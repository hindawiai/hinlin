<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#अगर defined(CONFIG_ARCH_TEGRA_186_SOC)
#समावेश <dt-bindings/memory/tegra186-mc.h>
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_TEGRA_194_SOC)
#समावेश <dt-bindings/memory/tegra194-mc.h>
#पूर्ण_अगर

काष्ठा tegra186_mc_client अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक sid;
	काष्ठा अणु
		अचिन्हित पूर्णांक override;
		अचिन्हित पूर्णांक security;
	पूर्ण regs;
पूर्ण;

काष्ठा tegra186_mc_soc अणु
	स्थिर काष्ठा tegra186_mc_client *clients;
	अचिन्हित पूर्णांक num_clients;
पूर्ण;

काष्ठा tegra186_mc अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;

	स्थिर काष्ठा tegra186_mc_soc *soc;
पूर्ण;

अटल व्योम tegra186_mc_program_sid(काष्ठा tegra186_mc *mc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < mc->soc->num_clients; i++) अणु
		स्थिर काष्ठा tegra186_mc_client *client = &mc->soc->clients[i];
		u32 override, security;

		override = पढ़ोl(mc->regs + client->regs.override);
		security = पढ़ोl(mc->regs + client->regs.security);

		dev_dbg(mc->dev, "client %s: override: %x security: %x\n",
			client->name, override, security);

		dev_dbg(mc->dev, "setting SID %u for %s\n", client->sid,
			client->name);
		ग_लिखोl(client->sid, mc->regs + client->regs.override);

		override = पढ़ोl(mc->regs + client->regs.override);
		security = पढ़ोl(mc->regs + client->regs.security);

		dev_dbg(mc->dev, "client %s: override: %x security: %x\n",
			client->name, override, security);
	पूर्ण
पूर्ण

