<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम Analog Devices ADV748X video decoder and HDMI receiver
 *
 * Copyright (C) 2017 Renesas Electronics Corp.
 *
 * Authors:
 *	Koji Matsuoka <koji.matsuoka.xm@renesas.com>
 *	Niklas Sथघderlund <niklas.soderlund@ragnatech.se>
 *	Kieran Bingham <kieran.bingham@ideasonboard.com>
 *
 * The ADV748x range of receivers have the following configurations:
 *
 *                  Analog   HDMI  MHL  4-Lane  1-Lane
 *                    In      In         CSI     CSI
 *       ADV7480               X    X     X
 *       ADV7481      X        X    X     X       X
 *       ADV7482      X        X          X       X
 */

#समावेश <linux/i2c.h>

#अगर_अघोषित _ADV748X_H_
#घोषणा _ADV748X_H_

क्रमागत adv748x_page अणु
	ADV748X_PAGE_IO,
	ADV748X_PAGE_DPLL,
	ADV748X_PAGE_CP,
	ADV748X_PAGE_HDMI,
	ADV748X_PAGE_EDID,
	ADV748X_PAGE_REPEATER,
	ADV748X_PAGE_INFOFRAME,
	ADV748X_PAGE_CBUS,
	ADV748X_PAGE_CEC,
	ADV748X_PAGE_SDP,
	ADV748X_PAGE_TXB,
	ADV748X_PAGE_TXA,
	ADV748X_PAGE_MAX,

	/* Fake pages क्रम रेजिस्टर sequences */
	ADV748X_PAGE_EOR,		/* End Mark */
पूर्ण;

/*
 * Device tree port number definitions
 *
 * The ADV748X ports define the mapping between subdevices
 * and the device tree specअगरication
 */
क्रमागत adv748x_ports अणु
	ADV748X_PORT_AIN0 = 0,
	ADV748X_PORT_AIN1 = 1,
	ADV748X_PORT_AIN2 = 2,
	ADV748X_PORT_AIN3 = 3,
	ADV748X_PORT_AIN4 = 4,
	ADV748X_PORT_AIN5 = 5,
	ADV748X_PORT_AIN6 = 6,
	ADV748X_PORT_AIN7 = 7,
	ADV748X_PORT_HDMI = 8,
	ADV748X_PORT_TTL = 9,
	ADV748X_PORT_TXA = 10,
	ADV748X_PORT_TXB = 11,
	ADV748X_PORT_MAX = 12,
पूर्ण;

क्रमागत adv748x_csi2_pads अणु
	ADV748X_CSI2_SINK,
	ADV748X_CSI2_SOURCE,
	ADV748X_CSI2_NR_PADS,
पूर्ण;

/* CSI2 transmitters can have 2 पूर्णांकernal connections, HDMI/AFE */
#घोषणा ADV748X_CSI2_MAX_SUBDEVS 2

काष्ठा adv748x_csi2 अणु
	काष्ठा adv748x_state *state;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	अचिन्हित पूर्णांक page;
	अचिन्हित पूर्णांक port;
	अचिन्हित पूर्णांक num_lanes;
	अचिन्हित पूर्णांक active_lanes;

	काष्ठा media_pad pads[ADV748X_CSI2_NR_PADS];
	काष्ठा v4l2_ctrl_handler ctrl_hdl;
	काष्ठा v4l2_ctrl *pixel_rate;
	काष्ठा v4l2_subdev *src;
	काष्ठा v4l2_subdev sd;
पूर्ण;

#घोषणा notअगरier_to_csi2(n) container_of(n, काष्ठा adv748x_csi2, notअगरier)
#घोषणा adv748x_sd_to_csi2(sd) container_of(sd, काष्ठा adv748x_csi2, sd)

#घोषणा is_tx_enabled(_tx) ((_tx)->state->endpoपूर्णांकs[(_tx)->port] != शून्य)
#घोषणा is_txa(_tx) ((_tx) == &(_tx)->state->txa)
#घोषणा is_txb(_tx) ((_tx) == &(_tx)->state->txb)
#घोषणा is_tx(_tx) (is_txa(_tx) || is_txb(_tx))

