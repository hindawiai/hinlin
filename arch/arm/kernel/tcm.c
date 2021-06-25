<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2009 ST-Ericsson AB
 * TCM memory handling क्रम ARM प्रणालीs
 *
 * Author: Linus Walleij <linus.walleij@stericsson.com>
 * Author: Rickard Andersson <rickard.andersson@stericsson.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ioport.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/माला.स> /* स_नकल */
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/tcm.h>

#घोषणा TCMTR_FORMAT_MASK	0xe0000000U

अटल काष्ठा gen_pool *tcm_pool;
अटल bool dtcm_present;
अटल bool itcm_present;

/* TCM section definitions from the linker */
बाह्य अक्षर __itcm_start, __sitcm_text, __eitcm_text;
बाह्य अक्षर __dtcm_start, __sdtcm_data, __edtcm_data;

/* These will be increased as we run */
अटल u32 dtcm_end = DTCM_OFFSET;
अटल u32 itcm_end = ITCM_OFFSET;

/*
 * TCM memory resources
 */
अटल काष्ठा resource dtcm_res = अणु
	.name = "DTCM RAM",
	.start = DTCM_OFFSET,
	.end = DTCM_OFFSET,
	.flags = IORESOURCE_MEM
पूर्ण;

अटल काष्ठा resource itcm_res = अणु
	.name = "ITCM RAM",
	.start = ITCM_OFFSET,
	.end = ITCM_OFFSET,
	.flags = IORESOURCE_MEM
पूर्ण;

अटल काष्ठा map_desc dtcm_iomap[] __initdata = अणु
	अणु
		.भव	= DTCM_OFFSET,
		.pfn		= __phys_to_pfn(DTCM_OFFSET),
		.length		= 0,
		.type		= MT_MEMORY_RW_DTCM
	पूर्ण
पूर्ण;

अटल काष्ठा map_desc itcm_iomap[] __initdata = अणु
	अणु
		.भव	= ITCM_OFFSET,
		.pfn		= __phys_to_pfn(ITCM_OFFSET),
		.length		= 0,
		.type		= MT_MEMORY_RWX_ITCM,
	पूर्ण
पूर्ण;

/*
 * Allocate a chunk of TCM memory
 */
व्योम *tcm_alloc(माप_प्रकार len)
अणु
	अचिन्हित दीर्घ vaddr;

	अगर (!tcm_pool)
		वापस शून्य;

	vaddr = gen_pool_alloc(tcm_pool, len);
	अगर (!vaddr)
		वापस शून्य;

	वापस (व्योम *) vaddr;
पूर्ण
EXPORT_SYMBOL(tcm_alloc);

/*
 * Free a chunk of TCM memory
 */
व्योम tcm_मुक्त(व्योम *addr, माप_प्रकार len)
अणु
	gen_pool_मुक्त(tcm_pool, (अचिन्हित दीर्घ) addr, len);
पूर्ण
EXPORT_SYMBOL(tcm_मुक्त);

bool tcm_dtcm_present(व्योम)
अणु
	वापस dtcm_present;
पूर्ण
EXPORT_SYMBOL(tcm_dtcm_present);

bool tcm_itcm_present(व्योम)
अणु
	वापस itcm_present;
पूर्ण
EXPORT_SYMBOL(tcm_itcm_present);

अटल पूर्णांक __init setup_tcm_bank(u8 type, u8 bank, u8 banks,
				  u32 *offset)
