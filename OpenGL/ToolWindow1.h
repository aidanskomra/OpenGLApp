#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "GameController.h"
#include "DefaultScene.h"
#include "FishScene.h"
#include "Scene.h"

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
		Shader* shader;




	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Label^ label1;
	public: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TrackBar^ trackBar1;


	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ sStrength;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TrackBar^ trackBar2;
	private: System::Windows::Forms::TrackBar^ trackBar3;
	private: System::Windows::Forms::TrackBar^ trackBar4;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::Button^ button2;
	public: System::Windows::Forms::CheckBox^ checkBox2;
	public: System::Windows::Forms::CheckBox^ checkBox3;
	public: System::Windows::Forms::CheckBox^ checkBox4;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TrackBar^ trackBar5;
	private: System::Windows::Forms::TrackBar^ trackBar6;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::CheckBox^ checkBox5;
	private: System::Windows::Forms::CheckBox^ checkBox6;
	private: System::Windows::Forms::RadioButton^ radioButton4;






	public:




		   

		ToolWindow1()  
		{
			InitializeComponent();
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

	public:
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
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->sStrength = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar3 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar4 = (gcnew System::Windows::Forms::TrackBar());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->trackBar5 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar6 = (gcnew System::Windows::Forms::TrackBar());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar6))->BeginInit();
			this->SuspendLayout();
			// 
			// checkBox1
			// 
			this->checkBox1->Location = System::Drawing::Point(0, 0);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(104, 24);
			this->checkBox1->TabIndex = 12;
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(100, 23);
			this->label1->TabIndex = 10;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(48, 31);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(149, 29);
			this->radioButton1->TabIndex = 13;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Move Light";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow1::radioButton1_CheckedChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(59, 76);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(229, 40);
			this->button1->TabIndex = 14;
			this->button1->Text = L"Reset Light Position";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ToolWindow1::button1_Click);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(59, 176);
			this->trackBar1->Maximum = 128;
			this->trackBar1->Minimum = 1;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(833, 90);
			this->trackBar1->TabIndex = 15;
			this->trackBar1->Value = 4;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &ToolWindow1::trackBar1_Scroll);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(74, 148);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(184, 25);
			this->label2->TabIndex = 16;
			this->label2->Text = L"Specular Strength";
			// 
			// sStrength
			// 
			this->sStrength->AutoSize = true;
			this->sStrength->Location = System::Drawing::Point(914, 176);
			this->sStrength->Name = L"sStrength";
			this->sStrength->Size = System::Drawing::Size(24, 25);
			this->sStrength->TabIndex = 17;
			this->sStrength->Text = L"4";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(79, 256);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(154, 25);
			this->label3->TabIndex = 18;
			this->label3->Text = L"Specular Color";
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(84, 295);
			this->trackBar2->Maximum = 300;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(808, 90);
			this->trackBar2->TabIndex = 19;
			this->trackBar2->Value = 1;
			this->trackBar2->Scroll += gcnew System::EventHandler(this, &ToolWindow1::trackBar2_Scroll);
			// 
			// trackBar3
			// 
			this->trackBar3->Location = System::Drawing::Point(84, 365);
			this->trackBar3->Maximum = 300;
			this->trackBar3->Name = L"trackBar3";
			this->trackBar3->Size = System::Drawing::Size(808, 90);
			this->trackBar3->TabIndex = 20;
			this->trackBar3->Value = 1;
			this->trackBar3->Scroll += gcnew System::EventHandler(this, &ToolWindow1::trackBar3_Scroll);
			// 
			// trackBar4
			// 
			this->trackBar4->Location = System::Drawing::Point(84, 439);
			this->trackBar4->Maximum = 300;
			this->trackBar4->Name = L"trackBar4";
			this->trackBar4->Size = System::Drawing::Size(808, 90);
			this->trackBar4->TabIndex = 21;
			this->trackBar4->Value = 1;
			this->trackBar4->Scroll += gcnew System::EventHandler(this, &ToolWindow1::trackBar4_Scroll);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(43, 295);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(27, 25);
			this->label4->TabIndex = 22;
			this->label4->Text = L"R";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(43, 365);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(28, 25);
			this->label5->TabIndex = 23;
			this->label5->Text = L"G";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(43, 439);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(26, 25);
			this->label6->TabIndex = 24;
			this->label6->Text = L"B";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(914, 295);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(54, 25);
			this->label7->TabIndex = 25;
			this->label7->Text = L"1.00";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(914, 365);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(54, 25);
			this->label8->TabIndex = 26;
			this->label8->Text = L"1.00";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(914, 439);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(54, 25);
			this->label9->TabIndex = 27;
			this->label9->Text = L"1.00";
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(48, 515);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(140, 29);
			this->radioButton2->TabIndex = 28;
			this->radioButton2->Text = L"Transform";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow1::radioButton2_CheckedChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(79, 566);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(209, 36);
			this->button2->TabIndex = 29;
			this->button2->Text = L"Reset Tranform";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &ToolWindow1::button2_Click);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(79, 619);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(134, 29);
			this->checkBox2->TabIndex = 30;
			this->checkBox2->Text = L"Translate";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow1::checkBox2_CheckedChanged);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(434, 619);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(107, 29);
			this->checkBox3->TabIndex = 31;
			this->checkBox3->Text = L"Rotate";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow1::checkBox3_CheckedChanged);
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(810, 619);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(98, 29);
			this->checkBox4->TabIndex = 32;
			this->checkBox4->Text = L"Scale";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow1::checkBox4_CheckedChanged);
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(48, 689);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(167, 29);
			this->radioButton3->TabIndex = 33;
			this->radioButton3->Text = L"Water Scene";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow1::radioButton3_CheckedChanged);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(83, 733);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(114, 25);
			this->label10->TabIndex = 34;
			this->label10->Text = L"Frequency";
			// 
			// trackBar5
			// 
			this->trackBar5->Location = System::Drawing::Point(79, 772);
			this->trackBar5->Name = L"trackBar5";
			this->trackBar5->Size = System::Drawing::Size(813, 90);
			this->trackBar5->TabIndex = 35;
			this->trackBar5->Value = 1;
			this->trackBar5->Scroll += gcnew System::EventHandler(this, &ToolWindow1::trackBar5_Scroll);
			// 
			// trackBar6
			// 
			this->trackBar6->Location = System::Drawing::Point(84, 885);
			this->trackBar6->Name = L"trackBar6";
			this->trackBar6->Size = System::Drawing::Size(804, 90);
			this->trackBar6->TabIndex = 36;
			this->trackBar6->Scroll += gcnew System::EventHandler(this, &ToolWindow1::trackBar6_Scroll);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(88, 841);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(107, 25);
			this->label11->TabIndex = 37;
			this->label11->Text = L"Amplitude";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(919, 772);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(54, 25);
			this->label12->TabIndex = 38;
			this->label12->Text = L"1.00";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(924, 885);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(54, 25);
			this->label13->TabIndex = 39;
			this->label13->Text = L"0.00";
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(84, 982);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(218, 29);
			this->checkBox5->TabIndex = 40;
			this->checkBox5->Text = L"Wireframe Render";
			this->checkBox5->UseVisualStyleBackColor = true;
			this->checkBox5->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow1::checkBox5_CheckedChanged);
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Location = System::Drawing::Point(434, 982);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(129, 29);
			this->checkBox6->TabIndex = 41;
			this->checkBox6->Text = L"Tint Blue";
			this->checkBox6->UseVisualStyleBackColor = true;
			this->checkBox6->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow1::checkBox6_CheckedChanged);
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(48, 1051);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(171, 29);
			this->radioButton4->TabIndex = 42;
			this->radioButton4->Text = L"Space Scene";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// ToolWindow1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1023, 1115);
			this->Controls->Add(this->radioButton4);
			this->Controls->Add(this->checkBox6);
			this->Controls->Add(this->checkBox5);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->trackBar6);
			this->Controls->Add(this->trackBar5);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->checkBox4);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->trackBar4);
			this->Controls->Add(this->trackBar3);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->sStrength);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->checkBox1);
			this->Name = L"ToolWindow1";
			this->Text = L"ToolWindow";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar6))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


