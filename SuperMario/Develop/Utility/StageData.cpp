#include "StageData.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "../Objects/GameObjectBase.h"

StageData* StageData::instance = nullptr;

/// <summary>
/// �X�e�[�W�f�[�^��ǂݍ���
/// </summary>
void StageData::Load()
{
	// �ǂݍ��ރt�@�C����
	//std::string file_name = "Resource/Map/StageMap.csv";

	// �t�@�C���X�g���[��
	//std::ifstream ifs;
	// �w��t�@�C����ǂݍ���
	//ifs.open(file_name, std::ios::in);

	// �G���[�`�F�b�N
	//if (ifs.fail())
	//{
	//	throw (file_name + "���J���܂���\n");
	//}

	//// �f�[�^��������
	//std::vector<ePanelID> init_data(28, ePanelID::NONE);
	//data = std::vector<std::vector<ePanelID>>(31, init_data);

	//// �ǂ̃f�[�^���쐬
	//std::string line;
	//while (std::getline(ifs, line))
	//{
	//	// �P�s�ǂݍ��񂾃f�[�^���X�g�����O�X�g���[���ɕϊ�
	//	std::stringstream line_stream = std::stringstream(line);

	//	// �������擾
	//	std::string mode;
	//	std::getline(line_stream, mode, ',');

	//	// id�̏����l
	//	ePanelID id = ePanelID::WALL;

	//	// �ǂ̓o�^
	//	switch ((*mode.c_str()))
	//	{
	//	case 'G':
	//		id = ePanelID::GATE;	// id��WALL�ɂ���
	//	case '#':
	//	{
	//		// �}���J�n�n�_�Ƒ}�������擾
	//		std::string line_data;
	//		std::getline(line_stream, line_data, ',');
	//		int x_size = std::stoi(line_data);

	//		std::getline(line_stream, line_data, ',');
	//		int y_size = std::stoi(line_data);

	//		std::getline(line_stream, line_data, ',');
	//		int x_start = std::stoi(line_data) - 1;

	//		std::getline(line_stream, line_data, ',');
	//		int y_start = std::stoi(line_data) - 1;

	//		// �ǃf�[�^��o�^
	//		if (x_size == 1)
	//		{
	//			for (int i = y_start; i < (y_start + y_size); i++)
	//			{
	//				data[i][x_start] = id;
	//			}
	//		}
	//		else
	//		{
	//			for (int i = x_start; i < (x_start + x_size); i++)
	//			{
	//				data[y_start][i] = id;
	//			}
	//		}
	//	}
	//	break;

	//	case 'B':
	//	{
	//		// �}���n�_���擾
	//		std::string line_data;
	//		std::getline(line_stream, line_data, ',');
	//		int x_start = std::stoi(line_data) - 1;

	//		std::getline(line_stream, line_data, ',');
	//		int y_start = std::stoi(line_data) - 1;

	//		// ����H��o�^
	//		data[y_start][x_start] = ePanelID::BRANCH;
	//	}
	//	break;

	//	default:
	//		break;
	//	}
	//}
}

/// <summary>
/// �S�Ẵp�l�������擾����
/// </summary>
/// <returns>�S�Ẵp�l�����</returns>
const std::vector<std::vector<ePanelID>> StageData::GetAll()
{
	if (instance == nullptr)
	{
		// �I�u�W�F�N�g�̍쐬
		instance = new StageData();
		instance->Load();
	}

	return instance->data;
}

/// <summary>
/// �אڂ���p�l�������擾
/// </summary>
/// <param name="location">���ݍ��W</param>
/// <returns>�אڂ���p�l�����</returns>
const std::map<eAdjacentDirection, ePanelID> StageData::GetAdjacentPanelData(const Vector2D& location)
{
	if (instance == nullptr)
	{
		// �I�u�W�F�N�g�̍쐬
		instance = new StageData();
		instance->Load();
	}

	// �߂�l�ƂȂ�f�[�^���쐬����
	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::NONE },
		{ eAdjacentDirection::DOWN, ePanelID::NONE },
		{ eAdjacentDirection::LEFT, ePanelID::NONE },
		{ eAdjacentDirection::RIGHT, ePanelID::NONE }
	};

	// ���W��Y���ɕϊ�
	int i = 0, j = 0;
	ConvertToIndex(location, i, j);

	// �͈̓`�F�b�N
	if ((0 <= i) || (i < instance->data.size()))
	{
		// LEFT�f�[�^�쐬
		if (0 <= (j - 1))
		{
			ret[eAdjacentDirection::LEFT] = instance->data[i][j - 1];
		}

		// RIGHT�f�[�^�쐬
		if ((j + 1) < instance->data[i].size())
		{
			ret[eAdjacentDirection::RIGHT] = instance->data[i][j + 1];
		}
	}

	// �͈̓`�F�b�N
	if ((0 <= j) || (j < instance->data[0].size()))
	{
		// UP�f�[�^�쐬
		if (0 <= (i - 1))
		{
			ret[eAdjacentDirection::UP] = instance->data[i - 1][j];
		}

		// DOWN�f�[�^�쐬
		if ((i + 1) < instance->data.size())
		{
			ret[eAdjacentDirection::DOWN] = instance->data[i + 1][j];
		}
	}

	return ret;
}

/// <summary>
/// ���ݍ��W�̃p�l�������擾����
/// </summary>
/// <param name="location">���ݍ��W</param>
/// <returns>�p�l�����</returns>
const ePanelID StageData::GetPanelData(const Vector2D& location)
{
	if (instance == nullptr)
	{
		// �I�u�W�F�N�g�̍쐬
		instance = new StageData();
		instance->Load();
	}

	// ���W��Y���ɕϊ�
	int i = 0, j = 0;
	ConvertToIndex(location, i, j);

	// i��j�͈̔̓`�F�b�N
	if ((i < 0) || (j < 0) || (instance->data.size() <= i) || (instance->data[0].size() <= j))
	{
		return ePanelID::NONE;
	}

	return instance->data[i][j];
}

/// <summary>
/// ���W����Y���ɕϊ�����
/// </summary>
/// <param name="location">���W���</param>
/// <param name="i">�ϊ���̓Y��</param>
/// <param name="j">�ϊ���̓Y��</param>
void StageData::ConvertToIndex(const Vector2D& location, int& i, int& j)
{
	j = static_cast<int>(location.x / D_OBJECT_SIZE);
	i = static_cast<int>(location.y / D_OBJECT_SIZE);
}