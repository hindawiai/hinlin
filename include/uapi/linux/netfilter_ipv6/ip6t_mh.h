<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _IP6T_MH_H
#घोषणा _IP6T_MH_H

#समावेश <linux/types.h>

/* MH matching stuff */
काष्ठा ip6t_mh अणु
	__u8 types[2];	/* MH type range */
	__u8 invflags;	/* Inverse flags */
पूर्ण;

/* Values क्रम "invflags" field in काष्ठा ip6t_mh. */
#घोषणा IP6T_MH_INV_TYPE	0x01	/* Invert the sense of type. */
#घोषणा IP6T_MH_INV_MASK	0x01	/* All possible flags. */

#पूर्ण_अगर /*_IP6T_MH_H*/
