<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  QLogic FCoE Offload Driver
 *  Copyright (c) 2016-2018 QLogic Corporation
 */
#अगर_घोषित CONFIG_DEBUG_FS

#समावेश <linux/uaccess.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>

#समावेश "qedf.h"
#समावेश "qedf_dbg.h"

अटल काष्ठा dentry *qedf_dbg_root;

/*
 * qedf_dbg_host_init - setup the debugfs file क्रम the pf
 */
व्योम
qedf_dbg_host_init(काष्ठा qedf_dbg_ctx *qedf,
		    स्थिर काष्ठा qedf_debugfs_ops *करोps,
		    स्थिर काष्ठा file_operations *fops)
अणु
	अक्षर host_स_नाम[32];

	QEDF_INFO(qedf, QEDF_LOG_DEBUGFS, "Creating debugfs host node\n");
	/* create pf dir */
	प्र_लिखो(host_स_नाम, "host%u", qedf->host_no);
	qedf->bdf_dentry = debugfs_create_dir(host_स_नाम, qedf_dbg_root);

	/* create debugfs files */
	जबतक (करोps) अणु
		अगर (!(करोps->name))
			अवरोध;

		debugfs_create_file(करोps->name, 0600, qedf->bdf_dentry, qedf,
				    fops);
		करोps++;
		fops++;
	पूर्ण
पूर्ण

/*
 * qedf_dbg_host_निकास - clear out the pf's debugfs entries
 */
व्योम
qedf_dbg_host_निकास(काष्ठा qedf_dbg_ctx *qedf_dbg)
अणु
	QEDF_INFO(qedf_dbg, QEDF_LOG_DEBUGFS, "Destroying debugfs host "
		   "entry\n");
	/* हटाओ debugfs  entries of this PF */
	debugfs_हटाओ_recursive(qedf_dbg->bdf_dentry);
	qedf_dbg->bdf_dentry = शून्य;
पूर्ण

/*
 * qedf_dbg_init - start up debugfs क्रम the driver
 */
व्योम
qedf_dbg_init(अक्षर *drv_name)
अणु
	QEDF_INFO(शून्य, QEDF_LOG_DEBUGFS, "Creating debugfs root node\n");

	/* create qed dir in root of debugfs. शून्य means debugfs root */
	qedf_dbg_root = debugfs_create_dir(drv_name, शून्य);
पूर्ण

/*
 * qedf_dbg_निकास - clean out the driver's debugfs entries
 */
व्योम
qedf_dbg_निकास(व्योम)
अणु
	QEDF_INFO(शून्य, QEDF_LOG_DEBUGFS, "Destroying debugfs root "
		   "entry\n");

	/* हटाओ qed dir in root of debugfs */
	debugfs_हटाओ_recursive(qedf_dbg_root);
	qedf_dbg_root = शून्य;
पूर्ण

स्थिर काष्ठा qedf_debugfs_ops qedf_debugfs_ops[] = अणु
	अणु "fp_int", शून्य पूर्ण,
	अणु "io_trace", शून्य पूर्ण,
	अणु "debug", शून्य पूर्ण,
	अणु "stop_io_on_error", शून्यपूर्ण,
	अणु "driver_stats", शून्यपूर्ण,
	अणु "clear_stats", शून्यपूर्ण,
	अणु "offload_stats", शून्यपूर्ण,
	/* This must be last */
	अणु शून्य, शून्य पूर्ण
पूर्ण;

DECLARE_PER_CPU(काष्ठा qedf_percpu_iothपढ़ो_s, qedf_percpu_iothपढ़ोs);

अटल sमाप_प्रकार
qedf_dbg_fp_पूर्णांक_cmd_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer, माप_प्रकार count,
			 loff_t *ppos)
