<शैली गुरु>
/*
 * Copyright (c) 2009-2010 Chelsio, Inc. All rights reserved.
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
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *      - Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
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
#अगर_अघोषित __IW_CXGB4_H__
#घोषणा __IW_CXGB4_H__

#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/xarray.h>
#समावेश <linux/completion.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/inet.h>
#समावेश <linux/रुको.h>
#समावेश <linux/kref.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/byteorder.h>

#समावेश <net/net_namespace.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/iw_cm.h>
#समावेश <rdma/rdma_netlink.h>
#समावेश <rdma/iw_porपंचांगap.h>
#समावेश <rdma/restrack.h>

#समावेश "cxgb4.h"
#समावेश "cxgb4_uld.h"
#समावेश "l2t.h"
#समावेश <rdma/cxgb4-abi.h>

#घोषणा DRV_NAME "iw_cxgb4"
#घोषणा MOD DRV_NAME ":"

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "t4.h"

#घोषणा PBL_OFF(rdev_p, a) ((a) - (rdev_p)->lldi.vr->pbl.start)
#घोषणा RQT_OFF(rdev_p, a) ((a) - (rdev_p)->lldi.vr->rq.start)

अटल अंतरभूत व्योम *cplhdr(काष्ठा sk_buff *skb)
अणु
	वापस skb->data;
पूर्ण

#घोषणा C4IW_ID_TABLE_F_RANDOM 1       /* Pseuकरो-अक्रमomize the id's वापसed */
#घोषणा C4IW_ID_TABLE_F_EMPTY  2       /* Table is initially empty */

काष्ठा c4iw_id_table अणु
	u32 flags;
	u32 start;              /* logical minimal id */
	u32 last;               /* hपूर्णांक क्रम find */
	u32 max;
	spinlock_t lock;
	अचिन्हित दीर्घ *table;
पूर्ण;

काष्ठा c4iw_resource अणु
	काष्ठा c4iw_id_table tpt_table;
	काष्ठा c4iw_id_table qid_table;
	काष्ठा c4iw_id_table pdid_table;
	काष्ठा c4iw_id_table srq_table;
पूर्ण;

काष्ठा c4iw_qid_list अणु
	काष्ठा list_head entry;
	u32 qid;
पूर्ण;

काष्ठा c4iw_dev_ucontext अणु
	काष्ठा list_head qpids;
	काष्ठा list_head cqids;
	काष्ठा mutex lock;
	काष्ठा kref kref;
पूर्ण;

क्रमागत c4iw_rdev_flags अणु
	T4_FATAL_ERROR = (1<<0),
	T4_STATUS_PAGE_DISABLED = (1<<1),
पूर्ण;

काष्ठा c4iw_stat अणु
	u64 total;
	u64 cur;
	u64 max;
	u64 fail;
पूर्ण;

काष्ठा c4iw_stats अणु
	काष्ठा mutex lock;
	काष्ठा c4iw_stat qid;
	काष्ठा c4iw_stat pd;
	काष्ठा c4iw_stat stag;
	काष्ठा c4iw_stat pbl;
	काष्ठा c4iw_stat rqt;
	काष्ठा c4iw_stat srqt;
	काष्ठा c4iw_stat srq;
	काष्ठा c4iw_stat ocqp;
	u64  db_full;
	u64  db_empty;
	u64  db_drop;
	u64  db_state_transitions;
	u64  db_fc_पूर्णांकerruptions;
	u64  tcam_full;
	u64  act_ofld_conn_fails;
	u64  pas_ofld_conn_fails;
	u64  neg_adv;
पूर्ण;

काष्ठा c4iw_hw_queue अणु
	पूर्णांक t4_eq_status_entries;
	पूर्णांक t4_max_eq_size;
	पूर्णांक t4_max_iq_size;
	पूर्णांक t4_max_rq_size;
	पूर्णांक t4_max_sq_size;
	पूर्णांक t4_max_qp_depth;
	पूर्णांक t4_max_cq_depth;
	पूर्णांक t4_stat_len;
पूर्ण;

काष्ठा wr_log_entry अणु
	kसमय_प्रकार post_host_समय;
	kसमय_प्रकार poll_host_समय;
	u64 post_sge_ts;
	u64 cqe_sge_ts;
	u64 poll_sge_ts;
	u16 qid;
	u16 wr_id;
	u8 opcode;
	u8 valid;
पूर्ण;

काष्ठा c4iw_rdev अणु
	काष्ठा c4iw_resource resource;
	u32 qpmask;
	u32 cqmask;
	काष्ठा c4iw_dev_ucontext uctx;
	काष्ठा gen_pool *pbl_pool;
	काष्ठा gen_pool *rqt_pool;
	काष्ठा gen_pool *ocqp_pool;
	u32 flags;
	काष्ठा cxgb4_lld_info lldi;
	अचिन्हित दीर्घ bar2_pa;
	व्योम __iomem *bar2_kva;
	अचिन्हित दीर्घ oc_mw_pa;
	व्योम __iomem *oc_mw_kva;
	काष्ठा c4iw_stats stats;
	काष्ठा c4iw_hw_queue hw_queue;
	काष्ठा t4_dev_status_page *status_page;
	atomic_t wr_log_idx;
	काष्ठा wr_log_entry *wr_log;
	पूर्णांक wr_log_size;
	काष्ठा workqueue_काष्ठा *मुक्त_workq;
	काष्ठा completion rqt_compl;
	काष्ठा completion pbl_compl;
	काष्ठा kref rqt_kref;
	काष्ठा kref pbl_kref;
पूर्ण;

अटल अंतरभूत पूर्णांक c4iw_fatal_error(काष्ठा c4iw_rdev *rdev)
अणु
	वापस rdev->flags & T4_FATAL_ERROR;
पूर्ण

