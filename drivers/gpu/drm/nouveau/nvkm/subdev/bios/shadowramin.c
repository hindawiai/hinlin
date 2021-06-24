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

काष्ठा priv अणु
	काष्ठा nvkm_bios *bios;
	u32 bar0;
पूर्ण;

अटल u32
pramin_पढ़ो(व्योम *data, u32 offset, u32 length, काष्ठा nvkm_bios *bios)
अणु
	काष्ठा nvkm_device *device = bios->subdev.device;
	u32 i;
	अगर (offset + length <= 0x00100000) अणु
		क्रम (i = offset; i < offset + length; i += 4)
			*(u32 *)&bios->data[i] = nvkm_rd32(device, 0x700000 + i);
		वापस length;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
pramin_fini(व्योम *data)
अणु
	काष्ठा priv *priv = data;
	अगर (priv) अणु
		काष्ठा nvkm_device *device = priv->bios->subdev.device;
		nvkm_wr32(device, 0x001700, priv->bar0);
		kमुक्त(priv);
	पूर्ण
पूर्ण

अटल व्योम *
pramin_init(काष्ठा nvkm_bios *bios, स्थिर अक्षर *name)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा priv *priv = शून्य;
	u64 addr = 0;

	/* PRAMIN always potentially available prior to nv50 */
	अगर (device->card_type < NV_50)
		वापस शून्य;

	/* we can't get the bios image poपूर्णांकer without PDISP */
	अगर (device->card_type >= GA100)
		addr = device->chipset == 0x170; /*XXX: find the fuse reg क्रम this */
	अन्यथा
	अगर (device->card_type >= GM100)
		addr = nvkm_rd32(device, 0x021c04);
	अन्यथा
	अगर (device->card_type >= NV_C0)
		addr = nvkm_rd32(device, 0x022500);
	अगर (addr & 0x00000001) अणु
		nvkm_debug(subdev, "... display disabled\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	/* check that the winकरोw is enabled and in vram, particularly
	 * important as we करोn't want to be touching vram on an
	 * uninitialised board
	 */
	अगर (device->card_type >= GV100)
		addr = nvkm_rd32(device, 0x625f04);
	अन्यथा
		addr = nvkm_rd32(device, 0x619f04);
	अगर (!(addr & 0x00000008)) अणु
		nvkm_debug(subdev, "... not enabled\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	अगर ( (addr & 0x00000003) != 1) अणु
		nvkm_debug(subdev, "... not in vram\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	/* some alternate method inherited from xf86-video-nv... */
	addr = (addr & 0xffffff00) << 8;
	अगर (!addr) अणु
		addr  = (u64)nvkm_rd32(device, 0x001700) << 16;
		addr += 0xf0000;
	पूर्ण

	/* modअगरy bar0 PRAMIN winकरोw to cover the bios image */
	अगर (!(priv = kदो_स्मृति(माप(*priv), GFP_KERNEL))) अणु
		nvkm_error(subdev, "... out of memory\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	priv->bios = bios;
	priv->bar0 = nvkm_rd32(device, 0x001700);
	nvkm_wr32(device, 0x001700, addr >> 16);
	वापस priv;
पूर्ण

स्थिर काष्ठा nvbios_source
nvbios_ramin = अणु
	.name = "PRAMIN",
	.init = pramin_init,
	.fini = pramin_fini,
	.पढ़ो = pramin_पढ़ो,
	.rw = true,
पूर्ण;
