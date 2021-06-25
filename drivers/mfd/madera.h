<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MFD पूर्णांकernals क्रम Cirrus Logic Madera codecs
 *
 * Copyright 2015-2018 Cirrus Logic
 */

#अगर_अघोषित MADERA_MFD_H
#घोषणा MADERA_MFD_H

#समावेश <linux/of.h>
#समावेश <linux/pm.h>

काष्ठा madera;

बाह्य स्थिर काष्ठा dev_pm_ops madera_pm_ops;
बाह्य स्थिर काष्ठा of_device_id madera_of_match[];

पूर्णांक madera_dev_init(काष्ठा madera *madera);
पूर्णांक madera_dev_निकास(काष्ठा madera *madera);

स्थिर अक्षर *madera_name_from_type(क्रमागत madera_type type);

बाह्य स्थिर काष्ठा regmap_config cs47l15_16bit_spi_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l15_32bit_spi_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l15_16bit_i2c_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l15_32bit_i2c_regmap;
पूर्णांक cs47l15_patch(काष्ठा madera *madera);

बाह्य स्थिर काष्ठा regmap_config cs47l35_16bit_spi_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l35_32bit_spi_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l35_16bit_i2c_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l35_32bit_i2c_regmap;
पूर्णांक cs47l35_patch(काष्ठा madera *madera);

बाह्य स्थिर काष्ठा regmap_config cs47l85_16bit_spi_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l85_32bit_spi_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l85_16bit_i2c_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l85_32bit_i2c_regmap;
पूर्णांक cs47l85_patch(काष्ठा madera *madera);

बाह्य स्थिर काष्ठा regmap_config cs47l90_16bit_spi_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l90_32bit_spi_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l90_16bit_i2c_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l90_32bit_i2c_regmap;
पूर्णांक cs47l90_patch(काष्ठा madera *madera);

बाह्य स्थिर काष्ठा regmap_config cs47l92_16bit_spi_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l92_32bit_spi_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l92_16bit_i2c_regmap;
बाह्य स्थिर काष्ठा regmap_config cs47l92_32bit_i2c_regmap;
पूर्णांक cs47l92_patch(काष्ठा madera *madera);

#पूर्ण_अगर
