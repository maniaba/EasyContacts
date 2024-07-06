## **EasyContacts**

**EasyContacts** je aplikacija za upravljanje kontakt informacijama. Ova aplikacija omogućava korisnicima da kreiraju, uređuju i upravljaju listom kontakata na jednostavan i efikasan način.

### Dokumentacija

Dokumentaciju možete pronaći u `docs` direktoriju ili možete posjetiti [EasyContacts Dokumentacija](https://maniaba.github.io/EasyContacts/) stranicu.

### Specifikacija: 
1. Struktura projekta
   - Organizovana struktura direktorija: Glavni direktorij sa poddirektorijima za izvornu kôd (src), resurse (resources), biblioteke (libs) i testove (tests).
   - Projekat fajl (pro): .pro datoteka koja definiše projektne postavke, uključujući izvorne datoteke, uključene biblioteke, opcije kompilatora i konfiguracije.
2. Korisnički interfejs (UI)
   - Glavni prozor (MainWindow): Glavna aplikacija sa osnovnim menijem, alatnim trakama i statusnim trakom.
   - Više dijaloga i formi: Dijaloge za različite funkcionalnosti (npr. postavke, informacije o aplikaciji).
   - Korištenje QML: Ako je primjenjivo, QML za kreiranje modernog i responzivnog korisničkog interfejsa.
3. Funkcionalnost
   - Upravljanje podacima: Implementacija osnovnih operacija sa podacima (CRUD operacije - kreiranje, čitanje, ažuriranje i brisanje).
   - Multithreading: Korištenje niti za poboljšanje performansi, posebno za dugotrajne operacije.
   - Asinhrone operacije: Korištenje asinkronih metoda za mrežne operacije ili rad sa bazama podataka.
4. Integracija i eksterni alati
   - Integracija sa bazom podataka: Povezivanje sa lokalnom ili udaljenom bazom podataka, npr. SQLite, MySQL.
   - Korištenje vanjskih biblioteka: Implementacija dodatnih funkcionalnosti kroz eksterne QT kompatibilne biblioteke.
5. Testiranje
   - Jedinično testiranje (Unit Testing): Pisanje jediničnih testova za ključne komponente korištenjem QT Test frameworka.
   - Integraciono testiranje: Testiranje interakcija između različitih modula.
6. Dokumentacija
   - Komentari u kodu: Jasno komentarisanje koda za lakše razumijevanje.
   - Tehnička dokumentacija: Dokument koji objašnjava arhitekturu projekta, korištene tehnologije i način korištenja aplikacije.
7. Upravljanje greškama
   - Rukovanje izuzecima: Implementacija rukovanja izuzecima za sprječavanje padova aplikacije.
   - Logiranje: Korištenje logiranja za praćenje rada aplikacije i dijagnosticiranje problema.
8. Deployment

Kreiranje instalacijskih paketa: Priprema instalacijskih paketa za različite platforme (Windows, macOS, Linux).
Automatizacija build procesa: Korištenje CI/CD alata za automatizaciju build i deployment procesa.
