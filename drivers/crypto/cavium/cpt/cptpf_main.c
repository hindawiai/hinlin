<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Cavium, Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश "cptpf.h"

#घोषणा DRV_NAME	"thunder-cpt"
#घोषणा DRV_VERSION	"1.0"

अटल u32 num_vfs = 4; /* Default 4 VF enabled */
module_param(num_vfs, uपूर्णांक, 0444);
MODULE_PARM_DESC(num_vfs, "Number of VFs to enable(1-16)");

/*
 * Disable cores specअगरied by coremask
 */
अटल व्योम cpt_disable_cores(काष्ठा cpt_device *cpt, u64 coremask,
			      u8 type, u8 grp)
अणु
	u64 pf_exe_ctl;
	u32 समयout = 100;
	u64 grpmask = 0;
	काष्ठा device *dev = &cpt->pdev->dev;

	अगर (type == AE_TYPES)
		coremask = (coremask << cpt->max_se_cores);

	/* Disengage the cores from groups */
	grpmask = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_GX_EN(0, grp));
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_GX_EN(0, grp),
			(grpmask & ~coremask));
	udelay(CSR_DELAY);
	grp = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_EXEC_BUSY(0));
	जबतक (grp & coremask) अणु
		dev_err(dev, "Cores still busy %llx", coremask);
		grp = cpt_पढ़ो_csr64(cpt->reg_base,
				     CPTX_PF_EXEC_BUSY(0));
		अगर (समयout--)
			अवरोध;

		udelay(CSR_DELAY);
	पूर्ण

	/* Disable the cores */
	pf_exe_ctl = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_EXE_CTL(0));
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_EXE_CTL(0),
			(pf_exe_ctl & ~coremask));
	udelay(CSR_DELAY);
पूर्ण

/*
 * Enable cores specअगरied by coremask
 */
अटल व्योम cpt_enable_cores(काष्ठा cpt_device *cpt, u64 coremask,
			     u8 type)
अणु
	u64 pf_exe_ctl;

	अगर (type == AE_TYPES)
		coremask = (coremask << cpt->max_se_cores);

	pf_exe_ctl = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_EXE_CTL(0));
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_EXE_CTL(0),
			(pf_exe_ctl | coremask));
	udelay(CSR_DELAY);
पूर्ण

अटल व्योम cpt_configure_group(काष्ठा cpt_device *cpt, u8 grp,
				u64 coremask, u8 type)
अणु
	u64 pf_gx_en = 0;

	अगर (type == AE_TYPES)
		coremask = (coremask << cpt->max_se_cores);

	pf_gx_en = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_GX_EN(0, grp));
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_GX_EN(0, grp),
			(pf_gx_en | coremask));
	udelay(CSR_DELAY);
पूर्ण

अटल व्योम cpt_disable_mbox_पूर्णांकerrupts(काष्ठा cpt_device *cpt)
अणु
	/* Clear mbox(0) पूर्णांकerupts क्रम all vfs */
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_MBOX_ENA_W1CX(0, 0), ~0ull);
पूर्ण

अटल व्योम cpt_disable_ecc_पूर्णांकerrupts(काष्ठा cpt_device *cpt)
अणु
	/* Clear ecc(0) पूर्णांकerupts क्रम all vfs */
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_ECC0_ENA_W1C(0), ~0ull);
पूर्ण

अटल व्योम cpt_disable_exec_पूर्णांकerrupts(काष्ठा cpt_device *cpt)
अणु
	/* Clear exec पूर्णांकerupts क्रम all vfs */
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_EXEC_ENA_W1C(0), ~0ull);
पूर्ण

अटल व्योम cpt_disable_all_पूर्णांकerrupts(काष्ठा cpt_device *cpt)
अणु
	cpt_disable_mbox_पूर्णांकerrupts(cpt);
	cpt_disable_ecc_पूर्णांकerrupts(cpt);
	cpt_disable_exec_पूर्णांकerrupts(cpt);
पूर्ण

