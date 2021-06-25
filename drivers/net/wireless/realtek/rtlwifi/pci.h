<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL_PCI_H__
#घोषणा __RTL_PCI_H__

#समावेश <linux/pci.h>
/* 1: MSDU packet queue,
 * 2: Rx Command Queue
 */
#घोषणा RTL_PCI_RX_MPDU_QUEUE			0
#घोषणा RTL_PCI_RX_CMD_QUEUE			1
#घोषणा RTL_PCI_MAX_RX_QUEUE			2

#घोषणा RTL_PCI_MAX_RX_COUNT			512/*64*/
#घोषणा RTL_PCI_MAX_TX_QUEUE_COUNT		9

#घोषणा RT_TXDESC_NUM				128
#घोषणा TX_DESC_NUM_92E				512
#घोषणा TX_DESC_NUM_8822B			512
#घोषणा RT_TXDESC_NUM_BE_QUEUE			256

#घोषणा BK_QUEUE				0
#घोषणा BE_QUEUE				1
#घोषणा VI_QUEUE				2
#घोषणा VO_QUEUE				3
#घोषणा BEACON_QUEUE				4
#घोषणा TXCMD_QUEUE				5
#घोषणा MGNT_QUEUE				6
#घोषणा HIGH_QUEUE				7
#घोषणा HCCA_QUEUE				8
#घोषणा H2C_QUEUE				TXCMD_QUEUE	/* In 8822B */

#घोषणा RTL_PCI_DEVICE(vend, dev, cfg)  \
	.venकरोr = (vend), \
	.device = (dev), \
	.subvenकरोr = PCI_ANY_ID, \
	.subdevice = PCI_ANY_ID,\
	.driver_data = (kernel_uदीर्घ_t)&(cfg)

#घोषणा INTEL_VENDOR_ID				0x8086
#घोषणा SIS_VENDOR_ID				0x1039
#घोषणा ATI_VENDOR_ID				0x1002
#घोषणा ATI_DEVICE_ID				0x7914
#घोषणा AMD_VENDOR_ID				0x1022

#घोषणा PCI_MAX_BRIDGE_NUMBER			255
#घोषणा PCI_MAX_DEVICES				32
#घोषणा PCI_MAX_FUNCTION			8

#घोषणा PCI_CONF_ADDRESS	0x0CF8	/*PCI Configuration Space Address */
#घोषणा PCI_CONF_DATA		0x0CFC	/*PCI Configuration Space Data */

#घोषणा PCI_CLASS_BRIDGE_DEV		0x06
#घोषणा PCI_SUBCLASS_BR_PCI_TO_PCI	0x04
#घोषणा PCI_CAPABILITY_ID_PCI_EXPRESS	0x10
#घोषणा PCI_CAP_ID_EXP			0x10

#घोषणा U1DONTCARE			0xFF
#घोषणा U2DONTCARE			0xFFFF
#घोषणा U4DONTCARE			0xFFFFFFFF

#घोषणा RTL_PCI_8192_DID	0x8192	/*8192 PCI-E */
#घोषणा RTL_PCI_8192SE_DID	0x8192	/*8192 SE */
#घोषणा RTL_PCI_8174_DID	0x8174	/*8192 SE */
#घोषणा RTL_PCI_8173_DID	0x8173	/*8191 SE Crab */
#घोषणा RTL_PCI_8172_DID	0x8172	/*8191 SE RE */
#घोषणा RTL_PCI_8171_DID	0x8171	/*8191 SE Unicron */
#घोषणा RTL_PCI_8723AE_DID	0x8723	/*8723AE */
#घोषणा RTL_PCI_0045_DID	0x0045	/*8190 PCI क्रम Ceraga */
#घोषणा RTL_PCI_0046_DID	0x0046	/*8190 Cardbus क्रम Ceraga */
#घोषणा RTL_PCI_0044_DID	0x0044	/*8192e PCIE क्रम Ceraga */
#घोषणा RTL_PCI_0047_DID	0x0047	/*8192e Express Card क्रम Ceraga */
#घोषणा RTL_PCI_700F_DID	0x700F
#घोषणा RTL_PCI_701F_DID	0x701F
#घोषणा RTL_PCI_DLINK_DID	0x3304
#घोषणा RTL_PCI_8723AE_DID	0x8723	/*8723e */
#घोषणा RTL_PCI_8192CET_DID	0x8191	/*8192ce */
#घोषणा RTL_PCI_8192CE_DID	0x8178	/*8192ce */
#घोषणा RTL_PCI_8191CE_DID	0x8177	/*8192ce */
#घोषणा RTL_PCI_8188CE_DID	0x8176	/*8192ce */
#घोषणा RTL_PCI_8192CU_DID	0x8191	/*8192ce */
#घोषणा RTL_PCI_8192DE_DID	0x8193	/*8192de */
#घोषणा RTL_PCI_8192DE_DID2	0x002B	/*92DE*/
#घोषणा RTL_PCI_8188EE_DID	0x8179  /*8188ee*/
#घोषणा RTL_PCI_8723BE_DID	0xB723  /*8723be*/
#घोषणा RTL_PCI_8192EE_DID	0x818B	/*8192ee*/
#घोषणा RTL_PCI_8821AE_DID	0x8821	/*8821ae*/
#घोषणा RTL_PCI_8812AE_DID	0x8812	/*8812ae*/
#घोषणा RTL_PCI_8822BE_DID	0xB822	/*8822be*/

