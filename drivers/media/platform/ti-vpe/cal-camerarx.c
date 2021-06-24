<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI Camera Access Layer (CAL) - CAMERARX
 *
 * Copyright (c) 2015-2020 Texas Instruments Inc.
 *
 * Authors:
 *	Benoit Parrot <bparrot@ti.com>
 *	Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "cal.h"
#समावेश "cal_regs.h"

/* ------------------------------------------------------------------
 *	I/O Register Accessors
 * ------------------------------------------------------------------
 */

अटल अंतरभूत u32 camerarx_पढ़ो(काष्ठा cal_camerarx *phy, u32 offset)
अणु
	वापस ioपढ़ो32(phy->base + offset);
पूर्ण

अटल अंतरभूत व्योम camerarx_ग_लिखो(काष्ठा cal_camerarx *phy, u32 offset, u32 val)
अणु
	ioग_लिखो32(val, phy->base + offset);
पूर्ण

/* ------------------------------------------------------------------
 *	CAMERARX Management
 * ------------------------------------------------------------------
 */

अटल s64 cal_camerarx_get_बाह्यal_rate(काष्ठा cal_camerarx *phy)
अणु
	काष्ठा v4l2_ctrl *ctrl;
	s64 rate;

	ctrl = v4l2_ctrl_find(phy->sensor->ctrl_handler, V4L2_CID_PIXEL_RATE);
	अगर (!ctrl) अणु
		phy_err(phy, "no pixel rate control in subdev: %s\n",
			phy->sensor->name);
		वापस -EPIPE;
	पूर्ण

	rate = v4l2_ctrl_g_ctrl_पूर्णांक64(ctrl);
	phy_dbg(3, phy, "sensor Pixel Rate: %llu\n", rate);

	वापस rate;
पूर्ण

अटल व्योम cal_camerarx_lane_config(काष्ठा cal_camerarx *phy)
अणु
	u32 val = cal_पढ़ो(phy->cal, CAL_CSI2_COMPLEXIO_CFG(phy->instance));
	u32 lane_mask = CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK;
	u32 polarity_mask = CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_MASK;
	काष्ठा v4l2_fwnode_bus_mipi_csi2 *mipi_csi2 =
		&phy->endpoपूर्णांक.bus.mipi_csi2;
	पूर्णांक lane;

	cal_set_field(&val, mipi_csi2->घड़ी_lane + 1, lane_mask);
	cal_set_field(&val, mipi_csi2->lane_polarities[0], polarity_mask);
	क्रम (lane = 0; lane < mipi_csi2->num_data_lanes; lane++) अणु
		/*
		 * Every lane are one nibble apart starting with the
		 * घड़ी followed by the data lanes so shअगरt masks by 4.
		 */
		lane_mask <<= 4;
		polarity_mask <<= 4;
		cal_set_field(&val, mipi_csi2->data_lanes[lane] + 1, lane_mask);
		cal_set_field(&val, mipi_csi2->lane_polarities[lane + 1],
			      polarity_mask);
	पूर्ण

	cal_ग_लिखो(phy->cal, CAL_CSI2_COMPLEXIO_CFG(phy->instance), val);
	phy_dbg(3, phy, "CAL_CSI2_COMPLEXIO_CFG(%d) = 0x%08x\n",
		phy->instance, val);
पूर्ण

अटल व्योम cal_camerarx_enable(काष्ठा cal_camerarx *phy)
अणु
	u32 num_lanes = phy->cal->data->camerarx[phy->instance].num_lanes;

	regmap_field_ग_लिखो(phy->fields[F_CAMMODE], 0);
	/* Always enable all lanes at the phy control level */
	regmap_field_ग_लिखो(phy->fields[F_LANEENABLE], (1 << num_lanes) - 1);
	/* F_CSI_MODE is not present on every architecture */
	अगर (phy->fields[F_CSI_MODE])
		regmap_field_ग_लिखो(phy->fields[F_CSI_MODE], 1);
	regmap_field_ग_लिखो(phy->fields[F_CTRLCLKEN], 1);
पूर्ण

व्योम cal_camerarx_disable(काष्ठा cal_camerarx *phy)
अणु
	regmap_field_ग_लिखो(phy->fields[F_CTRLCLKEN], 0);
पूर्ण

/*
 * TCLK values are OK at their reset values
 */
#घोषणा TCLK_TERM	0
#घोषणा TCLK_MISS	1
#घोषणा TCLK_SETTLE	14

