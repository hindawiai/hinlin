<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Helper module क्रम board specअगरic I2C bus registration
 *
 * Copyright (C) 2009 Nokia Corporation.
 */

#समावेश "soc.h"
#समावेश "omap_hwmod.h"
#समावेश "omap_device.h"

#समावेश "prm.h"
#समावेश "common.h"
#समावेश "i2c.h"

/* In रेजिस्टर I2C_CON, Bit 15 is the I2C enable bit */
#घोषणा I2C_EN					BIT(15)
#घोषणा OMAP2_I2C_CON_OFFSET			0x24
#घोषणा OMAP4_I2C_CON_OFFSET			0xA4

#घोषणा MAX_OMAP_I2C_HWMOD_NAME_LEN	16

/**
 * omap_i2c_reset - reset the omap i2c module.
 * @oh: काष्ठा omap_hwmod *
 *
 * The i2c moudle in omap2, omap3 had a special sequence to reset. The
 * sequence is:
 * - Disable the I2C.
 * - Write to SOFTRESET bit.
 * - Enable the I2C.
 * - Poll on the RESETDONE bit.
 * The sequence is implemented in below function. This is called क्रम 2420,
 * 2430 and omap3.
 */
पूर्णांक omap_i2c_reset(काष्ठा omap_hwmod *oh)
अणु
	u32 v;
	u16 i2c_con;
	पूर्णांक c = 0;

	अगर (soc_is_omap24xx() || soc_is_omap34xx() || soc_is_am35xx())
		i2c_con = OMAP2_I2C_CON_OFFSET;
	अन्यथा
		i2c_con = OMAP4_I2C_CON_OFFSET;

	/* Disable I2C */
	v = omap_hwmod_पढ़ो(oh, i2c_con);
	v &= ~I2C_EN;
	omap_hwmod_ग_लिखो(v, oh, i2c_con);

	/* Write to the SOFTRESET bit */
	omap_hwmod_softreset(oh);

	/* Enable I2C */
	v = omap_hwmod_पढ़ो(oh, i2c_con);
	v |= I2C_EN;
	omap_hwmod_ग_लिखो(v, oh, i2c_con);

	/* Poll on RESETDONE bit */
	omap_test_समयout((omap_hwmod_पढ़ो(oh,
				oh->class->sysc->syss_offs)
				& SYSS_RESETDONE_MASK),
				MAX_MODULE_SOFTRESET_WAIT, c);

	अगर (c == MAX_MODULE_SOFTRESET_WAIT)
		pr_warn("%s: %s: softreset failed (waited %d usec)\n",
			__func__, oh->name, MAX_MODULE_SOFTRESET_WAIT);
	अन्यथा
		pr_debug("%s: %s: softreset in %d usec\n", __func__,
			oh->name, c);

	वापस 0;
पूर्ण
