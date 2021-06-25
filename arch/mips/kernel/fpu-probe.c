<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Processor capabilities determination functions.
 *
 * Copyright (C) xxxx  the Anonymous
 * Copyright (C) 1994 - 2006 Ralf Baechle
 * Copyright (C) 2003, 2004  Maciej W. Rozycki
 * Copyright (C) 2001, 2004, 2011, 2012	 MIPS Technologies, Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/mipsregs.h>

#समावेश "fpu-probe.h"

/*
 * Get the FPU Implementation/Revision.
 */
अटल अंतरभूत अचिन्हित दीर्घ cpu_get_fpu_id(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp, fpu_id;

	पंचांगp = पढ़ो_c0_status();
	__enable_fpu(FPU_AS_IS);
	fpu_id = पढ़ो_32bit_cp1_रेजिस्टर(CP1_REVISION);
	ग_लिखो_c0_status(पंचांगp);
	वापस fpu_id;
पूर्ण

/*
 * Check अगर the CPU has an बाह्यal FPU.
 */
पूर्णांक __cpu_has_fpu(व्योम)
अणु
	वापस (cpu_get_fpu_id() & FPIR_IMP_MASK) != FPIR_IMP_NONE;
पूर्ण

/*
 * Determine the FCSR mask क्रम FPU hardware.
 */
अटल अंतरभूत व्योम cpu_set_fpu_fcsr_mask(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित दीर्घ sr, mask, fcsr, fcsr0, fcsr1;

	fcsr = c->fpu_csr31;
	mask = FPU_CSR_ALL_X | FPU_CSR_ALL_E | FPU_CSR_ALL_S | FPU_CSR_RM;

	sr = पढ़ो_c0_status();
	__enable_fpu(FPU_AS_IS);

	fcsr0 = fcsr & mask;
	ग_लिखो_32bit_cp1_रेजिस्टर(CP1_STATUS, fcsr0);
	fcsr0 = पढ़ो_32bit_cp1_रेजिस्टर(CP1_STATUS);

	fcsr1 = fcsr | ~mask;
	ग_लिखो_32bit_cp1_रेजिस्टर(CP1_STATUS, fcsr1);
	fcsr1 = पढ़ो_32bit_cp1_रेजिस्टर(CP1_STATUS);

	ग_लिखो_32bit_cp1_रेजिस्टर(CP1_STATUS, fcsr);

	ग_लिखो_c0_status(sr);

	c->fpu_msk31 = ~(fcsr0 ^ fcsr1) & ~mask;
पूर्ण

/*
 * Determine the IEEE 754 NaN encodings and ABS.fmt/NEG.fmt execution modes
 * supported by FPU hardware.
 */
अटल व्योम cpu_set_fpu_2008(काष्ठा cpuinfo_mips *c)
अणु
	अगर (c->isa_level & (MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
			    MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
			    MIPS_CPU_ISA_M32R5 | MIPS_CPU_ISA_M64R5 |
			    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6)) अणु
		अचिन्हित दीर्घ sr, fir, fcsr, fcsr0, fcsr1;

		sr = पढ़ो_c0_status();
		__enable_fpu(FPU_AS_IS);

		fir = पढ़ो_32bit_cp1_रेजिस्टर(CP1_REVISION);
		अगर (fir & MIPS_FPIR_HAS2008) अणु
			fcsr = पढ़ो_32bit_cp1_रेजिस्टर(CP1_STATUS);

			/*
			 * MAC2008 toolchain never landed in real world, so
			 * we're only testing whether it can be disabled and
			 *  करोn't try to enabled it.
			 */
			fcsr0 = fcsr & ~(FPU_CSR_ABS2008 | FPU_CSR_न_अंक2008 |
					 FPU_CSR_MAC2008);
			ग_लिखो_32bit_cp1_रेजिस्टर(CP1_STATUS, fcsr0);
			fcsr0 = पढ़ो_32bit_cp1_रेजिस्टर(CP1_STATUS);

			fcsr1 = fcsr | FPU_CSR_ABS2008 | FPU_CSR_न_अंक2008;
			ग_लिखो_32bit_cp1_रेजिस्टर(CP1_STATUS, fcsr1);
			fcsr1 = पढ़ो_32bit_cp1_रेजिस्टर(CP1_STATUS);

			ग_लिखो_32bit_cp1_रेजिस्टर(CP1_STATUS, fcsr);

			अगर (c->isa_level & (MIPS_CPU_ISA_M32R2 |
					    MIPS_CPU_ISA_M64R2)) अणु
				/*
				 * The bit क्रम MAC2008 might be reused by R6
				 * in future, so we only test क्रम R2-R5.
				 */
				अगर (fcsr0 & FPU_CSR_MAC2008)
					c->options |= MIPS_CPU_MAC_2008_ONLY;
			पूर्ण

			अगर (!(fcsr0 & FPU_CSR_न_अंक2008))
				c->options |= MIPS_CPU_न_अंक_LEGACY;
			अगर (fcsr1 & FPU_CSR_न_अंक2008)
				c->options |= MIPS_CPU_न_अंक_2008;

			अगर ((fcsr0 ^ fcsr1) & FPU_CSR_ABS2008)
				c->fpu_msk31 &= ~FPU_CSR_ABS2008;
			अन्यथा
				c->fpu_csr31 |= fcsr & FPU_CSR_ABS2008;

			अगर ((fcsr0 ^ fcsr1) & FPU_CSR_न_अंक2008)
				c->fpu_msk31 &= ~FPU_CSR_न_अंक2008;
			अन्यथा
				c->fpu_csr31 |= fcsr & FPU_CSR_न_अंक2008;
		पूर्ण अन्यथा अणु
			c->options |= MIPS_CPU_न_अंक_LEGACY;
		पूर्ण

		ग_लिखो_c0_status(sr);
	पूर्ण अन्यथा अणु
		c->options |= MIPS_CPU_न_अंक_LEGACY;
	पूर्ण
पूर्ण

/*
 * IEEE 754 conक्रमmance mode to use.  Affects the NaN encoding and the
 * ABS.fmt/NEG.fmt execution mode.
 */
अटल क्रमागत अणु STRICT, LEGACY, STD2008, RELAXED पूर्ण ieee754 = STRICT;

/*
 * Set the IEEE 754 NaN encodings and the ABS.fmt/NEG.fmt execution modes
 * to support by the FPU emulator according to the IEEE 754 conक्रमmance
 * mode selected.  Note that "relaxed" straps the emulator so that it
 * allows 2008-NaN binaries even क्रम legacy processors.
 */
अटल व्योम cpu_set_nofpu_2008(काष्ठा cpuinfo_mips *c)
अणु
	c->options &= ~(MIPS_CPU_न_अंक_2008 | MIPS_CPU_न_अंक_LEGACY);
	c->fpu_csr31 &= ~(FPU_CSR_ABS2008 | FPU_CSR_न_अंक2008);
	c->fpu_msk31 &= ~(FPU_CSR_ABS2008 | FPU_CSR_न_अंक2008);

	चयन (ieee754) अणु
	हाल STRICT:
		अगर (c->isa_level & (MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
				    MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
				    MIPS_CPU_ISA_M32R5 | MIPS_CPU_ISA_M64R5 |
				    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6)) अणु
			c->options |= MIPS_CPU_न_अंक_2008 | MIPS_CPU_न_अंक_LEGACY;
		पूर्ण अन्यथा अणु
			c->options |= MIPS_CPU_न_अंक_LEGACY;
			c->fpu_msk31 |= FPU_CSR_ABS2008 | FPU_CSR_न_अंक2008;
		पूर्ण
		अवरोध;
	हाल LEGACY:
		c->options |= MIPS_CPU_न_अंक_LEGACY;
		c->fpu_msk31 |= FPU_CSR_ABS2008 | FPU_CSR_न_अंक2008;
		अवरोध;
	हाल STD2008:
		c->options |= MIPS_CPU_न_अंक_2008;
		c->fpu_csr31 |= FPU_CSR_ABS2008 | FPU_CSR_न_अंक2008;
		c->fpu_msk31 |= FPU_CSR_ABS2008 | FPU_CSR_न_अंक2008;
		अवरोध;
	हाल RELAXED:
		c->options |= MIPS_CPU_न_अंक_2008 | MIPS_CPU_न_अंक_LEGACY;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Override the IEEE 754 NaN encoding and ABS.fmt/NEG.fmt execution mode
 * according to the "ieee754=" parameter.
 */
अटल व्योम cpu_set_nan_2008(काष्ठा cpuinfo_mips *c)
अणु
	चयन (ieee754) अणु
	हाल STRICT:
		mips_use_nan_legacy = !!cpu_has_nan_legacy;
		mips_use_nan_2008 = !!cpu_has_nan_2008;
		अवरोध;
	हाल LEGACY:
		mips_use_nan_legacy = !!cpu_has_nan_legacy;
		mips_use_nan_2008 = !cpu_has_nan_legacy;
		अवरोध;
	हाल STD2008:
		mips_use_nan_legacy = !cpu_has_nan_2008;
		mips_use_nan_2008 = !!cpu_has_nan_2008;
		अवरोध;
	हाल RELAXED:
		mips_use_nan_legacy = true;
		mips_use_nan_2008 = true;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * IEEE 754 NaN encoding and ABS.fmt/NEG.fmt execution mode override
 * settings:
 *
 * strict:  accept binaries that request a NaN encoding supported by the FPU
 * legacy:  only accept legacy-NaN binaries
 * 2008:    only accept 2008-NaN binaries
 * relaxed: accept any binaries regardless of whether supported by the FPU
 */
अटल पूर्णांक __init ieee754_setup(अक्षर *s)
अणु
	अगर (!s)
		वापस -1;
	अन्यथा अगर (!म_भेद(s, "strict"))
		ieee754 = STRICT;
	अन्यथा अगर (!म_भेद(s, "legacy"))
		ieee754 = LEGACY;
	अन्यथा अगर (!म_भेद(s, "2008"))
		ieee754 = STD2008;
	अन्यथा अगर (!म_भेद(s, "relaxed"))
		ieee754 = RELAXED;
	अन्यथा
		वापस -1;

	अगर (!(boot_cpu_data.options & MIPS_CPU_FPU))
		cpu_set_nofpu_2008(&boot_cpu_data);
	cpu_set_nan_2008(&boot_cpu_data);

	वापस 0;
पूर्ण

early_param("ieee754", ieee754_setup);

/*
 * Set the FIR feature flags क्रम the FPU emulator.
 */
अटल व्योम cpu_set_nofpu_id(काष्ठा cpuinfo_mips *c)
अणु
	u32 value;

	value = 0;
	अगर (c->isa_level & (MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
			    MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
			    MIPS_CPU_ISA_M32R5 | MIPS_CPU_ISA_M64R5 |
			    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6))
		value |= MIPS_FPIR_D | MIPS_FPIR_S;
	अगर (c->isa_level & (MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
			    MIPS_CPU_ISA_M32R5 | MIPS_CPU_ISA_M64R5 |
			    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6))
		value |= MIPS_FPIR_F64 | MIPS_FPIR_L | MIPS_FPIR_W;
	अगर (c->options & MIPS_CPU_न_अंक_2008)
		value |= MIPS_FPIR_HAS2008;
	c->fpu_id = value;
पूर्ण

/* Determined FPU emulator mask to use क्रम the boot CPU with "nofpu".  */
अटल अचिन्हित पूर्णांक mips_nofpu_msk31;

/*
 * Set options क्रम FPU hardware.
 */
व्योम cpu_set_fpu_opts(काष्ठा cpuinfo_mips *c)
अणु
	c->fpu_id = cpu_get_fpu_id();
	mips_nofpu_msk31 = c->fpu_msk31;

	अगर (c->isa_level & (MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
			    MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
			    MIPS_CPU_ISA_M32R5 | MIPS_CPU_ISA_M64R5 |
			    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6)) अणु
		अगर (c->fpu_id & MIPS_FPIR_3D)
			c->ases |= MIPS_ASE_MIPS3D;
		अगर (c->fpu_id & MIPS_FPIR_UFRP)
			c->options |= MIPS_CPU_UFR;
		अगर (c->fpu_id & MIPS_FPIR_FREP)
			c->options |= MIPS_CPU_FRE;
	पूर्ण

	cpu_set_fpu_fcsr_mask(c);
	cpu_set_fpu_2008(c);
	cpu_set_nan_2008(c);
पूर्ण

/*
 * Set options क्रम the FPU emulator.
 */
व्योम cpu_set_nofpu_opts(काष्ठा cpuinfo_mips *c)
अणु
	c->options &= ~MIPS_CPU_FPU;
	c->fpu_msk31 = mips_nofpu_msk31;

	cpu_set_nofpu_2008(c);
	cpu_set_nan_2008(c);
	cpu_set_nofpu_id(c);
पूर्ण

पूर्णांक mips_fpu_disabled;

अटल पूर्णांक __init fpu_disable(अक्षर *s)
अणु
	cpu_set_nofpu_opts(&boot_cpu_data);
	mips_fpu_disabled = 1;

	वापस 1;
पूर्ण

__setup("nofpu", fpu_disable);