#घोषणा is_afe_enabled(_state)					\
	((_state)->endpoपूर्णांकs[ADV748X_PORT_AIN0] != शून्य ||	\
	 (_state)->endpoपूर्णांकs[ADV748X_PORT_AIN1] != शून्य ||	\
	 (_state)->endpoपूर्णांकs[ADV748X_PORT_AIN2] != शून्य ||	\
	 (_state)->endpoपूर्णांकs[ADV748X_PORT_AIN3] != शून्य ||	\
	 (_state)->endpoपूर्णांकs[ADV748X_PORT_AIN4] != शून्य ||	\
	 (_state)->endpoपूर्णांकs[ADV748X_PORT_AIN5] != शून्य ||	\
	 (_state)->endpoपूर्णांकs[ADV748X_PORT_AIN6] != शून्य ||	\
	 (_state)->endpoपूर्णांकs[ADV748X_PORT_AIN7] != शून्य)
#घोषणा is_hdmi_enabled(_state) ((_state)->endpoपूर्णांकs[ADV748X_PORT_HDMI] != शून्य)

क्रमागत adv748x_hdmi_pads अणु
	ADV748X_HDMI_SINK,
	ADV748X_HDMI_SOURCE,
	ADV748X_HDMI_NR_PADS,
पूर्ण;

काष्ठा adv748x_hdmi अणु
	काष्ठा media_pad pads[ADV748X_HDMI_NR_PADS];
	काष्ठा v4l2_ctrl_handler ctrl_hdl;
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	काष्ठा v4l2_dv_timings timings;
	काष्ठा v4l2_fract aspect_ratio;

	काष्ठा adv748x_csi2 *tx;

	काष्ठा अणु
		u8 edid[512];
		u32 present;
		अचिन्हित पूर्णांक blocks;
	पूर्ण edid;
पूर्ण;

#घोषणा adv748x_ctrl_to_hdmi(ctrl) \
	container_of(ctrl->handler, काष्ठा adv748x_hdmi, ctrl_hdl)
#घोषणा adv748x_sd_to_hdmi(sd) container_of(sd, काष्ठा adv748x_hdmi, sd)

क्रमागत adv748x_afe_pads अणु
	ADV748X_AFE_SINK_AIN0,
	ADV748X_AFE_SINK_AIN1,
	ADV748X_AFE_SINK_AIN2,
	ADV748X_AFE_SINK_AIN3,
	ADV748X_AFE_SINK_AIN4,
	ADV748X_AFE_SINK_AIN5,
	ADV748X_AFE_SINK_AIN6,
	ADV748X_AFE_SINK_AIN7,
	ADV748X_AFE_SOURCE,
	ADV748X_AFE_NR_PADS,
पूर्ण;

काष्ठा adv748x_afe अणु
	काष्ठा media_pad pads[ADV748X_AFE_NR_PADS];
	काष्ठा v4l2_ctrl_handler ctrl_hdl;
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	काष्ठा adv748x_csi2 *tx;

	bool streaming;
	v4l2_std_id curr_norm;
	अचिन्हित पूर्णांक input;
पूर्ण;

#घोषणा adv748x_ctrl_to_afe(ctrl) \
	container_of(ctrl->handler, काष्ठा adv748x_afe, ctrl_hdl)
#घोषणा adv748x_sd_to_afe(sd) container_of(sd, काष्ठा adv748x_afe, sd)

/**
 * काष्ठा adv748x_state - State of ADV748X
 * @dev:		(OF) device
 * @client:		I2C client
 * @mutex:		protect global state
 *
 * @endpoपूर्णांकs:		parsed device node endpoपूर्णांकs क्रम each port
 *
 * @i2c_addresses:	I2C Page addresses
 * @i2c_clients:	I2C clients क्रम the page accesses
 * @regmap:		regmap configuration pages.
 *
 * @hdmi:		state of HDMI receiver context
 * @afe:		state of AFE receiver context
 * @txa:		state of TXA transmitter context
 * @txb:		state of TXB transmitter context
 */
काष्ठा adv748x_state अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	काष्ठा mutex mutex;

	काष्ठा device_node *endpoपूर्णांकs[ADV748X_PORT_MAX];

	काष्ठा i2c_client *i2c_clients[ADV748X_PAGE_MAX];
	काष्ठा regmap *regmap[ADV748X_PAGE_MAX];

	काष्ठा adv748x_hdmi hdmi;
	काष्ठा adv748x_afe afe;
	काष्ठा adv748x_csi2 txa;
	काष्ठा adv748x_csi2 txb;
