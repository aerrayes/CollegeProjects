package Pack;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;


public final class U_Ranker {
	
	// Empty Constructor
	private U_Ranker(){
	}
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public static HashMap <String,Double> computeRanks (HashMap <String ,List<String> > linkGraph){
		
		double d = 0.8; // damping factor
		int numLoops = 10;
		
		HashMap <String,Double> ranks = new HashMap <String,Double> ();
		int npages = linkGraph.size();
		
		// initialize ranks
		Iterator it = linkGraph.entrySet().iterator();
		while (it.hasNext()){
			Map.Entry pairs = (Map.Entry)it.next();
			ranks.put((String) pairs.getKey(), 1.0/npages);
		}
		
		for (int i=0;i<numLoops;i++){
			HashMap <String,Double> newRanks = new HashMap <String,Double> ();
			
			Iterator _it = linkGraph.entrySet().iterator();
			while (_it.hasNext()){
				Map.Entry pairs = (Map.Entry)_it.next();
				
				String page = (String) pairs.getKey();
				
				double newRank = (1-d) / npages;
				
				
				Iterator _it2 = linkGraph.entrySet().iterator();
				while (_it2.hasNext()){
					Map.Entry _pairs = (Map.Entry)_it2.next();
					
					String node = (String) _pairs.getKey();
					
					List<String> correspondingLinks = (List<String>) _pairs.getValue();
					
					if (correspondingLinks.contains(page))
						newRank += d * (ranks.get(node) / correspondingLinks.size()); 	
				}
				newRanks.put(page, newRank);
			}
			ranks = (HashMap<String, Double>) newRanks.clone();
		}
		return ranks;
	}
}
