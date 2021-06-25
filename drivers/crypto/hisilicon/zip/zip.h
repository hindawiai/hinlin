<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019 HiSilicon Limited. */
#अगर_अघोषित HISI_ZIP_H
#घोषणा HISI_ZIP_H

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	"hisi_zip: " fmt

#समावेश <linux/list.h>
#समावेश "../qm.h"

क्रमागत hisi_zip_error_type अणु
	/* negative compression */
	HZIP_NC_ERR = 0x0d,
पूर्ण;

काष्ठा hisi_zip_dfx अणु
	atomic64_t send_cnt;
	atomic64_t recv_cnt;
	atomic64_t send_busy_cnt;
	atomic64_t err_bd_cnt;
पूर्ण;

काष्ठा hisi_zip_ctrl;

काष्ठा hisi_zip अणु
	काष्ठा hisi_qm qm;
	काष्ठा hisi_zip_ctrl *ctrl;
	काष्ठा hisi_zip_dfx dfx;
पूर्ण;

काष्ठा hisi_zip_sqe अणु
	u32 consumed;
	u32 produced;
	u32 comp_data_length;
	/*
	 * status: 0~7 bits
	 * rsvd: 8~31 bits
	 */
	u32 dw3;
	u32 input_data_length;
	u32 dw5;
	u32 dw6;
	/*
	 * in_sge_data_offset: 0~23 bits
	 * rsvd: 24~27 bits
	 * sqe_type: 29~31 bits
	 */
	u32 dw7;
	/*
	 * out_sge_data_offset: 0~23 bits
	 * rsvd: 24~31 bits
	 */
	u32 dw8;
	/*
	 * request_type: 0~7 bits
	 * buffer_type: 8~11 bits
	 * rsvd: 13~31 bits
	 */
	u32 dw9;
	u32 dw10;
	u32 dw11;
	u32 dw12;
	/* tag: in sqe type 0 */
	u32 dw13;
	u32 dest_avail_out;
	u32 dw15;
	u32 dw16;
	u32 dw17;
	u32 source_addr_l;
	u32 source_addr_h;
	u32 dest_addr_l;
	u32 dest_addr_h;
	u32 dw22;
	u32 dw23;
	u32 dw24;
	u32 dw25;
	/* tag: in sqe type 3 */
	u32 dw26;
	u32 dw27;
	u32 rsvd1[4];
पूर्ण;

पूर्णांक zip_create_qps(काष्ठा hisi_qp **qps, पूर्णांक ctx_num, पूर्णांक node);
पूर्णांक hisi_zip_रेजिस्टर_to_crypto(काष्ठा hisi_qm *qm);
व्योम hisi_zip_unरेजिस्टर_from_crypto(काष्ठा hisi_qm *qm);
#पूर्ण_अगर
