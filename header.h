/* Saya Abdurrahman Al Ghifari mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah 
Struktur Data untuk keberkahanNya maka saya tidak melakukan kecurangan 
seperti yang telah dispesifikasikan. Aamiin. */

// import library yg dibutuhkan
#include <stdio.h> // lib untuk input output
#include <malloc.h> // lib untuk memory alloc dinamis
#include <string.h> // lib untuk mengolah string
#pragma once

// mendeklarasikan variabel global yang dipakai (tujuan agar mempermudah modifikasi data dalam mesin tanpa perlu return nilai)
extern int indeks; // var global untuk menyatakan indeks pada pita
extern int panjangkata; // var global untuk menampung panjang/lenght dari sebuah kata yg sedang digunakan 
extern char ckata[50]; // var untuk menampung kata yg sedang diolah pada mesin
extern int maxlen[100]; // var untuk menampung maxlen dari tiap levenya
extern int maxLevel; // var untuk menyimpan max level dari tree
extern int tahun; // var untuk menyimpan total tahun belajar

// ======================================================
// mendeklarasikan setiap tombol yang ada pada mesin kata
// ======================================================

void STARTKATA(char pita[]); // deklarasi prosedur untuk memulai mesin 

void RESETKATA(); // deklarasi prosedur untuk mereset kata yg sedang ditampung

void INCKATA(char pita[]); // deklarasi prosedur untuk lanjut ke next kata

char* GETCKATA(); // deklarasi fungsi untuk mengembalikan kata yg sedang berjalan ke main

int GETPANJANGKATA(); // deklarasi fungsi untuk mengembalikan nilai panjang dari kata yg digunakan 

int EOPKATA(char pita[]); // deklarasi fungsi untuk mengembalikan nilai batas dari pita
// ======================================================

typedef struct Data{ // deklarasi typedef struct untuk menampung data dari kontainer
    char namaSimpul[100]; // terdiri dari var string nama folder
    char namaParent[100]; // terdiri dari var string nama parrent dari folder
    int waktuBelajar; // terdiri dari var int waktu belajar
    int jumDipelajari; // terdiri dari var int jumlah yg dipelajari
    char daftarPelajaran[10][100]; // terdiri dari var array of string untuk daftar yang dipelajari
}Data; // memberi nama struct

typedef struct Node* Nodeaddress; // deklarasi typedef struct untuk tipe pointer
typedef struct Node{ // deklarasi typedef struct untuk node/simpul dari tree
    Data container; // terdiri dari single char kontainer (ADAPTIF TERGANTUNG SOAL)
    Nodeaddress sibling; // pointer saudara (node lain di parrent yg sama)
    Nodeaddress child; // pointer untuk anak dari node
}Node; // memberi nama struct

typedef struct{ // deklarasi typedef struct untuk tipe tree
    Node *root; // terdiri dari pointer root/akar/induk
}Tree; // memberi nama struct

// deklarasi prosedur untuk menginisialisasi pembuatan tree
void tree_create(Data data, Tree *T);

// deklarasi prosedur untuk menambahkan node/simpul anak
void add_child(Data data, Node *root);

// deklarasi prosedur untuk menghapus keseluruhan cabang pohon
void del_node(Node* root);

// deklarasi prosedur untuk menghapus node/simpul anak
void del_child(char find[], Node* root);

// deklarasi fungsi untuk menemukan suatu simpul berdasarkan isi nya
Node* find_node(char find[], Node* root);

// deklarasi prosedur untuk mencetak tree secara pre order
void print_preorder(Node* root, int level);

// deklarasi fungsi untuk mengubah string menjadi int
int konversiAngka(char ubahSTR[]);

// deklarasi prosedur untuk mencari len max dari tiap level anak pada tree
void cariMaxlen(Node* root, int level);

// deklarasi prosedur untuk mencari path yang diminta
void cariPathKarir(Node* root, char pathTujuan[]);

// deklarasi prosedur untuk mencari total tahun
void cariTahunKarir(Node* root, char pathTujuan[]);