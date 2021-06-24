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

#समावेश "dpaa_sys.h"

#समावेश <soc/fsl/qman.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/iommu.h>

#अगर defined(CONFIG_FSL_PAMU)
#समावेश <यंत्र/fsl_pamu_stash.h>
#पूर्ण_अगर

काष्ठा qm_mcr_querywq अणु
	u8 verb;
	u8 result;
	u16 channel_wq; /* ignores wq (3 lsbits): _res[0-2] */
	u8 __reserved[28];
	u32 wq_len[8];
पूर्ण __packed;

अटल अंतरभूत u16 qm_mcr_querywq_get_chan(स्थिर काष्ठा qm_mcr_querywq *wq)
अणु
	वापस wq->channel_wq >> 3;
पूर्ण

काष्ठा __qm_mcr_querycongestion अणु
	u32 state[8];
पूर्ण;

/* "Query Congestion Group State" */
काष्ठा qm_mcr_querycongestion अणु
	u8 verb;
	u8 result;
	u8 __reserved[30];
	/* Access this काष्ठा using qman_cgrs_get() */
	काष्ठा __qm_mcr_querycongestion state;
पूर्ण __packed;

/* "Query CGR" */
काष्ठा qm_mcr_querycgr अणु
	u8 verb;
	u8 result;
	u16 __reserved1;
	काष्ठा __qm_mc_cgr cgr; /* CGR fields */
	u8 __reserved2[6];
	u8 i_bcnt_hi;	/* high 8-bits of 40-bit "Instant" */
	__be32 i_bcnt_lo;	/* low 32-bits of 40-bit */
	u8 __reserved3[3];
	u8 a_bcnt_hi;	/* high 8-bits of 40-bit "Average" */
	__be32 a_bcnt_lo;	/* low 32-bits of 40-bit */
	__be32 cscn_targ_swp[4];
पूर्ण __packed;

अटल अंतरभूत u64 qm_mcr_querycgr_i_get64(स्थिर काष्ठा qm_mcr_querycgr *q)
अणु
	वापस ((u64)q->i_bcnt_hi << 32) | be32_to_cpu(q->i_bcnt_lo);
पूर्ण
अटल अंतरभूत u64 qm_mcr_querycgr_a_get64(स्थिर काष्ठा qm_mcr_querycgr *q)
अणु
	वापस ((u64)q->a_bcnt_hi << 32) | be32_to_cpu(q->a_bcnt_lo);
पूर्ण

/* Congestion Groups */

/*
 * This wrapper represents a bit-array क्रम the state of the 256 QMan congestion
 * groups. Is also used as a *mask* क्रम congestion groups, eg. so we ignore
 * those that करोn't concern us. We harness the काष्ठाure and accessor details
 * alपढ़ोy used in the management command to query congestion groups.
 */
#घोषणा CGR_BITS_PER_WORD 5
#घोषणा CGR_WORD(x)	((x) >> CGR_BITS_PER_WORD)
#घोषणा CGR_BIT(x)	(BIT(31) >> ((x) & 0x1f))
#घोषणा CGR_NUM	(माप(काष्ठा __qm_mcr_querycongestion) << 3)

काष्ठा qman_cgrs अणु
	काष्ठा __qm_mcr_querycongestion q;
पूर्ण;

अटल अंतरभूत व्योम qman_cgrs_init(काष्ठा qman_cgrs *c)
अणु
	स_रखो(c, 0, माप(*c));
पूर्ण

अटल अंतरभूत व्योम qman_cgrs_fill(काष्ठा qman_cgrs *c)
अणु
	स_रखो(c, 0xff, माप(*c));
पूर्ण

अटल अंतरभूत पूर्णांक qman_cgrs_get(काष्ठा qman_cgrs *c, u8 cgr)
अणु
	वापस c->q.state[CGR_WORD(cgr)] & CGR_BIT(cgr);
पूर्ण

अटल अंतरभूत व्योम qman_cgrs_cp(काष्ठा qman_cgrs *dest,
				स्थिर काष्ठा qman_cgrs *src)
अणु
	*dest = *src;
पूर्ण