अटल व्योम cal_camerarx_config(काष्ठा cal_camerarx *phy, s64 बाह्यal_rate)
अणु
	अचिन्हित पूर्णांक reg0, reg1;
	अचिन्हित पूर्णांक ths_term, ths_settle;
	अचिन्हित पूर्णांक csi2_ddrclk_khz;
	काष्ठा v4l2_fwnode_bus_mipi_csi2 *mipi_csi2 =
			&phy->endpoपूर्णांक.bus.mipi_csi2;
	u32 num_lanes = mipi_csi2->num_data_lanes;

	/* DPHY timing configuration */

	/*
	 * CSI-2 is DDR and we only count used lanes.
	 *
	 * csi2_ddrclk_khz = बाह्यal_rate / 1000
	 *		   / (2 * num_lanes) * phy->fmtinfo->bpp;
	 */
	csi2_ddrclk_khz = भाग_s64(बाह्यal_rate * phy->fmtinfo->bpp,
				  2 * num_lanes * 1000);

	phy_dbg(1, phy, "csi2_ddrclk_khz: %d\n", csi2_ddrclk_khz);

	/* THS_TERM: Programmed value = न्यूनमान(20 ns/DDRClk period) */
	ths_term = 20 * csi2_ddrclk_khz / 1000000;
	phy_dbg(1, phy, "ths_term: %d (0x%02x)\n", ths_term, ths_term);

	/* THS_SETTLE: Programmed value = न्यूनमान(105 ns/DDRClk period) + 4 */
	ths_settle = (105 * csi2_ddrclk_khz / 1000000) + 4;
	phy_dbg(1, phy, "ths_settle: %d (0x%02x)\n", ths_settle, ths_settle);

	reg0 = camerarx_पढ़ो(phy, CAL_CSI2_PHY_REG0);
	cal_set_field(&reg0, CAL_CSI2_PHY_REG0_HSCLOCKCONFIG_DISABLE,
		      CAL_CSI2_PHY_REG0_HSCLOCKCONFIG_MASK);
	cal_set_field(&reg0, ths_term, CAL_CSI2_PHY_REG0_THS_TERM_MASK);
	cal_set_field(&reg0, ths_settle, CAL_CSI2_PHY_REG0_THS_SETTLE_MASK);

	phy_dbg(1, phy, "CSI2_%d_REG0 = 0x%08x\n", phy->instance, reg0);
	camerarx_ग_लिखो(phy, CAL_CSI2_PHY_REG0, reg0);

	reg1 = camerarx_पढ़ो(phy, CAL_CSI2_PHY_REG1);
	cal_set_field(&reg1, TCLK_TERM, CAL_CSI2_PHY_REG1_TCLK_TERM_MASK);
	cal_set_field(&reg1, 0xb8, CAL_CSI2_PHY_REG1_DPHY_HS_SYNC_PATTERN_MASK);
	cal_set_field(&reg1, TCLK_MISS,
		      CAL_CSI2_PHY_REG1_CTRLCLK_DIV_FACTOR_MASK);
	cal_set_field(&reg1, TCLK_SETTLE, CAL_CSI2_PHY_REG1_TCLK_SETTLE_MASK);

	phy_dbg(1, phy, "CSI2_%d_REG1 = 0x%08x\n", phy->instance, reg1);
	camerarx_ग_लिखो(phy, CAL_CSI2_PHY_REG1, reg1);
पूर्ण

अटल व्योम cal_camerarx_घातer(काष्ठा cal_camerarx *phy, bool enable)
अणु
	u32 target_state;
	अचिन्हित पूर्णांक i;

	target_state = enable ? CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_STATE_ON :
		       CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_STATE_OFF;

	cal_ग_लिखो_field(phy->cal, CAL_CSI2_COMPLEXIO_CFG(phy->instance),
			target_state, CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_MASK);

	क्रम (i = 0; i < 10; i++) अणु
		u32 current_state;

		current_state = cal_पढ़ो_field(phy->cal,
					       CAL_CSI2_COMPLEXIO_CFG(phy->instance),
					       CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_MASK);

		अगर (current_state == target_state)
			अवरोध;

		usleep_range(1000, 1100);
	पूर्ण

	अगर (i == 10)
		phy_err(phy, "Failed to power %s complexio\n",
			enable ? "up" : "down");
पूर्ण

