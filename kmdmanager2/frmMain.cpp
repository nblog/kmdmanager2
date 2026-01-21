#include "pch.h"
#include "frmMain.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>
#include <winternl.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "shell32.lib")

#include "../third_party/wincomp/wincomp.h"
#if defined(_M_IX86)
#pragma comment(lib, "..\\third_party\\wincomp\\x86\\wincomp.lib")
#elif defined(_M_X64)
#pragma comment(lib, "..\\third_party\\wincomp\\x64\\wincomp.lib")
#elif defined(_M_ARM64)
#pragma comment(lib, "..\\third_party\\wincomp\\arm64\\wincomp.lib")
#else
#error "Unsupported platform"
#endif
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")


namespace kmdmanager2 {
	static String^ GetLastErrorString(UInt32 errCode = ::GetLastError()) {
		DWORD dwError = errCode;
		if (0 == dwError) return "Completed.";

		LPWSTR lpMsgBuf = NULL;
		::FormatMessageW(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, 
			dwError, 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			(LPWSTR)&lpMsgBuf, 0, NULL);

		String^ errstr = gcnew String(lpMsgBuf);
		::LocalFree(lpMsgBuf);

		return errstr;
	}

	static System::Void UpdateWindowVisualEffects(System::IntPtr Handle) {
		RTL_OSVERSIONINFOW versionInfo = {};
#pragma warning( push )
#pragma warning( disable : 4996 )
		typedef NTSTATUS(WINAPI* fnRtlGetVersion)(PRTL_OSVERSIONINFOW lpVersionInformation);
		auto RtlGetVersion = (fnRtlGetVersion)::GetProcAddress(::GetModuleHandleW(L"ntdll.dll"), "RtlGetVersion");

		versionInfo.dwOSVersionInfoSize = sizeof(versionInfo);
		if (!NT_SUCCESS(RtlGetVersion(&versionInfo))) return;
#pragma warning( pop )
		HWND hWnd = (HWND)Handle.ToPointer();

		if (versionInfo.dwMajorVersion >= 10) {
			if (versionInfo.dwBuildNumber >= 22000) {
				// Check for Windows 11, 22H2 or later
				DWM_SYSTEMBACKDROP_TYPE sbt = DWMSBT_TRANSIENTWINDOW;
				::DwmSetWindowAttribute(hWnd, DWMWA_SYSTEMBACKDROP_TYPE, &sbt, sizeof(sbt));
			}
			else {
				// Windows 10 or later
				ACCENT_POLICY ap = { ACCENT_ENABLE_BLURBEHIND };
				WINDOWCOMPOSITIONATTRIBDATA wca = { WCA_ACCENT_POLICY, &ap, sizeof(ap) };
				::SetWindowCompositionAttribute(hWnd, &wca);
			}
		}
		else if (versionInfo.dwMajorVersion == 6 && versionInfo.dwMinorVersion >= 0) {
			// Windows Vista to Windows 7
			DWM_BLURBEHIND bb = { DWM_BB_ENABLE, TRUE, NULL, FALSE };
			::DwmEnableBlurBehindWindow(hWnd, &bb);
		}
	}
}

namespace kmdmanager2 {
	System::Void frmMain::WndProc(Message% m)
	{
		if (WM_DROPFILES == m.Msg)
		{
			HDROP hDrop = (HDROP)m.WParam.ToPointer();
			if (1 == ::DragQueryFileW(hDrop, UInt32::MaxValue, NULL, 0)) 
			{
				WCHAR szFile[MAX_PATH] = { 0 };
				::DragQueryFileW(hDrop, 0, szFile, MAX_PATH);
				if (IO::File::Exists(gcnew String(szFile)))
					this->txtDriverPath->Text = gcnew String(szFile);
			}
			::DragFinish(hDrop);
		}

		return Form::WndProc(m);
	}

