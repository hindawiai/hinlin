<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 */

#अगर_अघोषित __ARCH_ARM_MACH_MSM_IOMMU_HW_8XXX_H
#घोषणा __ARCH_ARM_MACH_MSM_IOMMU_HW_8XXX_H

#घोषणा CTX_SHIFT 12

#घोषणा GET_GLOBAL_REG(reg, base) (पढ़ोl((base) + (reg)))
#घोषणा GET_CTX_REG(reg, base, ctx) \
				(पढ़ोl((base) + (reg) + ((ctx) << CTX_SHIFT)))

#घोषणा SET_GLOBAL_REG(reg, base, val)	ग_लिखोl((val), ((base) + (reg)))

#घोषणा SET_CTX_REG(reg, base, ctx, val) \
			ग_लिखोl((val), ((base) + (reg) + ((ctx) << CTX_SHIFT)))

/* Wrappers क्रम numbered रेजिस्टरs */
#घोषणा SET_GLOBAL_REG_N(b, n, r, v) SET_GLOBAL_REG(b, ((r) + (n << 2)), (v))
#घोषणा GET_GLOBAL_REG_N(b, n, r)    GET_GLOBAL_REG(b, ((r) + (n << 2)))

/* Field wrappers */
#घोषणा GET_GLOBAL_FIELD(b, r, F)    GET_FIELD(((b) + (r)), F##_MASK, F##_SHIFT)
#घोषणा GET_CONTEXT_FIELD(b, c, r, F)	\
	GET_FIELD(((b) + (r) + ((c) << CTX_SHIFT)), F##_MASK, F##_SHIFT)

#घोषणा SET_GLOBAL_FIELD(b, r, F, v) \
	SET_FIELD(((b) + (r)), F##_MASK, F##_SHIFT, (v))
#घोषणा SET_CONTEXT_FIELD(b, c, r, F, v)	\
	SET_FIELD(((b) + (r) + ((c) << CTX_SHIFT)), F##_MASK, F##_SHIFT, (v))

#घोषणा GET_FIELD(addr, mask, shअगरt)  ((पढ़ोl(addr) >> (shअगरt)) & (mask))

#घोषणा SET_FIELD(addr, mask, shअगरt, v) \
करो अणु \
	पूर्णांक t = पढ़ोl(addr); \
	ग_लिखोl((t & ~((mask) << (shअगरt))) + (((v) & (mask)) << (shअगरt)), addr);\
पूर्ण जबतक (0)


#घोषणा NUM_FL_PTE	4096
#घोषणा NUM_SL_PTE	256
#घोषणा NUM_TEX_CLASS	8

/* First-level page table bits */
#घोषणा FL_BASE_MASK		0xFFFFFC00
#घोषणा FL_TYPE_TABLE		(1 << 0)
#घोषणा FL_TYPE_SECT		(2 << 0)
#घोषणा FL_SUPERSECTION		(1 << 18)
#घोषणा FL_AP_WRITE		(1 << 10)
#घोषणा FL_AP_READ		(1 << 11)
#घोषणा FL_SHARED		(1 << 16)
#घोषणा FL_BUFFERABLE		(1 << 2)
#घोषणा FL_CACHEABLE		(1 << 3)
#घोषणा FL_TEX0			(1 << 12)
#घोषणा FL_OFFSET(va)		(((va) & 0xFFF00000) >> 20)
#घोषणा FL_NG			(1 << 17)

/* Second-level page table bits */
#घोषणा SL_BASE_MASK_LARGE	0xFFFF0000
#घोषणा SL_BASE_MASK_SMALL	0xFFFFF000
#घोषणा SL_TYPE_LARGE		(1 << 0)
#घोषणा SL_TYPE_SMALL		(2 << 0)
#घोषणा SL_AP0			(1 << 4)
#घोषणा SL_AP1			(2 << 4)
#घोषणा SL_SHARED		(1 << 10)
#घोषणा SL_BUFFERABLE		(1 << 2)
#घोषणा SL_CACHEABLE		(1 << 3)
#घोषणा SL_TEX0			(1 << 6)
#घोषणा SL_OFFSET(va)		(((va) & 0xFF000) >> 12)
#घोषणा SL_NG			(1 << 11)

/* Memory type and cache policy attributes */
#घोषणा MT_SO			0
#घोषणा MT_DEV			1
#घोषणा MT_NORMAL		2
#घोषणा CP_NONCACHED		0
#घोषणा CP_WB_WA		1
#घोषणा CP_WT			2
#घोषणा CP_WB_NWA		3

/* Global रेजिस्टर setters / getters */
#घोषणा SET_M2VCBR_N(b, N, v)	 SET_GLOBAL_REG_N(M2VCBR_N, N, (b), (v))
#घोषणा SET_CBACR_N(b, N, v)	 SET_GLOBAL_REG_N(CBACR_N, N, (b), (v))
#घोषणा SET_TLBRSW(b, v)	 SET_GLOBAL_REG(TLBRSW, (b), (v))
#घोषणा SET_TLBTR0(b, v)	 SET_GLOBAL_REG(TLBTR0, (b), (v))
#घोषणा SET_TLBTR1(b, v)	 SET_GLOBAL_REG(TLBTR1, (b), (v))
#घोषणा SET_TLBTR2(b, v)	 SET_GLOBAL_REG(TLBTR2, (b), (v))
#घोषणा SET_TESTBUSCR(b, v)	 SET_GLOBAL_REG(TESTBUSCR, (b), (v))
#घोषणा SET_GLOBAL_TLBIALL(b, v) SET_GLOBAL_REG(GLOBAL_TLBIALL, (b), (v))
#घोषणा SET_TLBIVMID(b, v)	 SET_GLOBAL_REG(TLBIVMID, (b), (v))
#घोषणा SET_CR(b, v)		 SET_GLOBAL_REG(CR, (b), (v))
#घोषणा SET_EAR(b, v)		 SET_GLOBAL_REG(EAR, (b), (v))
#घोषणा SET_ESR(b, v)		 SET_GLOBAL_REG(ESR, (b), (v))
#घोषणा SET_ESRRESTORE(b, v)	 SET_GLOBAL_REG(ESRRESTORE, (b), (v))
#घोषणा SET_ESYNR0(b, v)	 SET_GLOBAL_REG(ESYNR0, (b), (v))
#घोषणा SET_ESYNR1(b, v)	 SET_GLOBAL_REG(ESYNR1, (b), (v))
#घोषणा SET_RPU_ACR(b, v)	 SET_GLOBAL_REG(RPU_ACR, (b), (v))

#घोषणा GET_M2VCBR_N(b, N)	 GET_GLOBAL_REG_N(M2VCBR_N, N, (b))
#घोषणा GET_CBACR_N(b, N)	 GET_GLOBAL_REG_N(CBACR_N, N, (b))
#घोषणा GET_TLBTR0(b)		 GET_GLOBAL_REG(TLBTR0, (b))
#घोषणा GET_TLBTR1(b)		 GET_GLOBAL_REG(TLBTR1, (b))
#घोषणा GET_TLBTR2(b)		 GET_GLOBAL_REG(TLBTR2, (b))
#घोषणा GET_TESTBUSCR(b)	 GET_GLOBAL_REG(TESTBUSCR, (b))
#घोषणा GET_GLOBAL_TLBIALL(b)	 GET_GLOBAL_REG(GLOBAL_TLBIALL, (b))
#घोषणा GET_TLBIVMID(b)		 GET_GLOBAL_REG(TLBIVMID, (b))
#घोषणा GET_CR(b)		 GET_GLOBAL_REG(CR, (b))
#घोषणा GET_EAR(b)		 GET_GLOBAL_REG(EAR, (b))
#घोषणा GET_ESR(b)		 GET_GLOBAL_REG(ESR, (b))
#घोषणा GET_ESRRESTORE(b)	 GET_GLOBAL_REG(ESRRESTORE, (b))
#घोषणा GET_ESYNR0(b)		 GET_GLOBAL_REG(ESYNR0, (b))
#घोषणा GET_ESYNR1(b)		 GET_GLOBAL_REG(ESYNR1, (b))
#घोषणा GET_REV(b)		 GET_GLOBAL_REG(REV, (b))
#घोषणा GET_IDR(b)		 GET_GLOBAL_REG(IDR, (b))
#घोषणा GET_RPU_ACR(b)		 GET_GLOBAL_REG(RPU_ACR, (b))


/* Context रेजिस्टर setters/getters */
#घोषणा SET_SCTLR(b, c, v)	 SET_CTX_REG(SCTLR, (b), (c), (v))
#घोषणा SET_ACTLR(b, c, v)	 SET_CTX_REG(ACTLR, (b), (c), (v))
#घोषणा SET_CONTEXTIDR(b, c, v)	 SET_CTX_REG(CONTEXTIDR, (b), (c), (v))
#घोषणा SET_TTBR0(b, c, v)	 SET_CTX_REG(TTBR0, (b), (c), (v))
#घोषणा SET_TTBR1(b, c, v)	 SET_CTX_REG(TTBR1, (b), (c), (v))
#घोषणा SET_TTBCR(b, c, v)	 SET_CTX_REG(TTBCR, (b), (c), (v))
#घोषणा SET_PAR(b, c, v)	 SET_CTX_REG(PAR, (b), (c), (v))
#घोषणा SET_FSR(b, c, v)	 SET_CTX_REG(FSR, (b), (c), (v))
#घोषणा SET_FSRRESTORE(b, c, v)	 SET_CTX_REG(FSRRESTORE, (b), (c), (v))
#घोषणा SET_FAR(b, c, v)	 SET_CTX_REG(FAR, (b), (c), (v))
#घोषणा SET_FSYNR0(b, c, v)	 SET_CTX_REG(FSYNR0, (b), (c), (v))
#घोषणा SET_FSYNR1(b, c, v)	 SET_CTX_REG(FSYNR1, (b), (c), (v))
#घोषणा SET_PRRR(b, c, v)	 SET_CTX_REG(PRRR, (b), (c), (v))
#घोषणा SET_NMRR(b, c, v)	 SET_CTX_REG(NMRR, (b), (c), (v))
#घोषणा SET_TLBLKCR(b, c, v)	 SET_CTX_REG(TLBLCKR, (b), (c), (v))
#घोषणा SET_V2PSR(b, c, v)	 SET_CTX_REG(V2PSR, (b), (c), (v))
#घोषणा SET_TLBFLPTER(b, c, v)	 SET_CTX_REG(TLBFLPTER, (b), (c), (v))
#घोषणा SET_TLBSLPTER(b, c, v)	 SET_CTX_REG(TLBSLPTER, (b), (c), (v))
#घोषणा SET_BFBCR(b, c, v)	 SET_CTX_REG(BFBCR, (b), (c), (v))
#घोषणा SET_CTX_TLBIALL(b, c, v) SET_CTX_REG(CTX_TLBIALL, (b), (c), (v))
#घोषणा SET_TLBIASID(b, c, v)	 SET_CTX_REG(TLBIASID, (b), (c), (v))
#घोषणा SET_TLBIVA(b, c, v)	 SET_CTX_REG(TLBIVA, (b), (c), (v))
#घोषणा SET_TLBIVAA(b, c, v)	 SET_CTX_REG(TLBIVAA, (b), (c), (v))
#घोषणा SET_V2PPR(b, c, v)	 SET_CTX_REG(V2PPR, (b), (c), (v))
#घोषणा SET_V2PPW(b, c, v)	 SET_CTX_REG(V2PPW, (b), (c), (v))
#घोषणा SET_V2PUR(b, c, v)	 SET_CTX_REG(V2PUR, (b), (c), (v))
#घोषणा SET_V2PUW(b, c, v)	 SET_CTX_REG(V2PUW, (b), (c), (v))
#घोषणा SET_RESUME(b, c, v)	 SET_CTX_REG(RESUME, (b), (c), (v))

#घोषणा GET_SCTLR(b, c)		 GET_CTX_REG(SCTLR, (b), (c))
#घोषणा GET_ACTLR(b, c)		 GET_CTX_REG(ACTLR, (b), (c))
#घोषणा GET_CONTEXTIDR(b, c)	 GET_CTX_REG(CONTEXTIDR, (b), (c))
#घोषणा GET_TTBR0(b, c)		 GET_CTX_REG(TTBR0, (b), (c))
#घोषणा GET_TTBR1(b, c)		 GET_CTX_REG(TTBR1, (b), (c))
#घोषणा GET_TTBCR(b, c)		 GET_CTX_REG(TTBCR, (b), (c))
#घोषणा GET_PAR(b, c)		 GET_CTX_REG(PAR, (b), (c))
#घोषणा GET_FSR(b, c)		 GET_CTX_REG(FSR, (b), (c))
#घोषणा GET_FSRRESTORE(b, c)	 GET_CTX_REG(FSRRESTORE, (b), (c))
#घोषणा GET_FAR(b, c)		 GET_CTX_REG(FAR, (b), (c))
#घोषणा GET_FSYNR0(b, c)	 GET_CTX_REG(FSYNR0, (b), (c))
#घोषणा GET_FSYNR1(b, c)	 GET_CTX_REG(FSYNR1, (b), (c))
#घोषणा GET_PRRR(b, c)		 GET_CTX_REG(PRRR, (b), (c))
#घोषणा GET_NMRR(b, c)		 GET_CTX_REG(NMRR, (b), (c))
#घोषणा GET_TLBLCKR(b, c)	 GET_CTX_REG(TLBLCKR, (b), (c))
#घोषणा GET_V2PSR(b, c)		 GET_CTX_REG(V2PSR, (b), (c))
#घोषणा GET_TLBFLPTER(b, c)	 GET_CTX_REG(TLBFLPTER, (b), (c))
#घोषणा GET_TLBSLPTER(b, c)	 GET_CTX_REG(TLBSLPTER, (b), (c))
#घोषणा GET_BFBCR(b, c)		 GET_CTX_REG(BFBCR, (b), (c))
#घोषणा GET_CTX_TLBIALL(b, c)	 GET_CTX_REG(CTX_TLBIALL, (b), (c))
#घोषणा GET_TLBIASID(b, c)	 GET_CTX_REG(TLBIASID, (b), (c))
#घोषणा GET_TLBIVA(b, c)	 GET_CTX_REG(TLBIVA, (b), (c))
#घोषणा GET_TLBIVAA(b, c)	 GET_CTX_REG(TLBIVAA, (b), (c))
#घोषणा GET_V2PPR(b, c)		 GET_CTX_REG(V2PPR, (b), (c))
#घोषणा GET_V2PPW(b, c)		 GET_CTX_REG(V2PPW, (b), (c))
#घोषणा GET_V2PUR(b, c)		 GET_CTX_REG(V2PUR, (b), (c))
#घोषणा GET_V2PUW(b, c)		 GET_CTX_REG(V2PUW, (b), (c))
#घोषणा GET_RESUME(b, c)	 GET_CTX_REG(RESUME, (b), (c))


/* Global field setters / getters */
/* Global Field Setters: */
/* CBACR_N */
#घोषणा SET_RWVMID(b, n, v)   SET_GLOBAL_FIELD(b, (n<<2)|(CBACR_N), RWVMID, v)
#घोषणा SET_RWE(b, n, v)      SET_GLOBAL_FIELD(b, (n<<2)|(CBACR_N), RWE, v)
#घोषणा SET_RWGE(b, n, v)     SET_GLOBAL_FIELD(b, (n<<2)|(CBACR_N), RWGE, v)
#घोषणा SET_CBVMID(b, n, v)   SET_GLOBAL_FIELD(b, (n<<2)|(CBACR_N), CBVMID, v)
#घोषणा SET_IRPTNDX(b, n, v)  SET_GLOBAL_FIELD(b, (n<<2)|(CBACR_N), IRPTNDX, v)


/* M2VCBR_N */
#घोषणा SET_VMID(b, n, v)     SET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), VMID, v)
#घोषणा SET_CBNDX(b, n, v)    SET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), CBNDX, v)
#घोषणा SET_BYPASSD(b, n, v)  SET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BYPASSD, v)
#घोषणा SET_BPRCOSH(b, n, v)  SET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPRCOSH, v)
#घोषणा SET_BPRCISH(b, n, v)  SET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPRCISH, v)
#घोषणा SET_BPRCNSH(b, n, v)  SET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPRCNSH, v)
#घोषणा SET_BPSHCFG(b, n, v)  SET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPSHCFG, v)
#घोषणा SET_NSCFG(b, n, v)    SET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), NSCFG, v)
#घोषणा SET_BPMTCFG(b, n, v)  SET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPMTCFG, v)
#घोषणा SET_BPMEMTYPE(b, n, v) \
	SET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPMEMTYPE, v)


/* CR */
#घोषणा SET_RPUE(b, v)		 SET_GLOBAL_FIELD(b, CR, RPUE, v)
#घोषणा SET_RPUERE(b, v)	 SET_GLOBAL_FIELD(b, CR, RPUERE, v)
#घोषणा SET_RPUEIE(b, v)	 SET_GLOBAL_FIELD(b, CR, RPUEIE, v)
#घोषणा SET_DCDEE(b, v)		 SET_GLOBAL_FIELD(b, CR, DCDEE, v)
#घोषणा SET_CLIENTPD(b, v)       SET_GLOBAL_FIELD(b, CR, CLIENTPD, v)
#घोषणा SET_STALLD(b, v)	 SET_GLOBAL_FIELD(b, CR, STALLD, v)
#घोषणा SET_TLBLKCRWE(b, v)      SET_GLOBAL_FIELD(b, CR, TLBLKCRWE, v)
#घोषणा SET_CR_TLBIALLCFG(b, v)  SET_GLOBAL_FIELD(b, CR, CR_TLBIALLCFG, v)
#घोषणा SET_TLBIVMIDCFG(b, v)    SET_GLOBAL_FIELD(b, CR, TLBIVMIDCFG, v)
#घोषणा SET_CR_HUME(b, v)        SET_GLOBAL_FIELD(b, CR, CR_HUME, v)


/* ESR */
#घोषणा SET_CFG(b, v)		 SET_GLOBAL_FIELD(b, ESR, CFG, v)
#घोषणा SET_BYPASS(b, v)	 SET_GLOBAL_FIELD(b, ESR, BYPASS, v)
#घोषणा SET_ESR_MULTI(b, v)      SET_GLOBAL_FIELD(b, ESR, ESR_MULTI, v)


/* ESYNR0 */
#घोषणा SET_ESYNR0_AMID(b, v)    SET_GLOBAL_FIELD(b, ESYNR0, ESYNR0_AMID, v)
#घोषणा SET_ESYNR0_APID(b, v)    SET_GLOBAL_FIELD(b, ESYNR0, ESYNR0_APID, v)
#घोषणा SET_ESYNR0_ABID(b, v)    SET_GLOBAL_FIELD(b, ESYNR0, ESYNR0_ABID, v)
#घोषणा SET_ESYNR0_AVMID(b, v)   SET_GLOBAL_FIELD(b, ESYNR0, ESYNR0_AVMID, v)
#घोषणा SET_ESYNR0_ATID(b, v)    SET_GLOBAL_FIELD(b, ESYNR0, ESYNR0_ATID, v)


/* ESYNR1 */
#घोषणा SET_ESYNR1_AMEMTYPE(b, v) \
			SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AMEMTYPE, v)
#घोषणा SET_ESYNR1_ASHARED(b, v)  SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_ASHARED, v)
#घोषणा SET_ESYNR1_AINNERSHARED(b, v) \
			SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AINNERSHARED, v)
