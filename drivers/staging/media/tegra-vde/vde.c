<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * NVIDIA Tegra Video decoder driver
 *
 * Copyright (C) 2016-2017 Dmitry Osipenko <digetx@gmail.com>
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <soc/tegra/pmc.h>

#समावेश "uapi.h"
#समावेश "vde.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

#घोषणा ICMDQUE_WR		0x00
#घोषणा CMDQUE_CONTROL		0x08
#घोषणा INTR_STATUS		0x18
#घोषणा BSE_INT_ENB		0x40
#घोषणा BSE_CONFIG		0x44

#घोषणा BSE_ICMDQUE_EMPTY	BIT(3)
#घोषणा BSE_DMA_BUSY		BIT(23)

काष्ठा video_frame अणु
	काष्ठा dma_buf_attachment *y_dmabuf_attachment;
	काष्ठा dma_buf_attachment *cb_dmabuf_attachment;
	काष्ठा dma_buf_attachment *cr_dmabuf_attachment;
	काष्ठा dma_buf_attachment *aux_dmabuf_attachment;
	dma_addr_t y_addr;
	dma_addr_t cb_addr;
	dma_addr_t cr_addr;
	dma_addr_t aux_addr;
	u32 frame_num;
	u32 flags;
पूर्ण;

अटल व्योम tegra_vde_ग_लिखोl(काष्ठा tegra_vde *vde,
			     u32 value, व्योम __iomem *base, u32 offset)
अणु
	trace_vde_ग_लिखोl(vde, base, offset, value);

	ग_लिखोl_relaxed(value, base + offset);
पूर्ण

अटल u32 tegra_vde_पढ़ोl(काष्ठा tegra_vde *vde,
			   व्योम __iomem *base, u32 offset)
अणु
	u32 value = पढ़ोl_relaxed(base + offset);

	trace_vde_पढ़ोl(vde, base, offset, value);

	वापस value;
पूर्ण

अटल व्योम tegra_vde_set_bits(काष्ठा tegra_vde *vde,
			       u32 mask, व्योम __iomem *base, u32 offset)
अणु
	u32 value = tegra_vde_पढ़ोl(vde, base, offset);

	tegra_vde_ग_लिखोl(vde, value | mask, base, offset);
पूर्ण

अटल पूर्णांक tegra_vde_रुको_mbe(काष्ठा tegra_vde *vde)
अणु
	u32 पंचांगp;

	वापस पढ़ोl_relaxed_poll_समयout(vde->mbe + 0x8C, पंचांगp,
					  (पंचांगp >= 0x10), 1, 100);
पूर्ण

अटल पूर्णांक tegra_vde_setup_mbe_frame_idx(काष्ठा tegra_vde *vde,
					 अचिन्हित पूर्णांक refs_nb,
					 bool setup_refs)
अणु
	u32 frame_idx_enb_mask = 0;
	u32 value;
	अचिन्हित पूर्णांक frame_idx;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	tegra_vde_ग_लिखोl(vde, 0xD0000000 | (0 << 23), vde->mbe, 0x80);
	tegra_vde_ग_लिखोl(vde, 0xD0200000 | (0 << 23), vde->mbe, 0x80);

	err = tegra_vde_रुको_mbe(vde);
	अगर (err)
		वापस err;

	अगर (!setup_refs)
		वापस 0;

	क्रम (idx = 0, frame_idx = 1; idx < refs_nb; idx++, frame_idx++) अणु
		tegra_vde_ग_लिखोl(vde, 0xD0000000 | (frame_idx << 23),
				 vde->mbe, 0x80);
		tegra_vde_ग_लिखोl(vde, 0xD0200000 | (frame_idx << 23),
				 vde->mbe, 0x80);

		frame_idx_enb_mask |= frame_idx << (6 * (idx % 4));

		अगर (idx % 4 == 3 || idx == refs_nb - 1) अणु
			value = 0xC0000000;
			value |= (idx >> 2) << 24;
			value |= frame_idx_enb_mask;

			tegra_vde_ग_लिखोl(vde, value, vde->mbe, 0x80);

			err = tegra_vde_रुको_mbe(vde);
			अगर (err)
				वापस err;

			frame_idx_enb_mask = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_vde_mbe_set_0xa_reg(काष्ठा tegra_vde *vde, पूर्णांक reg, u32 val)
अणु
	tegra_vde_ग_लिखोl(vde, 0xA0000000 | (reg << 24) | (val & 0xFFFF),
			 vde->mbe, 0x80);
	tegra_vde_ग_लिखोl(vde, 0xA0000000 | ((reg + 1) << 24) | (val >> 16),
			 vde->mbe, 0x80);
पूर्ण

अटल पूर्णांक tegra_vde_रुको_bsev(काष्ठा tegra_vde *vde, bool रुको_dma)
अणु
	काष्ठा device *dev = vde->miscdev.parent;
	u32 value;
	पूर्णांक err;

	err = पढ़ोl_relaxed_poll_समयout(vde->bsev + INTR_STATUS, value,
					 !(value & BIT(2)), 1, 100);
	अगर (err) अणु
		dev_err(dev, "BSEV unknown bit timeout\n");
		वापस err;
	पूर्ण

	err = पढ़ोl_relaxed_poll_समयout(vde->bsev + INTR_STATUS, value,
					 (value & BSE_ICMDQUE_EMPTY), 1, 100);
	अगर (err) अणु
		dev_err(dev, "BSEV ICMDQUE flush timeout\n");
		वापस err;
	पूर्ण

	अगर (!रुको_dma)
		वापस 0;

	err = पढ़ोl_relaxed_poll_समयout(vde->bsev + INTR_STATUS, value,
					 !(value & BSE_DMA_BUSY), 1, 100);
	अगर (err) अणु
		dev_err(dev, "BSEV DMA timeout\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_vde_push_to_bsev_icmdqueue(काष्ठा tegra_vde *vde,
					    u32 value, bool रुको_dma)
