<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "dcss-dev.h"

#घोषणा DCSS_DTG_TC_CONTROL_STATUS			0x00
#घोषणा   CH3_EN					BIT(0)
#घोषणा   CH2_EN					BIT(1)
#घोषणा   CH1_EN					BIT(2)
#घोषणा   OVL_DATA_MODE					BIT(3)
#घोषणा   BLENDER_VIDEO_ALPHA_SEL			BIT(7)
#घोषणा   DTG_START					BIT(8)
#घोषणा   DBY_MODE_EN					BIT(9)
#घोषणा   CH1_ALPHA_SEL					BIT(10)
#घोषणा   CSS_PIX_COMP_SWAP_POS				12
#घोषणा   CSS_PIX_COMP_SWAP_MASK			GENMASK(14, 12)
#घोषणा   DEFAULT_FG_ALPHA_POS				24
#घोषणा   DEFAULT_FG_ALPHA_MASK				GENMASK(31, 24)
#घोषणा DCSS_DTG_TC_DTG					0x04
#घोषणा DCSS_DTG_TC_DISP_TOP				0x08
#घोषणा DCSS_DTG_TC_DISP_BOT				0x0C
#घोषणा DCSS_DTG_TC_CH1_TOP				0x10
#घोषणा DCSS_DTG_TC_CH1_BOT				0x14
#घोषणा DCSS_DTG_TC_CH2_TOP				0x18
#घोषणा DCSS_DTG_TC_CH2_BOT				0x1C
#घोषणा DCSS_DTG_TC_CH3_TOP				0x20
#घोषणा DCSS_DTG_TC_CH3_BOT				0x24
#घोषणा   TC_X_POS					0
#घोषणा   TC_X_MASK					GENMASK(12, 0)
#घोषणा   TC_Y_POS					16
#घोषणा   TC_Y_MASK					GENMASK(28, 16)
#घोषणा DCSS_DTG_TC_CTXLD				0x28
#घोषणा   TC_CTXLD_DB_Y_POS				0
#घोषणा   TC_CTXLD_DB_Y_MASK				GENMASK(12, 0)
#घोषणा   TC_CTXLD_SB_Y_POS				16
#घोषणा   TC_CTXLD_SB_Y_MASK				GENMASK(28, 16)
#घोषणा DCSS_DTG_TC_CH1_BKRND				0x2C
#घोषणा DCSS_DTG_TC_CH2_BKRND				0x30
#घोषणा   BKRND_R_Y_COMP_POS				20
#घोषणा   BKRND_R_Y_COMP_MASK				GENMASK(29, 20)
#घोषणा   BKRND_G_U_COMP_POS				10
#घोषणा   BKRND_G_U_COMP_MASK				GENMASK(19, 10)
#घोषणा   BKRND_B_V_COMP_POS				0
#घोषणा   BKRND_B_V_COMP_MASK				GENMASK(9, 0)
#घोषणा DCSS_DTG_BLENDER_DBY_RANGEINV			0x38
#घोषणा DCSS_DTG_BLENDER_DBY_RANGEMIN			0x3C
#घोषणा DCSS_DTG_BLENDER_DBY_BDP			0x40
#घोषणा DCSS_DTG_BLENDER_BKRND_I			0x44
#घोषणा DCSS_DTG_BLENDER_BKRND_P			0x48
#घोषणा DCSS_DTG_BLENDER_BKRND_T			0x4C
#घोषणा DCSS_DTG_LINE0_INT				0x50
#घोषणा DCSS_DTG_LINE1_INT				0x54
#घोषणा DCSS_DTG_BG_ALPHA_DEFAULT			0x58
#घोषणा DCSS_DTG_INT_STATUS				0x5C
#घोषणा DCSS_DTG_INT_CONTROL				0x60
#घोषणा DCSS_DTG_TC_CH3_BKRND				0x64
#घोषणा DCSS_DTG_INT_MASK				0x68
#घोषणा   LINE0_IRQ					BIT(0)
#घोषणा   LINE1_IRQ					BIT(1)
#घोषणा   LINE2_IRQ					BIT(2)
#घोषणा   LINE3_IRQ					BIT(3)
#घोषणा DCSS_DTG_LINE2_INT				0x6C
#घोषणा DCSS_DTG_LINE3_INT				0x70
#घोषणा DCSS_DTG_DBY_OL					0x74
#घोषणा DCSS_DTG_DBY_BL					0x78
#घोषणा DCSS_DTG_DBY_EL					0x7C

