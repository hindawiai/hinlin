<शैली गुरु>
/* Copyright 2008 - 2016 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "qman_priv.h"

#घोषणा DQRR_MAXFILL	15
#घोषणा EQCR_ITHRESH	4	/* अगर EQCR congests, पूर्णांकerrupt threshold */
#घोषणा IRQNAME		"QMan portal %d"
#घोषणा MAX_IRQNAME	16	/* big enough क्रम "QMan portal %d" */
#घोषणा QMAN_POLL_LIMIT 32
#घोषणा QMAN_PIRQ_DQRR_ITHRESH 12
#घोषणा QMAN_DQRR_IT_MAX 15
#घोषणा QMAN_ITP_MAX 0xFFF
#घोषणा QMAN_PIRQ_MR_ITHRESH 4
#घोषणा QMAN_PIRQ_IPERIOD 100

/* Portal रेजिस्टर assists */

#अगर defined(CONFIG_ARM) || defined(CONFIG_ARM64)
/* Cache-inhibited रेजिस्टर offsets */
#घोषणा QM_REG_EQCR_PI_CINH	0x3000
#घोषणा QM_REG_EQCR_CI_CINH	0x3040
#घोषणा QM_REG_EQCR_ITR		0x3080
#घोषणा QM_REG_DQRR_PI_CINH	0x3100
#घोषणा QM_REG_DQRR_CI_CINH	0x3140
#घोषणा QM_REG_DQRR_ITR		0x3180
#घोषणा QM_REG_DQRR_DCAP	0x31C0
#घोषणा QM_REG_DQRR_SDQCR	0x3200
#घोषणा QM_REG_DQRR_VDQCR	0x3240
#घोषणा QM_REG_DQRR_PDQCR	0x3280
#घोषणा QM_REG_MR_PI_CINH	0x3300
#घोषणा QM_REG_MR_CI_CINH	0x3340
#घोषणा QM_REG_MR_ITR		0x3380
#घोषणा QM_REG_CFG		0x3500
#घोषणा QM_REG_ISR		0x3600
#घोषणा QM_REG_IER		0x3640
#घोषणा QM_REG_ISDR		0x3680
#घोषणा QM_REG_IIR		0x36C0
#घोषणा QM_REG_ITPR		0x3740

/* Cache-enabled रेजिस्टर offsets */
#घोषणा QM_CL_EQCR		0x0000
#घोषणा QM_CL_DQRR		0x1000
#घोषणा QM_CL_MR		0x2000
#घोषणा QM_CL_EQCR_PI_CENA	0x3000
#घोषणा QM_CL_EQCR_CI_CENA	0x3040
#घोषणा QM_CL_DQRR_PI_CENA	0x3100
#घोषणा QM_CL_DQRR_CI_CENA	0x3140
#घोषणा QM_CL_MR_PI_CENA	0x3300
#घोषणा QM_CL_MR_CI_CENA	0x3340
#घोषणा QM_CL_CR		0x3800
#घोषणा QM_CL_RR0		0x3900
#घोषणा QM_CL_RR1		0x3940

#अन्यथा
/* Cache-inhibited रेजिस्टर offsets */
#घोषणा QM_REG_EQCR_PI_CINH	0x0000
#घोषणा QM_REG_EQCR_CI_CINH	0x0004
#घोषणा QM_REG_EQCR_ITR		0x0008
#घोषणा QM_REG_DQRR_PI_CINH	0x0040
#घोषणा QM_REG_DQRR_CI_CINH	0x0044
#घोषणा QM_REG_DQRR_ITR		0x0048
#घोषणा QM_REG_DQRR_DCAP	0x0050
#घोषणा QM_REG_DQRR_SDQCR	0x0054
#घोषणा QM_REG_DQRR_VDQCR	0x0058
#घोषणा QM_REG_DQRR_PDQCR	0x005c
#घोषणा QM_REG_MR_PI_CINH	0x0080
#घोषणा QM_REG_MR_CI_CINH	0x0084
#घोषणा QM_REG_MR_ITR		0x0088
#घोषणा QM_REG_CFG		0x0100
#घोषणा QM_REG_ISR		0x0e00
#घोषणा QM_REG_IER		0x0e04
#घोषणा QM_REG_ISDR		0x0e08
#घोषणा QM_REG_IIR		0x0e0c
#घोषणा QM_REG_ITPR		0x0e14

/* Cache-enabled रेजिस्टर offsets */
#घोषणा QM_CL_EQCR		0x0000
#घोषणा QM_CL_DQRR		0x1000
#घोषणा QM_CL_MR		0x2000
#घोषणा QM_CL_EQCR_PI_CENA	0x3000
#घोषणा QM_CL_EQCR_CI_CENA	0x3100
#घोषणा QM_CL_DQRR_PI_CENA	0x3200
#घोषणा QM_CL_DQRR_CI_CENA	0x3300
#घोषणा QM_CL_MR_PI_CENA	0x3400
#घोषणा QM_CL_MR_CI_CENA	0x3500
#घोषणा QM_CL_CR		0x3800
#घोषणा QM_CL_RR0		0x3900
#घोषणा QM_CL_RR1		0x3940
#पूर्ण_अगर

/*
 * BTW, the drivers (and h/w programming model) alपढ़ोy obtain the required
 * synchronisation क्रम portal accesses and data-dependencies. Use of barrier()s
 * or other order-preserving primitives simply degrade perक्रमmance. Hence the
 * use of the __raw_*() पूर्णांकerfaces, which simply ensure that the compiler treats
 * the portal रेजिस्टरs as अस्थिर
 */

/* Cache-enabled ring access */
#घोषणा qm_cl(base, idx)	((व्योम *)base + ((idx) << 6))

/*
 * Portal modes.
 *   Enum types;
 *     pmode == production mode
 *     cmode == consumption mode,
 *     dmode == h/w dequeue mode.
 *   Enum values use 3 letter codes. First letter matches the portal mode,
 *   reमुख्यing two letters indicate;
 *     ci == cache-inhibited portal रेजिस्टर
 *     ce == cache-enabled portal रेजिस्टर
 *     vb == in-band valid-bit (cache-enabled)
 *     dc == DCA (Discrete Consumption Acknowledgment), DQRR-only
 *   As क्रम "enum qm_dqrr_dmode", it should be self-explanatory.
 */
क्रमागत qm_eqcr_pmode अणु		/* matches QCSP_CFG::EPM */
	qm_eqcr_pci = 0,	/* PI index, cache-inhibited */
	qm_eqcr_pce = 1,	/* PI index, cache-enabled */
	qm_eqcr_pvb = 2		/* valid-bit */
पूर्ण;
क्रमागत qm_dqrr_dmode अणु		/* matches QCSP_CFG::DP */
	qm_dqrr_dpush = 0,	/* SDQCR  + VDQCR */
	qm_dqrr_dpull = 1	/* PDQCR */
पूर्ण;
क्रमागत qm_dqrr_pmode अणु		/* s/w-only */
	qm_dqrr_pci,		/* पढ़ोs DQRR_PI_CINH */
	qm_dqrr_pce,		/* पढ़ोs DQRR_PI_CENA */
	qm_dqrr_pvb		/* पढ़ोs valid-bit */
पूर्ण;
क्रमागत qm_dqrr_cmode अणु		/* matches QCSP_CFG::DCM */
	qm_dqrr_cci = 0,	/* CI index, cache-inhibited */
	qm_dqrr_cce = 1,	/* CI index, cache-enabled */
	qm_dqrr_cdc = 2		/* Discrete Consumption Acknowledgment */
पूर्ण;
क्रमागत qm_mr_pmode अणु		/* s/w-only */
	qm_mr_pci,		/* पढ़ोs MR_PI_CINH */
	qm_mr_pce,		/* पढ़ोs MR_PI_CENA */
	qm_mr_pvb		/* पढ़ोs valid-bit */
पूर्ण;
क्रमागत qm_mr_cmode अणु		/* matches QCSP_CFG::MM */
	qm_mr_cci = 0,		/* CI index, cache-inhibited */
	qm_mr_cce = 1		/* CI index, cache-enabled */
पूर्ण;

/* --- Portal काष्ठाures --- */

#घोषणा QM_EQCR_SIZE		8
#घोषणा QM_DQRR_SIZE		16
#घोषणा QM_MR_SIZE		8

/* "Enqueue Command" */
काष्ठा qm_eqcr_entry अणु
	u8 _ncw_verb; /* ग_लिखोs to this are non-coherent */
	u8 dca;
	__be16 seqnum;
	u8 __reserved[4];
	__be32 fqid;	/* 24-bit */
	__be32 tag;
	काष्ठा qm_fd fd;
	u8 __reserved3[32];
पूर्ण __packed __aligned(8);
#घोषणा QM_EQCR_VERB_VBIT		0x80
#घोषणा QM_EQCR_VERB_CMD_MASK		0x61	/* but only one value; */
#घोषणा QM_EQCR_VERB_CMD_ENQUEUE	0x01
#घोषणा QM_EQCR_SEQNUM_NESN		0x8000	/* Advance NESN */
#घोषणा QM_EQCR_SEQNUM_NLIS		0x4000	/* More fragments to come */
#घोषणा QM_EQCR_SEQNUM_SEQMASK		0x3fff	/* sequence number goes here */

काष्ठा qm_eqcr अणु
	काष्ठा qm_eqcr_entry *ring, *cursor;
	u8 ci, available, ithresh, vbit;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	u32 busy;
	क्रमागत qm_eqcr_pmode pmode;
#पूर्ण_अगर
पूर्ण;

काष्ठा qm_dqrr अणु
	स्थिर काष्ठा qm_dqrr_entry *ring, *cursor;
	u8 pi, ci, fill, ithresh, vbit;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	क्रमागत qm_dqrr_dmode dmode;
	क्रमागत qm_dqrr_pmode pmode;
	क्रमागत qm_dqrr_cmode cmode;
#पूर्ण_अगर
पूर्ण;

काष्ठा qm_mr अणु
	जोड़ qm_mr_entry *ring, *cursor;
	u8 pi, ci, fill, ithresh, vbit;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	क्रमागत qm_mr_pmode pmode;
	क्रमागत qm_mr_cmode cmode;
#पूर्ण_अगर
पूर्ण;

/* MC (Management Command) command */
/* "FQ" command layout */
काष्ठा qm_mcc_fq अणु
	u8 _ncw_verb;
	u8 __reserved1[3];
	__be32 fqid;	/* 24-bit */
	u8 __reserved2[56];
पूर्ण __packed;

/* "CGR" command layout */
काष्ठा qm_mcc_cgr अणु
	u8 _ncw_verb;
	u8 __reserved1[30];
	u8 cgid;
	u8 __reserved2[32];
पूर्ण;

#घोषणा QM_MCC_VERB_VBIT		0x80
#घोषणा QM_MCC_VERB_MASK		0x7f	/* where the verb contains; */
#घोषणा QM_MCC_VERB_INITFQ_PARKED	0x40
#घोषणा QM_MCC_VERB_INITFQ_SCHED	0x41
#घोषणा QM_MCC_VERB_QUERYFQ		0x44
#घोषणा QM_MCC_VERB_QUERYFQ_NP		0x45	/* "non-programmable" fields */
#घोषणा QM_MCC_VERB_QUERYWQ		0x46
#घोषणा QM_MCC_VERB_QUERYWQ_DEDICATED	0x47
#घोषणा QM_MCC_VERB_ALTER_SCHED		0x48	/* Schedule FQ */
#घोषणा QM_MCC_VERB_ALTER_FE		0x49	/* Force Eligible FQ */
#घोषणा QM_MCC_VERB_ALTER_RETIRE	0x4a	/* Retire FQ */
#घोषणा QM_MCC_VERB_ALTER_OOS		0x4b	/* Take FQ out of service */
#घोषणा QM_MCC_VERB_ALTER_FQXON		0x4d	/* FQ XON */
#घोषणा QM_MCC_VERB_ALTER_FQXOFF	0x4e	/* FQ XOFF */
#घोषणा QM_MCC_VERB_INITCGR		0x50
#घोषणा QM_MCC_VERB_MODIFYCGR		0x51
#घोषणा QM_MCC_VERB_CGRTESTWRITE	0x52
#घोषणा QM_MCC_VERB_QUERYCGR		0x58
#घोषणा QM_MCC_VERB_QUERYCONGESTION	0x59
जोड़ qm_mc_command अणु
	काष्ठा अणु
		u8 _ncw_verb; /* ग_लिखोs to this are non-coherent */
		u8 __reserved[63];
	पूर्ण;
	काष्ठा qm_mcc_initfq initfq;
	काष्ठा qm_mcc_initcgr initcgr;
	काष्ठा qm_mcc_fq fq;
	काष्ठा qm_mcc_cgr cgr;
पूर्ण;

/* MC (Management Command) result */
/* "Query FQ" */
काष्ठा qm_mcr_queryfq अणु
	u8 verb;
	u8 result;
	u8 __reserved1[8];
	काष्ठा qm_fqd fqd;	/* the FQD fields are here */
	u8 __reserved2[30];
पूर्ण __packed;

/* "Alter FQ State Commands" */
काष्ठा qm_mcr_alterfq अणु
	u8 verb;
	u8 result;
	u8 fqs;		/* Frame Queue Status */
	u8 __reserved1[61];
पूर्ण;
#घोषणा QM_MCR_VERB_RRID		0x80
#घोषणा QM_MCR_VERB_MASK		QM_MCC_VERB_MASK
#घोषणा QM_MCR_VERB_INITFQ_PARKED	QM_MCC_VERB_INITFQ_PARKED
#घोषणा QM_MCR_VERB_INITFQ_SCHED	QM_MCC_VERB_INITFQ_SCHED
#घोषणा QM_MCR_VERB_QUERYFQ		QM_MCC_VERB_QUERYFQ
#घोषणा QM_MCR_VERB_QUERYFQ_NP		QM_MCC_VERB_QUERYFQ_NP
#घोषणा QM_MCR_VERB_QUERYWQ		QM_MCC_VERB_QUERYWQ
#घोषणा QM_MCR_VERB_QUERYWQ_DEDICATED	QM_MCC_VERB_QUERYWQ_DEDICATED
#घोषणा QM_MCR_VERB_ALTER_SCHED		QM_MCC_VERB_ALTER_SCHED
#घोषणा QM_MCR_VERB_ALTER_FE		QM_MCC_VERB_ALTER_FE
#घोषणा QM_MCR_VERB_ALTER_RETIRE	QM_MCC_VERB_ALTER_RETIRE
#घोषणा QM_MCR_VERB_ALTER_OOS		QM_MCC_VERB_ALTER_OOS
#घोषणा QM_MCR_RESULT_शून्य		0x00
#घोषणा QM_MCR_RESULT_OK		0xf0
#घोषणा QM_MCR_RESULT_ERR_FQID		0xf1
#घोषणा QM_MCR_RESULT_ERR_FQSTATE	0xf2
#घोषणा QM_MCR_RESULT_ERR_NOTEMPTY	0xf3	/* OOS fails अगर FQ is !empty */
#घोषणा QM_MCR_RESULT_ERR_BADCHANNEL	0xf4
#घोषणा QM_MCR_RESULT_PENDING		0xf8
#घोषणा QM_MCR_RESULT_ERR_BADCOMMAND	0xff
#घोषणा QM_MCR_FQS_ORLPRESENT		0x02	/* ORL fragments to come */
#घोषणा QM_MCR_FQS_NOTEMPTY		0x01	/* FQ has enqueued frames */
#घोषणा QM_MCR_TIMEOUT			10000	/* us */
जोड़ qm_mc_result अणु
	काष्ठा अणु
		u8 verb;
		u8 result;
		u8 __reserved1[62];
	पूर्ण;
	काष्ठा qm_mcr_queryfq queryfq;
	काष्ठा qm_mcr_alterfq alterfq;
	काष्ठा qm_mcr_querycgr querycgr;
	काष्ठा qm_mcr_querycongestion querycongestion;
	काष्ठा qm_mcr_querywq querywq;
	काष्ठा qm_mcr_queryfq_np queryfq_np;
