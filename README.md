# Поиск пересекающихся отрезков

Этот репозиторий содержит реализацию задачи поиска пересекающихся отрезков с использованием двух различных подходов:

## Реализованные подходы

1. **Квадратичный (наивный) алгоритм**  
   Простая реализация, основанная на переборе всех пар отрезков и проверке их пересечения. Временная сложность: `O(n^2)`.

2. **Алгоритм на основе AVL-дерева**  
   Более оптимизированный метод, использующий сбалансированное AVL-дерево для поиска пересечений. Подходит для случаев с большим количеством отрезков, где требуется улучшенная производительность.

## Дополнительная информация
- `README.md` — описание проекта.
- `source_folder/` - тестовые данные и выходные результаты работы алгоритмов( о том как их интерпретировать написано в отчете стр. 5).
- `report.pdf` — полная документация по проекту.

## Как запустить
Для сборки проекта рекомендуется использовать **CMake**. Для этого выполните следующие шаги:

   ```bash
   git clone https://github.com/Torcna/segments-intersect-naive-avl
   cd segment-intersection
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
   ```

## Передача аргументов командной строки

При запуске программы можно передавать различные аргументы командной строки для выполнения тестов:

- `autogen_version` — стандартная версия тестов.
- `autogen_version k_varies` — тест с переменной длиной.
- `autogen_version length_test` — тест с различными длинами отрезков.
- `autogen_version length_varies` — тест с изменяющимися длинами отрезков.

Также, для использования собственных данных, можно передавать файлы:
```bash
AIAS_s.exe source_folder/sample.txt
AIAS_s.exe source_folder/sample2.txt
```
Файлы sample.txt и sample2.txt содержат примеры отрезков, которые можно использовать для тестирования.
Вы можете создать свои отрезки в этом формате, следуя образцу.
Так же можно при компиляции указать ключ, для отображения на консоль результатов работы алгоритмов.
```bash
cmake .. -D visual
```
