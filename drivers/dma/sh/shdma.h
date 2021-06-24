<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Renesas SuperH DMA Engine support
 *
 * Copyright (C) 2009 Nobuhiro Iwamatsu <iwamatsu.nobuhiro@renesas.com>
 * Copyright (C) 2009 Renesas Solutions, Inc. All rights reserved.
 *
 */
#अगर_अघोषित __DMA_SHDMA_H
#घोषणा __DMA_SHDMA_H

#समावेश <linux/sh_dma.h>
#समावेश <linux/shdma-base.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>

#घोषणा SH_DMAE_MAX_CHANNELS 20
#घोषणा SH_DMAE_TCR_MAX 0x00FFFFFF	/* 16MB */

काष्ठा device;

काष्ठा sh_dmae_chan अणु
	काष्ठा shdma_chan shdma_chan;
	स्थिर काष्ठा sh_dmae_slave_config *config; /* Slave DMA configuration */
	पूर्णांक xmit_shअगरt;			/* log_2(bytes_per_xfer) */
	व्योम __iomem *base;
	अक्षर dev_id[16];		/* unique name per DMAC of channel */
	पूर्णांक pm_error;
	dma_addr_t slave_addr;
पूर्ण;

काष्ठा sh_dmae_device अणु
	काष्ठा shdma_dev shdma_dev;
	काष्ठा sh_dmae_chan *chan[SH_DMAE_MAX_CHANNELS];
	स्थिर काष्ठा sh_dmae_pdata *pdata;
	काष्ठा list_head node;
	व्योम __iomem *chan_reg;
	व्योम __iomem *dmars;
	अचिन्हित पूर्णांक chcr_offset;
	u32 chcr_ie_bit;
पूर्ण;

काष्ठा sh_dmae_regs अणु
	u32 sar; /* SAR / source address */
	u32 dar; /* DAR / destination address */
	u32 tcr; /* TCR / transfer count */
पूर्ण;

काष्ठा sh_dmae_desc अणु
	काष्ठा sh_dmae_regs hw;
	काष्ठा shdma_desc shdma_desc;
पूर्ण;

#घोषणा to_sh_chan(chan) container_of(chan, काष्ठा sh_dmae_chan, shdma_chan)
#घोषणा to_sh_desc(lh) container_of(lh, काष्ठा sh_desc, node)
#घोषणा tx_to_sh_desc(tx) container_of(tx, काष्ठा sh_desc, async_tx)
#घोषणा to_sh_dev(chan) container_of(chan->shdma_chan.dma_chan.device,\
				     काष्ठा sh_dmae_device, shdma_dev.dma_dev)

#पूर्ण_अगर	/* __DMA_SHDMA_H */
