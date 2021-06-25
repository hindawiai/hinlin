<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2017 Nicira, Inc.
 */

#अगर_अघोषित METER_H
#घोषणा METER_H 1

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netlink.h>
#समावेश <linux/खोलोvचयन.h>
#समावेश <linux/genetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/bits.h>

#समावेश "flow.h"
काष्ठा datapath;

#घोषणा DP_MAX_BANDS		1
#घोषणा DP_METER_ARRAY_SIZE_MIN	BIT_ULL(10)
#घोषणा DP_METER_NUM_MAX	(200000UL)

काष्ठा dp_meter_band अणु
	u32 type;
	u32 rate;
	u32 burst_size;
	u64 bucket; /* 1/1000 packets, or in bits */
	काष्ठा ovs_flow_stats stats;
पूर्ण;

काष्ठा dp_meter अणु
	spinlock_t lock;    /* Per meter lock */
	काष्ठा rcu_head rcu;
	u32 id;
	u16 kbps:1, keep_stats:1;
	u16 n_bands;
	u32 max_delta_t;
	u64 used;
	काष्ठा ovs_flow_stats stats;
	काष्ठा dp_meter_band bands[];
पूर्ण;

काष्ठा dp_meter_instance अणु
	काष्ठा rcu_head rcu;
	u32 n_meters;
	काष्ठा dp_meter __rcu *dp_meters[];
पूर्ण;

काष्ठा dp_meter_table अणु
	काष्ठा dp_meter_instance __rcu *ti;
	u32 count;
	u32 max_meters_allowed;
पूर्ण;

बाह्य काष्ठा genl_family dp_meter_genl_family;
पूर्णांक ovs_meters_init(काष्ठा datapath *dp);
व्योम ovs_meters_निकास(काष्ठा datapath *dp);
bool ovs_meter_execute(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
		       काष्ठा sw_flow_key *key, u32 meter_id);

#पूर्ण_अगर /* meter.h */
