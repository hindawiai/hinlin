<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_NFNL_ACCT_H_
#घोषणा _UAPI_NFNL_ACCT_H_

#अगर_अघोषित NFACCT_NAME_MAX
#घोषणा NFACCT_NAME_MAX		32
#पूर्ण_अगर

क्रमागत nfnl_acct_msg_types अणु
	NFNL_MSG_ACCT_NEW,
	NFNL_MSG_ACCT_GET,
	NFNL_MSG_ACCT_GET_CTRZERO,
	NFNL_MSG_ACCT_DEL,
	NFNL_MSG_ACCT_OVERQUOTA,
	NFNL_MSG_ACCT_MAX
पूर्ण;

क्रमागत nfnl_acct_flags अणु
	NFACCT_F_QUOTA_PKTS	= (1 << 0),
	NFACCT_F_QUOTA_BYTES	= (1 << 1),
	NFACCT_F_OVERQUOTA	= (1 << 2), /* can't be set from userspace */
पूर्ण;

क्रमागत nfnl_acct_type अणु
	NFACCT_UNSPEC,
	NFACCT_NAME,
	NFACCT_PKTS,
	NFACCT_BYTES,
	NFACCT_USE,
	NFACCT_FLAGS,
	NFACCT_QUOTA,
	NFACCT_FILTER,
	NFACCT_PAD,
	__NFACCT_MAX
पूर्ण;
#घोषणा NFACCT_MAX (__NFACCT_MAX - 1)

क्रमागत nfnl_attr_filter_type अणु
	NFACCT_FILTER_UNSPEC,
	NFACCT_FILTER_MASK,
	NFACCT_FILTER_VALUE,
	__NFACCT_FILTER_MAX
पूर्ण;
#घोषणा NFACCT_FILTER_MAX (__NFACCT_FILTER_MAX - 1)

#पूर्ण_अगर /* _UAPI_NFNL_ACCT_H_ */
