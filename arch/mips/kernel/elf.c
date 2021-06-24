<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2014 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/binfmts.h>
#समावेश <linux/elf.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/cpu-info.h>

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT

/* Whether to accept legacy-NaN and 2008-NaN user binaries.  */
bool mips_use_nan_legacy;
bool mips_use_nan_2008;

/* FPU modes */
क्रमागत अणु
	FP_FRE,
	FP_FR0,
	FP_FR1,
पूर्ण;

/**
 * काष्ठा mode_req - ABI FPU mode requirements
 * @single:	The program being loaded needs an FPU but it will only issue
 *		single precision inकाष्ठाions meaning that it can execute in
 *		either FR0 or FR1.
 * @soft:	The soft(-भग्न) requirement means that the program being
 *		loaded needs has no FPU dependency at all (i.e. it has no
 *		FPU inकाष्ठाions).
 * @fr1:	The program being loaded depends on FPU being in FR=1 mode.
 * @frशेष:	The program being loaded depends on the शेष FPU mode.
 *		That is FR0 क्रम O32 and FR1 क्रम N32/N64.
 * @fre:	The program being loaded depends on FPU with FRE=1. This mode is
 *		a bridge which uses FR=1 whilst still being able to मुख्यtain
 *		full compatibility with pre-existing code using the O32 FP32
 *		ABI.
 *
 * More inक्रमmation about the FP ABIs can be found here:
 *
 * https://dmz-portal.mips.com/wiki/MIPS_O32_ABI_-_FR0_and_FR1_Interlinking#10.4.1._Basic_mode_set-up
 *
 */

काष्ठा mode_req अणु
	bool single;
	bool soft;
	bool fr1;
	bool frशेष;
	bool fre;
पूर्ण;

अटल स्थिर काष्ठा mode_req fpu_reqs[] = अणु
	[MIPS_ABI_FP_ANY]    = अणु true,  true,  true,  true,  true  पूर्ण,
	[MIPS_ABI_FP_DOUBLE] = अणु false, false, false, true,  true  पूर्ण,
	[MIPS_ABI_FP_SINGLE] = अणु true,  false, false, false, false पूर्ण,
	[MIPS_ABI_FP_SOFT]   = अणु false, true,  false, false, false पूर्ण,
	[MIPS_ABI_FP_OLD_64] = अणु false, false, false, false, false पूर्ण,
	[MIPS_ABI_FP_XX]     = अणु false, false, true,  true,  true  पूर्ण,
	[MIPS_ABI_FP_64]     = अणु false, false, true,  false, false पूर्ण,
	[MIPS_ABI_FP_64A]    = अणु false, false, true,  false, true  पूर्ण
पूर्ण;

/*
 * Mode requirements when .MIPS.abअगरlags is not present in the ELF.
 * Not present means that everything is acceptable except FR1.
 */
अटल काष्ठा mode_req none_req = अणु true, true, false, true, true पूर्ण;

पूर्णांक arch_elf_pt_proc(व्योम *_ehdr, व्योम *_phdr, काष्ठा file *elf,
		     bool is_पूर्णांकerp, काष्ठा arch_elf_state *state)
अणु
	जोड़ अणु
		काष्ठा elf32_hdr e32;
		काष्ठा elf64_hdr e64;
	पूर्ण *ehdr = _ehdr;
	काष्ठा elf32_phdr *phdr32 = _phdr;
	काष्ठा elf64_phdr *phdr64 = _phdr;
	काष्ठा mips_elf_abअगरlags_v0 abअगरlags;
	bool elf32;
	u32 flags;
	पूर्णांक ret;
	loff_t pos;

	elf32 = ehdr->e32.e_ident[EI_CLASS] == ELFCLASS32;
	flags = elf32 ? ehdr->e32.e_flags : ehdr->e64.e_flags;

	/* Let's see अगर this is an O32 ELF */
	अगर (elf32) अणु
		अगर (flags & EF_MIPS_FP64) अणु
			/*
			 * Set MIPS_ABI_FP_OLD_64 क्रम EF_MIPS_FP64. We will override it
			 * later अगर needed
			 */
			अगर (is_पूर्णांकerp)
				state->पूर्णांकerp_fp_abi = MIPS_ABI_FP_OLD_64;
			अन्यथा
				state->fp_abi = MIPS_ABI_FP_OLD_64;
		पूर्ण
		अगर (phdr32->p_type != PT_MIPS_ABIFLAGS)
			वापस 0;

		अगर (phdr32->p_filesz < माप(abअगरlags))
			वापस -EINVAL;
		pos = phdr32->p_offset;
	पूर्ण अन्यथा अणु
		अगर (phdr64->p_type != PT_MIPS_ABIFLAGS)
			वापस 0;
		अगर (phdr64->p_filesz < माप(abअगरlags))
			वापस -EINVAL;
		pos = phdr64->p_offset;
	पूर्ण

	ret = kernel_पढ़ो(elf, &abअगरlags, माप(abअगरlags), &pos);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != माप(abअगरlags))
		वापस -EIO;

	/* Record the required FP ABIs क्रम use by mips_check_elf */
	अगर (is_पूर्णांकerp)
		state->पूर्णांकerp_fp_abi = abअगरlags.fp_abi;
	अन्यथा
		state->fp_abi = abअगरlags.fp_abi;

	वापस 0;
