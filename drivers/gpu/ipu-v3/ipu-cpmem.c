<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012 Mentor Graphics Inc.
 * Copyright 2005-2012 Freescale Semiconductor, Inc. All Rights Reserved.
 */
#समावेश <linux/types.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/पन.स>
#समावेश <linux/sizes.h>
#समावेश <drm/drm_fourcc.h>
#समावेश "ipu-prv.h"

काष्ठा ipu_cpmem_word अणु
	u32 data[5];
	u32 res[3];
पूर्ण;

काष्ठा ipu_ch_param अणु
	काष्ठा ipu_cpmem_word word[2];
पूर्ण;

काष्ठा ipu_cpmem अणु
	काष्ठा ipu_ch_param __iomem *base;
	u32 module;
	spinlock_t lock;
	पूर्णांक use_count;
	काष्ठा ipu_soc *ipu;
पूर्ण;

#घोषणा IPU_CPMEM_WORD(word, ofs, size) ((((word) * 160 + (ofs)) << 8) | (size))

#घोषणा IPU_FIELD_UBO		IPU_CPMEM_WORD(0, 46, 22)
#घोषणा IPU_FIELD_VBO		IPU_CPMEM_WORD(0, 68, 22)
#घोषणा IPU_FIELD_IOX		IPU_CPMEM_WORD(0, 90, 4)
#घोषणा IPU_FIELD_RDRW		IPU_CPMEM_WORD(0, 94, 1)
#घोषणा IPU_FIELD_SO		IPU_CPMEM_WORD(0, 113, 1)
#घोषणा IPU_FIELD_SLY		IPU_CPMEM_WORD(1, 102, 14)
#घोषणा IPU_FIELD_SLUV		IPU_CPMEM_WORD(1, 128, 14)

#घोषणा IPU_FIELD_XV		IPU_CPMEM_WORD(0, 0, 10)
#घोषणा IPU_FIELD_YV		IPU_CPMEM_WORD(0, 10, 9)
#घोषणा IPU_FIELD_XB		IPU_CPMEM_WORD(0, 19, 13)
#घोषणा IPU_FIELD_YB		IPU_CPMEM_WORD(0, 32, 12)
#घोषणा IPU_FIELD_NSB_B		IPU_CPMEM_WORD(0, 44, 1)
#घोषणा IPU_FIELD_CF		IPU_CPMEM_WORD(0, 45, 1)
#घोषणा IPU_FIELD_SX		IPU_CPMEM_WORD(0, 46, 12)
#घोषणा IPU_FIELD_SY		IPU_CPMEM_WORD(0, 58, 11)
#घोषणा IPU_FIELD_NS		IPU_CPMEM_WORD(0, 69, 10)
#घोषणा IPU_FIELD_SDX		IPU_CPMEM_WORD(0, 79, 7)
#घोषणा IPU_FIELD_SM		IPU_CPMEM_WORD(0, 86, 10)
#घोषणा IPU_FIELD_SCC		IPU_CPMEM_WORD(0, 96, 1)
#घोषणा IPU_FIELD_SCE		IPU_CPMEM_WORD(0, 97, 1)
#घोषणा IPU_FIELD_SDY		IPU_CPMEM_WORD(0, 98, 7)
#घोषणा IPU_FIELD_SDRX		IPU_CPMEM_WORD(0, 105, 1)
#घोषणा IPU_FIELD_SDRY		IPU_CPMEM_WORD(0, 106, 1)
#घोषणा IPU_FIELD_BPP		IPU_CPMEM_WORD(0, 107, 3)
#घोषणा IPU_FIELD_DEC_SEL	IPU_CPMEM_WORD(0, 110, 2)
#घोषणा IPU_FIELD_DIM		IPU_CPMEM_WORD(0, 112, 1)
#घोषणा IPU_FIELD_BNDM		IPU_CPMEM_WORD(0, 114, 3)
#घोषणा IPU_FIELD_BM		IPU_CPMEM_WORD(0, 117, 2)
#घोषणा IPU_FIELD_ROT		IPU_CPMEM_WORD(0, 119, 1)
#घोषणा IPU_FIELD_ROT_HF_VF	IPU_CPMEM_WORD(0, 119, 3)
#घोषणा IPU_FIELD_HF		IPU_CPMEM_WORD(0, 120, 1)
#घोषणा IPU_FIELD_VF		IPU_CPMEM_WORD(0, 121, 1)
#घोषणा IPU_FIELD_THE		IPU_CPMEM_WORD(0, 122, 1)
#घोषणा IPU_FIELD_CAP		IPU_CPMEM_WORD(0, 123, 1)
#घोषणा IPU_FIELD_CAE		IPU_CPMEM_WORD(0, 124, 1)
#घोषणा IPU_FIELD_FW		IPU_CPMEM_WORD(0, 125, 13)
#घोषणा IPU_FIELD_FH		IPU_CPMEM_WORD(0, 138, 12)
#घोषणा IPU_FIELD_EBA0		IPU_CPMEM_WORD(1, 0, 29)
#घोषणा IPU_FIELD_EBA1		IPU_CPMEM_WORD(1, 29, 29)
#घोषणा IPU_FIELD_ILO		IPU_CPMEM_WORD(1, 58, 20)
#घोषणा IPU_FIELD_NPB		IPU_CPMEM_WORD(1, 78, 7)
#घोषणा IPU_FIELD_PFS		IPU_CPMEM_WORD(1, 85, 4)
#घोषणा IPU_FIELD_ALU		IPU_CPMEM_WORD(1, 89, 1)
#घोषणा IPU_FIELD_ALBM		IPU_CPMEM_WORD(1, 90, 3)
#घोषणा IPU_FIELD_ID		IPU_CPMEM_WORD(1, 93, 2)
#घोषणा IPU_FIELD_TH		IPU_CPMEM_WORD(1, 95, 7)
#घोषणा IPU_FIELD_SL		IPU_CPMEM_WORD(1, 102, 14)
#घोषणा IPU_FIELD_WID0		IPU_CPMEM_WORD(1, 116, 3)
#घोषणा IPU_FIELD_WID1		IPU_CPMEM_WORD(1, 119, 3)
#घोषणा IPU_FIELD_WID2		IPU_CPMEM_WORD(1, 122, 3)
#घोषणा IPU_FIELD_WID3		IPU_CPMEM_WORD(1, 125, 3)
#घोषणा IPU_FIELD_OFS0		IPU_CPMEM_WORD(1, 128, 5)
#घोषणा IPU_FIELD_OFS1		IPU_CPMEM_WORD(1, 133, 5)
#घोषणा IPU_FIELD_OFS2		IPU_CPMEM_WORD(1, 138, 5)
#घोषणा IPU_FIELD_OFS3		IPU_CPMEM_WORD(1, 143, 5)
#घोषणा IPU_FIELD_SXYS		IPU_CPMEM_WORD(1, 148, 1)
#घोषणा IPU_FIELD_CRE		IPU_CPMEM_WORD(1, 149, 1)
#घोषणा IPU_FIELD_DEC_SEL2	IPU_CPMEM_WORD(1, 150, 1)

