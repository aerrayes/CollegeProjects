import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Set;


@SuppressWarnings("rawtypes")
public class URLQueue implements Queue {
	public enum STATUS{CRAWL,RECRAWL};
	LinkedList evenQueue;
	LinkedList oddQueue;
	Set crawledLinks;
	private HashMap disallowListCache;
	PriorityQueue<CrawledLink> crawledPQ = new PriorityQueue<CrawledLink>(11, new Comparator<CrawledLink>() {
		@Override
		public int compare(CrawledLink o1, CrawledLink o2) {
			if(o1==null) return 1;
			if(o2 == null) return -1;
			if(o1.getDate().before(o2.getDate()))
				return -1;
			else if(o1.getDate().after(o2.getDate()))
				return 1;
			return 0;
		}
		
	});
	public PriorityQueue<CrawledLink> getCrawledPQ() {
		return crawledPQ;
	}

	public void setCrawledPQ(PriorityQueue<CrawledLink> crawledPQ) {
		this.crawledPQ = crawledPQ;
	}

	/**
	 * Maximum number of elements allowed in the gatheredLinks set
	 */
	int maxElements;
	
	
	public URLQueue() {
		evenQueue = new LinkedList();
		oddQueue = new LinkedList();
		crawledLinks = new HashSet();
		disallowListCache = new HashMap<String, ArrayList<String>>();
		maxElements = -1;
	}

	public URLQueue(int _maxElements, String _filenamePrefix) {
		evenQueue = new LinkedList();
		oddQueue = new LinkedList();
		crawledLinks = new HashSet();
		maxElements = _maxElements;
	}

	@Override
	public int getQueueSize(int level) {
		if (level % 2 == 0) {
			return evenQueue.size();
		} else {
			return oddQueue.size();
		}
	}
	
	@Override
	public int getCrawledListSize (){
		return crawledLinks.size();
	}

	@Override
	public Set getCrawledLinks() {
		return crawledLinks;
	}

	@Override
	public void setMaxElements(int elements) {
		maxElements = elements;
	}
	
	/**
	 * Return and remove the first element from the appropriate queue
	 */
	@Override
	public synchronized Object pop(int level) {
		String s;
		// try to get element from the appropriate queue
		// is the queue is empty, return null
		if (level % 2 == 0) {
			if (evenQueue.size() == 0) {
				return null;
			} else {
				s = (String) evenQueue.removeFirst();
			}
		} else {
			if (oddQueue.size() == 0) {
				return null;
			} else {
				s = (String) oddQueue.removeFirst();
			}
		}
		// convert the string to a url and add to the set of processed links
		try {
			URL url = new URL(s);
			return url;
		} catch (MalformedURLException e) {
			// shouldn't happen, as only URLs can be pushed
			return null;
		}
	}

	@SuppressWarnings("unchecked")
	@Override
	public synchronized boolean push(Object url, int level, boolean recrawl) {
		
		// don't allow more than maxElements links to be gathered
		if (maxElements != -1 && maxElements <= crawledLinks.size())
			return false;
		
		String urlString = ((URL) url).toString();
		
		if (recrawl ||crawledLinks.add(urlString)){
			// has not been crawled yet, so save in the appropriate queue
			// schedules the next time the crawler will recrawl this page.
			CrawledLink cwl;
			Calendar nextTime = Calendar.getInstance();
			if(recrawl) 
				 cwl =getCrawledPQ().remove();
			else
				cwl = new CrawledLink(nextTime,urlString);
			cwl.setOffset(1+(int)(Math.random()*((60-1)+1)));
			nextTime.add(Calendar.MINUTE, cwl.getOffset());
			cwl.setDate(nextTime);
			getCrawledPQ().add(cwl);
			System.out.println(urlString);
			
			if (level % 2 == 0){
				evenQueue.add(urlString);
			}
			
			else {
				oddQueue.add(urlString);
			}
			return true;
		}
		// the link has already been crawled
		return false;
	}

	@Override
	
	/**
	 * Clear both queues
	 */
	public synchronized void clear() {
		evenQueue.clear();
		oddQueue.clear();
	}

	@Override
	public HashMap getDisallowedList() {
	
		return disallowListCache;
	}

}
