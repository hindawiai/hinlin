<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _IP6T_FRAG_H
#घोषणा _IP6T_FRAG_H

#समावेश <linux/types.h>

काष्ठा ip6t_frag अणु
	__u32 ids[2];			/* Identअगरication range */
	__u32 hdrlen;			/* Header Length */
	__u8  flags;			/* Flags */
	__u8  invflags;			/* Inverse flags */
पूर्ण;

#घोषणा IP6T_FRAG_IDS 		0x01
#घोषणा IP6T_FRAG_LEN 		0x02
#घोषणा IP6T_FRAG_RES 		0x04
#घोषणा IP6T_FRAG_FST 		0x08
#घोषणा IP6T_FRAG_MF  		0x10
#घोषणा IP6T_FRAG_NMF  		0x20

/* Values क्रम "invflags" field in काष्ठा ip6t_frag. */
#घोषणा IP6T_FRAG_INV_IDS	0x01	/* Invert the sense of ids. */
#घोषणा IP6T_FRAG_INV_LEN	0x02	/* Invert the sense of length. */
#घोषणा IP6T_FRAG_INV_MASK	0x03	/* All possible flags. */

#पूर्ण_अगर /*_IP6T_FRAG_H*/
