#include "MyForm.h"

void UserForm::MyForm::ShowUsers()
{
    UpdateUserList();

    pictureBox2->BackColor = System::Drawing::Color::FromArgb(0xF0, 0xF0, 0xF0);
    label2->BackColor = System::Drawing::Color::FromArgb(0xF0, 0xF0, 0xF0);

    pictureBox1->BackColor = System::Drawing::Color::White;
    label1->BackColor = System::Drawing::Color::White;

    label3->Text = "Users list";

    panelUserList->Visible = true;
    panelUserForm->Visible = false;

    pictureBoxAddUser->Visible = false;

    if (restApi->getPage() == page && restApi->getPage() != 0)
    {
        pictureBoxShowMoreUsers->Visible = false;

    }
    else
    {
        pictureBoxShowMoreUsers->Visible = true;

    }
}

void UserForm::MyForm::ShowAddUser()
{
    if (update)
    {
        ClearUserForm();
    }
    pictureBox1->BackColor = System::Drawing::Color::FromArgb(0xF0, 0xF0, 0xF0);
    label1->BackColor = System::Drawing::Color::FromArgb(0xF0, 0xF0, 0xF0);

    label3->Text = "Add user";
    pictureBox2->BackColor = System::Drawing::Color::White;
    label2->BackColor = System::Drawing::Color::White;

    panelUserList->Visible = false;
    panelUserForm->Visible = true;

    pictureBoxAddUser->Visible = true;
    pictureBoxShowMoreUsers->Visible = false;
}

void UserForm::MyForm::UpdateUserList()
{
    if (update)
    {
        ClearUserForm();

        panelNewUserSuccess->Visible = false;

        update = false;

        this->Size = System::Drawing::Size(656, 969);

        for (int i = panelUserList->Controls->Count - 1; i >= 0; i--)
        {
            Control^ control = panelUserList->Controls[i];
            panelUserList->Controls->RemoveAt(i);
            delete control;
        }

        pics->Clear();
        names->Clear();
        emails->Clear();
        positionsLabel->Clear();
        phones->Clear();

        page = 1;
        indexPaddingPicture = -84;
        myThreadApi = gcnew Thread(gcnew ThreadStart(this, &MyForm::CreateUserList));
        myThreadApi->Start();

    }
}

