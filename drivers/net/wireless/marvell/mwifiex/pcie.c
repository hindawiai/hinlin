<शैली गुरु>
/*
 * NXP Wireless LAN device driver: PCIE specअगरic handling
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश <linux/firmware.h>

#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "11n.h"
#समावेश "pcie.h"

#घोषणा PCIE_VERSION	"1.0"
#घोषणा DRV_NAME        "Marvell mwifiex PCIe"

अटल काष्ठा mwअगरiex_अगर_ops pcie_ops;

अटल स्थिर काष्ठा mwअगरiex_pcie_card_reg mwअगरiex_reg_8766 = अणु
	.cmd_addr_lo = PCIE_SCRATCH_0_REG,
	.cmd_addr_hi = PCIE_SCRATCH_1_REG,
	.cmd_size = PCIE_SCRATCH_2_REG,
	.fw_status = PCIE_SCRATCH_3_REG,
	.cmdrsp_addr_lo = PCIE_SCRATCH_4_REG,
	.cmdrsp_addr_hi = PCIE_SCRATCH_5_REG,
	.tx_rdptr = PCIE_SCRATCH_6_REG,
	.tx_wrptr = PCIE_SCRATCH_7_REG,
	.rx_rdptr = PCIE_SCRATCH_8_REG,
	.rx_wrptr = PCIE_SCRATCH_9_REG,
	.evt_rdptr = PCIE_SCRATCH_10_REG,
	.evt_wrptr = PCIE_SCRATCH_11_REG,
	.drv_rdy = PCIE_SCRATCH_12_REG,
	.tx_start_ptr = 0,
	.tx_mask = MWIFIEX_TXBD_MASK,
	.tx_wrap_mask = 0,
	.rx_mask = MWIFIEX_RXBD_MASK,
	.rx_wrap_mask = 0,
	.tx_rollover_ind = MWIFIEX_BD_FLAG_ROLLOVER_IND,
	.rx_rollover_ind = MWIFIEX_BD_FLAG_ROLLOVER_IND,
	.evt_rollover_ind = MWIFIEX_BD_FLAG_ROLLOVER_IND,
	.ring_flag_sop = 0,
	.ring_flag_eop = 0,
	.ring_flag_xs_sop = 0,
	.ring_flag_xs_eop = 0,
	.ring_tx_start_ptr = 0,
	.pfu_enabled = 0,
	.sleep_cookie = 1,
	.msix_support = 0,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_pcie_card_reg mwअगरiex_reg_8897 = अणु
	.cmd_addr_lo = PCIE_SCRATCH_0_REG,
	.cmd_addr_hi = PCIE_SCRATCH_1_REG,
	.cmd_size = PCIE_SCRATCH_2_REG,
	.fw_status = PCIE_SCRATCH_3_REG,
	.cmdrsp_addr_lo = PCIE_SCRATCH_4_REG,
	.cmdrsp_addr_hi = PCIE_SCRATCH_5_REG,
	.tx_rdptr = PCIE_RD_DATA_PTR_Q0_Q1,
	.tx_wrptr = PCIE_WR_DATA_PTR_Q0_Q1,
	.rx_rdptr = PCIE_WR_DATA_PTR_Q0_Q1,
	.rx_wrptr = PCIE_RD_DATA_PTR_Q0_Q1,
	.evt_rdptr = PCIE_SCRATCH_10_REG,
	.evt_wrptr = PCIE_SCRATCH_11_REG,
	.drv_rdy = PCIE_SCRATCH_12_REG,
	.tx_start_ptr = 16,
	.tx_mask = 0x03FF0000,
	.tx_wrap_mask = 0x07FF0000,
	.rx_mask = 0x000003FF,
	.rx_wrap_mask = 0x000007FF,
	.tx_rollover_ind = MWIFIEX_BD_FLAG_TX_ROLLOVER_IND,
	.rx_rollover_ind = MWIFIEX_BD_FLAG_RX_ROLLOVER_IND,
	.evt_rollover_ind = MWIFIEX_BD_FLAG_EVT_ROLLOVER_IND,
	.ring_flag_sop = MWIFIEX_BD_FLAG_SOP,
	.ring_flag_eop = MWIFIEX_BD_FLAG_EOP,
	.ring_flag_xs_sop = MWIFIEX_BD_FLAG_XS_SOP,
	.ring_flag_xs_eop = MWIFIEX_BD_FLAG_XS_EOP,
	.ring_tx_start_ptr = MWIFIEX_BD_FLAG_TX_START_PTR,
	.pfu_enabled = 1,
	.sleep_cookie = 0,
	.fw_dump_ctrl = PCIE_SCRATCH_13_REG,
	.fw_dump_start = PCIE_SCRATCH_14_REG,
	.fw_dump_end = 0xcff,
	.fw_dump_host_पढ़ोy = 0xee,
	.fw_dump_पढ़ो_करोne = 0xfe,
	.msix_support = 0,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_pcie_card_reg mwअगरiex_reg_8997 = अणु
	.cmd_addr_lo = PCIE_SCRATCH_0_REG,
	.cmd_addr_hi = PCIE_SCRATCH_1_REG,
	.cmd_size = PCIE_SCRATCH_2_REG,
	.fw_status = PCIE_SCRATCH_3_REG,
	.cmdrsp_addr_lo = PCIE_SCRATCH_4_REG,
	.cmdrsp_addr_hi = PCIE_SCRATCH_5_REG,
	.tx_rdptr = 0xC1A4,
	.tx_wrptr = 0xC174,
	.rx_rdptr = 0xC174,
	.rx_wrptr = 0xC1A4,
	.evt_rdptr = PCIE_SCRATCH_10_REG,
	.evt_wrptr = PCIE_SCRATCH_11_REG,
	.drv_rdy = PCIE_SCRATCH_12_REG,
	.tx_start_ptr = 16,
	.tx_mask = 0x0FFF0000,
	.tx_wrap_mask = 0x1FFF0000,
	.rx_mask = 0x00000FFF,
	.rx_wrap_mask = 0x00001FFF,
	.tx_rollover_ind = BIT(28),
	.rx_rollover_ind = BIT(12),
	.evt_rollover_ind = MWIFIEX_BD_FLAG_EVT_ROLLOVER_IND,
	.ring_flag_sop = MWIFIEX_BD_FLAG_SOP,
	.ring_flag_eop = MWIFIEX_BD_FLAG_EOP,
	.ring_flag_xs_sop = MWIFIEX_BD_FLAG_XS_SOP,
	.ring_flag_xs_eop = MWIFIEX_BD_FLAG_XS_EOP,
	.ring_tx_start_ptr = MWIFIEX_BD_FLAG_TX_START_PTR,
	.pfu_enabled = 1,
	.sleep_cookie = 0,
	.fw_dump_ctrl = PCIE_SCRATCH_13_REG,
	.fw_dump_start = PCIE_SCRATCH_14_REG,
	.fw_dump_end = 0xcff,
	.fw_dump_host_पढ़ोy = 0xcc,
	.fw_dump_पढ़ो_करोne = 0xdd,
	.msix_support = 0,
पूर्ण;

अटल काष्ठा memory_type_mapping mem_type_mapping_tbl_w8897[] = अणु
	अणु"ITCM", शून्य, 0, 0xF0पूर्ण,
	अणु"DTCM", शून्य, 0, 0xF1पूर्ण,
	अणु"SQRAM", शून्य, 0, 0xF2पूर्ण,
	अणु"IRAM", शून्य, 0, 0xF3पूर्ण,
	अणु"APU", शून्य, 0, 0xF4पूर्ण,
	अणु"CIU", शून्य, 0, 0xF5पूर्ण,
	अणु"ICU", शून्य, 0, 0xF6पूर्ण,
	अणु"MAC", शून्य, 0, 0xF7पूर्ण,
पूर्ण;

अटल काष्ठा memory_type_mapping mem_type_mapping_tbl_w8997[] = अणु
	अणु"DUMP", शून्य, 0, 0xDDपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_pcie_device mwअगरiex_pcie8766 = अणु
	.reg            = &mwअगरiex_reg_8766,
	.blksz_fw_dl = MWIFIEX_PCIE_BLOCK_SIZE_FW_DNLD,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.can_dump_fw = false,
	.can_ext_scan = true,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_pcie_device mwअगरiex_pcie8897 = अणु
	.reg            = &mwअगरiex_reg_8897,
	.blksz_fw_dl = MWIFIEX_PCIE_BLOCK_SIZE_FW_DNLD,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K,
	.can_dump_fw = true,
	.mem_type_mapping_tbl = mem_type_mapping_tbl_w8897,
	.num_mem_types = ARRAY_SIZE(mem_type_mapping_tbl_w8897),
	.can_ext_scan = true,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_pcie_device mwअगरiex_pcie8997 = अणु
	.reg            = &mwअगरiex_reg_8997,
	.blksz_fw_dl = MWIFIEX_PCIE_BLOCK_SIZE_FW_DNLD,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K,
	.can_dump_fw = true,
	.mem_type_mapping_tbl = mem_type_mapping_tbl_w8997,
	.num_mem_types = ARRAY_SIZE(mem_type_mapping_tbl_w8997),
	.can_ext_scan = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mwअगरiex_pcie_of_match_table[] = अणु
	अणु .compatible = "pci11ab,2b42" पूर्ण,
	अणु .compatible = "pci1b4b,2b42" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक mwअगरiex_pcie_probe_of(काष्ठा device *dev)
अणु
	अगर (!of_match_node(mwअगरiex_pcie_of_match_table, dev->of_node)) अणु
		dev_err(dev, "required compatible string missing\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_pcie_work(काष्ठा work_काष्ठा *work);

अटल पूर्णांक
mwअगरiex_map_pci_memory(काष्ठा mwअगरiex_adapter *adapter, काष्ठा sk_buff *skb,
		       माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	काष्ठा mwअगरiex_dma_mapping mapping;

	mapping.addr = dma_map_single(&card->dev->dev, skb->data, size, flags);
	अगर (dma_mapping_error(&card->dev->dev, mapping.addr)) अणु
		mwअगरiex_dbg(adapter, ERROR, "failed to map pci memory!\n");
		वापस -1;
	पूर्ण
	mapping.len = size;
	mwअगरiex_store_mapping(skb, &mapping);
	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_unmap_pci_memory(काष्ठा mwअगरiex_adapter *adapter,
				     काष्ठा sk_buff *skb, पूर्णांक flags)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	काष्ठा mwअगरiex_dma_mapping mapping;

	mwअगरiex_get_mapping(skb, &mapping);
	dma_unmap_single(&card->dev->dev, mapping.addr, mapping.len, flags);
पूर्ण

/*
 * This function ग_लिखोs data पूर्णांकo PCIE card रेजिस्टर.
 */
अटल पूर्णांक mwअगरiex_ग_लिखो_reg(काष्ठा mwअगरiex_adapter *adapter, पूर्णांक reg, u32 data)
अणु
	काष्ठा pcie_service_card *card = adapter->card;

	ioग_लिखो32(data, card->pci_mmap1 + reg);

	वापस 0;
पूर्ण

/* This function पढ़ोs data from PCIE card रेजिस्टर.
 */
अटल पूर्णांक mwअगरiex_पढ़ो_reg(काष्ठा mwअगरiex_adapter *adapter, पूर्णांक reg, u32 *data)
अणु
	काष्ठा pcie_service_card *card = adapter->card;

	*data = ioपढ़ो32(card->pci_mmap1 + reg);
	अगर (*data == 0xffffffff)
		वापस 0xffffffff;

	वापस 0;
पूर्ण

/* This function पढ़ोs u8 data from PCIE card रेजिस्टर. */
अटल पूर्णांक mwअगरiex_पढ़ो_reg_byte(काष्ठा mwअगरiex_adapter *adapter,
				 पूर्णांक reg, u8 *data)
अणु
	काष्ठा pcie_service_card *card = adapter->card;

	*data = ioपढ़ो8(card->pci_mmap1 + reg);

	वापस 0;
पूर्ण

/*
 * This function पढ़ोs sleep cookie and checks अगर FW is पढ़ोy
 */
अटल bool mwअगरiex_pcie_ok_to_access_hw(काष्ठा mwअगरiex_adapter *adapter)
अणु
	u32 cookie_value;
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	अगर (!reg->sleep_cookie)
		वापस true;

	अगर (card->sleep_cookie_vbase) अणु
		cookie_value = get_unaligned_le32(card->sleep_cookie_vbase);
		mwअगरiex_dbg(adapter, INFO,
			    "info: ACCESS_HW: sleep cookie=0x%x\n",
			    cookie_value);
		अगर (cookie_value == FW_AWAKE_COOKIE)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * Kernel needs to suspend all functions separately. Thereक्रमe all
 * रेजिस्टरed functions must have drivers with suspend and resume
 * methods. Failing that the kernel simply हटाओs the whole card.
 *
 * If alपढ़ोy not suspended, this function allocates and sends a host
 * sleep activate request to the firmware and turns off the traffic.
 */
अटल पूर्णांक mwअगरiex_pcie_suspend(काष्ठा device *dev)
अणु
	काष्ठा mwअगरiex_adapter *adapter;
	काष्ठा pcie_service_card *card = dev_get_drvdata(dev);


	/* Might still be loading firmware */
	रुको_क्रम_completion(&card->fw_करोne);

	adapter = card->adapter;
	अगर (!adapter) अणु
		dev_err(dev, "adapter is not valid\n");
		वापस 0;
	पूर्ण

	mwअगरiex_enable_wake(adapter);

	/* Enable the Host Sleep */
	अगर (!mwअगरiex_enable_hs(adapter)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "cmd: failed to suspend\n");
		clear_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);
		mwअगरiex_disable_wake(adapter);
		वापस -EFAULT;
	पूर्ण

	flush_workqueue(adapter->workqueue);

	/* Indicate device suspended */
	set_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);
	clear_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);

	वापस 0;
पूर्ण

/*
 * Kernel needs to suspend all functions separately. Thereक्रमe all
 * रेजिस्टरed functions must have drivers with suspend and resume
 * methods. Failing that the kernel simply हटाओs the whole card.
 *
 * If alपढ़ोy not resumed, this function turns on the traffic and
 * sends a host sleep cancel request to the firmware.
 */
अटल पूर्णांक mwअगरiex_pcie_resume(काष्ठा device *dev)
अणु
	काष्ठा mwअगरiex_adapter *adapter;
	काष्ठा pcie_service_card *card = dev_get_drvdata(dev);


	अगर (!card->adapter) अणु
		dev_err(dev, "adapter structure is not valid\n");
		वापस 0;
	पूर्ण

	adapter = card->adapter;

	अगर (!test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags)) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "Device already resumed\n");
		वापस 0;
	पूर्ण

	clear_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);

	mwअगरiex_cancel_hs(mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA),
			  MWIFIEX_ASYNC_CMD);
	mwअगरiex_disable_wake(adapter);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * This function probes an mwअगरiex device and रेजिस्टरs it. It allocates
 * the card काष्ठाure, enables PCIE function number and initiates the
 * device registration and initialization procedure by adding a logical
 * पूर्णांकerface.
 */
