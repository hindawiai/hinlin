<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __WCD934X_H__
#घोषणा __WCD934X_H__
#समावेश <linux/clk.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slimbus.h>

#घोषणा WCD934X_MAX_SUPPLY	5

/**
 * काष्ठा wcd934x_ddata - wcd934x driver data
 *
 * @supplies:	wcd934x regulator supplies
 * @irq_data:	wcd934x irq_chip data
 * @regmap:	wcd934x regmap poपूर्णांकer
 * @extclk:	External घड़ी
 * @dev:	device instance of wcd934x slim device
 * @irq:	irq क्रम wcd934x.
 */
काष्ठा wcd934x_ddata अणु
	काष्ठा regulator_bulk_data supplies[WCD934X_MAX_SUPPLY];
	काष्ठा regmap_irq_chip_data *irq_data;
	काष्ठा regmap *regmap;
	काष्ठा clk *extclk;
	काष्ठा device *dev;
	पूर्णांक irq;
पूर्ण;

#पूर्ण_अगर /* __WCD934X_H__ */
