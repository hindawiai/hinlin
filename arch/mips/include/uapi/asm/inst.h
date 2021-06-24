<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Format of an inकाष्ठाion in memory.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 2000 by Ralf Baechle
 * Copyright (C) 2006 by Thiemo Seufer
 * Copyright (C) 2012 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2014 Imagination Technologies Ltd.
 */
#अगर_अघोषित _UAPI_ASM_INST_H
#घोषणा _UAPI_ASM_INST_H

#समावेश <यंत्र/bitfield.h>

/*
 * Major opcodes; beक्रमe MIPS IV cop1x was called cop3.
 */
क्रमागत major_op अणु
	spec_op, bcond_op, j_op, jal_op,
	beq_op, bne_op, blez_op, bgtz_op,
	addi_op, pop10_op = addi_op, addiu_op, slti_op, sltiu_op,
	andi_op, ori_op, xori_op, lui_op,
	cop0_op, cop1_op, cop2_op, cop1x_op,
	beql_op, bnel_op, blezl_op, bgtzl_op,
	daddi_op, pop30_op = daddi_op, daddiu_op, ldl_op, ldr_op,
	spec2_op, jalx_op, mdmx_op, msa_op = mdmx_op, spec3_op,
	lb_op, lh_op, lwl_op, lw_op,
	lbu_op, lhu_op, lwr_op, lwu_op,
	sb_op, sh_op, swl_op, sw_op,
	sdl_op, sdr_op, swr_op, cache_op,
	ll_op, lwc1_op, lwc2_op, bc6_op = lwc2_op, pref_op,
	lld_op, ldc1_op, ldc2_op, pop66_op = ldc2_op, ld_op,
	sc_op, swc1_op, swc2_op, balc6_op = swc2_op, major_3b_op,
	scd_op, sdc1_op, sdc2_op, pop76_op = sdc2_op, sd_op
पूर्ण;

/*
 * func field of spec opcode.
 */
क्रमागत spec_op अणु
	sll_op, movc_op, srl_op, sra_op,
	sllv_op, pmon_op, srlv_op, srav_op,
	jr_op, jalr_op, movz_op, movn_op,
	syscall_op, अवरोध_op, spim_op, sync_op,
	mfhi_op, mthi_op, mflo_op, mtlo_op,
	dsllv_op, spec2_unused_op, dsrlv_op, dsrav_op,
	mult_op, multu_op, भाग_op, भागu_op,
	dmult_op, dmultu_op, dभाग_op, dभागu_op,
	add_op, addu_op, sub_op, subu_op,
	and_op, or_op, xor_op, nor_op,
	spec3_unused_op, spec4_unused_op, slt_op, sltu_op,
	dadd_op, daddu_op, dsub_op, dsubu_op,
	tge_op, tgeu_op, tlt_op, tltu_op,
	teq_op, seleqz_op, tne_op, selnez_op,
	dsll_op, spec5_unused_op, dsrl_op, dsra_op,
	dsll32_op, spec6_unused_op, dsrl32_op, dsra32_op
पूर्ण;

/*
 * func field of spec2 opcode.
 */
क्रमागत spec2_op अणु
	madd_op, maddu_op, mul_op, spec2_3_unused_op,
	msub_op, msubu_op, /* more unused ops */
	clz_op = 0x20, clo_op,
	dclz_op = 0x24, dclo_op,
	sdbpp_op = 0x3f
पूर्ण;

/*
 * func field of spec3 opcode.
 */
क्रमागत spec3_op अणु
	ext_op, dexपंचांग_op, dextu_op, dext_op,
	ins_op, dinsm_op, dinsu_op, dins_op,
	yield_op  = 0x09, lx_op     = 0x0a,
	lwle_op   = 0x19, lwre_op   = 0x1a,
	cachee_op = 0x1b, sbe_op    = 0x1c,
	she_op    = 0x1d, sce_op    = 0x1e,
	swe_op    = 0x1f, bshfl_op  = 0x20,
	swle_op   = 0x21, swre_op   = 0x22,
	prefe_op  = 0x23, dbshfl_op = 0x24,
	cache6_op = 0x25, sc6_op    = 0x26,
	scd6_op   = 0x27, lbue_op   = 0x28,
	lhue_op   = 0x29, lbe_op    = 0x2c,
	lhe_op    = 0x2d, lle_op    = 0x2e,
	lwe_op    = 0x2f, pref6_op  = 0x35,
	ll6_op    = 0x36, lld6_op   = 0x37,
	rdhwr_op  = 0x3b
पूर्ण;

/*
 * Bits 10-6 minor opcode क्रम r6 spec mult/भाग encodings
 */
क्रमागत mult_op अणु
	mult_mult_op = 0x0,
	mult_mul_op = 0x2,
	mult_muh_op = 0x3,
