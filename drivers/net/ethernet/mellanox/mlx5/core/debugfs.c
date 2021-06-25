<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/mlx5/qp.h>
#समावेश <linux/mlx5/cq.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"
#समावेश "lib/eq.h"

क्रमागत अणु
	QP_PID,
	QP_STATE,
	QP_XPORT,
	QP_MTU,
	QP_N_RECV,
	QP_RECV_SZ,
	QP_N_SEND,
	QP_LOG_PG_SZ,
	QP_RQPN,
पूर्ण;

अटल अक्षर *qp_fields[] = अणु
	[QP_PID]	= "pid",
	[QP_STATE]	= "state",
	[QP_XPORT]	= "transport",
	[QP_MTU]	= "mtu",
	[QP_N_RECV]	= "num_recv",
	[QP_RECV_SZ]	= "rcv_wqe_sz",
	[QP_N_SEND]	= "num_send",
	[QP_LOG_PG_SZ]	= "log2_page_sz",
	[QP_RQPN]	= "remote_qpn",
पूर्ण;

क्रमागत अणु
	EQ_NUM_EQES,
	EQ_INTR,
	EQ_LOG_PG_SZ,
पूर्ण;

अटल अक्षर *eq_fields[] = अणु
	[EQ_NUM_EQES]	= "num_eqes",
	[EQ_INTR]	= "intr",
	[EQ_LOG_PG_SZ]	= "log_page_size",
पूर्ण;

क्रमागत अणु
	CQ_PID,
	CQ_NUM_CQES,
	CQ_LOG_PG_SZ,
पूर्ण;

अटल अक्षर *cq_fields[] = अणु
	[CQ_PID]	= "pid",
	[CQ_NUM_CQES]	= "num_cqes",
	[CQ_LOG_PG_SZ]	= "log_page_size",
पूर्ण;

काष्ठा dentry *mlx5_debugfs_root;
EXPORT_SYMBOL(mlx5_debugfs_root);

व्योम mlx5_रेजिस्टर_debugfs(व्योम)
अणु
	mlx5_debugfs_root = debugfs_create_dir("mlx5", शून्य);
पूर्ण

व्योम mlx5_unरेजिस्टर_debugfs(व्योम)
अणु
	debugfs_हटाओ(mlx5_debugfs_root);
पूर्ण

व्योम mlx5_qp_debugfs_init(काष्ठा mlx5_core_dev *dev)
अणु
	dev->priv.qp_debugfs = debugfs_create_dir("QPs",  dev->priv.dbg_root);
पूर्ण
EXPORT_SYMBOL(mlx5_qp_debugfs_init);

व्योम mlx5_qp_debugfs_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	debugfs_हटाओ_recursive(dev->priv.qp_debugfs);
पूर्ण
EXPORT_SYMBOL(mlx5_qp_debugfs_cleanup);

व्योम mlx5_eq_debugfs_init(काष्ठा mlx5_core_dev *dev)
अणु
	dev->priv.eq_debugfs = debugfs_create_dir("EQs",  dev->priv.dbg_root);
पूर्ण

व्योम mlx5_eq_debugfs_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	debugfs_हटाओ_recursive(dev->priv.eq_debugfs);
पूर्ण

अटल sमाप_प्रकार average_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			    loff_t *pos)
अणु
	काष्ठा mlx5_cmd_stats *stats;
	u64 field = 0;
	पूर्णांक ret;
	अक्षर tbuf[22];

	stats = filp->निजी_data;
	spin_lock_irq(&stats->lock);
	अगर (stats->n)
		field = भाग64_u64(stats->sum, stats->n);
	spin_unlock_irq(&stats->lock);
	ret = snम_लिखो(tbuf, माप(tbuf), "%llu\n", field);
	वापस simple_पढ़ो_from_buffer(buf, count, pos, tbuf, ret);
पूर्ण

