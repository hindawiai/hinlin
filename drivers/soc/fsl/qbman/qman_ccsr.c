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

u16 qman_ip_rev;
EXPORT_SYMBOL(qman_ip_rev);
u16 qm_channel_pool1 = QMAN_CHANNEL_POOL1;
EXPORT_SYMBOL(qm_channel_pool1);
u16 qm_channel_caam = QMAN_CHANNEL_CAAM;
EXPORT_SYMBOL(qm_channel_caam);

/* Register offsets */
#घोषणा REG_QCSP_LIO_CFG(n)	(0x0000 + ((n) * 0x10))
#घोषणा REG_QCSP_IO_CFG(n)	(0x0004 + ((n) * 0x10))
#घोषणा REG_QCSP_DD_CFG(n)	(0x000c + ((n) * 0x10))
#घोषणा REG_DD_CFG		0x0200
#घोषणा REG_DCP_CFG(n)		(0x0300 + ((n) * 0x10))
#घोषणा REG_DCP_DD_CFG(n)	(0x0304 + ((n) * 0x10))
#घोषणा REG_DCP_DLM_AVG(n)	(0x030c + ((n) * 0x10))
#घोषणा REG_PFDR_FPC		0x0400
#घोषणा REG_PFDR_FP_HEAD	0x0404
#घोषणा REG_PFDR_FP_TAIL	0x0408
#घोषणा REG_PFDR_FP_LWIT	0x0410
#घोषणा REG_PFDR_CFG		0x0414
#घोषणा REG_SFDR_CFG		0x0500
#घोषणा REG_SFDR_IN_USE		0x0504
#घोषणा REG_WQ_CS_CFG(n)	(0x0600 + ((n) * 0x04))
#घोषणा REG_WQ_DEF_ENC_WQID	0x0630
#घोषणा REG_WQ_SC_DD_CFG(n)	(0x640 + ((n) * 0x04))
#घोषणा REG_WQ_PC_DD_CFG(n)	(0x680 + ((n) * 0x04))
#घोषणा REG_WQ_DC0_DD_CFG(n)	(0x6c0 + ((n) * 0x04))
#घोषणा REG_WQ_DC1_DD_CFG(n)	(0x700 + ((n) * 0x04))
#घोषणा REG_WQ_DCn_DD_CFG(n)	(0x6c0 + ((n) * 0x40)) /* n=2,3 */
#घोषणा REG_CM_CFG		0x0800
#घोषणा REG_ECSR		0x0a00
#घोषणा REG_ECIR		0x0a04
#घोषणा REG_EADR		0x0a08
#घोषणा REG_ECIR2		0x0a0c
#घोषणा REG_EDATA(n)		(0x0a10 + ((n) * 0x04))
#घोषणा REG_SBEC(n)		(0x0a80 + ((n) * 0x04))
#घोषणा REG_MCR			0x0b00
#घोषणा REG_MCP(n)		(0x0b04 + ((n) * 0x04))
#घोषणा REG_MISC_CFG		0x0be0
#घोषणा REG_HID_CFG		0x0bf0
#घोषणा REG_IDLE_STAT		0x0bf4
#घोषणा REG_IP_REV_1		0x0bf8
#घोषणा REG_IP_REV_2		0x0bfc
#घोषणा REG_FQD_BARE		0x0c00
#घोषणा REG_PFDR_BARE		0x0c20
#घोषणा REG_offset_BAR		0x0004	/* relative to REG_[FQD|PFDR]_BARE */
#घोषणा REG_offset_AR		0x0010	/* relative to REG_[FQD|PFDR]_BARE */
#घोषणा REG_QCSP_BARE		0x0c80
#घोषणा REG_QCSP_BAR		0x0c84
#घोषणा REG_CI_SCHED_CFG	0x0d00
#घोषणा REG_SRCIDR		0x0d04
#घोषणा REG_LIODNR		0x0d08
#घोषणा REG_CI_RLM_AVG		0x0d14
#घोषणा REG_ERR_ISR		0x0e00
#घोषणा REG_ERR_IER		0x0e04
#घोषणा REG_REV3_QCSP_LIO_CFG(n)	(0x1000 + ((n) * 0x10))
#घोषणा REG_REV3_QCSP_IO_CFG(n)	(0x1004 + ((n) * 0x10))
#घोषणा REG_REV3_QCSP_DD_CFG(n)	(0x100c + ((n) * 0x10))

/* Assists क्रम QMAN_MCR */
#घोषणा MCR_INIT_PFDR		0x01000000
#घोषणा MCR_get_rslt(v)		(u8)((v) >> 24)
#घोषणा MCR_rslt_idle(r)	(!(r) || ((r) >= 0xf0))
#घोषणा MCR_rslt_ok(r)		((r) == 0xf0)
#घोषणा MCR_rslt_eaccess(r)	((r) == 0xf8)
#घोषणा MCR_rslt_inval(r)	((r) == 0xff)

/*
 * Corenet initiator settings. Stash request queues are 4-deep to match cores
 * ability to snarf. Stash priority is 3, other priorities are 2.
 */
