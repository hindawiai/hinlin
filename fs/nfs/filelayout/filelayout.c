<शैली गुरु>
/*
 *  Module क्रम the pnfs nfs4 file layout driver.
 *  Defines all I/O and Policy पूर्णांकerface operations, plus code
 *  to रेजिस्टर itself with the pNFS client.
 *
 *  Copyright (c) 2002
 *  The Regents of the University of Michigan
 *  All Rights Reserved
 *
 *  Dean Hildebअक्रम <dhildebz@umich.edu>
 *
 *  Permission is granted to use, copy, create derivative works, and
 *  redistribute this software and such derivative works क्रम any purpose,
 *  so दीर्घ as the name of the University of Michigan is not used in
 *  any advertising or खुलाity pertaining to the use or distribution
 *  of this software without specअगरic, written prior authorization. If
 *  the above copyright notice or any other identअगरication of the
 *  University of Michigan is included in any copy of any portion of
 *  this software, then the disclaimer below must also be included.
 *
 *  This software is provided as is, without representation or warranty
 *  of any kind either express or implied, including without limitation
 *  the implied warranties of merchantability, fitness क्रम a particular
 *  purpose, or noninfringement.  The Regents of the University of
 *  Michigan shall not be liable क्रम any damages, including special,
 *  indirect, incidental, or consequential damages, with respect to any
 *  claim arising out of or in connection with the use of the software,
 *  even अगर it has been or is hereafter advised of the possibility of
 *  such damages.
 */

#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/module.h>
#समावेश <linux/backing-dev.h>

#समावेश <linux/sunrpc/metrics.h>

#समावेश "../nfs4session.h"
#समावेश "../internal.h"
#समावेश "../delegation.h"
#समावेश "filelayout.h"
#समावेश "../nfs4trace.h"

#घोषणा NFSDBG_FACILITY         NFSDBG_PNFS_LD

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dean Hildebrand <dhildebz@umich.edu>");
MODULE_DESCRIPTION("The NFSv4 file layout driver");

#घोषणा खाताLAYOUT_POLL_RETRY_MAX     (15*HZ)
अटल स्थिर काष्ठा pnfs_commit_ops filelayout_commit_ops;

अटल loff_t
filelayout_get_dense_offset(काष्ठा nfs4_filelayout_segment *flseg,
			    loff_t offset)
अणु
	u32 stripe_width = flseg->stripe_unit * flseg->dsaddr->stripe_count;
	u64 stripe_no;
	u32 rem;

	offset -= flseg->pattern_offset;
	stripe_no = भाग_u64(offset, stripe_width);
	भाग_u64_rem(offset, flseg->stripe_unit, &rem);

	वापस stripe_no * flseg->stripe_unit + rem;
पूर्ण

/* This function is used by the layout driver to calculate the
 * offset of the file on the dserver based on whether the
 * layout type is STRIPE_DENSE or STRIPE_SPARSE
 */
अटल loff_t
filelayout_get_dserver_offset(काष्ठा pnfs_layout_segment *lseg, loff_t offset)
अणु
	काष्ठा nfs4_filelayout_segment *flseg = खाताLAYOUT_LSEG(lseg);

	चयन (flseg->stripe_type) अणु
	हाल STRIPE_SPARSE:
		वापस offset;

	हाल STRIPE_DENSE:
		वापस filelayout_get_dense_offset(flseg, offset);
	पूर्ण

	BUG();
पूर्ण

