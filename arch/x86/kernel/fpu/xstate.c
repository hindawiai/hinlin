<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * xsave/xrstor support.
 *
 * Author: Suresh Siddha <suresh.b.siddha@पूर्णांकel.com>
 */
#समावेश <linux/compat.h>
#समावेश <linux/cpu.h>
#समावेश <linux/mman.h>
#समावेश <linux/pkeys.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>

#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/fpu/संकेत.स>
#समावेश <यंत्र/fpu/regset.h>
#समावेश <यंत्र/fpu/xstate.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cpufeature.h>

/*
 * Although we spell it out in here, the Processor Trace
 * xfeature is completely unused.  We use other mechanisms
 * to save/restore PT state in Linux.
 */
अटल स्थिर अक्षर *xfeature_names[] =
अणु
	"x87 floating point registers"	,
	"SSE registers"			,
	"AVX registers"			,
	"MPX bounds registers"		,
	"MPX CSR"			,
	"AVX-512 opmask"		,
	"AVX-512 Hi256"			,
	"AVX-512 ZMM_Hi256"		,
	"Processor Trace (unused)"	,
	"Protection Keys User registers",
	"PASID state",
	"unknown xstate feature"	,
पूर्ण;

अटल लघु xsave_cpuid_features[] __initdata = अणु
	X86_FEATURE_FPU,
	X86_FEATURE_XMM,
	X86_FEATURE_AVX,
	X86_FEATURE_MPX,
	X86_FEATURE_MPX,
	X86_FEATURE_AVX512F,
	X86_FEATURE_AVX512F,
	X86_FEATURE_AVX512F,
	X86_FEATURE_INTEL_PT,
	X86_FEATURE_PKU,
	X86_FEATURE_ENQCMD,
पूर्ण;

/*
 * This represents the full set of bits that should ever be set in a kernel
 * XSAVE buffer, both supervisor and user xstates.
 */
u64 xfeatures_mask_all __पढ़ो_mostly;

अटल अचिन्हित पूर्णांक xstate_offsets[XFEATURE_MAX] = अणु [ 0 ... XFEATURE_MAX - 1] = -1पूर्ण;
अटल अचिन्हित पूर्णांक xstate_sizes[XFEATURE_MAX]   = अणु [ 0 ... XFEATURE_MAX - 1] = -1पूर्ण;
अटल अचिन्हित पूर्णांक xstate_comp_offsets[XFEATURE_MAX] = अणु [ 0 ... XFEATURE_MAX - 1] = -1पूर्ण;
अटल अचिन्हित पूर्णांक xstate_supervisor_only_offsets[XFEATURE_MAX] = अणु [ 0 ... XFEATURE_MAX - 1] = -1पूर्ण;

/*
 * The XSAVE area of kernel can be in standard or compacted क्रमmat;
 * it is always in standard क्रमmat क्रम user mode. This is the user
 * mode standard क्रमmat size used क्रम संकेत and ptrace frames.
 */
अचिन्हित पूर्णांक fpu_user_xstate_size;

/*
 * Return whether the प्रणाली supports a given xfeature.
 *
 * Also वापस the name of the (most advanced) feature that the caller requested:
 */
पूर्णांक cpu_has_xfeatures(u64 xfeatures_needed, स्थिर अक्षर **feature_name)
अणु
	u64 xfeatures_missing = xfeatures_needed & ~xfeatures_mask_all;

	अगर (unlikely(feature_name)) अणु
		दीर्घ xfeature_idx, max_idx;
		u64 xfeatures_prपूर्णांक;
		/*
		 * So we use FLS here to be able to prपूर्णांक the most advanced
		 * feature that was requested but is missing. So अगर a driver
		 * asks about "XFEATURE_MASK_SSE | XFEATURE_MASK_YMM" we'll prपूर्णांक the
		 * missing AVX feature - this is the most inक्रमmative message
		 * to users:
		 */
		अगर (xfeatures_missing)
			xfeatures_prपूर्णांक = xfeatures_missing;
		अन्यथा
			xfeatures_prपूर्णांक = xfeatures_needed;

		xfeature_idx = fls64(xfeatures_prपूर्णांक)-1;
		max_idx = ARRAY_SIZE(xfeature_names)-1;
		xfeature_idx = min(xfeature_idx, max_idx);

		*feature_name = xfeature_names[xfeature_idx];
	पूर्ण

	अगर (xfeatures_missing)
		वापस 0;

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_has_xfeatures);

अटल bool xfeature_is_supervisor(पूर्णांक xfeature_nr)
अणु
	/*
	 * Extended State Enumeration Sub-leaves (EAX = 0DH, ECX = n, n > 1)
	 * वापसs ECX[0] set to (1) क्रम a supervisor state, and cleared (0)
	 * क्रम a user state.
	 */
	u32 eax, ebx, ecx, edx;

	cpuid_count(XSTATE_CPUID, xfeature_nr, &eax, &ebx, &ecx, &edx);
	वापस ecx & 1;
पूर्ण

/*
 * When executing XSAVEOPT (or other optimized XSAVE inकाष्ठाions), अगर
 * a processor implementation detects that an FPU state component is still
 * (or is again) in its initialized state, it may clear the corresponding
 * bit in the header.xfeatures field, and can skip the ग_लिखोout of रेजिस्टरs
 * to the corresponding memory layout.
 *
 * This means that when the bit is zero, the state component might still contain
 * some previous - non-initialized रेजिस्टर state.
 *
 * Beक्रमe writing xstate inक्रमmation to user-space we sanitize those components,
 * to always ensure that the memory layout of a feature will be in the init state
 * अगर the corresponding header bit is zero. This is to ensure that user-space करोesn't
 * see some stale state in the memory layout during संकेत handling, debugging etc.
 */
व्योम fpstate_sanitize_xstate(काष्ठा fpu *fpu)
अणु
	काष्ठा fxregs_state *fx = &fpu->state.fxsave;
	पूर्णांक feature_bit;
	u64 xfeatures;

	अगर (!use_xsaveopt())
		वापस;

	xfeatures = fpu->state.xsave.header.xfeatures;

	/*
	 * None of the feature bits are in init state. So nothing अन्यथा
	 * to करो क्रम us, as the memory layout is up to date.
	 */
	अगर ((xfeatures & xfeatures_mask_all) == xfeatures_mask_all)
		वापस;

	/*
	 * FP is in init state
	 */
	अगर (!(xfeatures & XFEATURE_MASK_FP)) अणु
		fx->cwd = 0x37f;
		fx->swd = 0;
		fx->twd = 0;
		fx->fop = 0;
		fx->rip = 0;
		fx->rdp = 0;
		स_रखो(fx->st_space, 0, माप(fx->st_space));
	पूर्ण

	/*
	 * SSE is in init state
	 */
	अगर (!(xfeatures & XFEATURE_MASK_SSE))
		स_रखो(fx->xmm_space, 0, माप(fx->xmm_space));

	/*
	 * First two features are FPU and SSE, which above we handled
	 * in a special way alपढ़ोy:
	 */
	feature_bit = 0x2;
	xfeatures = (xfeatures_mask_user() & ~xfeatures) >> 2;

	/*
	 * Update all the reमुख्यing memory layouts according to their
	 * standard xstate layout, अगर their header bit is in the init
	 * state:
	 */
	जबतक (xfeatures) अणु
		अगर (xfeatures & 0x1) अणु
			पूर्णांक offset = xstate_comp_offsets[feature_bit];
			पूर्णांक size = xstate_sizes[feature_bit];

			स_नकल((व्योम *)fx + offset,
			       (व्योम *)&init_fpstate.xsave + offset,
			       size);
		पूर्ण

		xfeatures >>= 1;
		feature_bit++;
	पूर्ण