अणु
	माप_प्रकार cnt = 0;
	पूर्णांक id;
	काष्ठा qedf_fastpath *fp = शून्य;
	काष्ठा qedf_dbg_ctx *qedf_dbg =
				(काष्ठा qedf_dbg_ctx *)filp->निजी_data;
	काष्ठा qedf_ctx *qedf = container_of(qedf_dbg,
	    काष्ठा qedf_ctx, dbg_ctx);

	QEDF_INFO(qedf_dbg, QEDF_LOG_DEBUGFS, "entered\n");

	cnt = प्र_लिखो(buffer, "\nFastpath I/O completions\n\n");

	क्रम (id = 0; id < qedf->num_queues; id++) अणु
		fp = &(qedf->fp_array[id]);
		अगर (fp->sb_id == QEDF_SB_ID_शून्य)
			जारी;
		cnt += प्र_लिखो((buffer + cnt), "#%d: %lu\n", id,
			       fp->completions);
	पूर्ण

	cnt = min_t(पूर्णांक, count, cnt - *ppos);
	*ppos += cnt;
	वापस cnt;
पूर्ण

अटल sमाप_प्रकार
qedf_dbg_fp_पूर्णांक_cmd_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
			  माप_प्रकार count, loff_t *ppos)
अणु
	अगर (!count || *ppos)
		वापस 0;

	वापस count;
पूर्ण

अटल sमाप_प्रकार
qedf_dbg_debug_cmd_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer, माप_प्रकार count,
			loff_t *ppos)
अणु
	पूर्णांक cnt;
	काष्ठा qedf_dbg_ctx *qedf_dbg =
				(काष्ठा qedf_dbg_ctx *)filp->निजी_data;

	QEDF_INFO(qedf_dbg, QEDF_LOG_DEBUGFS, "debug mask=0x%x\n", qedf_debug);
	cnt = प्र_लिखो(buffer, "debug mask = 0x%x\n", qedf_debug);

	cnt = min_t(पूर्णांक, count, cnt - *ppos);
	*ppos += cnt;
	वापस cnt;
पूर्ण

अटल sमाप_प्रकार
qedf_dbg_debug_cmd_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
			 माप_प्रकार count, loff_t *ppos)
