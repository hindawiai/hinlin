<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1999, 2000 Ralf Baechle (ralf@gnu.org)
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/param.h>
#समावेश <linux/समयx.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/sn/klconfig.h>
#समावेश <यंत्र/sn/arch.h>
#समावेश <यंत्र/sn/gda.h>

klinfo_t *find_component(lboard_t *brd, klinfo_t *kli, अचिन्हित अक्षर काष्ठा_type)
अणु
	पूर्णांक index, j;

	अगर (kli == (klinfo_t *)शून्य) अणु
		index = 0;
	पूर्ण अन्यथा अणु
		क्रम (j = 0; j < KLCF_NUM_COMPS(brd); j++)
			अगर (kli == KLCF_COMP(brd, j))
				अवरोध;
		index = j;
		अगर (index == KLCF_NUM_COMPS(brd)) अणु
			prपूर्णांकk("find_component: Bad pointer: 0x%p\n", kli);
			वापस (klinfo_t *)शून्य;
		पूर्ण
		index++;		/* next component */
	पूर्ण

	क्रम (; index < KLCF_NUM_COMPS(brd); index++) अणु
		kli = KLCF_COMP(brd, index);
		अगर (KLCF_COMP_TYPE(kli) == काष्ठा_type)
			वापस kli;
	पूर्ण

	/* Didn't find it. */
	वापस (klinfo_t *)शून्य;
पूर्ण

klinfo_t *find_first_component(lboard_t *brd, अचिन्हित अक्षर काष्ठा_type)
अणु
	वापस find_component(brd, (klinfo_t *)शून्य, काष्ठा_type);
पूर्ण

lboard_t *find_lboard(lboard_t *start, अचिन्हित अक्षर brd_type)
अणु
	/* Search all boards stored on this node. */
	जबतक (start) अणु
		अगर (start->brd_type == brd_type)
			वापस start;
		start = KLCF_NEXT(start);
	पूर्ण
	/* Didn't find it. */
	वापस (lboard_t *)शून्य;
पूर्ण

lboard_t *find_lboard_class(lboard_t *start, अचिन्हित अक्षर brd_type)
अणु
	/* Search all boards stored on this node. */
	जबतक (start) अणु
		अगर (KLCLASS(start->brd_type) == KLCLASS(brd_type))
			वापस start;
		start = KLCF_NEXT(start);
	पूर्ण

	/* Didn't find it. */
	वापस (lboard_t *)शून्य;
पूर्ण
