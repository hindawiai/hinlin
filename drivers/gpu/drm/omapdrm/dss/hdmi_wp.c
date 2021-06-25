<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HDMI wrapper
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - https://www.ti.com/
 */

#घोषणा DSS_SUBSYS_NAME "HDMIWP"

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>

#समावेश "omapdss.h"
#समावेश "dss.h"
#समावेश "hdmi.h"

व्योम hdmi_wp_dump(काष्ठा hdmi_wp_data *wp, काष्ठा seq_file *s)
अणु
#घोषणा DUMPREG(r) seq_म_लिखो(s, "%-35s %08x\n", #r, hdmi_पढ़ो_reg(wp->base, r))

	DUMPREG(HDMI_WP_REVISION);
	DUMPREG(HDMI_WP_SYSCONFIG);
	DUMPREG(HDMI_WP_IRQSTATUS_RAW);
	DUMPREG(HDMI_WP_IRQSTATUS);
	DUMPREG(HDMI_WP_IRQENABLE_SET);
	DUMPREG(HDMI_WP_IRQENABLE_CLR);
	DUMPREG(HDMI_WP_IRQWAKEEN);
	DUMPREG(HDMI_WP_PWR_CTRL);
	DUMPREG(HDMI_WP_DEBOUNCE);
	DUMPREG(HDMI_WP_VIDEO_CFG);
	DUMPREG(HDMI_WP_VIDEO_SIZE);
	DUMPREG(HDMI_WP_VIDEO_TIMING_H);
	DUMPREG(HDMI_WP_VIDEO_TIMING_V);
	DUMPREG(HDMI_WP_CLK);
	DUMPREG(HDMI_WP_AUDIO_CFG);
	DUMPREG(HDMI_WP_AUDIO_CFG2);
	DUMPREG(HDMI_WP_AUDIO_CTRL);
	DUMPREG(HDMI_WP_AUDIO_DATA);
पूर्ण

u32 hdmi_wp_get_irqstatus(काष्ठा hdmi_wp_data *wp)
अणु
	वापस hdmi_पढ़ो_reg(wp->base, HDMI_WP_IRQSTATUS);
पूर्ण

व्योम hdmi_wp_set_irqstatus(काष्ठा hdmi_wp_data *wp, u32 irqstatus)
अणु
	hdmi_ग_लिखो_reg(wp->base, HDMI_WP_IRQSTATUS, irqstatus);
	/* flush posted ग_लिखो */
	hdmi_पढ़ो_reg(wp->base, HDMI_WP_IRQSTATUS);
पूर्ण

व्योम hdmi_wp_set_irqenable(काष्ठा hdmi_wp_data *wp, u32 mask)
अणु
	hdmi_ग_लिखो_reg(wp->base, HDMI_WP_IRQENABLE_SET, mask);
पूर्ण

व्योम hdmi_wp_clear_irqenable(काष्ठा hdmi_wp_data *wp, u32 mask)
अणु
	hdmi_ग_लिखो_reg(wp->base, HDMI_WP_IRQENABLE_CLR, mask);
पूर्ण

/* PHY_PWR_CMD */
पूर्णांक hdmi_wp_set_phy_pwr(काष्ठा hdmi_wp_data *wp, क्रमागत hdmi_phy_pwr val)
अणु
	/* Return अगर alपढ़ोy the state */
	अगर (REG_GET(wp->base, HDMI_WP_PWR_CTRL, 5, 4) == val)
		वापस 0;

	/* Command क्रम घातer control of HDMI PHY */
	REG_FLD_MOD(wp->base, HDMI_WP_PWR_CTRL, val, 7, 6);

	/* Status of the घातer control of HDMI PHY */
	अगर (hdmi_रुको_क्रम_bit_change(wp->base, HDMI_WP_PWR_CTRL, 5, 4, val)
			!= val) अणु
		DSSERR("Failed to set PHY power mode to %d\n", val);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/* PLL_PWR_CMD */
