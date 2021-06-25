<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
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

#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/page.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport_fc.h>

#समावेश "csio_hw.h"
#समावेश "csio_lnode.h"
#समावेश "csio_rnode.h"
#समावेश "csio_scsi.h"
#समावेश "csio_init.h"

पूर्णांक csio_scsi_eqsize = 65536;
पूर्णांक csio_scsi_iqlen = 128;
पूर्णांक csio_scsi_ioreqs = 2048;
uपूर्णांक32_t csio_max_scan_पंचांगo;
uपूर्णांक32_t csio_delta_scan_पंचांगo = 5;
पूर्णांक csio_lun_qdepth = 32;

अटल पूर्णांक csio_ddp_descs = 128;

अटल पूर्णांक csio_करो_abrt_cls(काष्ठा csio_hw *,
				      काष्ठा csio_ioreq *, bool);

अटल व्योम csio_scsis_uninit(काष्ठा csio_ioreq *, क्रमागत csio_scsi_ev);
अटल व्योम csio_scsis_io_active(काष्ठा csio_ioreq *, क्रमागत csio_scsi_ev);
अटल व्योम csio_scsis_पंचांग_active(काष्ठा csio_ioreq *, क्रमागत csio_scsi_ev);
अटल व्योम csio_scsis_पातing(काष्ठा csio_ioreq *, क्रमागत csio_scsi_ev);
अटल व्योम csio_scsis_closing(काष्ठा csio_ioreq *, क्रमागत csio_scsi_ev);
अटल व्योम csio_scsis_shost_cmpl_aरुको(काष्ठा csio_ioreq *, क्रमागत csio_scsi_ev);

/*
 * csio_scsi_match_io - Match an ioreq with the given SCSI level data.
 * @ioreq: The I/O request
 * @sld: Level inक्रमmation
 *
 * Should be called with lock held.
 *
 */
अटल bool
csio_scsi_match_io(काष्ठा csio_ioreq *ioreq, काष्ठा csio_scsi_level_data *sld)
अणु
	काष्ठा scsi_cmnd *scmnd = csio_scsi_cmnd(ioreq);

	चयन (sld->level) अणु
	हाल CSIO_LEV_LUN:
		अगर (scmnd == शून्य)
			वापस false;

		वापस ((ioreq->lnode == sld->lnode) &&
			(ioreq->rnode == sld->rnode) &&
			((uपूर्णांक64_t)scmnd->device->lun == sld->oslun));

	हाल CSIO_LEV_RNODE:
		वापस ((ioreq->lnode == sld->lnode) &&
				(ioreq->rnode == sld->rnode));
	हाल CSIO_LEV_LNODE:
		वापस (ioreq->lnode == sld->lnode);
	हाल CSIO_LEV_ALL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * csio_scsi_gather_active_ios - Gather active I/Os based on level
 * @scm: SCSI module
 * @sld: Level inक्रमmation
 * @dest: The queue where these I/Os have to be gathered.
 *
 * Should be called with lock held.
 */
अटल व्योम
csio_scsi_gather_active_ios(काष्ठा csio_scsim *scm,
			    काष्ठा csio_scsi_level_data *sld,
			    काष्ठा list_head *dest)
अणु
	काष्ठा list_head *पंचांगp, *next;

	अगर (list_empty(&scm->active_q))
		वापस;

	/* Just splice the entire active_q पूर्णांकo dest */
	अगर (sld->level == CSIO_LEV_ALL) अणु
		list_splice_tail_init(&scm->active_q, dest);
		वापस;
	पूर्ण

	list_क्रम_each_safe(पंचांगp, next, &scm->active_q) अणु
		अगर (csio_scsi_match_io((काष्ठा csio_ioreq *)पंचांगp, sld)) अणु
			list_del_init(पंचांगp);
			list_add_tail(पंचांगp, dest);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत bool
csio_scsi_itnexus_loss_error(uपूर्णांक16_t error)
अणु
	चयन (error) अणु
	हाल FW_ERR_LINK_DOWN:
	हाल FW_RDEV_NOT_READY:
	हाल FW_ERR_RDEV_LOST:
	हाल FW_ERR_RDEV_LOGO:
	हाल FW_ERR_RDEV_IMPL_LOGO:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * csio_scsi_fcp_cmnd - Frame the SCSI FCP command paylod.
 * @req: IO req काष्ठाure.
 * @addr: DMA location to place the payload.
 *
 * This routine is shared between FCP_WRITE, FCP_READ and FCP_CMD requests.
 */
अटल अंतरभूत व्योम
csio_scsi_fcp_cmnd(काष्ठा csio_ioreq *req, व्योम *addr)
अणु
	काष्ठा fcp_cmnd *fcp_cmnd = (काष्ठा fcp_cmnd *)addr;
	काष्ठा scsi_cmnd *scmnd = csio_scsi_cmnd(req);

	/* Check क्रम Task Management */
	अगर (likely(scmnd->SCp.Message == 0)) अणु
		पूर्णांक_to_scsilun(scmnd->device->lun, &fcp_cmnd->fc_lun);
		fcp_cmnd->fc_पंचांग_flags = 0;
		fcp_cmnd->fc_cmdref = 0;

		स_नकल(fcp_cmnd->fc_cdb, scmnd->cmnd, 16);
		fcp_cmnd->fc_pri_ta = FCP_PTA_SIMPLE;
		fcp_cmnd->fc_dl = cpu_to_be32(scsi_bufflen(scmnd));

		अगर (req->nsge)
			अगर (req->datadir == DMA_TO_DEVICE)
				fcp_cmnd->fc_flags = FCP_CFL_WRDATA;
			अन्यथा
				fcp_cmnd->fc_flags = FCP_CFL_RDDATA;
		अन्यथा
			fcp_cmnd->fc_flags = 0;
	पूर्ण अन्यथा अणु
		स_रखो(fcp_cmnd, 0, माप(*fcp_cmnd));
		पूर्णांक_to_scsilun(scmnd->device->lun, &fcp_cmnd->fc_lun);
		fcp_cmnd->fc_पंचांग_flags = (uपूर्णांक8_t)scmnd->SCp.Message;
	पूर्ण
पूर्ण

/*
 * csio_scsi_init_cmd_wr - Initialize the SCSI CMD WR.
 * @req: IO req काष्ठाure.
 * @addr: DMA location to place the payload.
 * @size: Size of WR (including FW WR + immed data + rsp SG entry
 *
 * Wrapper क्रम populating fw_scsi_cmd_wr.
 */
अटल अंतरभूत व्योम
csio_scsi_init_cmd_wr(काष्ठा csio_ioreq *req, व्योम *addr, uपूर्णांक32_t size)
अणु
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_rnode *rn = req->rnode;
	काष्ठा fw_scsi_cmd_wr *wr = (काष्ठा fw_scsi_cmd_wr *)addr;
	काष्ठा csio_dma_buf *dma_buf;
	uपूर्णांक8_t imm = csio_hw_to_scsim(hw)->proto_cmd_len;

	wr->op_immdlen = cpu_to_be32(FW_WR_OP_V(FW_SCSI_CMD_WR) |
					  FW_SCSI_CMD_WR_IMMDLEN(imm));
	wr->flowid_len16 = cpu_to_be32(FW_WR_FLOWID_V(rn->flowid) |
					    FW_WR_LEN16_V(
						DIV_ROUND_UP(size, 16)));

	wr->cookie = (uपूर्णांकptr_t) req;
	wr->iqid = cpu_to_be16(csio_q_physiqid(hw, req->iq_idx));
	wr->पंचांगo_val = (uपूर्णांक8_t) req->पंचांगo;
	wr->r3 = 0;
	स_रखो(&wr->r5, 0, 8);

	/* Get RSP DMA buffer */
	dma_buf = &req->dma_buf;

	/* Prepare RSP SGL */
	wr->rsp_dmalen = cpu_to_be32(dma_buf->len);
	wr->rsp_dmaaddr = cpu_to_be64(dma_buf->paddr);

	wr->r6 = 0;

	wr->u.fcoe.ctl_pri = 0;
	wr->u.fcoe.cp_en_class = 0;
	wr->u.fcoe.r4_lo[0] = 0;
	wr->u.fcoe.r4_lo[1] = 0;

	/* Frame a FCP command */
	csio_scsi_fcp_cmnd(req, (व्योम *)((uपूर्णांकptr_t)addr +
				    माप(काष्ठा fw_scsi_cmd_wr)));
पूर्ण

#घोषणा CSIO_SCSI_CMD_WR_SZ(_imm)					\
	(माप(काष्ठा fw_scsi_cmd_wr) +		/* WR size */	\
	 ALIGN((_imm), 16))				/* Immed data */

#घोषणा CSIO_SCSI_CMD_WR_SZ_16(_imm)					\
			(ALIGN(CSIO_SCSI_CMD_WR_SZ((_imm)), 16))

/*
 * csio_scsi_cmd - Create a SCSI CMD WR.
 * @req: IO req काष्ठाure.
 *
 * Gets a WR slot in the ingress queue and initializes it with SCSI CMD WR.
 *
 */
अटल अंतरभूत व्योम
csio_scsi_cmd(काष्ठा csio_ioreq *req)
अणु
	काष्ठा csio_wr_pair wrp;
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_scsim *scsim = csio_hw_to_scsim(hw);
	uपूर्णांक32_t size = CSIO_SCSI_CMD_WR_SZ_16(scsim->proto_cmd_len);

	req->drv_status = csio_wr_get(hw, req->eq_idx, size, &wrp);
	अगर (unlikely(req->drv_status != 0))
		वापस;

	अगर (wrp.size1 >= size) अणु
		/* Initialize WR in one shot */
		csio_scsi_init_cmd_wr(req, wrp.addr1, size);
	पूर्ण अन्यथा अणु
		uपूर्णांक8_t *पंचांगpwr = csio_q_eq_wrap(hw, req->eq_idx);

		/*
		 * Make a temporary copy of the WR and ग_लिखो back
		 * the copy पूर्णांकo the WR pair.
		 */
		csio_scsi_init_cmd_wr(req, (व्योम *)पंचांगpwr, size);
		स_नकल(wrp.addr1, पंचांगpwr, wrp.size1);
		स_नकल(wrp.addr2, पंचांगpwr + wrp.size1, size - wrp.size1);
	पूर्ण
पूर्ण

/*
 * csio_scsi_init_ulptx_dsgl - Fill in a ULP_TX_SC_DSGL
 * @hw: HW module
 * @req: IO request
 * @sgl: ULP TX SGL poपूर्णांकer.
 *
 */
अटल अंतरभूत व्योम
csio_scsi_init_ultptx_dsgl(काष्ठा csio_hw *hw, काष्ठा csio_ioreq *req,
			   काष्ठा ulptx_sgl *sgl)
