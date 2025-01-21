namespace src.Components.shared.digitalRoots
{
    public class DigitalRoots
    {
        public DigitalRoots()
        {
        }

        public List<string> Raices(List<string> numeros)
        {
            string nulo = "0";
            List<string> final = new List<string>();
            foreach (var linea in numeros)
            {
                if (linea != nulo)
                {
                    final.Add(Recursividad(linea).ToString());
                }
            }

            string rutaArchivo = @".\wwwroot\file\roots.txt";
            string contenido = "";

            if (!File.Exists(rutaArchivo))
            {
                File.Create(rutaArchivo).Close();
            }

            foreach (var linea in final)
            {
                contenido += linea + '\n';
            }

            File.WriteAllText(rutaArchivo, contenido);
            return final;
        }

        public int Recursividad(string numeros)
        {
            int suma = 0;
            // Caso base
            if (numeros.Length == 1)
            {
                return int.Parse(numeros);
            }

            for (int i = 0; i < numeros.Length; i++)
            {
                suma += numeros[i] - '0';
            }

            string nueva = suma.ToString();

            return Recursividad(nueva);
        }
    }
}