; Name: David Barbet
; gtid: dbarbet3


; Main
; Do not edit this function!

.orig x3000

	LD R6, STACK	; Initialize the stack

	LEA R0, STRING	; R0 = &str[0]
	ADD R1, R0, 0

SL_LOOP	LDR R2, R1, 0	; \ R1 = strlen(str)
	BRz SL_END	; |
	ADD R1, R1, 1	; |
	BR SL_LOOP	; |
SL_END	NOT R2, R0	; |
	ADD R2, R2, 1	; |
	ADD R1, R1, R2	; /

	ADD R6, R6, -2	; \ R0 = eval(str, len)
	STR R0, R6, 0	; | (add first param to stack: string)
	STR R1, R6, 1	; | (add 2nd param to stack: len)
	LD R2, EVALPTR	; |
	JSRR R2		; |
	LDR R0, R6, 0	; |
	ADD R6, R6, 3	; /

	ST R0, ANS
	HALT

STACK	.fill xf000
ANS	.fill -1
EVALPTR	.fill EVAL
STRING	.stringz "1*2+3*4+5"
	.blkw 200
PLUS	.fill '+'
MULT	.fill '*'
ZERO	.fill '0'

EVAL
	
	;Init stack frame
	ADD R6, R6, -1; Add one space for ret val
    	ADD R6, R6, -1; Add space for ret address
    	STR R7, R6, 0; Store ret add onto stack
   	ADD R6, R6, -1; Add space for old fp
    	STR R5, R6, 0; Store old fp
    	ADD R6, R6, -1; Go to spot for first local
    	ADD R5, R6, 0; Point fp at first loc
	ADD R6, R6, -2; Point R6 to the top of the stack
	
	;Init local vars
	AND R0, R0, 0; Clear r0 for i
	STR R0, R5, 0; i = 0 at first local in stack frame (r0 = i)
	STR R1, R5, -1; Store left at 2nd local in stack frame (r1 = left)
	STR R2, R5, -2; Store right 0 at 3rd local in stack frame (r2 = right)

	;Condition of first while
	W1COND
	LDR R3, R5, 5; Find len (2nd param) at r5 (first loc) plus 5 (down) (r3 = len)
	NOT R3, R3; Step 1 negation
	ADD R3, R3, 1; -len
	ADD R3, R0, R3; i - len
	BRn W1TRUE; Go to inside while if negative
	BRzp CONT; Go to next code if otherwise
	
	;Inside first while
	W1TRUE
	;Check if condition
	LDR R4, R5, 4; Find string (first param) at r5 (first loc) plus 5 (down) (r4 = string)
	ADD R4, R4, R0; compute new address
	LDR R4, R4, 0; Find string[i] (r0 = i) and put in r4
	NOT R4, R4; Step 1 negation
	ADD R4, R4, 1; negative of string
	AND R3, R3, 0; clear r3 for quick operation
	LD R3, PLUS; load + into r3
	ADD R4, R4, R3; add negative of string to +, if string = +, answer = 0
	LDR R3, R5, 5; reload len into r3
	ADD R4, R4, 0; put r4 back in cc
	BRz IF1TRUE; Branch to if1 true when string = +
	BRnp IF1FALSE; Branch to if1 false when string is not +
	
	;Else
	IF1FALSE
	ADD R0, R0, 1; Increment i
	BR W1COND; continue whiling

	;Inside first if
	IF1TRUE

	;First recursion statement (left)
	STR R0, R5, 0; Store i (r0) in first loc
	ADD R6, R6, -2; New frame for first recursion
	LDR R4, R5, 4; Reload str into r4 (r4 = string)
	STR R4, R6, 0; Put r4 (string) as first param in new stack
	STR R0, R6, 1; Put r0 (i) as second param in new stack
	JSR EVAL
	LDR R1, R6, 0; R1 = eval(str, i) (2nd local var)
	STR R1, R5, -1; left = eval(str, i)
	ADD R6, R5, -2; return stack pt to old position

	;Second recursion statement (right)
	LDR R0, R5, 0; Reload i into r0
	ADD R6, R6, -2; New frame for second recursion
	LDR R4, R5, 4; Reload str address into r4 (r4 = string)
	ADD R4, R4, R0; ADD str(r4) + i(r0)
	ADD R4, R4, 1; ADD str(r4) + i(r0) + 1 (this is the new address to use)
	STR R4, R6, 0; put str + i + 1 as first param in new stack
	NOT R0, R0; Step 1 of -i
	ADD R0, R0, 1; -i
	LDR R3, R5, 5; put len in r3
	ADD R3, R3, R0; len - i
	ADD R3, R3, -1; len - i - 1
	STR R3, R6, 1; put len - i -1 as 2nd param on new stack
	JSR EVAL
	LDR R2, R6, 0; R2 = eval(str + i + 1, len - i - 1) (3rd local var)
	STR R2, R5 , -2; right = eval(str + i....) (3rd local var)
	ADD R6, R5, -2; Return stack pt to old position
	LDR R0, R5, 0; Reload i into r0

	;Return statement left + right
	AND R0, R0, 0; Clear R0
	LDR R1, R5, -1; Load left into r1
	LDR R2, R5, -2; Load right into r2
	ADD R0, R2, R1; left + right = r1
	BR RETURN; branch to return

	;Continue with code
	CONT
	AND R0, R0, 0; Clear r0 for i
	STR R0, R5, 0; i = 0 at first local in stack frame (r0 = i)
	BR W2COND; go to check while loop 2 condition
	
	;Second while cond
	W2COND
	LDR R3, R5, 5; Find len (2nd param) at r5 (first loc) plus 5 (down) (r3 = len)
	NOT R3, R3; Step 1 negation
	ADD R3, R3, 1; -len
	ADD R3, R0, R3; i - len
	BRn W2TRUE; Go to inside while if negative
	BRzp RET2; Go to final return if none of the others are hit

	;Inside second while
	W2TRUE

	;Check if condition
	LDR R4, R5, 4; Find string (first param) at r5 (first loc) plus 5 (down) (r4 = string)
	ADD R4, R4, R0; compute new address
	LDR R4, R4, 0; Find string[i] (r0 = i) and put in r4
	NOT R4, R4; Step 1 negation
	ADD R4, R4, 1; negative of string
	AND R3, R3, 0; clear r3 for quick operation
	LD R3, MULT; load * into r3
	ADD R4, R4, R3; add negative of string to *, if string = *, answer = 0
	LDR R3, R5, 5; reload len into r3
	ADD R4, R4, 0; put r4 back in cc
	BRz IF2TRUE; Branch to if1 true when string = *
	BRnp IF2FALSE; Branch to if1 false when string is not *
	
	;Else
	IF2FALSE
	ADD R0, R0, 1; Increment i
	BR W2COND; continue whiling

	;if
	IF2TRUE
	;First recursion statement (left)
	STR R0, R5, 0; Store i (r0) in first loc
	ADD R6, R6, -2; New frame for first recursion
	LDR R4, R5, 4; Reload str into r4 (r4 = string)
	STR R4, R6, 0; Put r4 (string) as first param in new stack
	STR R0, R6, 1; Put r0 (i) as second param in new stack
	;STR R0, R5, 0; i at first local in stack frame (r0 = i)
	;STR R1, R5, -1; Store left at 2nd local in stack frame (r1 = left)
	;STR R2, R5, -2; Store right 0 at 3rd local in stack frame (r2 = right)
	JSR EVAL
	LDR R1, R6, 0; R1 = eval(str, i) (2nd local var)
	STR R1, R5, -1; left = eval(str, i)
	ADD R6, R5, -2; Return sp to top of stack

	;Second recursion statement (right)
	LDR R0, R5, 0; Reload i into r0
	ADD R6, R6, -2; New frame for second recursion
	LDR R4, R5, 4; Reload str address into r4 (r4 = string)
	ADD R4, R4, R0; ADD str(r4) + i(r0)
	ADD R4, R4, 1; ADD str(r4) + i(r0) + 1 (new address for str)
	STR R4, R6, 0; put str + i + 1 as first param in new stack
	NOT R0, R0; Step 1 of -i
	ADD R0, R0, 1; -i
	LDR R3, R5, 5; put len in r3
	ADD R3, R3, R0; len - i
	ADD R3, R3, -1; len - i - 1
	STR R3, R6, 1; put len - i -1 as 2nd param on new stack
	JSR EVAL
	LDR R2, R6, 0; R2 = eval(str + i + 1, len - i - 1) (3rd local var)
	STR R2, R5, -2; right = eval(str + i....) (3rd local var)
	ADD R6, R5, -2; Return sp to top of stack
	LDR R0, R5, 0; Reload i into r0

	;Return statement left * right
	
	AND R0, R0, 0; Clear R0
	LDR R1, R5, -1; load actual left data
	LDR R2, R5, -2; load actual right data
	ADD R0, R1, 0; put r1 in r0
	ADD R2, R2, -1; decrement before mult
	MULTIPLY
	ADD R0, R0, R1; left + left
	ADD R2, R2, -1; right - 1
	BRp MULTIPLY; do until right is not positive
	BRnz RETURN; branch to return

	;RETURN FROM FUNC
	RETURN
	STR R0, R5, 3; store left + right in ret val
	LDR R7, R5, 2; ret address
	ADD R6, R5, 3; point r6 at return value
	LDR R5, R5, 1; Restore r5
	BR DONE

	;Return number 2
	RET2
	AND R0, R0, 0; clear r0 for ans
	LDR R3, R5, 4; load str into r3
	LDR R3, R3, 0; load str at r3 into r3
	LD R4, ZERO; load zero into r4
	NOT R4, R4; step 1 of -'0'
	ADD R4, R4, 1; step 2 of -'0'
	ADD R0, R4, R3; add str - '0'
	BR RETURN

	;LDR R7, R5, 2; ret address
	;ADD R6, R5, 3; point r6 at return value
	;LDR R5, R5, 1; Restore r5
	;BR DONE

	DONE
	RET

	;RET2
	;AND R0, R0, 0; clear r0
	;LDR R3, R5, 4; load str into r3
	;LDR R3, R3, 0; load str at r3 into r3
	;LD R4, ZERO; load zero into r4
	;NOT R4, R4; step 1 of -'0'
	;ADD R4, R4, 1; step 2 of -'0'
	;ADD R0, R4, R3; add str - '0'
	;BR RETURN

	;LDR R7, R5, 2; ret address
	;ADD R6, R5, 3; point r6 at return value
	;LDR R5, R5, 1; Restore r5
	;BR DONE

.end