#अगर defined(CONFIG_ARCH_TEGRA_186_SOC)
अटल स्थिर काष्ठा tegra186_mc_client tegra186_mc_clients[] = अणु
	अणु
		.name = "ptcr",
		.sid = TEGRA186_SID_PASSTHROUGH,
		.regs = अणु
			.override = 0x000,
			.security = 0x004,
		पूर्ण,
	पूर्ण, अणु
		.name = "afir",
		.sid = TEGRA186_SID_AFI,
		.regs = अणु
			.override = 0x070,
			.security = 0x074,
		पूर्ण,
	पूर्ण, अणु
		.name = "hdar",
		.sid = TEGRA186_SID_HDA,
		.regs = अणु
			.override = 0x0a8,
			.security = 0x0ac,
		पूर्ण,
	पूर्ण, अणु
		.name = "host1xdmar",
		.sid = TEGRA186_SID_HOST1X,
		.regs = अणु
			.override = 0x0b0,
			.security = 0x0b4,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvencsrd",
		.sid = TEGRA186_SID_NVENC,
		.regs = अणु
			.override = 0x0e0,
			.security = 0x0e4,
		पूर्ण,
	पूर्ण, अणु
		.name = "satar",
		.sid = TEGRA186_SID_SATA,
		.regs = अणु
			.override = 0x0f8,
			.security = 0x0fc,
		पूर्ण,
	पूर्ण, अणु
		.name = "mpcorer",
		.sid = TEGRA186_SID_PASSTHROUGH,
		.regs = अणु
			.override = 0x138,
			.security = 0x13c,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvencswr",
		.sid = TEGRA186_SID_NVENC,
		.regs = अणु
			.override = 0x158,
			.security = 0x15c,
		पूर्ण,
	पूर्ण, अणु
		.name = "afiw",
		.sid = TEGRA186_SID_AFI,
		.regs = अणु
			.override = 0x188,
			.security = 0x18c,
		पूर्ण,
	पूर्ण, अणु
		.name = "hdaw",
		.sid = TEGRA186_SID_HDA,
		.regs = अणु
			.override = 0x1a8,
			.security = 0x1ac,
		पूर्ण,
	पूर्ण, अणु
		.name = "mpcorew",
		.sid = TEGRA186_SID_PASSTHROUGH,
		.regs = अणु
			.override = 0x1c8,
			.security = 0x1cc,
		पूर्ण,
	पूर्ण, अणु
		.name = "sataw",
		.sid = TEGRA186_SID_SATA,
		.regs = अणु
			.override = 0x1e8,
			.security = 0x1ec,
		पूर्ण,
	पूर्ण, अणु
		.name = "ispra",
		.sid = TEGRA186_SID_ISP,
		.regs = अणु
			.override = 0x220,
			.security = 0x224,
		पूर्ण,
	पूर्ण, अणु
		.name = "ispwa",
		.sid = TEGRA186_SID_ISP,
		.regs = अणु
			.override = 0x230,
			.security = 0x234,
		पूर्ण,
	पूर्ण, अणु
		.name = "ispwb",
		.sid = TEGRA186_SID_ISP,
		.regs = अणु
			.override = 0x238,
			.security = 0x23c,
		पूर्ण,
	पूर्ण, अणु
		.name = "xusb_hostr",
		.sid = TEGRA186_SID_XUSB_HOST,
		.regs = अणु
			.override = 0x250,
			.security = 0x254,
		पूर्ण,
	पूर्ण, अणु
		.name = "xusb_hostw",
		.sid = TEGRA186_SID_XUSB_HOST,
		.regs = अणु
			.override = 0x258,
			.security = 0x25c,
		पूर्ण,
	पूर्ण, अणु
		.name = "xusb_devr",
		.sid = TEGRA186_SID_XUSB_DEV,
		.regs = अणु
			.override = 0x260,
			.security = 0x264,
		पूर्ण,
	पूर्ण, अणु
		.name = "xusb_devw",
		.sid = TEGRA186_SID_XUSB_DEV,
		.regs = अणु
			.override = 0x268,
			.security = 0x26c,
		पूर्ण,
	पूर्ण, अणु
		.name = "tsecsrd",
		.sid = TEGRA186_SID_TSEC,
		.regs = अणु
			.override = 0x2a0,
			.security = 0x2a4,
		पूर्ण,
	पूर्ण, अणु
		.name = "tsecswr",
		.sid = TEGRA186_SID_TSEC,
		.regs = अणु
			.override = 0x2a8,
			.security = 0x2ac,
		पूर्ण,
	पूर्ण, अणु
		.name = "gpusrd",
		.sid = TEGRA186_SID_GPU,
		.regs = अणु
			.override = 0x2c0,
			.security = 0x2c4,
		पूर्ण,
	पूर्ण, अणु
		.name = "gpuswr",
		.sid = TEGRA186_SID_GPU,
		.regs = अणु
			.override = 0x2c8,
			.security = 0x2cc,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcra",
		.sid = TEGRA186_SID_SDMMC1,
		.regs = अणु
			.override = 0x300,
			.security = 0x304,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcraa",
		.sid = TEGRA186_SID_SDMMC2,
		.regs = अणु
			.override = 0x308,
			.security = 0x30c,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcr",
		.sid = TEGRA186_SID_SDMMC3,
		.regs = अणु
			.override = 0x310,
			.security = 0x314,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcrab",
		.sid = TEGRA186_SID_SDMMC4,
		.regs = अणु
			.override = 0x318,
			.security = 0x31c,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcwa",
		.sid = TEGRA186_SID_SDMMC1,
		.regs = अणु
			.override = 0x320,
			.security = 0x324,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcwaa",
		.sid = TEGRA186_SID_SDMMC2,
		.regs = अणु
			.override = 0x328,
			.security = 0x32c,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcw",
		.sid = TEGRA186_SID_SDMMC3,
		.regs = अणु
			.override = 0x330,
			.security = 0x334,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcwab",
		.sid = TEGRA186_SID_SDMMC4,
		.regs = अणु
			.override = 0x338,
			.security = 0x33c,
		पूर्ण,
	पूर्ण, अणु
		.name = "vicsrd",
		.sid = TEGRA186_SID_VIC,
		.regs = अणु
			.override = 0x360,
			.security = 0x364,
		पूर्ण,
	पूर्ण, अणु
		.name = "vicswr",
		.sid = TEGRA186_SID_VIC,
		.regs = अणु
			.override = 0x368,
			.security = 0x36c,
		पूर्ण,
	पूर्ण, अणु
		.name = "viw",
		.sid = TEGRA186_SID_VI,
		.regs = अणु
			.override = 0x390,
			.security = 0x394,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdecsrd",
		.sid = TEGRA186_SID_NVDEC,
		.regs = अणु
			.override = 0x3c0,
			.security = 0x3c4,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdecswr",
		.sid = TEGRA186_SID_NVDEC,
		.regs = अणु
			.override = 0x3c8,
			.security = 0x3cc,
		पूर्ण,
	पूर्ण, अणु
		.name = "aper",
		.sid = TEGRA186_SID_APE,
		.regs = अणु
			.override = 0x3d0,
			.security = 0x3d4,
		पूर्ण,
	पूर्ण, अणु
		.name = "apew",
		.sid = TEGRA186_SID_APE,
		.regs = अणु
			.override = 0x3d8,
			.security = 0x3dc,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvjpgsrd",
		.sid = TEGRA186_SID_NVJPG,
		.regs = अणु
			.override = 0x3f0,
			.security = 0x3f4,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvjpgswr",
		.sid = TEGRA186_SID_NVJPG,
		.regs = अणु
			.override = 0x3f8,
			.security = 0x3fc,
		पूर्ण,
	पूर्ण, अणु
		.name = "sesrd",
		.sid = TEGRA186_SID_SE,
		.regs = अणु
			.override = 0x400,
			.security = 0x404,
		पूर्ण,
	पूर्ण, अणु
		.name = "seswr",
		.sid = TEGRA186_SID_SE,
		.regs = अणु
			.override = 0x408,
			.security = 0x40c,
		पूर्ण,
	पूर्ण, अणु
		.name = "etrr",
		.sid = TEGRA186_SID_ETR,
		.regs = अणु
			.override = 0x420,
			.security = 0x424,
		पूर्ण,
	पूर्ण, अणु
		.name = "etrw",
		.sid = TEGRA186_SID_ETR,
		.regs = अणु
			.override = 0x428,
			.security = 0x42c,
		पूर्ण,
	पूर्ण, अणु
		.name = "tsecsrdb",
		.sid = TEGRA186_SID_TSECB,
		.regs = अणु
			.override = 0x430,
			.security = 0x434,
		पूर्ण,
	पूर्ण, अणु
		.name = "tsecswrb",
		.sid = TEGRA186_SID_TSECB,
		.regs = अणु
			.override = 0x438,
			.security = 0x43c,
		पूर्ण,
	पूर्ण, अणु
		.name = "gpusrd2",
		.sid = TEGRA186_SID_GPU,
		.regs = अणु
			.override = 0x440,
			.security = 0x444,
		पूर्ण,
	पूर्ण, अणु
		.name = "gpuswr2",
		.sid = TEGRA186_SID_GPU,
		.regs = अणु
			.override = 0x448,
			.security = 0x44c,
		पूर्ण,
	पूर्ण, अणु
		.name = "axisr",
		.sid = TEGRA186_SID_GPCDMA_0,
		.regs = अणु
			.override = 0x460,
			.security = 0x464,
		पूर्ण,
	पूर्ण, अणु
		.name = "axisw",
		.sid = TEGRA186_SID_GPCDMA_0,
		.regs = अणु
			.override = 0x468,
			.security = 0x46c,
		पूर्ण,
	पूर्ण, अणु
		.name = "eqosr",
		.sid = TEGRA186_SID_EQOS,
		.regs = अणु
			.override = 0x470,
			.security = 0x474,
		पूर्ण,
	पूर्ण, अणु
		.name = "eqosw",
		.sid = TEGRA186_SID_EQOS,
		.regs = अणु
			.override = 0x478,
			.security = 0x47c,
		पूर्ण,
	पूर्ण, अणु
		.name = "ufshcr",
		.sid = TEGRA186_SID_UFSHC,
		.regs = अणु
			.override = 0x480,
			.security = 0x484,
		पूर्ण,
	पूर्ण, अणु
		.name = "ufshcw",
		.sid = TEGRA186_SID_UFSHC,
		.regs = अणु
			.override = 0x488,
			.security = 0x48c,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdisplayr",
		.sid = TEGRA186_SID_NVDISPLAY,
		.regs = अणु
			.override = 0x490,
			.security = 0x494,
		पूर्ण,
	पूर्ण, अणु
		.name = "bpmpr",
		.sid = TEGRA186_SID_BPMP,
		.regs = अणु
			.override = 0x498,
			.security = 0x49c,
		पूर्ण,
	पूर्ण, अणु
		.name = "bpmpw",
		.sid = TEGRA186_SID_BPMP,
		.regs = अणु
			.override = 0x4a0,
			.security = 0x4a4,
		पूर्ण,
	पूर्ण, अणु
		.name = "bpmpdmar",
		.sid = TEGRA186_SID_BPMP,
		.regs = अणु
			.override = 0x4a8,
			.security = 0x4ac,
		पूर्ण,
	पूर्ण, अणु
		.name = "bpmpdmaw",
		.sid = TEGRA186_SID_BPMP,
		.regs = अणु
			.override = 0x4b0,
			.security = 0x4b4,
		पूर्ण,
	पूर्ण, अणु
		.name = "aonr",
		.sid = TEGRA186_SID_AON,
		.regs = अणु
			.override = 0x4b8,
			.security = 0x4bc,
		पूर्ण,
	पूर्ण, अणु
		.name = "aonw",
		.sid = TEGRA186_SID_AON,
		.regs = अणु
			.override = 0x4c0,
			.security = 0x4c4,
		पूर्ण,
	पूर्ण, अणु
		.name = "aondmar",
		.sid = TEGRA186_SID_AON,
		.regs = अणु
			.override = 0x4c8,
			.security = 0x4cc,
		पूर्ण,
	पूर्ण, अणु
		.name = "aondmaw",
		.sid = TEGRA186_SID_AON,
		.regs = अणु
			.override = 0x4d0,
			.security = 0x4d4,
		पूर्ण,
	पूर्ण, अणु
		.name = "scer",
		.sid = TEGRA186_SID_SCE,
		.regs = अणु
			.override = 0x4d8,
			.security = 0x4dc,
		पूर्ण,
	पूर्ण, अणु
		.name = "scew",
		.sid = TEGRA186_SID_SCE,
		.regs = अणु
			.override = 0x4e0,
			.security = 0x4e4,
		पूर्ण,
	पूर्ण, अणु
		.name = "scedmar",
		.sid = TEGRA186_SID_SCE,
		.regs = अणु
			.override = 0x4e8,
			.security = 0x4ec,
		पूर्ण,
	पूर्ण, अणु
		.name = "scedmaw",
		.sid = TEGRA186_SID_SCE,
		.regs = अणु
			.override = 0x4f0,
			.security = 0x4f4,
		पूर्ण,
	पूर्ण, अणु
		.name = "apedmar",
		.sid = TEGRA186_SID_APE,
		.regs = अणु
			.override = 0x4f8,
			.security = 0x4fc,
		पूर्ण,
	पूर्ण, अणु
		.name = "apedmaw",
		.sid = TEGRA186_SID_APE,
		.regs = अणु
			.override = 0x500,
			.security = 0x504,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdisplayr1",
		.sid = TEGRA186_SID_NVDISPLAY,
		.regs = अणु
			.override = 0x508,
			.security = 0x50c,
		पूर्ण,
	पूर्ण, अणु
		.name = "vicsrd1",
		.sid = TEGRA186_SID_VIC,
		.regs = अणु
			.override = 0x510,
			.security = 0x514,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdecsrd1",
		.sid = TEGRA186_SID_NVDEC,
		.regs = अणु
			.override = 0x518,
			.security = 0x51c,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra186_mc_soc tegra186_mc_soc = अणु
	.num_clients = ARRAY_SIZE(tegra186_mc_clients),
	.clients = tegra186_mc_clients,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_TEGRA_194_SOC)