पूर्ण;
क्रमागत multu_op अणु
	multu_multu_op = 0x0,
	multu_mulu_op = 0x2,
	multu_muhu_op = 0x3,
पूर्ण;
क्रमागत भाग_op अणु
	भाग_भाग_op = 0x0,
	भाग_भाग6_op = 0x2,
	भाग_mod_op = 0x3,
पूर्ण;
क्रमागत भागu_op अणु
	भागu_भागu_op = 0x0,
	भागu_भागu6_op = 0x2,
	भागu_modu_op = 0x3,
पूर्ण;
क्रमागत dmult_op अणु
	dmult_dmult_op = 0x0,
	dmult_dmul_op = 0x2,
	dmult_dmuh_op = 0x3,
पूर्ण;
क्रमागत dmultu_op अणु
	dmultu_dmultu_op = 0x0,
	dmultu_dmulu_op = 0x2,
	dmultu_dmuhu_op = 0x3,
पूर्ण;
क्रमागत dभाग_op अणु
	dभाग_dभाग_op = 0x0,
	dभाग_dभाग6_op = 0x2,
	dभाग_dmod_op = 0x3,
पूर्ण;
क्रमागत dभागu_op अणु
	dभागu_dभागu_op = 0x0,
	dभागu_dभागu6_op = 0x2,
	dभागu_dmodu_op = 0x3,
पूर्ण;

/*
 * rt field of bcond opcodes.
 */
क्रमागत rt_op अणु
	bltz_op, bgez_op, bltzl_op, bgezl_op,
	spimi_op, unused_rt_op_0x05, unused_rt_op_0x06, unused_rt_op_0x07,
	tgei_op, tgeiu_op, tlti_op, tltiu_op,
	teqi_op, unused_0x0d_rt_op, tnei_op, unused_0x0f_rt_op,
	bltzal_op, bgezal_op, bltzall_op, bgezall_op,
	rt_op_0x14, rt_op_0x15, rt_op_0x16, rt_op_0x17,
	rt_op_0x18, rt_op_0x19, rt_op_0x1a, rt_op_0x1b,
	bposge32_op, rt_op_0x1d, rt_op_0x1e, synci_op
पूर्ण;

/*
 * rs field of cop opcodes.
 */
क्रमागत cop_op अणु
	mfc_op	      = 0x00, dmfc_op	    = 0x01,
	cfc_op	      = 0x02, mfhc0_op	    = 0x02,
	mfhc_op       = 0x03, mtc_op	    = 0x04,
	dmtc_op	      = 0x05, ctc_op	    = 0x06,
	mthc0_op      = 0x06, mthc_op	    = 0x07,
	bc_op	      = 0x08, bc1eqz_op     = 0x09,
	mfmc0_op      = 0x0b, bc1nez_op     = 0x0d,
	wrpgpr_op     = 0x0e, cop_op	    = 0x10,
	copm_op	      = 0x18
पूर्ण;

/*
 * rt field of cop.bc_op opcodes
 */
क्रमागत bcop_op अणु
	bcf_op, bct_op, bcfl_op, bctl_op
पूर्ण;

/*
 * func field of cop0 coi opcodes.
 */
क्रमागत cop0_coi_func अणु
	tlbr_op	      = 0x01, tlbwi_op	    = 0x02,
	tlbwr_op      = 0x06, tlbp_op	    = 0x08,
	rfe_op	      = 0x10, eret_op	    = 0x18,
	रुको_op       = 0x20, hypcall_op    = 0x28
पूर्ण;

/*
 * func field of cop0 com opcodes.
 */
क्रमागत cop0_com_func अणु
	tlbr1_op      = 0x01, tlbw_op	    = 0x02,
	tlbp1_op      = 0x08, dctr_op	    = 0x09,
	dctw_op	      = 0x0a
पूर्ण;

/*
 * fmt field of cop1 opcodes.
 */
क्रमागत cop1_fmt अणु
	s_fmt, d_fmt, e_fmt, q_fmt,
	w_fmt, l_fmt
पूर्ण;

/*
 * func field of cop1 inकाष्ठाions using d, s or w क्रमmat.
 */
