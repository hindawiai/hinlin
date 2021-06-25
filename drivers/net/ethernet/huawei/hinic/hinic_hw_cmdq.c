<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sizes.h>
#समावेश <linux/atomic.h>
#समावेश <linux/log2.h>
#समावेश <linux/पन.स>
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/barrier.h>

#समावेश "hinic_common.h"
#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_eqs.h"
#समावेश "hinic_hw_mgmt.h"
#समावेश "hinic_hw_wqe.h"
#समावेश "hinic_hw_wq.h"
#समावेश "hinic_hw_cmdq.h"
#समावेश "hinic_hw_io.h"
#समावेश "hinic_hw_dev.h"

#घोषणा CMDQ_CEQE_TYPE_SHIFT                    0

#घोषणा CMDQ_CEQE_TYPE_MASK                     0x7

#घोषणा CMDQ_CEQE_GET(val, member)              \
			(((val) >> CMDQ_CEQE_##member##_SHIFT) \
			 & CMDQ_CEQE_##member##_MASK)

#घोषणा CMDQ_WQE_ERRCODE_VAL_SHIFT              20

#घोषणा CMDQ_WQE_ERRCODE_VAL_MASK               0xF

#घोषणा CMDQ_WQE_ERRCODE_GET(val, member)       \
			(((val) >> CMDQ_WQE_ERRCODE_##member##_SHIFT) \
			 & CMDQ_WQE_ERRCODE_##member##_MASK)

#घोषणा CMDQ_DB_PI_OFF(pi)              (((u16)LOWER_8_BITS(pi)) << 3)

#घोषणा CMDQ_DB_ADDR(db_base, pi)       ((db_base) + CMDQ_DB_PI_OFF(pi))

#घोषणा CMDQ_WQE_HEADER(wqe)            ((काष्ठा hinic_cmdq_header *)(wqe))

#घोषणा CMDQ_WQE_COMPLETED(ctrl_info)   \
			HINIC_CMDQ_CTRL_GET(ctrl_info, HW_BUSY_BIT)

#घोषणा FIRST_DATA_TO_WRITE_LAST        माप(u64)

#घोषणा CMDQ_DB_OFF                     SZ_2K

#घोषणा CMDQ_WQEBB_SIZE                 64
#घोषणा CMDQ_WQE_SIZE                   64
#घोषणा CMDQ_DEPTH                      SZ_4K

#घोषणा CMDQ_WQ_PAGE_SIZE               SZ_256K

#घोषणा WQE_LCMD_SIZE                   64
#घोषणा WQE_SCMD_SIZE                   64

#घोषणा COMPLETE_LEN                    3

#घोषणा CMDQ_TIMEOUT                    1000

#घोषणा CMDQ_PFN(addr, page_size)       ((addr) >> (ilog2(page_size)))

#घोषणा cmdq_to_cmdqs(cmdq)     container_of((cmdq) - (cmdq)->cmdq_type, \
					     काष्ठा hinic_cmdqs, cmdq[0])

#घोषणा cmdqs_to_func_to_io(cmdqs)      container_of(cmdqs, \
						     काष्ठा hinic_func_to_io, \
						     cmdqs)

क्रमागत cmdq_wqe_type अणु
	WQE_LCMD_TYPE = 0,
	WQE_SCMD_TYPE = 1,
पूर्ण;

क्रमागत completion_क्रमmat अणु
	COMPLETE_सूचीECT = 0,
	COMPLETE_SGE    = 1,
पूर्ण;

क्रमागत data_क्रमmat अणु
	DATA_SGE        = 0,
	DATA_सूचीECT     = 1,
पूर्ण;

क्रमागत bufdesc_len अणु
	BUFDESC_LCMD_LEN = 2,   /* 16 bytes - 2(8 byte unit) */
	BUFDESC_SCMD_LEN = 3,   /* 24 bytes - 3(8 byte unit) */
पूर्ण;

क्रमागत ctrl_sect_len अणु
	CTRL_SECT_LEN        = 1, /* 4 bytes (ctrl) - 1(8 byte unit) */
	CTRL_सूचीECT_SECT_LEN = 2, /* 12 bytes (ctrl + rsvd) - 2(8 byte unit) */
पूर्ण;

क्रमागत cmdq_scmd_type अणु
	CMDQ_SET_ARM_CMD = 2,
पूर्ण;

क्रमागत cmdq_cmd_type अणु
	CMDQ_CMD_SYNC_सूचीECT_RESP = 0,
	CMDQ_CMD_SYNC_SGE_RESP    = 1,
पूर्ण;

क्रमागत completion_request अणु
	NO_CEQ  = 0,
	CEQ_SET = 1,
पूर्ण;

/**
 * hinic_alloc_cmdq_buf - alloc buffer क्रम sending command
 * @cmdqs: the cmdqs
 * @cmdq_buf: the buffer वापसed in this काष्ठा
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_alloc_cmdq_buf(काष्ठा hinic_cmdqs *cmdqs,
			 काष्ठा hinic_cmdq_buf *cmdq_buf)
अणु
	काष्ठा hinic_hwअगर *hwअगर = cmdqs->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;

	cmdq_buf->buf = dma_pool_alloc(cmdqs->cmdq_buf_pool, GFP_KERNEL,
				       &cmdq_buf->dma_addr);
	अगर (!cmdq_buf->buf) अणु
		dev_err(&pdev->dev, "Failed to allocate cmd from the pool\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hinic_मुक्त_cmdq_buf - मुक्त buffer
 * @cmdqs: the cmdqs
 * @cmdq_buf: the buffer to मुक्त that is in this काष्ठा
 **/
व्योम hinic_मुक्त_cmdq_buf(काष्ठा hinic_cmdqs *cmdqs,
			 काष्ठा hinic_cmdq_buf *cmdq_buf)
अणु
	dma_pool_मुक्त(cmdqs->cmdq_buf_pool, cmdq_buf->buf, cmdq_buf->dma_addr);
पूर्ण

अटल अचिन्हित पूर्णांक cmdq_wqe_size_from_bdlen(क्रमागत bufdesc_len len)
अणु
	अचिन्हित पूर्णांक wqe_size = 0;

	चयन (len) अणु
	हाल BUFDESC_LCMD_LEN:
		wqe_size = WQE_LCMD_SIZE;
		अवरोध;
	हाल BUFDESC_SCMD_LEN:
		wqe_size = WQE_SCMD_SIZE;
		अवरोध;
	पूर्ण

	वापस wqe_size;
पूर्ण

अटल व्योम cmdq_set_sge_completion(काष्ठा hinic_cmdq_completion *completion,
				    काष्ठा hinic_cmdq_buf *buf_out)
अणु
	काष्ठा hinic_sge_resp *sge_resp = &completion->sge_resp;

	hinic_set_sge(&sge_resp->sge, buf_out->dma_addr, buf_out->size);
पूर्ण

अटल व्योम cmdq_prepare_wqe_ctrl(काष्ठा hinic_cmdq_wqe *wqe, पूर्णांक wrapped,
				  क्रमागत hinic_cmd_ack_type ack_type,
				  क्रमागत hinic_mod_type mod, u8 cmd, u16 prod_idx,
				  क्रमागत completion_क्रमmat complete_क्रमmat,
				  क्रमागत data_क्रमmat data_क्रमmat,
				  क्रमागत bufdesc_len buf_len)
अणु
	काष्ठा hinic_cmdq_wqe_lcmd *wqe_lcmd;
	काष्ठा hinic_cmdq_wqe_scmd *wqe_scmd;
	क्रमागत ctrl_sect_len ctrl_len;
	काष्ठा hinic_ctrl *ctrl;
	u32 saved_data;

	अगर (data_क्रमmat == DATA_SGE) अणु
		wqe_lcmd = &wqe->wqe_lcmd;

		wqe_lcmd->status.status_info = 0;
		ctrl = &wqe_lcmd->ctrl;
		ctrl_len = CTRL_SECT_LEN;
	पूर्ण अन्यथा अणु
		wqe_scmd = &wqe->direct_wqe.wqe_scmd;

		wqe_scmd->status.status_info = 0;
		ctrl = &wqe_scmd->ctrl;
		ctrl_len = CTRL_सूचीECT_SECT_LEN;
	पूर्ण

	ctrl->ctrl_info = HINIC_CMDQ_CTRL_SET(prod_idx, PI)             |
			  HINIC_CMDQ_CTRL_SET(cmd, CMD)                 |
			  HINIC_CMDQ_CTRL_SET(mod, MOD)                 |
			  HINIC_CMDQ_CTRL_SET(ack_type, ACK_TYPE);

	CMDQ_WQE_HEADER(wqe)->header_info =
		HINIC_CMDQ_WQE_HEADER_SET(buf_len, BUFDESC_LEN)            |
		HINIC_CMDQ_WQE_HEADER_SET(complete_क्रमmat, COMPLETE_FMT)   |
		HINIC_CMDQ_WQE_HEADER_SET(data_क्रमmat, DATA_FMT)           |
		HINIC_CMDQ_WQE_HEADER_SET(CEQ_SET, COMPLETE_REQ)           |
		HINIC_CMDQ_WQE_HEADER_SET(COMPLETE_LEN, COMPLETE_SECT_LEN) |
		HINIC_CMDQ_WQE_HEADER_SET(ctrl_len, CTRL_LEN)              |
		HINIC_CMDQ_WQE_HEADER_SET(wrapped, TOGGLED_WRAPPED);

	saved_data = CMDQ_WQE_HEADER(wqe)->saved_data;
	saved_data = HINIC_SAVED_DATA_CLEAR(saved_data, ARM);

	अगर ((cmd == CMDQ_SET_ARM_CMD) && (mod == HINIC_MOD_COMM))
		CMDQ_WQE_HEADER(wqe)->saved_data |=
						HINIC_SAVED_DATA_SET(1, ARM);
	अन्यथा
		CMDQ_WQE_HEADER(wqe)->saved_data = saved_data;
पूर्ण

अटल व्योम cmdq_set_lcmd_bufdesc(काष्ठा hinic_cmdq_wqe_lcmd *wqe_lcmd,
				  काष्ठा hinic_cmdq_buf *buf_in)
अणु
	hinic_set_sge(&wqe_lcmd->buf_desc.sge, buf_in->dma_addr, buf_in->size);
पूर्ण

अटल व्योम cmdq_set_direct_wqe_data(काष्ठा hinic_cmdq_direct_wqe *wqe,
				     व्योम *buf_in, u32 in_size)
अणु
	काष्ठा hinic_cmdq_wqe_scmd *wqe_scmd = &wqe->wqe_scmd;

	wqe_scmd->buf_desc.buf_len = in_size;
	स_नकल(wqe_scmd->buf_desc.data, buf_in, in_size);
पूर्ण

अटल व्योम cmdq_set_lcmd_wqe(काष्ठा hinic_cmdq_wqe *wqe,
			      क्रमागत cmdq_cmd_type cmd_type,
			      काष्ठा hinic_cmdq_buf *buf_in,
			      काष्ठा hinic_cmdq_buf *buf_out, पूर्णांक wrapped,
			      क्रमागत hinic_cmd_ack_type ack_type,
			      क्रमागत hinic_mod_type mod, u8 cmd, u16 prod_idx)
अणु
	काष्ठा hinic_cmdq_wqe_lcmd *wqe_lcmd = &wqe->wqe_lcmd;
	क्रमागत completion_क्रमmat complete_क्रमmat;

	चयन (cmd_type) अणु
	हाल CMDQ_CMD_SYNC_SGE_RESP:
		complete_क्रमmat = COMPLETE_SGE;
		cmdq_set_sge_completion(&wqe_lcmd->completion, buf_out);
		अवरोध;
	हाल CMDQ_CMD_SYNC_सूचीECT_RESP:
		complete_क्रमmat = COMPLETE_सूचीECT;
		wqe_lcmd->completion.direct_resp = 0;
		अवरोध;
	पूर्ण

	cmdq_prepare_wqe_ctrl(wqe, wrapped, ack_type, mod, cmd,
			      prod_idx, complete_क्रमmat, DATA_SGE,
			      BUFDESC_LCMD_LEN);

	cmdq_set_lcmd_bufdesc(wqe_lcmd, buf_in);
पूर्ण

अटल व्योम cmdq_set_direct_wqe(काष्ठा hinic_cmdq_wqe *wqe,
				क्रमागत cmdq_cmd_type cmd_type,
				व्योम *buf_in, u16 in_size,
				काष्ठा hinic_cmdq_buf *buf_out, पूर्णांक wrapped,
				क्रमागत hinic_cmd_ack_type ack_type,
				क्रमागत hinic_mod_type mod, u8 cmd, u16 prod_idx)
अणु
	काष्ठा hinic_cmdq_direct_wqe *direct_wqe = &wqe->direct_wqe;
	क्रमागत completion_क्रमmat complete_क्रमmat;
	काष्ठा hinic_cmdq_wqe_scmd *wqe_scmd;

	wqe_scmd = &direct_wqe->wqe_scmd;

	चयन (cmd_type) अणु
	हाल CMDQ_CMD_SYNC_SGE_RESP:
		complete_क्रमmat = COMPLETE_SGE;
		cmdq_set_sge_completion(&wqe_scmd->completion, buf_out);
		अवरोध;
	हाल CMDQ_CMD_SYNC_सूचीECT_RESP:
		complete_क्रमmat = COMPLETE_सूचीECT;
		wqe_scmd->completion.direct_resp = 0;
		अवरोध;
	पूर्ण

	cmdq_prepare_wqe_ctrl(wqe, wrapped, ack_type, mod, cmd, prod_idx,
			      complete_क्रमmat, DATA_सूचीECT, BUFDESC_SCMD_LEN);

	cmdq_set_direct_wqe_data(direct_wqe, buf_in, in_size);
पूर्ण

अटल व्योम cmdq_wqe_fill(व्योम *dst, व्योम *src)
अणु
	स_नकल(dst + FIRST_DATA_TO_WRITE_LAST, src + FIRST_DATA_TO_WRITE_LAST,
	       CMDQ_WQE_SIZE - FIRST_DATA_TO_WRITE_LAST);

	wmb();          /* The first 8 bytes should be written last */

	*(u64 *)dst = *(u64 *)src;
पूर्ण

अटल व्योम cmdq_fill_db(u32 *db_info,
			 क्रमागत hinic_cmdq_type cmdq_type, u16 prod_idx)
अणु
	*db_info = HINIC_CMDQ_DB_INFO_SET(UPPER_8_BITS(prod_idx), HI_PROD_IDX) |
		   HINIC_CMDQ_DB_INFO_SET(HINIC_CTRL_PATH, PATH)               |
		   HINIC_CMDQ_DB_INFO_SET(cmdq_type, CMDQ_TYPE)                |
		   HINIC_CMDQ_DB_INFO_SET(HINIC_DB_CMDQ_TYPE, DB_TYPE);
पूर्ण

अटल व्योम cmdq_set_db(काष्ठा hinic_cmdq *cmdq,
			क्रमागत hinic_cmdq_type cmdq_type, u16 prod_idx)
अणु
	u32 db_info;

	cmdq_fill_db(&db_info, cmdq_type, prod_idx);

	/* The data that is written to HW should be in Big Endian Format */
	db_info = cpu_to_be32(db_info);

	wmb();  /* ग_लिखो all beक्रमe the करोorbell */

	ग_लिखोl(db_info, CMDQ_DB_ADDR(cmdq->db_base, prod_idx));
पूर्ण

अटल पूर्णांक cmdq_sync_cmd_direct_resp(काष्ठा hinic_cmdq *cmdq,
				     क्रमागत hinic_mod_type mod, u8 cmd,
				     काष्ठा hinic_cmdq_buf *buf_in,
				     u64 *resp)
अणु
	काष्ठा hinic_cmdq_wqe *curr_cmdq_wqe, cmdq_wqe;
	u16 curr_prod_idx, next_prod_idx;
	पूर्णांक errcode, wrapped, num_wqebbs;
	काष्ठा hinic_wq *wq = cmdq->wq;
	काष्ठा hinic_hw_wqe *hw_wqe;
	काष्ठा completion करोne;

	/* Keep करोorbell index correct. bh - क्रम tasklet(ceq). */
	spin_lock_bh(&cmdq->cmdq_lock);

	/* WQE_SIZE = WQEBB_SIZE, we will get the wq element and not shaकरोw*/
	hw_wqe = hinic_get_wqe(wq, WQE_LCMD_SIZE, &curr_prod_idx);
	अगर (IS_ERR(hw_wqe)) अणु
		spin_unlock_bh(&cmdq->cmdq_lock);
		वापस -EBUSY;
	पूर्ण

	curr_cmdq_wqe = &hw_wqe->cmdq_wqe;

	wrapped = cmdq->wrapped;

	num_wqebbs = ALIGN(WQE_LCMD_SIZE, wq->wqebb_size) / wq->wqebb_size;
	next_prod_idx = curr_prod_idx + num_wqebbs;
	अगर (next_prod_idx >= wq->q_depth) अणु
		cmdq->wrapped = !cmdq->wrapped;
		next_prod_idx -= wq->q_depth;
	पूर्ण

	cmdq->errcode[curr_prod_idx] = &errcode;

	init_completion(&करोne);
	cmdq->करोne[curr_prod_idx] = &करोne;

	cmdq_set_lcmd_wqe(&cmdq_wqe, CMDQ_CMD_SYNC_सूचीECT_RESP, buf_in, शून्य,
			  wrapped, HINIC_CMD_ACK_TYPE_CMDQ, mod, cmd,
			  curr_prod_idx);

	/* The data that is written to HW should be in Big Endian Format */
	hinic_cpu_to_be32(&cmdq_wqe, WQE_LCMD_SIZE);

	/* CMDQ WQE is not shaकरोw, thereक्रमe wqe will be written to wq */
	cmdq_wqe_fill(curr_cmdq_wqe, &cmdq_wqe);

	cmdq_set_db(cmdq, HINIC_CMDQ_SYNC, next_prod_idx);

	spin_unlock_bh(&cmdq->cmdq_lock);

	अगर (!रुको_क्रम_completion_समयout(&करोne,
					 msecs_to_jअगरfies(CMDQ_TIMEOUT))) अणु
		spin_lock_bh(&cmdq->cmdq_lock);

		अगर (cmdq->errcode[curr_prod_idx] == &errcode)
			cmdq->errcode[curr_prod_idx] = शून्य;

		अगर (cmdq->करोne[curr_prod_idx] == &करोne)
			cmdq->करोne[curr_prod_idx] = शून्य;

		spin_unlock_bh(&cmdq->cmdq_lock);

		hinic_dump_ceq_info(cmdq->hwdev);
		वापस -ETIMEDOUT;
	पूर्ण

	smp_rmb();      /* पढ़ो error code after completion */

	अगर (resp) अणु
		काष्ठा hinic_cmdq_wqe_lcmd *wqe_lcmd = &curr_cmdq_wqe->wqe_lcmd;

		*resp = cpu_to_be64(wqe_lcmd->completion.direct_resp);
	पूर्ण

	अगर (errcode != 0)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक cmdq_set_arm_bit(काष्ठा hinic_cmdq *cmdq, व्योम *buf_in,
			    u16 in_size)
अणु
	काष्ठा hinic_cmdq_wqe *curr_cmdq_wqe, cmdq_wqe;
	u16 curr_prod_idx, next_prod_idx;
	काष्ठा hinic_wq *wq = cmdq->wq;
	काष्ठा hinic_hw_wqe *hw_wqe;
	पूर्णांक wrapped, num_wqebbs;

	/* Keep करोorbell index correct */
	spin_lock(&cmdq->cmdq_lock);

	/* WQE_SIZE = WQEBB_SIZE, we will get the wq element and not shaकरोw*/
	hw_wqe = hinic_get_wqe(wq, WQE_SCMD_SIZE, &curr_prod_idx);
	अगर (IS_ERR(hw_wqe)) अणु
		spin_unlock(&cmdq->cmdq_lock);
		वापस -EBUSY;
	पूर्ण

	curr_cmdq_wqe = &hw_wqe->cmdq_wqe;

	wrapped = cmdq->wrapped;

	num_wqebbs = ALIGN(WQE_SCMD_SIZE, wq->wqebb_size) / wq->wqebb_size;
	next_prod_idx = curr_prod_idx + num_wqebbs;
	अगर (next_prod_idx >= wq->q_depth) अणु
		cmdq->wrapped = !cmdq->wrapped;
		next_prod_idx -= wq->q_depth;
	पूर्ण

	cmdq_set_direct_wqe(&cmdq_wqe, CMDQ_CMD_SYNC_सूचीECT_RESP, buf_in,
			    in_size, शून्य, wrapped, HINIC_CMD_ACK_TYPE_CMDQ,
			    HINIC_MOD_COMM, CMDQ_SET_ARM_CMD, curr_prod_idx);

	/* The data that is written to HW should be in Big Endian Format */
	hinic_cpu_to_be32(&cmdq_wqe, WQE_SCMD_SIZE);

	/* cmdq wqe is not shaकरोw, thereक्रमe wqe will be written to wq */
	cmdq_wqe_fill(curr_cmdq_wqe, &cmdq_wqe);

	cmdq_set_db(cmdq, HINIC_CMDQ_SYNC, next_prod_idx);

	spin_unlock(&cmdq->cmdq_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक cmdq_params_valid(काष्ठा hinic_cmdq_buf *buf_in)
अणु
	अगर (buf_in->size > HINIC_CMDQ_MAX_DATA_SIZE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * hinic_cmdq_direct_resp - send command with direct data as resp
 * @cmdqs: the cmdqs
 * @mod: module on the card that will handle the command
 * @cmd: the command
 * @buf_in: the buffer क्रम the command
 * @resp: the response to वापस
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_cmdq_direct_resp(काष्ठा hinic_cmdqs *cmdqs,
			   क्रमागत hinic_mod_type mod, u8 cmd,
			   काष्ठा hinic_cmdq_buf *buf_in, u64 *resp)
अणु
	काष्ठा hinic_hwअगर *hwअगर = cmdqs->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	err = cmdq_params_valid(buf_in);
	अगर (err) अणु
		dev_err(&pdev->dev, "Invalid CMDQ parameters\n");
		वापस err;
	पूर्ण

	वापस cmdq_sync_cmd_direct_resp(&cmdqs->cmdq[HINIC_CMDQ_SYNC],
					 mod, cmd, buf_in, resp);
पूर्ण

/**
 * hinic_set_arm_bit - set arm bit क्रम enable पूर्णांकerrupt again
 * @cmdqs: the cmdqs
 * @q_type: type of queue to set the arm bit क्रम
 * @q_id: the queue number
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_set_arm_bit(काष्ठा hinic_cmdqs *cmdqs,
		      क्रमागत hinic_set_arm_qtype q_type, u32 q_id)
अणु
	काष्ठा hinic_cmdq *cmdq = &cmdqs->cmdq[HINIC_CMDQ_SYNC];
	काष्ठा hinic_hwअगर *hwअगर = cmdqs->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_cmdq_arm_bit arm_bit;
	पूर्णांक err;

	arm_bit.q_type = q_type;
	arm_bit.q_id   = q_id;

	err = cmdq_set_arm_bit(cmdq, &arm_bit, माप(arm_bit));
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to set arm for qid %d\n", q_id);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम clear_wqe_complete_bit(काष्ठा hinic_cmdq *cmdq,
				   काष्ठा hinic_cmdq_wqe *wqe)
अणु
	u32 header_info = be32_to_cpu(CMDQ_WQE_HEADER(wqe)->header_info);
	अचिन्हित पूर्णांक bufdesc_len, wqe_size;
	काष्ठा hinic_ctrl *ctrl;

	bufdesc_len = HINIC_CMDQ_WQE_HEADER_GET(header_info, BUFDESC_LEN);
	wqe_size = cmdq_wqe_size_from_bdlen(bufdesc_len);
	अगर (wqe_size == WQE_LCMD_SIZE) अणु
		काष्ठा hinic_cmdq_wqe_lcmd *wqe_lcmd = &wqe->wqe_lcmd;

		ctrl = &wqe_lcmd->ctrl;
	पूर्ण अन्यथा अणु
		काष्ठा hinic_cmdq_direct_wqe *direct_wqe = &wqe->direct_wqe;
		काष्ठा hinic_cmdq_wqe_scmd *wqe_scmd;

		wqe_scmd = &direct_wqe->wqe_scmd;
		ctrl = &wqe_scmd->ctrl;
	पूर्ण

	/* clear HW busy bit */
	ctrl->ctrl_info = 0;

	wmb();  /* verअगरy wqe is clear */
पूर्ण

/**
 * cmdq_arm_ceq_handler - cmdq completion event handler क्रम arm command
 * @cmdq: the cmdq of the arm command
 * @wqe: the wqe of the arm command
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक cmdq_arm_ceq_handler(काष्ठा hinic_cmdq *cmdq,
				काष्ठा hinic_cmdq_wqe *wqe)
अणु
	काष्ठा hinic_cmdq_direct_wqe *direct_wqe = &wqe->direct_wqe;
	काष्ठा hinic_cmdq_wqe_scmd *wqe_scmd;
	काष्ठा hinic_ctrl *ctrl;
	u32 ctrl_info;

	wqe_scmd = &direct_wqe->wqe_scmd;
	ctrl = &wqe_scmd->ctrl;
	ctrl_info = be32_to_cpu(ctrl->ctrl_info);

	/* HW should toggle the HW BUSY BIT */
	अगर (!CMDQ_WQE_COMPLETED(ctrl_info))
		वापस -EBUSY;

	clear_wqe_complete_bit(cmdq, wqe);

	hinic_put_wqe(cmdq->wq, WQE_SCMD_SIZE);
	वापस 0;
पूर्ण

अटल व्योम cmdq_update_errcode(काष्ठा hinic_cmdq *cmdq, u16 prod_idx,
				पूर्णांक errcode)
अणु
	अगर (cmdq->errcode[prod_idx])
		*cmdq->errcode[prod_idx] = errcode;
पूर्ण

/**
 * cmdq_arm_ceq_handler - cmdq completion event handler क्रम sync command
 * @cmdq: the cmdq of the command
 * @cons_idx: the consumer index to update the error code क्रम
 * @errcode: the error code
 **/
अटल व्योम cmdq_sync_cmd_handler(काष्ठा hinic_cmdq *cmdq, u16 cons_idx,
				  पूर्णांक errcode)
अणु
	u16 prod_idx = cons_idx;

	spin_lock(&cmdq->cmdq_lock);
	cmdq_update_errcode(cmdq, prod_idx, errcode);

	wmb();  /* ग_लिखो all beक्रमe update क्रम the command request */

	अगर (cmdq->करोne[prod_idx])
		complete(cmdq->करोne[prod_idx]);
	spin_unlock(&cmdq->cmdq_lock);
पूर्ण

अटल पूर्णांक cmdq_cmd_ceq_handler(काष्ठा hinic_cmdq *cmdq, u16 ci,
				काष्ठा hinic_cmdq_wqe *cmdq_wqe)
अणु
	काष्ठा hinic_cmdq_wqe_lcmd *wqe_lcmd = &cmdq_wqe->wqe_lcmd;
	काष्ठा hinic_status *status = &wqe_lcmd->status;
	काष्ठा hinic_ctrl *ctrl = &wqe_lcmd->ctrl;
	पूर्णांक errcode;

	अगर (!CMDQ_WQE_COMPLETED(be32_to_cpu(ctrl->ctrl_info)))
		वापस -EBUSY;

	dma_rmb();

	errcode = CMDQ_WQE_ERRCODE_GET(be32_to_cpu(status->status_info), VAL);

	cmdq_sync_cmd_handler(cmdq, ci, errcode);

	clear_wqe_complete_bit(cmdq, cmdq_wqe);
	hinic_put_wqe(cmdq->wq, WQE_LCMD_SIZE);
	वापस 0;
पूर्ण

/**
 * cmdq_ceq_handler - cmdq completion event handler
 * @handle: निजी data क्रम the handler(cmdqs)
 * @ceqe_data: ceq element data
 **/
अटल व्योम cmdq_ceq_handler(व्योम *handle, u32 ceqe_data)
अणु
	क्रमागत hinic_cmdq_type cmdq_type = CMDQ_CEQE_GET(ceqe_data, TYPE);
	काष्ठा hinic_cmdqs *cmdqs = (काष्ठा hinic_cmdqs *)handle;
	काष्ठा hinic_cmdq *cmdq = &cmdqs->cmdq[cmdq_type];
	काष्ठा hinic_cmdq_header *header;
	काष्ठा hinic_hw_wqe *hw_wqe;
	पूर्णांक err, set_arm = 0;
	u32 saved_data;
	u16 ci;

	/* Read the smallest wqe size क्रम getting wqe size */
	जबतक ((hw_wqe = hinic_पढ़ो_wqe(cmdq->wq, WQE_SCMD_SIZE, &ci))) अणु
		अगर (IS_ERR(hw_wqe))
			अवरोध;

		header = CMDQ_WQE_HEADER(&hw_wqe->cmdq_wqe);
		saved_data = be32_to_cpu(header->saved_data);

		अगर (HINIC_SAVED_DATA_GET(saved_data, ARM)) अणु
			/* arm_bit was set until here */
			set_arm = 0;

			अगर (cmdq_arm_ceq_handler(cmdq, &hw_wqe->cmdq_wqe))
				अवरोध;
		पूर्ण अन्यथा अणु
			set_arm = 1;

			hw_wqe = hinic_पढ़ो_wqe(cmdq->wq, WQE_LCMD_SIZE, &ci);
			अगर (IS_ERR(hw_wqe))
				अवरोध;

			अगर (cmdq_cmd_ceq_handler(cmdq, ci, &hw_wqe->cmdq_wqe))
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (set_arm) अणु
		काष्ठा hinic_hwअगर *hwअगर = cmdqs->hwअगर;
		काष्ठा pci_dev *pdev = hwअगर->pdev;

		err = hinic_set_arm_bit(cmdqs, HINIC_SET_ARM_CMDQ, cmdq_type);
		अगर (err)
			dev_err(&pdev->dev, "Failed to set arm for CMDQ\n");
	पूर्ण
पूर्ण

/**
 * cmdq_init_queue_ctxt - init the queue ctxt of a cmdq
 * @cmdq_ctxt: cmdq ctxt to initialize
 * @cmdq: the cmdq
 * @cmdq_pages: the memory of the queue
 **/
अटल व्योम cmdq_init_queue_ctxt(काष्ठा hinic_cmdq_ctxt *cmdq_ctxt,
				 काष्ठा hinic_cmdq *cmdq,
				 काष्ठा hinic_cmdq_pages *cmdq_pages)
अणु
	काष्ठा hinic_cmdq_ctxt_info *ctxt_info = &cmdq_ctxt->ctxt_info;
	u64 wq_first_page_paddr, cmdq_first_block_paddr, pfn;
	काष्ठा hinic_cmdqs *cmdqs = cmdq_to_cmdqs(cmdq);
	काष्ठा hinic_wq *wq = cmdq->wq;

	/* The data in the HW is in Big Endian Format */
	wq_first_page_paddr = be64_to_cpu(*wq->block_vaddr);

	pfn = CMDQ_PFN(wq_first_page_paddr, SZ_4K);

	ctxt_info->curr_wqe_page_pfn =
		HINIC_CMDQ_CTXT_PAGE_INFO_SET(pfn, CURR_WQE_PAGE_PFN)   |
		HINIC_CMDQ_CTXT_PAGE_INFO_SET(HINIC_CEQ_ID_CMDQ, EQ_ID) |
		HINIC_CMDQ_CTXT_PAGE_INFO_SET(1, CEQ_ARM)               |
		HINIC_CMDQ_CTXT_PAGE_INFO_SET(1, CEQ_EN)                |
		HINIC_CMDQ_CTXT_PAGE_INFO_SET(cmdq->wrapped, WRAPPED);

	अगर (wq->num_q_pages != 1) अणु
		/* block PFN - Read Modअगरy Write */
		cmdq_first_block_paddr = cmdq_pages->page_paddr;

		pfn = CMDQ_PFN(cmdq_first_block_paddr, wq->wq_page_size);
	पूर्ण

	ctxt_info->wq_block_pfn =
		HINIC_CMDQ_CTXT_BLOCK_INFO_SET(pfn, WQ_BLOCK_PFN) |
		HINIC_CMDQ_CTXT_BLOCK_INFO_SET(atomic_पढ़ो(&wq->cons_idx), CI);

	cmdq_ctxt->func_idx = HINIC_HWIF_FUNC_IDX(cmdqs->hwअगर);
	cmdq_ctxt->ppf_idx = HINIC_HWIF_PPF_IDX(cmdqs->hwअगर);
	cmdq_ctxt->cmdq_type  = cmdq->cmdq_type;
पूर्ण

/**
 * init_cmdq - initialize cmdq
 * @cmdq: the cmdq
 * @wq: the wq attaced to the cmdq
 * @q_type: the cmdq type of the cmdq
 * @db_area: करोorbell area क्रम the cmdq
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक init_cmdq(काष्ठा hinic_cmdq *cmdq, काष्ठा hinic_wq *wq,
		     क्रमागत hinic_cmdq_type q_type, व्योम __iomem *db_area)
अणु
	पूर्णांक err;

	cmdq->wq = wq;
	cmdq->cmdq_type = q_type;
	cmdq->wrapped = 1;

	spin_lock_init(&cmdq->cmdq_lock);

	cmdq->करोne = vzalloc(array_size(माप(*cmdq->करोne), wq->q_depth));
	अगर (!cmdq->करोne)
		वापस -ENOMEM;

	cmdq->errcode = vzalloc(array_size(माप(*cmdq->errcode),
					   wq->q_depth));
	अगर (!cmdq->errcode) अणु
		err = -ENOMEM;
		जाओ err_errcode;
	पूर्ण

	cmdq->db_base = db_area + CMDQ_DB_OFF;
	वापस 0;

err_errcode:
	vमुक्त(cmdq->करोne);
	वापस err;
पूर्ण

/**
 * मुक्त_cmdq - Free cmdq
 * @cmdq: the cmdq to मुक्त
 **/
अटल व्योम मुक्त_cmdq(काष्ठा hinic_cmdq *cmdq)
अणु
	vमुक्त(cmdq->errcode);
	vमुक्त(cmdq->करोne);
पूर्ण

/**
 * init_cmdqs_ctxt - ग_लिखो the cmdq ctxt to HW after init all cmdq
 * @hwdev: the NIC HW device
 * @cmdqs: cmdqs to ग_लिखो the ctxts क्रम
 * @db_area: db_area क्रम all the cmdqs
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक init_cmdqs_ctxt(काष्ठा hinic_hwdev *hwdev,
			   काष्ठा hinic_cmdqs *cmdqs, व्योम __iomem **db_area)
अणु
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	क्रमागत hinic_cmdq_type type, cmdq_type;
	काष्ठा hinic_cmdq_ctxt *cmdq_ctxts;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_pfhwdev *pfhwdev;
	माप_प्रकार cmdq_ctxts_size;
	पूर्णांक err;

	cmdq_ctxts_size = HINIC_MAX_CMDQ_TYPES * माप(*cmdq_ctxts);
	cmdq_ctxts = devm_kzalloc(&pdev->dev, cmdq_ctxts_size, GFP_KERNEL);
	अगर (!cmdq_ctxts)
		वापस -ENOMEM;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	cmdq_type = HINIC_CMDQ_SYNC;
	क्रम (; cmdq_type < HINIC_MAX_CMDQ_TYPES; cmdq_type++) अणु
		cmdqs->cmdq[cmdq_type].hwdev = hwdev;
		err = init_cmdq(&cmdqs->cmdq[cmdq_type],
				&cmdqs->saved_wqs[cmdq_type], cmdq_type,
				db_area[cmdq_type]);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to initialize cmdq\n");
			जाओ err_init_cmdq;
		पूर्ण

		cmdq_init_queue_ctxt(&cmdq_ctxts[cmdq_type],
				     &cmdqs->cmdq[cmdq_type],
				     &cmdqs->cmdq_pages);
	पूर्ण

	/* Write the CMDQ ctxts */
	cmdq_type = HINIC_CMDQ_SYNC;
	क्रम (; cmdq_type < HINIC_MAX_CMDQ_TYPES; cmdq_type++) अणु
		err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
					HINIC_COMM_CMD_CMDQ_CTXT_SET,
					&cmdq_ctxts[cmdq_type],
					माप(cmdq_ctxts[cmdq_type]),
					शून्य, शून्य, HINIC_MGMT_MSG_SYNC);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to set CMDQ CTXT type = %d\n",
				cmdq_type);
			जाओ err_ग_लिखो_cmdq_ctxt;
		पूर्ण
	पूर्ण

	devm_kमुक्त(&pdev->dev, cmdq_ctxts);
	वापस 0;

err_ग_लिखो_cmdq_ctxt:
	cmdq_type = HINIC_MAX_CMDQ_TYPES;

err_init_cmdq:
	क्रम (type = HINIC_CMDQ_SYNC; type < cmdq_type; type++)
		मुक्त_cmdq(&cmdqs->cmdq[type]);

	devm_kमुक्त(&pdev->dev, cmdq_ctxts);
	वापस err;
पूर्ण

अटल पूर्णांक hinic_set_cmdq_depth(काष्ठा hinic_hwdev *hwdev, u16 cmdq_depth)
अणु
	काष्ठा hinic_cmd_hw_ioctxt hw_ioctxt = अणु 0 पूर्ण;
	काष्ठा hinic_pfhwdev *pfhwdev;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	hw_ioctxt.func_idx = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);
	hw_ioctxt.ppf_idx = HINIC_HWIF_PPF_IDX(hwdev->hwअगर);

	hw_ioctxt.set_cmdq_depth = HW_IOCTXT_SET_CMDQ_DEPTH_ENABLE;
	hw_ioctxt.cmdq_depth = (u8)ilog2(cmdq_depth);

	वापस hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				 HINIC_COMM_CMD_HWCTXT_SET,
				 &hw_ioctxt, माप(hw_ioctxt), शून्य,
				 शून्य, HINIC_MGMT_MSG_SYNC);
