#include "GameController.h"

int main(void)
{
    GameController::GetInstance().Initialize();
    GameController::GetInstance().RunGame();

    return 0;
}

