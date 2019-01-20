/**
 * @Auther:PB16111485 张劲暾
 * @Platform:Ubuntu17.10
 */
import java.util.Scanner;

public class WordPuzzle{
    public WordPuzzle(){
        this.SetWordSet();
    }
    public String[] WordSet = new String[15];
    public void SetWordSet(){
        this.WordSet[0]  = new String("cautious");
        this.WordSet[1]  = new String("successive");
        this.WordSet[2]  = new String("marginal");
        this.WordSet[3]  = new String("clerk");
        this.WordSet[4]  = new String("rein");
        this.WordSet[5]  = new String("ozone");
        this.WordSet[6]  = new String("decay");
        this.WordSet[7]  = new String("cautious");
        this.WordSet[8]  = new String("neglect");
        this.WordSet[9]  = new String("heap");
        this.WordSet[10] = new String("application");
        this.WordSet[11] = new String("modest");
        this.WordSet[12] = new String("orchestra");
        this.WordSet[13] = new String("convention");
        this.WordSet[14] = new String("association");
    }
    public static void main(String[] args){
        WordPuzzle WP = new WordPuzzle();
        Scanner InputGet = new Scanner(System.in);     
        int ChoiseWord = (int)(Math.random() * 15);

        System.out.println("This is a word puzzle:");
        int LengthOfChooseWord = WP.WordSet[ChoiseWord].length();
        int[] FindOrNot = new int[LengthOfChooseWord];

        for (int i = 0;i < LengthOfChooseWord;i++) {
            System.out.print("_ ");
        }
        System.out.print("\n");
        boolean Flag = true;

        while(Flag){
            String Buffer = InputGet.next();
            char Get = Buffer.charAt(0);
            if(Get == '0'){
                while(true){
                    int RandomPosition = (int)(Math.random() * LengthOfChooseWord);
                    if(FindOrNot[RandomPosition] == 0){
                        FindOrNot[RandomPosition] = 1;
                        break;
                    }
                }
            }
            else{
                for(int i = 0;i < LengthOfChooseWord;i++){
                    if(WP.WordSet[ChoiseWord].charAt(i) == Get && FindOrNot[i] == 0){
                        FindOrNot[i] = 1;
                        break;
                    }
                }
            }
            for(int i = 0;i < LengthOfChooseWord;i++){
                if(FindOrNot[i] == 1){
                    System.out.print(WP.WordSet[ChoiseWord].charAt(i));
                    System.out.print(' ');
                }
                else{
                    System.out.print("_ ");
                }
            }
            System.out.print("\n");

            int tmp = 0;
            for(int i = 0;i < LengthOfChooseWord;i++){
                tmp += FindOrNot[i];
            }
            if(tmp == LengthOfChooseWord){
                Flag = false;
            }
        }
        InputGet.close();
    }
}
