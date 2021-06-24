<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित XT_HMARK_H_
#घोषणा XT_HMARK_H_

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>

क्रमागत अणु
	XT_HMARK_SADDR_MASK,
	XT_HMARK_DADDR_MASK,
	XT_HMARK_SPI,
	XT_HMARK_SPI_MASK,
	XT_HMARK_SPORT,
	XT_HMARK_DPORT,
	XT_HMARK_SPORT_MASK,
	XT_HMARK_DPORT_MASK,
	XT_HMARK_PROTO_MASK,
	XT_HMARK_RND,
	XT_HMARK_MODULUS,
	XT_HMARK_OFFSET,
	XT_HMARK_CT,
	XT_HMARK_METHOD_L3,
	XT_HMARK_METHOD_L3_4,
पूर्ण;
#घोषणा XT_HMARK_FLAG(flag)	(1 << flag)

जोड़ hmark_ports अणु
	काष्ठा अणु
		__u16	src;
		__u16	dst;
	पूर्ण p16;
	काष्ठा अणु
		__be16	src;
		__be16	dst;
	पूर्ण b16;
	__u32	v32;
	__be32	b32;
पूर्ण;

काष्ठा xt_hmark_info अणु
	जोड़ nf_inet_addr	src_mask;
	जोड़ nf_inet_addr	dst_mask;
	जोड़ hmark_ports	port_mask;
	जोड़ hmark_ports	port_set;
	__u32			flags;
	__u16			proto_mask;
	__u32			hashrnd;
	__u32			hmodulus;
	__u32			hoffset;	/* Mark offset to start from */
पूर्ण;

#पूर्ण_अगर /* XT_HMARK_H_ */