#घोषणा SET_ESYNR1_APRIV(b, v)   SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_APRIV, v)
#घोषणा SET_ESYNR1_APROTNS(b, v) SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_APROTNS, v)
#घोषणा SET_ESYNR1_AINST(b, v)   SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AINST, v)
#घोषणा SET_ESYNR1_AWRITE(b, v)  SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AWRITE, v)
#घोषणा SET_ESYNR1_ABURST(b, v)  SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_ABURST, v)
#घोषणा SET_ESYNR1_ALEN(b, v)    SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_ALEN, v)
#घोषणा SET_ESYNR1_ASIZE(b, v)   SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_ASIZE, v)
#घोषणा SET_ESYNR1_ALOCK(b, v)   SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_ALOCK, v)
#घोषणा SET_ESYNR1_AOOO(b, v)    SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AOOO, v)
#घोषणा SET_ESYNR1_AFULL(b, v)   SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AFULL, v)
#घोषणा SET_ESYNR1_AC(b, v)      SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AC, v)
#घोषणा SET_ESYNR1_DCD(b, v)     SET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_DCD, v)


/* TESTBUSCR */
#घोषणा SET_TBE(b, v)		 SET_GLOBAL_FIELD(b, TESTBUSCR, TBE, v)
#घोषणा SET_SPDMBE(b, v)	 SET_GLOBAL_FIELD(b, TESTBUSCR, SPDMBE, v)
#घोषणा SET_WGSEL(b, v)		 SET_GLOBAL_FIELD(b, TESTBUSCR, WGSEL, v)
#घोषणा SET_TBLSEL(b, v)	 SET_GLOBAL_FIELD(b, TESTBUSCR, TBLSEL, v)
#घोषणा SET_TBHSEL(b, v)	 SET_GLOBAL_FIELD(b, TESTBUSCR, TBHSEL, v)
#घोषणा SET_SPDM0SEL(b, v)       SET_GLOBAL_FIELD(b, TESTBUSCR, SPDM0SEL, v)
#घोषणा SET_SPDM1SEL(b, v)       SET_GLOBAL_FIELD(b, TESTBUSCR, SPDM1SEL, v)
#घोषणा SET_SPDM2SEL(b, v)       SET_GLOBAL_FIELD(b, TESTBUSCR, SPDM2SEL, v)
#घोषणा SET_SPDM3SEL(b, v)       SET_GLOBAL_FIELD(b, TESTBUSCR, SPDM3SEL, v)


/* TLBIVMID */
#घोषणा SET_TLBIVMID_VMID(b, v)  SET_GLOBAL_FIELD(b, TLBIVMID, TLBIVMID_VMID, v)


/* TLBRSW */
#घोषणा SET_TLBRSW_INDEX(b, v)   SET_GLOBAL_FIELD(b, TLBRSW, TLBRSW_INDEX, v)
#घोषणा SET_TLBBFBS(b, v)	 SET_GLOBAL_FIELD(b, TLBRSW, TLBBFBS, v)


/* TLBTR0 */
#घोषणा SET_PR(b, v)		 SET_GLOBAL_FIELD(b, TLBTR0, PR, v)
#घोषणा SET_PW(b, v)		 SET_GLOBAL_FIELD(b, TLBTR0, PW, v)
#घोषणा SET_UR(b, v)		 SET_GLOBAL_FIELD(b, TLBTR0, UR, v)
#घोषणा SET_UW(b, v)		 SET_GLOBAL_FIELD(b, TLBTR0, UW, v)
#घोषणा SET_XN(b, v)		 SET_GLOBAL_FIELD(b, TLBTR0, XN, v)
#घोषणा SET_NSDESC(b, v)	 SET_GLOBAL_FIELD(b, TLBTR0, NSDESC, v)
#घोषणा SET_ISH(b, v)		 SET_GLOBAL_FIELD(b, TLBTR0, ISH, v)
#घोषणा SET_SH(b, v)		 SET_GLOBAL_FIELD(b, TLBTR0, SH, v)
#घोषणा SET_MT(b, v)		 SET_GLOBAL_FIELD(b, TLBTR0, MT, v)
#घोषणा SET_DPSIZR(b, v)	 SET_GLOBAL_FIELD(b, TLBTR0, DPSIZR, v)
#घोषणा SET_DPSIZC(b, v)	 SET_GLOBAL_FIELD(b, TLBTR0, DPSIZC, v)


/* TLBTR1 */
#घोषणा SET_TLBTR1_VMID(b, v)    SET_GLOBAL_FIELD(b, TLBTR1, TLBTR1_VMID, v)
#घोषणा SET_TLBTR1_PA(b, v)      SET_GLOBAL_FIELD(b, TLBTR1, TLBTR1_PA, v)


/* TLBTR2 */
#घोषणा SET_TLBTR2_ASID(b, v)    SET_GLOBAL_FIELD(b, TLBTR2, TLBTR2_ASID, v)
#घोषणा SET_TLBTR2_V(b, v)       SET_GLOBAL_FIELD(b, TLBTR2, TLBTR2_V, v)
#घोषणा SET_TLBTR2_NSTID(b, v)   SET_GLOBAL_FIELD(b, TLBTR2, TLBTR2_NSTID, v)
#घोषणा SET_TLBTR2_NV(b, v)      SET_GLOBAL_FIELD(b, TLBTR2, TLBTR2_NV, v)
#घोषणा SET_TLBTR2_VA(b, v)      SET_GLOBAL_FIELD(b, TLBTR2, TLBTR2_VA, v)


/* Global Field Getters */
/* CBACR_N */
#घोषणा GET_RWVMID(b, n)	 GET_GLOBAL_FIELD(b, (n<<2)|(CBACR_N), RWVMID)
#घोषणा GET_RWE(b, n)		 GET_GLOBAL_FIELD(b, (n<<2)|(CBACR_N), RWE)
#घोषणा GET_RWGE(b, n)		 GET_GLOBAL_FIELD(b, (n<<2)|(CBACR_N), RWGE)
#घोषणा GET_CBVMID(b, n)	 GET_GLOBAL_FIELD(b, (n<<2)|(CBACR_N), CBVMID)
#घोषणा GET_IRPTNDX(b, n)	 GET_GLOBAL_FIELD(b, (n<<2)|(CBACR_N), IRPTNDX)


/* M2VCBR_N */
#घोषणा GET_VMID(b, n)       GET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), VMID)
#घोषणा GET_CBNDX(b, n)      GET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), CBNDX)
#घोषणा GET_BYPASSD(b, n)    GET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BYPASSD)
#घोषणा GET_BPRCOSH(b, n)    GET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPRCOSH)
#घोषणा GET_BPRCISH(b, n)    GET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPRCISH)
#घोषणा GET_BPRCNSH(b, n)    GET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPRCNSH)
#घोषणा GET_BPSHCFG(b, n)    GET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPSHCFG)
#घोषणा GET_NSCFG(b, n)      GET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), NSCFG)
#घोषणा GET_BPMTCFG(b, n)    GET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPMTCFG)
#घोषणा GET_BPMEMTYPE(b, n)  GET_GLOBAL_FIELD(b, (n<<2)|(M2VCBR_N), BPMEMTYPE)


/* CR */
#घोषणा GET_RPUE(b)		 GET_GLOBAL_FIELD(b, CR, RPUE)
#घोषणा GET_RPUERE(b)		 GET_GLOBAL_FIELD(b, CR, RPUERE)
#घोषणा GET_RPUEIE(b)		 GET_GLOBAL_FIELD(b, CR, RPUEIE)
#घोषणा GET_DCDEE(b)		 GET_GLOBAL_FIELD(b, CR, DCDEE)
#घोषणा GET_CLIENTPD(b)		 GET_GLOBAL_FIELD(b, CR, CLIENTPD)
#घोषणा GET_STALLD(b)		 GET_GLOBAL_FIELD(b, CR, STALLD)
#घोषणा GET_TLBLKCRWE(b)	 GET_GLOBAL_FIELD(b, CR, TLBLKCRWE)
#घोषणा GET_CR_TLBIALLCFG(b)	 GET_GLOBAL_FIELD(b, CR, CR_TLBIALLCFG)
#घोषणा GET_TLBIVMIDCFG(b)	 GET_GLOBAL_FIELD(b, CR, TLBIVMIDCFG)
#घोषणा GET_CR_HUME(b)		 GET_GLOBAL_FIELD(b, CR, CR_HUME)


/* ESR */
#घोषणा GET_CFG(b)		 GET_GLOBAL_FIELD(b, ESR, CFG)
#घोषणा GET_BYPASS(b)		 GET_GLOBAL_FIELD(b, ESR, BYPASS)
#घोषणा GET_ESR_MULTI(b)	 GET_GLOBAL_FIELD(b, ESR, ESR_MULTI)


/* ESYNR0 */
#घोषणा GET_ESYNR0_AMID(b)	 GET_GLOBAL_FIELD(b, ESYNR0, ESYNR0_AMID)
#घोषणा GET_ESYNR0_APID(b)	 GET_GLOBAL_FIELD(b, ESYNR0, ESYNR0_APID)
#घोषणा GET_ESYNR0_ABID(b)	 GET_GLOBAL_FIELD(b, ESYNR0, ESYNR0_ABID)
#घोषणा GET_ESYNR0_AVMID(b)	 GET_GLOBAL_FIELD(b, ESYNR0, ESYNR0_AVMID)
#घोषणा GET_ESYNR0_ATID(b)	 GET_GLOBAL_FIELD(b, ESYNR0, ESYNR0_ATID)


