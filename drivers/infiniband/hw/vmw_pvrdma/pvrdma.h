<शैली गुरु>
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __PVRDMA_H__
#घोषणा __PVRDMA_H__

#समावेश <linux/compiler.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/workqueue.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/vmw_pvrdma-abi.h>

#समावेश "pvrdma_ring.h"
#समावेश "pvrdma_dev_api.h"
#समावेश "pvrdma_verbs.h"

/* NOT the same as BIT_MASK(). */
#घोषणा PVRDMA_MASK(n) ((n << 1) - 1)

/*
 * VMware PVRDMA PCI device id.
 */
#घोषणा PCI_DEVICE_ID_VMWARE_PVRDMA	0x0820

#घोषणा PVRDMA_NUM_RING_PAGES		4
#घोषणा PVRDMA_QP_NUM_HEADER_PAGES	1

काष्ठा pvrdma_dev;

काष्ठा pvrdma_page_dir अणु
	dma_addr_t dir_dma;
	u64 *dir;
	पूर्णांक ntables;
	u64 **tables;
	u64 npages;
	व्योम **pages;
पूर्ण;

काष्ठा pvrdma_cq अणु
	काष्ठा ib_cq ibcq;
	पूर्णांक offset;
	spinlock_t cq_lock; /* Poll lock. */
	काष्ठा pvrdma_uar_map *uar;
	काष्ठा ib_umem *umem;
	काष्ठा pvrdma_ring_state *ring_state;
	काष्ठा pvrdma_page_dir pdir;
	u32 cq_handle;
	bool is_kernel;
	refcount_t refcnt;
	काष्ठा completion मुक्त;
पूर्ण;

काष्ठा pvrdma_id_table अणु
	u32 last;
	u32 top;
	u32 max;
	u32 mask;
	spinlock_t lock; /* Table lock. */
	अचिन्हित दीर्घ *table;
पूर्ण;

काष्ठा pvrdma_uar_map अणु
	अचिन्हित दीर्घ pfn;
	व्योम __iomem *map;
	पूर्णांक index;
पूर्ण;

काष्ठा pvrdma_uar_table अणु
	काष्ठा pvrdma_id_table tbl;
	पूर्णांक size;
पूर्ण;

काष्ठा pvrdma_ucontext अणु
	काष्ठा ib_ucontext ibucontext;
	काष्ठा pvrdma_dev *dev;
	काष्ठा pvrdma_uar_map uar;
	u64 ctx_handle;
पूर्ण;

काष्ठा pvrdma_pd अणु
	काष्ठा ib_pd ibpd;
	u32 pdn;
	u32 pd_handle;
	पूर्णांक privileged;
पूर्ण;

काष्ठा pvrdma_mr अणु
	u32 mr_handle;
	u64 iova;
	u64 size;
पूर्ण;

काष्ठा pvrdma_user_mr अणु
	काष्ठा ib_mr ibmr;
	काष्ठा ib_umem *umem;
	काष्ठा pvrdma_mr mmr;
	काष्ठा pvrdma_page_dir pdir;
	u64 *pages;
	u32 npages;
	u32 max_pages;
	u32 page_shअगरt;
पूर्ण;

काष्ठा pvrdma_wq अणु
	काष्ठा pvrdma_ring *ring;
	spinlock_t lock; /* Work queue lock. */
	पूर्णांक wqe_cnt;
	पूर्णांक wqe_size;
	पूर्णांक max_sg;
	पूर्णांक offset;
पूर्ण;

काष्ठा pvrdma_ah अणु
	काष्ठा ib_ah ibah;
	काष्ठा pvrdma_av av;
पूर्ण;

काष्ठा pvrdma_srq अणु
	काष्ठा ib_srq ibsrq;
	पूर्णांक offset;
	spinlock_t lock; /* SRQ lock. */
	पूर्णांक wqe_cnt;
	पूर्णांक wqe_size;
	पूर्णांक max_gs;
	काष्ठा ib_umem *umem;
	काष्ठा pvrdma_ring_state *ring;
	काष्ठा pvrdma_page_dir pdir;
	u32 srq_handle;
	पूर्णांक npages;
	refcount_t refcnt;
	काष्ठा completion मुक्त;
पूर्ण;

