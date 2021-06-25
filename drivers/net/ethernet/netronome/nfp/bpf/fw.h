<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#अगर_अघोषित NFP_BPF_FW_H
#घोषणा NFP_BPF_FW_H 1

#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश "../ccm.h"

/* Kernel's क्रमागत bpf_reg_type is not uABI so people may change it अवरोधing
 * our FW ABI.  In that हाल we will करो translation in the driver.
 */
#घोषणा NFP_BPF_SCALAR_VALUE		1
#घोषणा NFP_BPF_MAP_VALUE		4
#घोषणा NFP_BPF_STACK			6
#घोषणा NFP_BPF_PACKET_DATA		8

क्रमागत bpf_cap_tlv_type अणु
	NFP_BPF_CAP_TYPE_FUNC		= 1,
	NFP_BPF_CAP_TYPE_ADJUST_HEAD	= 2,
	NFP_BPF_CAP_TYPE_MAPS		= 3,
	NFP_BPF_CAP_TYPE_RANDOM		= 4,
	NFP_BPF_CAP_TYPE_QUEUE_SELECT	= 5,
	NFP_BPF_CAP_TYPE_ADJUST_TAIL	= 6,
	NFP_BPF_CAP_TYPE_ABI_VERSION	= 7,
	NFP_BPF_CAP_TYPE_CMSG_MULTI_ENT	= 8,
पूर्ण;

काष्ठा nfp_bpf_cap_tlv_func अणु
	__le32 func_id;
	__le32 func_addr;
पूर्ण;

काष्ठा nfp_bpf_cap_tlv_adjust_head अणु
	__le32 flags;
	__le32 off_min;
	__le32 off_max;
	__le32 guaranteed_sub;
	__le32 guaranteed_add;
पूर्ण;

#घोषणा NFP_BPF_ADJUST_HEAD_NO_META	BIT(0)

काष्ठा nfp_bpf_cap_tlv_maps अणु
	__le32 types;
	__le32 max_maps;
	__le32 max_elems;
	__le32 max_key_sz;
	__le32 max_val_sz;
	__le32 max_elem_sz;
पूर्ण;

/*
 * Types defined क्रम map related control messages
 */

/* BPF ABIv2 fixed-length control message fields */
#घोषणा CMSG_MAP_KEY_LW			16
#घोषणा CMSG_MAP_VALUE_LW		16

क्रमागत nfp_bpf_cmsg_status अणु
	CMSG_RC_SUCCESS			= 0,
	CMSG_RC_ERR_MAP_FD		= 1,
	CMSG_RC_ERR_MAP_NOENT		= 2,
	CMSG_RC_ERR_MAP_ERR		= 3,
	CMSG_RC_ERR_MAP_PARSE		= 4,
	CMSG_RC_ERR_MAP_EXIST		= 5,
	CMSG_RC_ERR_MAP_NOMEM		= 6,
	CMSG_RC_ERR_MAP_E2BIG		= 7,
पूर्ण;

काष्ठा cmsg_reply_map_simple अणु
	काष्ठा nfp_ccm_hdr hdr;
	__be32 rc;
पूर्ण;

काष्ठा cmsg_req_map_alloc_tbl अणु
	काष्ठा nfp_ccm_hdr hdr;
	__be32 key_size;		/* in bytes */
	__be32 value_size;		/* in bytes */
	__be32 max_entries;
	__be32 map_type;
	__be32 map_flags;		/* reserved */
पूर्ण;

काष्ठा cmsg_reply_map_alloc_tbl अणु
	काष्ठा cmsg_reply_map_simple reply_hdr;
	__be32 tid;
पूर्ण;

काष्ठा cmsg_req_map_मुक्त_tbl अणु
	काष्ठा nfp_ccm_hdr hdr;
	__be32 tid;
पूर्ण;

काष्ठा cmsg_reply_map_मुक्त_tbl अणु
	काष्ठा cmsg_reply_map_simple reply_hdr;
	__be32 count;
पूर्ण;

काष्ठा cmsg_req_map_op अणु
	काष्ठा nfp_ccm_hdr hdr;
	__be32 tid;
	__be32 count;
	__be32 flags;
	u8 data[];
पूर्ण;

काष्ठा cmsg_reply_map_op अणु
	काष्ठा cmsg_reply_map_simple reply_hdr;
	__be32 count;
	__be32 resv;
	u8 data[];
पूर्ण;

काष्ठा cmsg_bpf_event अणु
	काष्ठा nfp_ccm_hdr hdr;
	__be32 cpu_id;
	__be64 map_ptr;
	__be32 data_size;
	__be32 pkt_size;
	u8 data[];
पूर्ण;
#पूर्ण_अगर
