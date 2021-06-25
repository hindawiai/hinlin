<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 */

#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "vdec_helpers.h"
#समावेश "dos_regs.h"
#समावेश "codec_h264.h"

#घोषणा SIZE_EXT_FW	(20 * SZ_1K)
#घोषणा SIZE_WORKSPACE	0x1ee000
#घोषणा SIZE_SEI	(8 * SZ_1K)

/*
 * Offset added by the firmware which must be substracted
 * from the workspace phyaddr
 */
#घोषणा WORKSPACE_BUF_OFFSET	0x1000000

/* ISR status */
#घोषणा CMD_MASK		GENMASK(7, 0)
#घोषणा CMD_SRC_CHANGE		1
#घोषणा CMD_FRAMES_READY	2
#घोषणा CMD_FATAL_ERROR		6
#घोषणा CMD_BAD_WIDTH		7
#घोषणा CMD_BAD_HEIGHT		8

#घोषणा SEI_DATA_READY	BIT(15)

/* Picture type */
#घोषणा PIC_TOP_BOT	5
#घोषणा PIC_BOT_TOP	6

/* Size of Motion Vector per macroblock */
#घोषणा MB_MV_SIZE	96

/* Frame status data */
#घोषणा PIC_STRUCT_BIT	5
#घोषणा PIC_STRUCT_MASK	GENMASK(2, 0)
#घोषणा BUF_IDX_MASK	GENMASK(4, 0)
#घोषणा ERROR_FLAG	BIT(9)
#घोषणा OFFSET_BIT	16
#घोषणा OFFSET_MASK	GENMASK(15, 0)

/* Bitstream parsed data */
#घोषणा MB_TOTAL_BIT	8
#घोषणा MB_TOTAL_MASK	GENMASK(15, 0)
#घोषणा MB_WIDTH_MASK	GENMASK(7, 0)
#घोषणा MAX_REF_BIT	24
#घोषणा MAX_REF_MASK	GENMASK(6, 0)
#घोषणा AR_IDC_BIT	16
#घोषणा AR_IDC_MASK	GENMASK(7, 0)
#घोषणा AR_PRESENT_FLAG	BIT(0)
#घोषणा AR_EXTEND	0xff

/*
 * Buffer to send to the ESPARSER to संकेत End Of Stream क्रम H.264.
 * This is a 16x16 encoded picture that will trigger drain firmware-side.
 * There is no known alternative.
 */
