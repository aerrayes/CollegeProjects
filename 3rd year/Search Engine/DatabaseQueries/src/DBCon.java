package DBCon;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map.Entry;

import Pack.LinkIndex;
import Pack.Word;

public class DBCon {
	static String host = "jdbc:mysql://localhost:3306/keywordurl";
	static String uName = "root";
	static String uPass = "password";

	// Retrieves the id of a given URL
	private static int getURLId(String URL) {
		try {
			Connection con = DriverManager.getConnection(host, uName, uPass);

			String query = "SELECT urlid from link WHERE url='" + URL + "'";
			ResultSet result = con.createStatement().executeQuery(query);
			int urlID = -1;
			if (result.next()) {
				urlID = result.getInt("urlid");
			} else {

				System.out
						.println("SOMETHING IS SO WRONG HERE! IT SHOULD BE INSERTED!");

			}

			con.close();
			return urlID;
		} catch (Exception e) {
		}
		return -1;
	}

	// search for this keyword in DB if it doesn't exist then it inserts it and
	// gets the ID
	private static int getKeywordId(String keyword) {
		try {
			Connection con = DriverManager.getConnection(host, uName, uPass);

			String query = "SELECT keywordid from keyword WHERE keyword='"
					+ keyword + "'";
			ResultSet result = con.createStatement().executeQuery(query);
			int keywordid = -1;
			if (result.next()) {
				keywordid = result.getInt("keywordid");
			} else {
				query = "INSERT INTO keyword VALUES (default,?)";
				PreparedStatement ppKeyword = con.prepareStatement(query);
				ppKeyword.setString(1, keyword);
				ppKeyword.executeUpdate();
				query = "SELECT keywordid from keyword WHERE keyword='"
						+ keyword + "'";
				result = con.createStatement().executeQuery(query);
				if (result.next()) {
					keywordid = result.getInt("keywordid");
				} else {
					System.out
							.println("SOMETHING IS SO WRONG HERE! I JUST INSERTED!");

				}
			}
			con.close();
			return keywordid;
		} catch (Exception e) {
		}
		return -1;

	}

