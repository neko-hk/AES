#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int TMP[4];
int subkey[11][4][4];

int s_box[16][16] =
{{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
{0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
{0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
{0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
{0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
{0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
{0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
{0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
{0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
{0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
{0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
{0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
{0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
{0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
{0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
{0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};

int inv_s_box[16][16] =
{{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e,0x81, 0xf3, 0xd7, 0xfb},
{0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44,0xc4, 0xde, 0xe9, 0xcb},
{0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b,0x42, 0xfa, 0xc3, 0x4e},
{0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49,0x6d, 0x8b, 0xd1, 0x25},
{0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc,0x5d, 0x65, 0xb6, 0x92},
{0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57,0xa7, 0x8d, 0x9d, 0x84},
{0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05,0xb8, 0xb3, 0x45, 0x06},
{0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03,0x01, 0x13, 0x8a, 0x6b},
{0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce,0xf0, 0xb4, 0xe6, 0x73},
{0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8,0x1c, 0x75, 0xdf, 0x6e},
{0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e,0xaa, 0x18, 0xbe, 0x1b},
{0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe,0x78, 0xcd, 0x5a, 0xf4},
{0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59,0x27, 0x80, 0xec, 0x5f},
{0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f,0x93, 0xc9, 0x9c, 0xef},
{0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c,0x83, 0x53, 0x99, 0x61},
{0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63,0x55, 0x21, 0x0c, 0x7d}};

void rotword(int w[4][4], int count){//サブ鍵　左巡回シフト
    int i, j, tmp;
    tmp = w[3][0];
    w[3][0] = w[3][1];
    w[3][1] = w[3][2];
    w[3][2] = w[3][3];
    w[3][3] = tmp;
}

void subword(int w[4][4]){//サブ鍵　s-box処理
    int i, j, k, l, n;
    for(i=0; i<4; i++){
        k = w[3][i] / 0x10;//左側の値 16の商
        l = w[3][i] % 0x10;//右側の値 16の余り
        w[3][i] = s_box[k][l];//s_boxで置換
    }
}

void rcon(int w[4][4], int count){//サブ鍵　(x^i-1 mod 100011011),0,0,0との排他的論理和   
    int rcon[10] = {
    0b00000001,
    0b00000010,// x^1 mod x^8+x^4+x^3+x^1+1 = x
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b00011011,// x^8 mod x^8+x^4+x^3+x^1+1 = x^4+x^3+x^1+1
    0b00110110};// x^9 mod x^8+x^4+x^3+x^1+1 = x^5+x^4+x^2+x

    w[3][0] = w[3][0]^rcon[count-1];//排他的論理和 

    int i, j;
    for(i=0; i<4; i++)
        TMP[i] = w[3][i];//tempとして保存
}

void sub(int w[4][4], int count){//サブ鍵　subkey作成
    int i, j, p, num;
    p = 0;
    for(i=0; i<4; i++)
    w[3][i] = subkey[count-1][3][i];
    for(j = 0; j < 4; j++){
        for(num=0; num<4; num++){
            subkey[count][j][num] = w[p][num]^TMP[num];//排他的論理和
            TMP[num] = subkey[count][j][num];//tempを上書き
        }
        p++;
    }

    int a, b;
    for(a=0; a<4; a++){
        for(b=0; b<4; b++){
            w[a][b] = subkey[count][a][b];
        }
    }
}

void subbyte(int w[4][4]){//暗号化　s-box処理
    int i, j, k, l, n;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            k = w[i][j] / 0x10;//左側の値 16の商
            l = w[i][j] % 0x10;//右側の値 16の余り
            w[i][j] = s_box[k][l];
        }
    }
    printf("sub = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", w[j][i]);
        }
    }
    printf("\n");
}

void shiftrows(int m[4][4]){//暗号化　その行バイト分の左巡回シフト
    int i, j, temp1, temp2, temp3;

    temp1 = m[1][0];
    m[1][0] = m[1][1];
    m[1][1] = m[1][2];
    m[1][2] = m[1][3];
    m[1][3] = temp1;

    temp1 = m[2][0];
    temp2 = m[2][1];
    m[2][0] = m[2][2];
    m[2][1] = m[2][3];
    m[2][2] = temp1;
    m[2][3] = temp2;

    temp1 = m[3][3];
    m[3][3] = m[3][2];
    m[3][2] = m[3][1];
    m[3][1] = m[3][0];
    m[3][0] = temp1;

    printf("row = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", m[j][i]);
        }
    }
    printf("\n");
}

void mixcolumns(int m[4][4]){//暗号化　mix配列との行列計算
    int mix[4][4] = 
    {{0x02, 0x03, 0x01, 0x01},//[ x  x+1  1   1 ]
    {0x01, 0x02, 0x03, 0x01}, //[ 1   x  x+1  1 ]
    {0x01, 0x01, 0x02, 0x03}, //[ 1   1   x  x+1]
    {0x03, 0x01, 0x01, 0x02}};//[x+1  1   1   x ] 定数の配列

    int MixCol[4][4] = //初期化
    {{0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}, 
    {0, 0, 0,0}};

    int i, j, l, n, o, p, q;

    for(i=0; i<4; i++){//行目
        for(j=0; j<4; j++){//列目
            for(l=0; l<4; l++){//計算回数
                q = 0;
                for(n=0; n<8; n++){//定数の配列から次数を求めて位数上げ
                    p = mix[i][l] & (1 << n);
                    q = q^(p * m[l][j]);
                }
                MixCol[i][j] = MixCol[i][j]^q;
            }
            for(o=7; o>-1; o--){//8次以上になった場合
                if(MixCol[i][j] >= (0x100 << o)){
                    MixCol[i][j] = MixCol[i][j]^(0x11b << o);
                }
            }
        }
    }

    for(i=0; i<4; i++){//代入
        for(j=0; j<4; j++){
            m[i][j] = MixCol[i][j];
        }
    }

    printf("col = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", m[j][i]);
        }
    }
    printf("\n");
}

void addroundkey(int subkey[11][4][4], int count, int m[4][4]){//暗号化　サブ鍵との排他的論理和
    int i, j, p;
    p = 0;
    for(i = 0; i < 4 ; i++){
        for(j=0; j<4; j++){
            m[j][p] = m[j][p]^subkey[count][i][j];
        }
        p++;
    }

    printf("sch = ");
    for(i = 0; i < 4 ; i++){
        for(j=0; j<4; j++){
            printf("%2x ", subkey[count][i][j]);
        }
    }
    printf("\n\n");
    printf("add = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", m[j][i]);
        }
    }
    printf("\n");
}

void inv_addroundkey(int subkey[11][4][4], int count, int m[4][4]){//復号化　サブ鍵との排他的論理和
    int i, j, p;
    p = 0;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            m[j][p] = m[j][p]^subkey[count][i][j];
        }
        p++;
    }

    printf("inv_sch = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", subkey[count][i][j]);
        }
    }
    printf("\n\n");
    printf("inv_add = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", m[j][i]);
        }
    }
    printf("\n");
}