अटल पूर्णांक mwअगरiex_pcie_probe(काष्ठा pci_dev *pdev,
					स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा pcie_service_card *card;
	पूर्णांक ret;

	pr_debug("info: vendor=0x%4.04X device=0x%4.04X rev=%d\n",
		 pdev->venकरोr, pdev->device, pdev->revision);

	card = devm_kzalloc(&pdev->dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	init_completion(&card->fw_करोne);

	card->dev = pdev;

	अगर (ent->driver_data) अणु
		काष्ठा mwअगरiex_pcie_device *data = (व्योम *)ent->driver_data;
		card->pcie.reg = data->reg;
		card->pcie.blksz_fw_dl = data->blksz_fw_dl;
		card->pcie.tx_buf_size = data->tx_buf_size;
		card->pcie.can_dump_fw = data->can_dump_fw;
		card->pcie.mem_type_mapping_tbl = data->mem_type_mapping_tbl;
		card->pcie.num_mem_types = data->num_mem_types;
		card->pcie.can_ext_scan = data->can_ext_scan;
		INIT_WORK(&card->work, mwअगरiex_pcie_work);
	पूर्ण

	/* device tree node parsing and platक्रमm specअगरic configuration*/
	अगर (pdev->dev.of_node) अणु
		ret = mwअगरiex_pcie_probe_of(&pdev->dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (mwअगरiex_add_card(card, &card->fw_करोne, &pcie_ops,
			     MWIFIEX_PCIE, &pdev->dev)) अणु
		pr_err("%s failed\n", __func__);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function हटाओs the पूर्णांकerface and मुक्तs up the card काष्ठाure.
 */
अटल व्योम mwअगरiex_pcie_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pcie_service_card *card;
	काष्ठा mwअगरiex_adapter *adapter;
	काष्ठा mwअगरiex_निजी *priv;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg;
	u32 fw_status;

	card = pci_get_drvdata(pdev);

	रुको_क्रम_completion(&card->fw_करोne);

	adapter = card->adapter;
	अगर (!adapter || !adapter->priv_num)
		वापस;

	reg = card->pcie.reg;
	अगर (reg)
		mwअगरiex_पढ़ो_reg(adapter, reg->fw_status, &fw_status);
	अन्यथा
		fw_status = -1;

	अगर (fw_status == FIRMWARE_READY_PCIE && !adapter->mfg_mode) अणु
		mwअगरiex_deauthenticate_all(adapter);

		priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

		mwअगरiex_disable_स्वतः_ds(priv);

		mwअगरiex_init_shutकरोwn_fw(priv, MWIFIEX_FUNC_SHUTDOWN);
	पूर्ण

	mwअगरiex_हटाओ_card(adapter);
पूर्ण

अटल व्योम mwअगरiex_pcie_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	mwअगरiex_pcie_हटाओ(pdev);

	वापस;
पूर्ण

अटल व्योम mwअगरiex_pcie_coredump(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा pcie_service_card *card;

	pdev = container_of(dev, काष्ठा pci_dev, dev);
	card = pci_get_drvdata(pdev);

	अगर (!test_and_set_bit(MWIFIEX_IFACE_WORK_DEVICE_DUMP,
			      &card->work_flags))
		schedule_work(&card->work);
पूर्ण

अटल स्थिर काष्ठा pci_device_id mwअगरiex_ids[] = अणु
	अणु
		PCIE_VENDOR_ID_MARVELL, PCIE_DEVICE_ID_MARVELL_88W8766P,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		.driver_data = (अचिन्हित दीर्घ)&mwअगरiex_pcie8766,
	पूर्ण,
	अणु
		PCIE_VENDOR_ID_MARVELL, PCIE_DEVICE_ID_MARVELL_88W8897,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		.driver_data = (अचिन्हित दीर्घ)&mwअगरiex_pcie8897,
	पूर्ण,
	अणु
		PCIE_VENDOR_ID_MARVELL, PCIE_DEVICE_ID_MARVELL_88W8997,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		.driver_data = (अचिन्हित दीर्घ)&mwअगरiex_pcie8997,
	पूर्ण,
	अणु
		PCIE_VENDOR_ID_V2_MARVELL, PCIE_DEVICE_ID_MARVELL_88W8997,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		.driver_data = (अचिन्हित दीर्घ)&mwअगरiex_pcie8997,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, mwअगरiex_ids);

/*
 * Cleanup all software without cleaning anything related to PCIe and HW.
 */
अटल व्योम mwअगरiex_pcie_reset_prepare(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pcie_service_card *card = pci_get_drvdata(pdev);
	काष्ठा mwअगरiex_adapter *adapter = card->adapter;

	अगर (!adapter) अणु
		dev_err(&pdev->dev, "%s: adapter structure is not valid\n",
			__func__);
		वापस;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "%s: vendor=0x%4.04x device=0x%4.04x rev=%d Pre-FLR\n",
		    __func__, pdev->venकरोr, pdev->device, pdev->revision);

	mwअगरiex_shutकरोwn_sw(adapter);
	clear_bit(MWIFIEX_IFACE_WORK_DEVICE_DUMP, &card->work_flags);
	clear_bit(MWIFIEX_IFACE_WORK_CARD_RESET, &card->work_flags);
	mwअगरiex_dbg(adapter, INFO, "%s, successful\n", __func__);

	card->pci_reset_ongoing = true;
पूर्ण

/*
 * Kernel stores and restores PCIe function context beक्रमe and after perक्रमming
 * FLR respectively. Reconfigure the software and firmware including firmware
 * reकरोwnload.
 */
अटल व्योम mwअगरiex_pcie_reset_करोne(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pcie_service_card *card = pci_get_drvdata(pdev);
	काष्ठा mwअगरiex_adapter *adapter = card->adapter;
	पूर्णांक ret;

	अगर (!adapter) अणु
		dev_err(&pdev->dev, "%s: adapter structure is not valid\n",
			__func__);
		वापस;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "%s: vendor=0x%4.04x device=0x%4.04x rev=%d Post-FLR\n",
		    __func__, pdev->venकरोr, pdev->device, pdev->revision);

	ret = mwअगरiex_reinit_sw(adapter);
	अगर (ret)
		dev_err(&pdev->dev, "reinit failed: %d\n", ret);
	अन्यथा
		mwअगरiex_dbg(adapter, INFO, "%s, successful\n", __func__);

	card->pci_reset_ongoing = false;
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers mwअगरiex_pcie_err_handler = अणु
	.reset_prepare		= mwअगरiex_pcie_reset_prepare,
	.reset_करोne		= mwअगरiex_pcie_reset_करोne,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
/* Power Management Hooks */
अटल SIMPLE_DEV_PM_OPS(mwअगरiex_pcie_pm_ops, mwअगरiex_pcie_suspend,
				mwअगरiex_pcie_resume);
#पूर्ण_अगर

/* PCI Device Driver */
अटल काष्ठा pci_driver mwअगरiex_pcie = अणु
	.name     = "mwifiex_pcie",
	.id_table = mwअगरiex_ids,
	.probe    = mwअगरiex_pcie_probe,
	.हटाओ   = mwअगरiex_pcie_हटाओ,
	.driver   = अणु
		.coredump = mwअगरiex_pcie_coredump,
#अगर_घोषित CONFIG_PM_SLEEP
		.pm = &mwअगरiex_pcie_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.shutकरोwn = mwअगरiex_pcie_shutकरोwn,
	.err_handler = &mwअगरiex_pcie_err_handler,
पूर्ण;

/*
 * This function adds delay loop to ensure FW is awake beक्रमe proceeding.
 */
अटल व्योम mwअगरiex_pcie_dev_wakeup_delay(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक i = 0;

	जबतक (mwअगरiex_pcie_ok_to_access_hw(adapter)) अणु
		i++;
		usleep_range(10, 20);
		/* 50ms max रुको */
		अगर (i == 5000)
			अवरोध;
	पूर्ण

	वापस;
पूर्ण

अटल व्योम mwअगरiex_delay_क्रम_sleep_cookie(काष्ठा mwअगरiex_adapter *adapter,
					   u32 max_delay_loop_cnt)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	u8 *buffer;
	u32 sleep_cookie, count;
	काष्ठा sk_buff *cmdrsp = card->cmdrsp_buf;

	क्रम (count = 0; count < max_delay_loop_cnt; count++) अणु
		dma_sync_single_क्रम_cpu(&card->dev->dev,
					MWIFIEX_SKB_DMA_ADDR(cmdrsp),
					माप(sleep_cookie), DMA_FROM_DEVICE);
		buffer = cmdrsp->data;
		sleep_cookie = get_unaligned_le32(buffer);

		अगर (sleep_cookie == MWIFIEX_DEF_SLEEP_COOKIE) अणु
			mwअगरiex_dbg(adapter, INFO,
				    "sleep cookie found at count %d\n", count);
			अवरोध;
		पूर्ण
		dma_sync_single_क्रम_device(&card->dev->dev,
					   MWIFIEX_SKB_DMA_ADDR(cmdrsp),
					   माप(sleep_cookie),
					   DMA_FROM_DEVICE);
		usleep_range(20, 30);
	पूर्ण

	अगर (count >= max_delay_loop_cnt)
		mwअगरiex_dbg(adapter, INFO,
			    "max count reached while accessing sleep cookie\n");
पूर्ण

/* This function wakes up the card by पढ़ोing fw_status रेजिस्टर. */
अटल पूर्णांक mwअगरiex_pm_wakeup_card(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	mwअगरiex_dbg(adapter, EVENT,
		    "event: Wakeup device...\n");

	अगर (reg->sleep_cookie)
		mwअगरiex_pcie_dev_wakeup_delay(adapter);

	/* Accessing fw_status रेजिस्टर will wakeup device */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->fw_status, FIRMWARE_READY_PCIE)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Writing fw_status register failed\n");
		वापस -1;
	पूर्ण

	अगर (reg->sleep_cookie) अणु
		mwअगरiex_pcie_dev_wakeup_delay(adapter);
		mwअगरiex_dbg(adapter, INFO,
			    "PCIE wakeup: Setting PS_STATE_AWAKE\n");
		adapter->ps_state = PS_STATE_AWAKE;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function is called after the card has woken up.
 *
 * The card configuration रेजिस्टर is reset.
 */
अटल पूर्णांक mwअगरiex_pm_wakeup_card_complete(काष्ठा mwअगरiex_adapter *adapter)
अणु
	mwअगरiex_dbg(adapter, CMD,
		    "cmd: Wakeup device completed\n");

	वापस 0;
पूर्ण

/*
 * This function disables the host पूर्णांकerrupt.
 *
 * The host पूर्णांकerrupt mask is पढ़ो, the disable bit is reset and
 * written back to the card host पूर्णांकerrupt mask रेजिस्टर.
 */
अटल पूर्णांक mwअगरiex_pcie_disable_host_पूर्णांक(काष्ठा mwअगरiex_adapter *adapter)
अणु
	अगर (mwअगरiex_pcie_ok_to_access_hw(adapter)) अणु
		अगर (mwअगरiex_ग_लिखो_reg(adapter, PCIE_HOST_INT_MASK,
				      0x00000000)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Disable host interrupt failed\n");
			वापस -1;
		पूर्ण
	पूर्ण

	atomic_set(&adapter->tx_hw_pending, 0);
	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_pcie_disable_host_पूर्णांक_noerr(काष्ठा mwअगरiex_adapter *adapter)
अणु
	WARN_ON(mwअगरiex_pcie_disable_host_पूर्णांक(adapter));
पूर्ण

/*
 * This function enables the host पूर्णांकerrupt.
 *
 * The host पूर्णांकerrupt enable mask is written to the card
 * host पूर्णांकerrupt mask रेजिस्टर.
 */
अटल पूर्णांक mwअगरiex_pcie_enable_host_पूर्णांक(काष्ठा mwअगरiex_adapter *adapter)
अणु
	अगर (mwअगरiex_pcie_ok_to_access_hw(adapter)) अणु
		/* Simply ग_लिखो the mask to the रेजिस्टर */
		अगर (mwअगरiex_ग_लिखो_reg(adapter, PCIE_HOST_INT_MASK,
				      HOST_INTR_MASK)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Enable host interrupt failed\n");
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function initializes TX buffer ring descriptors
 */
अटल पूर्णांक mwअगरiex_init_txq_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	काष्ठा mwअगरiex_pcie_buf_desc *desc;
	काष्ठा mwअगरiex_pfu_buf_desc *desc2;
	पूर्णांक i;

	क्रम (i = 0; i < MWIFIEX_MAX_TXRX_BD; i++) अणु
		card->tx_buf_list[i] = शून्य;
		अगर (reg->pfu_enabled) अणु
			card->txbd_ring[i] = (व्योम *)card->txbd_ring_vbase +
					     (माप(*desc2) * i);
			desc2 = card->txbd_ring[i];
			स_रखो(desc2, 0, माप(*desc2));
		पूर्ण अन्यथा अणु
			card->txbd_ring[i] = (व्योम *)card->txbd_ring_vbase +
					     (माप(*desc) * i);
			desc = card->txbd_ring[i];
			स_रखो(desc, 0, माप(*desc));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* This function initializes RX buffer ring descriptors. Each SKB is allocated
 * here and after mapping PCI memory, its physical address is asचिन्हित to
 * PCIE Rx buffer descriptor's physical address.
 */
अटल पूर्णांक mwअगरiex_init_rxq_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	काष्ठा sk_buff *skb;
	काष्ठा mwअगरiex_pcie_buf_desc *desc;
	काष्ठा mwअगरiex_pfu_buf_desc *desc2;
	dma_addr_t buf_pa;
	पूर्णांक i;

	क्रम (i = 0; i < MWIFIEX_MAX_TXRX_BD; i++) अणु
		/* Allocate skb here so that firmware can DMA data from it */
		skb = mwअगरiex_alloc_dma_align_buf(MWIFIEX_RX_DATA_BUF_SIZE,
						  GFP_KERNEL);
		अगर (!skb) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Unable to allocate skb for RX ring.\n");
			kमुक्त(card->rxbd_ring_vbase);
			वापस -ENOMEM;
		पूर्ण

		अगर (mwअगरiex_map_pci_memory(adapter, skb,
					   MWIFIEX_RX_DATA_BUF_SIZE,
					   DMA_FROM_DEVICE))
			वापस -1;

		buf_pa = MWIFIEX_SKB_DMA_ADDR(skb);

		mwअगरiex_dbg(adapter, INFO,
			    "info: RX ring: skb=%p len=%d data=%p buf_pa=%#x:%x\n",
			    skb, skb->len, skb->data, (u32)buf_pa,
			    (u32)((u64)buf_pa >> 32));

		card->rx_buf_list[i] = skb;
		अगर (reg->pfu_enabled) अणु
			card->rxbd_ring[i] = (व्योम *)card->rxbd_ring_vbase +
					     (माप(*desc2) * i);
			desc2 = card->rxbd_ring[i];
			desc2->paddr = buf_pa;
			desc2->len = (u16)skb->len;
			desc2->frag_len = (u16)skb->len;
			desc2->flags = reg->ring_flag_eop | reg->ring_flag_sop;
			desc2->offset = 0;
		पूर्ण अन्यथा अणु
			card->rxbd_ring[i] = (व्योम *)(card->rxbd_ring_vbase +
					     (माप(*desc) * i));
			desc = card->rxbd_ring[i];
			desc->paddr = buf_pa;
			desc->len = (u16)skb->len;
			desc->flags = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* This function initializes event buffer ring descriptors. Each SKB is
 * allocated here and after mapping PCI memory, its physical address is asचिन्हित
 * to PCIE Rx buffer descriptor's physical address
 */
अटल पूर्णांक mwअगरiex_pcie_init_evt_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	काष्ठा mwअगरiex_evt_buf_desc *desc;
	काष्ठा sk_buff *skb;
	dma_addr_t buf_pa;
	पूर्णांक i;

	क्रम (i = 0; i < MWIFIEX_MAX_EVT_BD; i++) अणु
		/* Allocate skb here so that firmware can DMA data from it */
		skb = dev_alloc_skb(MAX_EVENT_SIZE);
		अगर (!skb) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Unable to allocate skb for EVENT buf.\n");
			kमुक्त(card->evtbd_ring_vbase);
			वापस -ENOMEM;
		पूर्ण
		skb_put(skb, MAX_EVENT_SIZE);

		अगर (mwअगरiex_map_pci_memory(adapter, skb, MAX_EVENT_SIZE,
					   DMA_FROM_DEVICE)) अणु
			kमुक्त_skb(skb);
			kमुक्त(card->evtbd_ring_vbase);
			वापस -1;
		पूर्ण

		buf_pa = MWIFIEX_SKB_DMA_ADDR(skb);

		mwअगरiex_dbg(adapter, EVENT,
			    "info: EVT ring: skb=%p len=%d data=%p buf_pa=%#x:%x\n",
			    skb, skb->len, skb->data, (u32)buf_pa,
			    (u32)((u64)buf_pa >> 32));

		card->evt_buf_list[i] = skb;
		card->evtbd_ring[i] = (व्योम *)(card->evtbd_ring_vbase +
				      (माप(*desc) * i));
		desc = card->evtbd_ring[i];
		desc->paddr = buf_pa;
		desc->len = (u16)skb->len;
		desc->flags = 0;
	पूर्ण

	वापस 0;
पूर्ण

/* This function cleans up TX buffer rings. If any of the buffer list has valid
 * SKB address, associated SKB is मुक्तd.
 */
अटल व्योम mwअगरiex_cleanup_txq_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	काष्ठा sk_buff *skb;
	काष्ठा mwअगरiex_pcie_buf_desc *desc;
	काष्ठा mwअगरiex_pfu_buf_desc *desc2;
	पूर्णांक i;

	क्रम (i = 0; i < MWIFIEX_MAX_TXRX_BD; i++) अणु
		अगर (reg->pfu_enabled) अणु
			desc2 = card->txbd_ring[i];
			अगर (card->tx_buf_list[i]) अणु
				skb = card->tx_buf_list[i];
				mwअगरiex_unmap_pci_memory(adapter, skb,
							 DMA_TO_DEVICE);
				dev_kमुक्त_skb_any(skb);
			पूर्ण
			स_रखो(desc2, 0, माप(*desc2));
		पूर्ण अन्यथा अणु
			desc = card->txbd_ring[i];
			अगर (card->tx_buf_list[i]) अणु
				skb = card->tx_buf_list[i];
				mwअगरiex_unmap_pci_memory(adapter, skb,
							 DMA_TO_DEVICE);
				dev_kमुक्त_skb_any(skb);
			पूर्ण
			स_रखो(desc, 0, माप(*desc));
		पूर्ण
		card->tx_buf_list[i] = शून्य;
	पूर्ण

	atomic_set(&adapter->tx_hw_pending, 0);
	वापस;
पूर्ण

/* This function cleans up RX buffer rings. If any of the buffer list has valid
 * SKB address, associated SKB is मुक्तd.
 */
अटल व्योम mwअगरiex_cleanup_rxq_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	काष्ठा mwअगरiex_pcie_buf_desc *desc;
	काष्ठा mwअगरiex_pfu_buf_desc *desc2;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < MWIFIEX_MAX_TXRX_BD; i++) अणु
		अगर (reg->pfu_enabled) अणु
			desc2 = card->rxbd_ring[i];
			अगर (card->rx_buf_list[i]) अणु
				skb = card->rx_buf_list[i];
				mwअगरiex_unmap_pci_memory(adapter, skb,
							 DMA_FROM_DEVICE);
				dev_kमुक्त_skb_any(skb);
			पूर्ण
			स_रखो(desc2, 0, माप(*desc2));
		पूर्ण अन्यथा अणु
			desc = card->rxbd_ring[i];
			अगर (card->rx_buf_list[i]) अणु
				skb = card->rx_buf_list[i];
				mwअगरiex_unmap_pci_memory(adapter, skb,
							 DMA_FROM_DEVICE);
				dev_kमुक्त_skb_any(skb);
			पूर्ण
			स_रखो(desc, 0, माप(*desc));
		पूर्ण
		card->rx_buf_list[i] = शून्य;
	पूर्ण

	वापस;
पूर्ण

/* This function cleans up event buffer rings. If any of the buffer list has
 * valid SKB address, associated SKB is मुक्तd.
 */
अटल व्योम mwअगरiex_cleanup_evt_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	काष्ठा mwअगरiex_evt_buf_desc *desc;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < MWIFIEX_MAX_EVT_BD; i++) अणु
		desc = card->evtbd_ring[i];
		अगर (card->evt_buf_list[i]) अणु
			skb = card->evt_buf_list[i];
			mwअगरiex_unmap_pci_memory(adapter, skb,
						 DMA_FROM_DEVICE);
			dev_kमुक्त_skb_any(skb);
		पूर्ण
		card->evt_buf_list[i] = शून्य;
		स_रखो(desc, 0, माप(*desc));
	पूर्ण

	वापस;
पूर्ण

/* This function creates buffer descriptor ring क्रम TX
 */
अटल पूर्णांक mwअगरiex_pcie_create_txbd_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	/*
	 * driver मुख्यtaines the ग_लिखो poपूर्णांकer and firmware मुख्यtaines the पढ़ो
	 * poपूर्णांकer. The ग_लिखो poपूर्णांकer starts at 0 (zero) जबतक the पढ़ो poपूर्णांकer
	 * starts at zero with rollover bit set
	 */
	card->txbd_wrptr = 0;

	अगर (reg->pfu_enabled)
		card->txbd_rdptr = 0;
	अन्यथा
		card->txbd_rdptr |= reg->tx_rollover_ind;

	/* allocate shared memory क्रम the BD ring and भागide the same in to
	   several descriptors */
	अगर (reg->pfu_enabled)
		card->txbd_ring_size = माप(काष्ठा mwअगरiex_pfu_buf_desc) *
				       MWIFIEX_MAX_TXRX_BD;
	अन्यथा
		card->txbd_ring_size = माप(काष्ठा mwअगरiex_pcie_buf_desc) *
				       MWIFIEX_MAX_TXRX_BD;

	mwअगरiex_dbg(adapter, INFO,
		    "info: txbd_ring: Allocating %d bytes\n",
		    card->txbd_ring_size);
	card->txbd_ring_vbase = dma_alloc_coherent(&card->dev->dev,
						   card->txbd_ring_size,
						   &card->txbd_ring_pbase,
						   GFP_KERNEL);
	अगर (!card->txbd_ring_vbase) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "allocate coherent memory (%d bytes) failed!\n",
			    card->txbd_ring_size);
		वापस -ENOMEM;
	पूर्ण

	mwअगरiex_dbg(adapter, DATA,
		    "info: txbd_ring - base: %p, pbase: %#x:%x, len: %#x\n",
		    card->txbd_ring_vbase, (u32)card->txbd_ring_pbase,
		    (u32)((u64)card->txbd_ring_pbase >> 32),
		    card->txbd_ring_size);

	वापस mwअगरiex_init_txq_ring(adapter);
पूर्ण

अटल पूर्णांक mwअगरiex_pcie_delete_txbd_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	mwअगरiex_cleanup_txq_ring(adapter);

	अगर (card->txbd_ring_vbase)
		dma_मुक्त_coherent(&card->dev->dev, card->txbd_ring_size,
				  card->txbd_ring_vbase,
				  card->txbd_ring_pbase);
	card->txbd_ring_size = 0;
	card->txbd_wrptr = 0;
	card->txbd_rdptr = 0 | reg->tx_rollover_ind;
	card->txbd_ring_vbase = शून्य;
	card->txbd_ring_pbase = 0;

	वापस 0;
पूर्ण

/*
 * This function creates buffer descriptor ring क्रम RX
 */
अटल पूर्णांक mwअगरiex_pcie_create_rxbd_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	/*
	 * driver मुख्यtaines the पढ़ो poपूर्णांकer and firmware मुख्यtaines the ग_लिखो
	 * poपूर्णांकer. The ग_लिखो poपूर्णांकer starts at 0 (zero) जबतक the पढ़ो poपूर्णांकer
	 * starts at zero with rollover bit set
	 */
	card->rxbd_wrptr = 0;
	card->rxbd_rdptr = reg->rx_rollover_ind;

	अगर (reg->pfu_enabled)
		card->rxbd_ring_size = माप(काष्ठा mwअगरiex_pfu_buf_desc) *
				       MWIFIEX_MAX_TXRX_BD;
	अन्यथा
		card->rxbd_ring_size = माप(काष्ठा mwअगरiex_pcie_buf_desc) *
				       MWIFIEX_MAX_TXRX_BD;

	mwअगरiex_dbg(adapter, INFO,
		    "info: rxbd_ring: Allocating %d bytes\n",
		    card->rxbd_ring_size);
	card->rxbd_ring_vbase = dma_alloc_coherent(&card->dev->dev,
						   card->rxbd_ring_size,
						   &card->rxbd_ring_pbase,
						   GFP_KERNEL);
	अगर (!card->rxbd_ring_vbase) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "allocate coherent memory (%d bytes) failed!\n",
			    card->rxbd_ring_size);
		वापस -ENOMEM;
	पूर्ण

	mwअगरiex_dbg(adapter, DATA,
		    "info: rxbd_ring - base: %p, pbase: %#x:%x, len: %#x\n",
		    card->rxbd_ring_vbase, (u32)card->rxbd_ring_pbase,
		    (u32)((u64)card->rxbd_ring_pbase >> 32),
		    card->rxbd_ring_size);

	वापस mwअगरiex_init_rxq_ring(adapter);
पूर्ण

/*
 * This function deletes Buffer descriptor ring क्रम RX
 */
अटल पूर्णांक mwअगरiex_pcie_delete_rxbd_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	mwअगरiex_cleanup_rxq_ring(adapter);

	अगर (card->rxbd_ring_vbase)
		dma_मुक्त_coherent(&card->dev->dev, card->rxbd_ring_size,
				  card->rxbd_ring_vbase,
				  card->rxbd_ring_pbase);
	card->rxbd_ring_size = 0;
	card->rxbd_wrptr = 0;
	card->rxbd_rdptr = 0 | reg->rx_rollover_ind;
	card->rxbd_ring_vbase = शून्य;
	card->rxbd_ring_pbase = 0;

	वापस 0;
पूर्ण

/*
 * This function creates buffer descriptor ring क्रम Events
 */
अटल पूर्णांक mwअगरiex_pcie_create_evtbd_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	/*
	 * driver मुख्यtaines the पढ़ो poपूर्णांकer and firmware मुख्यtaines the ग_लिखो
	 * poपूर्णांकer. The ग_लिखो poपूर्णांकer starts at 0 (zero) जबतक the पढ़ो poपूर्णांकer
	 * starts at zero with rollover bit set
	 */
	card->evtbd_wrptr = 0;
	card->evtbd_rdptr = reg->evt_rollover_ind;

	card->evtbd_ring_size = माप(काष्ठा mwअगरiex_evt_buf_desc) *
				MWIFIEX_MAX_EVT_BD;

	mwअगरiex_dbg(adapter, INFO,
		    "info: evtbd_ring: Allocating %d bytes\n",
		    card->evtbd_ring_size);
	card->evtbd_ring_vbase = dma_alloc_coherent(&card->dev->dev,
						    card->evtbd_ring_size,
						    &card->evtbd_ring_pbase,
						    GFP_KERNEL);
	अगर (!card->evtbd_ring_vbase) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "allocate coherent memory (%d bytes) failed!\n",
			    card->evtbd_ring_size);
		वापस -ENOMEM;
	पूर्ण

	mwअगरiex_dbg(adapter, EVENT,
		    "info: CMDRSP/EVT bd_ring - base: %p pbase: %#x:%x len: %#x\n",
		    card->evtbd_ring_vbase, (u32)card->evtbd_ring_pbase,
		    (u32)((u64)card->evtbd_ring_pbase >> 32),
		    card->evtbd_ring_size);

	वापस mwअगरiex_pcie_init_evt_ring(adapter);
पूर्ण

/*
 * This function deletes Buffer descriptor ring क्रम Events
 */
अटल पूर्णांक mwअगरiex_pcie_delete_evtbd_ring(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	mwअगरiex_cleanup_evt_ring(adapter);

	अगर (card->evtbd_ring_vbase)
		dma_मुक्त_coherent(&card->dev->dev, card->evtbd_ring_size,
				  card->evtbd_ring_vbase,
				  card->evtbd_ring_pbase);
	card->evtbd_wrptr = 0;
	card->evtbd_rdptr = 0 | reg->evt_rollover_ind;
	card->evtbd_ring_size = 0;
	card->evtbd_ring_vbase = शून्य;
	card->evtbd_ring_pbase = 0;

	वापस 0;
पूर्ण

/*
 * This function allocates a buffer क्रम CMDRSP
 */
अटल पूर्णांक mwअगरiex_pcie_alloc_cmdrsp_buf(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	काष्ठा sk_buff *skb;

	/* Allocate memory क्रम receiving command response data */
	skb = dev_alloc_skb(MWIFIEX_UPLD_SIZE);
	अगर (!skb) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Unable to allocate skb for command response data.\n");
		वापस -ENOMEM;
	पूर्ण
	skb_put(skb, MWIFIEX_UPLD_SIZE);
	अगर (mwअगरiex_map_pci_memory(adapter, skb, MWIFIEX_UPLD_SIZE,
				   DMA_FROM_DEVICE)) अणु
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	card->cmdrsp_buf = skb;

	वापस 0;
पूर्ण

/*
 * This function deletes a buffer क्रम CMDRSP
 */
अटल पूर्णांक mwअगरiex_pcie_delete_cmdrsp_buf(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card;

	अगर (!adapter)
		वापस 0;

	card = adapter->card;

	अगर (card && card->cmdrsp_buf) अणु
		mwअगरiex_unmap_pci_memory(adapter, card->cmdrsp_buf,
					 DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(card->cmdrsp_buf);
		card->cmdrsp_buf = शून्य;
	पूर्ण

	अगर (card && card->cmd_buf) अणु
		mwअगरiex_unmap_pci_memory(adapter, card->cmd_buf,
					 DMA_TO_DEVICE);
		dev_kमुक्त_skb_any(card->cmd_buf);
		card->cmd_buf = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function allocates a buffer क्रम sleep cookie
 */
अटल पूर्णांक mwअगरiex_pcie_alloc_sleep_cookie_buf(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	u32 पंचांगp;

	card->sleep_cookie_vbase = dma_alloc_coherent(&card->dev->dev,
						      माप(u32),
						      &card->sleep_cookie_pbase,
						      GFP_KERNEL);
	अगर (!card->sleep_cookie_vbase) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "dma_alloc_coherent failed!\n");
		वापस -ENOMEM;
	पूर्ण
	/* Init val of Sleep Cookie */
	पंचांगp = FW_AWAKE_COOKIE;
	put_unaligned(पंचांगp, card->sleep_cookie_vbase);

	mwअगरiex_dbg(adapter, INFO,
		    "alloc_scook: sleep cookie=0x%x\n",
		    get_unaligned(card->sleep_cookie_vbase));

	वापस 0;
पूर्ण

/*
 * This function deletes buffer क्रम sleep cookie
 */
अटल पूर्णांक mwअगरiex_pcie_delete_sleep_cookie_buf(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card;

	अगर (!adapter)
		वापस 0;

	card = adapter->card;

	अगर (card && card->sleep_cookie_vbase) अणु
		dma_मुक्त_coherent(&card->dev->dev, माप(u32),
				  card->sleep_cookie_vbase,
				  card->sleep_cookie_pbase);
		card->sleep_cookie_vbase = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/* This function flushes the TX buffer descriptor ring
 * This function defined as handler is also called जबतक cleaning TXRX
 * during disconnect/ bss stop.
 */
अटल पूर्णांक mwअगरiex_clean_pcie_ring_buf(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;

	अगर (!mwअगरiex_pcie_txbd_empty(card, card->txbd_rdptr)) अणु
		card->txbd_flush = 1;
		/* ग_लिखो poपूर्णांकer alपढ़ोy set at last send
		 * send dnld-rdy पूर्णांकr again, रुको क्रम completion.
		 */
		अगर (mwअगरiex_ग_लिखो_reg(adapter, PCIE_CPU_INT_EVENT,
				      CPU_INTR_DNLD_RDY)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "failed to assert dnld-rdy interrupt.\n");
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function unmaps and मुक्तs करोwnloaded data buffer
 */
अटल पूर्णांक mwअगरiex_pcie_send_data_complete(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sk_buff *skb;
	u32 wrकरोneidx, rdptr, num_tx_buffs, unmap_count = 0;
	काष्ठा mwअगरiex_pcie_buf_desc *desc;
	काष्ठा mwअगरiex_pfu_buf_desc *desc2;
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	अगर (!mwअगरiex_pcie_ok_to_access_hw(adapter))
		mwअगरiex_pm_wakeup_card(adapter);

	/* Read the TX ring पढ़ो poपूर्णांकer set by firmware */
	अगर (mwअगरiex_पढ़ो_reg(adapter, reg->tx_rdptr, &rdptr)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "SEND COMP: failed to read reg->tx_rdptr\n");
		वापस -1;
	पूर्ण

	mwअगरiex_dbg(adapter, DATA,
		    "SEND COMP: rdptr_prev=0x%x, rdptr=0x%x\n",
		    card->txbd_rdptr, rdptr);

	num_tx_buffs = MWIFIEX_MAX_TXRX_BD << reg->tx_start_ptr;
	/* मुक्त from previous txbd_rdptr to current txbd_rdptr */
	जबतक (((card->txbd_rdptr & reg->tx_mask) !=
		(rdptr & reg->tx_mask)) ||
	       ((card->txbd_rdptr & reg->tx_rollover_ind) !=
		(rdptr & reg->tx_rollover_ind))) अणु
		wrकरोneidx = (card->txbd_rdptr & reg->tx_mask) >>
			    reg->tx_start_ptr;

		skb = card->tx_buf_list[wrकरोneidx];

		अगर (skb) अणु
			mwअगरiex_dbg(adapter, DATA,
				    "SEND COMP: Detach skb %p at txbd_rdidx=%d\n",
				    skb, wrकरोneidx);
			mwअगरiex_unmap_pci_memory(adapter, skb,
						 DMA_TO_DEVICE);

			unmap_count++;

			अगर (card->txbd_flush)
				mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0,
							    -1);
			अन्यथा
				mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, 0);
			atomic_dec(&adapter->tx_hw_pending);
		पूर्ण

		card->tx_buf_list[wrकरोneidx] = शून्य;

		अगर (reg->pfu_enabled) अणु
			desc2 = card->txbd_ring[wrकरोneidx];
			स_रखो(desc2, 0, माप(*desc2));
		पूर्ण अन्यथा अणु
			desc = card->txbd_ring[wrकरोneidx];
			स_रखो(desc, 0, माप(*desc));
		पूर्ण
		चयन (card->dev->device) अणु
		हाल PCIE_DEVICE_ID_MARVELL_88W8766P:
			card->txbd_rdptr++;
			अवरोध;
		हाल PCIE_DEVICE_ID_MARVELL_88W8897:
		हाल PCIE_DEVICE_ID_MARVELL_88W8997:
			card->txbd_rdptr += reg->ring_tx_start_ptr;
			अवरोध;
		पूर्ण


		अगर ((card->txbd_rdptr & reg->tx_mask) == num_tx_buffs)
			card->txbd_rdptr = ((card->txbd_rdptr &
					     reg->tx_rollover_ind) ^
					     reg->tx_rollover_ind);
	पूर्ण

	अगर (unmap_count)
		adapter->data_sent = false;

	अगर (card->txbd_flush) अणु
		अगर (mwअगरiex_pcie_txbd_empty(card, card->txbd_rdptr))
			card->txbd_flush = 0;
		अन्यथा
			mwअगरiex_clean_pcie_ring_buf(adapter);
	पूर्ण

	वापस 0;
पूर्ण

/* This function sends data buffer to device. First 4 bytes of payload
 * are filled with payload length and payload type. Then this payload
 * is mapped to PCI device memory. Tx ring poपूर्णांकers are advanced accordingly.
 * Download पढ़ोy पूर्णांकerrupt to FW is deffered अगर Tx ring is not full and
 * additional payload can be accomodated.
 * Caller must ensure tx_param parameter to this function is not शून्य.
 */
अटल पूर्णांक
mwअगरiex_pcie_send_data(काष्ठा mwअगरiex_adapter *adapter, काष्ठा sk_buff *skb,
		       काष्ठा mwअगरiex_tx_param *tx_param)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	u32 wrindx, num_tx_buffs, rx_val;
	पूर्णांक ret;
	dma_addr_t buf_pa;
	काष्ठा mwअगरiex_pcie_buf_desc *desc = शून्य;
	काष्ठा mwअगरiex_pfu_buf_desc *desc2 = शून्य;

	अगर (!(skb->data && skb->len)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s(): invalid parameter <%p, %#x>\n",
			    __func__, skb->data, skb->len);
		वापस -1;
	पूर्ण

	अगर (!mwअगरiex_pcie_ok_to_access_hw(adapter))
		mwअगरiex_pm_wakeup_card(adapter);

	num_tx_buffs = MWIFIEX_MAX_TXRX_BD << reg->tx_start_ptr;
	mwअगरiex_dbg(adapter, DATA,
		    "info: SEND DATA: <Rd: %#x, Wr: %#x>\n",
		card->txbd_rdptr, card->txbd_wrptr);
	अगर (mwअगरiex_pcie_txbd_not_full(card)) अणु
		u8 *payload;

		adapter->data_sent = true;
		payload = skb->data;
		put_unaligned_le16((u16)skb->len, payload + 0);
		put_unaligned_le16(MWIFIEX_TYPE_DATA, payload + 2);

		अगर (mwअगरiex_map_pci_memory(adapter, skb, skb->len,
					   DMA_TO_DEVICE))
			वापस -1;

		wrindx = (card->txbd_wrptr & reg->tx_mask) >> reg->tx_start_ptr;
		buf_pa = MWIFIEX_SKB_DMA_ADDR(skb);
		card->tx_buf_list[wrindx] = skb;
		atomic_inc(&adapter->tx_hw_pending);

		अगर (reg->pfu_enabled) अणु
			desc2 = card->txbd_ring[wrindx];
			desc2->paddr = buf_pa;
			desc2->len = (u16)skb->len;
			desc2->frag_len = (u16)skb->len;
			desc2->offset = 0;
			desc2->flags = MWIFIEX_BD_FLAG_FIRST_DESC |
					 MWIFIEX_BD_FLAG_LAST_DESC;
		पूर्ण अन्यथा अणु
			desc = card->txbd_ring[wrindx];
			desc->paddr = buf_pa;
			desc->len = (u16)skb->len;
			desc->flags = MWIFIEX_BD_FLAG_FIRST_DESC |
				      MWIFIEX_BD_FLAG_LAST_DESC;
		पूर्ण

		चयन (card->dev->device) अणु
		हाल PCIE_DEVICE_ID_MARVELL_88W8766P:
			card->txbd_wrptr++;
			अवरोध;
		हाल PCIE_DEVICE_ID_MARVELL_88W8897:
		हाल PCIE_DEVICE_ID_MARVELL_88W8997:
			card->txbd_wrptr += reg->ring_tx_start_ptr;
			अवरोध;
		पूर्ण

		अगर ((card->txbd_wrptr & reg->tx_mask) == num_tx_buffs)
			card->txbd_wrptr = ((card->txbd_wrptr &
						reg->tx_rollover_ind) ^
						reg->tx_rollover_ind);

		rx_val = card->rxbd_rdptr & reg->rx_wrap_mask;
		/* Write the TX ring ग_लिखो poपूर्णांकer in to reg->tx_wrptr */
		अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->tx_wrptr,
				      card->txbd_wrptr | rx_val)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "SEND DATA: failed to write reg->tx_wrptr\n");
			ret = -1;
			जाओ करोne_unmap;
		पूर्ण
		अगर ((mwअगरiex_pcie_txbd_not_full(card)) &&
		    tx_param->next_pkt_len) अणु
			/* have more packets and TxBD still can hold more */
			mwअगरiex_dbg(adapter, DATA,
				    "SEND DATA: delay dnld-rdy interrupt.\n");
			adapter->data_sent = false;
		पूर्ण अन्यथा अणु
			/* Send the TX पढ़ोy पूर्णांकerrupt */
			अगर (mwअगरiex_ग_लिखो_reg(adapter, PCIE_CPU_INT_EVENT,
					      CPU_INTR_DNLD_RDY)) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "SEND DATA: failed to assert dnld-rdy interrupt.\n");
				ret = -1;
				जाओ करोne_unmap;
			पूर्ण
		पूर्ण
		mwअगरiex_dbg(adapter, DATA,
			    "info: SEND DATA: Updated <Rd: %#x, Wr:\t"
			    "%#x> and sent packet to firmware successfully\n",
			    card->txbd_rdptr, card->txbd_wrptr);
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(adapter, DATA,
			    "info: TX Ring full, can't send packets to fw\n");
		adapter->data_sent = true;
		/* Send the TX पढ़ोy पूर्णांकerrupt */
		अगर (mwअगरiex_ग_लिखो_reg(adapter, PCIE_CPU_INT_EVENT,
				      CPU_INTR_DNLD_RDY))
			mwअगरiex_dbg(adapter, ERROR,
				    "SEND DATA: failed to assert door-bell intr\n");
		वापस -EBUSY;
	पूर्ण

	वापस -EINPROGRESS;
करोne_unmap:
	mwअगरiex_unmap_pci_memory(adapter, skb, DMA_TO_DEVICE);
	card->tx_buf_list[wrindx] = शून्य;
	atomic_dec(&adapter->tx_hw_pending);
	अगर (reg->pfu_enabled)
		स_रखो(desc2, 0, माप(*desc2));
	अन्यथा
		स_रखो(desc, 0, माप(*desc));

	वापस ret;
पूर्ण

/*
 * This function handles received buffer ring and
 * dispatches packets to upper
 */
अटल पूर्णांक mwअगरiex_pcie_process_recv_data(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	u32 wrptr, rd_index, tx_val;
	dma_addr_t buf_pa;
	पूर्णांक ret = 0;
	काष्ठा sk_buff *skb_पंचांगp = शून्य;
	काष्ठा mwअगरiex_pcie_buf_desc *desc;
	काष्ठा mwअगरiex_pfu_buf_desc *desc2;

	अगर (!mwअगरiex_pcie_ok_to_access_hw(adapter))
		mwअगरiex_pm_wakeup_card(adapter);

	/* Read the RX ring Write poपूर्णांकer set by firmware */
	अगर (mwअगरiex_पढ़ो_reg(adapter, reg->rx_wrptr, &wrptr)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "RECV DATA: failed to read reg->rx_wrptr\n");
		ret = -1;
		जाओ करोne;
	पूर्ण
	card->rxbd_wrptr = wrptr;

	जबतक (((wrptr & reg->rx_mask) !=
		(card->rxbd_rdptr & reg->rx_mask)) ||
	       ((wrptr & reg->rx_rollover_ind) ==
		(card->rxbd_rdptr & reg->rx_rollover_ind))) अणु
		काष्ठा sk_buff *skb_data;
		u16 rx_len;

		rd_index = card->rxbd_rdptr & reg->rx_mask;
		skb_data = card->rx_buf_list[rd_index];

		/* If skb allocation was failed earlier क्रम Rx packet,
		 * rx_buf_list[rd_index] would have been left with a शून्य.
		 */
		अगर (!skb_data)
			वापस -ENOMEM;

		mwअगरiex_unmap_pci_memory(adapter, skb_data, DMA_FROM_DEVICE);
		card->rx_buf_list[rd_index] = शून्य;

		/* Get data length from पूर्णांकerface header -
		 * first 2 bytes क्रम len, next 2 bytes is क्रम type
		 */
		rx_len = get_unaligned_le16(skb_data->data);
		अगर (WARN_ON(rx_len <= adapter->पूर्णांकf_hdr_len ||
			    rx_len > MWIFIEX_RX_DATA_BUF_SIZE)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Invalid RX len %d, Rd=%#x, Wr=%#x\n",
				    rx_len, card->rxbd_rdptr, wrptr);
			dev_kमुक्त_skb_any(skb_data);
		पूर्ण अन्यथा अणु
			skb_put(skb_data, rx_len);
			mwअगरiex_dbg(adapter, DATA,
				    "info: RECV DATA: Rd=%#x, Wr=%#x, Len=%d\n",
				    card->rxbd_rdptr, wrptr, rx_len);
			skb_pull(skb_data, adapter->पूर्णांकf_hdr_len);
			अगर (adapter->rx_work_enabled) अणु
				skb_queue_tail(&adapter->rx_data_q, skb_data);
				adapter->data_received = true;
				atomic_inc(&adapter->rx_pending);
			पूर्ण अन्यथा अणु
				mwअगरiex_handle_rx_packet(adapter, skb_data);
			पूर्ण
		पूर्ण

		skb_पंचांगp = mwअगरiex_alloc_dma_align_buf(MWIFIEX_RX_DATA_BUF_SIZE,
						      GFP_KERNEL);
		अगर (!skb_पंचांगp) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Unable to allocate skb.\n");
			वापस -ENOMEM;
		पूर्ण

		अगर (mwअगरiex_map_pci_memory(adapter, skb_पंचांगp,
					   MWIFIEX_RX_DATA_BUF_SIZE,
					   DMA_FROM_DEVICE))
			वापस -1;

		buf_pa = MWIFIEX_SKB_DMA_ADDR(skb_पंचांगp);

		mwअगरiex_dbg(adapter, INFO,
			    "RECV DATA: Attach new sk_buff %p at rxbd_rdidx=%d\n",
			    skb_पंचांगp, rd_index);
		card->rx_buf_list[rd_index] = skb_पंचांगp;

		अगर (reg->pfu_enabled) अणु
			desc2 = card->rxbd_ring[rd_index];
			desc2->paddr = buf_pa;
			desc2->len = skb_पंचांगp->len;
			desc2->frag_len = skb_पंचांगp->len;
			desc2->offset = 0;
			desc2->flags = reg->ring_flag_sop | reg->ring_flag_eop;
		पूर्ण अन्यथा अणु
			desc = card->rxbd_ring[rd_index];
			desc->paddr = buf_pa;
			desc->len = skb_पंचांगp->len;
			desc->flags = 0;
		पूर्ण

		अगर ((++card->rxbd_rdptr & reg->rx_mask) ==
							MWIFIEX_MAX_TXRX_BD) अणु
			card->rxbd_rdptr = ((card->rxbd_rdptr &
					     reg->rx_rollover_ind) ^
					     reg->rx_rollover_ind);
		पूर्ण
		mwअगरiex_dbg(adapter, DATA,
			    "info: RECV DATA: <Rd: %#x, Wr: %#x>\n",
			    card->rxbd_rdptr, wrptr);

		tx_val = card->txbd_wrptr & reg->tx_wrap_mask;
		/* Write the RX ring पढ़ो poपूर्णांकer in to reg->rx_rdptr */
		अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->rx_rdptr,
				      card->rxbd_rdptr | tx_val)) अणु
			mwअगरiex_dbg(adapter, DATA,
				    "RECV DATA: failed to write reg->rx_rdptr\n");
			ret = -1;
			जाओ करोne;
		पूर्ण

		/* Read the RX ring Write poपूर्णांकer set by firmware */
		अगर (mwअगरiex_पढ़ो_reg(adapter, reg->rx_wrptr, &wrptr)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "RECV DATA: failed to read reg->rx_wrptr\n");
			ret = -1;
			जाओ करोne;
		पूर्ण
		mwअगरiex_dbg(adapter, DATA,
			    "info: RECV DATA: Rcvd packet from fw successfully\n");
		card->rxbd_wrptr = wrptr;
	पूर्ण

करोne:
	वापस ret;
पूर्ण

/*
 * This function करोwnloads the boot command to device
 */
अटल पूर्णांक
mwअगरiex_pcie_send_boot_cmd(काष्ठा mwअगरiex_adapter *adapter, काष्ठा sk_buff *skb)
अणु
	dma_addr_t buf_pa;
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	अगर (!(skb->data && skb->len)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Invalid parameter in %s <%p. len %d>\n",
			    __func__, skb->data, skb->len);
		वापस -1;
	पूर्ण

	अगर (mwअगरiex_map_pci_memory(adapter, skb, skb->len, DMA_TO_DEVICE))
		वापस -1;

	buf_pa = MWIFIEX_SKB_DMA_ADDR(skb);

	/* Write the lower 32bits of the physical address to low command
	 * address scratch रेजिस्टर
	 */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->cmd_addr_lo, (u32)buf_pa)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: failed to write download command to boot code.\n",
			    __func__);
		mwअगरiex_unmap_pci_memory(adapter, skb, DMA_TO_DEVICE);
		वापस -1;
	पूर्ण

	/* Write the upper 32bits of the physical address to high command
	 * address scratch रेजिस्टर
	 */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->cmd_addr_hi,
			      (u32)((u64)buf_pa >> 32))) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: failed to write download command to boot code.\n",
			    __func__);
		mwअगरiex_unmap_pci_memory(adapter, skb, DMA_TO_DEVICE);
		वापस -1;
	पूर्ण

	/* Write the command length to cmd_size scratch रेजिस्टर */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->cmd_size, skb->len)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: failed to write command len to cmd_size scratch reg\n",
			    __func__);
		mwअगरiex_unmap_pci_memory(adapter, skb, DMA_TO_DEVICE);
		वापस -1;
	पूर्ण

	/* Ring the करोor bell */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, PCIE_CPU_INT_EVENT,
			      CPU_INTR_DOOR_BELL)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: failed to assert door-bell intr\n", __func__);
		mwअगरiex_unmap_pci_memory(adapter, skb, DMA_TO_DEVICE);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* This function init rx port in firmware which in turn enables to receive data
 * from device beक्रमe transmitting any packet.
 */