अटल sमाप_प्रकार average_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा mlx5_cmd_stats *stats;

	stats = filp->निजी_data;
	spin_lock_irq(&stats->lock);
	stats->sum = 0;
	stats->n = 0;
	spin_unlock_irq(&stats->lock);

	*pos += count;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations stats_fops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= simple_खोलो,
	.पढ़ो	= average_पढ़ो,
	.ग_लिखो	= average_ग_लिखो,
पूर्ण;

व्योम mlx5_cmdअगर_debugfs_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_cmd_stats *stats;
	काष्ठा dentry **cmd;
	स्थिर अक्षर *namep;
	पूर्णांक i;

	cmd = &dev->priv.cmdअगर_debugfs;
	*cmd = debugfs_create_dir("commands", dev->priv.dbg_root);

	क्रम (i = 0; i < MLX5_CMD_OP_MAX; i++) अणु
		stats = &dev->cmd.stats[i];
		namep = mlx5_command_str(i);
		अगर (म_भेद(namep, "unknown command opcode")) अणु
			stats->root = debugfs_create_dir(namep, *cmd);

			debugfs_create_file("average", 0400, stats->root, stats,
					    &stats_fops);
			debugfs_create_u64("n", 0400, stats->root, &stats->n);
		पूर्ण
	पूर्ण
पूर्ण

व्योम mlx5_cmdअगर_debugfs_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	debugfs_हटाओ_recursive(dev->priv.cmdअगर_debugfs);
पूर्ण

व्योम mlx5_cq_debugfs_init(काष्ठा mlx5_core_dev *dev)
अणु
	dev->priv.cq_debugfs = debugfs_create_dir("CQs",  dev->priv.dbg_root);
पूर्ण

व्योम mlx5_cq_debugfs_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	debugfs_हटाओ_recursive(dev->priv.cq_debugfs);
पूर्ण

अटल u64 qp_पढ़ो_field(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_qp *qp,
			 पूर्णांक index, पूर्णांक *is_str)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_qp_out);
	u32 in[MLX5_ST_SZ_DW(query_qp_in)] = अणुपूर्ण;
	u64 param = 0;
	u32 *out;
	पूर्णांक state;
	u32 *qpc;
	पूर्णांक err;

	out = kzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस 0;

	MLX5_SET(query_qp_in, in, opcode, MLX5_CMD_OP_QUERY_QP);
	MLX5_SET(query_qp_in, in, qpn, qp->qpn);
	err = mlx5_cmd_exec_inout(dev, query_qp, in, out);
	अगर (err)
		जाओ out;

	*is_str = 0;

	qpc = MLX5_ADDR_OF(query_qp_out, out, qpc);
	चयन (index) अणु
	हाल QP_PID:
		param = qp->pid;
		अवरोध;
	हाल QP_STATE:
		state = MLX5_GET(qpc, qpc, state);
		param = (अचिन्हित दीर्घ)mlx5_qp_state_str(state);
		*is_str = 1;
		अवरोध;
	हाल QP_XPORT:
		param = (अचिन्हित दीर्घ)mlx5_qp_type_str(MLX5_GET(qpc, qpc, st));
		*is_str = 1;
		अवरोध;
	हाल QP_MTU:
		चयन (MLX5_GET(qpc, qpc, mtu)) अणु
		हाल IB_MTU_256:
			param = 256;
			अवरोध;
		हाल IB_MTU_512:
			param = 512;
			अवरोध;
		हाल IB_MTU_1024:
			param = 1024;
			अवरोध;
		हाल IB_MTU_2048:
			param = 2048;
			अवरोध;
		हाल IB_MTU_4096:
			param = 4096;
			अवरोध;
		शेष:
			param = 0;
		पूर्ण
		अवरोध;
	हाल QP_N_RECV:
		param = 1 << MLX5_GET(qpc, qpc, log_rq_size);
		अवरोध;
	हाल QP_RECV_SZ:
		param = 1 << (MLX5_GET(qpc, qpc, log_rq_stride) + 4);
		अवरोध;
	हाल QP_N_SEND:
		अगर (!MLX5_GET(qpc, qpc, no_sq))
			param = 1 << MLX5_GET(qpc, qpc, log_sq_size);
		अवरोध;
	हाल QP_LOG_PG_SZ:
		param = MLX5_GET(qpc, qpc, log_page_size) + 12;
		अवरोध;
	हाल QP_RQPN:
		param = MLX5_GET(qpc, qpc, remote_qpn);
		अवरोध;
	पूर्ण
