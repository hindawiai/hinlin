<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003, 2004 Ralf Baechle
 * Copyright (C) 2004  Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_CPU_FEATURES_H
#घोषणा __ASM_CPU_FEATURES_H

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-info.h>
#समावेश <यंत्र/isa-rev.h>
#समावेश <cpu-feature-overrides.h>

#घोषणा __ase(ase)			(cpu_data[0].ases & (ase))
#घोषणा __isa(isa)			(cpu_data[0].isa_level & (isa))
#घोषणा __opt(opt)			(cpu_data[0].options & (opt))

/*
 * Check अगर MIPS_ISA_REV is >= isa *and* an option or ASE is detected during
 * boot (typically by cpu_probe()).
 *
 * Note that these should only be used in हालs where a kernel built क्रम an
 * older ISA *cannot* run on a CPU which supports the feature in question. For
 * example this may be used क्रम features पूर्णांकroduced with MIPSr6, since a kernel
 * built क्रम an older ISA cannot run on a MIPSr6 CPU. This should not be used
 * क्रम MIPSr2 features however, since a MIPSr1 or earlier kernel might run on a
 * MIPSr2 CPU.
 */
#घोषणा __isa_ge_and_ase(isa, ase)	((MIPS_ISA_REV >= (isa)) && __ase(ase))
#घोषणा __isa_ge_and_opt(isa, opt)	((MIPS_ISA_REV >= (isa)) && __opt(opt))

/*
 * Check अगर MIPS_ISA_REV is >= isa *or* an option or ASE is detected during
 * boot (typically by cpu_probe()).
 *
 * These are क्रम use with features that are optional up until a particular ISA
 * revision & then become required.
 */
#घोषणा __isa_ge_or_ase(isa, ase)	((MIPS_ISA_REV >= (isa)) || __ase(ase))
#घोषणा __isa_ge_or_opt(isa, opt)	((MIPS_ISA_REV >= (isa)) || __opt(opt))

/*
 * Check अगर MIPS_ISA_REV is < isa *and* an option or ASE is detected during
 * boot (typically by cpu_probe()).
 *
 * These are क्रम use with features that are optional up until a particular ISA
 * revision & are then हटाओd - ie. no दीर्घer present in any CPU implementing
 * the given ISA revision.
 */
#घोषणा __isa_lt_and_ase(isa, ase)	((MIPS_ISA_REV < (isa)) && __ase(ase))
#घोषणा __isa_lt_and_opt(isa, opt)	((MIPS_ISA_REV < (isa)) && __opt(opt))

/*
 * Similarly allow क्रम ISA level checks that take पूर्णांकo account knowledge of the
 * ISA targeted by the kernel build, provided by MIPS_ISA_REV.
 */
#घोषणा __isa_ge_and_flag(isa, flag)	((MIPS_ISA_REV >= (isa)) && __isa(flag))
#घोषणा __isa_ge_or_flag(isa, flag)	((MIPS_ISA_REV >= (isa)) || __isa(flag))
#घोषणा __isa_lt_and_flag(isa, flag)	((MIPS_ISA_REV < (isa)) && __isa(flag))
#घोषणा __isa_range(ge, lt) \
	((MIPS_ISA_REV >= (ge)) && (MIPS_ISA_REV < (lt)))
#घोषणा __isa_range_or_flag(ge, lt, flag) \
	(__isa_range(ge, lt) || ((MIPS_ISA_REV < (lt)) && __isa(flag)))

/*
 * SMP assumption: Options of CPU 0 are a superset of all processors.
 * This is true क्रम all known MIPS प्रणालीs.
 */
