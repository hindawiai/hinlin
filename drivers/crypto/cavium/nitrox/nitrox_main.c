<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/aer.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>

#समावेश "nitrox_dev.h"
#समावेश "nitrox_common.h"
#समावेश "nitrox_csr.h"
#समावेश "nitrox_hal.h"
#समावेश "nitrox_isr.h"
#समावेश "nitrox_debugfs.h"

#घोषणा CNN55XX_DEV_ID	0x12
#घोषणा UCODE_HLEN 48
#घोषणा DEFAULT_SE_GROUP 0
#घोषणा DEFAULT_AE_GROUP 0

#घोषणा DRIVER_VERSION "1.2"
#घोषणा CNN55XX_UCD_BLOCK_SIZE 32768
#घोषणा CNN55XX_MAX_UCODE_SIZE (CNN55XX_UCD_BLOCK_SIZE * 2)
#घोषणा FW_सूची "cavium/"
/* SE microcode */
#घोषणा SE_FW	FW_सूची "cnn55xx_se.fw"
/* AE microcode */
#घोषणा AE_FW	FW_सूची "cnn55xx_ae.fw"

अटल स्थिर अक्षर nitrox_driver_name[] = "CNN55XX";

अटल LIST_HEAD(ndevlist);
अटल DEFINE_MUTEX(devlist_lock);
अटल अचिन्हित पूर्णांक num_devices;

/**
 * nitrox_pci_tbl - PCI Device ID Table
 */
अटल स्थिर काष्ठा pci_device_id nitrox_pci_tbl[] = अणु
	अणुPCI_VDEVICE(CAVIUM, CNN55XX_DEV_ID), 0पूर्ण,
	/* required last entry */
	अणु0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, nitrox_pci_tbl);

अटल अचिन्हित पूर्णांक qlen = DEFAULT_CMD_QLEN;
module_param(qlen, uपूर्णांक, 0644);
MODULE_PARM_DESC(qlen, "Command queue length - default 2048");

/**
 * काष्ठा ucode - Firmware Header
 * @id: microcode ID
 * @version: firmware version
 * @code_size: code section size
 * @raz: alignment
 * @code: code section
 */
काष्ठा ucode अणु
	u8 id;
	अक्षर version[VERSION_LEN - 1];
	__be32 code_size;
	u8 raz[12];
	u64 code[];
पूर्ण;

/**
 * ग_लिखो_to_ucd_unit - Write Firmware to NITROX UCD unit
 */
अटल व्योम ग_लिखो_to_ucd_unit(काष्ठा nitrox_device *ndev, u32 ucode_size,
			      u64 *ucode_data, पूर्णांक block_num)
अणु
	u32 code_size;
	u64 offset, data;
	पूर्णांक i = 0;

	/*
	 * UCD काष्ठाure
	 *
	 *  -------------
	 *  |    BLK 7  |
	 *  -------------
	 *  |    BLK 6  |
	 *  -------------
	 *  |    ...    |
	 *  -------------
	 *  |    BLK 0  |
	 *  -------------
	 *  Total of 8 blocks, each size 32KB
	 */

	/* set the block number */
	offset = UCD_UCODE_LOAD_BLOCK_NUM;
	nitrox_ग_लिखो_csr(ndev, offset, block_num);

	code_size = roundup(ucode_size, 16);
	जबतक (code_size) अणु
		data = ucode_data[i];
		/* ग_लिखो 8 bytes at a समय */
		offset = UCD_UCODE_LOAD_IDX_DATAX(i);
		nitrox_ग_लिखो_csr(ndev, offset, data);
		code_size -= 8;
		i++;
	पूर्ण

	usleep_range(300, 400);
पूर्ण

