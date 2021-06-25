<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_M0205_H__
#घोषणा __NVBIOS_M0205_H__
काष्ठा nvbios_M0205T अणु
	u16 freq;
पूर्ण;

u32 nvbios_M0205Te(काष्ठा nvkm_bios *,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *snr, u8 *ssz);
u32 nvbios_M0205Tp(काष्ठा nvkm_bios *,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *snr, u8 *ssz,
		   काष्ठा nvbios_M0205T *);

काष्ठा nvbios_M0205E अणु
	u8 type;
पूर्ण;

u32 nvbios_M0205Ee(काष्ठा nvkm_bios *, पूर्णांक idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u32 nvbios_M0205Ep(काष्ठा nvkm_bios *, पूर्णांक idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_M0205E *);

काष्ठा nvbios_M0205S अणु
	u8 data;
पूर्ण;

u32 nvbios_M0205Se(काष्ठा nvkm_bios *, पूर्णांक ent, पूर्णांक idx, u8 *ver, u8 *hdr);
u32 nvbios_M0205Sp(काष्ठा nvkm_bios *, पूर्णांक ent, पूर्णांक idx, u8 *ver, u8 *hdr,
		   काष्ठा nvbios_M0205S *);
#पूर्ण_अगर
