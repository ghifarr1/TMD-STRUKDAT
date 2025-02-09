/* Saya Abdurrahman Al Ghifari mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah 
Struktur Data untuk keberkahanNya maka saya tidak melakukan kecurangan 
seperti yang telah dispesifikasikan. Aamiin. */

// memasukkan deklarasi di header file ke mesin
#include "header.h"

// ======================================================
// mendefinisikan setiap tombol yang ada pada mesin kata
// ======================================================

int indeks; // var global untuk menyatakan indeks pada pita
int panjangkata; // var global untuk menampung panjang/lenght dari sebuah kata yg sedang digunakan 
char ckata[50]; // var untuk menampung kata yg sedang diolah pada mesin
int maxlen[100] = {0}; // inisialisasi var array penampung maxlen dgn 0
int maxLevel = 0; // inisialisasi var max level dgn 0
int tahun = 0; // inisialisasi var tahun dgn 0

// mendefinisikan prosedur untuk memulai mesin
void STARTKATA(char pita[]){
    indeks = 0; // inisialisasi indeks
    panjangkata = 0; // inisialisasi panjang kata
    while (pita[indeks] == ' ' || pita[indeks] == '#'){ // cek jika spasi
        indeks++; // skip terus indeksnya
    }
    
    while ((pita[indeks] != ' ') && (pita[indeks] != '#') && (pita[indeks] != ';')){ // cek kalo udh sampe batas akhir
        ckata[panjangkata] = pita[indeks]; // pindahin katanya
        indeks++; // tambah indeks
        panjangkata++; // tambah pj kata
    }
    ckata[panjangkata] = '\0'; // kasih nul termi diakhir
}

// mendefinisikan prosedur untuk mereset kata yg sedang ditampung
void RESETKATA(){
    panjangkata = 0; // reset panjangnya
    ckata[panjangkata] = '\0'; // cut langsung dengan nul termi
}

// mendefinisikan prosedur untuk lanjut ke next kata
void INCKATA(char pita[]){
    panjangkata = 0; // reset panjangnya
    while (pita[indeks] == ' ' || pita[indeks] == '#'){ // cek jika spasi
        indeks++; // skip terus indeksnya
    }
    while ((pita[indeks] != ' ') && (pita[indeks] != '#') && (pita[indeks] != ';')){ // cek kalo udh sampe batas akhir
        ckata[panjangkata] = pita[indeks]; // pindahin katanya
        indeks++; // tambah indeks
        panjangkata++; // tambah pj kata
    }
    ckata[panjangkata] = '\0'; // kasih nul termi diakhir
}

// mendefinisikan fungsi untuk mengembalikan kata yg sedang berjalan ke main
char* GETCKATA(){
    return ckata; // mengembalikan kata
}

// mendefinisikan fungsi untuk mengembalikan nilai panjang dari kata yg digunakan 
int GETPANJANGKATA(){
    return panjangkata; // mengembalikan nilai
}

// mendefinisikan fungsi untuk mengembalikan nilai batas dari pita
int EOPKATA(char pita[]){
    if (pita[indeks] == ';'){ // cek jika akhir dari pita
        return 1; // mengembalikan nilai
    }else{ // jika bukan
        return 0; // mengembalikan nilai
    }
}
// ======================================================


// mendefinisikan prosedur untuk menginisialisasi pembuatan tree
void tree_create(Data data, Tree* T){

    Node *node; // deklarasi pointer node
    node = (Node*) malloc(sizeof(Node)); // membuat alokasi kontainer node sesuai typedefnya
    
    node->container = data; // memindahkan isi kontainer 
    node->sibling = NULL; // pointer sibling/saudara di nullkan
    node->child = NULL; // pointer anak dinullkan

    T->root = node; // hubungkan root ke node

}

