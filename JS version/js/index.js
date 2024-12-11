import {calculateRoverPath} from '/js/dijkstra.js'

let terrainMapData = [];

document.getElementById("generateMap").addEventListener("click", () => {
    const rows = parseInt(document.getElementById("rows").value);
    const cols = parseInt(document.getElementById("cols").value);
    const minValue = parseInt(document.getElementById("minValue").value);
    const maxValue = parseInt(document.getElementById("maxValue").value);
    const xFrequency = parseFloat(document.getElementById("xFrequency").value);
    const fillRandom = document.getElementById("fillRandom").checked;
    const terrainMap = document.getElementById("terrainMap");

    if (isNaN(rows) || isNaN(cols) || isNaN(minValue) || isNaN(maxValue) || isNaN(xFrequency)) {
        alert("Please fill in all fields correctly.");
        return;
    }

    if (minValue >= maxValue) {
        alert("Minimum height value must be less than maximum height value.");
        return;
    }

    if (xFrequency < 0 || xFrequency > 100) {
        alert("X frequency must be a percentage between 0 and 100.");
        return;
    }

    terrainMap.innerHTML = "";

    const map = [];
    for (let i = 0; i < rows; i++) {
        const row = [];
        const rowElement = document.createElement("div");
        rowElement.classList.add("map-row");

        for (let j = 0; j < cols; j++) {
            let cellValue;
            if (fillRandom) {
                if (Math.random() * 100 < xFrequency) {
                    cellValue = "X";
                } else {
                    cellValue = Math.floor(Math.random() * (maxValue - minValue + 1)) + minValue;
                }
            } else {
                cellValue = "";
            }

            row.push(cellValue);

            const cellElement = document.createElement("div");
            cellElement.classList.add("map-cell");
            cellElement.textContent = cellValue;
            rowElement.appendChild(cellElement);
        }

        map.push(row);
        terrainMap.appendChild(rowElement);
    }

    terrainMapData = map;
    console.log("Generated Map:", map);
});

document.getElementById("solve").addEventListener("click", function() {
    if (terrainMapData.length === 0) {
        alert("Please generate the map first!");
        return;
    }

    const N = terrainMapData.length;
    const M = terrainMapData[0].length;

    // Вызов функции для получения пути и результатов
    const result = calculateRoverPath(terrainMapData, N, M);

    console.log(result);

    if (result.path.length === 0) {
        alert("Path not found!");
        return;
    }

    // Отображаем путь на карте
    const terrainMap = document.getElementById("terrainMap");
    const cells = terrainMap.getElementsByClassName("map-cell");

    // Очищаем все выделения
    for (let i = 0; i < cells.length; i++) {
        cells[i].classList.remove("path-cell");
    }

    // Выделяем ячейки пути
    result.path.forEach(({ X, Y }) => {
        const index = X * M + Y;
        cells[index].classList.add("path-cell");
    });

    // Обновляем значения в output
    document.getElementById("steps").value = result.steps;
    document.getElementById("fuel").value = result.fuel;
});