<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * da9052 declarations क्रम DA9052 PMICs.
 *
 * Copyright(c) 2011 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#अगर_अघोषित __MFD_DA9052_DA9052_H
#घोषणा __MFD_DA9052_DA9052_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/list.h>
#समावेश <linux/mfd/core.h>

#समावेश <linux/mfd/da9052/reg.h>

/* Common - HWMON Channel Definations */
#घोषणा DA9052_ADC_VDDOUT	0
#घोषणा DA9052_ADC_ICH		1
#घोषणा DA9052_ADC_TBAT	2
#घोषणा DA9052_ADC_VBAT	3
#घोषणा DA9052_ADC_IN4		4
#घोषणा DA9052_ADC_IN5		5
#घोषणा DA9052_ADC_IN6		6
#घोषणा DA9052_ADC_TSI		7
#घोषणा DA9052_ADC_TJUNC	8
#घोषणा DA9052_ADC_VBBAT	9

/* TSI channel has its own 4 channel mux */
#घोषणा DA9052_ADC_TSI_XP	70
#घोषणा DA9052_ADC_TSI_XN	71
#घोषणा DA9052_ADC_TSI_YP	72
#घोषणा DA9052_ADC_TSI_YN	73

#घोषणा DA9052_IRQ_DCIN	0
#घोषणा DA9052_IRQ_VBUS	1
#घोषणा DA9052_IRQ_DCINREM	2
#घोषणा DA9052_IRQ_VBUSREM	3
#घोषणा DA9052_IRQ_VDDLOW	4
#घोषणा DA9052_IRQ_ALARM	5
#घोषणा DA9052_IRQ_SEQRDY	6
#घोषणा DA9052_IRQ_COMP1V2	7
#घोषणा DA9052_IRQ_NONKEY	8
#घोषणा DA9052_IRQ_IDFLOAT	9
#घोषणा DA9052_IRQ_IDGND	10
#घोषणा DA9052_IRQ_CHGEND	11
#घोषणा DA9052_IRQ_TBAT	12
#घोषणा DA9052_IRQ_ADC_EOM	13
#घोषणा DA9052_IRQ_PENDOWN	14
#घोषणा DA9052_IRQ_TSIREADY	15
#घोषणा DA9052_IRQ_GPI0	16
#घोषणा DA9052_IRQ_GPI1	17
#घोषणा DA9052_IRQ_GPI2	18
#घोषणा DA9052_IRQ_GPI3	19
#घोषणा DA9052_IRQ_GPI4	20
#घोषणा DA9052_IRQ_GPI5	21
#घोषणा DA9052_IRQ_GPI6	22
#घोषणा DA9052_IRQ_GPI7	23
#घोषणा DA9052_IRQ_GPI8	24
#घोषणा DA9052_IRQ_GPI9	25
#घोषणा DA9052_IRQ_GPI10	26
#घोषणा DA9052_IRQ_GPI11	27
#घोषणा DA9052_IRQ_GPI12	28
#घोषणा DA9052_IRQ_GPI13	29
#घोषणा DA9052_IRQ_GPI14	30
#घोषणा DA9052_IRQ_GPI15	31

क्रमागत da9052_chip_id अणु
	DA9052,
	DA9053_AA,
	DA9053_BA,
	DA9053_BB,
	DA9053_BC,
पूर्ण;

काष्ठा da9052_pdata;

काष्ठा da9052 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;

	काष्ठा mutex auxadc_lock;
	काष्ठा completion करोne;

	पूर्णांक irq_base;
	काष्ठा regmap_irq_chip_data *irq_data;
	u8 chip_id;

	पूर्णांक chip_irq;

	/* SOC I/O transfer related fixes क्रम DA9052/53 */
	पूर्णांक (*fix_io) (काष्ठा da9052 *da9052, अचिन्हित अक्षर reg);
पूर्ण;

/* ADC API */
पूर्णांक da9052_adc_manual_पढ़ो(काष्ठा da9052 *da9052, अचिन्हित अक्षर channel);
पूर्णांक da9052_adc_पढ़ो_temp(काष्ठा da9052 *da9052);

/* Device I/O API */
अटल अंतरभूत पूर्णांक da9052_reg_पढ़ो(काष्ठा da9052 *da9052, अचिन्हित अक्षर reg)
अणु
	पूर्णांक val, ret;

	ret = regmap_पढ़ो(da9052->regmap, reg, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (da9052->fix_io) अणु
		ret = da9052->fix_io(da9052, reg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक da9052_reg_ग_लिखो(काष्ठा da9052 *da9052, अचिन्हित अक्षर reg,
				    अचिन्हित अक्षर val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(da9052->regmap, reg, val);
	अगर (ret < 0)
		वापस ret;

	अगर (da9052->fix_io) अणु
		ret = da9052->fix_io(da9052, reg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक da9052_group_पढ़ो(काष्ठा da9052 *da9052, अचिन्हित अक्षर reg,
				     अचिन्हित reg_cnt, अचिन्हित अक्षर *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक i;

	क्रम (i = 0; i < reg_cnt; i++) अणु
		ret = regmap_पढ़ो(da9052->regmap, reg + i, &पंचांगp);
		val[i] = (अचिन्हित अक्षर)पंचांगp;
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (da9052->fix_io) अणु
		ret = da9052->fix_io(da9052, reg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक da9052_group_ग_लिखो(काष्ठा da9052 *da9052, अचिन्हित अक्षर reg,
				      अचिन्हित reg_cnt, अचिन्हित अक्षर *val)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < reg_cnt; i++) अणु
		ret = regmap_ग_लिखो(da9052->regmap, reg + i, val[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (da9052->fix_io) अणु
		ret = da9052->fix_io(da9052, reg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक da9052_reg_update(काष्ठा da9052 *da9052, अचिन्हित अक्षर reg,
				     अचिन्हित अक्षर bit_mask,
				     अचिन्हित अक्षर reg_val)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(da9052->regmap, reg, bit_mask, reg_val);
	अगर (ret < 0)
		वापस ret;

	अगर (da9052->fix_io) अणु
		ret = da9052->fix_io(da9052, reg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक da9052_device_init(काष्ठा da9052 *da9052, u8 chip_id);
व्योम da9052_device_निकास(काष्ठा da9052 *da9052);

बाह्य स्थिर काष्ठा regmap_config da9052_regmap_config;

पूर्णांक da9052_irq_init(काष्ठा da9052 *da9052);
पूर्णांक da9052_irq_निकास(काष्ठा da9052 *da9052);
पूर्णांक da9052_request_irq(काष्ठा da9052 *da9052, पूर्णांक irq, अक्षर *name,
			   irq_handler_t handler, व्योम *data);
व्योम da9052_मुक्त_irq(काष्ठा da9052 *da9052, पूर्णांक irq, व्योम *data);

पूर्णांक da9052_enable_irq(काष्ठा da9052 *da9052, पूर्णांक irq);
पूर्णांक da9052_disable_irq(काष्ठा da9052 *da9052, पूर्णांक irq);
पूर्णांक da9052_disable_irq_nosync(काष्ठा da9052 *da9052, पूर्णांक irq);

#पूर्ण_अगर /* __MFD_DA9052_DA9052_H */
