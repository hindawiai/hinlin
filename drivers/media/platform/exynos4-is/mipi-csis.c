<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung S5P/EXYNOS SoC series MIPI-CSI receiver driver
 *
 * Copyright (C) 2011 - 2013 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memory.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/videodev2.h>
#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "mipi-csis.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-2)");

/* Register map definition */

/* CSIS global control */
#घोषणा S5PCSIS_CTRL			0x00
#घोषणा S5PCSIS_CTRL_DPDN_DEFAULT	(0 << 31)
#घोषणा S5PCSIS_CTRL_DPDN_SWAP		(1UL << 31)
#घोषणा S5PCSIS_CTRL_ALIGN_32BIT	(1 << 20)
#घोषणा S5PCSIS_CTRL_UPDATE_SHADOW	(1 << 16)
#घोषणा S5PCSIS_CTRL_WCLK_EXTCLK	(1 << 8)
#घोषणा S5PCSIS_CTRL_RESET		(1 << 4)
#घोषणा S5PCSIS_CTRL_ENABLE		(1 << 0)

/* D-PHY control */
#घोषणा S5PCSIS_DPHYCTRL		0x04
#घोषणा S5PCSIS_DPHYCTRL_HSS_MASK	(0x1f << 27)
#घोषणा S5PCSIS_DPHYCTRL_ENABLE		(0x1f << 0)

#घोषणा S5PCSIS_CONFIG			0x08
#घोषणा S5PCSIS_CFG_FMT_YCBCR422_8BIT	(0x1e << 2)
#घोषणा S5PCSIS_CFG_FMT_RAW8		(0x2a << 2)
#घोषणा S5PCSIS_CFG_FMT_RAW10		(0x2b << 2)
#घोषणा S5PCSIS_CFG_FMT_RAW12		(0x2c << 2)
/* User defined क्रमmats, x = 1...4 */
#घोषणा S5PCSIS_CFG_FMT_USER(x)		((0x30 + x - 1) << 2)
#घोषणा S5PCSIS_CFG_FMT_MASK		(0x3f << 2)
#घोषणा S5PCSIS_CFG_NR_LANE_MASK	3

/* Interrupt mask */
#घोषणा S5PCSIS_INTMSK			0x10
#घोषणा S5PCSIS_INTMSK_EVEN_BEFORE	(1UL << 31)
#घोषणा S5PCSIS_INTMSK_EVEN_AFTER	(1 << 30)
#घोषणा S5PCSIS_INTMSK_ODD_BEFORE	(1 << 29)
#घोषणा S5PCSIS_INTMSK_ODD_AFTER	(1 << 28)
#घोषणा S5PCSIS_INTMSK_FRAME_START	(1 << 27)
#घोषणा S5PCSIS_INTMSK_FRAME_END	(1 << 26)
#घोषणा S5PCSIS_INTMSK_ERR_SOT_HS	(1 << 12)
#घोषणा S5PCSIS_INTMSK_ERR_LOST_FS	(1 << 5)
#घोषणा S5PCSIS_INTMSK_ERR_LOST_FE	(1 << 4)
#घोषणा S5PCSIS_INTMSK_ERR_OVER		(1 << 3)
#घोषणा S5PCSIS_INTMSK_ERR_ECC		(1 << 2)
#घोषणा S5PCSIS_INTMSK_ERR_CRC		(1 << 1)
#घोषणा S5PCSIS_INTMSK_ERR_UNKNOWN	(1 << 0)
#घोषणा S5PCSIS_INTMSK_EXYNOS4_EN_ALL	0xf000103f
#घोषणा S5PCSIS_INTMSK_EXYNOS5_EN_ALL	0xfc00103f

/* Interrupt source */
#घोषणा S5PCSIS_INTSRC			0x14
#घोषणा S5PCSIS_INTSRC_EVEN_BEFORE	(1UL << 31)
#घोषणा S5PCSIS_INTSRC_EVEN_AFTER	(1 << 30)
#घोषणा S5PCSIS_INTSRC_EVEN		(0x3 << 30)
#घोषणा S5PCSIS_INTSRC_ODD_BEFORE	(1 << 29)
#घोषणा S5PCSIS_INTSRC_ODD_AFTER	(1 << 28)
#घोषणा S5PCSIS_INTSRC_ODD		(0x3 << 28)
#घोषणा S5PCSIS_INTSRC_NON_IMAGE_DATA	(0xf << 28)
#घोषणा S5PCSIS_INTSRC_FRAME_START	(1 << 27)
#घोषणा S5PCSIS_INTSRC_FRAME_END	(1 << 26)
#घोषणा S5PCSIS_INTSRC_ERR_SOT_HS	(0xf << 12)
#घोषणा S5PCSIS_INTSRC_ERR_LOST_FS	(1 << 5)
#घोषणा S5PCSIS_INTSRC_ERR_LOST_FE	(1 << 4)
#घोषणा S5PCSIS_INTSRC_ERR_OVER		(1 << 3)
#घोषणा S5PCSIS_INTSRC_ERR_ECC		(1 << 2)
#घोषणा S5PCSIS_INTSRC_ERR_CRC		(1 << 1)
#घोषणा S5PCSIS_INTSRC_ERR_UNKNOWN	(1 << 0)
#घोषणा S5PCSIS_INTSRC_ERRORS		0xf03f

