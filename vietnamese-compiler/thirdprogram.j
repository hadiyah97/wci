.class public thirdprogram
.super java/lang/Object

.field private static _runTimer LRunTimer;
.field private static _standardIn LPascalTextIn;

; T_integerH_mango,H_banana

.field private static H_mango I
.field private static H_banana I

; T_floatH_orange,H_peels

.field private static H_orange F
.field private static H_peels F

; T_booleanH_lies,H_truth

.field private static H_lies I
.field private static H_truth I

.method public <init>()V

	aload_0
	invokenonvirtual java/lang/Object/<init>()V
	return

.limit locals 1
.limit stack 1
.end method

.method public static main([Ljava/lang/String;)V

	new RunTimer
	dup
	invokenonvirtual RunTimer/<init>()V
	putstatic	thirdprogram/_runTimer LRunTimer;
	new PascalTextIn
	dup
	invokenonvirtual PascalTextIn/<init>()V
	putstatic	thirdprogram/_standardIn LPascalTextIn;

; H_mango<-24

	ldc	24
	putstatic	thirdprogram/H_mango I

; INRA('H_mango bang (24):\t%d\n',H_mango)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_mango bang (24):\t%d\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	thirdprogram/H_mango I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_banana<-0

	ldc	0
	putstatic	thirdprogram/H_banana I

; INRA('H_banana bang (0):\t%d\n',H_banana)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_banana bang (0):\t%d\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	thirdprogram/H_banana I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_orange<-45.0

	ldc	45.0
	putstatic	thirdprogram/H_orange F

; INRA('H_orange bang (45.0):\t%f\n',H_orange)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_orange bang (45.0):\t%f\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	thirdprogram/H_orange F
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_peels<-H_orange-1.0

	getstatic	thirdprogram/H_orange F
	ldc	1.0
	fsub
	putstatic	thirdprogram/H_peels F

; INRA('H_orange/H_peels bang (1.02):\t%f\n',(H_orange/H_peels))

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_orange/H_peels bang (1.02):\t%f\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	thirdprogram/H_orange F
	getstatic	thirdprogram/H_peels F
	fdiv
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_peels<-H_orange*90.0

	getstatic	thirdprogram/H_orange F
	ldc	90.0
	fmul
	putstatic	thirdprogram/H_peels F

; INRA('H_peels bang (4050.0):\t%f\n',H_peels)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_peels bang (4050.0):\t%f\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	thirdprogram/H_peels F
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_mango<-H_mango+235

	getstatic	thirdprogram/H_mango I
	ldc	235
	iadd
	putstatic	thirdprogram/H_mango I

; INRA('H_mango bang (259):\t%d\n',H_mango)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_mango bang (259):\t%d\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	thirdprogram/H_mango I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_mango<-H_banana+1

	getstatic	thirdprogram/H_banana I
	ldc	1
	iadd
	putstatic	thirdprogram/H_mango I

; INRA('H_mango bang (1):\t%d\n',H_mango)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_mango bang (1):\t%d\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	thirdprogram/H_mango I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; 


	getstatic     thirdprogram/_runTimer LRunTimer;
	invokevirtual RunTimer.printElapsedTime()V

	return

.limit locals 256
.limit stack 256
.end method
