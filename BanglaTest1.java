package BanglaWordTesting;

public class BanglaTest1 {

	public static void main(String[] args) {
		String word = "বিড় দচড";
		System.out.println(word);
		
		for(int i=0;i<word.length();i++){
			   System.out.println(word.charAt(i));
			   System.out.println(Integer.toHexString(word.charAt(i)));
		}
	}

}