/* ESYNR1 */
#घोषणा GET_ESYNR1_AMEMTYPE(b)   GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AMEMTYPE)
#घोषणा GET_ESYNR1_ASHARED(b)    GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_ASHARED)
#घोषणा GET_ESYNR1_AINNERSHARED(b) \
			GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AINNERSHARED)
#घोषणा GET_ESYNR1_APRIV(b)      GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_APRIV)
#घोषणा GET_ESYNR1_APROTNS(b)	 GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_APROTNS)
#घोषणा GET_ESYNR1_AINST(b)	 GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AINST)
#घोषणा GET_ESYNR1_AWRITE(b)	 GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AWRITE)
#घोषणा GET_ESYNR1_ABURST(b)	 GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_ABURST)
#घोषणा GET_ESYNR1_ALEN(b)	 GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_ALEN)
#घोषणा GET_ESYNR1_ASIZE(b)	 GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_ASIZE)
#घोषणा GET_ESYNR1_ALOCK(b)	 GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_ALOCK)
#घोषणा GET_ESYNR1_AOOO(b)	 GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AOOO)
#घोषणा GET_ESYNR1_AFULL(b)	 GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AFULL)
#घोषणा GET_ESYNR1_AC(b)	 GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_AC)
#घोषणा GET_ESYNR1_DCD(b)	 GET_GLOBAL_FIELD(b, ESYNR1, ESYNR1_DCD)


/* IDR */
#घोषणा GET_NM2VCBMT(b)		 GET_GLOBAL_FIELD(b, IDR, NM2VCBMT)
#घोषणा GET_HTW(b)		 GET_GLOBAL_FIELD(b, IDR, HTW)
#घोषणा GET_HUM(b)		 GET_GLOBAL_FIELD(b, IDR, HUM)
#घोषणा GET_TLBSIZE(b)		 GET_GLOBAL_FIELD(b, IDR, TLBSIZE)
#घोषणा GET_NCB(b)		 GET_GLOBAL_FIELD(b, IDR, NCB)
#घोषणा GET_NIRPT(b)		 GET_GLOBAL_FIELD(b, IDR, NIRPT)


/* REV */
#घोषणा GET_MAJOR(b)		 GET_GLOBAL_FIELD(b, REV, MAJOR)
#घोषणा GET_MINOR(b)		 GET_GLOBAL_FIELD(b, REV, MINOR)


/* TESTBUSCR */
#घोषणा GET_TBE(b)		 GET_GLOBAL_FIELD(b, TESTBUSCR, TBE)
#घोषणा GET_SPDMBE(b)		 GET_GLOBAL_FIELD(b, TESTBUSCR, SPDMBE)
#घोषणा GET_WGSEL(b)		 GET_GLOBAL_FIELD(b, TESTBUSCR, WGSEL)
#घोषणा GET_TBLSEL(b)		 GET_GLOBAL_FIELD(b, TESTBUSCR, TBLSEL)
#घोषणा GET_TBHSEL(b)		 GET_GLOBAL_FIELD(b, TESTBUSCR, TBHSEL)
#घोषणा GET_SPDM0SEL(b)		 GET_GLOBAL_FIELD(b, TESTBUSCR, SPDM0SEL)
#घोषणा GET_SPDM1SEL(b)		 GET_GLOBAL_FIELD(b, TESTBUSCR, SPDM1SEL)
#घोषणा GET_SPDM2SEL(b)		 GET_GLOBAL_FIELD(b, TESTBUSCR, SPDM2SEL)
#घोषणा GET_SPDM3SEL(b)		 GET_GLOBAL_FIELD(b, TESTBUSCR, SPDM3SEL)


/* TLBIVMID */
#घोषणा GET_TLBIVMID_VMID(b)	 GET_GLOBAL_FIELD(b, TLBIVMID, TLBIVMID_VMID)


/* TLBTR0 */
#घोषणा GET_PR(b)		 GET_GLOBAL_FIELD(b, TLBTR0, PR)
#घोषणा GET_PW(b)		 GET_GLOBAL_FIELD(b, TLBTR0, PW)
#घोषणा GET_UR(b)		 GET_GLOBAL_FIELD(b, TLBTR0, UR)
#घोषणा GET_UW(b)		 GET_GLOBAL_FIELD(b, TLBTR0, UW)
#घोषणा GET_XN(b)		 GET_GLOBAL_FIELD(b, TLBTR0, XN)
#घोषणा GET_NSDESC(b)		 GET_GLOBAL_FIELD(b, TLBTR0, NSDESC)
#घोषणा GET_ISH(b)		 GET_GLOBAL_FIELD(b, TLBTR0, ISH)
#घोषणा GET_SH(b)		 GET_GLOBAL_FIELD(b, TLBTR0, SH)
#घोषणा GET_MT(b)		 GET_GLOBAL_FIELD(b, TLBTR0, MT)
#घोषणा GET_DPSIZR(b)		 GET_GLOBAL_FIELD(b, TLBTR0, DPSIZR)
#घोषणा GET_DPSIZC(b)		 GET_GLOBAL_FIELD(b, TLBTR0, DPSIZC)


/* TLBTR1 */
#घोषणा GET_TLBTR1_VMID(b)	 GET_GLOBAL_FIELD(b, TLBTR1, TLBTR1_VMID)
#घोषणा GET_TLBTR1_PA(b)	 GET_GLOBAL_FIELD(b, TLBTR1, TLBTR1_PA)


/* TLBTR2 */
#घोषणा GET_TLBTR2_ASID(b)	 GET_GLOBAL_FIELD(b, TLBTR2, TLBTR2_ASID)
#घोषणा GET_TLBTR2_V(b)		 GET_GLOBAL_FIELD(b, TLBTR2, TLBTR2_V)
#घोषणा GET_TLBTR2_NSTID(b)	 GET_GLOBAL_FIELD(b, TLBTR2, TLBTR2_NSTID)
#घोषणा GET_TLBTR2_NV(b)	 GET_GLOBAL_FIELD(b, TLBTR2, TLBTR2_NV)
#घोषणा GET_TLBTR2_VA(b)	 GET_GLOBAL_FIELD(b, TLBTR2, TLBTR2_VA)


/* Context Register setters / getters */
/* Context Register setters */
/* ACTLR */
#घोषणा SET_CFERE(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, CFERE, v)
#घोषणा SET_CFEIE(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, CFEIE, v)
#घोषणा SET_PTSHCFG(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, PTSHCFG, v)
#घोषणा SET_RCOSH(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, RCOSH, v)
#घोषणा SET_RCISH(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, RCISH, v)
#घोषणा SET_RCNSH(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, RCNSH, v)
#घोषणा SET_PRIVCFG(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, PRIVCFG, v)
#घोषणा SET_DNA(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, DNA, v)
#घोषणा SET_DNLV2PA(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, DNLV2PA, v)
#घोषणा SET_TLBMCFG(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, TLBMCFG, v)
#घोषणा SET_CFCFG(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, CFCFG, v)
#घोषणा SET_TIPCF(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, TIPCF, v)
#घोषणा SET_V2PCFG(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, V2PCFG, v)
#घोषणा SET_HUME(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, HUME, v)
#घोषणा SET_PTMTCFG(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, PTMTCFG, v)
#घोषणा SET_PTMEMTYPE(b, c, v)	 SET_CONTEXT_FIELD(b, c, ACTLR, PTMEMTYPE, v)


/* BFBCR */
#घोषणा SET_BFBDFE(b, c, v)	 SET_CONTEXT_FIELD(b, c, BFBCR, BFBDFE, v)
#घोषणा SET_BFBSFE(b, c, v)	 SET_CONTEXT_FIELD(b, c, BFBCR, BFBSFE, v)
#घोषणा SET_SFVS(b, c, v)	 SET_CONTEXT_FIELD(b, c, BFBCR, SFVS, v)
#घोषणा SET_FLVIC(b, c, v)	 SET_CONTEXT_FIELD(b, c, BFBCR, FLVIC, v)
#घोषणा SET_SLVIC(b, c, v)	 SET_CONTEXT_FIELD(b, c, BFBCR, SLVIC, v)


/* CONTEXTIDR */
#घोषणा SET_CONTEXTIDR_ASID(b, c, v)   \
		SET_CONTEXT_FIELD(b, c, CONTEXTIDR, CONTEXTIDR_ASID, v)
#घोषणा SET_CONTEXTIDR_PROCID(b, c, v) \
		SET_CONTEXT_FIELD(b, c, CONTEXTIDR, PROCID, v)


/* FSR */
#घोषणा SET_TF(b, c, v)		 SET_CONTEXT_FIELD(b, c, FSR, TF, v)
#घोषणा SET_AFF(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSR, AFF, v)
#घोषणा SET_APF(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSR, APF, v)
#घोषणा SET_TLBMF(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSR, TLBMF, v)
#घोषणा SET_HTWDEEF(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSR, HTWDEEF, v)
#घोषणा SET_HTWSEEF(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSR, HTWSEEF, v)
#घोषणा SET_MHF(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSR, MHF, v)
#घोषणा SET_SL(b, c, v)		 SET_CONTEXT_FIELD(b, c, FSR, SL, v)
#घोषणा SET_SS(b, c, v)		 SET_CONTEXT_FIELD(b, c, FSR, SS, v)
#घोषणा SET_MULTI(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSR, MULTI, v)


/* FSYNR0 */
#घोषणा SET_AMID(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR0, AMID, v)
#घोषणा SET_APID(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR0, APID, v)
#घोषणा SET_ABID(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR0, ABID, v)
#घोषणा SET_ATID(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR0, ATID, v)


/* FSYNR1 */
#घोषणा SET_AMEMTYPE(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR1, AMEMTYPE, v)
#घोषणा SET_ASHARED(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR1, ASHARED, v)
#घोषणा SET_AINNERSHARED(b, c, v)  \
				SET_CONTEXT_FIELD(b, c, FSYNR1, AINNERSHARED, v)
#घोषणा SET_APRIV(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR1, APRIV, v)
#घोषणा SET_APROTNS(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR1, APROTNS, v)
#घोषणा SET_AINST(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR1, AINST, v)
#घोषणा SET_AWRITE(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR1, AWRITE, v)
#घोषणा SET_ABURST(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR1, ABURST, v)
#घोषणा SET_ALEN(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR1, ALEN, v)
#घोषणा SET_FSYNR1_ASIZE(b, c, v) \
				SET_CONTEXT_FIELD(b, c, FSYNR1, FSYNR1_ASIZE, v)
#घोषणा SET_ALOCK(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR1, ALOCK, v)
#घोषणा SET_AFULL(b, c, v)	 SET_CONTEXT_FIELD(b, c, FSYNR1, AFULL, v)


/* NMRR */
#घोषणा SET_ICPC0(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, ICPC0, v)
#घोषणा SET_ICPC1(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, ICPC1, v)
#घोषणा SET_ICPC2(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, ICPC2, v)
#घोषणा SET_ICPC3(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, ICPC3, v)
#घोषणा SET_ICPC4(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, ICPC4, v)
#घोषणा SET_ICPC5(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, ICPC5, v)
#घोषणा SET_ICPC6(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, ICPC6, v)
#घोषणा SET_ICPC7(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, ICPC7, v)
#घोषणा SET_OCPC0(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, OCPC0, v)
#घोषणा SET_OCPC1(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, OCPC1, v)
#घोषणा SET_OCPC2(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, OCPC2, v)
#घोषणा SET_OCPC3(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, OCPC3, v)
#घोषणा SET_OCPC4(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, OCPC4, v)
#घोषणा SET_OCPC5(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, OCPC5, v)
#घोषणा SET_OCPC6(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, OCPC6, v)
#घोषणा SET_OCPC7(b, c, v)	 SET_CONTEXT_FIELD(b, c, NMRR, OCPC7, v)


/* PAR */
#घोषणा SET_FAULT(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, FAULT, v)

#घोषणा SET_FAULT_TF(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, FAULT_TF, v)
#घोषणा SET_FAULT_AFF(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, FAULT_AFF, v)
#घोषणा SET_FAULT_APF(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, FAULT_APF, v)
#घोषणा SET_FAULT_TLBMF(b, c, v) SET_CONTEXT_FIELD(b, c, PAR, FAULT_TLBMF, v)
#घोषणा SET_FAULT_HTWDEEF(b, c, v) \
				SET_CONTEXT_FIELD(b, c, PAR, FAULT_HTWDEEF, v)
#घोषणा SET_FAULT_HTWSEEF(b, c, v) \
				SET_CONTEXT_FIELD(b, c, PAR, FAULT_HTWSEEF, v)
#घोषणा SET_FAULT_MHF(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, FAULT_MHF, v)
#घोषणा SET_FAULT_SL(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, FAULT_SL, v)
#घोषणा SET_FAULT_SS(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, FAULT_SS, v)

#घोषणा SET_NOFAULT_SS(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, NOFAULT_SS, v)
#घोषणा SET_NOFAULT_MT(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, NOFAULT_MT, v)
#घोषणा SET_NOFAULT_SH(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, NOFAULT_SH, v)
#घोषणा SET_NOFAULT_NS(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, NOFAULT_NS, v)
#घोषणा SET_NOFAULT_NOS(b, c, v) SET_CONTEXT_FIELD(b, c, PAR, NOFAULT_NOS, v)
#घोषणा SET_NPFAULT_PA(b, c, v)	 SET_CONTEXT_FIELD(b, c, PAR, NPFAULT_PA, v)


/* PRRR */
#घोषणा SET_MTC0(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, MTC0, v)
#घोषणा SET_MTC1(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, MTC1, v)
#घोषणा SET_MTC2(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, MTC2, v)
#घोषणा SET_MTC3(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, MTC3, v)
#घोषणा SET_MTC4(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, MTC4, v)
#घोषणा SET_MTC5(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, MTC5, v)
#घोषणा SET_MTC6(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, MTC6, v)
#घोषणा SET_MTC7(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, MTC7, v)
#घोषणा SET_SHDSH0(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, SHDSH0, v)
#घोषणा SET_SHDSH1(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, SHDSH1, v)
#घोषणा SET_SHNMSH0(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, SHNMSH0, v)
#घोषणा SET_SHNMSH1(b, c, v)     SET_CONTEXT_FIELD(b, c, PRRR, SHNMSH1, v)
#घोषणा SET_NOS0(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, NOS0, v)
#घोषणा SET_NOS1(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, NOS1, v)
#घोषणा SET_NOS2(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, NOS2, v)
#घोषणा SET_NOS3(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, NOS3, v)
#घोषणा SET_NOS4(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, NOS4, v)
#घोषणा SET_NOS5(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, NOS5, v)
#घोषणा SET_NOS6(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, NOS6, v)
#घोषणा SET_NOS7(b, c, v)	 SET_CONTEXT_FIELD(b, c, PRRR, NOS7, v)


