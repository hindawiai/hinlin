<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Coda multi-standard codec IP - JPEG support functions
 *
 * Copyright (C) 2014 Philipp Zabel, Pengutronix
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/swab.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-jpeg.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "coda.h"
#समावेश "trace.h"

#घोषणा SOI_MARKER	0xffd8
#घोषणा APP9_MARKER	0xffe9
#घोषणा DRI_MARKER	0xffdd
#घोषणा DQT_MARKER	0xffdb
#घोषणा DHT_MARKER	0xffc4
#घोषणा SOF_MARKER	0xffc0
#घोषणा SOS_MARKER	0xffda
#घोषणा EOI_MARKER	0xffd9

क्रमागत अणु
	CODA9_JPEG_FORMAT_420,
	CODA9_JPEG_FORMAT_422,
	CODA9_JPEG_FORMAT_224,
	CODA9_JPEG_FORMAT_444,
	CODA9_JPEG_FORMAT_400,
पूर्ण;

काष्ठा coda_huff_tab अणु
	u8 luma_dc[16 + 12];
	u8 chroma_dc[16 + 12];
	u8 luma_ac[16 + 162];
	u8 chroma_ac[16 + 162];

	/* DC Luma, DC Chroma, AC Luma, AC Chroma */
	s16	min[4 * 16];
	s16	max[4 * 16];
	s8	ptr[4 * 16];
पूर्ण;

#घोषणा CODA9_JPEG_ENC_HUFF_DATA_SIZE	(256 + 256 + 16 + 16)

/*
 * Typical Huffman tables क्रम 8-bit precision luminance and
 * chrominance from JPEG ITU-T.81 (ISO/IEC 10918-1) Annex K.3
 */

अटल स्थिर अचिन्हित अक्षर luma_dc[16 + 12] = अणु
	/* bits */
	0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* values */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर chroma_dc[16 + 12] = अणु
	/* bits */
	0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* values */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर luma_ac[16 + 162 + 2] = अणु
	/* bits */
	0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03,
	0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7d,
	/* values */
	0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
	0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
	0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
	0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
	0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
	0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
	0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
	0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
	0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
	0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
	0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
	0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
	0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
	0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
	0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
	0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa, /* padded to 32-bit */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर chroma_ac[16 + 162 + 2] = अणु
	/* bits */
	0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04,
	0x07, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 0x77,
	/* values */
	0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
	0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
	0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
	0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
	0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
	0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
	0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
	0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
	0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
	0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
	0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
	0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
	0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
	0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
	0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
	0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa, /* padded to 32-bit */
पूर्ण;

/*
 * Quantization tables क्रम luminance and chrominance components in
 * zig-zag scan order from the Freescale i.MX VPU libraries
 */

अटल अचिन्हित अक्षर luma_q[64] = अणु
	0x06, 0x04, 0x04, 0x04, 0x05, 0x04, 0x06, 0x05,
	0x05, 0x06, 0x09, 0x06, 0x05, 0x06, 0x09, 0x0b,
	0x08, 0x06, 0x06, 0x08, 0x0b, 0x0c, 0x0a, 0x0a,
	0x0b, 0x0a, 0x0a, 0x0c, 0x10, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x10, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
पूर्ण;

अटल अचिन्हित अक्षर chroma_q[64] = अणु
	0x07, 0x07, 0x07, 0x0d, 0x0c, 0x0d, 0x18, 0x10,
	0x10, 0x18, 0x14, 0x0e, 0x0e, 0x0e, 0x14, 0x14,
	0x0e, 0x0e, 0x0e, 0x0e, 0x14, 0x11, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x11, 0x11, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x11, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर width_align[] = अणु
	[CODA9_JPEG_FORMAT_420] = 16,
	[CODA9_JPEG_FORMAT_422] = 16,
	[CODA9_JPEG_FORMAT_224] = 8,
	[CODA9_JPEG_FORMAT_444] = 8,
	[CODA9_JPEG_FORMAT_400] = 8,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर height_align[] = अणु
	[CODA9_JPEG_FORMAT_420] = 16,
	[CODA9_JPEG_FORMAT_422] = 8,
	[CODA9_JPEG_FORMAT_224] = 16,
	[CODA9_JPEG_FORMAT_444] = 8,
	[CODA9_JPEG_FORMAT_400] = 8,
पूर्ण;

अटल पूर्णांक coda9_jpeg_chroma_क्रमmat(u32 pixfmt)
अणु
	चयन (pixfmt) अणु
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_NV12:
		वापस CODA9_JPEG_FORMAT_420;
	हाल V4L2_PIX_FMT_YUV422P:
		वापस CODA9_JPEG_FORMAT_422;
	हाल V4L2_PIX_FMT_YUV444:
		वापस CODA9_JPEG_FORMAT_444;
	हाल V4L2_PIX_FMT_GREY:
		वापस CODA9_JPEG_FORMAT_400;
	पूर्ण
	वापस -EINVAL;
पूर्ण

काष्ठा coda_स_नकल_desc अणु
	पूर्णांक offset;
	स्थिर व्योम *src;
	माप_प्रकार len;
पूर्ण;

अटल व्योम coda_स_नकल_parabuf(व्योम *parabuf,
				स्थिर काष्ठा coda_स_नकल_desc *desc)
अणु
	u32 *dst = parabuf + desc->offset;
	स्थिर u32 *src = desc->src;
	पूर्णांक len = desc->len / 4;
	पूर्णांक i;

	क्रम (i = 0; i < len; i += 2) अणु
		dst[i + 1] = swab32(src[i]);
		dst[i] = swab32(src[i + 1]);
	पूर्ण
पूर्ण

पूर्णांक coda_jpeg_ग_लिखो_tables(काष्ठा coda_ctx *ctx)
अणु
	पूर्णांक i;
	अटल स्थिर काष्ठा coda_स_नकल_desc huff[8] = अणु
		अणु 0,   luma_dc,    माप(luma_dc)    पूर्ण,
		अणु 32,  luma_ac,    माप(luma_ac)    पूर्ण,
		अणु 216, chroma_dc,  माप(chroma_dc)  पूर्ण,
		अणु 248, chroma_ac,  माप(chroma_ac)  पूर्ण,
	पूर्ण;
	काष्ठा coda_स_नकल_desc qmat[3] = अणु
		अणु 512, ctx->params.jpeg_qmat_tab[0], 64 पूर्ण,
		अणु 576, ctx->params.jpeg_qmat_tab[1], 64 पूर्ण,
		अणु 640, ctx->params.jpeg_qmat_tab[1], 64 पूर्ण,
	पूर्ण;

	/* Write huffman tables to parameter memory */
	क्रम (i = 0; i < ARRAY_SIZE(huff); i++)
		coda_स_नकल_parabuf(ctx->parabuf.vaddr, huff + i);

	/* Write Q-matrix to parameter memory */
	क्रम (i = 0; i < ARRAY_SIZE(qmat); i++)
		coda_स_नकल_parabuf(ctx->parabuf.vaddr, qmat + i);

	वापस 0;
पूर्ण

bool coda_jpeg_check_buffer(काष्ठा coda_ctx *ctx, काष्ठा vb2_buffer *vb)
अणु
	व्योम *vaddr = vb2_plane_vaddr(vb, 0);
	u16 soi, eoi;
	पूर्णांक len, i;

	soi = be16_to_cpup((__be16 *)vaddr);
	अगर (soi != SOI_MARKER)
		वापस false;

	len = vb2_get_plane_payload(vb, 0);
	vaddr += len - 2;
	क्रम (i = 0; i < 32; i++) अणु
		eoi = be16_to_cpup((__be16 *)(vaddr - i));
		अगर (eoi == EOI_MARKER) अणु
			अगर (i > 0)
				vb2_set_plane_payload(vb, 0, len - i);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक coda9_jpeg_gen_dec_huff_tab(काष्ठा coda_ctx *ctx, पूर्णांक tab_num);

