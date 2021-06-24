<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * MPC85xx/86xx PCI Express काष्ठाure define
 *
 * Copyright 2007,2011 Freescale Semiconductor, Inc
 */

#अगर_घोषित __KERNEL__
#अगर_अघोषित __POWERPC_FSL_PCI_H
#घोषणा __POWERPC_FSL_PCI_H

काष्ठा platक्रमm_device;


/* FSL PCI controller BRR1 रेजिस्टर */
#घोषणा PCI_FSL_BRR1      0xbf8
#घोषणा PCI_FSL_BRR1_VER 0xffff

#घोषणा PCIE_LTSSM	0x0404		/* PCIE Link Training and Status */
#घोषणा PCIE_LTSSM_L0	0x16		/* L0 state */
#घोषणा PCIE_IP_REV_2_2		0x02080202 /* PCIE IP block version Rev2.2 */
#घोषणा PCIE_IP_REV_3_0		0x02080300 /* PCIE IP block version Rev3.0 */
#घोषणा PIWAR_EN		0x80000000	/* Enable */
#घोषणा PIWAR_PF		0x20000000	/* prefetch */
#घोषणा PIWAR_TGI_LOCAL		0x00f00000	/* target - local memory */
#घोषणा PIWAR_READ_SNOOP	0x00050000
#घोषणा PIWAR_WRITE_SNOOP	0x00005000
#घोषणा PIWAR_SZ_MASK          0x0000003f

#घोषणा PEX_PMCR_PTOMR		0x1
#घोषणा PEX_PMCR_EXL2S		0x2

#घोषणा PME_DISR_EN_PTOD	0x00008000
#घोषणा PME_DISR_EN_ENL23D	0x00002000
#घोषणा PME_DISR_EN_EXL23D	0x00001000

/* PCI/PCI Express outbound winकरोw reg */
काष्ठा pci_outbound_winकरोw_regs अणु
	__be32	potar;	/* 0x.0 - Outbound translation address रेजिस्टर */
	__be32	potear;	/* 0x.4 - Outbound translation extended address रेजिस्टर */
	__be32	घातbar;	/* 0x.8 - Outbound winकरोw base address रेजिस्टर */
	u8	res1[4];
	__be32	घातar;	/* 0x.10 - Outbound winकरोw attributes रेजिस्टर */
	u8	res2[12];
पूर्ण;

/* PCI/PCI Express inbound winकरोw reg */
काष्ठा pci_inbound_winकरोw_regs अणु
	__be32	pitar;	/* 0x.0 - Inbound translation address रेजिस्टर */
	u8	res1[4];
	__be32	piwbar;	/* 0x.8 - Inbound winकरोw base address रेजिस्टर */
	__be32	piwbear;	/* 0x.c - Inbound winकरोw base extended address रेजिस्टर */
	__be32	piwar;	/* 0x.10 - Inbound winकरोw attributes रेजिस्टर */
	u8	res2[12];
पूर्ण;

/* PCI/PCI Express IO block रेजिस्टरs क्रम 85xx/86xx */
काष्ठा ccsr_pci अणु
	__be32	config_addr;		/* 0x.000 - PCI/PCIE Configuration Address Register */
	__be32	config_data;		/* 0x.004 - PCI/PCIE Configuration Data Register */
	__be32	पूर्णांक_ack;		/* 0x.008 - PCI Interrupt Acknowledge Register */
	__be32	pex_otb_cpl_tor;	/* 0x.00c - PCIE Outbound completion समयout रेजिस्टर */
	__be32	pex_conf_tor;		/* 0x.010 - PCIE configuration समयout रेजिस्टर */
	__be32	pex_config;		/* 0x.014 - PCIE CONFIG Register */
	__be32	pex_पूर्णांक_status;		/* 0x.018 - PCIE पूर्णांकerrupt status */
	u8	res2[4];
	__be32	pex_pme_mes_dr;		/* 0x.020 - PCIE PME and message detect रेजिस्टर */
	__be32	pex_pme_mes_disr;	/* 0x.024 - PCIE PME and message disable रेजिस्टर */
	__be32	pex_pme_mes_ier;	/* 0x.028 - PCIE PME and message पूर्णांकerrupt enable रेजिस्टर */
	__be32	pex_pmcr;		/* 0x.02c - PCIE घातer management command रेजिस्टर */
	u8	res3[3016];
	__be32	block_rev1;	/* 0x.bf8 - PCIE Block Revision रेजिस्टर 1 */
	__be32	block_rev2;	/* 0x.bfc - PCIE Block Revision रेजिस्टर 2 */

