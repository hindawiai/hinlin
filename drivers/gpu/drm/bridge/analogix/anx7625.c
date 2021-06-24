<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2020, Analogix Semiconductor. All rights reserved.
 *
 */
#समावेश <linux/gcd.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश <video/display_timing.h>

#समावेश "anx7625.h"

/*
 * There is a sync issue जबतक access I2C रेजिस्टर between AP(CPU) and
 * पूर्णांकernal firmware(OCM), to aव्योम the race condition, AP should access
 * the reserved slave address beक्रमe slave address occurs changes.
 */
अटल पूर्णांक i2c_access_workaround(काष्ठा anx7625_data *ctx,
				 काष्ठा i2c_client *client)
अणु
	u8 offset;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret;

	अगर (client == ctx->last_client)
		वापस 0;

	ctx->last_client = client;

	अगर (client == ctx->i2c.tcpc_client)
		offset = RSVD_00_ADDR;
	अन्यथा अगर (client == ctx->i2c.tx_p0_client)
		offset = RSVD_D1_ADDR;
	अन्यथा अगर (client == ctx->i2c.tx_p1_client)
		offset = RSVD_60_ADDR;
	अन्यथा अगर (client == ctx->i2c.rx_p0_client)
		offset = RSVD_39_ADDR;
	अन्यथा अगर (client == ctx->i2c.rx_p1_client)
		offset = RSVD_7F_ADDR;
	अन्यथा
		offset = RSVD_00_ADDR;

	ret = i2c_smbus_ग_लिखो_byte_data(client, offset, 0x00);
	अगर (ret < 0)
		DRM_DEV_ERROR(dev,
			      "fail to access i2c id=%x\n:%x",
			      client->addr, offset);

	वापस ret;
पूर्ण

अटल पूर्णांक anx7625_reg_पढ़ो(काष्ठा anx7625_data *ctx,
			    काष्ठा i2c_client *client, u8 reg_addr)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &client->dev;

	i2c_access_workaround(ctx, client);

	ret = i2c_smbus_पढ़ो_byte_data(client, reg_addr);
	अगर (ret < 0)
		DRM_DEV_ERROR(dev, "read i2c fail id=%x:%x\n",
			      client->addr, reg_addr);

	वापस ret;
पूर्ण

अटल पूर्णांक anx7625_reg_block_पढ़ो(काष्ठा anx7625_data *ctx,
				  काष्ठा i2c_client *client,
				  u8 reg_addr, u8 len, u8 *buf)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &client->dev;

	i2c_access_workaround(ctx, client);

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, reg_addr, len, buf);
	अगर (ret < 0)
		DRM_DEV_ERROR(dev, "read i2c block fail id=%x:%x\n",
			      client->addr, reg_addr);

	वापस ret;
पूर्ण

अटल पूर्णांक anx7625_reg_ग_लिखो(काष्ठा anx7625_data *ctx,
			     काष्ठा i2c_client *client,
			     u8 reg_addr, u8 reg_val)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &client->dev;

	i2c_access_workaround(ctx, client);

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg_addr, reg_val);

	अगर (ret < 0)
		DRM_DEV_ERROR(dev, "fail to write i2c id=%x\n:%x",
			      client->addr, reg_addr);

	वापस ret;
पूर्ण

अटल पूर्णांक anx7625_ग_लिखो_or(काष्ठा anx7625_data *ctx,
			    काष्ठा i2c_client *client,
			    u8 offset, u8 mask)
अणु
	पूर्णांक val;

	val = anx7625_reg_पढ़ो(ctx, client, offset);
	अगर (val < 0)
		वापस val;

	वापस anx7625_reg_ग_लिखो(ctx, client, offset, (val | (mask)));
पूर्ण

अटल पूर्णांक anx7625_ग_लिखो_and(काष्ठा anx7625_data *ctx,
			     काष्ठा i2c_client *client,
			     u8 offset, u8 mask)
अणु
	पूर्णांक val;

	val = anx7625_reg_पढ़ो(ctx, client, offset);
	अगर (val < 0)
		वापस val;

	वापस anx7625_reg_ग_लिखो(ctx, client, offset, (val & (mask)));
पूर्ण

अटल पूर्णांक anx7625_ग_लिखो_and_or(काष्ठा anx7625_data *ctx,
				काष्ठा i2c_client *client,
				u8 offset, u8 and_mask, u8 or_mask)
अणु
	पूर्णांक val;

	val = anx7625_reg_पढ़ो(ctx, client, offset);
	अगर (val < 0)
		वापस val;

	वापस anx7625_reg_ग_लिखो(ctx, client,
				 offset, (val & and_mask) | (or_mask));
पूर्ण

अटल पूर्णांक anx7625_पढ़ो_ctrl_status_p0(काष्ठा anx7625_data *ctx)
अणु
	वापस anx7625_reg_पढ़ो(ctx, ctx->i2c.rx_p0_client, AP_AUX_CTRL_STATUS);
पूर्ण

अटल पूर्णांक रुको_aux_op_finish(काष्ठा anx7625_data *ctx)
अणु
	काष्ठा device *dev = &ctx->client->dev;
	पूर्णांक val;
	पूर्णांक ret;

	ret = पढ़ोx_poll_समयout(anx7625_पढ़ो_ctrl_status_p0,
				 ctx, val,
				 (!(val & AP_AUX_CTRL_OP_EN) || (val < 0)),
				 2000,
				 2000 * 150);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "aux operation fail!\n");
		वापस -EIO;
	पूर्ण

	val = anx7625_reg_पढ़ो(ctx, ctx->i2c.rx_p0_client,
			       AP_AUX_CTRL_STATUS);
	अगर (val < 0 || (val & 0x0F)) अणु
		DRM_DEV_ERROR(dev, "aux status %02x\n", val);
		val = -EIO;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक anx7625_video_mute_control(काष्ठा anx7625_data *ctx,
				      u8 status)
अणु
	पूर्णांक ret;

	अगर (status) अणु
		/* Set mute on flag */
		ret = anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p0_client,
				       AP_AV_STATUS, AP_MIPI_MUTE);
		/* Clear mipi RX en */
		ret |= anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p0_client,
					 AP_AV_STATUS, (u8)~AP_MIPI_RX_EN);
	पूर्ण अन्यथा अणु
		/* Mute off flag */
		ret = anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p0_client,
					AP_AV_STATUS, (u8)~AP_MIPI_MUTE);
		/* Set MIPI RX EN */
		ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p0_client,
					AP_AV_STATUS, AP_MIPI_RX_EN);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक anx7625_config_audio_input(काष्ठा anx7625_data *ctx)
अणु
	काष्ठा device *dev = &ctx->client->dev;
	पूर्णांक ret;

	/* Channel num */
	ret = anx7625_reg_ग_लिखो(ctx, ctx->i2c.tx_p2_client,
				AUDIO_CHANNEL_STATUS_6, I2S_CH_2 << 5);

	/* FS */
	ret |= anx7625_ग_लिखो_and_or(ctx, ctx->i2c.tx_p2_client,
				    AUDIO_CHANNEL_STATUS_4,
				    0xf0, AUDIO_FS_48K);
	/* Word length */
	ret |= anx7625_ग_लिखो_and_or(ctx, ctx->i2c.tx_p2_client,
				    AUDIO_CHANNEL_STATUS_5,
				    0xf0, AUDIO_W_LEN_24_24MAX);
	/* I2S */
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.tx_p2_client,
				AUDIO_CHANNEL_STATUS_6, I2S_SLAVE_MODE);
	ret |= anx7625_ग_लिखो_and(ctx, ctx->i2c.tx_p2_client,
				 AUDIO_CONTROL_REGISTER, ~TDM_TIMING_MODE);
	/* Audio change flag */
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p0_client,
				AP_AV_STATUS, AP_AUDIO_CHG);

	अगर (ret < 0)
		DRM_DEV_ERROR(dev, "fail to config audio.\n");

	वापस ret;
पूर्ण

/* Reduction of fraction a/b */
अटल व्योम anx7625_reduction_of_a_fraction(अचिन्हित दीर्घ *a, अचिन्हित दीर्घ *b)
अणु
	अचिन्हित दीर्घ gcd_num;
	अचिन्हित दीर्घ पंचांगp_a, पंचांगp_b;
	u32 i = 1;

	gcd_num = gcd(*a, *b);
	*a /= gcd_num;
	*b /= gcd_num;

	पंचांगp_a = *a;
	पंचांगp_b = *b;

	जबतक ((*a > MAX_UNSIGNED_24BIT) || (*b > MAX_UNSIGNED_24BIT)) अणु
		i++;
		*a = पंचांगp_a / i;
		*b = पंचांगp_b / i;
	पूर्ण

	/*
	 * In the end, make a, b larger to have higher ODFC PLL
	 * output frequency accuracy
	 */
	जबतक ((*a < MAX_UNSIGNED_24BIT) && (*b < MAX_UNSIGNED_24BIT)) अणु
		*a <<= 1;
		*b <<= 1;
	पूर्ण

	*a >>= 1;
	*b >>= 1;
