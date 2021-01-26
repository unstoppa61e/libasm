# :mag: libasm
42 Tokyo プロジェクト
### アセンブラ学習の目的

- マシンへの理解を深める
- デバッグをより深いレベルで理解する
- オペレーションシステム（= デバイスドライバー、メモリプロテクション、実行状態の保存と復帰など）を書けるようになる

### コンパイル

1. nasm (= Netwide Assembler) をインストール。例: `brew install nasm`
2. `nasm -f macho64 (.s ファイル名)`

※ -f は32 bit か 64 bit かといった format の指定、macho64 は mach-O-64bit を表す。mach とは Mach カーネルを使った Unix のことであり、O はオブジェクトの意。  
3. （.s ファイルを単独でコンパイルしている場合）`ld (.o ファイル名) -lSystem`

※ .c ファイルとコンパイルするならば、 `gcc` で良い  
※ `ld` は load の略。これは link をしてくれるコマンド、つまり linker。Unix では linker が loader と呼ばれていたため、Linux へもその名称が引き継がれた。また、 `-lSystem` はライブラリサーチパス内にあるライブラリシステム (libSystem.dylib) をリンクするという意味。この libSystem の中に、libc (C 言語標準ライブラリ)、libm (算術ライブラリ)などが含まれている。dylib とは、”Mach-o Dynamic Library” の意。

### テストコマンド

- `make test` / `make test_bonus` にて、ライブラリを作成し、検証用のメインファイルとコンパイルした後、実行結果を表示します。

## :white_check_mark: [ft_strlen](https://github.com/monoue/libasm/blob/master/libasm/ft_strlen.s)

```
%define INDEX rax
```

- `define` は `%` に続ける。

```
section .text
```

- アセンブリプログラムは、 `section` によって区分けされる。
- `.text` セクションには「命令」を入れる。

```
_ft_strlen:
    global _ft_strlen
```

- `_ft_strlen:` や `.while：` というような記述を「ラベル」という。
- アセンブラ はこのラベルにアドレスを割り当てる。つまり、ラベルとは、アドレスに名前を付け、読みやすくするもの。
- 大文字、小文字は区別されるので注意
- `:` はなくても動くこともあるが、コンパイラにより注意されることもあるため、付けた方が良い。
- `_`（アンダースコア）から始まるラベル名の直前に `global` と宣言することにより、その関数名にて、他のファイルからの呼び出しが可能になる。
- グローバル宣言を行う場所は、プログラム内のどこでも良い。

```
xor INDEX, INDEX
```

- `xor` （= 排他的論理和）命令のオペランドを二つとも同じものにすると、ゼロアウトされる。
- この方法は、 `mov` で 0 を代入するよりもスピーディーであり、公式に奨励されている。


```
.while:
```

- `.` から始まるラベルを「ローカルラベル」と呼ぶ。
- 各ローカルラベルは、その直前に記述された、ノンローカルなラベルに属する。
- 今回であれば、 `.while` ラベルのフルネームは `_ft_strlen.while` となる。
- ローカルラベル名が同じでも、フルネームが異なれば、衝突が防がれ、ファイル中のどこからでもそのフルネームによってアドレッシングが可能。

```
cmp     byte[S + INDEX], 0 ; if (S[INDEX] - '\0'
```

- `cmp` 命令は、第一オペランドに対して第二オペランドによる減算を行った結果を、 `rflags` レジスタ内の各フラグに反映させる。
- 同じく減算を行う命令として `sub` というものがある。 `sub` では、減算の結果（= 差）が第一オペランドに格納されるのに対し、 `cmp` はフラグにのみ影響を及ぼす。
- `rdi` レジスタには、関数を呼び出した際の第一引数が格納される（今回の `strlen` における `char *str` ）。
- `[ ]` で囲むことにより、ポインタの値を扱うことになる。
- `0` など、数値そのままの値のことを「即値」という。
- 即値による計算を行う場合は、オペランド同士のサイズが揃っている必要がある。この行にて行おうとしていることは、 `index` の位置にある文字がヌル文字であるかのチェックである。即ち、文字同士の比較であり、 `char` 型のサイズは１バイトであるため、 `byte` と示してある。

