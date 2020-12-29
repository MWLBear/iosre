### Hopper
界面:

- “D” “A” “C” “P” “U” 代表 数据,ASCII字符串,代码,函数,未定义数据

blcok结构体对应代码

```
struct Block_layout {
	void *isa;
	int flags;
	int resrved;
	void (*invoke)(void*,...);
	struct Block_desciptor *descriptor;
	/* Import variables. */
}


struct Block_literal_1 {
    void *isa; // initialized to &_NSConcreteStackBlock or &_NSConcreteGlobalBlock
    int flags;
    int reserved;
    void (*invoke)(void *, ...);
    struct Block_descriptor_1 {
    	unsigned long int reserved;         // NULL
        unsigned long int size;         // sizeof(struct Block_literal_1)
        // optional helper functions
        void (*copy_helper)(void *dst, void *src);     // IFF (1<<25)
        void (*dispose_helper)(void *src);             // IFF (1<<25)
        // required ABI.2010.3.16
        const char *signature;                         // IFF (1<<30)
    } *descriptor;
    // imported variables
};



```

### IDA
- 左侧`Ctrl+F`快捷键进行类或方法的搜索。
- F5 显示伪代码
- 字符串搜索 `Alt+T` mac `Option+T`
- 跳转地址 `G`键
- 编写注释 "/"
- 变量重命名 "N"
- 查看交叉引用 "X"
- 进制转换 "H"
- 类定义: "Y"
- 格式转换 “C”键，即可将其还原成代码,在未被解析成数据的地方按“D”键，即可将机器码或者其他

### 静态库分析
- FAT 文件瘦身:  `
lipo Crashlytics -thin arm64 -output Crashlytics_arm64`

- ar指令过ar命令将静态库中的所有OBJECT文件解压出来

	```
	mkdir Objects
	cd Objects
	an -x . ./Crashlytics_arm64
	```
	 
- 如下命令可以查找所有出现“Upload"字符 :`grep "Upload" -rn ./`
- OBJECT文件是否包含bitcode `otool -1 Crashlytics.o | grep bitcode`
 
- 将所有OBJECT文件链接成一个OBJECT文件: `ld -r -arch arm64 -syslibroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk -bitcode_bundle ./*.o -o ../output` (若包含bitcode,则添加参数-bitcode_bundle;若不包含，则不用添加)
 
 
 ### 动态调试
 
- 1.复制debugserver文件 目录:

	- debugserver在Mac上的路径是：
	`/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/DeviceSupport/13.2/DeveloperDiskImage.dmg/usr/bin/debugserver`
	
	- debugserver安装到手机的路径是：
	`/Developer/usr/bin/debugserver`
- 2.签名权限:新建`entitlements.plist`文件，在其中写入如下内容:

	```
	<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>get-task-allow</key>
    <true/>
    <key>platform-application</key>
    <true/>
    <key>run-unsigned-code</key>
    <true/>
    <key>task_for_pid-allow</key>
    <true/>
    <key>com.apple.springboard.debugapplications</key>
    <true/>
    <key>com.apple.backboardd.launchapplications</key>
    <true/>
    <key>com.apple.backboardd.debugapplications</key>
    <true/>
    <key>com.apple.frontboard.launchapplications</key>
    <true/>
    <key>com.apple.frontboard.debugapplications</key>
    <true/>
    <key>com.apple.private.logging.diagnostic</key>
    <true/>
    <key>com.apple.private.memorystatus</key>
    <true/>
    <key>com.apple.private.cs.debugger</key>
    <true/>
</dict>
</plist>


	``` 
- 3.重签名 `codesign -s - --entitlements entitlements.plist -f debugserver`
- 4.将 debugserver文件复制回手机:`scp -P 2222 ./debugserver root@localhost:/usr/bin/debugserver`
 
- 5使用:

  debugserver 127.0.0.1:1234 -a WeChat`
  
  `$ lldb  `
  
  `(lldb) process connect connect://localhost:1234 `
 
 
 
  ### lldb 常用指令
-  register read:读取所有寄存器的值。
-  register read $x0:读取某个寄存器的值。
-  register write $x5 1:修改某个寄存器的值。
-  si:跳到当前指令的内部。
-  ni:跳过当前指令。
-  finish:返回上层调用栈。
-  thread return:不再执行下面的代码，直接从当前调用栈返回一个值。
-  br list:査看当前断点列表。 
-  br del:删除当前的所有断点。
- br del 1.1.1:删除指定编号的断点。
- br dis2.1:使断点2.1失效。
- br enable2.1:使断点2.1 生效。
- watch point set expression -w write --0xl01801a48:给某个地址设置观察断点，当对该地址的内存进行写操作时就会触发断点。
- x/10xg 0x101801a48:读取目标地址的内存指令。这里的“x”代表用十六进制来显示结果，“g”代表giant word(8字节)大小。所以，“x/10xg”就是用十六进制显示0x101801a48所指空间的10个64位的元素内容。常见的大小格式为“b-byte”( 1字节)“h-half world”(2字节)“w- word”(4字节)“g- giant word”(8字节)。
• dis -a $pc:反汇编指定地址。这里是pc寄存器所对应的地址。
• f2:切换到当前调用栈为2的位置，也就是bt中的frame #2。
• thread info:输出当前线程的信息。
• b ptrace-c xxx:满足某个条件之后程序才会中断。
- br s -a 0x0000000000074000+0x0000000100069700
 ### LLDB的高级调试技巧
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 