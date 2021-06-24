<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/machvec.c
 *
 * The SuperH machine vector setup handlers, yanked from setup.c
 *
 *  Copyright (C) 1999  Niibe Yutaka
 *  Copyright (C) 2002 - 2007 Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/processor.h>

#घोषणा MV_NAME_SIZE 32

#घोषणा क्रम_each_mv(mv) \
	क्रम ((mv) = (काष्ठा sh_machine_vector *)&__machvec_start; \
	     (mv) && (अचिन्हित दीर्घ)(mv) < (अचिन्हित दीर्घ)&__machvec_end; \
	     (mv)++)

अटल काष्ठा sh_machine_vector * __init get_mv_byname(स्थिर अक्षर *name)
अणु
	काष्ठा sh_machine_vector *mv;

	क्रम_each_mv(mv)
		अगर (strहालcmp(name, mv->mv_name) == 0)
			वापस mv;

	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक __initdata machvec_selected;

अटल पूर्णांक __init early_parse_mv(अक्षर *from)
अणु
	अक्षर mv_name[MV_NAME_SIZE] = "";
	अक्षर *mv_end;
	अक्षर *mv_comma;
	पूर्णांक mv_len;
	काष्ठा sh_machine_vector *mvp;

	mv_end = म_अक्षर(from, ' ');
	अगर (mv_end == शून्य)
		mv_end = from + म_माप(from);

	mv_comma = म_अक्षर(from, ',');
	mv_len = mv_end - from;
	अगर (mv_len > (MV_NAME_SIZE-1))
		mv_len = MV_NAME_SIZE-1;
	स_नकल(mv_name, from, mv_len);
	mv_name[mv_len] = '\0';
	from = mv_end;

	machvec_selected = 1;

	/* Boot with the generic vector */
	अगर (म_भेद(mv_name, "generic") == 0)
		वापस 0;

	mvp = get_mv_byname(mv_name);
	अगर (unlikely(!mvp)) अणु
		pr_info("Available vectors:\n\n\t'%s', ", sh_mv.mv_name);
		क्रम_each_mv(mvp)
			pr_cont("'%s', ", mvp->mv_name);
		pr_cont("\n\n");
		panic("Failed to select machvec '%s' -- halting.\n",
		      mv_name);
	पूर्ण अन्यथा
		sh_mv = *mvp;

	वापस 0;
पूर्ण
early_param("sh_mv", early_parse_mv);

व्योम __init sh_mv_setup(व्योम)
अणु
	/*
	 * Only overload the machvec अगर one hasn't been selected on
	 * the command line with sh_mv=
	 */
	अगर (!machvec_selected) अणु
		अचिन्हित दीर्घ machvec_size;

		machvec_size = ((अचिन्हित दीर्घ)&__machvec_end -
				(अचिन्हित दीर्घ)&__machvec_start);

		/*
		 * Sanity check क्रम machvec section alignment. Ensure
		 * __iniपंचांगv hasn't been misused.
		 */
		अगर (machvec_size % माप(काष्ठा sh_machine_vector))
			panic("machvec misaligned, invalid __initmv use?");

		/*
		 * If the machvec hasn't been preselected, use the first
		 * vector (usually the only one) from .machvec.init.
		 */
		अगर (machvec_size >= माप(काष्ठा sh_machine_vector))
			sh_mv = *(काष्ठा sh_machine_vector *)&__machvec_start;
	पूर्ण

	pr_notice("Booting machvec: %s\n", get_प्रणाली_type());

	/*
	 * Manually walk the vec, fill in anything that the board hasn't yet
	 * by hand, wrapping to the generic implementation.
	 */
#घोषणा mv_set(elem) करो अणु \
	अगर (!sh_mv.mv_##elem) \
		sh_mv.mv_##elem = generic_##elem; \
पूर्ण जबतक (0)

	mv_set(irq_demux);
	mv_set(mode_pins);
	mv_set(mem_init);
पूर्ण
