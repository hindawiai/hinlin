<शैली गुरु>
/*
 * Copyright (c) 2004, 2005, 2006 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2013-2014 Mellanox Technologies. All rights reserved.
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
 *	- Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *	- Redistributions in binary क्रमm must reproduce the above
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
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/scatterlist.h>

#समावेश "iscsi_iser.h"

व्योम iser_reg_comp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	iser_err_comp(wc, "memreg");
पूर्ण

अटल काष्ठा iser_fr_desc *
iser_reg_desc_get_fr(काष्ठा ib_conn *ib_conn)
अणु
	काष्ठा iser_fr_pool *fr_pool = &ib_conn->fr_pool;
	काष्ठा iser_fr_desc *desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fr_pool->lock, flags);
	desc = list_first_entry(&fr_pool->list,
				काष्ठा iser_fr_desc, list);
	list_del(&desc->list);
	spin_unlock_irqrestore(&fr_pool->lock, flags);

	वापस desc;
पूर्ण

अटल व्योम
iser_reg_desc_put_fr(काष्ठा ib_conn *ib_conn,
		     काष्ठा iser_fr_desc *desc)
अणु
	काष्ठा iser_fr_pool *fr_pool = &ib_conn->fr_pool;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fr_pool->lock, flags);
	list_add(&desc->list, &fr_pool->list);
	spin_unlock_irqrestore(&fr_pool->lock, flags);
पूर्ण

पूर्णांक iser_dma_map_task_data(काष्ठा iscsi_iser_task *iser_task,
			    काष्ठा iser_data_buf *data,
			    क्रमागत iser_data_dir iser_dir,
			    क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा ib_device *dev;

	iser_task->dir[iser_dir] = 1;
	dev = iser_task->iser_conn->ib_conn.device->ib_device;

	data->dma_nents = ib_dma_map_sg(dev, data->sg, data->size, dma_dir);
	अगर (unlikely(data->dma_nents == 0)) अणु
		iser_err("dma_map_sg failed!!!\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

व्योम iser_dma_unmap_task_data(काष्ठा iscsi_iser_task *iser_task,
			      काष्ठा iser_data_buf *data,
			      क्रमागत dma_data_direction dir)
अणु
	काष्ठा ib_device *dev;

	dev = iser_task->iser_conn->ib_conn.device->ib_device;
	ib_dma_unmap_sg(dev, data->sg, data->size, dir);
पूर्ण

अटल पूर्णांक
iser_reg_dma(काष्ठा iser_device *device, काष्ठा iser_data_buf *mem,
	     काष्ठा iser_mem_reg *reg)
अणु
	काष्ठा scatterlist *sg = mem->sg;

	reg->sge.lkey = device->pd->local_dma_lkey;
	/*
	 * FIXME: rework the registration code path to dअगरferentiate
	 * rkey/lkey use हालs
	 */

	अगर (device->pd->flags & IB_PD_UNSAFE_GLOBAL_RKEY)
		reg->rkey = device->pd->unsafe_global_rkey;
	अन्यथा
		reg->rkey = 0;
	reg->sge.addr = sg_dma_address(&sg[0]);
	reg->sge.length = sg_dma_len(&sg[0]);

	iser_dbg("Single DMA entry: lkey=0x%x, rkey=0x%x, addr=0x%llx,"
		 " length=0x%x\n", reg->sge.lkey, reg->rkey,
		 reg->sge.addr, reg->sge.length);

	वापस 0;
पूर्ण

व्योम iser_unreg_mem_fastreg(काष्ठा iscsi_iser_task *iser_task,
			    क्रमागत iser_data_dir cmd_dir)
