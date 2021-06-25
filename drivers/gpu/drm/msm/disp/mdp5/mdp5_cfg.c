<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015 The Linux Foundation. All rights reserved.
 */

#समावेश "mdp5_kms.h"
#समावेश "mdp5_cfg.h"

काष्ठा mdp5_cfg_handler अणु
	पूर्णांक revision;
	काष्ठा mdp5_cfg config;
पूर्ण;

/* mdp5_cfg must be exposed (used in mdp5.xml.h) */
स्थिर काष्ठा mdp5_cfg_hw *mdp5_cfg = शून्य;

अटल स्थिर काष्ठा mdp5_cfg_hw msm8x74v1_config = अणु
	.name = "msm8x74v1",
	.mdp = अणु
		.count = 1,
		.caps = MDP_CAP_SMP |
			0,
	पूर्ण,
	.smp = अणु
		.mmb_count = 22,
		.mmb_size = 4096,
		.clients = अणु
			[SSPP_VIG0] =  1, [SSPP_VIG1] =  4, [SSPP_VIG2] =  7,
			[SSPP_DMA0] = 10, [SSPP_DMA1] = 13,
			[SSPP_RGB0] = 16, [SSPP_RGB1] = 17, [SSPP_RGB2] = 18,
		पूर्ण,
	पूर्ण,
	.ctl = अणु
		.count = 5,
		.base = अणु 0x00500, 0x00600, 0x00700, 0x00800, 0x00900 पूर्ण,
		.flush_hw_mask = 0x0003ffff,
	पूर्ण,
	.pipe_vig = अणु
		.count = 3,
		.base = अणु 0x01100, 0x01500, 0x01900 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP |
			MDP_PIPE_CAP_VFLIP |
			MDP_PIPE_CAP_SCALE |
			MDP_PIPE_CAP_CSC   |
			0,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 3,
		.base = अणु 0x01d00, 0x02100, 0x02500 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP |
			MDP_PIPE_CAP_VFLIP |
			MDP_PIPE_CAP_SCALE |
			0,
	पूर्ण,
	.pipe_dma = अणु
		.count = 2,
		.base = अणु 0x02900, 0x02d00 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP |
			MDP_PIPE_CAP_VFLIP |
			0,
	पूर्ण,
	.lm = अणु
		.count = 5,
		.base = अणु 0x03100, 0x03500, 0x03900, 0x03d00, 0x04100 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 2, .pp = 2, .dspp = 2,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB पूर्ण,
				अणु .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB पूर्ण,
			     पूर्ण,
		.nb_stages = 5,
		.max_width = 2048,
		.max_height = 0xFFFF,
	पूर्ण,
	.dspp = अणु
		.count = 3,
		.base = अणु 0x04500, 0x04900, 0x04d00 पूर्ण,
	पूर्ण,
	.pp = अणु
		.count = 3,
		.base = अणु 0x21a00, 0x21b00, 0x21c00 पूर्ण,
	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x21000, 0x21200, 0x21400, 0x21600 पूर्ण,
		.connect = अणु
			[0] = INTF_eDP,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		पूर्ण,
	पूर्ण,
	.max_clk = 200000000,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_hw msm8x74v2_config = अणु
	.name = "msm8x74",
	.mdp = अणु
		.count = 1,
		.caps = MDP_CAP_SMP |
			0,
	पूर्ण,
	.smp = अणु
		.mmb_count = 22,
		.mmb_size = 4096,
		.clients = अणु
			[SSPP_VIG0] =  1, [SSPP_VIG1] =  4, [SSPP_VIG2] =  7,
			[SSPP_DMA0] = 10, [SSPP_DMA1] = 13,
			[SSPP_RGB0] = 16, [SSPP_RGB1] = 17, [SSPP_RGB2] = 18,
		पूर्ण,
	पूर्ण,
	.ctl = अणु
		.count = 5,
		.base = अणु 0x00500, 0x00600, 0x00700, 0x00800, 0x00900 पूर्ण,
		.flush_hw_mask = 0x0003ffff,
	पूर्ण,
	.pipe_vig = अणु
		.count = 3,
		.base = अणु 0x01100, 0x01500, 0x01900 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_SCALE | MDP_PIPE_CAP_CSC |
				MDP_PIPE_CAP_DECIMATION,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 3,
		.base = अणु 0x01d00, 0x02100, 0x02500 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_SCALE | MDP_PIPE_CAP_DECIMATION,
	पूर्ण,
	.pipe_dma = अणु
		.count = 2,
		.base = अणु 0x02900, 0x02d00 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP,
	पूर्ण,
	.lm = अणु
		.count = 5,
		.base = अणु 0x03100, 0x03500, 0x03900, 0x03d00, 0x04100 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 2, .pp = 2, .dspp = 2,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				अणु .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
			     पूर्ण,
		.nb_stages = 5,
		.max_width = 2048,
		.max_height = 0xFFFF,
	पूर्ण,
	.dspp = अणु
		.count = 3,
		.base = अणु 0x04500, 0x04900, 0x04d00 पूर्ण,
	पूर्ण,
	.ad = अणु
		.count = 2,
		.base = अणु 0x13000, 0x13200 पूर्ण,
	पूर्ण,
	.pp = अणु
		.count = 3,
		.base = अणु 0x12c00, 0x12d00, 0x12e00 पूर्ण,
	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x12400, 0x12600, 0x12800, 0x12a00 पूर्ण,
		.connect = अणु
			[0] = INTF_eDP,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		पूर्ण,
	पूर्ण,
	.max_clk = 320000000,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_hw apq8084_config = अणु
	.name = "apq8084",
	.mdp = अणु
		.count = 1,
		.caps = MDP_CAP_SMP |
			MDP_CAP_SRC_SPLIT |
			0,
	पूर्ण,
	.smp = अणु
		.mmb_count = 44,
		.mmb_size = 8192,
		.clients = अणु
			[SSPP_VIG0] =  1, [SSPP_VIG1] =  4,
			[SSPP_VIG2] =  7, [SSPP_VIG3] = 19,
			[SSPP_DMA0] = 10, [SSPP_DMA1] = 13,
			[SSPP_RGB0] = 16, [SSPP_RGB1] = 17,
			[SSPP_RGB2] = 18, [SSPP_RGB3] = 22,
		पूर्ण,
		.reserved_state[0] = GENMASK(7, 0),	/* first 8 MMBs */
		.reserved = अणु
			/* Two SMP blocks are अटलally tied to RGB pipes: */
			[16] = 2, [17] = 2, [18] = 2, [22] = 2,
		पूर्ण,
	पूर्ण,
	.ctl = अणु
		.count = 5,
		.base = अणु 0x00500, 0x00600, 0x00700, 0x00800, 0x00900 पूर्ण,
		.flush_hw_mask = 0x003fffff,
	पूर्ण,
	.pipe_vig = अणु
		.count = 4,
		.base = अणु 0x01100, 0x01500, 0x01900, 0x01d00 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_SCALE | MDP_PIPE_CAP_CSC |
				MDP_PIPE_CAP_DECIMATION,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 4,
		.base = अणु 0x02100, 0x02500, 0x02900, 0x02d00 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_SCALE | MDP_PIPE_CAP_DECIMATION,
	पूर्ण,
	.pipe_dma = अणु
		.count = 2,
		.base = अणु 0x03100, 0x03500 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP,
	पूर्ण,
	.lm = अणु
		.count = 6,
		.base = अणु 0x03900, 0x03d00, 0x04100, 0x04500, 0x04900, 0x04d00 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY |
					  MDP_LM_CAP_PAIR, पूर्ण,
				अणु .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 2, .pp = 2, .dspp = 2,
				  .caps = MDP_LM_CAP_DISPLAY |
					  MDP_LM_CAP_PAIR, पूर्ण,
				अणु .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				अणु .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				अणु .id = 5, .pp = 3, .dspp = 3,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
			     पूर्ण,
		.nb_stages = 5,
		.max_width = 2048,
		.max_height = 0xFFFF,
	पूर्ण,
	.dspp = अणु
		.count = 4,
		.base = अणु 0x05100, 0x05500, 0x05900, 0x05d00 पूर्ण,

	पूर्ण,
	.ad = अणु
		.count = 3,
		.base = अणु 0x13400, 0x13600, 0x13800 पूर्ण,
	पूर्ण,
	.pp = अणु
		.count = 4,
		.base = अणु 0x12e00, 0x12f00, 0x13000, 0x13100 पूर्ण,
	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x12400, 0x12600, 0x12800, 0x12a00, 0x12c00 पूर्ण,
		.connect = अणु
			[0] = INTF_eDP,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		पूर्ण,
	पूर्ण,
	.max_clk = 320000000,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_hw msm8x16_config = अणु
	.name = "msm8x16",
	.mdp = अणु
		.count = 1,
		.base = अणु 0x0 पूर्ण,
		.caps = MDP_CAP_SMP |
			0,
	पूर्ण,
	.smp = अणु
		.mmb_count = 8,
		.mmb_size = 8192,
		.clients = अणु
			[SSPP_VIG0] = 1, [SSPP_DMA0] = 4,
			[SSPP_RGB0] = 7, [SSPP_RGB1] = 8,
		पूर्ण,
	पूर्ण,
	.ctl = अणु
		.count = 5,
		.base = अणु 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 पूर्ण,
		.flush_hw_mask = 0x4003ffff,
	पूर्ण,
	.pipe_vig = अणु
		.count = 1,
		.base = अणु 0x04000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_SCALE | MDP_PIPE_CAP_CSC |
				MDP_PIPE_CAP_DECIMATION,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 2,
		.base = अणु 0x14000, 0x16000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_DECIMATION,
	पूर्ण,
	.pipe_dma = अणु
		.count = 1,
		.base = अणु 0x24000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP,
	पूर्ण,
	.lm = अणु
		.count = 2, /* LM0 and LM3 */
		.base = अणु 0x44000, 0x47000 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB पूर्ण,
			     पूर्ण,
		.nb_stages = 8,
		.max_width = 2048,
		.max_height = 0xFFFF,
	पूर्ण,
	.dspp = अणु
		.count = 1,
		.base = अणु 0x54000 पूर्ण,

	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x00000, 0x6a800 पूर्ण,
		.connect = अणु
			[0] = INTF_DISABLED,
			[1] = INTF_DSI,
		पूर्ण,
	पूर्ण,
	.max_clk = 320000000,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_hw msm8x36_config = अणु
	.name = "msm8x36",
	.mdp = अणु
		.count = 1,
		.base = अणु 0x0 पूर्ण,
		.caps = MDP_CAP_SMP |
			0,
	पूर्ण,
	.smp = अणु
		.mmb_count = 8,
		.mmb_size = 10240,
		.clients = अणु
			[SSPP_VIG0] = 1, [SSPP_DMA0] = 4,
			[SSPP_RGB0] = 7, [SSPP_RGB1] = 8,
		पूर्ण,
	पूर्ण,
	.ctl = अणु
		.count = 3,
		.base = अणु 0x01000, 0x01200, 0x01400 पूर्ण,
		.flush_hw_mask = 0x4003ffff,
	पूर्ण,
	.pipe_vig = अणु
		.count = 1,
		.base = अणु 0x04000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_SCALE | MDP_PIPE_CAP_CSC |
				MDP_PIPE_CAP_DECIMATION,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 2,
		.base = अणु 0x14000, 0x16000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_DECIMATION,
	पूर्ण,
	.pipe_dma = अणु
		.count = 1,
		.base = अणु 0x24000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP,
	पूर्ण,
	.lm = अणु
		.count = 2,
		.base = अणु 0x44000, 0x47000 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 1, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				पूर्ण,
		.nb_stages = 8,
		.max_width = 2560,
		.max_height = 0xFFFF,
	पूर्ण,
	.pp = अणु
		.count = 1,
		.base = अणु 0x70000 पूर्ण,
	पूर्ण,
	.ad = अणु
		.count = 1,
		.base = अणु 0x78000 पूर्ण,
	पूर्ण,
	.dspp = अणु
		.count = 1,
		.base = अणु 0x54000 पूर्ण,
	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x00000, 0x6a800, 0x6b000 पूर्ण,
		.connect = अणु
			[0] = INTF_DISABLED,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
		पूर्ण,
	पूर्ण,
	.max_clk = 366670000,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_hw msm8x94_config = अणु
	.name = "msm8x94",
	.mdp = अणु
		.count = 1,
		.caps = MDP_CAP_SMP |
			MDP_CAP_SRC_SPLIT |
			0,
	पूर्ण,
	.smp = अणु
		.mmb_count = 44,
		.mmb_size = 8192,
		.clients = अणु
			[SSPP_VIG0] =  1, [SSPP_VIG1] =  4,
			[SSPP_VIG2] =  7, [SSPP_VIG3] = 19,
			[SSPP_DMA0] = 10, [SSPP_DMA1] = 13,
			[SSPP_RGB0] = 16, [SSPP_RGB1] = 17,
			[SSPP_RGB2] = 18, [SSPP_RGB3] = 22,
		पूर्ण,
		.reserved_state[0] = GENMASK(23, 0),	/* first 24 MMBs */
		.reserved = अणु
			 [1] = 1,  [4] = 1,  [7] = 1, [19] = 1,
			[16] = 5, [17] = 5, [18] = 5, [22] = 5,
		पूर्ण,
	पूर्ण,
	.ctl = अणु
		.count = 5,
		.base = अणु 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 पूर्ण,
		.flush_hw_mask = 0xf0ffffff,
	पूर्ण,
	.pipe_vig = अणु
		.count = 4,
		.base = अणु 0x04000, 0x06000, 0x08000, 0x0a000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_SCALE | MDP_PIPE_CAP_CSC |
				MDP_PIPE_CAP_DECIMATION,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 4,
		.base = अणु 0x14000, 0x16000, 0x18000, 0x1a000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_SCALE | MDP_PIPE_CAP_DECIMATION,
	पूर्ण,
	.pipe_dma = अणु
		.count = 2,
		.base = अणु 0x24000, 0x26000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP,
	पूर्ण,
	.lm = अणु
		.count = 6,
		.base = अणु 0x44000, 0x45000, 0x46000, 0x47000, 0x48000, 0x49000 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY |
					  MDP_LM_CAP_PAIR, पूर्ण,
				अणु .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 2, .pp = 2, .dspp = 2,
				  .caps = MDP_LM_CAP_DISPLAY |
					  MDP_LM_CAP_PAIR, पूर्ण,
				अणु .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				अणु .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				अणु .id = 5, .pp = 3, .dspp = 3,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
			     पूर्ण,
		.nb_stages = 8,
		.max_width = 2048,
		.max_height = 0xFFFF,
	पूर्ण,
	.dspp = अणु
		.count = 4,
		.base = अणु 0x54000, 0x56000, 0x58000, 0x5a000 पूर्ण,

	पूर्ण,
	.ad = अणु
		.count = 3,
		.base = अणु 0x78000, 0x78800, 0x79000 पूर्ण,
	पूर्ण,
	.pp = अणु
		.count = 4,
		.base = अणु 0x70000, 0x70800, 0x71000, 0x71800 पूर्ण,
	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x6a000, 0x6a800, 0x6b000, 0x6b800, 0x6c000 पूर्ण,
		.connect = अणु
			[0] = INTF_DISABLED,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		पूर्ण,
	पूर्ण,
	.max_clk = 400000000,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_hw msm8x96_config = अणु
	.name = "msm8x96",
	.mdp = अणु
		.count = 1,
		.caps = MDP_CAP_DSC |
			MDP_CAP_CDM |
			MDP_CAP_SRC_SPLIT |
			0,
	पूर्ण,
	.ctl = अणु
		.count = 5,
		.base = अणु 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 पूर्ण,
		.flush_hw_mask = 0xf4ffffff,
	पूर्ण,
	.pipe_vig = अणु
		.count = 4,
		.base = अणु 0x04000, 0x06000, 0x08000, 0x0a000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SCALE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 4,
		.base = अणु 0x14000, 0x16000, 0x18000, 0x1a000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SCALE	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_dma = अणु
		.count = 2,
		.base = अणु 0x24000, 0x26000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_cursor = अणु
		.count = 2,
		.base = अणु 0x34000, 0x36000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CURSOR	|
			0,
	पूर्ण,

	.lm = अणु
		.count = 6,
		.base = अणु 0x44000, 0x45000, 0x46000, 0x47000, 0x48000, 0x49000 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY |
					  MDP_LM_CAP_PAIR, पूर्ण,
				अणु .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 2, .pp = 2, .dspp = -1,
				  .caps = MDP_LM_CAP_DISPLAY |
					  MDP_LM_CAP_PAIR, पूर्ण,
				अणु .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				अणु .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				अणु .id = 5, .pp = 3, .dspp = -1,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
			     पूर्ण,
		.nb_stages = 8,
		.max_width = 2560,
		.max_height = 0xFFFF,
	पूर्ण,
	.dspp = अणु
		.count = 2,
		.base = अणु 0x54000, 0x56000 पूर्ण,
	पूर्ण,
	.ad = अणु
		.count = 3,
		.base = अणु 0x78000, 0x78800, 0x79000 पूर्ण,
	पूर्ण,
	.pp = अणु
		.count = 4,
		.base = अणु 0x70000, 0x70800, 0x71000, 0x71800 पूर्ण,
	पूर्ण,
	.cdm = अणु
		.count = 1,
		.base = अणु 0x79200 पूर्ण,
	पूर्ण,
	.dsc = अणु
		.count = 2,
		.base = अणु 0x80000, 0x80400 पूर्ण,
	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x6a000, 0x6a800, 0x6b000, 0x6b800, 0x6c000 पूर्ण,
		.connect = अणु
			[0] = INTF_DISABLED,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		पूर्ण,
	पूर्ण,
	.max_clk = 412500000,
