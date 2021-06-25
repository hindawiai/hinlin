<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2016 Facebook
 */
#अगर_अघोषित _TEST_IPTNL_COMMON_H
#घोषणा _TEST_IPTNL_COMMON_H

#समावेश <linux/types.h>

#घोषणा MAX_IPTNL_ENTRIES 256U

काष्ठा vip अणु
	जोड़ अणु
		__u32 v6[4];
		__u32 v4;
	पूर्ण daddr;
	__u16 dport;
	__u16 family;
	__u8 protocol;
पूर्ण;

काष्ठा iptnl_info अणु
	जोड़ अणु
		__u32 v6[4];
		__u32 v4;
	पूर्ण saddr;
	जोड़ अणु
		__u32 v6[4];
		__u32 v4;
	पूर्ण daddr;
	__u16 family;
	__u8 dmac[6];
पूर्ण;

#पूर्ण_अगर