/* Pixel resolution */
#घोषणा S5PCSIS_RESOL			0x2c
#घोषणा CSIS_MAX_PIX_WIDTH		0xffff
#घोषणा CSIS_MAX_PIX_HEIGHT		0xffff

/* Non-image packet data buffers */
#घोषणा S5PCSIS_PKTDATA_ODD		0x2000
#घोषणा S5PCSIS_PKTDATA_EVEN		0x3000
#घोषणा S5PCSIS_PKTDATA_SIZE		SZ_4K

क्रमागत अणु
	CSIS_CLK_MUX,
	CSIS_CLK_GATE,
पूर्ण;

अटल अक्षर *csi_घड़ी_name[] = अणु
	[CSIS_CLK_MUX]  = "sclk_csis",
	[CSIS_CLK_GATE] = "csis",
पूर्ण;
#घोषणा NUM_CSIS_CLOCKS	ARRAY_SIZE(csi_घड़ी_name)
#घोषणा DEFAULT_SCLK_CSIS_FREQ	166000000UL

अटल स्थिर अक्षर * स्थिर csis_supply_name[] = अणु
	"vddcore",  /* CSIS Core (1.0V, 1.1V or 1.2V) suppply */
	"vddio",    /* CSIS I/O and PLL (1.8V) supply */
पूर्ण;
#घोषणा CSIS_NUM_SUPPLIES ARRAY_SIZE(csis_supply_name)

क्रमागत अणु
	ST_POWERED	= 1,
	ST_STREAMING	= 2,
	ST_SUSPENDED	= 4,
पूर्ण;

काष्ठा s5pcsis_event अणु
	u32 mask;
	स्थिर अक्षर * स्थिर name;
	अचिन्हित पूर्णांक counter;
पूर्ण;

अटल स्थिर काष्ठा s5pcsis_event s5pcsis_events[] = अणु
	/* Errors */
	अणु S5PCSIS_INTSRC_ERR_SOT_HS,	"SOT Error" पूर्ण,
	अणु S5PCSIS_INTSRC_ERR_LOST_FS,	"Lost Frame Start Error" पूर्ण,
	अणु S5PCSIS_INTSRC_ERR_LOST_FE,	"Lost Frame End Error" पूर्ण,
	अणु S5PCSIS_INTSRC_ERR_OVER,	"FIFO Overflow Error" पूर्ण,
	अणु S5PCSIS_INTSRC_ERR_ECC,	"ECC Error" पूर्ण,
	अणु S5PCSIS_INTSRC_ERR_CRC,	"CRC Error" पूर्ण,
	अणु S5PCSIS_INTSRC_ERR_UNKNOWN,	"Unknown Error" पूर्ण,
	/* Non-image data receive events */
	अणु S5PCSIS_INTSRC_EVEN_BEFORE,	"Non-image data before even frame" पूर्ण,
	अणु S5PCSIS_INTSRC_EVEN_AFTER,	"Non-image data after even frame" पूर्ण,
	अणु S5PCSIS_INTSRC_ODD_BEFORE,	"Non-image data before odd frame" पूर्ण,
	अणु S5PCSIS_INTSRC_ODD_AFTER,	"Non-image data after odd frame" पूर्ण,
	/* Frame start/end */
	अणु S5PCSIS_INTSRC_FRAME_START,	"Frame Start" पूर्ण,
	अणु S5PCSIS_INTSRC_FRAME_END,	"Frame End" पूर्ण,
पूर्ण;
#घोषणा S5PCSIS_NUM_EVENTS ARRAY_SIZE(s5pcsis_events)

काष्ठा csis_pktbuf अणु
	u32 *data;
	अचिन्हित पूर्णांक len;
पूर्ण;

काष्ठा csis_drvdata अणु
	/* Mask of all used पूर्णांकerrupts in S5PCSIS_INTMSK रेजिस्टर */
	u32 पूर्णांकerrupt_mask;
पूर्ण;

/**
 * काष्ठा csis_state - the driver's पूर्णांकernal state data काष्ठाure
 * @lock: mutex serializing the subdev and घातer management operations,
 *        protecting @क्रमmat and @flags members
 * @pads: CSIS pads array
 * @sd: v4l2_subdev associated with CSIS device instance
 * @index: the hardware instance index
 * @pdev: CSIS platक्रमm device
 * @phy: poपूर्णांकer to the CSIS generic PHY
 * @regs: mmapped I/O रेजिस्टरs memory
 * @supplies: CSIS regulator supplies
 * @घड़ी: CSIS घड़ीs
 * @irq: requested s5p-mipi-csis irq number
 * @पूर्णांकerrupt_mask: पूर्णांकerrupt mask of the all used पूर्णांकerrupts
 * @flags: the state variable क्रम घातer and streaming control
 * @clk_frequency: device bus घड़ी frequency
 * @hs_settle: HS-RX settle समय
 * @num_lanes: number of MIPI-CSI data lanes used
 * @max_num_lanes: maximum number of MIPI-CSI data lanes supported
 * @wclk_ext: CSI wrapper घड़ी: 0 - bus घड़ी, 1 - बाह्यal SCLK_CAM
 * @csis_fmt: current CSIS pixel क्रमmat
 * @क्रमmat: common media bus क्रमmat क्रम the source and sink pad
 * @slock: spinlock protecting काष्ठाure members below
 * @pkt_buf: the frame embedded (non-image) data buffer
 * @events: MIPI-CSIS event (error) counters
 */
