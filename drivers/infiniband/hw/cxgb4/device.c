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
 *
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
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/math64.h>

#समावेश <rdma/ib_verbs.h>

#समावेश "iw_cxgb4.h"

#घोषणा DRV_VERSION "0.1"

MODULE_AUTHOR("Steve Wise");
MODULE_DESCRIPTION("Chelsio T4/T5 RDMA Driver");
MODULE_LICENSE("Dual BSD/GPL");

अटल पूर्णांक allow_db_fc_on_t5;
module_param(allow_db_fc_on_t5, पूर्णांक, 0644);
MODULE_PARM_DESC(allow_db_fc_on_t5,
		 "Allow DB Flow Control on T5 (default = 0)");

अटल पूर्णांक allow_db_coalescing_on_t5;
module_param(allow_db_coalescing_on_t5, पूर्णांक, 0644);
MODULE_PARM_DESC(allow_db_coalescing_on_t5,
		 "Allow DB Coalescing on T5 (default = 0)");

पूर्णांक c4iw_wr_log = 0;
module_param(c4iw_wr_log, पूर्णांक, 0444);
MODULE_PARM_DESC(c4iw_wr_log, "Enables logging of work request timing data.");

अटल पूर्णांक c4iw_wr_log_size_order = 12;
module_param(c4iw_wr_log_size_order, पूर्णांक, 0444);
MODULE_PARM_DESC(c4iw_wr_log_size_order,
		 "Number of entries (log2) in the work request timing log.");

अटल LIST_HEAD(uld_ctx_list);
अटल DEFINE_MUTEX(dev_mutex);
अटल काष्ठा workqueue_काष्ठा *reg_workq;

#घोषणा DB_FC_RESUME_SIZE 64
#घोषणा DB_FC_RESUME_DELAY 1
#घोषणा DB_FC_DRAIN_THRESH 0

अटल काष्ठा dentry *c4iw_debugfs_root;

काष्ठा c4iw_debugfs_data अणु
	काष्ठा c4iw_dev *devp;
	अक्षर *buf;
	पूर्णांक bufsize;
	पूर्णांक pos;
पूर्ण;

अटल sमाप_प्रकार debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			    loff_t *ppos)
अणु
	काष्ठा c4iw_debugfs_data *d = file->निजी_data;

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, d->buf, d->pos);
पूर्ण

व्योम c4iw_log_wr_stats(काष्ठा t4_wq *wq, काष्ठा t4_cqe *cqe)
अणु
	काष्ठा wr_log_entry le;
	पूर्णांक idx;

	अगर (!wq->rdev->wr_log)
		वापस;

	idx = (atomic_inc_वापस(&wq->rdev->wr_log_idx) - 1) &
		(wq->rdev->wr_log_size - 1);
	le.poll_sge_ts = cxgb4_पढ़ो_sge_बारtamp(wq->rdev->lldi.ports[0]);
	le.poll_host_समय = kसमय_get();
	le.valid = 1;
	le.cqe_sge_ts = CQE_TS(cqe);
	अगर (SQ_TYPE(cqe)) अणु
		le.qid = wq->sq.qid;
		le.opcode = CQE_OPCODE(cqe);
		le.post_host_समय = wq->sq.sw_sq[wq->sq.cidx].host_समय;
		le.post_sge_ts = wq->sq.sw_sq[wq->sq.cidx].sge_ts;
		le.wr_id = CQE_WRID_SQ_IDX(cqe);
	पूर्ण अन्यथा अणु
		le.qid = wq->rq.qid;
		le.opcode = FW_RI_RECEIVE;
		le.post_host_समय = wq->rq.sw_rq[wq->rq.cidx].host_समय;
		le.post_sge_ts = wq->rq.sw_rq[wq->rq.cidx].sge_ts;
		le.wr_id = CQE_WRID_MSN(cqe);
	पूर्ण
	wq->rdev->wr_log[idx] = le;
पूर्ण

अटल पूर्णांक wr_log_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा c4iw_dev *dev = seq->निजी;
	kसमय_प्रकार prev_समय;
	काष्ठा wr_log_entry *lep;
	पूर्णांक prev_समय_set = 0;
	पूर्णांक idx, end;

#घोषणा ts2ns(ts) भाग64_u64((ts) * dev->rdev.lldi.cclk_ps, 1000)

	idx = atomic_पढ़ो(&dev->rdev.wr_log_idx) &
		(dev->rdev.wr_log_size - 1);
	end = idx - 1;
	अगर (end < 0)
		end = dev->rdev.wr_log_size - 1;
	lep = &dev->rdev.wr_log[idx];
	जबतक (idx != end) अणु
		अगर (lep->valid) अणु
			अगर (!prev_समय_set) अणु
				prev_समय_set = 1;
				prev_समय = lep->poll_host_समय;
			पूर्ण
			seq_म_लिखो(seq, "%04u: nsec %llu qid %u opcode "
				   "%u %s 0x%x host_wr_delta nsec %llu "
				   "post_sge_ts 0x%llx cqe_sge_ts 0x%llx "
				   "poll_sge_ts 0x%llx post_poll_delta_ns %llu "
				   "cqe_poll_delta_ns %llu\n",
				   idx,
				   kसमय_प्रकारo_ns(kसमय_sub(lep->poll_host_समय,
							 prev_समय)),
				   lep->qid, lep->opcode,
				   lep->opcode == FW_RI_RECEIVE ?
							"msn" : "wrid",
				   lep->wr_id,
				   kसमय_प्रकारo_ns(kसमय_sub(lep->poll_host_समय,
							 lep->post_host_समय)),
				   lep->post_sge_ts, lep->cqe_sge_ts,
				   lep->poll_sge_ts,
				   ts2ns(lep->poll_sge_ts - lep->post_sge_ts),
				   ts2ns(lep->poll_sge_ts - lep->cqe_sge_ts));
			prev_समय = lep->poll_host_समय;
		पूर्ण
		idx++;
		अगर (idx > (dev->rdev.wr_log_size - 1))
			idx = 0;
		lep = &dev->rdev.wr_log[idx];
	पूर्ण
#अघोषित ts2ns
	वापस 0;
पूर्ण

