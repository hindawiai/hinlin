<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकतर्क.स>
#समावेश <त्रुटिसं.स>

#घोषणा __weak __attribute__((weak))

व्योम __vwarning(स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	अगर (त्रुटि_सं)
		लिखो_त्रुटि("libtraceevent");
	त्रुटि_सं = 0;

	ख_लिखो(मानक_त्रुटि, "  ");
	भख_लिखो(मानक_त्रुटि, fmt, ap);

	ख_लिखो(मानक_त्रुटि, "\n");
पूर्ण

व्योम __warning(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	__vwarning(fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

व्योम __weak warning(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	__vwarning(fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

व्योम __vpr_stat(स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	भ_लिखो(fmt, ap);
	म_लिखो("\n");
पूर्ण

व्योम __pr_stat(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	__vpr_stat(fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

व्योम __weak vpr_stat(स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	__vpr_stat(fmt, ap);
पूर्ण

व्योम __weak pr_stat(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	__vpr_stat(fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण
