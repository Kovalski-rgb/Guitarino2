public static void PrintTabela(Tabuleiro tab)
        {
            for (int i = 0; i < tab.Linhas; i++)
            {
                Console.Write($"1 ");
                for (int j = 0; j < tab.Colunas; j++)
                {
                    if (tab.Peca(i, j) == null)
                    {
                        Console.Write($"|-");
                    }
                    else
                    {
                        Console.Write($"|"); 
                        ImprimirPeca(tab.Peca(i, j));
                    }
                }
                Console.Write('|');
                Console.WriteLine();
            }
            Console.WriteLine("   A B C D E F G H i j");
        }
