// printf ve fprintf, fscanf gibi giriş-çıkış işlemlerini dahil etmek için eklenen kütüphanedir.
#include <stdio.h>

// #define komutu, sabit değerleri tanımlamak için kullanılır.
// MAX_PERSONEL ile en fazla 50 personelin bilgisinin işleneceğini belirtiriz.
#define MAX_PERSONEL 50
// MAX_AD ve MAX_SOYAD ile her personelin adı ve soyadının ayrı ayrı maksimum 20 karakter olabileceğini belirtiriz.
#define MAX_AD 20
#define MAX_SOYAD 20

// struct, birden fazla farklı türden değişkeni bir arada tutmak için kullanılır.
// Burada Personel adında, içerisinde iki farklı türde değişken bulunduran bir struct tanımladık.
struct Personel {
    int sicil_no; // Personelin sicil numarası
    char ad[MAX_AD]; // Personelin adını içeren bir karakter dizisi
    char soyad[MAX_SOYAD]; // Personelin soyadını içeren bir karakter dizisi
    int satis_miktari; // Personelin satış miktarı

};
int main() {
    // FILE *, dosya işaretçisidir ve bir dosyaya erişim sağlamak için kullanılır.
    // girdi değişkeni, dosya_ac fonksiyonundan dönen FILE işaretçisi türündeki değeri tutar.
    // fopen("yillik.dat", "r") satırı, yillik.dat isimli dosyayı okuma modunda açtığımızı ifade eder. ("r" = read).
    FILE *girdi = fopen("yillik.dat", "r");

    // Eğer dosya başarılı bir şekilde açılmadıysa; girdi işaretçisi, yani dosya_ac fonksiyonundan dönen değer NULL döner.
    // Bu durumda ekrana hata mesajı yazdırılır ve return 1 komutu ile program çalışmayı durdurur.
    if (girdi == NULL) {
        printf("yillik.dat dosyasi acilamadi.\n");
        return 1;
    }

    // struct Personel, daha önce tanımlanan struct yapısını ifade eder. Bu yapı, bir personelin sicil numarası, adı, soyadı ve satış miktarını içerir.
    // personeller[MAX_PERSONEL], struct Personel tipinde bir dizidir. Bu dizide en fazla 50 personelin bilgileri saklanabilir.
    struct Personel personeller[MAX_PERSONEL];
    // n, dosyadan kaç personel bilgisi okunduğunu takip eden sayaç görevinde bir değişkendir ve başlangıç değeri olarak 0 atarız.
    int n = 0;
    // max_satis, okunan personeller arasındaki en yüksek satış miktarını saklayan değişkendir ve başlangıç değeri olarak 0 atarız.
    int max_satis = 0;

    // fscanf, dosyadan belirli bir formatta veri okumak için kullanılan bir fonksiyondur.
    //Eğer fscanf 4 doğru okuma yaparsa (4 değer okunursa), döngü çalışır. Aksi takdirde döngü sona erer.
    while (fscanf(girdi, "%d %s %s %d",
            // Alttaki bütün dizilerde; okunan veri, n değişkeninin o anki değerine bağlı olarak uygun dizinin n. indisine gönderilir.
                  &personeller[n].sicil_no,
                  personeller[n].ad,
                  personeller[n].soyad,
                  &personeller[n].satis_miktari) == 4) {
        // Yukarıda max_satis değişkenine ilk değer olarak 0 ataması yapılmasının nedeni, bu kısımda sırayla her personelin satış miktarını kıyaslamak içindir.
        // Diziden sırayla okunan her personel için mevcut maksimum değer ile o anki personelin satış miktarı karşılaştırılır.
        // Eğer okunan personelin satış miktarı daha büyükse; max_satis, o personelin satış miktarını tutacak şekilde güncellenir.
        if (personeller[n].satis_miktari > max_satis) {
            max_satis = personeller[n].satis_miktari;
        }
        // n değeri her personelden sonra 1 artılır. Bu; bir sonraki personelin, dizinin bir sonraki indeksine yazılmasını sağlar.
        n++;
    }

    // fclose, dosyayı kapatır. Burada dosya kapatıldıktan sonra, artık dosya üzerinde işlem yapılmaz.
    fclose(girdi);

    // Döngü kullanarak her bir personelin satış miktarını, en yüksek satış miktarından çıkararak dizinin uygun indisine atarız.
    // Bu işlem sonucunda personeller dizisi, güncellenmiş satış miktarlarıyla yeniden düzenlenmiş olur.
    for (int i = 0; i < n; i++) {
        personeller[i].satis_miktari = max_satis - personeller[i].satis_miktari;
    }

    // fopen komutu ile satislar.dat adında bir dosya oluşturulur ya da mevcutsa üzerine yazmak için açılır.
    // "w" (write) dosyanın yazma modunda açıldığını ifader eder. Dosya daha önce varsa içeriğini siler ve yeniden oluşturur.
    FILE *dosya = fopen("satislar.dat", "w");
    // Eğer dosya başarılı bir şekilde açılmadıysa NULL döner.
    // Bu durumda ekrana hata mesajı yazdırılır ve return 1 komutu ile program çalışmayı durdurur.
    if (dosya == NULL) {
        printf("satislar.dat dosyasi acilamadi.\n");
        return 1;
    }

    // Bu kısımda, satış miktarları güncellenen "personeller" dizisini ve diğer dizileri de döngü kullanarak yazdırırız.
    for (int i = 0; i < n; i++) {
        // fprintf fonksiyonu, dosyaya bir metin (text) yazmak için kullanılır.
        fprintf(dosya, "%d %s %s %d\n",
                personeller[i].sicil_no,
                personeller[i].ad,
                personeller[i].soyad,
                personeller[i].satis_miktari); // Eksik satış miktarı
    }
    // Dosya yazma işlemi tamamlandıktan sonra fclose ile dosya kapatılır.
    fclose(dosya);

    // Kullanıcıya, işlem tamamlandığına dair bilgi mesajını ekrana yazdırırız.
    printf("Islem tamamlandi. satislar.dat dosyasina yazildi.\n");

    // Kodun sorunsuz çalıştırıldığını gösterir.
    return 0;
}