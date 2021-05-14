package com.xiwen.flexcaculator;

import android.content.Intent;
import android.os.Bundle;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.GridLayout;
import android.widget.TextView;

public class Main2Activity extends AppCompatActivity implements View.OnClickListener{
    private GridLayout gridlayout;
    private EditText edit;
    private TextView view;
    private Button Clean;
    private Button cacl;
    private Button dot;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        gridlayout = (GridLayout) findViewById(R.id.gridlayout);
        edit = (EditText) findViewById(R.id.edit);
        view = (TextView) findViewById(R.id.view);
        cacl = (Button) findViewById(R.id.cacl);
        Clean = (Button) findViewById(R.id.Clean);
        dot = (Button) findViewById(R.id.dot);

        edit.setOnClickListener(this);
        view.setOnClickListener(this);
        cacl.setOnClickListener(this);
        Clean.setOnClickListener(this);
        dot.setOnClickListener(this);

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
            case R.id.cacl:
                System.out.println("默认字符串修改成功，下面开始计算器功能！");
                System.out.println(edit.getText());
                String a1 = Caculate.calc(edit.getText().toString());
                edit.setSelection(edit.getText().length());
                System.out.println(a1);
//                lasttext = edit.getText().toString();
                view.setText(a1);
                Clean.setText("C");
                now = false;
                break;
            case R.id.dot:
//                借用一下dot，改成让跳转到普通版模式，自定义函数等
                Intent intent = new Intent(this, com.xiwen.flexcaculator.MainActivity.class);
                startActivity(intent);
                break;
            //清楚操作，保留上一结果，引入计算部分
            case R.id.Clean:
                if(now==false) {
                    edit.setText("");
                    Clean.setText("AC");
                    now = true;
                }else {
                    view.clearComposingText();
                    view.setText("");
                }
                //归零操作，不保留上一次结果
        }
    }
}
