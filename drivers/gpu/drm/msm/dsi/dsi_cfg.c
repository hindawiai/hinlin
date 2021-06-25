<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश "dsi_cfg.h"

अटल स्थिर अक्षर * स्थिर dsi_v2_bus_clk_names[] = अणु
	"core_mmss", "iface", "bus",
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_config apq8064_dsi_cfg = अणु
	.io_offset = 0,
	.reg_cfg = अणु
		.num = 3,
		.regs = अणु
			अणु"vdda", 100000, 100पूर्ण,	/* 1.2 V */
			अणु"avdd", 10000, 100पूर्ण,	/* 3.0 V */
			अणु"vddio", 100000, 100पूर्ण,	/* 1.8 V */
		पूर्ण,
	पूर्ण,
	.bus_clk_names = dsi_v2_bus_clk_names,
	.num_bus_clks = ARRAY_SIZE(dsi_v2_bus_clk_names),
	.io_start = अणु 0x4700000, 0x5800000 पूर्ण,
	.num_dsi = 2,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsi_6g_bus_clk_names[] = अणु
	"mdp_core", "iface", "bus", "core_mmss",
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_config msm8974_apq8084_dsi_cfg = अणु
	.io_offset = DSI_6G_REG_SHIFT,
	.reg_cfg = अणु
		.num = 4,
		.regs = अणु
			अणु"gdsc", -1, -1पूर्ण,
			अणु"vdd", 150000, 100पूर्ण,	/* 3.0 V */
			अणु"vdda", 100000, 100पूर्ण,	/* 1.2 V */
			अणु"vddio", 100000, 100पूर्ण,	/* 1.8 V */
		पूर्ण,
	पूर्ण,
	.bus_clk_names = dsi_6g_bus_clk_names,
	.num_bus_clks = ARRAY_SIZE(dsi_6g_bus_clk_names),
	.io_start = अणु 0xfd922800, 0xfd922b00 पूर्ण,
	.num_dsi = 2,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsi_8916_bus_clk_names[] = अणु
	"mdp_core", "iface", "bus",
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_config msm8916_dsi_cfg = अणु
	.io_offset = DSI_6G_REG_SHIFT,
	.reg_cfg = अणु
		.num = 3,
		.regs = अणु
			अणु"gdsc", -1, -1पूर्ण,
			अणु"vdda", 100000, 100पूर्ण,	/* 1.2 V */
			अणु"vddio", 100000, 100पूर्ण,	/* 1.8 V */
		पूर्ण,
	पूर्ण,
	.bus_clk_names = dsi_8916_bus_clk_names,
	.num_bus_clks = ARRAY_SIZE(dsi_8916_bus_clk_names),
	.io_start = अणु 0x1a98000 पूर्ण,
	.num_dsi = 1,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsi_8976_bus_clk_names[] = अणु
	"mdp_core", "iface", "bus",
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_config msm8976_dsi_cfg = अणु
	.io_offset = DSI_6G_REG_SHIFT,
	.reg_cfg = अणु
		.num = 3,
		.regs = अणु
			अणु"gdsc", -1, -1पूर्ण,
			अणु"vdda", 100000, 100पूर्ण,	/* 1.2 V */
			अणु"vddio", 100000, 100पूर्ण,	/* 1.8 V */
		पूर्ण,
	पूर्ण,
	.bus_clk_names = dsi_8976_bus_clk_names,
	.num_bus_clks = ARRAY_SIZE(dsi_8976_bus_clk_names),
	.io_start = अणु 0x1a94000, 0x1a96000 पूर्ण,
	.num_dsi = 2,
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_config msm8994_dsi_cfg = अणु
	.io_offset = DSI_6G_REG_SHIFT,
	.reg_cfg = अणु
		.num = 7,
		.regs = अणु
			अणु"gdsc", -1, -1पूर्ण,
			अणु"vdda", 100000, 100पूर्ण,	/* 1.25 V */
			अणु"vddio", 100000, 100पूर्ण,	/* 1.8 V */
			अणु"vcca", 10000, 100पूर्ण,	/* 1.0 V */
			अणु"vdd", 100000, 100पूर्ण,	/* 1.8 V */
			अणु"lab_reg", -1, -1पूर्ण,
			अणु"ibb_reg", -1, -1पूर्ण,
		पूर्ण,
	पूर्ण,
	.bus_clk_names = dsi_6g_bus_clk_names,
	.num_bus_clks = ARRAY_SIZE(dsi_6g_bus_clk_names),
	.io_start = अणु 0xfd998000, 0xfd9a0000 पूर्ण,
	.num_dsi = 2,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsi_8996_bus_clk_names[] = अणु
	"mdp_core", "iface", "bus", "core_mmss",
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_config msm8996_dsi_cfg = अणु
	.io_offset = DSI_6G_REG_SHIFT,
	.reg_cfg = अणु
		.num = 2,
		.regs = अणु
			अणु"vdda", 18160, 1 पूर्ण,	/* 1.25 V */
			अणु"vcca", 17000, 32 पूर्ण,	/* 0.925 V */
			अणु"vddio", 100000, 100 पूर्ण,/* 1.8 V */
		पूर्ण,
	पूर्ण,
	.bus_clk_names = dsi_8996_bus_clk_names,
	.num_bus_clks = ARRAY_SIZE(dsi_8996_bus_clk_names),
	.io_start = अणु 0x994000, 0x996000 पूर्ण,
	.num_dsi = 2,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsi_msm8998_bus_clk_names[] = अणु
	"iface", "bus", "core",
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_config msm8998_dsi_cfg = अणु
	.io_offset = DSI_6G_REG_SHIFT,
	.reg_cfg = अणु
		.num = 2,
		.regs = अणु
			अणु"vdd", 367000, 16 पूर्ण,	/* 0.9 V */
			अणु"vdda", 62800, 2 पूर्ण,	/* 1.2 V */
		पूर्ण,
	पूर्ण,
	.bus_clk_names = dsi_msm8998_bus_clk_names,
	.num_bus_clks = ARRAY_SIZE(dsi_msm8998_bus_clk_names),
	.io_start = अणु 0xc994000, 0xc996000 पूर्ण,
	.num_dsi = 2,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsi_sdm660_bus_clk_names[] = अणु
	"iface", "bus", "core", "core_mmss",
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_config sdm660_dsi_cfg = अणु
	.io_offset = DSI_6G_REG_SHIFT,
	.reg_cfg = अणु
		.num = 2,
		.regs = अणु
			अणु"vdd", 73400, 32 पूर्ण,	/* 0.9 V */
			अणु"vdda", 12560, 4 पूर्ण,	/* 1.2 V */
		पूर्ण,
	पूर्ण,
	.bus_clk_names = dsi_sdm660_bus_clk_names,
	.num_bus_clks = ARRAY_SIZE(dsi_sdm660_bus_clk_names),
	.io_start = अणु 0xc994000, 0xc996000 पूर्ण,
	.num_dsi = 2,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsi_sdm845_bus_clk_names[] = अणु
	"iface", "bus",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsi_sc7180_bus_clk_names[] = अणु
	"iface", "bus",
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_config sdm845_dsi_cfg = अणु
	.io_offset = DSI_6G_REG_SHIFT,
	.reg_cfg = अणु
		.num = 1,
		.regs = अणु
			अणु"vdda", 21800, 4 पूर्ण,	/* 1.2 V */
		पूर्ण,
	पूर्ण,
	.bus_clk_names = dsi_sdm845_bus_clk_names,
	.num_bus_clks = ARRAY_SIZE(dsi_sdm845_bus_clk_names),
	.io_start = अणु 0xae94000, 0xae96000 पूर्ण,
	.num_dsi = 2,
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_config sc7180_dsi_cfg = अणु
	.io_offset = DSI_6G_REG_SHIFT,
	.reg_cfg = अणु
		.num = 1,
		.regs = अणु
			अणु"vdda", 21800, 4 पूर्ण,	/* 1.2 V */
		पूर्ण,
	पूर्ण,
	.bus_clk_names = dsi_sc7180_bus_clk_names,
	.num_bus_clks = ARRAY_SIZE(dsi_sc7180_bus_clk_names),
	.io_start = अणु 0xae94000 पूर्ण,
	.num_dsi = 1,
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_host_cfg_ops msm_dsi_v2_host_ops = अणु
	.link_clk_set_rate = dsi_link_clk_set_rate_v2,
	.link_clk_enable = dsi_link_clk_enable_v2,
	.link_clk_disable = dsi_link_clk_disable_v2,
	.clk_init_ver = dsi_clk_init_v2,
	.tx_buf_alloc = dsi_tx_buf_alloc_v2,
	.tx_buf_get = dsi_tx_buf_get_v2,
	.tx_buf_put = शून्य,
	.dma_base_get = dsi_dma_base_get_v2,
	.calc_clk_rate = dsi_calc_clk_rate_v2,
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_host_cfg_ops msm_dsi_6g_host_ops = अणु
	.link_clk_set_rate = dsi_link_clk_set_rate_6g,
	.link_clk_enable = dsi_link_clk_enable_6g,
	.link_clk_disable = dsi_link_clk_disable_6g,
	.clk_init_ver = शून्य,
	.tx_buf_alloc = dsi_tx_buf_alloc_6g,
	.tx_buf_get = dsi_tx_buf_get_6g,
	.tx_buf_put = dsi_tx_buf_put_6g,
	.dma_base_get = dsi_dma_base_get_6g,
	.calc_clk_rate = dsi_calc_clk_rate_6g,
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_host_cfg_ops msm_dsi_6g_v2_host_ops = अणु
	.link_clk_set_rate = dsi_link_clk_set_rate_6g,
	.link_clk_enable = dsi_link_clk_enable_6g,
	.link_clk_disable = dsi_link_clk_disable_6g,
	.clk_init_ver = dsi_clk_init_6g_v2,
	.tx_buf_alloc = dsi_tx_buf_alloc_6g,
	.tx_buf_get = dsi_tx_buf_get_6g,
	.tx_buf_put = dsi_tx_buf_put_6g,
	.dma_base_get = dsi_dma_base_get_6g,
	.calc_clk_rate = dsi_calc_clk_rate_6g,
