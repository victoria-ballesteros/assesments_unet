using System.Security.Cryptography.X509Certificates;

namespace src.Components.shared.sequences
{
    public class Sequences
    {
        public Sequences()
        {
        }

        public List<int> ResolverSecuencia(List<string> lineas)
        {
            int T = int.Parse(lineas[0]), N = 0;
            List<int> resultado = new List<int>();
            lineas.RemoveAt(0);
            foreach (var linea in lineas)
            {
                N = linea[0] - '0';
                List<int> numeros = new List<int>();
                for (int i = 0; i < N; i++)
                {
                    numeros.Add(linea[2 + (i * 2)] - '0');
                }
                resultado.Add(Recursive(numeros, N, 0));
            }

            // Se crea el archivo
            string rutaArchivo = @".\wwwroot\file\secuencia.txt";
            string contenido = "";

            if (!File.Exists(rutaArchivo))
            {
                File.Create(rutaArchivo).Close();
            }

            foreach (var linea in resultado)
            {
                contenido += linea.ToString() + '\n';
            }

            File.WriteAllText(rutaArchivo, contenido);
            return resultado;
        }

        public int Recursive(List<int> linea, int N, int S)
        {
            bool derecha = true;
            int iteraciones = 1;
            // Caso base
            if (N == S)
            {
                return iteraciones;
            }

            int helper = Recursive(linea, N, S + 1);

            for (int i = S; i < N - 1; i++)
            {
                if (derecha)
                {
                    if (linea[i] > linea[i + 1])
                    {
                        iteraciones++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if (linea[i] < linea[i + 1])
                    {
                        iteraciones++;
                    }
                    else
                    {
                        break;
                    }
                }
                derecha = !derecha;
            }
            if (helper <= iteraciones)
            {
                return iteraciones;
            }
            else
            {
                return helper;
            }
        }
    }
}
