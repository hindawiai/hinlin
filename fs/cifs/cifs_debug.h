<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *   Copyright (c) International Business Machines  Corp., 2000,2002
 *   Modअगरied by Steve French (sfrench@us.ibm.com)
*/

#अगर_अघोषित _H_CIFS_DEBUG
#घोषणा _H_CIFS_DEBUG

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) "CIFS: " fmt

व्योम cअगरs_dump_mem(अक्षर *label, व्योम *data, पूर्णांक length);
व्योम cअगरs_dump_detail(व्योम *buf, काष्ठा TCP_Server_Info *ptcp_info);
व्योम cअगरs_dump_mids(काष्ठा TCP_Server_Info *);
बाह्य bool traceSMB;		/* flag which enables the function below */
व्योम dump_smb(व्योम *, पूर्णांक);
#घोषणा CIFS_INFO	0x01
#घोषणा CIFS_RC		0x02
#घोषणा CIFS_TIMER	0x04

#घोषणा VFS 1
#घोषणा FYI 2
बाह्य पूर्णांक cअगरsFYI;
#अगर_घोषित CONFIG_CIFS_DEBUG2
#घोषणा NOISY 4
#अन्यथा
#घोषणा NOISY 0
#पूर्ण_अगर
#घोषणा ONCE 8

/*
 *	debug ON
 *	--------
 */
#अगर_घोषित CONFIG_CIFS_DEBUG


/*
 * When adding tracepoपूर्णांकs and debug messages we have various choices.
 * Some considerations:
 *
 * Use cअगरs_dbg(VFS, ...) क्रम things we always want logged, and the user to see
 *     cअगरs_info(...) slightly less important, admin can filter via loglevel > 6
 *     cअगरs_dbg(FYI, ...) minor debugging messages, off by शेष
 *     trace_smb3_*  ftrace functions are preferred क्रम complex debug messages
 *                 पूर्णांकended क्रम developers or experienced admins, off by शेष
 */

/* Inक्रमmation level messages, minor events */
#घोषणा cअगरs_info_func(ratefunc, fmt, ...)				\
	pr_info_ ## ratefunc(fmt, ##__VA_ARGS__)

#घोषणा cअगरs_info(fmt, ...)						\
	cअगरs_info_func(ratelimited, fmt, ##__VA_ARGS__)

/* inक्रमmation message: e.g., configuration, major event */
#घोषणा cअगरs_dbg_func(ratefunc, type, fmt, ...)				\
करो अणु									\
	अगर ((type) & FYI && cअगरsFYI & CIFS_INFO) अणु			\
		pr_debug_ ## ratefunc("%s: " fmt,			\
				      __खाता__, ##__VA_ARGS__);		\
	पूर्ण अन्यथा अगर ((type) & VFS) अणु					\
		pr_err_ ## ratefunc("VFS: " fmt, ##__VA_ARGS__);	\
	पूर्ण अन्यथा अगर ((type) & NOISY && (NOISY != 0)) अणु			\
		pr_debug_ ## ratefunc(fmt, ##__VA_ARGS__);		\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा cअगरs_dbg(type, fmt, ...)					\
करो अणु									\
	अगर ((type) & ONCE)						\
		cअगरs_dbg_func(once, type, fmt, ##__VA_ARGS__);		\
	अन्यथा								\
		cअगरs_dbg_func(ratelimited, type, fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा cअगरs_server_dbg_func(ratefunc, type, fmt, ...)			\
करो अणु									\
	स्थिर अक्षर *sn = "";						\
	अगर (server && server->hostname)					\
		sn = server->hostname;					\
	अगर ((type) & FYI && cअगरsFYI & CIFS_INFO) अणु			\
		pr_debug_ ## ratefunc("%s: \\\\%s " fmt,		\
				      __खाता__, sn, ##__VA_ARGS__);	\
	पूर्ण अन्यथा अगर ((type) & VFS) अणु					\
		pr_err_ ## ratefunc("VFS: \\\\%s " fmt,			\
				    sn, ##__VA_ARGS__);			\
	पूर्ण अन्यथा अगर ((type) & NOISY && (NOISY != 0)) अणु			\
		pr_debug_ ## ratefunc("\\\\%s " fmt,			\
				      sn, ##__VA_ARGS__);		\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा cअगरs_server_dbg(type, fmt, ...)					\
करो अणु									\
	अगर ((type) & ONCE)						\
		cअगरs_server_dbg_func(once, type, fmt, ##__VA_ARGS__);	\
	अन्यथा								\
		cअगरs_server_dbg_func(ratelimited, type, fmt,		\
				     ##__VA_ARGS__);			\
पूर्ण जबतक (0)

#घोषणा cअगरs_tcon_dbg_func(ratefunc, type, fmt, ...)			\
करो अणु									\
	स्थिर अक्षर *tn = "";						\
	अगर (tcon && tcon->treeName)					\
		tn = tcon->treeName;					\
	अगर ((type) & FYI && cअगरsFYI & CIFS_INFO) अणु			\
		pr_debug_ ## ratefunc("%s: %s "	fmt,			\
				      __खाता__, tn, ##__VA_ARGS__);	\
	पूर्ण अन्यथा अगर ((type) & VFS) अणु					\
		pr_err_ ## ratefunc("VFS: %s " fmt, tn, ##__VA_ARGS__);	\
	पूर्ण अन्यथा अगर ((type) & NOISY && (NOISY != 0)) अणु			\
		pr_debug_ ## ratefunc("%s " fmt, tn, ##__VA_ARGS__);	\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा cअगरs_tcon_dbg(type, fmt, ...)					\
करो अणु									\
	अगर ((type) & ONCE)						\
		cअगरs_tcon_dbg_func(once, type, fmt, ##__VA_ARGS__);	\
	अन्यथा								\
		cअगरs_tcon_dbg_func(ratelimited, type, fmt,		\
				   ##__VA_ARGS__);			\
पूर्ण जबतक (0)

/*
 *	debug OFF
 *	---------
 */
#अन्यथा		/* _CIFS_DEBUG */
#घोषणा cअगरs_dbg(type, fmt, ...)					\
करो अणु									\
	अगर (0)								\
		pr_debug(fmt, ##__VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा cअगरs_server_dbg(type, fmt, ...)					\
करो अणु									\
	अगर (0)								\
		pr_debug("\\\\%s " fmt,					\
			 server->hostname, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा cअगरs_tcon_dbg(type, fmt, ...)					\
करो अणु									\
	अगर (0)								\
		pr_debug("%s " fmt, tcon->treeName, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा cअगरs_info(fmt, ...)						\
	pr_info(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#पूर्ण_अगर				/* _H_CIFS_DEBUG */