अटल व्योम cal_camerarx_रुको_reset(काष्ठा cal_camerarx *phy)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(750);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (cal_पढ़ो_field(phy->cal,
				   CAL_CSI2_COMPLEXIO_CFG(phy->instance),
				   CAL_CSI2_COMPLEXIO_CFG_RESET_DONE_MASK) ==
		    CAL_CSI2_COMPLEXIO_CFG_RESET_DONE_RESETCOMPLETED)
			अवरोध;
		usleep_range(500, 5000);
	पूर्ण

	अगर (cal_पढ़ो_field(phy->cal, CAL_CSI2_COMPLEXIO_CFG(phy->instance),
			   CAL_CSI2_COMPLEXIO_CFG_RESET_DONE_MASK) !=
			   CAL_CSI2_COMPLEXIO_CFG_RESET_DONE_RESETCOMPLETED)
		phy_err(phy, "Timeout waiting for Complex IO reset done\n");
पूर्ण

अटल व्योम cal_camerarx_रुको_stop_state(काष्ठा cal_camerarx *phy)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(750);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (cal_पढ़ो_field(phy->cal,
				   CAL_CSI2_TIMING(phy->instance),
				   CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK) == 0)
			अवरोध;
		usleep_range(500, 5000);
	पूर्ण

	अगर (cal_पढ़ो_field(phy->cal, CAL_CSI2_TIMING(phy->instance),
			   CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK) != 0)
		phy_err(phy, "Timeout waiting for stop state\n");
पूर्ण

अटल व्योम cal_camerarx_enable_irqs(काष्ठा cal_camerarx *phy)
अणु
	स्थिर u32 cio_err_mask =
		CAL_CSI2_COMPLEXIO_IRQ_LANE_ERRORS_MASK |
		CAL_CSI2_COMPLEXIO_IRQ_FIFO_OVR_MASK |
		CAL_CSI2_COMPLEXIO_IRQ_SHORT_PACKET_MASK |
		CAL_CSI2_COMPLEXIO_IRQ_ECC_NO_CORRECTION_MASK;

	/* Enable CIO error IRQs. */
	cal_ग_लिखो(phy->cal, CAL_HL_IRQENABLE_SET(0),
		  CAL_HL_IRQ_CIO_MASK(phy->instance));
	cal_ग_लिखो(phy->cal, CAL_CSI2_COMPLEXIO_IRQENABLE(phy->instance),
		  cio_err_mask);
पूर्ण

अटल व्योम cal_camerarx_disable_irqs(काष्ठा cal_camerarx *phy)
अणु
	/* Disable CIO error irqs */
	cal_ग_लिखो(phy->cal, CAL_HL_IRQENABLE_CLR(0),
		  CAL_HL_IRQ_CIO_MASK(phy->instance));
	cal_ग_लिखो(phy->cal, CAL_CSI2_COMPLEXIO_IRQENABLE(phy->instance), 0);
पूर्ण

अटल व्योम cal_camerarx_ppi_enable(काष्ठा cal_camerarx *phy)
अणु
	cal_ग_लिखो_field(phy->cal, CAL_CSI2_PPI_CTRL(phy->instance),
			1, CAL_CSI2_PPI_CTRL_IF_EN_MASK);
पूर्ण

अटल व्योम cal_camerarx_ppi_disable(काष्ठा cal_camerarx *phy)
अणु
	cal_ग_लिखो_field(phy->cal, CAL_CSI2_PPI_CTRL(phy->instance),
			0, CAL_CSI2_PPI_CTRL_IF_EN_MASK);
पूर्ण

