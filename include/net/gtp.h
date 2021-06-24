<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _GTP_H_
#घोषणा _GTP_H_

/* General GTP protocol related definitions. */

#घोषणा GTP0_PORT	3386
#घोषणा GTP1U_PORT	2152

#घोषणा GTP_TPDU	255

काष्ठा gtp0_header अणु	/* According to GSM TS 09.60. */
	__u8	flags;
	__u8	type;
	__be16	length;
	__be16	seq;
	__be16	flow;
	__u8	number;
	__u8	spare[3];
	__be64	tid;
पूर्ण __attribute__ ((packed));

काष्ठा gtp1_header अणु	/* According to 3GPP TS 29.060. */
	__u8	flags;
	__u8	type;
	__be16	length;
	__be32	tid;
पूर्ण __attribute__ ((packed));

#घोषणा GTP1_F_NPDU	0x01
#घोषणा GTP1_F_SEQ	0x02
#घोषणा GTP1_F_EXTHDR	0x04
#घोषणा GTP1_F_MASK	0x07

#पूर्ण_अगर