```
cmp     byte[S + INDEX], 0 ; if (S[INDEX] - '\0'
je      .endwhile          ;                     == 0) goto .endwhile
```

- `je` は 'jump if equal' の意。即ち、（直前の演算により）zero フラグが立っているならば、指定したラベルへ移動する。

```
inc     INDEX              ; INDEX++;
```

- `inc`: increment（インクリメント）

```
jmp     .while             ; goto .while;
```

- `jmp` は、指定したラベルへ移動する命令。
- `je` と `jmp` の比較から分かるように、ジャンプ命令には、条件付き（conditional）のものと無条件のものがある。

```
ret                        ; return (INDEX);
```

- `ret`: return
- `rax` に格納されているものが返り値となる。

## :white_check_mark: [ft_strcpy](https://github.com/monoue/libasm/blob/master/libasm/ft_strcpy.s)

```
push    DST          ; var = dst;
```

- `push` : オペランドをスタック領域に格納する。

```
cld
```

- `cld` : 'clear the direction flag' の意。
- `movsb` などの命令の際、このフラグが立っていると、 `rsi` と `rdi` がインクリメントではなく、デクリメントされる。

```
movsb                ; *dst++ = *src++;
```

- `movsb` は、`move string by byte' の意。
- 名称に反し、文字以外の移動にも利用できる。
- `rsi` から `rdi` に、指定したサイズ（今回なら１バイト）をコピーする。
- 同時に、 `rsi` と `rdi` でポイントされている部分を、指定サイズ分インクリメントする。

```
mov     byte[DST], 0 ; *dst = '\0';
```

- `mov`: move　第二オペランドの中身を第一オペランドに移動する。

```
pop     rax          ; retV = dst;
```

- `pop` : スタックに積んであったデータをオペランドに引っ張ってくる。

## :white_check_mark: [ft_strcmp](https://github.com/monoue/libasm/blob/master/libasm/ft_strcmp.s)

```
%macro CLEAR_REG 1
    xor %1, %1
