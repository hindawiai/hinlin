<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Derived from IRIX <sys/SN/nmi.h>, Revision 1.5.
 *
 * Copyright (C) 1992 - 1997 Silicon Graphics, Inc.
 */
#अगर_अघोषित __ASM_SN_NMI_H
#घोषणा __ASM_SN_NMI_H

#समावेश <यंत्र/sn/addrs.h>

/*
 * The launch data काष्ठाure resides at a fixed place in each node's memory
 * and is used to communicate between the master processor and the slave
 * processors.
 *
 * The master stores launch parameters in the launch काष्ठाure
 * corresponding to a target processor that is in a slave loop, then sends
 * an पूर्णांकerrupt to the slave processor.	 The slave calls the desired
 * function, followed by an optional rendezvous function, then वापसs to
 * the slave loop.  The master करोes not रुको क्रम the slaves beक्रमe
 * वापसing.
 *
 * There is an array of launch काष्ठाures, one per CPU on the node.  One
 * पूर्णांकerrupt level is used per CPU.
 */

#घोषणा NMI_MAGIC		0x48414d4d455201
#घोषणा NMI_SIZखातापूर्ण		0x40

#घोषणा NMI_OFF_MAGIC		0x00	/* Struct offsets क्रम assembly	    */
#घोषणा NMI_OFF_FLAGS		0x08
#घोषणा NMI_OFF_CALL		0x10
#घोषणा NMI_OFF_CALLC		0x18
#घोषणा NMI_OFF_CALLPARM	0x20
#घोषणा NMI_OFF_GMASTER		0x28

/*
 * The NMI routine is called only अगर the complement address is
 * correct.
 *
 * Beक्रमe control is transferred to a routine, the complement address
 * is zeroed (invalidated) to prevent an accidental call from a spurious
 * पूर्णांकerrupt.
 *
 */

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा nmi_s अणु
	अस्थिर अचिन्हित दीर्घ	 magic;		/* Magic number */
	अस्थिर अचिन्हित दीर्घ	 flags;		/* Combination of flags above */
	अस्थिर व्योम *call_addr;	/* Routine क्रम slave to call	    */
	अस्थिर व्योम *call_addr_c;	/* 1's complement of address	    */
	अस्थिर व्योम *call_parm;	/* Single parm passed to call	    */
	अस्थिर अचिन्हित दीर्घ	 gmaster;	/* Flag true only on global master*/
पूर्ण nmi_t;

#पूर्ण_अगर /* !__ASSEMBLY__ */

/* Following definitions are needed both in the prom & the kernel
 * to identअगरy the क्रमmat of the nmi cpu रेजिस्टर save area in the
 * low memory on each node.
 */
#अगर_अघोषित __ASSEMBLY__

काष्ठा reg_काष्ठा अणु
	अचिन्हित दीर्घ	gpr[32];
	अचिन्हित दीर्घ	sr;
	अचिन्हित दीर्घ	cause;
	अचिन्हित दीर्घ	epc;
	अचिन्हित दीर्घ	badva;
	अचिन्हित दीर्घ	error_epc;
	अचिन्हित दीर्घ	cache_err;
	अचिन्हित दीर्घ	nmi_sr;
पूर्ण;

#पूर्ण_अगर /* !__ASSEMBLY__ */

/* These are the assembly language offsets पूर्णांकo the reg_काष्ठा काष्ठाure */

#घोषणा R0_OFF		0x0
#घोषणा R1_OFF		0x8
#घोषणा R2_OFF		0x10
#घोषणा R3_OFF		0x18
#घोषणा R4_OFF		0x20
#घोषणा R5_OFF		0x28
#घोषणा R6_OFF		0x30
#घोषणा R7_OFF		0x38
#घोषणा R8_OFF		0x40
#घोषणा R9_OFF		0x48
#घोषणा R10_OFF		0x50
#घोषणा R11_OFF		0x58
#घोषणा R12_OFF		0x60
#घोषणा R13_OFF		0x68
#घोषणा R14_OFF		0x70
#घोषणा R15_OFF		0x78
#घोषणा R16_OFF		0x80
#घोषणा R17_OFF		0x88
#घोषणा R18_OFF		0x90
#घोषणा R19_OFF		0x98
#घोषणा R20_OFF		0xa0
#घोषणा R21_OFF		0xa8
#घोषणा R22_OFF		0xb0
#घोषणा R23_OFF		0xb8
#घोषणा R24_OFF		0xc0
#घोषणा R25_OFF		0xc8
#घोषणा R26_OFF		0xd0
#घोषणा R27_OFF		0xd8
#घोषणा R28_OFF		0xe0
#घोषणा R29_OFF		0xe8
#घोषणा R30_OFF		0xf0
#घोषणा R31_OFF		0xf8
#घोषणा SR_OFF		0x100
#घोषणा CAUSE_OFF	0x108
#घोषणा EPC_OFF		0x110
#घोषणा BADVA_OFF	0x118
#घोषणा ERROR_EPC_OFF	0x120
#घोषणा CACHE_ERR_OFF	0x128
#घोषणा NMISR_OFF	0x130

#पूर्ण_अगर /* __ASM_SN_NMI_H */