अणु
	काष्ठा ulptx_sge_pair *sge_pair = शून्य;
	काष्ठा scatterlist *sgel;
	uपूर्णांक32_t i = 0;
	uपूर्णांक32_t xfer_len;
	काष्ठा list_head *पंचांगp;
	काष्ठा csio_dma_buf *dma_buf;
	काष्ठा scsi_cmnd *scmnd = csio_scsi_cmnd(req);

	sgl->cmd_nsge = htonl(ULPTX_CMD_V(ULP_TX_SC_DSGL) | ULPTX_MORE_F |
				     ULPTX_NSGE_V(req->nsge));
	/* Now add the data SGLs */
	अगर (likely(!req->dcopy)) अणु
		scsi_क्रम_each_sg(scmnd, sgel, req->nsge, i) अणु
			अगर (i == 0) अणु
				sgl->addr0 = cpu_to_be64(sg_dma_address(sgel));
				sgl->len0 = cpu_to_be32(sg_dma_len(sgel));
				sge_pair = (काष्ठा ulptx_sge_pair *)(sgl + 1);
				जारी;
			पूर्ण
			अगर ((i - 1) & 0x1) अणु
				sge_pair->addr[1] = cpu_to_be64(
							sg_dma_address(sgel));
				sge_pair->len[1] = cpu_to_be32(
							sg_dma_len(sgel));
				sge_pair++;
			पूर्ण अन्यथा अणु
				sge_pair->addr[0] = cpu_to_be64(
							sg_dma_address(sgel));
				sge_pair->len[0] = cpu_to_be32(
							sg_dma_len(sgel));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Program sg elements with driver's DDP buffer */
		xfer_len = scsi_bufflen(scmnd);
		list_क्रम_each(पंचांगp, &req->gen_list) अणु
			dma_buf = (काष्ठा csio_dma_buf *)पंचांगp;
			अगर (i == 0) अणु
				sgl->addr0 = cpu_to_be64(dma_buf->paddr);
				sgl->len0 = cpu_to_be32(
						min(xfer_len, dma_buf->len));
				sge_pair = (काष्ठा ulptx_sge_pair *)(sgl + 1);
			पूर्ण अन्यथा अगर ((i - 1) & 0x1) अणु
				sge_pair->addr[1] = cpu_to_be64(dma_buf->paddr);
				sge_pair->len[1] = cpu_to_be32(
						min(xfer_len, dma_buf->len));
				sge_pair++;
			पूर्ण अन्यथा अणु
				sge_pair->addr[0] = cpu_to_be64(dma_buf->paddr);
				sge_pair->len[0] = cpu_to_be32(
						min(xfer_len, dma_buf->len));
			पूर्ण
			xfer_len -= min(xfer_len, dma_buf->len);
			i++;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * csio_scsi_init_पढ़ो_wr - Initialize the READ SCSI WR.
 * @req: IO req काष्ठाure.
 * @wrp: DMA location to place the payload.
 * @size: Size of WR (including FW WR + immed data + rsp SG entry + data SGL
 *
 * Wrapper क्रम populating fw_scsi_पढ़ो_wr.
 */
अटल अंतरभूत व्योम
csio_scsi_init_पढ़ो_wr(काष्ठा csio_ioreq *req, व्योम *wrp, uपूर्णांक32_t size)
अणु
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_rnode *rn = req->rnode;
	काष्ठा fw_scsi_पढ़ो_wr *wr = (काष्ठा fw_scsi_पढ़ो_wr *)wrp;
	काष्ठा ulptx_sgl *sgl;
	काष्ठा csio_dma_buf *dma_buf;
	uपूर्णांक8_t imm = csio_hw_to_scsim(hw)->proto_cmd_len;
	काष्ठा scsi_cmnd *scmnd = csio_scsi_cmnd(req);

	wr->op_immdlen = cpu_to_be32(FW_WR_OP_V(FW_SCSI_READ_WR) |
				     FW_SCSI_READ_WR_IMMDLEN(imm));
	wr->flowid_len16 = cpu_to_be32(FW_WR_FLOWID_V(rn->flowid) |
				       FW_WR_LEN16_V(DIV_ROUND_UP(size, 16)));
	wr->cookie = (uपूर्णांकptr_t)req;
	wr->iqid = cpu_to_be16(csio_q_physiqid(hw, req->iq_idx));
	wr->पंचांगo_val = (uपूर्णांक8_t)(req->पंचांगo);
	wr->use_xfer_cnt = 1;
	wr->xfer_cnt = cpu_to_be32(scsi_bufflen(scmnd));
	wr->ini_xfer_cnt = cpu_to_be32(scsi_bufflen(scmnd));
	/* Get RSP DMA buffer */
	dma_buf = &req->dma_buf;

	/* Prepare RSP SGL */
	wr->rsp_dmalen = cpu_to_be32(dma_buf->len);
	wr->rsp_dmaaddr = cpu_to_be64(dma_buf->paddr);

	wr->r4 = 0;

	wr->u.fcoe.ctl_pri = 0;
	wr->u.fcoe.cp_en_class = 0;
	wr->u.fcoe.r3_lo[0] = 0;
	wr->u.fcoe.r3_lo[1] = 0;
	csio_scsi_fcp_cmnd(req, (व्योम *)((uपूर्णांकptr_t)wrp +
					माप(काष्ठा fw_scsi_पढ़ो_wr)));

	/* Move WR poपूर्णांकer past command and immediate data */
	sgl = (काष्ठा ulptx_sgl *)((uपूर्णांकptr_t)wrp +
			      माप(काष्ठा fw_scsi_पढ़ो_wr) + ALIGN(imm, 16));

	/* Fill in the DSGL */
	csio_scsi_init_ultptx_dsgl(hw, req, sgl);
पूर्ण

/*
 * csio_scsi_init_ग_लिखो_wr - Initialize the WRITE SCSI WR.
 * @req: IO req काष्ठाure.
 * @wrp: DMA location to place the payload.
 * @size: Size of WR (including FW WR + immed data + rsp SG entry + data SGL
 *
 * Wrapper क्रम populating fw_scsi_ग_लिखो_wr.
 */
अटल अंतरभूत व्योम
csio_scsi_init_ग_लिखो_wr(काष्ठा csio_ioreq *req, व्योम *wrp, uपूर्णांक32_t size)
अणु
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_rnode *rn = req->rnode;
	काष्ठा fw_scsi_ग_लिखो_wr *wr = (काष्ठा fw_scsi_ग_लिखो_wr *)wrp;
	काष्ठा ulptx_sgl *sgl;
	काष्ठा csio_dma_buf *dma_buf;
	uपूर्णांक8_t imm = csio_hw_to_scsim(hw)->proto_cmd_len;
	काष्ठा scsi_cmnd *scmnd = csio_scsi_cmnd(req);

	wr->op_immdlen = cpu_to_be32(FW_WR_OP_V(FW_SCSI_WRITE_WR) |
				     FW_SCSI_WRITE_WR_IMMDLEN(imm));
	wr->flowid_len16 = cpu_to_be32(FW_WR_FLOWID_V(rn->flowid) |
				       FW_WR_LEN16_V(DIV_ROUND_UP(size, 16)));
	wr->cookie = (uपूर्णांकptr_t)req;
	wr->iqid = cpu_to_be16(csio_q_physiqid(hw, req->iq_idx));
	wr->पंचांगo_val = (uपूर्णांक8_t)(req->पंचांगo);
	wr->use_xfer_cnt = 1;
	wr->xfer_cnt = cpu_to_be32(scsi_bufflen(scmnd));
	wr->ini_xfer_cnt = cpu_to_be32(scsi_bufflen(scmnd));
	/* Get RSP DMA buffer */
	dma_buf = &req->dma_buf;

	/* Prepare RSP SGL */
	wr->rsp_dmalen = cpu_to_be32(dma_buf->len);
	wr->rsp_dmaaddr = cpu_to_be64(dma_buf->paddr);

	wr->r4 = 0;

	wr->u.fcoe.ctl_pri = 0;
	wr->u.fcoe.cp_en_class = 0;
	wr->u.fcoe.r3_lo[0] = 0;
	wr->u.fcoe.r3_lo[1] = 0;
	csio_scsi_fcp_cmnd(req, (व्योम *)((uपूर्णांकptr_t)wrp +
					माप(काष्ठा fw_scsi_ग_लिखो_wr)));

	/* Move WR poपूर्णांकer past command and immediate data */
	sgl = (काष्ठा ulptx_sgl *)((uपूर्णांकptr_t)wrp +
			      माप(काष्ठा fw_scsi_ग_लिखो_wr) + ALIGN(imm, 16));

	/* Fill in the DSGL */
	csio_scsi_init_ultptx_dsgl(hw, req, sgl);
पूर्ण

/* Calculate WR size needed क्रम fw_scsi_पढ़ो_wr/fw_scsi_ग_लिखो_wr */
#घोषणा CSIO_SCSI_DATA_WRSZ(req, oper, sz, imm)				       \
करो अणु									       \
	(sz) = माप(काष्ठा fw_scsi_##oper##_wr) +	/* WR size */          \
	       ALIGN((imm), 16) +			/* Immed data */       \
	       माप(काष्ठा ulptx_sgl);		/* ulptx_sgl */	       \
									       \
	अगर (unlikely((req)->nsge > 1))				               \
		(sz) += (माप(काष्ठा ulptx_sge_pair) *		       \
				(ALIGN(((req)->nsge - 1), 2) / 2));            \
							/* Data SGE */	       \
पूर्ण जबतक (0)

/*
 * csio_scsi_पढ़ो - Create a SCSI READ WR.
 * @req: IO req काष्ठाure.
 *
 * Gets a WR slot in the ingress queue and initializes it with
 * SCSI READ WR.
 *
 */
अटल अंतरभूत व्योम
csio_scsi_पढ़ो(काष्ठा csio_ioreq *req)
अणु
	काष्ठा csio_wr_pair wrp;
	uपूर्णांक32_t size;
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_scsim *scsim = csio_hw_to_scsim(hw);

	CSIO_SCSI_DATA_WRSZ(req, पढ़ो, size, scsim->proto_cmd_len);
	size = ALIGN(size, 16);

	req->drv_status = csio_wr_get(hw, req->eq_idx, size, &wrp);
	अगर (likely(req->drv_status == 0)) अणु
		अगर (likely(wrp.size1 >= size)) अणु
			/* Initialize WR in one shot */
			csio_scsi_init_पढ़ो_wr(req, wrp.addr1, size);
		पूर्ण अन्यथा अणु
			uपूर्णांक8_t *पंचांगpwr = csio_q_eq_wrap(hw, req->eq_idx);
			/*
			 * Make a temporary copy of the WR and ग_लिखो back
			 * the copy पूर्णांकo the WR pair.
			 */
			csio_scsi_init_पढ़ो_wr(req, (व्योम *)पंचांगpwr, size);
			स_नकल(wrp.addr1, पंचांगpwr, wrp.size1);
			स_नकल(wrp.addr2, पंचांगpwr + wrp.size1, size - wrp.size1);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * csio_scsi_ग_लिखो - Create a SCSI WRITE WR.
 * @req: IO req काष्ठाure.
 *
 * Gets a WR slot in the ingress queue and initializes it with
 * SCSI WRITE WR.
 *
 */
अटल अंतरभूत व्योम
csio_scsi_ग_लिखो(काष्ठा csio_ioreq *req)
अणु
	काष्ठा csio_wr_pair wrp;
	uपूर्णांक32_t size;
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_scsim *scsim = csio_hw_to_scsim(hw);

	CSIO_SCSI_DATA_WRSZ(req, ग_लिखो, size, scsim->proto_cmd_len);
	size = ALIGN(size, 16);

	req->drv_status = csio_wr_get(hw, req->eq_idx, size, &wrp);
	अगर (likely(req->drv_status == 0)) अणु
		अगर (likely(wrp.size1 >= size)) अणु
			/* Initialize WR in one shot */
			csio_scsi_init_ग_लिखो_wr(req, wrp.addr1, size);
		पूर्ण अन्यथा अणु
			uपूर्णांक8_t *पंचांगpwr = csio_q_eq_wrap(hw, req->eq_idx);
			/*
			 * Make a temporary copy of the WR and ग_लिखो back
			 * the copy पूर्णांकo the WR pair.
			 */
			csio_scsi_init_ग_लिखो_wr(req, (व्योम *)पंचांगpwr, size);
			स_नकल(wrp.addr1, पंचांगpwr, wrp.size1);
			स_नकल(wrp.addr2, पंचांगpwr + wrp.size1, size - wrp.size1);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * csio_setup_ddp - Setup DDP buffers क्रम Read request.
 * @req: IO req काष्ठाure.
 *
 * Checks SGLs/Data buffers are भवly contiguous required क्रम DDP.
 * If contiguous,driver posts SGLs in the WR otherwise post पूर्णांकernal
 * buffers क्रम such request क्रम DDP.
 */
अटल अंतरभूत व्योम
csio_setup_ddp(काष्ठा csio_scsim *scsim, काष्ठा csio_ioreq *req)
अणु
#अगर_घोषित __CSIO_DEBUG__
	काष्ठा csio_hw *hw = req->lnode->hwp;
#पूर्ण_अगर
	काष्ठा scatterlist *sgel = शून्य;
	काष्ठा scsi_cmnd *scmnd = csio_scsi_cmnd(req);
	uपूर्णांक64_t sg_addr = 0;
	uपूर्णांक32_t ddp_pagesz = 4096;
	uपूर्णांक32_t buf_off;
	काष्ठा csio_dma_buf *dma_buf = शून्य;
	uपूर्णांक32_t alloc_len = 0;
	uपूर्णांक32_t xfer_len = 0;
	uपूर्णांक32_t sg_len = 0;
	uपूर्णांक32_t i;

	scsi_क्रम_each_sg(scmnd, sgel, req->nsge, i) अणु
		sg_addr = sg_dma_address(sgel);
		sg_len	= sg_dma_len(sgel);

		buf_off = sg_addr & (ddp_pagesz - 1);

		/* Except 1st buffer,all buffer addr have to be Page aligned */
		अगर (i != 0 && buf_off) अणु
			csio_dbg(hw, "SGL addr not DDP aligned (%llx:%d)\n",
				 sg_addr, sg_len);
			जाओ unaligned;
		पूर्ण

		/* Except last buffer,all buffer must end on page boundary */
		अगर ((i != (req->nsge - 1)) &&
			((buf_off + sg_len) & (ddp_pagesz - 1))) अणु
			csio_dbg(hw,
				 "SGL addr not ending on page boundary"
				 "(%llx:%d)\n", sg_addr, sg_len);
			जाओ unaligned;
		पूर्ण
	पूर्ण

	/* SGL's are भवly contiguous. HW will DDP to SGLs */
	req->dcopy = 0;
	csio_scsi_पढ़ो(req);

	वापस;

unaligned:
	CSIO_INC_STATS(scsim, n_unaligned);
	/*
	 * For unaligned SGLs, driver will allocate पूर्णांकernal DDP buffer.
	 * Once command is completed data from DDP buffer copied to SGLs
	 */
	req->dcopy = 1;

	/* Use gen_list to store the DDP buffers */
	INIT_LIST_HEAD(&req->gen_list);
	xfer_len = scsi_bufflen(scmnd);

	i = 0;
	/* Allocate ddp buffers क्रम this request */
	जबतक (alloc_len < xfer_len) अणु
		dma_buf = csio_get_scsi_ddp(scsim);
		अगर (dma_buf == शून्य || i > scsim->max_sge) अणु
			req->drv_status = -EBUSY;
			अवरोध;
		पूर्ण
		alloc_len += dma_buf->len;
		/* Added to IO req */
		list_add_tail(&dma_buf->list, &req->gen_list);
		i++;
	पूर्ण

	अगर (!req->drv_status) अणु
		/* set number of ddp bufs used */
		req->nsge = i;
		csio_scsi_पढ़ो(req);
		वापस;
	पूर्ण

	 /* release dma descs */
	अगर (i > 0)
		csio_put_scsi_ddp_list(scsim, &req->gen_list, i);
पूर्ण

/*
 * csio_scsi_init_abrt_cls_wr - Initialize an ABORT/CLOSE WR.
 * @req: IO req काष्ठाure.
 * @addr: DMA location to place the payload.
 * @size: Size of WR
 * @पात: पात OR बंद
 *
 * Wrapper क्रम populating fw_scsi_cmd_wr.
 */
अटल अंतरभूत व्योम
csio_scsi_init_abrt_cls_wr(काष्ठा csio_ioreq *req, व्योम *addr, uपूर्णांक32_t size,
			   bool पात)
अणु
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_rnode *rn = req->rnode;
	काष्ठा fw_scsi_abrt_cls_wr *wr = (काष्ठा fw_scsi_abrt_cls_wr *)addr;

	wr->op_immdlen = cpu_to_be32(FW_WR_OP_V(FW_SCSI_ABRT_CLS_WR));
	wr->flowid_len16 = cpu_to_be32(FW_WR_FLOWID_V(rn->flowid) |
					    FW_WR_LEN16_V(
						DIV_ROUND_UP(size, 16)));

	wr->cookie = (uपूर्णांकptr_t) req;
	wr->iqid = cpu_to_be16(csio_q_physiqid(hw, req->iq_idx));
	wr->पंचांगo_val = (uपूर्णांक8_t) req->पंचांगo;
	/* 0 क्रम CHK_ALL_IO tells FW to look up t_cookie */
	wr->sub_opcode_to_chk_all_io =
				(FW_SCSI_ABRT_CLS_WR_SUB_OPCODE(पात) |
				 FW_SCSI_ABRT_CLS_WR_CHK_ALL_IO(0));
	wr->r3[0] = 0;
	wr->r3[1] = 0;
	wr->r3[2] = 0;
	wr->r3[3] = 0;
	/* Since we re-use the same ioreq क्रम पात as well */
	wr->t_cookie = (uपूर्णांकptr_t) req;
पूर्ण

अटल अंतरभूत व्योम
csio_scsi_abrt_cls(काष्ठा csio_ioreq *req, bool पात)
अणु
	काष्ठा csio_wr_pair wrp;
	काष्ठा csio_hw *hw = req->lnode->hwp;
	uपूर्णांक32_t size = ALIGN(माप(काष्ठा fw_scsi_abrt_cls_wr), 16);

	req->drv_status = csio_wr_get(hw, req->eq_idx, size, &wrp);
	अगर (req->drv_status != 0)
		वापस;

	अगर (wrp.size1 >= size) अणु
		/* Initialize WR in one shot */
		csio_scsi_init_abrt_cls_wr(req, wrp.addr1, size, पात);
	पूर्ण अन्यथा अणु
		uपूर्णांक8_t *पंचांगpwr = csio_q_eq_wrap(hw, req->eq_idx);
		/*
		 * Make a temporary copy of the WR and ग_लिखो back
		 * the copy पूर्णांकo the WR pair.
		 */
		csio_scsi_init_abrt_cls_wr(req, (व्योम *)पंचांगpwr, size, पात);
		स_नकल(wrp.addr1, पंचांगpwr, wrp.size1);
		स_नकल(wrp.addr2, पंचांगpwr + wrp.size1, size - wrp.size1);
	पूर्ण
पूर्ण

/*****************************************************************************/
/* START: SCSI SM                                                            */
/*****************************************************************************/
अटल व्योम
csio_scsis_uninit(काष्ठा csio_ioreq *req, क्रमागत csio_scsi_ev evt)
अणु
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_scsim *scsim = csio_hw_to_scsim(hw);

	चयन (evt) अणु
	हाल CSIO_SCSIE_START_IO:

		अगर (req->nsge) अणु
			अगर (req->datadir == DMA_TO_DEVICE) अणु
				req->dcopy = 0;
				csio_scsi_ग_लिखो(req);
			पूर्ण अन्यथा
				csio_setup_ddp(scsim, req);
		पूर्ण अन्यथा अणु
			csio_scsi_cmd(req);
		पूर्ण

		अगर (likely(req->drv_status == 0)) अणु
			/* change state and enqueue on active_q */
			csio_set_state(&req->sm, csio_scsis_io_active);
			list_add_tail(&req->sm.sm_list, &scsim->active_q);
			csio_wr_issue(hw, req->eq_idx, false);
			CSIO_INC_STATS(scsim, n_active);

			वापस;
		पूर्ण
		अवरोध;

	हाल CSIO_SCSIE_START_TM:
		csio_scsi_cmd(req);
		अगर (req->drv_status == 0) अणु
			/*
			 * NOTE: We collect the affected I/Os prior to issuing
			 * LUN reset, and not after it. This is to prevent
			 * पातing I/Os that get issued after the LUN reset,
			 * but prior to LUN reset completion (in the event that
			 * the host stack has not blocked I/Os to a LUN that is
			 * being reset.
			 */
			csio_set_state(&req->sm, csio_scsis_पंचांग_active);
			list_add_tail(&req->sm.sm_list, &scsim->active_q);
			csio_wr_issue(hw, req->eq_idx, false);
			CSIO_INC_STATS(scsim, n_पंचांग_active);
		पूर्ण
		वापस;

	हाल CSIO_SCSIE_ABORT:
	हाल CSIO_SCSIE_CLOSE:
		/*
		 * NOTE:
		 * We could get here due to  :
		 * - a winकरोw in the cleanup path of the SCSI module
		 *   (csio_scsi_पात_io()). Please see NOTE in this function.
		 * - a winकरोw in the समय we tried to issue an पात/बंद
		 *   of a request to FW, and the FW completed the request
		 *   itself.
		 *   Prपूर्णांक a message क्रम now, and वापस INVAL either way.
		 */
		req->drv_status = -EINVAL;
		csio_warn(hw, "Trying to abort/close completed IO:%p!\n", req);
		अवरोध;

	शेष:
		csio_dbg(hw, "Unhandled event:%d sent to req:%p\n", evt, req);
		CSIO_DB_ASSERT(0);
	पूर्ण
पूर्ण

अटल व्योम
csio_scsis_io_active(काष्ठा csio_ioreq *req, क्रमागत csio_scsi_ev evt)
अणु
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_scsim *scm = csio_hw_to_scsim(hw);
	काष्ठा csio_rnode *rn;

	चयन (evt) अणु
	हाल CSIO_SCSIE_COMPLETED:
		CSIO_DEC_STATS(scm, n_active);
		list_del_init(&req->sm.sm_list);
		csio_set_state(&req->sm, csio_scsis_uninit);
		/*
		 * In MSIX mode, with multiple queues, the SCSI compeltions
		 * could reach us sooner than the FW events sent to indicate
		 * I-T nexus loss (link करोwn, remote device logo etc). We
		 * करोnt want to be वापसing such I/Os to the upper layer
		 * immediately, since we wouldnt have reported the I-T nexus
		 * loss itself. This क्रमces us to serialize such completions
		 * with the reporting of the I-T nexus loss. Thereक्रमe, we
		 * पूर्णांकernally queue up such up such completions in the rnode.
		 * The reporting of I-T nexus loss to the upper layer is then
		 * followed by the वापसing of I/Os in this पूर्णांकernal queue.
		 * Having another state aदीर्घwith another queue helps us take
		 * actions क्रम events such as ABORT received जबतक we are
		 * in this rnode queue.
		 */
		अगर (unlikely(req->wr_status != FW_SUCCESS)) अणु
			rn = req->rnode;
			/*
			 * FW says remote device is lost, but rnode
			 * करोesnt reflect it.
			 */
			अगर (csio_scsi_itnexus_loss_error(req->wr_status) &&
						csio_is_rnode_पढ़ोy(rn)) अणु
				csio_set_state(&req->sm,
						csio_scsis_shost_cmpl_aरुको);
				list_add_tail(&req->sm.sm_list,
					      &rn->host_cmpl_q);
			पूर्ण
		पूर्ण

		अवरोध;

	हाल CSIO_SCSIE_ABORT:
		csio_scsi_abrt_cls(req, SCSI_ABORT);
		अगर (req->drv_status == 0) अणु
			csio_wr_issue(hw, req->eq_idx, false);
			csio_set_state(&req->sm, csio_scsis_पातing);
		पूर्ण
		अवरोध;

	हाल CSIO_SCSIE_CLOSE:
		csio_scsi_abrt_cls(req, SCSI_CLOSE);
		अगर (req->drv_status == 0) अणु
			csio_wr_issue(hw, req->eq_idx, false);
			csio_set_state(&req->sm, csio_scsis_closing);
		पूर्ण
		अवरोध;

	हाल CSIO_SCSIE_DRVCLEANUP:
		req->wr_status = FW_HOSTERROR;
		CSIO_DEC_STATS(scm, n_active);
		csio_set_state(&req->sm, csio_scsis_uninit);
		अवरोध;

	शेष:
		csio_dbg(hw, "Unhandled event:%d sent to req:%p\n", evt, req);
		CSIO_DB_ASSERT(0);
	पूर्ण
पूर्ण

अटल व्योम
csio_scsis_पंचांग_active(काष्ठा csio_ioreq *req, क्रमागत csio_scsi_ev evt)
अणु
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_scsim *scm = csio_hw_to_scsim(hw);

	चयन (evt) अणु
	हाल CSIO_SCSIE_COMPLETED:
		CSIO_DEC_STATS(scm, n_पंचांग_active);
		list_del_init(&req->sm.sm_list);
		csio_set_state(&req->sm, csio_scsis_uninit);

		अवरोध;

	हाल CSIO_SCSIE_ABORT:
		csio_scsi_abrt_cls(req, SCSI_ABORT);
		अगर (req->drv_status == 0) अणु
			csio_wr_issue(hw, req->eq_idx, false);
			csio_set_state(&req->sm, csio_scsis_पातing);
		पूर्ण
		अवरोध;


	हाल CSIO_SCSIE_CLOSE:
		csio_scsi_abrt_cls(req, SCSI_CLOSE);
		अगर (req->drv_status == 0) अणु
			csio_wr_issue(hw, req->eq_idx, false);
			csio_set_state(&req->sm, csio_scsis_closing);
		पूर्ण
		अवरोध;

	हाल CSIO_SCSIE_DRVCLEANUP:
		req->wr_status = FW_HOSTERROR;
		CSIO_DEC_STATS(scm, n_पंचांग_active);
		csio_set_state(&req->sm, csio_scsis_uninit);
		अवरोध;

	शेष:
		csio_dbg(hw, "Unhandled event:%d sent to req:%p\n", evt, req);
		CSIO_DB_ASSERT(0);
	पूर्ण
पूर्ण

अटल व्योम
csio_scsis_पातing(काष्ठा csio_ioreq *req, क्रमागत csio_scsi_ev evt)
अणु
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_scsim *scm = csio_hw_to_scsim(hw);

	चयन (evt) अणु
	हाल CSIO_SCSIE_COMPLETED:
		csio_dbg(hw,
			 "ioreq %p recvd cmpltd (wr_status:%d) "
			 "in aborting st\n", req, req->wr_status);
		/*
		 * Use -ECANCELED to explicitly tell the ABORTED event that
		 * the original I/O was वापसed to driver by FW.
		 * We करोnt really care अगर the I/O was वापसed with success by
		 * FW (because the ABORT and completion of the I/O crossed each
		 * other), or any other वापस value. Once we are in पातing
		 * state, the success or failure of the I/O is unimportant to
		 * us.
		 */
		req->drv_status = -ECANCELED;
		अवरोध;

	हाल CSIO_SCSIE_ABORT:
		CSIO_INC_STATS(scm, n_abrt_dups);
		अवरोध;

	हाल CSIO_SCSIE_ABORTED:

		csio_dbg(hw, "abort of %p return status:0x%x drv_status:%x\n",
			 req, req->wr_status, req->drv_status);
		/*
		 * Check अगर original I/O WR completed beक्रमe the Abort
		 * completion.
		 */
		अगर (req->drv_status != -ECANCELED) अणु
			csio_warn(hw,
				  "Abort completed before original I/O,"
				   " req:%p\n", req);
			CSIO_DB_ASSERT(0);
		पूर्ण

		/*
		 * There are the following possible scenarios:
		 * 1. The पात completed successfully, FW वापसed FW_SUCCESS.
		 * 2. The completion of an I/O and the receipt of
		 *    पात क्रम that I/O by the FW crossed each other.
		 *    The FW वापसed FW_EINVAL. The original I/O would have
		 *    वापसed with FW_SUCCESS or any other SCSI error.
		 * 3. The FW couldn't sent the पात out on the wire, as there
		 *    was an I-T nexus loss (link करोwn, remote device logged
		 *    out etc). FW sent back an appropriate IT nexus loss status
		 *    क्रम the पात.
		 * 4. FW sent an पात, but पात समयd out (remote device
		 *    didnt respond). FW replied back with
		 *    FW_SCSI_ABORT_TIMEDOUT.
		 * 5. FW couldn't genuinely पात the request क्रम some reason,
		 *    and sent us an error.
		 *
		 * The first 3 scenarios are treated as  succesful पात
		 * operations by the host, जबतक the last 2 are failed attempts
		 * to पात. Manipulate the वापस value of the request
		 * appropriately, so that host can convey these results
		 * back to the upper layer.
		 */
		अगर ((req->wr_status == FW_SUCCESS) ||
		    (req->wr_status == FW_EINVAL) ||
		    csio_scsi_itnexus_loss_error(req->wr_status))
			req->wr_status = FW_SCSI_ABORT_REQUESTED;

		CSIO_DEC_STATS(scm, n_active);
		list_del_init(&req->sm.sm_list);
		csio_set_state(&req->sm, csio_scsis_uninit);
		अवरोध;

	हाल CSIO_SCSIE_DRVCLEANUP:
		req->wr_status = FW_HOSTERROR;
		CSIO_DEC_STATS(scm, n_active);
		csio_set_state(&req->sm, csio_scsis_uninit);
		अवरोध;

	हाल CSIO_SCSIE_CLOSE:
		/*
		 * We can receive this event from the module
		 * cleanup paths, अगर the FW क्रमgot to reply to the ABORT WR
		 * and left this ioreq in this state. For now, just ignore
		 * the event. The CLOSE event is sent to this state, as
		 * the LINK may have alपढ़ोy gone करोwn.
		 */
		अवरोध;

	शेष:
		csio_dbg(hw, "Unhandled event:%d sent to req:%p\n", evt, req);
		CSIO_DB_ASSERT(0);
	पूर्ण
पूर्ण

अटल व्योम
csio_scsis_closing(काष्ठा csio_ioreq *req, क्रमागत csio_scsi_ev evt)
अणु
	काष्ठा csio_hw *hw = req->lnode->hwp;
	काष्ठा csio_scsim *scm = csio_hw_to_scsim(hw);

	चयन (evt) अणु
	हाल CSIO_SCSIE_COMPLETED:
		csio_dbg(hw,
			 "ioreq %p recvd cmpltd (wr_status:%d) "
			 "in closing st\n", req, req->wr_status);
		/*
		 * Use -ECANCELED to explicitly tell the CLOSED event that
		 * the original I/O was वापसed to driver by FW.
		 * We करोnt really care अगर the I/O was वापसed with success by
		 * FW (because the CLOSE and completion of the I/O crossed each
		 * other), or any other वापस value. Once we are in पातing
		 * state, the success or failure of the I/O is unimportant to
		 * us.
		 */
		req->drv_status = -ECANCELED;
		अवरोध;

	हाल CSIO_SCSIE_CLOSED:
		/*
		 * Check अगर original I/O WR completed beक्रमe the Close
		 * completion.
		 */
		अगर (req->drv_status != -ECANCELED) अणु
			csio_fatal(hw,
				   "Close completed before original I/O,"
				   " req:%p\n", req);
			CSIO_DB_ASSERT(0);
		पूर्ण

		/*
		 * Either बंद succeeded, or we issued बंद to FW at the
		 * same समय FW compelted it to us. Either way, the I/O
		 * is बंदd.
		 */
		CSIO_DB_ASSERT((req->wr_status == FW_SUCCESS) ||
					(req->wr_status == FW_EINVAL));
		req->wr_status = FW_SCSI_CLOSE_REQUESTED;

		CSIO_DEC_STATS(scm, n_active);
		list_del_init(&req->sm.sm_list);
		csio_set_state(&req->sm, csio_scsis_uninit);
		अवरोध;

	हाल CSIO_SCSIE_CLOSE:
		अवरोध;

	हाल CSIO_SCSIE_DRVCLEANUP:
		req->wr_status = FW_HOSTERROR;
		CSIO_DEC_STATS(scm, n_active);
		csio_set_state(&req->sm, csio_scsis_uninit);
		अवरोध;

	शेष:
		csio_dbg(hw, "Unhandled event:%d sent to req:%p\n", evt, req);
		CSIO_DB_ASSERT(0);
	पूर्ण
पूर्ण

अटल व्योम
csio_scsis_shost_cmpl_aरुको(काष्ठा csio_ioreq *req, क्रमागत csio_scsi_ev evt)
अणु
	चयन (evt) अणु
	हाल CSIO_SCSIE_ABORT:
	हाल CSIO_SCSIE_CLOSE:
		/*
		 * Just succeed the पात request, and hope that
		 * the remote device unरेजिस्टर path will cleanup
		 * this I/O to the upper layer within a sane
		 * amount of समय.
		 */
		/*
		 * A बंद can come in during a LINK DOWN. The FW would have
		 * वापसed us the I/O back, but not the remote device lost
		 * FW event. In this पूर्णांकerval, अगर the I/O बार out at the upper
		 * layer, a बंद can come in. Take the same action as पात:
		 * वापस success, and hope that the remote device unरेजिस्टर
		 * path will cleanup this I/O. If the FW still करोesnt send
		 * the msg, the बंद बार out, and the upper layer resorts
		 * to the next level of error recovery.
		 */
		req->drv_status = 0;
		अवरोध;
	हाल CSIO_SCSIE_DRVCLEANUP:
		csio_set_state(&req->sm, csio_scsis_uninit);
		अवरोध;
	शेष:
		csio_dbg(req->lnode->hwp, "Unhandled event:%d sent to req:%p\n",
			 evt, req);
		CSIO_DB_ASSERT(0);
	पूर्ण
पूर्ण

/*
 * csio_scsi_cmpl_handler - WR completion handler क्रम SCSI.
 * @hw: HW module.
 * @wr: The completed WR from the ingress queue.
 * @len: Length of the WR.
 * @flb: Freelist buffer array.
 * @priv: Private object
 * @scsiwr: Poपूर्णांकer to SCSI WR.
 *
 * This is the WR completion handler called per completion from the
 * ISR. It is called with lock held. It walks past the RSS and CPL message
 * header where the actual WR is present.
 * It then माला_लो the status, WR handle (ioreq poपूर्णांकer) and the len of
 * the WR, based on WR opcode. Only on a non-good status is the entire
 * WR copied पूर्णांकo the WR cache (ioreq->fw_wr).
 * The ioreq corresponding to the WR is वापसed to the caller.
 * NOTE: The SCSI queue करोesnt allocate a मुक्तlist today, hence
 * no मुक्तlist buffer is expected.
 */
काष्ठा csio_ioreq *
csio_scsi_cmpl_handler(काष्ठा csio_hw *hw, व्योम *wr, uपूर्णांक32_t len,
		     काष्ठा csio_fl_dma_buf *flb, व्योम *priv, uपूर्णांक8_t **scsiwr)
अणु
	काष्ठा csio_ioreq *ioreq = शून्य;
	काष्ठा cpl_fw6_msg *cpl;
	uपूर्णांक8_t *tempwr;
	uपूर्णांक8_t	status;
	काष्ठा csio_scsim *scm = csio_hw_to_scsim(hw);

	/* skip RSS header */
	cpl = (काष्ठा cpl_fw6_msg *)((uपूर्णांकptr_t)wr + माप(__be64));

	अगर (unlikely(cpl->opcode != CPL_FW6_MSG)) अणु
		csio_warn(hw, "Error: Invalid CPL msg %x recvd on SCSI q\n",
			  cpl->opcode);
		CSIO_INC_STATS(scm, n_inval_cplop);
		वापस शून्य;
	पूर्ण

	tempwr = (uपूर्णांक8_t *)(cpl->data);
	status = csio_wr_status(tempwr);
	*scsiwr = tempwr;

	अगर (likely((*tempwr == FW_SCSI_READ_WR) ||
			(*tempwr == FW_SCSI_WRITE_WR) ||
			(*tempwr == FW_SCSI_CMD_WR))) अणु
		ioreq = (काष्ठा csio_ioreq *)((uपूर्णांकptr_t)
				 (((काष्ठा fw_scsi_पढ़ो_wr *)tempwr)->cookie));
		CSIO_DB_ASSERT(virt_addr_valid(ioreq));

		ioreq->wr_status = status;

		वापस ioreq;
	पूर्ण

	अगर (*tempwr == FW_SCSI_ABRT_CLS_WR) अणु
		ioreq = (काष्ठा csio_ioreq *)((uपूर्णांकptr_t)
			 (((काष्ठा fw_scsi_abrt_cls_wr *)tempwr)->cookie));
		CSIO_DB_ASSERT(virt_addr_valid(ioreq));

		ioreq->wr_status = status;
		वापस ioreq;
	पूर्ण

	csio_warn(hw, "WR with invalid opcode in SCSI IQ: %x\n", *tempwr);
	CSIO_INC_STATS(scm, n_inval_scsiop);
	वापस शून्य;
पूर्ण

/*
 * csio_scsi_cleanup_io_q - Cleanup the given queue.
 * @scm: SCSI module.
 * @q: Queue to be cleaned up.
 *
 * Called with lock held. Has to निकास with lock held.
 */
व्योम
csio_scsi_cleanup_io_q(काष्ठा csio_scsim *scm, काष्ठा list_head *q)
अणु
	काष्ठा csio_hw *hw = scm->hw;
	काष्ठा csio_ioreq *ioreq;
	काष्ठा list_head *पंचांगp, *next;
	काष्ठा scsi_cmnd *scmnd;

	/* Call back the completion routines of the active_q */
	list_क्रम_each_safe(पंचांगp, next, q) अणु
		ioreq = (काष्ठा csio_ioreq *)पंचांगp;
		csio_scsi_drvcleanup(ioreq);
		list_del_init(&ioreq->sm.sm_list);
		scmnd = csio_scsi_cmnd(ioreq);
		spin_unlock_irq(&hw->lock);

		/*
		 * Upper layers may have cleared this command, hence this
		 * check to aव्योम accessing stale references.
		 */
		अगर (scmnd != शून्य)
			ioreq->io_cbfn(hw, ioreq);

		spin_lock_irq(&scm->मुक्तlist_lock);
		csio_put_scsi_ioreq(scm, ioreq);
		spin_unlock_irq(&scm->मुक्तlist_lock);

		spin_lock_irq(&hw->lock);
	पूर्ण
पूर्ण

#घोषणा CSIO_SCSI_ABORT_Q_POLL_MS		2000

अटल व्योम
csio_abrt_cls(काष्ठा csio_ioreq *ioreq, काष्ठा scsi_cmnd *scmnd)
अणु
	काष्ठा csio_lnode *ln = ioreq->lnode;
	काष्ठा csio_hw *hw = ln->hwp;
	पूर्णांक पढ़ोy = 0;
	काष्ठा csio_scsim *scsim = csio_hw_to_scsim(hw);
	पूर्णांक rv;

	अगर (csio_scsi_cmnd(ioreq) != scmnd) अणु
		CSIO_INC_STATS(scsim, n_abrt_race_comp);
		वापस;
	पूर्ण

	पढ़ोy = csio_is_lnode_पढ़ोy(ln);

	rv = csio_करो_abrt_cls(hw, ioreq, (पढ़ोy ? SCSI_ABORT : SCSI_CLOSE));
	अगर (rv != 0) अणु
		अगर (पढ़ोy)
			CSIO_INC_STATS(scsim, n_abrt_busy_error);
		अन्यथा
			CSIO_INC_STATS(scsim, n_cls_busy_error);
	पूर्ण
पूर्ण

/*
 * csio_scsi_पात_io_q - Abort all I/Os on given queue
 * @scm: SCSI module.
 * @q: Queue to पात.
 * @पंचांगo: Timeout in ms
 *
 * Attempt to पात all I/Os on given queue, and रुको क्रम a max
 * of पंचांगo milliseconds क्रम them to complete. Returns success
 * अगर all I/Os are पातed. Else वापसs -ETIMEDOUT.
 * Should be entered with lock held. Exits with lock held.
 * NOTE:
 * Lock has to be held across the loop that पातs I/Os, since dropping the lock
 * in between can cause the list to be corrupted. As a result, the caller
 * of this function has to ensure that the number of I/os to be पातed
 * is finite enough to not cause lock-held-क्रम-too-दीर्घ issues.
 */
अटल पूर्णांक
csio_scsi_पात_io_q(काष्ठा csio_scsim *scm, काष्ठा list_head *q, uपूर्णांक32_t पंचांगo)
अणु
	काष्ठा csio_hw *hw = scm->hw;
	काष्ठा list_head *पंचांगp, *next;
	पूर्णांक count = DIV_ROUND_UP(पंचांगo, CSIO_SCSI_ABORT_Q_POLL_MS);
	काष्ठा scsi_cmnd *scmnd;

	अगर (list_empty(q))
		वापस 0;

	csio_dbg(hw, "Aborting SCSI I/Os\n");

	/* Now पात/बंद I/Os in the queue passed */
	list_क्रम_each_safe(पंचांगp, next, q) अणु
		scmnd = csio_scsi_cmnd((काष्ठा csio_ioreq *)पंचांगp);
		csio_abrt_cls((काष्ठा csio_ioreq *)पंचांगp, scmnd);
	पूर्ण

	/* Wait till all active I/Os are completed/पातed/बंदd */
	जबतक (!list_empty(q) && count--) अणु
		spin_unlock_irq(&hw->lock);
		msleep(CSIO_SCSI_ABORT_Q_POLL_MS);
		spin_lock_irq(&hw->lock);
	पूर्ण

	/* all पातs completed */
	अगर (list_empty(q))
		वापस 0;

	वापस -ETIMEDOUT;
पूर्ण

/*
 * csio_scsim_cleanup_io - Cleanup all I/Os in SCSI module.
 * @scm: SCSI module.
 * @पात: पात required.
 * Called with lock held, should निकास with lock held.
 * Can sleep when रुकोing क्रम I/Os to complete.
 */
पूर्णांक
csio_scsim_cleanup_io(काष्ठा csio_scsim *scm, bool पात)
अणु
	काष्ठा csio_hw *hw = scm->hw;
	पूर्णांक rv = 0;
	पूर्णांक count = DIV_ROUND_UP(60 * 1000, CSIO_SCSI_ABORT_Q_POLL_MS);

	/* No I/Os pending */
	अगर (list_empty(&scm->active_q))
		वापस 0;

	/* Wait until all active I/Os are completed */
	जबतक (!list_empty(&scm->active_q) && count--) अणु
		spin_unlock_irq(&hw->lock);
		msleep(CSIO_SCSI_ABORT_Q_POLL_MS);
		spin_lock_irq(&hw->lock);
	पूर्ण

	/* all I/Os completed */
	अगर (list_empty(&scm->active_q))
		वापस 0;

	/* Else पात */
	अगर (पात) अणु
		rv = csio_scsi_पात_io_q(scm, &scm->active_q, 30000);
		अगर (rv == 0)
			वापस rv;
		csio_dbg(hw, "Some I/O aborts timed out, cleaning up..\n");
	पूर्ण

	csio_scsi_cleanup_io_q(scm, &scm->active_q);

	CSIO_DB_ASSERT(list_empty(&scm->active_q));

	वापस rv;
पूर्ण

/*
 * csio_scsim_cleanup_io_lnode - Cleanup all I/Os of given lnode.
 * @scm: SCSI module.
 * @lnode: lnode
 *
 * Called with lock held, should निकास with lock held.
 * Can sleep (with dropped lock) when रुकोing क्रम I/Os to complete.
 */
पूर्णांक
csio_scsim_cleanup_io_lnode(काष्ठा csio_scsim *scm, काष्ठा csio_lnode *ln)
अणु
	काष्ठा csio_hw *hw = scm->hw;
	काष्ठा csio_scsi_level_data sld;
	पूर्णांक rv;
	पूर्णांक count = DIV_ROUND_UP(60 * 1000, CSIO_SCSI_ABORT_Q_POLL_MS);

	csio_dbg(hw, "Gathering all SCSI I/Os on lnode %p\n", ln);

	sld.level = CSIO_LEV_LNODE;
	sld.lnode = ln;
	INIT_LIST_HEAD(&ln->cmpl_q);
	csio_scsi_gather_active_ios(scm, &sld, &ln->cmpl_q);

	/* No I/Os pending on this lnode  */
	अगर (list_empty(&ln->cmpl_q))
		वापस 0;

	/* Wait until all active I/Os on this lnode are completed */
	जबतक (!list_empty(&ln->cmpl_q) && count--) अणु
		spin_unlock_irq(&hw->lock);
		msleep(CSIO_SCSI_ABORT_Q_POLL_MS);
		spin_lock_irq(&hw->lock);
	पूर्ण

	/* all I/Os completed */
	अगर (list_empty(&ln->cmpl_q))
		वापस 0;

	csio_dbg(hw, "Some I/Os pending on ln:%p, aborting them..\n", ln);

	/* I/Os are pending, पात them */
	rv = csio_scsi_पात_io_q(scm, &ln->cmpl_q, 30000);
	अगर (rv != 0) अणु
		csio_dbg(hw, "Some I/O aborts timed out, cleaning up..\n");
		csio_scsi_cleanup_io_q(scm, &ln->cmpl_q);
	पूर्ण

	CSIO_DB_ASSERT(list_empty(&ln->cmpl_q));

	वापस rv;
पूर्ण

अटल sमाप_प्रकार
csio_show_hw_state(काष्ठा device *dev,
		   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा csio_lnode *ln = shost_priv(class_to_shost(dev));
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	अगर (csio_is_hw_पढ़ोy(hw))
		वापस snम_लिखो(buf, PAGE_SIZE, "ready\n");
	अन्यथा
		वापस snम_लिखो(buf, PAGE_SIZE, "not ready\n");
पूर्ण

/* Device reset */
अटल sमाप_प्रकार
csio_device_reset(काष्ठा device *dev,
		   काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा csio_lnode *ln = shost_priv(class_to_shost(dev));
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	अगर (*buf != '1')
		वापस -EINVAL;

	/* Delete NPIV lnodes */
	csio_lnodes_निकास(hw, 1);

	/* Block upper IOs */
	csio_lnodes_block_request(hw);

	spin_lock_irq(&hw->lock);
	csio_hw_reset(hw);
	spin_unlock_irq(&hw->lock);

	/* Unblock upper IOs */
	csio_lnodes_unblock_request(hw);
	वापस count;
पूर्ण

/* disable port */
अटल sमाप_प्रकार
csio_disable_port(काष्ठा device *dev,
		   काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा csio_lnode *ln = shost_priv(class_to_shost(dev));
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	bool disable;

	अगर (*buf == '1' || *buf == '0')
		disable = (*buf == '1') ? true : false;
	अन्यथा
		वापस -EINVAL;

	/* Block upper IOs */
	csio_lnodes_block_by_port(hw, ln->portid);

	spin_lock_irq(&hw->lock);
	csio_disable_lnodes(hw, ln->portid, disable);
	spin_unlock_irq(&hw->lock);

	/* Unblock upper IOs */
	csio_lnodes_unblock_by_port(hw, ln->portid);
	वापस count;
पूर्ण

/* Show debug level */
अटल sमाप_प्रकार
csio_show_dbg_level(काष्ठा device *dev,
		   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा csio_lnode *ln = shost_priv(class_to_shost(dev));

	वापस snम_लिखो(buf, PAGE_SIZE, "%x\n", ln->params.log_level);
पूर्ण

/* Store debug level */
अटल sमाप_प्रकार
csio_store_dbg_level(काष्ठा device *dev,
		   काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा csio_lnode *ln = shost_priv(class_to_shost(dev));
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	uपूर्णांक32_t dbg_level = 0;

	अगर (!है_अंक(buf[0]))
		वापस -EINVAL;

	अगर (माला_पूछो(buf, "%i", &dbg_level))
		वापस -EINVAL;

	ln->params.log_level = dbg_level;
	hw->params.log_level = dbg_level;

	वापस 0;
पूर्ण

अटल DEVICE_ATTR(hw_state, S_IRUGO, csio_show_hw_state, शून्य);
अटल DEVICE_ATTR(device_reset, S_IWUSR, शून्य, csio_device_reset);
अटल DEVICE_ATTR(disable_port, S_IWUSR, शून्य, csio_disable_port);
अटल DEVICE_ATTR(dbg_level, S_IRUGO | S_IWUSR, csio_show_dbg_level,
		  csio_store_dbg_level);

अटल काष्ठा device_attribute *csio_fcoe_lport_attrs[] = अणु
	&dev_attr_hw_state,
	&dev_attr_device_reset,
	&dev_attr_disable_port,
	&dev_attr_dbg_level,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार
csio_show_num_reg_rnodes(काष्ठा device *dev,
		     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा csio_lnode *ln = shost_priv(class_to_shost(dev));

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ln->num_reg_rnodes);
पूर्ण

अटल DEVICE_ATTR(num_reg_rnodes, S_IRUGO, csio_show_num_reg_rnodes, शून्य);

अटल काष्ठा device_attribute *csio_fcoe_vport_attrs[] = अणु
	&dev_attr_num_reg_rnodes,
	&dev_attr_dbg_level,
	शून्य,
पूर्ण;

अटल अंतरभूत uपूर्णांक32_t
csio_scsi_copy_to_sgl(काष्ठा csio_hw *hw, काष्ठा csio_ioreq *req)
अणु
	काष्ठा scsi_cmnd *scmnd  = (काष्ठा scsi_cmnd *)csio_scsi_cmnd(req);
	काष्ठा scatterlist *sg;
	uपूर्णांक32_t bytes_left;
	uपूर्णांक32_t bytes_copy;
	uपूर्णांक32_t buf_off = 0;
	uपूर्णांक32_t start_off = 0;
	uपूर्णांक32_t sg_off = 0;
	व्योम *sg_addr;
	व्योम *buf_addr;
	काष्ठा csio_dma_buf *dma_buf;

	bytes_left = scsi_bufflen(scmnd);
	sg = scsi_sglist(scmnd);
	dma_buf = (काष्ठा csio_dma_buf *)csio_list_next(&req->gen_list);

	/* Copy data from driver buffer to SGs of SCSI CMD */
	जबतक (bytes_left > 0 && sg && dma_buf) अणु
		अगर (buf_off >= dma_buf->len) अणु
			buf_off = 0;
			dma_buf = (काष्ठा csio_dma_buf *)
					csio_list_next(dma_buf);
			जारी;
		पूर्ण

		अगर (start_off >= sg->length) अणु
			start_off -= sg->length;
			sg = sg_next(sg);
			जारी;
		पूर्ण

		buf_addr = dma_buf->vaddr + buf_off;
		sg_off = sg->offset + start_off;
		bytes_copy = min((dma_buf->len - buf_off),
				sg->length - start_off);
		bytes_copy = min((uपूर्णांक32_t)(PAGE_SIZE - (sg_off & ~PAGE_MASK)),
				 bytes_copy);

		sg_addr = kmap_atomic(sg_page(sg) + (sg_off >> PAGE_SHIFT));
		अगर (!sg_addr) अणु
			csio_err(hw, "failed to kmap sg:%p of ioreq:%p\n",
				sg, req);
			अवरोध;
		पूर्ण

		csio_dbg(hw, "copy_to_sgl:sg_addr %p sg_off %d buf %p len %d\n",
				sg_addr, sg_off, buf_addr, bytes_copy);
		स_नकल(sg_addr + (sg_off & ~PAGE_MASK), buf_addr, bytes_copy);
		kunmap_atomic(sg_addr);

		start_off +=  bytes_copy;
		buf_off += bytes_copy;
		bytes_left -= bytes_copy;
	पूर्ण

	अगर (bytes_left > 0)
		वापस DID_ERROR;
	अन्यथा
		वापस DID_OK;
पूर्ण

/*
 * csio_scsi_err_handler - SCSI error handler.
 * @hw: HW module.
 * @req: IO request.
 *
 */
अटल अंतरभूत व्योम
csio_scsi_err_handler(काष्ठा csio_hw *hw, काष्ठा csio_ioreq *req)
अणु
	काष्ठा scsi_cmnd *cmnd  = (काष्ठा scsi_cmnd *)csio_scsi_cmnd(req);
	काष्ठा csio_scsim *scm = csio_hw_to_scsim(hw);
	काष्ठा fcp_resp_with_ext *fcp_resp;
	काष्ठा fcp_resp_rsp_info *rsp_info;
	काष्ठा csio_dma_buf *dma_buf;
	uपूर्णांक8_t flags, scsi_status = 0;
	uपूर्णांक32_t host_status = DID_OK;
	uपूर्णांक32_t rsp_len = 0, sns_len = 0;
	काष्ठा csio_rnode *rn = (काष्ठा csio_rnode *)(cmnd->device->hostdata);


	चयन (req->wr_status) अणु
	हाल FW_HOSTERROR:
		अगर (unlikely(!csio_is_hw_पढ़ोy(hw)))
			वापस;

		host_status = DID_ERROR;
		CSIO_INC_STATS(scm, n_hosterror);

		अवरोध;
	हाल FW_SCSI_RSP_ERR:
		dma_buf = &req->dma_buf;
		fcp_resp = (काष्ठा fcp_resp_with_ext *)dma_buf->vaddr;
		rsp_info = (काष्ठा fcp_resp_rsp_info *)(fcp_resp + 1);
		flags = fcp_resp->resp.fr_flags;
		scsi_status = fcp_resp->resp.fr_status;

		अगर (flags & FCP_RSP_LEN_VAL) अणु
			rsp_len = be32_to_cpu(fcp_resp->ext.fr_rsp_len);
			अगर ((rsp_len != 0 && rsp_len != 4 && rsp_len != 8) ||
				(rsp_info->rsp_code != FCP_TMF_CMPL)) अणु
				host_status = DID_ERROR;
				जाओ out;
			पूर्ण
		पूर्ण

		अगर ((flags & FCP_SNS_LEN_VAL) && fcp_resp->ext.fr_sns_len) अणु
			sns_len = be32_to_cpu(fcp_resp->ext.fr_sns_len);
			अगर (sns_len > SCSI_SENSE_BUFFERSIZE)
				sns_len = SCSI_SENSE_BUFFERSIZE;

			स_नकल(cmnd->sense_buffer,
			       &rsp_info->_fr_resvd[0] + rsp_len, sns_len);
			CSIO_INC_STATS(scm, n_स्वतःsense);
		पूर्ण

		scsi_set_resid(cmnd, 0);

		/* Under run */
		अगर (flags & FCP_RESID_UNDER) अणु
			scsi_set_resid(cmnd,
				       be32_to_cpu(fcp_resp->ext.fr_resid));

			अगर (!(flags & FCP_SNS_LEN_VAL) &&
			    (scsi_status == SAM_STAT_GOOD) &&
			    ((scsi_bufflen(cmnd) - scsi_get_resid(cmnd))
							< cmnd->underflow))
				host_status = DID_ERROR;
		पूर्ण अन्यथा अगर (flags & FCP_RESID_OVER)
			host_status = DID_ERROR;

		CSIO_INC_STATS(scm, n_rsलिखो_त्रुटि);
		अवरोध;

	हाल FW_SCSI_OVER_FLOW_ERR:
		csio_warn(hw,
			  "Over-flow error,cmnd:0x%x expected len:0x%x"
			  " resid:0x%x\n", cmnd->cmnd[0],
			  scsi_bufflen(cmnd), scsi_get_resid(cmnd));
		host_status = DID_ERROR;
		CSIO_INC_STATS(scm, n_ovflerror);
		अवरोध;

	हाल FW_SCSI_UNDER_FLOW_ERR:
		csio_warn(hw,
			  "Under-flow error,cmnd:0x%x expected"
			  " len:0x%x resid:0x%x lun:0x%llx ssn:0x%x\n",
			  cmnd->cmnd[0], scsi_bufflen(cmnd),
			  scsi_get_resid(cmnd), cmnd->device->lun,
			  rn->flowid);
		host_status = DID_ERROR;
		CSIO_INC_STATS(scm, n_unflerror);
		अवरोध;

	हाल FW_SCSI_ABORT_REQUESTED:
	हाल FW_SCSI_ABORTED:
	हाल FW_SCSI_CLOSE_REQUESTED:
		csio_dbg(hw, "Req %p cmd:%p op:%x %s\n", req, cmnd,
			     cmnd->cmnd[0],
			    (req->wr_status == FW_SCSI_CLOSE_REQUESTED) ?
			    "closed" : "aborted");
		/*
		 * csio_eh_पात_handler checks this value to
		 * succeed or fail the पात request.
		 */
		host_status = DID_REQUEUE;
		अगर (req->wr_status == FW_SCSI_CLOSE_REQUESTED)
			CSIO_INC_STATS(scm, n_बंदd);
		अन्यथा
			CSIO_INC_STATS(scm, n_पातed);
		अवरोध;

	हाल FW_SCSI_ABORT_TIMEDOUT:
		/* FW समयd out the पात itself */
		csio_dbg(hw, "FW timed out abort req:%p cmnd:%p status:%x\n",
			 req, cmnd, req->wr_status);
		host_status = DID_ERROR;
		CSIO_INC_STATS(scm, n_abrt_समयकरोut);
		अवरोध;

	हाल FW_RDEV_NOT_READY:
		/*
		 * In firmware, a RDEV can get पूर्णांकo this state
		 * temporarily, beक्रमe moving पूर्णांकo dissapeared/lost
		 * state. So, the driver should complete the request equivalent
		 * to device-disappeared!
		 */
		CSIO_INC_STATS(scm, n_rdev_nr_error);
		host_status = DID_ERROR;
		अवरोध;

	हाल FW_ERR_RDEV_LOST:
		CSIO_INC_STATS(scm, n_rdev_lost_error);
		host_status = DID_ERROR;
		अवरोध;

	हाल FW_ERR_RDEV_LOGO:
		CSIO_INC_STATS(scm, n_rdev_logo_error);
		host_status = DID_ERROR;
		अवरोध;

	हाल FW_ERR_RDEV_IMPL_LOGO:
		host_status = DID_ERROR;
		अवरोध;

	हाल FW_ERR_LINK_DOWN:
		CSIO_INC_STATS(scm, n_link_करोwn_error);
		host_status = DID_ERROR;
		अवरोध;

	हाल FW_FCOE_NO_XCHG:
		CSIO_INC_STATS(scm, n_no_xchg_error);
		host_status = DID_ERROR;
		अवरोध;

	शेष:
		csio_err(hw, "Unknown SCSI FW WR status:%d req:%p cmnd:%p\n",
			    req->wr_status, req, cmnd);
		CSIO_DB_ASSERT(0);

		CSIO_INC_STATS(scm, n_unknown_error);
		host_status = DID_ERROR;
		अवरोध;
	पूर्ण

out:
	अगर (req->nsge > 0) अणु
		scsi_dma_unmap(cmnd);
		अगर (req->dcopy && (host_status == DID_OK))
			host_status = csio_scsi_copy_to_sgl(hw, req);
	पूर्ण

	cmnd->result = (((host_status) << 16) | scsi_status);
	cmnd->scsi_करोne(cmnd);

	/* Wake up रुकोing thपढ़ोs */
	csio_scsi_cmnd(req) = शून्य;
	complete(&req->cmplobj);
पूर्ण

/*
 * csio_scsi_cbfn - SCSI callback function.
 * @hw: HW module.
 * @req: IO request.
 *
 */
अटल व्योम
csio_scsi_cbfn(काष्ठा csio_hw *hw, काष्ठा csio_ioreq *req)
अणु
	काष्ठा scsi_cmnd *cmnd  = (काष्ठा scsi_cmnd *)csio_scsi_cmnd(req);
	uपूर्णांक8_t scsi_status = SAM_STAT_GOOD;
	uपूर्णांक32_t host_status = DID_OK;

	अगर (likely(req->wr_status == FW_SUCCESS)) अणु
		अगर (req->nsge > 0) अणु
			scsi_dma_unmap(cmnd);
			अगर (req->dcopy)
				host_status = csio_scsi_copy_to_sgl(hw, req);
		पूर्ण

		cmnd->result = (((host_status) << 16) | scsi_status);
		cmnd->scsi_करोne(cmnd);
		csio_scsi_cmnd(req) = शून्य;
		CSIO_INC_STATS(csio_hw_to_scsim(hw), n_tot_success);
	पूर्ण अन्यथा अणु
		/* Error handling */
		csio_scsi_err_handler(hw, req);
	पूर्ण
पूर्ण

/**
 * csio_queuecommand - Entry poपूर्णांक to kickstart an I/O request.
 * @host:	The scsi_host poपूर्णांकer.
 * @cmnd:	The I/O request from ML.
 *
 * This routine करोes the following:
 *	- Checks क्रम HW and Rnode module पढ़ोiness.
 *	- Gets a मुक्त ioreq काष्ठाure (which is alपढ़ोy initialized
 *	  to uninit during its allocation).
 *	- Maps SG elements.
 *	- Initializes ioreq members.
 *	- Kicks off the SCSI state machine क्रम this IO.
 *	- Returns busy status on error.
 */
अटल पूर्णांक
csio_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा csio_lnode *ln = shost_priv(host);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	काष्ठा csio_scsim *scsim = csio_hw_to_scsim(hw);
	काष्ठा csio_rnode *rn = (काष्ठा csio_rnode *)(cmnd->device->hostdata);
	काष्ठा csio_ioreq *ioreq = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक nsge = 0;
	पूर्णांक rv = SCSI_MLQUEUE_HOST_BUSY, nr;
	पूर्णांक retval;
	काष्ठा csio_scsi_qset *sqset;
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(cmnd->device));

	sqset = &hw->sqset[ln->portid][blk_mq_rq_cpu(cmnd->request)];

	nr = fc_remote_port_chkपढ़ोy(rport);
	अगर (nr) अणु
		cmnd->result = nr;
		CSIO_INC_STATS(scsim, n_rn_nr_error);
		जाओ err_करोne;
	पूर्ण

	अगर (unlikely(!csio_is_hw_पढ़ोy(hw))) अणु
		cmnd->result = (DID_REQUEUE << 16);
		CSIO_INC_STATS(scsim, n_hw_nr_error);
		जाओ err_करोne;
	पूर्ण

	/* Get req->nsge, अगर there are SG elements to be mapped  */
	nsge = scsi_dma_map(cmnd);
	अगर (unlikely(nsge < 0)) अणु
		CSIO_INC_STATS(scsim, n_dmamap_error);
		जाओ err;
	पूर्ण

	/* Do we support so many mappings? */
	अगर (unlikely(nsge > scsim->max_sge)) अणु
		csio_warn(hw,
			  "More SGEs than can be supported."
			  " SGEs: %d, Max SGEs: %d\n", nsge, scsim->max_sge);
		CSIO_INC_STATS(scsim, n_unsupp_sge_error);
		जाओ err_dma_unmap;
	पूर्ण

	/* Get a मुक्त ioreq काष्ठाure - SM is alपढ़ोy set to uninit */
	ioreq = csio_get_scsi_ioreq_lock(hw, scsim);
	अगर (!ioreq) अणु
		csio_err(hw, "Out of I/O request elements. Active #:%d\n",
			 scsim->stats.n_active);
		CSIO_INC_STATS(scsim, n_no_req_error);
		जाओ err_dma_unmap;
	पूर्ण

	ioreq->nsge		= nsge;
	ioreq->lnode		= ln;
	ioreq->rnode		= rn;
	ioreq->iq_idx		= sqset->iq_idx;
	ioreq->eq_idx		= sqset->eq_idx;
	ioreq->wr_status	= 0;
	ioreq->drv_status	= 0;
	csio_scsi_cmnd(ioreq)	= (व्योम *)cmnd;
	ioreq->पंचांगo		= 0;
	ioreq->datadir		= cmnd->sc_data_direction;

	अगर (cmnd->sc_data_direction == DMA_TO_DEVICE) अणु
		CSIO_INC_STATS(ln, n_output_requests);
		ln->stats.n_output_bytes += scsi_bufflen(cmnd);
	पूर्ण अन्यथा अगर (cmnd->sc_data_direction == DMA_FROM_DEVICE) अणु
		CSIO_INC_STATS(ln, n_input_requests);
		ln->stats.n_input_bytes += scsi_bufflen(cmnd);
	पूर्ण अन्यथा
		CSIO_INC_STATS(ln, n_control_requests);

	/* Set cbfn */
	ioreq->io_cbfn = csio_scsi_cbfn;

	/* Needed during पात */
	cmnd->host_scribble = (अचिन्हित अक्षर *)ioreq;
	cmnd->SCp.Message = 0;

	/* Kick off SCSI IO SM on the ioreq */
	spin_lock_irqsave(&hw->lock, flags);
	retval = csio_scsi_start_io(ioreq);
	spin_unlock_irqrestore(&hw->lock, flags);

	अगर (retval != 0) अणु
		csio_err(hw, "ioreq: %p couldn't be started, status:%d\n",
			 ioreq, retval);
		CSIO_INC_STATS(scsim, n_busy_error);
		जाओ err_put_req;
	पूर्ण

	वापस 0;

err_put_req:
	csio_put_scsi_ioreq_lock(hw, scsim, ioreq);
err_dma_unmap:
	अगर (nsge > 0)
		scsi_dma_unmap(cmnd);
err:
	वापस rv;

err_करोne:
	cmnd->scsi_करोne(cmnd);
	वापस 0;
पूर्ण

अटल पूर्णांक
csio_करो_abrt_cls(काष्ठा csio_hw *hw, काष्ठा csio_ioreq *ioreq, bool पात)
अणु
	पूर्णांक rv;
	पूर्णांक cpu = smp_processor_id();
	काष्ठा csio_lnode *ln = ioreq->lnode;
	काष्ठा csio_scsi_qset *sqset = &hw->sqset[ln->portid][cpu];

	ioreq->पंचांगo = CSIO_SCSI_ABRT_TMO_MS;
	/*
	 * Use current processor queue क्रम posting the पात/बंद, but retain
	 * the ingress queue ID of the original I/O being पातed/बंदd - we
	 * need the पात/बंद completion to be received on the same queue
	 * as the original I/O.
	 */
	ioreq->eq_idx = sqset->eq_idx;

	अगर (पात == SCSI_ABORT)
		rv = csio_scsi_पात(ioreq);
	अन्यथा
		rv = csio_scsi_बंद(ioreq);

	वापस rv;
पूर्ण

अटल पूर्णांक
csio_eh_पात_handler(काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा csio_ioreq *ioreq;
	काष्ठा csio_lnode *ln = shost_priv(cmnd->device->host);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	काष्ठा csio_scsim *scsim = csio_hw_to_scsim(hw);
	पूर्णांक पढ़ोy = 0, ret;
	अचिन्हित दीर्घ पंचांगo = 0;
	पूर्णांक rv;
	काष्ठा csio_rnode *rn = (काष्ठा csio_rnode *)(cmnd->device->hostdata);

	ret = fc_block_scsi_eh(cmnd);
	अगर (ret)
		वापस ret;

	ioreq = (काष्ठा csio_ioreq *)cmnd->host_scribble;
	अगर (!ioreq)
		वापस SUCCESS;

	अगर (!rn)
		वापस FAILED;

	csio_dbg(hw,
		 "Request to abort ioreq:%p cmd:%p cdb:%08llx"
		 " ssni:0x%x lun:%llu iq:0x%x\n",
		ioreq, cmnd, *((uपूर्णांक64_t *)cmnd->cmnd), rn->flowid,
		cmnd->device->lun, csio_q_physiqid(hw, ioreq->iq_idx));

	अगर (((काष्ठा scsi_cmnd *)csio_scsi_cmnd(ioreq)) != cmnd) अणु
		CSIO_INC_STATS(scsim, n_abrt_race_comp);
		वापस SUCCESS;
	पूर्ण

	पढ़ोy = csio_is_lnode_पढ़ोy(ln);
	पंचांगo = CSIO_SCSI_ABRT_TMO_MS;

	reinit_completion(&ioreq->cmplobj);
	spin_lock_irq(&hw->lock);
	rv = csio_करो_abrt_cls(hw, ioreq, (पढ़ोy ? SCSI_ABORT : SCSI_CLOSE));
	spin_unlock_irq(&hw->lock);

	अगर (rv != 0) अणु
		अगर (rv == -EINVAL) अणु
			/* Return success, अगर पात/बंद request issued on
			 * alपढ़ोy completed IO
			 */
			वापस SUCCESS;
		पूर्ण
		अगर (पढ़ोy)
			CSIO_INC_STATS(scsim, n_abrt_busy_error);
		अन्यथा
			CSIO_INC_STATS(scsim, n_cls_busy_error);

		जाओ inval_scmnd;
	पूर्ण

	रुको_क्रम_completion_समयout(&ioreq->cmplobj, msecs_to_jअगरfies(पंचांगo));

	/* FW didnt respond to पात within our समयout */
	अगर (((काष्ठा scsi_cmnd *)csio_scsi_cmnd(ioreq)) == cmnd) अणु

		csio_err(hw, "Abort timed out -- req: %p\n", ioreq);
		CSIO_INC_STATS(scsim, n_abrt_समयकरोut);

inval_scmnd:
		अगर (ioreq->nsge > 0)
			scsi_dma_unmap(cmnd);

		spin_lock_irq(&hw->lock);
		csio_scsi_cmnd(ioreq) = शून्य;
		spin_unlock_irq(&hw->lock);

		cmnd->result = (DID_ERROR << 16);
		cmnd->scsi_करोne(cmnd);

		वापस FAILED;
	पूर्ण

	/* FW successfully पातed the request */
	अगर (host_byte(cmnd->result) == DID_REQUEUE) अणु
		csio_info(hw,
			"Aborted SCSI command to (%d:%llu) tag %u\n",
			cmnd->device->id, cmnd->device->lun,
			cmnd->request->tag);
		वापस SUCCESS;
	पूर्ण अन्यथा अणु
		csio_info(hw,
			"Failed to abort SCSI command, (%d:%llu) tag %u\n",
			cmnd->device->id, cmnd->device->lun,
			cmnd->request->tag);
		वापस FAILED;
	पूर्ण
पूर्ण

/*
 * csio_पंचांग_cbfn - TM callback function.
 * @hw: HW module.
 * @req: IO request.
 *
 * Cache the result in 'cmnd', since ioreq will be मुक्तd soon
 * after we वापस from here, and the रुकोing thपढ़ो shouldnt trust
 * the ioreq contents.
 */
अटल व्योम
csio_पंचांग_cbfn(काष्ठा csio_hw *hw, काष्ठा csio_ioreq *req)
अणु
	काष्ठा scsi_cmnd *cmnd  = (काष्ठा scsi_cmnd *)csio_scsi_cmnd(req);
	काष्ठा csio_dma_buf *dma_buf;
	uपूर्णांक8_t flags = 0;
	काष्ठा fcp_resp_with_ext *fcp_resp;
	काष्ठा fcp_resp_rsp_info *rsp_info;

	csio_dbg(hw, "req: %p in csio_tm_cbfn status: %d\n",
		      req, req->wr_status);

	/* Cache FW वापस status */
	cmnd->SCp.Status = req->wr_status;

	/* Special handling based on FCP response */

	/*
	 * FW वापसs us this error, अगर flags were set. FCP4 says
	 * FCP_RSP_LEN_VAL in flags shall be set क्रम TM completions.
	 * So अगर a target were to set this bit, we expect that the
	 * rsp_code is set to FCP_TMF_CMPL क्रम a successful TM
	 * completion. Any other rsp_code means TM operation failed.
	 * If a target were to just ignore setting flags, we treat
	 * the TM operation as success, and FW वापसs FW_SUCCESS.
	 */
	अगर (req->wr_status == FW_SCSI_RSP_ERR) अणु
		dma_buf = &req->dma_buf;
		fcp_resp = (काष्ठा fcp_resp_with_ext *)dma_buf->vaddr;
		rsp_info = (काष्ठा fcp_resp_rsp_info *)(fcp_resp + 1);

		flags = fcp_resp->resp.fr_flags;

		/* Modअगरy वापस status अगर flags indicate success */
		अगर (flags & FCP_RSP_LEN_VAL)
			अगर (rsp_info->rsp_code == FCP_TMF_CMPL)
				cmnd->SCp.Status = FW_SUCCESS;

		csio_dbg(hw, "TM FCP rsp code: %d\n", rsp_info->rsp_code);
	पूर्ण

	/* Wake up the TM handler thपढ़ो */
	csio_scsi_cmnd(req) = शून्य;
पूर्ण

अटल पूर्णांक
csio_eh_lun_reset_handler(काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा csio_lnode *ln = shost_priv(cmnd->device->host);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	काष्ठा csio_scsim *scsim = csio_hw_to_scsim(hw);
	काष्ठा csio_rnode *rn = (काष्ठा csio_rnode *)(cmnd->device->hostdata);
	काष्ठा csio_ioreq *ioreq = शून्य;
	काष्ठा csio_scsi_qset *sqset;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;
	पूर्णांक count, ret;
	LIST_HEAD(local_q);
	काष्ठा csio_scsi_level_data sld;

	अगर (!rn)
		जाओ fail;

	csio_dbg(hw, "Request to reset LUN:%llu (ssni:0x%x tgtid:%d)\n",
		      cmnd->device->lun, rn->flowid, rn->scsi_id);

	अगर (!csio_is_lnode_पढ़ोy(ln)) अणु
		csio_err(hw,
			 "LUN reset cannot be issued on non-ready"
			 " local node vnpi:0x%x (LUN:%llu)\n",
			 ln->vnp_flowid, cmnd->device->lun);
		जाओ fail;
	पूर्ण

	/* Lnode is पढ़ोy, now रुको on rport node पढ़ोiness */
	ret = fc_block_scsi_eh(cmnd);
	अगर (ret)
		वापस ret;

	/*
	 * If we have blocked in the previous call, at this poपूर्णांक, either the
	 * remote node has come back online, or device loss समयr has fired
	 * and the remote node is destroyed. Allow the LUN reset only क्रम
	 * the क्रमmer हाल, since LUN reset is a TMF I/O on the wire, and we
	 * need a valid session to issue it.
	 */
	अगर (fc_remote_port_chkपढ़ोy(rn->rport)) अणु
		csio_err(hw,
			 "LUN reset cannot be issued on non-ready"
			 " remote node ssni:0x%x (LUN:%llu)\n",
			 rn->flowid, cmnd->device->lun);
		जाओ fail;
	पूर्ण

	/* Get a मुक्त ioreq काष्ठाure - SM is alपढ़ोy set to uninit */
	ioreq = csio_get_scsi_ioreq_lock(hw, scsim);

	अगर (!ioreq) अणु
		csio_err(hw, "Out of IO request elements. Active # :%d\n",
			 scsim->stats.n_active);
		जाओ fail;
	पूर्ण

	sqset			= &hw->sqset[ln->portid][smp_processor_id()];
	ioreq->nsge		= 0;
	ioreq->lnode		= ln;
	ioreq->rnode		= rn;
	ioreq->iq_idx		= sqset->iq_idx;
	ioreq->eq_idx		= sqset->eq_idx;

	csio_scsi_cmnd(ioreq)	= cmnd;
	cmnd->host_scribble	= (अचिन्हित अक्षर *)ioreq;
	cmnd->SCp.Status	= 0;

	cmnd->SCp.Message	= FCP_TMF_LUN_RESET;
	ioreq->पंचांगo		= CSIO_SCSI_LUNRST_TMO_MS / 1000;

	/*
	 * FW बार the LUN reset क्रम ioreq->पंचांगo, so we got to रुको a little
	 * दीर्घer (10s क्रम now) than that to allow FW to वापस the समयd
	 * out command.
	 */
	count = DIV_ROUND_UP((ioreq->पंचांगo + 10) * 1000, CSIO_SCSI_TM_POLL_MS);

	/* Set cbfn */
	ioreq->io_cbfn = csio_पंचांग_cbfn;

	/* Save of the ioreq info क्रम later use */
	sld.level = CSIO_LEV_LUN;
	sld.lnode = ioreq->lnode;
	sld.rnode = ioreq->rnode;
	sld.oslun = cmnd->device->lun;

	spin_lock_irqsave(&hw->lock, flags);
	/* Kick off TM SM on the ioreq */
	retval = csio_scsi_start_पंचांग(ioreq);
	spin_unlock_irqrestore(&hw->lock, flags);

	अगर (retval != 0) अणु
		csio_err(hw, "Failed to issue LUN reset, req:%p, status:%d\n",
			    ioreq, retval);
		जाओ fail_ret_ioreq;
	पूर्ण

	csio_dbg(hw, "Waiting max %d secs for LUN reset completion\n",
		    count * (CSIO_SCSI_TM_POLL_MS / 1000));
	/* Wait क्रम completion */
	जबतक ((((काष्ठा scsi_cmnd *)csio_scsi_cmnd(ioreq)) == cmnd)
								&& count--)
		msleep(CSIO_SCSI_TM_POLL_MS);

	/* LUN reset समयd-out */
	अगर (((काष्ठा scsi_cmnd *)csio_scsi_cmnd(ioreq)) == cmnd) अणु
		csio_err(hw, "LUN reset (%d:%llu) timed out\n",
			 cmnd->device->id, cmnd->device->lun);

		spin_lock_irq(&hw->lock);
		csio_scsi_drvcleanup(ioreq);
		list_del_init(&ioreq->sm.sm_list);
		spin_unlock_irq(&hw->lock);

		जाओ fail_ret_ioreq;
	पूर्ण

	/* LUN reset वापसed, check cached status */
	अगर (cmnd->SCp.Status != FW_SUCCESS) अणु
		csio_err(hw, "LUN reset failed (%d:%llu), status: %d\n",
			 cmnd->device->id, cmnd->device->lun, cmnd->SCp.Status);
		जाओ fail;
	पूर्ण

	/* LUN reset succeeded, Start पातing affected I/Os */
	/*
	 * Since the host guarantees during LUN reset that there
	 * will not be any more I/Os to that LUN, until the LUN reset
	 * completes, we gather pending I/Os after the LUN reset.
	 */
	spin_lock_irq(&hw->lock);
	csio_scsi_gather_active_ios(scsim, &sld, &local_q);

	retval = csio_scsi_पात_io_q(scsim, &local_q, 30000);
	spin_unlock_irq(&hw->lock);

	/* Aborts may have समयd out */
	अगर (retval != 0) अणु
		csio_err(hw,
			 "Attempt to abort I/Os during LUN reset of %llu"
			 " returned %d\n", cmnd->device->lun, retval);
		/* Return I/Os back to active_q */
		spin_lock_irq(&hw->lock);
		list_splice_tail_init(&local_q, &scsim->active_q);
		spin_unlock_irq(&hw->lock);
		जाओ fail;
	पूर्ण

	CSIO_INC_STATS(rn, n_lun_rst);

	csio_info(hw, "LUN reset occurred (%d:%llu)\n",
		  cmnd->device->id, cmnd->device->lun);

	वापस SUCCESS;

fail_ret_ioreq:
	csio_put_scsi_ioreq_lock(hw, scsim, ioreq);
fail:
	CSIO_INC_STATS(rn, n_lun_rst_fail);
	वापस FAILED;
पूर्ण

अटल पूर्णांक
csio_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));

	अगर (!rport || fc_remote_port_chkपढ़ोy(rport))
		वापस -ENXIO;

	sdev->hostdata = *((काष्ठा csio_lnode **)(rport->dd_data));

	वापस 0;
पूर्ण

अटल पूर्णांक
csio_slave_configure(काष्ठा scsi_device *sdev)
अणु
	scsi_change_queue_depth(sdev, csio_lun_qdepth);
	वापस 0;
पूर्ण

अटल व्योम
csio_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	sdev->hostdata = शून्य;
पूर्ण

अटल पूर्णांक
csio_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय)
अणु
	काष्ठा csio_lnode *ln = shost_priv(shost);
	पूर्णांक rv = 1;

	spin_lock_irq(shost->host_lock);
	अगर (!ln->hwp || csio_list_deleted(&ln->sm.sm_list))
		जाओ out;

	rv = csio_scan_करोne(ln, jअगरfies, समय, csio_max_scan_पंचांगo * HZ,
			    csio_delta_scan_पंचांगo * HZ);
out:
	spin_unlock_irq(shost->host_lock);

	वापस rv;
पूर्ण

काष्ठा scsi_host_ढाँचा csio_fcoe_shost_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= CSIO_DRV_DESC,
	.proc_name		= KBUILD_MODNAME,
	.queuecommand		= csio_queuecommand,
	.eh_समयd_out		= fc_eh_समयd_out,
	.eh_पात_handler	= csio_eh_पात_handler,
	.eh_device_reset_handler = csio_eh_lun_reset_handler,
	.slave_alloc		= csio_slave_alloc,
	.slave_configure	= csio_slave_configure,
	.slave_destroy		= csio_slave_destroy,
	.scan_finished		= csio_scan_finished,
	.this_id		= -1,
	.sg_tablesize		= CSIO_SCSI_MAX_SGE,
	.cmd_per_lun		= CSIO_MAX_CMD_PER_LUN,
	.shost_attrs		= csio_fcoe_lport_attrs,
	.max_sectors		= CSIO_MAX_SECTOR_SIZE,
पूर्ण;

काष्ठा scsi_host_ढाँचा csio_fcoe_shost_vport_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= CSIO_DRV_DESC,
	.proc_name		= KBUILD_MODNAME,
	.queuecommand		= csio_queuecommand,
	.eh_समयd_out		= fc_eh_समयd_out,
	.eh_पात_handler	= csio_eh_पात_handler,
	.eh_device_reset_handler = csio_eh_lun_reset_handler,
	.slave_alloc		= csio_slave_alloc,
	.slave_configure	= csio_slave_configure,
	.slave_destroy		= csio_slave_destroy,
	.scan_finished		= csio_scan_finished,
	.this_id		= -1,
	.sg_tablesize		= CSIO_SCSI_MAX_SGE,
	.cmd_per_lun		= CSIO_MAX_CMD_PER_LUN,
	.shost_attrs		= csio_fcoe_vport_attrs,
	.max_sectors		= CSIO_MAX_SECTOR_SIZE,
पूर्ण;

/*
 * csio_scsi_alloc_ddp_bufs - Allocate buffers क्रम DDP of unaligned SGLs.
 * @scm: SCSI Module
 * @hw: HW device.
 * @buf_size: buffer size
 * @num_buf : Number of buffers.
 *
 * This routine allocates DMA buffers required क्रम SCSI Data xfer, अगर
 * each SGL buffer क्रम a SCSI Read request posted by SCSI midlayer are
 * not भवly contiguous.
 */
अटल पूर्णांक
csio_scsi_alloc_ddp_bufs(काष्ठा csio_scsim *scm, काष्ठा csio_hw *hw,
			 पूर्णांक buf_size, पूर्णांक num_buf)
अणु
	पूर्णांक n = 0;
	काष्ठा list_head *पंचांगp;
	काष्ठा csio_dma_buf *ddp_desc = शून्य;
	uपूर्णांक32_t unit_size = 0;

	अगर (!num_buf)
		वापस 0;

	अगर (!buf_size)
		वापस -EINVAL;

	INIT_LIST_HEAD(&scm->ddp_मुक्तlist);

	/* Align buf size to page size */
	buf_size = (buf_size + PAGE_SIZE - 1) & PAGE_MASK;
	/* Initialize dma descriptors */
	क्रम (n = 0; n < num_buf; n++) अणु
		/* Set unit size to request size */
		unit_size = buf_size;
		ddp_desc = kzalloc(माप(काष्ठा csio_dma_buf), GFP_KERNEL);
		अगर (!ddp_desc) अणु
			csio_err(hw,
				 "Failed to allocate ddp descriptors,"
				 " Num allocated = %d.\n",
				 scm->stats.n_मुक्त_ddp);
			जाओ no_mem;
		पूर्ण

		/* Allocate Dma buffers क्रम DDP */
		ddp_desc->vaddr = dma_alloc_coherent(&hw->pdev->dev, unit_size,
				&ddp_desc->paddr, GFP_KERNEL);
		अगर (!ddp_desc->vaddr) अणु
			csio_err(hw,
				 "SCSI response DMA buffer (ddp) allocation"
				 " failed!\n");
			kमुक्त(ddp_desc);
			जाओ no_mem;
		पूर्ण

		ddp_desc->len = unit_size;

		/* Added it to scsi ddp मुक्तlist */
		list_add_tail(&ddp_desc->list, &scm->ddp_मुक्तlist);
		CSIO_INC_STATS(scm, n_मुक्त_ddp);
	पूर्ण

	वापस 0;
no_mem:
	/* release dma descs back to मुक्तlist and मुक्त dma memory */
	list_क्रम_each(पंचांगp, &scm->ddp_मुक्तlist) अणु
		ddp_desc = (काष्ठा csio_dma_buf *) पंचांगp;
		पंचांगp = csio_list_prev(पंचांगp);
		dma_मुक्त_coherent(&hw->pdev->dev, ddp_desc->len,
				  ddp_desc->vaddr, ddp_desc->paddr);
		list_del_init(&ddp_desc->list);
		kमुक्त(ddp_desc);
	पूर्ण
	scm->stats.n_मुक्त_ddp = 0;

	वापस -ENOMEM;
पूर्ण

/*
 * csio_scsi_मुक्त_ddp_bufs - मुक्त DDP buffers of unaligned SGLs.
 * @scm: SCSI Module
 * @hw: HW device.
 *
 * This routine मुक्तs ddp buffers.
 */
अटल व्योम
csio_scsi_मुक्त_ddp_bufs(काष्ठा csio_scsim *scm, काष्ठा csio_hw *hw)
अणु
	काष्ठा list_head *पंचांगp;
	काष्ठा csio_dma_buf *ddp_desc;

	/* release dma descs back to मुक्तlist and मुक्त dma memory */
	list_क्रम_each(पंचांगp, &scm->ddp_मुक्तlist) अणु
		ddp_desc = (काष्ठा csio_dma_buf *) पंचांगp;
		पंचांगp = csio_list_prev(पंचांगp);
		dma_मुक्त_coherent(&hw->pdev->dev, ddp_desc->len,
				  ddp_desc->vaddr, ddp_desc->paddr);
		list_del_init(&ddp_desc->list);
		kमुक्त(ddp_desc);
	पूर्ण
	scm->stats.n_मुक्त_ddp = 0;
पूर्ण

/**
 * csio_scsim_init - Initialize SCSI Module
 * @scm:	SCSI Module
 * @hw:		HW module
 *
 */
पूर्णांक
csio_scsim_init(काष्ठा csio_scsim *scm, काष्ठा csio_hw *hw)
अणु
	पूर्णांक i;
	काष्ठा csio_ioreq *ioreq;
	काष्ठा csio_dma_buf *dma_buf;

	INIT_LIST_HEAD(&scm->active_q);
	scm->hw = hw;

	scm->proto_cmd_len = माप(काष्ठा fcp_cmnd);
	scm->proto_rsp_len = CSIO_SCSI_RSP_LEN;
	scm->max_sge = CSIO_SCSI_MAX_SGE;

	spin_lock_init(&scm->मुक्तlist_lock);

	/* Pre-allocate ioreqs and initialize them */
	INIT_LIST_HEAD(&scm->ioreq_मुक्तlist);
	क्रम (i = 0; i < csio_scsi_ioreqs; i++) अणु

		ioreq = kzalloc(माप(काष्ठा csio_ioreq), GFP_KERNEL);
		अगर (!ioreq) अणु
			csio_err(hw,
				 "I/O request element allocation failed, "
				 " Num allocated = %d.\n",
				 scm->stats.n_मुक्त_ioreq);

			जाओ मुक्त_ioreq;
		पूर्ण

		/* Allocate Dma buffers क्रम Response Payload */
		dma_buf = &ioreq->dma_buf;
		dma_buf->vaddr = dma_pool_alloc(hw->scsi_dma_pool, GFP_KERNEL,
						&dma_buf->paddr);
		अगर (!dma_buf->vaddr) अणु
			csio_err(hw,
				 "SCSI response DMA buffer allocation"
				 " failed!\n");
			kमुक्त(ioreq);
			जाओ मुक्त_ioreq;
		पूर्ण

		dma_buf->len = scm->proto_rsp_len;

		/* Set state to uninit */
		csio_init_state(&ioreq->sm, csio_scsis_uninit);
		INIT_LIST_HEAD(&ioreq->gen_list);
		init_completion(&ioreq->cmplobj);

		list_add_tail(&ioreq->sm.sm_list, &scm->ioreq_मुक्तlist);
		CSIO_INC_STATS(scm, n_मुक्त_ioreq);
	पूर्ण

	अगर (csio_scsi_alloc_ddp_bufs(scm, hw, PAGE_SIZE, csio_ddp_descs))
		जाओ मुक्त_ioreq;

	वापस 0;

मुक्त_ioreq:
	/*
	 * Free up existing allocations, since an error
	 * from here means we are वापसing क्रम good
	 */
	जबतक (!list_empty(&scm->ioreq_मुक्तlist)) अणु
		काष्ठा csio_sm *पंचांगp;

		पंचांगp = list_first_entry(&scm->ioreq_मुक्तlist,
				       काष्ठा csio_sm, sm_list);
		list_del_init(&पंचांगp->sm_list);
		ioreq = (काष्ठा csio_ioreq *)पंचांगp;

		dma_buf = &ioreq->dma_buf;
		dma_pool_मुक्त(hw->scsi_dma_pool, dma_buf->vaddr,
			      dma_buf->paddr);

		kमुक्त(ioreq);
	पूर्ण

	scm->stats.n_मुक्त_ioreq = 0;

	वापस -ENOMEM;
पूर्ण

/**
 * csio_scsim_निकास: Uninitialize SCSI Module
 * @scm: SCSI Module
 *
 */
व्योम
csio_scsim_निकास(काष्ठा csio_scsim *scm)
अणु
	काष्ठा csio_ioreq *ioreq;
	काष्ठा csio_dma_buf *dma_buf;

	जबतक (!list_empty(&scm->ioreq_मुक्तlist)) अणु
		काष्ठा csio_sm *पंचांगp;

		पंचांगp = list_first_entry(&scm->ioreq_मुक्तlist,
				       काष्ठा csio_sm, sm_list);
		list_del_init(&पंचांगp->sm_list);
		ioreq = (काष्ठा csio_ioreq *)पंचांगp;

		dma_buf = &ioreq->dma_buf;
		dma_pool_मुक्त(scm->hw->scsi_dma_pool, dma_buf->vaddr,
			      dma_buf->paddr);

		kमुक्त(ioreq);
	पूर्ण

	scm->stats.n_मुक्त_ioreq = 0;

	csio_scsi_मुक्त_ddp_bufs(scm, scm->hw);
पूर्ण
