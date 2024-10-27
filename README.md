# Sistem Embedded untuk Sinyal LED

Proyek ini adalah implementasi dari sistem embedded untuk mengontrol sinyal LED menggunakan mikrokontroler AVR. Sistem ini dapat mengatur sinyal belok kanan, belok kiri, dan sinyal dari atas ke bawah.

## Daftar Isi

- [Pendahuluan](#pendahuluan)
- [Fitur](#fitur)
- [Persyaratan](#persyaratan)
- [Instalasi](#instalasi)
- [Penggunaan](#penggunaan)
- [Struktur Proyek](#struktur-proyek)
- [Lisensi](#lisensi)

## Pendahuluan

Proyek ini bertujuan untuk mengembangkan sistem sinyal LED yang dapat digunakan pada kendaraan atau aplikasi lain yang memerlukan sinyal visual. Sistem ini menggunakan mikrokontroler AVR untuk mengontrol LED berdasarkan input dari tombol.

## Fitur

- Sinyal belok kanan
- Sinyal belok kiri
- Sinyal dari atas ke bawah
- Debounce untuk tombol input

## Persyaratan

- Mikrokontroler AVR (misalnya, ATmega328P)
- LED dan resistor
- Tombol input
- AVR-GCC dan AVRDUDE untuk kompilasi dan pemrograman

## Instalasi

1. **Kloning repositori ini:**

    ```sh
    git clone https://github.com/fsudjatmiko/embedded.git
    cd embedded
    ```

2. **Kompilasi kode:**

    ```sh
    avr-gcc -mmcu=atmega328p -Os -o main.elf main.cpp
    avr-objcopy -O ihex main.elf main.hex
    ```

3. **Unggah ke mikrokontroler:**

    ```sh
    avrdude -c usbtiny -p m328p -U flash:w:main.hex
    ```

## Penggunaan

1. **Hubungkan tombol ke pin PD2, PD3, PD4, dan PD5 pada mikrokontroler.**
2. **Hubungkan LED ke pin PC0 hingga PC5 melalui resistor.**
3. **Nyalakan mikrokontroler.**
4. **Tekan tombol untuk mengaktifkan sinyal yang diinginkan.**

## Struktur Proyek

- `main.cpp`: Kode sumber utama untuk sistem sinyal LED.
- `README.md`: Dokumentasi proyek.
