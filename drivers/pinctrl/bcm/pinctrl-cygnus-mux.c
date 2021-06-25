<शैली गुरु>
/*
 * Copyright (C) 2014-2017 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

/*
 * Broadcom Cygnus IOMUX driver
 *
 * This file contains the Cygnus IOMUX driver that supports group based PINMUX
 * configuration. Although PINMUX configuration is मुख्यly group based, the
 * Cygnus IOMUX controller allows certain pins to be inभागidually muxed to GPIO
 * function, and thereक्रमe be controlled by the Cygnus ASIU GPIO controller
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"

#घोषणा CYGNUS_NUM_IOMUX_REGS     8
#घोषणा CYGNUS_NUM_MUX_PER_REG    8
#घोषणा CYGNUS_NUM_IOMUX          (CYGNUS_NUM_IOMUX_REGS * \
				   CYGNUS_NUM_MUX_PER_REG)

/*
 * Cygnus IOMUX रेजिस्टर description
 *
 * @offset: रेजिस्टर offset क्रम mux configuration of a group
 * @shअगरt: bit shअगरt क्रम mux configuration of a group
 * @alt: alternate function to set to
 */
काष्ठा cygnus_mux अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक alt;
पूर्ण;

/*
 * Keep track of Cygnus IOMUX configuration and prevent द्विगुन configuration
 *
 * @cygnus_mux: Cygnus IOMUX रेजिस्टर description
 * @is_configured: flag to indicate whether a mux setting has alपढ़ोy been
 * configured
 */
काष्ठा cygnus_mux_log अणु
	काष्ठा cygnus_mux mux;
	bool is_configured;
पूर्ण;

/*
 * Group based IOMUX configuration
 *
 * @name: name of the group
 * @pins: array of pins used by this group
 * @num_pins: total number of pins used by this group
 * @mux: Cygnus group based IOMUX configuration
 */
काष्ठा cygnus_pin_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित *pins;
	अचिन्हित num_pins;
	काष्ठा cygnus_mux mux;
पूर्ण;

/*
 * Cygnus mux function and supported pin groups
 *
 * @name: name of the function
 * @groups: array of groups that can be supported by this function
 * @num_groups: total number of groups that can be supported by this function
 */
काष्ठा cygnus_pin_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित num_groups;
पूर्ण;

/*
 * Cygnus IOMUX pinctrl core
 *
 * @pctl: poपूर्णांकer to pinctrl_dev
 * @dev: poपूर्णांकer to device
 * @base0: first I/O रेजिस्टर base of the Cygnus IOMUX controller
 * @base1: second I/O रेजिस्टर base
 * @groups: poपूर्णांकer to array of groups
 * @num_groups: total number of groups
 * @functions: poपूर्णांकer to array of functions
 * @num_functions: total number of functions
 * @mux_log: poपूर्णांकer to the array of mux logs
 * @lock: lock to protect रेजिस्टर access
 */
काष्ठा cygnus_pinctrl अणु
	काष्ठा pinctrl_dev *pctl;
	काष्ठा device *dev;
	व्योम __iomem *base0;
	व्योम __iomem *base1;

	स्थिर काष्ठा cygnus_pin_group *groups;
	अचिन्हित num_groups;

	स्थिर काष्ठा cygnus_pin_function *functions;
	अचिन्हित num_functions;

	काष्ठा cygnus_mux_log *mux_log;

	spinlock_t lock;
पूर्ण;

/*
 * Certain pins can be inभागidually muxed to GPIO function
 *
 * @is_supported: flag to indicate GPIO mux is supported क्रम this pin
 * @offset: रेजिस्टर offset क्रम GPIO mux override of a pin
 * @shअगरt: bit shअगरt क्रम GPIO mux override of a pin
 */
काष्ठा cygnus_gpio_mux अणु
	पूर्णांक is_supported;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक shअगरt;
पूर्ण;

/*
 * Description of a pin in Cygnus
 *
 * @pin: pin number
 * @name: pin name
 * @gpio_mux: GPIO override related inक्रमmation
 */
काष्ठा cygnus_pin अणु
	अचिन्हित pin;
	अक्षर *name;
	काष्ठा cygnus_gpio_mux gpio_mux;
पूर्ण;

#घोषणा CYGNUS_PIN_DESC(p, n, i, o, s)	\
अणु					\
	.pin = p,			\
	.name = n,			\
	.gpio_mux = अणु			\
		.is_supported = i,	\
		.offset = o,		\
		.shअगरt = s,		\
	पूर्ण,				\
पूर्ण

/*
 * List of pins in Cygnus
 */
