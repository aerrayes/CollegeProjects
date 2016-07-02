import java.util.HashMap;
import java.util.Set;


@SuppressWarnings("rawtypes")
public interface Queue {
	public int getQueueSize(int level);
	public int getCrawledListSize();
	public Set getCrawledLinks ();
	public void setMaxElements(int elements);
	public Object pop(int level);
	public HashMap getDisallowedList ();
	public boolean push(Object task, int level,boolean recrawl);
	public void clear();
}
