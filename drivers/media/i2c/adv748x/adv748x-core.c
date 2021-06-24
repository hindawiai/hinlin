<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Analog Devices ADV748X HDMI receiver with AFE
 *
 * Copyright (C) 2017 Renesas Electronics Corp.
 *
 * Authors:
 *	Koji Matsuoka <koji.matsuoka.xm@renesas.com>
 *	Niklas Sथघderlund <niklas.soderlund@ragnatech.se>
 *	Kieran Bingham <kieran.bingham@ideasonboard.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/v4l2-dv-timings.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "adv748x.h"

/* -----------------------------------------------------------------------------
 * Register manipulation
 */

#घोषणा ADV748X_REGMAP_CONF(n) \
अणु \
	.name = n, \
	.reg_bits = 8, \
	.val_bits = 8, \
	.max_रेजिस्टर = 0xff, \
	.cache_type = REGCACHE_NONE, \
पूर्ण

अटल स्थिर काष्ठा regmap_config adv748x_regmap_cnf[] = अणु
	ADV748X_REGMAP_CONF("io"),
	ADV748X_REGMAP_CONF("dpll"),
	ADV748X_REGMAP_CONF("cp"),
	ADV748X_REGMAP_CONF("hdmi"),
	ADV748X_REGMAP_CONF("edid"),
	ADV748X_REGMAP_CONF("repeater"),
	ADV748X_REGMAP_CONF("infoframe"),
	ADV748X_REGMAP_CONF("cbus"),
	ADV748X_REGMAP_CONF("cec"),
	ADV748X_REGMAP_CONF("sdp"),
	ADV748X_REGMAP_CONF("txa"),
	ADV748X_REGMAP_CONF("txb"),
पूर्ण;

अटल पूर्णांक adv748x_configure_regmap(काष्ठा adv748x_state *state, पूर्णांक region)
अणु
	पूर्णांक err;

	अगर (!state->i2c_clients[region])
		वापस -ENODEV;

	state->regmap[region] =
		devm_regmap_init_i2c(state->i2c_clients[region],
				     &adv748x_regmap_cnf[region]);

	अगर (IS_ERR(state->regmap[region])) अणु
		err = PTR_ERR(state->regmap[region]);
		adv_err(state,
			"Error initializing regmap %d with error %d\n",
			region, err);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
काष्ठा adv748x_रेजिस्टर_map अणु
	स्थिर अक्षर *name;
	u8 शेष_addr;
पूर्ण;

अटल स्थिर काष्ठा adv748x_रेजिस्टर_map adv748x_शेष_addresses[] = अणु
	[ADV748X_PAGE_IO] = अणु "main", 0x70 पूर्ण,
	[ADV748X_PAGE_DPLL] = अणु "dpll", 0x26 पूर्ण,
	[ADV748X_PAGE_CP] = अणु "cp", 0x22 पूर्ण,
	[ADV748X_PAGE_HDMI] = अणु "hdmi", 0x34 पूर्ण,
	[ADV748X_PAGE_EDID] = अणु "edid", 0x36 पूर्ण,
	[ADV748X_PAGE_REPEATER] = अणु "repeater", 0x32 पूर्ण,
	[ADV748X_PAGE_INFOFRAME] = अणु "infoframe", 0x31 पूर्ण,
	[ADV748X_PAGE_CBUS] = अणु "cbus", 0x30 पूर्ण,
	[ADV748X_PAGE_CEC] = अणु "cec", 0x41 पूर्ण,
	[ADV748X_PAGE_SDP] = अणु "sdp", 0x79 पूर्ण,
	[ADV748X_PAGE_TXB] = अणु "txb", 0x48 पूर्ण,
	[ADV748X_PAGE_TXA] = अणु "txa", 0x4a पूर्ण,
पूर्ण;

अटल पूर्णांक adv748x_पढ़ो_check(काष्ठा adv748x_state *state,
			      पूर्णांक client_page, u8 reg)
अणु
	काष्ठा i2c_client *client = state->i2c_clients[client_page];
	पूर्णांक err;
	अचिन्हित पूर्णांक val;

	err = regmap_पढ़ो(state->regmap[client_page], reg, &val);

	अगर (err) अणु
		adv_err(state, "error reading %02x, %02x\n",
				client->addr, reg);
		वापस err;
	पूर्ण

	वापस val;
