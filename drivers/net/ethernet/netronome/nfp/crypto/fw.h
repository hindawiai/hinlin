<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2019 Netronome Systems, Inc. */

#अगर_अघोषित NFP_CRYPTO_FW_H
#घोषणा NFP_CRYPTO_FW_H 1

#समावेश "../ccm.h"

#घोषणा NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_ENC	0
#घोषणा NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_DEC	1

काष्ठा nfp_net_tls_resync_req अणु
	__be32 fw_handle[2];
	__be32 tcp_seq;
	u8 l3_offset;
	u8 l4_offset;
	u8 resv[2];
पूर्ण;

काष्ठा nfp_crypto_reply_simple अणु
	काष्ठा nfp_ccm_hdr hdr;
	__be32 error;
पूर्ण;

काष्ठा nfp_crypto_req_reset अणु
	काष्ठा nfp_ccm_hdr hdr;
	__be32 ep_id;
पूर्ण;

#घोषणा NFP_NET_TLS_IPVER		GENMASK(15, 12)
#घोषणा NFP_NET_TLS_VLAN		GENMASK(11, 0)
#घोषणा NFP_NET_TLS_VLAN_UNUSED			4095

काष्ठा nfp_crypto_req_add_front अणु
	काष्ठा nfp_ccm_hdr hdr;
	__be32 ep_id;
	u8 resv[3];
	u8 opcode;
	u8 key_len;
	__be16 ipver_vlan __packed;
	u8 l4_proto;
#घोषणा NFP_NET_TLS_NON_ADDR_KEY_LEN	8
	u8 l3_addrs[];
पूर्ण;

काष्ठा nfp_crypto_req_add_back अणु
	__be16 src_port;
	__be16 dst_port;
	__be32 key[8];
	__be32 salt;
	__be32 iv[2];
	__be32 counter;
	__be32 rec_no[2];
	__be32 tcp_seq;
पूर्ण;

काष्ठा nfp_crypto_req_add_v4 अणु
	काष्ठा nfp_crypto_req_add_front front;
	__be32 src_ip;
	__be32 dst_ip;
	काष्ठा nfp_crypto_req_add_back back;
पूर्ण;

काष्ठा nfp_crypto_req_add_v6 अणु
	काष्ठा nfp_crypto_req_add_front front;
	__be32 src_ip[4];
	__be32 dst_ip[4];
	काष्ठा nfp_crypto_req_add_back back;
पूर्ण;

काष्ठा nfp_crypto_reply_add अणु
	काष्ठा nfp_ccm_hdr hdr;
	__be32 error;
	__be32 handle[2];
पूर्ण;

काष्ठा nfp_crypto_req_del अणु
	काष्ठा nfp_ccm_hdr hdr;
	__be32 ep_id;
	__be32 handle[2];
पूर्ण;

काष्ठा nfp_crypto_req_update अणु
	काष्ठा nfp_ccm_hdr hdr;
	__be32 ep_id;
	u8 resv[3];
	u8 opcode;
	__be32 handle[2];
	__be32 rec_no[2];
	__be32 tcp_seq;
पूर्ण;
#पूर्ण_अगर
