<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_NFLOG_TARGET
#घोषणा _XT_NFLOG_TARGET

#समावेश <linux/types.h>

#घोषणा XT_NFLOG_DEFAULT_GROUP		0x1
#घोषणा XT_NFLOG_DEFAULT_THRESHOLD	0

#घोषणा XT_NFLOG_MASK			0x1

/* This flag indicates that 'len' field in xt_nflog_info is set*/
#घोषणा XT_NFLOG_F_COPY_LEN		0x1

काष्ठा xt_nflog_info अणु
	/* 'len' will be used अगरf you set XT_NFLOG_F_COPY_LEN in flags */
	__u32	len;
	__u16	group;
	__u16	threshold;
	__u16	flags;
	__u16	pad;
	अक्षर		prefix[64];
पूर्ण;

#पूर्ण_अगर /* _XT_NFLOG_TARGET */