// mendefinisikan prosedur untuk menambahkan node/simpul anak
void add_child(Data data, Node* root){

    // Condition to check if the root existed
    if (root != NULL){ // cek jika root nya tidak null

        // jika simpul root tidak kosong, berarti dapat ditambahkan simpul anak
        Node* new; // deklarasi pointer baru
        new = (Node*) malloc(sizeof(Node)); // membuat alokasi kontainer baru sesuai typedefnya

        new->container = data; // memindahkan isi kontainer 
        new->child = NULL; // pointer child nya di nullkan 
        
        // Condition if the parent node doesn't have a child 
        if (root->child == NULL){ // cek jika root nya belum punya anak

            // jika simpul root belum memiliki simpul anak maka simpul baru menjadi anak pertama
            new->sibling = NULL; // pointer sibling si baru di nullkan
            root->child = new; // pointer child dari root hubungkan ke baru

            // Otherwise, we'll have to append it to the end of the child list
        }else{ // Condition where there's only 1 child / lainnya jika pointer child dari root sudah memiliki anak

            if (root->child->sibling == NULL){ // cek apakah anak dari root pointer siblingnya null

                // jika simpul root memiliki anak yang belum memiliki saudara, maka simpul baru menjadi anak kedua
                new->sibling = root->child; // pointer sibling dari baru ke anak yg ditunjuk pointer child dari root
                root->child->sibling = new; // pointer sibling dari anak yg ditunjuk root hubungkan ke baru

            }else{

                // Loop through to find the last child of the list
                Node* last = root->child; // deklarasi pointer last untuk mencari node terakhir

                /* mencari simpul anak terakhir karena akan dikaitkan dengan simpul baru sebagai simpul anak terakhir
                yang baru, simpul anak terakhir adalah yang memiliki sibling simpul anak pertama, maka selama belum
                sampai pada simpul anak terakhir, penunjuk last akan berjalan ke simpul anak berikutnya*/

                while (last->sibling != root->child){ // selagi pointer sibling dari node tidak menunjuk ke anak pertama

                    last = last->sibling; // iterasi terus pointer last nya

                }

                new->sibling = root->child; // pointer sibling dari baru hubungkan ke anak yg ditunjuk child dari root
                last->sibling = new; // pointer sibling dari node yg ditunjuk last hubungkan ke baru

            }

        }

    }

}

// mendefinisikan prosedur untuk menghapus keseluruhan cabang pohon
void del_node(Node* root){

    // Condition to check if root existed
    if (root != NULL){ // cek jika root nya tidak null / jika simpul root tidak kosong

        // Condition to check if the parent has a child
        if (root->child != NULL){ // cek jika pointer child dari root nya tidak null

            // Condition where there's only 1 child
            if (root->child->sibling == NULL){ // cek jika pointer sibling dari child yg ditunjuk root nya tidak null

                // jika hanya memiliki satu simpul anak
                del_node(root->child); // jalankan pemanggilan prosedur secara rekursif
                free(root); // diakhir free root nya

                // Condition where there are multiple children
            }else{ // lainnya jika memiliki banyak anak

                Node* current; // deklarasi pointer pembantu
                Node* target; // deklarasi pointer untuk memegang node yg selanjutnya di proses
                
                // Loop through to delete the children sequentially
                current = root->child; // inisialisasi bantu dimulai dari anak pertama

                while (current->sibling != root->child){ // selagi pointer sibling dari node tidak menunjuk ke anak pertama

                    target = current; // pindahkan pointer proses ke bantu
                    current = current->sibling; // bantu nya di next ke next node
                    del_node(target); // jalankan pemanggilan prosedur secara rekursif

                }

                if (current != NULL) del_node(current);
                // Delete isolated child
                free(root);

            }
            
        } else free(root); // Delete isolated parent

    }

}

