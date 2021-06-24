<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * bdc_dbg.c - BRCM BDC USB3.0 device controller debug functions
 *
 * Copyright (C) 2014 Broadcom Corporation
 *
 * Author: Ashwini Pahuja
 */

#समावेश "bdc.h"
#समावेश "bdc_dbg.h"

व्योम bdc_dbg_regs(काष्ठा bdc *bdc)
अणु
	u32 temp;

	dev_vdbg(bdc->dev, "bdc->regs:%p\n", bdc->regs);
	temp = bdc_पढ़ोl(bdc->regs, BDC_BDCCFG0);
	dev_vdbg(bdc->dev, "bdccfg0:0x%08x\n", temp);
	temp = bdc_पढ़ोl(bdc->regs, BDC_BDCCFG1);
	dev_vdbg(bdc->dev, "bdccfg1:0x%08x\n", temp);
	temp = bdc_पढ़ोl(bdc->regs, BDC_BDCCAP0);
	dev_vdbg(bdc->dev, "bdccap0:0x%08x\n", temp);
	temp = bdc_पढ़ोl(bdc->regs, BDC_BDCCAP1);
	dev_vdbg(bdc->dev, "bdccap1:0x%08x\n", temp);
	temp = bdc_पढ़ोl(bdc->regs, BDC_USPC);
	dev_vdbg(bdc->dev, "uspc:0x%08x\n", temp);
	temp = bdc_पढ़ोl(bdc->regs, BDC_DVCSA);
	dev_vdbg(bdc->dev, "dvcsa:0x%08x\n", temp);
	temp = bdc_पढ़ोl(bdc->regs, BDC_DVCSB);
	dev_vdbg(bdc->dev, "dvcsb:0x%x08\n", temp);
पूर्ण

व्योम bdc_dump_epsts(काष्ठा bdc *bdc)
अणु
	u32 temp;

	temp = bdc_पढ़ोl(bdc->regs, BDC_EPSTS0);
	dev_vdbg(bdc->dev, "BDC_EPSTS0:0x%08x\n", temp);

	temp = bdc_पढ़ोl(bdc->regs, BDC_EPSTS1);
	dev_vdbg(bdc->dev, "BDC_EPSTS1:0x%x\n", temp);

	temp = bdc_पढ़ोl(bdc->regs, BDC_EPSTS2);
	dev_vdbg(bdc->dev, "BDC_EPSTS2:0x%08x\n", temp);

	temp = bdc_पढ़ोl(bdc->regs, BDC_EPSTS3);
	dev_vdbg(bdc->dev, "BDC_EPSTS3:0x%08x\n", temp);

	temp = bdc_पढ़ोl(bdc->regs, BDC_EPSTS4);
	dev_vdbg(bdc->dev, "BDC_EPSTS4:0x%08x\n", temp);

	temp = bdc_पढ़ोl(bdc->regs, BDC_EPSTS5);
	dev_vdbg(bdc->dev, "BDC_EPSTS5:0x%08x\n", temp);

	temp = bdc_पढ़ोl(bdc->regs, BDC_EPSTS6);
	dev_vdbg(bdc->dev, "BDC_EPSTS6:0x%08x\n", temp);

	temp = bdc_पढ़ोl(bdc->regs, BDC_EPSTS7);
	dev_vdbg(bdc->dev, "BDC_EPSTS7:0x%08x\n", temp);
पूर्ण

व्योम bdc_dbg_srr(काष्ठा bdc *bdc, u32 srr_num)
अणु
	काष्ठा bdc_sr *sr;
	dma_addr_t addr;
	पूर्णांक i;

	sr = bdc->srr.sr_bds;
	addr = bdc->srr.dma_addr;
	dev_vdbg(bdc->dev, "%s sr:%p dqp_index:%d\n", __func__,
						sr, bdc->srr.dqp_index);
	क्रम (i = 0; i < NUM_SR_ENTRIES; i++) अणु
		sr = &bdc->srr.sr_bds[i];
		dev_vdbg(bdc->dev, "%llx %08x %08x %08x %08x\n",
					(अचिन्हित दीर्घ दीर्घ)addr,
					le32_to_cpu(sr->offset[0]),
					le32_to_cpu(sr->offset[1]),
					le32_to_cpu(sr->offset[2]),
					le32_to_cpu(sr->offset[3]));
		addr += माप(*sr);
	पूर्ण
पूर्ण

व्योम bdc_dbg_bd_list(काष्ठा bdc *bdc, काष्ठा bdc_ep *ep)
अणु
	काष्ठा bd_list *bd_list = &ep->bd_list;
	काष्ठा bd_table *bd_table;
	काष्ठा bdc_bd *bd;
	पूर्णांक tbi, bdi, gbdi;
	dma_addr_t dma;

	gbdi = 0;
	dev_vdbg(bdc->dev,
		"Dump bd list for %s epnum:%d\n",
		ep->name, ep->ep_num);

	dev_vdbg(bdc->dev,
		"tabs:%d max_bdi:%d eqp_bdi:%d hwd_bdi:%d num_bds_table:%d\n",
		bd_list->num_tअसल, bd_list->max_bdi, bd_list->eqp_bdi,
		bd_list->hwd_bdi, bd_list->num_bds_table);

	क्रम (tbi = 0; tbi < bd_list->num_tअसल; tbi++) अणु
		bd_table = bd_list->bd_table_array[tbi];
		क्रम (bdi = 0; bdi < bd_list->num_bds_table; bdi++) अणु
			bd =  bd_table->start_bd + bdi;
			dma = bd_table->dma + (माप(काष्ठा bdc_bd) * bdi);
			dev_vdbg(bdc->dev,
				"tbi:%2d bdi:%2d gbdi:%2d virt:%p phys:%llx %08x %08x %08x %08x\n",
				tbi, bdi, gbdi++, bd, (अचिन्हित दीर्घ दीर्घ)dma,
				le32_to_cpu(bd->offset[0]),
				le32_to_cpu(bd->offset[1]),
				le32_to_cpu(bd->offset[2]),
				le32_to_cpu(bd->offset[3]));
		पूर्ण
		dev_vdbg(bdc->dev, "\n\n");
	पूर्ण
पूर्ण