#घोषणा QM_CI_SCHED_CFG_SRCCIV		4
#घोषणा QM_CI_SCHED_CFG_SRQ_W		3
#घोषणा QM_CI_SCHED_CFG_RW_W		2
#घोषणा QM_CI_SCHED_CFG_BMAN_W		2
/* ग_लिखो SRCCIV enable */
#घोषणा QM_CI_SCHED_CFG_SRCCIV_EN	BIT(31)

/* Follows WQ_CS_CFG0-5 */
क्रमागत qm_wq_class अणु
	qm_wq_portal = 0,
	qm_wq_pool = 1,
	qm_wq_fman0 = 2,
	qm_wq_fman1 = 3,
	qm_wq_caam = 4,
	qm_wq_pme = 5,
	qm_wq_first = qm_wq_portal,
	qm_wq_last = qm_wq_pme
पूर्ण;

/* Follows FQD_[BARE|BAR|AR] and PFDR_[BARE|BAR|AR] */
क्रमागत qm_memory अणु
	qm_memory_fqd,
	qm_memory_pfdr
पूर्ण;

/* Used by all error पूर्णांकerrupt रेजिस्टरs except 'inhibit' */
#घोषणा QM_EIRQ_CIDE	0x20000000	/* Corenet Initiator Data Error */
#घोषणा QM_EIRQ_CTDE	0x10000000	/* Corenet Target Data Error */
#घोषणा QM_EIRQ_CITT	0x08000000	/* Corenet Invalid Target Transaction */
#घोषणा QM_EIRQ_PLWI	0x04000000	/* PFDR Low Watermark */
#घोषणा QM_EIRQ_MBEI	0x02000000	/* Multi-bit ECC Error */
#घोषणा QM_EIRQ_SBEI	0x01000000	/* Single-bit ECC Error */
#घोषणा QM_EIRQ_PEBI	0x00800000	/* PFDR Enqueues Blocked Interrupt */
#घोषणा QM_EIRQ_IFSI	0x00020000	/* Invalid FQ Flow Control State */
#घोषणा QM_EIRQ_ICVI	0x00010000	/* Invalid Command Verb */
#घोषणा QM_EIRQ_IDDI	0x00000800	/* Invalid Dequeue (Direct-connect) */
#घोषणा QM_EIRQ_IDFI	0x00000400	/* Invalid Dequeue FQ */
#घोषणा QM_EIRQ_IDSI	0x00000200	/* Invalid Dequeue Source */
#घोषणा QM_EIRQ_IDQI	0x00000100	/* Invalid Dequeue Queue */
#घोषणा QM_EIRQ_IECE	0x00000010	/* Invalid Enqueue Configuration */
#घोषणा QM_EIRQ_IEOI	0x00000008	/* Invalid Enqueue Overflow */
#घोषणा QM_EIRQ_IESI	0x00000004	/* Invalid Enqueue State */
#घोषणा QM_EIRQ_IECI	0x00000002	/* Invalid Enqueue Channel */
#घोषणा QM_EIRQ_IEQI	0x00000001	/* Invalid Enqueue Queue */

/* QMAN_ECIR valid error bit */
#घोषणा PORTAL_ECSR_ERR	(QM_EIRQ_IEQI | QM_EIRQ_IESI | QM_EIRQ_IEOI | \
			 QM_EIRQ_IDQI | QM_EIRQ_IDSI | QM_EIRQ_IDFI | \
			 QM_EIRQ_IDDI | QM_EIRQ_ICVI | QM_EIRQ_IFSI)
#घोषणा FQID_ECSR_ERR	(QM_EIRQ_IEQI | QM_EIRQ_IECI | QM_EIRQ_IESI | \
			 QM_EIRQ_IEOI | QM_EIRQ_IDQI | QM_EIRQ_IDFI | \
			 QM_EIRQ_IFSI)

काष्ठा qm_ecir अणु
	u32 info; /* res[30-31], ptyp[29], pnum[24-28], fqid[0-23] */
पूर्ण;

अटल bool qm_ecir_is_dcp(स्थिर काष्ठा qm_ecir *p)
अणु
	वापस p->info & BIT(29);
पूर्ण

अटल पूर्णांक qm_ecir_get_pnum(स्थिर काष्ठा qm_ecir *p)
अणु
	वापस (p->info >> 24) & 0x1f;
पूर्ण

अटल पूर्णांक qm_ecir_get_fqid(स्थिर काष्ठा qm_ecir *p)
अणु
	वापस p->info & (BIT(24) - 1);
पूर्ण

काष्ठा qm_ecir2 अणु
	u32 info; /* ptyp[31], res[10-30], pnum[0-9] */
पूर्ण;

अटल bool qm_ecir2_is_dcp(स्थिर काष्ठा qm_ecir2 *p)
अणु
	वापस p->info & BIT(31);
पूर्ण

अटल पूर्णांक qm_ecir2_get_pnum(स्थिर काष्ठा qm_ecir2 *p)
अणु
	वापस p->info & (BIT(10) - 1);
पूर्ण

काष्ठा qm_eadr अणु
	u32 info; /* memid[24-27], eadr[0-11] */
		  /* v3: memid[24-28], eadr[0-15] */
पूर्ण;