// mendefinisikan prosedur untuk menghapus node/simpul anak
void del_child(char find[], Node* root){

    // Condition where the root exist
    if (root != NULL && find != NULL){ // cek jika root nya tidak null

        Node* current = root->child; // deklarasi pointer hapus dan inisialkan dimulai dari anak pertama

        if (current != NULL){ // jika pointer hapus tidak null

            // Condition where there's only 1 child 
            if (current->sibling == NULL){ // jika pointer sibling dari hapus tidak null

                // Found condition / jika hanya mempunyai satu anak
                if (strcmp(root->child->container.namaSimpul, find) == 0){ // cek apakah isi dari node nya sesuai dgn yg mau dihapus

                    del_node(root->child); // jika iya jalankan prosedur penghapusan rekursif
                    root->child = NULL; // diakhir pointer child dari root nya di nullkan

                    // jika isi tidak sesuai / proses jika node tidak ditemukan
                }else printf("[!] Node %s has only one child (%s) and it's not the target", root->container.namaSimpul, root->child->container.namaSimpul);

                // Condition where there are multiple children / jika mempunyai banyak anak
            }else{

                // jika memiliki lebih dari satu simpul
                Node* prev = NULL; // deklarasi pointer pev dan inisialkan null

                // mencari simpul yang akan dihapus
                int found = 0; // var mark jika ketemu
                
                // Loop until every child is checked / perulangan selagi pointer sibling dari hapus tidak menunjuk anak pertama dan mark nya masi 0
                while (current->sibling != root->child && found != 0){

                    // Found condition 
                    if (strcmp(root->child->container.namaSimpul, find) == 0) found = 1; // cek jika isi nya sesuai == mark menyala
                    else{ // jika isi tidak sesuai

                        prev = current; // pindahkan prev ke hapus
                        current = current->sibling; // hapus nya di next ke sibling selanjutnya

                    }
                }
                
                // Check the last remaining child, if it's the target / memproses simpul anak terakhir karena belum terproses dalam pengulangan
                if (strcmp(root->child->container.namaSimpul, find) == 0) found = 1; // selagi ketemu masi 0 dan isi sesuai == mark menyala
                if (found == 1){ // jika mark menyala

                    Node* last = root->child; // deklarasi pointer last inisialkan ke anak pertama
                    
                    // Loop throught to the last child
                    /* mencari simpul anak terakhir untuk membantu proses
                    atau pemeriksaan jika yang dihapus nantinya anak terakhir */
                    while (last->sibling != root->child){ // perulangan sampai anak terakhir

                        last = last->sibling; // iterasi pointer lastnya

                    }
                    
                    // Prev is not initialized since the target is root->child in the initial loop
                    if (prev == NULL){ // jika prev nya masih null

                        // Condition where there is only 2 children
                        if (current->sibling == last && last->sibling == root->child){ // jika simpul yang dihapus anak pertama

                            // jika hanya ada dua anak
                            root->child = last; // pointer child dari root hubungkan ke anak last
                            last->sibling = NULL; // pointer sibling dari anak last di null

                            // Condition where the children count is above 2
                        }else{ // lainnya jika anak nya lebih dari 2

                            // jika memiliki simpul anak lebih dari dua simpul 
                            root->child = current->sibling; // pointer child dari root hubungkan ke node sibling dari hapus
                            last->sibling = root->child; // pointer sibling dari anak last hubungkan ke anak pertama 

                        }

                        // Normal last child condition
                    }else{

                        // Condition where target is last, but there's only 2 children
                        // cek apakah prev nya di anak pertama
                        if (prev == root->child && last->sibling == root->child){

                            // jika hanya ada dua simpul anak dan yang dihapus adalah simpul anak kedua 
                            root->child->sibling = NULL; // pointer sibling dari anak pertama di nullkan

                        }else{ // lainnya jika prev nya bukan di anak pertama

                            /* jika yang dihapus bukan simpul anak pertama dan simpul root
                            memiliki simpul anak lebih dari dua simpul */
                            prev->sibling = current->sibling; // pointer sibling dari prev hubungkan ke pointer sibling dari hapus
                            current->sibling = NULL; // pointer sibling dari hapus di nullkan

                        }

                    }

                    del_node(current); // menjalankan prosedur penghapusan rekursif

                    // lainnya jika isi tidak ketemu
                }
                // else printf("[!] Node with the name %s is not found\n", current->container.namaSimpul); // proses jika isi node tidak ditemukan

            }

        }

    }

}

