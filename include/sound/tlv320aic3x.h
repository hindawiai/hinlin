<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Platक्रमm data क्रम Texas Instruments TLV320AIC3x codec
 *
 * Author: Jarkko Nikula <jarkko.nikula@biपंचांगer.com>
 */
#अगर_अघोषित __TLV320AIC3x_H__
#घोषणा __TLV320AIC3x_H__

/* GPIO API */
क्रमागत अणु
	AIC3X_GPIO1_FUNC_DISABLED		= 0,
	AIC3X_GPIO1_FUNC_AUDIO_WORDCLK_ADC	= 1,
	AIC3X_GPIO1_FUNC_CLOCK_MUX		= 2,
	AIC3X_GPIO1_FUNC_CLOCK_MUX_DIV2		= 3,
	AIC3X_GPIO1_FUNC_CLOCK_MUX_DIV4		= 4,
	AIC3X_GPIO1_FUNC_CLOCK_MUX_DIV8		= 5,
	AIC3X_GPIO1_FUNC_SHORT_CIRCUIT_IRQ	= 6,
	AIC3X_GPIO1_FUNC_AGC_NOISE_IRQ		= 7,
	AIC3X_GPIO1_FUNC_INPUT			= 8,
	AIC3X_GPIO1_FUNC_OUTPUT			= 9,
	AIC3X_GPIO1_FUNC_DIGITAL_MIC_MODCLK	= 10,
	AIC3X_GPIO1_FUNC_AUDIO_WORDCLK		= 11,
	AIC3X_GPIO1_FUNC_BUTTON_IRQ		= 12,
	AIC3X_GPIO1_FUNC_HEADSET_DETECT_IRQ	= 13,
	AIC3X_GPIO1_FUNC_HEADSET_DETECT_OR_BUTTON_IRQ	= 14,
	AIC3X_GPIO1_FUNC_ALL_IRQ		= 16
पूर्ण;

क्रमागत अणु
	AIC3X_GPIO2_FUNC_DISABLED		= 0,
	AIC3X_GPIO2_FUNC_HEADSET_DETECT_IRQ	= 2,
	AIC3X_GPIO2_FUNC_INPUT			= 3,
	AIC3X_GPIO2_FUNC_OUTPUT			= 4,
	AIC3X_GPIO2_FUNC_DIGITAL_MIC_INPUT	= 5,
	AIC3X_GPIO2_FUNC_AUDIO_BITCLK		= 8,
	AIC3X_GPIO2_FUNC_HEADSET_DETECT_OR_BUTTON_IRQ = 9,
	AIC3X_GPIO2_FUNC_ALL_IRQ		= 10,
	AIC3X_GPIO2_FUNC_SHORT_CIRCUIT_OR_AGC_IRQ = 11,
	AIC3X_GPIO2_FUNC_HEADSET_OR_BUTTON_PRESS_OR_SHORT_CIRCUIT_IRQ = 12,
	AIC3X_GPIO2_FUNC_SHORT_CIRCUIT_IRQ	= 13,
	AIC3X_GPIO2_FUNC_AGC_NOISE_IRQ		= 14,
	AIC3X_GPIO2_FUNC_BUTTON_PRESS_IRQ	= 15
पूर्ण;

क्रमागत aic3x_micbias_voltage अणु
	AIC3X_MICBIAS_OFF = 0,
	AIC3X_MICBIAS_2_0V = 1,
	AIC3X_MICBIAS_2_5V = 2,
	AIC3X_MICBIAS_AVDDV = 3,
पूर्ण;

काष्ठा aic3x_setup_data अणु
	अचिन्हित पूर्णांक gpio_func[2];
पूर्ण;

काष्ठा aic3x_pdata अणु
	पूर्णांक gpio_reset; /* < 0 अगर not used */
	काष्ठा aic3x_setup_data *setup;

	/* Selects the micbias voltage */
	क्रमागत aic3x_micbias_voltage micbias_vg;
पूर्ण;

#पूर्ण_अगर
