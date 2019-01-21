package crawler;

import java.util.Date;
import java.util.Timer;
import java.util.Calendar;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;

public class WebinfoUpdate implements ServletContextListener {
	private static final long PERIOD_DAY = 24 * 60 * 60 * 1000;
	@Override
	public void contextDestroyed(ServletContextEvent sce) {
		// TODO Auto-generated method stub

	}

	@Override
	public void contextInitialized(ServletContextEvent sce) {
		// TODO Auto-generated method stub
		Calendar calendar = Calendar.getInstance();
		/************** Update at 3:00 everyday *********************/
		calendar.set(Calendar.HOUR_OF_DAY, 3);
		calendar.set(Calendar.MINUTE, 0);
		calendar.set(Calendar.SECOND, 0);
		Date date = calendar.getTime();	//第一次执行定时任务的时间
		
		//如果第一次执行定时任务的时间早于当前的时间
        //此时要在第一次执行定时任务的时间上加一天，以便此任务在下个时间点执行。如果不加一天，任务会立即执行。循环执行的周期则以当前时间为准
        if (date.before(new Date())) {
            date = this.addDay(date, 1); //后延一天
            System.out.println(date);
        }
        
		Timer timer = new Timer();
		Update task = new Update();
		//安排指定的任务在指定的时间开始进行重复的固定延迟执行。
		timer.schedule(task, date, PERIOD_DAY);
	}
	public Date addDay(Date date, int num) {
        Calendar startDT = Calendar.getInstance();
        startDT.setTime(date);
        startDT.add(Calendar.DAY_OF_MONTH, num);
        return startDT.getTime();
    }  
}
