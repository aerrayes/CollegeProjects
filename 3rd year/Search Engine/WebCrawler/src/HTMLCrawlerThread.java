import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class HTMLCrawlerThread extends ControllableThread {

	@Override
	public void process(Object o) {
		try {
			URL page = (URL) o;			
			String testUrl = o.toString();
			page = verifyUrl(testUrl);
			
			if (!isRobotAllowed(page))
				return;
			
			String pageContent = getContent(page);
			if (pageContent!=null && pageContent.length() > 0){
				ArrayList <String> links = retrieveLinks(pageContent, page);
				
				for (String link : links) {
					// urls might be relative to current page
					URL newlink = verifyUrl(link);
					queue.push(newlink, level + 1,false);
				}
			}
		}
		catch (Exception e){
			return;
		}
	}
	
	// downloads the page content of the given url
	private String getContent (URL url) throws IOException {
	    BufferedReader reader = null;
	    try {
	        reader = new BufferedReader(new InputStreamReader(url.openStream()));
	        StringBuilder buffer = new StringBuilder();
	        int read;
	        char[] chars = new char[1024];
	        while ((read = reader.read(chars)) != -1)
	            buffer.append(chars, 0, read); 

	        return buffer.toString();
	    } finally {
	        if (reader != null)
	            reader.close();
	    }
	}
	
	
	// Check if robot is allowed to access the given URL.)
		@SuppressWarnings({ "unchecked", "rawtypes" })
		private boolean isRobotAllowed(URL urlToCheck) {
			
			String host = urlToCheck.getHost().toLowerCase();
			// Retrieve host's disallow list from cache.
			
			HashMap disallowListCache = queue.getDisallowedList();
			ArrayList<String> disallowList =  (ArrayList<String>) disallowListCache .get(host);
			// If list is not in the cache, download and cache it.
			if (disallowList == null) {
				disallowList = new ArrayList<String>();
				try {
					URL robotsFileUrl = new URL("http://" + host + "/robots.txt");
					
					robotsFileUrl = removeWwwFromUrl(robotsFileUrl);
					
					// Open connection to robot file URL for reading.
					BufferedReader reader = new BufferedReader(new InputStreamReader(robotsFileUrl.openStream()));
					// Read robot file, creating list of disallowed paths.
					
					String line; char users = ' ';
					while ((line = reader.readLine()) != null) {
						
						if (line.indexOf("User-agent: *") == 0){
							users = '*';
						}
						
						else if (line.indexOf("Disallow:") == 0 && users == '*') {
							
							String disallowPath = line.substring("Disallow:".length());
					
							// Check disallow path for comments and remove if present.
					
							int commentIndex = disallowPath.indexOf("#");
							if (commentIndex != - 1) {
								disallowPath = disallowPath.substring(0, commentIndex);
							}
							
							// Remove leading or trailing spaces from disallow path.
							disallowPath = disallowPath.trim();
							// Add disallow path to list.
							disallowList.add(disallowPath);
						}
					}
					// Add new disallow list to cache.
					disallowListCache.put(host, disallowList);
				}
				catch (Exception e) {
					/* Assume robot is allowed since an exception
					is thrown if the robot file doesn't exist. */
					return true;
				}
			}
			/* Loop through disallow list to see if
			crawling is allowed for the given URL. */
			String file = urlToCheck.getFile();
			for(int i=0;i<disallowList.size(); i++) {
				String disallow = (String) disallowList.get(i);
				
				if (!disallow.equals("") && file.startsWith(disallow)) {
					return false;
				}
			}
			
			return true;
		}
		
	
	private String removeWwwFromUrl(String url) {
		int index = url.indexOf("://www.");
		if (index != -1) {
			return url.substring(0, index + 3) + url.substring(index + 7);
		}
		return url;
	}
	
	private URL removeWwwFromUrl(URL url) throws MalformedURLException {
		String urlString = url.toString();
		urlString = removeWwwFromUrl(urlString);
		return new URL (urlString);
	}
	
	
	
	// Verify URL format.
	private URL verifyUrl(String url) {
		// Only allow HTTP URLs.
		if (!url.toLowerCase().startsWith("http://"))
			return null;
		
		// Verify format of URL.
		URL verifiedUrl = null;
		try {
			verifiedUrl = new URL(url);
		} 
		catch (Exception e) {
			return null;
		}
		
		return verifiedUrl;
	}
	
	
	private ArrayList<String> retrieveLinks (String pageContents,URL pageUrl) {
		ArrayList<String> links = new ArrayList<String>();
		
		Pattern p = Pattern.compile("<a\\s+href\\s*=\\s*\"?(.*?)[\"|>]", Pattern.CASE_INSENSITIVE);
		Matcher matcher = p.matcher(pageContents);
		
		while (matcher.find()){
			String link = matcher.group(1).trim();
			
			// Skip empty links.
			if (link.length() < 1) 
				continue;
			
			// Skip links that are just page anchors.
			if (link.charAt(0) == '#')
				continue;
			
			// Skip mailto links.
			if (link.indexOf("mailto:") != -1) 
				continue;
			
			// Skip JavaScript links.
			if (link.toLowerCase().indexOf("javascript") != -1) 
				continue;
			
			// Skip .pdf files
			if (link.indexOf(".pdf") != -1)
				continue;
			
			// Skip .png files
			if (link.indexOf(".png") != -1)
				continue;
			
			// Skip .jpg files
			if (link.indexOf(".jpg") != -1)
				continue;
			
			// Skip .xml files
			if (link.indexOf(".xml") != -1)
				continue;
			
			// Prefix absolute and relative URLs if necessary.
			if (link.indexOf("://") == -1) {
				
				// Handle absolute URLs.
				if (link.charAt(0) == '/'){
					
					if (link.length() > 1 && link.charAt(1) == '/')
						link = "http:" + link;
					else 
						link = "http://" + pageUrl.getHost() + link;
				}
				
				// Handle relative URLs.
				else {
					String file = pageUrl.getFile();
					if (file.indexOf('/') == -1) 
						link = "http://" + pageUrl.getHost() + "/" + link;
					else {
						String path = file.substring(0, file.lastIndexOf('/') + 1);
						link = "http://" + pageUrl.getHost() + path + link;
					}
				}
			}
			
			
			// Remove anchors from link.
			int index = link.indexOf('#');
			if (index != -1)
				link = link.substring(0, index);
			
			// Remove www from link
			link = removeWwwFromUrl(link);
			
			
			// Verify link and skip if invalid.
			URL verifiedLink = verifyUrl(link);
			if (verifiedLink == null)
				continue;
			
			// remove the last '/' if it exists
			if (link.charAt(link.length()-1) == '/')
				link = link.substring(0,link.length()-1);
			
			// Add link to list.
			links.add(link);
			
		}
		
		return links;
	}
	
	
}