पूर्ण

पूर्णांक arch_check_elf(व्योम *_ehdr, bool has_पूर्णांकerpreter, व्योम *_पूर्णांकerp_ehdr,
		   काष्ठा arch_elf_state *state)
अणु
	जोड़ अणु
		काष्ठा elf32_hdr e32;
		काष्ठा elf64_hdr e64;
	पूर्ण *ehdr = _ehdr;
	जोड़ अणु
		काष्ठा elf32_hdr e32;
		काष्ठा elf64_hdr e64;
	पूर्ण *iehdr = _पूर्णांकerp_ehdr;
	काष्ठा mode_req prog_req, पूर्णांकerp_req;
	पूर्णांक fp_abi, पूर्णांकerp_fp_abi, abi0, abi1, max_abi;
	bool elf32;
	u32 flags;

	elf32 = ehdr->e32.e_ident[EI_CLASS] == ELFCLASS32;
	flags = elf32 ? ehdr->e32.e_flags : ehdr->e64.e_flags;

	/*
	 * Determine the NaN personality, reject the binary अगर not allowed.
	 * Also ensure that any पूर्णांकerpreter matches the executable.
	 */
	अगर (flags & EF_MIPS_न_अंक2008) अणु
		अगर (mips_use_nan_2008)
			state->nan_2008 = 1;
		अन्यथा
			वापस -ENOEXEC;
	पूर्ण अन्यथा अणु
		अगर (mips_use_nan_legacy)
			state->nan_2008 = 0;
		अन्यथा
			वापस -ENOEXEC;
	पूर्ण
	अगर (has_पूर्णांकerpreter) अणु
		bool ielf32;
		u32 अगरlags;

		ielf32 = iehdr->e32.e_ident[EI_CLASS] == ELFCLASS32;
		अगरlags = ielf32 ? iehdr->e32.e_flags : iehdr->e64.e_flags;

		अगर ((flags ^ अगरlags) & EF_MIPS_न_अंक2008)
			वापस -ELIBBAD;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_MIPS_O32_FP64_SUPPORT))
		वापस 0;

	fp_abi = state->fp_abi;

	अगर (has_पूर्णांकerpreter) अणु
		पूर्णांकerp_fp_abi = state->पूर्णांकerp_fp_abi;

		abi0 = min(fp_abi, पूर्णांकerp_fp_abi);
		abi1 = max(fp_abi, पूर्णांकerp_fp_abi);
	पूर्ण अन्यथा अणु
		abi0 = abi1 = fp_abi;
	पूर्ण

	अगर (elf32 && !(flags & EF_MIPS_ABI2)) अणु
		/* Default to a mode capable of running code expecting FR=0 */
		state->overall_fp_mode = cpu_has_mips_r6 ? FP_FRE : FP_FR0;

		/* Allow all ABIs we know about */
		max_abi = MIPS_ABI_FP_64A;
	पूर्ण अन्यथा अणु
		/* MIPS64 code always uses FR=1, thus the शेष is easy */
		state->overall_fp_mode = FP_FR1;

		/* Disallow access to the various FPXX & FP64 ABIs */
		max_abi = MIPS_ABI_FP_SOFT;
	पूर्ण

	अगर ((abi0 > max_abi && abi0 != MIPS_ABI_FP_UNKNOWN) ||
	    (abi1 > max_abi && abi1 != MIPS_ABI_FP_UNKNOWN))
		वापस -ELIBBAD;

	/* It's समय to determine the FPU mode requirements */
	prog_req = (abi0 == MIPS_ABI_FP_UNKNOWN) ? none_req : fpu_reqs[abi0];
	पूर्णांकerp_req = (abi1 == MIPS_ABI_FP_UNKNOWN) ? none_req : fpu_reqs[abi1];

	/*
	 * Check whether the program's and interp's ABIs have a matching FPU
	 * mode requirement.
	 */
	prog_req.single = पूर्णांकerp_req.single && prog_req.single;
	prog_req.soft = पूर्णांकerp_req.soft && prog_req.soft;
	prog_req.fr1 = पूर्णांकerp_req.fr1 && prog_req.fr1;
	prog_req.frशेष = पूर्णांकerp_req.frशेष && prog_req.frशेष;
	prog_req.fre = पूर्णांकerp_req.fre && prog_req.fre;

	/*
	 * Determine the desired FPU mode
	 *
	 * Decision making:
	 *
	 * - We want FR_FRE अगर FRE=1 and both FR=1 and FR=0 are false. This
	 *   means that we have a combination of program and पूर्णांकerpreter
	 *   that inherently require the hybrid FP mode.
	 * - If FR1 and FRDEFAULT is true, that means we hit the any-abi or
	 *   fpxx हाल. This is because, in any-ABI (or no-ABI) we have no FPU
	 *   inकाष्ठाions so we करोn't care about the mode. We will simply use
	 *   the one preferred by the hardware. In fpxx हाल, that ABI can
	 *   handle both FR=1 and FR=0, so, again, we simply choose the one
	 *   preferred by the hardware. Next, अगर we only use single-precision
	 *   FPU inकाष्ठाions, and the शेष ABI FPU mode is not good
	 *   (ie single + any ABI combination), we set again the FPU mode to the
	 *   one is preferred by the hardware. Next, अगर we know that the code
	 *   will only use single-precision inकाष्ठाions, shown by single being
	 *   true but frशेष being false, then we again set the FPU mode to
	 *   the one that is preferred by the hardware.
	 * - We want FP_FR1 अगर that's the only matching mode and the शेष one
	 *   is not good.
	 * - Return with -ELIBADD अगर we can't find a matching FPU mode.
	 */
	अगर (prog_req.fre && !prog_req.frशेष && !prog_req.fr1)
		state->overall_fp_mode = FP_FRE;
	अन्यथा अगर ((prog_req.fr1 && prog_req.frशेष) ||
		 (prog_req.single && !prog_req.frशेष))
		/* Make sure 64-bit MIPS III/IV/64R1 will not pick FR1 */
		state->overall_fp_mode = ((raw_current_cpu_data.fpu_id & MIPS_FPIR_F64) &&
					  cpu_has_mips_r2_r6) ?
					  FP_FR1 : FP_FR0;
	अन्यथा अगर (prog_req.fr1)
		state->overall_fp_mode = FP_FR1;
	अन्यथा  अगर (!prog_req.fre && !prog_req.frशेष &&
		  !prog_req.fr1 && !prog_req.single && !prog_req.soft)
		वापस -ELIBBAD;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम set_thपढ़ो_fp_mode(पूर्णांक hybrid, पूर्णांक regs32)