अटल अंतरभूत पूर्णांक c4iw_num_stags(काष्ठा c4iw_rdev *rdev)
अणु
	वापस (पूर्णांक)(rdev->lldi.vr->stag.size >> 5);
पूर्ण

#घोषणा C4IW_WR_TO (60*HZ)

काष्ठा c4iw_wr_रुको अणु
	काष्ठा completion completion;
	पूर्णांक ret;
	काष्ठा kref kref;
पूर्ण;

व्योम _c4iw_मुक्त_wr_रुको(काष्ठा kref *kref);

अटल अंतरभूत व्योम c4iw_put_wr_रुको(काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	pr_debug("wr_wait %p ref before put %u\n", wr_रुकोp,
		 kref_पढ़ो(&wr_रुकोp->kref));
	WARN_ON(kref_पढ़ो(&wr_रुकोp->kref) == 0);
	kref_put(&wr_रुकोp->kref, _c4iw_मुक्त_wr_रुको);
पूर्ण

अटल अंतरभूत व्योम c4iw_get_wr_रुको(काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	pr_debug("wr_wait %p ref before get %u\n", wr_रुकोp,
		 kref_पढ़ो(&wr_रुकोp->kref));
	WARN_ON(kref_पढ़ो(&wr_रुकोp->kref) == 0);
	kref_get(&wr_रुकोp->kref);
पूर्ण

अटल अंतरभूत व्योम c4iw_init_wr_रुको(काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	wr_रुकोp->ret = 0;
	init_completion(&wr_रुकोp->completion);
पूर्ण

अटल अंतरभूत व्योम _c4iw_wake_up(काष्ठा c4iw_wr_रुको *wr_रुकोp, पूर्णांक ret,
				 bool deref)
अणु
	wr_रुकोp->ret = ret;
	complete(&wr_रुकोp->completion);
	अगर (deref)
		c4iw_put_wr_रुको(wr_रुकोp);
पूर्ण

अटल अंतरभूत व्योम c4iw_wake_up_noref(काष्ठा c4iw_wr_रुको *wr_रुकोp, पूर्णांक ret)
अणु
	_c4iw_wake_up(wr_रुकोp, ret, false);
पूर्ण

अटल अंतरभूत व्योम c4iw_wake_up_deref(काष्ठा c4iw_wr_रुको *wr_रुकोp, पूर्णांक ret)
अणु
	_c4iw_wake_up(wr_रुकोp, ret, true);
पूर्ण

अटल अंतरभूत पूर्णांक c4iw_रुको_क्रम_reply(काष्ठा c4iw_rdev *rdev,
				 काष्ठा c4iw_wr_रुको *wr_रुकोp,
				 u32 hwtid, u32 qpid,
				 स्थिर अक्षर *func)
अणु
	पूर्णांक ret;

	अगर (c4iw_fatal_error(rdev)) अणु
		wr_रुकोp->ret = -EIO;
		जाओ out;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&wr_रुकोp->completion, C4IW_WR_TO);
	अगर (!ret) अणु
		pr_err("%s - Device %s not responding (disabling device) - tid %u qpid %u\n",
		       func, pci_name(rdev->lldi.pdev), hwtid, qpid);
		rdev->flags |= T4_FATAL_ERROR;
		wr_रुकोp->ret = -EIO;
		जाओ out;
	पूर्ण
	अगर (wr_रुकोp->ret)
		pr_debug("%s: FW reply %d tid %u qpid %u\n",
			 pci_name(rdev->lldi.pdev), wr_रुकोp->ret, hwtid, qpid);
out:
	वापस wr_रुकोp->ret;
पूर्ण

पूर्णांक c4iw_ofld_send(काष्ठा c4iw_rdev *rdev, काष्ठा sk_buff *skb);

अटल अंतरभूत पूर्णांक c4iw_ref_send_रुको(काष्ठा c4iw_rdev *rdev,
				     काष्ठा sk_buff *skb,
				     काष्ठा c4iw_wr_रुको *wr_रुकोp,
				     u32 hwtid, u32 qpid,
				     स्थिर अक्षर *func)
अणु
	पूर्णांक ret;

	pr_debug("%s wr_wait %p hwtid %u qpid %u\n", func, wr_रुकोp, hwtid,
		 qpid);
	c4iw_get_wr_रुको(wr_रुकोp);
	ret = c4iw_ofld_send(rdev, skb);
	अगर (ret) अणु
		c4iw_put_wr_रुको(wr_रुकोp);
		वापस ret;
	पूर्ण
	वापस c4iw_रुको_क्रम_reply(rdev, wr_रुकोp, hwtid, qpid, func);
पूर्ण

क्रमागत db_state अणु
	NORMAL = 0,
	FLOW_CONTROL = 1,
	RECOVERY = 2,
	STOPPED = 3
पूर्ण;

काष्ठा c4iw_dev अणु
	काष्ठा ib_device ibdev;
	काष्ठा c4iw_rdev rdev;
	u32 device_cap_flags;
	काष्ठा xarray cqs;
	काष्ठा xarray qps;
	काष्ठा xarray mrs;
	काष्ठा mutex db_mutex;
	काष्ठा dentry *debugfs_root;
	क्रमागत db_state db_state;
	काष्ठा xarray hwtids;
	काष्ठा xarray atids;
	काष्ठा xarray stids;
	काष्ठा list_head db_fc_list;
	u32 avail_ird;
	रुको_queue_head_t रुको;
पूर्ण;

काष्ठा uld_ctx अणु
	काष्ठा list_head entry;
	काष्ठा cxgb4_lld_info lldi;
	काष्ठा c4iw_dev *dev;
	काष्ठा work_काष्ठा reg_work;
पूर्ण;

अटल अंतरभूत काष्ठा c4iw_dev *to_c4iw_dev(काष्ठा ib_device *ibdev)
अणु
	वापस container_of(ibdev, काष्ठा c4iw_dev, ibdev);
पूर्ण

अटल अंतरभूत काष्ठा c4iw_cq *get_chp(काष्ठा c4iw_dev *rhp, u32 cqid)
अणु
	वापस xa_load(&rhp->cqs, cqid);
पूर्ण

अटल अंतरभूत काष्ठा c4iw_qp *get_qhp(काष्ठा c4iw_dev *rhp, u32 qpid)
अणु
	वापस xa_load(&rhp->qps, qpid);
पूर्ण

बाह्य uपूर्णांक c4iw_max_पढ़ो_depth;

अटल अंतरभूत पूर्णांक cur_max_पढ़ो_depth(काष्ठा c4iw_dev *dev)
अणु
	वापस min(dev->rdev.lldi.max_ordird_qp, c4iw_max_पढ़ो_depth);
पूर्ण

काष्ठा c4iw_pd अणु
	काष्ठा ib_pd ibpd;
	u32 pdid;
	काष्ठा c4iw_dev *rhp;
पूर्ण;

अटल अंतरभूत काष्ठा c4iw_pd *to_c4iw_pd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा c4iw_pd, ibpd);
पूर्ण

काष्ठा tpt_attributes अणु
	u64 len;
	u64 va_fbo;
	क्रमागत fw_ri_mem_perms perms;
	u32 stag;
	u32 pdid;
	u32 qpid;
	u32 pbl_addr;
	u32 pbl_size;
	u32 state:1;
	u32 type:2;
	u32 rsvd:1;
	u32 remote_invaliate_disable:1;
	u32 zbva:1;
	u32 mw_bind_enable:1;
	u32 page_size:5;
पूर्ण;

काष्ठा c4iw_mr अणु
	काष्ठा ib_mr ibmr;
	काष्ठा ib_umem *umem;
	काष्ठा c4iw_dev *rhp;
	काष्ठा sk_buff *dereg_skb;
	u64 kva;
	काष्ठा tpt_attributes attr;
	u64 *mpl;
	dma_addr_t mpl_addr;
	u32 max_mpl_len;
	u32 mpl_len;
	काष्ठा c4iw_wr_रुको *wr_रुकोp;
पूर्ण;

अटल अंतरभूत काष्ठा c4iw_mr *to_c4iw_mr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा c4iw_mr, ibmr);
पूर्ण

