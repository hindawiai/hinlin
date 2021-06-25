<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * FPU data काष्ठाures:
 */
#अगर_अघोषित _ASM_X86_FPU_H
#घोषणा _ASM_X86_FPU_H

/*
 * The legacy x87 FPU state क्रमmat, as saved by FSAVE and
 * restored by the FRSTOR inकाष्ठाions:
 */
काष्ठा fregs_state अणु
	u32			cwd;	/* FPU Control Word		*/
	u32			swd;	/* FPU Status Word		*/
	u32			twd;	/* FPU Tag Word			*/
	u32			fip;	/* FPU IP Offset		*/
	u32			fcs;	/* FPU IP Selector		*/
	u32			foo;	/* FPU Opeअक्रम Poपूर्णांकer Offset	*/
	u32			fos;	/* FPU Opeअक्रम Poपूर्णांकer Selector	*/

	/* 8*10 bytes क्रम each FP-reg = 80 bytes:			*/
	u32			st_space[20];

	/* Software status inक्रमmation [not touched by FSAVE]:		*/
	u32			status;
पूर्ण;

/*
 * The legacy fx SSE/MMX FPU state क्रमmat, as saved by FXSAVE and
 * restored by the FXRSTOR inकाष्ठाions. It's similar to the FSAVE
 * क्रमmat, but dअगरfers in some areas, plus has extensions at
 * the end क्रम the XMM रेजिस्टरs.
 */
काष्ठा fxregs_state अणु
	u16			cwd; /* Control Word			*/
	u16			swd; /* Status Word			*/
	u16			twd; /* Tag Word			*/
	u16			fop; /* Last Inकाष्ठाion Opcode		*/
	जोड़ अणु
		काष्ठा अणु
			u64	rip; /* Inकाष्ठाion Poपूर्णांकer		*/
			u64	rdp; /* Data Poपूर्णांकer			*/
		पूर्ण;
		काष्ठा अणु
			u32	fip; /* FPU IP Offset			*/
			u32	fcs; /* FPU IP Selector			*/
			u32	foo; /* FPU Opeअक्रम Offset		*/
			u32	fos; /* FPU Opeअक्रम Selector		*/
		पूर्ण;
	पूर्ण;
	u32			mxcsr;		/* MXCSR Register State */
	u32			mxcsr_mask;	/* MXCSR Mask		*/

	/* 8*16 bytes क्रम each FP-reg = 128 bytes:			*/
	u32			st_space[32];

	/* 16*16 bytes क्रम each XMM-reg = 256 bytes:			*/
	u32			xmm_space[64];

	u32			padding[12];

	जोड़ अणु
		u32		padding1[12];
		u32		sw_reserved[12];
	पूर्ण;

पूर्ण __attribute__((aligned(16)));

/* Default value क्रम fxregs_state.mxcsr: */
#घोषणा MXCSR_DEFAULT		0x1f80

/* Copy both mxcsr & mxcsr_flags with a single u64 स_नकल: */
#घोषणा MXCSR_AND_FLAGS_SIZE माप(u64)

/*
 * Software based FPU emulation state. This is arbitrary really,
 * it matches the x87 क्रमmat to make it easier to understand:
 */
काष्ठा swregs_state अणु
	u32			cwd;
	u32			swd;
	u32			twd;
	u32			fip;
	u32			fcs;
	u32			foo;
	u32			fos;
	/* 8*10 bytes क्रम each FP-reg = 80 bytes: */
	u32			st_space[20];
	u8			ftop;
	u8			changed;
	u8			lookahead;
	u8			no_update;
	u8			rm;
	u8			alimit;
	काष्ठा math_emu_info	*info;
	u32			entry_eip;
पूर्ण;

/*
 * List of XSAVE features Linux knows about:
 */
क्रमागत xfeature अणु
	XFEATURE_FP,
	XFEATURE_SSE,
	/*
	 * Values above here are "legacy states".
	 * Those below are "extended states".
	 */
	XFEATURE_YMM,
	XFEATURE_BNDREGS,
	XFEATURE_BNDCSR,
	XFEATURE_OPMASK,
	XFEATURE_ZMM_Hi256,
	XFEATURE_Hi16_ZMM,
	XFEATURE_PT_UNIMPLEMENTED_SO_FAR,
	XFEATURE_PKRU,
	XFEATURE_PASID,
	XFEATURE_RSRVD_COMP_11,
	XFEATURE_RSRVD_COMP_12,
	XFEATURE_RSRVD_COMP_13,
	XFEATURE_RSRVD_COMP_14,
	XFEATURE_LBR,

	XFEATURE_MAX,
