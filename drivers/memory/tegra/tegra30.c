<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/memory/tegra30-mc.h>

#समावेश "mc.h"

अटल स्थिर अचिन्हित दीर्घ tegra30_mc_emem_regs[] = अणु
	MC_EMEM_ARB_CFG,
	MC_EMEM_ARB_OUTSTANDING_REQ,
	MC_EMEM_ARB_TIMING_RCD,
	MC_EMEM_ARB_TIMING_RP,
	MC_EMEM_ARB_TIMING_RC,
	MC_EMEM_ARB_TIMING_RAS,
	MC_EMEM_ARB_TIMING_FAW,
	MC_EMEM_ARB_TIMING_RRD,
	MC_EMEM_ARB_TIMING_RAP2PRE,
	MC_EMEM_ARB_TIMING_WAP2PRE,
	MC_EMEM_ARB_TIMING_R2R,
	MC_EMEM_ARB_TIMING_W2W,
	MC_EMEM_ARB_TIMING_R2W,
	MC_EMEM_ARB_TIMING_W2R,
	MC_EMEM_ARB_DA_TURNS,
	MC_EMEM_ARB_DA_COVERS,
	MC_EMEM_ARB_MISC0,
	MC_EMEM_ARB_RING1_THROTTLE,
पूर्ण;

