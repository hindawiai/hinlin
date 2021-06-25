<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm-dp] %s: " fmt, __func__

#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-dp.h>
#समावेश <linux/rational.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "dp_catalog.h"
#समावेश "dp_reg.h"

#घोषणा POLLING_SLEEP_US			1000
#घोषणा POLLING_TIMEOUT_US			10000

#घोषणा SCRAMBLER_RESET_COUNT_VALUE		0xFC

#घोषणा DP_INTERRUPT_STATUS_ACK_SHIFT	1
#घोषणा DP_INTERRUPT_STATUS_MASK_SHIFT	2

#घोषणा MSM_DP_CONTROLLER_AHB_OFFSET	0x0000
#घोषणा MSM_DP_CONTROLLER_AHB_SIZE	0x0200
#घोषणा MSM_DP_CONTROLLER_AUX_OFFSET	0x0200
#घोषणा MSM_DP_CONTROLLER_AUX_SIZE	0x0200
#घोषणा MSM_DP_CONTROLLER_LINK_OFFSET	0x0400
#घोषणा MSM_DP_CONTROLLER_LINK_SIZE	0x0C00
#घोषणा MSM_DP_CONTROLLER_P0_OFFSET	0x1000
#घोषणा MSM_DP_CONTROLLER_P0_SIZE	0x0400

#घोषणा DP_INTERRUPT_STATUS1 \
	(DP_INTR_AUX_I2C_DONE| \
	DP_INTR_WRONG_ADDR | DP_INTR_TIMEOUT | \
	DP_INTR_NACK_DEFER | DP_INTR_WRONG_DATA_CNT | \
	DP_INTR_I2C_NACK | DP_INTR_I2C_DEFER | \
	DP_INTR_PLL_UNLOCKED | DP_INTR_AUX_ERROR)

#घोषणा DP_INTERRUPT_STATUS1_ACK \
	(DP_INTERRUPT_STATUS1 << DP_INTERRUPT_STATUS_ACK_SHIFT)
#घोषणा DP_INTERRUPT_STATUS1_MASK \
	(DP_INTERRUPT_STATUS1 << DP_INTERRUPT_STATUS_MASK_SHIFT)

#घोषणा DP_INTERRUPT_STATUS2 \
	(DP_INTR_READY_FOR_VIDEO | DP_INTR_IDLE_PATTERN_SENT | \
	DP_INTR_FRAME_END | DP_INTR_CRC_UPDATED)

#घोषणा DP_INTERRUPT_STATUS2_ACK \
	(DP_INTERRUPT_STATUS2 << DP_INTERRUPT_STATUS_ACK_SHIFT)
#घोषणा DP_INTERRUPT_STATUS2_MASK \
	(DP_INTERRUPT_STATUS2 << DP_INTERRUPT_STATUS_MASK_SHIFT)

काष्ठा dp_catalog_निजी अणु
	काष्ठा device *dev;
	काष्ठा dp_io *io;
	u32 (*audio_map)[DP_AUDIO_SDP_HEADER_MAX];
	काष्ठा dp_catalog dp_catalog;
	u8 aux_lut_cfg_index[PHY_AUX_CFG_MAX];
पूर्ण;

अटल अंतरभूत u32 dp_पढ़ो_aux(काष्ठा dp_catalog_निजी *catalog, u32 offset)
अणु
	offset += MSM_DP_CONTROLLER_AUX_OFFSET;
	वापस पढ़ोl_relaxed(catalog->io->dp_controller.base + offset);
पूर्ण

अटल अंतरभूत व्योम dp_ग_लिखो_aux(काष्ठा dp_catalog_निजी *catalog,
			       u32 offset, u32 data)
अणु
	offset += MSM_DP_CONTROLLER_AUX_OFFSET;
	/*
	 * To make sure aux reg ग_लिखोs happens beक्रमe any other operation,
	 * this function uses ग_लिखोl() instपढ़ो of ग_लिखोl_relaxed()
	 */
	ग_लिखोl(data, catalog->io->dp_controller.base + offset);
पूर्ण

अटल अंतरभूत u32 dp_पढ़ो_ahb(काष्ठा dp_catalog_निजी *catalog, u32 offset)
अणु
	offset += MSM_DP_CONTROLLER_AHB_OFFSET;
	वापस पढ़ोl_relaxed(catalog->io->dp_controller.base + offset);
पूर्ण

अटल अंतरभूत व्योम dp_ग_लिखो_ahb(काष्ठा dp_catalog_निजी *catalog,
			       u32 offset, u32 data)
अणु
	offset += MSM_DP_CONTROLLER_AHB_OFFSET;
	/*
	 * To make sure phy reg ग_लिखोs happens beक्रमe any other operation,
	 * this function uses ग_लिखोl() instपढ़ो of ग_लिखोl_relaxed()
	 */
	ग_लिखोl(data, catalog->io->dp_controller.base + offset);
पूर्ण

अटल अंतरभूत व्योम dp_ग_लिखो_p0(काष्ठा dp_catalog_निजी *catalog,
			       u32 offset, u32 data)
अणु
	offset += MSM_DP_CONTROLLER_P0_OFFSET;
	/*
	 * To make sure पूर्णांकerface reg ग_लिखोs happens beक्रमe any other operation,
	 * this function uses ग_लिखोl() instपढ़ो of ग_लिखोl_relaxed()
	 */
	ग_लिखोl(data, catalog->io->dp_controller.base + offset);
पूर्ण

अटल अंतरभूत u32 dp_पढ़ो_p0(काष्ठा dp_catalog_निजी *catalog,
			       u32 offset)
