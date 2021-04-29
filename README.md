# Self referential structure

_Self Referential structure_ adalah structur yang didalamnya memiliki pointer yang _pointing_ ke dirinya sendiri

```c
struct abc {
    int a;
    char b;
    struct abc *self;
}
```

# Membuat linked list satu node

Setidaknya ada 2 elemen di dalam struct yaitu data dan pointer keduanya memiliki tipe data yang berbeda data bisa berupa char int short dll sedangkan link berupa pointer. Di dalam node hanya boleh berisi satu pointer saja.

## Contoh

```c
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;

};

int main (){
    struct node *head = NULL;
    head = (struct node*)malloc(sizeof(struct node));

    head->data = 45;
    head->link = NULL;

    printf("%d", head->data);
    printf("%d", head->link);

}
```

Keterangan :

1. #include `<stdlib.h>` diperlukan untuk bisa menggunakan malloc function.
2. Pada function `main()` kita deklarasikan pointer `head` dengan tipe data `struct node` yang telah kita buat diatas yang sementara diisi dengan NULL, karena selanjutnya kita akan mengisinya dengan alamat dari node yang dibuat dengan `malloc()`.
3. Selanjutnya kita isi pointer `head` dengan alamat dari node yang baru saja dibuat.
4. Kemudian kita isi `data` dan `link` dengan bantuan pointer `head`

```c
head->data = 45;
head->link = NULL;
```

Cara kerjanya head akan pointing ke `data` & `link` yang berarti itu mengakses nilai (_dereferencing_) dari kedua elemen tersebut, kemudian mengisi nilainya dengan nilai/value baru.

# Membuat linked list 2 node

Bagaimana jika ingin menambahkan node kedua? Kita tahu bahwa function `malloc()` akan mengalokasikan memory untuk node. Pada node pertama alamat memorynya disimpan oleh pointer `head`.

```c
struct node *head = malloc(sizeof(struct node));
```

Lalu bagaimana jika kita ingin menambahkan node kedua? Kita pesan memory lagi untuk node kedua dengan `malloc()` dan membuat pointer yang akan menampung alamat memory dari node kedua tersebut.

```c
struct node *current = malloc(sizeof(struct node));
```

> node baru terbentuk yang alamat memorynya disimpan dalam pointer `current`

Sampai disini kita berhasil membuat node kedua, tapi `link` pada node pertama tidak menyimpan alamat memory node kedua sehingga kedua node tersebut belum tersambung, Jadi kita harus mengisi nilai pada link (dari yang tadinya NULL) dengan alamat memory node kedua.

```c
head->link = current;
```

Kode lengkapnya :

```c
struct node {
    int data;
    struct node *link;

};

int main (){
    struct node *head = NULL;
    head = malloc(sizeof(struct node));

    head->data = 45;
    head->link = NULL;

    struct node *current = malloc(sizeof(struct node));
    current->data = 98;
    current->link = NULL;
    head->link = current;


    printf("%d - ", head->data);
    printf("%d", current->data);

}
```

# Membuat linked list 3 node

Ada 2 cara untuk membuat banyak node

## Cara Pertama

Sama seperti pada saat kita membuat node kedua dari sebelumnya. Dengan membuat malloc yang baru dan pointer yang menyimpan alamat node tersebut kita dapat membuat node ketiga dan seterusnya. Tetapi ada satu masalah disini, bayangkan jika kita ingin membuat banyak node, akan begitu merepotkan jika kita secara manual membuat malloc satu persatu.

```c
struct node *current2 = malloc(sizeof(struct node));
...
struct node *current3 = malloc(sizeof(struct node));
```

## Cara kedua

Ada cara yang lebih baik disini dengan metode ini, tetapi kita harus memahami terlebih dahulu arti dari `head->link`.
`head->link` atau `(*head).link` akan mengakses (_Dereferencing_) _data field_ `link` dari struct node dan mengisinya dengan nilai baru yaitu berupa alamat memory dari link node selanjutnya (jika ada).

```c
head->link = current; // Ex. 1000
current->link = current2; // 2000
current2->link = NULL; // 3000
```

