using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

public class Rover {
  [Serializable]
  private class CannotStartMovement : Exception {
    public CannotStartMovement(string message) : base(message) { }
  }
  private class Field : IComparable {
    public int X, Y, Dist;
    public Directions FromTransformed;
    public bool IsIncDiagMove;
    public Field(int x, int y, int dist, bool isIncDiagMove, Directions fromTransformed = Directions.None) {
      X = x;
      Y = y;
      Dist = dist;
      FromTransformed = fromTransformed;
      IsIncDiagMove = isIncDiagMove;
    }
    public int CompareTo(object obj) {
      Field b = obj as Field;
      if (this.Dist == b.Dist) {
        if (this.X != b.X) {
          return this.X - b.X;
        } else {
          return this.Y - b.Y;
        }
      }
      return this.Dist - b.Dist;
    }
  }
  private enum Directions {
    None,
    Down,
    Left,
    Up,
    Right,
    Northeast,
    Northwest,
    Southeast,
    Southwest
  }
  public const int Infinity = int.MaxValue;
  public const int X = int.MinValue;
  public static string CurrentDirectory = Directory.GetCurrentDirectory();
  public static string PathWithSourceCode = Path.GetFullPath(Path.Combine(CurrentDirectory, @"..\..\..\"));
  public static string FilePath = Path.Combine(PathWithSourceCode, "path-plan.txt");
  public static void CalculateRoverPath(string[,] map) {
    try {
      #region define and init variables
      int n = map.GetLength(0);
      int m = map.GetLength(1);
      if ((n == 0) || (m == 0)) {
        throw new CannotStartMovement("intmap's row and column count can not be zero");
      }
      int[,] intmap = new int[n, m];
      bool success;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
          success = int.TryParse(map[i, j], out intmap[i, j]);
          if (!success) {
            if (map[i, j] == "X") {
              intmap[i, j] = X;
            } else {
              throw new CannotStartMovement("Can not start movement because of wrong input data");
            }
          }
        }
      if (intmap[0, 0] == X) {
        throw new CannotStartMovement("can not move - path start with X at [0][0]");
      }
      int[,] dis = new int[n, m];
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
          dis[i, j] = Infinity;
        }
      SortedSet<Field> sortSet = new SortedSet<Field>();
      List<Field> path = new List<Field>();
      path.Add(new Field(0, 0, intmap[0, 0], true));
      sortSet.Add(new Field(0, 0, 0, true));
      dis[0, 0] = intmap[0, 0];
      #endregion
      #region Dijkstra's algorithm
      while (sortSet.Count != 0) {
        Field k = sortSet.First();
        sortSet.Remove(sortSet.First());
        for (int i = 0; i < 8; i++) {
          int x = k.X;
          int y = k.Y;
          Directions fromTransformed = Directions.None;
          int updownValue = 0;
          bool isIncDiagMove = k.IsIncDiagMove;
          switch (i) {
            case 0:
              --x;
              fromTransformed = Directions.Down;
              break;
            case 1:
              ++y;
              fromTransformed = Directions.Left;
              break;
            case 2:
              ++x;
              fromTransformed = Directions.Up;
              break;
            case 3:
              --y;
              fromTransformed = Directions.Right;
              break;
            case 4:
              ++x;
              ++y;
              fromTransformed = Directions.Northwest;
              break;
            case 5:
              ++x;
              --y;
              fromTransformed = Directions.Northeast;
              break;
            case 6:
              --x;
              ++y;
              fromTransformed = Directions.Southwest;
              break;
            case 7:
              --x;
              --y;
              fromTransformed = Directions.Southeast;
              break;
          }
          if (!IsInsideintmap(x, y, n, m, intmap)) {
            continue;
          }
          switch (fromTransformed) {
            case Directions.Down:
              updownValue = Math.Abs(intmap[x, y] - intmap[x + 1, y]);
              break;
            case Directions.Left:
              updownValue = Math.Abs(intmap[x, y] - intmap[x, y - 1]);
              break;
            case Directions.Up:
              updownValue = Math.Abs(intmap[x, y] - intmap[x - 1, y]);
              break;
            case Directions.Right:
              updownValue = Math.Abs(intmap[x, y] - intmap[x, y + 1]);
              break;
            case Directions.Northwest:
              updownValue = Math.Abs(intmap[x, y] - intmap[x - 1, y - 1]);
              break;
            case Directions.Northeast:
              updownValue = Math.Abs(intmap[x, y] - intmap[x - 1, y + 1]);
              break;
            case Directions.Southwest:
              updownValue = Math.Abs(intmap[x, y] - intmap[x + 1, y - 1]);
              break;
            case Directions.Southeast:
              updownValue = Math.Abs(intmap[x, y] - intmap[x + 1, y + 1]);
              break;
          }
          if ((fromTransformed == Directions.Northwest) || (fromTransformed == Directions.Northeast) || (fromTransformed == Directions.Southwest) || (fromTransformed == Directions.Southeast)) {
            isIncDiagMove = !isIncDiagMove;
            if (isIncDiagMove) {
              ++updownValue;
            }
          }
          // If neighbour Field distance is bigger, then update it
          if (dis[x, y] > dis[k.X, k.Y] + updownValue + 1) {
            if (dis[x, y] != Infinity) {
              Field temp = new Field(x, y, dis[x, y], isIncDiagMove);
              sortSet.Remove(temp);
            }
            dis[x, y] = dis[k.X, k.Y] + updownValue + 1;
            sortSet.Add(new Field(x, y, dis[x, y], isIncDiagMove));
            path.Add(new Field(x, y, intmap[x, y], isIncDiagMove, fromTransformed));
          }
        }
      }
      #endregion
      #region output
      int length = dis[n - 1, m - 1] - intmap[0, 0];
      List<Field> pathFiltered = new List<Field>();
      Field tempField = path.LastOrDefault(c => (c.X == n - 1) && (c.Y == m - 1));
      if (tempField == null) {
        throw new CannotStartMovement("Can not reach desired location because of terrain");
      }
      do {
        pathFiltered.Add(tempField);
        switch (tempField.FromTransformed) {
          case Directions.Down:
            tempField = path.Last(c => (c.X == tempField.X + 1) && (c.Y == tempField.Y));
            break;
          case Directions.Left:
            tempField = path.Last(c => (c.X == tempField.X) && (c.Y == tempField.Y - 1));
            break;
          case Directions.Up:
            tempField = path.Last(c => (c.X == tempField.X - 1) && (c.Y == tempField.Y));
            break;
          case Directions.Right:
            tempField = path.Last(c => (c.X == tempField.X) && (c.Y == tempField.Y + 1));
            break;
          case Directions.Northwest:
            tempField = path.Last(c => (c.X == tempField.X - 1) && (c.Y == tempField.Y - 1));
            break;
          case Directions.Northeast:
            tempField = path.Last(c => (c.X == tempField.X - 1) && (c.Y == tempField.Y + 1));
            break;
          case Directions.Southwest:
            tempField = path.Last(c => (c.X == tempField.X + 1) && (c.Y == tempField.Y - 1));
            break;
          case Directions.Southeast:
            tempField = path.Last(c => (c.X == tempField.X + 1) && (c.Y == tempField.Y + 1));
            break;
        }
      }
      while (tempField.FromTransformed != Directions.None);
      pathFiltered.Add(new Field(0, 0, intmap[0, 0], true));
      pathFiltered.Reverse();
      using (TextWriter tw = new StreamWriter(FilePath)) {
        if ((pathFiltered.Last().X == 0) && (pathFiltered.Last().Y == 0)) {
          tw.WriteLine("[0][0]");
          tw.WriteLine("steps: 0");
          tw.WriteLine("fuel: 0");
          return;
        }
        for (int i = 0; i < pathFiltered.Count - 1; i++) {
          tw.Write("[" + pathFiltered[i].X + "][" + pathFiltered[i].Y + "]->");
        }
        tw.WriteLine("[" + pathFiltered.Last().X + "][" + pathFiltered.Last().Y + "]");
        tw.WriteLine("steps: " + (pathFiltered.Count - 1).ToString());
        tw.WriteLine("fuel: " + length);
      }
      #endregion
    }
    catch (CannotStartMovement ex) {
      using (TextWriter tw = new StreamWriter(FilePath)) {
        tw.WriteLine(ex.Message);
      }
    }
  }
  static bool IsInsideintmap(int i, int j, int n, int m, int[,] intmap) {
    return (i >= 0) && (i < n) && (j >= 0) && (j < m) && (intmap[i, j] != X);
  }
}