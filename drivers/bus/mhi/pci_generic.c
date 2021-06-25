<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MHI PCI driver - MHI over PCI controller driver
 *
 * This module is a generic driver क्रम रेजिस्टरing MHI-over-PCI devices,
 * such as PCIe QCOM modems.
 *
 * Copyright (C) 2020 Linaro Ltd <loic.poulain@linaro.org>
 */

#समावेश <linux/aer.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/mhi.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>

#घोषणा MHI_PCI_DEFAULT_BAR_NUM 0

#घोषणा MHI_POST_RESET_DELAY_MS 500

#घोषणा HEALTH_CHECK_PERIOD (HZ * 2)

/**
 * काष्ठा mhi_pci_dev_info - MHI PCI device specअगरic inक्रमmation
 * @config: MHI controller configuration
 * @name: name of the PCI module
 * @fw: firmware path (अगर any)
 * @edl: emergency करोwnload mode firmware path (अगर any)
 * @bar_num: PCI base address रेजिस्टर to use क्रम MHI MMIO रेजिस्टर space
 * @dma_data_width: DMA transfer word size (32 or 64 bits)
 */
काष्ठा mhi_pci_dev_info अणु
	स्थिर काष्ठा mhi_controller_config *config;
	स्थिर अक्षर *name;
	स्थिर अक्षर *fw;
	स्थिर अक्षर *edl;
	अचिन्हित पूर्णांक bar_num;
	अचिन्हित पूर्णांक dma_data_width;
पूर्ण;

#घोषणा MHI_CHANNEL_CONFIG_UL(ch_num, ch_name, el_count, ev_ring) \
	अणु						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_elements = el_count,		\
		.event_ring = ev_ring,			\
		.dir = DMA_TO_DEVICE,			\
		.ee_mask = BIT(MHI_EE_AMSS),		\
		.pollcfg = 0,				\
		.करोorbell = MHI_DB_BRST_DISABLE,	\
		.lpm_notअगरy = false,			\
		.offload_channel = false,		\
		.करोorbell_mode_चयन = false,		\
	पूर्ण						\

#घोषणा MHI_CHANNEL_CONFIG_DL(ch_num, ch_name, el_count, ev_ring) \
	अणु						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_elements = el_count,		\
		.event_ring = ev_ring,			\
		.dir = DMA_FROM_DEVICE,			\
		.ee_mask = BIT(MHI_EE_AMSS),		\
		.pollcfg = 0,				\
		.करोorbell = MHI_DB_BRST_DISABLE,	\
		.lpm_notअगरy = false,			\
		.offload_channel = false,		\
		.करोorbell_mode_चयन = false,		\
	पूर्ण

#घोषणा MHI_EVENT_CONFIG_CTRL(ev_ring, el_count) \
	अणु					\
		.num_elements = el_count,	\
		.irq_moderation_ms = 0,		\
		.irq = (ev_ring) + 1,		\
		.priority = 1,			\
		.mode = MHI_DB_BRST_DISABLE,	\
		.data_type = MHI_ER_CTRL,	\
		.hardware_event = false,	\
		.client_managed = false,	\
		.offload_channel = false,	\
	पूर्ण

#घोषणा MHI_CHANNEL_CONFIG_HW_UL(ch_num, ch_name, el_count, ev_ring) \
	अणु						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_elements = el_count,		\
		.event_ring = ev_ring,			\
		.dir = DMA_TO_DEVICE,			\
		.ee_mask = BIT(MHI_EE_AMSS),		\
		.pollcfg = 0,				\
		.करोorbell = MHI_DB_BRST_ENABLE,	\
		.lpm_notअगरy = false,			\
		.offload_channel = false,		\
		.करोorbell_mode_चयन = true,		\
	पूर्ण						\

#घोषणा MHI_CHANNEL_CONFIG_HW_DL(ch_num, ch_name, el_count, ev_ring) \
	अणु						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_elements = el_count,		\
		.event_ring = ev_ring,			\
		.dir = DMA_FROM_DEVICE,			\
		.ee_mask = BIT(MHI_EE_AMSS),		\
		.pollcfg = 0,				\
		.करोorbell = MHI_DB_BRST_ENABLE,	\
		.lpm_notअगरy = false,			\
		.offload_channel = false,		\
		.करोorbell_mode_चयन = true,		\
	पूर्ण

#घोषणा MHI_CHANNEL_CONFIG_UL_SBL(ch_num, ch_name, el_count, ev_ring) \
	अणु						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_elements = el_count,		\
		.event_ring = ev_ring,			\
		.dir = DMA_TO_DEVICE,			\
		.ee_mask = BIT(MHI_EE_SBL),		\
		.pollcfg = 0,				\
		.करोorbell = MHI_DB_BRST_DISABLE,	\
		.lpm_notअगरy = false,			\
		.offload_channel = false,		\
		.करोorbell_mode_चयन = false,		\
	पूर्ण						\

#घोषणा MHI_CHANNEL_CONFIG_DL_SBL(ch_num, ch_name, el_count, ev_ring) \
	अणु						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_elements = el_count,		\
		.event_ring = ev_ring,			\
		.dir = DMA_FROM_DEVICE,			\
		.ee_mask = BIT(MHI_EE_SBL),		\
		.pollcfg = 0,				\
		.करोorbell = MHI_DB_BRST_DISABLE,	\
		.lpm_notअगरy = false,			\
		.offload_channel = false,		\
		.करोorbell_mode_चयन = false,		\
	पूर्ण

