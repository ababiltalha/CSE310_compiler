.MODEL SMALL

.STACK 400H

.DATA
	FLAG DB 0
	NL DB 13,10,"$"
	NUMBER_STRING DB "00000$" 

.CODE

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
MOV AX, -4[BP]
PUSH AX ; b called
PUSH 3
POP AX ; r-val of assignop 3
MOV -4[BP], AX ; assigning 3 to b
POP AX
PUSH 1
POP AX ; expr in AX
CMP AX, 0 ; checking expr
JE label_else_1
PUSH 0
POP AX ; expr in AX
CMP AX, 0 ; checking expr
JE label_else_2
MOV AX, -2[BP]
PUSH AX ; a called
PUSH 10
POP AX ; r-val of assignop 10
MOV -2[BP], AX ; assigning 10 to a
POP AX
JMP label_endif_2
label_else_2: ; else label
MOV AX, -2[BP]
PUSH AX ; a called
PUSH 11
POP AX ; r-val of assignop 11
MOV -2[BP], AX ; assigning 11 to a
POP AX
label_endif_2: ; end if label
JMP label_endif_1
label_else_1: ; else label
MOV AX, -2[BP]
PUSH AX ; a called
PUSH 0
POP AX ; r-val of assignop 0
MOV -2[BP], AX ; assigning 0 to a
POP AX
label_endif_1: ; end if label
MOV AX, -2[BP]
CALL PRINT ; argument a in AX
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
