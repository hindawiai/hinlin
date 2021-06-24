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

#अगर defined(__घातerpc__)
काष्ठा priv अणु
	स्थिर व्योम __iomem *data;
	पूर्णांक size;
पूर्ण;

अटल u32
of_पढ़ो(व्योम *data, u32 offset, u32 length, काष्ठा nvkm_bios *bios)
अणु
	काष्ठा priv *priv = data;
	अगर (offset < priv->size) अणु
		length = min_t(u32, length, priv->size - offset);
		स_नकल_fromio(bios->data + offset, priv->data + offset, length);
		वापस length;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32
of_size(व्योम *data)
अणु
	काष्ठा priv *priv = data;
	वापस priv->size;
पूर्ण

अटल व्योम *
of_init(काष्ठा nvkm_bios *bios, स्थिर अक्षर *name)
अणु
	काष्ठा nvkm_device *device = bios->subdev.device;
	काष्ठा pci_dev *pdev = device->func->pci(device)->pdev;
	काष्ठा device_node *dn;
	काष्ठा priv *priv;
	अगर (!(dn = pci_device_to_OF_node(pdev)))
		वापस ERR_PTR(-ENODEV);
	अगर (!(priv = kzalloc(माप(*priv), GFP_KERNEL)))
		वापस ERR_PTR(-ENOMEM);
	अगर ((priv->data = of_get_property(dn, "NVDA,BMP", &priv->size)))
		वापस priv;
	kमुक्त(priv);
	वापस ERR_PTR(-EINVAL);
पूर्ण

स्थिर काष्ठा nvbios_source
nvbios_of = अणु
	.name = "OpenFirmware",
	.init = of_init,
	.fini = (व्योम(*)(व्योम *))kमुक्त,
	.पढ़ो = of_पढ़ो,
	.size = of_size,
	.rw = false,
	.ignore_checksum = true,
	.no_pcir = true,
पूर्ण;
#अन्यथा
स्थिर काष्ठा nvbios_source
nvbios_of = अणु
पूर्ण;
#पूर्ण_अगर
