<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DEVICE_PCI_H__
#घोषणा __NVKM_DEVICE_PCI_H__
#समावेश <core/device.h>

काष्ठा nvkm_device_pci अणु
	काष्ठा nvkm_device device;
	काष्ठा pci_dev *pdev;
	bool suspend;
पूर्ण;

पूर्णांक nvkm_device_pci_new(काष्ठा pci_dev *, स्थिर अक्षर *cfg, स्थिर अक्षर *dbg,
			bool detect, bool mmio, u64 subdev_mask,
			काष्ठा nvkm_device **);
#पूर्ण_अगर
