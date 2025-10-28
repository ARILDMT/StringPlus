echo "Заапуск CI/CD йоу"

make clean

echo "Так так так"
make all
if [ $? -ne 0 ]; then
    echo "не забилдился,исправляй"
    exit 1
fi

echo "запуск тестов"
make test
if [ $? -ne 0 ]; then
    echo "тесты не прошел исправляй проект или отчислят"
    exit 1
fi

echo "Запуск тестов с покрытием"
if ! command -v gcov >/dev/null 2>&1 || ! command -v genhtml >/dev/null 2>&1; then
    echo "ВНИМАНИЕ: gcov и genhtml не установлены. Пропускаем генерацию отчета о покрытии."
    echo "Для генерации отчета установите gcov и genhtml:"
    echo "  Ubuntu/Debian: sudo apt-get install gcov"
    echo "  MacOS: brew install lcov gcc"
    echo "  Windows (MSYS2): pacman -S mingw-w64-x86_64-gcov"
    echo ""
    echo "Продолжаем выполнение остальных тестов..."
    echo ""
    exit 0
fi

rm -f *.gcda *.gcno *.info
rm -rf report

if ! make gcov_report; then
    echo "Ошибка: Не удалось собрать проект с поддержкой покрытия"
    exit 1
fi

if [ -d "report" ] && [ -f "report/index.html" ]; then
    echo ""
    echo "========================================"
    echo "Отчет о покрытии успешно сгенерирован!"
    echo "Открыть в браузере: file://$(pwd)/report/index.html"
    echo "========================================"
    echo ""
    
    if [ "$(uname)" = "Darwin" ]; then
        open "report/index.html"
    elif [ "$(uname)" = "Linux" ] && [ -n "$DISPLAY" ]; then
        xdg-open "report/index.html"
    elif [ "$(uname -o)" = "Msys" ] || [ "$(uname -o)" = "Cygwin" ]; then
        start "" "report/index.html"
    fi
else
    echo "Ошибка: Не удалось сгенерировать отчёт о покрытии"
    echo "Проверьте, что у вас установлены все необходимые зависимости:"
    echo "- gcc с поддержкой gcov"
    echo "- lcov"
    echo "- genhtml"
    exit 1
fi

echo "запуск мемори чека"
if command -v valgrind >/dev/null 2>&1; then
    valgrind --tool=memcheck --leak-check=full --error-exitcode=1 ./test_s21_string
    if [ $? -ne 0 ]; then
        echo "мемори лик найден!"
        exit 1
    else
        echo "чек прошел красава всё супер"
    fi
else
    if [ "$(uname)" = "Darwin" ]; then
        echo "ВНИМАНИЕ: Valgrind не поддерживается на macOS с Apple Silicon."
        echo "Используйте Xcode Instruments или AddressSanitizer для проверки памяти."
        echo "Компиляция с AddressSanitizer: make CFLAGS='-fsanitize=address -g'"
    else
        echo "валгринд не найден пропуск этого теста"
    fi
fi

echo "CI/CD выполнен успешно!"
echo "автотесты прошли супер ты молодец"
echo "репорт создался тут: file://$(pwd)/report/index.html"