अटल स्थिर u8 eos_sequence[SZ_4K] = अणु
	0x00, 0x00, 0x00, 0x01, 0x06, 0x05, 0xff, 0xe4, 0xdc, 0x45, 0xe9, 0xbd,
	0xe6, 0xd9, 0x48, 0xb7,	0x96, 0x2c, 0xd8, 0x20, 0xd9, 0x23, 0xee, 0xef,
	0x78, 0x32, 0x36, 0x34, 0x20, 0x2d, 0x20, 0x63,	0x6f, 0x72, 0x65, 0x20,
	0x36, 0x37, 0x20, 0x72, 0x31, 0x31, 0x33, 0x30, 0x20, 0x38, 0x34, 0x37,
	0x35, 0x39, 0x37, 0x37, 0x20, 0x2d, 0x20, 0x48, 0x2e, 0x32, 0x36, 0x34,
	0x2f, 0x4d, 0x50, 0x45,	0x47, 0x2d, 0x34, 0x20, 0x41, 0x56, 0x43, 0x20,
	0x63, 0x6f, 0x64, 0x65, 0x63, 0x20, 0x2d, 0x20,	0x43, 0x6f, 0x70, 0x79,
	0x6c, 0x65, 0x66, 0x74, 0x20, 0x32, 0x30, 0x30, 0x33, 0x2d, 0x32, 0x30,
	0x30, 0x39, 0x20, 0x2d, 0x20, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f,
	0x77, 0x77, 0x77, 0x2e,	0x76, 0x69, 0x64, 0x65, 0x6f, 0x6c, 0x61, 0x6e,
	0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x78, 0x32, 0x36,	0x34, 0x2e, 0x68, 0x74,
	0x6d, 0x6c, 0x20, 0x2d, 0x20, 0x6f, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x73,
	0x3a, 0x20, 0x63, 0x61, 0x62, 0x61, 0x63, 0x3d, 0x31, 0x20, 0x72, 0x65,
	0x66, 0x3d, 0x31, 0x20,	0x64, 0x65, 0x62, 0x6c, 0x6f, 0x63, 0x6b, 0x3d,
	0x31, 0x3a, 0x30, 0x3a, 0x30, 0x20, 0x61, 0x6e,	0x61, 0x6c, 0x79, 0x73,
	0x65, 0x3d, 0x30, 0x78, 0x31, 0x3a, 0x30, 0x78, 0x31, 0x31, 0x31, 0x20,
	0x6d, 0x65, 0x3d, 0x68, 0x65, 0x78, 0x20, 0x73, 0x75, 0x62, 0x6d, 0x65,
	0x3d, 0x36, 0x20, 0x70,	0x73, 0x79, 0x5f, 0x72, 0x64, 0x3d, 0x31, 0x2e,
	0x30, 0x3a, 0x30, 0x2e, 0x30, 0x20, 0x6d, 0x69,	0x78, 0x65, 0x64, 0x5f,
	0x72, 0x65, 0x66, 0x3d, 0x30, 0x20, 0x6d, 0x65, 0x5f, 0x72, 0x61, 0x6e,
	0x67, 0x65, 0x3d, 0x31, 0x36, 0x20, 0x63, 0x68, 0x72, 0x6f, 0x6d, 0x61,
	0x5f, 0x6d, 0x65, 0x3d,	0x31, 0x20, 0x74, 0x72, 0x65, 0x6c, 0x6c, 0x69,
	0x73, 0x3d, 0x30, 0x20, 0x38, 0x78, 0x38, 0x64,	0x63, 0x74, 0x3d, 0x30,
	0x20, 0x63, 0x71, 0x6d, 0x3d, 0x30, 0x20, 0x64, 0x65, 0x61, 0x64, 0x7a,
	0x6f, 0x6e, 0x65, 0x3d, 0x32, 0x31, 0x2c, 0x31, 0x31, 0x20, 0x63, 0x68,
	0x72, 0x6f, 0x6d, 0x61,	0x5f, 0x71, 0x70, 0x5f, 0x6f, 0x66, 0x66, 0x73,
	0x65, 0x74, 0x3d, 0x2d, 0x32, 0x20, 0x74, 0x68,	0x72, 0x65, 0x61, 0x64,
	0x73, 0x3d, 0x31, 0x20, 0x6e, 0x72, 0x3d, 0x30, 0x20, 0x64, 0x65, 0x63,
	0x69, 0x6d, 0x61, 0x74, 0x65, 0x3d, 0x31, 0x20, 0x6d, 0x62, 0x61, 0x66,
	0x66, 0x3d, 0x30, 0x20,	0x62, 0x66, 0x72, 0x61, 0x6d, 0x65, 0x73, 0x3d,
	0x30, 0x20, 0x6b, 0x65, 0x79, 0x69, 0x6e, 0x74,	0x3d, 0x32, 0x35, 0x30,
	0x20, 0x6b, 0x65, 0x79, 0x69, 0x6e, 0x74, 0x5f, 0x6d, 0x69, 0x6e, 0x3d,
	0x32, 0x35, 0x20, 0x73, 0x63, 0x65, 0x6e, 0x65, 0x63, 0x75, 0x74, 0x3d,
	0x34, 0x30, 0x20, 0x72,	0x63, 0x3d, 0x61, 0x62, 0x72, 0x20, 0x62, 0x69,
	0x74, 0x72, 0x61, 0x74, 0x65, 0x3d, 0x31, 0x30,	0x20, 0x72, 0x61, 0x74,
	0x65, 0x74, 0x6f, 0x6c, 0x3d, 0x31, 0x2e, 0x30, 0x20, 0x71, 0x63, 0x6f,
	0x6d, 0x70, 0x3d, 0x30, 0x2e, 0x36, 0x30, 0x20, 0x71, 0x70, 0x6d, 0x69,
	0x6e, 0x3d, 0x31, 0x30,	0x20, 0x71, 0x70, 0x6d, 0x61, 0x78, 0x3d, 0x35,
	0x31, 0x20, 0x71, 0x70, 0x73, 0x74, 0x65, 0x70,	0x3d, 0x34, 0x20, 0x69,
	0x70, 0x5f, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x3d, 0x31, 0x2e, 0x34, 0x30,
	0x20, 0x61, 0x71, 0x3d, 0x31, 0x3a, 0x31, 0x2e, 0x30, 0x30, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x01,	0x67, 0x4d, 0x40, 0x0a, 0x9a, 0x74, 0xf4, 0x20,
	0x00, 0x00, 0x03, 0x00, 0x20, 0x00, 0x00, 0x06,	0x51, 0xe2, 0x44, 0xd4,
	0x00, 0x00, 0x00, 0x01, 0x68, 0xee, 0x32, 0xc8, 0x00, 0x00, 0x00, 0x01,
	0x65, 0x88, 0x80, 0x20, 0x00, 0x08, 0x7f, 0xea, 0x6a, 0xe2, 0x99, 0xb6,
	0x57, 0xae, 0x49, 0x30,	0xf5, 0xfe, 0x5e, 0x46, 0x0b, 0x72, 0x44, 0xc4,
	0xe1, 0xfc, 0x62, 0xda, 0xf1, 0xfb, 0xa2, 0xdb,	0xd6, 0xbe, 0x5c, 0xd7,
	0x24, 0xa3, 0xf5, 0xb9, 0x2f, 0x57, 0x16, 0x49, 0x75, 0x47, 0x77, 0x09,
	0x5c, 0xa1, 0xb4, 0xc3, 0x4f, 0x60, 0x2b, 0xb0, 0x0c, 0xc8, 0xd6, 0x66,
	0xba, 0x9b, 0x82, 0x29,	0x33, 0x92, 0x26, 0x99, 0x31, 0x1c, 0x7f, 0x9b,
	0x00, 0x00, 0x01, 0x0ff,
