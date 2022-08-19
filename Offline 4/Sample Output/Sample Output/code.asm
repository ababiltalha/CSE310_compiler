.MODEL SMALL
.STACK 400H
.DATA
.CODE
	;println(n)
	PRINT_INTEGER PROC NEAR
        PUSH BP             ;Saving BP
        MOV BP, SP          ;BP points to the top of the stack
        MOV BX, [BP+4]    ;The number to be printed
        ;if(BX < -1) then the number is positive
        CMP BX, 0
        JGE POSITIVE
        ;else, the number is negative
        MOV AH, 2           
        MOV DL, '-'         ;Print a '-' sign
        INT 21H
        NEG BX              ;make BX positive
        POSITIVE:
        MOV AX, BX
        MOV CX, 0        ;Initialize character count
        PUSH_WHILE:
            XOR DX, DX  ;clear DX
            MOV BX, 10  ;BX has the divisor //// AX has the dividend
            DIV BX
            ;quotient is in AX and remainder is in DX
            PUSH DX     ;Division by 10 will have a remainder less than 8 bits
            INC CX       ;CX++
            ;if(AX == 0) then break the loop
            CMP AX, 0
            JE END_PUSH_WHILE
            ;else continue
            JMP PUSH_WHILE
        END_PUSH_WHILE:
        MOV AH, 2
        POP_WHILE:
            POP DX      ;Division by 10 will have a remaainder less than 8 bits
            ADD DL, '0'
            INT 21H     ;So DL will have the desired character
            DEC CX       ;CX--
            ;if(CX <= 0) then end loop
            CMP CX, 0
            JLE END_POP_WHILE
            ;else continue
            JMP POP_WHILE
        END_POP_WHILE:
        ;Print newline
        MOV DL, 0DH
        INT 21H
        MOV DL, 0AH
        INT 21H
        POP BP          ; Restore BP
        RET 2
    PRINT_INTEGER ENDP
	f PROC
		;entering function: f
		PUSH BP	;saving BP
		MOV BP, SP	;BP = SP (all the offsets in this function are based on this value of BP)

		PUSH BX    ;line no 2: w declared
		PUSH [BP+-2]	; w pushed
		PUSH 2
		PUSH [BP+4]	; a pushed
		;Multiplication of 2 and a
		POP BX	;a popped
		POP AX	;2 popped
		IMUL BX	;AX = 2 * a
		PUSH AX	;pushed 2*a

		POP AX	;2*a popped
		MOV [BP+-2], AX	;assigned 2*a to w
		POP AX	;Popped out w=2*a
		PUSH [BP+-2]	; w pushed
		POP AX	;saving returned value in AX
		MOV SP, BP	;Restoring SP at the end of function
		POP BP	;restoring BP at the end of function
		RET 2
		PUSH [BP+4]	; a pushed
		PUSH 9
		POP AX	;9 popped
		MOV [BP+4], AX	;assigned 9 to a
		POP AX	;Popped out a=9
	f ENDP
	g PROC
		;entering function: g
		PUSH BP	;saving BP
		MOV BP, SP	;BP = SP (all the offsets in this function are based on this value of BP)

		PUSH BX    ;line no 9: x declared
		PUSH [BP+-2]	; x pushed
		PUSH [BP+6]	; a pushed
		CALL f
		PUSH AX	;pushed return value of f
		PUSH [BP+6]	; a pushed
		;line no 10: ADD f(a) and a
		POP BX	;a popped
		POP AX	;f(a) popped
		ADD AX, BX
		PUSH AX	;pushed f(a)+a

		PUSH [BP+4]	; b pushed
		;line no 10: ADD f(a)+a and b
		POP BX	;b popped
		POP AX	;f(a)+a popped
		ADD AX, BX
		PUSH AX	;pushed f(a)+a+b

		POP AX	;f(a)+a+b popped
		MOV [BP+-2], AX	;assigned f(a)+a+b to x
		POP AX	;Popped out x=f(a)+a+b
		PUSH [BP+-2]	; x pushed
		POP AX	;saving returned value in AX
		MOV SP, BP	;Restoring SP at the end of function
		POP BP	;restoring BP at the end of function
		RET 4
	g ENDP
	main PROC
		MOV AX, @DATA
		MOV DS, AX
		PUSH BX    ;line no 15: a declared
		PUSH BX    ;line no 15: b declared
		PUSH [BP+-2]	; a pushed
		PUSH 1
		POP AX	;1 popped
		MOV [BP+-2], AX	;assigned 1 to a
		POP AX	;Popped out a=1
		PUSH [BP+-4]	; b pushed
		PUSH 2
		POP AX	;2 popped
		MOV [BP+-4], AX	;assigned 2 to b
		POP AX	;Popped out b=2
		PUSH [BP+-2]	; a pushed
		PUSH [BP+-2]	; a pushed
		PUSH [BP+-4]	; b pushed
		CALL g
		PUSH AX	;pushed return value of g
		POP AX	;g(a,b) popped
		MOV [BP+-2], AX	;assigned g(a,b) to a
		POP AX	;Popped out a=g(a,b)

		PUSH [BP+-2]	;passing a to PRINT_INTEGER
		CALL PRINT_INTEGER

		PUSH 0
		MOV AH, 4CH
		INT 21H
		MOV AH, 4CH
		INT 21H
	main ENDP
END MAIN
