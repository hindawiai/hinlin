<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Pinctrl GPIO driver क्रम Intel Baytrail
 *
 * Copyright (c) 2012-2013, Intel Corporation
 * Author: Mathias Nyman <mathias.nyman@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "pinctrl-intel.h"

/* memory mapped रेजिस्टर offsets */
#घोषणा BYT_CONF0_REG		0x000
#घोषणा BYT_CONF1_REG		0x004
#घोषणा BYT_VAL_REG		0x008
#घोषणा BYT_DFT_REG		0x00c
#घोषणा BYT_INT_STAT_REG	0x800
#घोषणा BYT_DEBOUNCE_REG	0x9d0

/* BYT_CONF0_REG रेजिस्टर bits */
#घोषणा BYT_IODEN		BIT(31)
#घोषणा BYT_सूचीECT_IRQ_EN	BIT(27)
#घोषणा BYT_TRIG_MASK		GENMASK(26, 24)
#घोषणा BYT_TRIG_NEG		BIT(26)
#घोषणा BYT_TRIG_POS		BIT(25)
#घोषणा BYT_TRIG_LVL		BIT(24)
#घोषणा BYT_DEBOUNCE_EN		BIT(20)
#घोषणा BYT_GLITCH_FILTER_EN	BIT(19)
#घोषणा BYT_GLITCH_F_SLOW_CLK	BIT(17)
#घोषणा BYT_GLITCH_F_FAST_CLK	BIT(16)
#घोषणा BYT_PULL_STR_SHIFT	9
#घोषणा BYT_PULL_STR_MASK	GENMASK(10, 9)
#घोषणा BYT_PULL_STR_2K		(0 << BYT_PULL_STR_SHIFT)
#घोषणा BYT_PULL_STR_10K	(1 << BYT_PULL_STR_SHIFT)
#घोषणा BYT_PULL_STR_20K	(2 << BYT_PULL_STR_SHIFT)
#घोषणा BYT_PULL_STR_40K	(3 << BYT_PULL_STR_SHIFT)
#घोषणा BYT_PULL_ASSIGN_SHIFT	7
#घोषणा BYT_PULL_ASSIGN_MASK	GENMASK(8, 7)
#घोषणा BYT_PULL_ASSIGN_UP	(1 << BYT_PULL_ASSIGN_SHIFT)
#घोषणा BYT_PULL_ASSIGN_DOWN	(2 << BYT_PULL_ASSIGN_SHIFT)
#घोषणा BYT_PIN_MUX		GENMASK(2, 0)

/* BYT_VAL_REG रेजिस्टर bits */
#घोषणा BYT_सूची_MASK		GENMASK(2, 1)
#घोषणा BYT_INPUT_EN		BIT(2)  /* 0: input enabled (active low)*/
#घोषणा BYT_OUTPUT_EN		BIT(1)  /* 0: output enabled (active low)*/
#घोषणा BYT_LEVEL		BIT(0)

#घोषणा BYT_CONF0_RESTORE_MASK	(BYT_सूचीECT_IRQ_EN | BYT_TRIG_MASK | BYT_PIN_MUX)
#घोषणा BYT_VAL_RESTORE_MASK	(BYT_सूची_MASK | BYT_LEVEL)

/* BYT_DEBOUNCE_REG bits */
#घोषणा BYT_DEBOUNCE_PULSE_MASK		GENMASK(2, 0)
#घोषणा BYT_DEBOUNCE_PULSE_375US	1
#घोषणा BYT_DEBOUNCE_PULSE_750US	2
#घोषणा BYT_DEBOUNCE_PULSE_1500US	3
#घोषणा BYT_DEBOUNCE_PULSE_3MS		4
#घोषणा BYT_DEBOUNCE_PULSE_6MS		5
#घोषणा BYT_DEBOUNCE_PULSE_12MS		6
#घोषणा BYT_DEBOUNCE_PULSE_24MS		7

#घोषणा BYT_NGPIO_SCORE		102
#घोषणा BYT_NGPIO_NCORE		28
#घोषणा BYT_NGPIO_SUS		44

#घोषणा BYT_SCORE_ACPI_UID	"1"
#घोषणा BYT_NCORE_ACPI_UID	"2"
#घोषणा BYT_SUS_ACPI_UID	"3"

/*
 * This is the function value most pins have क्रम GPIO muxing. If the value
 * dअगरfers from the शेष one, it must be explicitly mentioned. Otherwise, the
 * pin control implementation will set the muxing value to शेष GPIO अगर it
 * करोes not find a match क्रम the requested function.
 */
#घोषणा BYT_DEFAULT_GPIO_MUX	0
#घोषणा BYT_ALTER_GPIO_MUX	1

काष्ठा पूर्णांकel_pad_context अणु
	u32 conf0;
	u32 val;
पूर्ण;

#घोषणा COMMUNITY(p, n, map)		\
	अणु				\
		.pin_base	= (p),	\
		.npins		= (n),	\
		.pad_map	= (map),\
	पूर्ण