काष्ठा dcss_dtg अणु
	काष्ठा device *dev;
	काष्ठा dcss_ctxld *ctxld;
	व्योम __iomem *base_reg;
	u32 base_ofs;

	u32 ctx_id;

	bool in_use;

	u32 dis_ulc_x;
	u32 dis_ulc_y;

	u32 control_status;
	u32 alpha;
	u32 alpha_cfg;

	पूर्णांक ctxld_kick_irq;
	bool ctxld_kick_irq_en;
पूर्ण;

अटल व्योम dcss_dtg_ग_लिखो(काष्ठा dcss_dtg *dtg, u32 val, u32 ofs)
अणु
	अगर (!dtg->in_use)
		dcss_ग_लिखोl(val, dtg->base_reg + ofs);

	dcss_ctxld_ग_लिखो(dtg->ctxld, dtg->ctx_id,
			 val, dtg->base_ofs + ofs);
पूर्ण

अटल irqवापस_t dcss_dtg_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा dcss_dtg *dtg = data;
	u32 status;

	status = dcss_पढ़ोl(dtg->base_reg + DCSS_DTG_INT_STATUS);

	अगर (!(status & LINE0_IRQ))
		वापस IRQ_NONE;

	dcss_ctxld_kick(dtg->ctxld);

	dcss_ग_लिखोl(status & LINE0_IRQ, dtg->base_reg + DCSS_DTG_INT_CONTROL);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dcss_dtg_irq_config(काष्ठा dcss_dtg *dtg,
			       काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	dtg->ctxld_kick_irq = platक्रमm_get_irq_byname(pdev, "ctxld_kick");
	अगर (dtg->ctxld_kick_irq < 0)
		वापस dtg->ctxld_kick_irq;

	dcss_update(0, LINE0_IRQ | LINE1_IRQ,
		    dtg->base_reg + DCSS_DTG_INT_MASK);

	ret = request_irq(dtg->ctxld_kick_irq, dcss_dtg_irq_handler,
			  0, "dcss_ctxld_kick", dtg);
	अगर (ret) अणु
		dev_err(dtg->dev, "dtg: irq request failed.\n");
		वापस ret;
	पूर्ण

	disable_irq(dtg->ctxld_kick_irq);

	dtg->ctxld_kick_irq_en = false;

	वापस 0;
पूर्ण

पूर्णांक dcss_dtg_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ dtg_base)
अणु
	पूर्णांक ret = 0;
	काष्ठा dcss_dtg *dtg;

	dtg = kzalloc(माप(*dtg), GFP_KERNEL);
	अगर (!dtg)
		वापस -ENOMEM;

	dcss->dtg = dtg;
	dtg->dev = dcss->dev;
	dtg->ctxld = dcss->ctxld;

	dtg->base_reg = ioremap(dtg_base, SZ_4K);
	अगर (!dtg->base_reg) अणु
		dev_err(dcss->dev, "dtg: unable to remap dtg base\n");
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	dtg->base_ofs = dtg_base;
	dtg->ctx_id = CTX_DB;

	dtg->alpha = 255;

	dtg->control_status |= OVL_DATA_MODE | BLENDER_VIDEO_ALPHA_SEL |
		((dtg->alpha << DEFAULT_FG_ALPHA_POS) & DEFAULT_FG_ALPHA_MASK);

	ret = dcss_dtg_irq_config(dtg, to_platक्रमm_device(dcss->dev));
	अगर (ret)
		जाओ err_irq;

	वापस 0;

err_irq:
	iounmap(dtg->base_reg);

err_ioremap:
	kमुक्त(dtg);

	वापस ret;
पूर्ण

व्योम dcss_dtg_निकास(काष्ठा dcss_dtg *dtg)
अणु
	मुक्त_irq(dtg->ctxld_kick_irq, dtg);

	अगर (dtg->base_reg)
		iounmap(dtg->base_reg);

	kमुक्त(dtg);
पूर्ण

