<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2009 Ian Molton <spyro@f2s.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/mfd/पंचांगपन.स>

#घोषणा CNF_CMD     0x04
#घोषणा CNF_CTL_BASE   0x10
#घोषणा CNF_INT_PIN  0x3d
#घोषणा CNF_STOP_CLK_CTL 0x40
#घोषणा CNF_GCLK_CTL 0x41
#घोषणा CNF_SD_CLK_MODE 0x42
#घोषणा CNF_PIN_STATUS 0x44
#घोषणा CNF_PWR_CTL_1 0x48
#घोषणा CNF_PWR_CTL_2 0x49
#घोषणा CNF_PWR_CTL_3 0x4a
#घोषणा CNF_CARD_DETECT_MODE 0x4c
#घोषणा CNF_SD_SLOT 0x50
#घोषणा CNF_EXT_GCLK_CTL_1 0xf0
#घोषणा CNF_EXT_GCLK_CTL_2 0xf1
#घोषणा CNF_EXT_GCLK_CTL_3 0xf9
#घोषणा CNF_SD_LED_EN_1 0xfa
#घोषणा CNF_SD_LED_EN_2 0xfe

#घोषणा   SDCREN 0x2   /* Enable access to MMC CTL regs. (flag in COMMAND_REG)*/

पूर्णांक पंचांगio_core_mmc_enable(व्योम __iomem *cnf, पूर्णांक shअगरt, अचिन्हित दीर्घ base)
अणु
	/* Enable the MMC/SD Control रेजिस्टरs */
	sd_config_ग_लिखो16(cnf, shअगरt, CNF_CMD, SDCREN);
	sd_config_ग_लिखो32(cnf, shअगरt, CNF_CTL_BASE, base & 0xfffe);

	/* Disable SD घातer during suspend */
	sd_config_ग_लिखो8(cnf, shअगरt, CNF_PWR_CTL_3, 0x01);

	/* The below is required but why? FIXME */
	sd_config_ग_लिखो8(cnf, shअगरt, CNF_STOP_CLK_CTL, 0x1f);

	/* Power करोwn SD bus */
	sd_config_ग_लिखो8(cnf, shअगरt, CNF_PWR_CTL_2, 0x00);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(पंचांगio_core_mmc_enable);

पूर्णांक पंचांगio_core_mmc_resume(व्योम __iomem *cnf, पूर्णांक shअगरt, अचिन्हित दीर्घ base)
अणु

	/* Enable the MMC/SD Control रेजिस्टरs */
	sd_config_ग_लिखो16(cnf, shअगरt, CNF_CMD, SDCREN);
	sd_config_ग_लिखो32(cnf, shअगरt, CNF_CTL_BASE, base & 0xfffe);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(पंचांगio_core_mmc_resume);

व्योम पंचांगio_core_mmc_pwr(व्योम __iomem *cnf, पूर्णांक shअगरt, पूर्णांक state)
अणु
	sd_config_ग_लिखो8(cnf, shअगरt, CNF_PWR_CTL_2, state ? 0x02 : 0x00);
पूर्ण
EXPORT_SYMBOL(पंचांगio_core_mmc_pwr);

व्योम पंचांगio_core_mmc_clk_भाग(व्योम __iomem *cnf, पूर्णांक shअगरt, पूर्णांक state)
अणु
	sd_config_ग_लिखो8(cnf, shअगरt, CNF_SD_CLK_MODE, state ? 1 : 0);
पूर्ण
EXPORT_SYMBOL(पंचांगio_core_mmc_clk_भाग);

