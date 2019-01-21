package crawler;

import org.apache.lucene.document.Document;

public class luceneSearchResult {
	public String sentdate;
	public String messagetype;
	public String from;
	public String subject;
	public String subjecturl;
	public String ddl;
	public String webpageurl;
	public String content;
	public luceneSearchResult(Document result) {
		this.sentdate 		= "" + result.get("sentdate");
		this.messagetype 	= "" + result.get("messagetype");
		this.from 			= "" + result.get("from");
		this.subject 		= "" + result.get("subject");
		this.subjecturl 	= "" + result.get("subjecturl");
		this.ddl 			= "" + result.get("ddl");
		this.webpageurl 	= "" + result.get("webpageurl");
		this.content 		= "" + result.get("content");
	}
}