अटल पूर्णांक qm_eadr_get_memid(स्थिर काष्ठा qm_eadr *p)
अणु
	वापस (p->info >> 24) & 0xf;
पूर्ण

अटल पूर्णांक qm_eadr_get_eadr(स्थिर काष्ठा qm_eadr *p)
अणु
	वापस p->info & (BIT(12) - 1);
पूर्ण

अटल पूर्णांक qm_eadr_v3_get_memid(स्थिर काष्ठा qm_eadr *p)
अणु
	वापस (p->info >> 24) & 0x1f;
पूर्ण

अटल पूर्णांक qm_eadr_v3_get_eadr(स्थिर काष्ठा qm_eadr *p)
अणु
	वापस p->info & (BIT(16) - 1);
पूर्ण

काष्ठा qman_hwerr_txt अणु
	u32 mask;
	स्थिर अक्षर *txt;
पूर्ण;


अटल स्थिर काष्ठा qman_hwerr_txt qman_hwerr_txts[] = अणु
	अणु QM_EIRQ_CIDE, "Corenet Initiator Data Error" पूर्ण,
	अणु QM_EIRQ_CTDE, "Corenet Target Data Error" पूर्ण,
	अणु QM_EIRQ_CITT, "Corenet Invalid Target Transaction" पूर्ण,
	अणु QM_EIRQ_PLWI, "PFDR Low Watermark" पूर्ण,
	अणु QM_EIRQ_MBEI, "Multi-bit ECC Error" पूर्ण,
	अणु QM_EIRQ_SBEI, "Single-bit ECC Error" पूर्ण,
	अणु QM_EIRQ_PEBI, "PFDR Enqueues Blocked Interrupt" पूर्ण,
	अणु QM_EIRQ_ICVI, "Invalid Command Verb" पूर्ण,
	अणु QM_EIRQ_IFSI, "Invalid Flow Control State" पूर्ण,
	अणु QM_EIRQ_IDDI, "Invalid Dequeue (Direct-connect)" पूर्ण,
	अणु QM_EIRQ_IDFI, "Invalid Dequeue FQ" पूर्ण,
	अणु QM_EIRQ_IDSI, "Invalid Dequeue Source" पूर्ण,
	अणु QM_EIRQ_IDQI, "Invalid Dequeue Queue" पूर्ण,
	अणु QM_EIRQ_IECE, "Invalid Enqueue Configuration" पूर्ण,
	अणु QM_EIRQ_IEOI, "Invalid Enqueue Overflow" पूर्ण,
	अणु QM_EIRQ_IESI, "Invalid Enqueue State" पूर्ण,
	अणु QM_EIRQ_IECI, "Invalid Enqueue Channel" पूर्ण,
	अणु QM_EIRQ_IEQI, "Invalid Enqueue Queue" पूर्ण,
पूर्ण;

काष्ठा qman_error_info_mdata अणु
	u16 addr_mask;
	u16 bits;
	स्थिर अक्षर *txt;
पूर्ण;

अटल स्थिर काष्ठा qman_error_info_mdata error_mdata[] = अणु
	अणु 0x01FF, 24, "FQD cache tag memory 0" पूर्ण,
	अणु 0x01FF, 24, "FQD cache tag memory 1" पूर्ण,
	अणु 0x01FF, 24, "FQD cache tag memory 2" पूर्ण,
	अणु 0x01FF, 24, "FQD cache tag memory 3" पूर्ण,
	अणु 0x0FFF, 512, "FQD cache memory" पूर्ण,
	अणु 0x07FF, 128, "SFDR memory" पूर्ण,
	अणु 0x01FF, 72, "WQ context memory" पूर्ण,
	अणु 0x00FF, 240, "CGR memory" पूर्ण,
	अणु 0x00FF, 302, "Internal Order Restoration List memory" पूर्ण,
	अणु 0x01FF, 256, "SW portal ring memory" पूर्ण,
पूर्ण;

#घोषणा QMAN_ERRS_TO_DISABLE (QM_EIRQ_PLWI | QM_EIRQ_PEBI)

/*
 * TODO: unimplemented रेजिस्टरs
 *
 * Keeping a list here of QMan रेजिस्टरs I have not yet covered;
 * QCSP_DD_IHRSR, QCSP_DD_IHRFR, QCSP_DD_HASR,
 * DCP_DD_IHRSR, DCP_DD_IHRFR, DCP_DD_HASR, CM_CFG,
 * QMAN_EECC, QMAN_SBET, QMAN_EINJ, QMAN_SBEC0-12
 */

/* Poपूर्णांकer to the start of the QMan's CCSR space */
अटल u32 __iomem *qm_ccsr_start;
/* A SDQCR mask comprising all the available/visible pool channels */
अटल u32 qm_pools_sdqcr;
अटल पूर्णांक __qman_probed;
अटल पूर्णांक  __qman_requires_cleanup;

अटल अंतरभूत u32 qm_ccsr_in(u32 offset)
अणु
	वापस ioपढ़ो32be(qm_ccsr_start + offset/4);
पूर्ण

अटल अंतरभूत व्योम qm_ccsr_out(u32 offset, u32 val)
अणु
	ioग_लिखो32be(val, qm_ccsr_start + offset/4);