अणु
	uपूर्णांक32_t val;
	व्योम *kern_buf;
	पूर्णांक rval;
	काष्ठा qedf_dbg_ctx *qedf_dbg =
	    (काष्ठा qedf_dbg_ctx *)filp->निजी_data;

	अगर (!count || *ppos)
		वापस 0;

	kern_buf = memdup_user(buffer, count);
	अगर (IS_ERR(kern_buf))
		वापस PTR_ERR(kern_buf);

	rval = kstrtouपूर्णांक(kern_buf, 10, &val);
	kमुक्त(kern_buf);
	अगर (rval)
		वापस rval;

	अगर (val == 1)
		qedf_debug = QEDF_DEFAULT_LOG_MASK;
	अन्यथा
		qedf_debug = val;

	QEDF_INFO(qedf_dbg, QEDF_LOG_DEBUGFS, "Setting debug=0x%x.\n", val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
qedf_dbg_stop_io_on_error_cmd_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				   माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक cnt;
	काष्ठा qedf_dbg_ctx *qedf_dbg =
				(काष्ठा qedf_dbg_ctx *)filp->निजी_data;
	काष्ठा qedf_ctx *qedf = container_of(qedf_dbg,
	    काष्ठा qedf_ctx, dbg_ctx);

	QEDF_INFO(qedf_dbg, QEDF_LOG_DEBUGFS, "entered\n");
	cnt = प्र_लिखो(buffer, "%s\n",
	    qedf->stop_io_on_error ? "true" : "false");

	cnt = min_t(पूर्णांक, count, cnt - *ppos);
	*ppos += cnt;
	वापस cnt;
पूर्ण

अटल sमाप_प्रकार
qedf_dbg_stop_io_on_error_cmd_ग_लिखो(काष्ठा file *filp,
				    स्थिर अक्षर __user *buffer, माप_प्रकार count,
				    loff_t *ppos)
अणु
	व्योम *kern_buf;
	काष्ठा qedf_dbg_ctx *qedf_dbg =
				(काष्ठा qedf_dbg_ctx *)filp->निजी_data;
	काष्ठा qedf_ctx *qedf = container_of(qedf_dbg, काष्ठा qedf_ctx,
	    dbg_ctx);

	QEDF_INFO(qedf_dbg, QEDF_LOG_DEBUGFS, "entered\n");

	अगर (!count || *ppos)
		वापस 0;

	kern_buf = memdup_user(buffer, 6);
	अगर (IS_ERR(kern_buf))
		वापस PTR_ERR(kern_buf);

	अगर (म_भेदन(kern_buf, "false", 5) == 0)
		qedf->stop_io_on_error = false;
	अन्यथा अगर (म_भेदन(kern_buf, "true", 4) == 0)
		qedf->stop_io_on_error = true;
	अन्यथा अगर (म_भेदन(kern_buf, "now", 3) == 0)
		/* Trigger from user to stop all I/O on this host */
		set_bit(QEDF_DBG_STOP_IO, &qedf->flags);

	kमुक्त(kern_buf);
	वापस count;
पूर्ण

अटल पूर्णांक
qedf_io_trace_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	पूर्णांक i, idx = 0;
	काष्ठा qedf_ctx *qedf = s->निजी;
	काष्ठा qedf_dbg_ctx *qedf_dbg = &qedf->dbg_ctx;
	काष्ठा qedf_io_log *io_log;
	अचिन्हित दीर्घ flags;

	अगर (!qedf_io_tracing) अणु
		seq_माला_दो(s, "I/O tracing not enabled.\n");
		जाओ out;
	पूर्ण

	QEDF_INFO(qedf_dbg, QEDF_LOG_DEBUGFS, "entered\n");

	spin_lock_irqsave(&qedf->io_trace_lock, flags);
	idx = qedf->io_trace_idx;
	क्रम (i = 0; i < QEDF_IO_TRACE_SIZE; i++) अणु
		io_log = &qedf->io_trace_buf[idx];
		seq_म_लिखो(s, "%d:", io_log->direction);
		seq_म_लिखो(s, "0x%x:", io_log->task_id);
		seq_म_लिखो(s, "0x%06x:", io_log->port_id);
		seq_म_लिखो(s, "%d:", io_log->lun);
		seq_म_लिखो(s, "0x%02x:", io_log->op);
		seq_म_लिखो(s, "0x%02x%02x%02x%02x:", io_log->lba[0],
		    io_log->lba[1], io_log->lba[2], io_log->lba[3]);
		seq_म_लिखो(s, "%d:", io_log->bufflen);
		seq_म_लिखो(s, "%d:", io_log->sg_count);
		seq_म_लिखो(s, "0x%08x:", io_log->result);
		seq_म_लिखो(s, "%lu:", io_log->jअगरfies);
		seq_म_लिखो(s, "%d:", io_log->refcount);
		seq_म_लिखो(s, "%d:", io_log->req_cpu);
		seq_म_लिखो(s, "%d:", io_log->पूर्णांक_cpu);
		seq_म_लिखो(s, "%d:", io_log->rsp_cpu);
		seq_म_लिखो(s, "%d\n", io_log->sge_type);

		idx++;
		अगर (idx == QEDF_IO_TRACE_SIZE)
			idx = 0;
	पूर्ण
	spin_unlock_irqrestore(&qedf->io_trace_lock, flags);

out:
	वापस 0;
पूर्ण

अटल पूर्णांक
qedf_dbg_io_trace_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा qedf_dbg_ctx *qedf_dbg = inode->i_निजी;
	काष्ठा qedf_ctx *qedf = container_of(qedf_dbg,
	    काष्ठा qedf_ctx, dbg_ctx);

	वापस single_खोलो(file, qedf_io_trace_show, qedf);
पूर्ण

/* Based on fip_state क्रमागत from libfcoe.h */
अटल अक्षर *fip_state_names[] = अणु
	"FIP_ST_DISABLED",
	"FIP_ST_LINK_WAIT",
	"FIP_ST_AUTO",
	"FIP_ST_NON_FIP",
	"FIP_ST_ENABLED",
	"FIP_ST_VNMP_START",
	"FIP_ST_VNMP_PROBE1",
	"FIP_ST_VNMP_PROBE2",
	"FIP_ST_VNMP_CLAIM",
	"FIP_ST_VNMP_UP",
पूर्ण;

/* Based on fc_rport_state क्रमागत from libfc.h */
अटल अक्षर *fc_rport_state_names[] = अणु
	"RPORT_ST_INIT",
	"RPORT_ST_FLOGI",
	"RPORT_ST_PLOGI_WAIT",
	"RPORT_ST_PLOGI",
	"RPORT_ST_PRLI",
	"RPORT_ST_RTV",
	"RPORT_ST_READY",
	"RPORT_ST_ADISC",
	"RPORT_ST_DELETE",
पूर्ण;

अटल पूर्णांक
qedf_driver_stats_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा qedf_ctx *qedf = s->निजी;
	काष्ठा qedf_rport *fcport;
	काष्ठा fc_rport_priv *rdata;

	seq_म_लिखो(s, "Host WWNN/WWPN: %016llx/%016llx\n",
		   qedf->wwnn, qedf->wwpn);
	seq_म_लिखो(s, "Host NPortID: %06x\n", qedf->lport->port_id);
	seq_म_लिखो(s, "Link State: %s\n", atomic_पढ़ो(&qedf->link_state) ?
	    "Up" : "Down");
	seq_म_लिखो(s, "Logical Link State: %s\n", qedf->lport->link_up ?
	    "Up" : "Down");
	seq_म_लिखो(s, "FIP state: %s\n", fip_state_names[qedf->ctlr.state]);
	seq_म_लिखो(s, "FIP VLAN ID: %d\n", qedf->vlan_id & 0xfff);
	seq_म_लिखो(s, "FIP 802.1Q Priority: %d\n", qedf->prio);
	अगर (qedf->ctlr.sel_fcf) अणु
		seq_म_लिखो(s, "FCF WWPN: %016llx\n",
			   qedf->ctlr.sel_fcf->चयन_name);
		seq_म_लिखो(s, "FCF MAC: %pM\n", qedf->ctlr.sel_fcf->fcf_mac);
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "FCF not selected\n");
	पूर्ण

	seq_माला_दो(s, "\nSGE stats:\n\n");
	seq_म_लिखो(s, "cmg_mgr free io_reqs: %d\n",
	    atomic_पढ़ो(&qedf->cmd_mgr->मुक्त_list_cnt));
	seq_म_लिखो(s, "slow SGEs: %d\n", qedf->slow_sge_ios);
	seq_म_लिखो(s, "fast SGEs: %d\n\n", qedf->fast_sge_ios);

	seq_माला_दो(s, "Offloaded ports:\n\n");

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(fcport, &qedf->fcports, peers) अणु
		rdata = fcport->rdata;
		अगर (rdata == शून्य)
			जारी;
		seq_म_लिखो(s, "%016llx/%016llx/%06x: state=%s, free_sqes=%d, num_active_ios=%d\n",
			   rdata->rport->node_name, rdata->rport->port_name,
			   rdata->ids.port_id,
			   fc_rport_state_names[rdata->rp_state],
			   atomic_पढ़ो(&fcport->मुक्त_sqes),
			   atomic_पढ़ो(&fcport->num_active_ios));
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक
qedf_dbg_driver_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा qedf_dbg_ctx *qedf_dbg = inode->i_निजी;
	काष्ठा qedf_ctx *qedf = container_of(qedf_dbg,
	    काष्ठा qedf_ctx, dbg_ctx);

	वापस single_खोलो(file, qedf_driver_stats_show, qedf);
