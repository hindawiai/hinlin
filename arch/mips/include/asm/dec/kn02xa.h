<शैली गुरु>
/*
 * Hardware info common to DECstation 5000/1xx प्रणालीs (otherwise
 * known as 3min or kn02ba) and Personal DECstations 5000/xx ones
 * (otherwise known as maxine or kn02ca).
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions
 * are by courtesy of Chris Fraser.
 * Copyright (C) 2000, 2002, 2003, 2005  Maciej W. Rozycki
 *
 * These are addresses which have to be known early in the boot process.
 * For other addresses refer to tc.h, ioasic_addrs.h and मित्रs.
 */
#अगर_अघोषित __ASM_MIPS_DEC_KN02XA_H
#घोषणा __ASM_MIPS_DEC_KN02XA_H

#समावेश <यंत्र/dec/ioasic_addrs.h>

#घोषणा KN02XA_SLOT_BASE	0x1c000000

/*
 * Memory control ASIC रेजिस्टरs.
 */
#घोषणा KN02XA_MER		0x0c400000	/* memory error रेजिस्टर */
#घोषणा KN02XA_MSR		0x0c800000	/* memory size रेजिस्टर */

/*
 * CPU control ASIC रेजिस्टरs.
 */
#घोषणा KN02XA_MEM_CONF		0x0e000000	/* ग_लिखो समयout config */
#घोषणा KN02XA_EAR		0x0e000004	/* error address रेजिस्टर */
#घोषणा KN02XA_BOOT0		0x0e000008	/* boot 0 रेजिस्टर */
#घोषणा KN02XA_MEM_INTR		0x0e00000c	/* ग_लिखो err IRQ stat & ack */

/*
 * Memory Error Register bits, common definitions.
 * The rest is defined in प्रणाली-specअगरic headers.
 */
#घोषणा KN02XA_MER_RES_28	(0xf<<28)	/* unused */
#घोषणा KN02XA_MER_RES_17	(0x3ff<<17)	/* unused */
#घोषणा KN02XA_MER_PAGERR	(1<<16)		/* 2k page boundary error */
#घोषणा KN02XA_MER_TRANSERR	(1<<15)		/* transfer length error */
#घोषणा KN02XA_MER_PARDIS	(1<<14)		/* parity error disable */
#घोषणा KN02XA_MER_SIZE		(1<<13)		/* r/o mirror of MSR_SIZE */
#घोषणा KN02XA_MER_RES_12	(1<<12)		/* unused */
#घोषणा KN02XA_MER_BYTERR	(0xf<<8)	/* byte lane error biपंचांगask: */
#घोषणा KN02XA_MER_BYTERR_3	(0x8<<8)	/* byte lane #3 */
#घोषणा KN02XA_MER_BYTERR_2	(0x4<<8)	/* byte lane #2 */
#घोषणा KN02XA_MER_BYTERR_1	(0x2<<8)	/* byte lane #1 */
#घोषणा KN02XA_MER_BYTERR_0	(0x1<<8)	/* byte lane #0 */
#घोषणा KN02XA_MER_RES_0	(0xff<<0)	/* unused */

/*
 * Memory Size Register bits, common definitions.
 * The rest is defined in प्रणाली-specअगरic headers.
 */
#घोषणा KN02XA_MSR_RES_27	(0x1f<<27)	/* unused */
#घोषणा KN02XA_MSR_RES_14	(0x7<<14)	/* unused */
#घोषणा KN02XA_MSR_SIZE		(1<<13)		/* 16M/4M stride */
#घोषणा KN02XA_MSR_RES_0	(0x1fff<<0)	/* unused */

/*
 * Error Address Register bits.
 */
#घोषणा KN02XA_EAR_RES_29	(0x7<<29)	/* unused */
#घोषणा KN02XA_EAR_ADDRESS	(0x7ffffff<<2)	/* address involved */
#घोषणा KN02XA_EAR_RES_0	(0x3<<0)	/* unused */


#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा pt_regs;

बाह्य व्योम dec_kn02xa_be_init(व्योम);
बाह्य पूर्णांक dec_kn02xa_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup);
बाह्य irqवापस_t dec_kn02xa_be_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MIPS_DEC_KN02XA_H */