पूर्ण;

#घोषणा XFEATURE_MASK_FP		(1 << XFEATURE_FP)
#घोषणा XFEATURE_MASK_SSE		(1 << XFEATURE_SSE)
#घोषणा XFEATURE_MASK_YMM		(1 << XFEATURE_YMM)
#घोषणा XFEATURE_MASK_BNDREGS		(1 << XFEATURE_BNDREGS)
#घोषणा XFEATURE_MASK_BNDCSR		(1 << XFEATURE_BNDCSR)
#घोषणा XFEATURE_MASK_OPMASK		(1 << XFEATURE_OPMASK)
#घोषणा XFEATURE_MASK_ZMM_Hi256		(1 << XFEATURE_ZMM_Hi256)
#घोषणा XFEATURE_MASK_Hi16_ZMM		(1 << XFEATURE_Hi16_ZMM)
#घोषणा XFEATURE_MASK_PT		(1 << XFEATURE_PT_UNIMPLEMENTED_SO_FAR)
#घोषणा XFEATURE_MASK_PKRU		(1 << XFEATURE_PKRU)
#घोषणा XFEATURE_MASK_PASID		(1 << XFEATURE_PASID)
#घोषणा XFEATURE_MASK_LBR		(1 << XFEATURE_LBR)

#घोषणा XFEATURE_MASK_FPSSE		(XFEATURE_MASK_FP | XFEATURE_MASK_SSE)
#घोषणा XFEATURE_MASK_AVX512		(XFEATURE_MASK_OPMASK \
					 | XFEATURE_MASK_ZMM_Hi256 \
					 | XFEATURE_MASK_Hi16_ZMM)

#घोषणा FIRST_EXTENDED_XFEATURE	XFEATURE_YMM

काष्ठा reg_128_bit अणु
	u8      regbytes[128/8];
पूर्ण;
काष्ठा reg_256_bit अणु
	u8	regbytes[256/8];
पूर्ण;
काष्ठा reg_512_bit अणु
	u8	regbytes[512/8];
पूर्ण;

/*
 * State component 2:
 *
 * There are 16x 256-bit AVX रेजिस्टरs named YMM0-YMM15.
 * The low 128 bits are aliased to the 16 SSE रेजिस्टरs (XMM0-XMM15)
 * and are stored in 'struct fxregs_state::xmm_space[]' in the
 * "legacy" area.
 *
 * The high 128 bits are stored here.
 */
काष्ठा ymmh_काष्ठा अणु
	काष्ठा reg_128_bit              hi_ymm[16];
पूर्ण __packed;

/* Intel MPX support: */

काष्ठा mpx_bndreg अणु
	u64				lower_bound;
	u64				upper_bound;
पूर्ण __packed;
/*
 * State component 3 is used क्रम the 4 128-bit bounds रेजिस्टरs
 */
काष्ठा mpx_bndreg_state अणु
	काष्ठा mpx_bndreg		bndreg[4];
पूर्ण __packed;

/*
 * State component 4 is used क्रम the 64-bit user-mode MPX
 * configuration रेजिस्टर BNDCFGU and the 64-bit MPX status
 * रेजिस्टर BNDSTATUS.  We call the pair "BNDCSR".
 */
काष्ठा mpx_bndcsr अणु
	u64				bndcfgu;
	u64				bndstatus;
पूर्ण __packed;

/*
 * The BNDCSR state is padded out to be 64-bytes in size.
 */
काष्ठा mpx_bndcsr_state अणु
	जोड़ अणु
		काष्ठा mpx_bndcsr		bndcsr;
		u8				pad_to_64_bytes[64];
	पूर्ण;
पूर्ण __packed;

/* AVX-512 Components: */

/*
 * State component 5 is used क्रम the 8 64-bit opmask रेजिस्टरs
 * k0-k7 (opmask state).
 */
काष्ठा avx_512_opmask_state अणु
	u64				opmask_reg[8];
पूर्ण __packed;

/*
 * State component 6 is used क्रम the upper 256 bits of the
 * रेजिस्टरs ZMM0-ZMM15. These 16 256-bit values are denoted
 * ZMM0_H-ZMM15_H (ZMM_Hi256 state).
 */
काष्ठा avx_512_zmm_uppers_state अणु
	काष्ठा reg_256_bit		zmm_upper[16];
पूर्ण __packed;

