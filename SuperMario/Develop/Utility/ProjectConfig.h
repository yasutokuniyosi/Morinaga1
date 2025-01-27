#pragma once

#include <string>

/**********************************************************
* �}�N����`
***********************************************************/
#define	D_SUCCESS		(0)		// ����
#define	D_FAILURE		(-1)	// ���s

#define D_WIN_MAX_X		(640)	// �X�N���[���T�C�Y�i���j
#define D_WIN_MAX_Y		(480)	// �X�N���[���T�C�Y�i�����j
#define D_COLOR_BIT		(32)	// �J���[�r�b�g

/**********************************************************
* �v���g�^�C�v�錾
***********************************************************/
/// <summary>
/// �t���[������
/// </summary>
void FreamControl();

/// <summary>
/// 1�t���[��������̎��Ԃ��擾����
/// </summary>
/// <returns>1�t���[��������̎���</returns>
const float& GetDeltaSecond();

/// <summary>
/// �G���[���e���o�͂���
/// </summary>
/// <returns>�I����Ԃ̒l</returns>
int ErrorThrow(std::string error_log);
