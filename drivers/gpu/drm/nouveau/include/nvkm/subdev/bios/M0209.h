<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_M0209_H__
#घोषणा __NVBIOS_M0209_H__
u32 nvbios_M0209Te(काष्ठा nvkm_bios *,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *snr, u8 *ssz);

काष्ठा nvbios_M0209E अणु
	u8 v00_40;
	u8 bits;
	u8 modulo;
	u8 v02_40;
	u8 v02_07;
	u8 v03;
पूर्ण;

u32 nvbios_M0209Ee(काष्ठा nvkm_bios *, पूर्णांक idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u32 nvbios_M0209Ep(काष्ठा nvkm_bios *, पूर्णांक idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_M0209E *);

काष्ठा nvbios_M0209S अणु
	u32 data[0x200];
पूर्ण;

u32 nvbios_M0209Se(काष्ठा nvkm_bios *, पूर्णांक ent, पूर्णांक idx, u8 *ver, u8 *hdr);
u32 nvbios_M0209Sp(काष्ठा nvkm_bios *, पूर्णांक ent, पूर्णांक idx, u8 *ver, u8 *hdr,
		   काष्ठा nvbios_M0209S *);
#पूर्ण_अगर