पूर्णांक coda_jpeg_decode_header(काष्ठा coda_ctx *ctx, काष्ठा vb2_buffer *vb)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	u8 *buf = vb2_plane_vaddr(vb, 0);
	माप_प्रकार len = vb2_get_plane_payload(vb, 0);
	काष्ठा v4l2_jpeg_scan_header scan_header;
	काष्ठा v4l2_jpeg_reference quantization_tables[4] = अणु पूर्ण;
	काष्ठा v4l2_jpeg_reference huffman_tables[4] = अणु पूर्ण;
	काष्ठा v4l2_jpeg_header header = अणु
		.scan = &scan_header,
		.quantization_tables = quantization_tables,
		.huffman_tables = huffman_tables,
	पूर्ण;
	काष्ठा coda_q_data *q_data_src;
	काष्ठा coda_huff_tab *huff_tab;
	पूर्णांक i, j, ret;

	ret = v4l2_jpeg_parse_header(buf, len, &header);
	अगर (ret < 0) अणु
		v4l2_err(&dev->v4l2_dev, "failed to parse header\n");
		वापस ret;
	पूर्ण

	ctx->params.jpeg_restart_पूर्णांकerval = header.restart_पूर्णांकerval;

	/* check frame header */
	अगर (header.frame.height > ctx->codec->max_h ||
	    header.frame.width > ctx->codec->max_w) अणु
		v4l2_err(&dev->v4l2_dev, "invalid dimensions: %dx%d\n",
			 header.frame.width, header.frame.height);
		वापस -EINVAL;
	पूर्ण

	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	अगर (header.frame.height != q_data_src->height ||
	    header.frame.width != q_data_src->width) अणु
		v4l2_err(&dev->v4l2_dev,
			 "dimensions don't match format: %dx%d\n",
			 header.frame.width, header.frame.height);
		वापस -EINVAL;
	पूर्ण

	अगर (header.frame.num_components != 3) अणु
		v4l2_err(&dev->v4l2_dev,
			 "unsupported number of components: %d\n",
			 header.frame.num_components);
		वापस -EINVAL;
	पूर्ण

	/* install quantization tables */
	अगर (quantization_tables[3].start) अणु
		v4l2_err(&dev->v4l2_dev,
			 "only 3 quantization tables supported\n");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < 3; i++) अणु
		अगर (!quantization_tables[i].start)
			जारी;
		अगर (quantization_tables[i].length != 64) अणु
			v4l2_err(&dev->v4l2_dev,
				 "only 8-bit quantization tables supported\n");
			जारी;
		पूर्ण
		अगर (!ctx->params.jpeg_qmat_tab[i]) अणु
			ctx->params.jpeg_qmat_tab[i] = kदो_स्मृति(64, GFP_KERNEL);
			अगर (!ctx->params.jpeg_qmat_tab[i])
				वापस -ENOMEM;
		पूर्ण
		स_नकल(ctx->params.jpeg_qmat_tab[i],
		       quantization_tables[i].start, 64);
	पूर्ण

	/* install Huffman tables */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!huffman_tables[i].start) अणु
			v4l2_err(&dev->v4l2_dev, "missing Huffman table\n");
			वापस -EINVAL;
		पूर्ण
		/* AC tables should be between 17 -> 178, DC between 17 -> 28 */
		अगर (huffman_tables[i].length < 17 ||
		    huffman_tables[i].length > 178 ||
		    ((i & 2) == 0 && huffman_tables[i].length > 28)) अणु
			v4l2_err(&dev->v4l2_dev,
				 "invalid Huffman table %d length: %zu\n",
				 i, huffman_tables[i].length);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	huff_tab = ctx->params.jpeg_huff_tab;
	अगर (!huff_tab) अणु
		huff_tab = kzalloc(माप(काष्ठा coda_huff_tab), GFP_KERNEL);
		अगर (!huff_tab)
			वापस -ENOMEM;
		ctx->params.jpeg_huff_tab = huff_tab;
	पूर्ण

	स_रखो(huff_tab, 0, माप(*huff_tab));
	स_नकल(huff_tab->luma_dc, huffman_tables[0].start, huffman_tables[0].length);
	स_नकल(huff_tab->chroma_dc, huffman_tables[1].start, huffman_tables[1].length);
	स_नकल(huff_tab->luma_ac, huffman_tables[2].start, huffman_tables[2].length);
	स_नकल(huff_tab->chroma_ac, huffman_tables[3].start, huffman_tables[3].length);

	/* check scan header */
	क्रम (i = 0; i < scan_header.num_components; i++) अणु
		काष्ठा v4l2_jpeg_scan_component_spec *scan_component;

		scan_component = &scan_header.component[i];
		क्रम (j = 0; j < header.frame.num_components; j++) अणु
			अगर (header.frame.component[j].component_identअगरier ==
			    scan_component->component_selector)
				अवरोध;
		पूर्ण
		अगर (j == header.frame.num_components)
			जारी;

		ctx->params.jpeg_huff_dc_index[j] =
			scan_component->dc_entropy_coding_table_selector;
		ctx->params.jpeg_huff_ac_index[j] =
			scan_component->ac_entropy_coding_table_selector;
	पूर्ण

	/* Generate Huffman table inक्रमmation */
	क्रम (i = 0; i < 4; i++)
		coda9_jpeg_gen_dec_huff_tab(ctx, i);

	/* start of entropy coded segment */
	ctx->jpeg_ecs_offset = header.ecs_offset;

	चयन (header.frame.subsampling) अणु
	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_420:
	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_422:
		ctx->params.jpeg_chroma_subsampling = header.frame.subsampling;
		अवरोध;
	शेष:
		v4l2_err(&dev->v4l2_dev, "chroma subsampling not supported: %d",
			 header.frame.subsampling);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम coda9_jpeg_ग_लिखो_huff_values(काष्ठा coda_dev *dev, u8 *bits,
						पूर्णांक num_values)
अणु
	s8 *values = (s8 *)(bits + 16);
	पूर्णांक huff_length, i;

	क्रम (huff_length = 0, i = 0; i < 16; i++)
		huff_length += bits[i];
	क्रम (i = huff_length; i < num_values; i++)
		values[i] = -1;
	क्रम (i = 0; i < num_values; i++)
		coda_ग_लिखो(dev, (s32)values[i], CODA9_REG_JPEG_HUFF_DATA);
पूर्ण

अटल पूर्णांक coda9_jpeg_dec_huff_setup(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_huff_tab *huff_tab = ctx->params.jpeg_huff_tab;
	काष्ठा coda_dev *dev = ctx->dev;
	s16 *huff_min = huff_tab->min;
	s16 *huff_max = huff_tab->max;
	s8 *huff_ptr = huff_tab->ptr;
	पूर्णांक i;

	/* MIN Tables */
	coda_ग_लिखो(dev, 0x003, CODA9_REG_JPEG_HUFF_CTRL);
	coda_ग_लिखो(dev, 0x000, CODA9_REG_JPEG_HUFF_ADDR);
	क्रम (i = 0; i < 4 * 16; i++)
		coda_ग_लिखो(dev, (s32)huff_min[i], CODA9_REG_JPEG_HUFF_DATA);

	/* MAX Tables */
	coda_ग_लिखो(dev, 0x403, CODA9_REG_JPEG_HUFF_CTRL);
	coda_ग_लिखो(dev, 0x440, CODA9_REG_JPEG_HUFF_ADDR);
	क्रम (i = 0; i < 4 * 16; i++)
		coda_ग_लिखो(dev, (s32)huff_max[i], CODA9_REG_JPEG_HUFF_DATA);

	/* PTR Tables */
	coda_ग_लिखो(dev, 0x803, CODA9_REG_JPEG_HUFF_CTRL);
	coda_ग_लिखो(dev, 0x880, CODA9_REG_JPEG_HUFF_ADDR);
	क्रम (i = 0; i < 4 * 16; i++)
		coda_ग_लिखो(dev, (s32)huff_ptr[i], CODA9_REG_JPEG_HUFF_DATA);

	/* VAL Tables: DC Luma, DC Chroma, AC Luma, AC Chroma */
	coda_ग_लिखो(dev, 0xc03, CODA9_REG_JPEG_HUFF_CTRL);
	coda9_jpeg_ग_लिखो_huff_values(dev, huff_tab->luma_dc, 12);
	coda9_jpeg_ग_लिखो_huff_values(dev, huff_tab->chroma_dc, 12);
	coda9_jpeg_ग_लिखो_huff_values(dev, huff_tab->luma_ac, 162);
	coda9_jpeg_ग_लिखो_huff_values(dev, huff_tab->chroma_ac, 162);
	coda_ग_लिखो(dev, 0x000, CODA9_REG_JPEG_HUFF_CTRL);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम coda9_jpeg_ग_लिखो_qmat_tab(काष्ठा coda_dev *dev,
					     u8 *qmat, पूर्णांक index)
अणु
	पूर्णांक i;

	coda_ग_लिखो(dev, index | 0x3, CODA9_REG_JPEG_QMAT_CTRL);
	क्रम (i = 0; i < 64; i++)
		coda_ग_लिखो(dev, qmat[i], CODA9_REG_JPEG_QMAT_DATA);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_QMAT_CTRL);
