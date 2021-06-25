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

#समावेश "bman_priv.h"

#घोषणा IRQNAME		"BMan portal %d"
#घोषणा MAX_IRQNAME	16	/* big enough क्रम "BMan portal %d" */

/* Portal रेजिस्टर assists */

#अगर defined(CONFIG_ARM) || defined(CONFIG_ARM64)
/* Cache-inhibited रेजिस्टर offsets */
#घोषणा BM_REG_RCR_PI_CINH	0x3000
#घोषणा BM_REG_RCR_CI_CINH	0x3100
#घोषणा BM_REG_RCR_ITR		0x3200
#घोषणा BM_REG_CFG		0x3300
#घोषणा BM_REG_SCN(n)		(0x3400 + ((n) << 6))
#घोषणा BM_REG_ISR		0x3e00
#घोषणा BM_REG_IER		0x3e40
#घोषणा BM_REG_ISDR		0x3e80
#घोषणा BM_REG_IIR		0x3ec0

/* Cache-enabled रेजिस्टर offsets */
#घोषणा BM_CL_CR		0x0000
#घोषणा BM_CL_RR0		0x0100
#घोषणा BM_CL_RR1		0x0140
#घोषणा BM_CL_RCR		0x1000
#घोषणा BM_CL_RCR_PI_CENA	0x3000
#घोषणा BM_CL_RCR_CI_CENA	0x3100

#अन्यथा
/* Cache-inhibited रेजिस्टर offsets */
#घोषणा BM_REG_RCR_PI_CINH	0x0000
#घोषणा BM_REG_RCR_CI_CINH	0x0004
#घोषणा BM_REG_RCR_ITR		0x0008
#घोषणा BM_REG_CFG		0x0100
#घोषणा BM_REG_SCN(n)		(0x0200 + ((n) << 2))
#घोषणा BM_REG_ISR		0x0e00
#घोषणा BM_REG_IER		0x0e04
#घोषणा BM_REG_ISDR		0x0e08
#घोषणा BM_REG_IIR		0x0e0c

/* Cache-enabled रेजिस्टर offsets */
#घोषणा BM_CL_CR		0x0000
#घोषणा BM_CL_RR0		0x0100
#घोषणा BM_CL_RR1		0x0140
#घोषणा BM_CL_RCR		0x1000
#घोषणा BM_CL_RCR_PI_CENA	0x3000
#घोषणा BM_CL_RCR_CI_CENA	0x3100
#पूर्ण_अगर

/*
 * Portal modes.
 *   Enum types;
 *     pmode == production mode
 *     cmode == consumption mode,
 *   Enum values use 3 letter codes. First letter matches the portal mode,
 *   reमुख्यing two letters indicate;
 *     ci == cache-inhibited portal रेजिस्टर
 *     ce == cache-enabled portal रेजिस्टर
 *     vb == in-band valid-bit (cache-enabled)
 */
क्रमागत bm_rcr_pmode अणु		/* matches BCSP_CFG::RPM */
	bm_rcr_pci = 0,		/* PI index, cache-inhibited */
	bm_rcr_pce = 1,		/* PI index, cache-enabled */
	bm_rcr_pvb = 2		/* valid-bit */
पूर्ण;
क्रमागत bm_rcr_cmode अणु		/* s/w-only */
	bm_rcr_cci,		/* CI index, cache-inhibited */
	bm_rcr_cce		/* CI index, cache-enabled */
पूर्ण;


/* --- Portal काष्ठाures --- */

#घोषणा BM_RCR_SIZE		8

/* Release Command */
काष्ठा bm_rcr_entry अणु
	जोड़ अणु
		काष्ठा अणु
			u8 _ncw_verb; /* ग_लिखोs to this are non-coherent */
			u8 bpid; /* used with BM_RCR_VERB_CMD_BPID_SINGLE */
			u8 __reserved1[62];
		पूर्ण;
		काष्ठा bm_buffer bufs[8];
	पूर्ण;
