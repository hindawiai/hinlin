<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0)
/*
 * oxnas SoC reset driver
 * based on:
 * Microsemi MIPS SoC reset driver
 * and ox820_निश्चित_प्रणाली_reset() written by Ma Hajun <mahaijuns@gmail.com>
 *
 * Copyright (c) 2013 Ma Hajun <mahaijuns@gmail.com>
 * Copyright (c) 2017 Microsemi Corporation
 * Copyright (c) 2020 Daniel Golle <daniel@makrotopia.org>
 */
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>

/* bit numbers of reset control रेजिस्टर */
#घोषणा OX820_SYS_CTRL_RST_SCU                0
#घोषणा OX820_SYS_CTRL_RST_COPRO              1
#घोषणा OX820_SYS_CTRL_RST_ARM0               2
#घोषणा OX820_SYS_CTRL_RST_ARM1               3
#घोषणा OX820_SYS_CTRL_RST_USBHS              4
#घोषणा OX820_SYS_CTRL_RST_USBHSPHYA          5
#घोषणा OX820_SYS_CTRL_RST_MACA               6
#घोषणा OX820_SYS_CTRL_RST_MAC                OX820_SYS_CTRL_RST_MACA
#घोषणा OX820_SYS_CTRL_RST_PCIEA              7
#घोषणा OX820_SYS_CTRL_RST_SGDMA              8
#घोषणा OX820_SYS_CTRL_RST_CIPHER             9
#घोषणा OX820_SYS_CTRL_RST_DDR                10
#घोषणा OX820_SYS_CTRL_RST_SATA               11
#घोषणा OX820_SYS_CTRL_RST_SATA_LINK          12
#घोषणा OX820_SYS_CTRL_RST_SATA_PHY           13
#घोषणा OX820_SYS_CTRL_RST_PCIEPHY            14
#घोषणा OX820_SYS_CTRL_RST_STATIC             15
#घोषणा OX820_SYS_CTRL_RST_GPIO               16
#घोषणा OX820_SYS_CTRL_RST_UART1              17
#घोषणा OX820_SYS_CTRL_RST_UART2              18
#घोषणा OX820_SYS_CTRL_RST_MISC               19
#घोषणा OX820_SYS_CTRL_RST_I2S                20
#घोषणा OX820_SYS_CTRL_RST_SD                 21
#घोषणा OX820_SYS_CTRL_RST_MACB               22
#घोषणा OX820_SYS_CTRL_RST_PCIEB              23
#घोषणा OX820_SYS_CTRL_RST_VIDEO              24
#घोषणा OX820_SYS_CTRL_RST_DDR_PHY            25
#घोषणा OX820_SYS_CTRL_RST_USBHSPHYB          26
#घोषणा OX820_SYS_CTRL_RST_USBDEV             27
#घोषणा OX820_SYS_CTRL_RST_ARMDBG             29
#घोषणा OX820_SYS_CTRL_RST_PLLA               30
#घोषणा OX820_SYS_CTRL_RST_PLLB               31

/* bit numbers of घड़ी control रेजिस्टर */
#घोषणा OX820_SYS_CTRL_CLK_COPRO              0
#घोषणा OX820_SYS_CTRL_CLK_DMA                1
#घोषणा OX820_SYS_CTRL_CLK_CIPHER             2
#घोषणा OX820_SYS_CTRL_CLK_SD                 3
#घोषणा OX820_SYS_CTRL_CLK_SATA               4
#घोषणा OX820_SYS_CTRL_CLK_I2S                5
#घोषणा OX820_SYS_CTRL_CLK_USBHS              6
#घोषणा OX820_SYS_CTRL_CLK_MACA               7
#घोषणा OX820_SYS_CTRL_CLK_MAC                OX820_SYS_CTRL_CLK_MACA
#घोषणा OX820_SYS_CTRL_CLK_PCIEA              8
#घोषणा OX820_SYS_CTRL_CLK_STATIC             9
#घोषणा OX820_SYS_CTRL_CLK_MACB               10
#घोषणा OX820_SYS_CTRL_CLK_PCIEB              11
#घोषणा OX820_SYS_CTRL_CLK_REF600             12
#घोषणा OX820_SYS_CTRL_CLK_USBDEV             13
#घोषणा OX820_SYS_CTRL_CLK_DDR                14
#घोषणा OX820_SYS_CTRL_CLK_DDRPHY             15
#घोषणा OX820_SYS_CTRL_CLK_DDRCK              16

