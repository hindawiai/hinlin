<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/mm.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>

#समावेश "csio_init.h"
#समावेश "csio_defs.h"

#घोषणा CSIO_MIN_MEMPOOL_SZ	64

अटल काष्ठा dentry *csio_debugfs_root;

अटल काष्ठा scsi_transport_ढाँचा *csio_fcoe_transport;
अटल काष्ठा scsi_transport_ढाँचा *csio_fcoe_transport_vport;

/*
 * debugfs support
 */
अटल sमाप_प्रकार
csio_mem_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	loff_t pos = *ppos;
	loff_t avail = file_inode(file)->i_size;
	अचिन्हित पूर्णांक mem = (uपूर्णांकptr_t)file->निजी_data & 3;
	काष्ठा csio_hw *hw = file->निजी_data - mem;

	अगर (pos < 0)
		वापस -EINVAL;
	अगर (pos >= avail)
		वापस 0;
	अगर (count > avail - pos)
		count = avail - pos;

	जबतक (count) अणु
		माप_प्रकार len;
		पूर्णांक ret, ofst;
		__be32 data[16];

		अगर (mem == MEM_MC)
			ret = hw->chip_ops->chip_mc_पढ़ो(hw, 0, pos,
							 data, शून्य);
		अन्यथा
			ret = hw->chip_ops->chip_edc_पढ़ो(hw, mem, pos,
							  data, शून्य);
		अगर (ret)
			वापस ret;

		ofst = pos % माप(data);
		len = min(count, माप(data) - ofst);
		अगर (copy_to_user(buf, (u8 *)data + ofst, len))
			वापस -EFAULT;

		buf += len;
		pos += len;
		count -= len;
	पूर्ण
	count = pos - *ppos;
	*ppos = pos;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations csio_mem_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = simple_खोलो,
	.पढ़ो    = csio_mem_पढ़ो,
	.llseek  = शेष_llseek,
पूर्ण;

व्योम csio_add_debugfs_mem(काष्ठा csio_hw *hw, स्थिर अक्षर *name,
				 अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक size_mb)
अणु
	debugfs_create_file_size(name, S_IRUSR, hw->debugfs_root,
				 (व्योम *)hw + idx, &csio_mem_debugfs_fops,
				 size_mb << 20);
पूर्ण

अटल पूर्णांक csio_setup_debugfs(काष्ठा csio_hw *hw)
अणु
	पूर्णांक i;

	अगर (IS_ERR_OR_शून्य(hw->debugfs_root))
		वापस -1;

	i = csio_rd_reg32(hw, MA_TARGET_MEM_ENABLE_A);
	अगर (i & EDRAM0_ENABLE_F)
		csio_add_debugfs_mem(hw, "edc0", MEM_EDC0, 5);
	अगर (i & EDRAM1_ENABLE_F)
		csio_add_debugfs_mem(hw, "edc1", MEM_EDC1, 5);

	hw->chip_ops->chip_dfs_create_ext_mem(hw);
	वापस 0;
पूर्ण

/*
 * csio_dfs_create - Creates and sets up per-hw debugfs.
 *
 */
अटल पूर्णांक
csio_dfs_create(काष्ठा csio_hw *hw)
अणु
	अगर (csio_debugfs_root) अणु
		hw->debugfs_root = debugfs_create_dir(pci_name(hw->pdev),
							csio_debugfs_root);
		csio_setup_debugfs(hw);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csio_dfs_destroy - Destroys per-hw debugfs.
 */
अटल व्योम
csio_dfs_destroy(काष्ठा csio_hw *hw)
अणु
	debugfs_हटाओ_recursive(hw->debugfs_root);
पूर्ण

/*
 * csio_dfs_init - Debug fileप्रणाली initialization क्रम the module.
 *
 */
अटल व्योम
csio_dfs_init(व्योम)
अणु
	csio_debugfs_root = debugfs_create_dir(KBUILD_MODNAME, शून्य);
पूर्ण

/*
 * csio_dfs_निकास - debugfs cleanup क्रम the module.
 */
अटल व्योम
csio_dfs_निकास(व्योम)
अणु
	debugfs_हटाओ(csio_debugfs_root);
पूर्ण

/*
 * csio_pci_init - PCI initialization.
 * @pdev: PCI device.
 * @bars: Biपंचांगask of bars to be requested.
 *
 * Initializes the PCI function by enabling MMIO, setting bus
 * mastership and setting DMA mask.
 */
अटल पूर्णांक
csio_pci_init(काष्ठा pci_dev *pdev, पूर्णांक *bars)
अणु
	पूर्णांक rv = -ENODEV;

	*bars = pci_select_bars(pdev, IORESOURCE_MEM);

	अगर (pci_enable_device_mem(pdev))
		जाओ err;

	अगर (pci_request_selected_regions(pdev, *bars, KBUILD_MODNAME))
		जाओ err_disable_device;

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	rv = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rv)
		rv = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (rv) अणु
		rv = -ENODEV;
		dev_err(&pdev->dev, "No suitable DMA available.\n");
		जाओ err_release_regions;
	पूर्ण

	वापस 0;

err_release_regions:
	pci_release_selected_regions(pdev, *bars);
err_disable_device:
	pci_disable_device(pdev);
err:
	वापस rv;

पूर्ण

/*
 * csio_pci_निकास - PCI unitialization.
 * @pdev: PCI device.
 * @bars: Bars to be released.
 *
 */
