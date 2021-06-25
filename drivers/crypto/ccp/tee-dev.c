<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * AMD Trusted Execution Environment (TEE) पूर्णांकerface
 *
 * Author: Rijo Thomas <Rijo-john.Thomas@amd.com>
 * Author: Devaraj Rangasamy <Devaraj.Rangasamy@amd.com>
 *
 * Copyright (C) 2019,2021 Advanced Micro Devices, Inc.
 */

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/gfp.h>
#समावेश <linux/psp-sev.h>
#समावेश <linux/psp-tee.h>

#समावेश "psp-dev.h"
#समावेश "tee-dev.h"

अटल bool psp_dead;

अटल पूर्णांक tee_alloc_ring(काष्ठा psp_tee_device *tee, पूर्णांक ring_size)
अणु
	काष्ठा ring_buf_manager *rb_mgr = &tee->rb_mgr;
	व्योम *start_addr;

	अगर (!ring_size)
		वापस -EINVAL;

	/* We need actual physical address instead of DMA address, since
	 * Trusted OS running on AMD Secure Processor will map this region
	 */
	start_addr = (व्योम *)__get_मुक्त_pages(GFP_KERNEL, get_order(ring_size));
	अगर (!start_addr)
		वापस -ENOMEM;

	स_रखो(start_addr, 0x0, ring_size);
	rb_mgr->ring_start = start_addr;
	rb_mgr->ring_size = ring_size;
	rb_mgr->ring_pa = __psp_pa(start_addr);
	mutex_init(&rb_mgr->mutex);

	वापस 0;
पूर्ण

अटल व्योम tee_मुक्त_ring(काष्ठा psp_tee_device *tee)
अणु
	काष्ठा ring_buf_manager *rb_mgr = &tee->rb_mgr;

	अगर (!rb_mgr->ring_start)
		वापस;

	मुक्त_pages((अचिन्हित दीर्घ)rb_mgr->ring_start,
		   get_order(rb_mgr->ring_size));

	rb_mgr->ring_start = शून्य;
	rb_mgr->ring_size = 0;
	rb_mgr->ring_pa = 0;
	mutex_destroy(&rb_mgr->mutex);
पूर्ण

अटल पूर्णांक tee_रुको_cmd_poll(काष्ठा psp_tee_device *tee, अचिन्हित पूर्णांक समयout,
			     अचिन्हित पूर्णांक *reg)
अणु
	/* ~10ms sleep per loop => nloop = समयout * 100 */
	पूर्णांक nloop = समयout * 100;

	जबतक (--nloop) अणु
		*reg = ioपढ़ो32(tee->io_regs + tee->vdata->cmdresp_reg);
		अगर (*reg & PSP_CMDRESP_RESP)
			वापस 0;

		usleep_range(10000, 10100);
	पूर्ण

	dev_err(tee->dev, "tee: command timed out, disabling PSP\n");
	psp_dead = true;

	वापस -ETIMEDOUT;
पूर्ण

अटल
काष्ठा tee_init_ring_cmd *tee_alloc_cmd_buffer(काष्ठा psp_tee_device *tee)
अणु
	काष्ठा tee_init_ring_cmd *cmd;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस शून्य;

	cmd->hi_addr = upper_32_bits(tee->rb_mgr.ring_pa);
	cmd->low_addr = lower_32_bits(tee->rb_mgr.ring_pa);
	cmd->size = tee->rb_mgr.ring_size;

	dev_dbg(tee->dev, "tee: ring address: high = 0x%x low = 0x%x size = %u\n",
		cmd->hi_addr, cmd->low_addr, cmd->size);

	वापस cmd;
पूर्ण

अटल अंतरभूत व्योम tee_मुक्त_cmd_buffer(काष्ठा tee_init_ring_cmd *cmd)
अणु
	kमुक्त(cmd);
पूर्ण