#अगर_अघोषित cpu_has_tlb
#घोषणा cpu_has_tlb		__opt(MIPS_CPU_TLB)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_ftlb
#घोषणा cpu_has_ftlb		__opt(MIPS_CPU_FTLB)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_tlbinv
#घोषणा cpu_has_tlbinv		__opt(MIPS_CPU_TLBINV)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_segments
#घोषणा cpu_has_segments	__opt(MIPS_CPU_SEGMENTS)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_eva
#घोषणा cpu_has_eva		__opt(MIPS_CPU_EVA)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_htw
#घोषणा cpu_has_htw		__opt(MIPS_CPU_HTW)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_ldpte
#घोषणा cpu_has_ldpte		__opt(MIPS_CPU_LDPTE)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_rixiex
#घोषणा cpu_has_rixiex		__isa_ge_or_opt(6, MIPS_CPU_RIXIEX)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_maar
#घोषणा cpu_has_maar		__opt(MIPS_CPU_MAAR)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_rw_llb
#घोषणा cpu_has_rw_llb		__isa_ge_or_opt(6, MIPS_CPU_RW_LLB)
#पूर्ण_अगर

/*
 * For the moment we करोn't consider R6000 and R8000 so we can assume that
 * anything that करोesn't support R4000-style exceptions and पूर्णांकerrupts is
 * R3000-like.  Users should still treat these two macro definitions as
 * opaque.
 */
#अगर_अघोषित cpu_has_3kex
#घोषणा cpu_has_3kex		(!cpu_has_4kex)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_4kex
#घोषणा cpu_has_4kex		__isa_ge_or_opt(1, MIPS_CPU_4KEX)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_3k_cache
#घोषणा cpu_has_3k_cache	__isa_lt_and_opt(1, MIPS_CPU_3K_CACHE)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_4k_cache
#घोषणा cpu_has_4k_cache	__isa_ge_or_opt(1, MIPS_CPU_4K_CACHE)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_tx39_cache
#घोषणा cpu_has_tx39_cache	__opt(MIPS_CPU_TX39_CACHE)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_octeon_cache
#घोषणा cpu_has_octeon_cache	0
#पूर्ण_अगर
/* Don't override `cpu_has_fpu' to 1 or the "nofpu" option won't work.  */
#अगर_अघोषित cpu_has_fpu
# अगरdef CONFIG_MIPS_FP_SUPPORT
#  define cpu_has_fpu		(current_cpu_data.options & MIPS_CPU_FPU)
#  define raw_cpu_has_fpu	(raw_current_cpu_data.options & MIPS_CPU_FPU)
# अन्यथा
#  define cpu_has_fpu		0
#  define raw_cpu_has_fpu	0
# endअगर
#अन्यथा
# define raw_cpu_has_fpu	cpu_has_fpu
#पूर्ण_अगर
#अगर_अघोषित cpu_has_32fpr
#घोषणा cpu_has_32fpr		__isa_ge_or_opt(1, MIPS_CPU_32FPR)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_counter
#घोषणा cpu_has_counter		__opt(MIPS_CPU_COUNTER)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_watch
#घोषणा cpu_has_watch		__opt(MIPS_CPU_WATCH)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_भागec
#घोषणा cpu_has_भागec		__isa_ge_or_opt(1, MIPS_CPU_DIVEC)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_vce
#घोषणा cpu_has_vce		__opt(MIPS_CPU_VCE)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_cache_cdex_p
#घोषणा cpu_has_cache_cdex_p	__opt(MIPS_CPU_CACHE_CDEX_P)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_cache_cdex_s
#घोषणा cpu_has_cache_cdex_s	__opt(MIPS_CPU_CACHE_CDEX_S)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_prefetch
#घोषणा cpu_has_prefetch	__isa_ge_or_opt(1, MIPS_CPU_PREFETCH)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mcheck
#घोषणा cpu_has_mcheck		__isa_ge_or_opt(1, MIPS_CPU_MCHECK)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_ejtag
#घोषणा cpu_has_ejtag		__opt(MIPS_CPU_EJTAG)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_llsc
#घोषणा cpu_has_llsc		__isa_ge_or_opt(1, MIPS_CPU_LLSC)
#पूर्ण_अगर
#अगर_अघोषित kernel_uses_llsc
#घोषणा kernel_uses_llsc	cpu_has_llsc
#पूर्ण_अगर
#अगर_अघोषित cpu_has_guestctl0ext
#घोषणा cpu_has_guestctl0ext	__opt(MIPS_CPU_GUESTCTL0EXT)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_guestctl1
#घोषणा cpu_has_guestctl1	__opt(MIPS_CPU_GUESTCTL1)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_guestctl2
#घोषणा cpu_has_guestctl2	__opt(MIPS_CPU_GUESTCTL2)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_guestid
#घोषणा cpu_has_guestid		__opt(MIPS_CPU_GUESTID)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_drg
#घोषणा cpu_has_drg		__opt(MIPS_CPU_DRG)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips16
#घोषणा cpu_has_mips16		__isa_lt_and_ase(6, MIPS_ASE_MIPS16)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips16e2
#घोषणा cpu_has_mips16e2	__isa_lt_and_ase(6, MIPS_ASE_MIPS16E2)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mdmx
#घोषणा cpu_has_mdmx		__isa_lt_and_ase(6, MIPS_ASE_MDMX)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips3d
#घोषणा cpu_has_mips3d		__isa_lt_and_ase(6, MIPS_ASE_MIPS3D)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_smarपंचांगips
#घोषणा cpu_has_smarपंचांगips	__isa_lt_and_ase(6, MIPS_ASE_SMARTMIPS)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_rixi
#घोषणा cpu_has_rixi		__isa_ge_or_opt(6, MIPS_CPU_RIXI)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_mmips
# अगर defined(__mips_micromips)
#  define cpu_has_mmips		1
# elअगर defined(CONFIG_SYS_SUPPORTS_MICROMIPS)
#  define cpu_has_mmips		__opt(MIPS_CPU_MICROMIPS)
# अन्यथा
#  define cpu_has_mmips		0
# endअगर
#पूर्ण_अगर

