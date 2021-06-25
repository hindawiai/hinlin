<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित __NETCNT_COMMON_H
#घोषणा __NETCNT_COMMON_H

#समावेश <linux/types.h>

#घोषणा MAX_PERCPU_PACKETS 32

काष्ठा percpu_net_cnt अणु
	__u64 packets;
	__u64 bytes;

	__u64 prev_ts;

	__u64 prev_packets;
	__u64 prev_bytes;
पूर्ण;

काष्ठा net_cnt अणु
	__u64 packets;
	__u64 bytes;
पूर्ण;

#पूर्ण_अगर