private: 
	
private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
	// Assuming trackBar1 is for specular strength
	float specularStrength = static_cast<float>(trackBar1->Value); // Convert slider value
	shader->SetFloat("material.specularStrength", specularStrength);
	sStrength->Text = specularStrength.ToString("F2"); // Update UI label
}

private: System::Void trackBar2_Scroll(System::Object^ sender, System::EventArgs^ e) {
	UpdateSpecularColor();
}

private: System::Void trackBar3_Scroll(System::Object^ sender, System::EventArgs^ e) {
	UpdateSpecularColor();
}

private: System::Void trackBar4_Scroll(System::Object^ sender, System::EventArgs^ e) {
	UpdateSpecularColor();
}

private: System::Void UpdateSpecularColor() {
	float r = static_cast<float>(trackBar2->Value) / 100.0f; // Normalize to 0.0 - 3.0
	float g = static_cast<float>(trackBar3->Value) / 100.0f;
	float b = static_cast<float>(trackBar4->Value) / 100.0f;

	// Update labels
	label7->Text = r.ToString("F2");
	label8->Text = g.ToString("F2");
	label9->Text = b.ToString("F2");

	// Update light color dynamically
	Scene* currentScene = GameController::GetInstance().GetCurrentScene();
	if (currentScene && !currentScene->GetLights().empty()) {
		Mesh* light = currentScene->GetLights()[0];
		light->SetSpecularColor(glm::vec3(r, g, b));
	}
}



