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

#अगर_अघोषित I40IW_IW_H
#घोषणा I40IW_IW_H
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/crc32c.h>
#समावेश <linux/net/पूर्णांकel/i40e_client.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_pack.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/iw_cm.h>
#समावेश <crypto/hash.h>

#समावेश "i40iw_status.h"
#समावेश "i40iw_osdep.h"
#समावेश "i40iw_d.h"
#समावेश "i40iw_hmc.h"

#समावेश "i40iw_type.h"
#समावेश "i40iw_p.h"
#समावेश <rdma/i40iw-abi.h>
#समावेश "i40iw_pble.h"
#समावेश "i40iw_verbs.h"
#समावेश "i40iw_cm.h"
#समावेश "i40iw_user.h"
#समावेश "i40iw_puda.h"

#घोषणा I40IW_FW_VER_DEFAULT 2
#घोषणा I40IW_HW_VERSION  2

#घोषणा I40IW_ARP_ADD     1
#घोषणा I40IW_ARP_DELETE  2
#घोषणा I40IW_ARP_RESOLVE 3

#घोषणा I40IW_MACIP_ADD     1
#घोषणा I40IW_MACIP_DELETE  2

#घोषणा IW_CCQ_SIZE         (I40IW_CQP_SW_SQSIZE_2048 + 1)
#घोषणा IW_CEQ_SIZE         2048
#घोषणा IW_AEQ_SIZE         2048

#घोषणा RX_BUF_SIZE            (1536 + 8)
#घोषणा IW_REG0_SIZE           (4 * 1024)
#घोषणा IW_TX_TIMEOUT          (6 * HZ)
#घोषणा IW_FIRST_QPN           1
#घोषणा IW_SW_CONTEXT_ALIGN    1024

#घोषणा MAX_DPC_ITERATIONS		128

#घोषणा I40IW_EVENT_TIMEOUT		100000
#घोषणा I40IW_VCHNL_EVENT_TIMEOUT	100000

#घोषणा	I40IW_NO_VLAN			0xffff
#घोषणा	I40IW_NO_QSET			0xffff

/* access to mcast filter list */
#घोषणा IW_ADD_MCAST false
#घोषणा IW_DEL_MCAST true

#घोषणा I40IW_DRV_OPT_ENABLE_MPA_VER_0     0x00000001
#घोषणा I40IW_DRV_OPT_DISABLE_MPA_CRC      0x00000002
#घोषणा I40IW_DRV_OPT_DISABLE_FIRST_WRITE  0x00000004
#घोषणा I40IW_DRV_OPT_DISABLE_INTF         0x00000008
#घोषणा I40IW_DRV_OPT_ENABLE_MSI           0x00000010
#घोषणा I40IW_DRV_OPT_DUAL_LOGICAL_PORT    0x00000020
#घोषणा I40IW_DRV_OPT_NO_INLINE_DATA       0x00000080
#घोषणा I40IW_DRV_OPT_DISABLE_INT_MOD      0x00000100
#घोषणा I40IW_DRV_OPT_DISABLE_VIRT_WQ      0x00000200
#घोषणा I40IW_DRV_OPT_ENABLE_PAU           0x00000400
#घोषणा I40IW_DRV_OPT_MCAST_LOGPORT_MAP    0x00000800

#घोषणा IW_HMC_OBJ_TYPE_NUM ARRAY_SIZE(iw_hmc_obj_types)
#घोषणा IW_CFG_FPM_QP_COUNT               32768
#घोषणा I40IW_MAX_PAGES_PER_FMR           512
#घोषणा I40IW_MIN_PAGES_PER_FMR           1
#घोषणा I40IW_CQP_COMPL_RQ_WQE_FLUSHED    2
#घोषणा I40IW_CQP_COMPL_SQ_WQE_FLUSHED    3
#घोषणा I40IW_CQP_COMPL_RQ_SQ_WQE_FLUSHED 4

काष्ठा i40iw_cqp_compl_info अणु
	u32 op_ret_val;
	u16 maj_err_code;
	u16 min_err_code;
	bool error;
	u8 op_code;
