#pragma once

#pragma managed(push, off)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wil/resource.h>

#include <optional>
#include <string>
#include <chrono>

namespace ServiceManager {

	/// <summary>
	/// 提供驱动程序和服务的安装、启动、停止、删除等操作
	/// </summary>
	class WindowServiceManager {
	public:
		// 禁止拷贝
		WindowServiceManager(const WindowServiceManager&) = delete;
		WindowServiceManager& operator=(const WindowServiceManager&) = delete;

		// 允许移动
		WindowServiceManager(WindowServiceManager&&) = default;
		WindowServiceManager& operator=(WindowServiceManager&&) = default;

		/// <summary>
		/// 构造函数，打开服务控制管理器
		/// </summary>
		/// <param name="dwAccess">访问权限，默认为 SC_MANAGER_ALL_ACCESS</param>
		explicit WindowServiceManager(DWORD dwAccess = SC_MANAGER_ALL_ACCESS) noexcept
			: m_hSCManager(::OpenSCManagerW(nullptr, nullptr, dwAccess)) {
		}

		/// <summary>
		/// 检查服务控制管理器是否有效
		/// </summary>
		[[nodiscard]] bool IsValid() const noexcept {
			return static_cast<bool>(m_hSCManager);
		}

		/// <summary>
		/// 显式布尔转换，检查服务控制管理器是否有效
		/// </summary>
		[[nodiscard]] explicit operator bool() const noexcept {
			return IsValid();
		}

		/// <summary>
		/// 检查指定服务是否存在
		/// </summary>
		/// <param name="szServiceName">服务名称</param>
		/// <returns>服务存在返回 true，否则返回 false</returns>
		[[nodiscard]] bool HasService(LPCWSTR szServiceName) const noexcept {
			if (!m_hSCManager) return false;

			wil::unique_schandle hService(
				::OpenServiceW(m_hSCManager.get(), szServiceName, SERVICE_QUERY_STATUS));
			return static_cast<bool>(hService);
		}

		/// <summary>
		/// 查询服务当前状态
		/// </summary>
		/// <param name="szServiceName">服务名称</param>
		/// <returns>服务状态，如果查询失败返回 std::nullopt</returns>
		[[nodiscard]] std::optional<DWORD> QueryServiceState(LPCWSTR szServiceName) const noexcept {
			if (!m_hSCManager) return std::nullopt;

			wil::unique_schandle hService(
				::OpenServiceW(m_hSCManager.get(), szServiceName, SERVICE_QUERY_STATUS));
			if (!hService) return std::nullopt;

			SERVICE_STATUS ss{};
			if (!::QueryServiceStatus(hService.get(), &ss)) return std::nullopt;

			return ss.dwCurrentState;
		}

		/// <summary>
		/// 检查指定服务是否正在运行
		/// </summary>
		/// <param name="szServiceName">服务名称</param>
		/// <returns>服务正在运行返回 true，否则返回 false</returns>
		[[nodiscard]] bool IsServiceRunning(LPCWSTR szServiceName) const noexcept {
			auto state = QueryServiceState(szServiceName);
			return state.has_value() && state.value() == SERVICE_RUNNING;
		}

		/// <summary>
		/// 启动指定服务
		/// </summary>
		/// <param name="szServiceName">服务名称</param>
		/// <returns>启动成功或服务已运行返回 true，否则返回 false</returns>
		[[nodiscard]] bool ServiceStart(LPCWSTR szServiceName) const noexcept {
			if (!m_hSCManager) return false;

			wil::unique_schandle hService(
				::OpenServiceW(m_hSCManager.get(), szServiceName, SERVICE_START));
			if (!hService) return false;

			if (::StartServiceW(hService.get(), 0, nullptr)) {
				return true;
			}
			return ::GetLastError() == ERROR_SERVICE_ALREADY_RUNNING;
		}

