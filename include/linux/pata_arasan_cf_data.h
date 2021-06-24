<शैली गुरु>
/*
 * include/linux/pata_arasan_cf_data.h
 *
 * Arasan Compact Flash host controller platक्रमm data header file
 *
 * Copyright (C) 2011 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित _PATA_ARASAN_CF_DATA_H
#घोषणा _PATA_ARASAN_CF_DATA_H

#समावेश <linux/platक्रमm_device.h>

काष्ठा arasan_cf_pdata अणु
	u8 cf_अगर_clk;
	#घोषणा CF_IF_CLK_100M			(0x0)
	#घोषणा CF_IF_CLK_75M			(0x1)
	#घोषणा CF_IF_CLK_66M			(0x2)
	#घोषणा CF_IF_CLK_50M			(0x3)
	#घोषणा CF_IF_CLK_40M			(0x4)
	#घोषणा CF_IF_CLK_33M			(0x5)
	#घोषणा CF_IF_CLK_25M			(0x6)
	#घोषणा CF_IF_CLK_125M			(0x7)
	#घोषणा CF_IF_CLK_150M			(0x8)
	#घोषणा CF_IF_CLK_166M			(0x9)
	#घोषणा CF_IF_CLK_200M			(0xA)
	/*
	 * Platक्रमm specअगरic incapabilities of CF controller is handled via
	 * quirks
	 */
	u32 quirk;
	#घोषणा CF_BROKEN_PIO			(1)
	#घोषणा CF_BROKEN_MWDMA			(1 << 1)
	#घोषणा CF_BROKEN_UDMA			(1 << 2)
पूर्ण;

अटल अंतरभूत व्योम
set_arasan_cf_pdata(काष्ठा platक्रमm_device *pdev, काष्ठा arasan_cf_pdata *data)
अणु
	pdev->dev.platक्रमm_data = data;
पूर्ण
#पूर्ण_अगर /* _PATA_ARASAN_CF_DATA_H */