%endmacro
```

- 複数行マクロは、 `%macro` と `%endmacro` で囲む。
- 定義名の横の数値は、引数の数（0 でも可）。
- 例えば `%2` とやれば、第二引数を指す。

```
cmp     al, cl             ; if (c1 - c2
jne     .endwhile          ;             != 0) goto .endwhile
```

- `jne` : 'jump if not equal' の意。
- zero フラグが立っていなければ、指定ラベル先へ移動する。

## :white_check_mark: [ft_write](https://github.com/monoue/libasm/blob/master/libasm/ft_write.s)

```
extern ___error
```

- 外部の関数を使用する場合、 `extern` に続ける。

```
mov     SYSCALL_NUM, 0x2000004 ; func = write;
syscall                        ; RET_V = func(fd, buf, nbyte)
```

- `syscall` 命令は、 `rax` に格納されているシステムコールを呼び出す。
- システムコール番号は、 `sys/syscall.h` に定義されている（[ソース](https://unix.superglobalmegacorp.com/Net2/newsrc/sys/syscall.h.html)）。ただし、macOS の場合、 `0x2000000` を足す必要がある。

```
push    RET_V                  ; var = RET_V (= errno)
call    ___error               ; rax = errno memory address
pop     qword[rax]             ; *(errno memory address) = errno
```

- エラーが発生した場合、 `rax` に `errno` がセットされる。
- `error` 関数は、 `rax` に、 `errno` 設定用のアドレスをセットする。
- そのアドレスの値として、スタックに積んであった `errno` をセットしている。

※ft_write チェック用の main ファイルについて

### `fcntl` : file control

```c
fcntl(fds[i], F_SETFL, O_NONBLOCK);
```

- 今回は、第一引数の、read 用の fd を操作している。
- `F_SETFL` : 'set flag' の意。第１引数のファイルに対し、第３引数のフラグをセットする。
- 第３引数の `O_NONBLOCK` は、ノンブロッキングに処理するように、というフラグ。
これにより、read する対象がない場合、入力（？）を待ち続けるのではなく、エラーを返すようになる。
（以前にあったノンブロッキング処理用のフラグの不具合を解消するために追加されたフラグとのこと）

## :white_check_mark: [ft_read](https://github.com/monoue/libasm/blob/master/libasm/ft_read.s)
- `ft_write` と同様のため、説明は割愛。
## :white_check_mark: [ft_strdup](https://github.com/monoue/libasm/blob/master/libasm/ft_strdup.s)

```
default rel
lea     ARG1, [LEN + 1] ; ARG1 = LEN + 1;
```

- これまで使用してきた通り、 `[ ]` でくくられたものは、ポインタの値を指す。今回は、単純に、計算を行うために括弧を使用したい。そのような場合、 `[rel LEN + 1]` としてやれば、値として扱ってくれる。
- これは、'RIP Relative Addressing モード' を変更している。
- `default rel` と設定してやれば、 `rel` の設定がデフォルトとなる。そこまで有用な機能ではないようにも思われるが、今回は、知識の定着のために使用している。

- `lea` : Load Effective Address の意。
- 今回は、計算と `mov` を一行で済ませるために使用している。

## :white_check_mark: [ft_list_size](https://github.com/monoue/libasm/blob/master/libasm/ft_list_size_bonus.s)

```
MEMBER_SIZE     equ 8 ; (sizeof(void *))
```

- 定数の設定は、 `equ` で行える。

```
test    BEGIN_LIST, BEGIN_LIST                 ; if (BEGIN_LIST == NULL)
jz      .endwhile                              ;     goto .endwhile;
```

- `test` : 対象オペランド同士で、`and` 、つまり AND 演算を行い、結果に従って各フラグを変更する。
- ある値が 0 かを確認するには、`cmp` と `0` を使うよりもこの方法の方が速いため、推奨されている。

## :white_check_mark: [ft_list_push_front](https://github.com/monoue/libasm/blob/master/libasm/ft_list_push_front_bonus.s)

→ 全て既出の事項によるため、説明は割愛。

## :pencil: 学習時メモ

（著作権の問題で画像を省いているため、意味が通らない点があるかもしれません。）

- `text` 内のインストラクションは、以下の４つの部位からなる。すなわち、ラベル、ニーモニック、オペランド、コメントである。この内、ラベルとコメントの２つはオプショナルである。


## ベーシックデザイン


- **CPU** : Central Process Unit
- **Memory** → RAM
- **I/O Devices** → keyboards, printers, ...
- **System Bus** allows 'data', 'address', 'control signals' transfer

プログラムは実行される前に、メモリにロードされなくてはならない。その後、CPU がメモリから指示を獲得し、実行する。

メモリへのアクセスは非常に遅いため、内部的な一時メモリとして、レジスタが存在する。

アセンブリでは、レジスタを主に扱う。

- **CU** → Control Unit

    機能：

    - デコード
    - メモリから獲得した指示の実行
    - CPU 操作の指示
- **ALU** → Arithmetic and Logic Unit

    計算や、&&, ||, ! などを担当

    - デコード
    - メモリから獲得した指示の実行
    - CPU 操作の指示


- **MSB**: Most Significant Bit
- **LSB**: Least Significant Bit
- 「バイト」は、メモリにおける addressable な最小単位。

    (1 バイト: db）
                  Word: 2 バイト(dw)

    Double Word: 4 バイト(dd)

       Quad Word: 8 バイト(dq)

    → 変数を定義するのに役立つ用語

## x86 プロセッサーモード


Intel 64 アーキテクチャは IA-32e モードを導入しており、それには２つのサブモードが内包されている。
Compatibility Mode では、16 もしくは 32 ビットプログラムを、リコンパイルせずに 64 ビット OS のもとで使用できる。

プロセッサは、64 ビットアドレスのうち、48 ビットヴァーチャルアドレスのみ実行する。48 ビットのうちの MSB が 1 の場合は、それより上の 16 ビットも全て 1 となる。逆も同様である。

## RIP (Register Instruction Pointer)


RIP レジスタは、次に実行される指示のアドレスを保持する。

1. メモリから、そのアドレスに格納されている指示を獲得、実行する
2. 次のアドレスを指すように、RIP レジスタをインクリメントする

## レジスタの主目的


- データ転送
- 演算　　　など

8-bit レジスタの上の方にある、２つの名称があるものは、左側が 16 ビットのうち上部の 8 ビット、右側が下部の 8 ビットを示す。それ以下のものは、下位の 8 ビットを示す。


**RSP**: Register Stack Pointer → スタック操作。スタックのトップのメモリアドレス

**RBP**: Register Base Pointer → 関数内でスタック領域を扱う処理の基準となるメモリアドレス


RSP と RBP 以外のものを、今後の演習で使用する。

## バイナリと 16 進数の変換法


## N ビットが示す範囲 → 0 から (2 の N 乗) - 1 まで


## MSB が立っている場合の、マイナス数の表し方

1. 全ビットを反転させる
2. 1 加える
3. 表された数字に -1 を掛ける

例えば、`11111111` であれば、

1. `00000000`
2. `00000001`
3.              `-1`

となる。

また、`10000000` であれば、

1. `01111111`
2. `10000000`
3.          `-128`

となる。

## Signed Number の表す範囲


## ASCII Code

**ASCII**: American Standard Code for Information Interchange




## セクション

- text: 指示
- data: 変数

## アセンブリ言語メモ

- ~~CMAIN: main のマクロ。_main と書いても同様。~~ 使えなかった
- ニーモニック直後のオペランド部に配置されうるのは、即値、レジスタ、メモリアドレスなどである。
- オペランドとして置けるデータは、0 ~ 3 個である。
- `db` nasm によって与えられている。byte を書き込むことができる。
- `hexdump -C .oファイル` で、中身を見られる…！
- `ld -lSystem` システムライブラリをリンクさせている。これによって、_main とかが使えるようになる。
- `sum dq 20` と`sum: dq 20` の間に差はない。しかし、コロンを付ける方が一般的。
- `db`: バイト　`dw`: ワード　`dd`: ダブルワード　`dq`: クオドワード
- `ret` を入れないと、続くメモリセルに入っているランダムな値（ゴミ）を読み込み、セグフォを起こす。
- 0 を代入したい場合は、 `mov` ではなく `xor` を使う
- 「ゼロか？」の最速チェックの方法は、 `test` を使用する（= AND 演算）。

    ```wasm
    test rcx, rcx
    jnz .loop
    ```

- `ja` / `jb` → unsigned
- `jg` / `jl` → signed
- `ret` を呼び出すのは、スタックが、関数の実行時と同じ状態である場合のみ！　でないと、スタックのトップにあるものを rip の新しい内容として扱うので、ゴミを実行してしまう。
- rbx, rbp, rsp, r12-r15 は、関数内で変更するのであれば、関数を終了する前に、必ず元に戻す。
- rbp と rsp は、決していじってはならない。
- `mov rax, counter` などとやる場合、rax に渡されているのは、値ではなく、counter のアドレス。値を渡すには、[rel counter] などとしてやる。
- 恐らくだが、逆に、mov [rel counter], rax などとする必要があるのは、rel の値にこの値を入れる、という指示なのでは…？
- 定数を扱うには、 `equ` を使う。

    ```jsx
    BufferSize equ 500
    ```

    のような感じ。
    これだと、アドレスではなく値が渡される。

    この場合、 `.data` セクションは不要。
    また、

    ```jsx
    BufferSize equ 500*4
    ```

    などとやっても、ちゃんと計算結果が格納される。

- 定数を設定するには、

    ```
    Buffersize equ 500*4
    ```

    などと、 `equ` でつないでやる。

    ## lldb デバッグ

    lldb にて、標準の出力を変更するには、

    1) ホームディレクトリに .lldbinit ファイルを作成

    2)

    ```
    settings set target.x86-disassembly-flavor intel
    settings set target.use-hex-immediates false # 10 進数に
    ```

    と記入。

    - lldb にて、 `expression $rax = 100` などとやると、書き換わった値での結果を見られる。
    - lldb にて、 `p/d $rax` などとやれば、10 進数で結果を表示してくれる（unsigned  で見たければ `u`）。
    - 2 進数でやりたければ、 `p/t` とする（'t' は 'two'）（`re r/t rax` でも可）
    - 文字列に変換したければ、 `p (char*)hoge` とする

    ## mov

    ```
    mov dword[rel counter], 20
    mov rax, [rel counter]
    ```

    即値をメモリに mov する場合、サイズを示す必要がある。

    - レジスタとメモリの間で mov を行う場合は、qword などの指示は不要。そこのサイズは、よしなに判断してくれる。
    - つまり、 `dword` みたいな感じでサイズの指定が必要なのは、即値とメモリ（= 変数）の間だけ！！

    レジスタとメモリ間の移動の場合は、省略できる。

    - メモリからメモリ（変数から変数）の mov はできないので注意。そのために、経由が必要になる…！
    - mov のオペランドは、両方とも同じサイズである必要がある。

    ## xchg

    - オペランドは両方とも同じサイズである必要がある。
    - メモリ同士だとできないのは、 `mov` と同様。
    - メモリ同士を交換したければ、以下のように行う。

        ```
        mov rax, [rel A]
        xchg rax, [rel B]
        mov [rel A], rax
        ```

    ## inc / dec

    - メモリを対象にする場合、以下のようにサイズを明記してやる

    ```
    inc byte [rel counter]
    ```

    ## neg

    - 正負逆転。
    - こいつも、メモリに使う場合はサイズ指定が必要。

    ## add / sub

    - オペランド同士のサイズを揃える。
    - メモリにはサイズ明示。
    - メモリ同士の演算は不可。

    ## フラグレジスタ

    - RFLAGS という名前の、64-bit のレジスタがある。その 64 個の各ビットが、コンピュータの操作をコントロールする。
    - この内のいくつかが、予め確保されている。


    ### ステータスフラグ

    - Carry, Zero, Sign, Overflow の４つ。
    - 計算を行った際の状態を表す。
    - Carry: 計算結果を unsigned の値だとみなした場合に、範囲内に収まらない場合にセットされる。
    - Overflow: Carry の、signed 版。
    - 例えば、8-bit の `al` に 180 をセットした場合、unsigned の範囲内（0 ~ 255）には収まっているが、signed (-128 ~ 127) には収まっていないため、Overflow フラグだけが立つ。

    ### コントロールフラグ

    - Direction, Interrupt など。

    ## ビットワイズ

    - `10010001b` などのように `b` を最後に付ければ、ビット、つまり 2 進数だということが示される。
    - メモリの場合はサイズを明示。
    - オペランド同士はサイズを揃える。
    - メモリ同士は不可。

    ### and / or

    ```
    mov rax, 10010001b
    and rax, 01110011b
    //       00010001
    ```

    ### ビットマスク

    ```
    mov rax, 10010001b
    and rax, 11101111b
    //          X     この桁のみを消せる

    mov rax, 10010001b
    or  rax, 00000100b
                  X   この桁のみを立てられる
    ```

    ### xor

    （基本的に or だが、両方とも立っている場合は 0 にする）

    ↑ これよりも、「値が異なれば true, 同じなら false」の方が分かりやすいかも

    ```
    xor rax, 0 // 変化は起こらない

    xor rax, 11111111b // 全て反転

    xor rbx, rcx
    xor rcx, rbx
    ```

    ## フラグとビット演算

    - ビット演算を行うと、overflow フラグと carry フラグは消去される
    - ビット演算の結果、左端のビット (MSF) が立っていたなら、sign フラグも立つ。

    ### not

    全てのビットを反転させる。

    ```
    mov rax, 11110000b
    not rax
    //       00001111
    ```

    RIP: Register Instruction Pointer

    ## Branching

    ### jmp

    ```
    jmp .loop
    ```

    なお、

    ```
    mov rbx, .loop
    jmp rbx
    ```

    などとすることもできる（メリットは分からない）

    ### test

    and の、値が変わらない版。zero フラグを操作できる。（他のフラグも確認できるはずなのだが、検証が上手くいかなかった。）

    ```
    mov  al, 101011b
    test al,   1000b
    // zero フラグは立たない
    ```

    ### フラグ一覧

    `jz` : jump if zero

    `jnz` : jump if not zero（以下、not は省略）

    `jc` : jump if carry

    `jo` : jump if overflow

    `js` : jump if signed

    ### unsigned

    `ja/jnbe` : left > right

    `jae/jnb` : left ≥ right

    `jb/jnae` : left < right

    `jbe/jna` : left ≤ right

    ### signed

    `jg/jnle` : left > right

    `jge/jnl` : left ≥ right

    `jl/jnge` : left < right

    `jle/jng` : left ≤ right

    ### cmp

    sub の、値が変わらない版。各フラグを操作できる。

    ### フラグのセットとクリア

    `stc` : carry フラグのセット

    `clc` : carry フラグのクリア

    ある値が 0 かによって jump する方法は、 `jz` と `je` の２パターンあり、等価である。

    `test eax eax` → `jz`

    `cmp ecx edx` → `je`

    といった感じで、zero フラグを見たいのか、それとも値を見たいのかによって使い分けるのが良い。

    ### if - else

    ```c
    if (rbx > rcx)
    	rax = 1;
    else
    	rax = 0;
    ```

    ```
    	cmp rbx, rcx
    	jg .if ; if (rbx > rcx)
    	; else
    	mov rax, 0
    	jmp .endif
    .if
    	mov rax, 1
    .endif
    ```

    ### &&

    > C

    ```c
    if (rbx > rcx && rcx && rdx)
    	rax = 1;
    else
    	rax = 0;
    ```

    > ASM

    ```
    	cmp rbx, rcx
    	jle .else; if (rbx <= rcx)
    	cmp rcx, rdx
    	jle .else; if (rcx <= rdx)
    	; if (rbx > rcx && rcx > rdx)
    	mov rax, 1
    	jmp .endif
    .else
    	mov rax, 0
    .endif
    ```

    ### while

    > C

    ```
    rbx = 0;
    while (rbx < rcx)
    {
    	rbx++;
    }
    ```

    > ASM

    ```
    mov rbx, 0
    ; 今回は要らないが、ここに (rbx >= rcx) を入れると字義通り
    .while
    	inc rbx
    	cmp rbx, rcx
    	jz .endwhile
    	jmp while
    .endwhile
    ```

    ```
    ; 自分で考えた方。こちらの方が良いかも
    .while
    	cmp rbx, rcx
    	jge .endwhile
    	inc rbx
    	jmp .while

    .endwhile
    ```

    ## 配列

    1 byte サイズの配列（文字列など）の例


    - ベースである 20 のアドレスに 2 を足してやれば、配列の 3 つ目の要素を指せる
    - 違う型の配列の場合は、その型のデータサイズを掛けてから足せば良い。

    ### 要素へのアドレッシング


```
section .data
value dd 1,2,3,4,5