/* RESUME */
#घोषणा SET_TNR(b, c, v)	 SET_CONTEXT_FIELD(b, c, RESUME, TNR, v)


/* SCTLR */
#घोषणा SET_M(b, c, v)		 SET_CONTEXT_FIELD(b, c, SCTLR, M, v)
#घोषणा SET_TRE(b, c, v)	 SET_CONTEXT_FIELD(b, c, SCTLR, TRE, v)
#घोषणा SET_AFE(b, c, v)	 SET_CONTEXT_FIELD(b, c, SCTLR, AFE, v)
#घोषणा SET_HAF(b, c, v)	 SET_CONTEXT_FIELD(b, c, SCTLR, HAF, v)
#घोषणा SET_BE(b, c, v)		 SET_CONTEXT_FIELD(b, c, SCTLR, BE, v)
#घोषणा SET_AFFD(b, c, v)	 SET_CONTEXT_FIELD(b, c, SCTLR, AFFD, v)


/* TLBLKCR */
#घोषणा SET_LKE(b, c, v)	   SET_CONTEXT_FIELD(b, c, TLBLKCR, LKE, v)
#घोषणा SET_TLBLKCR_TLBIALLCFG(b, c, v) \
			SET_CONTEXT_FIELD(b, c, TLBLKCR, TLBLCKR_TLBIALLCFG, v)
#घोषणा SET_TLBIASIDCFG(b, c, v) \
			SET_CONTEXT_FIELD(b, c, TLBLKCR, TLBIASIDCFG, v)
#घोषणा SET_TLBIVAACFG(b, c, v)	SET_CONTEXT_FIELD(b, c, TLBLKCR, TLBIVAACFG, v)
#घोषणा SET_FLOOR(b, c, v)	SET_CONTEXT_FIELD(b, c, TLBLKCR, FLOOR, v)
#घोषणा SET_VICTIM(b, c, v)	SET_CONTEXT_FIELD(b, c, TLBLKCR, VICTIM, v)


/* TTBCR */
#घोषणा SET_N(b, c, v)	         SET_CONTEXT_FIELD(b, c, TTBCR, N, v)
#घोषणा SET_PD0(b, c, v)	 SET_CONTEXT_FIELD(b, c, TTBCR, PD0, v)
#घोषणा SET_PD1(b, c, v)	 SET_CONTEXT_FIELD(b, c, TTBCR, PD1, v)


/* TTBR0 */
#घोषणा SET_TTBR0_IRGNH(b, c, v) SET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_IRGNH, v)
#घोषणा SET_TTBR0_SH(b, c, v)	 SET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_SH, v)
#घोषणा SET_TTBR0_ORGN(b, c, v)	 SET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_ORGN, v)
#घोषणा SET_TTBR0_NOS(b, c, v)	 SET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_NOS, v)
#घोषणा SET_TTBR0_IRGNL(b, c, v) SET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_IRGNL, v)
#घोषणा SET_TTBR0_PA(b, c, v)	 SET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_PA, v)


/* TTBR1 */
#घोषणा SET_TTBR1_IRGNH(b, c, v) SET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_IRGNH, v)
#घोषणा SET_TTBR1_SH(b, c, v)	 SET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_SH, v)
#घोषणा SET_TTBR1_ORGN(b, c, v)	 SET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_ORGN, v)
#घोषणा SET_TTBR1_NOS(b, c, v)	 SET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_NOS, v)
#घोषणा SET_TTBR1_IRGNL(b, c, v) SET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_IRGNL, v)
#घोषणा SET_TTBR1_PA(b, c, v)	 SET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_PA, v)


/* V2PSR */
#घोषणा SET_HIT(b, c, v)	 SET_CONTEXT_FIELD(b, c, V2PSR, HIT, v)
#घोषणा SET_INDEX(b, c, v)	 SET_CONTEXT_FIELD(b, c, V2PSR, INDEX, v)


/* Context Register getters */
/* ACTLR */
#घोषणा GET_CFERE(b, c)	        GET_CONTEXT_FIELD(b, c, ACTLR, CFERE)
#घोषणा GET_CFEIE(b, c)	        GET_CONTEXT_FIELD(b, c, ACTLR, CFEIE)
#घोषणा GET_PTSHCFG(b, c)       GET_CONTEXT_FIELD(b, c, ACTLR, PTSHCFG)
#घोषणा GET_RCOSH(b, c)	        GET_CONTEXT_FIELD(b, c, ACTLR, RCOSH)
#घोषणा GET_RCISH(b, c)	        GET_CONTEXT_FIELD(b, c, ACTLR, RCISH)
#घोषणा GET_RCNSH(b, c)	        GET_CONTEXT_FIELD(b, c, ACTLR, RCNSH)
#घोषणा GET_PRIVCFG(b, c)       GET_CONTEXT_FIELD(b, c, ACTLR, PRIVCFG)
#घोषणा GET_DNA(b, c)	        GET_CONTEXT_FIELD(b, c, ACTLR, DNA)
#घोषणा GET_DNLV2PA(b, c)       GET_CONTEXT_FIELD(b, c, ACTLR, DNLV2PA)
#घोषणा GET_TLBMCFG(b, c)       GET_CONTEXT_FIELD(b, c, ACTLR, TLBMCFG)
#घोषणा GET_CFCFG(b, c)	        GET_CONTEXT_FIELD(b, c, ACTLR, CFCFG)
#घोषणा GET_TIPCF(b, c)	        GET_CONTEXT_FIELD(b, c, ACTLR, TIPCF)
#घोषणा GET_V2PCFG(b, c)        GET_CONTEXT_FIELD(b, c, ACTLR, V2PCFG)
#घोषणा GET_HUME(b, c)	        GET_CONTEXT_FIELD(b, c, ACTLR, HUME)
#घोषणा GET_PTMTCFG(b, c)       GET_CONTEXT_FIELD(b, c, ACTLR, PTMTCFG)
#घोषणा GET_PTMEMTYPE(b, c)     GET_CONTEXT_FIELD(b, c, ACTLR, PTMEMTYPE)

/* BFBCR */
#घोषणा GET_BFBDFE(b, c)	GET_CONTEXT_FIELD(b, c, BFBCR, BFBDFE)
#घोषणा GET_BFBSFE(b, c)	GET_CONTEXT_FIELD(b, c, BFBCR, BFBSFE)
#घोषणा GET_SFVS(b, c)		GET_CONTEXT_FIELD(b, c, BFBCR, SFVS)
#घोषणा GET_FLVIC(b, c)		GET_CONTEXT_FIELD(b, c, BFBCR, FLVIC)
#घोषणा GET_SLVIC(b, c)		GET_CONTEXT_FIELD(b, c, BFBCR, SLVIC)


/* CONTEXTIDR */
#घोषणा GET_CONTEXTIDR_ASID(b, c) \
			GET_CONTEXT_FIELD(b, c, CONTEXTIDR, CONTEXTIDR_ASID)
#घोषणा GET_CONTEXTIDR_PROCID(b, c) GET_CONTEXT_FIELD(b, c, CONTEXTIDR, PROCID)


/* FSR */
#घोषणा GET_TF(b, c)		GET_CONTEXT_FIELD(b, c, FSR, TF)
#घोषणा GET_AFF(b, c)		GET_CONTEXT_FIELD(b, c, FSR, AFF)
#घोषणा GET_APF(b, c)		GET_CONTEXT_FIELD(b, c, FSR, APF)
#घोषणा GET_TLBMF(b, c)		GET_CONTEXT_FIELD(b, c, FSR, TLBMF)
#घोषणा GET_HTWDEEF(b, c)	GET_CONTEXT_FIELD(b, c, FSR, HTWDEEF)
#घोषणा GET_HTWSEEF(b, c)	GET_CONTEXT_FIELD(b, c, FSR, HTWSEEF)
#घोषणा GET_MHF(b, c)		GET_CONTEXT_FIELD(b, c, FSR, MHF)
#घोषणा GET_SL(b, c)		GET_CONTEXT_FIELD(b, c, FSR, SL)
#घोषणा GET_SS(b, c)		GET_CONTEXT_FIELD(b, c, FSR, SS)
#घोषणा GET_MULTI(b, c)		GET_CONTEXT_FIELD(b, c, FSR, MULTI)


/* FSYNR0 */
#घोषणा GET_AMID(b, c)		GET_CONTEXT_FIELD(b, c, FSYNR0, AMID)
#घोषणा GET_APID(b, c)		GET_CONTEXT_FIELD(b, c, FSYNR0, APID)
#घोषणा GET_ABID(b, c)		GET_CONTEXT_FIELD(b, c, FSYNR0, ABID)
#घोषणा GET_ATID(b, c)		GET_CONTEXT_FIELD(b, c, FSYNR0, ATID)


/* FSYNR1 */
#घोषणा GET_AMEMTYPE(b, c)	GET_CONTEXT_FIELD(b, c, FSYNR1, AMEMTYPE)
#घोषणा GET_ASHARED(b, c)	GET_CONTEXT_FIELD(b, c, FSYNR1, ASHARED)
#घोषणा GET_AINNERSHARED(b, c)  GET_CONTEXT_FIELD(b, c, FSYNR1, AINNERSHARED)
#घोषणा GET_APRIV(b, c)		GET_CONTEXT_FIELD(b, c, FSYNR1, APRIV)
#घोषणा GET_APROTNS(b, c)	GET_CONTEXT_FIELD(b, c, FSYNR1, APROTNS)
#घोषणा GET_AINST(b, c)		GET_CONTEXT_FIELD(b, c, FSYNR1, AINST)
#घोषणा GET_AWRITE(b, c)	GET_CONTEXT_FIELD(b, c, FSYNR1, AWRITE)
#घोषणा GET_ABURST(b, c)	GET_CONTEXT_FIELD(b, c, FSYNR1, ABURST)
#घोषणा GET_ALEN(b, c)		GET_CONTEXT_FIELD(b, c, FSYNR1, ALEN)
#घोषणा GET_FSYNR1_ASIZE(b, c)	GET_CONTEXT_FIELD(b, c, FSYNR1, FSYNR1_ASIZE)
#घोषणा GET_ALOCK(b, c)		GET_CONTEXT_FIELD(b, c, FSYNR1, ALOCK)
#घोषणा GET_AFULL(b, c)		GET_CONTEXT_FIELD(b, c, FSYNR1, AFULL)


/* NMRR */
#घोषणा GET_ICPC0(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, ICPC0)
#घोषणा GET_ICPC1(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, ICPC1)
#घोषणा GET_ICPC2(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, ICPC2)
#घोषणा GET_ICPC3(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, ICPC3)
#घोषणा GET_ICPC4(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, ICPC4)
#घोषणा GET_ICPC5(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, ICPC5)
#घोषणा GET_ICPC6(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, ICPC6)
#घोषणा GET_ICPC7(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, ICPC7)
#घोषणा GET_OCPC0(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, OCPC0)
#घोषणा GET_OCPC1(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, OCPC1)
#घोषणा GET_OCPC2(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, OCPC2)
#घोषणा GET_OCPC3(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, OCPC3)
#घोषणा GET_OCPC4(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, OCPC4)
#घोषणा GET_OCPC5(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, OCPC5)
#घोषणा GET_OCPC6(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, OCPC6)
#घोषणा GET_OCPC7(b, c)		GET_CONTEXT_FIELD(b, c, NMRR, OCPC7)
#घोषणा NMRR_ICP(nmrr, n)	(((nmrr) & (3 << ((n) * 2))) >> ((n) * 2))
#घोषणा NMRR_OCP(nmrr, n)	(((nmrr) & (3 << ((n) * 2 + 16))) >> \
								((n) * 2 + 16))

/* PAR */
#घोषणा GET_FAULT(b, c)		GET_CONTEXT_FIELD(b, c, PAR, FAULT)

#घोषणा GET_FAULT_TF(b, c)	GET_CONTEXT_FIELD(b, c, PAR, FAULT_TF)
#घोषणा GET_FAULT_AFF(b, c)	GET_CONTEXT_FIELD(b, c, PAR, FAULT_AFF)
#घोषणा GET_FAULT_APF(b, c)	GET_CONTEXT_FIELD(b, c, PAR, FAULT_APF)
#घोषणा GET_FAULT_TLBMF(b, c)   GET_CONTEXT_FIELD(b, c, PAR, FAULT_TLBMF)
#घोषणा GET_FAULT_HTWDEEF(b, c) GET_CONTEXT_FIELD(b, c, PAR, FAULT_HTWDEEF)
#घोषणा GET_FAULT_HTWSEEF(b, c) GET_CONTEXT_FIELD(b, c, PAR, FAULT_HTWSEEF)
#घोषणा GET_FAULT_MHF(b, c)	GET_CONTEXT_FIELD(b, c, PAR, FAULT_MHF)
#घोषणा GET_FAULT_SL(b, c)	GET_CONTEXT_FIELD(b, c, PAR, FAULT_SL)
#घोषणा GET_FAULT_SS(b, c)	GET_CONTEXT_FIELD(b, c, PAR, FAULT_SS)

#घोषणा GET_NOFAULT_SS(b, c)	GET_CONTEXT_FIELD(b, c, PAR, PAR_NOFAULT_SS)
#घोषणा GET_NOFAULT_MT(b, c)	GET_CONTEXT_FIELD(b, c, PAR, PAR_NOFAULT_MT)
#घोषणा GET_NOFAULT_SH(b, c)	GET_CONTEXT_FIELD(b, c, PAR, PAR_NOFAULT_SH)
#घोषणा GET_NOFAULT_NS(b, c)	GET_CONTEXT_FIELD(b, c, PAR, PAR_NOFAULT_NS)
#घोषणा GET_NOFAULT_NOS(b, c)   GET_CONTEXT_FIELD(b, c, PAR, PAR_NOFAULT_NOS)
#घोषणा GET_NPFAULT_PA(b, c)	GET_CONTEXT_FIELD(b, c, PAR, PAR_NPFAULT_PA)


