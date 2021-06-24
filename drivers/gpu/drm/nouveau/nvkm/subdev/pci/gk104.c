<शैली गुरु>
/*
 * Copyright 2015 Karol Herbst <nouveau@karolherbst.de>
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
 * Authors: Karol Herbst <nouveau@karolherbst.de>
 */
#समावेश "priv.h"

अटल पूर्णांक
gk104_pcie_version_supported(काष्ठा nvkm_pci *pci)
अणु
	वापस (nvkm_rd32(pci->subdev.device, 0x8c1c0) & 0x4) == 0x4 ? 2 : 1;
पूर्ण

अटल व्योम
gk104_pcie_set_cap_speed(काष्ठा nvkm_pci *pci, क्रमागत nvkm_pcie_speed speed)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;

	चयन (speed) अणु
	हाल NVKM_PCIE_SPEED_2_5:
		gf100_pcie_set_cap_speed(pci, false);
		nvkm_mask(device, 0x8c1c0, 0x30000, 0x10000);
		अवरोध;
	हाल NVKM_PCIE_SPEED_5_0:
		gf100_pcie_set_cap_speed(pci, true);
		nvkm_mask(device, 0x8c1c0, 0x30000, 0x20000);
		अवरोध;
	हाल NVKM_PCIE_SPEED_8_0:
		gf100_pcie_set_cap_speed(pci, true);
		nvkm_mask(device, 0x8c1c0, 0x30000, 0x30000);
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत nvkm_pcie_speed
gk104_pcie_cap_speed(काष्ठा nvkm_pci *pci)
अणु
	पूर्णांक speed = gf100_pcie_cap_speed(pci);

	अगर (speed == 0)
		वापस NVKM_PCIE_SPEED_2_5;

	अगर (speed >= 1) अणु
		पूर्णांक speed2 = nvkm_rd32(pci->subdev.device, 0x8c1c0) & 0x30000;
		चयन (speed2) अणु
		हाल 0x00000:
		हाल 0x10000:
			वापस NVKM_PCIE_SPEED_2_5;
		हाल 0x20000:
			वापस NVKM_PCIE_SPEED_5_0;
		हाल 0x30000:
			वापस NVKM_PCIE_SPEED_8_0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम
gk104_pcie_set_lnkctl_speed(काष्ठा nvkm_pci *pci, क्रमागत nvkm_pcie_speed speed)
अणु
	u8 reg_v = 0;
	चयन (speed) अणु
	हाल NVKM_PCIE_SPEED_2_5:
		reg_v = 1;
		अवरोध;
	हाल NVKM_PCIE_SPEED_5_0:
		reg_v = 2;
		अवरोध;
	हाल NVKM_PCIE_SPEED_8_0:
		reg_v = 3;
		अवरोध;
	पूर्ण
	nvkm_pci_mask(pci, 0xa8, 0x3, reg_v);
पूर्ण

अटल क्रमागत nvkm_pcie_speed
gk104_pcie_lnkctl_speed(काष्ठा nvkm_pci *pci)
अणु
	u8 reg_v = nvkm_pci_rd32(pci, 0xa8) & 0x3;
	चयन (reg_v) अणु
	हाल 0:
	हाल 1:
		वापस NVKM_PCIE_SPEED_2_5;
	हाल 2:
		वापस NVKM_PCIE_SPEED_5_0;
	हाल 3:
		वापस NVKM_PCIE_SPEED_8_0;
	पूर्ण
	वापस -1;
पूर्ण

अटल क्रमागत nvkm_pcie_speed
gk104_pcie_max_speed(काष्ठा nvkm_pci *pci)
अणु
	u32 max_speed = nvkm_rd32(pci->subdev.device, 0x8c1c0) & 0x300000;
	चयन (max_speed) अणु
	हाल 0x000000:
		वापस NVKM_PCIE_SPEED_8_0;
	हाल 0x100000:
		वापस NVKM_PCIE_SPEED_5_0;
	हाल 0x200000:
		वापस NVKM_PCIE_SPEED_2_5;
	पूर्ण
	वापस NVKM_PCIE_SPEED_2_5;
