<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_CSTEP_H__
#घोषणा __NVBIOS_CSTEP_H__
u32 nvbios_cstepTe(काष्ठा nvkm_bios *,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *xnr, u8 *xsz);

काष्ठा nvbios_cstepE अणु
	u8  pstate;
	u8  index;
पूर्ण;

u32 nvbios_cstepEe(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *hdr);
u32 nvbios_cstepEp(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *hdr,
		   काष्ठा nvbios_cstepE *);
u32 nvbios_cstepEm(काष्ठा nvkm_bios *, u8 pstate, u8 *ver, u8 *hdr,
		   काष्ठा nvbios_cstepE *);

काष्ठा nvbios_cstepX अणु
	u32 freq;
	u8  unkn[2];
	u8  voltage;
पूर्ण;

u32 nvbios_cstepXe(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *hdr);
u32 nvbios_cstepXp(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *hdr,
		   काष्ठा nvbios_cstepX *);
#पूर्ण_अगर
