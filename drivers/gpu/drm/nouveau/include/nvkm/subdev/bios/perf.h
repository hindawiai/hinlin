<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_PERF_H__
#घोषणा __NVBIOS_PERF_H__
u32 nvbios_perf_table(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr,
		      u8 *cnt, u8 *len, u8 *snr, u8 *ssz);

काष्ठा nvbios_perfE अणु
	u8  pstate;
	u8  fanspeed;
	u8  voltage;
	u32 core;
	u32 shader;
	u32 memory;
	u32 vdec;
	u32 disp;
	u32 script;
	u8  pcie_speed;
	u8  pcie_width;
पूर्ण;

u32 nvbios_perf_entry(काष्ठा nvkm_bios *, पूर्णांक idx,
		      u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u32 nvbios_perfEp(काष्ठा nvkm_bios *, पूर्णांक idx,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_perfE *);

काष्ठा nvbios_perfS अणु
	जोड़ अणु
		काष्ठा अणु
			u32 freq;
		पूर्ण v40;
	पूर्ण;
पूर्ण;

u32 nvbios_perfSe(काष्ठा nvkm_bios *, u32 data, पूर्णांक idx,
		  u8 *ver, u8 *hdr, u8 cnt, u8 len);
u32 nvbios_perfSp(काष्ठा nvkm_bios *, u32 data, पूर्णांक idx,
		  u8 *ver, u8 *hdr, u8 cnt, u8 len, काष्ठा nvbios_perfS *);

काष्ठा nvbios_perf_fan अणु
	u32 pwm_भागisor;
पूर्ण;

पूर्णांक nvbios_perf_fan_parse(काष्ठा nvkm_bios *, काष्ठा nvbios_perf_fan *);
#पूर्ण_अगर
