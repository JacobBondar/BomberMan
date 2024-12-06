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
        fileLevel.open(nameLevel);
        if (!fileLevel)
        {
            cout << nameLevel << endl;
            std::cerr << "Can't open the game file, moving to the next one...\n";
            std::this_thread::sleep_for(2000ms);
            continue;
        }

        if (!m_board.createBoard(fileLevel))
        {
            std::cout << "Invalid level, loading the next level...\n";
            std::this_thread::sleep_for(2000ms);
            m_board.resetBoard();
            fileLevel.close();
            continue;
        }

        numLevel++;
        m_board.eraseBoard();
        if (levelControl(numLevel))
        {
            m_board.eraseBoard();
            m_board.printFile("WellDone.txt");
            std::this_thread::sleep_for(1000ms);
        }
        else
        {
            m_board.eraseBoard();
            cout << "You lost, nice try... better luck next time <3\n" <<
                "You have: " <<
                m_player.getPoints() << " points.\n"
                "Do you want to spend 10 points per 1 life?\n" <<
                "Press the amount of lifes you want to get\n" <<
                "0 - for no lifes\n1 - for 1 life\n and so on...\n";
            int choice;
            cin >> choice;

            while (m_player.getPoints() < (10 * choice))
            {
                cout << "You dont have enough points!, " << 
                    "choose another value\n";
                cin >> choice;
            }
            if (choice == 0) break;
            m_player.boughtLife(choice);

            std::this_thread::sleep_for(1000ms);
        }

        m_board.resetBoard();
        m_guard.clear();
        fileLevel.close();
    }
    m_board.eraseBoard();
    m_board.printFile("GameOver.txt");
    m_board.printFinalScore(m_player.getPoints(), m_player.getLives());
    file.close();
}

bool Controller::levelControl(int numLevel)
{
    m_player.setToNewLevel(m_board.getPlayerLoc());
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

        else if (direction == ' ') break;

        cout << "Please press only the following characters: One of the " <<
            "arrows, b or spacebar. \nMake sure you are not trying to go into"
            << " a wall or stone!\n";
        system("pause");
        m_board.eraseBoard();
        m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);
    }

    for (int guardCell = 0; !playerTurn && guardCell < m_guard.size(); guardCell++)
    {
        Location prev = m_guard[guardCell].calcSetNextMove(m_player.getLocation());
        if (!m_board.validCell(m_guard[guardCell].getLocation()) ||
            m_board.checkIfStone(m_guard[guardCell].getLocation()))
            m_guard[guardCell].setLocation(prev);
        else
        {
            m_board.moveObject(prev, m_guard[guardCell].getLocation(), '!');
            m_board.setLocGuard(guardCell, m_guard[guardCell].getLocation());
        }
        endOfTurn(won, hurt, dead, playerTurn);
        if (dead) return;
        std::this_thread::sleep_for(100ms);
        m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);
        if (hurt) break;
    }

    if (playerTurn)
    {
        m_board.setLocPlayer(m_player.getLocation());
        endOfTurn(won, hurt, dead, playerTurn);
        if (dead) return;
        m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);
    }
}

void Controller::endOfTurn(bool& won, bool& hurt, bool& dead, bool player)
{
    if (player)
    {
        m_board.reduceBombsTimer();
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

            m_board.updateBoardAfterHit(m_player.getLocation(), 
                m_player.getOg(), m_guard);
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
                m_board.removeGuard(index);
                m_guard.erase(m_guard.begin() + index);
                m_player.addPoints(5);
                index--;
            }
        }

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