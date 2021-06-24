<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ERRNO_H
#घोषणा _LINUX_ERRNO_H

#समावेश <uapi/linux/त्रुटिसं.स>


/*
 * These should never be seen by user programs.  To वापस one of ERESTART*
 * codes, संकेत_pending() MUST be set.  Note that ptrace can observe these
 * at syscall निकास tracing, but they will never be left क्रम the debugged user
 * process to see.
 */
#घोषणा ERESTARTSYS	512
#घोषणा ERESTARTNOINTR	513
#घोषणा ERESTARTNOHAND	514	/* restart अगर no handler.. */
#घोषणा ENOIOCTLCMD	515	/* No ioctl command */
#घोषणा ERESTART_RESTARTBLOCK 516 /* restart by calling sys_restart_syscall */
#घोषणा EPROBE_DEFER	517	/* Driver requests probe retry */
#घोषणा EOPENSTALE	518	/* खोलो found a stale dentry */
#घोषणा ENOPARAM	519	/* Parameter not supported */

/* Defined क्रम the NFSv3 protocol */
#घोषणा EBADHANDLE	521	/* Illegal NFS file handle */
#घोषणा ENOTSYNC	522	/* Update synchronization mismatch */
#घोषणा EBADCOOKIE	523	/* Cookie is stale */
#घोषणा ENOTSUPP	524	/* Operation is not supported */
#घोषणा ETOOSMALL	525	/* Buffer or request is too small */
#घोषणा ESERVERFAULT	526	/* An untranslatable error occurred */
#घोषणा EBADTYPE	527	/* Type not supported by server */
#घोषणा EJUKEBOX	528	/* Request initiated, but will not complete beक्रमe समयout */
#घोषणा EIOCBQUEUED	529	/* iocb queued, will get completion event */
#घोषणा ERECALLCONFLICT	530	/* conflict with recalled state */

#पूर्ण_अगर
