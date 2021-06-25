<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARC Cache Management
 *
 * Copyright (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/cache.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pagemap.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cachectl.h>
#समावेश <यंत्र/setup.h>

#अगर_घोषित CONFIG_ISA_ARCV2
#घोषणा USE_RGN_FLSH	1
#पूर्ण_अगर

अटल पूर्णांक l2_line_sz;
अटल पूर्णांक ioc_exists;
पूर्णांक slc_enable = 1, ioc_enable = 1;
अचिन्हित दीर्घ perip_base = ARC_UNCACHED_ADDR_SPACE; /* legacy value क्रम boot */
अचिन्हित दीर्घ perip_end = 0xFFFFFFFF; /* legacy value */

व्योम (*_cache_line_loop_ic_fn)(phys_addr_t paddr, अचिन्हित दीर्घ vaddr,
			       अचिन्हित दीर्घ sz, स्थिर पूर्णांक op, स्थिर पूर्णांक full_page);

व्योम (*__dma_cache_wback_inv)(phys_addr_t start, अचिन्हित दीर्घ sz);
व्योम (*__dma_cache_inv)(phys_addr_t start, अचिन्हित दीर्घ sz);
व्योम (*__dma_cache_wback)(phys_addr_t start, अचिन्हित दीर्घ sz);

अक्षर *arc_cache_mumbojumbo(पूर्णांक c, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक n = 0;
	काष्ठा cpuinfo_arc_cache *p;

#घोषणा PR_CACHE(p, cfg, str)						\
	अगर (!(p)->line_len)						\
		n += scnम_लिखो(buf + n, len - n, str"\t\t: N/A\n");	\
	अन्यथा								\
		n += scnम_लिखो(buf + n, len - n,			\
			str"\t\t: %uK, %dway/set, %uB Line, %s%s%s\n",	\
			(p)->sz_k, (p)->assoc, (p)->line_len,		\
			(p)->vipt ? "VIPT" : "PIPT",			\
			(p)->alias ? " aliasing" : "",			\
			IS_USED_CFG(cfg));

	PR_CACHE(&cpuinfo_arc700[c].icache, CONFIG_ARC_HAS_ICACHE, "I-Cache");
	PR_CACHE(&cpuinfo_arc700[c].dcache, CONFIG_ARC_HAS_DCACHE, "D-Cache");

	p = &cpuinfo_arc700[c].slc;
	अगर (p->line_len)
		n += scnम_लिखो(buf + n, len - n,
			       "SLC\t\t: %uK, %uB Line%s\n",
			       p->sz_k, p->line_len, IS_USED_RUN(slc_enable));

	n += scnम_लिखो(buf + n, len - n, "Peripherals\t: %#lx%s%s\n",
		       perip_base,
		       IS_AVAIL3(ioc_exists, ioc_enable, ", IO-Coherency (per-device) "));

	वापस buf;
पूर्ण

/*
 * Read the Cache Build Confuration Registers, Decode them and save पूर्णांकo
 * the cpuinfo काष्ठाure क्रम later use.
 * No Validation करोne here, simply पढ़ो/convert the BCRs
 */
अटल व्योम पढ़ो_decode_cache_bcr_arcv2(पूर्णांक cpu)
अणु
	काष्ठा cpuinfo_arc_cache *p_slc = &cpuinfo_arc700[cpu].slc;
	काष्ठा bcr_generic sbcr;

	काष्ठा bcr_slc_cfg अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
		अचिन्हित पूर्णांक pad:24, way:2, lsz:2, sz:4;
#अन्यथा
		अचिन्हित पूर्णांक sz:4, lsz:2, way:2, pad:24;
#पूर्ण_अगर
	पूर्ण slc_cfg;

	काष्ठा bcr_clust_cfg अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
		अचिन्हित पूर्णांक pad:7, c:1, num_entries:8, num_cores:8, ver:8;
#अन्यथा
		अचिन्हित पूर्णांक ver:8, num_cores:8, num_entries:8, c:1, pad:7;
#पूर्ण_अगर
	पूर्ण cbcr;

	काष्ठा bcr_अस्थिर अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
		अचिन्हित पूर्णांक start:4, limit:4, pad:22, order:1, disable:1;
#अन्यथा
		अचिन्हित पूर्णांक disable:1, order:1, pad:22, limit:4, start:4;
#पूर्ण_अगर
	पूर्ण vol;


	READ_BCR(ARC_REG_SLC_BCR, sbcr);
	अगर (sbcr.ver) अणु
		READ_BCR(ARC_REG_SLC_CFG, slc_cfg);
		p_slc->sz_k = 128 << slc_cfg.sz;
		l2_line_sz = p_slc->line_len = (slc_cfg.lsz == 0) ? 128 : 64;
	पूर्ण

	READ_BCR(ARC_REG_CLUSTER_BCR, cbcr);
	अगर (cbcr.c) अणु
		ioc_exists = 1;

		/*
		 * As क्रम today we करोn't support both IOC and ZONE_HIGHMEM enabled
		 * simultaneously. This happens because as of today IOC aperture covers
		 * only ZONE_NORMAL (low mem) and any dma transactions outside this
		 * region won't be HW coherent.
		 * If we want to use both IOC and ZONE_HIGHMEM we can use
		 * bounce_buffer to handle dma transactions to HIGHMEM.
		 * Also it is possible to modअगरy dma_direct cache ops or increase IOC
		 * aperture size अगर we are planning to use HIGHMEM without PAE.
		 */
		अगर (IS_ENABLED(CONFIG_HIGHMEM) || is_pae40_enabled())
			ioc_enable = 0;
	पूर्ण अन्यथा अणु
		ioc_enable = 0;
	पूर्ण

	/* HS 2.0 didn't have AUX_VOL */
	अगर (cpuinfo_arc700[cpu].core.family > 0x51) अणु
		READ_BCR(AUX_VOL, vol);
		perip_base = vol.start << 28;
		/* HS 3.0 has limit and strict-ordering fields */
		अगर (cpuinfo_arc700[cpu].core.family > 0x52)
			perip_end = (vol.limit << 28) - 1;
	पूर्ण
पूर्ण

व्योम पढ़ो_decode_cache_bcr(व्योम)
अणु
	काष्ठा cpuinfo_arc_cache *p_ic, *p_dc;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा bcr_cache अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
		अचिन्हित पूर्णांक pad:12, line_len:4, sz:4, config:4, ver:8;
#अन्यथा
		अचिन्हित पूर्णांक ver:8, config:4, sz:4, line_len:4, pad:12;
#पूर्ण_अगर
	पूर्ण ibcr, dbcr;

	p_ic = &cpuinfo_arc700[cpu].icache;
	READ_BCR(ARC_REG_IC_BCR, ibcr);

	अगर (!ibcr.ver)
		जाओ dc_chk;

	अगर (ibcr.ver <= 3) अणु
		BUG_ON(ibcr.config != 3);
		p_ic->assoc = 2;		/* Fixed to 2w set assoc */
	पूर्ण अन्यथा अगर (ibcr.ver >= 4) अणु
		p_ic->assoc = 1 << ibcr.config;	/* 1,2,4,8 */
	पूर्ण

	p_ic->line_len = 8 << ibcr.line_len;
	p_ic->sz_k = 1 << (ibcr.sz - 1);
	p_ic->vipt = 1;
	p_ic->alias = p_ic->sz_k/p_ic->assoc/TO_KB(PAGE_SIZE) > 1;

dc_chk:
	p_dc = &cpuinfo_arc700[cpu].dcache;
	READ_BCR(ARC_REG_DC_BCR, dbcr);

	अगर (!dbcr.ver)
		जाओ slc_chk;

	अगर (dbcr.ver <= 3) अणु
		BUG_ON(dbcr.config != 2);
		p_dc->assoc = 4;		/* Fixed to 4w set assoc */
		p_dc->vipt = 1;
		p_dc->alias = p_dc->sz_k/p_dc->assoc/TO_KB(PAGE_SIZE) > 1;
	पूर्ण अन्यथा अगर (dbcr.ver >= 4) अणु
		p_dc->assoc = 1 << dbcr.config;	/* 1,2,4,8 */
		p_dc->vipt = 0;
		p_dc->alias = 0;		/* PIPT so can't VIPT alias */
	पूर्ण

	p_dc->line_len = 16 << dbcr.line_len;
	p_dc->sz_k = 1 << (dbcr.sz - 1);

slc_chk:
	अगर (is_isa_arcv2())
                पढ़ो_decode_cache_bcr_arcv2(cpu);
पूर्ण

/*
 * Line Operation on अणुI,Dपूर्ण-Cache
 */

#घोषणा OP_INV		0x1
#घोषणा OP_FLUSH	0x2
#घोषणा OP_FLUSH_N_INV	0x3
#घोषणा OP_INV_IC	0x4

/*
 *		I-Cache Aliasing in ARC700 VIPT caches (MMU v1-v3)
 *
 * ARC VIPT I-cache uses vaddr to index पूर्णांकo cache and paddr to match the tag.
 * The orig Cache Management Module "CDU" only required paddr to invalidate a
 * certain line since it sufficed as index in Non-Aliasing VIPT cache-geometry.
 * Infact क्रम distinct V1,V2,P: all of अणुV1-Pपूर्ण,अणुV2-Pपूर्ण,अणुP-Pपूर्ण would end up fetching
 * the exact same line.
 *
 * However क्रम larger Caches (way-size > page-size) - i.e. in Aliasing config,
 * paddr alone could not be used to correctly index the cache.
 *
 * ------------------
 * MMU v1/v2 (Fixed Page Size 8k)
 * ------------------
 * The solution was to provide CDU with these additonal vaddr bits. These
 * would be bits [x:13], x would depend on cache-geometry, 13 comes from
 * standard page size of 8k.
 * H/w folks chose [17:13] to be a future safe range, and moreso these 5 bits
 * of vaddr could easily be "stuffed" in the paddr as bits [4:0] since the
 * orig 5 bits of paddr were anyways ignored by CDU line ops, as they
 * represent the offset within cache-line. The adv of using this "clumsy"
 * पूर्णांकerface क्रम additional info was no new reg was needed in CDU programming
 * model.
 *
 * 17:13 represented the max num of bits passable, actual bits needed were
 * fewer, based on the num-of-aliases possible.
 * -क्रम 2 alias possibility, only bit 13 needed (32K cache)
 * -क्रम 4 alias possibility, bits 14:13 needed (64K cache)
 *
 * ------------------
 * MMU v3
 * ------------------
 * This ver of MMU supports variable page sizes (1k-16k): although Linux will
 * only support 8k (शेष), 16k and 4k.
 * However from hardware perspective, smaller page sizes aggravate aliasing
 * meaning more vaddr bits needed to disambiguate the cache-line-op ;
 * the existing scheme of piggybacking won't work क्रम certain configurations.
 * Two new रेजिस्टरs IC_PTAG and DC_PTAG पूर्णांकtoduced.
 * "tag" bits are provided in PTAG, index bits in existing IVIL/IVDL/FLDL regs
 */

अटल अंतरभूत
व्योम __cache_line_loop_v2(phys_addr_t paddr, अचिन्हित दीर्घ vaddr,
			  अचिन्हित दीर्घ sz, स्थिर पूर्णांक op, स्थिर पूर्णांक full_page)
अणु
	अचिन्हित पूर्णांक aux_cmd;
	पूर्णांक num_lines;

	अगर (op == OP_INV_IC) अणु
		aux_cmd = ARC_REG_IC_IVIL;
	पूर्ण अन्यथा अणु
		/* d$ cmd: INV (discard or wback-n-discard) OR FLUSH (wback) */
		aux_cmd = op & OP_INV ? ARC_REG_DC_IVDL : ARC_REG_DC_FLDL;
	पूर्ण

	/* Ensure we properly न्यूनमान/उच्चमान the non-line aligned/sized requests
	 * and have @paddr - aligned to cache line and पूर्णांकegral @num_lines.
	 * This however can be aव्योमed क्रम page sized since:
	 *  -@paddr will be cache-line aligned alपढ़ोy (being page aligned)
	 *  -@sz will be पूर्णांकegral multiple of line size (being page sized).
	 */
	अगर (!full_page) अणु
		sz += paddr & ~CACHE_LINE_MASK;
		paddr &= CACHE_LINE_MASK;
		vaddr &= CACHE_LINE_MASK;
	पूर्ण

	num_lines = DIV_ROUND_UP(sz, L1_CACHE_BYTES);

	/* MMUv2 and beक्रमe: paddr contains stuffed vaddrs bits */
	paddr |= (vaddr >> PAGE_SHIFT) & 0x1F;

	जबतक (num_lines-- > 0) अणु
		ग_लिखो_aux_reg(aux_cmd, paddr);
		paddr += L1_CACHE_BYTES;
	पूर्ण
पूर्ण

/*
 * For ARC700 MMUv3 I-cache and D-cache flushes
 *  - ARC700 programming model requires paddr and vaddr be passed in seperate
 *    AUX रेजिस्टरs (*_IV*L and *_PTAG respectively) irrespective of whether the
 *    caches actually alias or not.
 * -  For HS38, only the aliasing I-cache configuration uses the PTAG reg
 *    (non aliasing I-cache version करोesn't; while D-cache can't possibly alias)
 */
अटल अंतरभूत
व्योम __cache_line_loop_v3(phys_addr_t paddr, अचिन्हित दीर्घ vaddr,
			  अचिन्हित दीर्घ sz, स्थिर पूर्णांक op, स्थिर पूर्णांक full_page)
अणु
	अचिन्हित पूर्णांक aux_cmd, aux_tag;
	पूर्णांक num_lines;

	अगर (op == OP_INV_IC) अणु
		aux_cmd = ARC_REG_IC_IVIL;
		aux_tag = ARC_REG_IC_PTAG;
	पूर्ण अन्यथा अणु
		aux_cmd = op & OP_INV ? ARC_REG_DC_IVDL : ARC_REG_DC_FLDL;
		aux_tag = ARC_REG_DC_PTAG;
	पूर्ण

	/* Ensure we properly न्यूनमान/उच्चमान the non-line aligned/sized requests
	 * and have @paddr - aligned to cache line and पूर्णांकegral @num_lines.
	 * This however can be aव्योमed क्रम page sized since:
	 *  -@paddr will be cache-line aligned alपढ़ोy (being page aligned)
	 *  -@sz will be पूर्णांकegral multiple of line size (being page sized).
	 */
	अगर (!full_page) अणु
		sz += paddr & ~CACHE_LINE_MASK;
		paddr &= CACHE_LINE_MASK;
		vaddr &= CACHE_LINE_MASK;
	पूर्ण
	num_lines = DIV_ROUND_UP(sz, L1_CACHE_BYTES);

	/*
	 * MMUv3, cache ops require paddr in PTAG reg
	 * अगर V-P स्थिर क्रम loop, PTAG can be written once outside loop
	 */
	अगर (full_page)
		ग_लिखो_aux_reg(aux_tag, paddr);

	/*
	 * This is technically क्रम MMU v4, using the MMU v3 programming model
	 * Special work क्रम HS38 aliasing I-cache configuration with PAE40
	 *   - upper 8 bits of paddr need to be written पूर्णांकo PTAG_HI
	 *   - (and needs to be written beक्रमe the lower 32 bits)
	 * Note that PTAG_HI is hoisted outside the line loop
	 */
	अगर (is_pae40_enabled() && op == OP_INV_IC)
		ग_लिखो_aux_reg(ARC_REG_IC_PTAG_HI, (u64)paddr >> 32);

	जबतक (num_lines-- > 0) अणु
		अगर (!full_page) अणु
			ग_लिखो_aux_reg(aux_tag, paddr);
			paddr += L1_CACHE_BYTES;
		पूर्ण

		ग_लिखो_aux_reg(aux_cmd, vaddr);
		vaddr += L1_CACHE_BYTES;
	पूर्ण
पूर्ण

#अगर_अघोषित USE_RGN_FLSH

/*
 * In HS38x (MMU v4), I-cache is VIPT (can alias), D-cache is PIPT
 * Here's how cache ops are implemented
 *
 *  - D-cache: only paddr needed (in DC_IVDL/DC_FLDL)
 *  - I-cache Non Aliasing: Despite VIPT, only paddr needed (in IC_IVIL)
 *  - I-cache Aliasing: Both vaddr and paddr needed (in IC_IVIL, IC_PTAG
 *    respectively, similar to MMU v3 programming model, hence
 *    __cache_line_loop_v3() is used)
 *
 * If PAE40 is enabled, independent of aliasing considerations, the higher bits
 * needs to be written पूर्णांकo PTAG_HI
 */
अटल अंतरभूत
व्योम __cache_line_loop_v4(phys_addr_t paddr, अचिन्हित दीर्घ vaddr,
			  अचिन्हित दीर्घ sz, स्थिर पूर्णांक op, स्थिर पूर्णांक full_page)
अणु
	अचिन्हित पूर्णांक aux_cmd;
	पूर्णांक num_lines;

	अगर (op == OP_INV_IC) अणु
		aux_cmd = ARC_REG_IC_IVIL;
	पूर्ण अन्यथा अणु
		/* d$ cmd: INV (discard or wback-n-discard) OR FLUSH (wback) */
		aux_cmd = op & OP_INV ? ARC_REG_DC_IVDL : ARC_REG_DC_FLDL;
	पूर्ण

	/* Ensure we properly न्यूनमान/उच्चमान the non-line aligned/sized requests
	 * and have @paddr - aligned to cache line and पूर्णांकegral @num_lines.
	 * This however can be aव्योमed क्रम page sized since:
	 *  -@paddr will be cache-line aligned alपढ़ोy (being page aligned)
	 *  -@sz will be पूर्णांकegral multiple of line size (being page sized).
	 */
	अगर (!full_page) अणु
		sz += paddr & ~CACHE_LINE_MASK;
		paddr &= CACHE_LINE_MASK;
	पूर्ण

	num_lines = DIV_ROUND_UP(sz, L1_CACHE_BYTES);

	/*
	 * For HS38 PAE40 configuration
	 *   - upper 8 bits of paddr need to be written पूर्णांकo PTAG_HI
	 *   - (and needs to be written beक्रमe the lower 32 bits)
	 */
	अगर (is_pae40_enabled()) अणु
		अगर (op == OP_INV_IC)
			/*
			 * Non aliasing I-cache in HS38,
			 * aliasing I-cache handled in __cache_line_loop_v3()
			 */
			ग_लिखो_aux_reg(ARC_REG_IC_PTAG_HI, (u64)paddr >> 32);
		अन्यथा
			ग_लिखो_aux_reg(ARC_REG_DC_PTAG_HI, (u64)paddr >> 32);
	पूर्ण

	जबतक (num_lines-- > 0) अणु
		ग_लिखो_aux_reg(aux_cmd, paddr);
		paddr += L1_CACHE_BYTES;
	पूर्ण
पूर्ण

#अन्यथा

/*
 * optimized flush operation which takes a region as opposed to iterating per line
 */
अटल अंतरभूत
व्योम __cache_line_loop_v4(phys_addr_t paddr, अचिन्हित दीर्घ vaddr,
			  अचिन्हित दीर्घ sz, स्थिर पूर्णांक op, स्थिर पूर्णांक full_page)
अणु
	अचिन्हित पूर्णांक s, e;

	/* Only क्रम Non aliasing I-cache in HS38 */
	अगर (op == OP_INV_IC) अणु
		s = ARC_REG_IC_IVIR;
		e = ARC_REG_IC_ENDR;
	पूर्ण अन्यथा अणु
		s = ARC_REG_DC_STARTR;
		e = ARC_REG_DC_ENDR;
	पूर्ण

	अगर (!full_page) अणु
		/* क्रम any leading gap between @paddr and start of cache line */
		sz += paddr & ~CACHE_LINE_MASK;
		paddr &= CACHE_LINE_MASK;

		/*
		 *  account क्रम any trailing gap to end of cache line
		 *  this is equivalent to DIV_ROUND_UP() in line ops above
		 */
		sz += L1_CACHE_BYTES - 1;
	पूर्ण

	अगर (is_pae40_enabled()) अणु
		/* TBD: check अगर crossing 4TB boundary */
		अगर (op == OP_INV_IC)
			ग_लिखो_aux_reg(ARC_REG_IC_PTAG_HI, (u64)paddr >> 32);
		अन्यथा
			ग_लिखो_aux_reg(ARC_REG_DC_PTAG_HI, (u64)paddr >> 32);
	पूर्ण

	/* ENDR needs to be set ahead of START */
	ग_लिखो_aux_reg(e, paddr + sz);	/* ENDR is exclusive */
	ग_लिखो_aux_reg(s, paddr);

	/* caller रुकोs on DC_CTRL.FS */
पूर्ण

#पूर्ण_अगर

#अगर (CONFIG_ARC_MMU_VER < 3)
#घोषणा __cache_line_loop	__cache_line_loop_v2
#या_अगर (CONFIG_ARC_MMU_VER == 3)
#घोषणा __cache_line_loop	__cache_line_loop_v3
#या_अगर (CONFIG_ARC_MMU_VER > 3)
#घोषणा __cache_line_loop	__cache_line_loop_v4
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARC_HAS_DCACHE

/***************************************************************
 * Machine specअगरic helpers क्रम Entire D-Cache or Per Line ops
 */

#अगर_अघोषित USE_RGN_FLSH
/*
 * this version aव्योमs extra पढ़ो/ग_लिखो of DC_CTRL क्रम flush or invalid ops
 * in the non region flush regime (such as क्रम ARCompact)
 */
अटल अंतरभूत व्योम __beक्रमe_dc_op(स्थिर पूर्णांक op)
अणु
	अगर (op == OP_FLUSH_N_INV) अणु
		/* Dcache provides 2 cmd: FLUSH or INV
		 * INV पूर्णांकurn has sub-modes: DISCARD or FLUSH-BEFORE
		 * flush-n-inv is achieved by INV cmd but with IM=1
		 * So toggle INV sub-mode depending on op request and शेष
		 */
		स्थिर अचिन्हित पूर्णांक ctl = ARC_REG_DC_CTRL;
		ग_लिखो_aux_reg(ctl, पढ़ो_aux_reg(ctl) | DC_CTRL_INV_MODE_FLUSH);
	पूर्ण
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम __beक्रमe_dc_op(स्थिर पूर्णांक op)
अणु
	स्थिर अचिन्हित पूर्णांक ctl = ARC_REG_DC_CTRL;
	अचिन्हित पूर्णांक val = पढ़ो_aux_reg(ctl);

	अगर (op == OP_FLUSH_N_INV) अणु
		val |= DC_CTRL_INV_MODE_FLUSH;
	पूर्ण

	अगर (op != OP_INV_IC) अणु
		/*
		 * Flush / Invalidate is provided by DC_CTRL.RNG_OP 0 or 1
		 * combined Flush-n-invalidate uses DC_CTRL.IM = 1 set above
		 */
		val &= ~DC_CTRL_RGN_OP_MSK;
		अगर (op & OP_INV)
			val |= DC_CTRL_RGN_OP_INV;
	पूर्ण
	ग_लिखो_aux_reg(ctl, val);
पूर्ण

#पूर्ण_अगर


अटल अंतरभूत व्योम __after_dc_op(स्थिर पूर्णांक op)
अणु
	अगर (op & OP_FLUSH) अणु
		स्थिर अचिन्हित पूर्णांक ctl = ARC_REG_DC_CTRL;
		अचिन्हित पूर्णांक reg;

		/* flush / flush-n-inv both रुको */
		जबतक ((reg = पढ़ो_aux_reg(ctl)) & DC_CTRL_FLUSH_STATUS)
			;

		/* Switch back to शेष Invalidate mode */
		अगर (op == OP_FLUSH_N_INV)
			ग_लिखो_aux_reg(ctl, reg & ~DC_CTRL_INV_MODE_FLUSH);
	पूर्ण
पूर्ण

/*
 * Operation on Entire D-Cache
 * @op = अणुOP_INV, OP_FLUSH, OP_FLUSH_N_INVपूर्ण
 * Note that स्थिरant propagation ensures all the checks are gone
 * in generated code
 */
अटल अंतरभूत व्योम __dc_entire_op(स्थिर पूर्णांक op)
अणु
	पूर्णांक aux;

	__beक्रमe_dc_op(op);

	अगर (op & OP_INV)	/* Inv or flush-n-inv use same cmd reg */
		aux = ARC_REG_DC_IVDC;
	अन्यथा
		aux = ARC_REG_DC_FLSH;

	ग_लिखो_aux_reg(aux, 0x1);

	__after_dc_op(op);
पूर्ण

अटल अंतरभूत व्योम __dc_disable(व्योम)
अणु
	स्थिर पूर्णांक r = ARC_REG_DC_CTRL;

	__dc_entire_op(OP_FLUSH_N_INV);
	ग_लिखो_aux_reg(r, पढ़ो_aux_reg(r) | DC_CTRL_DIS);
पूर्ण

अटल व्योम __dc_enable(व्योम)
अणु
	स्थिर पूर्णांक r = ARC_REG_DC_CTRL;

	ग_लिखो_aux_reg(r, पढ़ो_aux_reg(r) & ~DC_CTRL_DIS);
पूर्ण

/* For kernel mappings cache operation: index is same as paddr */
#घोषणा __dc_line_op_k(p, sz, op)	__dc_line_op(p, p, sz, op)

/*
 * D-Cache Line ops: Per Line INV (discard or wback+discard) or FLUSH (wback)
 */
अटल अंतरभूत व्योम __dc_line_op(phys_addr_t paddr, अचिन्हित दीर्घ vaddr,
				अचिन्हित दीर्घ sz, स्थिर पूर्णांक op)
अणु
	स्थिर पूर्णांक full_page = __builtin_स्थिरant_p(sz) && sz == PAGE_SIZE;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	__beक्रमe_dc_op(op);

	__cache_line_loop(paddr, vaddr, sz, op, full_page);

	__after_dc_op(op);

	local_irq_restore(flags);
पूर्ण

#अन्यथा

#घोषणा __dc_entire_op(op)
#घोषणा __dc_disable()
#घोषणा __dc_enable()
#घोषणा __dc_line_op(paddr, vaddr, sz, op)
#घोषणा __dc_line_op_k(paddr, sz, op)

#पूर्ण_अगर /* CONFIG_ARC_HAS_DCACHE */

#अगर_घोषित CONFIG_ARC_HAS_ICACHE

अटल अंतरभूत व्योम __ic_entire_inv(व्योम)
अणु
	ग_लिखो_aux_reg(ARC_REG_IC_IVIC, 1);
	पढ़ो_aux_reg(ARC_REG_IC_CTRL);	/* blocks */
पूर्ण

अटल अंतरभूत व्योम
__ic_line_inv_vaddr_local(phys_addr_t paddr, अचिन्हित दीर्घ vaddr,
			  अचिन्हित दीर्घ sz)
अणु
	स्थिर पूर्णांक full_page = __builtin_स्थिरant_p(sz) && sz == PAGE_SIZE;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	(*_cache_line_loop_ic_fn)(paddr, vaddr, sz, OP_INV_IC, full_page);
	local_irq_restore(flags);
पूर्ण

#अगर_अघोषित CONFIG_SMP

#घोषणा __ic_line_inv_vaddr(p, v, s)	__ic_line_inv_vaddr_local(p, v, s)

#अन्यथा

काष्ठा ic_inv_args अणु
	phys_addr_t paddr, vaddr;
	पूर्णांक sz;
पूर्ण;

अटल व्योम __ic_line_inv_vaddr_helper(व्योम *info)
अणु
        काष्ठा ic_inv_args *ic_inv = info;

        __ic_line_inv_vaddr_local(ic_inv->paddr, ic_inv->vaddr, ic_inv->sz);
पूर्ण

अटल व्योम __ic_line_inv_vaddr(phys_addr_t paddr, अचिन्हित दीर्घ vaddr,
				अचिन्हित दीर्घ sz)
अणु
	काष्ठा ic_inv_args ic_inv = अणु
		.paddr = paddr,
		.vaddr = vaddr,
		.sz    = sz
	पूर्ण;

	on_each_cpu(__ic_line_inv_vaddr_helper, &ic_inv, 1);
पूर्ण

#पूर्ण_अगर	/* CONFIG_SMP */

#अन्यथा	/* !CONFIG_ARC_HAS_ICACHE */

#घोषणा __ic_entire_inv()
#घोषणा __ic_line_inv_vaddr(pstart, vstart, sz)

#पूर्ण_अगर /* CONFIG_ARC_HAS_ICACHE */

noअंतरभूत व्योम slc_op_rgn(phys_addr_t paddr, अचिन्हित दीर्घ sz, स्थिर पूर्णांक op)
अणु
#अगर_घोषित CONFIG_ISA_ARCV2
	/*
	 * SLC is shared between all cores and concurrent aux operations from
	 * multiple cores need to be serialized using a spinlock
	 * A concurrent operation can be silently ignored and/or the old/new
	 * operation can reमुख्य incomplete क्रमever (lockup in SLC_CTRL_BUSY loop
	 * below)
	 */
	अटल DEFINE_SPINLOCK(lock);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ctrl;
	phys_addr_t end;

	spin_lock_irqsave(&lock, flags);

	/*
	 * The Region Flush operation is specअगरied by CTRL.RGN_OP[11..9]
	 *  - b'000 (शेष) is Flush,
	 *  - b'001 is Invalidate अगर CTRL.IM == 0
	 *  - b'001 is Flush-n-Invalidate अगर CTRL.IM == 1
	 */
	ctrl = पढ़ो_aux_reg(ARC_REG_SLC_CTRL);

	/* Don't rely on शेष value of IM bit */
	अगर (!(op & OP_FLUSH))		/* i.e. OP_INV */
		ctrl &= ~SLC_CTRL_IM;	/* clear IM: Disable flush beक्रमe Inv */
	अन्यथा
		ctrl |= SLC_CTRL_IM;

	अगर (op & OP_INV)
		ctrl |= SLC_CTRL_RGN_OP_INV;	/* Inv or flush-n-inv */
	अन्यथा
		ctrl &= ~SLC_CTRL_RGN_OP_INV;

	ग_लिखो_aux_reg(ARC_REG_SLC_CTRL, ctrl);

	/*
	 * Lower bits are ignored, no need to clip
	 * END needs to be setup beक्रमe START (latter triggers the operation)
	 * END can't be same as START, so add (l2_line_sz - 1) to sz
	 */
	end = paddr + sz + l2_line_sz - 1;
	अगर (is_pae40_enabled())
		ग_लिखो_aux_reg(ARC_REG_SLC_RGN_END1, upper_32_bits(end));

	ग_लिखो_aux_reg(ARC_REG_SLC_RGN_END, lower_32_bits(end));

	अगर (is_pae40_enabled())
		ग_लिखो_aux_reg(ARC_REG_SLC_RGN_START1, upper_32_bits(paddr));

	ग_लिखो_aux_reg(ARC_REG_SLC_RGN_START, lower_32_bits(paddr));

	/* Make sure "busy" bit reports correct stataus, see STAR 9001165532 */
	पढ़ो_aux_reg(ARC_REG_SLC_CTRL);

	जबतक (पढ़ो_aux_reg(ARC_REG_SLC_CTRL) & SLC_CTRL_BUSY);

	spin_unlock_irqrestore(&lock, flags);
#पूर्ण_अगर
पूर्ण

noअंतरभूत व्योम slc_op_line(phys_addr_t paddr, अचिन्हित दीर्घ sz, स्थिर पूर्णांक op)
अणु
#अगर_घोषित CONFIG_ISA_ARCV2
	/*
	 * SLC is shared between all cores and concurrent aux operations from
	 * multiple cores need to be serialized using a spinlock
	 * A concurrent operation can be silently ignored and/or the old/new
	 * operation can reमुख्य incomplete क्रमever (lockup in SLC_CTRL_BUSY loop
	 * below)
	 */
	अटल DEFINE_SPINLOCK(lock);

	स्थिर अचिन्हित दीर्घ SLC_LINE_MASK = ~(l2_line_sz - 1);
	अचिन्हित पूर्णांक ctrl, cmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक num_lines;

	spin_lock_irqsave(&lock, flags);

	ctrl = पढ़ो_aux_reg(ARC_REG_SLC_CTRL);

	/* Don't rely on शेष value of IM bit */
	अगर (!(op & OP_FLUSH))		/* i.e. OP_INV */
		ctrl &= ~SLC_CTRL_IM;	/* clear IM: Disable flush beक्रमe Inv */
	अन्यथा
		ctrl |= SLC_CTRL_IM;

	ग_लिखो_aux_reg(ARC_REG_SLC_CTRL, ctrl);

	cmd = op & OP_INV ? ARC_AUX_SLC_IVDL : ARC_AUX_SLC_FLDL;

	sz += paddr & ~SLC_LINE_MASK;
	paddr &= SLC_LINE_MASK;

	num_lines = DIV_ROUND_UP(sz, l2_line_sz);

	जबतक (num_lines-- > 0) अणु
		ग_लिखो_aux_reg(cmd, paddr);
		paddr += l2_line_sz;
	पूर्ण

	/* Make sure "busy" bit reports correct stataus, see STAR 9001165532 */
	पढ़ो_aux_reg(ARC_REG_SLC_CTRL);

	जबतक (पढ़ो_aux_reg(ARC_REG_SLC_CTRL) & SLC_CTRL_BUSY);

	spin_unlock_irqrestore(&lock, flags);
#पूर्ण_अगर
पूर्ण

#घोषणा slc_op(paddr, sz, op)	slc_op_rgn(paddr, sz, op)

noअंतरभूत अटल व्योम slc_entire_op(स्थिर पूर्णांक op)
अणु
	अचिन्हित पूर्णांक ctrl, r = ARC_REG_SLC_CTRL;

	ctrl = पढ़ो_aux_reg(r);

	अगर (!(op & OP_FLUSH))		/* i.e. OP_INV */
		ctrl &= ~SLC_CTRL_IM;	/* clear IM: Disable flush beक्रमe Inv */
	अन्यथा
		ctrl |= SLC_CTRL_IM;

	ग_लिखो_aux_reg(r, ctrl);

	अगर (op & OP_INV)	/* Inv or flush-n-inv use same cmd reg */
		ग_लिखो_aux_reg(ARC_REG_SLC_INVALIDATE, 0x1);
	अन्यथा
		ग_लिखो_aux_reg(ARC_REG_SLC_FLUSH, 0x1);

	/* Make sure "busy" bit reports correct stataus, see STAR 9001165532 */
	पढ़ो_aux_reg(r);

	/* Important to रुको क्रम flush to complete */
	जबतक (पढ़ो_aux_reg(r) & SLC_CTRL_BUSY);
पूर्ण

अटल अंतरभूत व्योम arc_slc_disable(व्योम)
अणु
	स्थिर पूर्णांक r = ARC_REG_SLC_CTRL;

	slc_entire_op(OP_FLUSH_N_INV);
	ग_लिखो_aux_reg(r, पढ़ो_aux_reg(r) | SLC_CTRL_DIS);
पूर्ण

अटल अंतरभूत व्योम arc_slc_enable(व्योम)
अणु
	स्थिर पूर्णांक r = ARC_REG_SLC_CTRL;

	ग_लिखो_aux_reg(r, पढ़ो_aux_reg(r) & ~SLC_CTRL_DIS);
पूर्ण

/***********************************************************
 * Exported APIs
 */

/*
 * Handle cache congruency of kernel and userspace mappings of page when kernel
 * ग_लिखोs-to/पढ़ोs-from
 *
 * The idea is to defer flushing of kernel mapping after a WRITE, possible अगर:
 *  -dcache is NOT aliasing, hence any U/K-mappings of page are congruent
 *  -U-mapping करोesn't exist yet क्रम page (finalised in update_mmu_cache)
 *  -In SMP, अगर hardware caches are coherent
 *
 * There's a corollary हाल, where kernel READs from a userspace mapped page.
 * If the U-mapping is not congruent to to K-mapping, क्रमmer needs flushing.
 */
व्योम flush_dcache_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping;

	अगर (!cache_is_vipt_aliasing()) अणु
		clear_bit(PG_dc_clean, &page->flags);
		वापस;
	पूर्ण

	/* करोn't handle anon pages here */
	mapping = page_mapping_file(page);
	अगर (!mapping)
		वापस;

	/*
	 * pagecache page, file not yet mapped to userspace
	 * Make a note that K-mapping is dirty
	 */
	अगर (!mapping_mapped(mapping)) अणु
		clear_bit(PG_dc_clean, &page->flags);
	पूर्ण अन्यथा अगर (page_mapcount(page)) अणु

		/* kernel पढ़ोing from page with U-mapping */
		phys_addr_t paddr = (अचिन्हित दीर्घ)page_address(page);
		अचिन्हित दीर्घ vaddr = page->index << PAGE_SHIFT;

		अगर (addr_not_cache_congruent(paddr, vaddr))
			__flush_dcache_page(paddr, vaddr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_dcache_page);

/*
 * DMA ops क्रम प्रणालीs with L1 cache only
 * Make memory coherent with L1 cache by flushing/invalidating L1 lines
 */
अटल व्योम __dma_cache_wback_inv_l1(phys_addr_t start, अचिन्हित दीर्घ sz)
अणु
	__dc_line_op_k(start, sz, OP_FLUSH_N_INV);
पूर्ण

अटल व्योम __dma_cache_inv_l1(phys_addr_t start, अचिन्हित दीर्घ sz)
अणु
	__dc_line_op_k(start, sz, OP_INV);
पूर्ण

अटल व्योम __dma_cache_wback_l1(phys_addr_t start, अचिन्हित दीर्घ sz)
अणु
	__dc_line_op_k(start, sz, OP_FLUSH);
पूर्ण

/*
 * DMA ops क्रम प्रणालीs with both L1 and L2 caches, but without IOC
 * Both L1 and L2 lines need to be explicitly flushed/invalidated
 */
अटल व्योम __dma_cache_wback_inv_slc(phys_addr_t start, अचिन्हित दीर्घ sz)
अणु
	__dc_line_op_k(start, sz, OP_FLUSH_N_INV);
	slc_op(start, sz, OP_FLUSH_N_INV);
पूर्ण

अटल व्योम __dma_cache_inv_slc(phys_addr_t start, अचिन्हित दीर्घ sz)
अणु
	__dc_line_op_k(start, sz, OP_INV);
	slc_op(start, sz, OP_INV);
पूर्ण

अटल व्योम __dma_cache_wback_slc(phys_addr_t start, अचिन्हित दीर्घ sz)
अणु
	__dc_line_op_k(start, sz, OP_FLUSH);
	slc_op(start, sz, OP_FLUSH);
पूर्ण

/*
 * Exported DMA API
 */
व्योम dma_cache_wback_inv(phys_addr_t start, अचिन्हित दीर्घ sz)
अणु
	__dma_cache_wback_inv(start, sz);
पूर्ण
EXPORT_SYMBOL(dma_cache_wback_inv);

व्योम dma_cache_inv(phys_addr_t start, अचिन्हित दीर्घ sz)
अणु
	__dma_cache_inv(start, sz);
पूर्ण
EXPORT_SYMBOL(dma_cache_inv);

व्योम dma_cache_wback(phys_addr_t start, अचिन्हित दीर्घ sz)
अणु
	__dma_cache_wback(start, sz);
पूर्ण
EXPORT_SYMBOL(dma_cache_wback);

/*
 * This is API क्रम making I/D Caches consistent when modअगरying
 * kernel code (loadable modules, kprobes, kgdb...)
 * This is called on insmod, with kernel भव address क्रम CODE of
 * the module. ARC cache मुख्यtenance ops require PHY address thus we
 * need to convert vदो_स्मृति addr to PHY addr
 */
व्योम flush_icache_range(अचिन्हित दीर्घ kstart, अचिन्हित दीर्घ kend)
अणु
	अचिन्हित पूर्णांक tot_sz;

	WARN(kstart < TASK_SIZE, "%s() can't handle user vaddr", __func__);

	/* Shortcut क्रम bigger flush ranges.
	 * Here we करोn't care अगर this was kernel भव or phy addr
	 */
	tot_sz = kend - kstart;
	अगर (tot_sz > PAGE_SIZE) अणु
		flush_cache_all();
		वापस;
	पूर्ण

	/* Case: Kernel Phy addr (0x8000_0000 onwards) */
	अगर (likely(kstart > PAGE_OFFSET)) अणु
		/*
		 * The 2nd arg despite being paddr will be used to index icache
		 * This is OK since no alternate भव mappings will exist
		 * given the callers क्रम this हाल: kprobe/kgdb in built-in
		 * kernel code only.
		 */
		__sync_icache_dcache(kstart, kstart, kend - kstart);
		वापस;
	पूर्ण

	/*
	 * Case: Kernel Vaddr (0x7000_0000 to 0x7fff_ffff)
	 * (1) ARC Cache Maपूर्णांकenance ops only take Phy addr, hence special
	 *     handling of kernel vaddr.
	 *
	 * (2) Despite @tot_sz being < PAGE_SIZE (bigger हालs handled alपढ़ोy),
	 *     it still needs to handle  a 2 page scenario, where the range
	 *     straddles across 2 भव pages and hence need क्रम loop
	 */
	जबतक (tot_sz > 0) अणु
		अचिन्हित पूर्णांक off, sz;
		अचिन्हित दीर्घ phy, pfn;

		off = kstart % PAGE_SIZE;
		pfn = vदो_स्मृति_to_pfn((व्योम *)kstart);
		phy = (pfn << PAGE_SHIFT) + off;
		sz = min_t(अचिन्हित पूर्णांक, tot_sz, PAGE_SIZE - off);
		__sync_icache_dcache(phy, kstart, sz);
		kstart += sz;
		tot_sz -= sz;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_icache_range);

/*
 * General purpose helper to make I and D cache lines consistent.
 * @paddr is phy addr of region
 * @vaddr is typically user vaddr (अवरोधpoपूर्णांक) or kernel vaddr (vदो_स्मृति)
 *    However in one instance, when called by kprobe (क्रम a अवरोधpt in
 *    builtin kernel code) @vaddr will be paddr only, meaning CDU operation will
 *    use a paddr to index the cache (despite VIPT). This is fine since since a
 *    builtin kernel page will not have any भव mappings.
 *    kprobe on loadable module will be kernel vaddr.
 */
व्योम __sync_icache_dcache(phys_addr_t paddr, अचिन्हित दीर्घ vaddr, पूर्णांक len)
अणु
	__dc_line_op(paddr, vaddr, len, OP_FLUSH_N_INV);
	__ic_line_inv_vaddr(paddr, vaddr, len);
पूर्ण

/* wrapper to compile समय eliminate alignment checks in flush loop */
व्योम __inv_icache_page(phys_addr_t paddr, अचिन्हित दीर्घ vaddr)
अणु
	__ic_line_inv_vaddr(paddr, vaddr, PAGE_SIZE);
पूर्ण

/*
 * wrapper to clearout kernel or userspace mappings of a page
 * For kernel mappings @vaddr == @paddr
 */
व्योम __flush_dcache_page(phys_addr_t paddr, अचिन्हित दीर्घ vaddr)
अणु
	__dc_line_op(paddr, vaddr & PAGE_MASK, PAGE_SIZE, OP_FLUSH_N_INV);
पूर्ण

noअंतरभूत व्योम flush_cache_all(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	__ic_entire_inv();
	__dc_entire_op(OP_FLUSH_N_INV);

	local_irq_restore(flags);

पूर्ण

#अगर_घोषित CONFIG_ARC_CACHE_VIPT_ALIASING

व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	flush_cache_all();
पूर्ण

व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ u_vaddr,
		      अचिन्हित दीर्घ pfn)
अणु
	phys_addr_t paddr = pfn << PAGE_SHIFT;

	u_vaddr &= PAGE_MASK;

	__flush_dcache_page(paddr, u_vaddr);

	अगर (vma->vm_flags & VM_EXEC)
		__inv_icache_page(paddr, u_vaddr);
पूर्ण

व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		       अचिन्हित दीर्घ end)
अणु
	flush_cache_all();
