<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_RESOURCE_H
#घोषणा _ASM_GENERIC_RESOURCE_H

#समावेश <uapi/यंत्र-generic/resource.h>


/*
 * boot-समय rlimit शेषs क्रम the init task:
 */
#घोषणा INIT_RLIMITS							\
अणु									\
	[RLIMIT_CPU]		= अणु  RLIM_अनन्त,  RLIM_अनन्त पूर्ण,	\
	[RLIMIT_FSIZE]		= अणु  RLIM_अनन्त,  RLIM_अनन्त पूर्ण,	\
	[RLIMIT_DATA]		= अणु  RLIM_अनन्त,  RLIM_अनन्त पूर्ण,	\
	[RLIMIT_STACK]		= अणु       _STK_LIM,  RLIM_अनन्त पूर्ण,	\
	[RLIMIT_CORE]		= अणु              0,  RLIM_अनन्त पूर्ण,	\
	[RLIMIT_RSS]		= अणु  RLIM_अनन्त,  RLIM_अनन्त पूर्ण,	\
	[RLIMIT_NPROC]		= अणु              0,              0 पूर्ण,	\
	[RLIMIT_NOखाता]		= अणु   INR_OPEN_CUR,   INR_OPEN_MAX पूर्ण,	\
	[RLIMIT_MEMLOCK]	= अणु    MLOCK_LIMIT,    MLOCK_LIMIT पूर्ण,	\
	[RLIMIT_AS]		= अणु  RLIM_अनन्त,  RLIM_अनन्त पूर्ण,	\
	[RLIMIT_LOCKS]		= अणु  RLIM_अनन्त,  RLIM_अनन्त पूर्ण,	\
	[RLIMIT_SIGPENDING]	= अणु 		0,	       0 पूर्ण,	\
	[RLIMIT_MSGQUEUE]	= अणु   MQ_BYTES_MAX,   MQ_BYTES_MAX पूर्ण,	\
	[RLIMIT_NICE]		= अणु 0, 0 पूर्ण,				\
	[RLIMIT_RTPRIO]		= अणु 0, 0 पूर्ण,				\
	[RLIMIT_RTTIME]		= अणु  RLIM_अनन्त,  RLIM_अनन्त पूर्ण,	\
पूर्ण

#पूर्ण_अगर
