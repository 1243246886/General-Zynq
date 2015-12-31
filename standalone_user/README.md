# For standalone user
实验环境：vivado2014.4</br>
板卡：ZYBO</br>
<h2>测试各个外设</h2>

- 先在vivado上导出bitstream并Launch SDK</br>
<code>[vivado] File->Export->Export Hardware...</code></br>
打钩 `Include bitstream`</br>
点击ok.</br>
<code>[vivado] File->Launch SDK</code></br>
- 使用SDK建立应用工程：</br>
<code>[SDK] File->New->Application_Project</code></br>
- 为新建工程起名为 `test_XXX` 点击 Next</br>
选择template为 `Empty Application` 然后点击 Finish. 这个步骤会建立一个空白的工程和一个对应的BSP.</br>
- 将要测试的外设(ADC、IIC、PWM等)目录下的源文件导入到工程的src目录下:选择<code> General->File_System</code> 然后点击 Next</br>
  在 <code>From directory</code>中, 展开并选择`'your path’/standalone_user/XXX_test/src`文件夹</br>
  将所有文件导入。</br>
- 最后<code>Program FPGA</code>，并<code>Launch GDB</code>，即可在ZYBO板看到实验现象。</br>