पूर्ण;

#घोषणा i40iw_pr_err(fmt, args ...) pr_err("%s: "fmt, __func__, ## args)

#घोषणा i40iw_pr_info(fmt, args ...) pr_info("%s: " fmt, __func__, ## args)

#घोषणा i40iw_pr_warn(fmt, args ...) pr_warn("%s: " fmt, __func__, ## args)

काष्ठा i40iw_cqp_request अणु
	काष्ठा cqp_commands_info info;
	रुको_queue_head_t रुकोq;
	काष्ठा list_head list;
	atomic_t refcount;
	व्योम (*callback_fcn)(काष्ठा i40iw_cqp_request*, u32);
	व्योम *param;
	काष्ठा i40iw_cqp_compl_info compl_info;
	bool रुकोing;
	bool request_करोne;
	bool dynamic;
पूर्ण;

काष्ठा i40iw_cqp अणु
	काष्ठा i40iw_sc_cqp sc_cqp;
	spinlock_t req_lock; /*cqp request list */
	रुको_queue_head_t रुकोq;
	काष्ठा i40iw_dma_mem sq;
	काष्ठा i40iw_dma_mem host_ctx;
	u64 *scratch_array;
	काष्ठा i40iw_cqp_request *cqp_requests;
	काष्ठा list_head cqp_avail_reqs;
	काष्ठा list_head cqp_pending_reqs;
पूर्ण;

काष्ठा i40iw_device;

काष्ठा i40iw_ccq अणु
	काष्ठा i40iw_sc_cq sc_cq;
	spinlock_t lock; /* ccq control */
	रुको_queue_head_t रुकोq;
	काष्ठा i40iw_dma_mem mem_cq;
	काष्ठा i40iw_dma_mem shaकरोw_area;
पूर्ण;

काष्ठा i40iw_ceq अणु
	काष्ठा i40iw_sc_ceq sc_ceq;
	काष्ठा i40iw_dma_mem mem;
	u32 irq;
	u32 msix_idx;
	काष्ठा i40iw_device *iwdev;
	काष्ठा tasklet_काष्ठा dpc_tasklet;
पूर्ण;

काष्ठा i40iw_aeq अणु
	काष्ठा i40iw_sc_aeq sc_aeq;
	काष्ठा i40iw_dma_mem mem;
पूर्ण;

काष्ठा i40iw_arp_entry अणु
	u32 ip_addr[4];
	u8 mac_addr[ETH_ALEN];
पूर्ण;

क्रमागत init_completion_state अणु
	INVALID_STATE = 0,
	INITIAL_STATE,
	CQP_CREATED,
	HMC_OBJS_CREATED,
	PBLE_CHUNK_MEM,
	CCQ_CREATED,
	AEQ_CREATED,
	CEQ_CREATED,
	ILQ_CREATED,
	IEQ_CREATED,
	IP_ADDR_REGISTERED,
	RDMA_DEV_REGISTERED
पूर्ण;

काष्ठा i40iw_msix_vector अणु
	u32 idx;
	u32 irq;
	u32 cpu_affinity;
	u32 ceq_id;
	cpumask_t mask;
पूर्ण;

काष्ठा l2params_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_l2params l2params;
पूर्ण;

#घोषणा I40IW_MSIX_TABLE_SIZE   65

काष्ठा virtchnl_work अणु
	काष्ठा work_काष्ठा work;
	जोड़ अणु
		काष्ठा i40iw_cqp_request *cqp_request;
		काष्ठा i40iw_virtchnl_work_info work_info;
	पूर्ण;
पूर्ण;

काष्ठा i40e_qvlist_info;