/* Regmap offsets */
#घोषणा OX820_CLK_SET_REGOFFSET               0x2c
#घोषणा OX820_CLK_CLR_REGOFFSET               0x30
#घोषणा OX820_RST_SET_REGOFFSET               0x34
#घोषणा OX820_RST_CLR_REGOFFSET               0x38
#घोषणा OX820_SECONDARY_SEL_REGOFFSET         0x14
#घोषणा OX820_TERTIARY_SEL_REGOFFSET          0x8c
#घोषणा OX820_QUATERNARY_SEL_REGOFFSET        0x94
#घोषणा OX820_DEBUG_SEL_REGOFFSET             0x9c
#घोषणा OX820_ALTERNATIVE_SEL_REGOFFSET       0xa4
#घोषणा OX820_PULLUP_SEL_REGOFFSET            0xac
#घोषणा OX820_SEC_SECONDARY_SEL_REGOFFSET     0x100014
#घोषणा OX820_SEC_TERTIARY_SEL_REGOFFSET      0x10008c
#घोषणा OX820_SEC_QUATERNARY_SEL_REGOFFSET    0x100094
#घोषणा OX820_SEC_DEBUG_SEL_REGOFFSET         0x10009c
#घोषणा OX820_SEC_ALTERNATIVE_SEL_REGOFFSET   0x1000a4
#घोषणा OX820_SEC_PULLUP_SEL_REGOFFSET        0x1000ac

काष्ठा oxnas_restart_context अणु
	काष्ठा regmap *sys_ctrl;
	काष्ठा notअगरier_block restart_handler;
पूर्ण;