पूर्ण

व्योम flush_anon_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		     अचिन्हित दीर्घ u_vaddr)
अणु
	/* TBD: करो we really need to clear the kernel mapping */
	__flush_dcache_page((phys_addr_t)page_address(page), u_vaddr);
	__flush_dcache_page((phys_addr_t)page_address(page),
			    (phys_addr_t)page_address(page));

पूर्ण

#पूर्ण_अगर

व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
	अचिन्हित दीर्घ u_vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	व्योम *kfrom = kmap_atomic(from);
	व्योम *kto = kmap_atomic(to);
	पूर्णांक clean_src_k_mappings = 0;

	/*
	 * If SRC page was alपढ़ोy mapped in userspace AND it's U-mapping is
	 * not congruent with K-mapping, sync क्रमmer to physical page so that
	 * K-mapping in स_नकल below, sees the right data
	 *
	 * Note that जबतक @u_vaddr refers to DST page's userspace vaddr, it is
	 * equally valid क्रम SRC page as well
	 *
	 * For !VIPT cache, all of this माला_लो compiled out as
	 * addr_not_cache_congruent() is 0
	 */
	अगर (page_mapcount(from) && addr_not_cache_congruent(kfrom, u_vaddr)) अणु
		__flush_dcache_page((अचिन्हित दीर्घ)kfrom, u_vaddr);
		clean_src_k_mappings = 1;
	पूर्ण

	copy_page(kto, kfrom);

	/*
	 * Mark DST page K-mapping as dirty क्रम a later finalization by
	 * update_mmu_cache(). Although the finalization could have been करोne
	 * here as well (given that both vaddr/paddr are available).
	 * But update_mmu_cache() alपढ़ोy has code to करो that क्रम other
	 * non copied user pages (e.g. पढ़ो faults which wire in pagecache page
	 * directly).
	 */
	clear_bit(PG_dc_clean, &to->flags);

	/*
	 * अगर SRC was alपढ़ोy usermapped and non-congruent to kernel mapping
	 * sync the kernel mapping back to physical page
	 */
	अगर (clean_src_k_mappings) अणु
		__flush_dcache_page((अचिन्हित दीर्घ)kfrom, (अचिन्हित दीर्घ)kfrom);
		set_bit(PG_dc_clean, &from->flags);
	पूर्ण अन्यथा अणु
		clear_bit(PG_dc_clean, &from->flags);
	पूर्ण

	kunmap_atomic(kto);
	kunmap_atomic(kfrom);
