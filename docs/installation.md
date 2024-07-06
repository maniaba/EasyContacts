# Instalacija

Ovdje su koraci za instalaciju EasyContacts aplikacije.

## Preuzimanje

Preuzmite aplikaciju iz GitHub repozitorija:

```sh
git clone https://github.com/yourusername/EasyContacts.git
cd EasyContacts
```

## Zavisnosti

Instalirajte potrebne zavisnosti:

- Ako koristite Qt za razvoj aplikacije, osigurajte da imate instaliran Qt Creator. Ako nemate, možete ga preuzeti sa Qt službene stranice.

## Konfiguracija Qt okruženja

Otvorite Qt Creator i učitajte EasyContacts.pro fajl:

- Otvorite Qt Creator.
- Kliknite na "Open File or Project".
- Pronađite i odaberite EasyContacts.pro fajl.
- Konfigurirajte projekt prema vašim potrebama.

## Pokretanje aplikacije
- Pokretanje pomoću Qt Creator-a
- Otvorite projekt u Qt Creator-u.
- Kliknite na "Run" da pokrenete aplikaciju.

##  Postavljanje baze podataka
Aplikacija koristi SQLite bazu podataka za čuvanje informacija o kontaktima. Baza podataka će se automatski kreirati pri prvom pokretanju aplikacije.

Ako želite koristiti drugu bazu podataka (npr. MySQL ili PostgreSQL), potrebno je prilagoditi konfiguraciju u DatabaseManager klasi i osigurati da su odgovarajuće biblioteke instalirane.


#### Nakon ovih koraka, vaša EasyContacts aplikacija bi trebala biti spremna za korištenje. Ako naiđete na bilo kakve probleme tijekom instalacije ili korištenja, pogledajte Rješavanje problema sekciju za dodatnu pomoć.