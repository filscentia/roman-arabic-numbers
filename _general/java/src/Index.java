import java.io.BufferedReader;
import java.io.FileReader;

import filscentia.numerals.ConvertRomanNumeral;

public class Index {

    // need to read stdin and get the files to convert
    // need interactive mode
	public static void main(String... args) {
        ConvertRomanNumeral crn = new ConvertRomanNumeral();

        if (args[0].equals("--file") || args[0].equals("-f")){

        	System.out.println("--START--");
            try (BufferedReader br = new BufferedReader(new FileReader(args[1]))){
            	 String line;
            	 while ((line=br.readLine()) != null ){
            		 System.out.println(line+","+crn.process(line));
            	 }
            	 
            } catch (Exception e){
                e.printStackTrace();
            }
            System.out.println("--END--");
        }
		
	}
	
	

}