#अगर_अघोषित cpu_has_lpa
#घोषणा cpu_has_lpa		__opt(MIPS_CPU_LPA)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mvh
#घोषणा cpu_has_mvh		__opt(MIPS_CPU_MVH)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_xpa
#घोषणा cpu_has_xpa		(cpu_has_lpa && cpu_has_mvh)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_vtag_icache
#घोषणा cpu_has_vtag_icache	(cpu_data[0].icache.flags & MIPS_CACHE_VTAG)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_dc_aliases
#घोषणा cpu_has_dc_aliases	(cpu_data[0].dcache.flags & MIPS_CACHE_ALIASES)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_ic_fills_f_dc
#घोषणा cpu_has_ic_fills_f_dc	(cpu_data[0].icache.flags & MIPS_CACHE_IC_F_DC)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_pindexed_dcache
#घोषणा cpu_has_pindexed_dcache	(cpu_data[0].dcache.flags & MIPS_CACHE_PINDEX)
#पूर्ण_अगर

/*
 * I-Cache snoops remote store.	 This only matters on SMP.  Some multiprocessors
 * such as the R10000 have I-Caches that snoop local stores; the embedded ones
 * करोn't.  For मुख्यtaining I-cache coherency this means we need to flush the
 * D-cache all the way back to whever the I-cache करोes refills from, so the
 * I-cache has a chance to see the new data at all.  Then we have to flush the
 * I-cache also.
 * Note we may have been rescheduled and may no दीर्घer be running on the CPU
 * that did the store so we can't optimize this पूर्णांकo only करोing the flush on
 * the local CPU.
 */
