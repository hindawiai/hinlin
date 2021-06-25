<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2011 Texas Instruments. All rights reserved.
 */

#अगर_अघोषित __WL18XX_TX_H__
#घोषणा __WL18XX_TX_H__

#समावेश "../wlcore/wlcore.h"

#घोषणा WL18XX_TX_HW_BLOCK_SPARE        1
/* क्रम special हालs - namely, TKIP and GEM */
#घोषणा WL18XX_TX_HW_EXTRA_BLOCK_SPARE  2
#घोषणा WL18XX_TX_HW_BLOCK_SIZE         268

#घोषणा WL18XX_TX_STATUS_DESC_ID_MASK    0x7F
#घोषणा WL18XX_TX_STATUS_STAT_BIT_IDX    7

/* Indicates this TX HW frame is not padded to SDIO block size */
#घोषणा WL18XX_TX_CTRL_NOT_PADDED	BIT(7)

/*
 * The FW uses a special bit to indicate a wide channel should be used in
 * the rate policy.
 */
#घोषणा CONF_TX_RATE_USE_WIDE_CHAN BIT(31)

व्योम wl18xx_tx_immediate_complete(काष्ठा wl1271 *wl);

#पूर्ण_अगर /* __WL12XX_TX_H__ */