काष्ठा pvrdma_qp अणु
	काष्ठा ib_qp ibqp;
	u32 qp_handle;
	u32 qkey;
	काष्ठा pvrdma_wq sq;
	काष्ठा pvrdma_wq rq;
	काष्ठा ib_umem *rumem;
	काष्ठा ib_umem *sumem;
	काष्ठा pvrdma_page_dir pdir;
	काष्ठा pvrdma_srq *srq;
	पूर्णांक npages;
	पूर्णांक npages_send;
	पूर्णांक npages_recv;
	u32 flags;
	u8 port;
	u8 state;
	bool is_kernel;
	काष्ठा mutex mutex; /* QP state mutex. */
	refcount_t refcnt;
	काष्ठा completion मुक्त;
पूर्ण;

काष्ठा pvrdma_dev अणु
	/* PCI device-related inक्रमmation. */
	काष्ठा ib_device ib_dev;
	काष्ठा pci_dev *pdev;
	व्योम __iomem *regs;
	काष्ठा pvrdma_device_shared_region *dsr; /* Shared region poपूर्णांकer */
	dma_addr_t dsrbase; /* Shared region base address */
	व्योम *cmd_slot;
	व्योम *resp_slot;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head device_link;
	अचिन्हित पूर्णांक dsr_version;

	/* Locking and पूर्णांकerrupt inक्रमmation. */
	spinlock_t cmd_lock; /* Command lock. */
	काष्ठा semaphore cmd_sema;
	काष्ठा completion cmd_करोne;
	अचिन्हित पूर्णांक nr_vectors;

	/* RDMA-related device inक्रमmation. */
	जोड़ ib_gid *sgid_tbl;
	काष्ठा pvrdma_ring_state *async_ring_state;
	काष्ठा pvrdma_page_dir async_pdir;
	काष्ठा pvrdma_ring_state *cq_ring_state;
	काष्ठा pvrdma_page_dir cq_pdir;
	काष्ठा pvrdma_cq **cq_tbl;
	spinlock_t cq_tbl_lock;
	काष्ठा pvrdma_srq **srq_tbl;
	spinlock_t srq_tbl_lock;
	काष्ठा pvrdma_qp **qp_tbl;
	spinlock_t qp_tbl_lock;
	काष्ठा pvrdma_uar_table uar_table;
	काष्ठा pvrdma_uar_map driver_uar;
	__be64 sys_image_guid;
	spinlock_t desc_lock; /* Device modअगरication lock. */
	u32 port_cap_mask;
	काष्ठा mutex port_mutex; /* Port modअगरication mutex. */
	bool ib_active;
	atomic_t num_qps;
	atomic_t num_cqs;
	atomic_t num_srqs;
	atomic_t num_pds;
	atomic_t num_ahs;

	/* Network device inक्रमmation. */
	काष्ठा net_device *netdev;
	काष्ठा notअगरier_block nb_netdev;
पूर्ण;

काष्ठा pvrdma_netdevice_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा net_device *event_netdev;
	अचिन्हित दीर्घ event;
पूर्ण;

अटल अंतरभूत काष्ठा pvrdma_dev *to_vdev(काष्ठा ib_device *ibdev)
अणु
	वापस container_of(ibdev, काष्ठा pvrdma_dev, ib_dev);
पूर्ण

अटल अंतरभूत काष्ठा
pvrdma_ucontext *to_vucontext(काष्ठा ib_ucontext *ibucontext)
अणु
	वापस container_of(ibucontext, काष्ठा pvrdma_ucontext, ibucontext);
पूर्ण

अटल अंतरभूत काष्ठा pvrdma_pd *to_vpd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा pvrdma_pd, ibpd);
पूर्ण

अटल अंतरभूत काष्ठा pvrdma_cq *to_vcq(काष्ठा ib_cq *ibcq)
अणु
	वापस container_of(ibcq, काष्ठा pvrdma_cq, ibcq);
पूर्ण

अटल अंतरभूत काष्ठा pvrdma_srq *to_vsrq(काष्ठा ib_srq *ibsrq)
अणु
	वापस container_of(ibsrq, काष्ठा pvrdma_srq, ibsrq);
पूर्ण

अटल अंतरभूत काष्ठा pvrdma_user_mr *to_vmr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा pvrdma_user_mr, ibmr);
पूर्ण

अटल अंतरभूत काष्ठा pvrdma_qp *to_vqp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा pvrdma_qp, ibqp);
पूर्ण

अटल अंतरभूत काष्ठा pvrdma_ah *to_vah(काष्ठा ib_ah *ibah)
अणु
	वापस container_of(ibah, काष्ठा pvrdma_ah, ibah);
पूर्ण

