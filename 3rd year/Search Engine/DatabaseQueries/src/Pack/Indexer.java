package Pack;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

public final class Indexer {
	
	public enum Priority {
		TITLE,HEADER,PLAIN
	}
	
	/*
	 * The stopWords list represents the list of words that have little value in finding useful links in response to the user query
	 */
	private static final List<String> stopWords = Arrays.asList("a", "about", "above", "above", "across", "after", "afterwards", "again", "against", "all", "almost", "alone", "along", "already", "also","although","always","am","among", "amongst", "amoungst", "amount",  "an", "and", "another", "any","anyhow","anyone","anything","anyway", "anywhere", "are", "around", "as",  "at", "back","be","became", "because","become","becomes", "becoming", "been", "before", "beforehand", "behind", "being", "below", "beside", "besides", "between", "beyond", "bill", "both", "bottom","but", "by", "call", "can", "cannot", "cant", "co", "con", "could", "couldnt", "cry", "de", "describe", "detail", "do", "done", "down", "due", "during", "each", "eg", "eight", "either", "eleven","else", "elsewhere", "empty", "enough", "etc", "even", "ever", "every", "everyone", "everything", "everywhere", "except", "few", "fifteen", "fify", "fill", "find", "fire", "first", "five", "for", "former", "formerly", "forty", "found", "four", "from", "front", "full", "further", "get", "give", "go", "had", "has", "hasnt", "have", "he", "hence", "her", "here", "hereafter", "hereby", "herein", "hereupon", "hers", "herself", "him", "himself", "his", "how", "however", "hundred", "ie", "if", "in", "inc", "indeed", "interest", "into", "is", "it", "its", "itself", "keep", "last", "latter", "latterly", "least", "less", "ltd", "made", "many", "may", "me", "meanwhile", "might", "mill", "mine", "more", "moreover", "most", "mostly", "move", "much", "must", "my", "myself", "name", "namely", "neither", "never", "nevertheless", "next", "nine", "no", "nobody", "none", "noone", "nor", "not", "nothing", "now", "nowhere", "of", "off", "often", "on", "once", "one", "only", "onto", "or", "other", "others", "otherwise", "our", "ours", "ourselves", "out", "over", "own","part", "per", "perhaps", "please", "put", "rather", "re", "same", "see", "seem", "seemed", "seeming", "seems", "serious", "several", "she", "should", "show", "side", "since", "sincere", "six", "sixty", "so", "some", "somehow", "someone", "something", "sometime", "sometimes", "somewhere", "still", "such", "system", "take", "ten", "than", "that", "the", "their", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "therefore", "therein", "thereupon", "these", "they", "thickv", "thin", "third", "this", "those", "though", "three", "through", "throughout", "thru", "thus", "to", "together", "too", "top", "toward", "towards", "twelve", "twenty", "two", "un", "under", "until", "up", "upon", "us", "very", "via", "was", "we", "well", "were", "what", "whatever", "when", "whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "whereupon", "wherever", "whether", "which", "while", "whither", "who", "whoever", "whole", "whom", "whose", "why", "will", "with", "within", "without", "would", "yet", "you", "your", "yours", "yourself", "yourselves", "the");
	
	
	/* 
	 * The index itself can be efficiently represented as a Hash map where the key is a certain word and the value is a list of (urls/priorities) associated with this key.
	 * (Without including the priority in our Indexer. This implementation is known as the Inverted Index)
	 */
	private static HashMap < String ,List<Word> > Index = new HashMap< String, List<Word>>();
	
	
	/*
	 * The Stemmer Class to implement the term Stemming algorithm (for more details see the comments on the Stemmer Class) 
	 */
	private static Stemmer stemmer = new Stemmer();
	
	
	private Indexer(){
	}
	
	public static List<Word> lookUp (String keyWord){
		if (Index.containsKey(keyWord))
			return Index.get(keyWord);
		else
			return null;
	}
	
	public static void addPageToIndex (String page,String url){
		
		//Parse the HTML document
		Document doc = Jsoup.parse(page);
		
		//Retrieve the body , header and title.
		String body = doc.select("body").text();
		String title = doc.title();
		String header = doc.select("header").text();
		
		String[] headerSplit = header.split("[\\W]");
		String[] titleSplit = title.split("[\\W]");
		
		//Assuming the title has a higher priority then the header then the body.
		//First, Split the title and index it with a priority : TITLE
		
		for(String word : titleSplit){
			if (!stopWords.contains(word)){      //ignore stop words
				stemmer.add(word.toCharArray(), word.length());
				stemmer.stem();  // stem the word
				addToIndex(stemmer.toString(), url,Priority.TITLE);
			}
		}
		
		//Second Index the header with a priority : HEADER
		
		for(String word : headerSplit){
			if (!stopWords.contains(word)){       // ignore stop words
				stemmer.add(word.toCharArray(), word.length()); 
				stemmer.stem();
				addToIndex(stemmer.toString(), url,Priority.HEADER);
			}
		}
		
		
		//Before we can split and index the body we need to make sure to remove the header part from the body first
		//to avoid repetition
		
		
		StringBuilder bodyStringBuilder = new StringBuilder(body);
		int startIndexOfHeader = body.indexOf(header);
		bodyStringBuilder.replace(startIndexOfHeader, startIndexOfHeader+header.length(), "");
		
		
		//now we can split the body
		String[] bodySplit = bodyStringBuilder.toString().split("[\\W]");
		
		
		for(String word : bodySplit){
			if (!stopWords.contains(word)){		// ignore stop words
				stemmer.add(word.toCharArray(), word.length());
				stemmer.stem();
				addToIndex(stemmer.toString(), url,Priority.PLAIN);
			}
		}
	}
	
	
	/*
	 * if a current word already exists in the index as a key , then update the list with the new enry
	 * else , create a new entry in the index.
	 */
	
	private static void addToIndex (String keyWord, String url,Priority p){
		
//		if (Index.containsKey(keyWord))
//			Index.get(keyWord).add(new Word(p,url));
//		else{
//			List<Word> s = new ArrayList<Word>();
//			s.add(new Word(p,url));
//			Index.put(keyWord, s);
//		}
	}
}


/*
 *  The Word class represent the priority of the word in a given link
 */
