<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Free Electrons
 * Copyright (C) 2014 Aपंचांगel
 *
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 */

#अगर_अघोषित __LINUX_MFD_HLCDC_H
#घोषणा __LINUX_MFD_HLCDC_H

#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>

#घोषणा ATMEL_HLCDC_CFG(i)		((i) * 0x4)
#घोषणा ATMEL_HLCDC_SIG_CFG		LCDCFG(5)
#घोषणा ATMEL_HLCDC_HSPOL		BIT(0)
#घोषणा ATMEL_HLCDC_VSPOL		BIT(1)
#घोषणा ATMEL_HLCDC_VSPDLYS		BIT(2)
#घोषणा ATMEL_HLCDC_VSPDLYE		BIT(3)
#घोषणा ATMEL_HLCDC_DISPPOL		BIT(4)
#घोषणा ATMEL_HLCDC_DITHER		BIT(6)
#घोषणा ATMEL_HLCDC_DISPDLY		BIT(7)
#घोषणा ATMEL_HLCDC_MODE_MASK		GENMASK(9, 8)
#घोषणा ATMEL_HLCDC_PP			BIT(10)
#घोषणा ATMEL_HLCDC_VSPSU		BIT(12)
#घोषणा ATMEL_HLCDC_VSPHO		BIT(13)
#घोषणा ATMEL_HLCDC_GUARDTIME_MASK	GENMASK(20, 16)

#घोषणा ATMEL_HLCDC_EN			0x20
#घोषणा ATMEL_HLCDC_DIS			0x24
#घोषणा ATMEL_HLCDC_SR			0x28
#घोषणा ATMEL_HLCDC_IER			0x2c
#घोषणा ATMEL_HLCDC_IDR			0x30
#घोषणा ATMEL_HLCDC_IMR			0x34
#घोषणा ATMEL_HLCDC_ISR			0x38

#घोषणा ATMEL_HLCDC_CLKPOL		BIT(0)
#घोषणा ATMEL_HLCDC_CLKSEL		BIT(2)
#घोषणा ATMEL_HLCDC_CLKPWMSEL		BIT(3)
#घोषणा ATMEL_HLCDC_CGDIS(i)		BIT(8 + (i))
#घोषणा ATMEL_HLCDC_CLKDIV_SHFT		16
#घोषणा ATMEL_HLCDC_CLKDIV_MASK		GENMASK(23, 16)
#घोषणा ATMEL_HLCDC_CLKDIV(भाग)		((भाग - 2) << ATMEL_HLCDC_CLKDIV_SHFT)

#घोषणा ATMEL_HLCDC_PIXEL_CLK		BIT(0)
#घोषणा ATMEL_HLCDC_SYNC		BIT(1)
#घोषणा ATMEL_HLCDC_DISP		BIT(2)
#घोषणा ATMEL_HLCDC_PWM			BIT(3)
#घोषणा ATMEL_HLCDC_SIP			BIT(4)

#घोषणा ATMEL_HLCDC_SOF			BIT(0)
#घोषणा ATMEL_HLCDC_SYNCDIS		BIT(1)
#घोषणा ATMEL_HLCDC_FIFOERR		BIT(4)
#घोषणा ATMEL_HLCDC_LAYER_STATUS(x)	BIT((x) + 8)

/**
 * Structure shared by the MFD device and its subdevices.
 *
 * @regmap: रेजिस्टर map used to access HLCDC IP रेजिस्टरs
 * @periph_clk: the hlcdc peripheral घड़ी
 * @sys_clk: the hlcdc प्रणाली घड़ी
 * @slow_clk: the प्रणाली slow clk
 * @irq: the hlcdc irq
 */
काष्ठा aपंचांगel_hlcdc अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *periph_clk;
	काष्ठा clk *sys_clk;
	काष्ठा clk *slow_clk;
	पूर्णांक irq;
पूर्ण;

#पूर्ण_अगर /* __LINUX_MFD_HLCDC_H */
