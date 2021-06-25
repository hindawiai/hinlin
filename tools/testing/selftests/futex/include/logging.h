<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *   Copyright तऊ International Business Machines  Corp., 2009
 *
 * DESCRIPTION
 *      Glibc independent futex library क्रम testing kernel functionality.
 *
 * AUTHOR
 *      Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 * HISTORY
 *      2009-Nov-6: Initial version by Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 *****************************************************************************/

#अगर_अघोषित _LOGGING_H
#घोषणा _LOGGING_H

#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <linux/futex.h>
#समावेश "kselftest.h"

/*
 * Define PASS, ERROR, and FAIL strings with and without color escape
 * sequences, शेष to no color.
 */
#घोषणा ESC 0x1B, '['
#घोषणा BRIGHT '1'
#घोषणा GREEN '3', '2'
#घोषणा YELLOW '3', '3'
#घोषणा RED '3', '1'
#घोषणा ESCEND 'm'
#घोषणा BRIGHT_GREEN ESC, BRIGHT, ';', GREEN, ESCEND
#घोषणा BRIGHT_YELLOW ESC, BRIGHT, ';', YELLOW, ESCEND
#घोषणा BRIGHT_RED ESC, BRIGHT, ';', RED, ESCEND
#घोषणा RESET_COLOR ESC, '0', 'm'
अटल स्थिर अक्षर PASS_COLOR[] = अणुBRIGHT_GREEN, ' ', 'P', 'A', 'S', 'S',
				  RESET_COLOR, 0पूर्ण;
अटल स्थिर अक्षर ERROR_COLOR[] = अणुBRIGHT_YELLOW, 'E', 'R', 'R', 'O', 'R',
				   RESET_COLOR, 0पूर्ण;
अटल स्थिर अक्षर FAIL_COLOR[] = अणुBRIGHT_RED, ' ', 'F', 'A', 'I', 'L',
				  RESET_COLOR, 0पूर्ण;
अटल स्थिर अक्षर INFO_NORMAL[] = " INFO";
अटल स्थिर अक्षर PASS_NORMAL[] = " PASS";
अटल स्थिर अक्षर ERROR_NORMAL[] = "ERROR";
अटल स्थिर अक्षर FAIL_NORMAL[] = " FAIL";
स्थिर अक्षर *INFO = INFO_NORMAL;
स्थिर अक्षर *PASS = PASS_NORMAL;
स्थिर अक्षर *ERROR = ERROR_NORMAL;
स्थिर अक्षर *FAIL = FAIL_NORMAL;

/* Verbosity setting क्रम INFO messages */
#घोषणा VQUIET    0
#घोषणा VCRITICAL 1
#घोषणा VINFO     2
#घोषणा VMAX      VINFO
पूर्णांक _verbose = VCRITICAL;

/* Functional test वापस codes */
#घोषणा RET_PASS   0
#घोषणा RET_ERROR -1
#घोषणा RET_FAIL  -2

/**
 * log_color() - Use colored output क्रम PASS, ERROR, and FAIL strings
 * @use_color:	use color (1) or not (0)
 */
व्योम log_color(पूर्णांक use_color)
अणु
	अगर (use_color) अणु
		PASS = PASS_COLOR;
		ERROR = ERROR_COLOR;
		FAIL = FAIL_COLOR;
	पूर्ण अन्यथा अणु
		PASS = PASS_NORMAL;
		ERROR = ERROR_NORMAL;
		FAIL = FAIL_NORMAL;
	पूर्ण
पूर्ण

/**
 * log_verbosity() - Set verbosity of test output
 * @verbose:	Enable (1) verbose output or not (0)
 *
 * Currently setting verbose=1 will enable INFO messages and 0 will disable
 * them. FAIL and ERROR messages are always displayed.
 */
व्योम log_verbosity(पूर्णांक level)
अणु
	अगर (level > VMAX)
		level = VMAX;
	अन्यथा अगर (level < 0)
		level = 0;
	_verbose = level;
पूर्ण

/**
 * prपूर्णांक_result() - Prपूर्णांक standard PASS | ERROR | FAIL results
 * @ret:	the वापस value to be considered: 0 | RET_ERROR | RET_FAIL
 *
 * prपूर्णांक_result() is primarily पूर्णांकended क्रम functional tests.
 */
व्योम prपूर्णांक_result(स्थिर अक्षर *test_name, पूर्णांक ret)
अणु
	चयन (ret) अणु
	हाल RET_PASS:
		ksft_test_result_pass("%s\n", test_name);
		ksft_prपूर्णांक_cnts();
		वापस;
	हाल RET_ERROR:
		ksft_test_result_error("%s\n", test_name);
		ksft_prपूर्णांक_cnts();
		वापस;
	हाल RET_FAIL:
		ksft_test_result_fail("%s\n", test_name);
		ksft_prपूर्णांक_cnts();
		वापस;
	पूर्ण
पूर्ण

/* log level macros */
#घोषणा info(message, vargs...) \
करो अणु \
	अगर (_verbose >= VINFO) \
		ख_लिखो(मानक_त्रुटि, "\t%s: "message, INFO, ##vargs); \
पूर्ण जबतक (0)

#घोषणा error(message, err, args...) \
करो अणु \
	अगर (_verbose >= VCRITICAL) अणु\
		अगर (err) \
			ख_लिखो(मानक_त्रुटि, "\t%s: %s: "message, \
				ERROR, म_त्रुटि(err), ##args); \
		अन्यथा \
			ख_लिखो(मानक_त्रुटि, "\t%s: "message, ERROR, ##args); \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा fail(message, args...) \
करो अणु \
	अगर (_verbose >= VCRITICAL) \
		ख_लिखो(मानक_त्रुटि, "\t%s: "message, FAIL, ##args); \
पूर्ण जबतक (0)

#पूर्ण_अगर
