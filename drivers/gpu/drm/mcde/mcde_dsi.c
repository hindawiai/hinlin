<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <video/mipi_display.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "mcde_drm.h"
#समावेश "mcde_dsi_regs.h"

#घोषणा DSI_DEFAULT_LP_FREQ_HZ	19200000
#घोषणा DSI_DEFAULT_HS_FREQ_HZ	420160000

/* PRCMU DSI reset रेजिस्टरs */
#घोषणा PRCM_DSI_SW_RESET 0x324
#घोषणा PRCM_DSI_SW_RESET_DSI0_SW_RESETN BIT(0)
#घोषणा PRCM_DSI_SW_RESET_DSI1_SW_RESETN BIT(1)
#घोषणा PRCM_DSI_SW_RESET_DSI2_SW_RESETN BIT(2)

काष्ठा mcde_dsi अणु
	काष्ठा device *dev;
	काष्ठा mcde *mcde;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge_out;
	काष्ठा mipi_dsi_host dsi_host;
	काष्ठा mipi_dsi_device *mdsi;
	स्थिर काष्ठा drm_display_mode *mode;
	काष्ठा clk *hs_clk;
	काष्ठा clk *lp_clk;
	अचिन्हित दीर्घ hs_freq;
	अचिन्हित दीर्घ lp_freq;
	bool unused;

	व्योम __iomem *regs;
	काष्ठा regmap *prcmu;
पूर्ण;

अटल अंतरभूत काष्ठा mcde_dsi *bridge_to_mcde_dsi(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा mcde_dsi, bridge);
पूर्ण

अटल अंतरभूत काष्ठा mcde_dsi *host_to_mcde_dsi(काष्ठा mipi_dsi_host *h)
अणु
	वापस container_of(h, काष्ठा mcde_dsi, dsi_host);
पूर्ण

bool mcde_dsi_irq(काष्ठा mipi_dsi_device *mdsi)
अणु
	काष्ठा mcde_dsi *d;
	u32 val;
	bool te_received = false;

	d = host_to_mcde_dsi(mdsi->host);

	dev_dbg(d->dev, "%s called\n", __func__);

	val = पढ़ोl(d->regs + DSI_सूचीECT_CMD_STS_FLAG);
	अगर (val)
		dev_dbg(d->dev, "DSI_DIRECT_CMD_STS_FLAG = %08x\n", val);
	अगर (val & DSI_सूचीECT_CMD_STS_WRITE_COMPLETED)
		dev_dbg(d->dev, "direct command write completed\n");
	अगर (val & DSI_सूचीECT_CMD_STS_TE_RECEIVED) अणु
		te_received = true;
		dev_dbg(d->dev, "direct command TE received\n");
	पूर्ण
	अगर (val & DSI_सूचीECT_CMD_STS_ACKNOWLEDGE_WITH_ERR_RECEIVED)
		dev_err(d->dev, "direct command ACK ERR received\n");
	अगर (val & DSI_सूचीECT_CMD_STS_READ_COMPLETED_WITH_ERR)
		dev_err(d->dev, "direct command read ERR received\n");
	/* Mask off the ACK value and clear status */
	ग_लिखोl(val, d->regs + DSI_सूचीECT_CMD_STS_CLR);

	val = पढ़ोl(d->regs + DSI_CMD_MODE_STS_FLAG);
	अगर (val)
		dev_dbg(d->dev, "DSI_CMD_MODE_STS_FLAG = %08x\n", val);
	अगर (val & DSI_CMD_MODE_STS_ERR_NO_TE)
		/* This happens all the समय (safe to ignore) */
		dev_dbg(d->dev, "CMD mode no TE\n");
	अगर (val & DSI_CMD_MODE_STS_ERR_TE_MISS)
		/* This happens all the समय (safe to ignore) */
		dev_dbg(d->dev, "CMD mode TE miss\n");
	अगर (val & DSI_CMD_MODE_STS_ERR_SDI1_UNDERRUN)
		dev_err(d->dev, "CMD mode SD1 underrun\n");
	अगर (val & DSI_CMD_MODE_STS_ERR_SDI2_UNDERRUN)
		dev_err(d->dev, "CMD mode SD2 underrun\n");
	अगर (val & DSI_CMD_MODE_STS_ERR_UNWANTED_RD)
		dev_err(d->dev, "CMD mode unwanted RD\n");
	ग_लिखोl(val, d->regs + DSI_CMD_MODE_STS_CLR);

	val = पढ़ोl(d->regs + DSI_सूचीECT_CMD_RD_STS_FLAG);
	अगर (val)
		dev_dbg(d->dev, "DSI_DIRECT_CMD_RD_STS_FLAG = %08x\n", val);
	ग_लिखोl(val, d->regs + DSI_सूचीECT_CMD_RD_STS_CLR);

	val = पढ़ोl(d->regs + DSI_TG_STS_FLAG);
	अगर (val)
		dev_dbg(d->dev, "DSI_TG_STS_FLAG = %08x\n", val);
	ग_लिखोl(val, d->regs + DSI_TG_STS_CLR);

	val = पढ़ोl(d->regs + DSI_VID_MODE_STS_FLAG);
	अगर (val)
		dev_dbg(d->dev, "DSI_VID_MODE_STS_FLAG = %08x\n", val);
	अगर (val & DSI_VID_MODE_STS_VSG_RUNNING)
		dev_dbg(d->dev, "VID mode VSG running\n");
	अगर (val & DSI_VID_MODE_STS_ERR_MISSING_DATA)
		dev_err(d->dev, "VID mode missing data\n");
	अगर (val & DSI_VID_MODE_STS_ERR_MISSING_HSYNC)
		dev_err(d->dev, "VID mode missing HSYNC\n");
	अगर (val & DSI_VID_MODE_STS_ERR_MISSING_VSYNC)
		dev_err(d->dev, "VID mode missing VSYNC\n");
	अगर (val & DSI_VID_MODE_STS_REG_ERR_SMALL_LENGTH)
		dev_err(d->dev, "VID mode less bytes than expected between two HSYNC\n");
	अगर (val & DSI_VID_MODE_STS_REG_ERR_SMALL_HEIGHT)
		dev_err(d->dev, "VID mode less lines than expected between two VSYNC\n");
	अगर (val & (DSI_VID_MODE_STS_ERR_BURSTWRITE |
		   DSI_VID_MODE_STS_ERR_LINEWRITE |
		   DSI_VID_MODE_STS_ERR_LONGREAD))
		dev_err(d->dev, "VID mode read/write error\n");
	अगर (val & DSI_VID_MODE_STS_ERR_VRS_WRONG_LENGTH)
		dev_err(d->dev, "VID mode received packets differ from expected size\n");
	अगर (val & DSI_VID_MODE_STS_VSG_RECOVERY)
		dev_err(d->dev, "VID mode VSG in recovery mode\n");
	ग_लिखोl(val, d->regs + DSI_VID_MODE_STS_CLR);

	वापस te_received;
पूर्ण