		/// <summary>
		/// 停止指定服务
		/// </summary>
		/// <param name="szServiceName">服务名称</param>
		/// <param name="timeout">等待服务停止的超时时间，默认 30 秒</param>
		/// <returns>停止成功返回 true，否则返回 false</returns>
		[[nodiscard]] bool ServiceStop(
			LPCWSTR szServiceName,
			std::chrono::milliseconds timeout = std::chrono::seconds(30)) const noexcept {
			if (!m_hSCManager) return false;

			wil::unique_schandle hService(
				::OpenServiceW(m_hSCManager.get(), szServiceName, SERVICE_STOP | SERVICE_QUERY_STATUS));
			if (!hService) return false;

			SERVICE_STATUS ss{};
			if (!::ControlService(hService.get(), SERVICE_CONTROL_STOP, &ss)) {
				return ::GetLastError() == ERROR_SERVICE_NOT_ACTIVE;
			}

			// 等待服务完全停止
			return WaitForServiceState(hService.get(), SERVICE_STOPPED, timeout);
		}

		/// <summary>
		/// 删除指定服务
		/// </summary>
		/// <param name="szServiceName">服务名称</param>
		/// <returns>删除成功返回 true，否则返回 false</returns>
		[[nodiscard]] bool ServiceDelete(LPCWSTR szServiceName) const noexcept {
			if (!m_hSCManager) return false;

			wil::unique_schandle hService(
				::OpenServiceW(m_hSCManager.get(), szServiceName, SERVICE_STOP | DELETE | SERVICE_QUERY_STATUS));
			if (!hService) return false;

			// 如果服务正在运行，先停止它
			SERVICE_STATUS ss{};
			if (::QueryServiceStatus(hService.get(), &ss) && ss.dwCurrentState != SERVICE_STOPPED) {
				::ControlService(hService.get(), SERVICE_CONTROL_STOP, &ss);
				WaitForServiceState(hService.get(), SERVICE_STOPPED, std::chrono::seconds(30));
			}

			return ::DeleteService(hService.get()) != FALSE;
		}

		/// <summary>
		/// 安装内核驱动程序
		/// </summary>
		/// <param name="szBinaryPath">驱动程序二进制文件路径</param>
		/// <param name="szServiceName">服务名称</param>
		/// <param name="szDisplayName">显示名称</param>
		/// <returns>安装成功或服务已存在返回 true，否则返回 false</returns>
		[[nodiscard]] bool InstallDriver(
			LPCWSTR szBinaryPath,
			LPCWSTR szServiceName,
			LPCWSTR szDisplayName) const noexcept {
			return InstallServiceInternal(
				szBinaryPath, szServiceName, szDisplayName,
				SERVICE_KERNEL_DRIVER, nullptr, nullptr);
		}

		/// <summary>
		/// 安装文件系统过滤驱动程序
		/// </summary>
		/// <param name="szAltitude">过滤器高度值</param>
		/// <param name="szBinaryPath">驱动程序二进制文件路径</param>
		/// <param name="szServiceName">服务名称</param>
		/// <param name="szDisplayName">显示名称</param>
		/// <returns>安装成功或服务已存在返回 true，否则返回 false</returns>
		[[nodiscard]] bool InstallFSFilter(
			LPCWSTR szAltitude,
			LPCWSTR szBinaryPath,
			LPCWSTR szServiceName,
			LPCWSTR szDisplayName) const noexcept {
			if (!InstallServiceInternal(
				szBinaryPath, szServiceName, szDisplayName,
				SERVICE_FILE_SYSTEM_DRIVER, L"FSFilter Activity Monitor", L"FltMgr")) {
				return false;
			}

			return SetupFilterInstance(szServiceName, L"DefInst", szAltitude, 0, true);
		}

		/// <summary>
		/// 获取最后的 Windows 错误代码
		/// </summary>
		[[nodiscard]] static DWORD GetLastError() noexcept {
			return ::GetLastError();
		}

