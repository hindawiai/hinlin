<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2004 Voltaire, Inc. All rights reserved.
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

#अगर_अघोषित MTHCA_DEV_H
#घोषणा MTHCA_DEV_H

#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/semaphore.h>

#समावेश "mthca_provider.h"
#समावेश "mthca_doorbell.h"

#घोषणा DRV_NAME	"ib_mthca"
#घोषणा PFX		DRV_NAME ": "
#घोषणा DRV_VERSION	"1.0"
#घोषणा DRV_RELDATE	"April 4, 2008"

क्रमागत अणु
	MTHCA_FLAG_DDR_HIDDEN = 1 << 1,
	MTHCA_FLAG_SRQ        = 1 << 2,
	MTHCA_FLAG_MSI_X      = 1 << 3,
	MTHCA_FLAG_NO_LAM     = 1 << 4,
	MTHCA_FLAG_FMR        = 1 << 5,
	MTHCA_FLAG_MEMFREE    = 1 << 6,
	MTHCA_FLAG_PCIE       = 1 << 7,
	MTHCA_FLAG_SINAI_OPT  = 1 << 8
पूर्ण;

क्रमागत अणु
	MTHCA_MAX_PORTS = 2
पूर्ण;

क्रमागत अणु
	MTHCA_BOARD_ID_LEN = 64
पूर्ण;

क्रमागत अणु
	MTHCA_EQ_CONTEXT_SIZE =  0x40,
	MTHCA_CQ_CONTEXT_SIZE =  0x40,
	MTHCA_QP_CONTEXT_SIZE = 0x200,
	MTHCA_RDB_ENTRY_SIZE  =  0x20,
	MTHCA_AV_SIZE         =  0x20,
	MTHCA_MGM_ENTRY_SIZE  = 0x100,

	/* Arbel FW gives us these, but we need them क्रम Tavor */
	MTHCA_MPT_ENTRY_SIZE  =  0x40,
	MTHCA_MTT_SEG_SIZE    =  0x40,

	MTHCA_QP_PER_MGM      = 4 * (MTHCA_MGM_ENTRY_SIZE / 16 - 2)
पूर्ण;

क्रमागत अणु
	MTHCA_EQ_CMD,
	MTHCA_EQ_ASYNC,
	MTHCA_EQ_COMP,
	MTHCA_NUM_EQ
पूर्ण;

क्रमागत अणु
	MTHCA_OPCODE_NOP            = 0x00,
	MTHCA_OPCODE_RDMA_WRITE     = 0x08,
	MTHCA_OPCODE_RDMA_WRITE_IMM = 0x09,
	MTHCA_OPCODE_SEND           = 0x0a,
	MTHCA_OPCODE_SEND_IMM       = 0x0b,
	MTHCA_OPCODE_RDMA_READ      = 0x10,
	MTHCA_OPCODE_ATOMIC_CS      = 0x11,
	MTHCA_OPCODE_ATOMIC_FA      = 0x12,
	MTHCA_OPCODE_BIND_MW        = 0x18,
पूर्ण;

क्रमागत अणु
	MTHCA_CMD_USE_EVENTS         = 1 << 0,
	MTHCA_CMD_POST_DOORBELLS     = 1 << 1
पूर्ण;

क्रमागत अणु
	MTHCA_CMD_NUM_DBELL_DWORDS = 8
पूर्ण;

काष्ठा mthca_cmd अणु
	काष्ठा dma_pool          *pool;
	काष्ठा mutex              hcr_mutex;
	काष्ठा semaphore 	  poll_sem;
	काष्ठा semaphore 	  event_sem;
	पूर्णांक              	  max_cmds;
	spinlock_t                context_lock;
	पूर्णांक                       मुक्त_head;
	काष्ठा mthca_cmd_context *context;
	u16                       token_mask;
	u32                       flags;
	व्योम __iomem             *dbell_map;
	u16                       dbell_offsets[MTHCA_CMD_NUM_DBELL_DWORDS];
पूर्ण;

