.MODEL SMALL

.STACK 400H

.DATA
	FLAG DB 0
	NL DB 13,10,"$"
	NUMBER_STRING DB "00000$" 

.CODE

f PROC
	PUSH BP
	MOV BP, SP
PUSH AX ; w decl
MOV AX, -2[BP]
PUSH AX ; w called
PUSH 2
MOV AX, 4[BP]
PUSH AX ; a called
POP BX
POP AX
IMUL BX
PUSH AX ; result of 2*a is in AX, pushed
POP AX ; r-val of assignop 2*a
MOV -2[BP], AX ; assigning 2*a to w
POP AX
MOV AX, -2[BP]
PUSH AX ; w called
POP AX
	JMP f_EXIT
MOV AX, 4[BP]
PUSH AX ; a called
PUSH 9
POP AX ; r-val of assignop 9
MOV 4[BP], AX ; assigning 9 to a
POP AX
f_EXIT:
	MOV SP, BP ; Restoring SP
	POP BP
	RET 2
f ENDP

g PROC
	PUSH BP
	MOV BP, SP
PUSH AX ; x decl
MOV AX, -2[BP]
PUSH AX ; x called
MOV AX, 6[BP]
PUSH AX ; a called
CALL f
PUSH AX ; return value of f
MOV AX, 6[BP]
PUSH AX ; a called
POP AX
POP BX
ADD AX, BX
PUSH AX ; f(a)+a pushed
MOV AX, 4[BP]
PUSH AX ; b called
POP AX
POP BX
ADD AX, BX
PUSH AX ; f(a)+a+b pushed
POP AX ; r-val of assignop f(a)+a+b
MOV -2[BP], AX ; assigning f(a)+a+b to x
POP AX
MOV AX, -2[BP]
PUSH AX ; x called
POP AX
	JMP g_EXIT
g_EXIT:
	MOV SP, BP ; Restoring SP
	POP BP
	RET 4
g ENDP

main PROC
	MOV AX, @DATA
	MOV DS, AX
PUSH BP
MOV BP, SP
PUSH AX ; a decl
PUSH AX ; b decl
MOV AX, -2[BP]
PUSH AX ; a called
PUSH 1
POP AX ; r-val of assignop 1
MOV -2[BP], AX ; assigning 1 to a
POP AX
MOV AX, -4[BP]
PUSH AX ; b called
PUSH 2
POP AX ; r-val of assignop 2
MOV -4[BP], AX ; assigning 2 to b
POP AX
MOV AX, -2[BP]
PUSH AX ; a called
MOV AX, -2[BP]
PUSH AX ; a called
MOV AX, -4[BP]
PUSH AX ; b called
CALL g
PUSH AX ; return value of g
POP AX ; r-val of assignop g(a,b)
MOV -2[BP], AX ; assigning g(a,b) to a
POP AX
MOV AX, -2[BP]
CALL PRINT ; argument a in AX
PUSH 0
POP AX
	JMP main_EXIT
main_EXIT:
	MOV SP, BP ; Restoring SP
	POP BP
	MOV AH, 4CH
	INT 21H
main ENDP

PRINT PROC ; PRINTS A WORD INTEGER IN AX
	LEA SI, NUMBER_STRING ; IS 00000
    ADD SI, 5 ; START FROM ONE'S DIGIT
    CMP AX, 0
    JNL PRINT_LOOP
    MOV FLAG, 1
    NEG AX
    PRINT_LOOP:
        DEC SI
        MOV DX, 0 ; DX:AX = 0000:AX
        MOV CX, 10
        DIV CX
        ADD DL, '0'
        MOV [SI], DL
        CMP AX, 0
        JNE PRINT_LOOP
    CMP FLAG, 0
    JNG NOT_NEGATIVE
    MOV AH, 2
    MOV DL, 45
    INT 21H
    MOV FLAG, 0
	NOT_NEGATIVE:
    MOV DX, SI
    MOV AH, 9
    INT 21H
	MOV DX, OFFSET NL   ; NEWLINE
    MOV AH, 9
    INT 21H
    RET
PRINT ENDP
END MAIN