अणु
	स्थिर पूर्णांक tcm_sizes[16] = अणु 0, -1, -1, 4, 8, 16, 32, 64, 128,
				    256, 512, 1024, -1, -1, -1, -1 पूर्ण;
	u32 tcm_region;
	पूर्णांक tcm_size;

	/*
	 * If there are more than one TCM bank of this type,
	 * select the TCM bank to operate on in the TCM selection
	 * रेजिस्टर.
	 */
	अगर (banks > 1)
		यंत्र("mcr	p15, 0, %0, c9, c2, 0"
		    : /* No output opeअक्रमs */
		    : "r" (bank));

	/* Read the special TCM region रेजिस्टर c9, 0 */
	अगर (!type)
		यंत्र("mrc	p15, 0, %0, c9, c1, 0"
		    : "=r" (tcm_region));
	अन्यथा
		यंत्र("mrc	p15, 0, %0, c9, c1, 1"
		    : "=r" (tcm_region));

	tcm_size = tcm_sizes[(tcm_region >> 2) & 0x0f];
	अगर (tcm_size < 0) अणु
		pr_err("CPU: %sTCM%d of unknown size\n",
		       type ? "I" : "D", bank);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (tcm_size > 32) अणु
		pr_err("CPU: %sTCM%d larger than 32k found\n",
		       type ? "I" : "D", bank);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		pr_info("CPU: found %sTCM%d %dk @ %08x, %senabled\n",
			type ? "I" : "D",
			bank,
			tcm_size,
			(tcm_region & 0xfffff000U),
			(tcm_region & 1) ? "" : "not ");
	पूर्ण

	/* Not much fun you can करो with a size 0 bank */
	अगर (tcm_size == 0)
		वापस 0;

	/* Force move the TCM bank to where we want it, enable */
	tcm_region = *offset | (tcm_region & 0x00000ffeU) | 1;

	अगर (!type)
		यंत्र("mcr	p15, 0, %0, c9, c1, 0"
		    : /* No output opeअक्रमs */
		    : "r" (tcm_region));
	अन्यथा
		यंत्र("mcr	p15, 0, %0, c9, c1, 1"
		    : /* No output opeअक्रमs */
		    : "r" (tcm_region));

	/* Increase offset */
	*offset += (tcm_size << 10);

	pr_info("CPU: moved %sTCM%d %dk to %08x, enabled\n",
		type ? "I" : "D",
		bank,
		tcm_size,
		(tcm_region & 0xfffff000U));
	वापस 0;
पूर्ण

/*
 * When we are running in the non-secure world and the secure world
 * has not explicitly given us access to the TCM we will get an
 * undefined error when पढ़ोing the TCM region रेजिस्टर in the
 * setup_tcm_bank function (above).
 *
 * There are two variants of this रेजिस्टर पढ़ो that we need to trap,
 * the पढ़ो क्रम the data TCM and the पढ़ो क्रम the inकाष्ठाion TCM:
 *  c0370628:       ee196f11        mrc     15, 0, r6, cr9, cr1, अणु0पूर्ण
 *  c0370674:       ee196f31        mrc     15, 0, r6, cr9, cr1, अणु1पूर्ण
 *
 * Our undef hook mask explicitly matches all fields of the encoded
 * inकाष्ठाion other than the destination रेजिस्टर.  The mask also
 * only allows opeअक्रम 2 to have the values 0 or 1.
 *
 * The undefined hook is defined as __init and __initdata, and thereक्रमe
 * must be हटाओd beक्रमe tcm_init वापसs.
 *
 * In this particular हाल (MRC with ARM condition code ALways) the
 * Thumb-2 and ARM inकाष्ठाion encoding are identical, so this hook
 * will work on a Thumb-2 kernel.
 *
 * See A8.8.107, DDI0406C_C ARM Architecture Reference Manual, Encoding
 * T1/A1 क्रम the bit-by-bit details.
 *
 *  mrc   p15, 0, XX, c9, c1, 0
 *  mrc   p15, 0, XX, c9, c1, 1
 *   |  |  |   |   |   |   |  +---- opc2           0|1 = 000|001
 *   |  |  |   |   |   |   +------- CRm              0 = 0001
 *   |  |  |   |   |   +----------- CRn              0 = 1001
 *   |  |  |   |   +--------------- Rt               ? = ????
 *   |  |  |   +------------------- opc1             0 =  000
 *   |  |  +----------------------- coproc          15 = 1111
 *   |  +-------------------------- condition   ALways = 1110
 *   +----------------------------- inकाष्ठाion    MRC = 1110
 *
 * Encoding this as per A8.8.107 of DDI0406C, Encoding T1/A1, yields:
 *  1111 1111 1111 1111 0000 1111 1101 1111 Required Mask
 *  1110 1110 0001 1001 ???? 1111 0001 0001 mrc p15, 0, XX, c9, c1, 0
 *  1110 1110 0001 1001 ???? 1111 0011 0001 mrc p15, 0, XX, c9, c1, 1
 *  [  ] [  ] [ ]| [  ] [  ] [  ] [ ]| +--- CRm
 *    |    |   | |   |    |    |   | +----- SBO
 *    |    |   | |   |    |    |   +------- opc2
 *    |    |   | |   |    |    +----------- coproc
 *    |    |   | |   |    +---------------- Rt
 *    |    |   | |   +--------------------- CRn
 *    |    |   | +------------------------- SBO
 *    |    |   +--------------------------- opc1
 *    |    +------------------------------- inकाष्ठाion
 *    +------------------------------------ condition
 */
