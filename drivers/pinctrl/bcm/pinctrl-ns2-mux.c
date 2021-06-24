<शैली गुरु>
/* Copyright (C) 2016 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * This file contains the Northstar2 IOMUX driver that supports group
 * based PINMUX configuration. The PWM is functional only when the
 * corresponding mfio pin group is selected as gpio.
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"

#घोषणा NS2_NUM_IOMUX			19
#घोषणा NS2_NUM_PWM_MUX			4

#घोषणा NS2_PIN_MUX_BASE0		0x00
#घोषणा NS2_PIN_MUX_BASE1		0x01
#घोषणा NS2_PIN_CONF_BASE		0x02
#घोषणा NS2_MUX_PAD_FUNC1_OFFSET	0x04

#घोषणा NS2_PIN_SRC_MASK		0x01
#घोषणा NS2_PIN_PULL_MASK		0x03
#घोषणा NS2_PIN_DRIVE_STRENGTH_MASK	0x07

#घोषणा NS2_PIN_PULL_UP			0x01
#घोषणा NS2_PIN_PULL_DOWN		0x02

#घोषणा NS2_PIN_INPUT_EN_MASK		0x01

/*
 * Northstar2 IOMUX रेजिस्टर description
 *
 * @base: base address number
 * @offset: रेजिस्टर offset क्रम mux configuration of a group
 * @shअगरt: bit shअगरt क्रम mux configuration of a group
 * @mask: mask bits
 * @alt: alternate function to set to
 */
काष्ठा ns2_mux अणु
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक alt;
पूर्ण;

/*
 * Keep track of Northstar2 IOMUX configuration and prevent द्विगुन
 * configuration
 *
 * @ns2_mux: Northstar2 IOMUX रेजिस्टर description
 * @is_configured: flag to indicate whether a mux setting has alपढ़ोy
 * been configured
 */
काष्ठा ns2_mux_log अणु
	काष्ठा ns2_mux mux;
	bool is_configured;
पूर्ण;

/*
 * Group based IOMUX configuration
 *
 * @name: name of the group
 * @pins: array of pins used by this group
 * @num_pins: total number of pins used by this group
 * @mux: Northstar2 group based IOMUX configuration
 */
काष्ठा ns2_pin_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित पूर्णांक num_pins;
	स्थिर काष्ठा ns2_mux mux;
पूर्ण;

/*
 * Northstar2 mux function and supported pin groups
 *
 * @name: name of the function
 * @groups: array of groups that can be supported by this function
 * @num_groups: total number of groups that can be supported by function
 */
काष्ठा ns2_pin_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	स्थिर अचिन्हित पूर्णांक num_groups;
पूर्ण;

/*
 * Northstar2 IOMUX pinctrl core
 *
 * @pctl: poपूर्णांकer to pinctrl_dev
 * @dev: poपूर्णांकer to device
 * @base0: first IOMUX रेजिस्टर base
 * @base1: second IOMUX रेजिस्टर base
 * @pinconf_base: configuration रेजिस्टर base
 * @groups: poपूर्णांकer to array of groups
 * @num_groups: total number of groups
 * @functions: poपूर्णांकer to array of functions
 * @num_functions: total number of functions
 * @mux_log: poपूर्णांकer to the array of mux logs
 * @lock: lock to protect रेजिस्टर access
 */
काष्ठा ns2_pinctrl अणु
	काष्ठा pinctrl_dev *pctl;
	काष्ठा device *dev;
	व्योम __iomem *base0;
	व्योम __iomem *base1;
	व्योम __iomem *pinconf_base;

	स्थिर काष्ठा ns2_pin_group *groups;
	अचिन्हित पूर्णांक num_groups;

	स्थिर काष्ठा ns2_pin_function *functions;
	अचिन्हित पूर्णांक num_functions;

	काष्ठा ns2_mux_log *mux_log;

	spinlock_t lock;
पूर्ण;

/*
 * Pin configuration info
 *
 * @base: base address number
 * @offset: रेजिस्टर offset from base
 * @src_shअगरt: slew rate control bit shअगरt in the रेजिस्टर
 * @input_en: input enable control bit shअगरt
 * @pull_shअगरt: pull-up/pull-करोwn control bit shअगरt in the रेजिस्टर
 * @drive_shअगरt: drive strength control bit shअगरt in the रेजिस्टर
 */
काष्ठा ns2_pinconf अणु
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक src_shअगरt;
	अचिन्हित पूर्णांक input_en;
	अचिन्हित पूर्णांक pull_shअगरt;
	अचिन्हित पूर्णांक drive_shअगरt;
पूर्ण;

/*
 * Description of a pin in Northstar2
 *
 * @pin: pin number
 * @name: pin name
 * @pin_conf: pin configuration काष्ठाure
 */
काष्ठा ns2_pin अणु
	अचिन्हित पूर्णांक pin;
	अक्षर *name;
	काष्ठा ns2_pinconf pin_conf;
पूर्ण;

#घोषणा NS2_PIN_DESC(p, n, b, o, s, i, pu, d)	\
अणु						\
	.pin = p,				\
	.name = n,				\
	.pin_conf = अणु				\
		.base = b,			\
		.offset = o,			\
		.src_shअगरt = s,			\
		.input_en = i,			\
		.pull_shअगरt = pu,		\
		.drive_shअगरt = d,		\
	पूर्ण					\
पूर्ण

/*
 * List of pins in Northstar2
 */