private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	GameController::GetInstance().SetCurrentScene(new DefaultScene());
	DefaultScene* currentScene = dynamic_cast<DefaultScene*>(GameController::GetInstance().GetCurrentScene());
	if (currentScene) {
		currentScene->SetMoveLightActive(radioButton1->Checked);
	}
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	DefaultScene* currentScene = dynamic_cast<DefaultScene*>(GameController::GetInstance().GetCurrentScene());
	if (currentScene) {
		currentScene->ResetLightPosition();
	}
}
private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		GameController::GetInstance().SetCurrentScene(new DefaultScene());
		DefaultScene* currentScene = dynamic_cast<DefaultScene*>(GameController::GetInstance().GetCurrentScene());
		if (currentScene) {
			currentScene->SetTransformActive(radioButton2->Checked);
		}
}

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	DefaultScene* currentScene = dynamic_cast<DefaultScene*>(GameController::GetInstance().GetCurrentScene());
	if (currentScene) {
		currentScene->ResetTransform();
	}
}
private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	DefaultScene* currentScene = dynamic_cast<DefaultScene*>(GameController::GetInstance().GetCurrentScene());
	if (currentScene) {
		currentScene->SetTranslateActive(checkBox2->Checked);
	}
}
private: System::Void checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	DefaultScene* currentScene = dynamic_cast<DefaultScene*>(GameController::GetInstance().GetCurrentScene());
	if (currentScene) {
		currentScene->SetRotateActive(checkBox3->Checked);
	}
}
private: System::Void checkBox4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	DefaultScene* currentScene = dynamic_cast<DefaultScene*>(GameController::GetInstance().GetCurrentScene());
	if (currentScene) {
		currentScene->SetScaleActive(checkBox4->Checked);
	}
}
private: System::Void radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		GameController::GetInstance().SetCurrentScene(new FishScene());
}
private: System::Void trackBar5_Scroll(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void trackBar6_Scroll(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox5_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox6_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