अटल व्योम cpt_enable_mbox_पूर्णांकerrupts(काष्ठा cpt_device *cpt)
अणु
	/* Set mbox(0) पूर्णांकerupts क्रम all vfs */
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_MBOX_ENA_W1SX(0, 0), ~0ull);
पूर्ण

अटल पूर्णांक cpt_load_microcode(काष्ठा cpt_device *cpt, काष्ठा microcode *mcode)
अणु
	पूर्णांक ret = 0, core = 0, shअगरt = 0;
	u32 total_cores = 0;
	काष्ठा device *dev = &cpt->pdev->dev;

	अगर (!mcode || !mcode->code) अणु
		dev_err(dev, "Either the mcode is null or data is NULL\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mcode->code_size == 0) अणु
		dev_err(dev, "microcode size is 0\n");
		वापस -EINVAL;
	पूर्ण

	/* Assumes 0-9 are SE cores क्रम UCODE_BASE रेजिस्टरs and
	 * AE core bases follow
	 */
	अगर (mcode->is_ae) अणु
		core = CPT_MAX_SE_CORES; /* start couting from 10 */
		total_cores = CPT_MAX_TOTAL_CORES; /* upto 15 */
	पूर्ण अन्यथा अणु
		core = 0; /* start couting from 0 */
		total_cores = CPT_MAX_SE_CORES; /* upto 9 */
	पूर्ण

	/* Poपूर्णांक to microcode क्रम each core of the group */
	क्रम (; core < total_cores ; core++, shअगरt++) अणु
		अगर (mcode->core_mask & (1 << shअगरt)) अणु
			cpt_ग_लिखो_csr64(cpt->reg_base,
					CPTX_PF_ENGX_UCODE_BASE(0, core),
					(u64)mcode->phys_base);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक करो_cpt_init(काष्ठा cpt_device *cpt, काष्ठा microcode *mcode)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = &cpt->pdev->dev;

	/* Make device not पढ़ोy */
	cpt->flags &= ~CPT_FLAG_DEVICE_READY;
	/* Disable All PF पूर्णांकerrupts */
	cpt_disable_all_पूर्णांकerrupts(cpt);
	/* Calculate mcode group and coremasks */
	अगर (mcode->is_ae) अणु
		अगर (mcode->num_cores > cpt->max_ae_cores) अणु
			dev_err(dev, "Requested for more cores than available AE cores\n");
			ret = -EINVAL;
			जाओ cpt_init_fail;
		पूर्ण

		अगर (cpt->next_group >= CPT_MAX_CORE_GROUPS) अणु
			dev_err(dev, "Can't load, all eight microcode groups in use");
			वापस -ENखाता;
		पूर्ण

		mcode->group = cpt->next_group;
		/* Convert requested cores to mask */
		mcode->core_mask = GENMASK(mcode->num_cores, 0);
		cpt_disable_cores(cpt, mcode->core_mask, AE_TYPES,
				  mcode->group);
		/* Load microcode क्रम AE engines */
		ret = cpt_load_microcode(cpt, mcode);
		अगर (ret) अणु
			dev_err(dev, "Microcode load Failed for %s\n",
				mcode->version);
			जाओ cpt_init_fail;
		पूर्ण
		cpt->next_group++;
		/* Configure group mask क्रम the mcode */
		cpt_configure_group(cpt, mcode->group, mcode->core_mask,
				    AE_TYPES);
		/* Enable AE cores क्रम the group mask */
		cpt_enable_cores(cpt, mcode->core_mask, AE_TYPES);
	पूर्ण अन्यथा अणु
		अगर (mcode->num_cores > cpt->max_se_cores) अणु
			dev_err(dev, "Requested for more cores than available SE cores\n");
			ret = -EINVAL;
			जाओ cpt_init_fail;
		पूर्ण
		अगर (cpt->next_group >= CPT_MAX_CORE_GROUPS) अणु
			dev_err(dev, "Can't load, all eight microcode groups in use");
			वापस -ENखाता;
		पूर्ण

		mcode->group = cpt->next_group;
		/* Covert requested cores to mask */
		mcode->core_mask = GENMASK(mcode->num_cores, 0);
		cpt_disable_cores(cpt, mcode->core_mask, SE_TYPES,
				  mcode->group);
		/* Load microcode क्रम SE engines */
		ret = cpt_load_microcode(cpt, mcode);
		अगर (ret) अणु
			dev_err(dev, "Microcode load Failed for %s\n",
				mcode->version);
			जाओ cpt_init_fail;
		पूर्ण
		cpt->next_group++;
		/* Configure group mask क्रम the mcode */
		cpt_configure_group(cpt, mcode->group, mcode->core_mask,
				    SE_TYPES);
		/* Enable SE cores क्रम the group mask */
		cpt_enable_cores(cpt, mcode->core_mask, SE_TYPES);
	पूर्ण

	/* Enabled PF mailbox पूर्णांकerrupts */
	cpt_enable_mbox_पूर्णांकerrupts(cpt);
	cpt->flags |= CPT_FLAG_DEVICE_READY;

	वापस ret;

cpt_init_fail:
	/* Enabled PF mailbox पूर्णांकerrupts */
	cpt_enable_mbox_पूर्णांकerrupts(cpt);

	वापस ret;
पूर्ण

काष्ठा ucode_header अणु
	u8 version[CPT_UCODE_VERSION_SZ];
	__be32 code_length;
	u32 data_length;
	u64 sram_address;
पूर्ण;

अटल पूर्णांक cpt_ucode_load_fw(काष्ठा cpt_device *cpt, स्थिर u8 *fw, bool is_ae)
अणु
	स्थिर काष्ठा firmware *fw_entry;
	काष्ठा device *dev = &cpt->pdev->dev;
	काष्ठा ucode_header *ucode;
	काष्ठा microcode *mcode;
	पूर्णांक j, ret = 0;

	ret = request_firmware(&fw_entry, fw, dev);
	अगर (ret)
		वापस ret;

	ucode = (काष्ठा ucode_header *)fw_entry->data;
	mcode = &cpt->mcode[cpt->next_mc_idx];
	स_नकल(mcode->version, (u8 *)fw_entry->data, CPT_UCODE_VERSION_SZ);
	mcode->code_size = ntohl(ucode->code_length) * 2;
	अगर (!mcode->code_size) अणु
		ret = -EINVAL;
		जाओ fw_release;
	पूर्ण

	mcode->is_ae = is_ae;
	mcode->core_mask = 0ULL;
	mcode->num_cores = is_ae ? 6 : 10;

	/*  Allocate DMAable space */
	mcode->code = dma_alloc_coherent(&cpt->pdev->dev, mcode->code_size,
					 &mcode->phys_base, GFP_KERNEL);
	अगर (!mcode->code) अणु
		dev_err(dev, "Unable to allocate space for microcode");
		ret = -ENOMEM;
		जाओ fw_release;
	पूर्ण

	स_नकल((व्योम *)mcode->code, (व्योम *)(fw_entry->data + माप(*ucode)),
	       mcode->code_size);

	/* Byte swap 64-bit */
	क्रम (j = 0; j < (mcode->code_size / 8); j++)
		((__be64 *)mcode->code)[j] = cpu_to_be64(((u64 *)mcode->code)[j]);
	/*  MC needs 16-bit swap */
	क्रम (j = 0; j < (mcode->code_size / 2); j++)
		((__be16 *)mcode->code)[j] = cpu_to_be16(((u16 *)mcode->code)[j]);

	dev_dbg(dev, "mcode->code_size = %u\n", mcode->code_size);
	dev_dbg(dev, "mcode->is_ae = %u\n", mcode->is_ae);
	dev_dbg(dev, "mcode->num_cores = %u\n", mcode->num_cores);
	dev_dbg(dev, "mcode->code = %llx\n", (u64)mcode->code);
	dev_dbg(dev, "mcode->phys_base = %llx\n", mcode->phys_base);

	ret = करो_cpt_init(cpt, mcode);
	अगर (ret) अणु
		dev_err(dev, "do_cpt_init failed with ret: %d\n", ret);
		जाओ fw_release;
	पूर्ण

	dev_info(dev, "Microcode Loaded %s\n", mcode->version);
	mcode->is_mc_valid = 1;
	cpt->next_mc_idx++;

fw_release:
	release_firmware(fw_entry);

	वापस ret;
पूर्ण

अटल पूर्णांक cpt_ucode_load(काष्ठा cpt_device *cpt)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = &cpt->pdev->dev;

	ret = cpt_ucode_load_fw(cpt, "cpt8x-mc-ae.out", true);
	अगर (ret) अणु
		dev_err(dev, "ae:cpt_ucode_load failed with ret: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = cpt_ucode_load_fw(cpt, "cpt8x-mc-se.out", false);
	अगर (ret) अणु
		dev_err(dev, "se:cpt_ucode_load failed with ret: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t cpt_mbx0_पूर्णांकr_handler(पूर्णांक irq, व्योम *cpt_irq)
अणु
	काष्ठा cpt_device *cpt = (काष्ठा cpt_device *)cpt_irq;

	cpt_mbox_पूर्णांकr_handler(cpt, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cpt_reset(काष्ठा cpt_device *cpt)
अणु
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_RESET(0), 1);
पूर्ण

अटल व्योम cpt_find_max_enabled_cores(काष्ठा cpt_device *cpt)
अणु
	जोड़ cptx_pf_स्थिरants pf_cnsts = अणु0पूर्ण;

	pf_cnsts.u = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_CONSTANTS(0));
	cpt->max_se_cores = pf_cnsts.s.se;
	cpt->max_ae_cores = pf_cnsts.s.ae;
पूर्ण

अटल u32 cpt_check_bist_status(काष्ठा cpt_device *cpt)
अणु
	जोड़ cptx_pf_bist_status bist_sts = अणु0पूर्ण;

	bist_sts.u = cpt_पढ़ो_csr64(cpt->reg_base,
				    CPTX_PF_BIST_STATUS(0));

	वापस bist_sts.u;
पूर्ण

अटल u64 cpt_check_exe_bist_status(काष्ठा cpt_device *cpt)
अणु
	जोड़ cptx_pf_exe_bist_status bist_sts = अणु0पूर्ण;

	bist_sts.u = cpt_पढ़ो_csr64(cpt->reg_base,
				    CPTX_PF_EXE_BIST_STATUS(0));

	वापस bist_sts.u;
पूर्ण

अटल व्योम cpt_disable_all_cores(काष्ठा cpt_device *cpt)
अणु
	u32 grp, समयout = 100;
	काष्ठा device *dev = &cpt->pdev->dev;

	/* Disengage the cores from groups */
	क्रम (grp = 0; grp < CPT_MAX_CORE_GROUPS; grp++) अणु
		cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_GX_EN(0, grp), 0);
		udelay(CSR_DELAY);
	पूर्ण

	grp = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_EXEC_BUSY(0));
	जबतक (grp) अणु
		dev_err(dev, "Cores still busy");
		grp = cpt_पढ़ो_csr64(cpt->reg_base,
				     CPTX_PF_EXEC_BUSY(0));
		अगर (समयout--)
			अवरोध;

		udelay(CSR_DELAY);
	पूर्ण
	/* Disable the cores */
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_EXE_CTL(0), 0);
पूर्ण

