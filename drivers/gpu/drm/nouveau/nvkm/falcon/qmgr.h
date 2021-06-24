<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FALCON_QMGR_H__
#घोषणा __NVKM_FALCON_QMGR_H__
#समावेश <core/falcon.h>

#घोषणा HDR_SIZE माप(काष्ठा nvfw_falcon_msg)
#घोषणा QUEUE_ALIGNMENT 4
/* max size of the messages we can receive */
#घोषणा MSG_BUF_SIZE 128

/**
 * काष्ठा nvkm_falcon_qmgr_seq - keep track of ongoing commands
 *
 * Every समय a command is sent, a sequence is asचिन्हित to it so the
 * corresponding message can be matched. Upon receiving the message, a callback
 * can be called and/or a completion संकेतed.
 *
 * @id:		sequence ID
 * @state:	current state
 * @callback:	callback to call upon receiving matching message
 * @completion:	completion to संकेत after callback is called
 */
काष्ठा nvkm_falcon_qmgr_seq अणु
	u16 id;
	क्रमागत अणु
		SEQ_STATE_FREE = 0,
		SEQ_STATE_PENDING,
		SEQ_STATE_USED,
		SEQ_STATE_CANCELLED
	पूर्ण state;
	bool async;
	nvkm_falcon_qmgr_callback callback;
	व्योम *priv;
	काष्ठा completion करोne;
	पूर्णांक result;
पूर्ण;

/*
 * We can have an arbitrary number of sequences, but realistically we will
 * probably not use that much simultaneously.
 */
#घोषणा NVKM_FALCON_QMGR_SEQ_NUM 16

काष्ठा nvkm_falcon_qmgr अणु
	काष्ठा nvkm_falcon *falcon;

	काष्ठा अणु
		काष्ठा mutex mutex;
		काष्ठा nvkm_falcon_qmgr_seq id[NVKM_FALCON_QMGR_SEQ_NUM];
		अचिन्हित दीर्घ tbl[BITS_TO_LONGS(NVKM_FALCON_QMGR_SEQ_NUM)];
	पूर्ण seq;
पूर्ण;

काष्ठा nvkm_falcon_qmgr_seq *
nvkm_falcon_qmgr_seq_acquire(काष्ठा nvkm_falcon_qmgr *);
व्योम nvkm_falcon_qmgr_seq_release(काष्ठा nvkm_falcon_qmgr *,
				  काष्ठा nvkm_falcon_qmgr_seq *);

काष्ठा nvkm_falcon_cmdq अणु
	काष्ठा nvkm_falcon_qmgr *qmgr;
	स्थिर अक्षर *name;
	काष्ठा mutex mutex;
	काष्ठा completion पढ़ोy;

	u32 head_reg;
	u32 tail_reg;
	u32 offset;
	u32 size;

	u32 position;
पूर्ण;

काष्ठा nvkm_falcon_msgq अणु
	काष्ठा nvkm_falcon_qmgr *qmgr;
	स्थिर अक्षर *name;
	काष्ठा mutex mutex;

	u32 head_reg;
	u32 tail_reg;
	u32 offset;

	u32 position;
पूर्ण;

#घोषणा FLCNQ_PRINTK(t,q,f,a...)                                               \
       FLCN_PRINTK(t, (q)->qmgr->falcon, "%s: "f, (q)->name, ##a)
#घोषणा FLCNQ_DBG(q,f,a...) FLCNQ_PRINTK(debug, (q), f, ##a)
#घोषणा FLCNQ_ERR(q,f,a...) FLCNQ_PRINTK(error, (q), f, ##a)
#पूर्ण_अगर
