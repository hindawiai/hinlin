<शैली गुरु>
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
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
 *
 */

#समावेश <net/addrconf.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mlx5/vport.h>

#समावेश "mlx5_core.h"
#समावेश "lib/mlx5.h"
#समावेश "fpga/conn.h"

#घोषणा MLX5_FPGA_PKEY 0xFFFF
#घोषणा MLX5_FPGA_PKEY_INDEX 0 /* RoCE PKEY 0xFFFF is always at index 0 */
#घोषणा MLX5_FPGA_RECV_SIZE 2048
#घोषणा MLX5_FPGA_PORT_NUM 1
#घोषणा MLX5_FPGA_CQ_BUDGET 64

अटल पूर्णांक mlx5_fpga_conn_map_buf(काष्ठा mlx5_fpga_conn *conn,
				  काष्ठा mlx5_fpga_dma_buf *buf)
अणु
	काष्ठा device *dma_device;
	पूर्णांक err = 0;

	अगर (unlikely(!buf->sg[0].data))
		जाओ out;

	dma_device = mlx5_core_dma_dev(conn->fdev->mdev);
	buf->sg[0].dma_addr = dma_map_single(dma_device, buf->sg[0].data,
					     buf->sg[0].size, buf->dma_dir);
	err = dma_mapping_error(dma_device, buf->sg[0].dma_addr);
	अगर (unlikely(err)) अणु
		mlx5_fpga_warn(conn->fdev, "DMA error on sg 0: %d\n", err);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (!buf->sg[1].data)
		जाओ out;

	buf->sg[1].dma_addr = dma_map_single(dma_device, buf->sg[1].data,
					     buf->sg[1].size, buf->dma_dir);
	err = dma_mapping_error(dma_device, buf->sg[1].dma_addr);
	अगर (unlikely(err)) अणु
		mlx5_fpga_warn(conn->fdev, "DMA error on sg 1: %d\n", err);
		dma_unmap_single(dma_device, buf->sg[0].dma_addr,
				 buf->sg[0].size, buf->dma_dir);
		err = -ENOMEM;
	पूर्ण

out:
	वापस err;
पूर्ण

अटल व्योम mlx5_fpga_conn_unmap_buf(काष्ठा mlx5_fpga_conn *conn,
				     काष्ठा mlx5_fpga_dma_buf *buf)
अणु
	काष्ठा device *dma_device;

	dma_device = mlx5_core_dma_dev(conn->fdev->mdev);
	अगर (buf->sg[1].data)
		dma_unmap_single(dma_device, buf->sg[1].dma_addr,
				 buf->sg[1].size, buf->dma_dir);

	अगर (likely(buf->sg[0].data))
		dma_unmap_single(dma_device, buf->sg[0].dma_addr,
				 buf->sg[0].size, buf->dma_dir);
पूर्ण

अटल पूर्णांक mlx5_fpga_conn_post_recv(काष्ठा mlx5_fpga_conn *conn,
				    काष्ठा mlx5_fpga_dma_buf *buf)
अणु
	काष्ठा mlx5_wqe_data_seg *data;
	अचिन्हित पूर्णांक ix;
	पूर्णांक err = 0;

	err = mlx5_fpga_conn_map_buf(conn, buf);
	अगर (unlikely(err))
		जाओ out;

	अगर (unlikely(conn->qp.rq.pc - conn->qp.rq.cc >= conn->qp.rq.size)) अणु
		mlx5_fpga_conn_unmap_buf(conn, buf);
		वापस -EBUSY;
	पूर्ण

	ix = conn->qp.rq.pc & (conn->qp.rq.size - 1);
	data = mlx5_wq_cyc_get_wqe(&conn->qp.wq.rq, ix);
	data->byte_count = cpu_to_be32(buf->sg[0].size);
	data->lkey = cpu_to_be32(conn->fdev->conn_res.mkey.key);
	data->addr = cpu_to_be64(buf->sg[0].dma_addr);

	conn->qp.rq.pc++;
	conn->qp.rq.bufs[ix] = buf;

	/* Make sure that descriptors are written beक्रमe करोorbell record. */
	dma_wmb();
	*conn->qp.wq.rq.db = cpu_to_be32(conn->qp.rq.pc & 0xffff);
out:
	वापस err;
पूर्ण

अटल व्योम mlx5_fpga_conn_notअगरy_hw(काष्ठा mlx5_fpga_conn *conn, व्योम *wqe)
अणु
	/* ensure wqe is visible to device beक्रमe updating करोorbell record */
	dma_wmb();
	*conn->qp.wq.sq.db = cpu_to_be32(conn->qp.sq.pc);
	/* Make sure that करोorbell record is visible beक्रमe ringing */
	wmb();
	mlx5_ग_लिखो64(wqe, conn->fdev->conn_res.uar->map + MLX5_BF_OFFSET);
पूर्ण

अटल व्योम mlx5_fpga_conn_post_send(काष्ठा mlx5_fpga_conn *conn,
				     काष्ठा mlx5_fpga_dma_buf *buf)