/* SCORE pins, aka GPIOC_<pin_no> or GPIO_S0_SC[<pin_no>] */
अटल स्थिर काष्ठा pinctrl_pin_desc byt_score_pins[] = अणु
	PINCTRL_PIN(0, "SATA_GP0"),
	PINCTRL_PIN(1, "SATA_GP1"),
	PINCTRL_PIN(2, "SATA_LED#"),
	PINCTRL_PIN(3, "PCIE_CLKREQ0"),
	PINCTRL_PIN(4, "PCIE_CLKREQ1"),
	PINCTRL_PIN(5, "PCIE_CLKREQ2"),
	PINCTRL_PIN(6, "PCIE_CLKREQ3"),
	PINCTRL_PIN(7, "SD3_WP"),
	PINCTRL_PIN(8, "HDA_RST"),
	PINCTRL_PIN(9, "HDA_SYNC"),
	PINCTRL_PIN(10, "HDA_CLK"),
	PINCTRL_PIN(11, "HDA_SDO"),
	PINCTRL_PIN(12, "HDA_SDI0"),
	PINCTRL_PIN(13, "HDA_SDI1"),
	PINCTRL_PIN(14, "GPIO_S0_SC14"),
	PINCTRL_PIN(15, "GPIO_S0_SC15"),
	PINCTRL_PIN(16, "MMC1_CLK"),
	PINCTRL_PIN(17, "MMC1_D0"),
	PINCTRL_PIN(18, "MMC1_D1"),
	PINCTRL_PIN(19, "MMC1_D2"),
	PINCTRL_PIN(20, "MMC1_D3"),
	PINCTRL_PIN(21, "MMC1_D4"),
	PINCTRL_PIN(22, "MMC1_D5"),
	PINCTRL_PIN(23, "MMC1_D6"),
	PINCTRL_PIN(24, "MMC1_D7"),
	PINCTRL_PIN(25, "MMC1_CMD"),
	PINCTRL_PIN(26, "MMC1_RST"),
	PINCTRL_PIN(27, "SD2_CLK"),
	PINCTRL_PIN(28, "SD2_D0"),
	PINCTRL_PIN(29, "SD2_D1"),
	PINCTRL_PIN(30, "SD2_D2"),
	PINCTRL_PIN(31, "SD2_D3_CD"),
	PINCTRL_PIN(32, "SD2_CMD"),
	PINCTRL_PIN(33, "SD3_CLK"),
	PINCTRL_PIN(34, "SD3_D0"),
	PINCTRL_PIN(35, "SD3_D1"),
	PINCTRL_PIN(36, "SD3_D2"),
	PINCTRL_PIN(37, "SD3_D3"),
	PINCTRL_PIN(38, "SD3_CD"),
	PINCTRL_PIN(39, "SD3_CMD"),
	PINCTRL_PIN(40, "SD3_1P8EN"),
	PINCTRL_PIN(41, "SD3_PWREN#"),
	PINCTRL_PIN(42, "ILB_LPC_AD0"),
	PINCTRL_PIN(43, "ILB_LPC_AD1"),
	PINCTRL_PIN(44, "ILB_LPC_AD2"),
	PINCTRL_PIN(45, "ILB_LPC_AD3"),
	PINCTRL_PIN(46, "ILB_LPC_FRAME"),
	PINCTRL_PIN(47, "ILB_LPC_CLK0"),
	PINCTRL_PIN(48, "ILB_LPC_CLK1"),
	PINCTRL_PIN(49, "ILB_LPC_CLKRUN"),
	PINCTRL_PIN(50, "ILB_LPC_SERIRQ"),
	PINCTRL_PIN(51, "PCU_SMB_DATA"),
	PINCTRL_PIN(52, "PCU_SMB_CLK"),
	PINCTRL_PIN(53, "PCU_SMB_ALERT"),
	PINCTRL_PIN(54, "ILB_8254_SPKR"),
	PINCTRL_PIN(55, "GPIO_S0_SC55"),
	PINCTRL_PIN(56, "GPIO_S0_SC56"),
	PINCTRL_PIN(57, "GPIO_S0_SC57"),
	PINCTRL_PIN(58, "GPIO_S0_SC58"),
	PINCTRL_PIN(59, "GPIO_S0_SC59"),
	PINCTRL_PIN(60, "GPIO_S0_SC60"),
	PINCTRL_PIN(61, "GPIO_S0_SC61"),
	PINCTRL_PIN(62, "LPE_I2S2_CLK"),
	PINCTRL_PIN(63, "LPE_I2S2_FRM"),
	PINCTRL_PIN(64, "LPE_I2S2_DATAIN"),
	PINCTRL_PIN(65, "LPE_I2S2_DATAOUT"),
	PINCTRL_PIN(66, "SIO_SPI_CS"),
	PINCTRL_PIN(67, "SIO_SPI_MISO"),
	PINCTRL_PIN(68, "SIO_SPI_MOSI"),
	PINCTRL_PIN(69, "SIO_SPI_CLK"),
	PINCTRL_PIN(70, "SIO_UART1_RXD"),
	PINCTRL_PIN(71, "SIO_UART1_TXD"),
	PINCTRL_PIN(72, "SIO_UART1_RTS"),
	PINCTRL_PIN(73, "SIO_UART1_CTS"),
	PINCTRL_PIN(74, "SIO_UART2_RXD"),
	PINCTRL_PIN(75, "SIO_UART2_TXD"),
	PINCTRL_PIN(76, "SIO_UART2_RTS"),
	PINCTRL_PIN(77, "SIO_UART2_CTS"),
	PINCTRL_PIN(78, "SIO_I2C0_DATA"),
	PINCTRL_PIN(79, "SIO_I2C0_CLK"),
	PINCTRL_PIN(80, "SIO_I2C1_DATA"),
	PINCTRL_PIN(81, "SIO_I2C1_CLK"),
	PINCTRL_PIN(82, "SIO_I2C2_DATA"),
	PINCTRL_PIN(83, "SIO_I2C2_CLK"),
	PINCTRL_PIN(84, "SIO_I2C3_DATA"),
	PINCTRL_PIN(85, "SIO_I2C3_CLK"),
	PINCTRL_PIN(86, "SIO_I2C4_DATA"),
	PINCTRL_PIN(87, "SIO_I2C4_CLK"),
	PINCTRL_PIN(88, "SIO_I2C5_DATA"),
	PINCTRL_PIN(89, "SIO_I2C5_CLK"),
	PINCTRL_PIN(90, "SIO_I2C6_DATA"),
	PINCTRL_PIN(91, "SIO_I2C6_CLK"),
	PINCTRL_PIN(92, "GPIO_S0_SC92"),
	PINCTRL_PIN(93, "GPIO_S0_SC93"),
	PINCTRL_PIN(94, "SIO_PWM0"),
	PINCTRL_PIN(95, "SIO_PWM1"),
	PINCTRL_PIN(96, "PMC_PLT_CLK0"),
	PINCTRL_PIN(97, "PMC_PLT_CLK1"),
	PINCTRL_PIN(98, "PMC_PLT_CLK2"),
	PINCTRL_PIN(99, "PMC_PLT_CLK3"),
	PINCTRL_PIN(100, "PMC_PLT_CLK4"),
	PINCTRL_PIN(101, "PMC_PLT_CLK5"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_pins_map[BYT_NGPIO_SCORE] = अणु
	85, 89, 93, 96, 99, 102, 98, 101, 34, 37,
	36, 38, 39, 35, 40, 84, 62, 61, 64, 59,
	54, 56, 60, 55, 63, 57, 51, 50, 53, 47,
	52, 49, 48, 43, 46, 41, 45, 42, 58, 44,
	95, 105, 70, 68, 67, 66, 69, 71, 65, 72,
	86, 90, 88, 92, 103, 77, 79, 83, 78, 81,
	80, 82, 13, 12, 15, 14, 17, 18, 19, 16,
	2, 1, 0, 4, 6, 7, 9, 8, 33, 32,
	31, 30, 29, 27, 25, 28, 26, 23, 21, 20,
	24, 22, 5, 3, 10, 11, 106, 87, 91, 104,
	97, 100,
पूर्ण;

/* SCORE groups */
अटल स्थिर अचिन्हित पूर्णांक byt_score_uart1_pins[] = अणु 70, 71, 72, 73 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_uart2_pins[] = अणु 74, 75, 76, 77 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_pwm0_pins[] = अणु 94 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_pwm1_pins[] = अणु 95 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_sio_spi_pins[] = अणु 66, 67, 68, 69 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_i2c5_pins[] = अणु 88, 89 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_i2c6_pins[] = अणु 90, 91 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_i2c4_pins[] = अणु 86, 87 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_i2c3_pins[] = अणु 84, 85 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_i2c2_pins[] = अणु 82, 83 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_i2c1_pins[] = अणु 80, 81 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_i2c0_pins[] = अणु 78, 79 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_ssp0_pins[] = अणु 8, 9, 10, 11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_ssp1_pins[] = अणु 12, 13, 14, 15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_ssp2_pins[] = अणु 62, 63, 64, 65 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_sdcard_pins[] = अणु
	7, 33, 34, 35, 36, 37, 38, 39, 40, 41,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_sdcard_mux_values[] = अणु
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_sdio_pins[] = अणु 27, 28, 29, 30, 31, 32 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_emmc_pins[] = अणु
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_ilb_lpc_pins[] = अणु
	42, 43, 44, 45, 46, 47, 48, 49, 50,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_sata_pins[] = अणु 0, 1, 2 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_plt_clk0_pins[] = अणु 96 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_plt_clk1_pins[] = अणु 97 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_plt_clk2_pins[] = अणु 98 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_plt_clk3_pins[] = अणु 99 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_plt_clk4_pins[] = अणु 100 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_score_plt_clk5_pins[] = अणु 101 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_score_smbus_pins[] = अणु 51, 52, 53 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup byt_score_groups[] = अणु
	PIN_GROUP("uart1_grp", byt_score_uart1_pins, 1),
	PIN_GROUP("uart2_grp", byt_score_uart2_pins, 1),
	PIN_GROUP("pwm0_grp", byt_score_pwm0_pins, 1),
	PIN_GROUP("pwm1_grp", byt_score_pwm1_pins, 1),
	PIN_GROUP("ssp2_grp", byt_score_ssp2_pins, 1),
	PIN_GROUP("sio_spi_grp", byt_score_sio_spi_pins, 1),
	PIN_GROUP("i2c5_grp", byt_score_i2c5_pins, 1),
	PIN_GROUP("i2c6_grp", byt_score_i2c6_pins, 1),
	PIN_GROUP("i2c4_grp", byt_score_i2c4_pins, 1),
	PIN_GROUP("i2c3_grp", byt_score_i2c3_pins, 1),
	PIN_GROUP("i2c2_grp", byt_score_i2c2_pins, 1),
	PIN_GROUP("i2c1_grp", byt_score_i2c1_pins, 1),
	PIN_GROUP("i2c0_grp", byt_score_i2c0_pins, 1),
	PIN_GROUP("ssp0_grp", byt_score_ssp0_pins, 1),
	PIN_GROUP("ssp1_grp", byt_score_ssp1_pins, 1),
	PIN_GROUP("sdcard_grp", byt_score_sdcard_pins, byt_score_sdcard_mux_values),
	PIN_GROUP("sdio_grp", byt_score_sdio_pins, 1),
	PIN_GROUP("emmc_grp", byt_score_emmc_pins, 1),
	PIN_GROUP("lpc_grp", byt_score_ilb_lpc_pins, 1),
	PIN_GROUP("sata_grp", byt_score_sata_pins, 1),
	PIN_GROUP("plt_clk0_grp", byt_score_plt_clk0_pins, 1),
	PIN_GROUP("plt_clk1_grp", byt_score_plt_clk1_pins, 1),
	PIN_GROUP("plt_clk2_grp", byt_score_plt_clk2_pins, 1),
	PIN_GROUP("plt_clk3_grp", byt_score_plt_clk3_pins, 1),
	PIN_GROUP("plt_clk4_grp", byt_score_plt_clk4_pins, 1),
	PIN_GROUP("plt_clk5_grp", byt_score_plt_clk5_pins, 1),
	PIN_GROUP("smbus_grp", byt_score_smbus_pins, 1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर byt_score_uart_groups[] = अणु
	"uart1_grp", "uart2_grp",
पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_pwm_groups[] = अणु
	"pwm0_grp", "pwm1_grp",
पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_ssp_groups[] = अणु
	"ssp0_grp", "ssp1_grp", "ssp2_grp",
पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_spi_groups[] = अणु "sio_spi_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_i2c_groups[] = अणु
	"i2c0_grp", "i2c1_grp", "i2c2_grp", "i2c3_grp", "i2c4_grp", "i2c5_grp",
	"i2c6_grp",
पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_sdcard_groups[] = अणु "sdcard_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_sdio_groups[] = अणु "sdio_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_emmc_groups[] = अणु "emmc_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_lpc_groups[] = अणु "lpc_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_sata_groups[] = अणु "sata_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_plt_clk_groups[] = अणु
	"plt_clk0_grp", "plt_clk1_grp", "plt_clk2_grp", "plt_clk3_grp",
	"plt_clk4_grp", "plt_clk5_grp",
पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_smbus_groups[] = अणु "smbus_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_score_gpio_groups[] = अणु
	"uart1_grp", "uart2_grp", "pwm0_grp", "pwm1_grp", "ssp0_grp",
	"ssp1_grp", "ssp2_grp", "sio_spi_grp", "i2c0_grp", "i2c1_grp",
	"i2c2_grp", "i2c3_grp", "i2c4_grp", "i2c5_grp", "i2c6_grp",
	"sdcard_grp", "sdio_grp", "emmc_grp", "lpc_grp", "sata_grp",
	"plt_clk0_grp", "plt_clk1_grp", "plt_clk2_grp", "plt_clk3_grp",
	"plt_clk4_grp", "plt_clk5_grp", "smbus_grp",
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function byt_score_functions[] = अणु
	FUNCTION("uart", byt_score_uart_groups),
	FUNCTION("pwm", byt_score_pwm_groups),
	FUNCTION("ssp", byt_score_ssp_groups),
	FUNCTION("spi", byt_score_spi_groups),
	FUNCTION("i2c", byt_score_i2c_groups),
	FUNCTION("sdcard", byt_score_sdcard_groups),
	FUNCTION("sdio", byt_score_sdio_groups),
	FUNCTION("emmc", byt_score_emmc_groups),
	FUNCTION("lpc", byt_score_lpc_groups),
	FUNCTION("sata", byt_score_sata_groups),
	FUNCTION("plt_clk", byt_score_plt_clk_groups),
	FUNCTION("smbus", byt_score_smbus_groups),
	FUNCTION("gpio", byt_score_gpio_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community byt_score_communities[] = अणु
	COMMUNITY(0, BYT_NGPIO_SCORE, byt_score_pins_map),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data byt_score_soc_data = अणु
	.uid		= BYT_SCORE_ACPI_UID,
	.pins		= byt_score_pins,
	.npins		= ARRAY_SIZE(byt_score_pins),
	.groups		= byt_score_groups,
	.ngroups	= ARRAY_SIZE(byt_score_groups),
	.functions	= byt_score_functions,
	.nfunctions	= ARRAY_SIZE(byt_score_functions),
	.communities	= byt_score_communities,
	.ncommunities	= ARRAY_SIZE(byt_score_communities),
पूर्ण;

/* SUS pins, aka GPIOS_<pin_no> or GPIO_S5[<pin_no>]  */
अटल स्थिर काष्ठा pinctrl_pin_desc byt_sus_pins[] = अणु
	PINCTRL_PIN(0, "GPIO_S50"),
	PINCTRL_PIN(1, "GPIO_S51"),
	PINCTRL_PIN(2, "GPIO_S52"),
	PINCTRL_PIN(3, "GPIO_S53"),
	PINCTRL_PIN(4, "GPIO_S54"),
	PINCTRL_PIN(5, "GPIO_S55"),
	PINCTRL_PIN(6, "GPIO_S56"),
	PINCTRL_PIN(7, "GPIO_S57"),
	PINCTRL_PIN(8, "GPIO_S58"),
	PINCTRL_PIN(9, "GPIO_S59"),
	PINCTRL_PIN(10, "GPIO_S510"),
	PINCTRL_PIN(11, "PMC_SUSPWRDNACK"),
	PINCTRL_PIN(12, "PMC_SUSCLK0"),
	PINCTRL_PIN(13, "GPIO_S513"),
	PINCTRL_PIN(14, "USB_ULPI_RST"),
	PINCTRL_PIN(15, "PMC_WAKE_PCIE0#"),
	PINCTRL_PIN(16, "PMC_PWRBTN"),
	PINCTRL_PIN(17, "GPIO_S517"),
	PINCTRL_PIN(18, "PMC_SUS_STAT"),
	PINCTRL_PIN(19, "USB_OC0"),
	PINCTRL_PIN(20, "USB_OC1"),
	PINCTRL_PIN(21, "PCU_SPI_CS1"),
	PINCTRL_PIN(22, "GPIO_S522"),
	PINCTRL_PIN(23, "GPIO_S523"),
	PINCTRL_PIN(24, "GPIO_S524"),
	PINCTRL_PIN(25, "GPIO_S525"),
	PINCTRL_PIN(26, "GPIO_S526"),
	PINCTRL_PIN(27, "GPIO_S527"),
	PINCTRL_PIN(28, "GPIO_S528"),
	PINCTRL_PIN(29, "GPIO_S529"),
	PINCTRL_PIN(30, "GPIO_S530"),
	PINCTRL_PIN(31, "USB_ULPI_CLK"),
	PINCTRL_PIN(32, "USB_ULPI_DATA0"),
	PINCTRL_PIN(33, "USB_ULPI_DATA1"),
	PINCTRL_PIN(34, "USB_ULPI_DATA2"),
	PINCTRL_PIN(35, "USB_ULPI_DATA3"),
	PINCTRL_PIN(36, "USB_ULPI_DATA4"),
	PINCTRL_PIN(37, "USB_ULPI_DATA5"),
	PINCTRL_PIN(38, "USB_ULPI_DATA6"),
	PINCTRL_PIN(39, "USB_ULPI_DATA7"),
	PINCTRL_PIN(40, "USB_ULPI_DIR"),
	PINCTRL_PIN(41, "USB_ULPI_NXT"),
	PINCTRL_PIN(42, "USB_ULPI_STP"),
	PINCTRL_PIN(43, "USB_ULPI_REFCLK"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_sus_pins_map[BYT_NGPIO_SUS] = अणु
	29, 33, 30, 31, 32, 34, 36, 35, 38, 37,
	18, 7, 11, 20, 17, 1, 8, 10, 19, 12,
	0, 2, 23, 39, 28, 27, 22, 21, 24, 25,
	26, 51, 56, 54, 49, 55, 48, 57, 50, 58,
	52, 53, 59, 40,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_sus_usb_over_current_pins[] = अणु 19, 20 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_sus_usb_over_current_mode_values[] = अणु 0, 0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_sus_usb_over_current_gpio_mode_values[] = अणु 1, 1 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_sus_usb_ulpi_pins[] = अणु
	14, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_sus_usb_ulpi_mode_values[] = अणु
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_sus_usb_ulpi_gpio_mode_values[] = अणु
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_sus_pcu_spi_pins[] = अणु 21 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_sus_pcu_spi_mode_values[] = अणु 0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक byt_sus_pcu_spi_gpio_mode_values[] = अणु 1 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup byt_sus_groups[] = अणु
	PIN_GROUP("usb_oc_grp", byt_sus_usb_over_current_pins, byt_sus_usb_over_current_mode_values),
	PIN_GROUP("usb_ulpi_grp", byt_sus_usb_ulpi_pins, byt_sus_usb_ulpi_mode_values),
	PIN_GROUP("pcu_spi_grp", byt_sus_pcu_spi_pins, byt_sus_pcu_spi_mode_values),
	PIN_GROUP("usb_oc_grp_gpio", byt_sus_usb_over_current_pins, byt_sus_usb_over_current_gpio_mode_values),
	PIN_GROUP("usb_ulpi_grp_gpio", byt_sus_usb_ulpi_pins, byt_sus_usb_ulpi_gpio_mode_values),
	PIN_GROUP("pcu_spi_grp_gpio", byt_sus_pcu_spi_pins, byt_sus_pcu_spi_gpio_mode_values),
पूर्ण;

अटल स्थिर अक्षर * स्थिर byt_sus_usb_groups[] = अणु
	"usb_oc_grp", "usb_ulpi_grp",
पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_sus_spi_groups[] = अणु "pcu_spi_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर byt_sus_gpio_groups[] = अणु
	"usb_oc_grp_gpio", "usb_ulpi_grp_gpio", "pcu_spi_grp_gpio",
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function byt_sus_functions[] = अणु
	FUNCTION("usb", byt_sus_usb_groups),
	FUNCTION("spi", byt_sus_spi_groups),
	FUNCTION("gpio", byt_sus_gpio_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community byt_sus_communities[] = अणु
	COMMUNITY(0, BYT_NGPIO_SUS, byt_sus_pins_map),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data byt_sus_soc_data = अणु
	.uid		= BYT_SUS_ACPI_UID,
	.pins		= byt_sus_pins,
	.npins		= ARRAY_SIZE(byt_sus_pins),
	.groups		= byt_sus_groups,
	.ngroups	= ARRAY_SIZE(byt_sus_groups),
	.functions	= byt_sus_functions,
	.nfunctions	= ARRAY_SIZE(byt_sus_functions),
	.communities	= byt_sus_communities,
	.ncommunities	= ARRAY_SIZE(byt_sus_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc byt_ncore_pins[] = अणु
	PINCTRL_PIN(0, "HV_DDI0_HPD"),
	PINCTRL_PIN(1, "HV_DDI0_DDC_SDA"),
	PINCTRL_PIN(2, "HV_DDI0_DDC_SCL"),
	PINCTRL_PIN(3, "PANEL0_VDDEN"),
	PINCTRL_PIN(4, "PANEL0_BKLTEN"),
	PINCTRL_PIN(5, "PANEL0_BKLTCTL"),
	PINCTRL_PIN(6, "HV_DDI1_HPD"),
	PINCTRL_PIN(7, "HV_DDI1_DDC_SDA"),
	PINCTRL_PIN(8, "HV_DDI1_DDC_SCL"),
	PINCTRL_PIN(9, "PANEL1_VDDEN"),
	PINCTRL_PIN(10, "PANEL1_BKLTEN"),
	PINCTRL_PIN(11, "PANEL1_BKLTCTL"),
	PINCTRL_PIN(12, "GP_INTD_DSI_TE1"),
	PINCTRL_PIN(13, "HV_DDI2_DDC_SDA"),
	PINCTRL_PIN(14, "HV_DDI2_DDC_SCL"),
	PINCTRL_PIN(15, "GP_CAMERASB00"),
	PINCTRL_PIN(16, "GP_CAMERASB01"),
	PINCTRL_PIN(17, "GP_CAMERASB02"),
	PINCTRL_PIN(18, "GP_CAMERASB03"),
	PINCTRL_PIN(19, "GP_CAMERASB04"),
	PINCTRL_PIN(20, "GP_CAMERASB05"),
	PINCTRL_PIN(21, "GP_CAMERASB06"),
	PINCTRL_PIN(22, "GP_CAMERASB07"),
	PINCTRL_PIN(23, "GP_CAMERASB08"),
	PINCTRL_PIN(24, "GP_CAMERASB09"),
	PINCTRL_PIN(25, "GP_CAMERASB10"),
	PINCTRL_PIN(26, "GP_CAMERASB11"),
	PINCTRL_PIN(27, "GP_INTD_DSI_TE2"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक byt_ncore_pins_map[BYT_NGPIO_NCORE] = अणु
	19, 18, 17, 20, 21, 22, 24, 25, 23, 16,
	14, 15, 12, 26, 27, 1, 4, 8, 11, 0,
	3, 6, 10, 13, 2, 5, 9, 7,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community byt_ncore_communities[] = अणु
	COMMUNITY(0, BYT_NGPIO_NCORE, byt_ncore_pins_map),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data byt_ncore_soc_data = अणु
	.uid		= BYT_NCORE_ACPI_UID,
	.pins		= byt_ncore_pins,
	.npins		= ARRAY_SIZE(byt_ncore_pins),
	.communities	= byt_ncore_communities,
	.ncommunities	= ARRAY_SIZE(byt_ncore_communities),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *byt_soc_data[] = अणु
	&byt_score_soc_data,
	&byt_sus_soc_data,
	&byt_ncore_soc_data,
	शून्य
पूर्ण;

अटल DEFINE_RAW_SPINLOCK(byt_lock);

अटल काष्ठा पूर्णांकel_community *byt_get_community(काष्ठा पूर्णांकel_pinctrl *vg,
						 अचिन्हित पूर्णांक pin)
अणु
	काष्ठा पूर्णांकel_community *comm;
	पूर्णांक i;

	क्रम (i = 0; i < vg->ncommunities; i++) अणु
		comm = vg->communities + i;
		अगर (pin < comm->pin_base + comm->npins && pin >= comm->pin_base)
			वापस comm;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __iomem *byt_gpio_reg(काष्ठा पूर्णांकel_pinctrl *vg, अचिन्हित पूर्णांक offset,
				  पूर्णांक reg)
अणु
	काष्ठा पूर्णांकel_community *comm = byt_get_community(vg, offset);
	u32 reg_offset;

	अगर (!comm)
		वापस शून्य;

	offset -= comm->pin_base;
	चयन (reg) अणु
	हाल BYT_INT_STAT_REG:
		reg_offset = (offset / 32) * 4;
		अवरोध;
	हाल BYT_DEBOUNCE_REG:
		reg_offset = 0;
		अवरोध;
	शेष:
		reg_offset = comm->pad_map[offset] * 16;
		अवरोध;
	पूर्ण

	वापस comm->pad_regs + reg_offset + reg;
पूर्ण

अटल पूर्णांक byt_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctldev);

	वापस vg->soc->ngroups;
पूर्ण

अटल स्थिर अक्षर *byt_get_group_name(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक selector)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctldev);

	वापस vg->soc->groups[selector].name;
पूर्ण

अटल पूर्णांक byt_get_group_pins(काष्ठा pinctrl_dev *pctldev,
			      अचिन्हित पूर्णांक selector,
			      स्थिर अचिन्हित पूर्णांक **pins,
			      अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctldev);

	*pins		= vg->soc->groups[selector].pins;
	*num_pins	= vg->soc->groups[selector].npins;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops byt_pinctrl_ops = अणु
	.get_groups_count	= byt_get_groups_count,
	.get_group_name		= byt_get_group_name,
	.get_group_pins		= byt_get_group_pins,
पूर्ण;

अटल पूर्णांक byt_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctldev);

	वापस vg->soc->nfunctions;
पूर्ण

अटल स्थिर अक्षर *byt_get_function_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctldev);

	वापस vg->soc->functions[selector].name;
पूर्ण

अटल पूर्णांक byt_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक selector,
				   स्थिर अक्षर * स्थिर **groups,
				   अचिन्हित पूर्णांक *num_groups)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctldev);

	*groups		= vg->soc->functions[selector].groups;
	*num_groups	= vg->soc->functions[selector].ngroups;

	वापस 0;
पूर्ण

अटल व्योम byt_set_group_simple_mux(काष्ठा पूर्णांकel_pinctrl *vg,
				     स्थिर काष्ठा पूर्णांकel_pingroup group,
				     अचिन्हित पूर्णांक func)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	raw_spin_lock_irqsave(&byt_lock, flags);

	क्रम (i = 0; i < group.npins; i++) अणु
		व्योम __iomem *padcfg0;
		u32 value;

		padcfg0 = byt_gpio_reg(vg, group.pins[i], BYT_CONF0_REG);
		अगर (!padcfg0) अणु
			dev_warn(vg->dev,
				 "Group %s, pin %i not muxed (no padcfg0)\n",
				 group.name, i);
			जारी;
		पूर्ण

		value = पढ़ोl(padcfg0);
		value &= ~BYT_PIN_MUX;
		value |= func;
		ग_लिखोl(value, padcfg0);
	पूर्ण

	raw_spin_unlock_irqrestore(&byt_lock, flags);
पूर्ण

अटल व्योम byt_set_group_mixed_mux(काष्ठा पूर्णांकel_pinctrl *vg,
				    स्थिर काष्ठा पूर्णांकel_pingroup group,
				    स्थिर अचिन्हित पूर्णांक *func)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	raw_spin_lock_irqsave(&byt_lock, flags);

	क्रम (i = 0; i < group.npins; i++) अणु
		व्योम __iomem *padcfg0;
		u32 value;

		padcfg0 = byt_gpio_reg(vg, group.pins[i], BYT_CONF0_REG);
		अगर (!padcfg0) अणु
			dev_warn(vg->dev,
				 "Group %s, pin %i not muxed (no padcfg0)\n",
				 group.name, i);
			जारी;
		पूर्ण

		value = पढ़ोl(padcfg0);
		value &= ~BYT_PIN_MUX;
		value |= func[i];
		ग_लिखोl(value, padcfg0);
	पूर्ण

	raw_spin_unlock_irqrestore(&byt_lock, flags);
पूर्ण

अटल पूर्णांक byt_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक func_selector,
		       अचिन्हित पूर्णांक group_selector)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा पूर्णांकel_function func = vg->soc->functions[func_selector];
	स्थिर काष्ठा पूर्णांकel_pingroup group = vg->soc->groups[group_selector];

	अगर (group.modes)
		byt_set_group_mixed_mux(vg, group, group.modes);
	अन्यथा अगर (!म_भेद(func.name, "gpio"))
		byt_set_group_simple_mux(vg, group, BYT_DEFAULT_GPIO_MUX);
	अन्यथा
		byt_set_group_simple_mux(vg, group, group.mode);

	वापस 0;