अटल पूर्णांक nitrox_load_fw(काष्ठा nitrox_device *ndev)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name;
	काष्ठा ucode *ucode;
	u64 *ucode_data;
	u64 offset;
	जोड़ ucd_core_eid_ucode_block_num core_2_eid_val;
	जोड़ aqm_grp_execmsk_lo aqm_grp_execmask_lo;
	जोड़ aqm_grp_execmsk_hi aqm_grp_execmask_hi;
	u32 ucode_size;
	पूर्णांक ret, i = 0;

	fw_name = SE_FW;
	dev_info(DEV(ndev), "Loading firmware \"%s\"\n", fw_name);

	ret = request_firmware(&fw, fw_name, DEV(ndev));
	अगर (ret < 0) अणु
		dev_err(DEV(ndev), "failed to get firmware %s\n", fw_name);
		वापस ret;
	पूर्ण

	ucode = (काष्ठा ucode *)fw->data;

	ucode_size = be32_to_cpu(ucode->code_size) * 2;
	अगर (!ucode_size || ucode_size > CNN55XX_MAX_UCODE_SIZE) अणु
		dev_err(DEV(ndev), "Invalid ucode size: %u for firmware %s\n",
			ucode_size, fw_name);
		release_firmware(fw);
		वापस -EINVAL;
	पूर्ण
	ucode_data = ucode->code;

	/* copy the firmware version */
	स_नकल(&ndev->hw.fw_name[0][0], ucode->version, (VERSION_LEN - 2));
	ndev->hw.fw_name[0][VERSION_LEN - 1] = '\0';

	/* Load SE Firmware on UCD Block 0 */
	ग_लिखो_to_ucd_unit(ndev, ucode_size, ucode_data, 0);

	release_firmware(fw);

	/* put all SE cores in DEFAULT_SE_GROUP */
	offset = POM_GRP_EXECMASKX(DEFAULT_SE_GROUP);
	nitrox_ग_लिखो_csr(ndev, offset, (~0ULL));

	/* ग_लिखो block number and firmware length
	 * bit:<2:0> block number
	 * bit:3 is set SE uses 32KB microcode
	 * bit:3 is clear SE uses 64KB microcode
	 */
	core_2_eid_val.value = 0ULL;
	core_2_eid_val.ucode_blk = 0;
	अगर (ucode_size <= CNN55XX_UCD_BLOCK_SIZE)
		core_2_eid_val.ucode_len = 1;
	अन्यथा
		core_2_eid_val.ucode_len = 0;

	क्रम (i = 0; i < ndev->hw.se_cores; i++) अणु
		offset = UCD_SE_EID_UCODE_BLOCK_NUMX(i);
		nitrox_ग_लिखो_csr(ndev, offset, core_2_eid_val.value);
	पूर्ण


	fw_name = AE_FW;
	dev_info(DEV(ndev), "Loading firmware \"%s\"\n", fw_name);

	ret = request_firmware(&fw, fw_name, DEV(ndev));
	अगर (ret < 0) अणु
		dev_err(DEV(ndev), "failed to get firmware %s\n", fw_name);
		वापस ret;
	पूर्ण

	ucode = (काष्ठा ucode *)fw->data;

	ucode_size = be32_to_cpu(ucode->code_size) * 2;
	अगर (!ucode_size || ucode_size > CNN55XX_MAX_UCODE_SIZE) अणु
		dev_err(DEV(ndev), "Invalid ucode size: %u for firmware %s\n",
			ucode_size, fw_name);
		release_firmware(fw);
		वापस -EINVAL;
	पूर्ण
	ucode_data = ucode->code;

	/* copy the firmware version */
	स_नकल(&ndev->hw.fw_name[1][0], ucode->version, (VERSION_LEN - 2));
	ndev->hw.fw_name[1][VERSION_LEN - 1] = '\0';

	/* Load AE Firmware on UCD Block 2 */
	ग_लिखो_to_ucd_unit(ndev, ucode_size, ucode_data, 2);

	release_firmware(fw);

	/* put all AE cores in DEFAULT_AE_GROUP */
	offset = AQM_GRP_EXECMSK_LOX(DEFAULT_AE_GROUP);
	aqm_grp_execmask_lo.exec_0_to_39 = 0xFFFFFFFFFFULL;
	nitrox_ग_लिखो_csr(ndev, offset, aqm_grp_execmask_lo.value);
	offset = AQM_GRP_EXECMSK_HIX(DEFAULT_AE_GROUP);
	aqm_grp_execmask_hi.exec_40_to_79 = 0xFFFFFFFFFFULL;
	nitrox_ग_लिखो_csr(ndev, offset, aqm_grp_execmask_hi.value);

	/* ग_लिखो block number and firmware length
	 * bit:<2:0> block number
	 * bit:3 is set AE uses 32KB microcode
	 * bit:3 is clear AE uses 64KB microcode
	 */
	core_2_eid_val.value = 0ULL;
	core_2_eid_val.ucode_blk = 2;
	अगर (ucode_size <= CNN55XX_UCD_BLOCK_SIZE)
		core_2_eid_val.ucode_len = 1;
	अन्यथा
		core_2_eid_val.ucode_len = 0;

	क्रम (i = 0; i < ndev->hw.ae_cores; i++) अणु
		offset = UCD_AE_EID_UCODE_BLOCK_NUMX(i);
		nitrox_ग_लिखो_csr(ndev, offset, core_2_eid_val.value);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * nitrox_add_to_devlist - add NITROX device to global device list
 * @ndev: NITROX device
 */