/*8192 support 16 pages of IO रेजिस्टरs*/
#घोषणा RTL_MEM_MAPPED_IO_RANGE_8190PCI		0x1000
#घोषणा RTL_MEM_MAPPED_IO_RANGE_8192PCIE	0x4000
#घोषणा RTL_MEM_MAPPED_IO_RANGE_8192SE		0x4000
#घोषणा RTL_MEM_MAPPED_IO_RANGE_8192CE		0x4000
#घोषणा RTL_MEM_MAPPED_IO_RANGE_8192DE		0x4000

#घोषणा RTL_PCI_REVISION_ID_8190PCI		0x00
#घोषणा RTL_PCI_REVISION_ID_8192PCIE		0x01
#घोषणा RTL_PCI_REVISION_ID_8192SE		0x10
#घोषणा RTL_PCI_REVISION_ID_8192CE		0x1
#घोषणा RTL_PCI_REVISION_ID_8192DE		0x0

#घोषणा RTL_DEFAULT_HARDWARE_TYPE	HARDWARE_TYPE_RTL8192CE

क्रमागत pci_bridge_venकरोr अणु
	PCI_BRIDGE_VENDOR_INTEL = 0x0,	/*0b'0000,0001 */
	PCI_BRIDGE_VENDOR_ATI,		/*0b'0000,0010*/
	PCI_BRIDGE_VENDOR_AMD,		/*0b'0000,0100*/
	PCI_BRIDGE_VENDOR_SIS,		/*0b'0000,1000*/
	PCI_BRIDGE_VENDOR_UNKNOWN,	/*0b'0100,0000*/
	PCI_BRIDGE_VENDOR_MAX,
पूर्ण;

काष्ठा rtl_pci_capabilities_header अणु
	u8 capability_id;
	u8 next;
पूर्ण;

/* In new TRX flow, Buffer_desc is new concept
 * But TX wअगरi info == TX descriptor in old flow
 * RX wअगरi info == RX descriptor in old flow
 */
काष्ठा rtl_tx_buffer_desc अणु
	u32 dword[4 * (1 << (BUFDESC_SEG_NUM + 1))];
पूर्ण __packed;

काष्ठा rtl_tx_desc अणु
	u32 dword[16];
पूर्ण __packed;

काष्ठा rtl_rx_buffer_desc अणु /*rx buffer desc*/
	u32 dword[4];
पूर्ण __packed;

काष्ठा rtl_rx_desc अणु /*old: rx desc new: rx wअगरi info*/
	u32 dword[8];
पूर्ण __packed;

काष्ठा rtl_tx_cmd_desc अणु
	u32 dword[16];
पूर्ण __packed;

काष्ठा rtl8192_tx_ring अणु
	काष्ठा rtl_tx_desc *desc;
	dma_addr_t dma;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक entries;
	काष्ठा sk_buff_head queue;
	/*add क्रम new trx flow*/
	काष्ठा rtl_tx_buffer_desc *buffer_desc; /*tx buffer descriptor*/
	dma_addr_t buffer_desc_dma; /*tx bufferd desc dma memory*/
	u16 cur_tx_wp; /* current_tx_ग_लिखो_poपूर्णांक */
	u16 cur_tx_rp; /* current_tx_पढ़ो_poपूर्णांक */
पूर्ण;

काष्ठा rtl8192_rx_ring अणु
	काष्ठा rtl_rx_desc *desc;
	dma_addr_t dma;
	अचिन्हित पूर्णांक idx;
	काष्ठा sk_buff *rx_buf[RTL_PCI_MAX_RX_COUNT];
	/*add क्रम new trx flow*/
	काष्ठा rtl_rx_buffer_desc *buffer_desc; /*rx buffer descriptor*/
	u16 next_rx_rp; /* next_rx_पढ़ो_poपूर्णांक */
पूर्ण;

