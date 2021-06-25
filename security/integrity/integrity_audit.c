<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 IBM Corporation
 * Author: Mimi Zohar <zohar@us.ibm.com>
 *
 * File: पूर्णांकegrity_audit.c
 *	Audit calls क्रम the पूर्णांकegrity subप्रणाली
 */

#समावेश <linux/fs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/audit.h>
#समावेश "integrity.h"

अटल पूर्णांक पूर्णांकegrity_audit_info;

/* ima_audit_setup - enable inक्रमmational auditing messages */
अटल पूर्णांक __init पूर्णांकegrity_audit_setup(अक्षर *str)
अणु
	अचिन्हित दीर्घ audit;

	अगर (!kम_से_अदीर्घ(str, 0, &audit))
		पूर्णांकegrity_audit_info = audit ? 1 : 0;
	वापस 1;
पूर्ण
__setup("integrity_audit=", पूर्णांकegrity_audit_setup);

व्योम पूर्णांकegrity_audit_msg(पूर्णांक audit_msgno, काष्ठा inode *inode,
			 स्थिर अचिन्हित अक्षर *fname, स्थिर अक्षर *op,
			 स्थिर अक्षर *cause, पूर्णांक result, पूर्णांक audit_info)
अणु
	पूर्णांकegrity_audit_message(audit_msgno, inode, fname, op, cause,
				result, audit_info, 0);
पूर्ण

व्योम पूर्णांकegrity_audit_message(पूर्णांक audit_msgno, काष्ठा inode *inode,
			     स्थिर अचिन्हित अक्षर *fname, स्थिर अक्षर *op,
			     स्थिर अक्षर *cause, पूर्णांक result, पूर्णांक audit_info,
			     पूर्णांक त्रुटि_सं)
अणु
	काष्ठा audit_buffer *ab;
	अक्षर name[TASK_COMM_LEN];

	अगर (!पूर्णांकegrity_audit_info && audit_info == 1)	/* Skip info messages */
		वापस;

	ab = audit_log_start(audit_context(), GFP_KERNEL, audit_msgno);
	audit_log_क्रमmat(ab, "pid=%d uid=%u auid=%u ses=%u",
			 task_pid_nr(current),
			 from_kuid(&init_user_ns, current_uid()),
			 from_kuid(&init_user_ns, audit_get_loginuid(current)),
			 audit_get_sessionid(current));
	audit_log_task_context(ab);
	audit_log_क्रमmat(ab, " op=%s cause=%s comm=", op, cause);
	audit_log_untrustedstring(ab, get_task_comm(name, current));
	अगर (fname) अणु
		audit_log_क्रमmat(ab, " name=");
		audit_log_untrustedstring(ab, fname);
	पूर्ण
	अगर (inode) अणु
		audit_log_क्रमmat(ab, " dev=");
		audit_log_untrustedstring(ab, inode->i_sb->s_id);
		audit_log_क्रमmat(ab, " ino=%lu", inode->i_ino);
	पूर्ण
	audit_log_क्रमmat(ab, " res=%d errno=%d", !result, त्रुटि_सं);
	audit_log_end(ab);
पूर्ण
