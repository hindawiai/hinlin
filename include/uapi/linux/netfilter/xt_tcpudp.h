<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_TCPUDP_H
#घोषणा _XT_TCPUDP_H

#समावेश <linux/types.h>

/* TCP matching stuff */
काष्ठा xt_tcp अणु
	__u16 spts[2];			/* Source port range. */
	__u16 dpts[2];			/* Destination port range. */
	__u8 option;			/* TCP Option अगरf non-zero*/
	__u8 flg_mask;			/* TCP flags mask byte */
	__u8 flg_cmp;			/* TCP flags compare byte */
	__u8 invflags;			/* Inverse flags */
पूर्ण;

/* Values क्रम "inv" field in काष्ठा ipt_tcp. */
#घोषणा XT_TCP_INV_SRCPT	0x01	/* Invert the sense of source ports. */
#घोषणा XT_TCP_INV_DSTPT	0x02	/* Invert the sense of dest ports. */
#घोषणा XT_TCP_INV_FLAGS	0x04	/* Invert the sense of TCP flags. */
#घोषणा XT_TCP_INV_OPTION	0x08	/* Invert the sense of option test. */
#घोषणा XT_TCP_INV_MASK		0x0F	/* All possible flags. */

/* UDP matching stuff */
काष्ठा xt_udp अणु
	__u16 spts[2];			/* Source port range. */
	__u16 dpts[2];			/* Destination port range. */
	__u8 invflags;			/* Inverse flags */
पूर्ण;

/* Values क्रम "invflags" field in काष्ठा ipt_udp. */
#घोषणा XT_UDP_INV_SRCPT	0x01	/* Invert the sense of source ports. */
#घोषणा XT_UDP_INV_DSTPT	0x02	/* Invert the sense of dest ports. */
#घोषणा XT_UDP_INV_MASK	0x03	/* All possible flags. */


#पूर्ण_अगर
