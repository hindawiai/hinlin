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
#समावेश <subdev/vga.h>

u8
nvkm_rdport(काष्ठा nvkm_device *device, पूर्णांक head, u16 port)
अणु
	अगर (device->card_type >= NV_50)
		वापस nvkm_rd08(device, 0x601000 + port);

	अगर (port == 0x03c0 || port == 0x03c1 ||	/* AR */
	    port == 0x03c2 || port == 0x03da ||	/* INP0 */
	    port == 0x03d4 || port == 0x03d5)	/* CR */
		वापस nvkm_rd08(device, 0x601000 + (head * 0x2000) + port);

	अगर (port == 0x03c2 || port == 0x03cc ||	/* MISC */
	    port == 0x03c4 || port == 0x03c5 ||	/* SR */
	    port == 0x03ce || port == 0x03cf) अणु	/* GR */
		अगर (device->card_type < NV_40)
			head = 0; /* CR44 selects head */
		वापस nvkm_rd08(device, 0x0c0000 + (head * 0x2000) + port);
	पूर्ण

	वापस 0x00;
पूर्ण

व्योम
nvkm_wrport(काष्ठा nvkm_device *device, पूर्णांक head, u16 port, u8 data)
अणु
	अगर (device->card_type >= NV_50)
		nvkm_wr08(device, 0x601000 + port, data);
	अन्यथा
	अगर (port == 0x03c0 || port == 0x03c1 ||	/* AR */
	    port == 0x03c2 || port == 0x03da ||	/* INP0 */
	    port == 0x03d4 || port == 0x03d5)	/* CR */
		nvkm_wr08(device, 0x601000 + (head * 0x2000) + port, data);
	अन्यथा
	अगर (port == 0x03c2 || port == 0x03cc ||	/* MISC */
	    port == 0x03c4 || port == 0x03c5 ||	/* SR */
	    port == 0x03ce || port == 0x03cf) अणु	/* GR */
		अगर (device->card_type < NV_40)
			head = 0; /* CR44 selects head */
		nvkm_wr08(device, 0x0c0000 + (head * 0x2000) + port, data);
	पूर्ण
पूर्ण

u8
nvkm_rdvgas(काष्ठा nvkm_device *device, पूर्णांक head, u8 index)
अणु
	nvkm_wrport(device, head, 0x03c4, index);
	वापस nvkm_rdport(device, head, 0x03c5);
पूर्ण

व्योम
nvkm_wrvgas(काष्ठा nvkm_device *device, पूर्णांक head, u8 index, u8 value)
अणु
	nvkm_wrport(device, head, 0x03c4, index);
	nvkm_wrport(device, head, 0x03c5, value);
पूर्ण

u8
nvkm_rdvgag(काष्ठा nvkm_device *device, पूर्णांक head, u8 index)
अणु
	nvkm_wrport(device, head, 0x03ce, index);
	वापस nvkm_rdport(device, head, 0x03cf);
पूर्ण

व्योम
nvkm_wrvgag(काष्ठा nvkm_device *device, पूर्णांक head, u8 index, u8 value)
अणु
	nvkm_wrport(device, head, 0x03ce, index);
	nvkm_wrport(device, head, 0x03cf, value);
पूर्ण

u8
nvkm_rdvgac(काष्ठा nvkm_device *device, पूर्णांक head, u8 index)
अणु
	nvkm_wrport(device, head, 0x03d4, index);
	वापस nvkm_rdport(device, head, 0x03d5);
पूर्ण

व्योम
nvkm_wrvgac(काष्ठा nvkm_device *device, पूर्णांक head, u8 index, u8 value)
अणु
	nvkm_wrport(device, head, 0x03d4, index);
	nvkm_wrport(device, head, 0x03d5, value);
पूर्ण

u8
nvkm_rdvgai(काष्ठा nvkm_device *device, पूर्णांक head, u16 port, u8 index)
अणु
	अगर (port == 0x03c4) वापस nvkm_rdvgas(device, head, index);
	अगर (port == 0x03ce) वापस nvkm_rdvgag(device, head, index);
	अगर (port == 0x03d4) वापस nvkm_rdvgac(device, head, index);
	वापस 0x00;