/* PCI/PCI Express outbound winकरोw 0-4
 * Winकरोw 0 is the शेष winकरोw and is the only winकरोw enabled upon reset.
 * The शेष outbound रेजिस्टर set is used when a transaction misses
 * in all of the other outbound winकरोws.
 */
	काष्ठा pci_outbound_winकरोw_regs घात[5];
	u8	res14[96];
	काष्ठा pci_inbound_winकरोw_regs	pmit;	/* 0xd00 - 0xd9c Inbound MSI */
	u8	res6[96];
/* PCI/PCI Express inbound winकरोw 3-0
 * inbound winकरोw 1 supports only a 32-bit base address and करोes not
 * define an inbound winकरोw base extended address रेजिस्टर.
 */
	काष्ठा pci_inbound_winकरोw_regs piw[4];

	__be32	pex_err_dr;		/* 0x.e00 - PCI/PCIE error detect रेजिस्टर */
	u8	res21[4];
	__be32	pex_err_en;		/* 0x.e08 - PCI/PCIE error पूर्णांकerrupt enable रेजिस्टर */
	u8	res22[4];
	__be32	pex_err_disr;		/* 0x.e10 - PCI/PCIE error disable रेजिस्टर */
	u8	res23[12];
	__be32	pex_err_cap_stat;	/* 0x.e20 - PCI/PCIE error capture status रेजिस्टर */
	u8	res24[4];
	__be32	pex_err_cap_r0;		/* 0x.e28 - PCIE error capture रेजिस्टर 0 */
	__be32	pex_err_cap_r1;		/* 0x.e2c - PCIE error capture रेजिस्टर 0 */
	__be32	pex_err_cap_r2;		/* 0x.e30 - PCIE error capture रेजिस्टर 0 */
	__be32	pex_err_cap_r3;		/* 0x.e34 - PCIE error capture रेजिस्टर 0 */
	u8	res_e38[200];
	__be32	pdb_stat;		/* 0x.f00 - PCIE Debug Status */
	u8	res_f04[16];
	__be32	pex_csr0;		/* 0x.f14 - PEX Control/Status रेजिस्टर 0*/
#घोषणा PEX_CSR0_LTSSM_MASK	0xFC
#घोषणा PEX_CSR0_LTSSM_SHIFT	2
#घोषणा PEX_CSR0_LTSSM_L0	0x11
	__be32	pex_csr1;		/* 0x.f18 - PEX Control/Status रेजिस्टर 1*/
	u8	res_f1c[228];

पूर्ण;

बाह्य पूर्णांक fsl_add_bridge(काष्ठा platक्रमm_device *pdev, पूर्णांक is_primary);
बाह्य व्योम fsl_pcibios_fixup_bus(काष्ठा pci_bus *bus);
बाह्य व्योम fsl_pcibios_fixup_phb(काष्ठा pci_controller *phb);
बाह्य पूर्णांक mpc83xx_add_bridge(काष्ठा device_node *dev);
u64 fsl_pci_immrbar_base(काष्ठा pci_controller *hose);

बाह्य काष्ठा device_node *fsl_pci_primary;

#अगर_घोषित CONFIG_PCI
व्योम fsl_pci_assign_primary(व्योम);
#अन्यथा
अटल अंतरभूत व्योम fsl_pci_assign_primary(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FSL_PCI
बाह्य पूर्णांक fsl_pci_mcheck_exception(काष्ठा pt_regs *);
#अन्यथा
अटल अंतरभूत पूर्णांक fsl_pci_mcheck_exception(काष्ठा pt_regs *regs) अणुवापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __POWERPC_FSL_PCI_H */
#पूर्ण_अगर /* __KERNEL__ */