पूर्ण

अटल पूर्णांक anx7625_calculate_m_n(u32 pixelघड़ी,
				 अचिन्हित दीर्घ *m,
				 अचिन्हित दीर्घ *n,
				 u8 *post_भागider)
अणु
	अगर (pixelघड़ी > PLL_OUT_FREQ_ABS_MAX / POST_DIVIDER_MIN) अणु
		/* Pixel घड़ी frequency is too high */
		DRM_ERROR("pixelclock too high, act(%d), maximum(%lu)\n",
			  pixelघड़ी,
			  PLL_OUT_FREQ_ABS_MAX / POST_DIVIDER_MIN);
		वापस -EINVAL;
	पूर्ण

	अगर (pixelघड़ी < PLL_OUT_FREQ_ABS_MIN / POST_DIVIDER_MAX) अणु
		/* Pixel घड़ी frequency is too low */
		DRM_ERROR("pixelclock too low, act(%d), maximum(%lu)\n",
			  pixelघड़ी,
			  PLL_OUT_FREQ_ABS_MIN / POST_DIVIDER_MAX);
		वापस -EINVAL;
	पूर्ण

	क्रम (*post_भागider = 1;
		pixelघड़ी < (PLL_OUT_FREQ_MIN / (*post_भागider));)
		*post_भागider += 1;

	अगर (*post_भागider > POST_DIVIDER_MAX) अणु
		क्रम (*post_भागider = 1;
			(pixelघड़ी <
			 (PLL_OUT_FREQ_ABS_MIN / (*post_भागider)));)
			*post_भागider += 1;

		अगर (*post_भागider > POST_DIVIDER_MAX) अणु
			DRM_ERROR("cannot find property post_divider(%d)\n",
				  *post_भागider);
			वापस -गलत_तर्क;
		पूर्ण
	पूर्ण

	/* Patch to improve the accuracy */
	अगर (*post_भागider == 7) अणु
		/* 27,000,000 is not भागisible by 7 */
		*post_भागider = 8;
	पूर्ण अन्यथा अगर (*post_भागider == 11) अणु
		/* 27,000,000 is not भागisible by 11 */
		*post_भागider = 12;
	पूर्ण अन्यथा अगर ((*post_भागider == 13) || (*post_भागider == 14)) अणु
		/* 27,000,000 is not भागisible by 13 or 14 */
		*post_भागider = 15;
	पूर्ण

	अगर (pixelघड़ी * (*post_भागider) > PLL_OUT_FREQ_ABS_MAX) अणु
		DRM_ERROR("act clock(%u) large than maximum(%lu)\n",
			  pixelघड़ी * (*post_भागider),
			  PLL_OUT_FREQ_ABS_MAX);
		वापस -गलत_तर्क;
	पूर्ण

	*m = pixelघड़ी;
	*n = XTAL_FRQ / (*post_भागider);

	anx7625_reduction_of_a_fraction(m, n);

	वापस 0;
पूर्ण

अटल पूर्णांक anx7625_odfc_config(काष्ठा anx7625_data *ctx,
			       u8 post_भागider)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &ctx->client->dev;

	/* Config input reference घड़ी frequency 27MHz/19.2MHz */
	ret = anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p1_client, MIPI_DIGITAL_PLL_16,
				~(REF_CLK_27000KHZ << MIPI_FREF_D_IND));
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p1_client, MIPI_DIGITAL_PLL_16,
				(REF_CLK_27000KHZ << MIPI_FREF_D_IND));
	/* Post भागider */
	ret |= anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p1_client,
				 MIPI_DIGITAL_PLL_8, 0x0f);
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p1_client, MIPI_DIGITAL_PLL_8,
				post_भागider << 4);

	/* Add patch क्रम MIS2-125 (5pcs ANX7625 fail ATE MBIST test) */
	ret |= anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p1_client, MIPI_DIGITAL_PLL_7,
				 ~MIPI_PLL_VCO_TUNE_REG_VAL);

	/* Reset ODFC PLL */
	ret |= anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p1_client, MIPI_DIGITAL_PLL_7,
				 ~MIPI_PLL_RESET_N);
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p1_client, MIPI_DIGITAL_PLL_7,
				MIPI_PLL_RESET_N);

	अगर (ret < 0)
		DRM_DEV_ERROR(dev, "IO error.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक anx7625_dsi_video_timing_config(काष्ठा anx7625_data *ctx)
अणु
	काष्ठा device *dev = &ctx->client->dev;
	अचिन्हित दीर्घ m, n;
	u16 htotal;
	पूर्णांक ret;
	u8 post_भागider = 0;

	ret = anx7625_calculate_m_n(ctx->dt.pixelघड़ी.min * 1000,
				    &m, &n, &post_भागider);

	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "cannot get property m n value.\n");
		वापस ret;
	पूर्ण

	DRM_DEV_DEBUG_DRIVER(dev, "compute M(%lu), N(%lu), divider(%d).\n",
			     m, n, post_भागider);

	/* Configure pixel घड़ी */
	ret = anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client, PIXEL_CLOCK_L,
				(ctx->dt.pixelघड़ी.min / 1000) & 0xFF);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client, PIXEL_CLOCK_H,
				 (ctx->dt.pixelघड़ी.min / 1000) >> 8);
	/* Lane count */
	ret |= anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p1_client,
			MIPI_LANE_CTRL_0, 0xfc);
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p1_client,
				MIPI_LANE_CTRL_0, 3);

	/* Htotal */
	htotal = ctx->dt.hactive.min + ctx->dt.hfront_porch.min +
		ctx->dt.hback_porch.min + ctx->dt.hsync_len.min;
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			HORIZONTAL_TOTAL_PIXELS_L, htotal & 0xFF);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			HORIZONTAL_TOTAL_PIXELS_H, htotal >> 8);
	/* Hactive */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			HORIZONTAL_ACTIVE_PIXELS_L, ctx->dt.hactive.min & 0xFF);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			HORIZONTAL_ACTIVE_PIXELS_H, ctx->dt.hactive.min >> 8);
	/* HFP */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			HORIZONTAL_FRONT_PORCH_L, ctx->dt.hfront_porch.min);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			HORIZONTAL_FRONT_PORCH_H,
			ctx->dt.hfront_porch.min >> 8);
	/* HWS */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			HORIZONTAL_SYNC_WIDTH_L, ctx->dt.hsync_len.min);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			HORIZONTAL_SYNC_WIDTH_H, ctx->dt.hsync_len.min >> 8);
	/* HBP */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			HORIZONTAL_BACK_PORCH_L, ctx->dt.hback_porch.min);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			HORIZONTAL_BACK_PORCH_H, ctx->dt.hback_porch.min >> 8);
	/* Vactive */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client, ACTIVE_LINES_L,
			ctx->dt.vactive.min);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client, ACTIVE_LINES_H,
			ctx->dt.vactive.min >> 8);
	/* VFP */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			VERTICAL_FRONT_PORCH, ctx->dt.vfront_porch.min);
	/* VWS */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			VERTICAL_SYNC_WIDTH, ctx->dt.vsync_len.min);
	/* VBP */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p2_client,
			VERTICAL_BACK_PORCH, ctx->dt.vback_porch.min);
	/* M value */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client,
			MIPI_PLL_M_NUM_23_16, (m >> 16) & 0xff);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client,
			MIPI_PLL_M_NUM_15_8, (m >> 8) & 0xff);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client,
			MIPI_PLL_M_NUM_7_0, (m & 0xff));
	/* N value */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client,
			MIPI_PLL_N_NUM_23_16, (n >> 16) & 0xff);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client,
			MIPI_PLL_N_NUM_15_8, (n >> 8) & 0xff);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client, MIPI_PLL_N_NUM_7_0,
			(n & 0xff));
	/* Dअगरf */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client,
			MIPI_DIGITAL_ADJ_1, 0x3D);

	ret |= anx7625_odfc_config(ctx, post_भागider - 1);

	अगर (ret < 0)
		DRM_DEV_ERROR(dev, "mipi dsi setup IO error.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक anx7625_swap_dsi_lane3(काष्ठा anx7625_data *ctx)
अणु
	पूर्णांक val;
	काष्ठा device *dev = &ctx->client->dev;

	/* Swap MIPI-DSI data lane 3 P and N */
	val = anx7625_reg_पढ़ो(ctx, ctx->i2c.rx_p1_client, MIPI_SWAP);
	अगर (val < 0) अणु
		DRM_DEV_ERROR(dev, "IO error : access MIPI_SWAP.\n");
		वापस -EIO;
	पूर्ण

	val |= (1 << MIPI_SWAP_CH3);
	वापस anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client, MIPI_SWAP, val);
