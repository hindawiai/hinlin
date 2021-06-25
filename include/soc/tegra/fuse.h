<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित __SOC_TEGRA_FUSE_H__
#घोषणा __SOC_TEGRA_FUSE_H__

#घोषणा TEGRA20		0x20
#घोषणा TEGRA30		0x30
#घोषणा TEGRA114	0x35
#घोषणा TEGRA124	0x40
#घोषणा TEGRA132	0x13
#घोषणा TEGRA210	0x21
#घोषणा TEGRA186	0x18
#घोषणा TEGRA194	0x19
#घोषणा TEGRA234	0x23

#घोषणा TEGRA_FUSE_SKU_CALIB_0	0xf0
#घोषणा TEGRA30_FUSE_SATA_CALIB	0x124
#घोषणा TEGRA_FUSE_USB_CALIB_EXT_0 0x250

#अगर_अघोषित __ASSEMBLY__

u32 tegra_पढ़ो_chipid(व्योम);
u8 tegra_get_chip_id(व्योम);
u8 tegra_get_platक्रमm(व्योम);
bool tegra_is_silicon(व्योम);

क्रमागत tegra_revision अणु
	TEGRA_REVISION_UNKNOWN = 0,
	TEGRA_REVISION_A01,
	TEGRA_REVISION_A02,
	TEGRA_REVISION_A03,
	TEGRA_REVISION_A03p,
	TEGRA_REVISION_A04,
	TEGRA_REVISION_MAX,
पूर्ण;

काष्ठा tegra_sku_info अणु
	पूर्णांक sku_id;
	पूर्णांक cpu_process_id;
	पूर्णांक cpu_speeकरो_id;
	पूर्णांक cpu_speeकरो_value;
	पूर्णांक cpu_iddq_value;
	पूर्णांक soc_process_id;
	पूर्णांक soc_speeकरो_id;
	पूर्णांक soc_speeकरो_value;
	पूर्णांक gpu_process_id;
	पूर्णांक gpu_speeकरो_id;
	पूर्णांक gpu_speeकरो_value;
	क्रमागत tegra_revision revision;
पूर्ण;

u32 tegra_पढ़ो_straps(व्योम);
u32 tegra_पढ़ो_ram_code(व्योम);
पूर्णांक tegra_fuse_पढ़ोl(अचिन्हित दीर्घ offset, u32 *value);

#अगर_घोषित CONFIG_ARCH_TEGRA
बाह्य काष्ठा tegra_sku_info tegra_sku_info;
#अन्यथा
अटल काष्ठा tegra_sku_info tegra_sku_info __maybe_unused;
#पूर्ण_अगर

काष्ठा device *tegra_soc_device_रेजिस्टर(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __SOC_TEGRA_FUSE_H__ */
