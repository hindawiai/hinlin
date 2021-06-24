<शैली गुरु>
/*
** यंत्र-m68k/amigayle.h -- This header defines the रेजिस्टरs of the gayle chip
**                        found on the Amiga 1200
**                        This inक्रमmation was found by disassembling card.resource,
**                        so the definitions may not be 100% correct
**                        anyone has an official करोc ?
**
** Copyright 1997 by Alain Malek
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the मुख्य directory of this archive
** क्रम more details.
**
** Created: 11/28/97 by Alain Malek
*/

#अगर_अघोषित _M68K_AMIGAYLE_H_
#घोषणा _M68K_AMIGAYLE_H_

#समावेश <linux/types.h>
#समावेश <यंत्र/amigahw.h>

/* memory layout */

#घोषणा GAYLE_RAM		(0x600000+zTwoBase)
#घोषणा GAYLE_RAMSIZE		(0x400000)
#घोषणा GAYLE_ATTRIBUTE		(0xa00000+zTwoBase)
#घोषणा GAYLE_ATTRIBUTESIZE	(0x020000)
#घोषणा GAYLE_IO		(0xa20000+zTwoBase)	/* 16bit and even 8bit रेजिस्टरs */
#घोषणा GAYLE_IOSIZE		(0x010000)
#घोषणा GAYLE_IO_8BITODD	(0xa30000+zTwoBase)	/* odd 8bit रेजिस्टरs */

/* offset क्रम accessing odd IO रेजिस्टरs */
#घोषणा GAYLE_ODD		(GAYLE_IO_8BITODD-GAYLE_IO-1)

/* GAYLE रेजिस्टरs */

काष्ठा GAYLE अणु
	u_अक्षर cardstatus;
	u_अक्षर pad0[0x1000-1];

	u_अक्षर पूर्णांकreq;
	u_अक्षर pad1[0x1000-1];

	u_अक्षर पूर्णांकen;
	u_अक्षर pad2[0x1000-1];

	u_अक्षर config;
	u_अक्षर pad3[0x1000-1];
पूर्ण;

#घोषणा GAYLE_ADDRESS	(0xda8000)	/* gayle मुख्य रेजिस्टरs base address */

#घोषणा GAYLE_RESET	(0xa40000)	/* ग_लिखो 0x00 to start reset,
                                           पढ़ो 1 byte to stop reset */

#घोषणा gayle (*(अस्थिर काष्ठा GAYLE *)(zTwoBase+GAYLE_ADDRESS))
#घोषणा gayle_reset (*(अस्थिर u_अक्षर *)(zTwoBase+GAYLE_RESET))

#घोषणा gayle_attribute ((अस्थिर u_अक्षर *)(GAYLE_ATTRIBUTE))

#अगर 0
#घोषणा gayle_inb(a) पढ़ोb( GAYLE_IO+(a)+(((a)&1)*GAYLE_ODD) )
#घोषणा gayle_outb(v,a) ग_लिखोb( v, GAYLE_IO+(a)+(((a)&1)*GAYLE_ODD) )

#घोषणा gayle_inw(a) पढ़ोw( GAYLE_IO+(a) )
#घोषणा gayle_outw(v,a) ग_लिखोw( v, GAYLE_IO+(a) )
#पूर्ण_अगर

/* GAYLE_CARDSTATUS bit def */

#घोषणा GAYLE_CS_CCDET		0x40	/* credit card detect */
#घोषणा GAYLE_CS_BVD1		0x20	/* battery voltage detect 1 */
#घोषणा GAYLE_CS_SC		0x20	/* credit card status change */
#घोषणा GAYLE_CS_BVD2		0x10	/* battery voltage detect 2 */
#घोषणा GAYLE_CS_DA		0x10	/* digital audio */
#घोषणा GAYLE_CS_WR		0x08	/* ग_लिखो enable (1 == enabled) */
#घोषणा GAYLE_CS_BSY		0x04	/* credit card busy */
#घोषणा GAYLE_CS_IRQ		0x04	/* पूर्णांकerrupt request */

/* GAYLE_IRQ bit def */

#घोषणा GAYLE_IRQ_IDE		0x80
#घोषणा GAYLE_IRQ_CCDET		0x40
#घोषणा GAYLE_IRQ_BVD1		0x20
#घोषणा GAYLE_IRQ_SC		0x20
#घोषणा GAYLE_IRQ_BVD2		0x10
#घोषणा GAYLE_IRQ_DA		0x10
#घोषणा GAYLE_IRQ_WR		0x08
#घोषणा GAYLE_IRQ_BSY		0x04
#घोषणा GAYLE_IRQ_IRQ		0x04
#घोषणा GAYLE_IRQ_IDEACK1	0x02
#घोषणा GAYLE_IRQ_IDEACK0	0x01

/* GAYLE_CONFIG bit def
   (bit 0-1 क्रम program voltage, bit 2-3 क्रम access speed */

#घोषणा GAYLE_CFG_0V		0x00
#घोषणा GAYLE_CFG_5V		0x01
#घोषणा GAYLE_CFG_12V		0x02

#घोषणा GAYLE_CFG_100NS		0x08
#घोषणा GAYLE_CFG_150NS		0x04
#घोषणा GAYLE_CFG_250NS		0x00
#घोषणा GAYLE_CFG_720NS		0x0c

काष्ठा gayle_ide_platक्रमm_data अणु
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ irqport;
	पूर्णांक explicit_ack;	/* A1200 IDE needs explicit ack */
पूर्ण;

#पूर्ण_अगर /* यंत्र-m68k/amigayle.h */