पूर्ण

अटल पूर्णांक anx7625_api_dsi_config(काष्ठा anx7625_data *ctx)

अणु
	पूर्णांक val, ret;
	काष्ठा device *dev = &ctx->client->dev;

	/* Swap MIPI-DSI data lane 3 P and N */
	ret = anx7625_swap_dsi_lane3(ctx);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "IO error : swap dsi lane 3 fail.\n");
		वापस ret;
	पूर्ण

	/* DSI घड़ी settings */
	val = (0 << MIPI_HS_PWD_CLK)		|
		(0 << MIPI_HS_RT_CLK)		|
		(0 << MIPI_PD_CLK)		|
		(1 << MIPI_CLK_RT_MANUAL_PD_EN)	|
		(1 << MIPI_CLK_HS_MANUAL_PD_EN)	|
		(0 << MIPI_CLK_DET_DET_BYPASS)	|
		(0 << MIPI_CLK_MISS_CTRL)	|
		(0 << MIPI_PD_LPTX_CH_MANUAL_PD_EN);
	ret = anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client,
				MIPI_PHY_CONTROL_3, val);

	/*
	 * Decreased HS prepare timing delay from 160ns to 80ns work with
	 *     a) Dragon board 810 series (Qualcomm AP)
	 *     b) Moving Pixel DSI source (PG3A pattern generator +
	 *	P332 D-PHY Probe) शेष D-PHY timing
	 *	5ns/step
	 */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client,
				 MIPI_TIME_HS_PRPR, 0x10);

	/* Enable DSI mode*/
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p1_client, MIPI_DIGITAL_PLL_18,
				SELECT_DSI << MIPI_DPI_SELECT);

	ret |= anx7625_dsi_video_timing_config(ctx);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "dsi video timing config fail\n");
		वापस ret;
	पूर्ण

	/* Toggle m, n पढ़ोy */
	ret = anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p1_client, MIPI_DIGITAL_PLL_6,
				~(MIPI_M_NUM_READY | MIPI_N_NUM_READY));
	usleep_range(1000, 1100);
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p1_client, MIPI_DIGITAL_PLL_6,
				MIPI_M_NUM_READY | MIPI_N_NUM_READY);

	/* Configure पूर्णांकeger stable रेजिस्टर */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client,
				 MIPI_VIDEO_STABLE_CNT, 0x02);
	/* Power on MIPI RX */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client,
				 MIPI_LANE_CTRL_10, 0x00);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p1_client,
				 MIPI_LANE_CTRL_10, 0x80);

	अगर (ret < 0)
		DRM_DEV_ERROR(dev, "IO error : mipi dsi enable init fail.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक anx7625_dsi_config(काष्ठा anx7625_data *ctx)
अणु
	काष्ठा device *dev = &ctx->client->dev;
	पूर्णांक ret;

	DRM_DEV_DEBUG_DRIVER(dev, "config dsi.\n");

	/* DSC disable */
	ret = anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p0_client,
				R_DSC_CTRL_0, ~DSC_EN);

	ret |= anx7625_api_dsi_config(ctx);

	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "IO error : api dsi config error.\n");
		वापस ret;
	पूर्ण

	/* Set MIPI RX EN */
	ret = anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p0_client,
			       AP_AV_STATUS, AP_MIPI_RX_EN);
	/* Clear mute flag */
	ret |= anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p0_client,
				 AP_AV_STATUS, (u8)~AP_MIPI_MUTE);
	अगर (ret < 0)
		DRM_DEV_ERROR(dev, "IO error : enable mipi rx fail.\n");
	अन्यथा
		DRM_DEV_DEBUG_DRIVER(dev, "success to config DSI\n");

	वापस ret;
पूर्ण

अटल व्योम anx7625_dp_start(काष्ठा anx7625_data *ctx)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &ctx->client->dev;

	अगर (!ctx->display_timing_valid) अणु
		DRM_DEV_ERROR(dev, "mipi not set display timing yet.\n");
		वापस;
	पूर्ण

	anx7625_config_audio_input(ctx);

	ret = anx7625_dsi_config(ctx);

	अगर (ret < 0)
		DRM_DEV_ERROR(dev, "MIPI phy setup error.\n");
पूर्ण

अटल व्योम anx7625_dp_stop(काष्ठा anx7625_data *ctx)
अणु
	काष्ठा device *dev = &ctx->client->dev;
	पूर्णांक ret;

	DRM_DEV_DEBUG_DRIVER(dev, "stop dp output\n");

	/*
	 * Video disable: 0x72:08 bit 7 = 0;
	 * Audio disable: 0x70:87 bit 0 = 0;
	 */
	ret = anx7625_ग_लिखो_and(ctx, ctx->i2c.tx_p0_client, 0x87, 0xfe);
	ret |= anx7625_ग_लिखो_and(ctx, ctx->i2c.tx_p2_client, 0x08, 0x7f);

	ret |= anx7625_video_mute_control(ctx, 1);
	अगर (ret < 0)
		DRM_DEV_ERROR(dev, "IO error : mute video fail\n");
पूर्ण

अटल पूर्णांक sp_tx_rst_aux(काष्ठा anx7625_data *ctx)
अणु
	पूर्णांक ret;

	ret = anx7625_ग_लिखो_or(ctx, ctx->i2c.tx_p2_client, RST_CTRL2,
			       AUX_RST);
	ret |= anx7625_ग_लिखो_and(ctx, ctx->i2c.tx_p2_client, RST_CTRL2,
				 ~AUX_RST);
	वापस ret;
पूर्ण

अटल पूर्णांक sp_tx_aux_wr(काष्ठा anx7625_data *ctx, u8 offset)
अणु
	पूर्णांक ret;

	ret = anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				AP_AUX_BUFF_START, offset);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				 AP_AUX_COMMAND, 0x04);
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p0_client,
				AP_AUX_CTRL_STATUS, AP_AUX_CTRL_OP_EN);
	वापस (ret | रुको_aux_op_finish(ctx));
पूर्ण

अटल पूर्णांक sp_tx_aux_rd(काष्ठा anx7625_data *ctx, u8 len_cmd)
अणु
	पूर्णांक ret;

	ret = anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				AP_AUX_COMMAND, len_cmd);
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p0_client,
				AP_AUX_CTRL_STATUS, AP_AUX_CTRL_OP_EN);
	वापस (ret | रुको_aux_op_finish(ctx));
पूर्ण

अटल पूर्णांक sp_tx_get_edid_block(काष्ठा anx7625_data *ctx)
अणु
	पूर्णांक c = 0;
	काष्ठा device *dev = &ctx->client->dev;

	sp_tx_aux_wr(ctx, 0x7e);
	sp_tx_aux_rd(ctx, 0x01);
	c = anx7625_reg_पढ़ो(ctx, ctx->i2c.rx_p0_client, AP_AUX_BUFF_START);
	अगर (c < 0) अणु
		DRM_DEV_ERROR(dev, "IO error : access AUX BUFF.\n");
		वापस -EIO;
	पूर्ण

	DRM_DEV_DEBUG_DRIVER(dev, " EDID Block = %d\n", c + 1);

	अगर (c > MAX_EDID_BLOCK)
		c = 1;

	वापस c;
पूर्ण

अटल पूर्णांक edid_पढ़ो(काष्ठा anx7625_data *ctx,
		     u8 offset, u8 *pblock_buf)
अणु
	पूर्णांक ret, cnt;
	काष्ठा device *dev = &ctx->client->dev;

	क्रम (cnt = 0; cnt <= EDID_TRY_CNT; cnt++) अणु
		sp_tx_aux_wr(ctx, offset);
		/* Set I2C पढ़ो com 0x01 mot = 0 and पढ़ो 16 bytes */
		ret = sp_tx_aux_rd(ctx, 0xf1);

		अगर (ret) अणु
			sp_tx_rst_aux(ctx);
			DRM_DEV_DEBUG_DRIVER(dev, "edid read fail, reset!\n");
		पूर्ण अन्यथा अणु
			ret = anx7625_reg_block_पढ़ो(ctx, ctx->i2c.rx_p0_client,
						     AP_AUX_BUFF_START,
						     MAX_DPCD_BUFFER_SIZE,
						     pblock_buf);
			अगर (ret > 0)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (cnt > EDID_TRY_CNT)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक segments_edid_पढ़ो(काष्ठा anx7625_data *ctx,
			      u8 segment, u8 *buf, u8 offset)
