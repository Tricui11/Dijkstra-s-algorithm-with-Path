import {Directions} from '/js/directions.js'

class Field {
    constructor(x, y, dist, isIncDiagMove, fromTransformed = Directions.None) {
        this.X = x;
        this.Y = y;
        this.Dist = dist;
        this.FromTransformed = fromTransformed;
        this.IsIncDiagMove = isIncDiagMove;
    }

    static compare(a, b) {
        if (a.Dist !== b.Dist) {
            return a.Dist - b.Dist;
        } else {
            if (a.X !== b.X) {
                return a.X - b.X;
            } else {
                if (a.Y !== b.Y) {
                    return a.Y - b.Y;
                } else {
                    if (a.IsIncDiagMove === b.IsIncDiagMove) {
                        return 0;
                    } else {
                        return a.IsIncDiagMove ? 1 : -1;
                    }
                }
            }
        }
    }
}

export { Field };