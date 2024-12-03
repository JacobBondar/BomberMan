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
        fileLevel.open(nameLevel);
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

        if (levelControl(numLevel)) // returns won or lost
        {
            //טעינת שלב הבא
            

        }
        m_board.resetBoard();
        m_guard.clear();
        fileLevel.close();
    }
    file.close();
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
    m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);

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
            if (m_board.validCell(m_player.getLocation()))
            {
                //m_board.setPlayerLocation(m_player.getLocation());
                break; // אם נכון אז תשים אותו איפה שרציתי
            }
            m_player.changePosBack();
        }
        
        else if (direction == 'b') // פצצה
        {
            m_board.addBomb(m_player.getLocation()); // מוסיפים את הפצצה
            break;
        }
    }

    for (int guardCell = 0; !playerTurn && guardCell < m_guard.size(); guardCell++)
    {
        Location prev = m_guard[guardCell].calcSetNextMove(m_player.getLocation());
        if (m_board.checkIfStone(m_guard[guardCell].getLocation())) m_guard[guardCell].setLocation(prev);
        else m_board.moveObject(prev, m_guard[guardCell].getLocation(), '!');
        endOfTurn(won, hurt, dead, playerTurn);
        if (dead) return;
        m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);
        std::this_thread::sleep_for(200ms);
    }

    if (playerTurn)
    {
        endOfTurn(won, hurt, dead, playerTurn);
        if (dead) return;
        m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);
    }
}

void Controller::endOfTurn(bool& won, bool& hurt, bool& dead, bool player)
{
    m_board.reduceBombsTimer();

    if (player)
    {
        if (m_board.moveObject(m_player.getPrePlace(), m_player.getLocation(), '/'))
        {
            won = true; // מציאת דלת
            return;
        }
    }

    if(m_board.explodeBomb())
    {
        if (m_board.checkAllCells(m_player.getLocation()))
        {
            if (m_player.gotHitDead())
            {
                dead = true;
                return;
            }
            m_board.updateBoardAfterHit(m_player.getLocation(), m_player.getOg(), m_guard);
            m_player.SetOgPlace();
            for (int index = 0; index < m_guard.size(); index++)
            {
                m_guard[index].setLocation(m_guard[index].returnOg());
            }

            hurt = true;
            return;
        }

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

        m_board.removeStonesExploded();

        m_board.addExplodedBomb();
        m_board.removeBomb();
    }

    for (int index = 0; index < m_guard.size(); index++)
    {
        if (m_player.getLocation().isEqual(m_guard[index].getLocation()))
        {
            m_board.updateBoardAfterHit(m_player.getLocation() ,m_player.getOg(), m_guard);
            m_player.SetOgPlace();
            for (int index = 0; index < m_guard.size(); index++)
            {
                m_guard[index].setLocation(m_guard[index].returnOg());
            }

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