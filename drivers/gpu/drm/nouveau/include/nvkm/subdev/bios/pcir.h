<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_PCIR_H__
#घोषणा __NVBIOS_PCIR_H__
काष्ठा nvbios_pcirT अणु
	u16 venकरोr_id;
	u16 device_id;
	u8  class_code[3];
	u32 image_size;
	u16 image_rev;
	u8  image_type;
	bool last;
पूर्ण;

u32 nvbios_pcirTe(काष्ठा nvkm_bios *, u32, u8 *ver, u16 *hdr);
u32 nvbios_pcirTp(काष्ठा nvkm_bios *, u32, u8 *ver, u16 *hdr,
		  काष्ठा nvbios_pcirT *);
#पूर्ण_अगर
