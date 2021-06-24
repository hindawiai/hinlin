<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NVMe over Fabrics TCP protocol header.
 * Copyright (c) 2018 Lightbits Lअसल. All rights reserved.
 */

#अगर_अघोषित _LINUX_NVME_TCP_H
#घोषणा _LINUX_NVME_TCP_H

#समावेश <linux/nvme.h>

#घोषणा NVME_TCP_DISC_PORT	8009
#घोषणा NVME_TCP_ADMIN_CCSZ	SZ_8K
#घोषणा NVME_TCP_DIGEST_LENGTH	4

क्रमागत nvme_tcp_pfv अणु
	NVME_TCP_PFV_1_0 = 0x0,
पूर्ण;

क्रमागत nvme_tcp_fatal_error_status अणु
	NVME_TCP_FES_INVALID_PDU_HDR		= 0x01,
	NVME_TCP_FES_PDU_SEQ_ERR		= 0x02,
	NVME_TCP_FES_HDR_DIGEST_ERR		= 0x03,
	NVME_TCP_FES_DATA_OUT_OF_RANGE		= 0x04,
	NVME_TCP_FES_R2T_LIMIT_EXCEEDED		= 0x05,
	NVME_TCP_FES_DATA_LIMIT_EXCEEDED	= 0x05,
	NVME_TCP_FES_UNSUPPORTED_PARAM		= 0x06,
पूर्ण;

क्रमागत nvme_tcp_digest_option अणु
	NVME_TCP_HDR_DIGEST_ENABLE	= (1 << 0),
	NVME_TCP_DATA_DIGEST_ENABLE	= (1 << 1),
पूर्ण;

क्रमागत nvme_tcp_pdu_type अणु
	nvme_tcp_icreq		= 0x0,
	nvme_tcp_icresp		= 0x1,
	nvme_tcp_h2c_term	= 0x2,
	nvme_tcp_c2h_term	= 0x3,
	nvme_tcp_cmd		= 0x4,
	nvme_tcp_rsp		= 0x5,
	nvme_tcp_h2c_data	= 0x6,
	nvme_tcp_c2h_data	= 0x7,
	nvme_tcp_r2t		= 0x9,
पूर्ण;

क्रमागत nvme_tcp_pdu_flags अणु
	NVME_TCP_F_HDGST		= (1 << 0),
	NVME_TCP_F_DDGST		= (1 << 1),
	NVME_TCP_F_DATA_LAST		= (1 << 2),
	NVME_TCP_F_DATA_SUCCESS		= (1 << 3),
पूर्ण;

/**
 * काष्ठा nvme_tcp_hdr - nvme tcp pdu common header
 *
 * @type:          pdu type
 * @flags:         pdu specअगरic flags
 * @hlen:          pdu header length
 * @pकरो:           pdu data offset
 * @plen:          pdu wire byte length
 */
काष्ठा nvme_tcp_hdr अणु
	__u8	type;
	__u8	flags;
	__u8	hlen;
	__u8	pकरो;
	__le32	plen;
पूर्ण;

/**
 * काष्ठा nvme_tcp_icreq_pdu - nvme tcp initialize connection request pdu
 *
 * @hdr:           pdu generic header
 * @pfv:           pdu version क्रमmat
 * @hpda:          host pdu data alignment (dwords, 0's based)
 * @digest:        digest types enabled
 * @maxr2t:        maximum r2ts per request supported
 */
काष्ठा nvme_tcp_icreq_pdu अणु
	काष्ठा nvme_tcp_hdr	hdr;
	__le16			pfv;
	__u8			hpda;
	__u8			digest;
	__le32			maxr2t;
	__u8			rsvd2[112];
पूर्ण;

/**
 * काष्ठा nvme_tcp_icresp_pdu - nvme tcp initialize connection response pdu
 *
 * @hdr:           pdu common header
 * @pfv:           pdu version क्रमmat
 * @cpda:          controller pdu data alignment (करोwrds, 0's based)
 * @digest:        digest types enabled
 * @maxdata:       maximum data capsules per r2t supported
 */
काष्ठा nvme_tcp_icresp_pdu अणु
	काष्ठा nvme_tcp_hdr	hdr;
	__le16			pfv;
	__u8			cpda;
	__u8			digest;
	__le32			maxdata;
	__u8			rsvd[112];
पूर्ण;

/**
 * काष्ठा nvme_tcp_term_pdu - nvme tcp terminate connection pdu
 *
 * @hdr:           pdu common header
 * @fes:           fatal error status
 * @fei:           fatal error inक्रमmation
 */
काष्ठा nvme_tcp_term_pdu अणु
	काष्ठा nvme_tcp_hdr	hdr;
	__le16			fes;
	__le32			fei;
	__u8			rsvd[8];
पूर्ण;

/**
 * काष्ठा nvme_tcp_cmd_pdu - nvme tcp command capsule pdu
 *
 * @hdr:           pdu common header
 * @cmd:           nvme command
 */
काष्ठा nvme_tcp_cmd_pdu अणु
	काष्ठा nvme_tcp_hdr	hdr;
	काष्ठा nvme_command	cmd;
पूर्ण;

/**
 * काष्ठा nvme_tcp_rsp_pdu - nvme tcp response capsule pdu
 *
 * @hdr:           pdu common header
 * @hdr:           nvme-tcp generic header
 * @cqe:           nvme completion queue entry
 */
काष्ठा nvme_tcp_rsp_pdu अणु
	काष्ठा nvme_tcp_hdr	hdr;
	काष्ठा nvme_completion	cqe;
पूर्ण;

/**
 * काष्ठा nvme_tcp_r2t_pdu - nvme tcp पढ़ोy-to-transfer pdu
 *
 * @hdr:           pdu common header
 * @command_id:    nvme command identअगरier which this relates to
 * @ttag:          transfer tag (controller generated)
 * @r2t_offset:    offset from the start of the command data
 * @r2t_length:    length the host is allowed to send
 */
काष्ठा nvme_tcp_r2t_pdu अणु
	काष्ठा nvme_tcp_hdr	hdr;
	__u16			command_id;
	__u16			ttag;
	__le32			r2t_offset;
	__le32			r2t_length;
	__u8			rsvd[4];
पूर्ण;

/**
 * काष्ठा nvme_tcp_data_pdu - nvme tcp data pdu
 *
 * @hdr:           pdu common header
 * @command_id:    nvme command identअगरier which this relates to
 * @ttag:          transfer tag (controller generated)
 * @data_offset:   offset from the start of the command data
 * @data_length:   length of the data stream
 */
काष्ठा nvme_tcp_data_pdu अणु
	काष्ठा nvme_tcp_hdr	hdr;
	__u16			command_id;
	__u16			ttag;
	__le32			data_offset;
	__le32			data_length;
	__u8			rsvd[4];
पूर्ण;

जोड़ nvme_tcp_pdu अणु
	काष्ठा nvme_tcp_icreq_pdu	icreq;
	काष्ठा nvme_tcp_icresp_pdu	icresp;
	काष्ठा nvme_tcp_cmd_pdu		cmd;
	काष्ठा nvme_tcp_rsp_pdu		rsp;
	काष्ठा nvme_tcp_r2t_pdu		r2t;
	काष्ठा nvme_tcp_data_pdu	data;
पूर्ण;

#पूर्ण_अगर /* _LINUX_NVME_TCP_H */
