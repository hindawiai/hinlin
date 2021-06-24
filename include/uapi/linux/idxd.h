<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* Copyright(c) 2019 Intel Corporation. All rights rsvd. */
#अगर_अघोषित _USR_IDXD_H_
#घोषणा _USR_IDXD_H_

#अगर_घोषित __KERNEL__
#समावेश <linux/types.h>
#अन्यथा
#समावेश <मानक_निवेशt.h>
#पूर्ण_अगर

/* Descriptor flags */
#घोषणा IDXD_OP_FLAG_FENCE	0x0001
#घोषणा IDXD_OP_FLAG_BOF	0x0002
#घोषणा IDXD_OP_FLAG_CRAV	0x0004
#घोषणा IDXD_OP_FLAG_RCR	0x0008
#घोषणा IDXD_OP_FLAG_RCI	0x0010
#घोषणा IDXD_OP_FLAG_CRSTS	0x0020
#घोषणा IDXD_OP_FLAG_CR		0x0080
#घोषणा IDXD_OP_FLAG_CC		0x0100
#घोषणा IDXD_OP_FLAG_ADDR1_TCS	0x0200
#घोषणा IDXD_OP_FLAG_ADDR2_TCS	0x0400
#घोषणा IDXD_OP_FLAG_ADDR3_TCS	0x0800
#घोषणा IDXD_OP_FLAG_CR_TCS	0x1000
#घोषणा IDXD_OP_FLAG_STORD	0x2000
#घोषणा IDXD_OP_FLAG_DRDBK	0x4000
#घोषणा IDXD_OP_FLAG_DSTS	0x8000

/* IAX */
#घोषणा IDXD_OP_FLAG_RD_SRC2_AECS	0x010000

/* Opcode */
क्रमागत dsa_opcode अणु
	DSA_OPCODE_NOOP = 0,
	DSA_OPCODE_BATCH,
	DSA_OPCODE_DRAIN,
	DSA_OPCODE_MEMMOVE,
	DSA_OPCODE_MEMFILL,
	DSA_OPCODE_COMPARE,
	DSA_OPCODE_COMPVAL,
	DSA_OPCODE_CR_DELTA,
	DSA_OPCODE_AP_DELTA,
	DSA_OPCODE_DUALCAST,
	DSA_OPCODE_CRCGEN = 0x10,
	DSA_OPCODE_COPY_CRC,
	DSA_OPCODE_DIF_CHECK,
	DSA_OPCODE_DIF_INS,
	DSA_OPCODE_DIF_STRP,
	DSA_OPCODE_DIF_UPDT,
	DSA_OPCODE_CFLUSH = 0x20,
पूर्ण;

क्रमागत iax_opcode अणु
	IAX_OPCODE_NOOP = 0,
	IAX_OPCODE_DRAIN = 2,
	IAX_OPCODE_MEMMOVE,
	IAX_OPCODE_DECOMPRESS = 0x42,
	IAX_OPCODE_COMPRESS,
पूर्ण;

/* Completion record status */
क्रमागत dsa_completion_status अणु
	DSA_COMP_NONE = 0,
	DSA_COMP_SUCCESS,
	DSA_COMP_SUCCESS_PRED,
	DSA_COMP_PAGE_FAULT_NOBOF,
	DSA_COMP_PAGE_FAULT_IR,
	DSA_COMP_BATCH_FAIL,
	DSA_COMP_BATCH_PAGE_FAULT,
	DSA_COMP_DR_OFFSET_NOINC,
	DSA_COMP_DR_OFFSET_दुस्फल,
	DSA_COMP_DIF_ERR,
	DSA_COMP_BAD_OPCODE = 0x10,
	DSA_COMP_INVALID_FLAGS,
	DSA_COMP_NOZERO_RESERVE,
	DSA_COMP_XFER_दुस्फल,
	DSA_COMP_DESC_CNT_दुस्फल,
	DSA_COMP_DR_दुस्फल,
	DSA_COMP_OVERLAP_BUFFERS,
	DSA_COMP_DCAST_ERR,
	DSA_COMP_DESCLIST_ALIGN,
	DSA_COMP_INT_HANDLE_INVAL,
	DSA_COMP_CRA_XLAT,
	DSA_COMP_CRA_ALIGN,
	DSA_COMP_ADDR_ALIGN,
	DSA_COMP_PRIV_BAD,
	DSA_COMP_TRAFFIC_CLASS_CONF,
	DSA_COMP_PFAULT_RDBA,
	DSA_COMP_HW_ERR1,
	DSA_COMP_HW_ERR_DRB,
	DSA_COMP_TRANSLATION_FAIL,
पूर्ण;

