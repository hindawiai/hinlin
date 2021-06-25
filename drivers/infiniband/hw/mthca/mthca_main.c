<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gfp.h>

#समावेश "mthca_dev.h"
#समावेश "mthca_config_reg.h"
#समावेश "mthca_cmd.h"
#समावेश "mthca_profile.h"
#समावेश "mthca_memfree.h"
#समावेश "mthca_wqe.h"

MODULE_AUTHOR("Roland Dreier");
MODULE_DESCRIPTION("Mellanox InfiniBand HCA low-level driver");
MODULE_LICENSE("Dual BSD/GPL");

#अगर_घोषित CONFIG_INFINIBAND_MTHCA_DEBUG

पूर्णांक mthca_debug_level = 0;
module_param_named(debug_level, mthca_debug_level, पूर्णांक, 0644);
MODULE_PARM_DESC(debug_level, "Enable debug tracing if > 0");

#पूर्ण_अगर /* CONFIG_INFINIBAND_MTHCA_DEBUG */

#अगर_घोषित CONFIG_PCI_MSI

अटल पूर्णांक msi_x = 1;
module_param(msi_x, पूर्णांक, 0444);
MODULE_PARM_DESC(msi_x, "attempt to use MSI-X if nonzero");

#अन्यथा /* CONFIG_PCI_MSI */

#घोषणा msi_x (0)

#पूर्ण_अगर /* CONFIG_PCI_MSI */

अटल पूर्णांक tune_pci = 0;
module_param(tune_pci, पूर्णांक, 0444);
MODULE_PARM_DESC(tune_pci, "increase PCI burst from the default set by BIOS if nonzero");

DEFINE_MUTEX(mthca_device_mutex);

#घोषणा MTHCA_DEFAULT_NUM_QP            (1 << 16)
#घोषणा MTHCA_DEFAULT_RDB_PER_QP        (1 << 2)
#घोषणा MTHCA_DEFAULT_NUM_CQ            (1 << 16)
#घोषणा MTHCA_DEFAULT_NUM_MCG           (1 << 13)
#घोषणा MTHCA_DEFAULT_NUM_MPT           (1 << 17)
#घोषणा MTHCA_DEFAULT_NUM_MTT           (1 << 20)
#घोषणा MTHCA_DEFAULT_NUM_UDAV          (1 << 15)
#घोषणा MTHCA_DEFAULT_NUM_RESERVED_MTTS (1 << 18)
#घोषणा MTHCA_DEFAULT_NUM_UARC_SIZE     (1 << 18)

अटल काष्ठा mthca_profile hca_profile = अणु
	.num_qp             = MTHCA_DEFAULT_NUM_QP,
	.rdb_per_qp         = MTHCA_DEFAULT_RDB_PER_QP,
	.num_cq             = MTHCA_DEFAULT_NUM_CQ,
	.num_mcg            = MTHCA_DEFAULT_NUM_MCG,
	.num_mpt            = MTHCA_DEFAULT_NUM_MPT,
	.num_mtt            = MTHCA_DEFAULT_NUM_MTT,
	.num_udav           = MTHCA_DEFAULT_NUM_UDAV,          /* Tavor only */
	.fmr_reserved_mtts  = MTHCA_DEFAULT_NUM_RESERVED_MTTS, /* Tavor only */
	.uarc_size          = MTHCA_DEFAULT_NUM_UARC_SIZE,     /* Arbel only */
पूर्ण;

module_param_named(num_qp, hca_profile.num_qp, पूर्णांक, 0444);
MODULE_PARM_DESC(num_qp, "maximum number of QPs per HCA");

module_param_named(rdb_per_qp, hca_profile.rdb_per_qp, पूर्णांक, 0444);
MODULE_PARM_DESC(rdb_per_qp, "number of RDB buffers per QP");

module_param_named(num_cq, hca_profile.num_cq, पूर्णांक, 0444);
MODULE_PARM_DESC(num_cq, "maximum number of CQs per HCA");

module_param_named(num_mcg, hca_profile.num_mcg, पूर्णांक, 0444);
MODULE_PARM_DESC(num_mcg, "maximum number of multicast groups per HCA");

module_param_named(num_mpt, hca_profile.num_mpt, पूर्णांक, 0444);
MODULE_PARM_DESC(num_mpt,
		"maximum number of memory protection table entries per HCA");

module_param_named(num_mtt, hca_profile.num_mtt, पूर्णांक, 0444);
MODULE_PARM_DESC(num_mtt,
		 "maximum number of memory translation table segments per HCA");

module_param_named(num_udav, hca_profile.num_udav, पूर्णांक, 0444);
MODULE_PARM_DESC(num_udav, "maximum number of UD address vectors per HCA");

module_param_named(fmr_reserved_mtts, hca_profile.fmr_reserved_mtts, पूर्णांक, 0444);
MODULE_PARM_DESC(fmr_reserved_mtts,
		 "number of memory translation table segments reserved for FMR");

अटल पूर्णांक log_mtts_per_seg = ilog2(MTHCA_MTT_SEG_SIZE / 8);
module_param_named(log_mtts_per_seg, log_mtts_per_seg, पूर्णांक, 0444);
MODULE_PARM_DESC(log_mtts_per_seg, "Log2 number of MTT entries per segment (1-5)");

अटल अक्षर mthca_version[] =
	DRV_NAME ": Mellanox InfiniBand HCA driver v"
	DRV_VERSION " (" DRV_RELDATE ")\n";

