<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Platक्रमm data क्रम Cirrus Logic Madera codecs
 *
 * Copyright (C) 2015-2018 Cirrus Logic
 */

#अगर_अघोषित MADERA_PDATA_H
#घोषणा MADERA_PDATA_H

#समावेश <linux/kernel.h>
#समावेश <linux/regulator/arizona-lकरो1.h>
#समावेश <linux/regulator/arizona-micsupp.h>
#समावेश <linux/regulator/machine.h>
#समावेश <sound/madera-pdata.h>

#घोषणा MADERA_MAX_MICBIAS		4
#घोषणा MADERA_MAX_CHILD_MICBIAS	4

#घोषणा MADERA_MAX_GPSW			2

काष्ठा gpio_desc;
काष्ठा pinctrl_map;

/**
 * काष्ठा madera_pdata - Configuration data क्रम Madera devices
 *
 * @reset:	    GPIO controlling /RESET (शून्य = none)
 * @lकरो1:	    Subकाष्ठा of pdata क्रम the LDO1 regulator
 * @micvdd:	    Subकाष्ठा of pdata क्रम the MICVDD regulator
 * @irq_flags:	    Mode क्रम primary IRQ (शेषs to active low)
 * @gpio_base:	    Base GPIO number
 * @gpio_configs:   Array of GPIO configurations (See
 *		    Documentation/driver-api/pinctl.rst)
 * @n_gpio_configs: Number of entries in gpio_configs
 * @gpsw:	    General purpose चयन mode setting. Depends on the बाह्यal
 *		    hardware connected to the चयन. (See the SW1_MODE field
 *		    in the datasheet क्रम the available values क्रम your codec)
 * @codec:	    Subकाष्ठा of pdata क्रम the ASoC codec driver
 */
काष्ठा madera_pdata अणु
	काष्ठा gpio_desc *reset;

	काष्ठा arizona_lकरो1_pdata lकरो1;
	काष्ठा arizona_micsupp_pdata micvdd;

	अचिन्हित पूर्णांक irq_flags;
	पूर्णांक gpio_base;

	स्थिर काष्ठा pinctrl_map *gpio_configs;
	पूर्णांक n_gpio_configs;

	u32 gpsw[MADERA_MAX_GPSW];

	काष्ठा madera_codec_pdata codec;
पूर्ण;

#पूर्ण_अगर
