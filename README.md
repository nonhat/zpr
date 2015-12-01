# zpr
Birds project

WAŻNE: Po uruchomieniu serwera aplikacja dostępna jest pod http://adres_hosta/game/

Boxing - C++ - cos do fizyki 2D
test do kompilacji wymaga sdl2

Wiev - HTML/js - "sucha" realizacja widoku programu, wystepuje tymczasowo w niemal identycznej formie w szablonach i statycznych plikach Django

Komunikacja - txt - informacje o rozmowach miedzy klientem a serwerem

Model - C++ - wykorzystuje intensywnie Boxing do wytworzenia swiata gry. Udostępnie funkcje przez Boost.Python do Django.

birdsDjango - serwer aplikacji, kontroler; wykorzystuje Django do nawigacji po stronach. Jego prosty serwer www jest w chwili obecnej uzywany do testowania programu.

Instalacja Django:
wykorzystujemy tylko django oraz django-extensions. Wykorzystujemy python 3.5. Do startu serwera nalezy pod wirtualnym srodowiskiem w katalogu birdsDjango wywolac: .manage.py runserver 0.0.0.0:80 (adres opcjonalny, ale wtedy bedzie widoczny tylko na localhost:8000)

Kompilacja:
SCons - niestety testowany tylko na linuxie - kompiluje graficzny test OpenGL/SDL2 z Boxing oraz zwykla biblioteke wspoldzieloną z Boxing i Model.
