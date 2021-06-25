<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 NVIDIA Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/host1x.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "dc.h"
#समावेश "drm.h"
#समावेश "dsi.h"
#समावेश "mipi-phy.h"
#समावेश "trace.h"

काष्ठा tegra_dsi_state अणु
	काष्ठा drm_connector_state base;

	काष्ठा mipi_dphy_timing timing;
	अचिन्हित दीर्घ period;

	अचिन्हित पूर्णांक vrefresh;
	अचिन्हित पूर्णांक lanes;
	अचिन्हित दीर्घ pclk;
	अचिन्हित दीर्घ bclk;

	क्रमागत tegra_dsi_क्रमmat क्रमmat;
	अचिन्हित पूर्णांक mul;
	अचिन्हित पूर्णांक भाग;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_dsi_state *
to_dsi_state(काष्ठा drm_connector_state *state)
अणु
	वापस container_of(state, काष्ठा tegra_dsi_state, base);
पूर्ण

काष्ठा tegra_dsi अणु
	काष्ठा host1x_client client;
	काष्ठा tegra_output output;
	काष्ठा device *dev;

	व्योम __iomem *regs;

	काष्ठा reset_control *rst;
	काष्ठा clk *clk_parent;
	काष्ठा clk *clk_lp;
	काष्ठा clk *clk;

	काष्ठा drm_info_list *debugfs_files;

	अचिन्हित दीर्घ flags;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	अचिन्हित पूर्णांक lanes;

	काष्ठा tegra_mipi_device *mipi;
	काष्ठा mipi_dsi_host host;

	काष्ठा regulator *vdd;

	अचिन्हित पूर्णांक video_fअगरo_depth;
	अचिन्हित पूर्णांक host_fअगरo_depth;

	/* क्रम ganged-mode support */
	काष्ठा tegra_dsi *master;
	काष्ठा tegra_dsi *slave;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_dsi *
host1x_client_to_dsi(काष्ठा host1x_client *client)
अणु
	वापस container_of(client, काष्ठा tegra_dsi, client);
पूर्ण

अटल अंतरभूत काष्ठा tegra_dsi *host_to_tegra(काष्ठा mipi_dsi_host *host)
अणु
	वापस container_of(host, काष्ठा tegra_dsi, host);
पूर्ण

अटल अंतरभूत काष्ठा tegra_dsi *to_dsi(काष्ठा tegra_output *output)
अणु
	वापस container_of(output, काष्ठा tegra_dsi, output);
पूर्ण

अटल काष्ठा tegra_dsi_state *tegra_dsi_get_state(काष्ठा tegra_dsi *dsi)
अणु
	वापस to_dsi_state(dsi->output.connector.state);
पूर्ण

अटल अंतरभूत u32 tegra_dsi_पढ़ोl(काष्ठा tegra_dsi *dsi, अचिन्हित पूर्णांक offset)
अणु
	u32 value = पढ़ोl(dsi->regs + (offset << 2));

	trace_dsi_पढ़ोl(dsi->dev, offset, value);

	वापस value;
पूर्ण

अटल अंतरभूत व्योम tegra_dsi_ग_लिखोl(काष्ठा tegra_dsi *dsi, u32 value,
				    अचिन्हित पूर्णांक offset)
अणु
	trace_dsi_ग_लिखोl(dsi->dev, offset, value);
	ग_लिखोl(value, dsi->regs + (offset << 2));
पूर्ण

#घोषणा DEBUGFS_REG32(_name) अणु .name = #_name, .offset = _name पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 tegra_dsi_regs[] = अणु
	DEBUGFS_REG32(DSI_INCR_SYNCPT),
	DEBUGFS_REG32(DSI_INCR_SYNCPT_CONTROL),
	DEBUGFS_REG32(DSI_INCR_SYNCPT_ERROR),
	DEBUGFS_REG32(DSI_CTXSW),
	DEBUGFS_REG32(DSI_RD_DATA),
	DEBUGFS_REG32(DSI_WR_DATA),
	DEBUGFS_REG32(DSI_POWER_CONTROL),
	DEBUGFS_REG32(DSI_INT_ENABLE),
	DEBUGFS_REG32(DSI_INT_STATUS),
	DEBUGFS_REG32(DSI_INT_MASK),
	DEBUGFS_REG32(DSI_HOST_CONTROL),
	DEBUGFS_REG32(DSI_CONTROL),
	DEBUGFS_REG32(DSI_SOL_DELAY),
	DEBUGFS_REG32(DSI_MAX_THRESHOLD),
	DEBUGFS_REG32(DSI_TRIGGER),
	DEBUGFS_REG32(DSI_TX_CRC),
	DEBUGFS_REG32(DSI_STATUS),
	DEBUGFS_REG32(DSI_INIT_SEQ_CONTROL),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_0),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_1),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_2),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_3),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_4),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_5),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_6),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_7),
	DEBUGFS_REG32(DSI_PKT_SEQ_0_LO),
	DEBUGFS_REG32(DSI_PKT_SEQ_0_HI),
	DEBUGFS_REG32(DSI_PKT_SEQ_1_LO),
	DEBUGFS_REG32(DSI_PKT_SEQ_1_HI),
	DEBUGFS_REG32(DSI_PKT_SEQ_2_LO),
	DEBUGFS_REG32(DSI_PKT_SEQ_2_HI),
	DEBUGFS_REG32(DSI_PKT_SEQ_3_LO),
	DEBUGFS_REG32(DSI_PKT_SEQ_3_HI),
	DEBUGFS_REG32(DSI_PKT_SEQ_4_LO),
	DEBUGFS_REG32(DSI_PKT_SEQ_4_HI),
	DEBUGFS_REG32(DSI_PKT_SEQ_5_LO),
	DEBUGFS_REG32(DSI_PKT_SEQ_5_HI),
	DEBUGFS_REG32(DSI_DCS_CMDS),
	DEBUGFS_REG32(DSI_PKT_LEN_0_1),
	DEBUGFS_REG32(DSI_PKT_LEN_2_3),
	DEBUGFS_REG32(DSI_PKT_LEN_4_5),
	DEBUGFS_REG32(DSI_PKT_LEN_6_7),
	DEBUGFS_REG32(DSI_PHY_TIMING_0),
	DEBUGFS_REG32(DSI_PHY_TIMING_1),
	DEBUGFS_REG32(DSI_PHY_TIMING_2),
	DEBUGFS_REG32(DSI_BTA_TIMING),
	DEBUGFS_REG32(DSI_TIMEOUT_0),
	DEBUGFS_REG32(DSI_TIMEOUT_1),
	DEBUGFS_REG32(DSI_TO_TALLY),
	DEBUGFS_REG32(DSI_PAD_CONTROL_0),
	DEBUGFS_REG32(DSI_PAD_CONTROL_CD),
	DEBUGFS_REG32(DSI_PAD_CD_STATUS),
	DEBUGFS_REG32(DSI_VIDEO_MODE_CONTROL),
	DEBUGFS_REG32(DSI_PAD_CONTROL_1),
	DEBUGFS_REG32(DSI_PAD_CONTROL_2),
	DEBUGFS_REG32(DSI_PAD_CONTROL_3),
	DEBUGFS_REG32(DSI_PAD_CONTROL_4),
	DEBUGFS_REG32(DSI_GANGED_MODE_CONTROL),
	DEBUGFS_REG32(DSI_GANGED_MODE_START),
	DEBUGFS_REG32(DSI_GANGED_MODE_SIZE),
	DEBUGFS_REG32(DSI_RAW_DATA_BYTE_COUNT),
	DEBUGFS_REG32(DSI_ULTRA_LOW_POWER_CONTROL),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_8),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_9),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_10),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_11),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_12),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_13),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_14),
	DEBUGFS_REG32(DSI_INIT_SEQ_DATA_15),
