<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _PPC64_PPC_ASM_H
#घोषणा _PPC64_PPC_ASM_H
/*
 *
 * Definitions used by various bits of low-level assembly code on PowerPC.
 *
 * Copyright (C) 1995-1999 Gary Thomas, Paul Mackerras, Cort Dougan.
 */

/* Condition Register Bit Fields */

#घोषणा	cr0	0
#घोषणा	cr1	1
#घोषणा	cr2	2
#घोषणा	cr3	3
#घोषणा	cr4	4
#घोषणा	cr5	5
#घोषणा	cr6	6
#घोषणा	cr7	7


/* General Purpose Registers (GPRs) */

#घोषणा	r0	0
#घोषणा	r1	1
#घोषणा	r2	2
#घोषणा	r3	3
#घोषणा	r4	4
#घोषणा	r5	5
#घोषणा	r6	6
#घोषणा	r7	7
#घोषणा	r8	8
#घोषणा	r9	9
#घोषणा	r10	10
#घोषणा	r11	11
#घोषणा	r12	12
#घोषणा	r13	13
#घोषणा	r14	14
#घोषणा	r15	15
#घोषणा	r16	16
#घोषणा	r17	17
#घोषणा	r18	18
#घोषणा	r19	19
#घोषणा	r20	20
#घोषणा	r21	21
#घोषणा	r22	22
#घोषणा	r23	23
#घोषणा	r24	24
#घोषणा	r25	25
#घोषणा	r26	26
#घोषणा	r27	27
#घोषणा	r28	28
#घोषणा	r29	29
#घोषणा	r30	30
#घोषणा	r31	31

#घोषणा SPRN_TBRL	268
#घोषणा SPRN_TBRU	269
#घोषणा SPRN_HSRR0	0x13A	/* Hypervisor Save/Restore 0 */
#घोषणा SPRN_HSRR1	0x13B	/* Hypervisor Save/Restore 1 */

#घोषणा MSR_LE		0x0000000000000001

#घोषणा FIXUP_ENDIAN						   \
	tdi   0,0,0x48;	  /* Reverse endian of b . + 8		*/ \
	b     $+44;	  /* Skip trampoline अगर endian is good	*/ \
	.दीर्घ 0xa600607d; /* mfmsr r11				*/ \
	.दीर्घ 0x01006b69; /* xori r11,r11,1			*/ \
	.दीर्घ 0x00004039; /* li r10,0				*/ \
	.दीर्घ 0x6401417d; /* mपंचांगsrd r10,1			*/ \
	.दीर्घ 0x05009f42; /* bcl 20,31,$+4			*/ \
	.दीर्घ 0xa602487d; /* mflr r10				*/ \
	.दीर्घ 0x14004a39; /* addi r10,r10,20			*/ \
	.दीर्घ 0xa6035a7d; /* mtsrr0 r10				*/ \
	.दीर्घ 0xa6037b7d; /* mtsrr1 r11				*/ \
	.दीर्घ 0x2400004c  /* rfid				*/

#अगर_घोषित CONFIG_PPC_8xx
#घोषणा MFTBL(dest)			mftb dest
#घोषणा MFTBU(dest)			mftbu dest
#अन्यथा
#घोषणा MFTBL(dest)			mfspr dest, SPRN_TBRL
#घोषणा MFTBU(dest)			mfspr dest, SPRN_TBRU
#पूर्ण_अगर

#पूर्ण_अगर /* _PPC64_PPC_ASM_H */
