<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Common data shared between Maxim 77693 and 77843 drivers
 *
 * Copyright (C) 2015 Samsung Electronics
 */

#अगर_अघोषित __LINUX_MFD_MAX77693_COMMON_H
#घोषणा __LINUX_MFD_MAX77693_COMMON_H

क्रमागत max77693_types अणु
	TYPE_MAX77693_UNKNOWN,
	TYPE_MAX77693,
	TYPE_MAX77843,

	TYPE_MAX77693_NUM,
पूर्ण;

/*
 * Shared also with max77843.
 */
काष्ठा max77693_dev अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c;		/* 0xCC , PMIC, Charger, Flash LED */
	काष्ठा i2c_client *i2c_muic;	/* 0x4A , MUIC */
	काष्ठा i2c_client *i2c_haptic;	/* MAX77693: 0x90 , Haptic */
	काष्ठा i2c_client *i2c_chg;	/* MAX77843: 0xD2, Charger */

	क्रमागत max77693_types type;

	काष्ठा regmap *regmap;
	काष्ठा regmap *regmap_muic;
	काष्ठा regmap *regmap_haptic;	/* Only MAX77693 */
	काष्ठा regmap *regmap_chg;	/* Only MAX77843 */

	काष्ठा regmap_irq_chip_data *irq_data_led;
	काष्ठा regmap_irq_chip_data *irq_data_topsys;
	काष्ठा regmap_irq_chip_data *irq_data_chg; /* Only MAX77693 */
	काष्ठा regmap_irq_chip_data *irq_data_muic;

	पूर्णांक irq;
पूर्ण;


#पूर्ण_अगर /*  __LINUX_MFD_MAX77693_COMMON_H */
