<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_GENERIC_RESOURCE_H
#घोषणा _UAPI_ASM_GENERIC_RESOURCE_H

/*
 * Resource limit IDs
 *
 * ( Compatibility detail: there are architectures that have
 *   a dअगरferent rlimit ID order in the 5-9 range and want
 *   to keep that order क्रम binary compatibility. The reasons
 *   are historic and all new rlimits are identical across all
 *   arches. If an arch has such special order क्रम some rlimits
 *   then it defines them prior including यंत्र-generic/resource.h. )
 */

#घोषणा RLIMIT_CPU		0	/* CPU समय in sec */
#घोषणा RLIMIT_FSIZE		1	/* Maximum filesize */
#घोषणा RLIMIT_DATA		2	/* max data size */
#घोषणा RLIMIT_STACK		3	/* max stack size */
#घोषणा RLIMIT_CORE		4	/* max core file size */

#अगर_अघोषित RLIMIT_RSS
# define RLIMIT_RSS		5	/* max resident set size */
#पूर्ण_अगर

#अगर_अघोषित RLIMIT_NPROC
# define RLIMIT_NPROC		6	/* max number of processes */
#पूर्ण_अगर

#अगर_अघोषित RLIMIT_NOखाता
# define RLIMIT_NOखाता		7	/* max number of खोलो files */
#पूर्ण_अगर

#अगर_अघोषित RLIMIT_MEMLOCK
# define RLIMIT_MEMLOCK		8	/* max locked-in-memory address space */
#पूर्ण_अगर

#अगर_अघोषित RLIMIT_AS
# define RLIMIT_AS		9	/* address space limit */
#पूर्ण_अगर

#घोषणा RLIMIT_LOCKS		10	/* maximum file locks held */
#घोषणा RLIMIT_SIGPENDING	11	/* max number of pending संकेतs */
#घोषणा RLIMIT_MSGQUEUE		12	/* maximum bytes in POSIX mqueues */
#घोषणा RLIMIT_NICE		13	/* max nice prio allowed to उठाओ to
					   0-39 क्रम nice level 19 .. -20 */
#घोषणा RLIMIT_RTPRIO		14	/* maximum realसमय priority */
#घोषणा RLIMIT_RTTIME		15	/* समयout क्रम RT tasks in us */
#घोषणा RLIM_NLIMITS		16

/*
 * SuS says limits have to be अचिन्हित.
 * Which makes a ton more sense anyway.
 *
 * Some architectures override this (क्रम compatibility reasons):
 */
#अगर_अघोषित RLIM_अनन्त
# define RLIM_अनन्त		(~0UL)
#पूर्ण_अगर


#पूर्ण_अगर /* _UAPI_ASM_GENERIC_RESOURCE_H */
