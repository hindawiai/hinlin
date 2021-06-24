<शैली गुरु>
/*
 * Broadcom BCM63xx Processor Monitor Bus shared routines (SMP and reset)
 *
 * Copyright (C) 2015, Broadcom Corporation
 * Author: Florian Fainelli <f.fainelli@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित __BCM63XX_PMB_H
#घोषणा __BCM63XX_PMB_H

#समावेश <linux/पन.स>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>

/* PMB Master controller रेजिस्टर */
#घोषणा PMB_CTRL		0x00
#घोषणा  PMC_PMBM_START		(1 << 31)
#घोषणा  PMC_PMBM_TIMEOUT	(1 << 30)
#घोषणा  PMC_PMBM_SLAVE_ERR	(1 << 29)
#घोषणा  PMC_PMBM_BUSY		(1 << 28)
#घोषणा  PMC_PMBM_READ		(0 << 20)
#घोषणा  PMC_PMBM_WRITE		(1 << 20)
#घोषणा PMB_WR_DATA		0x04
#घोषणा PMB_TIMEOUT		0x08
#घोषणा PMB_RD_DATA		0x0C

#घोषणा PMB_BUS_ID_SHIFT	8

/* Perक्रमm the low-level PMB master operation, shared between पढ़ोs and
 * ग_लिखोs.
 */
अटल अंतरभूत पूर्णांक __bpcm_करो_op(व्योम __iomem *master, अचिन्हित पूर्णांक addr,
			       u32 off, u32 op)
अणु
	अचिन्हित पूर्णांक समयout = 1000;
	u32 cmd;

	cmd = (PMC_PMBM_START | op | (addr & 0xff) << 12 | off);
	ग_लिखोl(cmd, master + PMB_CTRL);
	करो अणु
		cmd = पढ़ोl(master + PMB_CTRL);
		अगर (!(cmd & PMC_PMBM_START))
			वापस 0;

		अगर (cmd & PMC_PMBM_SLAVE_ERR)
			वापस -EIO;

		अगर (cmd & PMC_PMBM_TIMEOUT)
			वापस -ETIMEDOUT;

		udelay(1);
	पूर्ण जबतक (समयout-- > 0);

	वापस -ETIMEDOUT;
पूर्ण

अटल अंतरभूत पूर्णांक bpcm_rd(व्योम __iomem *master, अचिन्हित पूर्णांक addr,
			  u32 off, u32 *val)
अणु
	पूर्णांक ret = 0;

	ret = __bpcm_करो_op(master, addr, off >> 2, PMC_PMBM_READ);
	*val = पढ़ोl(master + PMB_RD_DATA);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक bpcm_wr(व्योम __iomem *master, अचिन्हित पूर्णांक addr,
			  u32 off, u32 val)
अणु
	पूर्णांक ret = 0;

	ग_लिखोl(val, master + PMB_WR_DATA);
	ret = __bpcm_करो_op(master, addr, off >> 2, PMC_PMBM_WRITE);

	वापस ret;
पूर्ण

#पूर्ण_अगर /* __BCM63XX_PMB_H */
