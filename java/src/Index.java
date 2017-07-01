import filscentia.numerals.*;

public class Index {

	public static void main(String... args) {
        ConvertRomanNumeral crn = new ConvertRomanNumeral();
        for (int i=1; i<3500;i++){
            System.out.println(" "+i+" , "+crn.fromArabicToRoman(i));
        }
		
	}

}