अटल पूर्णांक mwअगरiex_pcie_init_fw_port(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	पूर्णांक tx_wrap = card->txbd_wrptr & reg->tx_wrap_mask;

	/* Write the RX ring पढ़ो poपूर्णांकer in to reg->rx_rdptr */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->rx_rdptr, card->rxbd_rdptr |
			      tx_wrap)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "RECV DATA: failed to write reg->rx_rdptr\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/* This function करोwnloads commands to the device
 */
अटल पूर्णांक
mwअगरiex_pcie_send_cmd(काष्ठा mwअगरiex_adapter *adapter, काष्ठा sk_buff *skb)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	पूर्णांक ret = 0;
	dma_addr_t cmd_buf_pa, cmdrsp_buf_pa;
	u8 *payload = (u8 *)skb->data;

	अगर (!(skb->data && skb->len)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Invalid parameter in %s <%p, %#x>\n",
			    __func__, skb->data, skb->len);
		वापस -1;
	पूर्ण

	/* Make sure a command response buffer is available */
	अगर (!card->cmdrsp_buf) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "No response buffer available, send command failed\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!mwअगरiex_pcie_ok_to_access_hw(adapter))
		mwअगरiex_pm_wakeup_card(adapter);

	adapter->cmd_sent = true;

	put_unaligned_le16((u16)skb->len, &payload[0]);
	put_unaligned_le16(MWIFIEX_TYPE_CMD, &payload[2]);

	अगर (mwअगरiex_map_pci_memory(adapter, skb, skb->len, DMA_TO_DEVICE))
		वापस -1;

	card->cmd_buf = skb;
	/*
	 * Need to keep a reference, since core driver might मुक्त up this
	 * buffer beक्रमe we've unmapped it.
	 */
	skb_get(skb);

	/* To send a command, the driver will:
		1. Write the 64bit physical address of the data buffer to
		   cmd response address low  + cmd response address high
		2. Ring the करोor bell (i.e. set the करोor bell पूर्णांकerrupt)

		In response to करोor bell पूर्णांकerrupt, the firmware will perक्रमm
		the DMA of the command packet (first header to obtain the total
		length and then rest of the command).
	*/

	अगर (card->cmdrsp_buf) अणु
		cmdrsp_buf_pa = MWIFIEX_SKB_DMA_ADDR(card->cmdrsp_buf);
		/* Write the lower 32bits of the cmdrsp buffer physical
		   address */
		अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->cmdrsp_addr_lo,
				      (u32)cmdrsp_buf_pa)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Failed to write download cmd to boot code.\n");
			ret = -1;
			जाओ करोne;
		पूर्ण
		/* Write the upper 32bits of the cmdrsp buffer physical
		   address */
		अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->cmdrsp_addr_hi,
				      (u32)((u64)cmdrsp_buf_pa >> 32))) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Failed to write download cmd to boot code.\n");
			ret = -1;
			जाओ करोne;
		पूर्ण
	पूर्ण

	cmd_buf_pa = MWIFIEX_SKB_DMA_ADDR(card->cmd_buf);
	/* Write the lower 32bits of the physical address to reg->cmd_addr_lo */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->cmd_addr_lo,
			      (u32)cmd_buf_pa)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Failed to write download cmd to boot code.\n");
		ret = -1;
		जाओ करोne;
	पूर्ण
	/* Write the upper 32bits of the physical address to reg->cmd_addr_hi */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->cmd_addr_hi,
			      (u32)((u64)cmd_buf_pa >> 32))) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Failed to write download cmd to boot code.\n");
		ret = -1;
		जाओ करोne;
	पूर्ण

	/* Write the command length to reg->cmd_size */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->cmd_size,
			      card->cmd_buf->len)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Failed to write cmd len to reg->cmd_size\n");
		ret = -1;
		जाओ करोne;
	पूर्ण

	/* Ring the करोor bell */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, PCIE_CPU_INT_EVENT,
			      CPU_INTR_DOOR_BELL)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Failed to assert door-bell intr\n");
		ret = -1;
		जाओ करोne;
	पूर्ण