/**
 * Ensure all cores are disengaged from all groups by
 * calling cpt_disable_all_cores() beक्रमe calling this
 * function.
 */
अटल व्योम cpt_unload_microcode(काष्ठा cpt_device *cpt)
अणु
	u32 grp = 0, core;

	/* Free microcode bases and reset group masks */
	क्रम (grp = 0; grp < CPT_MAX_CORE_GROUPS; grp++) अणु
		काष्ठा microcode *mcode = &cpt->mcode[grp];

		अगर (cpt->mcode[grp].code)
			dma_मुक्त_coherent(&cpt->pdev->dev, mcode->code_size,
					  mcode->code, mcode->phys_base);
		mcode->code = शून्य;
	पूर्ण
	/* Clear UCODE_BASE रेजिस्टरs क्रम all engines */
	क्रम (core = 0; core < CPT_MAX_TOTAL_CORES; core++)
		cpt_ग_लिखो_csr64(cpt->reg_base,
				CPTX_PF_ENGX_UCODE_BASE(0, core), 0ull);
पूर्ण

अटल पूर्णांक cpt_device_init(काष्ठा cpt_device *cpt)
अणु
	u64 bist;
	काष्ठा device *dev = &cpt->pdev->dev;

	/* Reset the PF when probed first */
	cpt_reset(cpt);
	msleep(100);

	/*Check BIST status*/
	bist = (u64)cpt_check_bist_status(cpt);
	अगर (bist) अणु
		dev_err(dev, "RAM BIST failed with code 0x%llx", bist);
		वापस -ENODEV;
	पूर्ण

	bist = cpt_check_exe_bist_status(cpt);
	अगर (bist) अणु
		dev_err(dev, "Engine BIST failed with code 0x%llx", bist);
		वापस -ENODEV;
	पूर्ण

	/*Get CLK frequency*/
	/*Get max enabled cores */
	cpt_find_max_enabled_cores(cpt);
	/*Disable all cores*/
	cpt_disable_all_cores(cpt);
	/*Reset device parameters*/
	cpt->next_mc_idx   = 0;
	cpt->next_group = 0;
	/* PF is पढ़ोy */
	cpt->flags |= CPT_FLAG_DEVICE_READY;

	वापस 0;