अणु
	अगर (hybrid)
		set_thपढ़ो_flag(TIF_HYBRID_FPREGS);
	अन्यथा
		clear_thपढ़ो_flag(TIF_HYBRID_FPREGS);
	अगर (regs32)
		set_thपढ़ो_flag(TIF_32BIT_FPREGS);
	अन्यथा
		clear_thपढ़ो_flag(TIF_32BIT_FPREGS);
पूर्ण

व्योम mips_set_personality_fp(काष्ठा arch_elf_state *state)
अणु
	/*
	 * This function is only ever called क्रम O32 ELFs so we should
	 * not be worried about N32/N64 binaries.
	 */

	अगर (!IS_ENABLED(CONFIG_MIPS_O32_FP64_SUPPORT))
		वापस;

	चयन (state->overall_fp_mode) अणु
	हाल FP_FRE:
		set_thपढ़ो_fp_mode(1, 0);
		अवरोध;
	हाल FP_FR0:
		set_thपढ़ो_fp_mode(0, 1);
		अवरोध;
	हाल FP_FR1:
		set_thपढ़ो_fp_mode(0, 0);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * Select the IEEE 754 NaN encoding and ABS.fmt/NEG.fmt execution mode
 * in FCSR according to the ELF NaN personality.
 */
व्योम mips_set_personality_nan(काष्ठा arch_elf_state *state)
अणु
	काष्ठा cpuinfo_mips *c = &boot_cpu_data;
	काष्ठा task_काष्ठा *t = current;

	t->thपढ़ो.fpu.fcr31 = c->fpu_csr31;
	चयन (state->nan_2008) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		अगर (!(c->fpu_msk31 & FPU_CSR_न_अंक2008))
			t->thपढ़ो.fpu.fcr31 |= FPU_CSR_न_अंक2008;
		अगर (!(c->fpu_msk31 & FPU_CSR_ABS2008))
			t->thपढ़ो.fpu.fcr31 |= FPU_CSR_ABS2008;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_MIPS_FP_SUPPORT */

पूर्णांक mips_elf_पढ़ो_implies_exec(व्योम *elf_ex, पूर्णांक exstack)
अणु
	अगर (exstack != EXSTACK_DISABLE_X) अणु
		/* The binary करोesn't request a non-executable stack */
		वापस 1;
	पूर्ण

	अगर (!cpu_has_rixi) अणु
		/* The CPU करोesn't support non-executable memory */
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mips_elf_पढ़ो_implies_exec);
