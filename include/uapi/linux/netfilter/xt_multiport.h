<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_MULTIPORT_H
#घोषणा _XT_MULTIPORT_H

#समावेश <linux/types.h>

क्रमागत xt_multiport_flags अणु
	XT_MULTIPORT_SOURCE,
	XT_MULTIPORT_DESTINATION,
	XT_MULTIPORT_EITHER
पूर्ण;

#घोषणा XT_MULTI_PORTS	15

/* Must fit inside जोड़ xt_matchinfo: 16 bytes */
काष्ठा xt_multiport अणु
	__u8 flags;				/* Type of comparison */
	__u8 count;				/* Number of ports */
	__u16 ports[XT_MULTI_PORTS];	/* Ports */
पूर्ण;

काष्ठा xt_multiport_v1 अणु
	__u8 flags;				/* Type of comparison */
	__u8 count;				/* Number of ports */
	__u16 ports[XT_MULTI_PORTS];	/* Ports */
	__u8 pflags[XT_MULTI_PORTS];	/* Port flags */
	__u8 invert;			/* Invert flag */
पूर्ण;

#पूर्ण_अगर /*_XT_MULTIPORT_H*/