पूर्ण;

#घोषणा adv748x_hdmi_to_state(h) container_of(h, काष्ठा adv748x_state, hdmi)
#घोषणा adv748x_afe_to_state(a) container_of(a, काष्ठा adv748x_state, afe)

#घोषणा adv_err(a, fmt, arg...)	dev_err(a->dev, fmt, ##arg)
#घोषणा adv_info(a, fmt, arg...) dev_info(a->dev, fmt, ##arg)
#घोषणा adv_dbg(a, fmt, arg...)	dev_dbg(a->dev, fmt, ##arg)

/* Register Mappings */

/* IO Map */
#घोषणा ADV748X_IO_PD			0x00	/* घातer करोwn controls */
#घोषणा ADV748X_IO_PD_RX_EN		BIT(6)

#घोषणा ADV748X_IO_REG_01		0x01	/* pwrdnअणु2पूर्णb, prog_xtal_freq */
#घोषणा ADV748X_IO_REG_01_PWRDN_MASK	(BIT(7) | BIT(6))
#घोषणा ADV748X_IO_REG_01_PWRDN2B	BIT(7)	/* CEC Wakeup Support */
#घोषणा ADV748X_IO_REG_01_PWRDNB	BIT(6)	/* CEC Wakeup Support */

#घोषणा ADV748X_IO_REG_04		0x04
#घोषणा ADV748X_IO_REG_04_FORCE_FR	BIT(0)	/* Force CP मुक्त-run */

#घोषणा ADV748X_IO_DATAPATH		0x03	/* datapath cntrl */
#घोषणा ADV748X_IO_DATAPATH_VFREQ_M	0x70
#घोषणा ADV748X_IO_DATAPATH_VFREQ_SHIFT	4

#घोषणा ADV748X_IO_VID_STD		0x05

#घोषणा ADV748X_IO_10			0x10	/* io_reg_10 */
#घोषणा ADV748X_IO_10_CSI4_EN		BIT(7)
#घोषणा ADV748X_IO_10_CSI1_EN		BIT(6)
#घोषणा ADV748X_IO_10_PIX_OUT_EN	BIT(5)
#घोषणा ADV748X_IO_10_CSI4_IN_SEL_AFE	BIT(3)

#घोषणा ADV748X_IO_CHIP_REV_ID_1	0xdf
#घोषणा ADV748X_IO_CHIP_REV_ID_2	0xe0

#घोषणा ADV748X_IO_REG_F2		0xf2
#घोषणा ADV748X_IO_REG_F2_READ_AUTO_INC	BIT(0)

/* For PAGE slave address offsets */
#घोषणा ADV748X_IO_SLAVE_ADDR_BASE	0xf2

/*
 * The ADV748x_Recommended_Settings_PrA_2014-08-20.pdf details both 0x80 and
 * 0xff as examples क्रम perक्रमming a software reset.
 */
#घोषणा ADV748X_IO_REG_FF		0xff
#घोषणा ADV748X_IO_REG_FF_MAIN_RESET	0xff

/* HDMI RX Map */
#घोषणा ADV748X_HDMI_LW1		0x07	/* line width_1 */
#घोषणा ADV748X_HDMI_LW1_VERT_FILTER	BIT(7)
#घोषणा ADV748X_HDMI_LW1_DE_REGEN	BIT(5)
#घोषणा ADV748X_HDMI_LW1_WIDTH_MASK	0x1fff

#घोषणा ADV748X_HDMI_F0H1		0x09	/* field0 height_1 */
#घोषणा ADV748X_HDMI_F0H1_HEIGHT_MASK	0x1fff

#घोषणा ADV748X_HDMI_F1H1		0x0b	/* field1 height_1 */
#घोषणा ADV748X_HDMI_F1H1_INTERLACED	BIT(5)

#घोषणा ADV748X_HDMI_HFRONT_PORCH	0x20	/* hsync_front_porch_1 */
#घोषणा ADV748X_HDMI_HFRONT_PORCH_MASK	0x1fff

