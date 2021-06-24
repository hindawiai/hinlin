<शैली गुरु>
/*
 * net/tipc/msg.h: Include file क्रम TIPC message header routines
 *
 * Copyright (c) 2000-2007, 2014-2017 Ericsson AB
 * Copyright (c) 2005-2008, 2010-2011, Wind River Systems
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

#अगर_अघोषित _TIPC_MSG_H
#घोषणा _TIPC_MSG_H

#समावेश <linux/tipc.h>
#समावेश "core.h"

/*
 * Constants and routines used to पढ़ो and ग_लिखो TIPC payload message headers
 *
 * Note: Some items are also used with TIPC पूर्णांकernal message headers
 */
#घोषणा TIPC_VERSION              2
काष्ठा plist;

/*
 * Payload message users are defined in TIPC's खुला API:
 * - TIPC_LOW_IMPORTANCE
 * - TIPC_MEDIUM_IMPORTANCE
 * - TIPC_HIGH_IMPORTANCE
 * - TIPC_CRITICAL_IMPORTANCE
 */
#घोषणा TIPC_SYSTEM_IMPORTANCE	4


/*
 * Payload message types
 */
#घोषणा TIPC_CONN_MSG           0
#घोषणा TIPC_MCAST_MSG          1
#घोषणा TIPC_NAMED_MSG          2
#घोषणा TIPC_सूचीECT_MSG         3
#घोषणा TIPC_GRP_MEMBER_EVT     4
#घोषणा TIPC_GRP_BCAST_MSG      5
#घोषणा TIPC_GRP_MCAST_MSG      6
#घोषणा TIPC_GRP_UCAST_MSG      7

/*
 * Internal message users
 */
#घोषणा  BCAST_PROTOCOL       5
#घोषणा  MSG_BUNDLER          6
#घोषणा  LINK_PROTOCOL        7
#घोषणा  CONN_MANAGER         8
#घोषणा  GROUP_PROTOCOL       9
#घोषणा  TUNNEL_PROTOCOL      10
#घोषणा  NAME_DISTRIBUTOR     11
#घोषणा  MSG_FRAGMENTER       12
#घोषणा  LINK_CONFIG          13
#घोषणा  MSG_CRYPTO           14
#घोषणा  SOCK_WAKEUP          14       /* pseuकरो user */
#घोषणा  TOP_SRV              15       /* pseuकरो user */

/*
 * Message header sizes
 */
#घोषणा SHORT_H_SIZE              24	/* In-cluster basic payload message */
#घोषणा BASIC_H_SIZE              32	/* Basic payload message */
#घोषणा NAMED_H_SIZE              40	/* Named payload message */
#घोषणा MCAST_H_SIZE              44	/* Multicast payload message */
#घोषणा GROUP_H_SIZE              44	/* Group payload message */
#घोषणा INT_H_SIZE                40	/* Internal messages */
#घोषणा MIN_H_SIZE                24	/* Smallest legal TIPC header size */
#घोषणा MAX_H_SIZE                60	/* Largest possible TIPC header size */

#घोषणा MAX_MSG_SIZE (MAX_H_SIZE + TIPC_MAX_USER_MSG_SIZE)
#घोषणा FB_MTU                  3744
#घोषणा TIPC_MEDIA_INFO_OFFSET	5

काष्ठा tipc_skb_cb अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा sk_buff *tail;
			अचिन्हित दीर्घ nxt_retr;
			अचिन्हित दीर्घ retr_stamp;
			u32 bytes_पढ़ो;
			u32 orig_member;
			u16 chain_imp;
			u16 ackers;
			u16 retr_cnt;
		पूर्ण __packed;
#अगर_घोषित CONFIG_TIPC_CRYPTO
		काष्ठा अणु
			काष्ठा tipc_crypto *rx;
			काष्ठा tipc_aead *last;
			u8 recurs;
		पूर्ण tx_clone_ctx __packed;
#पूर्ण_अगर
	पूर्ण __packed;
	जोड़ अणु
		काष्ठा अणु
			u8 validated:1;
#अगर_घोषित CONFIG_TIPC_CRYPTO
			u8 encrypted:1;
			u8 decrypted:1;
#घोषणा SKB_PROBING	1
#घोषणा SKB_GRACING	2
			u8 xmit_type:2;
			u8 tx_clone_deferred:1;
#पूर्ण_अगर
		पूर्ण;
		u8 flags;
	पूर्ण;
	u8 reserved;
#अगर_घोषित CONFIG_TIPC_CRYPTO
	व्योम *crypto_ctx;
#पूर्ण_अगर
पूर्ण __packed;

#घोषणा TIPC_SKB_CB(__skb) ((काष्ठा tipc_skb_cb *)&((__skb)->cb[0]))

काष्ठा tipc_msg अणु
	__be32 hdr[15];
पूर्ण;

/* काष्ठा tipc_gap_ack - TIPC Gap ACK block
 * @ack: seqno of the last consecutive packet in link deferdq
 * @gap: number of gap packets since the last ack
 *
 * E.g:
 *       link deferdq: 1 2 3 4      10 11      13 14 15       20
 * --> Gap ACK blocks:      <4, 5>,   <11, 1>,      <15, 4>, <20, 0>
 */