void inv_mixcolumns(int m[4][4]){//復号化　mix配列の逆行列inv_mixとの行列計算
    int i, j, k, l, n, o, p, q;

    int inv_MixCol[4][4] = 
    {{0, 0, 0, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}};

    int inv_mix[4][4] =
    {{0x0e, 0x0b, 0x0d, 0x09},
    {0x09, 0x0e, 0x0b, 0x0d},
    {0x0d, 0x09, 0x0e, 0x0b},
    {0x0b, 0x0d, 0x09, 0x0e}};

        for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            for(l=0; l<4; l++){
                q = 0;
                for(n=0; n<8; n++){
                    p = inv_mix[i][l] & (1 << n);
                    q = q^(p * m[l][j]);
                }
                inv_MixCol[i][j] = inv_MixCol[i][j]^q;
            }
            for(o=7; o>-1; o--){
                if(inv_MixCol[i][j] >= (0x100 << o)){
                inv_MixCol[i][j] = inv_MixCol[i][j]^(0x11b << o);
                }
            }
        }
    }
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            m[i][j] = inv_MixCol[i][j];
        }
    }

    printf("inv_col = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", m[j][i]);
        }
    }
    printf("\n");
}

void inv_shiftrows(int m[4][4]){//復号化　その行バイト分の右巡回シフト
    int i, j, temp1, temp2, temp3;
    temp1 = m[1][0];
    m[1][0] = m[1][3];
    m[1][3] = m[1][2];
    m[1][2] = m[1][1];
    m[1][1] = temp1;
    temp1 = m[2][0];
    temp2 = m[2][1];
    m[2][0] = m[2][2];
    m[2][1] = m[2][3];
    m[2][2] = temp1;
    m[2][3] = temp2;
    temp1 = m[3][3];

    m[3][3] = m[3][0];
    m[3][0] = m[3][1];
    m[3][1] = m[3][2];
    m[3][2] = temp1;

    printf("inv_row = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", m[j][i]);
        }
    }
    printf("\n");
}

