<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _IP6T_RT_H
#घोषणा _IP6T_RT_H

#समावेश <linux/types.h>
#समावेश <linux/in6.h>

#घोषणा IP6T_RT_HOPS 16

काष्ठा ip6t_rt अणु
	__u32 rt_type;			/* Routing Type */
	__u32 segsleft[2];			/* Segments Left */
	__u32 hdrlen;			/* Header Length */
	__u8  flags;			/*  */
	__u8  invflags;			/* Inverse flags */
	काष्ठा in6_addr addrs[IP6T_RT_HOPS];	/* Hops */
	__u8 addrnr;			/* Nr of Addresses */
पूर्ण;

#घोषणा IP6T_RT_TYP 		0x01
#घोषणा IP6T_RT_SGS 		0x02
#घोषणा IP6T_RT_LEN 		0x04
#घोषणा IP6T_RT_RES 		0x08
#घोषणा IP6T_RT_FST_MASK	0x30
#घोषणा IP6T_RT_FST 		0x10
#घोषणा IP6T_RT_FST_NSTRICT	0x20

/* Values क्रम "invflags" field in काष्ठा ip6t_rt. */
#घोषणा IP6T_RT_INV_TYP		0x01	/* Invert the sense of type. */
#घोषणा IP6T_RT_INV_SGS		0x02	/* Invert the sense of Segments. */
#घोषणा IP6T_RT_INV_LEN		0x04	/* Invert the sense of length. */
#घोषणा IP6T_RT_INV_MASK	0x07	/* All possible flags. */

#पूर्ण_अगर /*_IP6T_RT_H*/