out:
	kमुक्त(out);
	वापस param;
पूर्ण

अटल u64 eq_पढ़ो_field(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq,
			 पूर्णांक index)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_eq_out);
	u32 in[MLX5_ST_SZ_DW(query_eq_in)] = अणुपूर्ण;
	u64 param = 0;
	व्योम *ctx;
	u32 *out;
	पूर्णांक err;

	out = kzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस param;

	MLX5_SET(query_eq_in, in, opcode, MLX5_CMD_OP_QUERY_EQ);
	MLX5_SET(query_eq_in, in, eq_number, eq->eqn);
	err = mlx5_cmd_exec_inout(dev, query_eq, in, out);
	अगर (err) अणु
		mlx5_core_warn(dev, "failed to query eq\n");
		जाओ out;
	पूर्ण
	ctx = MLX5_ADDR_OF(query_eq_out, out, eq_context_entry);

	चयन (index) अणु
	हाल EQ_NUM_EQES:
		param = 1 << MLX5_GET(eqc, ctx, log_eq_size);
		अवरोध;
	हाल EQ_INTR:
		param = MLX5_GET(eqc, ctx, पूर्णांकr);
		अवरोध;
	हाल EQ_LOG_PG_SZ:
		param = MLX5_GET(eqc, ctx, log_page_size) + 12;
		अवरोध;
	पूर्ण

out:
	kमुक्त(out);
	वापस param;
पूर्ण

अटल u64 cq_पढ़ो_field(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq,
			 पूर्णांक index)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_cq_out);
	u64 param = 0;
	व्योम *ctx;
	u32 *out;
	पूर्णांक err;

	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस param;

	err = mlx5_core_query_cq(dev, cq, out);
	अगर (err) अणु
		mlx5_core_warn(dev, "failed to query cq\n");
		जाओ out;
	पूर्ण
	ctx = MLX5_ADDR_OF(query_cq_out, out, cq_context);

	चयन (index) अणु
	हाल CQ_PID:
		param = cq->pid;
		अवरोध;
	हाल CQ_NUM_CQES:
		param = 1 << MLX5_GET(cqc, ctx, log_cq_size);
		अवरोध;
	हाल CQ_LOG_PG_SZ:
		param = MLX5_GET(cqc, ctx, log_page_size);
		अवरोध;
	पूर्ण

out:
	kvमुक्त(out);
	वापस param;
पूर्ण

अटल sमाप_प्रकार dbg_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			loff_t *pos)
अणु
	काष्ठा mlx5_field_desc *desc;
	काष्ठा mlx5_rsc_debug *d;
	अक्षर tbuf[18];
	पूर्णांक is_str = 0;
	u64 field;
	पूर्णांक ret;

	desc = filp->निजी_data;
	d = (व्योम *)(desc - desc->i) - माप(*d);
	चयन (d->type) अणु
	हाल MLX5_DBG_RSC_QP:
		field = qp_पढ़ो_field(d->dev, d->object, desc->i, &is_str);
		अवरोध;

	हाल MLX5_DBG_RSC_EQ:
		field = eq_पढ़ो_field(d->dev, d->object, desc->i);
		अवरोध;

	हाल MLX5_DBG_RSC_CQ:
		field = cq_पढ़ो_field(d->dev, d->object, desc->i);
		अवरोध;

	शेष:
		mlx5_core_warn(d->dev, "invalid resource type %d\n", d->type);
		वापस -EINVAL;
	पूर्ण

	अगर (is_str)
		ret = snम_लिखो(tbuf, माप(tbuf), "%s\n", (स्थिर अक्षर *)(अचिन्हित दीर्घ)field);
	अन्यथा
		ret = snम_लिखो(tbuf, माप(tbuf), "0x%llx\n", field);

	वापस simple_पढ़ो_from_buffer(buf, count, pos, tbuf, ret);
