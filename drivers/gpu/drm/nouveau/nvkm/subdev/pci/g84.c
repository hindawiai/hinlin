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

#समावेश <core/pci.h>

अटल पूर्णांक
g84_pcie_version_supported(काष्ठा nvkm_pci *pci)
अणु
	/* g84 and g86 report wrong inक्रमmation about what they support */
	वापस 1;
पूर्ण

पूर्णांक
g84_pcie_version(काष्ठा nvkm_pci *pci)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	वापस (nvkm_rd32(device, 0x00154c) & 0x1) + 1;
पूर्ण

व्योम
g84_pcie_set_version(काष्ठा nvkm_pci *pci, u8 ver)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	nvkm_mask(device, 0x00154c, 0x1, (ver >= 2 ? 0x1 : 0x0));
पूर्ण

अटल व्योम
g84_pcie_set_cap_speed(काष्ठा nvkm_pci *pci, bool full_speed)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	nvkm_mask(device, 0x00154c, 0x80, full_speed ? 0x80 : 0x0);
पूर्ण

क्रमागत nvkm_pcie_speed
g84_pcie_cur_speed(काष्ठा nvkm_pci *pci)
अणु
	u32 reg_v = nvkm_pci_rd32(pci, 0x88) & 0x30000;
	चयन (reg_v) अणु
	हाल 0x30000:
		वापस NVKM_PCIE_SPEED_8_0;
	हाल 0x20000:
		वापस NVKM_PCIE_SPEED_5_0;
	हाल 0x10000:
	शेष:
		वापस NVKM_PCIE_SPEED_2_5;
	पूर्ण
पूर्ण

क्रमागत nvkm_pcie_speed
g84_pcie_max_speed(काष्ठा nvkm_pci *pci)
अणु
	u32 reg_v = nvkm_pci_rd32(pci, 0x460) & 0x3300;
	अगर (reg_v == 0x2200)
		वापस NVKM_PCIE_SPEED_5_0;
	वापस NVKM_PCIE_SPEED_2_5;
पूर्ण

व्योम
g84_pcie_set_link_speed(काष्ठा nvkm_pci *pci, क्रमागत nvkm_pcie_speed speed)
अणु
	u32 mask_value;

	अगर (speed == NVKM_PCIE_SPEED_5_0)
		mask_value = 0x20;
	अन्यथा
		mask_value = 0x10;

	nvkm_pci_mask(pci, 0x460, 0x30, mask_value);
	nvkm_pci_mask(pci, 0x460, 0x1, 0x1);
पूर्ण

पूर्णांक
g84_pcie_set_link(काष्ठा nvkm_pci *pci, क्रमागत nvkm_pcie_speed speed, u8 width)
अणु
	g84_pcie_set_cap_speed(pci, speed == NVKM_PCIE_SPEED_5_0);
	g84_pcie_set_link_speed(pci, speed);
	वापस 0;
पूर्ण

व्योम
g84_pci_init(काष्ठा nvkm_pci *pci)
अणु
	/* The following only concerns PCIe cards. */
	अगर (!pci_is_pcie(pci->pdev))
		वापस;

	/* Tag field is 8-bit दीर्घ, regardless of EXT_TAG.
	 * However, अगर EXT_TAG is disabled, only the lower 5 bits of the tag
	 * field should be used, limiting the number of request to 32.
	 *
	 * Apparently, 0x041c stores some limit on the number of requests
	 * possible, so अगर EXT_TAG is disabled, limit that requests number to
	 * 32
	 *
	 * Fixes fकरो#86537
	 */
	अगर (nvkm_pci_rd32(pci, 0x007c) & 0x00000020)
		nvkm_pci_mask(pci, 0x0080, 0x00000100, 0x00000100);
	अन्यथा
		nvkm_pci_mask(pci, 0x041c, 0x00000060, 0x00000000);
पूर्ण

पूर्णांक
g84_pcie_init(काष्ठा nvkm_pci *pci)
अणु
	bool full_speed = g84_pcie_cur_speed(pci) == NVKM_PCIE_SPEED_5_0;
	g84_pcie_set_cap_speed(pci, full_speed);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_pci_func
g84_pci_func = अणु
	.init = g84_pci_init,
	.rd32 = nv40_pci_rd32,
	.wr08 = nv40_pci_wr08,
	.wr32 = nv40_pci_wr32,
	.msi_rearm = nv46_pci_msi_rearm,

	.pcie.init = g84_pcie_init,
	.pcie.set_link = g84_pcie_set_link,

	.pcie.max_speed = g84_pcie_max_speed,
	.pcie.cur_speed = g84_pcie_cur_speed,

	.pcie.set_version = g84_pcie_set_version,
	.pcie.version = g84_pcie_version,
	.pcie.version_supported = g84_pcie_version_supported,
पूर्ण;

पूर्णांक
g84_pci_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	    काष्ठा nvkm_pci **ppci)
अणु
	वापस nvkm_pci_new_(&g84_pci_func, device, type, inst, ppci);
पूर्ण
