#include "InputManager.h"
#include "DxLib.h"

// �ÓI�����o�ϐ���`
InputManager* InputManager::instance = nullptr;

/// <summary>
/// �C���X�^���X�擾����
/// </summary>
/// <returns>�C���X�^���X�̃|�C���^��ԋp����</returns>
InputManager* InputManager::GetInstance()
{
	// �C���X�^���X����������Ă��Ȃ��ꍇ�A��������
	if (instance == nullptr)
	{
		instance = new InputManager();
	}

	// �C���X�^���X�̃|�C���^��ԋp����
	return instance;
}

/// <summary>
/// �C���X�^���X�폜����
/// </summary>
void InputManager::DeleteInstance()
{
	// �C���X�^���X�����݂��Ă���ꍇ�A�폜����
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

/// <summary>
/// �X�V����
/// </summary>
void InputManager::Update()
{
	// �L�[���͒l�̍X�V
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	GetHitKeyStateAll(now_key);

	// �R���g���[���[���͒l�̍X�V
	XINPUT_STATE input = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	for (int i = 0; i < D_BUTTON_MAX; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = static_cast<bool>(input.Buttons[i]);
	}
	trigger[0] = TriggerNormalization(input.LeftTrigger);
	trigger[1] = TriggerNormalization(input.RightTrigger);
	stick[0].x = StickNormalization(input.ThumbLX);
	stick[0].y = StickNormalization(input.ThumbLY);
	stick[1].x = StickNormalization(input.ThumbRX);
	stick[1].y = StickNormalization(input.ThumbRY);
}

/// <summary>
/// �L�[�{�[�h�̃L�[��������Ă��邩�m�F����
/// </summary>
/// <param name="key_code">���蓖�Ă�ꂽ�L�[</param>
/// <returns>������Ă�����Atrue</returns>
bool InputManager::GetKey(int key_code) const
{
	return CheckKeyCodeRange(key_code) && (now_key[key_code] == TRUE && old_key[key_code] == TRUE);
}

/// <summary>
/// �L�[�{�[�h�̃L�[�������ꂽ�u�Ԃ��m�F����
/// </summary>
/// <param name="key_code">���蓖�Ă�ꂽ�L�[</param>
/// <returns>�����ꂽ�u�ԂȂ�Atrue</returns>
bool InputManager::GetKeyDown(int key_code) const
{
	return CheckKeyCodeRange(key_code) && (now_key[key_code] == TRUE && old_key[key_code] == FALSE);
}

/// <summary>
/// �L�[�{�[�h�̃L�[�������ꂽ�u�Ԃ��m�F����
/// </summary>
/// <param name="key_code">���蓖�Ă�ꂽ�L�[</param>
/// <returns>�����ꂽ�u�ԂȂ�Atrue</returns>
bool InputManager::GetKeyUp(int key_code) const
{
	return CheckKeyCodeRange(key_code) && (now_key[key_code] == FALSE && old_key[key_code] == TRUE);
}

/// <summary>
/// �R���g���[���[�̃{�^����������Ă��邩�m�F����
/// </summary>
/// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
/// <returns>������Ă�����Atrue</returns>
bool InputManager::GetButton(int button) const
{
	return CheckButtonRange(button) && (now_button[button] && old_button[button]);
}

/// <summary>
/// �R���g���[���[�̃{�^���������ꂽ�u�Ԃ��m�F����
/// </summary>
/// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
/// <returns>�����ꂽ�u�ԂȂ�Atrue</returns>
bool InputManager::GetButtonDown(int button) const
{
	return CheckButtonRange(button) && (now_button[button] && !old_button[button]);
}

/// <summary>
/// �R���g���[���[�̃{�^���������ꂽ�u�Ԃ��m�F����
/// </summary>
/// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
/// <returns>�����ꂽ�u�ԂȂ�Atrue</returns>
bool InputManager::GetButtonUp(int button) const
{
	return CheckButtonRange(button) && (!now_button[button] && old_button[button]);
}

/// <summary>
/// ���g���K�[���͏�Ԏ擾
/// </summary>
/// <returns>���g���K�[���͏��(0.0f�`1.0f)</returns>
float InputManager::GetLeftTrigger() const
{
	return trigger[0];
}

/// <summary>
/// �E�g���K�[���͏�Ԏ擾
/// </summary>
/// <returns>�E�g���K�[���͏��(0.0f�`1.0f)</returns>
float InputManager::GetRightTrigger() const
{
	return trigger[1];
}

/// <summary>
/// ���X�e�B�b�N���͏�Ԏ擾
/// </summary>
/// <returns>���X�e�B�b�N���͏��(-1.0f�`1.0f)</returns>
Vector2D InputManager::GetLeftStick() const
{
	return stick[0];
}

/// <summary>
/// �E�X�e�B�b�N���͏�Ԏ擾
/// </summary>
/// <returns>�E�X�e�B�b�N���͏��(-1.0f�`1.0f)</returns>
Vector2D InputManager::GetRightStick() const
{
	return stick[1];
}

/// <summary>
/// �g���K�[���͒l�̐��K��
/// </summary>
/// <param name="value">�g���K�[���͒l</param>
/// <returns>���͒l�𐳋K�������l</returns>
float InputManager::TriggerNormalization(unsigned char value)
{
	float result = 0.0f;

	result = (float)value / (float)UCHAR_MAX;

	return result;
}

/// <summary>
/// �X�e�B�b�N���͒l�̐��K��
/// </summary>
/// <param name="value">�X�e�B�b�N���͒l</param>
/// <returns>���͒l�𐳋K�������l</returns>
float InputManager::StickNormalization(short value)
{
	float result = 0.0f;

	if (value >= 0)
	{
		result = (float)value / (float)SHRT_MAX;
	}
	else
	{
		result = -((float)value / (float)SHRT_MIN);
	}

	return result;
}

/// <summary>
/// ���蓖�ăL�[�R�[�h�͈͓��`�F�b�N����
/// </summary>
/// <param name="button">���蓖�Ă�ꂽ�L�[�R�[�h</param>
/// <returns>�͈͓��Ȃ�Atrue</returns>
bool InputManager::CheckKeyCodeRange(int key_code) const
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}

/// <summary>
/// ���蓖�ă{�^���͈͓��`�F�b�N����
/// </summary>
/// <param name="buttton">���蓖�Ă�ꂽ�{�^��</param>
/// <returns>�͈͓��Ȃ�Atrue</returns>
bool InputManager::CheckButtonRange(int button) const
{
	return (0 <= button && button < D_BUTTON_MAX);
}