पूर्ण

अटल व्योम coda9_jpeg_qmat_setup(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	पूर्णांक *qmat_index = ctx->params.jpeg_qmat_index;
	u8 **qmat_tab = ctx->params.jpeg_qmat_tab;

	coda9_jpeg_ग_लिखो_qmat_tab(dev, qmat_tab[qmat_index[0]], 0x00);
	coda9_jpeg_ग_लिखो_qmat_tab(dev, qmat_tab[qmat_index[1]], 0x40);
	coda9_jpeg_ग_लिखो_qmat_tab(dev, qmat_tab[qmat_index[2]], 0x80);
पूर्ण

अटल व्योम coda9_jpeg_dec_bbc_gbu_setup(काष्ठा coda_ctx *ctx,
					 काष्ठा vb2_buffer *buf, u32 ecs_offset)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	पूर्णांक page_ptr, word_ptr, bit_ptr;
	u32 bbc_base_addr, end_addr;
	पूर्णांक bbc_cur_pos;
	पूर्णांक ret, val;

	bbc_base_addr = vb2_dma_contig_plane_dma_addr(buf, 0);
	end_addr = bbc_base_addr + vb2_get_plane_payload(buf, 0);

	page_ptr = ecs_offset / 256;
	word_ptr = (ecs_offset % 256) / 4;
	अगर (page_ptr & 1)
		word_ptr += 64;
	bit_ptr = (ecs_offset % 4) * 8;
	अगर (word_ptr & 1)
		bit_ptr += 32;
	word_ptr &= ~0x1;

	coda_ग_लिखो(dev, end_addr, CODA9_REG_JPEG_BBC_WR_PTR);
	coda_ग_लिखो(dev, bbc_base_addr, CODA9_REG_JPEG_BBC_BAS_ADDR);

	/* Leave 3 256-byte page margin to aव्योम a BBC पूर्णांकerrupt */
	coda_ग_लिखो(dev, end_addr + 256 * 3 + 256, CODA9_REG_JPEG_BBC_END_ADDR);
	val = DIV_ROUND_UP(vb2_plane_size(buf, 0), 256) + 3;
	coda_ग_लिखो(dev, BIT(31) | val, CODA9_REG_JPEG_BBC_STRM_CTRL);

	bbc_cur_pos = page_ptr;
	coda_ग_लिखो(dev, bbc_cur_pos, CODA9_REG_JPEG_BBC_CUR_POS);
	coda_ग_लिखो(dev, bbc_base_addr + (bbc_cur_pos << 8),
			CODA9_REG_JPEG_BBC_EXT_ADDR);
	coda_ग_लिखो(dev, (bbc_cur_pos & 1) << 6, CODA9_REG_JPEG_BBC_INT_ADDR);
	coda_ग_लिखो(dev, 64, CODA9_REG_JPEG_BBC_DATA_CNT);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_BBC_COMMAND);
	करो अणु
		ret = coda_पढ़ो(dev, CODA9_REG_JPEG_BBC_BUSY);
	पूर्ण जबतक (ret == 1);

	bbc_cur_pos++;
	coda_ग_लिखो(dev, bbc_cur_pos, CODA9_REG_JPEG_BBC_CUR_POS);
	coda_ग_लिखो(dev, bbc_base_addr + (bbc_cur_pos << 8),
			CODA9_REG_JPEG_BBC_EXT_ADDR);
	coda_ग_लिखो(dev, (bbc_cur_pos & 1) << 6, CODA9_REG_JPEG_BBC_INT_ADDR);
	coda_ग_लिखो(dev, 64, CODA9_REG_JPEG_BBC_DATA_CNT);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_BBC_COMMAND);
	करो अणु
		ret = coda_पढ़ो(dev, CODA9_REG_JPEG_BBC_BUSY);
	पूर्ण जबतक (ret == 1);

	bbc_cur_pos++;
	coda_ग_लिखो(dev, bbc_cur_pos, CODA9_REG_JPEG_BBC_CUR_POS);
	coda_ग_लिखो(dev, 1, CODA9_REG_JPEG_BBC_CTRL);

	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_GBU_TT_CNT);
	coda_ग_लिखो(dev, word_ptr, CODA9_REG_JPEG_GBU_WD_PTR);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_GBU_BBSR);
	coda_ग_लिखो(dev, 127, CODA9_REG_JPEG_GBU_BBER);
	अगर (page_ptr & 1) अणु
		coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_GBU_BBIR);
		coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_GBU_BBHR);
	पूर्ण अन्यथा अणु
		coda_ग_लिखो(dev, 64, CODA9_REG_JPEG_GBU_BBIR);
		coda_ग_लिखो(dev, 64, CODA9_REG_JPEG_GBU_BBHR);
	पूर्ण
	coda_ग_लिखो(dev, 4, CODA9_REG_JPEG_GBU_CTRL);
	coda_ग_लिखो(dev, bit_ptr, CODA9_REG_JPEG_GBU_FF_RPTR);
	coda_ग_लिखो(dev, 3, CODA9_REG_JPEG_GBU_CTRL);
पूर्ण

अटल स्थिर पूर्णांक bus_req_num[] = अणु
	[CODA9_JPEG_FORMAT_420] = 2,
	[CODA9_JPEG_FORMAT_422] = 3,
	[CODA9_JPEG_FORMAT_224] = 3,
	[CODA9_JPEG_FORMAT_444] = 4,
	[CODA9_JPEG_FORMAT_400] = 4,
पूर्ण;

#घोषणा MCU_INFO(mcu_block_num, comp_num, comp0_info, comp1_info, comp2_info) \
	(((mcu_block_num) << CODA9_JPEG_MCU_BLOCK_NUM_OFFSET) | \
	 ((comp_num) << CODA9_JPEG_COMP_NUM_OFFSET) | \
	 ((comp0_info) << CODA9_JPEG_COMP0_INFO_OFFSET) | \
	 ((comp1_info) << CODA9_JPEG_COMP1_INFO_OFFSET) | \
	 ((comp2_info) << CODA9_JPEG_COMP2_INFO_OFFSET))

अटल स्थिर u32 mcu_info[] = अणु
	[CODA9_JPEG_FORMAT_420] = MCU_INFO(6, 3, 10, 5, 5),
	[CODA9_JPEG_FORMAT_422] = MCU_INFO(4, 3, 9, 5, 5),
	[CODA9_JPEG_FORMAT_224] = MCU_INFO(4, 3, 6, 5, 5),
	[CODA9_JPEG_FORMAT_444] = MCU_INFO(3, 3, 5, 5, 5),
	[CODA9_JPEG_FORMAT_400] = MCU_INFO(1, 1, 5, 0, 0),