काष्ठा mthca_limits अणु
	पूर्णांक      num_ports;
	पूर्णांक      vl_cap;
	पूर्णांक      mtu_cap;
	पूर्णांक      gid_table_len;
	पूर्णांक      pkey_table_len;
	पूर्णांक      local_ca_ack_delay;
	पूर्णांक      num_uars;
	पूर्णांक      max_sg;
	पूर्णांक      num_qps;
	पूर्णांक      max_wqes;
	पूर्णांक	 max_desc_sz;
	पूर्णांक	 max_qp_init_rdma;
	पूर्णांक      reserved_qps;
	पूर्णांक      num_srqs;
	पूर्णांक      max_srq_wqes;
	पूर्णांक      max_srq_sge;
	पूर्णांक      reserved_srqs;
	पूर्णांक      num_eecs;
	पूर्णांक      reserved_eecs;
	पूर्णांक      num_cqs;
	पूर्णांक      max_cqes;
	पूर्णांक      reserved_cqs;
	पूर्णांक      num_eqs;
	पूर्णांक      reserved_eqs;
	पूर्णांक      num_mpts;
	पूर्णांक      num_mtt_segs;
	पूर्णांक	 mtt_seg_size;
	पूर्णांक      fmr_reserved_mtts;
	पूर्णांक      reserved_mtts;
	पूर्णांक      reserved_mrws;
	पूर्णांक      reserved_uars;
	पूर्णांक      num_mgms;
	पूर्णांक      num_amgms;
	पूर्णांक      reserved_mcgs;
	पूर्णांक      num_pds;
	पूर्णांक      reserved_pds;
	u32      page_size_cap;
	u32      flags;
	u16      stat_rate_support;
	u8       port_width_cap;
पूर्ण;

काष्ठा mthca_alloc अणु
	u32            last;
	u32            top;
	u32            max;
	u32            mask;
	spinlock_t     lock;
	अचिन्हित दीर्घ *table;
पूर्ण;

काष्ठा mthca_array अणु
	काष्ठा अणु
		व्योम    **page;
		पूर्णांक       used;
	पूर्ण *page_list;
पूर्ण;

काष्ठा mthca_uar_table अणु
	काष्ठा mthca_alloc alloc;
	u64                uarc_base;
	पूर्णांक                uarc_size;
पूर्ण;

काष्ठा mthca_pd_table अणु
	काष्ठा mthca_alloc alloc;
पूर्ण;

काष्ठा mthca_buddy अणु
	अचिन्हित दीर्घ **bits;
	पूर्णांक	       *num_मुक्त;
	पूर्णांक             max_order;
	spinlock_t      lock;
पूर्ण;

काष्ठा mthca_mr_table अणु
	काष्ठा mthca_alloc      mpt_alloc;
	काष्ठा mthca_buddy      mtt_buddy;
	काष्ठा mthca_buddy     *fmr_mtt_buddy;
	u64                     mtt_base;
	u64                     mpt_base;
	काष्ठा mthca_icm_table *mtt_table;
	काष्ठा mthca_icm_table *mpt_table;
	काष्ठा अणु
		व्योम __iomem   *mpt_base;
		व्योम __iomem   *mtt_base;
		काष्ठा mthca_buddy mtt_buddy;
	पूर्ण tavor_fmr;
पूर्ण;

काष्ठा mthca_eq_table अणु
	काष्ठा mthca_alloc alloc;
	व्योम __iomem      *clr_पूर्णांक;
	u32                clr_mask;
	u32                arm_mask;
	काष्ठा mthca_eq    eq[MTHCA_NUM_EQ];
	u64                icm_virt;
	काष्ठा page       *icm_page;
	dma_addr_t         icm_dma;
	पूर्णांक                have_irq;
	u8                 पूर्णांकa_pin;
पूर्ण;

काष्ठा mthca_cq_table अणु
	काष्ठा mthca_alloc 	alloc;
	spinlock_t         	lock;
	काष्ठा mthca_array      cq;
	काष्ठा mthca_icm_table *table;
पूर्ण;

