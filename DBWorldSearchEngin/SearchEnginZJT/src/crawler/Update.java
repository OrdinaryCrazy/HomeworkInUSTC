package crawler;

import java.util.TimerTask;
import java.io.File;

public class Update extends TimerTask {

	@Override
	public void run() {
		// TODO Auto-generated method stub
		System.out.println("Daily Updating,Please wait for some minutes, you can go to take a coffee.");
		File f=new File("/home/crazy/eclipse-J2EE-workspace/SearchEnginZJT/webinfo/");
        for (File f1: f.listFiles()){
            f1.delete();
        }
        jsoupcrawler.main(null);
        f=new File("download\\index");
        for (File f1: f.listFiles()){
            f1.delete();
        }
        luceneindex.main(null);
		System.out.println("Updating Finished");
	}

}