पूर्ण;

अटल पूर्णांक tegra_dsi_show_regs(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा tegra_dsi *dsi = node->info_ent->data;
	काष्ठा drm_crtc *crtc = dsi->output.encoder.crtc;
	काष्ठा drm_device *drm = node->minor->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	drm_modeset_lock_all(drm);

	अगर (!crtc || !crtc->state->active) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tegra_dsi_regs); i++) अणु
		अचिन्हित पूर्णांक offset = tegra_dsi_regs[i].offset;

		seq_म_लिखो(s, "%-32s %#05x %08x\n", tegra_dsi_regs[i].name,
			   offset, tegra_dsi_पढ़ोl(dsi, offset));
	पूर्ण

unlock:
	drm_modeset_unlock_all(drm);
	वापस err;
पूर्ण

अटल काष्ठा drm_info_list debugfs_files[] = अणु
	अणु "regs", tegra_dsi_show_regs, 0, शून्य पूर्ण,
पूर्ण;

अटल पूर्णांक tegra_dsi_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	अचिन्हित पूर्णांक i, count = ARRAY_SIZE(debugfs_files);
	काष्ठा drm_minor *minor = connector->dev->primary;
	काष्ठा dentry *root = connector->debugfs_entry;
	काष्ठा tegra_dsi *dsi = to_dsi(output);

	dsi->debugfs_files = kmemdup(debugfs_files, माप(debugfs_files),
				     GFP_KERNEL);
	अगर (!dsi->debugfs_files)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; i++)
		dsi->debugfs_files[i].data = dsi;

	drm_debugfs_create_files(dsi->debugfs_files, count, root, minor);

	वापस 0;
पूर्ण

अटल व्योम tegra_dsi_early_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	अचिन्हित पूर्णांक count = ARRAY_SIZE(debugfs_files);
	काष्ठा tegra_dsi *dsi = to_dsi(output);

	drm_debugfs_हटाओ_files(dsi->debugfs_files, count,
				 connector->dev->primary);
	kमुक्त(dsi->debugfs_files);
	dsi->debugfs_files = शून्य;
पूर्ण

#घोषणा PKT_ID0(id)	((((id) & 0x3f) <<  3) | (1 <<  9))
#घोषणा PKT_LEN0(len)	(((len) & 0x07) <<  0)
#घोषणा PKT_ID1(id)	((((id) & 0x3f) << 13) | (1 << 19))
#घोषणा PKT_LEN1(len)	(((len) & 0x07) << 10)
#घोषणा PKT_ID2(id)	((((id) & 0x3f) << 23) | (1 << 29))
#घोषणा PKT_LEN2(len)	(((len) & 0x07) << 20)

#घोषणा PKT_LP		(1 << 30)
#घोषणा NUM_PKT_SEQ	12

/*
 * non-burst mode with sync pulses
 */
अटल स्थिर u32 pkt_seq_video_non_burst_sync_pulses[NUM_PKT_SEQ] = अणु
	[ 0] = PKT_ID0(MIPI_DSI_V_SYNC_START) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_BLANKING_PACKET) | PKT_LEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_LEN2(0) |
	       PKT_LP,
	[ 1] = 0,
	[ 2] = PKT_ID0(MIPI_DSI_V_SYNC_END) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_BLANKING_PACKET) | PKT_LEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_LEN2(0) |
	       PKT_LP,
	[ 3] = 0,
	[ 4] = PKT_ID0(MIPI_DSI_H_SYNC_START) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_BLANKING_PACKET) | PKT_LEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_LEN2(0) |
	       PKT_LP,
	[ 5] = 0,
	[ 6] = PKT_ID0(MIPI_DSI_H_SYNC_START) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_BLANKING_PACKET) | PKT_LEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_LEN2(0),
	[ 7] = PKT_ID0(MIPI_DSI_BLANKING_PACKET) | PKT_LEN0(2) |
	       PKT_ID1(MIPI_DSI_PACKED_PIXEL_STREAM_24) | PKT_LEN1(3) |
	       PKT_ID2(MIPI_DSI_BLANKING_PACKET) | PKT_LEN2(4),
	[ 8] = PKT_ID0(MIPI_DSI_H_SYNC_START) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_BLANKING_PACKET) | PKT_LEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_LEN2(0) |
	       PKT_LP,
	[ 9] = 0,
	[10] = PKT_ID0(MIPI_DSI_H_SYNC_START) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_BLANKING_PACKET) | PKT_LEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_LEN2(0),
	[11] = PKT_ID0(MIPI_DSI_BLANKING_PACKET) | PKT_LEN0(2) |
	       PKT_ID1(MIPI_DSI_PACKED_PIXEL_STREAM_24) | PKT_LEN1(3) |
	       PKT_ID2(MIPI_DSI_BLANKING_PACKET) | PKT_LEN2(4),
पूर्ण;

/*
 * non-burst mode with sync events
 */
अटल स्थिर u32 pkt_seq_video_non_burst_sync_events[NUM_PKT_SEQ] = अणु
	[ 0] = PKT_ID0(MIPI_DSI_V_SYNC_START) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_END_OF_TRANSMISSION) | PKT_LEN1(7) |
	       PKT_LP,
	[ 1] = 0,
	[ 2] = PKT_ID0(MIPI_DSI_H_SYNC_START) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_END_OF_TRANSMISSION) | PKT_LEN1(7) |
	       PKT_LP,
	[ 3] = 0,
	[ 4] = PKT_ID0(MIPI_DSI_H_SYNC_START) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_END_OF_TRANSMISSION) | PKT_LEN1(7) |
	       PKT_LP,
	[ 5] = 0,
	[ 6] = PKT_ID0(MIPI_DSI_H_SYNC_START) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_BLANKING_PACKET) | PKT_LEN1(2) |
	       PKT_ID2(MIPI_DSI_PACKED_PIXEL_STREAM_24) | PKT_LEN2(3),
	[ 7] = PKT_ID0(MIPI_DSI_BLANKING_PACKET) | PKT_LEN0(4),
	[ 8] = PKT_ID0(MIPI_DSI_H_SYNC_START) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_END_OF_TRANSMISSION) | PKT_LEN1(7) |
	       PKT_LP,
	[ 9] = 0,
	[10] = PKT_ID0(MIPI_DSI_H_SYNC_START) | PKT_LEN0(0) |
	       PKT_ID1(MIPI_DSI_BLANKING_PACKET) | PKT_LEN1(2) |
	       PKT_ID2(MIPI_DSI_PACKED_PIXEL_STREAM_24) | PKT_LEN2(3),
	[11] = PKT_ID0(MIPI_DSI_BLANKING_PACKET) | PKT_LEN0(4),
पूर्ण;

अटल स्थिर u32 pkt_seq_command_mode[NUM_PKT_SEQ] = अणु
	[ 0] = 0,
	[ 1] = 0,
	[ 2] = 0,
	[ 3] = 0,
	[ 4] = 0,
	[ 5] = 0,
	[ 6] = PKT_ID0(MIPI_DSI_DCS_LONG_WRITE) | PKT_LEN0(3) | PKT_LP,
	[ 7] = 0,
	[ 8] = 0,
	[ 9] = 0,
	[10] = PKT_ID0(MIPI_DSI_DCS_LONG_WRITE) | PKT_LEN0(5) | PKT_LP,
	[11] = 0,
पूर्ण;

अटल व्योम tegra_dsi_set_phy_timing(काष्ठा tegra_dsi *dsi,
				     अचिन्हित दीर्घ period,
				     स्थिर काष्ठा mipi_dphy_timing *timing)