#घोषणा TCM_REGION_READ_MASK		0xffff0fdf
#घोषणा TCM_REGION_READ_INSTR		0xee190f11
#घोषणा DEST_REG_SHIFT			12
#घोषणा DEST_REG_MASK			0xf

अटल पूर्णांक __init tcm_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	regs->uregs[(instr >> DEST_REG_SHIFT) & DEST_REG_MASK] = 0;
	regs->ARM_pc += 4;
	वापस 0;
पूर्ण

अटल काष्ठा undef_hook tcm_hook __initdata = अणु
	.instr_mask	= TCM_REGION_READ_MASK,
	.instr_val	= TCM_REGION_READ_INSTR,
	.cpsr_mask	= MODE_MASK,
	.cpsr_val	= SVC_MODE,
	.fn		= tcm_handler
पूर्ण;

/*
 * This initializes the TCM memory
 */
व्योम __init tcm_init(व्योम)
अणु
	u32 tcm_status;
	u8 dtcm_banks;
	u8 itcm_banks;
	माप_प्रकार dtcm_code_sz = &__edtcm_data - &__sdtcm_data;
	माप_प्रकार itcm_code_sz = &__eitcm_text - &__sitcm_text;
	अक्षर *start;
	अक्षर *end;
	अक्षर *ram;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * Prior to ARMv5 there is no TCM, and trying to पढ़ो the status
	 * रेजिस्टर will hang the processor.
	 */
	अगर (cpu_architecture() < CPU_ARCH_ARMv5) अणु
		अगर (dtcm_code_sz || itcm_code_sz)
			pr_info("CPU TCM: %u bytes of DTCM and %u bytes of "
				"ITCM code compiled in, but no TCM present "
				"in pre-v5 CPU\n", dtcm_code_sz, itcm_code_sz);
		वापस;
	पूर्ण

	tcm_status = पढ़ो_cpuid_tcmstatus();

	/*
	 * This code only supports v6-compatible TCMTR implementations.
	 */
	अगर (tcm_status & TCMTR_FORMAT_MASK)
		वापस;

	dtcm_banks = (tcm_status >> 16) & 0x03;
	itcm_banks = (tcm_status & 0x03);

	रेजिस्टर_undef_hook(&tcm_hook);

	/* Values greater than 2 क्रम D/ITCM banks are "reserved" */
	अगर (dtcm_banks > 2)
		dtcm_banks = 0;
	अगर (itcm_banks > 2)
		itcm_banks = 0;

	/* Setup DTCM अगर present */
	अगर (dtcm_banks > 0) अणु
		क्रम (i = 0; i < dtcm_banks; i++) अणु
			ret = setup_tcm_bank(0, i, dtcm_banks, &dtcm_end);
			अगर (ret)
				जाओ unरेजिस्टर;
		पूर्ण
		/* This means you compiled more code than fits पूर्णांकo DTCM */
		अगर (dtcm_code_sz > (dtcm_end - DTCM_OFFSET)) अणु
			pr_info("CPU DTCM: %u bytes of code compiled to "
				"DTCM but only %lu bytes of DTCM present\n",
				dtcm_code_sz, (dtcm_end - DTCM_OFFSET));
			जाओ no_dtcm;
		पूर्ण
		/*
		 * This means that the DTCM sizes were 0 or the DTCM banks
		 * were inaccessible due to TrustZone configuration.
		 */
		अगर (!(dtcm_end - DTCM_OFFSET))
			जाओ no_dtcm;
		dtcm_res.end = dtcm_end - 1;
		request_resource(&iomem_resource, &dtcm_res);
		dtcm_iomap[0].length = dtcm_end - DTCM_OFFSET;
		iotable_init(dtcm_iomap, 1);
		/* Copy data from RAM to DTCM */
		start = &__sdtcm_data;
		end   = &__edtcm_data;
		ram   = &__dtcm_start;
		स_नकल(start, ram, dtcm_code_sz);
		pr_debug("CPU DTCM: copied data from %p - %p\n",
			 start, end);
		dtcm_present = true;
	पूर्ण अन्यथा अगर (dtcm_code_sz) अणु
		pr_info("CPU DTCM: %u bytes of code compiled to DTCM but no "
			"DTCM banks present in CPU\n", dtcm_code_sz);
	पूर्ण

