<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* pci_sun4v.h: SUN4V specअगरic PCI controller support.
 *
 * Copyright (C) 2006 David S. Miller (davem@davemloft.net)
 */

#अगर_अघोषित _PCI_SUN4V_H
#घोषणा _PCI_SUN4V_H

दीर्घ pci_sun4v_iommu_map(अचिन्हित दीर्घ devhandle,
			 अचिन्हित दीर्घ tsbid,
			 अचिन्हित दीर्घ num_ttes,
			 अचिन्हित दीर्घ io_attributes,
			 अचिन्हित दीर्घ io_page_list_pa);
अचिन्हित दीर्घ pci_sun4v_iommu_demap(अचिन्हित दीर्घ devhandle,
				    अचिन्हित दीर्घ tsbid,
				    अचिन्हित दीर्घ num_ttes);
अचिन्हित दीर्घ pci_sun4v_iommu_geपंचांगap(अचिन्हित दीर्घ devhandle,
				     अचिन्हित दीर्घ tsbid,
				     अचिन्हित दीर्घ *io_attributes,
				     अचिन्हित दीर्घ *real_address);
अचिन्हित दीर्घ pci_sun4v_config_get(अचिन्हित दीर्घ devhandle,
				   अचिन्हित दीर्घ pci_device,
				   अचिन्हित दीर्घ config_offset,
				   अचिन्हित दीर्घ size);
पूर्णांक pci_sun4v_config_put(अचिन्हित दीर्घ devhandle,
			 अचिन्हित दीर्घ pci_device,
			 अचिन्हित दीर्घ config_offset,
			 अचिन्हित दीर्घ size,
			 अचिन्हित दीर्घ data);

अचिन्हित दीर्घ pci_sun4v_msiq_conf(अचिन्हित दीर्घ devhandle,
					 अचिन्हित दीर्घ msiqid,
					 अचिन्हित दीर्घ msiq_paddr,
					 अचिन्हित दीर्घ num_entries);
अचिन्हित दीर्घ pci_sun4v_msiq_info(अचिन्हित दीर्घ devhandle,
				  अचिन्हित दीर्घ msiqid,
				  अचिन्हित दीर्घ *msiq_paddr,
				  अचिन्हित दीर्घ *num_entries);
अचिन्हित दीर्घ pci_sun4v_msiq_getvalid(अचिन्हित दीर्घ devhandle,
				      अचिन्हित दीर्घ msiqid,
				      अचिन्हित दीर्घ *valid);
अचिन्हित दीर्घ pci_sun4v_msiq_setvalid(अचिन्हित दीर्घ devhandle,
				      अचिन्हित दीर्घ msiqid,
				      अचिन्हित दीर्घ valid);
अचिन्हित दीर्घ pci_sun4v_msiq_माला_लोtate(अचिन्हित दीर्घ devhandle,
				      अचिन्हित दीर्घ msiqid,
				      अचिन्हित दीर्घ *state);
अचिन्हित दीर्घ pci_sun4v_msiq_setstate(अचिन्हित दीर्घ devhandle,
				      अचिन्हित दीर्घ msiqid,
				      अचिन्हित दीर्घ state);
अचिन्हित दीर्घ pci_sun4v_msiq_gethead(अचिन्हित दीर्घ devhandle,
				     अचिन्हित दीर्घ msiqid,
				     अचिन्हित दीर्घ *head);
अचिन्हित दीर्घ pci_sun4v_msiq_sethead(अचिन्हित दीर्घ devhandle,
				     अचिन्हित दीर्घ msiqid,
				     अचिन्हित दीर्घ head);
अचिन्हित दीर्घ pci_sun4v_msiq_gettail(अचिन्हित दीर्घ devhandle,
				      अचिन्हित दीर्घ msiqid,
				      अचिन्हित दीर्घ *head);
अचिन्हित दीर्घ pci_sun4v_msi_getvalid(अचिन्हित दीर्घ devhandle,
				     अचिन्हित दीर्घ msinum,
				     अचिन्हित दीर्घ *valid);
अचिन्हित दीर्घ pci_sun4v_msi_setvalid(अचिन्हित दीर्घ devhandle,
				     अचिन्हित दीर्घ msinum,
				     अचिन्हित दीर्घ valid);
अचिन्हित दीर्घ pci_sun4v_msi_geपंचांगsiq(अचिन्हित दीर्घ devhandle,
				    अचिन्हित दीर्घ msinum,
				    अचिन्हित दीर्घ *msiq);
अचिन्हित दीर्घ pci_sun4v_msi_seपंचांगsiq(अचिन्हित दीर्घ devhandle,
				    अचिन्हित दीर्घ msinum,
				    अचिन्हित दीर्घ msiq,
				    अचिन्हित दीर्घ msitype);
अचिन्हित दीर्घ pci_sun4v_msi_माला_लोtate(अचिन्हित दीर्घ devhandle,
				     अचिन्हित दीर्घ msinum,
				     अचिन्हित दीर्घ *state);
अचिन्हित दीर्घ pci_sun4v_msi_setstate(अचिन्हित दीर्घ devhandle,
				     अचिन्हित दीर्घ msinum,
				     अचिन्हित दीर्घ state);
अचिन्हित दीर्घ pci_sun4v_msg_geपंचांगsiq(अचिन्हित दीर्घ devhandle,
				    अचिन्हित दीर्घ msinum,
				    अचिन्हित दीर्घ *msiq);
अचिन्हित दीर्घ pci_sun4v_msg_seपंचांगsiq(अचिन्हित दीर्घ devhandle,
				    अचिन्हित दीर्घ msinum,
				    अचिन्हित दीर्घ msiq);
अचिन्हित दीर्घ pci_sun4v_msg_getvalid(अचिन्हित दीर्घ devhandle,
				     अचिन्हित दीर्घ msinum,
				     अचिन्हित दीर्घ *valid);
अचिन्हित दीर्घ pci_sun4v_msg_setvalid(अचिन्हित दीर्घ devhandle,
				     अचिन्हित दीर्घ msinum,
				     अचिन्हित दीर्घ valid);

/* Sun4v HV IOMMU v2 APIs */
अचिन्हित दीर्घ pci_sun4v_iotsb_conf(अचिन्हित दीर्घ devhandle,
				   अचिन्हित दीर्घ ra,
				   अचिन्हित दीर्घ table_size,
				   अचिन्हित दीर्घ page_size,
				   अचिन्हित दीर्घ dvma_base,
				   u64 *iotsb_num);
अचिन्हित दीर्घ pci_sun4v_iotsb_bind(अचिन्हित दीर्घ devhandle,
				   अचिन्हित दीर्घ iotsb_num,
				   अचिन्हित पूर्णांक pci_device);
अचिन्हित दीर्घ pci_sun4v_iotsb_map(अचिन्हित दीर्घ devhandle,
				  अचिन्हित दीर्घ iotsb_num,
				  अचिन्हित दीर्घ iotsb_index_iottes,
				  अचिन्हित दीर्घ io_attributes,
				  अचिन्हित दीर्घ io_page_list_pa,
				  दीर्घ *mapped);
अचिन्हित दीर्घ pci_sun4v_iotsb_demap(अचिन्हित दीर्घ devhandle,
				    अचिन्हित दीर्घ iotsb_num,
				    अचिन्हित दीर्घ iotsb_index,
				    अचिन्हित दीर्घ iottes,
				    अचिन्हित दीर्घ *demapped);
#पूर्ण_अगर /* !(_PCI_SUN4V_H) */