करोne:
	अगर (ret)
		adapter->cmd_sent = false;

	वापस 0;
पूर्ण

/*
 * This function handles command complete पूर्णांकerrupt
 */
अटल पूर्णांक mwअगरiex_pcie_process_cmd_complete(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	काष्ठा sk_buff *skb = card->cmdrsp_buf;
	पूर्णांक count = 0;
	u16 rx_len;

	mwअगरiex_dbg(adapter, CMD,
		    "info: Rx CMD Response\n");

	अगर (adapter->curr_cmd)
		mwअगरiex_unmap_pci_memory(adapter, skb, DMA_FROM_DEVICE);
	अन्यथा
		dma_sync_single_क्रम_cpu(&card->dev->dev,
					MWIFIEX_SKB_DMA_ADDR(skb),
					MWIFIEX_UPLD_SIZE, DMA_FROM_DEVICE);

	/* Unmap the command as a response has been received. */
	अगर (card->cmd_buf) अणु
		mwअगरiex_unmap_pci_memory(adapter, card->cmd_buf,
					 DMA_TO_DEVICE);
		dev_kमुक्त_skb_any(card->cmd_buf);
		card->cmd_buf = शून्य;
	पूर्ण

	rx_len = get_unaligned_le16(skb->data);
	skb_put(skb, MWIFIEX_UPLD_SIZE - skb->len);
	skb_trim(skb, rx_len);

	अगर (!adapter->curr_cmd) अणु
		अगर (adapter->ps_state == PS_STATE_SLEEP_CFM) अणु
			dma_sync_single_क्रम_device(&card->dev->dev,
						   MWIFIEX_SKB_DMA_ADDR(skb),
						   MWIFIEX_SLEEP_COOKIE_SIZE,
						   DMA_FROM_DEVICE);
			अगर (mwअगरiex_ग_लिखो_reg(adapter,
					      PCIE_CPU_INT_EVENT,
					      CPU_INTR_SLEEP_CFM_DONE)) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "Write register failed\n");
				वापस -1;
			पूर्ण
			mwअगरiex_delay_क्रम_sleep_cookie(adapter,
						       MWIFIEX_MAX_DELAY_COUNT);
			mwअगरiex_unmap_pci_memory(adapter, skb,
						 DMA_FROM_DEVICE);
			skb_pull(skb, adapter->पूर्णांकf_hdr_len);
			जबतक (reg->sleep_cookie && (count++ < 10) &&
			       mwअगरiex_pcie_ok_to_access_hw(adapter))
				usleep_range(50, 60);
			mwअगरiex_pcie_enable_host_पूर्णांक(adapter);
			mwअगरiex_process_sleep_confirm_resp(adapter, skb->data,
							   skb->len);
		पूर्ण अन्यथा अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "There is no command but got cmdrsp\n");
		पूर्ण
		स_नकल(adapter->upld_buf, skb->data,
		       min_t(u32, MWIFIEX_SIZE_OF_CMD_BUFFER, skb->len));
		skb_push(skb, adapter->पूर्णांकf_hdr_len);
		अगर (mwअगरiex_map_pci_memory(adapter, skb, MWIFIEX_UPLD_SIZE,
					   DMA_FROM_DEVICE))
			वापस -1;
	पूर्ण अन्यथा अगर (mwअगरiex_pcie_ok_to_access_hw(adapter)) अणु
		skb_pull(skb, adapter->पूर्णांकf_hdr_len);
		adapter->curr_cmd->resp_skb = skb;
		adapter->cmd_resp_received = true;
		/* Take the poपूर्णांकer and set it to CMD node and will
		   वापस in the response complete callback */
		card->cmdrsp_buf = शून्य;

		/* Clear the cmd-rsp buffer address in scratch रेजिस्टरs. This
		   will prevent firmware from writing to the same response
		   buffer again. */
		अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->cmdrsp_addr_lo, 0)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "cmd_done: failed to clear cmd_rsp_addr_lo\n");
			वापस -1;
		पूर्ण
		/* Write the upper 32bits of the cmdrsp buffer physical
		   address */
		अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->cmdrsp_addr_hi, 0)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "cmd_done: failed to clear cmd_rsp_addr_hi\n");
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Command Response processing complete handler
 */
