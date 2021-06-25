<शैली गुरु>
/*
 * Inकाष्ठाion क्रमmats क्रम the sequencer program करोwnloaded to
 * Aic7xxx SCSI host adapters
 *
 * Copyright (c) 1997, 1998, 2000 Justin T. Gibbs.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aicयंत्र/aicयंत्र_insक्रमmat.h#12 $
 *
 * $FreeBSD$
 */

#समावेश <यंत्र/byteorder.h>

/* 8bit ALU logic operations */
काष्ठा ins_क्रमmat1 अणु
#अगर_घोषित __LITTLE_ENDIAN
	uपूर्णांक32_t	immediate	: 8,
			source		: 9,
			destination	: 9,
			ret		: 1,
			opcode		: 4,
			parity		: 1;
#अन्यथा
	uपूर्णांक32_t	parity		: 1,
			opcode		: 4,
			ret		: 1,
			destination	: 9,
			source		: 9,
			immediate	: 8;
#पूर्ण_अगर
पूर्ण;

/* 8bit ALU shअगरt/rotate operations */
काष्ठा ins_क्रमmat2 अणु
#अगर_घोषित __LITTLE_ENDIAN
	uपूर्णांक32_t	shअगरt_control	: 8,
			source		: 9,
			destination	: 9,
			ret		: 1,
			opcode		: 4,
			parity		: 1;
#अन्यथा
	uपूर्णांक32_t	parity		: 1,
			opcode		: 4,
			ret		: 1,
			destination	: 9,
			source		: 9,
			shअगरt_control	: 8;
#पूर्ण_अगर
पूर्ण;

/* 8bit branch control operations */
काष्ठा ins_क्रमmat3 अणु
#अगर_घोषित __LITTLE_ENDIAN
	uपूर्णांक32_t	immediate	: 8,
			source		: 9,
			address		: 10,
			opcode		: 4,
			parity		: 1;
#अन्यथा
	uपूर्णांक32_t	parity		: 1,
			opcode		: 4,
			address		: 10,
			source		: 9,
			immediate	: 8;
#पूर्ण_अगर
पूर्ण;

/* 16bit ALU logic operations */
काष्ठा ins_क्रमmat4 अणु
#अगर_घोषित __LITTLE_ENDIAN
	uपूर्णांक32_t	opcode_ext	: 8,
			source		: 9,
			destination	: 9,
			ret		: 1,
			opcode		: 4,
			parity		: 1;
#अन्यथा
	uपूर्णांक32_t	parity		: 1,
			opcode		: 4,
			ret		: 1,
			destination	: 9,
			source		: 9,
			opcode_ext	: 8;
#पूर्ण_अगर
पूर्ण;

/* 16bit branch control operations */
काष्ठा ins_क्रमmat5 अणु
#अगर_घोषित __LITTLE_ENDIAN
	uपूर्णांक32_t	opcode_ext	: 8,
			source		: 9,
			address		: 10,
			opcode		: 4,
			parity		: 1;
#अन्यथा
	uपूर्णांक32_t	parity		: 1,
			opcode		: 4,
			address		: 10,
			source		: 9,
			opcode_ext	: 8;
#पूर्ण_अगर
पूर्ण;

/*  Far branch operations */
काष्ठा ins_क्रमmat6 अणु
#अगर_घोषित __LITTLE_ENDIAN
	uपूर्णांक32_t	page		: 3,
			opcode_ext	: 5,
			source		: 9,
			address		: 10,
			opcode		: 4,
			parity		: 1;
#अन्यथा
	uपूर्णांक32_t	parity		: 1,
			opcode		: 4,
			address		: 10,
			source		: 9,
			opcode_ext	: 5,
			page		: 3;
#पूर्ण_अगर
पूर्ण;

जोड़ ins_क्रमmats अणु
		काष्ठा ins_क्रमmat1 क्रमmat1;
		काष्ठा ins_क्रमmat2 क्रमmat2;
		काष्ठा ins_क्रमmat3 क्रमmat3;
		काष्ठा ins_क्रमmat4 क्रमmat4;
		काष्ठा ins_क्रमmat5 क्रमmat5;
		काष्ठा ins_क्रमmat6 क्रमmat6;
		uपूर्णांक8_t		   bytes[4];
		uपूर्णांक32_t	   पूर्णांकeger;
पूर्ण;
काष्ठा inकाष्ठाion अणु
	जोड़	ins_क्रमmats क्रमmat;
	u_पूर्णांक	srcline;
	काष्ठा symbol *patch_label;
	STAILQ_ENTRY(inकाष्ठाion) links;
पूर्ण;

#घोषणा	AIC_OP_OR	0x0
#घोषणा	AIC_OP_AND	0x1
#घोषणा AIC_OP_XOR	0x2
#घोषणा	AIC_OP_ADD	0x3
#घोषणा	AIC_OP_ADC	0x4
#घोषणा	AIC_OP_ROL	0x5
#घोषणा	AIC_OP_BMOV	0x6

#घोषणा	AIC_OP_MVI16	0x7

#घोषणा	AIC_OP_JMP	0x8
#घोषणा AIC_OP_JC	0x9
#घोषणा AIC_OP_JNC	0xa
#घोषणा AIC_OP_CALL	0xb
#घोषणा	AIC_OP_JNE	0xc
#घोषणा	AIC_OP_JNZ	0xd
#घोषणा	AIC_OP_JE	0xe
#घोषणा	AIC_OP_JZ	0xf

/* Pseuकरो Ops */
#घोषणा	AIC_OP_SHL	0x10
#घोषणा	AIC_OP_SHR	0x20
#घोषणा	AIC_OP_ROR	0x30

/* 16bit Ops. Low byte मुख्य opcode.  High byte extended opcode. */ 
#घोषणा	AIC_OP_OR16	0x8005
#घोषणा	AIC_OP_AND16	0x8105
#घोषणा	AIC_OP_XOR16	0x8205
#घोषणा	AIC_OP_ADD16	0x8305
#घोषणा	AIC_OP_ADC16	0x8405
#घोषणा AIC_OP_JNE16	0x8805
#घोषणा AIC_OP_JNZ16	0x8905
#घोषणा AIC_OP_JE16	0x8C05
#घोषणा AIC_OP_JZ16	0x8B05
#घोषणा AIC_OP_JMP16	0x9005
#घोषणा AIC_OP_JC16	0x9105
#घोषणा AIC_OP_JNC16	0x9205
#घोषणा AIC_OP_CALL16	0x9305

/* Page extension is low three bits of second opcode byte. */
#घोषणा AIC_OP_JMPF	0xA005
#घोषणा AIC_OP_CALLF	0xB005
#घोषणा AIC_OP_JCF	0xC005
#घोषणा AIC_OP_JNCF	0xD005
#घोषणा AIC_OP_CMPXCHG	0xE005