पूर्ण

अटल u32 byt_get_gpio_mux(काष्ठा पूर्णांकel_pinctrl *vg, अचिन्हित पूर्णांक offset)
अणु
	/* SCORE pin 92-93 */
	अगर (!म_भेद(vg->soc->uid, BYT_SCORE_ACPI_UID) &&
	    offset >= 92 && offset <= 93)
		वापस BYT_ALTER_GPIO_MUX;

	/* SUS pin 11-21 */
	अगर (!म_भेद(vg->soc->uid, BYT_SUS_ACPI_UID) &&
	    offset >= 11 && offset <= 21)
		वापस BYT_ALTER_GPIO_MUX;

	वापस BYT_DEFAULT_GPIO_MUX;
पूर्ण

अटल व्योम byt_gpio_clear_triggering(काष्ठा पूर्णांकel_pinctrl *vg, अचिन्हित पूर्णांक offset)
अणु
	व्योम __iomem *reg = byt_gpio_reg(vg, offset, BYT_CONF0_REG);
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&byt_lock, flags);
	value = पढ़ोl(reg);

	/* Do not clear direct-irq enabled IRQs (from gpio_disable_मुक्त) */
	अगर (value & BYT_सूचीECT_IRQ_EN)
		/* nothing to करो */ ;
	अन्यथा
		value &= ~(BYT_TRIG_POS | BYT_TRIG_NEG | BYT_TRIG_LVL);

	ग_लिखोl(value, reg);
	raw_spin_unlock_irqrestore(&byt_lock, flags);
