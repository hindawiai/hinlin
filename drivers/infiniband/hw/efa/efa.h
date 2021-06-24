<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause */
/*
 * Copyright 2018-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#अगर_अघोषित _EFA_H_
#घोषणा _EFA_H_

#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>

#समावेश <rdma/efa-abi.h>
#समावेश <rdma/ib_verbs.h>

#समावेश "efa_com_cmd.h"

#घोषणा DRV_MODULE_NAME         "efa"
#घोषणा DEVICE_NAME             "Elastic Fabric Adapter (EFA)"

#घोषणा EFA_IRQNAME_SIZE        40

/* 1 क्रम AENQ + ADMIN */
#घोषणा EFA_NUM_MSIX_VEC                  1
#घोषणा EFA_MGMNT_MSIX_VEC_IDX            0

काष्ठा efa_irq अणु
	irq_handler_t handler;
	व्योम *data;
	पूर्णांक cpu;
	u32 vector;
	cpumask_t affinity_hपूर्णांक_mask;
	अक्षर name[EFA_IRQNAME_SIZE];
पूर्ण;

/* Don't use anything other than atomic64 */
काष्ठा efa_stats अणु
	atomic64_t alloc_pd_err;
	atomic64_t create_qp_err;
	atomic64_t create_cq_err;
	atomic64_t reg_mr_err;
	atomic64_t alloc_ucontext_err;
	atomic64_t create_ah_err;
	atomic64_t mmap_err;
	atomic64_t keep_alive_rcvd;
पूर्ण;

काष्ठा efa_dev अणु
	काष्ठा ib_device ibdev;
	काष्ठा efa_com_dev edev;
	काष्ठा pci_dev *pdev;
	काष्ठा efa_com_get_device_attr_result dev_attr;

	u64 reg_bar_addr;
	u64 reg_bar_len;
	u64 mem_bar_addr;
	u64 mem_bar_len;
	u64 db_bar_addr;
	u64 db_bar_len;

	पूर्णांक admin_msix_vector_idx;
	काष्ठा efa_irq admin_irq;

	काष्ठा efa_stats stats;
पूर्ण;

काष्ठा efa_ucontext अणु
	काष्ठा ib_ucontext ibucontext;
	u16 uarn;
पूर्ण;

काष्ठा efa_pd अणु
	काष्ठा ib_pd ibpd;
	u16 pdn;
पूर्ण;

काष्ठा efa_mr अणु
	काष्ठा ib_mr ibmr;
	काष्ठा ib_umem *umem;
पूर्ण;

काष्ठा efa_cq अणु
	काष्ठा ib_cq ibcq;
	काष्ठा efa_ucontext *ucontext;
	dma_addr_t dma_addr;
	व्योम *cpu_addr;
	काष्ठा rdma_user_mmap_entry *mmap_entry;
	माप_प्रकार size;
	u16 cq_idx;
पूर्ण;

काष्ठा efa_qp अणु
	काष्ठा ib_qp ibqp;
	dma_addr_t rq_dma_addr;
	व्योम *rq_cpu_addr;
	माप_प्रकार rq_size;
	क्रमागत ib_qp_state state;

	/* Used क्रम saving mmap_xa entries */
	काष्ठा rdma_user_mmap_entry *sq_db_mmap_entry;
	काष्ठा rdma_user_mmap_entry *llq_desc_mmap_entry;
	काष्ठा rdma_user_mmap_entry *rq_db_mmap_entry;
	काष्ठा rdma_user_mmap_entry *rq_mmap_entry;

	u32 qp_handle;
	u32 max_send_wr;
	u32 max_recv_wr;
	u32 max_send_sge;
	u32 max_recv_sge;
	u32 max_अंतरभूत_data;
पूर्ण;

काष्ठा efa_ah अणु
	काष्ठा ib_ah ibah;
	u16 ah;
	/* dest_addr */
	u8 id[EFA_GID_SIZE];
पूर्ण;

पूर्णांक efa_query_device(काष्ठा ib_device *ibdev,
		     काष्ठा ib_device_attr *props,
		     काष्ठा ib_udata *udata);
पूर्णांक efa_query_port(काष्ठा ib_device *ibdev, u32 port,
		   काष्ठा ib_port_attr *props);
पूर्णांक efa_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr,
		 पूर्णांक qp_attr_mask,
		 काष्ठा ib_qp_init_attr *qp_init_attr);
पूर्णांक efa_query_gid(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
		  जोड़ ib_gid *gid);
पूर्णांक efa_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index,
		   u16 *pkey);
पूर्णांक efa_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata);
पूर्णांक efa_dealloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata);
पूर्णांक efa_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata);
काष्ठा ib_qp *efa_create_qp(काष्ठा ib_pd *ibpd,
			    काष्ठा ib_qp_init_attr *init_attr,
			    काष्ठा ib_udata *udata);
पूर्णांक efa_destroy_cq(काष्ठा ib_cq *ibcq, काष्ठा ib_udata *udata);
पूर्णांक efa_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		  काष्ठा ib_udata *udata);
काष्ठा ib_mr *efa_reg_mr(काष्ठा ib_pd *ibpd, u64 start, u64 length,
			 u64 virt_addr, पूर्णांक access_flags,
			 काष्ठा ib_udata *udata);
पूर्णांक efa_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata);
पूर्णांक efa_get_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
			   काष्ठा ib_port_immutable *immutable);
पूर्णांक efa_alloc_ucontext(काष्ठा ib_ucontext *ibucontext, काष्ठा ib_udata *udata);
व्योम efa_dealloc_ucontext(काष्ठा ib_ucontext *ibucontext);
पूर्णांक efa_mmap(काष्ठा ib_ucontext *ibucontext,
	     काष्ठा vm_area_काष्ठा *vma);
व्योम efa_mmap_मुक्त(काष्ठा rdma_user_mmap_entry *rdma_entry);
पूर्णांक efa_create_ah(काष्ठा ib_ah *ibah,
		  काष्ठा rdma_ah_init_attr *init_attr,
		  काष्ठा ib_udata *udata);
पूर्णांक efa_destroy_ah(काष्ठा ib_ah *ibah, u32 flags);
पूर्णांक efa_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr,
		  पूर्णांक qp_attr_mask, काष्ठा ib_udata *udata);
क्रमागत rdma_link_layer efa_port_link_layer(काष्ठा ib_device *ibdev,
					 u32 port_num);
काष्ठा rdma_hw_stats *efa_alloc_hw_stats(काष्ठा ib_device *ibdev, u32 port_num);
पूर्णांक efa_get_hw_stats(काष्ठा ib_device *ibdev, काष्ठा rdma_hw_stats *stats,
		     u32 port_num, पूर्णांक index);

#पूर्ण_अगर /* _EFA_H_ */