काष्ठा rtl_pci अणु
	काष्ठा pci_dev *pdev;
	bool irq_enabled;

	bool driver_is_goingto_unload;
	bool up_first_समय;
	bool first_init;
	bool being_init_adapter;
	bool init_पढ़ोy;

	/*Tx */
	काष्ठा rtl8192_tx_ring tx_ring[RTL_PCI_MAX_TX_QUEUE_COUNT];
	पूर्णांक txringcount[RTL_PCI_MAX_TX_QUEUE_COUNT];
	u32 transmit_config;

	/*Rx */
	काष्ठा rtl8192_rx_ring rx_ring[RTL_PCI_MAX_RX_QUEUE];
	पूर्णांक rxringcount;
	u16 rxbuffersize;
	u32 receive_config;

	/*irq */
	u8 irq_alloc;
	u32 irq_mask[4];	/* 0-1: normal, 2: unused, 3: h2c */
	u32 sys_irq_mask;

	/*Bcn control रेजिस्टर setting */
	u32 reg_bcn_ctrl_val;

	 /*ASPM*/ u8 स्थिर_pci_aspm;
	u8 स्थिर_amdpci_aspm;
	u8 स्थिर_hwsw_rfoff_d3;
	u8 स्थिर_support_pciaspm;
	/*pci-e bridge */
	u8 स्थिर_hostpci_aspm_setting;
	/*pci-e device */
	u8 स्थिर_devicepci_aspm_setting;
	/* If it supports ASPM, Offset[560h] = 0x40,
	 * otherwise Offset[560h] = 0x00.
	 */
	bool support_aspm;
	bool support_backकरोor;

	/*QOS & EDCA */
	क्रमागत acm_method acm_method;

	u16 लघुretry_limit;
	u16 दीर्घretry_limit;

	/* MSI support */
	bool msi_support;
	bool using_msi;
	/* पूर्णांकerrupt clear beक्रमe set */
	bool पूर्णांक_clear;
पूर्ण;

काष्ठा mp_adapter अणु
	u8 linkctrl_reg;

	u8 busnumber;
	u8 devnumber;
	u8 funcnumber;

	u8 pcibridge_busnum;
	u8 pcibridge_devnum;
	u8 pcibridge_funcnum;

	u8 pcibridge_venकरोr;
	u16 pcibridge_venकरोrid;
	u16 pcibridge_deviceid;

	u8 num4bytes;

	u8 pcibridge_pciehdr_offset;
	u8 pcibridge_linkctrlreg;

	bool amd_l1_patch;
पूर्ण;

काष्ठा rtl_pci_priv अणु
	काष्ठा bt_coexist_info bt_coexist;
	काष्ठा rtl_led_ctl ledctl;
	काष्ठा rtl_pci dev;
	काष्ठा mp_adapter ndis_adapter;
पूर्ण;

#घोषणा rtl_pcipriv(hw)		(((काष्ठा rtl_pci_priv *)(rtl_priv(hw))->priv))
#घोषणा rtl_pcidev(pcipriv)	(&((pcipriv)->dev))

पूर्णांक rtl_pci_reset_trx_ring(काष्ठा ieee80211_hw *hw);

बाह्य स्थिर काष्ठा rtl_पूर्णांकf_ops rtl_pci_ops;

पूर्णांक rtl_pci_probe(काष्ठा pci_dev *pdev,
		  स्थिर काष्ठा pci_device_id *id);
व्योम rtl_pci_disconnect(काष्ठा pci_dev *pdev);
#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक rtl_pci_suspend(काष्ठा device *dev);
पूर्णांक rtl_pci_resume(काष्ठा device *dev);
#पूर्ण_अगर /* CONFIG_PM_SLEEP */
अटल अंतरभूत u8 pci_पढ़ो8_sync(काष्ठा rtl_priv *rtlpriv, u32 addr)
अणु
	वापस पढ़ोb((u8 __iomem *)rtlpriv->io.pci_mem_start + addr);
पूर्ण

अटल अंतरभूत u16 pci_पढ़ो16_sync(काष्ठा rtl_priv *rtlpriv, u32 addr)
अणु
	वापस पढ़ोw((u8 __iomem *)rtlpriv->io.pci_mem_start + addr);
पूर्ण

अटल अंतरभूत u32 pci_पढ़ो32_sync(काष्ठा rtl_priv *rtlpriv, u32 addr)
अणु
	वापस पढ़ोl((u8 __iomem *)rtlpriv->io.pci_mem_start + addr);
पूर्ण

अटल अंतरभूत व्योम pci_ग_लिखो8_async(काष्ठा rtl_priv *rtlpriv, u32 addr, u8 val)
अणु
	ग_लिखोb(val, (u8 __iomem *)rtlpriv->io.pci_mem_start + addr);
पूर्ण

अटल अंतरभूत व्योम pci_ग_लिखो16_async(काष्ठा rtl_priv *rtlpriv,
				     u32 addr, u16 val)
अणु
	ग_लिखोw(val, (u8 __iomem *)rtlpriv->io.pci_mem_start + addr);
पूर्ण

अटल अंतरभूत व्योम pci_ग_लिखो32_async(काष्ठा rtl_priv *rtlpriv,
				     u32 addr, u32 val)
अणु
	ग_लिखोl(val, (u8 __iomem *)rtlpriv->io.pci_mem_start + addr);
पूर्ण

अटल अंतरभूत u16 calc_fअगरo_space(u16 rp, u16 wp, u16 size)
अणु
	अगर (rp <= wp)
		वापस size - 1 + rp - wp;
	वापस rp - wp - 1;
पूर्ण

#पूर्ण_अगर
