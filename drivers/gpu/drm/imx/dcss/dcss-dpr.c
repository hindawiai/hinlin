<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश "dcss-dev.h"

#घोषणा DCSS_DPR_SYSTEM_CTRL0			0x000
#घोषणा   RUN_EN				BIT(0)
#घोषणा   SOFT_RESET				BIT(1)
#घोषणा   REPEAT_EN				BIT(2)
#घोषणा   SHADOW_LOAD_EN			BIT(3)
#घोषणा   SW_SHADOW_LOAD_SEL			BIT(4)
#घोषणा   BCMD2AXI_MSTR_ID_CTRL			BIT(16)
#घोषणा DCSS_DPR_IRQ_MASK			0x020
#घोषणा DCSS_DPR_IRQ_MASK_STATUS		0x030
#घोषणा DCSS_DPR_IRQ_NONMASK_STATUS		0x040
#घोषणा   IRQ_DPR_CTRL_DONE			BIT(0)
#घोषणा   IRQ_DPR_RUN				BIT(1)
#घोषणा   IRQ_DPR_SHADOW_LOADED			BIT(2)
#घोषणा   IRQ_AXI_READ_ERR			BIT(3)
#घोषणा   DPR2RTR_YRGB_FIFO_OVFL		BIT(4)
#घोषणा   DPR2RTR_UV_FIFO_OVFL			BIT(5)
#घोषणा   DPR2RTR_FIFO_LD_BUF_RDY_YRGB_ERR	BIT(6)
#घोषणा   DPR2RTR_FIFO_LD_BUF_RDY_UV_ERR	BIT(7)
#घोषणा DCSS_DPR_MODE_CTRL0			0x050
#घोषणा   RTR_3BUF_EN				BIT(0)
#घोषणा   RTR_4LINE_BUF_EN			BIT(1)
#घोषणा   TILE_TYPE_POS				2
#घोषणा   TILE_TYPE_MASK			GENMASK(4, 2)
#घोषणा   YUV_EN				BIT(6)
#घोषणा   COMP_2PLANE_EN			BIT(7)
#घोषणा   PIX_SIZE_POS				8
#घोषणा   PIX_SIZE_MASK				GENMASK(9, 8)
#घोषणा   PIX_LUMA_UV_SWAP			BIT(10)
#घोषणा   PIX_UV_SWAP				BIT(11)
#घोषणा   B_COMP_SEL_POS			12
#घोषणा   B_COMP_SEL_MASK			GENMASK(13, 12)
#घोषणा   G_COMP_SEL_POS			14
#घोषणा   G_COMP_SEL_MASK			GENMASK(15, 14)
#घोषणा   R_COMP_SEL_POS			16
#घोषणा   R_COMP_SEL_MASK			GENMASK(17, 16)
#घोषणा   A_COMP_SEL_POS			18
#घोषणा   A_COMP_SEL_MASK			GENMASK(19, 18)
#घोषणा DCSS_DPR_FRAME_CTRL0			0x070
#घोषणा   HFLIP_EN				BIT(0)
#घोषणा   VFLIP_EN				BIT(1)
#घोषणा   ROT_ENC_POS				2
#घोषणा   ROT_ENC_MASK				GENMASK(3, 2)
#घोषणा   ROT_FLIP_ORDER_EN			BIT(4)
#घोषणा   PITCH_POS				16
#घोषणा   PITCH_MASK				GENMASK(31, 16)
#घोषणा DCSS_DPR_FRAME_1P_CTRL0			0x090
#घोषणा DCSS_DPR_FRAME_1P_PIX_X_CTRL		0x0A0
#घोषणा DCSS_DPR_FRAME_1P_PIX_Y_CTRL		0x0B0
#घोषणा DCSS_DPR_FRAME_1P_BASE_ADDR		0x0C0
#घोषणा DCSS_DPR_FRAME_2P_CTRL0			0x0E0
#घोषणा DCSS_DPR_FRAME_2P_PIX_X_CTRL		0x0F0
#घोषणा DCSS_DPR_FRAME_2P_PIX_Y_CTRL		0x100
#घोषणा DCSS_DPR_FRAME_2P_BASE_ADDR		0x110
#घोषणा DCSS_DPR_STATUS_CTRL0			0x130
#घोषणा   STATUS_MUX_SEL_MASK			GENMASK(2, 0)
#घोषणा   STATUS_SRC_SEL_POS			16
#घोषणा   STATUS_SRC_SEL_MASK			GENMASK(18, 16)
#घोषणा DCSS_DPR_STATUS_CTRL1			0x140
#घोषणा DCSS_DPR_RTRAM_CTRL0			0x200
#घोषणा   NUM_ROWS_ACTIVE			BIT(0)
#घोषणा   THRES_HIGH_POS			1
#घोषणा   THRES_HIGH_MASK			GENMASK(3, 1)
#घोषणा   THRES_LOW_POS				4
#घोषणा   THRES_LOW_MASK			GENMASK(6, 4)
#घोषणा   ABORT_SEL				BIT(7)