अणु
	u32 value;

	value = DSI_TIMING_FIELD(timing->hsनिकास, period, 1) << 24 |
		DSI_TIMING_FIELD(timing->hstrail, period, 0) << 16 |
		DSI_TIMING_FIELD(timing->hszero, period, 3) << 8 |
		DSI_TIMING_FIELD(timing->hsprepare, period, 1);
	tegra_dsi_ग_लिखोl(dsi, value, DSI_PHY_TIMING_0);

	value = DSI_TIMING_FIELD(timing->clktrail, period, 1) << 24 |
		DSI_TIMING_FIELD(timing->clkpost, period, 1) << 16 |
		DSI_TIMING_FIELD(timing->clkzero, period, 1) << 8 |
		DSI_TIMING_FIELD(timing->lpx, period, 1);
	tegra_dsi_ग_लिखोl(dsi, value, DSI_PHY_TIMING_1);

	value = DSI_TIMING_FIELD(timing->clkprepare, period, 1) << 16 |
		DSI_TIMING_FIELD(timing->clkpre, period, 1) << 8 |
		DSI_TIMING_FIELD(0xff * period, period, 0) << 0;
	tegra_dsi_ग_लिखोl(dsi, value, DSI_PHY_TIMING_2);

	value = DSI_TIMING_FIELD(timing->taget, period, 1) << 16 |
		DSI_TIMING_FIELD(timing->tasure, period, 1) << 8 |
		DSI_TIMING_FIELD(timing->tago, period, 1);
	tegra_dsi_ग_लिखोl(dsi, value, DSI_BTA_TIMING);

	अगर (dsi->slave)
		tegra_dsi_set_phy_timing(dsi->slave, period, timing);
पूर्ण

अटल पूर्णांक tegra_dsi_get_muद_भाग(क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat,
				अचिन्हित पूर्णांक *mulp, अचिन्हित पूर्णांक *भागp)