अटल अंतरभूत व्योम pvrdma_ग_लिखो_reg(काष्ठा pvrdma_dev *dev, u32 reg, u32 val)
अणु
	ग_लिखोl(cpu_to_le32(val), dev->regs + reg);
पूर्ण

अटल अंतरभूत u32 pvrdma_पढ़ो_reg(काष्ठा pvrdma_dev *dev, u32 reg)
अणु
	वापस le32_to_cpu(पढ़ोl(dev->regs + reg));
पूर्ण

अटल अंतरभूत व्योम pvrdma_ग_लिखो_uar_cq(काष्ठा pvrdma_dev *dev, u32 val)
अणु
	ग_लिखोl(cpu_to_le32(val), dev->driver_uar.map + PVRDMA_UAR_CQ_OFFSET);
पूर्ण

अटल अंतरभूत व्योम pvrdma_ग_लिखो_uar_qp(काष्ठा pvrdma_dev *dev, u32 val)
अणु
	ग_लिखोl(cpu_to_le32(val), dev->driver_uar.map + PVRDMA_UAR_QP_OFFSET);
पूर्ण

अटल अंतरभूत व्योम *pvrdma_page_dir_get_ptr(काष्ठा pvrdma_page_dir *pdir,
					    u64 offset)
अणु
	वापस pdir->pages[offset / PAGE_SIZE] + (offset % PAGE_SIZE);
पूर्ण

अटल अंतरभूत क्रमागत pvrdma_mtu ib_mtu_to_pvrdma(क्रमागत ib_mtu mtu)
अणु
	वापस (क्रमागत pvrdma_mtu)mtu;
पूर्ण

अटल अंतरभूत क्रमागत ib_mtu pvrdma_mtu_to_ib(क्रमागत pvrdma_mtu mtu)
अणु
	वापस (क्रमागत ib_mtu)mtu;
पूर्ण

अटल अंतरभूत क्रमागत pvrdma_port_state ib_port_state_to_pvrdma(
					क्रमागत ib_port_state state)
अणु
	वापस (क्रमागत pvrdma_port_state)state;
पूर्ण

अटल अंतरभूत क्रमागत ib_port_state pvrdma_port_state_to_ib(
					क्रमागत pvrdma_port_state state)
अणु
	वापस (क्रमागत ib_port_state)state;
पूर्ण

अटल अंतरभूत पूर्णांक pvrdma_port_cap_flags_to_ib(पूर्णांक flags)
अणु
	वापस flags;
पूर्ण

अटल अंतरभूत क्रमागत pvrdma_port_width ib_port_width_to_pvrdma(
					क्रमागत ib_port_width width)
अणु
	वापस (क्रमागत pvrdma_port_width)width;
पूर्ण

अटल अंतरभूत क्रमागत ib_port_width pvrdma_port_width_to_ib(
					क्रमागत pvrdma_port_width width)
अणु
	वापस (क्रमागत ib_port_width)width;
पूर्ण

अटल अंतरभूत क्रमागत pvrdma_port_speed ib_port_speed_to_pvrdma(
					क्रमागत ib_port_speed speed)
अणु
	वापस (क्रमागत pvrdma_port_speed)speed;
पूर्ण

अटल अंतरभूत क्रमागत ib_port_speed pvrdma_port_speed_to_ib(
					क्रमागत pvrdma_port_speed speed)
अणु
	वापस (क्रमागत ib_port_speed)speed;
पूर्ण

अटल अंतरभूत पूर्णांक ib_qp_attr_mask_to_pvrdma(पूर्णांक attr_mask)
अणु
	वापस attr_mask & PVRDMA_MASK(PVRDMA_QP_ATTR_MASK_MAX);
पूर्ण

अटल अंतरभूत क्रमागत pvrdma_mig_state ib_mig_state_to_pvrdma(
					क्रमागत ib_mig_state state)
अणु
	वापस (क्रमागत pvrdma_mig_state)state;
पूर्ण

अटल अंतरभूत क्रमागत ib_mig_state pvrdma_mig_state_to_ib(
					क्रमागत pvrdma_mig_state state)
अणु
	वापस (क्रमागत ib_mig_state)state;
पूर्ण

अटल अंतरभूत पूर्णांक ib_access_flags_to_pvrdma(पूर्णांक flags)
अणु
	वापस flags;
पूर्ण

अटल अंतरभूत पूर्णांक pvrdma_access_flags_to_ib(पूर्णांक flags)
अणु
	वापस flags & PVRDMA_MASK(PVRDMA_ACCESS_FLAGS_MAX);
