<शैली गुरु>
/*
 * Copyright (c) 2017, NVIDIA CORPORATION. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#समावेश "qmgr.h"

अटल bool
nvkm_falcon_cmdq_has_room(काष्ठा nvkm_falcon_cmdq *cmdq, u32 size, bool *शुरुआत)
अणु
	u32 head = nvkm_falcon_rd32(cmdq->qmgr->falcon, cmdq->head_reg);
	u32 tail = nvkm_falcon_rd32(cmdq->qmgr->falcon, cmdq->tail_reg);
	u32 मुक्त;

	size = ALIGN(size, QUEUE_ALIGNMENT);

	अगर (head >= tail) अणु
		मुक्त = cmdq->offset + cmdq->size - head;
		मुक्त -= HDR_SIZE;

		अगर (size > मुक्त) अणु
			*शुरुआत = true;
			head = cmdq->offset;
		पूर्ण
	पूर्ण

	अगर (head < tail)
		मुक्त = tail - head - 1;

	वापस size <= मुक्त;
पूर्ण

अटल व्योम
nvkm_falcon_cmdq_push(काष्ठा nvkm_falcon_cmdq *cmdq, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_falcon *falcon = cmdq->qmgr->falcon;
	nvkm_falcon_load_dmem(falcon, data, cmdq->position, size, 0);
	cmdq->position += ALIGN(size, QUEUE_ALIGNMENT);
पूर्ण

अटल व्योम
nvkm_falcon_cmdq_शुरुआत(काष्ठा nvkm_falcon_cmdq *cmdq)
अणु
	काष्ठा nvfw_falcon_cmd cmd;

	cmd.unit_id = NV_FALCON_CMD_UNIT_ID_REWIND;
	cmd.size = माप(cmd);
	nvkm_falcon_cmdq_push(cmdq, &cmd, cmd.size);

	cmdq->position = cmdq->offset;
पूर्ण

अटल पूर्णांक
nvkm_falcon_cmdq_खोलो(काष्ठा nvkm_falcon_cmdq *cmdq, u32 size)
अणु
	काष्ठा nvkm_falcon *falcon = cmdq->qmgr->falcon;
	bool शुरुआत = false;

	mutex_lock(&cmdq->mutex);

	अगर (!nvkm_falcon_cmdq_has_room(cmdq, size, &शुरुआत)) अणु
		FLCNQ_DBG(cmdq, "queue full");
		mutex_unlock(&cmdq->mutex);
		वापस -EAGAIN;
	पूर्ण

	cmdq->position = nvkm_falcon_rd32(falcon, cmdq->head_reg);

	अगर (शुरुआत)
		nvkm_falcon_cmdq_शुरुआत(cmdq);

	वापस 0;
पूर्ण

अटल व्योम
nvkm_falcon_cmdq_बंद(काष्ठा nvkm_falcon_cmdq *cmdq)
अणु
	nvkm_falcon_wr32(cmdq->qmgr->falcon, cmdq->head_reg, cmdq->position);
	mutex_unlock(&cmdq->mutex);
पूर्ण

अटल पूर्णांक
nvkm_falcon_cmdq_ग_लिखो(काष्ठा nvkm_falcon_cmdq *cmdq, काष्ठा nvfw_falcon_cmd *cmd)
अणु
	अटल अचिन्हित समयout = 2000;
	अचिन्हित दीर्घ end_jअगरfies = jअगरfies + msecs_to_jअगरfies(समयout);
	पूर्णांक ret = -EAGAIN;

	जबतक (ret == -EAGAIN && समय_beक्रमe(jअगरfies, end_jअगरfies))
		ret = nvkm_falcon_cmdq_खोलो(cmdq, cmd->size);
	अगर (ret) अणु
		FLCNQ_ERR(cmdq, "timeout waiting for queue space");
		वापस ret;
	पूर्ण

	nvkm_falcon_cmdq_push(cmdq, cmd, cmd->size);
	nvkm_falcon_cmdq_बंद(cmdq);
	वापस ret;
पूर्ण

/* specअगरies that we want to know the command status in the answer message */
#घोषणा CMD_FLAGS_STATUS BIT(0)
/* specअगरies that we want an पूर्णांकerrupt when the answer message is queued */
#घोषणा CMD_FLAGS_INTR BIT(1)

