<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org)
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __MCONSOLE_H__
#घोषणा __MCONSOLE_H__

#अगर_घोषित __UM_HOST__
#समावेश <मानक_निवेशt.h>
#घोषणा u32 uपूर्णांक32_t
#पूर्ण_अगर

#समावेश <sysdep/ptrace.h>

#घोषणा MCONSOLE_MAGIC (0xcafebabe)
#घोषणा MCONSOLE_MAX_DATA (512)
#घोषणा MCONSOLE_VERSION 2

काष्ठा mconsole_request अणु
	u32 magic;
	u32 version;
	u32 len;
	अक्षर data[MCONSOLE_MAX_DATA];
पूर्ण;

काष्ठा mconsole_reply अणु
	u32 err;
	u32 more;
	u32 len;
	अक्षर data[MCONSOLE_MAX_DATA];
पूर्ण;

काष्ठा mconsole_notअगरy अणु
	u32 magic;
	u32 version;
	क्रमागत अणु MCONSOLE_SOCKET, MCONSOLE_PANIC, MCONSOLE_HANG,
	       MCONSOLE_USER_NOTIFY पूर्ण type;
	u32 len;
	अक्षर data[MCONSOLE_MAX_DATA];
पूर्ण;

काष्ठा mc_request;

क्रमागत mc_context अणु MCONSOLE_INTR, MCONSOLE_PROC पूर्ण;

काष्ठा mconsole_command
अणु
	अक्षर *command;
	व्योम (*handler)(काष्ठा mc_request *req);
	क्रमागत mc_context context;
पूर्ण;

काष्ठा mc_request
अणु
	पूर्णांक len;
	पूर्णांक as_पूर्णांकerrupt;

	पूर्णांक originating_fd;
	अचिन्हित पूर्णांक originlen;
	अचिन्हित अक्षर origin[128];			/* sockaddr_un */

	काष्ठा mconsole_request request;
	काष्ठा mconsole_command *cmd;
	काष्ठा uml_pt_regs regs;
पूर्ण;

बाह्य अक्षर mconsole_socket_name[];

बाह्य पूर्णांक mconsole_unlink_socket(व्योम);
बाह्य पूर्णांक mconsole_reply_len(काष्ठा mc_request *req, स्थिर अक्षर *reply,
			      पूर्णांक len, पूर्णांक err, पूर्णांक more);
बाह्य पूर्णांक mconsole_reply(काष्ठा mc_request *req, स्थिर अक्षर *str, पूर्णांक err,
			  पूर्णांक more);

बाह्य व्योम mconsole_version(काष्ठा mc_request *req);
बाह्य व्योम mconsole_help(काष्ठा mc_request *req);
बाह्य व्योम mconsole_halt(काष्ठा mc_request *req);
बाह्य व्योम mconsole_reboot(काष्ठा mc_request *req);
बाह्य व्योम mconsole_config(काष्ठा mc_request *req);
बाह्य व्योम mconsole_हटाओ(काष्ठा mc_request *req);
बाह्य व्योम mconsole_sysrq(काष्ठा mc_request *req);
बाह्य व्योम mconsole_cad(काष्ठा mc_request *req);
बाह्य व्योम mconsole_stop(काष्ठा mc_request *req);
बाह्य व्योम mconsole_go(काष्ठा mc_request *req);
बाह्य व्योम mconsole_log(काष्ठा mc_request *req);
बाह्य व्योम mconsole_proc(काष्ठा mc_request *req);
बाह्य व्योम mconsole_stack(काष्ठा mc_request *req);

बाह्य पूर्णांक mconsole_get_request(पूर्णांक fd, काष्ठा mc_request *req);
बाह्य पूर्णांक mconsole_notअगरy(अक्षर *sock_name, पूर्णांक type, स्थिर व्योम *data,
			   पूर्णांक len);
बाह्य अक्षर *mconsole_notअगरy_socket(व्योम);
बाह्य व्योम lock_notअगरy(व्योम);
बाह्य व्योम unlock_notअगरy(व्योम);

#पूर्ण_अगर