	// Retrieves URLs that have the same keyword
	public static ArrayList<String> getURLsByKeyword(String keyword) {

		try {
			Connection con = DriverManager.getConnection(host, uName, uPass);
			// adds it again can be removed
			int keywordid = getKeywordId(keyword);
			ResultSet result = con.createStatement().executeQuery(
					"SELECT link.url FROM keyword_url,link where keyword_url.keywordid = '"
							+ keywordid + "' AND keyword_url.urlid=link.urlid");
			ArrayList<String> arr = new ArrayList<String>();
			while (result.next()) {
				arr.add(result.getString("url"));
			}
			con.close();
			return arr;

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}

	// Retrieves keywords in a certain URL
	public static ArrayList<String> getKeywordFromURL(String URL) {

		try {
			Connection con = DriverManager.getConnection(host, uName, uPass);
			int urlid = getURLId(URL);
			if (urlid == -1) {
				con.close();
				System.out.println("This URL Isn't Indexed");
				return null;
			}
			ResultSet result = con.createStatement().executeQuery(
					"SELECT keyword.keyword FROM keyword_url,keyword where "
							+ "keyword_url.urlid ='" + urlid
							+ "' AND keyword_url.keywordid=keyword.keywordid");
			ArrayList<String> arr = new ArrayList<String>();
			while (result.next()) {
				arr.add(result.getString("keyword"));
			}
			con.close();
			return arr;

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}

	public static boolean insert(String keyword, String url, int priority,
			int index) {

		try {
			Connection con = DriverManager.getConnection(host, uName, uPass);

			int keywordid = getKeywordId(keyword);
			int urlid = getURLId(url);
			PreparedStatement pp = con
					.prepareStatement("INSERT INTO keyword_url VALUES (default,?,?,?,?)");
			pp.setString(1, Integer.toString(keywordid));
			pp.setString(2, Integer.toString(urlid));
			pp.setString(3, Integer.toString(priority));
			pp.setString(4, Integer.toString(index));
			int execRes = pp.executeUpdate();
			con.close();
			if (execRes == 1)
				return true;

		} catch (SQLException e) {
			e.printStackTrace();
		}

		return false;

	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static boolean insert(HashMap<String, List<Word>> hm) {

		try {
			Connection con = DriverManager.getConnection(host, uName, uPass);
			Iterator it = hm.entrySet().iterator();
			while (it.hasNext()) {
				Entry pairs = (Entry) it.next();
				java.sql.PreparedStatement pp = con
						.prepareStatement("INSERT INTO keyword_url VALUES (default,?,?,?,?)");
				int keywordid = getKeywordId((String) pairs.getKey());

				for (int i = 0; i < ((ArrayList<Word>) pairs.getValue()).size(); i++) {

					pp.setString(1, Integer.toString(keywordid));

					int urlid = getURLId((((ArrayList<Word>) pairs.getValue())
							.get(i)).getUrl());
					pp.setString(2, Integer.toString(urlid));

					int priority = (((ArrayList<Word>) pairs.getValue()).get(i))
							.getPriority().ordinal();
					pp.setString(3, Integer.toString(priority));

					int pos = (((ArrayList<Word>) pairs.getValue()).get(i))
							.getPosition();
					pp.setString(4, Integer.toString(pos));

					try {
						pp.executeUpdate();
					} catch (Exception e) {

					}
				}
			}
			con.close();
			return true;

		} catch (SQLException e) {
			e.printStackTrace();
		}

		return false;

	}

	public static boolean deleteByURL(String URL) {
		try {
			Connection con = DriverManager.getConnection(host, uName, uPass);
			int urlid = getURLId(URL);
			if (urlid == -1) {
				con.close();
				System.out.println("This URL Isn't Indexed");
				return false;
			}
			java.sql.PreparedStatement pp = con
					.prepareStatement("DELETE FROM keyword_url where urlid='"
							+ urlid + "'");
			pp.executeUpdate();
			con.close();
			return true;
		} catch (Exception e) {

		}
		return false;
	}

	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static ArrayList<LinkIndex> getLinkIndexbyKeyword(String keyword) {

		try {
			Connection con = DriverManager.getConnection(host, uName, uPass);
			int keywordid = getKeywordId(keyword);
			ResultSet result = con.createStatement().executeQuery(
					"SELECT link.url,keyword_url.`index` FROM keyword_url,link where keywordid='"
							+ keywordid + "' AND link.urlid=keyword_url.urlid");
			ArrayList<LinkIndex> arr = new ArrayList<LinkIndex>();
			HashMap<String, ArrayList<Integer>> linkwIndex = new HashMap<String, ArrayList<Integer>>();
			while (result.next()) {
				ArrayList<Integer> arrIndex = linkwIndex.get(result
						.getString("url"));
				if (arrIndex == null)
					arrIndex = new ArrayList<Integer>();
				arrIndex.add(Integer.parseInt(result.getString("index")));
				linkwIndex.put(result.getString("url"), arrIndex);
			}
			Iterator it = linkwIndex.entrySet().iterator();
			while (it.hasNext()) {
				Entry pairs = (Entry) it.next();
				LinkIndex li = new LinkIndex();
				li.setIndex((ArrayList<Integer>) pairs.getValue());
				li.setURL((String) pairs.getKey());
				arr.add(li);
			}
			con.close();
			return arr;

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}

	// Returns ArrayList containing URL that have 1 or more of these keywords
	// (UNION)
	public static ArrayList<String> getURLbyKeywordsOR(
			ArrayList<String> keywords) {

		try {
			Connection con = DriverManager.getConnection(host, uName, uPass);

			if (keywords.size() != 0) {
				int keywordid = getKeywordId(keywords.get(0));
				String query = "SELECT DISTINCT link.url FROM keyword_url,link WHERE ( keyword_url.keywordid='"
						+ keywordid + "' ";
				for (int i = 1; i < keywords.size(); i++) {
					keywordid = getKeywordId(keywords.get(i));
					query += "OR keyword_url.keywordid= '" + keywordid + "' ";
				}
				query += ") AND link.urlid=keyword_url.urlid";
				System.out.println(query);

				ResultSet result = con.createStatement().executeQuery(query);
				ArrayList<String> arr = new ArrayList<String>();
				while (result.next()) {
					arr.add(result.getString("url"));
				}
				con.close();
				return arr;
			}

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;

	}

	public static ArrayList<String> getURLbyKeywordsAND(
			ArrayList<String> keywords) {

		try {
			Connection con = DriverManager.getConnection(host, uName, uPass);

			if (keywords.size() != 0) {
				int keywordid = getKeywordId(keywords.get(0));
				String query2 = "SELECT DISTINCT t1.url FROM keyword_url,link t1 WHERE EXISTS (SELECT * from keyword_url,link where keywordid ='"
						+ keywordid
						+ "' and keyword_url.urlid= link.urlid and t1.urlid=link.urlid) ";
				for (int i = 1; i < keywords.size(); i++) {
					keywordid = getKeywordId(keywords.get(i));
					query2 += "AND EXISTS (SELECT * FROM keyword_url,link WHERE keywordid ='"
							+ keywordid
							+ "' and keyword_url.urlid= link.urlid and t1.urlid=link.urlid) ";
				}
				System.out.println(query2);
				ResultSet result = con.createStatement().executeQuery(query2);
				ArrayList<String> arr = new ArrayList<String>();
				while (result.next()) {
					arr.add(result.getString("url"));
				}
				con.close();
				return arr;
			}

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;

	}
	


	// check if this URL exists in link table if so it compares hashCodes to
	// output CHANGED or NOCHANGE
	// else it is a new record and inserts it into this table returning NEW
	public static Status checkHashCode(String url, int hashCode) {

		try {
			Connection con = DriverManager.getConnection(host, uName, uPass);
			String query = "SELECT hashcode FROM link WHERE url='" + url + "'";
			ResultSet result = con.createStatement().executeQuery(query);
			String dbHashCode = null;
			if (result.next())
				dbHashCode = result.getString("hashcode");
			if (dbHashCode == null) {
				query = "INSERT INTO link values (default,?,?)";
				PreparedStatement pp = con.prepareStatement(query);
				pp.setString(1, url);
				pp.setString(2, Integer.toString(hashCode));
				pp.execute();
				con.close();
				System.out.println("NEW");
				return Status.NEW;
			} else {
				if (Integer.parseInt(dbHashCode) != hashCode) {
					query = "UPDATE link SET hashcode ='" + hashCode
							+ "' where url='" + url + "'";
					PreparedStatement pp = con.prepareStatement(query);
					pp.execute();
					con.close();
					System.out.println("CHANGED");
					return Status.CHANGED;
				}
			}

		} catch (Exception e) {

		}

		System.out.println("NOCHANGE");
		return Status.NOCHANGE;

	}

	public enum Status {
		NEW, CHANGED, NOCHANGE
	}

}
