<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/mmc/sdio_ops.c
 *
 *  Copyright 2006-2007 Pierre Ossman
 */

#अगर_अघोषित _MMC_SDIO_OPS_H
#घोषणा _MMC_SDIO_OPS_H

#समावेश <linux/types.h>
#समावेश <linux/mmc/sdपन.स>

काष्ठा mmc_host;
काष्ठा mmc_card;
काष्ठा work_काष्ठा;

पूर्णांक mmc_send_io_op_cond(काष्ठा mmc_host *host, u32 ocr, u32 *rocr);
पूर्णांक mmc_io_rw_direct(काष्ठा mmc_card *card, पूर्णांक ग_लिखो, अचिन्हित fn,
	अचिन्हित addr, u8 in, u8* out);
पूर्णांक mmc_io_rw_extended(काष्ठा mmc_card *card, पूर्णांक ग_लिखो, अचिन्हित fn,
	अचिन्हित addr, पूर्णांक incr_addr, u8 *buf, अचिन्हित blocks, अचिन्हित blksz);
पूर्णांक sdio_reset(काष्ठा mmc_host *host);
व्योम sdio_irq_work(काष्ठा work_काष्ठा *work);

अटल अंतरभूत bool sdio_is_io_busy(u32 opcode, u32 arg)
अणु
	u32 addr;

	addr = (arg >> 9) & 0x1FFFF;

	वापस (opcode == SD_IO_RW_EXTENDED ||
		(opcode == SD_IO_RW_सूचीECT &&
		!(addr == SDIO_CCCR_ABORT || addr == SDIO_CCCR_SUSPEND)));
पूर्ण

#पूर्ण_अगर