पूर्ण

अटल पूर्णांक byt_gpio_request_enable(काष्ठा pinctrl_dev *pctl_dev,
				   काष्ठा pinctrl_gpio_range *range,
				   अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctl_dev);
	व्योम __iomem *reg = byt_gpio_reg(vg, offset, BYT_CONF0_REG);
	u32 value, gpio_mux;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&byt_lock, flags);

	/*
	 * In most हालs, func pin mux 000 means GPIO function.
	 * But, some pins may have func pin mux 001 represents
	 * GPIO function.
	 *
	 * Because there are devices out there where some pins were not
	 * configured correctly we allow changing the mux value from
	 * request (but prपूर्णांक out warning about that).
	 */
	value = पढ़ोl(reg) & BYT_PIN_MUX;
	gpio_mux = byt_get_gpio_mux(vg, offset);
	अगर (gpio_mux != value) अणु
		value = पढ़ोl(reg) & ~BYT_PIN_MUX;
		value |= gpio_mux;
		ग_लिखोl(value, reg);

		dev_warn(vg->dev, FW_BUG "pin %u forcibly re-configured as GPIO\n", offset);
	पूर्ण

	raw_spin_unlock_irqrestore(&byt_lock, flags);

	pm_runसमय_get(vg->dev);

	वापस 0;