अटल पूर्णांक mwअगरiex_pcie_cmdrsp_complete(काष्ठा mwअगरiex_adapter *adapter,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा pcie_service_card *card = adapter->card;

	अगर (skb) अणु
		card->cmdrsp_buf = skb;
		skb_push(card->cmdrsp_buf, adapter->पूर्णांकf_hdr_len);
		अगर (mwअगरiex_map_pci_memory(adapter, skb, MWIFIEX_UPLD_SIZE,
					   DMA_FROM_DEVICE))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function handles firmware event पढ़ोy पूर्णांकerrupt
 */
अटल पूर्णांक mwअगरiex_pcie_process_event_पढ़ोy(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	u32 rdptr = card->evtbd_rdptr & MWIFIEX_EVTBD_MASK;
	u32 wrptr, event;
	काष्ठा mwअगरiex_evt_buf_desc *desc;

	अगर (!mwअगरiex_pcie_ok_to_access_hw(adapter))
		mwअगरiex_pm_wakeup_card(adapter);

	अगर (adapter->event_received) अणु
		mwअगरiex_dbg(adapter, EVENT,
			    "info: Event being processed,\t"
			    "do not process this interrupt just yet\n");
		वापस 0;
	पूर्ण

	अगर (rdptr >= MWIFIEX_MAX_EVT_BD) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "info: Invalid read pointer...\n");
		वापस -1;
	पूर्ण

	/* Read the event ring ग_लिखो poपूर्णांकer set by firmware */
	अगर (mwअगरiex_पढ़ो_reg(adapter, reg->evt_wrptr, &wrptr)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "EventReady: failed to read reg->evt_wrptr\n");
		वापस -1;
	पूर्ण

	mwअगरiex_dbg(adapter, EVENT,
		    "info: EventReady: Initial <Rd: 0x%x, Wr: 0x%x>",
		    card->evtbd_rdptr, wrptr);
	अगर (((wrptr & MWIFIEX_EVTBD_MASK) != (card->evtbd_rdptr
					      & MWIFIEX_EVTBD_MASK)) ||
	    ((wrptr & reg->evt_rollover_ind) ==
	     (card->evtbd_rdptr & reg->evt_rollover_ind))) अणु
		काष्ठा sk_buff *skb_cmd;
		__le16 data_len = 0;
		u16 evt_len;

		mwअगरiex_dbg(adapter, INFO,
			    "info: Read Index: %d\n", rdptr);
		skb_cmd = card->evt_buf_list[rdptr];
		mwअगरiex_unmap_pci_memory(adapter, skb_cmd, DMA_FROM_DEVICE);

		/* Take the poपूर्णांकer and set it to event poपूर्णांकer in adapter
		   and will वापस back after event handling callback */
		card->evt_buf_list[rdptr] = शून्य;
		desc = card->evtbd_ring[rdptr];
		स_रखो(desc, 0, माप(*desc));

		event = get_unaligned_le32(
			&skb_cmd->data[adapter->पूर्णांकf_hdr_len]);
		adapter->event_cause = event;
		/* The first 4bytes will be the event transfer header
		   len is 2 bytes followed by type which is 2 bytes */
		स_नकल(&data_len, skb_cmd->data, माप(__le16));
		evt_len = le16_to_cpu(data_len);
		skb_trim(skb_cmd, evt_len);
		skb_pull(skb_cmd, adapter->पूर्णांकf_hdr_len);
		mwअगरiex_dbg(adapter, EVENT,
			    "info: Event length: %d\n", evt_len);

		अगर (evt_len > MWIFIEX_EVENT_HEADER_LEN &&
		    evt_len < MAX_EVENT_SIZE)
			स_नकल(adapter->event_body, skb_cmd->data +
			       MWIFIEX_EVENT_HEADER_LEN, evt_len -
			       MWIFIEX_EVENT_HEADER_LEN);

		adapter->event_received = true;
		adapter->event_skb = skb_cmd;

		/* Do not update the event पढ़ो poपूर्णांकer here, रुको till the
		   buffer is released. This is just to make things simpler,
		   we need to find a better method of managing these buffers.
		*/
	पूर्ण अन्यथा अणु
		अगर (mwअगरiex_ग_लिखो_reg(adapter, PCIE_CPU_INT_EVENT,
				      CPU_INTR_EVENT_DONE)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Write register failed\n");
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Event processing complete handler
 */
अटल पूर्णांक mwअगरiex_pcie_event_complete(काष्ठा mwअगरiex_adapter *adapter,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	पूर्णांक ret = 0;
	u32 rdptr = card->evtbd_rdptr & MWIFIEX_EVTBD_MASK;
	u32 wrptr;
	काष्ठा mwअगरiex_evt_buf_desc *desc;

	अगर (!skb)
		वापस 0;

	अगर (rdptr >= MWIFIEX_MAX_EVT_BD) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "event_complete: Invalid rdptr 0x%x\n",
			    rdptr);
		वापस -EINVAL;
	पूर्ण

	/* Read the event ring ग_लिखो poपूर्णांकer set by firmware */
	अगर (mwअगरiex_पढ़ो_reg(adapter, reg->evt_wrptr, &wrptr)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "event_complete: failed to read reg->evt_wrptr\n");
		वापस -1;
	पूर्ण

	अगर (!card->evt_buf_list[rdptr]) अणु
		skb_push(skb, adapter->पूर्णांकf_hdr_len);
		skb_put(skb, MAX_EVENT_SIZE - skb->len);
		अगर (mwअगरiex_map_pci_memory(adapter, skb,
					   MAX_EVENT_SIZE,
					   DMA_FROM_DEVICE))
			वापस -1;
		card->evt_buf_list[rdptr] = skb;
		desc = card->evtbd_ring[rdptr];
		desc->paddr = MWIFIEX_SKB_DMA_ADDR(skb);
		desc->len = (u16)skb->len;
		desc->flags = 0;
		skb = शून्य;
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "info: ERROR: buf still valid at index %d, <%p, %p>\n",
			    rdptr, card->evt_buf_list[rdptr], skb);
	पूर्ण

	अगर ((++card->evtbd_rdptr & MWIFIEX_EVTBD_MASK) == MWIFIEX_MAX_EVT_BD) अणु
		card->evtbd_rdptr = ((card->evtbd_rdptr &
					reg->evt_rollover_ind) ^
					reg->evt_rollover_ind);
	पूर्ण

	mwअगरiex_dbg(adapter, EVENT,
		    "info: Updated <Rd: 0x%x, Wr: 0x%x>",
		    card->evtbd_rdptr, wrptr);

	/* Write the event ring पढ़ो poपूर्णांकer in to reg->evt_rdptr */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->evt_rdptr,
			      card->evtbd_rdptr)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "event_complete: failed to read reg->evt_rdptr\n");
		वापस -1;
	पूर्ण

	mwअगरiex_dbg(adapter, EVENT,
		    "info: Check Events Again\n");
	ret = mwअगरiex_pcie_process_event_पढ़ोy(adapter);

	वापस ret;
