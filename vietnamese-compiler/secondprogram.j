.class public secondprogram
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
	putstatic	secondprogram/_runTimer LRunTimer;
	new PascalTextIn
	dup
	invokenonvirtual PascalTextIn/<init>()V
	putstatic	secondprogram/_standardIn LPascalTextIn;

; H_mango<--24

	ldc	24
	ineg
	putstatic	secondprogram/H_mango I

; INRA('H_mango bang (24):\t%d\n',H_mango)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_mango bang (24):\t%d\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_mango I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_banana<-0

	ldc	0
	putstatic	secondprogram/H_banana I

; INRA('H_banana bang (0):\t%d\n',H_banana)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_banana bang (0):\t%d\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_banana I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_orange<-45.0

	ldc	45.0
	putstatic	secondprogram/H_orange F

; INRA('H_orange bang (45.0):\t%f\n',H_orange)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_orange bang (45.0):\t%f\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_orange F
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_peels<-H_orange-1.0

	getstatic	secondprogram/H_orange F
	ldc	1.0
	fsub
	putstatic	secondprogram/H_peels F

; INRA('H_orange/H_peels bang (1.02):\t%f\n',(H_orange/H_peels))

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_orange/H_peels bang (1.02):\t%f\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_orange F
	getstatic	secondprogram/H_peels F
	fdiv
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_peels<-H_orange*90.0

	getstatic	secondprogram/H_orange F
	ldc	90.0
	fmul
	putstatic	secondprogram/H_peels F

; INRA('H_peels bang (4050.0):\t%f\n',H_peels)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_peels bang (4050.0):\t%f\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_peels F
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_mango<-H_mango+235

	getstatic	secondprogram/H_mango I
	ldc	235
	iadd
	putstatic	secondprogram/H_mango I

; INRA('H_mango bang (259):\t%d\n',H_mango)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_mango bang (259):\t%d\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_mango I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_mango<-H_banana+1

	getstatic	secondprogram/H_banana I
	ldc	1
	iadd
	putstatic	secondprogram/H_mango I

; INRA('H_mango bang (1):\t%d\n',H_mango)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_mango bang (1):\t%d\n"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_mango I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_lies<-0

	ldc	0
	putstatic	secondprogram/H_lies I

; H_truth<-1

	ldc	1
	putstatic	secondprogram/H_truth I

; NEU(H_orange!=46.0){H_mango<--120;}KHAC{H_mango<-1;}

	getstatic	secondprogram/H_orange F
	ldc	46.0
	fcmpl
	ifne	L001
	iconst_0
	goto	L002

L001:

	iconst_1

L002:

	ifeq	L003

; {H_mango<--120;}


; H_mango<--120

	ldc	120
	ineg
	putstatic	secondprogram/H_mango I

; 

	goto	L004

L003:


; {H_mango<-1;}


; H_mango<-1

	ldc	1
	putstatic	secondprogram/H_mango I

; 


L004:


; INRA('H_mango bang (-12):\t%d,\nH_banana bang (0):\t%d,\nH_orange bang (45.0):\t%f,\nH_peels bang (4050.0):\t%f,\nH_lies bang (0):\t%d,\nH_truth bang (1):\t%d.',H_mango,H_banana,H_orange,H_peels,H_lies,H_truth)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_mango bang (-12):\t%d,\nH_banana bang (0):\t%d,\nH_orange bang (45.0):\t%f,\nH_peels bang (4050.0):\t%f,\nH_lies bang (0):\t%d,\nH_truth bang (1):\t%d."
	ldc	6
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_mango I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	ldc	1
	getstatic	secondprogram/H_banana I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	ldc	2
	getstatic	secondprogram/H_orange F
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	ldc	3
	getstatic	secondprogram/H_peels F
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	ldc	4
	getstatic	secondprogram/H_lies I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	ldc	5
	getstatic	secondprogram/H_truth I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_peels<-2.0

	ldc	2.0
	putstatic	secondprogram/H_peels F

; KHI(H_peels>=0.0){INRA('\nH_truth bang (1):\t%d',H_truth);INRA('\nH_peels bang (2, 1, 0):\t%f',H_peels);H_peels<-H_peels-1.0;}


L005:

	getstatic	secondprogram/H_peels F
	ldc	0.0
	fcmpl
	ifge	L006
	iconst_0
	goto	L007

L006:

	iconst_1

L007:

	ifeq	L008

; {INRA('\nH_truth bang (1):\t%d',H_truth);INRA('\nH_peels bang (2, 1, 0):\t%f',H_peels);H_peels<-H_peels-1.0;}


; INRA('\nH_truth bang (1):\t%d',H_truth)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"\nH_truth bang (1):\t%d"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_truth I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; INRA('\nH_peels bang (2, 1, 0):\t%f',H_peels)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"\nH_peels bang (2, 1, 0):\t%f"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_peels F
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_peels<-H_peels-1.0

	getstatic	secondprogram/H_peels F
	ldc	1.0
	fsub
	putstatic	secondprogram/H_peels F

; 

	goto	L005

L008:


; INRA('\nH_peels bang (2, 1, 0):\t%f',H_peels)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"\nH_peels bang (2, 1, 0):\t%f"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_peels F
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_peels<-2.0

	ldc	2.0
	putstatic	secondprogram/H_peels F

; LAP(H_peels>=0.0){INRA('\nH_truth bang (1):\t%d',H_truth);INRA('\nH_peels bang (2, 1, 0):\t%f',H_peels);H_peels<-H_peels-1.0;}


L009:


; {INRA('\nH_truth bang (1):\t%d',H_truth);INRA('\nH_peels bang (2, 1, 0):\t%f',H_peels);H_peels<-H_peels-1.0;}


; INRA('\nH_truth bang (1):\t%d',H_truth)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"\nH_truth bang (1):\t%d"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_truth I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; INRA('\nH_peels bang (2, 1, 0):\t%f',H_peels)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"\nH_peels bang (2, 1, 0):\t%f"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	secondprogram/H_peels F
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_peels<-H_peels-1.0

	getstatic	secondprogram/H_peels F
	ldc	1.0
	fsub
	putstatic	secondprogram/H_peels F

; 

	getstatic	secondprogram/H_peels F
	ldc	0.0
	fcmpl
	ifge	L0010
	iconst_0
	goto	L0011

L0010:

	iconst_1

L0011:

	ifeq	L009

; 


	getstatic     secondprogram/_runTimer LRunTimer;
	invokevirtual RunTimer.printElapsedTime()V

	return

.limit locals 256
.limit stack 256
.end method