अणु
	u8 cnt;
	पूर्णांक ret;
	काष्ठा device *dev = &ctx->client->dev;

	/* Write address only */
	ret = anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				AP_AUX_ADDR_7_0, 0x30);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				 AP_AUX_COMMAND, 0x04);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				 AP_AUX_CTRL_STATUS,
				 AP_AUX_CTRL_ADDRONLY | AP_AUX_CTRL_OP_EN);

	ret |= रुको_aux_op_finish(ctx);
	/* Write segment address */
	ret |= sp_tx_aux_wr(ctx, segment);
	/* Data पढ़ो */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				 AP_AUX_ADDR_7_0, 0x50);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "IO error : aux initial fail.\n");
		वापस ret;
	पूर्ण

	क्रम (cnt = 0; cnt <= EDID_TRY_CNT; cnt++) अणु
		sp_tx_aux_wr(ctx, offset);
		/* Set I2C पढ़ो com 0x01 mot = 0 and पढ़ो 16 bytes */
		ret = sp_tx_aux_rd(ctx, 0xf1);

		अगर (ret) अणु
			ret = sp_tx_rst_aux(ctx);
			DRM_DEV_ERROR(dev, "segment read fail, reset!\n");
		पूर्ण अन्यथा अणु
			ret = anx7625_reg_block_पढ़ो(ctx, ctx->i2c.rx_p0_client,
						     AP_AUX_BUFF_START,
						     MAX_DPCD_BUFFER_SIZE, buf);
			अगर (ret > 0)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (cnt > EDID_TRY_CNT)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक sp_tx_edid_पढ़ो(काष्ठा anx7625_data *ctx,
			   u8 *pedid_blocks_buf)
अणु
	u8 offset, edid_pos;
	पूर्णांक count, blocks_num;
	u8 pblock_buf[MAX_DPCD_BUFFER_SIZE];
	u8 i, j;
	u8 g_edid_अवरोध = 0;
	पूर्णांक ret;
	काष्ठा device *dev = &ctx->client->dev;

	/* Address initial */
	ret = anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				AP_AUX_ADDR_7_0, 0x50);
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				 AP_AUX_ADDR_15_8, 0);
	ret |= anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p0_client,
				 AP_AUX_ADDR_19_16, 0xf0);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "access aux channel IO error.\n");
		वापस -EIO;
	पूर्ण

	blocks_num = sp_tx_get_edid_block(ctx);
	अगर (blocks_num < 0)
		वापस blocks_num;

	count = 0;

	करो अणु
		चयन (count) अणु
		हाल 0:
		हाल 1:
			क्रम (i = 0; i < 8; i++) अणु
				offset = (i + count * 8) * MAX_DPCD_BUFFER_SIZE;
				g_edid_अवरोध = edid_पढ़ो(ctx, offset,
							 pblock_buf);

				अगर (g_edid_अवरोध)
					अवरोध;

				स_नकल(&pedid_blocks_buf[offset],
				       pblock_buf,
				       MAX_DPCD_BUFFER_SIZE);
			पूर्ण

			अवरोध;
		हाल 2:
			offset = 0x00;

			क्रम (j = 0; j < 8; j++) अणु
				edid_pos = (j + count * 8) *
					MAX_DPCD_BUFFER_SIZE;

				अगर (g_edid_अवरोध == 1)
					अवरोध;

				segments_edid_पढ़ो(ctx, count / 2,
						   pblock_buf, offset);
				स_नकल(&pedid_blocks_buf[edid_pos],
				       pblock_buf,
				       MAX_DPCD_BUFFER_SIZE);
				offset = offset + 0x10;
			पूर्ण

			अवरोध;
		हाल 3:
			offset = 0x80;

			क्रम (j = 0; j < 8; j++) अणु
				edid_pos = (j + count * 8) *
					MAX_DPCD_BUFFER_SIZE;
				अगर (g_edid_अवरोध == 1)
					अवरोध;

				segments_edid_पढ़ो(ctx, count / 2,
						   pblock_buf, offset);
				स_नकल(&pedid_blocks_buf[edid_pos],
				       pblock_buf,
				       MAX_DPCD_BUFFER_SIZE);
				offset = offset + 0x10;
			पूर्ण

			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		count++;

	पूर्ण जबतक (blocks_num >= count);

	/* Check edid data */
	अगर (!drm_edid_is_valid((काष्ठा edid *)pedid_blocks_buf)) अणु
		DRM_DEV_ERROR(dev, "WARNING! edid check fail!\n");
		वापस -EINVAL;
	पूर्ण

	/* Reset aux channel */
	sp_tx_rst_aux(ctx);

	वापस (blocks_num + 1);
पूर्ण

अटल व्योम anx7625_घातer_on(काष्ठा anx7625_data *ctx)
अणु
	काष्ठा device *dev = &ctx->client->dev;
	पूर्णांक ret, i;

	अगर (!ctx->pdata.low_घातer_mode) अणु
		DRM_DEV_DEBUG_DRIVER(dev, "not low power mode!\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ctx->pdata.supplies); i++) अणु
		ret = regulator_enable(ctx->pdata.supplies[i].consumer);
		अगर (ret < 0) अणु
			DRM_DEV_DEBUG_DRIVER(dev, "cannot enable supply %d: %d\n",
					     i, ret);
			जाओ reg_err;
		पूर्ण
		usleep_range(2000, 2100);
	पूर्ण

	usleep_range(4000, 4100);

	/* Power on pin enable */
	gpiod_set_value(ctx->pdata.gpio_p_on, 1);
	usleep_range(10000, 11000);
	/* Power reset pin enable */
	gpiod_set_value(ctx->pdata.gpio_reset, 1);
	usleep_range(10000, 11000);

	DRM_DEV_DEBUG_DRIVER(dev, "power on !\n");
	वापस;
reg_err:
	क्रम (--i; i >= 0; i--)
		regulator_disable(ctx->pdata.supplies[i].consumer);
पूर्ण

अटल व्योम anx7625_घातer_standby(काष्ठा anx7625_data *ctx)
अणु
	काष्ठा device *dev = &ctx->client->dev;
	पूर्णांक ret;

	अगर (!ctx->pdata.low_घातer_mode) अणु
		DRM_DEV_DEBUG_DRIVER(dev, "not low power mode!\n");
		वापस;
	पूर्ण

	gpiod_set_value(ctx->pdata.gpio_reset, 0);
	usleep_range(1000, 1100);
	gpiod_set_value(ctx->pdata.gpio_p_on, 0);
	usleep_range(1000, 1100);

	ret = regulator_bulk_disable(ARRAY_SIZE(ctx->pdata.supplies),
				     ctx->pdata.supplies);
	अगर (ret < 0)
		DRM_DEV_DEBUG_DRIVER(dev, "cannot disable supplies %d\n", ret);

	DRM_DEV_DEBUG_DRIVER(dev, "power down\n");
पूर्ण

/* Basic configurations of ANX7625 */
अटल व्योम anx7625_config(काष्ठा anx7625_data *ctx)
अणु
	anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
			  XTAL_FRQ_SEL, XTAL_FRQ_27M);
पूर्ण

अटल व्योम anx7625_disable_pd_protocol(काष्ठा anx7625_data *ctx)
अणु
	काष्ठा device *dev = &ctx->client->dev;
	पूर्णांक ret;

	/* Reset मुख्य ocm */
	ret = anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client, 0x88, 0x40);
	/* Disable PD */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				 AP_AV_STATUS, AP_DISABLE_PD);
	/* Release मुख्य ocm */
	ret |= anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client, 0x88, 0x00);

	अगर (ret < 0)
		DRM_DEV_DEBUG_DRIVER(dev, "disable PD feature fail.\n");
	अन्यथा
		DRM_DEV_DEBUG_DRIVER(dev, "disable PD feature succeeded.\n");
पूर्ण

अटल पूर्णांक anx7625_ocm_loading_check(काष्ठा anx7625_data *ctx)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &ctx->client->dev;

	/* Check पूर्णांकerface workable */
	ret = anx7625_reg_पढ़ो(ctx, ctx->i2c.rx_p0_client,
			       FLASH_LOAD_STA);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "IO error : access flash load.\n");
		वापस ret;
	पूर्ण
	अगर ((ret & FLASH_LOAD_STA_CHK) != FLASH_LOAD_STA_CHK)
		वापस -ENODEV;

	anx7625_disable_pd_protocol(ctx);

	DRM_DEV_DEBUG_DRIVER(dev, "Firmware ver %02x%02x,",
			     anx7625_reg_पढ़ो(ctx,
					      ctx->i2c.rx_p0_client,
					      OCM_FW_VERSION),
			     anx7625_reg_पढ़ो(ctx,
					      ctx->i2c.rx_p0_client,
					      OCM_FW_REVERSION));
	DRM_DEV_DEBUG_DRIVER(dev, "Driver version %s\n",
			     ANX7625_DRV_VERSION);

	वापस 0;
पूर्ण

