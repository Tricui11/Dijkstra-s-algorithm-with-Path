import { Field } from '/js/field.js'
import { Directions } from '/js/directions.js'
import { CannotStartMovementException } from '/js/cannotStartMovementException.js'

function isInsideIntMap(x, y, n, m, intMap) {
    return x >= 0 && x < n && y >= 0 && y < m && intMap[x][y] !== Number.MIN_SAFE_INTEGER;
}

function calculateRoverPath(map, N, M) {
    try {
        if (N === 0 || M === 0) {
            throw new CannotStartMovementException("intmap's row and column count cannot be zero");
        }

        // Инициализация карты
        let intMap = Array.from({ length: N }, () => new Array(M));
        for (let i = 0; i < N; i++) {
            for (let j = 0; j < M; j++) {
                intMap[i][j] = map[i][j] === "X" ? Number.MIN_SAFE_INTEGER : parseInt(map[i][j], 10);
            }
        }

        if (intMap[0][0] === Number.MIN_SAFE_INTEGER) {
            throw new CannotStartMovementException("Cannot move - path starts with 'X' at [0][0]");
        }

        let dis = Array.from({ length: N }, () => new Array(M).fill(Number.MAX_SAFE_INTEGER));
        let sortSet = new Set();
        let path = [new Field(0, 0, intMap[0][0], true)];
        sortSet.add(new Field(0, 0, 0, true));

        dis[0][0] = intMap[0][0];

        while (sortSet.size > 0) {
            let k = [...sortSet].shift(); // Получаем первый элемент из множества
            sortSet.delete(k);

            for (let i = 0; i < 8; i++) {
                let x = k.X;
                let y = k.Y;
                let fromTransformed = Directions.None;
                let updownValue = 0;
                let isIncDiagMove = k.IsIncDiagMove;

                switch (i) {
                    case 0: x--; fromTransformed = Directions.Down; break;
                    case 1: y++; fromTransformed = Directions.Left; break;
                    case 2: x++; fromTransformed = Directions.Up; break;
                    case 3: y--; fromTransformed = Directions.Right; break;
                    case 4: x++; y++; fromTransformed = Directions.Northwest; break;
                    case 5: x++; y--; fromTransformed = Directions.Northeast; break;
                    case 6: x--; y++; fromTransformed = Directions.Southwest; break;
                    case 7: x--; y--; fromTransformed = Directions.Southeast; break;
                }

                if (!isInsideIntMap(x, y, N, M, intMap)) continue;

                switch (fromTransformed) {
                    case Directions.Down:
                        updownValue = Math.abs(intMap[x][y] - intMap[x + 1][y]);
                        break;
                    case Directions.Left:
                        updownValue = Math.abs(intMap[x][y] - intMap[x][y - 1]);
                        break;
                    case Directions.Up:
                        updownValue = Math.abs(intMap[x][y] - intMap[x - 1][y]);
                        break;
                    case Directions.Right:
                        updownValue = Math.abs(intMap[x][y] - intMap[x][y + 1]);
                        break;
                    case Directions.Northwest:
                        updownValue = Math.abs(intMap[x][y] - intMap[x - 1][y - 1]);
                        break;
                    case Directions.Northeast:
                        updownValue = Math.abs(intMap[x][y] - intMap[x - 1][y + 1]);
                        break;
                    case Directions.Southwest:
                        updownValue = Math.abs(intMap[x][y] - intMap[x + 1][y - 1]);
                        break;
                    case Directions.Southeast:
                        updownValue = Math.abs(intMap[x][y] - intMap[x + 1][y + 1]);
                        break;
                }

                if (dis[x][y] >= dis[k.X][k.Y] + updownValue + 1) {
                    dis[x][y] = dis[k.X][k.Y] + updownValue + 1;
                    sortSet.add(new Field(x, y, dis[x][y], isIncDiagMove));
                    path.push(new Field(x, y, dis[x][y], isIncDiagMove, fromTransformed));
                }
            }
        }

        // Логика вывода результатов
        let tempLastFields = path.filter(f => f.X === N - 1 && f.Y === M - 1);
        if (tempLastFields.length === 0) {
            throw new CannotStartMovementException("Cannot reach desired location due to terrain");
        }

        let minField = tempLastFields.reduce((min, curr) => curr.Dist < min.Dist ? curr : min);
        console.log(`Path found with ${minField.Dist} steps`);

        // Возвращаем данные: путь, количество шагов и топлива
        return {
            path: path.reverse(),  // Путь от начала до конца
            steps: minField.Dist,  // Количество шагов
            fuel: minField.Dist * 2 // Примерная логика для топлива (можно адаптировать)
        };
    } catch (ex) {
        console.error(ex.message);
        return { path: [], steps: 0, fuel: 0 };
    }
}

export { calculateRoverPath };
