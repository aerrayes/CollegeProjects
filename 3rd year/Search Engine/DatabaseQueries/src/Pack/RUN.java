package Pack;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;

import DBCon.DBCon;


public class RUN {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		DBCon.checkHashCode("yah.com", 1234);
//		DBCon.checkHashCode("yah.com", 1234);
//		DBCon.checkHashCode("yah.com", 4244);
//		
//
//		DBCon.checkHashCode("yah.com", 1234);
		DBCon.checkHashCode("abcs.com", -434);
		
		//DBCon.insert("abc", "FF.com", 1, 44);
		
		//DBCon.insert("abc", "FF.com", 1, 424);
		//DBCon.insert("asd", "FF.com", 1, 123);
		//System.out.println(DBCon.getURLbyKeywordsOR(sarr));
		
		//System.out.println(DBCon.getURLbyKeywordsAND(sarr));
		
		//DBCon.insert("aha","yah.com",1,5);
		//DBCon.insert("gasg", "yah.com",2,10);
		//DBCon.insert("gasg", "abcs.com",2,50);
		//DBCon.insert("has", "abcs.com",3,4);
		//DBCon.insert("gassg", "abcs.com",2,600);
		
		ArrayList<KeywordInURL> abc=DBCon.getKeywordInURLFromURL("abcs.com");
		for(int i = 0 ; i < abc.size();i++)
			System.out.println(abc.get(i).getKeyword()+" "+abc.get(i).getPriority()+" "+abc.get(i).getFrequency()+" ");
//		System.out.println(DBCon.getKeywordFromURL("yah.com"));
//		System.out.println(DBCon.getKeywordFromURL("abcs.com"));
//
//		System.out.println(DBCon.getURLsByKeyword("aha"));
//		System.out.println(DBCon.getURLsByKeyword("gasg"));
//		System.out.println(DBCon.getKeywordURLWithMissingChar("gas_g"));
//		ArrayList<String>keywords = new ArrayList<String>();
//		keywords.add("gasg");
//		keywords.add("aha");
//		HashMap<String,Double> hm = new HashMap<String,Double>();
//		hm.put("yah.com", new Double(3.12));
//		hm.put("abcs.com", 0.132);
//		DBCon.updateRank(hm);
//		System.out.println(DBCon.getURLbyKeywordsOR(keywords));
		
		
	}

}
