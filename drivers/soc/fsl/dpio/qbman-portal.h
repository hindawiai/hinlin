<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright (C) 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 *
 */
#अगर_अघोषित __FSL_QBMAN_PORTAL_H
#घोषणा __FSL_QBMAN_PORTAL_H

#समावेश <soc/fsl/dpaa2-fd.h>

#घोषणा QMAN_REV_4000   0x04000000
#घोषणा QMAN_REV_4100   0x04010000
#घोषणा QMAN_REV_4101   0x04010001
#घोषणा QMAN_REV_5000   0x05000000

#घोषणा QMAN_REV_MASK   0xffff0000

काष्ठा dpaa2_dq;
काष्ठा qbman_swp;

/* qbman software portal descriptor काष्ठाure */
काष्ठा qbman_swp_desc अणु
	व्योम *cena_bar; /* Cache-enabled portal base address */
	व्योम __iomem *cinh_bar; /* Cache-inhibited portal base address */
	u32 qman_version;
पूर्ण;

#घोषणा QBMAN_SWP_INTERRUPT_EQRI 0x01
#घोषणा QBMAN_SWP_INTERRUPT_EQDI 0x02
#घोषणा QBMAN_SWP_INTERRUPT_DQRI 0x04
#घोषणा QBMAN_SWP_INTERRUPT_RCRI 0x08
#घोषणा QBMAN_SWP_INTERRUPT_RCDI 0x10
#घोषणा QBMAN_SWP_INTERRUPT_VDCI 0x20

/* the काष्ठाure क्रम pull dequeue descriptor */
काष्ठा qbman_pull_desc अणु
	u8 verb;
	u8 numf;
	u8 tok;
	u8 reserved;
	__le32 dq_src;
	__le64 rsp_addr;
	u64 rsp_addr_virt;
	u8 padding[40];
पूर्ण;

क्रमागत qbman_pull_type_e अणु
	/* dequeue with priority precedence, respect पूर्णांकra-class scheduling */
	qbman_pull_type_prio = 1,
	/* dequeue with active FQ precedence, respect ICS */
	qbman_pull_type_active,
	/* dequeue with active FQ precedence, no ICS */
	qbman_pull_type_active_noics
पूर्ण;

/* Definitions क्रम parsing dequeue entries */
#घोषणा QBMAN_RESULT_MASK      0x7f
#घोषणा QBMAN_RESULT_DQ        0x60
#घोषणा QBMAN_RESULT_FQRN      0x21
#घोषणा QBMAN_RESULT_FQRNI     0x22
#घोषणा QBMAN_RESULT_FQPN      0x24
#घोषणा QBMAN_RESULT_FQDAN     0x25
#घोषणा QBMAN_RESULT_CDAN      0x26
#घोषणा QBMAN_RESULT_CSCN_MEM  0x27
#घोषणा QBMAN_RESULT_CGCU      0x28
#घोषणा QBMAN_RESULT_BPSCN     0x29
#घोषणा QBMAN_RESULT_CSCN_WQ   0x2a

/* QBMan FQ management command codes */
#घोषणा QBMAN_FQ_SCHEDULE	0x48
#घोषणा QBMAN_FQ_FORCE		0x49
#घोषणा QBMAN_FQ_XON		0x4d
#घोषणा QBMAN_FQ_XOFF		0x4e

/* काष्ठाure of enqueue descriptor */
काष्ठा qbman_eq_desc अणु
	u8 verb;
	u8 dca;
	__le16 seqnum;
	__le16 orpid;
	__le16 reserved1;
	__le32 tgtid;
	__le32 tag;
	__le16 qdbin;
	u8 qpri;
	u8 reserved[3];
	u8 wae;
	u8 rspid;
	__le64 rsp_addr;
पूर्ण;

काष्ठा qbman_eq_desc_with_fd अणु
	काष्ठा qbman_eq_desc desc;
	u8 fd[32];
पूर्ण;

/* buffer release descriptor */
काष्ठा qbman_release_desc अणु
	u8 verb;
	u8 reserved;
	__le16 bpid;
	__le32 reserved2;
	__le64 buf[7];