/* PRRR */
#घोषणा GET_MTC0(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, MTC0)
#घोषणा GET_MTC1(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, MTC1)
#घोषणा GET_MTC2(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, MTC2)
#घोषणा GET_MTC3(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, MTC3)
#घोषणा GET_MTC4(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, MTC4)
#घोषणा GET_MTC5(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, MTC5)
#घोषणा GET_MTC6(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, MTC6)
#घोषणा GET_MTC7(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, MTC7)
#घोषणा GET_SHDSH0(b, c)	GET_CONTEXT_FIELD(b, c, PRRR, SHDSH0)
#घोषणा GET_SHDSH1(b, c)	GET_CONTEXT_FIELD(b, c, PRRR, SHDSH1)
#घोषणा GET_SHNMSH0(b, c)	GET_CONTEXT_FIELD(b, c, PRRR, SHNMSH0)
#घोषणा GET_SHNMSH1(b, c)	GET_CONTEXT_FIELD(b, c, PRRR, SHNMSH1)
#घोषणा GET_NOS0(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, NOS0)
#घोषणा GET_NOS1(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, NOS1)
#घोषणा GET_NOS2(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, NOS2)
#घोषणा GET_NOS3(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, NOS3)
#घोषणा GET_NOS4(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, NOS4)
#घोषणा GET_NOS5(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, NOS5)
#घोषणा GET_NOS6(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, NOS6)
#घोषणा GET_NOS7(b, c)		GET_CONTEXT_FIELD(b, c, PRRR, NOS7)
#घोषणा PRRR_NOS(prrr, n)	 ((prrr) & (1 << ((n) + 24)) ? 1 : 0)
#घोषणा PRRR_MT(prrr, n)	 ((((prrr) & (3 << ((n) * 2))) >> ((n) * 2)))


/* RESUME */
#घोषणा GET_TNR(b, c)		GET_CONTEXT_FIELD(b, c, RESUME, TNR)


/* SCTLR */
#घोषणा GET_M(b, c)		GET_CONTEXT_FIELD(b, c, SCTLR, M)
#घोषणा GET_TRE(b, c)		GET_CONTEXT_FIELD(b, c, SCTLR, TRE)
#घोषणा GET_AFE(b, c)		GET_CONTEXT_FIELD(b, c, SCTLR, AFE)
#घोषणा GET_HAF(b, c)		GET_CONTEXT_FIELD(b, c, SCTLR, HAF)
#घोषणा GET_BE(b, c)		GET_CONTEXT_FIELD(b, c, SCTLR, BE)
#घोषणा GET_AFFD(b, c)		GET_CONTEXT_FIELD(b, c, SCTLR, AFFD)


/* TLBLKCR */
#घोषणा GET_LKE(b, c)		GET_CONTEXT_FIELD(b, c, TLBLKCR, LKE)
#घोषणा GET_TLBLCKR_TLBIALLCFG(b, c) \
			GET_CONTEXT_FIELD(b, c, TLBLKCR, TLBLCKR_TLBIALLCFG)
#घोषणा GET_TLBIASIDCFG(b, c)   GET_CONTEXT_FIELD(b, c, TLBLKCR, TLBIASIDCFG)
#घोषणा GET_TLBIVAACFG(b, c)	GET_CONTEXT_FIELD(b, c, TLBLKCR, TLBIVAACFG)
#घोषणा GET_FLOOR(b, c)		GET_CONTEXT_FIELD(b, c, TLBLKCR, FLOOR)
#घोषणा GET_VICTIM(b, c)	GET_CONTEXT_FIELD(b, c, TLBLKCR, VICTIM)


/* TTBCR */
#घोषणा GET_N(b, c)		GET_CONTEXT_FIELD(b, c, TTBCR, N)
#घोषणा GET_PD0(b, c)		GET_CONTEXT_FIELD(b, c, TTBCR, PD0)
#घोषणा GET_PD1(b, c)		GET_CONTEXT_FIELD(b, c, TTBCR, PD1)


/* TTBR0 */
#घोषणा GET_TTBR0_IRGNH(b, c)	GET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_IRGNH)
#घोषणा GET_TTBR0_SH(b, c)	GET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_SH)
#घोषणा GET_TTBR0_ORGN(b, c)	GET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_ORGN)
#घोषणा GET_TTBR0_NOS(b, c)	GET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_NOS)
#घोषणा GET_TTBR0_IRGNL(b, c)	GET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_IRGNL)
#घोषणा GET_TTBR0_PA(b, c)	GET_CONTEXT_FIELD(b, c, TTBR0, TTBR0_PA)


/* TTBR1 */
#घोषणा GET_TTBR1_IRGNH(b, c)	GET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_IRGNH)
#घोषणा GET_TTBR1_SH(b, c)	GET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_SH)
#घोषणा GET_TTBR1_ORGN(b, c)	GET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_ORGN)
#घोषणा GET_TTBR1_NOS(b, c)	GET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_NOS)
#घोषणा GET_TTBR1_IRGNL(b, c)	GET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_IRGNL)
#घोषणा GET_TTBR1_PA(b, c)	GET_CONTEXT_FIELD(b, c, TTBR1, TTBR1_PA)


/* V2PSR */
#घोषणा GET_HIT(b, c)		GET_CONTEXT_FIELD(b, c, V2PSR, HIT)
#घोषणा GET_INDEX(b, c)		GET_CONTEXT_FIELD(b, c, V2PSR, INDEX)


/* Global Registers */
#घोषणा M2VCBR_N	(0xFF000)
#घोषणा CBACR_N		(0xFF800)
#घोषणा TLBRSW		(0xFFE00)
#घोषणा TLBTR0		(0xFFE80)
#घोषणा TLBTR1		(0xFFE84)
#घोषणा TLBTR2		(0xFFE88)
#घोषणा TESTBUSCR	(0xFFE8C)
#घोषणा GLOBAL_TLBIALL	(0xFFF00)
#घोषणा TLBIVMID	(0xFFF04)
#घोषणा CR		(0xFFF80)
#घोषणा EAR		(0xFFF84)
#घोषणा ESR		(0xFFF88)
#घोषणा ESRRESTORE	(0xFFF8C)
#घोषणा ESYNR0		(0xFFF90)
#घोषणा ESYNR1		(0xFFF94)
#घोषणा REV		(0xFFFF4)
#घोषणा IDR		(0xFFFF8)
#घोषणा RPU_ACR		(0xFFFFC)


/* Context Bank Registers */
#घोषणा SCTLR		(0x000)
#घोषणा ACTLR		(0x004)
#घोषणा CONTEXTIDR	(0x008)
#घोषणा TTBR0		(0x010)
#घोषणा TTBR1		(0x014)
#घोषणा TTBCR		(0x018)
#घोषणा PAR		(0x01C)
#घोषणा FSR		(0x020)
#घोषणा FSRRESTORE	(0x024)
#घोषणा FAR		(0x028)
#घोषणा FSYNR0		(0x02C)
#घोषणा FSYNR1		(0x030)
#घोषणा PRRR		(0x034)
#घोषणा NMRR		(0x038)
#घोषणा TLBLCKR		(0x03C)
#घोषणा V2PSR		(0x040)
#घोषणा TLBFLPTER	(0x044)
#घोषणा TLBSLPTER	(0x048)
#घोषणा BFBCR		(0x04C)
#घोषणा CTX_TLBIALL	(0x800)
#घोषणा TLBIASID	(0x804)
#घोषणा TLBIVA		(0x808)
#घोषणा TLBIVAA		(0x80C)
#घोषणा V2PPR		(0x810)
#घोषणा V2PPW		(0x814)
#घोषणा V2PUR		(0x818)
#घोषणा V2PUW		(0x81C)
#घोषणा RESUME		(0x820)


/* Global Register Fields */
/* CBACRn */
#घोषणा RWVMID        (RWVMID_MASK       << RWVMID_SHIFT)
#घोषणा RWE           (RWE_MASK          << RWE_SHIFT)
#घोषणा RWGE          (RWGE_MASK         << RWGE_SHIFT)
#घोषणा CBVMID        (CBVMID_MASK       << CBVMID_SHIFT)
#घोषणा IRPTNDX       (IRPTNDX_MASK      << IRPTNDX_SHIFT)


/* CR */
#घोषणा RPUE          (RPUE_MASK          << RPUE_SHIFT)
#घोषणा RPUERE        (RPUERE_MASK        << RPUERE_SHIFT)
#घोषणा RPUEIE        (RPUEIE_MASK        << RPUEIE_SHIFT)
#घोषणा DCDEE         (DCDEE_MASK         << DCDEE_SHIFT)
#घोषणा CLIENTPD      (CLIENTPD_MASK      << CLIENTPD_SHIFT)
#घोषणा STALLD        (STALLD_MASK        << STALLD_SHIFT)
#घोषणा TLBLKCRWE     (TLBLKCRWE_MASK     << TLBLKCRWE_SHIFT)
#घोषणा CR_TLBIALLCFG (CR_TLBIALLCFG_MASK << CR_TLBIALLCFG_SHIFT)
#घोषणा TLBIVMIDCFG   (TLBIVMIDCFG_MASK   << TLBIVMIDCFG_SHIFT)
#घोषणा CR_HUME       (CR_HUME_MASK       << CR_HUME_SHIFT)


/* ESR */
#घोषणा CFG           (CFG_MASK          << CFG_SHIFT)
#घोषणा BYPASS        (BYPASS_MASK       << BYPASS_SHIFT)
#घोषणा ESR_MULTI     (ESR_MULTI_MASK    << ESR_MULTI_SHIFT)


/* ESYNR0 */
#घोषणा ESYNR0_AMID   (ESYNR0_AMID_MASK  << ESYNR0_AMID_SHIFT)
#घोषणा ESYNR0_APID   (ESYNR0_APID_MASK  << ESYNR0_APID_SHIFT)
#घोषणा ESYNR0_ABID   (ESYNR0_ABID_MASK  << ESYNR0_ABID_SHIFT)
#घोषणा ESYNR0_AVMID  (ESYNR0_AVMID_MASK << ESYNR0_AVMID_SHIFT)
#घोषणा ESYNR0_ATID   (ESYNR0_ATID_MASK  << ESYNR0_ATID_SHIFT)


/* ESYNR1 */
#घोषणा ESYNR1_AMEMTYPE      (ESYNR1_AMEMTYPE_MASK    << ESYNR1_AMEMTYPE_SHIFT)
#घोषणा ESYNR1_ASHARED       (ESYNR1_ASHARED_MASK     << ESYNR1_ASHARED_SHIFT)
#घोषणा ESYNR1_AINNERSHARED  (ESYNR1_AINNERSHARED_MASK<< \
						ESYNR1_AINNERSHARED_SHIFT)
#घोषणा ESYNR1_APRIV         (ESYNR1_APRIV_MASK       << ESYNR1_APRIV_SHIFT)
#घोषणा ESYNR1_APROTNS       (ESYNR1_APROTNS_MASK     << ESYNR1_APROTNS_SHIFT)
#घोषणा ESYNR1_AINST         (ESYNR1_AINST_MASK       << ESYNR1_AINST_SHIFT)
#घोषणा ESYNR1_AWRITE        (ESYNR1_AWRITE_MASK      << ESYNR1_AWRITE_SHIFT)
#घोषणा ESYNR1_ABURST        (ESYNR1_ABURST_MASK      << ESYNR1_ABURST_SHIFT)
#घोषणा ESYNR1_ALEN          (ESYNR1_ALEN_MASK        << ESYNR1_ALEN_SHIFT)
#घोषणा ESYNR1_ASIZE         (ESYNR1_ASIZE_MASK       << ESYNR1_ASIZE_SHIFT)
#घोषणा ESYNR1_ALOCK         (ESYNR1_ALOCK_MASK       << ESYNR1_ALOCK_SHIFT)
#घोषणा ESYNR1_AOOO          (ESYNR1_AOOO_MASK        << ESYNR1_AOOO_SHIFT)
#घोषणा ESYNR1_AFULL         (ESYNR1_AFULL_MASK       << ESYNR1_AFULL_SHIFT)
#घोषणा ESYNR1_AC            (ESYNR1_AC_MASK          << ESYNR1_AC_SHIFT)
#घोषणा ESYNR1_DCD           (ESYNR1_DCD_MASK         << ESYNR1_DCD_SHIFT)


/* IDR */
#घोषणा NM2VCBMT      (NM2VCBMT_MASK     << NM2VCBMT_SHIFT)
#घोषणा HTW           (HTW_MASK          << HTW_SHIFT)
#घोषणा HUM           (HUM_MASK          << HUM_SHIFT)
#घोषणा TLBSIZE       (TLBSIZE_MASK      << TLBSIZE_SHIFT)
#घोषणा NCB           (NCB_MASK          << NCB_SHIFT)
#घोषणा NIRPT         (NIRPT_MASK        << NIRPT_SHIFT)


/* M2VCBRn */
#घोषणा VMID          (VMID_MASK         << VMID_SHIFT)
#घोषणा CBNDX         (CBNDX_MASK        << CBNDX_SHIFT)
#घोषणा BYPASSD       (BYPASSD_MASK      << BYPASSD_SHIFT)
#घोषणा BPRCOSH       (BPRCOSH_MASK      << BPRCOSH_SHIFT)
#घोषणा BPRCISH       (BPRCISH_MASK      << BPRCISH_SHIFT)
#घोषणा BPRCNSH       (BPRCNSH_MASK      << BPRCNSH_SHIFT)
#घोषणा BPSHCFG       (BPSHCFG_MASK      << BPSHCFG_SHIFT)
#घोषणा NSCFG         (NSCFG_MASK        << NSCFG_SHIFT)
#घोषणा BPMTCFG       (BPMTCFG_MASK      << BPMTCFG_SHIFT)
#घोषणा BPMEMTYPE     (BPMEMTYPE_MASK    << BPMEMTYPE_SHIFT)


/* REV */
#घोषणा IDR_MINOR     (MINOR_MASK        << MINOR_SHIFT)
#घोषणा IDR_MAJOR     (MAJOR_MASK        << MAJOR_SHIFT)


/* TESTBUSCR */
#घोषणा TBE           (TBE_MASK          << TBE_SHIFT)
#घोषणा SPDMBE        (SPDMBE_MASK       << SPDMBE_SHIFT)
#घोषणा WGSEL         (WGSEL_MASK        << WGSEL_SHIFT)
#घोषणा TBLSEL        (TBLSEL_MASK       << TBLSEL_SHIFT)
#घोषणा TBHSEL        (TBHSEL_MASK       << TBHSEL_SHIFT)
#घोषणा SPDM0SEL      (SPDM0SEL_MASK     << SPDM0SEL_SHIFT)
#घोषणा SPDM1SEL      (SPDM1SEL_MASK     << SPDM1SEL_SHIFT)
#घोषणा SPDM2SEL      (SPDM2SEL_MASK     << SPDM2SEL_SHIFT)
#घोषणा SPDM3SEL      (SPDM3SEL_MASK     << SPDM3SEL_SHIFT)