अणु
	काष्ठा iser_mem_reg *reg = &iser_task->rdma_reg[cmd_dir];
	काष्ठा iser_fr_desc *desc;
	काष्ठा ib_mr_status mr_status;

	desc = reg->mem_h;
	अगर (!desc)
		वापस;

	/*
	 * The signature MR cannot be invalidated and reused without checking.
	 * libiscsi calls the check_protection transport handler only अगर
	 * SCSI-Response is received. And the signature MR is not checked अगर
	 * the task is completed क्रम some other reason like a समयout or error
	 * handling. That's why we must check the signature MR here beक्रमe
	 * putting it to the मुक्त pool.
	 */
	अगर (unlikely(desc->sig_रक्षित)) अणु
		desc->sig_रक्षित = false;
		ib_check_mr_status(desc->rsc.sig_mr, IB_MR_CHECK_SIG_STATUS,
				   &mr_status);
	पूर्ण
	iser_reg_desc_put_fr(&iser_task->iser_conn->ib_conn, reg->mem_h);
	reg->mem_h = शून्य;
पूर्ण

अटल व्योम
iser_set_dअगर_करोमुख्य(काष्ठा scsi_cmnd *sc, काष्ठा ib_sig_करोमुख्य *करोमुख्य)
अणु
	करोमुख्य->sig_type = IB_SIG_TYPE_T10_DIF;
	करोमुख्य->sig.dअगर.pi_पूर्णांकerval = scsi_prot_पूर्णांकerval(sc);
	करोमुख्य->sig.dअगर.ref_tag = t10_pi_ref_tag(sc->request);
	/*
	 * At the moment we hard code those, but in the future
	 * we will take them from sc.
	 */
	करोमुख्य->sig.dअगर.apptag_check_mask = 0xffff;
	करोमुख्य->sig.dअगर.app_escape = true;
	करोमुख्य->sig.dअगर.ref_escape = true;
	अगर (sc->prot_flags & SCSI_PROT_REF_INCREMENT)
		करोमुख्य->sig.dअगर.ref_remap = true;
पूर्ण

अटल पूर्णांक
iser_set_sig_attrs(काष्ठा scsi_cmnd *sc, काष्ठा ib_sig_attrs *sig_attrs)
अणु
	चयन (scsi_get_prot_op(sc)) अणु
	हाल SCSI_PROT_WRITE_INSERT:
	हाल SCSI_PROT_READ_STRIP:
		sig_attrs->mem.sig_type = IB_SIG_TYPE_NONE;
		iser_set_dअगर_करोमुख्य(sc, &sig_attrs->wire);
		sig_attrs->wire.sig.dअगर.bg_type = IB_T10DIF_CRC;
		अवरोध;
	हाल SCSI_PROT_READ_INSERT:
	हाल SCSI_PROT_WRITE_STRIP:
		sig_attrs->wire.sig_type = IB_SIG_TYPE_NONE;
		iser_set_dअगर_करोमुख्य(sc, &sig_attrs->mem);
		sig_attrs->mem.sig.dअगर.bg_type = sc->prot_flags & SCSI_PROT_IP_CHECKSUM ?
						IB_T10DIF_CSUM : IB_T10DIF_CRC;
		अवरोध;
	हाल SCSI_PROT_READ_PASS:
	हाल SCSI_PROT_WRITE_PASS:
		iser_set_dअगर_करोमुख्य(sc, &sig_attrs->wire);
		sig_attrs->wire.sig.dअगर.bg_type = IB_T10DIF_CRC;
		iser_set_dअगर_करोमुख्य(sc, &sig_attrs->mem);
		sig_attrs->mem.sig.dअगर.bg_type = sc->prot_flags & SCSI_PROT_IP_CHECKSUM ?
						IB_T10DIF_CSUM : IB_T10DIF_CRC;
		अवरोध;
	शेष:
		iser_err("Unsupported PI operation %d\n",
			 scsi_get_prot_op(sc));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
iser_set_prot_checks(काष्ठा scsi_cmnd *sc, u8 *mask)
अणु
	*mask = 0;
	अगर (sc->prot_flags & SCSI_PROT_REF_CHECK)
		*mask |= IB_SIG_CHECK_REFTAG;
	अगर (sc->prot_flags & SCSI_PROT_GUARD_CHECK)
		*mask |= IB_SIG_CHECK_GUARD;