अटल काष्ठा cygnus_pin cygnus_pins[] = अणु
	CYGNUS_PIN_DESC(0, "ext_device_reset_n", 0, 0, 0),
	CYGNUS_PIN_DESC(1, "chip_mode0", 0, 0, 0),
	CYGNUS_PIN_DESC(2, "chip_mode1", 0, 0, 0),
	CYGNUS_PIN_DESC(3, "chip_mode2", 0, 0, 0),
	CYGNUS_PIN_DESC(4, "chip_mode3", 0, 0, 0),
	CYGNUS_PIN_DESC(5, "chip_mode4", 0, 0, 0),
	CYGNUS_PIN_DESC(6, "bsc0_scl", 0, 0, 0),
	CYGNUS_PIN_DESC(7, "bsc0_sda", 0, 0, 0),
	CYGNUS_PIN_DESC(8, "bsc1_scl", 0, 0, 0),
	CYGNUS_PIN_DESC(9, "bsc1_sda", 0, 0, 0),
	CYGNUS_PIN_DESC(10, "d1w_dq", 1, 0x28, 0),
	CYGNUS_PIN_DESC(11, "d1wowstz_l", 1, 0x4, 28),
	CYGNUS_PIN_DESC(12, "gpio0", 0, 0, 0),
	CYGNUS_PIN_DESC(13, "gpio1", 0, 0, 0),
	CYGNUS_PIN_DESC(14, "gpio2", 0, 0, 0),
	CYGNUS_PIN_DESC(15, "gpio3", 0, 0, 0),
	CYGNUS_PIN_DESC(16, "gpio4", 0, 0, 0),
	CYGNUS_PIN_DESC(17, "gpio5", 0, 0, 0),
	CYGNUS_PIN_DESC(18, "gpio6", 0, 0, 0),
	CYGNUS_PIN_DESC(19, "gpio7", 0, 0, 0),
	CYGNUS_PIN_DESC(20, "gpio8", 0, 0, 0),
	CYGNUS_PIN_DESC(21, "gpio9", 0, 0, 0),
	CYGNUS_PIN_DESC(22, "gpio10", 0, 0, 0),
	CYGNUS_PIN_DESC(23, "gpio11", 0, 0, 0),
	CYGNUS_PIN_DESC(24, "gpio12", 0, 0, 0),
	CYGNUS_PIN_DESC(25, "gpio13", 0, 0, 0),
	CYGNUS_PIN_DESC(26, "gpio14", 0, 0, 0),
	CYGNUS_PIN_DESC(27, "gpio15", 0, 0, 0),
	CYGNUS_PIN_DESC(28, "gpio16", 0, 0, 0),
	CYGNUS_PIN_DESC(29, "gpio17", 0, 0, 0),
	CYGNUS_PIN_DESC(30, "gpio18", 0, 0, 0),
	CYGNUS_PIN_DESC(31, "gpio19", 0, 0, 0),
	CYGNUS_PIN_DESC(32, "gpio20", 0, 0, 0),
	CYGNUS_PIN_DESC(33, "gpio21", 0, 0, 0),
	CYGNUS_PIN_DESC(34, "gpio22", 0, 0, 0),
	CYGNUS_PIN_DESC(35, "gpio23", 0, 0, 0),
	CYGNUS_PIN_DESC(36, "mdc", 0, 0, 0),
	CYGNUS_PIN_DESC(37, "mdio", 0, 0, 0),
	CYGNUS_PIN_DESC(38, "pwm0", 1, 0x10, 30),
	CYGNUS_PIN_DESC(39, "pwm1", 1, 0x10, 28),
	CYGNUS_PIN_DESC(40, "pwm2", 1, 0x10, 26),
	CYGNUS_PIN_DESC(41, "pwm3", 1, 0x10, 24),
	CYGNUS_PIN_DESC(42, "sc0_clk", 1, 0x10, 22),
	CYGNUS_PIN_DESC(43, "sc0_cmdvcc_l", 1, 0x10, 20),
	CYGNUS_PIN_DESC(44, "sc0_detect", 1, 0x10, 18),
	CYGNUS_PIN_DESC(45, "sc0_fcb", 1, 0x10, 16),
	CYGNUS_PIN_DESC(46, "sc0_io", 1, 0x10, 14),
	CYGNUS_PIN_DESC(47, "sc0_rst_l", 1, 0x10, 12),
	CYGNUS_PIN_DESC(48, "sc1_clk", 1, 0x10, 10),
	CYGNUS_PIN_DESC(49, "sc1_cmdvcc_l", 1, 0x10, 8),
	CYGNUS_PIN_DESC(50, "sc1_detect", 1, 0x10, 6),
	CYGNUS_PIN_DESC(51, "sc1_fcb", 1, 0x10, 4),
	CYGNUS_PIN_DESC(52, "sc1_io", 1, 0x10, 2),
	CYGNUS_PIN_DESC(53, "sc1_rst_l", 1, 0x10, 0),
	CYGNUS_PIN_DESC(54, "spi0_clk", 1, 0x18, 10),
	CYGNUS_PIN_DESC(55, "spi0_mosi", 1, 0x18, 6),
	CYGNUS_PIN_DESC(56, "spi0_miso", 1, 0x18, 8),
	CYGNUS_PIN_DESC(57, "spi0_ss", 1, 0x18, 4),
	CYGNUS_PIN_DESC(58, "spi1_clk", 1, 0x18, 2),
	CYGNUS_PIN_DESC(59, "spi1_mosi", 1, 0x1c, 30),
	CYGNUS_PIN_DESC(60, "spi1_miso", 1, 0x18, 0),
	CYGNUS_PIN_DESC(61, "spi1_ss", 1, 0x1c, 28),
	CYGNUS_PIN_DESC(62, "spi2_clk", 1, 0x1c, 26),
	CYGNUS_PIN_DESC(63, "spi2_mosi", 1, 0x1c, 22),
	CYGNUS_PIN_DESC(64, "spi2_miso", 1, 0x1c, 24),
	CYGNUS_PIN_DESC(65, "spi2_ss", 1, 0x1c, 20),
	CYGNUS_PIN_DESC(66, "spi3_clk", 1, 0x1c, 18),
	CYGNUS_PIN_DESC(67, "spi3_mosi", 1, 0x1c, 14),
	CYGNUS_PIN_DESC(68, "spi3_miso", 1, 0x1c, 16),
	CYGNUS_PIN_DESC(69, "spi3_ss", 1, 0x1c, 12),
	CYGNUS_PIN_DESC(70, "uart0_cts", 1, 0x1c, 10),
	CYGNUS_PIN_DESC(71, "uart0_rts", 1, 0x1c, 8),
	CYGNUS_PIN_DESC(72, "uart0_rx", 1, 0x1c, 6),
	CYGNUS_PIN_DESC(73, "uart0_tx", 1, 0x1c, 4),
	CYGNUS_PIN_DESC(74, "uart1_cts", 1, 0x1c, 2),
	CYGNUS_PIN_DESC(75, "uart1_dcd", 1, 0x1c, 0),
	CYGNUS_PIN_DESC(76, "uart1_dsr", 1, 0x20, 14),
	CYGNUS_PIN_DESC(77, "uart1_dtr", 1, 0x20, 12),
	CYGNUS_PIN_DESC(78, "uart1_ri", 1, 0x20, 10),
	CYGNUS_PIN_DESC(79, "uart1_rts", 1, 0x20, 8),
	CYGNUS_PIN_DESC(80, "uart1_rx", 1, 0x20, 6),
	CYGNUS_PIN_DESC(81, "uart1_tx", 1, 0x20, 4),
	CYGNUS_PIN_DESC(82, "uart3_rx", 1, 0x20, 2),
	CYGNUS_PIN_DESC(83, "uart3_tx", 1, 0x20, 0),
	CYGNUS_PIN_DESC(84, "sdio1_clk_sdcard", 1, 0x14, 6),
	CYGNUS_PIN_DESC(85, "sdio1_cmd", 1, 0x14, 4),
	CYGNUS_PIN_DESC(86, "sdio1_data0", 1, 0x14, 2),
	CYGNUS_PIN_DESC(87, "sdio1_data1", 1, 0x14, 0),
	CYGNUS_PIN_DESC(88, "sdio1_data2", 1, 0x18, 30),
	CYGNUS_PIN_DESC(89, "sdio1_data3", 1, 0x18, 28),
	CYGNUS_PIN_DESC(90, "sdio1_wp_n", 1, 0x18, 24),
	CYGNUS_PIN_DESC(91, "sdio1_card_rst", 1, 0x14, 10),
	CYGNUS_PIN_DESC(92, "sdio1_led_on", 1, 0x18, 26),
	CYGNUS_PIN_DESC(93, "sdio1_cd", 1, 0x14, 8),
	CYGNUS_PIN_DESC(94, "sdio0_clk_sdcard", 1, 0x14, 26),
	CYGNUS_PIN_DESC(95, "sdio0_cmd", 1, 0x14, 24),
	CYGNUS_PIN_DESC(96, "sdio0_data0", 1, 0x14, 22),
	CYGNUS_PIN_DESC(97, "sdio0_data1", 1, 0x14, 20),
	CYGNUS_PIN_DESC(98, "sdio0_data2", 1, 0x14, 18),
	CYGNUS_PIN_DESC(99, "sdio0_data3", 1, 0x14, 16),
	CYGNUS_PIN_DESC(100, "sdio0_wp_n", 1, 0x14, 12),
	CYGNUS_PIN_DESC(101, "sdio0_card_rst", 1, 0x14, 30),
	CYGNUS_PIN_DESC(102, "sdio0_led_on", 1, 0x14, 14),
	CYGNUS_PIN_DESC(103, "sdio0_cd", 1, 0x14, 28),
	CYGNUS_PIN_DESC(104, "sflash_clk", 1, 0x18, 22),
	CYGNUS_PIN_DESC(105, "sflash_cs_l", 1, 0x18, 20),
	CYGNUS_PIN_DESC(106, "sflash_mosi", 1, 0x18, 14),
	CYGNUS_PIN_DESC(107, "sflash_miso", 1, 0x18, 16),
	CYGNUS_PIN_DESC(108, "sflash_wp_n", 1, 0x18, 12),
	CYGNUS_PIN_DESC(109, "sflash_hold_n", 1, 0x18, 18),
	CYGNUS_PIN_DESC(110, "nand_ale", 1, 0xc, 30),
	CYGNUS_PIN_DESC(111, "nand_ce0_l", 1, 0xc, 28),
	CYGNUS_PIN_DESC(112, "nand_ce1_l", 1, 0xc, 26),
	CYGNUS_PIN_DESC(113, "nand_cle", 1, 0xc, 24),
	CYGNUS_PIN_DESC(114, "nand_dq0", 1, 0xc, 22),
	CYGNUS_PIN_DESC(115, "nand_dq1", 1, 0xc, 20),
	CYGNUS_PIN_DESC(116, "nand_dq2", 1, 0xc, 18),
	CYGNUS_PIN_DESC(117, "nand_dq3", 1, 0xc, 16),
	CYGNUS_PIN_DESC(118, "nand_dq4", 1, 0xc, 14),
	CYGNUS_PIN_DESC(119, "nand_dq5", 1, 0xc, 12),
	CYGNUS_PIN_DESC(120, "nand_dq6", 1, 0xc, 10),
	CYGNUS_PIN_DESC(121, "nand_dq7", 1, 0xc, 8),
	CYGNUS_PIN_DESC(122, "nand_rb_l", 1, 0xc, 6),
	CYGNUS_PIN_DESC(123, "nand_re_l", 1, 0xc, 4),
	CYGNUS_PIN_DESC(124, "nand_we_l", 1, 0xc, 2),
	CYGNUS_PIN_DESC(125, "nand_wp_l", 1, 0xc, 0),
	CYGNUS_PIN_DESC(126, "lcd_clac", 1, 0x4, 26),
	CYGNUS_PIN_DESC(127, "lcd_clcp", 1, 0x4, 24),
	CYGNUS_PIN_DESC(128, "lcd_cld0", 1, 0x4, 22),
	CYGNUS_PIN_DESC(129, "lcd_cld1", 1, 0x4, 0),
	CYGNUS_PIN_DESC(130, "lcd_cld10", 1, 0x4, 20),
	CYGNUS_PIN_DESC(131, "lcd_cld11", 1, 0x4, 18),
	CYGNUS_PIN_DESC(132, "lcd_cld12", 1, 0x4, 16),
	CYGNUS_PIN_DESC(133, "lcd_cld13", 1, 0x4, 14),
	CYGNUS_PIN_DESC(134, "lcd_cld14", 1, 0x4, 12),
	CYGNUS_PIN_DESC(135, "lcd_cld15", 1, 0x4, 10),
	CYGNUS_PIN_DESC(136, "lcd_cld16", 1, 0x4, 8),
	CYGNUS_PIN_DESC(137, "lcd_cld17", 1, 0x4, 6),
	CYGNUS_PIN_DESC(138, "lcd_cld18", 1, 0x4, 4),
	CYGNUS_PIN_DESC(139, "lcd_cld19", 1, 0x4, 2),
	CYGNUS_PIN_DESC(140, "lcd_cld2", 1, 0x8, 22),
	CYGNUS_PIN_DESC(141, "lcd_cld20", 1, 0x8, 30),
	CYGNUS_PIN_DESC(142, "lcd_cld21", 1, 0x8, 28),
	CYGNUS_PIN_DESC(143, "lcd_cld22", 1, 0x8, 26),
	CYGNUS_PIN_DESC(144, "lcd_cld23", 1, 0x8, 24),
	CYGNUS_PIN_DESC(145, "lcd_cld3", 1, 0x8, 20),
	CYGNUS_PIN_DESC(146, "lcd_cld4", 1, 0x8, 18),
	CYGNUS_PIN_DESC(147, "lcd_cld5", 1, 0x8, 16),
	CYGNUS_PIN_DESC(148, "lcd_cld6", 1, 0x8, 14),
	CYGNUS_PIN_DESC(149, "lcd_cld7", 1, 0x8, 12),
	CYGNUS_PIN_DESC(150, "lcd_cld8", 1, 0x8, 10),
	CYGNUS_PIN_DESC(151, "lcd_cld9", 1, 0x8, 8),
	CYGNUS_PIN_DESC(152, "lcd_clfp", 1, 0x8, 6),
	CYGNUS_PIN_DESC(153, "lcd_clle", 1, 0x8, 4),
	CYGNUS_PIN_DESC(154, "lcd_cllp", 1, 0x8, 2),
	CYGNUS_PIN_DESC(155, "lcd_clpower", 1, 0x8, 0),
	CYGNUS_PIN_DESC(156, "camera_vsync", 1, 0x4, 30),
	CYGNUS_PIN_DESC(157, "camera_trigger", 1, 0x0, 0),
	CYGNUS_PIN_DESC(158, "camera_strobe", 1, 0x0, 2),
	CYGNUS_PIN_DESC(159, "camera_standby", 1, 0x0, 4),
	CYGNUS_PIN_DESC(160, "camera_reset_n", 1, 0x0, 6),
	CYGNUS_PIN_DESC(161, "camera_pixdata9", 1, 0x0, 8),
	CYGNUS_PIN_DESC(162, "camera_pixdata8", 1, 0x0, 10),
	CYGNUS_PIN_DESC(163, "camera_pixdata7", 1, 0x0, 12),
	CYGNUS_PIN_DESC(164, "camera_pixdata6", 1, 0x0, 14),
	CYGNUS_PIN_DESC(165, "camera_pixdata5", 1, 0x0, 16),
	CYGNUS_PIN_DESC(166, "camera_pixdata4", 1, 0x0, 18),
	CYGNUS_PIN_DESC(167, "camera_pixdata3", 1, 0x0, 20),
	CYGNUS_PIN_DESC(168, "camera_pixdata2", 1, 0x0, 22),
	CYGNUS_PIN_DESC(169, "camera_pixdata1", 1, 0x0, 24),
	CYGNUS_PIN_DESC(170, "camera_pixdata0", 1, 0x0, 26),
	CYGNUS_PIN_DESC(171, "camera_pixclk", 1, 0x0, 28),
	CYGNUS_PIN_DESC(172, "camera_hsync", 1, 0x0, 30),
	CYGNUS_PIN_DESC(173, "camera_pll_ref_clk", 0, 0, 0),
	CYGNUS_PIN_DESC(174, "usb_id_indication", 0, 0, 0),
	CYGNUS_PIN_DESC(175, "usb_vbus_indication", 0, 0, 0),
	CYGNUS_PIN_DESC(176, "gpio0_3p3", 0, 0, 0),
	CYGNUS_PIN_DESC(177, "gpio1_3p3", 0, 0, 0),
	CYGNUS_PIN_DESC(178, "gpio2_3p3", 0, 0, 0),
	CYGNUS_PIN_DESC(179, "gpio3_3p3", 0, 0, 0),
