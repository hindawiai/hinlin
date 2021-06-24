<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_PCI_H__
#घोषणा __NVKM_PCI_H__
#समावेश <core/subdev.h>

क्रमागत nvkm_pcie_speed अणु
	NVKM_PCIE_SPEED_2_5,
	NVKM_PCIE_SPEED_5_0,
	NVKM_PCIE_SPEED_8_0,
पूर्ण;

काष्ठा nvkm_pci अणु
	स्थिर काष्ठा nvkm_pci_func *func;
	काष्ठा nvkm_subdev subdev;
	काष्ठा pci_dev *pdev;
	पूर्णांक irq;

	काष्ठा अणु
		काष्ठा agp_bridge_data *bridge;
		u32 mode;
		u64 base;
		u64 size;
		पूर्णांक mtrr;
		bool cma;
		bool acquired;
	पूर्ण agp;

	काष्ठा अणु
		क्रमागत nvkm_pcie_speed speed;
		u8 width;
	पूर्ण pcie;

	bool msi;
पूर्ण;

u32 nvkm_pci_rd32(काष्ठा nvkm_pci *, u16 addr);
व्योम nvkm_pci_wr08(काष्ठा nvkm_pci *, u16 addr, u8 data);
व्योम nvkm_pci_wr32(काष्ठा nvkm_pci *, u16 addr, u32 data);
u32 nvkm_pci_mask(काष्ठा nvkm_pci *, u16 addr, u32 mask, u32 value);
व्योम nvkm_pci_rom_shaकरोw(काष्ठा nvkm_pci *, bool shaकरोw);

पूर्णांक nv04_pci_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pci **);
पूर्णांक nv40_pci_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pci **);
पूर्णांक nv46_pci_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pci **);
पूर्णांक nv4c_pci_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pci **);
पूर्णांक g84_pci_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pci **);
पूर्णांक g92_pci_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pci **);
पूर्णांक g94_pci_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pci **);
पूर्णांक gf100_pci_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pci **);
पूर्णांक gf106_pci_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pci **);
पूर्णांक gk104_pci_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pci **);
पूर्णांक gp100_pci_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pci **);

/* pcie functions */
पूर्णांक nvkm_pcie_set_link(काष्ठा nvkm_pci *, क्रमागत nvkm_pcie_speed, u8 width);
#पूर्ण_अगर
