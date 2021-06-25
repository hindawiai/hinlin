<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/es1888.c
 *
 * Init the built-in ES1888 sound chip (SB16 compatible)
 */

#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>
#समावेश "proto.h"

व्योम __init
es1888_init(व्योम)
अणु
	/* Sequence of IO पढ़ोs to init the audio controller */
	inb(0x0229);
	inb(0x0229);
	inb(0x0229);
	inb(0x022b);
	inb(0x0229);
	inb(0x022b);
	inb(0x0229);
	inb(0x0229);
	inb(0x022b);
	inb(0x0229);
	inb(0x0220); /* This sets the base address to 0x220 */

	/* Sequence to set DMA channels */
	outb(0x01, 0x0226);		/* reset */
	inb(0x0226);			/* छोड़ो */
	outb(0x00, 0x0226);		/* release reset */
	जबतक (!(inb(0x022e) & 0x80))	/* रुको क्रम bit 7 to निश्चित*/
		जारी;
	inb(0x022a);			/* छोड़ो */
	outb(0xc6, 0x022c);		/* enable extended mode */
	inb(0x022a);			/* छोड़ो, also क्रमces the ग_लिखो */
	जबतक (inb(0x022c) & 0x80)	/* रुको क्रम bit 7 to deनिश्चित */
		जारी;
	outb(0xb1, 0x022c);		/* setup क्रम ग_लिखो to Interrupt CR */
	जबतक (inb(0x022c) & 0x80)	/* रुको क्रम bit 7 to deनिश्चित */
		जारी;
	outb(0x14, 0x022c);		/* set IRQ 5 */
	जबतक (inb(0x022c) & 0x80)	/* रुको क्रम bit 7 to deनिश्चित */
		जारी;
	outb(0xb2, 0x022c);		/* setup क्रम ग_लिखो to DMA CR */
	जबतक (inb(0x022c) & 0x80)	/* रुको क्रम bit 7 to deनिश्चित */
		जारी;
	outb(0x18, 0x022c);		/* set DMA channel 1 */
	inb(0x022c);			/* क्रमce the ग_लिखो */
पूर्ण