#घोषणा MHI_CHANNEL_CONFIG_UL_FP(ch_num, ch_name, el_count, ev_ring) \
	अणु						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_elements = el_count,		\
		.event_ring = ev_ring,			\
		.dir = DMA_TO_DEVICE,			\
		.ee_mask = BIT(MHI_EE_FP),		\
		.pollcfg = 0,				\
		.करोorbell = MHI_DB_BRST_DISABLE,	\
		.lpm_notअगरy = false,			\
		.offload_channel = false,		\
		.करोorbell_mode_चयन = false,		\
	पूर्ण						\

#घोषणा MHI_CHANNEL_CONFIG_DL_FP(ch_num, ch_name, el_count, ev_ring) \
	अणु						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_elements = el_count,		\
		.event_ring = ev_ring,			\
		.dir = DMA_FROM_DEVICE,			\
		.ee_mask = BIT(MHI_EE_FP),		\
		.pollcfg = 0,				\
		.करोorbell = MHI_DB_BRST_DISABLE,	\
		.lpm_notअगरy = false,			\
		.offload_channel = false,		\
		.करोorbell_mode_चयन = false,		\
	पूर्ण

#घोषणा MHI_EVENT_CONFIG_DATA(ev_ring, el_count) \
	अणु					\
		.num_elements = el_count,	\
		.irq_moderation_ms = 5,		\
		.irq = (ev_ring) + 1,		\
		.priority = 1,			\
		.mode = MHI_DB_BRST_DISABLE,	\
		.data_type = MHI_ER_DATA,	\
		.hardware_event = false,	\
		.client_managed = false,	\
		.offload_channel = false,	\
	पूर्ण

#घोषणा MHI_EVENT_CONFIG_HW_DATA(ev_ring, el_count, ch_num) \
	अणु					\
		.num_elements = el_count,	\
		.irq_moderation_ms = 1,		\
		.irq = (ev_ring) + 1,		\
		.priority = 1,			\
		.mode = MHI_DB_BRST_DISABLE,	\
		.data_type = MHI_ER_DATA,	\
		.hardware_event = true,		\
		.client_managed = false,	\
		.offload_channel = false,	\
		.channel = ch_num,		\
	पूर्ण

अटल स्थिर काष्ठा mhi_channel_config modem_qcom_v1_mhi_channels[] = अणु
	MHI_CHANNEL_CONFIG_UL(4, "DIAG", 16, 1),
	MHI_CHANNEL_CONFIG_DL(5, "DIAG", 16, 1),
	MHI_CHANNEL_CONFIG_UL(12, "MBIM", 4, 0),
	MHI_CHANNEL_CONFIG_DL(13, "MBIM", 4, 0),
	MHI_CHANNEL_CONFIG_UL(14, "QMI", 4, 0),
	MHI_CHANNEL_CONFIG_DL(15, "QMI", 4, 0),
	MHI_CHANNEL_CONFIG_UL(20, "IPCR", 8, 0),
	MHI_CHANNEL_CONFIG_DL(21, "IPCR", 8, 0),
	MHI_CHANNEL_CONFIG_UL_FP(34, "FIREHOSE", 32, 0),
	MHI_CHANNEL_CONFIG_DL_FP(35, "FIREHOSE", 32, 0),
	MHI_CHANNEL_CONFIG_HW_UL(100, "IP_HW0", 128, 2),
	MHI_CHANNEL_CONFIG_HW_DL(101, "IP_HW0", 128, 3),
पूर्ण;

अटल काष्ठा mhi_event_config modem_qcom_v1_mhi_events[] = अणु
	/* first ring is control+data ring */
	MHI_EVENT_CONFIG_CTRL(0, 64),
	/* DIAG dedicated event ring */
	MHI_EVENT_CONFIG_DATA(1, 128),
	/* Hardware channels request dedicated hardware event rings */
	MHI_EVENT_CONFIG_HW_DATA(2, 1024, 100),
	MHI_EVENT_CONFIG_HW_DATA(3, 2048, 101)
पूर्ण;

अटल स्थिर काष्ठा mhi_controller_config modem_qcom_v1_mhiv_config = अणु
	.max_channels = 128,
	.समयout_ms = 8000,
	.num_channels = ARRAY_SIZE(modem_qcom_v1_mhi_channels),
	.ch_cfg = modem_qcom_v1_mhi_channels,
	.num_events = ARRAY_SIZE(modem_qcom_v1_mhi_events),
	.event_cfg = modem_qcom_v1_mhi_events,
पूर्ण;

अटल स्थिर काष्ठा mhi_pci_dev_info mhi_qcom_sdx65_info = अणु
	.name = "qcom-sdx65m",
	.fw = "qcom/sdx65m/xbl.elf",
	.edl = "qcom/sdx65m/edl.mbn",
	.config = &modem_qcom_v1_mhiv_config,
	.bar_num = MHI_PCI_DEFAULT_BAR_NUM,
	.dma_data_width = 32