पूर्ण

/* Combo firmware image is a combination of
 * (1) combo crc heaer, start with CMD5
 * (2) bluetooth image, start with CMD7, end with CMD6, data wrapped in CMD1.
 * (3) wअगरi image.
 *
 * This function bypass the header and bluetooth part, वापस
 * the offset of tail wअगरi-only part. If the image is alपढ़ोy wअगरi-only,
 * that is start with CMD1, वापस 0.
 */

अटल पूर्णांक mwअगरiex_extract_wअगरi_fw(काष्ठा mwअगरiex_adapter *adapter,
				   स्थिर व्योम *firmware, u32 firmware_len) अणु
	स्थिर काष्ठा mwअगरiex_fw_data *fwdata;
	u32 offset = 0, data_len, dnld_cmd;
	पूर्णांक ret = 0;
	bool cmd7_beक्रमe = false, first_cmd = false;

	जबतक (1) अणु
		/* Check क्रम पूर्णांकeger and buffer overflow */
		अगर (offset + माप(fwdata->header) < माप(fwdata->header) ||
		    offset + माप(fwdata->header) >= firmware_len) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "extract wifi-only fw failure!\n");
			ret = -1;
			जाओ करोne;
		पूर्ण

		fwdata = firmware + offset;
		dnld_cmd = le32_to_cpu(fwdata->header.dnld_cmd);
		data_len = le32_to_cpu(fwdata->header.data_length);

		/* Skip past header */
		offset += माप(fwdata->header);

		चयन (dnld_cmd) अणु
		हाल MWIFIEX_FW_DNLD_CMD_1:
			अगर (offset + data_len < data_len) अणु
				mwअगरiex_dbg(adapter, ERROR, "bad FW parse\n");
				ret = -1;
				जाओ करोne;
			पूर्ण

			/* Image start with cmd1, alपढ़ोy wअगरi-only firmware */
			अगर (!first_cmd) अणु
				mwअगरiex_dbg(adapter, MSG,
					    "input wifi-only firmware\n");
				वापस 0;
			पूर्ण

			अगर (!cmd7_beक्रमe) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "no cmd7 before cmd1!\n");
				ret = -1;
				जाओ करोne;
			पूर्ण
			offset += data_len;
			अवरोध;
		हाल MWIFIEX_FW_DNLD_CMD_5:
			first_cmd = true;
			/* Check क्रम पूर्णांकeger overflow */
			अगर (offset + data_len < data_len) अणु
				mwअगरiex_dbg(adapter, ERROR, "bad FW parse\n");
				ret = -1;
				जाओ करोne;
			पूर्ण
			offset += data_len;
			अवरोध;
		हाल MWIFIEX_FW_DNLD_CMD_6:
			first_cmd = true;
			/* Check क्रम पूर्णांकeger overflow */
			अगर (offset + data_len < data_len) अणु
				mwअगरiex_dbg(adapter, ERROR, "bad FW parse\n");
				ret = -1;
				जाओ करोne;
			पूर्ण
			offset += data_len;
			अगर (offset >= firmware_len) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "extract wifi-only fw failure!\n");
				ret = -1;
			पूर्ण अन्यथा अणु
				ret = offset;
			पूर्ण
			जाओ करोne;
		हाल MWIFIEX_FW_DNLD_CMD_7:
			first_cmd = true;
			cmd7_beक्रमe = true;
			अवरोध;
		शेष:
			mwअगरiex_dbg(adapter, ERROR, "unknown dnld_cmd %d\n",
				    dnld_cmd);
			ret = -1;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	वापस ret;
पूर्ण

/*
 * This function करोwnloads the firmware to the card.
 *
 * Firmware is करोwnloaded to the card in blocks. Every block करोwnload
 * is tested क्रम CRC errors, and retried a number of बार beक्रमe
 * वापसing failure.
 */
अटल पूर्णांक mwअगरiex_prog_fw_w_helper(काष्ठा mwअगरiex_adapter *adapter,
				    काष्ठा mwअगरiex_fw_image *fw)
अणु
	पूर्णांक ret;
	u8 *firmware = fw->fw_buf;
	u32 firmware_len = fw->fw_len;
	u32 offset = 0;
	काष्ठा sk_buff *skb;
	u32 txlen, tx_blocks = 0, tries, len, val;
	u32 block_retry_cnt = 0;
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	अगर (!firmware || !firmware_len) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "No firmware image found! Terminating download\n");
		वापस -1;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "info: Downloading FW image (%d bytes)\n",
		    firmware_len);

	अगर (mwअगरiex_pcie_disable_host_पूर्णांक(adapter)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: Disabling interrupts failed.\n", __func__);
		वापस -1;
	पूर्ण

	skb = dev_alloc_skb(MWIFIEX_UPLD_SIZE);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	ret = mwअगरiex_पढ़ो_reg(adapter, PCIE_SCRATCH_13_REG, &val);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, FATAL, "Failed to read scratch register 13\n");
		जाओ करोne;
	पूर्ण

	/* PCIE FLR हाल: extract wअगरi part from combo firmware*/
	अगर (val == MWIFIEX_PCIE_FLR_HAPPENS) अणु
		ret = mwअगरiex_extract_wअगरi_fw(adapter, firmware, firmware_len);
		अगर (ret < 0) अणु
			mwअगरiex_dbg(adapter, ERROR, "Failed to extract wifi fw\n");
			जाओ करोne;
		पूर्ण
		offset = ret;
		mwअगरiex_dbg(adapter, MSG,
			    "info: dnld wifi firmware from %d bytes\n", offset);
	पूर्ण

	/* Perक्रमm firmware data transfer */
	करो अणु
		u32 ireg_पूर्णांकr = 0;

		/* More data? */
		अगर (offset >= firmware_len)
			अवरोध;

		क्रम (tries = 0; tries < MAX_POLL_TRIES; tries++) अणु
			ret = mwअगरiex_पढ़ो_reg(adapter, reg->cmd_size,
					       &len);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, FATAL,
					    "Failed reading len from boot code\n");
				जाओ करोne;
			पूर्ण
			अगर (len)
				अवरोध;
			usleep_range(10, 20);
		पूर्ण

		अगर (!len) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (len > MWIFIEX_UPLD_SIZE) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "FW download failure @ %d, invalid length %d\n",
				    offset, len);
			ret = -1;
			जाओ करोne;
		पूर्ण

		txlen = len;

		अगर (len & BIT(0)) अणु
			block_retry_cnt++;
			अगर (block_retry_cnt > MAX_WRITE_IOMEM_RETRY) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "FW download failure @ %d, over max\t"
					    "retry count\n", offset);
				ret = -1;
				जाओ करोne;
			पूर्ण
			mwअगरiex_dbg(adapter, ERROR,
				    "FW CRC error indicated by the\t"
				    "helper: len = 0x%04X, txlen = %d\n",
				    len, txlen);
			len &= ~BIT(0);
			/* Setting this to 0 to resend from same offset */
			txlen = 0;
		पूर्ण अन्यथा अणु
			block_retry_cnt = 0;
			/* Set blocksize to transfer - checking क्रम
			   last block */
			अगर (firmware_len - offset < txlen)
				txlen = firmware_len - offset;

			tx_blocks = (txlen + card->pcie.blksz_fw_dl - 1) /
				    card->pcie.blksz_fw_dl;

			/* Copy payload to buffer */
			स_हटाओ(skb->data, &firmware[offset], txlen);
		पूर्ण

		skb_put(skb, MWIFIEX_UPLD_SIZE - skb->len);
		skb_trim(skb, tx_blocks * card->pcie.blksz_fw_dl);

		/* Send the boot command to device */
		अगर (mwअगरiex_pcie_send_boot_cmd(adapter, skb)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Failed to send firmware download command\n");
			ret = -1;
			जाओ करोne;
		पूर्ण

		/* Wait क्रम the command करोne पूर्णांकerrupt */
		क्रम (tries = 0; tries < MAX_POLL_TRIES; tries++) अणु
			अगर (mwअगरiex_पढ़ो_reg(adapter, PCIE_CPU_INT_STATUS,
					     &ireg_पूर्णांकr)) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "%s: Failed to read\t"
					    "interrupt status during fw dnld.\n",
					    __func__);
				mwअगरiex_unmap_pci_memory(adapter, skb,
							 DMA_TO_DEVICE);
				ret = -1;
				जाओ करोne;
			पूर्ण
			अगर (!(ireg_पूर्णांकr & CPU_INTR_DOOR_BELL))
				अवरोध;
			usleep_range(10, 20);
		पूर्ण
		अगर (ireg_पूर्णांकr & CPU_INTR_DOOR_BELL) अणु
			mwअगरiex_dbg(adapter, ERROR, "%s: Card failed to ACK download\n",
				    __func__);
			mwअगरiex_unmap_pci_memory(adapter, skb,
						 DMA_TO_DEVICE);
			ret = -1;
			जाओ करोne;
		पूर्ण

		mwअगरiex_unmap_pci_memory(adapter, skb, DMA_TO_DEVICE);

		offset += txlen;
	पूर्ण जबतक (true);

	mwअगरiex_dbg(adapter, MSG,
		    "info: FW download over, size %d bytes\n", offset);

	ret = 0;

करोne:
	dev_kमुक्त_skb_any(skb);
	वापस ret;
पूर्ण

/*
 * This function checks the firmware status in card.
 */
अटल पूर्णांक
mwअगरiex_check_fw_status(काष्ठा mwअगरiex_adapter *adapter, u32 poll_num)
अणु
	पूर्णांक ret = 0;
	u32 firmware_stat;
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	u32 tries;

	/* Mask spurios पूर्णांकerrupts */
	अगर (mwअगरiex_ग_लिखो_reg(adapter, PCIE_HOST_INT_STATUS_MASK,
			      HOST_INTR_MASK)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Write register failed\n");
		वापस -1;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "Setting driver ready signature\n");
	अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->drv_rdy,
			      FIRMWARE_READY_PCIE)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Failed to write driver ready signature\n");
		वापस -1;
	पूर्ण

	/* Wait क्रम firmware initialization event */
	क्रम (tries = 0; tries < poll_num; tries++) अणु
		अगर (mwअगरiex_पढ़ो_reg(adapter, reg->fw_status,
				     &firmware_stat))
			ret = -1;
		अन्यथा
			ret = 0;

		mwअगरiex_dbg(adapter, INFO, "Try %d if FW is ready <%d,%#x>",
			    tries, ret, firmware_stat);

		अगर (ret)
			जारी;
		अगर (firmware_stat == FIRMWARE_READY_PCIE) अणु
			ret = 0;
			अवरोध;
		पूर्ण अन्यथा अणु
			msleep(100);
			ret = -1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* This function checks अगर WLAN is the winner.
 */
अटल पूर्णांक
mwअगरiex_check_winner_status(काष्ठा mwअगरiex_adapter *adapter)
अणु
	u32 winner = 0;
	पूर्णांक ret = 0;
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	अगर (mwअगरiex_पढ़ो_reg(adapter, reg->fw_status, &winner)) अणु
		ret = -1;
	पूर्ण अन्यथा अगर (!winner) अणु
		mwअगरiex_dbg(adapter, INFO, "PCI-E is the winner\n");
		adapter->winner = 1;
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "PCI-E is not the winner <%#x>", winner);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function पढ़ोs the पूर्णांकerrupt status from card.
 */
अटल व्योम mwअगरiex_पूर्णांकerrupt_status(काष्ठा mwअगरiex_adapter *adapter,
				     पूर्णांक msg_id)