काष्ठा tipc_gap_ack अणु
	__be16 ack;
	__be16 gap;
पूर्ण;

/* काष्ठा tipc_gap_ack_blks
 * @len: actual length of the record
 * @ugack_cnt: number of Gap ACK blocks क्रम unicast (following the broadcast
 *             ones)
 * @start_index: starting index क्रम "valid" broadcast Gap ACK blocks
 * @bgack_cnt: number of Gap ACK blocks क्रम broadcast in the record
 * @gacks: array of Gap ACK blocks
 *
 *  31                       16 15                        0
 * +-------------+-------------+-------------+-------------+
 * |  bgack_cnt  |  ugack_cnt  |            len            |
 * +-------------+-------------+-------------+-------------+  -
 * |            gap            |            ack            |   |
 * +-------------+-------------+-------------+-------------+    > bc gacks
 * :                           :                           :   |
 * +-------------+-------------+-------------+-------------+  -
 * |            gap            |            ack            |   |
 * +-------------+-------------+-------------+-------------+    > uc gacks
 * :                           :                           :   |
 * +-------------+-------------+-------------+-------------+  -
 */
काष्ठा tipc_gap_ack_blks अणु
	__be16 len;
	जोड़ अणु
		u8 ugack_cnt;
		u8 start_index;
	पूर्ण;
	u8 bgack_cnt;
	काष्ठा tipc_gap_ack gacks[];
पूर्ण;

#घोषणा MAX_GAP_ACK_BLKS	128
#घोषणा MAX_GAP_ACK_BLKS_SZ	(माप(काष्ठा tipc_gap_ack_blks) + \
				 माप(काष्ठा tipc_gap_ack) * MAX_GAP_ACK_BLKS)

अटल अंतरभूत काष्ठा tipc_msg *buf_msg(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा tipc_msg *)skb->data;
पूर्ण

अटल अंतरभूत u32 msg_word(काष्ठा tipc_msg *m, u32 pos)
अणु
	वापस ntohl(m->hdr[pos]);
पूर्ण

अटल अंतरभूत व्योम msg_set_word(काष्ठा tipc_msg *m, u32 w, u32 val)
अणु
	m->hdr[w] = htonl(val);
पूर्ण

अटल अंतरभूत u32 msg_bits(काष्ठा tipc_msg *m, u32 w, u32 pos, u32 mask)
अणु
	वापस (msg_word(m, w) >> pos) & mask;
पूर्ण

अटल अंतरभूत व्योम msg_set_bits(काष्ठा tipc_msg *m, u32 w,
				u32 pos, u32 mask, u32 val)
अणु
	val = (val & mask) << pos;
	mask = mask << pos;
	m->hdr[w] &= ~htonl(mask);
	m->hdr[w] |= htonl(val);
पूर्ण

अटल अंतरभूत व्योम msg_swap_words(काष्ठा tipc_msg *msg, u32 a, u32 b)
अणु
	u32 temp = msg->hdr[a];

	msg->hdr[a] = msg->hdr[b];
	msg->hdr[b] = temp;
पूर्ण

/*
 * Word 0
 */
अटल अंतरभूत u32 msg_version(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 29, 7);
पूर्ण

अटल अंतरभूत व्योम msg_set_version(काष्ठा tipc_msg *m)
अणु
	msg_set_bits(m, 0, 29, 7, TIPC_VERSION);
पूर्ण

अटल अंतरभूत u32 msg_user(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 25, 0xf);
पूर्ण

अटल अंतरभूत u32 msg_isdata(काष्ठा tipc_msg *m)
अणु
	वापस msg_user(m) <= TIPC_CRITICAL_IMPORTANCE;
पूर्ण

अटल अंतरभूत व्योम msg_set_user(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 0, 25, 0xf, n);
पूर्ण

अटल अंतरभूत u32 msg_hdr_sz(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 21, 0xf) << 2;
पूर्ण

अटल अंतरभूत व्योम msg_set_hdr_sz(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 0, 21, 0xf, n>>2);
पूर्ण

अटल अंतरभूत u32 msg_size(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 0, 0x1ffff);
पूर्ण

अटल अंतरभूत u32 msg_blocks(काष्ठा tipc_msg *m)
अणु
	वापस (msg_size(m) / 1024) + 1;
पूर्ण

अटल अंतरभूत u32 msg_data_sz(काष्ठा tipc_msg *m)
अणु
	वापस msg_size(m) - msg_hdr_sz(m);
पूर्ण

अटल अंतरभूत पूर्णांक msg_non_seq(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 20, 1);
पूर्ण

अटल अंतरभूत व्योम msg_set_non_seq(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 0, 20, 1, n);
पूर्ण

अटल अंतरभूत पूर्णांक msg_is_syn(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 17, 1);
पूर्ण

अटल अंतरभूत व्योम msg_set_syn(काष्ठा tipc_msg *m, u32 d)
अणु
	msg_set_bits(m, 0, 17, 1, d);
पूर्ण

अटल अंतरभूत पूर्णांक msg_dest_droppable(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 19, 1);
पूर्ण

