<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2004, Instant802 Networks, Inc.
 * Copyright 2005, Devicescape Software, Inc.
 */

#अगर_अघोषित _WME_H
#घोषणा _WME_H

#समावेश <linux/netdevice.h>
#समावेश "ieee80211_i.h"

u16 ieee80211_select_queue_80211(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sk_buff *skb,
				 काष्ठा ieee80211_hdr *hdr);
u16 __ieee80211_select_queue(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा sta_info *sta, काष्ठा sk_buff *skb);
u16 ieee80211_select_queue(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा sk_buff *skb);
व्योम ieee80211_set_qos_hdr(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा sk_buff *skb);

#पूर्ण_अगर /* _WME_H */