पूर्ण;

अटल स्थिर काष्ठा msm_dsi_cfg_handler dsi_cfg_handlers[] = अणु
	अणुMSM_DSI_VER_MAJOR_V2, MSM_DSI_V2_VER_MINOR_8064,
		&apq8064_dsi_cfg, &msm_dsi_v2_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V1_0,
		&msm8974_apq8084_dsi_cfg, &msm_dsi_6g_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V1_1,
		&msm8974_apq8084_dsi_cfg, &msm_dsi_6g_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V1_1_1,
		&msm8974_apq8084_dsi_cfg, &msm_dsi_6g_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V1_2,
		&msm8974_apq8084_dsi_cfg, &msm_dsi_6g_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V1_3,
		&msm8994_dsi_cfg, &msm_dsi_6g_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V1_3_1,
		&msm8916_dsi_cfg, &msm_dsi_6g_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V1_4_1,
		&msm8996_dsi_cfg, &msm_dsi_6g_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V1_4_2,
		&msm8976_dsi_cfg, &msm_dsi_6g_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V2_1_0,
		&sdm660_dsi_cfg, &msm_dsi_6g_v2_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V2_2_0,
		&msm8998_dsi_cfg, &msm_dsi_6g_v2_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V2_2_1,
		&sdm845_dsi_cfg, &msm_dsi_6g_v2_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V2_3_0,
		&sdm845_dsi_cfg, &msm_dsi_6g_v2_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V2_4_0,
		&sdm845_dsi_cfg, &msm_dsi_6g_v2_host_opsपूर्ण,
	अणुMSM_DSI_VER_MAJOR_6G, MSM_DSI_6G_VER_MINOR_V2_4_1,
		&sc7180_dsi_cfg, &msm_dsi_6g_v2_host_opsपूर्ण,
पूर्ण;

स्थिर काष्ठा msm_dsi_cfg_handler *msm_dsi_cfg_get(u32 major, u32 minor)
अणु
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = शून्य;
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(dsi_cfg_handlers) - 1; i >= 0; i--) अणु
		अगर ((dsi_cfg_handlers[i].major == major) &&
			(dsi_cfg_handlers[i].minor == minor)) अणु
			cfg_hnd = &dsi_cfg_handlers[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस cfg_hnd;
पूर्ण

