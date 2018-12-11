/**
 * @Auther:ZhangJingtun(OrdinaryCrazy@github)
 * @FileName:Huffman.java
 * @Usage:Compress a lowercase english file use huffmancode
 */
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
public class Huffman{
    private class CharNum{
        int count;
        char name;
        char[] hcode;
    }
    private class Twomin{
        int min1, min2 ;
        int min1w,min2w;
    }
    private CharNum CharCount[];
    private class HuffmanNode{
        int Weight;
        int Parent, LeftChild, RightChild;
    }
    private HuffmanNode[] HuffmanTree;
    /******************************************************************/
    public Huffman(String CompressFile) throws IOException{
        File InputFile = new File(CompressFile);
        char[] CharBuffer = new char[(int)InputFile.length()];
        CharCount = new CharNum[26];
        for(int i = 0;i < 26;i++){
            CharCount[i] = new CharNum();
            CharCount[i].name = (char)('a' + i);
        }
        FileReader In = new FileReader(InputFile);
        In.read(CharBuffer);
        In.close();
        for(char c : CharBuffer){
            CharCount[c - 'a'].count++;
        }
    }
    public Twomin Select(int range){
        Twomin Result = new Twomin();
        Result.min1w = Integer.MAX_VALUE;
        for(int i = 1;i <= range;i++){
            if(HuffmanTree[i].Parent == 0){
                if(HuffmanTree[i].Weight < Result.min1w){
                    Result.min2w = Result.min1w;
                    Result.min2  = Result.min1;
                    Result.min1  = i;
                    Result.min1w = HuffmanTree[i].Weight;
                }
                else{
                    if(HuffmanTree[i].Weight < Result.min2w){
                        Result.min2  = i;
                        Result.min2w = HuffmanTree[i].Weight;
                    }
                }
            }
        }
        return Result;
    }
    public void BuildHuffmanTree(){
        HuffmanTree = new HuffmanNode[2 * 26 - 1 + 1];
        // initialization of huffman tree not must for init of 0
        for(int i = 1;i <= 26;i++){
            HuffmanTree[i] = new HuffmanNode();
            HuffmanTree[i].Weight = CharCount[i - 1].count;
            HuffmanTree[i].LeftChild = 
            HuffmanTree[i].RightChild = 
            HuffmanTree[i].Parent = 0;
        }
        for(int i = 27;i < 52;i++){
            HuffmanTree[i] = new HuffmanNode();
            HuffmanTree[i].LeftChild = 
            HuffmanTree[i].Weight = 
            HuffmanTree[i].RightChild = 
            HuffmanTree[i].Parent = 0;
        }
        //build huffman tree
        for(int i = 27;i < 52;i++){
            Twomin Choise = this.Select(i - 1);
            HuffmanTree[i].LeftChild = Choise.min1;
            HuffmanTree[i].RightChild = Choise.min2;
            HuffmanTree[Choise.min1].Parent = i;
            HuffmanTree[Choise.min2].Parent = i;
            HuffmanTree[i].Weight =   HuffmanTree[Choise.min1].Weight 
                                    + HuffmanTree[Choise.min2].Weight;
        }
        // gain huffman code for each character
        for(int i = 1;i <= 26;i++){
            StringBuffer TempHuffCode = new StringBuffer();
            for(    int c = i, f = HuffmanTree[i].Parent;
                    f != 0;
                    c = f,f = HuffmanTree[f].Parent){

                if(HuffmanTree[f].LeftChild == c){
                    TempHuffCode.insert(0, "0");
                }
                else{
                    TempHuffCode.insert(0, "1");
                }
            }
            CharCount[i - 1].hcode = TempHuffCode.toString().toCharArray();
        }
    }
    public void Compress(String CompressFile ,String CompressedFile) throws IOException{
        File InputFile = new File(CompressFile);
        //File OutputFile = new File(CompressedFile);
        FileReader In = new FileReader(InputFile);
        //FileWriter Out = new FileWriter(OutputFile);
        DataOutputStream Out = new DataOutputStream(new FileOutputStream(CompressedFile));
        // write character frequence to the head of compressed file for decompress
        for(int i = 0;i < 26;i++){
            Out.writeInt(CharCount[i].count);
        }
        // gain compress result as 01 string
        char[] CharBuffer = new char[(int)InputFile.length()];
        StringBuffer CompressResult = new StringBuffer();
        In.read(CharBuffer);
        In.close();
        for(char c: CharBuffer){
            CompressResult.append(CharCount[c - 'a'].hcode);
        }
        // trans char string into byte array
        int LengthOfByteArray = CompressResult.length() / 8;
        if(CompressResult.length() / 8 != 0){
            LengthOfByteArray++;
        }
        byte[] target = new byte[LengthOfByteArray];
        for(int i = 0;i < LengthOfByteArray;i++){
            target[i] = (byte)0;
        }
        for(int i = 0;i < CompressResult.length();i++){
            if(CompressResult.charAt(i) == '1'){
                if(i % 8 == 0){target[i/8] = (byte)((int)target[i/8]|0x80);}
                if(i % 8 == 1){target[i/8] = (byte)((int)target[i/8]|0x40);}
                if(i % 8 == 2){target[i/8] = (byte)((int)target[i/8]|0x20);}
                if(i % 8 == 3){target[i/8] = (byte)((int)target[i/8]|0x10);}
                if(i % 8 == 4){target[i/8] = (byte)((int)target[i/8]|0x8);}
                if(i % 8 == 5){target[i/8] = (byte)((int)target[i/8]|0x4);}
                if(i % 8 == 6){target[i/8] = (byte)((int)target[i/8]|0x2);}
                if(i % 8 == 7){target[i/8] = (byte)((int)target[i/8]|0x1);}
            }
        }
        Out.write(target);
        Out.close();
    }
    public void DeCompress(String DeCompressFile ,String DeCompressedFile) throws IOException{

    }
    public static void main(String args[]) throws IOException{
        if(args.length != 3){
            System.out.println("Wrong parameter numbers, please use pattern\n" 
            + "\"java Huffman compress compress_file_name compressed_file_name\"\n"
            + "or\n" 
            + "\"java Huffman decompress decompress_file_name decompressed_file_name\"\n");
            return;
        }
        if(args[0].equals("compress")){
            Huffman H = new Huffman(args[1]);
            H.BuildHuffmanTree();
            H.Compress(args[1],args[2]);
            for(CharNum i : H.CharCount){
                String tmp = new String(i.hcode);
                System.out.println(   i.name + " : "
                                    + i.count 
                                    + "\tHuffmanCode: " + tmp);
            }
        }
        else{
            //Decompress part: waiting....
        }
    }
}