पूर्ण;

/* Management command result codes */
#घोषणा QBMAN_MC_RSLT_OK      0xf0

#घोषणा CODE_CDAN_WE_EN    0x1
#घोषणा CODE_CDAN_WE_CTX   0x4

/* portal data काष्ठाure */
काष्ठा qbman_swp अणु
	स्थिर काष्ठा qbman_swp_desc *desc;
	व्योम *addr_cena;
	व्योम __iomem *addr_cinh;

	/* Management commands */
	काष्ठा अणु
		u32 valid_bit; /* 0x00 or 0x80 */
	पूर्ण mc;

	/* Management response */
	काष्ठा अणु
		u32 valid_bit; /* 0x00 or 0x80 */
	पूर्ण mr;

	/* Push dequeues */
	u32 sdq;

	/* Volatile dequeues */
	काष्ठा अणु
		atomic_t available; /* indicates अगर a command can be sent */
		u32 valid_bit; /* 0x00 or 0x80 */
		काष्ठा dpaa2_dq *storage; /* शून्य अगर DQRR */
	पूर्ण vdq;

	/* DQRR */
	काष्ठा अणु
		u32 next_idx;
		u32 valid_bit;
		u8 dqrr_size;
		पूर्णांक reset_bug; /* indicates dqrr reset workaround is needed */
	पूर्ण dqrr;

	काष्ठा अणु
		u32 pi;
		u32 pi_vb;
		u32 pi_ring_size;
		u32 pi_ci_mask;
		u32 ci;
		पूर्णांक available;
		u32 pend;
		u32 no_pfdr;
	पूर्ण eqcr;

	spinlock_t access_spinlock;
पूर्ण;

/* Function poपूर्णांकers */
बाह्य
पूर्णांक (*qbman_swp_enqueue_ptr)(काष्ठा qbman_swp *s,
			     स्थिर काष्ठा qbman_eq_desc *d,
			     स्थिर काष्ठा dpaa2_fd *fd);
बाह्य
पूर्णांक (*qbman_swp_enqueue_multiple_ptr)(काष्ठा qbman_swp *s,
				      स्थिर काष्ठा qbman_eq_desc *d,
				      स्थिर काष्ठा dpaa2_fd *fd,
				      uपूर्णांक32_t *flags,
				      पूर्णांक num_frames);
बाह्य
पूर्णांक (*qbman_swp_enqueue_multiple_desc_ptr)(काष्ठा qbman_swp *s,
					   स्थिर काष्ठा qbman_eq_desc *d,
					   स्थिर काष्ठा dpaa2_fd *fd,
					   पूर्णांक num_frames);
बाह्य
पूर्णांक (*qbman_swp_pull_ptr)(काष्ठा qbman_swp *s, काष्ठा qbman_pull_desc *d);
बाह्य
स्थिर काष्ठा dpaa2_dq *(*qbman_swp_dqrr_next_ptr)(काष्ठा qbman_swp *s);
बाह्य
पूर्णांक (*qbman_swp_release_ptr)(काष्ठा qbman_swp *s,
			     स्थिर काष्ठा qbman_release_desc *d,
			     स्थिर u64 *buffers,
			     अचिन्हित पूर्णांक num_buffers);

/* Functions */
काष्ठा qbman_swp *qbman_swp_init(स्थिर काष्ठा qbman_swp_desc *d);
व्योम qbman_swp_finish(काष्ठा qbman_swp *p);
u32 qbman_swp_पूर्णांकerrupt_पढ़ो_status(काष्ठा qbman_swp *p);
व्योम qbman_swp_पूर्णांकerrupt_clear_status(काष्ठा qbman_swp *p, u32 mask);
u32 qbman_swp_पूर्णांकerrupt_get_trigger(काष्ठा qbman_swp *p);
व्योम qbman_swp_पूर्णांकerrupt_set_trigger(काष्ठा qbman_swp *p, u32 mask);
पूर्णांक qbman_swp_पूर्णांकerrupt_get_inhibit(काष्ठा qbman_swp *p);
व्योम qbman_swp_पूर्णांकerrupt_set_inhibit(काष्ठा qbman_swp *p, पूर्णांक inhibit);

