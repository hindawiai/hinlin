<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#समावेश "qedi.h"
#समावेश "qedi_dbg.h"

#समावेश <linux/uaccess.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>

पूर्णांक qedi_करो_not_recover;
अटल काष्ठा dentry *qedi_dbg_root;

व्योम
qedi_dbg_host_init(काष्ठा qedi_dbg_ctx *qedi,
		   स्थिर काष्ठा qedi_debugfs_ops *करोps,
		   स्थिर काष्ठा file_operations *fops)
अणु
	अक्षर host_स_नाम[32];

	प्र_लिखो(host_स_नाम, "host%u", qedi->host_no);
	qedi->bdf_dentry = debugfs_create_dir(host_स_नाम, qedi_dbg_root);

	जबतक (करोps) अणु
		अगर (!(करोps->name))
			अवरोध;

		debugfs_create_file(करोps->name, 0600, qedi->bdf_dentry, qedi,
				    fops);
		करोps++;
		fops++;
	पूर्ण
पूर्ण

व्योम
qedi_dbg_host_निकास(काष्ठा qedi_dbg_ctx *qedi)
अणु
	debugfs_हटाओ_recursive(qedi->bdf_dentry);
	qedi->bdf_dentry = शून्य;
पूर्ण

व्योम
qedi_dbg_init(अक्षर *drv_name)
अणु
	qedi_dbg_root = debugfs_create_dir(drv_name, शून्य);
पूर्ण

व्योम
qedi_dbg_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(qedi_dbg_root);
	qedi_dbg_root = शून्य;
पूर्ण

अटल sमाप_प्रकार
qedi_dbg_करो_not_recover_enable(काष्ठा qedi_dbg_ctx *qedi_dbg)
अणु
	अगर (!qedi_करो_not_recover)
		qedi_करो_not_recover = 1;

	QEDI_INFO(qedi_dbg, QEDI_LOG_DEBUGFS, "do_not_recover=%d\n",
		  qedi_करो_not_recover);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
qedi_dbg_करो_not_recover_disable(काष्ठा qedi_dbg_ctx *qedi_dbg)
अणु
	अगर (qedi_करो_not_recover)
		qedi_करो_not_recover = 0;

	QEDI_INFO(qedi_dbg, QEDI_LOG_DEBUGFS, "do_not_recover=%d\n",
		  qedi_करो_not_recover);
	वापस 0;
पूर्ण

अटल काष्ठा qedi_list_of_funcs qedi_dbg_करो_not_recover_ops[] = अणु
	अणु "enable", qedi_dbg_करो_not_recover_enable पूर्ण,
	अणु "disable", qedi_dbg_करो_not_recover_disable पूर्ण,
	अणु शून्य, शून्य पूर्ण
पूर्ण;

स्थिर काष्ठा qedi_debugfs_ops qedi_debugfs_ops[] = अणु
	अणु "gbl_ctx", शून्य पूर्ण,
	अणु "do_not_recover", qedi_dbg_करो_not_recover_opsपूर्ण,
	अणु "io_trace", शून्य पूर्ण,
	अणु शून्य, शून्य पूर्ण
पूर्ण;

अटल sमाप_प्रकार
qedi_dbg_करो_not_recover_cmd_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
				  माप_प्रकार count, loff_t *ppos)
अणु
	माप_प्रकार cnt = 0;
	काष्ठा qedi_dbg_ctx *qedi_dbg =
			(काष्ठा qedi_dbg_ctx *)filp->निजी_data;
	काष्ठा qedi_list_of_funcs *lof = qedi_dbg_करो_not_recover_ops;

	अगर (*ppos)
		वापस 0;

	जबतक (lof) अणु
		अगर (!(lof->oper_str))
			अवरोध;

		अगर (!म_भेदन(lof->oper_str, buffer, म_माप(lof->oper_str))) अणु
			cnt = lof->oper_func(qedi_dbg);
			अवरोध;
		पूर्ण

		lof++;
	पूर्ण
	वापस (count - cnt);
पूर्ण

अटल sमाप_प्रकार
qedi_dbg_करो_not_recover_cmd_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				 माप_प्रकार count, loff_t *ppos)
अणु
	माप_प्रकार cnt = 0;

	अगर (*ppos)
		वापस 0;

	cnt = प्र_लिखो(buffer, "do_not_recover=%d\n", qedi_करो_not_recover);
	cnt = min_t(पूर्णांक, count, cnt - *ppos);
	*ppos += cnt;
	वापस cnt;
पूर्ण

