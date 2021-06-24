<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2015 Zhang, Keguang <keguang.zhang@gmail.com>
 *
 * Loongson 1 न_अंकD platक्रमm support.
 */

#अगर_अघोषित __ASM_MACH_LOONGSON32_न_अंकD_H
#घोषणा __ASM_MACH_LOONGSON32_न_अंकD_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/mtd/partitions.h>

काष्ठा plat_ls1x_nand अणु
	काष्ठा mtd_partition *parts;
	अचिन्हित पूर्णांक nr_parts;

	पूर्णांक hold_cycle;
	पूर्णांक रुको_cycle;
पूर्ण;

बाह्य काष्ठा plat_ls1x_nand ls1b_nand_pdata;

bool ls1x_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *param);

#पूर्ण_अगर /* __ASM_MACH_LOONGSON32_न_अंकD_H */