अटल अंतरभूत काष्ठा ipu_ch_param __iomem *
ipu_get_cpmem(काष्ठा ipuv3_channel *ch)
अणु
	काष्ठा ipu_cpmem *cpmem = ch->ipu->cpmem_priv;

	वापस cpmem->base + ch->num;
पूर्ण

अटल व्योम ipu_ch_param_ग_लिखो_field(काष्ठा ipuv3_channel *ch, u32 wbs, u32 v)
अणु
	काष्ठा ipu_ch_param __iomem *base = ipu_get_cpmem(ch);
	u32 bit = (wbs >> 8) % 160;
	u32 size = wbs & 0xff;
	u32 word = (wbs >> 8) / 160;
	u32 i = bit / 32;
	u32 ofs = bit % 32;
	u32 mask = (1 << size) - 1;
	u32 val;

	pr_debug("%s %d %d %d\n", __func__, word, bit , size);

	val = पढ़ोl(&base->word[word].data[i]);
	val &= ~(mask << ofs);
	val |= v << ofs;
	ग_लिखोl(val, &base->word[word].data[i]);

	अगर ((bit + size - 1) / 32 > i) अणु
		val = पढ़ोl(&base->word[word].data[i + 1]);
		val &= ~(mask >> (ofs ? (32 - ofs) : 0));
		val |= v >> (ofs ? (32 - ofs) : 0);
		ग_लिखोl(val, &base->word[word].data[i + 1]);
	पूर्ण
पूर्ण

अटल u32 ipu_ch_param_पढ़ो_field(काष्ठा ipuv3_channel *ch, u32 wbs)
अणु
	काष्ठा ipu_ch_param __iomem *base = ipu_get_cpmem(ch);
	u32 bit = (wbs >> 8) % 160;
	u32 size = wbs & 0xff;
	u32 word = (wbs >> 8) / 160;
	u32 i = bit / 32;
	u32 ofs = bit % 32;
	u32 mask = (1 << size) - 1;
	u32 val = 0;

	pr_debug("%s %d %d %d\n", __func__, word, bit , size);

	val = (पढ़ोl(&base->word[word].data[i]) >> ofs) & mask;

	अगर ((bit + size - 1) / 32 > i) अणु
		u32 पंचांगp;

		पंचांगp = पढ़ोl(&base->word[word].data[i + 1]);
		पंचांगp &= mask >> (ofs ? (32 - ofs) : 0);
		val |= पंचांगp << (ofs ? (32 - ofs) : 0);
	पूर्ण

	वापस val;
पूर्ण

/*
 * The V4L2 spec defines packed RGB क्रमmats in memory byte order, which from
 * poपूर्णांक of view of the IPU corresponds to little-endian words with the first
 * component in the least signअगरicant bits.
 * The DRM pixel क्रमmats and IPU पूर्णांकernal representation are ordered the other
 * way around, with the first named component ordered at the most signअगरicant
 * bits. Further, V4L2 क्रमmats are not well defined:
 *     https://linuxtv.org/करोwnloads/v4l-dvb-apis/packed-rgb.hपंचांगl
 * We choose the पूर्णांकerpretation which matches GStreamer behavior.
 */