व्योम dcss_dtg_sync_set(काष्ठा dcss_dtg *dtg, काष्ठा videomode *vm)
अणु
	काष्ठा dcss_dev *dcss = dcss_drv_dev_to_dcss(dtg->dev);
	u16 dtg_lrc_x, dtg_lrc_y;
	u16 dis_ulc_x, dis_ulc_y;
	u16 dis_lrc_x, dis_lrc_y;
	u32 sb_ctxld_trig, db_ctxld_trig;
	u32 pixघड़ी = vm->pixelघड़ी;
	u32 actual_clk;

	dtg_lrc_x = vm->hfront_porch + vm->hback_porch + vm->hsync_len +
		    vm->hactive - 1;
	dtg_lrc_y = vm->vfront_porch + vm->vback_porch + vm->vsync_len +
		    vm->vactive - 1;
	dis_ulc_x = vm->hsync_len + vm->hback_porch - 1;
	dis_ulc_y = vm->vsync_len + vm->vfront_porch + vm->vback_porch - 1;
	dis_lrc_x = vm->hsync_len + vm->hback_porch + vm->hactive - 1;
	dis_lrc_y = vm->vsync_len + vm->vfront_porch + vm->vback_porch +
		    vm->vactive - 1;

	clk_disable_unprepare(dcss->pix_clk);
	clk_set_rate(dcss->pix_clk, vm->pixelघड़ी);
	clk_prepare_enable(dcss->pix_clk);

	actual_clk = clk_get_rate(dcss->pix_clk);
	अगर (pixघड़ी != actual_clk) अणु
		dev_info(dtg->dev,
			 "Pixel clock set to %u kHz instead of %u kHz.\n",
			 (actual_clk / 1000), (pixघड़ी / 1000));
	पूर्ण

	dcss_dtg_ग_लिखो(dtg, ((dtg_lrc_y << TC_Y_POS) | dtg_lrc_x),
		       DCSS_DTG_TC_DTG);
	dcss_dtg_ग_लिखो(dtg, ((dis_ulc_y << TC_Y_POS) | dis_ulc_x),
		       DCSS_DTG_TC_DISP_TOP);
	dcss_dtg_ग_लिखो(dtg, ((dis_lrc_y << TC_Y_POS) | dis_lrc_x),
		       DCSS_DTG_TC_DISP_BOT);

	dtg->dis_ulc_x = dis_ulc_x;
	dtg->dis_ulc_y = dis_ulc_y;

	sb_ctxld_trig = ((0 * dis_lrc_y / 100) << TC_CTXLD_SB_Y_POS) &
							TC_CTXLD_SB_Y_MASK;
	db_ctxld_trig = ((99 * dis_lrc_y / 100) << TC_CTXLD_DB_Y_POS) &
							TC_CTXLD_DB_Y_MASK;

	dcss_dtg_ग_लिखो(dtg, sb_ctxld_trig | db_ctxld_trig, DCSS_DTG_TC_CTXLD);

	/* vblank trigger */
	dcss_dtg_ग_लिखो(dtg, 0, DCSS_DTG_LINE1_INT);

	/* CTXLD trigger */
	dcss_dtg_ग_लिखो(dtg, ((90 * dis_lrc_y) / 100) << 16, DCSS_DTG_LINE0_INT);
पूर्ण

व्योम dcss_dtg_plane_pos_set(काष्ठा dcss_dtg *dtg, पूर्णांक ch_num,
			    पूर्णांक px, पूर्णांक py, पूर्णांक pw, पूर्णांक ph)
अणु
	u16 p_ulc_x, p_ulc_y;
	u16 p_lrc_x, p_lrc_y;

	p_ulc_x = dtg->dis_ulc_x + px;
	p_ulc_y = dtg->dis_ulc_y + py;
	p_lrc_x = p_ulc_x + pw;
	p_lrc_y = p_ulc_y + ph;

	अगर (!px && !py && !pw && !ph) अणु
		dcss_dtg_ग_लिखो(dtg, 0, DCSS_DTG_TC_CH1_TOP + 0x8 * ch_num);
		dcss_dtg_ग_लिखो(dtg, 0, DCSS_DTG_TC_CH1_BOT + 0x8 * ch_num);
	पूर्ण अन्यथा अणु
		dcss_dtg_ग_लिखो(dtg, ((p_ulc_y << TC_Y_POS) | p_ulc_x),
			       DCSS_DTG_TC_CH1_TOP + 0x8 * ch_num);
		dcss_dtg_ग_लिखो(dtg, ((p_lrc_y << TC_Y_POS) | p_lrc_x),
			       DCSS_DTG_TC_CH1_BOT + 0x8 * ch_num);
	पूर्ण
पूर्ण

bool dcss_dtg_global_alpha_changed(काष्ठा dcss_dtg *dtg, पूर्णांक ch_num, पूर्णांक alpha)
अणु
	अगर (ch_num)
		वापस false;

	वापस alpha != dtg->alpha;
पूर्ण

व्योम dcss_dtg_plane_alpha_set(काष्ठा dcss_dtg *dtg, पूर्णांक ch_num,
			      स्थिर काष्ठा drm_क्रमmat_info *क्रमmat, पूर्णांक alpha)
अणु
	/* we care about alpha only when channel 0 is concerned */
	अगर (ch_num)
		वापस;

	/*
	 * Use global alpha अगर pixel क्रमmat करोes not have alpha channel or the
	 * user explicitly chose to use global alpha (i.e. alpha is not OPAQUE).
	 */
	अगर (!क्रमmat->has_alpha || alpha != 255)
		dtg->alpha_cfg = (alpha << DEFAULT_FG_ALPHA_POS) & DEFAULT_FG_ALPHA_MASK;
	अन्यथा /* use per-pixel alpha otherwise */
		dtg->alpha_cfg = CH1_ALPHA_SEL;

	dtg->alpha = alpha;
