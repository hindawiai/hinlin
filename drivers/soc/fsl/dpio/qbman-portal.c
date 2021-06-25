<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright (C) 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 *
 */

#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <soc/fsl/dpaa2-global.h>

#समावेश "qbman-portal.h"

/* All QBMan command and result काष्ठाures use this "valid bit" encoding */
#घोषणा QB_VALID_BIT ((u32)0x80)

/* QBMan portal management command codes */
#घोषणा QBMAN_MC_ACQUIRE       0x30
#घोषणा QBMAN_WQCHAN_CONFIGURE 0x46

/* CINH रेजिस्टर offsets */
#घोषणा QBMAN_CINH_SWP_EQCR_PI      0x800
#घोषणा QBMAN_CINH_SWP_EQCR_CI	    0x840
#घोषणा QBMAN_CINH_SWP_EQAR    0x8c0
#घोषणा QBMAN_CINH_SWP_CR_RT        0x900
#घोषणा QBMAN_CINH_SWP_VDQCR_RT     0x940
#घोषणा QBMAN_CINH_SWP_EQCR_AM_RT   0x980
#घोषणा QBMAN_CINH_SWP_RCR_AM_RT    0x9c0
#घोषणा QBMAN_CINH_SWP_DQPI    0xa00
#घोषणा QBMAN_CINH_SWP_DCAP    0xac0
#घोषणा QBMAN_CINH_SWP_SDQCR   0xb00
#घोषणा QBMAN_CINH_SWP_EQCR_AM_RT2  0xb40
#घोषणा QBMAN_CINH_SWP_RCR_PI       0xc00
#घोषणा QBMAN_CINH_SWP_RAR     0xcc0
#घोषणा QBMAN_CINH_SWP_ISR     0xe00
#घोषणा QBMAN_CINH_SWP_IER     0xe40
#घोषणा QBMAN_CINH_SWP_ISDR    0xe80
#घोषणा QBMAN_CINH_SWP_IIR     0xec0

/* CENA रेजिस्टर offsets */
#घोषणा QBMAN_CENA_SWP_EQCR(n) (0x000 + ((u32)(n) << 6))
#घोषणा QBMAN_CENA_SWP_DQRR(n) (0x200 + ((u32)(n) << 6))
#घोषणा QBMAN_CENA_SWP_RCR(n)  (0x400 + ((u32)(n) << 6))
#घोषणा QBMAN_CENA_SWP_CR      0x600
#घोषणा QBMAN_CENA_SWP_RR(vb)  (0x700 + ((u32)(vb) >> 1))
#घोषणा QBMAN_CENA_SWP_VDQCR   0x780
#घोषणा QBMAN_CENA_SWP_EQCR_CI 0x840
#घोषणा QBMAN_CENA_SWP_EQCR_CI_MEMBACK 0x1840

/* CENA रेजिस्टर offsets in memory-backed mode */
#घोषणा QBMAN_CENA_SWP_DQRR_MEM(n)  (0x800 + ((u32)(n) << 6))
#घोषणा QBMAN_CENA_SWP_RCR_MEM(n)   (0x1400 + ((u32)(n) << 6))
#घोषणा QBMAN_CENA_SWP_CR_MEM       0x1600
#घोषणा QBMAN_CENA_SWP_RR_MEM       0x1680
#घोषणा QBMAN_CENA_SWP_VDQCR_MEM    0x1780

/* Reverse mapping of QBMAN_CENA_SWP_DQRR() */
#घोषणा QBMAN_IDX_FROM_DQRR(p) (((अचिन्हित दीर्घ)(p) & 0x1ff) >> 6)

/* Define token used to determine अगर response written to memory is valid */
#घोषणा QMAN_DQ_TOKEN_VALID 1

/* SDQCR attribute codes */
#घोषणा QB_SDQCR_FC_SHIFT   29
#घोषणा QB_SDQCR_FC_MASK    0x1
#घोषणा QB_SDQCR_DCT_SHIFT  24
#घोषणा QB_SDQCR_DCT_MASK   0x3
#घोषणा QB_SDQCR_TOK_SHIFT  16
#घोषणा QB_SDQCR_TOK_MASK   0xff
#घोषणा QB_SDQCR_SRC_SHIFT  0
#घोषणा QB_SDQCR_SRC_MASK   0xffff

/* opaque token क्रम अटल dequeues */
#घोषणा QMAN_SDQCR_TOKEN    0xbb

#घोषणा QBMAN_EQCR_DCA_IDXMASK          0x0f
#घोषणा QBMAN_ENQUEUE_FLAG_DCA          (1ULL << 31)

#घोषणा EQ_DESC_SIZE_WITHOUT_FD 29
#घोषणा EQ_DESC_SIZE_FD_START 32

क्रमागत qbman_sdqcr_dct अणु
	qbman_sdqcr_dct_null = 0,
	qbman_sdqcr_dct_prio_ics,
	qbman_sdqcr_dct_active_ics,
	qbman_sdqcr_dct_active
पूर्ण;

क्रमागत qbman_sdqcr_fc अणु
	qbman_sdqcr_fc_one = 0,
	qbman_sdqcr_fc_up_to_3 = 1
पूर्ण;

/* Internal Function declaration */
अटल पूर्णांक qbman_swp_enqueue_direct(काष्ठा qbman_swp *s,
				    स्थिर काष्ठा qbman_eq_desc *d,
				    स्थिर काष्ठा dpaa2_fd *fd);
अटल पूर्णांक qbman_swp_enqueue_mem_back(काष्ठा qbman_swp *s,
				      स्थिर काष्ठा qbman_eq_desc *d,
				      स्थिर काष्ठा dpaa2_fd *fd);
अटल पूर्णांक qbman_swp_enqueue_multiple_direct(काष्ठा qbman_swp *s,
					     स्थिर काष्ठा qbman_eq_desc *d,
					     स्थिर काष्ठा dpaa2_fd *fd,
					     uपूर्णांक32_t *flags,
					     पूर्णांक num_frames);
अटल पूर्णांक qbman_swp_enqueue_multiple_mem_back(काष्ठा qbman_swp *s,
					       स्थिर काष्ठा qbman_eq_desc *d,
					       स्थिर काष्ठा dpaa2_fd *fd,
					       uपूर्णांक32_t *flags,
					       पूर्णांक num_frames);
अटल पूर्णांक
qbman_swp_enqueue_multiple_desc_direct(काष्ठा qbman_swp *s,
				       स्थिर काष्ठा qbman_eq_desc *d,
				       स्थिर काष्ठा dpaa2_fd *fd,
				       पूर्णांक num_frames);
अटल
पूर्णांक qbman_swp_enqueue_multiple_desc_mem_back(काष्ठा qbman_swp *s,
					     स्थिर काष्ठा qbman_eq_desc *d,
					     स्थिर काष्ठा dpaa2_fd *fd,
					     पूर्णांक num_frames);
अटल पूर्णांक qbman_swp_pull_direct(काष्ठा qbman_swp *s,
				 काष्ठा qbman_pull_desc *d);
अटल पूर्णांक qbman_swp_pull_mem_back(काष्ठा qbman_swp *s,
				   काष्ठा qbman_pull_desc *d);

स्थिर काष्ठा dpaa2_dq *qbman_swp_dqrr_next_direct(काष्ठा qbman_swp *s);
स्थिर काष्ठा dpaa2_dq *qbman_swp_dqrr_next_mem_back(काष्ठा qbman_swp *s);

अटल पूर्णांक qbman_swp_release_direct(काष्ठा qbman_swp *s,
				    स्थिर काष्ठा qbman_release_desc *d,
				    स्थिर u64 *buffers,
				    अचिन्हित पूर्णांक num_buffers);
अटल पूर्णांक qbman_swp_release_mem_back(काष्ठा qbman_swp *s,
				      स्थिर काष्ठा qbman_release_desc *d,
				      स्थिर u64 *buffers,
				      अचिन्हित पूर्णांक num_buffers);

/* Function poपूर्णांकers */
पूर्णांक (*qbman_swp_enqueue_ptr)(काष्ठा qbman_swp *s,
			     स्थिर काष्ठा qbman_eq_desc *d,
			     स्थिर काष्ठा dpaa2_fd *fd)
	= qbman_swp_enqueue_direct;

पूर्णांक (*qbman_swp_enqueue_multiple_ptr)(काष्ठा qbman_swp *s,
				      स्थिर काष्ठा qbman_eq_desc *d,
				      स्थिर काष्ठा dpaa2_fd *fd,
				      uपूर्णांक32_t *flags,
					     पूर्णांक num_frames)
	= qbman_swp_enqueue_multiple_direct;

पूर्णांक
(*qbman_swp_enqueue_multiple_desc_ptr)(काष्ठा qbman_swp *s,
				       स्थिर काष्ठा qbman_eq_desc *d,
				       स्थिर काष्ठा dpaa2_fd *fd,
				       पूर्णांक num_frames)
	= qbman_swp_enqueue_multiple_desc_direct;

पूर्णांक (*qbman_swp_pull_ptr)(काष्ठा qbman_swp *s, काष्ठा qbman_pull_desc *d)
			= qbman_swp_pull_direct;

स्थिर काष्ठा dpaa2_dq *(*qbman_swp_dqrr_next_ptr)(काष्ठा qbman_swp *s)
			= qbman_swp_dqrr_next_direct;

पूर्णांक (*qbman_swp_release_ptr)(काष्ठा qbman_swp *s,
			     स्थिर काष्ठा qbman_release_desc *d,
			     स्थिर u64 *buffers,
			     अचिन्हित पूर्णांक num_buffers)
			= qbman_swp_release_direct;

/* Portal Access */

अटल अंतरभूत u32 qbman_पढ़ो_रेजिस्टर(काष्ठा qbman_swp *p, u32 offset)
अणु
	वापस पढ़ोl_relaxed(p->addr_cinh + offset);
पूर्ण

अटल अंतरभूत व्योम qbman_ग_लिखो_रेजिस्टर(काष्ठा qbman_swp *p, u32 offset,
					u32 value)
