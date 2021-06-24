<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Witness Service client क्रम CIFS
 *
 * Copyright (c) 2020 Samuel Cabrero <scabrero@suse.de>
 */

#अगर_अघोषित _CIFS_SWN_H
#घोषणा _CIFS_SWN_H
#समावेश "cifsglob.h"

काष्ठा cअगरs_tcon;
काष्ठा sk_buff;
काष्ठा genl_info;

#अगर_घोषित CONFIG_CIFS_SWN_UPCALL
बाह्य पूर्णांक cअगरs_swn_रेजिस्टर(काष्ठा cअगरs_tcon *tcon);

बाह्य पूर्णांक cअगरs_swn_unरेजिस्टर(काष्ठा cअगरs_tcon *tcon);

बाह्य पूर्णांक cअगरs_swn_notअगरy(काष्ठा sk_buff *skb, काष्ठा genl_info *info);

बाह्य व्योम cअगरs_swn_dump(काष्ठा seq_file *m);

बाह्य व्योम cअगरs_swn_check(व्योम);

अटल अंतरभूत bool cअगरs_swn_set_server_dstaddr(काष्ठा TCP_Server_Info *server)
अणु
	अगर (server->use_swn_dstaddr) अणु
		server->dstaddr = server->swn_dstaddr;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत व्योम cअगरs_swn_reset_server_dstaddr(काष्ठा TCP_Server_Info *server)
अणु
	server->use_swn_dstaddr = false;
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक cअगरs_swn_रेजिस्टर(काष्ठा cअगरs_tcon *tcon) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक cअगरs_swn_unरेजिस्टर(काष्ठा cअगरs_tcon *tcon) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक cअगरs_swn_notअगरy(काष्ठा sk_buff *s, काष्ठा genl_info *i) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम cअगरs_swn_dump(काष्ठा seq_file *m) अणुपूर्ण
अटल अंतरभूत व्योम cअगरs_swn_check(व्योम) अणुपूर्ण
अटल अंतरभूत bool cअगरs_swn_set_server_dstaddr(काष्ठा TCP_Server_Info *server) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम cअगरs_swn_reset_server_dstaddr(काष्ठा TCP_Server_Info *server) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_CIFS_SWN_UPCALL */
#पूर्ण_अगर /* _CIFS_SWN_H */