अणु
	काष्ठा mlx5_wqe_ctrl_seg *ctrl;
	काष्ठा mlx5_wqe_data_seg *data;
	अचिन्हित पूर्णांक ix, sgi;
	पूर्णांक size = 1;

	ix = conn->qp.sq.pc & (conn->qp.sq.size - 1);

	ctrl = mlx5_wq_cyc_get_wqe(&conn->qp.wq.sq, ix);
	data = (व्योम *)(ctrl + 1);

	क्रम (sgi = 0; sgi < ARRAY_SIZE(buf->sg); sgi++) अणु
		अगर (!buf->sg[sgi].data)
			अवरोध;
		data->byte_count = cpu_to_be32(buf->sg[sgi].size);
		data->lkey = cpu_to_be32(conn->fdev->conn_res.mkey.key);
		data->addr = cpu_to_be64(buf->sg[sgi].dma_addr);
		data++;
		size++;
	पूर्ण

	ctrl->imm = 0;
	ctrl->fm_ce_se = MLX5_WQE_CTRL_CQ_UPDATE;
	ctrl->opmod_idx_opcode = cpu_to_be32(((conn->qp.sq.pc & 0xffff) << 8) |
					     MLX5_OPCODE_SEND);
	ctrl->qpn_ds = cpu_to_be32(size | (conn->qp.qpn << 8));

	conn->qp.sq.pc++;
	conn->qp.sq.bufs[ix] = buf;
	mlx5_fpga_conn_notअगरy_hw(conn, ctrl);
पूर्ण

पूर्णांक mlx5_fpga_conn_send(काष्ठा mlx5_fpga_conn *conn,
			काष्ठा mlx5_fpga_dma_buf *buf)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (!conn->qp.active)
		वापस -ENOTCONN;

	buf->dma_dir = DMA_TO_DEVICE;
	err = mlx5_fpga_conn_map_buf(conn, buf);
	अगर (err)
		वापस err;

	spin_lock_irqsave(&conn->qp.sq.lock, flags);

	अगर (conn->qp.sq.pc - conn->qp.sq.cc >= conn->qp.sq.size) अणु
		list_add_tail(&buf->list, &conn->qp.sq.backlog);
		जाओ out_unlock;
	पूर्ण

	mlx5_fpga_conn_post_send(conn, buf);

out_unlock:
	spin_unlock_irqrestore(&conn->qp.sq.lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_fpga_conn_post_recv_buf(काष्ठा mlx5_fpga_conn *conn)
अणु
	काष्ठा mlx5_fpga_dma_buf *buf;
	पूर्णांक err;

	buf = kzalloc(माप(*buf) + MLX5_FPGA_RECV_SIZE, 0);
	अगर (!buf)
		वापस -ENOMEM;

	buf->sg[0].data = (व्योम *)(buf + 1);
	buf->sg[0].size = MLX5_FPGA_RECV_SIZE;
	buf->dma_dir = DMA_FROM_DEVICE;

	err = mlx5_fpga_conn_post_recv(conn, buf);
	अगर (err)
		kमुक्त(buf);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_fpga_conn_create_mkey(काष्ठा mlx5_core_dev *mdev, u32 pdn,
				      काष्ठा mlx5_core_mkey *mkey)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	व्योम *mkc;
	u32 *in;
	पूर्णांक err;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, access_mode_1_0, MLX5_MKC_ACCESS_MODE_PA);
	MLX5_SET(mkc, mkc, lw, 1);
	MLX5_SET(mkc, mkc, lr, 1);

	MLX5_SET(mkc, mkc, pd, pdn);
	MLX5_SET(mkc, mkc, length64, 1);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);

	err = mlx5_core_create_mkey(mdev, mkey, in, inlen);

	kvमुक्त(in);
	वापस err;
पूर्ण

अटल व्योम mlx5_fpga_conn_rq_cqe(काष्ठा mlx5_fpga_conn *conn,
				  काष्ठा mlx5_cqe64 *cqe, u8 status)
अणु
	काष्ठा mlx5_fpga_dma_buf *buf;
	पूर्णांक ix, err;

	ix = be16_to_cpu(cqe->wqe_counter) & (conn->qp.rq.size - 1);
	buf = conn->qp.rq.bufs[ix];
	conn->qp.rq.bufs[ix] = शून्य;
	conn->qp.rq.cc++;

	अगर (unlikely(status && (status != MLX5_CQE_SYNDROME_WR_FLUSH_ERR)))
		mlx5_fpga_warn(conn->fdev, "RQ buf %p on FPGA QP %u completion status %d\n",
			       buf, conn->fpga_qpn, status);
	अन्यथा
		mlx5_fpga_dbg(conn->fdev, "RQ buf %p on FPGA QP %u completion status %d\n",
			      buf, conn->fpga_qpn, status);

	mlx5_fpga_conn_unmap_buf(conn, buf);

	अगर (unlikely(status || !conn->qp.active)) अणु
		conn->qp.active = false;
		kमुक्त(buf);
		वापस;
	पूर्ण

	buf->sg[0].size = be32_to_cpu(cqe->byte_cnt);
	mlx5_fpga_dbg(conn->fdev, "Message with %u bytes received successfully\n",
		      buf->sg[0].size);
	conn->recv_cb(conn->cb_arg, buf);

	buf->sg[0].size = MLX5_FPGA_RECV_SIZE;
	err = mlx5_fpga_conn_post_recv(conn, buf);
	अगर (unlikely(err)) अणु
		mlx5_fpga_warn(conn->fdev,
			       "Failed to re-post recv buf: %d\n", err);
		kमुक्त(buf);
	पूर्ण
पूर्ण

अटल व्योम mlx5_fpga_conn_sq_cqe(काष्ठा mlx5_fpga_conn *conn,
				  काष्ठा mlx5_cqe64 *cqe, u8 status)