पूर्ण;

/*
 * Convert Huffman table specअगरcations to tables of codes and code lengths.
 * For reference, see JPEG ITU-T.81 (ISO/IEC 10918-1) [1]
 *
 * [1] https://www.w3.org/Graphics/JPEG/itu-t81.pdf
 */
अटल पूर्णांक coda9_jpeg_gen_enc_huff_tab(काष्ठा coda_ctx *ctx, पूर्णांक tab_num,
				       पूर्णांक *ehufsi, पूर्णांक *ehufco)
अणु
	पूर्णांक i, j, k, lastk, si, code, maxsymbol;
	स्थिर u8 *bits, *huffval;
	काष्ठा अणु
		पूर्णांक size[256];
		पूर्णांक code[256];
	पूर्ण *huff;
	अटल स्थिर अचिन्हित अक्षर *huff_tअसल[4] = अणु
		luma_dc, luma_ac, chroma_dc, chroma_ac,
	पूर्ण;
	पूर्णांक ret = -EINVAL;

	huff = kzalloc(माप(*huff), GFP_KERNEL);
	अगर (!huff)
		वापस -ENOMEM;

	bits = huff_tअसल[tab_num];
	huffval = huff_tअसल[tab_num] + 16;

	maxsymbol = tab_num & 1 ? 256 : 16;

	/* Figure C.1 - Generation of table of Huffman code sizes */
	k = 0;
	क्रम (i = 1; i <= 16; i++) अणु
		j = bits[i - 1];
		अगर (k + j > maxsymbol)
			जाओ out;
		जबतक (j--)
			huff->size[k++] = i;
	पूर्ण
	lastk = k;

	/* Figure C.2 - Generation of table of Huffman codes */
	k = 0;
	code = 0;
	si = huff->size[0];
	जबतक (k < lastk) अणु
		जबतक (huff->size[k] == si) अणु
			huff->code[k++] = code;
			code++;
		पूर्ण
		अगर (code >= (1 << si))
			जाओ out;
		code <<= 1;
		si++;
	पूर्ण

	/* Figure C.3 - Ordering procedure क्रम encoding procedure code tables */
	क्रम (k = 0; k < lastk; k++) अणु
		i = huffval[k];
		अगर (i >= maxsymbol || ehufsi[i])
			जाओ out;
		ehufco[i] = huff->code[k];
		ehufsi[i] = huff->size[k];
	पूर्ण

	ret = 0;
out:
	kमुक्त(huff);
	वापस ret;
पूर्ण

#घोषणा DC_TABLE_INDEX0		    0
#घोषणा AC_TABLE_INDEX0		    1
#घोषणा DC_TABLE_INDEX1		    2
#घोषणा AC_TABLE_INDEX1		    3

अटल u8 *coda9_jpeg_get_huff_bits(काष्ठा coda_ctx *ctx, पूर्णांक tab_num)
अणु
	काष्ठा coda_huff_tab *huff_tab = ctx->params.jpeg_huff_tab;

	अगर (!huff_tab)
		वापस शून्य;

	चयन (tab_num) अणु
	हाल DC_TABLE_INDEX0: वापस huff_tab->luma_dc;
	हाल AC_TABLE_INDEX0: वापस huff_tab->luma_ac;
	हाल DC_TABLE_INDEX1: वापस huff_tab->chroma_dc;
	हाल AC_TABLE_INDEX1: वापस huff_tab->chroma_ac;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक coda9_jpeg_gen_dec_huff_tab(काष्ठा coda_ctx *ctx, पूर्णांक tab_num)
