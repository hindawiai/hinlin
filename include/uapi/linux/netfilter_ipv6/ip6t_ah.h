<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _IP6T_AH_H
#घोषणा _IP6T_AH_H

#समावेश <linux/types.h>

काष्ठा ip6t_ah अणु
	__u32 spis[2];			/* Security Parameter Index */
	__u32 hdrlen;			/* Header Length */
	__u8  hdrres;			/* Test of the Reserved Filed */
	__u8  invflags;			/* Inverse flags */
पूर्ण;

#घोषणा IP6T_AH_SPI 0x01
#घोषणा IP6T_AH_LEN 0x02
#घोषणा IP6T_AH_RES 0x04

/* Values क्रम "invflags" field in काष्ठा ip6t_ah. */
#घोषणा IP6T_AH_INV_SPI		0x01	/* Invert the sense of spi. */
#घोषणा IP6T_AH_INV_LEN		0x02	/* Invert the sense of length. */
#घोषणा IP6T_AH_INV_MASK	0x03	/* All possible flags. */

#पूर्ण_अगर /*_IP6T_AH_H*/
