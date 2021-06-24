<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *  Copyright (C) 2004 IDT Inc.
 *  Copyright (C) 2006 Felix Fietkau <nbd@खोलोwrt.org>
 */
#अगर_अघोषित __ASM_RC32434_RB_H
#घोषणा __ASM_RC32434_RB_H

#समावेश <linux/genhd.h>

#घोषणा REGBASE		0x18000000
#घोषणा IDT434_REG_BASE ((अस्थिर व्योम *) KSEG1ADDR(REGBASE))
#घोषणा UART0BASE	0x58000
#घोषणा RST		(1 << 15)
#घोषणा DEV0BASE	0x010000
#घोषणा DEV0MASK	0x010004
#घोषणा DEV0C		0x010008
#घोषणा DEV0T		0x01000C
#घोषणा DEV1BASE	0x010010
#घोषणा DEV1MASK	0x010014
#घोषणा DEV1C		0x010018
#घोषणा DEV1TC		0x01001C
#घोषणा DEV2BASE	0x010020
#घोषणा DEV2MASK	0x010024
#घोषणा DEV2C		0x010028
#घोषणा DEV2TC		0x01002C
#घोषणा DEV3BASE	0x010030
#घोषणा DEV3MASK	0x010034
#घोषणा DEV3C		0x010038
#घोषणा DEV3TC		0x01003C
#घोषणा BTCS		0x010040
#घोषणा BTCOMPARE	0x010044
#घोषणा GPIOBASE	0x050000
/* Offsets relative to GPIOBASE */
#घोषणा GPIOFUNC	0x00
#घोषणा GPIOCFG		0x04
#घोषणा GPIOD		0x08
#घोषणा GPIOILEVEL	0x0C
#घोषणा GPIOISTAT	0x10
#घोषणा GPIONMIEN	0x14
#घोषणा IMASK6		0x38
#घोषणा LO_WPX		(1 << 0)
#घोषणा LO_ALE		(1 << 1)
#घोषणा LO_CLE		(1 << 2)
#घोषणा LO_CEX		(1 << 3)
#घोषणा LO_FOFF		(1 << 5)
#घोषणा LO_SPICS	(1 << 6)
#घोषणा LO_ULED		(1 << 7)

#घोषणा BIT_TO_MASK(x)	(1 << x)

काष्ठा dev_reg अणु
	u32	base;
	u32	mask;
	u32	ctl;
	u32	timing;
पूर्ण;

काष्ठा korina_device अणु
	अक्षर *name;
	अचिन्हित अक्षर mac[6];
	काष्ठा net_device *dev;
पूर्ण;

काष्ठा mpmc_device अणु
	अचिन्हित अक्षर	state;
	spinlock_t	lock;
	व्योम __iomem	*base;
पूर्ण;

बाह्य व्योम set_latch_u5(अचिन्हित अक्षर or_mask, अचिन्हित अक्षर nand_mask);
बाह्य अचिन्हित अक्षर get_latch_u5(व्योम);

#पूर्ण_अगर	/* __ASM_RC32434_RB_H */