काष्ठा i40iw_device अणु
	काष्ठा i40iw_ib_device *iwibdev;
	काष्ठा net_device *netdev;
	रुको_queue_head_t vchnl_रुकोq;
	काष्ठा i40iw_sc_dev sc_dev;
	काष्ठा i40iw_sc_vsi vsi;
	काष्ठा i40iw_handler *hdl;
	काष्ठा i40e_info *ldev;
	काष्ठा i40e_client *client;
	काष्ठा i40iw_hw hw;
	काष्ठा i40iw_cm_core cm_core;
	u8 *mem_resources;
	अचिन्हित दीर्घ *allocated_qps;
	अचिन्हित दीर्घ *allocated_cqs;
	अचिन्हित दीर्घ *allocated_mrs;
	अचिन्हित दीर्घ *allocated_pds;
	अचिन्हित दीर्घ *allocated_arps;
	काष्ठा i40iw_qp **qp_table;
	bool msix_shared;
	u32 msix_count;
	काष्ठा i40iw_msix_vector *iw_msixtbl;
	काष्ठा i40e_qvlist_info *iw_qvlist;

	काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc;
	काष्ठा i40iw_arp_entry *arp_table;
	काष्ठा i40iw_cqp cqp;
	काष्ठा i40iw_ccq ccq;
	u32 ceqs_count;
	काष्ठा i40iw_ceq *ceqlist;
	काष्ठा i40iw_aeq aeq;
	u32 arp_table_size;
	u32 next_arp_index;
	spinlock_t resource_lock; /* hw resource access */
	spinlock_t qptable_lock;
	u32 venकरोr_id;
	u32 venकरोr_part_id;
	u32 of_device_रेजिस्टरed;

	u32 device_cap_flags;
	अचिन्हित दीर्घ db_start;
	u8 resource_profile;
	u8 max_rdma_vfs;
	u8 max_enabled_vfs;
	u8 max_sge;
	u8 iw_status;
	u8 send_term_ok;

	/* x710 specअगरic */
	काष्ठा mutex pbl_mutex;
	काष्ठा tasklet_काष्ठा dpc_tasklet;
	काष्ठा workqueue_काष्ठा *virtchnl_wq;
	काष्ठा virtchnl_work virtchnl_w[I40IW_MAX_PE_ENABLED_VF_COUNT];
	काष्ठा i40iw_dma_mem obj_mem;
	काष्ठा i40iw_dma_mem obj_next;
	u8 *hmc_info_mem;
	u32 sd_type;
	काष्ठा workqueue_काष्ठा *param_wq;
	atomic_t params_busy;
	क्रमागत init_completion_state init_state;
	u16 mac_ip_table_idx;
	atomic_t vchnl_msgs;
	u32 max_mr;
	u32 max_qp;
	u32 max_cq;
	u32 max_pd;
	u32 next_qp;
	u32 next_cq;
	u32 next_pd;
	u32 max_mr_size;
	u32 max_qp_wr;
	u32 max_cqe;
	u32 mr_stagmask;
	u32 mpa_version;
	bool dcb;
	bool closing;
	bool reset;
	u32 used_pds;
	u32 used_cqs;
	u32 used_mrs;
	u32 used_qps;
	रुको_queue_head_t बंद_wq;
	atomic64_t use_count;
पूर्ण;

काष्ठा i40iw_ib_device अणु
	काष्ठा ib_device ibdev;
	काष्ठा i40iw_device *iwdev;
पूर्ण;

काष्ठा i40iw_handler अणु
	काष्ठा list_head list;
	काष्ठा i40e_client *client;
	काष्ठा i40iw_device device;
	काष्ठा i40e_info ldev;
पूर्ण;

/**
 * i40iw_fw_major_ver - get firmware major version
 * @dev: iwarp device
 **/
अटल अंतरभूत u64 i40iw_fw_major_ver(काष्ठा i40iw_sc_dev *dev)
अणु
	वापस RS_64(dev->feature_info[I40IW_FEATURE_FW_INFO],
		     I40IW_FW_VER_MAJOR);
पूर्ण

/**
 * i40iw_fw_minor_ver - get firmware minor version
 * @dev: iwarp device
 **/
अटल अंतरभूत u64 i40iw_fw_minor_ver(काष्ठा i40iw_sc_dev *dev)
अणु
	वापस RS_64(dev->feature_info[I40IW_FEATURE_FW_INFO],
		     I40IW_FW_VER_MINOR);