अणु
	चयन (क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB666_PACKED:
	हाल MIPI_DSI_FMT_RGB888:
		*mulp = 3;
		*भागp = 1;
		अवरोध;

	हाल MIPI_DSI_FMT_RGB565:
		*mulp = 2;
		*भागp = 1;
		अवरोध;

	हाल MIPI_DSI_FMT_RGB666:
		*mulp = 9;
		*भागp = 4;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dsi_get_क्रमmat(क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat,
				क्रमागत tegra_dsi_क्रमmat *fmt)
अणु
	चयन (क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB888:
		*fmt = TEGRA_DSI_FORMAT_24P;
		अवरोध;

	हाल MIPI_DSI_FMT_RGB666:
		*fmt = TEGRA_DSI_FORMAT_18NP;
		अवरोध;

	हाल MIPI_DSI_FMT_RGB666_PACKED:
		*fmt = TEGRA_DSI_FORMAT_18P;
		अवरोध;

	हाल MIPI_DSI_FMT_RGB565:
		*fmt = TEGRA_DSI_FORMAT_16P;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_dsi_ganged_enable(काष्ठा tegra_dsi *dsi, अचिन्हित पूर्णांक start,
				    अचिन्हित पूर्णांक size)
अणु
	u32 value;

	tegra_dsi_ग_लिखोl(dsi, start, DSI_GANGED_MODE_START);
	tegra_dsi_ग_लिखोl(dsi, size << 16 | size, DSI_GANGED_MODE_SIZE);

	value = DSI_GANGED_MODE_CONTROL_ENABLE;
	tegra_dsi_ग_लिखोl(dsi, value, DSI_GANGED_MODE_CONTROL);
पूर्ण

अटल व्योम tegra_dsi_enable(काष्ठा tegra_dsi *dsi)
अणु
	u32 value;

	value = tegra_dsi_पढ़ोl(dsi, DSI_POWER_CONTROL);
	value |= DSI_POWER_CONTROL_ENABLE;
	tegra_dsi_ग_लिखोl(dsi, value, DSI_POWER_CONTROL);

	अगर (dsi->slave)
		tegra_dsi_enable(dsi->slave);
पूर्ण

अटल अचिन्हित पूर्णांक tegra_dsi_get_lanes(काष्ठा tegra_dsi *dsi)
अणु
	अगर (dsi->master)
		वापस dsi->master->lanes + dsi->lanes;

	अगर (dsi->slave)
		वापस dsi->lanes + dsi->slave->lanes;

	वापस dsi->lanes;
पूर्ण

अटल व्योम tegra_dsi_configure(काष्ठा tegra_dsi *dsi, अचिन्हित पूर्णांक pipe,
				स्थिर काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक hact, hsw, hbp, hfp, i, mul, भाग;
	काष्ठा tegra_dsi_state *state;
	स्थिर u32 *pkt_seq;
	u32 value;

	/* XXX: pass in state पूर्णांकo this function? */
	अगर (dsi->master)
		state = tegra_dsi_get_state(dsi->master);
	अन्यथा
		state = tegra_dsi_get_state(dsi);

	mul = state->mul;
	भाग = state->भाग;

	अगर (dsi->flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE) अणु
		DRM_DEBUG_KMS("Non-burst video mode with sync pulses\n");
		pkt_seq = pkt_seq_video_non_burst_sync_pulses;
	पूर्ण अन्यथा अगर (dsi->flags & MIPI_DSI_MODE_VIDEO) अणु
		DRM_DEBUG_KMS("Non-burst video mode with sync events\n");
		pkt_seq = pkt_seq_video_non_burst_sync_events;
	पूर्ण अन्यथा अणु
		DRM_DEBUG_KMS("Command mode\n");
		pkt_seq = pkt_seq_command_mode;
	पूर्ण

	value = DSI_CONTROL_CHANNEL(0) |
		DSI_CONTROL_FORMAT(state->क्रमmat) |
		DSI_CONTROL_LANES(dsi->lanes - 1) |
		DSI_CONTROL_SOURCE(pipe);
	tegra_dsi_ग_लिखोl(dsi, value, DSI_CONTROL);

	tegra_dsi_ग_लिखोl(dsi, dsi->video_fअगरo_depth, DSI_MAX_THRESHOLD);

	value = DSI_HOST_CONTROL_HS;
	tegra_dsi_ग_लिखोl(dsi, value, DSI_HOST_CONTROL);

	value = tegra_dsi_पढ़ोl(dsi, DSI_CONTROL);

	अगर (dsi->flags & MIPI_DSI_CLOCK_NON_CONTINUOUS)
		value |= DSI_CONTROL_HS_CLK_CTRL;

	value &= ~DSI_CONTROL_TX_TRIG(3);

	/* enable DCS commands क्रम command mode */
	अगर (dsi->flags & MIPI_DSI_MODE_VIDEO)
		value &= ~DSI_CONTROL_DCS_ENABLE;
	अन्यथा
		value |= DSI_CONTROL_DCS_ENABLE;

	value |= DSI_CONTROL_VIDEO_ENABLE;
	value &= ~DSI_CONTROL_HOST_ENABLE;
	tegra_dsi_ग_लिखोl(dsi, value, DSI_CONTROL);

	क्रम (i = 0; i < NUM_PKT_SEQ; i++)
		tegra_dsi_ग_लिखोl(dsi, pkt_seq[i], DSI_PKT_SEQ_0_LO + i);

	अगर (dsi->flags & MIPI_DSI_MODE_VIDEO) अणु
		/* horizontal active pixels */
		hact = mode->hdisplay * mul / भाग;

		/* horizontal sync width */
		hsw = (mode->hsync_end - mode->hsync_start) * mul / भाग;

		/* horizontal back porch */
		hbp = (mode->htotal - mode->hsync_end) * mul / भाग;

		अगर ((dsi->flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE) == 0)
			hbp += hsw;

		/* horizontal front porch */
		hfp = (mode->hsync_start - mode->hdisplay) * mul / भाग;

		/* subtract packet overhead */
		hsw -= 10;
		hbp -= 14;
		hfp -= 8;

		tegra_dsi_ग_लिखोl(dsi, hsw << 16 | 0, DSI_PKT_LEN_0_1);
		tegra_dsi_ग_लिखोl(dsi, hact << 16 | hbp, DSI_PKT_LEN_2_3);
		tegra_dsi_ग_लिखोl(dsi, hfp, DSI_PKT_LEN_4_5);
		tegra_dsi_ग_लिखोl(dsi, 0x0f0f << 16, DSI_PKT_LEN_6_7);

		/* set SOL delay (क्रम non-burst mode only) */
		tegra_dsi_ग_लिखोl(dsi, 8 * mul / भाग, DSI_SOL_DELAY);

		/* TODO: implement ganged mode */
	पूर्ण अन्यथा अणु
		u16 bytes;

		अगर (dsi->master || dsi->slave) अणु
			/*
			 * For ganged mode, assume symmetric left-right mode.
			 */
			bytes = 1 + (mode->hdisplay / 2) * mul / भाग;
		पूर्ण अन्यथा अणु
			/* 1 byte (DCS command) + pixel data */
			bytes = 1 + mode->hdisplay * mul / भाग;
		पूर्ण

		tegra_dsi_ग_लिखोl(dsi, 0, DSI_PKT_LEN_0_1);
		tegra_dsi_ग_लिखोl(dsi, bytes << 16, DSI_PKT_LEN_2_3);
		tegra_dsi_ग_लिखोl(dsi, bytes << 16, DSI_PKT_LEN_4_5);
		tegra_dsi_ग_लिखोl(dsi, 0, DSI_PKT_LEN_6_7);

		value = MIPI_DCS_WRITE_MEMORY_START << 8 |
			MIPI_DCS_WRITE_MEMORY_CONTINUE;
		tegra_dsi_ग_लिखोl(dsi, value, DSI_DCS_CMDS);

		/* set SOL delay */
		अगर (dsi->master || dsi->slave) अणु
			अचिन्हित दीर्घ delay, bclk, bclk_ganged;
			अचिन्हित पूर्णांक lanes = state->lanes;

			/* SOL to valid, valid to FIFO and FIFO ग_लिखो delay */
			delay = 4 + 4 + 2;
			delay = DIV_ROUND_UP(delay * mul, भाग * lanes);
			/* FIFO पढ़ो delay */
			delay = delay + 6;

			bclk = DIV_ROUND_UP(mode->htotal * mul, भाग * lanes);
			bclk_ganged = DIV_ROUND_UP(bclk * lanes / 2, lanes);
			value = bclk - bclk_ganged + delay + 20;
		पूर्ण अन्यथा अणु
			/* TODO: revisit क्रम non-ganged mode */
			value = 8 * mul / भाग;
		पूर्ण

		tegra_dsi_ग_लिखोl(dsi, value, DSI_SOL_DELAY);
	पूर्ण

	अगर (dsi->slave) अणु
		tegra_dsi_configure(dsi->slave, pipe, mode);

		/*
		 * TODO: Support modes other than symmetrical left-right
		 * split.
		 */
		tegra_dsi_ganged_enable(dsi, 0, mode->hdisplay / 2);
		tegra_dsi_ganged_enable(dsi->slave, mode->hdisplay / 2,
					mode->hdisplay / 2);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_dsi_रुको_idle(काष्ठा tegra_dsi *dsi, अचिन्हित दीर्घ समयout)
अणु
	u32 value;

	समयout = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_dsi_पढ़ोl(dsi, DSI_STATUS);
		अगर (value & DSI_STATUS_IDLE)
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम tegra_dsi_video_disable(काष्ठा tegra_dsi *dsi)
अणु
	u32 value;

	value = tegra_dsi_पढ़ोl(dsi, DSI_CONTROL);
	value &= ~DSI_CONTROL_VIDEO_ENABLE;
	tegra_dsi_ग_लिखोl(dsi, value, DSI_CONTROL);

	अगर (dsi->slave)
		tegra_dsi_video_disable(dsi->slave);
पूर्ण

अटल व्योम tegra_dsi_ganged_disable(काष्ठा tegra_dsi *dsi)
अणु
	tegra_dsi_ग_लिखोl(dsi, 0, DSI_GANGED_MODE_START);
	tegra_dsi_ग_लिखोl(dsi, 0, DSI_GANGED_MODE_SIZE);
	tegra_dsi_ग_लिखोl(dsi, 0, DSI_GANGED_MODE_CONTROL);
पूर्ण

अटल पूर्णांक tegra_dsi_pad_enable(काष्ठा tegra_dsi *dsi)
अणु
	u32 value;

	value = DSI_PAD_CONTROL_VS1_PULLDN(0) | DSI_PAD_CONTROL_VS1_PDIO(0);
	tegra_dsi_ग_लिखोl(dsi, value, DSI_PAD_CONTROL_0);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dsi_pad_calibrate(काष्ठा tegra_dsi *dsi)
अणु
	u32 value;
	पूर्णांक err;

	/*
	 * XXX Is this still needed? The module reset is deनिश्चितed right
	 * beक्रमe this function is called.
	 */
	tegra_dsi_ग_लिखोl(dsi, 0, DSI_PAD_CONTROL_0);
	tegra_dsi_ग_लिखोl(dsi, 0, DSI_PAD_CONTROL_1);
	tegra_dsi_ग_लिखोl(dsi, 0, DSI_PAD_CONTROL_2);
	tegra_dsi_ग_लिखोl(dsi, 0, DSI_PAD_CONTROL_3);
	tegra_dsi_ग_लिखोl(dsi, 0, DSI_PAD_CONTROL_4);

	/* start calibration */
	tegra_dsi_pad_enable(dsi);

	value = DSI_PAD_SLEW_UP(0x7) | DSI_PAD_SLEW_DN(0x7) |
		DSI_PAD_LP_UP(0x1) | DSI_PAD_LP_DN(0x1) |
		DSI_PAD_OUT_CLK(0x0);
	tegra_dsi_ग_लिखोl(dsi, value, DSI_PAD_CONTROL_2);

	value = DSI_PAD_PREEMP_PD_CLK(0x3) | DSI_PAD_PREEMP_PU_CLK(0x3) |
		DSI_PAD_PREEMP_PD(0x03) | DSI_PAD_PREEMP_PU(0x3);
	tegra_dsi_ग_लिखोl(dsi, value, DSI_PAD_CONTROL_3);

	err = tegra_mipi_start_calibration(dsi->mipi);
	अगर (err < 0)
		वापस err;

	वापस tegra_mipi_finish_calibration(dsi->mipi);
पूर्ण

अटल व्योम tegra_dsi_set_समयout(काष्ठा tegra_dsi *dsi, अचिन्हित दीर्घ bclk,
				  अचिन्हित पूर्णांक vrefresh)
अणु
	अचिन्हित पूर्णांक समयout;
	u32 value;

	/* one frame high-speed transmission समयout */
	समयout = (bclk / vrefresh) / 512;
	value = DSI_TIMEOUT_LRX(0x2000) | DSI_TIMEOUT_HTX(समयout);
	tegra_dsi_ग_लिखोl(dsi, value, DSI_TIMEOUT_0);

	/* 2 ms peripheral समयout क्रम panel */
	समयout = 2 * bclk / 512 * 1000;
	value = DSI_TIMEOUT_PR(समयout) | DSI_TIMEOUT_TA(0x2000);
	tegra_dsi_ग_लिखोl(dsi, value, DSI_TIMEOUT_1);

	value = DSI_TALLY_TA(0) | DSI_TALLY_LRX(0) | DSI_TALLY_HTX(0);
	tegra_dsi_ग_लिखोl(dsi, value, DSI_TO_TALLY);

	अगर (dsi->slave)
		tegra_dsi_set_समयout(dsi->slave, bclk, vrefresh);
पूर्ण

अटल व्योम tegra_dsi_disable(काष्ठा tegra_dsi *dsi)
अणु
	u32 value;

	अगर (dsi->slave) अणु
		tegra_dsi_ganged_disable(dsi->slave);
		tegra_dsi_ganged_disable(dsi);
	पूर्ण

	value = tegra_dsi_पढ़ोl(dsi, DSI_POWER_CONTROL);
	value &= ~DSI_POWER_CONTROL_ENABLE;
	tegra_dsi_ग_लिखोl(dsi, value, DSI_POWER_CONTROL);

	अगर (dsi->slave)
		tegra_dsi_disable(dsi->slave);

	usleep_range(5000, 10000);
पूर्ण

अटल व्योम tegra_dsi_soft_reset(काष्ठा tegra_dsi *dsi)
अणु
	u32 value;

	value = tegra_dsi_पढ़ोl(dsi, DSI_POWER_CONTROL);
	value &= ~DSI_POWER_CONTROL_ENABLE;
	tegra_dsi_ग_लिखोl(dsi, value, DSI_POWER_CONTROL);

	usleep_range(300, 1000);

	value = tegra_dsi_पढ़ोl(dsi, DSI_POWER_CONTROL);
	value |= DSI_POWER_CONTROL_ENABLE;
	tegra_dsi_ग_लिखोl(dsi, value, DSI_POWER_CONTROL);

	usleep_range(300, 1000);

	value = tegra_dsi_पढ़ोl(dsi, DSI_TRIGGER);
	अगर (value)
		tegra_dsi_ग_लिखोl(dsi, 0, DSI_TRIGGER);

	अगर (dsi->slave)
		tegra_dsi_soft_reset(dsi->slave);
पूर्ण

अटल व्योम tegra_dsi_connector_reset(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_dsi_state *state = kzalloc(माप(*state), GFP_KERNEL);

	अगर (!state)
		वापस;

	अगर (connector->state) अणु
		__drm_atomic_helper_connector_destroy_state(connector->state);
		kमुक्त(connector->state);
	पूर्ण

	__drm_atomic_helper_connector_reset(connector, &state->base);
पूर्ण

अटल काष्ठा drm_connector_state *
tegra_dsi_connector_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_dsi_state *state = to_dsi_state(connector->state);
	काष्ठा tegra_dsi_state *copy;

	copy = kmemdup(state, माप(*state), GFP_KERNEL);
	अगर (!copy)
		वापस शून्य;

	__drm_atomic_helper_connector_duplicate_state(connector,
						      &copy->base);

	वापस &copy->base;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs tegra_dsi_connector_funcs = अणु
	.reset = tegra_dsi_connector_reset,
	.detect = tegra_output_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = tegra_output_connector_destroy,
	.atomic_duplicate_state = tegra_dsi_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.late_रेजिस्टर = tegra_dsi_late_रेजिस्टर,
	.early_unरेजिस्टर = tegra_dsi_early_unरेजिस्टर,
पूर्ण;

अटल क्रमागत drm_mode_status
tegra_dsi_connector_mode_valid(काष्ठा drm_connector *connector,
			       काष्ठा drm_display_mode *mode)
अणु
	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs tegra_dsi_connector_helper_funcs = अणु
	.get_modes = tegra_output_connector_get_modes,
	.mode_valid = tegra_dsi_connector_mode_valid,
पूर्ण;

अटल व्योम tegra_dsi_unprepare(काष्ठा tegra_dsi *dsi)
अणु
	पूर्णांक err;

	अगर (dsi->slave)
		tegra_dsi_unprepare(dsi->slave);

	err = tegra_mipi_disable(dsi->mipi);
	अगर (err < 0)
		dev_err(dsi->dev, "failed to disable MIPI calibration: %d\n",
			err);

	err = host1x_client_suspend(&dsi->client);
	अगर (err < 0)
		dev_err(dsi->dev, "failed to suspend: %d\n", err);
पूर्ण

अटल व्योम tegra_dsi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_dc *dc = to_tegra_dc(encoder->crtc);
	काष्ठा tegra_dsi *dsi = to_dsi(output);
	u32 value;
	पूर्णांक err;

	अगर (output->panel)
		drm_panel_disable(output->panel);

	tegra_dsi_video_disable(dsi);

	/*
	 * The following accesses रेजिस्टरs of the display controller, so make
	 * sure it's only executed when the output is attached to one.
	 */
	अगर (dc) अणु
		value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_WIN_OPTIONS);
		value &= ~DSI_ENABLE;
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_WIN_OPTIONS);

		tegra_dc_commit(dc);
	पूर्ण

	err = tegra_dsi_रुको_idle(dsi, 100);
	अगर (err < 0)
		dev_dbg(dsi->dev, "failed to idle DSI: %d\n", err);

	tegra_dsi_soft_reset(dsi);

	अगर (output->panel)
		drm_panel_unprepare(output->panel);

	tegra_dsi_disable(dsi);

	tegra_dsi_unprepare(dsi);
पूर्ण

अटल पूर्णांक tegra_dsi_prepare(काष्ठा tegra_dsi *dsi)
अणु
	पूर्णांक err;

	err = host1x_client_resume(&dsi->client);
	अगर (err < 0) अणु
		dev_err(dsi->dev, "failed to resume: %d\n", err);
		वापस err;
	पूर्ण

	err = tegra_mipi_enable(dsi->mipi);
	अगर (err < 0)
		dev_err(dsi->dev, "failed to enable MIPI calibration: %d\n",
			err);

	err = tegra_dsi_pad_calibrate(dsi);
	अगर (err < 0)
		dev_err(dsi->dev, "MIPI calibration failed: %d\n", err);

	अगर (dsi->slave)
		tegra_dsi_prepare(dsi->slave);

	वापस 0;
पूर्ण

अटल व्योम tegra_dsi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_dc *dc = to_tegra_dc(encoder->crtc);
	काष्ठा tegra_dsi *dsi = to_dsi(output);
	काष्ठा tegra_dsi_state *state;
	u32 value;
	पूर्णांक err;

	err = tegra_dsi_prepare(dsi);
	अगर (err < 0) अणु
		dev_err(dsi->dev, "failed to prepare: %d\n", err);
		वापस;
	पूर्ण

	state = tegra_dsi_get_state(dsi);

	tegra_dsi_set_समयout(dsi, state->bclk, state->vrefresh);

	/*
	 * The D-PHY timing fields are expressed in byte-घड़ी cycles, so
	 * multiply the period by 8.
	 */
	tegra_dsi_set_phy_timing(dsi, state->period * 8, &state->timing);

	अगर (output->panel)
		drm_panel_prepare(output->panel);

	tegra_dsi_configure(dsi, dc->pipe, mode);

	/* enable display controller */
	value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_WIN_OPTIONS);
	value |= DSI_ENABLE;
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_WIN_OPTIONS);

	tegra_dc_commit(dc);

	/* enable DSI controller */
	tegra_dsi_enable(dsi);

	अगर (output->panel)
		drm_panel_enable(output->panel);