व्योम qbman_swp_push_get(काष्ठा qbman_swp *p, u8 channel_idx, पूर्णांक *enabled);
व्योम qbman_swp_push_set(काष्ठा qbman_swp *p, u8 channel_idx, पूर्णांक enable);

व्योम qbman_pull_desc_clear(काष्ठा qbman_pull_desc *d);
व्योम qbman_pull_desc_set_storage(काष्ठा qbman_pull_desc *d,
				 काष्ठा dpaa2_dq *storage,
				 dma_addr_t storage_phys,
				 पूर्णांक stash);
व्योम qbman_pull_desc_set_numframes(काष्ठा qbman_pull_desc *d, u8 numframes);
व्योम qbman_pull_desc_set_fq(काष्ठा qbman_pull_desc *d, u32 fqid);
व्योम qbman_pull_desc_set_wq(काष्ठा qbman_pull_desc *d, u32 wqid,
			    क्रमागत qbman_pull_type_e dct);
व्योम qbman_pull_desc_set_channel(काष्ठा qbman_pull_desc *d, u32 chid,
				 क्रमागत qbman_pull_type_e dct);

व्योम qbman_swp_dqrr_consume(काष्ठा qbman_swp *s, स्थिर काष्ठा dpaa2_dq *dq);

पूर्णांक qbman_result_has_new_result(काष्ठा qbman_swp *p, स्थिर काष्ठा dpaa2_dq *dq);

व्योम qbman_eq_desc_clear(काष्ठा qbman_eq_desc *d);
व्योम qbman_eq_desc_set_no_orp(काष्ठा qbman_eq_desc *d, पूर्णांक respond_success);
व्योम qbman_eq_desc_set_token(काष्ठा qbman_eq_desc *d, u8 token);
व्योम qbman_eq_desc_set_fq(काष्ठा qbman_eq_desc *d, u32 fqid);
व्योम qbman_eq_desc_set_qd(काष्ठा qbman_eq_desc *d, u32 qdid,
			  u32 qd_bin, u32 qd_prio);


व्योम qbman_release_desc_clear(काष्ठा qbman_release_desc *d);
व्योम qbman_release_desc_set_bpid(काष्ठा qbman_release_desc *d, u16 bpid);
व्योम qbman_release_desc_set_rcdi(काष्ठा qbman_release_desc *d, पूर्णांक enable);

पूर्णांक qbman_swp_acquire(काष्ठा qbman_swp *s, u16 bpid, u64 *buffers,
		      अचिन्हित पूर्णांक num_buffers);
पूर्णांक qbman_swp_alt_fq_state(काष्ठा qbman_swp *s, u32 fqid,
			   u8 alt_fq_verb);
पूर्णांक qbman_swp_CDAN_set(काष्ठा qbman_swp *s, u16 channelid,
		       u8 we_mask, u8 cdan_en,
		       u64 ctx);

व्योम *qbman_swp_mc_start(काष्ठा qbman_swp *p);
व्योम qbman_swp_mc_submit(काष्ठा qbman_swp *p, व्योम *cmd, u8 cmd_verb);
व्योम *qbman_swp_mc_result(काष्ठा qbman_swp *p);

/**
 * qbman_swp_enqueue() - Issue an enqueue command
 * @s:  the software portal used क्रम enqueue
 * @d:  the enqueue descriptor
 * @fd: the frame descriptor to be enqueued
 *
 * Return 0 क्रम successful enqueue, -EBUSY अगर the EQCR is not पढ़ोy.
 */
अटल अंतरभूत पूर्णांक
qbman_swp_enqueue(काष्ठा qbman_swp *s, स्थिर काष्ठा qbman_eq_desc *d,
		  स्थिर काष्ठा dpaa2_fd *fd)
अणु
	वापस qbman_swp_enqueue_ptr(s, d, fd);
पूर्ण

