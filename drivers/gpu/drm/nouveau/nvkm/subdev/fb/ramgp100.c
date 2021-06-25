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
 * Authors: Ben Skeggs
 */
#समावेश "ram.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/init.h>
#समावेश <subdev/bios/rammap.h>

अटल पूर्णांक
gp100_ram_init(काष्ठा nvkm_ram *ram)
अणु
	काष्ठा nvkm_subdev *subdev = &ram->fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_bios *bios = device->bios;
	u8  ver, hdr, cnt, len, snr, ssz;
	u32 data;
	पूर्णांक i;

	/* run a bunch of tables from rammap table.  there's actually
	 * inभागidual poपूर्णांकers क्रम each rammap entry too, but, nvidia
	 * seem to just run the last two entries' scripts early on in
	 * their init, and never again.. we'll just run 'em all once
	 * क्रम now.
	 *
	 * i strongly suspect that each script is क्रम a separate mode
	 * (likely selected by 0x9a065c's lower bits?), and the
	 * binary driver skips the one that's alपढ़ोy been setup by
	 * the init tables.
	 */
	data = nvbios_rammapTe(bios, &ver, &hdr, &cnt, &len, &snr, &ssz);
	अगर (!data || hdr < 0x15)
		वापस -EINVAL;

	cnt  = nvbios_rd08(bios, data + 0x14); /* guess at count */
	data = nvbios_rd32(bios, data + 0x10); /* guess u32... */
	अगर (cnt) अणु
		u32 save = nvkm_rd32(device, 0x9a065c) & 0x000000f0;
		क्रम (i = 0; i < cnt; i++, data += 4) अणु
			अगर (i != save >> 4) अणु
				nvkm_mask(device, 0x9a065c, 0x000000f0, i << 4);
				nvbios_init(subdev, nvbios_rd32(bios, data));
			पूर्ण
		पूर्ण
		nvkm_mask(device, 0x9a065c, 0x000000f0, save);
	पूर्ण

	nvkm_mask(device, 0x9a0584, 0x11000000, 0x00000000);
	nvkm_wr32(device, 0x10ecc0, 0xffffffff);
	nvkm_mask(device, 0x9a0160, 0x00000010, 0x00000010);
	वापस 0;
पूर्ण

अटल u32
gp100_ram_probe_fbpa(काष्ठा nvkm_device *device, पूर्णांक fbpa)
अणु
	वापस nvkm_rd32(device, 0x90020c + (fbpa * 0x4000));
पूर्ण

अटल स्थिर काष्ठा nvkm_ram_func
gp100_ram = अणु
	.upper = 0x1000000000ULL,
	.probe_fbp = gm107_ram_probe_fbp,
	.probe_fbp_amount = gm200_ram_probe_fbp_amount,
	.probe_fbpa_amount = gp100_ram_probe_fbpa,
	.init = gp100_ram_init,
पूर्ण;

पूर्णांक
gp100_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	काष्ठा nvkm_ram *ram;

	अगर (!(ram = *pram = kzalloc(माप(*ram), GFP_KERNEL)))
		वापस -ENOMEM;

	वापस gf100_ram_ctor(&gp100_ram, fb, ram);

पूर्ण