अटल पूर्णांक v4l2_pix_fmt_to_drm_fourcc(u32 pixelक्रमmat)
अणु
	चयन (pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_RGB565:
		/*
		 * Here we choose the 'corrected' पूर्णांकerpretation of RGBP, a
		 * little-endian 16-bit word with the red component at the most
		 * signअगरicant bits:
		 * g[2:0]b[4:0] r[4:0]g[5:3] <=> [16:0] R:G:B
		 */
		वापस DRM_FORMAT_RGB565;
	हाल V4L2_PIX_FMT_BGR24:
		/* B G R <=> [24:0] R:G:B */
		वापस DRM_FORMAT_RGB888;
	हाल V4L2_PIX_FMT_RGB24:
		/* R G B <=> [24:0] B:G:R */
		वापस DRM_FORMAT_BGR888;
	हाल V4L2_PIX_FMT_BGR32:
		/* B G R A <=> [32:0] A:B:G:R */
		वापस DRM_FORMAT_XRGB8888;
	हाल V4L2_PIX_FMT_RGB32:
		/* R G B A <=> [32:0] A:B:G:R */
		वापस DRM_FORMAT_XBGR8888;
	हाल V4L2_PIX_FMT_ABGR32:
		/* B G R A <=> [32:0] A:R:G:B */
		वापस DRM_FORMAT_ARGB8888;
	हाल V4L2_PIX_FMT_XBGR32:
		/* B G R X <=> [32:0] X:R:G:B */
		वापस DRM_FORMAT_XRGB8888;
	हाल V4L2_PIX_FMT_BGRA32:
		/* A B G R <=> [32:0] R:G:B:A */
		वापस DRM_FORMAT_RGBA8888;
	हाल V4L2_PIX_FMT_BGRX32:
		/* X B G R <=> [32:0] R:G:B:X */
		वापस DRM_FORMAT_RGBX8888;
	हाल V4L2_PIX_FMT_RGBA32:
		/* R G B A <=> [32:0] A:B:G:R */
		वापस DRM_FORMAT_ABGR8888;
	हाल V4L2_PIX_FMT_RGBX32:
		/* R G B X <=> [32:0] X:B:G:R */
		वापस DRM_FORMAT_XBGR8888;
	हाल V4L2_PIX_FMT_ARGB32:
		/* A R G B <=> [32:0] B:G:R:A */
		वापस DRM_FORMAT_BGRA8888;
	हाल V4L2_PIX_FMT_XRGB32:
		/* X R G B <=> [32:0] B:G:R:X */
		वापस DRM_FORMAT_BGRX8888;
	हाल V4L2_PIX_FMT_UYVY:
		वापस DRM_FORMAT_UYVY;
	हाल V4L2_PIX_FMT_YUYV:
		वापस DRM_FORMAT_YUYV;
	हाल V4L2_PIX_FMT_YUV420:
		वापस DRM_FORMAT_YUV420;
	हाल V4L2_PIX_FMT_YUV422P:
		वापस DRM_FORMAT_YUV422;
	हाल V4L2_PIX_FMT_YVU420:
		वापस DRM_FORMAT_YVU420;
	हाल V4L2_PIX_FMT_NV12:
		वापस DRM_FORMAT_NV12;
	हाल V4L2_PIX_FMT_NV16:
		वापस DRM_FORMAT_NV16;
	पूर्ण

	वापस -EINVAL;
पूर्ण

व्योम ipu_cpmem_zero(काष्ठा ipuv3_channel *ch)
अणु
	काष्ठा ipu_ch_param __iomem *p = ipu_get_cpmem(ch);
	व्योम __iomem *base = p;
	पूर्णांक i;

	क्रम (i = 0; i < माप(*p) / माप(u32); i++)
		ग_लिखोl(0, base + i * माप(u32));
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_zero);

व्योम ipu_cpmem_set_resolution(काष्ठा ipuv3_channel *ch, पूर्णांक xres, पूर्णांक yres)
अणु
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_FW, xres - 1);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_FH, yres - 1);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_resolution);

व्योम ipu_cpmem_skip_odd_chroma_rows(काष्ठा ipuv3_channel *ch)
अणु
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_RDRW, 1);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_skip_odd_chroma_rows);

व्योम ipu_cpmem_set_stride(काष्ठा ipuv3_channel *ch, पूर्णांक stride)
अणु
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_SLY, stride - 1);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_stride);

व्योम ipu_cpmem_set_high_priority(काष्ठा ipuv3_channel *ch)
अणु
	काष्ठा ipu_soc *ipu = ch->ipu;
	u32 val;

	अगर (ipu->ipu_type == IPUV3EX)
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_ID, 1);

	val = ipu_idmac_पढ़ो(ipu, IDMAC_CHA_PRI(ch->num));
	val |= 1 << (ch->num % 32);
	ipu_idmac_ग_लिखो(ipu, val, IDMAC_CHA_PRI(ch->num));
पूर्ण;
EXPORT_SYMBOL_GPL(ipu_cpmem_set_high_priority);

