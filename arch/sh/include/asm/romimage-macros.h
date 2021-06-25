<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ROMIMAGE_MACRO_H
#घोषणा __ROMIMAGE_MACRO_H

/* The LIST command is used to include comments in the script */
.macro	LIST comment
.endm

/* The ED command is used to ग_लिखो a 32-bit word */
.macro  ED, addr, data
	mov.l 1f, r1
	mov.l 2f, r0
	mov.l r0, @r1
	bra 3f
	 nop
	.align 2
1 :	.दीर्घ \चddr
2 :	.दीर्घ \data
3 :
.endm

/* The EW command is used to ग_लिखो a 16-bit word */
.macro  EW, addr, data
	mov.l 1f, r1
	mov.l 2f, r0
	mov.w r0, @r1
	bra 3f
	 nop
	.align 2
1 :	.दीर्घ \चddr
2 :	.दीर्घ \data
3 :
.endm

/* The EB command is used to ग_लिखो an 8-bit word */
.macro  EB, addr, data
	mov.l 1f, r1
	mov.l 2f, r0
	mov.b r0, @r1
	bra 3f
	 nop
	.align 2
1 :	.दीर्घ \चddr
2 :	.दीर्घ \data
3 :
.endm

/* The WAIT command is used to delay the execution */
.macro  WAIT, समय
	mov.l  2f, r3
1 :
	nop
	tst     r3, r3
	bf/s    1b
	dt      r3
	bra	3f
	 nop
	.align 2
2 :	.दीर्घ \टime * 100
3 :
.endm

/* The DD command is used to पढ़ो a 32-bit word */
.macro  DD, addr, addr2, nr
	mov.l 1f, r1
	mov.l @r1, r0
	bra 2f
	 nop
	.align 2
1 :	.दीर्घ \चddr
2 :
.endm

#पूर्ण_अगर /* __ROMIMAGE_MACRO_H */
