<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_IPCOMP_H
#घोषणा _XT_IPCOMP_H

#समावेश <linux/types.h>

काष्ठा xt_ipcomp अणु
	__u32 spis[2];	/* Security Parameter Index */
	__u8 invflags;	/* Inverse flags */
	__u8 hdrres;	/* Test of the Reserved Filed */
पूर्ण;

/* Values क्रम "invflags" field in काष्ठा xt_ipcomp. */
#घोषणा XT_IPCOMP_INV_SPI	0x01	/* Invert the sense of spi. */
#घोषणा XT_IPCOMP_INV_MASK	0x01	/* All possible flags. */

#पूर्ण_अगर /*_XT_IPCOMP_H*/