पूर्ण;

काष्ठा qm_mc अणु
	जोड़ qm_mc_command *cr;
	जोड़ qm_mc_result *rr;
	u8 rridx, vbit;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	क्रमागत अणु
		/* Can be _mc_start()ed */
		qman_mc_idle,
		/* Can be _mc_commit()ed or _mc_पात()ed */
		qman_mc_user,
		/* Can only be _mc_retry()ed */
		qman_mc_hw
	पूर्ण state;
#पूर्ण_अगर
पूर्ण;

काष्ठा qm_addr अणु
	व्योम *ce;		/* cache-enabled */
	__be32 *ce_be;		/* same value as above but क्रम direct access */
	व्योम __iomem *ci;	/* cache-inhibited */
पूर्ण;

काष्ठा qm_portal अणु
	/*
	 * In the non-CONFIG_FSL_DPAA_CHECKING हाल, the following stuff up to
	 * and including 'mc' fits within a cacheline (yay!). The 'config' part
	 * is setup-only, so isn't a cause for a concern. In other words, don't
	 * rearrange this काष्ठाure on a whim, there be dragons ...
	 */
	काष्ठा qm_addr addr;
	काष्ठा qm_eqcr eqcr;
	काष्ठा qm_dqrr dqrr;
	काष्ठा qm_mr mr;
	काष्ठा qm_mc mc;
पूर्ण ____cacheline_aligned;

/* Cache-inhibited रेजिस्टर access. */
अटल अंतरभूत u32 qm_in(काष्ठा qm_portal *p, u32 offset)
अणु
	वापस ioपढ़ो32be(p->addr.ci + offset);
पूर्ण

अटल अंतरभूत व्योम qm_out(काष्ठा qm_portal *p, u32 offset, u32 val)
अणु
	ioग_लिखो32be(val, p->addr.ci + offset);
पूर्ण

/* Cache Enabled Portal Access */
अटल अंतरभूत व्योम qm_cl_invalidate(काष्ठा qm_portal *p, u32 offset)
अणु
	dpaa_invalidate(p->addr.ce + offset);
पूर्ण

अटल अंतरभूत व्योम qm_cl_touch_ro(काष्ठा qm_portal *p, u32 offset)
अणु
	dpaa_touch_ro(p->addr.ce + offset);
पूर्ण

अटल अंतरभूत u32 qm_ce_in(काष्ठा qm_portal *p, u32 offset)
अणु
	वापस be32_to_cpu(*(p->addr.ce_be + (offset/4)));
पूर्ण

/* --- EQCR API --- */

#घोषणा EQCR_SHIFT	ilog2(माप(काष्ठा qm_eqcr_entry))
#घोषणा EQCR_CARRY	(uपूर्णांकptr_t)(QM_EQCR_SIZE << EQCR_SHIFT)

/* Bit-wise logic to wrap a ring poपूर्णांकer by clearing the "carry bit" */
अटल काष्ठा qm_eqcr_entry *eqcr_carryclear(काष्ठा qm_eqcr_entry *p)
अणु
	uपूर्णांकptr_t addr = (uपूर्णांकptr_t)p;

	addr &= ~EQCR_CARRY;

	वापस (काष्ठा qm_eqcr_entry *)addr;
पूर्ण

/* Bit-wise logic to convert a ring poपूर्णांकer to a ring index */
अटल पूर्णांक eqcr_ptr2idx(काष्ठा qm_eqcr_entry *e)
अणु
	वापस ((uपूर्णांकptr_t)e >> EQCR_SHIFT) & (QM_EQCR_SIZE - 1);
पूर्ण

/* Increment the 'cursor' ring pointer, taking 'vbit' पूर्णांकo account */
अटल अंतरभूत व्योम eqcr_inc(काष्ठा qm_eqcr *eqcr)
अणु
	/* increment to the next EQCR poपूर्णांकer and handle overflow and 'vbit' */
	काष्ठा qm_eqcr_entry *partial = eqcr->cursor + 1;

	eqcr->cursor = eqcr_carryclear(partial);
	अगर (partial != eqcr->cursor)
		eqcr->vbit ^= QM_EQCR_VERB_VBIT;
पूर्ण

अटल अंतरभूत पूर्णांक qm_eqcr_init(काष्ठा qm_portal *portal,
				क्रमागत qm_eqcr_pmode pmode,
				अचिन्हित पूर्णांक eq_stash_thresh,
				पूर्णांक eq_stash_prio)
अणु
	काष्ठा qm_eqcr *eqcr = &portal->eqcr;
	u32 cfg;
	u8 pi;

	eqcr->ring = portal->addr.ce + QM_CL_EQCR;
	eqcr->ci = qm_in(portal, QM_REG_EQCR_CI_CINH) & (QM_EQCR_SIZE - 1);
	qm_cl_invalidate(portal, QM_CL_EQCR_CI_CENA);
	pi = qm_in(portal, QM_REG_EQCR_PI_CINH) & (QM_EQCR_SIZE - 1);
	eqcr->cursor = eqcr->ring + pi;
	eqcr->vbit = (qm_in(portal, QM_REG_EQCR_PI_CINH) & QM_EQCR_SIZE) ?
		     QM_EQCR_VERB_VBIT : 0;
	eqcr->available = QM_EQCR_SIZE - 1 -
			  dpaa_cyc_dअगरf(QM_EQCR_SIZE, eqcr->ci, pi);
	eqcr->ithresh = qm_in(portal, QM_REG_EQCR_ITR);
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	eqcr->busy = 0;
	eqcr->pmode = pmode;