काष्ठा csis_state अणु
	काष्ठा mutex lock;
	काष्ठा media_pad pads[CSIS_PADS_NUM];
	काष्ठा v4l2_subdev sd;
	u8 index;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा phy *phy;
	व्योम __iomem *regs;
	काष्ठा regulator_bulk_data supplies[CSIS_NUM_SUPPLIES];
	काष्ठा clk *घड़ी[NUM_CSIS_CLOCKS];
	पूर्णांक irq;
	u32 पूर्णांकerrupt_mask;
	u32 flags;

	u32 clk_frequency;
	u32 hs_settle;
	u32 num_lanes;
	u32 max_num_lanes;
	u8 wclk_ext;

	स्थिर काष्ठा csis_pix_क्रमmat *csis_fmt;
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	spinlock_t slock;
	काष्ठा csis_pktbuf pkt_buf;
	काष्ठा s5pcsis_event events[S5PCSIS_NUM_EVENTS];
पूर्ण;

/**
 * काष्ठा csis_pix_क्रमmat - CSIS pixel क्रमmat description
 * @pix_width_alignment: horizontal pixel alignment, width will be
 *                       multiple of 2^pix_width_alignment
 * @code: corresponding media bus code
 * @fmt_reg: S5PCSIS_CONFIG रेजिस्टर value
 * @data_alignment: MIPI-CSI data alignment in bits
 */
काष्ठा csis_pix_क्रमmat अणु
	अचिन्हित पूर्णांक pix_width_alignment;
	u32 code;
	u32 fmt_reg;
	u8 data_alignment;
पूर्ण;

अटल स्थिर काष्ठा csis_pix_क्रमmat s5pcsis_क्रमmats[] = अणु
	अणु
		.code = MEDIA_BUS_FMT_VYUY8_2X8,
		.fmt_reg = S5PCSIS_CFG_FMT_YCBCR422_8BIT,
		.data_alignment = 32,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_JPEG_1X8,
		.fmt_reg = S5PCSIS_CFG_FMT_USER(1),
		.data_alignment = 32,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8,
		.fmt_reg = S5PCSIS_CFG_FMT_USER(1),
		.data_alignment = 32,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SGRBG8_1X8,
		.fmt_reg = S5PCSIS_CFG_FMT_RAW8,
		.data_alignment = 24,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SGRBG10_1X10,
		.fmt_reg = S5PCSIS_CFG_FMT_RAW10,
		.data_alignment = 24,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SGRBG12_1X12,
		.fmt_reg = S5PCSIS_CFG_FMT_RAW12,
		.data_alignment = 24,
	पूर्ण
पूर्ण;

#घोषणा s5pcsis_ग_लिखो(__csis, __r, __v) ग_लिखोl(__v, __csis->regs + __r)
#घोषणा s5pcsis_पढ़ो(__csis, __r) पढ़ोl(__csis->regs + __r)

अटल काष्ठा csis_state *sd_to_csis_state(काष्ठा v4l2_subdev *sdev)
अणु
	वापस container_of(sdev, काष्ठा csis_state, sd);
पूर्ण

अटल स्थिर काष्ठा csis_pix_क्रमmat *find_csis_क्रमmat(
	काष्ठा v4l2_mbus_framefmt *mf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(s5pcsis_क्रमmats); i++)
		अगर (mf->code == s5pcsis_क्रमmats[i].code)
			वापस &s5pcsis_क्रमmats[i];
	वापस शून्य;
पूर्ण

अटल व्योम s5pcsis_enable_पूर्णांकerrupts(काष्ठा csis_state *state, bool on)
अणु
	u32 val = s5pcsis_पढ़ो(state, S5PCSIS_INTMSK);
	अगर (on)
		val |= state->पूर्णांकerrupt_mask;
	अन्यथा
		val &= ~state->पूर्णांकerrupt_mask;
	s5pcsis_ग_लिखो(state, S5PCSIS_INTMSK, val);
पूर्ण

अटल व्योम s5pcsis_reset(काष्ठा csis_state *state)
अणु
	u32 val = s5pcsis_पढ़ो(state, S5PCSIS_CTRL);

	s5pcsis_ग_लिखो(state, S5PCSIS_CTRL, val | S5PCSIS_CTRL_RESET);
	udelay(10);
पूर्ण

अटल व्योम s5pcsis_प्रणाली_enable(काष्ठा csis_state *state, पूर्णांक on)
अणु
	u32 val, mask;

	val = s5pcsis_पढ़ो(state, S5PCSIS_CTRL);
	अगर (on)
		val |= S5PCSIS_CTRL_ENABLE;
	अन्यथा
		val &= ~S5PCSIS_CTRL_ENABLE;
	s5pcsis_ग_लिखो(state, S5PCSIS_CTRL, val);

	val = s5pcsis_पढ़ो(state, S5PCSIS_DPHYCTRL);
	val &= ~S5PCSIS_DPHYCTRL_ENABLE;
	अगर (on) अणु
		mask = (1 << (state->num_lanes + 1)) - 1;
		val |= (mask & S5PCSIS_DPHYCTRL_ENABLE);
	पूर्ण
	s5pcsis_ग_लिखो(state, S5PCSIS_DPHYCTRL, val);