अणु
	पूर्णांक ptr_cnt = 0, huff_code = 0, zero_flag = 0, data_flag = 0;
	u8 *huff_bits;
	s16 *huff_max;
	s16 *huff_min;
	s8 *huff_ptr;
	पूर्णांक ofs;
	पूर्णांक i;

	huff_bits = coda9_jpeg_get_huff_bits(ctx, tab_num);
	अगर (!huff_bits)
		वापस -EINVAL;

	/* DC/AC Luma, DC/AC Chroma -> DC Luma/Chroma, AC Luma/Chroma */
	ofs = ((tab_num & 1) << 1) | ((tab_num >> 1) & 1);
	ofs *= 16;

	huff_ptr = ctx->params.jpeg_huff_tab->ptr + ofs;
	huff_max = ctx->params.jpeg_huff_tab->max + ofs;
	huff_min = ctx->params.jpeg_huff_tab->min + ofs;

	क्रम (i = 0; i < 16; i++) अणु
		अगर (huff_bits[i]) अणु
			huff_ptr[i] = ptr_cnt;
			ptr_cnt += huff_bits[i];
			huff_min[i] = huff_code;
			huff_max[i] = huff_code + (huff_bits[i] - 1);
			data_flag = 1;
			zero_flag = 0;
		पूर्ण अन्यथा अणु
			huff_ptr[i] = -1;
			huff_min[i] = -1;
			huff_max[i] = -1;
			zero_flag = 1;
		पूर्ण

		अगर (data_flag == 1) अणु
			अगर (zero_flag == 1)
				huff_code <<= 1;
			अन्यथा
				huff_code = (huff_max[i] + 1) << 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक coda9_jpeg_load_huff_tab(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा अणु
		पूर्णांक size[4][256];
		पूर्णांक code[4][256];
	पूर्ण *huff;
	u32 *huff_data;
	पूर्णांक i, j;
	पूर्णांक ret;

	huff = kzalloc(माप(*huff), GFP_KERNEL);
	अगर (!huff)
		वापस -ENOMEM;

	/* Generate all four (luma/chroma DC/AC) code/size lookup tables */
	क्रम (i = 0; i < 4; i++) अणु
		ret = coda9_jpeg_gen_enc_huff_tab(ctx, i, huff->size[i],
						  huff->code[i]);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (!ctx->params.jpeg_huff_data) अणु
		ctx->params.jpeg_huff_data =
			kzalloc(माप(u32) * CODA9_JPEG_ENC_HUFF_DATA_SIZE,
				GFP_KERNEL);
		अगर (!ctx->params.jpeg_huff_data) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण
	huff_data = ctx->params.jpeg_huff_data;

	क्रम (j = 0; j < 4; j++) अणु
		/* Store Huffman lookup tables in AC0, AC1, DC0, DC1 order */
		पूर्णांक t = (j == 0) ? AC_TABLE_INDEX0 :
			(j == 1) ? AC_TABLE_INDEX1 :
			(j == 2) ? DC_TABLE_INDEX0 :
				   DC_TABLE_INDEX1;
		/* DC tables only have 16 entries */
		पूर्णांक len = (j < 2) ? 256 : 16;

		क्रम (i = 0; i < len; i++) अणु
			अगर (huff->size[t][i] == 0 && huff->code[t][i] == 0)
				*(huff_data++) = 0;
			अन्यथा
				*(huff_data++) =
					((huff->size[t][i] - 1) << 16) |
					huff->code[t][i];
		पूर्ण
	पूर्ण

	ret = 0;
out:
	kमुक्त(huff);
	वापस ret;
पूर्ण

अटल व्योम coda9_jpeg_ग_लिखो_huff_tab(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	u32 *huff_data = ctx->params.jpeg_huff_data;
	पूर्णांक i;

	/* Write Huffman size/code lookup tables in AC0, AC1, DC0, DC1 order */
	coda_ग_लिखो(dev, 0x3, CODA9_REG_JPEG_HUFF_CTRL);
	क्रम (i = 0; i < CODA9_JPEG_ENC_HUFF_DATA_SIZE; i++)
		coda_ग_लिखो(dev, *(huff_data++), CODA9_REG_JPEG_HUFF_DATA);
	coda_ग_लिखो(dev, 0x0, CODA9_REG_JPEG_HUFF_CTRL);
पूर्ण

अटल अंतरभूत व्योम coda9_jpeg_ग_लिखो_qmat_quotients(काष्ठा coda_dev *dev,
						   u8 *qmat, पूर्णांक index)
अणु
	पूर्णांक i;

	coda_ग_लिखो(dev, index | 0x3, CODA9_REG_JPEG_QMAT_CTRL);
	क्रम (i = 0; i < 64; i++)
		coda_ग_लिखो(dev, 0x80000 / qmat[i], CODA9_REG_JPEG_QMAT_DATA);
	coda_ग_लिखो(dev, index, CODA9_REG_JPEG_QMAT_CTRL);
पूर्ण

अटल व्योम coda9_jpeg_load_qmat_tab(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	u8 *luma_tab;
	u8 *chroma_tab;

	luma_tab = ctx->params.jpeg_qmat_tab[0];
	अगर (!luma_tab)
		luma_tab = luma_q;

	chroma_tab = ctx->params.jpeg_qmat_tab[1];
	अगर (!chroma_tab)
		chroma_tab = chroma_q;

	coda9_jpeg_ग_लिखो_qmat_quotients(dev, luma_tab, 0x00);
	coda9_jpeg_ग_लिखो_qmat_quotients(dev, chroma_tab, 0x40);
	coda9_jpeg_ग_लिखो_qmat_quotients(dev, chroma_tab, 0x80);
पूर्ण

काष्ठा coda_jpeg_stream अणु
	u8 *curr;
	u8 *end;
पूर्ण;

अटल अंतरभूत पूर्णांक coda_jpeg_put_byte(u8 byte, काष्ठा coda_jpeg_stream *stream)
अणु
	अगर (stream->curr >= stream->end)
		वापस -EINVAL;

	*stream->curr++ = byte;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक coda_jpeg_put_word(u16 word, काष्ठा coda_jpeg_stream *stream)
अणु
	अगर (stream->curr + माप(__be16) > stream->end)
		वापस -EINVAL;

	put_unaligned_be16(word, stream->curr);
	stream->curr += माप(__be16);

	वापस 0;
पूर्ण

अटल पूर्णांक coda_jpeg_put_table(u16 marker, u8 index, स्थिर u8 *table,
			       माप_प्रकार len, काष्ठा coda_jpeg_stream *stream)
अणु
	पूर्णांक i, ret;

	ret = coda_jpeg_put_word(marker, stream);
	अगर (ret < 0)
		वापस ret;
	ret = coda_jpeg_put_word(3 + len, stream);
	अगर (ret < 0)
		वापस ret;
	ret = coda_jpeg_put_byte(index, stream);
	क्रम (i = 0; i < len && ret == 0; i++)
		ret = coda_jpeg_put_byte(table[i], stream);

	वापस ret;
पूर्ण

अटल पूर्णांक coda_jpeg_define_quantization_table(काष्ठा coda_ctx *ctx, u8 index,
					       काष्ठा coda_jpeg_stream *stream)
अणु
	वापस coda_jpeg_put_table(DQT_MARKER, index,
				   ctx->params.jpeg_qmat_tab[index], 64,
				   stream);
पूर्ण

अटल पूर्णांक coda_jpeg_define_huffman_table(u8 index, स्थिर u8 *table, माप_प्रकार len,
					  काष्ठा coda_jpeg_stream *stream)
अणु
	वापस coda_jpeg_put_table(DHT_MARKER, index, table, len, stream);
पूर्ण

अटल पूर्णांक coda9_jpeg_encode_header(काष्ठा coda_ctx *ctx, पूर्णांक len, u8 *buf)
अणु
	काष्ठा coda_jpeg_stream stream = अणु buf, buf + len पूर्ण;
	काष्ठा coda_q_data *q_data_src;
	पूर्णांक chroma_क्रमmat, comp_num;
	पूर्णांक i, ret, pad;

	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	chroma_क्रमmat = coda9_jpeg_chroma_क्रमmat(q_data_src->fourcc);
	अगर (chroma_क्रमmat < 0)
		वापस 0;

	/* Start Of Image */
	ret = coda_jpeg_put_word(SOI_MARKER, &stream);
	अगर (ret < 0)
		वापस ret;

	/* Define Restart Interval */
	अगर (ctx->params.jpeg_restart_पूर्णांकerval) अणु
		ret = coda_jpeg_put_word(DRI_MARKER, &stream);
		अगर (ret < 0)
			वापस ret;
		ret = coda_jpeg_put_word(4, &stream);
		अगर (ret < 0)
			वापस ret;
		ret = coda_jpeg_put_word(ctx->params.jpeg_restart_पूर्णांकerval,
					 &stream);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Define Quantization Tables */
	ret = coda_jpeg_define_quantization_table(ctx, 0x00, &stream);
	अगर (ret < 0)
		वापस ret;
	अगर (chroma_क्रमmat != CODA9_JPEG_FORMAT_400) अणु
		ret = coda_jpeg_define_quantization_table(ctx, 0x01, &stream);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Define Huffman Tables */
	ret = coda_jpeg_define_huffman_table(0x00, luma_dc, 16 + 12, &stream);
	अगर (ret < 0)
		वापस ret;
	ret = coda_jpeg_define_huffman_table(0x10, luma_ac, 16 + 162, &stream);
	अगर (ret < 0)
		वापस ret;
	अगर (chroma_क्रमmat != CODA9_JPEG_FORMAT_400) अणु
		ret = coda_jpeg_define_huffman_table(0x01, chroma_dc, 16 + 12,
						     &stream);
		अगर (ret < 0)
			वापस ret;
		ret = coda_jpeg_define_huffman_table(0x11, chroma_ac, 16 + 162,
						     &stream);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Start Of Frame */
	ret = coda_jpeg_put_word(SOF_MARKER, &stream);
	अगर (ret < 0)
		वापस ret;
	comp_num = (chroma_क्रमmat == CODA9_JPEG_FORMAT_400) ? 1 : 3;
	ret = coda_jpeg_put_word(8 + comp_num * 3, &stream);
	अगर (ret < 0)
		वापस ret;
	ret = coda_jpeg_put_byte(0x08, &stream);
	अगर (ret < 0)
		वापस ret;
	ret = coda_jpeg_put_word(q_data_src->height, &stream);
	अगर (ret < 0)
		वापस ret;
	ret = coda_jpeg_put_word(q_data_src->width, &stream);
	अगर (ret < 0)
		वापस ret;
	ret = coda_jpeg_put_byte(comp_num, &stream);
	अगर (ret < 0)
		वापस ret;
	क्रम (i = 0; i < comp_num; i++) अणु
		अटल अचिन्हित अक्षर subsampling[5][3] = अणु
			[CODA9_JPEG_FORMAT_420] = अणु 0x22, 0x11, 0x11 पूर्ण,
			[CODA9_JPEG_FORMAT_422] = अणु 0x21, 0x11, 0x11 पूर्ण,
			[CODA9_JPEG_FORMAT_224] = अणु 0x12, 0x11, 0x11 पूर्ण,
			[CODA9_JPEG_FORMAT_444] = अणु 0x11, 0x11, 0x11 पूर्ण,
			[CODA9_JPEG_FORMAT_400] = अणु 0x11 पूर्ण,
		पूर्ण;

		/* Component identअगरier, matches SOS */
		ret = coda_jpeg_put_byte(i + 1, &stream);
		अगर (ret < 0)
			वापस ret;
		ret = coda_jpeg_put_byte(subsampling[chroma_क्रमmat][i],
					 &stream);
		अगर (ret < 0)
			वापस ret;
		/* Chroma table index */
		ret = coda_jpeg_put_byte((i == 0) ? 0 : 1, &stream);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Pad to multiple of 8 bytes */
	pad = (stream.curr - buf) % 8;
	अगर (pad) अणु
		pad = 8 - pad;
		जबतक (pad--) अणु
			ret = coda_jpeg_put_byte(0x00, &stream);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस stream.curr - buf;
पूर्ण

/*
 * Scale quantization table using nonlinear scaling factor
 * u8 qtab[64], scale [50,190]
 */
अटल व्योम coda_scale_quant_table(u8 *q_tab, पूर्णांक scale)
अणु
	अचिन्हित पूर्णांक temp;
	पूर्णांक i;

	क्रम (i = 0; i < 64; i++) अणु
		temp = DIV_ROUND_CLOSEST((अचिन्हित पूर्णांक)q_tab[i] * scale, 100);
		अगर (temp <= 0)
			temp = 1;
		अगर (temp > 255)
			temp = 255;
		q_tab[i] = (अचिन्हित अक्षर)temp;
	पूर्ण
पूर्ण

व्योम coda_set_jpeg_compression_quality(काष्ठा coda_ctx *ctx, पूर्णांक quality)
अणु
	अचिन्हित पूर्णांक scale;

	ctx->params.jpeg_quality = quality;

	/* Clip quality setting to [5,100] पूर्णांकerval */
	अगर (quality > 100)
		quality = 100;
	अगर (quality < 5)
		quality = 5;

	/*
	 * Non-linear scaling factor:
	 * [5,50] -> [1000..100], [51,100] -> [98..0]
	 */
	अगर (quality < 50)
		scale = 5000 / quality;
	अन्यथा
		scale = 200 - 2 * quality;

	अगर (ctx->params.jpeg_qmat_tab[0]) अणु
		स_नकल(ctx->params.jpeg_qmat_tab[0], luma_q, 64);
		coda_scale_quant_table(ctx->params.jpeg_qmat_tab[0], scale);
	पूर्ण
	अगर (ctx->params.jpeg_qmat_tab[1]) अणु
		स_नकल(ctx->params.jpeg_qmat_tab[1], chroma_q, 64);
		coda_scale_quant_table(ctx->params.jpeg_qmat_tab[1], scale);
	पूर्ण
पूर्ण

/*
 * Encoder context operations
 */

अटल पूर्णांक coda9_jpeg_start_encoding(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	पूर्णांक ret;

	ret = coda9_jpeg_load_huff_tab(ctx);
	अगर (ret < 0) अणु
		v4l2_err(&dev->v4l2_dev, "error loading Huffman tables\n");
		वापस ret;
	पूर्ण
	अगर (!ctx->params.jpeg_qmat_tab[0])
		ctx->params.jpeg_qmat_tab[0] = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!ctx->params.jpeg_qmat_tab[1])
		ctx->params.jpeg_qmat_tab[1] = kदो_स्मृति(64, GFP_KERNEL);
	coda_set_jpeg_compression_quality(ctx, ctx->params.jpeg_quality);

	वापस 0;
पूर्ण

अटल पूर्णांक coda9_jpeg_prepare_encode(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_q_data *q_data_src;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा coda_dev *dev = ctx->dev;
	u32 start_addr, end_addr;
	u16 aligned_width, aligned_height;
	bool chroma_पूर्णांकerleave;
	पूर्णांक chroma_क्रमmat;
	पूर्णांक header_len;
	पूर्णांक ret;
	kसमय_प्रकार समयout;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);

	अगर (vb2_get_plane_payload(&src_buf->vb2_buf, 0) == 0)
		vb2_set_plane_payload(&src_buf->vb2_buf, 0,
				      vb2_plane_size(&src_buf->vb2_buf, 0));

	src_buf->sequence = ctx->osequence;
	dst_buf->sequence = ctx->osequence;
	ctx->osequence++;

	src_buf->flags |= V4L2_BUF_FLAG_KEYFRAME;
	src_buf->flags &= ~V4L2_BUF_FLAG_PFRAME;

	coda_set_gdi_regs(ctx);

	start_addr = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
	end_addr = start_addr + vb2_plane_size(&dst_buf->vb2_buf, 0);

	chroma_क्रमmat = coda9_jpeg_chroma_क्रमmat(q_data_src->fourcc);
	अगर (chroma_क्रमmat < 0)
		वापस chroma_क्रमmat;

	/* Round image dimensions to multiple of MCU size */
	aligned_width = round_up(q_data_src->width, width_align[chroma_क्रमmat]);
	aligned_height = round_up(q_data_src->height,
				  height_align[chroma_क्रमmat]);
	अगर (aligned_width != q_data_src->bytesperline) अणु
		v4l2_err(&dev->v4l2_dev, "wrong stride: %d instead of %d\n",
			 aligned_width, q_data_src->bytesperline);
	पूर्ण

	header_len =
		coda9_jpeg_encode_header(ctx,
					 vb2_plane_size(&dst_buf->vb2_buf, 0),
					 vb2_plane_vaddr(&dst_buf->vb2_buf, 0));
	अगर (header_len < 0)
		वापस header_len;

	coda_ग_लिखो(dev, start_addr + header_len, CODA9_REG_JPEG_BBC_BAS_ADDR);
	coda_ग_लिखो(dev, end_addr, CODA9_REG_JPEG_BBC_END_ADDR);
	coda_ग_लिखो(dev, start_addr + header_len, CODA9_REG_JPEG_BBC_WR_PTR);
	coda_ग_लिखो(dev, start_addr + header_len, CODA9_REG_JPEG_BBC_RD_PTR);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_BBC_CUR_POS);
	/* 64 words per 256-byte page */
	coda_ग_लिखो(dev, 64, CODA9_REG_JPEG_BBC_DATA_CNT);
	coda_ग_लिखो(dev, start_addr, CODA9_REG_JPEG_BBC_EXT_ADDR);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_BBC_INT_ADDR);

	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_GBU_BT_PTR);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_GBU_WD_PTR);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_GBU_BBSR);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_BBC_STRM_CTRL);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_GBU_CTRL);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_GBU_FF_RPTR);
	coda_ग_लिखो(dev, 127, CODA9_REG_JPEG_GBU_BBER);
	coda_ग_लिखो(dev, 64, CODA9_REG_JPEG_GBU_BBIR);
	coda_ग_लिखो(dev, 64, CODA9_REG_JPEG_GBU_BBHR);

	chroma_पूर्णांकerleave = (q_data_src->fourcc == V4L2_PIX_FMT_NV12);
	coda_ग_लिखो(dev, CODA9_JPEG_PIC_CTRL_TC_सूचीECTION |
		   CODA9_JPEG_PIC_CTRL_ENCODER_EN, CODA9_REG_JPEG_PIC_CTRL);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_SCL_INFO);
	coda_ग_लिखो(dev, chroma_पूर्णांकerleave, CODA9_REG_JPEG_DPB_CONFIG);
	coda_ग_लिखो(dev, ctx->params.jpeg_restart_पूर्णांकerval,
		   CODA9_REG_JPEG_RST_INTVAL);
	coda_ग_लिखो(dev, 1, CODA9_REG_JPEG_BBC_CTRL);

	coda_ग_लिखो(dev, bus_req_num[chroma_क्रमmat], CODA9_REG_JPEG_OP_INFO);

	coda9_jpeg_ग_लिखो_huff_tab(ctx);
	coda9_jpeg_load_qmat_tab(ctx);

	अगर (ctx->params.rot_mode & CODA_ROT_90) अणु
		aligned_width = aligned_height;
		aligned_height = q_data_src->bytesperline;
		अगर (chroma_क्रमmat == CODA9_JPEG_FORMAT_422)
			chroma_क्रमmat = CODA9_JPEG_FORMAT_224;
		अन्यथा अगर (chroma_क्रमmat == CODA9_JPEG_FORMAT_224)
			chroma_क्रमmat = CODA9_JPEG_FORMAT_422;
	पूर्ण
	/* These need to be multiples of MCU size */
	coda_ग_लिखो(dev, aligned_width << 16 | aligned_height,
		   CODA9_REG_JPEG_PIC_SIZE);
	coda_ग_लिखो(dev, ctx->params.rot_mode ?
		   (CODA_ROT_MIR_ENABLE | ctx->params.rot_mode) : 0,
		   CODA9_REG_JPEG_ROT_INFO);

	coda_ग_लिखो(dev, mcu_info[chroma_क्रमmat], CODA9_REG_JPEG_MCU_INFO);

	coda_ग_लिखो(dev, 1, CODA9_GDI_CONTROL);
	समयout = kसमय_add_us(kसमय_get(), 100000);
	करो अणु
		ret = coda_पढ़ो(dev, CODA9_GDI_STATUS);
		अगर (kसमय_compare(kसमय_get(), समयout) > 0) अणु
			v4l2_err(&dev->v4l2_dev, "timeout waiting for GDI\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण जबतक (!ret);

	coda_ग_लिखो(dev, (chroma_क्रमmat << 17) | (chroma_पूर्णांकerleave << 16) |
		   q_data_src->bytesperline, CODA9_GDI_INFO_CONTROL);
	/* The content of this रेजिस्टर seems to be irrelevant: */
	coda_ग_लिखो(dev, aligned_width << 16 | aligned_height,
		   CODA9_GDI_INFO_PIC_SIZE);

	coda_ग_लिखो_base(ctx, q_data_src, src_buf, CODA9_GDI_INFO_BASE_Y);

	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_DPB_BASE00);
	coda_ग_लिखो(dev, 0, CODA9_GDI_CONTROL);
	coda_ग_लिखो(dev, 1, CODA9_GDI_PIC_INIT_HOST);

	coda_ग_लिखो(dev, 1, CODA9_GDI_WPROT_ERR_CLR);
	coda_ग_लिखो(dev, 0, CODA9_GDI_WPROT_RGN_EN);

	trace_coda_jpeg_run(ctx, src_buf);

	coda_ग_लिखो(dev, 1, CODA9_REG_JPEG_PIC_START);

	वापस 0;
