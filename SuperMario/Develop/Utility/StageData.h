#pragma once
#include <vector>
#include <map>

#include "Vector2D.h"

/// <summary>
/// �p�l�����
/// </summary>
enum ePanelID : unsigned char
{
	WALL,
	BRANCH,
	GATE,
	NONE
};

/// <summary>
/// �אڏ��̃L�[
/// </summary>
enum eAdjacentDirection : unsigned char
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

/// <summary>
/// �X�e�[�W�̃p�l�����
/// </summary>
class StageData
{
private:
	static StageData* instance;
	std::vector<std::vector<ePanelID>> data;

private:
	StageData() = default;

	// �R�s�[�K�[�h
	StageData(const StageData&) = delete;
	StageData& operator = (const StageData&) = delete;
	// ~�R�s�[�K�[�h

public:
	/// <summary>
	/// �S�Ẵp�l�������擾����
	/// </summary>
	/// <returns>�S�Ẵp�l�����</returns>
	static const std::vector<std::vector<ePanelID>> GetAll();

	/// <summary>
	/// �אڂ���p�l�������擾
	/// </summary>
	/// <param name="location">���ݍ��W</param>
	/// <returns>�אڂ���p�l�����</returns>
	static const std::map<eAdjacentDirection, ePanelID> GetAdjacentPanelData(const Vector2D& location);

	/// <summary>
	/// ���ݍ��W�̃p�l�������擾����
	/// </summary>
	/// <param name="location">���ݍ��W</param>
	/// <returns>�p�l�����</returns>
	static const ePanelID GetPanelData(const Vector2D& location);

	/// <summary>
	/// ���W����Y���ɕϊ�����
	/// </summary>
	/// <param name="location">���W���</param>
	/// <param name="i">�ϊ���̓Y��</param>
	/// <param name="j">�ϊ���̓Y��</param>
	static void ConvertToIndex(const Vector2D& location, int& i, int& j);

private:
	/// <summary>
	/// �X�e�[�W�f�[�^��ǂݍ���
	/// </summary>
	void Load();
};