<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ADAU17X1_H__
#घोषणा __ADAU17X1_H__

#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_data/adau17x1.h>

#समावेश "sigmadsp.h"

क्रमागत adau17x1_type अणु
	ADAU1361,
	ADAU1761,
	ADAU1381,
	ADAU1781,
पूर्ण;

क्रमागत adau17x1_pll अणु
	ADAU17X1_PLL,
पूर्ण;

क्रमागत adau17x1_pll_src अणु
	ADAU17X1_PLL_SRC_MCLK,
पूर्ण;

क्रमागत adau17x1_clk_src अणु
	/* Automatically configure PLL based on the sample rate */
	ADAU17X1_CLK_SRC_PLL_AUTO,
	ADAU17X1_CLK_SRC_MCLK,
	ADAU17X1_CLK_SRC_PLL,
पूर्ण;

काष्ठा clk;

काष्ठा adau अणु
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक pll_freq;
	काष्ठा clk *mclk;

	क्रमागत adau17x1_clk_src clk_src;
	क्रमागत adau17x1_type type;
	व्योम (*चयन_mode)(काष्ठा device *dev);

	अचिन्हित पूर्णांक dai_fmt;

	uपूर्णांक8_t pll_regs[6];

	bool master;

	अचिन्हित पूर्णांक tdm_slot[2];
	bool dsp_bypass[2];

	काष्ठा regmap *regmap;
	काष्ठा sigmadsp *sigmadsp;
पूर्ण;

पूर्णांक adau17x1_add_widमाला_लो(काष्ठा snd_soc_component *component);
पूर्णांक adau17x1_add_routes(काष्ठा snd_soc_component *component);
पूर्णांक adau17x1_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
	क्रमागत adau17x1_type type, व्योम (*चयन_mode)(काष्ठा device *dev),
	स्थिर अक्षर *firmware_name);
व्योम adau17x1_हटाओ(काष्ठा device *dev);
पूर्णांक adau17x1_set_micbias_voltage(काष्ठा snd_soc_component *component,
	क्रमागत adau17x1_micbias_voltage micbias);
bool adau17x1_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
bool adau17x1_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
bool adau17x1_precious_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
पूर्णांक adau17x1_resume(काष्ठा snd_soc_component *component);

बाह्य स्थिर काष्ठा snd_soc_dai_ops adau17x1_dai_ops;

#घोषणा ADAU17X1_CLOCK_CONTROL			0x4000
#घोषणा ADAU17X1_PLL_CONTROL			0x4002
#घोषणा ADAU17X1_REC_POWER_MGMT			0x4009
#घोषणा ADAU17X1_MICBIAS			0x4010
#घोषणा ADAU17X1_SERIAL_PORT0			0x4015
#घोषणा ADAU17X1_SERIAL_PORT1			0x4016
#घोषणा ADAU17X1_CONVERTER0			0x4017
#घोषणा ADAU17X1_CONVERTER1			0x4018
#घोषणा ADAU17X1_LEFT_INPUT_DIGITAL_VOL		0x401a
#घोषणा ADAU17X1_RIGHT_INPUT_DIGITAL_VOL	0x401b
#घोषणा ADAU17X1_ADC_CONTROL			0x4019
#घोषणा ADAU17X1_PLAY_POWER_MGMT		0x4029
#घोषणा ADAU17X1_DAC_CONTROL0			0x402a
#घोषणा ADAU17X1_DAC_CONTROL1			0x402b
#घोषणा ADAU17X1_DAC_CONTROL2			0x402c
#घोषणा ADAU17X1_SERIAL_PORT_PAD		0x402d
#घोषणा ADAU17X1_CONTROL_PORT_PAD0		0x402f
#घोषणा ADAU17X1_CONTROL_PORT_PAD1		0x4030
#घोषणा ADAU17X1_DSP_SAMPLING_RATE		0x40eb
#घोषणा ADAU17X1_SERIAL_INPUT_ROUTE		0x40f2
#घोषणा ADAU17X1_SERIAL_OUTPUT_ROUTE		0x40f3
#घोषणा ADAU17X1_DSP_ENABLE			0x40f5
#घोषणा ADAU17X1_DSP_RUN			0x40f6
#घोषणा ADAU17X1_SERIAL_SAMPLING_RATE		0x40f8

#घोषणा ADAU17X1_SERIAL_PORT0_BCLK_POL		BIT(4)
#घोषणा ADAU17X1_SERIAL_PORT0_LRCLK_POL		BIT(3)
#घोषणा ADAU17X1_SERIAL_PORT0_MASTER		BIT(0)

#घोषणा ADAU17X1_SERIAL_PORT1_DELAY1		0x00
#घोषणा ADAU17X1_SERIAL_PORT1_DELAY0		0x01
#घोषणा ADAU17X1_SERIAL_PORT1_DELAY8		0x02
#घोषणा ADAU17X1_SERIAL_PORT1_DELAY16		0x03
#घोषणा ADAU17X1_SERIAL_PORT1_DELAY_MASK	0x03

#घोषणा ADAU17X1_CLOCK_CONTROL_INFREQ_MASK	0x6
#घोषणा ADAU17X1_CLOCK_CONTROL_CORECLK_SRC_PLL	BIT(3)
#घोषणा ADAU17X1_CLOCK_CONTROL_SYSCLK_EN	BIT(0)

#घोषणा ADAU17X1_SERIAL_PORT1_BCLK64		(0x0 << 5)
#घोषणा ADAU17X1_SERIAL_PORT1_BCLK32		(0x1 << 5)
#घोषणा ADAU17X1_SERIAL_PORT1_BCLK48		(0x2 << 5)
#घोषणा ADAU17X1_SERIAL_PORT1_BCLK128		(0x3 << 5)
#घोषणा ADAU17X1_SERIAL_PORT1_BCLK256		(0x4 << 5)
#घोषणा ADAU17X1_SERIAL_PORT1_BCLK_MASK		(0x7 << 5)

#घोषणा ADAU17X1_SERIAL_PORT0_STEREO		(0x0 << 1)
#घोषणा ADAU17X1_SERIAL_PORT0_TDM4		(0x1 << 1)
#घोषणा ADAU17X1_SERIAL_PORT0_TDM8		(0x2 << 1)
#घोषणा ADAU17X1_SERIAL_PORT0_TDM_MASK		(0x3 << 1)
#घोषणा ADAU17X1_SERIAL_PORT0_PULSE_MODE	BIT(5)

#घोषणा ADAU17X1_CONVERTER0_DAC_PAIR(x)		(((x) - 1) << 5)
#घोषणा ADAU17X1_CONVERTER0_DAC_PAIR_MASK	(0x3 << 5)
#घोषणा ADAU17X1_CONVERTER1_ADC_PAIR(x)		((x) - 1)
#घोषणा ADAU17X1_CONVERTER1_ADC_PAIR_MASK	0x3

#घोषणा ADAU17X1_CONVERTER0_CONVSR_MASK		0x7

#घोषणा ADAU17X1_CONVERTER0_ADOSR		BIT(3)


#पूर्ण_अगर