पूर्णांक
nvkm_falcon_cmdq_send(काष्ठा nvkm_falcon_cmdq *cmdq, काष्ठा nvfw_falcon_cmd *cmd,
		      nvkm_falcon_qmgr_callback cb, व्योम *priv,
		      अचिन्हित दीर्घ समयout)
अणु
	काष्ठा nvkm_falcon_qmgr_seq *seq;
	पूर्णांक ret;

	अगर (!रुको_क्रम_completion_समयout(&cmdq->पढ़ोy,
					 msecs_to_jअगरfies(1000))) अणु
		FLCNQ_ERR(cmdq, "timeout waiting for queue ready");
		वापस -ETIMEDOUT;
	पूर्ण

	seq = nvkm_falcon_qmgr_seq_acquire(cmdq->qmgr);
	अगर (IS_ERR(seq))
		वापस PTR_ERR(seq);

	cmd->seq_id = seq->id;
	cmd->ctrl_flags = CMD_FLAGS_STATUS | CMD_FLAGS_INTR;

	seq->state = SEQ_STATE_USED;
	seq->async = !समयout;
	seq->callback = cb;
	seq->priv = priv;

	ret = nvkm_falcon_cmdq_ग_लिखो(cmdq, cmd);
	अगर (ret) अणु
		seq->state = SEQ_STATE_PENDING;
		nvkm_falcon_qmgr_seq_release(cmdq->qmgr, seq);
		वापस ret;
	पूर्ण

	अगर (!seq->async) अणु
		अगर (!रुको_क्रम_completion_समयout(&seq->करोne, समयout)) अणु
			FLCNQ_ERR(cmdq, "timeout waiting for reply");
			वापस -ETIMEDOUT;
		पूर्ण
		ret = seq->result;
		nvkm_falcon_qmgr_seq_release(cmdq->qmgr, seq);
	पूर्ण

	वापस ret;
पूर्ण

व्योम
nvkm_falcon_cmdq_fini(काष्ठा nvkm_falcon_cmdq *cmdq)
अणु
	reinit_completion(&cmdq->पढ़ोy);
पूर्ण

व्योम
nvkm_falcon_cmdq_init(काष्ठा nvkm_falcon_cmdq *cmdq,
		      u32 index, u32 offset, u32 size)
अणु
	स्थिर काष्ठा nvkm_falcon_func *func = cmdq->qmgr->falcon->func;

	cmdq->head_reg = func->cmdq.head + index * func->cmdq.stride;
	cmdq->tail_reg = func->cmdq.tail + index * func->cmdq.stride;
	cmdq->offset = offset;
	cmdq->size = size;
	complete_all(&cmdq->पढ़ोy);

	FLCNQ_DBG(cmdq, "initialised @ index %d offset 0x%08x size 0x%08x",
		  index, cmdq->offset, cmdq->size);
पूर्ण

व्योम
nvkm_falcon_cmdq_del(काष्ठा nvkm_falcon_cmdq **pcmdq)
अणु
	काष्ठा nvkm_falcon_cmdq *cmdq = *pcmdq;
	अगर (cmdq) अणु
		kमुक्त(*pcmdq);
		*pcmdq = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_falcon_cmdq_new(काष्ठा nvkm_falcon_qmgr *qmgr, स्थिर अक्षर *name,
		     काष्ठा nvkm_falcon_cmdq **pcmdq)
अणु
	काष्ठा nvkm_falcon_cmdq *cmdq = *pcmdq;

	अगर (!(cmdq = *pcmdq = kzalloc(माप(*cmdq), GFP_KERNEL)))
		वापस -ENOMEM;

	cmdq->qmgr = qmgr;
	cmdq->name = name;
	mutex_init(&cmdq->mutex);
	init_completion(&cmdq->पढ़ोy);
	वापस 0;
पूर्ण
