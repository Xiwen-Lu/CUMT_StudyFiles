package compiler;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.Reader;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;


import java.awt.*;

public class huibian extends JFrame {

	private static final long serialVersionUID = 8766059377195109228L;
	private static String title;
	private static String fileName;
	
	private static TextArea text;
	
	public huibian() {
		init();
		
	}
    public static boolean isNumericzidai(String str) {
        Pattern pattern = Pattern.compile("-?[0-9]+\\.?[0-9]*");
        Matcher isNum = pattern.matcher(str);
        if (!isNum.matches()) {
            return false;
        }
        return true;
    }

	
//	寄存器分配，用于存储变量与寄存器对应编号
//	寄存器分配还需好好设计，暂且使用数值自增
    private Map<String,String> registerVariateMap = new HashMap<String, String>();
    private int registerNum=65;
	public String registerAllocation(String vatiate) {
		if(isNumericzidai(vatiate)) {
			return vatiate;
		}
		if(registerVariateMap.get(vatiate)!=null) {
			
		} else{
			StringBuffer sbu = new StringBuffer();
	        sbu.append((char)registerNum++);
	        sbu.append('X');
	        System.out.print("vatiate: "+vatiate);
	        System.out.println(", "+sbu.toString());
			registerVariateMap.put(vatiate, sbu.toString());
		}
		return registerVariateMap.get(vatiate);
	}
	
	public huibian(String title,String fileName){
		this.title=title;
		this.fileName=fileName;
		init();
		this.setTitle(title);
		try {
			String str[] =readFile(fileName).split("\n");
			for(int i = 2; i < str.length; i++)
			{
				//System.out.println(str[i]);
				String temp[] = str[i].split(",");
				String temp1="";
				//System.out.println(temp.length);
				//for(int j = 0; j < temp.length; j++) System.out.println(temp[j]);
				if(temp[0].charAt(temp[0].length() -1) == '='){
					//System.out.println(i);
					temp1 = temp[0].substring(0,temp[0].length() - 2) + " MOV " + temp[3].substring(0,temp[3].length() - 1) + "," + temp[1] + "\n";
					//System.out.println(temp1);
				}
				else if(temp[0].charAt(temp[0].length() -1) == '+' && temp[0].charAt(temp[0].length() -2) == '+'){
					temp1 = temp[0].substring(0,temp[0].length() - 3) + " INC "  + temp[1] + "\n";
					//System.out.println(temp1);
				}
				else if(temp[0].charAt(temp[0].length() -1) == '+'){
					temp1 = temp[0].substring(0,temp[0].length() - 2) + " ADD " + temp[3].substring(0,temp[3].length() - 1) + "," + temp[1] + "\n";
					//System.out.println(temp1);
				}
				else if(temp[0].charAt(temp[0].length() -1) == '-'){
					temp1 = temp[0].substring(0,temp[0].length() - 2) + " SUB " + temp[3].substring(0,temp[3].length() - 1) + "," + temp[1] + "\n";
					//System.out.println(temp1);
				}
				else if(temp[0].charAt(temp[0].length() -1) == '*'){
					temp1 = temp[0].substring(0,temp[0].length() - 2) + " MUL " + temp[3].substring(0,temp[3].length() - 1) + "," + temp[1] + "\n";
					//System.out.println(temp1);
				}
				else if(temp[0].charAt(temp[0].length() -1) == '/'){
					temp1 = temp[0].substring(0,temp[0].length() - 2) + " DIV "  + temp[3].substring(0,temp[3].length() - 1) + "," + temp[1] + "\n";
					//System.out.println(temp1);
				}
				else if(temp[0].charAt(temp[0].length() -1) == 'J' && temp[0].charAt(temp[0].length() -2) == 'R'){
					temp1 = temp[0].substring(0,temp[0].length() - 3) + " JMP " + temp[3].substring(0,temp[3].length() - 1)  + "\n";
					//System.out.println(temp1);
				}
				else if(temp[0].charAt(temp[0].length() -1) == 'J' && temp[0].charAt(temp[0].length() -2) == 'F'){
					temp1 = temp[0].substring(0,temp[0].length() - 3) + " JZ " + temp[3].substring(0,temp[3].length() - 1)  + "\n";
					//System.out.println(temp1);
				}
				else if(temp[0].charAt(temp[0].length() -1) == '>'){
					temp1 = temp[0].substring(0,temp[0].length() - 2) + " JG " + temp[3].substring(0,temp[3].length() - 1)  + "\n";
					//System.out.println(temp1);
				}
				else if(temp[0].charAt(temp[0].length() -1) == '<'){
					temp1 = temp[0].substring(0,temp[0].length() - 2) + " JL " + temp[3].substring(0,temp[3].length() - 1)  + "\n";
					//System.out.println(temp1);
				}
				//text.append(temp1);
				
			}
			File file=new File(outputHuiBian());
			FileReader fos=new FileReader(file);  
			BufferedReader bos=new BufferedReader(fos); 
			String align;
			while((align=bos.readLine())!=null)text.append(align+"\n");
			fos.close();
			bos.close();
			
		} catch (IOException e) {
			
			e.printStackTrace();
		}	
	}
	