Lalu apa yang dimaksud dengan `head->link->link`? Jika kita tulis `head` saja maka akan merujuk pada alamat memory dari node itu sendiri yaitu 1000 (`head->data`) dengan value 45, tapi jika kita berikan _arrow_ `head->link` maka pointer `head` akan menyimpan data berupa alamat memory dari node selanjutnya (dalam contoh 2000) maka `head->link` (2000) dengan value 98.

Sehingga dari sini dapat kita jelaskan arti dari `head->link->link` yaitu head->link menyimpan 2000 (alamat memory node selanjutnya) sehingga Pointer akan berpindah ke alamat tersebut, kemudian akan terjadi _dereferencing_ lagi yaitu mengakses _field_ `link` dari node kedua tersebut (3000), 3000 merupakan alamat memory dari node ketiga sehingga pointer akan berpindah kesana dan seterusnya.

Sehingga kita tidak perlu membuat pointer-pointer baru karena dengan hanya melalui pointer `head` kita dapat mengakses alamat memory dari masing masing node dengan `head->link->link`.

head : 1000;
head->link : 2000;
head->link->link : 3000;
head->link->link->link : NULL;

```c
int main (){
    struct node *head = NULL;
    head = malloc(sizeof(struct node));

    head->data = 45;
    head->link = NULL;

    struct node *current = malloc(sizeof(struct node));
    current->data = 98;
    current->link = NULL;
    head->link = current;

    current = malloc(sizeof(struct node));
    current->data = 3;
    current->link = NULL;

    head->link->link = current;
}
```

# Inserting node at the beginning

Kita ingin menyisipkan node 3 pada urutan pertama (sebagai head) ke dalam list yang sudah ada sebelumnya yaitu

```c
node 1 =  45(1000);
node 2 =  98(2000);
node 3 =  3(3000);
```

> Berurutan : data, alamat memory

Bagaimana menjadikan node 3 pada urutan pertama?

1. Pertama kita harus meng-update nilai dari link pada node 3 yang sebelumnya bernilai NULL menjadi 1000 (alamat node pertama).

```c
ptr->link = head;
```

Node 3 menjadi urutan 1 dan node 1 menjadi urutan 2

2. Karena node 1 berubah urutan menjadi urutan kedua maka kita harus ubah pointer yang sebelumnya pointing ke node 1 menjadi pointing ke node 3, karena node 3 sekarang menjadi head

```c
head = ptr;
```

Catatan penting :
Kita **tidak** bisa melakukan _assignment_ `head = ptr` sebelum `ptr->link=head` karena jika kita melakukan _assignment_ terhadap `head=ptr` maka artinya kita tidak bisa melakukan _assignment_ `ptr->link=head` karena node 3 sudah diambil alih oleh `head` jadi pointer `ptr` tidak punya wewenang untuk mengubah nilai dari node 3, perintah `ptr->link=head` jelas tidak berlaku. Jadi urutan sangat penting disini.

```c
ptr->link = head;
head = ptr;
```

Kode Program :

```c
int main(){
    struct node *head = malloc(sizeof(struct node));
    head->data = 45;
    head->link = NULL;

    struct node *ptr = malloc(sizeof(struct node));
    ptr->data = 98;
    ptr->link = NULL;

    head->link = ptr;

    int data = 3;

    head = add_beg(head, data);
    ptr = head;
    while(ptr != NULL){
        printf("%d", ptr->data);
        ptr = ptr->link;
    }
}
```

Keterangan :

1. Pertama kita buat node menggunakan `malloc()` dan mengisikan data beserta linknya

```c
struct node *head = malloc(sizeof(struct node));
head->data = 45;
head->link = NULL;
```

2. Selanjutnya kita buat node kedua

```c
struct node *ptr = malloc(sizeof(struct node));
ptr->data = 98;
ptr->link = NULL;
```

3. Kemudian kita isikan `head->link` dari yang tadinya `NULL` menjadi link yang menyimpan alamat memory node kedua

```c
head->link = ptr;
```

Sehingga kedua node diatas tersambung

4. Selanjutnya kita buat data baru yang akan menjadi node 3

```c
int data = 3;
```