अणु
	tegra_vde_ग_लिखोl(vde, value, vde->bsev, ICMDQUE_WR);

	वापस tegra_vde_रुको_bsev(vde, रुको_dma);
पूर्ण

अटल व्योम tegra_vde_setup_frameid(काष्ठा tegra_vde *vde,
				    काष्ठा video_frame *frame,
				    अचिन्हित पूर्णांक frameid,
				    u32 mbs_width, u32 mbs_height)
अणु
	u32 y_addr  = frame ? frame->y_addr  : 0x6CDEAD00;
	u32 cb_addr = frame ? frame->cb_addr : 0x6CDEAD00;
	u32 cr_addr = frame ? frame->cr_addr : 0x6CDEAD00;
	u32 value1 = frame ? ((mbs_width << 16) | mbs_height) : 0;
	u32 value2 = frame ? ((((mbs_width + 1) >> 1) << 6) | 1) : 0;

	tegra_vde_ग_लिखोl(vde, y_addr  >> 8, vde->frameid, 0x000 + frameid * 4);
	tegra_vde_ग_लिखोl(vde, cb_addr >> 8, vde->frameid, 0x100 + frameid * 4);
	tegra_vde_ग_लिखोl(vde, cr_addr >> 8, vde->frameid, 0x180 + frameid * 4);
	tegra_vde_ग_लिखोl(vde, value1,       vde->frameid, 0x080 + frameid * 4);
	tegra_vde_ग_लिखोl(vde, value2,       vde->frameid, 0x280 + frameid * 4);
पूर्ण

अटल व्योम tegra_setup_frameidx(काष्ठा tegra_vde *vde,
				 काष्ठा video_frame *frames,
				 अचिन्हित पूर्णांक frames_nb,
				 u32 mbs_width, u32 mbs_height)
अणु
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 0; idx < frames_nb; idx++)
		tegra_vde_setup_frameid(vde, &frames[idx], idx,
					mbs_width, mbs_height);

	क्रम (; idx < 17; idx++)
		tegra_vde_setup_frameid(vde, शून्य, idx, 0, 0);
पूर्ण

अटल व्योम tegra_vde_setup_iram_entry(काष्ठा tegra_vde *vde,
				       अचिन्हित पूर्णांक table,
				       अचिन्हित पूर्णांक row,
				       u32 value1, u32 value2)
अणु
	u32 *iram_tables = vde->iram;

	trace_vde_setup_iram_entry(table, row, value1, value2);

	iram_tables[0x20 * table + row * 2] = value1;
	iram_tables[0x20 * table + row * 2 + 1] = value2;
पूर्ण

अटल व्योम tegra_vde_setup_iram_tables(काष्ठा tegra_vde *vde,
					काष्ठा video_frame *dpb_frames,
					अचिन्हित पूर्णांक ref_frames_nb,
					अचिन्हित पूर्णांक with_earlier_poc_nb)
अणु
	काष्ठा video_frame *frame;
	u32 value, aux_addr;
	पूर्णांक with_later_poc_nb;
	अचिन्हित पूर्णांक i, k;

	trace_vde_ref_l0(dpb_frames[0].frame_num);

	क्रम (i = 0; i < 16; i++) अणु
		अगर (i < ref_frames_nb) अणु
			frame = &dpb_frames[i + 1];

			aux_addr = frame->aux_addr;

			value  = (i + 1) << 26;
			value |= !(frame->flags & FLAG_B_FRAME) << 25;
			value |= 1 << 24;
			value |= frame->frame_num;
		पूर्ण अन्यथा अणु
			aux_addr = 0x6ADEAD00;
			value = 0;
		पूर्ण

		tegra_vde_setup_iram_entry(vde, 0, i, value, aux_addr);
		tegra_vde_setup_iram_entry(vde, 1, i, value, aux_addr);
		tegra_vde_setup_iram_entry(vde, 2, i, value, aux_addr);
		tegra_vde_setup_iram_entry(vde, 3, i, value, aux_addr);
	पूर्ण

	अगर (!(dpb_frames[0].flags & FLAG_B_FRAME))
		वापस;

	अगर (with_earlier_poc_nb >= ref_frames_nb)
		वापस;

	with_later_poc_nb = ref_frames_nb - with_earlier_poc_nb;

	trace_vde_ref_l1(with_later_poc_nb, with_earlier_poc_nb);

	क्रम (i = 0, k = with_earlier_poc_nb; i < with_later_poc_nb; i++, k++) अणु
		frame = &dpb_frames[k + 1];

		aux_addr = frame->aux_addr;

		value  = (k + 1) << 26;
		value |= !(frame->flags & FLAG_B_FRAME) << 25;
		value |= 1 << 24;
		value |= frame->frame_num;

		tegra_vde_setup_iram_entry(vde, 2, i, value, aux_addr);
	पूर्ण

	क्रम (k = 0; i < ref_frames_nb; i++, k++) अणु
		frame = &dpb_frames[k + 1];

		aux_addr = frame->aux_addr;

		value  = (k + 1) << 26;
		value |= !(frame->flags & FLAG_B_FRAME) << 25;
		value |= 1 << 24;
		value |= frame->frame_num;

		tegra_vde_setup_iram_entry(vde, 2, i, value, aux_addr);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_vde_setup_hw_context(काष्ठा tegra_vde *vde,
				      काष्ठा tegra_vde_h264_decoder_ctx *ctx,
				      काष्ठा video_frame *dpb_frames,
				      dma_addr_t bitstream_data_addr,
				      माप_प्रकार bitstream_data_size,
				      अचिन्हित पूर्णांक macroblocks_nb)
