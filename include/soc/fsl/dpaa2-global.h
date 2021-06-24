<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2016 NXP
 *
 */
#अगर_अघोषित __FSL_DPAA2_GLOBAL_H
#घोषणा __FSL_DPAA2_GLOBAL_H

#समावेश <linux/types.h>
#समावेश <linux/cpumask.h>
#समावेश "dpaa2-fd.h"

काष्ठा dpaa2_dq अणु
	जोड़ अणु
		काष्ठा common अणु
			u8 verb;
			u8 reserved[63];
		पूर्ण common;
		काष्ठा dq अणु
			u8 verb;
			u8 stat;
			__le16 seqnum;
			__le16 oprid;
			u8 reserved;
			u8 tok;
			__le32 fqid;
			u32 reserved2;
			__le32 fq_byte_cnt;
			__le32 fq_frm_cnt;
			__le64 fqd_ctx;
			u8 fd[32];
		पूर्ण dq;
		काष्ठा scn अणु
			u8 verb;
			u8 stat;
			u8 state;
			u8 reserved;
			__le32 rid_tok;
			__le64 ctx;
		पूर्ण scn;
	पूर्ण;
पूर्ण;

/* Parsing frame dequeue results */
/* FQ empty */
#घोषणा DPAA2_DQ_STAT_FQEMPTY       0x80
/* FQ held active */
#घोषणा DPAA2_DQ_STAT_HELDACTIVE    0x40
/* FQ क्रमce eligible */
#घोषणा DPAA2_DQ_STAT_FORCEELIGIBLE 0x20
/* valid frame */
#घोषणा DPAA2_DQ_STAT_VALIDFRAME    0x10
/* FQ ODP enable */
#घोषणा DPAA2_DQ_STAT_ODPVALID      0x04
/* अस्थिर dequeue */
#घोषणा DPAA2_DQ_STAT_VOLATILE      0x02
/* अस्थिर dequeue command is expired */
#घोषणा DPAA2_DQ_STAT_EXPIRED       0x01

#घोषणा DQ_FQID_MASK		0x00FFFFFF
#घोषणा DQ_FRAME_COUNT_MASK	0x00FFFFFF

/**
 * dpaa2_dq_flags() - Get the stat field of dequeue response
 * @dq: the dequeue result.
 */
अटल अंतरभूत u32 dpaa2_dq_flags(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस dq->dq.stat;
पूर्ण

/**
 * dpaa2_dq_is_pull() - Check whether the dq response is from a pull
 *                      command.
 * @dq: the dequeue result
 *
 * Return 1 क्रम अस्थिर(pull) dequeue, 0 क्रम अटल dequeue.
 */
अटल अंतरभूत पूर्णांक dpaa2_dq_is_pull(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस (पूर्णांक)(dpaa2_dq_flags(dq) & DPAA2_DQ_STAT_VOLATILE);
पूर्ण

/**
 * dpaa2_dq_is_pull_complete() - Check whether the pull command is completed.
 * @dq: the dequeue result
 *
 * Return boolean.
 */
अटल अंतरभूत bool dpaa2_dq_is_pull_complete(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस !!(dpaa2_dq_flags(dq) & DPAA2_DQ_STAT_EXPIRED);
पूर्ण

/**
 * dpaa2_dq_seqnum() - Get the seqnum field in dequeue response
 * @dq: the dequeue result
 *
 * seqnum is valid only अगर VALIDFRAME flag is TRUE
 *
 * Return seqnum.
 */
अटल अंतरभूत u16 dpaa2_dq_seqnum(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस le16_to_cpu(dq->dq.seqnum);
पूर्ण

/**
 * dpaa2_dq_odpid() - Get the odpid field in dequeue response
 * @dq: the dequeue result
 *
 * odpid is valid only अगर ODPVALID flag is TRUE.
 *
 * Return odpid.
 */
अटल अंतरभूत u16 dpaa2_dq_odpid(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस le16_to_cpu(dq->dq.oprid);
पूर्ण

/**
 * dpaa2_dq_fqid() - Get the fqid in dequeue response
 * @dq: the dequeue result
 *
 * Return fqid.
 */
अटल अंतरभूत u32 dpaa2_dq_fqid(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस le32_to_cpu(dq->dq.fqid) & DQ_FQID_MASK;
पूर्ण

/**
 * dpaa2_dq_byte_count() - Get the byte count in dequeue response
 * @dq: the dequeue result
 *
 * Return the byte count reमुख्यing in the FQ.
 */
अटल अंतरभूत u32 dpaa2_dq_byte_count(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस le32_to_cpu(dq->dq.fq_byte_cnt);
पूर्ण

/**
 * dpaa2_dq_frame_count() - Get the frame count in dequeue response
 * @dq: the dequeue result
 *
 * Return the frame count reमुख्यing in the FQ.
 */
अटल अंतरभूत u32 dpaa2_dq_frame_count(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस le32_to_cpu(dq->dq.fq_frm_cnt) & DQ_FRAME_COUNT_MASK;
पूर्ण

/**
 * dpaa2_dq_fd_ctx() - Get the frame queue context in dequeue response
 * @dq: the dequeue result
 *
 * Return the frame queue context.
 */
अटल अंतरभूत u64 dpaa2_dq_fqd_ctx(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस le64_to_cpu(dq->dq.fqd_ctx);
पूर्ण

/**
 * dpaa2_dq_fd() - Get the frame descriptor in dequeue response
 * @dq: the dequeue result
 *
 * Return the frame descriptor.
 */
अटल अंतरभूत स्थिर काष्ठा dpaa2_fd *dpaa2_dq_fd(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस (स्थिर काष्ठा dpaa2_fd *)&dq->dq.fd[0];
पूर्ण

#घोषणा DPAA2_CSCN_SIZE		माप(काष्ठा dpaa2_dq)
#घोषणा DPAA2_CSCN_ALIGN	16
#घोषणा DPAA2_CSCN_STATE_CG	BIT(0)

/**
 * dpaa2_cscn_state_congested() - Check congestion state
 * @cscn: congestion SCN (delivered to WQ or memory)
 *
i * Return true is congested.
 */
अटल अंतरभूत bool dpaa2_cscn_state_congested(काष्ठा dpaa2_dq *cscn)
अणु
	वापस !!(cscn->scn.state & DPAA2_CSCN_STATE_CG);
पूर्ण

#पूर्ण_अगर /* __FSL_DPAA2_GLOBAL_H */
