<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_TCPOPTSTRIP_H
#घोषणा _XT_TCPOPTSTRIP_H

#समावेश <linux/types.h>

#घोषणा tcpoptstrip_set_bit(bmap, idx) \
	(bmap[(idx) >> 5] |= 1U << (idx & 31))
#घोषणा tcpoptstrip_test_bit(bmap, idx) \
	(((1U << (idx & 31)) & bmap[(idx) >> 5]) != 0)

काष्ठा xt_tcpoptstrip_target_info अणु
	__u32 strip_bmap[8];
पूर्ण;

#पूर्ण_अगर /* _XT_TCPOPTSTRIP_H */