#अगर_अघोषित cpu_icache_snoops_remote_store
#अगर_घोषित CONFIG_SMP
#घोषणा cpu_icache_snoops_remote_store	(cpu_data[0].icache.flags & MIPS_IC_SNOOPS_REMOTE)
#अन्यथा
#घोषणा cpu_icache_snoops_remote_store	1
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित cpu_has_mips_1
# define cpu_has_mips_1		(MIPS_ISA_REV < 6)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips_2
# define cpu_has_mips_2		__isa_lt_and_flag(6, MIPS_CPU_ISA_II)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips_3
# define cpu_has_mips_3		__isa_lt_and_flag(6, MIPS_CPU_ISA_III)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips_4
# define cpu_has_mips_4		__isa_lt_and_flag(6, MIPS_CPU_ISA_IV)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips_5
# define cpu_has_mips_5		__isa_lt_and_flag(6, MIPS_CPU_ISA_V)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips32r1
# define cpu_has_mips32r1	__isa_range_or_flag(1, 6, MIPS_CPU_ISA_M32R1)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips32r2
# define cpu_has_mips32r2	__isa_range_or_flag(2, 6, MIPS_CPU_ISA_M32R2)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips32r5
# define cpu_has_mips32r5	__isa_range_or_flag(5, 6, MIPS_CPU_ISA_M32R5)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips32r6
# define cpu_has_mips32r6	__isa_ge_or_flag(6, MIPS_CPU_ISA_M32R6)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips64r1
# define cpu_has_mips64r1	(cpu_has_64bits && \
				 __isa_range_or_flag(1, 6, MIPS_CPU_ISA_M64R1))
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips64r2
# define cpu_has_mips64r2	(cpu_has_64bits && \
				 __isa_range_or_flag(2, 6, MIPS_CPU_ISA_M64R2))
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips64r5
# define cpu_has_mips64r5	(cpu_has_64bits && \
				 __isa_range_or_flag(5, 6, MIPS_CPU_ISA_M64R5))
#पूर्ण_अगर
#अगर_अघोषित cpu_has_mips64r6
# define cpu_has_mips64r6	__isa_ge_and_flag(6, MIPS_CPU_ISA_M64R6)
#पूर्ण_अगर

/*
 * Shortcuts ...
 */
#घोषणा cpu_has_mips_2_3_4_5	(cpu_has_mips_2 | cpu_has_mips_3_4_5)
#घोषणा cpu_has_mips_3_4_5	(cpu_has_mips_3 | cpu_has_mips_4_5)
#घोषणा cpu_has_mips_4_5	(cpu_has_mips_4 | cpu_has_mips_5)

#घोषणा cpu_has_mips_2_3_4_5_r	(cpu_has_mips_2 | cpu_has_mips_3_4_5_r)
#घोषणा cpu_has_mips_3_4_5_r	(cpu_has_mips_3 | cpu_has_mips_4_5_r)
#घोषणा cpu_has_mips_4_5_r	(cpu_has_mips_4 | cpu_has_mips_5_r)
#घोषणा cpu_has_mips_5_r	(cpu_has_mips_5 | cpu_has_mips_r)

#घोषणा cpu_has_mips_3_4_5_64_r2_r6					\
				(cpu_has_mips_3 | cpu_has_mips_4_5_64_r2_r6)
#घोषणा cpu_has_mips_4_5_64_r2_r6					\
				(cpu_has_mips_4_5 | cpu_has_mips64r1 |	\
				 cpu_has_mips_r2 | cpu_has_mips_r5 | \
				 cpu_has_mips_r6)

#घोषणा cpu_has_mips32	(cpu_has_mips32r1 | cpu_has_mips32r2 | \
			 cpu_has_mips32r5 | cpu_has_mips32r6)
#घोषणा cpu_has_mips64	(cpu_has_mips64r1 | cpu_has_mips64r2 | \
			 cpu_has_mips64r5 | cpu_has_mips64r6)
#घोषणा cpu_has_mips_r1 (cpu_has_mips32r1 | cpu_has_mips64r1)
#घोषणा cpu_has_mips_r2 (cpu_has_mips32r2 | cpu_has_mips64r2)
#घोषणा cpu_has_mips_r5	(cpu_has_mips32r5 | cpu_has_mips64r5)
#घोषणा cpu_has_mips_r6	(cpu_has_mips32r6 | cpu_has_mips64r6)
#घोषणा cpu_has_mips_r	(cpu_has_mips32r1 | cpu_has_mips32r2 | \
			 cpu_has_mips32r5 | cpu_has_mips32r6 | \
			 cpu_has_mips64r1 | cpu_has_mips64r2 | \
			 cpu_has_mips64r5 | cpu_has_mips64r6)

/* MIPSR2 - MIPSR6 have a lot of similarities */
#घोषणा cpu_has_mips_r2_r6	(cpu_has_mips_r2 | cpu_has_mips_r5 | \
				 cpu_has_mips_r6)