क्रमागत cop1_sdw_func अणु
	fadd_op	     =	0x00, fsub_op	   =  0x01,
	fmul_op	     =	0x02, fभाग_op	   =  0x03,
	fवर्ग_मूल_op     =	0x04, भ_असल_op	   =  0x05,
	fmov_op	     =	0x06, fneg_op	   =  0x07,
	froundl_op   =	0x08, ftruncl_op   =  0x09,
	fउच्चमानl_op    =	0x0a, fन्यूनमानl_op   =  0x0b,
	fround_op    =	0x0c, ftrunc_op	   =  0x0d,
	fउच्चमान_op     =	0x0e, fन्यूनमान_op	   =  0x0f,
	fsel_op      =  0x10,
	fmovc_op     =	0x11, fmovz_op	   =  0x12,
	fmovn_op     =	0x13, fseleqz_op   =  0x14,
	frecip_op    =  0x15, frवर्ग_मूल_op    =  0x16,
	fselnez_op   =  0x17, fmaddf_op    =  0x18,
	fmsubf_op    =  0x19, frपूर्णांक_op     =  0x1a,
	fclass_op    =  0x1b, fmin_op      =  0x1c,
	fmina_op     =  0x1d, fmax_op      =  0x1e,
	fmaxa_op     =  0x1f, fcvts_op     =  0x20,
	fcvtd_op     =	0x21, fcvte_op	   =  0x22,
	fcvtw_op     =	0x24, fcvtl_op	   =  0x25,
	fcmp_op	     =	0x30
पूर्ण;

/*
 * func field of cop1x opcodes (MIPS IV).
 */
क्रमागत cop1x_func अणु
	lwxc1_op     =	0x00, ldxc1_op	   =  0x01,
	swxc1_op     =  0x08, sdxc1_op	   =  0x09,
	pfetch_op    =	0x0f, madd_s_op	   =  0x20,
	madd_d_op    =	0x21, madd_e_op	   =  0x22,
	msub_s_op    =	0x28, msub_d_op	   =  0x29,
	msub_e_op    =	0x2a, nmadd_s_op   =  0x30,
	nmadd_d_op   =	0x31, nmadd_e_op   =  0x32,
	nmsub_s_op   =	0x38, nmsub_d_op   =  0x39,
	nmsub_e_op   =	0x3a
पूर्ण;

/*
 * func field क्रम mad opcodes (MIPS IV).
 */
क्रमागत mad_func अणु
	madd_fp_op	= 0x08, msub_fp_op	= 0x0a,
	nmadd_fp_op	= 0x0c, nmsub_fp_op	= 0x0e
पूर्ण;

/*
 * func field क्रम page table walker (Loongson-3).
 */
क्रमागत ptw_func अणु
	lwdir_op = 0x00,
	lwpte_op = 0x01,
	lddir_op = 0x02,
	ldpte_op = 0x03,
पूर्ण;

/*
 * func field क्रम special3 lx opcodes (Cavium Octeon).
 */
क्रमागत lx_func अणु
	lwx_op	= 0x00,
	lhx_op	= 0x04,
	lbux_op = 0x06,
	ldx_op	= 0x08,
	lwux_op = 0x10,
	lhux_op = 0x14,
	lbx_op	= 0x16,
पूर्ण;

/*
 * BSHFL opcodes
 */
क्रमागत bshfl_func अणु
	wsbh_op = 0x2,
	seb_op  = 0x10,
	seh_op  = 0x18,
पूर्ण;

/*
 * DBSHFL opcodes
 */
क्रमागत dbshfl_func अणु
	dsbh_op = 0x2,
	dshd_op = 0x5,
पूर्ण;

/*
 * MSA minor opcodes.
 */
क्रमागत msa_func अणु
	msa_elm_op = 0x19,
पूर्ण;

/*
 * MSA ELM opcodes.
 */
क्रमागत msa_elm अणु
	msa_ctc_op = 0x3e,
	msa_cfc_op = 0x7e,
पूर्ण;

/*
 * func field क्रम MSA MI10 क्रमmat.
 */
क्रमागत msa_mi10_func अणु
	msa_ld_op = 8,
	msa_st_op = 9,
पूर्ण;

/*
 * MSA 2 bit क्रमmat fields.
 */
क्रमागत msa_2b_fmt अणु
	msa_fmt_b = 0,
	msa_fmt_h = 1,
	msa_fmt_w = 2,
	msa_fmt_d = 3,
पूर्ण;

/*
 * (microMIPS) Major opcodes.
 */
क्रमागत mm_major_op अणु
	mm_pool32a_op, mm_pool16a_op, mm_lbu16_op, mm_move16_op,
	mm_addi32_op, mm_lbu32_op, mm_sb32_op, mm_lb32_op,
	mm_pool32b_op, mm_pool16b_op, mm_lhu16_op, mm_andi16_op,
	mm_addiu32_op, mm_lhu32_op, mm_sh32_op, mm_lh32_op,
	mm_pool32i_op, mm_pool16c_op, mm_lwsp16_op, mm_pool16d_op,
	mm_ori32_op, mm_pool32f_op, mm_pool32s_op, mm_reserved2_op,
	mm_pool32c_op, mm_lwgp16_op, mm_lw16_op, mm_pool16e_op,
	mm_xori32_op, mm_jals32_op, mm_addiupc_op, mm_reserved3_op,
	mm_reserved4_op, mm_pool16f_op, mm_sb16_op, mm_beqz16_op,
	mm_slti32_op, mm_beq32_op, mm_swc132_op, mm_lwc132_op,
	mm_reserved5_op, mm_reserved6_op, mm_sh16_op, mm_bnez16_op,
	mm_sltiu32_op, mm_bne32_op, mm_sdc132_op, mm_ldc132_op,
	mm_reserved7_op, mm_reserved8_op, mm_swsp16_op, mm_b16_op,
	mm_andi32_op, mm_j32_op, mm_sd32_op, mm_ld32_op,
	mm_reserved11_op, mm_reserved12_op, mm_sw16_op, mm_li16_op,
	mm_jalx32_op, mm_jal32_op, mm_sw32_op, mm_lw32_op,
