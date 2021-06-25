<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_MFD_TPS6586X_H
#घोषणा __LINUX_MFD_TPS6586X_H

#घोषणा TPS6586X_SLEW_RATE_INSTANTLY	0x00
#घोषणा TPS6586X_SLEW_RATE_110UV	0x01
#घोषणा TPS6586X_SLEW_RATE_220UV	0x02
#घोषणा TPS6586X_SLEW_RATE_440UV	0x03
#घोषणा TPS6586X_SLEW_RATE_880UV	0x04
#घोषणा TPS6586X_SLEW_RATE_1760UV	0x05
#घोषणा TPS6586X_SLEW_RATE_3520UV	0x06
#घोषणा TPS6586X_SLEW_RATE_7040UV	0x07

#घोषणा TPS6586X_SLEW_RATE_SET		0x08
#घोषणा TPS6586X_SLEW_RATE_MASK         0x07

/* VERSION CRC */
#घोषणा TPS658621A	0x15
#घोषणा TPS658621CD	0x2c
#घोषणा TPS658623	0x1b
#घोषणा TPS658624	0x0a
#घोषणा TPS658640	0x01
#घोषणा TPS658640v2	0x02
#घोषणा TPS658643	0x03

क्रमागत अणु
	TPS6586X_ID_SYS,
	TPS6586X_ID_SM_0,
	TPS6586X_ID_SM_1,
	TPS6586X_ID_SM_2,
	TPS6586X_ID_LDO_0,
	TPS6586X_ID_LDO_1,
	TPS6586X_ID_LDO_2,
	TPS6586X_ID_LDO_3,
	TPS6586X_ID_LDO_4,
	TPS6586X_ID_LDO_5,
	TPS6586X_ID_LDO_6,
	TPS6586X_ID_LDO_7,
	TPS6586X_ID_LDO_8,
	TPS6586X_ID_LDO_9,
	TPS6586X_ID_LDO_RTC,
	TPS6586X_ID_MAX_REGULATOR,
पूर्ण;

क्रमागत अणु
	TPS6586X_INT_PLDO_0,
	TPS6586X_INT_PLDO_1,
	TPS6586X_INT_PLDO_2,
	TPS6586X_INT_PLDO_3,
	TPS6586X_INT_PLDO_4,
	TPS6586X_INT_PLDO_5,
	TPS6586X_INT_PLDO_6,
	TPS6586X_INT_PLDO_7,
	TPS6586X_INT_COMP_DET,
	TPS6586X_INT_ADC,
	TPS6586X_INT_PLDO_8,
	TPS6586X_INT_PLDO_9,
	TPS6586X_INT_PSM_0,
	TPS6586X_INT_PSM_1,
	TPS6586X_INT_PSM_2,
	TPS6586X_INT_PSM_3,
	TPS6586X_INT_RTC_ALM1,
	TPS6586X_INT_ACUSB_OVP,
	TPS6586X_INT_USB_DET,
	TPS6586X_INT_AC_DET,
	TPS6586X_INT_BAT_DET,
	TPS6586X_INT_CHG_STAT,
	TPS6586X_INT_CHG_TEMP,
	TPS6586X_INT_PP,
	TPS6586X_INT_RESUME,
	TPS6586X_INT_LOW_SYS,
	TPS6586X_INT_RTC_ALM2,
पूर्ण;

काष्ठा tps6586x_settings अणु
	पूर्णांक slew_rate;
पूर्ण;

काष्ठा tps6586x_subdev_info अणु
	पूर्णांक		id;
	स्थिर अक्षर	*name;
	व्योम		*platक्रमm_data;
	काष्ठा device_node *of_node;
पूर्ण;

काष्ठा tps6586x_platक्रमm_data अणु
	पूर्णांक num_subdevs;
	काष्ठा tps6586x_subdev_info *subdevs;

	पूर्णांक gpio_base;
	पूर्णांक irq_base;
	bool pm_off;

	काष्ठा regulator_init_data *reg_init_data[TPS6586X_ID_MAX_REGULATOR];
पूर्ण;

/*
 * NOTE: the functions below are not पूर्णांकended क्रम use outside
 * of the TPS6586X sub-device drivers
 */
बाह्य पूर्णांक tps6586x_ग_लिखो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t val);
बाह्य पूर्णांक tps6586x_ग_लिखोs(काष्ठा device *dev, पूर्णांक reg, पूर्णांक len, uपूर्णांक8_t *val);
बाह्य पूर्णांक tps6586x_पढ़ो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t *val);
बाह्य पूर्णांक tps6586x_पढ़ोs(काष्ठा device *dev, पूर्णांक reg, पूर्णांक len, uपूर्णांक8_t *val);
बाह्य पूर्णांक tps6586x_set_bits(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t bit_mask);
बाह्य पूर्णांक tps6586x_clr_bits(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t bit_mask);
बाह्य पूर्णांक tps6586x_update(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t val,
			   uपूर्णांक8_t mask);
बाह्य पूर्णांक tps6586x_irq_get_virq(काष्ठा device *dev, पूर्णांक irq);
बाह्य पूर्णांक tps6586x_get_version(काष्ठा device *dev);

#पूर्ण_अगर /*__LINUX_MFD_TPS6586X_H */