पूर्णांक hdmi_wp_set_pll_pwr(काष्ठा hdmi_wp_data *wp, क्रमागत hdmi_pll_pwr val)
अणु
	/* Command क्रम घातer control of HDMI PLL */
	REG_FLD_MOD(wp->base, HDMI_WP_PWR_CTRL, val, 3, 2);

	/* रुको till PHY_PWR_STATUS is set */
	अगर (hdmi_रुको_क्रम_bit_change(wp->base, HDMI_WP_PWR_CTRL, 1, 0, val)
			!= val) अणु
		DSSERR("Failed to set PLL_PWR_STATUS\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hdmi_wp_video_start(काष्ठा hdmi_wp_data *wp)
अणु
	REG_FLD_MOD(wp->base, HDMI_WP_VIDEO_CFG, true, 31, 31);

	वापस 0;
पूर्ण

व्योम hdmi_wp_video_stop(काष्ठा hdmi_wp_data *wp)
अणु
	पूर्णांक i;

	hdmi_ग_लिखो_reg(wp->base, HDMI_WP_IRQSTATUS, HDMI_IRQ_VIDEO_FRAME_DONE);

	REG_FLD_MOD(wp->base, HDMI_WP_VIDEO_CFG, false, 31, 31);

	क्रम (i = 0; i < 50; ++i) अणु
		u32 v;

		msleep(20);

		v = hdmi_पढ़ो_reg(wp->base, HDMI_WP_IRQSTATUS_RAW);
		अगर (v & HDMI_IRQ_VIDEO_FRAME_DONE)
			वापस;
	पूर्ण

	DSSERR("no HDMI FRAMEDONE when disabling output\n");
पूर्ण

व्योम hdmi_wp_video_config_क्रमmat(काष्ठा hdmi_wp_data *wp,
		स्थिर काष्ठा hdmi_video_क्रमmat *video_fmt)
अणु
	u32 l = 0;

	REG_FLD_MOD(wp->base, HDMI_WP_VIDEO_CFG, video_fmt->packing_mode,
		10, 8);

	l |= FLD_VAL(video_fmt->y_res, 31, 16);
	l |= FLD_VAL(video_fmt->x_res, 15, 0);
	hdmi_ग_लिखो_reg(wp->base, HDMI_WP_VIDEO_SIZE, l);
पूर्ण

व्योम hdmi_wp_video_config_पूर्णांकerface(काष्ठा hdmi_wp_data *wp,
				    स्थिर काष्ठा videomode *vm)
अणु
	u32 r;
	bool vsync_inv, hsync_inv;
	DSSDBG("Enter hdmi_wp_video_config_interface\n");

	vsync_inv = !!(vm->flags & DISPLAY_FLAGS_VSYNC_LOW);
	hsync_inv = !!(vm->flags & DISPLAY_FLAGS_HSYNC_LOW);

	r = hdmi_पढ़ो_reg(wp->base, HDMI_WP_VIDEO_CFG);
	r = FLD_MOD(r, 1, 7, 7);	/* VSYNC_POL to dispc active high */
	r = FLD_MOD(r, 1, 6, 6);	/* HSYNC_POL to dispc active high */
	r = FLD_MOD(r, vsync_inv, 5, 5);	/* CORE_VSYNC_INV */
	r = FLD_MOD(r, hsync_inv, 4, 4);	/* CORE_HSYNC_INV */
	r = FLD_MOD(r, !!(vm->flags & DISPLAY_FLAGS_INTERLACED), 3, 3);
	r = FLD_MOD(r, 1, 1, 0); /* HDMI_TIMING_MASTER_24BIT */
	hdmi_ग_लिखो_reg(wp->base, HDMI_WP_VIDEO_CFG, r);
पूर्ण

व्योम hdmi_wp_video_config_timing(काष्ठा hdmi_wp_data *wp,
				 स्थिर काष्ठा videomode *vm)
अणु
	u32 timing_h = 0;
	u32 timing_v = 0;
	अचिन्हित पूर्णांक hsync_len_offset = 1;

	DSSDBG("Enter hdmi_wp_video_config_timing\n");

	/*
	 * On OMAP4 and OMAP5 ES1 the HSW field is programmed as is. On OMAP5
	 * ES2+ (including DRA7/AM5 SoCs) HSW field is programmed to hsync_len-1.
	 * However, we करोn't support OMAP5 ES1 at all, so we can just check क्रम
	 * OMAP4 here.
	 */
	अगर (wp->version == 4)
		hsync_len_offset = 0;

	timing_h |= FLD_VAL(vm->hback_porch, 31, 20);
	timing_h |= FLD_VAL(vm->hfront_porch, 19, 8);
	timing_h |= FLD_VAL(vm->hsync_len - hsync_len_offset, 7, 0);
	hdmi_ग_लिखो_reg(wp->base, HDMI_WP_VIDEO_TIMING_H, timing_h);

	timing_v |= FLD_VAL(vm->vback_porch, 31, 20);
	timing_v |= FLD_VAL(vm->vfront_porch, 19, 8);
	timing_v |= FLD_VAL(vm->vsync_len, 7, 0);
	hdmi_ग_लिखो_reg(wp->base, HDMI_WP_VIDEO_TIMING_V, timing_v);
पूर्ण

व्योम hdmi_wp_init_vid_fmt_timings(काष्ठा hdmi_video_क्रमmat *video_fmt,
		काष्ठा videomode *vm, स्थिर काष्ठा hdmi_config *param)
अणु
	DSSDBG("Enter hdmi_wp_video_init_format\n");

	video_fmt->packing_mode = HDMI_PACK_10b_RGB_YUV444;
	video_fmt->y_res = param->vm.vactive;
	video_fmt->x_res = param->vm.hactive;

	vm->hback_porch = param->vm.hback_porch;
	vm->hfront_porch = param->vm.hfront_porch;
	vm->hsync_len = param->vm.hsync_len;
	vm->vback_porch = param->vm.vback_porch;
	vm->vfront_porch = param->vm.vfront_porch;
	vm->vsync_len = param->vm.vsync_len;

	vm->flags = param->vm.flags;

	अगर (param->vm.flags & DISPLAY_FLAGS_INTERLACED) अणु
		video_fmt->y_res /= 2;
		vm->vback_porch /= 2;
		vm->vfront_porch /= 2;
		vm->vsync_len /= 2;
	पूर्ण

	अगर (param->vm.flags & DISPLAY_FLAGS_DOUBLECLK) अणु
		video_fmt->x_res *= 2;
		vm->hfront_porch *= 2;
		vm->hsync_len *= 2;
		vm->hback_porch *= 2;
	पूर्ण
पूर्ण

व्योम hdmi_wp_audio_config_क्रमmat(काष्ठा hdmi_wp_data *wp,
		काष्ठा hdmi_audio_क्रमmat *aud_fmt)
अणु
	u32 r;

	DSSDBG("Enter hdmi_wp_audio_config_format\n");

	r = hdmi_पढ़ो_reg(wp->base, HDMI_WP_AUDIO_CFG);
	अगर (wp->version == 4) अणु
		r = FLD_MOD(r, aud_fmt->stereo_channels, 26, 24);
		r = FLD_MOD(r, aud_fmt->active_chnnls_msk, 23, 16);
	पूर्ण
	r = FLD_MOD(r, aud_fmt->en_sig_blk_strt_end, 5, 5);
	r = FLD_MOD(r, aud_fmt->type, 4, 4);
	r = FLD_MOD(r, aud_fmt->justअगरication, 3, 3);
	r = FLD_MOD(r, aud_fmt->sample_order, 2, 2);
	r = FLD_MOD(r, aud_fmt->samples_per_word, 1, 1);
	r = FLD_MOD(r, aud_fmt->sample_size, 0, 0);
	hdmi_ग_लिखो_reg(wp->base, HDMI_WP_AUDIO_CFG, r);
पूर्ण

व्योम hdmi_wp_audio_config_dma(काष्ठा hdmi_wp_data *wp,
		काष्ठा hdmi_audio_dma *aud_dma)
अणु
	u32 r;

	DSSDBG("Enter hdmi_wp_audio_config_dma\n");

	r = hdmi_पढ़ो_reg(wp->base, HDMI_WP_AUDIO_CFG2);
	r = FLD_MOD(r, aud_dma->transfer_size, 15, 8);
	r = FLD_MOD(r, aud_dma->block_size, 7, 0);
	hdmi_ग_लिखो_reg(wp->base, HDMI_WP_AUDIO_CFG2, r);

	r = hdmi_पढ़ो_reg(wp->base, HDMI_WP_AUDIO_CTRL);
	r = FLD_MOD(r, aud_dma->mode, 9, 9);
	r = FLD_MOD(r, aud_dma->fअगरo_threshold, 8, 0);
	hdmi_ग_लिखो_reg(wp->base, HDMI_WP_AUDIO_CTRL, r);
पूर्ण

पूर्णांक hdmi_wp_audio_enable(काष्ठा hdmi_wp_data *wp, bool enable)
अणु
	REG_FLD_MOD(wp->base, HDMI_WP_AUDIO_CTRL, enable, 31, 31);

	वापस 0;
पूर्ण

पूर्णांक hdmi_wp_audio_core_req_enable(काष्ठा hdmi_wp_data *wp, bool enable)
अणु
	REG_FLD_MOD(wp->base, HDMI_WP_AUDIO_CTRL, enable, 30, 30);

	वापस 0;
पूर्ण

पूर्णांक hdmi_wp_init(काष्ठा platक्रमm_device *pdev, काष्ठा hdmi_wp_data *wp,
		 अचिन्हित पूर्णांक version)
अणु
	काष्ठा resource *res;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "wp");
	wp->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(wp->base))
		वापस PTR_ERR(wp->base);

	wp->phys_base = res->start;
	wp->version = version;

	वापस 0;
पूर्ण

phys_addr_t hdmi_wp_get_audio_dma_addr(काष्ठा hdmi_wp_data *wp)
अणु
	वापस wp->phys_base + HDMI_WP_AUDIO_DATA;
पूर्ण