अटल स्थिर काष्ठा tegra_mc_client tegra30_mc_clients[] = अणु
	अणु
		.id = 0x00,
		.name = "ptcr",
		.swgroup = TEGRA_SWGROUP_PTC,
		.la = अणु
			.reg = 0x34c,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x0,
		पूर्ण,
		.fअगरo_size = 16 * 2,
	पूर्ण, अणु
		.id = 0x01,
		.name = "display0a",
		.swgroup = TEGRA_SWGROUP_DC,
		.smmu = अणु
			.reg = 0x228,
			.bit = 1,
		पूर्ण,
		.la = अणु
			.reg = 0x2e8,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x4e,
		पूर्ण,
		.fअगरo_size = 16 * 128,
	पूर्ण, अणु
		.id = 0x02,
		.name = "display0ab",
		.swgroup = TEGRA_SWGROUP_DCB,
		.smmu = अणु
			.reg = 0x228,
			.bit = 2,
		पूर्ण,
		.la = अणु
			.reg = 0x2f4,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x4e,
		पूर्ण,
		.fअगरo_size = 16 * 128,
	पूर्ण, अणु
		.id = 0x03,
		.name = "display0b",
		.swgroup = TEGRA_SWGROUP_DC,
		.smmu = अणु
			.reg = 0x228,
			.bit = 3,
		पूर्ण,
		.la = अणु
			.reg = 0x2e8,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x4e,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x04,
		.name = "display0bb",
		.swgroup = TEGRA_SWGROUP_DCB,
		.smmu = अणु
			.reg = 0x228,
			.bit = 4,
		पूर्ण,
		.la = अणु
			.reg = 0x2f4,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x4e,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x05,
		.name = "display0c",
		.swgroup = TEGRA_SWGROUP_DC,
		.smmu = अणु
			.reg = 0x228,
			.bit = 5,
		पूर्ण,
		.la = अणु
			.reg = 0x2ec,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x4e,
		पूर्ण,
		.fअगरo_size = 16 * 128,
	पूर्ण, अणु
		.id = 0x06,
		.name = "display0cb",
		.swgroup = TEGRA_SWGROUP_DCB,
		.smmu = अणु
			.reg = 0x228,
			.bit = 6,
		पूर्ण,
		.la = अणु
			.reg = 0x2f8,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x4e,
		पूर्ण,
		.fअगरo_size = 16 * 128,
	पूर्ण, अणु
		.id = 0x07,
		.name = "display1b",
		.swgroup = TEGRA_SWGROUP_DC,
		.smmu = अणु
			.reg = 0x228,
			.bit = 7,
		पूर्ण,
		.la = अणु
			.reg = 0x2ec,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x4e,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x08,
		.name = "display1bb",
		.swgroup = TEGRA_SWGROUP_DCB,
		.smmu = अणु
			.reg = 0x228,
			.bit = 8,
		पूर्ण,
		.la = अणु
			.reg = 0x2f8,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x4e,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x09,
		.name = "eppup",
		.swgroup = TEGRA_SWGROUP_EPP,
		.smmu = अणु
			.reg = 0x228,
			.bit = 9,
		पूर्ण,
		.la = अणु
			.reg = 0x300,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x17,
		पूर्ण,
		.fअगरo_size = 16 * 8,
	पूर्ण, अणु
		.id = 0x0a,
		.name = "g2pr",
		.swgroup = TEGRA_SWGROUP_G2,
		.smmu = अणु
			.reg = 0x228,
			.bit = 10,
		पूर्ण,
		.la = अणु
			.reg = 0x308,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x09,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x0b,
		.name = "g2sr",
		.swgroup = TEGRA_SWGROUP_G2,
		.smmu = अणु
			.reg = 0x228,
			.bit = 11,
		पूर्ण,
		.la = अणु
			.reg = 0x308,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x09,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x0c,
		.name = "mpeunifbr",
		.swgroup = TEGRA_SWGROUP_MPE,
		.smmu = अणु
			.reg = 0x228,
			.bit = 12,
		पूर्ण,
		.la = अणु
			.reg = 0x328,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x50,
		पूर्ण,
		.fअगरo_size = 16 * 8,
	पूर्ण, अणु
		.id = 0x0d,
		.name = "viruv",
		.swgroup = TEGRA_SWGROUP_VI,
		.smmu = अणु
			.reg = 0x228,
			.bit = 13,
		पूर्ण,
		.la = अणु
			.reg = 0x364,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x2c,
		पूर्ण,
		.fअगरo_size = 16 * 8,
	पूर्ण, अणु
		.id = 0x0e,
		.name = "afir",
		.swgroup = TEGRA_SWGROUP_AFI,
		.smmu = अणु
			.reg = 0x228,
			.bit = 14,
		पूर्ण,
		.la = अणु
			.reg = 0x2e0,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x10,
		पूर्ण,
		.fअगरo_size = 16 * 32,
	पूर्ण, अणु
		.id = 0x0f,
		.name = "avpcarm7r",
		.swgroup = TEGRA_SWGROUP_AVPC,
		.smmu = अणु
			.reg = 0x228,
			.bit = 15,
		पूर्ण,
		.la = अणु
			.reg = 0x2e4,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x04,
		पूर्ण,
		.fअगरo_size = 16 * 2,
	पूर्ण, अणु
		.id = 0x10,
		.name = "displayhc",
		.swgroup = TEGRA_SWGROUP_DC,
		.smmu = अणु
			.reg = 0x228,
			.bit = 16,
		पूर्ण,
		.la = अणु
			.reg = 0x2f0,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
		.fअगरo_size = 16 * 2,
	पूर्ण, अणु
		.id = 0x11,
		.name = "displayhcb",
		.swgroup = TEGRA_SWGROUP_DCB,
		.smmu = अणु
			.reg = 0x228,
			.bit = 17,
		पूर्ण,
		.la = अणु
			.reg = 0x2fc,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
		.fअगरo_size = 16 * 2,
	पूर्ण, अणु
		.id = 0x12,
		.name = "fdcdrd",
		.swgroup = TEGRA_SWGROUP_NV,
		.smmu = अणु
			.reg = 0x228,
			.bit = 18,
		पूर्ण,
		.la = अणु
			.reg = 0x334,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x0a,
		पूर्ण,
		.fअगरo_size = 16 * 48,
	पूर्ण, अणु
		.id = 0x13,
		.name = "fdcdrd2",
		.swgroup = TEGRA_SWGROUP_NV2,
		.smmu = अणु
			.reg = 0x228,
			.bit = 19,
		पूर्ण,
		.la = अणु
			.reg = 0x33c,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x0a,
		पूर्ण,
		.fअगरo_size = 16 * 48,
	पूर्ण, अणु
		.id = 0x14,
		.name = "g2dr",
		.swgroup = TEGRA_SWGROUP_G2,
		.smmu = अणु
			.reg = 0x228,
			.bit = 20,
		पूर्ण,
		.la = अणु
			.reg = 0x30c,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x0a,
		पूर्ण,
		.fअगरo_size = 16 * 48,
	पूर्ण, अणु
		.id = 0x15,
		.name = "hdar",
		.swgroup = TEGRA_SWGROUP_HDA,
		.smmu = अणु
			.reg = 0x228,
			.bit = 21,
		पूर्ण,
		.la = अणु
			.reg = 0x318,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
		.fअगरo_size = 16 * 16,
	पूर्ण, अणु
		.id = 0x16,
		.name = "host1xdmar",
		.swgroup = TEGRA_SWGROUP_HC,
		.smmu = अणु
			.reg = 0x228,
			.bit = 22,
		पूर्ण,
		.la = अणु
			.reg = 0x310,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x05,
		पूर्ण,
		.fअगरo_size = 16 * 16,
	पूर्ण, अणु
		.id = 0x17,
		.name = "host1xr",
		.swgroup = TEGRA_SWGROUP_HC,
		.smmu = अणु
			.reg = 0x228,
			.bit = 23,
		पूर्ण,
		.la = अणु
			.reg = 0x310,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x50,
		पूर्ण,
		.fअगरo_size = 16 * 8,
	पूर्ण, अणु
		.id = 0x18,
		.name = "idxsrd",
		.swgroup = TEGRA_SWGROUP_NV,
		.smmu = अणु
			.reg = 0x228,
			.bit = 24,
		पूर्ण,
		.la = अणु
			.reg = 0x334,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x13,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x19,
		.name = "idxsrd2",
		.swgroup = TEGRA_SWGROUP_NV2,
		.smmu = अणु
			.reg = 0x228,
			.bit = 25,
		पूर्ण,
		.la = अणु
			.reg = 0x33c,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x13,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x1a,
		.name = "mpe_ipred",
		.swgroup = TEGRA_SWGROUP_MPE,
		.smmu = अणु
			.reg = 0x228,
			.bit = 26,
		पूर्ण,
		.la = अणु
			.reg = 0x328,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
		.fअगरo_size = 16 * 2,
	पूर्ण, अणु
		.id = 0x1b,
		.name = "mpeamemrd",
		.swgroup = TEGRA_SWGROUP_MPE,
		.smmu = अणु
			.reg = 0x228,
			.bit = 27,
		पूर्ण,
		.la = अणु
			.reg = 0x32c,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x42,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x1c,
		.name = "mpecsrd",
		.swgroup = TEGRA_SWGROUP_MPE,
		.smmu = अणु
			.reg = 0x228,
			.bit = 28,
		पूर्ण,
		.la = अणु
			.reg = 0x32c,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
		.fअगरo_size = 16 * 8,
	पूर्ण, अणु
		.id = 0x1d,
		.name = "ppcsahbdmar",
		.swgroup = TEGRA_SWGROUP_PPCS,
		.smmu = अणु
			.reg = 0x228,
			.bit = 29,
		पूर्ण,
		.la = अणु
			.reg = 0x344,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x10,
		पूर्ण,
		.fअगरo_size = 16 * 2,
	पूर्ण, अणु
		.id = 0x1e,
		.name = "ppcsahbslvr",
		.swgroup = TEGRA_SWGROUP_PPCS,
		.smmu = अणु
			.reg = 0x228,
			.bit = 30,
		पूर्ण,
		.la = अणु
			.reg = 0x344,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x12,
		पूर्ण,
		.fअगरo_size = 16 * 8,
	पूर्ण, अणु
		.id = 0x1f,
		.name = "satar",
		.swgroup = TEGRA_SWGROUP_SATA,
		.smmu = अणु
			.reg = 0x228,
			.bit = 31,
		पूर्ण,
		.la = अणु
			.reg = 0x350,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x33,
		पूर्ण,
		.fअगरo_size = 16 * 32,
	पूर्ण, अणु
		.id = 0x20,
		.name = "texsrd",
		.swgroup = TEGRA_SWGROUP_NV,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 0,
		पूर्ण,
		.la = अणु
			.reg = 0x338,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x13,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x21,
		.name = "texsrd2",
		.swgroup = TEGRA_SWGROUP_NV2,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 1,
		पूर्ण,
		.la = अणु
			.reg = 0x340,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x13,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x22,
		.name = "vdebsevr",
		.swgroup = TEGRA_SWGROUP_VDE,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 2,
		पूर्ण,
		.la = अणु
			.reg = 0x354,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
		.fअगरo_size = 16 * 8,
	पूर्ण, अणु
		.id = 0x23,
		.name = "vdember",
		.swgroup = TEGRA_SWGROUP_VDE,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 3,
		पूर्ण,
		.la = अणु
			.reg = 0x354,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0xd0,
		पूर्ण,
		.fअगरo_size = 16 * 4,
	पूर्ण, अणु
		.id = 0x24,
		.name = "vdemcer",
		.swgroup = TEGRA_SWGROUP_VDE,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 4,
		पूर्ण,
		.la = अणु
			.reg = 0x358,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x2a,
		पूर्ण,
		.fअगरo_size = 16 * 16,
	पूर्ण, अणु
		.id = 0x25,
		.name = "vdetper",
		.swgroup = TEGRA_SWGROUP_VDE,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 5,
		पूर्ण,
		.la = अणु
			.reg = 0x358,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x74,
		पूर्ण,
		.fअगरo_size = 16 * 16,
	पूर्ण, अणु
		.id = 0x26,
		.name = "mpcorelpr",
		.swgroup = TEGRA_SWGROUP_MPCORELP,
		.la = अणु
			.reg = 0x324,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x04,
		पूर्ण,
		.fअगरo_size = 16 * 14,
	पूर्ण, अणु
		.id = 0x27,
		.name = "mpcorer",
		.swgroup = TEGRA_SWGROUP_MPCORE,
		.la = अणु
			.reg = 0x320,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x04,
		पूर्ण,
		.fअगरo_size = 16 * 14,
	पूर्ण, अणु
		.id = 0x28,
		.name = "eppu",
		.swgroup = TEGRA_SWGROUP_EPP,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 8,
		पूर्ण,
		.la = अणु
			.reg = 0x300,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x6c,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x29,
		.name = "eppv",
		.swgroup = TEGRA_SWGROUP_EPP,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 9,
		पूर्ण,
		.la = अणु
			.reg = 0x304,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x6c,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x2a,
		.name = "eppy",
		.swgroup = TEGRA_SWGROUP_EPP,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 10,
		पूर्ण,
		.la = अणु
			.reg = 0x304,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x6c,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x2b,
		.name = "mpeunifbw",
		.swgroup = TEGRA_SWGROUP_MPE,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 11,
		पूर्ण,
		.la = अणु
			.reg = 0x330,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x13,
		पूर्ण,
		.fअगरo_size = 16 * 8,
	पूर्ण, अणु
		.id = 0x2c,
		.name = "viwsb",
		.swgroup = TEGRA_SWGROUP_VI,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 12,
		पूर्ण,
		.la = अणु
			.reg = 0x364,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x12,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x2d,
		.name = "viwu",
		.swgroup = TEGRA_SWGROUP_VI,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 13,
		पूर्ण,
		.la = अणु
			.reg = 0x368,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0xb2,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x2e,
		.name = "viwv",
		.swgroup = TEGRA_SWGROUP_VI,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 14,
		पूर्ण,
		.la = अणु
			.reg = 0x368,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0xb2,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x2f,
		.name = "viwy",
		.swgroup = TEGRA_SWGROUP_VI,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 15,
		पूर्ण,
		.la = अणु
			.reg = 0x36c,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x12,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x30,
		.name = "g2dw",
		.swgroup = TEGRA_SWGROUP_G2,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 16,
		पूर्ण,
		.la = अणु
			.reg = 0x30c,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x9,
		पूर्ण,
		.fअगरo_size = 16 * 128,
	पूर्ण, अणु
		.id = 0x31,
		.name = "afiw",
		.swgroup = TEGRA_SWGROUP_AFI,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 17,
		पूर्ण,
		.la = अणु
			.reg = 0x2e0,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x0c,
		पूर्ण,
		.fअगरo_size = 16 * 32,
	पूर्ण, अणु
		.id = 0x32,
		.name = "avpcarm7w",
		.swgroup = TEGRA_SWGROUP_AVPC,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 18,
		पूर्ण,
		.la = अणु
			.reg = 0x2e4,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x0e,
		पूर्ण,
		.fअगरo_size = 16 * 2,
	पूर्ण, अणु
		.id = 0x33,
		.name = "fdcdwr",
		.swgroup = TEGRA_SWGROUP_NV,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 19,
		पूर्ण,
		.la = अणु
			.reg = 0x338,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x0a,
		पूर्ण,
		.fअगरo_size = 16 * 48,
	पूर्ण, अणु
		.id = 0x34,
		.name = "fdcdwr2",
		.swgroup = TEGRA_SWGROUP_NV2,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 20,
		पूर्ण,
		.la = अणु
			.reg = 0x340,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x0a,
		पूर्ण,
		.fअगरo_size = 16 * 48,
	पूर्ण, अणु
		.id = 0x35,
		.name = "hdaw",
		.swgroup = TEGRA_SWGROUP_HDA,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 21,
		पूर्ण,
		.la = अणु
			.reg = 0x318,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
		.fअगरo_size = 16 * 16,
	पूर्ण, अणु
		.id = 0x36,
		.name = "host1xw",
		.swgroup = TEGRA_SWGROUP_HC,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 22,
		पूर्ण,
		.la = अणु
			.reg = 0x314,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x10,
		पूर्ण,
		.fअगरo_size = 16 * 32,
	पूर्ण, अणु
		.id = 0x37,
		.name = "ispw",
		.swgroup = TEGRA_SWGROUP_ISP,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 23,
		पूर्ण,
		.la = अणु
			.reg = 0x31c,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
		.fअगरo_size = 16 * 64,
	पूर्ण, अणु
		.id = 0x38,
		.name = "mpcorelpw",
		.swgroup = TEGRA_SWGROUP_MPCORELP,
		.la = अणु
			.reg = 0x324,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x0e,
		पूर्ण,
		.fअगरo_size = 16 * 24,
	पूर्ण, अणु
		.id = 0x39,
		.name = "mpcorew",
		.swgroup = TEGRA_SWGROUP_MPCORE,
		.la = अणु
			.reg = 0x320,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x0e,
		पूर्ण,
		.fअगरo_size = 16 * 24,
	पूर्ण, अणु
		.id = 0x3a,
		.name = "mpecswr",
		.swgroup = TEGRA_SWGROUP_MPE,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 26,
		पूर्ण,
		.la = अणु
			.reg = 0x330,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
		.fअगरo_size = 16 * 8,
	पूर्ण, अणु
		.id = 0x3b,
		.name = "ppcsahbdmaw",
		.swgroup = TEGRA_SWGROUP_PPCS,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 27,
		पूर्ण,
		.la = अणु
			.reg = 0x348,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x10,
		पूर्ण,
		.fअगरo_size = 16 * 2,
	पूर्ण, अणु
		.id = 0x3c,
		.name = "ppcsahbslvw",
		.swgroup = TEGRA_SWGROUP_PPCS,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 28,
		पूर्ण,
		.la = अणु
			.reg = 0x348,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x06,
		पूर्ण,
		.fअगरo_size = 16 * 4,
	पूर्ण, अणु
		.id = 0x3d,
		.name = "sataw",
		.swgroup = TEGRA_SWGROUP_SATA,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 29,
		पूर्ण,
		.la = अणु
			.reg = 0x350,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x33,
		पूर्ण,
		.fअगरo_size = 16 * 32,
	पूर्ण, अणु
		.id = 0x3e,
		.name = "vdebsevw",
		.swgroup = TEGRA_SWGROUP_VDE,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 30,
		पूर्ण,
		.la = अणु
			.reg = 0x35c,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
		.fअगरo_size = 16 * 4,
	पूर्ण, अणु
		.id = 0x3f,
		.name = "vdedbgw",
		.swgroup = TEGRA_SWGROUP_VDE,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 31,
		पूर्ण,
		.la = अणु
			.reg = 0x35c,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
		.fअगरo_size = 16 * 16,
	पूर्ण, अणु
		.id = 0x40,
		.name = "vdembew",
		.swgroup = TEGRA_SWGROUP_VDE,
		.smmu = अणु
			.reg = 0x230,
			.bit = 0,
		पूर्ण,
		.la = अणु
			.reg = 0x360,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x42,
		पूर्ण,
		.fअगरo_size = 16 * 2,
	पूर्ण, अणु
		.id = 0x41,
		.name = "vdetpmw",
		.swgroup = TEGRA_SWGROUP_VDE,
		.smmu = अणु
			.reg = 0x230,
			.bit = 1,
		पूर्ण,
		.la = अणु
			.reg = 0x360,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x2a,
		पूर्ण,
		.fअगरo_size = 16 * 16,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_smmu_swgroup tegra30_swgroups[] = अणु
	अणु .name = "dc",   .swgroup = TEGRA_SWGROUP_DC,   .reg = 0x240 पूर्ण,
	अणु .name = "dcb",  .swgroup = TEGRA_SWGROUP_DCB,  .reg = 0x244 पूर्ण,
	अणु .name = "epp",  .swgroup = TEGRA_SWGROUP_EPP,  .reg = 0x248 पूर्ण,
	अणु .name = "g2",   .swgroup = TEGRA_SWGROUP_G2,   .reg = 0x24c पूर्ण,
	अणु .name = "mpe",  .swgroup = TEGRA_SWGROUP_MPE,  .reg = 0x264 पूर्ण,
	अणु .name = "vi",   .swgroup = TEGRA_SWGROUP_VI,   .reg = 0x280 पूर्ण,
	अणु .name = "afi",  .swgroup = TEGRA_SWGROUP_AFI,  .reg = 0x238 पूर्ण,
	अणु .name = "avpc", .swgroup = TEGRA_SWGROUP_AVPC, .reg = 0x23c पूर्ण,
	अणु .name = "nv",   .swgroup = TEGRA_SWGROUP_NV,   .reg = 0x268 पूर्ण,
	अणु .name = "nv2",  .swgroup = TEGRA_SWGROUP_NV2,  .reg = 0x26c पूर्ण,
	अणु .name = "hda",  .swgroup = TEGRA_SWGROUP_HDA,  .reg = 0x254 पूर्ण,
	अणु .name = "hc",   .swgroup = TEGRA_SWGROUP_HC,   .reg = 0x250 पूर्ण,
	अणु .name = "ppcs", .swgroup = TEGRA_SWGROUP_PPCS, .reg = 0x270 पूर्ण,
	अणु .name = "sata", .swgroup = TEGRA_SWGROUP_SATA, .reg = 0x278 पूर्ण,
	अणु .name = "vde",  .swgroup = TEGRA_SWGROUP_VDE,  .reg = 0x27c पूर्ण,
	अणु .name = "isp",  .swgroup = TEGRA_SWGROUP_ISP,  .reg = 0x258 पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tegra30_group_drm[] = अणु
	TEGRA_SWGROUP_DC,
	TEGRA_SWGROUP_DCB,
	TEGRA_SWGROUP_G2,
	TEGRA_SWGROUP_NV,
	TEGRA_SWGROUP_NV2,