अणु
	काष्ठा device *dev = vde->miscdev.parent;
	u32 value;
	पूर्णांक err;

	tegra_vde_set_bits(vde, 0x000A, vde->sxe, 0xF0);
	tegra_vde_set_bits(vde, 0x000B, vde->bsev, CMDQUE_CONTROL);
	tegra_vde_set_bits(vde, 0x8002, vde->mbe, 0x50);
	tegra_vde_set_bits(vde, 0x000A, vde->mbe, 0xA0);
	tegra_vde_set_bits(vde, 0x000A, vde->ppe, 0x14);
	tegra_vde_set_bits(vde, 0x000A, vde->ppe, 0x28);
	tegra_vde_set_bits(vde, 0x0A00, vde->mce, 0x08);
	tegra_vde_set_bits(vde, 0x000A, vde->tfe, 0x00);
	tegra_vde_set_bits(vde, 0x0005, vde->vdma, 0x04);

	tegra_vde_ग_लिखोl(vde, 0x00000000, vde->vdma, 0x1C);
	tegra_vde_ग_लिखोl(vde, 0x00000000, vde->vdma, 0x00);
	tegra_vde_ग_लिखोl(vde, 0x00000007, vde->vdma, 0x04);
	tegra_vde_ग_लिखोl(vde, 0x00000007, vde->frameid, 0x200);
	tegra_vde_ग_लिखोl(vde, 0x00000005, vde->tfe, 0x04);
	tegra_vde_ग_लिखोl(vde, 0x00000000, vde->mbe, 0x84);
	tegra_vde_ग_लिखोl(vde, 0x00000010, vde->sxe, 0x08);
	tegra_vde_ग_लिखोl(vde, 0x00000150, vde->sxe, 0x54);
	tegra_vde_ग_लिखोl(vde, 0x0000054C, vde->sxe, 0x58);
	tegra_vde_ग_लिखोl(vde, 0x00000E34, vde->sxe, 0x5C);
	tegra_vde_ग_लिखोl(vde, 0x063C063C, vde->mce, 0x10);
	tegra_vde_ग_लिखोl(vde, 0x0003FC00, vde->bsev, INTR_STATUS);
	tegra_vde_ग_लिखोl(vde, 0x0000150D, vde->bsev, BSE_CONFIG);
	tegra_vde_ग_लिखोl(vde, 0x00000100, vde->bsev, BSE_INT_ENB);
	tegra_vde_ग_लिखोl(vde, 0x00000000, vde->bsev, 0x98);
	tegra_vde_ग_लिखोl(vde, 0x00000060, vde->bsev, 0x9C);

	स_रखो(vde->iram + 128, 0, macroblocks_nb / 2);

	tegra_setup_frameidx(vde, dpb_frames, ctx->dpb_frames_nb,
			     ctx->pic_width_in_mbs, ctx->pic_height_in_mbs);

	tegra_vde_setup_iram_tables(vde, dpb_frames,
				    ctx->dpb_frames_nb - 1,
				    ctx->dpb_ref_frames_with_earlier_poc_nb);

	/*
	 * The IRAM mapping is ग_लिखो-combine, ensure that CPU buffers have
	 * been flushed at this poपूर्णांक.
	 */
	wmb();

	tegra_vde_ग_लिखोl(vde, 0x00000000, vde->bsev, 0x8C);
	tegra_vde_ग_लिखोl(vde, bitstream_data_addr + bitstream_data_size,
			 vde->bsev, 0x54);

	value = ctx->pic_width_in_mbs << 11 | ctx->pic_height_in_mbs << 3;

	tegra_vde_ग_लिखोl(vde, value, vde->bsev, 0x88);

	err = tegra_vde_रुको_bsev(vde, false);
	अगर (err)
		वापस err;

	err = tegra_vde_push_to_bsev_icmdqueue(vde, 0x800003FC, false);
	अगर (err)
		वापस err;

	value = 0x01500000;
	value |= ((vde->iram_lists_addr + 512) >> 2) & 0xFFFF;

	err = tegra_vde_push_to_bsev_icmdqueue(vde, value, true);
	अगर (err)
		वापस err;

	err = tegra_vde_push_to_bsev_icmdqueue(vde, 0x840F054C, false);
	अगर (err)
		वापस err;

	err = tegra_vde_push_to_bsev_icmdqueue(vde, 0x80000080, false);
	अगर (err)
		वापस err;

	value = 0x0E340000 | ((vde->iram_lists_addr >> 2) & 0xFFFF);

	err = tegra_vde_push_to_bsev_icmdqueue(vde, value, true);
	अगर (err)
		वापस err;

	value = 0x00800005;
	value |= ctx->pic_width_in_mbs << 11;
	value |= ctx->pic_height_in_mbs << 3;

	tegra_vde_ग_लिखोl(vde, value, vde->sxe, 0x10);

	value = !ctx->baseline_profile << 17;
	value |= ctx->level_idc << 13;
	value |= ctx->log2_max_pic_order_cnt_lsb << 7;
	value |= ctx->pic_order_cnt_type << 5;
	value |= ctx->log2_max_frame_num;

	tegra_vde_ग_लिखोl(vde, value, vde->sxe, 0x40);

	value = ctx->pic_init_qp << 25;
	value |= !!(ctx->deblocking_filter_control_present_flag) << 2;
	value |= !!ctx->pic_order_present_flag;

	tegra_vde_ग_लिखोl(vde, value, vde->sxe, 0x44);

	value = ctx->chroma_qp_index_offset;
	value |= ctx->num_ref_idx_l0_active_minus1 << 5;
	value |= ctx->num_ref_idx_l1_active_minus1 << 10;
	value |= !!ctx->स्थिरrained_पूर्णांकra_pred_flag << 15;

	tegra_vde_ग_लिखोl(vde, value, vde->sxe, 0x48);

	value = 0x0C000000;
	value |= !!(dpb_frames[0].flags & FLAG_B_FRAME) << 24;

	tegra_vde_ग_लिखोl(vde, value, vde->sxe, 0x4C);

	value = 0x03800000;
	value |= bitstream_data_size & GENMASK(19, 15);

	tegra_vde_ग_लिखोl(vde, value, vde->sxe, 0x68);

	tegra_vde_ग_लिखोl(vde, bitstream_data_addr, vde->sxe, 0x6C);

	value = 0x10000005;
	value |= ctx->pic_width_in_mbs << 11;
	value |= ctx->pic_height_in_mbs << 3;

	tegra_vde_ग_लिखोl(vde, value, vde->mbe, 0x80);

	value = 0x26800000;
	value |= ctx->level_idc << 4;
	value |= !ctx->baseline_profile << 1;
	value |= !!ctx->direct_8x8_inference_flag;

	tegra_vde_ग_लिखोl(vde, value, vde->mbe, 0x80);

	tegra_vde_ग_लिखोl(vde, 0xF4000001, vde->mbe, 0x80);
	tegra_vde_ग_लिखोl(vde, 0x20000000, vde->mbe, 0x80);
	tegra_vde_ग_लिखोl(vde, 0xF4000101, vde->mbe, 0x80);

	value = 0x20000000;
	value |= ctx->chroma_qp_index_offset << 8;

	tegra_vde_ग_लिखोl(vde, value, vde->mbe, 0x80);

	err = tegra_vde_setup_mbe_frame_idx(vde,
					    ctx->dpb_frames_nb - 1,
					    ctx->pic_order_cnt_type == 0);
	अगर (err) अणु
		dev_err(dev, "MBE frames setup failed %d\n", err);
		वापस err;
	पूर्ण

	tegra_vde_mbe_set_0xa_reg(vde, 0, 0x000009FC);
	tegra_vde_mbe_set_0xa_reg(vde, 2, 0x61DEAD00);
	tegra_vde_mbe_set_0xa_reg(vde, 4, 0x62DEAD00);
	tegra_vde_mbe_set_0xa_reg(vde, 6, 0x63DEAD00);
	tegra_vde_mbe_set_0xa_reg(vde, 8, dpb_frames[0].aux_addr);

	value = 0xFC000000;
	value |= !!(dpb_frames[0].flags & FLAG_B_FRAME) << 2;

	अगर (!ctx->baseline_profile)
		value |= !!(dpb_frames[0].flags & FLAG_REFERENCE) << 1;

	tegra_vde_ग_लिखोl(vde, value, vde->mbe, 0x80);

	err = tegra_vde_रुको_mbe(vde);
	अगर (err) अणु
		dev_err(dev, "MBE programming failed %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_vde_decode_frame(काष्ठा tegra_vde *vde,
				   अचिन्हित पूर्णांक macroblocks_nb)