पूर्ण

अटल व्योम coda9_jpeg_finish_encode(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा coda_dev *dev = ctx->dev;
	u32 wr_ptr, start_ptr;
	u32 err_mb;

	अगर (ctx->पातing) अणु
		coda_ग_लिखो(ctx->dev, 0, CODA9_REG_JPEG_BBC_FLUSH_CMD);
		वापस;
	पूर्ण

	/*
	 * Lock to make sure that an encoder stop command running in parallel
	 * will either alपढ़ोy have marked src_buf as last, or it will wake up
	 * the capture queue after the buffers are वापसed.
	 */
	mutex_lock(&ctx->wakeup_mutex);
	src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

	trace_coda_jpeg_करोne(ctx, dst_buf);

	/*
	 * Set plane payload to the number of bytes written out
	 * by the JPEG processing unit
	 */
	start_ptr = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
	wr_ptr = coda_पढ़ो(dev, CODA9_REG_JPEG_BBC_WR_PTR);
	vb2_set_plane_payload(&dst_buf->vb2_buf, 0, wr_ptr - start_ptr);

	err_mb = coda_पढ़ो(dev, CODA9_REG_JPEG_PIC_ERRMB);
	अगर (err_mb)
		coda_dbg(1, ctx, "ERRMB: 0x%x\n", err_mb);

	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_BBC_FLUSH_CMD);

	dst_buf->flags &= ~(V4L2_BUF_FLAG_PFRAME | V4L2_BUF_FLAG_LAST);
	dst_buf->flags |= V4L2_BUF_FLAG_KEYFRAME;
	dst_buf->flags |= src_buf->flags & V4L2_BUF_FLAG_LAST;

	v4l2_m2m_buf_copy_metadata(src_buf, dst_buf, false);

	v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);
	coda_m2m_buf_करोne(ctx, dst_buf, err_mb ? VB2_BUF_STATE_ERROR :
						 VB2_BUF_STATE_DONE);
	mutex_unlock(&ctx->wakeup_mutex);

	coda_dbg(1, ctx, "job finished: encoded frame (%u)%s\n",
		 dst_buf->sequence,
		 (dst_buf->flags & V4L2_BUF_FLAG_LAST) ? " (last)" : "");

	/*
	 * Reset JPEG processing unit after each encode run to work
	 * around hangups when चयनing context between encoder and
	 * decoder.
	 */
	coda_hw_reset(ctx);
