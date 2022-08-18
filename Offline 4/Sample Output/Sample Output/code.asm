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
	main PROC
		MOV AX, @DATA
		MOV DS, AX
		PUSH BX    ;line no 2: a declared
		PUSH BX    ;line no 2: b declared
		MOV SP, [BP+-10]	;array c[3] declared
		PUSH [BP+-2]	; a pushed
		PUSH 1
		PUSH 2
		PUSH 3
		;line no 3: ADD 2 and 3
		POP BX	;3 popped
		POP AX	;2 popped
		ADD AX, BX
		PUSH AX	;pushed 2+3

		;Multiplication of 1 and (2+3)
		POP BX	;(2+3) popped
		POP AX	;1 popped
		IMUL BX	;AX = 1 * (2+3)
		PUSH AX	;pushed 1*(2+3)

		PUSH 3
		;Modulus of 1*(2+3) and 3
		POP BX	;3 popped
		POP AX	;1*(2+3) popped
		XOR DX, DX	;resetting DX to 0
		IDIV BX	;1*(2+3)/3
		MOV AX, DX	;AX = 1*(2+3)%3
		PUSH AX	;pushed 1*(2+3)%3

		POP AX	;1*(2+3)%3 popped
		MOV [BP+-2], AX	;assigned 1*(2+3)%3 to a
		POP AX	;Popped out a=1*(2+3)%3
		PUSH [BP+-4]	; b pushed
		PUSH 1
		PUSH 5
		;Checking if 1<5
		POP BX	;popped out 5
		POP AX	;popped out 1
		CMP AX, BX	;comparing 1 and 5
		JL L_1
		PUSH 0	;false
		JMP L_2
		L_1:
		PUSH 1	;true
		L_2:

		POP AX	;1<5 popped
		MOV [BP+-4], AX	;assigned 1<5 to b
		POP AX	;Popped out b=1<5
		PUSH 1
		;line no 5: getting the value of c[1]
		POP BX	;saving the index of the array in BX
		SHL BX, 1	;multiplying index by 2 to match the size of word
		NEG BX	;offset is negative
		ADD BX, -6	;adding the offset of the array to get the offset of array element
		ADD BX, BP	;adding BP to BX to get the address of the array
		MOV AX, [BX]	;getting the value of the array at index BX
		PUSH AX	;pushing the value of the array element at index 1
		PUSH BX	;pushing the index of the array
		PUSH 2
		POP AX	;2 popped
		POP BX	;index of the array element popped
		MOV [BX], AX	;assigning the value of 2 to c[BX]

		POP AX	;Popped out c=2
		PUSH [BP+-2]	; a pushed
		PUSH [BP+-4]	; b pushed
		;line no 6: a&&b
		POP BX	; b popped
		POP AX	; a popped
		CMP AX, 0	; comparing a and 0
		JNE L_3	; if a is not 0, check b. So, jump to L_3
		PUSH 0	; a is 0, the whole expression is 0. So, set the value to 0
		JMP L_5
		L_3:
		CMP BX, 0	; comparing b and 0
		JNE L_4	; if b is not 0, the whole expression is true. So, jump to L_4
		PUSH 0	; a and b are false. So, set the value to 0
		JMP L_5
		L_4:
		PUSH 1	; a and b are true. So, set the value to 1
		L_5:

		;line no 6: evaluating if block
		POP AX	;popped expression value
		CMP AX, 0	;compare with 0 to see if the expression is false
		JNE L_7
		JMP L_6	;if false jump to end of if block
		L_7:

		PUSH 1
		;line no 7: getting the value of c[1]
		POP BX	;saving the index of the array in BX
		SHL BX, 1	;multiplying index by 2 to match the size of word
		NEG BX	;offset is negative
		ADD BX, -6	;adding the offset of the array to get the offset of array element
		ADD BX, BP	;adding BP to BX to get the address of the array
		MOV AX, [BX]	;getting the value of the array at index BX
		PUSH AX	;pushing the value of the array element at index 1
		PUSH BX	;pushing the index of the array
		;line no 7: postfix increment of c
		POP BX	;popped array index address
		MOV AX, [BX]	;setting AX to the value of c
		INC AX	;incrementing c
		MOV [BX], AX	;saving the incremented value of c

		POP AX	;Popped out c++
		JMP L_8
		L_6:
		PUSH 0
		;line no 9: getting the value of c[0]
		POP BX	;saving the index of the array in BX
		SHL BX, 1	;multiplying index by 2 to match the size of word
		NEG BX	;offset is negative
		ADD BX, -6	;adding the offset of the array to get the offset of array element
		ADD BX, BP	;adding BP to BX to get the address of the array
		MOV AX, [BX]	;getting the value of the array at index BX
		PUSH AX	;pushing the value of the array element at index 0
		PUSH BX	;pushing the index of the array
		PUSH 1
		;line no 9: getting the value of c[1]
		POP BX	;saving the index of the array in BX
		SHL BX, 1	;multiplying index by 2 to match the size of word
		NEG BX	;offset is negative
		ADD BX, -6	;adding the offset of the array to get the offset of array element
		ADD BX, BP	;adding BP to BX to get the address of the array
		MOV AX, [BX]	;getting the value of the array at index BX
		PUSH AX	;pushing the value of the array element at index 1
		PUSH BX	;pushing the index of the array
		POP BX	;array index popped because it is no longer required
		POP AX	;c popped
		POP BX	;index of the array element popped
		MOV [BX], AX	;assigning the value of c to c[BX]

		POP AX	;Popped out c=c
		L_8:


		PUSH [BP+-2]	;passing a to PRINT_INTEGER
		CALL PRINT_INTEGER


		PUSH [BP+-4]	;passing b to PRINT_INTEGER
		CALL PRINT_INTEGER

		MOV AH, 4CH
		INT 21H
	main ENDP
END MAIN
