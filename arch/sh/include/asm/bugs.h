<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_BUGS_H
#घोषणा __ASM_SH_BUGS_H

/*
 * This is included by init/मुख्य.c to check क्रम architecture-dependent bugs.
 *
 * Needs:
 *	व्योम check_bugs(व्योम);
 */

/*
 * I करोn't know of any Super-H bugs yet.
 */

#समावेश <यंत्र/processor.h>

बाह्य व्योम select_idle_routine(व्योम);

अटल व्योम __init check_bugs(व्योम)
अणु
	बाह्य अचिन्हित दीर्घ loops_per_jअगरfy;
	अक्षर *p = &init_utsname()->machine[2]; /* "sh" */

	select_idle_routine();

	current_cpu_data.loops_per_jअगरfy = loops_per_jअगरfy;

	चयन (current_cpu_data.family) अणु
	हाल CPU_FAMILY_SH2:
		*p++ = '2';
		अवरोध;
	हाल CPU_FAMILY_SH2A:
		*p++ = '2';
		*p++ = 'a';
		अवरोध;
	हाल CPU_FAMILY_SH3:
		*p++ = '3';
		अवरोध;
	हाल CPU_FAMILY_SH4:
		*p++ = '4';
		अवरोध;
	हाल CPU_FAMILY_SH4A:
		*p++ = '4';
		*p++ = 'a';
		अवरोध;
	हाल CPU_FAMILY_SH4AL_DSP:
		*p++ = '4';
		*p++ = 'a';
		*p++ = 'l';
		*p++ = '-';
		*p++ = 'd';
		*p++ = 's';
		*p++ = 'p';
		अवरोध;
	हाल CPU_FAMILY_UNKNOWN:
		/*
		 * Specअगरically use CPU_FAMILY_UNKNOWN rather than
		 * शेष:, so we're able to have the compiler whine
		 * about unhandled क्रमागतerations.
		 */
		अवरोध;
	पूर्ण

	prपूर्णांकk("CPU: %s\n", get_cpu_subtype(&current_cpu_data));

#अगर_अघोषित __LITTLE_ENDIAN__
	/* 'eb' means 'Endian Big' */
	*p++ = 'e';
	*p++ = 'b';
#पूर्ण_अगर
	*p = '\0';
पूर्ण
#पूर्ण_अगर /* __ASM_SH_BUGS_H */
