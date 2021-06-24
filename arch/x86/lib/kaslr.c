<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Entropy functions used on early boot क्रम KASLR base and memory
 * अक्रमomization. The base अक्रमomization is करोne in the compressed
 * kernel and memory अक्रमomization is करोne early when the regular
 * kernel starts. This file is included in the compressed kernel and
 * normally linked in the regular.
 */
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/kaslr.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/archअक्रमom.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/पन.स>

/*
 * When built क्रम the regular kernel, several functions need to be stubbed out
 * or changed to their regular kernel equivalent.
 */
#अगर_अघोषित KASLR_COMPRESSED_BOOT
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/setup.h>

#घोषणा debug_माला_दोtr(v) early_prपूर्णांकk("%s", v)
#घोषणा has_cpuflag(f) boot_cpu_has(f)
#घोषणा get_boot_seed() kaslr_offset()
#पूर्ण_अगर

#घोषणा I8254_PORT_CONTROL	0x43
#घोषणा I8254_PORT_COUNTER0	0x40
#घोषणा I8254_CMD_READBACK	0xC0
#घोषणा I8254_SELECT_COUNTER0	0x02
#घोषणा I8254_STATUS_NOTREADY	0x40
अटल अंतरभूत u16 i8254(व्योम)
अणु
	u16 status, समयr;

	करो अणु
		outb(I8254_CMD_READBACK | I8254_SELECT_COUNTER0,
		     I8254_PORT_CONTROL);
		status = inb(I8254_PORT_COUNTER0);
		समयr  = inb(I8254_PORT_COUNTER0);
		समयr |= inb(I8254_PORT_COUNTER0) << 8;
	पूर्ण जबतक (status & I8254_STATUS_NOTREADY);

	वापस समयr;
पूर्ण

अचिन्हित दीर्घ kaslr_get_अक्रमom_दीर्घ(स्थिर अक्षर *purpose)
अणु
#अगर_घोषित CONFIG_X86_64
	स्थिर अचिन्हित दीर्घ mix_स्थिर = 0x5d6008cbf3848dd3UL;
#अन्यथा
	स्थिर अचिन्हित दीर्घ mix_स्थिर = 0x3f39e593UL;
#पूर्ण_अगर
	अचिन्हित दीर्घ raw, अक्रमom = get_boot_seed();
	bool use_i8254 = true;

	debug_माला_दोtr(purpose);
	debug_माला_दोtr(" KASLR using");

	अगर (has_cpuflag(X86_FEATURE_RDRAND)) अणु
		debug_माला_दोtr(" RDRAND");
		अगर (rdअक्रम_दीर्घ(&raw)) अणु
			अक्रमom ^= raw;
			use_i8254 = false;
		पूर्ण
	पूर्ण

	अगर (has_cpuflag(X86_FEATURE_TSC)) अणु
		debug_माला_दोtr(" RDTSC");
		raw = rdtsc();

		अक्रमom ^= raw;
		use_i8254 = false;
	पूर्ण

	अगर (use_i8254) अणु
		debug_माला_दोtr(" i8254");
		अक्रमom ^= i8254();
	पूर्ण

	/* Circular multiply क्रम better bit dअगरfusion */
	यंत्र(_ASM_MUL "%3"
	    : "=a" (अक्रमom), "=d" (raw)
	    : "a" (अक्रमom), "rm" (mix_स्थिर));
	अक्रमom += raw;

	debug_माला_दोtr("...\n");

	वापस अक्रमom;
पूर्ण
