<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* ns87303.h: Configuration Register Description क्रम the
 *            National Semiconductor PC87303 (SuperIO).
 *
 * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 */

#अगर_अघोषित _SPARC_NS87303_H
#घोषणा _SPARC_NS87303_H 1

/*
 * Control Register Index Values
 */
#घोषणा FER	0x00
#घोषणा FAR	0x01
#घोषणा PTR	0x02
#घोषणा FCR	0x03
#घोषणा PCR	0x04
#घोषणा KRR	0x05
#घोषणा PMC	0x06
#घोषणा TUP	0x07
#घोषणा SID	0x08
#घोषणा ASC	0x09
#घोषणा CS0CF0	0x0a
#घोषणा CS0CF1	0x0b
#घोषणा CS1CF0	0x0c
#घोषणा CS1CF1	0x0d

/* Function Enable Register (FER) bits */
#घोषणा FER_EDM		0x10	/* Encoded Drive and Motor pin inक्रमmation   */

/* Function Address Register (FAR) bits */
#घोषणा FAR_LPT_MASK	0x03
#घोषणा FAR_LPTB	0x00
#घोषणा FAR_LPTA	0x01
#घोषणा FAR_LPTC	0x02

/* Power and Test Register (PTR) bits */
#घोषणा PTR_LPTB_IRQ7	0x08
#घोषणा PTR_LEVEL_IRQ	0x80	/* When not ECP/EPP: Use level IRQ           */
#घोषणा PTR_LPT_REG_सूची	0x80	/* When ECP/EPP: LPT CTR controls direction */
				/*               of the parallel port	     */

/* Function Control Register (FCR) bits */
#घोषणा FCR_LDE		0x10	/* Logical Drive Exchange                    */
#घोषणा FCR_ZWS_ENA	0x20	/* Enable लघु host पढ़ो/ग_लिखो in ECP/EPP   */

/* Prपूर्णांकer Control Register (PCR) bits */
#घोषणा PCR_EPP_ENABLE	0x01
#घोषणा PCR_EPP_IEEE	0x02	/* Enable EPP Version 1.9 (IEEE 1284)        */
#घोषणा PCR_ECP_ENABLE	0x04
#घोषणा PCR_ECP_CLK_ENA	0x08	/* If 0 ECP Clock is stopped on Power करोwn   */
#घोषणा PCR_IRQ_POLAR	0x20	/* If 0 IRQ is level high or negative pulse, */
				/* अगर 1 polarity is inverted                 */
#घोषणा PCR_IRQ_ODRAIN	0x40	/* If 1, IRQ is खोलो drain                   */

/* Tape UARTs and Parallel Port Config Register (TUP) bits */
#घोषणा TUP_EPP_TIMO	0x02	/* Enable EPP समयout IRQ                    */

/* Advanced SuperIO Config Register (ASC) bits */
#घोषणा ASC_LPT_IRQ7	0x01	/* Always use IRQ7 क्रम LPT                  */
#घोषणा ASC_DRV2_SEL	0x02	/* Logical Drive Exchange controlled by TDR  */

#घोषणा FER_RESERVED	0x00
#घोषणा FAR_RESERVED	0x00
#घोषणा PTR_RESERVED	0x73
#घोषणा FCR_RESERVED	0xc4
#घोषणा PCR_RESERVED	0x10
#घोषणा KRR_RESERVED	0x00
#घोषणा PMC_RESERVED	0x98
#घोषणा TUP_RESERVED	0xfb
#घोषणा SIP_RESERVED	0x00
#घोषणा ASC_RESERVED	0x18
#घोषणा CS0CF0_RESERVED	0x00
#घोषणा CS0CF1_RESERVED	0x08
#घोषणा CS1CF0_RESERVED	0x00
#घोषणा CS1CF1_RESERVED	0x08

#अगर_घोषित __KERNEL__

#समावेश <linux/spinlock.h>

#समावेश <यंत्र/पन.स>

बाह्य spinlock_t ns87303_lock;

अटल अंतरभूत पूर्णांक ns87303_modअगरy(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक index,
				     अचिन्हित अक्षर clr, अचिन्हित अक्षर set)
अणु
	अटल अचिन्हित अक्षर reserved[] = अणु
		FER_RESERVED, FAR_RESERVED, PTR_RESERVED, FCR_RESERVED,
		PCR_RESERVED, KRR_RESERVED, PMC_RESERVED, TUP_RESERVED,
		SIP_RESERVED, ASC_RESERVED, CS0CF0_RESERVED, CS0CF1_RESERVED,
		CS1CF0_RESERVED, CS1CF1_RESERVED
	पूर्ण;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर value;

	अगर (index > 0x0d)
		वापस -EINVAL;

	spin_lock_irqsave(&ns87303_lock, flags);

	outb(index, port);
	value = inb(port + 1);
	value &= ~(reserved[index] | clr);
	value |= set;
	outb(value, port + 1);
	outb(value, port + 1);

	spin_unlock_irqrestore(&ns87303_lock, flags);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* !(_SPARC_NS87303_H) */