पूर्ण

/* Called with the state.lock mutex held */
अटल व्योम __s5pcsis_set_क्रमmat(काष्ठा csis_state *state)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &state->क्रमmat;
	u32 val;

	v4l2_dbg(1, debug, &state->sd, "fmt: %#x, %d x %d\n",
		 mf->code, mf->width, mf->height);

	/* Color क्रमmat */
	val = s5pcsis_पढ़ो(state, S5PCSIS_CONFIG);
	val = (val & ~S5PCSIS_CFG_FMT_MASK) | state->csis_fmt->fmt_reg;
	s5pcsis_ग_लिखो(state, S5PCSIS_CONFIG, val);

	/* Pixel resolution */
	val = (mf->width << 16) | mf->height;
	s5pcsis_ग_लिखो(state, S5PCSIS_RESOL, val);
पूर्ण

अटल व्योम s5pcsis_set_hsync_settle(काष्ठा csis_state *state, पूर्णांक settle)
अणु
	u32 val = s5pcsis_पढ़ो(state, S5PCSIS_DPHYCTRL);

	val = (val & ~S5PCSIS_DPHYCTRL_HSS_MASK) | (settle << 27);
	s5pcsis_ग_लिखो(state, S5PCSIS_DPHYCTRL, val);
पूर्ण

अटल व्योम s5pcsis_set_params(काष्ठा csis_state *state)
अणु
	u32 val;

	val = s5pcsis_पढ़ो(state, S5PCSIS_CONFIG);
	val = (val & ~S5PCSIS_CFG_NR_LANE_MASK) | (state->num_lanes - 1);
	s5pcsis_ग_लिखो(state, S5PCSIS_CONFIG, val);

	__s5pcsis_set_क्रमmat(state);
	s5pcsis_set_hsync_settle(state, state->hs_settle);

	val = s5pcsis_पढ़ो(state, S5PCSIS_CTRL);
	अगर (state->csis_fmt->data_alignment == 32)
		val |= S5PCSIS_CTRL_ALIGN_32BIT;
	अन्यथा /* 24-bits */
		val &= ~S5PCSIS_CTRL_ALIGN_32BIT;

	val &= ~S5PCSIS_CTRL_WCLK_EXTCLK;
	अगर (state->wclk_ext)
		val |= S5PCSIS_CTRL_WCLK_EXTCLK;
	s5pcsis_ग_लिखो(state, S5PCSIS_CTRL, val);

	/* Update the shaकरोw रेजिस्टर. */
	val = s5pcsis_पढ़ो(state, S5PCSIS_CTRL);
	s5pcsis_ग_लिखो(state, S5PCSIS_CTRL, val | S5PCSIS_CTRL_UPDATE_SHADOW);
पूर्ण

अटल व्योम s5pcsis_clk_put(काष्ठा csis_state *state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_CSIS_CLOCKS; i++) अणु
		अगर (IS_ERR(state->घड़ी[i]))
			जारी;
		clk_unprepare(state->घड़ी[i]);
		clk_put(state->घड़ी[i]);
		state->घड़ी[i] = ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल पूर्णांक s5pcsis_clk_get(काष्ठा csis_state *state)
अणु
	काष्ठा device *dev = &state->pdev->dev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < NUM_CSIS_CLOCKS; i++)
		state->घड़ी[i] = ERR_PTR(-EINVAL);

	क्रम (i = 0; i < NUM_CSIS_CLOCKS; i++) अणु
		state->घड़ी[i] = clk_get(dev, csi_घड़ी_name[i]);
		अगर (IS_ERR(state->घड़ी[i])) अणु
			ret = PTR_ERR(state->घड़ी[i]);
			जाओ err;
		पूर्ण
		ret = clk_prepare(state->घड़ी[i]);
		अगर (ret < 0) अणु
			clk_put(state->घड़ी[i]);
			state->घड़ी[i] = ERR_PTR(-EINVAL);
			जाओ err;
		पूर्ण
	पूर्ण
	वापस 0;
err:
	s5pcsis_clk_put(state);
	dev_err(dev, "failed to get clock: %s\n", csi_घड़ी_name[i]);
	वापस ret;
पूर्ण

अटल व्योम dump_regs(काष्ठा csis_state *state, स्थिर अक्षर *label)
अणु
	काष्ठा अणु
		u32 offset;
		स्थिर अक्षर * स्थिर name;
	पूर्ण रेजिस्टरs[] = अणु
		अणु 0x00, "CTRL" पूर्ण,
		अणु 0x04, "DPHYCTRL" पूर्ण,
		अणु 0x08, "CONFIG" पूर्ण,
		अणु 0x0c, "DPHYSTS" पूर्ण,
		अणु 0x10, "INTMSK" पूर्ण,
		अणु 0x2c, "RESOL" पूर्ण,
		अणु 0x38, "SDW_CONFIG" पूर्ण,
	पूर्ण;
	u32 i;

	v4l2_info(&state->sd, "--- %s ---\n", label);

	क्रम (i = 0; i < ARRAY_SIZE(रेजिस्टरs); i++) अणु
		u32 cfg = s5pcsis_पढ़ो(state, रेजिस्टरs[i].offset);
		v4l2_info(&state->sd, "%10s: 0x%08x\n", रेजिस्टरs[i].name, cfg);
	पूर्ण
