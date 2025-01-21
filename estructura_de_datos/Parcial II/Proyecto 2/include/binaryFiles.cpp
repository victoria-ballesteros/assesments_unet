#include "binaryFiles.h"

void binaryFiles::save(const char *nombreArchivo, const void *datos, size_t size)
{
    std::ofstream archivo(nombreArchivo, std::ios::binary | std::ios::app);
    if (!archivo)
    {
        std::cout << "NO SE PUEDO ABRIR EL ARCHIVO.";
        return;
    }
    archivo.write(reinterpret_cast<const char *>(datos), size);
    archivo.close();
}

void binaryFiles::read(const char *nombreArchivo, const size_t size, int indice, void *datos)
{
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo)
    {
        std::cerr << "NO SE PUDO ABRIR EL ARCHIVO." << std::endl;
        throw std::runtime_error("No se pudo abrir el archivo.");
    }

    size_t posicion = indice * size;
    archivo.seekg(posicion);
    if (!archivo.read(reinterpret_cast<char *>(datos), size))
    {
        std::cerr << "ERROR AL LEER DEL ARCHIVO." << std::endl;
        throw std::runtime_error("Error al leer del archivo.");
    }
}

size_t binaryFiles::getSize(const char *nombreArchivo, const size_t size)
{
    std::ifstream archivo(nombreArchivo, std::ios::binary | std::ios::ate);
    if (!archivo)
    {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 0;
    }
    size_t tamanoDelArchivo = archivo.tellg();
    return tamanoDelArchivo / size;
}

bool binaryFiles::isEmpty(const std::string &nombreArchivo)
{
    std::ifstream archivo(nombreArchivo, std::ios::binary | std::ios::ate);
    if (!archivo)
    {
        return true;
    }
    return archivo.tellg() == 0;
}

bool binaryFiles::deleteInFile(const char *nombreArchivo, const size_t size, int indice)
{
    std::vector<char> buffer;
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo)
    {
        std::cerr << "NO SE PUDO ABRIR EL ARCHIVO." << std::endl;
        return false;
    }
    archivo.seekg(0, std::ios::end);
    size_t tamano = archivo.tellg();
    archivo.seekg(0, std::ios::beg);
    buffer.resize(tamano);
    archivo.read(buffer.data(), tamano);
    archivo.close();

    size_t posicion = indice * size;
    if (posicion + size > tamano)
    {
        std::cerr << "Indice fuera de rango." << std::endl;
        return false;
    }

    buffer.erase(buffer.begin() + posicion, buffer.begin() + posicion + size);

    std::ofstream archivoSalida(nombreArchivo, std::ios::binary | std::ios::trunc);
    if (!archivoSalida)
    {
        std::cerr << "NO SE PUDO ABRIR EL ARCHIVO PARA ESCRIBIR." << std::endl;
        return false;
    }
    archivoSalida.write(buffer.data(), buffer.size());
    archivoSalida.close();

    return true;
}