	private:
		/// <summary>
		/// 内部服务安装实现
		/// </summary>
		[[nodiscard]] bool InstallServiceInternal(
			LPCWSTR szBinaryPath,
			LPCWSTR szServiceName,
			LPCWSTR szDisplayName,
			DWORD dwServiceType,
			LPCWSTR szLoadOrderGroup,
			LPCWSTR szDependencies) const noexcept {
			if (!m_hSCManager) return false;

			WCHAR szDriverImagePath[MAX_PATH]{};
			if (::GetFullPathNameW(szBinaryPath, MAX_PATH, szDriverImagePath, nullptr) == 0) {
				return false;
			}

			wil::unique_schandle hService(::CreateServiceW(
				m_hSCManager.get(),
				szServiceName,
				szDisplayName,
				SERVICE_ALL_ACCESS,
				dwServiceType,
				SERVICE_DEMAND_START,
				SERVICE_ERROR_NORMAL,
				szDriverImagePath,
				szLoadOrderGroup,
				nullptr,
				szDependencies,
				nullptr,
				nullptr));

			if (!hService) {
				return ::GetLastError() == ERROR_SERVICE_EXISTS;
			}
			return true;
		}

		/// <summary>
		/// 等待服务达到指定状态
		/// </summary>
		[[nodiscard]] static bool WaitForServiceState(
			SC_HANDLE hService,
			DWORD dwDesiredState,
			std::chrono::milliseconds timeout) noexcept {
			const auto startTime = std::chrono::steady_clock::now();

			SERVICE_STATUS ss{};
			while (std::chrono::steady_clock::now() - startTime < timeout) {
				if (!::QueryServiceStatus(hService, &ss)) {
					return false;
				}
				if (ss.dwCurrentState == dwDesiredState) {
					return true;
				}

				// 使用服务建议的等待时间，但限制在合理范围内
				DWORD waitTime = ss.dwWaitHint / 10;
				waitTime = (std::max)(static_cast<DWORD>(100), (std::min)(waitTime, static_cast<DWORD>(1000)));
				::Sleep(waitTime);
			}
			return false;
		}

		/// <summary>
		/// 设置文件系统过滤器实例
		/// </summary>
		[[nodiscard]] static bool SetupFilterInstance(
			LPCWSTR szDriverName,
			LPCWSTR szInstanceName,
			LPCWSTR szAltitude,
			DWORD dwFlags,
			bool bSetAsDefaultInstance) noexcept {
			std::wstring keyPath = L"System\\CurrentControlSet\\Services\\";
			keyPath += szDriverName;

			wil::unique_hkey hKey;
			LSTATUS status = ::RegOpenKeyExW(
				HKEY_LOCAL_MACHINE, keyPath.c_str(), 0, KEY_ALL_ACCESS, &hKey);
			if (status != ERROR_SUCCESS) return false;

			wil::unique_hkey hInstancesKey;
			DWORD disposition = 0;
			status = ::RegCreateKeyExW(
				hKey.get(), L"Instances", 0, nullptr,
				REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &hInstancesKey, &disposition);
			if (status != ERROR_SUCCESS) return false;

			if (bSetAsDefaultInstance) {
				const DWORD cbData = static_cast<DWORD>((wcslen(szInstanceName) + 1) * sizeof(WCHAR));
				status = ::RegSetValueExW(
					hInstancesKey.get(), L"DefaultInstance", 0, REG_SZ,
					reinterpret_cast<const BYTE*>(szInstanceName), cbData);
				if (status != ERROR_SUCCESS) return false;
			}

			wil::unique_hkey hInstanceKey;
			status = ::RegCreateKeyExW(
				hInstancesKey.get(), szInstanceName, 0, nullptr,
				REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &hInstanceKey, &disposition);
			if (status != ERROR_SUCCESS) return false;

			// 设置 Altitude
			const DWORD cbAltitude = static_cast<DWORD>((wcslen(szAltitude) + 1) * sizeof(WCHAR));
			status = ::RegSetValueExW(
				hInstanceKey.get(), L"Altitude", 0, REG_SZ,
				reinterpret_cast<const BYTE*>(szAltitude), cbAltitude);
			if (status != ERROR_SUCCESS) return false;

			// 设置 Flags
			status = ::RegSetValueExW(
				hInstanceKey.get(), L"Flags", 0, REG_DWORD,
				reinterpret_cast<const BYTE*>(&dwFlags), sizeof(dwFlags));

			return status == ERROR_SUCCESS;
		}

		wil::unique_schandle m_hSCManager;
	};

} // namespace ServiceManager

#pragma managed(pop)