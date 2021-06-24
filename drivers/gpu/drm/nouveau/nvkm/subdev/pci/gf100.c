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

अटल व्योम
gf100_pci_msi_rearm(काष्ठा nvkm_pci *pci)
अणु
	nvkm_pci_wr08(pci, 0x0704, 0xff);
पूर्ण

व्योम
gf100_pcie_set_version(काष्ठा nvkm_pci *pci, u8 ver)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	nvkm_mask(device, 0x02241c, 0x1, ver > 1 ? 1 : 0);
पूर्ण

पूर्णांक
gf100_pcie_version(काष्ठा nvkm_pci *pci)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	वापस (nvkm_rd32(device, 0x02241c) & 0x1) + 1;
पूर्ण

व्योम
gf100_pcie_set_cap_speed(काष्ठा nvkm_pci *pci, bool full_speed)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	nvkm_mask(device, 0x02241c, 0x80, full_speed ? 0x80 : 0x0);
पूर्ण

पूर्णांक
gf100_pcie_cap_speed(काष्ठा nvkm_pci *pci)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	u8 punits_pci_cap_speed = nvkm_rd32(device, 0x02241c) & 0x80;
	अगर (punits_pci_cap_speed == 0x80)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक
gf100_pcie_init(काष्ठा nvkm_pci *pci)
अणु
	bool full_speed = g84_pcie_cur_speed(pci) == NVKM_PCIE_SPEED_5_0;
	gf100_pcie_set_cap_speed(pci, full_speed);
	वापस 0;
पूर्ण

पूर्णांक
gf100_pcie_set_link(काष्ठा nvkm_pci *pci, क्रमागत nvkm_pcie_speed speed, u8 width)
अणु
	gf100_pcie_set_cap_speed(pci, speed == NVKM_PCIE_SPEED_5_0);
	g84_pcie_set_link_speed(pci, speed);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_pci_func
gf100_pci_func = अणु
	.init = g84_pci_init,
	.rd32 = nv40_pci_rd32,
	.wr08 = nv40_pci_wr08,
	.wr32 = nv40_pci_wr32,
	.msi_rearm = gf100_pci_msi_rearm,

	.pcie.init = gf100_pcie_init,
	.pcie.set_link = gf100_pcie_set_link,

	.pcie.max_speed = g84_pcie_max_speed,
	.pcie.cur_speed = g84_pcie_cur_speed,

	.pcie.set_version = gf100_pcie_set_version,
	.pcie.version = gf100_pcie_version,
	.pcie.version_supported = g92_pcie_version_supported,
पूर्ण;

पूर्णांक
gf100_pci_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_pci **ppci)
अणु
	वापस nvkm_pci_new_(&gf100_pci_func, device, type, inst, ppci);
पूर्ण