अणु
	u32 pcie_ireg;
	अचिन्हित दीर्घ flags;
	काष्ठा pcie_service_card *card = adapter->card;

	अगर (card->msi_enable) अणु
		spin_lock_irqsave(&adapter->पूर्णांक_lock, flags);
		adapter->पूर्णांक_status = 1;
		spin_unlock_irqrestore(&adapter->पूर्णांक_lock, flags);
		वापस;
	पूर्ण

	अगर (!mwअगरiex_pcie_ok_to_access_hw(adapter))
		वापस;

	अगर (card->msix_enable && msg_id >= 0) अणु
		pcie_ireg = BIT(msg_id);
	पूर्ण अन्यथा अणु
		अगर (mwअगरiex_पढ़ो_reg(adapter, PCIE_HOST_INT_STATUS,
				     &pcie_ireg)) अणु
			mwअगरiex_dbg(adapter, ERROR, "Read register failed\n");
			वापस;
		पूर्ण

		अगर ((pcie_ireg == 0xFFFFFFFF) || !pcie_ireg)
			वापस;


		mwअगरiex_pcie_disable_host_पूर्णांक(adapter);

		/* Clear the pending पूर्णांकerrupts */
		अगर (mwअगरiex_ग_लिखो_reg(adapter, PCIE_HOST_INT_STATUS,
				      ~pcie_ireg)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Write register failed\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (!adapter->pps_uapsd_mode &&
	    adapter->ps_state == PS_STATE_SLEEP &&
	    mwअगरiex_pcie_ok_to_access_hw(adapter)) अणु
		/* Potentially क्रम PCIe we could get other
		 * पूर्णांकerrupts like shared. Don't change घातer
		 * state until cookie is set
		 */
		adapter->ps_state = PS_STATE_AWAKE;
		adapter->pm_wakeup_fw_try = false;
		del_समयr(&adapter->wakeup_समयr);
	पूर्ण

	spin_lock_irqsave(&adapter->पूर्णांक_lock, flags);
	adapter->पूर्णांक_status |= pcie_ireg;
	spin_unlock_irqrestore(&adapter->पूर्णांक_lock, flags);
	mwअगरiex_dbg(adapter, INTR, "ireg: 0x%08x\n", pcie_ireg);
पूर्ण

/*
 * Interrupt handler क्रम PCIe root port
 *
 * This function पढ़ोs the पूर्णांकerrupt status from firmware and assigns
 * the मुख्य process in workqueue which will handle the पूर्णांकerrupt.
 */
अटल irqवापस_t mwअगरiex_pcie_पूर्णांकerrupt(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा mwअगरiex_msix_context *ctx = context;
	काष्ठा pci_dev *pdev = ctx->dev;
	काष्ठा pcie_service_card *card;
	काष्ठा mwअगरiex_adapter *adapter;

	card = pci_get_drvdata(pdev);

	अगर (!card->adapter) अणु
		pr_err("info: %s: card=%p adapter=%p\n", __func__, card,
		       card ? card->adapter : शून्य);
		जाओ निकास;
	पूर्ण
	adapter = card->adapter;

	अगर (test_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags))
		जाओ निकास;

	अगर (card->msix_enable)
		mwअगरiex_पूर्णांकerrupt_status(adapter, ctx->msg_id);
	अन्यथा
		mwअगरiex_पूर्णांकerrupt_status(adapter, -1);

	mwअगरiex_queue_मुख्य_work(adapter);

निकास:
	वापस IRQ_HANDLED;
पूर्ण

/*
 * This function checks the current पूर्णांकerrupt status.
 *
 * The following पूर्णांकerrupts are checked and handled by this function -
 *      - Data sent
 *      - Command sent
 *      - Command received
 *      - Packets received
 *      - Events received
 *
 * In हाल of Rx packets received, the packets are uploaded from card to
 * host and processed accordingly.
 */
अटल पूर्णांक mwअगरiex_process_पूर्णांक_status(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret;
	u32 pcie_ireg = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा pcie_service_card *card = adapter->card;

	spin_lock_irqsave(&adapter->पूर्णांक_lock, flags);
	अगर (!card->msi_enable) अणु
		/* Clear out unused पूर्णांकerrupts */
		pcie_ireg = adapter->पूर्णांक_status;
	पूर्ण
	adapter->पूर्णांक_status = 0;
	spin_unlock_irqrestore(&adapter->पूर्णांक_lock, flags);

	अगर (card->msi_enable) अणु
		अगर (mwअगरiex_pcie_ok_to_access_hw(adapter)) अणु
			अगर (mwअगरiex_पढ़ो_reg(adapter, PCIE_HOST_INT_STATUS,
					     &pcie_ireg)) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "Read register failed\n");
				वापस -1;
			पूर्ण

			अगर ((pcie_ireg != 0xFFFFFFFF) && (pcie_ireg)) अणु
				अगर (mwअगरiex_ग_लिखो_reg(adapter,
						      PCIE_HOST_INT_STATUS,
						      ~pcie_ireg)) अणु
					mwअगरiex_dbg(adapter, ERROR,
						    "Write register failed\n");
					वापस -1;
				पूर्ण
				अगर (!adapter->pps_uapsd_mode &&
				    adapter->ps_state == PS_STATE_SLEEP) अणु
					adapter->ps_state = PS_STATE_AWAKE;
					adapter->pm_wakeup_fw_try = false;
					del_समयr(&adapter->wakeup_समयr);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pcie_ireg & HOST_INTR_DNLD_DONE) अणु
		mwअगरiex_dbg(adapter, INTR, "info: TX DNLD Done\n");
		ret = mwअगरiex_pcie_send_data_complete(adapter);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (pcie_ireg & HOST_INTR_UPLD_RDY) अणु
		mwअगरiex_dbg(adapter, INTR, "info: Rx DATA\n");
		ret = mwअगरiex_pcie_process_recv_data(adapter);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (pcie_ireg & HOST_INTR_EVENT_RDY) अणु
		mwअगरiex_dbg(adapter, INTR, "info: Rx EVENT\n");
		ret = mwअगरiex_pcie_process_event_पढ़ोy(adapter);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (pcie_ireg & HOST_INTR_CMD_DONE) अणु
		अगर (adapter->cmd_sent) अणु
			mwअगरiex_dbg(adapter, INTR,
				    "info: CMD sent Interrupt\n");
			adapter->cmd_sent = false;
		पूर्ण
		/* Handle command response */
		ret = mwअगरiex_pcie_process_cmd_complete(adapter);
		अगर (ret)
			वापस ret;
	पूर्ण

	mwअगरiex_dbg(adapter, INTR,
		    "info: cmd_sent=%d data_sent=%d\n",
		    adapter->cmd_sent, adapter->data_sent);
	अगर (!card->msi_enable && !card->msix_enable &&
				 adapter->ps_state != PS_STATE_SLEEP)
		mwअगरiex_pcie_enable_host_पूर्णांक(adapter);

	वापस 0;
पूर्ण

/*
 * This function करोwnloads data from driver to card.
 *
 * Both commands and data packets are transferred to the card by this
 * function.
 *
 * This function adds the PCIE specअगरic header to the front of the buffer
 * beक्रमe transferring. The header contains the length of the packet and
 * the type. The firmware handles the packets based upon this set type.
 */
अटल पूर्णांक mwअगरiex_pcie_host_to_card(काष्ठा mwअगरiex_adapter *adapter, u8 type,
				     काष्ठा sk_buff *skb,
				     काष्ठा mwअगरiex_tx_param *tx_param)
अणु
	अगर (!skb) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Passed NULL skb to %s\n", __func__);
		वापस -1;
	पूर्ण

	अगर (type == MWIFIEX_TYPE_DATA)
		वापस mwअगरiex_pcie_send_data(adapter, skb, tx_param);
	अन्यथा अगर (type == MWIFIEX_TYPE_CMD)
		वापस mwअगरiex_pcie_send_cmd(adapter, skb);

	वापस 0;
पूर्ण

/* Function to dump PCIE scratch रेजिस्टरs in हाल of FW crash
 */
अटल पूर्णांक
mwअगरiex_pcie_reg_dump(काष्ठा mwअगरiex_adapter *adapter, अक्षर *drv_buf)
अणु
	अक्षर *p = drv_buf;
	अक्षर buf[256], *ptr;
	पूर्णांक i;
	u32 value;
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	पूर्णांक pcie_scratch_reg[] = अणुPCIE_SCRATCH_12_REG,
				  PCIE_SCRATCH_14_REG,
				  PCIE_SCRATCH_15_REGपूर्ण;

	अगर (!p)
		वापस 0;

	mwअगरiex_dbg(adapter, MSG, "PCIE register dump start\n");

	अगर (mwअगरiex_पढ़ो_reg(adapter, reg->fw_status, &value)) अणु
		mwअगरiex_dbg(adapter, ERROR, "failed to read firmware status");
		वापस 0;
	पूर्ण

	ptr = buf;
	mwअगरiex_dbg(adapter, MSG, "pcie scratch register:");
	क्रम (i = 0; i < ARRAY_SIZE(pcie_scratch_reg); i++) अणु
		mwअगरiex_पढ़ो_reg(adapter, pcie_scratch_reg[i], &value);
		ptr += प्र_लिखो(ptr, "reg:0x%x, value=0x%x\n",
			       pcie_scratch_reg[i], value);
	पूर्ण

	mwअगरiex_dbg(adapter, MSG, "%s\n", buf);
	p += प्र_लिखो(p, "%s\n", buf);

	mwअगरiex_dbg(adapter, MSG, "PCIE register dump end\n");

	वापस p - drv_buf;
पूर्ण

/* This function पढ़ो/ग_लिखो firmware */
अटल क्रमागत rdwr_status
mwअगरiex_pcie_rdwr_firmware(काष्ठा mwअगरiex_adapter *adapter, u8 करोneflag)
अणु
	पूर्णांक ret, tries;
	u8 ctrl_data;
	u32 fw_status;
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	अगर (mwअगरiex_पढ़ो_reg(adapter, reg->fw_status, &fw_status))
		वापस RDWR_STATUS_FAILURE;

	ret = mwअगरiex_ग_लिखो_reg(adapter, reg->fw_dump_ctrl,
				reg->fw_dump_host_पढ़ोy);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "PCIE write err\n");
		वापस RDWR_STATUS_FAILURE;
	पूर्ण

	क्रम (tries = 0; tries < MAX_POLL_TRIES; tries++) अणु
		mwअगरiex_पढ़ो_reg_byte(adapter, reg->fw_dump_ctrl, &ctrl_data);
		अगर (ctrl_data == FW_DUMP_DONE)
			वापस RDWR_STATUS_SUCCESS;
		अगर (करोneflag && ctrl_data == करोneflag)
			वापस RDWR_STATUS_DONE;
		अगर (ctrl_data != reg->fw_dump_host_पढ़ोy) अणु
			mwअगरiex_dbg(adapter, WARN,
				    "The ctrl reg was changed, re-try again!\n");
			ret = mwअगरiex_ग_लिखो_reg(adapter, reg->fw_dump_ctrl,
						reg->fw_dump_host_पढ़ोy);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "PCIE write err\n");
				वापस RDWR_STATUS_FAILURE;
			पूर्ण
		पूर्ण
		usleep_range(100, 200);
	पूर्ण

	mwअगरiex_dbg(adapter, ERROR, "Fail to pull ctrl_data\n");
	वापस RDWR_STATUS_FAILURE;
पूर्ण

/* This function dump firmware memory to file */
अटल व्योम mwअगरiex_pcie_fw_dump(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *creg = card->pcie.reg;
	अचिन्हित पूर्णांक reg, reg_start, reg_end;
	u8 *dbg_ptr, *end_ptr, *पंचांगp_ptr, fw_dump_num, dump_num;
	u8 idx, i, पढ़ो_reg, करोneflag = 0;
	क्रमागत rdwr_status stat;
	u32 memory_size;
	पूर्णांक ret;

	अगर (!card->pcie.can_dump_fw)
		वापस;

	क्रम (idx = 0; idx < adapter->num_mem_types; idx++) अणु
		काष्ठा memory_type_mapping *entry =
				&adapter->mem_type_mapping_tbl[idx];

		अगर (entry->mem_ptr) अणु
			vमुक्त(entry->mem_ptr);
			entry->mem_ptr = शून्य;
		पूर्ण
		entry->mem_size = 0;
	पूर्ण

	mwअगरiex_dbg(adapter, MSG, "== mwifiex firmware dump start ==\n");

	/* Read the number of the memories which will dump */
	stat = mwअगरiex_pcie_rdwr_firmware(adapter, करोneflag);
	अगर (stat == RDWR_STATUS_FAILURE)
		वापस;

	reg = creg->fw_dump_start;
	mwअगरiex_पढ़ो_reg_byte(adapter, reg, &fw_dump_num);

	/* W8997 chipset firmware dump will be restore in single region*/
	अगर (fw_dump_num == 0)
		dump_num = 1;
	अन्यथा
		dump_num = fw_dump_num;

	/* Read the length of every memory which will dump */
	क्रम (idx = 0; idx < dump_num; idx++) अणु
		काष्ठा memory_type_mapping *entry =
				&adapter->mem_type_mapping_tbl[idx];
		memory_size = 0;
		अगर (fw_dump_num != 0) अणु
			stat = mwअगरiex_pcie_rdwr_firmware(adapter, करोneflag);
			अगर (stat == RDWR_STATUS_FAILURE)
				वापस;

			reg = creg->fw_dump_start;
			क्रम (i = 0; i < 4; i++) अणु
				mwअगरiex_पढ़ो_reg_byte(adapter, reg, &पढ़ो_reg);
				memory_size |= (पढ़ो_reg << (i * 8));
				reg++;
			पूर्ण
		पूर्ण अन्यथा अणु
			memory_size = MWIFIEX_FW_DUMP_MAX_MEMSIZE;
		पूर्ण

		अगर (memory_size == 0) अणु
			mwअगरiex_dbg(adapter, MSG, "Firmware dump Finished!\n");
			ret = mwअगरiex_ग_लिखो_reg(adapter, creg->fw_dump_ctrl,
						creg->fw_dump_पढ़ो_करोne);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, ERROR, "PCIE write err\n");
				वापस;
			पूर्ण
			अवरोध;
		पूर्ण

		mwअगरiex_dbg(adapter, DUMP,
			    "%s_SIZE=0x%x\n", entry->mem_name, memory_size);
		entry->mem_ptr = vदो_स्मृति(memory_size + 1);
		entry->mem_size = memory_size;
		अगर (!entry->mem_ptr) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Vmalloc %s failed\n", entry->mem_name);
			वापस;
		पूर्ण
		dbg_ptr = entry->mem_ptr;
		end_ptr = dbg_ptr + memory_size;

		करोneflag = entry->करोne_flag;
		mwअगरiex_dbg(adapter, DUMP, "Start %s output, please wait...\n",
			    entry->mem_name);

		करो अणु
			stat = mwअगरiex_pcie_rdwr_firmware(adapter, करोneflag);
			अगर (RDWR_STATUS_FAILURE == stat)
				वापस;

			reg_start = creg->fw_dump_start;
			reg_end = creg->fw_dump_end;
			क्रम (reg = reg_start; reg <= reg_end; reg++) अणु
				mwअगरiex_पढ़ो_reg_byte(adapter, reg, dbg_ptr);
				अगर (dbg_ptr < end_ptr) अणु
					dbg_ptr++;
					जारी;
				पूर्ण
				mwअगरiex_dbg(adapter, ERROR,
					    "pre-allocated buf not enough\n");
				पंचांगp_ptr =
					vzalloc(memory_size + MWIFIEX_SIZE_4K);
				अगर (!पंचांगp_ptr)
					वापस;
				स_नकल(पंचांगp_ptr, entry->mem_ptr, memory_size);
				vमुक्त(entry->mem_ptr);
				entry->mem_ptr = पंचांगp_ptr;
				पंचांगp_ptr = शून्य;
				dbg_ptr = entry->mem_ptr + memory_size;
				memory_size += MWIFIEX_SIZE_4K;
				end_ptr = entry->mem_ptr + memory_size;
			पूर्ण

			अगर (stat != RDWR_STATUS_DONE)
				जारी;

			mwअगरiex_dbg(adapter, DUMP,
				    "%s done: size=0x%tx\n",
				    entry->mem_name, dbg_ptr - entry->mem_ptr);
			अवरोध;
		पूर्ण जबतक (true);
	पूर्ण
	mwअगरiex_dbg(adapter, MSG, "== mwifiex firmware dump end ==\n");
पूर्ण

अटल व्योम mwअगरiex_pcie_device_dump_work(काष्ठा mwअगरiex_adapter *adapter)
अणु
	adapter->devdump_data = vzalloc(MWIFIEX_FW_DUMP_SIZE);
	अगर (!adapter->devdump_data) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "vzalloc devdump data failure!\n");
		वापस;
	पूर्ण

	mwअगरiex_drv_info_dump(adapter);
	mwअगरiex_pcie_fw_dump(adapter);
	mwअगरiex_prepare_fw_dump_info(adapter);
	mwअगरiex_upload_device_dump(adapter);
पूर्ण