पूर्ण;

/*
 * List of groups of pins
 */
अटल स्थिर अचिन्हित bsc1_pins[] = अणु 8, 9 पूर्ण;
अटल स्थिर अचिन्हित pcie_clkreq_pins[] = अणु 8, 9 पूर्ण;

अटल स्थिर अचिन्हित i2s2_0_pins[] = अणु 12 पूर्ण;
अटल स्थिर अचिन्हित i2s2_1_pins[] = अणु 13 पूर्ण;
अटल स्थिर अचिन्हित i2s2_2_pins[] = अणु 14 पूर्ण;
अटल स्थिर अचिन्हित i2s2_3_pins[] = अणु 15 पूर्ण;
अटल स्थिर अचिन्हित i2s2_4_pins[] = अणु 16 पूर्ण;

अटल स्थिर अचिन्हित pwm4_pins[] = अणु 17 पूर्ण;
अटल स्थिर अचिन्हित pwm5_pins[] = अणु 18 पूर्ण;

अटल स्थिर अचिन्हित key0_pins[] = अणु 20 पूर्ण;
अटल स्थिर अचिन्हित key1_pins[] = अणु 21 पूर्ण;
अटल स्थिर अचिन्हित key2_pins[] = अणु 22 पूर्ण;
अटल स्थिर अचिन्हित key3_pins[] = अणु 23 पूर्ण;
अटल स्थिर अचिन्हित key4_pins[] = अणु 24 पूर्ण;
अटल स्थिर अचिन्हित key5_pins[] = अणु 25 पूर्ण;

