<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */

#अगर_अघोषित _UAPI_XT_CONNLABEL_H
#घोषणा _UAPI_XT_CONNLABEL_H

#समावेश <linux/types.h>

#घोषणा XT_CONNLABEL_MAXBIT 127
क्रमागत xt_connlabel_mtopts अणु
	XT_CONNLABEL_OP_INVERT = 1 << 0,
	XT_CONNLABEL_OP_SET    = 1 << 1,
पूर्ण;

काष्ठा xt_connlabel_mtinfo अणु
	__u16 bit;
	__u16 options;
पूर्ण;

#पूर्ण_अगर /* _UAPI_XT_CONNLABEL_H */