अणु
	काष्ठा mlx5_fpga_dma_buf *buf, *nextbuf;
	अचिन्हित दीर्घ flags;
	पूर्णांक ix;

	spin_lock_irqsave(&conn->qp.sq.lock, flags);

	ix = be16_to_cpu(cqe->wqe_counter) & (conn->qp.sq.size - 1);
	buf = conn->qp.sq.bufs[ix];
	conn->qp.sq.bufs[ix] = शून्य;
	conn->qp.sq.cc++;

	/* Handle backlog still under the spinlock to ensure message post order */
	अगर (unlikely(!list_empty(&conn->qp.sq.backlog))) अणु
		अगर (likely(conn->qp.active)) अणु
			nextbuf = list_first_entry(&conn->qp.sq.backlog,
						   काष्ठा mlx5_fpga_dma_buf, list);
			list_del(&nextbuf->list);
			mlx5_fpga_conn_post_send(conn, nextbuf);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&conn->qp.sq.lock, flags);

	अगर (unlikely(status && (status != MLX5_CQE_SYNDROME_WR_FLUSH_ERR)))
		mlx5_fpga_warn(conn->fdev, "SQ buf %p on FPGA QP %u completion status %d\n",
			       buf, conn->fpga_qpn, status);
	अन्यथा
		mlx5_fpga_dbg(conn->fdev, "SQ buf %p on FPGA QP %u completion status %d\n",
			      buf, conn->fpga_qpn, status);

	mlx5_fpga_conn_unmap_buf(conn, buf);

	अगर (likely(buf->complete))
		buf->complete(conn, conn->fdev, buf, status);

	अगर (unlikely(status))
		conn->qp.active = false;
पूर्ण

अटल व्योम mlx5_fpga_conn_handle_cqe(काष्ठा mlx5_fpga_conn *conn,
				      काष्ठा mlx5_cqe64 *cqe)
अणु
	u8 opcode, status = 0;

	opcode = get_cqe_opcode(cqe);

	चयन (opcode) अणु
	हाल MLX5_CQE_REQ_ERR:
		status = ((काष्ठा mlx5_err_cqe *)cqe)->syndrome;
		fallthrough;
	हाल MLX5_CQE_REQ:
		mlx5_fpga_conn_sq_cqe(conn, cqe, status);
		अवरोध;

	हाल MLX5_CQE_RESP_ERR:
		status = ((काष्ठा mlx5_err_cqe *)cqe)->syndrome;
		fallthrough;
	हाल MLX5_CQE_RESP_SEND:
		mlx5_fpga_conn_rq_cqe(conn, cqe, status);
		अवरोध;
	शेष:
		mlx5_fpga_warn(conn->fdev, "Unexpected cqe opcode %u\n",
			       opcode);
	पूर्ण
पूर्ण

अटल व्योम mlx5_fpga_conn_arm_cq(काष्ठा mlx5_fpga_conn *conn)
अणु
	mlx5_cq_arm(&conn->cq.mcq, MLX5_CQ_DB_REQ_NOT,
		    conn->fdev->conn_res.uar->map, conn->cq.wq.cc);
पूर्ण

अटल अंतरभूत व्योम mlx5_fpga_conn_cqes(काष्ठा mlx5_fpga_conn *conn,
				       अचिन्हित पूर्णांक budget)
अणु
	काष्ठा mlx5_cqe64 *cqe;

	जबतक (budget) अणु
		cqe = mlx5_cqwq_get_cqe(&conn->cq.wq);
		अगर (!cqe)
			अवरोध;

		budget--;
		mlx5_cqwq_pop(&conn->cq.wq);
		mlx5_fpga_conn_handle_cqe(conn, cqe);
		mlx5_cqwq_update_db_record(&conn->cq.wq);
	पूर्ण
	अगर (!budget) अणु
		tasklet_schedule(&conn->cq.tasklet);
		वापस;
	पूर्ण

	mlx5_fpga_dbg(conn->fdev, "Re-arming CQ with cc# %u\n", conn->cq.wq.cc);
	/* ensure cq space is मुक्तd beक्रमe enabling more cqes */
	wmb();
	mlx5_fpga_conn_arm_cq(conn);
पूर्ण

अटल व्योम mlx5_fpga_conn_cq_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mlx5_fpga_conn *conn = from_tasklet(conn, t, cq.tasklet);

	अगर (unlikely(!conn->qp.active))
		वापस;
	mlx5_fpga_conn_cqes(conn, MLX5_FPGA_CQ_BUDGET);
पूर्ण

अटल व्योम mlx5_fpga_conn_cq_complete(काष्ठा mlx5_core_cq *mcq,
				       काष्ठा mlx5_eqe *eqe)
अणु
	काष्ठा mlx5_fpga_conn *conn;

	conn = container_of(mcq, काष्ठा mlx5_fpga_conn, cq.mcq);
	अगर (unlikely(!conn->qp.active))
		वापस;
	mlx5_fpga_conn_cqes(conn, MLX5_FPGA_CQ_BUDGET);
पूर्ण