व्योम ipu_cpmem_set_buffer(काष्ठा ipuv3_channel *ch, पूर्णांक bufnum, dma_addr_t buf)
अणु
	WARN_ON_ONCE(buf & 0x7);

	अगर (bufnum)
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_EBA1, buf >> 3);
	अन्यथा
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_EBA0, buf >> 3);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_buffer);

व्योम ipu_cpmem_set_uv_offset(काष्ठा ipuv3_channel *ch, u32 u_off, u32 v_off)
अणु
	WARN_ON_ONCE((u_off & 0x7) || (v_off & 0x7));

	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_UBO, u_off / 8);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_VBO, v_off / 8);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_uv_offset);

व्योम ipu_cpmem_पूर्णांकerlaced_scan(काष्ठा ipuv3_channel *ch, पूर्णांक stride,
			       u32 pixelक्रमmat)
अणु
	u32 ilo, sly, sluv;

	अगर (stride < 0) अणु
		stride = -stride;
		ilo = 0x100000 - (stride / 8);
	पूर्ण अन्यथा अणु
		ilo = stride / 8;
	पूर्ण

	sly = (stride * 2) - 1;

	चयन (pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
		sluv = stride / 2 - 1;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
		sluv = stride - 1;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:
		sluv = stride - 1;
		अवरोध;
	हाल V4L2_PIX_FMT_NV16:
		sluv = stride * 2 - 1;
		अवरोध;
	शेष:
		sluv = 0;
		अवरोध;
	पूर्ण

	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_SO, 1);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_ILO, ilo);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_SLY, sly);
	अगर (sluv)
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_SLUV, sluv);
पूर्ण;
EXPORT_SYMBOL_GPL(ipu_cpmem_पूर्णांकerlaced_scan);

व्योम ipu_cpmem_set_axi_id(काष्ठा ipuv3_channel *ch, u32 id)
अणु
	id &= 0x3;
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_ID, id);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_axi_id);

पूर्णांक ipu_cpmem_get_burstsize(काष्ठा ipuv3_channel *ch)
अणु
	वापस ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_NPB) + 1;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_get_burstsize);

व्योम ipu_cpmem_set_burstsize(काष्ठा ipuv3_channel *ch, पूर्णांक burstsize)
अणु
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, burstsize - 1);
पूर्ण;
EXPORT_SYMBOL_GPL(ipu_cpmem_set_burstsize);

व्योम ipu_cpmem_set_block_mode(काष्ठा ipuv3_channel *ch)
अणु
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_BM, 1);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_block_mode);

व्योम ipu_cpmem_set_rotation(काष्ठा ipuv3_channel *ch,
			    क्रमागत ipu_rotate_mode rot)
अणु
	u32 temp_rot = bitrev8(rot) >> 5;

	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_ROT_HF_VF, temp_rot);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_rotation);

पूर्णांक ipu_cpmem_set_क्रमmat_rgb(काष्ठा ipuv3_channel *ch,
			     स्थिर काष्ठा ipu_rgb *rgb)
अणु
	पूर्णांक bpp = 0, npb = 0, ro, go, bo, to;

	ro = rgb->bits_per_pixel - rgb->red.length - rgb->red.offset;
	go = rgb->bits_per_pixel - rgb->green.length - rgb->green.offset;
	bo = rgb->bits_per_pixel - rgb->blue.length - rgb->blue.offset;
	to = rgb->bits_per_pixel - rgb->transp.length - rgb->transp.offset;

	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_WID0, rgb->red.length - 1);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_OFS0, ro);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_WID1, rgb->green.length - 1);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_OFS1, go);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_WID2, rgb->blue.length - 1);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_OFS2, bo);

	अगर (rgb->transp.length) अणु
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_WID3,
				rgb->transp.length - 1);
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_OFS3, to);
	पूर्ण अन्यथा अणु
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_WID3, 7);
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_OFS3,
				rgb->bits_per_pixel);
	पूर्ण

	चयन (rgb->bits_per_pixel) अणु
	हाल 32:
		bpp = 0;
		npb = 15;
		अवरोध;
	हाल 24:
		bpp = 1;
		npb = 19;
		अवरोध;
	हाल 16:
		bpp = 3;
		npb = 31;
		अवरोध;
	हाल 8:
		bpp = 5;
		npb = 63;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_BPP, bpp);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, npb);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_PFS, 7); /* rgb mode */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_क्रमmat_rgb);

पूर्णांक ipu_cpmem_set_क्रमmat_passthrough(काष्ठा ipuv3_channel *ch, पूर्णांक width)
अणु
	पूर्णांक bpp = 0, npb = 0;

	चयन (width) अणु
	हाल 32:
		bpp = 0;
		npb = 15;
		अवरोध;
	हाल 24:
		bpp = 1;
		npb = 19;
		अवरोध;
	हाल 16:
		bpp = 3;
		npb = 31;
		अवरोध;
	हाल 8:
		bpp = 5;
		npb = 63;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_BPP, bpp);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, npb);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_PFS, 6); /* raw mode */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_क्रमmat_passthrough);

