<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_RAMMAP_H__
#घोषणा __NVBIOS_RAMMAP_H__
#समावेश <subdev/bios/ramcfg.h>

u32 nvbios_rammapTe(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr,
		    u8 *cnt, u8 *len, u8 *snr, u8 *ssz);

u32 nvbios_rammapEe(काष्ठा nvkm_bios *, पूर्णांक idx,
		    u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u32 nvbios_rammapEp_from_perf(काष्ठा nvkm_bios *bios, u32 data, u8 size,
		    काष्ठा nvbios_ramcfg *p);
u32 nvbios_rammapEp(काष्ठा nvkm_bios *, पूर्णांक idx,
		    u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_ramcfg *);
u32 nvbios_rammapEm(काष्ठा nvkm_bios *, u16 mhz,
		    u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_ramcfg *);

u32 nvbios_rammapSe(काष्ठा nvkm_bios *, u32 data,
		    u8 ever, u8 ehdr, u8 ecnt, u8 elen, पूर्णांक idx,
		    u8 *ver, u8 *hdr);
u32 nvbios_rammapSp_from_perf(काष्ठा nvkm_bios *bios, u32 data, u8 size, पूर्णांक idx,
		    काष्ठा nvbios_ramcfg *p);
u32 nvbios_rammapSp(काष्ठा nvkm_bios *, u32 data,
		    u8 ever, u8 ehdr, u8 ecnt, u8 elen, पूर्णांक idx,
		    u8 *ver, u8 *hdr, काष्ठा nvbios_ramcfg *);
#पूर्ण_अगर
