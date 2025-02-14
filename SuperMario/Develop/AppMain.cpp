#include "DxLib.h"
#include "Utility/ProjectConfig.h"
#include "Scenes/SceneManager.h"
#include "Objects/BlockObject/BlockManager.h"

// ���C���֐��i�v���O�����͂�������n�܂�܂��j
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

		try
		{
			// �V�[���}�l�[�W���[�𐶐�����
			SceneManager manager;

			// ����������
			manager.WakeUp();

			// ���s����
			manager.Run();

			// �I��������
			manager.Shutdown();
		}
		catch (std::string error_log)
		{
			// �G���[���e���o�͂���
			return ErrorThrow(error_log);
		}

		// �I����Ԃ�ʒm����
		return D_SUCCESS;
	
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)

	{

		return -1;

	}

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() != -1)

	{

		ClearDrawScreen();

		DrawCircle(320, 240, 15, GetColor(255, 255, 255), TRUE);

		ScreenFlip();

	}

	DxLib_End();


	BlockManager block_manager;

	Block* block1 = new Block(Vector2D(10.0f, 20.0f), 24, 24, LoadGraph("block_image1.png"));
	Block* block2 = new Block(Vector2D(50.0f, 60.0f), 24, 24, LoadGraph("block_image2.png"));
	block_manager.AddBlock(block1);
	block_manager.AddBlock(block2);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		block_manager.UpdateBlocks(1.0f / 60.0f);
		block_manager.DrawBlocks(Vector2D(0.0f, 0.0f));
	}

	block_manager.FinalizeBlocks();
	DxLib_End();
	return 0;
}

	// �G���g���[�|�C���g
	int main()
	{
		

		BlockManager block_manager; // �u���b�N�}�l�[�W���̃C���X�^���X
		std::vector<GameObjectBase*> game_objects; // �Q�[���I�u�W�F�N�g�̃��X�g

		// �u���b�N�I�u�W�F�N�g�̍쐬�ƒǉ�
		Block* block1 = new Block(Vector2D(10.0f, 20.0f), 24, 24, LoadGraph("block_image1.png"));
		Block* block2 = new Block(Vector2D(50.0f, 60.0f), 24, 24, LoadGraph("block_image2.png"));
		GameObjectBase* player = new GameObjectBase(); // �v���C���[�I�u�W�F�N�g�̗�

		block_manager.AddBlock(block1);
		block_manager.AddBlock(block2);
		game_objects.push_back(player); // �v���C���[�I�u�W�F�N�g�����X�g�ɒǉ�

		// ���C�����[�v
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
		{
			block_manager.UpdateBlocks(1.0f / 60.0f); // �u���b�N���X�V
			block_manager.CheckCollisions(game_objects); // �Փ˂��`�F�b�N
			block_manager.DrawBlocks(Vector2D(0.0f, 0.0f)); // �u���b�N��`��
		}

		block_manager.FinalizeBlocks(); // �u���b�N�̍ŏI����
		for (auto& object : game_objects)
		{
			delete object; // �Q�[���I�u�W�F�N�g�����
		}
		game_objects.clear(); // ���X�g���N���A

		DxLib_End(); 
		return 0; 
	}
	