// mendefinisikan fungsi untuk menemukan suatu simpul berdasarkan isi nya
Node* find_node(char find[], Node* root){

    Node* result = NULL; // deklarasi pointer hasil inisialkan null

    // Condition where root exists
    if (root != NULL){ // cek jika root nya tidak null

        // Found condition
        if (strcmp(root->container.namaSimpul, find) == 0) result = root; // cek jika isi dari root sesuai yg diminta ==  pindahkan pointer hasil ke root

        else{ // jika isi dari root bukan yg diminta

            Node* current = root->child; // deklarasi pointer bantu di inisialkan dari anak pertama

            // Condition where current exists
            if (current != NULL){ // jika bantu nya tidak null

                // Condition where current is an only child
                if (current->sibling == NULL){ // cek jika sibling dari bantu null

                    // jika memiliki satu simpul anak
                    if (strcmp(current->container.namaSimpul, find) == 0) result = current; // Found condition / cek jika isi yg ditunjuk bantu sesuai == pindahkan hasil ke bantu
                    else result = find_node(find, current); // If not found, look for it recursively / lainnya jika tidak sesuai

                    // Condition where there are multiple children
                }else{ // lainnya jika memiliki sibling

                    // jika memiliki banyak simpul anak
                    int found = 0; // var mark

                    // perulangan selagi pointer sibling tidak menunjuk anak pertama dan mark masih 0
                    // Check each child of root
                    while (current->sibling != root->child && found == 0){

                        // Found condition
                        if (strcmp(current->container.namaSimpul, find) == 0){ // cek apakah isi sesuai 

                            result = current; // hasil pindahkan ke bantu
                            found = 1; // mark menyala
                            
                            // If not found, search recursively and laterally
                        }else{ // jika tidak

                            result = find_node(find, current); // panggil fungsi rekursif untuk menemukan hasil
                            current = current->sibling; // iterasi bantu ke next sibling
                            if (result != 0) found = 1;

                        }

                    } 

                    // memproses simpul anak terakhir karena belum terproses dalam pengulangan
                    // Process the last node, by now current should point to the last sibling 
                    if (found == 0){ // jika mark masih off

                        if (strcmp(current->container.namaSimpul, find) == 0) result = current; // Found condition / cek apakah isi dari bantu sesuai == pindahkan hasil ke bantu
                        else result = find_node(find, current); // If not found, look for it recursively / jika tidak sesuai == panggil fungsi rekursif untuk menemukan hasil

                    }

                }

            }

        }

    }

    return result; // kembalikan pointer hasil

}

// mendefinisikan prosedur untuk mencari len max dari tiap level anak pada tree
void cariMaxlen(Node* root, int level){

    // Condition where root exist
    if (root != NULL){ // cek jika root tidak null
            
        int currentLenSimpul = strlen(root->container.namaSimpul) + strlen("tahun") + 6; // tampung len awal di var temp untuk current simpul
        
        // cari maxlen nya pada level tersebut
        if (maxlen[level] < currentLenSimpul){ 
            
            maxlen[level] = currentLenSimpul;

        }

        // cek apakah simpul memiliki isi yang dipelajari
        if (root->container.jumDipelajari > 0){
            
            // perulangan sebanyak jumlah yang dipelajari
            for (int i = 0; i < root->container.jumDipelajari; i++){
                
                int currentLenIsi = strlen(root->container.daftarPelajaran[i]) + 3; // tampung len awal di var temp untuk current simpul
                
                // cari maxlen nya pada level tersebut
                if (maxlen[level] < currentLenIsi){
            
                    maxlen[level] = currentLenIsi;

                }

            }

        }

        Node* current = root->child; // deklarasi pointer bantu dan inisialkan dari anak pertama

        // Check if current node exists
        if (current != NULL){ // jika bantu nya tidak null

            // Condition where current is the only child
            if (current->sibling == NULL){ // cek jika pointer siblingnya null (1 anak)
        
                cariMaxlen(current, level + 1); // panggil prosedur rekursif untuk menelusuri node

                // Condition where there are multiple children
            }else{ // jika pointer sibling tidak null (banyak anak)

                // jika memiliki banyak simpul anak
                // Print preorder for each sibling / mencetak simpul anak
                while (current->sibling != root->child){ // selagi belum sampai ke anak terakhir
                    
                    cariMaxlen(current, level + 1); // panggil prosedur rekursif untuk menelusuri node
                    current = current->sibling; // iterasi pointer bantu ke next sibling

                }

                // memproses simpul anak terakhir karena belum terproses dalam pengulangan
                // Print the last sibling
            
                cariMaxlen(current, level + 1); // panggil prosedur rekursif untuk menelusuri node

            }

        }

    }

    // cari juga max dari level nya
    if (maxLevel < level){ 
        
        maxLevel = level;

    }
    
}

