<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_CONNBYTES_H
#घोषणा _XT_CONNBYTES_H

#समावेश <linux/types.h>

क्रमागत xt_connbytes_what अणु
	XT_CONNBYTES_PKTS,
	XT_CONNBYTES_BYTES,
	XT_CONNBYTES_AVGPKT,
पूर्ण;

क्रमागत xt_connbytes_direction अणु
	XT_CONNBYTES_सूची_ORIGINAL,
	XT_CONNBYTES_सूची_REPLY,
	XT_CONNBYTES_सूची_BOTH,
पूर्ण;

काष्ठा xt_connbytes_info अणु
	काष्ठा अणु
		__aligned_u64 from;	/* count to be matched */
		__aligned_u64 to;	/* count to be matched */
	पूर्ण count;
	__u8 what;		/* ipt_connbytes_what */
	__u8 direction;	/* ipt_connbytes_direction */
पूर्ण;
#पूर्ण_अगर
