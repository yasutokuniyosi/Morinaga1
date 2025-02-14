#include "DxLib.h"
#include "Utility/ProjectConfig.h"
#include "Scenes/SceneManager.h"
#include "Objects/BlockObject/BlockManager.h"

// メイン関数（プログラムはここから始まります）
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

		try
		{
			// シーンマネージャーを生成する
			SceneManager manager;

			// 初期化処理
			manager.WakeUp();

			// 実行処理
			manager.Run();

			// 終了時処理
			manager.Shutdown();
		}
		catch (std::string error_log)
		{
			// エラー内容を出力する
			return ErrorThrow(error_log);
		}

		// 終了状態を通知する
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

	// エントリーポイント
	int main()
	{
		

		BlockManager block_manager; // ブロックマネージャのインスタンス
		std::vector<GameObjectBase*> game_objects; // ゲームオブジェクトのリスト

		// ブロックオブジェクトの作成と追加
		Block* block1 = new Block(Vector2D(10.0f, 20.0f), 24, 24, LoadGraph("block_image1.png"));
		Block* block2 = new Block(Vector2D(50.0f, 60.0f), 24, 24, LoadGraph("block_image2.png"));
		GameObjectBase* player = new GameObjectBase(); // プレイヤーオブジェクトの例

		block_manager.AddBlock(block1);
		block_manager.AddBlock(block2);
		game_objects.push_back(player); // プレイヤーオブジェクトをリストに追加

		// メインループ
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
		{
			block_manager.UpdateBlocks(1.0f / 60.0f); // ブロックを更新
			block_manager.CheckCollisions(game_objects); // 衝突をチェック
			block_manager.DrawBlocks(Vector2D(0.0f, 0.0f)); // ブロックを描画
		}

		block_manager.FinalizeBlocks(); // ブロックの最終処理
		for (auto& object : game_objects)
		{
			delete object; // ゲームオブジェクトを解放
		}
		game_objects.clear(); // リストをクリア

		DxLib_End(); 
		return 0; 
	}
	