अटल व्योम filelayout_reset_ग_लिखो(काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा rpc_task *task = &hdr->task;

	अगर (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) अणु
		dprपूर्णांकk("%s Reset task %5u for i/o through MDS "
			"(req %s/%llu, %u bytes @ offset %llu)\n", __func__,
			hdr->task.tk_pid,
			hdr->inode->i_sb->s_id,
			(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(hdr->inode),
			hdr->args.count,
			(अचिन्हित दीर्घ दीर्घ)hdr->args.offset);

		task->tk_status = pnfs_ग_लिखो_करोne_resend_to_mds(hdr);
	पूर्ण
पूर्ण

अटल व्योम filelayout_reset_पढ़ो(काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा rpc_task *task = &hdr->task;

	अगर (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) अणु
		dprपूर्णांकk("%s Reset task %5u for i/o through MDS "
			"(req %s/%llu, %u bytes @ offset %llu)\n", __func__,
			hdr->task.tk_pid,
			hdr->inode->i_sb->s_id,
			(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(hdr->inode),
			hdr->args.count,
			(अचिन्हित दीर्घ दीर्घ)hdr->args.offset);

		task->tk_status = pnfs_पढ़ो_करोne_resend_to_mds(hdr);
	पूर्ण
पूर्ण

अटल पूर्णांक filelayout_async_handle_error(काष्ठा rpc_task *task,
					 काष्ठा nfs4_state *state,
					 काष्ठा nfs_client *clp,
					 काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा pnfs_layout_hdr *lo = lseg->pls_layout;
	काष्ठा inode *inode = lo->plh_inode;
	काष्ठा nfs4_deviceid_node *devid = खाताLAYOUT_DEVID_NODE(lseg);
	काष्ठा nfs4_slot_table *tbl = &clp->cl_session->fc_slot_table;

	अगर (task->tk_status >= 0)
		वापस 0;

	चयन (task->tk_status) अणु
	/* DS session errors */
	हाल -NFS4ERR_BADSESSION:
	हाल -NFS4ERR_BADSLOT:
	हाल -NFS4ERR_BAD_HIGH_SLOT:
	हाल -NFS4ERR_DEADSESSION:
	हाल -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
	हाल -NFS4ERR_SEQ_FALSE_RETRY:
	हाल -NFS4ERR_SEQ_MISORDERED:
		dprपूर्णांकk("%s ERROR %d, Reset session. Exchangeid "
			"flags 0x%x\n", __func__, task->tk_status,
			clp->cl_exchange_flags);
		nfs4_schedule_session_recovery(clp->cl_session, task->tk_status);
		अवरोध;
	हाल -NFS4ERR_DELAY:
	हाल -NFS4ERR_GRACE:
		rpc_delay(task, खाताLAYOUT_POLL_RETRY_MAX);
		अवरोध;
	हाल -NFS4ERR_RETRY_UNCACHED_REP:
		अवरोध;
	/* Invalidate Layout errors */
	हाल -NFS4ERR_ACCESS:
	हाल -NFS4ERR_PNFS_NO_LAYOUT:
	हाल -ESTALE:           /* mapped NFS4ERR_STALE */
	हाल -EBADHANDLE:       /* mapped NFS4ERR_BADHANDLE */
	हाल -EISसूची:           /* mapped NFS4ERR_ISसूची */
	हाल -NFS4ERR_FHEXPIRED:
	हाल -NFS4ERR_WRONG_TYPE:
		dprपूर्णांकk("%s Invalid layout error %d\n", __func__,
			task->tk_status);
		/*
		 * Destroy layout so new i/o will get a new layout.
		 * Layout will not be destroyed until all current lseg
		 * references are put. Mark layout as invalid to resend failed
		 * i/o and all i/o रुकोing on the slot table to the MDS until
		 * layout is destroyed and a new valid layout is obtained.
		 */
		pnfs_destroy_layout(NFS_I(inode));
		rpc_wake_up(&tbl->slot_tbl_रुकोq);
		जाओ reset;
	/* RPC connection errors */
	हाल -ECONNREFUSED:
	हाल -EHOSTDOWN:
	हाल -EHOSTUNREACH:
	हाल -ENETUNREACH:
	हाल -EIO:
	हाल -ETIMEDOUT:
	हाल -EPIPE:
		dprपूर्णांकk("%s DS connection error %d\n", __func__,
			task->tk_status);
		nfs4_mark_deviceid_unavailable(devid);
		pnfs_error_mark_layout_क्रम_वापस(inode, lseg);
		pnfs_set_lo_fail(lseg);
		rpc_wake_up(&tbl->slot_tbl_रुकोq);
		fallthrough;
	शेष:
reset:
		dprपूर्णांकk("%s Retry through MDS. Error %d\n", __func__,
			task->tk_status);
		वापस -NFS4ERR_RESET_TO_MDS;
	पूर्ण
	task->tk_status = 0;
	वापस -EAGAIN;
पूर्ण

/* NFS_PROTO call करोne callback routines */

अटल पूर्णांक filelayout_पढ़ो_करोne_cb(काष्ठा rpc_task *task,
				काष्ठा nfs_pgio_header *hdr)
अणु
	पूर्णांक err;

	trace_nfs4_pnfs_पढ़ो(hdr, task->tk_status);
	err = filelayout_async_handle_error(task, hdr->args.context->state,
					    hdr->ds_clp, hdr->lseg);

	चयन (err) अणु
	हाल -NFS4ERR_RESET_TO_MDS:
		filelayout_reset_पढ़ो(hdr);
		वापस task->tk_status;
	हाल -EAGAIN:
		rpc_restart_call_prepare(task);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * We reference the rpc_cred of the first WRITE that triggers the need क्रम
 * a LAYOUTCOMMIT, and use it to send the layoutcommit compound.
 * rfc5661 is not clear about which credential should be used.
 */
अटल व्योम
filelayout_set_layoutcommit(काष्ठा nfs_pgio_header *hdr)
अणु
	loff_t end_offs = 0;

	अगर (खाताLAYOUT_LSEG(hdr->lseg)->commit_through_mds ||
	    hdr->res.verf->committed == NFS_खाता_SYNC)
		वापस;
	अगर (hdr->res.verf->committed == NFS_DATA_SYNC)
		end_offs = hdr->mds_offset + (loff_t)hdr->res.count;

	/* Note: अगर the ग_लिखो is unstable, करोn't set end_offs until commit */
	pnfs_set_layoutcommit(hdr->inode, hdr->lseg, end_offs);
	dprपूर्णांकk("%s inode %lu pls_end_pos %lu\n", __func__, hdr->inode->i_ino,
		(अचिन्हित दीर्घ) NFS_I(hdr->inode)->layout->plh_lwb);
पूर्ण

bool
filelayout_test_devid_unavailable(काष्ठा nfs4_deviceid_node *node)
अणु
	वापस filelayout_test_devid_invalid(node) ||
		nfs4_test_deviceid_unavailable(node);
पूर्ण

अटल bool
filelayout_reset_to_mds(काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा nfs4_deviceid_node *node = खाताLAYOUT_DEVID_NODE(lseg);

	वापस filelayout_test_devid_unavailable(node);
पूर्ण

/*
 * Call ops क्रम the async पढ़ो/ग_लिखो हालs
 * In the हाल of dense layouts, the offset needs to be reset to its
 * original value.
 */
अटल व्योम filelayout_पढ़ो_prepare(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	अगर (unlikely(test_bit(NFS_CONTEXT_BAD, &hdr->args.context->flags))) अणु
		rpc_निकास(task, -EIO);
		वापस;
	पूर्ण
	अगर (filelayout_reset_to_mds(hdr->lseg)) अणु
		dprपूर्णांकk("%s task %u reset io to MDS\n", __func__, task->tk_pid);
		filelayout_reset_पढ़ो(hdr);
		rpc_निकास(task, 0);
		वापस;
	पूर्ण
	hdr->pgio_करोne_cb = filelayout_पढ़ो_करोne_cb;

	अगर (nfs4_setup_sequence(hdr->ds_clp,
			&hdr->args.seq_args,
			&hdr->res.seq_res,
			task))
		वापस;
	अगर (nfs4_set_rw_stateid(&hdr->args.stateid, hdr->args.context,
			hdr->args.lock_context, FMODE_READ) == -EIO)
		rpc_निकास(task, -EIO); /* lost lock, terminate I/O */
पूर्ण

अटल व्योम filelayout_पढ़ो_call_करोne(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	dprपूर्णांकk("--> %s task->tk_status %d\n", __func__, task->tk_status);

	अगर (test_bit(NFS_IOHDR_REDO, &hdr->flags) &&
	    task->tk_status == 0) अणु
		nfs41_sequence_करोne(task, &hdr->res.seq_res);
		वापस;
	पूर्ण

	/* Note this may cause RPC to be resent */
	hdr->mds_ops->rpc_call_करोne(task, data);
पूर्ण

अटल व्योम filelayout_पढ़ो_count_stats(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	rpc_count_iostats(task, NFS_SERVER(hdr->inode)->client->cl_metrics);
पूर्ण

अटल पूर्णांक filelayout_ग_लिखो_करोne_cb(काष्ठा rpc_task *task,
				काष्ठा nfs_pgio_header *hdr)
अणु
	पूर्णांक err;

	trace_nfs4_pnfs_ग_लिखो(hdr, task->tk_status);
	err = filelayout_async_handle_error(task, hdr->args.context->state,
					    hdr->ds_clp, hdr->lseg);

	चयन (err) अणु
	हाल -NFS4ERR_RESET_TO_MDS:
		filelayout_reset_ग_लिखो(hdr);
		वापस task->tk_status;
	हाल -EAGAIN:
		rpc_restart_call_prepare(task);
		वापस -EAGAIN;
	पूर्ण

	filelayout_set_layoutcommit(hdr);

	/* zero out the fattr */
	hdr->fattr.valid = 0;
	अगर (task->tk_status >= 0)
		nfs_ग_लिखोback_update_inode(hdr);

	वापस 0;
पूर्ण

अटल पूर्णांक filelayout_commit_करोne_cb(काष्ठा rpc_task *task,
				     काष्ठा nfs_commit_data *data)
अणु
	पूर्णांक err;

	trace_nfs4_pnfs_commit_ds(data, task->tk_status);
	err = filelayout_async_handle_error(task, शून्य, data->ds_clp,
					    data->lseg);

	चयन (err) अणु
	हाल -NFS4ERR_RESET_TO_MDS:
		pnfs_generic_prepare_to_resend_ग_लिखोs(data);
		वापस -EAGAIN;
	हाल -EAGAIN:
		rpc_restart_call_prepare(task);
		वापस -EAGAIN;
	पूर्ण

	pnfs_set_layoutcommit(data->inode, data->lseg, data->lwb);

	वापस 0;
पूर्ण

अटल व्योम filelayout_ग_लिखो_prepare(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	अगर (unlikely(test_bit(NFS_CONTEXT_BAD, &hdr->args.context->flags))) अणु
		rpc_निकास(task, -EIO);
		वापस;
	पूर्ण
	अगर (filelayout_reset_to_mds(hdr->lseg)) अणु
		dprपूर्णांकk("%s task %u reset io to MDS\n", __func__, task->tk_pid);
		filelayout_reset_ग_लिखो(hdr);
		rpc_निकास(task, 0);
		वापस;
	पूर्ण
	अगर (nfs4_setup_sequence(hdr->ds_clp,
			&hdr->args.seq_args,
			&hdr->res.seq_res,
			task))
		वापस;
	अगर (nfs4_set_rw_stateid(&hdr->args.stateid, hdr->args.context,
			hdr->args.lock_context, FMODE_WRITE) == -EIO)
		rpc_निकास(task, -EIO); /* lost lock, terminate I/O */
पूर्ण

अटल व्योम filelayout_ग_लिखो_call_करोne(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	अगर (test_bit(NFS_IOHDR_REDO, &hdr->flags) &&
	    task->tk_status == 0) अणु
		nfs41_sequence_करोne(task, &hdr->res.seq_res);
		वापस;
	पूर्ण

	/* Note this may cause RPC to be resent */
	hdr->mds_ops->rpc_call_करोne(task, data);
पूर्ण

अटल व्योम filelayout_ग_लिखो_count_stats(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	rpc_count_iostats(task, NFS_SERVER(hdr->inode)->client->cl_metrics);
पूर्ण

अटल व्योम filelayout_commit_prepare(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_commit_data *wdata = data;

	nfs4_setup_sequence(wdata->ds_clp,
			&wdata->args.seq_args,
			&wdata->res.seq_res,
			task);
पूर्ण

अटल व्योम filelayout_commit_count_stats(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_commit_data *cdata = data;

	rpc_count_iostats(task, NFS_SERVER(cdata->inode)->client->cl_metrics);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops filelayout_पढ़ो_call_ops = अणु
	.rpc_call_prepare = filelayout_पढ़ो_prepare,
	.rpc_call_करोne = filelayout_पढ़ो_call_करोne,
	.rpc_count_stats = filelayout_पढ़ो_count_stats,
	.rpc_release = pnfs_generic_rw_release,
पूर्ण;

अटल स्थिर काष्ठा rpc_call_ops filelayout_ग_लिखो_call_ops = अणु
	.rpc_call_prepare = filelayout_ग_लिखो_prepare,
	.rpc_call_करोne = filelayout_ग_लिखो_call_करोne,
	.rpc_count_stats = filelayout_ग_लिखो_count_stats,
	.rpc_release = pnfs_generic_rw_release,
पूर्ण;

अटल स्थिर काष्ठा rpc_call_ops filelayout_commit_call_ops = अणु
	.rpc_call_prepare = filelayout_commit_prepare,
	.rpc_call_करोne = pnfs_generic_ग_लिखो_commit_करोne,
	.rpc_count_stats = filelayout_commit_count_stats,
	.rpc_release = pnfs_generic_commit_release,
पूर्ण;

अटल क्रमागत pnfs_try_status
filelayout_पढ़ो_pagelist(काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा pnfs_layout_segment *lseg = hdr->lseg;
	काष्ठा nfs4_pnfs_ds *ds;
	काष्ठा rpc_clnt *ds_clnt;
	loff_t offset = hdr->args.offset;
	u32 j, idx;
	काष्ठा nfs_fh *fh;

	dprपूर्णांकk("--> %s ino %lu pgbase %u req %zu@%llu\n",
		__func__, hdr->inode->i_ino,
		hdr->args.pgbase, (माप_प्रकार)hdr->args.count, offset);

	/* Retrieve the correct rpc_client क्रम the byte range */
	j = nfs4_fl_calc_j_index(lseg, offset);
	idx = nfs4_fl_calc_ds_index(lseg, j);
	ds = nfs4_fl_prepare_ds(lseg, idx);
	अगर (!ds)
		वापस PNFS_NOT_ATTEMPTED;

	ds_clnt = nfs4_find_or_create_ds_client(ds->ds_clp, hdr->inode);
	अगर (IS_ERR(ds_clnt))
		वापस PNFS_NOT_ATTEMPTED;

	dprपूर्णांकk("%s USE DS: %s cl_count %d\n", __func__,
		ds->ds_remotestr, refcount_पढ़ो(&ds->ds_clp->cl_count));

	/* No multipath support. Use first DS */
	refcount_inc(&ds->ds_clp->cl_count);
	hdr->ds_clp = ds->ds_clp;
	hdr->ds_commit_idx = idx;
	fh = nfs4_fl_select_ds_fh(lseg, j);
	अगर (fh)
		hdr->args.fh = fh;

	hdr->args.offset = filelayout_get_dserver_offset(lseg, offset);
	hdr->mds_offset = offset;

	/* Perक्रमm an asynchronous पढ़ो to ds */
	nfs_initiate_pgio(ds_clnt, hdr, hdr->cred,
			  NFS_PROTO(hdr->inode), &filelayout_पढ़ो_call_ops,
			  0, RPC_TASK_SOFTCONN);
	वापस PNFS_ATTEMPTED;
पूर्ण

/* Perक्रमm async ग_लिखोs. */
अटल क्रमागत pnfs_try_status
filelayout_ग_लिखो_pagelist(काष्ठा nfs_pgio_header *hdr, पूर्णांक sync)
अणु
	काष्ठा pnfs_layout_segment *lseg = hdr->lseg;
	काष्ठा nfs4_pnfs_ds *ds;
	काष्ठा rpc_clnt *ds_clnt;
	loff_t offset = hdr->args.offset;
	u32 j, idx;
	काष्ठा nfs_fh *fh;

	/* Retrieve the correct rpc_client क्रम the byte range */
	j = nfs4_fl_calc_j_index(lseg, offset);
	idx = nfs4_fl_calc_ds_index(lseg, j);
	ds = nfs4_fl_prepare_ds(lseg, idx);
	अगर (!ds)
		वापस PNFS_NOT_ATTEMPTED;

	ds_clnt = nfs4_find_or_create_ds_client(ds->ds_clp, hdr->inode);
	अगर (IS_ERR(ds_clnt))
		वापस PNFS_NOT_ATTEMPTED;

	dprपूर्णांकk("%s ino %lu sync %d req %zu@%llu DS: %s cl_count %d\n",
		__func__, hdr->inode->i_ino, sync, (माप_प्रकार) hdr->args.count,
		offset, ds->ds_remotestr, refcount_पढ़ो(&ds->ds_clp->cl_count));

	hdr->pgio_करोne_cb = filelayout_ग_लिखो_करोne_cb;
	refcount_inc(&ds->ds_clp->cl_count);
	hdr->ds_clp = ds->ds_clp;
	hdr->ds_commit_idx = idx;
	fh = nfs4_fl_select_ds_fh(lseg, j);
	अगर (fh)
		hdr->args.fh = fh;
	hdr->args.offset = filelayout_get_dserver_offset(lseg, offset);

	/* Perक्रमm an asynchronous ग_लिखो */
	nfs_initiate_pgio(ds_clnt, hdr, hdr->cred,
			  NFS_PROTO(hdr->inode), &filelayout_ग_लिखो_call_ops,
			  sync, RPC_TASK_SOFTCONN);
	वापस PNFS_ATTEMPTED;
पूर्ण

अटल पूर्णांक
filelayout_check_deviceid(काष्ठा pnfs_layout_hdr *lo,
			  काष्ठा nfs4_filelayout_segment *fl,
			  gfp_t gfp_flags)
अणु
	काष्ठा nfs4_deviceid_node *d;
	काष्ठा nfs4_file_layout_dsaddr *dsaddr;
	पूर्णांक status = -EINVAL;

	/* Is the deviceid alपढ़ोy set? If so, we're good. */
	अगर (fl->dsaddr != शून्य)
		वापस 0;

	/* find and reference the deviceid */
	d = nfs4_find_get_deviceid(NFS_SERVER(lo->plh_inode), &fl->deviceid,
			lo->plh_lc_cred, gfp_flags);
	अगर (d == शून्य)
		जाओ out;

	dsaddr = container_of(d, काष्ठा nfs4_file_layout_dsaddr, id_node);
	/* Found deviceid is unavailable */
	अगर (filelayout_test_devid_unavailable(&dsaddr->id_node))
		जाओ out_put;

	अगर (fl->first_stripe_index >= dsaddr->stripe_count) अणु
		dprपूर्णांकk("%s Bad first_stripe_index %u\n",
				__func__, fl->first_stripe_index);
		जाओ out_put;
	पूर्ण

	अगर ((fl->stripe_type == STRIPE_SPARSE &&
	    fl->num_fh > 1 && fl->num_fh != dsaddr->ds_num) ||
	    (fl->stripe_type == STRIPE_DENSE &&
	    fl->num_fh != dsaddr->stripe_count)) अणु
		dprपूर्णांकk("%s num_fh %u not valid for given packing\n",
			__func__, fl->num_fh);
		जाओ out_put;
	पूर्ण
	status = 0;

	/*
	 * Atomic compare and xchange to ensure we करोn't scribble
	 * over a non-शून्य poपूर्णांकer.
	 */
	अगर (cmpxchg(&fl->dsaddr, शून्य, dsaddr) != शून्य)
		जाओ out_put;
out:
	वापस status;
out_put:
	nfs4_fl_put_deviceid(dsaddr);
	जाओ out;
पूर्ण

/*
 * filelayout_check_layout()
 *
 * Make sure layout segment parameters are sane WRT the device.
 * At this poपूर्णांक no generic layer initialization of the lseg has occurred,
 * and nothing has been added to the layout_hdr cache.
 *
 */
अटल पूर्णांक
filelayout_check_layout(काष्ठा pnfs_layout_hdr *lo,
			काष्ठा nfs4_filelayout_segment *fl,
			काष्ठा nfs4_layoutget_res *lgr,
			gfp_t gfp_flags)
अणु
	पूर्णांक status = -EINVAL;

	dprपूर्णांकk("--> %s\n", __func__);

	/* FIXME: हटाओ this check when layout segment support is added */
	अगर (lgr->range.offset != 0 ||
	    lgr->range.length != NFS4_MAX_UINT64) अणु
		dprपूर्णांकk("%s Only whole file layouts supported. Use MDS i/o\n",
			__func__);
		जाओ out;
	पूर्ण

	अगर (fl->pattern_offset > lgr->range.offset) अणु
		dprपूर्णांकk("%s pattern_offset %lld too large\n",
				__func__, fl->pattern_offset);
		जाओ out;
	पूर्ण

	अगर (!fl->stripe_unit) अणु
		dprपूर्णांकk("%s Invalid stripe unit (%u)\n",
			__func__, fl->stripe_unit);
		जाओ out;
	पूर्ण

	status = 0;
out:
	dprपूर्णांकk("--> %s returns %d\n", __func__, status);
	वापस status;
पूर्ण

अटल व्योम _filelayout_मुक्त_lseg(काष्ठा nfs4_filelayout_segment *fl)
अणु
	पूर्णांक i;

	अगर (fl->fh_array) अणु
		क्रम (i = 0; i < fl->num_fh; i++) अणु
			अगर (!fl->fh_array[i])
				अवरोध;
			kमुक्त(fl->fh_array[i]);
		पूर्ण
		kमुक्त(fl->fh_array);
	पूर्ण
	kमुक्त(fl);
पूर्ण

अटल पूर्णांक
filelayout_decode_layout(काष्ठा pnfs_layout_hdr *flo,
			 काष्ठा nfs4_filelayout_segment *fl,
			 काष्ठा nfs4_layoutget_res *lgr,
			 gfp_t gfp_flags)
अणु
	काष्ठा xdr_stream stream;
	काष्ठा xdr_buf buf;
	काष्ठा page *scratch;
	__be32 *p;
	uपूर्णांक32_t nfl_util;
	पूर्णांक i;

	dprपूर्णांकk("%s: set_layout_map Begin\n", __func__);

	scratch = alloc_page(gfp_flags);
	अगर (!scratch)
		वापस -ENOMEM;

	xdr_init_decode_pages(&stream, &buf, lgr->layoutp->pages, lgr->layoutp->len);
	xdr_set_scratch_page(&stream, scratch);

	/* 20 = ufl_util (4), first_stripe_index (4), pattern_offset (8),
	 * num_fh (4) */
	p = xdr_अंतरभूत_decode(&stream, NFS4_DEVICEID4_SIZE + 20);
	अगर (unlikely(!p))
		जाओ out_err;

	स_नकल(&fl->deviceid, p, माप(fl->deviceid));
	p += XDR_QUADLEN(NFS4_DEVICEID4_SIZE);
	nfs4_prपूर्णांक_deviceid(&fl->deviceid);

	nfl_util = be32_to_cpup(p++);
	अगर (nfl_util & NFL4_UFLG_COMMIT_THRU_MDS)
		fl->commit_through_mds = 1;
	अगर (nfl_util & NFL4_UFLG_DENSE)
		fl->stripe_type = STRIPE_DENSE;
	अन्यथा
		fl->stripe_type = STRIPE_SPARSE;
	fl->stripe_unit = nfl_util & ~NFL4_UFLG_MASK;

	fl->first_stripe_index = be32_to_cpup(p++);
	p = xdr_decode_hyper(p, &fl->pattern_offset);
	fl->num_fh = be32_to_cpup(p++);

	dprपूर्णांकk("%s: nfl_util 0x%X num_fh %u fsi %u po %llu\n",
		__func__, nfl_util, fl->num_fh, fl->first_stripe_index,
		fl->pattern_offset);

	/* Note that a zero value क्रम num_fh is legal क्रम STRIPE_SPARSE.
	 * Futher checking is करोne in filelayout_check_layout */
	अगर (fl->num_fh >
	    max(NFS4_PNFS_MAX_STRIPE_CNT, NFS4_PNFS_MAX_MULTI_CNT))
		जाओ out_err;

	अगर (fl->num_fh > 0) अणु
		fl->fh_array = kसुस्मृति(fl->num_fh, माप(fl->fh_array[0]),
				       gfp_flags);
		अगर (!fl->fh_array)
			जाओ out_err;
	पूर्ण

	क्रम (i = 0; i < fl->num_fh; i++) अणु
		/* Do we want to use a mempool here? */
		fl->fh_array[i] = kदो_स्मृति(माप(काष्ठा nfs_fh), gfp_flags);
		अगर (!fl->fh_array[i])
			जाओ out_err;

		p = xdr_अंतरभूत_decode(&stream, 4);
		अगर (unlikely(!p))
			जाओ out_err;
		fl->fh_array[i]->size = be32_to_cpup(p++);
		अगर (fl->fh_array[i]->size > NFS_MAXFHSIZE) अणु
			prपूर्णांकk(KERN_ERR "NFS: Too big fh %d received %d\n",
			       i, fl->fh_array[i]->size);
			जाओ out_err;
		पूर्ण

		p = xdr_अंतरभूत_decode(&stream, fl->fh_array[i]->size);
		अगर (unlikely(!p))
			जाओ out_err;
		स_नकल(fl->fh_array[i]->data, p, fl->fh_array[i]->size);
		dprपूर्णांकk("DEBUG: %s: fh len %d\n", __func__,
			fl->fh_array[i]->size);
	पूर्ण

	__मुक्त_page(scratch);
	वापस 0;

out_err:
	__मुक्त_page(scratch);
	वापस -EIO;
पूर्ण

अटल व्योम
filelayout_मुक्त_lseg(काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा nfs4_filelayout_segment *fl = खाताLAYOUT_LSEG(lseg);

	dprपूर्णांकk("--> %s\n", __func__);
	अगर (fl->dsaddr != शून्य)
		nfs4_fl_put_deviceid(fl->dsaddr);
	/* This assumes a single RW lseg */
	अगर (lseg->pls_range.iomode == IOMODE_RW) अणु
		काष्ठा nfs4_filelayout *flo;
		काष्ठा inode *inode;

		flo = खाताLAYOUT_FROM_HDR(lseg->pls_layout);
		inode = flo->generic_hdr.plh_inode;
		spin_lock(&inode->i_lock);
		pnfs_generic_ds_cinfo_release_lseg(&flo->commit_info, lseg);
		spin_unlock(&inode->i_lock);
	पूर्ण
	_filelayout_मुक्त_lseg(fl);
पूर्ण

अटल काष्ठा pnfs_layout_segment *
filelayout_alloc_lseg(काष्ठा pnfs_layout_hdr *layoutid,
		      काष्ठा nfs4_layoutget_res *lgr,
		      gfp_t gfp_flags)
अणु
	काष्ठा nfs4_filelayout_segment *fl;
	पूर्णांक rc;

	dprपूर्णांकk("--> %s\n", __func__);
	fl = kzalloc(माप(*fl), gfp_flags);
	अगर (!fl)
		वापस शून्य;

	rc = filelayout_decode_layout(layoutid, fl, lgr, gfp_flags);
	अगर (rc != 0 || filelayout_check_layout(layoutid, fl, lgr, gfp_flags)) अणु
		_filelayout_मुक्त_lseg(fl);
		वापस शून्य;
	पूर्ण
	वापस &fl->generic_hdr;
पूर्ण

/*
 * filelayout_pg_test(). Called by nfs_can_coalesce_requests()
 *
 * Return 0 अगर @req cannot be coalesced पूर्णांकo @pgio, otherwise वापस the number
 * of bytes (maximum @req->wb_bytes) that can be coalesced.
 */
अटल माप_प्रकार
filelayout_pg_test(काष्ठा nfs_pageio_descriptor *pgio, काष्ठा nfs_page *prev,
		   काष्ठा nfs_page *req)
अणु
	अचिन्हित पूर्णांक size;
	u64 p_stripe, r_stripe;
	u32 stripe_offset;
	u64 segment_offset = pgio->pg_lseg->pls_range.offset;
	u32 stripe_unit = खाताLAYOUT_LSEG(pgio->pg_lseg)->stripe_unit;

	/* calls nfs_generic_pg_test */
	size = pnfs_generic_pg_test(pgio, prev, req);
	अगर (!size)
		वापस 0;

	/* see अगर req and prev are in the same stripe */
	अगर (prev) अणु
		p_stripe = (u64)req_offset(prev) - segment_offset;
		r_stripe = (u64)req_offset(req) - segment_offset;
		करो_भाग(p_stripe, stripe_unit);
		करो_भाग(r_stripe, stripe_unit);

		अगर (p_stripe != r_stripe)
			वापस 0;
	पूर्ण

	/* calculate reमुख्यing bytes in the current stripe */
	भाग_u64_rem((u64)req_offset(req) - segment_offset,
			stripe_unit,
			&stripe_offset);
	WARN_ON_ONCE(stripe_offset > stripe_unit);
	अगर (stripe_offset >= stripe_unit)
		वापस 0;
	वापस min(stripe_unit - (अचिन्हित पूर्णांक)stripe_offset, size);
पूर्ण

अटल काष्ठा pnfs_layout_segment *
fl_pnfs_update_layout(काष्ठा inode *ino,
		      काष्ठा nfs_खोलो_context *ctx,
		      loff_t pos,
		      u64 count,
		      क्रमागत pnfs_iomode iomode,
		      bool strict_iomode,
		      gfp_t gfp_flags)
अणु
	काष्ठा pnfs_layout_segment *lseg = शून्य;
	काष्ठा pnfs_layout_hdr *lo;
	काष्ठा nfs4_filelayout_segment *fl;
	पूर्णांक status;

	lseg = pnfs_update_layout(ino, ctx, pos, count, iomode, strict_iomode,
				  gfp_flags);
	अगर (IS_ERR_OR_शून्य(lseg))
		जाओ out;

	lo = NFS_I(ino)->layout;
	fl = खाताLAYOUT_LSEG(lseg);

	status = filelayout_check_deviceid(lo, fl, gfp_flags);
	अगर (status) अणु
		pnfs_put_lseg(lseg);
		lseg = शून्य;
	पूर्ण
out:
	वापस lseg;
पूर्ण

अटल व्योम
filelayout_pg_init_पढ़ो(काष्ठा nfs_pageio_descriptor *pgio,
			काष्ठा nfs_page *req)
अणु
	pnfs_generic_pg_check_layout(pgio);
	अगर (!pgio->pg_lseg) अणु
		pgio->pg_lseg = fl_pnfs_update_layout(pgio->pg_inode,
						      nfs_req_खोलोctx(req),
						      0,
						      NFS4_MAX_UINT64,
						      IOMODE_READ,
						      false,
						      GFP_KERNEL);
		अगर (IS_ERR(pgio->pg_lseg)) अणु
			pgio->pg_error = PTR_ERR(pgio->pg_lseg);
			pgio->pg_lseg = शून्य;
			वापस;
		पूर्ण
	पूर्ण
	/* If no lseg, fall back to पढ़ो through mds */
	अगर (pgio->pg_lseg == शून्य)
		nfs_pageio_reset_पढ़ो_mds(pgio);
पूर्ण

अटल व्योम
filelayout_pg_init_ग_लिखो(काष्ठा nfs_pageio_descriptor *pgio,
			 काष्ठा nfs_page *req)
अणु
	pnfs_generic_pg_check_layout(pgio);
	अगर (!pgio->pg_lseg) अणु
		pgio->pg_lseg = fl_pnfs_update_layout(pgio->pg_inode,
						      nfs_req_खोलोctx(req),
						      0,
						      NFS4_MAX_UINT64,
						      IOMODE_RW,
						      false,
						      GFP_NOFS);
		अगर (IS_ERR(pgio->pg_lseg)) अणु
			pgio->pg_error = PTR_ERR(pgio->pg_lseg);
			pgio->pg_lseg = शून्य;
			वापस;
		पूर्ण
	पूर्ण

	/* If no lseg, fall back to ग_लिखो through mds */
	अगर (pgio->pg_lseg == शून्य)
		nfs_pageio_reset_ग_लिखो_mds(pgio);
पूर्ण

अटल स्थिर काष्ठा nfs_pageio_ops filelayout_pg_पढ़ो_ops = अणु
	.pg_init = filelayout_pg_init_पढ़ो,
	.pg_test = filelayout_pg_test,
	.pg_करोio = pnfs_generic_pg_पढ़ोpages,
	.pg_cleanup = pnfs_generic_pg_cleanup,
पूर्ण;

अटल स्थिर काष्ठा nfs_pageio_ops filelayout_pg_ग_लिखो_ops = अणु
	.pg_init = filelayout_pg_init_ग_लिखो,
	.pg_test = filelayout_pg_test,
	.pg_करोio = pnfs_generic_pg_ग_लिखोpages,
	.pg_cleanup = pnfs_generic_pg_cleanup,
पूर्ण;

अटल u32 select_bucket_index(काष्ठा nfs4_filelayout_segment *fl, u32 j)
अणु
	अगर (fl->stripe_type == STRIPE_SPARSE)
		वापस nfs4_fl_calc_ds_index(&fl->generic_hdr, j);
	अन्यथा
		वापस j;
पूर्ण

अटल व्योम
filelayout_mark_request_commit(काष्ठा nfs_page *req,
			       काष्ठा pnfs_layout_segment *lseg,
			       काष्ठा nfs_commit_info *cinfo,
			       u32 ds_commit_idx)

अणु
	काष्ठा nfs4_filelayout_segment *fl = खाताLAYOUT_LSEG(lseg);
	u32 i, j;

	अगर (fl->commit_through_mds) अणु
		nfs_request_add_commit_list(req, cinfo);
	पूर्ण अन्यथा अणु
		/* Note that we are calling nfs4_fl_calc_j_index on each page
		 * that ends up being committed to a data server.  An attractive
		 * alternative is to add a field to nfs_ग_लिखो_data and nfs_page
		 * to store the value calculated in filelayout_ग_लिखो_pagelist
		 * and just use that here.
		 */
		j = nfs4_fl_calc_j_index(lseg, req_offset(req));
		i = select_bucket_index(fl, j);
		pnfs_layout_mark_request_commit(req, lseg, cinfo, i);
	पूर्ण
पूर्ण

अटल u32 calc_ds_index_from_commit(काष्ठा pnfs_layout_segment *lseg, u32 i)
अणु
	काष्ठा nfs4_filelayout_segment *flseg = खाताLAYOUT_LSEG(lseg);

	अगर (flseg->stripe_type == STRIPE_SPARSE)
		वापस i;
	अन्यथा
		वापस nfs4_fl_calc_ds_index(lseg, i);
पूर्ण

अटल काष्ठा nfs_fh *
select_ds_fh_from_commit(काष्ठा pnfs_layout_segment *lseg, u32 i)
अणु
	काष्ठा nfs4_filelayout_segment *flseg = खाताLAYOUT_LSEG(lseg);

	अगर (flseg->stripe_type == STRIPE_SPARSE) अणु
		अगर (flseg->num_fh == 1)
			i = 0;
		अन्यथा अगर (flseg->num_fh == 0)
			/* Use the MDS OPEN fh set in nfs_पढ़ो_rpcsetup */
			वापस शून्य;
	पूर्ण
	वापस flseg->fh_array[i];
पूर्ण

अटल पूर्णांक filelayout_initiate_commit(काष्ठा nfs_commit_data *data, पूर्णांक how)
अणु
	काष्ठा pnfs_layout_segment *lseg = data->lseg;
	काष्ठा nfs4_pnfs_ds *ds;
	काष्ठा rpc_clnt *ds_clnt;
	u32 idx;
	काष्ठा nfs_fh *fh;

	idx = calc_ds_index_from_commit(lseg, data->ds_commit_index);
	ds = nfs4_fl_prepare_ds(lseg, idx);
	अगर (!ds)
		जाओ out_err;

	ds_clnt = nfs4_find_or_create_ds_client(ds->ds_clp, data->inode);
	अगर (IS_ERR(ds_clnt))
		जाओ out_err;

	dprपूर्णांकk("%s ino %lu, how %d cl_count %d\n", __func__,
		data->inode->i_ino, how, refcount_पढ़ो(&ds->ds_clp->cl_count));
	data->commit_करोne_cb = filelayout_commit_करोne_cb;
	refcount_inc(&ds->ds_clp->cl_count);
	data->ds_clp = ds->ds_clp;
	fh = select_ds_fh_from_commit(lseg, data->ds_commit_index);
	अगर (fh)
		data->args.fh = fh;
	वापस nfs_initiate_commit(ds_clnt, data, NFS_PROTO(data->inode),
				   &filelayout_commit_call_ops, how,
				   RPC_TASK_SOFTCONN);
out_err:
	pnfs_generic_prepare_to_resend_ग_लिखोs(data);
	pnfs_generic_commit_release(data);
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक
filelayout_commit_pagelist(काष्ठा inode *inode, काष्ठा list_head *mds_pages,
			   पूर्णांक how, काष्ठा nfs_commit_info *cinfo)
अणु
	वापस pnfs_generic_commit_pagelist(inode, mds_pages, how, cinfo,
					    filelayout_initiate_commit);
पूर्ण

अटल काष्ठा nfs4_deviceid_node *
filelayout_alloc_deviceid_node(काष्ठा nfs_server *server,
		काष्ठा pnfs_device *pdev, gfp_t gfp_flags)
अणु
	काष्ठा nfs4_file_layout_dsaddr *dsaddr;

	dsaddr = nfs4_fl_alloc_deviceid_node(server, pdev, gfp_flags);
	अगर (!dsaddr)
		वापस शून्य;
	वापस &dsaddr->id_node;
पूर्ण

अटल व्योम
filelayout_मुक्त_deviceid_node(काष्ठा nfs4_deviceid_node *d)
अणु
	nfs4_fl_मुक्त_deviceid(container_of(d, काष्ठा nfs4_file_layout_dsaddr, id_node));
पूर्ण

अटल काष्ठा pnfs_layout_hdr *
filelayout_alloc_layout_hdr(काष्ठा inode *inode, gfp_t gfp_flags)
अणु
	काष्ठा nfs4_filelayout *flo;

	flo = kzalloc(माप(*flo), gfp_flags);
	अगर (flo == शून्य)
		वापस शून्य;
	pnfs_init_ds_commit_info(&flo->commit_info);
	flo->commit_info.ops = &filelayout_commit_ops;
	वापस &flo->generic_hdr;
पूर्ण

अटल व्योम
filelayout_मुक्त_layout_hdr(काष्ठा pnfs_layout_hdr *lo)
अणु
	kमुक्त_rcu(खाताLAYOUT_FROM_HDR(lo), generic_hdr.plh_rcu);
पूर्ण

अटल काष्ठा pnfs_ds_commit_info *
filelayout_get_ds_info(काष्ठा inode *inode)
अणु
	काष्ठा pnfs_layout_hdr *layout = NFS_I(inode)->layout;

	अगर (layout == शून्य)
		वापस शून्य;
	अन्यथा
		वापस &खाताLAYOUT_FROM_HDR(layout)->commit_info;
पूर्ण

अटल व्योम
filelayout_setup_ds_info(काष्ठा pnfs_ds_commit_info *fl_cinfo,
		काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा nfs4_filelayout_segment *fl = खाताLAYOUT_LSEG(lseg);
	काष्ठा inode *inode = lseg->pls_layout->plh_inode;
	काष्ठा pnfs_commit_array *array, *new;
	अचिन्हित पूर्णांक size = (fl->stripe_type == STRIPE_SPARSE) ?
		fl->dsaddr->ds_num : fl->dsaddr->stripe_count;

	new = pnfs_alloc_commit_array(size, GFP_NOIO);
	अगर (new) अणु
		spin_lock(&inode->i_lock);
		array = pnfs_add_commit_array(fl_cinfo, new, lseg);
		spin_unlock(&inode->i_lock);
		अगर (array != new)
			pnfs_मुक्त_commit_array(new);
	पूर्ण
पूर्ण

अटल व्योम
filelayout_release_ds_info(काष्ठा pnfs_ds_commit_info *fl_cinfo,
		काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	pnfs_generic_ds_cinfo_destroy(fl_cinfo);
	spin_unlock(&inode->i_lock);
पूर्ण

अटल स्थिर काष्ठा pnfs_commit_ops filelayout_commit_ops = अणु
	.setup_ds_info		= filelayout_setup_ds_info,
	.release_ds_info	= filelayout_release_ds_info,
	.mark_request_commit	= filelayout_mark_request_commit,
	.clear_request_commit	= pnfs_generic_clear_request_commit,
	.scan_commit_lists	= pnfs_generic_scan_commit_lists,
	.recover_commit_reqs	= pnfs_generic_recover_commit_reqs,
	.search_commit_reqs	= pnfs_generic_search_commit_reqs,
	.commit_pagelist	= filelayout_commit_pagelist,
पूर्ण;

अटल काष्ठा pnfs_layoutdriver_type filelayout_type = अणु
	.id			= LAYOUT_NFSV4_1_खाताS,
	.name			= "LAYOUT_NFSV4_1_FILES",
	.owner			= THIS_MODULE,
	.flags			= PNFS_LAYOUTGET_ON_OPEN,
	.max_layoutget_response	= 4096, /* 1 page or so... */
	.alloc_layout_hdr	= filelayout_alloc_layout_hdr,
	.मुक्त_layout_hdr	= filelayout_मुक्त_layout_hdr,
	.alloc_lseg		= filelayout_alloc_lseg,
	.मुक्त_lseg		= filelayout_मुक्त_lseg,
	.pg_पढ़ो_ops		= &filelayout_pg_पढ़ो_ops,
	.pg_ग_लिखो_ops		= &filelayout_pg_ग_लिखो_ops,
	.get_ds_info		= &filelayout_get_ds_info,
	.पढ़ो_pagelist		= filelayout_पढ़ो_pagelist,
	.ग_लिखो_pagelist		= filelayout_ग_लिखो_pagelist,
	.alloc_deviceid_node	= filelayout_alloc_deviceid_node,
	.मुक्त_deviceid_node	= filelayout_मुक्त_deviceid_node,
	.sync			= pnfs_nfs_generic_sync,
पूर्ण;

अटल पूर्णांक __init nfs4filelayout_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "%s: NFSv4 File Layout Driver Registering...\n",
	       __func__);
	वापस pnfs_रेजिस्टर_layoutdriver(&filelayout_type);
पूर्ण

अटल व्योम __निकास nfs4filelayout_निकास(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "%s: NFSv4 File Layout Driver Unregistering...\n",
	       __func__);
	pnfs_unरेजिस्टर_layoutdriver(&filelayout_type);
पूर्ण

MODULE_ALIAS("nfs-layouttype4-1");

module_init(nfs4filelayout_init);
module_निकास(nfs4filelayout_निकास);
