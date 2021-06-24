<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_PCI_PRIV_H__
#घोषणा __NVKM_PCI_PRIV_H__
#घोषणा nvkm_pci(p) container_of((p), काष्ठा nvkm_pci, subdev)
#समावेश <subdev/pci.h>

पूर्णांक nvkm_pci_new_(स्थिर काष्ठा nvkm_pci_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_pci **);

काष्ठा nvkm_pci_func अणु
	व्योम (*init)(काष्ठा nvkm_pci *);
	u32 (*rd32)(काष्ठा nvkm_pci *, u16 addr);
	व्योम (*wr08)(काष्ठा nvkm_pci *, u16 addr, u8 data);
	व्योम (*wr32)(काष्ठा nvkm_pci *, u16 addr, u32 data);
	व्योम (*msi_rearm)(काष्ठा nvkm_pci *);

	काष्ठा अणु
		पूर्णांक (*init)(काष्ठा nvkm_pci *);
		पूर्णांक (*set_link)(काष्ठा nvkm_pci *, क्रमागत nvkm_pcie_speed, u8);

		क्रमागत nvkm_pcie_speed (*max_speed)(काष्ठा nvkm_pci *);
		क्रमागत nvkm_pcie_speed (*cur_speed)(काष्ठा nvkm_pci *);

		व्योम (*set_version)(काष्ठा nvkm_pci *, u8);
		पूर्णांक (*version)(काष्ठा nvkm_pci *);
		पूर्णांक (*version_supported)(काष्ठा nvkm_pci *);
	पूर्ण pcie;
पूर्ण;

u32 nv40_pci_rd32(काष्ठा nvkm_pci *, u16);
व्योम nv40_pci_wr08(काष्ठा nvkm_pci *, u16, u8);
व्योम nv40_pci_wr32(काष्ठा nvkm_pci *, u16, u32);
व्योम nv40_pci_msi_rearm(काष्ठा nvkm_pci *);

व्योम nv46_pci_msi_rearm(काष्ठा nvkm_pci *);

व्योम g84_pci_init(काष्ठा nvkm_pci *pci);

/* pcie functions */
व्योम g84_pcie_set_version(काष्ठा nvkm_pci *, u8);
पूर्णांक g84_pcie_version(काष्ठा nvkm_pci *);
व्योम g84_pcie_set_link_speed(काष्ठा nvkm_pci *, क्रमागत nvkm_pcie_speed);
क्रमागत nvkm_pcie_speed g84_pcie_cur_speed(काष्ठा nvkm_pci *);
क्रमागत nvkm_pcie_speed g84_pcie_max_speed(काष्ठा nvkm_pci *);
पूर्णांक g84_pcie_init(काष्ठा nvkm_pci *);
पूर्णांक g84_pcie_set_link(काष्ठा nvkm_pci *, क्रमागत nvkm_pcie_speed, u8);

पूर्णांक g92_pcie_version_supported(काष्ठा nvkm_pci *);

व्योम gf100_pcie_set_version(काष्ठा nvkm_pci *, u8);
पूर्णांक gf100_pcie_version(काष्ठा nvkm_pci *);
व्योम gf100_pcie_set_cap_speed(काष्ठा nvkm_pci *, bool);
पूर्णांक gf100_pcie_cap_speed(काष्ठा nvkm_pci *);
पूर्णांक gf100_pcie_init(काष्ठा nvkm_pci *);
पूर्णांक gf100_pcie_set_link(काष्ठा nvkm_pci *, क्रमागत nvkm_pcie_speed, u8);

पूर्णांक nvkm_pcie_oneinit(काष्ठा nvkm_pci *);
पूर्णांक nvkm_pcie_init(काष्ठा nvkm_pci *);
#पूर्ण_अगर