अटल पूर्णांक cal_camerarx_start(काष्ठा cal_camerarx *phy)
अणु
	s64 बाह्यal_rate;
	u32 sscounter;
	u32 val;
	पूर्णांक ret;

	बाह्यal_rate = cal_camerarx_get_बाह्यal_rate(phy);
	अगर (बाह्यal_rate < 0)
		वापस बाह्यal_rate;

	ret = v4l2_subdev_call(phy->sensor, core, s_घातer, 1);
	अगर (ret < 0 && ret != -ENOIOCTLCMD && ret != -ENODEV) अणु
		phy_err(phy, "power on failed in subdev\n");
		वापस ret;
	पूर्ण

	cal_camerarx_enable_irqs(phy);

	/*
	 * CSI-2 PHY Link Initialization Sequence, according to the DRA74xP /
	 * DRA75xP / DRA76xP / DRA77xP TRM. The DRA71x / DRA72x and the AM65x /
	 * DRA80xM TRMs have a a slightly simplअगरied sequence.
	 */

	/*
	 * 1. Configure all CSI-2 low level protocol रेजिस्टरs to be पढ़ोy to
	 *    receive संकेतs/data from the CSI-2 PHY.
	 *
	 *    i.-v. Configure the lanes position and polarity.
	 */
	cal_camerarx_lane_config(phy);

	/*
	 *    vi.-vii. Configure D-PHY mode, enable the required lanes and
	 *             enable the CAMERARX घड़ी.
	 */
	cal_camerarx_enable(phy);

	/*
	 * 2. CSI PHY and link initialization sequence.
	 *
	 *    a. Deनिश्चित the CSI-2 PHY reset. Do not रुको क्रम reset completion
	 *       at this poपूर्णांक, as it requires the बाह्यal sensor to send the
	 *       CSI-2 HS घड़ी.
	 */
	cal_ग_लिखो_field(phy->cal, CAL_CSI2_COMPLEXIO_CFG(phy->instance),
			CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL_OPERATIONAL,
			CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL_MASK);
	phy_dbg(3, phy, "CAL_CSI2_COMPLEXIO_CFG(%d) = 0x%08x De-assert Complex IO Reset\n",
		phy->instance,
		cal_पढ़ो(phy->cal, CAL_CSI2_COMPLEXIO_CFG(phy->instance)));

	/* Dummy पढ़ो to allow SCP reset to complete. */
	camerarx_पढ़ो(phy, CAL_CSI2_PHY_REG0);

	/* Program the PHY timing parameters. */
	cal_camerarx_config(phy, बाह्यal_rate);

	/*
	 *    b. Assert the FORCERXMODE संकेत.
	 *
	 * The stop-state-counter is based on fclk cycles, and we always use
	 * the x16 and x4 settings, so stop-state-समयout =
	 * fclk-cycle * 16 * 4 * counter.
	 *
	 * Stop-state-समयout must be more than 100us as per CSI-2 spec, so we
	 * calculate a समयout that's 100us (rounding up).
	 */
	sscounter = DIV_ROUND_UP(clk_get_rate(phy->cal->fclk), 10000 *  16 * 4);

	val = cal_पढ़ो(phy->cal, CAL_CSI2_TIMING(phy->instance));
	cal_set_field(&val, 1, CAL_CSI2_TIMING_STOP_STATE_X16_IO1_MASK);
	cal_set_field(&val, 1, CAL_CSI2_TIMING_STOP_STATE_X4_IO1_MASK);
	cal_set_field(&val, sscounter,
		      CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK);
	cal_ग_लिखो(phy->cal, CAL_CSI2_TIMING(phy->instance), val);
	phy_dbg(3, phy, "CAL_CSI2_TIMING(%d) = 0x%08x Stop States\n",
		phy->instance,
		cal_पढ़ो(phy->cal, CAL_CSI2_TIMING(phy->instance)));

	/* Assert the FORCERXMODE संकेत. */
	cal_ग_लिखो_field(phy->cal, CAL_CSI2_TIMING(phy->instance),
			1, CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK);
	phy_dbg(3, phy, "CAL_CSI2_TIMING(%d) = 0x%08x Force RXMODE\n",
		phy->instance,
		cal_पढ़ो(phy->cal, CAL_CSI2_TIMING(phy->instance)));

	/*
	 * c. Connect pull-करोwn on CSI-2 PHY link (using pad control).
	 *
	 * This is not required on DRA71x, DRA72x, AM65x and DRA80xM. Not
	 * implemented.
	 */

	/*
	 * d. Power up the CSI-2 PHY.
	 * e. Check whether the state status reaches the ON state.
	 */
	cal_camerarx_घातer(phy, true);

	/*
	 * Start the sensor to enable the CSI-2 HS घड़ी. We can now रुको क्रम
	 * CSI-2 PHY reset to complete.
	 */
	ret = v4l2_subdev_call(phy->sensor, video, s_stream, 1);
	अगर (ret) अणु
		v4l2_subdev_call(phy->sensor, core, s_घातer, 0);
		cal_camerarx_disable_irqs(phy);
		phy_err(phy, "stream on failed in subdev\n");
		वापस ret;
	पूर्ण

	cal_camerarx_रुको_reset(phy);

	/* f. Wait क्रम STOPSTATE=1 क्रम all enabled lane modules. */
	cal_camerarx_रुको_stop_state(phy);

	phy_dbg(1, phy, "CSI2_%u_REG1 = 0x%08x (bits 31-28 should be set)\n",
		phy->instance, camerarx_पढ़ो(phy, CAL_CSI2_PHY_REG1));

	/*
	 * g. Disable pull-करोwn on CSI-2 PHY link (using pad control).
	 *
	 * This is not required on DRA71x, DRA72x, AM65x and DRA80xM. Not
	 * implemented.
	 */

	/* Finally, enable the PHY Protocol Interface (PPI). */
	cal_camerarx_ppi_enable(phy);

	वापस 0;
