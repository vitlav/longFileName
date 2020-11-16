# Very Long FileName в Linux
В проекте приведена работа по исследованию различных файловых систем в Linux на пример максимальной длины имени файлов 
и написанию патча для ядра для приведения данного параметра к единому значению.

## Statfs
Проверка файловых систем выполнялась с помощью стандартной библиотечной функции statfs, которая по пути до файла/директории позволяет узнать информацию о файловой
системе в которой он располагается. 

## Эмуляция раздела диска с необходимой файловой системой
Командой truncate создавался файл размером 1 Гб, вызовом mkfs в этот файл добавлялась рассматриваемая файловая система, затем с помощью команды mount данный файл
монтировался в пустую директорию и на ней запускалась тестовая программа. После выполнения теста вызовом umount раздел отмонтировался и файл с 
директорией удалялись.

## FAT
Результат работы тестовой программы:
```
tf_type: FAT 0x4d44
tf_namelen: 1530
```
Рассмотрим как это значение вычисляется в ядре:

Предел FAT_LFN_LEN равный 255 находится в файле include/uapi/linux/msdos_fs.h
Вычисление значения в фукнции statfs для FAT реализовано следующим образом:
```
f_namelen = (sbi->options.isvfat ? FAT_LFN_LEN : 12) * NLS_MAX_CHARSET_SIZE;
```
Предел NLS_MAX_CHARSET_SIZE, находящегося в файле include/linux/nls.h равняется 6, хотя с ноября 2003 года пятый и шестой байты уже не используются при кодировании, 
для обеспечения совместимости с UTF-16.