अटल पूर्णांक mlx5_fpga_conn_create_cq(काष्ठा mlx5_fpga_conn *conn, पूर्णांक cq_size)
अणु
	काष्ठा mlx5_fpga_device *fdev = conn->fdev;
	काष्ठा mlx5_core_dev *mdev = fdev->mdev;
	u32 temp_cqc[MLX5_ST_SZ_DW(cqc)] = अणु0पूर्ण;
	u32 out[MLX5_ST_SZ_DW(create_cq_out)];
	काष्ठा mlx5_wq_param wqp;
	काष्ठा mlx5_cqe64 *cqe;
	पूर्णांक inlen, err, eqn;
	अचिन्हित पूर्णांक irqn;
	व्योम *cqc, *in;
	__be64 *pas;
	u32 i;

	cq_size = roundup_घात_of_two(cq_size);
	MLX5_SET(cqc, temp_cqc, log_cq_size, ilog2(cq_size));

	wqp.buf_numa_node = mdev->priv.numa_node;
	wqp.db_numa_node  = mdev->priv.numa_node;

	err = mlx5_cqwq_create(mdev, &wqp, temp_cqc, &conn->cq.wq,
			       &conn->cq.wq_ctrl);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < mlx5_cqwq_get_size(&conn->cq.wq); i++) अणु
		cqe = mlx5_cqwq_get_wqe(&conn->cq.wq, i);
		cqe->op_own = MLX5_CQE_INVALID << 4 | MLX5_CQE_OWNER_MASK;
	पूर्ण

	inlen = MLX5_ST_SZ_BYTES(create_cq_in) +
		माप(u64) * conn->cq.wq_ctrl.buf.npages;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_cqwq;
	पूर्ण

	err = mlx5_vector2eqn(mdev, smp_processor_id(), &eqn, &irqn);
	अगर (err) अणु
		kvमुक्त(in);
		जाओ err_cqwq;
	पूर्ण

	cqc = MLX5_ADDR_OF(create_cq_in, in, cq_context);
	MLX5_SET(cqc, cqc, log_cq_size, ilog2(cq_size));
	MLX5_SET(cqc, cqc, c_eqn, eqn);
	MLX5_SET(cqc, cqc, uar_page, fdev->conn_res.uar->index);
	MLX5_SET(cqc, cqc, log_page_size, conn->cq.wq_ctrl.buf.page_shअगरt -
			   MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET64(cqc, cqc, dbr_addr, conn->cq.wq_ctrl.db.dma);

	pas = (__be64 *)MLX5_ADDR_OF(create_cq_in, in, pas);
	mlx5_fill_page_frag_array(&conn->cq.wq_ctrl.buf, pas);

	err = mlx5_core_create_cq(mdev, &conn->cq.mcq, in, inlen, out, माप(out));
	kvमुक्त(in);

	अगर (err)
		जाओ err_cqwq;

	conn->cq.mcq.cqe_sz     = 64;
	conn->cq.mcq.set_ci_db  = conn->cq.wq_ctrl.db.db;
	conn->cq.mcq.arm_db     = conn->cq.wq_ctrl.db.db + 1;
	*conn->cq.mcq.set_ci_db = 0;
	*conn->cq.mcq.arm_db    = 0;
	conn->cq.mcq.vector     = 0;
	conn->cq.mcq.comp       = mlx5_fpga_conn_cq_complete;
	conn->cq.mcq.irqn       = irqn;
	conn->cq.mcq.uar        = fdev->conn_res.uar;
	tasklet_setup(&conn->cq.tasklet, mlx5_fpga_conn_cq_tasklet);

	mlx5_fpga_dbg(fdev, "Created CQ #0x%x\n", conn->cq.mcq.cqn);

	जाओ out;

err_cqwq:
	mlx5_wq_destroy(&conn->cq.wq_ctrl);
out:
	वापस err;
पूर्ण

अटल व्योम mlx5_fpga_conn_destroy_cq(काष्ठा mlx5_fpga_conn *conn)
अणु
	tasklet_disable(&conn->cq.tasklet);
	tasklet_समाप्त(&conn->cq.tasklet);
	mlx5_core_destroy_cq(conn->fdev->mdev, &conn->cq.mcq);
	mlx5_wq_destroy(&conn->cq.wq_ctrl);
पूर्ण

अटल पूर्णांक mlx5_fpga_conn_create_wq(काष्ठा mlx5_fpga_conn *conn, व्योम *qpc)
अणु
	काष्ठा mlx5_fpga_device *fdev = conn->fdev;
	काष्ठा mlx5_core_dev *mdev = fdev->mdev;
	काष्ठा mlx5_wq_param wqp;

	wqp.buf_numa_node = mdev->priv.numa_node;
	wqp.db_numa_node  = mdev->priv.numa_node;

	वापस mlx5_wq_qp_create(mdev, &wqp, qpc, &conn->qp.wq,
				 &conn->qp.wq_ctrl);
पूर्ण

अटल पूर्णांक mlx5_fpga_conn_create_qp(काष्ठा mlx5_fpga_conn *conn,
				    अचिन्हित पूर्णांक tx_size, अचिन्हित पूर्णांक rx_size)
अणु
	काष्ठा mlx5_fpga_device *fdev = conn->fdev;
	u32 out[MLX5_ST_SZ_DW(create_qp_out)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *mdev = fdev->mdev;
	u32 temp_qpc[MLX5_ST_SZ_DW(qpc)] = अणुपूर्ण;
	व्योम *in = शून्य, *qpc;
	पूर्णांक err, inlen;

	conn->qp.rq.pc = 0;
	conn->qp.rq.cc = 0;
	conn->qp.rq.size = roundup_घात_of_two(rx_size);
	conn->qp.sq.pc = 0;
	conn->qp.sq.cc = 0;
	conn->qp.sq.size = roundup_घात_of_two(tx_size);

	MLX5_SET(qpc, temp_qpc, log_rq_stride, ilog2(MLX5_SEND_WQE_DS) - 4);
	MLX5_SET(qpc, temp_qpc, log_rq_size, ilog2(conn->qp.rq.size));
	MLX5_SET(qpc, temp_qpc, log_sq_size, ilog2(conn->qp.sq.size));
	err = mlx5_fpga_conn_create_wq(conn, temp_qpc);
	अगर (err)
		जाओ out;

	conn->qp.rq.bufs = kvसुस्मृति(conn->qp.rq.size,
				    माप(conn->qp.rq.bufs[0]),
				    GFP_KERNEL);
	अगर (!conn->qp.rq.bufs) अणु
		err = -ENOMEM;
		जाओ err_wq;
	पूर्ण

	conn->qp.sq.bufs = kvसुस्मृति(conn->qp.sq.size,
				    माप(conn->qp.sq.bufs[0]),
				    GFP_KERNEL);
	अगर (!conn->qp.sq.bufs) अणु
		err = -ENOMEM;
		जाओ err_rq_bufs;
	पूर्ण

	inlen = MLX5_ST_SZ_BYTES(create_qp_in) +
		MLX5_FLD_SZ_BYTES(create_qp_in, pas[0]) *
		conn->qp.wq_ctrl.buf.npages;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_sq_bufs;
	पूर्ण

	qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);
	MLX5_SET(qpc, qpc, uar_page, fdev->conn_res.uar->index);
	MLX5_SET(qpc, qpc, log_page_size,
		 conn->qp.wq_ctrl.buf.page_shअगरt - MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET(qpc, qpc, fre, 1);
	MLX5_SET(qpc, qpc, rlky, 1);
	MLX5_SET(qpc, qpc, st, MLX5_QP_ST_RC);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
	MLX5_SET(qpc, qpc, pd, fdev->conn_res.pdn);
	MLX5_SET(qpc, qpc, log_rq_stride, ilog2(MLX5_SEND_WQE_DS) - 4);
	MLX5_SET(qpc, qpc, log_rq_size, ilog2(conn->qp.rq.size));
	MLX5_SET(qpc, qpc, rq_type, MLX5_NON_ZERO_RQ);
	MLX5_SET(qpc, qpc, log_sq_size, ilog2(conn->qp.sq.size));
	MLX5_SET(qpc, qpc, cqn_snd, conn->cq.mcq.cqn);
	MLX5_SET(qpc, qpc, cqn_rcv, conn->cq.mcq.cqn);
	MLX5_SET(qpc, qpc, ts_क्रमmat, mlx5_get_qp_शेष_ts(mdev));
	MLX5_SET64(qpc, qpc, dbr_addr, conn->qp.wq_ctrl.db.dma);
	अगर (MLX5_CAP_GEN(mdev, cqe_version) == 1)
		MLX5_SET(qpc, qpc, user_index, 0xFFFFFF);

	mlx5_fill_page_frag_array(&conn->qp.wq_ctrl.buf,
				  (__be64 *)MLX5_ADDR_OF(create_qp_in, in, pas));

	MLX5_SET(create_qp_in, in, opcode, MLX5_CMD_OP_CREATE_QP);
	err = mlx5_cmd_exec(mdev, in, inlen, out, माप(out));
	अगर (err)
		जाओ err_sq_bufs;

	conn->qp.qpn = MLX5_GET(create_qp_out, out, qpn);
	mlx5_fpga_dbg(fdev, "Created QP #0x%x\n", conn->qp.qpn);

	जाओ out;

err_sq_bufs:
	kvमुक्त(conn->qp.sq.bufs);
err_rq_bufs:
	kvमुक्त(conn->qp.rq.bufs);
err_wq:
	mlx5_wq_destroy(&conn->qp.wq_ctrl);
out:
	kvमुक्त(in);
	वापस err;
पूर्ण

अटल व्योम mlx5_fpga_conn_मुक्त_recv_bufs(काष्ठा mlx5_fpga_conn *conn)
अणु
	पूर्णांक ix;

	क्रम (ix = 0; ix < conn->qp.rq.size; ix++) अणु
		अगर (!conn->qp.rq.bufs[ix])
			जारी;
		mlx5_fpga_conn_unmap_buf(conn, conn->qp.rq.bufs[ix]);
		kमुक्त(conn->qp.rq.bufs[ix]);
		conn->qp.rq.bufs[ix] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम mlx5_fpga_conn_flush_send_bufs(काष्ठा mlx5_fpga_conn *conn)
अणु
	काष्ठा mlx5_fpga_dma_buf *buf, *temp;
	पूर्णांक ix;

	क्रम (ix = 0; ix < conn->qp.sq.size; ix++) अणु
		buf = conn->qp.sq.bufs[ix];
		अगर (!buf)
			जारी;
		conn->qp.sq.bufs[ix] = शून्य;
		mlx5_fpga_conn_unmap_buf(conn, buf);
		अगर (!buf->complete)
			जारी;
		buf->complete(conn, conn->fdev, buf, MLX5_CQE_SYNDROME_WR_FLUSH_ERR);
	पूर्ण
	list_क्रम_each_entry_safe(buf, temp, &conn->qp.sq.backlog, list) अणु
		mlx5_fpga_conn_unmap_buf(conn, buf);
		अगर (!buf->complete)
			जारी;
		buf->complete(conn, conn->fdev, buf, MLX5_CQE_SYNDROME_WR_FLUSH_ERR);
	पूर्ण
पूर्ण

अटल व्योम mlx5_fpga_conn_destroy_qp(काष्ठा mlx5_fpga_conn *conn)
अणु
	काष्ठा mlx5_core_dev *dev = conn->fdev->mdev;
	u32 in[MLX5_ST_SZ_DW(destroy_qp_in)] = अणुपूर्ण;

	MLX5_SET(destroy_qp_in, in, opcode, MLX5_CMD_OP_DESTROY_QP);
	MLX5_SET(destroy_qp_in, in, qpn, conn->qp.qpn);
	mlx5_cmd_exec_in(dev, destroy_qp, in);

	mlx5_fpga_conn_मुक्त_recv_bufs(conn);
	mlx5_fpga_conn_flush_send_bufs(conn);
	kvमुक्त(conn->qp.sq.bufs);
	kvमुक्त(conn->qp.rq.bufs);
	mlx5_wq_destroy(&conn->qp.wq_ctrl);
पूर्ण

अटल पूर्णांक mlx5_fpga_conn_reset_qp(काष्ठा mlx5_fpga_conn *conn)
अणु
	काष्ठा mlx5_core_dev *mdev = conn->fdev->mdev;
	u32 in[MLX5_ST_SZ_DW(qp_2rst_in)] = अणुपूर्ण;

	mlx5_fpga_dbg(conn->fdev, "Modifying QP %u to RST\n", conn->qp.qpn);

	MLX5_SET(qp_2rst_in, in, opcode, MLX5_CMD_OP_2RST_QP);
	MLX5_SET(qp_2rst_in, in, qpn, conn->qp.qpn);

	वापस mlx5_cmd_exec_in(mdev, qp_2rst, in);
पूर्ण

अटल पूर्णांक mlx5_fpga_conn_init_qp(काष्ठा mlx5_fpga_conn *conn)
अणु
	u32 in[MLX5_ST_SZ_DW(rst2init_qp_in)] = अणुपूर्ण;
	काष्ठा mlx5_fpga_device *fdev = conn->fdev;
	काष्ठा mlx5_core_dev *mdev = fdev->mdev;
	u32 *qpc;

	mlx5_fpga_dbg(conn->fdev, "Modifying QP %u to INIT\n", conn->qp.qpn);

	qpc = MLX5_ADDR_OF(rst2init_qp_in, in, qpc);

	MLX5_SET(qpc, qpc, st, MLX5_QP_ST_RC);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
	MLX5_SET(qpc, qpc, primary_address_path.pkey_index, MLX5_FPGA_PKEY_INDEX);
	MLX5_SET(qpc, qpc, primary_address_path.vhca_port_num, MLX5_FPGA_PORT_NUM);
	MLX5_SET(qpc, qpc, pd, conn->fdev->conn_res.pdn);
	MLX5_SET(qpc, qpc, cqn_snd, conn->cq.mcq.cqn);
	MLX5_SET(qpc, qpc, cqn_rcv, conn->cq.mcq.cqn);
	MLX5_SET64(qpc, qpc, dbr_addr, conn->qp.wq_ctrl.db.dma);

	MLX5_SET(rst2init_qp_in, in, opcode, MLX5_CMD_OP_RST2INIT_QP);
	MLX5_SET(rst2init_qp_in, in, qpn, conn->qp.qpn);

	वापस mlx5_cmd_exec_in(mdev, rst2init_qp, in);
पूर्ण

अटल पूर्णांक mlx5_fpga_conn_rtr_qp(काष्ठा mlx5_fpga_conn *conn)
अणु
	u32 in[MLX5_ST_SZ_DW(init2rtr_qp_in)] = अणुपूर्ण;
	काष्ठा mlx5_fpga_device *fdev = conn->fdev;
	काष्ठा mlx5_core_dev *mdev = fdev->mdev;
	u32 *qpc;

	mlx5_fpga_dbg(conn->fdev, "QP RTR\n");

	qpc = MLX5_ADDR_OF(init2rtr_qp_in, in, qpc);

	MLX5_SET(qpc, qpc, mtu, MLX5_QPC_MTU_1K_BYTES);
	MLX5_SET(qpc, qpc, log_msg_max, (u8)MLX5_CAP_GEN(mdev, log_max_msg));
	MLX5_SET(qpc, qpc, remote_qpn, conn->fpga_qpn);
	MLX5_SET(qpc, qpc, next_rcv_psn,
		 MLX5_GET(fpga_qpc, conn->fpga_qpc, next_send_psn));
	MLX5_SET(qpc, qpc, primary_address_path.pkey_index, MLX5_FPGA_PKEY_INDEX);
	MLX5_SET(qpc, qpc, primary_address_path.vhca_port_num, MLX5_FPGA_PORT_NUM);
	ether_addr_copy(MLX5_ADDR_OF(qpc, qpc, primary_address_path.rmac_47_32),
			MLX5_ADDR_OF(fpga_qpc, conn->fpga_qpc, fpga_mac_47_32));
	MLX5_SET(qpc, qpc, primary_address_path.udp_sport,
		 MLX5_CAP_ROCE(mdev, r_roce_min_src_udp_port));
	MLX5_SET(qpc, qpc, primary_address_path.src_addr_index,
		 conn->qp.sgid_index);
	MLX5_SET(qpc, qpc, primary_address_path.hop_limit, 0);
	स_नकल(MLX5_ADDR_OF(qpc, qpc, primary_address_path.rgid_rip),
	       MLX5_ADDR_OF(fpga_qpc, conn->fpga_qpc, fpga_ip),
	       MLX5_FLD_SZ_BYTES(qpc, primary_address_path.rgid_rip));

	MLX5_SET(init2rtr_qp_in, in, opcode, MLX5_CMD_OP_INIT2RTR_QP);
	MLX5_SET(init2rtr_qp_in, in, qpn, conn->qp.qpn);

	वापस mlx5_cmd_exec_in(mdev, init2rtr_qp, in);
पूर्ण

अटल पूर्णांक mlx5_fpga_conn_rts_qp(काष्ठा mlx5_fpga_conn *conn)
अणु
	काष्ठा mlx5_fpga_device *fdev = conn->fdev;
	u32 in[MLX5_ST_SZ_DW(rtr2rts_qp_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *mdev = fdev->mdev;
	u32 *qpc;

	mlx5_fpga_dbg(conn->fdev, "QP RTS\n");

	qpc = MLX5_ADDR_OF(rtr2rts_qp_in, in, qpc);

	MLX5_SET(qpc, qpc, log_ack_req_freq, 8);
	MLX5_SET(qpc, qpc, min_rnr_nak, 0x12);
	MLX5_SET(qpc, qpc, primary_address_path.ack_समयout, 0x12); /* ~1.07s */
	MLX5_SET(qpc, qpc, next_send_psn,
		 MLX5_GET(fpga_qpc, conn->fpga_qpc, next_rcv_psn));
	MLX5_SET(qpc, qpc, retry_count, 7);
	MLX5_SET(qpc, qpc, rnr_retry, 7); /* Infinite retry अगर RNR NACK */

	MLX5_SET(rtr2rts_qp_in, in, opcode, MLX5_CMD_OP_RTR2RTS_QP);
	MLX5_SET(rtr2rts_qp_in, in, qpn, conn->qp.qpn);
	MLX5_SET(rtr2rts_qp_in, in, opt_param_mask, MLX5_QP_OPTPAR_RNR_TIMEOUT);

	वापस mlx5_cmd_exec_in(mdev, rtr2rts_qp, in);
पूर्ण

अटल पूर्णांक mlx5_fpga_conn_connect(काष्ठा mlx5_fpga_conn *conn)
अणु
	काष्ठा mlx5_fpga_device *fdev = conn->fdev;
	पूर्णांक err;

	MLX5_SET(fpga_qpc, conn->fpga_qpc, state, MLX5_FPGA_QPC_STATE_ACTIVE);
	err = mlx5_fpga_modअगरy_qp(conn->fdev->mdev, conn->fpga_qpn,
				  MLX5_FPGA_QPC_STATE, &conn->fpga_qpc);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to activate FPGA RC QP: %d\n", err);
		जाओ out;
	पूर्ण

	err = mlx5_fpga_conn_reset_qp(conn);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to change QP state to reset\n");
		जाओ err_fpga_qp;
	पूर्ण

	err = mlx5_fpga_conn_init_qp(conn);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to modify QP from RESET to INIT\n");
		जाओ err_fpga_qp;
	पूर्ण
	conn->qp.active = true;

	जबतक (!mlx5_fpga_conn_post_recv_buf(conn))
		;

	err = mlx5_fpga_conn_rtr_qp(conn);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to change QP state from INIT to RTR\n");
		जाओ err_recv_bufs;
	पूर्ण

	err = mlx5_fpga_conn_rts_qp(conn);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to change QP state from RTR to RTS\n");
		जाओ err_recv_bufs;
	पूर्ण
	जाओ out;

err_recv_bufs:
	mlx5_fpga_conn_मुक्त_recv_bufs(conn);
err_fpga_qp:
	MLX5_SET(fpga_qpc, conn->fpga_qpc, state, MLX5_FPGA_QPC_STATE_INIT);
	अगर (mlx5_fpga_modअगरy_qp(conn->fdev->mdev, conn->fpga_qpn,
				MLX5_FPGA_QPC_STATE, &conn->fpga_qpc))
		mlx5_fpga_err(fdev, "Failed to revert FPGA QP to INIT\n");
out:
	वापस err;
पूर्ण

काष्ठा mlx5_fpga_conn *mlx5_fpga_conn_create(काष्ठा mlx5_fpga_device *fdev,
					     काष्ठा mlx5_fpga_conn_attr *attr,
					     क्रमागत mlx5_अगरc_fpga_qp_type qp_type)
अणु
	काष्ठा mlx5_fpga_conn *ret, *conn;
	u8 *remote_mac, *remote_ip;
	पूर्णांक err;

	अगर (!attr->recv_cb)
		वापस ERR_PTR(-EINVAL);

	conn = kzalloc(माप(*conn), GFP_KERNEL);
	अगर (!conn)
		वापस ERR_PTR(-ENOMEM);

	conn->fdev = fdev;
	INIT_LIST_HEAD(&conn->qp.sq.backlog);

	spin_lock_init(&conn->qp.sq.lock);

	conn->recv_cb = attr->recv_cb;
	conn->cb_arg = attr->cb_arg;

	remote_mac = MLX5_ADDR_OF(fpga_qpc, conn->fpga_qpc, remote_mac_47_32);
	err = mlx5_query_mac_address(fdev->mdev, remote_mac);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to query local MAC: %d\n", err);
		ret = ERR_PTR(err);
		जाओ err;
	पूर्ण

	/* Build Modअगरied EUI-64 IPv6 address from the MAC address */
	remote_ip = MLX5_ADDR_OF(fpga_qpc, conn->fpga_qpc, remote_ip);
	remote_ip[0] = 0xfe;
	remote_ip[1] = 0x80;
	addrconf_addr_eui48(&remote_ip[8], remote_mac);

	err = mlx5_core_reserved_gid_alloc(fdev->mdev, &conn->qp.sgid_index);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to allocate SGID: %d\n", err);
		ret = ERR_PTR(err);
		जाओ err;
	पूर्ण

	err = mlx5_core_roce_gid_set(fdev->mdev, conn->qp.sgid_index,
				     MLX5_ROCE_VERSION_2,
				     MLX5_ROCE_L3_TYPE_IPV6,
				     remote_ip, remote_mac, true, 0,
				     MLX5_FPGA_PORT_NUM);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to set SGID: %d\n", err);
		ret = ERR_PTR(err);
		जाओ err_rsvd_gid;
	पूर्ण
	mlx5_fpga_dbg(fdev, "Reserved SGID index %u\n", conn->qp.sgid_index);

	/* Allow क्रम one cqe per rx/tx wqe, plus one cqe क्रम the next wqe,
	 * created during processing of the cqe
	 */
	err = mlx5_fpga_conn_create_cq(conn,
				       (attr->tx_size + attr->rx_size) * 2);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to create CQ: %d\n", err);
		ret = ERR_PTR(err);
		जाओ err_gid;
	पूर्ण

	mlx5_fpga_conn_arm_cq(conn);

	err = mlx5_fpga_conn_create_qp(conn, attr->tx_size, attr->rx_size);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to create QP: %d\n", err);
		ret = ERR_PTR(err);
		जाओ err_cq;
	पूर्ण

	MLX5_SET(fpga_qpc, conn->fpga_qpc, state, MLX5_FPGA_QPC_STATE_INIT);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, qp_type, qp_type);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, st, MLX5_FPGA_QPC_ST_RC);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, ether_type, ETH_P_8021Q);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, vid, 0);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, next_rcv_psn, 1);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, next_send_psn, 0);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, pkey, MLX5_FPGA_PKEY);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, remote_qpn, conn->qp.qpn);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, rnr_retry, 7);
	MLX5_SET(fpga_qpc, conn->fpga_qpc, retry_count, 7);

	err = mlx5_fpga_create_qp(fdev->mdev, &conn->fpga_qpc,
				  &conn->fpga_qpn);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to create FPGA RC QP: %d\n", err);
		ret = ERR_PTR(err);
		जाओ err_qp;
	पूर्ण

	err = mlx5_fpga_conn_connect(conn);
	अगर (err) अणु
		ret = ERR_PTR(err);
		जाओ err_conn;
	पूर्ण

	mlx5_fpga_dbg(fdev, "FPGA QPN is %u\n", conn->fpga_qpn);
	ret = conn;
	जाओ out;