अटल व्योम mcde_dsi_attach_to_mcde(काष्ठा mcde_dsi *d)
अणु
	d->mcde->mdsi = d->mdsi;

	/*
	 * Select the way the DSI data flow is pushing to the display:
	 * currently we just support video or command mode depending
	 * on the type of display. Video mode शेषs to using the
	 * क्रमmatter itself क्रम synchronization (stateless video panel).
	 *
	 * FIXME: add flags to काष्ठा mipi_dsi_device .flags to indicate
	 * displays that require BTA (bus turn around) so we can handle
	 * such displays as well. Figure out how to properly handle
	 * single frame on-demand updates with DRM क्रम command mode
	 * displays (MCDE_COMMAND_ONESHOT_FLOW).
	 */
	अगर (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO)
		d->mcde->flow_mode = MCDE_VIDEO_FORMATTER_FLOW;
	अन्यथा
		d->mcde->flow_mode = MCDE_COMMAND_TE_FLOW;
पूर्ण

अटल पूर्णांक mcde_dsi_host_attach(काष्ठा mipi_dsi_host *host,
				काष्ठा mipi_dsi_device *mdsi)
अणु
	काष्ठा mcde_dsi *d = host_to_mcde_dsi(host);

	अगर (mdsi->lanes < 1 || mdsi->lanes > 2) अणु
		DRM_ERROR("dsi device params invalid, 1 or 2 lanes supported\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(d->dev, "attached DSI device with %d lanes\n", mdsi->lanes);
	/* MIPI_DSI_FMT_RGB88 etc */
	dev_info(d->dev, "format %08x, %dbpp\n", mdsi->क्रमmat,
		 mipi_dsi_pixel_क्रमmat_to_bpp(mdsi->क्रमmat));
	dev_info(d->dev, "mode flags: %08lx\n", mdsi->mode_flags);

	d->mdsi = mdsi;
	अगर (d->mcde)
		mcde_dsi_attach_to_mcde(d);

	वापस 0;
पूर्ण

अटल पूर्णांक mcde_dsi_host_detach(काष्ठा mipi_dsi_host *host,
				काष्ठा mipi_dsi_device *mdsi)
अणु
	काष्ठा mcde_dsi *d = host_to_mcde_dsi(host);

	d->mdsi = शून्य;
	अगर (d->mcde)
		d->mcde->mdsi = शून्य;

	वापस 0;
पूर्ण

#घोषणा MCDE_DSI_HOST_IS_READ(type)			    \
	((type == MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM) || \
	 (type == MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM) || \
	 (type == MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM) || \
	 (type == MIPI_DSI_DCS_READ))

अटल पूर्णांक mcde_dsi_execute_transfer(काष्ठा mcde_dsi *d,
				     स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	स्थिर u32 loop_delay_us = 10; /* us */
	u32 loop_counter;
	माप_प्रकार txlen = msg->tx_len;
	माप_प्रकार rxlen = msg->rx_len;
	पूर्णांक i;
	u32 val;
	पूर्णांक ret;

	ग_लिखोl(~0, d->regs + DSI_सूचीECT_CMD_STS_CLR);
	ग_लिखोl(~0, d->regs + DSI_CMD_MODE_STS_CLR);
	/* Send command */
	ग_लिखोl(1, d->regs + DSI_सूचीECT_CMD_SEND);

	loop_counter = 1000 * 1000 / loop_delay_us;
	अगर (MCDE_DSI_HOST_IS_READ(msg->type)) अणु
		/* Read command */
		जबतक (!(पढ़ोl(d->regs + DSI_सूचीECT_CMD_STS) &
			 (DSI_सूचीECT_CMD_STS_READ_COMPLETED |
			  DSI_सूचीECT_CMD_STS_READ_COMPLETED_WITH_ERR))
		       && --loop_counter)
			usleep_range(loop_delay_us, (loop_delay_us * 3) / 2);
		अगर (!loop_counter) अणु
			dev_err(d->dev, "DSI read timeout!\n");
			/* Set निकास code and retry */
			वापस -ETIME;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Writing only */
		जबतक (!(पढ़ोl(d->regs + DSI_सूचीECT_CMD_STS) &
			 DSI_सूचीECT_CMD_STS_WRITE_COMPLETED)
		       && --loop_counter)
			usleep_range(loop_delay_us, (loop_delay_us * 3) / 2);

		अगर (!loop_counter) अणु
			/* Set निकास code and retry */
			dev_err(d->dev, "DSI write timeout!\n");
			वापस -ETIME;
		पूर्ण
	पूर्ण

	val = पढ़ोl(d->regs + DSI_सूचीECT_CMD_STS);
	अगर (val & DSI_सूचीECT_CMD_STS_READ_COMPLETED_WITH_ERR) अणु
		dev_err(d->dev, "read completed with error\n");
		ग_लिखोl(1, d->regs + DSI_सूचीECT_CMD_RD_INIT);
		वापस -EIO;
	पूर्ण
	अगर (val & DSI_सूचीECT_CMD_STS_ACKNOWLEDGE_WITH_ERR_RECEIVED) अणु
		val >>= DSI_सूचीECT_CMD_STS_ACK_VAL_SHIFT;
		dev_err(d->dev, "error during transmission: %04x\n",
			val);
		वापस -EIO;
	पूर्ण

	अगर (!MCDE_DSI_HOST_IS_READ(msg->type)) अणु
		/* Return number of bytes written */
		ret = txlen;
	पूर्ण अन्यथा अणु
		/* OK this is a पढ़ो command, get the response */
		u32 rdsz;
		u32 rddat;
		u8 *rx = msg->rx_buf;

		rdsz = पढ़ोl(d->regs + DSI_सूचीECT_CMD_RD_PROPERTY);
		rdsz &= DSI_सूचीECT_CMD_RD_PROPERTY_RD_SIZE_MASK;
		rddat = पढ़ोl(d->regs + DSI_सूचीECT_CMD_RDDAT);
		अगर (rdsz < rxlen) अणु
			dev_err(d->dev, "read error, requested %zd got %d\n",
				rxlen, rdsz);
			वापस -EIO;
		पूर्ण
		/* FIXME: पढ़ो more than 4 bytes */
		क्रम (i = 0; i < 4 && i < rxlen; i++)
			rx[i] = (rddat >> (i * 8)) & 0xff;
		ret = rdsz;
	पूर्ण

	/* Successful transmission */
	वापस ret;
पूर्ण

अटल sमाप_प्रकार mcde_dsi_host_transfer(काष्ठा mipi_dsi_host *host,
				      स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा mcde_dsi *d = host_to_mcde_dsi(host);
	स्थिर u8 *tx = msg->tx_buf;
	माप_प्रकार txlen = msg->tx_len;
	माप_प्रकार rxlen = msg->rx_len;
	अचिन्हित पूर्णांक retries = 0;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (txlen > 16) अणु
		dev_err(d->dev,
			"dunno how to write more than 16 bytes yet\n");
		वापस -EIO;
	पूर्ण
	अगर (rxlen > 4) अणु
		dev_err(d->dev,
			"dunno how to read more than 4 bytes yet\n");
		वापस -EIO;
	पूर्ण

	dev_dbg(d->dev,
		"message to channel %d, write %zd bytes read %zd bytes\n",
		msg->channel, txlen, rxlen);

	/* Command "nature" */
	अगर (MCDE_DSI_HOST_IS_READ(msg->type))
		/* MCTL_MAIN_DATA_CTL alपढ़ोy set up */
		val = DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_NAT_READ;
	अन्यथा
		val = DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_NAT_WRITE;
	/*
	 * More than 2 bytes will not fit in a single packet, so it's
	 * समय to set the "long not short" bit. One byte is used by
	 * the MIPI DCS command leaving just one byte क्रम the payload
	 * in a लघु package.
	 */
	अगर (mipi_dsi_packet_क्रमmat_is_दीर्घ(msg->type))
		val |= DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_LONGNOTSHORT;
	val |= 0 << DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_ID_SHIFT;
	val |= txlen << DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_SIZE_SHIFT;
	val |= DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_LP_EN;
	val |= msg->type << DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_HEAD_SHIFT;
	ग_लिखोl(val, d->regs + DSI_सूचीECT_CMD_MAIN_SETTINGS);

	/* MIPI DCS command is part of the data */
	अगर (txlen > 0) अणु
		val = 0;
		क्रम (i = 0; i < 4 && i < txlen; i++)
			val |= tx[i] << (i * 8);
	पूर्ण
	ग_लिखोl(val, d->regs + DSI_सूचीECT_CMD_WRDAT0);
	अगर (txlen > 4) अणु
		val = 0;
		क्रम (i = 0; i < 4 && (i + 4) < txlen; i++)
			val |= tx[i + 4] << (i * 8);
		ग_लिखोl(val, d->regs + DSI_सूचीECT_CMD_WRDAT1);
	पूर्ण
	अगर (txlen > 8) अणु
		val = 0;
		क्रम (i = 0; i < 4 && (i + 8) < txlen; i++)
			val |= tx[i + 8] << (i * 8);
		ग_लिखोl(val, d->regs + DSI_सूचीECT_CMD_WRDAT2);
	पूर्ण
	अगर (txlen > 12) अणु
		val = 0;
		क्रम (i = 0; i < 4 && (i + 12) < txlen; i++)
			val |= tx[i + 12] << (i * 8);
		ग_लिखोl(val, d->regs + DSI_सूचीECT_CMD_WRDAT3);
	पूर्ण

	जबतक (retries < 3) अणु
		ret = mcde_dsi_execute_transfer(d, msg);
		अगर (ret >= 0)
			अवरोध;
		retries++;
	पूर्ण
	अगर (ret < 0 && retries)
		dev_err(d->dev, "gave up after %d retries\n", retries);

	/* Clear any errors */
	ग_लिखोl(~0, d->regs + DSI_सूचीECT_CMD_STS_CLR);
	ग_लिखोl(~0, d->regs + DSI_CMD_MODE_STS_CLR);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops mcde_dsi_host_ops = अणु
	.attach = mcde_dsi_host_attach,
	.detach = mcde_dsi_host_detach,
	.transfer = mcde_dsi_host_transfer,
पूर्ण;

/* This sends a direct (लघु) command to request TE */
व्योम mcde_dsi_te_request(काष्ठा mipi_dsi_device *mdsi)
अणु
	काष्ठा mcde_dsi *d;
	u32 val;

	d = host_to_mcde_dsi(mdsi->host);

	/* Command "nature" TE request */
	val = DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_NAT_TE_REQ;
	val |= 0 << DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_ID_SHIFT;
	val |= 2 << DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_SIZE_SHIFT;
	val |= DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_LP_EN;
	val |= MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM <<
		DSI_सूचीECT_CMD_MAIN_SETTINGS_CMD_HEAD_SHIFT;
	ग_लिखोl(val, d->regs + DSI_सूचीECT_CMD_MAIN_SETTINGS);

	/* Clear TE reveived and error status bits and enables them */
	ग_लिखोl(DSI_सूचीECT_CMD_STS_CLR_TE_RECEIVED_CLR |
	       DSI_सूचीECT_CMD_STS_CLR_ACKNOWLEDGE_WITH_ERR_RECEIVED_CLR,
	       d->regs + DSI_सूचीECT_CMD_STS_CLR);
	val = पढ़ोl(d->regs + DSI_सूचीECT_CMD_STS_CTL);
	val |= DSI_सूचीECT_CMD_STS_CTL_TE_RECEIVED_EN;
	val |= DSI_सूचीECT_CMD_STS_CTL_ACKNOWLEDGE_WITH_ERR_EN;
	ग_लिखोl(val, d->regs + DSI_सूचीECT_CMD_STS_CTL);

	/* Clear and enable no TE or TE missing status */
	ग_लिखोl(DSI_CMD_MODE_STS_CLR_ERR_NO_TE_CLR |
	       DSI_CMD_MODE_STS_CLR_ERR_TE_MISS_CLR,
	       d->regs + DSI_CMD_MODE_STS_CLR);
	val = पढ़ोl(d->regs + DSI_CMD_MODE_STS_CTL);
	val |= DSI_CMD_MODE_STS_CTL_ERR_NO_TE_EN;
	val |= DSI_CMD_MODE_STS_CTL_ERR_TE_MISS_EN;
	ग_लिखोl(val, d->regs + DSI_CMD_MODE_STS_CTL);

	/* Send this TE request command */
	ग_लिखोl(1, d->regs + DSI_सूचीECT_CMD_SEND);
पूर्ण

अटल व्योम mcde_dsi_setup_video_mode(काष्ठा mcde_dsi *d,
				      स्थिर काष्ठा drm_display_mode *mode)
अणु
	/* cpp, अक्षरacters per pixel, number of bytes per pixel */
	u8 cpp = mipi_dsi_pixel_क्रमmat_to_bpp(d->mdsi->क्रमmat) / 8;
	u64 pclk;
	u64 bpl;
	पूर्णांक hfp;
	पूर्णांक hbp;
	पूर्णांक hsa;
	u32 blkline_pck, line_duration;
	u32 val;

	val = 0;
	अगर (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
		val |= DSI_VID_MAIN_CTL_BURST_MODE;
	अगर (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE) अणु
		val |= DSI_VID_MAIN_CTL_SYNC_PULSE_ACTIVE;
		val |= DSI_VID_MAIN_CTL_SYNC_PULSE_HORIZONTAL;
	पूर्ण
	/* RGB header and pixel mode */
	चयन (d->mdsi->क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB565:
		val |= MIPI_DSI_PACKED_PIXEL_STREAM_16 <<
			DSI_VID_MAIN_CTL_HEADER_SHIFT;
		val |= DSI_VID_MAIN_CTL_VID_PIXEL_MODE_16BITS;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		val |= MIPI_DSI_PACKED_PIXEL_STREAM_18 <<
			DSI_VID_MAIN_CTL_HEADER_SHIFT;
		val |= DSI_VID_MAIN_CTL_VID_PIXEL_MODE_18BITS;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
		val |= MIPI_DSI_PIXEL_STREAM_3BYTE_18
			<< DSI_VID_MAIN_CTL_HEADER_SHIFT;
		val |= DSI_VID_MAIN_CTL_VID_PIXEL_MODE_18BITS_LOOSE;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB888:
		val |= MIPI_DSI_PACKED_PIXEL_STREAM_24 <<
			DSI_VID_MAIN_CTL_HEADER_SHIFT;
		val |= DSI_VID_MAIN_CTL_VID_PIXEL_MODE_24BITS;
		अवरोध;
	शेष:
		dev_err(d->dev, "unknown pixel mode\n");
		वापस;
	पूर्ण

	/* TODO: TVG (test video generator) could be enabled here */

	/*
	 * During vertical blanking: go to LP mode
	 * Like with the EOL setting, अगर this is not set, the EOL area will be
	 * filled with शून्य or blanking packets in the vblank area.
	 * FIXME: some Samsung phones and display panels such as s6e63m0 use
	 * DSI_VID_MAIN_CTL_REG_BLKLINE_MODE_BLANKING here instead,
	 * figure out how to properly configure that from the panel.
	 */
	val |= DSI_VID_MAIN_CTL_REG_BLKLINE_MODE_LP_0;
	/*
	 * During EOL: go to LP mode. If this is not set, the EOL area will be
	 * filled with शून्य or blanking packets.
	 */
	val |= DSI_VID_MAIN_CTL_REG_BLKEOL_MODE_LP_0;
	/* Recovery mode 1 */
	val |= 1 << DSI_VID_MAIN_CTL_RECOVERY_MODE_SHIFT;
	/* All other fields zero */
	ग_लिखोl(val, d->regs + DSI_VID_MAIN_CTL);

	/* Vertical frame parameters are pretty straight-क्रमward */
	val = mode->vdisplay << DSI_VID_VSIZE_VACT_LENGTH_SHIFT;
	/* vertical front porch */
	val |= (mode->vsync_start - mode->vdisplay)
		<< DSI_VID_VSIZE_VFP_LENGTH_SHIFT;
	/* vertical sync active */
	val |= (mode->vsync_end - mode->vsync_start)
		<< DSI_VID_VSIZE_VSA_LENGTH_SHIFT;
	/* vertical back porch */
	val |= (mode->vtotal - mode->vsync_end)
		<< DSI_VID_VSIZE_VBP_LENGTH_SHIFT;
	ग_लिखोl(val, d->regs + DSI_VID_VSIZE);

	/*
	 * Horizontal frame parameters:
	 * horizontal resolution is given in pixels but must be re-calculated
	 * पूर्णांकo bytes since this is what the hardware expects, these रेजिस्टरs
	 * define the payload size of the packet.
	 *
	 * hfp = horizontal front porch in bytes
	 * hbp = horizontal back porch in bytes
	 * hsa = horizontal sync active in bytes
	 *
	 * 6 + 2 is HFP header + checksum
	 */
	hfp = (mode->hsync_start - mode->hdisplay) * cpp - 6 - 2;
	अगर (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE) अणु
		/*
		 * Use sync pulse क्रम sync: explicit HSA समय
		 * 6 is HBP header + checksum
		 * 4 is RGB header + checksum
		 */
		hbp = (mode->htotal - mode->hsync_end) * cpp - 4 - 6;
		/*
		 * 6 is HBP header + checksum
		 * 4 is HSW packet bytes
		 * 4 is RGB header + checksum
		 */
		hsa = (mode->hsync_end - mode->hsync_start) * cpp - 4 - 4 - 6;
	पूर्ण अन्यथा अणु
		/*
		 * Use event क्रम sync: HBP includes both back porch and sync
		 * 6 is HBP header + checksum
		 * 4 is HSW packet bytes
		 * 4 is RGB header + checksum
		 */
		hbp = (mode->htotal - mode->hsync_start) * cpp - 4 - 4 - 6;
		/* HSA is not present in this mode and set to 0 */
		hsa = 0;
	पूर्ण
	अगर (hfp < 0) अणु
		dev_info(d->dev, "hfp negative, set to 0\n");
		hfp = 0;
	पूर्ण
	अगर (hbp < 0) अणु
		dev_info(d->dev, "hbp negative, set to 0\n");
		hbp = 0;
	पूर्ण
	अगर (hsa < 0) अणु
		dev_info(d->dev, "hsa negative, set to 0\n");
		hsa = 0;
	पूर्ण
	dev_dbg(d->dev, "hfp: %u, hbp: %u, hsa: %u bytes\n",
		hfp, hbp, hsa);

	/* Frame parameters: horizontal sync active */
	val = hsa << DSI_VID_HSIZE1_HSA_LENGTH_SHIFT;
	/* horizontal back porch */
	val |= hbp << DSI_VID_HSIZE1_HBP_LENGTH_SHIFT;
	/* horizontal front porch */
	val |= hfp << DSI_VID_HSIZE1_HFP_LENGTH_SHIFT;
	ग_लिखोl(val, d->regs + DSI_VID_HSIZE1);

	/* RGB data length (visible bytes on one scanline) */
	val = mode->hdisplay * cpp;
	ग_लिखोl(val, d->regs + DSI_VID_HSIZE2);
	dev_dbg(d->dev, "RGB length, visible area on a line: %u bytes\n", val);

	/*
	 * Calculate the समय between two pixels in picoseconds using
	 * the supplied refresh rate and total resolution including
	 * porches and sync.
	 */
	/* (ps/s) / (pixels/s) = ps/pixels */
	pclk = DIV_ROUND_UP_ULL(1000000000000, (mode->घड़ी * 1000));
	dev_dbg(d->dev, "picoseconds between two pixels: %llu\n",
		pclk);

	/*
	 * How many bytes per line will this update frequency yield?
	 *
	 * Calculate the number of picoseconds क्रम one scanline (1), then
	 * भागide by 1000000000000 (2) to get in pixels per second we
	 * want to output.
	 *
	 * Multiply with number of bytes per second at this video display
	 * frequency (3) to get number of bytes transferred during this
	 * समय. Notice that we use the frequency the display wants,
	 * not what we actually get from the DSI PLL, which is hs_freq.
	 *
	 * These arithmetics are करोne in a dअगरferent order to aव्योम
	 * overflow.
	 */
	bpl = pclk * mode->htotal; /* (1) picoseconds per line */
	dev_dbg(d->dev, "picoseconds per line: %llu\n", bpl);
	/* Multiply with bytes per second (3) */
	bpl *= (d->mdsi->hs_rate / 8);
	/* Pixels per second (2) */
	bpl = DIV_ROUND_DOWN_ULL(bpl, 1000000); /* microseconds */
	bpl = DIV_ROUND_DOWN_ULL(bpl, 1000000); /* seconds */
	/* parallel transactions in all lanes */
	bpl *= d->mdsi->lanes;
	dev_dbg(d->dev,
		"calculated bytes per line: %llu @ %d Hz with HS %lu Hz\n",
		bpl, drm_mode_vrefresh(mode), d->mdsi->hs_rate);

	/*
	 * 6 is header + checksum, header = 4 bytes, checksum = 2 bytes
	 * 4 is लघु packet क्रम vsync/hsync
	 */
	अगर (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE) अणु
		/* Set the event packet size to 0 (not used) */
		ग_लिखोl(0, d->regs + DSI_VID_BLKSIZE1);
		/*
		 * FIXME: isn't the hsync width in pixels? The porch and
		 * sync area size is in pixels here, but this -6
		 * seems to be क्रम bytes. It looks like this in the venकरोr
		 * code though. Is it completely untested?
		 */
		blkline_pck = bpl - (mode->hsync_end - mode->hsync_start) - 6;
		val = blkline_pck << DSI_VID_BLKSIZE2_BLKLINE_PULSE_PCK_SHIFT;
		ग_लिखोl(val, d->regs + DSI_VID_BLKSIZE2);
	पूर्ण अन्यथा अणु
		/* Set the sync pulse packet size to 0 (not used) */
		ग_लिखोl(0, d->regs + DSI_VID_BLKSIZE2);
		/* Specअगरying payload size in bytes (-4-6 from manual) */
		blkline_pck = bpl - 4 - 6;
		अगर (blkline_pck > 0x1FFF)
			dev_err(d->dev, "blkline_pck too big %d bytes\n",
				blkline_pck);
		val = blkline_pck << DSI_VID_BLKSIZE1_BLKLINE_EVENT_PCK_SHIFT;
		val &= DSI_VID_BLKSIZE1_BLKLINE_EVENT_PCK_MASK;
		ग_लिखोl(val, d->regs + DSI_VID_BLKSIZE1);
	पूर्ण

	/*
	 * The line duration is used to scale back the frequency from
	 * the max frequency supported by the HS घड़ी to the desired
	 * update frequency in vrefresh.
	 */
	line_duration = blkline_pck + 6;
	/*
	 * The datasheet contains this complex condition to decreasing
	 * the line duration by 1 under very specअगरic circumstances.
	 * Here we also imply that LP is used during burst EOL.
	 */
	अगर (d->mdsi->lanes == 2 && (hsa & 0x01) && (hfp & 0x01)
	    && (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO_BURST))
		line_duration--;
	line_duration = DIV_ROUND_CLOSEST(line_duration, d->mdsi->lanes);
	dev_dbg(d->dev, "line duration %u bytes\n", line_duration);
	val = line_duration << DSI_VID_DPHY_TIME_REG_LINE_DURATION_SHIFT;
	/*
	 * This is the समय to perक्रमm LP->HS on D-PHY
	 * FIXME: nowhere to get this from: DT property on the DSI?
	 * The manual says this is "system dependent".
	 * values like 48 and 72 seen in the venकरोr code.
	 */
	val |= 48 << DSI_VID_DPHY_TIME_REG_WAKEUP_TIME_SHIFT;
	ग_लिखोl(val, d->regs + DSI_VID_DPHY_TIME);

	/*
	 * See the manual figure 657 page 2203 क्रम understanding the impact
	 * of the dअगरferent burst mode settings.
	 */
	अगर (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO_BURST) अणु
		पूर्णांक blkeol_pck, blkeol_duration;
		/*
		 * Packet size at EOL क्रम burst mode, this is only used
		 * अगर DSI_VID_MAIN_CTL_REG_BLKEOL_MODE_LP_0 is NOT set,
		 * but we instead send शून्य or blanking packets at EOL.
		 * This is given in number of bytes.
		 *
		 * See the manual page 2198 क्रम the 13 reg_blkeol_pck bits.
		 */
		blkeol_pck = bpl - (mode->htotal * cpp) - 6;
		अगर (blkeol_pck < 0) अणु
			dev_err(d->dev, "video block does not fit on line!\n");
			dev_err(d->dev,
				"calculated bytes per line: %llu @ %d Hz\n",
				bpl, drm_mode_vrefresh(mode));
			dev_err(d->dev,
				"bytes per line (blkline_pck) %u bytes\n",
				blkline_pck);
			dev_err(d->dev,
				"blkeol_pck becomes %d bytes\n", blkeol_pck);
			वापस;
		पूर्ण
		dev_dbg(d->dev, "BLKEOL packet: %d bytes\n", blkeol_pck);

		val = पढ़ोl(d->regs + DSI_VID_BLKSIZE1);
		val &= ~DSI_VID_BLKSIZE1_BLKEOL_PCK_MASK;
		val |= blkeol_pck << DSI_VID_BLKSIZE1_BLKEOL_PCK_SHIFT;
		ग_लिखोl(val, d->regs + DSI_VID_BLKSIZE1);
		/* Use the same value क्रम exact burst limit */
		val = blkeol_pck <<
			DSI_VID_VCA_SETTING2_EXACT_BURST_LIMIT_SHIFT;
		val &= DSI_VID_VCA_SETTING2_EXACT_BURST_LIMIT_MASK;
		ग_लिखोl(val, d->regs + DSI_VID_VCA_SETTING2);
		/*
		 * This BLKEOL duration is claimed to be the duration in घड़ी
		 * cycles of the BLLP end-of-line (EOL) period क्रम each line अगर
		 * DSI_VID_MAIN_CTL_REG_BLKEOL_MODE_LP_0 is set.
		 *
		 * It is hard to trust the manuals' claim that this is in घड़ी
		 * cycles as we mimic the behaviour of the venकरोr code, which
		 * appears to ग_लिखो a number of bytes that would have been
		 * transferred on a single lane.
		 *
		 * See the manual figure 657 page 2203 and page 2198 क्रम the 13
		 * reg_blkeol_duration bits.
		 *
		 * FIXME: should this also be set up also क्रम non-burst mode
		 * according to figure 565 page 2202?
		 */
		blkeol_duration = DIV_ROUND_CLOSEST(blkeol_pck + 6,
						    d->mdsi->lanes);
		dev_dbg(d->dev, "BLKEOL duration: %d clock cycles\n",
			blkeol_duration);

		val = पढ़ोl(d->regs + DSI_VID_PCK_TIME);
		val &= ~DSI_VID_PCK_TIME_BLKEOL_DURATION_MASK;
		val |= blkeol_duration <<
			DSI_VID_PCK_TIME_BLKEOL_DURATION_SHIFT;
		ग_लिखोl(val, d->regs + DSI_VID_PCK_TIME);

		/* Max burst limit, this is given in bytes */
		val = पढ़ोl(d->regs + DSI_VID_VCA_SETTING1);
		val &= ~DSI_VID_VCA_SETTING1_MAX_BURST_LIMIT_MASK;
		val |= (blkeol_pck - 6) <<
			DSI_VID_VCA_SETTING1_MAX_BURST_LIMIT_SHIFT;
		ग_लिखोl(val, d->regs + DSI_VID_VCA_SETTING1);
	पूर्ण

	/* Maximum line limit */
	val = पढ़ोl(d->regs + DSI_VID_VCA_SETTING2);
	val &= ~DSI_VID_VCA_SETTING2_MAX_LINE_LIMIT_MASK;
	val |= (blkline_pck - 6) <<
		DSI_VID_VCA_SETTING2_MAX_LINE_LIMIT_SHIFT;
	ग_लिखोl(val, d->regs + DSI_VID_VCA_SETTING2);
	dev_dbg(d->dev, "blkline pck: %d bytes\n", blkline_pck - 6);
पूर्ण

अटल व्योम mcde_dsi_start(काष्ठा mcde_dsi *d)
अणु
	अचिन्हित दीर्घ hs_freq;
	u32 val;
	पूर्णांक i;

	/* No पूर्णांकegration mode */
	ग_लिखोl(0, d->regs + DSI_MCTL_INTEGRATION_MODE);

	/* Enable the DSI port, from drivers/video/mcde/dsilink_v2.c */
	val = DSI_MCTL_MAIN_DATA_CTL_LINK_EN |
		DSI_MCTL_MAIN_DATA_CTL_BTA_EN |
		DSI_MCTL_MAIN_DATA_CTL_READ_EN |
		DSI_MCTL_MAIN_DATA_CTL_REG_TE_EN;
	अगर (!(d->mdsi->mode_flags & MIPI_DSI_MODE_EOT_PACKET))
		val |= DSI_MCTL_MAIN_DATA_CTL_HOST_EOT_GEN;
	ग_लिखोl(val, d->regs + DSI_MCTL_MAIN_DATA_CTL);

	/* Set a high command समयout, clear other fields */
	val = 0x3ff << DSI_CMD_MODE_CTL_TE_TIMEOUT_SHIFT;
	ग_लिखोl(val, d->regs + DSI_CMD_MODE_CTL);

	/*
	 * UI_X4 is described as "unit interval times four"
	 * I guess since DSI packets are 4 bytes wide, one unit
	 * is one byte.
	 */
	hs_freq = clk_get_rate(d->hs_clk);
	hs_freq /= 1000000; /* MHz */
	val = 4000 / hs_freq;
	dev_dbg(d->dev, "UI value: %d\n", val);
	val <<= DSI_MCTL_DPHY_STATIC_UI_X4_SHIFT;
	val &= DSI_MCTL_DPHY_STATIC_UI_X4_MASK;
	ग_लिखोl(val, d->regs + DSI_MCTL_DPHY_STATIC);

	/*
	 * Enable घड़ीing: 0x0f (something?) between each burst,
	 * enable the second lane अगर needed, enable continuous घड़ी अगर
	 * needed, enable चयन पूर्णांकo ULPM (ultra-low घातer mode) on
	 * all the lines.
	 */
	val = 0x0f << DSI_MCTL_MAIN_PHY_CTL_WAIT_BURST_TIME_SHIFT;
	अगर (d->mdsi->lanes == 2)
		val |= DSI_MCTL_MAIN_PHY_CTL_LANE2_EN;
	अगर (!(d->mdsi->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS))
		val |= DSI_MCTL_MAIN_PHY_CTL_CLK_CONTINUOUS;
	val |= DSI_MCTL_MAIN_PHY_CTL_CLK_ULPM_EN |
		DSI_MCTL_MAIN_PHY_CTL_DAT1_ULPM_EN |
		DSI_MCTL_MAIN_PHY_CTL_DAT2_ULPM_EN;
	ग_लिखोl(val, d->regs + DSI_MCTL_MAIN_PHY_CTL);

	val = (1 << DSI_MCTL_ULPOUT_TIME_CKLANE_ULPOUT_TIME_SHIFT) |
		(1 << DSI_MCTL_ULPOUT_TIME_DATA_ULPOUT_TIME_SHIFT);
	ग_लिखोl(val, d->regs + DSI_MCTL_ULPOUT_TIME);

	ग_लिखोl(DSI_DPHY_LANES_TRIM_DPHY_SPECS_90_81B_0_90,
	       d->regs + DSI_DPHY_LANES_TRIM);

	/* High PHY समयout */
	val = (0x0f << DSI_MCTL_DPHY_TIMEOUT_CLK_DIV_SHIFT) |
		(0x3fff << DSI_MCTL_DPHY_TIMEOUT_HSTX_TO_VAL_SHIFT) |
		(0x3fff << DSI_MCTL_DPHY_TIMEOUT_LPRX_TO_VAL_SHIFT);
	ग_लिखोl(val, d->regs + DSI_MCTL_DPHY_TIMEOUT);

	val = DSI_MCTL_MAIN_EN_PLL_START |
		DSI_MCTL_MAIN_EN_CKLANE_EN |
		DSI_MCTL_MAIN_EN_DAT1_EN |
		DSI_MCTL_MAIN_EN_IF1_EN;
	अगर (d->mdsi->lanes == 2)
		val |= DSI_MCTL_MAIN_EN_DAT2_EN;
	ग_लिखोl(val, d->regs + DSI_MCTL_MAIN_EN);

	/* Wait क्रम the PLL to lock and the घड़ी and data lines to come up */
	i = 0;
	val = DSI_MCTL_MAIN_STS_PLL_LOCK |
		DSI_MCTL_MAIN_STS_CLKLANE_READY |
		DSI_MCTL_MAIN_STS_DAT1_READY;
	अगर (d->mdsi->lanes == 2)
		val |= DSI_MCTL_MAIN_STS_DAT2_READY;
	जबतक ((पढ़ोl(d->regs + DSI_MCTL_MAIN_STS) & val) != val) अणु
		/* Sleep क्रम a millisecond */
		usleep_range(1000, 1500);
		अगर (i++ == 100) अणु
			dev_warn(d->dev, "DSI lanes did not start up\n");
			वापस;
		पूर्ण
	पूर्ण

	/* TODO needed? */

	/* Command mode, clear IF1 ID */
	val = पढ़ोl(d->regs + DSI_CMD_MODE_CTL);
	/*
	 * If we enable low-घातer mode here,
	 * then display updates become really slow.
	 */
	अगर (d->mdsi->mode_flags & MIPI_DSI_MODE_LPM)
		val |= DSI_CMD_MODE_CTL_IF1_LP_EN;
	val &= ~DSI_CMD_MODE_CTL_IF1_ID_MASK;
	ग_लिखोl(val, d->regs + DSI_CMD_MODE_CTL);

	/* Wait क्रम DSI PHY to initialize */
	usleep_range(100, 200);
	dev_info(d->dev, "DSI link enabled\n");
पूर्ण

/*
 * Notice that this is called from inside the display controller
 * and not from the bridge callbacks.
 */
व्योम mcde_dsi_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा mcde_dsi *d = bridge_to_mcde_dsi(bridge);
	अचिन्हित दीर्घ hs_freq, lp_freq;
	u32 val;
	पूर्णांक ret;

	/* Copy maximum घड़ी frequencies */
	अगर (d->mdsi->lp_rate)
		lp_freq = d->mdsi->lp_rate;
	अन्यथा
		lp_freq = DSI_DEFAULT_LP_FREQ_HZ;
	अगर (d->mdsi->hs_rate)
		hs_freq = d->mdsi->hs_rate;
	अन्यथा
		hs_freq = DSI_DEFAULT_HS_FREQ_HZ;

	/* Enable LP (Low Power, Energy Save, ES) and HS (High Speed) घड़ीs */
	d->lp_freq = clk_round_rate(d->lp_clk, lp_freq);
	ret = clk_set_rate(d->lp_clk, d->lp_freq);
	अगर (ret)
		dev_err(d->dev, "failed to set LP clock rate %lu Hz\n",
			d->lp_freq);

	d->hs_freq = clk_round_rate(d->hs_clk, hs_freq);
	ret = clk_set_rate(d->hs_clk, d->hs_freq);
	अगर (ret)
		dev_err(d->dev, "failed to set HS clock rate %lu Hz\n",
			d->hs_freq);

	/* Start घड़ीs */
	ret = clk_prepare_enable(d->lp_clk);
	अगर (ret)
		dev_err(d->dev, "failed to enable LP clock\n");
	अन्यथा
		dev_info(d->dev, "DSI LP clock rate %lu Hz\n",
			 d->lp_freq);
	ret = clk_prepare_enable(d->hs_clk);
	अगर (ret)
		dev_err(d->dev, "failed to enable HS clock\n");
	अन्यथा
		dev_info(d->dev, "DSI HS clock rate %lu Hz\n",
			 d->hs_freq);

	/* Assert RESET through the PRCMU, active low */
	/* FIXME: which DSI block? */
	regmap_update_bits(d->prcmu, PRCM_DSI_SW_RESET,
			   PRCM_DSI_SW_RESET_DSI0_SW_RESETN, 0);

	usleep_range(100, 200);

	/* De-निश्चित RESET again */
	regmap_update_bits(d->prcmu, PRCM_DSI_SW_RESET,
			   PRCM_DSI_SW_RESET_DSI0_SW_RESETN,
			   PRCM_DSI_SW_RESET_DSI0_SW_RESETN);

	/* Start up the hardware */
	mcde_dsi_start(d);

	अगर (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO) अणु
		/* Set up the video mode from the DRM mode */
		mcde_dsi_setup_video_mode(d, d->mode);

		/* Put IF1 पूर्णांकo video mode */
		val = पढ़ोl(d->regs + DSI_MCTL_MAIN_DATA_CTL);
		val |= DSI_MCTL_MAIN_DATA_CTL_IF1_MODE;
		ग_लिखोl(val, d->regs + DSI_MCTL_MAIN_DATA_CTL);

		/* Disable command mode on IF1 */
		val = पढ़ोl(d->regs + DSI_CMD_MODE_CTL);
		val &= ~DSI_CMD_MODE_CTL_IF1_LP_EN;
		ग_लिखोl(val, d->regs + DSI_CMD_MODE_CTL);

		/* Enable some error पूर्णांकerrupts */
		val = पढ़ोl(d->regs + DSI_VID_MODE_STS_CTL);
		val |= DSI_VID_MODE_STS_CTL_ERR_MISSING_VSYNC;
		val |= DSI_VID_MODE_STS_CTL_ERR_MISSING_DATA;
		ग_लिखोl(val, d->regs + DSI_VID_MODE_STS_CTL);

		/* Enable video mode */
		val = पढ़ोl(d->regs + DSI_MCTL_MAIN_DATA_CTL);
		val |= DSI_MCTL_MAIN_DATA_CTL_VID_EN;
		ग_लिखोl(val, d->regs + DSI_MCTL_MAIN_DATA_CTL);
	पूर्ण अन्यथा अणु
		/* Command mode, clear IF1 ID */
		val = पढ़ोl(d->regs + DSI_CMD_MODE_CTL);
		/*
		 * If we enable low-घातer mode here
		 * the display updates become really slow.
		 */
		अगर (d->mdsi->mode_flags & MIPI_DSI_MODE_LPM)
			val |= DSI_CMD_MODE_CTL_IF1_LP_EN;
		val &= ~DSI_CMD_MODE_CTL_IF1_ID_MASK;
		ग_लिखोl(val, d->regs + DSI_CMD_MODE_CTL);
	पूर्ण

	dev_info(d->dev, "enabled MCDE DSI master\n");
पूर्ण

अटल व्योम mcde_dsi_bridge_mode_set(काष्ठा drm_bridge *bridge,
				     स्थिर काष्ठा drm_display_mode *mode,
				     स्थिर काष्ठा drm_display_mode *adj)
अणु
	काष्ठा mcde_dsi *d = bridge_to_mcde_dsi(bridge);

	अगर (!d->mdsi) अणु
		dev_err(d->dev, "no DSI device attached to encoder!\n");
		वापस;
	पूर्ण

	d->mode = mode;

	dev_info(d->dev, "set DSI master to %dx%d %u Hz %s mode\n",
		 mode->hdisplay, mode->vdisplay, mode->घड़ी * 1000,
		 (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO) ? "VIDEO" : "CMD"
		);
पूर्ण

अटल व्योम mcde_dsi_रुको_क्रम_command_mode_stop(काष्ठा mcde_dsi *d)
अणु
	u32 val;
	पूर्णांक i;

	/*
	 * Wait until we get out of command mode
	 * CSM = Command State Machine
	 */
	i = 0;
	val = DSI_CMD_MODE_STS_CSM_RUNNING;
	जबतक ((पढ़ोl(d->regs + DSI_CMD_MODE_STS) & val) == val) अणु
		/* Sleep क्रम a millisecond */
		usleep_range(1000, 2000);
		अगर (i++ == 100) अणु
			dev_warn(d->dev,
				 "could not get out of command mode\n");
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mcde_dsi_रुको_क्रम_video_mode_stop(काष्ठा mcde_dsi *d)
अणु
	u32 val;
	पूर्णांक i;

	/* Wait until we get out og video mode */
	i = 0;
	val = DSI_VID_MODE_STS_VSG_RUNNING;
	जबतक ((पढ़ोl(d->regs + DSI_VID_MODE_STS) & val) == val) अणु
		/* Sleep क्रम a millisecond */
		usleep_range(1000, 2000);
		अगर (i++ == 100) अणु
			dev_warn(d->dev,
				 "could not get out of video mode\n");
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Notice that this is called from inside the display controller
 * and not from the bridge callbacks.
 */
व्योम mcde_dsi_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा mcde_dsi *d = bridge_to_mcde_dsi(bridge);
	u32 val;

	अगर (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO) अणु
		/* Stop video mode */
		val = पढ़ोl(d->regs + DSI_MCTL_MAIN_DATA_CTL);
		val &= ~DSI_MCTL_MAIN_DATA_CTL_VID_EN;
		ग_लिखोl(val, d->regs + DSI_MCTL_MAIN_DATA_CTL);
		mcde_dsi_रुको_क्रम_video_mode_stop(d);
	पूर्ण अन्यथा अणु
		/* Stop command mode */
		mcde_dsi_रुको_क्रम_command_mode_stop(d);
	पूर्ण

	/*
	 * Stop घड़ीs and terminate any DSI traffic here so the panel can
	 * send commands to shut करोwn the display using DSI direct ग_लिखो until
	 * this poपूर्णांक.
	 */

	/* Disable all error पूर्णांकerrupts */
	ग_लिखोl(0, d->regs + DSI_VID_MODE_STS_CTL);
	clk_disable_unprepare(d->hs_clk);
	clk_disable_unprepare(d->lp_clk);
पूर्ण

अटल पूर्णांक mcde_dsi_bridge_attach(काष्ठा drm_bridge *bridge,
				  क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा mcde_dsi *d = bridge_to_mcde_dsi(bridge);
	काष्ठा drm_device *drm = bridge->dev;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(drm, DRIVER_ATOMIC)) अणु
		dev_err(d->dev, "we need atomic updates\n");
		वापस -ENOTSUPP;
	पूर्ण

	/* Attach the DSI bridge to the output (panel etc) bridge */
	ret = drm_bridge_attach(bridge->encoder, d->bridge_out, bridge, flags);
	अगर (ret) अणु
		dev_err(d->dev, "failed to attach the DSI bridge\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs mcde_dsi_bridge_funcs = अणु
	.attach = mcde_dsi_bridge_attach,
	.mode_set = mcde_dsi_bridge_mode_set,
पूर्ण;

अटल पूर्णांक mcde_dsi_bind(काष्ठा device *dev, काष्ठा device *master,
			 व्योम *data)
अणु
	काष्ठा drm_device *drm = data;
	काष्ठा mcde *mcde = to_mcde(drm);
	काष्ठा mcde_dsi *d = dev_get_drvdata(dev);
	काष्ठा device_node *child;
	काष्ठा drm_panel *panel = शून्य;
	काष्ठा drm_bridge *bridge = शून्य;

	अगर (!of_get_available_child_count(dev->of_node)) अणु
		dev_info(dev, "unused DSI interface\n");
		d->unused = true;
		वापस 0;
	पूर्ण
	d->mcde = mcde;
	/* If the display attached beक्रमe binding, set this up */
	अगर (d->mdsi)
		mcde_dsi_attach_to_mcde(d);

	/* Obtain the घड़ीs */
	d->hs_clk = devm_clk_get(dev, "hs");
	अगर (IS_ERR(d->hs_clk)) अणु
		dev_err(dev, "unable to get HS clock\n");
		वापस PTR_ERR(d->hs_clk);
	पूर्ण

	d->lp_clk = devm_clk_get(dev, "lp");
	अगर (IS_ERR(d->lp_clk)) अणु
		dev_err(dev, "unable to get LP clock\n");
		वापस PTR_ERR(d->lp_clk);
	पूर्ण

	/* Look क्रम a panel as a child to this node */
	क्रम_each_available_child_of_node(dev->of_node, child) अणु
		panel = of_drm_find_panel(child);
		अगर (IS_ERR(panel)) अणु
			dev_err(dev, "failed to find panel try bridge (%ld)\n",
				PTR_ERR(panel));
			panel = शून्य;

			bridge = of_drm_find_bridge(child);
			अगर (!bridge) अणु
				dev_err(dev, "failed to find bridge\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (panel) अणु
		bridge = drm_panel_bridge_add_typed(panel,
						    DRM_MODE_CONNECTOR_DSI);
		अगर (IS_ERR(bridge)) अणु
			dev_err(dev, "error adding panel bridge\n");
			वापस PTR_ERR(bridge);
		पूर्ण
		dev_info(dev, "connected to panel\n");
		d->panel = panel;
	पूर्ण अन्यथा अगर (bridge) अणु
		/* TODO: AV8100 HDMI encoder goes here क्रम example */
		dev_info(dev, "connected to non-panel bridge (unsupported)\n");
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		dev_err(dev, "no panel or bridge\n");
		वापस -ENODEV;
	पूर्ण

	d->bridge_out = bridge;

	/* Create a bridge क्रम this DSI channel */
	d->bridge.funcs = &mcde_dsi_bridge_funcs;
	d->bridge.of_node = dev->of_node;
	drm_bridge_add(&d->bridge);

	/* TODO: first come first serve, use a list */
	mcde->bridge = &d->bridge;

	dev_info(dev, "initialized MCDE DSI bridge\n");

	वापस 0;
पूर्ण

अटल व्योम mcde_dsi_unbind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	काष्ठा mcde_dsi *d = dev_get_drvdata(dev);

	अगर (d->panel)
		drm_panel_bridge_हटाओ(d->bridge_out);
	regmap_update_bits(d->prcmu, PRCM_DSI_SW_RESET,
			   PRCM_DSI_SW_RESET_DSI0_SW_RESETN, 0);
पूर्ण

अटल स्थिर काष्ठा component_ops mcde_dsi_component_ops = अणु
	.bind   = mcde_dsi_bind,
	.unbind = mcde_dsi_unbind,
पूर्ण;

अटल पूर्णांक mcde_dsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mcde_dsi *d;
	काष्ठा mipi_dsi_host *host;
	काष्ठा resource *res;
	u32 dsi_id;
	पूर्णांक ret;

	d = devm_kzalloc(dev, माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;
	d->dev = dev;
	platक्रमm_set_drvdata(pdev, d);

	/* Get a handle on the PRCMU so we can करो reset */
	d->prcmu =
		syscon_regmap_lookup_by_compatible("stericsson,db8500-prcmu");
	अगर (IS_ERR(d->prcmu)) अणु
		dev_err(dev, "no PRCMU regmap\n");
		वापस PTR_ERR(d->prcmu);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	d->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(d->regs)) अणु
		dev_err(dev, "no DSI regs\n");
		वापस PTR_ERR(d->regs);
	पूर्ण

	dsi_id = पढ़ोl(d->regs + DSI_ID_REG);
	dev_info(dev, "HW revision 0x%08x\n", dsi_id);

	host = &d->dsi_host;
	host->dev = dev;
	host->ops = &mcde_dsi_host_ops;
	ret = mipi_dsi_host_रेजिस्टर(host);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register DSI host: %d\n", ret);
		वापस ret;
	पूर्ण
	dev_info(dev, "registered DSI host\n");

	platक्रमm_set_drvdata(pdev, d);
	वापस component_add(dev, &mcde_dsi_component_ops);
पूर्ण

अटल पूर्णांक mcde_dsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mcde_dsi *d = platक्रमm_get_drvdata(pdev);

	component_del(&pdev->dev, &mcde_dsi_component_ops);
	mipi_dsi_host_unरेजिस्टर(&d->dsi_host);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mcde_dsi_of_match[] = अणु
	अणु
		.compatible = "ste,mcde-dsi",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

काष्ठा platक्रमm_driver mcde_dsi_driver = अणु
	.driver = अणु
		.name           = "mcde-dsi",
		.of_match_table = of_match_ptr(mcde_dsi_of_match),
	पूर्ण,
	.probe = mcde_dsi_probe,
	.हटाओ = mcde_dsi_हटाओ,
पूर्ण;