अटल व्योम mwअगरiex_pcie_card_reset_work(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;

	/* We can't afक्रमd to रुको here; हटाओ() might be रुकोing on us. If we
	 * can't grab the device lock, maybe we'll get another chance later.
	 */
	pci_try_reset_function(card->dev);
पूर्ण

अटल व्योम mwअगरiex_pcie_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pcie_service_card *card =
		container_of(work, काष्ठा pcie_service_card, work);

	अगर (test_and_clear_bit(MWIFIEX_IFACE_WORK_DEVICE_DUMP,
			       &card->work_flags))
		mwअगरiex_pcie_device_dump_work(card->adapter);
	अगर (test_and_clear_bit(MWIFIEX_IFACE_WORK_CARD_RESET,
			       &card->work_flags))
		mwअगरiex_pcie_card_reset_work(card->adapter);
पूर्ण

/* This function dumps FW inक्रमmation */
अटल व्योम mwअगरiex_pcie_device_dump(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;

	अगर (!test_and_set_bit(MWIFIEX_IFACE_WORK_DEVICE_DUMP,
			      &card->work_flags))
		schedule_work(&card->work);
पूर्ण

अटल व्योम mwअगरiex_pcie_card_reset(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;

	अगर (!test_and_set_bit(MWIFIEX_IFACE_WORK_CARD_RESET, &card->work_flags))
		schedule_work(&card->work);
पूर्ण

अटल पूर्णांक mwअगरiex_pcie_alloc_buffers(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	पूर्णांक ret;

	card->cmdrsp_buf = शून्य;
	ret = mwअगरiex_pcie_create_txbd_ring(adapter);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR, "Failed to create txbd ring\n");
		जाओ err_cre_txbd;
	पूर्ण

	ret = mwअगरiex_pcie_create_rxbd_ring(adapter);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR, "Failed to create rxbd ring\n");
		जाओ err_cre_rxbd;
	पूर्ण

	ret = mwअगरiex_pcie_create_evtbd_ring(adapter);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR, "Failed to create evtbd ring\n");
		जाओ err_cre_evtbd;
	पूर्ण

	ret = mwअगरiex_pcie_alloc_cmdrsp_buf(adapter);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR, "Failed to allocate cmdbuf buffer\n");
		जाओ err_alloc_cmdbuf;
	पूर्ण

	अगर (reg->sleep_cookie) अणु
		ret = mwअगरiex_pcie_alloc_sleep_cookie_buf(adapter);
		अगर (ret) अणु
			mwअगरiex_dbg(adapter, ERROR, "Failed to allocate sleep_cookie buffer\n");
			जाओ err_alloc_cookie;
		पूर्ण
	पूर्ण अन्यथा अणु
		card->sleep_cookie_vbase = शून्य;
	पूर्ण

	वापस 0;

err_alloc_cookie:
	mwअगरiex_pcie_delete_cmdrsp_buf(adapter);
err_alloc_cmdbuf:
	mwअगरiex_pcie_delete_evtbd_ring(adapter);
err_cre_evtbd:
	mwअगरiex_pcie_delete_rxbd_ring(adapter);
err_cre_rxbd:
	mwअगरiex_pcie_delete_txbd_ring(adapter);
err_cre_txbd:
	वापस ret;
पूर्ण

अटल व्योम mwअगरiex_pcie_मुक्त_buffers(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	अगर (reg->sleep_cookie)
		mwअगरiex_pcie_delete_sleep_cookie_buf(adapter);

	mwअगरiex_pcie_delete_cmdrsp_buf(adapter);
	mwअगरiex_pcie_delete_evtbd_ring(adapter);
	mwअगरiex_pcie_delete_rxbd_ring(adapter);
	mwअगरiex_pcie_delete_txbd_ring(adapter);
पूर्ण

/*
 * This function initializes the PCI-E host memory space, WCB rings, etc.
 */
अटल पूर्णांक mwअगरiex_init_pcie(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	पूर्णांक ret;
	काष्ठा pci_dev *pdev = card->dev;

	pci_set_drvdata(pdev, card);

	ret = pci_enable_device(pdev);
	अगर (ret)
		जाओ err_enable_dev;

	pci_set_master(pdev);

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		pr_err("dma_set_mask(32) failed: %d\n", ret);
		जाओ err_set_dma_mask;
	पूर्ण

	ret = pci_request_region(pdev, 0, DRV_NAME);
	अगर (ret) अणु
		pr_err("req_reg(0) error\n");
		जाओ err_req_region0;
	पूर्ण
	card->pci_mmap = pci_iomap(pdev, 0, 0);
	अगर (!card->pci_mmap) अणु
		pr_err("iomap(0) error\n");
		ret = -EIO;
		जाओ err_iomap0;
	पूर्ण
	ret = pci_request_region(pdev, 2, DRV_NAME);
	अगर (ret) अणु
		pr_err("req_reg(2) error\n");
		जाओ err_req_region2;
	पूर्ण
	card->pci_mmap1 = pci_iomap(pdev, 2, 0);
	अगर (!card->pci_mmap1) अणु
		pr_err("iomap(2) error\n");
		ret = -EIO;
		जाओ err_iomap2;
	पूर्ण

	pr_notice("PCI memory map Virt0: %pK PCI memory map Virt2: %pK\n",
		  card->pci_mmap, card->pci_mmap1);

	ret = mwअगरiex_pcie_alloc_buffers(adapter);
	अगर (ret)
		जाओ err_alloc_buffers;

	वापस 0;

err_alloc_buffers:
	pci_iounmap(pdev, card->pci_mmap1);
err_iomap2:
	pci_release_region(pdev, 2);
err_req_region2:
	pci_iounmap(pdev, card->pci_mmap);
err_iomap0:
	pci_release_region(pdev, 0);
err_req_region0:
err_set_dma_mask:
	pci_disable_device(pdev);
err_enable_dev:
	वापस ret;
पूर्ण

/*
 * This function cleans up the allocated card buffers.
 */
अटल व्योम mwअगरiex_cleanup_pcie(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	काष्ठा pci_dev *pdev = card->dev;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	u32 fw_status;

	/* Perक्रमm the cancel_work_sync() only when we're not resetting
	 * the card. It's because that function never returns if we're
	 * in reset path. If we're here when resetting the card, it means
	 * that we failed to reset the card (reset failure path).
	 */
	अगर (!card->pci_reset_ongoing) अणु
		mwअगरiex_dbg(adapter, MSG, "performing cancel_work_sync()...\n");
		cancel_work_sync(&card->work);
		mwअगरiex_dbg(adapter, MSG, "cancel_work_sync() done\n");
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(adapter, MSG,
			    "skipped cancel_work_sync() because we're in card reset failure path\n");
	पूर्ण

	mwअगरiex_पढ़ो_reg(adapter, reg->fw_status, &fw_status);
	अगर (fw_status == FIRMWARE_READY_PCIE) अणु
		mwअगरiex_dbg(adapter, INFO,
			    "Clearing driver ready signature\n");
		अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->drv_rdy, 0x00000000))
			mwअगरiex_dbg(adapter, ERROR,
				    "Failed to write driver not-ready signature\n");
	पूर्ण

	pci_disable_device(pdev);

	pci_iounmap(pdev, card->pci_mmap);
	pci_iounmap(pdev, card->pci_mmap1);
	pci_release_region(pdev, 2);
	pci_release_region(pdev, 0);

	mwअगरiex_pcie_मुक्त_buffers(adapter);
पूर्ण

अटल पूर्णांक mwअगरiex_pcie_request_irq(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret, i, j;
	काष्ठा pcie_service_card *card = adapter->card;
	काष्ठा pci_dev *pdev = card->dev;

	अगर (card->pcie.reg->msix_support) अणु
		क्रम (i = 0; i < MWIFIEX_NUM_MSIX_VECTORS; i++)
			card->msix_entries[i].entry = i;
		ret = pci_enable_msix_exact(pdev, card->msix_entries,
					    MWIFIEX_NUM_MSIX_VECTORS);
		अगर (!ret) अणु
			क्रम (i = 0; i < MWIFIEX_NUM_MSIX_VECTORS; i++) अणु
				card->msix_ctx[i].dev = pdev;
				card->msix_ctx[i].msg_id = i;

				ret = request_irq(card->msix_entries[i].vector,
						  mwअगरiex_pcie_पूर्णांकerrupt, 0,
						  "MWIFIEX_PCIE_MSIX",
						  &card->msix_ctx[i]);
				अगर (ret)
					अवरोध;
			पूर्ण

			अगर (ret) अणु
				mwअगरiex_dbg(adapter, INFO, "request_irq fail: %d\n",
					    ret);
				क्रम (j = 0; j < i; j++)
					मुक्त_irq(card->msix_entries[j].vector,
						 &card->msix_ctx[i]);
				pci_disable_msix(pdev);
			पूर्ण अन्यथा अणु
				mwअगरiex_dbg(adapter, MSG, "MSIx enabled!");
				card->msix_enable = 1;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pci_enable_msi(pdev) != 0)
		pci_disable_msi(pdev);
	अन्यथा
		card->msi_enable = 1;

	mwअगरiex_dbg(adapter, INFO, "msi_enable = %d\n", card->msi_enable);

	card->share_irq_ctx.dev = pdev;
	card->share_irq_ctx.msg_id = -1;
	ret = request_irq(pdev->irq, mwअगरiex_pcie_पूर्णांकerrupt, IRQF_SHARED,
			  "MRVL_PCIE", &card->share_irq_ctx);
	अगर (ret) अणु
		pr_err("request_irq failed: ret=%d\n", ret);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function माला_लो the firmware name क्रम करोwnloading by revision id
 *
 * Read revision id रेजिस्टर to get revision id
 */
अटल व्योम mwअगरiex_pcie_get_fw_name(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक revision_id = 0;
	पूर्णांक version, magic;
	काष्ठा pcie_service_card *card = adapter->card;

	चयन (card->dev->device) अणु
	हाल PCIE_DEVICE_ID_MARVELL_88W8766P:
		म_नकल(adapter->fw_name, PCIE8766_DEFAULT_FW_NAME);
		अवरोध;
	हाल PCIE_DEVICE_ID_MARVELL_88W8897:
		mwअगरiex_ग_लिखो_reg(adapter, 0x0c58, 0x80c00000);
		mwअगरiex_पढ़ो_reg(adapter, 0x0c58, &revision_id);
		revision_id &= 0xff00;
		चयन (revision_id) अणु
		हाल PCIE8897_A0:
			म_नकल(adapter->fw_name, PCIE8897_A0_FW_NAME);
			अवरोध;
		हाल PCIE8897_B0:
			म_नकल(adapter->fw_name, PCIE8897_B0_FW_NAME);
			अवरोध;
		शेष:
			म_नकल(adapter->fw_name, PCIE8897_DEFAULT_FW_NAME);

			अवरोध;
		पूर्ण
		अवरोध;
	हाल PCIE_DEVICE_ID_MARVELL_88W8997:
		mwअगरiex_पढ़ो_reg(adapter, 0x8, &revision_id);
		mwअगरiex_पढ़ो_reg(adapter, 0x0cd0, &version);
		mwअगरiex_पढ़ो_reg(adapter, 0x0cd4, &magic);
		revision_id &= 0xff;
		version &= 0x7;
		magic &= 0xff;
		अगर (revision_id == PCIE8997_A1 &&
		    magic == CHIP_MAGIC_VALUE &&
		    version == CHIP_VER_PCIEUART)
			म_नकल(adapter->fw_name, PCIEUART8997_FW_NAME_V4);
		अन्यथा
			म_नकल(adapter->fw_name, PCIEUSB8997_FW_NAME_V4);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * This function रेजिस्टरs the PCIE device.
 *
 * PCIE IRQ is claimed, block size is set and driver data is initialized.
 */
अटल पूर्णांक mwअगरiex_रेजिस्टर_dev(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;

	/* save adapter poपूर्णांकer in card */
	card->adapter = adapter;

	अगर (mwअगरiex_pcie_request_irq(adapter))
		वापस -1;

	adapter->tx_buf_size = card->pcie.tx_buf_size;
	adapter->mem_type_mapping_tbl = card->pcie.mem_type_mapping_tbl;
	adapter->num_mem_types = card->pcie.num_mem_types;
	adapter->ext_scan = card->pcie.can_ext_scan;
	mwअगरiex_pcie_get_fw_name(adapter);

	वापस 0;
पूर्ण

/*
 * This function unरेजिस्टरs the PCIE device.
 *
 * The PCIE IRQ is released, the function is disabled and driver
 * data is set to null.
 */
अटल व्योम mwअगरiex_unरेजिस्टर_dev(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	काष्ठा pci_dev *pdev = card->dev;
	पूर्णांक i;

	अगर (card->msix_enable) अणु
		क्रम (i = 0; i < MWIFIEX_NUM_MSIX_VECTORS; i++)
			synchronize_irq(card->msix_entries[i].vector);

		क्रम (i = 0; i < MWIFIEX_NUM_MSIX_VECTORS; i++)
			मुक्त_irq(card->msix_entries[i].vector,
				 &card->msix_ctx[i]);

		card->msix_enable = 0;
		pci_disable_msix(pdev);
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(adapter, INFO,
			    "%s(): calling free_irq()\n", __func__);
	       मुक्त_irq(card->dev->irq, &card->share_irq_ctx);

		अगर (card->msi_enable)
			pci_disable_msi(pdev);
	पूर्ण
	card->adapter = शून्य;
पूर्ण

/*
 * This function initializes the PCI-E host memory space, WCB rings, etc.,
 * similar to mwअगरiex_init_pcie(), but without resetting PCI-E state.
 */
अटल व्योम mwअगरiex_pcie_up_dev(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	काष्ठा pci_dev *pdev = card->dev;

	/* tx_buf_size might be changed to 3584 by firmware during
	 * data transfer, we should reset it to शेष size.
	 */
	adapter->tx_buf_size = card->pcie.tx_buf_size;

	mwअगरiex_pcie_alloc_buffers(adapter);

	pci_set_master(pdev);
पूर्ण

/* This function cleans up the PCI-E host memory space. */
अटल व्योम mwअगरiex_pcie_करोwn_dev(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा pcie_service_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;
	काष्ठा pci_dev *pdev = card->dev;

	अगर (mwअगरiex_ग_लिखो_reg(adapter, reg->drv_rdy, 0x00000000))
		mwअगरiex_dbg(adapter, ERROR, "Failed to write driver not-ready signature\n");

	pci_clear_master(pdev);

	adapter->seq_num = 0;

	mwअगरiex_pcie_मुक्त_buffers(adapter);
पूर्ण

अटल काष्ठा mwअगरiex_अगर_ops pcie_ops = अणु
	.init_अगर =			mwअगरiex_init_pcie,
	.cleanup_अगर =			mwअगरiex_cleanup_pcie,
	.check_fw_status =		mwअगरiex_check_fw_status,
	.check_winner_status =          mwअगरiex_check_winner_status,
	.prog_fw =			mwअगरiex_prog_fw_w_helper,
	.रेजिस्टर_dev =			mwअगरiex_रेजिस्टर_dev,
	.unरेजिस्टर_dev =		mwअगरiex_unरेजिस्टर_dev,
	.enable_पूर्णांक =			mwअगरiex_pcie_enable_host_पूर्णांक,
	.disable_पूर्णांक =			mwअगरiex_pcie_disable_host_पूर्णांक_noerr,
	.process_पूर्णांक_status =		mwअगरiex_process_पूर्णांक_status,
	.host_to_card =			mwअगरiex_pcie_host_to_card,
	.wakeup =			mwअगरiex_pm_wakeup_card,
	.wakeup_complete =		mwअगरiex_pm_wakeup_card_complete,

	/* PCIE specअगरic */
	.cmdrsp_complete =		mwअगरiex_pcie_cmdrsp_complete,
	.event_complete =		mwअगरiex_pcie_event_complete,
	.update_mp_end_port =		शून्य,
	.cleanup_mpa_buf =		शून्य,
	.init_fw_port =			mwअगरiex_pcie_init_fw_port,
	.clean_pcie_ring =		mwअगरiex_clean_pcie_ring_buf,
	.card_reset =			mwअगरiex_pcie_card_reset,
	.reg_dump =			mwअगरiex_pcie_reg_dump,
	.device_dump =			mwअगरiex_pcie_device_dump,
	.करोwn_dev =			mwअगरiex_pcie_करोwn_dev,
	.up_dev =			mwअगरiex_pcie_up_dev,
पूर्ण;

module_pci_driver(mwअगरiex_pcie);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell WiFi-Ex PCI-Express Driver version " PCIE_VERSION);
MODULE_VERSION(PCIE_VERSION);
MODULE_LICENSE("GPL v2");
