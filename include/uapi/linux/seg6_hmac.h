<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_SEG6_HMAC_H
#घोषणा _UAPI_LINUX_SEG6_HMAC_H

#समावेश <linux/types.h>
#समावेश <linux/seg6.h>

#घोषणा SEG6_HMAC_SECRET_LEN	64
#घोषणा SEG6_HMAC_FIELD_LEN	32

काष्ठा sr6_tlv_hmac अणु
	काष्ठा sr6_tlv tlvhdr;
	__u16 reserved;
	__be32 hmackeyid;
	__u8 hmac[SEG6_HMAC_FIELD_LEN];
पूर्ण;

क्रमागत अणु
	SEG6_HMAC_ALGO_SHA1 = 1,
	SEG6_HMAC_ALGO_SHA256 = 2,
पूर्ण;

#पूर्ण_अगर
