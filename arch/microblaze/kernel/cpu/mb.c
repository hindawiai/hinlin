<शैली गुरु>
/*
 * CPU-version specअगरic code
 *
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2006-2009 PetaLogix
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/cpu.h>
#समावेश <linux/initrd.h>

#समावेश <linux/bug.h>
#समावेश <यंत्र/cpuinfo.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <linux/param.h>
#समावेश <यंत्र/pvr.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>

अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	अक्षर *fpga_family = "Unknown";
	अक्षर *cpu_ver = "Unknown";
	पूर्णांक i;

	/* Denormalised to get the fpga family string */
	क्रम (i = 0; family_string_lookup[i].s != शून्य; i++) अणु
		अगर (cpuinfo.fpga_family_code == family_string_lookup[i].k) अणु
			fpga_family = (अक्षर *)family_string_lookup[i].s;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Denormalised to get the hw version string */
	क्रम (i = 0; cpu_ver_lookup[i].s != शून्य; i++) अणु
		अगर (cpuinfo.ver_code == cpu_ver_lookup[i].k) अणु
			cpu_ver = (अक्षर *)cpu_ver_lookup[i].s;
			अवरोध;
		पूर्ण
	पूर्ण

	seq_म_लिखो(m,
		   "CPU-Family:	MicroBlaze\n"
		   "FPGA-Arch:	%s\n"
		   "CPU-Ver:	%s, %s endian\n"
		   "CPU-MHz:	%d.%02d\n"
		   "BogoMips:	%lu.%02lu\n",
		   fpga_family,
		   cpu_ver,
		   cpuinfo.endian ? "little" : "big",
		   cpuinfo.cpu_घड़ी_freq / 1000000,
		   cpuinfo.cpu_घड़ी_freq % 1000000,
		   loops_per_jअगरfy / (500000 / HZ),
		   (loops_per_jअगरfy / (5000 / HZ)) % 100);

	seq_म_लिखो(m,
		   "HW:\n Shift:\t\t%s\n"
		   " MSR:\t\t%s\n"
		   " PCMP:\t\t%s\n"
		   " DIV:\t\t%s\n",
		   (cpuinfo.use_instr & PVR0_USE_BARREL_MASK) ? "yes" : "no",
		   (cpuinfo.use_instr & PVR2_USE_MSR_INSTR) ? "yes" : "no",
		   (cpuinfo.use_instr & PVR2_USE_PCMP_INSTR) ? "yes" : "no",
		   (cpuinfo.use_instr & PVR0_USE_DIV_MASK) ? "yes" : "no");

	seq_म_लिखो(m, " MMU:\t\t%x\n", cpuinfo.mmu);

	seq_म_लिखो(m,
		   " MUL:\t\t%s\n"
		   " FPU:\t\t%s\n",
		   (cpuinfo.use_mult & PVR2_USE_MUL64_MASK) ? "v2" :
		   (cpuinfo.use_mult & PVR0_USE_HW_MUL_MASK) ? "v1" : "no",
		   (cpuinfo.use_fpu & PVR2_USE_FPU2_MASK) ? "v2" :
		   (cpuinfo.use_fpu & PVR0_USE_FPU_MASK) ? "v1" : "no");

	seq_म_लिखो(m,
		   " Exc:\t\t%s%s%s%s%s%s%s%s\n",
		   (cpuinfo.use_exc & PVR2_OPCODE_0x0_ILL_MASK) ? "op0x0 " : "",
		   (cpuinfo.use_exc & PVR2_UNALIGNED_EXC_MASK) ? "unal " : "",
		   (cpuinfo.use_exc & PVR2_ILL_OPCODE_EXC_MASK) ? "ill " : "",
		   (cpuinfo.use_exc & PVR2_IOPB_BUS_EXC_MASK) ? "iopb " : "",
		   (cpuinfo.use_exc & PVR2_DOPB_BUS_EXC_MASK) ? "dopb " : "",
		   (cpuinfo.use_exc & PVR2_DIV_ZERO_EXC_MASK) ? "zero " : "",
		   (cpuinfo.use_exc & PVR2_FPU_EXC_MASK) ? "fpu " : "",
		   (cpuinfo.use_exc & PVR2_USE_FSL_EXC) ? "fsl " : "");

	seq_म_लिखो(m,
		   "Stream-insns:\t%sprivileged\n",
		   cpuinfo.mmu_privins ? "un" : "");

	अगर (cpuinfo.use_icache)
		seq_म_लिखो(m,
			   "Icache:\t\t%ukB\tline length:\t%dB\n",
			   cpuinfo.icache_size >> 10,
			   cpuinfo.icache_line_length);
	अन्यथा
		seq_माला_दो(m, "Icache:\t\tno\n");

	अगर (cpuinfo.use_dcache) अणु
		seq_म_लिखो(m,
			   "Dcache:\t\t%ukB\tline length:\t%dB\n",
			   cpuinfo.dcache_size >> 10,
			   cpuinfo.dcache_line_length);
		seq_माला_दो(m, "Dcache-Policy:\t");
		अगर (cpuinfo.dcache_wb)
			seq_माला_दो(m, "write-back\n");
		अन्यथा
			seq_माला_दो(m, "write-through\n");
	पूर्ण अन्यथा अणु
		seq_माला_दो(m, "Dcache:\t\tno\n");
	पूर्ण

	seq_म_लिखो(m,
		   "HW-Debug:\t%s\n",
		   cpuinfo.hw_debug ? "yes" : "no");

	seq_म_लिखो(m,
		   "PVR-USR1:\t%02x\n"
		   "PVR-USR2:\t%08x\n",
		   cpuinfo.pvr_user1,
		   cpuinfo.pvr_user2);

	seq_म_लिखो(m, "Page size:\t%lu\n", PAGE_SIZE);

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	पूर्णांक i = *pos;

	वापस i < NR_CPUS ? (व्योम *) (i + 1) : शून्य;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस c_start(m, pos);
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start = c_start,
	.next = c_next,
	.stop = c_stop,
	.show = show_cpuinfo,
पूर्ण;
