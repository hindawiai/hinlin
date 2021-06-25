<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SCTP kernel reference Implementation
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001-2003 International Business Machines, Corp.
 *
 * This file is part of the SCTP kernel reference Implementation
 *
 * SCTP Checksum functions
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Dinakaran Joseph
 *    Jon Grimm <jgrimm@us.ibm.com>
 *    Sridhar Samudrala <sri@us.ibm.com>
 *
 * Rewritten to use libcrc32c by:
 *    Vlad Yasevich <vladislav.yasevich@hp.com>
 */

#अगर_अघोषित __sctp_checksum_h__
#घोषणा __sctp_checksum_h__

#समावेश <linux/types.h>
#समावेश <net/sctp/sctp.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/crc32.h>

अटल अंतरभूत __wsum sctp_csum_update(स्थिर व्योम *buff, पूर्णांक len, __wsum sum)
अणु
	/* This uses the crypto implementation of crc32c, which is either
	 * implemented w/ hardware support or resolves to __crc32c_le().
	 */
	वापस (__क्रमce __wsum)crc32c((__क्रमce __u32)sum, buff, len);
पूर्ण

अटल अंतरभूत __wsum sctp_csum_combine(__wsum csum, __wsum csum2,
				       पूर्णांक offset, पूर्णांक len)
अणु
	वापस (__क्रमce __wsum)__crc32c_le_combine((__क्रमce __u32)csum,
						   (__क्रमce __u32)csum2, len);
पूर्ण

अटल स्थिर काष्ठा skb_checksum_ops sctp_csum_ops = अणु
	.update  = sctp_csum_update,
	.combine = sctp_csum_combine,
पूर्ण;

अटल अंतरभूत __le32 sctp_compute_cksum(स्थिर काष्ठा sk_buff *skb,
					अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sctphdr *sh = (काष्ठा sctphdr *)(skb->data + offset);
	__le32 old = sh->checksum;
	__wsum new;

	sh->checksum = 0;
	new = ~__skb_checksum(skb, offset, skb->len - offset, ~(__wsum)0,
			      &sctp_csum_ops);
	sh->checksum = old;

	वापस cpu_to_le32((__क्रमce __u32)new);
पूर्ण

#पूर्ण_अगर /* __sctp_checksum_h__ */
