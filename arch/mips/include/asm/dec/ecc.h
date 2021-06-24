<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	include/यंत्र-mips/dec/ecc.h
 *
 *	ECC handling logic definitions common to DECstation/DECप्रणाली
 *	5000/200 (KN02), 5000/240 (KN03), 5000/260 (KN05) and
 *	DECप्रणाली 5900 (KN03), 5900/260 (KN05) प्रणालीs.
 *
 *	Copyright (C) 2003  Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_MIPS_DEC_ECC_H
#घोषणा __ASM_MIPS_DEC_ECC_H

/*
 * Error Address Register bits.
 * The रेजिस्टर is r/wc -- any ग_लिखो clears it.
 */
#घोषणा KN0X_EAR_VALID		(1<<31)		/* error data valid, bus IRQ */
#घोषणा KN0X_EAR_CPU		(1<<30)		/* CPU/DMA transaction */
#घोषणा KN0X_EAR_WRITE		(1<<29)		/* ग_लिखो/पढ़ो transaction */
#घोषणा KN0X_EAR_ECCERR		(1<<28)		/* ECC/समयout or overrun */
#घोषणा KN0X_EAR_RES_27		(1<<27)		/* unused */
#घोषणा KN0X_EAR_ADDRESS	(0x7ffffff<<0)	/* address involved */

/*
 * Error Syndrome Register bits.
 * The रेजिस्टर is frozen when EAR.VALID is set, otherwise it records bits
 * from the last memory पढ़ो.  The रेजिस्टर is r/wc -- any ग_लिखो clears it.
 */
#घोषणा KN0X_ESR_VLDHI		(1<<31)		/* error data valid hi word */
#घोषणा KN0X_ESR_CHKHI		(0x7f<<24)	/* check bits पढ़ो from mem */
#घोषणा KN0X_ESR_SNGHI		(1<<23)		/* single/द्विगुन bit error */
#घोषणा KN0X_ESR_SYNHI		(0x7f<<16)	/* syndrome from ECC logic */
#घोषणा KN0X_ESR_VLDLO		(1<<15)		/* error data valid lo word */
#घोषणा KN0X_ESR_CHKLO		(0x7f<<8)	/* check bits पढ़ो from mem */
#घोषणा KN0X_ESR_SNGLO		(1<<7)		/* single/द्विगुन bit error */
#घोषणा KN0X_ESR_SYNLO		(0x7f<<0)	/* syndrome from ECC logic */


#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा pt_regs;

बाह्य व्योम dec_ecc_be_init(व्योम);
बाह्य पूर्णांक dec_ecc_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup);
बाह्य irqवापस_t dec_ecc_be_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MIPS_DEC_ECC_H */
