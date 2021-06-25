<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Lochnagar pin and GPIO control
 *
 * Copyright (c) 2017-2018 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
 *
 * Author: Charles Keepax <ckeepax@खोलोsource.cirrus.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश <linux/mfd/lochnagar.h>
#समावेश <linux/mfd/lochnagar1_regs.h>
#समावेश <linux/mfd/lochnagar2_regs.h>

#समावेश <dt-bindings/pinctrl/lochnagar.h>

#समावेश "../pinctrl-utils.h"

#घोषणा LN2_NUM_GPIO_CHANNELS	16

#घोषणा LN_CDC_AIF1_STR		"codec-aif1"
#घोषणा LN_CDC_AIF2_STR		"codec-aif2"
#घोषणा LN_CDC_AIF3_STR		"codec-aif3"
#घोषणा LN_DSP_AIF1_STR		"dsp-aif1"
#घोषणा LN_DSP_AIF2_STR		"dsp-aif2"
#घोषणा LN_PSIA1_STR		"psia1"
#घोषणा LN_PSIA2_STR		"psia2"
#घोषणा LN_GF_AIF1_STR		"gf-aif1"
#घोषणा LN_GF_AIF2_STR		"gf-aif2"
#घोषणा LN_GF_AIF3_STR		"gf-aif3"
#घोषणा LN_GF_AIF4_STR		"gf-aif4"
#घोषणा LN_SPDIF_AIF_STR	"spdif-aif"
#घोषणा LN_USB_AIF1_STR		"usb-aif1"
#घोषणा LN_USB_AIF2_STR		"usb-aif2"
#घोषणा LN_ADAT_AIF_STR		"adat-aif"
#घोषणा LN_SOUNDCARD_AIF_STR	"soundcard-aif"

#घोषणा LN_PIN_GPIO(REV, ID, NAME, REG, SHIFT, INVERT) \
अटल स्थिर काष्ठा lochnagar_pin lochnagar##REV##_##ID##_pin = अणु \
	.name = NAME, .type = LN_PTYPE_GPIO, .reg = LOCHNAGAR##REV##_##REG, \
	.shअगरt = LOCHNAGAR##REV##_##SHIFT##_SHIFT, .invert = INVERT, \
पूर्ण

#घोषणा LN_PIN_SAIF(REV, ID, NAME) \
अटल स्थिर काष्ठा lochnagar_pin lochnagar##REV##_##ID##_pin = \
	अणु .name = NAME, .type = LN_PTYPE_AIF, पूर्ण

