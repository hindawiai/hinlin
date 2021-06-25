<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SYS_H
#घोषणा _LINUX_SYS_H

/*
 * This file is no दीर्घer used or needed
 */

/*
 * These are प्रणाली calls that will be हटाओd at some समय
 * due to newer versions existing..
 * (please be careful - ibcs2 may need some of these).
 */
#अगर_घोषित notdef
#घोषणा _sys_रुकोpid	_sys_old_syscall	/* _sys_रुको4 */
#घोषणा _sys_olduname	_sys_old_syscall	/* _sys_newuname */
#घोषणा _sys_uname	_sys_old_syscall	/* _sys_newuname */
#घोषणा _sys_stat	_sys_old_syscall	/* _sys_newstat */
#घोषणा _sys_ख_स्थिति	_sys_old_syscall	/* _sys_newख_स्थिति */
#घोषणा _sys_lstat	_sys_old_syscall	/* _sys_newlstat */
#घोषणा _sys_संकेत	_sys_old_syscall	/* _sys_sigaction */
#घोषणा _sys_sgeपंचांगask	_sys_old_syscall	/* _sys_sigprocmask */
#घोषणा _sys_sseपंचांगask	_sys_old_syscall	/* _sys_sigprocmask */
#पूर्ण_अगर

/*
 * These are प्रणाली calls that haven't been implemented yet
 * but have an entry in the table क्रम future expansion..
 */
#पूर्ण_अगर