no_dtcm:
	/* Setup ITCM अगर present */
	अगर (itcm_banks > 0) अणु
		क्रम (i = 0; i < itcm_banks; i++) अणु
			ret = setup_tcm_bank(1, i, itcm_banks, &itcm_end);
			अगर (ret)
				जाओ unरेजिस्टर;
		पूर्ण
		/* This means you compiled more code than fits पूर्णांकo ITCM */
		अगर (itcm_code_sz > (itcm_end - ITCM_OFFSET)) अणु
			pr_info("CPU ITCM: %u bytes of code compiled to "
				"ITCM but only %lu bytes of ITCM present\n",
				itcm_code_sz, (itcm_end - ITCM_OFFSET));
			जाओ unरेजिस्टर;
		पूर्ण
		/*
		 * This means that the ITCM sizes were 0 or the ITCM banks
		 * were inaccessible due to TrustZone configuration.
		 */
		अगर (!(itcm_end - ITCM_OFFSET))
			जाओ unरेजिस्टर;
		itcm_res.end = itcm_end - 1;
		request_resource(&iomem_resource, &itcm_res);
		itcm_iomap[0].length = itcm_end - ITCM_OFFSET;
		iotable_init(itcm_iomap, 1);
		/* Copy code from RAM to ITCM */
		start = &__sitcm_text;
		end   = &__eitcm_text;
		ram   = &__itcm_start;
		स_नकल(start, ram, itcm_code_sz);
		pr_debug("CPU ITCM: copied code from %p - %p\n",
			 start, end);
		itcm_present = true;
	पूर्ण अन्यथा अगर (itcm_code_sz) अणु
		pr_info("CPU ITCM: %u bytes of code compiled to ITCM but no "
			"ITCM banks present in CPU\n", itcm_code_sz);
	पूर्ण

unरेजिस्टर:
	unरेजिस्टर_undef_hook(&tcm_hook);
पूर्ण

/*
 * This creates the TCM memory pool and has to be करोne later,
 * during the core_initicalls, since the allocator is not yet
 * up and running when the first initialization runs.
 */
अटल पूर्णांक __init setup_tcm_pool(व्योम)
अणु
	u32 dtcm_pool_start = (u32) &__edtcm_data;
	u32 itcm_pool_start = (u32) &__eitcm_text;
	पूर्णांक ret;

	/*
	 * Set up दो_स्मृति pool, 2^2 = 4 bytes granularity since
	 * the TCM is someबार just 4 KiB. NB: pages and cache
	 * line alignments करोes not matter in TCM!
	 */
	tcm_pool = gen_pool_create(2, -1);

	pr_debug("Setting up TCM memory pool\n");

	/* Add the rest of DTCM to the TCM pool */
	अगर (dtcm_present) अणु
		अगर (dtcm_pool_start < dtcm_end) अणु
			ret = gen_pool_add(tcm_pool, dtcm_pool_start,
					   dtcm_end - dtcm_pool_start, -1);
			अगर (ret) अणु
				pr_err("CPU DTCM: could not add DTCM " \
				       "remainder to pool!\n");
				वापस ret;
			पूर्ण
			pr_debug("CPU DTCM: Added %08x bytes @ %08x to " \
				 "the TCM memory pool\n",
				 dtcm_end - dtcm_pool_start,
				 dtcm_pool_start);
		पूर्ण
	पूर्ण

	/* Add the rest of ITCM to the TCM pool */
	अगर (itcm_present) अणु
		अगर (itcm_pool_start < itcm_end) अणु
			ret = gen_pool_add(tcm_pool, itcm_pool_start,
					   itcm_end - itcm_pool_start, -1);
			अगर (ret) अणु
				pr_err("CPU ITCM: could not add ITCM " \
				       "remainder to pool!\n");
				वापस ret;
			पूर्ण
			pr_debug("CPU ITCM: Added %08x bytes @ %08x to " \
				 "the TCM memory pool\n",
				 itcm_end - itcm_pool_start,
				 itcm_pool_start);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

core_initcall(setup_tcm_pool);
