<शैली गुरु>
/*
 * Copyright (C) 2016 Broadcom
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

#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/reboot.h>

#घोषणा RSTMGR_REG_WR_ACCESS_OFFSET	0
#घोषणा RSTMGR_REG_CHIP_SOFT_RST_OFFSET	4

#घोषणा RSTMGR_WR_PASSWORD		0xa5a5
#घोषणा RSTMGR_WR_PASSWORD_SHIFT	8
#घोषणा RSTMGR_WR_ACCESS_ENABLE		1

अटल व्योम __iomem *kona_reset_base;

अटल पूर्णांक kona_reset_handler(काष्ठा notअगरier_block *this,
				अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	/*
	 * A soft reset is triggered by writing a 0 to bit 0 of the soft reset
	 * रेजिस्टर. To ग_लिखो to that रेजिस्टर we must first ग_लिखो the password
	 * and the enable bit in the ग_लिखो access enable रेजिस्टर.
	 */
	ग_लिखोl((RSTMGR_WR_PASSWORD << RSTMGR_WR_PASSWORD_SHIFT) |
		RSTMGR_WR_ACCESS_ENABLE,
		kona_reset_base + RSTMGR_REG_WR_ACCESS_OFFSET);
	ग_लिखोl(0, kona_reset_base + RSTMGR_REG_CHIP_SOFT_RST_OFFSET);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block kona_reset_nb = अणु
	.notअगरier_call = kona_reset_handler,
	.priority = 128,
पूर्ण;

अटल पूर्णांक kona_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	kona_reset_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(kona_reset_base))
		वापस PTR_ERR(kona_reset_base);

	वापस रेजिस्टर_restart_handler(&kona_reset_nb);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match[] = अणु
	अणु .compatible = "brcm,bcm21664-resetmgr" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm_kona_reset_driver = अणु
	.probe = kona_reset_probe,
	.driver = अणु
		.name = "brcm-kona-reset",
		.of_match_table = of_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(bcm_kona_reset_driver);
