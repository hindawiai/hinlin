<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _IP6T_OPTS_H
#घोषणा _IP6T_OPTS_H

#समावेश <linux/types.h>

#घोषणा IP6T_OPTS_OPTSNR 16

काष्ठा ip6t_opts अणु
	__u32 hdrlen;			/* Header Length */
	__u8 flags;				/*  */
	__u8 invflags;			/* Inverse flags */
	__u16 opts[IP6T_OPTS_OPTSNR];	/* opts */
	__u8 optsnr;			/* Nr of OPts */
पूर्ण;

#घोषणा IP6T_OPTS_LEN 		0x01
#घोषणा IP6T_OPTS_OPTS 		0x02
#घोषणा IP6T_OPTS_NSTRICT	0x04

/* Values क्रम "invflags" field in काष्ठा ip6t_rt. */
#घोषणा IP6T_OPTS_INV_LEN	0x01	/* Invert the sense of length. */
#घोषणा IP6T_OPTS_INV_MASK	0x01	/* All possible flags. */

#पूर्ण_अगर /*_IP6T_OPTS_H*/
