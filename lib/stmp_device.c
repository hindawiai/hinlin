<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 1999 ARM Limited
 * Copyright (C) 2000 Deep Blue Solutions Ltd
 * Copyright 2006-2007,2010 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2008 Juergen Beisert, kernel@pengutronix.de
 * Copyright 2009 Ilya Yanok, Emcraft Systems Ltd, yanok@emcraft.com
 * Copyright (C) 2011 Wolfram Sang, Pengutronix e.K.
 */

#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>
#समावेश <linux/sपंचांगp_device.h>

#घोषणा STMP_MODULE_CLKGATE	(1 << 30)
#घोषणा STMP_MODULE_SFTRST	(1 << 31)

/*
 * Clear the bit and poll it cleared.  This is usually called with
 * a reset address and mask being either SFTRST(bit 31) or CLKGATE
 * (bit 30).
 */
अटल पूर्णांक sपंचांगp_clear_poll_bit(व्योम __iomem *addr, u32 mask)
अणु
	पूर्णांक समयout = 0x400;

	ग_लिखोl(mask, addr + STMP_OFFSET_REG_CLR);
	udelay(1);
	जबतक ((पढ़ोl(addr) & mask) && --समयout)
		/* nothing */;

	वापस !समयout;
पूर्ण

पूर्णांक sपंचांगp_reset_block(व्योम __iomem *reset_addr)
अणु
	पूर्णांक ret;
	पूर्णांक समयout = 0x400;

	/* clear and poll SFTRST */
	ret = sपंचांगp_clear_poll_bit(reset_addr, STMP_MODULE_SFTRST);
	अगर (unlikely(ret))
		जाओ error;

	/* clear CLKGATE */
	ग_लिखोl(STMP_MODULE_CLKGATE, reset_addr + STMP_OFFSET_REG_CLR);

	/* set SFTRST to reset the block */
	ग_लिखोl(STMP_MODULE_SFTRST, reset_addr + STMP_OFFSET_REG_SET);
	udelay(1);

	/* poll CLKGATE becoming set */
	जबतक ((!(पढ़ोl(reset_addr) & STMP_MODULE_CLKGATE)) && --समयout)
		/* nothing */;
	अगर (unlikely(!समयout))
		जाओ error;

	/* clear and poll SFTRST */
	ret = sपंचांगp_clear_poll_bit(reset_addr, STMP_MODULE_SFTRST);
	अगर (unlikely(ret))
		जाओ error;

	/* clear and poll CLKGATE */
	ret = sपंचांगp_clear_poll_bit(reset_addr, STMP_MODULE_CLKGATE);
	अगर (unlikely(ret))
		जाओ error;

	वापस 0;

error:
	pr_err("%s(%p): module reset timeout\n", __func__, reset_addr);
	वापस -ETIMEDOUT;
पूर्ण
EXPORT_SYMBOL(sपंचांगp_reset_block);
