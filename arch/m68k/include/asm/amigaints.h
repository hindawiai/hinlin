<शैली गुरु>
/*
** amigaपूर्णांकs.h -- Amiga Linux पूर्णांकerrupt handling काष्ठाs and prototypes
**
** Copyright 1992 by Greg Harp
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the मुख्य directory of this archive
** क्रम more details.
**
** Created 10/2/92 by Greg Harp
*/

#अगर_अघोषित _ASMm68k_AMIGAINTS_H_
#घोषणा _ASMm68k_AMIGAINTS_H_

#समावेश <यंत्र/irq.h>

/*
** Amiga Interrupt sources.
**
*/

#घोषणा AUTO_IRQS           (8)
#घोषणा AMI_STD_IRQS        (14)
#घोषणा CIA_IRQS            (5)
#घोषणा AMI_IRQS            (32) /* AUTO_IRQS+AMI_STD_IRQS+2*CIA_IRQS */

/* builtin serial port पूर्णांकerrupts */
#घोषणा IRQ_AMIGA_TBE		(IRQ_USER+0)
#घोषणा IRQ_AMIGA_RBF		(IRQ_USER+11)

/* floppy disk पूर्णांकerrupts */
#घोषणा IRQ_AMIGA_DSKBLK	(IRQ_USER+1)
#घोषणा IRQ_AMIGA_DSKSYN	(IRQ_USER+12)

/* software पूर्णांकerrupts */
#घोषणा IRQ_AMIGA_SOFT		(IRQ_USER+2)

/* पूर्णांकerrupts from बाह्यal hardware */
#घोषणा IRQ_AMIGA_PORTS		IRQ_AUTO_2
#घोषणा IRQ_AMIGA_EXTER		IRQ_AUTO_6

/* copper पूर्णांकerrupt */
#घोषणा IRQ_AMIGA_COPPER	(IRQ_USER+4)

/* vertical blanking पूर्णांकerrupt */
#घोषणा IRQ_AMIGA_VERTB		(IRQ_USER+5)

/* Blitter करोne पूर्णांकerrupt */
#घोषणा IRQ_AMIGA_BLIT		(IRQ_USER+6)

/* Audio पूर्णांकerrupts */
#घोषणा IRQ_AMIGA_AUD0		(IRQ_USER+7)
#घोषणा IRQ_AMIGA_AUD1		(IRQ_USER+8)
#घोषणा IRQ_AMIGA_AUD2		(IRQ_USER+9)
#घोषणा IRQ_AMIGA_AUD3		(IRQ_USER+10)

/* CIA पूर्णांकerrupt sources */
#घोषणा IRQ_AMIGA_CIAA		(IRQ_USER+14)
#घोषणा IRQ_AMIGA_CIAA_TA	(IRQ_USER+14)
#घोषणा IRQ_AMIGA_CIAA_TB	(IRQ_USER+15)
#घोषणा IRQ_AMIGA_CIAA_ALRM	(IRQ_USER+16)
#घोषणा IRQ_AMIGA_CIAA_SP	(IRQ_USER+17)
#घोषणा IRQ_AMIGA_CIAA_FLG	(IRQ_USER+18)
#घोषणा IRQ_AMIGA_CIAB		(IRQ_USER+19)
#घोषणा IRQ_AMIGA_CIAB_TA	(IRQ_USER+19)
#घोषणा IRQ_AMIGA_CIAB_TB	(IRQ_USER+20)
#घोषणा IRQ_AMIGA_CIAB_ALRM	(IRQ_USER+21)
#घोषणा IRQ_AMIGA_CIAB_SP	(IRQ_USER+22)
#घोषणा IRQ_AMIGA_CIAB_FLG	(IRQ_USER+23)


/* INTREQR masks */
#घोषणा IF_SETCLR   0x8000      /* set/clr bit */
#घोषणा IF_INTEN    0x4000	/* master पूर्णांकerrupt bit in INT* रेजिस्टरs */
#घोषणा IF_EXTER    0x2000	/* बाह्यal level 6 and CIA B पूर्णांकerrupt */
#घोषणा IF_DSKSYN   0x1000	/* disk sync पूर्णांकerrupt */
#घोषणा IF_RBF	    0x0800	/* serial receive buffer full पूर्णांकerrupt */
#घोषणा IF_AUD3     0x0400	/* audio channel 3 करोne पूर्णांकerrupt */
#घोषणा IF_AUD2     0x0200	/* audio channel 2 करोne पूर्णांकerrupt */
#घोषणा IF_AUD1     0x0100	/* audio channel 1 करोne पूर्णांकerrupt */
#घोषणा IF_AUD0     0x0080	/* audio channel 0 करोne पूर्णांकerrupt */
#घोषणा IF_BLIT     0x0040	/* blitter करोne पूर्णांकerrupt */
#घोषणा IF_VERTB    0x0020	/* vertical blanking पूर्णांकerrupt */
#घोषणा IF_COPER    0x0010	/* copper पूर्णांकerrupt */
#घोषणा IF_PORTS    0x0008	/* बाह्यal level 2 and CIA A पूर्णांकerrupt */
#घोषणा IF_SOFT     0x0004	/* software initiated पूर्णांकerrupt */
#घोषणा IF_DSKBLK   0x0002	/* diskblock DMA finished */
#घोषणा IF_TBE	    0x0001	/* serial transmit buffer empty पूर्णांकerrupt */

/* CIA पूर्णांकerrupt control रेजिस्टर bits */

#घोषणा CIA_ICR_TA	0x01
#घोषणा CIA_ICR_TB	0x02
#घोषणा CIA_ICR_ALRM	0x04
#घोषणा CIA_ICR_SP	0x08
#घोषणा CIA_ICR_FLG	0x10
#घोषणा CIA_ICR_ALL	0x1f
#घोषणा CIA_ICR_SETCLR	0x80

बाह्य व्योम amiga_init_IRQ(व्योम);

/* to access the पूर्णांकerrupt control रेजिस्टरs of CIA's use only
** these functions, they behave exactly like the amiga os routines
*/

बाह्य काष्ठा ciabase ciaa_base, ciab_base;

बाह्य व्योम cia_init_IRQ(काष्ठा ciabase *base);
बाह्य अचिन्हित अक्षर cia_set_irq(काष्ठा ciabase *base, अचिन्हित अक्षर mask);
बाह्य अचिन्हित अक्षर cia_able_irq(काष्ठा ciabase *base, अचिन्हित अक्षर mask);

#पूर्ण_अगर /* यंत्र-m68k/amigaपूर्णांकs.h */