काष्ठा c4iw_mw अणु
	काष्ठा ib_mw ibmw;
	काष्ठा c4iw_dev *rhp;
	काष्ठा sk_buff *dereg_skb;
	u64 kva;
	काष्ठा tpt_attributes attr;
	काष्ठा c4iw_wr_रुको *wr_रुकोp;
पूर्ण;

अटल अंतरभूत काष्ठा c4iw_mw *to_c4iw_mw(काष्ठा ib_mw *ibmw)
अणु
	वापस container_of(ibmw, काष्ठा c4iw_mw, ibmw);
पूर्ण

काष्ठा c4iw_cq अणु
	काष्ठा ib_cq ibcq;
	काष्ठा c4iw_dev *rhp;
	काष्ठा sk_buff *destroy_skb;
	काष्ठा t4_cq cq;
	spinlock_t lock;
	spinlock_t comp_handler_lock;
	atomic_t refcnt;
	रुको_queue_head_t रुको;
	काष्ठा c4iw_wr_रुको *wr_रुकोp;
पूर्ण;

अटल अंतरभूत काष्ठा c4iw_cq *to_c4iw_cq(काष्ठा ib_cq *ibcq)
अणु
	वापस container_of(ibcq, काष्ठा c4iw_cq, ibcq);
पूर्ण

काष्ठा c4iw_mpa_attributes अणु
	u8 initiator;
	u8 recv_marker_enabled;
	u8 xmit_marker_enabled;
	u8 crc_enabled;
	u8 enhanced_rdma_conn;
	u8 version;
	u8 p2p_type;
पूर्ण;

काष्ठा c4iw_qp_attributes अणु
	u32 scq;
	u32 rcq;
	u32 sq_num_entries;
	u32 rq_num_entries;
	u32 sq_max_sges;
	u32 sq_max_sges_rdma_ग_लिखो;
	u32 rq_max_sges;
	u32 state;
	u8 enable_rdma_पढ़ो;
	u8 enable_rdma_ग_लिखो;
	u8 enable_bind;
	u8 enable_mmid0_fastreg;
	u32 max_ord;
	u32 max_ird;
	u32 pd;
	u32 next_state;
	अक्षर terminate_buffer[52];
	u32 terminate_msg_len;
	u8 is_terminate_local;
	काष्ठा c4iw_mpa_attributes mpa_attr;
	काष्ठा c4iw_ep *llp_stream_handle;
	u8 layer_etype;
	u8 ecode;
	u16 sq_db_inc;
	u16 rq_db_inc;
	u8 send_term;
पूर्ण;

काष्ठा c4iw_qp अणु
	काष्ठा ib_qp ibqp;
	काष्ठा list_head db_fc_entry;
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_ep *ep;
	काष्ठा c4iw_qp_attributes attr;
	काष्ठा t4_wq wq;
	spinlock_t lock;
	काष्ठा mutex mutex;
	रुको_queue_head_t रुको;
	पूर्णांक sq_sig_all;
	काष्ठा c4iw_srq *srq;
	काष्ठा c4iw_ucontext *ucontext;
	काष्ठा c4iw_wr_रुको *wr_रुकोp;
	काष्ठा completion qp_rel_comp;
	refcount_t qp_refcnt;
पूर्ण;

अटल अंतरभूत काष्ठा c4iw_qp *to_c4iw_qp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा c4iw_qp, ibqp);
पूर्ण