अटल स्थिर काष्ठा tegra186_mc_client tegra194_mc_clients[] = अणु
	अणु
		.name = "ptcr",
		.sid = TEGRA194_SID_PASSTHROUGH,
		.regs = अणु
			.override = 0x000,
			.security = 0x004,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu7r",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x008,
			.security = 0x00c,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu7w",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x010,
			.security = 0x014,
		पूर्ण,
	पूर्ण, अणु
		.name = "hdar",
		.sid = TEGRA194_SID_HDA,
		.regs = अणु
			.override = 0x0a8,
			.security = 0x0ac,
		पूर्ण,
	पूर्ण, अणु
		.name = "host1xdmar",
		.sid = TEGRA194_SID_HOST1X,
		.regs = अणु
			.override = 0x0b0,
			.security = 0x0b4,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvencsrd",
		.sid = TEGRA194_SID_NVENC,
		.regs = अणु
			.override = 0x0e0,
			.security = 0x0e4,
		पूर्ण,
	पूर्ण, अणु
		.name = "satar",
		.sid = TEGRA194_SID_SATA,
		.regs = अणु
			.override = 0x0f8,
			.security = 0x0fc,
		पूर्ण,
	पूर्ण, अणु
		.name = "mpcorer",
		.sid = TEGRA194_SID_PASSTHROUGH,
		.regs = अणु
			.override = 0x138,
			.security = 0x13c,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvencswr",
		.sid = TEGRA194_SID_NVENC,
		.regs = अणु
			.override = 0x158,
			.security = 0x15c,
		पूर्ण,
	पूर्ण, अणु
		.name = "hdaw",
		.sid = TEGRA194_SID_HDA,
		.regs = अणु
			.override = 0x1a8,
			.security = 0x1ac,
		पूर्ण,
	पूर्ण, अणु
		.name = "mpcorew",
		.sid = TEGRA194_SID_PASSTHROUGH,
		.regs = अणु
			.override = 0x1c8,
			.security = 0x1cc,
		पूर्ण,
	पूर्ण, अणु
		.name = "sataw",
		.sid = TEGRA194_SID_SATA,
		.regs = अणु
			.override = 0x1e8,
			.security = 0x1ec,
		पूर्ण,
	पूर्ण, अणु
		.name = "ispra",
		.sid = TEGRA194_SID_ISP,
		.regs = अणु
			.override = 0x220,
			.security = 0x224,
		पूर्ण,
	पूर्ण, अणु
		.name = "ispfalr",
		.sid = TEGRA194_SID_ISP_FALCON,
		.regs = अणु
			.override = 0x228,
			.security = 0x22c,
		पूर्ण,
	पूर्ण, अणु
		.name = "ispwa",
		.sid = TEGRA194_SID_ISP,
		.regs = अणु
			.override = 0x230,
			.security = 0x234,
		पूर्ण,
	पूर्ण, अणु
		.name = "ispwb",
		.sid = TEGRA194_SID_ISP,
		.regs = अणु
			.override = 0x238,
			.security = 0x23c,
		पूर्ण,
	पूर्ण, अणु
		.name = "xusb_hostr",
		.sid = TEGRA194_SID_XUSB_HOST,
		.regs = अणु
			.override = 0x250,
			.security = 0x254,
		पूर्ण,
	पूर्ण, अणु
		.name = "xusb_hostw",
		.sid = TEGRA194_SID_XUSB_HOST,
		.regs = अणु
			.override = 0x258,
			.security = 0x25c,
		पूर्ण,
	पूर्ण, अणु
		.name = "xusb_devr",
		.sid = TEGRA194_SID_XUSB_DEV,
		.regs = अणु
			.override = 0x260,
			.security = 0x264,
		पूर्ण,
	पूर्ण, अणु
		.name = "xusb_devw",
		.sid = TEGRA194_SID_XUSB_DEV,
		.regs = अणु
			.override = 0x268,
			.security = 0x26c,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcra",
		.sid = TEGRA194_SID_SDMMC1,
		.regs = अणु
			.override = 0x300,
			.security = 0x304,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcr",
		.sid = TEGRA194_SID_SDMMC3,
		.regs = अणु
			.override = 0x310,
			.security = 0x314,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcrab",
		.sid = TEGRA194_SID_SDMMC4,
		.regs = अणु
			.override = 0x318,
			.security = 0x31c,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcwa",
		.sid = TEGRA194_SID_SDMMC1,
		.regs = अणु
			.override = 0x320,
			.security = 0x324,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcw",
		.sid = TEGRA194_SID_SDMMC3,
		.regs = अणु
			.override = 0x330,
			.security = 0x334,
		पूर्ण,
	पूर्ण, अणु
		.name = "sdmmcwab",
		.sid = TEGRA194_SID_SDMMC4,
		.regs = अणु
			.override = 0x338,
			.security = 0x33c,
		पूर्ण,
	पूर्ण, अणु
		.name = "vicsrd",
		.sid = TEGRA194_SID_VIC,
		.regs = अणु
			.override = 0x360,
			.security = 0x364,
		पूर्ण,
	पूर्ण, अणु
		.name = "vicswr",
		.sid = TEGRA194_SID_VIC,
		.regs = अणु
			.override = 0x368,
			.security = 0x36c,
		पूर्ण,
	पूर्ण, अणु
		.name = "viw",
		.sid = TEGRA194_SID_VI,
		.regs = अणु
			.override = 0x390,
			.security = 0x394,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdecsrd",
		.sid = TEGRA194_SID_NVDEC,
		.regs = अणु
			.override = 0x3c0,
			.security = 0x3c4,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdecswr",
		.sid = TEGRA194_SID_NVDEC,
		.regs = अणु
			.override = 0x3c8,
			.security = 0x3cc,
		पूर्ण,
	पूर्ण, अणु
		.name = "aper",
		.sid = TEGRA194_SID_APE,
		.regs = अणु
			.override = 0x3c0,
			.security = 0x3c4,
		पूर्ण,
	पूर्ण, अणु
		.name = "apew",
		.sid = TEGRA194_SID_APE,
		.regs = अणु
			.override = 0x3d0,
			.security = 0x3d4,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvjpgsrd",
		.sid = TEGRA194_SID_NVJPG,
		.regs = अणु
			.override = 0x3f0,
			.security = 0x3f4,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvjpgswr",
		.sid = TEGRA194_SID_NVJPG,
		.regs = अणु
			.override = 0x3f0,
			.security = 0x3f4,
		पूर्ण,
	पूर्ण, अणु
		.name = "axiapr",
		.sid = TEGRA194_SID_PASSTHROUGH,
		.regs = अणु
			.override = 0x410,
			.security = 0x414,
		पूर्ण,
	पूर्ण, अणु
		.name = "axiapw",
		.sid = TEGRA194_SID_PASSTHROUGH,
		.regs = अणु
			.override = 0x418,
			.security = 0x41c,
		पूर्ण,
	पूर्ण, अणु
		.name = "etrr",
		.sid = TEGRA194_SID_ETR,
		.regs = अणु
			.override = 0x420,
			.security = 0x424,
		पूर्ण,
	पूर्ण, अणु
		.name = "etrw",
		.sid = TEGRA194_SID_ETR,
		.regs = अणु
			.override = 0x428,
			.security = 0x42c,
		पूर्ण,
	पूर्ण, अणु
		.name = "axisr",
		.sid = TEGRA194_SID_PASSTHROUGH,
		.regs = अणु
			.override = 0x460,
			.security = 0x464,
		पूर्ण,
	पूर्ण, अणु
		.name = "axisw",
		.sid = TEGRA194_SID_PASSTHROUGH,
		.regs = अणु
			.override = 0x468,
			.security = 0x46c,
		पूर्ण,
	पूर्ण, अणु
		.name = "eqosr",
		.sid = TEGRA194_SID_EQOS,
		.regs = अणु
			.override = 0x470,
			.security = 0x474,
		पूर्ण,
	पूर्ण, अणु
		.name = "eqosw",
		.sid = TEGRA194_SID_EQOS,
		.regs = अणु
			.override = 0x478,
			.security = 0x47c,
		पूर्ण,
	पूर्ण, अणु
		.name = "ufshcr",
		.sid = TEGRA194_SID_UFSHC,
		.regs = अणु
			.override = 0x480,
			.security = 0x484,
		पूर्ण,
	पूर्ण, अणु
		.name = "ufshcw",
		.sid = TEGRA194_SID_UFSHC,
		.regs = अणु
			.override = 0x488,
			.security = 0x48c,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdisplayr",
		.sid = TEGRA194_SID_NVDISPLAY,
		.regs = अणु
			.override = 0x490,
			.security = 0x494,
		पूर्ण,
	पूर्ण, अणु
		.name = "bpmpr",
		.sid = TEGRA194_SID_BPMP,
		.regs = अणु
			.override = 0x498,
			.security = 0x49c,
		पूर्ण,
	पूर्ण, अणु
		.name = "bpmpw",
		.sid = TEGRA194_SID_BPMP,
		.regs = अणु
			.override = 0x4a0,
			.security = 0x4a4,
		पूर्ण,
	पूर्ण, अणु
		.name = "bpmpdmar",
		.sid = TEGRA194_SID_BPMP,
		.regs = अणु
			.override = 0x4a8,
			.security = 0x4ac,
		पूर्ण,
	पूर्ण, अणु
		.name = "bpmpdmaw",
		.sid = TEGRA194_SID_BPMP,
		.regs = अणु
			.override = 0x4b0,
			.security = 0x4b4,
		पूर्ण,
	पूर्ण, अणु
		.name = "aonr",
		.sid = TEGRA194_SID_AON,
		.regs = अणु
			.override = 0x4b8,
			.security = 0x4bc,
		पूर्ण,
	पूर्ण, अणु
		.name = "aonw",
		.sid = TEGRA194_SID_AON,
		.regs = अणु
			.override = 0x4c0,
			.security = 0x4c4,
		पूर्ण,
	पूर्ण, अणु
		.name = "aondmar",
		.sid = TEGRA194_SID_AON,
		.regs = अणु
			.override = 0x4c8,
			.security = 0x4cc,
		पूर्ण,
	पूर्ण, अणु
		.name = "aondmaw",
		.sid = TEGRA194_SID_AON,
		.regs = अणु
			.override = 0x4d0,
			.security = 0x4d4,
		पूर्ण,
	पूर्ण, अणु
		.name = "scer",
		.sid = TEGRA194_SID_SCE,
		.regs = अणु
			.override = 0x4d8,
			.security = 0x4dc,
		पूर्ण,
	पूर्ण, अणु
		.name = "scew",
		.sid = TEGRA194_SID_SCE,
		.regs = अणु
			.override = 0x4e0,
			.security = 0x4e4,
		पूर्ण,
	पूर्ण, अणु
		.name = "scedmar",
		.sid = TEGRA194_SID_SCE,
		.regs = अणु
			.override = 0x4e8,
			.security = 0x4ec,
		पूर्ण,
	पूर्ण, अणु
		.name = "scedmaw",
		.sid = TEGRA194_SID_SCE,
		.regs = अणु
			.override = 0x4f0,
			.security = 0x4f4,
		पूर्ण,
	पूर्ण, अणु
		.name = "apedmar",
		.sid = TEGRA194_SID_APE,
		.regs = अणु
			.override = 0x4f8,
			.security = 0x4fc,
		पूर्ण,
	पूर्ण, अणु
		.name = "apedmaw",
		.sid = TEGRA194_SID_APE,
		.regs = अणु
			.override = 0x500,
			.security = 0x504,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdisplayr1",
		.sid = TEGRA194_SID_NVDISPLAY,
		.regs = अणु
			.override = 0x508,
			.security = 0x50c,
		पूर्ण,
	पूर्ण, अणु
		.name = "vicsrd1",
		.sid = TEGRA194_SID_VIC,
		.regs = अणु
			.override = 0x510,
			.security = 0x514,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdecsrd1",
		.sid = TEGRA194_SID_NVDEC,
		.regs = अणु
			.override = 0x518,
			.security = 0x51c,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu0r",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x530,
			.security = 0x534,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu0w",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x538,
			.security = 0x53c,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu1r",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x540,
			.security = 0x544,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu1w",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x548,
			.security = 0x54c,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu2r",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x570,
			.security = 0x574,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu2w",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x578,
			.security = 0x57c,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu3r",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x580,
			.security = 0x584,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu3w",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x588,
			.security = 0x58c,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu4r",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x590,
			.security = 0x594,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu4w",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x598,
			.security = 0x59c,
		पूर्ण,
	पूर्ण, अणु
		.name = "dpmur",
		.sid = TEGRA194_SID_PASSTHROUGH,
		.regs = अणु
			.override = 0x598,
			.security = 0x59c,
		पूर्ण,
	पूर्ण, अणु
		.name = "vifalr",
		.sid = TEGRA194_SID_VI_FALCON,
		.regs = अणु
			.override = 0x5e0,
			.security = 0x5e4,
		पूर्ण,
	पूर्ण, अणु
		.name = "vifalw",
		.sid = TEGRA194_SID_VI_FALCON,
		.regs = अणु
			.override = 0x5e8,
			.security = 0x5ec,
		पूर्ण,
	पूर्ण, अणु
		.name = "dla0rda",
		.sid = TEGRA194_SID_NVDLA0,
		.regs = अणु
			.override = 0x5f0,
			.security = 0x5f4,
		पूर्ण,
	पूर्ण, अणु
		.name = "dla0falrdb",
		.sid = TEGRA194_SID_NVDLA0,
		.regs = अणु
			.override = 0x5f8,
			.security = 0x5fc,
		पूर्ण,
	पूर्ण, अणु
		.name = "dla0wra",
		.sid = TEGRA194_SID_NVDLA0,
		.regs = अणु
			.override = 0x600,
			.security = 0x604,
		पूर्ण,
	पूर्ण, अणु
		.name = "dla0falwrb",
		.sid = TEGRA194_SID_NVDLA0,
		.regs = अणु
			.override = 0x608,
			.security = 0x60c,
		पूर्ण,
	पूर्ण, अणु
		.name = "dla1rda",
		.sid = TEGRA194_SID_NVDLA1,
		.regs = अणु
			.override = 0x610,
			.security = 0x614,
		पूर्ण,
	पूर्ण, अणु
		.name = "dla1falrdb",
		.sid = TEGRA194_SID_NVDLA1,
		.regs = अणु
			.override = 0x618,
			.security = 0x61c,
		पूर्ण,
	पूर्ण, अणु
		.name = "dla1wra",
		.sid = TEGRA194_SID_NVDLA1,
		.regs = अणु
			.override = 0x620,
			.security = 0x624,
		पूर्ण,
	पूर्ण, अणु
		.name = "dla1falwrb",
		.sid = TEGRA194_SID_NVDLA1,
		.regs = अणु
			.override = 0x628,
			.security = 0x62c,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva0rda",
		.sid = TEGRA194_SID_PVA0,
		.regs = अणु
			.override = 0x630,
			.security = 0x634,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva0rdb",
		.sid = TEGRA194_SID_PVA0,
		.regs = अणु
			.override = 0x638,
			.security = 0x63c,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva0rdc",
		.sid = TEGRA194_SID_PVA0,
		.regs = अणु
			.override = 0x640,
			.security = 0x644,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva0wra",
		.sid = TEGRA194_SID_PVA0,
		.regs = अणु
			.override = 0x648,
			.security = 0x64c,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva0wrb",
		.sid = TEGRA194_SID_PVA0,
		.regs = अणु
			.override = 0x650,
			.security = 0x654,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva0wrc",
		.sid = TEGRA194_SID_PVA0,
		.regs = अणु
			.override = 0x658,
			.security = 0x65c,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva1rda",
		.sid = TEGRA194_SID_PVA1,
		.regs = अणु
			.override = 0x660,
			.security = 0x664,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva1rdb",
		.sid = TEGRA194_SID_PVA1,
		.regs = अणु
			.override = 0x668,
			.security = 0x66c,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva1rdc",
		.sid = TEGRA194_SID_PVA1,
		.regs = अणु
			.override = 0x670,
			.security = 0x674,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva1wra",
		.sid = TEGRA194_SID_PVA1,
		.regs = अणु
			.override = 0x678,
			.security = 0x67c,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva1wrb",
		.sid = TEGRA194_SID_PVA1,
		.regs = अणु
			.override = 0x680,
			.security = 0x684,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva1wrc",
		.sid = TEGRA194_SID_PVA1,
		.regs = अणु
			.override = 0x688,
			.security = 0x68c,
		पूर्ण,
	पूर्ण, अणु
		.name = "rcer",
		.sid = TEGRA194_SID_RCE,
		.regs = अणु
			.override = 0x690,
			.security = 0x694,
		पूर्ण,
	पूर्ण, अणु
		.name = "rcew",
		.sid = TEGRA194_SID_RCE,
		.regs = अणु
			.override = 0x698,
			.security = 0x69c,
		पूर्ण,
	पूर्ण, अणु
		.name = "rcedmar",
		.sid = TEGRA194_SID_RCE,
		.regs = अणु
			.override = 0x6a0,
			.security = 0x6a4,
		पूर्ण,
	पूर्ण, अणु
		.name = "rcedmaw",
		.sid = TEGRA194_SID_RCE,
		.regs = अणु
			.override = 0x6a8,
			.security = 0x6ac,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvenc1srd",
		.sid = TEGRA194_SID_NVENC1,
		.regs = अणु
			.override = 0x6b0,
			.security = 0x6b4,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvenc1swr",
		.sid = TEGRA194_SID_NVENC1,
		.regs = अणु
			.override = 0x6b8,
			.security = 0x6bc,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie0r",
		.sid = TEGRA194_SID_PCIE0,
		.regs = अणु
			.override = 0x6c0,
			.security = 0x6c4,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie0w",
		.sid = TEGRA194_SID_PCIE0,
		.regs = अणु
			.override = 0x6c8,
			.security = 0x6cc,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie1r",
		.sid = TEGRA194_SID_PCIE1,
		.regs = अणु
			.override = 0x6d0,
			.security = 0x6d4,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie1w",
		.sid = TEGRA194_SID_PCIE1,
		.regs = अणु
			.override = 0x6d8,
			.security = 0x6dc,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie2ar",
		.sid = TEGRA194_SID_PCIE2,
		.regs = अणु
			.override = 0x6e0,
			.security = 0x6e4,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie2aw",
		.sid = TEGRA194_SID_PCIE2,
		.regs = अणु
			.override = 0x6e8,
			.security = 0x6ec,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie3r",
		.sid = TEGRA194_SID_PCIE3,
		.regs = अणु
			.override = 0x6f0,
			.security = 0x6f4,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie3w",
		.sid = TEGRA194_SID_PCIE3,
		.regs = अणु
			.override = 0x6f8,
			.security = 0x6fc,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie4r",
		.sid = TEGRA194_SID_PCIE4,
		.regs = अणु
			.override = 0x700,
			.security = 0x704,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie4w",
		.sid = TEGRA194_SID_PCIE4,
		.regs = अणु
			.override = 0x708,
			.security = 0x70c,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie5r",
		.sid = TEGRA194_SID_PCIE5,
		.regs = अणु
			.override = 0x710,
			.security = 0x714,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie5w",
		.sid = TEGRA194_SID_PCIE5,
		.regs = अणु
			.override = 0x718,
			.security = 0x71c,
		पूर्ण,
	पूर्ण, अणु
		.name = "ispfalw",
		.sid = TEGRA194_SID_ISP_FALCON,
		.regs = अणु
			.override = 0x720,
			.security = 0x724,
		पूर्ण,
	पूर्ण, अणु
		.name = "dla0rda1",
		.sid = TEGRA194_SID_NVDLA0,
		.regs = अणु
			.override = 0x748,
			.security = 0x74c,
		पूर्ण,
	पूर्ण, अणु
		.name = "dla1rda1",
		.sid = TEGRA194_SID_NVDLA1,
		.regs = अणु
			.override = 0x750,
			.security = 0x754,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva0rda1",
		.sid = TEGRA194_SID_PVA0,
		.regs = अणु
			.override = 0x758,
			.security = 0x75c,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva0rdb1",
		.sid = TEGRA194_SID_PVA0,
		.regs = अणु
			.override = 0x760,
			.security = 0x764,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva1rda1",
		.sid = TEGRA194_SID_PVA1,
		.regs = अणु
			.override = 0x768,
			.security = 0x76c,
		पूर्ण,
	पूर्ण, अणु
		.name = "pva1rdb1",
		.sid = TEGRA194_SID_PVA1,
		.regs = अणु
			.override = 0x770,
			.security = 0x774,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie5r1",
		.sid = TEGRA194_SID_PCIE5,
		.regs = अणु
			.override = 0x778,
			.security = 0x77c,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvencsrd1",
		.sid = TEGRA194_SID_NVENC,
		.regs = अणु
			.override = 0x780,
			.security = 0x784,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvenc1srd1",
		.sid = TEGRA194_SID_NVENC1,
		.regs = अणु
			.override = 0x788,
			.security = 0x78c,
		पूर्ण,
	पूर्ण, अणु
		.name = "ispra1",
		.sid = TEGRA194_SID_ISP,
		.regs = अणु
			.override = 0x790,
			.security = 0x794,
		पूर्ण,
	पूर्ण, अणु
		.name = "pcie0r1",
		.sid = TEGRA194_SID_PCIE0,
		.regs = अणु
			.override = 0x798,
			.security = 0x79c,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdec1srd",
		.sid = TEGRA194_SID_NVDEC1,
		.regs = अणु
			.override = 0x7c8,
			.security = 0x7cc,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdec1srd1",
		.sid = TEGRA194_SID_NVDEC1,
		.regs = अणु
			.override = 0x7d0,
			.security = 0x7d4,
		पूर्ण,
	पूर्ण, अणु
		.name = "nvdec1swr",
		.sid = TEGRA194_SID_NVDEC1,
		.regs = अणु
			.override = 0x7d8,
			.security = 0x7dc,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu5r",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x7e0,
			.security = 0x7e4,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu5w",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x7e8,
			.security = 0x7ec,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu6r",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x7f0,
			.security = 0x7f4,
		पूर्ण,
	पूर्ण, अणु
		.name = "miu6w",
		.sid = TEGRA194_SID_MIU,
		.regs = अणु
			.override = 0x7f8,
			.security = 0x7fc,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra186_mc_soc tegra194_mc_soc = अणु
	.num_clients = ARRAY_SIZE(tegra194_mc_clients),
	.clients = tegra194_mc_clients,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक tegra186_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra186_mc *mc;
	काष्ठा resource *res;
	पूर्णांक err;

	mc = devm_kzalloc(&pdev->dev, माप(*mc), GFP_KERNEL);
	अगर (!mc)
		वापस -ENOMEM;

	mc->soc = of_device_get_match_data(&pdev->dev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mc->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mc->regs))
		वापस PTR_ERR(mc->regs);

	mc->dev = &pdev->dev;

	err = of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);
	अगर (err < 0)
		वापस err;

	platक्रमm_set_drvdata(pdev, mc);
	tegra186_mc_program_sid(mc);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_mc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra186_mc *mc = platक्रमm_get_drvdata(pdev);

	of_platक्रमm_depopulate(mc->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra186_mc_of_match[] = अणु
#अगर defined(CONFIG_ARCH_TEGRA_186_SOC)
	अणु .compatible = "nvidia,tegra186-mc", .data = &tegra186_mc_soc पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_TEGRA_194_SOC)
	अणु .compatible = "nvidia,tegra194-mc", .data = &tegra194_mc_soc पूर्ण,
#पूर्ण_अगर
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra186_mc_of_match);

अटल पूर्णांक __maybe_unused tegra186_mc_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra186_mc_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra186_mc *mc = dev_get_drvdata(dev);

	tegra186_mc_program_sid(mc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra186_mc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tegra186_mc_suspend, tegra186_mc_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra186_mc_driver = अणु
	.driver = अणु
		.name = "tegra186-mc",
		.of_match_table = tegra186_mc_of_match,
		.pm = &tegra186_mc_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = tegra186_mc_probe,
	.हटाओ = tegra186_mc_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra186_mc_driver);

MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra186 Memory Controller driver");
MODULE_LICENSE("GPL v2");
