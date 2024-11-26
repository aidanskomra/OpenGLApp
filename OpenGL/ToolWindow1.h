#pragma once
#include "Shader.h"
namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow1 : public System::Windows::Forms::Form
	{
	public:
		static bool RenderRedChannel;
		static bool RenderGreenChannel;
		static Shader* shaderInstance;
	private: System::Windows::Forms::TrackBar^ trackBarY;
	private: System::Windows::Forms::TrackBar^ trackBarU;
	private: System::Windows::Forms::TrackBar^ trackBarV;


	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ labelY;
	private: System::Windows::Forms::Label^ labelU;
	private: System::Windows::Forms::Label^ labelV;
	private: System::Windows::Forms::Label^ label4;
	public:

	public:
		static bool RenderBlueChannel;




		   

		ToolWindow1(Shader* shader)  
		{
			InitializeComponent();
			shaderInstance = shader;
			this->TopMost = true;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->trackBarY = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarU = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarV = (gcnew System::Windows::Forms::TrackBar());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->labelY = (gcnew System::Windows::Forms::Label());
			this->labelU = (gcnew System::Windows::Forms::Label());
			this->labelV = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarU))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarV))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(100, 23);
			this->label1->TabIndex = 10;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(38, 190);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(27, 25);
			this->label2->TabIndex = 5;
			this->label2->Text = L"U";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(38, 286);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(26, 25);
			this->label3->TabIndex = 6;
			this->label3->Text = L"V";
			// 
			// labelY
			// 
			this->labelY->AutoSize = true;
			this->labelY->Location = System::Drawing::Point(937, 94);
			this->labelY->Name = L"labelY";
			this->labelY->Size = System::Drawing::Size(24, 25);
			this->labelY->TabIndex = 7;
			this->labelY->Text = L"0";
			// 
			// labelU
			// 
			this->labelU->AutoSize = true;
			this->labelU->Location = System::Drawing::Point(937, 199);
			this->labelU->Name = L"labelU";
			this->labelU->Size = System::Drawing::Size(24, 25);
			this->labelU->TabIndex = 8;
			this->labelU->Text = L"0";
			// 
			// labelV
			// 
			this->labelV->AutoSize = true;
			this->labelV->Location = System::Drawing::Point(937, 286);
			this->labelV->Name = L"labelV";
			this->labelV->Size = System::Drawing::Size(24, 25);
			this->labelV->TabIndex = 9;
			this->labelV->Text = L"0";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(38, 94);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(27, 25);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Y";
			// 
			// ToolWindow1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1003, 470);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->labelV);
			this->Controls->Add(this->labelU);
			this->Controls->Add(this->labelY);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->trackBarV);
			this->Controls->Add(this->trackBarU);
			this->Controls->Add(this->trackBarY);
			this->Name = L"ToolWindow1";
			this->Text = L"ToolWindow";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarU))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarV))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


};
}