अटल व्योम
csio_pci_निकास(काष्ठा pci_dev *pdev, पूर्णांक *bars)
अणु
	pci_release_selected_regions(pdev, *bars);
	pci_disable_device(pdev);
पूर्ण

/*
 * csio_hw_init_workers - Initialize the HW module's worker thपढ़ोs.
 * @hw: HW module.
 *
 */
अटल व्योम
csio_hw_init_workers(काष्ठा csio_hw *hw)
अणु
	INIT_WORK(&hw->evtq_work, csio_evtq_worker);
पूर्ण

अटल व्योम
csio_hw_निकास_workers(काष्ठा csio_hw *hw)
अणु
	cancel_work_sync(&hw->evtq_work);
पूर्ण

अटल पूर्णांक
csio_create_queues(काष्ठा csio_hw *hw)
अणु
	पूर्णांक i, j;
	काष्ठा csio_mgmपंचांग *mgmपंचांग = csio_hw_to_mgmपंचांग(hw);
	पूर्णांक rv;
	काष्ठा csio_scsi_cpu_info *info;

	अगर (hw->flags & CSIO_HWF_Q_FW_ALLOCED)
		वापस 0;

	अगर (hw->पूर्णांकr_mode != CSIO_IM_MSIX) अणु
		rv = csio_wr_iq_create(hw, शून्य, hw->पूर्णांकr_iq_idx,
					0, hw->pport[0].portid, false, शून्य);
		अगर (rv != 0) अणु
			csio_err(hw, " Forward Interrupt IQ failed!: %d\n", rv);
			वापस rv;
		पूर्ण
	पूर्ण

	/* FW event queue */
	rv = csio_wr_iq_create(hw, शून्य, hw->fwevt_iq_idx,
			       csio_get_fwevt_पूर्णांकr_idx(hw),
			       hw->pport[0].portid, true, शून्य);
	अगर (rv != 0) अणु
		csio_err(hw, "FW event IQ config failed!: %d\n", rv);
		वापस rv;
	पूर्ण

	/* Create mgmt queue */
	rv = csio_wr_eq_create(hw, शून्य, mgmपंचांग->eq_idx,
			mgmपंचांग->iq_idx, hw->pport[0].portid, शून्य);

	अगर (rv != 0) अणु
		csio_err(hw, "Mgmt EQ create failed!: %d\n", rv);
		जाओ err;
	पूर्ण

	/* Create SCSI queues */
	क्रम (i = 0; i < hw->num_pports; i++) अणु
		info = &hw->scsi_cpu_info[i];

		क्रम (j = 0; j < info->max_cpus; j++) अणु
			काष्ठा csio_scsi_qset *sqset = &hw->sqset[i][j];

			rv = csio_wr_iq_create(hw, शून्य, sqset->iq_idx,
					       sqset->पूर्णांकr_idx, i, false, शून्य);
			अगर (rv != 0) अणु
				csio_err(hw,
				   "SCSI module IQ config failed [%d][%d]:%d\n",
				   i, j, rv);
				जाओ err;
			पूर्ण
			rv = csio_wr_eq_create(hw, शून्य, sqset->eq_idx,
					       sqset->iq_idx, i, शून्य);
			अगर (rv != 0) अणु
				csio_err(hw,
				   "SCSI module EQ config failed [%d][%d]:%d\n",
				   i, j, rv);
				जाओ err;
			पूर्ण
		पूर्ण /* क्रम all CPUs */
	पूर्ण /* For all ports */

	hw->flags |= CSIO_HWF_Q_FW_ALLOCED;
	वापस 0;
err:
	csio_wr_destroy_queues(hw, true);
	वापस -EINVAL;
पूर्ण

/*
 * csio_config_queues - Configure the DMA queues.
 * @hw: HW module.
 *
 * Allocates memory क्रम queues are रेजिस्टरs them with FW.
 */