पूर्ण

/**
 * to_iwdev - get device
 * @ibdev: ib device
 **/
अटल अंतरभूत काष्ठा i40iw_device *to_iwdev(काष्ठा ib_device *ibdev)
अणु
	वापस container_of(ibdev, काष्ठा i40iw_ib_device, ibdev)->iwdev;
पूर्ण

/**
 * to_ucontext - get user context
 * @ibucontext: ib user context
 **/
अटल अंतरभूत काष्ठा i40iw_ucontext *to_ucontext(काष्ठा ib_ucontext *ibucontext)
अणु
	वापस container_of(ibucontext, काष्ठा i40iw_ucontext, ibucontext);
पूर्ण

/**
 * to_iwpd - get protection करोमुख्य
 * @ibpd: ib pd
 **/
अटल अंतरभूत काष्ठा i40iw_pd *to_iwpd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा i40iw_pd, ibpd);
पूर्ण

/**
 * to_iwmr - get device memory region
 * @ibdev: ib memory region
 **/
अटल अंतरभूत काष्ठा i40iw_mr *to_iwmr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा i40iw_mr, ibmr);
पूर्ण

/**
 * to_iwmw - get device memory winकरोw
 * @ibmw: ib memory winकरोw
 **/
अटल अंतरभूत काष्ठा i40iw_mr *to_iwmw(काष्ठा ib_mw *ibmw)
अणु
	वापस container_of(ibmw, काष्ठा i40iw_mr, ibmw);
पूर्ण

/**
 * to_iwcq - get completion queue
 * @ibcq: ib cqdevice
 **/
अटल अंतरभूत काष्ठा i40iw_cq *to_iwcq(काष्ठा ib_cq *ibcq)
अणु
	वापस container_of(ibcq, काष्ठा i40iw_cq, ibcq);
पूर्ण

/**
 * to_iwqp - get device qp
 * @ibqp: ib qp
 **/
अटल अंतरभूत काष्ठा i40iw_qp *to_iwqp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा i40iw_qp, ibqp);
पूर्ण

/* i40iw.c */
व्योम i40iw_qp_add_ref(काष्ठा ib_qp *ibqp);
व्योम i40iw_qp_rem_ref(काष्ठा ib_qp *ibqp);
काष्ठा ib_qp *i40iw_get_qp(काष्ठा ib_device *, पूर्णांक);

व्योम i40iw_flush_wqes(काष्ठा i40iw_device *iwdev,
		      काष्ठा i40iw_qp *qp);

व्योम i40iw_manage_arp_cache(काष्ठा i40iw_device *iwdev,
			    अचिन्हित अक्षर *mac_addr,
			    u32 *ip_addr,
			    bool ipv4,
			    u32 action);

पूर्णांक i40iw_manage_apbvt(काष्ठा i40iw_device *iwdev,
		       u16 accel_local_port,
		       bool add_port);

काष्ठा i40iw_cqp_request *i40iw_get_cqp_request(काष्ठा i40iw_cqp *cqp, bool रुको);
व्योम i40iw_मुक्त_cqp_request(काष्ठा i40iw_cqp *cqp, काष्ठा i40iw_cqp_request *cqp_request);
व्योम i40iw_put_cqp_request(काष्ठा i40iw_cqp *cqp, काष्ठा i40iw_cqp_request *cqp_request);

/**
 * i40iw_alloc_resource - allocate a resource
 * @iwdev: device poपूर्णांकer
 * @resource_array: resource bit array:
 * @max_resources: maximum resource number
 * @req_resources_num: Allocated resource number
 * @next: next मुक्त id
 **/
अटल अंतरभूत पूर्णांक i40iw_alloc_resource(काष्ठा i40iw_device *iwdev,
				       अचिन्हित दीर्घ *resource_array,
				       u32 max_resources,
				       u32 *req_resource_num,
				       u32 *next)