पूर्ण

व्योम
nvkm_wrvgai(काष्ठा nvkm_device *device, पूर्णांक head, u16 port, u8 index, u8 value)
अणु
	अगर      (port == 0x03c4) nvkm_wrvgas(device, head, index, value);
	अन्यथा अगर (port == 0x03ce) nvkm_wrvgag(device, head, index, value);
	अन्यथा अगर (port == 0x03d4) nvkm_wrvgac(device, head, index, value);
पूर्ण

bool
nvkm_lockvgac(काष्ठा nvkm_device *device, bool lock)
अणु
	bool locked = !nvkm_rdvgac(device, 0, 0x1f);
	u8 data = lock ? 0x99 : 0x57;
	अगर (device->card_type < NV_50)
		nvkm_wrvgac(device, 0, 0x1f, data);
	अन्यथा
		nvkm_wrvgac(device, 0, 0x3f, data);
	अगर (device->chipset == 0x11) अणु
		अगर (!(nvkm_rd32(device, 0x001084) & 0x10000000))
			nvkm_wrvgac(device, 1, 0x1f, data);
	पूर्ण
	वापस locked;
पूर्ण

/* CR44 takes values 0 (head A), 3 (head B) and 4 (heads tied)
 * it affects only the 8 bit vga io regs, which we access using mmio at
 * 0xcअणु0,2पूर्ण3c*, 0x60अणु1,3पूर्ण3*, and 0x68अणु1,3पूर्ण3d*
 * in general, the set value of cr44 करोes not matter: reg access works as
 * expected and values can be set क्रम the appropriate head by using a 0x2000
 * offset as required
 * however:
 * a) pre nv40, the head B range of PRMVIO regs at 0xc23c* was not exposed and
 *    cr44 must be set to 0 or 3 क्रम accessing values on the correct head
 *    through the common 0xc03c* addresses
 * b) in tied mode (4) head B is programmed to the values set on head A, and
 *    access using the head B addresses can have strange results, ergo we leave
 *    tied mode in init once we know to what cr44 should be restored on निकास
 *
 * the owner parameter is slightly abused:
 * 0 and 1 are treated as head values and so the set value is (owner * 3)
 * other values are treated as literal values to set
 */
u8
nvkm_rdvgaowner(काष्ठा nvkm_device *device)
अणु
	अगर (device->card_type < NV_50) अणु
		अगर (device->chipset == 0x11) अणु
			u32 tied = nvkm_rd32(device, 0x001084) & 0x10000000;
			अगर (tied == 0) अणु
				u8 slA = nvkm_rdvgac(device, 0, 0x28) & 0x80;
				u8 tvA = nvkm_rdvgac(device, 0, 0x33) & 0x01;
				u8 slB = nvkm_rdvgac(device, 1, 0x28) & 0x80;
				u8 tvB = nvkm_rdvgac(device, 1, 0x33) & 0x01;
				अगर (slA && !tvA) वापस 0x00;
				अगर (slB && !tvB) वापस 0x03;
				अगर (slA) वापस 0x00;
				अगर (slB) वापस 0x03;
				वापस 0x00;
			पूर्ण
			वापस 0x04;
		पूर्ण

		वापस nvkm_rdvgac(device, 0, 0x44);
	पूर्ण

	वापस 0x00;
पूर्ण

व्योम
nvkm_wrvgaowner(काष्ठा nvkm_device *device, u8 select)
अणु
	अगर (device->card_type < NV_50) अणु
		u8 owner = (select == 1) ? 3 : select;
		अगर (device->chipset == 0x11) अणु
			/* workaround hw lockup bug */
			nvkm_rdvgac(device, 0, 0x1f);
			nvkm_rdvgac(device, 1, 0x1f);
		पूर्ण

		nvkm_wrvgac(device, 0, 0x44, owner);

		अगर (device->chipset == 0x11) अणु
			nvkm_wrvgac(device, 0, 0x2e, owner);
			nvkm_wrvgac(device, 0, 0x2e, owner);
		पूर्ण
	पूर्ण
पूर्ण