पूर्ण

अटल पूर्णांक cpt_रेजिस्टर_पूर्णांकerrupts(काष्ठा cpt_device *cpt)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &cpt->pdev->dev;

	/* Enable MSI-X */
	ret = pci_alloc_irq_vectors(cpt->pdev, CPT_PF_MSIX_VECTORS,
			CPT_PF_MSIX_VECTORS, PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		dev_err(&cpt->pdev->dev, "Request for #%d msix vectors failed\n",
			CPT_PF_MSIX_VECTORS);
		वापस ret;
	पूर्ण

	/* Register mailbox पूर्णांकerrupt handlers */
	ret = request_irq(pci_irq_vector(cpt->pdev, CPT_PF_INT_VEC_E_MBOXX(0)),
			  cpt_mbx0_पूर्णांकr_handler, 0, "CPT Mbox0", cpt);
	अगर (ret)
		जाओ fail;

	/* Enable mailbox पूर्णांकerrupt */
	cpt_enable_mbox_पूर्णांकerrupts(cpt);
	वापस 0;

fail:
	dev_err(dev, "Request irq failed\n");
	pci_disable_msix(cpt->pdev);
	वापस ret;
पूर्ण

अटल व्योम cpt_unरेजिस्टर_पूर्णांकerrupts(काष्ठा cpt_device *cpt)
अणु
	मुक्त_irq(pci_irq_vector(cpt->pdev, CPT_PF_INT_VEC_E_MBOXX(0)), cpt);
	pci_disable_msix(cpt->pdev);
पूर्ण

अटल पूर्णांक cpt_sriov_init(काष्ठा cpt_device *cpt, पूर्णांक num_vfs)
अणु
	पूर्णांक pos = 0;
	पूर्णांक err;
	u16 total_vf_cnt;
	काष्ठा pci_dev *pdev = cpt->pdev;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_SRIOV);
	अगर (!pos) अणु
		dev_err(&pdev->dev, "SRIOV capability is not found in PCIe config space\n");
		वापस -ENODEV;
	पूर्ण

	cpt->num_vf_en = num_vfs; /* User requested VFs */
	pci_पढ़ो_config_word(pdev, (pos + PCI_SRIOV_TOTAL_VF), &total_vf_cnt);
	अगर (total_vf_cnt < cpt->num_vf_en)
		cpt->num_vf_en = total_vf_cnt;

	अगर (!total_vf_cnt)
		वापस 0;

	/*Enabled the available VFs */
	err = pci_enable_sriov(pdev, cpt->num_vf_en);
	अगर (err) अणु
		dev_err(&pdev->dev, "SRIOV enable failed, num VF is %d\n",
			cpt->num_vf_en);
		cpt->num_vf_en = 0;
		वापस err;
	पूर्ण

	/* TODO: Optionally enable अटल VQ priorities feature */

	dev_info(&pdev->dev, "SRIOV enabled, number of VF available %d\n",
		 cpt->num_vf_en);

	cpt->flags |= CPT_FLAG_SRIOV_ENABLED;

	वापस 0;