अटल अंतरभूत व्योम msg_set_dest_droppable(काष्ठा tipc_msg *m, u32 d)
अणु
	msg_set_bits(m, 0, 19, 1, d);
पूर्ण

अटल अंतरभूत पूर्णांक msg_is_keepalive(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 19, 1);
पूर्ण

अटल अंतरभूत व्योम msg_set_is_keepalive(काष्ठा tipc_msg *m, u32 d)
अणु
	msg_set_bits(m, 0, 19, 1, d);
पूर्ण

अटल अंतरभूत पूर्णांक msg_src_droppable(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 18, 1);
पूर्ण

अटल अंतरभूत व्योम msg_set_src_droppable(काष्ठा tipc_msg *m, u32 d)
अणु
	msg_set_bits(m, 0, 18, 1, d);
पूर्ण

अटल अंतरभूत पूर्णांक msg_ack_required(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 18, 1);
पूर्ण

अटल अंतरभूत व्योम msg_set_ack_required(काष्ठा tipc_msg *m)
अणु
	msg_set_bits(m, 0, 18, 1, 1);
पूर्ण

अटल अंतरभूत पूर्णांक msg_nagle_ack(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 18, 1);
पूर्ण

अटल अंतरभूत व्योम msg_set_nagle_ack(काष्ठा tipc_msg *m)
अणु
	msg_set_bits(m, 0, 18, 1, 1);
पूर्ण

अटल अंतरभूत bool msg_is_rcast(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 0, 18, 0x1);
पूर्ण

अटल अंतरभूत व्योम msg_set_is_rcast(काष्ठा tipc_msg *m, bool d)
अणु
	msg_set_bits(m, 0, 18, 0x1, d);
पूर्ण

अटल अंतरभूत व्योम msg_set_size(काष्ठा tipc_msg *m, u32 sz)
अणु
	m->hdr[0] = htonl((msg_word(m, 0) & ~0x1ffff) | sz);
पूर्ण

अटल अंतरभूत unअक्षर *msg_data(काष्ठा tipc_msg *m)
अणु
	वापस ((unअक्षर *)m) + msg_hdr_sz(m);
पूर्ण

अटल अंतरभूत काष्ठा tipc_msg *msg_inner_hdr(काष्ठा tipc_msg *m)
अणु
	वापस (काष्ठा tipc_msg *)msg_data(m);
पूर्ण

/*
 * Word 1
 */
अटल अंतरभूत u32 msg_type(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 29, 0x7);
पूर्ण

अटल अंतरभूत व्योम msg_set_type(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 1, 29, 0x7, n);
पूर्ण

अटल अंतरभूत पूर्णांक msg_in_group(काष्ठा tipc_msg *m)
अणु
	पूर्णांक mtyp = msg_type(m);

	वापस mtyp >= TIPC_GRP_MEMBER_EVT && mtyp <= TIPC_GRP_UCAST_MSG;
पूर्ण

अटल अंतरभूत bool msg_is_grp_evt(काष्ठा tipc_msg *m)
अणु
	वापस msg_type(m) == TIPC_GRP_MEMBER_EVT;
पूर्ण

अटल अंतरभूत u32 msg_named(काष्ठा tipc_msg *m)
अणु
	वापस msg_type(m) == TIPC_NAMED_MSG;
पूर्ण

अटल अंतरभूत u32 msg_mcast(काष्ठा tipc_msg *m)
अणु
	पूर्णांक mtyp = msg_type(m);

	वापस ((mtyp == TIPC_MCAST_MSG) || (mtyp == TIPC_GRP_BCAST_MSG) ||
		(mtyp == TIPC_GRP_MCAST_MSG));
पूर्ण

अटल अंतरभूत u32 msg_connected(काष्ठा tipc_msg *m)
अणु
	वापस msg_type(m) == TIPC_CONN_MSG;
पूर्ण

अटल अंतरभूत u32 msg_direct(काष्ठा tipc_msg *m)
अणु
	वापस msg_type(m) == TIPC_सूचीECT_MSG;
पूर्ण

अटल अंतरभूत u32 msg_errcode(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 25, 0xf);
पूर्ण

अटल अंतरभूत व्योम msg_set_errcode(काष्ठा tipc_msg *m, u32 err)
अणु
	msg_set_bits(m, 1, 25, 0xf, err);
पूर्ण

अटल अंतरभूत व्योम msg_set_bulk(काष्ठा tipc_msg *m)
अणु
	msg_set_bits(m, 1, 28, 0x1, 1);
पूर्ण

अटल अंतरभूत u32 msg_is_bulk(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 28, 0x1);
पूर्ण

अटल अंतरभूत व्योम msg_set_last_bulk(काष्ठा tipc_msg *m)
अणु
	msg_set_bits(m, 1, 27, 0x1, 1);
पूर्ण

अटल अंतरभूत u32 msg_is_last_bulk(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 27, 0x1);
पूर्ण

अटल अंतरभूत व्योम msg_set_non_legacy(काष्ठा tipc_msg *m)
अणु
	msg_set_bits(m, 1, 26, 0x1, 1);
पूर्ण

