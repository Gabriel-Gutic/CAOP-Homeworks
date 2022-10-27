.model FLAT, C
.code

; extern "C" int RectCheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int* result);

; x1 -> ebp + 8
; y1 -> ebp + 12
; w1 -> ebp + 16
; h1 -> ebp + 20
; x2 -> ebp + 24
; y2 -> ebp + 28
; w2 -> ebp + 32
; h2 -> ebp + 36
; result -> ebp + 40

RectCheck PROC
	push ebp
	mov ebp, esp

	mov eax, [ebp + 8]
	mov ecx, [ebp + 24]
	cmp eax, ecx
	je WRONG
	jg FIRST_X_BIGGER
	jmp SECOND_X_BIGGER

FIRST_X_BIGGER:
	mov eax, [ebp + 12]
	mov ecx, [ebp + 28]
	cmp eax, ecx
	je WRONG
	jg FIRST_Y_BIGGER
	jmp WRONG

FIRST_Y_BIGGER:
	mov eax, [ebp + 8]
	add eax, [ebp + 16]
	mov ecx, eax

	mov eax, [ebp + 24]
	add eax, [ebp + 32]
	mov edx, eax

	cmp ecx, edx
	jb FIRST_WIDTH_SMALLER
	jmp WRONG

FIRST_WIDTH_SMALLER:
	mov eax, [ebp + 12]
	add eax, [ebp + 20]
	mov ecx, eax

	mov eax, [ebp + 28]
	add eax, [ebp + 36]
	mov edx, eax

	cmp ecx, edx
	jb FIRST_INSIDE_SECOND
	jmp WRONG

FIRST_INSIDE_SECOND:
	mov ecx, [ebp + 40]
	mov DWORD PTR [ecx], 1
	jmp GOOD

SECOND_X_BIGGER:
	mov eax, [ebp + 12]
	mov ecx, [ebp + 28]
	cmp eax, ecx
	je WRONG
	jb SECOND_Y_BIGGER
	jmp WRONG

SECOND_Y_BIGGER:
	mov eax, [ebp + 8]
	add eax, [ebp + 16]
	mov ecx, eax

	mov eax, [ebp + 24]
	add eax, [ebp + 32]
	mov edx, eax

	cmp ecx, edx
	jg SECOND_WIDTH_SMALLER
	jmp WRONG

SECOND_WIDTH_SMALLER:
	mov eax, [ebp + 12]
	add eax, [ebp + 20]
	mov ecx, eax

	mov eax, [ebp + 28]
	add eax, [ebp + 36]
	mov edx, eax

	cmp ecx, edx
	jg SECOND_INSIDE_FIRST
	jmp WRONG

SECOND_INSIDE_FIRST:
	mov ecx, [ebp + 40]
	mov DWORD PTR [ecx], 2
	jmp GOOD
WRONG:
	mov ecx, [ebp + 40]
	mov DWORD PTR [ecx], 0
GOOD:

	pop ebp
	ret
RectCheck ENDP

end