अणु
	reinit_completion(&vde->decode_completion);

	tegra_vde_ग_लिखोl(vde, 0x00000001, vde->bsev, 0x8C);
	tegra_vde_ग_लिखोl(vde, 0x20000000 | (macroblocks_nb - 1),
			 vde->sxe, 0x00);
पूर्ण

अटल पूर्णांक tegra_vde_attach_dmabuf(काष्ठा tegra_vde *vde,
				   पूर्णांक fd,
				   अचिन्हित दीर्घ offset,
				   माप_प्रकार min_size,
				   माप_प्रकार align_size,
				   काष्ठा dma_buf_attachment **a,
				   dma_addr_t *addrp,
				   माप_प्रकार *size,
				   क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा device *dev = vde->miscdev.parent;
	काष्ठा dma_buf *dmabuf;
	पूर्णांक err;

	dmabuf = dma_buf_get(fd);
	अगर (IS_ERR(dmabuf)) अणु
		dev_err(dev, "Invalid dmabuf FD\n");
		वापस PTR_ERR(dmabuf);
	पूर्ण

	अगर (dmabuf->size & (align_size - 1)) अणु
		dev_err(dev, "Unaligned dmabuf 0x%zX, should be aligned to 0x%zX\n",
			dmabuf->size, align_size);
		वापस -EINVAL;
	पूर्ण

	अगर ((u64)offset + min_size > dmabuf->size) अणु
		dev_err(dev, "Too small dmabuf size %zu @0x%lX, should be at least %zu\n",
			dmabuf->size, offset, min_size);
		वापस -EINVAL;
	पूर्ण

	err = tegra_vde_dmabuf_cache_map(vde, dmabuf, dma_dir, a, addrp);
	अगर (err)
		जाओ err_put;

	*addrp = *addrp + offset;

	अगर (size)
		*size = dmabuf->size - offset;

	वापस 0;

err_put:
	dma_buf_put(dmabuf);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_vde_attach_dmabufs_to_frame(काष्ठा tegra_vde *vde,
					     काष्ठा video_frame *frame,
					     काष्ठा tegra_vde_h264_frame *src,
					     क्रमागत dma_data_direction dma_dir,
					     bool baseline_profile,
					     माप_प्रकार lsize, माप_प्रकार csize)
अणु
	पूर्णांक err;

	err = tegra_vde_attach_dmabuf(vde, src->y_fd,
				      src->y_offset, lsize, SZ_256,
				      &frame->y_dmabuf_attachment,
				      &frame->y_addr,
				      शून्य, dma_dir);
	अगर (err)
		वापस err;

	err = tegra_vde_attach_dmabuf(vde, src->cb_fd,
				      src->cb_offset, csize, SZ_256,
				      &frame->cb_dmabuf_attachment,
				      &frame->cb_addr,
				      शून्य, dma_dir);
	अगर (err)
		जाओ err_release_y;

	err = tegra_vde_attach_dmabuf(vde, src->cr_fd,
				      src->cr_offset, csize, SZ_256,
				      &frame->cr_dmabuf_attachment,
				      &frame->cr_addr,
				      शून्य, dma_dir);
	अगर (err)
		जाओ err_release_cb;

	अगर (baseline_profile) अणु
		frame->aux_addr = 0x64DEAD00;
		वापस 0;
	पूर्ण

	err = tegra_vde_attach_dmabuf(vde, src->aux_fd,
				      src->aux_offset, csize, SZ_256,
				      &frame->aux_dmabuf_attachment,
				      &frame->aux_addr,
				      शून्य, dma_dir);
	अगर (err)
		जाओ err_release_cr;

	वापस 0;

err_release_cr:
	tegra_vde_dmabuf_cache_unmap(vde, frame->cr_dmabuf_attachment, true);
err_release_cb:
	tegra_vde_dmabuf_cache_unmap(vde, frame->cb_dmabuf_attachment, true);
err_release_y:
	tegra_vde_dmabuf_cache_unmap(vde, frame->y_dmabuf_attachment, true);

	वापस err;
पूर्ण

अटल व्योम tegra_vde_release_frame_dmabufs(काष्ठा tegra_vde *vde,
					    काष्ठा video_frame *frame,
					    क्रमागत dma_data_direction dma_dir,
					    bool baseline_profile,
					    bool release)
अणु
	अगर (!baseline_profile)
		tegra_vde_dmabuf_cache_unmap(vde, frame->aux_dmabuf_attachment,
					     release);

	tegra_vde_dmabuf_cache_unmap(vde, frame->cr_dmabuf_attachment, release);
	tegra_vde_dmabuf_cache_unmap(vde, frame->cb_dmabuf_attachment, release);
	tegra_vde_dmabuf_cache_unmap(vde, frame->y_dmabuf_attachment, release);
पूर्ण

अटल पूर्णांक tegra_vde_validate_frame(काष्ठा device *dev,
				    काष्ठा tegra_vde_h264_frame *frame)
अणु
	अगर (frame->frame_num > 0x7FFFFF) अणु
		dev_err(dev, "Bad frame_num %u\n", frame->frame_num);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_vde_validate_h264_ctx(काष्ठा device *dev,
				       काष्ठा tegra_vde_h264_decoder_ctx *ctx)
अणु
	अगर (ctx->dpb_frames_nb == 0 || ctx->dpb_frames_nb > 17) अणु
		dev_err(dev, "Bad DPB size %u\n", ctx->dpb_frames_nb);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->level_idc > 15) अणु
		dev_err(dev, "Bad level value %u\n", ctx->level_idc);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->pic_init_qp > 52) अणु
		dev_err(dev, "Bad pic_init_qp value %u\n", ctx->pic_init_qp);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->log2_max_pic_order_cnt_lsb > 16) अणु
		dev_err(dev, "Bad log2_max_pic_order_cnt_lsb value %u\n",
			ctx->log2_max_pic_order_cnt_lsb);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->log2_max_frame_num > 16) अणु
		dev_err(dev, "Bad log2_max_frame_num value %u\n",
			ctx->log2_max_frame_num);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->chroma_qp_index_offset > 31) अणु
		dev_err(dev, "Bad chroma_qp_index_offset value %u\n",
			ctx->chroma_qp_index_offset);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->pic_order_cnt_type > 2) अणु
		dev_err(dev, "Bad pic_order_cnt_type value %u\n",
			ctx->pic_order_cnt_type);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->num_ref_idx_l0_active_minus1 > 15) अणु
		dev_err(dev, "Bad num_ref_idx_l0_active_minus1 value %u\n",
			ctx->num_ref_idx_l0_active_minus1);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->num_ref_idx_l1_active_minus1 > 15) अणु
		dev_err(dev, "Bad num_ref_idx_l1_active_minus1 value %u\n",
			ctx->num_ref_idx_l1_active_minus1);
		वापस -EINVAL;
	पूर्ण

	अगर (!ctx->pic_width_in_mbs || ctx->pic_width_in_mbs > 127) अणु
		dev_err(dev, "Bad pic_width_in_mbs value %u\n",
			ctx->pic_width_in_mbs);
		वापस -EINVAL;
	पूर्ण

	अगर (!ctx->pic_height_in_mbs || ctx->pic_height_in_mbs > 127) अणु
		dev_err(dev, "Bad pic_height_in_mbs value %u\n",
			ctx->pic_height_in_mbs);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_vde_ioctl_decode_h264(काष्ठा tegra_vde *vde,
				       अचिन्हित दीर्घ vaddr)