पूर्णांक
csio_config_queues(काष्ठा csio_hw *hw)
अणु
	पूर्णांक i, j, idx, k = 0;
	पूर्णांक rv;
	काष्ठा csio_scsi_qset *sqset;
	काष्ठा csio_mgmपंचांग *mgmपंचांग = csio_hw_to_mgmपंचांग(hw);
	काष्ठा csio_scsi_qset *orig;
	काष्ठा csio_scsi_cpu_info *info;

	अगर (hw->flags & CSIO_HWF_Q_MEM_ALLOCED)
		वापस csio_create_queues(hw);

	/* Calculate number of SCSI queues क्रम MSIX we would like */
	hw->num_scsi_msix_cpus = num_online_cpus();
	hw->num_sqsets = num_online_cpus() * hw->num_pports;

	अगर (hw->num_sqsets > CSIO_MAX_SCSI_QSETS) अणु
		hw->num_sqsets = CSIO_MAX_SCSI_QSETS;
		hw->num_scsi_msix_cpus = CSIO_MAX_SCSI_CPU;
	पूर्ण

	/* Initialize max_cpus, may get reduced during msix allocations */
	क्रम (i = 0; i < hw->num_pports; i++)
		hw->scsi_cpu_info[i].max_cpus = hw->num_scsi_msix_cpus;

	csio_dbg(hw, "nsqsets:%d scpus:%d\n",
		    hw->num_sqsets, hw->num_scsi_msix_cpus);

	csio_पूर्णांकr_enable(hw);

	अगर (hw->पूर्णांकr_mode != CSIO_IM_MSIX) अणु

		/* Allocate Forward पूर्णांकerrupt iq. */
		hw->पूर्णांकr_iq_idx = csio_wr_alloc_q(hw, CSIO_INTR_IQSIZE,
						CSIO_INTR_WRSIZE, CSIO_INGRESS,
						(व्योम *)hw, 0, 0, शून्य);
		अगर (hw->पूर्णांकr_iq_idx == -1) अणु
			csio_err(hw,
				 "Forward interrupt queue creation failed\n");
			जाओ पूर्णांकr_disable;
		पूर्ण
	पूर्ण

	/* Allocate the FW evt queue */
	hw->fwevt_iq_idx = csio_wr_alloc_q(hw, CSIO_FWEVT_IQSIZE,
					   CSIO_FWEVT_WRSIZE,
					   CSIO_INGRESS, (व्योम *)hw,
					   CSIO_FWEVT_FLBUFS, 0,
					   csio_fwevt_पूर्णांकx_handler);
	अगर (hw->fwevt_iq_idx == -1) अणु
		csio_err(hw, "FW evt queue creation failed\n");
		जाओ पूर्णांकr_disable;
	पूर्ण

	/* Allocate the mgmt queue */
	mgmपंचांग->eq_idx = csio_wr_alloc_q(hw, CSIO_MGMT_EQSIZE,
				      CSIO_MGMT_EQ_WRSIZE,
				      CSIO_EGRESS, (व्योम *)hw, 0, 0, शून्य);
	अगर (mgmपंचांग->eq_idx == -1) अणु
		csio_err(hw, "Failed to alloc egress queue for mgmt module\n");
		जाओ पूर्णांकr_disable;
	पूर्ण

	/* Use FW IQ क्रम MGMT req completion */
	mgmपंचांग->iq_idx = hw->fwevt_iq_idx;

	/* Allocate SCSI queues */
	क्रम (i = 0; i < hw->num_pports; i++) अणु
		info = &hw->scsi_cpu_info[i];

		क्रम (j = 0; j < hw->num_scsi_msix_cpus; j++) अणु
			sqset = &hw->sqset[i][j];

			अगर (j >= info->max_cpus) अणु
				k = j % info->max_cpus;
				orig = &hw->sqset[i][k];
				sqset->eq_idx = orig->eq_idx;
				sqset->iq_idx = orig->iq_idx;
				जारी;
			पूर्ण

			idx = csio_wr_alloc_q(hw, csio_scsi_eqsize, 0,
					      CSIO_EGRESS, (व्योम *)hw, 0, 0,
					      शून्य);
			अगर (idx == -1) अणु
				csio_err(hw, "EQ creation failed for idx:%d\n",
					    idx);
				जाओ पूर्णांकr_disable;
			पूर्ण

			sqset->eq_idx = idx;

			idx = csio_wr_alloc_q(hw, CSIO_SCSI_IQSIZE,
					     CSIO_SCSI_IQ_WRSZ, CSIO_INGRESS,
					     (व्योम *)hw, 0, 0,
					     csio_scsi_पूर्णांकx_handler);
			अगर (idx == -1) अणु
				csio_err(hw, "IQ creation failed for idx:%d\n",
					    idx);
				जाओ पूर्णांकr_disable;
			पूर्ण
			sqset->iq_idx = idx;
		पूर्ण /* क्रम all CPUs */
	पूर्ण /* For all ports */

	hw->flags |= CSIO_HWF_Q_MEM_ALLOCED;

	rv = csio_create_queues(hw);
	अगर (rv != 0)
		जाओ पूर्णांकr_disable;

	/*
	 * Now request IRQs क्रम the vectors. In the event of a failure,
	 * cleanup is handled पूर्णांकernally by this function.
	 */
	rv = csio_request_irqs(hw);
	अगर (rv != 0)
		वापस -EINVAL;

	वापस 0;

पूर्णांकr_disable:
	csio_पूर्णांकr_disable(hw, false);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
