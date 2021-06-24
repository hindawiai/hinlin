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

काष्ठा nvkm_falcon_qmgr_seq *
nvkm_falcon_qmgr_seq_acquire(काष्ठा nvkm_falcon_qmgr *qmgr)
अणु
	स्थिर काष्ठा nvkm_subdev *subdev = qmgr->falcon->owner;
	काष्ठा nvkm_falcon_qmgr_seq *seq;
	u32 index;

	mutex_lock(&qmgr->seq.mutex);
	index = find_first_zero_bit(qmgr->seq.tbl, NVKM_FALCON_QMGR_SEQ_NUM);
	अगर (index >= NVKM_FALCON_QMGR_SEQ_NUM) अणु
		nvkm_error(subdev, "no free sequence available\n");
		mutex_unlock(&qmgr->seq.mutex);
		वापस ERR_PTR(-EAGAIN);
	पूर्ण

	set_bit(index, qmgr->seq.tbl);
	mutex_unlock(&qmgr->seq.mutex);

	seq = &qmgr->seq.id[index];
	seq->state = SEQ_STATE_PENDING;
	वापस seq;
पूर्ण

व्योम
nvkm_falcon_qmgr_seq_release(काष्ठा nvkm_falcon_qmgr *qmgr,
			     काष्ठा nvkm_falcon_qmgr_seq *seq)
अणु
	/* no need to acquire seq.mutex since clear_bit is atomic */
	seq->state = SEQ_STATE_FREE;
	seq->callback = शून्य;
	reinit_completion(&seq->करोne);
	clear_bit(seq->id, qmgr->seq.tbl);
पूर्ण

व्योम
nvkm_falcon_qmgr_del(काष्ठा nvkm_falcon_qmgr **pqmgr)
अणु
	काष्ठा nvkm_falcon_qmgr *qmgr = *pqmgr;
	अगर (qmgr) अणु
		kमुक्त(*pqmgr);
		*pqmgr = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_falcon_qmgr_new(काष्ठा nvkm_falcon *falcon,
		     काष्ठा nvkm_falcon_qmgr **pqmgr)
अणु
	काष्ठा nvkm_falcon_qmgr *qmgr;
	पूर्णांक i;

	अगर (!(qmgr = *pqmgr = kzalloc(माप(*qmgr), GFP_KERNEL)))
		वापस -ENOMEM;

	qmgr->falcon = falcon;
	mutex_init(&qmgr->seq.mutex);
	क्रम (i = 0; i < NVKM_FALCON_QMGR_SEQ_NUM; i++) अणु
		qmgr->seq.id[i].id = i;
		init_completion(&qmgr->seq.id[i].करोne);
	पूर्ण

	वापस 0;
पूर्ण