पूर्ण

अटल sमाप_प्रकार
qedf_dbg_clear_stats_cmd_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				   माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक cnt = 0;

	/* Essentially a पढ़ो stub */
	cnt = min_t(पूर्णांक, count, cnt - *ppos);
	*ppos += cnt;
	वापस cnt;
पूर्ण

अटल sमाप_प्रकार
qedf_dbg_clear_stats_cmd_ग_लिखो(काष्ठा file *filp,
				    स्थिर अक्षर __user *buffer, माप_प्रकार count,
				    loff_t *ppos)
अणु
	काष्ठा qedf_dbg_ctx *qedf_dbg =
				(काष्ठा qedf_dbg_ctx *)filp->निजी_data;
	काष्ठा qedf_ctx *qedf = container_of(qedf_dbg, काष्ठा qedf_ctx,
	    dbg_ctx);

	QEDF_INFO(qedf_dbg, QEDF_LOG_DEBUGFS, "Clearing stat counters.\n");

	अगर (!count || *ppos)
		वापस 0;

	/* Clear stat counters exposed by 'stats' node */
	qedf->slow_sge_ios = 0;
	qedf->fast_sge_ios = 0;

	वापस count;
पूर्ण

अटल पूर्णांक
qedf_offload_stats_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा qedf_ctx *qedf = s->निजी;
	काष्ठा qed_fcoe_stats *fw_fcoe_stats;

	fw_fcoe_stats = kदो_स्मृति(माप(काष्ठा qed_fcoe_stats), GFP_KERNEL);
	अगर (!fw_fcoe_stats) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Could not allocate memory for "
		    "fw_fcoe_stats.\n");
		जाओ out;
	पूर्ण

	/* Query firmware क्रम offload stats */
	qed_ops->get_stats(qedf->cdev, fw_fcoe_stats);

	seq_म_लिखो(s, "fcoe_rx_byte_cnt=%llu\n"
	    "fcoe_rx_data_pkt_cnt=%llu\n"
	    "fcoe_rx_xfer_pkt_cnt=%llu\n"
	    "fcoe_rx_other_pkt_cnt=%llu\n"
	    "fcoe_silent_drop_pkt_cmdq_full_cnt=%u\n"
	    "fcoe_silent_drop_pkt_crc_error_cnt=%u\n"
	    "fcoe_silent_drop_pkt_task_invalid_cnt=%u\n"
	    "fcoe_silent_drop_total_pkt_cnt=%u\n"
	    "fcoe_silent_drop_pkt_rq_full_cnt=%u\n"
	    "fcoe_tx_byte_cnt=%llu\n"
	    "fcoe_tx_data_pkt_cnt=%llu\n"
	    "fcoe_tx_xfer_pkt_cnt=%llu\n"
	    "fcoe_tx_other_pkt_cnt=%llu\n",
	    fw_fcoe_stats->fcoe_rx_byte_cnt,
	    fw_fcoe_stats->fcoe_rx_data_pkt_cnt,
	    fw_fcoe_stats->fcoe_rx_xfer_pkt_cnt,
	    fw_fcoe_stats->fcoe_rx_other_pkt_cnt,
	    fw_fcoe_stats->fcoe_silent_drop_pkt_cmdq_full_cnt,
	    fw_fcoe_stats->fcoe_silent_drop_pkt_crc_error_cnt,
	    fw_fcoe_stats->fcoe_silent_drop_pkt_task_invalid_cnt,
	    fw_fcoe_stats->fcoe_silent_drop_total_pkt_cnt,
	    fw_fcoe_stats->fcoe_silent_drop_pkt_rq_full_cnt,
	    fw_fcoe_stats->fcoe_tx_byte_cnt,
	    fw_fcoe_stats->fcoe_tx_data_pkt_cnt,
	    fw_fcoe_stats->fcoe_tx_xfer_pkt_cnt,
	    fw_fcoe_stats->fcoe_tx_other_pkt_cnt);

	kमुक्त(fw_fcoe_stats);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