पूर्ण;

स्थिर काष्ठा mdp5_cfg_hw msm8x76_config = अणु
	.name = "msm8x76",
	.mdp = अणु
		.count = 1,
		.caps = MDP_CAP_SMP |
			MDP_CAP_DSC |
			MDP_CAP_SRC_SPLIT |
			0,
	पूर्ण,
	.ctl = अणु
		.count = 3,
		.base = अणु 0x01000, 0x01200, 0x01400 पूर्ण,
		.flush_hw_mask = 0xffffffff,
	पूर्ण,
	.smp = अणु
		.mmb_count = 10,
		.mmb_size = 10240,
		.clients = अणु
			[SSPP_VIG0] = 1, [SSPP_VIG1] = 9,
			[SSPP_DMA0] = 4,
			[SSPP_RGB0] = 7, [SSPP_RGB1] = 8,
		पूर्ण,
	पूर्ण,
	.pipe_vig = अणु
		.count = 2,
		.base = अणु 0x04000, 0x06000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SCALE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 2,
		.base = अणु 0x14000, 0x16000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_dma = अणु
		.count = 1,
		.base = अणु 0x24000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_cursor = अणु
		.count = 1,
		.base = अणु 0x440DC पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CURSOR	|
			0,
	पूर्ण,
	.lm = अणु
		.count = 2,
		.base = अणु 0x44000, 0x45000 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 1, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB पूर्ण,
			     पूर्ण,
		.nb_stages = 8,
		.max_width = 2560,
		.max_height = 0xFFFF,
	पूर्ण,
	.dspp = अणु
		.count = 1,
		.base = अणु 0x54000 पूर्ण,

	पूर्ण,
	.pp = अणु
		.count = 3,
		.base = अणु 0x70000, 0x70800, 0x72000 पूर्ण,
	पूर्ण,
	.dsc = अणु
		.count = 2,
		.base = अणु 0x80000, 0x80400 पूर्ण,
	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x6a000, 0x6a800, 0x6b000 पूर्ण,
		.connect = अणु
			[0] = INTF_DISABLED,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
		पूर्ण,
	पूर्ण,
	.max_clk = 360000000,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_hw msm8917_config = अणु
	.name = "msm8917",
	.mdp = अणु
		.count = 1,
		.caps = MDP_CAP_CDM,
	पूर्ण,
	.ctl = अणु
		.count = 3,
		.base = अणु 0x01000, 0x01200, 0x01400 पूर्ण,
		.flush_hw_mask = 0xffffffff,
	पूर्ण,
	.pipe_vig = अणु
		.count = 1,
		.base = अणु 0x04000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SCALE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 2,
		.base = अणु 0x14000, 0x16000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_dma = अणु
		.count = 1,
		.base = अणु 0x24000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_cursor = अणु
		.count = 1,
		.base = अणु 0x34000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CURSOR	|
			0,
	पूर्ण,

	.lm = अणु
		.count = 2,
		.base = अणु 0x44000, 0x45000 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 1, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB पूर्ण,
			     पूर्ण,
		.nb_stages = 8,
		.max_width = 2048,
		.max_height = 0xFFFF,
	पूर्ण,
	.dspp = अणु
		.count = 1,
		.base = अणु 0x54000 पूर्ण,

	पूर्ण,
	.pp = अणु
		.count = 1,
		.base = अणु 0x70000 पूर्ण,
	पूर्ण,
	.cdm = अणु
		.count = 1,
		.base = अणु 0x79200 पूर्ण,
	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x6a000, 0x6a800 पूर्ण,
		.connect = अणु
			[0] = INTF_DISABLED,
			[1] = INTF_DSI,
		पूर्ण,
	पूर्ण,
	.max_clk = 320000000,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_hw msm8998_config = अणु
	.name = "msm8998",
	.mdp = अणु
		.count = 1,
		.caps = MDP_CAP_DSC |
			MDP_CAP_CDM |
			MDP_CAP_SRC_SPLIT |
			0,
	पूर्ण,
	.ctl = अणु
		.count = 5,
		.base = अणु 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 पूर्ण,
		.flush_hw_mask = 0xf7ffffff,
	पूर्ण,
	.pipe_vig = अणु
		.count = 4,
		.base = अणु 0x04000, 0x06000, 0x08000, 0x0a000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SCALE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 4,
		.base = अणु 0x14000, 0x16000, 0x18000, 0x1a000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SCALE	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_dma = अणु
		.count = 2, /* driver supports max of 2 currently */
		.base = अणु 0x24000, 0x26000, 0x28000, 0x2a000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_cursor = अणु
		.count = 2,
		.base = अणु 0x34000, 0x36000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CURSOR	|
			0,
	पूर्ण,

	.lm = अणु
		.count = 6,
		.base = अणु 0x44000, 0x45000, 0x46000, 0x47000, 0x48000, 0x49000 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY |
					  MDP_LM_CAP_PAIR, पूर्ण,
				अणु .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 2, .pp = 2, .dspp = -1,
				  .caps = MDP_LM_CAP_DISPLAY |
					  MDP_LM_CAP_PAIR, पूर्ण,
				अणु .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				अणु .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				अणु .id = 5, .pp = 3, .dspp = -1,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
			     पूर्ण,
		.nb_stages = 8,
		.max_width = 2560,
		.max_height = 0xFFFF,
	पूर्ण,
	.dspp = अणु
		.count = 2,
		.base = अणु 0x54000, 0x56000 पूर्ण,
	पूर्ण,
	.ad = अणु
		.count = 3,
		.base = अणु 0x78000, 0x78800, 0x79000 पूर्ण,
	पूर्ण,
	.pp = अणु
		.count = 4,
		.base = अणु 0x70000, 0x70800, 0x71000, 0x71800 पूर्ण,
	पूर्ण,
	.cdm = अणु
		.count = 1,
		.base = अणु 0x79200 पूर्ण,
	पूर्ण,
	.dsc = अणु
		.count = 2,
		.base = अणु 0x80000, 0x80400 पूर्ण,
	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x6a000, 0x6a800, 0x6b000, 0x6b800, 0x6c000 पूर्ण,
		.connect = अणु
			[0] = INTF_eDP,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		पूर्ण,
	पूर्ण,
	.max_clk = 412500000,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_hw sdm630_config = अणु
	.name = "sdm630",
	.mdp = अणु
		.count = 1,
		.caps = MDP_CAP_CDM |
			MDP_CAP_SRC_SPLIT |
			0,
	पूर्ण,
	.ctl = अणु
		.count = 5,
		.base = अणु 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 पूर्ण,
		.flush_hw_mask = 0xf4ffffff,
	पूर्ण,
	.pipe_vig = अणु
		.count = 1,
		.base = अणु 0x04000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SCALE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 4,
		.base = अणु 0x14000, 0x16000, 0x18000, 0x1a000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SCALE	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_dma = अणु
		.count = 2, /* driver supports max of 2 currently */
		.base = अणु 0x24000, 0x26000, 0x28000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_cursor = अणु
		.count = 1,
		.base = अणु 0x34000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CURSOR	|
			0,
	पूर्ण,

	.lm = अणु
		.count = 2,
		.base = अणु 0x44000, 0x46000 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY |
					  MDP_LM_CAP_PAIR, पूर्ण,
				अणु .id = 1, .pp = 1, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				पूर्ण,
		.nb_stages = 8,
		.max_width = 2048,
		.max_height = 0xFFFF,
	पूर्ण,
	.dspp = अणु
		.count = 1,
		.base = अणु 0x54000 पूर्ण,
	पूर्ण,
	.ad = अणु
		.count = 2,
		.base = अणु 0x78000, 0x78800 पूर्ण,
	पूर्ण,
	.pp = अणु
		.count = 3,
		.base = अणु 0x70000, 0x71000, 0x72000 पूर्ण,
	पूर्ण,
	.cdm = अणु
		.count = 1,
		.base = अणु 0x79200 पूर्ण,
	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x6a000, 0x6a800 पूर्ण,
		.connect = अणु
			[0] = INTF_DISABLED,
			[1] = INTF_DSI,
		पूर्ण,
	पूर्ण,
	.max_clk = 412500000,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_hw sdm660_config = अणु
	.name = "sdm660",
	.mdp = अणु
		.count = 1,
		.caps = MDP_CAP_DSC |
			MDP_CAP_CDM |
			MDP_CAP_SRC_SPLIT |
			0,
	पूर्ण,
	.ctl = अणु
		.count = 5,
		.base = अणु 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 पूर्ण,
		.flush_hw_mask = 0xf4ffffff,
	पूर्ण,
	.pipe_vig = अणु
		.count = 2,
		.base = अणु 0x04000, 0x6000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SCALE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_rgb = अणु
		.count = 4,
		.base = अणु 0x14000, 0x16000, 0x18000, 0x1a000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SCALE	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_dma = अणु
		.count = 2, /* driver supports max of 2 currently */
		.base = अणु 0x24000, 0x26000, 0x28000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	पूर्ण,
	.pipe_cursor = अणु
		.count = 1,
		.base = अणु 0x34000 पूर्ण,
		.caps = MDP_PIPE_CAP_HFLIP	|
			MDP_PIPE_CAP_VFLIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CURSOR	|
			0,
	पूर्ण,

	.lm = अणु
		.count = 4,
		.base = अणु 0x44000, 0x45000, 0x46000, 0x49000 पूर्ण,
		.instances = अणु
				अणु .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_LM_CAP_DISPLAY |
					  MDP_LM_CAP_PAIR, पूर्ण,
				अणु .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_LM_CAP_DISPLAY, पूर्ण,
				अणु .id = 2, .pp = 2, .dspp = -1,
				  .caps = MDP_LM_CAP_DISPLAY |
					  MDP_LM_CAP_PAIR, पूर्ण,
				अणु .id = 3, .pp = 3, .dspp = -1,
				  .caps = MDP_LM_CAP_WB, पूर्ण,
				पूर्ण,
		.nb_stages = 8,
		.max_width = 2560,
		.max_height = 0xFFFF,
	पूर्ण,
	.dspp = अणु
		.count = 2,
		.base = अणु 0x54000, 0x56000 पूर्ण,
	पूर्ण,
	.ad = अणु
		.count = 2,
		.base = अणु 0x78000, 0x78800 पूर्ण,
	पूर्ण,
	.pp = अणु
		.count = 5,
		.base = अणु 0x70000, 0x70800, 0x71000, 0x71800, 0x72000 पूर्ण,
	पूर्ण,
	.cdm = अणु
		.count = 1,
		.base = अणु 0x79200 पूर्ण,
	पूर्ण,
	.dsc = अणु
		.count = 2,
		.base = अणु 0x80000, 0x80400 पूर्ण,
	पूर्ण,
	.पूर्णांकf = अणु
		.base = अणु 0x6a000, 0x6a800, 0x6b000, 0x6b800 पूर्ण,
		.connect = अणु
			[0] = INTF_DISABLED,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		पूर्ण,
	पूर्ण,
	.max_clk = 412500000,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_handler cfg_handlers_v1[] = अणु
	अणु .revision = 0, .config = अणु .hw = &msm8x74v1_config पूर्ण पूर्ण,
	अणु .revision = 2, .config = अणु .hw = &msm8x74v2_config पूर्ण पूर्ण,
	अणु .revision = 3, .config = अणु .hw = &apq8084_config पूर्ण पूर्ण,
	अणु .revision = 6, .config = अणु .hw = &msm8x16_config पूर्ण पूर्ण,
	अणु .revision = 8, .config = अणु .hw = &msm8x36_config पूर्ण पूर्ण,
	अणु .revision = 9, .config = अणु .hw = &msm8x94_config पूर्ण पूर्ण,
	अणु .revision = 7, .config = अणु .hw = &msm8x96_config पूर्ण पूर्ण,
	अणु .revision = 11, .config = अणु .hw = &msm8x76_config पूर्ण पूर्ण,
	अणु .revision = 15, .config = अणु .hw = &msm8917_config पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mdp5_cfg_handler cfg_handlers_v3[] = अणु
	अणु .revision = 0, .config = अणु .hw = &msm8998_config पूर्ण पूर्ण,
	अणु .revision = 2, .config = अणु .hw = &sdm660_config पूर्ण पूर्ण,
	अणु .revision = 3, .config = अणु .hw = &sdm630_config पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा mdp5_cfg_platक्रमm *mdp5_get_config(काष्ठा platक्रमm_device *dev);