पूर्ण;

/*
 * (microMIPS) POOL32I minor opcodes.
 */
क्रमागत mm_32i_minor_op अणु
	mm_bltz_op, mm_bltzal_op, mm_bgez_op, mm_bgezal_op,
	mm_blez_op, mm_bnezc_op, mm_bgtz_op, mm_beqzc_op,
	mm_tlti_op, mm_tgei_op, mm_tltiu_op, mm_tgeiu_op,
	mm_tnei_op, mm_lui_op, mm_teqi_op, mm_reserved13_op,
	mm_synci_op, mm_bltzals_op, mm_reserved14_op, mm_bgezals_op,
	mm_bc2f_op, mm_bc2t_op, mm_reserved15_op, mm_reserved16_op,
	mm_reserved17_op, mm_reserved18_op, mm_bposge64_op, mm_bposge32_op,
	mm_bc1f_op, mm_bc1t_op, mm_reserved19_op, mm_reserved20_op,
	mm_bc1any2f_op, mm_bc1any2t_op, mm_bc1any4f_op, mm_bc1any4t_op,
पूर्ण;

/*
 * (microMIPS) POOL32A minor opcodes.
 */
क्रमागत mm_32a_minor_op अणु
	mm_sll32_op = 0x000,
	mm_ins_op = 0x00c,
	mm_sllv32_op = 0x010,
	mm_ext_op = 0x02c,
	mm_pool32axf_op = 0x03c,
	mm_srl32_op = 0x040,
	mm_srlv32_op = 0x050,
	mm_sra_op = 0x080,
	mm_srav_op = 0x090,
	mm_rotr_op = 0x0c0,
	mm_lwxs_op = 0x118,
	mm_addu32_op = 0x150,
	mm_subu32_op = 0x1d0,
	mm_wsbh_op = 0x1ec,
	mm_mul_op = 0x210,
	mm_and_op = 0x250,
	mm_or32_op = 0x290,
	mm_xor32_op = 0x310,
	mm_slt_op = 0x350,
	mm_sltu_op = 0x390,
पूर्ण;

/*
 * (microMIPS) POOL32B functions.
 */
क्रमागत mm_32b_func अणु
	mm_lwc2_func = 0x0,
	mm_lwp_func = 0x1,
	mm_ldc2_func = 0x2,
	mm_ldp_func = 0x4,
	mm_lwm32_func = 0x5,
	mm_cache_func = 0x6,
	mm_ldm_func = 0x7,
	mm_swc2_func = 0x8,
	mm_swp_func = 0x9,
	mm_sdc2_func = 0xa,
	mm_sdp_func = 0xc,
	mm_swm32_func = 0xd,
	mm_sdm_func = 0xf,
पूर्ण;

/*
 * (microMIPS) POOL32C functions.
 */
क्रमागत mm_32c_func अणु
	mm_pref_func = 0x2,
	mm_ll_func = 0x3,
	mm_swr_func = 0x9,
	mm_sc_func = 0xb,
	mm_lwu_func = 0xe,
पूर्ण;

/*
 * (microMIPS) POOL32AXF minor opcodes.
 */
क्रमागत mm_32axf_minor_op अणु
	mm_mfc0_op = 0x003,
	mm_mtc0_op = 0x00b,
	mm_tlbp_op = 0x00d,
	mm_mfhi32_op = 0x035,
	mm_jalr_op = 0x03c,
	mm_tlbr_op = 0x04d,
	mm_mflo32_op = 0x075,
	mm_jalrhb_op = 0x07c,
	mm_tlbwi_op = 0x08d,
	mm_mthi32_op = 0x0b5,
	mm_tlbwr_op = 0x0cd,
	mm_mtlo32_op = 0x0f5,
	mm_di_op = 0x11d,
	mm_jalrs_op = 0x13c,
	mm_jalrshb_op = 0x17c,
	mm_sync_op = 0x1ad,
	mm_syscall_op = 0x22d,
	mm_रुको_op = 0x24d,
	mm_eret_op = 0x3cd,
	mm_भागu_op = 0x5dc,
पूर्ण;

/*
 * (microMIPS) POOL32F minor opcodes.
 */
