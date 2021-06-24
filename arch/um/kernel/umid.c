<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <init.h>
#समावेश <kern.h>
#समावेश <os.h>

/* Changed by set_umid_arg */
अटल पूर्णांक umid_inited = 0;

अटल पूर्णांक __init set_umid_arg(अक्षर *name, पूर्णांक *add)
अणु
	पूर्णांक err;

	अगर (umid_inited) अणु
		os_warn("umid already set\n");
		वापस 0;
	पूर्ण

	*add = 0;
	err = set_umid(name);
	अगर (err == -EEXIST)
		os_warn("umid '%s' already in use\n", name);
	अन्यथा अगर (!err)
		umid_inited = 1;

	वापस 0;
पूर्ण

__uml_setup("umid=", set_umid_arg,
"umid=<name>\n"
"    This is used to assign a unique identity to this UML machine and\n"
"    is used for naming the pid file and management console socket.\n\n"
);