पूर्ण

अटल व्योम cal_camerarx_stop(काष्ठा cal_camerarx *phy)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	cal_camerarx_ppi_disable(phy);

	cal_camerarx_disable_irqs(phy);

	cal_camerarx_घातer(phy, false);

	/* Assert Complex IO Reset */
	cal_ग_लिखो_field(phy->cal, CAL_CSI2_COMPLEXIO_CFG(phy->instance),
			CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL,
			CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL_MASK);

	/* Wait क्रम घातer करोwn completion */
	क्रम (i = 0; i < 10; i++) अणु
		अगर (cal_पढ़ो_field(phy->cal,
				   CAL_CSI2_COMPLEXIO_CFG(phy->instance),
				   CAL_CSI2_COMPLEXIO_CFG_RESET_DONE_MASK) ==
		    CAL_CSI2_COMPLEXIO_CFG_RESET_DONE_RESETONGOING)
			अवरोध;
		usleep_range(1000, 1100);
	पूर्ण
	phy_dbg(3, phy, "CAL_CSI2_COMPLEXIO_CFG(%d) = 0x%08x Complex IO in Reset (%d) %s\n",
		phy->instance,
		cal_पढ़ो(phy->cal, CAL_CSI2_COMPLEXIO_CFG(phy->instance)), i,
		(i >= 10) ? "(timeout)" : "");

	/* Disable the phy */
	cal_camerarx_disable(phy);

	अगर (v4l2_subdev_call(phy->sensor, video, s_stream, 0))
		phy_err(phy, "stream off failed in subdev\n");

	ret = v4l2_subdev_call(phy->sensor, core, s_घातer, 0);
	अगर (ret < 0 && ret != -ENOIOCTLCMD && ret != -ENODEV)
		phy_err(phy, "power off failed in subdev\n");
पूर्ण

/*
 *   Errata i913: CSI2 LDO Needs to be disabled when module is घातered on
 *
 *   Enabling CSI2 LDO लघुs it to core supply. It is crucial the 2 CSI2
 *   LDOs on the device are disabled अगर CSI-2 module is घातered on
 *   (0x4845 B304 | 0x4845 B384 [28:27] = 0x1) or in ULPS (0x4845 B304
 *   | 0x4845 B384 [28:27] = 0x2) mode. Common concerns include: high
 *   current draw on the module supply in active mode.
 *
 *   Errata करोes not apply when CSI-2 module is घातered off
 *   (0x4845 B304 | 0x4845 B384 [28:27] = 0x0).
 *
 * SW Workaround:
 *	Set the following रेजिस्टर bits to disable the LDO,
 *	which is essentially CSI2 REG10 bit 6:
 *
 *		Core 0:  0x4845 B828 = 0x0000 0040
 *		Core 1:  0x4845 B928 = 0x0000 0040
 */
व्योम cal_camerarx_i913_errata(काष्ठा cal_camerarx *phy)
अणु
	u32 reg10 = camerarx_पढ़ो(phy, CAL_CSI2_PHY_REG10);

	cal_set_field(&reg10, 1, CAL_CSI2_PHY_REG10_I933_LDO_DISABLE_MASK);

	phy_dbg(1, phy, "CSI2_%d_REG10 = 0x%08x\n", phy->instance, reg10);
	camerarx_ग_लिखो(phy, CAL_CSI2_PHY_REG10, reg10);
पूर्ण

अटल पूर्णांक cal_camerarx_regmap_init(काष्ठा cal_dev *cal,
				    काष्ठा cal_camerarx *phy)
