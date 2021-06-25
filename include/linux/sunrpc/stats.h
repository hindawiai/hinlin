<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/stats.h
 *
 * Client statistics collection क्रम SUN RPC
 *
 * Copyright (C) 1996 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित _LINUX_SUNRPC_STATS_H
#घोषणा _LINUX_SUNRPC_STATS_H

#समावेश <linux/proc_fs.h>

काष्ठा rpc_stat अणु
	स्थिर काष्ठा rpc_program *program;

	अचिन्हित पूर्णांक		netcnt,
				netudpcnt,
				nettcpcnt,
				nettcpconn,
				netreconn;
	अचिन्हित पूर्णांक		rpccnt,
				rpcretrans,
				rpcauthrefresh,
				rpcgarbage;
पूर्ण;

काष्ठा svc_stat अणु
	काष्ठा svc_program *	program;

	अचिन्हित पूर्णांक		netcnt,
				netudpcnt,
				nettcpcnt,
				nettcpconn;
	अचिन्हित पूर्णांक		rpccnt,
				rpcbadfmt,
				rpcbadauth,
				rpcbadclnt;
पूर्ण;

काष्ठा net;
#अगर_घोषित CONFIG_PROC_FS
पूर्णांक			rpc_proc_init(काष्ठा net *);
व्योम			rpc_proc_निकास(काष्ठा net *);
#अन्यथा
अटल अंतरभूत पूर्णांक rpc_proc_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rpc_proc_निकास(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित MODULE
व्योम			rpc_modcount(काष्ठा inode *, पूर्णांक);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS
काष्ठा proc_dir_entry *	rpc_proc_रेजिस्टर(काष्ठा net *,काष्ठा rpc_stat *);
व्योम			rpc_proc_unरेजिस्टर(काष्ठा net *,स्थिर अक्षर *);
व्योम			rpc_proc_zero(स्थिर काष्ठा rpc_program *);
काष्ठा proc_dir_entry *	svc_proc_रेजिस्टर(काष्ठा net *, काष्ठा svc_stat *,
					  स्थिर काष्ठा proc_ops *);
व्योम			svc_proc_unरेजिस्टर(काष्ठा net *, स्थिर अक्षर *);

व्योम			svc_seq_show(काष्ठा seq_file *,
				     स्थिर काष्ठा svc_stat *);
#अन्यथा

अटल अंतरभूत काष्ठा proc_dir_entry *rpc_proc_रेजिस्टर(काष्ठा net *net, काष्ठा rpc_stat *s) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम rpc_proc_unरेजिस्टर(काष्ठा net *net, स्थिर अक्षर *p) अणुपूर्ण
अटल अंतरभूत व्योम rpc_proc_zero(स्थिर काष्ठा rpc_program *p) अणुपूर्ण

अटल अंतरभूत काष्ठा proc_dir_entry *svc_proc_रेजिस्टर(काष्ठा net *net, काष्ठा svc_stat *s,
						       स्थिर काष्ठा proc_ops *proc_ops) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम svc_proc_unरेजिस्टर(काष्ठा net *net, स्थिर अक्षर *p) अणुपूर्ण

अटल अंतरभूत व्योम svc_seq_show(काष्ठा seq_file *seq,
				स्थिर काष्ठा svc_stat *st) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SUNRPC_STATS_H */