#पूर्ण_अगर
	cfg = (qm_in(portal, QM_REG_CFG) & 0x00ffffff) |
	      (eq_stash_thresh << 28) | /* QCSP_CFG: EST */
	      (eq_stash_prio << 26) | /* QCSP_CFG: EP */
	      ((pmode & 0x3) << 24); /* QCSP_CFG::EPM */
	qm_out(portal, QM_REG_CFG, cfg);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qm_eqcr_finish(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_eqcr *eqcr = &portal->eqcr;
	u8 pi = qm_in(portal, QM_REG_EQCR_PI_CINH) & (QM_EQCR_SIZE - 1);
	u8 ci = qm_in(portal, QM_REG_EQCR_CI_CINH) & (QM_EQCR_SIZE - 1);

	DPAA_ASSERT(!eqcr->busy);
	अगर (pi != eqcr_ptr2idx(eqcr->cursor))
		pr_crit("losing uncommitted EQCR entries\n");
	अगर (ci != eqcr->ci)
		pr_crit("missing existing EQCR completions\n");
	अगर (eqcr->ci != eqcr_ptr2idx(eqcr->cursor))
		pr_crit("EQCR destroyed unquiesced\n");
पूर्ण

अटल अंतरभूत काष्ठा qm_eqcr_entry *qm_eqcr_start_no_stash(काष्ठा qm_portal
								 *portal)
अणु
	काष्ठा qm_eqcr *eqcr = &portal->eqcr;

	DPAA_ASSERT(!eqcr->busy);
	अगर (!eqcr->available)
		वापस शून्य;

#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	eqcr->busy = 1;
#पूर्ण_अगर
	dpaa_zero(eqcr->cursor);
	वापस eqcr->cursor;
पूर्ण

अटल अंतरभूत काष्ठा qm_eqcr_entry *qm_eqcr_start_stash(काष्ठा qm_portal
								*portal)
अणु
	काष्ठा qm_eqcr *eqcr = &portal->eqcr;
	u8 dअगरf, old_ci;

	DPAA_ASSERT(!eqcr->busy);
	अगर (!eqcr->available) अणु
		old_ci = eqcr->ci;
		eqcr->ci = qm_ce_in(portal, QM_CL_EQCR_CI_CENA) &
			   (QM_EQCR_SIZE - 1);
		dअगरf = dpaa_cyc_dअगरf(QM_EQCR_SIZE, old_ci, eqcr->ci);
		eqcr->available += dअगरf;
		अगर (!dअगरf)
			वापस शून्य;
	पूर्ण
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	eqcr->busy = 1;
#पूर्ण_अगर
	dpaa_zero(eqcr->cursor);
	वापस eqcr->cursor;
पूर्ण

अटल अंतरभूत व्योम eqcr_commit_checks(काष्ठा qm_eqcr *eqcr)
अणु
	DPAA_ASSERT(eqcr->busy);
	DPAA_ASSERT(!(be32_to_cpu(eqcr->cursor->fqid) & ~QM_FQID_MASK));
	DPAA_ASSERT(eqcr->available >= 1);
पूर्ण

अटल अंतरभूत व्योम qm_eqcr_pvb_commit(काष्ठा qm_portal *portal, u8 myverb)
अणु
	काष्ठा qm_eqcr *eqcr = &portal->eqcr;
	काष्ठा qm_eqcr_entry *eqcursor;

	eqcr_commit_checks(eqcr);
	DPAA_ASSERT(eqcr->pmode == qm_eqcr_pvb);
	dma_wmb();
	eqcursor = eqcr->cursor;
	eqcursor->_ncw_verb = myverb | eqcr->vbit;
	dpaa_flush(eqcursor);
	eqcr_inc(eqcr);
	eqcr->available--;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	eqcr->busy = 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम qm_eqcr_cce_prefetch(काष्ठा qm_portal *portal)
अणु
	qm_cl_touch_ro(portal, QM_CL_EQCR_CI_CENA);
पूर्ण

अटल अंतरभूत u8 qm_eqcr_cce_update(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_eqcr *eqcr = &portal->eqcr;
	u8 dअगरf, old_ci = eqcr->ci;

	eqcr->ci = qm_ce_in(portal, QM_CL_EQCR_CI_CENA) & (QM_EQCR_SIZE - 1);
	qm_cl_invalidate(portal, QM_CL_EQCR_CI_CENA);
	dअगरf = dpaa_cyc_dअगरf(QM_EQCR_SIZE, old_ci, eqcr->ci);
	eqcr->available += dअगरf;
	वापस dअगरf;
पूर्ण

अटल अंतरभूत व्योम qm_eqcr_set_ithresh(काष्ठा qm_portal *portal, u8 ithresh)
अणु
	काष्ठा qm_eqcr *eqcr = &portal->eqcr;

	eqcr->ithresh = ithresh;
	qm_out(portal, QM_REG_EQCR_ITR, ithresh);
पूर्ण

अटल अंतरभूत u8 qm_eqcr_get_avail(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_eqcr *eqcr = &portal->eqcr;

	वापस eqcr->available;
पूर्ण

अटल अंतरभूत u8 qm_eqcr_get_fill(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_eqcr *eqcr = &portal->eqcr;

	वापस QM_EQCR_SIZE - 1 - eqcr->available;
पूर्ण

/* --- DQRR API --- */

#घोषणा DQRR_SHIFT	ilog2(माप(काष्ठा qm_dqrr_entry))
#घोषणा DQRR_CARRY	(uपूर्णांकptr_t)(QM_DQRR_SIZE << DQRR_SHIFT)

अटल स्थिर काष्ठा qm_dqrr_entry *dqrr_carryclear(
					स्थिर काष्ठा qm_dqrr_entry *p)
अणु
	uपूर्णांकptr_t addr = (uपूर्णांकptr_t)p;

	addr &= ~DQRR_CARRY;

	वापस (स्थिर काष्ठा qm_dqrr_entry *)addr;
पूर्ण

अटल अंतरभूत पूर्णांक dqrr_ptr2idx(स्थिर काष्ठा qm_dqrr_entry *e)
अणु
	वापस ((uपूर्णांकptr_t)e >> DQRR_SHIFT) & (QM_DQRR_SIZE - 1);
पूर्ण

अटल स्थिर काष्ठा qm_dqrr_entry *dqrr_inc(स्थिर काष्ठा qm_dqrr_entry *e)
अणु
	वापस dqrr_carryclear(e + 1);
पूर्ण

अटल अंतरभूत व्योम qm_dqrr_set_maxfill(काष्ठा qm_portal *portal, u8 mf)
अणु
	qm_out(portal, QM_REG_CFG, (qm_in(portal, QM_REG_CFG) & 0xff0fffff) |
				   ((mf & (QM_DQRR_SIZE - 1)) << 20));
पूर्ण

अटल अंतरभूत पूर्णांक qm_dqrr_init(काष्ठा qm_portal *portal,
			       स्थिर काष्ठा qm_portal_config *config,
			       क्रमागत qm_dqrr_dmode dmode,
			       क्रमागत qm_dqrr_pmode pmode,
			       क्रमागत qm_dqrr_cmode cmode, u8 max_fill)
अणु
	काष्ठा qm_dqrr *dqrr = &portal->dqrr;
	u32 cfg;

	/* Make sure the DQRR will be idle when we enable */
	qm_out(portal, QM_REG_DQRR_SDQCR, 0);
	qm_out(portal, QM_REG_DQRR_VDQCR, 0);
	qm_out(portal, QM_REG_DQRR_PDQCR, 0);
	dqrr->ring = portal->addr.ce + QM_CL_DQRR;
	dqrr->pi = qm_in(portal, QM_REG_DQRR_PI_CINH) & (QM_DQRR_SIZE - 1);
	dqrr->ci = qm_in(portal, QM_REG_DQRR_CI_CINH) & (QM_DQRR_SIZE - 1);
	dqrr->cursor = dqrr->ring + dqrr->ci;
	dqrr->fill = dpaa_cyc_dअगरf(QM_DQRR_SIZE, dqrr->ci, dqrr->pi);
	dqrr->vbit = (qm_in(portal, QM_REG_DQRR_PI_CINH) & QM_DQRR_SIZE) ?
			QM_DQRR_VERB_VBIT : 0;
	dqrr->ithresh = qm_in(portal, QM_REG_DQRR_ITR);
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	dqrr->dmode = dmode;
	dqrr->pmode = pmode;
	dqrr->cmode = cmode;
#पूर्ण_अगर
	/* Invalidate every ring entry beक्रमe beginning */
	क्रम (cfg = 0; cfg < QM_DQRR_SIZE; cfg++)
		dpaa_invalidate(qm_cl(dqrr->ring, cfg));
	cfg = (qm_in(portal, QM_REG_CFG) & 0xff000f00) |
		((max_fill & (QM_DQRR_SIZE - 1)) << 20) | /* DQRR_MF */
		((dmode & 1) << 18) |			/* DP */
		((cmode & 3) << 16) |			/* DCM */
		0xa0 |					/* RE+SE */
		(0 ? 0x40 : 0) |			/* Ignore RP */
		(0 ? 0x10 : 0);				/* Ignore SP */
	qm_out(portal, QM_REG_CFG, cfg);
	qm_dqrr_set_maxfill(portal, max_fill);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qm_dqrr_finish(काष्ठा qm_portal *portal)
अणु
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	काष्ठा qm_dqrr *dqrr = &portal->dqrr;

	अगर (dqrr->cmode != qm_dqrr_cdc &&
	    dqrr->ci != dqrr_ptr2idx(dqrr->cursor))
		pr_crit("Ignoring completed DQRR entries\n");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत स्थिर काष्ठा qm_dqrr_entry *qm_dqrr_current(
						काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_dqrr *dqrr = &portal->dqrr;

	अगर (!dqrr->fill)
		वापस शून्य;
	वापस dqrr->cursor;
पूर्ण

अटल अंतरभूत u8 qm_dqrr_next(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_dqrr *dqrr = &portal->dqrr;

	DPAA_ASSERT(dqrr->fill);
	dqrr->cursor = dqrr_inc(dqrr->cursor);
	वापस --dqrr->fill;
पूर्ण

अटल अंतरभूत व्योम qm_dqrr_pvb_update(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_dqrr *dqrr = &portal->dqrr;
	काष्ठा qm_dqrr_entry *res = qm_cl(dqrr->ring, dqrr->pi);

	DPAA_ASSERT(dqrr->pmode == qm_dqrr_pvb);
#अगर_अघोषित CONFIG_FSL_PAMU
	/*
	 * If PAMU is not available we need to invalidate the cache.
	 * When PAMU is available the cache is updated by stash
	 */
	dpaa_invalidate_touch_ro(res);
#पूर्ण_अगर
	अगर ((res->verb & QM_DQRR_VERB_VBIT) == dqrr->vbit) अणु
		dqrr->pi = (dqrr->pi + 1) & (QM_DQRR_SIZE - 1);
		अगर (!dqrr->pi)
			dqrr->vbit ^= QM_DQRR_VERB_VBIT;
		dqrr->fill++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम qm_dqrr_cdc_consume_1ptr(काष्ठा qm_portal *portal,
					स्थिर काष्ठा qm_dqrr_entry *dq,
					पूर्णांक park)
अणु
	__maybe_unused काष्ठा qm_dqrr *dqrr = &portal->dqrr;
	पूर्णांक idx = dqrr_ptr2idx(dq);

	DPAA_ASSERT(dqrr->cmode == qm_dqrr_cdc);
	DPAA_ASSERT((dqrr->ring + idx) == dq);
	DPAA_ASSERT(idx < QM_DQRR_SIZE);
	qm_out(portal, QM_REG_DQRR_DCAP, (0 << 8) | /* DQRR_DCAP::S */
	       ((park ? 1 : 0) << 6) |		    /* DQRR_DCAP::PK */
	       idx);				    /* DQRR_DCAP::DCAP_CI */
पूर्ण

अटल अंतरभूत व्योम qm_dqrr_cdc_consume_n(काष्ठा qm_portal *portal, u32 biपंचांगask)
अणु
	__maybe_unused काष्ठा qm_dqrr *dqrr = &portal->dqrr;

	DPAA_ASSERT(dqrr->cmode == qm_dqrr_cdc);
	qm_out(portal, QM_REG_DQRR_DCAP, (1 << 8) | /* DQRR_DCAP::S */
	       (biपंचांगask << 16));		    /* DQRR_DCAP::DCAP_CI */
पूर्ण

अटल अंतरभूत व्योम qm_dqrr_sdqcr_set(काष्ठा qm_portal *portal, u32 sdqcr)
अणु
	qm_out(portal, QM_REG_DQRR_SDQCR, sdqcr);
पूर्ण

अटल अंतरभूत व्योम qm_dqrr_vdqcr_set(काष्ठा qm_portal *portal, u32 vdqcr)
अणु
	qm_out(portal, QM_REG_DQRR_VDQCR, vdqcr);
पूर्ण

अटल अंतरभूत पूर्णांक qm_dqrr_set_ithresh(काष्ठा qm_portal *portal, u8 ithresh)
अणु

	अगर (ithresh > QMAN_DQRR_IT_MAX)
		वापस -EINVAL;

	qm_out(portal, QM_REG_DQRR_ITR, ithresh);

	वापस 0;
पूर्ण

/* --- MR API --- */

#घोषणा MR_SHIFT	ilog2(माप(जोड़ qm_mr_entry))
#घोषणा MR_CARRY	(uपूर्णांकptr_t)(QM_MR_SIZE << MR_SHIFT)

अटल जोड़ qm_mr_entry *mr_carryclear(जोड़ qm_mr_entry *p)
अणु
	uपूर्णांकptr_t addr = (uपूर्णांकptr_t)p;

	addr &= ~MR_CARRY;

	वापस (जोड़ qm_mr_entry *)addr;
पूर्ण

अटल अंतरभूत पूर्णांक mr_ptr2idx(स्थिर जोड़ qm_mr_entry *e)
अणु
	वापस ((uपूर्णांकptr_t)e >> MR_SHIFT) & (QM_MR_SIZE - 1);
पूर्ण

अटल अंतरभूत जोड़ qm_mr_entry *mr_inc(जोड़ qm_mr_entry *e)
अणु
	वापस mr_carryclear(e + 1);
पूर्ण

अटल अंतरभूत पूर्णांक qm_mr_init(काष्ठा qm_portal *portal, क्रमागत qm_mr_pmode pmode,
			     क्रमागत qm_mr_cmode cmode)
अणु
	काष्ठा qm_mr *mr = &portal->mr;
	u32 cfg;

	mr->ring = portal->addr.ce + QM_CL_MR;
	mr->pi = qm_in(portal, QM_REG_MR_PI_CINH) & (QM_MR_SIZE - 1);
	mr->ci = qm_in(portal, QM_REG_MR_CI_CINH) & (QM_MR_SIZE - 1);
	mr->cursor = mr->ring + mr->ci;
	mr->fill = dpaa_cyc_dअगरf(QM_MR_SIZE, mr->ci, mr->pi);
	mr->vbit = (qm_in(portal, QM_REG_MR_PI_CINH) & QM_MR_SIZE)
		? QM_MR_VERB_VBIT : 0;
	mr->ithresh = qm_in(portal, QM_REG_MR_ITR);
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	mr->pmode = pmode;
	mr->cmode = cmode;
#पूर्ण_अगर
	cfg = (qm_in(portal, QM_REG_CFG) & 0xfffff0ff) |
	      ((cmode & 1) << 8);	/* QCSP_CFG:MM */
	qm_out(portal, QM_REG_CFG, cfg);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qm_mr_finish(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_mr *mr = &portal->mr;

	अगर (mr->ci != mr_ptr2idx(mr->cursor))
		pr_crit("Ignoring completed MR entries\n");
पूर्ण

अटल अंतरभूत स्थिर जोड़ qm_mr_entry *qm_mr_current(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_mr *mr = &portal->mr;

	अगर (!mr->fill)
		वापस शून्य;
	वापस mr->cursor;
पूर्ण

अटल अंतरभूत पूर्णांक qm_mr_next(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_mr *mr = &portal->mr;

	DPAA_ASSERT(mr->fill);
	mr->cursor = mr_inc(mr->cursor);
	वापस --mr->fill;
पूर्ण

अटल अंतरभूत व्योम qm_mr_pvb_update(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_mr *mr = &portal->mr;
	जोड़ qm_mr_entry *res = qm_cl(mr->ring, mr->pi);

	DPAA_ASSERT(mr->pmode == qm_mr_pvb);

	अगर ((res->verb & QM_MR_VERB_VBIT) == mr->vbit) अणु
		mr->pi = (mr->pi + 1) & (QM_MR_SIZE - 1);
		अगर (!mr->pi)
			mr->vbit ^= QM_MR_VERB_VBIT;
		mr->fill++;
		res = mr_inc(res);
	पूर्ण
	dpaa_invalidate_touch_ro(res);
पूर्ण

अटल अंतरभूत व्योम qm_mr_cci_consume(काष्ठा qm_portal *portal, u8 num)
अणु
	काष्ठा qm_mr *mr = &portal->mr;

	DPAA_ASSERT(mr->cmode == qm_mr_cci);
	mr->ci = (mr->ci + num) & (QM_MR_SIZE - 1);
	qm_out(portal, QM_REG_MR_CI_CINH, mr->ci);
पूर्ण

अटल अंतरभूत व्योम qm_mr_cci_consume_to_current(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_mr *mr = &portal->mr;

	DPAA_ASSERT(mr->cmode == qm_mr_cci);
	mr->ci = mr_ptr2idx(mr->cursor);
	qm_out(portal, QM_REG_MR_CI_CINH, mr->ci);
पूर्ण

अटल अंतरभूत व्योम qm_mr_set_ithresh(काष्ठा qm_portal *portal, u8 ithresh)
अणु
	qm_out(portal, QM_REG_MR_ITR, ithresh);
पूर्ण

/* --- Management command API --- */

अटल अंतरभूत पूर्णांक qm_mc_init(काष्ठा qm_portal *portal)
अणु
	u8 rr0, rr1;
	काष्ठा qm_mc *mc = &portal->mc;

	mc->cr = portal->addr.ce + QM_CL_CR;
	mc->rr = portal->addr.ce + QM_CL_RR0;
	/*
	 * The expected valid bit polarity क्रम the next CR command is 0
	 * अगर RR1 contains a valid response, and is 1 अगर RR0 contains a
	 * valid response. If both RR contain all 0, this indicates either
	 * that no command has been executed since reset (in which हाल the
	 * expected valid bit polarity is 1)
	 */
	rr0 = mc->rr->verb;
	rr1 = (mc->rr+1)->verb;
	अगर ((rr0 == 0 && rr1 == 0) || rr0 != 0)
		mc->rridx = 1;
	अन्यथा
		mc->rridx = 0;
	mc->vbit = mc->rridx ? QM_MCC_VERB_VBIT : 0;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	mc->state = qman_mc_idle;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qm_mc_finish(काष्ठा qm_portal *portal)
अणु
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	काष्ठा qm_mc *mc = &portal->mc;

	DPAA_ASSERT(mc->state == qman_mc_idle);
	अगर (mc->state != qman_mc_idle)
		pr_crit("Losing incomplete MC command\n");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत जोड़ qm_mc_command *qm_mc_start(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_mc *mc = &portal->mc;

	DPAA_ASSERT(mc->state == qman_mc_idle);
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	mc->state = qman_mc_user;
#पूर्ण_अगर
	dpaa_zero(mc->cr);
	वापस mc->cr;
पूर्ण

अटल अंतरभूत व्योम qm_mc_commit(काष्ठा qm_portal *portal, u8 myverb)
अणु
	काष्ठा qm_mc *mc = &portal->mc;
	जोड़ qm_mc_result *rr = mc->rr + mc->rridx;

	DPAA_ASSERT(mc->state == qman_mc_user);
	dma_wmb();
	mc->cr->_ncw_verb = myverb | mc->vbit;
	dpaa_flush(mc->cr);
	dpaa_invalidate_touch_ro(rr);
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	mc->state = qman_mc_hw;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत जोड़ qm_mc_result *qm_mc_result(काष्ठा qm_portal *portal)
अणु
	काष्ठा qm_mc *mc = &portal->mc;
	जोड़ qm_mc_result *rr = mc->rr + mc->rridx;

	DPAA_ASSERT(mc->state == qman_mc_hw);
	/*
	 *  The inactive response रेजिस्टर's verb byte always वापसs zero until
	 * its command is submitted and completed. This includes the valid-bit,
	 * in हाल you were wondering...
	 */
	अगर (!rr->verb) अणु
		dpaa_invalidate_touch_ro(rr);
		वापस शून्य;
	पूर्ण
	mc->rridx ^= 1;
	mc->vbit ^= QM_MCC_VERB_VBIT;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	mc->state = qman_mc_idle;
#पूर्ण_अगर
	वापस rr;
पूर्ण

अटल अंतरभूत पूर्णांक qm_mc_result_समयout(काष्ठा qm_portal *portal,
				       जोड़ qm_mc_result **mcr)
अणु
	पूर्णांक समयout = QM_MCR_TIMEOUT;

	करो अणु
		*mcr = qm_mc_result(portal);
		अगर (*mcr)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (--समयout);

	वापस समयout;
पूर्ण

अटल अंतरभूत व्योम fq_set(काष्ठा qman_fq *fq, u32 mask)
अणु
	fq->flags |= mask;
पूर्ण

अटल अंतरभूत व्योम fq_clear(काष्ठा qman_fq *fq, u32 mask)
अणु
	fq->flags &= ~mask;
पूर्ण

अटल अंतरभूत पूर्णांक fq_isset(काष्ठा qman_fq *fq, u32 mask)
अणु
	वापस fq->flags & mask;
पूर्ण

अटल अंतरभूत पूर्णांक fq_isclear(काष्ठा qman_fq *fq, u32 mask)
अणु
	वापस !(fq->flags & mask);
पूर्ण

काष्ठा qman_portal अणु
	काष्ठा qm_portal p;
	/* PORTAL_BITS_*** - dynamic, strictly पूर्णांकernal */
	अचिन्हित दीर्घ bits;
	/* पूर्णांकerrupt sources processed by portal_isr(), configurable */
	अचिन्हित दीर्घ irq_sources;
	u32 use_eqcr_ci_stashing;
	/* only 1 अस्थिर dequeue at a समय */
	काष्ठा qman_fq *vdqcr_owned;
	u32 sdqcr;
	/* probing समय config params क्रम cpu-affine portals */
	स्थिर काष्ठा qm_portal_config *config;
	/* 2-element array. cgrs[0] is mask, cgrs[1] is snapshot. */
	काष्ठा qman_cgrs *cgrs;
	/* linked-list of CSCN handlers. */
	काष्ठा list_head cgr_cbs;
	/* list lock */
	spinlock_t cgr_lock;
	काष्ठा work_काष्ठा congestion_work;
	काष्ठा work_काष्ठा mr_work;
	अक्षर irqname[MAX_IRQNAME];
पूर्ण;

अटल cpumask_t affine_mask;
अटल DEFINE_SPINLOCK(affine_mask_lock);
अटल u16 affine_channels[NR_CPUS];
अटल DEFINE_PER_CPU(काष्ठा qman_portal, qman_affine_portal);
काष्ठा qman_portal *affine_portals[NR_CPUS];

अटल अंतरभूत काष्ठा qman_portal *get_affine_portal(व्योम)
अणु
	वापस &get_cpu_var(qman_affine_portal);
पूर्ण

अटल अंतरभूत व्योम put_affine_portal(व्योम)
अणु
	put_cpu_var(qman_affine_portal);
पूर्ण


अटल अंतरभूत काष्ठा qman_portal *get_portal_क्रम_channel(u16 channel)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_possible_cpus(); i++) अणु
		अगर (affine_portals[i] &&
		    affine_portals[i]->config->channel == channel)
			वापस affine_portals[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा workqueue_काष्ठा *qm_portal_wq;

पूर्णांक qman_dqrr_set_ithresh(काष्ठा qman_portal *portal, u8 ithresh)
अणु
	पूर्णांक res;

	अगर (!portal)
		वापस -EINVAL;

	res = qm_dqrr_set_ithresh(&portal->p, ithresh);
	अगर (res)
		वापस res;

	portal->p.dqrr.ithresh = ithresh;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qman_dqrr_set_ithresh);

व्योम qman_dqrr_get_ithresh(काष्ठा qman_portal *portal, u8 *ithresh)
अणु
	अगर (portal && ithresh)
		*ithresh = qm_in(&portal->p, QM_REG_DQRR_ITR);
पूर्ण
EXPORT_SYMBOL(qman_dqrr_get_ithresh);

व्योम qman_portal_get_iperiod(काष्ठा qman_portal *portal, u32 *iperiod)
अणु
	अगर (portal && iperiod)
		*iperiod = qm_in(&portal->p, QM_REG_ITPR);
पूर्ण
EXPORT_SYMBOL(qman_portal_get_iperiod);

पूर्णांक qman_portal_set_iperiod(काष्ठा qman_portal *portal, u32 iperiod)
अणु
	अगर (!portal || iperiod > QMAN_ITP_MAX)
		वापस -EINVAL;

	qm_out(&portal->p, QM_REG_ITPR, iperiod);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qman_portal_set_iperiod);

पूर्णांक qman_wq_alloc(व्योम)
अणु
	qm_portal_wq = alloc_workqueue("qman_portal_wq", 0, 1);
	अगर (!qm_portal_wq)
		वापस -ENOMEM;
	वापस 0;
पूर्ण


व्योम qman_enable_irqs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_possible_cpus(); i++) अणु
		अगर (affine_portals[i]) अणु
			qm_out(&affine_portals[i]->p, QM_REG_ISR, 0xffffffff);
			qm_out(&affine_portals[i]->p, QM_REG_IIR, 0);
		पूर्ण

	पूर्ण
पूर्ण

/*
 * This is what everything can रुको on, even अगर it migrates to a dअगरferent cpu
 * to the one whose affine portal it is रुकोing on.
 */
अटल DECLARE_WAIT_QUEUE_HEAD(affine_queue);

अटल काष्ठा qman_fq **fq_table;
अटल u32 num_fqids;

पूर्णांक qman_alloc_fq_table(u32 _num_fqids)
अणु
	num_fqids = _num_fqids;

	fq_table = vzalloc(array3_size(माप(काष्ठा qman_fq *),
				       num_fqids, 2));
	अगर (!fq_table)
		वापस -ENOMEM;

	pr_debug("Allocated fq lookup table at %p, entry count %u\n",
		 fq_table, num_fqids * 2);
	वापस 0;
पूर्ण

अटल काष्ठा qman_fq *idx_to_fq(u32 idx)
अणु
	काष्ठा qman_fq *fq;

#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	अगर (WARN_ON(idx >= num_fqids * 2))
		वापस शून्य;
#पूर्ण_अगर
	fq = fq_table[idx];
	DPAA_ASSERT(!fq || idx == fq->idx);

	वापस fq;
पूर्ण

/*
 * Only वापसs full-service fq objects, not enqueue-only
 * references (QMAN_FQ_FLAG_NO_MODIFY).
 */
अटल काष्ठा qman_fq *fqid_to_fq(u32 fqid)
अणु
	वापस idx_to_fq(fqid * 2);
पूर्ण

अटल काष्ठा qman_fq *tag_to_fq(u32 tag)
अणु
#अगर BITS_PER_LONG == 64
	वापस idx_to_fq(tag);
#अन्यथा
	वापस (काष्ठा qman_fq *)tag;
#पूर्ण_अगर
पूर्ण

अटल u32 fq_to_tag(काष्ठा qman_fq *fq)
अणु
#अगर BITS_PER_LONG == 64
	वापस fq->idx;
#अन्यथा
	वापस (u32)fq;
#पूर्ण_अगर
पूर्ण

अटल u32 __poll_portal_slow(काष्ठा qman_portal *p, u32 is);
अटल अंतरभूत अचिन्हित पूर्णांक __poll_portal_fast(काष्ठा qman_portal *p,
					अचिन्हित पूर्णांक poll_limit, bool sched_napi);
अटल व्योम qm_congestion_task(काष्ठा work_काष्ठा *work);
अटल व्योम qm_mr_process_task(काष्ठा work_काष्ठा *work);

अटल irqवापस_t portal_isr(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा qman_portal *p = ptr;
	u32 is = qm_in(&p->p, QM_REG_ISR) & p->irq_sources;
	u32 clear = 0;

	अगर (unlikely(!is))
		वापस IRQ_NONE;

	/* DQRR-handling अगर it's पूर्णांकerrupt-driven */
	अगर (is & QM_PIRQ_DQRI) अणु
		__poll_portal_fast(p, QMAN_POLL_LIMIT, true);
		clear = QM_DQAVAIL_MASK | QM_PIRQ_DQRI;
	पूर्ण
	/* Handling of anything अन्यथा that's पूर्णांकerrupt-driven */
	clear |= __poll_portal_slow(p, is) & QM_PIRQ_SLOW;
	qm_out(&p->p, QM_REG_ISR, clear);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक drain_mr_fqrni(काष्ठा qm_portal *p)
अणु
	स्थिर जोड़ qm_mr_entry *msg;
loop:
	qm_mr_pvb_update(p);
	msg = qm_mr_current(p);
	अगर (!msg) अणु
		/*
		 * अगर MR was full and h/w had other FQRNI entries to produce, we
		 * need to allow it समय to produce those entries once the
		 * existing entries are consumed. A worst-हाल situation
		 * (fully-loaded प्रणाली) means h/w sequencers may have to करो 3-4
		 * other things beक्रमe servicing the portal's MR pump, each of
		 * which (अगर slow) may take ~50 qman cycles (which is ~200
		 * processor cycles). So rounding up and then multiplying this
		 * worst-हाल estimate by a factor of 10, just to be
		 * ultra-paranoid, goes as high as 10,000 cycles. NB, we consume
		 * one entry at a समय, so h/w has an opportunity to produce new
		 * entries well beक्रमe the ring has been fully consumed, so
		 * we're being *really* paranoid here.
		 */
		mdelay(1);
		qm_mr_pvb_update(p);
		msg = qm_mr_current(p);
		अगर (!msg)
			वापस 0;
	पूर्ण
	अगर ((msg->verb & QM_MR_VERB_TYPE_MASK) != QM_MR_VERB_FQRNI) अणु
		/* We aren't draining anything but FQRNIs */
		pr_err("Found verb 0x%x in MR\n", msg->verb);
		वापस -1;
	पूर्ण
	qm_mr_next(p);
	qm_mr_cci_consume(p, 1);
	जाओ loop;
पूर्ण

अटल पूर्णांक qman_create_portal(काष्ठा qman_portal *portal,
			      स्थिर काष्ठा qm_portal_config *c,
			      स्थिर काष्ठा qman_cgrs *cgrs)
अणु
	काष्ठा qm_portal *p;
	पूर्णांक ret;
	u32 isdr;

	p = &portal->p;

#अगर_घोषित CONFIG_FSL_PAMU
	/* PAMU is required क्रम stashing */
	portal->use_eqcr_ci_stashing = ((qman_ip_rev >= QMAN_REV30) ? 1 : 0);
#अन्यथा
	portal->use_eqcr_ci_stashing = 0;
#पूर्ण_अगर
	/*
	 * prep the low-level portal काष्ठा with the mapped addresses from the
	 * config, everything that follows depends on it and "config" is more
	 * क्रम (de)reference
	 */
	p->addr.ce = c->addr_virt_ce;
	p->addr.ce_be = c->addr_virt_ce;
	p->addr.ci = c->addr_virt_ci;
	/*
	 * If CI-stashing is used, the current शेषs use a threshold of 3,
	 * and stash with high-than-DQRR priority.
	 */
	अगर (qm_eqcr_init(p, qm_eqcr_pvb,
			portal->use_eqcr_ci_stashing ? 3 : 0, 1)) अणु
		dev_err(c->dev, "EQCR initialisation failed\n");
		जाओ fail_eqcr;
	पूर्ण
	अगर (qm_dqrr_init(p, c, qm_dqrr_dpush, qm_dqrr_pvb,
			qm_dqrr_cdc, DQRR_MAXFILL)) अणु
		dev_err(c->dev, "DQRR initialisation failed\n");
		जाओ fail_dqrr;
	पूर्ण
	अगर (qm_mr_init(p, qm_mr_pvb, qm_mr_cci)) अणु
		dev_err(c->dev, "MR initialisation failed\n");
		जाओ fail_mr;
	पूर्ण
	अगर (qm_mc_init(p)) अणु
		dev_err(c->dev, "MC initialisation failed\n");
		जाओ fail_mc;
	पूर्ण
	/* अटल पूर्णांकerrupt-gating controls */
	qm_dqrr_set_ithresh(p, QMAN_PIRQ_DQRR_ITHRESH);
	qm_mr_set_ithresh(p, QMAN_PIRQ_MR_ITHRESH);
	qm_out(p, QM_REG_ITPR, QMAN_PIRQ_IPERIOD);
	portal->cgrs = kदो_स्मृति_array(2, माप(*cgrs), GFP_KERNEL);
	अगर (!portal->cgrs)
		जाओ fail_cgrs;
	/* initial snapshot is no-depletion */
	qman_cgrs_init(&portal->cgrs[1]);
	अगर (cgrs)
		portal->cgrs[0] = *cgrs;
	अन्यथा
		/* अगर the given mask is शून्य, assume all CGRs can be seen */
		qman_cgrs_fill(&portal->cgrs[0]);
	INIT_LIST_HEAD(&portal->cgr_cbs);
	spin_lock_init(&portal->cgr_lock);
	INIT_WORK(&portal->congestion_work, qm_congestion_task);
	INIT_WORK(&portal->mr_work, qm_mr_process_task);
	portal->bits = 0;
	portal->sdqcr = QM_SDQCR_SOURCE_CHANNELS | QM_SDQCR_COUNT_UPTO3 |
			QM_SDQCR_DEDICATED_PRECEDENCE | QM_SDQCR_TYPE_PRIO_QOS |
			QM_SDQCR_TOKEN_SET(0xab) | QM_SDQCR_CHANNELS_DEDICATED;
	isdr = 0xffffffff;
	qm_out(p, QM_REG_ISDR, isdr);
	portal->irq_sources = 0;
	qm_out(p, QM_REG_IER, 0);
	snम_लिखो(portal->irqname, MAX_IRQNAME, IRQNAME, c->cpu);
	qm_out(p, QM_REG_IIR, 1);
	अगर (request_irq(c->irq, portal_isr, 0, portal->irqname,	portal)) अणु
		dev_err(c->dev, "request_irq() failed\n");
		जाओ fail_irq;
	पूर्ण

	अगर (dpaa_set_portal_irq_affinity(c->dev, c->irq, c->cpu))
		जाओ fail_affinity;

	/* Need EQCR to be empty beक्रमe continuing */
	isdr &= ~QM_PIRQ_EQCI;
	qm_out(p, QM_REG_ISDR, isdr);
	ret = qm_eqcr_get_fill(p);
	अगर (ret) अणु
		dev_err(c->dev, "EQCR unclean\n");
		जाओ fail_eqcr_empty;
	पूर्ण
	isdr &= ~(QM_PIRQ_DQRI | QM_PIRQ_MRI);
	qm_out(p, QM_REG_ISDR, isdr);
	अगर (qm_dqrr_current(p)) अणु
		dev_dbg(c->dev, "DQRR unclean\n");
		qm_dqrr_cdc_consume_n(p, 0xffff);
	पूर्ण
	अगर (qm_mr_current(p) && drain_mr_fqrni(p)) अणु
		/* special handling, drain just in हाल it's a few FQRNIs */
		स्थिर जोड़ qm_mr_entry *e = qm_mr_current(p);

		dev_err(c->dev, "MR dirty, VB 0x%x, rc 0x%x, addr 0x%llx\n",
			e->verb, e->ern.rc, qm_fd_addr_get64(&e->ern.fd));
		जाओ fail_dqrr_mr_empty;
	पूर्ण
	/* Success */
	portal->config = c;
	qm_out(p, QM_REG_ISR, 0xffffffff);
	qm_out(p, QM_REG_ISDR, 0);
	अगर (!qman_requires_cleanup())
		qm_out(p, QM_REG_IIR, 0);
	/* Write a sane SDQCR */
	qm_dqrr_sdqcr_set(p, portal->sdqcr);
	वापस 0;

fail_dqrr_mr_empty:
fail_eqcr_empty:
fail_affinity:
	मुक्त_irq(c->irq, portal);
fail_irq:
	kमुक्त(portal->cgrs);
fail_cgrs:
	qm_mc_finish(p);
fail_mc:
	qm_mr_finish(p);
fail_mr:
	qm_dqrr_finish(p);
fail_dqrr:
	qm_eqcr_finish(p);
fail_eqcr:
	वापस -EIO;
पूर्ण

काष्ठा qman_portal *qman_create_affine_portal(स्थिर काष्ठा qm_portal_config *c,
					      स्थिर काष्ठा qman_cgrs *cgrs)
अणु
	काष्ठा qman_portal *portal;
	पूर्णांक err;

	portal = &per_cpu(qman_affine_portal, c->cpu);
	err = qman_create_portal(portal, c, cgrs);
	अगर (err)
		वापस शून्य;

	spin_lock(&affine_mask_lock);
	cpumask_set_cpu(c->cpu, &affine_mask);
	affine_channels[c->cpu] = c->channel;
	affine_portals[c->cpu] = portal;
	spin_unlock(&affine_mask_lock);

	वापस portal;
पूर्ण

अटल व्योम qman_destroy_portal(काष्ठा qman_portal *qm)
अणु
	स्थिर काष्ठा qm_portal_config *pcfg;

	/* Stop dequeues on the portal */
	qm_dqrr_sdqcr_set(&qm->p, 0);

	/*
	 * NB we करो this to "quiesce" EQCR. If we add enqueue-completions or
	 * something related to QM_PIRQ_EQCI, this may need fixing.
	 * Also, due to the prefetching model used क्रम CI updates in the enqueue
	 * path, this update will only invalidate the CI cacheline *after*
	 * working on it, so we need to call this twice to ensure a full update
	 * irrespective of where the enqueue processing was at when the tearकरोwn
	 * began.
	 */
	qm_eqcr_cce_update(&qm->p);
	qm_eqcr_cce_update(&qm->p);
	pcfg = qm->config;

	मुक्त_irq(pcfg->irq, qm);

	kमुक्त(qm->cgrs);
	qm_mc_finish(&qm->p);
	qm_mr_finish(&qm->p);
	qm_dqrr_finish(&qm->p);
	qm_eqcr_finish(&qm->p);

	qm->config = शून्य;
पूर्ण

स्थिर काष्ठा qm_portal_config *qman_destroy_affine_portal(व्योम)
अणु
	काष्ठा qman_portal *qm = get_affine_portal();
	स्थिर काष्ठा qm_portal_config *pcfg;
	पूर्णांक cpu;

	pcfg = qm->config;
	cpu = pcfg->cpu;

	qman_destroy_portal(qm);

	spin_lock(&affine_mask_lock);
	cpumask_clear_cpu(cpu, &affine_mask);
	spin_unlock(&affine_mask_lock);
	put_affine_portal();
	वापस pcfg;
पूर्ण

/* Inline helper to reduce nesting in __poll_portal_slow() */
अटल अंतरभूत व्योम fq_state_change(काष्ठा qman_portal *p, काष्ठा qman_fq *fq,
				   स्थिर जोड़ qm_mr_entry *msg, u8 verb)
अणु
	चयन (verb) अणु
	हाल QM_MR_VERB_FQRL:
		DPAA_ASSERT(fq_isset(fq, QMAN_FQ_STATE_ORL));
		fq_clear(fq, QMAN_FQ_STATE_ORL);
		अवरोध;
	हाल QM_MR_VERB_FQRN:
		DPAA_ASSERT(fq->state == qman_fq_state_parked ||
			    fq->state == qman_fq_state_sched);
		DPAA_ASSERT(fq_isset(fq, QMAN_FQ_STATE_CHANGING));
		fq_clear(fq, QMAN_FQ_STATE_CHANGING);
		अगर (msg->fq.fqs & QM_MR_FQS_NOTEMPTY)
			fq_set(fq, QMAN_FQ_STATE_NE);
		अगर (msg->fq.fqs & QM_MR_FQS_ORLPRESENT)
			fq_set(fq, QMAN_FQ_STATE_ORL);
		fq->state = qman_fq_state_retired;
		अवरोध;
	हाल QM_MR_VERB_FQPN:
		DPAA_ASSERT(fq->state == qman_fq_state_sched);
		DPAA_ASSERT(fq_isclear(fq, QMAN_FQ_STATE_CHANGING));
		fq->state = qman_fq_state_parked;
	पूर्ण
पूर्ण

अटल व्योम qm_congestion_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qman_portal *p = container_of(work, काष्ठा qman_portal,
					     congestion_work);
	काष्ठा qman_cgrs rr, c;
	जोड़ qm_mc_result *mcr;
	काष्ठा qman_cgr *cgr;

	spin_lock(&p->cgr_lock);
	qm_mc_start(&p->p);
	qm_mc_commit(&p->p, QM_MCC_VERB_QUERYCONGESTION);
	अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
		spin_unlock(&p->cgr_lock);
		dev_crit(p->config->dev, "QUERYCONGESTION timeout\n");
		qman_p_irqsource_add(p, QM_PIRQ_CSCI);
		वापस;
	पूर्ण
	/* mask out the ones I'm not पूर्णांकerested in */
	qman_cgrs_and(&rr, (काष्ठा qman_cgrs *)&mcr->querycongestion.state,
		      &p->cgrs[0]);
	/* check previous snapshot क्रम delta, enter/निकास congestion */
	qman_cgrs_xor(&c, &rr, &p->cgrs[1]);
	/* update snapshot */
	qman_cgrs_cp(&p->cgrs[1], &rr);
	/* Invoke callback */
	list_क्रम_each_entry(cgr, &p->cgr_cbs, node)
		अगर (cgr->cb && qman_cgrs_get(&c, cgr->cgrid))
			cgr->cb(p, cgr, qman_cgrs_get(&rr, cgr->cgrid));
	spin_unlock(&p->cgr_lock);
	qman_p_irqsource_add(p, QM_PIRQ_CSCI);
पूर्ण

अटल व्योम qm_mr_process_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qman_portal *p = container_of(work, काष्ठा qman_portal,
					     mr_work);
	स्थिर जोड़ qm_mr_entry *msg;
	काष्ठा qman_fq *fq;
	u8 verb, num = 0;

	preempt_disable();

	जबतक (1) अणु
		qm_mr_pvb_update(&p->p);
		msg = qm_mr_current(&p->p);
		अगर (!msg)
			अवरोध;

		verb = msg->verb & QM_MR_VERB_TYPE_MASK;
		/* The message is a software ERN अगरf the 0x20 bit is clear */
		अगर (verb & 0x20) अणु
			चयन (verb) अणु
			हाल QM_MR_VERB_FQRNI:
				/* nada, we drop FQRNIs on the न्यूनमान */
				अवरोध;
			हाल QM_MR_VERB_FQRN:
			हाल QM_MR_VERB_FQRL:
				/* Lookup in the retirement table */
				fq = fqid_to_fq(qm_fqid_get(&msg->fq));
				अगर (WARN_ON(!fq))
					अवरोध;
				fq_state_change(p, fq, msg, verb);
				अगर (fq->cb.fqs)
					fq->cb.fqs(p, fq, msg);
				अवरोध;
			हाल QM_MR_VERB_FQPN:
				/* Parked */
				fq = tag_to_fq(be32_to_cpu(msg->fq.context_b));
				fq_state_change(p, fq, msg, verb);
				अगर (fq->cb.fqs)
					fq->cb.fqs(p, fq, msg);
				अवरोध;
			हाल QM_MR_VERB_DC_ERN:
				/* DCP ERN */
				pr_crit_once("Leaking DCP ERNs!\n");
				अवरोध;
			शेष:
				pr_crit("Invalid MR verb 0x%02x\n", verb);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Its a software ERN */
			fq = tag_to_fq(be32_to_cpu(msg->ern.tag));
			fq->cb.ern(p, fq, msg);
		पूर्ण
		num++;
		qm_mr_next(&p->p);
	पूर्ण

	qm_mr_cci_consume(&p->p, num);
	qman_p_irqsource_add(p, QM_PIRQ_MRI);
	preempt_enable();
पूर्ण

अटल u32 __poll_portal_slow(काष्ठा qman_portal *p, u32 is)
अणु
	अगर (is & QM_PIRQ_CSCI) अणु
		qman_p_irqsource_हटाओ(p, QM_PIRQ_CSCI);
		queue_work_on(smp_processor_id(), qm_portal_wq,
			      &p->congestion_work);
	पूर्ण

	अगर (is & QM_PIRQ_EQRI) अणु
		qm_eqcr_cce_update(&p->p);
		qm_eqcr_set_ithresh(&p->p, 0);
		wake_up(&affine_queue);
	पूर्ण

	अगर (is & QM_PIRQ_MRI) अणु
		qman_p_irqsource_हटाओ(p, QM_PIRQ_MRI);
		queue_work_on(smp_processor_id(), qm_portal_wq,
			      &p->mr_work);
	पूर्ण

	वापस is;
पूर्ण

/*
 * हटाओ some slowish-path stuff from the "fast path" and make sure it isn't
 * अंतरभूतd.
 */
अटल noअंतरभूत व्योम clear_vdqcr(काष्ठा qman_portal *p, काष्ठा qman_fq *fq)
अणु
	p->vdqcr_owned = शून्य;
	fq_clear(fq, QMAN_FQ_STATE_VDQCR);
	wake_up(&affine_queue);
पूर्ण

/*
 * The only states that would conflict with other things अगर they ran at the
 * same समय on the same cpu are:
 *
 *   (i) setting/clearing vdqcr_owned, and
 *  (ii) clearing the NE (Not Empty) flag.
 *
 * Both are safe. Because;
 *
 *   (i) this clearing can only occur after qman_अस्थिर_dequeue() has set the
 *	 vdqcr_owned field (which it करोes beक्रमe setting VDQCR), and
 *	 qman_अस्थिर_dequeue() blocks पूर्णांकerrupts and preemption जबतक this is
 *	 करोne so that we can't पूर्णांकerfere.
 *  (ii) the NE flag is only cleared after qman_retire_fq() has set it, and as
 *	 with (i) that API prevents us from पूर्णांकerfering until it's safe.
 *
 * The good thing is that qman_अस्थिर_dequeue() and qman_retire_fq() run far
 * less frequently (ie. per-FQ) than __poll_portal_fast() करोes, so the nett
 * advantage comes from this function not having to "lock" anything at all.
 *
 * Note also that the callbacks are invoked at poपूर्णांकs which are safe against the
 * above potential conflicts, but that this function itself is not re-entrant
 * (this is because the function tracks one end of each FIFO in the portal and
 * we करो *not* want to lock that). So the consequence is that it is safe क्रम
 * user callbacks to call पूर्णांकo any QMan API.
 */
अटल अंतरभूत अचिन्हित पूर्णांक __poll_portal_fast(काष्ठा qman_portal *p,
					अचिन्हित पूर्णांक poll_limit, bool sched_napi)
अणु
	स्थिर काष्ठा qm_dqrr_entry *dq;
	काष्ठा qman_fq *fq;
	क्रमागत qman_cb_dqrr_result res;
	अचिन्हित पूर्णांक limit = 0;

	करो अणु
		qm_dqrr_pvb_update(&p->p);
		dq = qm_dqrr_current(&p->p);
		अगर (!dq)
			अवरोध;

		अगर (dq->stat & QM_DQRR_STAT_UNSCHEDULED) अणु
			/*
			 * VDQCR: करोn't trust context_b as the FQ may have
			 * been configured क्रम h/w consumption and we're
			 * draining it post-retirement.
			 */
			fq = p->vdqcr_owned;
			/*
			 * We only set QMAN_FQ_STATE_NE when retiring, so we
			 * only need to check क्रम clearing it when करोing
			 * अस्थिर dequeues.  It's one less thing to check
			 * in the critical path (SDQCR).
			 */
			अगर (dq->stat & QM_DQRR_STAT_FQ_EMPTY)
				fq_clear(fq, QMAN_FQ_STATE_NE);
			/*
			 * This is duplicated from the SDQCR code, but we
			 * have stuff to करो beक्रमe *and* after this callback,
			 * and we करोn't want multiple अगर()s in the critical
			 * path (SDQCR).
			 */
			res = fq->cb.dqrr(p, fq, dq, sched_napi);
			अगर (res == qman_cb_dqrr_stop)
				अवरोध;
			/* Check क्रम VDQCR completion */
			अगर (dq->stat & QM_DQRR_STAT_DQCR_EXPIRED)
				clear_vdqcr(p, fq);
		पूर्ण अन्यथा अणु
			/* SDQCR: context_b poपूर्णांकs to the FQ */
			fq = tag_to_fq(be32_to_cpu(dq->context_b));
			/* Now let the callback करो its stuff */
			res = fq->cb.dqrr(p, fq, dq, sched_napi);
			/*
			 * The callback can request that we निकास without
			 * consuming this entry nor advancing;
			 */
			अगर (res == qman_cb_dqrr_stop)
				अवरोध;
		पूर्ण
		/* Interpret 'dq' from a driver perspective. */
		/*
		 * Parking isn't possible unless HELDACTIVE was set. NB,
		 * FORCEELIGIBLE implies HELDACTIVE, so we only need to
		 * check क्रम HELDACTIVE to cover both.
		 */
		DPAA_ASSERT((dq->stat & QM_DQRR_STAT_FQ_HELDACTIVE) ||
			    (res != qman_cb_dqrr_park));
		/* just means "skip it, I'll consume it myself later on" */
		अगर (res != qman_cb_dqrr_defer)
			qm_dqrr_cdc_consume_1ptr(&p->p, dq,
						 res == qman_cb_dqrr_park);
		/* Move क्रमward */
		qm_dqrr_next(&p->p);
		/*
		 * Entry processed and consumed, increment our counter.  The
		 * callback can request that we निकास after consuming the
		 * entry, and we also निकास अगर we reach our processing limit,
		 * so loop back only अगर neither of these conditions is met.
		 */
	पूर्ण जबतक (++limit < poll_limit && res != qman_cb_dqrr_consume_stop);

	वापस limit;
पूर्ण

व्योम qman_p_irqsource_add(काष्ठा qman_portal *p, u32 bits)
अणु
	अचिन्हित दीर्घ irqflags;

	local_irq_save(irqflags);
	p->irq_sources |= bits & QM_PIRQ_VISIBLE;
	qm_out(&p->p, QM_REG_IER, p->irq_sources);
	local_irq_restore(irqflags);
पूर्ण
EXPORT_SYMBOL(qman_p_irqsource_add);

व्योम qman_p_irqsource_हटाओ(काष्ठा qman_portal *p, u32 bits)
अणु
	अचिन्हित दीर्घ irqflags;
	u32 ier;

	/*
	 * Our पूर्णांकerrupt handler only processes+clears status रेजिस्टर bits that
	 * are in p->irq_sources. As we're trimming that mask, अगर one of them
	 * were to निश्चित in the status रेजिस्टर just beक्रमe we हटाओ it from
	 * the enable रेजिस्टर, there would be an पूर्णांकerrupt-storm when we
	 * release the IRQ lock. So we रुको क्रम the enable रेजिस्टर update to
	 * take effect in h/w (by पढ़ोing it back) and then clear all other bits
	 * in the status रेजिस्टर. Ie. we clear them from ISR once it's certain
	 * IER won't allow them to reनिश्चित.
	 */
	local_irq_save(irqflags);
	bits &= QM_PIRQ_VISIBLE;
	p->irq_sources &= ~bits;
	qm_out(&p->p, QM_REG_IER, p->irq_sources);
	ier = qm_in(&p->p, QM_REG_IER);
	/*
	 * Using "~ier" (rather than "bits" or "~p->irq_sources") creates a
	 * data-dependency, ie. to protect against re-ordering.
	 */
	qm_out(&p->p, QM_REG_ISR, ~ier);
	local_irq_restore(irqflags);
पूर्ण
EXPORT_SYMBOL(qman_p_irqsource_हटाओ);

स्थिर cpumask_t *qman_affine_cpus(व्योम)
अणु
	वापस &affine_mask;
पूर्ण
EXPORT_SYMBOL(qman_affine_cpus);

u16 qman_affine_channel(पूर्णांक cpu)
अणु
	अगर (cpu < 0) अणु
		काष्ठा qman_portal *portal = get_affine_portal();

		cpu = portal->config->cpu;
		put_affine_portal();
	पूर्ण
	WARN_ON(!cpumask_test_cpu(cpu, &affine_mask));
	वापस affine_channels[cpu];
पूर्ण
EXPORT_SYMBOL(qman_affine_channel);

काष्ठा qman_portal *qman_get_affine_portal(पूर्णांक cpu)
अणु
	वापस affine_portals[cpu];
पूर्ण
EXPORT_SYMBOL(qman_get_affine_portal);

पूर्णांक qman_start_using_portal(काष्ठा qman_portal *p, काष्ठा device *dev)
अणु
	वापस (!device_link_add(dev, p->config->dev,
				 DL_FLAG_AUTOREMOVE_CONSUMER)) ? -EINVAL : 0;
पूर्ण
EXPORT_SYMBOL(qman_start_using_portal);

पूर्णांक qman_p_poll_dqrr(काष्ठा qman_portal *p, अचिन्हित पूर्णांक limit)
अणु
	वापस __poll_portal_fast(p, limit, false);
पूर्ण
EXPORT_SYMBOL(qman_p_poll_dqrr);

व्योम qman_p_अटल_dequeue_add(काष्ठा qman_portal *p, u32 pools)
अणु
	अचिन्हित दीर्घ irqflags;

	local_irq_save(irqflags);
	pools &= p->config->pools;
	p->sdqcr |= pools;
	qm_dqrr_sdqcr_set(&p->p, p->sdqcr);
	local_irq_restore(irqflags);
पूर्ण
EXPORT_SYMBOL(qman_p_अटल_dequeue_add);

/* Frame queue API */

अटल स्थिर अक्षर *mcr_result_str(u8 result)
अणु
	चयन (result) अणु
	हाल QM_MCR_RESULT_शून्य:
		वापस "QM_MCR_RESULT_NULL";
	हाल QM_MCR_RESULT_OK:
		वापस "QM_MCR_RESULT_OK";
	हाल QM_MCR_RESULT_ERR_FQID:
		वापस "QM_MCR_RESULT_ERR_FQID";
	हाल QM_MCR_RESULT_ERR_FQSTATE:
		वापस "QM_MCR_RESULT_ERR_FQSTATE";
	हाल QM_MCR_RESULT_ERR_NOTEMPTY:
		वापस "QM_MCR_RESULT_ERR_NOTEMPTY";
	हाल QM_MCR_RESULT_PENDING:
		वापस "QM_MCR_RESULT_PENDING";
	हाल QM_MCR_RESULT_ERR_BADCOMMAND:
		वापस "QM_MCR_RESULT_ERR_BADCOMMAND";
	पूर्ण
	वापस "<unknown MCR result>";
पूर्ण

पूर्णांक qman_create_fq(u32 fqid, u32 flags, काष्ठा qman_fq *fq)
अणु
	अगर (flags & QMAN_FQ_FLAG_DYNAMIC_FQID) अणु
		पूर्णांक ret = qman_alloc_fqid(&fqid);

		अगर (ret)
			वापस ret;
	पूर्ण
	fq->fqid = fqid;
	fq->flags = flags;
	fq->state = qman_fq_state_oos;
	fq->cgr_groupid = 0;

	/* A context_b of 0 is allegedly special, so करोn't use that fqid */
	अगर (fqid == 0 || fqid >= num_fqids) अणु
		WARN(1, "bad fqid %d\n", fqid);
		वापस -EINVAL;
	पूर्ण

	fq->idx = fqid * 2;
	अगर (flags & QMAN_FQ_FLAG_NO_MODIFY)
		fq->idx++;

	WARN_ON(fq_table[fq->idx]);
	fq_table[fq->idx] = fq;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qman_create_fq);

व्योम qman_destroy_fq(काष्ठा qman_fq *fq)
अणु
	/*
	 * We करोn't need to lock the FQ as it is a pre-condition that the FQ be
	 * quiesced. Instead, run some checks.
	 */
	चयन (fq->state) अणु
	हाल qman_fq_state_parked:
	हाल qman_fq_state_oos:
		अगर (fq_isset(fq, QMAN_FQ_FLAG_DYNAMIC_FQID))
			qman_release_fqid(fq->fqid);

		DPAA_ASSERT(fq_table[fq->idx]);
		fq_table[fq->idx] = शून्य;
		वापस;
	शेष:
		अवरोध;
	पूर्ण
	DPAA_ASSERT(शून्य == "qman_free_fq() on unquiesced FQ!");
पूर्ण
EXPORT_SYMBOL(qman_destroy_fq);

u32 qman_fq_fqid(काष्ठा qman_fq *fq)
अणु
	वापस fq->fqid;
पूर्ण
EXPORT_SYMBOL(qman_fq_fqid);

पूर्णांक qman_init_fq(काष्ठा qman_fq *fq, u32 flags, काष्ठा qm_mcc_initfq *opts)
अणु
	जोड़ qm_mc_command *mcc;
	जोड़ qm_mc_result *mcr;
	काष्ठा qman_portal *p;
	u8 res, myverb;
	पूर्णांक ret = 0;

	myverb = (flags & QMAN_INITFQ_FLAG_SCHED)
		? QM_MCC_VERB_INITFQ_SCHED : QM_MCC_VERB_INITFQ_PARKED;

	अगर (fq->state != qman_fq_state_oos &&
	    fq->state != qman_fq_state_parked)
		वापस -EINVAL;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	अगर (fq_isset(fq, QMAN_FQ_FLAG_NO_MODIFY))
		वापस -EINVAL;
#पूर्ण_अगर
	अगर (opts && (be16_to_cpu(opts->we_mask) & QM_INITFQ_WE_OAC)) अणु
		/* And can't be set at the same समय as TDTHRESH */
		अगर (be16_to_cpu(opts->we_mask) & QM_INITFQ_WE_TDTHRESH)
			वापस -EINVAL;
	पूर्ण
	/* Issue an INITFQ_[PARKED|SCHED] management command */
	p = get_affine_portal();
	अगर (fq_isset(fq, QMAN_FQ_STATE_CHANGING) ||
	    (fq->state != qman_fq_state_oos &&
	     fq->state != qman_fq_state_parked)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	mcc = qm_mc_start(&p->p);
	अगर (opts)
		mcc->initfq = *opts;
	qm_fqid_set(&mcc->fq, fq->fqid);
	mcc->initfq.count = 0;
	/*
	 * If the FQ करोes *not* have the TO_DCPORTAL flag, context_b is set as a
	 * demux poपूर्णांकer. Otherwise, the caller-provided value is allowed to
	 * stand, करोn't overग_लिखो it.
	 */
	अगर (fq_isclear(fq, QMAN_FQ_FLAG_TO_DCPORTAL)) अणु
		dma_addr_t phys_fq;

		mcc->initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_CONTEXTB);
		mcc->initfq.fqd.context_b = cpu_to_be32(fq_to_tag(fq));
		/*
		 *  and the physical address - NB, अगर the user wasn't trying to
		 * set CONTEXTA, clear the stashing settings.
		 */
		अगर (!(be16_to_cpu(mcc->initfq.we_mask) &
				  QM_INITFQ_WE_CONTEXTA)) अणु
			mcc->initfq.we_mask |=
				cpu_to_be16(QM_INITFQ_WE_CONTEXTA);
			स_रखो(&mcc->initfq.fqd.context_a, 0,
				माप(mcc->initfq.fqd.context_a));
		पूर्ण अन्यथा अणु
			काष्ठा qman_portal *p = qman_dma_portal;

			phys_fq = dma_map_single(p->config->dev, fq,
						 माप(*fq), DMA_TO_DEVICE);
			अगर (dma_mapping_error(p->config->dev, phys_fq)) अणु
				dev_err(p->config->dev, "dma_mapping failed\n");
				ret = -EIO;
				जाओ out;
			पूर्ण

			qm_fqd_stashing_set64(&mcc->initfq.fqd, phys_fq);
		पूर्ण
	पूर्ण
	अगर (flags & QMAN_INITFQ_FLAG_LOCAL) अणु
		पूर्णांक wq = 0;

		अगर (!(be16_to_cpu(mcc->initfq.we_mask) &
				  QM_INITFQ_WE_DESTWQ)) अणु
			mcc->initfq.we_mask |=
				cpu_to_be16(QM_INITFQ_WE_DESTWQ);
			wq = 4;
		पूर्ण
		qm_fqd_set_destwq(&mcc->initfq.fqd, p->config->channel, wq);
	पूर्ण
	qm_mc_commit(&p->p, myverb);
	अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
		dev_err(p->config->dev, "MCR timeout\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == myverb);
	res = mcr->result;
	अगर (res != QM_MCR_RESULT_OK) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण
	अगर (opts) अणु
		अगर (be16_to_cpu(opts->we_mask) & QM_INITFQ_WE_FQCTRL) अणु
			अगर (be16_to_cpu(opts->fqd.fq_ctrl) & QM_FQCTRL_CGE)
				fq_set(fq, QMAN_FQ_STATE_CGR_EN);
			अन्यथा
				fq_clear(fq, QMAN_FQ_STATE_CGR_EN);
		पूर्ण
		अगर (be16_to_cpu(opts->we_mask) & QM_INITFQ_WE_CGID)
			fq->cgr_groupid = opts->fqd.cgid;
	पूर्ण
	fq->state = (flags & QMAN_INITFQ_FLAG_SCHED) ?
		qman_fq_state_sched : qman_fq_state_parked;

out:
	put_affine_portal();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(qman_init_fq);

पूर्णांक qman_schedule_fq(काष्ठा qman_fq *fq)
अणु
	जोड़ qm_mc_command *mcc;
	जोड़ qm_mc_result *mcr;
	काष्ठा qman_portal *p;
	पूर्णांक ret = 0;

	अगर (fq->state != qman_fq_state_parked)
		वापस -EINVAL;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	अगर (fq_isset(fq, QMAN_FQ_FLAG_NO_MODIFY))
		वापस -EINVAL;
#पूर्ण_अगर
	/* Issue a ALTERFQ_SCHED management command */
	p = get_affine_portal();
	अगर (fq_isset(fq, QMAN_FQ_STATE_CHANGING) ||
	    fq->state != qman_fq_state_parked) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fq->fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_ALTER_SCHED);
	अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
		dev_err(p->config->dev, "ALTER_SCHED timeout\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_ALTER_SCHED);
	अगर (mcr->result != QM_MCR_RESULT_OK) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण
	fq->state = qman_fq_state_sched;
out:
	put_affine_portal();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(qman_schedule_fq);

पूर्णांक qman_retire_fq(काष्ठा qman_fq *fq, u32 *flags)
अणु
	जोड़ qm_mc_command *mcc;
	जोड़ qm_mc_result *mcr;
	काष्ठा qman_portal *p;
	पूर्णांक ret;
	u8 res;

	अगर (fq->state != qman_fq_state_parked &&
	    fq->state != qman_fq_state_sched)
		वापस -EINVAL;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	अगर (fq_isset(fq, QMAN_FQ_FLAG_NO_MODIFY))
		वापस -EINVAL;
#पूर्ण_अगर
	p = get_affine_portal();
	अगर (fq_isset(fq, QMAN_FQ_STATE_CHANGING) ||
	    fq->state == qman_fq_state_retired ||
	    fq->state == qman_fq_state_oos) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fq->fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_ALTER_RETIRE);
	अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
		dev_crit(p->config->dev, "ALTER_RETIRE timeout\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_ALTER_RETIRE);
	res = mcr->result;
	/*
	 * "Elegant" would be to treat OK/PENDING the same way; set CHANGING,
	 * and defer the flags until FQRNI or FQRN (respectively) show up. But
	 * "Friendly" is to process OK immediately, and not set CHANGING. We करो
	 * मित्रly, otherwise the caller करोesn't necessarily have a fully
	 * "retired" FQ on वापस even अगर the retirement was immediate. However
	 * this करोes mean some code duplication between here and
	 * fq_state_change().
	 */
	अगर (res == QM_MCR_RESULT_OK) अणु
		ret = 0;
		/* Process 'fq' right away, we'll ignore FQRNI */
		अगर (mcr->alterfq.fqs & QM_MCR_FQS_NOTEMPTY)
			fq_set(fq, QMAN_FQ_STATE_NE);
		अगर (mcr->alterfq.fqs & QM_MCR_FQS_ORLPRESENT)
			fq_set(fq, QMAN_FQ_STATE_ORL);
		अगर (flags)
			*flags = fq->flags;
		fq->state = qman_fq_state_retired;
		अगर (fq->cb.fqs) अणु
			/*
			 * Another issue with supporting "immediate" retirement
			 * is that we're क्रमced to drop FQRNIs, because by the
			 * समय they're seen it may alपढ़ोy be "too late" (the
			 * fq may have been OOS'd and free()'d alपढ़ोy). But अगर
			 * the upper layer wants a callback whether it's
			 * immediate or not, we have to fake a "MR" entry to
			 * look like an FQRNI...
			 */
			जोड़ qm_mr_entry msg;

			msg.verb = QM_MR_VERB_FQRNI;
			msg.fq.fqs = mcr->alterfq.fqs;
			qm_fqid_set(&msg.fq, fq->fqid);
			msg.fq.context_b = cpu_to_be32(fq_to_tag(fq));
			fq->cb.fqs(p, fq, &msg);
		पूर्ण
	पूर्ण अन्यथा अगर (res == QM_MCR_RESULT_PENDING) अणु
		ret = 1;
		fq_set(fq, QMAN_FQ_STATE_CHANGING);
	पूर्ण अन्यथा अणु
		ret = -EIO;
	पूर्ण
out:
	put_affine_portal();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(qman_retire_fq);

पूर्णांक qman_oos_fq(काष्ठा qman_fq *fq)
अणु
	जोड़ qm_mc_command *mcc;
	जोड़ qm_mc_result *mcr;
	काष्ठा qman_portal *p;
	पूर्णांक ret = 0;

	अगर (fq->state != qman_fq_state_retired)
		वापस -EINVAL;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	अगर (fq_isset(fq, QMAN_FQ_FLAG_NO_MODIFY))
		वापस -EINVAL;
#पूर्ण_अगर
	p = get_affine_portal();
	अगर (fq_isset(fq, QMAN_FQ_STATE_BLOCKOOS) ||
	    fq->state != qman_fq_state_retired) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fq->fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_ALTER_OOS);
	अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण
	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_ALTER_OOS);
	अगर (mcr->result != QM_MCR_RESULT_OK) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण
	fq->state = qman_fq_state_oos;
out:
	put_affine_portal();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(qman_oos_fq);

पूर्णांक qman_query_fq(काष्ठा qman_fq *fq, काष्ठा qm_fqd *fqd)
अणु
	जोड़ qm_mc_command *mcc;
	जोड़ qm_mc_result *mcr;
	काष्ठा qman_portal *p = get_affine_portal();
	पूर्णांक ret = 0;

	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fq->fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_QUERYFQ);
	अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_QUERYFQ);
	अगर (mcr->result == QM_MCR_RESULT_OK)
		*fqd = mcr->queryfq.fqd;
	अन्यथा
		ret = -EIO;
out:
	put_affine_portal();
	वापस ret;
पूर्ण

पूर्णांक qman_query_fq_np(काष्ठा qman_fq *fq, काष्ठा qm_mcr_queryfq_np *np)
अणु
	जोड़ qm_mc_command *mcc;
	जोड़ qm_mc_result *mcr;
	काष्ठा qman_portal *p = get_affine_portal();
	पूर्णांक ret = 0;

	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fq->fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_QUERYFQ_NP);
	अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_QUERYFQ_NP);
	अगर (mcr->result == QM_MCR_RESULT_OK)
		*np = mcr->queryfq_np;
	अन्यथा अगर (mcr->result == QM_MCR_RESULT_ERR_FQID)
		ret = -दुस्फल;
	अन्यथा
		ret = -EIO;
out:
	put_affine_portal();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(qman_query_fq_np);

अटल पूर्णांक qman_query_cgr(काष्ठा qman_cgr *cgr,
			  काष्ठा qm_mcr_querycgr *cgrd)
अणु
	जोड़ qm_mc_command *mcc;
	जोड़ qm_mc_result *mcr;
	काष्ठा qman_portal *p = get_affine_portal();
	पूर्णांक ret = 0;

	mcc = qm_mc_start(&p->p);
	mcc->cgr.cgid = cgr->cgrid;
	qm_mc_commit(&p->p, QM_MCC_VERB_QUERYCGR);
	अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण
	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCC_VERB_QUERYCGR);
	अगर (mcr->result == QM_MCR_RESULT_OK)
		*cgrd = mcr->querycgr;
	अन्यथा अणु
		dev_err(p->config->dev, "QUERY_CGR failed: %s\n",
			mcr_result_str(mcr->result));
		ret = -EIO;
	पूर्ण
out:
	put_affine_portal();
	वापस ret;
पूर्ण

पूर्णांक qman_query_cgr_congested(काष्ठा qman_cgr *cgr, bool *result)
अणु
	काष्ठा qm_mcr_querycgr query_cgr;
	पूर्णांक err;

	err = qman_query_cgr(cgr, &query_cgr);
	अगर (err)
		वापस err;

	*result = !!query_cgr.cgr.cs;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qman_query_cgr_congested);

/* पूर्णांकernal function used as a रुको_event() expression */
अटल पूर्णांक set_p_vdqcr(काष्ठा qman_portal *p, काष्ठा qman_fq *fq, u32 vdqcr)
अणु
	अचिन्हित दीर्घ irqflags;
	पूर्णांक ret = -EBUSY;

	local_irq_save(irqflags);
	अगर (p->vdqcr_owned)
		जाओ out;
	अगर (fq_isset(fq, QMAN_FQ_STATE_VDQCR))
		जाओ out;

	fq_set(fq, QMAN_FQ_STATE_VDQCR);
	p->vdqcr_owned = fq;
	qm_dqrr_vdqcr_set(&p->p, vdqcr);
	ret = 0;
out:
	local_irq_restore(irqflags);
	वापस ret;
पूर्ण

अटल पूर्णांक set_vdqcr(काष्ठा qman_portal **p, काष्ठा qman_fq *fq, u32 vdqcr)
अणु
	पूर्णांक ret;

	*p = get_affine_portal();
	ret = set_p_vdqcr(*p, fq, vdqcr);
	put_affine_portal();
	वापस ret;
पूर्ण

अटल पूर्णांक रुको_vdqcr_start(काष्ठा qman_portal **p, काष्ठा qman_fq *fq,
				u32 vdqcr, u32 flags)
अणु
	पूर्णांक ret = 0;

	अगर (flags & QMAN_VOLATILE_FLAG_WAIT_INT)
		ret = रुको_event_पूर्णांकerruptible(affine_queue,
				!set_vdqcr(p, fq, vdqcr));
	अन्यथा
		रुको_event(affine_queue, !set_vdqcr(p, fq, vdqcr));
	वापस ret;
पूर्ण

पूर्णांक qman_अस्थिर_dequeue(काष्ठा qman_fq *fq, u32 flags, u32 vdqcr)
अणु
	काष्ठा qman_portal *p;
	पूर्णांक ret;

	अगर (fq->state != qman_fq_state_parked &&
	    fq->state != qman_fq_state_retired)
		वापस -EINVAL;
	अगर (vdqcr & QM_VDQCR_FQID_MASK)
		वापस -EINVAL;
	अगर (fq_isset(fq, QMAN_FQ_STATE_VDQCR))
		वापस -EBUSY;
	vdqcr = (vdqcr & ~QM_VDQCR_FQID_MASK) | fq->fqid;
	अगर (flags & QMAN_VOLATILE_FLAG_WAIT)
		ret = रुको_vdqcr_start(&p, fq, vdqcr, flags);
	अन्यथा
		ret = set_vdqcr(&p, fq, vdqcr);
	अगर (ret)
		वापस ret;
	/* VDQCR is set */
	अगर (flags & QMAN_VOLATILE_FLAG_FINISH) अणु
		अगर (flags & QMAN_VOLATILE_FLAG_WAIT_INT)
			/*
			 * NB: करोn't propagate any error - the caller wouldn't
			 * know whether the VDQCR was issued or not. A संकेत
			 * could arrive after वापसing anyway, so the caller
			 * can check संकेत_pending() अगर that's an issue.
			 */
			रुको_event_पूर्णांकerruptible(affine_queue,
				!fq_isset(fq, QMAN_FQ_STATE_VDQCR));
		अन्यथा
			रुको_event(affine_queue,
				!fq_isset(fq, QMAN_FQ_STATE_VDQCR));
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qman_अस्थिर_dequeue);

अटल व्योम update_eqcr_ci(काष्ठा qman_portal *p, u8 avail)
अणु
	अगर (avail)
		qm_eqcr_cce_prefetch(&p->p);
	अन्यथा
		qm_eqcr_cce_update(&p->p);
पूर्ण

पूर्णांक qman_enqueue(काष्ठा qman_fq *fq, स्थिर काष्ठा qm_fd *fd)
अणु
	काष्ठा qman_portal *p;
	काष्ठा qm_eqcr_entry *eq;
	अचिन्हित दीर्घ irqflags;
	u8 avail;

	p = get_affine_portal();
	local_irq_save(irqflags);

	अगर (p->use_eqcr_ci_stashing) अणु
		/*
		 * The stashing हाल is easy, only update अगर we need to in
		 * order to try and liberate ring entries.
		 */
		eq = qm_eqcr_start_stash(&p->p);
	पूर्ण अन्यथा अणु
		/*
		 * The non-stashing हाल is harder, need to prefetch ahead of
		 * समय.
		 */
		avail = qm_eqcr_get_avail(&p->p);
		अगर (avail < 2)
			update_eqcr_ci(p, avail);
		eq = qm_eqcr_start_no_stash(&p->p);
	पूर्ण

	अगर (unlikely(!eq))
		जाओ out;

	qm_fqid_set(eq, fq->fqid);
	eq->tag = cpu_to_be32(fq_to_tag(fq));
	eq->fd = *fd;

	qm_eqcr_pvb_commit(&p->p, QM_EQCR_VERB_CMD_ENQUEUE);
out:
	local_irq_restore(irqflags);
	put_affine_portal();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qman_enqueue);

अटल पूर्णांक qm_modअगरy_cgr(काष्ठा qman_cgr *cgr, u32 flags,
			 काष्ठा qm_mcc_initcgr *opts)
अणु
	जोड़ qm_mc_command *mcc;
	जोड़ qm_mc_result *mcr;
	काष्ठा qman_portal *p = get_affine_portal();
	u8 verb = QM_MCC_VERB_MODIFYCGR;
	पूर्णांक ret = 0;

	mcc = qm_mc_start(&p->p);
	अगर (opts)
		mcc->initcgr = *opts;
	mcc->initcgr.cgid = cgr->cgrid;
	अगर (flags & QMAN_CGR_FLAG_USE_INIT)
		verb = QM_MCC_VERB_INITCGR;
	qm_mc_commit(&p->p, verb);
	अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == verb);
	अगर (mcr->result != QM_MCR_RESULT_OK)
		ret = -EIO;