पूर्ण

व्योम clear_user_page(व्योम *to, अचिन्हित दीर्घ u_vaddr, काष्ठा page *page)
अणु
	clear_page(to);
	clear_bit(PG_dc_clean, &page->flags);
पूर्ण


/**********************************************************************
 * Explicit Cache flush request from user space via syscall
 * Needed क्रम JITs which generate code on the fly
 */
SYSCALL_DEFINE3(cacheflush, uपूर्णांक32_t, start, uपूर्णांक32_t, sz, uपूर्णांक32_t, flags)
अणु
	/* TBD: optimize this */
	flush_cache_all();
	वापस 0;
पूर्ण

/*
 * IO-Coherency (IOC) setup rules:
 *
 * 1. Needs to be at प्रणाली level, so only once by Master core
 *    Non-Masters need not be accessing caches at that समय
 *    - They are either HALT_ON_RESET and kick started much later or
 *    - अगर run on reset, need to ensure that arc_platक्रमm_smp_रुको_to_boot()
 *      करोesn't perturb caches or coherency unit
 *
 * 2. caches (L1 and SLC) need to be purged (flush+inv) beक्रमe setting up IOC,
 *    otherwise any straggler data might behave strangely post IOC enabling
 *
 * 3. All Caches need to be disabled when setting up IOC to elide any in-flight
 *    Coherency transactions
 */
