#pragma once

namespace kmdmanager2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// frmMain 摘要
	/// </summary>
	public ref class frmMain : public System::Windows::Forms::Form
	{
	public:
		frmMain(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~frmMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ groupBox1;
	protected:
	private: System::Windows::Forms::CheckBox^ chkAltitude;
	private: System::Windows::Forms::TextBox^ txtAltitude;
	private: System::Windows::Forms::ListView^ lvwDriver;

	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Button^ btnFileDialog;
	private: System::Windows::Forms::TextBox^ txtDriverPath;

	private: System::Windows::Forms::Button^ btnExit;
	private: System::Windows::Forms::Button^ btnAbout;
	private: System::Windows::Forms::Button^ btnOptions;
	private: System::Windows::Forms::Button^ btnRun;





	private: System::Windows::Forms::Button^ btnRegister;
	private: System::Windows::Forms::TextBox^ txtCtlCode;
	private: System::Windows::Forms::Button^ btnCtlIO;










	private: System::Windows::Forms::Button^ btnStop;

	private: System::Windows::Forms::Button^ btnUnregister;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::CheckBox^ chkAutoAll;

	private: System::Windows::Forms::CheckBox^ chkAutoStop;

	private: System::Windows::Forms::CheckBox^ chkAutoRun;





	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->chkAltitude = (gcnew System::Windows::Forms::CheckBox());
			this->txtAltitude = (gcnew System::Windows::Forms::TextBox());
			this->lvwDriver = (gcnew System::Windows::Forms::ListView());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->btnAbout = (gcnew System::Windows::Forms::Button());
			this->btnOptions = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->chkAutoAll = (gcnew System::Windows::Forms::CheckBox());
			this->chkAutoStop = (gcnew System::Windows::Forms::CheckBox());
			this->chkAutoRun = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtCtlCode = (gcnew System::Windows::Forms::TextBox());
			this->btnCtlIO = (gcnew System::Windows::Forms::Button());
			this->btnStop = (gcnew System::Windows::Forms::Button());
			this->btnUnregister = (gcnew System::Windows::Forms::Button());
			this->btnRun = (gcnew System::Windows::Forms::Button());
			this->btnRegister = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->btnFileDialog = (gcnew System::Windows::Forms::Button());
			this->txtDriverPath = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->chkAltitude);
			this->groupBox1->Controls->Add(this->txtAltitude);
			this->groupBox1->Location = System::Drawing::Point(7, 20);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(160, 75);
			this->groupBox1->TabIndex = 15;
			this->groupBox1->TabStop = false;
			// 
			// chkAltitude
			// 
			this->chkAltitude->AutoSize = true;
			this->chkAltitude->Location = System::Drawing::Point(8, 30);
			this->chkAltitude->Name = L"chkAltitude";
			this->chkAltitude->Size = System::Drawing::Size(28, 27);
			this->chkAltitude->TabIndex = 13;
			this->chkAltitude->UseVisualStyleBackColor = true;
			this->chkAltitude->CheckedChanged += gcnew System::EventHandler(this, &frmMain::chkAltitude_CheckedChanged);
			// 
			// txtAltitude
			// 
			this->txtAltitude->Location = System::Drawing::Point(45, 24);
			this->txtAltitude->Name = L"txtAltitude";
			this->txtAltitude->Size = System::Drawing::Size(105, 35);
			this->txtAltitude->TabIndex = 5;
			// 
			// lvwDriver
			// 
			this->lvwDriver->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->lvwDriver->HideSelection = false;
			this->lvwDriver->Location = System::Drawing::Point(7, 430);
			this->lvwDriver->Name = L"lvwDriver";
			this->lvwDriver->Size = System::Drawing::Size(975, 308);
			this->lvwDriver->TabIndex = 14;
			this->lvwDriver->UseCompatibleStateImageBehavior = false;
			this->lvwDriver->View = System::Windows::Forms::View::Details;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->btnExit);
			this->groupBox4->Controls->Add(this->btnAbout);
			this->groupBox4->Controls->Add(this->btnOptions);
			this->groupBox4->Location = System::Drawing::Point(704, 100);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(278, 318);
			this->groupBox4->TabIndex = 13;
			this->groupBox4->TabStop = false;
			// 
			// btnExit
			// 
			this->btnExit->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnExit->Location = System::Drawing::Point(18, 230);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(240, 60);
			this->btnExit->TabIndex = 0;
			this->btnExit->Text = L"E&xit";
			this->btnExit->UseVisualStyleBackColor = true;
			this->btnExit->Click += gcnew System::EventHandler(this, &frmMain::btnExit_Click);
			// 
			// btnAbout
			// 
			this->btnAbout->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnAbout->Location = System::Drawing::Point(18, 135);
			this->btnAbout->Name = L"btnAbout";
			this->btnAbout->Size = System::Drawing::Size(240, 60);
			this->btnAbout->TabIndex = 1;
			this->btnAbout->Text = L"&About";
			this->btnAbout->UseVisualStyleBackColor = true;
			this->btnAbout->Click += gcnew System::EventHandler(this, &frmMain::btnAbout_Click);
			// 
			// btnOptions
			// 
			this->btnOptions->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnOptions->Location = System::Drawing::Point(18, 40);
			this->btnOptions->Name = L"btnOptions";
			this->btnOptions->Size = System::Drawing::Size(240, 60);
			this->btnOptions->TabIndex = 2;
			this->btnOptions->Text = L"&Options...";
			this->btnOptions->UseVisualStyleBackColor = true;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->chkAutoAll);
			this->groupBox3->Controls->Add(this->chkAutoStop);
			this->groupBox3->Controls->Add(this->chkAutoRun);
			this->groupBox3->Controls->Add(this->label1);
			this->groupBox3->Controls->Add(this->txtCtlCode);
			this->groupBox3->Controls->Add(this->btnCtlIO);
			this->groupBox3->Controls->Add(this->btnStop);
			this->groupBox3->Controls->Add(this->btnUnregister);
			this->groupBox3->Controls->Add(this->btnRun);
			this->groupBox3->Controls->Add(this->btnRegister);
			this->groupBox3->Location = System::Drawing::Point(7, 100);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(688, 318);
			this->groupBox3->TabIndex = 12;
			this->groupBox3->TabStop = false;
			// 
			// chkAutoAll
			// 
			this->chkAutoAll->AutoSize = true;
			this->chkAutoAll->Location = System::Drawing::Point(630, 155);
			this->chkAutoAll->Name = L"chkAutoAll";
			this->chkAutoAll->Size = System::Drawing::Size(28, 27);
			this->chkAutoAll->TabIndex = 12;
			this->chkAutoAll->UseVisualStyleBackColor = true;
			this->chkAutoAll->CheckedChanged += gcnew System::EventHandler(this, &frmMain::chkAutoAll_CheckedChanged);
			// 
			// chkAutoStop
			// 
			this->chkAutoStop->AutoSize = true;
			this->chkAutoStop->Location = System::Drawing::Point(300, 255);
			this->chkAutoStop->Name = L"chkAutoStop";
			this->chkAutoStop->Size = System::Drawing::Size(28, 27);
			this->chkAutoStop->TabIndex = 10;
			this->chkAutoStop->UseVisualStyleBackColor = true;
			this->chkAutoStop->CheckedChanged += gcnew System::EventHandler(this, &frmMain::chkAutoStop_CheckedChanged);
			// 
			// chkAutoRun
			// 
			this->chkAutoRun->AutoSize = true;
			this->chkAutoRun->Location = System::Drawing::Point(300, 55);
			this->chkAutoRun->Name = L"chkAutoRun";
			this->chkAutoRun->Size = System::Drawing::Size(28, 27);
			this->chkAutoRun->TabIndex = 7;
			this->chkAutoRun->UseVisualStyleBackColor = true;
			this->chkAutoRun->CheckedChanged += gcnew System::EventHandler(this, &frmMain::chkAutoRun_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(20, 150);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(135, 31);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Code(Hex)";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// txtCtlCode
			// 
			this->txtCtlCode->Location = System::Drawing::Point(188, 150);
			this->txtCtlCode->Name = L"txtCtlCode";
			this->txtCtlCode->Size = System::Drawing::Size(160, 35);
			this->txtCtlCode->TabIndex = 13;
			this->txtCtlCode->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &frmMain::txtCtlCode_KeyPress);
			// 
			// btnCtlIO
			// 
			this->btnCtlIO->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnCtlIO->Location = System::Drawing::Point(400, 135);
			this->btnCtlIO->Name = L"btnCtlIO";
			this->btnCtlIO->Size = System::Drawing::Size(200, 60);
			this->btnCtlIO->TabIndex = 4;
			this->btnCtlIO->Text = L"I/O &Control";
			this->btnCtlIO->UseVisualStyleBackColor = true;
			this->btnCtlIO->Click += gcnew System::EventHandler(this, &frmMain::btnCtlIO_Click);
			// 
			// btnStop
			// 
			this->btnStop->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnStop->Location = System::Drawing::Point(400, 235);
			this->btnStop->Name = L"btnStop";
			this->btnStop->Size = System::Drawing::Size(200, 60);
			this->btnStop->TabIndex = 11;
			this->btnStop->Text = L"&Stop";
			this->btnStop->UseVisualStyleBackColor = true;
			this->btnStop->Click += gcnew System::EventHandler(this, &frmMain::btnStop_Click);
			// 
			// btnUnregister
			// 
			this->btnUnregister->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnUnregister->Location = System::Drawing::Point(30, 235);
			this->btnUnregister->Name = L"btnUnregister";
			this->btnUnregister->Size = System::Drawing::Size(200, 60);
			this->btnUnregister->TabIndex = 9;
			this->btnUnregister->Text = L"&Unregister";
			this->btnUnregister->UseVisualStyleBackColor = true;
			this->btnUnregister->Click += gcnew System::EventHandler(this, &frmMain::btnUnregister_Click);
			// 
			// btnRun
			// 
			this->btnRun->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnRun->Location = System::Drawing::Point(400, 35);
			this->btnRun->Name = L"btnRun";
			this->btnRun->Size = System::Drawing::Size(200, 60);
			this->btnRun->TabIndex = 8;
			this->btnRun->Text = L"&Run";
			this->btnRun->UseVisualStyleBackColor = true;
			this->btnRun->Click += gcnew System::EventHandler(this, &frmMain::btnRun_Click);
			// 
			// btnRegister
			// 
			this->btnRegister->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnRegister->Location = System::Drawing::Point(30, 35);
			this->btnRegister->Name = L"btnRegister";
			this->btnRegister->Size = System::Drawing::Size(200, 60);
			this->btnRegister->TabIndex = 6;
			this->btnRegister->Text = L"Re&gister";
			this->btnRegister->UseVisualStyleBackColor = true;
			this->btnRegister->Click += gcnew System::EventHandler(this, &frmMain::btnRegister_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->btnFileDialog);
			this->groupBox2->Controls->Add(this->txtDriverPath);
			this->groupBox2->Location = System::Drawing::Point(176, 20);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(806, 75);
			this->groupBox2->TabIndex = 16;
			this->groupBox2->TabStop = false;
			// 
			// btnFileDialog
			// 
			this->btnFileDialog->Location = System::Drawing::Point(732, 19);
			this->btnFileDialog->Name = L"btnFileDialog";
			this->btnFileDialog->Size = System::Drawing::Size(68, 45);
			this->btnFileDialog->TabIndex = 4;
			this->btnFileDialog->Text = L"...";
			this->btnFileDialog->UseVisualStyleBackColor = true;
			this->btnFileDialog->Click += gcnew System::EventHandler(this, &frmMain::btnFileDialog_Click);
			// 
			// txtDriverPath
			// 
			this->txtDriverPath->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->txtDriverPath->Location = System::Drawing::Point(8, 20);
			this->txtDriverPath->Name = L"txtDriverPath";
			this->txtDriverPath->Size = System::Drawing::Size(710, 39);
			this->txtDriverPath->TabIndex = 3;
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(994, 750);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->lvwDriver);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"frmMain";
			this->Load += gcnew System::EventHandler(this, &frmMain::frmMain_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	protected:
		ref struct LoadDriverConfig
		{
			UInt32 Altitude;
			String^ DriverPath;
			String^ DriverName;
			UInt32 CtlCode;
			cli::array<Byte>^ InBuffer;
			cli::array<Byte>^ OutBuffer;

			System::Void reset()
			{
				Altitude = 260000;
				DriverPath = String::Empty;
				DriverName = String::Empty;
				CtlCode = 0;
				InBuffer = gcnew cli::array<Byte>(0);
				OutBuffer = gcnew cli::array<Byte>(0);
			}

			LoadDriverConfig() { reset(); }
		};
		LoadDriverConfig^ myCfg = gcnew LoadDriverConfig();
	protected: virtual System::Void WndProc(Message% m) override;
	private: System::Void frmMain_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btnExit_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btnFileDialog_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void chkAltitude_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void txtCtlCode_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
	private: System::Void chkAutoAll_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void chkAutoRun_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void chkAutoStop_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btnCtlIO_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btnUnregister_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btnRun_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btnStop_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btnAbout_Click(System::Object^ sender, System::EventArgs^ e);
};
}