पूर्ण

अटल अंतरभूत व्योम
iser_inv_rkey(काष्ठा ib_send_wr *inv_wr,
	      काष्ठा ib_mr *mr,
	      काष्ठा ib_cqe *cqe,
	      काष्ठा ib_send_wr *next_wr)
अणु
	inv_wr->opcode = IB_WR_LOCAL_INV;
	inv_wr->wr_cqe = cqe;
	inv_wr->ex.invalidate_rkey = mr->rkey;
	inv_wr->send_flags = 0;
	inv_wr->num_sge = 0;
	inv_wr->next = next_wr;
पूर्ण

अटल पूर्णांक
iser_reg_sig_mr(काष्ठा iscsi_iser_task *iser_task,
		काष्ठा iser_data_buf *mem,
		काष्ठा iser_data_buf *sig_mem,
		काष्ठा iser_reg_resources *rsc,
		काष्ठा iser_mem_reg *sig_reg)
अणु
	काष्ठा iser_tx_desc *tx_desc = &iser_task->desc;
	काष्ठा ib_cqe *cqe = &iser_task->iser_conn->ib_conn.reg_cqe;
	काष्ठा ib_mr *mr = rsc->sig_mr;
	काष्ठा ib_sig_attrs *sig_attrs = mr->sig_attrs;
	काष्ठा ib_reg_wr *wr = &tx_desc->reg_wr;
	पूर्णांक ret;

	स_रखो(sig_attrs, 0, माप(*sig_attrs));
	ret = iser_set_sig_attrs(iser_task->sc, sig_attrs);
	अगर (ret)
		जाओ err;

	iser_set_prot_checks(iser_task->sc, &sig_attrs->check_mask);

	अगर (rsc->mr_valid)
		iser_inv_rkey(&tx_desc->inv_wr, mr, cqe, &wr->wr);

	ib_update_fast_reg_key(mr, ib_inc_rkey(mr->rkey));

	ret = ib_map_mr_sg_pi(mr, mem->sg, mem->dma_nents, शून्य,
			      sig_mem->sg, sig_mem->dma_nents, शून्य, SZ_4K);
	अगर (unlikely(ret)) अणु
		iser_err("failed to map PI sg (%d)\n",
			 mem->dma_nents + sig_mem->dma_nents);
		जाओ err;
	पूर्ण

	स_रखो(wr, 0, माप(*wr));
	wr->wr.next = &tx_desc->send_wr;
	wr->wr.opcode = IB_WR_REG_MR_INTEGRITY;
	wr->wr.wr_cqe = cqe;
	wr->wr.num_sge = 0;
	wr->wr.send_flags = 0;
	wr->mr = mr;
	wr->key = mr->rkey;
	wr->access = IB_ACCESS_LOCAL_WRITE |
		     IB_ACCESS_REMOTE_READ |
		     IB_ACCESS_REMOTE_WRITE;
	rsc->mr_valid = 1;

	sig_reg->sge.lkey = mr->lkey;
	sig_reg->rkey = mr->rkey;
	sig_reg->sge.addr = mr->iova;
	sig_reg->sge.length = mr->length;

	iser_dbg("lkey=0x%x rkey=0x%x addr=0x%llx length=%u\n",
		 sig_reg->sge.lkey, sig_reg->rkey, sig_reg->sge.addr,
		 sig_reg->sge.length);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक iser_fast_reg_mr(काष्ठा iscsi_iser_task *iser_task,
			    काष्ठा iser_data_buf *mem,
			    काष्ठा iser_reg_resources *rsc,
			    काष्ठा iser_mem_reg *reg)