पूर्ण

अटल पूर्णांक cpt_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cpt_device *cpt;
	पूर्णांक err;

	अगर (num_vfs > 16 || num_vfs < 4) अणु
		dev_warn(dev, "Invalid vf count %d, Resetting it to 4(default)\n",
			 num_vfs);
		num_vfs = 4;
	पूर्ण

	cpt = devm_kzalloc(dev, माप(*cpt), GFP_KERNEL);
	अगर (!cpt)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, cpt);
	cpt->pdev = pdev;
	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		pci_set_drvdata(pdev, शून्य);
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		जाओ cpt_err_disable_device;
	पूर्ण

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "Unable to get usable 48-bit DMA configuration\n");
		जाओ cpt_err_release_regions;
	पूर्ण

	/* MAP PF's configuration रेजिस्टरs */
	cpt->reg_base = pcim_iomap(pdev, 0, 0);
	अगर (!cpt->reg_base) अणु
		dev_err(dev, "Cannot map config register space, aborting\n");
		err = -ENOMEM;
		जाओ cpt_err_release_regions;
	पूर्ण

	/* CPT device HW initialization */
	cpt_device_init(cpt);

	/* Register पूर्णांकerrupts */
	err = cpt_रेजिस्टर_पूर्णांकerrupts(cpt);
	अगर (err)
		जाओ cpt_err_release_regions;

	err = cpt_ucode_load(cpt);
	अगर (err)
		जाओ cpt_err_unरेजिस्टर_पूर्णांकerrupts;

	/* Configure SRIOV */
	err = cpt_sriov_init(cpt, num_vfs);
	अगर (err)
		जाओ cpt_err_unरेजिस्टर_पूर्णांकerrupts;

	वापस 0;