csio_resource_alloc(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	पूर्णांक rv = -ENOMEM;

	wrm->num_q = ((CSIO_MAX_SCSI_QSETS * 2) + CSIO_HW_NIQ +
		       CSIO_HW_NEQ + CSIO_HW_NFLQ + CSIO_HW_NINTXQ);

	hw->mb_mempool = mempool_create_kदो_स्मृति_pool(CSIO_MIN_MEMPOOL_SZ,
						  माप(काष्ठा csio_mb));
	अगर (!hw->mb_mempool)
		जाओ err;

	hw->rnode_mempool = mempool_create_kदो_स्मृति_pool(CSIO_MIN_MEMPOOL_SZ,
						     माप(काष्ठा csio_rnode));
	अगर (!hw->rnode_mempool)
		जाओ err_मुक्त_mb_mempool;

	hw->scsi_dma_pool = dma_pool_create("csio_scsi_dma_pool",
					    &hw->pdev->dev, CSIO_SCSI_RSP_LEN,
					    8, 0);
	अगर (!hw->scsi_dma_pool)
		जाओ err_मुक्त_rn_pool;

	वापस 0;

err_मुक्त_rn_pool:
	mempool_destroy(hw->rnode_mempool);
	hw->rnode_mempool = शून्य;
err_मुक्त_mb_mempool:
	mempool_destroy(hw->mb_mempool);
	hw->mb_mempool = शून्य;
err:
	वापस rv;
पूर्ण

अटल व्योम
csio_resource_मुक्त(काष्ठा csio_hw *hw)
अणु
	dma_pool_destroy(hw->scsi_dma_pool);
	hw->scsi_dma_pool = शून्य;
	mempool_destroy(hw->rnode_mempool);
	hw->rnode_mempool = शून्य;
	mempool_destroy(hw->mb_mempool);
	hw->mb_mempool = शून्य;
पूर्ण

/*
 * csio_hw_alloc - Allocate and initialize the HW module.
 * @pdev: PCI device.
 *
 * Allocates HW काष्ठाure, DMA, memory resources, maps BARS to
 * host memory and initializes HW module.
 */
अटल काष्ठा csio_hw *csio_hw_alloc(काष्ठा pci_dev *pdev)
अणु
	काष्ठा csio_hw *hw;

	hw = kzalloc(माप(काष्ठा csio_hw), GFP_KERNEL);
	अगर (!hw)
		जाओ err;

	hw->pdev = pdev;
	म_नकलन(hw->drv_version, CSIO_DRV_VERSION, 32);

	/* memory pool/DMA pool allocation */
	अगर (csio_resource_alloc(hw))
		जाओ err_मुक्त_hw;

	/* Get the start address of रेजिस्टरs from BAR 0 */
	hw->regstart = ioremap(pci_resource_start(pdev, 0),
				       pci_resource_len(pdev, 0));
	अगर (!hw->regstart) अणु
		csio_err(hw, "Could not map BAR 0, regstart = %p\n",
			 hw->regstart);
		जाओ err_resource_मुक्त;
	पूर्ण

	csio_hw_init_workers(hw);

	अगर (csio_hw_init(hw))
		जाओ err_unmap_bar;

	csio_dfs_create(hw);

	csio_dbg(hw, "hw:%p\n", hw);

	वापस hw;

err_unmap_bar:
	csio_hw_निकास_workers(hw);
	iounmap(hw->regstart);
err_resource_मुक्त:
	csio_resource_मुक्त(hw);
err_मुक्त_hw:
	kमुक्त(hw);
err:
	वापस शून्य;
पूर्ण

/*
 * csio_hw_मुक्त - Uninitialize and मुक्त the HW module.
 * @hw: The HW module
 *
 * Disable पूर्णांकerrupts, uninit the HW module, मुक्त resources, मुक्त hw.
 */
अटल व्योम
csio_hw_मुक्त(काष्ठा csio_hw *hw)
अणु
	csio_पूर्णांकr_disable(hw, true);
	csio_hw_निकास_workers(hw);
	csio_hw_निकास(hw);
	iounmap(hw->regstart);
	csio_dfs_destroy(hw);
	csio_resource_मुक्त(hw);
	kमुक्त(hw);
पूर्ण

/**
 * csio_shost_init - Create and initialize the lnode module.
 * @hw:		The HW module.
 * @dev:	The device associated with this invocation.
 * @probe:	Called from probe context or not?
 * @pln:	Parent lnode अगर any.
 *
 * Allocates lnode काष्ठाure via scsi_host_alloc, initializes
 * shost, initializes lnode module and रेजिस्टरs with SCSI ML
 * via scsi_host_add. This function is shared between physical and
 * भव node ports.
 */
काष्ठा csio_lnode *
csio_shost_init(काष्ठा csio_hw *hw, काष्ठा device *dev,
		  bool probe, काष्ठा csio_lnode *pln)
अणु
	काष्ठा Scsi_Host  *shost = शून्य;
	काष्ठा csio_lnode *ln;

	csio_fcoe_shost_ढाँचा.cmd_per_lun = csio_lun_qdepth;
	csio_fcoe_shost_vport_ढाँचा.cmd_per_lun = csio_lun_qdepth;

	/*
	 * hw->pdev is the physical port's PCI dev काष्ठाure,
	 * which will be dअगरferent from the NPIV dev काष्ठाure.
	 */
	अगर (dev == &hw->pdev->dev)
		shost = scsi_host_alloc(
				&csio_fcoe_shost_ढाँचा,
				माप(काष्ठा csio_lnode));
	अन्यथा
		shost = scsi_host_alloc(
				&csio_fcoe_shost_vport_ढाँचा,
				माप(काष्ठा csio_lnode));

	अगर (!shost)
		जाओ err;

	ln = shost_priv(shost);
	स_रखो(ln, 0, माप(काष्ठा csio_lnode));

	/* Link common lnode to this lnode */
	ln->dev_num = (shost->host_no << 16);

	shost->can_queue = CSIO_MAX_QUEUE;
	shost->this_id = -1;
	shost->unique_id = shost->host_no;
	shost->max_cmd_len = 16; /* Max CDB length supported */
	shost->max_id = min_t(uपूर्णांक32_t, csio_fcoe_rnodes,
			      hw->fres_info.max_ssns);
	shost->max_lun = CSIO_MAX_LUN;
	अगर (dev == &hw->pdev->dev)
		shost->transportt = csio_fcoe_transport;
	अन्यथा
		shost->transportt = csio_fcoe_transport_vport;

	/* root lnode */
	अगर (!hw->rln)
		hw->rln = ln;

	/* Other initialization here: Common, Transport specअगरic */
	अगर (csio_lnode_init(ln, hw, pln))
		जाओ err_shost_put;

	अगर (scsi_add_host_with_dma(shost, dev, &hw->pdev->dev))
		जाओ err_lnode_निकास;

	वापस ln;

err_lnode_निकास:
	csio_lnode_निकास(ln);
err_shost_put:
	scsi_host_put(shost);
err:
	वापस शून्य;
पूर्ण

/**
 * csio_shost_निकास - De-instantiate the shost.
 * @ln:		The lnode module corresponding to the shost.
 *
 */
व्योम
csio_shost_निकास(काष्ठा csio_lnode *ln)
अणु
	काष्ठा Scsi_Host *shost = csio_ln_to_shost(ln);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	/* Inक्रमm transport */
	fc_हटाओ_host(shost);

	/* Inक्रमm SCSI ML */
	scsi_हटाओ_host(shost);

	/* Flush all the events, so that any rnode removal events
	 * alपढ़ोy queued are all handled, beक्रमe we हटाओ the lnode.
	 */
	spin_lock_irq(&hw->lock);
	csio_evtq_flush(hw);
	spin_unlock_irq(&hw->lock);

	csio_lnode_निकास(ln);
	scsi_host_put(shost);
पूर्ण

काष्ठा csio_lnode *
csio_lnode_alloc(काष्ठा csio_hw *hw)
अणु
	वापस csio_shost_init(hw, &hw->pdev->dev, false, शून्य);
पूर्ण

व्योम
csio_lnodes_block_request(काष्ठा csio_hw *hw)
अणु
	काष्ठा Scsi_Host  *shost;
	काष्ठा csio_lnode *sln;
	काष्ठा csio_lnode *ln;
	काष्ठा list_head *cur_ln, *cur_cln;
	काष्ठा csio_lnode **lnode_list;
	पूर्णांक cur_cnt = 0, ii;

	lnode_list = kzalloc((माप(काष्ठा csio_lnode *) * hw->num_lns),
			GFP_KERNEL);
	अगर (!lnode_list) अणु
		csio_err(hw, "Failed to allocate lnodes_list");
		वापस;
	पूर्ण

	spin_lock_irq(&hw->lock);
	/* Traverse sibling lnodes */
	list_क्रम_each(cur_ln, &hw->sln_head) अणु
		sln = (काष्ठा csio_lnode *) cur_ln;
		lnode_list[cur_cnt++] = sln;

		/* Traverse children lnodes */
		list_क्रम_each(cur_cln, &sln->cln_head)
			lnode_list[cur_cnt++] = (काष्ठा csio_lnode *) cur_cln;
	पूर्ण
	spin_unlock_irq(&hw->lock);

	क्रम (ii = 0; ii < cur_cnt; ii++) अणु
		csio_dbg(hw, "Blocking IOs on lnode: %p\n", lnode_list[ii]);
		ln = lnode_list[ii];
		shost = csio_ln_to_shost(ln);
		scsi_block_requests(shost);

	पूर्ण
	kमुक्त(lnode_list);
पूर्ण

व्योम
csio_lnodes_unblock_request(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_lnode *ln;
	काष्ठा Scsi_Host  *shost;
	काष्ठा csio_lnode *sln;
	काष्ठा list_head *cur_ln, *cur_cln;
	काष्ठा csio_lnode **lnode_list;
	पूर्णांक cur_cnt = 0, ii;

	lnode_list = kzalloc((माप(काष्ठा csio_lnode *) * hw->num_lns),
			GFP_KERNEL);
	अगर (!lnode_list) अणु
		csio_err(hw, "Failed to allocate lnodes_list");
		वापस;
	पूर्ण

	spin_lock_irq(&hw->lock);
	/* Traverse sibling lnodes */
	list_क्रम_each(cur_ln, &hw->sln_head) अणु
		sln = (काष्ठा csio_lnode *) cur_ln;
		lnode_list[cur_cnt++] = sln;

		/* Traverse children lnodes */
		list_क्रम_each(cur_cln, &sln->cln_head)
			lnode_list[cur_cnt++] = (काष्ठा csio_lnode *) cur_cln;
	पूर्ण
	spin_unlock_irq(&hw->lock);

	क्रम (ii = 0; ii < cur_cnt; ii++) अणु
		csio_dbg(hw, "unblocking IOs on lnode: %p\n", lnode_list[ii]);
		ln = lnode_list[ii];
		shost = csio_ln_to_shost(ln);
		scsi_unblock_requests(shost);
	पूर्ण
	kमुक्त(lnode_list);
पूर्ण

व्योम
csio_lnodes_block_by_port(काष्ठा csio_hw *hw, uपूर्णांक8_t portid)
अणु
	काष्ठा csio_lnode *ln;
	काष्ठा Scsi_Host  *shost;
	काष्ठा csio_lnode *sln;
	काष्ठा list_head *cur_ln, *cur_cln;
	काष्ठा csio_lnode **lnode_list;
	पूर्णांक cur_cnt = 0, ii;

	lnode_list = kzalloc((माप(काष्ठा csio_lnode *) * hw->num_lns),
			GFP_KERNEL);
	अगर (!lnode_list) अणु
		csio_err(hw, "Failed to allocate lnodes_list");
		वापस;
	पूर्ण

	spin_lock_irq(&hw->lock);
	/* Traverse sibling lnodes */
	list_क्रम_each(cur_ln, &hw->sln_head) अणु
		sln = (काष्ठा csio_lnode *) cur_ln;
		अगर (sln->portid != portid)
			जारी;

		lnode_list[cur_cnt++] = sln;

		/* Traverse children lnodes */
		list_क्रम_each(cur_cln, &sln->cln_head)
			lnode_list[cur_cnt++] = (काष्ठा csio_lnode *) cur_cln;
	पूर्ण
	spin_unlock_irq(&hw->lock);

	क्रम (ii = 0; ii < cur_cnt; ii++) अणु
		csio_dbg(hw, "Blocking IOs on lnode: %p\n", lnode_list[ii]);
		ln = lnode_list[ii];
		shost = csio_ln_to_shost(ln);
		scsi_block_requests(shost);
	पूर्ण
	kमुक्त(lnode_list);
पूर्ण

व्योम
csio_lnodes_unblock_by_port(काष्ठा csio_hw *hw, uपूर्णांक8_t portid)
अणु
	काष्ठा csio_lnode *ln;
	काष्ठा Scsi_Host  *shost;
	काष्ठा csio_lnode *sln;
	काष्ठा list_head *cur_ln, *cur_cln;
	काष्ठा csio_lnode **lnode_list;
	पूर्णांक cur_cnt = 0, ii;

	lnode_list = kzalloc((माप(काष्ठा csio_lnode *) * hw->num_lns),
			GFP_KERNEL);
	अगर (!lnode_list) अणु
		csio_err(hw, "Failed to allocate lnodes_list");
		वापस;
	पूर्ण

	spin_lock_irq(&hw->lock);
	/* Traverse sibling lnodes */
	list_क्रम_each(cur_ln, &hw->sln_head) अणु
		sln = (काष्ठा csio_lnode *) cur_ln;
		अगर (sln->portid != portid)
			जारी;
		lnode_list[cur_cnt++] = sln;

		/* Traverse children lnodes */
		list_क्रम_each(cur_cln, &sln->cln_head)
			lnode_list[cur_cnt++] = (काष्ठा csio_lnode *) cur_cln;
	पूर्ण
	spin_unlock_irq(&hw->lock);

	क्रम (ii = 0; ii < cur_cnt; ii++) अणु
		csio_dbg(hw, "unblocking IOs on lnode: %p\n", lnode_list[ii]);
		ln = lnode_list[ii];
		shost = csio_ln_to_shost(ln);
		scsi_unblock_requests(shost);
	पूर्ण
	kमुक्त(lnode_list);
पूर्ण

व्योम
csio_lnodes_निकास(काष्ठा csio_hw *hw, bool npiv)
अणु
	काष्ठा csio_lnode *sln;
	काष्ठा csio_lnode *ln;
	काष्ठा list_head *cur_ln, *cur_cln;
	काष्ठा csio_lnode **lnode_list;
	पूर्णांक cur_cnt = 0, ii;

	lnode_list = kzalloc((माप(काष्ठा csio_lnode *) * hw->num_lns),
			GFP_KERNEL);
	अगर (!lnode_list) अणु
		csio_err(hw, "lnodes_exit: Failed to allocate lnodes_list.\n");
		वापस;
	पूर्ण

	/* Get all child lnodes(NPIV ports) */
	spin_lock_irq(&hw->lock);
	list_क्रम_each(cur_ln, &hw->sln_head) अणु
		sln = (काष्ठा csio_lnode *) cur_ln;

		/* Traverse children lnodes */
		list_क्रम_each(cur_cln, &sln->cln_head)
			lnode_list[cur_cnt++] = (काष्ठा csio_lnode *) cur_cln;
	पूर्ण
	spin_unlock_irq(&hw->lock);

	/* Delete NPIV lnodes */
	क्रम (ii = 0; ii < cur_cnt; ii++) अणु
		csio_dbg(hw, "Deleting child lnode: %p\n", lnode_list[ii]);
		ln = lnode_list[ii];
		fc_vport_terminate(ln->fc_vport);
	पूर्ण

	/* Delete only npiv lnodes */
	अगर (npiv)
		जाओ मुक्त_lnodes;

	cur_cnt = 0;
	/* Get all physical lnodes */
	spin_lock_irq(&hw->lock);
	/* Traverse sibling lnodes */
	list_क्रम_each(cur_ln, &hw->sln_head) अणु
		sln = (काष्ठा csio_lnode *) cur_ln;
		lnode_list[cur_cnt++] = sln;
	पूर्ण
	spin_unlock_irq(&hw->lock);

	/* Delete physical lnodes */
	क्रम (ii = 0; ii < cur_cnt; ii++) अणु
		csio_dbg(hw, "Deleting parent lnode: %p\n", lnode_list[ii]);
		csio_shost_निकास(lnode_list[ii]);
	पूर्ण

मुक्त_lnodes:
	kमुक्त(lnode_list);
पूर्ण

/*
 * csio_lnode_init_post: Set lnode attributes after starting HW.
 * @ln: lnode.
 *
 */
अटल व्योम
csio_lnode_init_post(काष्ठा csio_lnode *ln)
अणु
	काष्ठा Scsi_Host  *shost = csio_ln_to_shost(ln);

	csio_fchost_attr_init(ln);

	scsi_scan_host(shost);
पूर्ण

/*
 * csio_probe_one - Instantiate this function.
 * @pdev: PCI device
 * @id: Device ID
 *
 * This is the .probe() callback of the driver. This function:
 * - Initializes the PCI function by enabling MMIO, setting bus
 *   mastership and setting DMA mask.
 * - Allocates HW काष्ठाure, DMA, memory resources, maps BARS to
 *   host memory and initializes HW module.
 * - Allocates lnode काष्ठाure via scsi_host_alloc, initializes
 *   shost, initialized lnode module and रेजिस्टरs with SCSI ML
 *   via scsi_host_add.
 * - Enables पूर्णांकerrupts, and starts the chip by kicking off the
 *   HW state machine.
 * - Once hardware is पढ़ोy, initiated scan of the host via
 *   scsi_scan_host.
 */
अटल पूर्णांक csio_probe_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक rv;
	पूर्णांक bars;
	पूर्णांक i;
	काष्ठा csio_hw *hw;
	काष्ठा csio_lnode *ln;

	/* probe only T5 and T6 cards */
	अगर (!csio_is_t5((pdev->device & CSIO_HW_CHIP_MASK)) &&
	    !csio_is_t6((pdev->device & CSIO_HW_CHIP_MASK)))
		वापस -ENODEV;

	rv = csio_pci_init(pdev, &bars);
	अगर (rv)
		जाओ err;

	hw = csio_hw_alloc(pdev);
	अगर (!hw) अणु
		rv = -ENODEV;
		जाओ err_pci_निकास;
	पूर्ण

	अगर (!pcie_relaxed_ordering_enabled(pdev))
		hw->flags |= CSIO_HWF_ROOT_NO_RELAXED_ORDERING;

	pci_set_drvdata(pdev, hw);

	rv = csio_hw_start(hw);
	अगर (rv) अणु
		अगर (rv == -EINVAL) अणु
			dev_err(&pdev->dev,
				"Failed to start FW, continuing in debug mode.\n");
			वापस 0;
		पूर्ण
		जाओ err_lnode_निकास;
	पूर्ण

	प्र_लिखो(hw->fwrev_str, "%u.%u.%u.%u\n",
		    FW_HDR_FW_VER_MAJOR_G(hw->fwrev),
		    FW_HDR_FW_VER_MINOR_G(hw->fwrev),
		    FW_HDR_FW_VER_MICRO_G(hw->fwrev),
		    FW_HDR_FW_VER_BUILD_G(hw->fwrev));

	क्रम (i = 0; i < hw->num_pports; i++) अणु
		ln = csio_shost_init(hw, &pdev->dev, true, शून्य);
		अगर (!ln) अणु
			rv = -ENODEV;
			अवरोध;
		पूर्ण
		/* Initialize portid */
		ln->portid = hw->pport[i].portid;

		spin_lock_irq(&hw->lock);
		अगर (csio_lnode_start(ln) != 0)
			rv = -ENODEV;
		spin_unlock_irq(&hw->lock);

		अगर (rv)
			अवरोध;

		csio_lnode_init_post(ln);
	पूर्ण

	अगर (rv)
		जाओ err_lnode_निकास;

	वापस 0;

err_lnode_निकास:
	csio_lnodes_block_request(hw);
	spin_lock_irq(&hw->lock);
	csio_hw_stop(hw);
	spin_unlock_irq(&hw->lock);
	csio_lnodes_unblock_request(hw);
	csio_lnodes_निकास(hw, 0);
	csio_hw_मुक्त(hw);
err_pci_निकास:
	csio_pci_निकास(pdev, &bars);
err:
	dev_err(&pdev->dev, "probe of device failed: %d\n", rv);
	वापस rv;
पूर्ण

/*
 * csio_हटाओ_one - Remove one instance of the driver at this PCI function.
 * @pdev: PCI device
 *
 * Used during hotplug operation.
 */
अटल व्योम csio_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा csio_hw *hw = pci_get_drvdata(pdev);
	पूर्णांक bars = pci_select_bars(pdev, IORESOURCE_MEM);

	csio_lnodes_block_request(hw);
	spin_lock_irq(&hw->lock);

	/* Stops lnode, Rnode s/m
	 * Quiesce IOs.
	 * All sessions with remote ports are unरेजिस्टरed.
	 */
	csio_hw_stop(hw);
	spin_unlock_irq(&hw->lock);
	csio_lnodes_unblock_request(hw);

	csio_lnodes_निकास(hw, 0);
	csio_hw_मुक्त(hw);
	csio_pci_निकास(pdev, &bars);
पूर्ण

/*
 * csio_pci_error_detected - PCI error was detected
 * @pdev: PCI device
 *
 */
अटल pci_ers_result_t
csio_pci_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	काष्ठा csio_hw *hw = pci_get_drvdata(pdev);

	csio_lnodes_block_request(hw);
	spin_lock_irq(&hw->lock);

	/* Post PCI error detected evt to HW s/m
	 * HW s/m handles this evt by quiescing IOs, unरेजिस्टरs rports
	 * and finally takes the device to offline.
	 */
	csio_post_event(&hw->sm, CSIO_HWE_PCIERR_DETECTED);
	spin_unlock_irq(&hw->lock);
	csio_lnodes_unblock_request(hw);
	csio_lnodes_निकास(hw, 0);
	csio_पूर्णांकr_disable(hw, true);
	pci_disable_device(pdev);
	वापस state == pci_channel_io_perm_failure ?
		PCI_ERS_RESULT_DISCONNECT : PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/*
 * csio_pci_slot_reset - PCI slot has been reset.
 * @pdev: PCI device
 *
 */
अटल pci_ers_result_t
csio_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा csio_hw *hw = pci_get_drvdata(pdev);
	पूर्णांक पढ़ोy;

	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev, "cannot re-enable device in slot reset\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	pci_set_master(pdev);
	pci_restore_state(pdev);
	pci_save_state(pdev);

	/* Bring HW s/m to पढ़ोy state.
	 * but करोn't resume IOs.
	 */
	spin_lock_irq(&hw->lock);
	csio_post_event(&hw->sm, CSIO_HWE_PCIERR_SLOT_RESET);
	पढ़ोy = csio_is_hw_पढ़ोy(hw);
	spin_unlock_irq(&hw->lock);

	अगर (पढ़ोy) अणु
		वापस PCI_ERS_RESULT_RECOVERED;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Can't initialize HW when in slot reset\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
पूर्ण

/*
 * csio_pci_resume - Resume normal operations
 * @pdev: PCI device
 *
 */
अटल व्योम
csio_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा csio_hw *hw = pci_get_drvdata(pdev);
	काष्ठा csio_lnode *ln;
	पूर्णांक rv = 0;
	पूर्णांक i;

	/* Bring the LINK UP and Resume IO */

	क्रम (i = 0; i < hw->num_pports; i++) अणु
		ln = csio_shost_init(hw, &pdev->dev, true, शून्य);
		अगर (!ln) अणु
			rv = -ENODEV;
			अवरोध;
		पूर्ण
		/* Initialize portid */
		ln->portid = hw->pport[i].portid;

		spin_lock_irq(&hw->lock);
		अगर (csio_lnode_start(ln) != 0)
			rv = -ENODEV;
		spin_unlock_irq(&hw->lock);

		अगर (rv)
			अवरोध;

		csio_lnode_init_post(ln);
	पूर्ण

	अगर (rv)
		जाओ err_resume_निकास;

	वापस;

err_resume_निकास:
	csio_lnodes_block_request(hw);
	spin_lock_irq(&hw->lock);
	csio_hw_stop(hw);
	spin_unlock_irq(&hw->lock);
	csio_lnodes_unblock_request(hw);
	csio_lnodes_निकास(hw, 0);
	csio_hw_मुक्त(hw);
	dev_err(&pdev->dev, "resume of device failed: %d\n", rv);
पूर्ण

अटल काष्ठा pci_error_handlers csio_err_handler = अणु
	.error_detected = csio_pci_error_detected,
	.slot_reset	= csio_pci_slot_reset,
	.resume		= csio_pci_resume,
पूर्ण;

/*
 *  Macros needed to support the PCI Device ID Table ...
 */
#घोषणा CH_PCI_DEVICE_ID_TABLE_DEFINE_BEGIN \
	अटल स्थिर काष्ठा pci_device_id csio_pci_tbl[] = अणु
/* Define क्रम FCoE uses PF6 */
#घोषणा CH_PCI_DEVICE_ID_FUNCTION	0x6

#घोषणा CH_PCI_ID_TABLE_ENTRY(devid) \
		अणु PCI_VDEVICE(CHELSIO, (devid)), 0 पूर्ण

#घोषणा CH_PCI_DEVICE_ID_TABLE_DEFINE_END अणु 0, पूर्ण पूर्ण

#समावेश "t4_pci_id_tbl.h"

अटल काष्ठा pci_driver csio_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.driver		= अणु
		.owner	= THIS_MODULE,
	पूर्ण,
	.id_table	= csio_pci_tbl,
	.probe		= csio_probe_one,
	.हटाओ		= csio_हटाओ_one,
	.err_handler	= &csio_err_handler,
पूर्ण;

/*
 * csio_init - Chelsio storage driver initialization function.
 *
 */
अटल पूर्णांक __init
csio_init(व्योम)
अणु
	पूर्णांक rv = -ENOMEM;

	pr_info("%s %s\n", CSIO_DRV_DESC, CSIO_DRV_VERSION);

	csio_dfs_init();

	csio_fcoe_transport = fc_attach_transport(&csio_fc_transport_funcs);
	अगर (!csio_fcoe_transport)
		जाओ err;

	csio_fcoe_transport_vport =
			fc_attach_transport(&csio_fc_transport_vport_funcs);
	अगर (!csio_fcoe_transport_vport)
		जाओ err_vport;

	rv = pci_रेजिस्टर_driver(&csio_pci_driver);
	अगर (rv)
		जाओ err_pci;

	वापस 0;

err_pci:
	fc_release_transport(csio_fcoe_transport_vport);
err_vport:
	fc_release_transport(csio_fcoe_transport);
err:
	csio_dfs_निकास();
	वापस rv;
पूर्ण

/*
 * csio_निकास - Chelsio storage driver uninitialization .
 *
 * Function that माला_लो called in the unload path.
 */
अटल व्योम __निकास
csio_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&csio_pci_driver);
	csio_dfs_निकास();
	fc_release_transport(csio_fcoe_transport_vport);
	fc_release_transport(csio_fcoe_transport);
पूर्ण

module_init(csio_init);
module_निकास(csio_निकास);
MODULE_AUTHOR(CSIO_DRV_AUTHOR);
MODULE_DESCRIPTION(CSIO_DRV_DESC);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DEVICE_TABLE(pci, csio_pci_tbl);
MODULE_VERSION(CSIO_DRV_VERSION);
MODULE_FIRMWARE(FW_FNAME_T5);
MODULE_FIRMWARE(FW_FNAME_T6);