अटल व्योम anx7625_घातer_on_init(काष्ठा anx7625_data *ctx)
अणु
	पूर्णांक retry_count, i;

	क्रम (retry_count = 0; retry_count < 3; retry_count++) अणु
		anx7625_घातer_on(ctx);
		anx7625_config(ctx);

		क्रम (i = 0; i < OCM_LOADING_TIME; i++) अणु
			अगर (!anx7625_ocm_loading_check(ctx))
				वापस;
			usleep_range(1000, 1100);
		पूर्ण
		anx7625_घातer_standby(ctx);
	पूर्ण
पूर्ण

अटल व्योम anx7625_chip_control(काष्ठा anx7625_data *ctx, पूर्णांक state)
अणु
	काष्ठा device *dev = &ctx->client->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "before set, power_state(%d).\n",
			     atomic_पढ़ो(&ctx->घातer_status));

	अगर (!ctx->pdata.low_घातer_mode)
		वापस;

	अगर (state) अणु
		atomic_inc(&ctx->घातer_status);
		अगर (atomic_पढ़ो(&ctx->घातer_status) == 1)
			anx7625_घातer_on_init(ctx);
	पूर्ण अन्यथा अणु
		अगर (atomic_पढ़ो(&ctx->घातer_status)) अणु
			atomic_dec(&ctx->घातer_status);

			अगर (atomic_पढ़ो(&ctx->घातer_status) == 0)
				anx7625_घातer_standby(ctx);
		पूर्ण
	पूर्ण

	DRM_DEV_DEBUG_DRIVER(dev, "after set, power_state(%d).\n",
			     atomic_पढ़ो(&ctx->घातer_status));
पूर्ण

अटल व्योम anx7625_init_gpio(काष्ठा anx7625_data *platक्रमm)
अणु
	काष्ठा device *dev = &platक्रमm->client->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "init gpio\n");

	/* Gpio क्रम chip घातer enable */
	platक्रमm->pdata.gpio_p_on =
		devm_gpiod_get_optional(dev, "enable", GPIOD_OUT_LOW);
	/* Gpio क्रम chip reset */
	platक्रमm->pdata.gpio_reset =
		devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);

	अगर (platक्रमm->pdata.gpio_p_on && platक्रमm->pdata.gpio_reset) अणु
		platक्रमm->pdata.low_घातer_mode = 1;
		DRM_DEV_DEBUG_DRIVER(dev, "low power mode, pon %d, reset %d.\n",
				     desc_to_gpio(platक्रमm->pdata.gpio_p_on),
				     desc_to_gpio(platक्रमm->pdata.gpio_reset));
	पूर्ण अन्यथा अणु
		platक्रमm->pdata.low_घातer_mode = 0;
		DRM_DEV_DEBUG_DRIVER(dev, "not low power mode.\n");
	पूर्ण
पूर्ण

अटल व्योम anx7625_stop_dp_work(काष्ठा anx7625_data *ctx)
अणु
	ctx->hpd_status = 0;
	ctx->hpd_high_cnt = 0;
	ctx->display_timing_valid = 0;

	अगर (ctx->pdata.low_घातer_mode == 0)
		anx7625_disable_pd_protocol(ctx);
पूर्ण

अटल व्योम anx7625_start_dp_work(काष्ठा anx7625_data *ctx)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &ctx->client->dev;

	अगर (ctx->hpd_high_cnt >= 2) अणु
		DRM_DEV_DEBUG_DRIVER(dev, "filter useless HPD\n");
		वापस;
	पूर्ण

	ctx->hpd_high_cnt++;

	/* Not support HDCP */
	ret = anx7625_ग_लिखो_and(ctx, ctx->i2c.rx_p1_client, 0xee, 0x9f);

	/* Try auth flag */
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p1_client, 0xec, 0x10);
	/* Interrupt क्रम DRM */
	ret |= anx7625_ग_लिखो_or(ctx, ctx->i2c.rx_p1_client, 0xff, 0x01);
	अगर (ret < 0)
		वापस;

	ret = anx7625_reg_पढ़ो(ctx, ctx->i2c.rx_p1_client, 0x86);
	अगर (ret < 0)
		वापस;

	DRM_DEV_DEBUG_DRIVER(dev, "Secure OCM version=%02x\n", ret);
पूर्ण

अटल पूर्णांक anx7625_पढ़ो_hpd_status_p0(काष्ठा anx7625_data *ctx)
अणु
	वापस anx7625_reg_पढ़ो(ctx, ctx->i2c.rx_p0_client, SYSTEM_STSTUS);
पूर्ण

अटल व्योम anx7625_hpd_polling(काष्ठा anx7625_data *ctx)
अणु
	पूर्णांक ret, val;
	काष्ठा device *dev = &ctx->client->dev;

	अगर (atomic_पढ़ो(&ctx->घातer_status) != 1) अणु
		DRM_DEV_DEBUG_DRIVER(dev, "No need to poling HPD status.\n");
		वापस;
	पूर्ण

	ret = पढ़ोx_poll_समयout(anx7625_पढ़ो_hpd_status_p0,
				 ctx, val,
				 ((val & HPD_STATUS) || (val < 0)),
				 5000,
				 5000 * 100);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "HPD polling timeout!\n");
	पूर्ण अन्यथा अणु
		DRM_DEV_DEBUG_DRIVER(dev, "HPD raise up.\n");
		anx7625_reg_ग_लिखो(ctx, ctx->i2c.tcpc_client,
				  INTR_ALERT_1, 0xFF);
		anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				  INTERFACE_CHANGE_INT, 0);
	पूर्ण

	anx7625_start_dp_work(ctx);
पूर्ण

अटल व्योम anx7625_disconnect_check(काष्ठा anx7625_data *ctx)
अणु
	अगर (atomic_पढ़ो(&ctx->घातer_status) == 0)
		anx7625_stop_dp_work(ctx);
पूर्ण

अटल व्योम anx7625_low_घातer_mode_check(काष्ठा anx7625_data *ctx,
					 पूर्णांक state)
अणु
	काष्ठा device *dev = &ctx->client->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "low power mode check, state(%d).\n", state);

	अगर (ctx->pdata.low_घातer_mode) अणु
		anx7625_chip_control(ctx, state);
		अगर (state)
			anx7625_hpd_polling(ctx);
		अन्यथा
			anx7625_disconnect_check(ctx);
	पूर्ण
पूर्ण

अटल व्योम anx7625_हटाओ_edid(काष्ठा anx7625_data *ctx)
अणु
	ctx->slimport_edid_p.edid_block_num = -1;
पूर्ण

अटल व्योम dp_hpd_change_handler(काष्ठा anx7625_data *ctx, bool on)
अणु
	काष्ठा device *dev = &ctx->client->dev;

	/* HPD changed */
	DRM_DEV_DEBUG_DRIVER(dev, "dp_hpd_change_default_func: %d\n",
			     (u32)on);

	अगर (on == 0) अणु
		DRM_DEV_DEBUG_DRIVER(dev, " HPD low\n");
		anx7625_हटाओ_edid(ctx);
		anx7625_stop_dp_work(ctx);
	पूर्ण अन्यथा अणु
		DRM_DEV_DEBUG_DRIVER(dev, " HPD high\n");
		anx7625_start_dp_work(ctx);
	पूर्ण

	ctx->hpd_status = 1;
पूर्ण

अटल पूर्णांक anx7625_hpd_change_detect(काष्ठा anx7625_data *ctx)
अणु
	पूर्णांक पूर्णांकr_vector, status;
	काष्ठा device *dev = &ctx->client->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "power_status=%d\n",
			     (u32)atomic_पढ़ो(&ctx->घातer_status));

	status = anx7625_reg_ग_लिखो(ctx, ctx->i2c.tcpc_client,
				   INTR_ALERT_1, 0xFF);
	अगर (status < 0) अणु
		DRM_DEV_ERROR(dev, "cannot clear alert reg.\n");
		वापस status;
	पूर्ण

	पूर्णांकr_vector = anx7625_reg_पढ़ो(ctx, ctx->i2c.rx_p0_client,
				       INTERFACE_CHANGE_INT);
	अगर (पूर्णांकr_vector < 0) अणु
		DRM_DEV_ERROR(dev, "cannot access interrupt change reg.\n");
		वापस पूर्णांकr_vector;
	पूर्ण
	DRM_DEV_DEBUG_DRIVER(dev, "0x7e:0x44=%x\n", पूर्णांकr_vector);
	status = anx7625_reg_ग_लिखो(ctx, ctx->i2c.rx_p0_client,
				   INTERFACE_CHANGE_INT,
				   पूर्णांकr_vector & (~पूर्णांकr_vector));
	अगर (status < 0) अणु
		DRM_DEV_ERROR(dev, "cannot clear interrupt change reg.\n");
		वापस status;
	पूर्ण

	अगर (!(पूर्णांकr_vector & HPD_STATUS_CHANGE))
		वापस -ENOENT;

	status = anx7625_reg_पढ़ो(ctx, ctx->i2c.rx_p0_client,
				  SYSTEM_STSTUS);
	अगर (status < 0) अणु
		DRM_DEV_ERROR(dev, "cannot clear interrupt status.\n");
		वापस status;
	पूर्ण

	DRM_DEV_DEBUG_DRIVER(dev, "0x7e:0x45=%x\n", status);
	dp_hpd_change_handler(ctx, status & HPD_STATUS);

	वापस 0;