पूर्ण

/**
 * hinic_init_cmdqs - init all cmdqs
 * @cmdqs: cmdqs to init
 * @hwअगर: HW पूर्णांकerface क्रम accessing cmdqs
 * @db_area: करोorbell areas क्रम all the cmdqs
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_init_cmdqs(काष्ठा hinic_cmdqs *cmdqs, काष्ठा hinic_hwअगर *hwअगर,
		     व्योम __iomem **db_area)
अणु
	काष्ठा hinic_func_to_io *func_to_io = cmdqs_to_func_to_io(cmdqs);
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_hwdev *hwdev;
	माप_प्रकार saved_wqs_size;
	u16 max_wqe_size;
	पूर्णांक err;

	cmdqs->hwअगर = hwअगर;
	cmdqs->cmdq_buf_pool = dma_pool_create("hinic_cmdq", &pdev->dev,
					       HINIC_CMDQ_BUF_SIZE,
					       HINIC_CMDQ_BUF_SIZE, 0);
	अगर (!cmdqs->cmdq_buf_pool)
		वापस -ENOMEM;

	saved_wqs_size = HINIC_MAX_CMDQ_TYPES * माप(काष्ठा hinic_wq);
	cmdqs->saved_wqs = devm_kzalloc(&pdev->dev, saved_wqs_size, GFP_KERNEL);
	अगर (!cmdqs->saved_wqs) अणु
		err = -ENOMEM;
		जाओ err_saved_wqs;
	पूर्ण

	max_wqe_size = WQE_LCMD_SIZE;
	err = hinic_wqs_cmdq_alloc(&cmdqs->cmdq_pages, cmdqs->saved_wqs, hwअगर,
				   HINIC_MAX_CMDQ_TYPES, CMDQ_WQEBB_SIZE,
				   CMDQ_WQ_PAGE_SIZE, CMDQ_DEPTH, max_wqe_size);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate CMDQ wqs\n");
		जाओ err_cmdq_wqs;
	पूर्ण

	hwdev = container_of(func_to_io, काष्ठा hinic_hwdev, func_to_io);
	err = init_cmdqs_ctxt(hwdev, cmdqs, db_area);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to write cmdq ctxt\n");
		जाओ err_cmdq_ctxt;
	पूर्ण

	hinic_ceq_रेजिस्टर_cb(&func_to_io->ceqs, HINIC_CEQ_CMDQ, cmdqs,
			      cmdq_ceq_handler);

	err = hinic_set_cmdq_depth(hwdev, CMDQ_DEPTH);
	अगर (err) अणु
		dev_err(&hwअगर->pdev->dev, "Failed to set cmdq depth\n");
		जाओ err_set_cmdq_depth;
	पूर्ण

	वापस 0;

err_set_cmdq_depth:
	hinic_ceq_unरेजिस्टर_cb(&func_to_io->ceqs, HINIC_CEQ_CMDQ);

err_cmdq_ctxt:
	hinic_wqs_cmdq_मुक्त(&cmdqs->cmdq_pages, cmdqs->saved_wqs,
			    HINIC_MAX_CMDQ_TYPES);

err_cmdq_wqs:
	devm_kमुक्त(&pdev->dev, cmdqs->saved_wqs);

err_saved_wqs:
	dma_pool_destroy(cmdqs->cmdq_buf_pool);
	वापस err;
पूर्ण

/**
 * hinic_मुक्त_cmdqs - मुक्त all cmdqs
 * @cmdqs: cmdqs to मुक्त
 **/
व्योम hinic_मुक्त_cmdqs(काष्ठा hinic_cmdqs *cmdqs)
अणु
	काष्ठा hinic_func_to_io *func_to_io = cmdqs_to_func_to_io(cmdqs);
	काष्ठा hinic_hwअगर *hwअगर = cmdqs->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	क्रमागत hinic_cmdq_type cmdq_type;

	hinic_ceq_unरेजिस्टर_cb(&func_to_io->ceqs, HINIC_CEQ_CMDQ);

	cmdq_type = HINIC_CMDQ_SYNC;
	क्रम (; cmdq_type < HINIC_MAX_CMDQ_TYPES; cmdq_type++)
		मुक्त_cmdq(&cmdqs->cmdq[cmdq_type]);

	hinic_wqs_cmdq_मुक्त(&cmdqs->cmdq_pages, cmdqs->saved_wqs,
			    HINIC_MAX_CMDQ_TYPES);

	devm_kमुक्त(&pdev->dev, cmdqs->saved_wqs);

	dma_pool_destroy(cmdqs->cmdq_buf_pool);
पूर्ण
