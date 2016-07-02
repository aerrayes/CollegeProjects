package Pack;

public class KeywordInURL {

	String keyword;
	int priority;
	int frequency;
	public KeywordInURL(String _keyword,int _priority,int _frequency)
	{
		keyword = _keyword;
		priority = _priority;
		frequency = _frequency;
		
	}
	public String getKeyword() {
		return keyword;
	}
	public void setKeyword(String keyword) {
		this.keyword = keyword;
	}
	public int getPriority() {
		return priority;
	}
	public void setPriority(int priority) {
		this.priority = priority;
	}
	public int getFrequency() {
		return frequency;
	}
	public void setFrequency(int frequency) {
		this.frequency = frequency;
	}
}
