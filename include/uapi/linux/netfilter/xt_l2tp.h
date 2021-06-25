<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_NETFILTER_XT_L2TP_H
#घोषणा _LINUX_NETFILTER_XT_L2TP_H

#समावेश <linux/types.h>

क्रमागत xt_l2tp_type अणु
	XT_L2TP_TYPE_CONTROL,
	XT_L2TP_TYPE_DATA,
पूर्ण;

/* L2TP matching stuff */
काष्ठा xt_l2tp_info अणु
	__u32 tid;			/* tunnel id */
	__u32 sid;			/* session id */
	__u8 version;			/* L2TP protocol version */
	__u8 type;			/* L2TP packet type */
	__u8 flags;			/* which fields to match */
पूर्ण;

क्रमागत अणु
	XT_L2TP_TID	= (1 << 0),	/* match L2TP tunnel id */
	XT_L2TP_SID	= (1 << 1),	/* match L2TP session id */
	XT_L2TP_VERSION	= (1 << 2),	/* match L2TP protocol version */
	XT_L2TP_TYPE	= (1 << 3),	/* match L2TP packet type */
पूर्ण;

#पूर्ण_अगर /* _LINUX_NETFILTER_XT_L2TP_H */
