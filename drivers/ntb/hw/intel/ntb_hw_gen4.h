<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)          */
/* Copyright(c) 2020 Intel Corporation. All rights reserved.   */
#अगर_अघोषित _NTB_INTEL_GEN4_H_
#घोषणा _NTB_INTEL_GEN4_H_

#समावेश "ntb_hw_intel.h"

/* Supported PCI device revision range क्रम ICX */
#घोषणा PCI_DEVICE_REVISION_ICX_MIN	0x2
#घोषणा PCI_DEVICE_REVISION_ICX_MAX	0xF

/* Intel Gen4 NTB hardware */
/* PCIe config space */
#घोषणा GEN4_IMBAR23SZ_OFFSET		0x00c4
#घोषणा GEN4_IMBAR45SZ_OFFSET		0x00c5
#घोषणा GEN4_EMBAR23SZ_OFFSET		0x00c6
#घोषणा GEN4_EMBAR45SZ_OFFSET		0x00c7
#घोषणा GEN4_DEVCTRL_OFFSET		0x0048
#घोषणा GEN4_DEVSTS_OFFSET		0x004a
#घोषणा GEN4_UNCERRSTS_OFFSET		0x0104
#घोषणा GEN4_CORERRSTS_OFFSET		0x0110

/* BAR0 MMIO */
#घोषणा GEN4_NTBCNTL_OFFSET		0x0000
#घोषणा GEN4_IM23XBASE_OFFSET		0x0010	/* IMBAR1XBASE */
#घोषणा GEN4_IM23XLMT_OFFSET		0x0018  /* IMBAR1XLMT */
#घोषणा GEN4_IM45XBASE_OFFSET		0x0020	/* IMBAR2XBASE */
#घोषणा GEN4_IM45XLMT_OFFSET		0x0028  /* IMBAR2XLMT */
#घोषणा GEN4_IM_INT_STATUS_OFFSET	0x0040
#घोषणा GEN4_IM_INT_DISABLE_OFFSET	0x0048
#घोषणा GEN4_INTVEC_OFFSET		0x0050  /* 0-32 vecs */
#घोषणा GEN4_IM23XBASEIDX_OFFSET	0x0074
#घोषणा GEN4_IM45XBASEIDX_OFFSET	0x0076
#घोषणा GEN4_IM_SPAD_OFFSET		0x0080  /* 0-15 SPADs */
#घोषणा GEN4_IM_SPAD_SEM_OFFSET		0x00c0	/* SPAD hw semaphore */
#घोषणा GEN4_IM_SPAD_STICKY_OFFSET	0x00c4  /* sticky SPAD */
#घोषणा GEN4_IM_DOORBELL_OFFSET		0x0100  /* 0-31 करोorbells */
#घोषणा GEN4_LTR_SWSEL_OFFSET		0x30ec
#घोषणा GEN4_LTR_ACTIVE_OFFSET		0x30f0
#घोषणा GEN4_LTR_IDLE_OFFSET		0x30f4
#घोषणा GEN4_EM_SPAD_OFFSET		0x8080
/* note, link status is now in MMIO and not config space क्रम NTB */
#घोषणा GEN4_LINK_CTRL_OFFSET		0xb050
#घोषणा GEN4_LINK_STATUS_OFFSET		0xb052
#घोषणा GEN4_PPD0_OFFSET		0xb0d4
#घोषणा GEN4_PPD1_OFFSET		0xb4c0
#घोषणा GEN4_LTSSMSTATEJMP		0xf040

#घोषणा GEN4_PPD_CLEAR_TRN		0x0001
#घोषणा GEN4_PPD_LINKTRN		0x0008
#घोषणा GEN4_PPD_CONN_MASK		0x0300
#घोषणा GEN4_PPD_CONN_B2B		0x0200
#घोषणा GEN4_PPD_DEV_MASK		0x1000
#घोषणा GEN4_PPD_DEV_DSD		0x1000
#घोषणा GEN4_PPD_DEV_USD		0x0000
#घोषणा GEN4_LINK_CTRL_LINK_DISABLE	0x0010

#घोषणा GEN4_SLOTSTS			0xb05a
#घोषणा GEN4_SLOTSTS_DLLSCS		0x100

#घोषणा GEN4_PPD_TOPO_MASK	(GEN4_PPD_CONN_MASK | GEN4_PPD_DEV_MASK)
#घोषणा GEN4_PPD_TOPO_B2B_USD	(GEN4_PPD_CONN_B2B | GEN4_PPD_DEV_USD)
#घोषणा GEN4_PPD_TOPO_B2B_DSD	(GEN4_PPD_CONN_B2B | GEN4_PPD_DEV_DSD)

#घोषणा GEN4_DB_COUNT			32
#घोषणा GEN4_DB_LINK			32
#घोषणा GEN4_DB_LINK_BIT		BIT_ULL(GEN4_DB_LINK)
#घोषणा GEN4_DB_MSIX_VECTOR_COUNT	33
#घोषणा GEN4_DB_MSIX_VECTOR_SHIFT	1
#घोषणा GEN4_DB_TOTAL_SHIFT		33
#घोषणा GEN4_SPAD_COUNT			16

#घोषणा NTB_CTL_E2I_BAR23_SNOOP		0x000004
#घोषणा NTB_CTL_E2I_BAR23_NOSNOOP	0x000008
#घोषणा NTB_CTL_I2E_BAR23_SNOOP		0x000010
#घोषणा NTB_CTL_I2E_BAR23_NOSNOOP	0x000020
#घोषणा NTB_CTL_E2I_BAR45_SNOOP		0x000040
#घोषणा NTB_CTL_E2I_BAR45_NOSNOO	0x000080
#घोषणा NTB_CTL_I2E_BAR45_SNOOP		0x000100
#घोषणा NTB_CTL_I2E_BAR45_NOSNOOP	0x000200
#घोषणा NTB_CTL_BUSNO_DIS_INC		0x000400
#घोषणा NTB_CTL_LINK_DOWN		0x010000

#घोषणा NTB_SJC_FORCEDETECT		0x000004

#घोषणा NTB_LTR_SWSEL_ACTIVE		0x0
#घोषणा NTB_LTR_SWSEL_IDLE		0x1

#घोषणा NTB_LTR_NS_SHIFT		16
#घोषणा NTB_LTR_ACTIVE_VAL		0x0000  /* 0 us */
#घोषणा NTB_LTR_ACTIVE_LATSCALE		0x0800  /* 1us scale */
#घोषणा NTB_LTR_ACTIVE_REQMNT		0x8000  /* snoop req enable */

#घोषणा NTB_LTR_IDLE_VAL		0x0258  /* 600 us */
#घोषणा NTB_LTR_IDLE_LATSCALE		0x0800  /* 1us scale */
#घोषणा NTB_LTR_IDLE_REQMNT		0x8000  /* snoop req enable */

sमाप_प्रकार ndev_ntb4_debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				      माप_प्रकार count, loff_t *offp);
पूर्णांक gen4_init_dev(काष्ठा पूर्णांकel_ntb_dev *ndev);
sमाप_प्रकार ndev_ntb4_debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				      माप_प्रकार count, loff_t *offp);

बाह्य स्थिर काष्ठा ntb_dev_ops पूर्णांकel_ntb4_ops;

अटल अंतरभूत पूर्णांक pdev_is_ICX(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev_is_gen4(pdev) &&
	    pdev->revision >= PCI_DEVICE_REVISION_ICX_MIN &&
	    pdev->revision <= PCI_DEVICE_REVISION_ICX_MAX)
		वापस 1;
	वापस 0;
पूर्ण

#पूर्ण_अगर