पूर्ण

अटल व्योम s5pcsis_start_stream(काष्ठा csis_state *state)
अणु
	s5pcsis_reset(state);
	s5pcsis_set_params(state);
	s5pcsis_प्रणाली_enable(state, true);
	s5pcsis_enable_पूर्णांकerrupts(state, true);
पूर्ण

अटल व्योम s5pcsis_stop_stream(काष्ठा csis_state *state)
अणु
	s5pcsis_enable_पूर्णांकerrupts(state, false);
	s5pcsis_प्रणाली_enable(state, false);
पूर्ण

अटल व्योम s5pcsis_clear_counters(काष्ठा csis_state *state)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&state->slock, flags);
	क्रम (i = 0; i < S5PCSIS_NUM_EVENTS; i++)
		state->events[i].counter = 0;
	spin_unlock_irqrestore(&state->slock, flags);
पूर्ण

अटल व्योम s5pcsis_log_counters(काष्ठा csis_state *state, bool non_errors)
अणु
	पूर्णांक i = non_errors ? S5PCSIS_NUM_EVENTS : S5PCSIS_NUM_EVENTS - 4;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&state->slock, flags);

	क्रम (i--; i >= 0; i--) अणु
		अगर (state->events[i].counter > 0 || debug)
			v4l2_info(&state->sd, "%s events: %d\n",
				  state->events[i].name,
				  state->events[i].counter);
	पूर्ण
	spin_unlock_irqrestore(&state->slock, flags);
पूर्ण

/*
 * V4L2 subdev operations
 */
अटल पूर्णांक s5pcsis_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा csis_state *state = sd_to_csis_state(sd);
	काष्ठा device *dev = &state->pdev->dev;

	अगर (on)
		वापस pm_runसमय_get_sync(dev);

	वापस pm_runसमय_put_sync(dev);
पूर्ण

अटल पूर्णांक s5pcsis_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा csis_state *state = sd_to_csis_state(sd);
	पूर्णांक ret = 0;

	v4l2_dbg(1, debug, sd, "%s: %d, state: 0x%x\n",
		 __func__, enable, state->flags);

	अगर (enable) अणु
		s5pcsis_clear_counters(state);
		ret = pm_runसमय_get_sync(&state->pdev->dev);
		अगर (ret && ret != 1) अणु
			pm_runसमय_put_noidle(&state->pdev->dev);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_lock(&state->lock);
	अगर (enable) अणु
		अगर (state->flags & ST_SUSPENDED) अणु
			ret = -EBUSY;
			जाओ unlock;
		पूर्ण
		s5pcsis_start_stream(state);
		state->flags |= ST_STREAMING;
	पूर्ण अन्यथा अणु
		s5pcsis_stop_stream(state);
		state->flags &= ~ST_STREAMING;
		अगर (debug > 0)
			s5pcsis_log_counters(state, true);
	पूर्ण
unlock:
	mutex_unlock(&state->lock);
	अगर (!enable)
		pm_runसमय_put(&state->pdev->dev);

	वापस ret == 1 ? 0 : ret;
पूर्ण

अटल पूर्णांक s5pcsis_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(s5pcsis_क्रमmats))
		वापस -EINVAL;

	code->code = s5pcsis_क्रमmats[code->index].code;
	वापस 0;
पूर्ण

अटल काष्ठा csis_pix_क्रमmat स्थिर *s5pcsis_try_क्रमmat(
	काष्ठा v4l2_mbus_framefmt *mf)