काष्ठा mthca_srq_table अणु
	काष्ठा mthca_alloc 	alloc;
	spinlock_t         	lock;
	काष्ठा mthca_array      srq;
	काष्ठा mthca_icm_table *table;
पूर्ण;

काष्ठा mthca_qp_table अणु
	काष्ठा mthca_alloc     	alloc;
	u32                    	rdb_base;
	पूर्णांक                    	rdb_shअगरt;
	पूर्णांक                    	sqp_start;
	spinlock_t             	lock;
	काष्ठा mthca_array     	qp;
	काष्ठा mthca_icm_table *qp_table;
	काष्ठा mthca_icm_table *eqp_table;
	काष्ठा mthca_icm_table *rdb_table;
पूर्ण;

काष्ठा mthca_av_table अणु
	काष्ठा dma_pool   *pool;
	पूर्णांक                num_ddr_avs;
	u64                ddr_av_base;
	व्योम __iomem      *av_map;
	काष्ठा mthca_alloc alloc;
पूर्ण;

काष्ठा mthca_mcg_table अणु
	काष्ठा mutex		mutex;
	काष्ठा mthca_alloc 	alloc;
	काष्ठा mthca_icm_table *table;
पूर्ण;

काष्ठा mthca_catas_err अणु
	u64			addr;
	u32 __iomem	       *map;
	u32			size;
	काष्ठा समयr_list	समयr;
	काष्ठा list_head	list;
पूर्ण;

बाह्य काष्ठा mutex mthca_device_mutex;

काष्ठा mthca_dev अणु
	काष्ठा ib_device  ib_dev;
	काष्ठा pci_dev   *pdev;

	पूर्णांक          	 hca_type;
	अचिन्हित दीर्घ	 mthca_flags;
	अचिन्हित दीर्घ    device_cap_flags;

	u32              rev_id;
	अक्षर             board_id[MTHCA_BOARD_ID_LEN];

	/* firmware info */
	u64              fw_ver;
	जोड़ अणु
		काष्ठा अणु
			u64 fw_start;
			u64 fw_end;
		पूर्ण        tavor;
		काष्ठा अणु
			u64 clr_पूर्णांक_base;
			u64 eq_arm_base;
			u64 eq_set_ci_base;
			काष्ठा mthca_icm *fw_icm;
			काष्ठा mthca_icm *aux_icm;
			u16 fw_pages;
		पूर्ण        arbel;
	पूर्ण                fw;

	u64              ddr_start;
	u64              ddr_end;

	MTHCA_DECLARE_DOORBELL_LOCK(करोorbell_lock)
	काष्ठा mutex cap_mask_mutex;

	व्योम __iomem    *hcr;
	व्योम __iomem    *kar;
	व्योम __iomem    *clr_base;
	जोड़ अणु
		काष्ठा अणु
			व्योम __iomem *ecr_base;
		पूर्ण tavor;
		काष्ठा अणु
			व्योम __iomem *eq_arm;
			व्योम __iomem *eq_set_ci_base;
		पूर्ण arbel;
	पूर्ण eq_regs;

	काष्ठा mthca_cmd    cmd;
	काष्ठा mthca_limits limits;

	काष्ठा mthca_uar_table uar_table;
	काष्ठा mthca_pd_table  pd_table;
	काष्ठा mthca_mr_table  mr_table;
	काष्ठा mthca_eq_table  eq_table;
	काष्ठा mthca_cq_table  cq_table;
	काष्ठा mthca_srq_table srq_table;
	काष्ठा mthca_qp_table  qp_table;
	काष्ठा mthca_av_table  av_table;
	काष्ठा mthca_mcg_table mcg_table;

	काष्ठा mthca_catas_err catas_err;

	काष्ठा mthca_uar       driver_uar;
	काष्ठा mthca_db_table *db_tab;
	काष्ठा mthca_pd        driver_pd;
	काष्ठा mthca_mr        driver_mr;

	काष्ठा ib_mad_agent  *send_agent[MTHCA_MAX_PORTS][2];
	काष्ठा ib_ah         *sm_ah[MTHCA_MAX_PORTS];
	spinlock_t            sm_lock;
	u8                    rate[MTHCA_MAX_PORTS];
	bool		      active;
