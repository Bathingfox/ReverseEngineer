package com.learning.crackme;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("crackme");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        final EditText editText1 = (EditText) findViewById(R.id.name);
        final EditText editText2 = (EditText) findViewById(R.id.serial);
        Button btn = (Button) findViewById(R.id.login);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(isValid(editText1.getText().toString(), editText2.getText().toString())) {
                    startActivity(new Intent(MainActivity.this, ResultActivity.class));
                    return;
                }
                Toast.makeText(MainActivity.this.getApplicationContext(), "Verify failed...", 0).show();
            }
        });
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native boolean isValid(String name, String serial);
}