अणु
	काष्ठा iser_tx_desc *tx_desc = &iser_task->desc;
	काष्ठा ib_cqe *cqe = &iser_task->iser_conn->ib_conn.reg_cqe;
	काष्ठा ib_mr *mr = rsc->mr;
	काष्ठा ib_reg_wr *wr = &tx_desc->reg_wr;
	पूर्णांक n;

	अगर (rsc->mr_valid)
		iser_inv_rkey(&tx_desc->inv_wr, mr, cqe, &wr->wr);

	ib_update_fast_reg_key(mr, ib_inc_rkey(mr->rkey));

	n = ib_map_mr_sg(mr, mem->sg, mem->dma_nents, शून्य, SZ_4K);
	अगर (unlikely(n != mem->dma_nents)) अणु
		iser_err("failed to map sg (%d/%d)\n",
			 n, mem->dma_nents);
		वापस n < 0 ? n : -EINVAL;
	पूर्ण

	wr->wr.next = &tx_desc->send_wr;
	wr->wr.opcode = IB_WR_REG_MR;
	wr->wr.wr_cqe = cqe;
	wr->wr.send_flags = 0;
	wr->wr.num_sge = 0;
	wr->mr = mr;
	wr->key = mr->rkey;
	wr->access = IB_ACCESS_LOCAL_WRITE  |
		     IB_ACCESS_REMOTE_WRITE |
		     IB_ACCESS_REMOTE_READ;

	rsc->mr_valid = 1;

	reg->sge.lkey = mr->lkey;
	reg->rkey = mr->rkey;
	reg->sge.addr = mr->iova;
	reg->sge.length = mr->length;

	iser_dbg("lkey=0x%x rkey=0x%x addr=0x%llx length=0x%x\n",
		 reg->sge.lkey, reg->rkey, reg->sge.addr, reg->sge.length);

	वापस 0;
पूर्ण

अटल पूर्णांक
iser_reg_data_sg(काष्ठा iscsi_iser_task *task,
		 काष्ठा iser_data_buf *mem,
		 काष्ठा iser_fr_desc *desc,
		 bool use_dma_key,
		 काष्ठा iser_mem_reg *reg)
अणु
	काष्ठा iser_device *device = task->iser_conn->ib_conn.device;

	अगर (use_dma_key)
		वापस iser_reg_dma(device, mem, reg);

	वापस iser_fast_reg_mr(task, mem, &desc->rsc, reg);
पूर्ण

पूर्णांक iser_reg_mem_fastreg(काष्ठा iscsi_iser_task *task,
			 क्रमागत iser_data_dir dir,
			 bool all_imm)
अणु
	काष्ठा ib_conn *ib_conn = &task->iser_conn->ib_conn;
	काष्ठा iser_data_buf *mem = &task->data[dir];
	काष्ठा iser_mem_reg *reg = &task->rdma_reg[dir];
	काष्ठा iser_fr_desc *desc = शून्य;
	bool use_dma_key;
	पूर्णांक err;

	use_dma_key = mem->dma_nents == 1 && (all_imm || !iser_always_reg) &&
		      scsi_get_prot_op(task->sc) == SCSI_PROT_NORMAL;

	अगर (!use_dma_key) अणु
		desc = iser_reg_desc_get_fr(ib_conn);
		reg->mem_h = desc;
	पूर्ण

	अगर (scsi_get_prot_op(task->sc) == SCSI_PROT_NORMAL) अणु
		err = iser_reg_data_sg(task, mem, desc, use_dma_key, reg);
		अगर (unlikely(err))
			जाओ err_reg;
	पूर्ण अन्यथा अणु
		err = iser_reg_sig_mr(task, mem, &task->prot[dir],
				      &desc->rsc, reg);
		अगर (unlikely(err))
			जाओ err_reg;

		desc->sig_रक्षित = true;
	पूर्ण

	वापस 0;

err_reg:
	अगर (desc)
		iser_reg_desc_put_fr(ib_conn, desc);

	वापस err;
पूर्ण