पूर्ण;
#घोषणा BM_RCR_VERB_VBIT		0x80
#घोषणा BM_RCR_VERB_CMD_MASK		0x70	/* one of two values; */
#घोषणा BM_RCR_VERB_CMD_BPID_SINGLE	0x20
#घोषणा BM_RCR_VERB_CMD_BPID_MULTI	0x30
#घोषणा BM_RCR_VERB_BUFCOUNT_MASK	0x0f	/* values 1..8 */

काष्ठा bm_rcr अणु
	काष्ठा bm_rcr_entry *ring, *cursor;
	u8 ci, available, ithresh, vbit;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	u32 busy;
	क्रमागत bm_rcr_pmode pmode;
	क्रमागत bm_rcr_cmode cmode;
#पूर्ण_अगर
पूर्ण;

/* MC (Management Command) command */
काष्ठा bm_mc_command अणु
	u8 _ncw_verb; /* ग_लिखोs to this are non-coherent */
	u8 bpid; /* used by acquire command */
	u8 __reserved[62];
पूर्ण;
#घोषणा BM_MCC_VERB_VBIT		0x80
#घोषणा BM_MCC_VERB_CMD_MASK		0x70	/* where the verb contains; */
#घोषणा BM_MCC_VERB_CMD_ACQUIRE		0x10
#घोषणा BM_MCC_VERB_CMD_QUERY		0x40
#घोषणा BM_MCC_VERB_ACQUIRE_BUFCOUNT	0x0f	/* values 1..8 go here */

/* MC result, Acquire and Query Response */
जोड़ bm_mc_result अणु
	काष्ठा अणु
		u8 verb;
		u8 bpid;
		u8 __reserved[62];
	पूर्ण;
	काष्ठा bm_buffer bufs[8];
पूर्ण;
#घोषणा BM_MCR_VERB_VBIT		0x80
#घोषणा BM_MCR_VERB_CMD_MASK		BM_MCC_VERB_CMD_MASK
#घोषणा BM_MCR_VERB_CMD_ACQUIRE		BM_MCC_VERB_CMD_ACQUIRE
#घोषणा BM_MCR_VERB_CMD_QUERY		BM_MCC_VERB_CMD_QUERY
#घोषणा BM_MCR_VERB_CMD_ERR_INVALID	0x60
#घोषणा BM_MCR_VERB_CMD_ERR_ECC		0x70
#घोषणा BM_MCR_VERB_ACQUIRE_BUFCOUNT	BM_MCC_VERB_ACQUIRE_BUFCOUNT /* 0..8 */
#घोषणा BM_MCR_TIMEOUT			10000 /* us */

काष्ठा bm_mc अणु
	काष्ठा bm_mc_command *cr;
	जोड़ bm_mc_result *rr;
	u8 rridx, vbit;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	क्रमागत अणु
		/* Can only be _mc_start()ed */
		mc_idle,
		/* Can only be _mc_commit()ed or _mc_पात()ed */
		mc_user,
		/* Can only be _mc_retry()ed */
		mc_hw
	पूर्ण state;
#पूर्ण_अगर
पूर्ण;

काष्ठा bm_addr अणु
	व्योम *ce;		/* cache-enabled */
	__be32 *ce_be;		/* Same as above but क्रम direct access */
	व्योम __iomem *ci;	/* cache-inhibited */
पूर्ण;

काष्ठा bm_portal अणु
	काष्ठा bm_addr addr;
	काष्ठा bm_rcr rcr;
	काष्ठा bm_mc mc;
पूर्ण ____cacheline_aligned;

/* Cache-inhibited रेजिस्टर access. */
अटल अंतरभूत u32 bm_in(काष्ठा bm_portal *p, u32 offset)
अणु
	वापस ioपढ़ो32be(p->addr.ci + offset);
पूर्ण