अटल पूर्णांक tee_init_ring(काष्ठा psp_tee_device *tee)
अणु
	पूर्णांक ring_size = MAX_RING_BUFFER_ENTRIES * माप(काष्ठा tee_ring_cmd);
	काष्ठा tee_init_ring_cmd *cmd;
	phys_addr_t cmd_buffer;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	BUILD_BUG_ON(माप(काष्ठा tee_ring_cmd) != 1024);

	ret = tee_alloc_ring(tee, ring_size);
	अगर (ret) अणु
		dev_err(tee->dev, "tee: ring allocation failed %d\n", ret);
		वापस ret;
	पूर्ण

	tee->rb_mgr.wptr = 0;

	cmd = tee_alloc_cmd_buffer(tee);
	अगर (!cmd) अणु
		tee_मुक्त_ring(tee);
		वापस -ENOMEM;
	पूर्ण

	cmd_buffer = __psp_pa((व्योम *)cmd);

	/* Send command buffer details to Trusted OS by writing to
	 * CPU-PSP message रेजिस्टरs
	 */

	ioग_लिखो32(lower_32_bits(cmd_buffer),
		  tee->io_regs + tee->vdata->cmdbuff_addr_lo_reg);
	ioग_लिखो32(upper_32_bits(cmd_buffer),
		  tee->io_regs + tee->vdata->cmdbuff_addr_hi_reg);
	ioग_लिखो32(TEE_RING_INIT_CMD,
		  tee->io_regs + tee->vdata->cmdresp_reg);

	ret = tee_रुको_cmd_poll(tee, TEE_DEFAULT_TIMEOUT, &reg);
	अगर (ret) अणु
		dev_err(tee->dev, "tee: ring init command timed out\n");
		tee_मुक्त_ring(tee);
		जाओ मुक्त_buf;
	पूर्ण

	अगर (reg & PSP_CMDRESP_ERR_MASK) अणु
		dev_err(tee->dev, "tee: ring init command failed (%#010x)\n",
			reg & PSP_CMDRESP_ERR_MASK);
		tee_मुक्त_ring(tee);
		ret = -EIO;
	पूर्ण

मुक्त_buf:
	tee_मुक्त_cmd_buffer(cmd);

	वापस ret;
पूर्ण

अटल व्योम tee_destroy_ring(काष्ठा psp_tee_device *tee)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	अगर (!tee->rb_mgr.ring_start)
		वापस;

	अगर (psp_dead)
		जाओ मुक्त_ring;

	ioग_लिखो32(TEE_RING_DESTROY_CMD,
		  tee->io_regs + tee->vdata->cmdresp_reg);

	ret = tee_रुको_cmd_poll(tee, TEE_DEFAULT_TIMEOUT, &reg);
	अगर (ret) अणु
		dev_err(tee->dev, "tee: ring destroy command timed out\n");
	पूर्ण अन्यथा अगर (reg & PSP_CMDRESP_ERR_MASK) अणु
		dev_err(tee->dev, "tee: ring destroy command failed (%#010x)\n",
			reg & PSP_CMDRESP_ERR_MASK);
	पूर्ण

मुक्त_ring:
	tee_मुक्त_ring(tee);
पूर्ण

पूर्णांक tee_dev_init(काष्ठा psp_device *psp)
अणु
	काष्ठा device *dev = psp->dev;
	काष्ठा psp_tee_device *tee;
	पूर्णांक ret;

	ret = -ENOMEM;
	tee = devm_kzalloc(dev, माप(*tee), GFP_KERNEL);
	अगर (!tee)
		जाओ e_err;

	psp->tee_data = tee;

	tee->dev = dev;
	tee->psp = psp;

	tee->io_regs = psp->io_regs;

	tee->vdata = (काष्ठा tee_vdata *)psp->vdata->tee;
	अगर (!tee->vdata) अणु
		ret = -ENODEV;
		dev_err(dev, "tee: missing driver data\n");
		जाओ e_err;
	पूर्ण

	ret = tee_init_ring(tee);
	अगर (ret) अणु
		dev_err(dev, "tee: failed to init ring buffer\n");
		जाओ e_err;
	पूर्ण

	dev_notice(dev, "tee enabled\n");

	वापस 0;

e_err:
	psp->tee_data = शून्य;

	dev_notice(dev, "tee initialization failed\n");

	वापस ret;
पूर्ण

व्योम tee_dev_destroy(काष्ठा psp_device *psp)
अणु
	काष्ठा psp_tee_device *tee = psp->tee_data;

	अगर (!tee)
		वापस;

	tee_destroy_ring(tee);
पूर्ण

अटल पूर्णांक tee_submit_cmd(काष्ठा psp_tee_device *tee, क्रमागत tee_cmd_id cmd_id,
			  व्योम *buf, माप_प्रकार len, काष्ठा tee_ring_cmd **resp)
