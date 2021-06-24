<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

अटल काष्ठा dentry *qla2x00_dfs_root;
अटल atomic_t qla2x00_dfs_root_count;

#घोषणा QLA_DFS_RPORT_DEVLOSS_TMO	1

अटल पूर्णांक
qla_dfs_rport_get(काष्ठा fc_port *fp, पूर्णांक attr_id, u64 *val)
अणु
	चयन (attr_id) अणु
	हाल QLA_DFS_RPORT_DEVLOSS_TMO:
		/* Only supported क्रम FC-NVMe devices that are रेजिस्टरed. */
		अगर (!(fp->nvme_flag & NVME_FLAG_REGISTERED))
			वापस -EIO;
		*val = fp->nvme_remote_port->dev_loss_पंचांगo;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
qla_dfs_rport_set(काष्ठा fc_port *fp, पूर्णांक attr_id, u64 val)
अणु
	चयन (attr_id) अणु
	हाल QLA_DFS_RPORT_DEVLOSS_TMO:
		/* Only supported क्रम FC-NVMe devices that are रेजिस्टरed. */
		अगर (!(fp->nvme_flag & NVME_FLAG_REGISTERED))
			वापस -EIO;
#अगर (IS_ENABLED(CONFIG_NVME_FC))
		वापस nvme_fc_set_remoteport_devloss(fp->nvme_remote_port,
						      val);
#अन्यथा /* CONFIG_NVME_FC */
		वापस -EINVAL;
#पूर्ण_अगर /* CONFIG_NVME_FC */
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा DEFINE_QLA_DFS_RPORT_RW_ATTR(_attr_id, _attr)		\
अटल पूर्णांक qla_dfs_rport_##_attr##_get(व्योम *data, u64 *val)	\
अणु								\
	काष्ठा fc_port *fp = data;				\
	वापस qla_dfs_rport_get(fp, _attr_id, val);		\
पूर्ण								\
अटल पूर्णांक qla_dfs_rport_##_attr##_set(व्योम *data, u64 val)	\
अणु								\
	काष्ठा fc_port *fp = data;				\
	वापस qla_dfs_rport_set(fp, _attr_id, val);		\
