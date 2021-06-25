<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/smp.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-info.h>
#समावेश <यंत्र/elf.h>

#समावेश <loongson_regs.h>
#समावेश <cpucfg-emul.h>

अटल bool is_loongson(काष्ठा cpuinfo_mips *c)
अणु
	चयन (c->processor_id & PRID_COMP_MASK) अणु
	हाल PRID_COMP_LEGACY:
		वापस ((c->processor_id & PRID_IMP_MASK) ==
			PRID_IMP_LOONGSON_64C);

	हाल PRID_COMP_LOONGSON:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल u32 get_loongson_fprev(काष्ठा cpuinfo_mips *c)
अणु
	वापस c->fpu_id & LOONGSON_FPREV_MASK;
पूर्ण

अटल bool cpu_has_uca(व्योम)
अणु
	u32 diag = पढ़ो_c0_diag();
	u32 new_diag;

	अगर (diag & LOONGSON_DIAG_UCAC)
		/* UCA is alपढ़ोy enabled. */
		वापस true;

	/* See अगर UCAC bit can be flipped on. This should be safe. */
	new_diag = diag | LOONGSON_DIAG_UCAC;
	ग_लिखो_c0_diag(new_diag);
	new_diag = पढ़ो_c0_diag();
	ग_लिखो_c0_diag(diag);

	वापस (new_diag & LOONGSON_DIAG_UCAC) != 0;
पूर्ण

अटल व्योम probe_uca(काष्ठा cpuinfo_mips *c)
अणु
	अगर (cpu_has_uca())
		c->loongson3_cpucfg_data[0] |= LOONGSON_CFG1_LSUCA;
पूर्ण

अटल व्योम decode_loongson_config6(काष्ठा cpuinfo_mips *c)
अणु
	u32 config6 = पढ़ो_c0_config6();

	अगर (config6 & LOONGSON_CONF6_SFBEN)
		c->loongson3_cpucfg_data[0] |= LOONGSON_CFG1_SFBP;
	अगर (config6 & LOONGSON_CONF6_LLEXC)
		c->loongson3_cpucfg_data[0] |= LOONGSON_CFG1_LLEXC;
	अगर (config6 & LOONGSON_CONF6_SCRAND)
		c->loongson3_cpucfg_data[0] |= LOONGSON_CFG1_SCRAND;
पूर्ण

अटल व्योम patch_cpucfg_sel1(काष्ठा cpuinfo_mips *c)
अणु
	u64 ases = c->ases;
	u64 options = c->options;
	u32 data = c->loongson3_cpucfg_data[0];

	अगर (options & MIPS_CPU_FPU) अणु
		data |= LOONGSON_CFG1_FP;
		data |= get_loongson_fprev(c) << LOONGSON_CFG1_FPREV_OFFSET;
	पूर्ण
	अगर (ases & MIPS_ASE_LOONGSON_MMI)
		data |= LOONGSON_CFG1_MMI;
	अगर (ases & MIPS_ASE_MSA)
		data |= LOONGSON_CFG1_MSA1;

	c->loongson3_cpucfg_data[0] = data;
पूर्ण

अटल व्योम patch_cpucfg_sel2(काष्ठा cpuinfo_mips *c)
अणु
	u64 ases = c->ases;
	u64 options = c->options;
	u32 data = c->loongson3_cpucfg_data[1];

	अगर (ases & MIPS_ASE_LOONGSON_EXT)
		data |= LOONGSON_CFG2_LEXT1;
	अगर (ases & MIPS_ASE_LOONGSON_EXT2)
		data |= LOONGSON_CFG2_LEXT2;
	अगर (options & MIPS_CPU_LDPTE)
		data |= LOONGSON_CFG2_LSPW;

	अगर (ases & MIPS_ASE_VZ)
		data |= LOONGSON_CFG2_LVZP;
	अन्यथा
		data &= ~LOONGSON_CFG2_LVZREV;

	c->loongson3_cpucfg_data[1] = data;
पूर्ण

अटल व्योम patch_cpucfg_sel3(काष्ठा cpuinfo_mips *c)
अणु
	u64 ases = c->ases;
	u32 data = c->loongson3_cpucfg_data[2];

	अगर (ases & MIPS_ASE_LOONGSON_CAM) अणु
		data |= LOONGSON_CFG3_LCAMP;
	पूर्ण अन्यथा अणु
		data &= ~LOONGSON_CFG3_LCAMREV;
		data &= ~LOONGSON_CFG3_LCAMNUM;
		data &= ~LOONGSON_CFG3_LCAMKW;
		data &= ~LOONGSON_CFG3_LCAMVW;
	पूर्ण

	c->loongson3_cpucfg_data[2] = data;
पूर्ण