void UserForm::MyForm::CreateUserList()
{
    auto users = restApi->getUsers(page, countUsersInRequest);

    if (!users.empty())
    {
        for (int i = 0; i < users.size(); i++)
        {
            int indexList = i + ((countUsersInRequest * page) - countUsersInRequest);

            int newY = 84 + indexPaddingPicture - panelUserList->VerticalScroll->Value;
            //AVATAR
            String^ link = gcnew String(users[i].getPictureLink().c_str());
            PictureBox^ pictureBox = gcnew PictureBox();
            pictureBox->ErrorImage = errorImage;
            pictureBox->ImageLocation = link;
            pictureBox->Location = System::Drawing::Point(24, newY);
            pictureBox->SizeMode = PictureBoxSizeMode::Zoom;
            pictureBox->Size = Drawing::Size(84, 84);
            pictureBox->Visible = true;
            pics->Add(pictureBox);
            this->panelUserList->BeginInvoke(gcnew InvokeDelegateAddPictureboxToPanel(this, &MyForm::AddPictureBoxToPanel), pics[indexList]);
            
            //Border
            PictureBox^ border = gcnew PictureBox();
            border->Location = System::Drawing::Point(24, newY+100);
            border->BackColor = System::Drawing::Color::Silver;
            border->Size = Drawing::Size(592, 1);
            border->Visible = true;
            this->panelUserList->BeginInvoke(gcnew InvokeDelegateAddPictureboxToPanel(this, &MyForm::AddPictureBoxToPanel), border);

            //Name
            String^ name = gcnew String(users[i].getName().c_str());
            Label^ l_name = gcnew Label();
            l_name->Font = (gcnew System::Drawing::Font(L"Inter", 13.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            l_name->Location = System::Drawing::Point(124, newY);
            l_name->Size = System::Drawing::Size(200, 22);
            l_name->TabIndex = 4;
            l_name->Text = name;
            names->Add(l_name);
            this->panelUserList->BeginInvoke(gcnew InvokeDelegateAddLabelToPanel(this, &MyForm::AddLabelToPanel), names[indexList]);




            //Position
            String^ position = gcnew String(users[i].getPosition().c_str());
            Label^ l_position = gcnew Label();
            l_position->Font = (gcnew System::Drawing::Font(L"Inter", 10.5, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            l_position->Location = System::Drawing::Point(124, newY + 28);
            l_position->Size = System::Drawing::Size(200, 17);
            l_position->TabIndex = 4;
            l_position->Text = position;
            positionsLabel->Add(l_position);
            this->panelUserList->BeginInvoke(gcnew InvokeDelegateAddLabelToPanel(this, &MyForm::AddLabelToPanel), positionsLabel[indexList]);



            //Email
            String^ email = gcnew String(users[i].getEmail().c_str());
            Label^ l_email = gcnew Label();
            l_email->Font = (gcnew System::Drawing::Font(L"Inter", 10.5, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            l_email->Location = System::Drawing::Point(124, newY + 49);
            l_email->Size = System::Drawing::Size(200, 17);
            l_email->TabIndex = 4;
            l_email->Text = email;
            emails->Add(l_email);
            this->panelUserList->BeginInvoke(gcnew InvokeDelegateAddLabelToPanel(this, &MyForm::AddLabelToPanel), emails[indexList]);

            //Phone
            String^ phoneNumber = gcnew String(users[i].getPhoneNumber().c_str());
            Label^ l_phoneNumber = gcnew Label();
            l_phoneNumber->Font = (gcnew System::Drawing::Font(L"Inter", 10.5, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            l_phoneNumber->Location = System::Drawing::Point(124, newY + 70);
            l_phoneNumber->Size = System::Drawing::Size(200, 17);
            l_phoneNumber->TabIndex = 4;
            l_phoneNumber->Text = phoneNumber;
            phones->Add(l_phoneNumber);
            this->panelUserList->BeginInvoke(gcnew InvokeDelegateAddLabelToPanel(this, &MyForm::AddLabelToPanel), phones[indexList]);

            indexPaddingPicture += 84 + 33;
        }
    }
    else
    {
        page--;
    }


    try {
        myThreadRotate->Abort();
    }
    catch (...) {}

    pictureBoxUserListLoading->BeginInvoke(gcnew InvokeDelegateShowHidePictureLoading(this, &MyForm::ShowHidePictureLoading), false);

    if (restApi->getPage() == page && restApi->getPage() != 0)
    {
        pictureBoxShowMoreUsers->BeginInvoke(gcnew InvokeDelegateShowHidePictureShowMoreUsers(this, &MyForm::ShowHidePictureShowMoreUsers), false);

    }
    else
    {
        pictureBoxShowMoreUsers->BeginInvoke(gcnew InvokeDelegateShowHidePictureShowMoreUsers(this, &MyForm::ShowHidePictureShowMoreUsers), true);

    }
}

void UserForm::MyForm::CreatePositionsList()
{
    auto positions = restApi->getPositions();
    int a = 0;

    for (size_t i = 0; i < positions.size(); i++)
    {
        String^ name = gcnew String(positions[i].c_str());

        RadioButton^ radioButton = gcnew RadioButton();
        radioButton->Font = (gcnew System::Drawing::Font(L"Inter", 19.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        radioButton->Location = System::Drawing::Point(120, 417 + a);
        radioButton->Size = Drawing::Size(400, 36);
        radioButton->Text = name;
        radioButton->Visible = true;
        radioButton->AutoSize = true;
        radioButtons->Add(radioButton);
        this->panelUserForm->Controls->Add(radioButtons[i]);
        a += 36;
    }
}

void UserForm::MyForm::CreateNewUser()
{
    std::string name = msclr::interop::marshal_as<std::string>(textboxUserFormName->Text);
    std::string email = msclr::interop::marshal_as<std::string>(textboxUserFormEmail->Text);
    std::string phone = msclr::interop::marshal_as<std::string>(textboxUserFormPhone->Text);

    int position_id = 0;
    for (size_t i = 0; i < radioButtons->Count; i++)
    {
        if (radioButtons[i]->Checked)
        {
            position_id = i + 1;
        }
    }

    std::string position = std::to_string(position_id);
    std::string photo = msclr::interop::marshal_as<std::string>(textboxUserFormPicture->Text);
    User* user = new User(name, email, position, phone, photo);


    if (restApi->postNewUser(*(user)))
    {

        panelNewUserSuccess->BeginInvoke(gcnew InvokeDelegateShowHidePanelNewUserSuccess(this, &MyForm::ShowHidePanelNewUserSuccess), true);
        panelUserForm->BeginInvoke(gcnew InvokeDelegateShowHidePanelUserForm(this, &MyForm::ShowHidePanelUserForm), false);

        this->Size = System::Drawing::Size(656, 580);

        update = true;
    }


    try {
        myThreadRotate->Abort();
    }
    catch (...) {}

    pictureBoxUserListLoading->BeginInvoke(gcnew InvokeDelegateShowHidePictureLoading(this, &MyForm::ShowHidePictureLoading), false);

    if (restApi->getPage() == page && restApi->getPage() != 0)
    {
        pictureBoxAddUser->BeginInvoke(gcnew InvokeDelegateShowHidePictureAddUser(this, &MyForm::ShowHidePictureShowAddUser), false);

    }
    else
    {
        pictureBoxAddUser->BeginInvoke(gcnew InvokeDelegateShowHidePictureAddUser(this, &MyForm::ShowHidePictureShowAddUser), true);

    }

}

void UserForm::MyForm::ClearUserForm()
{
    textboxUserFormPicture->Text = L"Upload photo";
    textboxUserFormPicture->ForeColor = System::Drawing::SystemColors::GrayText;

    textboxUserFormPhone->Text = L"Phone";
    textboxUserFormPhone->ForeColor = System::Drawing::SystemColors::GrayText;

    textboxUserFormEmail->Text = L"Email";
    textboxUserFormEmail->ForeColor = System::Drawing::SystemColors::GrayText;

    textboxUserFormName->Text = L"Name";
    textboxUserFormName->ForeColor = System::Drawing::SystemColors::GrayText;


    for (size_t i = 0; i < radioButtons->Count; i++)
    {
        radioButtons[i]->Checked = false;

    }
}

void UserForm::MyForm::Rotate()
{
    pictureBoxUserListLoading->Image->RotateFlip(System::Drawing::RotateFlipType::Rotate90FlipNone);
    pictureBoxUserListLoading->Invalidate();
}

void UserForm::MyForm::RotatePicture()
{
    pictureBoxUserListLoading->BeginInvoke(gcnew InvokeDelegateShowHidePictureLoading(this, &MyForm::ShowHidePictureLoading), true);

    while (true) {
        pictureBoxUserListLoading->BeginInvoke(gcnew InvokeDelegateRotateImage(this, &MyForm::Rotate));
        Sleep(100);
    }
}

System::Void UserForm::MyForm::pictureBox2_Click(System::Object^ sender, System::EventArgs^ e)
{
    ShowAddUser();
}

System::Void UserForm::MyForm::pictureBox1_Click(System::Object^ sender, System::EventArgs^ e)
{
    ShowUsers();
}

System::Void UserForm::MyForm::label2_Click(System::Object^ sender, System::EventArgs^ e)
{
    ShowAddUser();
}

System::Void UserForm::MyForm::label1_Click(System::Object^ sender, System::EventArgs^ e)
{
    ShowUsers();
}

System::Void UserForm::MyForm::pictureBoxShowMoreUsers_Click(System::Object^ sender, System::EventArgs^ e)
{
    page++;

    pictureBoxUserListLoading->Visible = true;
    pictureBoxShowMoreUsers->Visible = false;

    myThreadApi = gcnew Thread(gcnew ThreadStart(this, &MyForm::CreateUserList));
    myThreadApi->Start();

    myThreadRotate = gcnew Thread(gcnew ThreadStart(this, &MyForm::RotatePicture));
    myThreadRotate->Start();
}

System::Void UserForm::MyForm::pictureBoxUploadPicture_Click(System::Object^ sender, System::EventArgs^ e)
{
    String^ Filename = "";
    openFileDialog1->InitialDirectory = Path::GetDirectoryName(Application::ExecutablePath);
    openFileDialog1->Filter = "Image Files|*.jpeg;*.jpg|Все файлы|*.*";
    openFileDialog1->ShowDialog();
    Filename = openFileDialog1->FileName;
    validationPhoto(Filename);
    textboxUserFormPicture->Text = Filename;
}

System::Void UserForm::MyForm::pictureBoxAddUser_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (validationName(textboxUserFormName->Text) &&
        validationEmail(textboxUserFormEmail->Text) &&
        validationPhone(textboxUserFormPhone->Text) &&
        validationPosition() &&
        validationPhoto(textboxUserFormPicture->Text))
    {
        pictureBoxUserListLoading->Visible = true;
        pictureBoxAddUser->Visible = false;

        myThreadApi = gcnew Thread(gcnew ThreadStart(this, &MyForm::CreateNewUser));
        myThreadApi->Start();
        myThreadRotate = gcnew Thread(gcnew ThreadStart(this, &MyForm::RotatePicture));
        myThreadRotate->Start();
    }
}

System::Void UserForm::MyForm::textboxUserFormName_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
    validationName(textboxUserFormName->Text);
}

System::Void UserForm::MyForm::textboxUserFormEmail_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
    validationEmail(textboxUserFormEmail->Text);
}

System::Void UserForm::MyForm::textboxUserFormPhone_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
    validationPhone(textboxUserFormPhone->Text);
}

bool UserForm::MyForm::validationName(String^ name)
{
    if (name->Length > 60 || name->Length < 2 || textboxUserFormName->Text == L"Name")
    {
        labelUserFormNameError->Text = "Name should be 2-60 characters";
        labelUserFormNameError->Visible = true;
        labelUserFormNameError->ForeColor = System::Drawing::Color::Red;
        return 0;
    }
    labelUserFormNameError->Visible = false;
    return 1;
}

bool UserForm::MyForm::validationEmail(String^ email)
{
    String^ pattern = R"(^(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])$)";

    Regex^ regex = gcnew Regex(pattern);

    if (!regex->IsMatch(email) || email->Length > 100 || email->Length < 2)
    {

        labelUserFormEmailError->Text = "Error email";
        labelUserFormEmailError->Visible = true;
        labelUserFormEmailError->ForeColor = System::Drawing::Color::Red;
        return 0;
    }
    else
    {
        labelUserFormEmailError->Visible = false;
        return 1;
    }
}

bool UserForm::MyForm::validationPhone(String^ phone)
{
    String^ pattern = "^(\\+380)\\d{9}$";

    Regex^ regex = gcnew Regex(pattern);

    if (!regex->IsMatch(phone))
    {

        labelUserFormPhoneError->Text = "+38 (XXX) XXX - XX - XX";
        labelUserFormPhoneError->Visible = true;
        labelUserFormPhoneError->ForeColor = System::Drawing::Color::Red;
        return 0;
    }
    else
    {
        labelUserFormPhoneError->Visible = false;
        return 1;
    }
}

bool UserForm::MyForm::validationPosition()
{
    for (size_t i = 0; i < radioButtons->Count; i++)
    {
        if (radioButtons[i]->Checked)
        {
            labelUserFormPositionError->Visible = false;
            return 1;
        }
    }
    labelUserFormPositionError->Text = "Choose position";
    labelUserFormPositionError->Visible = true;
    labelUserFormPositionError->ForeColor = System::Drawing::Color::Red;
    return 0;
}

bool UserForm::MyForm::validationPhoto(String^ filePath)
{
    if (File::Exists(filePath))
    {

        Image^ image = Image::FromFile(filePath);


        if (Path::GetExtension(filePath)->Equals(".jpg", StringComparison::InvariantCultureIgnoreCase) ||
            Path::GetExtension(filePath)->Equals(".jpeg", StringComparison::InvariantCultureIgnoreCase))
        {

            if (image->Width >= 70 && image->Height >= 70)
            {

                FileInfo^ fileInfo = gcnew FileInfo(filePath);
                if (fileInfo->Length <= 5 * 1024 * 1024)
                {
                    this->labelUserFormPhotoError->Visible = false;
                    return 1;
                }
                else
                {
                    this->labelUserFormPhotoError->Visible = true;
                    this->labelUserFormPhotoError->Text = "The file size increases by 5 MB.";
                    this->labelUserFormPhotoError->ForeColor = System::Drawing::Color::Red;
                    return 0;
                }
            }
            else
            {
                this->labelUserFormPhotoError->Visible = true;
                this->labelUserFormPhotoError->Text = "Image resolution must be at least 70x70 pixels.";
                this->labelUserFormPhotoError->ForeColor = System::Drawing::Color::Red;
                return 0;
            }
        }
        else
        {
            this->labelUserFormPhotoError->Visible = true;
            this->labelUserFormPhotoError->Text = "The file format must be jpg/jpeg.";
            this->labelUserFormPhotoError->ForeColor = System::Drawing::Color::Red;
            return 0;
        }
    }
    else
    {
        this->labelUserFormPhotoError->Visible = true;
        this->labelUserFormPhotoError->Text = "The file does not exist at the specified path.";
        this->labelUserFormPhotoError->ForeColor = System::Drawing::Color::Red;
        return 0;
    }
}

void UserForm::MyForm::AddPictureBoxToPanel(System::Windows::Forms::PictureBox^ pictureBox)
{
    panelUserList->Controls->Add(pictureBox);
}

void UserForm::MyForm::AddLabelToPanel(System::Windows::Forms::Label^ label)
{
    panelUserList->Controls->Add(label);
}

void UserForm::MyForm::ShowHidePictureLoading(bool visible)
{
    pictureBoxUserListLoading->Visible = visible;
}

void UserForm::MyForm::ShowHidePictureShowMoreUsers(bool visible)
{
    pictureBoxShowMoreUsers->Visible = visible;
}

void UserForm::MyForm::ShowHidePictureShowAddUser(bool visible)
{
    pictureBoxAddUser->Visible = visible;
}

void UserForm::MyForm::ShowHidePanelNewUserSuccess(bool visible)
{
    panelNewUserSuccess->Visible = visible;
}

void UserForm::MyForm::ShowHidePanelUserForm(bool visible)
{
    panelUserForm->Visible = visible;
}

System::Void UserForm::MyForm::buttonSuccessAddOneMore_Click(System::Object^ sender, System::EventArgs^ e)
{
    ClearUserForm();
    panelNewUserSuccess->Visible = false;
    panelUserForm->Visible = true;

    this->Size = System::Drawing::Size(656, 969);
}

System::Void UserForm::MyForm::buttonShowUserList_Click(System::Object^ sender, System::EventArgs^ e)
{
    ShowUsers();
}

System::Void UserForm::MyForm::textboxUserFormName_Enter(System::Object^ sender, System::EventArgs^ e)
{
    if (textboxUserFormName->Text == L"Name") {
        textboxUserFormName->Text = L"";
        textboxUserFormName->ForeColor = System::Drawing::SystemColors::WindowText;
    }
}

System::Void UserForm::MyForm::textboxUserFormName_Leave(System::Object^ sender, System::EventArgs^ e)
{
    if (textboxUserFormName->Text == L"") {
        textboxUserFormName->Text = L"Name";
        textboxUserFormName->ForeColor = System::Drawing::SystemColors::GrayText;
    }
}

System::Void UserForm::MyForm::textboxUserFormEmail_Enter(System::Object^ sender, System::EventArgs^ e)
{
    if (textboxUserFormEmail->Text == L"Email") {
        textboxUserFormEmail->Text = L"";
        textboxUserFormEmail->ForeColor = System::Drawing::SystemColors::WindowText;
    }
}

System::Void UserForm::MyForm::textboxUserFormEmail_Leave(System::Object^ sender, System::EventArgs^ e)
{
    if (textboxUserFormEmail->Text == L"") {
        textboxUserFormEmail->Text = L"Email";
        textboxUserFormEmail->ForeColor = System::Drawing::SystemColors::GrayText;
    }
}

System::Void UserForm::MyForm::textboxUserFormEmail_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
    if (Char::IsLetter(e->KeyChar) && Char::IsUpper(e->KeyChar)) {
        e->KeyChar = Char::ToLower(e->KeyChar);
    }
}

System::Void UserForm::MyForm::textboxUserFormPhone_Enter(System::Object^ sender, System::EventArgs^ e)
{
    if (textboxUserFormPhone->Text == L"Phone") {
        textboxUserFormPhone->Text = L"";
        textboxUserFormPhone->ForeColor = System::Drawing::SystemColors::WindowText;
    }
}

System::Void UserForm::MyForm::textboxUserFormPhone_Leave(System::Object^ sender, System::EventArgs^ e)
{
    if (textboxUserFormPhone->Text == L"") {
        textboxUserFormPhone->Text = L"Phone";
        textboxUserFormPhone->ForeColor = System::Drawing::SystemColors::GrayText;
    }
}

System::Void UserForm::MyForm::textboxUserFormPicture_Enter(System::Object^ sender, System::EventArgs^ e)
{
    if (textboxUserFormPicture->Text == L"Upload photo") {
        textboxUserFormPicture->Text = L"";
        textboxUserFormPicture->ForeColor = System::Drawing::SystemColors::WindowText;
    }
}

System::Void UserForm::MyForm::textboxUserFormPicture_Leave(System::Object^ sender, System::EventArgs^ e)
{
    if (textboxUserFormPicture->Text == L"") {
        textboxUserFormPicture->Text = L"Upload photo";
        textboxUserFormPicture->ForeColor = System::Drawing::SystemColors::GrayText;
    };
}
