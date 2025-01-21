namespace src.Components.shared.pixels
{
    public class Pixels
    {
        public Pixels()
        { }

        public string Solution(List<string> pixeles)
        {
            List<int> valores = new List<int>(), indicadores = new List<int>();
            string[] separacion = pixeles[0].Split(' ');
            int M = int.Parse(separacion[0]), N = int.Parse(separacion[1]), K = int.Parse(separacion[2]);
            pixeles.RemoveAt(0);
            Console.WriteLine($"M = {M}, N = {N}, K = {K}");
            int[,] matriz = new int[M, N];
            int auxMatriz = 0;
            foreach (var linea in pixeles)
            {
                string[] pixel = linea.Split(' ');
                for (int i = 0; i < N; i++)
                {
                    matriz[auxMatriz, i] = int.Parse(pixel[i]);
                }
                auxMatriz++;
            }

            int totalCuadrados = 0, g = 0, c = 0, d = 0;
            List<int> colores = new List<int>();

            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    totalCuadrados += Recursividad(i, j, 2, matriz, ref g, ref c, ref d, ref colores);
                }
            }

            Console.WriteLine($"La cantidad total de cuadrados en la matriz es: {totalCuadrados}");
            Console.WriteLine(g);
            Console.WriteLine(c);
            Console.WriteLine(d);

            string rutaArchivo = @".\wwwroot\file\pixeles.txt";
            string contenido = "";

            if (!File.Exists(rutaArchivo))
            {
                File.Create(rutaArchivo).Close();
            }

            contenido += g.ToString() + " ";
            contenido += c.ToString() + " ";
            contenido += d.ToString();

            File.WriteAllText(rutaArchivo, contenido);

            return contenido;
        }

        public int Recursividad(int fila, int columna, int size, int[,] matriz, ref int g, ref int c, ref int d, ref List<int> colores)
        {
            if (fila + size > matriz.GetLength(0) || columna + size > matriz.GetLength(1))
                return 0;

            int valor = matriz[fila, columna];
            for (int i = fila; i < fila + size; i++)
            {
                for (int j = columna; j < columna + size; j++)
                {
                    if (matriz[i, j] != valor)
                        return 0;
                }
            }
            if (g < size)
            {
                g = size;
                c = 0;
                d = 0;
                colores.Clear();
            }

            if (size == g)
            {
                c++;
            }
            bool flag = false;
            foreach (var color in colores)
            {
                if (color == valor)
                {
                    flag = true;
                }
            }
            if (!flag)
            {
                d++;
                colores.Add(valor);
            }
            return 1 + Recursividad(fila, columna, size + 1, matriz, ref g, ref c, ref d, ref colores);
        }
    }
}