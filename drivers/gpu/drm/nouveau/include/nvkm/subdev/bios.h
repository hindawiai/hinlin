<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_BIOS_H__
#घोषणा __NVKM_BIOS_H__
#समावेश <core/subdev.h>

काष्ठा nvkm_bios अणु
	काष्ठा nvkm_subdev subdev;
	u32 size;
	u8 *data;

	u32 image0_size;
	u32 imaged_addr;

	u32 bmp_offset;
	u32 bit_offset;

	काष्ठा अणु
		u8 major;
		u8 chip;
		u8 minor;
		u8 micro;
		u8 patch;
	पूर्ण version;
पूर्ण;

u8  nvbios_checksum(स्थिर u8 *data, पूर्णांक size);
u16 nvbios_findstr(स्थिर u8 *data, पूर्णांक size, स्थिर अक्षर *str, पूर्णांक len);
पूर्णांक nvbios_स_भेद(काष्ठा nvkm_bios *, u32 addr, स्थिर अक्षर *, u32 len);
u8  nvbios_rd08(काष्ठा nvkm_bios *, u32 addr);
u16 nvbios_rd16(काष्ठा nvkm_bios *, u32 addr);
u32 nvbios_rd32(काष्ठा nvkm_bios *, u32 addr);

पूर्णांक nvkm_bios_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_bios **);
#पूर्ण_अगर