out:
	put_affine_portal();
	वापस ret;
पूर्ण

#घोषणा PORTAL_IDX(n)	(n->config->channel - QM_CHANNEL_SWPORTAL0)

/* congestion state change notअगरication target update control */
अटल व्योम qm_cgr_cscn_targ_set(काष्ठा __qm_mc_cgr *cgr, पूर्णांक pi, u32 val)
अणु
	अगर (qman_ip_rev >= QMAN_REV30)
		cgr->cscn_targ_upd_ctrl = cpu_to_be16(pi |
					QM_CGR_TARG_UDP_CTRL_WRITE_BIT);
	अन्यथा
		cgr->cscn_targ = cpu_to_be32(val | QM_CGR_TARG_PORTAL(pi));
पूर्ण

अटल व्योम qm_cgr_cscn_targ_clear(काष्ठा __qm_mc_cgr *cgr, पूर्णांक pi, u32 val)
अणु
	अगर (qman_ip_rev >= QMAN_REV30)
		cgr->cscn_targ_upd_ctrl = cpu_to_be16(pi);
	अन्यथा
		cgr->cscn_targ = cpu_to_be32(val & ~QM_CGR_TARG_PORTAL(pi));
पूर्ण

अटल u8 qman_cgr_cpus[CGR_NUM];