व्योम ipu_cpmem_set_yuv_पूर्णांकerleaved(काष्ठा ipuv3_channel *ch, u32 pixel_क्रमmat)
अणु
	चयन (pixel_क्रमmat) अणु
	हाल V4L2_PIX_FMT_UYVY:
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_BPP, 3); /* bits/pixel */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_PFS, 0xA);/* pix fmt */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, 31);/* burst size */
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_BPP, 3); /* bits/pixel */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_PFS, 0x8);/* pix fmt */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, 31);/* burst size */
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_yuv_पूर्णांकerleaved);

व्योम ipu_cpmem_set_yuv_planar_full(काष्ठा ipuv3_channel *ch,
				   अचिन्हित पूर्णांक uv_stride,
				   अचिन्हित पूर्णांक u_offset, अचिन्हित पूर्णांक v_offset)
अणु
	WARN_ON_ONCE((u_offset & 0x7) || (v_offset & 0x7));

	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_SLUV, uv_stride - 1);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_UBO, u_offset / 8);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_VBO, v_offset / 8);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_yuv_planar_full);

अटल स्थिर काष्ठा ipu_rgb def_xrgb_32 = अणु
	.red	= अणु .offset = 16, .length = 8, पूर्ण,
	.green	= अणु .offset =  8, .length = 8, पूर्ण,
	.blue	= अणु .offset =  0, .length = 8, पूर्ण,
	.transp = अणु .offset = 24, .length = 8, पूर्ण,
	.bits_per_pixel = 32,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_xbgr_32 = अणु
	.red	= अणु .offset =  0, .length = 8, पूर्ण,
	.green	= अणु .offset =  8, .length = 8, पूर्ण,
	.blue	= अणु .offset = 16, .length = 8, पूर्ण,
	.transp = अणु .offset = 24, .length = 8, पूर्ण,
	.bits_per_pixel = 32,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_rgbx_32 = अणु
	.red	= अणु .offset = 24, .length = 8, पूर्ण,
	.green	= अणु .offset = 16, .length = 8, पूर्ण,
	.blue	= अणु .offset =  8, .length = 8, पूर्ण,
	.transp = अणु .offset =  0, .length = 8, पूर्ण,
	.bits_per_pixel = 32,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_bgrx_32 = अणु
	.red	= अणु .offset =  8, .length = 8, पूर्ण,
	.green	= अणु .offset = 16, .length = 8, पूर्ण,
	.blue	= अणु .offset = 24, .length = 8, पूर्ण,
	.transp = अणु .offset =  0, .length = 8, पूर्ण,
	.bits_per_pixel = 32,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_rgb_24 = अणु
	.red	= अणु .offset = 16, .length = 8, पूर्ण,
	.green	= अणु .offset =  8, .length = 8, पूर्ण,
	.blue	= अणु .offset =  0, .length = 8, पूर्ण,
	.transp = अणु .offset =  0, .length = 0, पूर्ण,
	.bits_per_pixel = 24,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_bgr_24 = अणु
	.red	= अणु .offset =  0, .length = 8, पूर्ण,
	.green	= अणु .offset =  8, .length = 8, पूर्ण,
	.blue	= अणु .offset = 16, .length = 8, पूर्ण,
	.transp = अणु .offset =  0, .length = 0, पूर्ण,
	.bits_per_pixel = 24,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_rgb_16 = अणु
	.red	= अणु .offset = 11, .length = 5, पूर्ण,
	.green	= अणु .offset =  5, .length = 6, पूर्ण,
	.blue	= अणु .offset =  0, .length = 5, पूर्ण,
	.transp = अणु .offset =  0, .length = 0, पूर्ण,
	.bits_per_pixel = 16,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_bgr_16 = अणु
	.red	= अणु .offset =  0, .length = 5, पूर्ण,
	.green	= अणु .offset =  5, .length = 6, पूर्ण,
	.blue	= अणु .offset = 11, .length = 5, पूर्ण,
	.transp = अणु .offset =  0, .length = 0, पूर्ण,
	.bits_per_pixel = 16,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_argb_16 = अणु
	.red	= अणु .offset = 10, .length = 5, पूर्ण,
	.green	= अणु .offset =  5, .length = 5, पूर्ण,
	.blue	= अणु .offset =  0, .length = 5, पूर्ण,
	.transp = अणु .offset = 15, .length = 1, पूर्ण,
	.bits_per_pixel = 16,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_argb_16_4444 = अणु
	.red	= अणु .offset =  8, .length = 4, पूर्ण,
	.green	= अणु .offset =  4, .length = 4, पूर्ण,
	.blue	= अणु .offset =  0, .length = 4, पूर्ण,
	.transp = अणु .offset = 12, .length = 4, पूर्ण,
	.bits_per_pixel = 16,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_abgr_16 = अणु
	.red	= अणु .offset =  0, .length = 5, पूर्ण,
	.green	= अणु .offset =  5, .length = 5, पूर्ण,
	.blue	= अणु .offset = 10, .length = 5, पूर्ण,
	.transp = अणु .offset = 15, .length = 1, पूर्ण,
	.bits_per_pixel = 16,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_rgba_16 = अणु
	.red	= अणु .offset = 11, .length = 5, पूर्ण,
	.green	= अणु .offset =  6, .length = 5, पूर्ण,
	.blue	= अणु .offset =  1, .length = 5, पूर्ण,
	.transp = अणु .offset =  0, .length = 1, पूर्ण,
	.bits_per_pixel = 16,
