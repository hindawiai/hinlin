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

पूर्णांक
nv1a_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	काष्ठा pci_dev *bridge;
	u32 mem, mib;
	पूर्णांक करोमुख्य = 0;
	काष्ठा pci_dev *pdev = शून्य;

	अगर (dev_is_pci(fb->subdev.device->dev))
		pdev = to_pci_dev(fb->subdev.device->dev);

	अगर (pdev)
		करोमुख्य = pci_करोमुख्य_nr(pdev->bus);

	bridge = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, PCI_DEVFN(0, 1));
	अगर (!bridge) अणु
		nvkm_error(&fb->subdev, "no bridge device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (fb->subdev.device->chipset == 0x1a) अणु
		pci_पढ़ो_config_dword(bridge, 0x7c, &mem);
		mib = ((mem >> 6) & 31) + 1;
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_dword(bridge, 0x84, &mem);
		mib = ((mem >> 4) & 127) + 1;
	पूर्ण

	वापस nvkm_ram_new_(&nv04_ram_func, fb, NVKM_RAM_TYPE_STOLEN,
			     mib * 1024 * 1024, pram);
पूर्ण
