# ROOT - Zadanie 1

## Opis
Ten projekt zawiera makro napisane w środowisku ROOT do przetwarzania danych zapisanych w pliku binarnym pochodzących z detektora scyntylacyjnego. Celem makra jest umożliwienie przeglądania histogramów sygnałów jeden po drugim z dodatkowymi funkcjami przetwarzania danych.

## Pliki

- "wave_0.dat": Przykładowy plik binarny zawierający dane z detektora 
		(nie został załączony ze względu na wagę przekraczającą możliwości githuba).
- "Wave.C": Kod źródłowy makra ROOT.
- "README.md": Ten plik z opisem projektu.

## Wymagania

- ROOT w wersji >= 6.0.
- Kompilator C++ zgodny z wymaganiami ROOT.

## Instalacja i Uruchomienie

1. Skopiuj pliki projektu do katalogu roboczego.
2. Uruchom środowisko ROOT.
3. Uruchom makro, podając nazwę pliku binarnego jako argument:

   ```
   .x Wave.C("wave_0.dat")

   ```

### Główne funkcjonalności makra:

1. **Otwieranie pliku binarnego:**
   - Sprawdzanie poprawności otwarcia pliku.

2. **Tworzenie histogramu i canvas:**
   - Ustawianie odpowiednich tytułów dla osi i wykresu.

3. **Przetwarzanie danych:**
   - Odczyt danych z pliku binarnego.
   - Konwersja wartości z jednostek ADC na mV (1 mV = 4.096 ADC).

4. **Przeglądanie sygnałów:**
   - Umożliwia przechodzenie do kolejnych sygnałów za pomocą podwójnego kliknięcia na canvas (funkcja `WaitPrimitive()`).

5. **Odejmowanie linii bazowej:**
   - Opcjonalne odejmowanie linii bazowej obliczonej jako średnia z pierwszych 50 próbek.
   - Wyświetlanie wartości linii bazowej na ekranie.

## Instrukcja Obsługi

1. **Uruchamianie makra:**
   Podstawowe użycie polega na podaniu nazwy pliku binarnego:

   ```
   .x Wave.C("wave_0.dat")

   ```

2. **Odejmowanie linii bazowej:**
   Dodaj drugi argument "false", aby dezaktywować odejmowanie linii bazowej:

   ```
   .x Wave.C("wave_0.dat", false)

   ```

3. **Obsługa canvas:**
   - Podwójne kliknięcie na canvas pozwala przejść do następnego sygnału.

## Przykłady

   ### Bez odejmowania linii bazowej:

   ```
   .x Wave.C("wave0.dat", false)

   ```

   ### Z odejmowaniem linii bazowej:

   ``` 
   x Wave.C("wave0.dat")

   ```

   lub


   ``` 
   x Wave.C("wave0.dat", true)

   ```

Wartość linii bazowej zostanie wyświetlona na histogramie.