पूर्ण;

अटल स्थिर काष्ठा ipu_rgb def_bgra_16 = अणु
	.red	= अणु .offset =  1, .length = 5, पूर्ण,
	.green	= अणु .offset =  6, .length = 5, पूर्ण,
	.blue	= अणु .offset = 11, .length = 5, पूर्ण,
	.transp = अणु .offset =  0, .length = 1, पूर्ण,
	.bits_per_pixel = 16,
पूर्ण;

#घोषणा Y_OFFSET(pix, x, y)	((x) + pix->width * (y))
#घोषणा U_OFFSET(pix, x, y)	((pix->width * pix->height) +		\
				 (pix->width * ((y) / 2) / 2) + (x) / 2)
#घोषणा V_OFFSET(pix, x, y)	((pix->width * pix->height) +		\
				 (pix->width * pix->height / 4) +	\
				 (pix->width * ((y) / 2) / 2) + (x) / 2)
#घोषणा U2_OFFSET(pix, x, y)	((pix->width * pix->height) +		\
				 (pix->width * (y) / 2) + (x) / 2)
#घोषणा V2_OFFSET(pix, x, y)	((pix->width * pix->height) +		\
				 (pix->width * pix->height / 2) +	\
				 (pix->width * (y) / 2) + (x) / 2)
#घोषणा UV_OFFSET(pix, x, y)	((pix->width * pix->height) +	\
				 (pix->width * ((y) / 2)) + (x))
#घोषणा UV2_OFFSET(pix, x, y)	((pix->width * pix->height) +	\
				 (pix->width * y) + (x))

#घोषणा NUM_ALPHA_CHANNELS	7

/* See Table 37-12. Alpha channels mapping. */
अटल पूर्णांक ipu_channel_albm(पूर्णांक ch_num)
अणु
	चयन (ch_num) अणु
	हाल IPUV3_CHANNEL_G_MEM_IC_PRP_VF:	वापस 0;
	हाल IPUV3_CHANNEL_G_MEM_IC_PP:		वापस 1;
	हाल IPUV3_CHANNEL_MEM_FG_SYNC:		वापस 2;
	हाल IPUV3_CHANNEL_MEM_FG_ASYNC:	वापस 3;
	हाल IPUV3_CHANNEL_MEM_BG_SYNC:		वापस 4;
	हाल IPUV3_CHANNEL_MEM_BG_ASYNC:	वापस 5;
	हाल IPUV3_CHANNEL_MEM_VDI_PLANE1_COMB: वापस 6;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम ipu_cpmem_set_separate_alpha(काष्ठा ipuv3_channel *ch)
अणु
	काष्ठा ipu_soc *ipu = ch->ipu;
	पूर्णांक albm;
	u32 val;

	albm = ipu_channel_albm(ch->num);
	अगर (albm < 0)
		वापस;

	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_ALU, 1);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_ALBM, albm);
	ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_CRE, 1);

	val = ipu_idmac_पढ़ो(ipu, IDMAC_SEP_ALPHA);
	val |= BIT(ch->num);
	ipu_idmac_ग_लिखो(ipu, val, IDMAC_SEP_ALPHA);
पूर्ण

पूर्णांक ipu_cpmem_set_fmt(काष्ठा ipuv3_channel *ch, u32 drm_fourcc)
अणु
	चयन (drm_fourcc) अणु
	हाल DRM_FORMAT_YUV420:
	हाल DRM_FORMAT_YVU420:
		/* pix क्रमmat */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_PFS, 2);
		/* burst size */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, 31);
		अवरोध;
	हाल DRM_FORMAT_YUV422:
	हाल DRM_FORMAT_YVU422:
		/* pix क्रमmat */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_PFS, 1);
		/* burst size */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, 31);
		अवरोध;
	हाल DRM_FORMAT_YUV444:
	हाल DRM_FORMAT_YVU444:
		/* pix क्रमmat */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_PFS, 0);
		/* burst size */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, 31);
		अवरोध;
	हाल DRM_FORMAT_NV12:
		/* pix क्रमmat */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_PFS, 4);
		/* burst size */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, 31);
		अवरोध;
	हाल DRM_FORMAT_NV16:
		/* pix क्रमmat */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_PFS, 3);
		/* burst size */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, 31);
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		/* bits/pixel */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_BPP, 3);
		/* pix क्रमmat */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_PFS, 0xA);
		/* burst size */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, 31);
		अवरोध;
	हाल DRM_FORMAT_YUYV:
		/* bits/pixel */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_BPP, 3);
		/* pix क्रमmat */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_PFS, 0x8);
		/* burst size */
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_NPB, 31);
		अवरोध;
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_XBGR8888:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_xbgr_32);
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XRGB8888:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_xrgb_32);
		अवरोध;
	हाल DRM_FORMAT_RGBA8888:
	हाल DRM_FORMAT_RGBX8888:
	हाल DRM_FORMAT_RGBX8888_A8:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_rgbx_32);
		अवरोध;
	हाल DRM_FORMAT_BGRA8888:
	हाल DRM_FORMAT_BGRX8888:
	हाल DRM_FORMAT_BGRX8888_A8:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_bgrx_32);
		अवरोध;
	हाल DRM_FORMAT_BGR888:
	हाल DRM_FORMAT_BGR888_A8:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_bgr_24);
		अवरोध;
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_RGB888_A8:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_rgb_24);
		अवरोध;
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_RGB565_A8:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_rgb_16);
		अवरोध;
	हाल DRM_FORMAT_BGR565:
	हाल DRM_FORMAT_BGR565_A8:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_bgr_16);
		अवरोध;
	हाल DRM_FORMAT_ARGB1555:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_argb_16);
		अवरोध;
	हाल DRM_FORMAT_ABGR1555:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_abgr_16);
		अवरोध;
	हाल DRM_FORMAT_RGBA5551:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_rgba_16);
		अवरोध;
	हाल DRM_FORMAT_BGRA5551:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_bgra_16);
		अवरोध;
	हाल DRM_FORMAT_ARGB4444:
		ipu_cpmem_set_क्रमmat_rgb(ch, &def_argb_16_4444);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (drm_fourcc) अणु
	हाल DRM_FORMAT_RGB565_A8:
	हाल DRM_FORMAT_BGR565_A8:
	हाल DRM_FORMAT_RGB888_A8:
	हाल DRM_FORMAT_BGR888_A8:
	हाल DRM_FORMAT_RGBX8888_A8:
	हाल DRM_FORMAT_BGRX8888_A8:
		ipu_ch_param_ग_लिखो_field(ch, IPU_FIELD_WID3, 7);
		ipu_cpmem_set_separate_alpha(ch);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_fmt);

