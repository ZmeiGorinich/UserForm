#pragma once
#include "RestApi.h"
#include <msclr/marshal_cppstd.h>
namespace UserForm {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;
    using namespace System::Threading;
    using namespace System::Text::RegularExpressions;
    using namespace System::IO;

    /// <summary>
    /// Summary for MyForm
    /// </summary>
    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            CreatePositionsList();
            myThreadApi = gcnew Thread(gcnew ThreadStart(this, &MyForm::CreateUserList));
            myThreadApi->Start();
            //
            //TODO: Add the constructor code here
            //
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~MyForm()
        {
            try {
                myThreadRotate->Abort();
            }
            catch (...) {}
            try {
                myThreadRotate->Abort();
            }
            catch (...) {}
            if (components)
            {
                delete components;
            }
        }

        
        rest::RestApi* restApi = new rest::RestApi;
        int indexPaddingPicture = -84;
        const int countUsersInRequest = 6;
        int page = 1;
        bool update = false;

        Thread^ myThreadApi;
        Thread^ myThreadRotate;

        System::Windows::Forms::PictureBox^ pictureBox1;
        System::Windows::Forms::PictureBox^ pictureBox2;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Label^ label3;

        List<PictureBox^>^ pics = gcnew List<PictureBox^>();
        List<Label^>^ names = gcnew List<Label^>();
        List<Label^>^ emails = gcnew List<Label^>();
        List<Label^>^ positionsLabel = gcnew List<Label^>();
        List<Label^>^ phones = gcnew List<Label^>();
        List<RadioButton^>^ radioButtons = gcnew List<RadioButton^>();

        Image^ errorImage = Image::FromFile("res/placeholder.png");


