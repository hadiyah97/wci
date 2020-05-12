.class public trial
.super java/lang/Object

.field private static _runTimer LRunTimer;
.field private static _standardIn LPascalTextIn;

; T_integerH_mango

.field private static H_mango I

; T_floatH_oranges

.field private static H_oranges F

.method public <init>()V

	aload_0
	invokenonvirtual java/lang/Object/<init>()V
	return

.limit locals 1
.limit stack 1
.end method

.method private static G_functionName(I)I
.var 1 is H_firstVariable I
.var 2 is G_functionName I

; INRA('Inside the function:')

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"Inside the function:"
	ldc	0
	anewarray	java/lang/Object
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; INRA('H_firstVariable bang (1):\t%d',H_firstVariable)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_firstVariable bang (1):\t%d"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	iload_0
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; TRALOIH_firstVariable

	iload_0

; 

	ireturn

.limit locals 32
.limit stack 32
.end method

.method public static main([Ljava/lang/String;)V

	new RunTimer
	dup
	invokenonvirtual RunTimer/<init>()V
	putstatic	trial/_runTimer LRunTimer;
	new PascalTextIn
	dup
	invokenonvirtual PascalTextIn/<init>()V
	putstatic	trial/_standardIn LPascalTextIn;

; H_mango<--25

	ldc	25
	ineg
	putstatic	trial/H_mango I

; INRA('H_mango bang (-25):\t%d',H_mango)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_mango bang (-25):\t%d"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	trial/H_mango I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_oranges<-95.4

	ldc	95.4
	putstatic	trial/H_oranges F

; INRA('H_oranges bang (95.4):\t%f',H_oranges)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_oranges bang (95.4):\t%f"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	trial/H_oranges F
	invokestatic	java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop

; H_mango<-G_functionName(1)

	ldc	1
	invokestatic	trial/G_functionName(I)I
	putstatic	trial/H_mango I	
	
; INRA('H_mango bang (0):\t%d',H_mango)

	getstatic	java/lang/System/out Ljava/io/PrintStream;
	ldc	"H_mango bang (0):\t%d"
	ldc	1
	anewarray	java/lang/Object
	dup
	ldc	0
	getstatic	trial/H_mango I
	invokestatic	java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop
	
; 


	getstatic     trial/_runTimer LRunTimer;
	invokevirtual RunTimer.printElapsedTime()V

	return

.limit locals 256
.limit stack 256
.end method
