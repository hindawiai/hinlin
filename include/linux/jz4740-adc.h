<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __LINUX_JZ4740_ADC
#घोषणा __LINUX_JZ4740_ADC

काष्ठा device;

/*
 * jz4740_adc_set_config - Configure a JZ4740 adc device
 * @dev: Poपूर्णांकer to a jz4740-adc device
 * @mask: Mask क्रम the config value to be set
 * @val: Value to be set
 *
 * This function can be used by the JZ4740 ADC mfd cells to configure their
 * options in the shared config रेजिस्टर.
*/
पूर्णांक jz4740_adc_set_config(काष्ठा device *dev, uपूर्णांक32_t mask, uपूर्णांक32_t val);

#घोषणा JZ_ADC_CONFIG_SPZZ		BIT(31)
#घोषणा JZ_ADC_CONFIG_EX_IN		BIT(30)
#घोषणा JZ_ADC_CONFIG_DNUM_MASK		(0x7 << 16)
#घोषणा JZ_ADC_CONFIG_DMA_ENABLE	BIT(15)
#घोषणा JZ_ADC_CONFIG_XYZ_MASK		(0x2 << 13)
#घोषणा JZ_ADC_CONFIG_SAMPLE_NUM_MASK	(0x7 << 10)
#घोषणा JZ_ADC_CONFIG_CLKDIV_MASK	(0xf << 5)
#घोषणा JZ_ADC_CONFIG_BAT_MB		BIT(4)

#घोषणा JZ_ADC_CONFIG_DNUM(dnum)	((dnum) << 16)
#घोषणा JZ_ADC_CONFIG_XYZ_OFFSET(dnum)	((xyz) << 13)
#घोषणा JZ_ADC_CONFIG_SAMPLE_NUM(x)	((x) << 10)
#घोषणा JZ_ADC_CONFIG_CLKDIV(भाग)	((भाग) << 5)

#पूर्ण_अगर