पूर्ण

अटल पूर्णांक
tegra_dsi_encoder_atomic_check(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_crtc_state *crtc_state,
			       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_dsi_state *state = to_dsi_state(conn_state);
	काष्ठा tegra_dc *dc = to_tegra_dc(conn_state->crtc);
	काष्ठा tegra_dsi *dsi = to_dsi(output);
	अचिन्हित पूर्णांक scभाग;
	अचिन्हित दीर्घ plld;
	पूर्णांक err;

	state->pclk = crtc_state->mode.घड़ी * 1000;

	err = tegra_dsi_get_muद_भाग(dsi->क्रमmat, &state->mul, &state->भाग);
	अगर (err < 0)
		वापस err;

	state->lanes = tegra_dsi_get_lanes(dsi);

	err = tegra_dsi_get_क्रमmat(dsi->क्रमmat, &state->क्रमmat);
	अगर (err < 0)
		वापस err;

	state->vrefresh = drm_mode_vrefresh(&crtc_state->mode);

	/* compute byte घड़ी */
	state->bclk = (state->pclk * state->mul) / (state->भाग * state->lanes);

	DRM_DEBUG_KMS("mul: %u, div: %u, lanes: %u\n", state->mul, state->भाग,
		      state->lanes);
	DRM_DEBUG_KMS("format: %u, vrefresh: %u\n", state->क्रमmat,
		      state->vrefresh);
	DRM_DEBUG_KMS("bclk: %lu\n", state->bclk);

	/*
	 * Compute bit घड़ी and round up to the next MHz.
	 */
	plld = DIV_ROUND_UP(state->bclk * 8, USEC_PER_SEC) * USEC_PER_SEC;
	state->period = DIV_ROUND_CLOSEST(NSEC_PER_SEC, plld);

	err = mipi_dphy_timing_get_शेष(&state->timing, state->period);
	अगर (err < 0)
		वापस err;

	err = mipi_dphy_timing_validate(&state->timing, state->period);
	अगर (err < 0) अणु
		dev_err(dsi->dev, "failed to validate D-PHY timing: %d\n", err);
		वापस err;
	पूर्ण

	/*
	 * We भागide the frequency by two here, but we make up क्रम that by
	 * setting the shअगरt घड़ी भागider (further below) to half of the
	 * correct value.
	 */
	plld /= 2;

	/*
	 * Derive pixel घड़ी from bit घड़ी using the shअगरt घड़ी भागider.
	 * Note that this is only half of what we would expect, but we need
	 * that to make up क्रम the fact that we भागided the bit घड़ी by a
	 * factor of two above.
	 *
	 * It's not clear exactly why this is necessary, but the display is
	 * not working properly otherwise. Perhaps the PLLs cannot generate
	 * frequencies sufficiently high.
	 */
	scभाग = ((8 * state->mul) / (state->भाग * state->lanes)) - 2;

	err = tegra_dc_state_setup_घड़ी(dc, crtc_state, dsi->clk_parent,
					 plld, scभाग);
	अगर (err < 0) अणु
		dev_err(output->dev, "failed to setup CRTC state: %d\n", err);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs tegra_dsi_encoder_helper_funcs = अणु
	.disable = tegra_dsi_encoder_disable,
	.enable = tegra_dsi_encoder_enable,
	.atomic_check = tegra_dsi_encoder_atomic_check,
पूर्ण;

अटल पूर्णांक tegra_dsi_init(काष्ठा host1x_client *client)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(client->host);
	काष्ठा tegra_dsi *dsi = host1x_client_to_dsi(client);
	पूर्णांक err;

	/* Gangsters must not रेजिस्टर their own outमाला_दो. */
	अगर (!dsi->master) अणु
		dsi->output.dev = client->dev;

		drm_connector_init(drm, &dsi->output.connector,
				   &tegra_dsi_connector_funcs,
				   DRM_MODE_CONNECTOR_DSI);
		drm_connector_helper_add(&dsi->output.connector,
					 &tegra_dsi_connector_helper_funcs);
		dsi->output.connector.dpms = DRM_MODE_DPMS_OFF;

		drm_simple_encoder_init(drm, &dsi->output.encoder,
					DRM_MODE_ENCODER_DSI);
		drm_encoder_helper_add(&dsi->output.encoder,
				       &tegra_dsi_encoder_helper_funcs);

		drm_connector_attach_encoder(&dsi->output.connector,
						  &dsi->output.encoder);
		drm_connector_रेजिस्टर(&dsi->output.connector);

		err = tegra_output_init(drm, &dsi->output);
		अगर (err < 0)
			dev_err(dsi->dev, "failed to initialize output: %d\n",
				err);

		dsi->output.encoder.possible_crtcs = 0x3;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dsi_निकास(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_dsi *dsi = host1x_client_to_dsi(client);

	tegra_output_निकास(&dsi->output);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dsi_runसमय_suspend(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_dsi *dsi = host1x_client_to_dsi(client);
	काष्ठा device *dev = client->dev;
	पूर्णांक err;

	अगर (dsi->rst) अणु
		err = reset_control_निश्चित(dsi->rst);
		अगर (err < 0) अणु
			dev_err(dev, "failed to assert reset: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	usleep_range(1000, 2000);

	clk_disable_unprepare(dsi->clk_lp);
	clk_disable_unprepare(dsi->clk);

	regulator_disable(dsi->vdd);
	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dsi_runसमय_resume(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_dsi *dsi = host1x_client_to_dsi(client);
	काष्ठा device *dev = client->dev;
	पूर्णांक err;

	err = pm_runसमय_resume_and_get(dev);
	अगर (err < 0) अणु
		dev_err(dev, "failed to get runtime PM: %d\n", err);
		वापस err;
	पूर्ण

	err = regulator_enable(dsi->vdd);
	अगर (err < 0) अणु
		dev_err(dev, "failed to enable VDD supply: %d\n", err);
		जाओ put_rpm;
	पूर्ण

	err = clk_prepare_enable(dsi->clk);
	अगर (err < 0) अणु
		dev_err(dev, "cannot enable DSI clock: %d\n", err);
		जाओ disable_vdd;
	पूर्ण

	err = clk_prepare_enable(dsi->clk_lp);
	अगर (err < 0) अणु
		dev_err(dev, "cannot enable low-power clock: %d\n", err);
		जाओ disable_clk;
	पूर्ण

	usleep_range(1000, 2000);

	अगर (dsi->rst) अणु
		err = reset_control_deनिश्चित(dsi->rst);
		अगर (err < 0) अणु
			dev_err(dev, "cannot assert reset: %d\n", err);
			जाओ disable_clk_lp;
		पूर्ण
	पूर्ण

	वापस 0;

disable_clk_lp:
	clk_disable_unprepare(dsi->clk_lp);
disable_clk:
	clk_disable_unprepare(dsi->clk);
disable_vdd:
	regulator_disable(dsi->vdd);
put_rpm:
	pm_runसमय_put_sync(dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा host1x_client_ops dsi_client_ops = अणु
	.init = tegra_dsi_init,
	.निकास = tegra_dsi_निकास,
	.suspend = tegra_dsi_runसमय_suspend,
	.resume = tegra_dsi_runसमय_resume,
पूर्ण;

अटल पूर्णांक tegra_dsi_setup_घड़ीs(काष्ठा tegra_dsi *dsi)
अणु
	काष्ठा clk *parent;
	पूर्णांक err;

	parent = clk_get_parent(dsi->clk);
	अगर (!parent)
		वापस -EINVAL;

	err = clk_set_parent(parent, dsi->clk_parent);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर error_report[16] = अणु
	"SoT Error",
	"SoT Sync Error",
	"EoT Sync Error",
	"Escape Mode Entry Command Error",
	"Low-Power Transmit Sync Error",
	"Peripheral Timeout Error",
	"False Control Error",
	"Contention Detected",
	"ECC Error, single-bit",
	"ECC Error, multi-bit",
	"Checksum Error",
	"DSI Data Type Not Recognized",
	"DSI VC ID Invalid",
	"Invalid Transmission Length",
	"Reserved",
	"DSI Protocol Violation",
पूर्ण;

अटल sमाप_प्रकार tegra_dsi_पढ़ो_response(काष्ठा tegra_dsi *dsi,
				       स्थिर काष्ठा mipi_dsi_msg *msg,
				       माप_प्रकार count)
अणु
	u8 *rx = msg->rx_buf;
	अचिन्हित पूर्णांक i, j, k;
	माप_प्रकार size = 0;
	u16 errors;
	u32 value;

	/* पढ़ो and parse packet header */
	value = tegra_dsi_पढ़ोl(dsi, DSI_RD_DATA);

	चयन (value & 0x3f) अणु
	हाल MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT:
		errors = (value >> 8) & 0xffff;
		dev_dbg(dsi->dev, "Acknowledge and error report: %04x\n",
			errors);
		क्रम (i = 0; i < ARRAY_SIZE(error_report); i++)
			अगर (errors & BIT(i))
				dev_dbg(dsi->dev, "  %2u: %s\n", i,
					error_report[i]);
		अवरोध;

	हाल MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE:
		rx[0] = (value >> 8) & 0xff;
		size = 1;
		अवरोध;

	हाल MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE:
		rx[0] = (value >>  8) & 0xff;
		rx[1] = (value >> 16) & 0xff;
		size = 2;
		अवरोध;

	हाल MIPI_DSI_RX_DCS_LONG_READ_RESPONSE:
		size = ((value >> 8) & 0xff00) | ((value >> 8) & 0xff);
		अवरोध;

	हाल MIPI_DSI_RX_GENERIC_LONG_READ_RESPONSE:
		size = ((value >> 8) & 0xff00) | ((value >> 8) & 0xff);
		अवरोध;

	शेष:
		dev_err(dsi->dev, "unhandled response type: %02x\n",
			value & 0x3f);
		वापस -EPROTO;
	पूर्ण

	size = min(size, msg->rx_len);

	अगर (msg->rx_buf && size > 0) अणु
		क्रम (i = 0, j = 0; i < count - 1; i++, j += 4) अणु
			u8 *rx = msg->rx_buf + j;

			value = tegra_dsi_पढ़ोl(dsi, DSI_RD_DATA);

			क्रम (k = 0; k < 4 && (j + k) < msg->rx_len; k++)
				rx[j + k] = (value >> (k << 3)) & 0xff;
		पूर्ण
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक tegra_dsi_transmit(काष्ठा tegra_dsi *dsi, अचिन्हित दीर्घ समयout)
अणु
	tegra_dsi_ग_लिखोl(dsi, DSI_TRIGGER_HOST, DSI_TRIGGER);

	समयout = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		u32 value = tegra_dsi_पढ़ोl(dsi, DSI_TRIGGER);
		अगर ((value & DSI_TRIGGER_HOST) == 0)
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण

	DRM_DEBUG_KMS("timeout waiting for transmission to complete\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक tegra_dsi_रुको_क्रम_response(काष्ठा tegra_dsi *dsi,
				       अचिन्हित दीर्घ समयout)
अणु
	समयout = jअगरfies + msecs_to_jअगरfies(250);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		u32 value = tegra_dsi_पढ़ोl(dsi, DSI_STATUS);
		u8 count = value & 0x1f;

		अगर (count > 0)
			वापस count;

		usleep_range(1000, 2000);
	पूर्ण

	DRM_DEBUG_KMS("peripheral returned no data\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम tegra_dsi_ग_लिखोsl(काष्ठा tegra_dsi *dsi, अचिन्हित दीर्घ offset,
			      स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	स्थिर u8 *buf = buffer;
	माप_प्रकार i, j;
	u32 value;

	क्रम (j = 0; j < size; j += 4) अणु
		value = 0;

		क्रम (i = 0; i < 4 && j + i < size; i++)
			value |= buf[j + i] << (i << 3);

		tegra_dsi_ग_लिखोl(dsi, value, DSI_WR_DATA);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार tegra_dsi_host_transfer(काष्ठा mipi_dsi_host *host,
				       स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा tegra_dsi *dsi = host_to_tegra(host);
	काष्ठा mipi_dsi_packet packet;
	स्थिर u8 *header;
	माप_प्रकार count;
	sमाप_प्रकार err;
	u32 value;

	err = mipi_dsi_create_packet(&packet, msg);
	अगर (err < 0)
		वापस err;

	header = packet.header;

	/* maximum FIFO depth is 1920 words */
	अगर (packet.size > dsi->video_fअगरo_depth * 4)
		वापस -ENOSPC;

	/* reset underflow/overflow flags */
	value = tegra_dsi_पढ़ोl(dsi, DSI_STATUS);
	अगर (value & (DSI_STATUS_UNDERFLOW | DSI_STATUS_OVERFLOW)) अणु
		value = DSI_HOST_CONTROL_FIFO_RESET;
		tegra_dsi_ग_लिखोl(dsi, value, DSI_HOST_CONTROL);
		usleep_range(10, 20);
	पूर्ण

	value = tegra_dsi_पढ़ोl(dsi, DSI_POWER_CONTROL);
	value |= DSI_POWER_CONTROL_ENABLE;
	tegra_dsi_ग_लिखोl(dsi, value, DSI_POWER_CONTROL);

	usleep_range(5000, 10000);

	value = DSI_HOST_CONTROL_CRC_RESET | DSI_HOST_CONTROL_TX_TRIG_HOST |
		DSI_HOST_CONTROL_CS | DSI_HOST_CONTROL_ECC;

	अगर ((msg->flags & MIPI_DSI_MSG_USE_LPM) == 0)
		value |= DSI_HOST_CONTROL_HS;

	/*
	 * The host FIFO has a maximum of 64 words, so larger transmissions
	 * need to use the video FIFO.
	 */
	अगर (packet.size > dsi->host_fअगरo_depth * 4)
		value |= DSI_HOST_CONTROL_FIFO_SEL;

	tegra_dsi_ग_लिखोl(dsi, value, DSI_HOST_CONTROL);

	/*
	 * For पढ़ोs and messages with explicitly requested ACK, generate a
	 * BTA sequence after the transmission of the packet.
	 */
	अगर ((msg->flags & MIPI_DSI_MSG_REQ_ACK) ||
	    (msg->rx_buf && msg->rx_len > 0)) अणु
		value = tegra_dsi_पढ़ोl(dsi, DSI_HOST_CONTROL);
		value |= DSI_HOST_CONTROL_PKT_BTA;
		tegra_dsi_ग_लिखोl(dsi, value, DSI_HOST_CONTROL);
	पूर्ण

	value = DSI_CONTROL_LANES(0) | DSI_CONTROL_HOST_ENABLE;
	tegra_dsi_ग_लिखोl(dsi, value, DSI_CONTROL);

	/* ग_लिखो packet header, ECC is generated by hardware */
	value = header[2] << 16 | header[1] << 8 | header[0];
	tegra_dsi_ग_लिखोl(dsi, value, DSI_WR_DATA);

	/* ग_लिखो payload (अगर any) */
	अगर (packet.payload_length > 0)
		tegra_dsi_ग_लिखोsl(dsi, DSI_WR_DATA, packet.payload,
				  packet.payload_length);

	err = tegra_dsi_transmit(dsi, 250);
	अगर (err < 0)
		वापस err;

	अगर ((msg->flags & MIPI_DSI_MSG_REQ_ACK) ||
	    (msg->rx_buf && msg->rx_len > 0)) अणु
		err = tegra_dsi_रुको_क्रम_response(dsi, 250);
		अगर (err < 0)
			वापस err;

		count = err;

		value = tegra_dsi_पढ़ोl(dsi, DSI_RD_DATA);
		चयन (value) अणु
		हाल 0x84:
			/*
			dev_dbg(dsi->dev, "ACK\n");
			*/
			अवरोध;

		हाल 0x87:
			/*
			dev_dbg(dsi->dev, "ESCAPE\n");
			*/
			अवरोध;

		शेष:
			dev_err(dsi->dev, "unknown status: %08x\n", value);
			अवरोध;
		पूर्ण

		अगर (count > 1) अणु
			err = tegra_dsi_पढ़ो_response(dsi, msg, count);
			अगर (err < 0)
				dev_err(dsi->dev,
					"failed to parse response: %zd\n",
					err);
			अन्यथा अणु
				/*
				 * For पढ़ो commands, वापस the number of
				 * bytes वापसed by the peripheral.
				 */
				count = err;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * For ग_लिखो commands, we have transmitted the 4-byte header
		 * plus the variable-length payload.
		 */
		count = 4 + packet.payload_length;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक tegra_dsi_ganged_setup(काष्ठा tegra_dsi *dsi)
अणु
	काष्ठा clk *parent;
	पूर्णांक err;

	/* make sure both DSI controllers share the same PLL */
	parent = clk_get_parent(dsi->slave->clk);
	अगर (!parent)
		वापस -EINVAL;

	err = clk_set_parent(parent, dsi->clk_parent);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dsi_host_attach(काष्ठा mipi_dsi_host *host,
				 काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा tegra_dsi *dsi = host_to_tegra(host);

	dsi->flags = device->mode_flags;
	dsi->क्रमmat = device->क्रमmat;
	dsi->lanes = device->lanes;

	अगर (dsi->slave) अणु
		पूर्णांक err;

		dev_dbg(dsi->dev, "attaching dual-channel device %s\n",
			dev_name(&device->dev));

		err = tegra_dsi_ganged_setup(dsi);
		अगर (err < 0) अणु
			dev_err(dsi->dev, "failed to set up ganged mode: %d\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण

	/*
	 * Slaves करोn't have a panel associated with them, so they provide
	 * merely the second channel.
	 */
	अगर (!dsi->master) अणु
		काष्ठा tegra_output *output = &dsi->output;

		output->panel = of_drm_find_panel(device->dev.of_node);
		अगर (IS_ERR(output->panel))
			output->panel = शून्य;

		अगर (output->panel && output->connector.dev)
			drm_helper_hpd_irq_event(output->connector.dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dsi_host_detach(काष्ठा mipi_dsi_host *host,
				 काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा tegra_dsi *dsi = host_to_tegra(host);
	काष्ठा tegra_output *output = &dsi->output;

	अगर (output->panel && &device->dev == output->panel->dev) अणु
		output->panel = शून्य;

		अगर (output->connector.dev)
			drm_helper_hpd_irq_event(output->connector.dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops tegra_dsi_host_ops = अणु
	.attach = tegra_dsi_host_attach,
	.detach = tegra_dsi_host_detach,
	.transfer = tegra_dsi_host_transfer,
पूर्ण;

अटल पूर्णांक tegra_dsi_ganged_probe(काष्ठा tegra_dsi *dsi)
अणु
	काष्ठा device_node *np;

	np = of_parse_phandle(dsi->dev->of_node, "nvidia,ganged-mode", 0);
	अगर (np) अणु
		काष्ठा platक्रमm_device *gangster = of_find_device_by_node(np);

		dsi->slave = platक्रमm_get_drvdata(gangster);
		of_node_put(np);

		अगर (!dsi->slave)
			वापस -EPROBE_DEFER;

		dsi->slave->master = dsi;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_dsi *dsi;
	काष्ठा resource *regs;
	पूर्णांक err;

	dsi = devm_kzalloc(&pdev->dev, माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस -ENOMEM;

	dsi->output.dev = dsi->dev = &pdev->dev;
	dsi->video_fअगरo_depth = 1920;
	dsi->host_fअगरo_depth = 64;

	err = tegra_dsi_ganged_probe(dsi);
	अगर (err < 0)
		वापस err;

	err = tegra_output_probe(&dsi->output);
	अगर (err < 0)
		वापस err;

	dsi->output.connector.polled = DRM_CONNECTOR_POLL_HPD;

	/*
	 * Assume these values by शेष. When a DSI peripheral driver
	 * attaches to the DSI host, the parameters will be taken from
	 * the attached device.
	 */
	dsi->flags = MIPI_DSI_MODE_VIDEO;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->lanes = 4;

	अगर (!pdev->dev.pm_करोमुख्य) अणु
		dsi->rst = devm_reset_control_get(&pdev->dev, "dsi");
		अगर (IS_ERR(dsi->rst))
			वापस PTR_ERR(dsi->rst);
	पूर्ण

	dsi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dsi->clk)) अणु
		dev_err(&pdev->dev, "cannot get DSI clock\n");
		वापस PTR_ERR(dsi->clk);
	पूर्ण

	dsi->clk_lp = devm_clk_get(&pdev->dev, "lp");
	अगर (IS_ERR(dsi->clk_lp)) अणु
		dev_err(&pdev->dev, "cannot get low-power clock\n");
		वापस PTR_ERR(dsi->clk_lp);
	पूर्ण

	dsi->clk_parent = devm_clk_get(&pdev->dev, "parent");
	अगर (IS_ERR(dsi->clk_parent)) अणु
		dev_err(&pdev->dev, "cannot get parent clock\n");
		वापस PTR_ERR(dsi->clk_parent);
	पूर्ण

	dsi->vdd = devm_regulator_get(&pdev->dev, "avdd-dsi-csi");
	अगर (IS_ERR(dsi->vdd)) अणु
		dev_err(&pdev->dev, "cannot get VDD supply\n");
		वापस PTR_ERR(dsi->vdd);
	पूर्ण

	err = tegra_dsi_setup_घड़ीs(dsi);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "cannot setup clocks\n");
		वापस err;
	पूर्ण

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dsi->regs = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(dsi->regs))
		वापस PTR_ERR(dsi->regs);

	dsi->mipi = tegra_mipi_request(&pdev->dev, pdev->dev.of_node);
	अगर (IS_ERR(dsi->mipi))
		वापस PTR_ERR(dsi->mipi);

	dsi->host.ops = &tegra_dsi_host_ops;
	dsi->host.dev = &pdev->dev;

	err = mipi_dsi_host_रेजिस्टर(&dsi->host);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register DSI host: %d\n", err);
		जाओ mipi_मुक्त;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dsi);
	pm_runसमय_enable(&pdev->dev);

	INIT_LIST_HEAD(&dsi->client.list);
	dsi->client.ops = &dsi_client_ops;
	dsi->client.dev = &pdev->dev;

	err = host1x_client_रेजिस्टर(&dsi->client);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register host1x client: %d\n",
			err);
		जाओ unरेजिस्टर;
	पूर्ण

	वापस 0;

unरेजिस्टर:
	mipi_dsi_host_unरेजिस्टर(&dsi->host);
mipi_मुक्त:
	tegra_mipi_मुक्त(dsi->mipi);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_dsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_dsi *dsi = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	pm_runसमय_disable(&pdev->dev);

	err = host1x_client_unरेजिस्टर(&dsi->client);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		वापस err;
	पूर्ण

	tegra_output_हटाओ(&dsi->output);

	mipi_dsi_host_unरेजिस्टर(&dsi->host);
	tegra_mipi_मुक्त(dsi->mipi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_dsi_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-dsi", पूर्ण,
	अणु .compatible = "nvidia,tegra132-dsi", पूर्ण,
	अणु .compatible = "nvidia,tegra124-dsi", पूर्ण,
	अणु .compatible = "nvidia,tegra114-dsi", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_dsi_of_match);

काष्ठा platक्रमm_driver tegra_dsi_driver = अणु
	.driver = अणु
		.name = "tegra-dsi",
		.of_match_table = tegra_dsi_of_match,
	पूर्ण,
	.probe = tegra_dsi_probe,
	.हटाओ = tegra_dsi_हटाओ,
पूर्ण;