/* TLBIVMID */
#घोषणा TLBIVMID_VMID (TLBIVMID_VMID_MASK << TLBIVMID_VMID_SHIFT)


/* TLBRSW */
#घोषणा TLBRSW_INDEX  (TLBRSW_INDEX_MASK << TLBRSW_INDEX_SHIFT)
#घोषणा TLBBFBS       (TLBBFBS_MASK      << TLBBFBS_SHIFT)


/* TLBTR0 */
#घोषणा PR            (PR_MASK           << PR_SHIFT)
#घोषणा PW            (PW_MASK           << PW_SHIFT)
#घोषणा UR            (UR_MASK           << UR_SHIFT)
#घोषणा UW            (UW_MASK           << UW_SHIFT)
#घोषणा XN            (XN_MASK           << XN_SHIFT)
#घोषणा NSDESC        (NSDESC_MASK       << NSDESC_SHIFT)
#घोषणा ISH           (ISH_MASK          << ISH_SHIFT)
#घोषणा SH            (SH_MASK           << SH_SHIFT)
#घोषणा MT            (MT_MASK           << MT_SHIFT)
#घोषणा DPSIZR        (DPSIZR_MASK       << DPSIZR_SHIFT)
#घोषणा DPSIZC        (DPSIZC_MASK       << DPSIZC_SHIFT)


/* TLBTR1 */
#घोषणा TLBTR1_VMID   (TLBTR1_VMID_MASK  << TLBTR1_VMID_SHIFT)
#घोषणा TLBTR1_PA     (TLBTR1_PA_MASK    << TLBTR1_PA_SHIFT)


/* TLBTR2 */
#घोषणा TLBTR2_ASID   (TLBTR2_ASID_MASK  << TLBTR2_ASID_SHIFT)
#घोषणा TLBTR2_V      (TLBTR2_V_MASK     << TLBTR2_V_SHIFT)
#घोषणा TLBTR2_NSTID  (TLBTR2_NSTID_MASK << TLBTR2_NSTID_SHIFT)
#घोषणा TLBTR2_NV     (TLBTR2_NV_MASK    << TLBTR2_NV_SHIFT)
#घोषणा TLBTR2_VA     (TLBTR2_VA_MASK    << TLBTR2_VA_SHIFT)


/* Context Register Fields */
/* ACTLR */
#घोषणा CFERE              (CFERE_MASK              << CFERE_SHIFT)
#घोषणा CFEIE              (CFEIE_MASK              << CFEIE_SHIFT)
#घोषणा PTSHCFG            (PTSHCFG_MASK            << PTSHCFG_SHIFT)
#घोषणा RCOSH              (RCOSH_MASK              << RCOSH_SHIFT)
#घोषणा RCISH              (RCISH_MASK              << RCISH_SHIFT)
#घोषणा RCNSH              (RCNSH_MASK              << RCNSH_SHIFT)
#घोषणा PRIVCFG            (PRIVCFG_MASK            << PRIVCFG_SHIFT)
#घोषणा DNA                (DNA_MASK                << DNA_SHIFT)
#घोषणा DNLV2PA            (DNLV2PA_MASK            << DNLV2PA_SHIFT)
#घोषणा TLBMCFG            (TLBMCFG_MASK            << TLBMCFG_SHIFT)
#घोषणा CFCFG              (CFCFG_MASK              << CFCFG_SHIFT)
#घोषणा TIPCF              (TIPCF_MASK              << TIPCF_SHIFT)
#घोषणा V2PCFG             (V2PCFG_MASK             << V2PCFG_SHIFT)
#घोषणा HUME               (HUME_MASK               << HUME_SHIFT)
#घोषणा PTMTCFG            (PTMTCFG_MASK            << PTMTCFG_SHIFT)
#घोषणा PTMEMTYPE          (PTMEMTYPE_MASK          << PTMEMTYPE_SHIFT)


/* BFBCR */
#घोषणा BFBDFE             (BFBDFE_MASK             << BFBDFE_SHIFT)
#घोषणा BFBSFE             (BFBSFE_MASK             << BFBSFE_SHIFT)
#घोषणा SFVS               (SFVS_MASK               << SFVS_SHIFT)
#घोषणा FLVIC              (FLVIC_MASK              << FLVIC_SHIFT)
#घोषणा SLVIC              (SLVIC_MASK              << SLVIC_SHIFT)


/* CONTEXTIDR */
#घोषणा CONTEXTIDR_ASID    (CONTEXTIDR_ASID_MASK    << CONTEXTIDR_ASID_SHIFT)
#घोषणा PROCID             (PROCID_MASK             << PROCID_SHIFT)


/* FSR */
#घोषणा TF                 (TF_MASK                 << TF_SHIFT)
#घोषणा AFF                (AFF_MASK                << AFF_SHIFT)
#घोषणा APF                (APF_MASK                << APF_SHIFT)
#घोषणा TLBMF              (TLBMF_MASK              << TLBMF_SHIFT)
#घोषणा HTWDEEF            (HTWDEEF_MASK            << HTWDEEF_SHIFT)
#घोषणा HTWSEEF            (HTWSEEF_MASK            << HTWSEEF_SHIFT)
#घोषणा MHF                (MHF_MASK                << MHF_SHIFT)
#घोषणा SL                 (SL_MASK                 << SL_SHIFT)
#घोषणा SS                 (SS_MASK                 << SS_SHIFT)
#घोषणा MULTI              (MULTI_MASK              << MULTI_SHIFT)


/* FSYNR0 */
#घोषणा AMID               (AMID_MASK               << AMID_SHIFT)
#घोषणा APID               (APID_MASK               << APID_SHIFT)
#घोषणा ABID               (ABID_MASK               << ABID_SHIFT)
#घोषणा ATID               (ATID_MASK               << ATID_SHIFT)


/* FSYNR1 */
#घोषणा AMEMTYPE           (AMEMTYPE_MASK           << AMEMTYPE_SHIFT)
#घोषणा ASHARED            (ASHARED_MASK            << ASHARED_SHIFT)
#घोषणा AINNERSHARED       (AINNERSHARED_MASK       << AINNERSHARED_SHIFT)
#घोषणा APRIV              (APRIV_MASK              << APRIV_SHIFT)
#घोषणा APROTNS            (APROTNS_MASK            << APROTNS_SHIFT)
#घोषणा AINST              (AINST_MASK              << AINST_SHIFT)
#घोषणा AWRITE             (AWRITE_MASK             << AWRITE_SHIFT)
#घोषणा ABURST             (ABURST_MASK             << ABURST_SHIFT)
#घोषणा ALEN               (ALEN_MASK               << ALEN_SHIFT)
#घोषणा FSYNR1_ASIZE       (FSYNR1_ASIZE_MASK       << FSYNR1_ASIZE_SHIFT)
#घोषणा ALOCK              (ALOCK_MASK              << ALOCK_SHIFT)
#घोषणा AFULL              (AFULL_MASK              << AFULL_SHIFT)


/* NMRR */
#घोषणा ICPC0              (ICPC0_MASK              << ICPC0_SHIFT)
#घोषणा ICPC1              (ICPC1_MASK              << ICPC1_SHIFT)
#घोषणा ICPC2              (ICPC2_MASK              << ICPC2_SHIFT)
#घोषणा ICPC3              (ICPC3_MASK              << ICPC3_SHIFT)
#घोषणा ICPC4              (ICPC4_MASK              << ICPC4_SHIFT)
#घोषणा ICPC5              (ICPC5_MASK              << ICPC5_SHIFT)
#घोषणा ICPC6              (ICPC6_MASK              << ICPC6_SHIFT)
#घोषणा ICPC7              (ICPC7_MASK              << ICPC7_SHIFT)
#घोषणा OCPC0              (OCPC0_MASK              << OCPC0_SHIFT)
#घोषणा OCPC1              (OCPC1_MASK              << OCPC1_SHIFT)
#घोषणा OCPC2              (OCPC2_MASK              << OCPC2_SHIFT)
#घोषणा OCPC3              (OCPC3_MASK              << OCPC3_SHIFT)
#घोषणा OCPC4              (OCPC4_MASK              << OCPC4_SHIFT)
#घोषणा OCPC5              (OCPC5_MASK              << OCPC5_SHIFT)
#घोषणा OCPC6              (OCPC6_MASK              << OCPC6_SHIFT)
#घोषणा OCPC7              (OCPC7_MASK              << OCPC7_SHIFT)


/* PAR */
#घोषणा FAULT              (FAULT_MASK              << FAULT_SHIFT)
/* If a fault is present, these are the
same as the fault fields in the FAR */
#घोषणा FAULT_TF           (FAULT_TF_MASK           << FAULT_TF_SHIFT)
#घोषणा FAULT_AFF          (FAULT_AFF_MASK          << FAULT_AFF_SHIFT)
#घोषणा FAULT_APF          (FAULT_APF_MASK          << FAULT_APF_SHIFT)
#घोषणा FAULT_TLBMF        (FAULT_TLBMF_MASK        << FAULT_TLBMF_SHIFT)
#घोषणा FAULT_HTWDEEF      (FAULT_HTWDEEF_MASK      << FAULT_HTWDEEF_SHIFT)
#घोषणा FAULT_HTWSEEF      (FAULT_HTWSEEF_MASK      << FAULT_HTWSEEF_SHIFT)
#घोषणा FAULT_MHF          (FAULT_MHF_MASK          << FAULT_MHF_SHIFT)
#घोषणा FAULT_SL           (FAULT_SL_MASK           << FAULT_SL_SHIFT)
#घोषणा FAULT_SS           (FAULT_SS_MASK           << FAULT_SS_SHIFT)

/* If NO fault is present, the following fields are in effect */
/* (FAULT reमुख्यs as beक्रमe) */
#घोषणा PAR_NOFAULT_SS     (PAR_NOFAULT_SS_MASK     << PAR_NOFAULT_SS_SHIFT)
#घोषणा PAR_NOFAULT_MT     (PAR_NOFAULT_MT_MASK     << PAR_NOFAULT_MT_SHIFT)
#घोषणा PAR_NOFAULT_SH     (PAR_NOFAULT_SH_MASK     << PAR_NOFAULT_SH_SHIFT)
#घोषणा PAR_NOFAULT_NS     (PAR_NOFAULT_NS_MASK     << PAR_NOFAULT_NS_SHIFT)
#घोषणा PAR_NOFAULT_NOS    (PAR_NOFAULT_NOS_MASK    << PAR_NOFAULT_NOS_SHIFT)
#घोषणा PAR_NPFAULT_PA     (PAR_NPFAULT_PA_MASK     << PAR_NPFAULT_PA_SHIFT)


/* PRRR */
#घोषणा MTC0               (MTC0_MASK               << MTC0_SHIFT)
#घोषणा MTC1               (MTC1_MASK               << MTC1_SHIFT)
#घोषणा MTC2               (MTC2_MASK               << MTC2_SHIFT)
#घोषणा MTC3               (MTC3_MASK               << MTC3_SHIFT)
#घोषणा MTC4               (MTC4_MASK               << MTC4_SHIFT)
#घोषणा MTC5               (MTC5_MASK               << MTC5_SHIFT)
#घोषणा MTC6               (MTC6_MASK               << MTC6_SHIFT)
#घोषणा MTC7               (MTC7_MASK               << MTC7_SHIFT)
#घोषणा SHDSH0             (SHDSH0_MASK             << SHDSH0_SHIFT)
#घोषणा SHDSH1             (SHDSH1_MASK             << SHDSH1_SHIFT)
#घोषणा SHNMSH0            (SHNMSH0_MASK            << SHNMSH0_SHIFT)
#घोषणा SHNMSH1            (SHNMSH1_MASK            << SHNMSH1_SHIFT)
#घोषणा NOS0               (NOS0_MASK               << NOS0_SHIFT)
#घोषणा NOS1               (NOS1_MASK               << NOS1_SHIFT)
#घोषणा NOS2               (NOS2_MASK               << NOS2_SHIFT)
#घोषणा NOS3               (NOS3_MASK               << NOS3_SHIFT)
#घोषणा NOS4               (NOS4_MASK               << NOS4_SHIFT)
#घोषणा NOS5               (NOS5_MASK               << NOS5_SHIFT)
#घोषणा NOS6               (NOS6_MASK               << NOS6_SHIFT)
#घोषणा NOS7               (NOS7_MASK               << NOS7_SHIFT)


/* RESUME */
#घोषणा TNR                (TNR_MASK                << TNR_SHIFT)


/* SCTLR */
#घोषणा M                  (M_MASK                  << M_SHIFT)
#घोषणा TRE                (TRE_MASK                << TRE_SHIFT)
#घोषणा AFE                (AFE_MASK                << AFE_SHIFT)
#घोषणा HAF                (HAF_MASK                << HAF_SHIFT)
#घोषणा BE                 (BE_MASK                 << BE_SHIFT)
#घोषणा AFFD               (AFFD_MASK               << AFFD_SHIFT)


/* TLBIASID */
#घोषणा TLBIASID_ASID      (TLBIASID_ASID_MASK      << TLBIASID_ASID_SHIFT)


/* TLBIVA */
#घोषणा TLBIVA_ASID        (TLBIVA_ASID_MASK        << TLBIVA_ASID_SHIFT)
#घोषणा TLBIVA_VA          (TLBIVA_VA_MASK          << TLBIVA_VA_SHIFT)


/* TLBIVAA */
#घोषणा TLBIVAA_VA         (TLBIVAA_VA_MASK         << TLBIVAA_VA_SHIFT)


/* TLBLCKR */
#घोषणा LKE                (LKE_MASK                << LKE_SHIFT)
#घोषणा TLBLCKR_TLBIALLCFG (TLBLCKR_TLBIALLCFG_MASK<<TLBLCKR_TLBIALLCFG_SHIFT)
#घोषणा TLBIASIDCFG        (TLBIASIDCFG_MASK        << TLBIASIDCFG_SHIFT)
#घोषणा TLBIVAACFG         (TLBIVAACFG_MASK         << TLBIVAACFG_SHIFT)
#घोषणा FLOOR              (FLOOR_MASK              << FLOOR_SHIFT)
#घोषणा VICTIM             (VICTIM_MASK             << VICTIM_SHIFT)


