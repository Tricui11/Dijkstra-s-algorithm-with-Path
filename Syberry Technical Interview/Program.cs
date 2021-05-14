using System;
using System.IO;

namespace SyberryTestTask
{
    class Program
    {
        static void Main(string[] args)
        {   /*   
            #region input and define
            int n = 0, m = 0;
            string temp;

            Console.Write("N: ");
            temp = Console.ReadLine();

            try
            {
                n = int.Parse(temp);
            }
            catch (FormatException)
            {
                Console.WriteLine($"Unable to parse '{temp}'");
            }

            Console.Write("M: ");
            temp = Console.ReadLine();
            try
            {
                m = int.Parse(temp);
            }
            catch (FormatException)
            {
                Console.WriteLine($"Unable to parse '{temp}'");
            }

            string[,] map = new string[n, m];

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                        map[i, j] = Console.ReadLine();  
                }
            }
            #endregion
*/
      
      string[,] map = new string[5,4]     {
                            {    "-2",  "10",  "1", "-2"},
                            {    "13", "3",   "X",  "1"},
                            {   "-11",  "X",  "X", "-3"},
                            {   "-1",  "0",  "1", "-11"},
                            {   "-1",  "X",  "X", "-3"},
                };
      Rover.CalculateRoverPath(map);
        }
    }
}