err_conn:
	mlx5_fpga_destroy_qp(conn->fdev->mdev, conn->fpga_qpn);
err_qp:
	mlx5_fpga_conn_destroy_qp(conn);
err_cq:
	mlx5_fpga_conn_destroy_cq(conn);
err_gid:
	mlx5_core_roce_gid_set(fdev->mdev, conn->qp.sgid_index, 0, 0, शून्य,
			       शून्य, false, 0, MLX5_FPGA_PORT_NUM);
err_rsvd_gid:
	mlx5_core_reserved_gid_मुक्त(fdev->mdev, conn->qp.sgid_index);
err:
	kमुक्त(conn);
out:
	वापस ret;
पूर्ण

व्योम mlx5_fpga_conn_destroy(काष्ठा mlx5_fpga_conn *conn)
अणु
	conn->qp.active = false;
	tasklet_disable(&conn->cq.tasklet);
	synchronize_irq(conn->cq.mcq.irqn);

	mlx5_fpga_destroy_qp(conn->fdev->mdev, conn->fpga_qpn);
	mlx5_fpga_conn_destroy_qp(conn);
	mlx5_fpga_conn_destroy_cq(conn);

	mlx5_core_roce_gid_set(conn->fdev->mdev, conn->qp.sgid_index, 0, 0,
			       शून्य, शून्य, false, 0, MLX5_FPGA_PORT_NUM);
	mlx5_core_reserved_gid_मुक्त(conn->fdev->mdev, conn->qp.sgid_index);
	kमुक्त(conn);