/* TTBCR */
#घोषणा N                  (N_MASK                  << N_SHIFT)
#घोषणा PD0                (PD0_MASK                << PD0_SHIFT)
#घोषणा PD1                (PD1_MASK                << PD1_SHIFT)


/* TTBR0 */
#घोषणा TTBR0_IRGNH        (TTBR0_IRGNH_MASK        << TTBR0_IRGNH_SHIFT)
#घोषणा TTBR0_SH           (TTBR0_SH_MASK           << TTBR0_SH_SHIFT)
#घोषणा TTBR0_ORGN         (TTBR0_ORGN_MASK         << TTBR0_ORGN_SHIFT)
#घोषणा TTBR0_NOS          (TTBR0_NOS_MASK          << TTBR0_NOS_SHIFT)
#घोषणा TTBR0_IRGNL        (TTBR0_IRGNL_MASK        << TTBR0_IRGNL_SHIFT)
#घोषणा TTBR0_PA           (TTBR0_PA_MASK           << TTBR0_PA_SHIFT)


/* TTBR1 */
#घोषणा TTBR1_IRGNH        (TTBR1_IRGNH_MASK        << TTBR1_IRGNH_SHIFT)
#घोषणा TTBR1_SH           (TTBR1_SH_MASK           << TTBR1_SH_SHIFT)
#घोषणा TTBR1_ORGN         (TTBR1_ORGN_MASK         << TTBR1_ORGN_SHIFT)
#घोषणा TTBR1_NOS          (TTBR1_NOS_MASK          << TTBR1_NOS_SHIFT)
#घोषणा TTBR1_IRGNL        (TTBR1_IRGNL_MASK        << TTBR1_IRGNL_SHIFT)
#घोषणा TTBR1_PA           (TTBR1_PA_MASK           << TTBR1_PA_SHIFT)


/* V2PSR */
#घोषणा HIT                (HIT_MASK                << HIT_SHIFT)
#घोषणा INDEX              (INDEX_MASK              << INDEX_SHIFT)


/* V2Pxx */
#घोषणा V2Pxx_INDEX        (V2Pxx_INDEX_MASK        << V2Pxx_INDEX_SHIFT)
#घोषणा V2Pxx_VA           (V2Pxx_VA_MASK           << V2Pxx_VA_SHIFT)


/* Global Register Masks */
/* CBACRn */
#घोषणा RWVMID_MASK               0x1F
#घोषणा RWE_MASK                  0x01
#घोषणा RWGE_MASK                 0x01
#घोषणा CBVMID_MASK               0x1F
#घोषणा IRPTNDX_MASK              0xFF


/* CR */
#घोषणा RPUE_MASK                 0x01
#घोषणा RPUERE_MASK               0x01
#घोषणा RPUEIE_MASK               0x01
#घोषणा DCDEE_MASK                0x01
#घोषणा CLIENTPD_MASK             0x01
#घोषणा STALLD_MASK               0x01
#घोषणा TLBLKCRWE_MASK            0x01
#घोषणा CR_TLBIALLCFG_MASK        0x01
#घोषणा TLBIVMIDCFG_MASK          0x01
#घोषणा CR_HUME_MASK              0x01


/* ESR */
#घोषणा CFG_MASK                  0x01
#घोषणा BYPASS_MASK               0x01
#घोषणा ESR_MULTI_MASK            0x01


/* ESYNR0 */
#घोषणा ESYNR0_AMID_MASK          0xFF
#घोषणा ESYNR0_APID_MASK          0x1F
#घोषणा ESYNR0_ABID_MASK          0x07
#घोषणा ESYNR0_AVMID_MASK         0x1F
#घोषणा ESYNR0_ATID_MASK          0xFF


/* ESYNR1 */
#घोषणा ESYNR1_AMEMTYPE_MASK             0x07
#घोषणा ESYNR1_ASHARED_MASK              0x01
#घोषणा ESYNR1_AINNERSHARED_MASK         0x01
#घोषणा ESYNR1_APRIV_MASK                0x01
#घोषणा ESYNR1_APROTNS_MASK              0x01
#घोषणा ESYNR1_AINST_MASK                0x01
#घोषणा ESYNR1_AWRITE_MASK               0x01
#घोषणा ESYNR1_ABURST_MASK               0x01
#घोषणा ESYNR1_ALEN_MASK                 0x0F
#घोषणा ESYNR1_ASIZE_MASK                0x01
#घोषणा ESYNR1_ALOCK_MASK                0x03
#घोषणा ESYNR1_AOOO_MASK                 0x01
#घोषणा ESYNR1_AFULL_MASK                0x01
#घोषणा ESYNR1_AC_MASK                   0x01
#घोषणा ESYNR1_DCD_MASK                  0x01


/* IDR */
#घोषणा NM2VCBMT_MASK             0x1FF
#घोषणा HTW_MASK                  0x01
#घोषणा HUM_MASK                  0x01
#घोषणा TLBSIZE_MASK              0x0F
#घोषणा NCB_MASK                  0xFF
#घोषणा NIRPT_MASK                0xFF


/* M2VCBRn */
#घोषणा VMID_MASK                 0x1F
#घोषणा CBNDX_MASK                0xFF
#घोषणा BYPASSD_MASK              0x01
#घोषणा BPRCOSH_MASK              0x01
#घोषणा BPRCISH_MASK              0x01
#घोषणा BPRCNSH_MASK              0x01
#घोषणा BPSHCFG_MASK              0x03
#घोषणा NSCFG_MASK                0x03
#घोषणा BPMTCFG_MASK              0x01
#घोषणा BPMEMTYPE_MASK            0x07


/* REV */
#घोषणा MINOR_MASK                0x0F
#घोषणा MAJOR_MASK                0x0F


/* TESTBUSCR */
#घोषणा TBE_MASK                  0x01
#घोषणा SPDMBE_MASK               0x01
#घोषणा WGSEL_MASK                0x03
#घोषणा TBLSEL_MASK               0x03
#घोषणा TBHSEL_MASK               0x03
#घोषणा SPDM0SEL_MASK             0x0F
#घोषणा SPDM1SEL_MASK             0x0F
#घोषणा SPDM2SEL_MASK             0x0F
#घोषणा SPDM3SEL_MASK             0x0F


/* TLBIMID */
#घोषणा TLBIVMID_VMID_MASK        0x1F


/* TLBRSW */
#घोषणा TLBRSW_INDEX_MASK         0xFF
#घोषणा TLBBFBS_MASK              0x03


/* TLBTR0 */
#घोषणा PR_MASK                   0x01
#घोषणा PW_MASK                   0x01
#घोषणा UR_MASK                   0x01
#घोषणा UW_MASK                   0x01
#घोषणा XN_MASK                   0x01
#घोषणा NSDESC_MASK               0x01
#घोषणा ISH_MASK                  0x01
#घोषणा SH_MASK                   0x01
#घोषणा MT_MASK                   0x07
#घोषणा DPSIZR_MASK               0x07
#घोषणा DPSIZC_MASK               0x07


/* TLBTR1 */
#घोषणा TLBTR1_VMID_MASK          0x1F
#घोषणा TLBTR1_PA_MASK            0x000FFFFF


/* TLBTR2 */
#घोषणा TLBTR2_ASID_MASK          0xFF
#घोषणा TLBTR2_V_MASK             0x01
#घोषणा TLBTR2_NSTID_MASK         0x01
#घोषणा TLBTR2_NV_MASK            0x01
#घोषणा TLBTR2_VA_MASK            0x000FFFFF


/* Global Register Shअगरts */
/* CBACRn */
#घोषणा RWVMID_SHIFT             0
#घोषणा RWE_SHIFT                8
#घोषणा RWGE_SHIFT               9
#घोषणा CBVMID_SHIFT             16
#घोषणा IRPTNDX_SHIFT            24


/* CR */
#घोषणा RPUE_SHIFT               0
#घोषणा RPUERE_SHIFT             1
#घोषणा RPUEIE_SHIFT             2
#घोषणा DCDEE_SHIFT              3
#घोषणा CLIENTPD_SHIFT           4
#घोषणा STALLD_SHIFT             5
#घोषणा TLBLKCRWE_SHIFT          6
#घोषणा CR_TLBIALLCFG_SHIFT      7
#घोषणा TLBIVMIDCFG_SHIFT        8
#घोषणा CR_HUME_SHIFT            9


/* ESR */
#घोषणा CFG_SHIFT                0
#घोषणा BYPASS_SHIFT             1
#घोषणा ESR_MULTI_SHIFT          31


/* ESYNR0 */
#घोषणा ESYNR0_AMID_SHIFT        0
#घोषणा ESYNR0_APID_SHIFT        8
#घोषणा ESYNR0_ABID_SHIFT        13
#घोषणा ESYNR0_AVMID_SHIFT       16
#घोषणा ESYNR0_ATID_SHIFT        24


/* ESYNR1 */
#घोषणा ESYNR1_AMEMTYPE_SHIFT           0
#घोषणा ESYNR1_ASHARED_SHIFT            3
#घोषणा ESYNR1_AINNERSHARED_SHIFT       4
#घोषणा ESYNR1_APRIV_SHIFT              5
#घोषणा ESYNR1_APROTNS_SHIFT            6
#घोषणा ESYNR1_AINST_SHIFT              7
#घोषणा ESYNR1_AWRITE_SHIFT             8
#घोषणा ESYNR1_ABURST_SHIFT             10
#घोषणा ESYNR1_ALEN_SHIFT               12
#घोषणा ESYNR1_ASIZE_SHIFT              16
#घोषणा ESYNR1_ALOCK_SHIFT              20
#घोषणा ESYNR1_AOOO_SHIFT               22
#घोषणा ESYNR1_AFULL_SHIFT              24
#घोषणा ESYNR1_AC_SHIFT                 30
#घोषणा ESYNR1_DCD_SHIFT                31


/* IDR */
#घोषणा NM2VCBMT_SHIFT           0
#घोषणा HTW_SHIFT                9
#घोषणा HUM_SHIFT                10
#घोषणा TLBSIZE_SHIFT            12
#घोषणा NCB_SHIFT                16
#घोषणा NIRPT_SHIFT              24


/* M2VCBRn */
#घोषणा VMID_SHIFT               0
#घोषणा CBNDX_SHIFT              8
#घोषणा BYPASSD_SHIFT            16
#घोषणा BPRCOSH_SHIFT            17
#घोषणा BPRCISH_SHIFT            18
#घोषणा BPRCNSH_SHIFT            19
#घोषणा BPSHCFG_SHIFT            20
#घोषणा NSCFG_SHIFT              22
#घोषणा BPMTCFG_SHIFT            24
#घोषणा BPMEMTYPE_SHIFT          25


/* REV */
#घोषणा MINOR_SHIFT              0
#घोषणा MAJOR_SHIFT              4


/* TESTBUSCR */
#घोषणा TBE_SHIFT                0
#घोषणा SPDMBE_SHIFT             1
#घोषणा WGSEL_SHIFT              8
#घोषणा TBLSEL_SHIFT             12
#घोषणा TBHSEL_SHIFT             14
#घोषणा SPDM0SEL_SHIFT           16
#घोषणा SPDM1SEL_SHIFT           20
#घोषणा SPDM2SEL_SHIFT           24
#घोषणा SPDM3SEL_SHIFT           28


/* TLBIMID */
#घोषणा TLBIVMID_VMID_SHIFT      0


/* TLBRSW */
#घोषणा TLBRSW_INDEX_SHIFT       0
#घोषणा TLBBFBS_SHIFT            8


/* TLBTR0 */
#घोषणा PR_SHIFT                 0
#घोषणा PW_SHIFT                 1
#घोषणा UR_SHIFT                 2
#घोषणा UW_SHIFT                 3
#घोषणा XN_SHIFT                 4
#घोषणा NSDESC_SHIFT             6
#घोषणा ISH_SHIFT                7
#घोषणा SH_SHIFT                 8
#घोषणा MT_SHIFT                 9
#घोषणा DPSIZR_SHIFT             16
#घोषणा DPSIZC_SHIFT             20


/* TLBTR1 */
#घोषणा TLBTR1_VMID_SHIFT        0
#घोषणा TLBTR1_PA_SHIFT          12


/* TLBTR2 */
#घोषणा TLBTR2_ASID_SHIFT        0
#घोषणा TLBTR2_V_SHIFT           8
#घोषणा TLBTR2_NSTID_SHIFT       9
#घोषणा TLBTR2_NV_SHIFT          10
#घोषणा TLBTR2_VA_SHIFT          12


/* Context Register Masks */
/* ACTLR */
#घोषणा CFERE_MASK                       0x01
#घोषणा CFEIE_MASK                       0x01
#घोषणा PTSHCFG_MASK                     0x03
#घोषणा RCOSH_MASK                       0x01
#घोषणा RCISH_MASK                       0x01
#घोषणा RCNSH_MASK                       0x01
#घोषणा PRIVCFG_MASK                     0x03
#घोषणा DNA_MASK                         0x01
#घोषणा DNLV2PA_MASK                     0x01
#घोषणा TLBMCFG_MASK                     0x03
#घोषणा CFCFG_MASK                       0x01
#घोषणा TIPCF_MASK                       0x01
#घोषणा V2PCFG_MASK                      0x03
#घोषणा HUME_MASK                        0x01
#घोषणा PTMTCFG_MASK                     0x01
#घोषणा PTMEMTYPE_MASK                   0x07


/* BFBCR */
#घोषणा BFBDFE_MASK                      0x01
#घोषणा BFBSFE_MASK                      0x01
#घोषणा SFVS_MASK                        0x01
#घोषणा FLVIC_MASK                       0x0F
#घोषणा SLVIC_MASK                       0x0F


/* CONTEXTIDR */
#घोषणा CONTEXTIDR_ASID_MASK             0xFF
#घोषणा PROCID_MASK                      0x00FFFFFF


/* FSR */
#घोषणा TF_MASK                          0x01
#घोषणा AFF_MASK                         0x01
#घोषणा APF_MASK                         0x01
#घोषणा TLBMF_MASK                       0x01
#घोषणा HTWDEEF_MASK                     0x01
#घोषणा HTWSEEF_MASK                     0x01
#घोषणा MHF_MASK                         0x01
#घोषणा SL_MASK                          0x01
#घोषणा SS_MASK                          0x01
#घोषणा MULTI_MASK                       0x01