noअंतरभूत व्योम __init arc_ioc_setup(व्योम)
अणु
	अचिन्हित पूर्णांक ioc_base, mem_sz;

	/*
	 * If IOC was alपढ़ोy enabled (due to bootloader) it technically needs to
	 * be reconfigured with aperture base,size corresponding to Linux memory map
	 * which will certainly be dअगरferent than uboot's. But disabling and
	 * reenabling IOC when DMA might be potentially active is tricky business.
	 * To aव्योम अक्रमom memory issues later, just panic here and ask user to
	 * upgrade bootloader to one which करोesn't enable IOC
	 */
	अगर (पढ़ो_aux_reg(ARC_REG_IO_COH_ENABLE) & ARC_IO_COH_ENABLE_BIT)
		panic("IOC already enabled, please upgrade bootloader!\n");

	अगर (!ioc_enable)
		वापस;

	/* Flush + invalidate + disable L1 dcache */
	__dc_disable();

	/* Flush + invalidate SLC */
	अगर (पढ़ो_aux_reg(ARC_REG_SLC_BCR))
		slc_entire_op(OP_FLUSH_N_INV);

	/*
	 * currently IOC Aperture covers entire DDR
	 * TBD: fix क्रम PGU + 1GB of low mem
	 * TBD: fix क्रम PAE
	 */
	mem_sz = arc_get_mem_sz();

	अगर (!is_घातer_of_2(mem_sz) || mem_sz < 4096)
		panic("IOC Aperture size must be power of 2 larger than 4KB");

	/*
	 * IOC Aperture size decoded as 2 ^ (SIZE + 2) KB,
	 * so setting 0x11 implies 512MB, 0x12 implies 1GB...
	 */
	ग_लिखो_aux_reg(ARC_REG_IO_COH_AP0_SIZE, order_base_2(mem_sz >> 10) - 2);

	/* क्रम now assume kernel base is start of IOC aperture */
	ioc_base = CONFIG_LINUX_RAM_BASE;

	अगर (ioc_base % mem_sz != 0)
		panic("IOC Aperture start must be aligned to the size of the aperture");

	ग_लिखो_aux_reg(ARC_REG_IO_COH_AP0_BASE, ioc_base >> 12);
	ग_लिखो_aux_reg(ARC_REG_IO_COH_PARTIAL, ARC_IO_COH_PARTIAL_BIT);
	ग_लिखो_aux_reg(ARC_REG_IO_COH_ENABLE, ARC_IO_COH_ENABLE_BIT);

	/* Re-enable L1 dcache */
	__dc_enable();
