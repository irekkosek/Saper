# Saper
This is source and documentation for my I semestral final project.  

Politechnika Śląska
Wydział Matematyk Stosowanej
Kierunek Informatyka
Gliwice, 01.10.2020



Programowanie I
projekt zaliczeniowy
"Saper"

Ireneusz Kosek gr. lab. 2/3














	







1. Opis projektu.
Celem projektu będzie stworzenie gry logicznej Saper
2. Wymagania
   -Użytkownik może wybrać rozmiar planszy
   -Użytkownik może wybrać ilość bomb 
   -Program pozwala flagować rozmieszczenie bomb i zlicza ile zostało jeszcze nieoznakowanych
   -Program informuje ile bomb sąsiaduje z polem
   -Program liczy upływ czasu
   -Program rekurencyjnie odsłania pola
3. Przebieg realizacji
W ramach projektu zostały zrealizowane wszystkie założone wcześniej wymagania. 
Projekt końcowy składa się z dwóch plików: saper.cpp i saper.exe
Do generowania położenia bomb użyto algorytmu mt19937
Użyte biblioteki:
-windows.h – zbiór funkcji w Windows API – pozwolił na użycie kolorów w konsoli
-time.h – biblioteka z funkcjami czasu – użyta do naliczania czasu.
-random – biblioteka z generatorami liczb losowych – tutaj wykorzystano generator mt19937
4. Instrukcja użytkownika 
Opis działania stworzonego programu ze zrzutami ekranów ilustrujące sposób działania programu. Krótka instrukcja obsługi
Na początku program pyta nas o rozmiar planszy oraz ilość zadanych min:

 ![image](https://user-images.githubusercontent.com/78158271/150696714-f9b8fb70-865c-4289-bb49-fc21710d6ffa.png)

Następnie wybieramy czy chcemy odkrywać pola czy je flagować

![image](https://user-images.githubusercontent.com/78158271/150696718-4ab2b6d7-74dd-4322-8100-c029c8a94ae0.png)



Po wybraniu stosownego trybu wpisujemy współrzędne w postaci: [kolumna][wiersz]

 ![image](https://user-images.githubusercontent.com/78158271/150696720-afd555cc-5df3-4fd2-ad6b-cdb4e5939bcf.png)

Program pokazuje nam ile zostało jeszcze min, ile czasu minęło i w jakim trybie aktualnie się znajdujemy.

 ![image](https://user-images.githubusercontent.com/78158271/150696721-6fcafacd-c243-451a-981e-27cf004a9a6c.png)


Program kończy się gdy oflagujemy wszystkie bomby lub na jakąś natrafimy

![image](https://user-images.githubusercontent.com/78158271/150696726-cc184094-e903-4a3e-880a-624ece8a49ad.png)
![image](https://user-images.githubusercontent.com/78158271/150696734-02a33d6a-212b-4de2-8996-070a55023f70.png)

Pod koniec program pyta nas czy chcielibyśmy zacząć od nowa.

5. Podsumowanie i wnioski.
Udało się zrealizować wszystkie założenia programu. Największe problemy pojawiały się z początku przy rekurencji,  przy nie wychodzeniu poza zakres, przyjmowaniu danych od użytkownika i sprawdzaniu czy koordynaty są zgodne z oczekiwanym schematem oraz sprawdzaniu warunku zwycięstwa. Program warto by w przyszłości wzbogacić o interfejs graficzny i być może tryb gry z komputerem.  