अणु
	काष्ठा device *dev = vde->miscdev.parent;
	काष्ठा tegra_vde_h264_decoder_ctx ctx;
	काष्ठा tegra_vde_h264_frame *frames;
	काष्ठा tegra_vde_h264_frame __user *frames_user;
	काष्ठा video_frame *dpb_frames;
	काष्ठा dma_buf_attachment *bitstream_data_dmabuf_attachment;
	क्रमागत dma_data_direction dma_dir;
	dma_addr_t bitstream_data_addr;
	dma_addr_t bsev_ptr;
	माप_प्रकार lsize, csize;
	माप_प्रकार bitstream_data_size;
	अचिन्हित पूर्णांक macroblocks_nb;
	अचिन्हित पूर्णांक पढ़ो_bytes;
	अचिन्हित पूर्णांक cstride;
	अचिन्हित पूर्णांक i;
	दीर्घ समयout;
	पूर्णांक ret, err;

	अगर (copy_from_user(&ctx, (व्योम __user *)vaddr, माप(ctx)))
		वापस -EFAULT;

	ret = tegra_vde_validate_h264_ctx(dev, &ctx);
	अगर (ret)
		वापस ret;

	ret = tegra_vde_attach_dmabuf(vde, ctx.bitstream_data_fd,
				      ctx.bitstream_data_offset,
				      SZ_16K, SZ_16K,
				      &bitstream_data_dmabuf_attachment,
				      &bitstream_data_addr,
				      &bitstream_data_size,
				      DMA_TO_DEVICE);
	अगर (ret)
		वापस ret;

	frames = kदो_स्मृति_array(ctx.dpb_frames_nb, माप(*frames), GFP_KERNEL);
	अगर (!frames) अणु
		ret = -ENOMEM;
		जाओ release_bitstream_dmabuf;
	पूर्ण

	dpb_frames = kसुस्मृति(ctx.dpb_frames_nb, माप(*dpb_frames),
			     GFP_KERNEL);
	अगर (!dpb_frames) अणु
		ret = -ENOMEM;
		जाओ मुक्त_frames;
	पूर्ण

	macroblocks_nb = ctx.pic_width_in_mbs * ctx.pic_height_in_mbs;
	frames_user = u64_to_user_ptr(ctx.dpb_frames_ptr);

	अगर (copy_from_user(frames, frames_user,
			   ctx.dpb_frames_nb * माप(*frames))) अणु
		ret = -EFAULT;
		जाओ मुक्त_dpb_frames;
	पूर्ण

	cstride = ALIGN(ctx.pic_width_in_mbs * 8, 16);
	csize = cstride * ctx.pic_height_in_mbs * 8;
	lsize = macroblocks_nb * 256;

	क्रम (i = 0; i < ctx.dpb_frames_nb; i++) अणु
		ret = tegra_vde_validate_frame(dev, &frames[i]);
		अगर (ret)
			जाओ release_dpb_frames;

		dpb_frames[i].flags = frames[i].flags;
		dpb_frames[i].frame_num = frames[i].frame_num;

		dma_dir = (i == 0) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

		ret = tegra_vde_attach_dmabufs_to_frame(vde, &dpb_frames[i],
							&frames[i], dma_dir,
							ctx.baseline_profile,
							lsize, csize);
		अगर (ret)
			जाओ release_dpb_frames;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&vde->lock);
	अगर (ret)
		जाओ release_dpb_frames;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		जाओ put_runसमय_pm;

	/*
	 * We rely on the VDE रेजिस्टरs reset value, otherwise VDE
	 * causes bus lockup.
	 */
	ret = reset_control_निश्चित(vde->rst_mc);
	अगर (ret) अणु
		dev_err(dev, "DEC start: Failed to assert MC reset: %d\n",
			ret);
		जाओ put_runसमय_pm;
	पूर्ण

	ret = reset_control_reset(vde->rst);
	अगर (ret) अणु
		dev_err(dev, "DEC start: Failed to reset HW: %d\n", ret);
		जाओ put_runसमय_pm;
	पूर्ण

	ret = reset_control_deनिश्चित(vde->rst_mc);
	अगर (ret) अणु
		dev_err(dev, "DEC start: Failed to deassert MC reset: %d\n",
			ret);
		जाओ put_runसमय_pm;
	पूर्ण

	ret = tegra_vde_setup_hw_context(vde, &ctx, dpb_frames,
					 bitstream_data_addr,
					 bitstream_data_size,
					 macroblocks_nb);
	अगर (ret)
		जाओ put_runसमय_pm;

	tegra_vde_decode_frame(vde, macroblocks_nb);

	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&vde->decode_completion, msecs_to_jअगरfies(1000));
	अगर (समयout == 0) अणु
		bsev_ptr = tegra_vde_पढ़ोl(vde, vde->bsev, 0x10);
		macroblocks_nb = tegra_vde_पढ़ोl(vde, vde->sxe, 0xC8) & 0x1FFF;
		पढ़ो_bytes = bsev_ptr ? bsev_ptr - bitstream_data_addr : 0;

		dev_err(dev, "Decoding failed: read 0x%X bytes, %u macroblocks parsed\n",
			पढ़ो_bytes, macroblocks_nb);

		ret = -EIO;
	पूर्ण अन्यथा अगर (समयout < 0) अणु
		ret = समयout;
	पूर्ण

	/*
	 * At first reset memory client to aव्योम resetting VDE HW in the
	 * middle of DMA which could result पूर्णांकo memory corruption or hang
	 * the whole प्रणाली.
	 */
	err = reset_control_निश्चित(vde->rst_mc);
	अगर (err)
		dev_err(dev, "DEC end: Failed to assert MC reset: %d\n", err);

	err = reset_control_निश्चित(vde->rst);
	अगर (err)
		dev_err(dev, "DEC end: Failed to assert HW reset: %d\n", err);

