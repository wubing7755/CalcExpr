#!/usr/bin/env sh
set -eu

PRESET="ninja-debug"
ENABLE_TIDY=0
SKIP_FORMAT=0
FIX_FORMAT=0
SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
REPO_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)

cd "$REPO_ROOT"

show_usage() {
  echo "Usage: $0 [--preset <name>] [--skip-format] [--enable-tidy]"
  echo "       $0 [preset] [tidy|--tidy]"
}

PRESET_SET=0
while [ "$#" -gt 0 ]; do
  case "$1" in
    --preset)
      if [ "$#" -lt 2 ]; then
        echo "ERROR: --preset requires a value." >&2
        exit 2
      fi
      PRESET="$2"
      PRESET_SET=1
      shift 2
      ;;
    --skip-format)
      SKIP_FORMAT=1
      shift
      ;;
    --fix-format)
      FIX_FORMAT=1
      shift
      ;;
    --enable-tidy|--tidy|tidy)
      ENABLE_TIDY=1
      shift
      ;;
    -h|--help)
      show_usage
      exit 0
      ;;
    -*)
      echo "ERROR: unknown option $1" >&2
      show_usage >&2
      exit 2
      ;;
    *)
      if [ "$PRESET_SET" -ne 0 ]; then
        echo "ERROR: unexpected argument $1" >&2
        show_usage >&2
        exit 2
      fi
      PRESET="$1"
      PRESET_SET=1
      shift
      ;;
  esac
done

if [ "$SKIP_FORMAT" -eq 0 ] && command -v clang-format >/dev/null 2>&1; then
  if [ "$FIX_FORMAT" -ne 0 ]; then
    find include src test -type f \( -name '*.c' -o -name '*.h' \) -print0 \
      | xargs -0 clang-format -i
  else
    find include src test -type f \( -name '*.c' -o -name '*.h' \) -print0 \
      | xargs -0 clang-format --dry-run --Werror
  fi
elif [ "$SKIP_FORMAT" -eq 0 ]; then
  echo "Skipping clang-format: command not found."
fi

cmake --preset "$PRESET"
cmake --build --preset "$PRESET"

if [ "$ENABLE_TIDY" -ne 0 ]; then
  if command -v clang-tidy >/dev/null 2>&1; then
    BUILD_DIR="build/$PRESET"
    if [ -f "$BUILD_DIR/compile_commands.json" ]; then
      # 只检查编译数据库中实际参与构建的 .c 文件，避免平台无关
      # 源文件与条件编译文件在缺少对应编译标志时产生误报。
      if command -v python3 >/dev/null 2>&1; then
        files=$(python3 -c 'import json,sys; print("\n".join(e["file"] for e in json.load(open(sys.argv[1])) if e["file"].endswith(".c")))' "$BUILD_DIR/compile_commands.json")
      else
        files=$(find src test -type f -name '*.c')
      fi
      for f in $files; do
        clang-tidy --warnings-as-errors='*' -quiet -p "$BUILD_DIR" "$f"
      done
    else
      find src test -type f -name '*.c' \
        -exec clang-tidy --warnings-as-errors='*' -quiet --extra-arg=-std=c11 {} -- -Iinclude -Isrc \;
    fi
  else
    echo "Skipping clang-tidy: command not found."
  fi
fi

ctest --preset "$PRESET" --output-on-failure
