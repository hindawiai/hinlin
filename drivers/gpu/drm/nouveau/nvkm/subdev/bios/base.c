<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#समावेश "priv.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/bmp.h>
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/image.h>

अटल bool
nvbios_addr(काष्ठा nvkm_bios *bios, u32 *addr, u8 size)
अणु
	u32 p = *addr;

	अगर (*addr > bios->image0_size && bios->imaged_addr) अणु
		*addr -= bios->image0_size;
		*addr += bios->imaged_addr;
	पूर्ण

	अगर (unlikely(*addr + size >= bios->size)) अणु
		nvkm_error(&bios->subdev, "OOB %d %08x %08x\n", size, p, *addr);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

u8
nvbios_rd08(काष्ठा nvkm_bios *bios, u32 addr)
अणु
	अगर (likely(nvbios_addr(bios, &addr, 1)))
		वापस bios->data[addr];
	वापस 0x00;
पूर्ण

u16
nvbios_rd16(काष्ठा nvkm_bios *bios, u32 addr)
अणु
	अगर (likely(nvbios_addr(bios, &addr, 2)))
		वापस get_unaligned_le16(&bios->data[addr]);
	वापस 0x0000;
पूर्ण

u32
nvbios_rd32(काष्ठा nvkm_bios *bios, u32 addr)
अणु
	अगर (likely(nvbios_addr(bios, &addr, 4)))
		वापस get_unaligned_le32(&bios->data[addr]);
	वापस 0x00000000;
पूर्ण

u8
nvbios_checksum(स्थिर u8 *data, पूर्णांक size)
अणु
	u8 sum = 0;
	जबतक (size--)
		sum += *data++;
	वापस sum;
पूर्ण

u16
nvbios_findstr(स्थिर u8 *data, पूर्णांक size, स्थिर अक्षर *str, पूर्णांक len)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i <= (size - len); i++) अणु
		क्रम (j = 0; j < len; j++)
			अगर ((अक्षर)data[i + j] != str[j])
				अवरोध;
		अगर (j == len)
			वापस i;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nvbios_स_भेद(काष्ठा nvkm_bios *bios, u32 addr, स्थिर अक्षर *str, u32 len)
अणु
	अचिन्हित अक्षर c1, c2;

	जबतक (len--) अणु
		c1 = nvbios_rd08(bios, addr++);
		c2 = *(str++);
		अगर (c1 != c2)
			वापस c1 - c2;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
nvbios_extend(काष्ठा nvkm_bios *bios, u32 length)
अणु
	अगर (bios->size < length) अणु
		u8 *prev = bios->data;
		अगर (!(bios->data = kदो_स्मृति(length, GFP_KERNEL))) अणु
			bios->data = prev;
			वापस -ENOMEM;
		पूर्ण
		स_नकल(bios->data, prev, bios->size);
		bios->size = length;
		kमुक्त(prev);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_bios_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_bios *bios = nvkm_bios(subdev);
	kमुक्त(bios->data);
	वापस bios;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_bios = अणु
	.dtor = nvkm_bios_dtor,
पूर्ण;

पूर्णांक
nvkm_bios_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_bios **pbios)
अणु
	काष्ठा nvkm_bios *bios;
	काष्ठा nvbios_image image;
	काष्ठा bit_entry bit_i;
	पूर्णांक ret, idx = 0;

	अगर (!(bios = *pbios = kzalloc(माप(*bios), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_subdev_ctor(&nvkm_bios, device, type, inst, &bios->subdev);

	ret = nvbios_shaकरोw(bios);
	अगर (ret)
		वापस ret;

	/* Some tables have weird poपूर्णांकers that need adjusपंचांगent beक्रमe
	 * they're dereferenced.  I'm not entirely sure why...
	 */
	अगर (nvbios_image(bios, idx++, &image)) अणु
		bios->image0_size = image.size;
		जबतक (nvbios_image(bios, idx++, &image)) अणु
			अगर (image.type == 0xe0) अणु
				bios->imaged_addr = image.base;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* detect type of vbios we're dealing with */
	bios->bmp_offset = nvbios_findstr(bios->data, bios->size,
					  "\xff\x7f""NV\0", 5);
	अगर (bios->bmp_offset) अणु
		nvkm_debug(&bios->subdev, "BMP version %x.%x\n",
			   bmp_version(bios) >> 8,
			   bmp_version(bios) & 0xff);
	पूर्ण

	bios->bit_offset = nvbios_findstr(bios->data, bios->size,
					  "\xff\xb8""BIT", 5);
	अगर (bios->bit_offset)
		nvkm_debug(&bios->subdev, "BIT signature found\n");

	/* determine the vbios version number */
	अगर (!bit_entry(bios, 'i', &bit_i) && bit_i.length >= 4) अणु
		bios->version.major = nvbios_rd08(bios, bit_i.offset + 3);
		bios->version.chip  = nvbios_rd08(bios, bit_i.offset + 2);
		bios->version.minor = nvbios_rd08(bios, bit_i.offset + 1);
		bios->version.micro = nvbios_rd08(bios, bit_i.offset + 0);
		bios->version.patch = nvbios_rd08(bios, bit_i.offset + 4);
	पूर्ण अन्यथा
	अगर (bmp_version(bios)) अणु
		bios->version.major = nvbios_rd08(bios, bios->bmp_offset + 13);
		bios->version.chip  = nvbios_rd08(bios, bios->bmp_offset + 12);
		bios->version.minor = nvbios_rd08(bios, bios->bmp_offset + 11);
		bios->version.micro = nvbios_rd08(bios, bios->bmp_offset + 10);
	पूर्ण

	nvkm_info(&bios->subdev, "version %02x.%02x.%02x.%02x.%02x\n",
		  bios->version.major, bios->version.chip,
		  bios->version.minor, bios->version.micro, bios->version.patch);
	वापस 0;
पूर्ण