अटल पूर्णांक mthca_tune_pci(काष्ठा mthca_dev *mdev)
अणु
	अगर (!tune_pci)
		वापस 0;

	/* First try to max out Read Byte Count */
	अगर (pci_find_capability(mdev->pdev, PCI_CAP_ID_PCIX)) अणु
		अगर (pcix_set_mmrbc(mdev->pdev, pcix_get_max_mmrbc(mdev->pdev))) अणु
			mthca_err(mdev, "Couldn't set PCI-X max read count, "
				"aborting.\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अगर (!(mdev->mthca_flags & MTHCA_FLAG_PCIE))
		mthca_info(mdev, "No PCI-X capability, not setting RBC.\n");

	अगर (pci_is_pcie(mdev->pdev)) अणु
		अगर (pcie_set_पढ़ोrq(mdev->pdev, 4096)) अणु
			mthca_err(mdev, "Couldn't write PCI Express read request, "
				"aborting.\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अगर (mdev->mthca_flags & MTHCA_FLAG_PCIE)
		mthca_info(mdev, "No PCI Express capability, "
			   "not setting Max Read Request Size.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक mthca_dev_lim(काष्ठा mthca_dev *mdev, काष्ठा mthca_dev_lim *dev_lim)
अणु
	पूर्णांक err;

	mdev->limits.mtt_seg_size = (1 << log_mtts_per_seg) * 8;
	err = mthca_QUERY_DEV_LIM(mdev, dev_lim);
	अगर (err) अणु
		mthca_err(mdev, "QUERY_DEV_LIM command returned %d"
				", aborting.\n", err);
		वापस err;
	पूर्ण
	अगर (dev_lim->min_page_sz > PAGE_SIZE) अणु
		mthca_err(mdev, "HCA minimum page size of %d bigger than "
			  "kernel PAGE_SIZE of %ld, aborting.\n",
			  dev_lim->min_page_sz, PAGE_SIZE);
		वापस -ENODEV;
	पूर्ण
	अगर (dev_lim->num_ports > MTHCA_MAX_PORTS) अणु
		mthca_err(mdev, "HCA has %d ports, but we only support %d, "
			  "aborting.\n",
			  dev_lim->num_ports, MTHCA_MAX_PORTS);
		वापस -ENODEV;
	पूर्ण

	अगर (dev_lim->uar_size > pci_resource_len(mdev->pdev, 2)) अणु
		mthca_err(mdev, "HCA reported UAR size of 0x%x bigger than "
			  "PCI resource 2 size of 0x%llx, aborting.\n",
			  dev_lim->uar_size,
			  (अचिन्हित दीर्घ दीर्घ)pci_resource_len(mdev->pdev, 2));
		वापस -ENODEV;
	पूर्ण

	mdev->limits.num_ports      	= dev_lim->num_ports;
	mdev->limits.vl_cap             = dev_lim->max_vl;
	mdev->limits.mtu_cap            = dev_lim->max_mtu;
	mdev->limits.gid_table_len  	= dev_lim->max_gids;
	mdev->limits.pkey_table_len 	= dev_lim->max_pkeys;
	mdev->limits.local_ca_ack_delay = dev_lim->local_ca_ack_delay;
	/*
	 * Need to allow क्रम worst हाल send WQE overhead and check
	 * whether max_desc_sz imposes a lower limit than max_sg; UD
	 * send has the biggest overhead.
	 */
	mdev->limits.max_sg		= min_t(पूर्णांक, dev_lim->max_sg,
					      (dev_lim->max_desc_sz -
					       माप (काष्ठा mthca_next_seg) -
					       (mthca_is_memमुक्त(mdev) ?
						माप (काष्ठा mthca_arbel_ud_seg) :
						माप (काष्ठा mthca_tavor_ud_seg))) /
						माप (काष्ठा mthca_data_seg));
	mdev->limits.max_wqes           = dev_lim->max_qp_sz;
	mdev->limits.max_qp_init_rdma   = dev_lim->max_requester_per_qp;
	mdev->limits.reserved_qps       = dev_lim->reserved_qps;
	mdev->limits.max_srq_wqes       = dev_lim->max_srq_sz;
	mdev->limits.reserved_srqs      = dev_lim->reserved_srqs;
	mdev->limits.reserved_eecs      = dev_lim->reserved_eecs;
	mdev->limits.max_desc_sz        = dev_lim->max_desc_sz;
	mdev->limits.max_srq_sge	= mthca_max_srq_sge(mdev);
	/*
	 * Subtract 1 from the limit because we need to allocate a
	 * spare CQE so the HCA HW can tell the dअगरference between an
	 * empty CQ and a full CQ.
	 */
	mdev->limits.max_cqes           = dev_lim->max_cq_sz - 1;
	mdev->limits.reserved_cqs       = dev_lim->reserved_cqs;
	mdev->limits.reserved_eqs       = dev_lim->reserved_eqs;
	mdev->limits.reserved_mtts      = dev_lim->reserved_mtts;
	mdev->limits.reserved_mrws      = dev_lim->reserved_mrws;
	mdev->limits.reserved_uars      = dev_lim->reserved_uars;
	mdev->limits.reserved_pds       = dev_lim->reserved_pds;
	mdev->limits.port_width_cap     = dev_lim->max_port_width;
	mdev->limits.page_size_cap      = ~(u32) (dev_lim->min_page_sz - 1);
	mdev->limits.flags              = dev_lim->flags;
	/*
	 * For old FW that करोesn't वापस अटल rate support, use a
	 * value of 0x3 (only अटल rate values of 0 or 1 are handled),
	 * except on Sinai, where even old FW can handle अटल rate
	 * values of 2 and 3.
	 */
	अगर (dev_lim->stat_rate_support)
		mdev->limits.stat_rate_support = dev_lim->stat_rate_support;
	अन्यथा अगर (mdev->mthca_flags & MTHCA_FLAG_SINAI_OPT)
		mdev->limits.stat_rate_support = 0xf;
	अन्यथा
		mdev->limits.stat_rate_support = 0x3;

	/* IB_DEVICE_RESIZE_MAX_WR not supported by driver.
	   May be करोable since hardware supports it क्रम SRQ.

	   IB_DEVICE_N_NOTIFY_CQ is supported by hardware but not by driver.

	   IB_DEVICE_SRQ_RESIZE is supported by hardware but SRQ is not
	   supported by driver. */
	mdev->device_cap_flags = IB_DEVICE_CHANGE_PHY_PORT |
		IB_DEVICE_PORT_ACTIVE_EVENT |
		IB_DEVICE_SYS_IMAGE_GUID |
		IB_DEVICE_RC_RNR_NAK_GEN;

	अगर (dev_lim->flags & DEV_LIM_FLAG_BAD_PKEY_CNTR)
		mdev->device_cap_flags |= IB_DEVICE_BAD_PKEY_CNTR;

	अगर (dev_lim->flags & DEV_LIM_FLAG_BAD_QKEY_CNTR)
		mdev->device_cap_flags |= IB_DEVICE_BAD_QKEY_CNTR;

	अगर (dev_lim->flags & DEV_LIM_FLAG_RAW_MULTI)
		mdev->device_cap_flags |= IB_DEVICE_RAW_MULTI;

	अगर (dev_lim->flags & DEV_LIM_FLAG_AUTO_PATH_MIG)
		mdev->device_cap_flags |= IB_DEVICE_AUTO_PATH_MIG;

	अगर (dev_lim->flags & DEV_LIM_FLAG_UD_AV_PORT_ENFORCE)
		mdev->device_cap_flags |= IB_DEVICE_UD_AV_PORT_ENFORCE;

	अगर (dev_lim->flags & DEV_LIM_FLAG_SRQ)
		mdev->mthca_flags |= MTHCA_FLAG_SRQ;

	अगर (mthca_is_memमुक्त(mdev))
		अगर (dev_lim->flags & DEV_LIM_FLAG_IPOIB_CSUM)
			mdev->device_cap_flags |= IB_DEVICE_UD_IP_CSUM;

	वापस 0;
पूर्ण

अटल पूर्णांक mthca_init_tavor(काष्ठा mthca_dev *mdev)
अणु
	s64 size;
	पूर्णांक err;
	काष्ठा mthca_dev_lim        dev_lim;
	काष्ठा mthca_profile        profile;
	काष्ठा mthca_init_hca_param init_hca;

	err = mthca_SYS_EN(mdev);
	अगर (err) अणु
		mthca_err(mdev, "SYS_EN command returned %d, aborting.\n", err);
		वापस err;
	पूर्ण

	err = mthca_QUERY_FW(mdev);
	अगर (err) अणु
		mthca_err(mdev, "QUERY_FW command returned %d,"
				" aborting.\n", err);
		जाओ err_disable;
	पूर्ण
	err = mthca_QUERY_DDR(mdev);
	अगर (err) अणु
		mthca_err(mdev, "QUERY_DDR command returned %d, aborting.\n", err);
		जाओ err_disable;
	पूर्ण

	err = mthca_dev_lim(mdev, &dev_lim);
	अगर (err) अणु
		mthca_err(mdev, "QUERY_DEV_LIM command returned %d, aborting.\n", err);
		जाओ err_disable;
	पूर्ण

	profile = hca_profile;
	profile.num_uar   = dev_lim.uar_size / PAGE_SIZE;
	profile.uarc_size = 0;
	अगर (mdev->mthca_flags & MTHCA_FLAG_SRQ)
		profile.num_srq = dev_lim.max_srqs;

	size = mthca_make_profile(mdev, &profile, &dev_lim, &init_hca);
	अगर (size < 0) अणु
		err = size;
		जाओ err_disable;
	पूर्ण

	err = mthca_INIT_HCA(mdev, &init_hca);
	अगर (err) अणु
		mthca_err(mdev, "INIT_HCA command returned %d, aborting.\n", err);
		जाओ err_disable;
	पूर्ण

	वापस 0;

err_disable:
	mthca_SYS_DIS(mdev);

	वापस err;
पूर्ण

अटल पूर्णांक mthca_load_fw(काष्ठा mthca_dev *mdev)
अणु
	पूर्णांक err;

	/* FIXME: use HCA-attached memory क्रम FW अगर present */

	mdev->fw.arbel.fw_icm =
		mthca_alloc_icm(mdev, mdev->fw.arbel.fw_pages,
				GFP_HIGHUSER | __GFP_NOWARN, 0);
	अगर (!mdev->fw.arbel.fw_icm) अणु
		mthca_err(mdev, "Couldn't allocate FW area, aborting.\n");
		वापस -ENOMEM;
	पूर्ण

	err = mthca_MAP_FA(mdev, mdev->fw.arbel.fw_icm);
	अगर (err) अणु
		mthca_err(mdev, "MAP_FA command returned %d, aborting.\n", err);
		जाओ err_मुक्त;
	पूर्ण
	err = mthca_RUN_FW(mdev);
	अगर (err) अणु
		mthca_err(mdev, "RUN_FW command returned %d, aborting.\n", err);
		जाओ err_unmap_fa;
	पूर्ण

	वापस 0;

err_unmap_fa:
	mthca_UNMAP_FA(mdev);

err_मुक्त:
	mthca_मुक्त_icm(mdev, mdev->fw.arbel.fw_icm, 0);
	वापस err;
पूर्ण

अटल पूर्णांक mthca_init_icm(काष्ठा mthca_dev *mdev,
			  काष्ठा mthca_dev_lim *dev_lim,
			  काष्ठा mthca_init_hca_param *init_hca,
			  u64 icm_size)
अणु
	u64 aux_pages;
	पूर्णांक err;

	err = mthca_SET_ICM_SIZE(mdev, icm_size, &aux_pages);
	अगर (err) अणु
		mthca_err(mdev, "SET_ICM_SIZE command returned %d, aborting.\n", err);
		वापस err;
	पूर्ण

	mthca_dbg(mdev, "%lld KB of HCA context requires %lld KB aux memory.\n",
		  (अचिन्हित दीर्घ दीर्घ) icm_size >> 10,
		  (अचिन्हित दीर्घ दीर्घ) aux_pages << 2);

	mdev->fw.arbel.aux_icm = mthca_alloc_icm(mdev, aux_pages,
						 GFP_HIGHUSER | __GFP_NOWARN, 0);
	अगर (!mdev->fw.arbel.aux_icm) अणु
		mthca_err(mdev, "Couldn't allocate aux memory, aborting.\n");
		वापस -ENOMEM;
	पूर्ण

	err = mthca_MAP_ICM_AUX(mdev, mdev->fw.arbel.aux_icm);
	अगर (err) अणु
		mthca_err(mdev, "MAP_ICM_AUX returned %d, aborting.\n", err);
		जाओ err_मुक्त_aux;
	पूर्ण

	err = mthca_map_eq_icm(mdev, init_hca->eqc_base);
	अगर (err) अणु
		mthca_err(mdev, "Failed to map EQ context memory, aborting.\n");
		जाओ err_unmap_aux;
	पूर्ण

	/* CPU ग_लिखोs to non-reserved MTTs, जबतक HCA might DMA to reserved mtts */
	mdev->limits.reserved_mtts = ALIGN(mdev->limits.reserved_mtts * mdev->limits.mtt_seg_size,
					   dma_get_cache_alignment()) / mdev->limits.mtt_seg_size;

	mdev->mr_table.mtt_table = mthca_alloc_icm_table(mdev, init_hca->mtt_base,
							 mdev->limits.mtt_seg_size,
							 mdev->limits.num_mtt_segs,
							 mdev->limits.reserved_mtts,
							 1, 0);
	अगर (!mdev->mr_table.mtt_table) अणु
		mthca_err(mdev, "Failed to map MTT context memory, aborting.\n");
		err = -ENOMEM;
		जाओ err_unmap_eq;
	पूर्ण

	mdev->mr_table.mpt_table = mthca_alloc_icm_table(mdev, init_hca->mpt_base,
							 dev_lim->mpt_entry_sz,
							 mdev->limits.num_mpts,
							 mdev->limits.reserved_mrws,
							 1, 1);
	अगर (!mdev->mr_table.mpt_table) अणु
		mthca_err(mdev, "Failed to map MPT context memory, aborting.\n");
		err = -ENOMEM;
		जाओ err_unmap_mtt;
	पूर्ण

	mdev->qp_table.qp_table = mthca_alloc_icm_table(mdev, init_hca->qpc_base,
							dev_lim->qpc_entry_sz,
							mdev->limits.num_qps,
							mdev->limits.reserved_qps,
							0, 0);
	अगर (!mdev->qp_table.qp_table) अणु
		mthca_err(mdev, "Failed to map QP context memory, aborting.\n");
		err = -ENOMEM;
		जाओ err_unmap_mpt;
	पूर्ण

	mdev->qp_table.eqp_table = mthca_alloc_icm_table(mdev, init_hca->eqpc_base,
							 dev_lim->eqpc_entry_sz,
							 mdev->limits.num_qps,
							 mdev->limits.reserved_qps,
							 0, 0);
	अगर (!mdev->qp_table.eqp_table) अणु
		mthca_err(mdev, "Failed to map EQP context memory, aborting.\n");
		err = -ENOMEM;
		जाओ err_unmap_qp;
	पूर्ण

	mdev->qp_table.rdb_table = mthca_alloc_icm_table(mdev, init_hca->rdb_base,
							 MTHCA_RDB_ENTRY_SIZE,
							 mdev->limits.num_qps <<
							 mdev->qp_table.rdb_shअगरt, 0,
							 0, 0);
	अगर (!mdev->qp_table.rdb_table) अणु
		mthca_err(mdev, "Failed to map RDB context memory, aborting\n");
		err = -ENOMEM;
		जाओ err_unmap_eqp;
	पूर्ण

	mdev->cq_table.table = mthca_alloc_icm_table(mdev, init_hca->cqc_base,
						     dev_lim->cqc_entry_sz,
						     mdev->limits.num_cqs,
						     mdev->limits.reserved_cqs,
						     0, 0);
	अगर (!mdev->cq_table.table) अणु
		mthca_err(mdev, "Failed to map CQ context memory, aborting.\n");
		err = -ENOMEM;
		जाओ err_unmap_rdb;
	पूर्ण

	अगर (mdev->mthca_flags & MTHCA_FLAG_SRQ) अणु
		mdev->srq_table.table =
			mthca_alloc_icm_table(mdev, init_hca->srqc_base,
					      dev_lim->srq_entry_sz,
					      mdev->limits.num_srqs,
					      mdev->limits.reserved_srqs,
					      0, 0);
		अगर (!mdev->srq_table.table) अणु
			mthca_err(mdev, "Failed to map SRQ context memory, "
				  "aborting.\n");
			err = -ENOMEM;
			जाओ err_unmap_cq;
		पूर्ण
	पूर्ण

	/*
	 * It's not strictly required, but क्रम simplicity just map the
	 * whole multicast group table now.  The table isn't very big
	 * and it's a lot easier than trying to track ref counts.
	 */
	mdev->mcg_table.table = mthca_alloc_icm_table(mdev, init_hca->mc_base,
						      MTHCA_MGM_ENTRY_SIZE,
						      mdev->limits.num_mgms +
						      mdev->limits.num_amgms,
						      mdev->limits.num_mgms +
						      mdev->limits.num_amgms,
						      0, 0);
	अगर (!mdev->mcg_table.table) अणु
		mthca_err(mdev, "Failed to map MCG context memory, aborting.\n");
		err = -ENOMEM;
		जाओ err_unmap_srq;
	पूर्ण

	वापस 0;

err_unmap_srq:
	अगर (mdev->mthca_flags & MTHCA_FLAG_SRQ)
		mthca_मुक्त_icm_table(mdev, mdev->srq_table.table);

err_unmap_cq:
	mthca_मुक्त_icm_table(mdev, mdev->cq_table.table);

err_unmap_rdb:
	mthca_मुक्त_icm_table(mdev, mdev->qp_table.rdb_table);

err_unmap_eqp:
	mthca_मुक्त_icm_table(mdev, mdev->qp_table.eqp_table);

err_unmap_qp:
	mthca_मुक्त_icm_table(mdev, mdev->qp_table.qp_table);

err_unmap_mpt:
	mthca_मुक्त_icm_table(mdev, mdev->mr_table.mpt_table);

err_unmap_mtt:
	mthca_मुक्त_icm_table(mdev, mdev->mr_table.mtt_table);

err_unmap_eq:
	mthca_unmap_eq_icm(mdev);

err_unmap_aux:
	mthca_UNMAP_ICM_AUX(mdev);

err_मुक्त_aux:
	mthca_मुक्त_icm(mdev, mdev->fw.arbel.aux_icm, 0);

	वापस err;
पूर्ण

अटल व्योम mthca_मुक्त_icms(काष्ठा mthca_dev *mdev)
अणु

	mthca_मुक्त_icm_table(mdev, mdev->mcg_table.table);
	अगर (mdev->mthca_flags & MTHCA_FLAG_SRQ)
		mthca_मुक्त_icm_table(mdev, mdev->srq_table.table);
	mthca_मुक्त_icm_table(mdev, mdev->cq_table.table);
	mthca_मुक्त_icm_table(mdev, mdev->qp_table.rdb_table);
	mthca_मुक्त_icm_table(mdev, mdev->qp_table.eqp_table);
	mthca_मुक्त_icm_table(mdev, mdev->qp_table.qp_table);
	mthca_मुक्त_icm_table(mdev, mdev->mr_table.mpt_table);
	mthca_मुक्त_icm_table(mdev, mdev->mr_table.mtt_table);
	mthca_unmap_eq_icm(mdev);

	mthca_UNMAP_ICM_AUX(mdev);
	mthca_मुक्त_icm(mdev, mdev->fw.arbel.aux_icm, 0);
पूर्ण

अटल पूर्णांक mthca_init_arbel(काष्ठा mthca_dev *mdev)
अणु
	काष्ठा mthca_dev_lim        dev_lim;
	काष्ठा mthca_profile        profile;
	काष्ठा mthca_init_hca_param init_hca;
	s64 icm_size;
	पूर्णांक err;

	err = mthca_QUERY_FW(mdev);
	अगर (err) अणु
		mthca_err(mdev, "QUERY_FW command failed %d, aborting.\n", err);
		वापस err;
	पूर्ण

	err = mthca_ENABLE_LAM(mdev);
	अगर (err == -EAGAIN) अणु
		mthca_dbg(mdev, "No HCA-attached memory (running in MemFree mode)\n");
		mdev->mthca_flags |= MTHCA_FLAG_NO_LAM;
	पूर्ण अन्यथा अगर (err) अणु
		mthca_err(mdev, "ENABLE_LAM returned %d, aborting.\n", err);
		वापस err;
	पूर्ण

	err = mthca_load_fw(mdev);
	अगर (err) अणु
		mthca_err(mdev, "Loading FW returned %d, aborting.\n", err);
		जाओ err_disable;
	पूर्ण

	err = mthca_dev_lim(mdev, &dev_lim);
	अगर (err) अणु
		mthca_err(mdev, "QUERY_DEV_LIM returned %d, aborting.\n", err);
		जाओ err_stop_fw;
	पूर्ण

	profile = hca_profile;
	profile.num_uar  = dev_lim.uar_size / PAGE_SIZE;
	profile.num_udav = 0;
	अगर (mdev->mthca_flags & MTHCA_FLAG_SRQ)
		profile.num_srq = dev_lim.max_srqs;

	icm_size = mthca_make_profile(mdev, &profile, &dev_lim, &init_hca);
	अगर (icm_size < 0) अणु
		err = icm_size;
		जाओ err_stop_fw;
	पूर्ण

	err = mthca_init_icm(mdev, &dev_lim, &init_hca, icm_size);
	अगर (err)
		जाओ err_stop_fw;

	err = mthca_INIT_HCA(mdev, &init_hca);
	अगर (err) अणु
		mthca_err(mdev, "INIT_HCA command returned %d, aborting.\n", err);
		जाओ err_मुक्त_icm;
	पूर्ण

	वापस 0;

err_मुक्त_icm:
	mthca_मुक्त_icms(mdev);

err_stop_fw:
	mthca_UNMAP_FA(mdev);
	mthca_मुक्त_icm(mdev, mdev->fw.arbel.fw_icm, 0);

err_disable:
	अगर (!(mdev->mthca_flags & MTHCA_FLAG_NO_LAM))
		mthca_DISABLE_LAM(mdev);

	वापस err;
पूर्ण

अटल व्योम mthca_बंद_hca(काष्ठा mthca_dev *mdev)
अणु
	mthca_CLOSE_HCA(mdev, 0);

	अगर (mthca_is_memमुक्त(mdev)) अणु
		mthca_मुक्त_icms(mdev);

		mthca_UNMAP_FA(mdev);
		mthca_मुक्त_icm(mdev, mdev->fw.arbel.fw_icm, 0);

		अगर (!(mdev->mthca_flags & MTHCA_FLAG_NO_LAM))
			mthca_DISABLE_LAM(mdev);
	पूर्ण अन्यथा
		mthca_SYS_DIS(mdev);
पूर्ण

अटल पूर्णांक mthca_init_hca(काष्ठा mthca_dev *mdev)
अणु
	पूर्णांक err;
	काष्ठा mthca_adapter adapter;

	अगर (mthca_is_memमुक्त(mdev))
		err = mthca_init_arbel(mdev);
	अन्यथा
		err = mthca_init_tavor(mdev);

	अगर (err)
		वापस err;

	err = mthca_QUERY_ADAPTER(mdev, &adapter);
	अगर (err) अणु
		mthca_err(mdev, "QUERY_ADAPTER command returned %d, aborting.\n", err);
		जाओ err_बंद;
	पूर्ण

	mdev->eq_table.पूर्णांकa_pin = adapter.पूर्णांकa_pin;
	अगर (!mthca_is_memमुक्त(mdev))
		mdev->rev_id = adapter.revision_id;
	स_नकल(mdev->board_id, adapter.board_id, माप mdev->board_id);

	वापस 0;

err_बंद:
	mthca_बंद_hca(mdev);
	वापस err;
पूर्ण

अटल पूर्णांक mthca_setup_hca(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक err;

	MTHCA_INIT_DOORBELL_LOCK(&dev->करोorbell_lock);

	err = mthca_init_uar_table(dev);
	अगर (err) अणु
		mthca_err(dev, "Failed to initialize "
			  "user access region table, aborting.\n");
		वापस err;
	पूर्ण

	err = mthca_uar_alloc(dev, &dev->driver_uar);
	अगर (err) अणु
		mthca_err(dev, "Failed to allocate driver access region, "
			  "aborting.\n");
		जाओ err_uar_table_मुक्त;
	पूर्ण

	dev->kar = ioremap((phys_addr_t) dev->driver_uar.pfn << PAGE_SHIFT, PAGE_SIZE);
	अगर (!dev->kar) अणु
		mthca_err(dev, "Couldn't map kernel access region, "
			  "aborting.\n");
		err = -ENOMEM;
		जाओ err_uar_मुक्त;
	पूर्ण

	err = mthca_init_pd_table(dev);
	अगर (err) अणु
		mthca_err(dev, "Failed to initialize "
			  "protection domain table, aborting.\n");
		जाओ err_kar_unmap;
	पूर्ण

	err = mthca_init_mr_table(dev);
	अगर (err) अणु
		mthca_err(dev, "Failed to initialize "
			  "memory region table, aborting.\n");
		जाओ err_pd_table_मुक्त;
	पूर्ण

	err = mthca_pd_alloc(dev, 1, &dev->driver_pd);
	अगर (err) अणु
		mthca_err(dev, "Failed to create driver PD, "
			  "aborting.\n");
		जाओ err_mr_table_मुक्त;
	पूर्ण

	err = mthca_init_eq_table(dev);
	अगर (err) अणु
		mthca_err(dev, "Failed to initialize "
			  "event queue table, aborting.\n");
		जाओ err_pd_मुक्त;
	पूर्ण

	err = mthca_cmd_use_events(dev);
	अगर (err) अणु
		mthca_err(dev, "Failed to switch to event-driven "
			  "firmware commands, aborting.\n");
		जाओ err_eq_table_मुक्त;
	पूर्ण

	err = mthca_NOP(dev);
	अगर (err) अणु
		अगर (dev->mthca_flags & MTHCA_FLAG_MSI_X) अणु
			mthca_warn(dev, "NOP command failed to generate interrupt "
				   "(IRQ %d).\n",
				   dev->eq_table.eq[MTHCA_EQ_CMD].msi_x_vector);
			mthca_warn(dev, "Trying again with MSI-X disabled.\n");
		पूर्ण अन्यथा अणु
			mthca_err(dev, "NOP command failed to generate interrupt "
				  "(IRQ %d), aborting.\n",
				  dev->pdev->irq);
			mthca_err(dev, "BIOS or ACPI interrupt routing problem?\n");
		पूर्ण

		जाओ err_cmd_poll;
	पूर्ण

	mthca_dbg(dev, "NOP command IRQ test passed\n");

	err = mthca_init_cq_table(dev);
	अगर (err) अणु
		mthca_err(dev, "Failed to initialize "
			  "completion queue table, aborting.\n");
		जाओ err_cmd_poll;
	पूर्ण

	err = mthca_init_srq_table(dev);
	अगर (err) अणु
		mthca_err(dev, "Failed to initialize "
			  "shared receive queue table, aborting.\n");
		जाओ err_cq_table_मुक्त;
	पूर्ण

	err = mthca_init_qp_table(dev);
	अगर (err) अणु
		mthca_err(dev, "Failed to initialize "
			  "queue pair table, aborting.\n");
		जाओ err_srq_table_मुक्त;
	पूर्ण

	err = mthca_init_av_table(dev);
	अगर (err) अणु
		mthca_err(dev, "Failed to initialize "
			  "address vector table, aborting.\n");
		जाओ err_qp_table_मुक्त;
	पूर्ण

	err = mthca_init_mcg_table(dev);
	अगर (err) अणु
		mthca_err(dev, "Failed to initialize "
			  "multicast group table, aborting.\n");
		जाओ err_av_table_मुक्त;
	पूर्ण

	वापस 0;

err_av_table_मुक्त:
	mthca_cleanup_av_table(dev);

err_qp_table_मुक्त:
	mthca_cleanup_qp_table(dev);

err_srq_table_मुक्त:
	mthca_cleanup_srq_table(dev);

err_cq_table_मुक्त:
	mthca_cleanup_cq_table(dev);

err_cmd_poll:
	mthca_cmd_use_polling(dev);

err_eq_table_मुक्त:
	mthca_cleanup_eq_table(dev);

err_pd_मुक्त:
	mthca_pd_मुक्त(dev, &dev->driver_pd);

err_mr_table_मुक्त:
	mthca_cleanup_mr_table(dev);

err_pd_table_मुक्त:
	mthca_cleanup_pd_table(dev);

err_kar_unmap:
	iounmap(dev->kar);

err_uar_मुक्त:
	mthca_uar_मुक्त(dev, &dev->driver_uar);

err_uar_table_मुक्त:
	mthca_cleanup_uar_table(dev);
	वापस err;
पूर्ण

अटल पूर्णांक mthca_enable_msi_x(काष्ठा mthca_dev *mdev)
अणु
	पूर्णांक err;

	err = pci_alloc_irq_vectors(mdev->pdev, 3, 3, PCI_IRQ_MSIX);
	अगर (err < 0)
		वापस err;

	mdev->eq_table.eq[MTHCA_EQ_COMP ].msi_x_vector =
			pci_irq_vector(mdev->pdev, 0);
	mdev->eq_table.eq[MTHCA_EQ_ASYNC].msi_x_vector =
			pci_irq_vector(mdev->pdev, 1);
	mdev->eq_table.eq[MTHCA_EQ_CMD  ].msi_x_vector =
			pci_irq_vector(mdev->pdev, 2);

	वापस 0;
पूर्ण

/* Types of supported HCA */
क्रमागत अणु
	TAVOR,			/* MT23108                        */
	ARBEL_COMPAT,		/* MT25208 in Tavor compat mode   */
	ARBEL_NATIVE,		/* MT25208 with extended features */
	SINAI			/* MT25204 */
पूर्ण;

#घोषणा MTHCA_FW_VER(major, minor, subminor) \
	(((u64) (major) << 32) | ((u64) (minor) << 16) | (u64) (subminor))

अटल काष्ठा अणु
	u64 latest_fw;
	u32 flags;
पूर्ण mthca_hca_table[] = अणु
	[TAVOR]        = अणु .latest_fw = MTHCA_FW_VER(3, 5, 0),
			   .flags     = 0 पूर्ण,
	[ARBEL_COMPAT] = अणु .latest_fw = MTHCA_FW_VER(4, 8, 200),
			   .flags     = MTHCA_FLAG_PCIE पूर्ण,
	[ARBEL_NATIVE] = अणु .latest_fw = MTHCA_FW_VER(5, 3, 0),
			   .flags     = MTHCA_FLAG_MEMFREE |
					MTHCA_FLAG_PCIE पूर्ण,
	[SINAI]        = अणु .latest_fw = MTHCA_FW_VER(1, 2, 0),
			   .flags     = MTHCA_FLAG_MEMFREE |
					MTHCA_FLAG_PCIE    |
					MTHCA_FLAG_SINAI_OPT पूर्ण
पूर्ण;

अटल पूर्णांक __mthca_init_one(काष्ठा pci_dev *pdev, पूर्णांक hca_type)
अणु
	पूर्णांक ddr_hidden = 0;
	पूर्णांक err;
	काष्ठा mthca_dev *mdev;

	prपूर्णांकk(KERN_INFO PFX "Initializing %s\n",
	       pci_name(pdev));

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot enable PCI device, "
			"aborting.\n");
		वापस err;
	पूर्ण

	/*
	 * Check क्रम BARs.  We expect 0: 1MB, 2: 8MB, 4: DDR (may not
	 * be present)
	 */
	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM) ||
	    pci_resource_len(pdev, 0) != 1 << 20) अणु
		dev_err(&pdev->dev, "Missing DCS, aborting.\n");
		err = -ENODEV;
		जाओ err_disable_pdev;
	पूर्ण
	अगर (!(pci_resource_flags(pdev, 2) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "Missing UAR, aborting.\n");
		err = -ENODEV;
		जाओ err_disable_pdev;
	पूर्ण
	अगर (!(pci_resource_flags(pdev, 4) & IORESOURCE_MEM))
		ddr_hidden = 1;

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot obtain PCI resources, "
			"aborting.\n");
		जाओ err_disable_pdev;
	पूर्ण

	pci_set_master(pdev);

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err) अणु
		dev_warn(&pdev->dev, "Warning: couldn't set 64-bit PCI DMA mask.\n");
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "Can't set PCI DMA mask, aborting.\n");
			जाओ err_मुक्त_res;
		पूर्ण
	पूर्ण
	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err) अणु
		dev_warn(&pdev->dev, "Warning: couldn't set 64-bit "
			 "consistent PCI DMA mask.\n");
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "Can't set consistent PCI DMA mask, "
				"aborting.\n");
			जाओ err_मुक्त_res;
		पूर्ण
	पूर्ण

	/* We can handle large RDMA requests, so allow larger segments. */
	dma_set_max_seg_size(&pdev->dev, 1024 * 1024 * 1024);

	mdev = ib_alloc_device(mthca_dev, ib_dev);
	अगर (!mdev) अणु
		dev_err(&pdev->dev, "Device struct alloc failed, "
			"aborting.\n");
		err = -ENOMEM;
		जाओ err_मुक्त_res;
	पूर्ण

	mdev->pdev = pdev;

	mdev->mthca_flags = mthca_hca_table[hca_type].flags;
	अगर (ddr_hidden)
		mdev->mthca_flags |= MTHCA_FLAG_DDR_HIDDEN;

	/*
	 * Now reset the HCA beक्रमe we touch the PCI capabilities or
	 * attempt a firmware command, since a boot ROM may have left
	 * the HCA in an undefined state.
	 */
	err = mthca_reset(mdev);
	अगर (err) अणु
		mthca_err(mdev, "Failed to reset HCA, aborting.\n");
		जाओ err_मुक्त_dev;
	पूर्ण

	err = mthca_cmd_init(mdev);
	अगर (err) अणु
		mthca_err(mdev, "Failed to init command interface, aborting.\n");
		जाओ err_मुक्त_dev;
	पूर्ण

	err = mthca_tune_pci(mdev);
	अगर (err)
		जाओ err_cmd;

	err = mthca_init_hca(mdev);
	अगर (err)
		जाओ err_cmd;

	अगर (mdev->fw_ver < mthca_hca_table[hca_type].latest_fw) अणु
		mthca_warn(mdev, "HCA FW version %d.%d.%03d is old (%d.%d.%03d is current).\n",
			   (पूर्णांक) (mdev->fw_ver >> 32), (पूर्णांक) (mdev->fw_ver >> 16) & 0xffff,
			   (पूर्णांक) (mdev->fw_ver & 0xffff),
			   (पूर्णांक) (mthca_hca_table[hca_type].latest_fw >> 32),
			   (पूर्णांक) (mthca_hca_table[hca_type].latest_fw >> 16) & 0xffff,
			   (पूर्णांक) (mthca_hca_table[hca_type].latest_fw & 0xffff));
		mthca_warn(mdev, "If you have problems, try updating your HCA FW.\n");
	पूर्ण

	अगर (msi_x && !mthca_enable_msi_x(mdev))
		mdev->mthca_flags |= MTHCA_FLAG_MSI_X;

	err = mthca_setup_hca(mdev);
	अगर (err == -EBUSY && (mdev->mthca_flags & MTHCA_FLAG_MSI_X)) अणु
		pci_मुक्त_irq_vectors(pdev);
		mdev->mthca_flags &= ~MTHCA_FLAG_MSI_X;

		err = mthca_setup_hca(mdev);
	पूर्ण

	अगर (err)
		जाओ err_बंद;

	err = mthca_रेजिस्टर_device(mdev);
	अगर (err)
		जाओ err_cleanup;

	err = mthca_create_agents(mdev);
	अगर (err)
		जाओ err_unरेजिस्टर;

	pci_set_drvdata(pdev, mdev);
	mdev->hca_type = hca_type;

	mdev->active = true;

	वापस 0;