put_runसमय_pm:
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
	mutex_unlock(&vde->lock);

release_dpb_frames:
	जबतक (i--) अणु
		dma_dir = (i == 0) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

		tegra_vde_release_frame_dmabufs(vde, &dpb_frames[i], dma_dir,
						ctx.baseline_profile, ret != 0);
	पूर्ण

मुक्त_dpb_frames:
	kमुक्त(dpb_frames);

मुक्त_frames:
	kमुक्त(frames);

release_bitstream_dmabuf:
	tegra_vde_dmabuf_cache_unmap(vde, bitstream_data_dmabuf_attachment,
				     ret != 0);

	वापस ret;
पूर्ण

अटल दीर्घ tegra_vde_unlocked_ioctl(काष्ठा file *filp,
				     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा miscdevice *miscdev = filp->निजी_data;
	काष्ठा tegra_vde *vde = container_of(miscdev, काष्ठा tegra_vde,
					     miscdev);

	चयन (cmd) अणु
	हाल TEGRA_VDE_IOCTL_DECODE_H264:
		वापस tegra_vde_ioctl_decode_h264(vde, arg);
	पूर्ण

	dev_err(miscdev->parent, "Invalid IOCTL command %u\n", cmd);

	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक tegra_vde_release_file(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा miscdevice *miscdev = filp->निजी_data;
	काष्ठा tegra_vde *vde = container_of(miscdev, काष्ठा tegra_vde,
					     miscdev);

	tegra_vde_dmabuf_cache_unmap_sync(vde);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations tegra_vde_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= tegra_vde_unlocked_ioctl,
	.release	= tegra_vde_release_file,
पूर्ण;

अटल irqवापस_t tegra_vde_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_vde *vde = data;

	अगर (completion_करोne(&vde->decode_completion))
		वापस IRQ_NONE;

	tegra_vde_set_bits(vde, 0, vde->frameid, 0x208);
	complete(&vde->decode_completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल __maybe_unused पूर्णांक tegra_vde_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_vde *vde = dev_get_drvdata(dev);
	पूर्णांक err;

	err = tegra_घातergate_घातer_off(TEGRA_POWERGATE_VDEC);
	अगर (err) अणु
		dev_err(dev, "Failed to power down HW: %d\n", err);
		वापस err;
	पूर्ण

	clk_disable_unprepare(vde->clk);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक tegra_vde_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_vde *vde = dev_get_drvdata(dev);
	पूर्णांक err;

	err = tegra_घातergate_sequence_घातer_up(TEGRA_POWERGATE_VDEC,
						vde->clk, vde->rst);
	अगर (err) अणु
		dev_err(dev, "Failed to power up HW : %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_vde_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tegra_vde *vde;
	पूर्णांक irq, err;

	vde = devm_kzalloc(dev, माप(*vde), GFP_KERNEL);
	अगर (!vde)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, vde);

	vde->sxe = devm_platक्रमm_ioremap_resource_byname(pdev, "sxe");
	अगर (IS_ERR(vde->sxe))
		वापस PTR_ERR(vde->sxe);

	vde->bsev = devm_platक्रमm_ioremap_resource_byname(pdev, "bsev");
	अगर (IS_ERR(vde->bsev))
		वापस PTR_ERR(vde->bsev);

	vde->mbe = devm_platक्रमm_ioremap_resource_byname(pdev, "mbe");
	अगर (IS_ERR(vde->mbe))
		वापस PTR_ERR(vde->mbe);

	vde->ppe = devm_platक्रमm_ioremap_resource_byname(pdev, "ppe");
	अगर (IS_ERR(vde->ppe))
		वापस PTR_ERR(vde->ppe);

	vde->mce = devm_platक्रमm_ioremap_resource_byname(pdev, "mce");
	अगर (IS_ERR(vde->mce))
		वापस PTR_ERR(vde->mce);

	vde->tfe = devm_platक्रमm_ioremap_resource_byname(pdev, "tfe");
	अगर (IS_ERR(vde->tfe))
		वापस PTR_ERR(vde->tfe);

	vde->ppb = devm_platक्रमm_ioremap_resource_byname(pdev, "ppb");
	अगर (IS_ERR(vde->ppb))
		वापस PTR_ERR(vde->ppb);

	vde->vdma = devm_platक्रमm_ioremap_resource_byname(pdev, "vdma");
	अगर (IS_ERR(vde->vdma))
		वापस PTR_ERR(vde->vdma);

	vde->frameid = devm_platक्रमm_ioremap_resource_byname(pdev, "frameid");
	अगर (IS_ERR(vde->frameid))
		वापस PTR_ERR(vde->frameid);

	vde->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(vde->clk)) अणु
		err = PTR_ERR(vde->clk);
		dev_err(dev, "Could not get VDE clk %d\n", err);
		वापस err;
	पूर्ण

	vde->rst = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(vde->rst)) अणु
		err = PTR_ERR(vde->rst);
		dev_err(dev, "Could not get VDE reset %d\n", err);
		वापस err;
	पूर्ण

	vde->rst_mc = devm_reset_control_get_optional(dev, "mc");
	अगर (IS_ERR(vde->rst_mc)) अणु
		err = PTR_ERR(vde->rst_mc);
		dev_err(dev, "Could not get MC reset %d\n", err);
		वापस err;
	पूर्ण

	irq = platक्रमm_get_irq_byname(pdev, "sync-token");
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(dev, irq, tegra_vde_isr, 0,
			       dev_name(dev), vde);
	अगर (err) अणु
		dev_err(dev, "Could not request IRQ %d\n", err);
		वापस err;
	पूर्ण

	vde->iram_pool = of_gen_pool_get(dev->of_node, "iram", 0);
	अगर (!vde->iram_pool) अणु
		dev_err(dev, "Could not get IRAM pool\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	vde->iram = gen_pool_dma_alloc(vde->iram_pool,
				       gen_pool_size(vde->iram_pool),
				       &vde->iram_lists_addr);
	अगर (!vde->iram) अणु
		dev_err(dev, "Could not reserve IRAM\n");
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&vde->map_list);
	mutex_init(&vde->map_lock);
	mutex_init(&vde->lock);
	init_completion(&vde->decode_completion);

	vde->miscdev.minor = MISC_DYNAMIC_MINOR;
	vde->miscdev.name = "tegra_vde";
	vde->miscdev.fops = &tegra_vde_fops;
	vde->miscdev.parent = dev;

	err = tegra_vde_iommu_init(vde);
	अगर (err) अणु
		dev_err(dev, "Failed to initialize IOMMU: %d\n", err);
		जाओ err_gen_मुक्त;
	पूर्ण

	err = misc_रेजिस्टर(&vde->miscdev);
	अगर (err) अणु
		dev_err(dev, "Failed to register misc device: %d\n", err);
		जाओ err_deinit_iommu;
	पूर्ण

	pm_runसमय_enable(dev);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 300);

	/*
	 * VDE partition may be left ON after bootloader, hence let's
	 * घातer-cycle it in order to put hardware पूर्णांकo a predictable lower
	 * घातer state.
	 */
	pm_runसमय_get_sync(dev);
	pm_runसमय_put(dev);

	वापस 0;

