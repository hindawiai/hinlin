<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2012-2020, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#अगर_अघोषित _MEI_INTERFACE_H_
#घोषणा _MEI_INTERFACE_H_

#समावेश <linux/irqवापस.h>
#समावेश <linux/pci.h>
#समावेश <linux/mei.h>

#समावेश "mei_dev.h"
#समावेश "client.h"

/*
 * mei_cfg - mei device configuration
 *
 * @fw_status: FW status
 * @quirk_probe: device exclusion quirk
 * @kind: MEI head kind
 * @dma_size: device DMA buffers size
 * @fw_ver_supported: is fw version retrievable from FW
 * @hw_trc_supported: करोes the hw support trc रेजिस्टर
 */
काष्ठा mei_cfg अणु
	स्थिर काष्ठा mei_fw_status fw_status;
	bool (*quirk_probe)(स्थिर काष्ठा pci_dev *pdev);
	स्थिर अक्षर *kind;
	माप_प्रकार dma_size[DMA_DSCR_NUM];
	u32 fw_ver_supported:1;
	u32 hw_trc_supported:1;
पूर्ण;


#घोषणा MEI_PCI_DEVICE(dev, cfg) \
	.venकरोr = PCI_VENDOR_ID_INTEL, .device = (dev), \
	.subvenकरोr = PCI_ANY_ID, .subdevice = PCI_ANY_ID, \
	.driver_data = (kernel_uदीर्घ_t)(cfg),

#घोषणा MEI_ME_RPM_TIMEOUT    500 /* ms */

/**
 * काष्ठा mei_me_hw - me hw specअगरic data
 *
 * @cfg: per device generation config and ops
 * @mem_addr: io memory address
 * @irq: irq number
 * @pg_state: घातer gating state
 * @d0i3_supported: di03 support
 * @hbuf_depth: depth of hardware host/ग_लिखो buffer in slots
 * @पढ़ो_fws: पढ़ो FW status रेजिस्टर handler
 */
काष्ठा mei_me_hw अणु
	स्थिर काष्ठा mei_cfg *cfg;
	व्योम __iomem *mem_addr;
	पूर्णांक irq;
	क्रमागत mei_pg_state pg_state;
	bool d0i3_supported;
	u8 hbuf_depth;
	पूर्णांक (*पढ़ो_fws)(स्थिर काष्ठा mei_device *dev, पूर्णांक where, u32 *val);
पूर्ण;

#घोषणा to_me_hw(dev) (काष्ठा mei_me_hw *)((dev)->hw)

/**
 * क्रमागत mei_cfg_idx - indices to platक्रमm specअगरic configurations.
 *
 * Note: has to be synchronized with mei_cfg_list[]
 *
 * @MEI_ME_UNDEF_CFG:      Lower sentinel.
 * @MEI_ME_ICH_CFG:        I/O Controller Hub legacy devices.
 * @MEI_ME_ICH10_CFG:      I/O Controller Hub platक्रमms Gen10
 * @MEI_ME_PCH6_CFG:       Platक्रमm Controller Hub platक्रमms (Gen6).
 * @MEI_ME_PCH7_CFG:       Platक्रमm Controller Hub platक्रमms (Gen7).
 * @MEI_ME_PCH_CPT_PBG_CFG:Platक्रमm Controller Hub workstations
 *                         with quirk क्रम Node Manager exclusion.
 * @MEI_ME_PCH8_CFG:       Platक्रमm Controller Hub Gen8 and newer
 *                         client platक्रमms.
 * @MEI_ME_PCH8_ITOUCH_CFG:Platक्रमm Controller Hub Gen8 and newer
 *                         client platक्रमms (iTouch).
 * @MEI_ME_PCH8_SPS_4_CFG: Platक्रमm Controller Hub Gen8 and newer
 *                         servers platक्रमms with quirk क्रम
 *                         SPS firmware exclusion.
 * @MEI_ME_PCH12_CFG:      Platक्रमm Controller Hub Gen12 and newer
 * @MEI_ME_PCH12_SPS_4_CFG:Platक्रमm Controller Hub Gen12 up to 4.0
 *                         servers platक्रमms with quirk क्रम
 *                         SPS firmware exclusion.
 * @MEI_ME_PCH12_SPS_CFG:  Platक्रमm Controller Hub Gen12 5.0 and newer
 *                         servers platक्रमms with quirk क्रम
 *                         SPS firmware exclusion.
 * @MEI_ME_PCH15_CFG:      Platक्रमm Controller Hub Gen15 and newer
 * @MEI_ME_PCH15_SPS_CFG:  Platक्रमm Controller Hub Gen15 and newer
 *                         servers platक्रमms with quirk क्रम
 *                         SPS firmware exclusion.
 * @MEI_ME_NUM_CFG:        Upper Sentinel.
 */
क्रमागत mei_cfg_idx अणु
	MEI_ME_UNDEF_CFG,
	MEI_ME_ICH_CFG,
	MEI_ME_ICH10_CFG,
	MEI_ME_PCH6_CFG,
	MEI_ME_PCH7_CFG,
	MEI_ME_PCH_CPT_PBG_CFG,
	MEI_ME_PCH8_CFG,
	MEI_ME_PCH8_ITOUCH_CFG,
	MEI_ME_PCH8_SPS_4_CFG,
	MEI_ME_PCH12_CFG,
	MEI_ME_PCH12_SPS_4_CFG,
	MEI_ME_PCH12_SPS_CFG,
	MEI_ME_PCH12_SPS_ITOUCH_CFG,
	MEI_ME_PCH15_CFG,
	MEI_ME_PCH15_SPS_CFG,
	MEI_ME_NUM_CFG,
पूर्ण;

स्थिर काष्ठा mei_cfg *mei_me_get_cfg(kernel_uदीर्घ_t idx);

काष्ठा mei_device *mei_me_dev_init(काष्ठा device *parent,
				   स्थिर काष्ठा mei_cfg *cfg);

पूर्णांक mei_me_pg_enter_sync(काष्ठा mei_device *dev);
पूर्णांक mei_me_pg_निकास_sync(काष्ठा mei_device *dev);

irqवापस_t mei_me_irq_quick_handler(पूर्णांक irq, व्योम *dev_id);
irqवापस_t mei_me_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *dev_id);

#पूर्ण_अगर /* _MEI_INTERFACE_H_ */