/*
 * cpu_has_mips_r2_exec_hazard - वापस अगर IHB is required on current processor
 *
 * Returns non-zero value अगर the current processor implementation requires
 * an IHB inकाष्ठाion to deal with an inकाष्ठाion hazard as per MIPS R2
 * architecture specअगरication, zero otherwise.
 */
#अगर_अघोषित cpu_has_mips_r2_exec_hazard
#घोषणा cpu_has_mips_r2_exec_hazard					\
(अणु									\
	पूर्णांक __res;							\
									\
	चयन (current_cpu_type()) अणु					\
	हाल CPU_M14KC:							\
	हाल CPU_74K:							\
	हाल CPU_1074K:							\
	हाल CPU_PROAPTIV:						\
	हाल CPU_P5600:							\
	हाल CPU_M5150:							\
	हाल CPU_QEMU_GENERIC:						\
	हाल CPU_CAVIUM_OCTEON:						\
	हाल CPU_CAVIUM_OCTEON_PLUS:					\
	हाल CPU_CAVIUM_OCTEON2:					\
	हाल CPU_CAVIUM_OCTEON3:					\
		__res = 0;						\
		अवरोध;							\
									\
	शेष:							\
		__res = 1;						\
	पूर्ण								\
									\
	__res;								\
पूर्ण)
#पूर्ण_अगर

/*
 * MIPS32, MIPS64, VR5500, IDT32332, IDT32334 and maybe a few other
 * pre-MIPS32/MIPS64 processors have CLO, CLZ.	The IDT RC64574 is 64-bit and
 * has CLO and CLZ but not DCLO nor DCLZ.  For 64-bit kernels
 * cpu_has_clo_clz also indicates the availability of DCLO and DCLZ.
 */
#अगर_अघोषित cpu_has_clo_clz
#घोषणा cpu_has_clo_clz	cpu_has_mips_r
#पूर्ण_अगर

/*
 * MIPS32 R2, MIPS64 R2, Loongson 3A and Octeon have WSBH.
 * MIPS64 R2, Loongson 3A and Octeon have WSBH, DSBH and DSHD.
 * This indicates the availability of WSBH and in हाल of 64 bit CPUs also
 * DSBH and DSHD.
 */
#अगर_अघोषित cpu_has_wsbh
#घोषणा cpu_has_wsbh		cpu_has_mips_r2
#पूर्ण_अगर

#अगर_अघोषित cpu_has_dsp
#घोषणा cpu_has_dsp		__ase(MIPS_ASE_DSP)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_dsp2
#घोषणा cpu_has_dsp2		__ase(MIPS_ASE_DSP2P)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_dsp3
#घोषणा cpu_has_dsp3		__ase(MIPS_ASE_DSP3)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_loongson_mmi
#घोषणा cpu_has_loongson_mmi		__ase(MIPS_ASE_LOONGSON_MMI)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_loongson_cam
#घोषणा cpu_has_loongson_cam		__ase(MIPS_ASE_LOONGSON_CAM)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_loongson_ext
#घोषणा cpu_has_loongson_ext		__ase(MIPS_ASE_LOONGSON_EXT)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_loongson_ext2
#घोषणा cpu_has_loongson_ext2		__ase(MIPS_ASE_LOONGSON_EXT2)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_mipsmt
#घोषणा cpu_has_mipsmt		__isa_lt_and_ase(6, MIPS_ASE_MIPSMT)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_vp
#घोषणा cpu_has_vp		__isa_ge_and_opt(6, MIPS_CPU_VP)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_userlocal
#घोषणा cpu_has_userlocal	__isa_ge_or_opt(6, MIPS_CPU_ULRI)
#पूर्ण_अगर