पूर्ण

/*
 * Cache related boot समय checks/setups only needed on master CPU:
 *  - Geometry checks (kernel build and hardware agree: e.g. L1_CACHE_BYTES)
 *    Assume SMP only, so all cores will have same cache config. A check on
 *    one core suffices क्रम all
 *  - IOC setup / dma callbacks only need to be करोne once
 */
व्योम __init arc_cache_init_master(व्योम)
अणु
	अचिन्हित पूर्णांक __maybe_unused cpu = smp_processor_id();

	अगर (IS_ENABLED(CONFIG_ARC_HAS_ICACHE)) अणु
		काष्ठा cpuinfo_arc_cache *ic = &cpuinfo_arc700[cpu].icache;

		अगर (!ic->line_len)
			panic("cache support enabled but non-existent cache\n");

		अगर (ic->line_len != L1_CACHE_BYTES)
			panic("ICache line [%d] != kernel Config [%d]",
			      ic->line_len, L1_CACHE_BYTES);

		/*
		 * In MMU v4 (HS38x) the aliasing icache config uses IVIL/PTAG
		 * pair to provide vaddr/paddr respectively, just as in MMU v3
		 */
		अगर (is_isa_arcv2() && ic->alias)
			_cache_line_loop_ic_fn = __cache_line_loop_v3;
		अन्यथा
			_cache_line_loop_ic_fn = __cache_line_loop;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_ARC_HAS_DCACHE)) अणु
		काष्ठा cpuinfo_arc_cache *dc = &cpuinfo_arc700[cpu].dcache;

		अगर (!dc->line_len)
			panic("cache support enabled but non-existent cache\n");

		अगर (dc->line_len != L1_CACHE_BYTES)
			panic("DCache line [%d] != kernel Config [%d]",
			      dc->line_len, L1_CACHE_BYTES);

		/* check क्रम D-Cache aliasing on ARCompact: ARCv2 has PIPT */
		अगर (is_isa_arcompact()) अणु
			पूर्णांक handled = IS_ENABLED(CONFIG_ARC_CACHE_VIPT_ALIASING);
			पूर्णांक num_colors = dc->sz_k/dc->assoc/TO_KB(PAGE_SIZE);

			अगर (dc->alias) अणु
				अगर (!handled)
					panic("Enable CONFIG_ARC_CACHE_VIPT_ALIASING\n");
				अगर (CACHE_COLORS_NUM != num_colors)
					panic("CACHE_COLORS_NUM not optimized for config\n");
			पूर्ण अन्यथा अगर (!dc->alias && handled) अणु
				panic("Disable CONFIG_ARC_CACHE_VIPT_ALIASING\n");
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Check that SMP_CACHE_BYTES (and hence ARCH_DMA_MINALIGN) is larger
	 * or equal to any cache line length.
	 */
	BUILD_BUG_ON_MSG(L1_CACHE_BYTES > SMP_CACHE_BYTES,
			 "SMP_CACHE_BYTES must be >= any cache line length");
	अगर (is_isa_arcv2() && (l2_line_sz > SMP_CACHE_BYTES))
		panic("L2 Cache line [%d] > kernel Config [%d]\n",
		      l2_line_sz, SMP_CACHE_BYTES);

	/* Note that SLC disable not क्रमmally supported till HS 3.0 */
	अगर (is_isa_arcv2() && l2_line_sz && !slc_enable)
		arc_slc_disable();

	अगर (is_isa_arcv2() && ioc_exists)
		arc_ioc_setup();

	अगर (is_isa_arcv2() && l2_line_sz && slc_enable) अणु
		__dma_cache_wback_inv = __dma_cache_wback_inv_slc;
		__dma_cache_inv = __dma_cache_inv_slc;
		__dma_cache_wback = __dma_cache_wback_slc;
	पूर्ण अन्यथा अणु
		__dma_cache_wback_inv = __dma_cache_wback_inv_l1;
		__dma_cache_inv = __dma_cache_inv_l1;
		__dma_cache_wback = __dma_cache_wback_l1;
	पूर्ण
	/*
	 * In हाल of IOC (say IOC+SLC हाल), poपूर्णांकers above could still be set
	 * but end up not being relevant as the first function in chain is not
	 * called at all क्रम devices using coherent DMA.
	 *     arch_sync_dma_क्रम_cpu() -> dma_cache_*() -> __dma_cache_*()
	 */