व्योम qman_init_cgr_all(व्योम)
अणु
	काष्ठा qman_cgr cgr;
	पूर्णांक err_cnt = 0;

	क्रम (cgr.cgrid = 0; cgr.cgrid < CGR_NUM; cgr.cgrid++) अणु
		अगर (qm_modअगरy_cgr(&cgr, QMAN_CGR_FLAG_USE_INIT, शून्य))
			err_cnt++;
	पूर्ण

	अगर (err_cnt)
		pr_err("Warning: %d error%s while initialising CGR h/w\n",
		       err_cnt, (err_cnt > 1) ? "s" : "");
पूर्ण

पूर्णांक qman_create_cgr(काष्ठा qman_cgr *cgr, u32 flags,
		    काष्ठा qm_mcc_initcgr *opts)
अणु
	काष्ठा qm_mcr_querycgr cgr_state;
	पूर्णांक ret;
	काष्ठा qman_portal *p;

	/*
	 * We have to check that the provided CGRID is within the limits of the
	 * data-काष्ठाures, क्रम obvious reasons. However we'll let h/w take
	 * care of determining whether it's within the limits of what exists on
	 * the SoC.
	 */
	अगर (cgr->cgrid >= CGR_NUM)
		वापस -EINVAL;

	preempt_disable();
	p = get_affine_portal();
	qman_cgr_cpus[cgr->cgrid] = smp_processor_id();
	preempt_enable();

	cgr->chan = p->config->channel;
	spin_lock(&p->cgr_lock);

	अगर (opts) अणु
		काष्ठा qm_mcc_initcgr local_opts = *opts;

		ret = qman_query_cgr(cgr, &cgr_state);
		अगर (ret)
			जाओ out;

		qm_cgr_cscn_targ_set(&local_opts.cgr, PORTAL_IDX(p),
				     be32_to_cpu(cgr_state.cgr.cscn_targ));
		local_opts.we_mask |= cpu_to_be16(QM_CGR_WE_CSCN_TARG);

		/* send init अगर flags indicate so */
		अगर (flags & QMAN_CGR_FLAG_USE_INIT)
			ret = qm_modअगरy_cgr(cgr, QMAN_CGR_FLAG_USE_INIT,
					    &local_opts);
		अन्यथा
			ret = qm_modअगरy_cgr(cgr, 0, &local_opts);
		अगर (ret)
			जाओ out;
	पूर्ण

	list_add(&cgr->node, &p->cgr_cbs);

	/* Determine अगर newly added object requires its callback to be called */
	ret = qman_query_cgr(cgr, &cgr_state);
	अगर (ret) अणु
		/* we can't go back, so proceed and वापस success */
		dev_err(p->config->dev, "CGR HW state partially modified\n");
		ret = 0;
		जाओ out;
	पूर्ण
	अगर (cgr->cb && cgr_state.cgr.cscn_en &&
	    qman_cgrs_get(&p->cgrs[1], cgr->cgrid))
		cgr->cb(p, cgr, 1);