अणु
	स्थिर काष्ठा cal_camerarx_data *phy_data;
	अचिन्हित पूर्णांक i;

	अगर (!cal->data)
		वापस -EINVAL;

	phy_data = &cal->data->camerarx[phy->instance];

	क्रम (i = 0; i < F_MAX_FIELDS; i++) अणु
		काष्ठा reg_field field = अणु
			.reg = cal->syscon_camerrx_offset,
			.lsb = phy_data->fields[i].lsb,
			.msb = phy_data->fields[i].msb,
		पूर्ण;

		/*
		 * Here we update the reg offset with the
		 * value found in DT
		 */
		phy->fields[i] = devm_regmap_field_alloc(cal->dev,
							 cal->syscon_camerrx,
							 field);
		अगर (IS_ERR(phy->fields[i])) अणु
			cal_err(cal, "Unable to allocate regmap fields\n");
			वापस PTR_ERR(phy->fields[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cal_camerarx_parse_dt(काष्ठा cal_camerarx *phy)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक *endpoपूर्णांक = &phy->endpoपूर्णांक;
	अक्षर data_lanes[V4L2_FWNODE_CSI2_MAX_DATA_LANES * 2];
	काष्ठा device_node *ep_node;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/*
	 * Find the endpoपूर्णांक node क्रम the port corresponding to the PHY
	 * instance, and parse its CSI-2-related properties.
	 */
	ep_node = of_graph_get_endpoपूर्णांक_by_regs(phy->cal->dev->of_node,
						phy->instance, 0);
	अगर (!ep_node) अणु
		/*
		 * The endpoपूर्णांक is not mandatory, not all PHY instances need to
		 * be connected in DT.
		 */
		phy_dbg(3, phy, "Port has no endpoint\n");
		वापस 0;
	पूर्ण

	endpoपूर्णांक->bus_type = V4L2_MBUS_CSI2_DPHY;
	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(ep_node), endpoपूर्णांक);
	अगर (ret < 0) अणु
		phy_err(phy, "Failed to parse endpoint\n");
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < endpoपूर्णांक->bus.mipi_csi2.num_data_lanes; i++) अणु
		अचिन्हित पूर्णांक lane = endpoपूर्णांक->bus.mipi_csi2.data_lanes[i];

		अगर (lane > 4) अणु
			phy_err(phy, "Invalid position %u for data lane %u\n",
				lane, i);
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		data_lanes[i*2] = '0' + lane;
		data_lanes[i*2+1] = ' ';
	पूर्ण

	data_lanes[i*2-1] = '\0';

	phy_dbg(3, phy,
		"CSI-2 bus: clock lane <%u>, data lanes <%s>, flags 0x%08x\n",
		endpoपूर्णांक->bus.mipi_csi2.घड़ी_lane, data_lanes,
		endpoपूर्णांक->bus.mipi_csi2.flags);

	/* Retrieve the connected device and store it क्रम later use. */
	phy->sensor_ep_node = of_graph_get_remote_endpoपूर्णांक(ep_node);
	phy->sensor_node = of_graph_get_port_parent(phy->sensor_ep_node);
	अगर (!phy->sensor_node) अणु
		phy_dbg(3, phy, "Can't get remote parent\n");
		of_node_put(phy->sensor_ep_node);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	phy_dbg(1, phy, "Found connected device %pOFn\n", phy->sensor_node);

करोne:
	of_node_put(ep_node);
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------
 *	V4L2 Subdev Operations
 * ------------------------------------------------------------------
 */

