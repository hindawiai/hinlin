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

अटल व्योम
nvkm_falcon_msgq_खोलो(काष्ठा nvkm_falcon_msgq *msgq)
अणु
	mutex_lock(&msgq->mutex);
	msgq->position = nvkm_falcon_rd32(msgq->qmgr->falcon, msgq->tail_reg);
पूर्ण

अटल व्योम
nvkm_falcon_msgq_बंद(काष्ठा nvkm_falcon_msgq *msgq, bool commit)
अणु
	काष्ठा nvkm_falcon *falcon = msgq->qmgr->falcon;

	अगर (commit)
		nvkm_falcon_wr32(falcon, msgq->tail_reg, msgq->position);

	mutex_unlock(&msgq->mutex);
पूर्ण

अटल bool
nvkm_falcon_msgq_empty(काष्ठा nvkm_falcon_msgq *msgq)
अणु
	u32 head = nvkm_falcon_rd32(msgq->qmgr->falcon, msgq->head_reg);
	u32 tail = nvkm_falcon_rd32(msgq->qmgr->falcon, msgq->tail_reg);
	वापस head == tail;
पूर्ण

अटल पूर्णांक
nvkm_falcon_msgq_pop(काष्ठा nvkm_falcon_msgq *msgq, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_falcon *falcon = msgq->qmgr->falcon;
	u32 head, tail, available;

	head = nvkm_falcon_rd32(falcon, msgq->head_reg);
	/* has the buffer looped? */
	अगर (head < msgq->position)
		msgq->position = msgq->offset;

	tail = msgq->position;

	available = head - tail;
	अगर (size > available) अणु
		FLCNQ_ERR(msgq, "requested %d bytes, but only %d available",
			  size, available);
		वापस -EINVAL;
	पूर्ण

	nvkm_falcon_पढ़ो_dmem(falcon, tail, size, 0, data);
	msgq->position += ALIGN(size, QUEUE_ALIGNMENT);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_falcon_msgq_पढ़ो(काष्ठा nvkm_falcon_msgq *msgq, काष्ठा nvfw_falcon_msg *hdr)
अणु
	पूर्णांक ret = 0;

	nvkm_falcon_msgq_खोलो(msgq);

	अगर (nvkm_falcon_msgq_empty(msgq))
		जाओ बंद;

	ret = nvkm_falcon_msgq_pop(msgq, hdr, HDR_SIZE);
	अगर (ret) अणु
		FLCNQ_ERR(msgq, "failed to read message header");
		जाओ बंद;
	पूर्ण

	अगर (hdr->size > MSG_BUF_SIZE) अणु
		FLCNQ_ERR(msgq, "message too big, %d bytes", hdr->size);
		ret = -ENOSPC;
		जाओ बंद;
	पूर्ण

	अगर (hdr->size > HDR_SIZE) अणु
		u32 पढ़ो_size = hdr->size - HDR_SIZE;

		ret = nvkm_falcon_msgq_pop(msgq, (hdr + 1), पढ़ो_size);
		अगर (ret) अणु
			FLCNQ_ERR(msgq, "failed to read message data");
			जाओ बंद;
		पूर्ण
	पूर्ण

	ret = 1;
बंद:
	nvkm_falcon_msgq_बंद(msgq, (ret >= 0));
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_falcon_msgq_exec(काष्ठा nvkm_falcon_msgq *msgq, काष्ठा nvfw_falcon_msg *hdr)
अणु
	काष्ठा nvkm_falcon_qmgr_seq *seq;

	seq = &msgq->qmgr->seq.id[hdr->seq_id];
	अगर (seq->state != SEQ_STATE_USED && seq->state != SEQ_STATE_CANCELLED) अणु
		FLCNQ_ERR(msgq, "message for unknown sequence %08x", seq->id);
		वापस -EINVAL;
	पूर्ण

	अगर (seq->state == SEQ_STATE_USED) अणु
		अगर (seq->callback)
			seq->result = seq->callback(seq->priv, hdr);
	पूर्ण

	अगर (seq->async) अणु
		nvkm_falcon_qmgr_seq_release(msgq->qmgr, seq);
		वापस 0;
	पूर्ण

	complete_all(&seq->करोne);
	वापस 0;
पूर्ण

व्योम
nvkm_falcon_msgq_recv(काष्ठा nvkm_falcon_msgq *msgq)
अणु
	/*
	 * We are invoked from a worker thपढ़ो, so normally we have plenty of
	 * stack space to work with.
	 */
	u8 msg_buffer[MSG_BUF_SIZE];
	काष्ठा nvfw_falcon_msg *hdr = (व्योम *)msg_buffer;

	जबतक (nvkm_falcon_msgq_पढ़ो(msgq, hdr) > 0)
		nvkm_falcon_msgq_exec(msgq, hdr);
पूर्ण

पूर्णांक
nvkm_falcon_msgq_recv_iniपंचांगsg(काष्ठा nvkm_falcon_msgq *msgq,
			      व्योम *data, u32 size)
अणु
	काष्ठा nvkm_falcon *falcon = msgq->qmgr->falcon;
	काष्ठा nvfw_falcon_msg *hdr = data;
	पूर्णांक ret;

	msgq->head_reg = falcon->func->msgq.head;
	msgq->tail_reg = falcon->func->msgq.tail;
	msgq->offset = nvkm_falcon_rd32(falcon, falcon->func->msgq.tail);

	nvkm_falcon_msgq_खोलो(msgq);
	ret = nvkm_falcon_msgq_pop(msgq, data, size);
	अगर (ret == 0 && hdr->size != size) अणु
		FLCN_ERR(falcon, "unexpected init message size %d vs %d",
			 hdr->size, size);
		ret = -EINVAL;
	पूर्ण
	nvkm_falcon_msgq_बंद(msgq, ret == 0);
	वापस ret;
पूर्ण

व्योम
nvkm_falcon_msgq_init(काष्ठा nvkm_falcon_msgq *msgq,
		      u32 index, u32 offset, u32 size)
अणु
	स्थिर काष्ठा nvkm_falcon_func *func = msgq->qmgr->falcon->func;

	msgq->head_reg = func->msgq.head + index * func->msgq.stride;
	msgq->tail_reg = func->msgq.tail + index * func->msgq.stride;
	msgq->offset = offset;

	FLCNQ_DBG(msgq, "initialised @ index %d offset 0x%08x size 0x%08x",
		  index, msgq->offset, size);
पूर्ण

व्योम
nvkm_falcon_msgq_del(काष्ठा nvkm_falcon_msgq **pmsgq)
अणु
	काष्ठा nvkm_falcon_msgq *msgq = *pmsgq;
	अगर (msgq) अणु
		kमुक्त(*pmsgq);
		*pmsgq = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_falcon_msgq_new(काष्ठा nvkm_falcon_qmgr *qmgr, स्थिर अक्षर *name,
		     काष्ठा nvkm_falcon_msgq **pmsgq)
अणु
	काष्ठा nvkm_falcon_msgq *msgq = *pmsgq;

	अगर (!(msgq = *pmsgq = kzalloc(माप(*msgq), GFP_KERNEL)))
		वापस -ENOMEM;

	msgq->qmgr = qmgr;
	msgq->name = name;
	mutex_init(&msgq->mutex);
	वापस 0;
पूर्ण
