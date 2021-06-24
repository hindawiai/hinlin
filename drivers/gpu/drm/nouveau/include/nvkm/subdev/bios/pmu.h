<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_PMU_H__
#घोषणा __NVBIOS_PMU_H__
काष्ठा nvbios_pmuT अणु
पूर्ण;

u32 nvbios_pmuTe(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr, u8 *cnt, u8 *len);

काष्ठा nvbios_pmuE अणु
	u8  type;
	u32 data;
पूर्ण;

u32 nvbios_pmuEe(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *hdr);
u32 nvbios_pmuEp(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *hdr,
		 काष्ठा nvbios_pmuE *);

काष्ठा nvbios_pmuR अणु
	u32 boot_addr_pmu;
	u32 boot_addr;
	u32 boot_size;
	u32 code_addr_pmu;
	u32 code_addr;
	u32 code_size;
	u32 init_addr_pmu;

	u32 data_addr_pmu;
	u32 data_addr;
	u32 data_size;
	u32 args_addr_pmu;
पूर्ण;

bool nvbios_pmuRm(काष्ठा nvkm_bios *, u8 type, काष्ठा nvbios_pmuR *);
#पूर्ण_अगर