qedf_dbg_offload_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा qedf_dbg_ctx *qedf_dbg = inode->i_निजी;
	काष्ठा qedf_ctx *qedf = container_of(qedf_dbg,
	    काष्ठा qedf_ctx, dbg_ctx);

	वापस single_खोलो(file, qedf_offload_stats_show, qedf);
पूर्ण

स्थिर काष्ठा file_operations qedf_dbg_fops[] = अणु
	qedf_dbg_fileops(qedf, fp_पूर्णांक),
	qedf_dbg_fileops_seq(qedf, io_trace),
	qedf_dbg_fileops(qedf, debug),
	qedf_dbg_fileops(qedf, stop_io_on_error),
	qedf_dbg_fileops_seq(qedf, driver_stats),
	qedf_dbg_fileops(qedf, clear_stats),
	qedf_dbg_fileops_seq(qedf, offload_stats),
	/* This must be last */
	अणु पूर्ण,
पूर्ण;

#अन्यथा /* CONFIG_DEBUG_FS */
व्योम qedf_dbg_host_init(काष्ठा qedf_dbg_ctx *);
व्योम qedf_dbg_host_निकास(काष्ठा qedf_dbg_ctx *);
व्योम qedf_dbg_init(अक्षर *);
व्योम qedf_dbg_निकास(व्योम);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