पूर्ण

u32 qm_get_pools_sdqcr(व्योम)
अणु
	वापस qm_pools_sdqcr;
पूर्ण

क्रमागत qm_dc_portal अणु
	qm_dc_portal_fman0 = 0,
	qm_dc_portal_fman1 = 1
पूर्ण;

अटल व्योम qm_set_dc(क्रमागत qm_dc_portal portal, पूर्णांक ed, u8 sernd)
अणु
	DPAA_ASSERT(!ed || portal == qm_dc_portal_fman0 ||
		    portal == qm_dc_portal_fman1);
	अगर ((qman_ip_rev & 0xFF00) >= QMAN_REV30)
		qm_ccsr_out(REG_DCP_CFG(portal),
			    (ed ? 0x1000 : 0) | (sernd & 0x3ff));
	अन्यथा
		qm_ccsr_out(REG_DCP_CFG(portal),
			    (ed ? 0x100 : 0) | (sernd & 0x1f));
पूर्ण

अटल व्योम qm_set_wq_scheduling(क्रमागत qm_wq_class wq_class,
				 u8 cs_elev, u8 csw2, u8 csw3, u8 csw4,
				 u8 csw5, u8 csw6, u8 csw7)
अणु
	qm_ccsr_out(REG_WQ_CS_CFG(wq_class), ((cs_elev & 0xff) << 24) |
		    ((csw2 & 0x7) << 20) | ((csw3 & 0x7) << 16) |
		    ((csw4 & 0x7) << 12) | ((csw5 & 0x7) << 8) |
		    ((csw6 & 0x7) << 4) | (csw7 & 0x7));
पूर्ण

अटल व्योम qm_set_hid(व्योम)
अणु
	qm_ccsr_out(REG_HID_CFG, 0);
पूर्ण

अटल व्योम qm_set_corenet_initiator(व्योम)
अणु
	qm_ccsr_out(REG_CI_SCHED_CFG, QM_CI_SCHED_CFG_SRCCIV_EN |
		    (QM_CI_SCHED_CFG_SRCCIV << 24) |
		    (QM_CI_SCHED_CFG_SRQ_W << 8) |
		    (QM_CI_SCHED_CFG_RW_W << 4) |
		    QM_CI_SCHED_CFG_BMAN_W);
पूर्ण

अटल व्योम qm_get_version(u16 *id, u8 *major, u8 *minor)
अणु
	u32 v = qm_ccsr_in(REG_IP_REV_1);
	*id = (v >> 16);
	*major = (v >> 8) & 0xff;
	*minor = v & 0xff;
पूर्ण

#घोषणा PFDR_AR_EN		BIT(31)
अटल पूर्णांक qm_set_memory(क्रमागत qm_memory memory, u64 ba, u32 size)
अणु
	व्योम *ptr;
	u32 offset = (memory == qm_memory_fqd) ? REG_FQD_BARE : REG_PFDR_BARE;
	u32 exp = ilog2(size);
	u32 bar, bare;

	/* choke अगर size isn't within range */
	DPAA_ASSERT((size >= 4096) && (size <= 1024*1024*1024) &&
		    is_घातer_of_2(size));
	/* choke अगर 'ba' has lower-alignment than 'size' */
	DPAA_ASSERT(!(ba & (size - 1)));

	/* Check to see अगर QMan has alपढ़ोy been initialized */
	bar = qm_ccsr_in(offset + REG_offset_BAR);
	अगर (bar) अणु
		/* Maker sure ba == what was programmed) */
		bare = qm_ccsr_in(offset);
		अगर (bare != upper_32_bits(ba) || bar != lower_32_bits(ba)) अणु
			pr_err("Attempted to reinitialize QMan with different BAR, got 0x%llx read BARE=0x%x BAR=0x%x\n",
			       ba, bare, bar);
			वापस -ENOMEM;
		पूर्ण
		__qman_requires_cleanup = 1;
		/* Return 1 to indicate memory was previously programmed */
		वापस 1;
	पूर्ण
	/* Need to temporarily map the area to make sure it is zeroed */
	ptr = memremap(ba, size, MEMREMAP_WB);
	अगर (!ptr) अणु
		pr_crit("memremap() of QMan private memory failed\n");
		वापस -ENOMEM;
	पूर्ण
	स_रखो(ptr, 0, size);

#अगर_घोषित CONFIG_PPC
	/*
	 * PPC करोesn't appear to flush the cache on memunmap() but the
	 * cache must be flushed since QMan करोes non coherent accesses
	 * to this memory
	 */
	flush_dcache_range((अचिन्हित दीर्घ) ptr, (अचिन्हित दीर्घ) ptr+size);
#पूर्ण_अगर
	memunmap(ptr);

	qm_ccsr_out(offset, upper_32_bits(ba));
	qm_ccsr_out(offset + REG_offset_BAR, lower_32_bits(ba));
	qm_ccsr_out(offset + REG_offset_AR, PFDR_AR_EN | (exp - 1));
	वापस 0;
पूर्ण