अटल अंतरभूत व्योम qman_cgrs_and(काष्ठा qman_cgrs *dest,
			स्थिर काष्ठा qman_cgrs *a, स्थिर काष्ठा qman_cgrs *b)
अणु
	पूर्णांक ret;
	u32 *_d = dest->q.state;
	स्थिर u32 *_a = a->q.state;
	स्थिर u32 *_b = b->q.state;

	क्रम (ret = 0; ret < 8; ret++)
		*_d++ = *_a++ & *_b++;
पूर्ण

अटल अंतरभूत व्योम qman_cgrs_xor(काष्ठा qman_cgrs *dest,
			स्थिर काष्ठा qman_cgrs *a, स्थिर काष्ठा qman_cgrs *b)
अणु
	पूर्णांक ret;
	u32 *_d = dest->q.state;
	स्थिर u32 *_a = a->q.state;
	स्थिर u32 *_b = b->q.state;

	क्रम (ret = 0; ret < 8; ret++)
		*_d++ = *_a++ ^ *_b++;
पूर्ण

व्योम qman_init_cgr_all(व्योम);

काष्ठा qm_portal_config अणु
	/* Portal addresses */
	व्योम *addr_virt_ce;
	व्योम __iomem *addr_virt_ci;
	काष्ठा device *dev;
	काष्ठा iommu_करोमुख्य *iommu_करोमुख्य;
	/* Allow these to be joined in lists */
	काष्ठा list_head list;
	/* User-visible portal configuration settings */
	/* portal is affined to this cpu */
	पूर्णांक cpu;
	/* portal पूर्णांकerrupt line */
	पूर्णांक irq;
	/*
	 * the portal's dedicated channel id, used initialising
	 * frame queues to target this portal when scheduled
	 */
	u16 channel;
	/*
	 * mask of pool channels this portal has dequeue access to
	 * (using QM_SDQCR_CHANNELS_POOL(n) क्रम the biपंचांगask)
	 */
	u32 pools;
पूर्ण;

/* Revision info (क्रम errata and feature handling) */
#घोषणा QMAN_REV11 0x0101
#घोषणा QMAN_REV12 0x0102
#घोषणा QMAN_REV20 0x0200
#घोषणा QMAN_REV30 0x0300
#घोषणा QMAN_REV31 0x0301
#घोषणा QMAN_REV32 0x0302
बाह्य u16 qman_ip_rev; /* 0 अगर uninitialised, otherwise QMAN_REVx */

#घोषणा QM_FQID_RANGE_START 1 /* FQID 0 reserved क्रम पूर्णांकernal use */
बाह्य काष्ठा gen_pool *qm_fqalloc; /* FQID allocator */
बाह्य काष्ठा gen_pool *qm_qpalloc; /* pool-channel allocator */
बाह्य काष्ठा gen_pool *qm_cgralloc; /* CGR ID allocator */
u32 qm_get_pools_sdqcr(व्योम);

पूर्णांक qman_wq_alloc(व्योम);
#अगर_घोषित CONFIG_FSL_PAMU
#घोषणा qman_liodn_fixup __qman_liodn_fixup
#अन्यथा
अटल अंतरभूत व्योम qman_liodn_fixup(u16 channel)
अणु
पूर्ण
#पूर्ण_अगर
व्योम __qman_liodn_fixup(u16 channel);
व्योम qman_set_sdest(u16 channel, अचिन्हित पूर्णांक cpu_idx);

काष्ठा qman_portal *qman_create_affine_portal(
			स्थिर काष्ठा qm_portal_config *config,
			स्थिर काष्ठा qman_cgrs *cgrs);
स्थिर काष्ठा qm_portal_config *qman_destroy_affine_portal(व्योम);

/*
 * qman_query_fq - Queries FQD fields (via h/w query command)
 * @fq: the frame queue object to be queried
 * @fqd: storage क्रम the queried FQD fields
 */
पूर्णांक qman_query_fq(काष्ठा qman_fq *fq, काष्ठा qm_fqd *fqd);

पूर्णांक qman_alloc_fq_table(u32 num_fqids);

/*   QMan s/w corenet portal, low-level i/face	 */