पूर्ण;

#अगर_घोषित CONFIG_INFINIBAND_MTHCA_DEBUG
बाह्य पूर्णांक mthca_debug_level;

#घोषणा mthca_dbg(mdev, क्रमmat, arg...)					\
	करो अणु								\
		अगर (mthca_debug_level)					\
			dev_prपूर्णांकk(KERN_DEBUG, &mdev->pdev->dev, क्रमmat, ## arg); \
	पूर्ण जबतक (0)

#अन्यथा /* CONFIG_INFINIBAND_MTHCA_DEBUG */

#घोषणा mthca_dbg(mdev, क्रमmat, arg...) करो अणु (व्योम) mdev; पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_INFINIBAND_MTHCA_DEBUG */

#घोषणा mthca_err(mdev, क्रमmat, arg...) \
	dev_err(&mdev->pdev->dev, क्रमmat, ## arg)
#घोषणा mthca_info(mdev, क्रमmat, arg...) \
	dev_info(&mdev->pdev->dev, क्रमmat, ## arg)
#घोषणा mthca_warn(mdev, क्रमmat, arg...) \
	dev_warn(&mdev->pdev->dev, क्रमmat, ## arg)

बाह्य व्योम __buggy_use_of_MTHCA_GET(व्योम);
बाह्य व्योम __buggy_use_of_MTHCA_PUT(व्योम);

#घोषणा MTHCA_GET(dest, source, offset)                               \
	करो अणु                                                          \
		व्योम *__p = (अक्षर *) (source) + (offset);             \
		चयन (माप (dest)) अणु                              \
		हाल 1: (dest) = *(u8 *) __p;       अवरोध;	      \
		हाल 2: (dest) = be16_to_cpup(__p); अवरोध;	      \
		हाल 4: (dest) = be32_to_cpup(__p); अवरोध;	      \
		हाल 8: (dest) = be64_to_cpup(__p); अवरोध;	      \
		शेष: __buggy_use_of_MTHCA_GET();		      \
		पूर्ण                                                     \
	पूर्ण जबतक (0)

#घोषणा MTHCA_PUT(dest, source, offset)                               \
	करो अणु                                                          \
		व्योम *__d = ((अक्षर *) (dest) + (offset));	      \
		चयन (माप(source)) अणु                             \
		हाल 1: *(u8 *) __d = (source);                अवरोध; \
		हाल 2:	*(__be16 *) __d = cpu_to_be16(source); अवरोध; \
		हाल 4:	*(__be32 *) __d = cpu_to_be32(source); अवरोध; \
		हाल 8:	*(__be64 *) __d = cpu_to_be64(source); अवरोध; \
		शेष: __buggy_use_of_MTHCA_PUT();		      \
		पूर्ण                                                     \
	पूर्ण जबतक (0)

पूर्णांक mthca_reset(काष्ठा mthca_dev *mdev);

u32 mthca_alloc(काष्ठा mthca_alloc *alloc);
व्योम mthca_मुक्त(काष्ठा mthca_alloc *alloc, u32 obj);
पूर्णांक mthca_alloc_init(काष्ठा mthca_alloc *alloc, u32 num, u32 mask,
		     u32 reserved);
व्योम mthca_alloc_cleanup(काष्ठा mthca_alloc *alloc);
व्योम *mthca_array_get(काष्ठा mthca_array *array, पूर्णांक index);
पूर्णांक mthca_array_set(काष्ठा mthca_array *array, पूर्णांक index, व्योम *value);
व्योम mthca_array_clear(काष्ठा mthca_array *array, पूर्णांक index);
पूर्णांक mthca_array_init(काष्ठा mthca_array *array, पूर्णांक nent);
व्योम mthca_array_cleanup(काष्ठा mthca_array *array, पूर्णांक nent);
पूर्णांक mthca_buf_alloc(काष्ठा mthca_dev *dev, पूर्णांक size, पूर्णांक max_direct,
		    जोड़ mthca_buf *buf, पूर्णांक *is_direct, काष्ठा mthca_pd *pd,
		    पूर्णांक hca_ग_लिखो, काष्ठा mthca_mr *mr);
व्योम mthca_buf_मुक्त(काष्ठा mthca_dev *dev, पूर्णांक size, जोड़ mthca_buf *buf,
		    पूर्णांक is_direct, काष्ठा mthca_mr *mr);

पूर्णांक mthca_init_uar_table(काष्ठा mthca_dev *dev);
पूर्णांक mthca_init_pd_table(काष्ठा mthca_dev *dev);
पूर्णांक mthca_init_mr_table(काष्ठा mthca_dev *dev);
पूर्णांक mthca_init_eq_table(काष्ठा mthca_dev *dev);
पूर्णांक mthca_init_cq_table(काष्ठा mthca_dev *dev);
पूर्णांक mthca_init_srq_table(काष्ठा mthca_dev *dev);
पूर्णांक mthca_init_qp_table(काष्ठा mthca_dev *dev);
पूर्णांक mthca_init_av_table(काष्ठा mthca_dev *dev);
पूर्णांक mthca_init_mcg_table(काष्ठा mthca_dev *dev);

व्योम mthca_cleanup_uar_table(काष्ठा mthca_dev *dev);
व्योम mthca_cleanup_pd_table(काष्ठा mthca_dev *dev);
व्योम mthca_cleanup_mr_table(काष्ठा mthca_dev *dev);
व्योम mthca_cleanup_eq_table(काष्ठा mthca_dev *dev);
व्योम mthca_cleanup_cq_table(काष्ठा mthca_dev *dev);
व्योम mthca_cleanup_srq_table(काष्ठा mthca_dev *dev);
व्योम mthca_cleanup_qp_table(काष्ठा mthca_dev *dev);
व्योम mthca_cleanup_av_table(काष्ठा mthca_dev *dev);
व्योम mthca_cleanup_mcg_table(काष्ठा mthca_dev *dev);

पूर्णांक mthca_रेजिस्टर_device(काष्ठा mthca_dev *dev);
व्योम mthca_unरेजिस्टर_device(काष्ठा mthca_dev *dev);

व्योम mthca_start_catas_poll(काष्ठा mthca_dev *dev);
व्योम mthca_stop_catas_poll(काष्ठा mthca_dev *dev);
पूर्णांक __mthca_restart_one(काष्ठा pci_dev *pdev);
पूर्णांक mthca_catas_init(व्योम);
व्योम mthca_catas_cleanup(व्योम);

पूर्णांक mthca_uar_alloc(काष्ठा mthca_dev *dev, काष्ठा mthca_uar *uar);
व्योम mthca_uar_मुक्त(काष्ठा mthca_dev *dev, काष्ठा mthca_uar *uar);

पूर्णांक mthca_pd_alloc(काष्ठा mthca_dev *dev, पूर्णांक privileged, काष्ठा mthca_pd *pd);
व्योम mthca_pd_मुक्त(काष्ठा mthca_dev *dev, काष्ठा mthca_pd *pd);

पूर्णांक mthca_ग_लिखो_mtt_size(काष्ठा mthca_dev *dev);

काष्ठा mthca_mtt *mthca_alloc_mtt(काष्ठा mthca_dev *dev, पूर्णांक size);
व्योम mthca_मुक्त_mtt(काष्ठा mthca_dev *dev, काष्ठा mthca_mtt *mtt);
पूर्णांक mthca_ग_लिखो_mtt(काष्ठा mthca_dev *dev, काष्ठा mthca_mtt *mtt,
		    पूर्णांक start_index, u64 *buffer_list, पूर्णांक list_len);
पूर्णांक mthca_mr_alloc(काष्ठा mthca_dev *dev, u32 pd, पूर्णांक buffer_size_shअगरt,
		   u64 iova, u64 total_size, u32 access, काष्ठा mthca_mr *mr);
पूर्णांक mthca_mr_alloc_notrans(काष्ठा mthca_dev *dev, u32 pd,
			   u32 access, काष्ठा mthca_mr *mr);
पूर्णांक mthca_mr_alloc_phys(काष्ठा mthca_dev *dev, u32 pd,
			u64 *buffer_list, पूर्णांक buffer_size_shअगरt,
			पूर्णांक list_len, u64 iova, u64 total_size,
			u32 access, काष्ठा mthca_mr *mr);
व्योम mthca_मुक्त_mr(काष्ठा mthca_dev *dev,  काष्ठा mthca_mr *mr);

पूर्णांक mthca_map_eq_icm(काष्ठा mthca_dev *dev, u64 icm_virt);
व्योम mthca_unmap_eq_icm(काष्ठा mthca_dev *dev);

पूर्णांक mthca_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries,
		  काष्ठा ib_wc *entry);
पूर्णांक mthca_tavor_arm_cq(काष्ठा ib_cq *cq, क्रमागत ib_cq_notअगरy_flags flags);
पूर्णांक mthca_arbel_arm_cq(काष्ठा ib_cq *cq, क्रमागत ib_cq_notअगरy_flags flags);
पूर्णांक mthca_init_cq(काष्ठा mthca_dev *dev, पूर्णांक nent,
		  काष्ठा mthca_ucontext *ctx, u32 pdn,
		  काष्ठा mthca_cq *cq);
व्योम mthca_मुक्त_cq(काष्ठा mthca_dev *dev,
		   काष्ठा mthca_cq *cq);
व्योम mthca_cq_completion(काष्ठा mthca_dev *dev, u32 cqn);
व्योम mthca_cq_event(काष्ठा mthca_dev *dev, u32 cqn,
		    क्रमागत ib_event_type event_type);
व्योम mthca_cq_clean(काष्ठा mthca_dev *dev, काष्ठा mthca_cq *cq, u32 qpn,
		    काष्ठा mthca_srq *srq);
व्योम mthca_cq_resize_copy_cqes(काष्ठा mthca_cq *cq);
पूर्णांक mthca_alloc_cq_buf(काष्ठा mthca_dev *dev, काष्ठा mthca_cq_buf *buf, पूर्णांक nent);
व्योम mthca_मुक्त_cq_buf(काष्ठा mthca_dev *dev, काष्ठा mthca_cq_buf *buf, पूर्णांक cqe);

पूर्णांक mthca_alloc_srq(काष्ठा mthca_dev *dev, काष्ठा mthca_pd *pd,
		    काष्ठा ib_srq_attr *attr, काष्ठा mthca_srq *srq,
		    काष्ठा ib_udata *udata);
व्योम mthca_मुक्त_srq(काष्ठा mthca_dev *dev, काष्ठा mthca_srq *srq);
पूर्णांक mthca_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
		     क्रमागत ib_srq_attr_mask attr_mask, काष्ठा ib_udata *udata);
पूर्णांक mthca_query_srq(काष्ठा ib_srq *srq, काष्ठा ib_srq_attr *srq_attr);
पूर्णांक mthca_max_srq_sge(काष्ठा mthca_dev *dev);
व्योम mthca_srq_event(काष्ठा mthca_dev *dev, u32 srqn,
		     क्रमागत ib_event_type event_type);
व्योम mthca_मुक्त_srq_wqe(काष्ठा mthca_srq *srq, u32 wqe_addr);
पूर्णांक mthca_tavor_post_srq_recv(काष्ठा ib_srq *srq, स्थिर काष्ठा ib_recv_wr *wr,
			      स्थिर काष्ठा ib_recv_wr **bad_wr);
पूर्णांक mthca_arbel_post_srq_recv(काष्ठा ib_srq *srq, स्थिर काष्ठा ib_recv_wr *wr,
			      स्थिर काष्ठा ib_recv_wr **bad_wr);

व्योम mthca_qp_event(काष्ठा mthca_dev *dev, u32 qpn,
		    क्रमागत ib_event_type event_type);
पूर्णांक mthca_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr, पूर्णांक qp_attr_mask,
		   काष्ठा ib_qp_init_attr *qp_init_attr);
पूर्णांक mthca_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask,
		    काष्ठा ib_udata *udata);
