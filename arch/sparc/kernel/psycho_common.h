<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PSYCHO_COMMON_H
#घोषणा _PSYCHO_COMMON_H

/* U2P Programmer's Manual, page 13-55, configuration space
 * address क्रमmat:
 * 
 *  32             24 23 16 15    11 10       8 7   2  1 0
 * ---------------------------------------------------------
 * |0 0 0 0 0 0 0 0 1| bus | device | function | reg | 0 0 |
 * ---------------------------------------------------------
 */
#घोषणा PSYCHO_CONFIG_BASE(PBM)	\
	((PBM)->config_space | (1UL << 24))
#घोषणा PSYCHO_CONFIG_ENCODE(BUS, DEVFN, REG)	\
	(((अचिन्हित दीर्घ)(BUS)   << 16) |	\
	 ((अचिन्हित दीर्घ)(DEVFN) << 8)  |	\
	 ((अचिन्हित दीर्घ)(REG)))

अटल अंतरभूत व्योम *psycho_pci_config_mkaddr(काष्ठा pci_pbm_info *pbm,
					     अचिन्हित अक्षर bus,
					     अचिन्हित पूर्णांक devfn,
					     पूर्णांक where)
अणु
	वापस (व्योम *)
		(PSYCHO_CONFIG_BASE(pbm) |
		 PSYCHO_CONFIG_ENCODE(bus, devfn, where));
पूर्ण

क्रमागत psycho_error_type अणु
	UE_ERR, CE_ERR, PCI_ERR
पूर्ण;

व्योम psycho_check_iommu_error(काष्ठा pci_pbm_info *pbm,
			      अचिन्हित दीर्घ afsr,
			      अचिन्हित दीर्घ afar,
			      क्रमागत psycho_error_type type);

irqवापस_t psycho_pcierr_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);

पूर्णांक psycho_iommu_init(काष्ठा pci_pbm_info *pbm, पूर्णांक tsbsize,
		      u32 dvma_offset, u32 dma_mask,
		      अचिन्हित दीर्घ ग_लिखो_complete_offset);

व्योम psycho_pbm_init_common(काष्ठा pci_pbm_info *pbm,
			    काष्ठा platक्रमm_device *op,
			    स्थिर अक्षर *chip_name, पूर्णांक chip_type);

#पूर्ण_अगर /* _PSYCHO_COMMON_H */