पूर्ण;

अटल स्थिर u8 *codec_h264_eos_sequence(u32 *len)
अणु
	*len = ARRAY_SIZE(eos_sequence);
	वापस eos_sequence;
पूर्ण

काष्ठा codec_h264 अणु
	/* H.264 decoder requires an extended firmware */
	व्योम      *ext_fw_vaddr;
	dma_addr_t ext_fw_paddr;

	/* Buffer क्रम the H.264 Workspace */
	व्योम      *workspace_vaddr;
	dma_addr_t workspace_paddr;

	/* Buffer क्रम the H.264 references MV */
	व्योम      *ref_vaddr;
	dma_addr_t ref_paddr;
	u32	   ref_size;

	/* Buffer क्रम parsed SEI data */
	व्योम      *sei_vaddr;
	dma_addr_t sei_paddr;

	u32 mb_width;
	u32 mb_height;
	u32 max_refs;
पूर्ण;

अटल पूर्णांक codec_h264_can_recycle(काष्ठा amvdec_core *core)
अणु
	वापस !amvdec_पढ़ो_करोs(core, AV_SCRATCH_7) ||
	       !amvdec_पढ़ो_करोs(core, AV_SCRATCH_8);
पूर्ण

अटल व्योम codec_h264_recycle(काष्ठा amvdec_core *core, u32 buf_idx)
अणु
	/*
	 * Tell the firmware it can recycle this buffer.
	 * AV_SCRATCH_8 serves the same purpose.
	 */
	अगर (!amvdec_पढ़ो_करोs(core, AV_SCRATCH_7))
		amvdec_ग_लिखो_करोs(core, AV_SCRATCH_7, buf_idx + 1);
	अन्यथा
		amvdec_ग_लिखो_करोs(core, AV_SCRATCH_8, buf_idx + 1);
पूर्ण

