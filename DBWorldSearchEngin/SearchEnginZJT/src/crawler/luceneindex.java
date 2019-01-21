package crawler;
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Properties;
import java.io.File;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.TextField;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;

import edu.stanford.nlp.pipeline.StanfordCoreNLP;

public class luceneindex {
	private IndexWriter writer;
	public luceneindex(String IndexDir)throws Exception {
		Directory dir = FSDirectory.open(new File(IndexDir));
		Analyzer analy = new StandardAnalyzer(Version.LUCENE_44);	//创建标准分词器
		IndexWriterConfig config = new IndexWriterConfig(Version.LUCENE_44, analy);	//将标准分词器加入到写索引配置中
		writer = new IndexWriter(dir, config);
	}
	public void close() throws Exception{
		writer.close();
	}
	public void indexAll(String DataDir) throws Exception{ //Index All Files Under the Path
		File[] DataFiles = new File(DataDir).listFiles();
		for(File f:DataFiles) {
			indexFile(f);
		}
	}
	public void indexFile(File DataFile)throws Exception {
		getDocument(DataFile);
	}
	public Document getDocument(File f)throws Exception {
		Document doc = new Document();
		BufferedReader br = new BufferedReader(new FileReader(f));
		String s;
		if((s = br.readLine()) != null) {
			doc.add(new TextField("sentdate", s.replace("Sent Date:", ""), Field.Store.YES));
		}else {doc.add(new TextField("sentdate", " ", Field.Store.YES));}
		if((s = br.readLine()) != null) {
			doc.add(new TextField("messagetype", s.replace("Message Type:", ""), Field.Store.YES));
		}else {doc.add(new TextField("messagetype", " ", Field.Store.YES));}
		if((s = br.readLine()) != null) {
			doc.add(new TextField("from", s.replace("From:", ""), Field.Store.YES));
		}else {doc.add(new TextField("from", " ", Field.Store.YES));}
		if((s = br.readLine()) != null) {
			doc.add(new TextField("subject", s.replace("Subject:", ""), Field.Store.YES));
		}else {doc.add(new TextField("subject", " ", Field.Store.YES));}
		if((s = br.readLine()) != null) {
			doc.add(new TextField("subjecturl", s.replace("SubjectURL:", ""), Field.Store.YES));
		}else {doc.add(new TextField("subjecturl", " ", Field.Store.YES));}
		if((s = br.readLine()) != null) {
			doc.add(new TextField("ddl", s.replace("Deadline:", ""), Field.Store.YES));
		}else {doc.add(new TextField("ddl", " ", Field.Store.YES));}
		if((s = br.readLine()) != null) {
			doc.add(new TextField("webpageurl", s.replace("WebPageURL:", ""), Field.Store.YES));
		}else {doc.add(new TextField("webpageurl", " ", Field.Store.YES));}
		
		s = br.readLine();
		s = "";
		String tmp;
		while ((tmp = br.readLine()) != null) {
			s = s + " " + tmp;
		}
		doc.add(new TextField("content", s, Field.Store.YES));
		
		PlaceNlp placeNlp = new PlaceNlp();
		Properties properties = new Properties();
		properties.setProperty("annotators", "tokenize,ssplit,pos,lemma,ner");
		StanfordCoreNLP pipeline = new StanfordCoreNLP(properties);
		
		String place = placeNlp.getPlace(s,properties,pipeline);
		doc.add(new TextField("place", place, Field.Store.YES));
		
		br.close();
		//System.out.println(doc);
		writer.addDocument(doc);
		return doc;
	}
	public static void main(String[] args) {
		String IndexDir = "./index/";	//Path to save IndexFile
		String DataDir  = "./webinfo/";	//Path of data
		luceneindex Indexer = null;
		try {
			Indexer = new luceneindex(IndexDir);
			Indexer.indexAll(DataDir);
		}catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}finally {
			try {
				Indexer.close();
			} catch (Exception e2) {
				// TODO: handle exception
				e2.printStackTrace();
			}
		}
		System.out.println("Index Building Finished!");
	}
}