	public String outputHuiBian() throws IOException{
		
		File file=new File("./output/");
		if(!file.exists()){
			file.mkdirs();
			file.createNewFile();//如果这个文件不存在就创建它
		}
		String path=file.getAbsolutePath();
		FileOutputStream fos=new FileOutputStream(path+"/HuiBian.txt");  
		BufferedOutputStream bos=new BufferedOutputStream(fos); 
		OutputStreamWriter osw1=new OutputStreamWriter(bos,"utf-8");
		PrintWriter pw1=new PrintWriter(osw1);
		pw1.println("ASSUME CS:codesg");
		pw1.println("codesg segment");
		
//		FourElement temp;
//		for(int i=0;i<fourElemList.size();i++){
//			temp=fourElemList.get(i);
//			pw1.println(temp.id+"("+temp.op+","+temp.arg1+","+temp.arg2+","+temp.result+")");
//		}
		
		try {
			String str[] =readFile(fileName).split("\n");
			String temp1 = null;
			for(int i = 2; i < str.length; i++)
			{
				String temp[] = str[i].split(",");
				if(temp[0].charAt(temp[0].length() -1) == '='){
					String src = temp[3].substring(0,temp[3].length() - 1);
					temp1 = "MOV " + registerAllocation(src) + "," + registerAllocation(temp[1]) + "\n";
				}
				else if(temp[0].charAt(temp[0].length() -1) == '+' && temp[0].charAt(temp[0].length() -2) == '+'){
					temp1 = "INC "  + registerAllocation(temp[1]) + "\n";
				}
				else if(temp[0].charAt(temp[0].length() -1) == '+'){
					String dst = registerAllocation(temp[1]);
					String src = registerAllocation(temp[2]);				
					String dsf = registerAllocation(temp[3].substring(0,temp[3].length() - 1));
					temp1 = "ADD " + dst + "," + src + "\n";
					temp1+= "\t"+"MOV " + dsf + "," + dst + "\n";
				}
				else if(temp[0].charAt(temp[0].length() -1) == '-'){
					temp1 = "SUB " + temp[3].substring(0,temp[3].length() - 1) + "," + temp[1] + "\n";
				}
				else if(temp[0].charAt(temp[0].length() -1) == '*'){
					temp1 = "MUL " + temp[3].substring(0,temp[3].length() - 1) + "," + temp[1] + "\n";
				}
				else if(temp[0].charAt(temp[0].length() -1) == '/'){
					temp1 = "DIV "  + temp[3].substring(0,temp[3].length() - 1) + "," + temp[1] + "\n";
				}
				else if(temp[0].charAt(temp[0].length() -1) == 'J' && temp[0].charAt(temp[0].length() -2) == 'R'){
					temp1 = "JMP " + temp[3].substring(0,temp[3].length() - 1)  + "\n";
				}
				else if(temp[0].charAt(temp[0].length() -1) == 'J' && temp[0].charAt(temp[0].length() -2) == 'F'){
					temp1 = "JZ " + temp[3].substring(0,temp[3].length() - 1)  + "\n";
				}
				else if(temp[0].charAt(temp[0].length() -1) == '>'){
					temp1 = "JG " + temp[3].substring(0,temp[3].length() - 1)  + "\n";
				}
				else if(temp[0].charAt(temp[0].length() -1) == '<'){
					temp1 = "JL " + temp[3].substring(0,temp[3].length() - 1)  + "\n";
				}
				pw1.print("\t"+temp1);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		pw1.println("codesg ends");
		pw1.println("end");
		pw1.close();
		
		return path+"/HuiBian.txt";
	}

	private void init() {
		Toolkit toolkit = Toolkit.getDefaultToolkit();
		Dimension screen = toolkit.getScreenSize();
		setSize(500, 400);
		super.setLocation(screen.width / 2 - this.getWidth() / 2, screen.height
				/ 2 - this.getHeight() / 2);
		setContentPane(createContentPane());
	}

	private Container createContentPane() {
		JPanel pane = new JPanel(new BorderLayout());
		text = new TextArea();
		//msg.setBackground(Color.green);
		text.setForeground(Color.BLUE);
		text.setFont(new Font("Serif",0,20));
		pane.add(BorderLayout.CENTER, text);
		return pane;
	}
	private String readFile(String filename) 
	throws IOException{
		StringBuilder sbr = new StringBuilder();
		String str;
			FileInputStream fis = new FileInputStream(filename);
			BufferedInputStream bis = new BufferedInputStream(fis);
			InputStreamReader isr = new InputStreamReader(bis, "UTF-8");
			BufferedReader in=new BufferedReader(isr);
			while((str=in.readLine())!=null){
				sbr.append(str).append('\n');
			}
			in.close();
			//text.setText(sbr.toString());
		return sbr.toString();
	}
	public static String getTitl() {
		return title;
	}

	public static void setTitl(String title) {
		huibian.title = title;
	}

	public static String getFileName() {
		return fileName;
	}

	public static void setFileName(String fileName) {
		huibian.fileName = fileName;
	}

	public static TextArea getText() {
		return text;
	}

	public static void setText(TextArea jText) {
		huibian.text = jText;
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		huibian inf=new huibian("测试","test.txt");
inf.setVisible(true);
	}

}