पूर्णांक ipu_cpmem_set_image(काष्ठा ipuv3_channel *ch, काष्ठा ipu_image *image)
अणु
	काष्ठा v4l2_pix_क्रमmat *pix = &image->pix;
	पूर्णांक offset, u_offset, v_offset;
	पूर्णांक ret = 0;

	pr_debug("%s: resolution: %dx%d stride: %d\n",
		 __func__, pix->width, pix->height,
		 pix->bytesperline);

	ipu_cpmem_set_resolution(ch, image->rect.width, image->rect.height);
	ipu_cpmem_set_stride(ch, pix->bytesperline);

	ipu_cpmem_set_fmt(ch, v4l2_pix_fmt_to_drm_fourcc(pix->pixelक्रमmat));

	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUV420:
		offset = Y_OFFSET(pix, image->rect.left, image->rect.top);
		u_offset = image->u_offset ?
			image->u_offset : U_OFFSET(pix, image->rect.left,
						   image->rect.top) - offset;
		v_offset = image->v_offset ?
			image->v_offset : V_OFFSET(pix, image->rect.left,
						   image->rect.top) - offset;

		ipu_cpmem_set_yuv_planar_full(ch, pix->bytesperline / 2,
					      u_offset, v_offset);
		अवरोध;
	हाल V4L2_PIX_FMT_YVU420:
		offset = Y_OFFSET(pix, image->rect.left, image->rect.top);
		u_offset = image->u_offset ?
			image->u_offset : V_OFFSET(pix, image->rect.left,
						   image->rect.top) - offset;
		v_offset = image->v_offset ?
			image->v_offset : U_OFFSET(pix, image->rect.left,
						   image->rect.top) - offset;

		ipu_cpmem_set_yuv_planar_full(ch, pix->bytesperline / 2,
					      u_offset, v_offset);
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:
		offset = Y_OFFSET(pix, image->rect.left, image->rect.top);
		u_offset = image->u_offset ?
			image->u_offset : U2_OFFSET(pix, image->rect.left,
						    image->rect.top) - offset;
		v_offset = image->v_offset ?
			image->v_offset : V2_OFFSET(pix, image->rect.left,
						    image->rect.top) - offset;

		ipu_cpmem_set_yuv_planar_full(ch, pix->bytesperline / 2,
					      u_offset, v_offset);
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
		offset = Y_OFFSET(pix, image->rect.left, image->rect.top);
		u_offset = image->u_offset ?
			image->u_offset : UV_OFFSET(pix, image->rect.left,
						    image->rect.top) - offset;
		v_offset = image->v_offset ? image->v_offset : 0;

		ipu_cpmem_set_yuv_planar_full(ch, pix->bytesperline,
					      u_offset, v_offset);
		अवरोध;
	हाल V4L2_PIX_FMT_NV16:
		offset = Y_OFFSET(pix, image->rect.left, image->rect.top);
		u_offset = image->u_offset ?
			image->u_offset : UV2_OFFSET(pix, image->rect.left,
						     image->rect.top) - offset;
		v_offset = image->v_offset ? image->v_offset : 0;

		ipu_cpmem_set_yuv_planar_full(ch, pix->bytesperline,
					      u_offset, v_offset);
		अवरोध;
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_RGB565:
		offset = image->rect.left * 2 +
			image->rect.top * pix->bytesperline;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB32:
	हाल V4L2_PIX_FMT_BGR32:
	हाल V4L2_PIX_FMT_ABGR32:
	हाल V4L2_PIX_FMT_XBGR32:
	हाल V4L2_PIX_FMT_BGRA32:
	हाल V4L2_PIX_FMT_BGRX32:
	हाल V4L2_PIX_FMT_RGBA32:
	हाल V4L2_PIX_FMT_RGBX32:
	हाल V4L2_PIX_FMT_ARGB32:
	हाल V4L2_PIX_FMT_XRGB32:
		offset = image->rect.left * 4 +
			image->rect.top * pix->bytesperline;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB24:
	हाल V4L2_PIX_FMT_BGR24:
		offset = image->rect.left * 3 +
			image->rect.top * pix->bytesperline;
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
	हाल V4L2_PIX_FMT_GREY:
		offset = image->rect.left + image->rect.top * pix->bytesperline;
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR16:
	हाल V4L2_PIX_FMT_SGBRG16:
	हाल V4L2_PIX_FMT_SGRBG16:
	हाल V4L2_PIX_FMT_SRGGB16:
	हाल V4L2_PIX_FMT_Y16:
		offset = image->rect.left * 2 +
			 image->rect.top * pix->bytesperline;
		अवरोध;
	शेष:
		/* This should not happen */
		WARN_ON(1);
		offset = 0;
		ret = -EINVAL;
	पूर्ण

	ipu_cpmem_set_buffer(ch, 0, image->phys0 + offset);
	ipu_cpmem_set_buffer(ch, 1, image->phys1 + offset);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_set_image);