#घोषणा LN_PIN_AIF(REV, ID) \
	LN_PIN_SAIF(REV, ID##_BCLK,  LN_##ID##_STR"-bclk"); \
	LN_PIN_SAIF(REV, ID##_LRCLK, LN_##ID##_STR"-lrclk"); \
	LN_PIN_SAIF(REV, ID##_RXDAT, LN_##ID##_STR"-rxdat"); \
	LN_PIN_SAIF(REV, ID##_TXDAT, LN_##ID##_STR"-txdat")

#घोषणा LN1_PIN_GPIO(ID, NAME, REG, SHIFT, INVERT) \
	LN_PIN_GPIO(1, ID, NAME, REG, SHIFT, INVERT)

#घोषणा LN1_PIN_MUX(ID, NAME) \
अटल स्थिर काष्ठा lochnagar_pin lochnagar1_##ID##_pin = \
	अणु .name = NAME, .type = LN_PTYPE_MUX, .reg = LOCHNAGAR1_##ID, पूर्ण

#घोषणा LN1_PIN_AIF(ID) LN_PIN_AIF(1, ID)

#घोषणा LN2_PIN_GPIO(ID, NAME, REG, SHIFT, INVERT) \
	LN_PIN_GPIO(2, ID, NAME, REG, SHIFT, INVERT)

#घोषणा LN2_PIN_MUX(ID, NAME) \
अटल स्थिर काष्ठा lochnagar_pin lochnagar2_##ID##_pin = \
	अणु .name = NAME, .type = LN_PTYPE_MUX, .reg = LOCHNAGAR2_GPIO_##ID, पूर्ण

#घोषणा LN2_PIN_AIF(ID) LN_PIN_AIF(2, ID)

#घोषणा LN2_PIN_GAI(ID) \
	LN2_PIN_MUX(ID##_BCLK,  LN_##ID##_STR"-bclk"); \
	LN2_PIN_MUX(ID##_LRCLK, LN_##ID##_STR"-lrclk"); \
	LN2_PIN_MUX(ID##_RXDAT, LN_##ID##_STR"-rxdat"); \
	LN2_PIN_MUX(ID##_TXDAT, LN_##ID##_STR"-txdat")

#घोषणा LN_PIN(REV, ID) [LOCHNAGAR##REV##_PIN_##ID] = अणु \
	.number = LOCHNAGAR##REV##_PIN_##ID, \
	.name = lochnagar##REV##_##ID##_pin.name, \
	.drv_data = (व्योम *)&lochnagar##REV##_##ID##_pin, \
पूर्ण

#घोषणा LN1_PIN(ID) LN_PIN(1, ID)
#घोषणा LN2_PIN(ID) LN_PIN(2, ID)

#घोषणा LN_PINS(REV, ID) \
	LN_PIN(REV, ID##_BCLK), LN_PIN(REV, ID##_LRCLK), \
	LN_PIN(REV, ID##_RXDAT), LN_PIN(REV, ID##_TXDAT)

#घोषणा LN1_PINS(ID) LN_PINS(1, ID)
#घोषणा LN2_PINS(ID) LN_PINS(2, ID)

क्रमागत अणु
	LOCHNAGAR1_PIN_GF_GPIO2 = LOCHNAGAR1_PIN_NUM_GPIOS,
	LOCHNAGAR1_PIN_GF_GPIO3,
	LOCHNAGAR1_PIN_GF_GPIO7,
	LOCHNAGAR1_PIN_LED1,
	LOCHNAGAR1_PIN_LED2,
	LOCHNAGAR1_PIN_CDC_AIF1_BCLK,
	LOCHNAGAR1_PIN_CDC_AIF1_LRCLK,
	LOCHNAGAR1_PIN_CDC_AIF1_RXDAT,
	LOCHNAGAR1_PIN_CDC_AIF1_TXDAT,
	LOCHNAGAR1_PIN_CDC_AIF2_BCLK,
	LOCHNAGAR1_PIN_CDC_AIF2_LRCLK,
	LOCHNAGAR1_PIN_CDC_AIF2_RXDAT,
	LOCHNAGAR1_PIN_CDC_AIF2_TXDAT,
	LOCHNAGAR1_PIN_CDC_AIF3_BCLK,
	LOCHNAGAR1_PIN_CDC_AIF3_LRCLK,
	LOCHNAGAR1_PIN_CDC_AIF3_RXDAT,
	LOCHNAGAR1_PIN_CDC_AIF3_TXDAT,
	LOCHNAGAR1_PIN_DSP_AIF1_BCLK,
	LOCHNAGAR1_PIN_DSP_AIF1_LRCLK,
	LOCHNAGAR1_PIN_DSP_AIF1_RXDAT,
	LOCHNAGAR1_PIN_DSP_AIF1_TXDAT,
	LOCHNAGAR1_PIN_DSP_AIF2_BCLK,
	LOCHNAGAR1_PIN_DSP_AIF2_LRCLK,
	LOCHNAGAR1_PIN_DSP_AIF2_RXDAT,
	LOCHNAGAR1_PIN_DSP_AIF2_TXDAT,
	LOCHNAGAR1_PIN_PSIA1_BCLK,
	LOCHNAGAR1_PIN_PSIA1_LRCLK,
	LOCHNAGAR1_PIN_PSIA1_RXDAT,
	LOCHNAGAR1_PIN_PSIA1_TXDAT,
	LOCHNAGAR1_PIN_PSIA2_BCLK,
	LOCHNAGAR1_PIN_PSIA2_LRCLK,
	LOCHNAGAR1_PIN_PSIA2_RXDAT,
	LOCHNAGAR1_PIN_PSIA2_TXDAT,
	LOCHNAGAR1_PIN_SPDIF_AIF_BCLK,
	LOCHNAGAR1_PIN_SPDIF_AIF_LRCLK,
	LOCHNAGAR1_PIN_SPDIF_AIF_RXDAT,
	LOCHNAGAR1_PIN_SPDIF_AIF_TXDAT,
	LOCHNAGAR1_PIN_GF_AIF3_BCLK,
	LOCHNAGAR1_PIN_GF_AIF3_RXDAT,
	LOCHNAGAR1_PIN_GF_AIF3_LRCLK,
	LOCHNAGAR1_PIN_GF_AIF3_TXDAT,
	LOCHNAGAR1_PIN_GF_AIF4_BCLK,
	LOCHNAGAR1_PIN_GF_AIF4_RXDAT,
	LOCHNAGAR1_PIN_GF_AIF4_LRCLK,
	LOCHNAGAR1_PIN_GF_AIF4_TXDAT,
	LOCHNAGAR1_PIN_GF_AIF1_BCLK,
	LOCHNAGAR1_PIN_GF_AIF1_RXDAT,
	LOCHNAGAR1_PIN_GF_AIF1_LRCLK,
	LOCHNAGAR1_PIN_GF_AIF1_TXDAT,
	LOCHNAGAR1_PIN_GF_AIF2_BCLK,
	LOCHNAGAR1_PIN_GF_AIF2_RXDAT,
	LOCHNAGAR1_PIN_GF_AIF2_LRCLK,
	LOCHNAGAR1_PIN_GF_AIF2_TXDAT,

	LOCHNAGAR2_PIN_SPDIF_AIF_BCLK = LOCHNAGAR2_PIN_NUM_GPIOS,
	LOCHNAGAR2_PIN_SPDIF_AIF_LRCLK,
	LOCHNAGAR2_PIN_SPDIF_AIF_RXDAT,
	LOCHNAGAR2_PIN_SPDIF_AIF_TXDAT,
	LOCHNAGAR2_PIN_USB_AIF1_BCLK,
	LOCHNAGAR2_PIN_USB_AIF1_LRCLK,
	LOCHNAGAR2_PIN_USB_AIF1_RXDAT,
	LOCHNAGAR2_PIN_USB_AIF1_TXDAT,
	LOCHNAGAR2_PIN_USB_AIF2_BCLK,
	LOCHNAGAR2_PIN_USB_AIF2_LRCLK,
	LOCHNAGAR2_PIN_USB_AIF2_RXDAT,
	LOCHNAGAR2_PIN_USB_AIF2_TXDAT,
	LOCHNAGAR2_PIN_ADAT_AIF_BCLK,
	LOCHNAGAR2_PIN_ADAT_AIF_LRCLK,
	LOCHNAGAR2_PIN_ADAT_AIF_RXDAT,
	LOCHNAGAR2_PIN_ADAT_AIF_TXDAT,
	LOCHNAGAR2_PIN_SOUNDCARD_AIF_BCLK,
	LOCHNAGAR2_PIN_SOUNDCARD_AIF_LRCLK,
	LOCHNAGAR2_PIN_SOUNDCARD_AIF_RXDAT,
	LOCHNAGAR2_PIN_SOUNDCARD_AIF_TXDAT,
पूर्ण;

क्रमागत lochnagar_pin_type अणु
	LN_PTYPE_GPIO,
	LN_PTYPE_MUX,
	LN_PTYPE_AIF,
	LN_PTYPE_COUNT,
पूर्ण;

काष्ठा lochnagar_pin अणु
	स्थिर अक्षर name[20];

	क्रमागत lochnagar_pin_type type;

	अचिन्हित पूर्णांक reg;
	पूर्णांक shअगरt;
	bool invert;
पूर्ण;

LN1_PIN_GPIO(CDC_RESET,    "codec-reset",    RST,      CDC_RESET,    1);
LN1_PIN_GPIO(DSP_RESET,    "dsp-reset",      RST,      DSP_RESET,    1);
LN1_PIN_GPIO(CDC_CIF1MODE, "codec-cif1mode", I2C_CTRL, CDC_CIF_MODE, 0);
LN1_PIN_MUX(GF_GPIO2,      "gf-gpio2");
LN1_PIN_MUX(GF_GPIO3,      "gf-gpio3");
LN1_PIN_MUX(GF_GPIO7,      "gf-gpio7");
LN1_PIN_MUX(LED1,          "led1");
LN1_PIN_MUX(LED2,          "led2");
LN1_PIN_AIF(CDC_AIF1);
LN1_PIN_AIF(CDC_AIF2);
LN1_PIN_AIF(CDC_AIF3);
LN1_PIN_AIF(DSP_AIF1);
LN1_PIN_AIF(DSP_AIF2);
LN1_PIN_AIF(PSIA1);
LN1_PIN_AIF(PSIA2);
LN1_PIN_AIF(SPDIF_AIF);
LN1_PIN_AIF(GF_AIF1);
LN1_PIN_AIF(GF_AIF2);
LN1_PIN_AIF(GF_AIF3);
LN1_PIN_AIF(GF_AIF4);

LN2_PIN_GPIO(CDC_RESET,    "codec-reset",    MINICARD_RESETS, CDC_RESET,     1);
LN2_PIN_GPIO(DSP_RESET,    "dsp-reset",      MINICARD_RESETS, DSP_RESET,     1);
LN2_PIN_GPIO(CDC_CIF1MODE, "codec-cif1mode", COMMS_CTRL4,     CDC_CIF1MODE,  0);
LN2_PIN_GPIO(CDC_LDOENA,   "codec-ldoena",   POWER_CTRL,      PWR_ENA,       0);
LN2_PIN_GPIO(SPDIF_HWMODE, "spdif-hwmode",   SPDIF_CTRL,      SPDIF_HWMODE,  0);
LN2_PIN_GPIO(SPDIF_RESET,  "spdif-reset",    SPDIF_CTRL,      SPDIF_RESET,   1);
LN2_PIN_MUX(FPGA_GPIO1,    "fpga-gpio1");
LN2_PIN_MUX(FPGA_GPIO2,    "fpga-gpio2");
LN2_PIN_MUX(FPGA_GPIO3,    "fpga-gpio3");
LN2_PIN_MUX(FPGA_GPIO4,    "fpga-gpio4");
LN2_PIN_MUX(FPGA_GPIO5,    "fpga-gpio5");
LN2_PIN_MUX(FPGA_GPIO6,    "fpga-gpio6");
LN2_PIN_MUX(CDC_GPIO1,     "codec-gpio1");
LN2_PIN_MUX(CDC_GPIO2,     "codec-gpio2");
LN2_PIN_MUX(CDC_GPIO3,     "codec-gpio3");
LN2_PIN_MUX(CDC_GPIO4,     "codec-gpio4");
LN2_PIN_MUX(CDC_GPIO5,     "codec-gpio5");
LN2_PIN_MUX(CDC_GPIO6,     "codec-gpio6");
LN2_PIN_MUX(CDC_GPIO7,     "codec-gpio7");
LN2_PIN_MUX(CDC_GPIO8,     "codec-gpio8");
LN2_PIN_MUX(DSP_GPIO1,     "dsp-gpio1");
LN2_PIN_MUX(DSP_GPIO2,     "dsp-gpio2");
LN2_PIN_MUX(DSP_GPIO3,     "dsp-gpio3");
LN2_PIN_MUX(DSP_GPIO4,     "dsp-gpio4");
LN2_PIN_MUX(DSP_GPIO5,     "dsp-gpio5");
LN2_PIN_MUX(DSP_GPIO6,     "dsp-gpio6");
LN2_PIN_MUX(GF_GPIO2,      "gf-gpio2");
LN2_PIN_MUX(GF_GPIO3,      "gf-gpio3");
LN2_PIN_MUX(GF_GPIO7,      "gf-gpio7");
LN2_PIN_MUX(DSP_UART1_RX,  "dsp-uart1-rx");
LN2_PIN_MUX(DSP_UART1_TX,  "dsp-uart1-tx");
LN2_PIN_MUX(DSP_UART2_RX,  "dsp-uart2-rx");
LN2_PIN_MUX(DSP_UART2_TX,  "dsp-uart2-tx");
LN2_PIN_MUX(GF_UART2_RX,   "gf-uart2-rx");
LN2_PIN_MUX(GF_UART2_TX,   "gf-uart2-tx");
LN2_PIN_MUX(USB_UART_RX,   "usb-uart-rx");
LN2_PIN_MUX(CDC_PDMCLK1,   "codec-pdmclk1");
LN2_PIN_MUX(CDC_PDMDAT1,   "codec-pdmdat1");
LN2_PIN_MUX(CDC_PDMCLK2,   "codec-pdmclk2");
LN2_PIN_MUX(CDC_PDMDAT2,   "codec-pdmdat2");
LN2_PIN_MUX(CDC_DMICCLK1,  "codec-dmicclk1");
LN2_PIN_MUX(CDC_DMICDAT1,  "codec-dmicdat1");
LN2_PIN_MUX(CDC_DMICCLK2,  "codec-dmicclk2");
LN2_PIN_MUX(CDC_DMICDAT2,  "codec-dmicdat2");
LN2_PIN_MUX(CDC_DMICCLK3,  "codec-dmicclk3");
LN2_PIN_MUX(CDC_DMICDAT3,  "codec-dmicdat3");
LN2_PIN_MUX(CDC_DMICCLK4,  "codec-dmicclk4");
LN2_PIN_MUX(CDC_DMICDAT4,  "codec-dmicdat4");
LN2_PIN_MUX(DSP_DMICCLK1,  "dsp-dmicclk1");
LN2_PIN_MUX(DSP_DMICDAT1,  "dsp-dmicdat1");
LN2_PIN_MUX(DSP_DMICCLK2,  "dsp-dmicclk2");
LN2_PIN_MUX(DSP_DMICDAT2,  "dsp-dmicdat2");
LN2_PIN_MUX(I2C2_SCL,      "i2c2-scl");
LN2_PIN_MUX(I2C2_SDA,      "i2c2-sda");
LN2_PIN_MUX(I2C3_SCL,      "i2c3-scl");
LN2_PIN_MUX(I2C3_SDA,      "i2c3-sda");
LN2_PIN_MUX(I2C4_SCL,      "i2c4-scl");
LN2_PIN_MUX(I2C4_SDA,      "i2c4-sda");
LN2_PIN_MUX(DSP_STANDBY,   "dsp-standby");
LN2_PIN_MUX(CDC_MCLK1,     "codec-mclk1");
LN2_PIN_MUX(CDC_MCLK2,     "codec-mclk2");
LN2_PIN_MUX(DSP_CLKIN,     "dsp-clkin");
LN2_PIN_MUX(PSIA1_MCLK,    "psia1-mclk");
LN2_PIN_MUX(PSIA2_MCLK,    "psia2-mclk");
LN2_PIN_MUX(GF_GPIO1,      "gf-gpio1");
LN2_PIN_MUX(GF_GPIO5,      "gf-gpio5");
LN2_PIN_MUX(DSP_GPIO20,    "dsp-gpio20");
LN2_PIN_GAI(CDC_AIF1);
LN2_PIN_GAI(CDC_AIF2);
LN2_PIN_GAI(CDC_AIF3);
LN2_PIN_GAI(DSP_AIF1);
LN2_PIN_GAI(DSP_AIF2);
LN2_PIN_GAI(PSIA1);
LN2_PIN_GAI(PSIA2);
LN2_PIN_GAI(GF_AIF1);
LN2_PIN_GAI(GF_AIF2);
LN2_PIN_GAI(GF_AIF3);
LN2_PIN_GAI(GF_AIF4);
LN2_PIN_AIF(SPDIF_AIF);
LN2_PIN_AIF(USB_AIF1);
LN2_PIN_AIF(USB_AIF2);
LN2_PIN_AIF(ADAT_AIF);
LN2_PIN_AIF(SOUNDCARD_AIF);

अटल स्थिर काष्ठा pinctrl_pin_desc lochnagar1_pins[] = अणु
	LN1_PIN(CDC_RESET),      LN1_PIN(DSP_RESET),    LN1_PIN(CDC_CIF1MODE),
	LN1_PIN(GF_GPIO2),       LN1_PIN(GF_GPIO3),     LN1_PIN(GF_GPIO7),
	LN1_PIN(LED1),           LN1_PIN(LED2),
	LN1_PINS(CDC_AIF1),      LN1_PINS(CDC_AIF2),    LN1_PINS(CDC_AIF3),
	LN1_PINS(DSP_AIF1),      LN1_PINS(DSP_AIF2),
	LN1_PINS(PSIA1),         LN1_PINS(PSIA2),
	LN1_PINS(SPDIF_AIF),
	LN1_PINS(GF_AIF1),       LN1_PINS(GF_AIF2),
	LN1_PINS(GF_AIF3),       LN1_PINS(GF_AIF4),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc lochnagar2_pins[] = अणु
	LN2_PIN(CDC_RESET),      LN2_PIN(DSP_RESET),    LN2_PIN(CDC_CIF1MODE),
	LN2_PIN(CDC_LDOENA),
	LN2_PIN(SPDIF_HWMODE),   LN2_PIN(SPDIF_RESET),
	LN2_PIN(FPGA_GPIO1),     LN2_PIN(FPGA_GPIO2),   LN2_PIN(FPGA_GPIO3),
	LN2_PIN(FPGA_GPIO4),     LN2_PIN(FPGA_GPIO5),   LN2_PIN(FPGA_GPIO6),
	LN2_PIN(CDC_GPIO1),      LN2_PIN(CDC_GPIO2),    LN2_PIN(CDC_GPIO3),
	LN2_PIN(CDC_GPIO4),      LN2_PIN(CDC_GPIO5),    LN2_PIN(CDC_GPIO6),
	LN2_PIN(CDC_GPIO7),      LN2_PIN(CDC_GPIO8),
	LN2_PIN(DSP_GPIO1),      LN2_PIN(DSP_GPIO2),    LN2_PIN(DSP_GPIO3),
	LN2_PIN(DSP_GPIO4),      LN2_PIN(DSP_GPIO5),    LN2_PIN(DSP_GPIO6),
	LN2_PIN(DSP_GPIO20),
	LN2_PIN(GF_GPIO1),       LN2_PIN(GF_GPIO2),     LN2_PIN(GF_GPIO3),
	LN2_PIN(GF_GPIO5),       LN2_PIN(GF_GPIO7),
	LN2_PINS(CDC_AIF1),      LN2_PINS(CDC_AIF2),    LN2_PINS(CDC_AIF3),
	LN2_PINS(DSP_AIF1),      LN2_PINS(DSP_AIF2),
	LN2_PINS(PSIA1),         LN2_PINS(PSIA2),
	LN2_PINS(GF_AIF1),       LN2_PINS(GF_AIF2),
	LN2_PINS(GF_AIF3),       LN2_PINS(GF_AIF4),
	LN2_PIN(DSP_UART1_RX),   LN2_PIN(DSP_UART1_TX),
	LN2_PIN(DSP_UART2_RX),   LN2_PIN(DSP_UART2_TX),
	LN2_PIN(GF_UART2_RX),    LN2_PIN(GF_UART2_TX),
	LN2_PIN(USB_UART_RX),
	LN2_PIN(CDC_PDMCLK1),    LN2_PIN(CDC_PDMDAT1),
	LN2_PIN(CDC_PDMCLK2),    LN2_PIN(CDC_PDMDAT2),
	LN2_PIN(CDC_DMICCLK1),   LN2_PIN(CDC_DMICDAT1),
	LN2_PIN(CDC_DMICCLK2),   LN2_PIN(CDC_DMICDAT2),
	LN2_PIN(CDC_DMICCLK3),   LN2_PIN(CDC_DMICDAT3),
	LN2_PIN(CDC_DMICCLK4),   LN2_PIN(CDC_DMICDAT4),
	LN2_PIN(DSP_DMICCLK1),   LN2_PIN(DSP_DMICDAT1),
	LN2_PIN(DSP_DMICCLK2),   LN2_PIN(DSP_DMICDAT2),
	LN2_PIN(I2C2_SCL),       LN2_PIN(I2C2_SDA),
	LN2_PIN(I2C3_SCL),       LN2_PIN(I2C3_SDA),
	LN2_PIN(I2C4_SCL),       LN2_PIN(I2C4_SDA),
	LN2_PIN(DSP_STANDBY),
	LN2_PIN(CDC_MCLK1),      LN2_PIN(CDC_MCLK2),
	LN2_PIN(DSP_CLKIN),
	LN2_PIN(PSIA1_MCLK),     LN2_PIN(PSIA2_MCLK),
	LN2_PINS(SPDIF_AIF),
	LN2_PINS(USB_AIF1),      LN2_PINS(USB_AIF2),
	LN2_PINS(ADAT_AIF),
	LN2_PINS(SOUNDCARD_AIF),
पूर्ण;

#घोषणा LN_AIF_PINS(REV, ID) \
	LOCHNAGAR##REV##_PIN_##ID##_BCLK, \
	LOCHNAGAR##REV##_PIN_##ID##_LRCLK, \
	LOCHNAGAR##REV##_PIN_##ID##_TXDAT, \
	LOCHNAGAR##REV##_PIN_##ID##_RXDAT,

#घोषणा LN1_AIF(ID, CTRL) \
अटल स्थिर काष्ठा lochnagar_aअगर lochnagar1_##ID##_aअगर = अणु \
	.name = LN_##ID##_STR, \
	.pins = अणु LN_AIF_PINS(1, ID) पूर्ण, \
	.src_reg = LOCHNAGAR1_##ID##_SEL, \
	.src_mask = LOCHNAGAR1_SRC_MASK, \
	.ctrl_reg = LOCHNAGAR1_##CTRL, \
	.ena_mask = LOCHNAGAR1_##ID##_ENA_MASK, \
	.master_mask = LOCHNAGAR1_##ID##_LRCLK_सूची_MASK | \
		       LOCHNAGAR1_##ID##_BCLK_सूची_MASK, \
पूर्ण

#घोषणा LN2_AIF(ID) \
अटल स्थिर काष्ठा lochnagar_aअगर lochnagar2_##ID##_aअगर = अणु \
	.name = LN_##ID##_STR, \
	.pins = अणु LN_AIF_PINS(2, ID) पूर्ण, \
	.src_reg = LOCHNAGAR2_##ID##_CTRL,  \
	.src_mask = LOCHNAGAR2_AIF_SRC_MASK, \
	.ctrl_reg = LOCHNAGAR2_##ID##_CTRL, \
	.ena_mask = LOCHNAGAR2_AIF_ENA_MASK, \
	.master_mask = LOCHNAGAR2_AIF_LRCLK_सूची_MASK | \
		       LOCHNAGAR2_AIF_BCLK_सूची_MASK, \
पूर्ण

काष्ठा lochnagar_aअगर अणु
	स्थिर अक्षर name[16];

	अचिन्हित पूर्णांक pins[4];

	u16 src_reg;
	u16 src_mask;

	u16 ctrl_reg;
	u16 ena_mask;
	u16 master_mask;
पूर्ण;

LN1_AIF(CDC_AIF1,      CDC_AIF_CTRL1);
LN1_AIF(CDC_AIF2,      CDC_AIF_CTRL1);
LN1_AIF(CDC_AIF3,      CDC_AIF_CTRL2);
LN1_AIF(DSP_AIF1,      DSP_AIF);
LN1_AIF(DSP_AIF2,      DSP_AIF);
LN1_AIF(PSIA1,         PSIA_AIF);
LN1_AIF(PSIA2,         PSIA_AIF);
LN1_AIF(GF_AIF1,       GF_AIF1);
LN1_AIF(GF_AIF2,       GF_AIF2);
LN1_AIF(GF_AIF3,       GF_AIF1);
LN1_AIF(GF_AIF4,       GF_AIF2);
LN1_AIF(SPDIF_AIF,     EXT_AIF_CTRL);

LN2_AIF(CDC_AIF1);
LN2_AIF(CDC_AIF2);
LN2_AIF(CDC_AIF3);
LN2_AIF(DSP_AIF1);
LN2_AIF(DSP_AIF2);
LN2_AIF(PSIA1);
LN2_AIF(PSIA2);
LN2_AIF(GF_AIF1);
LN2_AIF(GF_AIF2);
LN2_AIF(GF_AIF3);
LN2_AIF(GF_AIF4);
LN2_AIF(SPDIF_AIF);
LN2_AIF(USB_AIF1);
LN2_AIF(USB_AIF2);
LN2_AIF(ADAT_AIF);
LN2_AIF(SOUNDCARD_AIF);

#घोषणा LN2_OP_AIF	0x00
#घोषणा LN2_OP_GPIO	0xFE

#घोषणा LN_FUNC(NAME, TYPE, OP) \
	अणु .name = NAME, .type = LN_FTYPE_##TYPE, .op = OP पूर्ण

#घोषणा LN_FUNC_PIN(REV, ID, OP) \
	LN_FUNC(lochnagar##REV##_##ID##_pin.name, PIN, OP)

#घोषणा LN1_FUNC_PIN(ID, OP) LN_FUNC_PIN(1, ID, OP)
#घोषणा LN2_FUNC_PIN(ID, OP) LN_FUNC_PIN(2, ID, OP)

#घोषणा LN_FUNC_AIF(REV, ID, OP) \
	LN_FUNC(lochnagar##REV##_##ID##_aअगर.name, AIF, OP)

#घोषणा LN1_FUNC_AIF(ID, OP) LN_FUNC_AIF(1, ID, OP)
#घोषणा LN2_FUNC_AIF(ID, OP) LN_FUNC_AIF(2, ID, OP)

#घोषणा LN2_FUNC_GAI(ID, OP, BOP, LROP, RXOP, TXOP) \
	LN2_FUNC_AIF(ID, OP), \
	LN_FUNC(lochnagar2_##ID##_BCLK_pin.name, PIN, BOP), \
	LN_FUNC(lochnagar2_##ID##_LRCLK_pin.name, PIN, LROP), \
	LN_FUNC(lochnagar2_##ID##_RXDAT_pin.name, PIN, RXOP), \
	LN_FUNC(lochnagar2_##ID##_TXDAT_pin.name, PIN, TXOP)

क्रमागत lochnagar_func_type अणु
	LN_FTYPE_PIN,
	LN_FTYPE_AIF,
	LN_FTYPE_COUNT,
पूर्ण;

काष्ठा lochnagar_func अणु
	स्थिर अक्षर * स्थिर name;

	क्रमागत lochnagar_func_type type;

	u8 op;
पूर्ण;

अटल स्थिर काष्ठा lochnagar_func lochnagar1_funcs[] = अणु
	LN_FUNC("dsp-gpio1",       PIN, 0x01),
	LN_FUNC("dsp-gpio2",       PIN, 0x02),
	LN_FUNC("dsp-gpio3",       PIN, 0x03),
	LN_FUNC("codec-gpio1",     PIN, 0x04),
	LN_FUNC("codec-gpio2",     PIN, 0x05),
	LN_FUNC("codec-gpio3",     PIN, 0x06),
	LN_FUNC("codec-gpio4",     PIN, 0x07),
	LN_FUNC("codec-gpio5",     PIN, 0x08),
	LN_FUNC("codec-gpio6",     PIN, 0x09),
	LN_FUNC("codec-gpio7",     PIN, 0x0A),
	LN_FUNC("codec-gpio8",     PIN, 0x0B),
	LN1_FUNC_PIN(GF_GPIO2,          0x0C),
	LN1_FUNC_PIN(GF_GPIO3,          0x0D),
	LN1_FUNC_PIN(GF_GPIO7,          0x0E),

	LN1_FUNC_AIF(SPDIF_AIF,         0x01),
	LN1_FUNC_AIF(PSIA1,             0x02),
	LN1_FUNC_AIF(PSIA2,             0x03),
	LN1_FUNC_AIF(CDC_AIF1,          0x04),
	LN1_FUNC_AIF(CDC_AIF2,          0x05),
	LN1_FUNC_AIF(CDC_AIF3,          0x06),
	LN1_FUNC_AIF(DSP_AIF1,          0x07),
	LN1_FUNC_AIF(DSP_AIF2,          0x08),
	LN1_FUNC_AIF(GF_AIF3,           0x09),
	LN1_FUNC_AIF(GF_AIF4,           0x0A),
	LN1_FUNC_AIF(GF_AIF1,           0x0B),
	LN1_FUNC_AIF(GF_AIF2,           0x0C),
पूर्ण;

अटल स्थिर काष्ठा lochnagar_func lochnagar2_funcs[] = अणु
	LN_FUNC("aif",             PIN, LN2_OP_AIF),
	LN2_FUNC_PIN(FPGA_GPIO1,        0x01),
	LN2_FUNC_PIN(FPGA_GPIO2,        0x02),
	LN2_FUNC_PIN(FPGA_GPIO3,        0x03),
	LN2_FUNC_PIN(FPGA_GPIO4,        0x04),
	LN2_FUNC_PIN(FPGA_GPIO5,        0x05),
	LN2_FUNC_PIN(FPGA_GPIO6,        0x06),
	LN2_FUNC_PIN(CDC_GPIO1,         0x07),
	LN2_FUNC_PIN(CDC_GPIO2,         0x08),
	LN2_FUNC_PIN(CDC_GPIO3,         0x09),
	LN2_FUNC_PIN(CDC_GPIO4,         0x0A),
	LN2_FUNC_PIN(CDC_GPIO5,         0x0B),
	LN2_FUNC_PIN(CDC_GPIO6,         0x0C),
	LN2_FUNC_PIN(CDC_GPIO7,         0x0D),
	LN2_FUNC_PIN(CDC_GPIO8,         0x0E),
	LN2_FUNC_PIN(DSP_GPIO1,         0x0F),
	LN2_FUNC_PIN(DSP_GPIO2,         0x10),
	LN2_FUNC_PIN(DSP_GPIO3,         0x11),
	LN2_FUNC_PIN(DSP_GPIO4,         0x12),
	LN2_FUNC_PIN(DSP_GPIO5,         0x13),
	LN2_FUNC_PIN(DSP_GPIO6,         0x14),
	LN2_FUNC_PIN(GF_GPIO2,          0x15),
	LN2_FUNC_PIN(GF_GPIO3,          0x16),
	LN2_FUNC_PIN(GF_GPIO7,          0x17),
	LN2_FUNC_PIN(GF_GPIO1,          0x18),
	LN2_FUNC_PIN(GF_GPIO5,          0x19),
	LN2_FUNC_PIN(DSP_GPIO20,        0x1A),
	LN_FUNC("codec-clkout",    PIN, 0x20),
	LN_FUNC("dsp-clkout",      PIN, 0x21),
	LN_FUNC("pmic-32k",        PIN, 0x22),
	LN_FUNC("spdif-clkout",    PIN, 0x23),
	LN_FUNC("clk-12m288",      PIN, 0x24),
	LN_FUNC("clk-11m2986",     PIN, 0x25),
	LN_FUNC("clk-24m576",      PIN, 0x26),
	LN_FUNC("clk-22m5792",     PIN, 0x27),
	LN_FUNC("xmos-mclk",       PIN, 0x29),
	LN_FUNC("gf-clkout1",      PIN, 0x2A),
	LN_FUNC("gf-mclk1",        PIN, 0x2B),
	LN_FUNC("gf-mclk3",        PIN, 0x2C),
	LN_FUNC("gf-mclk2",        PIN, 0x2D),
	LN_FUNC("gf-clkout2",      PIN, 0x2E),
	LN2_FUNC_PIN(CDC_MCLK1,         0x2F),
	LN2_FUNC_PIN(CDC_MCLK2,         0x30),
	LN2_FUNC_PIN(DSP_CLKIN,         0x31),
	LN2_FUNC_PIN(PSIA1_MCLK,        0x32),
	LN2_FUNC_PIN(PSIA2_MCLK,        0x33),
	LN_FUNC("spdif-mclk",      PIN, 0x34),
	LN_FUNC("codec-irq",       PIN, 0x42),
	LN2_FUNC_PIN(CDC_RESET,         0x43),
	LN2_FUNC_PIN(DSP_RESET,         0x44),
	LN_FUNC("dsp-irq",         PIN, 0x45),
	LN2_FUNC_PIN(DSP_STANDBY,       0x46),
	LN2_FUNC_PIN(CDC_PDMCLK1,       0x90),
	LN2_FUNC_PIN(CDC_PDMDAT1,       0x91),
	LN2_FUNC_PIN(CDC_PDMCLK2,       0x92),
	LN2_FUNC_PIN(CDC_PDMDAT2,       0x93),
	LN2_FUNC_PIN(CDC_DMICCLK1,      0xA0),
	LN2_FUNC_PIN(CDC_DMICDAT1,      0xA1),
	LN2_FUNC_PIN(CDC_DMICCLK2,      0xA2),
	LN2_FUNC_PIN(CDC_DMICDAT2,      0xA3),
	LN2_FUNC_PIN(CDC_DMICCLK3,      0xA4),
	LN2_FUNC_PIN(CDC_DMICDAT3,      0xA5),
	LN2_FUNC_PIN(CDC_DMICCLK4,      0xA6),
	LN2_FUNC_PIN(CDC_DMICDAT4,      0xA7),
	LN2_FUNC_PIN(DSP_DMICCLK1,      0xA8),
	LN2_FUNC_PIN(DSP_DMICDAT1,      0xA9),
	LN2_FUNC_PIN(DSP_DMICCLK2,      0xAA),
	LN2_FUNC_PIN(DSP_DMICDAT2,      0xAB),
	LN2_FUNC_PIN(DSP_UART1_RX,      0xC0),
	LN2_FUNC_PIN(DSP_UART1_TX,      0xC1),
	LN2_FUNC_PIN(DSP_UART2_RX,      0xC2),
	LN2_FUNC_PIN(DSP_UART2_TX,      0xC3),
	LN2_FUNC_PIN(GF_UART2_RX,       0xC4),
	LN2_FUNC_PIN(GF_UART2_TX,       0xC5),
	LN2_FUNC_PIN(USB_UART_RX,       0xC6),
	LN_FUNC("usb-uart-tx",     PIN, 0xC7),
	LN2_FUNC_PIN(I2C2_SCL,          0xE0),
	LN2_FUNC_PIN(I2C2_SDA,          0xE1),
	LN2_FUNC_PIN(I2C3_SCL,          0xE2),
	LN2_FUNC_PIN(I2C3_SDA,          0xE3),
	LN2_FUNC_PIN(I2C4_SCL,          0xE4),
	LN2_FUNC_PIN(I2C4_SDA,          0xE5),

	LN2_FUNC_AIF(SPDIF_AIF,         0x01),
	LN2_FUNC_GAI(PSIA1,             0x02, 0x50, 0x51, 0x52, 0x53),
	LN2_FUNC_GAI(PSIA2,             0x03, 0x54, 0x55, 0x56, 0x57),
	LN2_FUNC_GAI(CDC_AIF1,          0x04, 0x59, 0x5B, 0x5A, 0x58),
	LN2_FUNC_GAI(CDC_AIF2,          0x05, 0x5D, 0x5F, 0x5E, 0x5C),
	LN2_FUNC_GAI(CDC_AIF3,          0x06, 0x61, 0x62, 0x63, 0x60),
	LN2_FUNC_GAI(DSP_AIF1,          0x07, 0x65, 0x67, 0x66, 0x64),
	LN2_FUNC_GAI(DSP_AIF2,          0x08, 0x69, 0x6B, 0x6A, 0x68),
	LN2_FUNC_GAI(GF_AIF3,           0x09, 0x6D, 0x6F, 0x6C, 0x6E),
	LN2_FUNC_GAI(GF_AIF4,           0x0A, 0x71, 0x73, 0x70, 0x72),
	LN2_FUNC_GAI(GF_AIF1,           0x0B, 0x75, 0x77, 0x74, 0x76),
	LN2_FUNC_GAI(GF_AIF2,           0x0C, 0x79, 0x7B, 0x78, 0x7A),
	LN2_FUNC_AIF(USB_AIF1,          0x0D),
	LN2_FUNC_AIF(USB_AIF2,          0x0E),
	LN2_FUNC_AIF(ADAT_AIF,          0x0F),
	LN2_FUNC_AIF(SOUNDCARD_AIF,     0x10),
पूर्ण;

#घोषणा LN_GROUP_PIN(REV, ID) अणु \
	.name = lochnagar##REV##_##ID##_pin.name, \
	.type = LN_FTYPE_PIN, \
	.pins = &lochnagar##REV##_pins[LOCHNAGAR##REV##_PIN_##ID].number, \
	.npins = 1, \
	.priv = &lochnagar##REV##_pins[LOCHNAGAR##REV##_PIN_##ID], \
पूर्ण

#घोषणा LN_GROUP_AIF(REV, ID) अणु \
	.name = lochnagar##REV##_##ID##_aअगर.name, \
	.type = LN_FTYPE_AIF, \
	.pins = lochnagar##REV##_##ID##_aअगर.pins, \
	.npins = ARRAY_SIZE(lochnagar##REV##_##ID##_aअगर.pins), \
	.priv = &lochnagar##REV##_##ID##_aअगर, \
पूर्ण

#घोषणा LN1_GROUP_PIN(ID) LN_GROUP_PIN(1, ID)
#घोषणा LN2_GROUP_PIN(ID) LN_GROUP_PIN(2, ID)

#घोषणा LN1_GROUP_AIF(ID) LN_GROUP_AIF(1, ID)
#घोषणा LN2_GROUP_AIF(ID) LN_GROUP_AIF(2, ID)

#घोषणा LN2_GROUP_GAI(ID) \
	LN2_GROUP_AIF(ID), \
	LN2_GROUP_PIN(ID##_BCLK), LN2_GROUP_PIN(ID##_LRCLK), \
	LN2_GROUP_PIN(ID##_RXDAT), LN2_GROUP_PIN(ID##_TXDAT)

काष्ठा lochnagar_group अणु
	स्थिर अक्षर * स्थिर name;

	क्रमागत lochnagar_func_type type;

	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक npins;

	स्थिर व्योम *priv;
पूर्ण;

अटल स्थिर काष्ठा lochnagar_group lochnagar1_groups[] = अणु
	LN1_GROUP_PIN(GF_GPIO2),       LN1_GROUP_PIN(GF_GPIO3),
	LN1_GROUP_PIN(GF_GPIO7),
	LN1_GROUP_PIN(LED1),           LN1_GROUP_PIN(LED2),
	LN1_GROUP_AIF(CDC_AIF1),       LN1_GROUP_AIF(CDC_AIF2),
	LN1_GROUP_AIF(CDC_AIF3),
	LN1_GROUP_AIF(DSP_AIF1),       LN1_GROUP_AIF(DSP_AIF2),
	LN1_GROUP_AIF(PSIA1),          LN1_GROUP_AIF(PSIA2),
	LN1_GROUP_AIF(GF_AIF1),        LN1_GROUP_AIF(GF_AIF2),
	LN1_GROUP_AIF(GF_AIF3),        LN1_GROUP_AIF(GF_AIF4),
	LN1_GROUP_AIF(SPDIF_AIF),
पूर्ण;

अटल स्थिर काष्ठा lochnagar_group lochnagar2_groups[] = अणु
	LN2_GROUP_PIN(FPGA_GPIO1),     LN2_GROUP_PIN(FPGA_GPIO2),
	LN2_GROUP_PIN(FPGA_GPIO3),     LN2_GROUP_PIN(FPGA_GPIO4),
	LN2_GROUP_PIN(FPGA_GPIO5),     LN2_GROUP_PIN(FPGA_GPIO6),
	LN2_GROUP_PIN(CDC_GPIO1),      LN2_GROUP_PIN(CDC_GPIO2),
	LN2_GROUP_PIN(CDC_GPIO3),      LN2_GROUP_PIN(CDC_GPIO4),
	LN2_GROUP_PIN(CDC_GPIO5),      LN2_GROUP_PIN(CDC_GPIO6),
	LN2_GROUP_PIN(CDC_GPIO7),      LN2_GROUP_PIN(CDC_GPIO8),
	LN2_GROUP_PIN(DSP_GPIO1),      LN2_GROUP_PIN(DSP_GPIO2),
	LN2_GROUP_PIN(DSP_GPIO3),      LN2_GROUP_PIN(DSP_GPIO4),
	LN2_GROUP_PIN(DSP_GPIO5),      LN2_GROUP_PIN(DSP_GPIO6),
	LN2_GROUP_PIN(DSP_GPIO20),
	LN2_GROUP_PIN(GF_GPIO1),
	LN2_GROUP_PIN(GF_GPIO2),       LN2_GROUP_PIN(GF_GPIO5),
	LN2_GROUP_PIN(GF_GPIO3),       LN2_GROUP_PIN(GF_GPIO7),
	LN2_GROUP_PIN(DSP_UART1_RX),   LN2_GROUP_PIN(DSP_UART1_TX),
	LN2_GROUP_PIN(DSP_UART2_RX),   LN2_GROUP_PIN(DSP_UART2_TX),
	LN2_GROUP_PIN(GF_UART2_RX),    LN2_GROUP_PIN(GF_UART2_TX),
	LN2_GROUP_PIN(USB_UART_RX),
	LN2_GROUP_PIN(CDC_PDMCLK1),    LN2_GROUP_PIN(CDC_PDMDAT1),
	LN2_GROUP_PIN(CDC_PDMCLK2),    LN2_GROUP_PIN(CDC_PDMDAT2),
	LN2_GROUP_PIN(CDC_DMICCLK1),   LN2_GROUP_PIN(CDC_DMICDAT1),
	LN2_GROUP_PIN(CDC_DMICCLK2),   LN2_GROUP_PIN(CDC_DMICDAT2),
	LN2_GROUP_PIN(CDC_DMICCLK3),   LN2_GROUP_PIN(CDC_DMICDAT3),
	LN2_GROUP_PIN(CDC_DMICCLK4),   LN2_GROUP_PIN(CDC_DMICDAT4),
	LN2_GROUP_PIN(DSP_DMICCLK1),   LN2_GROUP_PIN(DSP_DMICDAT1),
	LN2_GROUP_PIN(DSP_DMICCLK2),   LN2_GROUP_PIN(DSP_DMICDAT2),
	LN2_GROUP_PIN(I2C2_SCL),       LN2_GROUP_PIN(I2C2_SDA),
	LN2_GROUP_PIN(I2C3_SCL),       LN2_GROUP_PIN(I2C3_SDA),
	LN2_GROUP_PIN(I2C4_SCL),       LN2_GROUP_PIN(I2C4_SDA),
	LN2_GROUP_PIN(DSP_STANDBY),
	LN2_GROUP_PIN(CDC_MCLK1),      LN2_GROUP_PIN(CDC_MCLK2),
	LN2_GROUP_PIN(DSP_CLKIN),
	LN2_GROUP_PIN(PSIA1_MCLK),     LN2_GROUP_PIN(PSIA2_MCLK),
	LN2_GROUP_GAI(CDC_AIF1),       LN2_GROUP_GAI(CDC_AIF2),
	LN2_GROUP_GAI(CDC_AIF3),
	LN2_GROUP_GAI(DSP_AIF1),       LN2_GROUP_GAI(DSP_AIF2),
	LN2_GROUP_GAI(PSIA1),          LN2_GROUP_GAI(PSIA2),
	LN2_GROUP_GAI(GF_AIF1),        LN2_GROUP_GAI(GF_AIF2),
	LN2_GROUP_GAI(GF_AIF3),        LN2_GROUP_GAI(GF_AIF4),
	LN2_GROUP_AIF(SPDIF_AIF),
	LN2_GROUP_AIF(USB_AIF1),       LN2_GROUP_AIF(USB_AIF2),
	LN2_GROUP_AIF(ADAT_AIF),
	LN2_GROUP_AIF(SOUNDCARD_AIF),
पूर्ण;

काष्ठा lochnagar_func_groups अणु
	स्थिर अक्षर **groups;
	अचिन्हित पूर्णांक ngroups;
पूर्ण;

काष्ठा lochnagar_pin_priv अणु
	काष्ठा lochnagar *lochnagar;
	काष्ठा device *dev;

	स्थिर काष्ठा lochnagar_func *funcs;
	अचिन्हित पूर्णांक nfuncs;

	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक npins;

	स्थिर काष्ठा lochnagar_group *groups;
	अचिन्हित पूर्णांक ngroups;

	काष्ठा lochnagar_func_groups func_groups[LN_FTYPE_COUNT];

	काष्ठा gpio_chip gpio_chip;
पूर्ण;

अटल पूर्णांक lochnagar_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->ngroups;
पूर्ण

अटल स्थिर अक्षर *lochnagar_get_group_name(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित पूर्णांक group_idx)
अणु
	काष्ठा lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->groups[group_idx].name;
पूर्ण

अटल पूर्णांक lochnagar_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित पूर्णांक group_idx,
				    स्थिर अचिन्हित पूर्णांक **pins,
				    अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	*pins = priv->groups[group_idx].pins;
	*num_pins = priv->groups[group_idx].npins;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops lochnagar_pin_group_ops = अणु
	.get_groups_count = lochnagar_get_groups_count,
	.get_group_name = lochnagar_get_group_name,
	.get_group_pins = lochnagar_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक lochnagar_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->nfuncs;
पूर्ण

अटल स्थिर अक्षर *lochnagar_get_func_name(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक func_idx)
अणु
	काष्ठा lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->funcs[func_idx].name;
पूर्ण

अटल पूर्णांक lochnagar_get_func_groups(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक func_idx,
				     स्थिर अक्षर * स्थिर **groups,
				     अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	काष्ठा lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक func_type;

	func_type = priv->funcs[func_idx].type;

	*groups = priv->func_groups[func_type].groups;
	*num_groups = priv->func_groups[func_type].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक lochnagar2_get_gpio_chan(काष्ठा lochnagar_pin_priv *priv,
				    अचिन्हित पूर्णांक op)
अणु
	काष्ठा regmap *regmap = priv->lochnagar->regmap;
	अचिन्हित पूर्णांक val;
	पूर्णांक मुक्त = -1;
	पूर्णांक i, ret;

	क्रम (i = 0; i < LN2_NUM_GPIO_CHANNELS; i++) अणु
		ret = regmap_पढ़ो(regmap, LOCHNAGAR2_GPIO_CHANNEL1 + i, &val);
		अगर (ret)
			वापस ret;

		val &= LOCHNAGAR2_GPIO_CHANNEL_SRC_MASK;

		अगर (val == op)
			वापस i + 1;

		अगर (मुक्त < 0 && !val)
			मुक्त = i;
	पूर्ण

	अगर (मुक्त >= 0) अणु
		ret = regmap_update_bits(regmap,
					 LOCHNAGAR2_GPIO_CHANNEL1 + मुक्त,
					 LOCHNAGAR2_GPIO_CHANNEL_SRC_MASK, op);
		अगर (ret)
			वापस ret;

		मुक्त++;

		dev_dbg(priv->dev, "Set channel %d to 0x%x\n", मुक्त, op);

		वापस मुक्त;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक lochnagar_pin_set_mux(काष्ठा lochnagar_pin_priv *priv,
				 स्थिर काष्ठा lochnagar_pin *pin,
				 अचिन्हित पूर्णांक op)
अणु
	पूर्णांक ret;

	चयन (priv->lochnagar->type) अणु
	हाल LOCHNAGAR1:
		अवरोध;
	शेष:
		ret = lochnagar2_get_gpio_chan(priv, op);
		अगर (ret < 0) अणु
			dev_err(priv->dev, "Failed to get channel for %s: %d\n",
				pin->name, ret);
			वापस ret;
		पूर्ण

		op = ret;
		अवरोध;
	पूर्ण

	dev_dbg(priv->dev, "Set pin %s to 0x%x\n", pin->name, op);

	ret = regmap_ग_लिखो(priv->lochnagar->regmap, pin->reg, op);
	अगर (ret)
		dev_err(priv->dev, "Failed to set %s mux: %d\n",
			pin->name, ret);

	वापस 0;
पूर्ण

अटल पूर्णांक lochnagar_aअगर_set_mux(काष्ठा lochnagar_pin_priv *priv,
				 स्थिर काष्ठा lochnagar_group *group,
				 अचिन्हित पूर्णांक op)
अणु
	काष्ठा regmap *regmap = priv->lochnagar->regmap;
	स्थिर काष्ठा lochnagar_aअगर *aअगर = group->priv;
	स्थिर काष्ठा lochnagar_pin *pin;
	पूर्णांक i, ret;

	ret = regmap_update_bits(regmap, aअगर->src_reg, aअगर->src_mask, op);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to set %s source: %d\n",
			group->name, ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(regmap, aअगर->ctrl_reg,
				 aअगर->ena_mask, aअगर->ena_mask);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to set %s enable: %d\n",
			group->name, ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < group->npins; i++) अणु
		pin = priv->pins[group->pins[i]].drv_data;

		अगर (pin->type != LN_PTYPE_MUX)
			जारी;

		dev_dbg(priv->dev, "Set pin %s to AIF\n", pin->name);

		ret = regmap_update_bits(regmap, pin->reg,
					 LOCHNAGAR2_GPIO_SRC_MASK,
					 LN2_OP_AIF);
		अगर (ret) अणु
			dev_err(priv->dev, "Failed to set %s to AIF: %d\n",
				pin->name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lochnagar_set_mux(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित पूर्णांक func_idx, अचिन्हित पूर्णांक group_idx)
अणु
	काष्ठा lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा lochnagar_func *func = &priv->funcs[func_idx];
	स्थिर काष्ठा lochnagar_group *group = &priv->groups[group_idx];
	स्थिर काष्ठा lochnagar_pin *pin;

	चयन (func->type) अणु
	हाल LN_FTYPE_AIF:
		dev_dbg(priv->dev, "Set group %s to %s\n",
			group->name, func->name);

		वापस lochnagar_aअगर_set_mux(priv, group, func->op);
	हाल LN_FTYPE_PIN:
		pin = priv->pins[*group->pins].drv_data;

		dev_dbg(priv->dev, "Set pin %s to %s\n", pin->name, func->name);

		वापस lochnagar_pin_set_mux(priv, pin, func->op);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक lochnagar_gpio_request(काष्ठा pinctrl_dev *pctldev,
				  काष्ठा pinctrl_gpio_range *range,
				  अचिन्हित पूर्णांक offset)
अणु
	काष्ठा lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा lochnagar *lochnagar = priv->lochnagar;
	स्थिर काष्ठा lochnagar_pin *pin = priv->pins[offset].drv_data;
	पूर्णांक ret;

	dev_dbg(priv->dev, "Requesting GPIO %s\n", pin->name);

	अगर (lochnagar->type == LOCHNAGAR1 || pin->type != LN_PTYPE_MUX)
		वापस 0;

	ret = lochnagar2_get_gpio_chan(priv, LN2_OP_GPIO);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "Failed to get low channel: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = lochnagar2_get_gpio_chan(priv, LN2_OP_GPIO | 0x1);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "Failed to get high channel: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lochnagar_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
					काष्ठा pinctrl_gpio_range *range,
					अचिन्हित पूर्णांक offset,
					bool input)
अणु
	/* The GPIOs only support output */
	अगर (input)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops lochnagar_pin_mux_ops = अणु
	.get_functions_count = lochnagar_get_funcs_count,
	.get_function_name = lochnagar_get_func_name,
	.get_function_groups = lochnagar_get_func_groups,
	.set_mux = lochnagar_set_mux,

	.gpio_request_enable = lochnagar_gpio_request,
	.gpio_set_direction = lochnagar_gpio_set_direction,

	.strict = true,
पूर्ण;

अटल पूर्णांक lochnagar_aअगर_set_master(काष्ठा lochnagar_pin_priv *priv,
				    अचिन्हित पूर्णांक group_idx, bool master)
अणु
	काष्ठा regmap *regmap = priv->lochnagar->regmap;
	स्थिर काष्ठा lochnagar_group *group = &priv->groups[group_idx];
	स्थिर काष्ठा lochnagar_aअगर *aअगर = group->priv;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	अगर (group->type != LN_FTYPE_AIF)
		वापस -EINVAL;

	अगर (!master)
		val = aअगर->master_mask;

	dev_dbg(priv->dev, "Set AIF %s to %s\n",
		group->name, master ? "master" : "slave");

	ret = regmap_update_bits(regmap, aअगर->ctrl_reg, aअगर->master_mask, val);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to set %s mode: %d\n",
			group->name, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lochnagar_conf_group_set(काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित पूर्णांक group_idx,
				    अचिन्हित दीर्घ *configs,
				    अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_configs; i++) अणु
		अचिन्हित पूर्णांक param = pinconf_to_config_param(*configs);

		चयन (param) अणु
		हाल PIN_CONFIG_OUTPUT_ENABLE:
			ret = lochnagar_aअगर_set_master(priv, group_idx, true);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल PIN_CONFIG_INPUT_ENABLE:
			ret = lochnagar_aअगर_set_master(priv, group_idx, false);
			अगर (ret)
				वापस ret;
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण

		configs++;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops lochnagar_pin_conf_ops = अणु
	.pin_config_group_set = lochnagar_conf_group_set,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_desc lochnagar_pin_desc = अणु
	.name = "lochnagar-pinctrl",
	.owner = THIS_MODULE,

	.pctlops = &lochnagar_pin_group_ops,
	.pmxops = &lochnagar_pin_mux_ops,
	.confops = &lochnagar_pin_conf_ops,
पूर्ण;

अटल व्योम lochnagar_gpio_set(काष्ठा gpio_chip *chip,
			       अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा lochnagar_pin_priv *priv = gpiochip_get_data(chip);
	काष्ठा lochnagar *lochnagar = priv->lochnagar;
	स्थिर काष्ठा lochnagar_pin *pin = priv->pins[offset].drv_data;
	पूर्णांक ret;

	value = !!value;

	dev_dbg(priv->dev, "Set GPIO %s to %s\n",
		pin->name, value ? "high" : "low");

	चयन (pin->type) अणु
	हाल LN_PTYPE_MUX:
		value |= LN2_OP_GPIO;

		ret = lochnagar_pin_set_mux(priv, pin, value);
		अवरोध;
	हाल LN_PTYPE_GPIO:
		अगर (pin->invert)
			value = !value;

		ret = regmap_update_bits(lochnagar->regmap, pin->reg,
					 BIT(pin->shअगरt), value << pin->shअगरt);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret < 0)
		dev_err(chip->parent, "Failed to set %s value: %d\n",
			pin->name, ret);
पूर्ण

अटल पूर्णांक lochnagar_gpio_direction_out(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	lochnagar_gpio_set(chip, offset, value);

	वापस pinctrl_gpio_direction_output(chip->base + offset);
पूर्ण

अटल पूर्णांक lochnagar_fill_func_groups(काष्ठा lochnagar_pin_priv *priv)
अणु
	काष्ठा lochnagar_func_groups *funcs;
	पूर्णांक i;

	क्रम (i = 0; i < priv->ngroups; i++)
		priv->func_groups[priv->groups[i].type].ngroups++;

	क्रम (i = 0; i < LN_FTYPE_COUNT; i++) अणु
		funcs = &priv->func_groups[i];

		अगर (!funcs->ngroups)
			जारी;

		funcs->groups = devm_kसुस्मृति(priv->dev, funcs->ngroups,
					     माप(*funcs->groups),
					     GFP_KERNEL);
		अगर (!funcs->groups)
			वापस -ENOMEM;

		funcs->ngroups = 0;
	पूर्ण

	क्रम (i = 0; i < priv->ngroups; i++) अणु
		funcs = &priv->func_groups[priv->groups[i].type];

		funcs->groups[funcs->ngroups++] = priv->groups[i].name;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lochnagar_pin_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lochnagar *lochnagar = dev_get_drvdata(pdev->dev.parent);
	काष्ठा lochnagar_pin_priv *priv;
	काष्ठा pinctrl_desc *desc;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->lochnagar = lochnagar;

	desc = devm_kzalloc(dev, माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	*desc = lochnagar_pin_desc;

	priv->gpio_chip.label = dev_name(dev);
	priv->gpio_chip.request = gpiochip_generic_request;
	priv->gpio_chip.मुक्त = gpiochip_generic_मुक्त;
	priv->gpio_chip.direction_output = lochnagar_gpio_direction_out;
	priv->gpio_chip.set = lochnagar_gpio_set;
	priv->gpio_chip.can_sleep = true;
	priv->gpio_chip.parent = dev;
	priv->gpio_chip.base = -1;
#अगर_घोषित CONFIG_OF_GPIO
	priv->gpio_chip.of_node = dev->of_node;
#पूर्ण_अगर

	चयन (lochnagar->type) अणु
	हाल LOCHNAGAR1:
		priv->funcs = lochnagar1_funcs;
		priv->nfuncs = ARRAY_SIZE(lochnagar1_funcs);
		priv->pins = lochnagar1_pins;
		priv->npins = ARRAY_SIZE(lochnagar1_pins);
		priv->groups = lochnagar1_groups;
		priv->ngroups = ARRAY_SIZE(lochnagar1_groups);

		priv->gpio_chip.ngpio = LOCHNAGAR1_PIN_NUM_GPIOS;
		अवरोध;
	हाल LOCHNAGAR2:
		priv->funcs = lochnagar2_funcs;
		priv->nfuncs = ARRAY_SIZE(lochnagar2_funcs);
		priv->pins = lochnagar2_pins;
		priv->npins = ARRAY_SIZE(lochnagar2_pins);
		priv->groups = lochnagar2_groups;
		priv->ngroups = ARRAY_SIZE(lochnagar2_groups);

		priv->gpio_chip.ngpio = LOCHNAGAR2_PIN_NUM_GPIOS;
		अवरोध;
	शेष:
		dev_err(dev, "Unknown Lochnagar type: %d\n", lochnagar->type);
		वापस -EINVAL;
	पूर्ण

	ret = lochnagar_fill_func_groups(priv);
	अगर (ret < 0)
		वापस ret;

	desc->pins = priv->pins;
	desc->npins = priv->npins;

	pctl = devm_pinctrl_रेजिस्टर(dev, desc, priv);
	अगर (IS_ERR(pctl)) अणु
		ret = PTR_ERR(pctl);
		dev_err(priv->dev, "Failed to register pinctrl: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, &priv->gpio_chip, priv);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register gpiochip: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lochnagar_of_match[] = अणु
	अणु .compatible = "cirrus,lochnagar-pinctrl" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lochnagar_of_match);

अटल काष्ठा platक्रमm_driver lochnagar_pin_driver = अणु
	.driver = अणु
		.name = "lochnagar-pinctrl",
		.of_match_table = of_match_ptr(lochnagar_of_match),
	पूर्ण,

	.probe = lochnagar_pin_probe,
पूर्ण;
module_platक्रमm_driver(lochnagar_pin_driver);

MODULE_AUTHOR("Charles Keepax <ckeepax@opensource.cirrus.com>");
MODULE_DESCRIPTION("Pinctrl driver for Cirrus Logic Lochnagar Board");
MODULE_LICENSE("GPL v2");