अटल पूर्णांक nitrox_add_to_devlist(काष्ठा nitrox_device *ndev)
अणु
	काष्ठा nitrox_device *dev;
	पूर्णांक ret = 0;

	INIT_LIST_HEAD(&ndev->list);
	refcount_set(&ndev->refcnt, 1);

	mutex_lock(&devlist_lock);
	list_क्रम_each_entry(dev, &ndevlist, list) अणु
		अगर (dev == ndev) अणु
			ret = -EEXIST;
			जाओ unlock;
		पूर्ण
	पूर्ण
	ndev->idx = num_devices++;
	list_add_tail(&ndev->list, &ndevlist);
unlock:
	mutex_unlock(&devlist_lock);
	वापस ret;
पूर्ण

/**
 * nitrox_हटाओ_from_devlist - हटाओ NITROX device from
 *   global device list
 * @ndev: NITROX device
 */
अटल व्योम nitrox_हटाओ_from_devlist(काष्ठा nitrox_device *ndev)
अणु
	mutex_lock(&devlist_lock);
	list_del(&ndev->list);
	num_devices--;
	mutex_unlock(&devlist_lock);
पूर्ण

काष्ठा nitrox_device *nitrox_get_first_device(व्योम)
अणु
	काष्ठा nitrox_device *ndev;

	mutex_lock(&devlist_lock);
	list_क्रम_each_entry(ndev, &ndevlist, list) अणु
		अगर (nitrox_पढ़ोy(ndev))
			अवरोध;
	पूर्ण
	mutex_unlock(&devlist_lock);
	अगर (&ndev->list == &ndevlist)
		वापस शून्य;

	refcount_inc(&ndev->refcnt);
	/* barrier to sync with other cpus */
	smp_mb__after_atomic();
	वापस ndev;
पूर्ण

व्योम nitrox_put_device(काष्ठा nitrox_device *ndev)
अणु
	अगर (!ndev)
		वापस;

	refcount_dec(&ndev->refcnt);
	/* barrier to sync with other cpus */
	smp_mb__after_atomic();
पूर्ण

