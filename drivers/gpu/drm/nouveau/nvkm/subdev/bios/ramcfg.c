<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/ramcfg.h>
#समावेश <subdev/bios/M0203.h>

अटल u8
nvbios_ramcfg_strap(काष्ठा nvkm_subdev *subdev)
अणु
	वापस (nvkm_rd32(subdev->device, 0x101000) & 0x0000003c) >> 2;
पूर्ण

u8
nvbios_ramcfg_count(काष्ठा nvkm_bios *bios)
अणु
	काष्ठा bit_entry bit_M;

	अगर (!bit_entry(bios, 'M', &bit_M)) अणु
		अगर (bit_M.version == 1 && bit_M.length >= 5)
			वापस nvbios_rd08(bios, bit_M.offset + 2);
		अगर (bit_M.version == 2 && bit_M.length >= 3)
			वापस nvbios_rd08(bios, bit_M.offset + 0);
	पूर्ण

	वापस 0x00;
पूर्ण

u8
nvbios_ramcfg_index(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	u8 strap = nvbios_ramcfg_strap(subdev);
	u32 xlat = 0x00000000;
	काष्ठा bit_entry bit_M;
	काष्ठा nvbios_M0203E M0203E;
	u8 ver, hdr;

	अगर (!bit_entry(bios, 'M', &bit_M)) अणु
		अगर (bit_M.version == 1 && bit_M.length >= 5)
			xlat = nvbios_rd16(bios, bit_M.offset + 3);
		अगर (bit_M.version == 2 && bit_M.length >= 3) अणु
			/*XXX: is M ever लघुer than this?
			 *     अगर not - what is xlat used क्रम now?
			 *     also - sigh..
			 */
			अगर (bit_M.length >= 7 &&
			    nvbios_M0203Em(bios, strap, &ver, &hdr, &M0203E))
				वापस M0203E.group;
			xlat = nvbios_rd16(bios, bit_M.offset + 1);
		पूर्ण
	पूर्ण

	अगर (xlat)
		strap = nvbios_rd08(bios, xlat + strap);
	वापस strap;
पूर्ण
