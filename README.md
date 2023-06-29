# Access control list
## Сборка и запуск
Используется компилятор gcc.

Сборка находится в основной папке.

```
mkdir build && cd build
cmake ..
make
./ACL
```
## Тесты
Тесты представлены в папке Test. 

Чтобы добавить собственные тесты необходимо объявить соответствующую функцию в файле test.h, а после определить ее в файле test.cpp. Добавьте вызов функции в 
try-catch блок функцию run_test.

## Реализация
Класс сущности (кому предоставляем доступ) - Entity:
- get_id() - получение id сущности
  
Класс ресурсы (к чему предоставляем доступ) - Resource:
- get_name() - получение имени ресурса

ACL - шаблонный класс реализации механизма списка контроля доступа
- AddEntity(EntityId const& e, Resource const& r, AccessMode m) - добавление сущности в список с соответ. ресурсом и доступом
- DelEntity(EntityId const& e) - удаление сущности
- GetAccessMode(EntityId const& e, Resource const& r) - получение уровня доступа сущноси к ресурсу
- SetAccessMode(EntityId const& e, Resource const& r, AccessMode m) - изменение доступа сущности к ресурсу