        System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));

        System::Windows::Forms::Panel^ panelUserList;
        System::Windows::Forms::Panel^ panelUserForm;
        System::Windows::Forms::Panel^ panelNewUserSuccess;



        System::Windows::Forms::TextBox^ textboxUserFormPicture;
        System::Windows::Forms::TextBox^ textboxUserFormPhone;
        System::Windows::Forms::TextBox^ textboxUserFormEmail;
        System::Windows::Forms::TextBox^ textboxUserFormName;

        System::Windows::Forms::Label^ labelUserFormPhotoError;
        System::Windows::Forms::Label^ labelUserFormPhoto;
        System::Windows::Forms::Label^ labelUserFormPositionError;
        System::Windows::Forms::Label^ labelUserFormPosition;
        System::Windows::Forms::Label^ labelUserFormPhoneError;
        System::Windows::Forms::Label^ labelUserFormPhone;
        System::Windows::Forms::Label^ labelUserFormEmailError;
        System::Windows::Forms::Label^ labelUserFormEmail;
        System::Windows::Forms::Label^ labelUserFormNameError;
        System::Windows::Forms::Label^ labelUserFormName;
        System::Windows::Forms::Label^ labelSuccess;


        System::Windows::Forms::PictureBox^ buttonSuccessAddOneMore;
        System::Windows::Forms::PictureBox^ buttonShowUserList;
        System::Windows::Forms::PictureBox^ pictureBoxUploadPicture;


        System::Windows::Forms::PictureBox^ pictureBoxSuccess;


        System::Windows::Forms::PictureBox^ pictureBoxShowMoreUsers;
        System::Windows::Forms::PictureBox^ pictureBoxUserListLoading;
        System::Windows::Forms::PictureBox^ pictureBoxAddUser;
        System::Windows::Forms::OpenFileDialog^ openFileDialog1;

    protected:


        System::ComponentModel::IContainer^ components;
    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->panelUserList = (gcnew System::Windows::Forms::Panel());
            this->panelUserForm = (gcnew System::Windows::Forms::Panel());
            this->labelUserFormPhotoError = (gcnew System::Windows::Forms::Label());
            this->pictureBoxUploadPicture = (gcnew System::Windows::Forms::PictureBox());
            this->textboxUserFormPicture = (gcnew System::Windows::Forms::TextBox());
            this->textboxUserFormPhone = (gcnew System::Windows::Forms::TextBox());
            this->textboxUserFormEmail = (gcnew System::Windows::Forms::TextBox());
            this->textboxUserFormName = (gcnew System::Windows::Forms::TextBox());
            this->labelUserFormPhoto = (gcnew System::Windows::Forms::Label());
            this->labelUserFormPositionError = (gcnew System::Windows::Forms::Label());
            this->labelUserFormPosition = (gcnew System::Windows::Forms::Label());
            this->labelUserFormPhoneError = (gcnew System::Windows::Forms::Label());
            this->labelUserFormPhone = (gcnew System::Windows::Forms::Label());
            this->labelUserFormEmailError = (gcnew System::Windows::Forms::Label());
            this->labelUserFormEmail = (gcnew System::Windows::Forms::Label());
            this->labelUserFormNameError = (gcnew System::Windows::Forms::Label());
            this->labelUserFormName = (gcnew System::Windows::Forms::Label());
            this->panelNewUserSuccess = (gcnew System::Windows::Forms::Panel());
            this->labelSuccess = (gcnew System::Windows::Forms::Label());
            this->pictureBoxSuccess = (gcnew System::Windows::Forms::PictureBox());
            this->buttonSuccessAddOneMore = (gcnew System::Windows::Forms::PictureBox());
            this->buttonShowUserList = (gcnew System::Windows::Forms::PictureBox());
            this->pictureBoxUserListLoading = (gcnew System::Windows::Forms::PictureBox());
            this->pictureBoxShowMoreUsers = (gcnew System::Windows::Forms::PictureBox());
            this->pictureBoxAddUser = (gcnew System::Windows::Forms::PictureBox());
            this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
            this->panelUserForm->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxUploadPicture))->BeginInit();
            this->panelNewUserSuccess->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxSuccess))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->buttonSuccessAddOneMore))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->buttonShowUserList))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxUserListLoading))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxShowMoreUsers))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxAddUser))->BeginInit();
            this->SuspendLayout();
            // 
            // pictureBox1
            // 
            this->pictureBox1->Location = System::Drawing::Point(0, 0);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(320, 54);
            this->pictureBox1->TabIndex = 0;
            this->pictureBox1->TabStop = false;
            this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
            // 
            // pictureBox2
            // 
            this->pictureBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
                static_cast<System::Int32>(static_cast<System::Byte>(240)));
            this->pictureBox2->Location = System::Drawing::Point(320, 0);
            this->pictureBox2->Name = L"pictureBox2";
            this->pictureBox2->Size = System::Drawing::Size(320, 54);
            this->pictureBox2->TabIndex = 1;
            this->pictureBox2->TabStop = false;
            this->pictureBox2->Click += gcnew System::EventHandler(this, &MyForm::pictureBox2_Click);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Inter", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(130, 16);
            this->label1->Margin = System::Windows::Forms::Padding(0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(56, 20);
            this->label1->TabIndex = 2;
            this->label1->Text = L"Users";
            this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
                static_cast<System::Int32>(static_cast<System::Byte>(240)));
            this->label2->Font = (gcnew System::Drawing::Font(L"Inter", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(437, 16);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(86, 20);
            this->label2->TabIndex = 3;
            this->label2->Text = L"Add User";
            this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Inter", 18));
            this->label3->Location = System::Drawing::Point(260, 86);
            this->label3->Margin = System::Windows::Forms::Padding(0);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(121, 29);
            this->label3->TabIndex = 4;
            this->label3->Text = L"Users list";
            // 
            // panelUserList
            // 
            this->panelUserList->AutoScroll = true;
            this->panelUserList->Location = System::Drawing::Point(0, 139);
            this->panelUserList->Name = L"panelUserList";
            this->panelUserList->Size = System::Drawing::Size(640, 702);
            this->panelUserList->TabIndex = 7;
            // 
            // panelUserForm
            // 
            this->panelUserForm->Controls->Add(this->labelUserFormPhotoError);
            this->panelUserForm->Controls->Add(this->pictureBoxUploadPicture);
            this->panelUserForm->Controls->Add(this->textboxUserFormPicture);
            this->panelUserForm->Controls->Add(this->textboxUserFormPhone);
            this->panelUserForm->Controls->Add(this->textboxUserFormEmail);
            this->panelUserForm->Controls->Add(this->textboxUserFormName);
            this->panelUserForm->Controls->Add(this->labelUserFormPhoto);
            this->panelUserForm->Controls->Add(this->labelUserFormPositionError);
            this->panelUserForm->Controls->Add(this->labelUserFormPosition);
            this->panelUserForm->Controls->Add(this->labelUserFormPhoneError);
            this->panelUserForm->Controls->Add(this->labelUserFormPhone);
            this->panelUserForm->Controls->Add(this->labelUserFormEmailError);
            this->panelUserForm->Controls->Add(this->labelUserFormEmail);
            this->panelUserForm->Controls->Add(this->labelUserFormNameError);
            this->panelUserForm->Controls->Add(this->labelUserFormName);
            this->panelUserForm->Location = System::Drawing::Point(0, 139);
            this->panelUserForm->Name = L"panelUserForm";
            this->panelUserForm->Size = System::Drawing::Size(640, 702);
            this->panelUserForm->TabIndex = 30;
            this->panelUserForm->Visible = false;
            // 
            // labelUserFormPhotoError
            // 
            this->labelUserFormPhotoError->AutoSize = true;
            this->labelUserFormPhotoError->Font = (gcnew System::Drawing::Font(L"Inter", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelUserFormPhotoError->Location = System::Drawing::Point(120, 668);
            this->labelUserFormPhotoError->Margin = System::Windows::Forms::Padding(0);
            this->labelUserFormPhotoError->Name = L"labelUserFormPhotoError";
            this->labelUserFormPhotoError->Size = System::Drawing::Size(71, 15);
            this->labelUserFormPhotoError->TabIndex = 24;
            this->labelUserFormPhotoError->Text = L"Enter photo";
            this->labelUserFormPhotoError->Visible = false;
            // 
            // pictureBoxUploadPicture
            // 
            this->pictureBoxUploadPicture->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBoxUploadPicture.Image")));
            this->pictureBoxUploadPicture->Location = System::Drawing::Point(434, 612);
            this->pictureBoxUploadPicture->Name = L"pictureBoxUploadPicture";
            this->pictureBoxUploadPicture->Size = System::Drawing::Size(86, 48);
            this->pictureBoxUploadPicture->TabIndex = 30;
            this->pictureBoxUploadPicture->TabStop = false;
            this->pictureBoxUploadPicture->Click += gcnew System::EventHandler(this, &MyForm::pictureBoxUploadPicture_Click);
            // 
            // textboxUserFormPicture
            // 
            this->textboxUserFormPicture->Font = (gcnew System::Drawing::Font(L"Inter", 25));
            this->textboxUserFormPicture->ForeColor = System::Drawing::SystemColors::GrayText;
            this->textboxUserFormPicture->Location = System::Drawing::Point(120, 612);
            this->textboxUserFormPicture->Margin = System::Windows::Forms::Padding(0);
            this->textboxUserFormPicture->Name = L"textboxUserFormPicture";
            this->textboxUserFormPicture->Size = System::Drawing::Size(314, 48);
            this->textboxUserFormPicture->TabIndex = 43;
            this->textboxUserFormPicture->Text = L"Upload photo";
            this->textboxUserFormPicture->Enter += gcnew System::EventHandler(this, &MyForm::textboxUserFormPicture_Enter);
            this->textboxUserFormPicture->Leave += gcnew System::EventHandler(this, &MyForm::textboxUserFormPicture_Leave);
            // 
            // textboxUserFormPhone
            // 
            this->textboxUserFormPhone->Font = (gcnew System::Drawing::Font(L"Inter", 25));
            this->textboxUserFormPhone->ForeColor = System::Drawing::SystemColors::GrayText;
            this->textboxUserFormPhone->Location = System::Drawing::Point(120, 287);
            this->textboxUserFormPhone->Margin = System::Windows::Forms::Padding(0);
            this->textboxUserFormPhone->Name = L"textboxUserFormPhone";
            this->textboxUserFormPhone->Size = System::Drawing::Size(400, 48);
            this->textboxUserFormPhone->TabIndex = 42;
            this->textboxUserFormPhone->Text = L"Phone";
            this->textboxUserFormPhone->TextChanged += gcnew System::EventHandler(this, &MyForm::textboxUserFormPhone_TextChanged);
            this->textboxUserFormPhone->Enter += gcnew System::EventHandler(this, &MyForm::textboxUserFormPhone_Enter);
            this->textboxUserFormPhone->Leave += gcnew System::EventHandler(this, &MyForm::textboxUserFormPhone_Leave);
            // 
            // textboxUserFormEmail
            // 
            this->textboxUserFormEmail->Font = (gcnew System::Drawing::Font(L"Inter", 25));
            this->textboxUserFormEmail->ForeColor = System::Drawing::SystemColors::GrayText;
            this->textboxUserFormEmail->Location = System::Drawing::Point(120, 165);
            this->textboxUserFormEmail->Margin = System::Windows::Forms::Padding(0);
            this->textboxUserFormEmail->Name = L"textboxUserFormEmail";
            this->textboxUserFormEmail->Size = System::Drawing::Size(400, 48);
            this->textboxUserFormEmail->TabIndex = 41;
            this->textboxUserFormEmail->Text = L"Email";
            this->textboxUserFormEmail->TextChanged += gcnew System::EventHandler(this, &MyForm::textboxUserFormEmail_TextChanged);
            this->textboxUserFormEmail->Enter += gcnew System::EventHandler(this, &MyForm::textboxUserFormEmail_Enter);
            this->textboxUserFormEmail->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textboxUserFormEmail_KeyPress);
            this->textboxUserFormEmail->Leave += gcnew System::EventHandler(this, &MyForm::textboxUserFormEmail_Leave);
            // 
            // textboxUserFormName
            // 
            this->textboxUserFormName->Font = (gcnew System::Drawing::Font(L"Inter", 25));
            this->textboxUserFormName->ForeColor = System::Drawing::SystemColors::GrayText;
            this->textboxUserFormName->Location = System::Drawing::Point(120, 43);
            this->textboxUserFormName->Margin = System::Windows::Forms::Padding(0);
            this->textboxUserFormName->Name = L"textboxUserFormName";
            this->textboxUserFormName->Size = System::Drawing::Size(400, 48);
            this->textboxUserFormName->TabIndex = 40;
            this->textboxUserFormName->Text = L"Name";
            this->textboxUserFormName->TextChanged += gcnew System::EventHandler(this, &MyForm::textboxUserFormName_TextChanged);
            this->textboxUserFormName->Enter += gcnew System::EventHandler(this, &MyForm::textboxUserFormName_Enter);
            this->textboxUserFormName->Leave += gcnew System::EventHandler(this, &MyForm::textboxUserFormName_Leave);
            // 
            // labelUserFormPhoto
            // 
            this->labelUserFormPhoto->AutoSize = true;
            this->labelUserFormPhoto->Font = (gcnew System::Drawing::Font(L"Inter", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelUserFormPhoto->Location = System::Drawing::Point(120, 585);
            this->labelUserFormPhoto->Margin = System::Windows::Forms::Padding(0);
            this->labelUserFormPhoto->Name = L"labelUserFormPhoto";
            this->labelUserFormPhoto->Size = System::Drawing::Size(51, 19);
            this->labelUserFormPhoto->TabIndex = 39;
            this->labelUserFormPhoto->Text = L"Photo";
            // 
            // labelUserFormPositionError
            // 
            this->labelUserFormPositionError->AutoSize = true;
            this->labelUserFormPositionError->Font = (gcnew System::Drawing::Font(L"Inter", 9));
            this->labelUserFormPositionError->Location = System::Drawing::Point(120, 567);
            this->labelUserFormPositionError->Margin = System::Windows::Forms::Padding(0);
            this->labelUserFormPositionError->Name = L"labelUserFormPositionError";
            this->labelUserFormPositionError->Size = System::Drawing::Size(83, 15);
            this->labelUserFormPositionError->TabIndex = 38;
            this->labelUserFormPositionError->Text = L"Enter position";
            this->labelUserFormPositionError->Visible = false;
            // 
            // labelUserFormPosition
            // 
            this->labelUserFormPosition->AutoSize = true;
            this->labelUserFormPosition->Font = (gcnew System::Drawing::Font(L"Inter", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelUserFormPosition->Location = System::Drawing::Point(120, 382);
            this->labelUserFormPosition->Margin = System::Windows::Forms::Padding(0);
            this->labelUserFormPosition->Name = L"labelUserFormPosition";
            this->labelUserFormPosition->Size = System::Drawing::Size(67, 19);
            this->labelUserFormPosition->TabIndex = 37;
            this->labelUserFormPosition->Text = L"Position";
            // 
            // labelUserFormPhoneError
            // 
            this->labelUserFormPhoneError->AutoSize = true;
            this->labelUserFormPhoneError->Font = (gcnew System::Drawing::Font(L"Inter", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelUserFormPhoneError->Location = System::Drawing::Point(120, 343);
            this->labelUserFormPhoneError->Name = L"labelUserFormPhoneError";
            this->labelUserFormPhoneError->Size = System::Drawing::Size(148, 15);
            this->labelUserFormPhoneError->TabIndex = 36;
            this->labelUserFormPhoneError->Text = L"+38 (XXX) XXX - XX - XX";
            this->labelUserFormPhoneError->Visible = false;
            // 
            // labelUserFormPhone
            // 
            this->labelUserFormPhone->AutoSize = true;
            this->labelUserFormPhone->Font = (gcnew System::Drawing::Font(L"Inter", 11));
            this->labelUserFormPhone->Location = System::Drawing::Point(120, 260);
            this->labelUserFormPhone->Name = L"labelUserFormPhone";
            this->labelUserFormPhone->Size = System::Drawing::Size(55, 19);
            this->labelUserFormPhone->TabIndex = 35;
            this->labelUserFormPhone->Text = L"Phone";
            // 
            // labelUserFormEmailError
            // 
            this->labelUserFormEmailError->AutoSize = true;
            this->labelUserFormEmailError->Font = (gcnew System::Drawing::Font(L"Inter", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelUserFormEmailError->Location = System::Drawing::Point(120, 221);
            this->labelUserFormEmailError->Name = L"labelUserFormEmailError";
            this->labelUserFormEmailError->Size = System::Drawing::Size(66, 15);
            this->labelUserFormEmailError->TabIndex = 34;
            this->labelUserFormEmailError->Text = L"Error email";
            this->labelUserFormEmailError->Visible = false;
            // 
            // labelUserFormEmail
            // 
            this->labelUserFormEmail->AutoSize = true;
            this->labelUserFormEmail->Font = (gcnew System::Drawing::Font(L"Inter", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelUserFormEmail->Location = System::Drawing::Point(120, 138);
            this->labelUserFormEmail->Margin = System::Windows::Forms::Padding(0);
            this->labelUserFormEmail->Name = L"labelUserFormEmail";
            this->labelUserFormEmail->Size = System::Drawing::Size(47, 19);
            this->labelUserFormEmail->TabIndex = 33;
            this->labelUserFormEmail->Text = L"Email";
            // 
            // labelUserFormNameError
            // 
            this->labelUserFormNameError->AutoSize = true;
            this->labelUserFormNameError->Font = (gcnew System::Drawing::Font(L"Inter", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelUserFormNameError->Location = System::Drawing::Point(120, 99);
            this->labelUserFormNameError->Name = L"labelUserFormNameError";
            this->labelUserFormNameError->Size = System::Drawing::Size(70, 15);
            this->labelUserFormNameError->TabIndex = 32;
            this->labelUserFormNameError->Text = L"Enter name";
            this->labelUserFormNameError->Visible = false;
            // 
            // labelUserFormName
            // 
            this->labelUserFormName->AutoSize = true;
            this->labelUserFormName->Font = (gcnew System::Drawing::Font(L"Inter", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelUserFormName->Location = System::Drawing::Point(120, 16);
            this->labelUserFormName->Margin = System::Windows::Forms::Padding(0);
            this->labelUserFormName->Name = L"labelUserFormName";
            this->labelUserFormName->Size = System::Drawing::Size(50, 19);
            this->labelUserFormName->TabIndex = 31;
            this->labelUserFormName->Text = L"Name";
            // 
            // panelNewUserSuccess
            // 
            this->panelNewUserSuccess->Controls->Add(this->labelSuccess);
            this->panelNewUserSuccess->Controls->Add(this->pictureBoxSuccess);
            this->panelNewUserSuccess->Controls->Add(this->buttonSuccessAddOneMore);
            this->panelNewUserSuccess->Controls->Add(this->buttonShowUserList);
            this->panelNewUserSuccess->Font = (gcnew System::Drawing::Font(L"Inter", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->panelNewUserSuccess->Location = System::Drawing::Point(0, 54);
            this->panelNewUserSuccess->Name = L"panelNewUserSuccess";
            this->panelNewUserSuccess->Size = System::Drawing::Size(640, 485);
            this->panelNewUserSuccess->TabIndex = 100;
            this->panelNewUserSuccess->Visible = false;
            // 
            // labelSuccess
            // 
            this->labelSuccess->AutoSize = true;
            this->labelSuccess->Font = (gcnew System::Drawing::Font(L"Inter", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelSuccess->Location = System::Drawing::Point(157, 224);
            this->labelSuccess->Name = L"labelSuccess";
            this->labelSuccess->Size = System::Drawing::Size(350, 29);
            this->labelSuccess->TabIndex = 3;
            this->labelSuccess->Text = L"New user successfully added";
            // 
            // pictureBoxSuccess
            // 
            this->pictureBoxSuccess->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBoxSuccess.Image")));
            this->pictureBoxSuccess->Location = System::Drawing::Point(268, 104);
            this->pictureBoxSuccess->Name = L"pictureBoxSuccess";
            this->pictureBoxSuccess->Size = System::Drawing::Size(104, 104);
            this->pictureBoxSuccess->TabIndex = 2;
            this->pictureBoxSuccess->TabStop = false;
            // 
            // buttonSuccessAddOneMore
            // 
            this->buttonSuccessAddOneMore->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonSuccessAddOneMore.Image")));
            this->buttonSuccessAddOneMore->Location = System::Drawing::Point(328, 297);
            this->buttonSuccessAddOneMore->Name = L"buttonSuccessAddOneMore";
            this->buttonSuccessAddOneMore->Size = System::Drawing::Size(120, 40);
            this->buttonSuccessAddOneMore->TabIndex = 1;
            this->buttonSuccessAddOneMore->TabStop = false;
            this->buttonSuccessAddOneMore->Click += gcnew System::EventHandler(this, &MyForm::buttonSuccessAddOneMore_Click);
            // 
            // buttonShowUserList
            // 
            this->buttonShowUserList->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonShowUserList.Image")));
            this->buttonShowUserList->Location = System::Drawing::Point(192, 297);
            this->buttonShowUserList->Name = L"buttonShowUserList";
            this->buttonShowUserList->Size = System::Drawing::Size(120, 40);
            this->buttonShowUserList->TabIndex = 0;
            this->buttonShowUserList->TabStop = false;
            this->buttonShowUserList->Click += gcnew System::EventHandler(this, &MyForm::buttonShowUserList_Click);
            // 
            // pictureBoxUserListLoading
            // 
            this->pictureBoxUserListLoading->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBoxUserListLoading.Image")));
            this->pictureBoxUserListLoading->Location = System::Drawing::Point(296, 861);
            this->pictureBoxUserListLoading->Name = L"pictureBoxUserListLoading";
            this->pictureBoxUserListLoading->Size = System::Drawing::Size(48, 48);
            this->pictureBoxUserListLoading->TabIndex = 9;
            this->pictureBoxUserListLoading->TabStop = false;
            this->pictureBoxUserListLoading->Visible = false;
            // 
            // pictureBoxShowMoreUsers
            // 
            this->pictureBoxShowMoreUsers->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBoxShowMoreUsers.Image")));
            this->pictureBoxShowMoreUsers->Location = System::Drawing::Point(260, 865);
            this->pictureBoxShowMoreUsers->Name = L"pictureBoxShowMoreUsers";
            this->pictureBoxShowMoreUsers->Size = System::Drawing::Size(120, 40);
            this->pictureBoxShowMoreUsers->TabIndex = 8;
            this->pictureBoxShowMoreUsers->TabStop = false;
            this->pictureBoxShowMoreUsers->Click += gcnew System::EventHandler(this, &MyForm::pictureBoxShowMoreUsers_Click);
            // 
            // pictureBoxAddUser
            // 
            this->pictureBoxAddUser->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBoxAddUser.Image")));
            this->pictureBoxAddUser->Location = System::Drawing::Point(260, 865);
            this->pictureBoxAddUser->Name = L"pictureBoxAddUser";
            this->pictureBoxAddUser->Size = System::Drawing::Size(120, 40);
            this->pictureBoxAddUser->TabIndex = 32;
            this->pictureBoxAddUser->TabStop = false;
            this->pictureBoxAddUser->Visible = false;
            this->pictureBoxAddUser->Click += gcnew System::EventHandler(this, &MyForm::pictureBoxAddUser_Click);
            // 
            // openFileDialog1
            // 
            this->openFileDialog1->FileName = L"openFileDialog1";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::ControlLightLight;
            this->ClientSize = System::Drawing::Size(640, 930);
            this->Controls->Add(this->pictureBoxAddUser);
            this->Controls->Add(this->panelUserForm);
            this->Controls->Add(this->panelNewUserSuccess);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->pictureBoxUserListLoading);
            this->Controls->Add(this->pictureBoxShowMoreUsers);
            this->Controls->Add(this->panelUserList);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->pictureBox2);
            this->Controls->Add(this->pictureBox1);
            this->Name = L"MyForm";
            this->Text = L"UserForm";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
            this->panelUserForm->ResumeLayout(false);
            this->panelUserForm->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxUploadPicture))->EndInit();
            this->panelNewUserSuccess->ResumeLayout(false);
            this->panelNewUserSuccess->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxSuccess))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->buttonSuccessAddOneMore))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->buttonShowUserList))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxUserListLoading))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxShowMoreUsers))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxAddUser))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }

#pragma endregion
        delegate void InvokeDelegateRotateImage();
        delegate void InvokeDelegateAddPictureboxToPanel(PictureBox^ picturebox);
        delegate void InvokeDelegateAddLabelToPanel(Label^ label);

        delegate void InvokeDelegateShowHidePictureLoading(bool visible);
        delegate void InvokeDelegateShowHidePictureShowMoreUsers(bool visible);
        delegate void InvokeDelegateShowHidePictureAddUser(bool visible);
        delegate void InvokeDelegateShowHidePanelNewUserSuccess(bool visible);
        delegate void InvokeDelegateShowHidePanelUserForm(bool visible);


        void ShowUsers();
        void ShowAddUser();
        void UpdateUserList();
        void CreateUserList();
        void CreatePositionsList();
        void CreateNewUser();
        void ClearUserForm();
        void Rotate();
        void RotatePicture();



        System::Void pictureBox2_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void label2_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void label1_Click(System::Object^ sender, System::EventArgs^ e);

        System::Void pictureBoxShowMoreUsers_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void pictureBoxUploadPicture_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void pictureBoxAddUser_Click(System::Object^ sender, System::EventArgs^ e);

        

        bool validationName(String^ name);
        bool validationEmail(String^ email);
        bool validationPhone(String^ phone);
        bool validationPosition();
        bool validationPhoto(String^ filePath);


        //delegate
        void AddPictureBoxToPanel(System::Windows::Forms::PictureBox^ pictureBox);
        void AddLabelToPanel(System::Windows::Forms::Label^ label);
        void ShowHidePictureLoading(bool visible);
        void ShowHidePictureShowMoreUsers(bool visible);
        void ShowHidePictureShowAddUser(bool visible);
        void ShowHidePanelNewUserSuccess(bool visible);
        void ShowHidePanelUserForm(bool visible);

        System::Void buttonSuccessAddOneMore_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void buttonShowUserList_Click(System::Object^ sender, System::EventArgs^ e);

        System::Void textboxUserFormName_Enter(System::Object^ sender, System::EventArgs^ e);
        System::Void textboxUserFormName_Leave(System::Object^ sender, System::EventArgs^ e);
        System::Void textboxUserFormName_TextChanged(System::Object^ sender, System::EventArgs^ e);

        System::Void textboxUserFormEmail_Enter(System::Object^ sender, System::EventArgs^ e);
        System::Void textboxUserFormEmail_Leave(System::Object^ sender, System::EventArgs^ e);
        System::Void textboxUserFormEmail_TextChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void textboxUserFormEmail_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
        
        System::Void textboxUserFormPhone_Enter(System::Object^ sender, System::EventArgs^ e);
        System::Void textboxUserFormPhone_Leave(System::Object^ sender, System::EventArgs^ e);
        System::Void textboxUserFormPhone_TextChanged(System::Object^ sender, System::EventArgs^ e);

        System::Void textboxUserFormPicture_Enter(System::Object^ sender, System::EventArgs^ e);
        System::Void textboxUserFormPicture_Leave(System::Object^ sender, System::EventArgs^ e);

    };
}
