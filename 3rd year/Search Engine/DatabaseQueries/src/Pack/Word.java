package Pack;

public class Word {
	
	Word (Indexer.Priority _priority,String _url,int _frequency){
		priority = _priority;
		url = _url;
		frequency = _frequency;
	}
	Indexer.Priority priority;
	String url;
	int frequency;
	public int getFrequency() {
		return frequency;
	}
	public void setFrequency(int frequency) {
		this.frequency = frequency;
	}
	public Indexer.Priority getPriority() {
		return priority;
	}
	public void setPriority(Indexer.Priority priority) {
		this.priority = priority;
	}
	public String getUrl() {
		return url;
	}
	public void setUrl(String url) {
		this.url = url;
	}
}