अणु
	ग_लिखोl_relaxed(value, p->addr_cinh + offset);
पूर्ण

अटल अंतरभूत व्योम *qbman_get_cmd(काष्ठा qbman_swp *p, u32 offset)
अणु
	वापस p->addr_cena + offset;
पूर्ण

#घोषणा QBMAN_CINH_SWP_CFG   0xd00

#घोषणा SWP_CFG_DQRR_MF_SHIFT 20
#घोषणा SWP_CFG_EST_SHIFT     16
#घोषणा SWP_CFG_CPBS_SHIFT    15
#घोषणा SWP_CFG_WN_SHIFT      14
#घोषणा SWP_CFG_RPM_SHIFT     12
#घोषणा SWP_CFG_DCM_SHIFT     10
#घोषणा SWP_CFG_EPM_SHIFT     8
#घोषणा SWP_CFG_VPM_SHIFT     7
#घोषणा SWP_CFG_CPM_SHIFT     6
#घोषणा SWP_CFG_SD_SHIFT      5
#घोषणा SWP_CFG_SP_SHIFT      4
#घोषणा SWP_CFG_SE_SHIFT      3
#घोषणा SWP_CFG_DP_SHIFT      2
#घोषणा SWP_CFG_DE_SHIFT      1
#घोषणा SWP_CFG_EP_SHIFT      0

अटल अंतरभूत u32 qbman_set_swp_cfg(u8 max_fill, u8 wn,	u8 est, u8 rpm, u8 dcm,
				    u8 epm, पूर्णांक sd, पूर्णांक sp, पूर्णांक se,
				    पूर्णांक dp, पूर्णांक de, पूर्णांक ep)
अणु
	वापस (max_fill << SWP_CFG_DQRR_MF_SHIFT |
		est << SWP_CFG_EST_SHIFT |
		wn << SWP_CFG_WN_SHIFT |
		rpm << SWP_CFG_RPM_SHIFT |
		dcm << SWP_CFG_DCM_SHIFT |
		epm << SWP_CFG_EPM_SHIFT |
		sd << SWP_CFG_SD_SHIFT |
		sp << SWP_CFG_SP_SHIFT |
		se << SWP_CFG_SE_SHIFT |
		dp << SWP_CFG_DP_SHIFT |
		de << SWP_CFG_DE_SHIFT |
		ep << SWP_CFG_EP_SHIFT);
पूर्ण

#घोषणा QMAN_RT_MODE	   0x00000100

अटल अंतरभूत u8 qm_cyc_dअगरf(u8 ringsize, u8 first, u8 last)
अणु
	/* 'first' is included, 'last' is excluded */
	अगर (first <= last)
		वापस last - first;
	अन्यथा
		वापस (2 * ringsize) - (first - last);
पूर्ण

/**
 * qbman_swp_init() - Create a functional object representing the given
 *                    QBMan portal descriptor.
 * @d: the given qbman swp descriptor
 *
 * Return qbman_swp portal क्रम success, शून्य अगर the object cannot
 * be created.
 */
