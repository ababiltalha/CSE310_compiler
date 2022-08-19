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
PUSH AX ; i decl
PUSH AX ; j decl
PUSH AX ; a decl
MOV AX, -6[BP]
PUSH AX ; a called
PUSH 0
POP AX ; r-val of assignop 0
MOV -6[BP], AX ; assigning 0 to a
POP AX
MOV AX, -2[BP]
PUSH AX ; i called
PUSH 0
POP AX ; r-val of assignop 0
MOV -2[BP], AX ; assigning 0 to i
POP AX
label_for_start_1: ; for loop starting label
MOV AX, -2[BP]
PUSH AX ; i called
PUSH 5
POP AX
POP BX ; left side value
CMP BX, AX ; evaluating i<5
JNL label_1
PUSH 1 ; if i<5 is true
JMP label_0
label_1:
PUSH 0 ; if i<5 is false
label_0:
POP AX
CMP AX, 0
JE label_for_end_1 ; loop ending condn
JMP label_for_stmt_1 ; loop code label
label_for_ite_1: ; loop iterator inc/dec
MOV AX, -2[BP]
PUSH AX ; i called
INC AX
MOV -2[BP], AX
JMP label_for_start_1 ; restart loop
label_for_stmt_1: ; loop code
MOV AX, -4[BP]
PUSH AX ; j called
PUSH 0
POP AX ; r-val of assignop 0
MOV -4[BP], AX ; assigning 0 to j
POP AX
label_for_start_2: ; for loop starting label
MOV AX, -4[BP]
PUSH AX ; j called
MOV AX, -2[BP]
PUSH AX ; i called
POP AX
POP BX ; left side value
CMP BX, AX ; evaluating j<=i
JNLE label_3
PUSH 1 ; if j<=i is true
JMP label_2
label_3:
PUSH 0 ; if j<=i is false
label_2:
POP AX
CMP AX, 0
JE label_for_end_2 ; loop ending condn
JMP label_for_stmt_2 ; loop code label
label_for_ite_2: ; loop iterator inc/dec
MOV AX, -4[BP]
PUSH AX ; j called
INC AX
MOV -4[BP], AX
JMP label_for_start_2 ; restart loop
label_for_stmt_2: ; loop code
MOV AX, -6[BP]
CALL PRINT ; argument a in AX
JMP label_for_ite_2 ; update iterator after stmt
label_for_end_2: ; end of for loop
JMP label_for_ite_1 ; update iterator after stmt
label_for_end_1: ; end of for loop
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