पूर्ण

/*
 * Enable the extended processor state save/restore feature.
 * Called once per CPU onlining.
 */
व्योम fpu__init_cpu_xstate(व्योम)
अणु
	u64 unsup_bits;

	अगर (!boot_cpu_has(X86_FEATURE_XSAVE) || !xfeatures_mask_all)
		वापस;
	/*
	 * Unsupported supervisor xstates should not be found in
	 * the xfeatures mask.
	 */
	unsup_bits = xfeatures_mask_all & XFEATURE_MASK_SUPERVISOR_UNSUPPORTED;
	WARN_ONCE(unsup_bits, "x86/fpu: Found unsupported supervisor xstates: 0x%llx\n",
		  unsup_bits);

	xfeatures_mask_all &= ~XFEATURE_MASK_SUPERVISOR_UNSUPPORTED;

	cr4_set_bits(X86_CR4_OSXSAVE);

	/*
	 * XCR_XFEATURE_ENABLED_MASK (aka. XCR0) sets user features
	 * managed by XSAVEअणुC, OPT, Sपूर्ण and XRSTORअणुSपूर्ण.  Only XSAVE user
	 * states can be set here.
	 */
	xsetbv(XCR_XFEATURE_ENABLED_MASK, xfeatures_mask_user());

	/*
	 * MSR_IA32_XSS sets supervisor states managed by XSAVES.
	 */
	अगर (boot_cpu_has(X86_FEATURE_XSAVES)) अणु
		wrmsrl(MSR_IA32_XSS, xfeatures_mask_supervisor() |
				     xfeatures_mask_dynamic());
	पूर्ण
पूर्ण

अटल bool xfeature_enabled(क्रमागत xfeature xfeature)
अणु
	वापस xfeatures_mask_all & BIT_ULL(xfeature);
पूर्ण

/*
 * Record the offsets and sizes of various xstates contained
 * in the XSAVE state memory layout.
 */
अटल व्योम __init setup_xstate_features(व्योम)
अणु
	u32 eax, ebx, ecx, edx, i;
	/* start at the beginning of the "extended state" */
	अचिन्हित पूर्णांक last_good_offset = दुरत्व(काष्ठा xregs_state,
						 extended_state_area);
	/*
	 * The FP xstates and SSE xstates are legacy states. They are always
	 * in the fixed offsets in the xsave area in either compacted क्रमm
	 * or standard क्रमm.
	 */
	xstate_offsets[XFEATURE_FP]	= 0;
	xstate_sizes[XFEATURE_FP]	= दुरत्व(काष्ठा fxregs_state,
						   xmm_space);

	xstate_offsets[XFEATURE_SSE]	= xstate_sizes[XFEATURE_FP];
	xstate_sizes[XFEATURE_SSE]	= माप_field(काष्ठा fxregs_state,
						       xmm_space);

	क्रम (i = FIRST_EXTENDED_XFEATURE; i < XFEATURE_MAX; i++) अणु
		अगर (!xfeature_enabled(i))
			जारी;

		cpuid_count(XSTATE_CPUID, i, &eax, &ebx, &ecx, &edx);

		xstate_sizes[i] = eax;

		/*
		 * If an xfeature is supervisor state, the offset in EBX is
		 * invalid, leave it to -1.
		 */
		अगर (xfeature_is_supervisor(i))
			जारी;

		xstate_offsets[i] = ebx;

		/*
		 * In our xstate size checks, we assume that the highest-numbered
		 * xstate feature has the highest offset in the buffer.  Ensure
		 * it करोes.
		 */
		WARN_ONCE(last_good_offset > xstate_offsets[i],
			  "x86/fpu: misordered xstate at %d\n", last_good_offset);

		last_good_offset = xstate_offsets[i];
	पूर्ण
पूर्ण

अटल व्योम __init prपूर्णांक_xstate_feature(u64 xstate_mask)
अणु
	स्थिर अक्षर *feature_name;

	अगर (cpu_has_xfeatures(xstate_mask, &feature_name))
		pr_info("x86/fpu: Supporting XSAVE feature 0x%03Lx: '%s'\n", xstate_mask, feature_name);
पूर्ण

/*
 * Prपूर्णांक out all the supported xstate features:
 */
अटल व्योम __init prपूर्णांक_xstate_features(व्योम)
अणु
	prपूर्णांक_xstate_feature(XFEATURE_MASK_FP);
	prपूर्णांक_xstate_feature(XFEATURE_MASK_SSE);
	prपूर्णांक_xstate_feature(XFEATURE_MASK_YMM);
	prपूर्णांक_xstate_feature(XFEATURE_MASK_BNDREGS);
	prपूर्णांक_xstate_feature(XFEATURE_MASK_BNDCSR);
	prपूर्णांक_xstate_feature(XFEATURE_MASK_OPMASK);
	prपूर्णांक_xstate_feature(XFEATURE_MASK_ZMM_Hi256);
	prपूर्णांक_xstate_feature(XFEATURE_MASK_Hi16_ZMM);
	prपूर्णांक_xstate_feature(XFEATURE_MASK_PKRU);
	prपूर्णांक_xstate_feature(XFEATURE_MASK_PASID);
पूर्ण

/*
 * This check is important because it is easy to get XSTATE_*
 * confused with XSTATE_BIT_*.
 */
#घोषणा CHECK_XFEATURE(nr) करो अणु		\
	WARN_ON(nr < FIRST_EXTENDED_XFEATURE);	\
	WARN_ON(nr >= XFEATURE_MAX);	\
पूर्ण जबतक (0)

/*
 * We could cache this like xstate_size[], but we only use
 * it here, so it would be a waste of space.
 */