क्रमागत mm_32f_minor_op अणु
	mm_32f_00_op = 0x00,
	mm_32f_01_op = 0x01,
	mm_32f_02_op = 0x02,
	mm_32f_10_op = 0x08,
	mm_32f_11_op = 0x09,
	mm_32f_12_op = 0x0a,
	mm_32f_20_op = 0x10,
	mm_32f_30_op = 0x18,
	mm_32f_40_op = 0x20,
	mm_32f_41_op = 0x21,
	mm_32f_42_op = 0x22,
	mm_32f_50_op = 0x28,
	mm_32f_51_op = 0x29,
	mm_32f_52_op = 0x2a,
	mm_32f_60_op = 0x30,
	mm_32f_70_op = 0x38,
	mm_32f_73_op = 0x3b,
	mm_32f_74_op = 0x3c,
पूर्ण;

/*
 * (microMIPS) POOL32F secondary minor opcodes.
 */
क्रमागत mm_32f_10_minor_op अणु
	mm_lwxc1_op = 0x1,
	mm_swxc1_op,
	mm_ldxc1_op,
	mm_sdxc1_op,
	mm_luxc1_op,
	mm_suxc1_op,
पूर्ण;

क्रमागत mm_32f_func अणु
	mm_lwxc1_func = 0x048,
	mm_swxc1_func = 0x088,
	mm_ldxc1_func = 0x0c8,
	mm_sdxc1_func = 0x108,
पूर्ण;

/*
 * (microMIPS) POOL32F secondary minor opcodes.
 */
क्रमागत mm_32f_40_minor_op अणु
	mm_fmovf_op,
	mm_fmovt_op,
पूर्ण;

/*
 * (microMIPS) POOL32F secondary minor opcodes.
 */
क्रमागत mm_32f_60_minor_op अणु
	mm_fadd_op,
	mm_fsub_op,
	mm_fmul_op,
	mm_fभाग_op,
पूर्ण;

/*
 * (microMIPS) POOL32F secondary minor opcodes.
 */
क्रमागत mm_32f_70_minor_op अणु
	mm_fmovn_op,
	mm_fmovz_op,
पूर्ण;

/*
 * (microMIPS) POOL32FXF secondary minor opcodes क्रम POOL32F.
 */
क्रमागत mm_32f_73_minor_op अणु
	mm_fmov0_op = 0x01,
	mm_fcvtl_op = 0x04,
	mm_movf0_op = 0x05,
	mm_frवर्ग_मूल_op = 0x08,
	mm_fन्यूनमानl_op = 0x0c,
	mm_भ_असल0_op = 0x0d,
	mm_fcvtw_op = 0x24,
	mm_movt0_op = 0x25,
	mm_fवर्ग_मूल_op = 0x28,
	mm_fन्यूनमानw_op = 0x2c,
	mm_fneg0_op = 0x2d,
	mm_cfc1_op = 0x40,
	mm_frecip_op = 0x48,
	mm_fउच्चमानl_op = 0x4c,
	mm_fcvtd0_op = 0x4d,
	mm_ctc1_op = 0x60,
	mm_fउच्चमानw_op = 0x6c,
	mm_fcvts0_op = 0x6d,
	mm_mfc1_op = 0x80,
	mm_fmov1_op = 0x81,
	mm_movf1_op = 0x85,
	mm_ftruncl_op = 0x8c,
	mm_भ_असल1_op = 0x8d,
	mm_mtc1_op = 0xa0,
	mm_movt1_op = 0xa5,
	mm_ftruncw_op = 0xac,
	mm_fneg1_op = 0xad,
	mm_mfhc1_op = 0xc0,
	mm_froundl_op = 0xcc,
	mm_fcvtd1_op = 0xcd,
	mm_mthc1_op = 0xe0,
	mm_froundw_op = 0xec,
	mm_fcvts1_op = 0xed,
पूर्ण;

/*
 * (microMIPS) POOL32S minor opcodes.
 */
क्रमागत mm_32s_minor_op अणु
	mm_32s_elm_op = 0x16,
पूर्ण;

/*
 * (microMIPS) POOL16C minor opcodes.
 */
क्रमागत mm_16c_minor_op अणु
	mm_lwm16_op = 0x04,
	mm_swm16_op = 0x05,
	mm_jr16_op = 0x0c,
	mm_jrc_op = 0x0d,
	mm_jalr16_op = 0x0e,
	mm_jalrs16_op = 0x0f,
	mm_jraddiusp_op = 0x18,
पूर्ण;

/*
 * (microMIPS) POOL16D minor opcodes.
 */
क्रमागत mm_16d_minor_op अणु
	mm_addius5_func,
	mm_addiusp_func,
पूर्ण;

/*
 * (MIPS16e) opcodes.
 */
