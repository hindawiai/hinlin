<शैली गुरु>
/*
 * Copyright 2014 Red Hat Inc.
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
#समावेश <subdev/bios/image.h>
#समावेश <subdev/bios/pcir.h>
#समावेश <subdev/bios/npde.h>

अटल bool
nvbios_imagen(काष्ठा nvkm_bios *bios, काष्ठा nvbios_image *image)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	काष्ठा nvbios_pcirT pcir;
	काष्ठा nvbios_npdeT npde;
	u8  ver;
	u16 hdr;
	u32 data;

	चयन ((data = nvbios_rd16(bios, image->base + 0x00))) अणु
	हाल 0xaa55:
	हाल 0xbb77:
	हाल 0x4e56: /* NV */
		अवरोध;
	शेष:
		nvkm_debug(subdev, "%08x: ROM signature (%04x) unknown\n",
			   image->base, data);
		वापस false;
	पूर्ण

	अगर (!(data = nvbios_pcirTp(bios, image->base, &ver, &hdr, &pcir)))
		वापस false;
	image->size = pcir.image_size;
	image->type = pcir.image_type;
	image->last = pcir.last;

	अगर (image->type != 0x70) अणु
		अगर (!(data = nvbios_npdeTp(bios, image->base, &npde)))
			वापस true;
		image->size = npde.image_size;
		image->last = npde.last;
	पूर्ण अन्यथा अणु
		image->last = true;
	पूर्ण

	वापस true;
पूर्ण

bool
nvbios_image(काष्ठा nvkm_bios *bios, पूर्णांक idx, काष्ठा nvbios_image *image)
अणु
	u32 imaged_addr = bios->imaged_addr;
	स_रखो(image, 0x00, माप(*image));
	bios->imaged_addr = 0;
	करो अणु
		image->base += image->size;
		अगर (image->last || !nvbios_imagen(bios, image)) अणु
			bios->imaged_addr = imaged_addr;
			वापस false;
		पूर्ण
	पूर्ण जबतक(idx--);
	bios->imaged_addr = imaged_addr;
	वापस true;
पूर्ण