अटल काष्ठा ns2_pin ns2_pins[] = अणु
	NS2_PIN_DESC(0, "mfio_0", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(1, "mfio_1", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(2, "mfio_2", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(3, "mfio_3", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(4, "mfio_4", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(5, "mfio_5", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(6, "mfio_6", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(7, "mfio_7", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(8, "mfio_8", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(9, "mfio_9", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(10, "mfio_10", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(11, "mfio_11", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(12, "mfio_12", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(13, "mfio_13", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(14, "mfio_14", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(15, "mfio_15", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(16, "mfio_16", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(17, "mfio_17", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(18, "mfio_18", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(19, "mfio_19", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(20, "mfio_20", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(21, "mfio_21", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(22, "mfio_22", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(23, "mfio_23", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(24, "mfio_24", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(25, "mfio_25", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(26, "mfio_26", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(27, "mfio_27", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(28, "mfio_28", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(29, "mfio_29", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(30, "mfio_30", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(31, "mfio_31", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(32, "mfio_32", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(33, "mfio_33", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(34, "mfio_34", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(35, "mfio_35", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(36, "mfio_36", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(37, "mfio_37", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(38, "mfio_38", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(39, "mfio_39", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(40, "mfio_40", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(41, "mfio_41", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(42, "mfio_42", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(43, "mfio_43", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(44, "mfio_44", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(45, "mfio_45", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(46, "mfio_46", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(47, "mfio_47", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(48, "mfio_48", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(49, "mfio_49", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(50, "mfio_50", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(51, "mfio_51", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(52, "mfio_52", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(53, "mfio_53", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(54, "mfio_54", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(55, "mfio_55", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(56, "mfio_56", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(57, "mfio_57", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(58, "mfio_58", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(59, "mfio_59", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(60, "mfio_60", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(61, "mfio_61", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(62, "mfio_62", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(63, "qspi_wp", 2, 0x0, 31, 30, 27, 24),
	NS2_PIN_DESC(64, "qspi_hold", 2, 0x0, 23, 22, 19, 16),
	NS2_PIN_DESC(65, "qspi_cs", 2, 0x0, 15, 14, 11, 8),
	NS2_PIN_DESC(66, "qspi_sck", 2, 0x0, 7, 6, 3, 0),
	NS2_PIN_DESC(67, "uart3_sin", 2, 0x04, 31, 30, 27, 24),
	NS2_PIN_DESC(68, "uart3_sout", 2, 0x04, 23, 22, 19, 16),
	NS2_PIN_DESC(69, "qspi_mosi", 2, 0x04, 15, 14, 11, 8),
	NS2_PIN_DESC(70, "qspi_miso", 2, 0x04, 7, 6, 3, 0),
	NS2_PIN_DESC(71, "spi0_fss", 2, 0x08, 31, 30, 27, 24),
	NS2_PIN_DESC(72, "spi0_rxd", 2, 0x08, 23, 22, 19, 16),
	NS2_PIN_DESC(73, "spi0_txd", 2, 0x08, 15, 14, 11, 8),
	NS2_PIN_DESC(74, "spi0_sck", 2, 0x08, 7, 6, 3, 0),
	NS2_PIN_DESC(75, "spi1_fss", 2, 0x0c, 31, 30, 27, 24),
	NS2_PIN_DESC(76, "spi1_rxd", 2, 0x0c, 23, 22, 19, 16),
	NS2_PIN_DESC(77, "spi1_txd", 2, 0x0c, 15, 14, 11, 8),
	NS2_PIN_DESC(78, "spi1_sck", 2, 0x0c, 7, 6, 3, 0),
	NS2_PIN_DESC(79, "sdio0_data7", 2, 0x10, 31, 30, 27, 24),
	NS2_PIN_DESC(80, "sdio0_emmc_rst", 2, 0x10, 23, 22, 19, 16),
	NS2_PIN_DESC(81, "sdio0_led_on", 2, 0x10, 15, 14, 11, 8),
	NS2_PIN_DESC(82, "sdio0_wp", 2, 0x10, 7, 6, 3, 0),
	NS2_PIN_DESC(83, "sdio0_data3", 2, 0x14, 31, 30, 27, 24),
	NS2_PIN_DESC(84, "sdio0_data4", 2, 0x14, 23, 22, 19, 16),
	NS2_PIN_DESC(85, "sdio0_data5", 2, 0x14, 15, 14, 11, 8),
	NS2_PIN_DESC(86, "sdio0_data6", 2, 0x14, 7, 6, 3, 0),
	NS2_PIN_DESC(87, "sdio0_cmd", 2, 0x18, 31, 30, 27, 24),
	NS2_PIN_DESC(88, "sdio0_data0", 2, 0x18, 23, 22, 19, 16),
	NS2_PIN_DESC(89, "sdio0_data1", 2, 0x18, 15, 14, 11, 8),
	NS2_PIN_DESC(90, "sdio0_data2", 2, 0x18, 7, 6, 3, 0),
	NS2_PIN_DESC(91, "sdio1_led_on", 2, 0x1c, 31, 30, 27, 24),
	NS2_PIN_DESC(92, "sdio1_wp", 2, 0x1c, 23, 22, 19, 16),
	NS2_PIN_DESC(93, "sdio0_cd_l", 2, 0x1c, 15, 14, 11, 8),
	NS2_PIN_DESC(94, "sdio0_clk", 2, 0x1c, 7, 6, 3, 0),
	NS2_PIN_DESC(95, "sdio1_data5", 2, 0x20, 31, 30, 27, 24),
	NS2_PIN_DESC(96, "sdio1_data6", 2, 0x20, 23, 22, 19, 16),
	NS2_PIN_DESC(97, "sdio1_data7", 2, 0x20, 15, 14, 11, 8),
	NS2_PIN_DESC(98, "sdio1_emmc_rst", 2, 0x20, 7, 6, 3, 0),
	NS2_PIN_DESC(99, "sdio1_data1", 2, 0x24, 31, 30, 27, 24),
	NS2_PIN_DESC(100, "sdio1_data2", 2, 0x24, 23, 22, 19, 16),
	NS2_PIN_DESC(101, "sdio1_data3", 2, 0x24, 15, 14, 11, 8),
	NS2_PIN_DESC(102, "sdio1_data4", 2, 0x24, 7, 6, 3, 0),
	NS2_PIN_DESC(103, "sdio1_cd_l", 2, 0x28, 31, 30, 27, 24),
	NS2_PIN_DESC(104, "sdio1_clk", 2, 0x28, 23, 22, 19, 16),
	NS2_PIN_DESC(105, "sdio1_cmd", 2, 0x28, 15, 14, 11, 8),
	NS2_PIN_DESC(106, "sdio1_data0", 2, 0x28, 7, 6, 3, 0),
	NS2_PIN_DESC(107, "ext_mdio_0", 2, 0x2c, 15, 14, 11, 8),
	NS2_PIN_DESC(108, "ext_mdc_0", 2, 0x2c, 7, 6, 3, 0),
	NS2_PIN_DESC(109, "usb3_p1_vbus_ppc", 2, 0x34, 31, 30, 27, 24),
	NS2_PIN_DESC(110, "usb3_p1_overcurrent", 2, 0x34, 23, 22, 19, 16),
	NS2_PIN_DESC(111, "usb3_p0_vbus_ppc", 2, 0x34, 15, 14, 11, 8),
	NS2_PIN_DESC(112, "usb3_p0_overcurrent", 2, 0x34, 7, 6, 3, 0),
	NS2_PIN_DESC(113, "usb2_presence_indication", 2, 0x38, 31, 30, 27, 24),
	NS2_PIN_DESC(114, "usb2_vbus_present", 2, 0x38, 23, 22, 19, 16),
	NS2_PIN_DESC(115, "usb2_vbus_ppc", 2, 0x38, 15, 14, 11, 8),
	NS2_PIN_DESC(116, "usb2_overcurrent", 2, 0x38, 7, 6, 3, 0),
	NS2_PIN_DESC(117, "sata_led1", 2, 0x3c, 15, 14, 11, 8),
	NS2_PIN_DESC(118, "sata_led0", 2, 0x3c, 7, 6, 3, 0),
पूर्ण;

/*
 * List of groups of pins
 */

अटल स्थिर अचिन्हित पूर्णांक nand_pins[] = अणु0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_data_pins[] =  अणु0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_0_1_pins[] = अणु24, 25पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_0_pins[] = अणु24पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_1_pins[] = अणु25पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uart1_ext_clk_pins[] = अणु26पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_adv_pins[] = अणु26पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_2_5_pins[] = अणु27, 28, 29, 30पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pcie_ab1_clk_wak_pins[] = अणु27, 28, 29, 30पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_addr_0_3_pins[] = अणु27, 28, 29, 30पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_2_pins[] = अणु27पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_3_pins[] = अणु28पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_6_7_pins[] = अणु31, 32पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pcie_a3_clk_wak_pins[] = अणु31, 32पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_addr_4_5_pins[] = अणु31, 32पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_8_9_pins[] = अणु33, 34पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pcie_b3_clk_wak_pins[] = अणु33, 34पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_addr_6_7_pins[] = अणु33, 34पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_10_11_pins[] = अणु35, 36पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pcie_b2_clk_wak_pins[] = अणु35, 36पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_addr_8_9_pins[] = अणु35, 36पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_12_13_pins[] = अणु37, 38पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pcie_a2_clk_wak_pins[] = अणु37, 38पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_addr_10_11_pins[] = अणु37, 38पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_14_17_pins[] = अणु39, 40, 41, 42पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_modem_pins[] = अणु39, 40, 41, 42पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_addr_12_15_pins[] = अणु39, 40, 41, 42पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_18_19_pins[] = अणु43, 44पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_rts_cts_pins[] = अणु43, 44पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_20_21_pins[] = अणु45, 46पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_in_out_pins[] = अणु45, 46पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_22_23_pins[] = अणु47, 48पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_dcd_dsr_pins[] = अणु47, 48पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_24_25_pins[] = अणु49, 50पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_ri_dtr_pins[] = अणु49, 50पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_26_27_pins[] = अणु51, 52पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_rts_cts_pins[] = अणु51, 52पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_28_29_pins[] = अणु53, 54पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_in_out_pins[] = अणु53, 54पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_30_31_pins[] = अणु55, 56पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart2_rts_cts_pins[] = अणु55, 56पूर्ण;

#घोषणा NS2_PIN_GROUP(group_name, ba, off, sh, ma, al)	\
अणु							\
	.name = __stringअगरy(group_name) "_grp",		\
	.pins = group_name ## _pins,			\
	.num_pins = ARRAY_SIZE(group_name ## _pins),	\
	.mux = अणु					\
		.base = ba,				\
		.offset = off,				\
		.shअगरt = sh,				\
		.mask = ma,				\
		.alt = al,				\
	पूर्ण						\
पूर्ण

/*
 * List of Northstar2 pin groups
 */
अटल स्थिर काष्ठा ns2_pin_group ns2_pin_groups[] = अणु
	NS2_PIN_GROUP(nand, 0, 0, 31, 1, 0),
	NS2_PIN_GROUP(nor_data, 0, 0, 31, 1, 1),
	NS2_PIN_GROUP(gpio_0_1, 0, 0, 31, 1, 0),

	NS2_PIN_GROUP(uart1_ext_clk, 0, 4, 30, 3, 1),
	NS2_PIN_GROUP(nor_adv, 0, 4, 30, 3, 2),

	NS2_PIN_GROUP(gpio_2_5,	0, 4, 28, 3, 0),
	NS2_PIN_GROUP(pcie_ab1_clk_wak, 0, 4, 28, 3, 1),
	NS2_PIN_GROUP(nor_addr_0_3, 0, 4, 28, 3, 2),

	NS2_PIN_GROUP(gpio_6_7, 0, 4, 26, 3, 0),
	NS2_PIN_GROUP(pcie_a3_clk_wak, 0, 4, 26, 3, 1),
	NS2_PIN_GROUP(nor_addr_4_5, 0, 4, 26, 3, 2),

	NS2_PIN_GROUP(gpio_8_9, 0, 4, 24, 3, 0),
	NS2_PIN_GROUP(pcie_b3_clk_wak, 0, 4, 24, 3, 1),
	NS2_PIN_GROUP(nor_addr_6_7, 0, 4, 24, 3, 2),

	NS2_PIN_GROUP(gpio_10_11, 0, 4, 22, 3, 0),
	NS2_PIN_GROUP(pcie_b2_clk_wak, 0, 4, 22, 3, 1),
	NS2_PIN_GROUP(nor_addr_8_9, 0, 4, 22, 3, 2),

	NS2_PIN_GROUP(gpio_12_13, 0, 4, 20, 3, 0),
	NS2_PIN_GROUP(pcie_a2_clk_wak, 0, 4, 20, 3, 1),
	NS2_PIN_GROUP(nor_addr_10_11, 0, 4, 20, 3, 2),

	NS2_PIN_GROUP(gpio_14_17, 0, 4, 18, 3, 0),
	NS2_PIN_GROUP(uart0_modem, 0, 4, 18, 3, 1),
	NS2_PIN_GROUP(nor_addr_12_15, 0, 4, 18, 3, 2),

	NS2_PIN_GROUP(gpio_18_19, 0, 4, 16, 3, 0),
	NS2_PIN_GROUP(uart0_rts_cts, 0, 4, 16, 3, 1),

	NS2_PIN_GROUP(gpio_20_21, 0, 4, 14, 3, 0),
	NS2_PIN_GROUP(uart0_in_out, 0, 4, 14, 3, 1),

	NS2_PIN_GROUP(gpio_22_23, 0, 4, 12, 3, 0),
	NS2_PIN_GROUP(uart1_dcd_dsr, 0, 4, 12, 3, 1),

	NS2_PIN_GROUP(gpio_24_25, 0, 4, 10, 3, 0),
	NS2_PIN_GROUP(uart1_ri_dtr, 0, 4, 10, 3, 1),

	NS2_PIN_GROUP(gpio_26_27, 0, 4, 8, 3, 0),
	NS2_PIN_GROUP(uart1_rts_cts, 0, 4, 8, 3, 1),

	NS2_PIN_GROUP(gpio_28_29, 0, 4, 6, 3, 0),
	NS2_PIN_GROUP(uart1_in_out, 0, 4, 6, 3, 1),

	NS2_PIN_GROUP(gpio_30_31, 0, 4, 4, 3, 0),
	NS2_PIN_GROUP(uart2_rts_cts, 0, 4, 4, 3, 1),

	NS2_PIN_GROUP(pwm_0, 1, 0, 0, 1, 1),
	NS2_PIN_GROUP(pwm_1, 1, 0, 1, 1, 1),
	NS2_PIN_GROUP(pwm_2, 1, 0, 2, 1, 1),
	NS2_PIN_GROUP(pwm_3, 1, 0, 3, 1, 1),
पूर्ण;

/*
 * List of groups supported by functions
 */

अटल स्थिर अक्षर * स्थिर nand_grps[] = अणु"nand_grp"पूर्ण;

अटल स्थिर अक्षर * स्थिर nor_grps[] = अणु"nor_data_grp", "nor_adv_grp",
	"nor_addr_0_3_grp", "nor_addr_4_5_grp",	"nor_addr_6_7_grp",
	"nor_addr_8_9_grp", "nor_addr_10_11_grp", "nor_addr_12_15_grp"पूर्ण;

अटल स्थिर अक्षर * स्थिर gpio_grps[] = अणु"gpio_0_1_grp", "gpio_2_5_grp",
	"gpio_6_7_grp",	"gpio_8_9_grp",	"gpio_10_11_grp", "gpio_12_13_grp",
	"gpio_14_17_grp", "gpio_18_19_grp", "gpio_20_21_grp", "gpio_22_23_grp",
	"gpio_24_25_grp", "gpio_26_27_grp", "gpio_28_29_grp",
	"gpio_30_31_grp"पूर्ण;

अटल स्थिर अक्षर * स्थिर pcie_grps[] = अणु"pcie_ab1_clk_wak_grp",
	"pcie_a3_clk_wak_grp", "pcie_b3_clk_wak_grp", "pcie_b2_clk_wak_grp",
	"pcie_a2_clk_wak_grp"पूर्ण;

अटल स्थिर अक्षर * स्थिर uart0_grps[] = अणु"uart0_modem_grp",
	"uart0_rts_cts_grp", "uart0_in_out_grp"पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_grps[] = अणु"uart1_ext_clk_grp",
	"uart1_dcd_dsr_grp", "uart1_ri_dtr_grp", "uart1_rts_cts_grp",
	"uart1_in_out_grp"पूर्ण;

अटल स्थिर अक्षर * स्थिर uart2_grps[] = अणु"uart2_rts_cts_grp"पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_grps[] = अणु"pwm_0_grp", "pwm_1_grp",
	"pwm_2_grp", "pwm_3_grp"पूर्ण;

#घोषणा NS2_PIN_FUNCTION(func)				\
अणु							\
	.name = #func,					\
	.groups = func ## _grps,			\
	.num_groups = ARRAY_SIZE(func ## _grps),	\
पूर्ण

/*
 * List of supported functions
 */
अटल स्थिर काष्ठा ns2_pin_function ns2_pin_functions[] = अणु
	NS2_PIN_FUNCTION(nand),
	NS2_PIN_FUNCTION(nor),
	NS2_PIN_FUNCTION(gpio),
	NS2_PIN_FUNCTION(pcie),
	NS2_PIN_FUNCTION(uart0),
	NS2_PIN_FUNCTION(uart1),
	NS2_PIN_FUNCTION(uart2),
	NS2_PIN_FUNCTION(pwm),
पूर्ण;

अटल पूर्णांक ns2_get_groups_count(काष्ठा pinctrl_dev *pctrl_dev)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->num_groups;
पूर्ण

अटल स्थिर अक्षर *ns2_get_group_name(काष्ठा pinctrl_dev *pctrl_dev,
				      अचिन्हित पूर्णांक selector)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->groups[selector].name;
पूर्ण

अटल पूर्णांक ns2_get_group_pins(काष्ठा pinctrl_dev *pctrl_dev,
			      अचिन्हित पूर्णांक selector, स्थिर अचिन्हित पूर्णांक **pins,
			      अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	*pins = pinctrl->groups[selector].pins;
	*num_pins = pinctrl->groups[selector].num_pins;

	वापस 0;
पूर्ण

अटल व्योम ns2_pin_dbg_show(काष्ठा pinctrl_dev *pctrl_dev,
			     काष्ठा seq_file *s, अचिन्हित पूर्णांक offset)
अणु
	seq_म_लिखो(s, " %s", dev_name(pctrl_dev->dev));
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops ns2_pinctrl_ops = अणु
	.get_groups_count = ns2_get_groups_count,
	.get_group_name = ns2_get_group_name,
	.get_group_pins = ns2_get_group_pins,
	.pin_dbg_show = ns2_pin_dbg_show,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक ns2_get_functions_count(काष्ठा pinctrl_dev *pctrl_dev)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->num_functions;
पूर्ण

अटल स्थिर अक्षर *ns2_get_function_name(काष्ठा pinctrl_dev *pctrl_dev,
					 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->functions[selector].name;
पूर्ण

अटल पूर्णांक ns2_get_function_groups(काष्ठा pinctrl_dev *pctrl_dev,
				   अचिन्हित पूर्णांक selector,
				   स्थिर अक्षर * स्थिर **groups,
				   अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	*groups = pinctrl->functions[selector].groups;
	*num_groups = pinctrl->functions[selector].num_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक ns2_pinmux_set(काष्ठा ns2_pinctrl *pinctrl,
			  स्थिर काष्ठा ns2_pin_function *func,
			  स्थिर काष्ठा ns2_pin_group *grp,
			  काष्ठा ns2_mux_log *mux_log)
अणु
	स्थिर काष्ठा ns2_mux *mux = &grp->mux;
	पूर्णांक i;
	u32 val, mask;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *base_address;

	क्रम (i = 0; i < NS2_NUM_IOMUX; i++) अणु
		अगर ((mux->shअगरt != mux_log[i].mux.shअगरt) ||
			(mux->base != mux_log[i].mux.base) ||
			(mux->offset != mux_log[i].mux.offset))
			जारी;

		/* अगर this is a new configuration, just करो it! */
		अगर (!mux_log[i].is_configured)
			अवरोध;

		/*
		 * IOMUX has been configured previously and one is trying to
		 * configure it to a dअगरferent function
		 */
		अगर (mux_log[i].mux.alt != mux->alt) अणु
			dev_err(pinctrl->dev,
				"double configuration error detected!\n");
			dev_err(pinctrl->dev, "func:%s grp:%s\n",
				func->name, grp->name);
			वापस -EINVAL;
		पूर्ण

		वापस 0;
	पूर्ण
	अगर (i == NS2_NUM_IOMUX)
		वापस -EINVAL;

	mask = mux->mask;
	mux_log[i].mux.alt = mux->alt;
	mux_log[i].is_configured = true;

	चयन (mux->base) अणु
	हाल NS2_PIN_MUX_BASE0:
		base_address = pinctrl->base0;
		अवरोध;

	हाल NS2_PIN_MUX_BASE1:
		base_address = pinctrl->base1;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&pinctrl->lock, flags);
	val = पढ़ोl(base_address + grp->mux.offset);
	val &= ~(mask << grp->mux.shअगरt);
	val |= grp->mux.alt << grp->mux.shअगरt;
	ग_लिखोl(val, (base_address + grp->mux.offset));
	spin_unlock_irqrestore(&pinctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ns2_pinmux_enable(काष्ठा pinctrl_dev *pctrl_dev,
			     अचिन्हित पूर्णांक func_select, अचिन्हित पूर्णांक grp_select)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	स्थिर काष्ठा ns2_pin_function *func;
	स्थिर काष्ठा ns2_pin_group *grp;

	अगर (grp_select >= pinctrl->num_groups ||
		func_select >= pinctrl->num_functions)
		वापस -EINVAL;

	func = &pinctrl->functions[func_select];
	grp = &pinctrl->groups[grp_select];

	dev_dbg(pctrl_dev->dev, "func:%u name:%s grp:%u name:%s\n",
		func_select, func->name, grp_select, grp->name);

	dev_dbg(pctrl_dev->dev, "offset:0x%08x shift:%u alt:%u\n",
		grp->mux.offset, grp->mux.shअगरt, grp->mux.alt);

	वापस ns2_pinmux_set(pinctrl, func, grp, pinctrl->mux_log);
पूर्ण

अटल पूर्णांक ns2_pin_set_enable(काष्ठा pinctrl_dev *pctrldev, अचिन्हित पूर्णांक pin,
			    u16 enable)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrldev);
	काष्ठा ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	अचिन्हित दीर्घ flags;
	u32 val;
	व्योम __iomem *base_address;

	base_address = pinctrl->pinconf_base;
	spin_lock_irqsave(&pinctrl->lock, flags);
	val = पढ़ोl(base_address + pin_data->pin_conf.offset);
	val &= ~(NS2_PIN_SRC_MASK << pin_data->pin_conf.input_en);

	अगर (!enable)
		val |= NS2_PIN_INPUT_EN_MASK << pin_data->pin_conf.input_en;

	ग_लिखोl(val, (base_address + pin_data->pin_conf.offset));
	spin_unlock_irqrestore(&pinctrl->lock, flags);

	dev_dbg(pctrldev->dev, "pin:%u set enable:%d\n", pin, enable);
	वापस 0;
पूर्ण

अटल पूर्णांक ns2_pin_get_enable(काष्ठा pinctrl_dev *pctrldev, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrldev);
	काष्ठा ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक enable;

	spin_lock_irqsave(&pinctrl->lock, flags);
	enable = पढ़ोl(pinctrl->pinconf_base + pin_data->pin_conf.offset);
	enable = (enable >> pin_data->pin_conf.input_en) &
			NS2_PIN_INPUT_EN_MASK;
	spin_unlock_irqrestore(&pinctrl->lock, flags);

	अगर (!enable)
		enable = NS2_PIN_INPUT_EN_MASK;
	अन्यथा
		enable = 0;

	dev_dbg(pctrldev->dev, "pin:%u get disable:%d\n", pin, enable);
	वापस enable;
पूर्ण

अटल पूर्णांक ns2_pin_set_slew(काष्ठा pinctrl_dev *pctrldev, अचिन्हित पूर्णांक pin,
			    u32 slew)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrldev);
	काष्ठा ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	अचिन्हित दीर्घ flags;
	u32 val;
	व्योम __iomem *base_address;

	base_address = pinctrl->pinconf_base;
	spin_lock_irqsave(&pinctrl->lock, flags);
	val = पढ़ोl(base_address + pin_data->pin_conf.offset);
	val &= ~(NS2_PIN_SRC_MASK << pin_data->pin_conf.src_shअगरt);

	अगर (slew)
		val |= NS2_PIN_SRC_MASK << pin_data->pin_conf.src_shअगरt;

	ग_लिखोl(val, (base_address + pin_data->pin_conf.offset));
	spin_unlock_irqrestore(&pinctrl->lock, flags);

	dev_dbg(pctrldev->dev, "pin:%u set slew:%d\n", pin, slew);
	वापस 0;
पूर्ण

अटल पूर्णांक ns2_pin_get_slew(काष्ठा pinctrl_dev *pctrldev, अचिन्हित पूर्णांक pin,
			    u16 *slew)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrldev);
	काष्ठा ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&pinctrl->lock, flags);
	val = पढ़ोl(pinctrl->pinconf_base + pin_data->pin_conf.offset);
	*slew = (val >> pin_data->pin_conf.src_shअगरt) & NS2_PIN_SRC_MASK;
	spin_unlock_irqrestore(&pinctrl->lock, flags);

	dev_dbg(pctrldev->dev, "pin:%u get slew:%d\n", pin, *slew);
	वापस 0;
पूर्ण

अटल पूर्णांक ns2_pin_set_pull(काष्ठा pinctrl_dev *pctrldev, अचिन्हित पूर्णांक pin,
			    bool pull_up, bool pull_करोwn)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrldev);
	काष्ठा ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	अचिन्हित दीर्घ flags;
	u32 val;
	व्योम __iomem *base_address;

	base_address = pinctrl->pinconf_base;
	spin_lock_irqsave(&pinctrl->lock, flags);
	val = पढ़ोl(base_address + pin_data->pin_conf.offset);
	val &= ~(NS2_PIN_PULL_MASK << pin_data->pin_conf.pull_shअगरt);

	अगर (pull_up == true)
		val |= NS2_PIN_PULL_UP << pin_data->pin_conf.pull_shअगरt;
	अगर (pull_करोwn == true)
		val |= NS2_PIN_PULL_DOWN << pin_data->pin_conf.pull_shअगरt;
	ग_लिखोl(val, (base_address + pin_data->pin_conf.offset));
	spin_unlock_irqrestore(&pinctrl->lock, flags);

	dev_dbg(pctrldev->dev, "pin:%u set pullup:%d pulldown: %d\n",
		pin, pull_up, pull_करोwn);
	वापस 0;
पूर्ण

अटल व्योम ns2_pin_get_pull(काष्ठा pinctrl_dev *pctrldev,
			     अचिन्हित पूर्णांक pin, bool *pull_up,
			     bool *pull_करोwn)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrldev);
	काष्ठा ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&pinctrl->lock, flags);
	val = पढ़ोl(pinctrl->pinconf_base + pin_data->pin_conf.offset);
	val = (val >> pin_data->pin_conf.pull_shअगरt) & NS2_PIN_PULL_MASK;
	*pull_up = false;
	*pull_करोwn = false;

	अगर (val == NS2_PIN_PULL_UP)
		*pull_up = true;

	अगर (val == NS2_PIN_PULL_DOWN)
		*pull_करोwn = true;
	spin_unlock_irqrestore(&pinctrl->lock, flags);
पूर्ण

अटल पूर्णांक ns2_pin_set_strength(काष्ठा pinctrl_dev *pctrldev, अचिन्हित पूर्णांक pin,
				u32 strength)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrldev);
	काष्ठा ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	u32 val;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *base_address;

	/* make sure drive strength is supported */
	अगर (strength < 2 || strength > 16 || (strength % 2))
		वापस -ENOTSUPP;

	base_address = pinctrl->pinconf_base;
	spin_lock_irqsave(&pinctrl->lock, flags);
	val = पढ़ोl(base_address + pin_data->pin_conf.offset);
	val &= ~(NS2_PIN_DRIVE_STRENGTH_MASK << pin_data->pin_conf.drive_shअगरt);
	val |= ((strength / 2) - 1) << pin_data->pin_conf.drive_shअगरt;
	ग_लिखोl(val, (base_address + pin_data->pin_conf.offset));
	spin_unlock_irqrestore(&pinctrl->lock, flags);

	dev_dbg(pctrldev->dev, "pin:%u set drive strength:%d mA\n",
		pin, strength);
	वापस 0;
पूर्ण

अटल पूर्णांक ns2_pin_get_strength(काष्ठा pinctrl_dev *pctrldev, अचिन्हित पूर्णांक pin,
				 u16 *strength)
अणु
	काष्ठा ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrldev);
	काष्ठा ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pinctrl->lock, flags);
	val = पढ़ोl(pinctrl->pinconf_base + pin_data->pin_conf.offset);
	*strength = (val >> pin_data->pin_conf.drive_shअगरt) &
					NS2_PIN_DRIVE_STRENGTH_MASK;
	*strength = (*strength + 1) * 2;
	spin_unlock_irqrestore(&pinctrl->lock, flags);

	dev_dbg(pctrldev->dev, "pin:%u get drive strength:%d mA\n",
		pin, *strength);
	वापस 0;
पूर्ण

अटल पूर्णांक ns2_pin_config_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			      अचिन्हित दीर्घ *config)
अणु
	काष्ठा ns2_pin *pin_data = pctldev->desc->pins[pin].drv_data;
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	bool pull_up, pull_करोwn;
	u16 arg = 0;
	पूर्णांक ret;

	अगर (pin_data->pin_conf.base == -1)
		वापस -ENOTSUPP;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		ns2_pin_get_pull(pctldev, pin, &pull_up, &pull_करोwn);
		अगर (!pull_up && !pull_करोwn)
			वापस 0;
		अन्यथा
			वापस -EINVAL;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		ns2_pin_get_pull(pctldev, pin, &pull_up, &pull_करोwn);
		अगर (pull_up)
			वापस 0;
		अन्यथा
			वापस -EINVAL;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		ns2_pin_get_pull(pctldev, pin, &pull_up, &pull_करोwn);
		अगर (pull_करोwn)
			वापस 0;
		अन्यथा
			वापस -EINVAL;

	हाल PIN_CONFIG_DRIVE_STRENGTH:
		ret = ns2_pin_get_strength(pctldev, pin, &arg);
		अगर (ret)
			वापस ret;
		*config = pinconf_to_config_packed(param, arg);
		वापस 0;

	हाल PIN_CONFIG_SLEW_RATE:
		ret = ns2_pin_get_slew(pctldev, pin, &arg);
		अगर (ret)
			वापस ret;
		*config = pinconf_to_config_packed(param, arg);
		वापस 0;

	हाल PIN_CONFIG_INPUT_ENABLE:
		ret = ns2_pin_get_enable(pctldev, pin);
		अगर (ret)
			वापस 0;
		अन्यथा
			वापस -EINVAL;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ns2_pin_config_set(काष्ठा pinctrl_dev *pctrldev, अचिन्हित पूर्णांक pin,
			      अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	क्रमागत pin_config_param param;
	अचिन्हित पूर्णांक i;
	u32 arg;
	पूर्णांक ret = -ENOTSUPP;

	अगर (pin_data->pin_conf.base == -1)
		वापस -ENOTSUPP;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			ret = ns2_pin_set_pull(pctrldev, pin, false, false);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_UP:
			ret = ns2_pin_set_pull(pctrldev, pin, true, false);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			ret = ns2_pin_set_pull(pctrldev, pin, false, true);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_DRIVE_STRENGTH:
			ret = ns2_pin_set_strength(pctrldev, pin, arg);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_SLEW_RATE:
			ret = ns2_pin_set_slew(pctrldev, pin, arg);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_INPUT_ENABLE:
			ret = ns2_pin_set_enable(pctrldev, pin, arg);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		शेष:
			dev_err(pctrldev->dev, "invalid configuration\n");
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण
अटल स्थिर काष्ठा pinmux_ops ns2_pinmux_ops = अणु
	.get_functions_count = ns2_get_functions_count,
	.get_function_name = ns2_get_function_name,
	.get_function_groups = ns2_get_function_groups,
	.set_mux = ns2_pinmux_enable,
पूर्ण;

अटल स्थिर काष्ठा pinconf_ops ns2_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = ns2_pin_config_get,
	.pin_config_set = ns2_pin_config_set,
पूर्ण;

अटल काष्ठा pinctrl_desc ns2_pinctrl_desc = अणु
	.name = "ns2-pinmux",
	.pctlops = &ns2_pinctrl_ops,
	.pmxops = &ns2_pinmux_ops,
	.confops = &ns2_pinconf_ops,
पूर्ण;

अटल पूर्णांक ns2_mux_log_init(काष्ठा ns2_pinctrl *pinctrl)
अणु
	काष्ठा ns2_mux_log *log;
	अचिन्हित पूर्णांक i;

	pinctrl->mux_log = devm_kसुस्मृति(pinctrl->dev, NS2_NUM_IOMUX,
					माप(काष्ठा ns2_mux_log),
					GFP_KERNEL);
	अगर (!pinctrl->mux_log)
		वापस -ENOMEM;

	क्रम (i = 0; i < NS2_NUM_IOMUX; i++)
		pinctrl->mux_log[i].is_configured = false;
	/* Group 0 uses bit 31 in the IOMUX_PAD_FUNCTION_0 रेजिस्टर */
	log = &pinctrl->mux_log[0];
	log->mux.base = NS2_PIN_MUX_BASE0;
	log->mux.offset = 0;
	log->mux.shअगरt = 31;
	log->mux.alt = 0;

	/*
	 * Groups 1 through 14 use two bits each in the
	 * IOMUX_PAD_FUNCTION_1 रेजिस्टर starting with
	 * bit position 30.
	 */
	क्रम (i = 1; i < (NS2_NUM_IOMUX - NS2_NUM_PWM_MUX); i++) अणु
		log = &pinctrl->mux_log[i];
		log->mux.base = NS2_PIN_MUX_BASE0;
		log->mux.offset = NS2_MUX_PAD_FUNC1_OFFSET;
		log->mux.shअगरt = 32 - (i * 2);
		log->mux.alt = 0;
	पूर्ण

	/*
	 * Groups 15 through 18 use one bit each in the
	 * AUX_SEL रेजिस्टर.
	 */
	क्रम (i = 0; i < NS2_NUM_PWM_MUX; i++) अणु
		log = &pinctrl->mux_log[(NS2_NUM_IOMUX - NS2_NUM_PWM_MUX) + i];
		log->mux.base = NS2_PIN_MUX_BASE1;
		log->mux.offset = 0;
		log->mux.shअगरt = i;
		log->mux.alt =  0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ns2_pinmux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ns2_pinctrl *pinctrl;
	काष्ठा resource *res;
	पूर्णांक i, ret;
	काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक num_pins = ARRAY_SIZE(ns2_pins);

	pinctrl = devm_kzalloc(&pdev->dev, माप(*pinctrl), GFP_KERNEL);
	अगर (!pinctrl)
		वापस -ENOMEM;

	pinctrl->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, pinctrl);
	spin_lock_init(&pinctrl->lock);

	pinctrl->base0 = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pinctrl->base0))
		वापस PTR_ERR(pinctrl->base0);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res)
		वापस -EINVAL;
	pinctrl->base1 = devm_ioremap(&pdev->dev, res->start,
					resource_size(res));
	अगर (!pinctrl->base1) अणु
		dev_err(&pdev->dev, "unable to map I/O space\n");
		वापस -ENOMEM;
	पूर्ण

	pinctrl->pinconf_base = devm_platक्रमm_ioremap_resource(pdev, 2);
	अगर (IS_ERR(pinctrl->pinconf_base))
		वापस PTR_ERR(pinctrl->pinconf_base);

	ret = ns2_mux_log_init(pinctrl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to initialize IOMUX log\n");
		वापस ret;
	पूर्ण

	pins = devm_kसुस्मृति(&pdev->dev, num_pins, माप(*pins), GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_pins; i++) अणु
		pins[i].number = ns2_pins[i].pin;
		pins[i].name = ns2_pins[i].name;
		pins[i].drv_data = &ns2_pins[i];
	पूर्ण

	pinctrl->groups = ns2_pin_groups;
	pinctrl->num_groups = ARRAY_SIZE(ns2_pin_groups);
	pinctrl->functions = ns2_pin_functions;
	pinctrl->num_functions = ARRAY_SIZE(ns2_pin_functions);
	ns2_pinctrl_desc.pins = pins;
	ns2_pinctrl_desc.npins = num_pins;

	pinctrl->pctl = pinctrl_रेजिस्टर(&ns2_pinctrl_desc, &pdev->dev,
			pinctrl);
	अगर (IS_ERR(pinctrl->pctl)) अणु
		dev_err(&pdev->dev, "unable to register IOMUX pinctrl\n");
		वापस PTR_ERR(pinctrl->pctl);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ns2_pinmux_of_match[] = अणु
	अणु.compatible = "brcm,ns2-pinmux"पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ns2_pinmux_driver = अणु
	.driver = अणु
		.name = "ns2-pinmux",
		.of_match_table = ns2_pinmux_of_match,
	पूर्ण,
	.probe = ns2_pinmux_probe,
पूर्ण;

अटल पूर्णांक __init ns2_pinmux_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ns2_pinmux_driver);
पूर्ण
arch_initcall(ns2_pinmux_init);