पूर्ण;

अटल स्थिर काष्ठा mhi_pci_dev_info mhi_qcom_sdx55_info = अणु
	.name = "qcom-sdx55m",
	.fw = "qcom/sdx55m/sbl1.mbn",
	.edl = "qcom/sdx55m/edl.mbn",
	.config = &modem_qcom_v1_mhiv_config,
	.bar_num = MHI_PCI_DEFAULT_BAR_NUM,
	.dma_data_width = 32
पूर्ण;

अटल स्थिर काष्ठा mhi_pci_dev_info mhi_qcom_sdx24_info = अणु
	.name = "qcom-sdx24",
	.edl = "qcom/prog_firehose_sdx24.mbn",
	.config = &modem_qcom_v1_mhiv_config,
	.bar_num = MHI_PCI_DEFAULT_BAR_NUM,
	.dma_data_width = 32
पूर्ण;

अटल स्थिर काष्ठा mhi_channel_config mhi_quectel_em1xx_channels[] = अणु
	MHI_CHANNEL_CONFIG_UL(0, "NMEA", 32, 0),
	MHI_CHANNEL_CONFIG_DL(1, "NMEA", 32, 0),
	MHI_CHANNEL_CONFIG_UL_SBL(2, "SAHARA", 32, 0),
	MHI_CHANNEL_CONFIG_DL_SBL(3, "SAHARA", 32, 0),
	MHI_CHANNEL_CONFIG_UL(4, "DIAG", 32, 1),
	MHI_CHANNEL_CONFIG_DL(5, "DIAG", 32, 1),
	MHI_CHANNEL_CONFIG_UL(12, "MBIM", 32, 0),
	MHI_CHANNEL_CONFIG_DL(13, "MBIM", 32, 0),
	MHI_CHANNEL_CONFIG_UL(32, "DUN", 32, 0),
	MHI_CHANNEL_CONFIG_DL(33, "DUN", 32, 0),
	/* The EDL firmware is a flash-programmer exposing firehose protocol */
	MHI_CHANNEL_CONFIG_UL_FP(34, "FIREHOSE", 32, 0),
	MHI_CHANNEL_CONFIG_DL_FP(35, "FIREHOSE", 32, 0),
	MHI_CHANNEL_CONFIG_HW_UL(100, "IP_HW0_MBIM", 128, 2),
	MHI_CHANNEL_CONFIG_HW_DL(101, "IP_HW0_MBIM", 128, 3),
पूर्ण;

अटल काष्ठा mhi_event_config mhi_quectel_em1xx_events[] = अणु
	MHI_EVENT_CONFIG_CTRL(0, 128),
	MHI_EVENT_CONFIG_DATA(1, 128),
	MHI_EVENT_CONFIG_HW_DATA(2, 1024, 100),
	MHI_EVENT_CONFIG_HW_DATA(3, 1024, 101)
पूर्ण;

अटल स्थिर काष्ठा mhi_controller_config modem_quectel_em1xx_config = अणु
	.max_channels = 128,
	.समयout_ms = 20000,
	.num_channels = ARRAY_SIZE(mhi_quectel_em1xx_channels),
	.ch_cfg = mhi_quectel_em1xx_channels,
	.num_events = ARRAY_SIZE(mhi_quectel_em1xx_events),
	.event_cfg = mhi_quectel_em1xx_events,
पूर्ण;

अटल स्थिर काष्ठा mhi_pci_dev_info mhi_quectel_em1xx_info = अणु
	.name = "quectel-em1xx",
	.edl = "qcom/prog_firehose_sdx24.mbn",
	.config = &modem_quectel_em1xx_config,
	.bar_num = MHI_PCI_DEFAULT_BAR_NUM,
	.dma_data_width = 32
पूर्ण;

अटल स्थिर काष्ठा mhi_channel_config mhi_foxconn_sdx55_channels[] = अणु
	MHI_CHANNEL_CONFIG_UL(0, "LOOPBACK", 32, 0),
	MHI_CHANNEL_CONFIG_DL(1, "LOOPBACK", 32, 0),
	MHI_CHANNEL_CONFIG_UL(4, "DIAG", 32, 1),
	MHI_CHANNEL_CONFIG_DL(5, "DIAG", 32, 1),
	MHI_CHANNEL_CONFIG_UL(12, "MBIM", 32, 0),
	MHI_CHANNEL_CONFIG_DL(13, "MBIM", 32, 0),
	MHI_CHANNEL_CONFIG_UL(32, "DUN", 32, 0),
	MHI_CHANNEL_CONFIG_DL(33, "DUN", 32, 0),
	MHI_CHANNEL_CONFIG_HW_UL(100, "IP_HW0_MBIM", 128, 2),
	MHI_CHANNEL_CONFIG_HW_DL(101, "IP_HW0_MBIM", 128, 3),
पूर्ण;

अटल काष्ठा mhi_event_config mhi_foxconn_sdx55_events[] = अणु
	MHI_EVENT_CONFIG_CTRL(0, 128),
	MHI_EVENT_CONFIG_DATA(1, 128),
	MHI_EVENT_CONFIG_HW_DATA(2, 1024, 100),
	MHI_EVENT_CONFIG_HW_DATA(3, 1024, 101)