अटल पूर्णांक codec_h264_start(काष्ठा amvdec_session *sess)
अणु
	u32 workspace_offset;
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा codec_h264 *h264 = sess->priv;

	/* Allocate some memory क्रम the H.264 decoder's state */
	h264->workspace_vaddr =
		dma_alloc_coherent(core->dev, SIZE_WORKSPACE,
				   &h264->workspace_paddr, GFP_KERNEL);
	अगर (!h264->workspace_vaddr)
		वापस -ENOMEM;

	/* Allocate some memory क्रम the H.264 SEI dump */
	h264->sei_vaddr = dma_alloc_coherent(core->dev, SIZE_SEI,
					     &h264->sei_paddr, GFP_KERNEL);
	अगर (!h264->sei_vaddr)
		वापस -ENOMEM;

	amvdec_ग_लिखो_करोs_bits(core, POWER_CTL_VLD, BIT(9) | BIT(6));

	workspace_offset = h264->workspace_paddr - WORKSPACE_BUF_OFFSET;
	amvdec_ग_लिखो_करोs(core, AV_SCRATCH_1, workspace_offset);
	amvdec_ग_लिखो_करोs(core, AV_SCRATCH_G, h264->ext_fw_paddr);
	amvdec_ग_लिखो_करोs(core, AV_SCRATCH_I, h264->sei_paddr -
					     workspace_offset);

	/* Enable "error correction" */
	amvdec_ग_लिखो_करोs(core, AV_SCRATCH_F,
			 (amvdec_पढ़ो_करोs(core, AV_SCRATCH_F) & 0xffffffc3) |
			 BIT(4) | BIT(7));

	amvdec_ग_लिखो_करोs(core, MDEC_PIC_DC_THRESH, 0x404038aa);

	वापस 0;
पूर्ण

अटल पूर्णांक codec_h264_stop(काष्ठा amvdec_session *sess)
अणु
	काष्ठा codec_h264 *h264 = sess->priv;
	काष्ठा amvdec_core *core = sess->core;

	अगर (h264->ext_fw_vaddr)
		dma_मुक्त_coherent(core->dev, SIZE_EXT_FW,
				  h264->ext_fw_vaddr, h264->ext_fw_paddr);

	अगर (h264->workspace_vaddr)
		dma_मुक्त_coherent(core->dev, SIZE_WORKSPACE,
				  h264->workspace_vaddr, h264->workspace_paddr);

	अगर (h264->ref_vaddr)
		dma_मुक्त_coherent(core->dev, h264->ref_size,
				  h264->ref_vaddr, h264->ref_paddr);

	अगर (h264->sei_vaddr)
		dma_मुक्त_coherent(core->dev, SIZE_SEI,
				  h264->sei_vaddr, h264->sei_paddr);

	वापस 0;
पूर्ण

अटल पूर्णांक codec_h264_load_extended_firmware(काष्ठा amvdec_session *sess,
					     स्थिर u8 *data, u32 len)
अणु
	काष्ठा codec_h264 *h264;
	काष्ठा amvdec_core *core = sess->core;

	अगर (len < SIZE_EXT_FW)
		वापस -EINVAL;

	h264 = kzalloc(माप(*h264), GFP_KERNEL);
	अगर (!h264)
		वापस -ENOMEM;

	h264->ext_fw_vaddr = dma_alloc_coherent(core->dev, SIZE_EXT_FW,
						&h264->ext_fw_paddr,
						GFP_KERNEL);
	अगर (!h264->ext_fw_vaddr) अणु
		kमुक्त(h264);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(h264->ext_fw_vaddr, data, SIZE_EXT_FW);
	sess->priv = h264;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_fract par_table[] = अणु
	अणु 1, 1 पूर्ण,   अणु 1, 1 पूर्ण,    अणु 12, 11 पूर्ण, अणु 10, 11 पूर्ण,
	अणु 16, 11 पूर्ण, अणु 40, 33 पूर्ण,  अणु 24, 11 पूर्ण, अणु 20, 11 पूर्ण,
	अणु 32, 11 पूर्ण, अणु 80, 33 पूर्ण,  अणु 18, 11 पूर्ण, अणु 15, 11 पूर्ण,
	अणु 64, 33 पूर्ण, अणु 160, 99 पूर्ण, अणु 4, 3 पूर्ण,   अणु 3, 2 पूर्ण,
	अणु 2, 1 पूर्ण
पूर्ण;