पूर्ण

अटल व्योम anx7625_work_func(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक event;
	काष्ठा anx7625_data *ctx = container_of(work,
						काष्ठा anx7625_data, work);

	mutex_lock(&ctx->lock);
	event = anx7625_hpd_change_detect(ctx);
	mutex_unlock(&ctx->lock);
	अगर (event < 0)
		वापस;

	अगर (ctx->bridge_attached)
		drm_helper_hpd_irq_event(ctx->bridge.dev);
पूर्ण

अटल irqवापस_t anx7625_पूर्णांकr_hpd_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा anx7625_data *ctx = (काष्ठा anx7625_data *)data;

	अगर (atomic_पढ़ो(&ctx->घातer_status) != 1)
		वापस IRQ_NONE;

	queue_work(ctx->workqueue, &ctx->work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक anx7625_parse_dt(काष्ठा device *dev,
			    काष्ठा anx7625_platक्रमm_data *pdata)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा drm_panel *panel;
	पूर्णांक ret;

	pdata->mipi_host_node = of_graph_get_remote_node(np, 0, 0);
	अगर (!pdata->mipi_host_node) अणु
		DRM_DEV_ERROR(dev, "fail to get internal panel.\n");
		वापस -ENODEV;
	पूर्ण

	DRM_DEV_DEBUG_DRIVER(dev, "found dsi host node.\n");

	ret = drm_of_find_panel_or_bridge(np, 1, 0, &panel, शून्य);
	अगर (ret < 0) अणु
		अगर (ret == -ENODEV)
			वापस 0;
		वापस ret;
	पूर्ण
	अगर (!panel)
		वापस -ENODEV;

	pdata->panel_bridge = devm_drm_panel_bridge_add(dev, panel);
	अगर (IS_ERR(pdata->panel_bridge))
		वापस PTR_ERR(pdata->panel_bridge);
	DRM_DEV_DEBUG_DRIVER(dev, "get panel node.\n");

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा anx7625_data *bridge_to_anx7625(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा anx7625_data, bridge);
पूर्ण

अटल काष्ठा edid *anx7625_get_edid(काष्ठा anx7625_data *ctx)
अणु
	काष्ठा device *dev = &ctx->client->dev;
	काष्ठा s_edid_data *p_edid = &ctx->slimport_edid_p;
	पूर्णांक edid_num;
	u8 *edid;

	edid = kदो_स्मृति(FOUR_BLOCK_SIZE, GFP_KERNEL);
	अगर (!edid) अणु
		DRM_DEV_ERROR(dev, "Fail to allocate buffer\n");
		वापस शून्य;
	पूर्ण

	अगर (ctx->slimport_edid_p.edid_block_num > 0) अणु
		स_नकल(edid, ctx->slimport_edid_p.edid_raw_data,
		       FOUR_BLOCK_SIZE);
		वापस (काष्ठा edid *)edid;
	पूर्ण

	anx7625_low_घातer_mode_check(ctx, 1);
	edid_num = sp_tx_edid_पढ़ो(ctx, p_edid->edid_raw_data);
	anx7625_low_घातer_mode_check(ctx, 0);

	अगर (edid_num < 1) अणु
		DRM_DEV_ERROR(dev, "Fail to read EDID: %d\n", edid_num);
		kमुक्त(edid);
		वापस शून्य;
	पूर्ण

	p_edid->edid_block_num = edid_num;

	स_नकल(edid, ctx->slimport_edid_p.edid_raw_data, FOUR_BLOCK_SIZE);
	वापस (काष्ठा edid *)edid;
पूर्ण

अटल क्रमागत drm_connector_status anx7625_sink_detect(काष्ठा anx7625_data *ctx)
अणु
	काष्ठा device *dev = &ctx->client->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "sink detect, return connected\n");

	वापस connector_status_connected;
पूर्ण

अटल पूर्णांक anx7625_attach_dsi(काष्ठा anx7625_data *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा device *dev = &ctx->client->dev;
	काष्ठा mipi_dsi_host *host;
	स्थिर काष्ठा mipi_dsi_device_info info = अणु
		.type = "anx7625",
		.channel = 0,
		.node = शून्य,
	पूर्ण;

	DRM_DEV_DEBUG_DRIVER(dev, "attach dsi\n");

	host = of_find_mipi_dsi_host_by_node(ctx->pdata.mipi_host_node);
	अगर (!host) अणु
		DRM_DEV_ERROR(dev, "fail to find dsi host.\n");
		वापस -EINVAL;
	पूर्ण

	dsi = mipi_dsi_device_रेजिस्टर_full(host, &info);
	अगर (IS_ERR(dsi)) अणु
		DRM_DEV_ERROR(dev, "fail to create dsi device.\n");
		वापस -EINVAL;
	पूर्ण

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO	|
		MIPI_DSI_MODE_VIDEO_SYNC_PULSE	|
		MIPI_DSI_MODE_EOT_PACKET	|
		MIPI_DSI_MODE_VIDEO_HSE;

	अगर (mipi_dsi_attach(dsi) < 0) अणु
		DRM_DEV_ERROR(dev, "fail to attach dsi to host.\n");
		mipi_dsi_device_unरेजिस्टर(dsi);
		वापस -EINVAL;
	पूर्ण

	ctx->dsi = dsi;

	DRM_DEV_DEBUG_DRIVER(dev, "attach dsi succeeded.\n");

	वापस 0;
पूर्ण

अटल व्योम anx7625_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा anx7625_data *ctx = bridge_to_anx7625(bridge);

	अगर (ctx->dsi) अणु
		mipi_dsi_detach(ctx->dsi);
		mipi_dsi_device_unरेजिस्टर(ctx->dsi);
	पूर्ण
पूर्ण

अटल पूर्णांक anx7625_bridge_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा anx7625_data *ctx = bridge_to_anx7625(bridge);
	पूर्णांक err;
	काष्ठा device *dev = &ctx->client->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "drm attach\n");
	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR))
		वापस -EINVAL;

	अगर (!bridge->encoder) अणु
		DRM_DEV_ERROR(dev, "Parent encoder object not found");
		वापस -ENODEV;
	पूर्ण

	err = anx7625_attach_dsi(ctx);
	अगर (err) अणु
		DRM_DEV_ERROR(dev, "Fail to attach to dsi : %d\n", err);
		वापस err;
	पूर्ण

	अगर (ctx->pdata.panel_bridge) अणु
		err = drm_bridge_attach(bridge->encoder,
					ctx->pdata.panel_bridge,
					&ctx->bridge, flags);
		अगर (err) अणु
			DRM_DEV_ERROR(dev,
				      "Fail to attach panel bridge: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	ctx->bridge_attached = 1;

	वापस 0;
पूर्ण

अटल क्रमागत drm_mode_status
anx7625_bridge_mode_valid(काष्ठा drm_bridge *bridge,
			  स्थिर काष्ठा drm_display_info *info,
			  स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा anx7625_data *ctx = bridge_to_anx7625(bridge);
	काष्ठा device *dev = &ctx->client->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "drm mode checking\n");

	/* Max 1200p at 5.4 Ghz, one lane, pixel घड़ी 300M */
	अगर (mode->घड़ी > SUPPORT_PIXEL_CLOCK) अणु
		DRM_DEV_DEBUG_DRIVER(dev,
				     "drm mode invalid, pixelclock too high.\n");
		वापस MODE_CLOCK_HIGH;
	पूर्ण

	DRM_DEV_DEBUG_DRIVER(dev, "drm mode valid.\n");

	वापस MODE_OK;
पूर्ण

अटल व्योम anx7625_bridge_mode_set(काष्ठा drm_bridge *bridge,
				    स्थिर काष्ठा drm_display_mode *old_mode,
				    स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा anx7625_data *ctx = bridge_to_anx7625(bridge);
	काष्ठा device *dev = &ctx->client->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "drm mode set\n");

	ctx->dt.pixelघड़ी.min = mode->घड़ी;
	ctx->dt.hactive.min = mode->hdisplay;
	ctx->dt.hsync_len.min = mode->hsync_end - mode->hsync_start;
	ctx->dt.hfront_porch.min = mode->hsync_start - mode->hdisplay;
	ctx->dt.hback_porch.min = mode->htotal - mode->hsync_end;
	ctx->dt.vactive.min = mode->vdisplay;
	ctx->dt.vsync_len.min = mode->vsync_end - mode->vsync_start;
	ctx->dt.vfront_porch.min = mode->vsync_start - mode->vdisplay;
	ctx->dt.vback_porch.min = mode->vtotal - mode->vsync_end;

	ctx->display_timing_valid = 1;

	DRM_DEV_DEBUG_DRIVER(dev, "pixelclock(%d).\n", ctx->dt.pixelघड़ी.min);
	DRM_DEV_DEBUG_DRIVER(dev, "hactive(%d), hsync(%d), hfp(%d), hbp(%d)\n",
			     ctx->dt.hactive.min,
			     ctx->dt.hsync_len.min,
			     ctx->dt.hfront_porch.min,
			     ctx->dt.hback_porch.min);
	DRM_DEV_DEBUG_DRIVER(dev, "vactive(%d), vsync(%d), vfp(%d), vbp(%d)\n",
			     ctx->dt.vactive.min,
			     ctx->dt.vsync_len.min,
			     ctx->dt.vfront_porch.min,
			     ctx->dt.vback_porch.min);
	DRM_DEV_DEBUG_DRIVER(dev, "hdisplay(%d),hsync_start(%d).\n",
			     mode->hdisplay,
			     mode->hsync_start);
	DRM_DEV_DEBUG_DRIVER(dev, "hsync_end(%d),htotal(%d).\n",
			     mode->hsync_end,
			     mode->htotal);
	DRM_DEV_DEBUG_DRIVER(dev, "vdisplay(%d),vsync_start(%d).\n",
			     mode->vdisplay,
			     mode->vsync_start);
	DRM_DEV_DEBUG_DRIVER(dev, "vsync_end(%d),vtotal(%d).\n",
			     mode->vsync_end,
			     mode->vtotal);
पूर्ण

अटल bool anx7625_bridge_mode_fixup(काष्ठा drm_bridge *bridge,
				      स्थिर काष्ठा drm_display_mode *mode,
				      काष्ठा drm_display_mode *adj)
अणु
	काष्ठा anx7625_data *ctx = bridge_to_anx7625(bridge);
	काष्ठा device *dev = &ctx->client->dev;
	u32 hsync, hfp, hbp, hblanking;
	u32 adj_hsync, adj_hfp, adj_hbp, adj_hblanking, delta_adj;
	u32 vref, adj_घड़ी;

	DRM_DEV_DEBUG_DRIVER(dev, "drm mode fixup set\n");

	hsync = mode->hsync_end - mode->hsync_start;
	hfp = mode->hsync_start - mode->hdisplay;
	hbp = mode->htotal - mode->hsync_end;
	hblanking = mode->htotal - mode->hdisplay;

	DRM_DEV_DEBUG_DRIVER(dev, "before mode fixup\n");
	DRM_DEV_DEBUG_DRIVER(dev, "hsync(%d), hfp(%d), hbp(%d), clock(%d)\n",
			     hsync, hfp, hbp, adj->घड़ी);
	DRM_DEV_DEBUG_DRIVER(dev, "hsync_start(%d), hsync_end(%d), htot(%d)\n",
			     adj->hsync_start, adj->hsync_end, adj->htotal);

	adj_hfp = hfp;
	adj_hsync = hsync;
	adj_hbp = hbp;
	adj_hblanking = hblanking;

	/* HFP needs to be even */
	अगर (hfp & 0x1) अणु
		adj_hfp += 1;
		adj_hblanking += 1;
	पूर्ण

	/* HBP needs to be even */
	अगर (hbp & 0x1) अणु
		adj_hbp -= 1;
		adj_hblanking -= 1;
	पूर्ण

	/* HSYNC needs to be even */
	अगर (hsync & 0x1) अणु
		अगर (adj_hblanking < hblanking)
			adj_hsync += 1;
		अन्यथा
			adj_hsync -= 1;
	पूर्ण

	/*
	 * Once illegal timing detected, use शेष HFP, HSYNC, HBP
	 * This adjusting made क्रम built-in eDP panel, क्रम the बाह्यel
	 * DP monitor, may need वापस false.
	 */
	अगर (hblanking < HBLANKING_MIN || (hfp < HP_MIN && hbp < HP_MIN)) अणु
		adj_hsync = SYNC_LEN_DEF;
		adj_hfp = HFP_HBP_DEF;
		adj_hbp = HFP_HBP_DEF;
		vref = adj->घड़ी * 1000 / (adj->htotal * adj->vtotal);
		अगर (hblanking < HBLANKING_MIN) अणु
			delta_adj = HBLANKING_MIN - hblanking;
			adj_घड़ी = vref * delta_adj * adj->vtotal;
			adj->घड़ी += DIV_ROUND_UP(adj_घड़ी, 1000);
		पूर्ण अन्यथा अणु
			delta_adj = hblanking - HBLANKING_MIN;
			adj_घड़ी = vref * delta_adj * adj->vtotal;
			adj->घड़ी -= DIV_ROUND_UP(adj_घड़ी, 1000);
		पूर्ण

		DRM_WARN("illegal hblanking timing, use default.\n");
		DRM_WARN("hfp(%d), hbp(%d), hsync(%d).\n", hfp, hbp, hsync);
	पूर्ण अन्यथा अगर (adj_hfp < HP_MIN) अणु
		/* Adjust hfp अगर hfp less than HP_MIN */
		delta_adj = HP_MIN - adj_hfp;
		adj_hfp = HP_MIN;

		/*
		 * Balance total HBlanking pixel, अगर HBP करोes not have enough
		 * space, adjust HSYNC length, otherwise adjust HBP
		 */
		अगर ((adj_hbp - delta_adj) < HP_MIN)
			/* HBP not enough space */
			adj_hsync -= delta_adj;
		अन्यथा
			adj_hbp -= delta_adj;
	पूर्ण अन्यथा अगर (adj_hbp < HP_MIN) अणु
		delta_adj = HP_MIN - adj_hbp;
		adj_hbp = HP_MIN;

		/*
		 * Balance total HBlanking pixel, अगर HBP hasn't enough space,
		 * adjust HSYNC length, otherwize adjust HBP
		 */
		अगर ((adj_hfp - delta_adj) < HP_MIN)
			/* HFP not enough space */
			adj_hsync -= delta_adj;
		अन्यथा
			adj_hfp -= delta_adj;
	पूर्ण

	DRM_DEV_DEBUG_DRIVER(dev, "after mode fixup\n");
	DRM_DEV_DEBUG_DRIVER(dev, "hsync(%d), hfp(%d), hbp(%d), clock(%d)\n",
			     adj_hsync, adj_hfp, adj_hbp, adj->घड़ी);

	/* Reस्थिरruct timing */
	adj->hsync_start = adj->hdisplay + adj_hfp;
	adj->hsync_end = adj->hsync_start + adj_hsync;
	adj->htotal = adj->hsync_end + adj_hbp;
	DRM_DEV_DEBUG_DRIVER(dev, "hsync_start(%d), hsync_end(%d), htot(%d)\n",
			     adj->hsync_start, adj->hsync_end, adj->htotal);

	वापस true;
पूर्ण

अटल व्योम anx7625_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा anx7625_data *ctx = bridge_to_anx7625(bridge);
	काष्ठा device *dev = &ctx->client->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "drm enable\n");

	anx7625_low_घातer_mode_check(ctx, 1);

	अगर (WARN_ON(!atomic_पढ़ो(&ctx->घातer_status)))
		वापस;

	anx7625_dp_start(ctx);