पूर्ण;

अटल स्थिर काष्ठा mhi_controller_config modem_foxconn_sdx55_config = अणु
	.max_channels = 128,
	.समयout_ms = 20000,
	.num_channels = ARRAY_SIZE(mhi_foxconn_sdx55_channels),
	.ch_cfg = mhi_foxconn_sdx55_channels,
	.num_events = ARRAY_SIZE(mhi_foxconn_sdx55_events),
	.event_cfg = mhi_foxconn_sdx55_events,
पूर्ण;

अटल स्थिर काष्ठा mhi_pci_dev_info mhi_foxconn_sdx55_info = अणु
	.name = "foxconn-sdx55",
	.fw = "qcom/sdx55m/sbl1.mbn",
	.edl = "qcom/sdx55m/edl.mbn",
	.config = &modem_foxconn_sdx55_config,
	.bar_num = MHI_PCI_DEFAULT_BAR_NUM,
	.dma_data_width = 32
पूर्ण;

अटल स्थिर काष्ठा pci_device_id mhi_pci_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_QCOM, 0x0306),
		.driver_data = (kernel_uदीर्घ_t) &mhi_qcom_sdx55_info पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QCOM, 0x0304),
		.driver_data = (kernel_uदीर्घ_t) &mhi_qcom_sdx24_info पूर्ण,
	अणु PCI_DEVICE(0x1eac, 0x1001), /* EM120R-GL (sdx24) */
		.driver_data = (kernel_uदीर्घ_t) &mhi_quectel_em1xx_info पूर्ण,
	अणु PCI_DEVICE(0x1eac, 0x1002), /* EM160R-GL (sdx24) */
		.driver_data = (kernel_uदीर्घ_t) &mhi_quectel_em1xx_info पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QCOM, 0x0308),
		.driver_data = (kernel_uदीर्घ_t) &mhi_qcom_sdx65_info पूर्ण,
	/* T99W175 (sdx55), Both क्रम eSIM and Non-eSIM */
	अणु PCI_DEVICE(PCI_VENDOR_ID_FOXCONN, 0xe0ab),
		.driver_data = (kernel_uदीर्घ_t) &mhi_foxconn_sdx55_info पूर्ण,
	/* DW5930e (sdx55), With eSIM, It's also T99W175 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_FOXCONN, 0xe0b0),
		.driver_data = (kernel_uदीर्घ_t) &mhi_foxconn_sdx55_info पूर्ण,
	/* DW5930e (sdx55), Non-eSIM, It's also T99W175 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_FOXCONN, 0xe0b1),
		.driver_data = (kernel_uदीर्घ_t) &mhi_foxconn_sdx55_info पूर्ण,
	अणु  पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, mhi_pci_id_table);

क्रमागत mhi_pci_device_status अणु
	MHI_PCI_DEV_STARTED,
	MHI_PCI_DEV_SUSPENDED,
पूर्ण;

काष्ठा mhi_pci_device अणु
	काष्ठा mhi_controller mhi_cntrl;
	काष्ठा pci_saved_state *pci_state;
	काष्ठा work_काष्ठा recovery_work;
	काष्ठा समयr_list health_check_समयr;
	अचिन्हित दीर्घ status;
पूर्ण;

अटल पूर्णांक mhi_pci_पढ़ो_reg(काष्ठा mhi_controller *mhi_cntrl,
			    व्योम __iomem *addr, u32 *out)
अणु
	*out = पढ़ोl(addr);
	वापस 0;
पूर्ण

अटल व्योम mhi_pci_ग_लिखो_reg(काष्ठा mhi_controller *mhi_cntrl,
			      व्योम __iomem *addr, u32 val)
अणु
	ग_लिखोl(val, addr);
पूर्ण

अटल व्योम mhi_pci_status_cb(काष्ठा mhi_controller *mhi_cntrl,
			      क्रमागत mhi_callback cb)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(mhi_cntrl->cntrl_dev);

	/* Nothing to करो क्रम now */
	चयन (cb) अणु
	हाल MHI_CB_FATAL_ERROR:
	हाल MHI_CB_SYS_ERROR:
		dev_warn(&pdev->dev, "firmware crashed (%u)\n", cb);
		pm_runसमय_क्रमbid(&pdev->dev);
		अवरोध;
	हाल MHI_CB_EE_MISSION_MODE:
		pm_runसमय_allow(&pdev->dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mhi_pci_wake_get_nop(काष्ठा mhi_controller *mhi_cntrl, bool क्रमce)
अणु
	/* no-op */
पूर्ण

अटल व्योम mhi_pci_wake_put_nop(काष्ठा mhi_controller *mhi_cntrl, bool override)
अणु
	/* no-op */
पूर्ण

अटल व्योम mhi_pci_wake_toggle_nop(काष्ठा mhi_controller *mhi_cntrl)
अणु
	/* no-op */
पूर्ण

अटल bool mhi_pci_is_alive(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(mhi_cntrl->cntrl_dev);
	u16 venकरोr = 0;

	अगर (pci_पढ़ो_config_word(pdev, PCI_VENDOR_ID, &venकरोr))
		वापस false;

	अगर (venकरोr == (u16) ~0 || venकरोr == 0)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक mhi_pci_claim(काष्ठा mhi_controller *mhi_cntrl,
			 अचिन्हित पूर्णांक bar_num, u64 dma_mask)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(mhi_cntrl->cntrl_dev);
	पूर्णांक err;

	err = pci_assign_resource(pdev, bar_num);
	अगर (err)
		वापस err;

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable pci device: %d\n", err);
		वापस err;
	पूर्ण

	err = pcim_iomap_regions(pdev, 1 << bar_num, pci_name(pdev));
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to map pci region: %d\n", err);
		वापस err;
	पूर्ण
	mhi_cntrl->regs = pcim_iomap_table(pdev)[bar_num];

	err = pci_set_dma_mask(pdev, dma_mask);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot set proper DMA mask\n");
		वापस err;
	पूर्ण

	err = pci_set_consistent_dma_mask(pdev, dma_mask);
	अगर (err) अणु
		dev_err(&pdev->dev, "set consistent dma mask failed\n");
		वापस err;
	पूर्ण

	pci_set_master(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक mhi_pci_get_irqs(काष्ठा mhi_controller *mhi_cntrl,
			    स्थिर काष्ठा mhi_controller_config *mhi_cntrl_config)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(mhi_cntrl->cntrl_dev);
	पूर्णांक nr_vectors, i;
	पूर्णांक *irq;

	/*
	 * Alloc one MSI vector क्रम BHI + one vector per event ring, ideally...
	 * No explicit pci_मुक्त_irq_vectors required, करोne by pcim_release.
	 */
	mhi_cntrl->nr_irqs = 1 + mhi_cntrl_config->num_events;

	nr_vectors = pci_alloc_irq_vectors(pdev, 1, mhi_cntrl->nr_irqs, PCI_IRQ_MSI);
	अगर (nr_vectors < 0) अणु
		dev_err(&pdev->dev, "Error allocating MSI vectors %d\n",
			nr_vectors);
		वापस nr_vectors;
	पूर्ण

	अगर (nr_vectors < mhi_cntrl->nr_irqs) अणु
		dev_warn(&pdev->dev, "using shared MSI\n");

		/* Patch msi vectors, use only one (shared) */
		क्रम (i = 0; i < mhi_cntrl_config->num_events; i++)
			mhi_cntrl_config->event_cfg[i].irq = 0;
		mhi_cntrl->nr_irqs = 1;
	पूर्ण

	irq = devm_kसुस्मृति(&pdev->dev, mhi_cntrl->nr_irqs, माप(पूर्णांक), GFP_KERNEL);
	अगर (!irq)
		वापस -ENOMEM;

	क्रम (i = 0; i < mhi_cntrl->nr_irqs; i++) अणु
		पूर्णांक vector = i >= nr_vectors ? (nr_vectors - 1) : i;

		irq[i] = pci_irq_vector(pdev, vector);
	पूर्ण

	mhi_cntrl->irq = irq;

	वापस 0;
पूर्ण

अटल पूर्णांक mhi_pci_runसमय_get(काष्ठा mhi_controller *mhi_cntrl)
अणु
	/* The runसमय_get() MHI callback means:
	 *    Do whatever is requested to leave M3.
	 */
	वापस pm_runसमय_get(mhi_cntrl->cntrl_dev);
पूर्ण

अटल व्योम mhi_pci_runसमय_put(काष्ठा mhi_controller *mhi_cntrl)
अणु
	/* The runसमय_put() MHI callback means:
	 *    Device can be moved in M3 state.
	 */
	pm_runसमय_mark_last_busy(mhi_cntrl->cntrl_dev);
	pm_runसमय_put(mhi_cntrl->cntrl_dev);
पूर्ण

अटल व्योम mhi_pci_recovery_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mhi_pci_device *mhi_pdev = container_of(work, काष्ठा mhi_pci_device,
						       recovery_work);
	काष्ठा mhi_controller *mhi_cntrl = &mhi_pdev->mhi_cntrl;
	काष्ठा pci_dev *pdev = to_pci_dev(mhi_cntrl->cntrl_dev);
	पूर्णांक err;

	dev_warn(&pdev->dev, "device recovery started\n");

	del_समयr(&mhi_pdev->health_check_समयr);
	pm_runसमय_क्रमbid(&pdev->dev);

	/* Clean up MHI state */
	अगर (test_and_clear_bit(MHI_PCI_DEV_STARTED, &mhi_pdev->status)) अणु
		mhi_घातer_करोwn(mhi_cntrl, false);
		mhi_unprepare_after_घातer_करोwn(mhi_cntrl);
	पूर्ण

	pci_set_घातer_state(pdev, PCI_D0);
	pci_load_saved_state(pdev, mhi_pdev->pci_state);
	pci_restore_state(pdev);

	अगर (!mhi_pci_is_alive(mhi_cntrl))
		जाओ err_try_reset;

	err = mhi_prepare_क्रम_घातer_up(mhi_cntrl);
	अगर (err)
		जाओ err_try_reset;

	err = mhi_sync_घातer_up(mhi_cntrl);
	अगर (err)
		जाओ err_unprepare;

	dev_dbg(&pdev->dev, "Recovery completed\n");

	set_bit(MHI_PCI_DEV_STARTED, &mhi_pdev->status);
	mod_समयr(&mhi_pdev->health_check_समयr, jअगरfies + HEALTH_CHECK_PERIOD);
	वापस;

err_unprepare:
	mhi_unprepare_after_घातer_करोwn(mhi_cntrl);
err_try_reset:
	अगर (pci_reset_function(pdev))
		dev_err(&pdev->dev, "Recovery failed\n");
पूर्ण

अटल व्योम health_check(काष्ठा समयr_list *t)
अणु
	काष्ठा mhi_pci_device *mhi_pdev = from_समयr(mhi_pdev, t, health_check_समयr);
	काष्ठा mhi_controller *mhi_cntrl = &mhi_pdev->mhi_cntrl;

	अगर (!test_bit(MHI_PCI_DEV_STARTED, &mhi_pdev->status) ||
			test_bit(MHI_PCI_DEV_SUSPENDED, &mhi_pdev->status))
		वापस;

	अगर (!mhi_pci_is_alive(mhi_cntrl)) अणु
		dev_err(mhi_cntrl->cntrl_dev, "Device died\n");
		queue_work(प्रणाली_दीर्घ_wq, &mhi_pdev->recovery_work);
		वापस;
	पूर्ण

	/* reschedule in two seconds */
	mod_समयr(&mhi_pdev->health_check_समयr, jअगरfies + HEALTH_CHECK_PERIOD);
पूर्ण

अटल पूर्णांक mhi_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा mhi_pci_dev_info *info = (काष्ठा mhi_pci_dev_info *) id->driver_data;
	स्थिर काष्ठा mhi_controller_config *mhi_cntrl_config;
	काष्ठा mhi_pci_device *mhi_pdev;
	काष्ठा mhi_controller *mhi_cntrl;
	पूर्णांक err;

	dev_dbg(&pdev->dev, "MHI PCI device found: %s\n", info->name);

	/* mhi_pdev.mhi_cntrl must be zero-initialized */
	mhi_pdev = devm_kzalloc(&pdev->dev, माप(*mhi_pdev), GFP_KERNEL);
	अगर (!mhi_pdev)
		वापस -ENOMEM;

	INIT_WORK(&mhi_pdev->recovery_work, mhi_pci_recovery_work);
	समयr_setup(&mhi_pdev->health_check_समयr, health_check, 0);

	mhi_cntrl_config = info->config;
	mhi_cntrl = &mhi_pdev->mhi_cntrl;

	mhi_cntrl->cntrl_dev = &pdev->dev;
	mhi_cntrl->ioबहु_शुरू = 0;
	mhi_cntrl->iova_stop = (dma_addr_t)DMA_BIT_MASK(info->dma_data_width);
	mhi_cntrl->fw_image = info->fw;
	mhi_cntrl->edl_image = info->edl;

	mhi_cntrl->पढ़ो_reg = mhi_pci_पढ़ो_reg;
	mhi_cntrl->ग_लिखो_reg = mhi_pci_ग_लिखो_reg;
	mhi_cntrl->status_cb = mhi_pci_status_cb;
	mhi_cntrl->runसमय_get = mhi_pci_runसमय_get;
	mhi_cntrl->runसमय_put = mhi_pci_runसमय_put;
	mhi_cntrl->wake_get = mhi_pci_wake_get_nop;
	mhi_cntrl->wake_put = mhi_pci_wake_put_nop;
	mhi_cntrl->wake_toggle = mhi_pci_wake_toggle_nop;

	err = mhi_pci_claim(mhi_cntrl, info->bar_num, DMA_BIT_MASK(info->dma_data_width));
	अगर (err)
		वापस err;

	err = mhi_pci_get_irqs(mhi_cntrl, mhi_cntrl_config);
	अगर (err)
		वापस err;

	pci_set_drvdata(pdev, mhi_pdev);

	/* Have stored pci confspace at hand क्रम restore in sudden PCI error.
	 * cache the state locally and discard the PCI core one.
	 */
	pci_save_state(pdev);
	mhi_pdev->pci_state = pci_store_saved_state(pdev);
	pci_load_saved_state(pdev, शून्य);

	pci_enable_pcie_error_reporting(pdev);

	err = mhi_रेजिस्टर_controller(mhi_cntrl, mhi_cntrl_config);
	अगर (err)
		वापस err;

	/* MHI bus करोes not घातer up the controller by शेष */
	err = mhi_prepare_क्रम_घातer_up(mhi_cntrl);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to prepare MHI controller\n");
		जाओ err_unरेजिस्टर;
	पूर्ण

	err = mhi_sync_घातer_up(mhi_cntrl);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to power up MHI controller\n");
		जाओ err_unprepare;
	पूर्ण

	set_bit(MHI_PCI_DEV_STARTED, &mhi_pdev->status);

	/* start health check */
	mod_समयr(&mhi_pdev->health_check_समयr, jअगरfies + HEALTH_CHECK_PERIOD);

	/* Only allow runसमय-suspend अगर PME capable (क्रम wakeup) */
	अगर (pci_pme_capable(pdev, PCI_D3hot)) अणु
		pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 2000);
		pm_runसमय_use_स्वतःsuspend(&pdev->dev);
		pm_runसमय_mark_last_busy(&pdev->dev);
		pm_runसमय_put_noidle(&pdev->dev);
	पूर्ण

	वापस 0;

err_unprepare:
	mhi_unprepare_after_घातer_करोwn(mhi_cntrl);
err_unरेजिस्टर:
	mhi_unरेजिस्टर_controller(mhi_cntrl);

	वापस err;
पूर्ण

अटल व्योम mhi_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mhi_pci_device *mhi_pdev = pci_get_drvdata(pdev);
	काष्ठा mhi_controller *mhi_cntrl = &mhi_pdev->mhi_cntrl;

	del_समयr_sync(&mhi_pdev->health_check_समयr);
	cancel_work_sync(&mhi_pdev->recovery_work);

	अगर (test_and_clear_bit(MHI_PCI_DEV_STARTED, &mhi_pdev->status)) अणु
		mhi_घातer_करोwn(mhi_cntrl, true);
		mhi_unprepare_after_घातer_करोwn(mhi_cntrl);
	पूर्ण

	/* balancing probe put_noidle */
	अगर (pci_pme_capable(pdev, PCI_D3hot))
		pm_runसमय_get_noresume(&pdev->dev);

	mhi_unरेजिस्टर_controller(mhi_cntrl);
पूर्ण

अटल व्योम mhi_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	mhi_pci_हटाओ(pdev);
	pci_set_घातer_state(pdev, PCI_D3hot);
पूर्ण

अटल व्योम mhi_pci_reset_prepare(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mhi_pci_device *mhi_pdev = pci_get_drvdata(pdev);
	काष्ठा mhi_controller *mhi_cntrl = &mhi_pdev->mhi_cntrl;

	dev_info(&pdev->dev, "reset\n");

	del_समयr(&mhi_pdev->health_check_समयr);

	/* Clean up MHI state */
	अगर (test_and_clear_bit(MHI_PCI_DEV_STARTED, &mhi_pdev->status)) अणु
		mhi_घातer_करोwn(mhi_cntrl, false);
		mhi_unprepare_after_घातer_करोwn(mhi_cntrl);
	पूर्ण

	/* cause पूर्णांकernal device reset */
	mhi_soc_reset(mhi_cntrl);

	/* Be sure device reset has been executed */
	msleep(MHI_POST_RESET_DELAY_MS);
पूर्ण

अटल व्योम mhi_pci_reset_करोne(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mhi_pci_device *mhi_pdev = pci_get_drvdata(pdev);
	काष्ठा mhi_controller *mhi_cntrl = &mhi_pdev->mhi_cntrl;
	पूर्णांक err;

	/* Restore initial known working PCI state */
	pci_load_saved_state(pdev, mhi_pdev->pci_state);
	pci_restore_state(pdev);

	/* Is device status available ? */
	अगर (!mhi_pci_is_alive(mhi_cntrl)) अणु
		dev_err(&pdev->dev, "reset failed\n");
		वापस;
	पूर्ण

	err = mhi_prepare_क्रम_घातer_up(mhi_cntrl);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to prepare MHI controller\n");
		वापस;
	पूर्ण

	err = mhi_sync_घातer_up(mhi_cntrl);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to power up MHI controller\n");
		mhi_unprepare_after_घातer_करोwn(mhi_cntrl);
		वापस;
	पूर्ण

	set_bit(MHI_PCI_DEV_STARTED, &mhi_pdev->status);
	mod_समयr(&mhi_pdev->health_check_समयr, jअगरfies + HEALTH_CHECK_PERIOD);
पूर्ण

अटल pci_ers_result_t mhi_pci_error_detected(काष्ठा pci_dev *pdev,
					       pci_channel_state_t state)
अणु
	काष्ठा mhi_pci_device *mhi_pdev = pci_get_drvdata(pdev);
	काष्ठा mhi_controller *mhi_cntrl = &mhi_pdev->mhi_cntrl;

	dev_err(&pdev->dev, "PCI error detected, state = %u\n", state);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	/* Clean up MHI state */
	अगर (test_and_clear_bit(MHI_PCI_DEV_STARTED, &mhi_pdev->status)) अणु
		mhi_घातer_करोwn(mhi_cntrl, false);
		mhi_unprepare_after_घातer_करोwn(mhi_cntrl);
	पूर्ण अन्यथा अणु
		/* Nothing to करो */
		वापस PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	pci_disable_device(pdev);

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t mhi_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev, "Cannot re-enable PCI device after reset.\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम mhi_pci_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mhi_pci_device *mhi_pdev = pci_get_drvdata(pdev);

	dev_err(&pdev->dev, "PCI slot reset done\n");

	queue_work(प्रणाली_दीर्घ_wq, &mhi_pdev->recovery_work);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers mhi_pci_err_handler = अणु
	.error_detected = mhi_pci_error_detected,
	.slot_reset = mhi_pci_slot_reset,
	.resume = mhi_pci_io_resume,
	.reset_prepare = mhi_pci_reset_prepare,
	.reset_करोne = mhi_pci_reset_करोne,
पूर्ण;

अटल पूर्णांक  __maybe_unused mhi_pci_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा mhi_pci_device *mhi_pdev = dev_get_drvdata(dev);
	काष्ठा mhi_controller *mhi_cntrl = &mhi_pdev->mhi_cntrl;
	पूर्णांक err;

	अगर (test_and_set_bit(MHI_PCI_DEV_SUSPENDED, &mhi_pdev->status))
		वापस 0;

	del_समयr(&mhi_pdev->health_check_समयr);
	cancel_work_sync(&mhi_pdev->recovery_work);

	अगर (!test_bit(MHI_PCI_DEV_STARTED, &mhi_pdev->status) ||
			mhi_cntrl->ee != MHI_EE_AMSS)
		जाओ pci_suspend; /* Nothing to करो at MHI level */

	/* Transition to M3 state */
	err = mhi_pm_suspend(mhi_cntrl);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to suspend device: %d\n", err);
		clear_bit(MHI_PCI_DEV_SUSPENDED, &mhi_pdev->status);
		वापस -EBUSY;
	पूर्ण

pci_suspend:
	pci_disable_device(pdev);
	pci_wake_from_d3(pdev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mhi_pci_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा mhi_pci_device *mhi_pdev = dev_get_drvdata(dev);
	काष्ठा mhi_controller *mhi_cntrl = &mhi_pdev->mhi_cntrl;
	पूर्णांक err;

	अगर (!test_and_clear_bit(MHI_PCI_DEV_SUSPENDED, &mhi_pdev->status))
		वापस 0;

	err = pci_enable_device(pdev);
	अगर (err)
		जाओ err_recovery;

	pci_set_master(pdev);
	pci_wake_from_d3(pdev, false);

	अगर (!test_bit(MHI_PCI_DEV_STARTED, &mhi_pdev->status) ||
			mhi_cntrl->ee != MHI_EE_AMSS)
		वापस 0; /* Nothing to करो at MHI level */

	/* Exit M3, transition to M0 state */
	err = mhi_pm_resume(mhi_cntrl);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to resume device: %d\n", err);
		जाओ err_recovery;
	पूर्ण

	/* Resume health check */
	mod_समयr(&mhi_pdev->health_check_समयr, jअगरfies + HEALTH_CHECK_PERIOD);

	/* It can be a remote wakeup (no mhi runसमय_get), update access समय */
	pm_runसमय_mark_last_busy(dev);

	वापस 0;

err_recovery:
	/* Do not fail to not mess up our PCI device state, the device likely
	 * lost घातer (d3cold) and we simply need to reset it from the recovery
	 * procedure, trigger the recovery asynchronously to prevent प्रणाली
	 * suspend निकास delaying.
	 */
	queue_work(प्रणाली_दीर्घ_wq, &mhi_pdev->recovery_work);
	pm_runसमय_mark_last_busy(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक  __maybe_unused mhi_pci_suspend(काष्ठा device *dev)
अणु
	pm_runसमय_disable(dev);
	वापस mhi_pci_runसमय_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused mhi_pci_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	/* Depending the platक्रमm, device may have lost घातer (d3cold), we need
	 * to resume it now to check its state and recover when necessary.
	 */
	ret = mhi_pci_runसमय_resume(dev);
	pm_runसमय_enable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused mhi_pci_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा mhi_pci_device *mhi_pdev = dev_get_drvdata(dev);
	काष्ठा mhi_controller *mhi_cntrl = &mhi_pdev->mhi_cntrl;

	/* We want to stop all operations, hibernation करोes not guarantee that
	 * device will be in the same state as beक्रमe मुक्तzing, especially अगर
	 * the पूर्णांकermediate restore kernel reinitializes MHI device with new
	 * context.
	 */
	अगर (test_and_clear_bit(MHI_PCI_DEV_STARTED, &mhi_pdev->status)) अणु
		mhi_घातer_करोwn(mhi_cntrl, false);
		mhi_unprepare_after_घातer_करोwn(mhi_cntrl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mhi_pci_restore(काष्ठा device *dev)
अणु
	काष्ठा mhi_pci_device *mhi_pdev = dev_get_drvdata(dev);

	/* Reinitialize the device */
	queue_work(प्रणाली_दीर्घ_wq, &mhi_pdev->recovery_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mhi_pci_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mhi_pci_runसमय_suspend, mhi_pci_runसमय_resume, शून्य)
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend = mhi_pci_suspend,
	.resume = mhi_pci_resume,
	.मुक्तze = mhi_pci_मुक्तze,
	.thaw = mhi_pci_restore,
	.restore = mhi_pci_restore,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा pci_driver mhi_pci_driver = अणु
	.name		= "mhi-pci-generic",
	.id_table	= mhi_pci_id_table,
	.probe		= mhi_pci_probe,
	.हटाओ		= mhi_pci_हटाओ,
	.shutकरोwn	= mhi_pci_shutकरोwn,
	.err_handler	= &mhi_pci_err_handler,
	.driver.pm	= &mhi_pci_pm_ops
पूर्ण;
module_pci_driver(mhi_pci_driver);

MODULE_AUTHOR("Loic Poulain <loic.poulain@linaro.org>");
MODULE_DESCRIPTION("Modem Host Interface (MHI) PCI controller driver");
MODULE_LICENSE("GPL");