अणु
	काष्ठा tee_ring_cmd *cmd;
	पूर्णांक nloop = 1000, ret = 0;
	u32 rptr;

	*resp = शून्य;

	mutex_lock(&tee->rb_mgr.mutex);

	/* Loop until empty entry found in ring buffer */
	करो अणु
		/* Get poपूर्णांकer to ring buffer command entry */
		cmd = (काष्ठा tee_ring_cmd *)
			(tee->rb_mgr.ring_start + tee->rb_mgr.wptr);

		rptr = ioपढ़ो32(tee->io_regs + tee->vdata->ring_rptr_reg);

		/* Check अगर ring buffer is full or command entry is रुकोing
		 * क्रम response from TEE
		 */
		अगर (!(tee->rb_mgr.wptr + माप(काष्ठा tee_ring_cmd) == rptr ||
		      cmd->flag == CMD_WAITING_FOR_RESPONSE))
			अवरोध;

		dev_dbg(tee->dev, "tee: ring buffer full. rptr = %u wptr = %u\n",
			rptr, tee->rb_mgr.wptr);

		/* Wait अगर ring buffer is full or TEE is processing data */
		mutex_unlock(&tee->rb_mgr.mutex);
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(10));
		mutex_lock(&tee->rb_mgr.mutex);

	पूर्ण जबतक (--nloop);

	अगर (!nloop &&
	    (tee->rb_mgr.wptr + माप(काष्ठा tee_ring_cmd) == rptr ||
	     cmd->flag == CMD_WAITING_FOR_RESPONSE)) अणु
		dev_err(tee->dev, "tee: ring buffer full. rptr = %u wptr = %u response flag %u\n",
			rptr, tee->rb_mgr.wptr, cmd->flag);
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	/* Do not submit command अगर PSP got disabled जबतक processing any
	 * command in another thपढ़ो
	 */
	अगर (psp_dead) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	/* Write command data पूर्णांकo ring buffer */
	cmd->cmd_id = cmd_id;
	cmd->cmd_state = TEE_CMD_STATE_INIT;
	स_रखो(&cmd->buf[0], 0, माप(cmd->buf));
	स_नकल(&cmd->buf[0], buf, len);

	/* Indicate driver is रुकोing क्रम response */
	cmd->flag = CMD_WAITING_FOR_RESPONSE;

	/* Update local copy of ग_लिखो poपूर्णांकer */
	tee->rb_mgr.wptr += माप(काष्ठा tee_ring_cmd);
	अगर (tee->rb_mgr.wptr >= tee->rb_mgr.ring_size)
		tee->rb_mgr.wptr = 0;

	/* Trigger पूर्णांकerrupt to Trusted OS */
	ioग_लिखो32(tee->rb_mgr.wptr, tee->io_regs + tee->vdata->ring_wptr_reg);

	/* The response is provided by Trusted OS in same
	 * location as submitted data entry within ring buffer.
	 */
	*resp = cmd;

unlock:
	mutex_unlock(&tee->rb_mgr.mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक tee_रुको_cmd_completion(काष्ठा psp_tee_device *tee,
				   काष्ठा tee_ring_cmd *resp,
				   अचिन्हित पूर्णांक समयout)
अणु
	/* ~1ms sleep per loop => nloop = समयout * 1000 */
	पूर्णांक nloop = समयout * 1000;

	जबतक (--nloop) अणु
		अगर (resp->cmd_state == TEE_CMD_STATE_COMPLETED)
			वापस 0;

		usleep_range(1000, 1100);
	पूर्ण

	dev_err(tee->dev, "tee: command 0x%x timed out, disabling PSP\n",
		resp->cmd_id);

	psp_dead = true;

	वापस -ETIMEDOUT;
पूर्ण

पूर्णांक psp_tee_process_cmd(क्रमागत tee_cmd_id cmd_id, व्योम *buf, माप_प्रकार len,
			u32 *status)
अणु
	काष्ठा psp_device *psp = psp_get_master_device();
	काष्ठा psp_tee_device *tee;
	काष्ठा tee_ring_cmd *resp;
	पूर्णांक ret;

	अगर (!buf || !status || !len || len > माप(resp->buf))
		वापस -EINVAL;

	*status = 0;

	अगर (!psp || !psp->tee_data)
		वापस -ENODEV;

	अगर (psp_dead)
		वापस -EBUSY;

	tee = psp->tee_data;

	ret = tee_submit_cmd(tee, cmd_id, buf, len, &resp);
	अगर (ret)
		वापस ret;

	ret = tee_रुको_cmd_completion(tee, resp, TEE_DEFAULT_TIMEOUT);
	अगर (ret) अणु
		resp->flag = CMD_RESPONSE_TIMEDOUT;
		वापस ret;
	पूर्ण

	स_नकल(buf, &resp->buf[0], len);
	*status = resp->status;

	resp->flag = CMD_RESPONSE_COPIED;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(psp_tee_process_cmd);

पूर्णांक psp_check_tee_status(व्योम)
अणु
	काष्ठा psp_device *psp = psp_get_master_device();

	अगर (!psp || !psp->tee_data)
		वापस -ENODEV;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(psp_check_tee_status);