क्रमागत iax_completion_status अणु
	IAX_COMP_NONE = 0,
	IAX_COMP_SUCCESS,
	IAX_COMP_PAGE_FAULT_IR = 0x04,
	IAX_COMP_OUTBUF_OVERFLOW,
	IAX_COMP_BAD_OPCODE = 0x10,
	IAX_COMP_INVALID_FLAGS,
	IAX_COMP_NOZERO_RESERVE,
	IAX_COMP_INVALID_SIZE,
	IAX_COMP_OVERLAP_BUFFERS = 0x16,
	IAX_COMP_INT_HANDLE_INVAL = 0x19,
	IAX_COMP_CRA_XLAT,
	IAX_COMP_CRA_ALIGN,
	IAX_COMP_ADDR_ALIGN,
	IAX_COMP_PRIV_BAD,
	IAX_COMP_TRAFFIC_CLASS_CONF,
	IAX_COMP_PFAULT_RDBA,
	IAX_COMP_HW_ERR1,
	IAX_COMP_HW_ERR_DRB,
	IAX_COMP_TRANSLATION_FAIL,
	IAX_COMP_PRS_TIMEOUT,
	IAX_COMP_WATCHDOG,
	IAX_COMP_INVALID_COMP_FLAG = 0x30,
	IAX_COMP_INVALID_FILTER_FLAG,
	IAX_COMP_INVALID_NUM_ELEMS = 0x33,
पूर्ण;

#घोषणा DSA_COMP_STATUS_MASK		0x7f
#घोषणा DSA_COMP_STATUS_WRITE		0x80

काष्ठा dsa_hw_desc अणु
	uपूर्णांक32_t	pasid:20;
	uपूर्णांक32_t	rsvd:11;
	uपूर्णांक32_t	priv:1;
	uपूर्णांक32_t	flags:24;
	uपूर्णांक32_t	opcode:8;
	uपूर्णांक64_t	completion_addr;
	जोड़ अणु
		uपूर्णांक64_t	src_addr;
		uपूर्णांक64_t	rdback_addr;
		uपूर्णांक64_t	pattern;
		uपूर्णांक64_t	desc_list_addr;
	पूर्ण;
	जोड़ अणु
		uपूर्णांक64_t	dst_addr;
		uपूर्णांक64_t	rdback_addr2;
		uपूर्णांक64_t	src2_addr;
		uपूर्णांक64_t	comp_pattern;
	पूर्ण;
	जोड़ अणु
		uपूर्णांक32_t	xfer_size;
		uपूर्णांक32_t	desc_count;
	पूर्ण;
	uपूर्णांक16_t	पूर्णांक_handle;
	uपूर्णांक16_t	rsvd1;
	जोड़ अणु
		uपूर्णांक8_t		expected_res;
		/* create delta record */
		काष्ठा अणु
			uपूर्णांक64_t	delta_addr;
			uपूर्णांक32_t	max_delta_size;
			uपूर्णांक32_t 	delt_rsvd;
			uपूर्णांक8_t 	expected_res_mask;
		पूर्ण;
		uपूर्णांक32_t	delta_rec_size;
		uपूर्णांक64_t	dest2;
		/* CRC */
		काष्ठा अणु
			uपूर्णांक32_t	crc_seed;
			uपूर्णांक32_t	crc_rsvd;
			uपूर्णांक64_t	seed_addr;
		पूर्ण;
		/* DIF check or strip */
		काष्ठा अणु
			uपूर्णांक8_t		src_dअगर_flags;
			uपूर्णांक8_t		dअगर_chk_res;
			uपूर्णांक8_t		dअगर_chk_flags;
			uपूर्णांक8_t		dअगर_chk_res2[5];
			uपूर्णांक32_t	chk_ref_tag_seed;
			uपूर्णांक16_t	chk_app_tag_mask;
			uपूर्णांक16_t	chk_app_tag_seed;
		पूर्ण;
		/* DIF insert */
		काष्ठा अणु
			uपूर्णांक8_t		dअगर_ins_res;
			uपूर्णांक8_t		dest_dअगर_flag;
			uपूर्णांक8_t		dअगर_ins_flags;
			uपूर्णांक8_t		dअगर_ins_res2[13];
			uपूर्णांक32_t	ins_ref_tag_seed;
			uपूर्णांक16_t	ins_app_tag_mask;
			uपूर्णांक16_t	ins_app_tag_seed;
		पूर्ण;
		/* DIF update */
		काष्ठा अणु
			uपूर्णांक8_t		src_upd_flags;
			uपूर्णांक8_t		upd_dest_flags;
			uपूर्णांक8_t		dअगर_upd_flags;
			uपूर्णांक8_t		dअगर_upd_res[5];
			uपूर्णांक32_t	src_ref_tag_seed;
			uपूर्णांक16_t	src_app_tag_mask;
			uपूर्णांक16_t	src_app_tag_seed;
			uपूर्णांक32_t	dest_ref_tag_seed;
			uपूर्णांक16_t	dest_app_tag_mask;
			uपूर्णांक16_t	dest_app_tag_seed;
		पूर्ण;

		uपूर्णांक8_t		op_specअगरic[24];
	पूर्ण;