पूर्ण;

अटल स्थिर काष्ठा tegra_smmu_group_soc tegra30_groups[] = अणु
	अणु
		.name = "drm",
		.swgroups = tegra30_group_drm,
		.num_swgroups = ARRAY_SIZE(tegra30_group_drm),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_smmu_soc tegra30_smmu_soc = अणु
	.clients = tegra30_mc_clients,
	.num_clients = ARRAY_SIZE(tegra30_mc_clients),
	.swgroups = tegra30_swgroups,
	.num_swgroups = ARRAY_SIZE(tegra30_swgroups),
	.groups = tegra30_groups,
	.num_groups = ARRAY_SIZE(tegra30_groups),
	.supports_round_robin_arbitration = false,
	.supports_request_limit = false,
	.num_tlb_lines = 16,
	.num_asids = 4,
पूर्ण;

#घोषणा TEGRA30_MC_RESET(_name, _control, _status, _bit)	\
	अणु							\
		.name = #_name,					\
		.id = TEGRA30_MC_RESET_##_name,			\
		.control = _control,				\
		.status = _status,				\
		.bit = _bit,					\
	पूर्ण

अटल स्थिर काष्ठा tegra_mc_reset tegra30_mc_resets[] = अणु
	TEGRA30_MC_RESET(AFI,      0x200, 0x204,  0),
	TEGRA30_MC_RESET(AVPC,     0x200, 0x204,  1),
	TEGRA30_MC_RESET(DC,       0x200, 0x204,  2),
	TEGRA30_MC_RESET(DCB,      0x200, 0x204,  3),
	TEGRA30_MC_RESET(EPP,      0x200, 0x204,  4),
	TEGRA30_MC_RESET(2D,       0x200, 0x204,  5),
	TEGRA30_MC_RESET(HC,       0x200, 0x204,  6),
	TEGRA30_MC_RESET(HDA,      0x200, 0x204,  7),
	TEGRA30_MC_RESET(ISP,      0x200, 0x204,  8),
	TEGRA30_MC_RESET(MPCORE,   0x200, 0x204,  9),
	TEGRA30_MC_RESET(MPCORELP, 0x200, 0x204, 10),
	TEGRA30_MC_RESET(MPE,      0x200, 0x204, 11),
	TEGRA30_MC_RESET(3D,       0x200, 0x204, 12),
	TEGRA30_MC_RESET(3D2,      0x200, 0x204, 13),
	TEGRA30_MC_RESET(PPCS,     0x200, 0x204, 14),
	TEGRA30_MC_RESET(SATA,     0x200, 0x204, 15),
	TEGRA30_MC_RESET(VDE,      0x200, 0x204, 16),
	TEGRA30_MC_RESET(VI,       0x200, 0x204, 17),
