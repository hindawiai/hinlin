<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_VMAP_H__
#घोषणा __NVBIOS_VMAP_H__
काष्ठा nvbios_vmap अणु
	u8  max0;
	u8  max1;
	u8  max2;
पूर्ण;

u32 nvbios_vmap_table(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u32 nvbios_vmap_parse(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		      काष्ठा nvbios_vmap *);

काष्ठा nvbios_vmap_entry अणु
	u8  mode;
	u8  link;
	u32 min;
	u32 max;
	s32 arg[6];
पूर्ण;

u32 nvbios_vmap_entry(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *len);
u32 nvbios_vmap_entry_parse(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *len,
			    काष्ठा nvbios_vmap_entry *);
#पूर्ण_अगर