पूर्ण

व्योम __ref arc_cache_init(व्योम)
अणु
	अचिन्हित पूर्णांक __maybe_unused cpu = smp_processor_id();
	अक्षर str[256];

	pr_info("%s", arc_cache_mumbojumbo(0, str, माप(str)));

	अगर (!cpu)
		arc_cache_init_master();

	/*
	 * In PAE regime, TLB and cache मुख्यtenance ops take wider addresses
	 * And even अगर PAE is not enabled in kernel, the upper 32-bits still need
	 * to be zeroed to keep the ops sane.
	 * As an optimization क्रम more common !PAE enabled हाल, zero them out
	 * once at init, rather than checking/setting to 0 क्रम every runसमय op
	 */
	अगर (is_isa_arcv2() && pae40_exist_but_not_enab()) अणु

		अगर (IS_ENABLED(CONFIG_ARC_HAS_ICACHE))
			ग_लिखो_aux_reg(ARC_REG_IC_PTAG_HI, 0);

		अगर (IS_ENABLED(CONFIG_ARC_HAS_DCACHE))
			ग_लिखो_aux_reg(ARC_REG_DC_PTAG_HI, 0);

		अगर (l2_line_sz) अणु
			ग_लिखो_aux_reg(ARC_REG_SLC_RGN_END1, 0);
			ग_लिखो_aux_reg(ARC_REG_SLC_RGN_START1, 0);
		पूर्ण
	पूर्ण
पूर्ण
