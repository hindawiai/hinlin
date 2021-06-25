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
 */
#समावेश "priv.h"

#समावेश <subdev/pci.h>

अटल u32
prom_पढ़ो(व्योम *data, u32 offset, u32 length, काष्ठा nvkm_bios *bios)
अणु
	काष्ठा nvkm_device *device = data;
	u32 i;
	अगर (offset + length <= 0x00100000) अणु
		क्रम (i = offset; i < offset + length; i += 4)
			*(u32 *)&bios->data[i] = nvkm_rd32(device, 0x300000 + i);
		वापस length;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
prom_fini(व्योम *data)
अणु
	काष्ठा nvkm_device *device = data;
	nvkm_pci_rom_shaकरोw(device->pci, true);
पूर्ण

अटल व्योम *
prom_init(काष्ठा nvkm_bios *bios, स्थिर अक्षर *name)
अणु
	काष्ठा nvkm_device *device = bios->subdev.device;
	अगर (device->card_type == NV_40 && device->chipset >= 0x4c)
		वापस ERR_PTR(-ENODEV);
	nvkm_pci_rom_shaकरोw(device->pci, false);
	वापस device;
पूर्ण

स्थिर काष्ठा nvbios_source
nvbios_rom = अणु
	.name = "PROM",
	.init = prom_init,
	.fini = prom_fini,
	.पढ़ो = prom_पढ़ो,
	.rw = false,
पूर्ण;