काष्ठा c4iw_srq अणु
	काष्ठा ib_srq ibsrq;
	काष्ठा list_head db_fc_entry;
	काष्ठा c4iw_dev *rhp;
	काष्ठा t4_srq wq;
	काष्ठा sk_buff *destroy_skb;
	u32 srq_limit;
	u32 pdid;
	पूर्णांक idx;
	u32 flags;
	spinlock_t lock; /* protects srq */
	काष्ठा c4iw_wr_रुको *wr_रुकोp;
	bool armed;
पूर्ण;

अटल अंतरभूत काष्ठा c4iw_srq *to_c4iw_srq(काष्ठा ib_srq *ibsrq)
अणु
	वापस container_of(ibsrq, काष्ठा c4iw_srq, ibsrq);
पूर्ण

काष्ठा c4iw_ucontext अणु
	काष्ठा ib_ucontext ibucontext;
	काष्ठा c4iw_dev_ucontext uctx;
	u32 key;
	spinlock_t mmap_lock;
	काष्ठा list_head mmaps;
	bool is_32b_cqe;
पूर्ण;

अटल अंतरभूत काष्ठा c4iw_ucontext *to_c4iw_ucontext(काष्ठा ib_ucontext *c)
अणु
	वापस container_of(c, काष्ठा c4iw_ucontext, ibucontext);
पूर्ण

काष्ठा c4iw_mm_entry अणु
	काष्ठा list_head entry;
	u64 addr;
	u32 key;
	अचिन्हित len;
पूर्ण;

अटल अंतरभूत काष्ठा c4iw_mm_entry *हटाओ_mmap(काष्ठा c4iw_ucontext *ucontext,
						u32 key, अचिन्हित len)
अणु
	काष्ठा list_head *pos, *nxt;
	काष्ठा c4iw_mm_entry *mm;

	spin_lock(&ucontext->mmap_lock);
	list_क्रम_each_safe(pos, nxt, &ucontext->mmaps) अणु

		mm = list_entry(pos, काष्ठा c4iw_mm_entry, entry);
		अगर (mm->key == key && mm->len == len) अणु
			list_del_init(&mm->entry);
			spin_unlock(&ucontext->mmap_lock);
			pr_debug("key 0x%x addr 0x%llx len %d\n", key,
				 (अचिन्हित दीर्घ दीर्घ)mm->addr, mm->len);
			वापस mm;
		पूर्ण
	पूर्ण
	spin_unlock(&ucontext->mmap_lock);
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम insert_mmap(काष्ठा c4iw_ucontext *ucontext,
			       काष्ठा c4iw_mm_entry *mm)
अणु
	spin_lock(&ucontext->mmap_lock);
	pr_debug("key 0x%x addr 0x%llx len %d\n",
		 mm->key, (अचिन्हित दीर्घ दीर्घ)mm->addr, mm->len);
	list_add_tail(&mm->entry, &ucontext->mmaps);
	spin_unlock(&ucontext->mmap_lock);
पूर्ण

क्रमागत c4iw_qp_attr_mask अणु
	C4IW_QP_ATTR_NEXT_STATE = 1 << 0,
	C4IW_QP_ATTR_SQ_DB = 1<<1,
	C4IW_QP_ATTR_RQ_DB = 1<<2,
	C4IW_QP_ATTR_ENABLE_RDMA_READ = 1 << 7,
	C4IW_QP_ATTR_ENABLE_RDMA_WRITE = 1 << 8,
	C4IW_QP_ATTR_ENABLE_RDMA_BIND = 1 << 9,
	C4IW_QP_ATTR_MAX_ORD = 1 << 11,
	C4IW_QP_ATTR_MAX_IRD = 1 << 12,
	C4IW_QP_ATTR_LLP_STREAM_HANDLE = 1 << 22,
	C4IW_QP_ATTR_STREAM_MSG_BUFFER = 1 << 23,
	C4IW_QP_ATTR_MPA_ATTR = 1 << 24,
	C4IW_QP_ATTR_QP_CONTEXT_ACTIVATE = 1 << 25,
	C4IW_QP_ATTR_VALID_MODIFY = (C4IW_QP_ATTR_ENABLE_RDMA_READ |
				     C4IW_QP_ATTR_ENABLE_RDMA_WRITE |
				     C4IW_QP_ATTR_MAX_ORD |
				     C4IW_QP_ATTR_MAX_IRD |
				     C4IW_QP_ATTR_LLP_STREAM_HANDLE |
				     C4IW_QP_ATTR_STREAM_MSG_BUFFER |
				     C4IW_QP_ATTR_MPA_ATTR |
				     C4IW_QP_ATTR_QP_CONTEXT_ACTIVATE)
पूर्ण;

पूर्णांक c4iw_modअगरy_qp(काष्ठा c4iw_dev *rhp,
				काष्ठा c4iw_qp *qhp,
				क्रमागत c4iw_qp_attr_mask mask,
				काष्ठा c4iw_qp_attributes *attrs,
				पूर्णांक पूर्णांकernal);

क्रमागत c4iw_qp_state अणु
	C4IW_QP_STATE_IDLE,
	C4IW_QP_STATE_RTS,
	C4IW_QP_STATE_ERROR,
	C4IW_QP_STATE_TERMINATE,
	C4IW_QP_STATE_CLOSING,
	C4IW_QP_STATE_TOT
पूर्ण;

अटल अंतरभूत पूर्णांक c4iw_convert_state(क्रमागत ib_qp_state ib_state)
अणु
	चयन (ib_state) अणु
	हाल IB_QPS_RESET:
	हाल IB_QPS_INIT:
		वापस C4IW_QP_STATE_IDLE;
	हाल IB_QPS_RTS:
		वापस C4IW_QP_STATE_RTS;
	हाल IB_QPS_SQD:
		वापस C4IW_QP_STATE_CLOSING;
	हाल IB_QPS_SQE:
		वापस C4IW_QP_STATE_TERMINATE;
	हाल IB_QPS_ERR:
		वापस C4IW_QP_STATE_ERROR;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक to_ib_qp_state(पूर्णांक c4iw_qp_state)