पूर्ण

पूर्णांक adv748x_पढ़ो(काष्ठा adv748x_state *state, u8 page, u8 reg)
अणु
	वापस adv748x_पढ़ो_check(state, page, reg);
पूर्ण

पूर्णांक adv748x_ग_लिखो(काष्ठा adv748x_state *state, u8 page, u8 reg, u8 value)
अणु
	वापस regmap_ग_लिखो(state->regmap[page], reg, value);
पूर्ण

अटल पूर्णांक adv748x_ग_लिखो_check(काष्ठा adv748x_state *state, u8 page, u8 reg,
			       u8 value, पूर्णांक *error)
अणु
	अगर (*error)
		वापस *error;

	*error = adv748x_ग_लिखो(state, page, reg, value);
	वापस *error;
पूर्ण

/* adv748x_ग_लिखो_block(): Write raw data with a maximum of I2C_SMBUS_BLOCK_MAX
 * size to one or more रेजिस्टरs.
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक adv748x_ग_लिखो_block(काष्ठा adv748x_state *state, पूर्णांक client_page,
			अचिन्हित पूर्णांक init_reg, स्थिर व्योम *val,
			माप_प्रकार val_len)
अणु
	काष्ठा regmap *regmap = state->regmap[client_page];

	अगर (val_len > I2C_SMBUS_BLOCK_MAX)
		val_len = I2C_SMBUS_BLOCK_MAX;

	वापस regmap_raw_ग_लिखो(regmap, init_reg, val, val_len);
पूर्ण

अटल पूर्णांक adv748x_set_slave_addresses(काष्ठा adv748x_state *state)
अणु
	काष्ठा i2c_client *client;
	अचिन्हित पूर्णांक i;
	u8 io_reg;

	क्रम (i = ADV748X_PAGE_DPLL; i < ADV748X_PAGE_MAX; ++i) अणु
		io_reg = ADV748X_IO_SLAVE_ADDR_BASE + i;
		client = state->i2c_clients[i];

		io_ग_लिखो(state, io_reg, client->addr << 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adv748x_unरेजिस्टर_clients(काष्ठा adv748x_state *state)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 1; i < ARRAY_SIZE(state->i2c_clients); ++i)
		i2c_unरेजिस्टर_device(state->i2c_clients[i]);
पूर्ण

अटल पूर्णांक adv748x_initialise_clients(काष्ठा adv748x_state *state)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = ADV748X_PAGE_DPLL; i < ADV748X_PAGE_MAX; ++i) अणु
		state->i2c_clients[i] = i2c_new_ancillary_device(
				state->client,
				adv748x_शेष_addresses[i].name,
				adv748x_शेष_addresses[i].शेष_addr);

		अगर (IS_ERR(state->i2c_clients[i])) अणु
			adv_err(state, "failed to create i2c client %u\n", i);
			वापस PTR_ERR(state->i2c_clients[i]);
		पूर्ण

		ret = adv748x_configure_regmap(state, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * काष्ठा adv748x_reg_value - Register ग_लिखो inकाष्ठाion
 * @page:		Regmap page identअगरier
 * @reg:		I2C रेजिस्टर
 * @value:		value to ग_लिखो to @page at @reg
 */
काष्ठा adv748x_reg_value अणु
	u8 page;
	u8 reg;
	u8 value;
पूर्ण;

अटल पूर्णांक adv748x_ग_लिखो_regs(काष्ठा adv748x_state *state,
			      स्थिर काष्ठा adv748x_reg_value *regs)
अणु
	पूर्णांक ret;

	क्रम (; regs->page != ADV748X_PAGE_EOR; regs++) अणु
		ret = adv748x_ग_लिखो(state, regs->page, regs->reg, regs->value);
		अगर (ret < 0) अणु
			adv_err(state, "Error regs page: 0x%02x reg: 0x%02x\n",
				regs->page, regs->reg);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * TXA and TXB
 */