अटल व्योम qm_set_pfdr_threshold(u32 th, u8 k)
अणु
	qm_ccsr_out(REG_PFDR_FP_LWIT, th & 0xffffff);
	qm_ccsr_out(REG_PFDR_CFG, k);
पूर्ण

अटल व्योम qm_set_sfdr_threshold(u16 th)
अणु
	qm_ccsr_out(REG_SFDR_CFG, th & 0x3ff);
पूर्ण

अटल पूर्णांक qm_init_pfdr(काष्ठा device *dev, u32 pfdr_start, u32 num)
अणु
	u8 rslt = MCR_get_rslt(qm_ccsr_in(REG_MCR));

	DPAA_ASSERT(pfdr_start && !(pfdr_start & 7) && !(num & 7) && num);
	/* Make sure the command पूर्णांकerface is 'idle' */
	अगर (!MCR_rslt_idle(rslt)) अणु
		dev_crit(dev, "QMAN_MCR isn't idle");
		WARN_ON(1);
	पूर्ण

	/* Write the MCR command params then the verb */
	qm_ccsr_out(REG_MCP(0), pfdr_start);
	/*
	 * TODO: हटाओ this - it's a workaround क्रम a model bug that is
	 * corrected in more recent versions. We use the workaround until
	 * everyone has upgraded.
	 */
	qm_ccsr_out(REG_MCP(1), pfdr_start + num - 16);
	dma_wmb();
	qm_ccsr_out(REG_MCR, MCR_INIT_PFDR);
	/* Poll क्रम the result */
	करो अणु
		rslt = MCR_get_rslt(qm_ccsr_in(REG_MCR));
	पूर्ण जबतक (!MCR_rslt_idle(rslt));
	अगर (MCR_rslt_ok(rslt))
		वापस 0;
	अगर (MCR_rslt_eaccess(rslt))
		वापस -EACCES;
	अगर (MCR_rslt_inval(rslt))
		वापस -EINVAL;
	dev_crit(dev, "Unexpected result from MCR_INIT_PFDR: %02x\n", rslt);
	वापस -ENODEV;
पूर्ण

/*
 * QMan needs two global memory areas initialized at boot समय:
 *  1) FQD: Frame Queue Descriptors used to manage frame queues
 *  2) PFDR: Packed Frame Queue Descriptor Records used to store frames
 * Both areas are reserved using the device tree reserved memory framework
 * and the addresses and sizes are initialized when the QMan device is probed
 */
अटल dma_addr_t fqd_a, pfdr_a;
अटल माप_प्रकार fqd_sz, pfdr_sz;

#अगर_घोषित CONFIG_PPC
/*
 * Support क्रम PPC Device Tree backward compatibility when compatible
 * string is set to fsl-qman-fqd and fsl-qman-pfdr
 */
अटल पूर्णांक zero_priv_mem(phys_addr_t addr, माप_प्रकार sz)
अणु
	/* map as cacheable, non-guarded */
	व्योम __iomem *पंचांगpp = ioremap_cache(addr, sz);

	अगर (!पंचांगpp)
		वापस -ENOMEM;

	स_रखो_io(पंचांगpp, 0, sz);
	flush_dcache_range((अचिन्हित दीर्घ)पंचांगpp,
			   (अचिन्हित दीर्घ)पंचांगpp + sz);
	iounmap(पंचांगpp);

	वापस 0;
पूर्ण

अटल पूर्णांक qman_fqd(काष्ठा reserved_mem *rmem)
अणु
	fqd_a = rmem->base;
	fqd_sz = rmem->size;

	WARN_ON(!(fqd_a && fqd_sz));
	वापस 0;
पूर्ण
RESERVEDMEM_OF_DECLARE(qman_fqd, "fsl,qman-fqd", qman_fqd);

अटल पूर्णांक qman_pfdr(काष्ठा reserved_mem *rmem)
अणु
	pfdr_a = rmem->base;
	pfdr_sz = rmem->size;

	WARN_ON(!(pfdr_a && pfdr_sz));

	वापस 0;
पूर्ण
RESERVEDMEM_OF_DECLARE(qman_pfdr, "fsl,qman-pfdr", qman_pfdr);

#पूर्ण_अगर

अचिन्हित पूर्णांक qm_get_fqid_maxcnt(व्योम)
अणु
	वापस fqd_sz / 64;
पूर्ण

अटल व्योम log_edata_bits(काष्ठा device *dev, u32 bit_count)
अणु
	u32 i, j, mask = 0xffffffff;

	dev_warn(dev, "ErrInt, EDATA:\n");
	i = bit_count / 32;
	अगर (bit_count % 32) अणु
		i++;
		mask = ~(mask << bit_count % 32);
	पूर्ण
	j = 16 - i;
	dev_warn(dev, "  0x%08x\n", qm_ccsr_in(REG_EDATA(j)) & mask);
	j++;
	क्रम (; j < 16; j++)
		dev_warn(dev, "  0x%08x\n", qm_ccsr_in(REG_EDATA(j)));
पूर्ण

अटल व्योम log_additional_error_info(काष्ठा device *dev, u32 isr_val,
				      u32 ecsr_val)