err_unरेजिस्टर:
	mthca_unरेजिस्टर_device(mdev);

err_cleanup:
	mthca_cleanup_mcg_table(mdev);
	mthca_cleanup_av_table(mdev);
	mthca_cleanup_qp_table(mdev);
	mthca_cleanup_srq_table(mdev);
	mthca_cleanup_cq_table(mdev);
	mthca_cmd_use_polling(mdev);
	mthca_cleanup_eq_table(mdev);

	mthca_pd_मुक्त(mdev, &mdev->driver_pd);

	mthca_cleanup_mr_table(mdev);
	mthca_cleanup_pd_table(mdev);
	mthca_cleanup_uar_table(mdev);

err_बंद:
	अगर (mdev->mthca_flags & MTHCA_FLAG_MSI_X)
		pci_मुक्त_irq_vectors(pdev);

	mthca_बंद_hca(mdev);

err_cmd:
	mthca_cmd_cleanup(mdev);

err_मुक्त_dev:
	ib_dealloc_device(&mdev->ib_dev);

err_मुक्त_res:
	pci_release_regions(pdev);

err_disable_pdev:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम __mthca_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mthca_dev *mdev = pci_get_drvdata(pdev);
	पूर्णांक p;

	अगर (mdev) अणु
		mthca_मुक्त_agents(mdev);
		mthca_unरेजिस्टर_device(mdev);

		क्रम (p = 1; p <= mdev->limits.num_ports; ++p)
			mthca_CLOSE_IB(mdev, p);

		mthca_cleanup_mcg_table(mdev);
		mthca_cleanup_av_table(mdev);
		mthca_cleanup_qp_table(mdev);
		mthca_cleanup_srq_table(mdev);
		mthca_cleanup_cq_table(mdev);
		mthca_cmd_use_polling(mdev);
		mthca_cleanup_eq_table(mdev);

		mthca_pd_मुक्त(mdev, &mdev->driver_pd);

		mthca_cleanup_mr_table(mdev);
		mthca_cleanup_pd_table(mdev);

		iounmap(mdev->kar);
		mthca_uar_मुक्त(mdev, &mdev->driver_uar);
		mthca_cleanup_uar_table(mdev);
		mthca_बंद_hca(mdev);
		mthca_cmd_cleanup(mdev);

		अगर (mdev->mthca_flags & MTHCA_FLAG_MSI_X)
			pci_मुक्त_irq_vectors(pdev);

		ib_dealloc_device(&mdev->ib_dev);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		pci_set_drvdata(pdev, शून्य);
	पूर्ण
