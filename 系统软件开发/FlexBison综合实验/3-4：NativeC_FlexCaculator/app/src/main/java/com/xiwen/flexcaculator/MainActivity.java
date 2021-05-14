package com.xiwen.flexcaculator;

import androidx.appcompat.app.AppCompatActivity;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.AttributeSet;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.GridLayout;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    /**定义所有使用的按钮，最好与前端id相同,使用findviewbyme! 别一个一个敲*/
    private GridLayout gridlayout;
    private EditText edit;
    private TextView view;
    private Button add;
    private Button substact;
    private Button multiply;
    private Button divide;
    private Button seven;
    private Button eight;
    private Button nine;
    private Button left;
    private Button four;
    private Button five;
    private Button six;
    private Button right;
    private Button three;
    private Button two;
    private Button one;
    private Button Clean;
    private Button dot;
    private Button zero;
    private Button equal;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        gridlayout = (GridLayout) findViewById(R.id.gridlayout);
        edit = (EditText) findViewById(R.id.edit);
        view = (TextView) findViewById(R.id.view);
        add = (Button) findViewById(R.id.add);
        substact = (Button) findViewById(R.id.substact);
        multiply = (Button) findViewById(R.id.multiply);
        divide = (Button) findViewById(R.id.divide);
        seven = (Button) findViewById(R.id.seven);
        eight = (Button) findViewById(R.id.eight);
        nine = (Button) findViewById(R.id.nine);
        left = (Button) findViewById(R.id.left);
        four = (Button) findViewById(R.id.four);
        five = (Button) findViewById(R.id.five);
        six = (Button) findViewById(R.id.six);
        right = (Button) findViewById(R.id.right);
        three = (Button) findViewById(R.id.three);
        two = (Button) findViewById(R.id.two);
        one = (Button) findViewById(R.id.one);
        Clean = (Button) findViewById(R.id.Clean);
        dot = (Button) findViewById(R.id.dot);
        zero = (Button) findViewById(R.id.zero);
        equal = (Button) findViewById(R.id.equal);
        //建立联系


        edit.setOnClickListener(this);
        view.setOnClickListener(this);
        add.setOnClickListener(this);
        multiply.setOnClickListener(this);
        divide.setOnClickListener(this);
        dot.setOnClickListener(this);
        one.setOnClickListener(this);
        two.setOnClickListener(this);
        three.setOnClickListener(this);
        four.setOnClickListener(this);
        five.setOnClickListener(this);
        six.setOnClickListener(this);
        seven.setOnClickListener(this);
        eight.setOnClickListener(this);
        nine.setOnClickListener(this);
        zero.setOnClickListener(this);
        right.setOnClickListener(this);
        Clean.setOnClickListener(this);
        left.setOnClickListener(this);
        equal.setOnClickListener(this);
        substact.setOnClickListener(this);

//        view.setText(Caculate.calc("1+2*3;"));
    }

    private String lastresult;//用来记录上一个结果
    private boolean now;//判断当前是否进行计算

    @Override
    public void onClick(View v) {
        String text = edit.getText().toString();//获取当前文本编译框内容
        String lasttext;
        boolean clean = false;

        if (text.equals("0"))
        {
            edit.setText("");
        }
        switch(v.getId())
        {
            case R.id.zero:
            case R.id.one:
            case R.id.two:
            case R.id.three:
            case R.id.four:
            case R.id.five:
            case R.id.six:
            case R.id.seven:
            case R.id.eight:
            case R.id.nine:
            case R.id.right:
            case R.id.left:
            case R.id.add:
            case R.id.substact:
            case R.id.multiply:
            case R.id.divide:
                edit.setText(edit.getText() + (String)v.getTag());
                edit.setSelection(edit.getText().length());
                Clean.setText("C");
                now = false;
                break;

            case R.id.dot:
//                edit.setText(edit.getText() + ".");
//                Clean.setText("C");
//                now = false;
//                借用一下dot，改成让跳转到高级模式，自定义函数等
                Intent intent = new Intent(this, com.xiwen.flexcaculator.Main2Activity.class);
                startActivity(intent);
                break;

            case R.id.equal:
                System.out.println("默认字符串修改成功，下面开始计算器功能！");
                String expr = edit.getText().toString()+";";
                System.out.println(expr);
                String a1 = Caculate.calc(expr);
                System.out.println(a1);
//                edit.setSelection(edit.getText().length());
//                lasttext = edit.getText().toString();
                view.setText(a1);
                break;
            //清楚操作，保留上一结果，引入计算部分
            case R.id.Clean:
                if(now==false) {
                    edit.setText("0");
                    edit.setSelection(edit.getText().length());
                    Clean.setText("AC");
                    now = true;
                }else {
                    view.clearComposingText();
                    view.setText("");
                }
                //归零操作，不保留上一次结果
        }
    }
    //public native String stringFromJNI();
}