अटल अंतरभूत व्योम bm_out(काष्ठा bm_portal *p, u32 offset, u32 val)
अणु
	ioग_लिखो32be(val, p->addr.ci + offset);
पूर्ण

/* Cache Enabled Portal Access */
अटल अंतरभूत व्योम bm_cl_invalidate(काष्ठा bm_portal *p, u32 offset)
अणु
	dpaa_invalidate(p->addr.ce + offset);
पूर्ण

अटल अंतरभूत व्योम bm_cl_touch_ro(काष्ठा bm_portal *p, u32 offset)
अणु
	dpaa_touch_ro(p->addr.ce + offset);
पूर्ण

अटल अंतरभूत u32 bm_ce_in(काष्ठा bm_portal *p, u32 offset)
अणु
	वापस be32_to_cpu(*(p->addr.ce_be + (offset/4)));
पूर्ण

काष्ठा bman_portal अणु
	काष्ठा bm_portal p;
	/* पूर्णांकerrupt sources processed by portal_isr(), configurable */
	अचिन्हित दीर्घ irq_sources;
	/* probing समय config params क्रम cpu-affine portals */
	स्थिर काष्ठा bm_portal_config *config;
	अक्षर irqname[MAX_IRQNAME];
पूर्ण;

अटल cpumask_t affine_mask;
अटल DEFINE_SPINLOCK(affine_mask_lock);
अटल DEFINE_PER_CPU(काष्ठा bman_portal, bman_affine_portal);

अटल अंतरभूत काष्ठा bman_portal *get_affine_portal(व्योम)
अणु
	वापस &get_cpu_var(bman_affine_portal);
पूर्ण

अटल अंतरभूत व्योम put_affine_portal(व्योम)
अणु
	put_cpu_var(bman_affine_portal);
पूर्ण

/*
 * This object type refers to a pool, it isn't *the* pool. There may be
 * more than one such object per BMan buffer pool, eg. अगर dअगरferent users of the
 * pool are operating via dअगरferent portals.
 */
काष्ठा bman_pool अणु
	/* index of the buffer pool to encapsulate (0-63) */
	u32 bpid;
	/* Used क्रम hash-table admin when using depletion notअगरications. */
	काष्ठा bman_portal *portal;
	काष्ठा bman_pool *next;
पूर्ण;

अटल u32 poll_portal_slow(काष्ठा bman_portal *p, u32 is);