अणु
	काष्ठा csis_pix_क्रमmat स्थिर *csis_fmt;

	csis_fmt = find_csis_क्रमmat(mf);
	अगर (csis_fmt == शून्य)
		csis_fmt = &s5pcsis_क्रमmats[0];

	mf->code = csis_fmt->code;
	v4l_bound_align_image(&mf->width, 1, CSIS_MAX_PIX_WIDTH,
			      csis_fmt->pix_width_alignment,
			      &mf->height, 1, CSIS_MAX_PIX_HEIGHT, 1,
			      0);
	वापस csis_fmt;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *__s5pcsis_get_क्रमmat(
		काष्ठा csis_state *state, काष्ठा v4l2_subdev_pad_config *cfg,
		क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस cfg ? v4l2_subdev_get_try_क्रमmat(&state->sd, cfg, 0) : शून्य;

	वापस &state->क्रमmat;
पूर्ण

अटल पूर्णांक s5pcsis_set_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा csis_state *state = sd_to_csis_state(sd);
	काष्ठा csis_pix_क्रमmat स्थिर *csis_fmt;
	काष्ठा v4l2_mbus_framefmt *mf;

	mf = __s5pcsis_get_क्रमmat(state, cfg, fmt->which);

	अगर (fmt->pad == CSIS_PAD_SOURCE) अणु
		अगर (mf) अणु
			mutex_lock(&state->lock);
			fmt->क्रमmat = *mf;
			mutex_unlock(&state->lock);
		पूर्ण
		वापस 0;
	पूर्ण
	csis_fmt = s5pcsis_try_क्रमmat(&fmt->क्रमmat);
	अगर (mf) अणु
		mutex_lock(&state->lock);
		*mf = fmt->क्रमmat;
		अगर (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE)
			state->csis_fmt = csis_fmt;
		mutex_unlock(&state->lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5pcsis_get_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा csis_state *state = sd_to_csis_state(sd);
	काष्ठा v4l2_mbus_framefmt *mf;

	mf = __s5pcsis_get_क्रमmat(state, cfg, fmt->which);
	अगर (!mf)
		वापस -EINVAL;

	mutex_lock(&state->lock);
	fmt->क्रमmat = *mf;
	mutex_unlock(&state->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक s5pcsis_s_rx_buffer(काष्ठा v4l2_subdev *sd, व्योम *buf,
			       अचिन्हित पूर्णांक *size)
अणु
	काष्ठा csis_state *state = sd_to_csis_state(sd);
	अचिन्हित दीर्घ flags;

	*size = min_t(अचिन्हित पूर्णांक, *size, S5PCSIS_PKTDATA_SIZE);

	spin_lock_irqsave(&state->slock, flags);
	state->pkt_buf.data = buf;
	state->pkt_buf.len = *size;
	spin_unlock_irqrestore(&state->slock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक s5pcsis_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा csis_state *state = sd_to_csis_state(sd);

	mutex_lock(&state->lock);
	s5pcsis_log_counters(state, true);
	अगर (debug && (state->flags & ST_POWERED))
		dump_regs(state, __func__);
	mutex_unlock(&state->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops s5pcsis_core_ops = अणु
	.s_घातer = s5pcsis_s_घातer,
	.log_status = s5pcsis_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops s5pcsis_pad_ops = अणु
	.क्रमागत_mbus_code = s5pcsis_क्रमागत_mbus_code,
	.get_fmt = s5pcsis_get_fmt,
	.set_fmt = s5pcsis_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops s5pcsis_video_ops = अणु
	.s_rx_buffer = s5pcsis_s_rx_buffer,
	.s_stream = s5pcsis_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops s5pcsis_subdev_ops = अणु
	.core = &s5pcsis_core_ops,
	.pad = &s5pcsis_pad_ops,
	.video = &s5pcsis_video_ops,
पूर्ण;

अटल irqवापस_t s5pcsis_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा csis_state *state = dev_id;
	काष्ठा csis_pktbuf *pktbuf = &state->pkt_buf;
	अचिन्हित दीर्घ flags;
	u32 status;

	status = s5pcsis_पढ़ो(state, S5PCSIS_INTSRC);
	spin_lock_irqsave(&state->slock, flags);

	अगर ((status & S5PCSIS_INTSRC_NON_IMAGE_DATA) && pktbuf->data) अणु
		u32 offset;

		अगर (status & S5PCSIS_INTSRC_EVEN)
			offset = S5PCSIS_PKTDATA_EVEN;
		अन्यथा
			offset = S5PCSIS_PKTDATA_ODD;

		स_नकल(pktbuf->data, (u8 __क्रमce *)state->regs + offset,
		       pktbuf->len);
		pktbuf->data = शून्य;
		rmb();
	पूर्ण

	/* Update the event/error counters */
	अगर ((status & S5PCSIS_INTSRC_ERRORS) || debug) अणु
		पूर्णांक i;
		क्रम (i = 0; i < S5PCSIS_NUM_EVENTS; i++) अणु
			अगर (!(status & state->events[i].mask))
				जारी;
			state->events[i].counter++;
			v4l2_dbg(2, debug, &state->sd, "%s: %d\n",
				 state->events[i].name,
				 state->events[i].counter);
		पूर्ण
		v4l2_dbg(2, debug, &state->sd, "status: %08x\n", status);
	पूर्ण
	spin_unlock_irqrestore(&state->slock, flags);

	s5pcsis_ग_लिखो(state, S5PCSIS_INTSRC, status);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक s5pcsis_parse_dt(काष्ठा platक्रमm_device *pdev,
			    काष्ठा csis_state *state)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा v4l2_fwnode_endpoपूर्णांक endpoपूर्णांक = अणु .bus_type = 0 पूर्ण;
	पूर्णांक ret;

	अगर (of_property_पढ़ो_u32(node, "clock-frequency",
				 &state->clk_frequency))
		state->clk_frequency = DEFAULT_SCLK_CSIS_FREQ;
	अगर (of_property_पढ़ो_u32(node, "bus-width",
				 &state->max_num_lanes))
		वापस -EINVAL;

	node = of_graph_get_next_endpoपूर्णांक(node, शून्य);
	अगर (!node) अणु
		dev_err(&pdev->dev, "No port node at %pOF\n",
				pdev->dev.of_node);
		वापस -EINVAL;
	पूर्ण
	/* Get port node and validate MIPI-CSI channel id. */
	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(node), &endpoपूर्णांक);
	अगर (ret)
		जाओ err;

	state->index = endpoपूर्णांक.base.port - FIMC_INPUT_MIPI_CSI2_0;
	अगर (state->index >= CSIS_MAX_ENTITIES) अणु
		ret = -ENXIO;
		जाओ err;
	पूर्ण

	/* Get MIPI CSI-2 bus configuration from the endpoपूर्णांक node. */
	of_property_पढ़ो_u32(node, "samsung,csis-hs-settle",
					&state->hs_settle);
	state->wclk_ext = of_property_पढ़ो_bool(node,
					"samsung,csis-wclk");

	state->num_lanes = endpoपूर्णांक.bus.mipi_csi2.num_data_lanes;

err:
	of_node_put(node);
	वापस ret;
पूर्ण

अटल पूर्णांक s5pcsis_pm_resume(काष्ठा device *dev, bool runसमय);
अटल स्थिर काष्ठा of_device_id s5pcsis_of_match[];

अटल पूर्णांक s5pcsis_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा csis_drvdata *drv_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *mem_res;
	काष्ठा csis_state *state;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i;

	state = devm_kzalloc(dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	mutex_init(&state->lock);
	spin_lock_init(&state->slock);
	state->pdev = pdev;

	of_id = of_match_node(s5pcsis_of_match, dev->of_node);
	अगर (WARN_ON(of_id == शून्य))
		वापस -EINVAL;

	drv_data = of_id->data;
	state->पूर्णांकerrupt_mask = drv_data->पूर्णांकerrupt_mask;

	ret = s5pcsis_parse_dt(pdev, state);
	अगर (ret < 0)
		वापस ret;

	अगर (state->num_lanes == 0 || state->num_lanes > state->max_num_lanes) अणु
		dev_err(dev, "Unsupported number of data lanes: %d (max. %d)\n",
			state->num_lanes, state->max_num_lanes);
		वापस -EINVAL;
	पूर्ण

	state->phy = devm_phy_get(dev, "csis");
	अगर (IS_ERR(state->phy))
		वापस PTR_ERR(state->phy);

	mem_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	state->regs = devm_ioremap_resource(dev, mem_res);
	अगर (IS_ERR(state->regs))
		वापस PTR_ERR(state->regs);

	state->irq = platक्रमm_get_irq(pdev, 0);
	अगर (state->irq < 0)
		वापस state->irq;

	क्रम (i = 0; i < CSIS_NUM_SUPPLIES; i++)
		state->supplies[i].supply = csis_supply_name[i];

	ret = devm_regulator_bulk_get(dev, CSIS_NUM_SUPPLIES,
				 state->supplies);
	अगर (ret)
		वापस ret;

	ret = s5pcsis_clk_get(state);
	अगर (ret < 0)
		वापस ret;

	अगर (state->clk_frequency)
		ret = clk_set_rate(state->घड़ी[CSIS_CLK_MUX],
				   state->clk_frequency);
	अन्यथा
		dev_WARN(dev, "No clock frequency specified!\n");
	अगर (ret < 0)
		जाओ e_clkput;

	ret = clk_enable(state->घड़ी[CSIS_CLK_MUX]);
	अगर (ret < 0)
		जाओ e_clkput;

	ret = devm_request_irq(dev, state->irq, s5pcsis_irq_handler,
			       0, dev_name(dev), state);
	अगर (ret) अणु
		dev_err(dev, "Interrupt request failed\n");
		जाओ e_clkdis;
	पूर्ण

	v4l2_subdev_init(&state->sd, &s5pcsis_subdev_ops);
	state->sd.owner = THIS_MODULE;
	snम_लिखो(state->sd.name, माप(state->sd.name), "%s.%d",
		 CSIS_SUBDEV_NAME, state->index);
	state->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	state->csis_fmt = &s5pcsis_क्रमmats[0];

	state->क्रमmat.code = s5pcsis_क्रमmats[0].code;
	state->क्रमmat.width = S5PCSIS_DEF_PIX_WIDTH;
	state->क्रमmat.height = S5PCSIS_DEF_PIX_HEIGHT;

	state->sd.entity.function = MEDIA_ENT_F_IO_V4L;
	state->pads[CSIS_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	state->pads[CSIS_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&state->sd.entity,
				CSIS_PADS_NUM, state->pads);
	अगर (ret < 0)
		जाओ e_clkdis;

	/* This allows to retrieve the platक्रमm device id by the host driver */
	v4l2_set_subdevdata(&state->sd, pdev);

	/* .. and a poपूर्णांकer to the subdev. */
	platक्रमm_set_drvdata(pdev, &state->sd);
	स_नकल(state->events, s5pcsis_events, माप(state->events));

	pm_runसमय_enable(dev);
	अगर (!pm_runसमय_enabled(dev)) अणु
		ret = s5pcsis_pm_resume(dev, true);
		अगर (ret < 0)
			जाओ e_m_ent;
	पूर्ण

	dev_info(&pdev->dev, "lanes: %d, hs_settle: %d, wclk: %d, freq: %u\n",
		 state->num_lanes, state->hs_settle, state->wclk_ext,
		 state->clk_frequency);
	वापस 0;

e_m_ent:
	media_entity_cleanup(&state->sd.entity);
e_clkdis:
	clk_disable(state->घड़ी[CSIS_CLK_MUX]);
e_clkput:
	s5pcsis_clk_put(state);
	वापस ret;
पूर्ण

अटल पूर्णांक s5pcsis_pm_suspend(काष्ठा device *dev, bool runसमय)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा csis_state *state = sd_to_csis_state(sd);
	पूर्णांक ret = 0;

	v4l2_dbg(1, debug, sd, "%s: flags: 0x%x\n",
		 __func__, state->flags);

	mutex_lock(&state->lock);
	अगर (state->flags & ST_POWERED) अणु
		s5pcsis_stop_stream(state);
		ret = phy_घातer_off(state->phy);
		अगर (ret)
			जाओ unlock;
		ret = regulator_bulk_disable(CSIS_NUM_SUPPLIES,
					     state->supplies);
		अगर (ret)
			जाओ unlock;
		clk_disable(state->घड़ी[CSIS_CLK_GATE]);
		state->flags &= ~ST_POWERED;
		अगर (!runसमय)
			state->flags |= ST_SUSPENDED;
	पूर्ण
 unlock:
	mutex_unlock(&state->lock);
	वापस ret ? -EAGAIN : 0;
पूर्ण

अटल पूर्णांक s5pcsis_pm_resume(काष्ठा device *dev, bool runसमय)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा csis_state *state = sd_to_csis_state(sd);
	पूर्णांक ret = 0;

	v4l2_dbg(1, debug, sd, "%s: flags: 0x%x\n",
		 __func__, state->flags);

	mutex_lock(&state->lock);
	अगर (!runसमय && !(state->flags & ST_SUSPENDED))
		जाओ unlock;

	अगर (!(state->flags & ST_POWERED)) अणु
		ret = regulator_bulk_enable(CSIS_NUM_SUPPLIES,
					    state->supplies);
		अगर (ret)
			जाओ unlock;
		ret = phy_घातer_on(state->phy);
		अगर (!ret) अणु
			state->flags |= ST_POWERED;
		पूर्ण अन्यथा अणु
			regulator_bulk_disable(CSIS_NUM_SUPPLIES,
					       state->supplies);
			जाओ unlock;
		पूर्ण
		clk_enable(state->घड़ी[CSIS_CLK_GATE]);
	पूर्ण
	अगर (state->flags & ST_STREAMING)
		s5pcsis_start_stream(state);

	state->flags &= ~ST_SUSPENDED;
 unlock:
	mutex_unlock(&state->lock);
	वापस ret ? -EAGAIN : 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक s5pcsis_suspend(काष्ठा device *dev)
अणु
	वापस s5pcsis_pm_suspend(dev, false);
पूर्ण

अटल पूर्णांक s5pcsis_resume(काष्ठा device *dev)
अणु
	वापस s5pcsis_pm_resume(dev, false);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक s5pcsis_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस s5pcsis_pm_suspend(dev, true);
पूर्ण

अटल पूर्णांक s5pcsis_runसमय_resume(काष्ठा device *dev)
अणु
	वापस s5pcsis_pm_resume(dev, true);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक s5pcsis_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा v4l2_subdev *sd = platक्रमm_get_drvdata(pdev);
	काष्ठा csis_state *state = sd_to_csis_state(sd);

	pm_runसमय_disable(&pdev->dev);
	s5pcsis_pm_suspend(&pdev->dev, true);
	clk_disable(state->घड़ी[CSIS_CLK_MUX]);
	pm_runसमय_set_suspended(&pdev->dev);
	s5pcsis_clk_put(state);

	media_entity_cleanup(&state->sd.entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops s5pcsis_pm_ops = अणु
	SET_RUNTIME_PM_OPS(s5pcsis_runसमय_suspend, s5pcsis_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(s5pcsis_suspend, s5pcsis_resume)
पूर्ण;

अटल स्थिर काष्ठा csis_drvdata exynos4_csis_drvdata = अणु
	.पूर्णांकerrupt_mask = S5PCSIS_INTMSK_EXYNOS4_EN_ALL,
पूर्ण;

अटल स्थिर काष्ठा csis_drvdata exynos5_csis_drvdata = अणु
	.पूर्णांकerrupt_mask = S5PCSIS_INTMSK_EXYNOS5_EN_ALL,
पूर्ण;

अटल स्थिर काष्ठा of_device_id s5pcsis_of_match[] = अणु
	अणु
		.compatible = "samsung,s5pv210-csis",
		.data = &exynos4_csis_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos4210-csis",
		.data = &exynos4_csis_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos5250-csis",
		.data = &exynos5_csis_drvdata,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s5pcsis_of_match);

अटल काष्ठा platक्रमm_driver s5pcsis_driver = अणु
	.probe		= s5pcsis_probe,
	.हटाओ		= s5pcsis_हटाओ,
	.driver		= अणु
		.of_match_table = s5pcsis_of_match,
		.name		= CSIS_DRIVER_NAME,
		.pm		= &s5pcsis_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s5pcsis_driver);

MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_DESCRIPTION("Samsung S5P/EXYNOS SoC MIPI-CSI2 receiver driver");
MODULE_LICENSE("GPL");