क्रमागत MIPS16e_ops अणु
	MIPS16e_jal_op = 003,
	MIPS16e_ld_op = 007,
	MIPS16e_i8_op = 014,
	MIPS16e_sd_op = 017,
	MIPS16e_lb_op = 020,
	MIPS16e_lh_op = 021,
	MIPS16e_lwsp_op = 022,
	MIPS16e_lw_op = 023,
	MIPS16e_lbu_op = 024,
	MIPS16e_lhu_op = 025,
	MIPS16e_lwpc_op = 026,
	MIPS16e_lwu_op = 027,
	MIPS16e_sb_op = 030,
	MIPS16e_sh_op = 031,
	MIPS16e_swsp_op = 032,
	MIPS16e_sw_op = 033,
	MIPS16e_rr_op = 035,
	MIPS16e_extend_op = 036,
	MIPS16e_i64_op = 037,
पूर्ण;

क्रमागत MIPS16e_i64_func अणु
	MIPS16e_ldsp_func,
	MIPS16e_sdsp_func,
	MIPS16e_sdrasp_func,
	MIPS16e_dadjsp_func,
	MIPS16e_ldpc_func,
पूर्ण;

क्रमागत MIPS16e_rr_func अणु
	MIPS16e_jr_func,
पूर्ण;

क्रमागत MIPS6e_i8_func अणु
	MIPS16e_swrasp_func = 02,
पूर्ण;

/*
 * (microMIPS) NOP inकाष्ठाion.
 */
#घोषणा MM_NOP16	0x0c00

काष्ठा j_क्रमmat अणु
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6, /* Jump क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक target : 26,
	;))
पूर्ण;

काष्ठा i_क्रमmat अणु			/* चिन्हित immediate क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(चिन्हित पूर्णांक simmediate : 16,
	;))))
पूर्ण;

काष्ठा u_क्रमmat अणु			/* अचिन्हित immediate क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक uimmediate : 16,
	;))))
पूर्ण;

काष्ठा c_क्रमmat अणु			/* Cache (>= R6000) क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक c_op : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक cache : 2,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक simmediate : 16,
	;)))))
पूर्ण;

काष्ठा r_क्रमmat अणु			/* Register क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक re : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

काष्ठा c0r_क्रमmat अणु			/* C0 रेजिस्टर क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक z: 8,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक sel : 3,
	;))))))
पूर्ण;

काष्ठा mfmc0_क्रमmat अणु			/* MFMC0 रेजिस्टर क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक re : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक sc : 1,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक : 2,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक sel : 3,
	;))))))))
पूर्ण;

काष्ठा co_क्रमmat अणु			/* C0 CO क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक co : 1,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक code : 19,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))
पूर्ण;

काष्ठा p_क्रमmat अणु		/* Perक्रमmance counter क्रमmat (R10000) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक re : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

काष्ठा f_क्रमmat अणु			/* FPU रेजिस्टर क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक : 1,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fmt : 4,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक re : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;)))))))
पूर्ण;

काष्ठा ma_क्रमmat अणु		/* FPU multiply and add क्रमmat (MIPS IV) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fr : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक ft : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 4,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fmt : 2,
	;)))))))
पूर्ण;

काष्ठा b_क्रमmat अणु			/* BREAK and SYSCALL */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक code : 20,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;)))
पूर्ण;

काष्ठा ps_क्रमmat अणु			/* MIPS-3D / paired single क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक ft : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

काष्ठा v_क्रमmat अणु				/* MDMX vector क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक sel : 4,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fmt : 1,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक vt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक vs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक vd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;)))))))
पूर्ण;

काष्ठा msa_mi10_क्रमmat अणु		/* MSA MI10 */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(चिन्हित पूर्णांक s10 : 10,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक wd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 4,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक df : 2,
	;))))))
पूर्ण;

काष्ठा dsp_क्रमmat अणु		/* SPEC3 DSP क्रमmat inकाष्ठाions */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक base : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक index : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक op : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

काष्ठा spec3_क्रमmat अणु   /* SPEC3 */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode:6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs:5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt:5,
	__BITFIELD_FIELD(चिन्हित पूर्णांक simmediate:9,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func:7,
	;)))))
पूर्ण;

/*
 * microMIPS inकाष्ठाion क्रमmats (32-bit length)
 *
 * NOTE:
 *	Parenthesis denote whether the क्रमmat is a microMIPS inकाष्ठाion or
 *	अगर it is MIPS32 inकाष्ठाion re-encoded क्रम use in the microMIPS ASE.
 */
