<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <dt-bindings/memory/tegra210-mc.h>

#समावेश "mc.h"

अटल स्थिर काष्ठा tegra_mc_client tegra210_mc_clients[] = अणु
	अणु
		.id = 0x00,
		.name = "ptcr",
		.swgroup = TEGRA_SWGROUP_PTC,
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
			.def = 0x1e,
		पूर्ण,
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
			.def = 0x1e,
		पूर्ण,
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
			.def = 0x1e,
		पूर्ण,
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
			.def = 0x1e,
		पूर्ण,
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
			.def = 0x1e,
		पूर्ण,
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
			.def = 0x1e,
		पूर्ण,
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
			.def = 0x2e,
		पूर्ण,
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
			.def = 0x1e,
		पूर्ण,
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
			.def = 0x1e,
		पूर्ण,
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
			.def = 0x24,
		पूर्ण,
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
			.def = 0x1e,
		पूर्ण,
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
	पूर्ण, अणु
		.id = 0x1c,
		.name = "nvencsrd",
		.swgroup = TEGRA_SWGROUP_NVENC,
		.smmu = अणु
			.reg = 0x228,
			.bit = 28,
		पूर्ण,
		.la = अणु
			.reg = 0x328,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x23,
		पूर्ण,
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
			.def = 0x49,
		पूर्ण,
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
			.def = 0x1a,
		पूर्ण,
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
			.def = 0x65,
		पूर्ण,
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
	पूर्ण, अणु
		.id = 0x2b,
		.name = "nvencswr",
		.swgroup = TEGRA_SWGROUP_NVENC,
		.smmu = अणु
			.reg = 0x22c,
			.bit = 11,
		पूर्ण,
		.la = अणु
			.reg = 0x328,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
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
			.def = 0x80,
		पूर्ण,
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
			.def = 0x80,
		पूर्ण,
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
			.def = 0x80,
		पूर्ण,
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
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x39,
		.name = "mpcorew",
		.swgroup = TEGRA_SWGROUP_MPCORE,
		.la = अणु
			.reg = 0x320,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
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
			.def = 0x80,
		पूर्ण,
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
			.def = 0x80,
		पूर्ण,
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
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x44,
		.name = "ispra",
		.swgroup = TEGRA_SWGROUP_ISP2,
		.smmu = अणु
			.reg = 0x230,
			.bit = 4,
		पूर्ण,
		.la = अणु
			.reg = 0x370,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x18,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x46,
		.name = "ispwa",
		.swgroup = TEGRA_SWGROUP_ISP2,
		.smmu = अणु
			.reg = 0x230,
			.bit = 6,
		पूर्ण,
		.la = अणु
			.reg = 0x374,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x47,
		.name = "ispwb",
		.swgroup = TEGRA_SWGROUP_ISP2,
		.smmu = अणु
			.reg = 0x230,
			.bit = 7,
		पूर्ण,
		.la = अणु
			.reg = 0x374,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x4a,
		.name = "xusb_hostr",
		.swgroup = TEGRA_SWGROUP_XUSB_HOST,
		.smmu = अणु
			.reg = 0x230,
			.bit = 10,
		पूर्ण,
		.la = अणु
			.reg = 0x37c,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x7a,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x4b,
		.name = "xusb_hostw",
		.swgroup = TEGRA_SWGROUP_XUSB_HOST,
		.smmu = अणु
			.reg = 0x230,
			.bit = 11,
		पूर्ण,
		.la = अणु
			.reg = 0x37c,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x4c,
		.name = "xusb_devr",
		.swgroup = TEGRA_SWGROUP_XUSB_DEV,
		.smmu = अणु
			.reg = 0x230,
			.bit = 12,
		पूर्ण,
		.la = अणु
			.reg = 0x380,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x39,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x4d,
		.name = "xusb_devw",
		.swgroup = TEGRA_SWGROUP_XUSB_DEV,
		.smmu = अणु
			.reg = 0x230,
			.bit = 13,
		पूर्ण,
		.la = अणु
			.reg = 0x380,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x4e,
		.name = "isprab",
		.swgroup = TEGRA_SWGROUP_ISP2B,
		.smmu = अणु
			.reg = 0x230,
			.bit = 14,
		पूर्ण,
		.la = अणु
			.reg = 0x384,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x18,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x50,
		.name = "ispwab",
		.swgroup = TEGRA_SWGROUP_ISP2B,
		.smmu = अणु
			.reg = 0x230,
			.bit = 16,
		पूर्ण,
		.la = अणु
			.reg = 0x388,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x51,
		.name = "ispwbb",
		.swgroup = TEGRA_SWGROUP_ISP2B,
		.smmu = अणु
			.reg = 0x230,
			.bit = 17,
		पूर्ण,
		.la = अणु
			.reg = 0x388,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x54,
		.name = "tsecsrd",
		.swgroup = TEGRA_SWGROUP_TSEC,
		.smmu = अणु
			.reg = 0x230,
			.bit = 20,
		पूर्ण,
		.la = अणु
			.reg = 0x390,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x9b,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x55,
		.name = "tsecswr",
		.swgroup = TEGRA_SWGROUP_TSEC,
		.smmu = अणु
			.reg = 0x230,
			.bit = 21,
		पूर्ण,
		.la = अणु
			.reg = 0x390,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x56,
		.name = "a9avpscr",
		.swgroup = TEGRA_SWGROUP_A9AVP,
		.smmu = अणु
			.reg = 0x230,
			.bit = 22,
		पूर्ण,
		.la = अणु
			.reg = 0x3a4,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x04,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x57,
		.name = "a9avpscw",
		.swgroup = TEGRA_SWGROUP_A9AVP,
		.smmu = अणु
			.reg = 0x230,
			.bit = 23,
		पूर्ण,
		.la = अणु
			.reg = 0x3a4,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x58,
		.name = "gpusrd",
		.swgroup = TEGRA_SWGROUP_GPU,
		.smmu = अणु
			/* पढ़ो-only */
			.reg = 0x230,
			.bit = 24,
		पूर्ण,
		.la = अणु
			.reg = 0x3c8,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x1a,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x59,
		.name = "gpuswr",
		.swgroup = TEGRA_SWGROUP_GPU,
		.smmu = अणु
			/* पढ़ो-only */
			.reg = 0x230,
			.bit = 25,
		पूर्ण,
		.la = अणु
			.reg = 0x3c8,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x5a,
		.name = "displayt",
		.swgroup = TEGRA_SWGROUP_DC,
		.smmu = अणु
			.reg = 0x230,
			.bit = 26,
		पूर्ण,
		.la = अणु
			.reg = 0x2f0,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x1e,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x60,
		.name = "sdmmcra",
		.swgroup = TEGRA_SWGROUP_SDMMC1A,
		.smmu = अणु
			.reg = 0x234,
			.bit = 0,
		पूर्ण,
		.la = अणु
			.reg = 0x3b8,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x49,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x61,
		.name = "sdmmcraa",
		.swgroup = TEGRA_SWGROUP_SDMMC2A,
		.smmu = अणु
			.reg = 0x234,
			.bit = 1,
		पूर्ण,
		.la = अणु
			.reg = 0x3bc,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x5a,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x62,
		.name = "sdmmcr",
		.swgroup = TEGRA_SWGROUP_SDMMC3A,
		.smmu = अणु
			.reg = 0x234,
			.bit = 2,
		पूर्ण,
		.la = अणु
			.reg = 0x3c0,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x49,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x63,
		.swgroup = TEGRA_SWGROUP_SDMMC4A,
		.name = "sdmmcrab",
		.smmu = अणु
			.reg = 0x234,
			.bit = 3,
		पूर्ण,
		.la = अणु
			.reg = 0x3c4,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x5a,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x64,
		.name = "sdmmcwa",
		.swgroup = TEGRA_SWGROUP_SDMMC1A,
		.smmu = अणु
			.reg = 0x234,
			.bit = 4,
		पूर्ण,
		.la = अणु
			.reg = 0x3b8,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x65,
		.name = "sdmmcwaa",
		.swgroup = TEGRA_SWGROUP_SDMMC2A,
		.smmu = अणु
			.reg = 0x234,
			.bit = 5,
		पूर्ण,
		.la = अणु
			.reg = 0x3bc,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x66,
		.name = "sdmmcw",
		.swgroup = TEGRA_SWGROUP_SDMMC3A,
		.smmu = अणु
			.reg = 0x234,
			.bit = 6,
		पूर्ण,
		.la = अणु
			.reg = 0x3c0,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x67,
		.name = "sdmmcwab",
		.swgroup = TEGRA_SWGROUP_SDMMC4A,
		.smmu = अणु
			.reg = 0x234,
			.bit = 7,
		पूर्ण,
		.la = अणु
			.reg = 0x3c4,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x6c,
		.name = "vicsrd",
		.swgroup = TEGRA_SWGROUP_VIC,
		.smmu = अणु
			.reg = 0x234,
			.bit = 12,
		पूर्ण,
		.la = अणु
			.reg = 0x394,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x1a,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x6d,
		.name = "vicswr",
		.swgroup = TEGRA_SWGROUP_VIC,
		.smmu = अणु
			.reg = 0x234,
			.bit = 13,
		पूर्ण,
		.la = अणु
			.reg = 0x394,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x72,
		.name = "viw",
		.swgroup = TEGRA_SWGROUP_VI,
		.smmu = अणु
			.reg = 0x234,
			.bit = 18,
		पूर्ण,
		.la = अणु
			.reg = 0x398,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x73,
		.name = "displayd",
		.swgroup = TEGRA_SWGROUP_DC,
		.smmu = अणु
			.reg = 0x234,
			.bit = 19,
		पूर्ण,
		.la = अणु
			.reg = 0x3c8,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x50,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x78,
		.name = "nvdecsrd",
		.swgroup = TEGRA_SWGROUP_NVDEC,
		.smmu = अणु
			.reg = 0x234,
			.bit = 24,
		पूर्ण,
		.la = अणु
			.reg = 0x3d8,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x23,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x79,
		.name = "nvdecswr",
		.swgroup = TEGRA_SWGROUP_NVDEC,
		.smmu = अणु
			.reg = 0x234,
			.bit = 25,
		पूर्ण,
		.la = अणु
			.reg = 0x3d8,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x7a,
		.name = "aper",
		.swgroup = TEGRA_SWGROUP_APE,
		.smmu = अणु
			.reg = 0x234,
			.bit = 26,
		पूर्ण,
		.la = अणु
			.reg = 0x3dc,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x7b,
		.name = "apew",
		.swgroup = TEGRA_SWGROUP_APE,
		.smmu = अणु
			.reg = 0x234,
			.bit = 27,
		पूर्ण,
		.la = अणु
			.reg = 0x3dc,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x7e,
		.name = "nvjpgsrd",
		.swgroup = TEGRA_SWGROUP_NVJPG,
		.smmu = अणु
			.reg = 0x234,
			.bit = 30,
		पूर्ण,
		.la = अणु
			.reg = 0x3e4,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x23,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x7f,
		.name = "nvjpgswr",
		.swgroup = TEGRA_SWGROUP_NVJPG,
		.smmu = अणु
			.reg = 0x234,
			.bit = 31,
		पूर्ण,
		.la = अणु
			.reg = 0x3e4,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x80,
		.name = "sesrd",
		.swgroup = TEGRA_SWGROUP_SE,
		.smmu = अणु
			.reg = 0xb98,
			.bit = 0,
		पूर्ण,
		.la = अणु
			.reg = 0x3e0,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x2e,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x81,
		.name = "seswr",
		.swgroup = TEGRA_SWGROUP_SE,
		.smmu = अणु
			.reg = 0xb98,
			.bit = 1,
		पूर्ण,
		.la = अणु
			.reg = 0x3e0,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x82,
		.name = "axiapr",
		.swgroup = TEGRA_SWGROUP_AXIAP,
		.smmu = अणु
			.reg = 0xb98,
			.bit = 2,
		पूर्ण,
		.la = अणु
			.reg = 0x3a0,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x83,
		.name = "axiapw",
		.swgroup = TEGRA_SWGROUP_AXIAP,
		.smmu = अणु
			.reg = 0xb98,
			.bit = 3,
		पूर्ण,
		.la = अणु
			.reg = 0x3a0,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x84,
		.name = "etrr",
		.swgroup = TEGRA_SWGROUP_ETR,
		.smmu = अणु
			.reg = 0xb98,
			.bit = 4,
		पूर्ण,
		.la = अणु
			.reg = 0x3ec,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0xff,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x85,
		.name = "etrw",
		.swgroup = TEGRA_SWGROUP_ETR,
		.smmu = अणु
			.reg = 0xb98,
			.bit = 5,
		पूर्ण,
		.la = अणु
			.reg = 0x3ec,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x86,
		.name = "tsecsrdb",
		.swgroup = TEGRA_SWGROUP_TSECB,
		.smmu = अणु
			.reg = 0xb98,
			.bit = 6,
		पूर्ण,
		.la = अणु
			.reg = 0x3f0,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x9b,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x87,
		.name = "tsecswrb",
		.swgroup = TEGRA_SWGROUP_TSECB,
		.smmu = अणु
			.reg = 0xb98,
			.bit = 7,
		पूर्ण,
		.la = अणु
			.reg = 0x3f0,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x88,
		.name = "gpusrd2",
		.swgroup = TEGRA_SWGROUP_GPU,
		.smmu = अणु
			/* पढ़ो-only */
			.reg = 0xb98,
			.bit = 8,
		पूर्ण,
		.la = अणु
			.reg = 0x3e8,
			.shअगरt = 0,
			.mask = 0xff,
			.def = 0x1a,
		पूर्ण,
	पूर्ण, अणु
		.id = 0x89,
		.name = "gpuswr2",
		.swgroup = TEGRA_SWGROUP_GPU,
		.smmu = अणु
			/* पढ़ो-only */
			.reg = 0xb98,
			.bit = 9,
		पूर्ण,
		.la = अणु
			.reg = 0x3e8,
			.shअगरt = 16,
			.mask = 0xff,
			.def = 0x80,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_smmu_swgroup tegra210_swgroups[] = अणु
	अणु .name = "afi",       .swgroup = TEGRA_SWGROUP_AFI,       .reg = 0x238 पूर्ण,
	अणु .name = "avpc",      .swgroup = TEGRA_SWGROUP_AVPC,      .reg = 0x23c पूर्ण,
	अणु .name = "dc",        .swgroup = TEGRA_SWGROUP_DC,        .reg = 0x240 पूर्ण,
	अणु .name = "dcb",       .swgroup = TEGRA_SWGROUP_DCB,       .reg = 0x244 पूर्ण,
	अणु .name = "hc",        .swgroup = TEGRA_SWGROUP_HC,        .reg = 0x250 पूर्ण,
	अणु .name = "hda",       .swgroup = TEGRA_SWGROUP_HDA,       .reg = 0x254 पूर्ण,
	अणु .name = "isp2",      .swgroup = TEGRA_SWGROUP_ISP2,      .reg = 0x258 पूर्ण,
	अणु .name = "nvenc",     .swgroup = TEGRA_SWGROUP_NVENC,     .reg = 0x264 पूर्ण,
	अणु .name = "nv",        .swgroup = TEGRA_SWGROUP_NV,        .reg = 0x268 पूर्ण,
	अणु .name = "nv2",       .swgroup = TEGRA_SWGROUP_NV2,       .reg = 0x26c पूर्ण,
	अणु .name = "ppcs",      .swgroup = TEGRA_SWGROUP_PPCS,      .reg = 0x270 पूर्ण,
	अणु .name = "sata",      .swgroup = TEGRA_SWGROUP_SATA,      .reg = 0x274 पूर्ण,
	अणु .name = "vi",        .swgroup = TEGRA_SWGROUP_VI,        .reg = 0x280 पूर्ण,
	अणु .name = "vic",       .swgroup = TEGRA_SWGROUP_VIC,       .reg = 0x284 पूर्ण,
	अणु .name = "xusb_host", .swgroup = TEGRA_SWGROUP_XUSB_HOST, .reg = 0x288 पूर्ण,
	अणु .name = "xusb_dev",  .swgroup = TEGRA_SWGROUP_XUSB_DEV,  .reg = 0x28c पूर्ण,
	अणु .name = "a9avp",     .swgroup = TEGRA_SWGROUP_A9AVP,     .reg = 0x290 पूर्ण,
	अणु .name = "tsec",      .swgroup = TEGRA_SWGROUP_TSEC,      .reg = 0x294 पूर्ण,
	अणु .name = "ppcs1",     .swgroup = TEGRA_SWGROUP_PPCS1,     .reg = 0x298 पूर्ण,
	अणु .name = "dc1",       .swgroup = TEGRA_SWGROUP_DC1,       .reg = 0xa88 पूर्ण,
	अणु .name = "sdmmc1a",   .swgroup = TEGRA_SWGROUP_SDMMC1A,   .reg = 0xa94 पूर्ण,
	अणु .name = "sdmmc2a",   .swgroup = TEGRA_SWGROUP_SDMMC2A,   .reg = 0xa98 पूर्ण,
	अणु .name = "sdmmc3a",   .swgroup = TEGRA_SWGROUP_SDMMC3A,   .reg = 0xa9c पूर्ण,
	अणु .name = "sdmmc4a",   .swgroup = TEGRA_SWGROUP_SDMMC4A,   .reg = 0xaa0 पूर्ण,
	अणु .name = "isp2b",     .swgroup = TEGRA_SWGROUP_ISP2B,     .reg = 0xaa4 पूर्ण,
	अणु .name = "gpu",       .swgroup = TEGRA_SWGROUP_GPU,       .reg = 0xaac पूर्ण,
	अणु .name = "ppcs2",     .swgroup = TEGRA_SWGROUP_PPCS2,     .reg = 0xab0 पूर्ण,
	अणु .name = "nvdec",     .swgroup = TEGRA_SWGROUP_NVDEC,     .reg = 0xab4 पूर्ण,
	अणु .name = "ape",       .swgroup = TEGRA_SWGROUP_APE,       .reg = 0xab8 पूर्ण,
	अणु .name = "se",        .swgroup = TEGRA_SWGROUP_SE,        .reg = 0xabc पूर्ण,
	अणु .name = "nvjpg",     .swgroup = TEGRA_SWGROUP_NVJPG,     .reg = 0xac0 पूर्ण,
	अणु .name = "hc1",       .swgroup = TEGRA_SWGROUP_HC1,       .reg = 0xac4 पूर्ण,
	अणु .name = "se1",       .swgroup = TEGRA_SWGROUP_SE1,       .reg = 0xac8 पूर्ण,
	अणु .name = "axiap",     .swgroup = TEGRA_SWGROUP_AXIAP,     .reg = 0xacc पूर्ण,
	अणु .name = "etr",       .swgroup = TEGRA_SWGROUP_ETR,       .reg = 0xad0 पूर्ण,
	अणु .name = "tsecb",     .swgroup = TEGRA_SWGROUP_TSECB,     .reg = 0xad4 पूर्ण,
	अणु .name = "tsec1",     .swgroup = TEGRA_SWGROUP_TSEC1,     .reg = 0xad8 पूर्ण,
	अणु .name = "tsecb1",    .swgroup = TEGRA_SWGROUP_TSECB1,    .reg = 0xadc पूर्ण,
	अणु .name = "nvdec1",    .swgroup = TEGRA_SWGROUP_NVDEC1,    .reg = 0xae0 पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tegra210_group_display[] = अणु
	TEGRA_SWGROUP_DC,
	TEGRA_SWGROUP_DCB,