section .text
_main:
	mov eax, [rel value + 12] ; al = 4
```

> rax に配列の各要素を渡す例

```
section .data
var dq 10, 20, 30, 40, 50, 60, 70, 80
varSize equ $ - var ; $ は、現在のアドレスの位置。
varTypeSize equ 8
varCount equ varSize / varTypeSize

section .text
_main:
	mov rsi, var
	mov rdx, varCount
	xor rcx, rcx

.while:
	mov rax, [rsi + rcx * varTypeSize] ; なぜか rel 入れずに実行できる
	inc rcx
	cmp rcx, rdx
	jl .while
```

## エンディアン

x86 プロセッサでは、リトルエンディアン方式が採用されている。


- つまり、リトルエンディアンでは LSB から扱い始める点に注意。

```
section .data
value dd 0x12345678

section .text
_main:
	mov rbp, rsp
	mov al, [rel value]     ; 0x78
	mov bl, [rel value + 1] ; 0x56
	mov cl, [rel value + 2] ; 0x34
	mov dl, [rel value + 3] ; 0x12
```

### lea

- Load Effective Address の意。

```
section .data
sum dq 10

section .text
_main:
	mov rbp, rsp
	mov rax, [rel sum]
	lea rbx, [rel sum] ; この [] が必要！ 忘れがち！
	mov rcx, [rbx]
