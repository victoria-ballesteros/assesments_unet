namespace src.Components.shared.lists
{
    public class Lists
    {
        public Lists()
        {
        }

        public void Solucion(List<string> cadenas)
        {
            List<List<string>> lineas = new List<List<string>>();
            int posicionLista = 0;
            List<int> posiciones = new List<int>();
            char[] delimitadores = { ',', ' ' };

            lineas.Add(new List<string>());
            foreach (var cadena in cadenas)
            {
                string[] subcadenas = cadena.Split(delimitadores, StringSplitOptions.RemoveEmptyEntries);
                foreach (var palabra in subcadenas)
                {
                    if (palabra.Length > 0 && palabra[palabra.Length - 1] == '.')
                    {
                        lineas[posicionLista].Add(palabra.TrimEnd('.'));
                        posicionLista++;
                        lineas.Add(new List<string>());
                    }
                    else
                    {
                        posiciones[posicionLista]++;
                        lineas[posicionLista].Add(palabra);
                    }
                }
            }

            for (int i = 0; i < lineas.Count; i++)
            {
                for (int j = 0; j < lineas[i].Count; j++)
                {
                    string palabraActual = lineas[i][j];
                    if (palabraActual == "-")
                    {
                        if (j + 1 < lineas[i].Count)
                        {
                            string siguientePalabra = lineas[i][j + 1];
                            lineas[i][j + 1] = "-" + siguientePalabra;
                            lineas[i].RemoveAt(j);
                        }
                    }
                }
            }

            for (int i = 0; i < lineas.Count; i++)
            {
                List<int> numeros = new List<int>();
                List<string> palabras = new List<string>();

                if (lineas[i].Count > 1)
                {
                    for (int j = 0; j < lineas[i].Count; j++)
                    {
                        string espacio = lineas[i][j];
                        if (int.TryParse(espacio, out int resultado))
                        {
                            numeros.Add(resultado);
                        }
                        else
                        {
                            palabras.Add(espacio);
                        }
                    }
                    if (numeros.Count > 1)
                    {
                        numeros.Sort();
                    }
                    if (palabras.Count > 1)
                    {
                        palabras.Sort();
                    }
                    int contNum = 0, contPal = 0;
                    for (int j = 0; j < lineas[i].Count; j++)
                    {
                        string espacio = lineas[i][j];
                        if (int.TryParse(espacio, out int resultado))
                        {
                            lineas[i][j] = numeros[contNum].ToString();
                            contNum++;
                        }
                        else
                        {
                            lineas[i][j] = palabras[contPal];
                            contPal++;
                        }
                    }
                }
            }

            // Actualizamos cadenas sacando de lineas las palabras
            int contador = 0, posicion = 0;
            string final = "";
            cadenas.Clear();
            foreach (var cantidad in posiciones)
            {
                for (int i = 0; i < cantidad; i++)
                {
                    if (posicion < lineas[contador].Count)
                    {
                        final += lineas[contador][posicion];
                    }
                    else
                    {
                    }
                    posicion++;
                }
            }
        }
    }
}