अणु
	u32 resource_num;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iwdev->resource_lock, flags);
	resource_num = find_next_zero_bit(resource_array, max_resources, *next);
	अगर (resource_num >= max_resources) अणु
		resource_num = find_first_zero_bit(resource_array, max_resources);
		अगर (resource_num >= max_resources) अणु
			spin_unlock_irqrestore(&iwdev->resource_lock, flags);
			वापस -EOVERFLOW;
		पूर्ण
	पूर्ण
	set_bit(resource_num, resource_array);
	*next = resource_num + 1;
	अगर (*next == max_resources)
		*next = 0;
	*req_resource_num = resource_num;
	spin_unlock_irqrestore(&iwdev->resource_lock, flags);

	वापस 0;
पूर्ण

/**
 * i40iw_is_resource_allocated - detrmine अगर resource is
 * allocated
 * @iwdev: device poपूर्णांकer
 * @resource_array: resource array क्रम the resource_num
 * @resource_num: resource number to check
 **/
अटल अंतरभूत bool i40iw_is_resource_allocated(काष्ठा i40iw_device *iwdev,
					       अचिन्हित दीर्घ *resource_array,
					       u32 resource_num)
अणु
	bool bit_is_set;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iwdev->resource_lock, flags);

	bit_is_set = test_bit(resource_num, resource_array);
	spin_unlock_irqrestore(&iwdev->resource_lock, flags);

	वापस bit_is_set;
पूर्ण

/**
 * i40iw_मुक्त_resource - मुक्त a resource
 * @iwdev: device poपूर्णांकer
 * @resource_array: resource array क्रम the resource_num
 * @resource_num: resource number to मुक्त
 **/
अटल अंतरभूत व्योम i40iw_मुक्त_resource(काष्ठा i40iw_device *iwdev,
				       अचिन्हित दीर्घ *resource_array,
				       u32 resource_num)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iwdev->resource_lock, flags);
	clear_bit(resource_num, resource_array);
	spin_unlock_irqrestore(&iwdev->resource_lock, flags);
पूर्ण

काष्ठा i40iw_handler *i40iw_find_netdev(काष्ठा net_device *netdev);

/**
 * iw_init_resources -
 */
u32 i40iw_initialize_hw_resources(काष्ठा i40iw_device *iwdev);

पूर्णांक i40iw_रेजिस्टर_rdma_device(काष्ठा i40iw_device *iwdev);
व्योम i40iw_port_ibevent(काष्ठा i40iw_device *iwdev);
व्योम i40iw_cm_disconn(काष्ठा i40iw_qp *iwqp);
व्योम i40iw_cm_disconn_worker(व्योम *);
पूर्णांक mini_cm_recv_pkt(काष्ठा i40iw_cm_core *, काष्ठा i40iw_device *,
		     काष्ठा sk_buff *);

क्रमागत i40iw_status_code i40iw_handle_cqp_op(काष्ठा i40iw_device *iwdev,
					   काष्ठा i40iw_cqp_request *cqp_request);
क्रमागत i40iw_status_code i40iw_add_mac_addr(काष्ठा i40iw_device *iwdev,
					  u8 *mac_addr, u8 *mac_index);
पूर्णांक i40iw_modअगरy_qp(काष्ठा ib_qp *, काष्ठा ib_qp_attr *, पूर्णांक, काष्ठा ib_udata *);
व्योम i40iw_cq_wq_destroy(काष्ठा i40iw_device *iwdev, काष्ठा i40iw_sc_cq *cq);

व्योम i40iw_cleanup_pending_cqp_op(काष्ठा i40iw_device *iwdev);
व्योम i40iw_rem_pdusecount(काष्ठा i40iw_pd *iwpd, काष्ठा i40iw_device *iwdev);
व्योम i40iw_add_pdusecount(काष्ठा i40iw_pd *iwpd);
व्योम i40iw_rem_devusecount(काष्ठा i40iw_device *iwdev);
व्योम i40iw_add_devusecount(काष्ठा i40iw_device *iwdev);
व्योम i40iw_hw_modअगरy_qp(काष्ठा i40iw_device *iwdev, काष्ठा i40iw_qp *iwqp,
			काष्ठा i40iw_modअगरy_qp_info *info, bool रुको);

