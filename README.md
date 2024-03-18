# racing-zadanie_rekrutacyjne
Rozwiązałem zadanie z wykorzystaniem algorytmu Grahama. 
W skrócie algorytm ten polega na:
1. wybraniu punktu o najniższej współrzędnej y lub jeśli jest takich kilka to o najniższej x, jest to punkt startowy który równierz należy do otoczki, 
2. posortowaniu punktów kątowo od najmniejszego kąta (ja użyłem zwykłej funkcji sort i dodatkowej własnej funkcji compareAngle, która porównuje wartości funkcji arc tan)
3. porównaniu 3 kolejnych punktów obliczając ich iloczyn wektorowy, sprawdzamy czy otoczka tworzy "zakręt" w prawo czy w lewo (musi w lewo ponieważ tak posortowaliśmy punkty, a chcemy otrzymać wielokąt wypukły a nie wklęsły)
4. porównujemy punkty i zapisujemy te które tworzą otoczke skręcającą w lewo
