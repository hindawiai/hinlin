<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* iptables module क्रम using NFQUEUE mechanism
 *
 * (C) 2005 Harald Welte <laक्रमge@netfilter.org>
 *
 * This software is distributed under GNU GPL v2, 1991
 * 
*/
#अगर_अघोषित _XT_NFQ_TARGET_H
#घोषणा _XT_NFQ_TARGET_H

#समावेश <linux/types.h>

/* target info */
काष्ठा xt_NFQ_info अणु
	__u16 queuक्रमागत;
पूर्ण;

काष्ठा xt_NFQ_info_v1 अणु
	__u16 queuक्रमागत;
	__u16 queues_total;
पूर्ण;

काष्ठा xt_NFQ_info_v2 अणु
	__u16 queuक्रमागत;
	__u16 queues_total;
	__u16 bypass;
पूर्ण;

काष्ठा xt_NFQ_info_v3 अणु
	__u16 queuक्रमागत;
	__u16 queues_total;
	__u16 flags;
#घोषणा NFQ_FLAG_BYPASS		0x01 /* क्रम compatibility with v2 */
#घोषणा NFQ_FLAG_CPU_FANOUT	0x02 /* use current CPU (no hashing) */
#घोषणा NFQ_FLAG_MASK		0x03
पूर्ण;

#पूर्ण_अगर /* _XT_NFQ_TARGET_H */