#अगर_घोषित CONFIG_32BIT
# अगरndef cpu_has_nofpuex
# define cpu_has_nofpuex	__isa_lt_and_opt(1, MIPS_CPU_NOFPUEX)
# endअगर
# अगरndef cpu_has_64bits
# define cpu_has_64bits		(cpu_data[0].isa_level & MIPS_CPU_ISA_64BIT)
# endअगर
# अगरndef cpu_has_64bit_zero_reg
# define cpu_has_64bit_zero_reg	(cpu_data[0].isa_level & MIPS_CPU_ISA_64BIT)
# endअगर
# अगरndef cpu_has_64bit_gp_regs
# define cpu_has_64bit_gp_regs		0
# endअगर
# अगरndef cpu_vmbits
# define cpu_vmbits 31
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
# अगरndef cpu_has_nofpuex
# define cpu_has_nofpuex		0
# endअगर
# अगरndef cpu_has_64bits
# define cpu_has_64bits			1
# endअगर
# अगरndef cpu_has_64bit_zero_reg
# define cpu_has_64bit_zero_reg		1
# endअगर
# अगरndef cpu_has_64bit_gp_regs
# define cpu_has_64bit_gp_regs		1
# endअगर
# अगरndef cpu_vmbits
# define cpu_vmbits cpu_data[0].vmbits
# define __NEED_VMBITS_PROBE
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_MIPSR2_IRQ_VI) && !defined(cpu_has_vपूर्णांक)
# define cpu_has_vपूर्णांक		__opt(MIPS_CPU_VINT)
#या_अगर !defined(cpu_has_vपूर्णांक)
# define cpu_has_vपूर्णांक			0
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_MIPSR2_IRQ_EI) && !defined(cpu_has_veic)
# define cpu_has_veic		__opt(MIPS_CPU_VEIC)
#या_अगर !defined(cpu_has_veic)
# define cpu_has_veic			0
#पूर्ण_अगर

#अगर_अघोषित cpu_has_inclusive_pcaches
#घोषणा cpu_has_inclusive_pcaches	__opt(MIPS_CPU_INCLUSIVE_CACHES)
#पूर्ण_अगर

#अगर_अघोषित cpu_dcache_line_size
#घोषणा cpu_dcache_line_size()	cpu_data[0].dcache.linesz
#पूर्ण_अगर
#अगर_अघोषित cpu_icache_line_size
#घोषणा cpu_icache_line_size()	cpu_data[0].icache.linesz
#पूर्ण_अगर
#अगर_अघोषित cpu_scache_line_size
#घोषणा cpu_scache_line_size()	cpu_data[0].scache.linesz
#पूर्ण_अगर
#अगर_अघोषित cpu_tcache_line_size
#घोषणा cpu_tcache_line_size()	cpu_data[0].tcache.linesz
#पूर्ण_अगर

#अगर_अघोषित cpu_hwrena_impl_bits
#घोषणा cpu_hwrena_impl_bits		0
#पूर्ण_अगर

#अगर_अघोषित cpu_has_perf_cntr_पूर्णांकr_bit
#घोषणा cpu_has_perf_cntr_पूर्णांकr_bit	__opt(MIPS_CPU_PCI)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_vz
#घोषणा cpu_has_vz		__ase(MIPS_ASE_VZ)
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_HAS_MSA) && !defined(cpu_has_msa)
# define cpu_has_msa		__ase(MIPS_ASE_MSA)
#या_अगर !defined(cpu_has_msa)
# define cpu_has_msa		0
#पूर्ण_अगर