स्थिर काष्ठा mdp5_cfg_hw *mdp5_cfg_get_hw_config(काष्ठा mdp5_cfg_handler *cfg_handler)
अणु
	वापस cfg_handler->config.hw;
पूर्ण

काष्ठा mdp5_cfg *mdp5_cfg_get_config(काष्ठा mdp5_cfg_handler *cfg_handler)
अणु
	वापस &cfg_handler->config;
पूर्ण

पूर्णांक mdp5_cfg_get_hw_rev(काष्ठा mdp5_cfg_handler *cfg_handler)
अणु
	वापस cfg_handler->revision;
पूर्ण

व्योम mdp5_cfg_destroy(काष्ठा mdp5_cfg_handler *cfg_handler)
अणु
	kमुक्त(cfg_handler);
पूर्ण

काष्ठा mdp5_cfg_handler *mdp5_cfg_init(काष्ठा mdp5_kms *mdp5_kms,
		uपूर्णांक32_t major, uपूर्णांक32_t minor)
अणु
	काष्ठा drm_device *dev = mdp5_kms->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev);
	काष्ठा mdp5_cfg_handler *cfg_handler;
	स्थिर काष्ठा mdp5_cfg_handler *cfg_handlers;
	काष्ठा mdp5_cfg_platक्रमm *pconfig;
	पूर्णांक i, ret = 0, num_handlers;

	cfg_handler = kzalloc(माप(*cfg_handler), GFP_KERNEL);
	अगर (unlikely(!cfg_handler)) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	चयन (major) अणु
	हाल 1:
		cfg_handlers = cfg_handlers_v1;
		num_handlers = ARRAY_SIZE(cfg_handlers_v1);
		अवरोध;
	हाल 3:
		cfg_handlers = cfg_handlers_v3;
		num_handlers = ARRAY_SIZE(cfg_handlers_v3);
		अवरोध;
	शेष:
		DRM_DEV_ERROR(dev->dev, "unexpected MDP major version: v%d.%d\n",
				major, minor);
		ret = -ENXIO;
		जाओ fail;
	पूर्ण

	/* only after mdp5_cfg global poपूर्णांकer's init can we access the hw */
	क्रम (i = 0; i < num_handlers; i++) अणु
		अगर (cfg_handlers[i].revision != minor)
			जारी;
		mdp5_cfg = cfg_handlers[i].config.hw;

		अवरोध;
	पूर्ण
	अगर (unlikely(!mdp5_cfg)) अणु
		DRM_DEV_ERROR(dev->dev, "unexpected MDP minor revision: v%d.%d\n",
				major, minor);
		ret = -ENXIO;
		जाओ fail;
	पूर्ण

	cfg_handler->revision = minor;
	cfg_handler->config.hw = mdp5_cfg;

	pconfig = mdp5_get_config(pdev);
	स_नकल(&cfg_handler->config.platक्रमm, pconfig, माप(*pconfig));

	DBG("MDP5: %s hw config selected", mdp5_cfg->name);

	वापस cfg_handler;

fail:
	अगर (cfg_handler)
		mdp5_cfg_destroy(cfg_handler);

	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा mdp5_cfg_platक्रमm *mdp5_get_config(काष्ठा platक्रमm_device *dev)
अणु
	अटल काष्ठा mdp5_cfg_platक्रमm config = अणुपूर्ण;

	config.iommu = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);

	वापस &config;
पूर्ण