अणु
	चयन (c4iw_qp_state) अणु
	हाल C4IW_QP_STATE_IDLE:
		वापस IB_QPS_INIT;
	हाल C4IW_QP_STATE_RTS:
		वापस IB_QPS_RTS;
	हाल C4IW_QP_STATE_CLOSING:
		वापस IB_QPS_SQD;
	हाल C4IW_QP_STATE_TERMINATE:
		वापस IB_QPS_SQE;
	हाल C4IW_QP_STATE_ERROR:
		वापस IB_QPS_ERR;
	पूर्ण
	वापस IB_QPS_ERR;
पूर्ण

अटल अंतरभूत u32 c4iw_ib_to_tpt_access(पूर्णांक a)
अणु
	वापस (a & IB_ACCESS_REMOTE_WRITE ? FW_RI_MEM_ACCESS_REM_WRITE : 0) |
	       (a & IB_ACCESS_REMOTE_READ ? FW_RI_MEM_ACCESS_REM_READ : 0) |
	       (a & IB_ACCESS_LOCAL_WRITE ? FW_RI_MEM_ACCESS_LOCAL_WRITE : 0) |
	       FW_RI_MEM_ACCESS_LOCAL_READ;
पूर्ण

क्रमागत c4iw_mmid_state अणु
	C4IW_STAG_STATE_VALID,
	C4IW_STAG_STATE_INVALID
पूर्ण;

#घोषणा C4IW_NODE_DESC "cxgb4 Chelsio Communications"

#घोषणा MPA_KEY_REQ "MPA ID Req Frame"
#घोषणा MPA_KEY_REP "MPA ID Rep Frame"

#घोषणा MPA_MAX_PRIVATE_DATA	256
#घोषणा MPA_ENHANCED_RDMA_CONN	0x10
#घोषणा MPA_REJECT		0x20
#घोषणा MPA_CRC			0x40
#घोषणा MPA_MARKERS		0x80
#घोषणा MPA_FLAGS_MASK		0xE0

#घोषणा MPA_V2_PEER2PEER_MODEL          0x8000
#घोषणा MPA_V2_ZERO_LEN_FPDU_RTR        0x4000
#घोषणा MPA_V2_RDMA_WRITE_RTR           0x8000
#घोषणा MPA_V2_RDMA_READ_RTR            0x4000
#घोषणा MPA_V2_IRD_ORD_MASK             0x3FFF

#घोषणा c4iw_put_ep(ep) अणु						\
	pr_debug("put_ep ep %p refcnt %d\n",		\
		 ep, kref_पढ़ो(&((ep)->kref)));				\
	WARN_ON(kref_पढ़ो(&((ep)->kref)) < 1);				\
	kref_put(&((ep)->kref), _c4iw_मुक्त_ep);				\
पूर्ण

#घोषणा c4iw_get_ep(ep) अणु						\
	pr_debug("get_ep ep %p, refcnt %d\n",		\
		 ep, kref_पढ़ो(&((ep)->kref)));				\
	kref_get(&((ep)->kref));					\
पूर्ण
व्योम _c4iw_मुक्त_ep(काष्ठा kref *kref);

काष्ठा mpa_message अणु
	u8 key[16];
	u8 flags;
	u8 revision;
	__be16 निजी_data_size;
	u8 निजी_data[];
पूर्ण;

काष्ठा mpa_v2_conn_params अणु
	__be16 ird;
	__be16 ord;
पूर्ण;

काष्ठा terminate_message अणु
	u8 layer_etype;
	u8 ecode;
	__be16 hdrct_rsvd;
	u8 len_hdrs[];
पूर्ण;

#घोषणा TERM_MAX_LENGTH (माप(काष्ठा terminate_message) + 2 + 18 + 28)

क्रमागत c4iw_layers_types अणु
	LAYER_RDMAP		= 0x00,
	LAYER_DDP		= 0x10,
	LAYER_MPA		= 0x20,
	RDMAP_LOCAL_CATA	= 0x00,
	RDMAP_REMOTE_PROT	= 0x01,
	RDMAP_REMOTE_OP		= 0x02,
	DDP_LOCAL_CATA		= 0x00,
	DDP_TAGGED_ERR		= 0x01,
	DDP_UNTAGGED_ERR	= 0x02,
	DDP_LLP			= 0x03
पूर्ण;

क्रमागत c4iw_rdma_ecodes अणु
	RDMAP_INV_STAG		= 0x00,
	RDMAP_BASE_BOUNDS	= 0x01,
	RDMAP_ACC_VIOL		= 0x02,
	RDMAP_STAG_NOT_ASSOC	= 0x03,
	RDMAP_TO_WRAP		= 0x04,
	RDMAP_INV_VERS		= 0x05,
	RDMAP_INV_OPCODE	= 0x06,
	RDMAP_STREAM_CATA	= 0x07,
	RDMAP_GLOBAL_CATA	= 0x08,
	RDMAP_CANT_INV_STAG	= 0x09,
	RDMAP_UNSPECIFIED	= 0xff
पूर्ण;

क्रमागत c4iw_ddp_ecodes अणु
	DDPT_INV_STAG		= 0x00,
	DDPT_BASE_BOUNDS	= 0x01,
	DDPT_STAG_NOT_ASSOC	= 0x02,
	DDPT_TO_WRAP		= 0x03,
	DDPT_INV_VERS		= 0x04,
	DDPU_INV_QN		= 0x01,
	DDPU_INV_MSN_NOBUF	= 0x02,
	DDPU_INV_MSN_RANGE	= 0x03,
	DDPU_INV_MO		= 0x04,
	DDPU_MSG_TOOBIG		= 0x05,
	DDPU_INV_VERS		= 0x06
