#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include "CannotStartMovementException.cpp"
#include "Field.cpp"
#include "ui_dialog.h"
using namespace std;

bool Compare_Field_dists(const Field* x, const Field* y)
{
    return x->Dist < y->Dist;
}

bool IsInsideintmap(int i, int j, int n, int m, int** intmap)
{
    return (i >= 0) && (i < n) && (j >= 0) && (j < m) && *(intmap[i] + j) != INT_MIN;
}

void CalculateRoverPath(string** map, int N, int M, Ui::Dialog* ui)
{
    try
    {
    #pragma region define and init variables
        if ((N == 0) || (M == 0))
        {
            const char* errMsg = "intmap's row and column count can not be zero";
            throw CannotStartMovementException((char*)errMsg);
        }

        int** intmap = new int* [N];
        for (int i = 0; i < N; ++i)
        {
            intmap[i] = new int[M];
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (*(map[i] + j) == "X")
                {
                    *(intmap[i] + j) = INT_MIN;
                }
                else
                {
                    stringstream ss;
                    ss << *(map[i] + j);
                    ss >> *(intmap[i] + j);
                }
            }
        }
        if (*intmap[0, 0] == INT_MIN)
        {
            const char* errMsg = "can not move - path start with X at [0][0]";
            throw new CannotStartMovementException((char*)errMsg);
        }

        int** dis = new int* [N];
        for (int i = 0; i < N; ++i)
        {
            dis[i] = new int[M];
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                dis[i][j] = INT_MAX;
            }
        }

        set<Field*, Field::compare> sortSet;
        vector<Field*> path;
        path.emplace_back(new Field(0, 0, *intmap[0, 0], true));
        sortSet.insert(new Field(0, 0, 0, true));
        *dis[0, 0] = *intmap[0, 0];
    #pragma endregion

    #pragma region Dijkstras algorithm
        while (sortSet.size() != 0)
        {
            auto k = *(sortSet.begin());
            auto iterator = sortSet.begin();
            sortSet.erase(iterator);
            for (int i = 0; i < 8; i++)
            {
                int x = k->X;
                int y = k->Y;
                Directions fromTransformed = None;
                int updownValue = 0;
                bool isIncDiagMove = k->IsIncDiagMove;
                switch (i)
                {
                case 0:
                    --x;
                    fromTransformed = Down;
                    break;
                case 1:
                    ++y;
                    fromTransformed = Left;
                    break;
                case 2:
                    ++x;
                    fromTransformed = Up;
                    break;
                case 3:
                    --y;
                    fromTransformed = Right;
                    break;
                case 4:
                    ++x;
                    ++y;
                    fromTransformed = Northwest;
                    break;
                case 5:
                    ++x;
                    --y;
                    fromTransformed = Northeast;
                    break;
                case 6:
                    --x;
                    ++y;
                    fromTransformed = Southwest;
                    break;
                case 7:
                    --x;
                    --y;
                    fromTransformed = Southeast;
                    break;
                }
                if (!IsInsideintmap(x, y, N, M, intmap))
                {
                    continue;
                }
                switch (fromTransformed)
                {
                case Down:
                    updownValue = abs(*(intmap[x] + y) - *(intmap[x + 1] + y));
                    break;
                case Left:
                    updownValue = abs(*(intmap[x] + y) - *(intmap[x] + y - 1));
                    break;
                case Up:
                    updownValue = abs(*(intmap[x] + y) - *(intmap[x - 1] + y));
                    break;
                case Right:
                    updownValue = abs(*(intmap[x] + y) - *(intmap[x] + y + 1));
                    break;
                case Northwest:
                    updownValue = abs(*(intmap[x] + y) - *(intmap[x - 1] + y - 1));
                    break;
                case Northeast:
                    updownValue = abs(*(intmap[x] + y) - *(intmap[x - 1] + y + 1));
                    break;
                case Southwest:
                    updownValue = abs(*(intmap[x] + y) - *(intmap[x + 1] + y - 1));
                    break;
                case Southeast:
                    updownValue = abs(*(intmap[x] + y) - *(intmap[x + 1] + y + 1));
                    break;
                }
                if ((fromTransformed == Northwest) || (fromTransformed == Northeast) || (fromTransformed == Southwest) || (fromTransformed == Southeast))
                {
                    isIncDiagMove = !isIncDiagMove;
                    if (isIncDiagMove)
                    {
                        ++updownValue;
                    }
                }
                // If neighbour Field distance is bigger, then update it
                if (*(dis[x] + y) >= *(dis[k->X] + k->Y) + updownValue + 1)
                {
                    if (*(dis[x] + y) != INT_MAX)
                    {
                        Field* temp = new Field(x, y, *(dis[x] + y), isIncDiagMove);
                        sortSet.erase(temp);
                    }
                    *(dis[x] + y) = *(dis[k->X] + k->Y) + updownValue + 1;
                    sortSet.insert(new Field(x, y, *(dis[x] + y), isIncDiagMove));
                    path.emplace_back(new Field(x, y, *(dis[x] + y), isIncDiagMove, fromTransformed));
                }
            }
        }
    #pragma endregion

    #pragma region output
        vector<Field*> tempLastFields;
        for (int i = 0; i < path.size(); i++)
        {
            Field* temp = path.at(i);
            if ((temp->X == N - 1) && (temp->Y == M - 1))
            {
                tempLastFields.emplace_back(temp);
            }
        }
        if (tempLastFields.size() == 0)
        {
            const char* errMsg = "Can not reach desired location because of terrain";
            throw CannotStartMovementException((char*)errMsg);
        }
        Field* tempField = *min_element(tempLastFields.begin(), tempLastFields.end(), Compare_Field_dists);
        vector<Field*> pathFiltered;
        int length = 0;
        int totalDiags = 0;
        do
        {
            pathFiltered.emplace_back(tempField);
            switch (tempField->FromTransformed)
            {
            case Down:
                length += abs(*(intmap[tempField->X] + tempField->Y) - *(intmap[tempField->X + 1] + tempField->Y)) + 1;
                tempField = *find_if(path.rbegin(), path.rend(), [&](Field* c)
                    {
                        return (c->X == tempField->X + 1) && (c->Y == tempField->Y) && (c->IsIncDiagMove == tempField->IsIncDiagMove);
                    });
                break;
            case Left:
                length += abs(*(intmap[tempField->X] + tempField->Y) - *(intmap[tempField->X] + tempField->Y - 1)) + 1;
                tempField = *find_if(path.rbegin(), path.rend(), [&](Field* c)
                    {
                        return (c->X == tempField->X) && (c->Y == tempField->Y - 1) && (c->IsIncDiagMove == tempField->IsIncDiagMove);
                    });
                break;
            case Up:
                length += abs(*(intmap[tempField->X] + tempField->Y) - *(intmap[tempField->X - 1] + tempField->Y)) + 1;
                tempField = *find_if(path.rbegin(), path.rend(), [&](Field* c)
                    {
                        return (c->X == tempField->X - 1) && (c->Y == tempField->Y) && (c->IsIncDiagMove == tempField->IsIncDiagMove);
                    });
                break;
            case Right:
                length += abs(*(intmap[tempField->X] + tempField->Y) - *(intmap[tempField->X] + tempField->Y + 1)) + 1;
                tempField = *find_if(path.rbegin(), path.rend(), [&](Field* c)
                    {
                        return (c->X == tempField->X) && (c->Y == tempField->Y + 1) && (c->IsIncDiagMove == tempField->IsIncDiagMove);
                    });
                break;
            case Northwest:
                length += abs(*(intmap[tempField->X] + tempField->Y) - *(intmap[tempField->X - 1] + tempField->Y - 1)) + 1;
                tempField = *find_if(path.rbegin(), path.rend(), [&](Field* c)
                    {
                        return (c->X == tempField->X - 1) && (c->Y == tempField->Y - 1) && (c->IsIncDiagMove != tempField->IsIncDiagMove);
                    });
                ++totalDiags;
                break;
            case Northeast:
                length += abs(*(intmap[tempField->X] + tempField->Y) - *(intmap[tempField->X - 1] + tempField->Y + 1)) + 1;
                tempField = *find_if(path.rbegin(), path.rend(), [&](Field* c)
                    {
                        return (c->X == tempField->X - 1) && (c->Y == tempField->Y + 1) && (c->IsIncDiagMove != tempField->IsIncDiagMove);
                    });
                ++totalDiags;
                break;
            case Southwest:
                length += abs(*(intmap[tempField->X] + tempField->Y) - *(intmap[tempField->X + 1] + tempField->Y - 1)) + 1;
                tempField = *find_if(path.rbegin(), path.rend(), [&](Field* c)
                    {
                        return (c->X == tempField->X + 1) && (c->Y == tempField->Y - 1) && (c->IsIncDiagMove != tempField->IsIncDiagMove);
                    });
                ++totalDiags;
                break;
            case Southeast:
                length += abs(*(intmap[tempField->X] + tempField->Y) - *(intmap[tempField->X + 1] + tempField->Y + 1)) + 1;
                tempField = *find_if(path.rbegin(), path.rend(), [&](Field* c)
                    {
                        return (c->X == tempField->X + 1) && (c->Y == tempField->Y + 1) && (c->IsIncDiagMove != tempField->IsIncDiagMove);
                    });
                ++totalDiags;
                break;
            }
        }
        while (tempField->FromTransformed != None);

        pathFiltered.emplace_back(new Field(0, 0, *intmap[0, 0], true));
        reverse(pathFiltered.begin(), pathFiltered.end());
        length += totalDiags / 2;
        Field* lastField = pathFiltered.back();
        if ((lastField->X == 0) && (lastField->Y == 0))
        {
            cout << "[0][0]" << endl;
            cout << "steps: 0" << endl;
            cout << "fuel: 0" << endl;
            return;
        }
        for (int i = 0; i < pathFiltered.size() - 1; i++)
        {
            Field* current = pathFiltered.at(i);
            cout << "[" << current->X << "][" << current->Y << "]->";
            QLineEdit *pathCell = ((QLineEdit*)ui->mapGridLayout->itemAtPosition(current->X,current->Y)->widget());
            pathCell->setStyleSheet("color: white;  background-color: green");
        }
        cout << "[" << lastField->X << "][" << lastField->Y << "]" << endl;int steps = pathFiltered.size() - 1;
        QLineEdit *pathLastCell = ((QLineEdit*)ui->mapGridLayout->itemAtPosition(lastField->X,lastField->Y)->widget());
        pathLastCell->setStyleSheet("color: white;  background-color: green");
        cout << "steps:" << steps << endl;
        ui->lineEdit_Steps->setText(QString::number(steps));
        cout << "fuel: " << length << endl;
        ui->lineEdit_Fuel->setText(QString::number(length));
    #pragma endregion
    }
    catch (CannotStartMovementException ex)
    {
        cout << ex.what() << endl;
    }
}