अणु
	offset += MSM_DP_CONTROLLER_P0_OFFSET;
	/*
	 * To make sure पूर्णांकerface reg ग_लिखोs happens beक्रमe any other operation,
	 * this function uses ग_लिखोl() instपढ़ो of ग_लिखोl_relaxed()
	 */
	वापस पढ़ोl_relaxed(catalog->io->dp_controller.base + offset);
पूर्ण

अटल अंतरभूत u32 dp_पढ़ो_link(काष्ठा dp_catalog_निजी *catalog, u32 offset)
अणु
	offset += MSM_DP_CONTROLLER_LINK_OFFSET;
	वापस पढ़ोl_relaxed(catalog->io->dp_controller.base + offset);
पूर्ण

अटल अंतरभूत व्योम dp_ग_लिखो_link(काष्ठा dp_catalog_निजी *catalog,
			       u32 offset, u32 data)
अणु
	offset += MSM_DP_CONTROLLER_LINK_OFFSET;
	/*
	 * To make sure link reg ग_लिखोs happens beक्रमe any other operation,
	 * this function uses ग_लिखोl() instपढ़ो of ग_लिखोl_relaxed()
	 */
	ग_लिखोl(data, catalog->io->dp_controller.base + offset);
पूर्ण

/* aux related catalog functions */
u32 dp_catalog_aux_पढ़ो_data(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	वापस dp_पढ़ो_aux(catalog, REG_DP_AUX_DATA);
पूर्ण

पूर्णांक dp_catalog_aux_ग_लिखो_data(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	dp_ग_लिखो_aux(catalog, REG_DP_AUX_DATA, dp_catalog->aux_data);
	वापस 0;
पूर्ण

पूर्णांक dp_catalog_aux_ग_लिखो_trans(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	dp_ग_लिखो_aux(catalog, REG_DP_AUX_TRANS_CTRL, dp_catalog->aux_data);
	वापस 0;
पूर्ण

पूर्णांक dp_catalog_aux_clear_trans(काष्ठा dp_catalog *dp_catalog, bool पढ़ो)
अणु
	u32 data;
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	अगर (पढ़ो) अणु
		data = dp_पढ़ो_aux(catalog, REG_DP_AUX_TRANS_CTRL);
		data &= ~DP_AUX_TRANS_CTRL_GO;
		dp_ग_लिखो_aux(catalog, REG_DP_AUX_TRANS_CTRL, data);
	पूर्ण अन्यथा अणु
		dp_ग_लिखो_aux(catalog, REG_DP_AUX_TRANS_CTRL, 0);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक dp_catalog_aux_clear_hw_पूर्णांकerrupts(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	dp_पढ़ो_aux(catalog, REG_DP_PHY_AUX_INTERRUPT_STATUS);
	dp_ग_लिखो_aux(catalog, REG_DP_PHY_AUX_INTERRUPT_CLEAR, 0x1f);
	dp_ग_लिखो_aux(catalog, REG_DP_PHY_AUX_INTERRUPT_CLEAR, 0x9f);
	dp_ग_लिखो_aux(catalog, REG_DP_PHY_AUX_INTERRUPT_CLEAR, 0);
	वापस 0;
पूर्ण

/**
 * dp_catalog_aux_reset() - reset AUX controller
 *
 * @aux: DP catalog काष्ठाure
 *
 * वापस: व्योम
 *
 * This function reset AUX controller
 *
 * NOTE: reset AUX controller will also clear any pending HPD related पूर्णांकerrupts
 * 
 */
व्योम dp_catalog_aux_reset(काष्ठा dp_catalog *dp_catalog)
अणु
	u32 aux_ctrl;
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	aux_ctrl = dp_पढ़ो_aux(catalog, REG_DP_AUX_CTRL);

	aux_ctrl |= DP_AUX_CTRL_RESET;
	dp_ग_लिखो_aux(catalog, REG_DP_AUX_CTRL, aux_ctrl);
	usleep_range(1000, 1100); /* h/w recommended delay */

	aux_ctrl &= ~DP_AUX_CTRL_RESET;
	dp_ग_लिखो_aux(catalog, REG_DP_AUX_CTRL, aux_ctrl);
पूर्ण

व्योम dp_catalog_aux_enable(काष्ठा dp_catalog *dp_catalog, bool enable)
अणु
	u32 aux_ctrl;
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	aux_ctrl = dp_पढ़ो_aux(catalog, REG_DP_AUX_CTRL);

	अगर (enable) अणु
		dp_ग_लिखो_aux(catalog, REG_DP_TIMEOUT_COUNT, 0xffff);
		dp_ग_लिखो_aux(catalog, REG_DP_AUX_LIMITS, 0xffff);
		aux_ctrl |= DP_AUX_CTRL_ENABLE;
	पूर्ण अन्यथा अणु
		aux_ctrl &= ~DP_AUX_CTRL_ENABLE;
	पूर्ण

	dp_ग_लिखो_aux(catalog, REG_DP_AUX_CTRL, aux_ctrl);
पूर्ण

व्योम dp_catalog_aux_update_cfg(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);
	काष्ठा dp_io *dp_io = catalog->io;
	काष्ठा phy *phy = dp_io->phy;

	phy_calibrate(phy);
पूर्ण

अटल व्योम dump_regs(व्योम __iomem *base, पूर्णांक len)
अणु
	पूर्णांक i;
	u32 x0, x4, x8, xc;
	u32 addr_off = 0;

	len = DIV_ROUND_UP(len, 16);
	क्रम (i = 0; i < len; i++) अणु
		x0 = पढ़ोl_relaxed(base + addr_off);
		x4 = पढ़ोl_relaxed(base + addr_off + 0x04);
		x8 = पढ़ोl_relaxed(base + addr_off + 0x08);
		xc = पढ़ोl_relaxed(base + addr_off + 0x0c);

		pr_info("%08x: %08x %08x %08x %08x", addr_off, x0, x4, x8, xc);
		addr_off += 16;
	पूर्ण
पूर्ण

व्योम dp_catalog_dump_regs(काष्ठा dp_catalog *dp_catalog)
अणु
	u32 offset, len;
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
		काष्ठा dp_catalog_निजी, dp_catalog);

	pr_info("AHB regs\n");
	offset = MSM_DP_CONTROLLER_AHB_OFFSET;
	len = MSM_DP_CONTROLLER_AHB_SIZE;
	dump_regs(catalog->io->dp_controller.base + offset, len);

	pr_info("AUXCLK regs\n");
	offset = MSM_DP_CONTROLLER_AUX_OFFSET;
	len = MSM_DP_CONTROLLER_AUX_SIZE;
	dump_regs(catalog->io->dp_controller.base + offset, len);

	pr_info("LCLK regs\n");
	offset = MSM_DP_CONTROLLER_LINK_OFFSET;
	len = MSM_DP_CONTROLLER_LINK_SIZE;
	dump_regs(catalog->io->dp_controller.base + offset, len);

	pr_info("P0CLK regs\n");
	offset = MSM_DP_CONTROLLER_P0_OFFSET;
	len = MSM_DP_CONTROLLER_P0_SIZE;
	dump_regs(catalog->io->dp_controller.base + offset, len);
पूर्ण

पूर्णांक dp_catalog_aux_get_irq(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);
	u32 पूर्णांकr, पूर्णांकr_ack;

	पूर्णांकr = dp_पढ़ो_ahb(catalog, REG_DP_INTR_STATUS);
	पूर्णांकr &= ~DP_INTERRUPT_STATUS1_MASK;
	पूर्णांकr_ack = (पूर्णांकr & DP_INTERRUPT_STATUS1)
			<< DP_INTERRUPT_STATUS_ACK_SHIFT;
	dp_ग_लिखो_ahb(catalog, REG_DP_INTR_STATUS, पूर्णांकr_ack |
			DP_INTERRUPT_STATUS1_MASK);

	वापस पूर्णांकr;

पूर्ण

/* controller related catalog functions */
व्योम dp_catalog_ctrl_update_transfer_unit(काष्ठा dp_catalog *dp_catalog,
				u32 dp_tu, u32 valid_boundary,
				u32 valid_boundary2)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	dp_ग_लिखो_link(catalog, REG_DP_VALID_BOUNDARY, valid_boundary);
	dp_ग_लिखो_link(catalog, REG_DP_TU, dp_tu);
	dp_ग_लिखो_link(catalog, REG_DP_VALID_BOUNDARY_2, valid_boundary2);
पूर्ण

व्योम dp_catalog_ctrl_state_ctrl(काष्ठा dp_catalog *dp_catalog, u32 state)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	dp_ग_लिखो_link(catalog, REG_DP_STATE_CTRL, state);
पूर्ण

व्योम dp_catalog_ctrl_config_ctrl(काष्ठा dp_catalog *dp_catalog, u32 cfg)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	DRM_DEBUG_DP("DP_CONFIGURATION_CTRL=0x%x\n", cfg);

	dp_ग_लिखो_link(catalog, REG_DP_CONFIGURATION_CTRL, cfg);
पूर्ण

व्योम dp_catalog_ctrl_lane_mapping(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);
	u32 ln_0 = 0, ln_1 = 1, ln_2 = 2, ln_3 = 3; /* One-to-One mapping */
	u32 ln_mapping;

	ln_mapping = ln_0 << LANE0_MAPPING_SHIFT;
	ln_mapping |= ln_1 << LANE1_MAPPING_SHIFT;
	ln_mapping |= ln_2 << LANE2_MAPPING_SHIFT;
	ln_mapping |= ln_3 << LANE3_MAPPING_SHIFT;

	dp_ग_लिखो_link(catalog, REG_DP_LOGICAL2PHYSICAL_LANE_MAPPING,
			ln_mapping);
पूर्ण

व्योम dp_catalog_ctrl_मुख्यlink_ctrl(काष्ठा dp_catalog *dp_catalog,
						bool enable)
अणु
	u32 मुख्यlink_ctrl;
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	अगर (enable) अणु
		/*
		 * To make sure link reg ग_लिखोs happens beक्रमe other operation,
		 * dp_ग_लिखो_link() function uses ग_लिखोl()
		 */
		मुख्यlink_ctrl = dp_पढ़ो_link(catalog, REG_DP_MAINLINK_CTRL);

		मुख्यlink_ctrl &= ~(DP_MAINLINK_CTRL_RESET |
						DP_MAINLINK_CTRL_ENABLE);
		dp_ग_लिखो_link(catalog, REG_DP_MAINLINK_CTRL, मुख्यlink_ctrl);

		मुख्यlink_ctrl |= DP_MAINLINK_CTRL_RESET;
		dp_ग_लिखो_link(catalog, REG_DP_MAINLINK_CTRL, मुख्यlink_ctrl);

		मुख्यlink_ctrl &= ~DP_MAINLINK_CTRL_RESET;
		dp_ग_लिखो_link(catalog, REG_DP_MAINLINK_CTRL, मुख्यlink_ctrl);

		मुख्यlink_ctrl |= (DP_MAINLINK_CTRL_ENABLE |
					DP_MAINLINK_FB_BOUNDARY_SEL);
		dp_ग_लिखो_link(catalog, REG_DP_MAINLINK_CTRL, मुख्यlink_ctrl);
	पूर्ण अन्यथा अणु
		मुख्यlink_ctrl = dp_पढ़ो_link(catalog, REG_DP_MAINLINK_CTRL);
		मुख्यlink_ctrl &= ~DP_MAINLINK_CTRL_ENABLE;
		dp_ग_लिखो_link(catalog, REG_DP_MAINLINK_CTRL, मुख्यlink_ctrl);
	पूर्ण
पूर्ण

व्योम dp_catalog_ctrl_config_misc(काष्ठा dp_catalog *dp_catalog,
					u32 colorimetry_cfg,
					u32 test_bits_depth)
अणु
	u32 misc_val;
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	misc_val = dp_पढ़ो_link(catalog, REG_DP_MISC1_MISC0);

	/* clear bpp bits */
	misc_val &= ~(0x07 << DP_MISC0_TEST_BITS_DEPTH_SHIFT);
	misc_val |= colorimetry_cfg << DP_MISC0_COLORIMETRY_CFG_SHIFT;
	misc_val |= test_bits_depth << DP_MISC0_TEST_BITS_DEPTH_SHIFT;
	/* Configure घड़ी to synchronous mode */
	misc_val |= DP_MISC0_SYNCHRONOUS_CLK;

	DRM_DEBUG_DP("misc settings = 0x%x\n", misc_val);
	dp_ग_लिखो_link(catalog, REG_DP_MISC1_MISC0, misc_val);
पूर्ण

व्योम dp_catalog_ctrl_config_msa(काष्ठा dp_catalog *dp_catalog,
					u32 rate, u32 stream_rate_khz,
					bool fixed_nvid)
अणु
	u32 pixel_m, pixel_n;
	u32 mvid, nvid, pixel_भाग = 0, dispcc_input_rate;
	u32 स्थिर nvid_fixed = DP_LINK_CONSTANT_N_VALUE;
	u32 स्थिर link_rate_hbr2 = 540000;
	u32 स्थिर link_rate_hbr3 = 810000;
	अचिन्हित दीर्घ den, num;

	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	अगर (rate == link_rate_hbr3)
		pixel_भाग = 6;
	अन्यथा अगर (rate == 1620000 || rate == 270000)
		pixel_भाग = 2;
	अन्यथा अगर (rate == link_rate_hbr2)
		pixel_भाग = 4;
	अन्यथा
		DRM_ERROR("Invalid pixel mux divider\n");

	dispcc_input_rate = (rate * 10) / pixel_भाग;

	rational_best_approximation(dispcc_input_rate, stream_rate_khz,
			(अचिन्हित दीर्घ)(1 << 16) - 1,
			(अचिन्हित दीर्घ)(1 << 16) - 1, &den, &num);

	den = ~(den - num);
	den = den & 0xFFFF;
	pixel_m = num;
	pixel_n = den;

	mvid = (pixel_m & 0xFFFF) * 5;
	nvid = (0xFFFF & (~pixel_n)) + (pixel_m & 0xFFFF);

	अगर (nvid < nvid_fixed) अणु
		u32 temp;

		temp = (nvid_fixed / nvid) * nvid;
		mvid = (nvid_fixed / nvid) * mvid;
		nvid = temp;
	पूर्ण

	अगर (link_rate_hbr2 == rate)
		nvid *= 2;

	अगर (link_rate_hbr3 == rate)
		nvid *= 3;

	DRM_DEBUG_DP("mvid=0x%x, nvid=0x%x\n", mvid, nvid);
	dp_ग_लिखो_link(catalog, REG_DP_SOFTWARE_MVID, mvid);
	dp_ग_लिखो_link(catalog, REG_DP_SOFTWARE_NVID, nvid);
	dp_ग_लिखो_p0(catalog, MMSS_DP_DSC_DTO, 0x0);
पूर्ण

पूर्णांक dp_catalog_ctrl_set_pattern(काष्ठा dp_catalog *dp_catalog,
					u32 pattern)
अणु
	पूर्णांक bit, ret;
	u32 data;
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	bit = BIT(pattern - 1);
	DRM_DEBUG_DP("hw: bit=%d train=%d\n", bit, pattern);
	dp_catalog_ctrl_state_ctrl(dp_catalog, bit);

	bit = BIT(pattern - 1) << DP_MAINLINK_READY_LINK_TRAINING_SHIFT;

	/* Poll क्रम मुख्यlink पढ़ोy status */
	ret = पढ़ोx_poll_समयout(पढ़ोl, catalog->io->dp_controller.base +
					MSM_DP_CONTROLLER_LINK_OFFSET +
					REG_DP_MAINLINK_READY,
					data, data & bit,
					POLLING_SLEEP_US, POLLING_TIMEOUT_US);
	अगर (ret < 0) अणु
		DRM_ERROR("set pattern for link_train=%d failed\n", pattern);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * dp_catalog_ctrl_reset() - reset DP controller
 *
 * @dp_catalog: DP catalog काष्ठाure
 *
 * वापस: व्योम
 *
 * This function reset the DP controller
 *
 * NOTE: reset DP controller will also clear any pending HPD related पूर्णांकerrupts
 * 
 */
व्योम dp_catalog_ctrl_reset(काष्ठा dp_catalog *dp_catalog)
अणु
	u32 sw_reset;
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	sw_reset = dp_पढ़ो_ahb(catalog, REG_DP_SW_RESET);

	sw_reset |= DP_SW_RESET;
	dp_ग_लिखो_ahb(catalog, REG_DP_SW_RESET, sw_reset);
	usleep_range(1000, 1100); /* h/w recommended delay */

	sw_reset &= ~DP_SW_RESET;
	dp_ग_लिखो_ahb(catalog, REG_DP_SW_RESET, sw_reset);
पूर्ण

bool dp_catalog_ctrl_मुख्यlink_पढ़ोy(काष्ठा dp_catalog *dp_catalog)
अणु
	u32 data;
	पूर्णांक ret;
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	/* Poll क्रम मुख्यlink पढ़ोy status */
	ret = पढ़ोl_poll_समयout(catalog->io->dp_controller.base +
				MSM_DP_CONTROLLER_LINK_OFFSET +
				REG_DP_MAINLINK_READY,
				data, data & DP_MAINLINK_READY_FOR_VIDEO,
				POLLING_SLEEP_US, POLLING_TIMEOUT_US);
	अगर (ret < 0) अणु
		DRM_ERROR("mainlink not ready\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम dp_catalog_ctrl_enable_irq(काष्ठा dp_catalog *dp_catalog,
						bool enable)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	अगर (enable) अणु
		dp_ग_लिखो_ahb(catalog, REG_DP_INTR_STATUS,
				DP_INTERRUPT_STATUS1_MASK);
		dp_ग_लिखो_ahb(catalog, REG_DP_INTR_STATUS2,
				DP_INTERRUPT_STATUS2_MASK);
	पूर्ण अन्यथा अणु
		dp_ग_लिखो_ahb(catalog, REG_DP_INTR_STATUS, 0x00);
		dp_ग_लिखो_ahb(catalog, REG_DP_INTR_STATUS2, 0x00);
	पूर्ण
पूर्ण

व्योम dp_catalog_hpd_config_पूर्णांकr(काष्ठा dp_catalog *dp_catalog,
			u32 पूर्णांकr_mask, bool en)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	u32 config = dp_पढ़ो_aux(catalog, REG_DP_DP_HPD_INT_MASK);

	config = (en ? config | पूर्णांकr_mask : config & ~पूर्णांकr_mask);

	dp_ग_लिखो_aux(catalog, REG_DP_DP_HPD_INT_MASK,
				config & DP_DP_HPD_INT_MASK);
पूर्ण

व्योम dp_catalog_ctrl_hpd_config(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	u32 refसमयr = dp_पढ़ो_aux(catalog, REG_DP_DP_HPD_REFTIMER);

	/* enable HPD पूर्णांकerrupts */
	dp_catalog_hpd_config_पूर्णांकr(dp_catalog,
		DP_DP_HPD_PLUG_INT_MASK | DP_DP_IRQ_HPD_INT_MASK
		| DP_DP_HPD_UNPLUG_INT_MASK | DP_DP_HPD_REPLUG_INT_MASK, true);

	/* Configure REFTIMER and enable it */
	refसमयr |= DP_DP_HPD_REFTIMER_ENABLE;
	dp_ग_लिखो_aux(catalog, REG_DP_DP_HPD_REFTIMER, refसमयr);

	/* Enable HPD */
	dp_ग_लिखो_aux(catalog, REG_DP_DP_HPD_CTRL, DP_DP_HPD_CTRL_HPD_EN);
पूर्ण

u32 dp_catalog_link_is_connected(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);
	u32 status;

	status = dp_पढ़ो_aux(catalog, REG_DP_DP_HPD_INT_STATUS);
	status >>= DP_DP_HPD_STATE_STATUS_BITS_SHIFT;
	status &= DP_DP_HPD_STATE_STATUS_BITS_MASK;

	वापस status;
पूर्ण

u32 dp_catalog_hpd_get_पूर्णांकr_status(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);
	पूर्णांक isr = 0;

	isr = dp_पढ़ो_aux(catalog, REG_DP_DP_HPD_INT_STATUS);
	dp_ग_लिखो_aux(catalog, REG_DP_DP_HPD_INT_ACK,
				 (isr & DP_DP_HPD_INT_MASK));

	वापस isr;
पूर्ण

पूर्णांक dp_catalog_ctrl_get_पूर्णांकerrupt(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);
	u32 पूर्णांकr, पूर्णांकr_ack;

	पूर्णांकr = dp_पढ़ो_ahb(catalog, REG_DP_INTR_STATUS2);
	पूर्णांकr &= ~DP_INTERRUPT_STATUS2_MASK;
	पूर्णांकr_ack = (पूर्णांकr & DP_INTERRUPT_STATUS2)
			<< DP_INTERRUPT_STATUS_ACK_SHIFT;
	dp_ग_लिखो_ahb(catalog, REG_DP_INTR_STATUS2,
			पूर्णांकr_ack | DP_INTERRUPT_STATUS2_MASK);

	वापस पूर्णांकr;
पूर्ण

व्योम dp_catalog_ctrl_phy_reset(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	dp_ग_लिखो_ahb(catalog, REG_DP_PHY_CTRL,
			DP_PHY_CTRL_SW_RESET | DP_PHY_CTRL_SW_RESET_PLL);
	usleep_range(1000, 1100); /* h/w recommended delay */
	dp_ग_लिखो_ahb(catalog, REG_DP_PHY_CTRL, 0x0);
पूर्ण

पूर्णांक dp_catalog_ctrl_update_vx_px(काष्ठा dp_catalog *dp_catalog,
		u8 v_level, u8 p_level)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);
	काष्ठा dp_io *dp_io = catalog->io;
	काष्ठा phy *phy = dp_io->phy;
	काष्ठा phy_configure_opts_dp *opts_dp = &dp_io->phy_opts.dp;

	/* TODO: Update क्रम all lanes instead of just first one */
	opts_dp->voltage[0] = v_level;
	opts_dp->pre[0] = p_level;
	opts_dp->set_voltages = 1;
	phy_configure(phy, &dp_io->phy_opts);
	opts_dp->set_voltages = 0;

	वापस 0;
पूर्ण

व्योम dp_catalog_ctrl_send_phy_pattern(काष्ठा dp_catalog *dp_catalog,
			u32 pattern)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);
	u32 value = 0x0;

	/* Make sure to clear the current pattern beक्रमe starting a new one */
	dp_ग_लिखो_link(catalog, REG_DP_STATE_CTRL, 0x0);

	चयन (pattern) अणु
	हाल DP_PHY_TEST_PATTERN_D10_2:
		dp_ग_लिखो_link(catalog, REG_DP_STATE_CTRL,
				DP_STATE_CTRL_LINK_TRAINING_PATTERN1);
		अवरोध;
	हाल DP_PHY_TEST_PATTERN_ERROR_COUNT:
		value &= ~(1 << 16);
		dp_ग_लिखो_link(catalog, REG_DP_HBR2_COMPLIANCE_SCRAMBLER_RESET,
					value);
		value |= SCRAMBLER_RESET_COUNT_VALUE;
		dp_ग_लिखो_link(catalog, REG_DP_HBR2_COMPLIANCE_SCRAMBLER_RESET,
					value);
		dp_ग_लिखो_link(catalog, REG_DP_MAINLINK_LEVELS,
					DP_MAINLINK_SAFE_TO_EXIT_LEVEL_2);
		dp_ग_लिखो_link(catalog, REG_DP_STATE_CTRL,
					DP_STATE_CTRL_LINK_SYMBOL_ERR_MEASURE);
		अवरोध;
	हाल DP_PHY_TEST_PATTERN_PRBS7:
		dp_ग_लिखो_link(catalog, REG_DP_STATE_CTRL,
				DP_STATE_CTRL_LINK_PRBS7);
		अवरोध;
	हाल DP_PHY_TEST_PATTERN_80BIT_CUSTOM:
		dp_ग_लिखो_link(catalog, REG_DP_STATE_CTRL,
				DP_STATE_CTRL_LINK_TEST_CUSTOM_PATTERN);
		/* 00111110000011111000001111100000 */
		dp_ग_लिखो_link(catalog, REG_DP_TEST_80BIT_CUSTOM_PATTERN_REG0,
				0x3E0F83E0);
		/* 00001111100000111110000011111000 */
		dp_ग_लिखो_link(catalog, REG_DP_TEST_80BIT_CUSTOM_PATTERN_REG1,
				0x0F83E0F8);
		/* 1111100000111110 */
		dp_ग_लिखो_link(catalog, REG_DP_TEST_80BIT_CUSTOM_PATTERN_REG2,
				0x0000F83E);
		अवरोध;
	हाल DP_PHY_TEST_PATTERN_CP2520:
		value = dp_पढ़ो_link(catalog, REG_DP_MAINLINK_CTRL);
		value &= ~DP_MAINLINK_CTRL_SW_BYPASS_SCRAMBLER;
		dp_ग_लिखो_link(catalog, REG_DP_MAINLINK_CTRL, value);

		value = DP_HBR2_ERM_PATTERN;
		dp_ग_लिखो_link(catalog, REG_DP_HBR2_COMPLIANCE_SCRAMBLER_RESET,
				value);
		value |= SCRAMBLER_RESET_COUNT_VALUE;
		dp_ग_लिखो_link(catalog, REG_DP_HBR2_COMPLIANCE_SCRAMBLER_RESET,
					value);
		dp_ग_लिखो_link(catalog, REG_DP_MAINLINK_LEVELS,
					DP_MAINLINK_SAFE_TO_EXIT_LEVEL_2);
		dp_ग_लिखो_link(catalog, REG_DP_STATE_CTRL,
					DP_STATE_CTRL_LINK_SYMBOL_ERR_MEASURE);
		value = dp_पढ़ो_link(catalog, REG_DP_MAINLINK_CTRL);
		value |= DP_MAINLINK_CTRL_ENABLE;
		dp_ग_लिखो_link(catalog, REG_DP_MAINLINK_CTRL, value);
		अवरोध;
	हाल DP_PHY_TEST_PATTERN_SEL_MASK:
		dp_ग_लिखो_link(catalog, REG_DP_MAINLINK_CTRL,
				DP_MAINLINK_CTRL_ENABLE);
		dp_ग_लिखो_link(catalog, REG_DP_STATE_CTRL,
				DP_STATE_CTRL_LINK_TRAINING_PATTERN4);
		अवरोध;
	शेष:
		DRM_DEBUG_DP("No valid test pattern requested:0x%x\n", pattern);
		अवरोध;
	पूर्ण
पूर्ण

u32 dp_catalog_ctrl_पढ़ो_phy_pattern(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	वापस dp_पढ़ो_link(catalog, REG_DP_MAINLINK_READY);
पूर्ण

/* panel related catalog functions */
पूर्णांक dp_catalog_panel_timing_cfg(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	dp_ग_लिखो_link(catalog, REG_DP_TOTAL_HOR_VER,
				dp_catalog->total);
	dp_ग_लिखो_link(catalog, REG_DP_START_HOR_VER_FROM_SYNC,
				dp_catalog->sync_start);
	dp_ग_लिखो_link(catalog, REG_DP_HSYNC_VSYNC_WIDTH_POLARITY,
				dp_catalog->width_blanking);
	dp_ग_लिखो_link(catalog, REG_DP_ACTIVE_HOR_VER, dp_catalog->dp_active);
	वापस 0;
पूर्ण

व्योम dp_catalog_panel_tpg_enable(काष्ठा dp_catalog *dp_catalog,
				काष्ठा drm_display_mode *drm_mode)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);
	u32 hsync_period, vsync_period;
	u32 display_v_start, display_v_end;
	u32 hsync_start_x, hsync_end_x;
	u32 v_sync_width;
	u32 hsync_ctl;
	u32 display_hctl;

	/* TPG config parameters*/
	hsync_period = drm_mode->htotal;
	vsync_period = drm_mode->vtotal;

	display_v_start = ((drm_mode->vtotal - drm_mode->vsync_start) *
					hsync_period);
	display_v_end = ((vsync_period - (drm_mode->vsync_start -
					drm_mode->vdisplay))
					* hsync_period) - 1;

	display_v_start += drm_mode->htotal - drm_mode->hsync_start;
	display_v_end -= (drm_mode->hsync_start - drm_mode->hdisplay);

	hsync_start_x = drm_mode->htotal - drm_mode->hsync_start;
	hsync_end_x = hsync_period - (drm_mode->hsync_start -
					drm_mode->hdisplay) - 1;

	v_sync_width = drm_mode->vsync_end - drm_mode->vsync_start;

	hsync_ctl = (hsync_period << 16) |
			(drm_mode->hsync_end - drm_mode->hsync_start);
	display_hctl = (hsync_end_x << 16) | hsync_start_x;


	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_CONFIG, 0x0);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_HSYNC_CTL, hsync_ctl);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_VSYNC_PERIOD_F0, vsync_period *
			hsync_period);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_VSYNC_PULSE_WIDTH_F0, v_sync_width *
			hsync_period);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_VSYNC_PERIOD_F1, 0);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_VSYNC_PULSE_WIDTH_F1, 0);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_DISPLAY_HCTL, display_hctl);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_ACTIVE_HCTL, 0);
	dp_ग_लिखो_p0(catalog, MMSS_INTF_DISPLAY_V_START_F0, display_v_start);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_DISPLAY_V_END_F0, display_v_end);
	dp_ग_लिखो_p0(catalog, MMSS_INTF_DISPLAY_V_START_F1, 0);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_DISPLAY_V_END_F1, 0);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_ACTIVE_V_START_F0, 0);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_ACTIVE_V_END_F0, 0);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_ACTIVE_V_START_F1, 0);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_ACTIVE_V_END_F1, 0);
	dp_ग_लिखो_p0(catalog, MMSS_DP_INTF_POLARITY_CTL, 0);

	dp_ग_लिखो_p0(catalog, MMSS_DP_TPG_MAIN_CONTROL,
				DP_TPG_CHECKERED_RECT_PATTERN);
	dp_ग_लिखो_p0(catalog, MMSS_DP_TPG_VIDEO_CONFIG,
				DP_TPG_VIDEO_CONFIG_BPP_8BIT |
				DP_TPG_VIDEO_CONFIG_RGB);
	dp_ग_लिखो_p0(catalog, MMSS_DP_BIST_ENABLE,
				DP_BIST_ENABLE_DPBIST_EN);
	dp_ग_लिखो_p0(catalog, MMSS_DP_TIMING_ENGINE_EN,
				DP_TIMING_ENGINE_EN_EN);
	DRM_DEBUG_DP("%s: enabled tpg\n", __func__);
