<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/mmc/s3cmci.h - Samsung S3C MCI driver
 *
 *  Copyright (C) 2004-2006 Thomas Kleffel, All Rights Reserved.
 */

क्रमागत s3cmci_रुकोक्रम अणु
	COMPLETION_NONE,
	COMPLETION_FINALIZE,
	COMPLETION_CMDSENT,
	COMPLETION_RSPFIN,
	COMPLETION_XFERFINISH,
	COMPLETION_XFERFINISH_RSPFIN,
पूर्ण;

काष्ठा s3cmci_host अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा s3c24xx_mci_pdata *pdata;
	काष्ठा mmc_host		*mmc;
	काष्ठा resource		*mem;
	काष्ठा clk		*clk;
	व्योम __iomem		*base;
	पूर्णांक			irq;
	पूर्णांक			irq_cd;
	काष्ठा dma_chan		*dma;

	अचिन्हित दीर्घ		clk_rate;
	अचिन्हित दीर्घ		clk_भाग;
	अचिन्हित दीर्घ		real_rate;
	u8			prescaler;

	पूर्णांक			is2440;
	अचिन्हित		sdiimsk;
	अचिन्हित		sdidata;

	bool			irq_disabled;
	bool			irq_enabled;
	bool			irq_state;
	पूर्णांक			sdio_irqen;

	काष्ठा mmc_request	*mrq;
	पूर्णांक			cmd_is_stop;

	spinlock_t		complete_lock;
	क्रमागत s3cmci_रुकोक्रम	complete_what;

	पूर्णांक			dma_complete;

	u32			pio_sgptr;
	u32			pio_bytes;
	u32			pio_count;
	u32			*pio_ptr;
#घोषणा XFER_NONE 0
#घोषणा XFER_READ 1
#घोषणा XFER_WRITE 2
	u32			pio_active;

	पूर्णांक			bus_width;

	अक्षर 			dbgmsg_cmd[301];
	अक्षर 			dbgmsg_dat[301];
	अक्षर			*status;

	अचिन्हित पूर्णांक		ccnt, dcnt;
	काष्ठा tasklet_काष्ठा	pio_tasklet;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry		*debug_root;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ
	काष्ठा notअगरier_block	freq_transition;
#पूर्ण_अगर
पूर्ण;
