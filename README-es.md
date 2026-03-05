# CExpression-Calculator

Una calculadora de expresiones matemáticas escrita en lenguaje C, que soporta operaciones básicas y prioridad de paréntesis.

[![C Version](https://img.shields.io/badge/C-C11-blue)](https://en.wikipedia.org/wiki/C_(programming_language))
[![CMake](https://img.shields.io/badge/CMake-3.10+-blue)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![CN](https://img.shields.io/badge/中文-red)](README.md)
[![EN](https://img.shields.io/badge/English-blue)](README-en.md)

🌐 **Elegir Idioma**: [English](README-en.md) | [中文](README.md) | **Español**

## 📚 Descripción del Proyecto

Este es un proyecto de práctica para aprender el lenguaje C, implementando la evaluación de expresiones matemáticas usando el algoritmo **Recursive Descent Parser** (Analizador Recursivo Descendente). A través de este proyecto, puedes aprender:

- Fundamentos del lenguaje C
- Algoritmo recursivo descendente
- Fundamentos del análisis léxico
- Diseño de código modular

## ✨ Características

- ✅ Suma (+), Resta (-), Multiplicación (*), División (/)
- ✅ Manejo de prioridad de paréntesis
- ✅ Precedencia de operadores (multiplicación/división > suma/resta)
- ✅ Soporte para números decimales
- ✅ Interfaz interactiva de línea de comandos

## 🛠️ Tecnologías

- **Lenguaje de Programación**: C (C11)
- **Herramientas de Construcción**: CMake / GCC
- **Algoritmo**: Analizador Recursivo Descendente

## 📁 Estructura de Archivos

```
CExpressionCalculator/
├── main.c           # Punto de entrada del programa principal
├── calculator.c     # Lógica central de la calculadora (por implementar)
├── calculator.h     # Archivo de encabezado de la calculadora
├── token.h          # Definiciones de tipos de Token
├── CMakeLists.txt   # Configuración de compilación CMake
└── README.md        # Documentación del proyecto
```

## 🚀 Inicio Rápido

### Compilar el Proyecto

#### Método 1: Usando GCC

```bash
gcc main.c calculator.c -o calculator.exe -lm
```

#### Método 2: Usando CMake

```bash
# Crear directorio de compilación
mkdir build && cd build

# Configurar proyecto (especificar MinGW)
cmake -G "MinGW Makefiles" ..

# Compilar
cmake --build .
```

### Ejecutar el Programa

```bash
./calculator.exe
```

### Ejemplo de Uso

```
Por favor ingrese la expresión> 2+3*4
Expresión: 2+3*4
Resultado: 14.00

Por favor ingrese la expresión> (2+3)*4
Expresión: (2+3)*4
Resultado: 20.00

Por favor ingrese la expresión> (3-5)*6
Expresión: (3-5)*6
Resultado: -12.00
```

## 📖 Temas de Aprendizaje

### 1. Algoritmo Recursivo Descendente

Definición recursiva de expresiones matemáticas:

```
Expresión = Término { (+|-) Término }
Término   = Factor { (*|/) Factor }
Factor    = Número | '(' Expresión ')'
```

¡Esta definición recursiva soporta naturalmente la precedencia de operadores!

### 2. Análisis Léxico (Lexer)

Dividir la cadena de entrada en Tokens:
- Números: `123`, `45.67`
- Operadores: `+`, `-`, `*`, `/`
- Paréntesis: `(`, `)`

### 3. Diseño Modular

- `token.h` - Definiciones de tipos de Token
- `calculator.c` - Lógica de cálculo
- `main.c` - Interacción con el usuario

## 🤝 Contribuciones

1. Fork este repositorio
2. Crea una rama de característica (`git checkout -b feature/amazing-feature`)
3. Confirma tus cambios (`git commit -m 'Add some amazing feature'`)
4. Envía la rama (`git push origin feature/amazing-feature`)
5. Abre un Pull Request

## Licencia

Este proyecto está licenciado bajo la Licencia MIT - consulta el archivo [LICENSE](LICENSE) para más detalles.

---

⭐ Si este proyecto te ayuda, por favor pon una estrella para mostrar tu apoyo.