अटल स्थिर अचिन्हित key6_pins[] = अणु 26 पूर्ण;
अटल स्थिर अचिन्हित audio_dte0_pins[] = अणु 26 पूर्ण;

अटल स्थिर अचिन्हित key7_pins[] = अणु 27 पूर्ण;
अटल स्थिर अचिन्हित audio_dte1_pins[] = अणु 27 पूर्ण;

अटल स्थिर अचिन्हित key8_pins[] = अणु 28 पूर्ण;
अटल स्थिर अचिन्हित key9_pins[] = अणु 29 पूर्ण;
अटल स्थिर अचिन्हित key10_pins[] = अणु 30 पूर्ण;
अटल स्थिर अचिन्हित key11_pins[] = अणु 31 पूर्ण;
अटल स्थिर अचिन्हित key12_pins[] = अणु 32 पूर्ण;
अटल स्थिर अचिन्हित key13_pins[] = अणु 33 पूर्ण;

अटल स्थिर अचिन्हित key14_pins[] = अणु 34 पूर्ण;
अटल स्थिर अचिन्हित audio_dte2_pins[] = अणु 34 पूर्ण;

अटल स्थिर अचिन्हित key15_pins[] = अणु 35 पूर्ण;
अटल स्थिर अचिन्हित audio_dte3_pins[] = अणु 35 पूर्ण;

अटल स्थिर अचिन्हित pwm0_pins[] = अणु 38 पूर्ण;
अटल स्थिर अचिन्हित pwm1_pins[] = अणु 39 पूर्ण;
अटल स्थिर अचिन्हित pwm2_pins[] = अणु 40 पूर्ण;
अटल स्थिर अचिन्हित pwm3_pins[] = अणु 41 पूर्ण;

अटल स्थिर अचिन्हित sdio0_pins[] = अणु 94, 95, 96, 97, 98, 99 पूर्ण;

अटल स्थिर अचिन्हित smart_card0_pins[] = अणु 42, 43, 44, 46, 47 पूर्ण;
अटल स्थिर अचिन्हित i2s0_0_pins[] = अणु 42, 43, 44, 46 पूर्ण;
अटल स्थिर अचिन्हित spdअगर_pins[] = अणु 47 पूर्ण;

अटल स्थिर अचिन्हित smart_card1_pins[] = अणु 48, 49, 50, 52, 53 पूर्ण;
अटल स्थिर अचिन्हित i2s1_0_pins[] = अणु 48, 49, 50, 52 पूर्ण;

अटल स्थिर अचिन्हित spi0_pins[] = अणु 54, 55, 56, 57 पूर्ण;

अटल स्थिर अचिन्हित spi1_pins[] = अणु 58, 59, 60, 61 पूर्ण;

अटल स्थिर अचिन्हित spi2_pins[] = अणु 62, 63, 64, 65 पूर्ण;

अटल स्थिर अचिन्हित spi3_pins[] = अणु 66, 67, 68, 69 पूर्ण;
अटल स्थिर अचिन्हित sw_led0_0_pins[] = अणु 66, 67, 68, 69 पूर्ण;

अटल स्थिर अचिन्हित d1w_pins[] = अणु 10, 11 पूर्ण;
अटल स्थिर अचिन्हित uart4_pins[] = अणु 10, 11 पूर्ण;
अटल स्थिर अचिन्हित sw_led2_0_pins[] = अणु 10, 11 पूर्ण;

अटल स्थिर अचिन्हित lcd_pins[] = अणु 126, 127, 128, 129, 130, 131, 132, 133,
	134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147,
	148, 149, 150, 151, 152, 153, 154, 155 पूर्ण;
अटल स्थिर अचिन्हित sram_0_pins[] = अणु 126, 127, 128, 129, 130, 131, 132, 133,
	134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147,
	148, 149, 150, 151, 152, 153, 154, 155 पूर्ण;
अटल स्थिर अचिन्हित spi5_pins[] = अणु 141, 142, 143, 144 पूर्ण;

अटल स्थिर अचिन्हित uart0_pins[] = अणु 70, 71, 72, 73 पूर्ण;
अटल स्थिर अचिन्हित sw_led0_1_pins[] = अणु 70, 71, 72, 73 पूर्ण;

अटल स्थिर अचिन्हित uart1_dte_pins[] = अणु 75, 76, 77, 78 पूर्ण;
अटल स्थिर अचिन्हित uart2_pins[] = अणु 75, 76, 77, 78 पूर्ण;

अटल स्थिर अचिन्हित uart1_pins[] = अणु 74, 79, 80, 81 पूर्ण;

अटल स्थिर अचिन्हित uart3_pins[] = अणु 82, 83 पूर्ण;

अटल स्थिर अचिन्हित qspi_0_pins[] = अणु 104, 105, 106, 107 पूर्ण;