अटल व्योम codec_h264_set_par(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	u32 seq_info = amvdec_पढ़ो_करोs(core, AV_SCRATCH_2);
	u32 ar_idc = (seq_info >> AR_IDC_BIT) & AR_IDC_MASK;

	अगर (!(seq_info & AR_PRESENT_FLAG))
		वापस;

	अगर (ar_idc == AR_EXTEND) अणु
		u32 ar_info = amvdec_पढ़ो_करोs(core, AV_SCRATCH_3);

		sess->pixelaspect.numerator = ar_info & 0xffff;
		sess->pixelaspect.denominator = (ar_info >> 16) & 0xffff;
		वापस;
	पूर्ण

	अगर (ar_idc >= ARRAY_SIZE(par_table))
		वापस;

	sess->pixelaspect = par_table[ar_idc];
पूर्ण

अटल व्योम codec_h264_resume(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा codec_h264 *h264 = sess->priv;
	u32 mb_width, mb_height, mb_total;

	amvdec_set_canvases(sess,
			    (u32[])अणु ANC0_CANVAS_ADDR, 0 पूर्ण,
			    (u32[])अणु 24, 0 पूर्ण);

	dev_dbg(core->dev, "max_refs = %u; actual_dpb_size = %u\n",
		h264->max_refs, sess->num_dst_bufs);

	/* Align to a multiple of 4 macroblocks */
	mb_width = ALIGN(h264->mb_width, 4);
	mb_height = ALIGN(h264->mb_height, 4);
	mb_total = mb_width * mb_height;

	h264->ref_size = mb_total * MB_MV_SIZE * h264->max_refs;
	h264->ref_vaddr = dma_alloc_coherent(core->dev, h264->ref_size,
					     &h264->ref_paddr, GFP_KERNEL);
	अगर (!h264->ref_vaddr) अणु
		amvdec_पात(sess);
		वापस;
	पूर्ण

	/* Address to store the references' MVs */
	amvdec_ग_लिखो_करोs(core, AV_SCRATCH_1, h264->ref_paddr);
	/* End of ref MV */
	amvdec_ग_लिखो_करोs(core, AV_SCRATCH_4, h264->ref_paddr + h264->ref_size);

	amvdec_ग_लिखो_करोs(core, AV_SCRATCH_0, (h264->max_refs << 24) |
					     (sess->num_dst_bufs << 16) |
					     ((h264->max_refs - 1) << 8));
पूर्ण

/*
 * Configure the H.264 decoder when the parser detected a parameter set change
 */
अटल व्योम codec_h264_src_change(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा codec_h264 *h264 = sess->priv;
	u32 parsed_info, mb_total;
	u32 crop_inक्रम, crop_bottom, crop_right;
	u32 frame_width, frame_height;

	sess->keyframe_found = 1;

	parsed_info = amvdec_पढ़ो_करोs(core, AV_SCRATCH_1);

	/* Total number of 16x16 macroblocks */
	mb_total = (parsed_info >> MB_TOTAL_BIT) & MB_TOTAL_MASK;
	/* Number of macroblocks per line */
	h264->mb_width = parsed_info & MB_WIDTH_MASK;
	/* Number of macroblock lines */
	h264->mb_height = mb_total / h264->mb_width;

	h264->max_refs = ((parsed_info >> MAX_REF_BIT) & MAX_REF_MASK) + 1;

	crop_inक्रम = amvdec_पढ़ो_करोs(core, AV_SCRATCH_6);
	crop_bottom = (crop_inक्रम & 0xff);
	crop_right = (crop_inक्रम >> 16) & 0xff;

	frame_width = h264->mb_width * 16 - crop_right;
	frame_height = h264->mb_height * 16 - crop_bottom;

	dev_dbg(core->dev, "frame: %ux%u; crop: %u %u\n",
		frame_width, frame_height, crop_right, crop_bottom);

	codec_h264_set_par(sess);
	amvdec_src_change(sess, frame_width, frame_height, h264->max_refs + 5);
पूर्ण

/*
 * The bitstream offset is split in half in 2 dअगरferent रेजिस्टरs.
 * Fetch its MSB here, which location depends on the frame number.
 */
अटल u32 get_offset_msb(काष्ठा amvdec_core *core, पूर्णांक frame_num)
अणु
	पूर्णांक take_msb = frame_num % 2;
	पूर्णांक reg_offset = (frame_num / 2) * 4;
	u32 offset_msb = amvdec_पढ़ो_करोs(core, AV_SCRATCH_A + reg_offset);

	अगर (take_msb)
		वापस offset_msb & 0xffff0000;

	वापस (offset_msb & 0x0000ffff) << 16;
पूर्ण

अटल व्योम codec_h264_frames_पढ़ोy(काष्ठा amvdec_session *sess, u32 status)
अणु
	काष्ठा amvdec_core *core = sess->core;
	पूर्णांक error_count;
	पूर्णांक num_frames;
	पूर्णांक i;

	error_count = amvdec_पढ़ो_करोs(core, AV_SCRATCH_D);
	num_frames = (status >> 8) & 0xff;
	अगर (error_count) अणु
		dev_warn(core->dev,
			 "decoder error(s) happened, count %d\n", error_count);
		amvdec_ग_लिखो_करोs(core, AV_SCRATCH_D, 0);
	पूर्ण

	क्रम (i = 0; i < num_frames; i++) अणु
		u32 frame_status = amvdec_पढ़ो_करोs(core, AV_SCRATCH_1 + i * 4);
		u32 buffer_index = frame_status & BUF_IDX_MASK;
		u32 pic_काष्ठा = (frame_status >> PIC_STRUCT_BIT) &
				 PIC_STRUCT_MASK;
		u32 offset = (frame_status >> OFFSET_BIT) & OFFSET_MASK;
		u32 field = V4L2_FIELD_NONE;

		/*
		 * A buffer decode error means it was decoded,
		 * but part of the picture will have artअगरacts.
		 * Typical reason is a temporarily corrupted bitstream
		 */
		अगर (frame_status & ERROR_FLAG)
			dev_dbg(core->dev, "Buffer %d decode error\n",
				buffer_index);

		अगर (pic_काष्ठा == PIC_TOP_BOT)
			field = V4L2_FIELD_INTERLACED_TB;
		अन्यथा अगर (pic_काष्ठा == PIC_BOT_TOP)
			field = V4L2_FIELD_INTERLACED_BT;

		offset |= get_offset_msb(core, i);
		amvdec_dst_buf_करोne_idx(sess, buffer_index, offset, field);
	पूर्ण
पूर्ण

अटल irqवापस_t codec_h264_thपढ़ोed_isr(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	u32 status;
	u32 size;
	u8 cmd;

	status = amvdec_पढ़ो_करोs(core, AV_SCRATCH_0);
	cmd = status & CMD_MASK;

	चयन (cmd) अणु
	हाल CMD_SRC_CHANGE:
		codec_h264_src_change(sess);
		अवरोध;
	हाल CMD_FRAMES_READY:
		codec_h264_frames_पढ़ोy(sess, status);
		अवरोध;
	हाल CMD_FATAL_ERROR:
		dev_err(core->dev, "H.264 decoder fatal error\n");
		जाओ पात;
	हाल CMD_BAD_WIDTH:
		size = (amvdec_पढ़ो_करोs(core, AV_SCRATCH_1) + 1) * 16;
		dev_err(core->dev, "Unsupported video width: %u\n", size);
		जाओ पात;
	हाल CMD_BAD_HEIGHT:
		size = (amvdec_पढ़ो_करोs(core, AV_SCRATCH_1) + 1) * 16;
		dev_err(core->dev, "Unsupported video height: %u\n", size);
		जाओ पात;
	हाल 0: /* Unused but not worth prपूर्णांकing क्रम */
	हाल 9:
		अवरोध;
	शेष:
		dev_info(core->dev, "Unexpected H264 ISR: %08X\n", cmd);
		अवरोध;
	पूर्ण

	अगर (cmd && cmd != CMD_SRC_CHANGE)
		amvdec_ग_लिखो_करोs(core, AV_SCRATCH_0, 0);

	/* Decoder has some SEI data क्रम us ; ignore */
	अगर (amvdec_पढ़ो_करोs(core, AV_SCRATCH_J) & SEI_DATA_READY)
		amvdec_ग_लिखो_करोs(core, AV_SCRATCH_J, 0);

	वापस IRQ_HANDLED;
पात:
	amvdec_पात(sess);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t codec_h264_isr(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;

	amvdec_ग_लिखो_करोs(core, ASSIST_MBOX1_CLR_REG, 1);

	वापस IRQ_WAKE_THREAD;
पूर्ण

काष्ठा amvdec_codec_ops codec_h264_ops = अणु
	.start = codec_h264_start,
	.stop = codec_h264_stop,
	.load_extended_firmware = codec_h264_load_extended_firmware,
	.isr = codec_h264_isr,
	.thपढ़ोed_isr = codec_h264_thपढ़ोed_isr,
	.can_recycle = codec_h264_can_recycle,
	.recycle = codec_h264_recycle,
	.eos_sequence = codec_h264_eos_sequence,
	.resume = codec_h264_resume,
पूर्ण;