पूर्ण

अटल स्थिर काष्ठा file_operations fops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= simple_खोलो,
	.पढ़ो	= dbg_पढ़ो,
पूर्ण;

अटल पूर्णांक add_res_tree(काष्ठा mlx5_core_dev *dev, क्रमागत dbg_rsc_type type,
			काष्ठा dentry *root, काष्ठा mlx5_rsc_debug **dbg,
			पूर्णांक rsn, अक्षर **field, पूर्णांक nfile, व्योम *data)
अणु
	काष्ठा mlx5_rsc_debug *d;
	अक्षर resn[32];
	पूर्णांक i;

	d = kzalloc(काष्ठा_size(d, fields, nfile), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	d->dev = dev;
	d->object = data;
	d->type = type;
	प्र_लिखो(resn, "0x%x", rsn);
	d->root = debugfs_create_dir(resn,  root);

	क्रम (i = 0; i < nfile; i++) अणु
		d->fields[i].i = i;
		debugfs_create_file(field[i], 0400, d->root, &d->fields[i],
				    &fops);
	पूर्ण
	*dbg = d;

	वापस 0;
पूर्ण

अटल व्योम rem_res_tree(काष्ठा mlx5_rsc_debug *d)
अणु
	debugfs_हटाओ_recursive(d->root);
	kमुक्त(d);
पूर्ण

पूर्णांक mlx5_debug_qp_add(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_qp *qp)
अणु
	पूर्णांक err;

	अगर (!mlx5_debugfs_root)
		वापस 0;

	err = add_res_tree(dev, MLX5_DBG_RSC_QP, dev->priv.qp_debugfs,
			   &qp->dbg, qp->qpn, qp_fields,
			   ARRAY_SIZE(qp_fields), qp);
	अगर (err)
		qp->dbg = शून्य;

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_debug_qp_add);

व्योम mlx5_debug_qp_हटाओ(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_qp *qp)
अणु
	अगर (!mlx5_debugfs_root)
		वापस;

	अगर (qp->dbg)
		rem_res_tree(qp->dbg);
पूर्ण
EXPORT_SYMBOL(mlx5_debug_qp_हटाओ);

पूर्णांक mlx5_debug_eq_add(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq)
अणु
	पूर्णांक err;

	अगर (!mlx5_debugfs_root)
		वापस 0;

	err = add_res_tree(dev, MLX5_DBG_RSC_EQ, dev->priv.eq_debugfs,
			   &eq->dbg, eq->eqn, eq_fields,
			   ARRAY_SIZE(eq_fields), eq);
	अगर (err)
		eq->dbg = शून्य;

	वापस err;
पूर्ण

व्योम mlx5_debug_eq_हटाओ(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq)
अणु
	अगर (!mlx5_debugfs_root)
		वापस;

	अगर (eq->dbg)
		rem_res_tree(eq->dbg);
पूर्ण

पूर्णांक mlx5_debug_cq_add(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq)
अणु
	पूर्णांक err;

	अगर (!mlx5_debugfs_root)
		वापस 0;

	err = add_res_tree(dev, MLX5_DBG_RSC_CQ, dev->priv.cq_debugfs,
			   &cq->dbg, cq->cqn, cq_fields,
			   ARRAY_SIZE(cq_fields), cq);
	अगर (err)
		cq->dbg = शून्य;

	वापस err;
पूर्ण

व्योम mlx5_debug_cq_हटाओ(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq)
अणु
	अगर (!mlx5_debugfs_root)
		वापस;

	अगर (cq->dbg)
		rem_res_tree(cq->dbg);
पूर्ण