अटल पूर्णांक ox820_restart_handle(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	काष्ठा oxnas_restart_context *ctx = container_of(this, काष्ठा
							oxnas_restart_context,
							restart_handler);
	u32 value;

	/*
	 * Assert reset to cores as per घातer on शेषs
	 * Don't touch the DDR पूर्णांकerface as things will come to an impromptu
	 * stop NB Possibly should be निश्चितing reset क्रम PLLB, but there are
	 * timing concerns here according to the करोcs
	 */
	value = BIT(OX820_SYS_CTRL_RST_COPRO)		|
		BIT(OX820_SYS_CTRL_RST_USBHS)		|
		BIT(OX820_SYS_CTRL_RST_USBHSPHYA)	|
		BIT(OX820_SYS_CTRL_RST_MACA)		|
		BIT(OX820_SYS_CTRL_RST_PCIEA)		|
		BIT(OX820_SYS_CTRL_RST_SGDMA)		|
		BIT(OX820_SYS_CTRL_RST_CIPHER)		|
		BIT(OX820_SYS_CTRL_RST_SATA)		|
		BIT(OX820_SYS_CTRL_RST_SATA_LINK)	|
		BIT(OX820_SYS_CTRL_RST_SATA_PHY)	|
		BIT(OX820_SYS_CTRL_RST_PCIEPHY)		|
		BIT(OX820_SYS_CTRL_RST_STATIC)		|
		BIT(OX820_SYS_CTRL_RST_UART1)		|
		BIT(OX820_SYS_CTRL_RST_UART2)		|
		BIT(OX820_SYS_CTRL_RST_MISC)		|
		BIT(OX820_SYS_CTRL_RST_I2S)		|
		BIT(OX820_SYS_CTRL_RST_SD)		|
		BIT(OX820_SYS_CTRL_RST_MACB)		|
		BIT(OX820_SYS_CTRL_RST_PCIEB)		|
		BIT(OX820_SYS_CTRL_RST_VIDEO)		|
		BIT(OX820_SYS_CTRL_RST_USBHSPHYB)	|
		BIT(OX820_SYS_CTRL_RST_USBDEV);

	regmap_ग_लिखो(ctx->sys_ctrl, OX820_RST_SET_REGOFFSET, value);

	/* Release reset to cores as per घातer on शेषs */
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_RST_CLR_REGOFFSET,
			BIT(OX820_SYS_CTRL_RST_GPIO));

	/*
	 * Disable घड़ीs to cores as per घातer-on शेषs - must leave DDR
	 * related घड़ीs enabled otherwise we'll stop rather abruptly.
	 */
	value = BIT(OX820_SYS_CTRL_CLK_COPRO)		|
		BIT(OX820_SYS_CTRL_CLK_DMA)		|
		BIT(OX820_SYS_CTRL_CLK_CIPHER)		|
		BIT(OX820_SYS_CTRL_CLK_SD)		|
		BIT(OX820_SYS_CTRL_CLK_SATA)		|
		BIT(OX820_SYS_CTRL_CLK_I2S)		|
		BIT(OX820_SYS_CTRL_CLK_USBHS)		|
		BIT(OX820_SYS_CTRL_CLK_MAC)		|
		BIT(OX820_SYS_CTRL_CLK_PCIEA)		|
		BIT(OX820_SYS_CTRL_CLK_STATIC)		|
		BIT(OX820_SYS_CTRL_CLK_MACB)		|
		BIT(OX820_SYS_CTRL_CLK_PCIEB)		|
		BIT(OX820_SYS_CTRL_CLK_REF600)		|
		BIT(OX820_SYS_CTRL_CLK_USBDEV);

	regmap_ग_लिखो(ctx->sys_ctrl, OX820_CLK_CLR_REGOFFSET, value);

	/* Enable घड़ीs to cores as per घातer-on शेषs */

	/* Set sys-control pin mux'ing as per घातer-on शेषs */
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_SECONDARY_SEL_REGOFFSET, 0);
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_TERTIARY_SEL_REGOFFSET, 0);
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_QUATERNARY_SEL_REGOFFSET, 0);
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_DEBUG_SEL_REGOFFSET, 0);
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_ALTERNATIVE_SEL_REGOFFSET, 0);
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_PULLUP_SEL_REGOFFSET, 0);

	regmap_ग_लिखो(ctx->sys_ctrl, OX820_SEC_SECONDARY_SEL_REGOFFSET, 0);
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_SEC_TERTIARY_SEL_REGOFFSET, 0);
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_SEC_QUATERNARY_SEL_REGOFFSET, 0);
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_SEC_DEBUG_SEL_REGOFFSET, 0);
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_SEC_ALTERNATIVE_SEL_REGOFFSET, 0);
	regmap_ग_लिखो(ctx->sys_ctrl, OX820_SEC_PULLUP_SEL_REGOFFSET, 0);

	/*
	 * No need to save any state, as the ROM loader can determine whether
	 * reset is due to घातer cycling or programatic action, just hit the
	 * (self-clearing) CPU reset bit of the block reset रेजिस्टर
	 */
	value =
		BIT(OX820_SYS_CTRL_RST_SCU) |
		BIT(OX820_SYS_CTRL_RST_ARM0) |
		BIT(OX820_SYS_CTRL_RST_ARM1);

	regmap_ग_लिखो(ctx->sys_ctrl, OX820_RST_SET_REGOFFSET, value);

	pr_emerg("Unable to restart system\n");
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक ox820_restart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा oxnas_restart_context *ctx;
	काष्ठा regmap *sys_ctrl;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err = 0;

	sys_ctrl = syscon_node_to_regmap(pdev->dev.of_node);
	अगर (IS_ERR(sys_ctrl))
		वापस PTR_ERR(sys_ctrl);

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->sys_ctrl = sys_ctrl;
	ctx->restart_handler.notअगरier_call = ox820_restart_handle;
	ctx->restart_handler.priority = 192;
	err = रेजिस्टर_restart_handler(&ctx->restart_handler);
	अगर (err)
		dev_err(dev, "can't register restart notifier (err=%d)\n", err);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id ox820_restart_of_match[] = अणु
	अणु .compatible = "oxsemi,ox820-sys-ctrl" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ox820_restart_driver = अणु
	.probe = ox820_restart_probe,
	.driver = अणु
		.name = "ox820-chip-reset",
		.of_match_table = ox820_restart_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(ox820_restart_driver);
