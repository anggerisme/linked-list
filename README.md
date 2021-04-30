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

# Inserting node at the end

Kita sudah memiliki 3 list yang telah kita buat diatas, bagaimana jika kita ingin menambahkan node 4 di urutan terakhir list tersebut?

1. Pertama dengan membuat node ke 4 dengan pointer yang akan menjadi penanda kalau node 4 urutan terakhir.
2. Jika sebelumnya kita mempunyai pointer `ptr` untuk menghitung total list maka di akhir nanti kita isikan nilai node 3 pada _field_ link agar menyimpan alamat memory dari node 4 menggunakan `ptr`

```c
ptr->link = temp;
```

> Setelah `ptr` sampai pada node 3 maka kita akses nilai field linknya lalu kita isikan dengan alamat node 4 yang disimpan dalam pointer `temp`.

Kode Program :

```c
struct node {
    int data;
    struct node *link;
};

void add_at_end(struct node *head, int data){
    struct node *ptr, *temp;
    ptr = head;
    temp = (struct node*)malloc(sizeof(struct node));

    temp->data = data;
    temp->link = NULL;

    while(ptr->link != NULL){
        ptr = ptr->link;
    }
    ptr->link = temp;
}

struct node *add_beg(struct node *head, int d){
    struct node *ptr = malloc(sizeof(struct node));
    ptr->data = d;
    ptr->link = NULL;

    ptr->link = head;
    head = ptr;
    return head;
}

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
    add_at_end(head, 67);
    while(ptr != NULL){
        printf("%d - ", ptr->data);
        ptr = ptr->link;
    }

}
```

Keterangan :

1. Pertama kita buat node yang akan kita posisikan pada urutan pertama. Untuk itu kita perlu membuat function `add_beg` dengan parameter `head`, dan `int d`.

```c
struct node *add_beg(struct node *head, int d)
```

> Mengapa Function _add_beg () kita beri arterisk (`_`) karena function `add_beg()`akan mengembalikan nilai yang akan kita simpan nanti dalam pointer head di function`main()`.

Di dalam `add_beg()` terdapat perintah untuk membuat node dengan pointer `ptr`. Dan _data field_ yang ada di dalamnya kita isi masing masing dengan nilai yang diberikan oleh parameter `*head` dan `d` yang di dapat dari argumen dari function `main()`.

```c
    struct node *ptr = malloc(sizeof(struct node));
    ptr->data = d;
    ptr->link = NULL;
```

Karena kita ingin menjadikan node ini berada pada urutan pertama maka kita perlu meng-update _data field_ `link` pada node `ptr` yang sebelumnya bernilai `NULL` dengan mengisikan alamat memory pada node 1 (`head`) ke dalam link node `ptr` ini yaitu 1000. Sehingga node 1 `head` akan berada di urutan kedua dan node yang baru ini (`ptr`) akan berada pada urutan pertama.

```c
    ptr->link = head;
    head = ptr;
```

Dan kemudian kita arahkan pointer `head` ke node `ptr` agar jelas posisi bahwa node `ptr` berada di urutan pertama.

karena `ptr` beralamat memory 3000 dan `link` pada node `head` = `ptr` maka head juga beralamat 3000. Dan kita kembalikan (`return`) ke dalam function `main()`.

2. Kemudian kita buat function `add_at_end` untuk menambahkan node baru diurutan terakhir. function `add_at_end` memiliki parameter `*head` dan `int data` yang masing-masing menerima argumen yang dikirimkan oleh function `main()`.

Cara kerja dari function `add_at_end` yakni mengisi nilai node yang paling terakhir dengan data/argumen yang kita kirimkan melalui `main()` setelah proses pengulangan while menemui kondisi `ptr != NULL` tidak lagi terpenuhi. Jadi ketika `ptr` menemukan node yang link-nya memiliki nilai NULL untuk kemudian diganti dengan data yang sudah disediakan. Node yang terakhir ini memiliki pointer `temp`

```c
while(ptr != NULL){
        printf("%d - ", ptr->data);
        ptr = ptr->link;
    }
```

> Artinyta `ptr` yang sebelumnya berpindah (looping) dari satu node ke node berikutnya. Proses assignment ini dilakukan setelah kondisi `while` terpenuhi yaitu apabila suatu node memiliki link `NULL` maka isi link tersebut dengan alamat memory node yang baru, Sehingga otomatis node yang baru tersebut berada pada urutan terakhir.

Di dalam function `add_at_end` kita membuat pointer `*ptr` dan `*temp`

```c
struct node *ptr, *temp;
```

Kemudian pointer `ptr` kita isi dengan `head` yang kita peroleh dari argumen yang dikirimkan oleh function main()

```c
temp = (struct node*)malloc(sizeof(struct node));
```

Nilai dari head ini di dapat setelah pemrosesan function add*beg yang kemudian head menjadi beralamat 3000 dan \_pointing* ke node pertama dengan value 3.

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