क्रमागत dcss_tile_type अणु
	TILE_LINEAR = 0,
	TILE_GPU_STANDARD,
	TILE_GPU_SUPER,
	TILE_VPU_YUV420,
	TILE_VPU_VP9,
पूर्ण;

क्रमागत dcss_pix_size अणु
	PIX_SIZE_8,
	PIX_SIZE_16,
	PIX_SIZE_32,
पूर्ण;

काष्ठा dcss_dpr_ch अणु
	काष्ठा dcss_dpr *dpr;
	व्योम __iomem *base_reg;
	u32 base_ofs;

	काष्ठा drm_क्रमmat_info क्रमmat;
	क्रमागत dcss_pix_size pix_size;
	क्रमागत dcss_tile_type tile;
	bool rtram_4line_en;
	bool rtram_3buf_en;

	u32 frame_ctrl;
	u32 mode_ctrl;
	u32 sys_ctrl;
	u32 rtram_ctrl;

	bool sys_ctrl_chgd;

	पूर्णांक ch_num;
	पूर्णांक irq;
पूर्ण;

काष्ठा dcss_dpr अणु
	काष्ठा device *dev;
	काष्ठा dcss_ctxld *ctxld;
	u32  ctx_id;

	काष्ठा dcss_dpr_ch ch[3];
पूर्ण;

अटल व्योम dcss_dpr_ग_लिखो(काष्ठा dcss_dpr_ch *ch, u32 val, u32 ofs)
अणु
	काष्ठा dcss_dpr *dpr = ch->dpr;

	dcss_ctxld_ग_लिखो(dpr->ctxld, dpr->ctx_id, val, ch->base_ofs + ofs);
पूर्ण

अटल पूर्णांक dcss_dpr_ch_init_all(काष्ठा dcss_dpr *dpr, अचिन्हित दीर्घ dpr_base)
अणु
	काष्ठा dcss_dpr_ch *ch;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		ch = &dpr->ch[i];

		ch->base_ofs = dpr_base + i * 0x1000;

		ch->base_reg = ioremap(ch->base_ofs, SZ_4K);
		अगर (!ch->base_reg) अणु
			dev_err(dpr->dev, "dpr: unable to remap ch %d base\n",
				i);
			वापस -ENOMEM;
		पूर्ण

		ch->dpr = dpr;
		ch->ch_num = i;

		dcss_ग_लिखोl(0xff, ch->base_reg + DCSS_DPR_IRQ_MASK);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dcss_dpr_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ dpr_base)
अणु
	काष्ठा dcss_dpr *dpr;

	dpr = kzalloc(माप(*dpr), GFP_KERNEL);
	अगर (!dpr)
		वापस -ENOMEM;

	dcss->dpr = dpr;
	dpr->dev = dcss->dev;
	dpr->ctxld = dcss->ctxld;
	dpr->ctx_id = CTX_SB_HP;

	अगर (dcss_dpr_ch_init_all(dpr, dpr_base)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 3; i++) अणु
			अगर (dpr->ch[i].base_reg)
				iounmap(dpr->ch[i].base_reg);
		पूर्ण

		kमुक्त(dpr);

		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम dcss_dpr_निकास(काष्ठा dcss_dpr *dpr)