/**
 * qbman_swp_enqueue_multiple() - Issue a multi enqueue command
 * using one enqueue descriptor
 * @s:  the software portal used क्रम enqueue
 * @d:  the enqueue descriptor
 * @fd: table poपूर्णांकer of frame descriptor table to be enqueued
 * @flags: table poपूर्णांकer of QBMAN_ENQUEUE_FLAG_DCA flags, not used अगर शून्य
 * @num_frames: number of fd to be enqueued
 *
 * Return the number of fd enqueued, or a negative error number.
 */
अटल अंतरभूत पूर्णांक
qbman_swp_enqueue_multiple(काष्ठा qbman_swp *s,
			   स्थिर काष्ठा qbman_eq_desc *d,
			   स्थिर काष्ठा dpaa2_fd *fd,
			   uपूर्णांक32_t *flags,
			   पूर्णांक num_frames)
अणु
	वापस qbman_swp_enqueue_multiple_ptr(s, d, fd, flags, num_frames);
पूर्ण

/**
 * qbman_swp_enqueue_multiple_desc() - Issue a multi enqueue command
 * using multiple enqueue descriptor
 * @s:  the software portal used क्रम enqueue
 * @d:  table of minimal enqueue descriptor
 * @fd: table poपूर्णांकer of frame descriptor table to be enqueued
 * @num_frames: number of fd to be enqueued
 *
 * Return the number of fd enqueued, or a negative error number.
 */
अटल अंतरभूत पूर्णांक
qbman_swp_enqueue_multiple_desc(काष्ठा qbman_swp *s,
				स्थिर काष्ठा qbman_eq_desc *d,
				स्थिर काष्ठा dpaa2_fd *fd,
				पूर्णांक num_frames)
अणु
	वापस qbman_swp_enqueue_multiple_desc_ptr(s, d, fd, num_frames);
पूर्ण

/**
 * qbman_result_is_DQ() - check अगर the dequeue result is a dequeue response
 * @dq: the dequeue result to be checked
 *
 * DQRR entries may contain non-dequeue results, ie. notअगरications
 */