// mendefinisikan prosedur untuk mencetak tree secara pre order
void print_preorder(Node* root, int level){

    // Condition where root exist
    if (root != NULL){ // cek jika root tidak null

        if (level > 0){ // jika level tree lebih besar dari 0
            
            // cetak spasi nya 
            for (int i = 0; i < maxlen[level - 1]; i++){
                
                printf(" ");

            }
            

        }
        
        printf("[%s][%d tahun]\n", root->container.namaSimpul, root->container.waktuBelajar); // cetak isi terlebih dahulu

        // perulangan sebanyak jumlah yang dipelajari
        for (int i = 0; i < root->container.jumDipelajari; i++){

            if (level > 0){ // jika level tree lebih besar dari 0
            
                // cetak spasi nya
                for (int i = 0; i < maxlen[level - 1]; i++){
                    
                    printf(" ");

                }
                

            }
            
            // cetak isi yang dipelajari
            printf(" - %s\n", &root->container.daftarPelajaran[i]);

        }

        printf("\n"); // newline

        Node* current = root->child; // deklarasi pointer bantu dan inisialkan dari anak pertama

        // Check if current node exists
        if (current != NULL){ // jika bantu nya tidak null

            // Condition where current is the only child
            if (current->sibling == NULL){ // cek jika pointer siblingnya null (1 anak)

                // jika memiliki satu simpul anak
                print_preorder(current, level + 1); // panggil prosedur rekursif untuk menelusuri node

                // Condition where there are multiple children
            }else{ // jika pointer sibling tidak null (banyak anak)

                // jika memiliki banyak simpul anak
                // Print preorder for each sibling / mencetak simpul anak
                while (current->sibling != root->child){ // selagi belum sampai ke anak terakhir

                    print_preorder(current, level + 1); // panggil prosedur rekursif untuk menelusuri node
                    current = current->sibling; // iterasi pointer bantu ke next sibling

                }

                // memproses simpul anak terakhir karena belum terproses dalam pengulangan
                // Print the last sibling
                print_preorder(current, level + 1); // panggil prosedur rekursif untuk menelusuri node

            }

        }

    }

}

// mendefinisikan fungsi untuk mengubah string menjadi int
int konversiAngka(char ubahSTR[]){

    int result = 0;// inisialisasi var penampung hasil

    if (strcmp(ubahSTR, "1") == 0){ // cek jika string nya 1
        
        result = 1; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "2") == 0){ // cek jika string nya 2
    
        result = 2; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "3") == 0){ // cek jika string nya 3
    
        result = 3; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "4") == 0){ // cek jika string nya 4
    
        result = 4; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "5") == 0){ // cek jika string nya 5
    
        result = 5; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "6") == 0){ // cek jika string nya 6
    
        result = 6; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "7") == 0){ // cek jika string nya 7
    
        result = 7; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "8") == 0){ // cek jika string nya 8
    
        result = 8; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "9") == 0){ // cek jika string nya 9
    
        result = 9; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "10") == 0){ // cek jika string nya 10
    
        result = 10; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "11") == 0){ // cek jika string nya 11
    
        result = 11; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "12") == 0){ // cek jika string nya 12
    
        result = 12; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "13") == 0){ // cek jika string nya 13
    
        result = 13; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "14") == 0){ // cek jika string nya 14
    
        result = 14; // masukan ke var hasil

    }else if (strcmp(ubahSTR, "15") == 0){ // cek jika string nya 15
    
        result = 15; // masukan ke var hasil

    }
    
    return result; // kembalikan hasil

}