अटल irqवापस_t portal_isr(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा bman_portal *p = ptr;
	काष्ठा bm_portal *portal = &p->p;
	u32 clear = p->irq_sources;
	u32 is = bm_in(portal, BM_REG_ISR) & p->irq_sources;

	अगर (unlikely(!is))
		वापस IRQ_NONE;

	clear |= poll_portal_slow(p, is);
	bm_out(portal, BM_REG_ISR, clear);
	वापस IRQ_HANDLED;
पूर्ण

/* --- RCR API --- */

#घोषणा RCR_SHIFT	ilog2(माप(काष्ठा bm_rcr_entry))
#घोषणा RCR_CARRY	(uपूर्णांकptr_t)(BM_RCR_SIZE << RCR_SHIFT)

/* Bit-wise logic to wrap a ring poपूर्णांकer by clearing the "carry bit" */
अटल काष्ठा bm_rcr_entry *rcr_carryclear(काष्ठा bm_rcr_entry *p)
अणु
	uपूर्णांकptr_t addr = (uपूर्णांकptr_t)p;

	addr &= ~RCR_CARRY;

	वापस (काष्ठा bm_rcr_entry *)addr;
पूर्ण

#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
/* Bit-wise logic to convert a ring poपूर्णांकer to a ring index */
अटल पूर्णांक rcr_ptr2idx(काष्ठा bm_rcr_entry *e)
अणु
	वापस ((uपूर्णांकptr_t)e >> RCR_SHIFT) & (BM_RCR_SIZE - 1);
पूर्ण
#पूर्ण_अगर

/* Increment the 'cursor' ring pointer, taking 'vbit' पूर्णांकo account */
अटल अंतरभूत व्योम rcr_inc(काष्ठा bm_rcr *rcr)
अणु
	/* increment to the next RCR poपूर्णांकer and handle overflow and 'vbit' */
	काष्ठा bm_rcr_entry *partial = rcr->cursor + 1;

	rcr->cursor = rcr_carryclear(partial);
	अगर (partial != rcr->cursor)
		rcr->vbit ^= BM_RCR_VERB_VBIT;
पूर्ण

अटल पूर्णांक bm_rcr_get_avail(काष्ठा bm_portal *portal)
अणु
	काष्ठा bm_rcr *rcr = &portal->rcr;

	वापस rcr->available;
पूर्ण

अटल पूर्णांक bm_rcr_get_fill(काष्ठा bm_portal *portal)
अणु
	काष्ठा bm_rcr *rcr = &portal->rcr;

	वापस BM_RCR_SIZE - 1 - rcr->available;
पूर्ण

अटल व्योम bm_rcr_set_ithresh(काष्ठा bm_portal *portal, u8 ithresh)
अणु
	काष्ठा bm_rcr *rcr = &portal->rcr;

	rcr->ithresh = ithresh;
	bm_out(portal, BM_REG_RCR_ITR, ithresh);
पूर्ण

अटल व्योम bm_rcr_cce_prefetch(काष्ठा bm_portal *portal)
अणु
	__maybe_unused काष्ठा bm_rcr *rcr = &portal->rcr;

	DPAA_ASSERT(rcr->cmode == bm_rcr_cce);
	bm_cl_touch_ro(portal, BM_CL_RCR_CI_CENA);
पूर्ण

अटल u8 bm_rcr_cce_update(काष्ठा bm_portal *portal)
अणु
	काष्ठा bm_rcr *rcr = &portal->rcr;
	u8 dअगरf, old_ci = rcr->ci;

	DPAA_ASSERT(rcr->cmode == bm_rcr_cce);
	rcr->ci = bm_ce_in(portal, BM_CL_RCR_CI_CENA) & (BM_RCR_SIZE - 1);
	bm_cl_invalidate(portal, BM_CL_RCR_CI_CENA);
	dअगरf = dpaa_cyc_dअगरf(BM_RCR_SIZE, old_ci, rcr->ci);
	rcr->available += dअगरf;
	वापस dअगरf;
पूर्ण

अटल अंतरभूत काष्ठा bm_rcr_entry *bm_rcr_start(काष्ठा bm_portal *portal)
अणु
	काष्ठा bm_rcr *rcr = &portal->rcr;

	DPAA_ASSERT(!rcr->busy);
	अगर (!rcr->available)
		वापस शून्य;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	rcr->busy = 1;
#पूर्ण_अगर
	dpaa_zero(rcr->cursor);
	वापस rcr->cursor;
पूर्ण

अटल अंतरभूत व्योम bm_rcr_pvb_commit(काष्ठा bm_portal *portal, u8 myverb)
अणु
	काष्ठा bm_rcr *rcr = &portal->rcr;
	काष्ठा bm_rcr_entry *rcursor;

	DPAA_ASSERT(rcr->busy);
	DPAA_ASSERT(rcr->pmode == bm_rcr_pvb);
	DPAA_ASSERT(rcr->available >= 1);
	dma_wmb();
	rcursor = rcr->cursor;
	rcursor->_ncw_verb = myverb | rcr->vbit;
	dpaa_flush(rcursor);
	rcr_inc(rcr);
	rcr->available--;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	rcr->busy = 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक bm_rcr_init(काष्ठा bm_portal *portal, क्रमागत bm_rcr_pmode pmode,
		       क्रमागत bm_rcr_cmode cmode)
अणु
	काष्ठा bm_rcr *rcr = &portal->rcr;
	u32 cfg;
	u8 pi;

	rcr->ring = portal->addr.ce + BM_CL_RCR;
	rcr->ci = bm_in(portal, BM_REG_RCR_CI_CINH) & (BM_RCR_SIZE - 1);
	pi = bm_in(portal, BM_REG_RCR_PI_CINH) & (BM_RCR_SIZE - 1);
	rcr->cursor = rcr->ring + pi;
	rcr->vbit = (bm_in(portal, BM_REG_RCR_PI_CINH) & BM_RCR_SIZE) ?
		BM_RCR_VERB_VBIT : 0;
	rcr->available = BM_RCR_SIZE - 1
		- dpaa_cyc_dअगरf(BM_RCR_SIZE, rcr->ci, pi);
	rcr->ithresh = bm_in(portal, BM_REG_RCR_ITR);
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	rcr->busy = 0;
	rcr->pmode = pmode;
	rcr->cmode = cmode;
#पूर्ण_अगर
	cfg = (bm_in(portal, BM_REG_CFG) & 0xffffffe0)
		| (pmode & 0x3); /* BCSP_CFG::RPM */
	bm_out(portal, BM_REG_CFG, cfg);
	वापस 0;
पूर्ण

अटल व्योम bm_rcr_finish(काष्ठा bm_portal *portal)
अणु
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	काष्ठा bm_rcr *rcr = &portal->rcr;
	पूर्णांक i;

	DPAA_ASSERT(!rcr->busy);

	i = bm_in(portal, BM_REG_RCR_PI_CINH) & (BM_RCR_SIZE - 1);
	अगर (i != rcr_ptr2idx(rcr->cursor))
		pr_crit("losing uncommitted RCR entries\n");

	i = bm_in(portal, BM_REG_RCR_CI_CINH) & (BM_RCR_SIZE - 1);
	अगर (i != rcr->ci)
		pr_crit("missing existing RCR completions\n");
	अगर (rcr->ci != rcr_ptr2idx(rcr->cursor))
		pr_crit("RCR destroyed unquiesced\n");
#पूर्ण_अगर
पूर्ण

/* --- Management command API --- */
अटल पूर्णांक bm_mc_init(काष्ठा bm_portal *portal)
अणु
	काष्ठा bm_mc *mc = &portal->mc;

	mc->cr = portal->addr.ce + BM_CL_CR;
	mc->rr = portal->addr.ce + BM_CL_RR0;
	mc->rridx = (mc->cr->_ncw_verb & BM_MCC_VERB_VBIT) ?
		    0 : 1;
	mc->vbit = mc->rridx ? BM_MCC_VERB_VBIT : 0;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	mc->state = mc_idle;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम bm_mc_finish(काष्ठा bm_portal *portal)
अणु
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	काष्ठा bm_mc *mc = &portal->mc;

	DPAA_ASSERT(mc->state == mc_idle);
	अगर (mc->state != mc_idle)
		pr_crit("Losing incomplete MC command\n");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत काष्ठा bm_mc_command *bm_mc_start(काष्ठा bm_portal *portal)
अणु
	काष्ठा bm_mc *mc = &portal->mc;

	DPAA_ASSERT(mc->state == mc_idle);
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	mc->state = mc_user;
#पूर्ण_अगर
	dpaa_zero(mc->cr);
	वापस mc->cr;
पूर्ण

अटल अंतरभूत व्योम bm_mc_commit(काष्ठा bm_portal *portal, u8 myverb)
अणु
	काष्ठा bm_mc *mc = &portal->mc;
	जोड़ bm_mc_result *rr = mc->rr + mc->rridx;

	DPAA_ASSERT(mc->state == mc_user);
	dma_wmb();
	mc->cr->_ncw_verb = myverb | mc->vbit;
	dpaa_flush(mc->cr);
	dpaa_invalidate_touch_ro(rr);
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	mc->state = mc_hw;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत जोड़ bm_mc_result *bm_mc_result(काष्ठा bm_portal *portal)
अणु
	काष्ठा bm_mc *mc = &portal->mc;
	जोड़ bm_mc_result *rr = mc->rr + mc->rridx;

	DPAA_ASSERT(mc->state == mc_hw);
	/*
	 * The inactive response रेजिस्टर's verb byte always वापसs zero until
	 * its command is submitted and completed. This includes the valid-bit,
	 * in हाल you were wondering...
	 */
	अगर (!rr->verb) अणु
		dpaa_invalidate_touch_ro(rr);
		वापस शून्य;
	पूर्ण
	mc->rridx ^= 1;
	mc->vbit ^= BM_MCC_VERB_VBIT;
#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
	mc->state = mc_idle;
#पूर्ण_अगर
	वापस rr;
पूर्ण

अटल अंतरभूत पूर्णांक bm_mc_result_समयout(काष्ठा bm_portal *portal,
				       जोड़ bm_mc_result **mcr)
अणु
	पूर्णांक समयout = BM_MCR_TIMEOUT;

	करो अणु
		*mcr = bm_mc_result(portal);
		अगर (*mcr)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (--समयout);

	वापस समयout;
पूर्ण

/* Disable all BSCN पूर्णांकerrupts क्रम the portal */
अटल व्योम bm_isr_bscn_disable(काष्ठा bm_portal *portal)
अणु
	bm_out(portal, BM_REG_SCN(0), 0);
	bm_out(portal, BM_REG_SCN(1), 0);
पूर्ण

अटल पूर्णांक bman_create_portal(काष्ठा bman_portal *portal,
			      स्थिर काष्ठा bm_portal_config *c)
अणु
	काष्ठा bm_portal *p;
	पूर्णांक ret;

	p = &portal->p;
	/*
	 * prep the low-level portal काष्ठा with the mapped addresses from the
	 * config, everything that follows depends on it and "config" is more
	 * क्रम (de)reference...
	 */
	p->addr.ce = c->addr_virt_ce;
	p->addr.ce_be = c->addr_virt_ce;
	p->addr.ci = c->addr_virt_ci;
	अगर (bm_rcr_init(p, bm_rcr_pvb, bm_rcr_cce)) अणु
		dev_err(c->dev, "RCR initialisation failed\n");
		जाओ fail_rcr;
	पूर्ण
	अगर (bm_mc_init(p)) अणु
		dev_err(c->dev, "MC initialisation failed\n");
		जाओ fail_mc;
	पूर्ण
	/*
	 * Default to all BPIDs disabled, we enable as required at
	 * run-समय.
	 */
	bm_isr_bscn_disable(p);

	/* Write-to-clear any stale पूर्णांकerrupt status bits */
	bm_out(p, BM_REG_ISDR, 0xffffffff);
	portal->irq_sources = 0;
	bm_out(p, BM_REG_IER, 0);
	bm_out(p, BM_REG_ISR, 0xffffffff);
	snम_लिखो(portal->irqname, MAX_IRQNAME, IRQNAME, c->cpu);
	अगर (request_irq(c->irq, portal_isr, 0, portal->irqname,	portal)) अणु
		dev_err(c->dev, "request_irq() failed\n");
		जाओ fail_irq;
	पूर्ण

	अगर (dpaa_set_portal_irq_affinity(c->dev, c->irq, c->cpu))
		जाओ fail_affinity;

	/* Need RCR to be empty beक्रमe continuing */
	ret = bm_rcr_get_fill(p);
	अगर (ret) अणु
		dev_err(c->dev, "RCR unclean\n");
		जाओ fail_rcr_empty;
	पूर्ण
	/* Success */
	portal->config = c;

	bm_out(p, BM_REG_ISDR, 0);
	bm_out(p, BM_REG_IIR, 0);

	वापस 0;

fail_rcr_empty:
fail_affinity:
	मुक्त_irq(c->irq, portal);
fail_irq:
	bm_mc_finish(p);
fail_mc:
	bm_rcr_finish(p);
fail_rcr:
	वापस -EIO;
पूर्ण

काष्ठा bman_portal *bman_create_affine_portal(स्थिर काष्ठा bm_portal_config *c)
अणु
	काष्ठा bman_portal *portal;
	पूर्णांक err;

	portal = &per_cpu(bman_affine_portal, c->cpu);
	err = bman_create_portal(portal, c);
	अगर (err)
		वापस शून्य;

	spin_lock(&affine_mask_lock);
	cpumask_set_cpu(c->cpu, &affine_mask);
	spin_unlock(&affine_mask_lock);

	वापस portal;
पूर्ण

अटल u32 poll_portal_slow(काष्ठा bman_portal *p, u32 is)
अणु
	u32 ret = is;

	अगर (is & BM_PIRQ_RCRI) अणु
		bm_rcr_cce_update(&p->p);
		bm_rcr_set_ithresh(&p->p, 0);
		bm_out(&p->p, BM_REG_ISR, BM_PIRQ_RCRI);
		is &= ~BM_PIRQ_RCRI;
	पूर्ण

	/* There should be no status रेजिस्टर bits left undefined */
	DPAA_ASSERT(!is);
	वापस ret;
पूर्ण

पूर्णांक bman_p_irqsource_add(काष्ठा bman_portal *p, u32 bits)
अणु
	अचिन्हित दीर्घ irqflags;

	local_irq_save(irqflags);
	p->irq_sources |= bits & BM_PIRQ_VISIBLE;
	bm_out(&p->p, BM_REG_IER, p->irq_sources);
	local_irq_restore(irqflags);
	वापस 0;
पूर्ण

पूर्णांक bm_shutकरोwn_pool(u32 bpid)
अणु
	पूर्णांक err = 0;
	काष्ठा bm_mc_command *bm_cmd;
	जोड़ bm_mc_result *bm_res;


	काष्ठा bman_portal *p = get_affine_portal();
	जबतक (1) अणु
		/* Acquire buffers until empty */
		bm_cmd = bm_mc_start(&p->p);
		bm_cmd->bpid = bpid;
		bm_mc_commit(&p->p, BM_MCC_VERB_CMD_ACQUIRE | 1);
		अगर (!bm_mc_result_समयout(&p->p, &bm_res)) अणु
			pr_crit("BMan Acquire Command timedout\n");
			err = -ETIMEDOUT;
			जाओ करोne;
		पूर्ण
		अगर (!(bm_res->verb & BM_MCR_VERB_ACQUIRE_BUFCOUNT)) अणु
			/* Pool is empty */
			जाओ करोne;
		पूर्ण
	पूर्ण
करोne:
	put_affine_portal();
	वापस err;
पूर्ण

काष्ठा gen_pool *bm_bpalloc;

अटल पूर्णांक bm_alloc_bpid_range(u32 *result, u32 count)
अणु
	अचिन्हित दीर्घ addr;

	addr = gen_pool_alloc(bm_bpalloc, count);
	अगर (!addr)
		वापस -ENOMEM;

	*result = addr & ~DPAA_GENALLOC_OFF;

	वापस 0;
पूर्ण

अटल पूर्णांक bm_release_bpid(u32 bpid)
अणु
	पूर्णांक ret;

	ret = bm_shutकरोwn_pool(bpid);
	अगर (ret) अणु
		pr_debug("BPID %d leaked\n", bpid);
		वापस ret;
	पूर्ण

	gen_pool_मुक्त(bm_bpalloc, bpid | DPAA_GENALLOC_OFF, 1);
	वापस 0;
पूर्ण

काष्ठा bman_pool *bman_new_pool(व्योम)
अणु
	काष्ठा bman_pool *pool = शून्य;
	u32 bpid;

	अगर (bm_alloc_bpid_range(&bpid, 1))
		वापस शून्य;

	pool = kदो_स्मृति(माप(*pool), GFP_KERNEL);
	अगर (!pool)
		जाओ err;

	pool->bpid = bpid;

	वापस pool;
err:
	bm_release_bpid(bpid);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(bman_new_pool);

व्योम bman_मुक्त_pool(काष्ठा bman_pool *pool)
अणु
	bm_release_bpid(pool->bpid);

	kमुक्त(pool);
पूर्ण
EXPORT_SYMBOL(bman_मुक्त_pool);

पूर्णांक bman_get_bpid(स्थिर काष्ठा bman_pool *pool)
अणु
	वापस pool->bpid;
पूर्ण
EXPORT_SYMBOL(bman_get_bpid);

अटल व्योम update_rcr_ci(काष्ठा bman_portal *p, पूर्णांक avail)
अणु
	अगर (avail)
		bm_rcr_cce_prefetch(&p->p);
	अन्यथा
		bm_rcr_cce_update(&p->p);
पूर्ण

पूर्णांक bman_release(काष्ठा bman_pool *pool, स्थिर काष्ठा bm_buffer *bufs, u8 num)
अणु
	काष्ठा bman_portal *p;
	काष्ठा bm_rcr_entry *r;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक avail, समयout = 1000; /* 1ms */
	पूर्णांक i = num - 1;

	DPAA_ASSERT(num > 0 && num <= 8);

	करो अणु
		p = get_affine_portal();
		local_irq_save(irqflags);
		avail = bm_rcr_get_avail(&p->p);
		अगर (avail < 2)
			update_rcr_ci(p, avail);
		r = bm_rcr_start(&p->p);
		local_irq_restore(irqflags);
		put_affine_portal();
		अगर (likely(r))
			अवरोध;

		udelay(1);
	पूर्ण जबतक (--समयout);

	अगर (unlikely(!समयout))
		वापस -ETIMEDOUT;

	p = get_affine_portal();
	local_irq_save(irqflags);
	/*
	 * we can copy all but the first entry, as this can trigger badness
	 * with the valid-bit
	 */
	bm_buffer_set64(r->bufs, bm_buffer_get64(bufs));
	bm_buffer_set_bpid(r->bufs, pool->bpid);
	अगर (i)
		स_नकल(&r->bufs[1], &bufs[1], i * माप(bufs[0]));

	bm_rcr_pvb_commit(&p->p, BM_RCR_VERB_CMD_BPID_SINGLE |
			  (num & BM_RCR_VERB_BUFCOUNT_MASK));

	local_irq_restore(irqflags);
	put_affine_portal();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(bman_release);

पूर्णांक bman_acquire(काष्ठा bman_pool *pool, काष्ठा bm_buffer *bufs, u8 num)
अणु
	काष्ठा bman_portal *p = get_affine_portal();
	काष्ठा bm_mc_command *mcc;
	जोड़ bm_mc_result *mcr;
	पूर्णांक ret;

	DPAA_ASSERT(num > 0 && num <= 8);

	mcc = bm_mc_start(&p->p);
	mcc->bpid = pool->bpid;
	bm_mc_commit(&p->p, BM_MCC_VERB_CMD_ACQUIRE |
		     (num & BM_MCC_VERB_ACQUIRE_BUFCOUNT));
	अगर (!bm_mc_result_समयout(&p->p, &mcr)) अणु
		put_affine_portal();
		pr_crit("BMan Acquire Timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण
	ret = mcr->verb & BM_MCR_VERB_ACQUIRE_BUFCOUNT;
	अगर (bufs)
		स_नकल(&bufs[0], &mcr->bufs[0], num * माप(bufs[0]));

	put_affine_portal();
	अगर (ret != num)
		ret = -ENOMEM;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(bman_acquire);

स्थिर काष्ठा bm_portal_config *
bman_get_bm_portal_config(स्थिर काष्ठा bman_portal *portal)
अणु
	वापस portal->config;
पूर्ण