#अगर_अघोषित cpu_has_ufr
# define cpu_has_ufr		__opt(MIPS_CPU_UFR)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_fre
# define cpu_has_fre		__opt(MIPS_CPU_FRE)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_cdmm
# define cpu_has_cdmm		__opt(MIPS_CPU_CDMM)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_small_pages
# define cpu_has_small_pages	__opt(MIPS_CPU_SP)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_nan_legacy
#घोषणा cpu_has_nan_legacy	__isa_lt_and_opt(6, MIPS_CPU_न_अंक_LEGACY)
#पूर्ण_अगर
#अगर_अघोषित cpu_has_nan_2008
#घोषणा cpu_has_nan_2008	__isa_ge_or_opt(6, MIPS_CPU_न_अंक_2008)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_ebase_wg
# define cpu_has_ebase_wg	__opt(MIPS_CPU_EBASE_WG)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_badinstr
# define cpu_has_badinstr	__isa_ge_or_opt(6, MIPS_CPU_BADINSTR)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_badinstrp
# define cpu_has_badinstrp	__isa_ge_or_opt(6, MIPS_CPU_BADINSTRP)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_contextconfig
# define cpu_has_contextconfig	__opt(MIPS_CPU_CTXTC)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_perf
# define cpu_has_perf		__opt(MIPS_CPU_PERF)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_mac2008_only
# define cpu_has_mac2008_only	__opt(MIPS_CPU_MAC_2008_ONLY)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_ftlbparex
# define cpu_has_ftlbparex	__opt(MIPS_CPU_FTLBPAREX)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_gsexcex
# define cpu_has_gsexcex	__opt(MIPS_CPU_GSEXCEX)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
/*
 * Some प्रणालीs share FTLB RAMs between thपढ़ोs within a core (siblings in
 * kernel parlance). This means that FTLB entries may become invalid at almost
 * any poपूर्णांक when an entry is evicted due to a sibling thपढ़ो writing an entry
 * to the shared FTLB RAM.
 *
 * This is only relevant to SMP प्रणालीs, and the only प्रणालीs that exhibit this
 * property implement MIPSr6 or higher so we स्थिरrain support क्रम this to
 * kernels that will run on such प्रणालीs.
 */
# अगरndef cpu_has_shared_ftlb_ram
#  define cpu_has_shared_ftlb_ram \
	__isa_ge_and_opt(6, MIPS_CPU_SHARED_FTLB_RAM)
# endअगर

/*
 * Some प्रणालीs take this a step further & share FTLB entries between siblings.
 * This is implemented as TLB ग_लिखोs happening as usual, but अगर an entry
 * written by a sibling exists in the shared FTLB क्रम a translation which would
 * otherwise cause a TLB refill exception then the CPU will use the entry
 * written by its sibling rather than triggering a refill & writing a matching
 * TLB entry क्रम itself.
 *
 * This is naturally only valid अगर a TLB entry is known to be suitable क्रम use
 * on all siblings in a CPU, and so it only takes effect when MMIDs are in use
 * rather than ASIDs or when a TLB entry is marked global.
 */
# अगरndef cpu_has_shared_ftlb_entries
#  define cpu_has_shared_ftlb_entries \
	__isa_ge_and_opt(6, MIPS_CPU_SHARED_FTLB_ENTRIES)
# endअगर
#पूर्ण_अगर /* SMP */

#अगर_अघोषित cpu_has_shared_ftlb_ram
# define cpu_has_shared_ftlb_ram 0
#पूर्ण_अगर
#अगर_अघोषित cpu_has_shared_ftlb_entries
# define cpu_has_shared_ftlb_entries 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MIPS_MT_SMP
# define cpu_has_mipsmt_pertccounters \
	__isa_lt_and_opt(6, MIPS_CPU_MT_PER_TC_PERF_COUNTERS)
#अन्यथा
# define cpu_has_mipsmt_pertccounters 0
#पूर्ण_अगर /* CONFIG_MIPS_MT_SMP */

/*
 * We only enable MMID support क्रम configurations which natively support 64 bit
 * atomics because getting good perक्रमmance from the allocator relies upon
 * efficient atomic64_*() functions.
 */
#अगर_अघोषित cpu_has_mmid
# अगरdef CONFIG_GENERIC_ATOMIC64
#  define cpu_has_mmid		0
# अन्यथा
#  define cpu_has_mmid		__isa_ge_and_opt(6, MIPS_CPU_MMID)
# endअगर
#पूर्ण_अगर

#अगर_अघोषित cpu_has_mm_sysad
# define cpu_has_mm_sysad	__opt(MIPS_CPU_MM_SYSAD)
#पूर्ण_अगर

#अगर_अघोषित cpu_has_mm_full
# define cpu_has_mm_full	__opt(MIPS_CPU_MM_FULL)
#पूर्ण_अगर

/*
 * Guest capabilities
 */