पूर्ण

पूर्णांक mlx5_fpga_conn_device_init(काष्ठा mlx5_fpga_device *fdev)
अणु
	पूर्णांक err;

	err = mlx5_nic_vport_enable_roce(fdev->mdev);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to enable RoCE: %d\n", err);
		जाओ out;
	पूर्ण

	fdev->conn_res.uar = mlx5_get_uars_page(fdev->mdev);
	अगर (IS_ERR(fdev->conn_res.uar)) अणु
		err = PTR_ERR(fdev->conn_res.uar);
		mlx5_fpga_err(fdev, "get_uars_page failed, %d\n", err);
		जाओ err_roce;
	पूर्ण
	mlx5_fpga_dbg(fdev, "Allocated UAR index %u\n",
		      fdev->conn_res.uar->index);

	err = mlx5_core_alloc_pd(fdev->mdev, &fdev->conn_res.pdn);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "alloc pd failed, %d\n", err);
		जाओ err_uar;
	पूर्ण
	mlx5_fpga_dbg(fdev, "Allocated PD %u\n", fdev->conn_res.pdn);

	err = mlx5_fpga_conn_create_mkey(fdev->mdev, fdev->conn_res.pdn,
					 &fdev->conn_res.mkey);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "create mkey failed, %d\n", err);
		जाओ err_dealloc_pd;
	पूर्ण
	mlx5_fpga_dbg(fdev, "Created mkey 0x%x\n", fdev->conn_res.mkey.key);

	वापस 0;

err_dealloc_pd:
	mlx5_core_dealloc_pd(fdev->mdev, fdev->conn_res.pdn);
err_uar:
	mlx5_put_uars_page(fdev->mdev, fdev->conn_res.uar);
err_roce:
	mlx5_nic_vport_disable_roce(fdev->mdev);
out:
	वापस err;
पूर्ण

व्योम mlx5_fpga_conn_device_cleanup(काष्ठा mlx5_fpga_device *fdev)
अणु
	mlx5_core_destroy_mkey(fdev->mdev, &fdev->conn_res.mkey);
	mlx5_core_dealloc_pd(fdev->mdev, fdev->conn_res.pdn);
	mlx5_put_uars_page(fdev->mdev, fdev->conn_res.uar);
	mlx5_nic_vport_disable_roce(fdev->mdev);
पूर्ण