// mendefinisikan prosedur untuk mencetak tree secara pre order
void cariPathKarir(Node* root, char pathTujuan[]){  

    int mark; // var mark untuk mengisi kekosongan

    // Condition where root exist
    if (root != NULL){ // cek jika root tidak null

        Node* current = root->child; // deklarasi pointer bantu dan inisialkan dari anak pertama

        // Check if current node exists
        if (current != NULL){ // jika bantu nya tidak null

            // Condition where current is the only child
            if (current->sibling == NULL){ // cek jika pointer siblingnya null (1 anak)

                // jika memiliki satu simpul anak
                mark = 1; // tidak perlu dilakukan pemotongan jika anak 1, ubah mark saja

                // Condition where there are multiple children
            }else{ // jika pointer sibling tidak null (banyak anak)

                Node *current = root->child; // deklarasi pointer current dr root child
                Node *temp = NULL; // deklarasi pointer temp inisialkan null

                // jika memiliki banyak simpul anak
                while (current->sibling != root->child){ // selagi belum sampai ke anak terakhir


                    Node *target = find_node(pathTujuan, current); // cari target dengan find node lalu masukan ke pointer target

                    if (target == NULL){ // cek jika targetnya null
                        
                        del_node(current); // maka panggil prosedur del node untuk mendelete simpul

                    }else{ // jika target ditemukan

                        temp = current; // pindahkan current nya ke temp

                    }

                    current = current->sibling; // iterasi pointer bantu ke next sibling

                }

                // memproses simpul anak terakhir karena belum terproses dalam pengulangan
                Node *target = find_node(pathTujuan, current); // cari target dengan find node lalu masukan ke pointer target

                if (target == NULL){ // cek jika targetnya null
                    
                    del_node(current); // maka panggil prosedur del node untuk mendelete simpul

                }else{ // jika target ditemukan

                    temp = current; // pindahkan current nya ke temp

                }

                root->child = temp; // pindahkan pointer root child menjadi menunjuk temp
                root->child->sibling = NULL; // lalu putus sibling nya

            }

        }

    }

}

// mendefinisikan prosedur untuk mencetak tree secara pre order
void cariTahunKarir(Node* root, char pathTujuan[]){  

    // Condition where root exist
    if (root != NULL){ // cek jika root tidak null

        Node* current = root->child; // deklarasi pointer bantu dan inisialkan dari anak pertama

        // Check if current node exists
        if (current != NULL){ // jika bantu nya tidak null                   

            // Condition where current is the only child
            if (current->sibling == NULL){ // cek jika pointer siblingnya null (1 anak)

                // jika memiliki satu simpul anak
                Node *target = find_node(pathTujuan, current); // cari target dengan find node lalu masukan ke pointer target  

                if (target != NULL){ // jika target ditemukan
                    
                    tahun += current->container.waktuBelajar; // jumlahkan tahunnya

                }

                cariTahunKarir(current, pathTujuan); // panggil rekursif prosedur cari total tahun

                // Condition where there are multiple children
            }else{ // jika pointer sibling tidak null (banyak anak)

                // jika memiliki banyak simpul anak
                while (current->sibling != root->child){ // selagi belum sampai ke anak terakhir


                    Node *target = find_node(pathTujuan, current); // cari target dengan find node lalu masukan ke pointer target

                    if (target != NULL){ // jika target ditemukan
                        
                        tahun += current->container.waktuBelajar; // jumlahkan tahunnya

                    }

                    cariTahunKarir(current, pathTujuan); // panggil rekursif prosedur cari total tahun
                    current = current->sibling; // iterasi pointer bantu ke next sibling

                }

                // memproses simpul anak terakhir karena belum terproses dalam pengulangan
                Node *target = find_node(pathTujuan, current); // cari target dengan find node lalu masukan ke pointer target 

                if (target != NULL){ // jika target ditemukan
                    
                    tahun += current->container.waktuBelajar; // jumlahkan tahunnya

                }

                cariTahunKarir(current, pathTujuan); // panggil rekursif prosedur cari total tahun

            }

        }

    }

}