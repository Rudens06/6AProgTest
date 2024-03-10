/***************************************
    Autori:
        Mihails Daņilovs, md22039
        Rolands Pučeta, rp22046
        Kristofers Semjonovs, ks22110
        Aleksis Volrāts, av22110
        Ralfs Čipāns, rc22007
***************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Nosaka kļūdu kodus un atbilstošos kļūdu ziņojumus
enum ErrorCode
{
    SUCCESS,
    ERROR_001,
    ERROR_002,
    ERROR_004,
    ERROR_009,
    ERROR_011,
};

string getErrorMessage(ErrorCode error)
{
    switch (error)
    {
    case ERROR_001:
        return "Lūdzu aizpildiet visus obligātos laukus!";
    case ERROR_002:
        return "Kļūda ievadē! Pārliecinieties, vai ievadītie dati ir pareizi!";
    case ERROR_004:
        return "Attēls ir lielāks par maksimālo atļauto izmēru!";
    case ERROR_009:
        return "Ievadītais teksts pārsniedz atļauto simbolu skaitu!";
    case ERROR_011:
        return "Attēlam jābūt formātā JPEG, JPG vai PNG!";
    default:
        return "Kļūda! Lūdzu atkārtojiet darbību!";
    }
}

bool validatePrice(const string &input)
{
    if (input.empty())
        return false;

    // Pārbauda vai ievade sastāv tikai no cipariem un viena decimālpunkta
    bool dotFound = false;
    for (char c : input)
    {
        if (!isdigit(c))
        {
            if (c == '.' && !dotFound)
            {
                dotFound = true;
            }
            else
            {
                return false;
            }
        }
    }

    // Pārbauda vai decimālpunkts nav sākumā vai beigās
    if (input.front() == '.' || input.back() == '.' || input.find('.') != input.rfind('.'))
    {
        return false;
    }

    // Sadala ievadu veselā un decimāldaļā
    string integerPart, fractionalPart;
    size_t dotPos = input.find('.');
    if (dotPos == string::npos)
    {
        integerPart = input;
    }
    else
    {
        integerPart = input.substr(0, dotPos);
        fractionalPart = input.substr(dotPos + 1);
    }

    // Datu validācija
    if (integerPart.size() > 4 || fractionalPart.size() > 2)
    {
        return false;
    }

    // Pievieno trukstošās nulles decimāldaļai, ja nepieciešams
    if (fractionalPart.empty())
    {
        fractionalPart = "00";
    }
    else if (fractionalPart.size() == 1)
    {
        fractionalPart += "0";
    }

    // Pārveido uz skaitli datu validācijai
    int integer = stoi(integerPart);
    int fractional = stoi(fractionalPart);

    // Pārbauda vai cena ir lielāka par 0
    if (integer == 0 && fractional == 0)
    {
        return false;
    }

    return true;
}
// Maketa struktūra, kas raksturo attēlu
struct Image
{
    string format; // "JPEG", "JPG", "PNG"
    size_t size;   // Attēla izmērs baitos
};

// Funkcija, lai izveidotu kursu
ErrorCode createCourse(const string &courseName, const string &courseCategory, const Image &previewImage, const string &courseDescription, const string coursePrice)
{
    // Pārbauda obligātos laukus
    if (courseName.empty() || courseCategory.empty() || courseDescription.empty() || coursePrice.empty())
    {
        return ERROR_001;
    }
    if (!validatePrice(coursePrice))
    { // Pārbauda cenas formātu
        return ERROR_002;
    }
    if (previewImage.size > 3 * 1024 * 1024)
    { // Pārbauda attēla izmēru (maksimālais izmērs 3MB)
        return ERROR_004;
    }
    // Pārbauda ievades garumu un formātus
    if (courseName.length() > 100 || courseCategory.length() > 100 || courseDescription.length() > 1000)
    {
        return ERROR_009;
    }
    // Pārbauda attēla formātu
    if (previewImage.format != "JPEG" && previewImage.format != "JPG" && previewImage.format != "PNG")
    {
        return ERROR_011;
    }

    // Simulē kursa saglabāšanu datu bāzē
    // cout << "Kurss izveidots!" << endl;
    // cout << "Kursa nosaukums: " << courseName << ", Kategorija: " << courseCategory << ", Cena: " << coursePrice << endl;

    return SUCCESS;
}

/// TESTĒŠANAS FUNKCIJA DATU PĀRBAUDĒM (TEST CASES)

void testCreateCourse(int testCaseID, ErrorCode expectedResult, string courseName, string categoryName, Image image, string description, string price) {
    ErrorCode result = createCourse(courseName, categoryName, image, description, price);
    if (result == expectedResult)
    {
        cout << "#" << testCaseID << ": Passed" << endl;
    }
    else
    {
        cout << "#" << testCaseID << ": Failed" << endl;
    }
}

void functionTesting()
{
    // Valid function inputs
    string validCourseName = "course 1";
    string validCategoryName = "category 1";
    Image validImage = {"JPEG", 1024 * 1024};
    string validDescription = "This is a valid description";
    string validPrice = "10.00";
    
    // Testing Variable definition
    string emptyString = "";
    string hundredSymbolString = "PK9fpGN0MH#M.UjiE7X4#[k8AqdeVpQ&w5}*76BqQA5A*%]bcN@cP;jqv*:1f]cGj4RF[yFzx{K$L[3[chL0QAT!MpMg(:n+!*$h";
    string moreThanHundredSymbolString = "PK9fpGN0MH#M.UjiE7X4#[k8AqdeVpQ&w5}*76BqQA5A*%]bcN@cP;jqv*:1f]cGj4RF[yFzx{K$L[3[chL0QAT!MpMg(:n+!*$hqsssda";
    
    string thousandSymbolString = "=bRDGzZSALt/H9GmbkhiRm-HQDv{L1wc#x[0!0wThG}G4GY#{*-;xjUa}%E(_&g&GF].p-[YQN3p{4w1J).]KQCe.9kZR0]U1)6-AjvM8p6X!m.vw%FWG*@2$uP/*cP0mQ$)dnGk:D;DH6iyLN@UpQ1[tM8N,1$RR&Ck39Nk}R1V57/W+1pmUqfAiEgCLqW#+!rt*{mtAgJmmD){{5kktwtW+S:Qb&yNQMDcVfQ14f/(n9!w5JUx4kT@H:bgd(6apARPgRg-vqcY$+_!deMLF]k[zg!1?])N%P8C9ubGQ(2!d),{K4!m&=Lwv3dFy!]Ej{4pGvmR&NZt%]2XF3k=PL@!13Zx?B)?LyXe2ppZfhEKQmk*JyC5*)W:MV8@qR8.MTfv]VRw@eVyV@NBrXKE=0F#VF6Uzwu:GD@[3[T_VB:8q6U4R0()F)jN0AB9ULynck@DraS*LVLME3cGL&2SE4?uU51qFa+#d6/($%F9hf*yb!1,8ae]CDWcDU];,8q{.fw51Hi)7DNrx!83pb7/=ivN3w=#_2*$[a4[:{){*:Fpk=#rb)b,+BAj8Ga4jbE3%U*[QM&r#Rj9PT%nGS/b=agjaDak;Zb;iq=5LaXS5B%Q2j[Mg?JgXbMRK3#210{W0.!Vw5krddEn2H+/hX4_fg5MyihrSgBiU/gv_?Z9P!L5VeVH]Q+G}{.d)qzBhR!29EjkuY;0{6kE)J.wbt4SFH;@h1M6bY6Z9?7{=m!0Y}by$vn{wjUH11BN**k:E=8wZ{H,6U0k[H+@9w)RGWFHKM)KE7C#g}7f=b?{SMSw4[F.h0v)T%2HZH(+6(.,ZcMiHcH4P1{+W*w[!xGeiphVKVNR#0S?4gt5irv.pU=!gpYaQqW=4gJa*K#?N[K7:97dZ.i;!dQ3p:]kZNc2-HK;2.F0Pf;c1,khH&vR(%x0gmt!eh&wV%_6F%ny{kD+WRRaDX$_WU)3*6M&gbU,!Nm5g#C34MvFwvWg+hkxqcK#";
    
    string moreThanThousandSymbolString = "=bRDGzZSALt/H9GmbkhiRm-HQDv{L1wc#x[0!0wThG}G4GY#{*-;xjUa}%E(_&g&GF].p-[YQN3p{4w1J).]KQCe.9kZR0]U1)6-AjvM8p6X!m.vw%FWG*@2$uP/*cP0mQ$)dnGk:D;DH6iyLN@UpQ1[tM8N,1$RR&Ck39Nk}R1V57/W+1pmUqfAiEgCLqW#+!rt*{mtAgJmmD){{5kktwtW+S:Qb&yNQMDcVfQ14f/(n9!w5JUx4kT@H:bgd(6apARPgRg-vqcY$+_!deMLF]k[zg!1?])N%P8C9ubGQ(2!d),{K4!m&=Lwv3dFy!]Ej{4pGvmR&NZt%]2XF3k=PL@!13Zx?B)?LyXe2ppZfhEKQmk*JyC5*)W:MV8@qR8.MTfv]VRw@eVyV@NBrXKE=0F#VF6Uzwu:GD@[3[T_VB:8q6U4R0()F)jN0AB9ULynck@DraS*LVLME3cGL&2SE4?uU51qFa+#d6/($%F9hf*yb!1,8ae]CDWcDU];,8q{.fw51Hi)7DNrx!83pb7/=ivN3w=#_2*$[a4[:{){*:Fpk=#rb)b,+BAj8Ga4jbE3%U*[QM&r#Rj9PT%nGS/b=agjaDak;Zb;iq=5LaXS5B%Q2j[Mg?JgXbMRK3#210{W0.!Vw5krddEn2H+/hX4_fg5MyihrSgBiU/gv_?Z9P!L5VeVH]Q+G}{.d)qzBhR!29EjkuY;0{6kE)J.wbt4SFH;@h1M6bY6Z9?7{=m!0Y}by$vn{wjUH11BN**k:E=8wZ{H,6U0k[H+@9w)RGWFHKM)KE7C#g}7f=b?{SMSw4[F.h0v)T%2HZH(+6(.,ZcMiHcH4P1{+W*w[!xGeiphVKVNR#0S?4gt5irv.pU=!gpYaQqW=4gJa*K#?N[K7:97dZ.i;!dQ3p:]kZNc2-HK;2.F0Pf;c1,khH&vR(%x0gmt!eh&wV%_6F%ny{kD+WRRaDX$_WU)3*6M&gbU,!Nm5g#C34MvFwvWg+hkxqcK#sdgsd";

    Image JPEGImage = {"JPEG", 1024 * 1024};
    Image PNGImage = {"PNG", 1024 * 1024};
    Image JPGImage = {"JPG", 1024 * 1024};
    Image TIFFImage = {"TIFF", 1024 * 1024};
    Image ABCDImage = {"ABCD", 1024 * 1024};
    Image size0mbImage = {"JPG", 0};
    Image size3mbImage = {"JPEG", 1024 * 1024 * 3};
    Image moreThan3mbImage = {"JPEG", 1024 * 1024 * 30};

    string negativePrice = "-10";
    string zeroPrice = "0";
    string maxPrice = "9999.99";

    // courseName TESTS
    testCreateCourse(1, ERROR_001, emptyString, validCategoryName, validImage, validDescription, validPrice);
    testCreateCourse(2, SUCCESS, validCourseName, validCategoryName, validImage, validDescription, validPrice);
    testCreateCourse(3, SUCCESS, hundredSymbolString, validCategoryName, validImage, validDescription, validPrice);
    testCreateCourse(4, ERROR_009, moreThanHundredSymbolString, validCategoryName, validImage, validDescription, validPrice);
    // courseName TESTS END

    // courseCategory TESTS
    testCreateCourse(5, ERROR_001, validCourseName, emptyString, validImage, validDescription, validPrice);
    testCreateCourse(6, SUCCESS, validCourseName, hundredSymbolString, validImage, validDescription, validPrice);
    testCreateCourse(7, ERROR_009, validCourseName, moreThanHundredSymbolString, validImage, validDescription, validPrice);
    // courseDescription TESTS END

    // Image TESTS
    testCreateCourse(8, SUCCESS, validCourseName, validDescription, JPEGImage, validDescription, validPrice);
    testCreateCourse(9, SUCCESS, validCourseName, validDescription, PNGImage, validDescription, validPrice);
    testCreateCourse(10, SUCCESS, validCourseName, validDescription, JPGImage, validDescription, validPrice);
    testCreateCourse(11, ERROR_011, validCourseName, validDescription, TIFFImage, validDescription, validPrice);
    testCreateCourse(12, ERROR_011, validCourseName, validDescription, ABCDImage, validDescription, validPrice);
    testCreateCourse(13, SUCCESS, validCourseName, validDescription, size0mbImage, validDescription, validPrice);
    testCreateCourse(14, SUCCESS, validCourseName, validDescription, size3mbImage, validDescription, validPrice);
    testCreateCourse(15, ERROR_004, validCourseName, validDescription, moreThan3mbImage, validDescription, validPrice);
    // Image TESTS END

    // courseDescription TESTS
    testCreateCourse(16, ERROR_001, validCourseName, validCategoryName, validImage, emptyString, validPrice);
    testCreateCourse(17, SUCCESS, validCourseName, validCategoryName, validImage, thousandSymbolString, validPrice);
    testCreateCourse(18, ERROR_009, validCourseName, validCategoryName, validImage, moreThanThousandSymbolString, validPrice);
    // courseDescription END

    // coursePrice TESTS
    testCreateCourse(19, ERROR_002, validCourseName, validCategoryName, validImage, validDescription, negativePrice);
    testCreateCourse(20, SUCCESS, validCourseName, validCategoryName, validImage, validDescription, maxPrice);
    testCreateCourse(21, ERROR_002, validCourseName, validCategoryName, validImage, validDescription, hundredSymbolString);
}

int main()
{
    try
    { /// Pārbaudes nolūkiem (datu testēšanai) mainiet vērtības "Image courseImage" un "ErrorCode result"
        /// Vēlams, ka tiek izmantota functionTesting() funkcija, lai testētu funkciju createCourse()
        /// Formāts priekšskatījuma attēlam(courseImage): {string formāts, size_t izmērs_baitos}
        /// Atļautie formāti: "JPEG", "JPG", "PNG"
        Image courseImage = {"PNG", 3 * 1024 * 1024};
        /// Formāts kursa izveidnei(result): {string nosaukums, string kategorija, Image priekšskatījuma_attēls, string apraksts, string cena}
        ErrorCode result = createCourse("Ievads programmēšanā", "Datorzinātnes", courseImage, "Šis kurss piedāvā ievadu programmēšanā ar C++.", "99.99");
        if (result != SUCCESS)
        {
            throw getErrorMessage(result);
        }
    }
    catch (string error)
    {
        cout << error << endl;
    }

    /// Izsaukums testēšanas funkcijai
    try
    {
        functionTesting(); // Atkomentēt pēc nepieciešamības
    }
    catch (string error)
    {
        cout << error << endl;
    }

    return 0;
}