पूर्ण

अटल व्योम coda9_jpeg_release(काष्ठा coda_ctx *ctx)
अणु
	पूर्णांक i;

	अगर (ctx->params.jpeg_qmat_tab[0] == luma_q)
		ctx->params.jpeg_qmat_tab[0] = शून्य;
	अगर (ctx->params.jpeg_qmat_tab[1] == chroma_q)
		ctx->params.jpeg_qmat_tab[1] = शून्य;
	क्रम (i = 0; i < 3; i++)
		kमुक्त(ctx->params.jpeg_qmat_tab[i]);
	kमुक्त(ctx->params.jpeg_huff_data);
	kमुक्त(ctx->params.jpeg_huff_tab);
पूर्ण

स्थिर काष्ठा coda_context_ops coda9_jpeg_encode_ops = अणु
	.queue_init = coda_encoder_queue_init,
	.start_streaming = coda9_jpeg_start_encoding,
	.prepare_run = coda9_jpeg_prepare_encode,
	.finish_run = coda9_jpeg_finish_encode,
	.release = coda9_jpeg_release,
पूर्ण;

/*
 * Decoder context operations
 */

अटल पूर्णांक coda9_jpeg_start_decoding(काष्ठा coda_ctx *ctx)
अणु
	ctx->params.jpeg_qmat_index[0] = 0;
	ctx->params.jpeg_qmat_index[1] = 1;
	ctx->params.jpeg_qmat_index[2] = 1;
	ctx->params.jpeg_qmat_tab[0] = luma_q;
	ctx->params.jpeg_qmat_tab[1] = chroma_q;
	/* nothing more to करो here */

	/* TODO: we could alपढ़ोy scan the first header to get the chroma
	 * क्रमmat.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक coda9_jpeg_prepare_decode(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	पूर्णांक aligned_width, aligned_height;
	पूर्णांक chroma_क्रमmat;
	पूर्णांक ret;
	u32 val, dst_fourcc;
	काष्ठा coda_q_data *q_data_src, *q_data_dst;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	पूर्णांक chroma_पूर्णांकerleave;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	dst_fourcc = q_data_dst->fourcc;

	अगर (vb2_get_plane_payload(&src_buf->vb2_buf, 0) == 0)
		vb2_set_plane_payload(&src_buf->vb2_buf, 0,
				      vb2_plane_size(&src_buf->vb2_buf, 0));

	chroma_क्रमmat = coda9_jpeg_chroma_क्रमmat(q_data_dst->fourcc);
	अगर (chroma_क्रमmat < 0) अणु
		v4l2_m2m_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx);
		वापस chroma_क्रमmat;
	पूर्ण

	ret = coda_jpeg_decode_header(ctx, &src_buf->vb2_buf);
	अगर (ret < 0) अणु
		v4l2_err(&dev->v4l2_dev, "failed to decode JPEG header: %d\n",
			 ret);

		src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);
		v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_DONE);

		v4l2_m2m_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx);
		वापस ret;
	पूर्ण

	/* Round image dimensions to multiple of MCU size */
	aligned_width = round_up(q_data_src->width, width_align[chroma_क्रमmat]);
	aligned_height = round_up(q_data_src->height, height_align[chroma_क्रमmat]);
	अगर (aligned_width != q_data_dst->bytesperline) अणु
		v4l2_err(&dev->v4l2_dev, "stride mismatch: %d != %d\n",
			 aligned_width, q_data_dst->bytesperline);
	पूर्ण

	coda_set_gdi_regs(ctx);

	val = ctx->params.jpeg_huff_ac_index[0] << 12 |
	      ctx->params.jpeg_huff_ac_index[1] << 11 |
	      ctx->params.jpeg_huff_ac_index[2] << 10 |
	      ctx->params.jpeg_huff_dc_index[0] << 9 |
	      ctx->params.jpeg_huff_dc_index[1] << 8 |
	      ctx->params.jpeg_huff_dc_index[2] << 7;
	अगर (ctx->params.jpeg_huff_tab)
		val |= CODA9_JPEG_PIC_CTRL_USER_HUFFMAN_EN;
	coda_ग_लिखो(dev, val, CODA9_REG_JPEG_PIC_CTRL);

	coda_ग_लिखो(dev, aligned_width << 16 | aligned_height,
			CODA9_REG_JPEG_PIC_SIZE);

	chroma_पूर्णांकerleave = (dst_fourcc == V4L2_PIX_FMT_NV12);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_ROT_INFO);
	coda_ग_लिखो(dev, bus_req_num[chroma_क्रमmat], CODA9_REG_JPEG_OP_INFO);
	coda_ग_लिखो(dev, mcu_info[chroma_क्रमmat], CODA9_REG_JPEG_MCU_INFO);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_SCL_INFO);
	coda_ग_लिखो(dev, chroma_पूर्णांकerleave, CODA9_REG_JPEG_DPB_CONFIG);
	coda_ग_लिखो(dev, ctx->params.jpeg_restart_पूर्णांकerval,
			CODA9_REG_JPEG_RST_INTVAL);

	अगर (ctx->params.jpeg_huff_tab) अणु
		ret = coda9_jpeg_dec_huff_setup(ctx);
		अगर (ret < 0) अणु
			v4l2_err(&dev->v4l2_dev,
				 "failed to set up Huffman tables: %d\n", ret);
			v4l2_m2m_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx);
			वापस ret;
		पूर्ण
	पूर्ण

	coda9_jpeg_qmat_setup(ctx);

	coda9_jpeg_dec_bbc_gbu_setup(ctx, &src_buf->vb2_buf,
				     ctx->jpeg_ecs_offset);

	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_RST_INDEX);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_RST_COUNT);

	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_DPCM_DIFF_Y);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_DPCM_DIFF_CB);
	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_DPCM_DIFF_CR);

	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_ROT_INFO);

	coda_ग_लिखो(dev, 1, CODA9_GDI_CONTROL);
	करो अणु
		ret = coda_पढ़ो(dev, CODA9_GDI_STATUS);
	पूर्ण जबतक (!ret);

	val = (chroma_क्रमmat << 17) | (chroma_पूर्णांकerleave << 16) |
	      q_data_dst->bytesperline;
	अगर (ctx->tiled_map_type == GDI_TILED_FRAME_MB_RASTER_MAP)
		val |= 3 << 20;
	coda_ग_लिखो(dev, val, CODA9_GDI_INFO_CONTROL);

	coda_ग_लिखो(dev, aligned_width << 16 | aligned_height,
			CODA9_GDI_INFO_PIC_SIZE);

	coda_ग_लिखो_base(ctx, q_data_dst, dst_buf, CODA9_GDI_INFO_BASE_Y);

	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_DPB_BASE00);
	coda_ग_लिखो(dev, 0, CODA9_GDI_CONTROL);
	coda_ग_लिखो(dev, 1, CODA9_GDI_PIC_INIT_HOST);

	trace_coda_jpeg_run(ctx, src_buf);

	coda_ग_लिखो(dev, 1, CODA9_REG_JPEG_PIC_START);

	वापस 0;