पूर्ण

पूर्णांक __mthca_restart_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mthca_dev *mdev;
	पूर्णांक hca_type;

	mdev = pci_get_drvdata(pdev);
	अगर (!mdev)
		वापस -ENODEV;
	hca_type = mdev->hca_type;
	__mthca_हटाओ_one(pdev);
	वापस __mthca_init_one(pdev, hca_type);
पूर्ण

अटल पूर्णांक mthca_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक ret;

	mutex_lock(&mthca_device_mutex);

	prपूर्णांकk_once(KERN_INFO "%s", mthca_version);

	अगर (id->driver_data >= ARRAY_SIZE(mthca_hca_table)) अणु
		prपूर्णांकk(KERN_ERR PFX "%s has invalid driver data %lx\n",
		       pci_name(pdev), id->driver_data);
		mutex_unlock(&mthca_device_mutex);
		वापस -ENODEV;
	पूर्ण

	ret = __mthca_init_one(pdev, id->driver_data);

	mutex_unlock(&mthca_device_mutex);

	वापस ret;
पूर्ण

अटल व्योम mthca_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	mutex_lock(&mthca_device_mutex);
	__mthca_हटाओ_one(pdev);
	mutex_unlock(&mthca_device_mutex);
पूर्ण

अटल स्थिर काष्ठा pci_device_id mthca_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MELLANOX, PCI_DEVICE_ID_MELLANOX_TAVOR),
	  .driver_data = TAVOR पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOPSPIN, PCI_DEVICE_ID_MELLANOX_TAVOR),
	  .driver_data = TAVOR पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MELLANOX, PCI_DEVICE_ID_MELLANOX_ARBEL_COMPAT),
	  .driver_data = ARBEL_COMPAT पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOPSPIN, PCI_DEVICE_ID_MELLANOX_ARBEL_COMPAT),
	  .driver_data = ARBEL_COMPAT पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MELLANOX, PCI_DEVICE_ID_MELLANOX_ARBEL),
	  .driver_data = ARBEL_NATIVE पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOPSPIN, PCI_DEVICE_ID_MELLANOX_ARBEL),
	  .driver_data = ARBEL_NATIVE पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MELLANOX, PCI_DEVICE_ID_MELLANOX_SINAI),
	  .driver_data = SINAI पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOPSPIN, PCI_DEVICE_ID_MELLANOX_SINAI),
	  .driver_data = SINAI पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MELLANOX, PCI_DEVICE_ID_MELLANOX_SINAI_OLD),
	  .driver_data = SINAI पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOPSPIN, PCI_DEVICE_ID_MELLANOX_SINAI_OLD),
	  .driver_data = SINAI पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, mthca_pci_table);