अटल पूर्णांक
qedi_gbl_ctx_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा qedi_fastpath *fp = शून्य;
	काष्ठा qed_sb_info *sb_info = शून्य;
	काष्ठा status_block_e4 *sb = शून्य;
	काष्ठा global_queue *que = शून्य;
	पूर्णांक id;
	u16 prod_idx;
	काष्ठा qedi_ctx *qedi = s->निजी;
	अचिन्हित दीर्घ flags;

	seq_माला_दो(s, " DUMP CQ CONTEXT:\n");

	क्रम (id = 0; id < MIN_NUM_CPUS_MSIX(qedi); id++) अणु
		spin_lock_irqsave(&qedi->hba_lock, flags);
		seq_म_लिखो(s, "=========FAST CQ PATH [%d] ==========\n", id);
		fp = &qedi->fp_array[id];
		sb_info = fp->sb_info;
		sb = sb_info->sb_virt;
		prod_idx = (sb->pi_array[QEDI_PROTO_CQ_PROD_IDX] &
			    STATUS_BLOCK_E4_PROD_INDEX_MASK);
		seq_म_लिखो(s, "SB PROD IDX: %d\n", prod_idx);
		que = qedi->global_queues[fp->sb_id];
		seq_म_लिखो(s, "DRV CONS IDX: %d\n", que->cq_cons_idx);
		seq_म_लिखो(s, "CQ complete host memory: %d\n", fp->sb_id);
		seq_माला_दो(s, "=========== END ==================\n\n\n");
		spin_unlock_irqrestore(&qedi->hba_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
qedi_dbg_gbl_ctx_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा qedi_dbg_ctx *qedi_dbg = inode->i_निजी;
	काष्ठा qedi_ctx *qedi = container_of(qedi_dbg, काष्ठा qedi_ctx,
					     dbg_ctx);

	वापस single_खोलो(file, qedi_gbl_ctx_show, qedi);
पूर्ण

अटल पूर्णांक
qedi_io_trace_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	पूर्णांक id, idx = 0;
	काष्ठा qedi_ctx *qedi = s->निजी;
	काष्ठा qedi_io_log *io_log;
	अचिन्हित दीर्घ flags;

	seq_माला_दो(s, " DUMP IO LOGS:\n");
	spin_lock_irqsave(&qedi->io_trace_lock, flags);
	idx = qedi->io_trace_idx;
	क्रम (id = 0; id < QEDI_IO_TRACE_SIZE; id++) अणु
		io_log = &qedi->io_trace_buf[idx];
		seq_म_लिखो(s, "iodir-%d:", io_log->direction);
		seq_म_लिखो(s, "tid-0x%x:", io_log->task_id);
		seq_म_लिखो(s, "cid-0x%x:", io_log->cid);
		seq_म_लिखो(s, "lun-%d:", io_log->lun);
		seq_म_लिखो(s, "op-0x%02x:", io_log->op);
		seq_म_लिखो(s, "0x%02x%02x%02x%02x:", io_log->lba[0],
			   io_log->lba[1], io_log->lba[2], io_log->lba[3]);
		seq_म_लिखो(s, "buflen-%d:", io_log->bufflen);
		seq_म_लिखो(s, "sgcnt-%d:", io_log->sg_count);
		seq_म_लिखो(s, "res-0x%08x:", io_log->result);
		seq_म_लिखो(s, "jif-%lu:", io_log->jअगरfies);
		seq_म_लिखो(s, "blk_req_cpu-%d:", io_log->blk_req_cpu);
		seq_म_लिखो(s, "req_cpu-%d:", io_log->req_cpu);
		seq_म_लिखो(s, "intr_cpu-%d:", io_log->पूर्णांकr_cpu);
		seq_म_लिखो(s, "blk_rsp_cpu-%d\n", io_log->blk_rsp_cpu);

		idx++;
		अगर (idx == QEDI_IO_TRACE_SIZE)
			idx = 0;
	पूर्ण
	spin_unlock_irqrestore(&qedi->io_trace_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
qedi_dbg_io_trace_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा qedi_dbg_ctx *qedi_dbg = inode->i_निजी;
	काष्ठा qedi_ctx *qedi = container_of(qedi_dbg, काष्ठा qedi_ctx,
					     dbg_ctx);

	वापस single_खोलो(file, qedi_io_trace_show, qedi);
पूर्ण

स्थिर काष्ठा file_operations qedi_dbg_fops[] = अणु
	qedi_dbg_fileops_seq(qedi, gbl_ctx),
	qedi_dbg_fileops(qedi, करो_not_recover),
	qedi_dbg_fileops_seq(qedi, io_trace),
	अणु पूर्ण,
पूर्ण;
