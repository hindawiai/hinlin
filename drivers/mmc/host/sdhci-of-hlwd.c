<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/mmc/host/sdhci-of-hlwd.c
 *
 * Nपूर्णांकenकरो Wii Secure Digital Host Controller Interface.
 * Copyright (C) 2009 The GameCube Linux Team
 * Copyright (C) 2009 Albert Herranz
 *
 * Based on sdhci-of-esdhc.c
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 * Copyright (c) 2009 MontaVista Software, Inc.
 *
 * Authors: Xiaobo Xie <X.Xie@मुक्तscale.com>
 *	    Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mmc/host.h>
#समावेश "sdhci-pltfm.h"

/*
 * Ops and quirks क्रम the Nपूर्णांकenकरो Wii SDHCI controllers.
 */

/*
 * We need a small delay after each ग_लिखो, or things go horribly wrong.
 */
#घोषणा SDHCI_HLWD_WRITE_DELAY	5 /* usecs */

अटल व्योम sdhci_hlwd_ग_लिखोl(काष्ठा sdhci_host *host, u32 val, पूर्णांक reg)
अणु
	sdhci_be32bs_ग_लिखोl(host, val, reg);
	udelay(SDHCI_HLWD_WRITE_DELAY);
पूर्ण

अटल व्योम sdhci_hlwd_ग_लिखोw(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	sdhci_be32bs_ग_लिखोw(host, val, reg);
	udelay(SDHCI_HLWD_WRITE_DELAY);
पूर्ण

अटल व्योम sdhci_hlwd_ग_लिखोb(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	sdhci_be32bs_ग_लिखोb(host, val, reg);
	udelay(SDHCI_HLWD_WRITE_DELAY);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_hlwd_ops = अणु
	.पढ़ो_l = sdhci_be32bs_पढ़ोl,
	.पढ़ो_w = sdhci_be32bs_पढ़ोw,
	.पढ़ो_b = sdhci_be32bs_पढ़ोb,
	.ग_लिखो_l = sdhci_hlwd_ग_लिखोl,
	.ग_लिखो_w = sdhci_hlwd_ग_लिखोw,
	.ग_लिखो_b = sdhci_hlwd_ग_लिखोb,
	.set_घड़ी = sdhci_set_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_hlwd_pdata = अणु
	.quirks = SDHCI_QUIRK_32BIT_DMA_ADDR |
		  SDHCI_QUIRK_32BIT_DMA_SIZE,
	.ops = &sdhci_hlwd_ops,
पूर्ण;

अटल पूर्णांक sdhci_hlwd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस sdhci_pltfm_रेजिस्टर(pdev, &sdhci_hlwd_pdata, 0);
पूर्ण

अटल स्थिर काष्ठा of_device_id sdhci_hlwd_of_match[] = अणु
	अणु .compatible = "nintendo,hollywood-sdhci" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_hlwd_of_match);

अटल काष्ठा platक्रमm_driver sdhci_hlwd_driver = अणु
	.driver = अणु
		.name = "sdhci-hlwd",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sdhci_hlwd_of_match,
		.pm = &sdhci_pltfm_pmops,
	पूर्ण,
	.probe = sdhci_hlwd_probe,
	.हटाओ = sdhci_pltfm_unरेजिस्टर,
पूर्ण;

module_platक्रमm_driver(sdhci_hlwd_driver);

MODULE_DESCRIPTION("Nintendo Wii SDHCI OF driver");
MODULE_AUTHOR("The GameCube Linux Team, Albert Herranz");
MODULE_LICENSE("GPL v2");