पूर्ण

व्योम dp_catalog_panel_tpg_disable(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog = container_of(dp_catalog,
				काष्ठा dp_catalog_निजी, dp_catalog);

	dp_ग_लिखो_p0(catalog, MMSS_DP_TPG_MAIN_CONTROL, 0x0);
	dp_ग_लिखो_p0(catalog, MMSS_DP_BIST_ENABLE, 0x0);
	dp_ग_लिखो_p0(catalog, MMSS_DP_TIMING_ENGINE_EN, 0x0);
पूर्ण

काष्ठा dp_catalog *dp_catalog_get(काष्ठा device *dev, काष्ठा dp_io *io)
अणु
	काष्ठा dp_catalog_निजी *catalog;

	अगर (!io) अणु
		DRM_ERROR("invalid input\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	catalog  = devm_kzalloc(dev, माप(*catalog), GFP_KERNEL);
	अगर (!catalog)
		वापस ERR_PTR(-ENOMEM);

	catalog->dev = dev;
	catalog->io = io;

	वापस &catalog->dp_catalog;
पूर्ण

व्योम dp_catalog_audio_get_header(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog;
	u32 (*sdp_map)[DP_AUDIO_SDP_HEADER_MAX];
	क्रमागत dp_catalog_audio_sdp_type sdp;
	क्रमागत dp_catalog_audio_header_type header;

	अगर (!dp_catalog)
		वापस;

	catalog = container_of(dp_catalog,
		काष्ठा dp_catalog_निजी, dp_catalog);

	sdp_map = catalog->audio_map;
	sdp     = dp_catalog->sdp_type;
	header  = dp_catalog->sdp_header;

	dp_catalog->audio_data = dp_पढ़ो_link(catalog,
			sdp_map[sdp][header]);
पूर्ण

व्योम dp_catalog_audio_set_header(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog;
	u32 (*sdp_map)[DP_AUDIO_SDP_HEADER_MAX];
	क्रमागत dp_catalog_audio_sdp_type sdp;
	क्रमागत dp_catalog_audio_header_type header;
	u32 data;

	अगर (!dp_catalog)
		वापस;

	catalog = container_of(dp_catalog,
		काष्ठा dp_catalog_निजी, dp_catalog);

	sdp_map = catalog->audio_map;
	sdp     = dp_catalog->sdp_type;
	header  = dp_catalog->sdp_header;
	data    = dp_catalog->audio_data;

	dp_ग_लिखो_link(catalog, sdp_map[sdp][header], data);
पूर्ण

व्योम dp_catalog_audio_config_acr(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog;
	u32 acr_ctrl, select;

	अगर (!dp_catalog)
		वापस;

	catalog = container_of(dp_catalog,
		काष्ठा dp_catalog_निजी, dp_catalog);

	select = dp_catalog->audio_data;
	acr_ctrl = select << 4 | BIT(31) | BIT(8) | BIT(14);

	DRM_DEBUG_DP("select = 0x%x, acr_ctrl = 0x%x\n", select, acr_ctrl);

	dp_ग_लिखो_link(catalog, MMSS_DP_AUDIO_ACR_CTRL, acr_ctrl);
पूर्ण

व्योम dp_catalog_audio_enable(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog;
	bool enable;
	u32 audio_ctrl;

	अगर (!dp_catalog)
		वापस;

	catalog = container_of(dp_catalog,
		काष्ठा dp_catalog_निजी, dp_catalog);

	enable = !!dp_catalog->audio_data;
	audio_ctrl = dp_पढ़ो_link(catalog, MMSS_DP_AUDIO_CFG);

	अगर (enable)
		audio_ctrl |= BIT(0);
	अन्यथा
		audio_ctrl &= ~BIT(0);

	DRM_DEBUG_DP("dp_audio_cfg = 0x%x\n", audio_ctrl);

	dp_ग_लिखो_link(catalog, MMSS_DP_AUDIO_CFG, audio_ctrl);
	/* make sure audio engine is disabled */
	wmb();
पूर्ण

व्योम dp_catalog_audio_config_sdp(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog;
	u32 sdp_cfg = 0;
	u32 sdp_cfg2 = 0;

	अगर (!dp_catalog)
		वापस;

	catalog = container_of(dp_catalog,
		काष्ठा dp_catalog_निजी, dp_catalog);

	sdp_cfg = dp_पढ़ो_link(catalog, MMSS_DP_SDP_CFG);
	/* AUDIO_TIMESTAMP_SDP_EN */
	sdp_cfg |= BIT(1);
	/* AUDIO_STREAM_SDP_EN */
	sdp_cfg |= BIT(2);
	/* AUDIO_COPY_MANAGEMENT_SDP_EN */
	sdp_cfg |= BIT(5);
	/* AUDIO_ISRC_SDP_EN  */
	sdp_cfg |= BIT(6);
	/* AUDIO_INFOFRAME_SDP_EN  */
	sdp_cfg |= BIT(20);

	DRM_DEBUG_DP("sdp_cfg = 0x%x\n", sdp_cfg);

	dp_ग_लिखो_link(catalog, MMSS_DP_SDP_CFG, sdp_cfg);

	sdp_cfg2 = dp_पढ़ो_link(catalog, MMSS_DP_SDP_CFG2);
	/* IFRM_REGSRC -> Do not use reg values */
	sdp_cfg2 &= ~BIT(0);
	/* AUDIO_STREAM_HB3_REGSRC-> Do not use reg values */
	sdp_cfg2 &= ~BIT(1);

	DRM_DEBUG_DP("sdp_cfg2 = 0x%x\n", sdp_cfg2);

	dp_ग_लिखो_link(catalog, MMSS_DP_SDP_CFG2, sdp_cfg2);
पूर्ण

व्योम dp_catalog_audio_init(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog;

	अटल u32 sdp_map[][DP_AUDIO_SDP_HEADER_MAX] = अणु
		अणु
			MMSS_DP_AUDIO_STREAM_0,
			MMSS_DP_AUDIO_STREAM_1,
			MMSS_DP_AUDIO_STREAM_1,
		पूर्ण,
		अणु
			MMSS_DP_AUDIO_TIMESTAMP_0,
			MMSS_DP_AUDIO_TIMESTAMP_1,
			MMSS_DP_AUDIO_TIMESTAMP_1,
		पूर्ण,
		अणु
			MMSS_DP_AUDIO_INFOFRAME_0,
			MMSS_DP_AUDIO_INFOFRAME_1,
			MMSS_DP_AUDIO_INFOFRAME_1,
		पूर्ण,
		अणु
			MMSS_DP_AUDIO_COPYMANAGEMENT_0,
			MMSS_DP_AUDIO_COPYMANAGEMENT_1,
			MMSS_DP_AUDIO_COPYMANAGEMENT_1,
		पूर्ण,
		अणु
			MMSS_DP_AUDIO_ISRC_0,
			MMSS_DP_AUDIO_ISRC_1,
			MMSS_DP_AUDIO_ISRC_1,
		पूर्ण,
	पूर्ण;

	अगर (!dp_catalog)
		वापस;

	catalog = container_of(dp_catalog,
		काष्ठा dp_catalog_निजी, dp_catalog);

	catalog->audio_map = sdp_map;
पूर्ण

व्योम dp_catalog_audio_sfe_level(काष्ठा dp_catalog *dp_catalog)
अणु
	काष्ठा dp_catalog_निजी *catalog;
	u32 मुख्यlink_levels, safe_to_निकास_level;

	अगर (!dp_catalog)
		वापस;

	catalog = container_of(dp_catalog,
		काष्ठा dp_catalog_निजी, dp_catalog);

	safe_to_निकास_level = dp_catalog->audio_data;
	मुख्यlink_levels = dp_पढ़ो_link(catalog, REG_DP_MAINLINK_LEVELS);
	मुख्यlink_levels &= 0xFE0;
	मुख्यlink_levels |= safe_to_निकास_level;

	DRM_DEBUG_DP("mainlink_level = 0x%x, safe_to_exit_level = 0x%x\n",
			 मुख्यlink_levels, safe_to_निकास_level);

	dp_ग_लिखो_link(catalog, REG_DP_MAINLINK_LEVELS, मुख्यlink_levels);
पूर्ण
