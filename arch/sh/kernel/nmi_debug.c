<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Aपंचांगel Corporation
 */
#समावेश <linux/delay.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/hardirq.h>

क्रमागत nmi_action अणु
	NMI_SHOW_STATE	= 1 << 0,
	NMI_SHOW_REGS	= 1 << 1,
	NMI_DIE		= 1 << 2,
	NMI_DEBOUNCE	= 1 << 3,
पूर्ण;

अटल अचिन्हित दीर्घ nmi_actions;

अटल पूर्णांक nmi_debug_notअगरy(काष्ठा notअगरier_block *self,
		अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा die_args *args = data;

	अगर (likely(val != DIE_NMI))
		वापस NOTIFY_DONE;

	अगर (nmi_actions & NMI_SHOW_STATE)
		show_state();
	अगर (nmi_actions & NMI_SHOW_REGS)
		show_regs(args->regs);
	अगर (nmi_actions & NMI_DEBOUNCE)
		mdelay(10);
	अगर (nmi_actions & NMI_DIE)
		वापस NOTIFY_BAD;

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block nmi_debug_nb = अणु
	.notअगरier_call = nmi_debug_notअगरy,
पूर्ण;

अटल पूर्णांक __init nmi_debug_setup(अक्षर *str)
अणु
	अक्षर *p, *sep;

	रेजिस्टर_die_notअगरier(&nmi_debug_nb);

	अगर (*str != '=')
		वापस 0;

	क्रम (p = str + 1; *p; p = sep + 1) अणु
		sep = म_अक्षर(p, ',');
		अगर (sep)
			*sep = 0;
		अगर (म_भेद(p, "state") == 0)
			nmi_actions |= NMI_SHOW_STATE;
		अन्यथा अगर (म_भेद(p, "regs") == 0)
			nmi_actions |= NMI_SHOW_REGS;
		अन्यथा अगर (म_भेद(p, "debounce") == 0)
			nmi_actions |= NMI_DEBOUNCE;
		अन्यथा अगर (म_भेद(p, "die") == 0)
			nmi_actions |= NMI_DIE;
		अन्यथा
			prपूर्णांकk(KERN_WARNING "NMI: Unrecognized action `%s'\n",
				p);
		अगर (!sep)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
__setup("nmi_debug", nmi_debug_setup);
