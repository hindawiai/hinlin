<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * net/tipc/crypto.h: Include file क्रम TIPC crypto
 *
 * Copyright (c) 2019, Ericsson AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#अगर_घोषित CONFIG_TIPC_CRYPTO
#अगर_अघोषित _TIPC_CRYPTO_H
#घोषणा _TIPC_CRYPTO_H

#समावेश "core.h"
#समावेश "node.h"
#समावेश "msg.h"
#समावेश "bearer.h"

#घोषणा TIPC_EVERSION			7

/* AEAD aes(gcm) */
#घोषणा TIPC_AES_GCM_KEY_SIZE_128	16
#घोषणा TIPC_AES_GCM_KEY_SIZE_192	24
#घोषणा TIPC_AES_GCM_KEY_SIZE_256	32

#घोषणा TIPC_AES_GCM_SALT_SIZE		4
#घोषणा TIPC_AES_GCM_IV_SIZE		12
#घोषणा TIPC_AES_GCM_TAG_SIZE		16

/*
 * TIPC crypto modes:
 * - CLUSTER_KEY:
 *	One single key is used क्रम both TX & RX in all nodes in the cluster.
 * - PER_NODE_KEY:
 *	Each nodes in the cluster has one TX key, क्रम RX a node needs to know
 *	its peers' TX key क्रम the decryption of messages from those nodes.
 */
क्रमागत अणु
	CLUSTER_KEY = 1,
	PER_NODE_KEY = (1 << 1),
पूर्ण;

बाह्य पूर्णांक sysctl_tipc_max_tfms __पढ़ो_mostly;
बाह्य पूर्णांक sysctl_tipc_key_exchange_enabled __पढ़ो_mostly;

/*
 * TIPC encryption message क्रमmat:
 *
 *     3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 *     1 0 9 8 7 6 5 4|3 2 1 0 9 8 7 6|5 4 3 2 1 0 9 8|7 6 5 4 3 2 1 0
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * w0:|Ver=7| User  |D|TX |RX |K|M|N|             Rsvd                |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * w1:|                             Seqno                             |
 * w2:|                           (8 octets)                          |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * w3:\                            Prevnode                           \
 *    /                        (4 or 16 octets)                       /
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    \                                                               \
 *    /       Encrypted complete TIPC V2 header and user data         /
 *    \                                                               \
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    |                                                               |
 *    |                             AuthTag                           |
 *    |                           (16 octets)                         |
 *    |                                                               |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Word0:
 *	Ver	: = 7 i.e. TIPC encryption message version
 *	User	: = 7 (क्रम LINK_PROTOCOL); = 13 (क्रम LINK_CONFIG) or = 0
 *	D	: The destined bit i.e. the message's destination node is
 *	          "known" or not at the message encryption
 *	TX	: TX key used क्रम the message encryption
 *	RX	: Currently RX active key corresponding to the destination
 *	          node's TX key (when the "D" bit is set)
 *	K	: Keep-alive bit (क्रम RPS, LINK_PROTOCOL/STATE_MSG only)
 *	M       : Bit indicates अगर sender has master key
 *	N	: Bit indicates अगर sender has no RX keys corresponding to the
 *	          receiver's TX (when the "D" bit is set)
 *	Rsvd	: Reserved bit, field
 * Word1-2:
 *	Seqno	: The 64-bit sequence number of the encrypted message, also
 *		  part of the nonce used क्रम the message encryption/decryption
 * Word3-:
 *	Prevnode: The source node address, or ID in हाल LINK_CONFIG only
 *	AuthTag	: The authentication tag क्रम the message पूर्णांकegrity checking
 *		  generated by the message encryption
 */
काष्ठा tipc_ehdr अणु
	जोड़ अणु
		काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
			__u8	destined:1,
				user:4,
				version:3;
			__u8	reserved_1:1,
				rx_nokey:1,
				master_key:1,
				keepalive:1,
				rx_key_active:2,
				tx_key:2;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
			__u8	version:3,
				user:4,
				destined:1;
			__u8	tx_key:2,
				rx_key_active:2,
				keepalive:1,
				master_key:1,
				rx_nokey:1,
				reserved_1:1;
#अन्यथा
#त्रुटि  "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
			__be16	reserved_2;
		पूर्ण __packed;
		__be32 w0;
	पूर्ण;
	__be64 seqno;
	जोड़ अणु
		__be32 addr;
		__u8 id[NODE_ID_LEN]; /* For a LINK_CONFIG message only! */
	पूर्ण;
#घोषणा EHDR_SIZE	(दुरत्व(काष्ठा tipc_ehdr, addr) + माप(__be32))
#घोषणा EHDR_CFG_SIZE	(माप(काष्ठा tipc_ehdr))
#घोषणा EHDR_MIN_SIZE	(EHDR_SIZE)
#घोषणा EHDR_MAX_SIZE	(EHDR_CFG_SIZE)
#घोषणा EMSG_OVERHEAD	(EHDR_SIZE + TIPC_AES_GCM_TAG_SIZE)
पूर्ण __packed;

पूर्णांक tipc_crypto_start(काष्ठा tipc_crypto **crypto, काष्ठा net *net,
		      काष्ठा tipc_node *node);
व्योम tipc_crypto_stop(काष्ठा tipc_crypto **crypto);
व्योम tipc_crypto_समयout(काष्ठा tipc_crypto *rx);
पूर्णांक tipc_crypto_xmit(काष्ठा net *net, काष्ठा sk_buff **skb,
		     काष्ठा tipc_bearer *b, काष्ठा tipc_media_addr *dst,
		     काष्ठा tipc_node *__dnode);
पूर्णांक tipc_crypto_rcv(काष्ठा net *net, काष्ठा tipc_crypto *rx,
		    काष्ठा sk_buff **skb, काष्ठा tipc_bearer *b);
पूर्णांक tipc_crypto_key_init(काष्ठा tipc_crypto *c, काष्ठा tipc_aead_key *ukey,
			 u8 mode, bool master_key);
व्योम tipc_crypto_key_flush(काष्ठा tipc_crypto *c);
पूर्णांक tipc_crypto_key_distr(काष्ठा tipc_crypto *tx, u8 key,
			  काष्ठा tipc_node *dest);
व्योम tipc_crypto_msg_rcv(काष्ठा net *net, काष्ठा sk_buff *skb);
व्योम tipc_crypto_rekeying_sched(काष्ठा tipc_crypto *tx, bool changed,
				u32 new_पूर्णांकv);
पूर्णांक tipc_aead_key_validate(काष्ठा tipc_aead_key *ukey, काष्ठा genl_info *info);
bool tipc_ehdr_validate(काष्ठा sk_buff *skb);

अटल अंतरभूत u32 msg_key_gen(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 4, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_key_gen(काष्ठा tipc_msg *m, u32 gen)
अणु
	msg_set_bits(m, 4, 16, 0xffff, gen);
पूर्ण

अटल अंतरभूत u32 msg_key_mode(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 4, 0, 0xf);
पूर्ण

अटल अंतरभूत व्योम msg_set_key_mode(काष्ठा tipc_msg *m, u32 mode)
अणु
	msg_set_bits(m, 4, 0, 0xf, mode);
पूर्ण

#पूर्ण_अगर /* _TIPC_CRYPTO_H */
#पूर्ण_अगर