अटल पूर्णांक xfeature_is_aligned(पूर्णांक xfeature_nr)
अणु
	u32 eax, ebx, ecx, edx;

	CHECK_XFEATURE(xfeature_nr);

	अगर (!xfeature_enabled(xfeature_nr)) अणु
		WARN_ONCE(1, "Checking alignment of disabled xfeature %d\n",
			  xfeature_nr);
		वापस 0;
	पूर्ण

	cpuid_count(XSTATE_CPUID, xfeature_nr, &eax, &ebx, &ecx, &edx);
	/*
	 * The value वापसed by ECX[1] indicates the alignment
	 * of state component 'i' when the compacted क्रमmat
	 * of the extended region of an XSAVE area is used:
	 */
	वापस !!(ecx & 2);
पूर्ण

/*
 * This function sets up offsets and sizes of all extended states in
 * xsave area. This supports both standard क्रमmat and compacted क्रमmat
 * of the xsave area.
 */
अटल व्योम __init setup_xstate_comp_offsets(व्योम)
अणु
	अचिन्हित पूर्णांक next_offset;
	पूर्णांक i;

	/*
	 * The FP xstates and SSE xstates are legacy states. They are always
	 * in the fixed offsets in the xsave area in either compacted क्रमm
	 * or standard क्रमm.
	 */
	xstate_comp_offsets[XFEATURE_FP] = 0;
	xstate_comp_offsets[XFEATURE_SSE] = दुरत्व(काष्ठा fxregs_state,
						     xmm_space);

	अगर (!boot_cpu_has(X86_FEATURE_XSAVES)) अणु
		क्रम (i = FIRST_EXTENDED_XFEATURE; i < XFEATURE_MAX; i++) अणु
			अगर (xfeature_enabled(i))
				xstate_comp_offsets[i] = xstate_offsets[i];
		पूर्ण
		वापस;
	पूर्ण

	next_offset = FXSAVE_SIZE + XSAVE_HDR_SIZE;

	क्रम (i = FIRST_EXTENDED_XFEATURE; i < XFEATURE_MAX; i++) अणु
		अगर (!xfeature_enabled(i))
			जारी;

		अगर (xfeature_is_aligned(i))
			next_offset = ALIGN(next_offset, 64);

		xstate_comp_offsets[i] = next_offset;
		next_offset += xstate_sizes[i];
	पूर्ण
पूर्ण

/*
 * Setup offsets of a supervisor-state-only XSAVES buffer:
 *
 * The offsets stored in xstate_comp_offsets[] only work क्रम one specअगरic
 * value of the Requested Feature BitMap (RFBM).  In हालs where a dअगरferent
 * RFBM value is used, a dअगरferent set of offsets is required.  This set of
 * offsets is क्रम when RFBM=xfeatures_mask_supervisor().
 */
अटल व्योम __init setup_supervisor_only_offsets(व्योम)
अणु
	अचिन्हित पूर्णांक next_offset;
	पूर्णांक i;

	next_offset = FXSAVE_SIZE + XSAVE_HDR_SIZE;

	क्रम (i = FIRST_EXTENDED_XFEATURE; i < XFEATURE_MAX; i++) अणु
		अगर (!xfeature_enabled(i) || !xfeature_is_supervisor(i))
			जारी;

		अगर (xfeature_is_aligned(i))
			next_offset = ALIGN(next_offset, 64);

		xstate_supervisor_only_offsets[i] = next_offset;
		next_offset += xstate_sizes[i];
	पूर्ण
पूर्ण

/*
 * Prपूर्णांक out xstate component offsets and sizes
 */
अटल व्योम __init prपूर्णांक_xstate_offset_size(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = FIRST_EXTENDED_XFEATURE; i < XFEATURE_MAX; i++) अणु
		अगर (!xfeature_enabled(i))
			जारी;
		pr_info("x86/fpu: xstate_offset[%d]: %4d, xstate_sizes[%d]: %4d\n",
			 i, xstate_comp_offsets[i], i, xstate_sizes[i]);
	पूर्ण
पूर्ण

/*
 * setup the xstate image representing the init state
 */
अटल व्योम __init setup_init_fpu_buf(व्योम)
अणु
	अटल पूर्णांक on_boot_cpu __initdata = 1;

	WARN_ON_FPU(!on_boot_cpu);
	on_boot_cpu = 0;

	अगर (!boot_cpu_has(X86_FEATURE_XSAVE))
		वापस;

	setup_xstate_features();
	prपूर्णांक_xstate_features();

	अगर (boot_cpu_has(X86_FEATURE_XSAVES))
		init_fpstate.xsave.header.xcomp_bv = XCOMP_BV_COMPACTED_FORMAT |
						     xfeatures_mask_all;

	/*
	 * Init all the features state with header.xfeatures being 0x0
	 */
	copy_kernel_to_xregs_booting(&init_fpstate.xsave);

	/*
	 * Dump the init state again. This is to identअगरy the init state
	 * of any feature which is not represented by all zero's.
	 */
	copy_xregs_to_kernel_booting(&init_fpstate.xsave);
पूर्ण

अटल पूर्णांक xfeature_uncompacted_offset(पूर्णांक xfeature_nr)
अणु
	u32 eax, ebx, ecx, edx;

	/*
	 * Only XSAVES supports supervisor states and it uses compacted
	 * क्रमmat. Checking a supervisor state's uncompacted offset is
	 * an error.
	 */
	अगर (XFEATURE_MASK_SUPERVISOR_ALL & BIT_ULL(xfeature_nr)) अणु
		WARN_ONCE(1, "No fixed offset for xstate %d\n", xfeature_nr);
		वापस -1;
	पूर्ण

	CHECK_XFEATURE(xfeature_nr);
	cpuid_count(XSTATE_CPUID, xfeature_nr, &eax, &ebx, &ecx, &edx);
	वापस ebx;
पूर्ण

पूर्णांक xfeature_size(पूर्णांक xfeature_nr)
अणु
	u32 eax, ebx, ecx, edx;

	CHECK_XFEATURE(xfeature_nr);
	cpuid_count(XSTATE_CPUID, xfeature_nr, &eax, &ebx, &ecx, &edx);
	वापस eax;
पूर्ण

/*
 * 'XSAVES' implies two dअगरferent things:
 * 1. saving of supervisor/प्रणाली state
 * 2. using the compacted क्रमmat
 *
 * Use this function when dealing with the compacted क्रमmat so
 * that it is obvious which aspect of 'XSAVES' is being handled
 * by the calling code.
 */
पूर्णांक using_compacted_क्रमmat(व्योम)
अणु
	वापस boot_cpu_has(X86_FEATURE_XSAVES);
पूर्ण