5. Pada function `add_beg()` berfungsi untuk menyisipkan suatu node menjadi urutan pertama

```c
struct node* add_beg(struct node* head, int d){
    struct node *ptr = malloc(sizeof(struct node));
    ptr->data = d;
    ptr->link = NULL;

    ptr->link = head;
    head = ptr;
    return head;
}
```

function `add_beg()` menerima argumen `head`, dan `int d` yang kemudian di dalamnya kita membuat node dengan dengan pointer `*ptr` dan di dalam struct node tersebut kita berikan nilai

```c
ptr->data = d;
ptr->link = NULL;

```

link pada node `ptr` tersebut lalu kita isi dengan alamat memory dari `head` yang merupakan node pertama, jadi node 1 berada diurutan kedua dan node 3 menjadi yang pertama.

```c
ptr->link = head;
head = ptr;
```

pointer `head` menyimpan alamat memory dari node 3, jadi node 3 resmi menjadi node 1.

6. Karena kita akan menghitung berapa list yang terdapat dalam program kita maka disinilah fungsi dari `ptr` yaitu untuk menelusuri keseluruhan dari list yang telah kita buat dan menampilkan hasilnya ada berapa list disana. Untuk melakukan tugas itu maka kita gunakan `while`

```c
ptr = head;
while(ptr != NULL){
    printf("%d", ptr->data);
    ptr = ptr->link;
}
```

Selama `ptr` tidak menemui `NULL` (tidak ada node list) maka perulangan berhenti 7. Ouput :

```c
3 45 98
```

# Contoh lain linked list

```c
struct node{
int value;
struct node* next;
};

typedef struct node node_t;

void printlist(node_t *head){
node_t *temporary = head;

    while(temporary != NULL){
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");

};

int main(){
node_t n1, n2, n3;
node_t \*head;

    n1.value = 45;
    n2.value = 8;
    n3.value = 32;

    // link them up
    head = &n3;
    n3.next = &n2;
    n2.next = &n1;
    n1.next = NULL; // so we know when to stop

    printlist(head);

}

```

1. Pertama kita akan membuat struct node yang berisi int value dan node yang menyimpan alamat node selanjutnya

```c
struct node{
    int value;
    struct node* next;
};
```

Dengan keyword `typedef` maka kita bisa menggantikan penulisan `struct node` menjadi lebih simple dengan hanya cukup menuliskan node_t.

```c
typedef struct node node_t;
```

2. Membuat 3 `node_t` dengan variable `n1`, `n2`, `n3` dan pointer `*head`

```c
int main(){
    node_t n1, n2, n3;
    node_t *head;

    n1.value = 45;
    n2.value = 8;
    n3.value = 32;
    .....
}

```

3. Kemudian kita menggabungkan ketiga node diatas dengan mengambil masing masing alamat memory dari value masing masing node

```c
    head = &n3;
    n3.next = &n2;
    n2.next = &n1;
    n1.next = NULL; // so we know when to stop
```

Pointer `head` menyimpan alamat memory dari `n3` (32).
Pointer `n3` menyimpan alamat memory dari `n2` (8).
Pointer `n2` menyimpan alamat memory dari `n1` (45).
Pointer `n1` menyimpan alamat memory NULL.

4. Selanjutnya kita ingin menampilkan hasil berupa list yang tersusun dari linked list yang telah kita buat.

```c
void printlist(node_t *head){
    node_t *temporary = head;

    while(temporary != NULL){
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
};
```

Dengan while maka node yang telah dibuat dapat ditampilkan secara berurutan sampai kondisi `while( temporary!=NULL)` tercapai. Pertama kita isi pointer `temporary` dengan `head` yang sebelumnya menyimpan alamat memory dari `n3`(32) kemudian pointer `temporary` tersebut _pointing_ ke _field_ value dari struct node yang akan mendeferencing nilainya karena

```c
temporary->value
// sama dengan
(*temp).value // Deferencing value
```

Kemudian setelah `printf()` dijalankan nilai pointer `temporary` akan diisi lagi dengan alamat memory dari linked list selanjutnya sampai while berhenti ketika alamat memory bernilai NULL.