अणु
	पूर्णांक ch_no;

	/* stop DPR on all channels */
	क्रम (ch_no = 0; ch_no < 3; ch_no++) अणु
		काष्ठा dcss_dpr_ch *ch = &dpr->ch[ch_no];

		dcss_ग_लिखोl(0, ch->base_reg + DCSS_DPR_SYSTEM_CTRL0);

		अगर (ch->base_reg)
			iounmap(ch->base_reg);
	पूर्ण

	kमुक्त(dpr);
पूर्ण

अटल u32 dcss_dpr_x_pix_wide_adjust(काष्ठा dcss_dpr_ch *ch, u32 pix_wide,
				      u32 pix_क्रमmat)
अणु
	u8 pix_in_64byte_map[3][5] = अणु
		/* LIN, GPU_STD, GPU_SUP, VPU_YUV420, VPU_VP9 */
		अणु   64,       8,       8,          8,     16पूर्ण, /* PIX_SIZE_8  */
		अणु   32,       8,       8,          8,      8पूर्ण, /* PIX_SIZE_16 */
		अणु   16,       4,       4,          8,      8पूर्ण, /* PIX_SIZE_32 */
	पूर्ण;
	u32 offset;
	u32 भाग_64byte_mod, pix_in_64byte;

	pix_in_64byte = pix_in_64byte_map[ch->pix_size][ch->tile];

	भाग_64byte_mod = pix_wide % pix_in_64byte;
	offset = (भाग_64byte_mod == 0) ? 0 : (pix_in_64byte - भाग_64byte_mod);

	वापस pix_wide + offset;
पूर्ण

अटल u32 dcss_dpr_y_pix_high_adjust(काष्ठा dcss_dpr_ch *ch, u32 pix_high,
				      u32 pix_क्रमmat)
अणु
	u8 num_rows_buf = ch->rtram_4line_en ? 4 : 8;
	u32 offset, pix_y_mod;

	pix_y_mod = pix_high % num_rows_buf;
	offset = pix_y_mod ? (num_rows_buf - pix_y_mod) : 0;

	वापस pix_high + offset;
पूर्ण

व्योम dcss_dpr_set_res(काष्ठा dcss_dpr *dpr, पूर्णांक ch_num, u32 xres, u32 yres)
अणु
	काष्ठा dcss_dpr_ch *ch = &dpr->ch[ch_num];
	u32 pix_क्रमmat = ch->क्रमmat.क्रमmat;
	u32 gap = DCSS_DPR_FRAME_2P_BASE_ADDR - DCSS_DPR_FRAME_1P_BASE_ADDR;
	पूर्णांक plane, max_planes = 1;
	u32 pix_x_wide, pix_y_high;

	अगर (pix_क्रमmat == DRM_FORMAT_NV12 ||
	    pix_क्रमmat == DRM_FORMAT_NV21)
		max_planes = 2;

	क्रम (plane = 0; plane < max_planes; plane++) अणु
		yres = plane == 1 ? yres >> 1 : yres;

		pix_x_wide = dcss_dpr_x_pix_wide_adjust(ch, xres, pix_क्रमmat);
		pix_y_high = dcss_dpr_y_pix_high_adjust(ch, yres, pix_क्रमmat);

		dcss_dpr_ग_लिखो(ch, pix_x_wide,
			       DCSS_DPR_FRAME_1P_PIX_X_CTRL + plane * gap);
		dcss_dpr_ग_लिखो(ch, pix_y_high,
			       DCSS_DPR_FRAME_1P_PIX_Y_CTRL + plane * gap);

		dcss_dpr_ग_लिखो(ch, 2, DCSS_DPR_FRAME_1P_CTRL0 + plane * gap);
	पूर्ण
पूर्ण

व्योम dcss_dpr_addr_set(काष्ठा dcss_dpr *dpr, पूर्णांक ch_num, u32 luma_base_addr,
		       u32 chroma_base_addr, u16 pitch)
अणु
	काष्ठा dcss_dpr_ch *ch = &dpr->ch[ch_num];

	dcss_dpr_ग_लिखो(ch, luma_base_addr, DCSS_DPR_FRAME_1P_BASE_ADDR);

	dcss_dpr_ग_लिखो(ch, chroma_base_addr, DCSS_DPR_FRAME_2P_BASE_ADDR);

	ch->frame_ctrl &= ~PITCH_MASK;
	ch->frame_ctrl |= (((u32)pitch << PITCH_POS) & PITCH_MASK);
