<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_REJECT_H
#घोषणा _NF_REJECT_H

#समावेश <linux/types.h>
#समावेश <uapi/linux/in.h>

अटल अंतरभूत bool nf_reject_verअगरy_csum(__u8 proto)
अणु
	/* Skip protocols that करोn't use 16-bit one's complement checksum
	 * of the entire payload.
	 */
	चयन (proto) अणु
		/* Protocols with other पूर्णांकegrity checks. */
		हाल IPPROTO_AH:
		हाल IPPROTO_ESP:
		हाल IPPROTO_SCTP:

		/* Protocols with partial checksums. */
		हाल IPPROTO_UDPLITE:
		हाल IPPROTO_DCCP:

		/* Protocols with optional checksums. */
		हाल IPPROTO_GRE:
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

#पूर्ण_अगर /* _NF_REJECT_H */
