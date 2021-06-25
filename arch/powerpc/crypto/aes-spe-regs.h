<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Common रेजिस्टरs क्रम PPC AES implementation
 *
 * Copyright (c) 2015 Markus Stockhausen <stockhausen@collogia.de>
 */

#घोषणा rKS r0	/* copy of en-/decryption key poपूर्णांकer			*/
#घोषणा rDP r3	/* destination poपूर्णांकer					*/
#घोषणा rSP r4	/* source poपूर्णांकer					*/
#घोषणा rKP r5	/* poपूर्णांकer to en-/decryption key poपूर्णांकer		*/
#घोषणा rRR r6	/* en-/decryption rounds				*/
#घोषणा rLN r7	/* length of data to be processed			*/
#घोषणा rIP r8	/* potiner to IV (CBC/CTR/XTS modes)			*/
#घोषणा rKT r9	/* poपूर्णांकer to tweak key (XTS mode)			*/
#घोषणा rT0 r11	/* poपूर्णांकers to en-/decryption tables			*/
#घोषणा rT1 r10
#घोषणा rD0 r9	/* data 						*/
#घोषणा rD1 r14
#घोषणा rD2 r12
#घोषणा rD3 r15
#घोषणा rW0 r16	/* working रेजिस्टरs					*/
#घोषणा rW1 r17
#घोषणा rW2 r18
#घोषणा rW3 r19
#घोषणा rW4 r20
#घोषणा rW5 r21
#घोषणा rW6 r22
#घोषणा rW7 r23
#घोषणा rI0 r24	/* IV							*/
#घोषणा rI1 r25
#घोषणा rI2 r26
#घोषणा rI3 r27
#घोषणा rG0 r28	/* endian reversed tweak (XTS mode)			*/
#घोषणा rG1 r29
#घोषणा rG2 r30
#घोषणा rG3 r31
