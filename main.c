/* Saya Abdurrahman Al Ghifari mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah 
Struktur Data untuk keberkahanNya maka saya tidak melakukan kecurangan 
seperti yang telah dispesifikasikan. Aamiin. */

// memasukkan deklarasi di header file ke main
#include "header.h"

int main(){ // deklarasi fungsi main

    char pita[501]; // string untuk menampung inputan user
    Data tempSimpul; // var temp dengan tipedata struct untuk menampung sementara inputan data simpul

    char tempJumDipelajari[5]; // var temp untuk menampung inputan string sementara bagi inputan angka
    char tempWaktuBelajar[5]; // var temp untuk menampung inputan string sementara bagi inputan angka

    Tree T; // deklarasi pembuatan tree

    int n; // var untuk menampung jumlah inputan data
    scanf("%d", &n); // meminta masukkan user

    for (int i = 0; i < n; i++){ // perulangan sebanyak jumlah data yg diminta
    
        scanf(" %500[^\n]s", &pita); // minta masukan user untuk mengisi pita

        STARTKATA(pita); // menjalankan mesin kata
        strcpy(tempSimpul.namaSimpul, GETCKATA()); // mengcopy kata pertama
        INCKATA(pita);
        strcpy(tempSimpul.namaParent, GETCKATA()); // mengcopy kata kedua
        INCKATA(pita);
        strcpy(tempWaktuBelajar, GETCKATA()); // mengcopy kata ketiga
        INCKATA(pita);
        strcpy(tempJumDipelajari, GETCKATA()); // mengcopy kata keempat

        tempSimpul.waktuBelajar = konversiAngka(tempWaktuBelajar); // memanggil fungsi konversi string ke angka untuk inputan waktu belajar
        tempSimpul.jumDipelajari = konversiAngka(tempJumDipelajari); // memanggil fungsi konversi string ke angka untuk inputan jumlah dipelajari

        if (strcmp(tempSimpul.namaParent, "null") == 0){ // jika parent nya null, yang artinya root utama
            
            tree_create(tempSimpul, &T); // panggil prosedur untuk tree create

        }else{ // lainnya jika tree sudah di inisialisasi


            for (int j = 0; j < tempSimpul.jumDipelajari; j++){ // perulangan sebanyak inputan jumlah yg dipelajari
            
                scanf("%s", &tempSimpul.daftarPelajaran[j]); // meminta masukkan

            }

            Node *parent = find_node(tempSimpul.namaParent, T.root); // mencari parent untuk parameter add child

            add_child(tempSimpul, parent); // panggil prosedur add child
            
        }
        
    }

    char pathTujuan[50]; // deklarasi var untuk menampung path yg ingin dituju
    scanf("%s", &pathTujuan); // meminta masukkan user

    cariMaxlen(T.root, 0); // mencari maxlen untuk proses mencetak tree

    for (int i = 0; i < maxLevel; i++){ // perulangan sebanyak kedalaman tree
        
        maxlen[i] = maxlen[i] + maxlen[i - 1] + 1; // jumlahkan len tree nya tiap level nya bertambah

    }
    
    print_preorder(T.root, 0); // mencetak tree 
  
    cariPathKarir(T.root, pathTujuan); // melakukan pruning untuk memotong tree yang bukan tujuan dari anak pertama

    for (int i = 0; i < maxLevel; i++){ // perulangan sebanyak maxlevel
        
        maxlen[i] = 0; // inisialisasikan 0 var array penampung maxlen untuk proses print selanjutnya

    }

    cariMaxlen(T.root, 0); // memanggil prosedur untuk mencari maxlen kembali untuk tree yg sudah di pruning

    for (int i = 0; i < maxLevel; i++){ // perulangan sebanyak maxlevel
        
        maxlen[i] = maxlen[i] + maxlen[i - 1] + 1; // jumlahkan len tree nya tiap level nya bertambah

    }

    print_preorder(T.root, 0); // mencetak tree

    tahun += T.root->container.waktuBelajar; // menjumlahkan tahun untuk root utama

    cariTahunKarir(T.root, pathTujuan); // panggil prosedur cari total tahun untuk anak anak root

    Node *target = find_node(pathTujuan, T.root); // inisialisasi pointer target dengan find node path yang dituju untuk print

    printf("Untuk menjadi %s dibutuhkan waktu %d tahun.\n", target->container.namaSimpul, tahun); // melakukan print akhir

    return 0;
    
}