पूर्ण

अटल व्योम anx7625_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा anx7625_data *ctx = bridge_to_anx7625(bridge);
	काष्ठा device *dev = &ctx->client->dev;

	अगर (WARN_ON(!atomic_पढ़ो(&ctx->घातer_status)))
		वापस;

	DRM_DEV_DEBUG_DRIVER(dev, "drm disable\n");

	anx7625_dp_stop(ctx);

	anx7625_low_घातer_mode_check(ctx, 0);
पूर्ण

अटल क्रमागत drm_connector_status
anx7625_bridge_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा anx7625_data *ctx = bridge_to_anx7625(bridge);
	काष्ठा device *dev = &ctx->client->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "drm bridge detect\n");

	वापस anx7625_sink_detect(ctx);
पूर्ण

अटल काष्ठा edid *anx7625_bridge_get_edid(काष्ठा drm_bridge *bridge,
					    काष्ठा drm_connector *connector)
अणु
	काष्ठा anx7625_data *ctx = bridge_to_anx7625(bridge);
	काष्ठा device *dev = &ctx->client->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "drm bridge get edid\n");

	वापस anx7625_get_edid(ctx);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs anx7625_bridge_funcs = अणु
	.attach = anx7625_bridge_attach,
	.detach = anx7625_bridge_detach,
	.disable = anx7625_bridge_disable,
	.mode_valid = anx7625_bridge_mode_valid,
	.mode_set = anx7625_bridge_mode_set,
	.mode_fixup = anx7625_bridge_mode_fixup,
	.enable = anx7625_bridge_enable,
	.detect = anx7625_bridge_detect,
	.get_edid = anx7625_bridge_get_edid,