पूर्ण;

क्रमागत c4iw_mpa_ecodes अणु
	MPA_CRC_ERR		= 0x02,
	MPA_MARKER_ERR          = 0x03,
	MPA_LOCAL_CATA          = 0x05,
	MPA_INSUFF_IRD          = 0x06,
	MPA_NOMATCH_RTR         = 0x07,
पूर्ण;

क्रमागत c4iw_ep_state अणु
	IDLE = 0,
	LISTEN,
	CONNECTING,
	MPA_REQ_WAIT,
	MPA_REQ_SENT,
	MPA_REQ_RCVD,
	MPA_REP_SENT,
	FPDU_MODE,
	ABORTING,
	CLOSING,
	MORIBUND,
	DEAD,
पूर्ण;

क्रमागत c4iw_ep_flags अणु
	PEER_ABORT_IN_PROGRESS	= 0,
	ABORT_REQ_IN_PROGRESS	= 1,
	RELEASE_RESOURCES	= 2,
	CLOSE_SENT		= 3,
	TIMEOUT                 = 4,
	QP_REFERENCED           = 5,
	STOP_MPA_TIMER		= 7,
पूर्ण;

क्रमागत c4iw_ep_history अणु
	ACT_OPEN_REQ            = 0,
	ACT_OFLD_CONN           = 1,
	ACT_OPEN_RPL            = 2,
	ACT_ESTAB               = 3,
	PASS_ACCEPT_REQ         = 4,
	PASS_ESTAB              = 5,
	ABORT_UPCALL            = 6,
	ESTAB_UPCALL            = 7,
	CLOSE_UPCALL            = 8,
	ULP_ACCEPT              = 9,
	ULP_REJECT              = 10,
	TIMEDOUT                = 11,
	PEER_ABORT              = 12,
	PEER_CLOSE              = 13,
	CONNREQ_UPCALL          = 14,
	ABORT_CONN              = 15,
	DISCONN_UPCALL          = 16,
	EP_DISC_CLOSE           = 17,
	EP_DISC_ABORT           = 18,
	CONN_RPL_UPCALL         = 19,
	ACT_RETRY_NOMEM         = 20,
	ACT_RETRY_INUSE         = 21,
	CLOSE_CON_RPL		= 22,
	EP_DISC_FAIL		= 24,
	QP_REFED		= 25,
	QP_DEREFED		= 26,
	CM_ID_REFED		= 27,
	CM_ID_DEREFED		= 28,
पूर्ण;

क्रमागत conn_pre_alloc_buffers अणु
	CN_ABORT_REQ_BUF,
	CN_ABORT_RPL_BUF,
	CN_CLOSE_CON_REQ_BUF,
	CN_DESTROY_BUF,
	CN_FLOWC_BUF,
	CN_MAX_CON_BUF
पूर्ण;

क्रमागत अणु
	FLOWC_LEN = दुरत्व(काष्ठा fw_flowc_wr, mnemval[FW_FLOWC_MNEM_MAX])
पूर्ण;

जोड़ cpl_wr_size अणु
	काष्ठा cpl_पात_req abrt_req;
	काष्ठा cpl_पात_rpl abrt_rpl;
	काष्ठा fw_ri_wr ri_req;
	काष्ठा cpl_बंद_con_req बंद_req;
	अक्षर flowc_buf[FLOWC_LEN];
पूर्ण;

काष्ठा c4iw_ep_common अणु
	काष्ठा iw_cm_id *cm_id;
	काष्ठा c4iw_qp *qp;
	काष्ठा c4iw_dev *dev;
	काष्ठा sk_buff_head ep_skb_list;
	क्रमागत c4iw_ep_state state;
	काष्ठा kref kref;
	काष्ठा mutex mutex;
	काष्ठा sockaddr_storage local_addr;
	काष्ठा sockaddr_storage remote_addr;
	काष्ठा c4iw_wr_रुको *wr_रुकोp;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ history;
पूर्ण;

काष्ठा c4iw_listen_ep अणु
	काष्ठा c4iw_ep_common com;
	अचिन्हित पूर्णांक stid;
	पूर्णांक backlog;
पूर्ण;

काष्ठा c4iw_ep_stats अणु
	अचिन्हित connect_neg_adv;
	अचिन्हित पात_neg_adv;
पूर्ण;

काष्ठा c4iw_ep अणु
	काष्ठा c4iw_ep_common com;
	काष्ठा c4iw_ep *parent_ep;
	काष्ठा समयr_list समयr;
	काष्ठा list_head entry;
	अचिन्हित पूर्णांक atid;
	u32 hwtid;
	u32 snd_seq;
	u32 rcv_seq;
	काष्ठा l2t_entry *l2t;
	काष्ठा dst_entry *dst;
	काष्ठा sk_buff *mpa_skb;
	काष्ठा c4iw_mpa_attributes mpa_attr;
	u8 mpa_pkt[माप(काष्ठा mpa_message) + MPA_MAX_PRIVATE_DATA];
	अचिन्हित पूर्णांक mpa_pkt_len;
	u32 ird;
	u32 ord;
	u32 smac_idx;
	u32 tx_chan;
	u32 mtu;
	u16 mss;
	u16 emss;
	u16 plen;
	u16 rss_qid;
	u16 txq_idx;
	u16 ctrlq_idx;
	u8 tos;
	u8 retry_with_mpa_v1;
	u8 tried_with_mpa_v1;
	अचिन्हित पूर्णांक retry_count;
	पूर्णांक snd_win;
	पूर्णांक rcv_win;
	u32 snd_wscale;
	काष्ठा c4iw_ep_stats stats;
	u32 srqe_idx;
	u32 rx_pdu_out_cnt;
	काष्ठा sk_buff *peer_पात_skb;