पूर्ण

व्योम dcss_dtg_css_set(काष्ठा dcss_dtg *dtg)
अणु
	dtg->control_status |=
			(0x5 << CSS_PIX_COMP_SWAP_POS) & CSS_PIX_COMP_SWAP_MASK;
पूर्ण

व्योम dcss_dtg_enable(काष्ठा dcss_dtg *dtg)
अणु
	dtg->control_status |= DTG_START;

	dtg->control_status &= ~(CH1_ALPHA_SEL | DEFAULT_FG_ALPHA_MASK);
	dtg->control_status |= dtg->alpha_cfg;

	dcss_dtg_ग_लिखो(dtg, dtg->control_status, DCSS_DTG_TC_CONTROL_STATUS);

	dtg->in_use = true;
पूर्ण

व्योम dcss_dtg_shutoff(काष्ठा dcss_dtg *dtg)
अणु
	dtg->control_status &= ~DTG_START;

	dcss_ग_लिखोl(dtg->control_status,
		    dtg->base_reg + DCSS_DTG_TC_CONTROL_STATUS);

	dtg->in_use = false;
पूर्ण

bool dcss_dtg_is_enabled(काष्ठा dcss_dtg *dtg)
अणु
	वापस dtg->in_use;
पूर्ण

व्योम dcss_dtg_ch_enable(काष्ठा dcss_dtg *dtg, पूर्णांक ch_num, bool en)
अणु
	u32 ch_en_map[] = अणुCH1_EN, CH2_EN, CH3_ENपूर्ण;
	u32 control_status;

	control_status = dtg->control_status & ~ch_en_map[ch_num];
	control_status |= en ? ch_en_map[ch_num] : 0;

	control_status &= ~(CH1_ALPHA_SEL | DEFAULT_FG_ALPHA_MASK);
	control_status |= dtg->alpha_cfg;

	अगर (dtg->control_status != control_status)
		dcss_dtg_ग_लिखो(dtg, control_status, DCSS_DTG_TC_CONTROL_STATUS);

	dtg->control_status = control_status;
पूर्ण

व्योम dcss_dtg_vblank_irq_enable(काष्ठा dcss_dtg *dtg, bool en)
अणु
	u32 status;
	u32 mask = en ? LINE1_IRQ : 0;

	अगर (en) अणु
		status = dcss_पढ़ोl(dtg->base_reg + DCSS_DTG_INT_STATUS);
		dcss_ग_लिखोl(status & LINE1_IRQ,
			    dtg->base_reg + DCSS_DTG_INT_CONTROL);
	पूर्ण

	dcss_update(mask, LINE1_IRQ, dtg->base_reg + DCSS_DTG_INT_MASK);
पूर्ण

व्योम dcss_dtg_ctxld_kick_irq_enable(काष्ठा dcss_dtg *dtg, bool en)
अणु
	u32 status;
	u32 mask = en ? LINE0_IRQ : 0;

	अगर (en) अणु
		status = dcss_पढ़ोl(dtg->base_reg + DCSS_DTG_INT_STATUS);

		अगर (!dtg->ctxld_kick_irq_en) अणु
			dcss_ग_लिखोl(status & LINE0_IRQ,
				    dtg->base_reg + DCSS_DTG_INT_CONTROL);
			enable_irq(dtg->ctxld_kick_irq);
			dtg->ctxld_kick_irq_en = true;
			dcss_update(mask, LINE0_IRQ,
				    dtg->base_reg + DCSS_DTG_INT_MASK);
		पूर्ण

		वापस;
	पूर्ण

	अगर (!dtg->ctxld_kick_irq_en)
		वापस;

	disable_irq_nosync(dtg->ctxld_kick_irq);
	dtg->ctxld_kick_irq_en = false;

	dcss_update(mask, LINE0_IRQ, dtg->base_reg + DCSS_DTG_INT_MASK);
पूर्ण

व्योम dcss_dtg_vblank_irq_clear(काष्ठा dcss_dtg *dtg)
अणु
	dcss_update(LINE1_IRQ, LINE1_IRQ, dtg->base_reg + DCSS_DTG_INT_CONTROL);
पूर्ण

bool dcss_dtg_vblank_irq_valid(काष्ठा dcss_dtg *dtg)
अणु
	वापस !!(dcss_पढ़ोl(dtg->base_reg + DCSS_DTG_INT_STATUS) & LINE1_IRQ);
पूर्ण