पूर्ण;

अटल पूर्णांक anx7625_रेजिस्टर_i2c_dummy_clients(काष्ठा anx7625_data *ctx,
					      काष्ठा i2c_client *client)
अणु
	ctx->i2c.tx_p0_client = i2c_new_dummy_device(client->adapter,
						     TX_P0_ADDR >> 1);
	अगर (!ctx->i2c.tx_p0_client)
		वापस -ENOMEM;

	ctx->i2c.tx_p1_client = i2c_new_dummy_device(client->adapter,
						     TX_P1_ADDR >> 1);
	अगर (!ctx->i2c.tx_p1_client)
		जाओ मुक्त_tx_p0;

	ctx->i2c.tx_p2_client = i2c_new_dummy_device(client->adapter,
						     TX_P2_ADDR >> 1);
	अगर (!ctx->i2c.tx_p2_client)
		जाओ मुक्त_tx_p1;

	ctx->i2c.rx_p0_client = i2c_new_dummy_device(client->adapter,
						     RX_P0_ADDR >> 1);
	अगर (!ctx->i2c.rx_p0_client)
		जाओ मुक्त_tx_p2;

	ctx->i2c.rx_p1_client = i2c_new_dummy_device(client->adapter,
						     RX_P1_ADDR >> 1);
	अगर (!ctx->i2c.rx_p1_client)
		जाओ मुक्त_rx_p0;

	ctx->i2c.rx_p2_client = i2c_new_dummy_device(client->adapter,
						     RX_P2_ADDR >> 1);
	अगर (!ctx->i2c.rx_p2_client)
		जाओ मुक्त_rx_p1;

	ctx->i2c.tcpc_client = i2c_new_dummy_device(client->adapter,
						    TCPC_INTERFACE_ADDR >> 1);
	अगर (!ctx->i2c.tcpc_client)
		जाओ मुक्त_rx_p2;

	वापस 0;

मुक्त_rx_p2:
	i2c_unरेजिस्टर_device(ctx->i2c.rx_p2_client);
मुक्त_rx_p1:
	i2c_unरेजिस्टर_device(ctx->i2c.rx_p1_client);
मुक्त_rx_p0:
	i2c_unरेजिस्टर_device(ctx->i2c.rx_p0_client);
मुक्त_tx_p2:
	i2c_unरेजिस्टर_device(ctx->i2c.tx_p2_client);
मुक्त_tx_p1:
	i2c_unरेजिस्टर_device(ctx->i2c.tx_p1_client);
मुक्त_tx_p0:
	i2c_unरेजिस्टर_device(ctx->i2c.tx_p0_client);

	वापस -ENOMEM;
पूर्ण

अटल व्योम anx7625_unरेजिस्टर_i2c_dummy_clients(काष्ठा anx7625_data *ctx)
अणु
	i2c_unरेजिस्टर_device(ctx->i2c.tx_p0_client);
	i2c_unरेजिस्टर_device(ctx->i2c.tx_p1_client);
	i2c_unरेजिस्टर_device(ctx->i2c.tx_p2_client);
	i2c_unरेजिस्टर_device(ctx->i2c.rx_p0_client);
	i2c_unरेजिस्टर_device(ctx->i2c.rx_p1_client);
	i2c_unरेजिस्टर_device(ctx->i2c.rx_p2_client);
	i2c_unरेजिस्टर_device(ctx->i2c.tcpc_client);
पूर्ण

अटल पूर्णांक anx7625_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा anx7625_data *platक्रमm;
	काष्ठा anx7625_platक्रमm_data *pdata;
	पूर्णांक ret = 0;
	काष्ठा device *dev = &client->dev;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_I2C_BLOCK)) अणु
		DRM_DEV_ERROR(dev, "anx7625's i2c bus doesn't support\n");
		वापस -ENODEV;
	पूर्ण

	platक्रमm = kzalloc(माप(*platक्रमm), GFP_KERNEL);
	अगर (!platक्रमm) अणु
		DRM_DEV_ERROR(dev, "fail to allocate driver data\n");
		वापस -ENOMEM;
	पूर्ण

	pdata = &platक्रमm->pdata;

	ret = anx7625_parse_dt(dev, pdata);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "fail to parse DT : %d\n", ret);
		जाओ मुक्त_platक्रमm;
	पूर्ण

	platक्रमm->client = client;
	i2c_set_clientdata(client, platक्रमm);

	pdata->supplies[0].supply = "vdd10";
	pdata->supplies[1].supply = "vdd18";
	pdata->supplies[2].supply = "vdd33";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(pdata->supplies),
				      pdata->supplies);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "fail to get power supplies: %d\n", ret);
		वापस ret;
	पूर्ण
	anx7625_init_gpio(platक्रमm);

	atomic_set(&platक्रमm->घातer_status, 0);

	mutex_init(&platक्रमm->lock);

	platक्रमm->pdata.पूर्णांकp_irq = client->irq;
	अगर (platक्रमm->pdata.पूर्णांकp_irq) अणु
		INIT_WORK(&platक्रमm->work, anx7625_work_func);
		platक्रमm->workqueue = create_workqueue("anx7625_work");
		अगर (!platक्रमm->workqueue) अणु
			DRM_DEV_ERROR(dev, "fail to create work queue\n");
			ret = -ENOMEM;
			जाओ मुक्त_platक्रमm;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(dev, platक्रमm->pdata.पूर्णांकp_irq,
						शून्य, anx7625_पूर्णांकr_hpd_isr,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						"anx7625-intp", platक्रमm);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev, "fail to request irq\n");
			जाओ मुक्त_wq;
		पूर्ण
	पूर्ण

	अगर (anx7625_रेजिस्टर_i2c_dummy_clients(platक्रमm, client) != 0) अणु
		ret = -ENOMEM;
		DRM_DEV_ERROR(dev, "fail to reserve I2C bus.\n");
		जाओ मुक्त_wq;
	पूर्ण

	अगर (platक्रमm->pdata.low_घातer_mode == 0) अणु
		anx7625_disable_pd_protocol(platक्रमm);
		atomic_set(&platक्रमm->घातer_status, 1);
	पूर्ण

	/* Add work function */
	अगर (platक्रमm->pdata.पूर्णांकp_irq)
		queue_work(platक्रमm->workqueue, &platक्रमm->work);

	platक्रमm->bridge.funcs = &anx7625_bridge_funcs;
	platक्रमm->bridge.of_node = client->dev.of_node;
	platक्रमm->bridge.ops = DRM_BRIDGE_OP_EDID | DRM_BRIDGE_OP_HPD;
	platक्रमm->bridge.type = DRM_MODE_CONNECTOR_eDP;
	drm_bridge_add(&platक्रमm->bridge);

	DRM_DEV_DEBUG_DRIVER(dev, "probe done\n");

	वापस 0;

मुक्त_wq:
	अगर (platक्रमm->workqueue)
		destroy_workqueue(platक्रमm->workqueue);

मुक्त_platक्रमm:
	kमुक्त(platक्रमm);

	वापस ret;
पूर्ण

अटल पूर्णांक anx7625_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा anx7625_data *platक्रमm = i2c_get_clientdata(client);

	drm_bridge_हटाओ(&platक्रमm->bridge);

	अगर (platक्रमm->pdata.पूर्णांकp_irq)
		destroy_workqueue(platक्रमm->workqueue);

	anx7625_unरेजिस्टर_i2c_dummy_clients(platक्रमm);

	kमुक्त(platक्रमm);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id anx7625_id[] = अणु
	अणु"anx7625", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, anx7625_id);

अटल स्थिर काष्ठा of_device_id anx_match_table[] = अणु
	अणु.compatible = "analogix,anx7625",पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा i2c_driver anx7625_driver = अणु
	.driver = अणु
		.name = "anx7625",
		.of_match_table = anx_match_table,
	पूर्ण,
	.probe = anx7625_i2c_probe,
	.हटाओ = anx7625_i2c_हटाओ,

	.id_table = anx7625_id,
पूर्ण;

module_i2c_driver(anx7625_driver);

MODULE_DESCRIPTION("MIPI2DP anx7625 driver");
MODULE_AUTHOR("Xin Ji <xji@analogixsemi.com>");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(ANX7625_DRV_VERSION);