out:
	spin_unlock(&p->cgr_lock);
	put_affine_portal();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(qman_create_cgr);

पूर्णांक qman_delete_cgr(काष्ठा qman_cgr *cgr)
अणु
	अचिन्हित दीर्घ irqflags;
	काष्ठा qm_mcr_querycgr cgr_state;
	काष्ठा qm_mcc_initcgr local_opts;
	पूर्णांक ret = 0;
	काष्ठा qman_cgr *i;
	काष्ठा qman_portal *p = get_affine_portal();

	अगर (cgr->chan != p->config->channel) अणु
		/* attempt to delete from other portal than creator */
		dev_err(p->config->dev, "CGR not owned by current portal");
		dev_dbg(p->config->dev, " create 0x%x, delete 0x%x\n",
			cgr->chan, p->config->channel);

		ret = -EINVAL;
		जाओ put_portal;
	पूर्ण
	स_रखो(&local_opts, 0, माप(काष्ठा qm_mcc_initcgr));
	spin_lock_irqsave(&p->cgr_lock, irqflags);
	list_del(&cgr->node);
	/*
	 * If there are no other CGR objects क्रम this CGRID in the list,
	 * update CSCN_TARG accordingly
	 */
	list_क्रम_each_entry(i, &p->cgr_cbs, node)
		अगर (i->cgrid == cgr->cgrid && i->cb)
			जाओ release_lock;
	ret = qman_query_cgr(cgr, &cgr_state);
	अगर (ret)  अणु
		/* add back to the list */
		list_add(&cgr->node, &p->cgr_cbs);
		जाओ release_lock;
	पूर्ण

	local_opts.we_mask = cpu_to_be16(QM_CGR_WE_CSCN_TARG);
	qm_cgr_cscn_targ_clear(&local_opts.cgr, PORTAL_IDX(p),
			       be32_to_cpu(cgr_state.cgr.cscn_targ));

	ret = qm_modअगरy_cgr(cgr, 0, &local_opts);
	अगर (ret)
		/* add back to the list */
		list_add(&cgr->node, &p->cgr_cbs);