cpt_err_unरेजिस्टर_पूर्णांकerrupts:
	cpt_unरेजिस्टर_पूर्णांकerrupts(cpt);
cpt_err_release_regions:
	pci_release_regions(pdev);
cpt_err_disable_device:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम cpt_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cpt_device *cpt = pci_get_drvdata(pdev);

	/* Disengage SE and AE cores from all groups*/
	cpt_disable_all_cores(cpt);
	/* Unload microcodes */
	cpt_unload_microcode(cpt);
	cpt_unरेजिस्टर_पूर्णांकerrupts(cpt);
	pci_disable_sriov(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

अटल व्योम cpt_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cpt_device *cpt = pci_get_drvdata(pdev);

	अगर (!cpt)
		वापस;

	dev_info(&pdev->dev, "Shutdown device %x:%x.\n",
		 (u32)pdev->venकरोr, (u32)pdev->device);

	cpt_unरेजिस्टर_पूर्णांकerrupts(cpt);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id cpt_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, CPT_81XX_PCI_PF_DEVICE_ID) पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

अटल काष्ठा pci_driver cpt_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = cpt_id_table,
	.probe = cpt_probe,
	.हटाओ = cpt_हटाओ,
	.shutकरोwn = cpt_shutकरोwn,
पूर्ण;

module_pci_driver(cpt_pci_driver);

MODULE_AUTHOR("George Cherian <george.cherian@cavium.com>");
MODULE_DESCRIPTION("Cavium Thunder CPT Physical Function Driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, cpt_id_table);