अणु
	काष्ठा qm_ecir ecir_val;
	काष्ठा qm_eadr eadr_val;
	पूर्णांक memid;

	ecir_val.info = qm_ccsr_in(REG_ECIR);
	/* Is portal info valid */
	अगर ((qman_ip_rev & 0xFF00) >= QMAN_REV30) अणु
		काष्ठा qm_ecir2 ecir2_val;

		ecir2_val.info = qm_ccsr_in(REG_ECIR2);
		अगर (ecsr_val & PORTAL_ECSR_ERR) अणु
			dev_warn(dev, "ErrInt: %s id %d\n",
				 qm_ecir2_is_dcp(&ecir2_val) ? "DCP" : "SWP",
				 qm_ecir2_get_pnum(&ecir2_val));
		पूर्ण
		अगर (ecsr_val & (FQID_ECSR_ERR | QM_EIRQ_IECE))
			dev_warn(dev, "ErrInt: ecir.fqid 0x%x\n",
				 qm_ecir_get_fqid(&ecir_val));

		अगर (ecsr_val & (QM_EIRQ_SBEI|QM_EIRQ_MBEI)) अणु
			eadr_val.info = qm_ccsr_in(REG_EADR);
			memid = qm_eadr_v3_get_memid(&eadr_val);
			dev_warn(dev, "ErrInt: EADR Memory: %s, 0x%x\n",
				 error_mdata[memid].txt,
				 error_mdata[memid].addr_mask
					& qm_eadr_v3_get_eadr(&eadr_val));
			log_edata_bits(dev, error_mdata[memid].bits);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ecsr_val & PORTAL_ECSR_ERR) अणु
			dev_warn(dev, "ErrInt: %s id %d\n",
				 qm_ecir_is_dcp(&ecir_val) ? "DCP" : "SWP",
				 qm_ecir_get_pnum(&ecir_val));
		पूर्ण
		अगर (ecsr_val & FQID_ECSR_ERR)
			dev_warn(dev, "ErrInt: ecir.fqid 0x%x\n",
				 qm_ecir_get_fqid(&ecir_val));

		अगर (ecsr_val & (QM_EIRQ_SBEI|QM_EIRQ_MBEI)) अणु
			eadr_val.info = qm_ccsr_in(REG_EADR);
			memid = qm_eadr_get_memid(&eadr_val);
			dev_warn(dev, "ErrInt: EADR Memory: %s, 0x%x\n",
				 error_mdata[memid].txt,
				 error_mdata[memid].addr_mask
					& qm_eadr_get_eadr(&eadr_val));
			log_edata_bits(dev, error_mdata[memid].bits);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t qman_isr(पूर्णांक irq, व्योम *ptr)
अणु
	u32 isr_val, ier_val, ecsr_val, isr_mask, i;
	काष्ठा device *dev = ptr;

	ier_val = qm_ccsr_in(REG_ERR_IER);
	isr_val = qm_ccsr_in(REG_ERR_ISR);
	ecsr_val = qm_ccsr_in(REG_ECSR);
	isr_mask = isr_val & ier_val;

	अगर (!isr_mask)
		वापस IRQ_NONE;

	क्रम (i = 0; i < ARRAY_SIZE(qman_hwerr_txts); i++) अणु
		अगर (qman_hwerr_txts[i].mask & isr_mask) अणु
			dev_err_ratelimited(dev, "ErrInt: %s\n",
					    qman_hwerr_txts[i].txt);
			अगर (qman_hwerr_txts[i].mask & ecsr_val) अणु
				log_additional_error_info(dev, isr_mask,
							  ecsr_val);
				/* Re-arm error capture रेजिस्टरs */
				qm_ccsr_out(REG_ECSR, ecsr_val);
			पूर्ण
			अगर (qman_hwerr_txts[i].mask & QMAN_ERRS_TO_DISABLE) अणु
				dev_dbg(dev, "Disabling error 0x%x\n",
					qman_hwerr_txts[i].mask);
				ier_val &= ~qman_hwerr_txts[i].mask;
				qm_ccsr_out(REG_ERR_IER, ier_val);
			पूर्ण
		पूर्ण
	पूर्ण
	qm_ccsr_out(REG_ERR_ISR, isr_val);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qman_init_ccsr(काष्ठा device *dev)
अणु
	पूर्णांक i, err;

	/* FQD memory */
	err = qm_set_memory(qm_memory_fqd, fqd_a, fqd_sz);
	अगर (err < 0)
		वापस err;
	/* PFDR memory */
	err = qm_set_memory(qm_memory_pfdr, pfdr_a, pfdr_sz);
	अगर (err < 0)
		वापस err;
	/* Only initialize PFDRs अगर the QMan was not initialized beक्रमe */
	अगर (err == 0) अणु
		err = qm_init_pfdr(dev, 8, pfdr_sz / 64 - 8);
		अगर (err)
			वापस err;
	पूर्ण
	/* thresholds */
	qm_set_pfdr_threshold(512, 64);
	qm_set_sfdr_threshold(128);
	/* clear stale PEBI bit from पूर्णांकerrupt status रेजिस्टर */
	qm_ccsr_out(REG_ERR_ISR, QM_EIRQ_PEBI);
	/* corenet initiator settings */
	qm_set_corenet_initiator();
	/* HID settings */
	qm_set_hid();
	/* Set scheduling weights to शेषs */
	क्रम (i = qm_wq_first; i <= qm_wq_last; i++)
		qm_set_wq_scheduling(i, 0, 0, 0, 0, 0, 0, 0);
	/* We are not prepared to accept ERNs क्रम hardware enqueues */
	qm_set_dc(qm_dc_portal_fman0, 1, 0);
	qm_set_dc(qm_dc_portal_fman1, 1, 0);
	वापस 0;
