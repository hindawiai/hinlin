<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Copyright (C) 2018 ROHM Semiconductors */

#अगर_अघोषित __LINUX_MFD_ROHM_H__
#घोषणा __LINUX_MFD_ROHM_H__

#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>

क्रमागत rohm_chip_type अणु
	ROHM_CHIP_TYPE_BD9571,
	ROHM_CHIP_TYPE_BD9573,
	ROHM_CHIP_TYPE_BD9574,
	ROHM_CHIP_TYPE_BD9576,
	ROHM_CHIP_TYPE_BD70528,
	ROHM_CHIP_TYPE_BD71815,
	ROHM_CHIP_TYPE_BD71828,
	ROHM_CHIP_TYPE_BD71837,
	ROHM_CHIP_TYPE_BD71847,
	ROHM_CHIP_TYPE_AMOUNT
पूर्ण;

काष्ठा rohm_regmap_dev अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा ROHM_DVS_LEVEL_RUN		BIT(0)
#घोषणा ROHM_DVS_LEVEL_IDLE		BIT(1)
#घोषणा ROHM_DVS_LEVEL_SUSPEND		BIT(2)
#घोषणा ROHM_DVS_LEVEL_LPSR		BIT(3)
#घोषणा ROHM_DVS_LEVEL_SNVS		BIT(4)
#घोषणा ROHM_DVS_LEVEL_VALID_AMOUNT	5
#घोषणा ROHM_DVS_LEVEL_UNKNOWN		0

/**
 * काष्ठा rohm_dvs_config - dynamic voltage scaling रेजिस्टर descriptions
 *
 * @level_map:		biपंचांगap representing supported run-levels क्रम this
 *			regulator
 * @run_reg:		रेजिस्टर address क्रम regulator config at 'run' state
 * @run_mask:		value mask क्रम regulator voltages at 'run' state
 * @run_on_mask:	enable mask क्रम regulator at 'run' state
 * @idle_reg:		रेजिस्टर address क्रम regulator config at 'idle' state
 * @idle_mask:		value mask क्रम regulator voltages at 'idle' state
 * @idle_on_mask:	enable mask क्रम regulator at 'idle' state
 * @suspend_reg:	रेजिस्टर address क्रम regulator config at 'suspend' state
 * @suspend_mask:	value mask क्रम regulator voltages at 'suspend' state
 * @suspend_on_mask:	enable mask क्रम regulator at 'suspend' state
 * @lpsr_reg:		रेजिस्टर address क्रम regulator config at 'lpsr' state
 * @lpsr_mask:		value mask क्रम regulator voltages at 'lpsr' state
 * @lpsr_on_mask:	enable mask क्रम regulator at 'lpsr' state
 *
 * Description of ROHM PMICs voltage configuration रेजिस्टरs क्रम dअगरferent
 * प्रणाली states. This is used to correctly configure the PMIC at startup
 * based on values पढ़ो from DT.
 */
काष्ठा rohm_dvs_config अणु
	uपूर्णांक64_t level_map;
	अचिन्हित पूर्णांक run_reg;
	अचिन्हित पूर्णांक run_mask;
	अचिन्हित पूर्णांक run_on_mask;
	अचिन्हित पूर्णांक idle_reg;
	अचिन्हित पूर्णांक idle_mask;
	अचिन्हित पूर्णांक idle_on_mask;
	अचिन्हित पूर्णांक suspend_reg;
	अचिन्हित पूर्णांक suspend_mask;
	अचिन्हित पूर्णांक suspend_on_mask;
	अचिन्हित पूर्णांक lpsr_reg;
	अचिन्हित पूर्णांक lpsr_mask;
	अचिन्हित पूर्णांक lpsr_on_mask;
	अचिन्हित पूर्णांक snvs_reg;
	अचिन्हित पूर्णांक snvs_mask;
	अचिन्हित पूर्णांक snvs_on_mask;
पूर्ण;

#अगर IS_ENABLED(CONFIG_REGULATOR_ROHM)
पूर्णांक rohm_regulator_set_dvs_levels(स्थिर काष्ठा rohm_dvs_config *dvs,
				  काष्ठा device_node *np,
				  स्थिर काष्ठा regulator_desc *desc,
				  काष्ठा regmap *regmap);

#अन्यथा
अटल अंतरभूत पूर्णांक rohm_regulator_set_dvs_levels(स्थिर काष्ठा rohm_dvs_config *dvs,
						काष्ठा device_node *np,
						स्थिर काष्ठा regulator_desc *desc,
						काष्ठा regmap *regmap)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
