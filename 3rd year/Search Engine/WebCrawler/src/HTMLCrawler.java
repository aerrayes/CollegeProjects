import java.net.URL;
import java.util.Calendar;
import java.util.PriorityQueue;



public class HTMLCrawler {
	@SuppressWarnings("unused")
	public HTMLCrawler(Queue q, int maxLevel, int maxThreads) 
			throws InstantiationException, IllegalAccessException {
			ThreadController tc = new ThreadController(HTMLCrawlerThread.class,maxThreads,maxLevel,q,0);
	}
	
	public static void main(String[] args) {
		
		try {
			
			int maxLevel = 2;
			int maxThreads = 3;
			String seedPage = "http://xkcd.com";
			URLQueue q = new URLQueue();
			q.push(new URL(seedPage), 0,false);
			new HTMLCrawler(q, maxLevel, maxThreads);
			while(true){
				PriorityQueue<CrawledLink> pq= q.getCrawledPQ();
				if(pq.size()!=0)
				{
					CrawledLink crawledLink =pq.peek();
					Calendar date = crawledLink.getDate();
					Calendar now = Calendar.getInstance();
					if(now.equals(date)||now.after(date)){
						//pq.remove();
						System.out.println("****nowrecrawling "+crawledLink.getURL()+" ****");
						q.push(new URL(crawledLink.getURL()), 0, true);
					}
				}
			}
		} catch (Exception e) {
			System.err.println("An error occured: ");
			e.printStackTrace();
			// System.err.println(e.toString());
		}
		
	}
}
