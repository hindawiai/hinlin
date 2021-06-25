<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR Linux-OpenIB) */
/*
 * Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित _RDMA_SIGNATURE_H_
#घोषणा _RDMA_SIGNATURE_H_

#समावेश <linux/types.h>

क्रमागत ib_signature_prot_cap अणु
	IB_PROT_T10DIF_TYPE_1 = 1,
	IB_PROT_T10DIF_TYPE_2 = 1 << 1,
	IB_PROT_T10DIF_TYPE_3 = 1 << 2,
पूर्ण;

क्रमागत ib_signature_guard_cap अणु
	IB_GUARD_T10DIF_CRC	= 1,
	IB_GUARD_T10DIF_CSUM	= 1 << 1,
पूर्ण;

/**
 * क्रमागत ib_signature_type - Signature types
 * @IB_SIG_TYPE_NONE: Unरक्षित.
 * @IB_SIG_TYPE_T10_DIF: Type T10-DIF
 */
क्रमागत ib_signature_type अणु
	IB_SIG_TYPE_NONE,
	IB_SIG_TYPE_T10_DIF,
पूर्ण;

/**
 * क्रमागत ib_t10_dअगर_bg_type - Signature T10-DIF block-guard types
 * @IB_T10DIF_CRC: Corresponds to T10-PI mandated CRC checksum rules.
 * @IB_T10DIF_CSUM: Corresponds to IP checksum rules.
 */
क्रमागत ib_t10_dअगर_bg_type अणु
	IB_T10DIF_CRC,
	IB_T10DIF_CSUM,
पूर्ण;

/**
 * काष्ठा ib_t10_dअगर_करोमुख्य - Parameters specअगरic क्रम T10-DIF
 *     करोमुख्य.
 * @bg_type: T10-DIF block guard type (CRC|CSUM)
 * @pi_पूर्णांकerval: protection inक्रमmation पूर्णांकerval.
 * @bg: seed of guard computation.
 * @app_tag: application tag of guard block
 * @ref_tag: initial guard block reference tag.
 * @ref_remap: Indicate wethear the reftag increments each block
 * @app_escape: Indicate to skip block check अगर apptag=0xffff
 * @ref_escape: Indicate to skip block check अगर reftag=0xffffffff
 * @apptag_check_mask: check biपंचांगask of application tag.
 */
काष्ठा ib_t10_dअगर_करोमुख्य अणु
	क्रमागत ib_t10_dअगर_bg_type bg_type;
	u16			pi_पूर्णांकerval;
	u16			bg;
	u16			app_tag;
	u32			ref_tag;
	bool			ref_remap;
	bool			app_escape;
	bool			ref_escape;
	u16			apptag_check_mask;
पूर्ण;

/**
 * काष्ठा ib_sig_करोमुख्य - Parameters क्रम signature करोमुख्य
 * @sig_type: specअगरic signauture type
 * @sig: जोड़ of all signature करोमुख्य attributes that may
 *     be used to set करोमुख्य layout.
 */
काष्ठा ib_sig_करोमुख्य अणु
	क्रमागत ib_signature_type sig_type;
	जोड़ अणु
		काष्ठा ib_t10_dअगर_करोमुख्य dअगर;
	पूर्ण sig;
पूर्ण;

/**
 * काष्ठा ib_sig_attrs - Parameters क्रम signature hanकरोver operation
 * @check_mask: biपंचांगask क्रम signature byte check (8 bytes)
 * @mem: memory करोमुख्य layout descriptor.
 * @wire: wire करोमुख्य layout descriptor.
 * @meta_length: metadata length
 */
काष्ठा ib_sig_attrs अणु
	u8			check_mask;
	काष्ठा ib_sig_करोमुख्य	mem;
	काष्ठा ib_sig_करोमुख्य	wire;
	पूर्णांक			meta_length;
पूर्ण;

क्रमागत ib_sig_err_type अणु
	IB_SIG_BAD_GUARD,
	IB_SIG_BAD_REFTAG,
	IB_SIG_BAD_APPTAG,
पूर्ण;

/*
 * Signature check masks (8 bytes in total) according to the T10-PI standard:
 *  -------- -------- ------------
 * | GUARD  | APPTAG |   REFTAG   |
 * |  2B    |  2B    |    4B      |
 *  -------- -------- ------------
 */
क्रमागत अणु
	IB_SIG_CHECK_GUARD = 0xc0,
	IB_SIG_CHECK_APPTAG = 0x30,
	IB_SIG_CHECK_REFTAG = 0x0f,
पूर्ण;

/*
 * काष्ठा ib_sig_err - signature error descriptor
 */
काष्ठा ib_sig_err अणु
	क्रमागत ib_sig_err_type	err_type;
	u32			expected;
	u32			actual;
	u64			sig_err_offset;
	u32			key;
पूर्ण;

#पूर्ण_अगर /* _RDMA_SIGNATURE_H_ */