काष्ठा fb_क्रमmat अणु		/* FPU branch क्रमmat (MIPS32) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक bc : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक cc : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक flag : 2,
	__BITFIELD_FIELD(चिन्हित पूर्णांक simmediate : 16,
	;)))))
पूर्ण;

काष्ठा fp0_क्रमmat अणु		/* FPU multiply and add क्रमmat (MIPS32) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fmt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक ft : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

काष्ठा mm_fp0_क्रमmat अणु		/* FPU multiply and add क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक ft : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fmt : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक op : 2,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;)))))))
पूर्ण;

काष्ठा fp1_क्रमmat अणु		/* FPU mfc1 and cfc1 क्रमmat (MIPS32) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक op : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

काष्ठा mm_fp1_क्रमmat अणु		/* FPU mfc1 and cfc1 क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fmt : 2,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक op : 8,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

काष्ठा mm_fp2_क्रमmat अणु		/* FPU movt and movf क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक cc : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक zero : 2,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fmt : 2,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक op : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))))
पूर्ण;

काष्ठा mm_fp3_क्रमmat अणु		/* FPU असल and neg क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fmt : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक op : 7,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

काष्ठा mm_fp4_क्रमmat अणु		/* FPU c.cond क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक cc : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fmt : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक cond : 4,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;)))))))
पूर्ण;

काष्ठा mm_fp5_क्रमmat अणु		/* FPU lwxc1 and swxc1 क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक index : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक base : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक op : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

काष्ठा fp6_क्रमmat अणु		/* FPU madd and msub क्रमmat (MIPS IV) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fr : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक ft : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

काष्ठा mm_fp6_क्रमmat अणु		/* FPU madd and msub क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक ft : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fr : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

काष्ठा mm_i_क्रमmat अणु		/* Immediate क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 5,
	__BITFIELD_FIELD(चिन्हित पूर्णांक simmediate : 16,
	;))))
पूर्ण;

काष्ठा mm_m_क्रमmat अणु		/* Multi-word load/store क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक base : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 4,
	__BITFIELD_FIELD(चिन्हित पूर्णांक simmediate : 12,
	;)))))
पूर्ण;

काष्ठा mm_x_क्रमmat अणु		/* Scaled indexed load क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक index : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक base : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 11,
	;)))))
पूर्ण;

काष्ठा mm_a_क्रमmat अणु		/* ADDIUPC क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 3,
	__BITFIELD_FIELD(चिन्हित पूर्णांक simmediate : 23,
	;)))
पूर्ण;

/*
 * microMIPS inकाष्ठाion क्रमmats (16-bit length)
 */
काष्ठा mm_b0_क्रमmat अणु		/* Unconditional branch क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(चिन्हित पूर्णांक simmediate : 10,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक : 16, /* Ignored */
	;)))
पूर्ण;

काष्ठा mm_b1_क्रमmat अणु		/* Conditional branch क्रमmat (microMIPS) */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 3,
	__BITFIELD_FIELD(चिन्हित पूर्णांक simmediate : 7,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक : 16, /* Ignored */
	;))))
पूर्ण;

काष्ठा mm16_m_क्रमmat अणु		/* Multi-word load/store क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 4,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rlist : 2,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक imm : 4,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक : 16, /* Ignored */
	;)))))
पूर्ण;

काष्ठा mm16_rb_क्रमmat अणु		/* Signed immediate क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक base : 3,
	__BITFIELD_FIELD(चिन्हित पूर्णांक simmediate : 4,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक : 16, /* Ignored */
	;)))))
पूर्ण;

काष्ठा mm16_r3_क्रमmat अणु		/* Load from global poपूर्णांकer क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 3,
	__BITFIELD_FIELD(चिन्हित पूर्णांक simmediate : 7,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक : 16, /* Ignored */
	;))))
पूर्ण;

काष्ठा mm16_r5_क्रमmat अणु		/* Load/store from stack poपूर्णांकer क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक imm : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक : 16, /* Ignored */
	;))))
पूर्ण;

/*
 * Loongson-3 overridden COP2 inकाष्ठाion क्रमmats (32-bit length)
 */
काष्ठा loongson3_lswc2_क्रमmat अणु	/* Loongson-3 overridden lwc2/swc2 Load/Store क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक base : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fr : 1,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक offset : 9,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक ls : 1,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rq : 5,
	;)))))))
पूर्ण;

काष्ठा loongson3_lsdc2_क्रमmat अणु	/* Loongson-3 overridden ldc2/sdc2 Load/Store क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक base : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rt : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक index : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक offset : 8,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode1 : 3,
	;))))))
पूर्ण;

काष्ठा loongson3_lscsr_क्रमmat अणु	/* Loongson-3 CPUCFG&CSR पढ़ो/ग_लिखो क्रमmat */
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 6,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rs : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fr : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक fd : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 6,
	;))))))
पूर्ण;

/*
 * MIPS16e inकाष्ठाion क्रमmats (16-bit length)
 */
काष्ठा m16e_rr अणु
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rx : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक nd : 1,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक l : 1,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक ra : 1,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 5,
	;))))))
पूर्ण;

