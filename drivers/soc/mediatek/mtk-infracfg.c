<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Pengutronix, Sascha Hauer <kernel@pengutronix.de>
 */

#समावेश <linux/export.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/regmap.h>
#समावेश <linux/soc/mediatek/infracfg.h>
#समावेश <यंत्र/processor.h>

#घोषणा MTK_POLL_DELAY_US   10
#घोषणा MTK_POLL_TIMEOUT    (jअगरfies_to_usecs(HZ))

/**
 * mtk_infracfg_set_bus_protection - enable bus protection
 * @infracfg: The infracfg regmap
 * @mask: The mask containing the protection bits to be enabled.
 * @reg_update: The boolean flag determines to set the protection bits
 *              by regmap_update_bits with enable रेजिस्टर(PROTECTEN) or
 *              by regmap_ग_लिखो with set रेजिस्टर(PROTECTEN_SET).
 *
 * This function enables the bus protection bits क्रम disabled घातer
 * करोमुख्यs so that the प्रणाली करोes not hang when some unit accesses the
 * bus जबतक in घातer करोwn.
 */
पूर्णांक mtk_infracfg_set_bus_protection(काष्ठा regmap *infracfg, u32 mask,
		bool reg_update)
अणु
	u32 val;
	पूर्णांक ret;

	अगर (reg_update)
		regmap_update_bits(infracfg, INFRA_TOPAXI_PROTECTEN, mask,
				mask);
	अन्यथा
		regmap_ग_लिखो(infracfg, INFRA_TOPAXI_PROTECTEN_SET, mask);

	ret = regmap_पढ़ो_poll_समयout(infracfg, INFRA_TOPAXI_PROTECTSTA1,
				       val, (val & mask) == mask,
				       MTK_POLL_DELAY_US, MTK_POLL_TIMEOUT);

	वापस ret;
पूर्ण

/**
 * mtk_infracfg_clear_bus_protection - disable bus protection
 * @infracfg: The infracfg regmap
 * @mask: The mask containing the protection bits to be disabled.
 * @reg_update: The boolean flag determines to clear the protection bits
 *              by regmap_update_bits with enable रेजिस्टर(PROTECTEN) or
 *              by regmap_ग_लिखो with clear रेजिस्टर(PROTECTEN_CLR).
 *
 * This function disables the bus protection bits previously enabled with
 * mtk_infracfg_set_bus_protection.
 */

पूर्णांक mtk_infracfg_clear_bus_protection(काष्ठा regmap *infracfg, u32 mask,
		bool reg_update)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (reg_update)
		regmap_update_bits(infracfg, INFRA_TOPAXI_PROTECTEN, mask, 0);
	अन्यथा
		regmap_ग_लिखो(infracfg, INFRA_TOPAXI_PROTECTEN_CLR, mask);

	ret = regmap_पढ़ो_poll_समयout(infracfg, INFRA_TOPAXI_PROTECTSTA1,
				       val, !(val & mask),
				       MTK_POLL_DELAY_US, MTK_POLL_TIMEOUT);

	वापस ret;
पूर्ण