पूर्णांक mthca_tavor_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
			  स्थिर काष्ठा ib_send_wr **bad_wr);
पूर्णांक mthca_tavor_post_receive(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
			     स्थिर काष्ठा ib_recv_wr **bad_wr);
पूर्णांक mthca_arbel_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
			  स्थिर काष्ठा ib_send_wr **bad_wr);
पूर्णांक mthca_arbel_post_receive(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
			     स्थिर काष्ठा ib_recv_wr **bad_wr);
व्योम mthca_मुक्त_err_wqe(काष्ठा mthca_dev *dev, काष्ठा mthca_qp *qp, पूर्णांक is_send,
			पूर्णांक index, पूर्णांक *dbd, __be32 *new_wqe);
पूर्णांक mthca_alloc_qp(काष्ठा mthca_dev *dev,
		   काष्ठा mthca_pd *pd,
		   काष्ठा mthca_cq *send_cq,
		   काष्ठा mthca_cq *recv_cq,
		   क्रमागत ib_qp_type type,
		   क्रमागत ib_sig_type send_policy,
		   काष्ठा ib_qp_cap *cap,
		   काष्ठा mthca_qp *qp,
		   काष्ठा ib_udata *udata);
पूर्णांक mthca_alloc_sqp(काष्ठा mthca_dev *dev,
		    काष्ठा mthca_pd *pd,
		    काष्ठा mthca_cq *send_cq,
		    काष्ठा mthca_cq *recv_cq,
		    क्रमागत ib_sig_type send_policy,
		    काष्ठा ib_qp_cap *cap,
		    पूर्णांक qpn,
		    u32 port,
		    काष्ठा mthca_qp *qp,
		    काष्ठा ib_udata *udata);
