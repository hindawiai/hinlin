<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2003 - 2004  Dominik Broकरोwski <linux@करोminikbroकरोwski.de>
 *
 * Based on code found in
 * linux/arch/i386/kernel/cpu/cpufreq/speedstep-centrino.c
 * and originally developed by Jeremy Fitzhardinge.
 *
 * USAGE: simply run it to decode the current settings on CPU 0,
 *	  or pass the CPU number as argument, or pass the MSR content
 *	  as argument.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>

#घोषणा MCPU	32

#घोषणा MSR_IA32_PERF_STATUS	0x198

अटल पूर्णांक rdmsr(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक msr,
		 अचिन्हित पूर्णांक *lo, अचिन्हित पूर्णांक *hi)
अणु
	पूर्णांक fd;
	अक्षर file[20];
	अचिन्हित दीर्घ दीर्घ val;
	पूर्णांक retval = -1;

	*lo = *hi = 0;

	अगर (cpu > MCPU)
		जाओ err1;

	प्र_लिखो(file, "/dev/cpu/%d/msr", cpu);
	fd = खोलो(file, O_RDONLY);

	अगर (fd < 0)
		जाओ err1;

	अगर (lseek(fd, msr, प्रस्तुत_से) == -1)
		जाओ err2;

	अगर (पढ़ो(fd, &val, 8) != 8)
		जाओ err2;

	*lo = (uपूर्णांक32_t )(val & 0xffffffffull);
	*hi = (uपूर्णांक32_t )(val>>32 & 0xffffffffull);

	retval = 0;
err2:
	बंद(fd);
err1:
	वापस retval;
पूर्ण

अटल व्योम decode (अचिन्हित पूर्णांक msr)
अणु
	अचिन्हित पूर्णांक multiplier;
	अचिन्हित पूर्णांक mv;

	multiplier = ((msr >> 8) & 0xFF);

	mv = (((msr & 0xFF) * 16) + 700);

	म_लिखो("0x%x means multiplier %d @ %d mV\n", msr, multiplier, mv);
पूर्ण

अटल पूर्णांक decode_live(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक lo, hi;
	पूर्णांक err;

	err = rdmsr(cpu, MSR_IA32_PERF_STATUS, &lo, &hi);

	अगर (err) अणु
		म_लिखो("can't get MSR_IA32_PERF_STATUS for cpu %d\n", cpu);
		म_लिखो("Possible trouble: you don't run an Enhanced SpeedStep capable cpu\n");
		म_लिखो("or you are not root, or the msr driver is not present\n");
		वापस 1;
	पूर्ण

	decode(lo);

	वापस 0;
पूर्ण

पूर्णांक मुख्य (पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित पूर्णांक cpu, mode = 0;

	अगर (argc < 2)
		cpu = 0;
	अन्यथा अणु
		cpu = म_से_अदीर्घ(argv[1], शून्य, 0);
		अगर (cpu >= MCPU)
			mode = 1;
	पूर्ण

	अगर (mode)
		decode(cpu);
	अन्यथा
		decode_live(cpu);

	वापस 0;
पूर्ण