अटल पूर्णांक nitrox_device_flr(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक pos = 0;

	pos = pci_save_state(pdev);
	अगर (pos) अणु
		dev_err(&pdev->dev, "Failed to save pci state\n");
		वापस -ENOMEM;
	पूर्ण

	/* check flr support */
	अगर (pcie_has_flr(pdev))
		pcie_flr(pdev);

	pci_restore_state(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक nitrox_pf_sw_init(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक err;

	err = nitrox_common_sw_init(ndev);
	अगर (err)
		वापस err;

	err = nitrox_रेजिस्टर_पूर्णांकerrupts(ndev);
	अगर (err)
		nitrox_common_sw_cleanup(ndev);

	वापस err;
पूर्ण

अटल व्योम nitrox_pf_sw_cleanup(काष्ठा nitrox_device *ndev)
अणु
	nitrox_unरेजिस्टर_पूर्णांकerrupts(ndev);
	nitrox_common_sw_cleanup(ndev);
पूर्ण

/**
 * nitrox_bist_check - Check NITROX BIST रेजिस्टरs status
 * @ndev: NITROX device
 */
अटल पूर्णांक nitrox_bist_check(काष्ठा nitrox_device *ndev)
अणु
	u64 value = 0;
	पूर्णांक i;

	क्रम (i = 0; i < NR_CLUSTERS; i++) अणु
		value += nitrox_पढ़ो_csr(ndev, EMU_BIST_STATUSX(i));
		value += nitrox_पढ़ो_csr(ndev, EFL_CORE_BIST_REGX(i));
	पूर्ण
	value += nitrox_पढ़ो_csr(ndev, UCD_BIST_STATUS);
	value += nitrox_पढ़ो_csr(ndev, NPS_CORE_BIST_REG);
	value += nitrox_पढ़ो_csr(ndev, NPS_CORE_NPC_BIST_REG);
	value += nitrox_पढ़ो_csr(ndev, NPS_PKT_SLC_BIST_REG);
	value += nitrox_पढ़ो_csr(ndev, NPS_PKT_IN_BIST_REG);
	value += nitrox_पढ़ो_csr(ndev, POM_BIST_REG);
	value += nitrox_पढ़ो_csr(ndev, BMI_BIST_REG);
	value += nitrox_पढ़ो_csr(ndev, EFL_TOP_BIST_STAT);
	value += nitrox_पढ़ो_csr(ndev, BMO_BIST_REG);
	value += nitrox_पढ़ो_csr(ndev, LBC_BIST_STATUS);
	value += nitrox_पढ़ो_csr(ndev, PEM_BIST_STATUSX(0));
	अगर (value)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक nitrox_pf_hw_init(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक err;

	err = nitrox_bist_check(ndev);
	अगर (err) अणु
		dev_err(&ndev->pdev->dev, "BIST check failed\n");
		वापस err;
	पूर्ण
	/* get cores inक्रमmation */
	nitrox_get_hwinfo(ndev);

	nitrox_config_nps_core_unit(ndev);
	nitrox_config_aqm_unit(ndev);
	nitrox_config_nps_pkt_unit(ndev);
	nitrox_config_pom_unit(ndev);
	nitrox_config_efl_unit(ndev);
	/* configure IO units */
	nitrox_config_bmi_unit(ndev);
	nitrox_config_bmo_unit(ndev);
	/* configure Local Buffer Cache */
	nitrox_config_lbc_unit(ndev);
	nitrox_config_अक्रम_unit(ndev);

	/* load firmware on cores */
	err = nitrox_load_fw(ndev);
	अगर (err)
		वापस err;

	nitrox_config_emu_unit(ndev);

	वापस 0;
पूर्ण

/**
 * nitrox_probe - NITROX Initialization function.
 * @pdev: PCI device inक्रमmation काष्ठा
 * @id: entry in nitrox_pci_tbl
 *
 * Return: 0, अगर the driver is bound to the device, or
 *         a negative error अगर there is failure.
 */
अटल पूर्णांक nitrox_probe(काष्ठा pci_dev *pdev,
			स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा nitrox_device *ndev;
	पूर्णांक err;

	dev_info_once(&pdev->dev, "%s driver version %s\n",
		      nitrox_driver_name, DRIVER_VERSION);

	err = pci_enable_device_mem(pdev);
	अगर (err)
		वापस err;

	/* करो FLR */
	err = nitrox_device_flr(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "FLR failed\n");
		pci_disable_device(pdev);
		वापस err;
	पूर्ण

	अगर (!dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64))) अणु
		dev_dbg(&pdev->dev, "DMA to 64-BIT address\n");
	पूर्ण अन्यथा अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "DMA configuration failed\n");
			pci_disable_device(pdev);
			वापस err;
		पूर्ण
	पूर्ण

	err = pci_request_mem_regions(pdev, nitrox_driver_name);
	अगर (err) अणु
		pci_disable_device(pdev);
		वापस err;
	पूर्ण
	pci_set_master(pdev);

	ndev = kzalloc(माप(*ndev), GFP_KERNEL);
	अगर (!ndev) अणु
		err = -ENOMEM;
		जाओ ndev_fail;
	पूर्ण

	pci_set_drvdata(pdev, ndev);
	ndev->pdev = pdev;

	/* add to device list */
	nitrox_add_to_devlist(ndev);

	ndev->hw.venकरोr_id = pdev->venकरोr;
	ndev->hw.device_id = pdev->device;
	ndev->hw.revision_id = pdev->revision;
	/* command समयout in jअगरfies */
	ndev->समयout = msecs_to_jअगरfies(CMD_TIMEOUT);
	ndev->node = dev_to_node(&pdev->dev);
	अगर (ndev->node == NUMA_NO_NODE)
		ndev->node = 0;

	ndev->bar_addr = ioremap(pci_resource_start(pdev, 0),
				 pci_resource_len(pdev, 0));
	अगर (!ndev->bar_addr) अणु
		err = -EIO;
		जाओ ioremap_err;
	पूर्ण
	/* allocate command queus based on cpus, max queues are 64 */
	ndev->nr_queues = min_t(u32, MAX_PF_QUEUES, num_online_cpus());
	ndev->qlen = qlen;

	err = nitrox_pf_sw_init(ndev);
	अगर (err)
		जाओ ioremap_err;

	err = nitrox_pf_hw_init(ndev);
	अगर (err)
		जाओ pf_hw_fail;

	nitrox_debugfs_init(ndev);

	/* clear the statistics */
	atomic64_set(&ndev->stats.posted, 0);
	atomic64_set(&ndev->stats.completed, 0);
	atomic64_set(&ndev->stats.dropped, 0);

	atomic_set(&ndev->state, __NDEV_READY);
	/* barrier to sync with other cpus */
	smp_mb__after_atomic();

	err = nitrox_crypto_रेजिस्टर();
	अगर (err)
		जाओ crypto_fail;

	वापस 0;

crypto_fail:
	nitrox_debugfs_निकास(ndev);
	atomic_set(&ndev->state, __NDEV_NOT_READY);
	/* barrier to sync with other cpus */
	smp_mb__after_atomic();
pf_hw_fail:
	nitrox_pf_sw_cleanup(ndev);
ioremap_err:
	nitrox_हटाओ_from_devlist(ndev);
	kमुक्त(ndev);
	pci_set_drvdata(pdev, शून्य);
ndev_fail:
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * nitrox_हटाओ - Unbind the driver from the device.
 * @pdev: PCI device inक्रमmation काष्ठा
 */
अटल व्योम nitrox_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा nitrox_device *ndev = pci_get_drvdata(pdev);

	अगर (!ndev)
		वापस;

	अगर (!refcount_dec_and_test(&ndev->refcnt)) अणु
		dev_err(DEV(ndev), "Device refcnt not zero (%d)\n",
			refcount_पढ़ो(&ndev->refcnt));
		वापस;
	पूर्ण

	dev_info(DEV(ndev), "Removing Device %x:%x\n",
		 ndev->hw.venकरोr_id, ndev->hw.device_id);

	atomic_set(&ndev->state, __NDEV_NOT_READY);
	/* barrier to sync with other cpus */
	smp_mb__after_atomic();

	nitrox_हटाओ_from_devlist(ndev);

	/* disable SR-IOV */
	nitrox_sriov_configure(pdev, 0);
	nitrox_crypto_unरेजिस्टर();
	nitrox_debugfs_निकास(ndev);
	nitrox_pf_sw_cleanup(ndev);

	iounmap(ndev->bar_addr);
	kमुक्त(ndev);

	pci_set_drvdata(pdev, शून्य);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल व्योम nitrox_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	pci_set_drvdata(pdev, शून्य);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver nitrox_driver = अणु
	.name = nitrox_driver_name,
	.id_table = nitrox_pci_tbl,
	.probe = nitrox_probe,
	.हटाओ	= nitrox_हटाओ,
	.shutकरोwn = nitrox_shutकरोwn,
	.sriov_configure = nitrox_sriov_configure,
पूर्ण;

module_pci_driver(nitrox_driver);

MODULE_AUTHOR("Srikanth Jampala <Jampala.Srikanth@cavium.com>");
MODULE_DESCRIPTION("Cavium CNN55XX PF Driver" DRIVER_VERSION " ");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);
MODULE_FIRMWARE(SE_FW);
