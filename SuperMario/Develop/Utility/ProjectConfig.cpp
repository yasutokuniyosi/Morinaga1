#include "ProjectConfig.h"
#include "DxLib.h"

// �O���[�o���ϐ���`
LONGLONG old_time;		// �O��v���l
LONGLONG now_time;		// ���݌v���l
float delta_second;		// �P�t���[��������̎���

// �t���[�����Ԍv��
void FreamControl()
{
	// ���ݎ��Ԃ̎擾�i�ʕb�j
	now_time = GetNowHiPerformanceCount();

	// �J�n���Ԃ��猻�ݎ��Ԃ܂łɌo�߂������Ԃ��v�Z����i�ʕb�j
	// ����\���ʕb���b�ɕϊ�����
	delta_second = (float)(now_time - old_time) * 1.0e-6f;

	// �v���J�n���Ԃ��X�V����
	old_time = now_time;

	// �f�B�X�v���C�̃��t���b�V�����[�g���擾����
	float refresh_rate = (float)GetRefreshRate();

	// �P�t���[��������̎��Ԃ�1/���t���b�V�����[�g�b�𒴂�����A������
	if (delta_second > (1.0f / refresh_rate))
	{
		delta_second = (1.0f / refresh_rate);
	}
}

// 1�t���[��������̎��Ԃ��擾����
const float& GetDeltaSecond()
{
	return delta_second;
}

// �G���[���e���o�͂���
int ErrorThrow(std::string error_log)
{
	// Log.txt�ɃG���[���e��ǉ�����
	ErrorLogFmtAdd(error_log.c_str());
	return D_FAILURE;
}