अटल काष्ठा pci_driver mthca_driver = अणु
	.name		= DRV_NAME,
	.id_table	= mthca_pci_table,
	.probe		= mthca_init_one,
	.हटाओ		= mthca_हटाओ_one,
पूर्ण;

अटल व्योम __init __mthca_check_profile_val(स्थिर अक्षर *name, पूर्णांक *pval,
					     पूर्णांक pval_शेष)
अणु
	/* value must be positive and घातer of 2 */
	पूर्णांक old_pval = *pval;

	अगर (old_pval <= 0)
		*pval = pval_शेष;
	अन्यथा
		*pval = roundup_घात_of_two(old_pval);

	अगर (old_pval != *pval) अणु
		prपूर्णांकk(KERN_WARNING PFX "Invalid value %d for %s in module parameter.\n",
		       old_pval, name);
		prपूर्णांकk(KERN_WARNING PFX "Corrected %s to %d.\n", name, *pval);
	पूर्ण
पूर्ण

#घोषणा mthca_check_profile_val(name, शेष)				\
	__mthca_check_profile_val(#name, &hca_profile.name, शेष)

अटल व्योम __init mthca_validate_profile(व्योम)
अणु
	mthca_check_profile_val(num_qp,            MTHCA_DEFAULT_NUM_QP);
	mthca_check_profile_val(rdb_per_qp,        MTHCA_DEFAULT_RDB_PER_QP);
	mthca_check_profile_val(num_cq,            MTHCA_DEFAULT_NUM_CQ);
	mthca_check_profile_val(num_mcg, 	   MTHCA_DEFAULT_NUM_MCG);
	mthca_check_profile_val(num_mpt, 	   MTHCA_DEFAULT_NUM_MPT);
	mthca_check_profile_val(num_mtt, 	   MTHCA_DEFAULT_NUM_MTT);
	mthca_check_profile_val(num_udav,          MTHCA_DEFAULT_NUM_UDAV);
	mthca_check_profile_val(fmr_reserved_mtts, MTHCA_DEFAULT_NUM_RESERVED_MTTS);

	अगर (hca_profile.fmr_reserved_mtts >= hca_profile.num_mtt) अणु
		prपूर्णांकk(KERN_WARNING PFX "Invalid fmr_reserved_mtts module parameter %d.\n",
		       hca_profile.fmr_reserved_mtts);
		prपूर्णांकk(KERN_WARNING PFX "(Must be smaller than num_mtt %d)\n",
		       hca_profile.num_mtt);
		hca_profile.fmr_reserved_mtts = hca_profile.num_mtt / 2;
		prपूर्णांकk(KERN_WARNING PFX "Corrected fmr_reserved_mtts to %d.\n",
		       hca_profile.fmr_reserved_mtts);
	पूर्ण

	अगर ((log_mtts_per_seg < 1) || (log_mtts_per_seg > 5)) अणु
		prपूर्णांकk(KERN_WARNING PFX "bad log_mtts_per_seg (%d). Using default - %d\n",
		       log_mtts_per_seg, ilog2(MTHCA_MTT_SEG_SIZE / 8));
		log_mtts_per_seg = ilog2(MTHCA_MTT_SEG_SIZE / 8);
	पूर्ण
पूर्ण

अटल पूर्णांक __init mthca_init(व्योम)
अणु
	पूर्णांक ret;

	mthca_validate_profile();

	ret = mthca_catas_init();
	अगर (ret)
		वापस ret;

	ret = pci_रेजिस्टर_driver(&mthca_driver);
	अगर (ret < 0) अणु
		mthca_catas_cleanup();
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास mthca_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&mthca_driver);
	mthca_catas_cleanup();
पूर्ण

module_init(mthca_init);
module_निकास(mthca_cleanup);