/*
 * State component 7 is used क्रम the 16 512-bit रेजिस्टरs
 * ZMM16-ZMM31 (Hi16_ZMM state).
 */
काष्ठा avx_512_hi16_state अणु
	काष्ठा reg_512_bit		hi16_zmm[16];
पूर्ण __packed;

/*
 * State component 9: 32-bit PKRU रेजिस्टर.  The state is
 * 8 bytes दीर्घ but only 4 bytes is used currently.
 */
काष्ठा pkru_state अणु
	u32				pkru;
	u32				pad;
पूर्ण __packed;

/*
 * State component 15: Architectural LBR configuration state.
 * The size of Arch LBR state depends on the number of LBRs (lbr_depth).
 */

काष्ठा lbr_entry अणु
	u64 from;
	u64 to;
	u64 info;
पूर्ण;

काष्ठा arch_lbr_state अणु
	u64 lbr_ctl;
	u64 lbr_depth;
	u64 ler_from;
	u64 ler_to;
	u64 ler_info;
	काष्ठा lbr_entry		entries[];
पूर्ण __packed;

/*
 * State component 10 is supervisor state used क्रम context-चयनing the
 * PASID state.
 */
काष्ठा ia32_pasid_state अणु
	u64 pasid;
पूर्ण __packed;

काष्ठा xstate_header अणु
	u64				xfeatures;
	u64				xcomp_bv;
	u64				reserved[6];
पूर्ण __attribute__((packed));

/*
 * xstate_header.xcomp_bv[63] indicates that the extended_state_area
 * is in compacted क्रमmat.
 */
#घोषणा XCOMP_BV_COMPACTED_FORMAT ((u64)1 << 63)

/*
 * This is our most modern FPU state क्रमmat, as saved by the XSAVE
 * and restored by the XRSTOR inकाष्ठाions.
 *
 * It consists of a legacy fxregs portion, an xstate header and
 * subsequent areas as defined by the xstate header.  Not all CPUs
 * support all the extensions, so the size of the extended area
 * can vary quite a bit between CPUs.
 */
काष्ठा xregs_state अणु
	काष्ठा fxregs_state		i387;
	काष्ठा xstate_header		header;
	u8				extended_state_area[0];
पूर्ण __attribute__ ((packed, aligned (64)));

/*
 * This is a जोड़ of all the possible FPU state क्रमmats
 * put together, so that we can pick the right one runसमय.
 *
 * The size of the काष्ठाure is determined by the largest
 * member - which is the xsave area.  The padding is there
 * to ensure that अटलally-allocated task_काष्ठाs (just
 * the init_task today) have enough space.
 */
जोड़ fpregs_state अणु
	काष्ठा fregs_state		fsave;
	काष्ठा fxregs_state		fxsave;
	काष्ठा swregs_state		soft;
	काष्ठा xregs_state		xsave;
	u8 __padding[PAGE_SIZE];
पूर्ण;

/*
 * Highest level per task FPU state data काष्ठाure that
 * contains the FPU रेजिस्टर state plus various FPU
 * state fields:
 */
काष्ठा fpu अणु
	/*
	 * @last_cpu:
	 *
	 * Records the last CPU on which this context was loaded पूर्णांकo
	 * FPU रेजिस्टरs. (In the lazy-restore हाल we might be
	 * able to reuse FPU रेजिस्टरs across multiple context चयनes
	 * this way, अगर no पूर्णांकermediate task used the FPU.)
	 *
	 * A value of -1 is used to indicate that the FPU state in context
	 * memory is newer than the FPU state in रेजिस्टरs, and that the
	 * FPU state should be reloaded next समय the task is run.
	 */
	अचिन्हित पूर्णांक			last_cpu;

	/*
	 * @avx512_बारtamp:
	 *
	 * Records the बारtamp of AVX512 use during last context चयन.
	 */
	अचिन्हित दीर्घ			avx512_बारtamp;

	/*
	 * @state:
	 *
	 * In-memory copy of all FPU रेजिस्टरs that we save/restore
	 * over context चयनes. If the task is using the FPU then
	 * the रेजिस्टरs in the FPU are more recent than this state
	 * copy. If the task context-चयनes away then they get
	 * saved here and represent the FPU state.
	 */
	जोड़ fpregs_state		state;
	/*
	 * WARNING: 'state' is dynamically-sized.  Do not put
	 * anything after it here.
	 */
पूर्ण;

#पूर्ण_अगर /* _ASM_X86_FPU_H */
