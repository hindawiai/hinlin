<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#समावेश "priv.h"
#अगर defined(CONFIG_AGP) || (defined(CONFIG_AGP_MODULE) && defined(MODULE))
#अगर_अघोषित __NVKM_PCI_AGP_H__
#घोषणा __NVKM_PCI_AGP_H__

व्योम nvkm_agp_ctor(काष्ठा nvkm_pci *);
व्योम nvkm_agp_dtor(काष्ठा nvkm_pci *);
व्योम nvkm_agp_preinit(काष्ठा nvkm_pci *);
पूर्णांक nvkm_agp_init(काष्ठा nvkm_pci *);
व्योम nvkm_agp_fini(काष्ठा nvkm_pci *);
#पूर्ण_अगर
#अन्यथा
अटल अंतरभूत व्योम nvkm_agp_ctor(काष्ठा nvkm_pci *pci) अणुपूर्ण
अटल अंतरभूत व्योम nvkm_agp_dtor(काष्ठा nvkm_pci *pci) अणुपूर्ण
अटल अंतरभूत व्योम nvkm_agp_preinit(काष्ठा nvkm_pci *pci) अणुपूर्ण
अटल अंतरभूत पूर्णांक nvkm_agp_init(काष्ठा nvkm_pci *pci) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम nvkm_agp_fini(काष्ठा nvkm_pci *pci) अणुपूर्ण
#पूर्ण_अगर