व्योम i40iw_qp_suspend_resume(काष्ठा i40iw_sc_dev *dev,
			     काष्ठा i40iw_sc_qp *qp,
			     bool suspend);
क्रमागत i40iw_status_code i40iw_manage_qhash(काष्ठा i40iw_device *iwdev,
					  काष्ठा i40iw_cm_info *cminfo,
					  क्रमागत i40iw_quad_entry_type etype,
					  क्रमागत i40iw_quad_hash_manage_type mtype,
					  व्योम *cmnode,
					  bool रुको);
व्योम i40iw_receive_ilq(काष्ठा i40iw_sc_vsi *vsi, काष्ठा i40iw_puda_buf *rbuf);
व्योम i40iw_मुक्त_sqbuf(काष्ठा i40iw_sc_vsi *vsi, व्योम *bufp);
व्योम i40iw_मुक्त_qp_resources(काष्ठा i40iw_qp *iwqp);

क्रमागत i40iw_status_code i40iw_obj_aligned_mem(काष्ठा i40iw_device *iwdev,
					     काष्ठा i40iw_dma_mem *memptr,
					     u32 size, u32 mask);

व्योम i40iw_request_reset(काष्ठा i40iw_device *iwdev);
व्योम i40iw_destroy_rdma_device(काष्ठा i40iw_ib_device *iwibdev);
पूर्णांक i40iw_setup_cm_core(काष्ठा i40iw_device *iwdev);
व्योम i40iw_cleanup_cm_core(काष्ठा i40iw_cm_core *cm_core);
व्योम i40iw_process_ceq(काष्ठा i40iw_device *, काष्ठा i40iw_ceq *iwceq);
व्योम i40iw_process_aeq(काष्ठा i40iw_device *);
व्योम i40iw_next_iw_state(काष्ठा i40iw_qp *iwqp,
			 u8 state, u8 del_hash,
			 u8 term, u8 term_len);
पूर्णांक i40iw_send_syn(काष्ठा i40iw_cm_node *cm_node, u32 sendack);
पूर्णांक i40iw_send_reset(काष्ठा i40iw_cm_node *cm_node);
काष्ठा i40iw_cm_node *i40iw_find_node(काष्ठा i40iw_cm_core *cm_core,
				      u16 rem_port,
				      u32 *rem_addr,
				      u16 loc_port,
				      u32 *loc_addr,
				      bool add_refcnt,
				      bool accelerated_list);

क्रमागत i40iw_status_code i40iw_hw_flush_wqes(काष्ठा i40iw_device *iwdev,
					   काष्ठा i40iw_sc_qp *qp,
					   काष्ठा i40iw_qp_flush_info *info,
					   bool रुको);

व्योम i40iw_gen_ae(काष्ठा i40iw_device *iwdev,
		  काष्ठा i40iw_sc_qp *qp,
		  काष्ठा i40iw_gen_ae_info *info,
		  bool रुको);

व्योम i40iw_copy_ip_ntohl(u32 *dst, __be32 *src);
काष्ठा ib_mr *i40iw_reg_phys_mr(काष्ठा ib_pd *ib_pd,
				u64 addr,
				u64 size,
				पूर्णांक acc,
				u64 *ioबहु_शुरू);

पूर्णांक i40iw_inetaddr_event(काष्ठा notअगरier_block *notअगरier,
			 अचिन्हित दीर्घ event,
			 व्योम *ptr);
पूर्णांक i40iw_inet6addr_event(काष्ठा notअगरier_block *notअगरier,
			  अचिन्हित दीर्घ event,
			  व्योम *ptr);
पूर्णांक i40iw_net_event(काष्ठा notअगरier_block *notअगरier,
		    अचिन्हित दीर्घ event,
		    व्योम *ptr);
पूर्णांक i40iw_netdevice_event(काष्ठा notअगरier_block *notअगरier,
			  अचिन्हित दीर्घ event,
			  व्योम *ptr);

#पूर्ण_अगर
