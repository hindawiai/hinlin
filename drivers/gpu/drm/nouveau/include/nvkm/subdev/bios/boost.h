<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_BOOST_H__
#घोषणा __NVBIOS_BOOST_H__
u32 nvbios_boostTe(काष्ठा nvkm_bios *, u8 *, u8 *, u8 *, u8 *, u8 *, u8 *);

काष्ठा nvbios_boostE अणु
	u8  pstate;
	u32 min;
	u32 max;
पूर्ण;

u32 nvbios_boostEe(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *, u8 *, u8 *, u8 *);
u32 nvbios_boostEp(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *, u8 *, u8 *, u8 *,
		   काष्ठा nvbios_boostE *);
u32 nvbios_boostEm(काष्ठा nvkm_bios *, u8, u8 *, u8 *, u8 *, u8 *,
		   काष्ठा nvbios_boostE *);

काष्ठा nvbios_boostS अणु
	u8  करोमुख्य;
	u8  percent;
	u32 min;
	u32 max;
पूर्ण;

u32 nvbios_boostSe(काष्ठा nvkm_bios *, पूर्णांक, u32, u8 *, u8 *, u8, u8);
u32 nvbios_boostSp(काष्ठा nvkm_bios *, पूर्णांक, u32, u8 *, u8 *, u8, u8,
		   काष्ठा nvbios_boostS *);
#पूर्ण_अगर
