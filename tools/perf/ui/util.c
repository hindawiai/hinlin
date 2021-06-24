<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "util.h"
#समावेश "../util/debug.h"
#समावेश <मानकपन.स>

/*
 * Default error logging functions
 */
अटल पूर्णांक perf_stdio__error(स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	ख_लिखो(मानक_त्रुटि, "Error:\n");
	भख_लिखो(मानक_त्रुटि, क्रमmat, args);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_stdio__warning(स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	ख_लिखो(मानक_त्रुटि, "Warning:\n");
	भख_लिखो(मानक_त्रुटि, क्रमmat, args);
	वापस 0;
पूर्ण

अटल काष्ठा perf_error_ops शेष_eops =
अणु
	.error		= perf_stdio__error,
	.warning	= perf_stdio__warning,
पूर्ण;

अटल काष्ठा perf_error_ops *perf_eops = &शेष_eops;


पूर्णांक ui__error(स्थिर अक्षर *क्रमmat, ...)
अणु
	पूर्णांक ret;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);
	ret = perf_eops->error(क्रमmat, args);
	बहु_पूर्ण(args);

	वापस ret;
पूर्ण

पूर्णांक ui__warning(स्थिर अक्षर *क्रमmat, ...)
अणु
	पूर्णांक ret;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);
	ret = perf_eops->warning(क्रमmat, args);
	बहु_पूर्ण(args);

	वापस ret;
पूर्ण

/**
 * perf_error__रेजिस्टर - Register error logging functions
 * @eops: The poपूर्णांकer to error logging function काष्ठा
 *
 * Register UI-specअगरic error logging functions. Beक्रमe calling this,
 * other logging functions should be unरेजिस्टरed, अगर any.
 */
पूर्णांक perf_error__रेजिस्टर(काष्ठा perf_error_ops *eops)
अणु
	अगर (perf_eops != &शेष_eops)
		वापस -1;

	perf_eops = eops;
	वापस 0;
पूर्ण

/**
 * perf_error__unरेजिस्टर - Unरेजिस्टर error logging functions
 * @eops: The poपूर्णांकer to error logging function काष्ठा
 *
 * Unरेजिस्टर alपढ़ोy रेजिस्टरed error logging functions.
 */
पूर्णांक perf_error__unरेजिस्टर(काष्ठा perf_error_ops *eops)
अणु
	अगर (perf_eops != eops)
		वापस -1;

	perf_eops = &शेष_eops;
	वापस 0;
पूर्ण
