<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2021 Cadence Design Systems Inc. */

#अगर_अघोषित _XTENSA_PLATFORM_ISS_SIMCALL_ISS_H
#घोषणा _XTENSA_PLATFORM_ISS_SIMCALL_ISS_H

/*
 *  System call like services offered by the simulator host.
 */

#घोषणा SYS_nop		0	/* unused */
#घोषणा SYS_निकास	1	/*x*/
#घोषणा SYS_विभाजन	2
#घोषणा SYS_पढ़ो	3	/*x*/
#घोषणा SYS_ग_लिखो	4	/*x*/
#घोषणा SYS_खोलो	5	/*x*/
#घोषणा SYS_बंद	6	/*x*/
#घोषणा SYS_नाम	7	/*x 38 - रुकोpid */
#घोषणा SYS_creat	8	/*x*/
#घोषणा SYS_link	9	/*x (not implemented on WIN32) */
#घोषणा SYS_unlink	10	/*x*/
#घोषणा SYS_execv	11	/* n/a - execve */
#घोषणा SYS_execve	12	/* 11 - स_बदलो */
#घोषणा SYS_pipe	13	/* 42 - समय */
#घोषणा SYS_stat	14	/* 106 - mknod */
#घोषणा SYS_chmod	15
#घोषणा SYS_chown	16	/* 202 - lchown */
#घोषणा SYS_uसमय	17	/* 30 - अवरोध */
#घोषणा SYS_रुको	18	/* n/a - oldstat */
#घोषणा SYS_lseek	19	/*x*/
#घोषणा SYS_getpid	20
#घोषणा SYS_isatty	21	/* n/a - mount */
#घोषणा SYS_ख_स्थिति	22	/* 108 - oldumount */
#घोषणा SYS_समय	23	/* 13 - setuid */
#घोषणा SYS_समय_लोofday 24	/*x 78 - getuid (not implemented on WIN32) */
#घोषणा SYS_बार	25	/*X 43 - sसमय (Xtensa-specअगरic implementation) */
#घोषणा SYS_socket      26
#घोषणा SYS_sendto      27
#घोषणा SYS_recvfrom    28
#घोषणा SYS_select_one  29      /* not compatible select, one file descriptor at the समय */
#घोषणा SYS_bind        30
#घोषणा SYS_ioctl	31

#घोषणा SYS_iss_argc	1000	/* वापसs value of argc */
#घोषणा SYS_iss_argv_size 1001	/* bytes needed क्रम argv & arg strings */
#घोषणा SYS_iss_set_argv 1002	/* saves argv & arg strings at given addr */

/*
 * SYS_select_one specअगरiers
 */

#घोषणा  XTISS_SELECT_ONE_READ    1
#घोषणा  XTISS_SELECT_ONE_WRITE   2
#घोषणा  XTISS_SELECT_ONE_EXCEPT  3

अटल पूर्णांक त्रुटि_सं;

अटल अंतरभूत पूर्णांक __simc(पूर्णांक a, पूर्णांक b, पूर्णांक c, पूर्णांक d)
अणु
	रेजिस्टर पूर्णांक a1 यंत्र("a2") = a;
	रेजिस्टर पूर्णांक b1 यंत्र("a3") = b;
	रेजिस्टर पूर्णांक c1 यंत्र("a4") = c;
	रेजिस्टर पूर्णांक d1 यंत्र("a5") = d;
	__यंत्र__ __अस्थिर__ (
			"simcall\n"
			: "+r"(a1), "+r"(b1)
			: "r"(c1), "r"(d1)
			: "memory");
	त्रुटि_सं = b1;
	वापस a1;
पूर्ण

#पूर्ण_अगर /* _XTENSA_PLATFORM_ISS_SIMCALL_ISS_H */