पूर्ण								\
DEFINE_DEBUGFS_ATTRIBUTE(qla_dfs_rport_##_attr##_fops,		\
		qla_dfs_rport_##_attr##_get,			\
		qla_dfs_rport_##_attr##_set, "%llu\n")

/*
 * Wrapper क्रम getting fc_port fields.
 *
 * _attr    : Attribute name.
 * _get_val : Accessor macro to retrieve the value.
 */
#घोषणा DEFINE_QLA_DFS_RPORT_FIELD_GET(_attr, _get_val)			\
अटल पूर्णांक qla_dfs_rport_field_##_attr##_get(व्योम *data, u64 *val)	\
अणु									\
	काष्ठा fc_port *fp = data;					\
	*val = _get_val;						\
	वापस 0;							\
पूर्ण									\
DEFINE_DEBUGFS_ATTRIBUTE(qla_dfs_rport_field_##_attr##_fops,		\
		qla_dfs_rport_field_##_attr##_get,			\
		शून्य, "%llu\n")

#घोषणा DEFINE_QLA_DFS_RPORT_ACCESS(_attr, _get_val) \
	DEFINE_QLA_DFS_RPORT_FIELD_GET(_attr, _get_val)

#घोषणा DEFINE_QLA_DFS_RPORT_FIELD(_attr) \
	DEFINE_QLA_DFS_RPORT_FIELD_GET(_attr, fp->_attr)

DEFINE_QLA_DFS_RPORT_RW_ATTR(QLA_DFS_RPORT_DEVLOSS_TMO, dev_loss_पंचांगo);

DEFINE_QLA_DFS_RPORT_FIELD(disc_state);
DEFINE_QLA_DFS_RPORT_FIELD(scan_state);
DEFINE_QLA_DFS_RPORT_FIELD(fw_login_state);
DEFINE_QLA_DFS_RPORT_FIELD(login_छोड़ो);
DEFINE_QLA_DFS_RPORT_FIELD(flags);
DEFINE_QLA_DFS_RPORT_FIELD(nvme_flag);
DEFINE_QLA_DFS_RPORT_FIELD(last_rscn_gen);
DEFINE_QLA_DFS_RPORT_FIELD(rscn_gen);
DEFINE_QLA_DFS_RPORT_FIELD(login_gen);
DEFINE_QLA_DFS_RPORT_FIELD(loop_id);
DEFINE_QLA_DFS_RPORT_FIELD_GET(port_id, fp->d_id.b24);
DEFINE_QLA_DFS_RPORT_FIELD_GET(sess_kref, kref_पढ़ो(&fp->sess_kref));

व्योम
qla2x00_dfs_create_rport(scsi_qla_host_t *vha, काष्ठा fc_port *fp)
अणु
	अक्षर wwn[32];

#घोषणा QLA_CREATE_RPORT_FIELD_ATTR(_attr)			\
	debugfs_create_file(#_attr, 0400, fp->dfs_rport_dir,	\
		fp, &qla_dfs_rport_field_##_attr##_fops)

	अगर (!vha->dfs_rport_root || fp->dfs_rport_dir)
		वापस;

	प्र_लिखो(wwn, "pn-%016llx", wwn_to_u64(fp->port_name));
	fp->dfs_rport_dir = debugfs_create_dir(wwn, vha->dfs_rport_root);
	अगर (!fp->dfs_rport_dir)
		वापस;
	अगर (NVME_TARGET(vha->hw, fp))
		debugfs_create_file("dev_loss_tmo", 0600, fp->dfs_rport_dir,
				    fp, &qla_dfs_rport_dev_loss_पंचांगo_fops);

	QLA_CREATE_RPORT_FIELD_ATTR(disc_state);
	QLA_CREATE_RPORT_FIELD_ATTR(scan_state);
	QLA_CREATE_RPORT_FIELD_ATTR(fw_login_state);
	QLA_CREATE_RPORT_FIELD_ATTR(login_छोड़ो);
	QLA_CREATE_RPORT_FIELD_ATTR(flags);
	QLA_CREATE_RPORT_FIELD_ATTR(nvme_flag);
	QLA_CREATE_RPORT_FIELD_ATTR(last_rscn_gen);
	QLA_CREATE_RPORT_FIELD_ATTR(rscn_gen);
	QLA_CREATE_RPORT_FIELD_ATTR(login_gen);
	QLA_CREATE_RPORT_FIELD_ATTR(loop_id);
	QLA_CREATE_RPORT_FIELD_ATTR(port_id);
	QLA_CREATE_RPORT_FIELD_ATTR(sess_kref);
पूर्ण

व्योम
qla2x00_dfs_हटाओ_rport(scsi_qla_host_t *vha, काष्ठा fc_port *fp)
अणु
	अगर (!vha->dfs_rport_root || !fp->dfs_rport_dir)
		वापस;
	debugfs_हटाओ_recursive(fp->dfs_rport_dir);
	fp->dfs_rport_dir = शून्य;
पूर्ण

अटल पूर्णांक
qla2x00_dfs_tgt_sess_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	scsi_qla_host_t *vha = s->निजी;
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags;
	काष्ठा fc_port *sess = शून्य;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;

	seq_म_लिखो(s, "%s\n", vha->host_str);
	अगर (tgt) अणु
		seq_माला_दो(s, "Port ID   Port Name                Handle\n");

		spin_lock_irqsave(&ha->tgt.sess_lock, flags);
		list_क्रम_each_entry(sess, &vha->vp_fcports, list)
			seq_म_लिखो(s, "%02x:%02x:%02x  %8phC  %d\n",
			    sess->d_id.b.करोमुख्य, sess->d_id.b.area,
			    sess->d_id.b.al_pa, sess->port_name,
			    sess->loop_id);
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(qla2x00_dfs_tgt_sess);

अटल पूर्णांक
qla2x00_dfs_tgt_port_database_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	scsi_qla_host_t *vha = s->निजी;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा gid_list_info *gid_list;
	dma_addr_t gid_list_dma;
	fc_port_t fc_port;
	अक्षर *id_iter;
	पूर्णांक rc, i;
	uपूर्णांक16_t entries, loop_id;

	seq_म_लिखो(s, "%s\n", vha->host_str);
	gid_list = dma_alloc_coherent(&ha->pdev->dev,
				      qla2x00_gid_list_size(ha),
				      &gid_list_dma, GFP_KERNEL);
	अगर (!gid_list) अणु
		ql_dbg(ql_dbg_user, vha, 0x7018,
		       "DMA allocation failed for %u\n",
		       qla2x00_gid_list_size(ha));
		वापस 0;
	पूर्ण

	rc = qla24xx_gidlist_रुको(vha, gid_list, gid_list_dma,
				  &entries);
	अगर (rc != QLA_SUCCESS)
		जाओ out_मुक्त_id_list;

	id_iter = (अक्षर *)gid_list;

	seq_माला_दो(s, "Port Name	Port ID		Loop ID\n");

	क्रम (i = 0; i < entries; i++) अणु
		काष्ठा gid_list_info *gid =
			(काष्ठा gid_list_info *)id_iter;
		loop_id = le16_to_cpu(gid->loop_id);
		स_रखो(&fc_port, 0, माप(fc_port_t));

		fc_port.loop_id = loop_id;

		rc = qla24xx_gpdb_रुको(vha, &fc_port, 0);
		seq_म_लिखो(s, "%8phC  %02x%02x%02x  %d\n",
			   fc_port.port_name, fc_port.d_id.b.करोमुख्य,
			   fc_port.d_id.b.area, fc_port.d_id.b.al_pa,
			   fc_port.loop_id);
		id_iter += ha->gid_list_info_size;
	पूर्ण
out_मुक्त_id_list:
	dma_मुक्त_coherent(&ha->pdev->dev, qla2x00_gid_list_size(ha),
			  gid_list, gid_list_dma);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(qla2x00_dfs_tgt_port_database);

अटल पूर्णांक
qla_dfs_fw_resource_cnt_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा scsi_qla_host *vha = s->निजी;
	uपूर्णांक16_t mb[MAX_IOCB_MB_REG];
	पूर्णांक rc;
	काष्ठा qla_hw_data *ha = vha->hw;
	u16 iocbs_used, i;

	rc = qla24xx_res_count_रुको(vha, mb, SIZखातापूर्ण_IOCB_MB_REG);
	अगर (rc != QLA_SUCCESS) अणु
		seq_म_लिखो(s, "Mailbox Command failed %d, mb %#x", rc, mb[0]);
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "FW Resource count\n\n");
		seq_म_लिखो(s, "Original TGT exchg count[%d]\n", mb[1]);
		seq_म_लिखो(s, "Current TGT exchg count[%d]\n", mb[2]);
		seq_म_लिखो(s, "Current Initiator Exchange count[%d]\n", mb[3]);
		seq_म_लिखो(s, "Original Initiator Exchange count[%d]\n", mb[6]);
		seq_म_लिखो(s, "Current IOCB count[%d]\n", mb[7]);
		seq_म_लिखो(s, "Original IOCB count[%d]\n", mb[10]);
		seq_म_लिखो(s, "MAX VP count[%d]\n", mb[11]);
		seq_म_लिखो(s, "MAX FCF count[%d]\n", mb[12]);
		seq_म_लिखो(s, "Current free pageable XCB buffer cnt[%d]\n",
		    mb[20]);
		seq_म_लिखो(s, "Original Initiator fast XCB buffer cnt[%d]\n",
		    mb[21]);
		seq_म_लिखो(s, "Current free Initiator fast XCB buffer cnt[%d]\n",
		    mb[22]);
		seq_म_लिखो(s, "Original Target fast XCB buffer cnt[%d]\n",
		    mb[23]);
	पूर्ण

	अगर (ql2xenक्रमce_iocb_limit) अणु
		/* lock is not require. It's an estimate. */
		iocbs_used = ha->base_qpair->fwres.iocbs_used;
		क्रम (i = 0; i < ha->max_qpairs; i++) अणु
			अगर (ha->queue_pair_map[i])
				iocbs_used += ha->queue_pair_map[i]->fwres.iocbs_used;
		पूर्ण

		seq_म_लिखो(s, "Driver: estimate iocb used [%d] high water limit [%d]\n",
			   iocbs_used, ha->base_qpair->fwres.iocbs_limit);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(qla_dfs_fw_resource_cnt);

अटल पूर्णांक
qla_dfs_tgt_counters_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा scsi_qla_host *vha = s->निजी;
	काष्ठा qla_qpair *qpair = vha->hw->base_qpair;
	uपूर्णांक64_t qla_core_sbt_cmd, core_qla_que_buf, qla_core_ret_ctio,
		core_qla_snd_status, qla_core_ret_sta_ctio, core_qla_मुक्त_cmd,
		num_q_full_sent, num_alloc_iocb_failed, num_term_xchg_sent;
	u16 i;
	fc_port_t *fcport = शून्य;

	अगर (qla2x00_chip_is_करोwn(vha))
		वापस 0;

	qla_core_sbt_cmd = qpair->tgt_counters.qla_core_sbt_cmd;
	core_qla_que_buf = qpair->tgt_counters.core_qla_que_buf;
	qla_core_ret_ctio = qpair->tgt_counters.qla_core_ret_ctio;
	core_qla_snd_status = qpair->tgt_counters.core_qla_snd_status;
	qla_core_ret_sta_ctio = qpair->tgt_counters.qla_core_ret_sta_ctio;
	core_qla_मुक्त_cmd = qpair->tgt_counters.core_qla_मुक्त_cmd;
	num_q_full_sent = qpair->tgt_counters.num_q_full_sent;
	num_alloc_iocb_failed = qpair->tgt_counters.num_alloc_iocb_failed;
	num_term_xchg_sent = qpair->tgt_counters.num_term_xchg_sent;

	क्रम (i = 0; i < vha->hw->max_qpairs; i++) अणु
		qpair = vha->hw->queue_pair_map[i];
		अगर (!qpair)
			जारी;
		qla_core_sbt_cmd += qpair->tgt_counters.qla_core_sbt_cmd;
		core_qla_que_buf += qpair->tgt_counters.core_qla_que_buf;
		qla_core_ret_ctio += qpair->tgt_counters.qla_core_ret_ctio;
		core_qla_snd_status += qpair->tgt_counters.core_qla_snd_status;
		qla_core_ret_sta_ctio +=
		    qpair->tgt_counters.qla_core_ret_sta_ctio;
		core_qla_मुक्त_cmd += qpair->tgt_counters.core_qla_मुक्त_cmd;
		num_q_full_sent += qpair->tgt_counters.num_q_full_sent;
		num_alloc_iocb_failed +=
		    qpair->tgt_counters.num_alloc_iocb_failed;
		num_term_xchg_sent += qpair->tgt_counters.num_term_xchg_sent;
	पूर्ण

	seq_माला_दो(s, "Target Counters\n");
	seq_म_लिखो(s, "qla_core_sbt_cmd = %lld\n",
		qla_core_sbt_cmd);
	seq_म_लिखो(s, "qla_core_ret_sta_ctio = %lld\n",
		qla_core_ret_sta_ctio);
	seq_म_लिखो(s, "qla_core_ret_ctio = %lld\n",
		qla_core_ret_ctio);
	seq_म_लिखो(s, "core_qla_que_buf = %lld\n",
		core_qla_que_buf);
	seq_म_लिखो(s, "core_qla_snd_status = %lld\n",
		core_qla_snd_status);
	seq_म_लिखो(s, "core_qla_free_cmd = %lld\n",
		core_qla_मुक्त_cmd);
	seq_म_लिखो(s, "num alloc iocb failed = %lld\n",
		num_alloc_iocb_failed);
	seq_म_लिखो(s, "num term exchange sent = %lld\n",
		num_term_xchg_sent);
	seq_म_लिखो(s, "num Q full sent = %lld\n",
		num_q_full_sent);

	/* DIF stats */
	seq_म_लिखो(s, "DIF Inp Bytes = %lld\n",
		vha->qla_stats.qla_dअगर_stats.dअगर_input_bytes);
	seq_म_लिखो(s, "DIF Outp Bytes = %lld\n",
		vha->qla_stats.qla_dअगर_stats.dअगर_output_bytes);
	seq_म_लिखो(s, "DIF Inp Req = %lld\n",
		vha->qla_stats.qla_dअगर_stats.dअगर_input_requests);
	seq_म_लिखो(s, "DIF Outp Req = %lld\n",
		vha->qla_stats.qla_dअगर_stats.dअगर_output_requests);
	seq_म_लिखो(s, "DIF Guard err = %d\n",
		vha->qla_stats.qla_dअगर_stats.dअगर_guard_err);
	seq_म_लिखो(s, "DIF Ref tag err = %d\n",
		vha->qla_stats.qla_dअगर_stats.dअगर_ref_tag_err);
	seq_म_लिखो(s, "DIF App tag err = %d\n",
		vha->qla_stats.qla_dअगर_stats.dअगर_app_tag_err);

	seq_माला_दो(s, "\n");
	seq_माला_दो(s, "Initiator Error Counters\n");
	seq_म_लिखो(s, "HW Error Count =		%14lld\n",
		   vha->hw_err_cnt);
	seq_म_लिखो(s, "Link Down Count =	%14lld\n",
		   vha->लघु_link_करोwn_cnt);
	seq_म_लिखो(s, "Interface Err Count =	%14lld\n",
		   vha->पूर्णांकerface_err_cnt);
	seq_म_लिखो(s, "Cmd Timeout Count =	%14lld\n",
		   vha->cmd_समयout_cnt);
	seq_म_लिखो(s, "Reset Count =		%14lld\n",
		   vha->reset_cmd_err_cnt);
	seq_माला_दो(s, "\n");

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (!fcport->rport)
			जारी;

		seq_म_लिखो(s, "Target Num = %7d Link Down Count = %14lld\n",
			   fcport->rport->number, fcport->tgt_लघु_link_करोwn_cnt);
	पूर्ण
	seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(qla_dfs_tgt_counters);

अटल पूर्णांक
qla2x00_dfs_fce_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	scsi_qla_host_t *vha = s->निजी;
	uपूर्णांक32_t cnt;
	uपूर्णांक32_t *fce;
	uपूर्णांक64_t fce_start;
	काष्ठा qla_hw_data *ha = vha->hw;

	mutex_lock(&ha->fce_mutex);

	seq_माला_दो(s, "FCE Trace Buffer\n");
	seq_म_लिखो(s, "In Pointer = %llx\n\n", (अचिन्हित दीर्घ दीर्घ)ha->fce_wr);
	seq_म_लिखो(s, "Base = %llx\n\n", (अचिन्हित दीर्घ दीर्घ) ha->fce_dma);
	seq_माला_दो(s, "FCE Enable Registers\n");
	seq_म_लिखो(s, "%08x %08x %08x %08x %08x %08x\n",
	    ha->fce_mb[0], ha->fce_mb[2], ha->fce_mb[3], ha->fce_mb[4],
	    ha->fce_mb[5], ha->fce_mb[6]);

	fce = (uपूर्णांक32_t *) ha->fce;
	fce_start = (अचिन्हित दीर्घ दीर्घ) ha->fce_dma;
	क्रम (cnt = 0; cnt < fce_calc_size(ha->fce_bufs) / 4; cnt++) अणु
		अगर (cnt % 8 == 0)
			seq_म_लिखो(s, "\n%llx: ",
			    (अचिन्हित दीर्घ दीर्घ)((cnt * 4) + fce_start));
		अन्यथा
			seq_अ_दो(s, ' ');
		seq_म_लिखो(s, "%08x", *fce++);
	पूर्ण

	seq_माला_दो(s, "\nEnd\n");

	mutex_unlock(&ha->fce_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla2x00_dfs_fce_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	scsi_qla_host_t *vha = inode->i_निजी;
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval;

	अगर (!ha->flags.fce_enabled)
		जाओ out;

	mutex_lock(&ha->fce_mutex);

	/* Pause tracing to flush FCE buffers. */
	rval = qla2x00_disable_fce_trace(vha, &ha->fce_wr, &ha->fce_rd);
	अगर (rval)
		ql_dbg(ql_dbg_user, vha, 0x705c,
		    "DebugFS: Unable to disable FCE (%d).\n", rval);

	ha->flags.fce_enabled = 0;

	mutex_unlock(&ha->fce_mutex);
out:
	वापस single_खोलो(file, qla2x00_dfs_fce_show, vha);
पूर्ण

अटल पूर्णांक
qla2x00_dfs_fce_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	scsi_qla_host_t *vha = inode->i_निजी;
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval;

	अगर (ha->flags.fce_enabled)
		जाओ out;

	mutex_lock(&ha->fce_mutex);

	/* Re-enable FCE tracing. */
	ha->flags.fce_enabled = 1;
	स_रखो(ha->fce, 0, fce_calc_size(ha->fce_bufs));
	rval = qla2x00_enable_fce_trace(vha, ha->fce_dma, ha->fce_bufs,
	    ha->fce_mb, &ha->fce_bufs);
	अगर (rval) अणु
		ql_dbg(ql_dbg_user, vha, 0x700d,
		    "DebugFS: Unable to reinitialize FCE (%d).\n", rval);
		ha->flags.fce_enabled = 0;
	पूर्ण

	mutex_unlock(&ha->fce_mutex);
out:
	वापस single_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations dfs_fce_ops = अणु
	.खोलो		= qla2x00_dfs_fce_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= qla2x00_dfs_fce_release,
पूर्ण;

अटल पूर्णांक
qla_dfs_naqp_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा scsi_qla_host *vha = s->निजी;
	काष्ठा qla_hw_data *ha = vha->hw;

	seq_म_लिखो(s, "%d\n", ha->tgt.num_act_qpairs);
	वापस 0;
पूर्ण

अटल पूर्णांक
qla_dfs_naqp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा scsi_qla_host *vha = inode->i_निजी;

	वापस single_खोलो(file, qla_dfs_naqp_show, vha);
पूर्ण

अटल sमाप_प्रकार
qla_dfs_naqp_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
    माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा scsi_qla_host *vha = s->निजी;
	काष्ठा qla_hw_data *ha = vha->hw;
	अक्षर *buf;
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ num_act_qp;

	अगर (!(IS_QLA27XX(ha) || IS_QLA83XX(ha) || IS_QLA28XX(ha))) अणु
		pr_err("host%ld: this adapter does not support Multi Q.",
		    vha->host_no);
		वापस -EINVAL;
	पूर्ण

	अगर (!vha->flags.qpairs_available) अणु
		pr_err("host%ld: Driver is not setup with Multi Q.",
		    vha->host_no);
		वापस -EINVAL;
	पूर्ण
	buf = memdup_user_nul(buffer, count);
	अगर (IS_ERR(buf)) अणु
		pr_err("host%ld: fail to copy user buffer.",
		    vha->host_no);
		वापस PTR_ERR(buf);
	पूर्ण

	num_act_qp = simple_म_से_अदीर्घ(buf, शून्य, 0);

	अगर (num_act_qp >= vha->hw->max_qpairs) अणु
		pr_err("User set invalid number of qpairs %lu. Max = %d",
		    num_act_qp, vha->hw->max_qpairs);
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	अगर (num_act_qp != ha->tgt.num_act_qpairs) अणु
		ha->tgt.num_act_qpairs = num_act_qp;
		qlt_clr_qp_table(vha);
	पूर्ण
	rc = count;
out_मुक्त:
	kमुक्त(buf);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations dfs_naqp_ops = अणु
	.खोलो		= qla_dfs_naqp_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
	.ग_लिखो		= qla_dfs_naqp_ग_लिखो,
पूर्ण;


पूर्णांक
qla2x00_dfs_setup(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA25XX(ha) && !IS_QLA81XX(ha) && !IS_QLA83XX(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		जाओ out;
	अगर (!ha->fce)
		जाओ out;

	अगर (qla2x00_dfs_root)
		जाओ create_dir;

	atomic_set(&qla2x00_dfs_root_count, 0);
	qla2x00_dfs_root = debugfs_create_dir(QLA2XXX_DRIVER_NAME, शून्य);

create_dir:
	अगर (ha->dfs_dir)
		जाओ create_nodes;

	mutex_init(&ha->fce_mutex);
	ha->dfs_dir = debugfs_create_dir(vha->host_str, qla2x00_dfs_root);

	atomic_inc(&qla2x00_dfs_root_count);

create_nodes:
	ha->dfs_fw_resource_cnt = debugfs_create_file("fw_resource_count",
	    S_IRUSR, ha->dfs_dir, vha, &qla_dfs_fw_resource_cnt_fops);

	ha->dfs_tgt_counters = debugfs_create_file("tgt_counters", S_IRUSR,
	    ha->dfs_dir, vha, &qla_dfs_tgt_counters_fops);

	ha->tgt.dfs_tgt_port_database = debugfs_create_file("tgt_port_database",
	    S_IRUSR,  ha->dfs_dir, vha, &qla2x00_dfs_tgt_port_database_fops);

	ha->dfs_fce = debugfs_create_file("fce", S_IRUSR, ha->dfs_dir, vha,
	    &dfs_fce_ops);

	ha->tgt.dfs_tgt_sess = debugfs_create_file("tgt_sess",
		S_IRUSR, ha->dfs_dir, vha, &qla2x00_dfs_tgt_sess_fops);

	अगर (IS_QLA27XX(ha) || IS_QLA83XX(ha) || IS_QLA28XX(ha)) अणु
		ha->tgt.dfs_naqp = debugfs_create_file("naqp",
		    0400, ha->dfs_dir, vha, &dfs_naqp_ops);
		अगर (!ha->tgt.dfs_naqp) अणु
			ql_log(ql_log_warn, vha, 0xd011,
			       "Unable to create debugFS naqp node.\n");
			जाओ out;
		पूर्ण
	पूर्ण
	vha->dfs_rport_root = debugfs_create_dir("rports", ha->dfs_dir);
	अगर (!vha->dfs_rport_root) अणु
		ql_log(ql_log_warn, vha, 0xd012,
		       "Unable to create debugFS rports node.\n");
		जाओ out;
	पूर्ण
out:
	वापस 0;
पूर्ण

पूर्णांक
qla2x00_dfs_हटाओ(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (ha->tgt.dfs_naqp) अणु
		debugfs_हटाओ(ha->tgt.dfs_naqp);
		ha->tgt.dfs_naqp = शून्य;
	पूर्ण

	अगर (ha->tgt.dfs_tgt_sess) अणु
		debugfs_हटाओ(ha->tgt.dfs_tgt_sess);
		ha->tgt.dfs_tgt_sess = शून्य;
	पूर्ण

	अगर (ha->tgt.dfs_tgt_port_database) अणु
		debugfs_हटाओ(ha->tgt.dfs_tgt_port_database);
		ha->tgt.dfs_tgt_port_database = शून्य;
	पूर्ण

	अगर (ha->dfs_fw_resource_cnt) अणु
		debugfs_हटाओ(ha->dfs_fw_resource_cnt);
		ha->dfs_fw_resource_cnt = शून्य;
	पूर्ण

	अगर (ha->dfs_tgt_counters) अणु
		debugfs_हटाओ(ha->dfs_tgt_counters);
		ha->dfs_tgt_counters = शून्य;
	पूर्ण

	अगर (ha->dfs_fce) अणु
		debugfs_हटाओ(ha->dfs_fce);
		ha->dfs_fce = शून्य;
	पूर्ण

	अगर (vha->dfs_rport_root) अणु
		debugfs_हटाओ_recursive(vha->dfs_rport_root);
		vha->dfs_rport_root = शून्य;
	पूर्ण

	अगर (ha->dfs_dir) अणु
		debugfs_हटाओ(ha->dfs_dir);
		ha->dfs_dir = शून्य;
		atomic_dec(&qla2x00_dfs_root_count);
	पूर्ण

	अगर (atomic_पढ़ो(&qla2x00_dfs_root_count) == 0 &&
	    qla2x00_dfs_root) अणु
		debugfs_हटाओ(qla2x00_dfs_root);
		qla2x00_dfs_root = शून्य;
	पूर्ण

	वापस 0;
पूर्ण