#अगर_अघोषित cpu_guest_has_conf1
#घोषणा cpu_guest_has_conf1	(cpu_data[0].guest.conf & (1 << 1))
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_conf2
#घोषणा cpu_guest_has_conf2	(cpu_data[0].guest.conf & (1 << 2))
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_conf3
#घोषणा cpu_guest_has_conf3	(cpu_data[0].guest.conf & (1 << 3))
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_conf4
#घोषणा cpu_guest_has_conf4	(cpu_data[0].guest.conf & (1 << 4))
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_conf5
#घोषणा cpu_guest_has_conf5	(cpu_data[0].guest.conf & (1 << 5))
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_conf6
#घोषणा cpu_guest_has_conf6	(cpu_data[0].guest.conf & (1 << 6))
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_conf7
#घोषणा cpu_guest_has_conf7	(cpu_data[0].guest.conf & (1 << 7))
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_fpu
#घोषणा cpu_guest_has_fpu	(cpu_data[0].guest.options & MIPS_CPU_FPU)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_watch
#घोषणा cpu_guest_has_watch	(cpu_data[0].guest.options & MIPS_CPU_WATCH)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_contextconfig
#घोषणा cpu_guest_has_contextconfig (cpu_data[0].guest.options & MIPS_CPU_CTXTC)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_segments
#घोषणा cpu_guest_has_segments	(cpu_data[0].guest.options & MIPS_CPU_SEGMENTS)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_badinstr
#घोषणा cpu_guest_has_badinstr	(cpu_data[0].guest.options & MIPS_CPU_BADINSTR)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_badinstrp
#घोषणा cpu_guest_has_badinstrp	(cpu_data[0].guest.options & MIPS_CPU_BADINSTRP)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_htw
#घोषणा cpu_guest_has_htw	(cpu_data[0].guest.options & MIPS_CPU_HTW)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_ldpte
#घोषणा cpu_guest_has_ldpte	(cpu_data[0].guest.options & MIPS_CPU_LDPTE)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_mvh
#घोषणा cpu_guest_has_mvh	(cpu_data[0].guest.options & MIPS_CPU_MVH)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_msa
#घोषणा cpu_guest_has_msa	(cpu_data[0].guest.ases & MIPS_ASE_MSA)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_kscr
#घोषणा cpu_guest_has_kscr(n)	(cpu_data[0].guest.kscratch_mask & (1u << (n)))
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_rw_llb
#घोषणा cpu_guest_has_rw_llb	(cpu_has_mips_r6 || (cpu_data[0].guest.options & MIPS_CPU_RW_LLB))
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_perf
#घोषणा cpu_guest_has_perf	(cpu_data[0].guest.options & MIPS_CPU_PERF)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_maar
#घोषणा cpu_guest_has_maar	(cpu_data[0].guest.options & MIPS_CPU_MAAR)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_userlocal
#घोषणा cpu_guest_has_userlocal	(cpu_data[0].guest.options & MIPS_CPU_ULRI)
#पूर्ण_अगर

/*
 * Guest dynamic capabilities
 */
#अगर_अघोषित cpu_guest_has_dyn_fpu
#घोषणा cpu_guest_has_dyn_fpu	(cpu_data[0].guest.options_dyn & MIPS_CPU_FPU)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_dyn_watch
#घोषणा cpu_guest_has_dyn_watch	(cpu_data[0].guest.options_dyn & MIPS_CPU_WATCH)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_dyn_contextconfig
#घोषणा cpu_guest_has_dyn_contextconfig (cpu_data[0].guest.options_dyn & MIPS_CPU_CTXTC)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_dyn_perf
#घोषणा cpu_guest_has_dyn_perf	(cpu_data[0].guest.options_dyn & MIPS_CPU_PERF)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_dyn_msa
#घोषणा cpu_guest_has_dyn_msa	(cpu_data[0].guest.ases_dyn & MIPS_ASE_MSA)
#पूर्ण_अगर
#अगर_अघोषित cpu_guest_has_dyn_maar
#घोषणा cpu_guest_has_dyn_maar	(cpu_data[0].guest.options_dyn & MIPS_CPU_MAAR)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_CPU_FEATURES_H */