काष्ठा qbman_swp *qbman_swp_init(स्थिर काष्ठा qbman_swp_desc *d)
अणु
	काष्ठा qbman_swp *p = kzalloc(माप(*p), GFP_KERNEL);
	u32 reg;
	u32 mask_size;
	u32 eqcr_pi;

	अगर (!p)
		वापस शून्य;

	spin_lock_init(&p->access_spinlock);

	p->desc = d;
	p->mc.valid_bit = QB_VALID_BIT;
	p->sdq = 0;
	p->sdq |= qbman_sdqcr_dct_prio_ics << QB_SDQCR_DCT_SHIFT;
	p->sdq |= qbman_sdqcr_fc_up_to_3 << QB_SDQCR_FC_SHIFT;
	p->sdq |= QMAN_SDQCR_TOKEN << QB_SDQCR_TOK_SHIFT;
	अगर ((p->desc->qman_version & QMAN_REV_MASK) >= QMAN_REV_5000)
		p->mr.valid_bit = QB_VALID_BIT;

	atomic_set(&p->vdq.available, 1);
	p->vdq.valid_bit = QB_VALID_BIT;
	p->dqrr.next_idx = 0;
	p->dqrr.valid_bit = QB_VALID_BIT;

	अगर ((p->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_4100) अणु
		p->dqrr.dqrr_size = 4;
		p->dqrr.reset_bug = 1;
	पूर्ण अन्यथा अणु
		p->dqrr.dqrr_size = 8;
		p->dqrr.reset_bug = 0;
	पूर्ण

	p->addr_cena = d->cena_bar;
	p->addr_cinh = d->cinh_bar;

	अगर ((p->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_5000) अणु

		reg = qbman_set_swp_cfg(p->dqrr.dqrr_size,
			1, /* Writes Non-cacheable */
			0, /* EQCR_CI stashing threshold */
			3, /* RPM: RCR in array mode */
			2, /* DCM: Discrete consumption ack */
			2, /* EPM: EQCR in ring mode */
			1, /* mem stashing drop enable enable */
			1, /* mem stashing priority enable */
			1, /* mem stashing enable */
			1, /* dequeue stashing priority enable */
			0, /* dequeue stashing enable enable */
			0); /* EQCR_CI stashing priority enable */
	पूर्ण अन्यथा अणु
		स_रखो(p->addr_cena, 0, 64 * 1024);
		reg = qbman_set_swp_cfg(p->dqrr.dqrr_size,
			1, /* Writes Non-cacheable */
			1, /* EQCR_CI stashing threshold */
			3, /* RPM: RCR in array mode */
			2, /* DCM: Discrete consumption ack */
			0, /* EPM: EQCR in ring mode */
			1, /* mem stashing drop enable */
			1, /* mem stashing priority enable */
			1, /* mem stashing enable */
			1, /* dequeue stashing priority enable */
			0, /* dequeue stashing enable */
			0); /* EQCR_CI stashing priority enable */
		reg |= 1 << SWP_CFG_CPBS_SHIFT | /* memory-backed mode */
		       1 << SWP_CFG_VPM_SHIFT |  /* VDQCR पढ़ो triggered mode */
		       1 << SWP_CFG_CPM_SHIFT;   /* CR पढ़ो triggered mode */
	पूर्ण

	qbman_ग_लिखो_रेजिस्टर(p, QBMAN_CINH_SWP_CFG, reg);
	reg = qbman_पढ़ो_रेजिस्टर(p, QBMAN_CINH_SWP_CFG);
	अगर (!reg) अणु
		pr_err("qbman: the portal is not enabled!\n");
		kमुक्त(p);
		वापस शून्य;
	पूर्ण

	अगर ((p->desc->qman_version & QMAN_REV_MASK) >= QMAN_REV_5000) अणु
		qbman_ग_लिखो_रेजिस्टर(p, QBMAN_CINH_SWP_EQCR_PI, QMAN_RT_MODE);
		qbman_ग_लिखो_रेजिस्टर(p, QBMAN_CINH_SWP_RCR_PI, QMAN_RT_MODE);
	पूर्ण
	/*
	 * SDQCR needs to be initialized to 0 when no channels are
	 * being dequeued from or अन्यथा the QMan HW will indicate an
	 * error.  The values that were calculated above will be
	 * applied when dequeues from a specअगरic channel are enabled.
	 */
	qbman_ग_लिखो_रेजिस्टर(p, QBMAN_CINH_SWP_SDQCR, 0);

	p->eqcr.pi_ring_size = 8;
	अगर ((p->desc->qman_version & QMAN_REV_MASK) >= QMAN_REV_5000) अणु
		p->eqcr.pi_ring_size = 32;
		qbman_swp_enqueue_ptr =
			qbman_swp_enqueue_mem_back;
		qbman_swp_enqueue_multiple_ptr =
			qbman_swp_enqueue_multiple_mem_back;
		qbman_swp_enqueue_multiple_desc_ptr =
			qbman_swp_enqueue_multiple_desc_mem_back;
		qbman_swp_pull_ptr = qbman_swp_pull_mem_back;
		qbman_swp_dqrr_next_ptr = qbman_swp_dqrr_next_mem_back;
		qbman_swp_release_ptr = qbman_swp_release_mem_back;
	पूर्ण

	क्रम (mask_size = p->eqcr.pi_ring_size; mask_size > 0; mask_size >>= 1)
		p->eqcr.pi_ci_mask = (p->eqcr.pi_ci_mask << 1) + 1;
	eqcr_pi = qbman_पढ़ो_रेजिस्टर(p, QBMAN_CINH_SWP_EQCR_PI);
	p->eqcr.pi = eqcr_pi & p->eqcr.pi_ci_mask;
	p->eqcr.pi_vb = eqcr_pi & QB_VALID_BIT;
	p->eqcr.ci = qbman_पढ़ो_रेजिस्टर(p, QBMAN_CINH_SWP_EQCR_CI)
			& p->eqcr.pi_ci_mask;
	p->eqcr.available = p->eqcr.pi_ring_size;

	वापस p;
पूर्ण

/**
 * qbman_swp_finish() - Create and destroy a functional object representing
 *                      the given QBMan portal descriptor.
 * @p: the qbman_swp object to be destroyed
 */
व्योम qbman_swp_finish(काष्ठा qbman_swp *p)
अणु
	kमुक्त(p);
पूर्ण

/**
 * qbman_swp_पूर्णांकerrupt_पढ़ो_status()
 * @p: the given software portal
 *
 * Return the value in the SWP_ISR रेजिस्टर.
 */
u32 qbman_swp_पूर्णांकerrupt_पढ़ो_status(काष्ठा qbman_swp *p)
अणु
	वापस qbman_पढ़ो_रेजिस्टर(p, QBMAN_CINH_SWP_ISR);
पूर्ण

/**
 * qbman_swp_पूर्णांकerrupt_clear_status()
 * @p: the given software portal
 * @mask: The mask to clear in SWP_ISR रेजिस्टर
 */
व्योम qbman_swp_पूर्णांकerrupt_clear_status(काष्ठा qbman_swp *p, u32 mask)
अणु
	qbman_ग_लिखो_रेजिस्टर(p, QBMAN_CINH_SWP_ISR, mask);
पूर्ण

/**
 * qbman_swp_पूर्णांकerrupt_get_trigger() - पढ़ो पूर्णांकerrupt enable रेजिस्टर
 * @p: the given software portal
 *
 * Return the value in the SWP_IER रेजिस्टर.
 */
u32 qbman_swp_पूर्णांकerrupt_get_trigger(काष्ठा qbman_swp *p)
अणु
	वापस qbman_पढ़ो_रेजिस्टर(p, QBMAN_CINH_SWP_IER);
पूर्ण

/**
 * qbman_swp_पूर्णांकerrupt_set_trigger() - enable पूर्णांकerrupts क्रम a swp
 * @p: the given software portal
 * @mask: The mask of bits to enable in SWP_IER
 */
व्योम qbman_swp_पूर्णांकerrupt_set_trigger(काष्ठा qbman_swp *p, u32 mask)
अणु
	qbman_ग_लिखो_रेजिस्टर(p, QBMAN_CINH_SWP_IER, mask);
पूर्ण

/**
 * qbman_swp_पूर्णांकerrupt_get_inhibit() - पढ़ो पूर्णांकerrupt mask रेजिस्टर
 * @p: the given software portal object
 *
 * Return the value in the SWP_IIR रेजिस्टर.
 */
पूर्णांक qbman_swp_पूर्णांकerrupt_get_inhibit(काष्ठा qbman_swp *p)
अणु
	वापस qbman_पढ़ो_रेजिस्टर(p, QBMAN_CINH_SWP_IIR);
पूर्ण

/**
 * qbman_swp_पूर्णांकerrupt_set_inhibit() - ग_लिखो पूर्णांकerrupt mask रेजिस्टर
 * @p: the given software portal object
 * @inhibit: whether to inhibit the IRQs
 */
व्योम qbman_swp_पूर्णांकerrupt_set_inhibit(काष्ठा qbman_swp *p, पूर्णांक inhibit)
अणु
	qbman_ग_लिखो_रेजिस्टर(p, QBMAN_CINH_SWP_IIR, inhibit ? 0xffffffff : 0);
पूर्ण

/*
 * Dअगरferent management commands all use this common base layer of code to issue
 * commands and poll क्रम results.
 */

/*
 * Returns a poपूर्णांकer to where the caller should fill in their management command
 * (caller should ignore the verb byte)
 */
व्योम *qbman_swp_mc_start(काष्ठा qbman_swp *p)
अणु
	अगर ((p->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_5000)
		वापस qbman_get_cmd(p, QBMAN_CENA_SWP_CR);
	अन्यथा
		वापस qbman_get_cmd(p, QBMAN_CENA_SWP_CR_MEM);
पूर्ण

/*
 * Commits merges in the caller-supplied command verb (which should not include
 * the valid-bit) and submits the command to hardware
 */
व्योम qbman_swp_mc_submit(काष्ठा qbman_swp *p, व्योम *cmd, u8 cmd_verb)
अणु
	u8 *v = cmd;

	अगर ((p->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_5000) अणु
		dma_wmb();
		*v = cmd_verb | p->mc.valid_bit;
	पूर्ण अन्यथा अणु
		*v = cmd_verb | p->mc.valid_bit;
		dma_wmb();
		qbman_ग_लिखो_रेजिस्टर(p, QBMAN_CINH_SWP_CR_RT, QMAN_RT_MODE);
	पूर्ण
पूर्ण

/*
 * Checks क्रम a completed response (वापसs non-शून्य अगर only अगर the response
 * is complete).
 */
व्योम *qbman_swp_mc_result(काष्ठा qbman_swp *p)
अणु
	u32 *ret, verb;

	अगर ((p->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_5000) अणु
		ret = qbman_get_cmd(p, QBMAN_CENA_SWP_RR(p->mc.valid_bit));
		/* Remove the valid-bit - command completed अगर the rest
		 * is non-zero.
		 */
		verb = ret[0] & ~QB_VALID_BIT;
		अगर (!verb)
			वापस शून्य;
		p->mc.valid_bit ^= QB_VALID_BIT;
	पूर्ण अन्यथा अणु
		ret = qbman_get_cmd(p, QBMAN_CENA_SWP_RR_MEM);
		/* Command completed अगर the valid bit is toggled */
		अगर (p->mr.valid_bit != (ret[0] & QB_VALID_BIT))
			वापस शून्य;
		/* Command completed अगर the rest is non-zero */
		verb = ret[0] & ~QB_VALID_BIT;
		अगर (!verb)
			वापस शून्य;
		p->mr.valid_bit ^= QB_VALID_BIT;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा QB_ENQUEUE_CMD_OPTIONS_SHIFT    0
क्रमागत qb_enqueue_commands अणु
	enqueue_empty = 0,
	enqueue_response_always = 1,
	enqueue_rejects_to_fq = 2
पूर्ण;

#घोषणा QB_ENQUEUE_CMD_ORP_ENABLE_SHIFT      2
#घोषणा QB_ENQUEUE_CMD_IRQ_ON_DISPATCH_SHIFT 3
#घोषणा QB_ENQUEUE_CMD_TARGET_TYPE_SHIFT     4
#घोषणा QB_ENQUEUE_CMD_DCA_EN_SHIFT          7

/*
 * qbman_eq_desc_clear() - Clear the contents of a descriptor to
 *                         शेष/starting state.
 */
व्योम qbman_eq_desc_clear(काष्ठा qbman_eq_desc *d)
अणु
	स_रखो(d, 0, माप(*d));
पूर्ण

/**
 * qbman_eq_desc_set_no_orp() - Set enqueue descriptor without orp
 * @d:                the enqueue descriptor.
 * @respond_success:  1 = enqueue with response always; 0 = enqueue with
 *                    rejections वापसed on a FQ.
 */
व्योम qbman_eq_desc_set_no_orp(काष्ठा qbman_eq_desc *d, पूर्णांक respond_success)
अणु
	d->verb &= ~(1 << QB_ENQUEUE_CMD_ORP_ENABLE_SHIFT);
	अगर (respond_success)
		d->verb |= enqueue_response_always;
	अन्यथा
		d->verb |= enqueue_rejects_to_fq;
पूर्ण

/*
 * Exactly one of the following descriptor "targets" should be set. (Calling any
 * one of these will replace the effect of any prior call to one of these.)
 *   -enqueue to a frame queue
 *   -enqueue to a queuing destination
 */

/**
 * qbman_eq_desc_set_fq() - set the FQ क्रम the enqueue command
 * @d:    the enqueue descriptor
 * @fqid: the id of the frame queue to be enqueued
 */
व्योम qbman_eq_desc_set_fq(काष्ठा qbman_eq_desc *d, u32 fqid)
अणु
	d->verb &= ~(1 << QB_ENQUEUE_CMD_TARGET_TYPE_SHIFT);
	d->tgtid = cpu_to_le32(fqid);
पूर्ण

/**
 * qbman_eq_desc_set_qd() - Set Queuing Destination क्रम the enqueue command
 * @d:       the enqueue descriptor
 * @qdid:    the id of the queuing destination to be enqueued
 * @qd_bin:  the queuing destination bin
 * @qd_prio: the queuing destination priority
 */
व्योम qbman_eq_desc_set_qd(काष्ठा qbman_eq_desc *d, u32 qdid,
			  u32 qd_bin, u32 qd_prio)
अणु
	d->verb |= 1 << QB_ENQUEUE_CMD_TARGET_TYPE_SHIFT;
	d->tgtid = cpu_to_le32(qdid);
	d->qdbin = cpu_to_le16(qd_bin);
	d->qpri = qd_prio;
पूर्ण

#घोषणा EQAR_IDX(eqar)     ((eqar) & 0x7)
#घोषणा EQAR_VB(eqar)      ((eqar) & 0x80)
#घोषणा EQAR_SUCCESS(eqar) ((eqar) & 0x100)

#घोषणा QB_RT_BIT ((u32)0x100)
/**
 * qbman_swp_enqueue_direct() - Issue an enqueue command
 * @s:  the software portal used क्रम enqueue
 * @d:  the enqueue descriptor
 * @fd: the frame descriptor to be enqueued
 *
 * Please note that 'fd' should only be शून्य अगर the "action" of the
 * descriptor is "orp_hole" or "orp_nesn".
 *
 * Return 0 क्रम successful enqueue, -EBUSY अगर the EQCR is not पढ़ोy.
 */
अटल
पूर्णांक qbman_swp_enqueue_direct(काष्ठा qbman_swp *s,
			     स्थिर काष्ठा qbman_eq_desc *d,
			     स्थिर काष्ठा dpaa2_fd *fd)
अणु
	पूर्णांक flags = 0;
	पूर्णांक ret = qbman_swp_enqueue_multiple_direct(s, d, fd, &flags, 1);

	अगर (ret >= 0)
		ret = 0;
	अन्यथा
		ret = -EBUSY;
	वापस  ret;
पूर्ण

/**
 * qbman_swp_enqueue_mem_back() - Issue an enqueue command
 * @s:  the software portal used क्रम enqueue
 * @d:  the enqueue descriptor
 * @fd: the frame descriptor to be enqueued
 *
 * Please note that 'fd' should only be शून्य अगर the "action" of the
 * descriptor is "orp_hole" or "orp_nesn".
 *
 * Return 0 क्रम successful enqueue, -EBUSY अगर the EQCR is not पढ़ोy.
 */
अटल
पूर्णांक qbman_swp_enqueue_mem_back(काष्ठा qbman_swp *s,
			       स्थिर काष्ठा qbman_eq_desc *d,
			       स्थिर काष्ठा dpaa2_fd *fd)
अणु
	पूर्णांक flags = 0;
	पूर्णांक ret = qbman_swp_enqueue_multiple_mem_back(s, d, fd, &flags, 1);

	अगर (ret >= 0)
		ret = 0;
	अन्यथा
		ret = -EBUSY;
	वापस  ret;
पूर्ण

/**
 * qbman_swp_enqueue_multiple_direct() - Issue a multi enqueue command
 * using one enqueue descriptor
 * @s:  the software portal used क्रम enqueue
 * @d:  the enqueue descriptor
 * @fd: table poपूर्णांकer of frame descriptor table to be enqueued
 * @flags: table poपूर्णांकer of QBMAN_ENQUEUE_FLAG_DCA flags, not used अगर शून्य
 * @num_frames: number of fd to be enqueued
 *
 * Return the number of fd enqueued, or a negative error number.
 */
अटल
पूर्णांक qbman_swp_enqueue_multiple_direct(काष्ठा qbman_swp *s,
				      स्थिर काष्ठा qbman_eq_desc *d,
				      स्थिर काष्ठा dpaa2_fd *fd,
				      uपूर्णांक32_t *flags,
				      पूर्णांक num_frames)
अणु
	uपूर्णांक32_t *p = शून्य;
	स्थिर uपूर्णांक32_t *cl = (uपूर्णांक32_t *)d;
	uपूर्णांक32_t eqcr_ci, eqcr_pi, half_mask, full_mask;
	पूर्णांक i, num_enqueued = 0;

	spin_lock(&s->access_spinlock);
	half_mask = (s->eqcr.pi_ci_mask>>1);
	full_mask = s->eqcr.pi_ci_mask;

	अगर (!s->eqcr.available) अणु
		eqcr_ci = s->eqcr.ci;
		p = s->addr_cena + QBMAN_CENA_SWP_EQCR_CI;
		s->eqcr.ci = qbman_पढ़ो_रेजिस्टर(s, QBMAN_CINH_SWP_EQCR_CI);
		s->eqcr.ci &= full_mask;

		s->eqcr.available = qm_cyc_dअगरf(s->eqcr.pi_ring_size,
					eqcr_ci, s->eqcr.ci);
		अगर (!s->eqcr.available) अणु
			spin_unlock(&s->access_spinlock);
			वापस 0;
		पूर्ण
	पूर्ण

	eqcr_pi = s->eqcr.pi;
	num_enqueued = (s->eqcr.available < num_frames) ?
			s->eqcr.available : num_frames;
	s->eqcr.available -= num_enqueued;
	/* Fill in the EQCR ring */
	क्रम (i = 0; i < num_enqueued; i++) अणु
		p = (s->addr_cena + QBMAN_CENA_SWP_EQCR(eqcr_pi & half_mask));
		/* Skip copying the verb */
		स_नकल(&p[1], &cl[1], EQ_DESC_SIZE_WITHOUT_FD - 1);
		स_नकल(&p[EQ_DESC_SIZE_FD_START/माप(uपूर्णांक32_t)],
		       &fd[i], माप(*fd));
		eqcr_pi++;
	पूर्ण

	dma_wmb();

	/* Set the verb byte, have to substitute in the valid-bit */
	eqcr_pi = s->eqcr.pi;
	क्रम (i = 0; i < num_enqueued; i++) अणु
		p = (s->addr_cena + QBMAN_CENA_SWP_EQCR(eqcr_pi & half_mask));
		p[0] = cl[0] | s->eqcr.pi_vb;
		अगर (flags && (flags[i] & QBMAN_ENQUEUE_FLAG_DCA)) अणु
			काष्ठा qbman_eq_desc *d = (काष्ठा qbman_eq_desc *)p;

			d->dca = (1 << QB_ENQUEUE_CMD_DCA_EN_SHIFT) |
				((flags[i]) & QBMAN_EQCR_DCA_IDXMASK);
		पूर्ण
		eqcr_pi++;
		अगर (!(eqcr_pi & half_mask))
			s->eqcr.pi_vb ^= QB_VALID_BIT;
	पूर्ण

	/* Flush all the cacheline without load/store in between */
	eqcr_pi = s->eqcr.pi;
	क्रम (i = 0; i < num_enqueued; i++)
		eqcr_pi++;
	s->eqcr.pi = eqcr_pi & full_mask;
	spin_unlock(&s->access_spinlock);

	वापस num_enqueued;
पूर्ण

/**
 * qbman_swp_enqueue_multiple_mem_back() - Issue a multi enqueue command
 * using one enqueue descriptor
 * @s:  the software portal used क्रम enqueue
 * @d:  the enqueue descriptor
 * @fd: table poपूर्णांकer of frame descriptor table to be enqueued
 * @flags: table poपूर्णांकer of QBMAN_ENQUEUE_FLAG_DCA flags, not used अगर शून्य
 * @num_frames: number of fd to be enqueued
 *
 * Return the number of fd enqueued, or a negative error number.
 */
अटल
पूर्णांक qbman_swp_enqueue_multiple_mem_back(काष्ठा qbman_swp *s,
					स्थिर काष्ठा qbman_eq_desc *d,
					स्थिर काष्ठा dpaa2_fd *fd,
					uपूर्णांक32_t *flags,
					पूर्णांक num_frames)
अणु
	uपूर्णांक32_t *p = शून्य;
	स्थिर uपूर्णांक32_t *cl = (uपूर्णांक32_t *)(d);
	uपूर्णांक32_t eqcr_ci, eqcr_pi, half_mask, full_mask;
	पूर्णांक i, num_enqueued = 0;
	अचिन्हित दीर्घ irq_flags;

	spin_lock(&s->access_spinlock);
	local_irq_save(irq_flags);

	half_mask = (s->eqcr.pi_ci_mask>>1);
	full_mask = s->eqcr.pi_ci_mask;
	अगर (!s->eqcr.available) अणु
		eqcr_ci = s->eqcr.ci;
		p = s->addr_cena + QBMAN_CENA_SWP_EQCR_CI_MEMBACK;
		s->eqcr.ci = *p & full_mask;
		s->eqcr.available = qm_cyc_dअगरf(s->eqcr.pi_ring_size,
					eqcr_ci, s->eqcr.ci);
		अगर (!s->eqcr.available) अणु
			local_irq_restore(irq_flags);
			spin_unlock(&s->access_spinlock);
			वापस 0;
		पूर्ण
	पूर्ण

	eqcr_pi = s->eqcr.pi;
	num_enqueued = (s->eqcr.available < num_frames) ?
			s->eqcr.available : num_frames;
	s->eqcr.available -= num_enqueued;
	/* Fill in the EQCR ring */
	क्रम (i = 0; i < num_enqueued; i++) अणु
		p = (s->addr_cena + QBMAN_CENA_SWP_EQCR(eqcr_pi & half_mask));
		/* Skip copying the verb */
		स_नकल(&p[1], &cl[1], EQ_DESC_SIZE_WITHOUT_FD - 1);
		स_नकल(&p[EQ_DESC_SIZE_FD_START/माप(uपूर्णांक32_t)],
		       &fd[i], माप(*fd));
		eqcr_pi++;
	पूर्ण

	/* Set the verb byte, have to substitute in the valid-bit */
	eqcr_pi = s->eqcr.pi;
	क्रम (i = 0; i < num_enqueued; i++) अणु
		p = (s->addr_cena + QBMAN_CENA_SWP_EQCR(eqcr_pi & half_mask));
		p[0] = cl[0] | s->eqcr.pi_vb;
		अगर (flags && (flags[i] & QBMAN_ENQUEUE_FLAG_DCA)) अणु
			काष्ठा qbman_eq_desc *d = (काष्ठा qbman_eq_desc *)p;

			d->dca = (1 << QB_ENQUEUE_CMD_DCA_EN_SHIFT) |
				((flags[i]) & QBMAN_EQCR_DCA_IDXMASK);
		पूर्ण
		eqcr_pi++;
		अगर (!(eqcr_pi & half_mask))
			s->eqcr.pi_vb ^= QB_VALID_BIT;
	पूर्ण
	s->eqcr.pi = eqcr_pi & full_mask;

	dma_wmb();
	qbman_ग_लिखो_रेजिस्टर(s, QBMAN_CINH_SWP_EQCR_PI,
				(QB_RT_BIT)|(s->eqcr.pi)|s->eqcr.pi_vb);
	local_irq_restore(irq_flags);
	spin_unlock(&s->access_spinlock);

	वापस num_enqueued;
पूर्ण

/**
 * qbman_swp_enqueue_multiple_desc_direct() - Issue a multi enqueue command
 * using multiple enqueue descriptor
 * @s:  the software portal used क्रम enqueue
 * @d:  table of minimal enqueue descriptor
 * @fd: table poपूर्णांकer of frame descriptor table to be enqueued
 * @num_frames: number of fd to be enqueued
 *
 * Return the number of fd enqueued, or a negative error number.
 */
अटल
पूर्णांक qbman_swp_enqueue_multiple_desc_direct(काष्ठा qbman_swp *s,
					   स्थिर काष्ठा qbman_eq_desc *d,
					   स्थिर काष्ठा dpaa2_fd *fd,
					   पूर्णांक num_frames)
अणु
	uपूर्णांक32_t *p;
	स्थिर uपूर्णांक32_t *cl;
	uपूर्णांक32_t eqcr_ci, eqcr_pi, half_mask, full_mask;
	पूर्णांक i, num_enqueued = 0;

	half_mask = (s->eqcr.pi_ci_mask>>1);
	full_mask = s->eqcr.pi_ci_mask;
	अगर (!s->eqcr.available) अणु
		eqcr_ci = s->eqcr.ci;
		p = s->addr_cena + QBMAN_CENA_SWP_EQCR_CI;
		s->eqcr.ci = qbman_पढ़ो_रेजिस्टर(s, QBMAN_CINH_SWP_EQCR_CI);
		s->eqcr.available = qm_cyc_dअगरf(s->eqcr.pi_ring_size,
					eqcr_ci, s->eqcr.ci);
		अगर (!s->eqcr.available)
			वापस 0;
	पूर्ण

	eqcr_pi = s->eqcr.pi;
	num_enqueued = (s->eqcr.available < num_frames) ?
			s->eqcr.available : num_frames;
	s->eqcr.available -= num_enqueued;
	/* Fill in the EQCR ring */
	क्रम (i = 0; i < num_enqueued; i++) अणु
		p = (s->addr_cena + QBMAN_CENA_SWP_EQCR(eqcr_pi & half_mask));
		cl = (uपूर्णांक32_t *)(&d[i]);
		/* Skip copying the verb */
		स_नकल(&p[1], &cl[1], EQ_DESC_SIZE_WITHOUT_FD - 1);
		स_नकल(&p[EQ_DESC_SIZE_FD_START/माप(uपूर्णांक32_t)],
		       &fd[i], माप(*fd));
		eqcr_pi++;
	पूर्ण

	dma_wmb();

	/* Set the verb byte, have to substitute in the valid-bit */
	eqcr_pi = s->eqcr.pi;
	क्रम (i = 0; i < num_enqueued; i++) अणु
		p = (s->addr_cena + QBMAN_CENA_SWP_EQCR(eqcr_pi & half_mask));
		cl = (uपूर्णांक32_t *)(&d[i]);
		p[0] = cl[0] | s->eqcr.pi_vb;
		eqcr_pi++;
		अगर (!(eqcr_pi & half_mask))
			s->eqcr.pi_vb ^= QB_VALID_BIT;
	पूर्ण

	/* Flush all the cacheline without load/store in between */
	eqcr_pi = s->eqcr.pi;
	क्रम (i = 0; i < num_enqueued; i++)
		eqcr_pi++;
	s->eqcr.pi = eqcr_pi & full_mask;

	वापस num_enqueued;
पूर्ण

/**
 * qbman_swp_enqueue_multiple_desc_mem_back() - Issue a multi enqueue command
 * using multiple enqueue descriptor
 * @s:  the software portal used क्रम enqueue
 * @d:  table of minimal enqueue descriptor
 * @fd: table poपूर्णांकer of frame descriptor table to be enqueued
 * @num_frames: number of fd to be enqueued
 *
 * Return the number of fd enqueued, or a negative error number.
 */
अटल
पूर्णांक qbman_swp_enqueue_multiple_desc_mem_back(काष्ठा qbman_swp *s,
					   स्थिर काष्ठा qbman_eq_desc *d,
					   स्थिर काष्ठा dpaa2_fd *fd,
					   पूर्णांक num_frames)
अणु
	uपूर्णांक32_t *p;
	स्थिर uपूर्णांक32_t *cl;
	uपूर्णांक32_t eqcr_ci, eqcr_pi, half_mask, full_mask;
	पूर्णांक i, num_enqueued = 0;

	half_mask = (s->eqcr.pi_ci_mask>>1);
	full_mask = s->eqcr.pi_ci_mask;
	अगर (!s->eqcr.available) अणु
		eqcr_ci = s->eqcr.ci;
		p = s->addr_cena + QBMAN_CENA_SWP_EQCR_CI_MEMBACK;
		s->eqcr.ci = *p & full_mask;
		s->eqcr.available = qm_cyc_dअगरf(s->eqcr.pi_ring_size,
					eqcr_ci, s->eqcr.ci);
		अगर (!s->eqcr.available)
			वापस 0;
	पूर्ण

	eqcr_pi = s->eqcr.pi;
	num_enqueued = (s->eqcr.available < num_frames) ?
			s->eqcr.available : num_frames;
	s->eqcr.available -= num_enqueued;
	/* Fill in the EQCR ring */
	क्रम (i = 0; i < num_enqueued; i++) अणु
		p = (s->addr_cena + QBMAN_CENA_SWP_EQCR(eqcr_pi & half_mask));
		cl = (uपूर्णांक32_t *)(&d[i]);
		/* Skip copying the verb */
		स_नकल(&p[1], &cl[1], EQ_DESC_SIZE_WITHOUT_FD - 1);
		स_नकल(&p[EQ_DESC_SIZE_FD_START/माप(uपूर्णांक32_t)],
		       &fd[i], माप(*fd));
		eqcr_pi++;
	पूर्ण

	/* Set the verb byte, have to substitute in the valid-bit */
	eqcr_pi = s->eqcr.pi;
	क्रम (i = 0; i < num_enqueued; i++) अणु
		p = (s->addr_cena + QBMAN_CENA_SWP_EQCR(eqcr_pi & half_mask));
		cl = (uपूर्णांक32_t *)(&d[i]);
		p[0] = cl[0] | s->eqcr.pi_vb;
		eqcr_pi++;
		अगर (!(eqcr_pi & half_mask))
			s->eqcr.pi_vb ^= QB_VALID_BIT;
	पूर्ण

	s->eqcr.pi = eqcr_pi & full_mask;

	dma_wmb();
	qbman_ग_लिखो_रेजिस्टर(s, QBMAN_CINH_SWP_EQCR_PI,
				(QB_RT_BIT)|(s->eqcr.pi)|s->eqcr.pi_vb);

	वापस num_enqueued;
पूर्ण

/* Static (push) dequeue */

/**
 * qbman_swp_push_get() - Get the push dequeue setup
 * @s:           the software portal object
 * @channel_idx: the channel index to query
 * @enabled:     वापसed boolean to show whether the push dequeue is enabled
 *               क्रम the given channel
 */
व्योम qbman_swp_push_get(काष्ठा qbman_swp *s, u8 channel_idx, पूर्णांक *enabled)
अणु
	u16 src = (s->sdq >> QB_SDQCR_SRC_SHIFT) & QB_SDQCR_SRC_MASK;

	WARN_ON(channel_idx > 15);
	*enabled = src | (1 << channel_idx);
पूर्ण

/**
 * qbman_swp_push_set() - Enable or disable push dequeue
 * @s:           the software portal object
 * @channel_idx: the channel index (0 to 15)
 * @enable:      enable or disable push dequeue
 */
व्योम qbman_swp_push_set(काष्ठा qbman_swp *s, u8 channel_idx, पूर्णांक enable)
अणु
	u16 dqsrc;

	WARN_ON(channel_idx > 15);
	अगर (enable)
		s->sdq |= 1 << channel_idx;
	अन्यथा
		s->sdq &= ~(1 << channel_idx);

	/* Read make the complete src map.  If no channels are enabled
	 * the SDQCR must be 0 or अन्यथा QMan will निश्चित errors
	 */
	dqsrc = (s->sdq >> QB_SDQCR_SRC_SHIFT) & QB_SDQCR_SRC_MASK;
	अगर (dqsrc != 0)
		qbman_ग_लिखो_रेजिस्टर(s, QBMAN_CINH_SWP_SDQCR, s->sdq);
	अन्यथा
		qbman_ग_लिखो_रेजिस्टर(s, QBMAN_CINH_SWP_SDQCR, 0);
पूर्ण

#घोषणा QB_VDQCR_VERB_DCT_SHIFT    0
#घोषणा QB_VDQCR_VERB_DT_SHIFT     2
#घोषणा QB_VDQCR_VERB_RLS_SHIFT    4
#घोषणा QB_VDQCR_VERB_WAE_SHIFT    5

क्रमागत qb_pull_dt_e अणु
	qb_pull_dt_channel,
	qb_pull_dt_workqueue,
	qb_pull_dt_framequeue
पूर्ण;

/**
 * qbman_pull_desc_clear() - Clear the contents of a descriptor to
 *                           शेष/starting state
 * @d: the pull dequeue descriptor to be cleared
 */
व्योम qbman_pull_desc_clear(काष्ठा qbman_pull_desc *d)
अणु
	स_रखो(d, 0, माप(*d));
पूर्ण

/**
 * qbman_pull_desc_set_storage()- Set the pull dequeue storage
 * @d:            the pull dequeue descriptor to be set
 * @storage:      the poपूर्णांकer of the memory to store the dequeue result
 * @storage_phys: the physical address of the storage memory
 * @stash:        to indicate whether ग_लिखो allocate is enabled
 *
 * If not called, or अगर called with 'storage' as शून्य, the result pull dequeues
 * will produce results to DQRR. If 'storage' is non-शून्य, then results are
 * produced to the given memory location (using the DMA address which
 * the caller provides in 'storage_phys'), and 'stash' controls whether or not
 * those ग_लिखोs to मुख्य-memory express a cache-warming attribute.
 */
व्योम qbman_pull_desc_set_storage(काष्ठा qbman_pull_desc *d,
				 काष्ठा dpaa2_dq *storage,
				 dma_addr_t storage_phys,
				 पूर्णांक stash)
अणु
	/* save the भव address */
	d->rsp_addr_virt = (u64)(uपूर्णांकptr_t)storage;

	अगर (!storage) अणु
		d->verb &= ~(1 << QB_VDQCR_VERB_RLS_SHIFT);
		वापस;
	पूर्ण
	d->verb |= 1 << QB_VDQCR_VERB_RLS_SHIFT;
	अगर (stash)
		d->verb |= 1 << QB_VDQCR_VERB_WAE_SHIFT;
	अन्यथा
		d->verb &= ~(1 << QB_VDQCR_VERB_WAE_SHIFT);

	d->rsp_addr = cpu_to_le64(storage_phys);
पूर्ण

/**
 * qbman_pull_desc_set_numframes() - Set the number of frames to be dequeued
 * @d:         the pull dequeue descriptor to be set
 * @numframes: number of frames to be set, must be between 1 and 16, inclusive
 */
व्योम qbman_pull_desc_set_numframes(काष्ठा qbman_pull_desc *d, u8 numframes)
अणु
	d->numf = numframes - 1;
पूर्ण

/*
 * Exactly one of the following descriptor "actions" should be set. (Calling any
 * one of these will replace the effect of any prior call to one of these.)
 * - pull dequeue from the given frame queue (FQ)
 * - pull dequeue from any FQ in the given work queue (WQ)
 * - pull dequeue from any FQ in any WQ in the given channel
 */

/**
 * qbman_pull_desc_set_fq() - Set fqid from which the dequeue command dequeues
 * @d:    the pull dequeue descriptor to be set
 * @fqid: the frame queue index of the given FQ
 */
व्योम qbman_pull_desc_set_fq(काष्ठा qbman_pull_desc *d, u32 fqid)
अणु
	d->verb |= 1 << QB_VDQCR_VERB_DCT_SHIFT;
	d->verb |= qb_pull_dt_framequeue << QB_VDQCR_VERB_DT_SHIFT;
	d->dq_src = cpu_to_le32(fqid);
पूर्ण

/**
 * qbman_pull_desc_set_wq() - Set wqid from which the dequeue command dequeues
 * @d:    the pull dequeue descriptor to be set
 * @wqid: composed of channel id and wqid within the channel
 * @dct:  the dequeue command type
 */
व्योम qbman_pull_desc_set_wq(काष्ठा qbman_pull_desc *d, u32 wqid,
			    क्रमागत qbman_pull_type_e dct)
अणु
	d->verb |= dct << QB_VDQCR_VERB_DCT_SHIFT;
	d->verb |= qb_pull_dt_workqueue << QB_VDQCR_VERB_DT_SHIFT;
	d->dq_src = cpu_to_le32(wqid);
पूर्ण

/**
 * qbman_pull_desc_set_channel() - Set channelid from which the dequeue command
 *                                 dequeues
 * @d:    the pull dequeue descriptor to be set
 * @chid: the channel id to be dequeued
 * @dct:  the dequeue command type
 */
व्योम qbman_pull_desc_set_channel(काष्ठा qbman_pull_desc *d, u32 chid,
				 क्रमागत qbman_pull_type_e dct)
अणु
	d->verb |= dct << QB_VDQCR_VERB_DCT_SHIFT;
	d->verb |= qb_pull_dt_channel << QB_VDQCR_VERB_DT_SHIFT;
	d->dq_src = cpu_to_le32(chid);
पूर्ण

/**
 * qbman_swp_pull_direct() - Issue the pull dequeue command
 * @s: the software portal object
 * @d: the software portal descriptor which has been configured with
 *     the set of qbman_pull_desc_set_*() calls
 *
 * Return 0 क्रम success, and -EBUSY अगर the software portal is not पढ़ोy
 * to करो pull dequeue.
 */
अटल
पूर्णांक qbman_swp_pull_direct(काष्ठा qbman_swp *s, काष्ठा qbman_pull_desc *d)
अणु
	काष्ठा qbman_pull_desc *p;

	अगर (!atomic_dec_and_test(&s->vdq.available)) अणु
		atomic_inc(&s->vdq.available);
		वापस -EBUSY;
	पूर्ण
	s->vdq.storage = (व्योम *)(uपूर्णांकptr_t)d->rsp_addr_virt;
	अगर ((s->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_5000)
		p = qbman_get_cmd(s, QBMAN_CENA_SWP_VDQCR);
	अन्यथा
		p = qbman_get_cmd(s, QBMAN_CENA_SWP_VDQCR_MEM);
	p->numf = d->numf;
	p->tok = QMAN_DQ_TOKEN_VALID;
	p->dq_src = d->dq_src;
	p->rsp_addr = d->rsp_addr;
	p->rsp_addr_virt = d->rsp_addr_virt;
	dma_wmb();
	/* Set the verb byte, have to substitute in the valid-bit */
	p->verb = d->verb | s->vdq.valid_bit;
	s->vdq.valid_bit ^= QB_VALID_BIT;

	वापस 0;
पूर्ण

/**
 * qbman_swp_pull_mem_back() - Issue the pull dequeue command
 * @s: the software portal object
 * @d: the software portal descriptor which has been configured with
 *     the set of qbman_pull_desc_set_*() calls
 *
 * Return 0 क्रम success, and -EBUSY अगर the software portal is not पढ़ोy
 * to करो pull dequeue.
 */
अटल
पूर्णांक qbman_swp_pull_mem_back(काष्ठा qbman_swp *s, काष्ठा qbman_pull_desc *d)
अणु
	काष्ठा qbman_pull_desc *p;

	अगर (!atomic_dec_and_test(&s->vdq.available)) अणु
		atomic_inc(&s->vdq.available);
		वापस -EBUSY;
	पूर्ण
	s->vdq.storage = (व्योम *)(uपूर्णांकptr_t)d->rsp_addr_virt;
	अगर ((s->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_5000)
		p = qbman_get_cmd(s, QBMAN_CENA_SWP_VDQCR);
	अन्यथा
		p = qbman_get_cmd(s, QBMAN_CENA_SWP_VDQCR_MEM);
	p->numf = d->numf;
	p->tok = QMAN_DQ_TOKEN_VALID;
	p->dq_src = d->dq_src;
	p->rsp_addr = d->rsp_addr;
	p->rsp_addr_virt = d->rsp_addr_virt;

	/* Set the verb byte, have to substitute in the valid-bit */
	p->verb = d->verb | s->vdq.valid_bit;
	s->vdq.valid_bit ^= QB_VALID_BIT;
	dma_wmb();
	qbman_ग_लिखो_रेजिस्टर(s, QBMAN_CINH_SWP_VDQCR_RT, QMAN_RT_MODE);

	वापस 0;
पूर्ण

#घोषणा QMAN_DQRR_PI_MASK   0xf

/**
 * qbman_swp_dqrr_next_direct() - Get an valid DQRR entry
 * @s: the software portal object
 *
 * Return शून्य अगर there are no unconsumed DQRR entries. Return a DQRR entry
 * only once, so repeated calls can वापस a sequence of DQRR entries, without
 * requiring they be consumed immediately or in any particular order.
 */
स्थिर काष्ठा dpaa2_dq *qbman_swp_dqrr_next_direct(काष्ठा qbman_swp *s)
अणु
	u32 verb;
	u32 response_verb;
	u32 flags;
	काष्ठा dpaa2_dq *p;

	/* Beक्रमe using valid-bit to detect अगर something is there, we have to
	 * handle the हाल of the DQRR reset bug...
	 */
	अगर (unlikely(s->dqrr.reset_bug)) अणु
		/*
		 * We pick up new entries by cache-inhibited producer index,
		 * which means that a non-coherent mapping would require us to
		 * invalidate and पढ़ो *only* once that PI has indicated that
		 * there's an entry here. The first trip around the DQRR ring
		 * will be much less efficient than all subsequent trips around
		 * it...
		 */
		u8 pi = qbman_पढ़ो_रेजिस्टर(s, QBMAN_CINH_SWP_DQPI) &
			QMAN_DQRR_PI_MASK;

		/* there are new entries अगर pi != next_idx */
		अगर (pi == s->dqrr.next_idx)
			वापस शून्य;

		/*
		 * अगर next_idx is/was the last ring index, and 'pi' is
		 * dअगरferent, we can disable the workaround as all the ring
		 * entries have now been DMA'd to so valid-bit checking is
		 * repaired. Note: this logic needs to be based on next_idx
		 * (which increments one at a समय), rather than on pi (which
		 * can burst and wrap-around between our snapshots of it).
		 */
		अगर (s->dqrr.next_idx == (s->dqrr.dqrr_size - 1)) अणु
			pr_debug("next_idx=%d, pi=%d, clear reset bug\n",
				 s->dqrr.next_idx, pi);
			s->dqrr.reset_bug = 0;
		पूर्ण
		prefetch(qbman_get_cmd(s,
				       QBMAN_CENA_SWP_DQRR(s->dqrr.next_idx)));
	पूर्ण

	p = qbman_get_cmd(s, QBMAN_CENA_SWP_DQRR(s->dqrr.next_idx));
	verb = p->dq.verb;

	/*
	 * If the valid-bit isn't of the expected polarity, nothing there. Note,
	 * in the DQRR reset bug workaround, we shouldn't need to skip these
	 * check, because we've alपढ़ोy determined that a new entry is available
	 * and we've invalidated the cacheline beक्रमe पढ़ोing it, so the
	 * valid-bit behaviour is repaired and should tell us what we alपढ़ोy
	 * knew from पढ़ोing PI.
	 */
	अगर ((verb & QB_VALID_BIT) != s->dqrr.valid_bit) अणु
		prefetch(qbman_get_cmd(s,
				       QBMAN_CENA_SWP_DQRR(s->dqrr.next_idx)));
		वापस शून्य;
	पूर्ण
	/*
	 * There's something there. Move "next_idx" attention to the next ring
	 * entry (and prefetch it) beक्रमe वापसing what we found.
	 */
	s->dqrr.next_idx++;
	s->dqrr.next_idx &= s->dqrr.dqrr_size - 1; /* Wrap around */
	अगर (!s->dqrr.next_idx)
		s->dqrr.valid_bit ^= QB_VALID_BIT;

	/*
	 * If this is the final response to a अस्थिर dequeue command
	 * indicate that the vdq is available
	 */
	flags = p->dq.stat;
	response_verb = verb & QBMAN_RESULT_MASK;
	अगर ((response_verb == QBMAN_RESULT_DQ) &&
	    (flags & DPAA2_DQ_STAT_VOLATILE) &&
	    (flags & DPAA2_DQ_STAT_EXPIRED))
		atomic_inc(&s->vdq.available);

	prefetch(qbman_get_cmd(s, QBMAN_CENA_SWP_DQRR(s->dqrr.next_idx)));

	वापस p;
पूर्ण

/**
 * qbman_swp_dqrr_next_mem_back() - Get an valid DQRR entry
 * @s: the software portal object
 *
 * Return शून्य अगर there are no unconsumed DQRR entries. Return a DQRR entry
 * only once, so repeated calls can वापस a sequence of DQRR entries, without
 * requiring they be consumed immediately or in any particular order.
 */
स्थिर काष्ठा dpaa2_dq *qbman_swp_dqrr_next_mem_back(काष्ठा qbman_swp *s)
अणु
	u32 verb;
	u32 response_verb;
	u32 flags;
	काष्ठा dpaa2_dq *p;

	/* Beक्रमe using valid-bit to detect अगर something is there, we have to
	 * handle the हाल of the DQRR reset bug...
	 */
	अगर (unlikely(s->dqrr.reset_bug)) अणु
		/*
		 * We pick up new entries by cache-inhibited producer index,
		 * which means that a non-coherent mapping would require us to
		 * invalidate and पढ़ो *only* once that PI has indicated that
		 * there's an entry here. The first trip around the DQRR ring
		 * will be much less efficient than all subsequent trips around
		 * it...
		 */
		u8 pi = qbman_पढ़ो_रेजिस्टर(s, QBMAN_CINH_SWP_DQPI) &
			QMAN_DQRR_PI_MASK;

		/* there are new entries अगर pi != next_idx */
		अगर (pi == s->dqrr.next_idx)
			वापस शून्य;

		/*
		 * अगर next_idx is/was the last ring index, and 'pi' is
		 * dअगरferent, we can disable the workaround as all the ring
		 * entries have now been DMA'd to so valid-bit checking is
		 * repaired. Note: this logic needs to be based on next_idx
		 * (which increments one at a समय), rather than on pi (which
		 * can burst and wrap-around between our snapshots of it).
		 */
		अगर (s->dqrr.next_idx == (s->dqrr.dqrr_size - 1)) अणु
			pr_debug("next_idx=%d, pi=%d, clear reset bug\n",
				 s->dqrr.next_idx, pi);
			s->dqrr.reset_bug = 0;
		पूर्ण
		prefetch(qbman_get_cmd(s,
				       QBMAN_CENA_SWP_DQRR(s->dqrr.next_idx)));
	पूर्ण

	p = qbman_get_cmd(s, QBMAN_CENA_SWP_DQRR_MEM(s->dqrr.next_idx));
	verb = p->dq.verb;

	/*
	 * If the valid-bit isn't of the expected polarity, nothing there. Note,
	 * in the DQRR reset bug workaround, we shouldn't need to skip these
	 * check, because we've alपढ़ोy determined that a new entry is available
	 * and we've invalidated the cacheline beक्रमe पढ़ोing it, so the
	 * valid-bit behaviour is repaired and should tell us what we alपढ़ोy
	 * knew from पढ़ोing PI.
	 */
	अगर ((verb & QB_VALID_BIT) != s->dqrr.valid_bit) अणु
		prefetch(qbman_get_cmd(s,
				       QBMAN_CENA_SWP_DQRR(s->dqrr.next_idx)));
		वापस शून्य;
	पूर्ण
	/*
	 * There's something there. Move "next_idx" attention to the next ring
	 * entry (and prefetch it) beक्रमe वापसing what we found.
	 */
	s->dqrr.next_idx++;
	s->dqrr.next_idx &= s->dqrr.dqrr_size - 1; /* Wrap around */
	अगर (!s->dqrr.next_idx)
		s->dqrr.valid_bit ^= QB_VALID_BIT;

	/*
	 * If this is the final response to a अस्थिर dequeue command
	 * indicate that the vdq is available
	 */
	flags = p->dq.stat;
	response_verb = verb & QBMAN_RESULT_MASK;
	अगर ((response_verb == QBMAN_RESULT_DQ) &&
	    (flags & DPAA2_DQ_STAT_VOLATILE) &&
	    (flags & DPAA2_DQ_STAT_EXPIRED))
		atomic_inc(&s->vdq.available);

	prefetch(qbman_get_cmd(s, QBMAN_CENA_SWP_DQRR(s->dqrr.next_idx)));

	वापस p;
पूर्ण

/**
 * qbman_swp_dqrr_consume() -  Consume DQRR entries previously वापसed from
 *                             qbman_swp_dqrr_next().
 * @s: the software portal object
 * @dq: the DQRR entry to be consumed
 */
व्योम qbman_swp_dqrr_consume(काष्ठा qbman_swp *s, स्थिर काष्ठा dpaa2_dq *dq)
अणु
	qbman_ग_लिखो_रेजिस्टर(s, QBMAN_CINH_SWP_DCAP, QBMAN_IDX_FROM_DQRR(dq));
पूर्ण

/**
 * qbman_result_has_new_result() - Check and get the dequeue response from the
 *                                 dq storage memory set in pull dequeue command
 * @s: the software portal object
 * @dq: the dequeue result पढ़ो from the memory
 *
 * Return 1 क्रम getting a valid dequeue result, or 0 क्रम not getting a valid
 * dequeue result.
 *
 * Only used क्रम user-provided storage of dequeue results, not DQRR. For
 * efficiency purposes, the driver will perक्रमm any required endianness
 * conversion to ensure that the user's dequeue result storage is in host-endian
 * क्रमmat. As such, once the user has called qbman_result_has_new_result() and
 * been वापसed a valid dequeue result, they should not call it again on
 * the same memory location (except of course अगर another dequeue command has
 * been executed to produce a new result to that location).
 */
पूर्णांक qbman_result_has_new_result(काष्ठा qbman_swp *s, स्थिर काष्ठा dpaa2_dq *dq)
अणु
	अगर (dq->dq.tok != QMAN_DQ_TOKEN_VALID)
		वापस 0;

	/*
	 * Set token to be 0 so we will detect change back to 1
	 * next समय the looping is traversed. Const is cast away here
	 * as we want users to treat the dequeue responses as पढ़ो only.
	 */
	((काष्ठा dpaa2_dq *)dq)->dq.tok = 0;

	/*
	 * Determine whether VDQCR is available based on whether the
	 * current result is sitting in the first storage location of
	 * the busy command.
	 */
	अगर (s->vdq.storage == dq) अणु
		s->vdq.storage = शून्य;
		atomic_inc(&s->vdq.available);
	पूर्ण

	वापस 1;
पूर्ण

/**
 * qbman_release_desc_clear() - Clear the contents of a descriptor to
 *                              शेष/starting state.
 * @d: the pull dequeue descriptor to be cleared
 */
व्योम qbman_release_desc_clear(काष्ठा qbman_release_desc *d)
अणु
	स_रखो(d, 0, माप(*d));
	d->verb = 1 << 5; /* Release Command Valid */
पूर्ण

/**
 * qbman_release_desc_set_bpid() - Set the ID of the buffer pool to release to
 * @d:    the pull dequeue descriptor to be set
 * @bpid: the bpid value to be set
 */
व्योम qbman_release_desc_set_bpid(काष्ठा qbman_release_desc *d, u16 bpid)
अणु
	d->bpid = cpu_to_le16(bpid);
पूर्ण

/**
 * qbman_release_desc_set_rcdi() - Determines whether or not the portal's RCDI
 * पूर्णांकerrupt source should be निश्चितed after the release command is completed.
 * @d:      the pull dequeue descriptor to be set
 * @enable: enable (1) or disable (0) value
 */
व्योम qbman_release_desc_set_rcdi(काष्ठा qbman_release_desc *d, पूर्णांक enable)
अणु
	अगर (enable)
		d->verb |= 1 << 6;
	अन्यथा
		d->verb &= ~(1 << 6);
पूर्ण

#घोषणा RAR_IDX(rar)     ((rar) & 0x7)
#घोषणा RAR_VB(rar)      ((rar) & 0x80)
#घोषणा RAR_SUCCESS(rar) ((rar) & 0x100)

/**
 * qbman_swp_release_direct() - Issue a buffer release command
 * @s:           the software portal object
 * @d:           the release descriptor
 * @buffers:     a poपूर्णांकer poपूर्णांकing to the buffer address to be released
 * @num_buffers: number of buffers to be released,  must be less than 8
 *
 * Return 0 क्रम success, -EBUSY अगर the release command ring is not पढ़ोy.
 */
पूर्णांक qbman_swp_release_direct(काष्ठा qbman_swp *s,
			     स्थिर काष्ठा qbman_release_desc *d,
			     स्थिर u64 *buffers, अचिन्हित पूर्णांक num_buffers)
अणु
	पूर्णांक i;
	काष्ठा qbman_release_desc *p;
	u32 rar;

	अगर (!num_buffers || (num_buffers > 7))
		वापस -EINVAL;

	rar = qbman_पढ़ो_रेजिस्टर(s, QBMAN_CINH_SWP_RAR);
	अगर (!RAR_SUCCESS(rar))
		वापस -EBUSY;

	/* Start the release command */
	p = qbman_get_cmd(s, QBMAN_CENA_SWP_RCR(RAR_IDX(rar)));

	/* Copy the caller's buffer poपूर्णांकers to the command */
	क्रम (i = 0; i < num_buffers; i++)
		p->buf[i] = cpu_to_le64(buffers[i]);
	p->bpid = d->bpid;

	/*
	 * Set the verb byte, have to substitute in the valid-bit
	 * and the number of buffers.
	 */
	dma_wmb();
	p->verb = d->verb | RAR_VB(rar) | num_buffers;

	वापस 0;
पूर्ण

/**
 * qbman_swp_release_mem_back() - Issue a buffer release command
 * @s:           the software portal object
 * @d:           the release descriptor
 * @buffers:     a poपूर्णांकer poपूर्णांकing to the buffer address to be released
 * @num_buffers: number of buffers to be released,  must be less than 8
 *
 * Return 0 क्रम success, -EBUSY अगर the release command ring is not पढ़ोy.
 */
पूर्णांक qbman_swp_release_mem_back(काष्ठा qbman_swp *s,
			       स्थिर काष्ठा qbman_release_desc *d,
			       स्थिर u64 *buffers, अचिन्हित पूर्णांक num_buffers)
अणु
	पूर्णांक i;
	काष्ठा qbman_release_desc *p;
	u32 rar;

	अगर (!num_buffers || (num_buffers > 7))
		वापस -EINVAL;

	rar = qbman_पढ़ो_रेजिस्टर(s, QBMAN_CINH_SWP_RAR);
	अगर (!RAR_SUCCESS(rar))
		वापस -EBUSY;

	/* Start the release command */
	p = qbman_get_cmd(s, QBMAN_CENA_SWP_RCR_MEM(RAR_IDX(rar)));

	/* Copy the caller's buffer poपूर्णांकers to the command */
	क्रम (i = 0; i < num_buffers; i++)
		p->buf[i] = cpu_to_le64(buffers[i]);
	p->bpid = d->bpid;

	p->verb = d->verb | RAR_VB(rar) | num_buffers;
	dma_wmb();
	qbman_ग_लिखो_रेजिस्टर(s, QBMAN_CINH_SWP_RCR_AM_RT +
			     RAR_IDX(rar)  * 4, QMAN_RT_MODE);

	वापस 0;
पूर्ण

काष्ठा qbman_acquire_desc अणु
	u8 verb;
	u8 reserved;
	__le16 bpid;
	u8 num;
	u8 reserved2[59];
पूर्ण;

काष्ठा qbman_acquire_rslt अणु
	u8 verb;
	u8 rslt;
	__le16 reserved;
	u8 num;
	u8 reserved2[3];
	__le64 buf[7];
पूर्ण;

/**
 * qbman_swp_acquire() - Issue a buffer acquire command
 * @s:           the software portal object
 * @bpid:        the buffer pool index
 * @buffers:     a poपूर्णांकer poपूर्णांकing to the acquired buffer addresses
 * @num_buffers: number of buffers to be acquired, must be less than 8
 *
 * Return 0 क्रम success, or negative error code अगर the acquire command
 * fails.
 */
पूर्णांक qbman_swp_acquire(काष्ठा qbman_swp *s, u16 bpid, u64 *buffers,
		      अचिन्हित पूर्णांक num_buffers)
अणु
	काष्ठा qbman_acquire_desc *p;
	काष्ठा qbman_acquire_rslt *r;
	पूर्णांक i;

	अगर (!num_buffers || (num_buffers > 7))
		वापस -EINVAL;

	/* Start the management command */
	p = qbman_swp_mc_start(s);

	अगर (!p)
		वापस -EBUSY;

	/* Encode the caller-provided attributes */
	p->bpid = cpu_to_le16(bpid);
	p->num = num_buffers;

	/* Complete the management command */
	r = qbman_swp_mc_complete(s, p, QBMAN_MC_ACQUIRE);
	अगर (unlikely(!r)) अणु
		pr_err("qbman: acquire from BPID %d failed, no response\n",
		       bpid);
		वापस -EIO;
	पूर्ण

	/* Decode the outcome */
	WARN_ON((r->verb & 0x7f) != QBMAN_MC_ACQUIRE);

	/* Determine success or failure */
	अगर (unlikely(r->rslt != QBMAN_MC_RSLT_OK)) अणु
		pr_err("qbman: acquire from BPID 0x%x failed, code=0x%02x\n",
		       bpid, r->rslt);
		वापस -EIO;
	पूर्ण

	WARN_ON(r->num > num_buffers);

	/* Copy the acquired buffers to the caller's array */
	क्रम (i = 0; i < r->num; i++)
		buffers[i] = le64_to_cpu(r->buf[i]);

	वापस (पूर्णांक)r->num;
पूर्ण

काष्ठा qbman_alt_fq_state_desc अणु
	u8 verb;
	u8 reserved[3];
	__le32 fqid;
	u8 reserved2[56];
पूर्ण;

काष्ठा qbman_alt_fq_state_rslt अणु
	u8 verb;
	u8 rslt;
	u8 reserved[62];
पूर्ण;

#घोषणा ALT_FQ_FQID_MASK 0x00FFFFFF

पूर्णांक qbman_swp_alt_fq_state(काष्ठा qbman_swp *s, u32 fqid,
			   u8 alt_fq_verb)
अणु
	काष्ठा qbman_alt_fq_state_desc *p;
	काष्ठा qbman_alt_fq_state_rslt *r;

	/* Start the management command */
	p = qbman_swp_mc_start(s);
	अगर (!p)
		वापस -EBUSY;

	p->fqid = cpu_to_le32(fqid & ALT_FQ_FQID_MASK);

	/* Complete the management command */
	r = qbman_swp_mc_complete(s, p, alt_fq_verb);
	अगर (unlikely(!r)) अणु
		pr_err("qbman: mgmt cmd failed, no response (verb=0x%x)\n",
		       alt_fq_verb);
		वापस -EIO;
	पूर्ण

	/* Decode the outcome */
	WARN_ON((r->verb & QBMAN_RESULT_MASK) != alt_fq_verb);

	/* Determine success or failure */
	अगर (unlikely(r->rslt != QBMAN_MC_RSLT_OK)) अणु
		pr_err("qbman: ALT FQID %d failed: verb = 0x%08x code = 0x%02x\n",
		       fqid, r->verb, r->rslt);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा qbman_cdan_ctrl_desc अणु
	u8 verb;
	u8 reserved;
	__le16 ch;
	u8 we;
	u8 ctrl;
	__le16 reserved2;
	__le64 cdan_ctx;
	u8 reserved3[48];

पूर्ण;

काष्ठा qbman_cdan_ctrl_rslt अणु
	u8 verb;
	u8 rslt;
	__le16 ch;
	u8 reserved[60];
पूर्ण;

पूर्णांक qbman_swp_CDAN_set(काष्ठा qbman_swp *s, u16 channelid,
		       u8 we_mask, u8 cdan_en,
		       u64 ctx)
अणु
	काष्ठा qbman_cdan_ctrl_desc *p = शून्य;
	काष्ठा qbman_cdan_ctrl_rslt *r = शून्य;

	/* Start the management command */
	p = qbman_swp_mc_start(s);
	अगर (!p)
		वापस -EBUSY;

	/* Encode the caller-provided attributes */
	p->ch = cpu_to_le16(channelid);
	p->we = we_mask;
	अगर (cdan_en)
		p->ctrl = 1;
	अन्यथा
		p->ctrl = 0;
	p->cdan_ctx = cpu_to_le64(ctx);

	/* Complete the management command */
	r = qbman_swp_mc_complete(s, p, QBMAN_WQCHAN_CONFIGURE);
	अगर (unlikely(!r)) अणु
		pr_err("qbman: wqchan config failed, no response\n");
		वापस -EIO;
	पूर्ण

	WARN_ON((r->verb & 0x7f) != QBMAN_WQCHAN_CONFIGURE);

	/* Determine success or failure */
	अगर (unlikely(r->rslt != QBMAN_MC_RSLT_OK)) अणु
		pr_err("qbman: CDAN cQID %d failed: code = 0x%02x\n",
		       channelid, r->rslt);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा QBMAN_RESPONSE_VERB_MASK	0x7f
#घोषणा QBMAN_FQ_QUERY_NP		0x45
#घोषणा QBMAN_BP_QUERY			0x32

काष्ठा qbman_fq_query_desc अणु
	u8 verb;
	u8 reserved[3];
	__le32 fqid;
	u8 reserved2[56];
पूर्ण;

पूर्णांक qbman_fq_query_state(काष्ठा qbman_swp *s, u32 fqid,
			 काष्ठा qbman_fq_query_np_rslt *r)
अणु
	काष्ठा qbman_fq_query_desc *p;
	व्योम *resp;

	p = (काष्ठा qbman_fq_query_desc *)qbman_swp_mc_start(s);
	अगर (!p)
		वापस -EBUSY;

	/* FQID is a 24 bit value */
	p->fqid = cpu_to_le32(fqid & 0x00FFFFFF);
	resp = qbman_swp_mc_complete(s, p, QBMAN_FQ_QUERY_NP);
	अगर (!resp) अणु
		pr_err("qbman: Query FQID %d NP fields failed, no response\n",
		       fqid);
		वापस -EIO;
	पूर्ण
	*r = *(काष्ठा qbman_fq_query_np_rslt *)resp;
	/* Decode the outcome */
	WARN_ON((r->verb & QBMAN_RESPONSE_VERB_MASK) != QBMAN_FQ_QUERY_NP);

	/* Determine success or failure */
	अगर (r->rslt != QBMAN_MC_RSLT_OK) अणु
		pr_err("Query NP fields of FQID 0x%x failed, code=0x%02x\n",
		       p->fqid, r->rslt);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

u32 qbman_fq_state_frame_count(स्थिर काष्ठा qbman_fq_query_np_rslt *r)
अणु
	वापस (le32_to_cpu(r->frm_cnt) & 0x00FFFFFF);
पूर्ण

u32 qbman_fq_state_byte_count(स्थिर काष्ठा qbman_fq_query_np_rslt *r)
अणु
	वापस le32_to_cpu(r->byte_cnt);
पूर्ण

काष्ठा qbman_bp_query_desc अणु
	u8 verb;
	u8 reserved;
	__le16 bpid;
	u8 reserved2[60];
पूर्ण;

पूर्णांक qbman_bp_query(काष्ठा qbman_swp *s, u16 bpid,
		   काष्ठा qbman_bp_query_rslt *r)
अणु
	काष्ठा qbman_bp_query_desc *p;
	व्योम *resp;

	p = (काष्ठा qbman_bp_query_desc *)qbman_swp_mc_start(s);
	अगर (!p)
		वापस -EBUSY;

	p->bpid = cpu_to_le16(bpid);
	resp = qbman_swp_mc_complete(s, p, QBMAN_BP_QUERY);
	अगर (!resp) अणु
		pr_err("qbman: Query BPID %d fields failed, no response\n",
		       bpid);
		वापस -EIO;
	पूर्ण
	*r = *(काष्ठा qbman_bp_query_rslt *)resp;
	/* Decode the outcome */
	WARN_ON((r->verb & QBMAN_RESPONSE_VERB_MASK) != QBMAN_BP_QUERY);

	/* Determine success or failure */
	अगर (r->rslt != QBMAN_MC_RSLT_OK) अणु
		pr_err("Query fields of BPID 0x%x failed, code=0x%02x\n",
		       bpid, r->rslt);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

u32 qbman_bp_info_num_मुक्त_bufs(काष्ठा qbman_bp_query_rslt *a)
अणु
	वापस le32_to_cpu(a->fill);
पूर्ण
