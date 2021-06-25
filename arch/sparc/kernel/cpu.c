<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* cpu.c: Dinky routines to look क्रम the kind of Sparc cpu
 *        we are on.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/head.h>
#समावेश <यंत्र/psr.h>
#समावेश <यंत्र/mbus.h>
#समावेश <यंत्र/cpudata.h>

#समावेश "kernel.h"
#समावेश "entry.h"

DEFINE_PER_CPU(cpuinfo_sparc, __cpu_data) = अणु 0 पूर्ण;
EXPORT_PER_CPU_SYMBOL(__cpu_data);

पूर्णांक ncpus_probed;
अचिन्हित पूर्णांक fsr_storage;

काष्ठा cpu_info अणु
	पूर्णांक psr_vers;
	स्थिर अक्षर *name;
	स्थिर अक्षर *pmu_name;
पूर्ण;

काष्ठा fpu_info अणु
	पूर्णांक fp_vers;
	स्थिर अक्षर *name;
पूर्ण;

#घोषणा NOCPU 8
#घोषणा NOFPU 8

काष्ठा manufacturer_info अणु
	पूर्णांक psr_impl;
	काष्ठा cpu_info cpu_info[NOCPU];
	काष्ठा fpu_info fpu_info[NOFPU];
पूर्ण;

#घोषणा CPU(ver, _name) \
अणु .psr_vers = ver, .name = _name पूर्ण

#घोषणा CPU_PMU(ver, _name, _pmu_name)	\
अणु .psr_vers = ver, .name = _name, .pmu_name = _pmu_name पूर्ण

#घोषणा FPU(ver, _name) \
अणु .fp_vers = ver, .name = _name पूर्ण