#घोषणा ADV748X_HDMI_HSYNC_WIDTH	0x22	/* hsync_pulse_width_1 */
#घोषणा ADV748X_HDMI_HSYNC_WIDTH_MASK	0x1fff

#घोषणा ADV748X_HDMI_HBACK_PORCH	0x24	/* hsync_back_porch_1 */
#घोषणा ADV748X_HDMI_HBACK_PORCH_MASK	0x1fff

#घोषणा ADV748X_HDMI_VFRONT_PORCH	0x2a	/* field0_vs_front_porch_1 */
#घोषणा ADV748X_HDMI_VFRONT_PORCH_MASK	0x3fff

#घोषणा ADV748X_HDMI_VSYNC_WIDTH	0x2e	/* field0_vs_pulse_width_1 */
#घोषणा ADV748X_HDMI_VSYNC_WIDTH_MASK	0x3fff

#घोषणा ADV748X_HDMI_VBACK_PORCH	0x32	/* field0_vs_back_porch_1 */
#घोषणा ADV748X_HDMI_VBACK_PORCH_MASK	0x3fff

#घोषणा ADV748X_HDMI_TMDS_1		0x51	/* hdmi_reg_51 */
#घोषणा ADV748X_HDMI_TMDS_2		0x52	/* hdmi_reg_52 */

/* HDMI RX Repeater Map */
#घोषणा ADV748X_REPEATER_EDID_SZ	0x70	/* primary_edid_size */
#घोषणा ADV748X_REPEATER_EDID_SZ_SHIFT	4

#घोषणा ADV748X_REPEATER_EDID_CTL	0x74	/* hdcp edid controls */
#घोषणा ADV748X_REPEATER_EDID_CTL_EN	BIT(0)	/* man_edid_a_enable */

/* SDP Main Map */
#घोषणा ADV748X_SDP_INSEL		0x00	/* user_map_rw_reg_00 */

#घोषणा ADV748X_SDP_VID_SEL		0x02	/* user_map_rw_reg_02 */
#घोषणा ADV748X_SDP_VID_SEL_MASK	0xf0
#घोषणा ADV748X_SDP_VID_SEL_SHIFT	4

/* Contrast - Unचिन्हित*/
#घोषणा ADV748X_SDP_CON			0x08	/* user_map_rw_reg_08 */
#घोषणा ADV748X_SDP_CON_MIN		0
#घोषणा ADV748X_SDP_CON_DEF		128
#घोषणा ADV748X_SDP_CON_MAX		255

/* Brightness - Signed */
#घोषणा ADV748X_SDP_BRI			0x0a	/* user_map_rw_reg_0a */
#घोषणा ADV748X_SDP_BRI_MIN		-128
#घोषणा ADV748X_SDP_BRI_DEF		0
#घोषणा ADV748X_SDP_BRI_MAX		127

/* Hue - Signed, inverted*/
#घोषणा ADV748X_SDP_HUE			0x0b	/* user_map_rw_reg_0b */
#घोषणा ADV748X_SDP_HUE_MIN		-127
#घोषणा ADV748X_SDP_HUE_DEF		0
#घोषणा ADV748X_SDP_HUE_MAX		128

/* Test Patterns / Default Values */
#घोषणा ADV748X_SDP_DEF			0x0c	/* user_map_rw_reg_0c */
#घोषणा ADV748X_SDP_DEF_VAL_EN		BIT(0)	/* Force मुक्त run mode */
#घोषणा ADV748X_SDP_DEF_VAL_AUTO_EN	BIT(1)	/* Free run when no संकेत */

#घोषणा ADV748X_SDP_MAP_SEL		0x0e	/* user_map_rw_reg_0e */
#घोषणा ADV748X_SDP_MAP_SEL_RO_MAIN	1

/* Free run pattern select */
#घोषणा ADV748X_SDP_FRP			0x14
#घोषणा ADV748X_SDP_FRP_MASK		GENMASK(3, 1)

/* Saturation */
#घोषणा ADV748X_SDP_SD_SAT_U		0xe3	/* user_map_rw_reg_e3 */
#घोषणा ADV748X_SDP_SD_SAT_V		0xe4	/* user_map_rw_reg_e4 */
#घोषणा ADV748X_SDP_SAT_MIN		0
#घोषणा ADV748X_SDP_SAT_DEF		128
#घोषणा ADV748X_SDP_SAT_MAX		255