पूर्ण

अटल अंतरभूत क्रमागत pvrdma_qp_type ib_qp_type_to_pvrdma(क्रमागत ib_qp_type type)
अणु
	वापस (क्रमागत pvrdma_qp_type)type;
पूर्ण

अटल अंतरभूत क्रमागत pvrdma_qp_state ib_qp_state_to_pvrdma(क्रमागत ib_qp_state state)
अणु
	वापस (क्रमागत pvrdma_qp_state)state;
पूर्ण

अटल अंतरभूत क्रमागत ib_qp_state pvrdma_qp_state_to_ib(क्रमागत pvrdma_qp_state state)
अणु
	वापस (क्रमागत ib_qp_state)state;
पूर्ण

अटल अंतरभूत क्रमागत pvrdma_wr_opcode ib_wr_opcode_to_pvrdma(क्रमागत ib_wr_opcode op)
अणु
	चयन (op) अणु
	हाल IB_WR_RDMA_WRITE:
		वापस PVRDMA_WR_RDMA_WRITE;
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		वापस PVRDMA_WR_RDMA_WRITE_WITH_IMM;
	हाल IB_WR_SEND:
		वापस PVRDMA_WR_SEND;
	हाल IB_WR_SEND_WITH_IMM:
		वापस PVRDMA_WR_SEND_WITH_IMM;
	हाल IB_WR_RDMA_READ:
		वापस PVRDMA_WR_RDMA_READ;
	हाल IB_WR_ATOMIC_CMP_AND_SWP:
		वापस PVRDMA_WR_ATOMIC_CMP_AND_SWP;
	हाल IB_WR_ATOMIC_FETCH_AND_ADD:
		वापस PVRDMA_WR_ATOMIC_FETCH_AND_ADD;
	हाल IB_WR_LSO:
		वापस PVRDMA_WR_LSO;
	हाल IB_WR_SEND_WITH_INV:
		वापस PVRDMA_WR_SEND_WITH_INV;
	हाल IB_WR_RDMA_READ_WITH_INV:
		वापस PVRDMA_WR_RDMA_READ_WITH_INV;
	हाल IB_WR_LOCAL_INV:
		वापस PVRDMA_WR_LOCAL_INV;
	हाल IB_WR_REG_MR:
		वापस PVRDMA_WR_FAST_REG_MR;
	हाल IB_WR_MASKED_ATOMIC_CMP_AND_SWP:
		वापस PVRDMA_WR_MASKED_ATOMIC_CMP_AND_SWP;
	हाल IB_WR_MASKED_ATOMIC_FETCH_AND_ADD:
		वापस PVRDMA_WR_MASKED_ATOMIC_FETCH_AND_ADD;
	हाल IB_WR_REG_MR_INTEGRITY:
		वापस PVRDMA_WR_REG_SIG_MR;
	शेष:
		वापस PVRDMA_WR_ERROR;
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत ib_wc_status pvrdma_wc_status_to_ib(
					क्रमागत pvrdma_wc_status status)
अणु
	वापस (क्रमागत ib_wc_status)status;
पूर्ण

अटल अंतरभूत पूर्णांक pvrdma_wc_opcode_to_ib(अचिन्हित पूर्णांक opcode)
अणु
	चयन (opcode) अणु
	हाल PVRDMA_WC_SEND:
		वापस IB_WC_SEND;
	हाल PVRDMA_WC_RDMA_WRITE:
		वापस IB_WC_RDMA_WRITE;
	हाल PVRDMA_WC_RDMA_READ:
		वापस IB_WC_RDMA_READ;
	हाल PVRDMA_WC_COMP_SWAP:
		वापस IB_WC_COMP_SWAP;
	हाल PVRDMA_WC_FETCH_ADD:
		वापस IB_WC_FETCH_ADD;
	हाल PVRDMA_WC_LOCAL_INV:
		वापस IB_WC_LOCAL_INV;
	हाल PVRDMA_WC_FAST_REG_MR:
		वापस IB_WC_REG_MR;
	हाल PVRDMA_WC_MASKED_COMP_SWAP:
		वापस IB_WC_MASKED_COMP_SWAP;
	हाल PVRDMA_WC_MASKED_FETCH_ADD:
		वापस IB_WC_MASKED_FETCH_ADD;
	हाल PVRDMA_WC_RECV:
		वापस IB_WC_RECV;
	हाल PVRDMA_WC_RECV_RDMA_WITH_IMM:
		वापस IB_WC_RECV_RDMA_WITH_IMM;
	शेष:
		वापस IB_WC_SEND;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक pvrdma_wc_flags_to_ib(पूर्णांक flags)
