.MODEL SMALL

.STACK 400H

.DATA


.CODE
	FLAG DB 0
	NL DB 13,10,"$"
	NUMBER_STRING DB "00000$" 

main PROC
	MOV AX, @DATA
	MOV DS, AX
PUSH BP
MOV BP, SP
PUSH AX ; a decl
PUSH AX ; b decl
PUSH AX ; c[2] decl
PUSH AX ; c[1] decl
PUSH AX ; c[0] decl
MOV AX, -2[BP]
PUSH AX ; a called
PUSH 1
PUSH 2
;PUSH 3
MOV AX, 3
POP BX
ADD AX, BX
;PUSH AX ; 2+3 pushed
MOV BX, AX
POP AX
IMUL BX
PUSH AX ; result of 1*(2+3) is in AX, pushed
PUSH 3
MOV DX, 0 ; DX:AX = 0000:AX
POP BX
POP AX
IDIV BX
;PUSH DX ; remainder of 1*(2+3)%3 is in DX
MOV AX, DX
MOV -2[BP], AX ; assigning 1*(2+3)%3 to a
POP AX
MOV AX, -4[BP]
PUSH AX ; b called
PUSH 1
;PUSH 5
MOV AX, 5
POP BX ; left side value
CMP BX, AX ; evaluating 1<5
JNL label_1
PUSH 1 ; if 1<5 is true
JMP label_0
label_1:
PUSH 0 ; if 1<5 is false
label_0:
POP AX ; r-val of assignop 1<5
MOV -4[BP], AX ; assigning 1<5 to b
POP AX
;PUSH 0
MOV BX, 0
SHL BX, 1
ADD BX, -10
;ADD BX, BP
PUSH BP
ADD BP, BX
MOV AX, [BP]
POP BP
;MOV AX, [BX]
PUSH AX ; value of c[0]
PUSH BX ; index 0
;PUSH 2
MOV AX, 2
POP BX
;MOV [BX], AX
PUSH BP
ADD BP, BX
MOV [BP], AX
POP BP ; assigning to c[0]
POP AX
MOV AX, -2[BP]
PUSH AX ; a called
MOV AX, -4[BP]
;PUSH AX ; b called
MOV BX, AX
POP AX ; left side value
CMP AX, 0
JE label_3
CMP BX, 0
JE label_3
PUSH 1
JMP label_2
label_3:
PUSH 0 ; total false
label_2:
POP AX ; expr in AX
CMP AX, 0 ; checking expr
JE label_else_1
;PUSH 0
MOV BX, 0
SHL BX, 1
ADD BX, -10
;ADD BX, BP
PUSH BP
ADD BP, BX
MOV AX, [BP]
POP BP
;MOV AX, [BX]
PUSH AX ; value of c[0]
;PUSH BX ; index 0
;POP BX
POP AX
INC AX ; c[0]++
PUSH BP
ADD BP, BX
MOV [BP], AX
POP BP
POP AX
JMP label_endif_1
label_else_1: ; else label
;PUSH 1
MOV BX, 1
SHL BX, 1
ADD BX, -10
;ADD BX, BP
PUSH BP
ADD BP, BX
MOV AX, [BP]
POP BP
;MOV AX, [BX]
PUSH AX ; value of c[1]
PUSH BX ; index 1
;PUSH 0
MOV BX, 0
SHL BX, 1
ADD BX, -10
;ADD BX, BP
PUSH BP
ADD BP, BX
MOV AX, [BP]
POP BP
;MOV AX, [BX]
PUSH AX ; value of c[0]
;PUSH BX ; index 0
;POP BX ; r-value, no need for index
POP AX ; r-val of assignop c[0]
POP BX
;MOV [BX], AX
PUSH BP
ADD BP, BX
MOV [BP], AX
POP BP ; assigning to c[1]
POP AX
label_endif_1: ; end if label
MOV AX, -2[BP]
CALL PRINT ; argument a in AX
MOV AX, -4[BP]
CALL PRINT ; argument b in AX
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
