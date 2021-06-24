<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*******************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/addrconf.h>

#समावेश "i40iw.h"
#समावेश "i40iw_register.h"
#समावेश <net/netevent.h>
#घोषणा CLIENT_IW_INTERFACE_VERSION_MAJOR 0
#घोषणा CLIENT_IW_INTERFACE_VERSION_MINOR 01
#घोषणा CLIENT_IW_INTERFACE_VERSION_BUILD 00

#घोषणा DRV_VERSION_MAJOR 0
#घोषणा DRV_VERSION_MINOR 5
#घोषणा DRV_VERSION_BUILD 123
#घोषणा DRV_VERSION	__stringअगरy(DRV_VERSION_MAJOR) "."		\
	__stringअगरy(DRV_VERSION_MINOR) "." __stringअगरy(DRV_VERSION_BUILD)

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug flags: 0=disabled (default), 0x7fffffff=all");

अटल पूर्णांक resource_profile;
module_param(resource_profile, पूर्णांक, 0644);
MODULE_PARM_DESC(resource_profile,
		 "Resource Profile: 0=no VF RDMA support (default), 1=Weighted VF, 2=Even Distribution");

अटल पूर्णांक max_rdma_vfs = 32;
module_param(max_rdma_vfs, पूर्णांक, 0644);
MODULE_PARM_DESC(max_rdma_vfs, "Maximum VF count: 0-32 32=default");
अटल पूर्णांक mpa_version = 2;
module_param(mpa_version, पूर्णांक, 0644);
MODULE_PARM_DESC(mpa_version, "MPA version to be used in MPA Req/Resp 1 or 2");

MODULE_AUTHOR("Intel Corporation, <e1000-rdma@lists.sourceforge.net>");
MODULE_DESCRIPTION("Intel(R) Ethernet Connection X722 iWARP RDMA Driver");
MODULE_LICENSE("Dual BSD/GPL");

अटल काष्ठा i40e_client i40iw_client;
अटल अक्षर i40iw_client_name[I40E_CLIENT_STR_LENGTH] = "i40iw";

अटल LIST_HEAD(i40iw_handlers);
अटल DEFINE_SPINLOCK(i40iw_handler_lock);

अटल क्रमागत i40iw_status_code i40iw_virtchnl_send(काष्ठा i40iw_sc_dev *dev,
						  u32 vf_id, u8 *msg, u16 len);

अटल काष्ठा notअगरier_block i40iw_inetaddr_notअगरier = अणु
	.notअगरier_call = i40iw_inetaddr_event
पूर्ण;

अटल काष्ठा notअगरier_block i40iw_inetaddr6_notअगरier = अणु
	.notअगरier_call = i40iw_inet6addr_event
पूर्ण;

अटल काष्ठा notअगरier_block i40iw_net_notअगरier = अणु
	.notअगरier_call = i40iw_net_event
पूर्ण;

अटल काष्ठा notअगरier_block i40iw_netdevice_notअगरier = अणु
	.notअगरier_call = i40iw_netdevice_event
पूर्ण;

/**
 * i40iw_find_i40e_handler - find a handler given a client info
 * @ldev: poपूर्णांकer to a client info
 */
अटल काष्ठा i40iw_handler *i40iw_find_i40e_handler(काष्ठा i40e_info *ldev)
अणु
	काष्ठा i40iw_handler *hdl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i40iw_handler_lock, flags);
	list_क्रम_each_entry(hdl, &i40iw_handlers, list) अणु
		अगर (hdl->ldev.netdev == ldev->netdev) अणु
			spin_unlock_irqrestore(&i40iw_handler_lock, flags);
			वापस hdl;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&i40iw_handler_lock, flags);
	वापस शून्य;
पूर्ण

/**
 * i40iw_find_netdev - find a handler given a netdev
 * @netdev: poपूर्णांकer to net_device
 */
काष्ठा i40iw_handler *i40iw_find_netdev(काष्ठा net_device *netdev)
अणु
	काष्ठा i40iw_handler *hdl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i40iw_handler_lock, flags);
	list_क्रम_each_entry(hdl, &i40iw_handlers, list) अणु
		अगर (hdl->ldev.netdev == netdev) अणु
			spin_unlock_irqrestore(&i40iw_handler_lock, flags);
			वापस hdl;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&i40iw_handler_lock, flags);
	वापस शून्य;
पूर्ण

/**
 * i40iw_add_handler - add a handler to the list
 * @hdl: handler to be added to the handler list
 */
अटल व्योम i40iw_add_handler(काष्ठा i40iw_handler *hdl)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i40iw_handler_lock, flags);
	list_add(&hdl->list, &i40iw_handlers);
	spin_unlock_irqrestore(&i40iw_handler_lock, flags);
पूर्ण

/**
 * i40iw_del_handler - delete a handler from the list
 * @hdl: handler to be deleted from the handler list
 */
अटल पूर्णांक i40iw_del_handler(काष्ठा i40iw_handler *hdl)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i40iw_handler_lock, flags);
	list_del(&hdl->list);
	spin_unlock_irqrestore(&i40iw_handler_lock, flags);
	वापस 0;
पूर्ण

/**
 * i40iw_enable_पूर्णांकr - set up device पूर्णांकerrupts
 * @dev: hardware control device काष्ठाure
 * @msix_id: id of the पूर्णांकerrupt to be enabled
 */
अटल व्योम i40iw_enable_पूर्णांकr(काष्ठा i40iw_sc_dev *dev, u32 msix_id)
अणु
	u32 val;

	val = I40E_PFINT_DYN_CTLN_INTENA_MASK |
		I40E_PFINT_DYN_CTLN_CLEARPBA_MASK |
		(3 << I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT);
	अगर (dev->is_pf)
		i40iw_wr32(dev->hw, I40E_PFINT_DYN_CTLN(msix_id - 1), val);
	अन्यथा
		i40iw_wr32(dev->hw, I40E_VFINT_DYN_CTLN1(msix_id - 1), val);
पूर्ण

/**
 * i40iw_dpc - tasklet क्रम aeq and ceq 0
 * @t: Timer context to fetch poपूर्णांकer to iwarp device
 */
