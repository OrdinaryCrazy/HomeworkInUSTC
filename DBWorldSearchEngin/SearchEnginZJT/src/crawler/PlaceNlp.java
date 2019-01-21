package crawler;
import java.util.Properties;

import edu.stanford.nlp.pipeline.*;
public class PlaceNlp {
	public String getPlace(String text,Properties properties,StanfordCoreNLP pipeline) {
		String Place = "";
		CoreDocument document = new CoreDocument(text);
		pipeline.annotate(document);
		int count = 0;
		for(CoreEntityMention eMention : document.entityMentions()) {
			if (count < 30) {
				if(	eMention.entityType().equals("COUNTRY") ||
					eMention.entityType().equals("STATE_OR_PROVINCE") ||
					eMention.entityType().equals("CITY")
				) {	Place = Place + " " + eMention.text();	}
				count++;
			}
		}
		//System.out.println(text);
		System.out.println(Place);
		return Place;
	}
}
