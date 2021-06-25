<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_TC_CSUM_H
#घोषणा __LINUX_TC_CSUM_H

#समावेश <linux/types.h>
#समावेश <linux/pkt_cls.h>

क्रमागत अणु
	TCA_CSUM_UNSPEC,
	TCA_CSUM_PARMS,
	TCA_CSUM_TM,
	TCA_CSUM_PAD,
	__TCA_CSUM_MAX
पूर्ण;
#घोषणा TCA_CSUM_MAX (__TCA_CSUM_MAX - 1)

क्रमागत अणु
	TCA_CSUM_UPDATE_FLAG_IPV4HDR = 1,
	TCA_CSUM_UPDATE_FLAG_ICMP    = 2,
	TCA_CSUM_UPDATE_FLAG_IGMP    = 4,
	TCA_CSUM_UPDATE_FLAG_TCP     = 8,
	TCA_CSUM_UPDATE_FLAG_UDP     = 16,
	TCA_CSUM_UPDATE_FLAG_UDPLITE = 32,
	TCA_CSUM_UPDATE_FLAG_SCTP    = 64,
पूर्ण;

काष्ठा tc_csum अणु
	tc_gen;

	__u32 update_flags;
पूर्ण;

#पूर्ण_अगर /* __LINUX_TC_CSUM_H */
