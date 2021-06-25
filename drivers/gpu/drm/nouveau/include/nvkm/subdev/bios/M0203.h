<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_M0203_H__
#घोषणा __NVBIOS_M0203_H__
काष्ठा nvbios_M0203T अणु
#घोषणा M0203T_TYPE_RAMCFG 0x00
	u8  type;
	u16 poपूर्णांकer;
पूर्ण;

u32 nvbios_M0203Te(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u32 nvbios_M0203Tp(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		   काष्ठा nvbios_M0203T *);

काष्ठा nvbios_M0203E अणु
#घोषणा M0203E_TYPE_DDR2   0x0
#घोषणा M0203E_TYPE_DDR3   0x1
#घोषणा M0203E_TYPE_GDDR3  0x2
#घोषणा M0203E_TYPE_GDDR5  0x3
#घोषणा M0203E_TYPE_HBM2   0x6
#घोषणा M0203E_TYPE_GDDR5X 0x8
#घोषणा M0203E_TYPE_GDDR6  0x9
#घोषणा M0203E_TYPE_SKIP   0xf
	u8 type;
	u8 strap;
	u8 group;
पूर्ण;

u32 nvbios_M0203Ee(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *hdr);
u32 nvbios_M0203Ep(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *hdr,
		   काष्ठा nvbios_M0203E *);
u32 nvbios_M0203Em(काष्ठा nvkm_bios *, u8 ramcfg, u8 *ver, u8 *hdr,
		   काष्ठा nvbios_M0203E *);
#पूर्ण_अगर
