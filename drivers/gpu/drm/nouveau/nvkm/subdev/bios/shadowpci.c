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
 */
#समावेश "priv.h"

#समावेश <core/pci.h>

काष्ठा priv अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *rom;
	माप_प्रकार size;
पूर्ण;

अटल u32
pcirom_पढ़ो(व्योम *data, u32 offset, u32 length, काष्ठा nvkm_bios *bios)
अणु
	काष्ठा priv *priv = data;
	अगर (offset + length <= priv->size) अणु
		स_नकल_fromio(bios->data + offset, priv->rom + offset, length);
		वापस length;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
pcirom_fini(व्योम *data)
अणु
	काष्ठा priv *priv = data;
	pci_unmap_rom(priv->pdev, priv->rom);
	pci_disable_rom(priv->pdev);
	kमुक्त(priv);
पूर्ण

अटल व्योम *
pcirom_init(काष्ठा nvkm_bios *bios, स्थिर अक्षर *name)
अणु
	काष्ठा nvkm_device *device = bios->subdev.device;
	काष्ठा priv *priv = शून्य;
	काष्ठा pci_dev *pdev;
	पूर्णांक ret;

	अगर (device->func->pci)
		pdev = device->func->pci(device)->pdev;
	अन्यथा
		वापस ERR_PTR(-ENODEV);

	अगर (!(ret = pci_enable_rom(pdev))) अणु
		अगर (ret = -ENOMEM,
		    (priv = kदो_स्मृति(माप(*priv), GFP_KERNEL))) अणु
			अगर (ret = -EFAULT,
			    (priv->rom = pci_map_rom(pdev, &priv->size))) अणु
				priv->pdev = pdev;
				वापस priv;
			पूर्ण
			kमुक्त(priv);
		पूर्ण
		pci_disable_rom(pdev);
	पूर्ण

	वापस ERR_PTR(ret);
पूर्ण

स्थिर काष्ठा nvbios_source
nvbios_pcirom = अणु
	.name = "PCIROM",
	.init = pcirom_init,
	.fini = pcirom_fini,
	.पढ़ो = pcirom_पढ़ो,
	.rw = true,
पूर्ण;

अटल व्योम *
platक्रमm_init(काष्ठा nvkm_bios *bios, स्थिर अक्षर *name)
अणु
	काष्ठा nvkm_device *device = bios->subdev.device;
	काष्ठा pci_dev *pdev;
	काष्ठा priv *priv;
	पूर्णांक ret = -ENOMEM;

	अगर (device->func->pci)
		pdev = device->func->pci(device)->pdev;
	अन्यथा
		वापस ERR_PTR(-ENODEV);

	अगर (!pdev->rom || pdev->romlen == 0)
		वापस ERR_PTR(-ENODEV);

	अगर ((priv = kदो_स्मृति(माप(*priv), GFP_KERNEL))) अणु
		priv->size = pdev->romlen;
		अगर (ret = -ENODEV,
		    (priv->rom = ioremap(pdev->rom, pdev->romlen)))
			वापस priv;
		kमुक्त(priv);
	पूर्ण

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम
platक्रमm_fini(व्योम *data)
अणु
	काष्ठा priv *priv = data;

	iounmap(priv->rom);
	kमुक्त(priv);
पूर्ण

स्थिर काष्ठा nvbios_source
nvbios_platक्रमm = अणु
	.name = "PLATFORM",
	.init = platक्रमm_init,
	.fini = platक्रमm_fini,
	.पढ़ो = pcirom_पढ़ो,
	.rw = true,
पूर्ण;