पूर्ण;

अटल व्योम tegra30_mc_tune_client_latency(काष्ठा tegra_mc *mc,
					   स्थिर काष्ठा tegra_mc_client *client,
					   अचिन्हित पूर्णांक bandwidth_mbytes_sec)
अणु
	u32 arb_tolerance_compensation_nsec, arb_tolerance_compensation_भाग;
	स्थिर काष्ठा tegra_mc_la *la = &client->la;
	अचिन्हित पूर्णांक fअगरo_size = client->fअगरo_size;
	u32 arb_nsec, la_ticks, value;

	/* see 18.4.1 Client Configuration in Tegra3 TRM v03p */
	अगर (bandwidth_mbytes_sec)
		arb_nsec = fअगरo_size * NSEC_PER_USEC / bandwidth_mbytes_sec;
	अन्यथा
		arb_nsec = U32_MAX;

	/*
	 * Latency allowness should be set with consideration क्रम the module's
	 * latency tolerance and पूर्णांकernal buffering capabilities.
	 *
	 * Display memory clients use isochronous transfers and have very low
	 * tolerance to a belated transfers. Hence we need to compensate the
	 * memory arbitration imperfection क्रम them in order to prevent FIFO
	 * underflow condition when memory bus is busy.
	 *
	 * VI clients also need a stronger compensation.
	 */
	चयन (client->swgroup) अणु
	हाल TEGRA_SWGROUP_MPCORE:
	हाल TEGRA_SWGROUP_PTC:
		/*
		 * We always want lower latency क्रम these clients, hence
		 * करोn't touch them.
		 */
		वापस;

	हाल TEGRA_SWGROUP_DC:
	हाल TEGRA_SWGROUP_DCB:
		arb_tolerance_compensation_nsec = 1050;
		arb_tolerance_compensation_भाग = 2;
		अवरोध;

	हाल TEGRA_SWGROUP_VI:
		arb_tolerance_compensation_nsec = 1050;
		arb_tolerance_compensation_भाग = 1;
		अवरोध;

	शेष:
		arb_tolerance_compensation_nsec = 150;
		arb_tolerance_compensation_भाग = 1;
		अवरोध;
	पूर्ण

	अगर (arb_nsec > arb_tolerance_compensation_nsec)
		arb_nsec -= arb_tolerance_compensation_nsec;
	अन्यथा
		arb_nsec = 0;

	arb_nsec /= arb_tolerance_compensation_भाग;

	/*
	 * Latency allowance is a number of ticks a request from a particular
	 * client may रुको in the EMEM arbiter beक्रमe it becomes a high-priority
	 * request.
	 */
	la_ticks = arb_nsec / mc->tick;
	la_ticks = min(la_ticks, la->mask);

	value = mc_पढ़ोl(mc, la->reg);
	value &= ~(la->mask << la->shअगरt);
	value |= la_ticks << la->shअगरt;
	mc_ग_लिखोl(mc, value, la->reg);