अटल अंतरभूत u32 msg_is_legacy(काष्ठा tipc_msg *m)
अणु
	वापस !msg_bits(m, 1, 26, 0x1);
पूर्ण

अटल अंतरभूत u32 msg_reroute_cnt(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 21, 0xf);
पूर्ण

अटल अंतरभूत व्योम msg_incr_reroute_cnt(काष्ठा tipc_msg *m)
अणु
	msg_set_bits(m, 1, 21, 0xf, msg_reroute_cnt(m) + 1);
पूर्ण

अटल अंतरभूत व्योम msg_reset_reroute_cnt(काष्ठा tipc_msg *m)
अणु
	msg_set_bits(m, 1, 21, 0xf, 0);
पूर्ण

अटल अंतरभूत u32 msg_lookup_scope(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 19, 0x3);
पूर्ण

अटल अंतरभूत व्योम msg_set_lookup_scope(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 1, 19, 0x3, n);
पूर्ण

अटल अंतरभूत u16 msg_bcast_ack(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 0, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_bcast_ack(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 1, 0, 0xffff, n);
पूर्ण

/* Note: reusing bits in word 1 क्रम ACTIVATE_MSG only, to re-synch
 * link peer session number
 */
अटल अंतरभूत bool msg_dest_session_valid(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 16, 0x1);
पूर्ण

अटल अंतरभूत व्योम msg_set_dest_session_valid(काष्ठा tipc_msg *m, bool valid)
अणु
	msg_set_bits(m, 1, 16, 0x1, valid);
पूर्ण

अटल अंतरभूत u16 msg_dest_session(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 0, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_dest_session(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 1, 0, 0xffff, n);
पूर्ण

/*
 * Word 2
 */
अटल अंतरभूत u16 msg_ack(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 2, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_ack(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 2, 16, 0xffff, n);
पूर्ण

अटल अंतरभूत u16 msg_seqno(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 2, 0, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_seqno(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 2, 0, 0xffff, n);
पूर्ण

/*
 * Words 3-10
 */
अटल अंतरभूत u32 msg_importance(काष्ठा tipc_msg *m)
अणु
	पूर्णांक usr = msg_user(m);

	अगर (likely((usr <= TIPC_CRITICAL_IMPORTANCE) && !msg_errcode(m)))
		वापस usr;
	अगर ((usr == MSG_FRAGMENTER) || (usr == MSG_BUNDLER))
		वापस msg_bits(m, 9, 0, 0x7);
	वापस TIPC_SYSTEM_IMPORTANCE;
पूर्ण

अटल अंतरभूत व्योम msg_set_importance(काष्ठा tipc_msg *m, u32 i)
अणु
	पूर्णांक usr = msg_user(m);

	अगर (likely((usr == MSG_FRAGMENTER) || (usr == MSG_BUNDLER)))
		msg_set_bits(m, 9, 0, 0x7, i);
	अन्यथा अगर (i < TIPC_SYSTEM_IMPORTANCE)
		msg_set_user(m, i);
	अन्यथा
		pr_warn("Trying to set illegal importance in message\n");
पूर्ण

अटल अंतरभूत u32 msg_prevnode(काष्ठा tipc_msg *m)
अणु
	वापस msg_word(m, 3);
पूर्ण

अटल अंतरभूत व्योम msg_set_prevnode(काष्ठा tipc_msg *m, u32 a)
अणु
	msg_set_word(m, 3, a);
पूर्ण

अटल अंतरभूत u32 msg_origport(काष्ठा tipc_msg *m)
अणु
	अगर (msg_user(m) == MSG_FRAGMENTER)
		m = msg_inner_hdr(m);
	वापस msg_word(m, 4);
पूर्ण

अटल अंतरभूत व्योम msg_set_origport(काष्ठा tipc_msg *m, u32 p)
अणु
	msg_set_word(m, 4, p);
पूर्ण

अटल अंतरभूत u16 msg_named_seqno(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 4, 0, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_named_seqno(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 4, 0, 0xffff, n);
पूर्ण

अटल अंतरभूत u32 msg_destport(काष्ठा tipc_msg *m)
अणु
	वापस msg_word(m, 5);
पूर्ण

अटल अंतरभूत व्योम msg_set_destport(काष्ठा tipc_msg *m, u32 p)
अणु
	msg_set_word(m, 5, p);
पूर्ण

अटल अंतरभूत u32 msg_mc_netid(काष्ठा tipc_msg *m)
अणु
	वापस msg_word(m, 5);
पूर्ण

अटल अंतरभूत व्योम msg_set_mc_netid(काष्ठा tipc_msg *m, u32 p)
अणु
	msg_set_word(m, 5, p);
पूर्ण

अटल अंतरभूत पूर्णांक msg_लघु(काष्ठा tipc_msg *m)
अणु
	वापस msg_hdr_sz(m) == SHORT_H_SIZE;
पूर्ण

अटल अंतरभूत u32 msg_orignode(काष्ठा tipc_msg *m)
अणु
	अगर (likely(msg_लघु(m)))
		वापस msg_prevnode(m);
	वापस msg_word(m, 6);
पूर्ण

अटल अंतरभूत व्योम msg_set_orignode(काष्ठा tipc_msg *m, u32 a)
अणु
	msg_set_word(m, 6, a);
पूर्ण

अटल अंतरभूत u32 msg_destnode(काष्ठा tipc_msg *m)
अणु
	वापस msg_word(m, 7);
पूर्ण

अटल अंतरभूत व्योम msg_set_destnode(काष्ठा tipc_msg *m, u32 a)
अणु
	msg_set_word(m, 7, a);
पूर्ण

अटल अंतरभूत u32 msg_nametype(काष्ठा tipc_msg *m)
अणु
	वापस msg_word(m, 8);
पूर्ण

अटल अंतरभूत व्योम msg_set_nametype(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_word(m, 8, n);
पूर्ण

अटल अंतरभूत u32 msg_nameinst(काष्ठा tipc_msg *m)
अणु
	वापस msg_word(m, 9);
पूर्ण

अटल अंतरभूत u32 msg_namelower(काष्ठा tipc_msg *m)
अणु
	वापस msg_nameinst(m);
पूर्ण

अटल अंतरभूत व्योम msg_set_namelower(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_word(m, 9, n);
पूर्ण

अटल अंतरभूत व्योम msg_set_nameinst(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_namelower(m, n);
पूर्ण

अटल अंतरभूत u32 msg_nameupper(काष्ठा tipc_msg *m)
अणु
	वापस msg_word(m, 10);
पूर्ण

अटल अंतरभूत व्योम msg_set_nameupper(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_word(m, 10, n);
पूर्ण

/*
 * Constants and routines used to पढ़ो and ग_लिखो TIPC पूर्णांकernal message headers
 */

/*
 *  Connection management protocol message types
 */
#घोषणा CONN_PROBE        0
#घोषणा CONN_PROBE_REPLY  1
#घोषणा CONN_ACK          2

/*
 * Name distributor message types
 */
#घोषणा PUBLICATION       0
#घोषणा WITHDRAWAL        1

/*
 * Segmentation message types
 */
#घोषणा FIRST_FRAGMENT		0
#घोषणा FRAGMENT		1
#घोषणा LAST_FRAGMENT		2

/*
 * Link management protocol message types
 */
#घोषणा STATE_MSG		0
#घोषणा RESET_MSG		1
#घोषणा ACTIVATE_MSG		2

/*
 * Changeover tunnel message types
 */
#घोषणा SYNCH_MSG		0
#घोषणा FAILOVER_MSG		1

/*
 * Config protocol message types
 */
#घोषणा DSC_REQ_MSG		0
#घोषणा DSC_RESP_MSG		1
#घोषणा DSC_TRIAL_MSG		2
#घोषणा DSC_TRIAL_FAIL_MSG	3

/*
 * Group protocol message types
 */
#घोषणा GRP_JOIN_MSG         0
#घोषणा GRP_LEAVE_MSG        1
#घोषणा GRP_ADV_MSG          2
#घोषणा GRP_ACK_MSG          3
#घोषणा GRP_RECLAIM_MSG      4
#घोषणा GRP_REMIT_MSG        5

/* Crypto message types */
#घोषणा KEY_DISTR_MSG		0

/*
 * Word 1
 */
अटल अंतरभूत u32 msg_seq_gap(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 16, 0x1fff);
पूर्ण

अटल अंतरभूत व्योम msg_set_seq_gap(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 1, 16, 0x1fff, n);
पूर्ण

अटल अंतरभूत u32 msg_node_sig(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 0, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_node_sig(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 1, 0, 0xffff, n);
पूर्ण

अटल अंतरभूत u32 msg_node_capabilities(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 1, 15, 0x1fff);
पूर्ण

अटल अंतरभूत व्योम msg_set_node_capabilities(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 1, 15, 0x1fff, n);
पूर्ण

/*
 * Word 2
 */
अटल अंतरभूत u32 msg_dest_करोमुख्य(काष्ठा tipc_msg *m)
अणु
	वापस msg_word(m, 2);
पूर्ण

अटल अंतरभूत व्योम msg_set_dest_करोमुख्य(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_word(m, 2, n);
पूर्ण

अटल अंतरभूत u32 msg_bcgap_after(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 2, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_bcgap_after(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 2, 16, 0xffff, n);
पूर्ण

अटल अंतरभूत u32 msg_bcgap_to(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 2, 0, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_bcgap_to(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 2, 0, 0xffff, n);
पूर्ण

/*
 * Word 4
 */
अटल अंतरभूत u32 msg_last_bcast(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 4, 16, 0xffff);
पूर्ण

अटल अंतरभूत u32 msg_bc_snd_nxt(काष्ठा tipc_msg *m)
अणु
	वापस msg_last_bcast(m) + 1;
पूर्ण

अटल अंतरभूत व्योम msg_set_last_bcast(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 4, 16, 0xffff, n);
पूर्ण

अटल अंतरभूत u32 msg_nof_fragms(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 4, 0, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_nof_fragms(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 4, 0, 0xffff, n);
पूर्ण

अटल अंतरभूत u32 msg_fragm_no(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 4, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_fragm_no(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 4, 16, 0xffff, n);
पूर्ण

अटल अंतरभूत u16 msg_next_sent(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 4, 0, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_next_sent(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 4, 0, 0xffff, n);
पूर्ण

अटल अंतरभूत व्योम msg_set_दीर्घ_msgno(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 4, 0, 0xffff, n);
पूर्ण

अटल अंतरभूत u32 msg_bc_netid(काष्ठा tipc_msg *m)
अणु
	वापस msg_word(m, 4);
पूर्ण

अटल अंतरभूत व्योम msg_set_bc_netid(काष्ठा tipc_msg *m, u32 id)
अणु
	msg_set_word(m, 4, id);
पूर्ण

अटल अंतरभूत u32 msg_link_selector(काष्ठा tipc_msg *m)
अणु
	अगर (msg_user(m) == MSG_FRAGMENTER)
		m = (व्योम *)msg_data(m);
	वापस msg_bits(m, 4, 0, 1);
पूर्ण

/*
 * Word 5
 */
अटल अंतरभूत u16 msg_session(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 5, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_session(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 5, 16, 0xffff, n);
पूर्ण

अटल अंतरभूत u32 msg_probe(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 5, 0, 1);
पूर्ण

अटल अंतरभूत व्योम msg_set_probe(काष्ठा tipc_msg *m, u32 val)
अणु
	msg_set_bits(m, 5, 0, 1, val);
पूर्ण

अटल अंतरभूत अक्षर msg_net_plane(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 5, 1, 7) + 'A';
पूर्ण

अटल अंतरभूत व्योम msg_set_net_plane(काष्ठा tipc_msg *m, अक्षर n)
अणु
	msg_set_bits(m, 5, 1, 7, (n - 'A'));
पूर्ण

अटल अंतरभूत u32 msg_linkprio(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 5, 4, 0x1f);
पूर्ण

अटल अंतरभूत व्योम msg_set_linkprio(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 5, 4, 0x1f, n);
पूर्ण

अटल अंतरभूत u32 msg_bearer_id(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 5, 9, 0x7);
पूर्ण

अटल अंतरभूत व्योम msg_set_bearer_id(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 5, 9, 0x7, n);
पूर्ण

अटल अंतरभूत u32 msg_redundant_link(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 5, 12, 0x1);
पूर्ण

अटल अंतरभूत व्योम msg_set_redundant_link(काष्ठा tipc_msg *m, u32 r)
अणु
	msg_set_bits(m, 5, 12, 0x1, r);
पूर्ण

अटल अंतरभूत u32 msg_peer_stopping(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 5, 13, 0x1);
पूर्ण

अटल अंतरभूत व्योम msg_set_peer_stopping(काष्ठा tipc_msg *m, u32 s)
अणु
	msg_set_bits(m, 5, 13, 0x1, s);
पूर्ण

अटल अंतरभूत bool msg_bc_ack_invalid(काष्ठा tipc_msg *m)
अणु
	चयन (msg_user(m)) अणु
	हाल BCAST_PROTOCOL:
	हाल NAME_DISTRIBUTOR:
	हाल LINK_PROTOCOL:
		वापस msg_bits(m, 5, 14, 0x1);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम msg_set_bc_ack_invalid(काष्ठा tipc_msg *m, bool invalid)
अणु
	msg_set_bits(m, 5, 14, 0x1, invalid);
पूर्ण

अटल अंतरभूत अक्षर *msg_media_addr(काष्ठा tipc_msg *m)
अणु
	वापस (अक्षर *)&m->hdr[TIPC_MEDIA_INFO_OFFSET];
पूर्ण

अटल अंतरभूत u32 msg_bc_gap(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 8, 0, 0x3ff);
पूर्ण

अटल अंतरभूत व्योम msg_set_bc_gap(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 8, 0, 0x3ff, n);
पूर्ण

/*
 * Word 9
 */
अटल अंतरभूत u16 msg_msgcnt(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 9, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_msgcnt(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 9, 16, 0xffff, n);
पूर्ण

अटल अंतरभूत u16 msg_syncpt(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 9, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_syncpt(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 9, 16, 0xffff, n);
पूर्ण

अटल अंतरभूत u32 msg_conn_ack(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 9, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_conn_ack(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 9, 16, 0xffff, n);
पूर्ण

अटल अंतरभूत u16 msg_adv_win(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 9, 0, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_adv_win(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 9, 0, 0xffff, n);
पूर्ण

अटल अंतरभूत u32 msg_max_pkt(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 9, 16, 0xffff) * 4;
पूर्ण

अटल अंतरभूत व्योम msg_set_max_pkt(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 9, 16, 0xffff, (n / 4));
पूर्ण

अटल अंतरभूत u32 msg_link_tolerance(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 9, 0, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_link_tolerance(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 9, 0, 0xffff, n);
पूर्ण

अटल अंतरभूत u16 msg_grp_bc_syncpt(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 9, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_grp_bc_syncpt(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 9, 16, 0xffff, n);
पूर्ण

अटल अंतरभूत u16 msg_grp_bc_acked(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 9, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_grp_bc_acked(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 9, 16, 0xffff, n);
पूर्ण

अटल अंतरभूत u16 msg_grp_remitted(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 9, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_grp_remitted(काष्ठा tipc_msg *m, u16 n)
अणु
	msg_set_bits(m, 9, 16, 0xffff, n);
पूर्ण

/* Word 10
 */
अटल अंतरभूत u16 msg_grp_evt(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 10, 0, 0x3);
पूर्ण

अटल अंतरभूत व्योम msg_set_grp_evt(काष्ठा tipc_msg *m, पूर्णांक n)
अणु
	msg_set_bits(m, 10, 0, 0x3, n);
पूर्ण

अटल अंतरभूत u16 msg_grp_bc_ack_req(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 10, 0, 0x1);
पूर्ण

अटल अंतरभूत व्योम msg_set_grp_bc_ack_req(काष्ठा tipc_msg *m, bool n)
अणु
	msg_set_bits(m, 10, 0, 0x1, n);
पूर्ण

अटल अंतरभूत u16 msg_grp_bc_seqno(काष्ठा tipc_msg *m)
अणु
	वापस msg_bits(m, 10, 16, 0xffff);
पूर्ण

अटल अंतरभूत व्योम msg_set_grp_bc_seqno(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_bits(m, 10, 16, 0xffff, n);
पूर्ण

अटल अंतरभूत bool msg_peer_link_is_up(काष्ठा tipc_msg *m)
अणु
	अगर (likely(msg_user(m) != LINK_PROTOCOL))
		वापस true;
	अगर (msg_type(m) == STATE_MSG)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool msg_peer_node_is_up(काष्ठा tipc_msg *m)
अणु
	अगर (msg_peer_link_is_up(m))
		वापस true;
	वापस msg_redundant_link(m);
पूर्ण

अटल अंतरभूत bool msg_is_reset(काष्ठा tipc_msg *hdr)
अणु
	वापस (msg_user(hdr) == LINK_PROTOCOL) && (msg_type(hdr) == RESET_MSG);
पूर्ण

/* Word 13
 */
अटल अंतरभूत व्योम msg_set_peer_net_hash(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_word(m, 13, n);
पूर्ण

अटल अंतरभूत u32 msg_peer_net_hash(काष्ठा tipc_msg *m)
अणु
	वापस msg_word(m, 13);
पूर्ण

/* Word 14
 */
अटल अंतरभूत u32 msg_sugg_node_addr(काष्ठा tipc_msg *m)
अणु
	वापस msg_word(m, 14);
पूर्ण

अटल अंतरभूत व्योम msg_set_sugg_node_addr(काष्ठा tipc_msg *m, u32 n)
अणु
	msg_set_word(m, 14, n);
पूर्ण

अटल अंतरभूत व्योम msg_set_node_id(काष्ठा tipc_msg *hdr, u8 *id)
अणु
	स_नकल(msg_data(hdr), id, 16);
पूर्ण

अटल अंतरभूत u8 *msg_node_id(काष्ठा tipc_msg *hdr)
अणु
	वापस (u8 *)msg_data(hdr);
पूर्ण

काष्ठा sk_buff *tipc_buf_acquire(u32 size, gfp_t gfp);
bool tipc_msg_validate(काष्ठा sk_buff **_skb);
bool tipc_msg_reverse(u32 own_addr, काष्ठा sk_buff **skb, पूर्णांक err);
व्योम tipc_skb_reject(काष्ठा net *net, पूर्णांक err, काष्ठा sk_buff *skb,
		     काष्ठा sk_buff_head *xmitq);
व्योम tipc_msg_init(u32 own_addr, काष्ठा tipc_msg *m, u32 user, u32 type,
		   u32 hsize, u32 destnode);
काष्ठा sk_buff *tipc_msg_create(uपूर्णांक user, uपूर्णांक type, uपूर्णांक hdr_sz,
				uपूर्णांक data_sz, u32 dnode, u32 onode,
				u32 dport, u32 oport, पूर्णांक errcode);
पूर्णांक tipc_buf_append(काष्ठा sk_buff **headbuf, काष्ठा sk_buff **buf);
bool tipc_msg_try_bundle(काष्ठा sk_buff *tskb, काष्ठा sk_buff **skb, u32 mss,
			 u32 dnode, bool *new_bundle);
bool tipc_msg_extract(काष्ठा sk_buff *skb, काष्ठा sk_buff **iskb, पूर्णांक *pos);
पूर्णांक tipc_msg_fragment(काष्ठा sk_buff *skb, स्थिर काष्ठा tipc_msg *hdr,
		      पूर्णांक pkपंचांगax, काष्ठा sk_buff_head *frags);
पूर्णांक tipc_msg_build(काष्ठा tipc_msg *mhdr, काष्ठा msghdr *m,
		   पूर्णांक offset, पूर्णांक dsz, पूर्णांक mtu, काष्ठा sk_buff_head *list);
पूर्णांक tipc_msg_append(काष्ठा tipc_msg *hdr, काष्ठा msghdr *m, पूर्णांक dlen,
		    पूर्णांक mss, काष्ठा sk_buff_head *txq);
bool tipc_msg_lookup_dest(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक *err);
bool tipc_msg_assemble(काष्ठा sk_buff_head *list);
bool tipc_msg_reassemble(काष्ठा sk_buff_head *list, काष्ठा sk_buff_head *rcvq);
bool tipc_msg_pskb_copy(u32 dst, काष्ठा sk_buff_head *msg,
			काष्ठा sk_buff_head *cpy);
bool __tipc_skb_queue_sorted(काष्ठा sk_buff_head *list, u16 seqno,
			     काष्ठा sk_buff *skb);
bool tipc_msg_skb_clone(काष्ठा sk_buff_head *msg, काष्ठा sk_buff_head *cpy);

अटल अंतरभूत u16 buf_seqno(काष्ठा sk_buff *skb)
अणु
	वापस msg_seqno(buf_msg(skb));
पूर्ण

अटल अंतरभूत पूर्णांक buf_roundup_len(काष्ठा sk_buff *skb)
अणु
	वापस (skb->len / 1024 + 1) * 1024;
पूर्ण

/* tipc_skb_peek(): peek and reserve first buffer in list
 * @list: list to be peeked in
 * Returns poपूर्णांकer to first buffer in list, अगर any
 */
अटल अंतरभूत काष्ठा sk_buff *tipc_skb_peek(काष्ठा sk_buff_head *list,
					    spinlock_t *lock)
अणु
	काष्ठा sk_buff *skb;

	spin_lock_bh(lock);
	skb = skb_peek(list);
	अगर (skb)
		skb_get(skb);
	spin_unlock_bh(lock);
	वापस skb;
पूर्ण

/* tipc_skb_peek_port(): find a destination port, ignoring all destinations
 *                       up to and including 'filter'.
 * Note: ignoring previously tried destinations minimizes the risk of
 *       contention on the socket lock
 * @list: list to be peeked in
 * @filter: last destination to be ignored from search
 * Returns a destination port number, of applicable.
 */
अटल अंतरभूत u32 tipc_skb_peek_port(काष्ठा sk_buff_head *list, u32 filter)
अणु
	काष्ठा sk_buff *skb;
	u32 dport = 0;
	bool ignore = true;

	spin_lock_bh(&list->lock);
	skb_queue_walk(list, skb) अणु
		dport = msg_destport(buf_msg(skb));
		अगर (!filter || skb_queue_is_last(list, skb))
			अवरोध;
		अगर (dport == filter)
			ignore = false;
		अन्यथा अगर (!ignore)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&list->lock);
	वापस dport;
पूर्ण

/* tipc_skb_dequeue(): unlink first buffer with dest 'dport' from list
 * @list: list to be unlinked from
 * @dport: selection criteria क्रम buffer to unlink
 */
अटल अंतरभूत काष्ठा sk_buff *tipc_skb_dequeue(काष्ठा sk_buff_head *list,
					       u32 dport)
अणु
	काष्ठा sk_buff *_skb, *पंचांगp, *skb = शून्य;

	spin_lock_bh(&list->lock);
	skb_queue_walk_safe(list, _skb, पंचांगp) अणु
		अगर (msg_destport(buf_msg(_skb)) == dport) अणु
			__skb_unlink(_skb, list);
			skb = _skb;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&list->lock);
	वापस skb;
पूर्ण

/* tipc_skb_queue_splice_tail - append an skb list to lock रक्षित list
 * @list: the new list to append. Not lock रक्षित
 * @head: target list. Lock रक्षित.
 */
अटल अंतरभूत व्योम tipc_skb_queue_splice_tail(काष्ठा sk_buff_head *list,
					      काष्ठा sk_buff_head *head)
अणु
	spin_lock_bh(&head->lock);
	skb_queue_splice_tail(list, head);
	spin_unlock_bh(&head->lock);
पूर्ण

/* tipc_skb_queue_splice_tail_init - merge two lock रक्षित skb lists
 * @list: the new list to add. Lock रक्षित. Will be reinitialized
 * @head: target list. Lock रक्षित.
 */
अटल अंतरभूत व्योम tipc_skb_queue_splice_tail_init(काष्ठा sk_buff_head *list,
						   काष्ठा sk_buff_head *head)
अणु
	काष्ठा sk_buff_head पंचांगp;

	__skb_queue_head_init(&पंचांगp);

	spin_lock_bh(&list->lock);
	skb_queue_splice_tail_init(list, &पंचांगp);
	spin_unlock_bh(&list->lock);
	tipc_skb_queue_splice_tail(&पंचांगp, head);
पूर्ण

/* __tipc_skb_dequeue() - dequeue the head skb according to expected seqno
 * @list: list to be dequeued from
 * @seqno: seqno of the expected msg
 *
 * वापसs skb dequeued from the list अगर its seqno is less than or equal to
 * the expected one, otherwise the skb is still hold
 *
 * Note: must be used with appropriate locks held only
 */
अटल अंतरभूत काष्ठा sk_buff *__tipc_skb_dequeue(काष्ठा sk_buff_head *list,
						 u16 seqno)
अणु
	काष्ठा sk_buff *skb = skb_peek(list);

	अगर (skb && less_eq(buf_seqno(skb), seqno)) अणु
		__skb_unlink(skb, list);
		वापस skb;
	पूर्ण
	वापस शून्य;
पूर्ण

#पूर्ण_अगर
