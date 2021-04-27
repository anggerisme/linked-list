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
    node_t *head;

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


