<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश "dcss-dev.h"

#घोषणा DCSS_BLKCTL_RESET_CTRL		0x00
#घोषणा   B_CLK_RESETN			BIT(0)
#घोषणा   APB_CLK_RESETN		BIT(1)
#घोषणा   P_CLK_RESETN			BIT(2)
#घोषणा   RTR_CLK_RESETN		BIT(4)
#घोषणा DCSS_BLKCTL_CONTROL0		0x10
#घोषणा   HDMI_MIPI_CLK_SEL		BIT(0)
#घोषणा   DISPMIX_REFCLK_SEL_POS	4
#घोषणा   DISPMIX_REFCLK_SEL_MASK	GENMASK(5, 4)
#घोषणा   DISPMIX_PIXCLK_SEL		BIT(8)
#घोषणा   HDMI_SRC_SECURE_EN		BIT(16)

काष्ठा dcss_blkctl अणु
	काष्ठा dcss_dev *dcss;
	व्योम __iomem *base_reg;
पूर्ण;

व्योम dcss_blkctl_cfg(काष्ठा dcss_blkctl *blkctl)
अणु
	अगर (blkctl->dcss->hdmi_output)
		dcss_ग_लिखोl(0, blkctl->base_reg + DCSS_BLKCTL_CONTROL0);
	अन्यथा
		dcss_ग_लिखोl(DISPMIX_PIXCLK_SEL,
			    blkctl->base_reg + DCSS_BLKCTL_CONTROL0);

	dcss_set(B_CLK_RESETN | APB_CLK_RESETN | P_CLK_RESETN | RTR_CLK_RESETN,
		 blkctl->base_reg + DCSS_BLKCTL_RESET_CTRL);
पूर्ण

पूर्णांक dcss_blkctl_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ blkctl_base)
अणु
	काष्ठा dcss_blkctl *blkctl;

	blkctl = kzalloc(माप(*blkctl), GFP_KERNEL);
	अगर (!blkctl)
		वापस -ENOMEM;

	blkctl->base_reg = ioremap(blkctl_base, SZ_4K);
	अगर (!blkctl->base_reg) अणु
		dev_err(dcss->dev, "unable to remap BLK CTRL base\n");
		kमुक्त(blkctl);
		वापस -ENOMEM;
	पूर्ण

	dcss->blkctl = blkctl;
	blkctl->dcss = dcss;

	dcss_blkctl_cfg(blkctl);

	वापस 0;
पूर्ण

व्योम dcss_blkctl_निकास(काष्ठा dcss_blkctl *blkctl)
अणु
	अगर (blkctl->base_reg)
		iounmap(blkctl->base_reg);

	kमुक्त(blkctl);
पूर्ण
