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
#समावेश "agp.h"

#समावेश <core/option.h>
#समावेश <core/pci.h>
#समावेश <subdev/mc.h>

u32
nvkm_pci_rd32(काष्ठा nvkm_pci *pci, u16 addr)
अणु
	वापस pci->func->rd32(pci, addr);
पूर्ण

व्योम
nvkm_pci_wr08(काष्ठा nvkm_pci *pci, u16 addr, u8 data)
अणु
	pci->func->wr08(pci, addr, data);
पूर्ण

व्योम
nvkm_pci_wr32(काष्ठा nvkm_pci *pci, u16 addr, u32 data)
अणु
	pci->func->wr32(pci, addr, data);
पूर्ण

u32
nvkm_pci_mask(काष्ठा nvkm_pci *pci, u16 addr, u32 mask, u32 value)
अणु
	u32 data = pci->func->rd32(pci, addr);
	pci->func->wr32(pci, addr, (data & ~mask) | value);
	वापस data;
पूर्ण

व्योम
nvkm_pci_rom_shaकरोw(काष्ठा nvkm_pci *pci, bool shaकरोw)
अणु
	u32 data = nvkm_pci_rd32(pci, 0x0050);
	अगर (shaकरोw)
		data |=  0x00000001;
	अन्यथा
		data &= ~0x00000001;
	nvkm_pci_wr32(pci, 0x0050, data);
पूर्ण

अटल irqवापस_t
nvkm_pci_पूर्णांकr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा nvkm_pci *pci = arg;
	काष्ठा nvkm_device *device = pci->subdev.device;
	bool handled = false;

	अगर (pci->irq < 0)
		वापस IRQ_HANDLED;

	nvkm_mc_पूर्णांकr_unarm(device);
	अगर (pci->msi)
		pci->func->msi_rearm(pci);
	nvkm_mc_पूर्णांकr(device, &handled);
	nvkm_mc_पूर्णांकr_rearm(device);
	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक
nvkm_pci_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_pci *pci = nvkm_pci(subdev);

	अगर (pci->agp.bridge)
		nvkm_agp_fini(pci);

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_pci_preinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_pci *pci = nvkm_pci(subdev);
	अगर (pci->agp.bridge)
		nvkm_agp_preinit(pci);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_pci_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_pci *pci = nvkm_pci(subdev);
	काष्ठा pci_dev *pdev = pci->pdev;
	पूर्णांक ret;

	अगर (pci_is_pcie(pci->pdev)) अणु
		ret = nvkm_pcie_oneinit(pci);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = request_irq(pdev->irq, nvkm_pci_पूर्णांकr, IRQF_SHARED, "nvkm", pci);
	अगर (ret)
		वापस ret;

	pci->irq = pdev->irq;
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_pci_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_pci *pci = nvkm_pci(subdev);
	पूर्णांक ret;

	अगर (pci->agp.bridge) अणु
		ret = nvkm_agp_init(pci);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (pci_is_pcie(pci->pdev)) अणु
		nvkm_pcie_init(pci);
	पूर्ण

	अगर (pci->func->init)
		pci->func->init(pci);

	/* Ensure MSI पूर्णांकerrupts are armed, क्रम the हाल where there are
	 * alपढ़ोy पूर्णांकerrupts pending (क्रम whatever reason) at load समय.
	 */
	अगर (pci->msi)
		pci->func->msi_rearm(pci);

	वापस 0;
पूर्ण

अटल व्योम *
nvkm_pci_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_pci *pci = nvkm_pci(subdev);

	nvkm_agp_dtor(pci);

	अगर (pci->irq >= 0) अणु
		/* freq_irq() will call the handler, we use pci->irq == -1
		 * to संकेत that it's been torn करोwn and should be a noop.
		 */
		पूर्णांक irq = pci->irq;
		pci->irq = -1;
		मुक्त_irq(irq, pci);
	पूर्ण

	अगर (pci->msi)
		pci_disable_msi(pci->pdev);

	वापस nvkm_pci(subdev);
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_pci_func = अणु
	.dtor = nvkm_pci_dtor,
	.oneinit = nvkm_pci_oneinit,
	.preinit = nvkm_pci_preinit,
	.init = nvkm_pci_init,
	.fini = nvkm_pci_fini,
पूर्ण;

पूर्णांक
nvkm_pci_new_(स्थिर काष्ठा nvkm_pci_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pci **ppci)
अणु
	काष्ठा nvkm_pci *pci;

	अगर (!(pci = *ppci = kzalloc(माप(**ppci), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_subdev_ctor(&nvkm_pci_func, device, type, inst, &pci->subdev);
	pci->func = func;
	pci->pdev = device->func->pci(device)->pdev;
	pci->irq = -1;
	pci->pcie.speed = -1;
	pci->pcie.width = -1;

	अगर (device->type == NVKM_DEVICE_AGP)
		nvkm_agp_ctor(pci);

	चयन (pci->pdev->device & 0x0ff0) अणु
	हाल 0x00f0:
	हाल 0x02e0:
		/* BR02? NFI how these would be handled yet exactly */
		अवरोध;
	शेष:
		चयन (device->chipset) अणु
		हाल 0xaa:
			/* reported broken, nv also disable it */
			अवरोध;
		शेष:
			pci->msi = true;
			अवरोध;
		पूर्ण
	पूर्ण

#अगर_घोषित __BIG_ENDIAN
	pci->msi = false;
#पूर्ण_अगर

	pci->msi = nvkm_boolopt(device->cfgopt, "NvMSI", pci->msi);
	अगर (pci->msi && func->msi_rearm) अणु
		pci->msi = pci_enable_msi(pci->pdev) == 0;
		अगर (pci->msi)
			nvkm_debug(&pci->subdev, "MSI enabled\n");
	पूर्ण अन्यथा अणु
		pci->msi = false;
	पूर्ण

	वापस 0;
पूर्ण
