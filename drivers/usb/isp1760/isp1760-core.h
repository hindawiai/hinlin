<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the NXP ISP1760 chip
 *
 * Copyright 2014 Laurent Pinअक्षरt
 * Copyright 2007 Sebastian Siewior
 *
 * Contacts:
 *	Sebastian Siewior <bigeasy@linutronix.de>
 *	Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित _ISP1760_CORE_H_
#घोषणा _ISP1760_CORE_H_

#समावेश <linux/ioport.h>

#समावेश "isp1760-hcd.h"
#समावेश "isp1760-udc.h"

काष्ठा device;
काष्ठा gpio_desc;

/*
 * Device flags that can vary from board to board.  All of these
 * indicate the most "atypical" हाल, so that a devflags of 0 is
 * a sane शेष configuration.
 */
#घोषणा ISP1760_FLAG_BUS_WIDTH_16	0x00000002 /* 16-bit data bus width */
#घोषणा ISP1760_FLAG_OTG_EN		0x00000004 /* Port 1 supports OTG */
#घोषणा ISP1760_FLAG_ANALOG_OC		0x00000008 /* Analog overcurrent */
#घोषणा ISP1760_FLAG_DACK_POL_HIGH	0x00000010 /* DACK active high */
#घोषणा ISP1760_FLAG_DREQ_POL_HIGH	0x00000020 /* DREQ active high */
#घोषणा ISP1760_FLAG_ISP1761		0x00000040 /* Chip is ISP1761 */
#घोषणा ISP1760_FLAG_INTR_POL_HIGH	0x00000080 /* Interrupt polarity active high */
#घोषणा ISP1760_FLAG_INTR_EDGE_TRIG	0x00000100 /* Interrupt edge triggered */

काष्ठा isp1760_device अणु
	काष्ठा device *dev;

	व्योम __iomem *regs;
	अचिन्हित पूर्णांक devflags;
	काष्ठा gpio_desc *rst_gpio;

	काष्ठा isp1760_hcd hcd;
	काष्ठा isp1760_udc udc;
पूर्ण;

पूर्णांक isp1760_रेजिस्टर(काष्ठा resource *mem, पूर्णांक irq, अचिन्हित दीर्घ irqflags,
		     काष्ठा device *dev, अचिन्हित पूर्णांक devflags);
व्योम isp1760_unरेजिस्टर(काष्ठा device *dev);

व्योम isp1760_set_pullup(काष्ठा isp1760_device *isp, bool enable);

अटल अंतरभूत u32 isp1760_पढ़ो32(व्योम __iomem *base, u32 reg)
अणु
	वापस पढ़ोl(base + reg);
पूर्ण

अटल अंतरभूत व्योम isp1760_ग_लिखो32(व्योम __iomem *base, u32 reg, u32 val)
अणु
	ग_लिखोl(val, base + reg);
पूर्ण

#पूर्ण_अगर