अटल स्थिर काष्ठा manufacturer_info __initस्थिर manufacturer_info[] = अणु
अणु
	0,
	/* Sun4/100, 4/200, SLC */
	.cpu_info = अणु
		CPU(0, "Fujitsu  MB86900/1A or LSI L64831 SparcKIT-40"),
		/* borned STP1012PGA */
		CPU(4,  "Fujitsu  MB86904"),
		CPU(5, "Fujitsu TurboSparc MB86907"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(0, "Fujitsu MB86910 or Weitek WTL1164/5"),
		FPU(1, "Fujitsu MB86911 or Weitek WTL1164/5 or LSI L64831"),
		FPU(2, "LSI Logic L64802 or Texas Instruments ACT8847"),
		/* SparcStation SLC, SparcStation1 */
		FPU(3, "Weitek WTL3170/2"),
		/* SPARCstation-5 */
		FPU(4, "Lsi Logic/Meiko L64804 or compatible"),
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	1,
	.cpu_info = अणु
		/* SparcStation2, SparcServer 490 & 690 */
		CPU(0, "LSI Logic Corporation - L64811"),
		/* SparcStation2 */
		CPU(1, "Cypress/ROSS CY7C601"),
		/* Embedded controller */
		CPU(3, "Cypress/ROSS CY7C611"),
		/* Ross Technologies HyperSparc */
		CPU(0xf, "ROSS HyperSparc RT620"),
		CPU(0xe, "ROSS HyperSparc RT625 or RT626"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(0, "ROSS HyperSparc combined IU/FPU"),
		FPU(1, "Lsi Logic L64814"),
		FPU(2, "Texas Instruments TMS390-C602A"),
		FPU(3, "Cypress CY7C602 FPU"),
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	2,
	.cpu_info = अणु
		/* ECL Implementation, CRAY S-MP Supercomputer... AIEEE! */
		/* Someone please ग_लिखो the code to support this beast! ;) */
		CPU(0, "Bipolar Integrated Technology - B5010"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	3,
	.cpu_info = अणु
		CPU(0, "LSI Logic Corporation - unknown-type"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	PSR_IMPL_TI,
	.cpu_info = अणु
		CPU(0, "Texas Instruments, Inc. - SuperSparc-(II)"),
		/* SparcClassic  --  borned STP1010TAB-50*/
		CPU(1, "Texas Instruments, Inc. - MicroSparc"),
		CPU(2, "Texas Instruments, Inc. - MicroSparc II"),
		CPU(3, "Texas Instruments, Inc. - SuperSparc 51"),
		CPU(4, "Texas Instruments, Inc. - SuperSparc 61"),
		CPU(5, "Texas Instruments, Inc. - unknown"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		/* SuperSparc 50 module */
		FPU(0, "SuperSparc on-chip FPU"),
		/* SparcClassic */
		FPU(4, "TI MicroSparc on chip FPU"),
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	5,
	.cpu_info = अणु
		CPU(0, "Matsushita - MN10501"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(0, "Matsushita MN10501"),
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	6,
	.cpu_info = अणु
		CPU(0, "Philips Corporation - unknown"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	7,
	.cpu_info = अणु
		CPU(0, "Harvest VLSI Design Center, Inc. - unknown"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	8,
	.cpu_info = अणु
		CPU(0, "Systems and Processes Engineering Corporation (SPEC)"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	9,
	.cpu_info = अणु
		/* Gallium arsenide 200MHz, BOOOOGOOOOMIPS!!! */
		CPU(0, "Fujitsu or Weitek Power-UP"),
		CPU(1, "Fujitsu or Weitek Power-UP"),
		CPU(2, "Fujitsu or Weitek Power-UP"),
		CPU(3, "Fujitsu or Weitek Power-UP"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(3, "Fujitsu or Weitek on-chip FPU"),
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	PSR_IMPL_LEON,		/* Aeroflex Gaisler */
	.cpu_info = अणु
		CPU(3, "LEON"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(2, "GRFPU"),
		FPU(3, "GRFPU-Lite"),
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	0x17,
	.cpu_info = अणु
		CPU_PMU(0x10, "TI UltraSparc I   (SpitFire)", "ultra12"),
		CPU_PMU(0x11, "TI UltraSparc II  (BlackBird)", "ultra12"),
		CPU_PMU(0x12, "TI UltraSparc IIi (Sabre)", "ultra12"),
		CPU_PMU(0x13, "TI UltraSparc IIe (Hummingbird)", "ultra12"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(0x10, "UltraSparc I integrated FPU"),
		FPU(0x11, "UltraSparc II integrated FPU"),
		FPU(0x12, "UltraSparc IIi integrated FPU"),
		FPU(0x13, "UltraSparc IIe integrated FPU"),
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	0x22,
	.cpu_info = अणु
		CPU_PMU(0x10, "TI UltraSparc I   (SpitFire)", "ultra12"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(0x10, "UltraSparc I integrated FPU"),
		FPU(-1, शून्य)
	पूर्ण
पूर्ण,अणु
	0x3e,
	.cpu_info = अणु
		CPU_PMU(0x14, "TI UltraSparc III (Cheetah)", "ultra3"),
		CPU_PMU(0x15, "TI UltraSparc III+ (Cheetah+)", "ultra3+"),
		CPU_PMU(0x16, "TI UltraSparc IIIi (Jalapeno)", "ultra3i"),
		CPU_PMU(0x18, "TI UltraSparc IV (Jaguar)", "ultra3+"),
		CPU_PMU(0x19, "TI UltraSparc IV+ (Panther)", "ultra4+"),
		CPU_PMU(0x22, "TI UltraSparc IIIi+ (Serrano)", "ultra3i"),
		CPU(-1, शून्य)
	पूर्ण,
	.fpu_info = अणु
		FPU(0x14, "UltraSparc III integrated FPU"),
		FPU(0x15, "UltraSparc III+ integrated FPU"),
		FPU(0x16, "UltraSparc IIIi integrated FPU"),
		FPU(0x18, "UltraSparc IV integrated FPU"),
		FPU(0x19, "UltraSparc IV+ integrated FPU"),
		FPU(0x22, "UltraSparc IIIi+ integrated FPU"),
		FPU(-1, शून्य)
	पूर्ण
पूर्णपूर्ण;

/* In order to get the fpu type correct, you need to take the IDPROM's
 * machine type value पूर्णांकo consideration too.  I will fix this.
 */

अटल स्थिर अक्षर *sparc_cpu_type;
अटल स्थिर अक्षर *sparc_fpu_type;
स्थिर अक्षर *sparc_pmu_type;


अटल व्योम __init set_cpu_and_fpu(पूर्णांक psr_impl, पूर्णांक psr_vers, पूर्णांक fpu_vers)
अणु
	स्थिर काष्ठा manufacturer_info *manuf;
	पूर्णांक i;

	sparc_cpu_type = शून्य;
	sparc_fpu_type = शून्य;
	sparc_pmu_type = शून्य;
	manuf = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(manufacturer_info); i++)
	अणु
		अगर (psr_impl == manufacturer_info[i].psr_impl) अणु
			manuf = &manufacturer_info[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (manuf != शून्य)
	अणु
		स्थिर काष्ठा cpu_info *cpu;
		स्थिर काष्ठा fpu_info *fpu;

		cpu = &manuf->cpu_info[0];
		जबतक (cpu->psr_vers != -1)
		अणु
			अगर (cpu->psr_vers == psr_vers) अणु
				sparc_cpu_type = cpu->name;
				sparc_pmu_type = cpu->pmu_name;
				sparc_fpu_type = "No FPU";
				अवरोध;
			पूर्ण
			cpu++;
		पूर्ण
		fpu =  &manuf->fpu_info[0];
		जबतक (fpu->fp_vers != -1)
		अणु
			अगर (fpu->fp_vers == fpu_vers) अणु
				sparc_fpu_type = fpu->name;
				अवरोध;
			पूर्ण
			fpu++;
		पूर्ण
	पूर्ण
	अगर (sparc_cpu_type == शून्य)
	अणु
		prपूर्णांकk(KERN_ERR "CPU: Unknown chip, impl[0x%x] vers[0x%x]\n",
		       psr_impl, psr_vers);
		sparc_cpu_type = "Unknown CPU";
	पूर्ण
	अगर (sparc_fpu_type == शून्य)
	अणु
		prपूर्णांकk(KERN_ERR "FPU: Unknown chip, impl[0x%x] vers[0x%x]\n",
		       psr_impl, fpu_vers);
		sparc_fpu_type = "Unknown FPU";
	पूर्ण
	अगर (sparc_pmu_type == शून्य)
		sparc_pmu_type = "Unknown PMU";
पूर्ण

#अगर_घोषित CONFIG_SPARC32
अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *__unused)
अणु
	seq_म_लिखो(m,
		   "cpu\t\t: %s\n"
		   "fpu\t\t: %s\n"
		   "promlib\t\t: Version %d Revision %d\n"
		   "prom\t\t: %d.%d\n"
		   "type\t\t: %s\n"
		   "ncpus probed\t: %d\n"
		   "ncpus active\t: %d\n"
#अगर_अघोषित CONFIG_SMP
		   "CPU0Bogo\t: %lu.%02lu\n"
		   "CPU0ClkTck\t: %ld\n"
#पूर्ण_अगर
		   ,
		   sparc_cpu_type,
		   sparc_fpu_type ,
		   romvec->pv_romvers,
		   prom_rev,
		   romvec->pv_prपूर्णांकrev >> 16,
		   romvec->pv_prपूर्णांकrev & 0xffff,
		   &cputypval[0],
		   ncpus_probed,
		   num_online_cpus()
#अगर_अघोषित CONFIG_SMP
		   , cpu_data(0).udelay_val/(500000/HZ),
		   (cpu_data(0).udelay_val/(5000/HZ)) % 100,
		   cpu_data(0).घड़ी_प्रकारick
#पूर्ण_अगर
		);

#अगर_घोषित CONFIG_SMP
	smp_bogo(m);
#पूर्ण_अगर
	mmu_info(m);
#अगर_घोषित CONFIG_SMP
	smp_info(m);
#पूर्ण_अगर
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SPARC32 */

#अगर_घोषित CONFIG_SPARC64
अचिन्हित पूर्णांक dcache_parity_tl1_occurred;
अचिन्हित पूर्णांक icache_parity_tl1_occurred;


अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *__unused)
अणु
	seq_म_लिखो(m,
		   "cpu\t\t: %s\n"
		   "fpu\t\t: %s\n"
		   "pmu\t\t: %s\n"
		   "prom\t\t: %s\n"
		   "type\t\t: %s\n"
		   "ncpus probed\t: %d\n"
		   "ncpus active\t: %d\n"
		   "D$ parity tl1\t: %u\n"
		   "I$ parity tl1\t: %u\n"
#अगर_अघोषित CONFIG_SMP
		   "Cpu0ClkTck\t: %016lx\n"
#पूर्ण_अगर
		   ,
		   sparc_cpu_type,
		   sparc_fpu_type,
		   sparc_pmu_type,
		   prom_version,
		   ((tlb_type == hypervisor) ?
		    "sun4v" :
		    "sun4u"),
		   ncpus_probed,
		   num_online_cpus(),
		   dcache_parity_tl1_occurred,
		   icache_parity_tl1_occurred
#अगर_अघोषित CONFIG_SMP
		   , cpu_data(0).घड़ी_प्रकारick
#पूर्ण_अगर
		);
	cpucap_info(m);
#अगर_घोषित CONFIG_SMP
	smp_bogo(m);
#पूर्ण_अगर
	mmu_info(m);
#अगर_घोषित CONFIG_SMP
	smp_info(m);
#पूर्ण_अगर
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SPARC64 */

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	/* The poपूर्णांकer we are वापसing is arbitrary,
	 * it just has to be non-शून्य and not IS_ERR
	 * in the success हाल.
	 */
	वापस *pos == 0 ? &c_start : शून्य;
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
	.start =c_start,
	.next =	c_next,
	.stop =	c_stop,
	.show =	show_cpuinfo,
पूर्ण;

#अगर_घोषित CONFIG_SPARC32
अटल पूर्णांक __init cpu_type_probe(व्योम)
अणु
	पूर्णांक psr_impl, psr_vers, fpu_vers;
	पूर्णांक psr;

	psr_impl = ((get_psr() >> PSR_IMPL_SHIFT) & PSR_IMPL_SHIFTED_MASK);
	psr_vers = ((get_psr() >> PSR_VERS_SHIFT) & PSR_VERS_SHIFTED_MASK);

	psr = get_psr();
	put_psr(psr | PSR_EF);

	अगर (psr_impl == PSR_IMPL_LEON)
		fpu_vers = get_psr() & PSR_EF ? ((get_fsr() >> 17) & 0x7) : 7;
	अन्यथा
		fpu_vers = ((get_fsr() >> 17) & 0x7);

	put_psr(psr);

	set_cpu_and_fpu(psr_impl, psr_vers, fpu_vers);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SPARC32 */

#अगर_घोषित CONFIG_SPARC64
अटल व्योम __init sun4v_cpu_probe(व्योम)
अणु
	चयन (sun4v_chip_type) अणु
	हाल SUN4V_CHIP_NIAGARA1:
		sparc_cpu_type = "UltraSparc T1 (Niagara)";
		sparc_fpu_type = "UltraSparc T1 integrated FPU";
		sparc_pmu_type = "niagara";
		अवरोध;

	हाल SUN4V_CHIP_NIAGARA2:
		sparc_cpu_type = "UltraSparc T2 (Niagara2)";
		sparc_fpu_type = "UltraSparc T2 integrated FPU";
		sparc_pmu_type = "niagara2";
		अवरोध;

	हाल SUN4V_CHIP_NIAGARA3:
		sparc_cpu_type = "UltraSparc T3 (Niagara3)";
		sparc_fpu_type = "UltraSparc T3 integrated FPU";
		sparc_pmu_type = "niagara3";
		अवरोध;

	हाल SUN4V_CHIP_NIAGARA4:
		sparc_cpu_type = "UltraSparc T4 (Niagara4)";
		sparc_fpu_type = "UltraSparc T4 integrated FPU";
		sparc_pmu_type = "niagara4";
		अवरोध;

	हाल SUN4V_CHIP_NIAGARA5:
		sparc_cpu_type = "UltraSparc T5 (Niagara5)";
		sparc_fpu_type = "UltraSparc T5 integrated FPU";
		sparc_pmu_type = "niagara5";
		अवरोध;

	हाल SUN4V_CHIP_SPARC_M6:
		sparc_cpu_type = "SPARC-M6";
		sparc_fpu_type = "SPARC-M6 integrated FPU";
		sparc_pmu_type = "sparc-m6";
		अवरोध;

	हाल SUN4V_CHIP_SPARC_M7:
		sparc_cpu_type = "SPARC-M7";
		sparc_fpu_type = "SPARC-M7 integrated FPU";
		sparc_pmu_type = "sparc-m7";
		अवरोध;

	हाल SUN4V_CHIP_SPARC_M8:
		sparc_cpu_type = "SPARC-M8";
		sparc_fpu_type = "SPARC-M8 integrated FPU";
		sparc_pmu_type = "sparc-m8";
		अवरोध;

	हाल SUN4V_CHIP_SPARC_SN:
		sparc_cpu_type = "SPARC-SN";
		sparc_fpu_type = "SPARC-SN integrated FPU";
		sparc_pmu_type = "sparc-sn";
		अवरोध;

	हाल SUN4V_CHIP_SPARC64X:
		sparc_cpu_type = "SPARC64-X";
		sparc_fpu_type = "SPARC64-X integrated FPU";
		sparc_pmu_type = "sparc64-x";
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_WARNING "CPU: Unknown sun4v cpu type [%s]\n",
		       prom_cpu_compatible);
		sparc_cpu_type = "Unknown SUN4V CPU";
		sparc_fpu_type = "Unknown SUN4V FPU";
		sparc_pmu_type = "Unknown SUN4V PMU";
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __init cpu_type_probe(व्योम)
अणु
	अगर (tlb_type == hypervisor) अणु
		sun4v_cpu_probe();
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ ver;
		पूर्णांक manuf, impl;

		__यंत्र__ __अस्थिर__("rdpr %%ver, %0" : "=r" (ver));

		manuf = ((ver >> 48) & 0xffff);
		impl = ((ver >> 32) & 0xffff);
		set_cpu_and_fpu(manuf, impl, impl);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SPARC64 */

early_initcall(cpu_type_probe);
