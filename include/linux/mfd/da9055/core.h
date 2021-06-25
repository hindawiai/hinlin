<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * da9055 declarations क्रम DA9055 PMICs.
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#अगर_अघोषित __DA9055_CORE_H
#घोषणा __DA9055_CORE_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>

/*
 * PMIC IRQ
 */
#घोषणा DA9055_IRQ_ALARM	0x01
#घोषणा DA9055_IRQ_TICK		0x02
#घोषणा DA9055_IRQ_NONKEY	0x00
#घोषणा DA9055_IRQ_REGULATOR	0x0B
#घोषणा DA9055_IRQ_HWMON	0x03

काष्ठा da9055_pdata;

काष्ठा da9055 अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *irq_data;
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c_client;

	पूर्णांक irq_base;
	पूर्णांक chip_irq;
पूर्ण;

/* Device I/O */
अटल अंतरभूत पूर्णांक da9055_reg_पढ़ो(काष्ठा da9055 *da9055, अचिन्हित अक्षर reg)
अणु
	पूर्णांक val, ret;

	ret = regmap_पढ़ो(da9055->regmap, reg, &val);
	अगर (ret < 0)
		वापस ret;

	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक da9055_reg_ग_लिखो(काष्ठा da9055 *da9055, अचिन्हित अक्षर reg,
				    अचिन्हित अक्षर val)
अणु
	वापस regmap_ग_लिखो(da9055->regmap, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक da9055_group_पढ़ो(काष्ठा da9055 *da9055, अचिन्हित अक्षर reg,
				     अचिन्हित reg_cnt, अचिन्हित अक्षर *val)
अणु
	वापस regmap_bulk_पढ़ो(da9055->regmap, reg, val, reg_cnt);
पूर्ण

अटल अंतरभूत पूर्णांक da9055_group_ग_लिखो(काष्ठा da9055 *da9055, अचिन्हित अक्षर reg,
				      अचिन्हित reg_cnt, अचिन्हित अक्षर *val)
अणु
	वापस regmap_raw_ग_लिखो(da9055->regmap, reg, val, reg_cnt);
पूर्ण

अटल अंतरभूत पूर्णांक da9055_reg_update(काष्ठा da9055 *da9055, अचिन्हित अक्षर reg,
				     अचिन्हित अक्षर bit_mask,
				     अचिन्हित अक्षर reg_val)
अणु
	वापस regmap_update_bits(da9055->regmap, reg, bit_mask, reg_val);
पूर्ण

/* Generic Device API */
पूर्णांक da9055_device_init(काष्ठा da9055 *da9055);
व्योम da9055_device_निकास(काष्ठा da9055 *da9055);

बाह्य स्थिर काष्ठा regmap_config da9055_regmap_config;

#पूर्ण_अगर /* __DA9055_CORE_H */
