#include "Controller.h"


using std::ifstream;

Controller::Controller() {}


void Controller::run()
{
    ifstream file, fileLevel;
    string level;
    int numLevel = 0;

    file.open("Playlist.txt");
    if (!file)
    {
        std::cerr << "Can't open the main file\n";
        exit(EXIT_FAILURE);
    }

    while (getline(file, level))
    {
        numLevel++;
        fileLevel.open(level);
        if (!fileLevel)
        {
            std::cerr << "Can't open the game file, moving to the next one...\n";
            continue;
        }

        if (!m_board.createBoard(fileLevel)) continue;

        m_board.loadNextLevel();

        if (levelControl(numLevel))
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
    for (int index = 0; index < m_board.getGuards().size() + 1; index++) //check +1
    {
        if (index >= m_guard.size()) m_guard.resize(index + 1);
        m_guard[index].setGuard(m_board.getGuards()[index], true);
        guardCounter++;
    }

    bool hurt = false, dead = false, won = false;
    //כל עוד השחקן שלי עם חיים ממשיכים 
    while (m_player.getLives() != 0)
    {
        hurt = false;
        playTurn(1, hurt, dead, won, numLevel);
        if (won)
        {
            m_player.addPoints(25 + 3 * guardCounter);
            return true;
        }
        if (dead) return false;
        if (hurt) continue;

        playTurn(0, hurt, dead, won, numLevel);
        if (dead) return false;
    }
    return false;
}

void Controller::playTurn(bool playerTurn, bool& hurt, bool& dead, bool& won, int numLevel)
{
    while (playerTurn) //מתגלגלים בלולאה כל עוד השחקן מפגר ושם לי תווים לא נכונים (חיצים או פצצה)
    {
        auto direction = _getch();
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
        m_guard[guardCell].calcSetNextMove();
        if (m_guard[guardCell].getLocation().isEqual(m_player.getLocation()))
        {
            if (endTurnFunction(won, hurt, dead, numLevel)) return;
            m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);
        }
    }

    if(playerTurn) endTurnFunction(won, hurt, dead, numLevel);
}

bool Controller::endTurnFunction(bool& won, bool& hurt, bool& dead, int numLevel)
{
    switch (endOfTurn())
    {
    case 0: // won level
        won = true;
        return true;
    case 1: // hurt
        hurt = true;
        return true;
    case 2:
        dead = true;
        return true;
    case 3:
        m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);
        break;
    }
    return false;
}



int Controller::endOfTurn()
{
    m_board.reduceBombsTimer();
    m_board.loadAfterMove(); //שמה את המיקום במקום 0
    if (m_board.foundDoor(m_player.getLocation())) return 0; // מציאת דלת

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
            if (m_player.gotHitDead()) return 2;
            m_player.SetOgPlace();
            for (int index = 0; index < m_guard.size(); index++)
            {
                m_guard[index].returnOg();
            }
            m_board.updateBoardAfterExploded(m_player.getLocation(), m_guard);

            return 1;
        }
    }

    for (int index = 0; index < m_guard.size(); index++)
    {
        if (m_player.getLocation().isEqual(m_guard[index].getLocation()))
        {
            if (m_player.gotHitDead()) return 2;
            return 1;
        }
    }
    return 3;
}