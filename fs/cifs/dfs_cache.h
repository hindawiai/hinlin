<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * DFS referral cache routines
 *
 * Copyright (c) 2018-2019 Paulo Alcantara <palcantara@suse.de>
 */

#अगर_अघोषित _CIFS_DFS_CACHE_H
#घोषणा _CIFS_DFS_CACHE_H

#समावेश <linux/nls.h>
#समावेश <linux/list.h>
#समावेश "cifsglob.h"

काष्ठा dfs_cache_tgt_list अणु
	पूर्णांक tl_numtgts;
	काष्ठा list_head tl_list;
पूर्ण;

काष्ठा dfs_cache_tgt_iterator अणु
	अक्षर *it_name;
	पूर्णांक it_path_consumed;
	काष्ठा list_head it_list;
पूर्ण;

बाह्य पूर्णांक dfs_cache_init(व्योम);
बाह्य व्योम dfs_cache_destroy(व्योम);
बाह्य स्थिर काष्ठा proc_ops dfscache_proc_ops;

बाह्य पूर्णांक dfs_cache_find(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			  स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap,
			  स्थिर अक्षर *path, काष्ठा dfs_info3_param *ref,
			  काष्ठा dfs_cache_tgt_list *tgt_list);
बाह्य पूर्णांक dfs_cache_noreq_find(स्थिर अक्षर *path, काष्ठा dfs_info3_param *ref,
				काष्ठा dfs_cache_tgt_list *tgt_list);
बाह्य पूर्णांक dfs_cache_update_tgthपूर्णांक(स्थिर अचिन्हित पूर्णांक xid,
				    काष्ठा cअगरs_ses *ses,
				    स्थिर काष्ठा nls_table *nls_codepage,
				    पूर्णांक remap, स्थिर अक्षर *path,
				    स्थिर काष्ठा dfs_cache_tgt_iterator *it);
बाह्य पूर्णांक
dfs_cache_noreq_update_tgthपूर्णांक(स्थिर अक्षर *path,
			       स्थिर काष्ठा dfs_cache_tgt_iterator *it);
बाह्य पूर्णांक dfs_cache_get_tgt_referral(स्थिर अक्षर *path,
				      स्थिर काष्ठा dfs_cache_tgt_iterator *it,
				      काष्ठा dfs_info3_param *ref);
बाह्य पूर्णांक dfs_cache_add_vol(अक्षर *mntdata, काष्ठा smb3_fs_context *ctx,
			स्थिर अक्षर *fullpath);
बाह्य पूर्णांक dfs_cache_update_vol(स्थिर अक्षर *fullpath,
				काष्ठा TCP_Server_Info *server);
बाह्य व्योम dfs_cache_del_vol(स्थिर अक्षर *fullpath);
बाह्य पूर्णांक dfs_cache_get_tgt_share(अक्षर *path, स्थिर काष्ठा dfs_cache_tgt_iterator *it,
				   अक्षर **share, अक्षर **prefix);

अटल अंतरभूत काष्ठा dfs_cache_tgt_iterator *
dfs_cache_get_next_tgt(काष्ठा dfs_cache_tgt_list *tl,
		       काष्ठा dfs_cache_tgt_iterator *it)
अणु
	अगर (!tl || list_empty(&tl->tl_list) || !it ||
	    list_is_last(&it->it_list, &tl->tl_list))
		वापस शून्य;
	वापस list_next_entry(it, it_list);
पूर्ण

अटल अंतरभूत काष्ठा dfs_cache_tgt_iterator *
dfs_cache_get_tgt_iterator(काष्ठा dfs_cache_tgt_list *tl)
अणु
	अगर (!tl)
		वापस शून्य;
	वापस list_first_entry_or_null(&tl->tl_list,
					काष्ठा dfs_cache_tgt_iterator,
					it_list);
पूर्ण

अटल अंतरभूत व्योम dfs_cache_मुक्त_tgts(काष्ठा dfs_cache_tgt_list *tl)
अणु
	काष्ठा dfs_cache_tgt_iterator *it, *nit;

	अगर (!tl || list_empty(&tl->tl_list))
		वापस;
	list_क्रम_each_entry_safe(it, nit, &tl->tl_list, it_list) अणु
		list_del(&it->it_list);
		kमुक्त(it->it_name);
		kमुक्त(it);
	पूर्ण
	tl->tl_numtgts = 0;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
dfs_cache_get_tgt_name(स्थिर काष्ठा dfs_cache_tgt_iterator *it)
अणु
	वापस it ? it->it_name : शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक
dfs_cache_get_nr_tgts(स्थिर काष्ठा dfs_cache_tgt_list *tl)
अणु
	वापस tl ? tl->tl_numtgts : 0;
पूर्ण

#पूर्ण_अगर /* _CIFS_DFS_CACHE_H */
