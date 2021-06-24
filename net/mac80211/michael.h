<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Michael MIC implementation - optimized क्रम TKIP MIC operations
 * Copyright 2002-2003, Instant802 Networks, Inc.
 */

#अगर_अघोषित MICHAEL_H
#घोषणा MICHAEL_H

#समावेश <linux/types.h>
#समावेश <linux/ieee80211.h>

#घोषणा MICHAEL_MIC_LEN 8

काष्ठा michael_mic_ctx अणु
	u32 l, r;
पूर्ण;

व्योम michael_mic(स्थिर u8 *key, काष्ठा ieee80211_hdr *hdr,
		 स्थिर u8 *data, माप_प्रकार data_len, u8 *mic);

#पूर्ण_अगर /* MICHAEL_H */
