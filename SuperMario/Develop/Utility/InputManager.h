#pragma once

#include "Vector2D.h"

// �}�N����`
#define	D_KEYCODE_MAX	(256)		// �L�[�{�[�h���͒l�ő吔
#define D_BUTTON_MAX	(16)		// �R���g���[���[�̓��̓{�^���ő吔

/// <summary>
/// ���͊Ǘ��N���X�iSingleton�j
/// </summary>
class InputManager
{
private:
	// ���N���X�̃|�C���^�i���̂��A�h���X�̐�ŕۗL�j
	static InputManager* instance;

	// �L�[���͏��
	char now_key[D_KEYCODE_MAX];		// ���݂̓��͒l
	char old_key[D_KEYCODE_MAX];		// �O��̓��͒l

	// �R���g���[���[���͏��
	bool now_button[D_BUTTON_MAX];		// ���݂̃{�^�����͒l
	bool old_button[D_BUTTON_MAX];		// �O��̃{�^�����͒l
	float trigger[2];					// �g���K�[���͒l�i0.0f�`1.0f�j
	Vector2D stick[2];					// �X�e�B�b�N���͒l�i-1.0f�`1.0f�j

private:
	// �N���X�̎��̂������o�֐����ł��������ł��Ȃ��悤�ɂ���
	InputManager() = default;
	// �R�s�[�K�[�h
	InputManager(const InputManager& v) = delete;
	InputManager& operator = (const InputManager& v) = delete;
	// ~�R�s�[�K�[�h

public:
	~InputManager() = default;

public:
	/// <summary>
	/// �C���X�^���X�擾����
	/// </summary>
	/// <returns>�C���X�^���X�̃|�C���^��ԋp����</returns>
	static InputManager* GetInstance();

	/// <summary>
	/// �C���X�^���X�폜����
	/// </summary>
	static void DeleteInstance();

public:
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

public:
	// ���͏�Ԃ̎擾

	/// <summary>
	/// �L�[�{�[�h�̃L�[��������Ă��邩�m�F����
	/// </summary>
	/// <param name="key_code">���蓖�Ă�ꂽ�L�[</param>
	/// <returns>������Ă�����Atrue</returns>
	bool GetKey(int key_code) const;

	/// <summary>
	/// �L�[�{�[�h�̃L�[�������ꂽ�u�Ԃ��m�F����
	/// </summary>
	/// <param name="key_code">���蓖�Ă�ꂽ�L�[</param>
	/// <returns>�����ꂽ�u�ԂȂ�Atrue</returns>
	bool GetKeyDown(int key_code) const;

	/// <summary>
	/// �L�[�{�[�h�̃L�[�������ꂽ�u�Ԃ��m�F����
	/// </summary>
	/// <param name="key_code">���蓖�Ă�ꂽ�L�[</param>
	/// <returns>�����ꂽ�u�ԂȂ�Atrue</returns>
	bool GetKeyUp(int key_code) const;

	/// <summary>
	/// �R���g���[���[�̃{�^����������Ă��邩�m�F����
	/// </summary>
	/// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
	/// <returns>������Ă�����Atrue</returns>
	bool GetButton(int button) const;
	/// <summary>
	/// �R���g���[���[�̃{�^���������ꂽ�u�Ԃ��m�F����
	/// </summary>
	/// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
	/// <returns>�����ꂽ�u�ԂȂ�Atrue</returns>
	bool GetButtonDown(int button) const;
	/// <summary>
	/// �R���g���[���[�̃{�^���������ꂽ�u�Ԃ��m�F����
	/// </summary>
	/// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
	/// <returns>�����ꂽ�u�ԂȂ�Atrue</returns>
	bool GetButtonUp(int button) const;

	/// <summary>
	/// ���g���K�[���͏�Ԏ擾
	/// </summary>
	/// <returns>���g���K�[���͏��(0.0f�`1.0f)</returns>
	float GetLeftTrigger() const;

	/// <summary>
	/// �E�g���K�[���͏�Ԏ擾
	/// </summary>
	/// <returns>�E�g���K�[���͏��(0.0f�`1.0f)</returns>
	float GetRightTrigger() const;

	/// <summary>
	/// ���X�e�B�b�N���͏�Ԏ擾
	/// </summary>
	/// <returns>���X�e�B�b�N���͏��(-1.0f�`1.0f)</returns>
	Vector2D GetLeftStick() const;

	/// <summary>
	/// �E�X�e�B�b�N���͏�Ԏ擾
	/// </summary>
	/// <returns>�E�X�e�B�b�N���͏��(-1.0f�`1.0f)</returns>
	Vector2D GetRightStick() const;

private:
	/// <summary>
	/// �g���K�[���͒l�̐��K��
	/// </summary>
	/// <param name="value">�g���K�[���͒l</param>
	/// <returns>���͒l�𐳋K�������l</returns>
	float TriggerNormalization(unsigned char value);

	/// <summary>
	/// �X�e�B�b�N���͒l�̐��K��
	/// </summary>
	/// <param name="value">�X�e�B�b�N���͒l</param>
	/// <returns>���͒l�𐳋K�������l</returns>
	float StickNormalization(short value);

	/// <summary>
	/// ���蓖�ăL�[�R�[�h�͈͓��`�F�b�N����
	/// </summary>
	/// <param name="key_code">���蓖�Ă�ꂽ�L�[�R�[�h</param>
	/// <returns>�͈͓��Ȃ�Atrue</returns>
	bool CheckKeyCodeRange(int key_code) const;

	/// <summary>
	/// ���蓖�ă{�^���͈͓��`�F�b�N����
	/// </summary>
	/// <param name="buttton">���蓖�Ă�ꂽ�{�^��</param>
	/// <returns>�͈͓��Ȃ�Atrue</returns>
	bool CheckButtonRange(int button) const;

};