पूर्ण

अटल व्योम dcss_dpr_argb_comp_sel(काष्ठा dcss_dpr_ch *ch, पूर्णांक a_sel, पूर्णांक r_sel,
				   पूर्णांक g_sel, पूर्णांक b_sel)
अणु
	u32 sel;

	sel = ((a_sel << A_COMP_SEL_POS) & A_COMP_SEL_MASK) |
	      ((r_sel << R_COMP_SEL_POS) & R_COMP_SEL_MASK) |
	      ((g_sel << G_COMP_SEL_POS) & G_COMP_SEL_MASK) |
	      ((b_sel << B_COMP_SEL_POS) & B_COMP_SEL_MASK);

	ch->mode_ctrl &= ~(A_COMP_SEL_MASK | R_COMP_SEL_MASK |
			   G_COMP_SEL_MASK | B_COMP_SEL_MASK);
	ch->mode_ctrl |= sel;
पूर्ण

अटल व्योम dcss_dpr_pix_size_set(काष्ठा dcss_dpr_ch *ch,
				  स्थिर काष्ठा drm_क्रमmat_info *क्रमmat)
अणु
	u32 val;

	चयन (क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV21:
		val = PIX_SIZE_8;
		अवरोध;

	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_VYUY:
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_YVYU:
		val = PIX_SIZE_16;
		अवरोध;

	शेष:
		val = PIX_SIZE_32;
		अवरोध;
	पूर्ण

	ch->pix_size = val;

	ch->mode_ctrl &= ~PIX_SIZE_MASK;
	ch->mode_ctrl |= ((val << PIX_SIZE_POS) & PIX_SIZE_MASK);
पूर्ण

अटल व्योम dcss_dpr_uv_swap(काष्ठा dcss_dpr_ch *ch, bool swap)
अणु
	ch->mode_ctrl &= ~PIX_UV_SWAP;
	ch->mode_ctrl |= (swap ? PIX_UV_SWAP : 0);
पूर्ण

अटल व्योम dcss_dpr_y_uv_swap(काष्ठा dcss_dpr_ch *ch, bool swap)
अणु
	ch->mode_ctrl &= ~PIX_LUMA_UV_SWAP;
	ch->mode_ctrl |= (swap ? PIX_LUMA_UV_SWAP : 0);
पूर्ण

अटल व्योम dcss_dpr_2plane_en(काष्ठा dcss_dpr_ch *ch, bool en)
अणु
	ch->mode_ctrl &= ~COMP_2PLANE_EN;
	ch->mode_ctrl |= (en ? COMP_2PLANE_EN : 0);
पूर्ण

अटल व्योम dcss_dpr_yuv_en(काष्ठा dcss_dpr_ch *ch, bool en)
अणु
	ch->mode_ctrl &= ~YUV_EN;
	ch->mode_ctrl |= (en ? YUV_EN : 0);
पूर्ण

व्योम dcss_dpr_enable(काष्ठा dcss_dpr *dpr, पूर्णांक ch_num, bool en)
अणु
	काष्ठा dcss_dpr_ch *ch = &dpr->ch[ch_num];
	u32 sys_ctrl;

	sys_ctrl = (en ? REPEAT_EN | RUN_EN : 0);

	अगर (en) अणु
		dcss_dpr_ग_लिखो(ch, ch->mode_ctrl, DCSS_DPR_MODE_CTRL0);
		dcss_dpr_ग_लिखो(ch, ch->frame_ctrl, DCSS_DPR_FRAME_CTRL0);
		dcss_dpr_ग_लिखो(ch, ch->rtram_ctrl, DCSS_DPR_RTRAM_CTRL0);
	पूर्ण

	अगर (ch->sys_ctrl != sys_ctrl)
		ch->sys_ctrl_chgd = true;

	ch->sys_ctrl = sys_ctrl;
पूर्ण

काष्ठा rgb_comp_sel अणु
	u32 drm_क्रमmat;
	पूर्णांक a_sel;
	पूर्णांक r_sel;
	पूर्णांक g_sel;
	पूर्णांक b_sel;
पूर्ण;

अटल काष्ठा rgb_comp_sel comp_sel_map[] = अणु
	अणुDRM_FORMAT_ARGB8888, 3, 2, 1, 0पूर्ण,
	अणुDRM_FORMAT_XRGB8888, 3, 2, 1, 0पूर्ण,
	अणुDRM_FORMAT_ABGR8888, 3, 0, 1, 2पूर्ण,
	अणुDRM_FORMAT_XBGR8888, 3, 0, 1, 2पूर्ण,
	अणुDRM_FORMAT_RGBA8888, 0, 3, 2, 1पूर्ण,
	अणुDRM_FORMAT_RGBX8888, 0, 3, 2, 1पूर्ण,
	अणुDRM_FORMAT_BGRA8888, 0, 1, 2, 3पूर्ण,
	अणुDRM_FORMAT_BGRX8888, 0, 1, 2, 3पूर्ण,
पूर्ण;

अटल पूर्णांक to_comp_sel(u32 pix_fmt, पूर्णांक *a_sel, पूर्णांक *r_sel, पूर्णांक *g_sel,
		       पूर्णांक *b_sel)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(comp_sel_map); i++) अणु
		अगर (comp_sel_map[i].drm_क्रमmat == pix_fmt) अणु
			*a_sel = comp_sel_map[i].a_sel;
			*r_sel = comp_sel_map[i].r_sel;
			*g_sel = comp_sel_map[i].g_sel;
			*b_sel = comp_sel_map[i].b_sel;

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम dcss_dpr_rtram_set(काष्ठा dcss_dpr_ch *ch, u32 pix_क्रमmat)
अणु
	u32 val, mask;

	चयन (pix_क्रमmat) अणु
	हाल DRM_FORMAT_NV21:
	हाल DRM_FORMAT_NV12:
		ch->rtram_3buf_en = true;
		ch->rtram_4line_en = false;
		अवरोध;

	शेष:
		ch->rtram_3buf_en = true;
		ch->rtram_4line_en = true;
		अवरोध;
	पूर्ण

	val = (ch->rtram_4line_en ? RTR_4LINE_BUF_EN : 0);
	val |= (ch->rtram_3buf_en ? RTR_3BUF_EN : 0);
	mask = RTR_4LINE_BUF_EN | RTR_3BUF_EN;

	ch->mode_ctrl &= ~mask;
	ch->mode_ctrl |= (val & mask);

	val = (ch->rtram_4line_en ? 0 : NUM_ROWS_ACTIVE);
	val |= (3 << THRES_LOW_POS) & THRES_LOW_MASK;
	val |= (4 << THRES_HIGH_POS) & THRES_HIGH_MASK;
	mask = THRES_LOW_MASK | THRES_HIGH_MASK | NUM_ROWS_ACTIVE;

	ch->rtram_ctrl &= ~mask;
	ch->rtram_ctrl |= (val & mask);
