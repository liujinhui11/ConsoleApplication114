#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using Song = std::vector<std::pair<int, int>>;

/*** 数据结构部分 */

}

{
        
                }
	showText();
	printf("%d\n", score);
            }


void chooseSongs(int now)
{
	gameClass = now;

	memset(gameMap, 0, sizeof(gameMap));
	prints(2, 3, "Choose Songs:");
	if (now == 0)
		prints(4, 1, "←  Twin Tigers  →");
	else
		prints(4, 1, "←TwinTigerEndless→");

	while (_kbhit()) _getch();
	if (_getch() == 13)
		return;
	else
		return chooseSongs(now ^ 1);
        }



                    break;
                }
		}

		maxScore = max(score, maxScore);
		if (fail)
		{
			Beep(400, 1200); 
			printf("Your Score : %d\nMax  Score : %d\n", score, maxScore);
            }
		else
		{
			Beep(700, 20);
			printf("Well Done!\n");
			printf("Your Score : %d\n", score);
        }
     }
	system("pause");
    return 0;
}