release_lock:
	spin_unlock_irqrestore(&p->cgr_lock, irqflags);
put_portal:
	put_affine_portal();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(qman_delete_cgr);

काष्ठा cgr_comp अणु
	काष्ठा qman_cgr *cgr;
	काष्ठा completion completion;
पूर्ण;

अटल व्योम qman_delete_cgr_smp_call(व्योम *p)
अणु
	qman_delete_cgr((काष्ठा qman_cgr *)p);
पूर्ण

व्योम qman_delete_cgr_safe(काष्ठा qman_cgr *cgr)
अणु
	preempt_disable();
	अगर (qman_cgr_cpus[cgr->cgrid] != smp_processor_id()) अणु
		smp_call_function_single(qman_cgr_cpus[cgr->cgrid],
					 qman_delete_cgr_smp_call, cgr, true);
		preempt_enable();
		वापस;
	पूर्ण

	qman_delete_cgr(cgr);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(qman_delete_cgr_safe);

/* Cleanup FQs */

अटल पूर्णांक _qm_mr_consume_and_match_verb(काष्ठा qm_portal *p, पूर्णांक v)
अणु
	स्थिर जोड़ qm_mr_entry *msg;
	पूर्णांक found = 0;

	qm_mr_pvb_update(p);
	msg = qm_mr_current(p);
	जबतक (msg) अणु
		अगर ((msg->verb & QM_MR_VERB_TYPE_MASK) == v)
			found = 1;
		qm_mr_next(p);
		qm_mr_cci_consume_to_current(p);
		qm_mr_pvb_update(p);
		msg = qm_mr_current(p);
	पूर्ण
	वापस found;