अटल अंतरभूत पूर्णांक qbman_result_is_DQ(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस ((dq->dq.verb & QBMAN_RESULT_MASK) == QBMAN_RESULT_DQ);
पूर्ण

/**
 * qbman_result_is_SCN() - Check the dequeue result is notअगरication or not
 * @dq: the dequeue result to be checked
 *
 */
अटल अंतरभूत पूर्णांक qbman_result_is_SCN(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस !qbman_result_is_DQ(dq);
पूर्ण

/* FQ Data Availability */
अटल अंतरभूत पूर्णांक qbman_result_is_FQDAN(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस ((dq->dq.verb & QBMAN_RESULT_MASK) == QBMAN_RESULT_FQDAN);
पूर्ण

/* Channel Data Availability */
अटल अंतरभूत पूर्णांक qbman_result_is_CDAN(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस ((dq->dq.verb & QBMAN_RESULT_MASK) == QBMAN_RESULT_CDAN);
पूर्ण

/* Congestion State Change */
अटल अंतरभूत पूर्णांक qbman_result_is_CSCN(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस ((dq->dq.verb & QBMAN_RESULT_MASK) == QBMAN_RESULT_CSCN_WQ);
पूर्ण

/* Buffer Pool State Change */
अटल अंतरभूत पूर्णांक qbman_result_is_BPSCN(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस ((dq->dq.verb & QBMAN_RESULT_MASK) == QBMAN_RESULT_BPSCN);
पूर्ण

/* Congestion Group Count Update */
अटल अंतरभूत पूर्णांक qbman_result_is_CGCU(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस ((dq->dq.verb & QBMAN_RESULT_MASK) == QBMAN_RESULT_CGCU);
पूर्ण

/* Retirement */
अटल अंतरभूत पूर्णांक qbman_result_is_FQRN(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस ((dq->dq.verb & QBMAN_RESULT_MASK) == QBMAN_RESULT_FQRN);
पूर्ण

/* Retirement Immediate */
अटल अंतरभूत पूर्णांक qbman_result_is_FQRNI(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस ((dq->dq.verb & QBMAN_RESULT_MASK) == QBMAN_RESULT_FQRNI);
पूर्ण

 /* Park */
अटल अंतरभूत पूर्णांक qbman_result_is_FQPN(स्थिर काष्ठा dpaa2_dq *dq)
अणु
	वापस ((dq->dq.verb & QBMAN_RESULT_MASK) == QBMAN_RESULT_FQPN);
पूर्ण

/**
 * qbman_result_SCN_state() - Get the state field in State-change notअगरication
 */
अटल अंतरभूत u8 qbman_result_SCN_state(स्थिर काष्ठा dpaa2_dq *scn)
अणु
	वापस scn->scn.state;
पूर्ण

#घोषणा SCN_RID_MASK 0x00FFFFFF

/**
 * qbman_result_SCN_rid() - Get the resource id in State-change notअगरication
 */
अटल अंतरभूत u32 qbman_result_SCN_rid(स्थिर काष्ठा dpaa2_dq *scn)
अणु
	वापस le32_to_cpu(scn->scn.rid_tok) & SCN_RID_MASK;
पूर्ण

/**
 * qbman_result_SCN_ctx() - Get the context data in State-change notअगरication
 */
अटल अंतरभूत u64 qbman_result_SCN_ctx(स्थिर काष्ठा dpaa2_dq *scn)
अणु
	वापस le64_to_cpu(scn->scn.ctx);
पूर्ण

/**
 * qbman_swp_fq_schedule() - Move the fq to the scheduled state
 * @s:    the software portal object
 * @fqid: the index of frame queue to be scheduled
 *
 * There are a couple of dअगरferent ways that a FQ can end up parked state,
 * This schedules it.
 *
 * Return 0 क्रम success, or negative error code क्रम failure.
 */
अटल अंतरभूत पूर्णांक qbman_swp_fq_schedule(काष्ठा qbman_swp *s, u32 fqid)
अणु
	वापस qbman_swp_alt_fq_state(s, fqid, QBMAN_FQ_SCHEDULE);
पूर्ण

/**
 * qbman_swp_fq_क्रमce() - Force the FQ to fully scheduled state
 * @s:    the software portal object
 * @fqid: the index of frame queue to be क्रमced
 *
 * Force eligible will क्रमce a tentatively-scheduled FQ to be fully-scheduled
 * and thus be available क्रम selection by any channel-dequeuing behaviour (push
 * or pull). If the FQ is subsequently "dequeued" from the channel and is still
 * empty at the समय this happens, the resulting dq_entry will have no FD.
 * (qbman_result_DQ_fd() will वापस शून्य.)
 *
 * Return 0 क्रम success, or negative error code क्रम failure.
 */
अटल अंतरभूत पूर्णांक qbman_swp_fq_क्रमce(काष्ठा qbman_swp *s, u32 fqid)
अणु
	वापस qbman_swp_alt_fq_state(s, fqid, QBMAN_FQ_FORCE);
पूर्ण

/**
 * qbman_swp_fq_xon() - sets FQ flow-control to XON
 * @s:    the software portal object
 * @fqid: the index of frame queue
 *
 * This setting करोesn't affect enqueues to the FQ, just dequeues.
 *
 * Return 0 क्रम success, or negative error code क्रम failure.
 */
अटल अंतरभूत पूर्णांक qbman_swp_fq_xon(काष्ठा qbman_swp *s, u32 fqid)
अणु
	वापस qbman_swp_alt_fq_state(s, fqid, QBMAN_FQ_XON);
पूर्ण

/**
 * qbman_swp_fq_xoff() - sets FQ flow-control to XOFF
 * @s:    the software portal object
 * @fqid: the index of frame queue
 *
 * This setting करोesn't affect enqueues to the FQ, just dequeues.
 * XOFF FQs will reमुख्य in the tenatively-scheduled state, even when
 * non-empty, meaning they won't be selected क्रम scheduled dequeuing.
 * If a FQ is changed to XOFF after it had alपढ़ोy become truly-scheduled
 * to a channel, and a pull dequeue of that channel occurs that selects
 * that FQ क्रम dequeuing, then the resulting dq_entry will have no FD.
 * (qbman_result_DQ_fd() will वापस शून्य.)
 *
 * Return 0 क्रम success, or negative error code क्रम failure.
 */
अटल अंतरभूत पूर्णांक qbman_swp_fq_xoff(काष्ठा qbman_swp *s, u32 fqid)
अणु
	वापस qbman_swp_alt_fq_state(s, fqid, QBMAN_FQ_XOFF);
पूर्ण

/* If the user has been allocated a channel object that is going to generate
 * CDANs to another channel, then the qbman_swp_CDAN* functions will be
 * necessary.
 *
 * CDAN-enabled channels only generate a single CDAN notअगरication, after which
 * they need to be reenabled beक्रमe they'll generate another. The idea is
 * that pull dequeuing will occur in reaction to the CDAN, followed by a
 * reenable step. Each function generates a distinct command to hardware, so a
 * combination function is provided अगर the user wishes to modअगरy the "context"
 * (which shows up in each CDAN message) each समय they reenable, as a single
 * command to hardware.
 */

/**
 * qbman_swp_CDAN_set_context() - Set CDAN context
 * @s:         the software portal object
 * @channelid: the channel index
 * @ctx:       the context to be set in CDAN
 *
 * Return 0 क्रम success, or negative error code क्रम failure.
 */
अटल अंतरभूत पूर्णांक qbman_swp_CDAN_set_context(काष्ठा qbman_swp *s, u16 channelid,
					     u64 ctx)
अणु
	वापस qbman_swp_CDAN_set(s, channelid,
				  CODE_CDAN_WE_CTX,
				  0, ctx);
पूर्ण

/**
 * qbman_swp_CDAN_enable() - Enable CDAN क्रम the channel
 * @s:         the software portal object
 * @channelid: the index of the channel to generate CDAN
 *
 * Return 0 क्रम success, or negative error code क्रम failure.
 */
अटल अंतरभूत पूर्णांक qbman_swp_CDAN_enable(काष्ठा qbman_swp *s, u16 channelid)
अणु
	वापस qbman_swp_CDAN_set(s, channelid,
				  CODE_CDAN_WE_EN,
				  1, 0);
पूर्ण

/**
 * qbman_swp_CDAN_disable() - disable CDAN क्रम the channel
 * @s:         the software portal object
 * @channelid: the index of the channel to generate CDAN
 *
 * Return 0 क्रम success, or negative error code क्रम failure.
 */
अटल अंतरभूत पूर्णांक qbman_swp_CDAN_disable(काष्ठा qbman_swp *s, u16 channelid)
अणु
	वापस qbman_swp_CDAN_set(s, channelid,
				  CODE_CDAN_WE_EN,
				  0, 0);
पूर्ण

/**
 * qbman_swp_CDAN_set_context_enable() - Set CDAN contest and enable CDAN
 * @s:         the software portal object
 * @channelid: the index of the channel to generate CDAN
 * @ctx:i      the context set in CDAN
 *
 * Return 0 क्रम success, or negative error code क्रम failure.
 */
अटल अंतरभूत पूर्णांक qbman_swp_CDAN_set_context_enable(काष्ठा qbman_swp *s,
						    u16 channelid,
						    u64 ctx)
अणु
	वापस qbman_swp_CDAN_set(s, channelid,
				  CODE_CDAN_WE_EN | CODE_CDAN_WE_CTX,
				  1, ctx);
पूर्ण

/* Wraps up submit + poll-क्रम-result */
अटल अंतरभूत व्योम *qbman_swp_mc_complete(काष्ठा qbman_swp *swp, व्योम *cmd,
					  u8 cmd_verb)
अणु
	पूर्णांक loopvar = 2000;

	qbman_swp_mc_submit(swp, cmd, cmd_verb);

	करो अणु
		cmd = qbman_swp_mc_result(swp);
	पूर्ण जबतक (!cmd && loopvar--);

	WARN_ON(!loopvar);

	वापस cmd;
पूर्ण

/* Query APIs */
काष्ठा qbman_fq_query_np_rslt अणु
	u8 verb;
	u8 rslt;
	u8 st1;
	u8 st2;
	u8 reserved[2];
	__le16 od1_sfdr;
	__le16 od2_sfdr;
	__le16 od3_sfdr;
	__le16 ra1_sfdr;
	__le16 ra2_sfdr;
	__le32 pfdr_hptr;
	__le32 pfdr_tptr;
	__le32 frm_cnt;
	__le32 byte_cnt;
	__le16 ics_surp;
	u8 is;
	u8 reserved2[29];
पूर्ण;

पूर्णांक qbman_fq_query_state(काष्ठा qbman_swp *s, u32 fqid,
			 काष्ठा qbman_fq_query_np_rslt *r);
u32 qbman_fq_state_frame_count(स्थिर काष्ठा qbman_fq_query_np_rslt *r);
u32 qbman_fq_state_byte_count(स्थिर काष्ठा qbman_fq_query_np_rslt *r);

काष्ठा qbman_bp_query_rslt अणु
	u8 verb;
	u8 rslt;
	u8 reserved[4];
	u8 bdi;
	u8 state;
	__le32 fill;
	__le32 hकरोtr;
	__le16 swdet;
	__le16 swdxt;
	__le16 hwdet;
	__le16 hwdxt;
	__le16 swset;
	__le16 swsxt;
	__le16 vbpid;
	__le16 icid;
	__le64 bpscn_addr;
	__le64 bpscn_ctx;
	__le16 hw_targ;
	u8 dbe;
	u8 reserved2;
	u8 sdcnt;
	u8 hdcnt;
	u8 sscnt;
	u8 reserved3[9];
पूर्ण;

पूर्णांक qbman_bp_query(काष्ठा qbman_swp *s, u16 bpid,
		   काष्ठा qbman_bp_query_rslt *r);

u32 qbman_bp_info_num_मुक्त_bufs(काष्ठा qbman_bp_query_rslt *a);

/**
 * qbman_swp_release() - Issue a buffer release command
 * @s:           the software portal object
 * @d:           the release descriptor
 * @buffers:     a poपूर्णांकer poपूर्णांकing to the buffer address to be released
 * @num_buffers: number of buffers to be released,  must be less than 8
 *
 * Return 0 क्रम success, -EBUSY अगर the release command ring is not पढ़ोy.
 */
अटल अंतरभूत पूर्णांक qbman_swp_release(काष्ठा qbman_swp *s,
				    स्थिर काष्ठा qbman_release_desc *d,
				    स्थिर u64 *buffers,
				    अचिन्हित पूर्णांक num_buffers)
अणु
	वापस qbman_swp_release_ptr(s, d, buffers, num_buffers);
पूर्ण

/**
 * qbman_swp_pull() - Issue the pull dequeue command
 * @s: the software portal object
 * @d: the software portal descriptor which has been configured with
 *     the set of qbman_pull_desc_set_*() calls
 *
 * Return 0 क्रम success, and -EBUSY अगर the software portal is not पढ़ोy
 * to करो pull dequeue.
 */
अटल अंतरभूत पूर्णांक qbman_swp_pull(काष्ठा qbman_swp *s,
				 काष्ठा qbman_pull_desc *d)
अणु
	वापस qbman_swp_pull_ptr(s, d);
पूर्ण

/**
 * qbman_swp_dqrr_next() - Get an valid DQRR entry
 * @s: the software portal object
 *
 * Return शून्य अगर there are no unconsumed DQRR entries. Return a DQRR entry
 * only once, so repeated calls can वापस a sequence of DQRR entries, without
 * requiring they be consumed immediately or in any particular order.
 */
अटल अंतरभूत स्थिर काष्ठा dpaa2_dq *qbman_swp_dqrr_next(काष्ठा qbman_swp *s)
अणु
	वापस qbman_swp_dqrr_next_ptr(s);
पूर्ण

#पूर्ण_अगर /* __FSL_QBMAN_PORTAL_H */
