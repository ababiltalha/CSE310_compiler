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
PUSH AX ; c decl
PUSH AX ; i decl
MOV AX, -4[BP]
PUSH AX ; b called
PUSH 0
POP AX ; r-val of assignop 0
MOV -4[BP], AX ; assigning 0 to b
POP AX
MOV AX, -6[BP]
PUSH AX ; c called
PUSH 3
POP AX ; r-val of assignop 3
MOV -6[BP], AX ; assigning 3 to c
POP AX
label_0: ; while loop begin
MOV AX, -6[BP]
PUSH AX ; c called
DEC AX
MOV -6[BP], AX
POP CX
CMP CX, 0
JE label_1
MOV AX, -4[BP]
PUSH AX ; b called
INC AX
MOV -4[BP], AX
POP AX
JMP label_0 ; back to top of loop
label_1:
MOV AX, -4[BP]
CALL PRINT ; argument b in AX
MOV AX, -6[BP]
CALL PRINT ; argument c in AX
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