अटल व्योम i40iw_dpc(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा i40iw_device *iwdev = from_tasklet(iwdev, t, dpc_tasklet);

	अगर (iwdev->msix_shared)
		i40iw_process_ceq(iwdev, iwdev->ceqlist);
	i40iw_process_aeq(iwdev);
	i40iw_enable_पूर्णांकr(&iwdev->sc_dev, iwdev->iw_msixtbl[0].idx);
पूर्ण

/**
 * i40iw_ceq_dpc - dpc handler क्रम CEQ
 * @t: Timer context to fetch poपूर्णांकer to CEQ data
 */
अटल व्योम i40iw_ceq_dpc(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा i40iw_ceq *iwceq = from_tasklet(iwceq, t, dpc_tasklet);
	काष्ठा i40iw_device *iwdev = iwceq->iwdev;

	i40iw_process_ceq(iwdev, iwceq);
	i40iw_enable_पूर्णांकr(&iwdev->sc_dev, iwceq->msix_idx);
पूर्ण

/**
 * i40iw_irq_handler - पूर्णांकerrupt handler क्रम aeq and ceq0
 * @irq: Interrupt request number
 * @data: iwarp device
 */
अटल irqवापस_t i40iw_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)data;

	tasklet_schedule(&iwdev->dpc_tasklet);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * i40iw_destroy_cqp  - destroy control qp
 * @iwdev: iwarp device
 * @मुक्त_hwcqp: 1 अगर CQP should be destroyed
 *
 * Issue destroy cqp request and
 * मुक्त the resources associated with the cqp
 */
अटल व्योम i40iw_destroy_cqp(काष्ठा i40iw_device *iwdev, bool मुक्त_hwcqp)
अणु
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_cqp *cqp = &iwdev->cqp;

	अगर (मुक्त_hwcqp)
		dev->cqp_ops->cqp_destroy(dev->cqp);

	i40iw_cleanup_pending_cqp_op(iwdev);

	i40iw_मुक्त_dma_mem(dev->hw, &cqp->sq);
	kमुक्त(cqp->scratch_array);
	iwdev->cqp.scratch_array = शून्य;

	kमुक्त(cqp->cqp_requests);
	cqp->cqp_requests = शून्य;
पूर्ण

/**
 * i40iw_disable_irq - disable device पूर्णांकerrupts
 * @dev: hardware control device काष्ठाure
 * @msix_vec: msix vector to disable irq
 * @dev_id: parameter to pass to मुक्त_irq (used during irq setup)
 *
 * The function is called when destroying aeq/ceq
 */
अटल व्योम i40iw_disable_irq(काष्ठा i40iw_sc_dev *dev,
			      काष्ठा i40iw_msix_vector *msix_vec,
			      व्योम *dev_id)
अणु
	अगर (dev->is_pf)
		i40iw_wr32(dev->hw, I40E_PFINT_DYN_CTLN(msix_vec->idx - 1), 0);
	अन्यथा
		i40iw_wr32(dev->hw, I40E_VFINT_DYN_CTLN1(msix_vec->idx - 1), 0);
	irq_set_affinity_hपूर्णांक(msix_vec->irq, शून्य);
	मुक्त_irq(msix_vec->irq, dev_id);
पूर्ण

/**
 * i40iw_destroy_aeq - destroy aeq
 * @iwdev: iwarp device
 *
 * Issue a destroy aeq request and
 * मुक्त the resources associated with the aeq
 * The function is called during driver unload
 */
अटल व्योम i40iw_destroy_aeq(काष्ठा i40iw_device *iwdev)
अणु
	क्रमागत i40iw_status_code status = I40IW_ERR_NOT_READY;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_aeq *aeq = &iwdev->aeq;

	अगर (!iwdev->msix_shared)
		i40iw_disable_irq(dev, iwdev->iw_msixtbl, (व्योम *)iwdev);
	अगर (iwdev->reset)
		जाओ निकास;

	अगर (!dev->aeq_ops->aeq_destroy(&aeq->sc_aeq, 0, 1))
		status = dev->aeq_ops->aeq_destroy_करोne(&aeq->sc_aeq);
	अगर (status)
		i40iw_pr_err("destroy aeq failed %d\n", status);

निकास:
	i40iw_मुक्त_dma_mem(dev->hw, &aeq->mem);
पूर्ण

/**
 * i40iw_destroy_ceq - destroy ceq
 * @iwdev: iwarp device
 * @iwceq: ceq to be destroyed
 *
 * Issue a destroy ceq request and
 * मुक्त the resources associated with the ceq
 */
अटल व्योम i40iw_destroy_ceq(काष्ठा i40iw_device *iwdev,
			      काष्ठा i40iw_ceq *iwceq)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;

	अगर (iwdev->reset)
		जाओ निकास;

	status = dev->ceq_ops->ceq_destroy(&iwceq->sc_ceq, 0, 1);
	अगर (status) अणु
		i40iw_pr_err("ceq destroy command failed %d\n", status);
		जाओ निकास;
	पूर्ण

	status = dev->ceq_ops->cceq_destroy_करोne(&iwceq->sc_ceq);
	अगर (status)
		i40iw_pr_err("ceq destroy completion failed %d\n", status);
निकास:
	i40iw_मुक्त_dma_mem(dev->hw, &iwceq->mem);
पूर्ण

/**
 * i40iw_dele_ceqs - destroy all ceq's
 * @iwdev: iwarp device
 *
 * Go through all of the device ceq's and क्रम each ceq
 * disable the ceq पूर्णांकerrupt and destroy the ceq
 */
अटल व्योम i40iw_dele_ceqs(काष्ठा i40iw_device *iwdev)
अणु
	u32 i = 0;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_ceq *iwceq = iwdev->ceqlist;
	काष्ठा i40iw_msix_vector *msix_vec = iwdev->iw_msixtbl;

	अगर (iwdev->msix_shared) अणु
		i40iw_disable_irq(dev, msix_vec, (व्योम *)iwdev);
		i40iw_destroy_ceq(iwdev, iwceq);
		iwceq++;
		i++;
	पूर्ण

	क्रम (msix_vec++; i < iwdev->ceqs_count; i++, msix_vec++, iwceq++) अणु
		i40iw_disable_irq(dev, msix_vec, (व्योम *)iwceq);
		i40iw_destroy_ceq(iwdev, iwceq);
	पूर्ण

	iwdev->sc_dev.ceq_valid = false;
पूर्ण

/**
 * i40iw_destroy_ccq - destroy control cq
 * @iwdev: iwarp device
 *
 * Issue destroy ccq request and
 * मुक्त the resources associated with the ccq
 */
अटल व्योम i40iw_destroy_ccq(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_ccq *ccq = &iwdev->ccq;
	क्रमागत i40iw_status_code status = 0;

	अगर (!iwdev->reset)
		status = dev->ccq_ops->ccq_destroy(dev->ccq, 0, true);
	अगर (status)
		i40iw_pr_err("ccq destroy failed %d\n", status);
	i40iw_मुक्त_dma_mem(dev->hw, &ccq->mem_cq);
पूर्ण

/* types of hmc objects */
अटल क्रमागत i40iw_hmc_rsrc_type iw_hmc_obj_types[] = अणु
	I40IW_HMC_IW_QP,
	I40IW_HMC_IW_CQ,
	I40IW_HMC_IW_HTE,
	I40IW_HMC_IW_ARP,
	I40IW_HMC_IW_APBVT_ENTRY,
	I40IW_HMC_IW_MR,
	I40IW_HMC_IW_XF,
	I40IW_HMC_IW_XFFL,
	I40IW_HMC_IW_Q1,
	I40IW_HMC_IW_Q1FL,
	I40IW_HMC_IW_TIMER,
पूर्ण;

/**
 * i40iw_बंद_hmc_objects_type - delete hmc objects of a given type
 * @dev: iwarp device
 * @obj_type: the hmc object type to be deleted
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation
 * @is_pf: true अगर the function is PF otherwise false
 * @reset: true अगर called beक्रमe reset
 */
अटल व्योम i40iw_बंद_hmc_objects_type(काष्ठा i40iw_sc_dev *dev,
					 क्रमागत i40iw_hmc_rsrc_type obj_type,
					 काष्ठा i40iw_hmc_info *hmc_info,
					 bool is_pf,
					 bool reset)
अणु
	काष्ठा i40iw_hmc_del_obj_info info;

	स_रखो(&info, 0, माप(info));
	info.hmc_info = hmc_info;
	info.rsrc_type = obj_type;
	info.count = hmc_info->hmc_obj[obj_type].cnt;
	info.is_pf = is_pf;
	अगर (dev->hmc_ops->del_hmc_object(dev, &info, reset))
		i40iw_pr_err("del obj of type %d failed\n", obj_type);
पूर्ण

/**
 * i40iw_del_hmc_objects - हटाओ all device hmc objects
 * @dev: iwarp device
 * @hmc_info: hmc_info to मुक्त
 * @is_pf: true अगर hmc_info beदीर्घs to PF, not vf nor allocated
 *	   by PF on behalf of VF
 * @reset: true अगर called beक्रमe reset
 */
अटल व्योम i40iw_del_hmc_objects(काष्ठा i40iw_sc_dev *dev,
				  काष्ठा i40iw_hmc_info *hmc_info,
				  bool is_pf,
				  bool reset)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IW_HMC_OBJ_TYPE_NUM; i++)
		i40iw_बंद_hmc_objects_type(dev, iw_hmc_obj_types[i], hmc_info, is_pf, reset);
पूर्ण

/**
 * i40iw_ceq_handler - पूर्णांकerrupt handler क्रम ceq
 * @irq: पूर्णांकerrupt request number
 * @data: ceq poपूर्णांकer
 */
अटल irqवापस_t i40iw_ceq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा i40iw_ceq *iwceq = (काष्ठा i40iw_ceq *)data;

	अगर (iwceq->irq != irq)
		i40iw_pr_err("expected irq = %d received irq = %d\n", iwceq->irq, irq);
	tasklet_schedule(&iwceq->dpc_tasklet);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * i40iw_create_hmc_obj_type - create hmc object of a given type
 * @dev: hardware control device काष्ठाure
 * @info: inक्रमmation क्रम the hmc object to create
 */
अटल क्रमागत i40iw_status_code i40iw_create_hmc_obj_type(काष्ठा i40iw_sc_dev *dev,
							काष्ठा i40iw_hmc_create_obj_info *info)
अणु
	वापस dev->hmc_ops->create_hmc_object(dev, info);
पूर्ण

/**
 * i40iw_create_hmc_objs - create all hmc objects क्रम the device
 * @iwdev: iwarp device
 * @is_pf: true अगर the function is PF otherwise false
 *
 * Create the device hmc objects and allocate hmc pages
 * Return 0 अगर successful, otherwise clean up and वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_create_hmc_objs(काष्ठा i40iw_device *iwdev,
						    bool is_pf)
अणु
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_hmc_create_obj_info info;
	क्रमागत i40iw_status_code status;
	पूर्णांक i;

	स_रखो(&info, 0, माप(info));
	info.hmc_info = dev->hmc_info;
	info.is_pf = is_pf;
	info.entry_type = iwdev->sd_type;
	क्रम (i = 0; i < IW_HMC_OBJ_TYPE_NUM; i++) अणु
		info.rsrc_type = iw_hmc_obj_types[i];
		info.count = dev->hmc_info->hmc_obj[info.rsrc_type].cnt;
		info.add_sd_cnt = 0;
		status = i40iw_create_hmc_obj_type(dev, &info);
		अगर (status) अणु
			i40iw_pr_err("create obj type %d status = %d\n",
				     iw_hmc_obj_types[i], status);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!status)
		वापस (dev->cqp_misc_ops->अटल_hmc_pages_allocated(dev->cqp, 0,
								      dev->hmc_fn_id,
								      true, true));

	जबतक (i) अणु
		i--;
		/* destroy the hmc objects of a given type */
		i40iw_बंद_hmc_objects_type(dev,
					     iw_hmc_obj_types[i],
					     dev->hmc_info,
					     is_pf,
					     false);
	पूर्ण
	वापस status;
पूर्ण

/**
 * i40iw_obj_aligned_mem - get aligned memory from device allocated memory
 * @iwdev: iwarp device
 * @memptr: poपूर्णांकs to the memory addresses
 * @size: size of memory needed
 * @mask: mask क्रम the aligned memory
 *
 * Get aligned memory of the requested size and
 * update the memptr to poपूर्णांक to the new aligned memory
 * Return 0 अगर successful, otherwise वापस no memory error
 */
क्रमागत i40iw_status_code i40iw_obj_aligned_mem(काष्ठा i40iw_device *iwdev,
					     काष्ठा i40iw_dma_mem *memptr,
					     u32 size,
					     u32 mask)
अणु
	अचिन्हित दीर्घ va, newva;
	अचिन्हित दीर्घ extra;

	va = (अचिन्हित दीर्घ)iwdev->obj_next.va;
	newva = va;
	अगर (mask)
		newva = ALIGN(va, (mask + 1));
	extra = newva - va;
	memptr->va = (u8 *)va + extra;
	memptr->pa = iwdev->obj_next.pa + extra;
	memptr->size = size;
	अगर ((memptr->va + size) > (iwdev->obj_mem.va + iwdev->obj_mem.size))
		वापस I40IW_ERR_NO_MEMORY;

	iwdev->obj_next.va = memptr->va + size;
	iwdev->obj_next.pa = memptr->pa + size;
	वापस 0;
पूर्ण

/**
 * i40iw_create_cqp - create control qp
 * @iwdev: iwarp device
 *
 * Return 0, अगर the cqp and all the resources associated with it
 * are successfully created, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_create_cqp(काष्ठा i40iw_device *iwdev)
अणु
	क्रमागत i40iw_status_code status;
	u32 sqsize = I40IW_CQP_SW_SQSIZE_2048;
	काष्ठा i40iw_dma_mem mem;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_cqp_init_info cqp_init_info;
	काष्ठा i40iw_cqp *cqp = &iwdev->cqp;
	u16 maj_err, min_err;
	पूर्णांक i;

	cqp->cqp_requests = kसुस्मृति(sqsize, माप(*cqp->cqp_requests), GFP_KERNEL);
	अगर (!cqp->cqp_requests)
		वापस I40IW_ERR_NO_MEMORY;
	cqp->scratch_array = kसुस्मृति(sqsize, माप(*cqp->scratch_array), GFP_KERNEL);
	अगर (!cqp->scratch_array) अणु
		kमुक्त(cqp->cqp_requests);
		वापस I40IW_ERR_NO_MEMORY;
	पूर्ण
	dev->cqp = &cqp->sc_cqp;
	dev->cqp->dev = dev;
	स_रखो(&cqp_init_info, 0, माप(cqp_init_info));
	status = i40iw_allocate_dma_mem(dev->hw, &cqp->sq,
					(माप(काष्ठा i40iw_cqp_sq_wqe) * sqsize),
					I40IW_CQP_ALIGNMENT);
	अगर (status)
		जाओ निकास;
	status = i40iw_obj_aligned_mem(iwdev, &mem, माप(काष्ठा i40iw_cqp_ctx),
				       I40IW_HOST_CTX_ALIGNMENT_MASK);
	अगर (status)
		जाओ निकास;
	dev->cqp->host_ctx_pa = mem.pa;
	dev->cqp->host_ctx = mem.va;
	/* populate the cqp init info */
	cqp_init_info.dev = dev;
	cqp_init_info.sq_size = sqsize;
	cqp_init_info.sq = cqp->sq.va;
	cqp_init_info.sq_pa = cqp->sq.pa;
	cqp_init_info.host_ctx_pa = mem.pa;
	cqp_init_info.host_ctx = mem.va;
	cqp_init_info.hmc_profile = iwdev->resource_profile;
	cqp_init_info.enabled_vf_count = iwdev->max_rdma_vfs;
	cqp_init_info.scratch_array = cqp->scratch_array;
	status = dev->cqp_ops->cqp_init(dev->cqp, &cqp_init_info);
	अगर (status) अणु
		i40iw_pr_err("cqp init status %d\n", status);
		जाओ निकास;
	पूर्ण
	status = dev->cqp_ops->cqp_create(dev->cqp, &maj_err, &min_err);
	अगर (status) अणु
		i40iw_pr_err("cqp create status %d maj_err %d min_err %d\n",
			     status, maj_err, min_err);
		जाओ निकास;
	पूर्ण
	spin_lock_init(&cqp->req_lock);
	INIT_LIST_HEAD(&cqp->cqp_avail_reqs);
	INIT_LIST_HEAD(&cqp->cqp_pending_reqs);
	/* init the रुकोq of the cqp_requests and add them to the list */
	क्रम (i = 0; i < sqsize; i++) अणु
		init_रुकोqueue_head(&cqp->cqp_requests[i].रुकोq);
		list_add_tail(&cqp->cqp_requests[i].list, &cqp->cqp_avail_reqs);
	पूर्ण
	वापस 0;
निकास:
	/* clean up the created resources */
	i40iw_destroy_cqp(iwdev, false);
	वापस status;
पूर्ण

/**
 * i40iw_create_ccq - create control cq
 * @iwdev: iwarp device
 *
 * Return 0, अगर the ccq and the resources associated with it
 * are successfully created, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_create_ccq(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_dma_mem mem;
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_ccq_init_info info;
	काष्ठा i40iw_ccq *ccq = &iwdev->ccq;

	स_रखो(&info, 0, माप(info));
	dev->ccq = &ccq->sc_cq;
	dev->ccq->dev = dev;
	info.dev = dev;
	ccq->shaकरोw_area.size = माप(काष्ठा i40iw_cq_shaकरोw_area);
	ccq->mem_cq.size = माप(काष्ठा i40iw_cqe) * IW_CCQ_SIZE;
	status = i40iw_allocate_dma_mem(dev->hw, &ccq->mem_cq,
					ccq->mem_cq.size, I40IW_CQ0_ALIGNMENT);
	अगर (status)
		जाओ निकास;
	status = i40iw_obj_aligned_mem(iwdev, &mem, ccq->shaकरोw_area.size,
				       I40IW_SHADOWAREA_MASK);
	अगर (status)
		जाओ निकास;
	ccq->sc_cq.back_cq = (व्योम *)ccq;
	/* populate the ccq init info */
	info.cq_base = ccq->mem_cq.va;
	info.cq_pa = ccq->mem_cq.pa;
	info.num_elem = IW_CCQ_SIZE;
	info.shaकरोw_area = mem.va;
	info.shaकरोw_area_pa = mem.pa;
	info.ceqe_mask = false;
	info.ceq_id_valid = true;
	info.shaकरोw_पढ़ो_threshold = 16;
	status = dev->ccq_ops->ccq_init(dev->ccq, &info);
	अगर (!status)
		status = dev->ccq_ops->ccq_create(dev->ccq, 0, true, true);
निकास:
	अगर (status)
		i40iw_मुक्त_dma_mem(dev->hw, &ccq->mem_cq);
	वापस status;
पूर्ण

/**
 * i40iw_configure_ceq_vector - set up the msix पूर्णांकerrupt vector क्रम ceq
 * @iwdev: iwarp device
 * @msix_vec: पूर्णांकerrupt vector inक्रमmation
 * @iwceq: ceq associated with the vector
 * @ceq_id: the id number of the iwceq
 *
 * Allocate पूर्णांकerrupt resources and enable irq handling
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_configure_ceq_vector(काष्ठा i40iw_device *iwdev,
							 काष्ठा i40iw_ceq *iwceq,
							 u32 ceq_id,
							 काष्ठा i40iw_msix_vector *msix_vec)
अणु
	क्रमागत i40iw_status_code status;

	अगर (iwdev->msix_shared && !ceq_id) अणु
		tasklet_setup(&iwdev->dpc_tasklet, i40iw_dpc);
		status = request_irq(msix_vec->irq, i40iw_irq_handler, 0, "AEQCEQ", iwdev);
	पूर्ण अन्यथा अणु
		tasklet_setup(&iwceq->dpc_tasklet, i40iw_ceq_dpc);
		status = request_irq(msix_vec->irq, i40iw_ceq_handler, 0, "CEQ", iwceq);
	पूर्ण

	cpumask_clear(&msix_vec->mask);
	cpumask_set_cpu(msix_vec->cpu_affinity, &msix_vec->mask);
	irq_set_affinity_hपूर्णांक(msix_vec->irq, &msix_vec->mask);

	अगर (status) अणु
		i40iw_pr_err("ceq irq config fail\n");
		वापस I40IW_ERR_CONFIG;
	पूर्ण
	msix_vec->ceq_id = ceq_id;

	वापस 0;
पूर्ण

/**
 * i40iw_create_ceq - create completion event queue
 * @iwdev: iwarp device
 * @iwceq: poपूर्णांकer to the ceq resources to be created
 * @ceq_id: the id number of the iwceq
 *
 * Return 0, अगर the ceq and the resources associated with it
 * are successfully created, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_create_ceq(काष्ठा i40iw_device *iwdev,
					       काष्ठा i40iw_ceq *iwceq,
					       u32 ceq_id)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_ceq_init_info info;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	u64 scratch;

	स_रखो(&info, 0, माप(info));
	info.ceq_id = ceq_id;
	iwceq->iwdev = iwdev;
	iwceq->mem.size = माप(काष्ठा i40iw_ceqe) *
		iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_CQ].cnt;
	status = i40iw_allocate_dma_mem(dev->hw, &iwceq->mem, iwceq->mem.size,
					I40IW_CEQ_ALIGNMENT);
	अगर (status)
		जाओ निकास;
	info.ceq_id = ceq_id;
	info.ceqe_base = iwceq->mem.va;
	info.ceqe_pa = iwceq->mem.pa;

	info.elem_cnt = iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_CQ].cnt;
	iwceq->sc_ceq.ceq_id = ceq_id;
	info.dev = dev;
	scratch = (uपूर्णांकptr_t)&iwdev->cqp.sc_cqp;
	status = dev->ceq_ops->ceq_init(&iwceq->sc_ceq, &info);
	अगर (!status)
		status = dev->ceq_ops->cceq_create(&iwceq->sc_ceq, scratch);

निकास:
	अगर (status)
		i40iw_मुक्त_dma_mem(dev->hw, &iwceq->mem);
	वापस status;
पूर्ण

व्योम i40iw_request_reset(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40e_info *ldev = iwdev->ldev;

	ldev->ops->request_reset(ldev, iwdev->client, 1);
पूर्ण

/**
 * i40iw_setup_ceqs - manage the device ceq's and their पूर्णांकerrupt resources
 * @iwdev: iwarp device
 * @ldev: i40e lan device
 *
 * Allocate a list क्रम all device completion event queues
 * Create the ceq's and configure their msix पूर्णांकerrupt vectors
 * Return 0, अगर at least one ceq is successfully set up, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_setup_ceqs(काष्ठा i40iw_device *iwdev,
					       काष्ठा i40e_info *ldev)
अणु
	u32 i;
	u32 ceq_id;
	काष्ठा i40iw_ceq *iwceq;
	काष्ठा i40iw_msix_vector *msix_vec;
	क्रमागत i40iw_status_code status = 0;
	u32 num_ceqs;

	अगर (ldev && ldev->ops && ldev->ops->setup_qvlist) अणु
		status = ldev->ops->setup_qvlist(ldev, &i40iw_client,
						 iwdev->iw_qvlist);
		अगर (status)
			जाओ निकास;
	पूर्ण अन्यथा अणु
		status = I40IW_ERR_BAD_PTR;
		जाओ निकास;
	पूर्ण

	num_ceqs = min(iwdev->msix_count, iwdev->sc_dev.hmc_fpm_misc.max_ceqs);
	iwdev->ceqlist = kसुस्मृति(num_ceqs, माप(*iwdev->ceqlist), GFP_KERNEL);
	अगर (!iwdev->ceqlist) अणु
		status = I40IW_ERR_NO_MEMORY;
		जाओ निकास;
	पूर्ण
	i = (iwdev->msix_shared) ? 0 : 1;
	क्रम (ceq_id = 0; i < num_ceqs; i++, ceq_id++) अणु
		iwceq = &iwdev->ceqlist[ceq_id];
		status = i40iw_create_ceq(iwdev, iwceq, ceq_id);
		अगर (status) अणु
			i40iw_pr_err("create ceq status = %d\n", status);
			अवरोध;
		पूर्ण

		msix_vec = &iwdev->iw_msixtbl[i];
		iwceq->irq = msix_vec->irq;
		iwceq->msix_idx = msix_vec->idx;
		status = i40iw_configure_ceq_vector(iwdev, iwceq, ceq_id, msix_vec);
		अगर (status) अणु
			i40iw_destroy_ceq(iwdev, iwceq);
			अवरोध;
		पूर्ण
		i40iw_enable_पूर्णांकr(&iwdev->sc_dev, msix_vec->idx);
		iwdev->ceqs_count++;
	पूर्ण
निकास:
	अगर (status && !iwdev->ceqs_count) अणु
		kमुक्त(iwdev->ceqlist);
		iwdev->ceqlist = शून्य;
		वापस status;
	पूर्ण अन्यथा अणु
		iwdev->sc_dev.ceq_valid = true;
		वापस 0;
	पूर्ण

पूर्ण

/**
 * i40iw_configure_aeq_vector - set up the msix vector क्रम aeq
 * @iwdev: iwarp device
 *
 * Allocate पूर्णांकerrupt resources and enable irq handling
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_configure_aeq_vector(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_msix_vector *msix_vec = iwdev->iw_msixtbl;
	u32 ret = 0;

	अगर (!iwdev->msix_shared) अणु
		tasklet_setup(&iwdev->dpc_tasklet, i40iw_dpc);
		ret = request_irq(msix_vec->irq, i40iw_irq_handler, 0, "i40iw", iwdev);
	पूर्ण
	अगर (ret) अणु
		i40iw_pr_err("aeq irq config fail\n");
		वापस I40IW_ERR_CONFIG;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40iw_create_aeq - create async event queue
 * @iwdev: iwarp device
 *
 * Return 0, अगर the aeq and the resources associated with it
 * are successfully created, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_create_aeq(काष्ठा i40iw_device *iwdev)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_aeq_init_info info;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_aeq *aeq = &iwdev->aeq;
	u64 scratch = 0;
	u32 aeq_size;

	aeq_size = 2 * iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_QP].cnt +
		iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_CQ].cnt;
	स_रखो(&info, 0, माप(info));
	aeq->mem.size = माप(काष्ठा i40iw_sc_aeqe) * aeq_size;
	status = i40iw_allocate_dma_mem(dev->hw, &aeq->mem, aeq->mem.size,
					I40IW_AEQ_ALIGNMENT);
	अगर (status)
		जाओ निकास;

	info.aeqe_base = aeq->mem.va;
	info.aeq_elem_pa = aeq->mem.pa;
	info.elem_cnt = aeq_size;
	info.dev = dev;
	status = dev->aeq_ops->aeq_init(&aeq->sc_aeq, &info);
	अगर (status)
		जाओ निकास;
	status = dev->aeq_ops->aeq_create(&aeq->sc_aeq, scratch, 1);
	अगर (!status)
		status = dev->aeq_ops->aeq_create_करोne(&aeq->sc_aeq);
निकास:
	अगर (status)
		i40iw_मुक्त_dma_mem(dev->hw, &aeq->mem);
	वापस status;
पूर्ण

/**
 * i40iw_setup_aeq - set up the device aeq
 * @iwdev: iwarp device
 *
 * Create the aeq and configure its msix पूर्णांकerrupt vector
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_setup_aeq(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	क्रमागत i40iw_status_code status;

	status = i40iw_create_aeq(iwdev);
	अगर (status)
		वापस status;

	status = i40iw_configure_aeq_vector(iwdev);
	अगर (status) अणु
		i40iw_destroy_aeq(iwdev);
		वापस status;
	पूर्ण

	अगर (!iwdev->msix_shared)
		i40iw_enable_पूर्णांकr(dev, iwdev->iw_msixtbl[0].idx);
	वापस 0;
पूर्ण

/**
 * i40iw_initialize_ilq - create iwarp local queue क्रम cm
 * @iwdev: iwarp device
 *
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_initialize_ilq(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_puda_rsrc_info info;
	क्रमागत i40iw_status_code status;

	स_रखो(&info, 0, माप(info));
	info.type = I40IW_PUDA_RSRC_TYPE_ILQ;
	info.cq_id = 1;
	info.qp_id = 0;
	info.count = 1;
	info.pd_id = 1;
	info.sq_size = 8192;
	info.rq_size = 8192;
	info.buf_size = 1024;
	info.tx_buf_cnt = 16384;
	info.receive = i40iw_receive_ilq;
	info.xmit_complete = i40iw_मुक्त_sqbuf;
	status = i40iw_puda_create_rsrc(&iwdev->vsi, &info);
	अगर (status)
		i40iw_pr_err("ilq create fail\n");
	वापस status;
पूर्ण

/**
 * i40iw_initialize_ieq - create iwarp exception queue
 * @iwdev: iwarp device
 *
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_initialize_ieq(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_puda_rsrc_info info;
	क्रमागत i40iw_status_code status;

	स_रखो(&info, 0, माप(info));
	info.type = I40IW_PUDA_RSRC_TYPE_IEQ;
	info.cq_id = 2;
	info.qp_id = iwdev->vsi.exception_lan_queue;
	info.count = 1;
	info.pd_id = 2;
	info.sq_size = 8192;
	info.rq_size = 8192;
	info.buf_size = iwdev->vsi.mtu + VLAN_ETH_HLEN;
	info.tx_buf_cnt = 4096;
	status = i40iw_puda_create_rsrc(&iwdev->vsi, &info);
	अगर (status)
		i40iw_pr_err("ieq create fail\n");
	वापस status;
पूर्ण

/**
 * i40iw_reinitialize_ieq - destroy and re-create ieq
 * @dev: iwarp device
 */
व्योम i40iw_reinitialize_ieq(काष्ठा i40iw_sc_dev *dev)
अणु
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;

	i40iw_puda_dele_resources(&iwdev->vsi, I40IW_PUDA_RSRC_TYPE_IEQ, false);
	अगर (i40iw_initialize_ieq(iwdev)) अणु
		iwdev->reset = true;
		i40iw_request_reset(iwdev);
	पूर्ण
पूर्ण

/**
 * i40iw_hmc_setup - create hmc objects क्रम the device
 * @iwdev: iwarp device
 *
 * Set up the device निजी memory space क्रम the number and size of
 * the hmc objects and create the objects
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_hmc_setup(काष्ठा i40iw_device *iwdev)
अणु
	क्रमागत i40iw_status_code status;

	iwdev->sd_type = I40IW_SD_TYPE_सूचीECT;
	status = i40iw_config_fpm_values(&iwdev->sc_dev, IW_CFG_FPM_QP_COUNT);
	अगर (status)
		जाओ निकास;
	status = i40iw_create_hmc_objs(iwdev, true);
	अगर (status)
		जाओ निकास;
	iwdev->init_state = HMC_OBJS_CREATED;
निकास:
	वापस status;
पूर्ण

/**
 * i40iw_del_init_mem - deallocate memory resources
 * @iwdev: iwarp device
 */
अटल व्योम i40iw_del_init_mem(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;

	i40iw_मुक्त_dma_mem(&iwdev->hw, &iwdev->obj_mem);
	kमुक्त(dev->hmc_info->sd_table.sd_entry);
	dev->hmc_info->sd_table.sd_entry = शून्य;
	kमुक्त(iwdev->mem_resources);
	iwdev->mem_resources = शून्य;
	kमुक्त(iwdev->ceqlist);
	iwdev->ceqlist = शून्य;
	kमुक्त(iwdev->iw_msixtbl);
	iwdev->iw_msixtbl = शून्य;
	kमुक्त(iwdev->hmc_info_mem);
	iwdev->hmc_info_mem = शून्य;
पूर्ण

/**
 * i40iw_del_macip_entry - हटाओ a mac ip address entry from the hw table
 * @iwdev: iwarp device
 * @idx: the index of the mac ip address to delete
 */
अटल व्योम i40iw_del_macip_entry(काष्ठा i40iw_device *iwdev, u8 idx)
अणु
	काष्ठा i40iw_cqp *iwcqp = &iwdev->cqp;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	क्रमागत i40iw_status_code status = 0;

	cqp_request = i40iw_get_cqp_request(iwcqp, true);
	अगर (!cqp_request) अणु
		i40iw_pr_err("cqp_request memory failed\n");
		वापस;
	पूर्ण
	cqp_info = &cqp_request->info;
	cqp_info->cqp_cmd = OP_DELETE_LOCAL_MAC_IPADDR_ENTRY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.del_local_mac_ipaddr_entry.cqp = &iwcqp->sc_cqp;
	cqp_info->in.u.del_local_mac_ipaddr_entry.scratch = (uपूर्णांकptr_t)cqp_request;
	cqp_info->in.u.del_local_mac_ipaddr_entry.entry_idx = idx;
	cqp_info->in.u.del_local_mac_ipaddr_entry.ignore_ref_count = 0;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP Del MAC Ip entry fail");
पूर्ण

/**
 * i40iw_add_mac_ipaddr_entry - add a mac ip address entry to the hw table
 * @iwdev: iwarp device
 * @mac_addr: poपूर्णांकer to mac address
 * @idx: the index of the mac ip address to add
 */
अटल क्रमागत i40iw_status_code i40iw_add_mac_ipaddr_entry(काष्ठा i40iw_device *iwdev,
							 u8 *mac_addr,
							 u8 idx)
अणु
	काष्ठा i40iw_local_mac_ipaddr_entry_info *info;
	काष्ठा i40iw_cqp *iwcqp = &iwdev->cqp;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	क्रमागत i40iw_status_code status = 0;

	cqp_request = i40iw_get_cqp_request(iwcqp, true);
	अगर (!cqp_request) अणु
		i40iw_pr_err("cqp_request memory failed\n");
		वापस I40IW_ERR_NO_MEMORY;
	पूर्ण

	cqp_info = &cqp_request->info;

	cqp_info->post_sq = 1;
	info = &cqp_info->in.u.add_local_mac_ipaddr_entry.info;
	ether_addr_copy(info->mac_addr, mac_addr);
	info->entry_idx = idx;
	cqp_info->in.u.add_local_mac_ipaddr_entry.scratch = (uपूर्णांकptr_t)cqp_request;
	cqp_info->cqp_cmd = OP_ADD_LOCAL_MAC_IPADDR_ENTRY;
	cqp_info->in.u.add_local_mac_ipaddr_entry.cqp = &iwcqp->sc_cqp;
	cqp_info->in.u.add_local_mac_ipaddr_entry.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP Add MAC Ip entry fail");
	वापस status;
पूर्ण

/**
 * i40iw_alloc_local_mac_ipaddr_entry - allocate a mac ip address entry
 * @iwdev: iwarp device
 * @mac_ip_tbl_idx: the index of the new mac ip address
 *
 * Allocate a mac ip address entry and update the mac_ip_tbl_idx
 * to hold the index of the newly created mac ip address
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_alloc_local_mac_ipaddr_entry(काष्ठा i40iw_device *iwdev,
								 u16 *mac_ip_tbl_idx)
अणु
	काष्ठा i40iw_cqp *iwcqp = &iwdev->cqp;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	क्रमागत i40iw_status_code status = 0;

	cqp_request = i40iw_get_cqp_request(iwcqp, true);
	अगर (!cqp_request) अणु
		i40iw_pr_err("cqp_request memory failed\n");
		वापस I40IW_ERR_NO_MEMORY;
	पूर्ण

	/* increment refcount, because we need the cqp request ret value */
	atomic_inc(&cqp_request->refcount);

	cqp_info = &cqp_request->info;
	cqp_info->cqp_cmd = OP_ALLOC_LOCAL_MAC_IPADDR_ENTRY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.alloc_local_mac_ipaddr_entry.cqp = &iwcqp->sc_cqp;
	cqp_info->in.u.alloc_local_mac_ipaddr_entry.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (!status)
		*mac_ip_tbl_idx = cqp_request->compl_info.op_ret_val;
	अन्यथा
		i40iw_pr_err("CQP-OP Alloc MAC Ip entry fail");
	/* decrement refcount and मुक्त the cqp request, अगर no दीर्घer used */
	i40iw_put_cqp_request(iwcqp, cqp_request);
	वापस status;
पूर्ण

/**
 * i40iw_alloc_set_mac_ipaddr - set up a mac ip address table entry
 * @iwdev: iwarp device
 * @macaddr: poपूर्णांकer to mac address
 *
 * Allocate a mac ip address entry and add it to the hw table
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_alloc_set_mac_ipaddr(काष्ठा i40iw_device *iwdev,
							 u8 *macaddr)
अणु
	क्रमागत i40iw_status_code status;

	status = i40iw_alloc_local_mac_ipaddr_entry(iwdev, &iwdev->mac_ip_table_idx);
	अगर (!status) अणु
		status = i40iw_add_mac_ipaddr_entry(iwdev, macaddr,
						    (u8)iwdev->mac_ip_table_idx);
		अगर (status)
			i40iw_del_macip_entry(iwdev, (u8)iwdev->mac_ip_table_idx);
	पूर्ण
	वापस status;
पूर्ण

/**
 * i40iw_add_ipv6_addr - add ipv6 address to the hw arp table
 * @iwdev: iwarp device
 */
अटल व्योम i40iw_add_ipv6_addr(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा net_device *ip_dev;
	काष्ठा inet6_dev *idev;
	काष्ठा inet6_अगरaddr *अगरp, *पंचांगp;
	u32 local_ipaddr6[4];

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, ip_dev) अणु
		अगर ((((rdma_vlan_dev_vlan_id(ip_dev) < 0xFFFF) &&
		      (rdma_vlan_dev_real_dev(ip_dev) == iwdev->netdev)) ||
		     (ip_dev == iwdev->netdev)) && (ip_dev->flags & IFF_UP)) अणु
			idev = __in6_dev_get(ip_dev);
			अगर (!idev) अणु
				i40iw_pr_err("ipv6 inet device not found\n");
				अवरोध;
			पूर्ण
			list_क्रम_each_entry_safe(अगरp, पंचांगp, &idev->addr_list, अगर_list) अणु
				i40iw_pr_info("IP=%pI6, vlan_id=%d, MAC=%pM\n", &अगरp->addr,
					      rdma_vlan_dev_vlan_id(ip_dev), ip_dev->dev_addr);
				i40iw_copy_ip_ntohl(local_ipaddr6,
						    अगरp->addr.in6_u.u6_addr32);
				i40iw_manage_arp_cache(iwdev,
						       ip_dev->dev_addr,
						       local_ipaddr6,
						       false,
						       I40IW_ARP_ADD);
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * i40iw_add_ipv4_addr - add ipv4 address to the hw arp table
 * @iwdev: iwarp device
 */
अटल व्योम i40iw_add_ipv4_addr(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा in_device *idev;
	u32 ip_addr;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev) अणु
		अगर ((((rdma_vlan_dev_vlan_id(dev) < 0xFFFF) &&
		      (rdma_vlan_dev_real_dev(dev) == iwdev->netdev)) ||
		    (dev == iwdev->netdev)) && (READ_ONCE(dev->flags) & IFF_UP)) अणु
			स्थिर काष्ठा in_अगरaddr *अगरa;

			idev = __in_dev_get_rcu(dev);
			अगर (!idev)
				जारी;
			in_dev_क्रम_each_अगरa_rcu(अगरa, idev) अणु
				i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_CM,
					    "IP=%pI4, vlan_id=%d, MAC=%pM\n", &अगरa->अगरa_address,
					     rdma_vlan_dev_vlan_id(dev), dev->dev_addr);

				ip_addr = ntohl(अगरa->अगरa_address);
				i40iw_manage_arp_cache(iwdev,
						       dev->dev_addr,
						       &ip_addr,
						       true,
						       I40IW_ARP_ADD);
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * i40iw_add_mac_ip - add mac and ip addresses
 * @iwdev: iwarp device
 *
 * Create and add a mac ip address entry to the hw table and
 * ipv4/ipv6 addresses to the arp cache
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_add_mac_ip(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा net_device *netdev = iwdev->netdev;
	क्रमागत i40iw_status_code status;

	status = i40iw_alloc_set_mac_ipaddr(iwdev, (u8 *)netdev->dev_addr);
	अगर (status)
		वापस status;
	i40iw_add_ipv4_addr(iwdev);
	i40iw_add_ipv6_addr(iwdev);
	वापस 0;
पूर्ण

/**
 * i40iw_रुको_pe_पढ़ोy - Check अगर firmware is पढ़ोy
 * @hw: provides access to रेजिस्टरs
 */
अटल व्योम i40iw_रुको_pe_पढ़ोy(काष्ठा i40iw_hw *hw)
अणु
	u32 statusfw;
	u32 statuscpu0;
	u32 statuscpu1;
	u32 statuscpu2;
	u32 retrycount = 0;

	करो अणु
		statusfw = i40iw_rd32(hw, I40E_GLPE_FWLDSTATUS);
		i40iw_pr_info("[%04d] fm load status[x%04X]\n", __LINE__, statusfw);
		statuscpu0 = i40iw_rd32(hw, I40E_GLPE_CPUSTATUS0);
		i40iw_pr_info("[%04d] CSR_CQP status[x%04X]\n", __LINE__, statuscpu0);
		statuscpu1 = i40iw_rd32(hw, I40E_GLPE_CPUSTATUS1);
		i40iw_pr_info("[%04d] I40E_GLPE_CPUSTATUS1 status[x%04X]\n",
			      __LINE__, statuscpu1);
		statuscpu2 = i40iw_rd32(hw, I40E_GLPE_CPUSTATUS2);
		i40iw_pr_info("[%04d] I40E_GLPE_CPUSTATUS2 status[x%04X]\n",
			      __LINE__, statuscpu2);
		अगर ((statuscpu0 == 0x80) && (statuscpu1 == 0x80) && (statuscpu2 == 0x80))
			अवरोध;	/* SUCCESS */
		msleep(1000);
		retrycount++;
	पूर्ण जबतक (retrycount < 14);
	i40iw_wr32(hw, 0xb4040, 0x4C104C5);
पूर्ण

/**
 * i40iw_initialize_dev - initialize device
 * @iwdev: iwarp device
 * @ldev: lan device inक्रमmation
 *
 * Allocate memory क्रम the hmc objects and initialize iwdev
 * Return 0 अगर successful, otherwise clean up the resources
 * and वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_initialize_dev(काष्ठा i40iw_device *iwdev,
						   काष्ठा i40e_info *ldev)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_device_init_info info;
	काष्ठा i40iw_vsi_init_info vsi_info;
	काष्ठा i40iw_dma_mem mem;
	काष्ठा i40iw_l2params l2params;
	u32 size;
	काष्ठा i40iw_vsi_stats_info stats_info;
	u16 last_qset = I40IW_NO_QSET;
	u16 qset;
	u32 i;

	स_रखो(&l2params, 0, माप(l2params));
	स_रखो(&info, 0, माप(info));
	size = माप(काष्ठा i40iw_hmc_pble_rsrc) + माप(काष्ठा i40iw_hmc_info) +
				(माप(काष्ठा i40iw_hmc_obj_info) * I40IW_HMC_IW_MAX);
	iwdev->hmc_info_mem = kzalloc(size, GFP_KERNEL);
	अगर (!iwdev->hmc_info_mem)
		वापस I40IW_ERR_NO_MEMORY;

	iwdev->pble_rsrc = (काष्ठा i40iw_hmc_pble_rsrc *)iwdev->hmc_info_mem;
	dev->hmc_info = &iwdev->hw.hmc;
	dev->hmc_info->hmc_obj = (काष्ठा i40iw_hmc_obj_info *)(iwdev->pble_rsrc + 1);
	status = i40iw_obj_aligned_mem(iwdev, &mem, I40IW_QUERY_FPM_BUF_SIZE,
				       I40IW_FPM_QUERY_BUF_ALIGNMENT_MASK);
	अगर (status)
		जाओ error;
	info.fpm_query_buf_pa = mem.pa;
	info.fpm_query_buf = mem.va;
	status = i40iw_obj_aligned_mem(iwdev, &mem, I40IW_COMMIT_FPM_BUF_SIZE,
				       I40IW_FPM_COMMIT_BUF_ALIGNMENT_MASK);
	अगर (status)
		जाओ error;
	info.fpm_commit_buf_pa = mem.pa;
	info.fpm_commit_buf = mem.va;
	info.hmc_fn_id = ldev->fid;
	info.is_pf = (ldev->ftype) ? false : true;
	info.bar0 = ldev->hw_addr;
	info.hw = &iwdev->hw;
	info.debug_mask = debug;
	l2params.mtu =
		(ldev->params.mtu) ? ldev->params.mtu : I40IW_DEFAULT_MTU;
	क्रम (i = 0; i < I40E_CLIENT_MAX_USER_PRIORITY; i++) अणु
		qset = ldev->params.qos.prio_qos[i].qs_handle;
		l2params.qs_handle_list[i] = qset;
		अगर (last_qset == I40IW_NO_QSET)
			last_qset = qset;
		अन्यथा अगर ((qset != last_qset) && (qset != I40IW_NO_QSET))
			iwdev->dcb = true;
	पूर्ण
	i40iw_pr_info("DCB is set/clear = %d\n", iwdev->dcb);
	info.vchnl_send = i40iw_virtchnl_send;
	status = i40iw_device_init(&iwdev->sc_dev, &info);

	अगर (status)
		जाओ error;
	स_रखो(&vsi_info, 0, माप(vsi_info));
	vsi_info.dev = &iwdev->sc_dev;
	vsi_info.back_vsi = (व्योम *)iwdev;
	vsi_info.params = &l2params;
	vsi_info.exception_lan_queue = 1;
	i40iw_sc_vsi_init(&iwdev->vsi, &vsi_info);

	अगर (dev->is_pf) अणु
		स_रखो(&stats_info, 0, माप(stats_info));
		stats_info.fcn_id = ldev->fid;
		stats_info.pestat = kzalloc(माप(*stats_info.pestat), GFP_KERNEL);
		अगर (!stats_info.pestat) अणु
			status = I40IW_ERR_NO_MEMORY;
			जाओ error;
		पूर्ण
		stats_info.stats_initialize = true;
		अगर (stats_info.pestat)
			i40iw_vsi_stats_init(&iwdev->vsi, &stats_info);
	पूर्ण
	वापस status;
error:
	kमुक्त(iwdev->hmc_info_mem);
	iwdev->hmc_info_mem = शून्य;
	वापस status;
पूर्ण

/**
 * i40iw_रेजिस्टर_notअगरiers - रेजिस्टर tcp ip notअगरiers
 */
अटल व्योम i40iw_रेजिस्टर_notअगरiers(व्योम)
अणु
	रेजिस्टर_inetaddr_notअगरier(&i40iw_inetaddr_notअगरier);
	रेजिस्टर_inet6addr_notअगरier(&i40iw_inetaddr6_notअगरier);
	रेजिस्टर_netevent_notअगरier(&i40iw_net_notअगरier);
	रेजिस्टर_netdevice_notअगरier(&i40iw_netdevice_notअगरier);
पूर्ण

/**
 * i40iw_unरेजिस्टर_notअगरiers - unरेजिस्टर tcp ip notअगरiers
 */

अटल व्योम i40iw_unरेजिस्टर_notअगरiers(व्योम)
अणु
	unरेजिस्टर_netevent_notअगरier(&i40iw_net_notअगरier);
	unरेजिस्टर_inetaddr_notअगरier(&i40iw_inetaddr_notअगरier);
	unरेजिस्टर_inet6addr_notअगरier(&i40iw_inetaddr6_notअगरier);
	unरेजिस्टर_netdevice_notअगरier(&i40iw_netdevice_notअगरier);
पूर्ण

/**
 * i40iw_save_msix_info - copy msix vector inक्रमmation to iwarp device
 * @iwdev: iwarp device
 * @ldev: lan device inक्रमmation
 *
 * Allocate iwdev msix table and copy the ldev msix info to the table
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_save_msix_info(काष्ठा i40iw_device *iwdev,
						   काष्ठा i40e_info *ldev)
अणु
	काष्ठा i40e_qvlist_info *iw_qvlist;
	काष्ठा i40e_qv_info *iw_qvinfo;
	u32 ceq_idx;
	u32 i;
	u32 size;

	अगर (!ldev->msix_count) अणु
		i40iw_pr_err("No MSI-X vectors\n");
		वापस I40IW_ERR_CONFIG;
	पूर्ण

	iwdev->msix_count = ldev->msix_count;

	size = माप(काष्ठा i40iw_msix_vector) * iwdev->msix_count;
	size += माप(काष्ठा i40e_qvlist_info);
	size +=  माप(काष्ठा i40e_qv_info) * iwdev->msix_count - 1;
	iwdev->iw_msixtbl = kzalloc(size, GFP_KERNEL);

	अगर (!iwdev->iw_msixtbl)
		वापस I40IW_ERR_NO_MEMORY;
	iwdev->iw_qvlist = (काष्ठा i40e_qvlist_info *)(&iwdev->iw_msixtbl[iwdev->msix_count]);
	iw_qvlist = iwdev->iw_qvlist;
	iw_qvinfo = iw_qvlist->qv_info;
	iw_qvlist->num_vectors = iwdev->msix_count;
	अगर (iwdev->msix_count <= num_online_cpus())
		iwdev->msix_shared = true;
	क्रम (i = 0, ceq_idx = 0; i < iwdev->msix_count; i++, iw_qvinfo++) अणु
		iwdev->iw_msixtbl[i].idx = ldev->msix_entries[i].entry;
		iwdev->iw_msixtbl[i].irq = ldev->msix_entries[i].vector;
		iwdev->iw_msixtbl[i].cpu_affinity = ceq_idx;
		अगर (i == 0) अणु
			iw_qvinfo->aeq_idx = 0;
			अगर (iwdev->msix_shared)
				iw_qvinfo->ceq_idx = ceq_idx++;
			अन्यथा
				iw_qvinfo->ceq_idx = I40E_QUEUE_INVALID_IDX;
		पूर्ण अन्यथा अणु
			iw_qvinfo->aeq_idx = I40E_QUEUE_INVALID_IDX;
			iw_qvinfo->ceq_idx = ceq_idx++;
		पूर्ण
		iw_qvinfo->itr_idx = 3;
		iw_qvinfo->v_idx = iwdev->iw_msixtbl[i].idx;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40iw_deinit_device - clean up the device resources
 * @iwdev: iwarp device
 *
 * Destroy the ib device पूर्णांकerface, हटाओ the mac ip entry and ipv4/ipv6 addresses,
 * destroy the device queues and मुक्त the pble and the hmc objects
 */
अटल व्योम i40iw_deinit_device(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40e_info *ldev = iwdev->ldev;

	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;

	i40iw_pr_info("state = %d\n", iwdev->init_state);
	अगर (iwdev->param_wq)
		destroy_workqueue(iwdev->param_wq);

	चयन (iwdev->init_state) अणु
	हाल RDMA_DEV_REGISTERED:
		iwdev->iw_status = 0;
		i40iw_port_ibevent(iwdev);
		i40iw_destroy_rdma_device(iwdev->iwibdev);
		fallthrough;
	हाल IP_ADDR_REGISTERED:
		अगर (!iwdev->reset)
			i40iw_del_macip_entry(iwdev, (u8)iwdev->mac_ip_table_idx);
		fallthrough;
	हाल PBLE_CHUNK_MEM:
		i40iw_destroy_pble_pool(dev, iwdev->pble_rsrc);
		fallthrough;
	हाल CEQ_CREATED:
		i40iw_dele_ceqs(iwdev);
		fallthrough;
	हाल AEQ_CREATED:
		i40iw_destroy_aeq(iwdev);
		fallthrough;
	हाल IEQ_CREATED:
		i40iw_puda_dele_resources(&iwdev->vsi, I40IW_PUDA_RSRC_TYPE_IEQ, iwdev->reset);
		fallthrough;
	हाल ILQ_CREATED:
		i40iw_puda_dele_resources(&iwdev->vsi, I40IW_PUDA_RSRC_TYPE_ILQ, iwdev->reset);
		fallthrough;
	हाल CCQ_CREATED:
		i40iw_destroy_ccq(iwdev);
		fallthrough;
	हाल HMC_OBJS_CREATED:
		i40iw_del_hmc_objects(dev, dev->hmc_info, true, iwdev->reset);
		fallthrough;
	हाल CQP_CREATED:
		i40iw_destroy_cqp(iwdev, true);
		fallthrough;
	हाल INITIAL_STATE:
		i40iw_cleanup_cm_core(&iwdev->cm_core);
		अगर (iwdev->vsi.pestat) अणु
			i40iw_vsi_stats_मुक्त(&iwdev->vsi);
			kमुक्त(iwdev->vsi.pestat);
		पूर्ण
		i40iw_del_init_mem(iwdev);
		अवरोध;
	हाल INVALID_STATE:
	शेष:
		i40iw_pr_err("bad init_state = %d\n", iwdev->init_state);
		अवरोध;
	पूर्ण

	i40iw_del_handler(i40iw_find_i40e_handler(ldev));
	kमुक्त(iwdev->hdl);
पूर्ण

/**
 * i40iw_setup_init_state - set up the initial device काष्ठा
 * @hdl: handler क्रम iwarp device - one per instance
 * @ldev: lan device inक्रमmation
 * @client: iwarp client inक्रमmation, provided during registration
 *
 * Initialize the iwarp device and its hdl inक्रमmation
 * using the ldev and client inक्रमmation
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_setup_init_state(काष्ठा i40iw_handler *hdl,
						     काष्ठा i40e_info *ldev,
						     काष्ठा i40e_client *client)
अणु
	काष्ठा i40iw_device *iwdev = &hdl->device;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	क्रमागत i40iw_status_code status;

	स_नकल(&hdl->ldev, ldev, माप(*ldev));

	iwdev->mpa_version = mpa_version;
	iwdev->resource_profile = (resource_profile < I40IW_HMC_PROखाता_EQUAL) ?
	    (u8)resource_profile + I40IW_HMC_PROखाता_DEFAULT :
	    I40IW_HMC_PROखाता_DEFAULT;
	iwdev->max_rdma_vfs =
		(iwdev->resource_profile != I40IW_HMC_PROखाता_DEFAULT) ?  max_rdma_vfs : 0;
	iwdev->max_enabled_vfs = iwdev->max_rdma_vfs;
	iwdev->netdev = ldev->netdev;
	hdl->client = client;
	अगर (!ldev->ftype)
		iwdev->db_start = pci_resource_start(ldev->pcidev, 0) + I40IW_DB_ADDR_OFFSET;
	अन्यथा
		iwdev->db_start = pci_resource_start(ldev->pcidev, 0) + I40IW_VF_DB_ADDR_OFFSET;

	status = i40iw_save_msix_info(iwdev, ldev);
	अगर (status)
		वापस status;
	iwdev->hw.pcidev = ldev->pcidev;
	iwdev->hw.hw_addr = ldev->hw_addr;
	status = i40iw_allocate_dma_mem(&iwdev->hw,
					&iwdev->obj_mem, 8192, 4096);
	अगर (status)
		जाओ निकास;
	iwdev->obj_next = iwdev->obj_mem;

	init_रुकोqueue_head(&iwdev->vchnl_रुकोq);
	init_रुकोqueue_head(&dev->vf_reqs);
	init_रुकोqueue_head(&iwdev->बंद_wq);

	status = i40iw_initialize_dev(iwdev, ldev);
निकास:
	अगर (status) अणु
		kमुक्त(iwdev->iw_msixtbl);
		i40iw_मुक्त_dma_mem(dev->hw, &iwdev->obj_mem);
		iwdev->iw_msixtbl = शून्य;
	पूर्ण
	वापस status;
पूर्ण

/**
 * i40iw_get_used_rsrc - determine resources used पूर्णांकernally
 * @iwdev: iwarp device
 *
 * Called after पूर्णांकernal allocations
 */
अटल व्योम i40iw_get_used_rsrc(काष्ठा i40iw_device *iwdev)
अणु
	iwdev->used_pds = find_next_zero_bit(iwdev->allocated_pds, iwdev->max_pd, 0);
	iwdev->used_qps = find_next_zero_bit(iwdev->allocated_qps, iwdev->max_qp, 0);
	iwdev->used_cqs = find_next_zero_bit(iwdev->allocated_cqs, iwdev->max_cq, 0);
	iwdev->used_mrs = find_next_zero_bit(iwdev->allocated_mrs, iwdev->max_mr, 0);
पूर्ण

/**
 * i40iw_खोलो - client पूर्णांकerface operation खोलो क्रम iwarp/uda device
 * @ldev: lan device inक्रमmation
 * @client: iwarp client inक्रमmation, provided during registration
 *
 * Called by the lan driver during the processing of client रेजिस्टर
 * Create device resources, set up queues, pble and hmc objects and
 * रेजिस्टर the device with the ib verbs पूर्णांकerface
 * Return 0 अगर successful, otherwise वापस error
 */
अटल पूर्णांक i40iw_खोलो(काष्ठा i40e_info *ldev, काष्ठा i40e_client *client)
अणु
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_sc_dev *dev;
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_handler *hdl;

	hdl = i40iw_find_netdev(ldev->netdev);
	अगर (hdl)
		वापस 0;

	hdl = kzalloc(माप(*hdl), GFP_KERNEL);
	अगर (!hdl)
		वापस -ENOMEM;
	iwdev = &hdl->device;
	iwdev->hdl = hdl;
	dev = &iwdev->sc_dev;
	अगर (i40iw_setup_cm_core(iwdev)) अणु
		kमुक्त(iwdev->hdl);
		वापस -ENOMEM;
	पूर्ण

	dev->back_dev = (व्योम *)iwdev;
	iwdev->ldev = &hdl->ldev;
	iwdev->client = client;
	mutex_init(&iwdev->pbl_mutex);
	i40iw_add_handler(hdl);

	करो अणु
		status = i40iw_setup_init_state(hdl, ldev, client);
		अगर (status)
			अवरोध;
		iwdev->init_state = INITIAL_STATE;
		अगर (dev->is_pf)
			i40iw_रुको_pe_पढ़ोy(dev->hw);
		status = i40iw_create_cqp(iwdev);
		अगर (status)
			अवरोध;
		iwdev->init_state = CQP_CREATED;
		status = i40iw_hmc_setup(iwdev);
		अगर (status)
			अवरोध;
		status = i40iw_create_ccq(iwdev);
		अगर (status)
			अवरोध;
		iwdev->init_state = CCQ_CREATED;
		status = i40iw_initialize_ilq(iwdev);
		अगर (status)
			अवरोध;
		iwdev->init_state = ILQ_CREATED;
		status = i40iw_initialize_ieq(iwdev);
		अगर (status)
			अवरोध;
		iwdev->init_state = IEQ_CREATED;
		status = i40iw_setup_aeq(iwdev);
		अगर (status)
			अवरोध;
		iwdev->init_state = AEQ_CREATED;
		status = i40iw_setup_ceqs(iwdev, ldev);
		अगर (status)
			अवरोध;

		status = i40iw_get_rdma_features(dev);
		अगर (status)
			dev->feature_info[I40IW_FEATURE_FW_INFO] =
				I40IW_FW_VER_DEFAULT;

		iwdev->init_state = CEQ_CREATED;
		status = i40iw_initialize_hw_resources(iwdev);
		अगर (status)
			अवरोध;
		i40iw_get_used_rsrc(iwdev);
		dev->ccq_ops->ccq_arm(dev->ccq);
		status = i40iw_hmc_init_pble(&iwdev->sc_dev, iwdev->pble_rsrc);
		अगर (status)
			अवरोध;
		iwdev->init_state = PBLE_CHUNK_MEM;
		iwdev->virtchnl_wq = alloc_ordered_workqueue("iwvch", WQ_MEM_RECLAIM);
		status = i40iw_add_mac_ip(iwdev);
		अगर (status)
			अवरोध;
		iwdev->init_state = IP_ADDR_REGISTERED;
		अगर (i40iw_रेजिस्टर_rdma_device(iwdev)) अणु
			i40iw_pr_err("register rdma device fail\n");
			अवरोध;
		पूर्ण;

		iwdev->init_state = RDMA_DEV_REGISTERED;
		iwdev->iw_status = 1;
		i40iw_port_ibevent(iwdev);
		iwdev->param_wq = alloc_ordered_workqueue("l2params", WQ_MEM_RECLAIM);
		अगर(iwdev->param_wq == शून्य)
			अवरोध;
		i40iw_pr_info("i40iw_open completed\n");
		वापस 0;
	पूर्ण जबतक (0);

	i40iw_pr_err("status = %d last completion = %d\n", status, iwdev->init_state);
	i40iw_deinit_device(iwdev);
	वापस -ERESTART;
पूर्ण

/**
 * i40iw_l2params_worker - worker क्रम l2 params change
 * @work: work poपूर्णांकer क्रम l2 params
 */
अटल व्योम i40iw_l2params_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा l2params_work *dwork =
	    container_of(work, काष्ठा l2params_work, work);
	काष्ठा i40iw_device *iwdev = dwork->iwdev;

	i40iw_change_l2params(&iwdev->vsi, &dwork->l2params);
	atomic_dec(&iwdev->params_busy);
	kमुक्त(work);
पूर्ण

/**
 * i40iw_l2param_change - handle qs handles क्रम qos and mss change
 * @ldev: lan device inक्रमmation
 * @client: client क्रम paramater change
 * @params: new parameters from L2
 */
अटल व्योम i40iw_l2param_change(काष्ठा i40e_info *ldev, काष्ठा i40e_client *client,
				 काष्ठा i40e_params *params)
अणु
	काष्ठा i40iw_handler *hdl;
	काष्ठा i40iw_l2params *l2params;
	काष्ठा l2params_work *work;
	काष्ठा i40iw_device *iwdev;
	पूर्णांक i;

	hdl = i40iw_find_i40e_handler(ldev);
	अगर (!hdl)
		वापस;

	iwdev = &hdl->device;

	अगर (atomic_पढ़ो(&iwdev->params_busy))
		वापस;


	work = kzalloc(माप(*work), GFP_KERNEL);
	अगर (!work)
		वापस;

	atomic_inc(&iwdev->params_busy);

	work->iwdev = iwdev;
	l2params = &work->l2params;
	क्रम (i = 0; i < I40E_CLIENT_MAX_USER_PRIORITY; i++)
		l2params->qs_handle_list[i] = params->qos.prio_qos[i].qs_handle;

	l2params->mtu = (params->mtu) ? params->mtu : iwdev->vsi.mtu;

	INIT_WORK(&work->work, i40iw_l2params_worker);
	queue_work(iwdev->param_wq, &work->work);
पूर्ण

/**
 * i40iw_बंद - client पूर्णांकerface operation बंद क्रम iwarp/uda device
 * @ldev: lan device inक्रमmation
 * @reset: true अगर called beक्रमe reset
 * @client: client to बंद
 *
 * Called by the lan driver during the processing of client unरेजिस्टर
 * Destroy and clean up the driver resources
 */
अटल व्योम i40iw_बंद(काष्ठा i40e_info *ldev, काष्ठा i40e_client *client, bool reset)
अणु
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_handler *hdl;

	hdl = i40iw_find_i40e_handler(ldev);
	अगर (!hdl)
		वापस;

	iwdev = &hdl->device;
	iwdev->closing = true;

	अगर (reset)
		iwdev->reset = true;

	i40iw_cm_tearकरोwn_connections(iwdev, शून्य, शून्य, true);
	destroy_workqueue(iwdev->virtchnl_wq);
	i40iw_deinit_device(iwdev);
पूर्ण

/**
 * i40iw_vf_reset - process VF reset
 * @ldev: lan device inक्रमmation
 * @client: client पूर्णांकerface instance
 * @vf_id: भव function id
 *
 * Called when a VF is reset by the PF
 * Destroy and clean up the VF resources
 */
अटल व्योम i40iw_vf_reset(काष्ठा i40e_info *ldev, काष्ठा i40e_client *client, u32 vf_id)
अणु
	काष्ठा i40iw_handler *hdl;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_hmc_fcn_info hmc_fcn_info;
	काष्ठा i40iw_virt_mem vf_dev_mem;
	काष्ठा i40iw_vfdev *पंचांगp_vfdev;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा i40iw_device *iwdev;

	hdl = i40iw_find_i40e_handler(ldev);
	अगर (!hdl)
		वापस;

	dev = &hdl->device.sc_dev;
	iwdev = (काष्ठा i40iw_device *)dev->back_dev;

	क्रम (i = 0; i < I40IW_MAX_PE_ENABLED_VF_COUNT; i++) अणु
		अगर (!dev->vf_dev[i] || (dev->vf_dev[i]->vf_id != vf_id))
			जारी;
		/* मुक्त all resources allocated on behalf of vf */
		पंचांगp_vfdev = dev->vf_dev[i];
		spin_lock_irqsave(&iwdev->vsi.pestat->lock, flags);
		dev->vf_dev[i] = शून्य;
		spin_unlock_irqrestore(&iwdev->vsi.pestat->lock, flags);
		i40iw_del_hmc_objects(dev, &पंचांगp_vfdev->hmc_info, false, false);
		/* हटाओ vf hmc function */
		स_रखो(&hmc_fcn_info, 0, माप(hmc_fcn_info));
		hmc_fcn_info.vf_id = vf_id;
		hmc_fcn_info.iw_vf_idx = पंचांगp_vfdev->iw_vf_idx;
		hmc_fcn_info.मुक्त_fcn = true;
		i40iw_cqp_manage_hmc_fcn_cmd(dev, &hmc_fcn_info);
		/* मुक्त vf_dev */
		vf_dev_mem.va = पंचांगp_vfdev;
		vf_dev_mem.size = माप(काष्ठा i40iw_vfdev) +
					माप(काष्ठा i40iw_hmc_obj_info) * I40IW_HMC_IW_MAX;
		i40iw_मुक्त_virt_mem(dev->hw, &vf_dev_mem);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40iw_vf_enable - enable a number of VFs
 * @ldev: lan device inक्रमmation
 * @client: client पूर्णांकerface instance
 * @num_vfs: number of VFs क्रम the PF
 *
 * Called when the number of VFs changes
 */
अटल व्योम i40iw_vf_enable(काष्ठा i40e_info *ldev,
			    काष्ठा i40e_client *client,
			    u32 num_vfs)
अणु
	काष्ठा i40iw_handler *hdl;

	hdl = i40iw_find_i40e_handler(ldev);
	अगर (!hdl)
		वापस;

	अगर (num_vfs > I40IW_MAX_PE_ENABLED_VF_COUNT)
		hdl->device.max_enabled_vfs = I40IW_MAX_PE_ENABLED_VF_COUNT;
	अन्यथा
		hdl->device.max_enabled_vfs = num_vfs;
पूर्ण

/**
 * i40iw_vf_capable - check अगर VF capable
 * @ldev: lan device inक्रमmation
 * @client: client पूर्णांकerface instance
 * @vf_id: भव function id
 *
 * Return 1 अगर a VF slot is available or अगर VF is alपढ़ोy RDMA enabled
 * Return 0 otherwise
 */
अटल पूर्णांक i40iw_vf_capable(काष्ठा i40e_info *ldev,
			    काष्ठा i40e_client *client,
			    u32 vf_id)
अणु
	काष्ठा i40iw_handler *hdl;
	काष्ठा i40iw_sc_dev *dev;
	अचिन्हित पूर्णांक i;

	hdl = i40iw_find_i40e_handler(ldev);
	अगर (!hdl)
		वापस 0;

	dev = &hdl->device.sc_dev;

	क्रम (i = 0; i < hdl->device.max_enabled_vfs; i++) अणु
		अगर (!dev->vf_dev[i] || (dev->vf_dev[i]->vf_id == vf_id))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40iw_virtchnl_receive - receive a message through the भव channel
 * @ldev: lan device inक्रमmation
 * @client: client पूर्णांकerface instance
 * @vf_id: भव function id associated with the message
 * @msg: message buffer poपूर्णांकer
 * @len: length of the message
 *
 * Invoke भव channel receive operation क्रम the given msg
 * Return 0 अगर successful, otherwise वापस error
 */
अटल पूर्णांक i40iw_virtchnl_receive(काष्ठा i40e_info *ldev,
				  काष्ठा i40e_client *client,
				  u32 vf_id,
				  u8 *msg,
				  u16 len)
अणु
	काष्ठा i40iw_handler *hdl;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_device *iwdev;
	पूर्णांक ret_code = I40IW_NOT_SUPPORTED;

	अगर (!len || !msg)
		वापस I40IW_ERR_PARAM;

	hdl = i40iw_find_i40e_handler(ldev);
	अगर (!hdl)
		वापस I40IW_ERR_PARAM;

	dev = &hdl->device.sc_dev;
	iwdev = dev->back_dev;

	अगर (dev->vchnl_अगर.vchnl_recv) अणु
		ret_code = dev->vchnl_अगर.vchnl_recv(dev, vf_id, msg, len);
		अगर (!dev->is_pf) अणु
			atomic_dec(&iwdev->vchnl_msgs);
			wake_up(&iwdev->vchnl_रुकोq);
		पूर्ण
	पूर्ण
	वापस ret_code;
पूर्ण

/**
 * i40iw_vf_clear_to_send - रुको to send भव channel message
 * @dev: iwarp device *
 * Wait क्रम until भव channel is clear
 * beक्रमe sending the next message
 *
 * Returns false अगर error
 * Returns true अगर clear to send
 */
bool i40iw_vf_clear_to_send(काष्ठा i40iw_sc_dev *dev)
अणु
	काष्ठा i40iw_device *iwdev;
	रुको_queue_entry_t रुको;

	iwdev = dev->back_dev;

	अगर (!wq_has_sleeper(&dev->vf_reqs) &&
	    (atomic_पढ़ो(&iwdev->vchnl_msgs) == 0))
		वापस true; /* भव channel is clear */

	init_रुको(&रुको);
	add_रुको_queue_exclusive(&dev->vf_reqs, &रुको);

	अगर (!रुको_event_समयout(dev->vf_reqs,
				(atomic_पढ़ो(&iwdev->vchnl_msgs) == 0),
				I40IW_VCHNL_EVENT_TIMEOUT))
		dev->vchnl_up = false;

	हटाओ_रुको_queue(&dev->vf_reqs, &रुको);

	वापस dev->vchnl_up;
पूर्ण

/**
 * i40iw_virtchnl_send - send a message through the भव channel
 * @dev: iwarp device
 * @vf_id: भव function id associated with the message
 * @msg: भव channel message buffer poपूर्णांकer
 * @len: length of the message
 *
 * Invoke भव channel send operation क्रम the given msg
 * Return 0 अगर successful, otherwise वापस error
 */
अटल क्रमागत i40iw_status_code i40iw_virtchnl_send(काष्ठा i40iw_sc_dev *dev,
						  u32 vf_id,
						  u8 *msg,
						  u16 len)
अणु
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40e_info *ldev;

	अगर (!dev || !dev->back_dev)
		वापस I40IW_ERR_BAD_PTR;

	iwdev = dev->back_dev;
	ldev = iwdev->ldev;

	अगर (ldev && ldev->ops && ldev->ops->virtchnl_send)
		वापस ldev->ops->virtchnl_send(ldev, &i40iw_client, vf_id, msg, len);
	वापस I40IW_ERR_BAD_PTR;
पूर्ण

/* client पूर्णांकerface functions */
अटल स्थिर काष्ठा i40e_client_ops i40e_ops = अणु
	.खोलो = i40iw_खोलो,
	.बंद = i40iw_बंद,
	.l2_param_change = i40iw_l2param_change,
	.virtchnl_receive = i40iw_virtchnl_receive,
	.vf_reset = i40iw_vf_reset,
	.vf_enable = i40iw_vf_enable,
	.vf_capable = i40iw_vf_capable
पूर्ण;

/**
 * i40iw_init_module - driver initialization function
 *
 * First function to call when the driver is loaded
 * Register the driver as i40e client and port mapper client
 */
अटल पूर्णांक __init i40iw_init_module(व्योम)
अणु
	पूर्णांक ret;

	स_रखो(&i40iw_client, 0, माप(i40iw_client));
	i40iw_client.version.major = CLIENT_IW_INTERFACE_VERSION_MAJOR;
	i40iw_client.version.minor = CLIENT_IW_INTERFACE_VERSION_MINOR;
	i40iw_client.version.build = CLIENT_IW_INTERFACE_VERSION_BUILD;
	i40iw_client.ops = &i40e_ops;
	स_नकल(i40iw_client.name, i40iw_client_name, I40E_CLIENT_STR_LENGTH);
	i40iw_client.type = I40E_CLIENT_IWARP;
	ret = i40e_रेजिस्टर_client(&i40iw_client);
	i40iw_रेजिस्टर_notअगरiers();

	वापस ret;
पूर्ण

/**
 * i40iw_निकास_module - driver निकास clean up function
 *
 * The function is called just beक्रमe the driver is unloaded
 * Unरेजिस्टर the driver as i40e client and port mapper client
 */
अटल व्योम __निकास i40iw_निकास_module(व्योम)
अणु
	i40iw_unरेजिस्टर_notअगरiers();
	i40e_unरेजिस्टर_client(&i40iw_client);
पूर्ण

module_init(i40iw_init_module);
module_निकास(i40iw_निकास_module);
