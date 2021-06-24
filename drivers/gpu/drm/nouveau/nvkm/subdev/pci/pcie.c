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
 * Authors: Karol Herbst <git@karolherbst.de>
 */
#समावेश "priv.h"

अटल अक्षर *nvkm_pcie_speeds[] = अणु
	"2.5GT/s",
	"5.0GT/s",
	"8.0GT/s",
पूर्ण;

अटल क्रमागत nvkm_pcie_speed
nvkm_pcie_speed(क्रमागत pci_bus_speed speed)
अणु
	चयन (speed) अणु
	हाल PCIE_SPEED_2_5GT:
		वापस NVKM_PCIE_SPEED_2_5;
	हाल PCIE_SPEED_5_0GT:
		वापस NVKM_PCIE_SPEED_5_0;
	हाल PCIE_SPEED_8_0GT:
		वापस NVKM_PCIE_SPEED_8_0;
	शेष:
		/* XXX 0x16 is 8_0, assume 0x17 will be 16_0 क्रम now */
		अगर (speed == 0x17)
			वापस NVKM_PCIE_SPEED_8_0;
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_pcie_get_version(काष्ठा nvkm_pci *pci)
अणु
	अगर (!pci->func->pcie.version)
		वापस -ENOSYS;

	वापस pci->func->pcie.version(pci);
पूर्ण

अटल पूर्णांक
nvkm_pcie_get_max_version(काष्ठा nvkm_pci *pci)
अणु
	अगर (!pci->func->pcie.version_supported)
		वापस -ENOSYS;

	वापस pci->func->pcie.version_supported(pci);
पूर्ण

अटल पूर्णांक
nvkm_pcie_set_version(काष्ठा nvkm_pci *pci, पूर्णांक version)
अणु
	अगर (!pci->func->pcie.set_version)
		वापस -ENOSYS;

	nvkm_trace(&pci->subdev, "set to version %i\n", version);
	pci->func->pcie.set_version(pci, version);
	वापस nvkm_pcie_get_version(pci);
पूर्ण

पूर्णांक
nvkm_pcie_oneinit(काष्ठा nvkm_pci *pci)
अणु
	अगर (pci->func->pcie.max_speed)
		nvkm_debug(&pci->subdev, "pcie max speed: %s\n",
			   nvkm_pcie_speeds[pci->func->pcie.max_speed(pci)]);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_pcie_init(काष्ठा nvkm_pci *pci)
अणु
	काष्ठा nvkm_subdev *subdev = &pci->subdev;
	पूर्णांक ret;

	/* उठाओ pcie version first */
	ret = nvkm_pcie_get_version(pci);
	अगर (ret > 0) अणु
		पूर्णांक max_version = nvkm_pcie_get_max_version(pci);
		अगर (max_version > 0 && max_version > ret)
			ret = nvkm_pcie_set_version(pci, max_version);

		अगर (ret < max_version)
			nvkm_error(subdev, "couldn't raise version: %i\n", ret);
	पूर्ण

	अगर (pci->func->pcie.init)
		pci->func->pcie.init(pci);

	अगर (pci->pcie.speed != -1)
		nvkm_pcie_set_link(pci, pci->pcie.speed, pci->pcie.width);

	वापस 0;
पूर्ण

पूर्णांक
nvkm_pcie_set_link(काष्ठा nvkm_pci *pci, क्रमागत nvkm_pcie_speed speed, u8 width)
अणु
	काष्ठा nvkm_subdev *subdev = &pci->subdev;
	क्रमागत nvkm_pcie_speed cur_speed, max_speed;
	काष्ठा pci_bus *pbus;
	पूर्णांक ret;

	अगर (!pci || !pci_is_pcie(pci->pdev))
		वापस 0;
	pbus = pci->pdev->bus;

	अगर (!pci->func->pcie.set_link)
		वापस -ENOSYS;

	nvkm_trace(subdev, "requested %s\n", nvkm_pcie_speeds[speed]);

	अगर (pci->func->pcie.version(pci) < 2) अणु
		nvkm_error(subdev, "setting link failed due to low version\n");
		वापस -ENODEV;
	पूर्ण

	cur_speed = pci->func->pcie.cur_speed(pci);
	max_speed = min(nvkm_pcie_speed(pbus->max_bus_speed),
			pci->func->pcie.max_speed(pci));

	nvkm_trace(subdev, "current speed: %s\n", nvkm_pcie_speeds[cur_speed]);

	अगर (speed > max_speed) अणु
		nvkm_debug(subdev, "%s not supported by bus or card, dropping"
			   "requested speed to %s", nvkm_pcie_speeds[speed],
			   nvkm_pcie_speeds[max_speed]);
		speed = max_speed;
	पूर्ण

	pci->pcie.speed = speed;
	pci->pcie.width = width;

	अगर (speed == cur_speed) अणु
		nvkm_debug(subdev, "requested matches current speed\n");
		वापस speed;
	पूर्ण

	nvkm_debug(subdev, "set link to %s x%i\n",
		   nvkm_pcie_speeds[speed], width);

	ret = pci->func->pcie.set_link(pci, speed, width);
	अगर (ret < 0)
		nvkm_error(subdev, "setting link failed: %i\n", ret);

	वापस ret;
पूर्ण
