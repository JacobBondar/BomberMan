#include "Controller.h"

using std::ifstream;
using std::cerr;
using std::cout;

//-----------------------------------------------------------------------------

Controller::Controller() {}

//-----------------------------------------------------------------------------

void Controller::run()
{
    ifstream file, fileLevel;
    string nameLevel;
    int numLevel = 0;

    file.open("Playlist.txt");

    checkIfFileOpened(file);

    while (file >> nameLevel)
    {
        fileLevel.open(nameLevel);

        if (!checkIfGameOpened(fileLevel)) continue;
        if (!checkIfBoardValid(fileLevel)) continue;

        numLevel++;
        m_board.eraseBoard();

        if (levelControl(numLevel)) wonGame();
        else
        {
            if (lostGame()) break;
        }

        m_board.resetBoard();
        m_guard.clear();
        fileLevel.close();
    }
    endGame(file);
}

//-----------------------------------------------------------------------------

bool Controller::levelControl(int numLevel)
{
    m_player.setToNewLevel(m_board.getPlayerLoc());
    int guardCounter = insertNewGuards();

    m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);

    bool hurt = false, dead = false, won = false;
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

//-----------------------------------------------------------------------------

void Controller::playTurn(bool playerTurn, bool& hurt, bool& dead, bool& won,
    int numLevel)
{
    while (playerTurn)
    {
        if (playerPlaysTurn(numLevel)) break;
    }

    for (int guardCell = 0; !playerTurn && guardCell < m_guard.size();
        guardCell++)
    {
        if (guardPlaysTurn(numLevel, won, hurt, dead, playerTurn, guardCell))
            return;
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

//-----------------------------------------------------------------------------

void Controller::endOfTurn(bool& won, bool& hurt, bool& dead, bool player)
{
    if (player)
    {
        m_board.reduceBombsTimer();
        if (m_board.moveObject(m_player.getPrePlace(), 
            m_player.getLocation(), '/'))
        {
            won = true;
            return;
        }
    }

    if(m_board.explodeBomb())
    {
        if (controlTheExplosion(dead, hurt)) return;
    }
    
    checkIfPlayerHitGuard(dead, hurt);
}

//-----------------------------------------------------------------------------

void Controller::checkIfFileOpened(ifstream &file)
{
    if (!file)
    {
        cerr << "Can't open the file\n";
        exit(EXIT_FAILURE);
    }
}

//-----------------------------------------------------------------------------

bool Controller::checkIfGameOpened(ifstream& file)
{
    if (!file)
    {
        cerr << "Can't open the game file, moving to the next one...\n";
        std::this_thread::sleep_for(2000ms);
        return false;
    }
    return true;
}

//-----------------------------------------------------------------------------

bool Controller::checkIfBoardValid(ifstream& file)
{
    if (!m_board.createBoard(file))
    {
        cout << "Invalid level, loading the next level...\n";
        std::this_thread::sleep_for(2000ms);
        m_board.resetBoard();
        file.close();
        return false;
    }
    return true;
}

//-----------------------------------------------------------------------------

void Controller::wonGame()
{
    m_board.eraseBoard();
    m_board.printFile("WellDone.txt");
    std::this_thread::sleep_for(1000ms);
}

//-----------------------------------------------------------------------------

bool Controller::lostGame()
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
        cout << "You dont have enough points! " <<
            "Choose another value\n";
        cin >> choice;
    }
    if (choice == 0) return true;
    m_player.boughtLife(choice);

    std::this_thread::sleep_for(1000ms);
    return false;
}

//-----------------------------------------------------------------------------

void Controller::endGame(ifstream &file)
{
    m_board.eraseBoard();
    m_board.printFile("GameOver.txt");
    m_board.printFinalScore(m_player.getPoints(), m_player.getLives());
    file.close();
}

//-----------------------------------------------------------------------------

int Controller::insertNewGuards()
{
    int guardCounter = 0;
    for (int index = 0; index < m_board.getGuards().size(); index++)
    {
        if (index >= m_guard.size()) m_guard.resize(index + 1);
        m_guard[index].setGuard(m_board.getGuards()[index], true);
        guardCounter++;
    }
    return guardCounter;
}

//-----------------------------------------------------------------------------

bool Controller::playerPlaysTurn(int numLevel)
{
    int direction = _getch();

    if (m_player.setLocation(direction))
    {
        if (m_board.validCell(m_player.getLocation())) return true;
        m_player.changePosBack();
    }

    else if (direction == 'b')
    {
        m_board.addBomb(m_player.getLocation());
        return true;
    }

    else if (direction == ' ') return true;

    cout << "Please press only the following characters: One of the " <<
        "arrows, b or spacebar. \nMake sure you are not trying to go into"
        << " a wall or stone!\n";
    system("pause");
    m_board.eraseBoard();
    m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);

    return false;
}

//-----------------------------------------------------------------------------

bool Controller::guardPlaysTurn(int numLevel, bool &won, bool &hurt,
    bool &dead, bool playerTurn, int guardCell)
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
    if (dead) return true;
    std::this_thread::sleep_for(100ms);
    m_board.print(m_player.getPoints(), m_player.getLives(), numLevel);

    return false;
}

//-----------------------------------------------------------------------------

bool Controller::controlTheExplosion(bool& dead, bool& hurt)
{
    if (m_board.checkAllCells(m_player.getLocation()))
    {
        if (m_player.gotHitDead())
        {
            dead = true;
            return true;
        }

        m_board.updateBoardAfterHit(m_player.getLocation(),
            m_player.getOg(), m_guard);
        m_player.SetOgPlace();
        for (int index = 0; index < m_guard.size(); index++)
        {
            m_guard[index].setLocation(m_guard[index].returnOg());
        }

        hurt = true;
        return true;
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

    return false;
}

//-----------------------------------------------------------------------------

void Controller::checkIfPlayerHitGuard(bool& dead, bool& hurt)
{
    for (int index = 0; index < m_guard.size(); index++)
    {
        if (m_player.getLocation().isEqual(m_guard[index].getLocation()))
        {
            m_board.updateBoardAfterHit(m_player.getLocation(), 
                m_player.getOg(), m_guard);
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