अटल पूर्णांक adv748x_घातer_up_tx(काष्ठा adv748x_csi2 *tx)
अणु
	काष्ठा adv748x_state *state = tx->state;
	u8 page = is_txa(tx) ? ADV748X_PAGE_TXA : ADV748X_PAGE_TXB;
	पूर्णांक ret = 0;

	/* Enable n-lane MIPI */
	adv748x_ग_लिखो_check(state, page, 0x00, 0x80 | tx->active_lanes, &ret);

	/* Set Auto DPHY Timing */
	adv748x_ग_लिखो_check(state, page, 0x00, 0xa0 | tx->active_lanes, &ret);

	/* ADI Required Write */
	अगर (tx->src == &state->hdmi.sd) अणु
		adv748x_ग_लिखो_check(state, page, 0xdb, 0x10, &ret);
		adv748x_ग_लिखो_check(state, page, 0xd6, 0x07, &ret);
	पूर्ण अन्यथा अणु
		adv748x_ग_लिखो_check(state, page, 0xd2, 0x40, &ret);
	पूर्ण

	adv748x_ग_लिखो_check(state, page, 0xc4, 0x0a, &ret);
	adv748x_ग_लिखो_check(state, page, 0x71, 0x33, &ret);
	adv748x_ग_लिखो_check(state, page, 0x72, 0x11, &ret);

	/* i2c_dphy_pwdn - 1'b0 */
	adv748x_ग_लिखो_check(state, page, 0xf0, 0x00, &ret);

	/* ADI Required Writes*/
	adv748x_ग_लिखो_check(state, page, 0x31, 0x82, &ret);
	adv748x_ग_लिखो_check(state, page, 0x1e, 0x40, &ret);

	/* i2c_mipi_pll_en - 1'b1 */
	adv748x_ग_लिखो_check(state, page, 0xda, 0x01, &ret);
	usleep_range(2000, 2500);

	/* Power-up CSI-TX */
	adv748x_ग_लिखो_check(state, page, 0x00, 0x20 | tx->active_lanes, &ret);
	usleep_range(1000, 1500);

	/* ADI Required Writes */
	adv748x_ग_लिखो_check(state, page, 0xc1, 0x2b, &ret);
	usleep_range(1000, 1500);
	adv748x_ग_लिखो_check(state, page, 0x31, 0x80, &ret);

	वापस ret;
पूर्ण

अटल पूर्णांक adv748x_घातer_करोwn_tx(काष्ठा adv748x_csi2 *tx)
अणु
	काष्ठा adv748x_state *state = tx->state;
	u8 page = is_txa(tx) ? ADV748X_PAGE_TXA : ADV748X_PAGE_TXB;
	पूर्णांक ret = 0;

	/* ADI Required Writes */
	adv748x_ग_लिखो_check(state, page, 0x31, 0x82, &ret);
	adv748x_ग_लिखो_check(state, page, 0x1e, 0x00, &ret);

	/* Enable n-lane MIPI */
	adv748x_ग_लिखो_check(state, page, 0x00, 0x80 | tx->active_lanes, &ret);

	/* i2c_mipi_pll_en - 1'b1 */
	adv748x_ग_लिखो_check(state, page, 0xda, 0x01, &ret);

	/* ADI Required Write */
	adv748x_ग_लिखो_check(state, page, 0xc1, 0x3b, &ret);

	वापस ret;
पूर्ण

पूर्णांक adv748x_tx_घातer(काष्ठा adv748x_csi2 *tx, bool on)
अणु
	पूर्णांक val;

	अगर (!is_tx_enabled(tx))
		वापस 0;

	val = tx_पढ़ो(tx, ADV748X_CSI_FS_AS_LS);
	अगर (val < 0)
		वापस val;

	/*
	 * This test against BIT(6) is not करोcumented by the datasheet, but was
	 * specअगरied in the करोwnstream driver.
	 * Track with a WARN_ONCE to determine अगर it is ever set by HW.
	 */
	WARN_ONCE((on && val & ADV748X_CSI_FS_AS_LS_UNKNOWN),
			"Enabling with unknown bit set");

	वापस on ? adv748x_घातer_up_tx(tx) : adv748x_घातer_करोwn_tx(tx);
पूर्ण

/* -----------------------------------------------------------------------------
 * Media Operations
 */
