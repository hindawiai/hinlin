<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * aQuantia Corporation Network Driver
 * Copyright (C) 2014-2017 aQuantia Corporation. All rights reserved
 */

/* File aq_rss.h: Receive Side Scaling definitions. */

#अगर_अघोषित AQ_RSS_H
#घोषणा AQ_RSS_H

#समावेश "aq_common.h"
#समावेश "aq_cfg.h"

काष्ठा aq_rss_parameters अणु
	u16 base_cpu_number;
	u16 indirection_table_size;
	u16 hash_secret_key_size;
	u32 hash_secret_key[AQ_CFG_RSS_HASHKEY_SIZE / माप(u32)];
	u8 indirection_table[AQ_CFG_RSS_INसूचीECTION_TABLE_MAX];
पूर्ण;

#पूर्ण_अगर /* AQ_RSS_H */
