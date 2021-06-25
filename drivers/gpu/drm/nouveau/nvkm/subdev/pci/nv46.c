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

/* MSI re-arm through the PRI appears to be broken on NV46/NV50/G84/G86/G92,
 * so we access it via alternate PCI config space mechanisms.
 */
व्योम
nv46_pci_msi_rearm(काष्ठा nvkm_pci *pci)
अणु
	काष्ठा nvkm_device *device = pci->subdev.device;
	काष्ठा pci_dev *pdev = device->func->pci(device)->pdev;
	pci_ग_लिखो_config_byte(pdev, 0x68, 0xff);
पूर्ण

अटल स्थिर काष्ठा nvkm_pci_func
nv46_pci_func = अणु
	.rd32 = nv40_pci_rd32,
	.wr08 = nv40_pci_wr08,
	.wr32 = nv40_pci_wr32,
	.msi_rearm = nv46_pci_msi_rearm,
पूर्ण;

पूर्णांक
nv46_pci_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_pci **ppci)
अणु
	वापस nvkm_pci_new_(&nv46_pci_func, device, type, inst, ppci);
पूर्ण
