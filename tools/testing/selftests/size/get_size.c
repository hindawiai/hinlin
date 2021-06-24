<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014 Sony Mobile Communications Inc.
 *
 * Selftest क्रम runसमय प्रणाली size
 *
 * Prपूर्णांकs the amount of RAM that the currently running प्रणाली is using.
 *
 * This program tries to be as small as possible itself, to
 * aव्योम perturbing the प्रणाली memory utilization with its
 * own execution.  It also attempts to have as few dependencies
 * on kernel features as possible.
 *
 * It should be अटलally linked, with startup libs aव्योमed.  It uses
 * no library calls except the syscall() function क्रम the following 3
 * syscalls:
 *   sysinfo(), ग_लिखो(), and _निकास()
 *
 * For output, it aव्योमs म_लिखो (which in some C libraries
 * has large बाह्यal dependencies) by  implementing it's own
 * number output and prपूर्णांक routines, and using __builtin_म_माप()
 *
 * The test may crash अगर any of the above syscalls fails because in some
 * libc implementations (e.g. the GNU C Library) त्रुटि_सं is saved in
 * thपढ़ो-local storage, which करोes not get initialized due to aव्योमing
 * startup libs.
 */

#समावेश <sys/sysinfo.h>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>

#घोषणा STDOUT_खाताNO 1

अटल पूर्णांक prपूर्णांक(स्थिर अक्षर *s)
अणु
	माप_प्रकार len = 0;

	जबतक (s[len] != '\0')
		len++;

	वापस syscall(SYS_ग_लिखो, STDOUT_खाताNO, s, len);
पूर्ण

अटल अंतरभूत अक्षर *num_to_str(अचिन्हित दीर्घ num, अक्षर *buf, पूर्णांक len)
अणु
	अचिन्हित पूर्णांक digit;

	/* put digits in buffer from back to front */
	buf += len - 1;
	*buf = 0;
	करो अणु
		digit = num % 10;
		*(--buf) = digit + '0';
		num /= 10;
	पूर्ण जबतक (num > 0);

	वापस buf;
पूर्ण

अटल पूर्णांक prपूर्णांक_num(अचिन्हित दीर्घ num)
अणु
	अक्षर num_buf[30];

	वापस prपूर्णांक(num_to_str(num, num_buf, माप(num_buf)));
पूर्ण

अटल पूर्णांक prपूर्णांक_k_value(स्थिर अक्षर *s, अचिन्हित दीर्घ num, अचिन्हित दीर्घ units)
अणु
	अचिन्हित दीर्घ दीर्घ temp;
	पूर्णांक ccode;

	prपूर्णांक(s);

	temp = num;
	temp = (temp * units)/1024;
	num = temp;
	ccode = prपूर्णांक_num(num);
	prपूर्णांक("\n");
	वापस ccode;
पूर्ण

/* this program has no मुख्य(), as startup libraries are not used */
व्योम _start(व्योम)
अणु
	पूर्णांक ccode;
	काष्ठा sysinfo info;
	अचिन्हित दीर्घ used;
	अटल स्थिर अक्षर *test_name = " get runtime memory use\n";

	prपूर्णांक("TAP version 13\n");
	prपूर्णांक("# Testing system size.\n");

	ccode = syscall(SYS_sysinfo, &info);
	अगर (ccode < 0) अणु
		prपूर्णांक("not ok 1");
		prपूर्णांक(test_name);
		prपूर्णांक(" ---\n reason: \"could not get sysinfo\"\n ...\n");
		syscall(SYS_निकास, ccode);
	पूर्ण
	prपूर्णांक("ok 1");
	prपूर्णांक(test_name);

	/* ignore cache complनिकासies क्रम now */
	used = info.totalram - info.मुक्तram - info.bufferram;
	prपूर्णांक("# System runtime memory report (units in Kilobytes):\n");
	prपूर्णांक(" ---\n");
	prपूर्णांक_k_value(" Total:  ", info.totalram, info.mem_unit);
	prपूर्णांक_k_value(" Free:   ", info.मुक्तram, info.mem_unit);
	prपूर्णांक_k_value(" Buffer: ", info.bufferram, info.mem_unit);
	prपूर्णांक_k_value(" In use: ", used, info.mem_unit);
	prपूर्णांक(" ...\n");
	prपूर्णांक("1..1\n");

	syscall(SYS_निकास, 0);
पूर्ण
