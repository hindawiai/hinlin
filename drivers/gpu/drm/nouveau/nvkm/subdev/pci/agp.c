<शैली गुरु>
/*
 * Copyright 2015 Nouveau Project
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
 */
#समावेश "agp.h"
#अगर_घोषित __NVKM_PCI_AGP_H__
#समावेश <core/option.h>

काष्ठा nvkm_device_agp_quirk अणु
	u16 hostbridge_venकरोr;
	u16 hostbridge_device;
	u16 chip_venकरोr;
	u16 chip_device;
	पूर्णांक mode;
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_agp_quirk
nvkm_device_agp_quirks[] = अणु
	/* VIA Apollo PRO133x / GeForce FX 5600 Ultra - fकरो#20341 */
	अणु PCI_VENDOR_ID_VIA, 0x0691, PCI_VENDOR_ID_NVIDIA, 0x0311, 2 पूर्ण,
	/* SiS 761 करोes not support AGP cards, use PCI mode */
	अणु PCI_VENDOR_ID_SI, 0x0761, PCI_ANY_ID, PCI_ANY_ID, 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;

व्योम
nvkm_agp_fini(काष्ठा nvkm_pci *pci)
अणु
	अगर (pci->agp.acquired) अणु
		agp_backend_release(pci->agp.bridge);
		pci->agp.acquired = false;
	पूर्ण
पूर्ण

/* Ensure AGP controller is in a consistent state in हाल we need to
 * execute the VBIOS DEVINIT scripts.
 */
व्योम
nvkm_agp_preinit(काष्ठा nvkm_pci *pci)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	u32 mode = nvkm_pci_rd32(pci, 0x004c);
	u32 save[2];

	/* First of all, disable fast ग_लिखोs, otherwise अगर it's alपढ़ोy
	 * enabled in the AGP bridge and we disable the card's AGP
	 * controller we might be locking ourselves out of it.
	 */
	अगर ((mode | pci->agp.mode) & PCI_AGP_COMMAND_FW) अणु
		mode = pci->agp.mode & ~PCI_AGP_COMMAND_FW;
		agp_enable(pci->agp.bridge, mode);
	पूर्ण

	/* clear busmaster bit, and disable AGP */
	save[0] = nvkm_pci_rd32(pci, 0x0004);
	nvkm_pci_wr32(pci, 0x0004, save[0] & ~0x00000004);
	nvkm_pci_wr32(pci, 0x004c, 0x00000000);

	/* reset PGRAPH, PFIFO and PTIMER */
	save[1] = nvkm_mask(device, 0x000200, 0x00011100, 0x00000000);
	nvkm_mask(device, 0x000200, 0x00011100, save[1]);

	/* and restore busmaster bit (gives effect of resetting AGP) */
	nvkm_pci_wr32(pci, 0x0004, save[0]);
पूर्ण

पूर्णांक
nvkm_agp_init(काष्ठा nvkm_pci *pci)
अणु
	अगर (!agp_backend_acquire(pci->pdev)) अणु
		nvkm_error(&pci->subdev, "failed to acquire agp\n");
		वापस -ENODEV;
	पूर्ण

	agp_enable(pci->agp.bridge, pci->agp.mode);
	pci->agp.acquired = true;
	वापस 0;
पूर्ण

व्योम
nvkm_agp_dtor(काष्ठा nvkm_pci *pci)
अणु
	arch_phys_wc_del(pci->agp.mtrr);
पूर्ण

व्योम
nvkm_agp_ctor(काष्ठा nvkm_pci *pci)
अणु
	स्थिर काष्ठा nvkm_device_agp_quirk *quirk = nvkm_device_agp_quirks;
	काष्ठा nvkm_subdev *subdev = &pci->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा agp_kern_info info;
	पूर्णांक mode = -1;

#अगर_घोषित __घातerpc__
	/* Disable AGP by शेष on all PowerPC machines क्रम now -- At
	 * least some UniNorth-2 AGP bridges are known to be broken:
	 * DMA from the host to the card works just fine, but ग_लिखोback
	 * from the card to the host goes straight to memory
	 * untranslated bypassing that GATT somehow, making them quite
	 * painful to deal with...
	 */
	mode = 0;
#पूर्ण_अगर
	mode = nvkm_दीर्घopt(device->cfgopt, "NvAGP", mode);

	/* acquire bridge temporarily, so that we can copy its info */
	अगर (!(pci->agp.bridge = agp_backend_acquire(pci->pdev))) अणु
		nvkm_warn(subdev, "failed to acquire agp\n");
		वापस;
	पूर्ण
	agp_copy_info(pci->agp.bridge, &info);
	agp_backend_release(pci->agp.bridge);

	pci->agp.mode = info.mode;
	pci->agp.base = info.aper_base;
	pci->agp.size = info.aper_size * 1024 * 1024;
	pci->agp.cma  = info.cant_use_aperture;
	pci->agp.mtrr = -1;

	/* determine अगर bridge + chipset combination needs a workaround */
	जबतक (quirk->hostbridge_venकरोr) अणु
		अगर (info.device->venकरोr == quirk->hostbridge_venकरोr &&
		    info.device->device == quirk->hostbridge_device &&
		    (quirk->chip_venकरोr == (u16)PCI_ANY_ID ||
		    pci->pdev->venकरोr == quirk->chip_venकरोr) &&
		    (quirk->chip_device == (u16)PCI_ANY_ID ||
		    pci->pdev->device == quirk->chip_device)) अणु
			nvkm_info(subdev, "forcing default agp mode to %dX, "
					  "use NvAGP=<mode> to override\n",
				  quirk->mode);
			mode = quirk->mode;
			अवरोध;
		पूर्ण
		quirk++;
	पूर्ण

	/* apply quirk / user-specअगरied mode */
	अगर (mode >= 1) अणु
		अगर (pci->agp.mode & 0x00000008)
			mode /= 4; /* AGPv3 */
		pci->agp.mode &= ~0x00000007;
		pci->agp.mode |= (mode & 0x7);
	पूर्ण अन्यथा
	अगर (mode == 0) अणु
		pci->agp.bridge = शून्य;
		वापस;
	पूर्ण

	/* fast ग_लिखोs appear to be broken on nv18, they make the card
	 * lock up अक्रमomly.
	 */
	अगर (device->chipset == 0x18)
		pci->agp.mode &= ~PCI_AGP_COMMAND_FW;

	pci->agp.mtrr = arch_phys_wc_add(pci->agp.base, pci->agp.size);
पूर्ण
#पूर्ण_अगर