पूर्ण

अटल व्योम coda9_jpeg_finish_decode(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	काष्ठा vb2_v4l2_buffer *dst_buf, *src_buf;
	काष्ठा coda_q_data *q_data_dst;
	u32 err_mb;

	err_mb = coda_पढ़ो(dev, CODA9_REG_JPEG_PIC_ERRMB);
	अगर (err_mb)
		v4l2_err(&dev->v4l2_dev, "ERRMB: 0x%x\n", err_mb);

	coda_ग_लिखो(dev, 0, CODA9_REG_JPEG_BBC_FLUSH_CMD);

	/*
	 * Lock to make sure that a decoder stop command running in parallel
	 * will either alपढ़ोy have marked src_buf as last, or it will wake up
	 * the capture queue after the buffers are वापसed.
	 */
	mutex_lock(&ctx->wakeup_mutex);
	src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_buf->sequence = ctx->osequence++;

	trace_coda_jpeg_करोne(ctx, dst_buf);

	dst_buf->flags &= ~(V4L2_BUF_FLAG_PFRAME | V4L2_BUF_FLAG_LAST);
	dst_buf->flags |= V4L2_BUF_FLAG_KEYFRAME;
	dst_buf->flags |= src_buf->flags & V4L2_BUF_FLAG_LAST;

	v4l2_m2m_buf_copy_metadata(src_buf, dst_buf, false);

	q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	vb2_set_plane_payload(&dst_buf->vb2_buf, 0, q_data_dst->sizeimage);

	v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);
	coda_m2m_buf_करोne(ctx, dst_buf, err_mb ? VB2_BUF_STATE_ERROR :
						 VB2_BUF_STATE_DONE);

	mutex_unlock(&ctx->wakeup_mutex);

	coda_dbg(1, ctx, "job finished: decoded frame (%u)%s\n",
		 dst_buf->sequence,
		 (dst_buf->flags & V4L2_BUF_FLAG_LAST) ? " (last)" : "");

	/*
	 * Reset JPEG processing unit after each decode run to work
	 * around hangups when चयनing context between encoder and
	 * decoder.
	 */
	coda_hw_reset(ctx);
पूर्ण

स्थिर काष्ठा coda_context_ops coda9_jpeg_decode_ops = अणु
	.queue_init = coda_encoder_queue_init, /* non-bitstream operation */
	.start_streaming = coda9_jpeg_start_decoding,
	.prepare_run = coda9_jpeg_prepare_decode,
	.finish_run = coda9_jpeg_finish_decode,
	.release = coda9_jpeg_release,
पूर्ण;

irqवापस_t coda9_jpeg_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा coda_dev *dev = data;
	काष्ठा coda_ctx *ctx;
	पूर्णांक status;
	पूर्णांक err_mb;

	status = coda_पढ़ो(dev, CODA9_REG_JPEG_PIC_STATUS);
	अगर (status == 0)
		वापस IRQ_HANDLED;
	coda_ग_लिखो(dev, status, CODA9_REG_JPEG_PIC_STATUS);

	अगर (status & CODA9_JPEG_STATUS_OVERFLOW)
		v4l2_err(&dev->v4l2_dev, "JPEG overflow\n");

	अगर (status & CODA9_JPEG_STATUS_BBC_INT)
		v4l2_err(&dev->v4l2_dev, "JPEG BBC interrupt\n");

	अगर (status & CODA9_JPEG_STATUS_ERROR) अणु
		v4l2_err(&dev->v4l2_dev, "JPEG error\n");

		err_mb = coda_पढ़ो(dev, CODA9_REG_JPEG_PIC_ERRMB);
		अगर (err_mb) अणु
			v4l2_err(&dev->v4l2_dev,
				 "ERRMB: 0x%x: rst idx %d, mcu pos (%d,%d)\n",
				 err_mb, err_mb >> 24, (err_mb >> 12) & 0xfff,
				 err_mb & 0xfff);
		पूर्ण
	पूर्ण

	ctx = v4l2_m2m_get_curr_priv(dev->m2m_dev);
	अगर (!ctx) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Instance released before the end of transaction\n");
		mutex_unlock(&dev->coda_mutex);
		वापस IRQ_HANDLED;
	पूर्ण

	complete(&ctx->completion);

	वापस IRQ_HANDLED;
पूर्ण