पूर्ण __attribute__((packed));

काष्ठा iax_hw_desc अणु
	uपूर्णांक32_t        pasid:20;
	uपूर्णांक32_t        rsvd:11;
	uपूर्णांक32_t        priv:1;
	uपूर्णांक32_t        flags:24;
	uपूर्णांक32_t        opcode:8;
	uपूर्णांक64_t        completion_addr;
	uपूर्णांक64_t        src1_addr;
	uपूर्णांक64_t        dst_addr;
	uपूर्णांक32_t        src1_size;
	uपूर्णांक16_t        पूर्णांक_handle;
	जोड़ अणु
		uपूर्णांक16_t        compr_flags;
		uपूर्णांक16_t        decompr_flags;
	पूर्ण;
	uपूर्णांक64_t        src2_addr;
	uपूर्णांक32_t        max_dst_size;
	uपूर्णांक32_t        src2_size;
	uपूर्णांक32_t	filter_flags;
	uपूर्णांक32_t	num_inमाला_दो;
पूर्ण __attribute__((packed));

काष्ठा dsa_raw_desc अणु
	uपूर्णांक64_t	field[8];
पूर्ण __attribute__((packed));

/*
 * The status field will be modअगरied by hardware, thereक्रमe it should be
 * अस्थिर and prevent the compiler from optimize the पढ़ो.
 */
काष्ठा dsa_completion_record अणु
	अस्थिर uपूर्णांक8_t	status;
	जोड़ अणु
		uपूर्णांक8_t		result;
		uपूर्णांक8_t		dअगर_status;
	पूर्ण;
	uपूर्णांक16_t		rsvd;
	uपूर्णांक32_t		bytes_completed;
	uपूर्णांक64_t		fault_addr;
	जोड़ अणु
		/* common record */
		काष्ठा अणु
			uपूर्णांक32_t	invalid_flags:24;
			uपूर्णांक32_t	rsvd2:8;
		पूर्ण;

		uपूर्णांक32_t	delta_rec_size;
		uपूर्णांक32_t	crc_val;

		/* DIF check & strip */
		काष्ठा अणु
			uपूर्णांक32_t	dअगर_chk_ref_tag;
			uपूर्णांक16_t	dअगर_chk_app_tag_mask;
			uपूर्णांक16_t	dअगर_chk_app_tag;
		पूर्ण;

		/* DIF insert */
		काष्ठा अणु
			uपूर्णांक64_t	dअगर_ins_res;
			uपूर्णांक32_t	dअगर_ins_ref_tag;
			uपूर्णांक16_t	dअगर_ins_app_tag_mask;
			uपूर्णांक16_t	dअगर_ins_app_tag;
		पूर्ण;

		/* DIF update */
		काष्ठा अणु
			uपूर्णांक32_t	dअगर_upd_src_ref_tag;
			uपूर्णांक16_t	dअगर_upd_src_app_tag_mask;
			uपूर्णांक16_t	dअगर_upd_src_app_tag;
			uपूर्णांक32_t	dअगर_upd_dest_ref_tag;
			uपूर्णांक16_t	dअगर_upd_dest_app_tag_mask;
			uपूर्णांक16_t	dअगर_upd_dest_app_tag;
		पूर्ण;

		uपूर्णांक8_t		op_specअगरic[16];
	पूर्ण;
पूर्ण __attribute__((packed));

काष्ठा dsa_raw_completion_record अणु
	uपूर्णांक64_t	field[4];
पूर्ण __attribute__((packed));

काष्ठा iax_completion_record अणु
	अस्थिर uपूर्णांक8_t        status;
	uपूर्णांक8_t                 error_code;
	uपूर्णांक16_t                rsvd;
	uपूर्णांक32_t                bytes_completed;
	uपूर्णांक64_t                fault_addr;
	uपूर्णांक32_t                invalid_flags;
	uपूर्णांक32_t                rsvd2;
	uपूर्णांक32_t                output_size;
	uपूर्णांक8_t                 output_bits;
	uपूर्णांक8_t                 rsvd3;
	uपूर्णांक16_t                rsvd4;
	uपूर्णांक64_t                rsvd5[4];
पूर्ण __attribute__((packed));

काष्ठा iax_raw_completion_record अणु
	uपूर्णांक64_t	field[8];
पूर्ण __attribute__((packed));

#पूर्ण_अगर