err_deinit_iommu:
	tegra_vde_iommu_deinit(vde);

err_gen_मुक्त:
	gen_pool_मुक्त(vde->iram_pool, (अचिन्हित दीर्घ)vde->iram,
		      gen_pool_size(vde->iram_pool));

	वापस err;
पूर्ण

अटल पूर्णांक tegra_vde_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_vde *vde = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;

	pm_runसमय_get_sync(dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);

	/*
	 * Balance RPM state, the VDE घातer करोमुख्य is left ON and hardware
	 * is घड़ी-gated. It's safe to reboot machine now.
	 */
	pm_runसमय_put_noidle(dev);
	clk_disable_unprepare(vde->clk);

	misc_deरेजिस्टर(&vde->miscdev);

	tegra_vde_dmabuf_cache_unmap_all(vde);
	tegra_vde_iommu_deinit(vde);

	gen_pool_मुक्त(vde->iram_pool, (अचिन्हित दीर्घ)vde->iram,
		      gen_pool_size(vde->iram_pool));

	वापस 0;
पूर्ण

अटल व्योम tegra_vde_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	/*
	 * On some devices bootloader isn't पढ़ोy to a घातer-gated VDE on
	 * a warm-reboot, machine will hang in that हाल.
	 */
	अगर (pm_runसमय_status_suspended(&pdev->dev))
		tegra_vde_runसमय_resume(&pdev->dev);