व्योम mthca_मुक्त_qp(काष्ठा mthca_dev *dev, काष्ठा mthca_qp *qp);
पूर्णांक mthca_create_ah(काष्ठा mthca_dev *dev,
		    काष्ठा mthca_pd *pd,
		    काष्ठा rdma_ah_attr *ah_attr,
		    काष्ठा mthca_ah *ah);
पूर्णांक mthca_destroy_ah(काष्ठा mthca_dev *dev, काष्ठा mthca_ah *ah);
पूर्णांक mthca_पढ़ो_ah(काष्ठा mthca_dev *dev, काष्ठा mthca_ah *ah,
		  काष्ठा ib_ud_header *header);
पूर्णांक mthca_ah_query(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *attr);
पूर्णांक mthca_ah_grh_present(काष्ठा mthca_ah *ah);
u8 mthca_get_rate(काष्ठा mthca_dev *dev, पूर्णांक अटल_rate, u32 port);
क्रमागत ib_rate mthca_rate_to_ib(काष्ठा mthca_dev *dev, u8 mthca_rate, u32 port);

पूर्णांक mthca_multicast_attach(काष्ठा ib_qp *ibqp, जोड़ ib_gid *gid, u16 lid);
पूर्णांक mthca_multicast_detach(काष्ठा ib_qp *ibqp, जोड़ ib_gid *gid, u16 lid);

पूर्णांक mthca_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port_num,
		      स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
		      स्थिर काष्ठा ib_mad *in, काष्ठा ib_mad *out,
		      माप_प्रकार *out_mad_size, u16 *out_mad_pkey_index);
पूर्णांक mthca_create_agents(काष्ठा mthca_dev *dev);
व्योम mthca_मुक्त_agents(काष्ठा mthca_dev *dev);

अटल अंतरभूत काष्ठा mthca_dev *to_mdev(काष्ठा ib_device *ibdev)
अणु
	वापस container_of(ibdev, काष्ठा mthca_dev, ib_dev);
पूर्ण

अटल अंतरभूत पूर्णांक mthca_is_memमुक्त(काष्ठा mthca_dev *dev)
अणु
	वापस dev->mthca_flags & MTHCA_FLAG_MEMFREE;
पूर्ण

#पूर्ण_अगर /* MTHCA_DEV_H */
