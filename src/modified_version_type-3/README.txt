Модификация ТИП-3 от Модификации ТИП-2 отличается только тем,
что на каждом поколении у каждого из паралельно работающих алгоритмов
есть 50% шанс обменять своего лучшего индвида в текущей популяции.

Это реализованно следующим образом, сервер собирает в массив все индивиды, которые прислали клиенты
и возвращает им назад случайный индивид из массива полученных. Полученный индивид встает на место старого.