अटल स्थिर अचिन्हित nand_pins[] = अणु 110, 111, 112, 113, 114, 115, 116, 117,
	118, 119, 120, 121, 122, 123, 124, 125 पूर्ण;

अटल स्थिर अचिन्हित sdio0_cd_pins[] = अणु 103 पूर्ण;

अटल स्थिर अचिन्हित sdio0_mmc_pins[] = अणु 100, 101, 102 पूर्ण;

अटल स्थिर अचिन्हित sdio1_data_0_pins[] = अणु 86, 87 पूर्ण;
अटल स्थिर अचिन्हित can0_pins[] = अणु 86, 87 पूर्ण;
अटल स्थिर अचिन्हित spi4_0_pins[] = अणु 86, 87 पूर्ण;

अटल स्थिर अचिन्हित sdio1_data_1_pins[] = अणु 88, 89 पूर्ण;
अटल स्थिर अचिन्हित can1_pins[] = अणु 88, 89 पूर्ण;
अटल स्थिर अचिन्हित spi4_1_pins[] = अणु 88, 89 पूर्ण;

अटल स्थिर अचिन्हित sdio1_cd_pins[] = अणु 93 पूर्ण;

अटल स्थिर अचिन्हित sdio1_led_pins[] = अणु 84, 85 पूर्ण;
अटल स्थिर अचिन्हित sw_led2_1_pins[] = अणु 84, 85 पूर्ण;

अटल स्थिर अचिन्हित sdio1_mmc_pins[] = अणु 90, 91, 92 पूर्ण;

अटल स्थिर अचिन्हित cam_led_pins[] = अणु 156, 157, 158, 159, 160 पूर्ण;
अटल स्थिर अचिन्हित sw_led1_pins[] = अणु 156, 157, 158, 159 पूर्ण;

अटल स्थिर अचिन्हित cam_0_pins[] = अणु 169, 170, 171, 169, 170 पूर्ण;

अटल स्थिर अचिन्हित cam_1_pins[] = अणु 161, 162, 163, 164, 165, 166, 167,
	168 पूर्ण;
अटल स्थिर अचिन्हित sram_1_pins[] = अणु 161, 162, 163, 164, 165, 166, 167,
	168 पूर्ण;

अटल स्थिर अचिन्हित qspi_1_pins[] = अणु 108, 109 पूर्ण;

अटल स्थिर अचिन्हित smart_card0_fcb_pins[] = अणु 45 पूर्ण;
अटल स्थिर अचिन्हित i2s0_1_pins[] = अणु 45 पूर्ण;

अटल स्थिर अचिन्हित smart_card1_fcb_pins[] = अणु 51 पूर्ण;
अटल स्थिर अचिन्हित i2s1_1_pins[] = अणु 51 पूर्ण;

अटल स्थिर अचिन्हित gpio0_3p3_pins[] = अणु 176 पूर्ण;
अटल स्थिर अचिन्हित usb0_oc_pins[] = अणु 176 पूर्ण;

अटल स्थिर अचिन्हित gpio1_3p3_pins[] = अणु 177 पूर्ण;
अटल स्थिर अचिन्हित usb1_oc_pins[] = अणु 177 पूर्ण;

अटल स्थिर अचिन्हित gpio2_3p3_pins[] = अणु 178 पूर्ण;
अटल स्थिर अचिन्हित usb2_oc_pins[] = अणु 178 पूर्ण;

