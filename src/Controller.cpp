#include "Controller.h"


using std::ifstream;

Controller::Controller() {}


void Controller::run()
{
    ifstream file, fileLevel;
    string nameLevel;
    int numLevel = 0;

    file.open("Playlist.txt");
    if (!file)
    {
        std::cerr << "Can't open the main file\n";
        exit(EXIT_FAILURE);
    }

    while (file >> nameLevel)
    {
        cout << nameLevel << endl;
        numLevel++;
        //fileLevel.open(nameLevel);
        fileLevel.open("game1.txt");
        if (!fileLevel)
        {
            std::cerr << "Can't open the game file, moving to the next one...\n"; // add timer pls ty
            continue;
        }

        if (!m_board.createBoard(fileLevel))
        {
            std::cout << "Invalid level name, loading the next level...\n"; // add timer pls ty
            continue;
        }

        m_board.loadNextLevel();
        m_board.print(0, 0, 0);

        if (levelControl(numLevel)) // returns won or lost
        {
            //טעינת שלב הבא
            

        }
    }
}

bool Controller::levelControl(int numLevel)
{
    Player player(m_board.getPlayerLoc());//קבלת מיקום של השחקן
    m_player = player;
    int guardCounter = 0;

    //מקבלת את מיקום השחקנים בהתחלה
    for (int index = 0; index < m_board.getGuards().size(); index++)
    {
        if (index >= m_guard.size()) m_guard.resize(index + 1);
        m_guard[index].setGuard(m_board.getGuards()[index], true);
        guardCounter++;
    }

    bool hurt = false, dead = false, won = false;
    //כל עוד השחקן שלי עם חיים ממשיכים 
    while (m_player.getLives() > 0)
    {
        hurt = false;
        playTurn(true, hurt, dead, won, numLevel);
        if (won)
        {
            m_player.addPoints(25 + 3 * guardCounter);
            return true;
        }
        if (dead) return false;
        if (hurt) continue;

        playTurn(false, hurt, dead, won, numLevel);
        if (dead) return false;
    }
    return false;
}

void Controller::playTurn(bool playerTurn, bool& hurt, bool& dead, bool& won, int numLevel)
{
    while (playerTurn) //מתגלגלים בלולאה כל עוד השחקן מפגר ושם לי תווים לא נכונים (חיצים או פצצה)
    {
        int direction = _getch();
        
        if (m_player.setLocation(direction)) //במזיז את השחקן לאן ששמתי מבחינת חצים 
        {
            if (m_board.validCell(m_player.getLocation())) break; // אם נכון אז תשים אותו איפה שרציתי
        }

        if (direction == 'b') // פצצה
        {
            m_board.addBomb(m_player.getLocation()); // מוסיפים את הפצצה
            break;
        }
    }
    for (int guardCell = 0; !playerTurn && guardCell < m_guard.size(); guardCell++)
    {
        m_guard[guardCell].calcSetNextMove(m_player.getLocation());
        endOfTurn(won, hurt, dead);
        if (dead) return;
        m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);
    }

    if (playerTurn)
    {
        endOfTurn(won, hurt, dead);
        if (dead) return;
        m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);
    }
}

void Controller::endOfTurn(bool& won, bool& hurt, bool& dead) // 0 1 2
{
    m_board.reduceBombsTimer();
    cout << "hi\n";
    m_board.loadAfterMove(); //שמה את המיקום במקום 0
    cout << "hi\n";
    if (m_board.foundDoor(m_player.getLocation()))
    {
        won = true; // מציאת דלת
        return;
    }
    cout << "hi\n";
    if(m_board.explodeBomb()) 
    {
        for (int index = 0; index < m_guard.size(); index++)
        {
            if (m_board.checkAllCells(m_guard[index].getLocation()))
            {
                m_guard.erase(m_guard.begin() + index);
                m_board.removeGuard(index);
                m_player.addPoints(5);
            }
        }
        m_guard.shrink_to_fit();

        if (m_board.checkAllCells(m_player.getLocation()))
        {
            if (m_player.gotHitDead())
            {
                dead = true;
                return;
            }
            m_player.SetOgPlace();
            for (int index = 0; index < m_guard.size(); index++)
            {
                m_guard[index].returnOg();
            }
            m_board.updateBoardAfterExploded(m_player.getLocation(), m_guard);

            hurt = true;
            return;
        }
        m_board.removeStonesExploded();
    }

    for (int index = 0; index < m_guard.size(); index++)
    {
        if (m_player.getLocation().isEqual(m_guard[index].getLocation()))
        {
            if (m_player.gotHitDead())
            {
                dead = true;
                return;
            }
            hurt = true;
            return;
        }
    }
}