अटल अंतरभूत काष्ठा cal_camerarx *to_cal_camerarx(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा cal_camerarx, subdev);
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
cal_camerarx_get_pad_क्रमmat(काष्ठा cal_camerarx *phy,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    अचिन्हित पूर्णांक pad, u32 which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&phy->subdev, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &phy->क्रमmats[pad];
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक cal_camerarx_sd_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा cal_camerarx *phy = to_cal_camerarx(sd);

	अगर (enable)
		वापस cal_camerarx_start(phy);

	cal_camerarx_stop(phy);
	वापस 0;
पूर्ण

अटल पूर्णांक cal_camerarx_sd_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
					  काष्ठा v4l2_subdev_pad_config *cfg,
					  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा cal_camerarx *phy = to_cal_camerarx(sd);

	/* No transcoding, source and sink codes must match. */
	अगर (code->pad == CAL_CAMERARX_PAD_SOURCE) अणु
		काष्ठा v4l2_mbus_framefmt *fmt;

		अगर (code->index > 0)
			वापस -EINVAL;

		fmt = cal_camerarx_get_pad_क्रमmat(phy, cfg,
						  CAL_CAMERARX_PAD_SINK,
						  code->which);
		code->code = fmt->code;
		वापस 0;
	पूर्ण

	अगर (code->index >= cal_num_क्रमmats)
		वापस -EINVAL;

	code->code = cal_क्रमmats[code->index].code;

	वापस 0;
पूर्ण

अटल पूर्णांक cal_camerarx_sd_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
					   काष्ठा v4l2_subdev_pad_config *cfg,
					   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा cal_camerarx *phy = to_cal_camerarx(sd);
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;

	अगर (fse->index > 0)
		वापस -EINVAL;

	/* No transcoding, source and sink क्रमmats must match. */
	अगर (fse->pad == CAL_CAMERARX_PAD_SOURCE) अणु
		काष्ठा v4l2_mbus_framefmt *fmt;

		fmt = cal_camerarx_get_pad_क्रमmat(phy, cfg,
						  CAL_CAMERARX_PAD_SINK,
						  fse->which);
		अगर (fse->code != fmt->code)
			वापस -EINVAL;

		fse->min_width = fmt->width;
		fse->max_width = fmt->width;
		fse->min_height = fmt->height;
		fse->max_height = fmt->height;

		वापस 0;
	पूर्ण

	fmtinfo = cal_क्रमmat_by_code(fse->code);
	अगर (!fmtinfo)
		वापस -EINVAL;

	fse->min_width = CAL_MIN_WIDTH_BYTES * 8 / ALIGN(fmtinfo->bpp, 8);
	fse->max_width = CAL_MAX_WIDTH_BYTES * 8 / ALIGN(fmtinfo->bpp, 8);
	fse->min_height = CAL_MIN_HEIGHT_LINES;
	fse->max_height = CAL_MAX_HEIGHT_LINES;

	वापस 0;
पूर्ण

अटल पूर्णांक cal_camerarx_sd_get_fmt(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा cal_camerarx *phy = to_cal_camerarx(sd);
	काष्ठा v4l2_mbus_framefmt *fmt;

	fmt = cal_camerarx_get_pad_क्रमmat(phy, cfg, क्रमmat->pad, क्रमmat->which);
	क्रमmat->क्रमmat = *fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक cal_camerarx_sd_set_fmt(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा cal_camerarx *phy = to_cal_camerarx(sd);
	स्थिर काष्ठा cal_क्रमmat_info *fmtinfo;
	काष्ठा v4l2_mbus_framefmt *fmt;
	अचिन्हित पूर्णांक bpp;

	/* No transcoding, source and sink क्रमmats must match. */
	अगर (क्रमmat->pad == CAL_CAMERARX_PAD_SOURCE)
		वापस cal_camerarx_sd_get_fmt(sd, cfg, क्रमmat);

	/*
	 * Default to the first क्रमmat is the requested media bus code isn't
	 * supported.
	 */
	fmtinfo = cal_क्रमmat_by_code(क्रमmat->क्रमmat.code);
	अगर (!fmtinfo)
		fmtinfo = &cal_क्रमmats[0];

	/*
	 * Clamp the size, update the code. The field and colorspace are
	 * accepted as-is.
	 */
	bpp = ALIGN(fmtinfo->bpp, 8);

	क्रमmat->क्रमmat.width = clamp_t(अचिन्हित पूर्णांक, क्रमmat->क्रमmat.width,
				       CAL_MIN_WIDTH_BYTES * 8 / bpp,
				       CAL_MAX_WIDTH_BYTES * 8 / bpp);
	क्रमmat->क्रमmat.height = clamp_t(अचिन्हित पूर्णांक, क्रमmat->क्रमmat.height,
					CAL_MIN_HEIGHT_LINES,
					CAL_MAX_HEIGHT_LINES);
	क्रमmat->क्रमmat.code = fmtinfo->code;

	/* Store the क्रमmat and propagate it to the source pad. */
	fmt = cal_camerarx_get_pad_क्रमmat(phy, cfg, CAL_CAMERARX_PAD_SINK,
					  क्रमmat->which);
	*fmt = क्रमmat->क्रमmat;

	fmt = cal_camerarx_get_pad_क्रमmat(phy, cfg, CAL_CAMERARX_PAD_SOURCE,
					  क्रमmat->which);
	*fmt = क्रमmat->क्रमmat;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		phy->fmtinfo = fmtinfo;

	वापस 0;
पूर्ण

अटल पूर्णांक cal_camerarx_sd_init_cfg(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = cfg ? V4L2_SUBDEV_FORMAT_TRY
		       : V4L2_SUBDEV_FORMAT_ACTIVE,
		.pad = CAL_CAMERARX_PAD_SINK,
		.क्रमmat = अणु
			.width = 640,
			.height = 480,
			.code = MEDIA_BUS_FMT_UYVY8_2X8,
			.field = V4L2_FIELD_NONE,
			.colorspace = V4L2_COLORSPACE_SRGB,
			.ycbcr_enc = V4L2_YCBCR_ENC_601,
			.quantization = V4L2_QUANTIZATION_LIM_RANGE,
			.xfer_func = V4L2_XFER_FUNC_SRGB,
		पूर्ण,
	पूर्ण;

	वापस cal_camerarx_sd_set_fmt(sd, cfg, &क्रमmat);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops cal_camerarx_video_ops = अणु
	.s_stream = cal_camerarx_sd_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops cal_camerarx_pad_ops = अणु
	.init_cfg = cal_camerarx_sd_init_cfg,
	.क्रमागत_mbus_code = cal_camerarx_sd_क्रमागत_mbus_code,
	.क्रमागत_frame_size = cal_camerarx_sd_क्रमागत_frame_size,
	.get_fmt = cal_camerarx_sd_get_fmt,
	.set_fmt = cal_camerarx_sd_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops cal_camerarx_subdev_ops = अणु
	.video = &cal_camerarx_video_ops,
	.pad = &cal_camerarx_pad_ops,
पूर्ण;

अटल काष्ठा media_entity_operations cal_camerarx_media_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/* ------------------------------------------------------------------
 *	Create and Destroy
 * ------------------------------------------------------------------
 */

काष्ठा cal_camerarx *cal_camerarx_create(काष्ठा cal_dev *cal,
					 अचिन्हित पूर्णांक instance)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(cal->dev);
	काष्ठा cal_camerarx *phy;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	phy = kzalloc(माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस ERR_PTR(-ENOMEM);

	phy->cal = cal;
	phy->instance = instance;

	phy->res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						(instance == 0) ?
						"cal_rx_core0" :
						"cal_rx_core1");
	phy->base = devm_ioremap_resource(cal->dev, phy->res);
	अगर (IS_ERR(phy->base)) अणु
		cal_err(cal, "failed to ioremap\n");
		ret = PTR_ERR(phy->base);
		जाओ error;
	पूर्ण

	cal_dbg(1, cal, "ioresource %s at %pa - %pa\n",
		phy->res->name, &phy->res->start, &phy->res->end);

	ret = cal_camerarx_regmap_init(cal, phy);
	अगर (ret)
		जाओ error;

	ret = cal_camerarx_parse_dt(phy);
	अगर (ret)
		जाओ error;

	/* Initialize the V4L2 subdev and media entity. */
	sd = &phy->subdev;
	v4l2_subdev_init(sd, &cal_camerarx_subdev_ops);
	sd->entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	sd->flags = V4L2_SUBDEV_FL_HAS_DEVNODE;
	snम_लिखो(sd->name, माप(sd->name), "CAMERARX%u", instance);
	sd->dev = cal->dev;

	phy->pads[CAL_CAMERARX_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	phy->pads[CAL_CAMERARX_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.ops = &cal_camerarx_media_ops;
	ret = media_entity_pads_init(&sd->entity, ARRAY_SIZE(phy->pads),
				     phy->pads);
	अगर (ret)
		जाओ error;

	cal_camerarx_sd_init_cfg(sd, शून्य);

	ret = v4l2_device_रेजिस्टर_subdev(&cal->v4l2_dev, sd);
	अगर (ret)
		जाओ error;

	वापस phy;

error:
	media_entity_cleanup(&phy->subdev.entity);
	kमुक्त(phy);
	वापस ERR_PTR(ret);
पूर्ण

व्योम cal_camerarx_destroy(काष्ठा cal_camerarx *phy)
अणु
	अगर (!phy)
		वापस;

	v4l2_device_unरेजिस्टर_subdev(&phy->subdev);
	media_entity_cleanup(&phy->subdev.entity);
	of_node_put(phy->sensor_ep_node);
	of_node_put(phy->sensor_node);
	kमुक्त(phy);
पूर्ण