पूर्ण

अटल व्योम
gk104_pcie_set_link_speed(काष्ठा nvkm_pci *pci, क्रमागत nvkm_pcie_speed speed)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	u32 mask_value;

	चयन (speed) अणु
	हाल NVKM_PCIE_SPEED_8_0:
		mask_value = 0x00000;
		अवरोध;
	हाल NVKM_PCIE_SPEED_5_0:
		mask_value = 0x40000;
		अवरोध;
	हाल NVKM_PCIE_SPEED_2_5:
	शेष:
		mask_value = 0x80000;
		अवरोध;
	पूर्ण

	nvkm_mask(device, 0x8c040, 0xc0000, mask_value);
	nvkm_mask(device, 0x8c040, 0x1, 0x1);
पूर्ण

अटल पूर्णांक
gk104_pcie_init(काष्ठा nvkm_pci * pci)
अणु
	क्रमागत nvkm_pcie_speed lnkctl_speed, max_speed, cap_speed;
	काष्ठा nvkm_subdev *subdev = &pci->subdev;

	अगर (gf100_pcie_version(pci) < 2)
		वापस 0;

	lnkctl_speed = gk104_pcie_lnkctl_speed(pci);
	max_speed = gk104_pcie_max_speed(pci);
	cap_speed = gk104_pcie_cap_speed(pci);

	अगर (cap_speed != max_speed) अणु
		nvkm_trace(subdev, "adjusting cap to max speed\n");
		gk104_pcie_set_cap_speed(pci, max_speed);
		cap_speed = gk104_pcie_cap_speed(pci);
		अगर (cap_speed != max_speed)
			nvkm_warn(subdev, "failed to adjust cap speed\n");
	पूर्ण

	अगर (lnkctl_speed != max_speed) अणु
		nvkm_debug(subdev, "adjusting lnkctl to max speed\n");
		gk104_pcie_set_lnkctl_speed(pci, max_speed);
		lnkctl_speed = gk104_pcie_lnkctl_speed(pci);
		अगर (lnkctl_speed != max_speed)
			nvkm_error(subdev, "failed to adjust lnkctl speed\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
gk104_pcie_set_link(काष्ठा nvkm_pci *pci, क्रमागत nvkm_pcie_speed speed, u8 width)
अणु
	काष्ठा nvkm_subdev *subdev = &pci->subdev;
	क्रमागत nvkm_pcie_speed lnk_ctl_speed = gk104_pcie_lnkctl_speed(pci);
	क्रमागत nvkm_pcie_speed lnk_cap_speed = gk104_pcie_cap_speed(pci);

	अगर (speed > lnk_cap_speed) अणु
		speed = lnk_cap_speed;
		nvkm_warn(subdev, "dropping requested speed due too low cap"
			  " speed\n");
	पूर्ण

	अगर (speed > lnk_ctl_speed) अणु
		speed = lnk_ctl_speed;
		nvkm_warn(subdev, "dropping requested speed due too low"
			  " lnkctl speed\n");
	पूर्ण

	gk104_pcie_set_link_speed(pci, speed);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा nvkm_pci_func
gk104_pci_func = अणु
	.init = g84_pci_init,
	.rd32 = nv40_pci_rd32,
	.wr08 = nv40_pci_wr08,
	.wr32 = nv40_pci_wr32,
	.msi_rearm = nv40_pci_msi_rearm,

	.pcie.init = gk104_pcie_init,
	.pcie.set_link = gk104_pcie_set_link,

	.pcie.max_speed = gk104_pcie_max_speed,
	.pcie.cur_speed = g84_pcie_cur_speed,

	.pcie.set_version = gf100_pcie_set_version,
	.pcie.version = gf100_pcie_version,
	.pcie.version_supported = gk104_pcie_version_supported,
पूर्ण;

पूर्णांक
gk104_pci_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_pci **ppci)
अणु
	वापस nvkm_pci_new_(&gk104_pci_func, device, type, inst, ppci);
पूर्ण