पूर्ण

अटल पूर्णांक _qm_dqrr_consume_and_match(काष्ठा qm_portal *p, u32 fqid, पूर्णांक s,
				      bool रुको)
अणु
	स्थिर काष्ठा qm_dqrr_entry *dqrr;
	पूर्णांक found = 0;

	करो अणु
		qm_dqrr_pvb_update(p);
		dqrr = qm_dqrr_current(p);
		अगर (!dqrr)
			cpu_relax();
	पूर्ण जबतक (रुको && !dqrr);

	जबतक (dqrr) अणु
		अगर (qm_fqid_get(dqrr) == fqid && (dqrr->stat & s))
			found = 1;
		qm_dqrr_cdc_consume_1ptr(p, dqrr, 0);
		qm_dqrr_pvb_update(p);
		qm_dqrr_next(p);
		dqrr = qm_dqrr_current(p);
	पूर्ण
	वापस found;
पूर्ण

#घोषणा qm_mr_drain(p, V) \
	_qm_mr_consume_and_match_verb(p, QM_MR_VERB_##V)

#घोषणा qm_dqrr_drain(p, f, S) \
	_qm_dqrr_consume_and_match(p, f, QM_DQRR_STAT_##S, false)

#घोषणा qm_dqrr_drain_रुको(p, f, S) \
	_qm_dqrr_consume_and_match(p, f, QM_DQRR_STAT_##S, true)

#घोषणा qm_dqrr_drain_nomatch(p) \
	_qm_dqrr_consume_and_match(p, 0, 0, false)

पूर्णांक qman_shutकरोwn_fq(u32 fqid)
अणु
	काष्ठा qman_portal *p, *channel_portal;
	काष्ठा device *dev;
	जोड़ qm_mc_command *mcc;
	जोड़ qm_mc_result *mcr;
	पूर्णांक orl_empty, drain = 0, ret = 0;
	u32 channel, res;
	u8 state;

	p = get_affine_portal();
	dev = p->config->dev;
	/* Determine the state of the FQID */
	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_QUERYFQ_NP);
	अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
		dev_err(dev, "QUERYFQ_NP timeout\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_QUERYFQ_NP);
	state = mcr->queryfq_np.state & QM_MCR_NP_STATE_MASK;
	अगर (state == QM_MCR_NP_STATE_OOS)
		जाओ out; /* Alपढ़ोy OOS, no need to करो anymore checks */

	/* Query which channel the FQ is using */
	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_QUERYFQ);
	अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
		dev_err(dev, "QUERYFQ timeout\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_QUERYFQ);
	/* Need to store these since the MCR माला_लो reused */
	channel = qm_fqd_get_chan(&mcr->queryfq.fqd);
	qm_fqd_get_wq(&mcr->queryfq.fqd);

	अगर (channel < qm_channel_pool1) अणु
		channel_portal = get_portal_क्रम_channel(channel);
		अगर (channel_portal == शून्य) अणु
			dev_err(dev, "Can't find portal for dedicated channel 0x%x\n",
				channel);
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		channel_portal = p;

	चयन (state) अणु
	हाल QM_MCR_NP_STATE_TEN_SCHED:
	हाल QM_MCR_NP_STATE_TRU_SCHED:
	हाल QM_MCR_NP_STATE_ACTIVE:
	हाल QM_MCR_NP_STATE_PARKED:
		orl_empty = 0;
		mcc = qm_mc_start(&channel_portal->p);
		qm_fqid_set(&mcc->fq, fqid);
		qm_mc_commit(&channel_portal->p, QM_MCC_VERB_ALTER_RETIRE);
		अगर (!qm_mc_result_समयout(&channel_portal->p, &mcr)) अणु
			dev_err(dev, "ALTER_RETIRE timeout\n");
			ret = -ETIMEDOUT;
			जाओ out;
		पूर्ण
		DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) ==
			    QM_MCR_VERB_ALTER_RETIRE);
		res = mcr->result; /* Make a copy as we reuse MCR below */

		अगर (res == QM_MCR_RESULT_OK)
			drain_mr_fqrni(&channel_portal->p);

		अगर (res == QM_MCR_RESULT_PENDING) अणु
			/*
			 * Need to रुको क्रम the FQRN in the message ring, which
			 * will only occur once the FQ has been drained.  In
			 * order क्रम the FQ to drain the portal needs to be set
			 * to dequeue from the channel the FQ is scheduled on
			 */
			पूर्णांक found_fqrn = 0;

			/* Flag that we need to drain FQ */
			drain = 1;

			अगर (channel >= qm_channel_pool1 &&
			    channel < qm_channel_pool1 + 15) अणु
				/* Pool channel, enable the bit in the portal */
			पूर्ण अन्यथा अगर (channel < qm_channel_pool1) अणु
				/* Dedicated channel */
			पूर्ण अन्यथा अणु
				dev_err(dev, "Can't recover FQ 0x%x, ch: 0x%x",
					fqid, channel);
				ret = -EBUSY;
				जाओ out;
			पूर्ण
			/* Set the sdqcr to drain this channel */
			अगर (channel < qm_channel_pool1)
				qm_dqrr_sdqcr_set(&channel_portal->p,
						  QM_SDQCR_TYPE_ACTIVE |
						  QM_SDQCR_CHANNELS_DEDICATED);
			अन्यथा
				qm_dqrr_sdqcr_set(&channel_portal->p,
						  QM_SDQCR_TYPE_ACTIVE |
						  QM_SDQCR_CHANNELS_POOL_CONV
						  (channel));
			करो अणु
				/* Keep draining DQRR जबतक checking the MR*/
				qm_dqrr_drain_nomatch(&channel_portal->p);
				/* Process message ring too */
				found_fqrn = qm_mr_drain(&channel_portal->p,
							 FQRN);
				cpu_relax();
			पूर्ण जबतक (!found_fqrn);
			/* Restore SDQCR */
			qm_dqrr_sdqcr_set(&channel_portal->p,
					  channel_portal->sdqcr);

		पूर्ण
		अगर (res != QM_MCR_RESULT_OK &&
		    res != QM_MCR_RESULT_PENDING) अणु
			dev_err(dev, "retire_fq failed: FQ 0x%x, res=0x%x\n",
				fqid, res);
			ret = -EIO;
			जाओ out;
		पूर्ण
		अगर (!(mcr->alterfq.fqs & QM_MCR_FQS_ORLPRESENT)) अणु
			/*
			 * ORL had no entries, no need to रुको until the
			 * ERNs come in
			 */
			orl_empty = 1;
		पूर्ण
		/*
		 * Retirement succeeded, check to see अगर FQ needs
		 * to be drained
		 */
		अगर (drain || mcr->alterfq.fqs & QM_MCR_FQS_NOTEMPTY) अणु
			/* FQ is Not Empty, drain using अस्थिर DQ commands */
			करो अणु
				u32 vdqcr = fqid | QM_VDQCR_NUMFRAMES_SET(3);

				qm_dqrr_vdqcr_set(&p->p, vdqcr);
				/*
				 * Wait क्रम a dequeue and process the dequeues,
				 * making sure to empty the ring completely
				 */
			पूर्ण जबतक (!qm_dqrr_drain_रुको(&p->p, fqid, FQ_EMPTY));
		पूर्ण

		जबतक (!orl_empty) अणु
			/* Wait क्रम the ORL to have been completely drained */
			orl_empty = qm_mr_drain(&p->p, FQRL);
			cpu_relax();
		पूर्ण
		mcc = qm_mc_start(&p->p);
		qm_fqid_set(&mcc->fq, fqid);
		qm_mc_commit(&p->p, QM_MCC_VERB_ALTER_OOS);
		अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
			ret = -ETIMEDOUT;
			जाओ out;
		पूर्ण

		DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) ==
			    QM_MCR_VERB_ALTER_OOS);
		अगर (mcr->result != QM_MCR_RESULT_OK) अणु
			dev_err(dev, "OOS after drain fail: FQ 0x%x (0x%x)\n",
				fqid, mcr->result);
			ret = -EIO;
			जाओ out;
		पूर्ण
		अवरोध;

	हाल QM_MCR_NP_STATE_RETIRED:
		/* Send OOS Command */
		mcc = qm_mc_start(&p->p);
		qm_fqid_set(&mcc->fq, fqid);
		qm_mc_commit(&p->p, QM_MCC_VERB_ALTER_OOS);
		अगर (!qm_mc_result_समयout(&p->p, &mcr)) अणु
			ret = -ETIMEDOUT;
			जाओ out;
		पूर्ण

		DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) ==
			    QM_MCR_VERB_ALTER_OOS);
		अगर (mcr->result != QM_MCR_RESULT_OK) अणु
			dev_err(dev, "OOS fail: FQ 0x%x (0x%x)\n",
				fqid, mcr->result);
			ret = -EIO;
			जाओ out;
		पूर्ण
		अवरोध;

	हाल QM_MCR_NP_STATE_OOS:
		/*  Done */
		अवरोध;

	शेष:
		ret = -EIO;
	पूर्ण

out:
	put_affine_portal();
	वापस ret;
पूर्ण

स्थिर काष्ठा qm_portal_config *qman_get_qm_portal_config(
						काष्ठा qman_portal *portal)
अणु
	वापस portal->config;
पूर्ण
EXPORT_SYMBOL(qman_get_qm_portal_config);

काष्ठा gen_pool *qm_fqalloc; /* FQID allocator */
काष्ठा gen_pool *qm_qpalloc; /* pool-channel allocator */
काष्ठा gen_pool *qm_cgralloc; /* CGR ID allocator */

अटल पूर्णांक qman_alloc_range(काष्ठा gen_pool *p, u32 *result, u32 cnt)
अणु
	अचिन्हित दीर्घ addr;

	अगर (!p)
		वापस -ENODEV;

	addr = gen_pool_alloc(p, cnt);
	अगर (!addr)
		वापस -ENOMEM;

	*result = addr & ~DPAA_GENALLOC_OFF;

	वापस 0;
पूर्ण

पूर्णांक qman_alloc_fqid_range(u32 *result, u32 count)
अणु
	वापस qman_alloc_range(qm_fqalloc, result, count);
पूर्ण
EXPORT_SYMBOL(qman_alloc_fqid_range);

पूर्णांक qman_alloc_pool_range(u32 *result, u32 count)
अणु
	वापस qman_alloc_range(qm_qpalloc, result, count);
पूर्ण
EXPORT_SYMBOL(qman_alloc_pool_range);

पूर्णांक qman_alloc_cgrid_range(u32 *result, u32 count)
अणु
	वापस qman_alloc_range(qm_cgralloc, result, count);
पूर्ण
EXPORT_SYMBOL(qman_alloc_cgrid_range);

पूर्णांक qman_release_fqid(u32 fqid)
अणु
	पूर्णांक ret = qman_shutकरोwn_fq(fqid);

	अगर (ret) अणु
		pr_debug("FQID %d leaked\n", fqid);
		वापस ret;
	पूर्ण

	gen_pool_मुक्त(qm_fqalloc, fqid | DPAA_GENALLOC_OFF, 1);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qman_release_fqid);

अटल पूर्णांक qpool_cleanup(u32 qp)
अणु
	/*
	 * We query all FQDs starting from
	 * FQID 1 until we get an "invalid FQID" error, looking क्रम non-OOS FQDs
	 * whose destination channel is the pool-channel being released.
	 * When a non-OOS FQD is found we attempt to clean it up
	 */
	काष्ठा qman_fq fq = अणु
		.fqid = QM_FQID_RANGE_START
	पूर्ण;
	पूर्णांक err;

	करो अणु
		काष्ठा qm_mcr_queryfq_np np;

		err = qman_query_fq_np(&fq, &np);
		अगर (err == -दुस्फल)
			/* FQID range exceeded, found no problems */
			वापस 0;
		अन्यथा अगर (WARN_ON(err))
			वापस err;

		अगर ((np.state & QM_MCR_NP_STATE_MASK) != QM_MCR_NP_STATE_OOS) अणु
			काष्ठा qm_fqd fqd;

			err = qman_query_fq(&fq, &fqd);
			अगर (WARN_ON(err))
				वापस err;
			अगर (qm_fqd_get_chan(&fqd) == qp) अणु
				/* The channel is the FQ's target, clean it */
				err = qman_shutकरोwn_fq(fq.fqid);
				अगर (err)
					/*
					 * Couldn't shut करोwn the FQ
					 * so the pool must be leaked
					 */
					वापस err;
			पूर्ण
		पूर्ण
		/* Move to the next FQID */
		fq.fqid++;
	पूर्ण जबतक (1);
पूर्ण

पूर्णांक qman_release_pool(u32 qp)
अणु
	पूर्णांक ret;

	ret = qpool_cleanup(qp);
	अगर (ret) अणु
		pr_debug("CHID %d leaked\n", qp);
		वापस ret;
	पूर्ण

	gen_pool_मुक्त(qm_qpalloc, qp | DPAA_GENALLOC_OFF, 1);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qman_release_pool);

अटल पूर्णांक cgr_cleanup(u32 cgrid)
अणु
	/*
	 * query all FQDs starting from FQID 1 until we get an "invalid FQID"
	 * error, looking क्रम non-OOS FQDs whose CGR is the CGR being released
	 */
	काष्ठा qman_fq fq = अणु
		.fqid = QM_FQID_RANGE_START
	पूर्ण;
	पूर्णांक err;

	करो अणु
		काष्ठा qm_mcr_queryfq_np np;

		err = qman_query_fq_np(&fq, &np);
		अगर (err == -दुस्फल)
			/* FQID range exceeded, found no problems */
			वापस 0;
		अन्यथा अगर (WARN_ON(err))
			वापस err;

		अगर ((np.state & QM_MCR_NP_STATE_MASK) != QM_MCR_NP_STATE_OOS) अणु
			काष्ठा qm_fqd fqd;

			err = qman_query_fq(&fq, &fqd);
			अगर (WARN_ON(err))
				वापस err;
			अगर (be16_to_cpu(fqd.fq_ctrl) & QM_FQCTRL_CGE &&
			    fqd.cgid == cgrid) अणु
				pr_err("CRGID 0x%x is being used by FQID 0x%x, CGR will be leaked\n",
				       cgrid, fq.fqid);
				वापस -EIO;
			पूर्ण
		पूर्ण
		/* Move to the next FQID */
		fq.fqid++;
	पूर्ण जबतक (1);
पूर्ण

पूर्णांक qman_release_cgrid(u32 cgrid)
अणु
	पूर्णांक ret;

	ret = cgr_cleanup(cgrid);
	अगर (ret) अणु
		pr_debug("CGRID %d leaked\n", cgrid);
		वापस ret;
	पूर्ण

	gen_pool_मुक्त(qm_cgralloc, cgrid | DPAA_GENALLOC_OFF, 1);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qman_release_cgrid);