अणु
	वापस flags;
पूर्ण

अटल अंतरभूत पूर्णांक ib_send_flags_to_pvrdma(पूर्णांक flags)
अणु
	वापस flags & PVRDMA_MASK(PVRDMA_SEND_FLAGS_MAX);
पूर्ण

अटल अंतरभूत पूर्णांक pvrdma_network_type_to_ib(क्रमागत pvrdma_network_type type)
अणु
	चयन (type) अणु
	हाल PVRDMA_NETWORK_ROCE_V1:
		वापस RDMA_NETWORK_ROCE_V1;
	हाल PVRDMA_NETWORK_IPV4:
		वापस RDMA_NETWORK_IPV4;
	हाल PVRDMA_NETWORK_IPV6:
		वापस RDMA_NETWORK_IPV6;
	शेष:
		वापस RDMA_NETWORK_IPV6;
	पूर्ण
पूर्ण

व्योम pvrdma_qp_cap_to_ib(काष्ठा ib_qp_cap *dst,
			 स्थिर काष्ठा pvrdma_qp_cap *src);
व्योम ib_qp_cap_to_pvrdma(काष्ठा pvrdma_qp_cap *dst,
			 स्थिर काष्ठा ib_qp_cap *src);
व्योम pvrdma_gid_to_ib(जोड़ ib_gid *dst, स्थिर जोड़ pvrdma_gid *src);
व्योम ib_gid_to_pvrdma(जोड़ pvrdma_gid *dst, स्थिर जोड़ ib_gid *src);
व्योम pvrdma_global_route_to_ib(काष्ठा ib_global_route *dst,
			       स्थिर काष्ठा pvrdma_global_route *src);
व्योम ib_global_route_to_pvrdma(काष्ठा pvrdma_global_route *dst,
			       स्थिर काष्ठा ib_global_route *src);
व्योम pvrdma_ah_attr_to_rdma(काष्ठा rdma_ah_attr *dst,
			    स्थिर काष्ठा pvrdma_ah_attr *src);
व्योम rdma_ah_attr_to_pvrdma(काष्ठा pvrdma_ah_attr *dst,
			    स्थिर काष्ठा rdma_ah_attr *src);
u8 ib_gid_type_to_pvrdma(क्रमागत ib_gid_type gid_type);

पूर्णांक pvrdma_uar_table_init(काष्ठा pvrdma_dev *dev);
व्योम pvrdma_uar_table_cleanup(काष्ठा pvrdma_dev *dev);

पूर्णांक pvrdma_uar_alloc(काष्ठा pvrdma_dev *dev, काष्ठा pvrdma_uar_map *uar);
व्योम pvrdma_uar_मुक्त(काष्ठा pvrdma_dev *dev, काष्ठा pvrdma_uar_map *uar);

व्योम _pvrdma_flush_cqe(काष्ठा pvrdma_qp *qp, काष्ठा pvrdma_cq *cq);

पूर्णांक pvrdma_page_dir_init(काष्ठा pvrdma_dev *dev, काष्ठा pvrdma_page_dir *pdir,
			 u64 npages, bool alloc_pages);
व्योम pvrdma_page_dir_cleanup(काष्ठा pvrdma_dev *dev,
			     काष्ठा pvrdma_page_dir *pdir);
पूर्णांक pvrdma_page_dir_insert_dma(काष्ठा pvrdma_page_dir *pdir, u64 idx,
			       dma_addr_t daddr);
पूर्णांक pvrdma_page_dir_insert_umem(काष्ठा pvrdma_page_dir *pdir,
				काष्ठा ib_umem *umem, u64 offset);
dma_addr_t pvrdma_page_dir_get_dma(काष्ठा pvrdma_page_dir *pdir, u64 idx);
पूर्णांक pvrdma_page_dir_insert_page_list(काष्ठा pvrdma_page_dir *pdir,
				     u64 *page_list, पूर्णांक num_pages);

पूर्णांक pvrdma_cmd_post(काष्ठा pvrdma_dev *dev, जोड़ pvrdma_cmd_req *req,
		    जोड़ pvrdma_cmd_resp *rsp, अचिन्हित resp_code);

#पूर्ण_अगर /* __PVRDMA_H__ */