पूर्ण

अटल व्योम byt_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctl_dev,
				  काष्ठा pinctrl_gpio_range *range,
				  अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctl_dev);

	byt_gpio_clear_triggering(vg, offset);
	pm_runसमय_put(vg->dev);
पूर्ण

अटल व्योम byt_gpio_direct_irq_check(काष्ठा पूर्णांकel_pinctrl *vg,
				      अचिन्हित पूर्णांक offset)
अणु
	व्योम __iomem *conf_reg = byt_gpio_reg(vg, offset, BYT_CONF0_REG);

	/*
	 * Beक्रमe making any direction modअगरications, करो a check अगर gpio is set
	 * क्रम direct IRQ. On Bay Trail, setting GPIO to output करोes not make
	 * sense, so let's at least inक्रमm the caller beक्रमe they shoot
	 * themselves in the foot.
	 */
	अगर (पढ़ोl(conf_reg) & BYT_सूचीECT_IRQ_EN)
		dev_info_once(vg->dev, "Potential Error: Setting GPIO with direct_irq_en to output");
पूर्ण

अटल पूर्णांक byt_gpio_set_direction(काष्ठा pinctrl_dev *pctl_dev,
				  काष्ठा pinctrl_gpio_range *range,
				  अचिन्हित पूर्णांक offset,
				  bool input)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctl_dev);
	व्योम __iomem *val_reg = byt_gpio_reg(vg, offset, BYT_VAL_REG);
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&byt_lock, flags);

	value = पढ़ोl(val_reg);
	value &= ~BYT_सूची_MASK;
	अगर (input)
		value |= BYT_OUTPUT_EN;
	अन्यथा
		byt_gpio_direct_irq_check(vg, offset);

	ग_लिखोl(value, val_reg);

	raw_spin_unlock_irqrestore(&byt_lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops byt_pinmux_ops = अणु
	.get_functions_count	= byt_get_functions_count,
	.get_function_name	= byt_get_function_name,
	.get_function_groups	= byt_get_function_groups,
	.set_mux		= byt_set_mux,
	.gpio_request_enable	= byt_gpio_request_enable,
	.gpio_disable_मुक्त	= byt_gpio_disable_मुक्त,
	.gpio_set_direction	= byt_gpio_set_direction,
पूर्ण;

अटल व्योम byt_get_pull_strength(u32 reg, u16 *strength)
अणु
	चयन (reg & BYT_PULL_STR_MASK) अणु
	हाल BYT_PULL_STR_2K:
		*strength = 2000;
		अवरोध;
	हाल BYT_PULL_STR_10K:
		*strength = 10000;
		अवरोध;
	हाल BYT_PULL_STR_20K:
		*strength = 20000;
		अवरोध;
	हाल BYT_PULL_STR_40K:
		*strength = 40000;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक byt_set_pull_strength(u32 *reg, u16 strength)
अणु
	*reg &= ~BYT_PULL_STR_MASK;

	चयन (strength) अणु
	हाल 2000:
		*reg |= BYT_PULL_STR_2K;
		अवरोध;
	हाल 10000:
		*reg |= BYT_PULL_STR_10K;
		अवरोध;
	हाल 20000:
		*reg |= BYT_PULL_STR_20K;
		अवरोध;
	हाल 40000:
		*reg |= BYT_PULL_STR_40K;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक byt_pin_config_get(काष्ठा pinctrl_dev *pctl_dev, अचिन्हित पूर्णांक offset,
			      अचिन्हित दीर्घ *config)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctl_dev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	व्योम __iomem *conf_reg = byt_gpio_reg(vg, offset, BYT_CONF0_REG);
	व्योम __iomem *val_reg = byt_gpio_reg(vg, offset, BYT_VAL_REG);
	व्योम __iomem *db_reg = byt_gpio_reg(vg, offset, BYT_DEBOUNCE_REG);
	अचिन्हित दीर्घ flags;
	u32 conf, pull, val, debounce;
	u16 arg = 0;

	raw_spin_lock_irqsave(&byt_lock, flags);
	conf = पढ़ोl(conf_reg);
	pull = conf & BYT_PULL_ASSIGN_MASK;
	val = पढ़ोl(val_reg);
	raw_spin_unlock_irqrestore(&byt_lock, flags);

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (pull)
			वापस -EINVAL;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		/* Pull assignment is only applicable in input mode */
		अगर ((val & BYT_INPUT_EN) || pull != BYT_PULL_ASSIGN_DOWN)
			वापस -EINVAL;

		byt_get_pull_strength(conf, &arg);

		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		/* Pull assignment is only applicable in input mode */
		अगर ((val & BYT_INPUT_EN) || pull != BYT_PULL_ASSIGN_UP)
			वापस -EINVAL;

		byt_get_pull_strength(conf, &arg);

		अवरोध;
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		अगर (!(conf & BYT_DEBOUNCE_EN))
			वापस -EINVAL;

		raw_spin_lock_irqsave(&byt_lock, flags);
		debounce = पढ़ोl(db_reg);
		raw_spin_unlock_irqrestore(&byt_lock, flags);

		चयन (debounce & BYT_DEBOUNCE_PULSE_MASK) अणु
		हाल BYT_DEBOUNCE_PULSE_375US:
			arg = 375;
			अवरोध;
		हाल BYT_DEBOUNCE_PULSE_750US:
			arg = 750;
			अवरोध;
		हाल BYT_DEBOUNCE_PULSE_1500US:
			arg = 1500;
			अवरोध;
		हाल BYT_DEBOUNCE_PULSE_3MS:
			arg = 3000;
			अवरोध;
		हाल BYT_DEBOUNCE_PULSE_6MS:
			arg = 6000;
			अवरोध;
		हाल BYT_DEBOUNCE_PULSE_12MS:
			arg = 12000;
			अवरोध;
		हाल BYT_DEBOUNCE_PULSE_24MS:
			arg = 24000;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक byt_pin_config_set(काष्ठा pinctrl_dev *pctl_dev,
			      अचिन्हित पूर्णांक offset,
			      अचिन्हित दीर्घ *configs,
			      अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = pinctrl_dev_get_drvdata(pctl_dev);
	अचिन्हित पूर्णांक param, arg;
	व्योम __iomem *conf_reg = byt_gpio_reg(vg, offset, BYT_CONF0_REG);
	व्योम __iomem *val_reg = byt_gpio_reg(vg, offset, BYT_VAL_REG);
	व्योम __iomem *db_reg = byt_gpio_reg(vg, offset, BYT_DEBOUNCE_REG);
	अचिन्हित दीर्घ flags;
	u32 conf, val, debounce;
	पूर्णांक i, ret = 0;

	raw_spin_lock_irqsave(&byt_lock, flags);

	conf = पढ़ोl(conf_reg);
	val = पढ़ोl(val_reg);

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			conf &= ~BYT_PULL_ASSIGN_MASK;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			/* Set शेष strength value in हाल none is given */
			अगर (arg == 1)
				arg = 2000;

			/*
			 * Pull assignment is only applicable in input mode. If
			 * chip is not in input mode, set it and warn about it.
			 */
			अगर (val & BYT_INPUT_EN) अणु
				val &= ~BYT_INPUT_EN;
				ग_लिखोl(val, val_reg);
				dev_warn(vg->dev,
					 "pin %u forcibly set to input mode\n",
					 offset);
			पूर्ण

			conf &= ~BYT_PULL_ASSIGN_MASK;
			conf |= BYT_PULL_ASSIGN_DOWN;
			ret = byt_set_pull_strength(&conf, arg);

			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			/* Set शेष strength value in हाल none is given */
			अगर (arg == 1)
				arg = 2000;

			/*
			 * Pull assignment is only applicable in input mode. If
			 * chip is not in input mode, set it and warn about it.
			 */
			अगर (val & BYT_INPUT_EN) अणु
				val &= ~BYT_INPUT_EN;
				ग_लिखोl(val, val_reg);
				dev_warn(vg->dev,
					 "pin %u forcibly set to input mode\n",
					 offset);
			पूर्ण

			conf &= ~BYT_PULL_ASSIGN_MASK;
			conf |= BYT_PULL_ASSIGN_UP;
			ret = byt_set_pull_strength(&conf, arg);

			अवरोध;
		हाल PIN_CONFIG_INPUT_DEBOUNCE:
			debounce = पढ़ोl(db_reg);

			अगर (arg)
				conf |= BYT_DEBOUNCE_EN;
			अन्यथा
				conf &= ~BYT_DEBOUNCE_EN;

			चयन (arg) अणु
			हाल 375:
				debounce &= ~BYT_DEBOUNCE_PULSE_MASK;
				debounce |= BYT_DEBOUNCE_PULSE_375US;
				अवरोध;
			हाल 750:
				debounce &= ~BYT_DEBOUNCE_PULSE_MASK;
				debounce |= BYT_DEBOUNCE_PULSE_750US;
				अवरोध;
			हाल 1500:
				debounce &= ~BYT_DEBOUNCE_PULSE_MASK;
				debounce |= BYT_DEBOUNCE_PULSE_1500US;
				अवरोध;
			हाल 3000:
				debounce &= ~BYT_DEBOUNCE_PULSE_MASK;
				debounce |= BYT_DEBOUNCE_PULSE_3MS;
				अवरोध;
			हाल 6000:
				debounce &= ~BYT_DEBOUNCE_PULSE_MASK;
				debounce |= BYT_DEBOUNCE_PULSE_6MS;
				अवरोध;
			हाल 12000:
				debounce &= ~BYT_DEBOUNCE_PULSE_MASK;
				debounce |= BYT_DEBOUNCE_PULSE_12MS;
				अवरोध;
			हाल 24000:
				debounce &= ~BYT_DEBOUNCE_PULSE_MASK;
				debounce |= BYT_DEBOUNCE_PULSE_24MS;
				अवरोध;
			शेष:
				अगर (arg)
					ret = -EINVAL;
				अवरोध;
			पूर्ण

			अगर (!ret)
				ग_लिखोl(debounce, db_reg);
			अवरोध;
		शेष:
			ret = -ENOTSUPP;
		पूर्ण

		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (!ret)
		ग_लिखोl(conf, conf_reg);

	raw_spin_unlock_irqrestore(&byt_lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops byt_pinconf_ops = अणु
	.is_generic	= true,
	.pin_config_get	= byt_pin_config_get,
	.pin_config_set	= byt_pin_config_set,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_desc byt_pinctrl_desc = अणु
	.pctlops	= &byt_pinctrl_ops,
	.pmxops		= &byt_pinmux_ops,
	.confops	= &byt_pinconf_ops,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक byt_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(chip);
	व्योम __iomem *reg = byt_gpio_reg(vg, offset, BYT_VAL_REG);
	अचिन्हित दीर्घ flags;
	u32 val;

	raw_spin_lock_irqsave(&byt_lock, flags);
	val = पढ़ोl(reg);
	raw_spin_unlock_irqrestore(&byt_lock, flags);

	वापस !!(val & BYT_LEVEL);
पूर्ण

अटल व्योम byt_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(chip);
	व्योम __iomem *reg = byt_gpio_reg(vg, offset, BYT_VAL_REG);
	अचिन्हित दीर्घ flags;
	u32 old_val;

	अगर (!reg)
		वापस;

	raw_spin_lock_irqsave(&byt_lock, flags);
	old_val = पढ़ोl(reg);
	अगर (value)
		ग_लिखोl(old_val | BYT_LEVEL, reg);
	अन्यथा
		ग_लिखोl(old_val & ~BYT_LEVEL, reg);
	raw_spin_unlock_irqrestore(&byt_lock, flags);
पूर्ण

अटल पूर्णांक byt_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(chip);
	व्योम __iomem *reg = byt_gpio_reg(vg, offset, BYT_VAL_REG);
	अचिन्हित दीर्घ flags;
	u32 value;

	अगर (!reg)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&byt_lock, flags);
	value = पढ़ोl(reg);
	raw_spin_unlock_irqrestore(&byt_lock, flags);

	अगर (!(value & BYT_OUTPUT_EN))
		वापस GPIO_LINE_सूचीECTION_OUT;
	अगर (!(value & BYT_INPUT_EN))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक byt_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(chip);
	व्योम __iomem *val_reg = byt_gpio_reg(vg, offset, BYT_VAL_REG);
	अचिन्हित दीर्घ flags;
	u32 reg;

	raw_spin_lock_irqsave(&byt_lock, flags);

	reg = पढ़ोl(val_reg);
	reg &= ~BYT_सूची_MASK;
	reg |= BYT_OUTPUT_EN;
	ग_लिखोl(reg, val_reg);

	raw_spin_unlock_irqrestore(&byt_lock, flags);
	वापस 0;
पूर्ण

/*
 * Note despite the temptation this MUST NOT be converted पूर्णांकo a call to
 * pinctrl_gpio_direction_output() + byt_gpio_set() that करोes not work this
 * MUST be करोne as a single BYT_VAL_REG रेजिस्टर ग_लिखो.
 * See the commit message of the commit adding this comment क्रम details.
 */
अटल पूर्णांक byt_gpio_direction_output(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(chip);
	व्योम __iomem *val_reg = byt_gpio_reg(vg, offset, BYT_VAL_REG);
	अचिन्हित दीर्घ flags;
	u32 reg;

	raw_spin_lock_irqsave(&byt_lock, flags);

	byt_gpio_direct_irq_check(vg, offset);

	reg = पढ़ोl(val_reg);
	reg &= ~BYT_सूची_MASK;
	अगर (value)
		reg |= BYT_LEVEL;
	अन्यथा
		reg &= ~BYT_LEVEL;

	ग_लिखोl(reg, val_reg);

	raw_spin_unlock_irqrestore(&byt_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम byt_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(chip);
	पूर्णांक i;
	u32 conf0, val;

	क्रम (i = 0; i < vg->soc->npins; i++) अणु
		स्थिर काष्ठा पूर्णांकel_community *comm;
		स्थिर अक्षर *pull_str = शून्य;
		स्थिर अक्षर *pull = शून्य;
		व्योम __iomem *reg;
		अचिन्हित दीर्घ flags;
		स्थिर अक्षर *label;
		अचिन्हित पूर्णांक pin;

		raw_spin_lock_irqsave(&byt_lock, flags);
		pin = vg->soc->pins[i].number;
		reg = byt_gpio_reg(vg, pin, BYT_CONF0_REG);
		अगर (!reg) अणु
			seq_म_लिखो(s,
				   "Could not retrieve pin %i conf0 reg\n",
				   pin);
			raw_spin_unlock_irqrestore(&byt_lock, flags);
			जारी;
		पूर्ण
		conf0 = पढ़ोl(reg);

		reg = byt_gpio_reg(vg, pin, BYT_VAL_REG);
		अगर (!reg) अणु
			seq_म_लिखो(s,
				   "Could not retrieve pin %i val reg\n", pin);
			raw_spin_unlock_irqrestore(&byt_lock, flags);
			जारी;
		पूर्ण
		val = पढ़ोl(reg);
		raw_spin_unlock_irqrestore(&byt_lock, flags);

		comm = byt_get_community(vg, pin);
		अगर (!comm) अणु
			seq_म_लिखो(s,
				   "Could not get community for pin %i\n", pin);
			जारी;
		पूर्ण
		label = gpiochip_is_requested(chip, i);
		अगर (!label)
			label = "Unrequested";

		चयन (conf0 & BYT_PULL_ASSIGN_MASK) अणु
		हाल BYT_PULL_ASSIGN_UP:
			pull = "up";
			अवरोध;
		हाल BYT_PULL_ASSIGN_DOWN:
			pull = "down";
			अवरोध;
		पूर्ण

		चयन (conf0 & BYT_PULL_STR_MASK) अणु
		हाल BYT_PULL_STR_2K:
			pull_str = "2k";
			अवरोध;
		हाल BYT_PULL_STR_10K:
			pull_str = "10k";
			अवरोध;
		हाल BYT_PULL_STR_20K:
			pull_str = "20k";
			अवरोध;
		हाल BYT_PULL_STR_40K:
			pull_str = "40k";
			अवरोध;
		पूर्ण

		seq_म_लिखो(s,
			   " gpio-%-3d (%-20.20s) %s %s %s pad-%-3d offset:0x%03x mux:%d %s%s%s",
			   pin,
			   label,
			   val & BYT_INPUT_EN ? "  " : "in",
			   val & BYT_OUTPUT_EN ? "   " : "out",
			   val & BYT_LEVEL ? "hi" : "lo",
			   comm->pad_map[i], comm->pad_map[i] * 16,
			   conf0 & 0x7,
			   conf0 & BYT_TRIG_NEG ? " fall" : "     ",
			   conf0 & BYT_TRIG_POS ? " rise" : "     ",
			   conf0 & BYT_TRIG_LVL ? " level" : "      ");

		अगर (pull && pull_str)
			seq_म_लिखो(s, " %-4s %-3s", pull, pull_str);
		अन्यथा
			seq_माला_दो(s, "          ");

		अगर (conf0 & BYT_IODEN)
			seq_माला_दो(s, " open-drain");

		seq_माला_दो(s, "\n");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा gpio_chip byt_gpio_chip = अणु
	.owner			= THIS_MODULE,
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.get_direction		= byt_gpio_get_direction,
	.direction_input	= byt_gpio_direction_input,
	.direction_output	= byt_gpio_direction_output,
	.get			= byt_gpio_get,
	.set			= byt_gpio_set,
	.set_config		= gpiochip_generic_config,
	.dbg_show		= byt_gpio_dbg_show,
पूर्ण;

अटल व्योम byt_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक offset = irqd_to_hwirq(d);
	व्योम __iomem *reg;

	reg = byt_gpio_reg(vg, offset, BYT_INT_STAT_REG);
	अगर (!reg)
		वापस;

	raw_spin_lock(&byt_lock);
	ग_लिखोl(BIT(offset % 32), reg);
	raw_spin_unlock(&byt_lock);
पूर्ण

अटल व्योम byt_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(gc);

	byt_gpio_clear_triggering(vg, irqd_to_hwirq(d));
पूर्ण

अटल व्योम byt_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक offset = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg;
	u32 value;

	reg = byt_gpio_reg(vg, offset, BYT_CONF0_REG);
	अगर (!reg)
		वापस;

	raw_spin_lock_irqsave(&byt_lock, flags);
	value = पढ़ोl(reg);

	चयन (irqd_get_trigger_type(d)) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		value |= BYT_TRIG_LVL;
		fallthrough;
	हाल IRQ_TYPE_EDGE_RISING:
		value |= BYT_TRIG_POS;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		value |= BYT_TRIG_LVL;
		fallthrough;
	हाल IRQ_TYPE_EDGE_FALLING:
		value |= BYT_TRIG_NEG;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		value |= (BYT_TRIG_NEG | BYT_TRIG_POS);
		अवरोध;
	पूर्ण

	ग_लिखोl(value, reg);

	raw_spin_unlock_irqrestore(&byt_lock, flags);
पूर्ण

अटल पूर्णांक byt_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(irq_data_get_irq_chip_data(d));
	u32 offset = irqd_to_hwirq(d);
	u32 value;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg = byt_gpio_reg(vg, offset, BYT_CONF0_REG);

	अगर (!reg || offset >= vg->chip.ngpio)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&byt_lock, flags);
	value = पढ़ोl(reg);

	WARN(value & BYT_सूचीECT_IRQ_EN,
	     "Bad pad config for io mode, force direct_irq_en bit clearing");

	/* For level trigges the BYT_TRIG_POS and BYT_TRIG_NEG bits
	 * are used to indicate high and low level triggering
	 */
	value &= ~(BYT_सूचीECT_IRQ_EN | BYT_TRIG_POS | BYT_TRIG_NEG |
		   BYT_TRIG_LVL);
	/* Enable glitch filtering */
	value |= BYT_GLITCH_FILTER_EN | BYT_GLITCH_F_SLOW_CLK |
		 BYT_GLITCH_F_FAST_CLK;

	ग_लिखोl(value, reg);

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);
	अन्यथा अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(d, handle_level_irq);

	raw_spin_unlock_irqrestore(&byt_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम byt_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(irq_desc_get_handler_data(desc));
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);
	u32 base, pin;
	व्योम __iomem *reg;
	अचिन्हित दीर्घ pending;
	अचिन्हित पूर्णांक virq;

	/* check from GPIO controller which pin triggered the पूर्णांकerrupt */
	क्रम (base = 0; base < vg->chip.ngpio; base += 32) अणु
		reg = byt_gpio_reg(vg, base, BYT_INT_STAT_REG);

		अगर (!reg) अणु
			dev_warn(vg->dev,
				 "Pin %i: could not retrieve interrupt status register\n",
				 base);
			जारी;
		पूर्ण

		raw_spin_lock(&byt_lock);
		pending = पढ़ोl(reg);
		raw_spin_unlock(&byt_lock);
		क्रम_each_set_bit(pin, &pending, 32) अणु
			virq = irq_find_mapping(vg->chip.irq.करोमुख्य, base + pin);
			generic_handle_irq(virq);
		पूर्ण
	पूर्ण
	chip->irq_eoi(data);
पूर्ण

अटल व्योम byt_init_irq_valid_mask(काष्ठा gpio_chip *chip,
				    अचिन्हित दीर्घ *valid_mask,
				    अचिन्हित पूर्णांक ngpios)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(chip);
	व्योम __iomem *reg;
	u32 value;
	पूर्णांक i;

	/*
	 * Clear पूर्णांकerrupt triggers क्रम all pins that are GPIOs and
	 * करो not use direct IRQ mode. This will prevent spurious
	 * पूर्णांकerrupts from misconfigured pins.
	 */
	क्रम (i = 0; i < vg->soc->npins; i++) अणु
		अचिन्हित पूर्णांक pin = vg->soc->pins[i].number;

		reg = byt_gpio_reg(vg, pin, BYT_CONF0_REG);
		अगर (!reg) अणु
			dev_warn(vg->dev,
				 "Pin %i: could not retrieve conf0 register\n",
				 i);
			जारी;
		पूर्ण

		value = पढ़ोl(reg);
		अगर (value & BYT_सूचीECT_IRQ_EN) अणु
			clear_bit(i, valid_mask);
			dev_dbg(vg->dev, "excluding GPIO %d from IRQ domain\n", i);
		पूर्ण अन्यथा अगर ((value & BYT_PIN_MUX) == byt_get_gpio_mux(vg, i)) अणु
			byt_gpio_clear_triggering(vg, i);
			dev_dbg(vg->dev, "disabling GPIO %d\n", i);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक byt_gpio_irq_init_hw(काष्ठा gpio_chip *chip)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(chip);
	व्योम __iomem *reg;
	u32 base, value;

	/* clear पूर्णांकerrupt status trigger रेजिस्टरs */
	क्रम (base = 0; base < vg->soc->npins; base += 32) अणु
		reg = byt_gpio_reg(vg, base, BYT_INT_STAT_REG);

		अगर (!reg) अणु
			dev_warn(vg->dev,
				 "Pin %i: could not retrieve irq status reg\n",
				 base);
			जारी;
		पूर्ण

		ग_लिखोl(0xffffffff, reg);
		/* make sure trigger bits are cleared, अगर not then a pin
		   might be misconfigured in bios */
		value = पढ़ोl(reg);
		अगर (value)
			dev_err(vg->dev,
				"GPIO interrupt error, pins misconfigured. INT_STAT%u: 0x%08x\n",
				base / 32, value);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक byt_gpio_add_pin_ranges(काष्ठा gpio_chip *chip)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = gpiochip_get_data(chip);
	काष्ठा device *dev = vg->dev;
	पूर्णांक ret;

	ret = gpiochip_add_pin_range(chip, dev_name(dev), 0, 0, vg->soc->npins);
	अगर (ret)
		dev_err(dev, "failed to add GPIO pin range\n");

	वापस ret;
पूर्ण

अटल पूर्णांक byt_gpio_probe(काष्ठा पूर्णांकel_pinctrl *vg)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(vg->dev);
	काष्ठा gpio_chip *gc;
	पूर्णांक irq, ret;

	/* Set up gpio chip */
	vg->chip	= byt_gpio_chip;
	gc		= &vg->chip;
	gc->label	= dev_name(vg->dev);
	gc->base	= -1;
	gc->can_sleep	= false;
	gc->add_pin_ranges = byt_gpio_add_pin_ranges;
	gc->parent	= vg->dev;
	gc->ngpio	= vg->soc->npins;

#अगर_घोषित CONFIG_PM_SLEEP
	vg->context.pads = devm_kसुस्मृति(vg->dev, gc->ngpio, माप(*vg->context.pads),
					GFP_KERNEL);
	अगर (!vg->context.pads)
		वापस -ENOMEM;
#पूर्ण_अगर

	/* set up पूर्णांकerrupts  */
	irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (irq > 0) अणु
		काष्ठा gpio_irq_chip *girq;

		vg->irqchip.name = "BYT-GPIO",
		vg->irqchip.irq_ack = byt_irq_ack,
		vg->irqchip.irq_mask = byt_irq_mask,
		vg->irqchip.irq_unmask = byt_irq_unmask,
		vg->irqchip.irq_set_type = byt_irq_type,
		vg->irqchip.flags = IRQCHIP_SKIP_SET_WAKE,

		girq = &gc->irq;
		girq->chip = &vg->irqchip;
		girq->init_hw = byt_gpio_irq_init_hw;
		girq->init_valid_mask = byt_init_irq_valid_mask;
		girq->parent_handler = byt_gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(vg->dev, girq->num_parents,
					     माप(*girq->parents), GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_bad_irq;
	पूर्ण

	ret = devm_gpiochip_add_data(vg->dev, gc, vg);
	अगर (ret) अणु
		dev_err(vg->dev, "failed adding byt-gpio chip\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक byt_set_soc_data(काष्ठा पूर्णांकel_pinctrl *vg,
			    स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *soc)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(vg->dev);
	पूर्णांक i;

	vg->soc = soc;

	vg->ncommunities = vg->soc->ncommunities;
	vg->communities = devm_kसुस्मृति(vg->dev, vg->ncommunities,
				       माप(*vg->communities), GFP_KERNEL);
	अगर (!vg->communities)
		वापस -ENOMEM;

	क्रम (i = 0; i < vg->soc->ncommunities; i++) अणु
		काष्ठा पूर्णांकel_community *comm = vg->communities + i;

		*comm = vg->soc->communities[i];

		comm->pad_regs = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(comm->pad_regs))
			वापस PTR_ERR(comm->pad_regs);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id byt_gpio_acpi_match[] = अणु
	अणु "INT33B2", (kernel_uदीर्घ_t)byt_soc_data पूर्ण,
	अणु "INT33FC", (kernel_uदीर्घ_t)byt_soc_data पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक byt_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *soc_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकel_pinctrl *vg;
	पूर्णांक ret;

	soc_data = पूर्णांकel_pinctrl_get_soc_data(pdev);
	अगर (IS_ERR(soc_data))
		वापस PTR_ERR(soc_data);

	vg = devm_kzalloc(dev, माप(*vg), GFP_KERNEL);
	अगर (!vg)
		वापस -ENOMEM;

	vg->dev = dev;
	ret = byt_set_soc_data(vg, soc_data);
	अगर (ret) अणु
		dev_err(dev, "failed to set soc data\n");
		वापस ret;
	पूर्ण

	vg->pctldesc		= byt_pinctrl_desc;
	vg->pctldesc.name	= dev_name(dev);
	vg->pctldesc.pins	= vg->soc->pins;
	vg->pctldesc.npins	= vg->soc->npins;

	vg->pctldev = devm_pinctrl_रेजिस्टर(dev, &vg->pctldesc, vg);
	अगर (IS_ERR(vg->pctldev)) अणु
		dev_err(dev, "failed to register pinctrl driver\n");
		वापस PTR_ERR(vg->pctldev);
	पूर्ण

	ret = byt_gpio_probe(vg);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, vg);
	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक byt_gpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	raw_spin_lock_irqsave(&byt_lock, flags);

	क्रम (i = 0; i < vg->soc->npins; i++) अणु
		व्योम __iomem *reg;
		u32 value;
		अचिन्हित पूर्णांक pin = vg->soc->pins[i].number;

		reg = byt_gpio_reg(vg, pin, BYT_CONF0_REG);
		अगर (!reg) अणु
			dev_warn(vg->dev,
				 "Pin %i: could not retrieve conf0 register\n",
				 i);
			जारी;
		पूर्ण
		value = पढ़ोl(reg) & BYT_CONF0_RESTORE_MASK;
		vg->context.pads[i].conf0 = value;

		reg = byt_gpio_reg(vg, pin, BYT_VAL_REG);
		value = पढ़ोl(reg) & BYT_VAL_RESTORE_MASK;
		vg->context.pads[i].val = value;
	पूर्ण

	raw_spin_unlock_irqrestore(&byt_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक byt_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_pinctrl *vg = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	raw_spin_lock_irqsave(&byt_lock, flags);

	क्रम (i = 0; i < vg->soc->npins; i++) अणु
		व्योम __iomem *reg;
		u32 value;
		अचिन्हित पूर्णांक pin = vg->soc->pins[i].number;

		reg = byt_gpio_reg(vg, pin, BYT_CONF0_REG);
		अगर (!reg) अणु
			dev_warn(vg->dev,
				 "Pin %i: could not retrieve conf0 register\n",
				 i);
			जारी;
		पूर्ण
		value = पढ़ोl(reg);
		अगर ((value & BYT_CONF0_RESTORE_MASK) !=
		     vg->context.pads[i].conf0) अणु
			value &= ~BYT_CONF0_RESTORE_MASK;
			value |= vg->context.pads[i].conf0;
			ग_लिखोl(value, reg);
			dev_info(dev, "restored pin %d conf0 %#08x", i, value);
		पूर्ण

		reg = byt_gpio_reg(vg, pin, BYT_VAL_REG);
		value = पढ़ोl(reg);
		अगर ((value & BYT_VAL_RESTORE_MASK) !=
		     vg->context.pads[i].val) अणु
			u32 v;

			v = value & ~BYT_VAL_RESTORE_MASK;
			v |= vg->context.pads[i].val;
			अगर (v != value) अणु
				ग_लिखोl(v, reg);
				dev_dbg(dev, "restored pin %d val %#08x\n",
					i, v);
			पूर्ण
		पूर्ण
	पूर्ण

	raw_spin_unlock_irqrestore(&byt_lock, flags);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक byt_gpio_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक byt_gpio_runसमय_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops byt_gpio_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(byt_gpio_suspend, byt_gpio_resume)
	SET_RUNTIME_PM_OPS(byt_gpio_runसमय_suspend, byt_gpio_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver byt_gpio_driver = अणु
	.probe          = byt_pinctrl_probe,
	.driver         = अणु
		.name			= "byt_gpio",
		.pm			= &byt_gpio_pm_ops,
		.acpi_match_table	= byt_gpio_acpi_match,
		.suppress_bind_attrs	= true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init byt_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&byt_gpio_driver);
पूर्ण
subsys_initcall(byt_gpio_init);