पूर्ण;

अटल अंतरभूत काष्ठा c4iw_ep *to_ep(काष्ठा iw_cm_id *cm_id)
अणु
	वापस cm_id->provider_data;
पूर्ण

अटल अंतरभूत काष्ठा c4iw_listen_ep *to_listen_ep(काष्ठा iw_cm_id *cm_id)
अणु
	वापस cm_id->provider_data;
पूर्ण

अटल अंतरभूत पूर्णांक ocqp_supported(स्थिर काष्ठा cxgb4_lld_info *infop)
अणु
#अगर defined(__i386__) || defined(__x86_64__) || defined(CONFIG_PPC64)
	वापस infop->vr->ocq.size > 0;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

u32 c4iw_id_alloc(काष्ठा c4iw_id_table *alloc);
व्योम c4iw_id_मुक्त(काष्ठा c4iw_id_table *alloc, u32 obj);
पूर्णांक c4iw_id_table_alloc(काष्ठा c4iw_id_table *alloc, u32 start, u32 num,
			u32 reserved, u32 flags);
व्योम c4iw_id_table_मुक्त(काष्ठा c4iw_id_table *alloc);

प्रकार पूर्णांक (*c4iw_handler_func)(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb);

पूर्णांक c4iw_ep_redirect(व्योम *ctx, काष्ठा dst_entry *old, काष्ठा dst_entry *new,
		     काष्ठा l2t_entry *l2t);
व्योम c4iw_put_qpid(काष्ठा c4iw_rdev *rdev, u32 qpid,
		   काष्ठा c4iw_dev_ucontext *uctx);
u32 c4iw_get_resource(काष्ठा c4iw_id_table *id_table);
व्योम c4iw_put_resource(काष्ठा c4iw_id_table *id_table, u32 entry);
पूर्णांक c4iw_init_resource(काष्ठा c4iw_rdev *rdev, u32 nr_tpt,
		       u32 nr_pdid, u32 nr_srqt);
पूर्णांक c4iw_init_ctrl_qp(काष्ठा c4iw_rdev *rdev);
पूर्णांक c4iw_pblpool_create(काष्ठा c4iw_rdev *rdev);
पूर्णांक c4iw_rqtpool_create(काष्ठा c4iw_rdev *rdev);
पूर्णांक c4iw_ocqp_pool_create(काष्ठा c4iw_rdev *rdev);
व्योम c4iw_pblpool_destroy(काष्ठा c4iw_rdev *rdev);
व्योम c4iw_rqtpool_destroy(काष्ठा c4iw_rdev *rdev);
व्योम c4iw_ocqp_pool_destroy(काष्ठा c4iw_rdev *rdev);
व्योम c4iw_destroy_resource(काष्ठा c4iw_resource *rscp);
पूर्णांक c4iw_destroy_ctrl_qp(काष्ठा c4iw_rdev *rdev);
व्योम c4iw_रेजिस्टर_device(काष्ठा work_काष्ठा *work);
व्योम c4iw_unरेजिस्टर_device(काष्ठा c4iw_dev *dev);
पूर्णांक __init c4iw_cm_init(व्योम);
व्योम c4iw_cm_term(व्योम);
व्योम c4iw_release_dev_ucontext(काष्ठा c4iw_rdev *rdev,
			       काष्ठा c4iw_dev_ucontext *uctx);
व्योम c4iw_init_dev_ucontext(काष्ठा c4iw_rdev *rdev,
			    काष्ठा c4iw_dev_ucontext *uctx);
पूर्णांक c4iw_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc);
पूर्णांक c4iw_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		   स्थिर काष्ठा ib_send_wr **bad_wr);
पूर्णांक c4iw_post_receive(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		      स्थिर काष्ठा ib_recv_wr **bad_wr);
पूर्णांक c4iw_connect(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *conn_param);
पूर्णांक c4iw_create_listen(काष्ठा iw_cm_id *cm_id, पूर्णांक backlog);
पूर्णांक c4iw_destroy_listen(काष्ठा iw_cm_id *cm_id);
पूर्णांक c4iw_accept_cr(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *conn_param);
पूर्णांक c4iw_reject_cr(काष्ठा iw_cm_id *cm_id, स्थिर व्योम *pdata, u8 pdata_len);
व्योम c4iw_qp_add_ref(काष्ठा ib_qp *qp);
व्योम c4iw_qp_rem_ref(काष्ठा ib_qp *qp);
काष्ठा ib_mr *c4iw_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			    u32 max_num_sg);
पूर्णांक c4iw_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		   अचिन्हित पूर्णांक *sg_offset);
व्योम c4iw_dealloc(काष्ठा uld_ctx *ctx);
काष्ठा ib_mr *c4iw_reg_user_mr(काष्ठा ib_pd *pd, u64 start,
					   u64 length, u64 virt, पूर्णांक acc,
					   काष्ठा ib_udata *udata);
काष्ठा ib_mr *c4iw_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc);
पूर्णांक c4iw_dereg_mr(काष्ठा ib_mr *ib_mr, काष्ठा ib_udata *udata);
पूर्णांक c4iw_destroy_cq(काष्ठा ib_cq *ib_cq, काष्ठा ib_udata *udata);
पूर्णांक c4iw_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		   काष्ठा ib_udata *udata);
पूर्णांक c4iw_arm_cq(काष्ठा ib_cq *ibcq, क्रमागत ib_cq_notअगरy_flags flags);
पूर्णांक c4iw_modअगरy_srq(काष्ठा ib_srq *ib_srq, काष्ठा ib_srq_attr *attr,
		    क्रमागत ib_srq_attr_mask srq_attr_mask,
		    काष्ठा ib_udata *udata);