```

- 要は、C 言語での、 `&` でアドレスを取り出すのと同じ。
- なお、`mov rcx, [rbx]` などと `[]` を使うのは、C 言語での、 `*` で値を取り出すのと同じ。
- 重要かつ厄介なことには、 **計算もこの命令で扱う。**

    ```
    mov rax, 10
    lea rbx, [rax + 10] ; rbx: 20
    ```

    これはすなわち、

    ```
    mov rax, 10
    mov rbx, rax
    add rbx, 10
    ```

    と等しく、一行で済ませられるということである。

## RIP Relative Addressing モード

- 大層な名前が付いているが、Mach-O 環境では、このモードを使わないと動いていない。
- `default rel` と記述しておくと、 `rel` の記述が不要になる。

## 乗算・除算

### Unsigned

### 乗算: `mul`

- オペランドは１つしか取らない。
- オペランドに即値は指定できない。
- 対象の２要素のサイズは等しくなければならない。


- サイズによってそれぞれ、 `al` / `ax` / `eax` / `rax` が、もう片方の要素となる。
- 計算結果の上半分と下半分に分かれて格納される。上半分は、 `d` の行のレジスタに記録されることに注意。
- 上半分に格納されるのは、サイズを超えた場合。この場合、Overflow と Carry の両方のフラグが立つ。

### 除算: `div`


- オペランドは、除数。
- 被除数 8 bit の場合は、被除数を ax に入れてやれば良いのだが、その他の bit の場合は、被除数を d と a に分けて格納してやらねばならない…。
- 余りまで出してくれる。
- 深く考えず、被除数を rax にセットし、商を同じく rax から、また余りは rdx から、それぞれ取り出せば良いような気がする。
- フラグの動きは undefined となっている。
- 商の値がオーバーフローしている場合は、プログラムが停止する。

### Signed

### 乗算: `imul`

- ３つの用法がある。
    1. オペランド１つ。unsigned と同様。
    2. オペランド２つ。
        - 積は１つ目のオペランドに格納される。
        - この１つ目のオペランドは、レジスタでなくてはならない。
        - １つ目のオペランドには、8 ビットレジスタは使用できない。
        - ２つ目のオペランドは、レジスタ、メモリ、即値のいずれでも良い。
    3. オペランド３つ。
        - １つ目のオペランドに、積が格納される。
        - ２つ目のオペランドは、レジスタかメモリ。
        - ３つ目のオペランドは、即値のみ。

### 除算: `idiv`

- Sign extension という操作が必要になる。

    マイナスの値を示そうとしても、最初はこのように格納されてしまう。つまり、マイナスを示すための MSB が立っていない。


    下位のレジスタの MSB が正しい。なので、こちらを上位ビット全てに反映させる必要がある。



    これを実行するには、 `edx` に -1 を代入してやるという方法があるが、それだと、毎回下位レジスタの MSB をチェックしなくてはならない。

    そこで、この動作をやってくれるオペレーションが存在する。

    ```
    mov al, 40
    cbw ; convert byte to word
    mov bl, 10
    idiv bl
    ```

    のように、 `cbw`, `cwd`, `cdq`, `cqo` というものを使う。

## シフト

### 左論理シフト: `shl` (SHift Left)


- 第一オペランドは、シフト対象
- 第二オペランドは、シフト数。これは、即値、もしくは `cl` のみが使用可。

### 左算術シフト: `sal` (Shift Arithmetic Left)

- 左論理シフトとの違いはない。

### 右論理シフト: `shr`

- 左シフトと仕組みは同じ。


### 右算術シフト: `sar`



- sign を示す MSB が保持 & 複製され続ける。

### 左ローテート: `rol`


### 左キャリーローテート: `rcl`


- Carry フラグは経由地として使われる。

### 右ローテート

- 左ローテートと仕組みは同じ。



## 文字列

### movs

- 'move string' の意。
- 名称に反し、文字以外の移動にも利用できる。
- `movsb` , `movsw` などと、一度の命令につき移動させるサイズを、末尾で指定する。
- `rsi` から `rdi` に、指定したサイズ（今回なら１バイト）をコピーする。
- 同時に、 `rsi` と `rdi` でポイントされているアドレスを、指定サイズ分インクリメント / デクリメントする。
- Direction フラグが true であれば、デクリメント、false であれば インクリメントとなる。
- Direction フラグをクリアするには、 `cld` という命令を使用する。

### rep

- 文字列操作とセットで使われることの多いプレフィックス。
- `rep movsb` のようにして使う。
- `rcx` がカウンターとして機能し、実行ごとにデクリメントされ、0 になったら止まる。そのため、実行したい回数を予め `rcx` に格納しておく。

### stos

- 'store string' の意。


- 指定サイズに従い、`al` / `ax` / `eax` / `rax` の要素を、 `rdi` にコピーする。
- インクリメント / デクリメントも同時になされるので、 `rep` と併用した場合、ある要素で `rdi` を埋めていく形になる。

### lods

- 'load string' の意。


- `rsi` から、指定サイズ分を `al` / `ax` / `eax` / `rax` にコピーする。
- `stos` や `loop` と組み合わせれば、例えば、 `rsi` に格納されている小文字を全て大文字に変えて `rdi` に移動するようなことが可能！

### loop

- ラベル先へ跳ぶ。同時に、 `rcx` をデクリメントする。 `rcx` が 0 以下の場合は、ジャンプが実行されない。
- `loop` コマンドは、そのジャンプ先のラベルが、現在の位置より -128 から 127 バイトに収まっていなければならない（※この条件を満たさない場合は、jmp 系の命令を使えば良い。）

### scas

- 'scan string' の意。


- `rdi` 中でポイントされている要素が、`al` / `ax` / `eax` / `rax` と同じかどうかをチェックしながら、 `rdi` のインクリメント / デクリメントを同時に行う。
- `repne` (= repeat while not equal) というプレフィックスと組み合わせて使えば、その要素が見つかるまで `rdi` のインクリメント / デクリメントが行われる。
- 見つかった場合は zero フラグがセットされ、見つからなかった場合は zero フラグがクリアされるので、最後まで見つからなかった場合の条件付きジャンプには、 `jnz` を使ってやれば良い。

### cmps

- 'compare string' の意。
- `rsi` と `rdi` を要素サイズごとに比較していく。
- `repe` (= repeat while equal) とセットで使われる。
- こちらも、 `jnz` と組み合わせて使えば、違う要素が見つかった場合に指定先へジャンプできる。

### push & pop


- 指定できるサイズは 64 か 16 ビットのみ。
- push される度に、アドレスは１バイトずつデクリメントされる。
- ブロックに入る時と出る時は、 `RSP` は同じところを指していなければならない。

### プロシージャ

- 関数と同じ。
- 単なるラベルとは異なる。

### call

- ラベル、レジスタ、メモリを呼ぶ。
- 呼ぶたびに、スタックに、復帰位置のアドレスが積まれる。
- `ret` で、スタックに積まれた一番上のアドレスの位置にリターンする。

### 参考：引数の配列の値を全て足して返す関数

```
ArraySum:
	xor rax, rax

