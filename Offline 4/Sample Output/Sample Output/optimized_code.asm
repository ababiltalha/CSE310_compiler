.MODEL SMALL
.STACK 400H
	;println(n)
.DATA
.CODE
	PRINT_INTEGER PROC NEAR
        PUSH BP             ;Saving BP
        ;if(BX < -1) then the number is positive
        MOV BP, SP          ;BP points to the top of the stack
        MOV BX, [BP+4]    ;The number to be printed
        ;else, the number is negative
        CMP BX, 0
        JGE POSITIVE
        MOV AH, 2           
        MOV DL, '-'         ;Print a '-' sign
        INT 21H
        NEG BX              ;make BX positive
        POSITIVE:
        MOV AX, BX
        MOV CX, 0        ;Initialize character count
        PUSH_WHILE:
            XOR DX, DX  ;clear DX
            ;quotient is in AX and remainder is in DX
            MOV BX, 10  ;BX has the divisor //// AX has the dividend
            DIV BX
            ;if(AX == 0) then break the loop
            PUSH DX     ;Division by 10 will have a remainder less than 8 bits
            INC CX       ;CX++
            ;else continue
            CMP AX, 0
            JE END_PUSH_WHILE
            JMP PUSH_WHILE
        END_PUSH_WHILE:
        MOV AH, 2
        POP_WHILE:
            POP DX      ;Division by 10 will have a remaainder less than 8 bits
            ADD DL, '0'
            ;if(CX <= 0) then end loop
            INT 21H     ;So DL will have the desired character
            DEC CX       ;CX--
            ;else continue
            CMP CX, 0
            JLE END_POP_WHILE
        ;Print newline
            JMP POP_WHILE
        END_POP_WHILE:
        MOV DL, 0DH
        INT 21H
        MOV DL, 0AH
        INT 21H
        POP BP          ; Restore BP
        RET 2
    PRINT_INTEGER ENDP
	main PROC
		MOV AX, @DATA
		MOV DS, AX
		PUSH BX    ;line no 2: a declared
		PUSH BX    ;line no 2: b declared
		PUSH BX    ;line no 2: c declared
		PUSH BX    ;line no 2: i declared
;		PUSH 0
;		POP AX	;0 popped
		PUSH [BP+-4]	; b pushed
		MOV AX, 0
		MOV [BP+-4], AX	;assigned 0 to b
		POP AX	;Popped out b=0
;		PUSH 1
;		POP AX	;1 popped
		PUSH [BP+-6]	; c pushed
		MOV AX, 1
		MOV [BP+-6], AX	;assigned 1 to c
		POP AX	;Popped out c=1
;		PUSH 0
;		POP AX	;0 popped
		PUSH [BP+-8]	; i pushed
		MOV AX, 0
		;line no 5: evaluating for loop
		MOV [BP+-8], AX	;assigned 0 to i
		POP AX	;Popped out i=0
		L_1:	;For loop start label
		;Checking if i<4
;		PUSH 4
;		POP BX	;popped out 4
		PUSH [BP+-8]	; i pushed
		MOV BX, 4
		POP AX	;popped out i
		CMP AX, BX	;comparing i and 4
		JL L_2
		PUSH 0	;false
		JMP L_3
		L_2:
		PUSH 1	;true
		L_3:
		POP AX	;Popped out i<4
		CMP AX, 0	;compare with 0 to see if the expression is false
		JNE L_5
		JMP L_4	;if false jump to end of for loop
		L_5:
;		PUSH 3
;		POP AX	;3 popped
		PUSH [BP+-2]	; a pushed
		MOV AX, 3
		MOV [BP+-2], AX	;assigned 3 to a
		POP AX	;Popped out a=3
		;line no 7: postfix decrement of a
;		PUSH [BP+-2]	; a pushed
;		POP AX	;setting AX to the value of a
		L_6:	;while loop start label
		MOV AX, [BP+-2]
		PUSH AX	;pushing the value of a back to stack
		DEC AX	;decrementing a
		MOV [BP+-2], AX	;saving the decremented value of a
		POP AX	;popped a--
		CMP AX, 0	;compare with 0 to see if the expression is false
		JNE L_8
		JMP L_7	;if false jump to end of while loop
		;line no 8: postfix increment of b
;		PUSH [BP+-4]	; b pushed
;		POP AX	;setting AX to the value of b
		L_8:
		MOV AX, [BP+-4]
		PUSH AX	;pushing the value of b back to stack
		INC AX	;incrementing b
		MOV [BP+-4], AX	;saving the incremented value of b
		POP AX	;Popped out b++
		JMP L_6
		;line no 5: postfix increment of i
;		PUSH [BP+-8]	; i pushed
;		POP AX	;setting AX to the value of i
		L_7:	;while loop end label
		MOV AX, [BP+-8]
		PUSH AX	;pushing the value of i back to stack
		INC AX	;incrementing i
		MOV [BP+-8], AX	;saving the incremented value of i
		POP AX	;popped i++
		JMP L_1	;jump back to for loop
		L_4:
		PUSH [BP+-2]	;passing a to PRINT_INTEGER
		CALL PRINT_INTEGER
		PUSH [BP+-4]	;passing b to PRINT_INTEGER
		CALL PRINT_INTEGER
		PUSH [BP+-6]	;passing c to PRINT_INTEGER
		CALL PRINT_INTEGER
		MOV AH, 4CH
		INT 21H
	main ENDP
END MAIN