/* SDP RO Main Map */
#घोषणा ADV748X_SDP_RO_10		0x10
#घोषणा ADV748X_SDP_RO_10_IN_LOCK	BIT(0)

/* CP Map */
#घोषणा ADV748X_CP_PAT_GEN		0x37	/* पूर्णांक_pat_gen_1 */
#घोषणा ADV748X_CP_PAT_GEN_EN		BIT(7)

/* Contrast Control - Unचिन्हित */
#घोषणा ADV748X_CP_CON			0x3a	/* contrast_cntrl */
#घोषणा ADV748X_CP_CON_MIN		0	/* Minimum contrast */
#घोषणा ADV748X_CP_CON_DEF		128	/* Default */
#घोषणा ADV748X_CP_CON_MAX		255	/* Maximum contrast */

/* Saturation Control - Unचिन्हित */
#घोषणा ADV748X_CP_SAT			0x3b	/* saturation_cntrl */
#घोषणा ADV748X_CP_SAT_MIN		0	/* Minimum saturation */
#घोषणा ADV748X_CP_SAT_DEF		128	/* Default */
#घोषणा ADV748X_CP_SAT_MAX		255	/* Maximum saturation */

/* Brightness Control - Signed */
#घोषणा ADV748X_CP_BRI			0x3c	/* brightness_cntrl */
#घोषणा ADV748X_CP_BRI_MIN		-128	/* Luma is -512d */
#घोषणा ADV748X_CP_BRI_DEF		0	/* Luma is 0 */
#घोषणा ADV748X_CP_BRI_MAX		127	/* Luma is 508d */

/* Hue Control */
#घोषणा ADV748X_CP_HUE			0x3d	/* hue_cntrl */
#घोषणा ADV748X_CP_HUE_MIN		0	/* -90 degree */
#घोषणा ADV748X_CP_HUE_DEF		0	/* -90 degree */
#घोषणा ADV748X_CP_HUE_MAX		255	/* +90 degree */

#घोषणा ADV748X_CP_VID_ADJ		0x3e	/* vid_adj_0 */
#घोषणा ADV748X_CP_VID_ADJ_ENABLE	BIT(7)	/* Enable colour controls */

#घोषणा ADV748X_CP_DE_POS_HIGH		0x8b	/* de_pos_adj_6 */
#घोषणा ADV748X_CP_DE_POS_HIGH_SET	BIT(6)
#घोषणा ADV748X_CP_DE_POS_END_LOW	0x8c	/* de_pos_adj_7 */
#घोषणा ADV748X_CP_DE_POS_START_LOW	0x8d	/* de_pos_adj_8 */

#घोषणा ADV748X_CP_VID_ADJ_2			0x91
#घोषणा ADV748X_CP_VID_ADJ_2_INTERLACED		BIT(6)
#घोषणा ADV748X_CP_VID_ADJ_2_INTERLACED_3D	BIT(4)

#घोषणा ADV748X_CP_CLMP_POS		0xc9	/* clmp_pos_cntrl_4 */
#घोषणा ADV748X_CP_CLMP_POS_DIS_AUTO	BIT(0)	/* dis_स्वतः_param_buff */

/* CSI : TXA/TXB Maps */
#घोषणा ADV748X_CSI_VC_REF		0x0d	/* csi_tx_top_reg_0d */
#घोषणा ADV748X_CSI_VC_REF_SHIFT	6

#घोषणा ADV748X_CSI_FS_AS_LS		0x1e	/* csi_tx_top_reg_1e */
#घोषणा ADV748X_CSI_FS_AS_LS_UNKNOWN	BIT(6)	/* Unकरोcumented bit */

/* Register handling */

पूर्णांक adv748x_पढ़ो(काष्ठा adv748x_state *state, u8 addr, u8 reg);
पूर्णांक adv748x_ग_लिखो(काष्ठा adv748x_state *state, u8 page, u8 reg, u8 value);
पूर्णांक adv748x_ग_लिखो_block(काष्ठा adv748x_state *state, पूर्णांक client_page,
			अचिन्हित पूर्णांक init_reg, स्थिर व्योम *val,
			माप_प्रकार val_len);

