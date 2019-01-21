package crawler;

import org.jsoup.nodes.*;
import org.jsoup.select.*;
import org.jsoup.*;
import java.io.*;

public class jsoupcrawler{
	public void crawl() throws IOException{
		String URL = "https://research.cs.wisc.edu/dbworld/browse.html";
		String Path = "./webinfo/";
		Document doc = Jsoup.connect(URL).timeout(500000).get();
		Elements links = doc.select("TBODY");
		for(Element l:links) {
			Element usrl_in_item = l.select("A").first();
				System.out.println(usrl_in_item.attr("HREF"));
			File subjectf = new File(Path + usrl_in_item.text().replaceAll("/", "-"));
			PrintStream subjectps = new PrintStream(new FileOutputStream(subjectf));
			
			String contenturl = usrl_in_item.attr("HREF").replace("http://www", "https://research");
			
			Elements TDS = l.select("TD");
			int i = 0;
			for(Element TD:TDS) {
				i++;
				switch(i) {
					case 1:
						subjectps.println("Sent Date: " + TD.text());
						break;
					case 2:
						subjectps.println("Message Type: " + TD.text());
						break;
					case 3:
						subjectps.println("From: " + TD.text());
						break;
					case 4:
						subjectps.println("Subject: " + TD.text());
						subjectps.println("SubjectURL: " + l.select("A").get(0).attr("HREF"));
						break;
					case 5:
						subjectps.println("Deadline: " + TD.text());
						break;
					case 6:
						try {
							subjectps.println("WebPageURL: " + l.select("A").get(1).attr("HREF"));
						}
						catch(IndexOutOfBoundsException e){
							subjectps.println("WebPageURL: ");
						}
						break;
				}
			}
			subjectps.println("Content: ");
			try {
				Document Itemcontent = Jsoup.connect(contenturl).timeout(500000).get();
				Element content = Itemcontent.selectFirst("BODY");
				subjectps.println(content.text());
			}catch(java.net.SocketTimeoutException e) {
				
			}
			subjectps.close();
		}
	}
	public static void main(String[] args) {
		jsoupcrawler c = new jsoupcrawler();
		try{
			c.crawl();
		}
		catch(Exception e) {
			e.printStackTrace();
		}
		System.out.println("Crawl finished.");
	}
}