पूर्णांक c4iw_destroy_srq(काष्ठा ib_srq *ib_srq, काष्ठा ib_udata *udata);
पूर्णांक c4iw_create_srq(काष्ठा ib_srq *srq, काष्ठा ib_srq_init_attr *attrs,
		    काष्ठा ib_udata *udata);
पूर्णांक c4iw_destroy_qp(काष्ठा ib_qp *ib_qp, काष्ठा ib_udata *udata);
काष्ठा ib_qp *c4iw_create_qp(काष्ठा ib_pd *pd,
			     काष्ठा ib_qp_init_attr *attrs,
			     काष्ठा ib_udata *udata);
पूर्णांक c4iw_ib_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
				 पूर्णांक attr_mask, काष्ठा ib_udata *udata);
पूर्णांक c4iw_ib_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		     पूर्णांक attr_mask, काष्ठा ib_qp_init_attr *init_attr);
काष्ठा ib_qp *c4iw_get_qp(काष्ठा ib_device *dev, पूर्णांक qpn);
u32 c4iw_rqtpool_alloc(काष्ठा c4iw_rdev *rdev, पूर्णांक size);
व्योम c4iw_rqtpool_मुक्त(काष्ठा c4iw_rdev *rdev, u32 addr, पूर्णांक size);
u32 c4iw_pblpool_alloc(काष्ठा c4iw_rdev *rdev, पूर्णांक size);
व्योम c4iw_pblpool_मुक्त(काष्ठा c4iw_rdev *rdev, u32 addr, पूर्णांक size);
u32 c4iw_ocqp_pool_alloc(काष्ठा c4iw_rdev *rdev, पूर्णांक size);
व्योम c4iw_ocqp_pool_मुक्त(काष्ठा c4iw_rdev *rdev, u32 addr, पूर्णांक size);
व्योम c4iw_flush_hw_cq(काष्ठा c4iw_cq *chp, काष्ठा c4iw_qp *flush_qhp);
व्योम c4iw_count_rcqes(काष्ठा t4_cq *cq, काष्ठा t4_wq *wq, पूर्णांक *count);
पूर्णांक c4iw_ep_disconnect(काष्ठा c4iw_ep *ep, पूर्णांक abrupt, gfp_t gfp);
पूर्णांक c4iw_flush_rq(काष्ठा t4_wq *wq, काष्ठा t4_cq *cq, पूर्णांक count);
पूर्णांक c4iw_flush_sq(काष्ठा c4iw_qp *qhp);
पूर्णांक c4iw_ev_handler(काष्ठा c4iw_dev *rnicp, u32 qid);
u16 c4iw_rqes_posted(काष्ठा c4iw_qp *qhp);
पूर्णांक c4iw_post_terminate(काष्ठा c4iw_qp *qhp, काष्ठा t4_cqe *err_cqe);
u32 c4iw_get_cqid(काष्ठा c4iw_rdev *rdev, काष्ठा c4iw_dev_ucontext *uctx);
व्योम c4iw_put_cqid(काष्ठा c4iw_rdev *rdev, u32 qid,
		काष्ठा c4iw_dev_ucontext *uctx);
u32 c4iw_get_qpid(काष्ठा c4iw_rdev *rdev, काष्ठा c4iw_dev_ucontext *uctx);
व्योम c4iw_put_qpid(काष्ठा c4iw_rdev *rdev, u32 qid,
		काष्ठा c4iw_dev_ucontext *uctx);
व्योम c4iw_ev_dispatch(काष्ठा c4iw_dev *dev, काष्ठा t4_cqe *err_cqe);

बाह्य काष्ठा cxgb4_client t4c_client;
बाह्य c4iw_handler_func c4iw_handlers[NUM_CPL_CMDS];
व्योम __iomem *c4iw_bar2_addrs(काष्ठा c4iw_rdev *rdev, अचिन्हित पूर्णांक qid,
			      क्रमागत cxgb4_bar2_qtype qtype,
			      अचिन्हित पूर्णांक *pbar2_qid, u64 *pbar2_pa);
पूर्णांक c4iw_alloc_srq_idx(काष्ठा c4iw_rdev *rdev);
व्योम c4iw_मुक्त_srq_idx(काष्ठा c4iw_rdev *rdev, पूर्णांक idx);
बाह्य व्योम c4iw_log_wr_stats(काष्ठा t4_wq *wq, काष्ठा t4_cqe *cqe);
बाह्य पूर्णांक c4iw_wr_log;
बाह्य पूर्णांक db_fc_threshold;
बाह्य पूर्णांक db_coalescing_threshold;
बाह्य पूर्णांक use_dsgl;
व्योम c4iw_invalidate_mr(काष्ठा c4iw_dev *rhp, u32 rkey);
व्योम c4iw_dispatch_srq_limit_reached_event(काष्ठा c4iw_srq *srq);
व्योम c4iw_copy_wr_to_srq(काष्ठा t4_srq *srq, जोड़ t4_recv_wr *wqe, u8 len16);
व्योम c4iw_flush_srqidx(काष्ठा c4iw_qp *qhp, u32 srqidx);
पूर्णांक c4iw_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
		       स्थिर काष्ठा ib_recv_wr **bad_wr);
काष्ठा c4iw_wr_रुको *c4iw_alloc_wr_रुको(gfp_t gfp);

पूर्णांक c4iw_fill_res_mr_entry(काष्ठा sk_buff *msg, काष्ठा ib_mr *ibmr);
पूर्णांक c4iw_fill_res_cq_entry(काष्ठा sk_buff *msg, काष्ठा ib_cq *ibcq);
पूर्णांक c4iw_fill_res_qp_entry(काष्ठा sk_buff *msg, काष्ठा ib_qp *ibqp);
पूर्णांक c4iw_fill_res_cm_id_entry(काष्ठा sk_buff *msg, काष्ठा rdma_cm_id *cm_id);

#पूर्ण_अगर
