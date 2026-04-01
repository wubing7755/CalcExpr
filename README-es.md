# CalcExpr

Una calculadora de expresiones matemáticas escrita en lenguaje C, que soporta operaciones básicas y prioridad de paréntesis.

[![C Version](https://img.shields.io/badge/C-C11-blue)](https://en.wikipedia.org/wiki/C_(programming_language))
[![CMake](https://img.shields.io/badge/CMake-3.10+-blue)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![CN](https://img.shields.io/badge/中文-red)](README.md)
[![EN](https://img.shields.io/badge/English-blue)](README-en.md)

🌐 **Elegir Idioma**: [English](README-en.md) | [中文](README.md) | **Español**

## 📚 Descripción del Proyecto

CalcExpr es una calculadora de expresiones matemáticas desarrollada en C, utilizando el algoritmo **Recursive Descent Parser** (Analizador Recursivo Descendente) para la evaluación de expresiones.

Características del proyecto:
- Arquitectura modular limpia
- Sin dependencias (solo biblioteca estándar de C)
- Sistema de depuración controlable en tiempo de ejecución
- Cobertura completa de pruebas unitarias

## ✨ Características

- ✅ Suma (+), Resta (-), Multiplicación (*), División (/)
- ✅ Manejo de prioridad de paréntesis
- ✅ Precedencia de operadores (multiplicación/división > suma/resta)
- ✅ Soporte para decimales y notación científica
- ✅ Interfaz interactiva de línea de comandos
- ✅ Selección interactiva del nivel de depuración
- ✅ Sistema de depuración (compilación tiempo de activación / control en ejecución)

## 🛠️ Tecnologías

- **Lenguaje de Programación**: C (C11)
- **Herramientas de Construcción**: CMake
- **Algoritmo**: Analizador Recursivo Descendente
- **Pruebas**: CTest

## 📁 Estructura de Archivos

```
CalcExpr/
├── src/                    # Código fuente
│   ├── main.c            # Punto de entrada principal
│   ├── calculator.c       # Interfaz pública de la calculadora
│   ├── parser.c          # Analizador recursivo descendente
│   ├── lexer.c           # Analizador léxico
│   ├── command.c         # Manejador de comandos
│   ├── logger.c          # Sistema de registro
│   ├── debug.c            # Sistema de depuración
│   └── platform/          # Código específico de plataforma
├── include/               # Archivos de encabezado
│   ├── calculator.h      # Interfaz pública
│   ├── parser.h         # Interfaz del analizador
│   ├── lexer.h          # Interfaz del analizador léxico
│   ├── command.h        # Interfaz de comandos
│   ├── logger.h         # Interfaz del registrador
│   └── debug.h          # Interfaz de macros de depuración
├── test/                  # Pruebas unitarias
├── .vscode/              # Configuración de VS Code
├── CMakeLists.txt        # Configuración de compilación CMake
└── README.md             # Documentación del proyecto
```

## 🚀 Inicio Rápido

### Compilar el Proyecto (CMake)

```bash
# 1. Crear directorio de compilación
mkdir build && cd build

# 2. Configurar según tu plataforma
# Windows MinGW:
cmake -G "MinGW Makefiles" ..

# Windows MSVC:
cmake -G "Visual Studio 17 2022" ..

# Linux/macOS:
cmake ..

# 3. Compilar
cmake --build .
```

### Ejecutar el Programa

```bash
# Windows
./bin/calculator.exe

# Linux / macOS
./bin/calculator
```

### Depuración Interactiva

```bash
# Activar modo de depuración
./bin/calculator --debug

# Usar comandos en el programa
/show process   # Seleccionar nivel de depuración interactivamente
/hide process    # Desactivar salida de depuración
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

## 🧪 Pruebas

El proyecto utiliza CTest para las pruebas.

```bash
# Ejecutar todas las pruebas
ctest --output-on-failure

# Ejecutar suite de pruebas específico
ctest -R calc_tests_error --output-on-failure
```

Suites de pruebas disponibles:
- `calc_tests_all` - Ejecutar todas las pruebas
- `calc_tests_success` - Casos de éxito
- `calc_tests_error` - Casos de error
- `calc_tests_api` - Pruebas de contrato API
- `calc_tests_error_div0` - Pruebas de división por cero

## 🔧 Sistema de Depuración

### Activar en Tiempo de Compilación

Compilar con `-DENABLE_DEBUG=ON`:

```bash
cmake -DENABLE_DEBUG=ON -DCMAKE_BUILD_TYPE=Debug -S . -B build
cmake --build build
```

### Argumentos de Línea de Comandos

| Argumento | Descripción |
|-----------|-------------|
| `--debug` | Activar modo de depuración |
| `--debug-level=N` | Establecer nivel de depuración (1-5) |
| `--debug-module=NAME` | Establecer módulo (lexer/parser/calc/main/all) |

### Niveles de Depuración

| Nivel | Descripción |
|-------|-------------|
| 1. Solo error | Desactivar salida de depuración |
| 2. Aviso+Info | Mostrar información general |
| 3. Mostrar pasos | Mostrar proceso de evaluación de expresiones |
| 4. Traza del analizador | Mostrar detalles del análisis de sintaxis |
| 5. Traza completa | Mostrar cadena de llamadas completa |

### Ejemplo de Salida de Depuración

Entrada `2+3*4` con modo de depuración nivel 5:

```
[Paso 1] Leer número 2
[Paso 2] Leer número 3
[Paso 3] Leer número 4
[Paso 4] 3 * 4 = 12
[Paso 5] 2 + 12 = 14
Expresión: 2+3*4
Resultado: 14
```

## 🤝 Contribuciones

¡Issues y Pull Requests son bienvenidos!

1. Fork este repositorio
2. Crea una rama de característica (`git checkout -b feature/amazing-feature`)
3. Confirma tus cambios (`git commit -m 'Add amazing feature'`)
4. Envía la rama (`git push origin feature/amazing-feature`)
5. Abre un Pull Request

## Licencia

Este proyecto está licenciado bajo la Licencia MIT - consulta el archivo [LICENSE](LICENSE) para más detalles.

---

⭐ Si este proyecto te ayuda, por favor pon una estrella para mostrar tu apoyo.