/*
 * For qm_dqrr_sdqcr_set(); Choose one SOURCE. Choose one COUNT. Choose one
 * dequeue TYPE. Choose TOKEN (8-bit).
 * If SOURCE == CHANNELS,
 *   Choose CHANNELS_DEDICATED and/or CHANNELS_POOL(n).
 *   You can choose DEDICATED_PRECEDENCE अगर the portal channel should have
 *   priority.
 * If SOURCE == SPECIFICWQ,
 *     Either select the work-queue ID with SPECIFICWQ_WQ(), or select the
 *     channel (SPECIFICWQ_DEDICATED or SPECIFICWQ_POOL()) and specअगरy the
 *     work-queue priority (0-7) with SPECIFICWQ_WQ() - either way, you get the
 *     same value.
 */
#घोषणा QM_SDQCR_SOURCE_CHANNELS	0x0
#घोषणा QM_SDQCR_SOURCE_SPECIFICWQ	0x40000000
#घोषणा QM_SDQCR_COUNT_EXACT1		0x0
#घोषणा QM_SDQCR_COUNT_UPTO3		0x20000000
#घोषणा QM_SDQCR_DEDICATED_PRECEDENCE	0x10000000
#घोषणा QM_SDQCR_TYPE_MASK		0x03000000
#घोषणा QM_SDQCR_TYPE_शून्य		0x0
#घोषणा QM_SDQCR_TYPE_PRIO_QOS		0x01000000
#घोषणा QM_SDQCR_TYPE_ACTIVE_QOS	0x02000000
#घोषणा QM_SDQCR_TYPE_ACTIVE		0x03000000
#घोषणा QM_SDQCR_TOKEN_MASK		0x00ff0000
#घोषणा QM_SDQCR_TOKEN_SET(v)		(((v) & 0xff) << 16)
#घोषणा QM_SDQCR_TOKEN_GET(v)		(((v) >> 16) & 0xff)
#घोषणा QM_SDQCR_CHANNELS_DEDICATED	0x00008000
#घोषणा QM_SDQCR_SPECIFICWQ_MASK	0x000000f7
#घोषणा QM_SDQCR_SPECIFICWQ_DEDICATED	0x00000000
#घोषणा QM_SDQCR_SPECIFICWQ_POOL(n)	((n) << 4)
#घोषणा QM_SDQCR_SPECIFICWQ_WQ(n)	(n)

/* For qm_dqrr_vdqcr_set(): use FQID(n) to fill in the frame queue ID */
#घोषणा QM_VDQCR_FQID_MASK		0x00ffffff
#घोषणा QM_VDQCR_FQID(n)		((n) & QM_VDQCR_FQID_MASK)

/*
 * Used by all portal पूर्णांकerrupt रेजिस्टरs except 'inhibit'
 * Channels with frame availability
 */
#घोषणा QM_PIRQ_DQAVAIL	0x0000ffff

/* The DQAVAIL पूर्णांकerrupt fields अवरोध करोwn पूर्णांकo these bits; */
#घोषणा QM_DQAVAIL_PORTAL	0x8000		/* Portal channel */
#घोषणा QM_DQAVAIL_POOL(n)	(0x8000 >> (n))	/* Pool channel, n==[1..15] */
#घोषणा QM_DQAVAIL_MASK		0xffff
/* This mask contains all the "irqsource" bits visible to API users */
#घोषणा QM_PIRQ_VISIBLE	(QM_PIRQ_SLOW | QM_PIRQ_DQRI)

बाह्य काष्ठा qman_portal *affine_portals[NR_CPUS];
बाह्य काष्ठा qman_portal *qman_dma_portal;
स्थिर काष्ठा qm_portal_config *qman_get_qm_portal_config(
						काष्ठा qman_portal *portal);

अचिन्हित पूर्णांक qm_get_fqid_maxcnt(व्योम);

पूर्णांक qman_shutकरोwn_fq(u32 fqid);

पूर्णांक qman_requires_cleanup(व्योम);
व्योम qman_करोne_cleanup(व्योम);
व्योम qman_enable_irqs(व्योम);