अटल पूर्णांक adv748x_link_setup(काष्ठा media_entity *entity,
			      स्थिर काष्ठा media_pad *local,
			      स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *rsd = media_entity_to_v4l2_subdev(remote->entity);
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा adv748x_state *state = v4l2_get_subdevdata(sd);
	काष्ठा adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	bool enable = flags & MEDIA_LNK_FL_ENABLED;
	u8 io10_mask = ADV748X_IO_10_CSI1_EN |
		       ADV748X_IO_10_CSI4_EN |
		       ADV748X_IO_10_CSI4_IN_SEL_AFE;
	u8 io10 = 0;

	/* Refuse to enable multiple links to the same TX at the same समय. */
	अगर (enable && tx->src)
		वापस -EINVAL;

	/* Set or clear the source (HDMI or AFE) and the current TX. */
	अगर (rsd == &state->afe.sd)
		state->afe.tx = enable ? tx : शून्य;
	अन्यथा
		state->hdmi.tx = enable ? tx : शून्य;

	tx->src = enable ? rsd : शून्य;

	अगर (state->afe.tx) अणु
		/* AFE Requires TXA enabled, even when output to TXB */
		io10 |= ADV748X_IO_10_CSI4_EN;
		अगर (is_txa(tx)) अणु
			/*
			 * Output from the SD-core (480i and 576i) from the TXA
			 * पूर्णांकerface requires reducing the number of enabled
			 * data lanes in order to guarantee a valid link
			 * frequency.
			 */
			tx->active_lanes = min(tx->num_lanes, 2U);
			io10 |= ADV748X_IO_10_CSI4_IN_SEL_AFE;
		पूर्ण अन्यथा अणु
			/* TXB has a single data lane, no need to adjust. */
			io10 |= ADV748X_IO_10_CSI1_EN;
		पूर्ण
	पूर्ण

	अगर (state->hdmi.tx) अणु
		/*
		 * Restore the number of active lanes, in हाल we have gone
		 * through an AFE->TXA streaming sessions.
		 */
		tx->active_lanes = tx->num_lanes;
		io10 |= ADV748X_IO_10_CSI4_EN;
	पूर्ण

	वापस io_clrset(state, ADV748X_IO_10, io10_mask, io10);
पूर्ण

अटल स्थिर काष्ठा media_entity_operations adv748x_tx_media_ops = अणु
	.link_setup	= adv748x_link_setup,
	.link_validate	= v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations adv748x_media_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/* -----------------------------------------------------------------------------
 * HW setup
 */

/* Initialize CP Core with RGB888 क्रमmat. */
अटल स्थिर काष्ठा adv748x_reg_value adv748x_init_hdmi[] = अणु
	/* Disable chip घातerकरोwn & Enable HDMI Rx block */
	अणुADV748X_PAGE_IO, 0x00, 0x40पूर्ण,

	अणुADV748X_PAGE_REPEATER, 0x40, 0x83पूर्ण, /* Enable HDCP 1.1 */

	अणुADV748X_PAGE_HDMI, 0x00, 0x08पूर्ण,/* Foreground Channel = A */
	अणुADV748X_PAGE_HDMI, 0x98, 0xffपूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x99, 0xa3पूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x9a, 0x00पूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x9b, 0x0aपूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x9d, 0x40पूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0xcb, 0x09पूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x3d, 0x10पूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x3e, 0x7bपूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x3f, 0x5eपूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x4e, 0xfeपूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x4f, 0x18पूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x57, 0xa3पूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x58, 0x04पूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0x85, 0x10पूर्ण,/* ADI Required Write */

	अणुADV748X_PAGE_HDMI, 0x83, 0x00पूर्ण,/* Enable All Terminations */
	अणुADV748X_PAGE_HDMI, 0xa3, 0x01पूर्ण,/* ADI Required Write */
	अणुADV748X_PAGE_HDMI, 0xbe, 0x00पूर्ण,/* ADI Required Write */

	अणुADV748X_PAGE_HDMI, 0x6c, 0x01पूर्ण,/* HPA Manual Enable */
	अणुADV748X_PAGE_HDMI, 0xf8, 0x01पूर्ण,/* HPA Asserted */
	अणुADV748X_PAGE_HDMI, 0x0f, 0x00पूर्ण,/* Audio Mute Speed Set to Fastest */
	/* (Smallest Step Size) */

	अणुADV748X_PAGE_IO, 0x04, 0x02पूर्ण,	/* RGB Out of CP */
	अणुADV748X_PAGE_IO, 0x12, 0xf0पूर्ण,	/* CSC Depends on ip Packets, SDR 444 */
	अणुADV748X_PAGE_IO, 0x17, 0x80पूर्ण,	/* Luma & Chroma can reach 254d */
	अणुADV748X_PAGE_IO, 0x03, 0x86पूर्ण,	/* CP-Insert_AV_Code */

	अणुADV748X_PAGE_CP, 0x7c, 0x00पूर्ण,	/* ADI Required Write */

	अणुADV748X_PAGE_IO, 0x0c, 0xe0पूर्ण,	/* Enable LLC_DLL & Double LLC Timing */
	अणुADV748X_PAGE_IO, 0x0e, 0xddपूर्ण,	/* LLC/PIX/SPI PINS TRISTATED AUD */

	अणुADV748X_PAGE_EOR, 0xff, 0xffपूर्ण	/* End of रेजिस्टर table */
पूर्ण;

/* Initialize AFE core with YUV8 क्रमmat. */
अटल स्थिर काष्ठा adv748x_reg_value adv748x_init_afe[] = अणु
	अणुADV748X_PAGE_IO, 0x00, 0x30पूर्ण,	/* Disable chip घातerकरोwn Rx */
	अणुADV748X_PAGE_IO, 0xf2, 0x01पूर्ण,	/* Enable I2C Read Auto-Increment */

	अणुADV748X_PAGE_IO, 0x0e, 0xffपूर्ण,	/* LLC/PIX/AUD/SPI PINS TRISTATED */

	अणुADV748X_PAGE_SDP, 0x0f, 0x00पूर्ण,	/* Exit Power Down Mode */
	अणुADV748X_PAGE_SDP, 0x52, 0xcdपूर्ण,	/* ADI Required Write */

	अणुADV748X_PAGE_SDP, 0x0e, 0x80पूर्ण,	/* ADI Required Write */
	अणुADV748X_PAGE_SDP, 0x9c, 0x00पूर्ण,	/* ADI Required Write */
	अणुADV748X_PAGE_SDP, 0x9c, 0xffपूर्ण,	/* ADI Required Write */
	अणुADV748X_PAGE_SDP, 0x0e, 0x00पूर्ण,	/* ADI Required Write */

	/* ADI recommended ग_लिखोs क्रम improved video quality */
	अणुADV748X_PAGE_SDP, 0x80, 0x51पूर्ण,	/* ADI Required Write */
	अणुADV748X_PAGE_SDP, 0x81, 0x51पूर्ण,	/* ADI Required Write */
	अणुADV748X_PAGE_SDP, 0x82, 0x68पूर्ण,	/* ADI Required Write */

	अणुADV748X_PAGE_SDP, 0x03, 0x42पूर्ण,	/* Tri-S Output , PwrDwn 656 pads */
	अणुADV748X_PAGE_SDP, 0x04, 0xb5पूर्ण,	/* ITU-R BT.656-4 compatible */
	अणुADV748X_PAGE_SDP, 0x13, 0x00पूर्ण,	/* ADI Required Write */

	अणुADV748X_PAGE_SDP, 0x17, 0x41पूर्ण,	/* Select SH1 */
	अणुADV748X_PAGE_SDP, 0x31, 0x12पूर्ण,	/* ADI Required Write */
	अणुADV748X_PAGE_SDP, 0xe6, 0x4fपूर्ण,  /* V bit end pos manually in NTSC */

	अणुADV748X_PAGE_EOR, 0xff, 0xffपूर्ण	/* End of रेजिस्टर table */
पूर्ण;

अटल पूर्णांक adv748x_sw_reset(काष्ठा adv748x_state *state)
अणु
	पूर्णांक ret;

	ret = io_ग_लिखो(state, ADV748X_IO_REG_FF, ADV748X_IO_REG_FF_MAIN_RESET);
	अगर (ret)
		वापस ret;

	usleep_range(5000, 6000);

	/* Disable CEC Wakeup from घातer-करोwn mode */
	ret = io_clrset(state, ADV748X_IO_REG_01, ADV748X_IO_REG_01_PWRDN_MASK,
			ADV748X_IO_REG_01_PWRDNB);
	अगर (ret)
		वापस ret;

	/* Enable I2C Read Auto-Increment क्रम consecutive पढ़ोs */
	वापस io_ग_लिखो(state, ADV748X_IO_REG_F2,
			ADV748X_IO_REG_F2_READ_AUTO_INC);
पूर्ण

अटल पूर्णांक adv748x_reset(काष्ठा adv748x_state *state)
अणु
	पूर्णांक ret;
	u8 regval = 0;

	ret = adv748x_sw_reset(state);
	अगर (ret < 0)
		वापस ret;

	ret = adv748x_set_slave_addresses(state);
	अगर (ret < 0)
		वापस ret;

	/* Initialize CP and AFE cores. */
	ret = adv748x_ग_लिखो_regs(state, adv748x_init_hdmi);
	अगर (ret)
		वापस ret;

	ret = adv748x_ग_लिखो_regs(state, adv748x_init_afe);
	अगर (ret)
		वापस ret;

	adv748x_afe_s_input(&state->afe, state->afe.input);

	adv_dbg(state, "AFE Default input set to %d\n", state->afe.input);

	/* Reset TXA and TXB */
	adv748x_tx_घातer(&state->txa, 1);
	adv748x_tx_घातer(&state->txa, 0);
	adv748x_tx_घातer(&state->txb, 1);
	adv748x_tx_घातer(&state->txb, 0);

	/* Disable chip घातerकरोwn & Enable HDMI Rx block */
	io_ग_लिखो(state, ADV748X_IO_PD, ADV748X_IO_PD_RX_EN);

	/* Conditionally enable TXa and TXb. */
	अगर (is_tx_enabled(&state->txa)) अणु
		regval |= ADV748X_IO_10_CSI4_EN;
		adv748x_csi2_set_भव_channel(&state->txa, 0);
	पूर्ण
	अगर (is_tx_enabled(&state->txb)) अणु
		regval |= ADV748X_IO_10_CSI1_EN;
		adv748x_csi2_set_भव_channel(&state->txb, 0);
	पूर्ण
	io_ग_लिखो(state, ADV748X_IO_10, regval);

	/* Use vid_std and v_freq as मुक्तrun resolution क्रम CP */
	cp_clrset(state, ADV748X_CP_CLMP_POS, ADV748X_CP_CLMP_POS_DIS_AUTO,
					      ADV748X_CP_CLMP_POS_DIS_AUTO);

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_identअगरy_chip(काष्ठा adv748x_state *state)
अणु
	पूर्णांक msb, lsb;

	lsb = io_पढ़ो(state, ADV748X_IO_CHIP_REV_ID_1);
	msb = io_पढ़ो(state, ADV748X_IO_CHIP_REV_ID_2);

	अगर (lsb < 0 || msb < 0) अणु
		adv_err(state, "Failed to read chip revision\n");
		वापस -EIO;
	पूर्ण

	adv_info(state, "chip found @ 0x%02x revision %02x%02x\n",
		 state->client->addr << 1, lsb, msb);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Suspend / Resume
 */

अटल पूर्णांक __maybe_unused adv748x_resume_early(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा adv748x_state *state = i2c_get_clientdata(client);

	वापस adv748x_reset(state);
पूर्ण

/* -----------------------------------------------------------------------------
 * i2c driver
 */

व्योम adv748x_subdev_init(काष्ठा v4l2_subdev *sd, काष्ठा adv748x_state *state,
			 स्थिर काष्ठा v4l2_subdev_ops *ops, u32 function,
			 स्थिर अक्षर *ident)
अणु
	v4l2_subdev_init(sd, ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	/* the owner is the same as the i2c_client's driver owner */
	sd->owner = state->dev->driver->owner;
	sd->dev = state->dev;

	v4l2_set_subdevdata(sd, state);

	/* initialize name */
	snम_लिखो(sd->name, माप(sd->name), "%s %d-%04x %s",
		state->dev->driver->name,
		i2c_adapter_id(state->client->adapter),
		state->client->addr, ident);

	sd->entity.function = function;
	sd->entity.ops = is_tx(adv748x_sd_to_csi2(sd)) ?
			 &adv748x_tx_media_ops : &adv748x_media_ops;
पूर्ण

अटल पूर्णांक adv748x_parse_csi2_lanes(काष्ठा adv748x_state *state,
				    अचिन्हित पूर्णांक port,
				    काष्ठा device_node *ep)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु .bus_type = V4L2_MBUS_CSI2_DPHY पूर्ण;
	अचिन्हित पूर्णांक num_lanes;
	पूर्णांक ret;

	अगर (port != ADV748X_PORT_TXA && port != ADV748X_PORT_TXB)
		वापस 0;

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(ep), &vep);
	अगर (ret)
		वापस ret;

	num_lanes = vep.bus.mipi_csi2.num_data_lanes;

	अगर (vep.base.port == ADV748X_PORT_TXA) अणु
		अगर (num_lanes != 1 && num_lanes != 2 && num_lanes != 4) अणु
			adv_err(state, "TXA: Invalid number (%u) of lanes\n",
				num_lanes);
			वापस -EINVAL;
		पूर्ण

		state->txa.num_lanes = num_lanes;
		state->txa.active_lanes = num_lanes;
		adv_dbg(state, "TXA: using %u lanes\n", state->txa.num_lanes);
	पूर्ण

	अगर (vep.base.port == ADV748X_PORT_TXB) अणु
		अगर (num_lanes != 1) अणु
			adv_err(state, "TXB: Invalid number (%u) of lanes\n",
				num_lanes);
			वापस -EINVAL;
		पूर्ण

		state->txb.num_lanes = num_lanes;
		state->txb.active_lanes = num_lanes;
		adv_dbg(state, "TXB: using %u lanes\n", state->txb.num_lanes);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_parse_dt(काष्ठा adv748x_state *state)
अणु
	काष्ठा device_node *ep_np = शून्य;
	काष्ठा of_endpoपूर्णांक ep;
	bool out_found = false;
	bool in_found = false;
	पूर्णांक ret;

	क्रम_each_endpoपूर्णांक_of_node(state->dev->of_node, ep_np) अणु
		of_graph_parse_endpoपूर्णांक(ep_np, &ep);
		adv_info(state, "Endpoint %pOF on port %d", ep.local_node,
			 ep.port);

		अगर (ep.port >= ADV748X_PORT_MAX) अणु
			adv_err(state, "Invalid endpoint %pOF on port %d",
				ep.local_node, ep.port);

			जारी;
		पूर्ण

		अगर (state->endpoपूर्णांकs[ep.port]) अणु
			adv_err(state,
				"Multiple port endpoints are not supported");
			जारी;
		पूर्ण

		of_node_get(ep_np);
		state->endpoपूर्णांकs[ep.port] = ep_np;

		/*
		 * At least one input endpoपूर्णांक and one output endpoपूर्णांक shall
		 * be defined.
		 */
		अगर (ep.port < ADV748X_PORT_TXA)
			in_found = true;
		अन्यथा
			out_found = true;

		/* Store number of CSI-2 lanes used क्रम TXA and TXB. */
		ret = adv748x_parse_csi2_lanes(state, ep.port, ep_np);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस in_found && out_found ? 0 : -ENODEV;
पूर्ण

अटल व्योम adv748x_dt_cleanup(काष्ठा adv748x_state *state)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ADV748X_PORT_MAX; i++)
		of_node_put(state->endpoपूर्णांकs[i]);
पूर्ण

अटल पूर्णांक adv748x_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा adv748x_state *state;
	पूर्णांक ret;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	mutex_init(&state->mutex);

	state->dev = &client->dev;
	state->client = client;
	state->i2c_clients[ADV748X_PAGE_IO] = client;
	i2c_set_clientdata(client, state);

	/*
	 * We can not use container_of to get back to the state with two TXs;
	 * Initialize the TXs's fields unconditionally on the endpoपूर्णांक
	 * presence to access them later.
	 */
	state->txa.state = state->txb.state = state;
	state->txa.page = ADV748X_PAGE_TXA;
	state->txb.page = ADV748X_PAGE_TXB;
	state->txa.port = ADV748X_PORT_TXA;
	state->txb.port = ADV748X_PORT_TXB;

	/* Discover and process ports declared by the Device tree endpoपूर्णांकs */
	ret = adv748x_parse_dt(state);
	अगर (ret) अणु
		adv_err(state, "Failed to parse device tree");
		जाओ err_मुक्त_mutex;
	पूर्ण

	/* Configure IO Regmap region */
	ret = adv748x_configure_regmap(state, ADV748X_PAGE_IO);
	अगर (ret) अणु
		adv_err(state, "Error configuring IO regmap region");
		जाओ err_cleanup_dt;
	पूर्ण

	ret = adv748x_identअगरy_chip(state);
	अगर (ret) अणु
		adv_err(state, "Failed to identify chip");
		जाओ err_cleanup_dt;
	पूर्ण

	/* Configure reमुख्यing pages as I2C clients with regmap access */
	ret = adv748x_initialise_clients(state);
	अगर (ret) अणु
		adv_err(state, "Failed to setup client regmap pages");
		जाओ err_cleanup_clients;
	पूर्ण

	/* SW reset ADV748X to its शेष values */
	ret = adv748x_reset(state);
	अगर (ret) अणु
		adv_err(state, "Failed to reset hardware");
		जाओ err_cleanup_clients;
	पूर्ण

	/* Initialise HDMI */
	ret = adv748x_hdmi_init(&state->hdmi);
	अगर (ret) अणु
		adv_err(state, "Failed to probe HDMI");
		जाओ err_cleanup_clients;
	पूर्ण

	/* Initialise AFE */
	ret = adv748x_afe_init(&state->afe);
	अगर (ret) अणु
		adv_err(state, "Failed to probe AFE");
		जाओ err_cleanup_hdmi;
	पूर्ण

	/* Initialise TXA */
	ret = adv748x_csi2_init(state, &state->txa);
	अगर (ret) अणु
		adv_err(state, "Failed to probe TXA");
		जाओ err_cleanup_afe;
	पूर्ण

	/* Initialise TXB */
	ret = adv748x_csi2_init(state, &state->txb);
	अगर (ret) अणु
		adv_err(state, "Failed to probe TXB");
		जाओ err_cleanup_txa;
	पूर्ण

	वापस 0;

err_cleanup_txa:
	adv748x_csi2_cleanup(&state->txa);
err_cleanup_afe:
	adv748x_afe_cleanup(&state->afe);
err_cleanup_hdmi:
	adv748x_hdmi_cleanup(&state->hdmi);
err_cleanup_clients:
	adv748x_unरेजिस्टर_clients(state);
err_cleanup_dt:
	adv748x_dt_cleanup(state);
err_मुक्त_mutex:
	mutex_destroy(&state->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक adv748x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा adv748x_state *state = i2c_get_clientdata(client);

	adv748x_afe_cleanup(&state->afe);
	adv748x_hdmi_cleanup(&state->hdmi);

	adv748x_csi2_cleanup(&state->txa);
	adv748x_csi2_cleanup(&state->txb);

	adv748x_unरेजिस्टर_clients(state);
	adv748x_dt_cleanup(state);
	mutex_destroy(&state->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id adv748x_of_table[] = अणु
	अणु .compatible = "adi,adv7481", पूर्ण,
	अणु .compatible = "adi,adv7482", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adv748x_of_table);

अटल स्थिर काष्ठा dev_pm_ops adv748x_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(शून्य, adv748x_resume_early)
पूर्ण;

अटल काष्ठा i2c_driver adv748x_driver = अणु
	.driver = अणु
		.name = "adv748x",
		.of_match_table = adv748x_of_table,
		.pm = &adv748x_pm_ops,
	पूर्ण,
	.probe_new = adv748x_probe,
	.हटाओ = adv748x_हटाओ,
पूर्ण;

module_i2c_driver(adv748x_driver);

MODULE_AUTHOR("Kieran Bingham <kieran.bingham@ideasonboard.com>");
MODULE_DESCRIPTION("ADV748X video decoder");
MODULE_LICENSE("GPL");