/* FSYNR0 */
#घोषणा AMID_MASK                        0xFF
#घोषणा APID_MASK                        0x1F
#घोषणा ABID_MASK                        0x07
#घोषणा ATID_MASK                        0xFF


/* FSYNR1 */
#घोषणा AMEMTYPE_MASK                    0x07
#घोषणा ASHARED_MASK                     0x01
#घोषणा AINNERSHARED_MASK                0x01
#घोषणा APRIV_MASK                       0x01
#घोषणा APROTNS_MASK                     0x01
#घोषणा AINST_MASK                       0x01
#घोषणा AWRITE_MASK                      0x01
#घोषणा ABURST_MASK                      0x01
#घोषणा ALEN_MASK                        0x0F
#घोषणा FSYNR1_ASIZE_MASK                0x07
#घोषणा ALOCK_MASK                       0x03
#घोषणा AFULL_MASK                       0x01


/* NMRR */
#घोषणा ICPC0_MASK                       0x03
#घोषणा ICPC1_MASK                       0x03
#घोषणा ICPC2_MASK                       0x03
#घोषणा ICPC3_MASK                       0x03
#घोषणा ICPC4_MASK                       0x03
#घोषणा ICPC5_MASK                       0x03
#घोषणा ICPC6_MASK                       0x03
#घोषणा ICPC7_MASK                       0x03
#घोषणा OCPC0_MASK                       0x03
#घोषणा OCPC1_MASK                       0x03
#घोषणा OCPC2_MASK                       0x03
#घोषणा OCPC3_MASK                       0x03
#घोषणा OCPC4_MASK                       0x03
#घोषणा OCPC5_MASK                       0x03
#घोषणा OCPC6_MASK                       0x03
#घोषणा OCPC7_MASK                       0x03


/* PAR */
#घोषणा FAULT_MASK                       0x01
/* If a fault is present, these are the
same as the fault fields in the FAR */
#घोषणा FAULT_TF_MASK                    0x01
#घोषणा FAULT_AFF_MASK                   0x01
#घोषणा FAULT_APF_MASK                   0x01
#घोषणा FAULT_TLBMF_MASK                 0x01
#घोषणा FAULT_HTWDEEF_MASK               0x01
#घोषणा FAULT_HTWSEEF_MASK               0x01
#घोषणा FAULT_MHF_MASK                   0x01
#घोषणा FAULT_SL_MASK                    0x01
#घोषणा FAULT_SS_MASK                    0x01

/* If NO fault is present, the following
 * fields are in effect
 * (FAULT reमुख्यs as beक्रमe) */
#घोषणा PAR_NOFAULT_SS_MASK              0x01
#घोषणा PAR_NOFAULT_MT_MASK              0x07
#घोषणा PAR_NOFAULT_SH_MASK              0x01
#घोषणा PAR_NOFAULT_NS_MASK              0x01
#घोषणा PAR_NOFAULT_NOS_MASK             0x01
#घोषणा PAR_NPFAULT_PA_MASK              0x000FFFFF


/* PRRR */
#घोषणा MTC0_MASK                        0x03
#घोषणा MTC1_MASK                        0x03
#घोषणा MTC2_MASK                        0x03
#घोषणा MTC3_MASK                        0x03
#घोषणा MTC4_MASK                        0x03
#घोषणा MTC5_MASK                        0x03
#घोषणा MTC6_MASK                        0x03
#घोषणा MTC7_MASK                        0x03
#घोषणा SHDSH0_MASK                      0x01
#घोषणा SHDSH1_MASK                      0x01
#घोषणा SHNMSH0_MASK                     0x01
#घोषणा SHNMSH1_MASK                     0x01
#घोषणा NOS0_MASK                        0x01
#घोषणा NOS1_MASK                        0x01
#घोषणा NOS2_MASK                        0x01
#घोषणा NOS3_MASK                        0x01
#घोषणा NOS4_MASK                        0x01
#घोषणा NOS5_MASK                        0x01
#घोषणा NOS6_MASK                        0x01
#घोषणा NOS7_MASK                        0x01


/* RESUME */
#घोषणा TNR_MASK                         0x01


/* SCTLR */
#घोषणा M_MASK                           0x01
#घोषणा TRE_MASK                         0x01
#घोषणा AFE_MASK                         0x01
#घोषणा HAF_MASK                         0x01
#घोषणा BE_MASK                          0x01
#घोषणा AFFD_MASK                        0x01


/* TLBIASID */
#घोषणा TLBIASID_ASID_MASK               0xFF


/* TLBIVA */
#घोषणा TLBIVA_ASID_MASK                 0xFF
#घोषणा TLBIVA_VA_MASK                   0x000FFFFF


/* TLBIVAA */
#घोषणा TLBIVAA_VA_MASK                  0x000FFFFF


/* TLBLCKR */
#घोषणा LKE_MASK                         0x01
#घोषणा TLBLCKR_TLBIALLCFG_MASK          0x01
#घोषणा TLBIASIDCFG_MASK                 0x01
#घोषणा TLBIVAACFG_MASK                  0x01
#घोषणा FLOOR_MASK                       0xFF
#घोषणा VICTIM_MASK                      0xFF


/* TTBCR */
#घोषणा N_MASK                           0x07
#घोषणा PD0_MASK                         0x01
#घोषणा PD1_MASK                         0x01


/* TTBR0 */
#घोषणा TTBR0_IRGNH_MASK                 0x01
#घोषणा TTBR0_SH_MASK                    0x01
#घोषणा TTBR0_ORGN_MASK                  0x03
#घोषणा TTBR0_NOS_MASK                   0x01
#घोषणा TTBR0_IRGNL_MASK                 0x01
#घोषणा TTBR0_PA_MASK                    0x0003FFFF


/* TTBR1 */
#घोषणा TTBR1_IRGNH_MASK                 0x01
#घोषणा TTBR1_SH_MASK                    0x01
#घोषणा TTBR1_ORGN_MASK                  0x03
#घोषणा TTBR1_NOS_MASK                   0x01
#घोषणा TTBR1_IRGNL_MASK                 0x01
#घोषणा TTBR1_PA_MASK                    0x0003FFFF


/* V2PSR */
#घोषणा HIT_MASK                         0x01
#घोषणा INDEX_MASK                       0xFF


/* V2Pxx */
#घोषणा V2Pxx_INDEX_MASK                 0xFF
#घोषणा V2Pxx_VA_MASK                    0x000FFFFF


/* Context Register Shअगरts */
/* ACTLR */
#घोषणा CFERE_SHIFT                    0
#घोषणा CFEIE_SHIFT                    1
#घोषणा PTSHCFG_SHIFT                  2
#घोषणा RCOSH_SHIFT                    4
#घोषणा RCISH_SHIFT                    5
#घोषणा RCNSH_SHIFT                    6
#घोषणा PRIVCFG_SHIFT                  8
#घोषणा DNA_SHIFT                      10
#घोषणा DNLV2PA_SHIFT                  11
#घोषणा TLBMCFG_SHIFT                  12
#घोषणा CFCFG_SHIFT                    14
#घोषणा TIPCF_SHIFT                    15
#घोषणा V2PCFG_SHIFT                   16
#घोषणा HUME_SHIFT                     18
#घोषणा PTMTCFG_SHIFT                  20
#घोषणा PTMEMTYPE_SHIFT                21


/* BFBCR */
#घोषणा BFBDFE_SHIFT                   0
#घोषणा BFBSFE_SHIFT                   1
#घोषणा SFVS_SHIFT                     2
#घोषणा FLVIC_SHIFT                    4
#घोषणा SLVIC_SHIFT                    8


/* CONTEXTIDR */
#घोषणा CONTEXTIDR_ASID_SHIFT          0
#घोषणा PROCID_SHIFT                   8


/* FSR */
#घोषणा TF_SHIFT                       1
#घोषणा AFF_SHIFT                      2
#घोषणा APF_SHIFT                      3
#घोषणा TLBMF_SHIFT                    4
#घोषणा HTWDEEF_SHIFT                  5
#घोषणा HTWSEEF_SHIFT                  6
#घोषणा MHF_SHIFT                      7
#घोषणा SL_SHIFT                       16
#घोषणा SS_SHIFT                       30
#घोषणा MULTI_SHIFT                    31


/* FSYNR0 */
#घोषणा AMID_SHIFT                     0
#घोषणा APID_SHIFT                     8
#घोषणा ABID_SHIFT                     13
#घोषणा ATID_SHIFT                     24


/* FSYNR1 */
#घोषणा AMEMTYPE_SHIFT                 0
#घोषणा ASHARED_SHIFT                  3
#घोषणा AINNERSHARED_SHIFT             4
#घोषणा APRIV_SHIFT                    5
#घोषणा APROTNS_SHIFT                  6
#घोषणा AINST_SHIFT                    7
#घोषणा AWRITE_SHIFT                   8
#घोषणा ABURST_SHIFT                   10
#घोषणा ALEN_SHIFT                     12
#घोषणा FSYNR1_ASIZE_SHIFT             16
#घोषणा ALOCK_SHIFT                    20
#घोषणा AFULL_SHIFT                    24


/* NMRR */
#घोषणा ICPC0_SHIFT                    0
#घोषणा ICPC1_SHIFT                    2
#घोषणा ICPC2_SHIFT                    4
#घोषणा ICPC3_SHIFT                    6
#घोषणा ICPC4_SHIFT                    8
#घोषणा ICPC5_SHIFT                    10
#घोषणा ICPC6_SHIFT                    12
#घोषणा ICPC7_SHIFT                    14
#घोषणा OCPC0_SHIFT                    16
#घोषणा OCPC1_SHIFT                    18
#घोषणा OCPC2_SHIFT                    20
#घोषणा OCPC3_SHIFT                    22
#घोषणा OCPC4_SHIFT                    24
#घोषणा OCPC5_SHIFT                    26
#घोषणा OCPC6_SHIFT                    28
#घोषणा OCPC7_SHIFT                    30


/* PAR */
#घोषणा FAULT_SHIFT                    0
/* If a fault is present, these are the
same as the fault fields in the FAR */
#घोषणा FAULT_TF_SHIFT                 1
#घोषणा FAULT_AFF_SHIFT                2
#घोषणा FAULT_APF_SHIFT                3
#घोषणा FAULT_TLBMF_SHIFT              4
#घोषणा FAULT_HTWDEEF_SHIFT            5
#घोषणा FAULT_HTWSEEF_SHIFT            6
#घोषणा FAULT_MHF_SHIFT                7
#घोषणा FAULT_SL_SHIFT                 16
#घोषणा FAULT_SS_SHIFT                 30

/* If NO fault is present, the following
 * fields are in effect
 * (FAULT reमुख्यs as beक्रमe) */
#घोषणा PAR_NOFAULT_SS_SHIFT           1
#घोषणा PAR_NOFAULT_MT_SHIFT           4
#घोषणा PAR_NOFAULT_SH_SHIFT           7
#घोषणा PAR_NOFAULT_NS_SHIFT           9
#घोषणा PAR_NOFAULT_NOS_SHIFT          10
#घोषणा PAR_NPFAULT_PA_SHIFT           12


/* PRRR */
#घोषणा MTC0_SHIFT                     0
#घोषणा MTC1_SHIFT                     2
#घोषणा MTC2_SHIFT                     4
#घोषणा MTC3_SHIFT                     6
#घोषणा MTC4_SHIFT                     8
#घोषणा MTC5_SHIFT                     10
#घोषणा MTC6_SHIFT                     12
#घोषणा MTC7_SHIFT                     14
#घोषणा SHDSH0_SHIFT                   16
#घोषणा SHDSH1_SHIFT                   17
#घोषणा SHNMSH0_SHIFT                  18
#घोषणा SHNMSH1_SHIFT                  19
#घोषणा NOS0_SHIFT                     24
#घोषणा NOS1_SHIFT                     25
#घोषणा NOS2_SHIFT                     26
#घोषणा NOS3_SHIFT                     27
#घोषणा NOS4_SHIFT                     28
#घोषणा NOS5_SHIFT                     29
#घोषणा NOS6_SHIFT                     30
#घोषणा NOS7_SHIFT                     31


/* RESUME */
#घोषणा TNR_SHIFT                      0


/* SCTLR */
#घोषणा M_SHIFT                        0
#घोषणा TRE_SHIFT                      1
#घोषणा AFE_SHIFT                      2
#घोषणा HAF_SHIFT                      3
#घोषणा BE_SHIFT                       4
#घोषणा AFFD_SHIFT                     5


/* TLBIASID */
#घोषणा TLBIASID_ASID_SHIFT            0


/* TLBIVA */
#घोषणा TLBIVA_ASID_SHIFT              0
#घोषणा TLBIVA_VA_SHIFT                12


/* TLBIVAA */
#घोषणा TLBIVAA_VA_SHIFT               12


/* TLBLCKR */
#घोषणा LKE_SHIFT                      0
#घोषणा TLBLCKR_TLBIALLCFG_SHIFT       1
#घोषणा TLBIASIDCFG_SHIFT              2
#घोषणा TLBIVAACFG_SHIFT               3
#घोषणा FLOOR_SHIFT                    8
#घोषणा VICTIM_SHIFT                   8


/* TTBCR */
#घोषणा N_SHIFT                        3
#घोषणा PD0_SHIFT                      4
#घोषणा PD1_SHIFT                      5


/* TTBR0 */
#घोषणा TTBR0_IRGNH_SHIFT              0
#घोषणा TTBR0_SH_SHIFT                 1
#घोषणा TTBR0_ORGN_SHIFT               3
#घोषणा TTBR0_NOS_SHIFT                5
#घोषणा TTBR0_IRGNL_SHIFT              6
#घोषणा TTBR0_PA_SHIFT                 14


/* TTBR1 */
#घोषणा TTBR1_IRGNH_SHIFT              0
#घोषणा TTBR1_SH_SHIFT                 1
#घोषणा TTBR1_ORGN_SHIFT               3
#घोषणा TTBR1_NOS_SHIFT                5
#घोषणा TTBR1_IRGNL_SHIFT              6
#घोषणा TTBR1_PA_SHIFT                 14


/* V2PSR */
#घोषणा HIT_SHIFT                      0
#घोषणा INDEX_SHIFT                    8


/* V2Pxx */
#घोषणा V2Pxx_INDEX_SHIFT              0
#घोषणा V2Pxx_VA_SHIFT                 12

#पूर्ण_अगर