.Add:
	add rax, [rdx] ; rdx は dq で宣言された配列
	add rdx, 8     ; dq なので 8 足せば、次の要素に移る
	loop .Add
	ret

_main:
	mov rcx, count
	mov rdx, array
call ArrySum
```

- プロシージャに引数を渡す際は、 `push` を使うという手もある。
- プロシージャに移動した後、 `mov rcx, [rsp + 8]` などとやってやれば、リターン用のアドレスの直前に積まれた要素を獲得できる。
- この手法を使う場合、プログラムの最後に、
    1. `rsp` に、 `push` した回数 * 8 をプラスする
    2. 適当に `pop` する

    のいずれかによって、 `rsp` の位置を戻すのを忘れずに。

### ローカル変数

- 難しい。rbp と rsp をいじって、スタックを使う。

- 備え付けの関数の返り値は、 `rax` に格納させるっぽい。

## マクロ

### 一行マクロ

- `%define` とする。あとは C 言語と同じ。
- パラメータを渡す場合は、各要素を () で囲んでやらないと、意図せぬ結果に至ってしまう場合がある。

### 複数行マクロ

- `%macro` で開始、 `%endmacro` で終了。
- マクロ内のラベルには、先頭に `%%` を付けることで、マクロを複数回使用した際にラベル名の重複とみなされるのを回避できる。

```
%macro clear_reg 1 ; この数値が、引数の数。0 の場合も 0 と記述。
  xor %1, %1       ; 第一引数なら %1 。第二なら %2。
%endmacro
```

- アセンブラによって解釈される要素であり、アセンブラによって記述が異なってくる点に注意。