#घोषणा CYGNUS_PIN_GROUP(group_name, off, sh, al)	\
अणु							\
	.name = __stringअगरy(group_name) "_grp",		\
	.pins = group_name ## _pins,			\
	.num_pins = ARRAY_SIZE(group_name ## _pins),	\
	.mux = अणु					\
		.offset = off,				\
		.shअगरt = sh,				\
		.alt = al,				\
	पूर्ण						\
पूर्ण

/*
 * List of Cygnus pin groups
 */
अटल स्थिर काष्ठा cygnus_pin_group cygnus_pin_groups[] = अणु
	CYGNUS_PIN_GROUP(i2s2_0, 0x0, 0, 2),
	CYGNUS_PIN_GROUP(i2s2_1, 0x0, 4, 2),
	CYGNUS_PIN_GROUP(i2s2_2, 0x0, 8, 2),
	CYGNUS_PIN_GROUP(i2s2_3, 0x0, 12, 2),
	CYGNUS_PIN_GROUP(i2s2_4, 0x0, 16, 2),
	CYGNUS_PIN_GROUP(pwm4, 0x0, 20, 0),
	CYGNUS_PIN_GROUP(pwm5, 0x0, 24, 2),
	CYGNUS_PIN_GROUP(key0, 0x4, 0, 1),
	CYGNUS_PIN_GROUP(key1, 0x4, 4, 1),
	CYGNUS_PIN_GROUP(key2, 0x4, 8, 1),
	CYGNUS_PIN_GROUP(key3, 0x4, 12, 1),
	CYGNUS_PIN_GROUP(key4, 0x4, 16, 1),
	CYGNUS_PIN_GROUP(key5, 0x4, 20, 1),
	CYGNUS_PIN_GROUP(key6, 0x4, 24, 1),
	CYGNUS_PIN_GROUP(audio_dte0, 0x4, 24, 2),
	CYGNUS_PIN_GROUP(key7, 0x4, 28, 1),
	CYGNUS_PIN_GROUP(audio_dte1, 0x4, 28, 2),
	CYGNUS_PIN_GROUP(key8, 0x8, 0, 1),
	CYGNUS_PIN_GROUP(key9, 0x8, 4, 1),
	CYGNUS_PIN_GROUP(key10, 0x8, 8, 1),
	CYGNUS_PIN_GROUP(key11, 0x8, 12, 1),
	CYGNUS_PIN_GROUP(key12, 0x8, 16, 1),
	CYGNUS_PIN_GROUP(key13, 0x8, 20, 1),
	CYGNUS_PIN_GROUP(key14, 0x8, 24, 1),
	CYGNUS_PIN_GROUP(audio_dte2, 0x8, 24, 2),
	CYGNUS_PIN_GROUP(key15, 0x8, 28, 1),
	CYGNUS_PIN_GROUP(audio_dte3, 0x8, 28, 2),
	CYGNUS_PIN_GROUP(pwm0, 0xc, 0, 0),
	CYGNUS_PIN_GROUP(pwm1, 0xc, 4, 0),
	CYGNUS_PIN_GROUP(pwm2, 0xc, 8, 0),
	CYGNUS_PIN_GROUP(pwm3, 0xc, 12, 0),
	CYGNUS_PIN_GROUP(sdio0, 0xc, 16, 0),
	CYGNUS_PIN_GROUP(smart_card0, 0xc, 20, 0),
	CYGNUS_PIN_GROUP(i2s0_0, 0xc, 20, 1),
	CYGNUS_PIN_GROUP(spdअगर, 0xc, 20, 1),
	CYGNUS_PIN_GROUP(smart_card1, 0xc, 24, 0),
	CYGNUS_PIN_GROUP(i2s1_0, 0xc, 24, 1),
	CYGNUS_PIN_GROUP(spi0, 0x10, 0, 0),
	CYGNUS_PIN_GROUP(spi1, 0x10, 4, 0),
	CYGNUS_PIN_GROUP(spi2, 0x10, 8, 0),
	CYGNUS_PIN_GROUP(spi3, 0x10, 12, 0),
	CYGNUS_PIN_GROUP(sw_led0_0, 0x10, 12, 2),
	CYGNUS_PIN_GROUP(d1w, 0x10, 16, 0),
	CYGNUS_PIN_GROUP(uart4, 0x10, 16, 1),
	CYGNUS_PIN_GROUP(sw_led2_0, 0x10, 16, 2),
	CYGNUS_PIN_GROUP(lcd, 0x10, 20, 0),
	CYGNUS_PIN_GROUP(sram_0, 0x10, 20, 1),
	CYGNUS_PIN_GROUP(spi5, 0x10, 20, 2),
	CYGNUS_PIN_GROUP(uart0, 0x14, 0, 0),
	CYGNUS_PIN_GROUP(sw_led0_1, 0x14, 0, 2),
	CYGNUS_PIN_GROUP(uart1_dte, 0x14, 4, 0),
	CYGNUS_PIN_GROUP(uart2, 0x14, 4, 1),
	CYGNUS_PIN_GROUP(uart1, 0x14, 8, 0),
	CYGNUS_PIN_GROUP(uart3, 0x14, 12, 0),
	CYGNUS_PIN_GROUP(qspi_0, 0x14, 16, 0),
	CYGNUS_PIN_GROUP(nand, 0x14, 20, 0),
	CYGNUS_PIN_GROUP(sdio0_cd, 0x18, 0, 0),
	CYGNUS_PIN_GROUP(sdio0_mmc, 0x18, 4, 0),
	CYGNUS_PIN_GROUP(sdio1_data_0, 0x18, 8, 0),
	CYGNUS_PIN_GROUP(can0, 0x18, 8, 1),
	CYGNUS_PIN_GROUP(spi4_0, 0x18, 8, 2),
	CYGNUS_PIN_GROUP(sdio1_data_1, 0x18, 12, 0),
	CYGNUS_PIN_GROUP(can1, 0x18, 12, 1),
	CYGNUS_PIN_GROUP(spi4_1, 0x18, 12, 2),
	CYGNUS_PIN_GROUP(sdio1_cd, 0x18, 16, 0),
	CYGNUS_PIN_GROUP(sdio1_led, 0x18, 20, 0),
	CYGNUS_PIN_GROUP(sw_led2_1, 0x18, 20, 2),
	CYGNUS_PIN_GROUP(sdio1_mmc, 0x18, 24, 0),
	CYGNUS_PIN_GROUP(cam_led, 0x1c, 0, 0),
	CYGNUS_PIN_GROUP(sw_led1, 0x1c, 0, 1),
	CYGNUS_PIN_GROUP(cam_0, 0x1c, 4, 0),
	CYGNUS_PIN_GROUP(cam_1, 0x1c, 8, 0),
	CYGNUS_PIN_GROUP(sram_1, 0x1c, 8, 1),
	CYGNUS_PIN_GROUP(qspi_1, 0x1c, 12, 0),
	CYGNUS_PIN_GROUP(bsc1, 0x1c, 16, 0),
	CYGNUS_PIN_GROUP(pcie_clkreq, 0x1c, 16, 1),
	CYGNUS_PIN_GROUP(smart_card0_fcb, 0x20, 0, 0),
	CYGNUS_PIN_GROUP(i2s0_1, 0x20, 0, 1),
	CYGNUS_PIN_GROUP(smart_card1_fcb, 0x20, 4, 0),
	CYGNUS_PIN_GROUP(i2s1_1, 0x20, 4, 1),
	CYGNUS_PIN_GROUP(gpio0_3p3, 0x28, 0, 0),
	CYGNUS_PIN_GROUP(usb0_oc, 0x28, 0, 1),
	CYGNUS_PIN_GROUP(gpio1_3p3, 0x28, 4, 0),
	CYGNUS_PIN_GROUP(usb1_oc, 0x28, 4, 1),
	CYGNUS_PIN_GROUP(gpio2_3p3, 0x28, 8, 0),
	CYGNUS_PIN_GROUP(usb2_oc, 0x28, 8, 1),
पूर्ण;

/*
 * List of groups supported by functions
 */
अटल स्थिर अक्षर * स्थिर i2s0_grps[] = अणु "i2s0_0_grp", "i2s0_1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s1_grps[] = अणु "i2s1_0_grp", "i2s1_1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s2_grps[] = अणु "i2s2_0_grp", "i2s2_1_grp",
	"i2s2_2_grp", "i2s2_3_grp", "i2s2_4_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर spdअगर_grps[] = अणु "spdif_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm0_grps[] = अणु "pwm0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm1_grps[] = अणु "pwm1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm2_grps[] = अणु "pwm2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm3_grps[] = अणु "pwm3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm4_grps[] = अणु "pwm4_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm5_grps[] = अणु "pwm5_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर key_grps[] = अणु "key0_grp", "key1_grp", "key2_grp",
	"key3_grp", "key4_grp", "key5_grp", "key6_grp", "key7_grp", "key8_grp",
	"key9_grp", "key10_grp", "key11_grp", "key12_grp", "key13_grp",
	"key14_grp", "key15_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर audio_dte_grps[] = अणु "audio_dte0_grp",
	"audio_dte1_grp", "audio_dte2_grp", "audio_dte3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर smart_card0_grps[] = अणु "smart_card0_grp",
	"smart_card0_fcb_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर smart_card1_grps[] = अणु "smart_card1_grp",
	"smart_card1_fcb_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर spi0_grps[] = अणु "spi0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर spi1_grps[] = अणु "spi1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर spi2_grps[] = अणु "spi2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर spi3_grps[] = अणु "spi3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर spi4_grps[] = अणु "spi4_0_grp", "spi4_1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर spi5_grps[] = अणु "spi5_grp" पूर्ण;

अटल स्थिर अक्षर * स्थिर sw_led0_grps[] = अणु "sw_led0_0_grp",
	"sw_led0_1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर sw_led1_grps[] = अणु "sw_led1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर sw_led2_grps[] = अणु "sw_led2_0_grp",
	"sw_led2_1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर d1w_grps[] = अणु "d1w_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर lcd_grps[] = अणु "lcd_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर sram_grps[] = अणु "sram_0_grp", "sram_1_grp" पूर्ण;

अटल स्थिर अक्षर * स्थिर uart0_grps[] = अणु "uart0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart1_grps[] = अणु "uart1_grp", "uart1_dte_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart2_grps[] = अणु "uart2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart3_grps[] = अणु "uart3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart4_grps[] = अणु "uart4_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_grps[] = अणु "qspi_0_grp", "qspi_1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर nand_grps[] = अणु "nand_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio0_grps[] = अणु "sdio0_grp", "sdio0_cd_grp",
	"sdio0_mmc_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio1_grps[] = अणु "sdio1_data_0_grp",
	"sdio1_data_1_grp", "sdio1_cd_grp", "sdio1_led_grp", "sdio1_mmc_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर can0_grps[] = अणु "can0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर can1_grps[] = अणु "can1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर cam_grps[] = अणु "cam_led_grp", "cam_0_grp",
	"cam_1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bsc1_grps[] = अणु "bsc1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pcie_clkreq_grps[] = अणु "pcie_clkreq_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर usb0_oc_grps[] = अणु "usb0_oc_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर usb1_oc_grps[] = अणु "usb1_oc_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर usb2_oc_grps[] = अणु "usb2_oc_grp" पूर्ण;

#घोषणा CYGNUS_PIN_FUNCTION(func)				\
अणु								\
	.name = #func,						\
	.groups = func ## _grps,				\
	.num_groups = ARRAY_SIZE(func ## _grps),		\
पूर्ण

/*
 * List of supported functions in Cygnus
 */
अटल स्थिर काष्ठा cygnus_pin_function cygnus_pin_functions[] = अणु
	CYGNUS_PIN_FUNCTION(i2s0),
	CYGNUS_PIN_FUNCTION(i2s1),
	CYGNUS_PIN_FUNCTION(i2s2),
	CYGNUS_PIN_FUNCTION(spdअगर),
	CYGNUS_PIN_FUNCTION(pwm0),
	CYGNUS_PIN_FUNCTION(pwm1),
	CYGNUS_PIN_FUNCTION(pwm2),
	CYGNUS_PIN_FUNCTION(pwm3),
	CYGNUS_PIN_FUNCTION(pwm4),
	CYGNUS_PIN_FUNCTION(pwm5),
	CYGNUS_PIN_FUNCTION(key),
	CYGNUS_PIN_FUNCTION(audio_dte),
	CYGNUS_PIN_FUNCTION(smart_card0),
	CYGNUS_PIN_FUNCTION(smart_card1),
	CYGNUS_PIN_FUNCTION(spi0),
	CYGNUS_PIN_FUNCTION(spi1),
	CYGNUS_PIN_FUNCTION(spi2),
	CYGNUS_PIN_FUNCTION(spi3),
	CYGNUS_PIN_FUNCTION(spi4),
	CYGNUS_PIN_FUNCTION(spi5),
	CYGNUS_PIN_FUNCTION(sw_led0),
	CYGNUS_PIN_FUNCTION(sw_led1),
	CYGNUS_PIN_FUNCTION(sw_led2),
	CYGNUS_PIN_FUNCTION(d1w),
	CYGNUS_PIN_FUNCTION(lcd),
	CYGNUS_PIN_FUNCTION(sram),
	CYGNUS_PIN_FUNCTION(uart0),
	CYGNUS_PIN_FUNCTION(uart1),
	CYGNUS_PIN_FUNCTION(uart2),
	CYGNUS_PIN_FUNCTION(uart3),
	CYGNUS_PIN_FUNCTION(uart4),
	CYGNUS_PIN_FUNCTION(qspi),
	CYGNUS_PIN_FUNCTION(nand),
	CYGNUS_PIN_FUNCTION(sdio0),
	CYGNUS_PIN_FUNCTION(sdio1),
	CYGNUS_PIN_FUNCTION(can0),
	CYGNUS_PIN_FUNCTION(can1),
	CYGNUS_PIN_FUNCTION(cam),
	CYGNUS_PIN_FUNCTION(bsc1),
	CYGNUS_PIN_FUNCTION(pcie_clkreq),
	CYGNUS_PIN_FUNCTION(usb0_oc),
	CYGNUS_PIN_FUNCTION(usb1_oc),
	CYGNUS_PIN_FUNCTION(usb2_oc),
पूर्ण;

अटल पूर्णांक cygnus_get_groups_count(काष्ठा pinctrl_dev *pctrl_dev)
अणु
	काष्ठा cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->num_groups;
पूर्ण

अटल स्थिर अक्षर *cygnus_get_group_name(काष्ठा pinctrl_dev *pctrl_dev,
					 अचिन्हित selector)
अणु
	काष्ठा cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->groups[selector].name;
पूर्ण

अटल पूर्णांक cygnus_get_group_pins(काष्ठा pinctrl_dev *pctrl_dev,
				 अचिन्हित selector, स्थिर अचिन्हित **pins,
				 अचिन्हित *num_pins)
अणु
	काष्ठा cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	*pins = pinctrl->groups[selector].pins;
	*num_pins = pinctrl->groups[selector].num_pins;

	वापस 0;
पूर्ण

अटल व्योम cygnus_pin_dbg_show(काष्ठा pinctrl_dev *pctrl_dev,
				काष्ठा seq_file *s, अचिन्हित offset)
अणु
	seq_म_लिखो(s, " %s", dev_name(pctrl_dev->dev));
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops cygnus_pinctrl_ops = अणु
	.get_groups_count = cygnus_get_groups_count,
	.get_group_name = cygnus_get_group_name,
	.get_group_pins = cygnus_get_group_pins,
	.pin_dbg_show = cygnus_pin_dbg_show,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक cygnus_get_functions_count(काष्ठा pinctrl_dev *pctrl_dev)
अणु
	काष्ठा cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->num_functions;
पूर्ण

अटल स्थिर अक्षर *cygnus_get_function_name(काष्ठा pinctrl_dev *pctrl_dev,
					    अचिन्हित selector)
अणु
	काष्ठा cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->functions[selector].name;
पूर्ण

अटल पूर्णांक cygnus_get_function_groups(काष्ठा pinctrl_dev *pctrl_dev,
				      अचिन्हित selector,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	*groups = pinctrl->functions[selector].groups;
	*num_groups = pinctrl->functions[selector].num_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_pinmux_set(काष्ठा cygnus_pinctrl *pinctrl,
			     स्थिर काष्ठा cygnus_pin_function *func,
			     स्थिर काष्ठा cygnus_pin_group *grp,
			     काष्ठा cygnus_mux_log *mux_log)
अणु
	स्थिर काष्ठा cygnus_mux *mux = &grp->mux;
	पूर्णांक i;
	u32 val, mask = 0x7;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < CYGNUS_NUM_IOMUX; i++) अणु
		अगर (mux->offset != mux_log[i].mux.offset ||
		    mux->shअगरt != mux_log[i].mux.shअगरt)
			जारी;

		/* match found अगर we reach here */

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
		पूर्ण अन्यथा अणु
			/*
			 * One tries to configure it to the same function.
			 * Just quit and करोn't bother
			 */
			वापस 0;
		पूर्ण
	पूर्ण

	mux_log[i].mux.alt = mux->alt;
	mux_log[i].is_configured = true;

	spin_lock_irqsave(&pinctrl->lock, flags);

	val = पढ़ोl(pinctrl->base0 + grp->mux.offset);
	val &= ~(mask << grp->mux.shअगरt);
	val |= grp->mux.alt << grp->mux.shअगरt;
	ग_लिखोl(val, pinctrl->base0 + grp->mux.offset);

	spin_unlock_irqrestore(&pinctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_pinmux_set_mux(काष्ठा pinctrl_dev *pctrl_dev,
				 अचिन्हित func_select, अचिन्हित grp_select)
अणु
	काष्ठा cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	स्थिर काष्ठा cygnus_pin_function *func =
		&pinctrl->functions[func_select];
	स्थिर काष्ठा cygnus_pin_group *grp = &pinctrl->groups[grp_select];

	dev_dbg(pctrl_dev->dev, "func:%u name:%s grp:%u name:%s\n",
		func_select, func->name, grp_select, grp->name);

	dev_dbg(pctrl_dev->dev, "offset:0x%08x shift:%u alt:%u\n",
		grp->mux.offset, grp->mux.shअगरt, grp->mux.alt);

	वापस cygnus_pinmux_set(pinctrl, func, grp, pinctrl->mux_log);
पूर्ण

अटल पूर्णांक cygnus_gpio_request_enable(काष्ठा pinctrl_dev *pctrl_dev,
				      काष्ठा pinctrl_gpio_range *range,
				      अचिन्हित pin)
अणु
	काष्ठा cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	स्थिर काष्ठा cygnus_gpio_mux *mux = pctrl_dev->desc->pins[pin].drv_data;
	u32 val;
	अचिन्हित दीर्घ flags;

	/* not all pins support GPIO pinmux override */
	अगर (!mux->is_supported)
		वापस -ENOTSUPP;

	spin_lock_irqsave(&pinctrl->lock, flags);

	val = पढ़ोl(pinctrl->base1 + mux->offset);
	val |= 0x3 << mux->shअगरt;
	ग_लिखोl(val, pinctrl->base1 + mux->offset);

	spin_unlock_irqrestore(&pinctrl->lock, flags);

	dev_dbg(pctrl_dev->dev,
		"gpio request enable pin=%u offset=0x%x shift=%u\n",
		pin, mux->offset, mux->shअगरt);

	वापस 0;
पूर्ण

अटल व्योम cygnus_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctrl_dev,
				     काष्ठा pinctrl_gpio_range *range,
				     अचिन्हित pin)
अणु
	काष्ठा cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	काष्ठा cygnus_gpio_mux *mux = pctrl_dev->desc->pins[pin].drv_data;
	u32 val;
	अचिन्हित दीर्घ flags;

	अगर (!mux->is_supported)
		वापस;

	spin_lock_irqsave(&pinctrl->lock, flags);

	val = पढ़ोl(pinctrl->base1 + mux->offset);
	val &= ~(0x3 << mux->shअगरt);
	ग_लिखोl(val, pinctrl->base1 + mux->offset);

	spin_unlock_irqrestore(&pinctrl->lock, flags);

	dev_err(pctrl_dev->dev,
		"gpio disable free pin=%u offset=0x%x shift=%u\n",
		pin, mux->offset, mux->shअगरt);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops cygnus_pinmux_ops = अणु
	.get_functions_count = cygnus_get_functions_count,
	.get_function_name = cygnus_get_function_name,
	.get_function_groups = cygnus_get_function_groups,
	.set_mux = cygnus_pinmux_set_mux,
	.gpio_request_enable = cygnus_gpio_request_enable,
	.gpio_disable_मुक्त = cygnus_gpio_disable_मुक्त,
पूर्ण;

अटल काष्ठा pinctrl_desc cygnus_pinctrl_desc = अणु
	.name = "cygnus-pinmux",
	.pctlops = &cygnus_pinctrl_ops,
	.pmxops = &cygnus_pinmux_ops,
पूर्ण;

अटल पूर्णांक cygnus_mux_log_init(काष्ठा cygnus_pinctrl *pinctrl)
अणु
	काष्ठा cygnus_mux_log *log;
	अचिन्हित पूर्णांक i, j;

	pinctrl->mux_log = devm_kसुस्मृति(pinctrl->dev, CYGNUS_NUM_IOMUX,
					माप(काष्ठा cygnus_mux_log),
					GFP_KERNEL);
	अगर (!pinctrl->mux_log)
		वापस -ENOMEM;

	क्रम (i = 0; i < CYGNUS_NUM_IOMUX_REGS; i++) अणु
		क्रम (j = 0; j < CYGNUS_NUM_MUX_PER_REG; j++) अणु
			log = &pinctrl->mux_log[i * CYGNUS_NUM_MUX_PER_REG
				+ j];
			log->mux.offset = i * 4;
			log->mux.shअगरt = j * 4;
			log->mux.alt = 0;
			log->is_configured = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_pinmux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cygnus_pinctrl *pinctrl;
	पूर्णांक i, ret;
	काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित num_pins = ARRAY_SIZE(cygnus_pins);

	pinctrl = devm_kzalloc(&pdev->dev, माप(*pinctrl), GFP_KERNEL);
	अगर (!pinctrl)
		वापस -ENOMEM;

	pinctrl->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, pinctrl);
	spin_lock_init(&pinctrl->lock);

	pinctrl->base0 = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pinctrl->base0)) अणु
		dev_err(&pdev->dev, "unable to map I/O space\n");
		वापस PTR_ERR(pinctrl->base0);
	पूर्ण

	pinctrl->base1 = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(pinctrl->base1)) अणु
		dev_err(&pdev->dev, "unable to map I/O space\n");
		वापस PTR_ERR(pinctrl->base1);
	पूर्ण

	ret = cygnus_mux_log_init(pinctrl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to initialize IOMUX log\n");
		वापस ret;
	पूर्ण

	pins = devm_kसुस्मृति(&pdev->dev, num_pins, माप(*pins), GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_pins; i++) अणु
		pins[i].number = cygnus_pins[i].pin;
		pins[i].name = cygnus_pins[i].name;
		pins[i].drv_data = &cygnus_pins[i].gpio_mux;
	पूर्ण

	pinctrl->groups = cygnus_pin_groups;
	pinctrl->num_groups = ARRAY_SIZE(cygnus_pin_groups);
	pinctrl->functions = cygnus_pin_functions;
	pinctrl->num_functions = ARRAY_SIZE(cygnus_pin_functions);
	cygnus_pinctrl_desc.pins = pins;
	cygnus_pinctrl_desc.npins = num_pins;

	pinctrl->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, &cygnus_pinctrl_desc,
			pinctrl);
	अगर (IS_ERR(pinctrl->pctl)) अणु
		dev_err(&pdev->dev, "unable to register Cygnus IOMUX pinctrl\n");
		वापस PTR_ERR(pinctrl->pctl);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cygnus_pinmux_of_match[] = अणु
	अणु .compatible = "brcm,cygnus-pinmux" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver cygnus_pinmux_driver = अणु
	.driver = अणु
		.name = "cygnus-pinmux",
		.of_match_table = cygnus_pinmux_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = cygnus_pinmux_probe,
पूर्ण;

अटल पूर्णांक __init cygnus_pinmux_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&cygnus_pinmux_driver);
पूर्ण
arch_initcall(cygnus_pinmux_init);