#घोषणा io_पढ़ो(s, r) adv748x_पढ़ो(s, ADV748X_PAGE_IO, r)
#घोषणा io_ग_लिखो(s, r, v) adv748x_ग_लिखो(s, ADV748X_PAGE_IO, r, v)
#घोषणा io_clrset(s, r, m, v) io_ग_लिखो(s, r, (io_पढ़ो(s, r) & ~(m)) | (v))

#घोषणा hdmi_पढ़ो(s, r) adv748x_पढ़ो(s, ADV748X_PAGE_HDMI, r)
#घोषणा hdmi_पढ़ो16(s, r, m) (((hdmi_पढ़ो(s, r) << 8) | hdmi_पढ़ो(s, (r)+1)) & (m))
#घोषणा hdmi_ग_लिखो(s, r, v) adv748x_ग_लिखो(s, ADV748X_PAGE_HDMI, r, v)

#घोषणा repeater_पढ़ो(s, r) adv748x_पढ़ो(s, ADV748X_PAGE_REPEATER, r)
#घोषणा repeater_ग_लिखो(s, r, v) adv748x_ग_लिखो(s, ADV748X_PAGE_REPEATER, r, v)

#घोषणा sdp_पढ़ो(s, r) adv748x_पढ़ो(s, ADV748X_PAGE_SDP, r)
#घोषणा sdp_ग_लिखो(s, r, v) adv748x_ग_लिखो(s, ADV748X_PAGE_SDP, r, v)
#घोषणा sdp_clrset(s, r, m, v) sdp_ग_लिखो(s, r, (sdp_पढ़ो(s, r) & ~(m)) | (v))

#घोषणा cp_पढ़ो(s, r) adv748x_पढ़ो(s, ADV748X_PAGE_CP, r)
#घोषणा cp_ग_लिखो(s, r, v) adv748x_ग_लिखो(s, ADV748X_PAGE_CP, r, v)
#घोषणा cp_clrset(s, r, m, v) cp_ग_लिखो(s, r, (cp_पढ़ो(s, r) & ~(m)) | (v))

#घोषणा tx_पढ़ो(t, r) adv748x_पढ़ो(t->state, t->page, r)
#घोषणा tx_ग_लिखो(t, r, v) adv748x_ग_लिखो(t->state, t->page, r, v)

अटल अंतरभूत काष्ठा v4l2_subdev *adv748x_get_remote_sd(काष्ठा media_pad *pad)
अणु
	pad = media_entity_remote_pad(pad);
	अगर (!pad)
		वापस शून्य;

	वापस media_entity_to_v4l2_subdev(pad->entity);
पूर्ण

व्योम adv748x_subdev_init(काष्ठा v4l2_subdev *sd, काष्ठा adv748x_state *state,
			 स्थिर काष्ठा v4l2_subdev_ops *ops, u32 function,
			 स्थिर अक्षर *ident);

पूर्णांक adv748x_रेजिस्टर_subdevs(काष्ठा adv748x_state *state,
			     काष्ठा v4l2_device *v4l2_dev);

पूर्णांक adv748x_tx_घातer(काष्ठा adv748x_csi2 *tx, bool on);

पूर्णांक adv748x_afe_init(काष्ठा adv748x_afe *afe);
व्योम adv748x_afe_cleanup(काष्ठा adv748x_afe *afe);
पूर्णांक adv748x_afe_s_input(काष्ठा adv748x_afe *afe, अचिन्हित पूर्णांक input);

पूर्णांक adv748x_csi2_init(काष्ठा adv748x_state *state, काष्ठा adv748x_csi2 *tx);
व्योम adv748x_csi2_cleanup(काष्ठा adv748x_csi2 *tx);
पूर्णांक adv748x_csi2_set_भव_channel(काष्ठा adv748x_csi2 *tx, अचिन्हित पूर्णांक vc);
पूर्णांक adv748x_csi2_set_pixelrate(काष्ठा v4l2_subdev *sd, s64 rate);

पूर्णांक adv748x_hdmi_init(काष्ठा adv748x_hdmi *hdmi);
व्योम adv748x_hdmi_cleanup(काष्ठा adv748x_hdmi *hdmi);

#पूर्ण_अगर /* _ADV748X_H_ */
