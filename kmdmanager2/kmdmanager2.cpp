#include "pch.h"
#include "frmMain.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew kmdmanager2::frmMain());

    return Environment::ExitCode;
}