पूर्ण;

अटल स्थिर काष्ठा tegra_smmu_group_soc tegra210_groups[] = अणु
	अणु
		.name = "display",
		.swgroups = tegra210_group_display,
		.num_swgroups = ARRAY_SIZE(tegra210_group_display),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_smmu_soc tegra210_smmu_soc = अणु
	.clients = tegra210_mc_clients,
	.num_clients = ARRAY_SIZE(tegra210_mc_clients),
	.swgroups = tegra210_swgroups,
	.num_swgroups = ARRAY_SIZE(tegra210_swgroups),
	.groups = tegra210_groups,
	.num_groups = ARRAY_SIZE(tegra210_groups),
	.supports_round_robin_arbitration = true,
	.supports_request_limit = true,
	.num_tlb_lines = 48,
	.num_asids = 128,
पूर्ण;

#घोषणा TEGRA210_MC_RESET(_name, _control, _status, _bit)	\
	अणु							\
		.name = #_name,					\
		.id = TEGRA210_MC_RESET_##_name,		\
		.control = _control,				\
		.status = _status,				\
		.bit = _bit,					\
	पूर्ण

अटल स्थिर काष्ठा tegra_mc_reset tegra210_mc_resets[] = अणु
	TEGRA210_MC_RESET(AFI,       0x200, 0x204,  0),
	TEGRA210_MC_RESET(AVPC,      0x200, 0x204,  1),
	TEGRA210_MC_RESET(DC,        0x200, 0x204,  2),
	TEGRA210_MC_RESET(DCB,       0x200, 0x204,  3),
	TEGRA210_MC_RESET(HC,        0x200, 0x204,  6),
	TEGRA210_MC_RESET(HDA,       0x200, 0x204,  7),
	TEGRA210_MC_RESET(ISP2,      0x200, 0x204,  8),
	TEGRA210_MC_RESET(MPCORE,    0x200, 0x204,  9),
	TEGRA210_MC_RESET(NVENC,     0x200, 0x204, 11),
	TEGRA210_MC_RESET(PPCS,      0x200, 0x204, 14),
	TEGRA210_MC_RESET(SATA,      0x200, 0x204, 15),
	TEGRA210_MC_RESET(VI,        0x200, 0x204, 17),
	TEGRA210_MC_RESET(VIC,       0x200, 0x204, 18),
	TEGRA210_MC_RESET(XUSB_HOST, 0x200, 0x204, 19),
	TEGRA210_MC_RESET(XUSB_DEV,  0x200, 0x204, 20),
	TEGRA210_MC_RESET(A9AVP,     0x200, 0x204, 21),
	TEGRA210_MC_RESET(TSEC,      0x200, 0x204, 22),
	TEGRA210_MC_RESET(SDMMC1,    0x200, 0x204, 29),
	TEGRA210_MC_RESET(SDMMC2,    0x200, 0x204, 30),
	TEGRA210_MC_RESET(SDMMC3,    0x200, 0x204, 31),
	TEGRA210_MC_RESET(SDMMC4,    0x970, 0x974,  0),
	TEGRA210_MC_RESET(ISP2B,     0x970, 0x974,  1),
	TEGRA210_MC_RESET(GPU,       0x970, 0x974,  2),
	TEGRA210_MC_RESET(NVDEC,     0x970, 0x974,  5),
	TEGRA210_MC_RESET(APE,       0x970, 0x974,  6),
	TEGRA210_MC_RESET(SE,        0x970, 0x974,  7),
	TEGRA210_MC_RESET(NVJPG,     0x970, 0x974,  8),
	TEGRA210_MC_RESET(AXIAP,     0x970, 0x974, 11),
	TEGRA210_MC_RESET(ETR,       0x970, 0x974, 12),
	TEGRA210_MC_RESET(TSECB,     0x970, 0x974, 13),
पूर्ण;

स्थिर काष्ठा tegra_mc_soc tegra210_mc_soc = अणु
	.clients = tegra210_mc_clients,
	.num_clients = ARRAY_SIZE(tegra210_mc_clients),
	.num_address_bits = 34,
	.atom_size = 64,
	.client_id_mask = 0xff,
	.smmu = &tegra210_smmu_soc,
	.पूर्णांकmask = MC_INT_DECERR_MTS | MC_INT_SECERR_SEC | MC_INT_DECERR_VPR |
		   MC_INT_INVALID_APB_ASID_UPDATE | MC_INT_INVALID_SMMU_PAGE |
		   MC_INT_SECURITY_VIOLATION | MC_INT_DECERR_EMEM,
	.reset_ops = &tegra_mc_reset_ops_common,
	.resets = tegra210_mc_resets,
	.num_resets = ARRAY_SIZE(tegra210_mc_resets),
पूर्ण;