void inv_subbyte(int m[4][4]){//復号化　inv_s_vox処理
    int i, j, k, l;

    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            k = m[i][j] / 0x10;
            l = m[i][j] % 0x10;
            m[i][j] = inv_s_box[k][l];
        }
    }

    printf("inv_sub = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", m[j][i]);
        }
    }
    printf("\n");
}

int main(void){
    int count;
    int i, j;
    int w[4][4];//サブ鍵生成用
    int m[4][4];//過程表示用
    int key[4][4];//鍵用
    int ple[4][4];//平文用
    int cip[4][4];//暗号文用
    
    count = 1;

    printf("Enter the Keytext 2bits:00~ff\n");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            scanf("%2x",&key[i][j]);
        }
    }

    printf("Enter the Plaintext 2bits:00~ff\n");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            scanf("%2x",&m[j][i]);
            ple[i][j] = m[j][i];
        }   
    }

    printf("\nUsed key     = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", key[i][j]);
        }
    }

    printf("\nPlaintext    = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", ple[i][j]);
        }
    }
    printf("\n\n");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            w[i][j] = key[i][j];
            subkey[0][i][j] = key[i][j];
        }
    }
    for(; count<=10; count++){
        rotword(w, count);
        subword(w);
        rcon(w, count);
        sub(w, count);
    }

    //暗号化
    count = 1;

    count = 0;
    addroundkey(subkey, count, m);

    for(count=1; count<10; count++){
        subbyte(m);
        shiftrows(m);
        mixcolumns(m);
        addroundkey(subkey, count, m);
    }

    count = 10;
    subbyte(m);
    shiftrows(m);
    addroundkey(subkey, count, m);

    printf("\n");
    printf("Ciphertext   = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", m[j][i]);
            cip[i][j] = m[j][i];
        }
    }
    printf("\n");

    //復号化

    printf("\n");
    inv_addroundkey(subkey, count, m);
    inv_shiftrows(m);
    inv_subbyte(m);

    for(count=9; count>0; count--){
        inv_addroundkey(subkey, count, m);
        inv_mixcolumns(m);
        inv_shiftrows(m);
        inv_subbyte(m);
    }

    count = 0;
    inv_addroundkey(subkey, count, m);

    printf("\nUsed key     = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", key[i][j]);
        }
    }

    printf("\nPlaintext    = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", ple[i][j]);
        }
    }

    printf("\nCiphertext   = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", cip[i][j]);
        }
    }

    printf("\nDeciphertext = ");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%2x ", m[j][i]);
        }
    }
    return 0;
}