/* Validate an xstate header supplied by userspace (ptrace or sigवापस) */
पूर्णांक validate_user_xstate_header(स्थिर काष्ठा xstate_header *hdr)
अणु
	/* No unknown or supervisor features may be set */
	अगर (hdr->xfeatures & ~xfeatures_mask_user())
		वापस -EINVAL;

	/* Userspace must use the uncompacted क्रमmat */
	अगर (hdr->xcomp_bv)
		वापस -EINVAL;

	/*
	 * If 'reserved' is shrunken to add a new field, make sure to validate
	 * that new field here!
	 */
	BUILD_BUG_ON(माप(hdr->reserved) != 48);

	/* No reserved bits may be set */
	अगर (स_प्रथम_inv(hdr->reserved, 0, माप(hdr->reserved)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम __xstate_dump_leaves(व्योम)
अणु
	पूर्णांक i;
	u32 eax, ebx, ecx, edx;
	अटल पूर्णांक should_dump = 1;

	अगर (!should_dump)
		वापस;
	should_dump = 0;
	/*
	 * Dump out a few leaves past the ones that we support
	 * just in हाल there are some goodies up there
	 */
	क्रम (i = 0; i < XFEATURE_MAX + 10; i++) अणु
		cpuid_count(XSTATE_CPUID, i, &eax, &ebx, &ecx, &edx);
		pr_warn("CPUID[%02x, %02x]: eax=%08x ebx=%08x ecx=%08x edx=%08x\n",
			XSTATE_CPUID, i, eax, ebx, ecx, edx);
	पूर्ण
पूर्ण

#घोषणा XSTATE_WARN_ON(x) करो अणु							\
	अगर (WARN_ONCE(x, "XSAVE consistency problem, dumping leaves")) अणु	\
		__xstate_dump_leaves();						\
	पूर्ण									\
पूर्ण जबतक (0)

#घोषणा XCHECK_SZ(sz, nr, nr_macro, __काष्ठा) करो अणु			\
	अगर ((nr == nr_macro) &&						\
	    WARN_ONCE(sz != माप(__काष्ठा),				\
		"%s: struct is %zu bytes, cpu state %d bytes\n",	\
		__stringअगरy(nr_macro), माप(__काष्ठा), sz)) अणु		\
		__xstate_dump_leaves();					\
	पूर्ण								\
पूर्ण जबतक (0)

/*
 * We have a C काष्ठा क्रम each 'xstate'.  We need to ensure
 * that our software representation matches what the CPU
 * tells us about the state's size.
 */
अटल व्योम check_xstate_against_काष्ठा(पूर्णांक nr)
अणु
	/*
	 * Ask the CPU क्रम the size of the state.
	 */
	पूर्णांक sz = xfeature_size(nr);
	/*
	 * Match each CPU state with the corresponding software
	 * काष्ठाure.
	 */
	XCHECK_SZ(sz, nr, XFEATURE_YMM,       काष्ठा ymmh_काष्ठा);
	XCHECK_SZ(sz, nr, XFEATURE_BNDREGS,   काष्ठा mpx_bndreg_state);
	XCHECK_SZ(sz, nr, XFEATURE_BNDCSR,    काष्ठा mpx_bndcsr_state);
	XCHECK_SZ(sz, nr, XFEATURE_OPMASK,    काष्ठा avx_512_opmask_state);
	XCHECK_SZ(sz, nr, XFEATURE_ZMM_Hi256, काष्ठा avx_512_zmm_uppers_state);
	XCHECK_SZ(sz, nr, XFEATURE_Hi16_ZMM,  काष्ठा avx_512_hi16_state);
	XCHECK_SZ(sz, nr, XFEATURE_PKRU,      काष्ठा pkru_state);
	XCHECK_SZ(sz, nr, XFEATURE_PASID,     काष्ठा ia32_pasid_state);

	/*
	 * Make *SURE* to add any feature numbers in below अगर
	 * there are "holes" in the xsave state component
	 * numbers.
	 */
	अगर ((nr < XFEATURE_YMM) ||
	    (nr >= XFEATURE_MAX) ||
	    (nr == XFEATURE_PT_UNIMPLEMENTED_SO_FAR) ||
	    ((nr >= XFEATURE_RSRVD_COMP_11) && (nr <= XFEATURE_LBR))) अणु
		WARN_ONCE(1, "no structure for xstate: %d\n", nr);
		XSTATE_WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * This essentially द्विगुन-checks what the cpu told us about
 * how large the XSAVE buffer needs to be.  We are recalculating
 * it to be safe.
 *
 * Dynamic XSAVE features allocate their own buffers and are not
 * covered by these checks. Only the size of the buffer क्रम task->fpu
 * is checked here.
 */
अटल व्योम करो_extra_xstate_size_checks(व्योम)
अणु
	पूर्णांक paranoid_xstate_size = FXSAVE_SIZE + XSAVE_HDR_SIZE;
	पूर्णांक i;

	क्रम (i = FIRST_EXTENDED_XFEATURE; i < XFEATURE_MAX; i++) अणु
		अगर (!xfeature_enabled(i))
			जारी;

		check_xstate_against_काष्ठा(i);
		/*
		 * Supervisor state components can be managed only by
		 * XSAVES, which is compacted-क्रमmat only.
		 */
		अगर (!using_compacted_क्रमmat())
			XSTATE_WARN_ON(xfeature_is_supervisor(i));

		/* Align from the end of the previous feature */
		अगर (xfeature_is_aligned(i))
			paranoid_xstate_size = ALIGN(paranoid_xstate_size, 64);
		/*
		 * The offset of a given state in the non-compacted
		 * क्रमmat is given to us in a CPUID leaf.  We check
		 * them क्रम being ordered (increasing offsets) in
		 * setup_xstate_features().
		 */
		अगर (!using_compacted_क्रमmat())
			paranoid_xstate_size = xfeature_uncompacted_offset(i);
		/*
		 * The compacted-क्रमmat offset always depends on where
		 * the previous state ended.
		 */
		paranoid_xstate_size += xfeature_size(i);
	पूर्ण
	XSTATE_WARN_ON(paranoid_xstate_size != fpu_kernel_xstate_size);
पूर्ण


/*
 * Get total size of enabled xstates in XCR0 | IA32_XSS.
 *
 * Note the SDM's wording here.  "sub-function 0" only क्रमागतerates
 * the size of the *user* states.  If we use it to size a buffer
 * that we use 'XSAVES' on, we could potentially overflow the
 * buffer because 'XSAVES' saves प्रणाली states too.
 */
अटल अचिन्हित पूर्णांक __init get_xsaves_size(व्योम)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	/*
	 * - CPUID function 0DH, sub-function 1:
	 *    EBX क्रमागतerates the size (in bytes) required by
	 *    the XSAVES inकाष्ठाion क्रम an XSAVE area
	 *    containing all the state components
	 *    corresponding to bits currently set in
	 *    XCR0 | IA32_XSS.
	 */
	cpuid_count(XSTATE_CPUID, 1, &eax, &ebx, &ecx, &edx);
	वापस ebx;
पूर्ण

/*
 * Get the total size of the enabled xstates without the dynamic supervisor
 * features.
 */
अटल अचिन्हित पूर्णांक __init get_xsaves_size_no_dynamic(व्योम)
अणु
	u64 mask = xfeatures_mask_dynamic();
	अचिन्हित पूर्णांक size;

	अगर (!mask)
		वापस get_xsaves_size();

	/* Disable dynamic features. */
	wrmsrl(MSR_IA32_XSS, xfeatures_mask_supervisor());

	/*
	 * Ask the hardware what size is required of the buffer.
	 * This is the size required क्रम the task->fpu buffer.
	 */
	size = get_xsaves_size();

	/* Re-enable dynamic features so XSAVES will work on them again. */
	wrmsrl(MSR_IA32_XSS, xfeatures_mask_supervisor() | mask);

	वापस size;
पूर्ण

अटल अचिन्हित पूर्णांक __init get_xsave_size(व्योम)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	/*
	 * - CPUID function 0DH, sub-function 0:
	 *    EBX क्रमागतerates the size (in bytes) required by
	 *    the XSAVE inकाष्ठाion क्रम an XSAVE area
	 *    containing all the *user* state components
	 *    corresponding to bits currently set in XCR0.
	 */
	cpuid_count(XSTATE_CPUID, 0, &eax, &ebx, &ecx, &edx);
	वापस ebx;
पूर्ण

/*
 * Will the runसमय-क्रमागतerated 'xstate_size' fit in the init
 * task's अटलally-allocated buffer?
 */
अटल bool is_supported_xstate_size(अचिन्हित पूर्णांक test_xstate_size)
अणु
	अगर (test_xstate_size <= माप(जोड़ fpregs_state))
		वापस true;

	pr_warn("x86/fpu: xstate buffer too small (%zu < %d), disabling xsave\n",
			माप(जोड़ fpregs_state), test_xstate_size);
	वापस false;
पूर्ण

अटल पूर्णांक __init init_xstate_size(व्योम)
अणु
	/* Recompute the context size क्रम enabled features: */
	अचिन्हित पूर्णांक possible_xstate_size;
	अचिन्हित पूर्णांक xsave_size;

	xsave_size = get_xsave_size();

	अगर (boot_cpu_has(X86_FEATURE_XSAVES))
		possible_xstate_size = get_xsaves_size_no_dynamic();
	अन्यथा
		possible_xstate_size = xsave_size;

	/* Ensure we have the space to store all enabled: */
	अगर (!is_supported_xstate_size(possible_xstate_size))
		वापस -EINVAL;

	/*
	 * The size is OK, we are definitely going to use xsave,
	 * make it known to the world that we need more space.
	 */
	fpu_kernel_xstate_size = possible_xstate_size;
	करो_extra_xstate_size_checks();

	/*
	 * User space is always in standard क्रमmat.
	 */
	fpu_user_xstate_size = xsave_size;
	वापस 0;
पूर्ण

/*
 * We enabled the XSAVE hardware, but something went wrong and
 * we can not use it.  Disable it.
 */
अटल व्योम fpu__init_disable_प्रणाली_xstate(व्योम)
अणु
	xfeatures_mask_all = 0;
	cr4_clear_bits(X86_CR4_OSXSAVE);
	setup_clear_cpu_cap(X86_FEATURE_XSAVE);
पूर्ण

/*
 * Enable and initialize the xsave feature.
 * Called once per प्रणाली bootup.
 */
व्योम __init fpu__init_प्रणाली_xstate(व्योम)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	अटल पूर्णांक on_boot_cpu __initdata = 1;
	पूर्णांक err;
	पूर्णांक i;

	WARN_ON_FPU(!on_boot_cpu);
	on_boot_cpu = 0;

	अगर (!boot_cpu_has(X86_FEATURE_FPU)) अणु
		pr_info("x86/fpu: No FPU detected\n");
		वापस;
	पूर्ण

	अगर (!boot_cpu_has(X86_FEATURE_XSAVE)) अणु
		pr_info("x86/fpu: x87 FPU will use %s\n",
			boot_cpu_has(X86_FEATURE_FXSR) ? "FXSAVE" : "FSAVE");
		वापस;
	पूर्ण

	अगर (boot_cpu_data.cpuid_level < XSTATE_CPUID) अणु
		WARN_ON_FPU(1);
		वापस;
	पूर्ण

	/*
	 * Find user xstates supported by the processor.
	 */
	cpuid_count(XSTATE_CPUID, 0, &eax, &ebx, &ecx, &edx);
	xfeatures_mask_all = eax + ((u64)edx << 32);

	/*
	 * Find supervisor xstates supported by the processor.
	 */
	cpuid_count(XSTATE_CPUID, 1, &eax, &ebx, &ecx, &edx);
	xfeatures_mask_all |= ecx + ((u64)edx << 32);

	अगर ((xfeatures_mask_user() & XFEATURE_MASK_FPSSE) != XFEATURE_MASK_FPSSE) अणु
		/*
		 * This indicates that something really unexpected happened
		 * with the क्रमागतeration.  Disable XSAVE and try to जारी
		 * booting without it.  This is too early to BUG().
		 */
		pr_err("x86/fpu: FP/SSE not present amongst the CPU's xstate features: 0x%llx.\n",
		       xfeatures_mask_all);
		जाओ out_disable;
	पूर्ण

	/*
	 * Clear XSAVE features that are disabled in the normal CPUID.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(xsave_cpuid_features); i++) अणु
		अगर (!boot_cpu_has(xsave_cpuid_features[i]))
			xfeatures_mask_all &= ~BIT_ULL(i);
	पूर्ण

	xfeatures_mask_all &= fpu__get_supported_xfeatures_mask();

	/* Enable xstate inकाष्ठाions to be able to जारी with initialization: */
	fpu__init_cpu_xstate();
	err = init_xstate_size();
	अगर (err)
		जाओ out_disable;

	/*
	 * Update info used क्रम ptrace frames; use standard-क्रमmat size and no
	 * supervisor xstates:
	 */
	update_regset_xstate_info(fpu_user_xstate_size, xfeatures_mask_user());

	fpu__init_prepare_fx_sw_frame();
	setup_init_fpu_buf();
	setup_xstate_comp_offsets();
	setup_supervisor_only_offsets();
	prपूर्णांक_xstate_offset_size();

	pr_info("x86/fpu: Enabled xstate features 0x%llx, context size is %d bytes, using '%s' format.\n",
		xfeatures_mask_all,
		fpu_kernel_xstate_size,
		boot_cpu_has(X86_FEATURE_XSAVES) ? "compacted" : "standard");
	वापस;

out_disable:
	/* something went wrong, try to boot without any XSAVE support */
	fpu__init_disable_प्रणाली_xstate();
पूर्ण

/*
 * Restore minimal FPU state after suspend:
 */
व्योम fpu__resume_cpu(व्योम)
अणु
	/*
	 * Restore XCR0 on xsave capable CPUs:
	 */
	अगर (boot_cpu_has(X86_FEATURE_XSAVE))
		xsetbv(XCR_XFEATURE_ENABLED_MASK, xfeatures_mask_user());

	/*
	 * Restore IA32_XSS. The same CPUID bit क्रमागतerates support
	 * of XSAVES and MSR_IA32_XSS.
	 */
	अगर (boot_cpu_has(X86_FEATURE_XSAVES)) अणु
		wrmsrl(MSR_IA32_XSS, xfeatures_mask_supervisor()  |
				     xfeatures_mask_dynamic());
	पूर्ण
पूर्ण

/*
 * Given an xstate feature nr, calculate where in the xsave
 * buffer the state is.  Callers should ensure that the buffer
 * is valid.
 */
अटल व्योम *__raw_xsave_addr(काष्ठा xregs_state *xsave, पूर्णांक xfeature_nr)
अणु
	अगर (!xfeature_enabled(xfeature_nr)) अणु
		WARN_ON_FPU(1);
		वापस शून्य;
	पूर्ण

	वापस (व्योम *)xsave + xstate_comp_offsets[xfeature_nr];
पूर्ण
/*
 * Given the xsave area and a state inside, this function वापसs the
 * address of the state.
 *
 * This is the API that is called to get xstate address in either
 * standard क्रमmat or compacted क्रमmat of xsave area.
 *
 * Note that अगर there is no data क्रम the field in the xsave buffer
 * this will वापस शून्य.
 *
 * Inमाला_दो:
 *	xstate: the thपढ़ो's storage area क्रम all FPU data
 *	xfeature_nr: state which is defined in xsave.h (e.g. XFEATURE_FP,
 *	XFEATURE_SSE, etc...)
 * Output:
 *	address of the state in the xsave area, or शून्य अगर the
 *	field is not present in the xsave buffer.
 */
व्योम *get_xsave_addr(काष्ठा xregs_state *xsave, पूर्णांक xfeature_nr)
अणु
	/*
	 * Do we even *have* xsave state?
	 */
	अगर (!boot_cpu_has(X86_FEATURE_XSAVE))
		वापस शून्य;

	/*
	 * We should not ever be requesting features that we
	 * have not enabled.
	 */
	WARN_ONCE(!(xfeatures_mask_all & BIT_ULL(xfeature_nr)),
		  "get of unsupported state");
	/*
	 * This assumes the last 'xsave*' inकाष्ठाion to
	 * have requested that 'xfeature_nr' be saved.
	 * If it did not, we might be seeing and old value
	 * of the field in the buffer.
	 *
	 * This can happen because the last 'xsave' did not
	 * request that this feature be saved (unlikely)
	 * or because the "init optimization" caused it
	 * to not be saved.
	 */
	अगर (!(xsave->header.xfeatures & BIT_ULL(xfeature_nr)))
		वापस शून्य;

	वापस __raw_xsave_addr(xsave, xfeature_nr);
पूर्ण
EXPORT_SYMBOL_GPL(get_xsave_addr);

/*
 * This wraps up the common operations that need to occur when retrieving
 * data from xsave state.  It first ensures that the current task was
 * using the FPU and retrieves the data in to a buffer.  It then calculates
 * the offset of the requested field in the buffer.
 *
 * This function is safe to call whether the FPU is in use or not.
 *
 * Note that this only works on the current task.
 *
 * Inमाला_दो:
 *	@xfeature_nr: state which is defined in xsave.h (e.g. XFEATURE_FP,
 *	XFEATURE_SSE, etc...)
 * Output:
 *	address of the state in the xsave area or शून्य अगर the state
 *	is not present or is in its 'init state'.
 */
स्थिर व्योम *get_xsave_field_ptr(पूर्णांक xfeature_nr)
अणु
	काष्ठा fpu *fpu = &current->thपढ़ो.fpu;

	/*
	 * fpu__save() takes the CPU's xstate रेजिस्टरs
	 * and saves them off to the 'fpu memory buffer.
	 */
	fpu__save(fpu);

	वापस get_xsave_addr(&fpu->state.xsave, xfeature_nr);
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_PKEYS

/*
 * This will go out and modअगरy PKRU रेजिस्टर to set the access
 * rights क्रम @pkey to @init_val.
 */
पूर्णांक arch_set_user_pkey_access(काष्ठा task_काष्ठा *tsk, पूर्णांक pkey,
		अचिन्हित दीर्घ init_val)
अणु
	u32 old_pkru;
	पूर्णांक pkey_shअगरt = (pkey * PKRU_BITS_PER_PKEY);
	u32 new_pkru_bits = 0;

	/*
	 * This check implies XSAVE support.  OSPKE only माला_लो
	 * set अगर we enable XSAVE and we enable PKU in XCR0.
	 */
	अगर (!boot_cpu_has(X86_FEATURE_OSPKE))
		वापस -EINVAL;

	/*
	 * This code should only be called with valid 'pkey'
	 * values originating from in-kernel users.  Complain
	 * अगर a bad value is observed.
	 */
	WARN_ON_ONCE(pkey >= arch_max_pkey());

	/* Set the bits we need in PKRU:  */
	अगर (init_val & PKEY_DISABLE_ACCESS)
		new_pkru_bits |= PKRU_AD_BIT;
	अगर (init_val & PKEY_DISABLE_WRITE)
		new_pkru_bits |= PKRU_WD_BIT;

	/* Shअगरt the bits in to the correct place in PKRU क्रम pkey: */
	new_pkru_bits <<= pkey_shअगरt;

	/* Get old PKRU and mask off any old bits in place: */
	old_pkru = पढ़ो_pkru();
	old_pkru &= ~((PKRU_AD_BIT|PKRU_WD_BIT) << pkey_shअगरt);

	/* Write old part aदीर्घ with new part: */
	ग_लिखो_pkru(old_pkru | new_pkru_bits);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* ! CONFIG_ARCH_HAS_PKEYS */

/*
 * Weird legacy quirk: SSE and YMM states store inक्रमmation in the
 * MXCSR and MXCSR_FLAGS fields of the FP area. That means अगर the FP
 * area is marked as unused in the xfeatures header, we need to copy
 * MXCSR and MXCSR_FLAGS अगर either SSE or YMM are in use.
 */
अटल अंतरभूत bool xfeatures_mxcsr_quirk(u64 xfeatures)
अणु
	अगर (!(xfeatures & (XFEATURE_MASK_SSE|XFEATURE_MASK_YMM)))
		वापस false;

	अगर (xfeatures & XFEATURE_MASK_FP)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम fill_gap(काष्ठा membuf *to, अचिन्हित *last, अचिन्हित offset)
अणु
	अगर (*last >= offset)
		वापस;
	membuf_ग_लिखो(to, (व्योम *)&init_fpstate.xsave + *last, offset - *last);
	*last = offset;
पूर्ण

अटल व्योम copy_part(काष्ठा membuf *to, अचिन्हित *last, अचिन्हित offset,
		      अचिन्हित size, व्योम *from)
अणु
	fill_gap(to, last, offset);
	membuf_ग_लिखो(to, from, size);
	*last = offset + size;
पूर्ण

/*
 * Convert from kernel XSAVES compacted क्रमmat to standard क्रमmat and copy
 * to a kernel-space ptrace buffer.
 *
 * It supports partial copy but pos always starts from zero. This is called
 * from xstateregs_get() and there we check the CPU has XSAVES.
 */
व्योम copy_xstate_to_kernel(काष्ठा membuf to, काष्ठा xregs_state *xsave)
अणु
	काष्ठा xstate_header header;
	स्थिर अचिन्हित off_mxcsr = दुरत्व(काष्ठा fxregs_state, mxcsr);
	अचिन्हित size = to.left;
	अचिन्हित last = 0;
	पूर्णांक i;

	/*
	 * The destination is a ptrace buffer; we put in only user xstates:
	 */
	स_रखो(&header, 0, माप(header));
	header.xfeatures = xsave->header.xfeatures;
	header.xfeatures &= xfeatures_mask_user();

	अगर (header.xfeatures & XFEATURE_MASK_FP)
		copy_part(&to, &last, 0, off_mxcsr, &xsave->i387);
	अगर (header.xfeatures & (XFEATURE_MASK_SSE | XFEATURE_MASK_YMM))
		copy_part(&to, &last, off_mxcsr,
			  MXCSR_AND_FLAGS_SIZE, &xsave->i387.mxcsr);
	अगर (header.xfeatures & XFEATURE_MASK_FP)
		copy_part(&to, &last, दुरत्व(काष्ठा fxregs_state, st_space),
			  128, &xsave->i387.st_space);
	अगर (header.xfeatures & XFEATURE_MASK_SSE)
		copy_part(&to, &last, xstate_offsets[XFEATURE_SSE],
			  256, &xsave->i387.xmm_space);
	/*
	 * Fill xsave->i387.sw_reserved value क्रम ptrace frame:
	 */
	copy_part(&to, &last, दुरत्व(काष्ठा fxregs_state, sw_reserved),
		  48, xstate_fx_sw_bytes);
	/*
	 * Copy xregs_state->header:
	 */
	copy_part(&to, &last, दुरत्व(काष्ठा xregs_state, header),
		  माप(header), &header);

	क्रम (i = FIRST_EXTENDED_XFEATURE; i < XFEATURE_MAX; i++) अणु
		/*
		 * Copy only in-use xstates:
		 */
		अगर ((header.xfeatures >> i) & 1) अणु
			व्योम *src = __raw_xsave_addr(xsave, i);

			copy_part(&to, &last, xstate_offsets[i],
				  xstate_sizes[i], src);
		पूर्ण

	पूर्ण
	fill_gap(&to, &last, size);
पूर्ण

/*
 * Convert from a ptrace standard-क्रमmat kernel buffer to kernel XSAVES क्रमmat
 * and copy to the target thपढ़ो. This is called from xstateregs_set().
 */
पूर्णांक copy_kernel_to_xstate(काष्ठा xregs_state *xsave, स्थिर व्योम *kbuf)
अणु
	अचिन्हित पूर्णांक offset, size;
	पूर्णांक i;
	काष्ठा xstate_header hdr;

	offset = दुरत्व(काष्ठा xregs_state, header);
	size = माप(hdr);

	स_नकल(&hdr, kbuf + offset, size);

	अगर (validate_user_xstate_header(&hdr))
		वापस -EINVAL;

	क्रम (i = 0; i < XFEATURE_MAX; i++) अणु
		u64 mask = ((u64)1 << i);

		अगर (hdr.xfeatures & mask) अणु
			व्योम *dst = __raw_xsave_addr(xsave, i);

			offset = xstate_offsets[i];
			size = xstate_sizes[i];

			स_नकल(dst, kbuf + offset, size);
		पूर्ण
	पूर्ण

	अगर (xfeatures_mxcsr_quirk(hdr.xfeatures)) अणु
		offset = दुरत्व(काष्ठा fxregs_state, mxcsr);
		size = MXCSR_AND_FLAGS_SIZE;
		स_नकल(&xsave->i387.mxcsr, kbuf + offset, size);
	पूर्ण

	/*
	 * The state that came in from userspace was user-state only.
	 * Mask all the user states out of 'xfeatures':
	 */
	xsave->header.xfeatures &= XFEATURE_MASK_SUPERVISOR_ALL;

	/*
	 * Add back in the features that came in from userspace:
	 */
	xsave->header.xfeatures |= hdr.xfeatures;

	वापस 0;
पूर्ण

/*
 * Convert from a ptrace or sigवापस standard-क्रमmat user-space buffer to
 * kernel XSAVES क्रमmat and copy to the target thपढ़ो. This is called from
 * xstateregs_set(), as well as potentially from the sigवापस() and
 * rt_sigवापस() प्रणाली calls.
 */
पूर्णांक copy_user_to_xstate(काष्ठा xregs_state *xsave, स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित पूर्णांक offset, size;
	पूर्णांक i;
	काष्ठा xstate_header hdr;

	offset = दुरत्व(काष्ठा xregs_state, header);
	size = माप(hdr);

	अगर (__copy_from_user(&hdr, ubuf + offset, size))
		वापस -EFAULT;

	अगर (validate_user_xstate_header(&hdr))
		वापस -EINVAL;

	क्रम (i = 0; i < XFEATURE_MAX; i++) अणु
		u64 mask = ((u64)1 << i);

		अगर (hdr.xfeatures & mask) अणु
			व्योम *dst = __raw_xsave_addr(xsave, i);

			offset = xstate_offsets[i];
			size = xstate_sizes[i];

			अगर (__copy_from_user(dst, ubuf + offset, size))
				वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (xfeatures_mxcsr_quirk(hdr.xfeatures)) अणु
		offset = दुरत्व(काष्ठा fxregs_state, mxcsr);
		size = MXCSR_AND_FLAGS_SIZE;
		अगर (__copy_from_user(&xsave->i387.mxcsr, ubuf + offset, size))
			वापस -EFAULT;
	पूर्ण

	/*
	 * The state that came in from userspace was user-state only.
	 * Mask all the user states out of 'xfeatures':
	 */
	xsave->header.xfeatures &= XFEATURE_MASK_SUPERVISOR_ALL;

	/*
	 * Add back in the features that came in from userspace:
	 */
	xsave->header.xfeatures |= hdr.xfeatures;

	वापस 0;
पूर्ण

/*
 * Save only supervisor states to the kernel buffer.  This blows away all
 * old states, and is पूर्णांकended to be used only in __fpu__restore_sig(), where
 * user states are restored from the user buffer.
 */
व्योम copy_supervisor_to_kernel(काष्ठा xregs_state *xstate)
अणु
	काष्ठा xstate_header *header;
	u64 max_bit, min_bit;
	u32 lmask, hmask;
	पूर्णांक err, i;

	अगर (WARN_ON(!boot_cpu_has(X86_FEATURE_XSAVES)))
		वापस;

	अगर (!xfeatures_mask_supervisor())
		वापस;

	max_bit = __fls(xfeatures_mask_supervisor());
	min_bit = __ffs(xfeatures_mask_supervisor());

	lmask = xfeatures_mask_supervisor();
	hmask = xfeatures_mask_supervisor() >> 32;
	XSTATE_OP(XSAVES, xstate, lmask, hmask, err);

	/* We should never fault when copying to a kernel buffer: */
	अगर (WARN_ON_FPU(err))
		वापस;

	/*
	 * At this poपूर्णांक, the buffer has only supervisor states and must be
	 * converted back to normal kernel क्रमmat.
	 */
	header = &xstate->header;
	header->xcomp_bv |= xfeatures_mask_all;

	/*
	 * This only moves states up in the buffer.  Start with
	 * the last state and move backwards so that states are
	 * not overwritten until after they are moved.  Note:
	 * स_हटाओ() allows overlapping src/dst buffers.
	 */
	क्रम (i = max_bit; i >= min_bit; i--) अणु
		u8 *xbuf = (u8 *)xstate;

		अगर (!((header->xfeatures >> i) & 1))
			जारी;

		/* Move xfeature 'i' पूर्णांकo its normal location */
		स_हटाओ(xbuf + xstate_comp_offsets[i],
			xbuf + xstate_supervisor_only_offsets[i],
			xstate_sizes[i]);
	पूर्ण
पूर्ण

/**
 * copy_dynamic_supervisor_to_kernel() - Save dynamic supervisor states to
 *                                       an xsave area
 * @xstate: A poपूर्णांकer to an xsave area
 * @mask: Represent the dynamic supervisor features saved पूर्णांकo the xsave area
 *
 * Only the dynamic supervisor states sets in the mask are saved पूर्णांकo the xsave
 * area (See the comment in XFEATURE_MASK_DYNAMIC क्रम the details of dynamic
 * supervisor feature). Besides the dynamic supervisor states, the legacy
 * region and XSAVE header are also saved पूर्णांकo the xsave area. The supervisor
 * features in the XFEATURE_MASK_SUPERVISOR_SUPPORTED and
 * XFEATURE_MASK_SUPERVISOR_UNSUPPORTED are not saved.
 *
 * The xsave area must be 64-bytes aligned.
 */
व्योम copy_dynamic_supervisor_to_kernel(काष्ठा xregs_state *xstate, u64 mask)
अणु
	u64 dynamic_mask = xfeatures_mask_dynamic() & mask;
	u32 lmask, hmask;
	पूर्णांक err;

	अगर (WARN_ON_FPU(!boot_cpu_has(X86_FEATURE_XSAVES)))
		वापस;

	अगर (WARN_ON_FPU(!dynamic_mask))
		वापस;

	lmask = dynamic_mask;
	hmask = dynamic_mask >> 32;

	XSTATE_OP(XSAVES, xstate, lmask, hmask, err);

	/* Should never fault when copying to a kernel buffer */
	WARN_ON_FPU(err);
पूर्ण

/**
 * copy_kernel_to_dynamic_supervisor() - Restore dynamic supervisor states from
 *                                       an xsave area
 * @xstate: A poपूर्णांकer to an xsave area
 * @mask: Represent the dynamic supervisor features restored from the xsave area
 *
 * Only the dynamic supervisor states sets in the mask are restored from the
 * xsave area (See the comment in XFEATURE_MASK_DYNAMIC क्रम the details of
 * dynamic supervisor feature). Besides the dynamic supervisor states, the
 * legacy region and XSAVE header are also restored from the xsave area. The
 * supervisor features in the XFEATURE_MASK_SUPERVISOR_SUPPORTED and
 * XFEATURE_MASK_SUPERVISOR_UNSUPPORTED are not restored.
 *
 * The xsave area must be 64-bytes aligned.
 */
व्योम copy_kernel_to_dynamic_supervisor(काष्ठा xregs_state *xstate, u64 mask)
अणु
	u64 dynamic_mask = xfeatures_mask_dynamic() & mask;
	u32 lmask, hmask;
	पूर्णांक err;

	अगर (WARN_ON_FPU(!boot_cpu_has(X86_FEATURE_XSAVES)))
		वापस;

	अगर (WARN_ON_FPU(!dynamic_mask))
		वापस;

	lmask = dynamic_mask;
	hmask = dynamic_mask >> 32;

	XSTATE_OP(XRSTORS, xstate, lmask, hmask, err);

	/* Should never fault when copying from a kernel buffer */
	WARN_ON_FPU(err);
पूर्ण

#अगर_घोषित CONFIG_PROC_PID_ARCH_STATUS
/*
 * Report the amount of समय elapsed in millisecond since last AVX512
 * use in the task.
 */
अटल व्योम avx512_status(काष्ठा seq_file *m, काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ बारtamp = READ_ONCE(task->thपढ़ो.fpu.avx512_बारtamp);
	दीर्घ delta;

	अगर (!बारtamp) अणु
		/*
		 * Report -1 अगर no AVX512 usage
		 */
		delta = -1;
	पूर्ण अन्यथा अणु
		delta = (दीर्घ)(jअगरfies - बारtamp);
		/*
		 * Cap to दीर्घ_उच्च अगर समय dअगरference > दीर्घ_उच्च
		 */
		अगर (delta < 0)
			delta = दीर्घ_उच्च;
		delta = jअगरfies_to_msecs(delta);
	पूर्ण

	seq_put_decimal_ll(m, "AVX512_elapsed_ms:\t", delta);
	seq_अ_दो(m, '\n');
पूर्ण

/*
 * Report architecture specअगरic inक्रमmation
 */
पूर्णांक proc_pid_arch_status(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	/*
	 * Report AVX512 state अगर the processor and build option supported.
	 */
	अगर (cpu_feature_enabled(X86_FEATURE_AVX512F))
		avx512_status(m, task);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_PID_ARCH_STATUS */