अटल पूर्णांक wr_log_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, wr_log_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार wr_log_clear(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा c4iw_dev *dev = ((काष्ठा seq_file *)file->निजी_data)->निजी;
	पूर्णांक i;

	अगर (dev->rdev.wr_log)
		क्रम (i = 0; i < dev->rdev.wr_log_size; i++)
			dev->rdev.wr_log[i].valid = 0;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations wr_log_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = wr_log_खोलो,
	.release = single_release,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.ग_लिखो   = wr_log_clear,
पूर्ण;

अटल काष्ठा sockaddr_in zero_sin = अणु
	.sin_family = AF_INET,
पूर्ण;

अटल काष्ठा sockaddr_in6 zero_sin6 = अणु
	.sin6_family = AF_INET6,
पूर्ण;

अटल व्योम set_ep_sin_addrs(काष्ठा c4iw_ep *ep,
			     काष्ठा sockaddr_in **lsin,
			     काष्ठा sockaddr_in **rsin,
			     काष्ठा sockaddr_in **m_lsin,
			     काष्ठा sockaddr_in **m_rsin)
अणु
	काष्ठा iw_cm_id *id = ep->com.cm_id;

	*m_lsin = (काष्ठा sockaddr_in *)&ep->com.local_addr;
	*m_rsin = (काष्ठा sockaddr_in *)&ep->com.remote_addr;
	अगर (id) अणु
		*lsin = (काष्ठा sockaddr_in *)&id->local_addr;
		*rsin = (काष्ठा sockaddr_in *)&id->remote_addr;
	पूर्ण अन्यथा अणु
		*lsin = &zero_sin;
		*rsin = &zero_sin;
	पूर्ण
पूर्ण

अटल व्योम set_ep_sin6_addrs(काष्ठा c4iw_ep *ep,
			      काष्ठा sockaddr_in6 **lsin6,
			      काष्ठा sockaddr_in6 **rsin6,
			      काष्ठा sockaddr_in6 **m_lsin6,
			      काष्ठा sockaddr_in6 **m_rsin6)
अणु
	काष्ठा iw_cm_id *id = ep->com.cm_id;

	*m_lsin6 = (काष्ठा sockaddr_in6 *)&ep->com.local_addr;
	*m_rsin6 = (काष्ठा sockaddr_in6 *)&ep->com.remote_addr;
	अगर (id) अणु
		*lsin6 = (काष्ठा sockaddr_in6 *)&id->local_addr;
		*rsin6 = (काष्ठा sockaddr_in6 *)&id->remote_addr;
	पूर्ण अन्यथा अणु
		*lsin6 = &zero_sin6;
		*rsin6 = &zero_sin6;
	पूर्ण
पूर्ण

अटल पूर्णांक dump_qp(अचिन्हित दीर्घ id, काष्ठा c4iw_qp *qp,
		   काष्ठा c4iw_debugfs_data *qpd)
अणु
	पूर्णांक space;
	पूर्णांक cc;
	अगर (id != qp->wq.sq.qid)
		वापस 0;

	space = qpd->bufsize - qpd->pos - 1;
	अगर (space == 0)
		वापस 1;

	अगर (qp->ep) अणु
		काष्ठा c4iw_ep *ep = qp->ep;

		अगर (ep->com.local_addr.ss_family == AF_INET) अणु
			काष्ठा sockaddr_in *lsin;
			काष्ठा sockaddr_in *rsin;
			काष्ठा sockaddr_in *m_lsin;
			काष्ठा sockaddr_in *m_rsin;

			set_ep_sin_addrs(ep, &lsin, &rsin, &m_lsin, &m_rsin);
			cc = snम_लिखो(qpd->buf + qpd->pos, space,
				      "rc qp sq id %u %s id %u state %u "
				      "onchip %u ep tid %u state %u "
				      "%pI4:%u/%u->%pI4:%u/%u\n",
				      qp->wq.sq.qid, qp->srq ? "srq" : "rq",
				      qp->srq ? qp->srq->idx : qp->wq.rq.qid,
				      (पूर्णांक)qp->attr.state,
				      qp->wq.sq.flags & T4_SQ_ONCHIP,
				      ep->hwtid, (पूर्णांक)ep->com.state,
				      &lsin->sin_addr, ntohs(lsin->sin_port),
				      ntohs(m_lsin->sin_port),
				      &rsin->sin_addr, ntohs(rsin->sin_port),
				      ntohs(m_rsin->sin_port));
		पूर्ण अन्यथा अणु
			काष्ठा sockaddr_in6 *lsin6;
			काष्ठा sockaddr_in6 *rsin6;
			काष्ठा sockaddr_in6 *m_lsin6;
			काष्ठा sockaddr_in6 *m_rsin6;

			set_ep_sin6_addrs(ep, &lsin6, &rsin6, &m_lsin6,
					  &m_rsin6);
			cc = snम_लिखो(qpd->buf + qpd->pos, space,
				      "rc qp sq id %u rq id %u state %u "
				      "onchip %u ep tid %u state %u "
				      "%pI6:%u/%u->%pI6:%u/%u\n",
				      qp->wq.sq.qid, qp->wq.rq.qid,
				      (पूर्णांक)qp->attr.state,
				      qp->wq.sq.flags & T4_SQ_ONCHIP,
				      ep->hwtid, (पूर्णांक)ep->com.state,
				      &lsin6->sin6_addr,
				      ntohs(lsin6->sin6_port),
				      ntohs(m_lsin6->sin6_port),
				      &rsin6->sin6_addr,
				      ntohs(rsin6->sin6_port),
				      ntohs(m_rsin6->sin6_port));
		पूर्ण
	पूर्ण अन्यथा
		cc = snम_लिखो(qpd->buf + qpd->pos, space,
			     "qp sq id %u rq id %u state %u onchip %u\n",
			      qp->wq.sq.qid, qp->wq.rq.qid,
			      (पूर्णांक)qp->attr.state,
			      qp->wq.sq.flags & T4_SQ_ONCHIP);
	अगर (cc < space)
		qpd->pos += cc;
	वापस 0;
पूर्ण

अटल पूर्णांक qp_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा c4iw_debugfs_data *qpd = file->निजी_data;
	अगर (!qpd) अणु
		pr_info("%s null qpd?\n", __func__);
		वापस 0;
	पूर्ण
	vमुक्त(qpd->buf);
	kमुक्त(qpd);
	वापस 0;
पूर्ण

अटल पूर्णांक qp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा c4iw_qp *qp;
	काष्ठा c4iw_debugfs_data *qpd;
	अचिन्हित दीर्घ index;
	पूर्णांक count = 1;

	qpd = kदो_स्मृति(माप(*qpd), GFP_KERNEL);
	अगर (!qpd)
		वापस -ENOMEM;

	qpd->devp = inode->i_निजी;
	qpd->pos = 0;

	/*
	 * No need to lock; we drop the lock to call vदो_स्मृति so it's racy
	 * anyway.  Someone who cares should चयन this over to seq_file
	 */
	xa_क्रम_each(&qpd->devp->qps, index, qp)
		count++;

	qpd->bufsize = count * 180;
	qpd->buf = vदो_स्मृति(qpd->bufsize);
	अगर (!qpd->buf) अणु
		kमुक्त(qpd);
		वापस -ENOMEM;
	पूर्ण

	xa_lock_irq(&qpd->devp->qps);
	xa_क्रम_each(&qpd->devp->qps, index, qp)
		dump_qp(index, qp, qpd);
	xa_unlock_irq(&qpd->devp->qps);

	qpd->buf[qpd->pos++] = 0;
	file->निजी_data = qpd;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations qp_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = qp_खोलो,
	.release = qp_release,
	.पढ़ो    = debugfs_पढ़ो,
	.llseek  = शेष_llseek,
पूर्ण;

अटल पूर्णांक dump_stag(अचिन्हित दीर्घ id, काष्ठा c4iw_debugfs_data *stagd)
अणु
	पूर्णांक space;
	पूर्णांक cc;
	काष्ठा fw_ri_tpte tpte;
	पूर्णांक ret;

	space = stagd->bufsize - stagd->pos - 1;
	अगर (space == 0)
		वापस 1;

	ret = cxgb4_पढ़ो_tpte(stagd->devp->rdev.lldi.ports[0], (u32)id<<8,
			      (__be32 *)&tpte);
	अगर (ret) अणु
		dev_err(&stagd->devp->rdev.lldi.pdev->dev,
			"%s cxgb4_read_tpte err %d\n", __func__, ret);
		वापस ret;
	पूर्ण
	cc = snम_लिखो(stagd->buf + stagd->pos, space,
		      "stag: idx 0x%x valid %d key 0x%x state %d pdid %d "
		      "perm 0x%x ps %d len 0x%llx va 0x%llx\n",
		      (u32)id<<8,
		      FW_RI_TPTE_VALID_G(ntohl(tpte.valid_to_pdid)),
		      FW_RI_TPTE_STAGKEY_G(ntohl(tpte.valid_to_pdid)),
		      FW_RI_TPTE_STAGSTATE_G(ntohl(tpte.valid_to_pdid)),
		      FW_RI_TPTE_PDID_G(ntohl(tpte.valid_to_pdid)),
		      FW_RI_TPTE_PERM_G(ntohl(tpte.locपढ़ो_to_qpid)),
		      FW_RI_TPTE_PS_G(ntohl(tpte.locपढ़ो_to_qpid)),
		      ((u64)ntohl(tpte.len_hi) << 32) | ntohl(tpte.len_lo),
		      ((u64)ntohl(tpte.va_hi) << 32) | ntohl(tpte.va_lo_fbo));
	अगर (cc < space)
		stagd->pos += cc;
	वापस 0;
पूर्ण

अटल पूर्णांक stag_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा c4iw_debugfs_data *stagd = file->निजी_data;
	अगर (!stagd) अणु
		pr_info("%s null stagd?\n", __func__);
		वापस 0;
	पूर्ण
	vमुक्त(stagd->buf);
	kमुक्त(stagd);
	वापस 0;
पूर्ण

अटल पूर्णांक stag_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा c4iw_debugfs_data *stagd;
	व्योम *p;
	अचिन्हित दीर्घ index;
	पूर्णांक ret = 0;
	पूर्णांक count = 1;

	stagd = kदो_स्मृति(माप(*stagd), GFP_KERNEL);
	अगर (!stagd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	stagd->devp = inode->i_निजी;
	stagd->pos = 0;

	xa_क्रम_each(&stagd->devp->mrs, index, p)
		count++;

	stagd->bufsize = count * 256;
	stagd->buf = vदो_स्मृति(stagd->bufsize);
	अगर (!stagd->buf) अणु
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण

	xa_lock_irq(&stagd->devp->mrs);
	xa_क्रम_each(&stagd->devp->mrs, index, p)
		dump_stag(index, stagd);
	xa_unlock_irq(&stagd->devp->mrs);

	stagd->buf[stagd->pos++] = 0;
	file->निजी_data = stagd;
	जाओ out;
err1:
	kमुक्त(stagd);
out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations stag_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = stag_खोलो,
	.release = stag_release,
	.पढ़ो    = debugfs_पढ़ो,
	.llseek  = शेष_llseek,
पूर्ण;

अटल अक्षर *db_state_str[] = अणु"NORMAL", "FLOW_CONTROL", "RECOVERY", "STOPPED"पूर्ण;

अटल पूर्णांक stats_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा c4iw_dev *dev = seq->निजी;

	seq_म_लिखो(seq, "   Object: %10s %10s %10s %10s\n", "Total", "Current",
		   "Max", "Fail");
	seq_म_लिखो(seq, "     PDID: %10llu %10llu %10llu %10llu\n",
			dev->rdev.stats.pd.total, dev->rdev.stats.pd.cur,
			dev->rdev.stats.pd.max, dev->rdev.stats.pd.fail);
	seq_म_लिखो(seq, "      QID: %10llu %10llu %10llu %10llu\n",
			dev->rdev.stats.qid.total, dev->rdev.stats.qid.cur,
			dev->rdev.stats.qid.max, dev->rdev.stats.qid.fail);
	seq_म_लिखो(seq, "     SRQS: %10llu %10llu %10llu %10llu\n",
		   dev->rdev.stats.srqt.total, dev->rdev.stats.srqt.cur,
			dev->rdev.stats.srqt.max, dev->rdev.stats.srqt.fail);
	seq_म_लिखो(seq, "   TPTMEM: %10llu %10llu %10llu %10llu\n",
			dev->rdev.stats.stag.total, dev->rdev.stats.stag.cur,
			dev->rdev.stats.stag.max, dev->rdev.stats.stag.fail);
	seq_म_लिखो(seq, "   PBLMEM: %10llu %10llu %10llu %10llu\n",
			dev->rdev.stats.pbl.total, dev->rdev.stats.pbl.cur,
			dev->rdev.stats.pbl.max, dev->rdev.stats.pbl.fail);
	seq_म_लिखो(seq, "   RQTMEM: %10llu %10llu %10llu %10llu\n",
			dev->rdev.stats.rqt.total, dev->rdev.stats.rqt.cur,
			dev->rdev.stats.rqt.max, dev->rdev.stats.rqt.fail);
	seq_म_लिखो(seq, "  OCQPMEM: %10llu %10llu %10llu %10llu\n",
			dev->rdev.stats.ocqp.total, dev->rdev.stats.ocqp.cur,
			dev->rdev.stats.ocqp.max, dev->rdev.stats.ocqp.fail);
	seq_म_लिखो(seq, "  DB FULL: %10llu\n", dev->rdev.stats.db_full);
	seq_म_लिखो(seq, " DB EMPTY: %10llu\n", dev->rdev.stats.db_empty);
	seq_म_लिखो(seq, "  DB DROP: %10llu\n", dev->rdev.stats.db_drop);
	seq_म_लिखो(seq, " DB State: %s Transitions %llu FC Interruptions %llu\n",
		   db_state_str[dev->db_state],
		   dev->rdev.stats.db_state_transitions,
		   dev->rdev.stats.db_fc_पूर्णांकerruptions);
	seq_म_लिखो(seq, "TCAM_FULL: %10llu\n", dev->rdev.stats.tcam_full);
	seq_म_लिखो(seq, "ACT_OFLD_CONN_FAILS: %10llu\n",
		   dev->rdev.stats.act_ofld_conn_fails);
	seq_म_लिखो(seq, "PAS_OFLD_CONN_FAILS: %10llu\n",
		   dev->rdev.stats.pas_ofld_conn_fails);
	seq_म_लिखो(seq, "NEG_ADV_RCVD: %10llu\n", dev->rdev.stats.neg_adv);
	seq_म_लिखो(seq, "AVAILABLE IRD: %10u\n", dev->avail_ird);
	वापस 0;
पूर्ण

अटल पूर्णांक stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, stats_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार stats_clear(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा c4iw_dev *dev = ((काष्ठा seq_file *)file->निजी_data)->निजी;

	mutex_lock(&dev->rdev.stats.lock);
	dev->rdev.stats.pd.max = 0;
	dev->rdev.stats.pd.fail = 0;
	dev->rdev.stats.qid.max = 0;
	dev->rdev.stats.qid.fail = 0;
	dev->rdev.stats.stag.max = 0;
	dev->rdev.stats.stag.fail = 0;
	dev->rdev.stats.pbl.max = 0;
	dev->rdev.stats.pbl.fail = 0;
	dev->rdev.stats.rqt.max = 0;
	dev->rdev.stats.rqt.fail = 0;
	dev->rdev.stats.rqt.max = 0;
	dev->rdev.stats.rqt.fail = 0;
	dev->rdev.stats.ocqp.max = 0;
	dev->rdev.stats.ocqp.fail = 0;
	dev->rdev.stats.db_full = 0;
	dev->rdev.stats.db_empty = 0;
	dev->rdev.stats.db_drop = 0;
	dev->rdev.stats.db_state_transitions = 0;
	dev->rdev.stats.tcam_full = 0;
	dev->rdev.stats.act_ofld_conn_fails = 0;
	dev->rdev.stats.pas_ofld_conn_fails = 0;
	mutex_unlock(&dev->rdev.stats.lock);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations stats_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = stats_खोलो,
	.release = single_release,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.ग_लिखो   = stats_clear,
पूर्ण;

अटल पूर्णांक dump_ep(काष्ठा c4iw_ep *ep, काष्ठा c4iw_debugfs_data *epd)
अणु
	पूर्णांक space;
	पूर्णांक cc;

	space = epd->bufsize - epd->pos - 1;
	अगर (space == 0)
		वापस 1;

	अगर (ep->com.local_addr.ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *lsin;
		काष्ठा sockaddr_in *rsin;
		काष्ठा sockaddr_in *m_lsin;
		काष्ठा sockaddr_in *m_rsin;

		set_ep_sin_addrs(ep, &lsin, &rsin, &m_lsin, &m_rsin);
		cc = snम_लिखो(epd->buf + epd->pos, space,
			      "ep %p cm_id %p qp %p state %d flags 0x%lx "
			      "history 0x%lx hwtid %d atid %d "
			      "conn_na %u abort_na %u "
			      "%pI4:%d/%d <-> %pI4:%d/%d\n",
			      ep, ep->com.cm_id, ep->com.qp,
			      (पूर्णांक)ep->com.state, ep->com.flags,
			      ep->com.history, ep->hwtid, ep->atid,
			      ep->stats.connect_neg_adv,
			      ep->stats.पात_neg_adv,
			      &lsin->sin_addr, ntohs(lsin->sin_port),
			      ntohs(m_lsin->sin_port),
			      &rsin->sin_addr, ntohs(rsin->sin_port),
			      ntohs(m_rsin->sin_port));
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *lsin6;
		काष्ठा sockaddr_in6 *rsin6;
		काष्ठा sockaddr_in6 *m_lsin6;
		काष्ठा sockaddr_in6 *m_rsin6;

		set_ep_sin6_addrs(ep, &lsin6, &rsin6, &m_lsin6, &m_rsin6);
		cc = snम_लिखो(epd->buf + epd->pos, space,
			      "ep %p cm_id %p qp %p state %d flags 0x%lx "
			      "history 0x%lx hwtid %d atid %d "
			      "conn_na %u abort_na %u "
			      "%pI6:%d/%d <-> %pI6:%d/%d\n",
			      ep, ep->com.cm_id, ep->com.qp,
			      (पूर्णांक)ep->com.state, ep->com.flags,
			      ep->com.history, ep->hwtid, ep->atid,
			      ep->stats.connect_neg_adv,
			      ep->stats.पात_neg_adv,
			      &lsin6->sin6_addr, ntohs(lsin6->sin6_port),
			      ntohs(m_lsin6->sin6_port),
			      &rsin6->sin6_addr, ntohs(rsin6->sin6_port),
			      ntohs(m_rsin6->sin6_port));
	पूर्ण
	अगर (cc < space)
		epd->pos += cc;
	वापस 0;
पूर्ण

अटल
पूर्णांक dump_listen_ep(काष्ठा c4iw_listen_ep *ep, काष्ठा c4iw_debugfs_data *epd)
अणु
	पूर्णांक space;
	पूर्णांक cc;

	space = epd->bufsize - epd->pos - 1;
	अगर (space == 0)
		वापस 1;

	अगर (ep->com.local_addr.ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *lsin = (काष्ठा sockaddr_in *)
			&ep->com.cm_id->local_addr;
		काष्ठा sockaddr_in *m_lsin = (काष्ठा sockaddr_in *)
			&ep->com.cm_id->m_local_addr;

		cc = snम_लिखो(epd->buf + epd->pos, space,
			      "ep %p cm_id %p state %d flags 0x%lx stid %d "
			      "backlog %d %pI4:%d/%d\n",
			      ep, ep->com.cm_id, (पूर्णांक)ep->com.state,
			      ep->com.flags, ep->stid, ep->backlog,
			      &lsin->sin_addr, ntohs(lsin->sin_port),
			      ntohs(m_lsin->sin_port));
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *lsin6 = (काष्ठा sockaddr_in6 *)
			&ep->com.cm_id->local_addr;
		काष्ठा sockaddr_in6 *m_lsin6 = (काष्ठा sockaddr_in6 *)
			&ep->com.cm_id->m_local_addr;

		cc = snम_लिखो(epd->buf + epd->pos, space,
			      "ep %p cm_id %p state %d flags 0x%lx stid %d "
			      "backlog %d %pI6:%d/%d\n",
			      ep, ep->com.cm_id, (पूर्णांक)ep->com.state,
			      ep->com.flags, ep->stid, ep->backlog,
			      &lsin6->sin6_addr, ntohs(lsin6->sin6_port),
			      ntohs(m_lsin6->sin6_port));
	पूर्ण
	अगर (cc < space)
		epd->pos += cc;
	वापस 0;
पूर्ण

अटल पूर्णांक ep_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा c4iw_debugfs_data *epd = file->निजी_data;
	अगर (!epd) अणु
		pr_info("%s null qpd?\n", __func__);
		वापस 0;
	पूर्ण
	vमुक्त(epd->buf);
	kमुक्त(epd);
	वापस 0;
पूर्ण

अटल पूर्णांक ep_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा c4iw_ep *ep;
	काष्ठा c4iw_listen_ep *lep;
	अचिन्हित दीर्घ index;
	काष्ठा c4iw_debugfs_data *epd;
	पूर्णांक ret = 0;
	पूर्णांक count = 1;

	epd = kदो_स्मृति(माप(*epd), GFP_KERNEL);
	अगर (!epd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	epd->devp = inode->i_निजी;
	epd->pos = 0;

	xa_क्रम_each(&epd->devp->hwtids, index, ep)
		count++;
	xa_क्रम_each(&epd->devp->atids, index, ep)
		count++;
	xa_क्रम_each(&epd->devp->stids, index, lep)
		count++;

	epd->bufsize = count * 240;
	epd->buf = vदो_स्मृति(epd->bufsize);
	अगर (!epd->buf) अणु
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण

	xa_lock_irq(&epd->devp->hwtids);
	xa_क्रम_each(&epd->devp->hwtids, index, ep)
		dump_ep(ep, epd);
	xa_unlock_irq(&epd->devp->hwtids);
	xa_lock_irq(&epd->devp->atids);
	xa_क्रम_each(&epd->devp->atids, index, ep)
		dump_ep(ep, epd);
	xa_unlock_irq(&epd->devp->atids);
	xa_lock_irq(&epd->devp->stids);
	xa_क्रम_each(&epd->devp->stids, index, lep)
		dump_listen_ep(lep, epd);
	xa_unlock_irq(&epd->devp->stids);

	file->निजी_data = epd;
	जाओ out;
err1:
	kमुक्त(epd);
out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations ep_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = ep_खोलो,
	.release = ep_release,
	.पढ़ो    = debugfs_पढ़ो,
पूर्ण;

अटल व्योम setup_debugfs(काष्ठा c4iw_dev *devp)
अणु
	debugfs_create_file_size("qps", S_IWUSR, devp->debugfs_root,
				 (व्योम *)devp, &qp_debugfs_fops, 4096);

	debugfs_create_file_size("stags", S_IWUSR, devp->debugfs_root,
				 (व्योम *)devp, &stag_debugfs_fops, 4096);

	debugfs_create_file_size("stats", S_IWUSR, devp->debugfs_root,
				 (व्योम *)devp, &stats_debugfs_fops, 4096);

	debugfs_create_file_size("eps", S_IWUSR, devp->debugfs_root,
				 (व्योम *)devp, &ep_debugfs_fops, 4096);

	अगर (c4iw_wr_log)
		debugfs_create_file_size("wr_log", S_IWUSR, devp->debugfs_root,
					 (व्योम *)devp, &wr_log_debugfs_fops, 4096);
पूर्ण

व्योम c4iw_release_dev_ucontext(काष्ठा c4iw_rdev *rdev,
			       काष्ठा c4iw_dev_ucontext *uctx)
अणु
	काष्ठा list_head *pos, *nxt;
	काष्ठा c4iw_qid_list *entry;

	mutex_lock(&uctx->lock);
	list_क्रम_each_safe(pos, nxt, &uctx->qpids) अणु
		entry = list_entry(pos, काष्ठा c4iw_qid_list, entry);
		list_del_init(&entry->entry);
		अगर (!(entry->qid & rdev->qpmask)) अणु
			c4iw_put_resource(&rdev->resource.qid_table,
					  entry->qid);
			mutex_lock(&rdev->stats.lock);
			rdev->stats.qid.cur -= rdev->qpmask + 1;
			mutex_unlock(&rdev->stats.lock);
		पूर्ण
		kमुक्त(entry);
	पूर्ण

	list_क्रम_each_safe(pos, nxt, &uctx->cqids) अणु
		entry = list_entry(pos, काष्ठा c4iw_qid_list, entry);
		list_del_init(&entry->entry);
		kमुक्त(entry);
	पूर्ण
	mutex_unlock(&uctx->lock);
पूर्ण

व्योम c4iw_init_dev_ucontext(काष्ठा c4iw_rdev *rdev,
			    काष्ठा c4iw_dev_ucontext *uctx)
अणु
	INIT_LIST_HEAD(&uctx->qpids);
	INIT_LIST_HEAD(&uctx->cqids);
	mutex_init(&uctx->lock);
पूर्ण

/* Caller takes care of locking अगर needed */
अटल पूर्णांक c4iw_rdev_खोलो(काष्ठा c4iw_rdev *rdev)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक factor;

	c4iw_init_dev_ucontext(rdev, &rdev->uctx);

	/*
	 * This implementation assumes udb_density == ucq_density!  Eventually
	 * we might need to support this but क्रम now fail the खोलो. Also the
	 * cqid and qpid range must match क्रम now.
	 */
	अगर (rdev->lldi.udb_density != rdev->lldi.ucq_density) अणु
		pr_err("%s: unsupported udb/ucq densities %u/%u\n",
		       pci_name(rdev->lldi.pdev), rdev->lldi.udb_density,
		       rdev->lldi.ucq_density);
		वापस -EINVAL;
	पूर्ण
	अगर (rdev->lldi.vr->qp.start != rdev->lldi.vr->cq.start ||
	    rdev->lldi.vr->qp.size != rdev->lldi.vr->cq.size) अणु
		pr_err("%s: unsupported qp and cq id ranges qp start %u size %u cq start %u size %u\n",
		       pci_name(rdev->lldi.pdev), rdev->lldi.vr->qp.start,
		       rdev->lldi.vr->qp.size, rdev->lldi.vr->cq.size,
		       rdev->lldi.vr->cq.size);
		वापस -EINVAL;
	पूर्ण

	/* This implementation requires a sge_host_page_size <= PAGE_SIZE. */
	अगर (rdev->lldi.sge_host_page_size > PAGE_SIZE) अणु
		pr_err("%s: unsupported sge host page size %u\n",
		       pci_name(rdev->lldi.pdev),
		       rdev->lldi.sge_host_page_size);
		वापस -EINVAL;
	पूर्ण

	factor = PAGE_SIZE / rdev->lldi.sge_host_page_size;
	rdev->qpmask = (rdev->lldi.udb_density * factor) - 1;
	rdev->cqmask = (rdev->lldi.ucq_density * factor) - 1;

	pr_debug("dev %s stag start 0x%0x size 0x%0x num stags %d pbl start 0x%0x size 0x%0x rq start 0x%0x size 0x%0x qp qid start %u size %u cq qid start %u size %u srq size %u\n",
		 pci_name(rdev->lldi.pdev), rdev->lldi.vr->stag.start,
		 rdev->lldi.vr->stag.size, c4iw_num_stags(rdev),
		 rdev->lldi.vr->pbl.start,
		 rdev->lldi.vr->pbl.size, rdev->lldi.vr->rq.start,
		 rdev->lldi.vr->rq.size,
		 rdev->lldi.vr->qp.start,
		 rdev->lldi.vr->qp.size,
		 rdev->lldi.vr->cq.start,
		 rdev->lldi.vr->cq.size,
		 rdev->lldi.vr->srq.size);
	pr_debug("udb %pR db_reg %p gts_reg %p qpmask 0x%x cqmask 0x%x\n",
		 &rdev->lldi.pdev->resource[2],
		 rdev->lldi.db_reg, rdev->lldi.gts_reg,
		 rdev->qpmask, rdev->cqmask);

	अगर (c4iw_num_stags(rdev) == 0)
		वापस -EINVAL;

	rdev->stats.pd.total = T4_MAX_NUM_PD;
	rdev->stats.stag.total = rdev->lldi.vr->stag.size;
	rdev->stats.pbl.total = rdev->lldi.vr->pbl.size;
	rdev->stats.rqt.total = rdev->lldi.vr->rq.size;
	rdev->stats.srqt.total = rdev->lldi.vr->srq.size;
	rdev->stats.ocqp.total = rdev->lldi.vr->ocq.size;
	rdev->stats.qid.total = rdev->lldi.vr->qp.size;

	err = c4iw_init_resource(rdev, c4iw_num_stags(rdev),
				 T4_MAX_NUM_PD, rdev->lldi.vr->srq.size);
	अगर (err) अणु
		pr_err("error %d initializing resources\n", err);
		वापस err;
	पूर्ण
	err = c4iw_pblpool_create(rdev);
	अगर (err) अणु
		pr_err("error %d initializing pbl pool\n", err);
		जाओ destroy_resource;
	पूर्ण
	err = c4iw_rqtpool_create(rdev);
	अगर (err) अणु
		pr_err("error %d initializing rqt pool\n", err);
		जाओ destroy_pblpool;
	पूर्ण
	err = c4iw_ocqp_pool_create(rdev);
	अगर (err) अणु
		pr_err("error %d initializing ocqp pool\n", err);
		जाओ destroy_rqtpool;
	पूर्ण
	rdev->status_page = (काष्ठा t4_dev_status_page *)
			    __get_मुक्त_page(GFP_KERNEL);
	अगर (!rdev->status_page) अणु
		err = -ENOMEM;
		जाओ destroy_ocqp_pool;
	पूर्ण
	rdev->status_page->qp_start = rdev->lldi.vr->qp.start;
	rdev->status_page->qp_size = rdev->lldi.vr->qp.size;
	rdev->status_page->cq_start = rdev->lldi.vr->cq.start;
	rdev->status_page->cq_size = rdev->lldi.vr->cq.size;
	rdev->status_page->ग_लिखो_cmpl_supported = rdev->lldi.ग_लिखो_cmpl_support;

	अगर (c4iw_wr_log) अणु
		rdev->wr_log = kसुस्मृति(1 << c4iw_wr_log_size_order,
				       माप(*rdev->wr_log),
				       GFP_KERNEL);
		अगर (rdev->wr_log) अणु
			rdev->wr_log_size = 1 << c4iw_wr_log_size_order;
			atomic_set(&rdev->wr_log_idx, 0);
		पूर्ण
	पूर्ण

	rdev->मुक्त_workq = create_singlethपढ़ो_workqueue("iw_cxgb4_free");
	अगर (!rdev->मुक्त_workq) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_status_page_and_wr_log;
	पूर्ण

	rdev->status_page->db_off = 0;

	init_completion(&rdev->rqt_compl);
	init_completion(&rdev->pbl_compl);
	kref_init(&rdev->rqt_kref);
	kref_init(&rdev->pbl_kref);

	वापस 0;
err_मुक्त_status_page_and_wr_log:
	अगर (c4iw_wr_log && rdev->wr_log)
		kमुक्त(rdev->wr_log);
	मुक्त_page((अचिन्हित दीर्घ)rdev->status_page);
destroy_ocqp_pool:
	c4iw_ocqp_pool_destroy(rdev);
destroy_rqtpool:
	c4iw_rqtpool_destroy(rdev);
destroy_pblpool:
	c4iw_pblpool_destroy(rdev);
destroy_resource:
	c4iw_destroy_resource(&rdev->resource);
	वापस err;
पूर्ण

अटल व्योम c4iw_rdev_बंद(काष्ठा c4iw_rdev *rdev)
अणु
	kमुक्त(rdev->wr_log);
	c4iw_release_dev_ucontext(rdev, &rdev->uctx);
	मुक्त_page((अचिन्हित दीर्घ)rdev->status_page);
	c4iw_pblpool_destroy(rdev);
	c4iw_rqtpool_destroy(rdev);
	रुको_क्रम_completion(&rdev->pbl_compl);
	रुको_क्रम_completion(&rdev->rqt_compl);
	c4iw_ocqp_pool_destroy(rdev);
	destroy_workqueue(rdev->मुक्त_workq);
	c4iw_destroy_resource(&rdev->resource);
पूर्ण

व्योम c4iw_dealloc(काष्ठा uld_ctx *ctx)
अणु
	c4iw_rdev_बंद(&ctx->dev->rdev);
	WARN_ON(!xa_empty(&ctx->dev->cqs));
	WARN_ON(!xa_empty(&ctx->dev->qps));
	WARN_ON(!xa_empty(&ctx->dev->mrs));
	रुको_event(ctx->dev->रुको, xa_empty(&ctx->dev->hwtids));
	WARN_ON(!xa_empty(&ctx->dev->stids));
	WARN_ON(!xa_empty(&ctx->dev->atids));
	अगर (ctx->dev->rdev.bar2_kva)
		iounmap(ctx->dev->rdev.bar2_kva);
	अगर (ctx->dev->rdev.oc_mw_kva)
		iounmap(ctx->dev->rdev.oc_mw_kva);
	ib_dealloc_device(&ctx->dev->ibdev);
	ctx->dev = शून्य;
पूर्ण

अटल व्योम c4iw_हटाओ(काष्ठा uld_ctx *ctx)
अणु
	pr_debug("c4iw_dev %p\n", ctx->dev);
	debugfs_हटाओ_recursive(ctx->dev->debugfs_root);
	c4iw_unरेजिस्टर_device(ctx->dev);
	c4iw_dealloc(ctx);
पूर्ण

अटल पूर्णांक rdma_supported(स्थिर काष्ठा cxgb4_lld_info *infop)
अणु
	वापस infop->vr->stag.size > 0 && infop->vr->pbl.size > 0 &&
	       infop->vr->rq.size > 0 && infop->vr->qp.size > 0 &&
	       infop->vr->cq.size > 0;
पूर्ण

अटल काष्ठा c4iw_dev *c4iw_alloc(स्थिर काष्ठा cxgb4_lld_info *infop)
अणु
	काष्ठा c4iw_dev *devp;
	पूर्णांक ret;

	अगर (!rdma_supported(infop)) अणु
		pr_info("%s: RDMA not supported on this device\n",
			pci_name(infop->pdev));
		वापस ERR_PTR(-ENOSYS);
	पूर्ण
	अगर (!ocqp_supported(infop))
		pr_info("%s: On-Chip Queues not supported on this device\n",
			pci_name(infop->pdev));

	devp = ib_alloc_device(c4iw_dev, ibdev);
	अगर (!devp) अणु
		pr_err("Cannot allocate ib device\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	devp->rdev.lldi = *infop;

	/* init various hw-queue params based on lld info */
	pr_debug("Ing. padding boundary is %d, egrsstatuspagesize = %d\n",
		 devp->rdev.lldi.sge_ingpadboundary,
		 devp->rdev.lldi.sge_egrstatuspagesize);

	devp->rdev.hw_queue.t4_eq_status_entries =
		devp->rdev.lldi.sge_egrstatuspagesize / 64;
	devp->rdev.hw_queue.t4_max_eq_size = 65520;
	devp->rdev.hw_queue.t4_max_iq_size = 65520;
	devp->rdev.hw_queue.t4_max_rq_size = 8192 -
		devp->rdev.hw_queue.t4_eq_status_entries - 1;
	devp->rdev.hw_queue.t4_max_sq_size =
		devp->rdev.hw_queue.t4_max_eq_size -
		devp->rdev.hw_queue.t4_eq_status_entries - 1;
	devp->rdev.hw_queue.t4_max_qp_depth =
		devp->rdev.hw_queue.t4_max_rq_size;
	devp->rdev.hw_queue.t4_max_cq_depth =
		devp->rdev.hw_queue.t4_max_iq_size - 2;
	devp->rdev.hw_queue.t4_stat_len =
		devp->rdev.lldi.sge_egrstatuspagesize;

	/*
	 * For T5/T6 devices, we map all of BAR2 with WC.
	 * For T4 devices with onchip qp mem, we map only that part
	 * of BAR2 with WC.
	 */
	devp->rdev.bar2_pa = pci_resource_start(devp->rdev.lldi.pdev, 2);
	अगर (!is_t4(devp->rdev.lldi.adapter_type)) अणु
		devp->rdev.bar2_kva = ioremap_wc(devp->rdev.bar2_pa,
			pci_resource_len(devp->rdev.lldi.pdev, 2));
		अगर (!devp->rdev.bar2_kva) अणु
			pr_err("Unable to ioremap BAR2\n");
			ib_dealloc_device(&devp->ibdev);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण अन्यथा अगर (ocqp_supported(infop)) अणु
		devp->rdev.oc_mw_pa =
			pci_resource_start(devp->rdev.lldi.pdev, 2) +
			pci_resource_len(devp->rdev.lldi.pdev, 2) -
			roundup_घात_of_two(devp->rdev.lldi.vr->ocq.size);
		devp->rdev.oc_mw_kva = ioremap_wc(devp->rdev.oc_mw_pa,
			devp->rdev.lldi.vr->ocq.size);
		अगर (!devp->rdev.oc_mw_kva) अणु
			pr_err("Unable to ioremap onchip mem\n");
			ib_dealloc_device(&devp->ibdev);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	pr_debug("ocq memory: hw_start 0x%x size %u mw_pa 0x%lx mw_kva %p\n",
		 devp->rdev.lldi.vr->ocq.start, devp->rdev.lldi.vr->ocq.size,
		 devp->rdev.oc_mw_pa, devp->rdev.oc_mw_kva);

	ret = c4iw_rdev_खोलो(&devp->rdev);
	अगर (ret) अणु
		pr_err("Unable to open CXIO rdev err %d\n", ret);
		ib_dealloc_device(&devp->ibdev);
		वापस ERR_PTR(ret);
	पूर्ण

	xa_init_flags(&devp->cqs, XA_FLAGS_LOCK_IRQ);
	xa_init_flags(&devp->qps, XA_FLAGS_LOCK_IRQ);
	xa_init_flags(&devp->mrs, XA_FLAGS_LOCK_IRQ);
	xa_init_flags(&devp->hwtids, XA_FLAGS_LOCK_IRQ);
	xa_init_flags(&devp->atids, XA_FLAGS_LOCK_IRQ);
	xa_init_flags(&devp->stids, XA_FLAGS_LOCK_IRQ);
	mutex_init(&devp->rdev.stats.lock);
	mutex_init(&devp->db_mutex);
	INIT_LIST_HEAD(&devp->db_fc_list);
	init_रुकोqueue_head(&devp->रुको);
	devp->avail_ird = devp->rdev.lldi.max_ird_adapter;

	अगर (c4iw_debugfs_root) अणु
		devp->debugfs_root = debugfs_create_dir(
					pci_name(devp->rdev.lldi.pdev),
					c4iw_debugfs_root);
		setup_debugfs(devp);
	पूर्ण


	वापस devp;
पूर्ण

अटल व्योम *c4iw_uld_add(स्थिर काष्ठा cxgb4_lld_info *infop)
अणु
	काष्ठा uld_ctx *ctx;
	अटल पूर्णांक vers_prपूर्णांकed;
	पूर्णांक i;

	अगर (!vers_prपूर्णांकed++)
		pr_info("Chelsio T4/T5 RDMA Driver - version %s\n",
			DRV_VERSION);

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		ctx = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	ctx->lldi = *infop;

	pr_debug("found device %s nchan %u nrxq %u ntxq %u nports %u\n",
		 pci_name(ctx->lldi.pdev),
		 ctx->lldi.nchan, ctx->lldi.nrxq,
		 ctx->lldi.ntxq, ctx->lldi.nports);

	mutex_lock(&dev_mutex);
	list_add_tail(&ctx->entry, &uld_ctx_list);
	mutex_unlock(&dev_mutex);

	क्रम (i = 0; i < ctx->lldi.nrxq; i++)
		pr_debug("rxqid[%u] %u\n", i, ctx->lldi.rxq_ids[i]);
out:
	वापस ctx;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *copy_gl_to_skb_pkt(स्थिर काष्ठा pkt_gl *gl,
						 स्थिर __be64 *rsp,
						 u32 pktshअगरt)
अणु
	काष्ठा sk_buff *skb;

	/*
	 * Allocate space क्रम cpl_pass_accept_req which will be synthesized by
	 * driver. Once the driver synthesizes the request the skb will go
	 * through the regular cpl_pass_accept_req processing.
	 * The math here assumes माप cpl_pass_accept_req >= माप
	 * cpl_rx_pkt.
	 */
	skb = alloc_skb(gl->tot_len + माप(काष्ठा cpl_pass_accept_req) +
			माप(काष्ठा rss_header) - pktshअगरt, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस शून्य;

	__skb_put(skb, gl->tot_len + माप(काष्ठा cpl_pass_accept_req) +
		  माप(काष्ठा rss_header) - pktshअगरt);

	/*
	 * This skb will contain:
	 *   rss_header from the rspq descriptor (1 flit)
	 *   cpl_rx_pkt काष्ठा from the rspq descriptor (2 flits)
	 *   space क्रम the dअगरference between the size of an
	 *      rx_pkt and pass_accept_req cpl (1 flit)
	 *   the packet data from the gl
	 */
	skb_copy_to_linear_data(skb, rsp, माप(काष्ठा cpl_pass_accept_req) +
				माप(काष्ठा rss_header));
	skb_copy_to_linear_data_offset(skb, माप(काष्ठा rss_header) +
				       माप(काष्ठा cpl_pass_accept_req),
				       gl->va + pktshअगरt,
				       gl->tot_len - pktshअगरt);
	वापस skb;
पूर्ण

अटल अंतरभूत पूर्णांक recv_rx_pkt(काष्ठा c4iw_dev *dev, स्थिर काष्ठा pkt_gl *gl,
			   स्थिर __be64 *rsp)
अणु
	अचिन्हित पूर्णांक opcode = *(u8 *)rsp;
	काष्ठा sk_buff *skb;

	अगर (opcode != CPL_RX_PKT)
		जाओ out;

	skb = copy_gl_to_skb_pkt(gl , rsp, dev->rdev.lldi.sge_pktshअगरt);
	अगर (skb == शून्य)
		जाओ out;

	अगर (c4iw_handlers[opcode] == शून्य) अणु
		pr_info("%s no handler opcode 0x%x...\n", __func__, opcode);
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण
	c4iw_handlers[opcode](dev, skb);
	वापस 1;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक c4iw_uld_rx_handler(व्योम *handle, स्थिर __be64 *rsp,
			स्थिर काष्ठा pkt_gl *gl)
अणु
	काष्ठा uld_ctx *ctx = handle;
	काष्ठा c4iw_dev *dev = ctx->dev;
	काष्ठा sk_buff *skb;
	u8 opcode;

	अगर (gl == शून्य) अणु
		/* omit RSS and rsp_ctrl at end of descriptor */
		अचिन्हित पूर्णांक len = 64 - माप(काष्ठा rsp_ctrl) - 8;

		skb = alloc_skb(256, GFP_ATOMIC);
		अगर (!skb)
			जाओ nomem;
		__skb_put(skb, len);
		skb_copy_to_linear_data(skb, &rsp[1], len);
	पूर्ण अन्यथा अगर (gl == CXGB4_MSG_AN) अणु
		स्थिर काष्ठा rsp_ctrl *rc = (व्योम *)rsp;

		u32 qid = be32_to_cpu(rc->pldbuflen_qid);
		c4iw_ev_handler(dev, qid);
		वापस 0;
	पूर्ण अन्यथा अगर (unlikely(*(u8 *)rsp != *(u8 *)gl->va)) अणु
		अगर (recv_rx_pkt(dev, gl, rsp))
			वापस 0;

		pr_info("%s: unexpected FL contents at %p, RSS %#llx, FL %#llx, len %u\n",
			pci_name(ctx->lldi.pdev), gl->va,
			be64_to_cpu(*rsp),
			be64_to_cpu(*(__क्रमce __be64 *)gl->va),
			gl->tot_len);

		वापस 0;
	पूर्ण अन्यथा अणु
		skb = cxgb4_pktgl_to_skb(gl, 128, 128);
		अगर (unlikely(!skb))
			जाओ nomem;
	पूर्ण

	opcode = *(u8 *)rsp;
	अगर (c4iw_handlers[opcode]) अणु
		c4iw_handlers[opcode](dev, skb);
	पूर्ण अन्यथा अणु
		pr_info("%s no handler opcode 0x%x...\n", __func__, opcode);
		kमुक्त_skb(skb);
	पूर्ण

	वापस 0;
nomem:
	वापस -1;
पूर्ण

अटल पूर्णांक c4iw_uld_state_change(व्योम *handle, क्रमागत cxgb4_state new_state)
अणु
	काष्ठा uld_ctx *ctx = handle;

	pr_debug("new_state %u\n", new_state);
	चयन (new_state) अणु
	हाल CXGB4_STATE_UP:
		pr_info("%s: Up\n", pci_name(ctx->lldi.pdev));
		अगर (!ctx->dev) अणु
			ctx->dev = c4iw_alloc(&ctx->lldi);
			अगर (IS_ERR(ctx->dev)) अणु
				pr_err("%s: initialization failed: %ld\n",
				       pci_name(ctx->lldi.pdev),
				       PTR_ERR(ctx->dev));
				ctx->dev = शून्य;
				अवरोध;
			पूर्ण

			INIT_WORK(&ctx->reg_work, c4iw_रेजिस्टर_device);
			queue_work(reg_workq, &ctx->reg_work);
		पूर्ण
		अवरोध;
	हाल CXGB4_STATE_DOWN:
		pr_info("%s: Down\n", pci_name(ctx->lldi.pdev));
		अगर (ctx->dev)
			c4iw_हटाओ(ctx);
		अवरोध;
	हाल CXGB4_STATE_FATAL_ERROR:
	हाल CXGB4_STATE_START_RECOVERY:
		pr_info("%s: Fatal Error\n", pci_name(ctx->lldi.pdev));
		अगर (ctx->dev) अणु
			काष्ठा ib_event event = अणुपूर्ण;

			ctx->dev->rdev.flags |= T4_FATAL_ERROR;
			event.event  = IB_EVENT_DEVICE_FATAL;
			event.device = &ctx->dev->ibdev;
			ib_dispatch_event(&event);
			c4iw_हटाओ(ctx);
		पूर्ण
		अवरोध;
	हाल CXGB4_STATE_DETACH:
		pr_info("%s: Detach\n", pci_name(ctx->lldi.pdev));
		अगर (ctx->dev)
			c4iw_हटाओ(ctx);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम stop_queues(काष्ठा uld_ctx *ctx)
अणु
	काष्ठा c4iw_qp *qp;
	अचिन्हित दीर्घ index, flags;

	xa_lock_irqsave(&ctx->dev->qps, flags);
	ctx->dev->rdev.stats.db_state_transitions++;
	ctx->dev->db_state = STOPPED;
	अगर (ctx->dev->rdev.flags & T4_STATUS_PAGE_DISABLED) अणु
		xa_क्रम_each(&ctx->dev->qps, index, qp)
			t4_disable_wq_db(&qp->wq);
	पूर्ण अन्यथा अणु
		ctx->dev->rdev.status_page->db_off = 1;
	पूर्ण
	xa_unlock_irqrestore(&ctx->dev->qps, flags);
पूर्ण

अटल व्योम resume_rc_qp(काष्ठा c4iw_qp *qp)
अणु
	spin_lock(&qp->lock);
	t4_ring_sq_db(&qp->wq, qp->wq.sq.wq_pidx_inc, शून्य);
	qp->wq.sq.wq_pidx_inc = 0;
	t4_ring_rq_db(&qp->wq, qp->wq.rq.wq_pidx_inc, शून्य);
	qp->wq.rq.wq_pidx_inc = 0;
	spin_unlock(&qp->lock);
पूर्ण

अटल व्योम resume_a_chunk(काष्ठा uld_ctx *ctx)
अणु
	पूर्णांक i;
	काष्ठा c4iw_qp *qp;

	क्रम (i = 0; i < DB_FC_RESUME_SIZE; i++) अणु
		qp = list_first_entry(&ctx->dev->db_fc_list, काष्ठा c4iw_qp,
				      db_fc_entry);
		list_del_init(&qp->db_fc_entry);
		resume_rc_qp(qp);
		अगर (list_empty(&ctx->dev->db_fc_list))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम resume_queues(काष्ठा uld_ctx *ctx)
अणु
	xa_lock_irq(&ctx->dev->qps);
	अगर (ctx->dev->db_state != STOPPED)
		जाओ out;
	ctx->dev->db_state = FLOW_CONTROL;
	जबतक (1) अणु
		अगर (list_empty(&ctx->dev->db_fc_list)) अणु
			काष्ठा c4iw_qp *qp;
			अचिन्हित दीर्घ index;

			WARN_ON(ctx->dev->db_state != FLOW_CONTROL);
			ctx->dev->db_state = NORMAL;
			ctx->dev->rdev.stats.db_state_transitions++;
			अगर (ctx->dev->rdev.flags & T4_STATUS_PAGE_DISABLED) अणु
				xa_क्रम_each(&ctx->dev->qps, index, qp)
					t4_enable_wq_db(&qp->wq);
			पूर्ण अन्यथा अणु
				ctx->dev->rdev.status_page->db_off = 0;
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अणु
			अगर (cxgb4_dbfअगरo_count(ctx->dev->rdev.lldi.ports[0], 1)
			    < (ctx->dev->rdev.lldi.dbfअगरo_पूर्णांक_thresh <<
			       DB_FC_DRAIN_THRESH)) अणु
				resume_a_chunk(ctx);
			पूर्ण
			अगर (!list_empty(&ctx->dev->db_fc_list)) अणु
				xa_unlock_irq(&ctx->dev->qps);
				अगर (DB_FC_RESUME_DELAY) अणु
					set_current_state(TASK_UNINTERRUPTIBLE);
					schedule_समयout(DB_FC_RESUME_DELAY);
				पूर्ण
				xa_lock_irq(&ctx->dev->qps);
				अगर (ctx->dev->db_state != FLOW_CONTROL)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	अगर (ctx->dev->db_state != NORMAL)
		ctx->dev->rdev.stats.db_fc_पूर्णांकerruptions++;
	xa_unlock_irq(&ctx->dev->qps);
पूर्ण

काष्ठा qp_list अणु
	अचिन्हित idx;
	काष्ठा c4iw_qp **qps;
पूर्ण;

अटल व्योम deref_qps(काष्ठा qp_list *qp_list)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < qp_list->idx; idx++)
		c4iw_qp_rem_ref(&qp_list->qps[idx]->ibqp);
पूर्ण

अटल व्योम recover_lost_dbs(काष्ठा uld_ctx *ctx, काष्ठा qp_list *qp_list)
अणु
	पूर्णांक idx;
	पूर्णांक ret;

	क्रम (idx = 0; idx < qp_list->idx; idx++) अणु
		काष्ठा c4iw_qp *qp = qp_list->qps[idx];

		xa_lock_irq(&qp->rhp->qps);
		spin_lock(&qp->lock);
		ret = cxgb4_sync_txq_pidx(qp->rhp->rdev.lldi.ports[0],
					  qp->wq.sq.qid,
					  t4_sq_host_wq_pidx(&qp->wq),
					  t4_sq_wq_size(&qp->wq));
		अगर (ret) अणु
			pr_err("%s: Fatal error - DB overflow recovery failed - error syncing SQ qid %u\n",
			       pci_name(ctx->lldi.pdev), qp->wq.sq.qid);
			spin_unlock(&qp->lock);
			xa_unlock_irq(&qp->rhp->qps);
			वापस;
		पूर्ण
		qp->wq.sq.wq_pidx_inc = 0;

		ret = cxgb4_sync_txq_pidx(qp->rhp->rdev.lldi.ports[0],
					  qp->wq.rq.qid,
					  t4_rq_host_wq_pidx(&qp->wq),
					  t4_rq_wq_size(&qp->wq));

		अगर (ret) अणु
			pr_err("%s: Fatal error - DB overflow recovery failed - error syncing RQ qid %u\n",
			       pci_name(ctx->lldi.pdev), qp->wq.rq.qid);
			spin_unlock(&qp->lock);
			xa_unlock_irq(&qp->rhp->qps);
			वापस;
		पूर्ण
		qp->wq.rq.wq_pidx_inc = 0;
		spin_unlock(&qp->lock);
		xa_unlock_irq(&qp->rhp->qps);

		/* Wait क्रम the dbfअगरo to drain */
		जबतक (cxgb4_dbfअगरo_count(qp->rhp->rdev.lldi.ports[0], 1) > 0) अणु
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_समयout(usecs_to_jअगरfies(10));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम recover_queues(काष्ठा uld_ctx *ctx)
अणु
	काष्ठा c4iw_qp *qp;
	अचिन्हित दीर्घ index;
	पूर्णांक count = 0;
	काष्ठा qp_list qp_list;
	पूर्णांक ret;

	/* slow everybody करोwn */
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_समयout(usecs_to_jअगरfies(1000));

	/* flush the SGE contexts */
	ret = cxgb4_flush_eq_cache(ctx->dev->rdev.lldi.ports[0]);
	अगर (ret) अणु
		pr_err("%s: Fatal error - DB overflow recovery failed\n",
		       pci_name(ctx->lldi.pdev));
		वापस;
	पूर्ण

	/* Count active queues so we can build a list of queues to recover */
	xa_lock_irq(&ctx->dev->qps);
	WARN_ON(ctx->dev->db_state != STOPPED);
	ctx->dev->db_state = RECOVERY;
	xa_क्रम_each(&ctx->dev->qps, index, qp)
		count++;

	qp_list.qps = kसुस्मृति(count, माप(*qp_list.qps), GFP_ATOMIC);
	अगर (!qp_list.qps) अणु
		xa_unlock_irq(&ctx->dev->qps);
		वापस;
	पूर्ण
	qp_list.idx = 0;

	/* add and ref each qp so it करोesn't get मुक्तd */
	xa_क्रम_each(&ctx->dev->qps, index, qp) अणु
		c4iw_qp_add_ref(&qp->ibqp);
		qp_list.qps[qp_list.idx++] = qp;
	पूर्ण

	xa_unlock_irq(&ctx->dev->qps);

	/* now traverse the list in a safe context to recover the db state*/
	recover_lost_dbs(ctx, &qp_list);

	/* we're almost करोne!  deref the qps and clean up */
	deref_qps(&qp_list);
	kमुक्त(qp_list.qps);

	xa_lock_irq(&ctx->dev->qps);
	WARN_ON(ctx->dev->db_state != RECOVERY);
	ctx->dev->db_state = STOPPED;
	xa_unlock_irq(&ctx->dev->qps);
पूर्ण

अटल पूर्णांक c4iw_uld_control(व्योम *handle, क्रमागत cxgb4_control control, ...)
अणु
	काष्ठा uld_ctx *ctx = handle;

	चयन (control) अणु
	हाल CXGB4_CONTROL_DB_FULL:
		stop_queues(ctx);
		ctx->dev->rdev.stats.db_full++;
		अवरोध;
	हाल CXGB4_CONTROL_DB_EMPTY:
		resume_queues(ctx);
		mutex_lock(&ctx->dev->rdev.stats.lock);
		ctx->dev->rdev.stats.db_empty++;
		mutex_unlock(&ctx->dev->rdev.stats.lock);
		अवरोध;
	हाल CXGB4_CONTROL_DB_DROP:
		recover_queues(ctx);
		mutex_lock(&ctx->dev->rdev.stats.lock);
		ctx->dev->rdev.stats.db_drop++;
		mutex_unlock(&ctx->dev->rdev.stats.lock);
		अवरोध;
	शेष:
		pr_warn("%s: unknown control cmd %u\n",
			pci_name(ctx->lldi.pdev), control);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा cxgb4_uld_info c4iw_uld_info = अणु
	.name = DRV_NAME,
	.nrxq = MAX_ULD_QSETS,
	.ntxq = MAX_ULD_QSETS,
	.rxq_size = 511,
	.ciq = true,
	.lro = false,
	.add = c4iw_uld_add,
	.rx_handler = c4iw_uld_rx_handler,
	.state_change = c4iw_uld_state_change,
	.control = c4iw_uld_control,
पूर्ण;

व्योम _c4iw_मुक्त_wr_रुको(काष्ठा kref *kref)
अणु
	काष्ठा c4iw_wr_रुको *wr_रुकोp;

	wr_रुकोp = container_of(kref, काष्ठा c4iw_wr_रुको, kref);
	pr_debug("Free wr_wait %p\n", wr_रुकोp);
	kमुक्त(wr_रुकोp);
पूर्ण

काष्ठा c4iw_wr_रुको *c4iw_alloc_wr_रुको(gfp_t gfp)
अणु
	काष्ठा c4iw_wr_रुको *wr_रुकोp;

	wr_रुकोp = kzalloc(माप(*wr_रुकोp), gfp);
	अगर (wr_रुकोp) अणु
		kref_init(&wr_रुकोp->kref);
		pr_debug("wr_wait %p\n", wr_रुकोp);
	पूर्ण
	वापस wr_रुकोp;
पूर्ण

अटल पूर्णांक __init c4iw_init_module(व्योम)
अणु
	पूर्णांक err;

	err = c4iw_cm_init();
	अगर (err)
		वापस err;

	c4iw_debugfs_root = debugfs_create_dir(DRV_NAME, शून्य);

	reg_workq = create_singlethपढ़ो_workqueue("Register_iWARP_device");
	अगर (!reg_workq) अणु
		pr_err("Failed creating workqueue to register iwarp device\n");
		वापस -ENOMEM;
	पूर्ण

	cxgb4_रेजिस्टर_uld(CXGB4_ULD_RDMA, &c4iw_uld_info);

	वापस 0;
पूर्ण

अटल व्योम __निकास c4iw_निकास_module(व्योम)
अणु
	काष्ठा uld_ctx *ctx, *पंचांगp;

	mutex_lock(&dev_mutex);
	list_क्रम_each_entry_safe(ctx, पंचांगp, &uld_ctx_list, entry) अणु
		अगर (ctx->dev)
			c4iw_हटाओ(ctx);
		kमुक्त(ctx);
	पूर्ण
	mutex_unlock(&dev_mutex);
	flush_workqueue(reg_workq);
	destroy_workqueue(reg_workq);
	cxgb4_unरेजिस्टर_uld(CXGB4_ULD_RDMA);
	c4iw_cm_term();
	debugfs_हटाओ_recursive(c4iw_debugfs_root);
पूर्ण

module_init(c4iw_init_module);
module_निकास(c4iw_निकास_module);
