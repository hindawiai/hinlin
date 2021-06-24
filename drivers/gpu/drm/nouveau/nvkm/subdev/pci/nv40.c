<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
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
#समावेश "priv.h"

u32
nv40_pci_rd32(काष्ठा nvkm_pci *pci, u16 addr)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	वापस nvkm_rd32(device, 0x088000 + addr);
पूर्ण

व्योम
nv40_pci_wr08(काष्ठा nvkm_pci *pci, u16 addr, u8 data)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	nvkm_wr08(device, 0x088000 + addr, data);
पूर्ण

व्योम
nv40_pci_wr32(काष्ठा nvkm_pci *pci, u16 addr, u32 data)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	nvkm_wr32(device, 0x088000 + addr, data);
पूर्ण

व्योम
nv40_pci_msi_rearm(काष्ठा nvkm_pci *pci)
अणु
	nvkm_pci_wr08(pci, 0x0068, 0xff);
पूर्ण

अटल स्थिर काष्ठा nvkm_pci_func
nv40_pci_func = अणु
	.rd32 = nv40_pci_rd32,
	.wr08 = nv40_pci_wr08,
	.wr32 = nv40_pci_wr32,
	.msi_rearm = nv40_pci_msi_rearm,
पूर्ण;

पूर्णांक
nv40_pci_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_pci **ppci)
अणु
	वापस nvkm_pci_new_(&nv40_pci_func, device, type, inst, ppci);
पूर्ण