पूर्ण

#घोषणा LIO_CFG_LIODN_MASK 0x0fff0000
व्योम __qman_liodn_fixup(u16 channel)
अणु
	अटल पूर्णांक करोne;
	अटल u32 liodn_offset;
	u32 beक्रमe, after;
	पूर्णांक idx = channel - QM_CHANNEL_SWPORTAL0;

	अगर ((qman_ip_rev & 0xFF00) >= QMAN_REV30)
		beक्रमe = qm_ccsr_in(REG_REV3_QCSP_LIO_CFG(idx));
	अन्यथा
		beक्रमe = qm_ccsr_in(REG_QCSP_LIO_CFG(idx));
	अगर (!करोne) अणु
		liodn_offset = beक्रमe & LIO_CFG_LIODN_MASK;
		करोne = 1;
		वापस;
	पूर्ण
	after = (beक्रमe & (~LIO_CFG_LIODN_MASK)) | liodn_offset;
	अगर ((qman_ip_rev & 0xFF00) >= QMAN_REV30)
		qm_ccsr_out(REG_REV3_QCSP_LIO_CFG(idx), after);
	अन्यथा
		qm_ccsr_out(REG_QCSP_LIO_CFG(idx), after);
पूर्ण

#घोषणा IO_CFG_SDEST_MASK 0x00ff0000
व्योम qman_set_sdest(u16 channel, अचिन्हित पूर्णांक cpu_idx)
अणु
	पूर्णांक idx = channel - QM_CHANNEL_SWPORTAL0;
	u32 beक्रमe, after;

	अगर ((qman_ip_rev & 0xFF00) >= QMAN_REV30) अणु
		beक्रमe = qm_ccsr_in(REG_REV3_QCSP_IO_CFG(idx));
		/* Each pair of vcpu share the same SRQ(SDEST) */
		cpu_idx /= 2;
		after = (beक्रमe & (~IO_CFG_SDEST_MASK)) | (cpu_idx << 16);
		qm_ccsr_out(REG_REV3_QCSP_IO_CFG(idx), after);
	पूर्ण अन्यथा अणु
		beक्रमe = qm_ccsr_in(REG_QCSP_IO_CFG(idx));
		after = (beक्रमe & (~IO_CFG_SDEST_MASK)) | (cpu_idx << 16);
		qm_ccsr_out(REG_QCSP_IO_CFG(idx), after);
	पूर्ण
पूर्ण