काष्ठा m16e_jal अणु
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक x : 1,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक imm20_16 : 5,
	__BITFIELD_FIELD(चिन्हित पूर्णांक imm25_21 : 5,
	;))))
पूर्ण;

काष्ठा m16e_i64 अणु
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक imm : 8,
	;)))
पूर्ण;

काष्ठा m16e_ri64 अणु
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक ry : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक imm : 5,
	;))))
पूर्ण;

काष्ठा m16e_ri अणु
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rx : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक imm : 8,
	;)))
पूर्ण;

काष्ठा m16e_rri अणु
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक rx : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक ry : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक imm : 5,
	;))))
पूर्ण;

काष्ठा m16e_i8 अणु
	__BITFIELD_FIELD(अचिन्हित पूर्णांक opcode : 5,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक func : 3,
	__BITFIELD_FIELD(अचिन्हित पूर्णांक imm : 8,
	;)))
पूर्ण;

जोड़ mips_inकाष्ठाion अणु
	अचिन्हित पूर्णांक word;
	अचिन्हित लघु halfword[2];
	अचिन्हित अक्षर byte[4];
	काष्ठा j_क्रमmat j_क्रमmat;
	काष्ठा i_क्रमmat i_क्रमmat;
	काष्ठा u_क्रमmat u_क्रमmat;
	काष्ठा c_क्रमmat c_क्रमmat;
	काष्ठा r_क्रमmat r_क्रमmat;
	काष्ठा c0r_क्रमmat c0r_क्रमmat;
	काष्ठा mfmc0_क्रमmat mfmc0_क्रमmat;
	काष्ठा co_क्रमmat co_क्रमmat;
	काष्ठा p_क्रमmat p_क्रमmat;
	काष्ठा f_क्रमmat f_क्रमmat;
	काष्ठा ma_क्रमmat ma_क्रमmat;
	काष्ठा msa_mi10_क्रमmat msa_mi10_क्रमmat;
	काष्ठा b_क्रमmat b_क्रमmat;
	काष्ठा ps_क्रमmat ps_क्रमmat;
	काष्ठा v_क्रमmat v_क्रमmat;
	काष्ठा dsp_क्रमmat dsp_क्रमmat;
	काष्ठा spec3_क्रमmat spec3_क्रमmat;
	काष्ठा fb_क्रमmat fb_क्रमmat;
	काष्ठा fp0_क्रमmat fp0_क्रमmat;
	काष्ठा mm_fp0_क्रमmat mm_fp0_क्रमmat;
	काष्ठा fp1_क्रमmat fp1_क्रमmat;
	काष्ठा mm_fp1_क्रमmat mm_fp1_क्रमmat;
	काष्ठा mm_fp2_क्रमmat mm_fp2_क्रमmat;
	काष्ठा mm_fp3_क्रमmat mm_fp3_क्रमmat;
	काष्ठा mm_fp4_क्रमmat mm_fp4_क्रमmat;
	काष्ठा mm_fp5_क्रमmat mm_fp5_क्रमmat;
	काष्ठा fp6_क्रमmat fp6_क्रमmat;
	काष्ठा mm_fp6_क्रमmat mm_fp6_क्रमmat;
	काष्ठा mm_i_क्रमmat mm_i_क्रमmat;
	काष्ठा mm_m_क्रमmat mm_m_क्रमmat;
	काष्ठा mm_x_क्रमmat mm_x_क्रमmat;
	काष्ठा mm_a_क्रमmat mm_a_क्रमmat;
	काष्ठा mm_b0_क्रमmat mm_b0_क्रमmat;
	काष्ठा mm_b1_क्रमmat mm_b1_क्रमmat;
	काष्ठा mm16_m_क्रमmat mm16_m_क्रमmat ;
	काष्ठा mm16_rb_क्रमmat mm16_rb_क्रमmat;
	काष्ठा mm16_r3_क्रमmat mm16_r3_क्रमmat;
	काष्ठा mm16_r5_क्रमmat mm16_r5_क्रमmat;
	काष्ठा loongson3_lswc2_क्रमmat loongson3_lswc2_क्रमmat;
	काष्ठा loongson3_lsdc2_क्रमmat loongson3_lsdc2_क्रमmat;
	काष्ठा loongson3_lscsr_क्रमmat loongson3_lscsr_क्रमmat;
पूर्ण;

जोड़ mips16e_inकाष्ठाion अणु
	अचिन्हित पूर्णांक full : 16;
	काष्ठा m16e_rr rr;
	काष्ठा m16e_jal jal;
	काष्ठा m16e_i64 i64;
	काष्ठा m16e_ri64 ri64;
	काष्ठा m16e_ri ri;
	काष्ठा m16e_rri rri;
	काष्ठा m16e_i8 i8;
पूर्ण;

#पूर्ण_अगर /* _UAPI_ASM_INST_H */
