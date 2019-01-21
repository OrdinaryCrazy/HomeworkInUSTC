package crawler;

import java.io.File;
import java.util.ArrayList;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;

public class luceneSearch {
	public ArrayList<luceneSearchResult> search(String Field, String Que)throws Exception {
		String IndexDir = "/home/crazy/eclipse-J2EE-workspace/SearchEnginZJT/index/";
		Directory dir = FSDirectory.open(new File(IndexDir));
		IndexReader ir = DirectoryReader.open(dir);
		IndexSearcher is = new IndexSearcher(ir);
		Analyzer anal = new StandardAnalyzer(Version.LUCENE_44);
		QueryParser qp = new QueryParser(Version.LUCENE_44, Field, anal);
		Query q = qp.parse(Que);
		//DuplicateFilter df = new DuplicateFilter("subject");
		
		long StartTime = System.currentTimeMillis();
		//TopDocs docs = is.sea(q, df, 50);
		TopDocs docs = is.search(q, 500);
		long EndTime = System.currentTimeMillis();
		System.out.println("用时： " + (EndTime - StartTime) + "ms");;
		System.out.println("查询到：" + docs.totalHits + "条记录");;
		
		ArrayList<luceneSearchResult> results = new ArrayList<luceneSearchResult>();
		for(ScoreDoc sd:docs.scoreDocs) {
			Document resultdoc = is.doc(sd.doc);
			luceneSearchResult result = new luceneSearchResult(resultdoc);
			boolean nodup = true;
			for(luceneSearchResult pre:results) {
				if(pre.subject.equals(result.subject)) {
					nodup = false;
				}
			}
			if(nodup) {
				results.add(result);
			}
		}
		ir.close();
		for(luceneSearchResult r:results) {
			System.out.println(r.subject);
		}
		return results;
	}
	public static void main(String[] args) {
		String Que = "International Conference on Internet Technologies & Society";
		try {
			luceneSearch s = new luceneSearch();
			s.search("subject",Que);
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}
}