अटल पूर्णांक qman_resource_init(काष्ठा device *dev)
अणु
	पूर्णांक pool_chan_num, cgrid_num;
	पूर्णांक ret, i;

	चयन (qman_ip_rev >> 8) अणु
	हाल 1:
		pool_chan_num = 15;
		cgrid_num = 256;
		अवरोध;
	हाल 2:
		pool_chan_num = 3;
		cgrid_num = 64;
		अवरोध;
	हाल 3:
		pool_chan_num = 15;
		cgrid_num = 256;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	ret = gen_pool_add(qm_qpalloc, qm_channel_pool1 | DPAA_GENALLOC_OFF,
			   pool_chan_num, -1);
	अगर (ret) अणु
		dev_err(dev, "Failed to seed pool channels (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = gen_pool_add(qm_cgralloc, DPAA_GENALLOC_OFF, cgrid_num, -1);
	अगर (ret) अणु
		dev_err(dev, "Failed to seed CGRID range (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* parse pool channels पूर्णांकo the SDQCR mask */
	क्रम (i = 0; i < cgrid_num; i++)
		qm_pools_sdqcr |= QM_SDQCR_CHANNELS_POOL_CONV(i);

	ret = gen_pool_add(qm_fqalloc, QM_FQID_RANGE_START | DPAA_GENALLOC_OFF,
			   qm_get_fqid_maxcnt() - QM_FQID_RANGE_START, -1);
	अगर (ret) अणु
		dev_err(dev, "Failed to seed FQID range (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qman_is_probed(व्योम)
अणु
	वापस __qman_probed;
पूर्ण
EXPORT_SYMBOL_GPL(qman_is_probed);

पूर्णांक qman_requires_cleanup(व्योम)
अणु
	वापस __qman_requires_cleanup;
पूर्ण

व्योम qman_करोne_cleanup(व्योम)
अणु
	qman_enable_irqs();
	__qman_requires_cleanup = 0;
पूर्ण


अटल पूर्णांक fsl_qman_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा resource *res;
	पूर्णांक ret, err_irq;
	u16 id;
	u8 major, minor;

	__qman_probed = -1;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "Can't get %pOF property 'IORESOURCE_MEM'\n",
			node);
		वापस -ENXIO;
	पूर्ण
	qm_ccsr_start = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!qm_ccsr_start)
		वापस -ENXIO;

	qm_get_version(&id, &major, &minor);
	अगर (major == 1 && minor == 0) अणु
		dev_err(dev, "Rev1.0 on P4080 rev1 is not supported!\n");
			वापस -ENODEV;
	पूर्ण अन्यथा अगर (major == 1 && minor == 1)
		qman_ip_rev = QMAN_REV11;
	अन्यथा अगर	(major == 1 && minor == 2)
		qman_ip_rev = QMAN_REV12;
	अन्यथा अगर (major == 2 && minor == 0)
		qman_ip_rev = QMAN_REV20;
	अन्यथा अगर (major == 3 && minor == 0)
		qman_ip_rev = QMAN_REV30;
	अन्यथा अगर (major == 3 && minor == 1)
		qman_ip_rev = QMAN_REV31;
	अन्यथा अगर (major == 3 && minor == 2)
		qman_ip_rev = QMAN_REV32;
	अन्यथा अणु
		dev_err(dev, "Unknown QMan version\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((qman_ip_rev & 0xff00) >= QMAN_REV30) अणु
		qm_channel_pool1 = QMAN_CHANNEL_POOL1_REV3;
		qm_channel_caam = QMAN_CHANNEL_CAAM_REV3;
	पूर्ण

	अगर (fqd_a) अणु
#अगर_घोषित CONFIG_PPC
		/*
		 * For PPC backward DT compatibility
		 * FQD memory MUST be zero'd by software
		 */
		zero_priv_mem(fqd_a, fqd_sz);
#अन्यथा
		WARN(1, "Unexpected architecture using non shared-dma-mem reservations");
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/*
		 * Order of memory regions is assumed as FQD followed by PFDR
		 * in order to ensure allocations from the correct regions the
		 * driver initializes then allocates each piece in order
		 */
		ret = qbman_init_निजी_mem(dev, 0, &fqd_a, &fqd_sz);
		अगर (ret) अणु
			dev_err(dev, "qbman_init_private_mem() for FQD failed 0x%x\n",
				ret);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	dev_dbg(dev, "Allocated FQD 0x%llx 0x%zx\n", fqd_a, fqd_sz);

	अगर (!pfdr_a) अणु
		/* Setup PFDR memory */
		ret = qbman_init_निजी_mem(dev, 1, &pfdr_a, &pfdr_sz);
		अगर (ret) अणु
			dev_err(dev, "qbman_init_private_mem() for PFDR failed 0x%x\n",
				ret);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	dev_dbg(dev, "Allocated PFDR 0x%llx 0x%zx\n", pfdr_a, pfdr_sz);

	ret = qman_init_ccsr(dev);
	अगर (ret) अणु
		dev_err(dev, "CCSR setup failed\n");
		वापस ret;
	पूर्ण

	err_irq = platक्रमm_get_irq(pdev, 0);
	अगर (err_irq <= 0) अणु
		dev_info(dev, "Can't get %pOF property 'interrupts'\n",
			 node);
		वापस -ENODEV;
	पूर्ण
	ret = devm_request_irq(dev, err_irq, qman_isr, IRQF_SHARED, "qman-err",
			       dev);
	अगर (ret)  अणु
		dev_err(dev, "devm_request_irq() failed %d for '%pOF'\n",
			ret, node);
		वापस ret;
	पूर्ण

	/*
	 * Write-to-clear any stale bits, (eg. starvation being निश्चितed prior
	 * to resource allocation during driver init).
	 */
	qm_ccsr_out(REG_ERR_ISR, 0xffffffff);
	/* Enable Error Interrupts */
	qm_ccsr_out(REG_ERR_IER, 0xffffffff);

	qm_fqalloc = devm_gen_pool_create(dev, 0, -1, "qman-fqalloc");
	अगर (IS_ERR(qm_fqalloc)) अणु
		ret = PTR_ERR(qm_fqalloc);
		dev_err(dev, "qman-fqalloc pool init failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	qm_qpalloc = devm_gen_pool_create(dev, 0, -1, "qman-qpalloc");
	अगर (IS_ERR(qm_qpalloc)) अणु
		ret = PTR_ERR(qm_qpalloc);
		dev_err(dev, "qman-qpalloc pool init failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	qm_cgralloc = devm_gen_pool_create(dev, 0, -1, "qman-cgralloc");
	अगर (IS_ERR(qm_cgralloc)) अणु
		ret = PTR_ERR(qm_cgralloc);
		dev_err(dev, "qman-cgralloc pool init failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = qman_resource_init(dev);
	अगर (ret)
		वापस ret;

	ret = qman_alloc_fq_table(qm_get_fqid_maxcnt());
	अगर (ret)
		वापस ret;

	ret = qman_wq_alloc();
	अगर (ret)
		वापस ret;

	__qman_probed = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_qman_ids[] = अणु
	अणु
		.compatible = "fsl,qman",
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_qman_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = fsl_qman_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = fsl_qman_probe,
पूर्ण;

builtin_platक्रमm_driver(fsl_qman_driver);
