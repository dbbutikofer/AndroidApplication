package com.example.drew.clienttest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.EditText;

import java.net.Socket;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MainActivity extends AppCompatActivity
{

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        final EditText myText = (EditText) this.findViewById(R.id.editText);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        new Thread(new Runnable() {
            public void run() {
                try
                {
                    Socket sock = new Socket("10.0.2.2", 1234);

                    // Your Java Code Verbatim:
                    BufferedReader br = new BufferedReader(new InputStreamReader(sock.getInputStream()));
                    String test = br.readLine();

                    Log.d("myTag",test);

                    sock.close();
                } catch (Exception ex) {}
            }
        }).start();

    }
}