व्योम loongson3_cpucfg_synthesize_data(काष्ठा cpuinfo_mips *c)
अणु
	/* Only engage the logic on Loongson processors. */
	अगर (!is_loongson(c))
		वापस;

	/* CPUs with CPUCFG support करोn't need to synthesize anything. */
	अगर (cpu_has_cfg())
		जाओ have_cpucfg_now;

	c->loongson3_cpucfg_data[0] = 0;
	c->loongson3_cpucfg_data[1] = 0;
	c->loongson3_cpucfg_data[2] = 0;

	/* Add CPUCFG features non-discoverable otherwise. */
	चयन (c->processor_id & (PRID_IMP_MASK | PRID_REV_MASK)) अणु
	हाल PRID_IMP_LOONGSON_64R | PRID_REV_LOONGSON2K_R1_0:
	हाल PRID_IMP_LOONGSON_64R | PRID_REV_LOONGSON2K_R1_1:
	हाल PRID_IMP_LOONGSON_64R | PRID_REV_LOONGSON2K_R1_2:
	हाल PRID_IMP_LOONGSON_64R | PRID_REV_LOONGSON2K_R1_3:
		decode_loongson_config6(c);
		probe_uca(c);

		c->loongson3_cpucfg_data[0] |= (LOONGSON_CFG1_LSLDR0 |
			LOONGSON_CFG1_LSSYNCI | LOONGSON_CFG1_LLSYNC |
			LOONGSON_CFG1_TGTSYNC);
		c->loongson3_cpucfg_data[1] |= (LOONGSON_CFG2_LBT1 |
			LOONGSON_CFG2_LBT2 | LOONGSON_CFG2_LPMP |
			LOONGSON_CFG2_LPM_REV2);
		c->loongson3_cpucfg_data[2] = 0;
		अवरोध;

	हाल PRID_IMP_LOONGSON_64C | PRID_REV_LOONGSON3A_R1:
		c->loongson3_cpucfg_data[0] |= (LOONGSON_CFG1_LSLDR0 |
			LOONGSON_CFG1_LSSYNCI | LOONGSON_CFG1_LSUCA |
			LOONGSON_CFG1_LLSYNC | LOONGSON_CFG1_TGTSYNC);
		c->loongson3_cpucfg_data[1] |= (LOONGSON_CFG2_LBT1 |
			LOONGSON_CFG2_LPMP | LOONGSON_CFG2_LPM_REV1);
		c->loongson3_cpucfg_data[2] |= (
			LOONGSON_CFG3_LCAM_REV1 |
			LOONGSON_CFG3_LCAMNUM_REV1 |
			LOONGSON_CFG3_LCAMKW_REV1 |
			LOONGSON_CFG3_LCAMVW_REV1);
		अवरोध;

	हाल PRID_IMP_LOONGSON_64C | PRID_REV_LOONGSON3B_R1:
	हाल PRID_IMP_LOONGSON_64C | PRID_REV_LOONGSON3B_R2:
		c->loongson3_cpucfg_data[0] |= (LOONGSON_CFG1_LSLDR0 |
			LOONGSON_CFG1_LSSYNCI | LOONGSON_CFG1_LSUCA |
			LOONGSON_CFG1_LLSYNC | LOONGSON_CFG1_TGTSYNC);
		c->loongson3_cpucfg_data[1] |= (LOONGSON_CFG2_LBT1 |
			LOONGSON_CFG2_LPMP | LOONGSON_CFG2_LPM_REV1);
		c->loongson3_cpucfg_data[2] |= (
			LOONGSON_CFG3_LCAM_REV1 |
			LOONGSON_CFG3_LCAMNUM_REV1 |
			LOONGSON_CFG3_LCAMKW_REV1 |
			LOONGSON_CFG3_LCAMVW_REV1);
		अवरोध;

	हाल PRID_IMP_LOONGSON_64C | PRID_REV_LOONGSON3A_R2_0:
	हाल PRID_IMP_LOONGSON_64C | PRID_REV_LOONGSON3A_R2_1:
	हाल PRID_IMP_LOONGSON_64C | PRID_REV_LOONGSON3A_R3_0:
	हाल PRID_IMP_LOONGSON_64C | PRID_REV_LOONGSON3A_R3_1:
		decode_loongson_config6(c);
		probe_uca(c);

		c->loongson3_cpucfg_data[0] |= (LOONGSON_CFG1_CNT64 |
			LOONGSON_CFG1_LSLDR0 | LOONGSON_CFG1_LSPREF |
			LOONGSON_CFG1_LSPREFX | LOONGSON_CFG1_LSSYNCI |
			LOONGSON_CFG1_LLSYNC | LOONGSON_CFG1_TGTSYNC);
		c->loongson3_cpucfg_data[1] |= (LOONGSON_CFG2_LBT1 |
			LOONGSON_CFG2_LBT2 | LOONGSON_CFG2_LBTMMU |
			LOONGSON_CFG2_LPMP | LOONGSON_CFG2_LPM_REV1 |
			LOONGSON_CFG2_LVZ_REV1);
		c->loongson3_cpucfg_data[2] |= (LOONGSON_CFG3_LCAM_REV1 |
			LOONGSON_CFG3_LCAMNUM_REV1 |
			LOONGSON_CFG3_LCAMKW_REV1 |
			LOONGSON_CFG3_LCAMVW_REV1);
		अवरोध;

	शेष:
		/* It is possible that some future Loongson cores still करो
		 * not have CPUCFG, so करो not emulate anything क्रम these
		 * cores.
		 */
		वापस;
	पूर्ण

	/* This feature is set by firmware, but all known Loongson-64 प्रणालीs
	 * are configured this way.
	 */
	c->loongson3_cpucfg_data[0] |= LOONGSON_CFG1_CDMAP;

	/* Patch in dynamically probed bits. */
	patch_cpucfg_sel1(c);
	patch_cpucfg_sel2(c);
	patch_cpucfg_sel3(c);

have_cpucfg_now:
	/* We have usable CPUCFG now, emulated or not.
	 * Announce CPUCFG availability to userspace via hwcap.
	 */
	elf_hwcap |= HWCAP_LOONGSON_CPUCFG;
पूर्ण
