import java.util.Calendar;


public class CrawledLink {
	Calendar date;
	String URL;
	int offset;
	
	public int getOffset() {
		return offset;
	}

	public void setOffset(int offset) {
		this.offset = offset;
	}

	CrawledLink(Calendar date,String URL){
		this.date = date;
		this.URL = URL;
		offset = 1+(int)(Math.random()*((60-1)+1));
	}
	
	public Calendar getDate() {
		return date;
	}
	public void setDate(Calendar date) {
		this.date = date;
	}
	public String getURL() {
		return URL;
	}
	public void setURL(String uRL) {
		URL = uRL;
	}
}
