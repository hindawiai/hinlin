<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ppp-comp.h - Definitions क्रम करोing PPP packet compression.
 *
 * Copyright 1994-1998 Paul Mackerras.
 *
 *  This program is मुक्त software; you can redistribute it and/or
 *  modअगरy it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.
 */
#अगर_अघोषित _UAPI_NET_PPP_COMP_H
#घोषणा _UAPI_NET_PPP_COMP_H


/*
 * CCP codes.
 */

#घोषणा CCP_CONFREQ	1
#घोषणा CCP_CONFACK	2
#घोषणा CCP_TERMREQ	5
#घोषणा CCP_TERMACK	6
#घोषणा CCP_RESETREQ	14
#घोषणा CCP_RESETACK	15

/*
 * Max # bytes क्रम a CCP option
 */

#घोषणा CCP_MAX_OPTION_LENGTH	32

/*
 * Parts of a CCP packet.
 */

#घोषणा CCP_CODE(dp)		((dp)[0])
#घोषणा CCP_ID(dp)		((dp)[1])
#घोषणा CCP_LENGTH(dp)		(((dp)[2] << 8) + (dp)[3])
#घोषणा CCP_HDRLEN		4

#घोषणा CCP_OPT_CODE(dp)	((dp)[0])
#घोषणा CCP_OPT_LENGTH(dp)	((dp)[1])
#घोषणा CCP_OPT_MINLEN		2

/*
 * Definitions क्रम BSD-Compress.
 */

#घोषणा CI_BSD_COMPRESS		21	/* config. option क्रम BSD-Compress */
#घोषणा CILEN_BSD_COMPRESS	3	/* length of config. option */

/* Macros क्रम handling the 3rd byte of the BSD-Compress config option. */
#घोषणा BSD_NBITS(x)		((x) & 0x1F)	/* number of bits requested */
#घोषणा BSD_VERSION(x)		((x) >> 5)	/* version of option क्रमmat */
#घोषणा BSD_CURRENT_VERSION	1		/* current version number */
#घोषणा BSD_MAKE_OPT(v, n)	(((v) << 5) | (n))

#घोषणा BSD_MIN_BITS		9	/* smallest code size supported */
#घोषणा BSD_MAX_BITS		15	/* largest code size supported */

/*
 * Definitions क्रम Deflate.
 */

#घोषणा CI_DEFLATE		26	/* config option क्रम Deflate */
#घोषणा CI_DEFLATE_DRAFT	24	/* value used in original draft RFC */
#घोषणा CILEN_DEFLATE		4	/* length of its config option */

#घोषणा DEFLATE_MIN_SIZE	9
#घोषणा DEFLATE_MAX_SIZE	15
#घोषणा DEFLATE_METHOD_VAL	8
#घोषणा DEFLATE_SIZE(x)		(((x) >> 4) + 8)
#घोषणा DEFLATE_METHOD(x)	((x) & 0x0F)
#घोषणा DEFLATE_MAKE_OPT(w)	((((w) - 8) << 4) + DEFLATE_METHOD_VAL)
#घोषणा DEFLATE_CHK_SEQUENCE	0

/*
 * Definitions क्रम MPPE.
 */

#घोषणा CI_MPPE                18      /* config option क्रम MPPE */
#घोषणा CILEN_MPPE              6      /* length of config option */

/*
 * Definitions क्रम other, as yet unsupported, compression methods.
 */

#घोषणा CI_PREDICTOR_1		1	/* config option क्रम Predictor-1 */
#घोषणा CILEN_PREDICTOR_1	2	/* length of its config option */
#घोषणा CI_PREDICTOR_2		2	/* config option क्रम Predictor-2 */
#घोषणा CILEN_PREDICTOR_2	2	/* length of its config option */


#पूर्ण_अगर /* _UAPI_NET_PPP_COMP_H */