व्योम ipu_cpmem_dump(काष्ठा ipuv3_channel *ch)
अणु
	काष्ठा ipu_ch_param __iomem *p = ipu_get_cpmem(ch);
	काष्ठा ipu_soc *ipu = ch->ipu;
	पूर्णांक chno = ch->num;

	dev_dbg(ipu->dev, "ch %d word 0 - %08X %08X %08X %08X %08X\n", chno,
		पढ़ोl(&p->word[0].data[0]),
		पढ़ोl(&p->word[0].data[1]),
		पढ़ोl(&p->word[0].data[2]),
		पढ़ोl(&p->word[0].data[3]),
		पढ़ोl(&p->word[0].data[4]));
	dev_dbg(ipu->dev, "ch %d word 1 - %08X %08X %08X %08X %08X\n", chno,
		पढ़ोl(&p->word[1].data[0]),
		पढ़ोl(&p->word[1].data[1]),
		पढ़ोl(&p->word[1].data[2]),
		पढ़ोl(&p->word[1].data[3]),
		पढ़ोl(&p->word[1].data[4]));
	dev_dbg(ipu->dev, "PFS 0x%x, ",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_PFS));
	dev_dbg(ipu->dev, "BPP 0x%x, ",
		ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_BPP));
	dev_dbg(ipu->dev, "NPB 0x%x\n",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_NPB));

	dev_dbg(ipu->dev, "FW %d, ",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_FW));
	dev_dbg(ipu->dev, "FH %d, ",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_FH));
	dev_dbg(ipu->dev, "EBA0 0x%x\n",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_EBA0) << 3);
	dev_dbg(ipu->dev, "EBA1 0x%x\n",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_EBA1) << 3);
	dev_dbg(ipu->dev, "Stride %d\n",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_SL));
	dev_dbg(ipu->dev, "scan_order %d\n",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_SO));
	dev_dbg(ipu->dev, "uv_stride %d\n",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_SLUV));
	dev_dbg(ipu->dev, "u_offset 0x%x\n",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_UBO) << 3);
	dev_dbg(ipu->dev, "v_offset 0x%x\n",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_VBO) << 3);

	dev_dbg(ipu->dev, "Width0 %d+1, ",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_WID0));
	dev_dbg(ipu->dev, "Width1 %d+1, ",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_WID1));
	dev_dbg(ipu->dev, "Width2 %d+1, ",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_WID2));
	dev_dbg(ipu->dev, "Width3 %d+1, ",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_WID3));
	dev_dbg(ipu->dev, "Offset0 %d, ",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_OFS0));
	dev_dbg(ipu->dev, "Offset1 %d, ",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_OFS1));
	dev_dbg(ipu->dev, "Offset2 %d, ",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_OFS2));
	dev_dbg(ipu->dev, "Offset3 %d\n",
		 ipu_ch_param_पढ़ो_field(ch, IPU_FIELD_OFS3));
पूर्ण
EXPORT_SYMBOL_GPL(ipu_cpmem_dump);

पूर्णांक ipu_cpmem_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, अचिन्हित दीर्घ base)
अणु
	काष्ठा ipu_cpmem *cpmem;

	cpmem = devm_kzalloc(dev, माप(*cpmem), GFP_KERNEL);
	अगर (!cpmem)
		वापस -ENOMEM;

	ipu->cpmem_priv = cpmem;

	spin_lock_init(&cpmem->lock);
	cpmem->base = devm_ioremap(dev, base, SZ_128K);
	अगर (!cpmem->base)
		वापस -ENOMEM;

	dev_dbg(dev, "CPMEM base: 0x%08lx remapped to %p\n",
		base, cpmem->base);
	cpmem->ipu = ipu;

	वापस 0;
पूर्ण

व्योम ipu_cpmem_निकास(काष्ठा ipu_soc *ipu)
अणु
पूर्ण