पूर्ण

अटल पूर्णांक tegra30_mc_icc_set(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	काष्ठा tegra_mc *mc = icc_provider_to_tegra_mc(src->provider);
	स्थिर काष्ठा tegra_mc_client *client = &mc->soc->clients[src->id];
	u64 peak_bandwidth = icc_units_to_bps(src->peak_bw);

	/*
	 * Skip pre-initialization that is करोne by icc_node_add(), which sets
	 * bandwidth to maximum क्रम all clients beक्रमe drivers are loaded.
	 *
	 * This करोesn't make sense for us because we don't have drivers क्रम all
	 * clients and it's okay to keep configuration left from bootloader
	 * during boot, at least क्रम today.
	 */
	अगर (src == dst)
		वापस 0;

	/* convert bytes/sec to megabytes/sec */
	करो_भाग(peak_bandwidth, 1000000);

	tegra30_mc_tune_client_latency(mc, client, peak_bandwidth);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra30_mc_icc_aggreate(काष्ठा icc_node *node, u32 tag, u32 avg_bw,
				   u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
अणु
	/*
	 * ISO clients need to reserve extra bandwidth up-front because
	 * there could be high bandwidth pressure during initial filling
	 * of the client's FIFO buffers.  Secondly, we need to take पूर्णांकo
	 * account impurities of the memory subप्रणाली.
	 */
	अगर (tag & TEGRA_MC_ICC_TAG_ISO)
		peak_bw = tegra_mc_scale_percents(peak_bw, 400);

	*agg_avg += avg_bw;
	*agg_peak = max(*agg_peak, peak_bw);

	वापस 0;
पूर्ण

अटल काष्ठा icc_node_data *
tegra30_mc_of_icc_xlate_extended(काष्ठा of_phandle_args *spec, व्योम *data)
अणु
	काष्ठा tegra_mc *mc = icc_provider_to_tegra_mc(data);
	स्थिर काष्ठा tegra_mc_client *client;
	अचिन्हित पूर्णांक i, idx = spec->args[0];
	काष्ठा icc_node_data *ndata;
	काष्ठा icc_node *node;

	list_क्रम_each_entry(node, &mc->provider.nodes, node_list) अणु
		अगर (node->id != idx)
			जारी;

		ndata = kzalloc(माप(*ndata), GFP_KERNEL);
		अगर (!ndata)
			वापस ERR_PTR(-ENOMEM);

		client = &mc->soc->clients[idx];
		ndata->node = node;

		चयन (client->swgroup) अणु
		हाल TEGRA_SWGROUP_DC:
		हाल TEGRA_SWGROUP_DCB:
		हाल TEGRA_SWGROUP_PTC:
		हाल TEGRA_SWGROUP_VI:
			/* these clients are isochronous by शेष */
			ndata->tag = TEGRA_MC_ICC_TAG_ISO;
			अवरोध;

		शेष:
			ndata->tag = TEGRA_MC_ICC_TAG_DEFAULT;
			अवरोध;
		पूर्ण

		वापस ndata;
	पूर्ण

	क्रम (i = 0; i < mc->soc->num_clients; i++) अणु
		अगर (mc->soc->clients[i].id == idx)
			वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	dev_err(mc->dev, "invalid ICC client ID %u\n", idx);

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल स्थिर काष्ठा tegra_mc_icc_ops tegra30_mc_icc_ops = अणु
	.xlate_extended = tegra30_mc_of_icc_xlate_extended,
	.aggregate = tegra30_mc_icc_aggreate,
	.set = tegra30_mc_icc_set,
पूर्ण;

स्थिर काष्ठा tegra_mc_soc tegra30_mc_soc = अणु
	.clients = tegra30_mc_clients,
	.num_clients = ARRAY_SIZE(tegra30_mc_clients),
	.num_address_bits = 32,
	.atom_size = 16,
	.client_id_mask = 0x7f,
	.smmu = &tegra30_smmu_soc,
	.emem_regs = tegra30_mc_emem_regs,
	.num_emem_regs = ARRAY_SIZE(tegra30_mc_emem_regs),
	.पूर्णांकmask = MC_INT_INVALID_SMMU_PAGE | MC_INT_SECURITY_VIOLATION |
		   MC_INT_DECERR_EMEM,
	.reset_ops = &tegra_mc_reset_ops_common,
	.resets = tegra30_mc_resets,
	.num_resets = ARRAY_SIZE(tegra30_mc_resets),
	.icc_ops = &tegra30_mc_icc_ops,
पूर्ण;
