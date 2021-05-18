#include "Directions.cpp"
class Field
{
public:
    int X, Y, Dist;
    Directions FromTransformed;
    bool IsIncDiagMove;
    Field(int x, int y, int dist, bool isIncDiagMove, Directions fromTransformed = None) {
        X = x;
        Y = y;
        Dist = dist;
        FromTransformed = fromTransformed;
        IsIncDiagMove = isIncDiagMove;
    }
    struct compare
    {
        bool operator()(const Field* a, const Field* b) const
        {
            if (a->Dist != b->Dist)
            {
                return a->Dist - b->Dist;
            }
            else
            {
                if (a->X != b->X)
                {
                    return a->X - b->X;
                }
                else
                {
                    if (a->Y != b->Y)
                    {
                        return a->Y - b->Y;
                    }
                    else
                    {
                        if (a->IsIncDiagMove == b->IsIncDiagMove)
                        {
                            return 0;
                        }
                        else
                        {
                            return a->IsIncDiagMove ? 1 : -1;
                        }
                    }
                }
            };
        }
    };
};