पूर्ण

अटल __maybe_unused पूर्णांक tegra_vde_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_vde *vde = dev_get_drvdata(dev);
	पूर्णांक err;

	mutex_lock(&vde->lock);

	err = pm_runसमय_क्रमce_suspend(dev);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक tegra_vde_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_vde *vde = dev_get_drvdata(dev);
	पूर्णांक err;

	err = pm_runसमय_क्रमce_resume(dev);
	अगर (err < 0)
		वापस err;

	mutex_unlock(&vde->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_vde_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_vde_runसमय_suspend,
			   tegra_vde_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(tegra_vde_pm_suspend,
				tegra_vde_pm_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_vde_of_match[] = अणु
	अणु .compatible = "nvidia,tegra20-vde", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_vde_of_match);

अटल काष्ठा platक्रमm_driver tegra_vde_driver = अणु
	.probe		= tegra_vde_probe,
	.हटाओ		= tegra_vde_हटाओ,
	.shutकरोwn	= tegra_vde_shutकरोwn,
	.driver		= अणु
		.name		= "tegra-vde",
		.of_match_table = tegra_vde_of_match,
		.pm		= &tegra_vde_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_vde_driver);

MODULE_DESCRIPTION("NVIDIA Tegra Video Decoder driver");
MODULE_AUTHOR("Dmitry Osipenko <digetx@gmail.com>");
MODULE_LICENSE("GPL");
