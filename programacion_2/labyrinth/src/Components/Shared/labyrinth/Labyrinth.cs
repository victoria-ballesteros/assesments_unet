namespace src.Components.shared.labyrinth
{
    public class Labyrinth
    {
        public struct Step
        {
            public int id;
            public int peso;
            public List<int> allegados;
        }
        public List<Step> vertices = new List<Step>();

        public Labyrinth()
        {
        }

        public List<string> resolverLaberinto(List<string> lineas)
        {
            List<string> archivo = ProcesarArchivo(lineas);
            string rutaArchivo = @".\wwwroot\file\laberinto.txt";
            string contenido = "";

            if (!File.Exists(rutaArchivo))
            {
                File.Create(rutaArchivo).Close();
            }

            foreach (var linea in archivo)
            {
                contenido += linea + '\n';
            }

            File.WriteAllText(rutaArchivo, contenido);

            return archivo;
        }

        public List<string> ProcesarArchivo(List<string> lineas)
        {
            int L = 0; // Numero maximo de lobos
            int N = 0; // Tablero N x N
            int cantLineas = 0, indiceEntrada = 0, indiceSalida = 0;
            foreach (var linea in lineas)
            {
                if (cantLineas == 1)
                {
                    N = int.Parse(linea);
                    break;
                }
                cantLineas++;
            }
            // Creamos la matriz que representa al tablero
            int[,] matriz = new int[N, N];
            int auxMatriz = 0;
            cantLineas = 0;
            foreach (var linea in lineas)
            {
                if (cantLineas == 0)
                {
                    L = int.Parse(linea);
                }
                else if (cantLineas == 1)
                {
                    N = int.Parse(linea);
                }
                else
                {
                    for (int i = 0; i < N; i++)
                    {
                        if (linea.ElementAt(i) == '#')
                        {
                            matriz[auxMatriz, i] = 0;
                        }
                        else if (linea.ElementAt(i) == '.')
                        {
                            matriz[auxMatriz, i] = 1;
                        }
                        else if (linea.ElementAt(i) == '*')
                        {
                            matriz[auxMatriz, i] = 2;
                        }
                        else if (linea.ElementAt(i) == 'E')
                        {
                            matriz[auxMatriz, i] = 3;
                        }
                        else if (linea.ElementAt(i) == 'S')
                        {
                            matriz[auxMatriz, i] = 4;
                        }
                    }
                    auxMatriz++;
                }
                cantLineas++;
            }
            // Creamos el grafo no dirigido
            int contPasos = 1;
            for (int i = 0; i < N; i++)
            {
                for (int a = 0; a < N; a++)
                {
                    if (matriz[i, a] != 0)
                    {
                        Step step = new Step
                        {
                            id = contPasos,
                            peso = matriz[i, a],
                            allegados = new List<int>()
                        };
                        vertices.Add(step);
                        matriz[i, a] = contPasos;
                        contPasos++;
                    }
                }
            }
            contPasos = 0;
            // Unir los vertices
            for (int i = 0; i < N; i++)
            {
                for (int a = 0; a < N; a++)
                {
                    if (matriz[i, a] != 0)
                    {
                        // El vertice está en la posicion contPasos en la lista
                        // Vericamos los posibles caminos A-A-I-D
                        // Arriba - Abajo
                        if (i != 0)
                        {
                            if (matriz[i - 1, a] != 0)
                            {
                                vertices[contPasos].allegados.Add(matriz[i - 1, a]);
                            }
                        }
                        if (i != N - 2)
                        {
                            if (matriz[i + 1, a] != 0)
                            {
                                vertices[contPasos].allegados.Add(matriz[i + 1, a]);
                            }
                        }
                        // Izquierda - Derecha
                        if (a != 0)
                        {
                            if (matriz[i, a - 1] != 0)
                            {
                                vertices[contPasos].allegados.Add(matriz[i, a - 1]);
                            }
                        }
                        if (a != N - 2)
                        {
                            if (matriz[i, a + 1] != 0)
                            {
                                vertices[contPasos].allegados.Add(matriz[i, a + 1]);
                            }
                        }
                        contPasos++;
                    }
                }
            }
            // Aplicar Dijkstra
            // Buscamos los indices de la Entrada (peso == 3) y de la Salida (peso == 4)
            indiceEntrada = vertices.FindIndex(step => step.peso == 3);
            indiceSalida = vertices.FindIndex(step => step.peso == 4);

            // Inicializamos la tabla
            // COLUMNA 0, VALORES DE 0 A 1 PARA MARCAR SI YA SE VISITO EL VERTICE
            // COLUMNA 1, VALOR DE LA DISTANCIA OBTENIDA
            // COLUMNA 2, VALOR DEL PADRE
            // COLUMNA 3, LOBOS POR LOS QUE DEBE PASAR
            int[,] tabla = new int[contPasos, 4];
            for (int i = 0; i < contPasos; i++)
            {
                tabla[i, 0] = 0;
                tabla[i, 1] = int.MaxValue;
                tabla[i, 2] = 0;
                tabla[i, 3] = 0;
            }
            tabla[indiceEntrada, 1] = 0;

            // Iniciamos Dijkstra
            int actual = indiceEntrada, distancia = 0;
            do
            {
                // Marcar vertice como visitado
                tabla[actual, 0] = 1;

                if (vertices[actual].peso == 2)
                {
                    tabla[actual, 3]++;
                }

                // Buscamos a quien se conecta
                for (int i = 0; i < vertices[actual].allegados.Count; i++)
                {
                    // Calculamos la distancia
                    int vecino = vertices[actual].allegados[i] - 1;
                    distancia = vertices[vecino].peso + tabla[actual, 1];

                    // Colocamos las distancias
                    if (distancia < tabla[vertices[actual].allegados[i] - 1, 1])
                    {
                        if (vertices[vecino].peso == 2)
                        {
                            if (tabla[actual, 3] + 1 > L)
                            {
                            }
                            else
                            {
                                tabla[vecino, 3]++;
                                tabla[vecino, 3] += tabla[actual, 3];

                                tabla[vertices[actual].allegados[i] - 1, 1] = distancia;

                                // Colocamos la informacion del padre
                                tabla[vertices[actual].allegados[i] - 1, 2] = actual;
                            }
                        }
                        else
                        {
                            tabla[vecino, 3] += tabla[actual, 3];

                            tabla[vertices[actual].allegados[i] - 1, 1] = distancia;

                            // Colocamos la informacion del padre
                            tabla[vertices[actual].allegados[i] - 1, 2] = actual;
                        }
                    }

                }


                // El nuevo actual es el nodo con la menor distancia que no ha sido visitado

                int indiceMenor = -1, distanciaMenor = int.MaxValue;
                for (int i = 0; i < contPasos; i++)
                {
                    if (tabla[i, 1] < distanciaMenor && tabla[i, 0] == 0)
                    {
                        indiceMenor = i;
                        distanciaMenor = tabla[i, 1];
                    }
                }
                actual = indiceMenor;
            } while (actual != -1);

            List<int> ruta = new List<int>();
            int nodo = indiceSalida;
            while (nodo != indiceEntrada)
            {
                ruta.Add(nodo);
                nodo = tabla[nodo, 2];
            }
            ruta.Add(indiceEntrada);
            ruta.Reverse();

            // Traducir la ruta a coordenadas N, S, E, O

            // Buscamos la primera posicion en la matriz
            int fila = 0, columna = 0, contRuta = 0;
            for (int i = 0; i < N; i++)
            {
                for (int a = 0; a < N; a++)
                {
                    if (matriz[i, a] - 1 == ruta[contRuta])
                    {
                        fila = i;
                        columna = a;
                        contRuta++;
                        break;
                    }
                }
            }

            List<char> direccion = new List<char>();
            bool seguir = true;

            // Empezamos la traduccion
            for (int i = 0; i < ruta.Count - 1; i++)
            {
                // Buscamos arriba
                seguir = true;
                if (fila > 0 && seguir)
                {
                    if (matriz[fila - 1, columna] - 1 == ruta[contRuta])
                    {
                        direccion.Add('N');
                        contRuta++;
                        fila--;
                        seguir = false;
                    }
                }

                // Buscamos abajo
                if (fila < N - 1 && seguir)
                {
                    if (matriz[fila + 1, columna] - 1 == ruta[contRuta])
                    {
                        direccion.Add('S');
                        contRuta++;
                        fila++;
                        seguir = false;
                    }
                }

                // Buscamos hacia la izquierda
                if (columna > 0 && seguir)
                {
                    if (matriz[fila, columna - 1] - 1 == ruta[contRuta])
                    {
                        direccion.Add('O');
                        contRuta++;
                        columna--;
                        seguir = false;
                    }
                }

                // Buscamos hacia la derecha
                if (columna < N - 1 && seguir)
                {
                    if (matriz[fila, columna + 1] - 1 == ruta[contRuta])
                    {
                        direccion.Add('E');
                        contRuta++;
                        columna++;
                        seguir = false;
                    }
                }
            }

            // Guardamos el resultado de la traduccion en el formato solicitado
            string resultado = "";
            int pasos = ruta.Count - 1;
            foreach (var coordenada in direccion)
            {
                resultado += coordenada;
            }

            List<string> final = new List<string>();
            final.Add(pasos.ToString());
            final.Add(resultado);

            return final;
        }

        public void print(int[,] matriz, int N)
        {
            for (int r = 0; r < N; r++)
            {
                for (int c = 0; c < N; c++)
                {
                    Console.Write(" " + matriz[r, c]);
                }
                Console.WriteLine();
            }
        }
    }
}