<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __DRV_TYPES_SDIO_H__
#घोषणा __DRV_TYPES_SDIO_H__

/*  SDIO Header Files */
	#समावेश <linux/mmc/sdio_func.h>
	#समावेश <linux/mmc/sdio_ids.h>

काष्ठा sdio_data अणु
	u8  func_number;

	u8  tx_block_mode;
	u8  rx_block_mode;
	u32 block_transfer_len;

	काष्ठा sdio_func	 *func;
	व्योम *sys_sdio_irq_thd;
पूर्ण;

#पूर्ण_अगर