	inline System::Void frmMain::btnExit_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
		return System::Void();
	}

	inline System::Void frmMain::frmMain_Load(System::Object^ sender, System::EventArgs^ e) {
		this->Text = "Kernel-Mode Driver Manager";
		this->groupBox1->Text = " FSFilter ";
		UpdateWindowVisualEffects(this->Handle);

		::ChangeWindowMessageFilterEx(HWND(this->Handle.ToPointer()), WM_DROPFILES, MSGFLT_ALLOW, NULL);
		::ChangeWindowMessageFilterEx(HWND(this->Handle.ToPointer()), WM_COPYDATA, MSGFLT_ALLOW, NULL);
		::ChangeWindowMessageFilterEx(HWND(this->Handle.ToPointer()), 0x0049/*WM_COPYGLOBALDATA*/, MSGFLT_ALLOW, NULL);
		::DragAcceptFiles(HWND(this->Handle.ToPointer()), TRUE);

		::SetWindowLongPtrW(HWND(this->txtAltitude->Handle.ToPointer()), GWL_STYLE, \
			::GetWindowLongPtrW(HWND(this->txtAltitude->Handle.ToPointer()), GWL_STYLE) | ES_NUMBER);
		this->txtAltitude->Text = this->myCfg->Altitude.ToString(); this->txtAltitude->Enabled = false;

		{
			this->lvwDriver->View = View::Details;
			this->lvwDriver->FullRowSelect = true;
			this->lvwDriver->GridLines = true;
			this->lvwDriver->MultiSelect = false;

			auto chDriver = gcnew ColumnHeader();
			chDriver->Text = "Driver";
			chDriver->Width = 100;

			auto chOperation = gcnew ColumnHeader();
			chOperation->Text = "Operation";
			chOperation->Width = 88;

			auto chStatus = gcnew ColumnHeader();
			chStatus->Text = "Status";
			chStatus->Width = 60;

			auto chResult = gcnew ColumnHeader();
			chResult->Text = "Result";
			chResult->Width = 180;

			this->lvwDriver->Columns->AddRange(gcnew cli::array<ColumnHeader^> {
				chDriver, chOperation, chStatus, chResult
			});
		}

		return System::Void();
	}

	inline System::Void frmMain::btnFileDialog_Click(System::Object^ sender, System::EventArgs^ e) {
		auto ofd = gcnew OpenFileDialog();
		ofd->Filter = "Driver Files (*.sys)|*.sys|All files (*.*)|*.*";
		ofd->RestoreDirectory = true;

		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			this->txtDriverPath->Text = ofd->FileName;
		}

		return System::Void();
	}

	inline System::Void frmMain::chkAltitude_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		this->txtAltitude->Enabled = this->chkAltitude->Checked;

		if (this->chkAltitude->Checked != true) return;

		return System::Void();
	}

	inline System::Void frmMain::txtCtlCode_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Uri::IsHexDigit(e->KeyChar) && !Char::IsControl(e->KeyChar)) {
			e->Handled = true;
		}

		return System::Void();
	}

	inline System::Void frmMain::chkAutoAll_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		this->btnCtlIO->Text = this->chkAutoAll->Checked ? "All A&ctions" : "I/O &Control";

		this->btnRun->Enabled = !this->chkAutoRun->Checked && !this->chkAutoAll->Checked;
		this->btnStop->Enabled = !this->chkAutoStop->Checked && !this->chkAutoAll->Checked;

		this->btnRegister->Enabled = !this->chkAutoAll->Checked;
		this->btnUnregister->Enabled = !this->chkAutoAll->Checked;

		this->chkAutoRun->Enabled = !this->chkAutoAll->Checked;
		this->chkAutoStop->Enabled = !this->chkAutoAll->Checked;
		return System::Void();
	}

	inline System::Void frmMain::chkAutoRun_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		this->btnRegister->Text = this->chkAutoRun->Checked ? "&Reg'n'Run" : "Re&gister";

		this->btnRun->Enabled = !this->chkAutoRun->Checked;
		return System::Void();
	}

	inline System::Void frmMain::chkAutoStop_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		this->btnUnregister->Text = this->chkAutoStop->Checked ? "&Stop'n'Unreg" : "&Unregister";

		this->btnStop->Enabled = !this->chkAutoStop->Checked;
		return System::Void();
	}

	inline System::Void frmMain::btnCtlIO_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->chkAutoAll->Checked) {
			this->btnRegister_Click(sender, e);
			this->btnRun_Click(sender, e);
		}

		unsigned int value = 0;
		if (UInt32::TryParse(this->txtCtlCode->Text, value))
			this->myCfg->CtlCode = value;

		if (0 == this->myCfg->CtlCode) {
			MessageBox::Show("Invalid control code.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return System::Void();
		}

		cli::pin_ptr<Byte> pInBuffer = \
			this->myCfg->InBuffer->Length ? &this->myCfg->InBuffer[0] : nullptr;
		cli::pin_ptr<Byte> pOutBuffer = \
			this->myCfg->OutBuffer->Length ? &this->myCfg->OutBuffer[0] : nullptr;

		DWORD dwBytesReturned = 0;
		BOOL isOk = ::DeviceIoControl(
			INVALID_HANDLE_VALUE,
			this->myCfg->CtlCode,
			pInBuffer, this->myCfg->InBuffer->Length,
			pOutBuffer, this->myCfg->OutBuffer->Length, &dwBytesReturned, NULL);

		this->lvwDriver->Items->Add(gcnew ListViewItem(gcnew cli::array<String^> {
			this->myCfg->DriverName, "I/O Control", isOk ? "Success" : "Failure", isOk ? String::Format("Written: {0}", dwBytesReturned) : GetLastErrorString()
		}));

		if (this->chkAutoAll->Checked) {
			this->btnStop_Click(sender, e);
			this->btnUnregister_Click(sender, e);
		}

		return System::Void();
	}

	inline System::Void frmMain::btnRegister_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::Empty == this->txtDriverPath->Text || !IO::File::Exists(IO::Path::GetFullPath(this->txtDriverPath->Text))) {
			MessageBox::Show("Driver file not found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return System::Void();
		}

		if (this->chkAltitude->Checked && this->txtAltitude->Text != String::Empty) {
			unsigned int value = 0;
			bool isNumeric = UInt32::TryParse(this->txtAltitude->Text, value);
			// https://learn.microsoft.com/windows-hardware/drivers/ifs/load-order-groups-and-altitudes-for-minifilter-drivers
			if (!isNumeric || value < 40000 || value > 429999) {
				auto toolTip1 = gcnew ToolTip();
				toolTip1->ToolTipIcon = ToolTipIcon::Warning;
				toolTip1->Show("altitude ranges from 40000 to 429999.", this->txtAltitude, 0, this->txtAltitude->Height, 2000);
				this->txtAltitude->Text = this->myCfg->Altitude.ToString();
				return System::Void();
			}
			this->myCfg->Altitude = value;
		}

		this->myCfg->DriverPath = IO::Path::GetFullPath(this->txtDriverPath->Text);
		this->myCfg->DriverName = IO::Path::GetFileNameWithoutExtension(this->myCfg->DriverPath);

		// ...
		if (this->chkAltitude->Checked) {
			this->myCfg->Altitude;
		}
		else {

		}

		this->lvwDriver->Items->Add(gcnew ListViewItem(gcnew cli::array<String^> {
			this->myCfg->DriverName, "Register", false ? "Success" : "Failure", GetLastErrorString()
		}));

		if (this->chkAutoRun->Checked) {
			this->btnRun_Click(sender, e);
		}

		return System::Void();
	}

	inline System::Void frmMain::btnUnregister_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::Empty == this->txtDriverPath->Text || !IO::File::Exists(this->myCfg->DriverPath)) {
			MessageBox::Show("Driver file not found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return System::Void();
		}

		if (this->chkAutoStop->Checked) {
			this->btnStop_Click(sender, e);
		}

		// ...
		this->lvwDriver->Items->Add(gcnew ListViewItem(gcnew cli::array<String^> {
			this->myCfg->DriverName, "Unregister", false ? "Success" : "Failure", GetLastErrorString()
		}));

		this->myCfg->reset();

		return System::Void();
	}

	inline System::Void frmMain::btnRun_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::Empty == this->myCfg->DriverName) {
			MessageBox::Show("Driver file not found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return System::Void();
		}

		// ...
		this->lvwDriver->Items->Add(gcnew ListViewItem(gcnew cli::array<String^> {
			this->myCfg->DriverName, "Run", false ? "Success" : "Failure", GetLastErrorString()
		}));

		return System::Void();
	}

	inline System::Void frmMain::btnStop_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::Empty == this->myCfg->DriverName) {
			MessageBox::Show("Driver file not found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return System::Void();
		}

		// ...
		this->lvwDriver->Items->Add(gcnew ListViewItem(gcnew cli::array<String^> {
			this->myCfg->DriverName, "Stop", false ? "Success" : "Failure", GetLastErrorString()
		}));

		return System::Void();
	}

	inline System::Void frmMain::btnAbout_Click(System::Object^ sender, System::EventArgs^ e) {
		auto version = System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Version;
		auto AboutMessage = String::Format(R"(Kernel-Mode Driver Manager  v{0}.{1}.{2}

https://github.com/nblog/kmdmanager2)", version->Major, version->Minor, version->Build);
		MessageBox::Show(gcnew String(AboutMessage), "About", MessageBoxButtons::OK, MessageBoxIcon::Information);

		return System::Void();
	}
}