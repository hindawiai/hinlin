<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानकतर्क.स>
#समावेश "debug.h"
#समावेश "debug-internal.h"

अटल पूर्णांक __base_pr(स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;
	पूर्णांक err;

	बहु_शुरू(args, क्रमmat);
	err = भख_लिखो(मानक_त्रुटि, क्रमmat, args);
	बहु_पूर्ण(args);
	वापस err;
पूर्ण

libapi_prपूर्णांक_fn_t __pr_warn    = __base_pr;
libapi_prपूर्णांक_fn_t __pr_info    = __base_pr;
libapi_prपूर्णांक_fn_t __pr_debug;

व्योम libapi_set_prपूर्णांक(libapi_prपूर्णांक_fn_t warn,
		      libapi_prपूर्णांक_fn_t info,
		      libapi_prपूर्णांक_fn_t debug)
अणु
	__pr_warn    = warn;
	__pr_info    = info;
	__pr_debug   = debug;
पूर्ण
