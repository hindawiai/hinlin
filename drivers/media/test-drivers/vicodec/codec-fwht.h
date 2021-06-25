<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ */
/*
 * Copyright 2016 Tom aan de Wiel
 * Copyright 2018 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित CODEC_FWHT_H
#घोषणा CODEC_FWHT_H

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/byteorder.h>

/*
 * The compressed क्रमmat consists of a fwht_cframe_hdr काष्ठा followed by the
 * compressed frame data. The header contains the size of that data.
 * Each Y, Cb and Cr plane is compressed separately. If the compressed
 * size of each plane becomes larger than the uncompressed size, then
 * that plane is stored uncompressed and the corresponding bit is set
 * in the flags field of the header.
 *
 * Each compressed plane consists of macroblocks and each macroblock
 * is run-length-encoded. Each macroblock starts with a 16 bit value.
 * Bit 15 indicates अगर this is a P-coded macroblock (1) or not (0).
 * P-coded macroblocks contain a delta against the previous frame.
 *
 * Bits 1-12 contain a number. If non-zero, then this same macroblock
 * repeats that number of बार. This results in a high degree of
 * compression क्रम generated images like colorbars.
 *
 * Following this macroblock header the MB coefficients are run-length
 * encoded: the top 12 bits contain the coefficient, the bottom 4 bits
 * tell how many बार this coefficient occurs. The value 0xf indicates
 * that the reमुख्यder of the macroblock should be filled with zeroes.
 *
 * All 16 and 32 bit values are stored in big-endian (network) order.
 *
 * Each fwht_cframe_hdr starts with an 8 byte magic header that is
 * guaranteed not to occur in the compressed frame data. This header
 * can be used to sync to the next frame.
 *
 * This codec uses the Fast Walsh Hadamard Transक्रमm. Tom aan de Wiel
 * developed this as part of a university project, specअगरically क्रम use
 * with this driver. His project report can be found here:
 *
 * https://hverkuil.home.xs4all.nl/fwht.pdf
 */

/*
 * This is a sequence of 8 bytes with the low 4 bits set to 0xf.
 *
 * This sequence cannot occur in the encoded data
 *
 * Note that these two magic values are symmetrical so endian issues here.
 */
#घोषणा FWHT_MAGIC1 0x4f4f4f4f
#घोषणा FWHT_MAGIC2 0xffffffff

/*
 * A macro to calculate the needed padding in order to make sure
 * both luma and chroma components resolutions are rounded up to
 * a multiple of 8
 */
#घोषणा vic_round_dim(dim, भाग) (round_up((dim) / (भाग), 8) * (भाग))

काष्ठा fwht_cframe_hdr अणु
	u32 magic1;
	u32 magic2;
	__be32 version;
	__be32 width, height;
	__be32 flags;
	__be32 colorspace;
	__be32 xfer_func;
	__be32 ycbcr_enc;
	__be32 quantization;
	__be32 size;
पूर्ण;

काष्ठा fwht_cframe अणु
	u16 i_frame_qp;
	u16 p_frame_qp;
	__be16 *rlc_data;
	s16 coeffs[8 * 8];
	s16 de_coeffs[8 * 8];
	s16 de_fwht[8 * 8];
	u32 size;
पूर्ण;

काष्ठा fwht_raw_frame अणु
	अचिन्हित पूर्णांक width_भाग;
	अचिन्हित पूर्णांक height_भाग;
	अचिन्हित पूर्णांक luma_alpha_step;
	अचिन्हित पूर्णांक chroma_step;
	अचिन्हित पूर्णांक components_num;
	u8 *buf;
	u8 *luma, *cb, *cr, *alpha;
पूर्ण;

#घोषणा FWHT_FRAME_PCODED	BIT(0)
#घोषणा FWHT_FRAME_UNENCODED	BIT(1)
#घोषणा FWHT_LUMA_UNENCODED	BIT(2)
#घोषणा FWHT_CB_UNENCODED	BIT(3)
#घोषणा FWHT_CR_UNENCODED	BIT(4)
#घोषणा FWHT_ALPHA_UNENCODED	BIT(5)

u32 fwht_encode_frame(काष्ठा fwht_raw_frame *frm,
		      काष्ठा fwht_raw_frame *ref_frm,
		      काष्ठा fwht_cframe *cf,
		      bool is_पूर्णांकra, bool next_is_पूर्णांकra,
		      अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
		      अचिन्हित पूर्णांक stride, अचिन्हित पूर्णांक chroma_stride);
bool fwht_decode_frame(काष्ठा fwht_cframe *cf, u32 hdr_flags,
		अचिन्हित पूर्णांक components_num, अचिन्हित पूर्णांक width,
		अचिन्हित पूर्णांक height, स्थिर काष्ठा fwht_raw_frame *ref,
		अचिन्हित पूर्णांक ref_stride, अचिन्हित पूर्णांक ref_chroma_stride,
		काष्ठा fwht_raw_frame *dst, अचिन्हित पूर्णांक dst_stride,
		अचिन्हित पूर्णांक dst_chroma_stride);
#पूर्ण_अगर