पूर्ण

अटल व्योम dcss_dpr_setup_components(काष्ठा dcss_dpr_ch *ch,
				      स्थिर काष्ठा drm_क्रमmat_info *क्रमmat)
अणु
	पूर्णांक a_sel, r_sel, g_sel, b_sel;
	bool uv_swap, y_uv_swap;

	चयन (क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_YVYU:
		uv_swap = true;
		y_uv_swap = true;
		अवरोध;

	हाल DRM_FORMAT_VYUY:
	हाल DRM_FORMAT_NV21:
		uv_swap = true;
		y_uv_swap = false;
		अवरोध;

	हाल DRM_FORMAT_YUYV:
		uv_swap = false;
		y_uv_swap = true;
		अवरोध;

	शेष:
		uv_swap = false;
		y_uv_swap = false;
		अवरोध;
	पूर्ण

	dcss_dpr_uv_swap(ch, uv_swap);

	dcss_dpr_y_uv_swap(ch, y_uv_swap);

	अगर (!क्रमmat->is_yuv) अणु
		अगर (!to_comp_sel(क्रमmat->क्रमmat, &a_sel, &r_sel,
				 &g_sel, &b_sel)) अणु
			dcss_dpr_argb_comp_sel(ch, a_sel, r_sel, g_sel, b_sel);
		पूर्ण अन्यथा अणु
			dcss_dpr_argb_comp_sel(ch, 3, 2, 1, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		dcss_dpr_argb_comp_sel(ch, 0, 0, 0, 0);
	पूर्ण
पूर्ण

अटल व्योम dcss_dpr_tile_set(काष्ठा dcss_dpr_ch *ch, uपूर्णांक64_t modअगरier)
अणु
	चयन (ch->ch_num) अणु
	हाल 0:
		चयन (modअगरier) अणु
		हाल DRM_FORMAT_MOD_LINEAR:
			ch->tile = TILE_LINEAR;
			अवरोध;
		हाल DRM_FORMAT_MOD_VIVANTE_TILED:
			ch->tile = TILE_GPU_STANDARD;
			अवरोध;
		हाल DRM_FORMAT_MOD_VIVANTE_SUPER_TILED:
			ch->tile = TILE_GPU_SUPER;
			अवरोध;
		शेष:
			WARN_ON(1);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 1:
	हाल 2:
		ch->tile = TILE_LINEAR;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	ch->mode_ctrl &= ~TILE_TYPE_MASK;
	ch->mode_ctrl |= ((ch->tile << TILE_TYPE_POS) & TILE_TYPE_MASK);
पूर्ण

व्योम dcss_dpr_क्रमmat_set(काष्ठा dcss_dpr *dpr, पूर्णांक ch_num,
			 स्थिर काष्ठा drm_क्रमmat_info *क्रमmat, u64 modअगरier)
अणु
	काष्ठा dcss_dpr_ch *ch = &dpr->ch[ch_num];

	ch->क्रमmat = *क्रमmat;

	dcss_dpr_yuv_en(ch, क्रमmat->is_yuv);

	dcss_dpr_pix_size_set(ch, क्रमmat);

	dcss_dpr_setup_components(ch, क्रमmat);

	dcss_dpr_2plane_en(ch, क्रमmat->num_planes == 2);

	dcss_dpr_rtram_set(ch, क्रमmat->क्रमmat);

	dcss_dpr_tile_set(ch, modअगरier);
पूर्ण

/* This function will be called from पूर्णांकerrupt context. */
व्योम dcss_dpr_ग_लिखो_sysctrl(काष्ठा dcss_dpr *dpr)
अणु
	पूर्णांक chnum;

	dcss_ctxld_निश्चित_locked(dpr->ctxld);

	क्रम (chnum = 0; chnum < 3; chnum++) अणु
		काष्ठा dcss_dpr_ch *ch = &dpr->ch[chnum];

		अगर (ch->sys_ctrl_chgd) अणु
			dcss_ctxld_ग_लिखो_irqsafe(dpr->ctxld, dpr->ctx_id,
						 ch->sys_ctrl,
						 ch->base_ofs +
						 DCSS_DPR_SYSTEM_CTRL0);
			ch->sys_ctrl_chgd = false;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dcss_dpr_set_rotation(काष्ठा dcss_dpr *dpr, पूर्णांक ch_num, u32 rotation)
अणु
	काष्ठा dcss_dpr_ch *ch = &dpr->ch[ch_num];

	ch->frame_ctrl &= ~(HFLIP_EN | VFLIP_EN | ROT_ENC_MASK);

	ch->frame_ctrl |= rotation & DRM_MODE_REFLECT_X ? HFLIP_EN : 0;
	ch->frame_ctrl |= rotation & DRM_MODE_REFLECT_Y ? VFLIP_EN : 0;

	अगर (rotation & DRM_MODE_ROTATE_90)
		ch->frame_ctrl |= 1 << ROT_ENC_POS;
	अन्यथा अगर (rotation & DRM_MODE_ROTATE_180)
		ch->frame_ctrl |= 2 << ROT_ENC_POS;
	अन्यथा अगर (rotation & DRM_MODE_ROTATE_270)
		ch->frame_ctrl |= 3 << ROT_ENC_POS;
पूर्ण
