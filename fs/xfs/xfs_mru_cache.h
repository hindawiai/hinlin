<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2006-2007 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_MRU_CACHE_H__
#घोषणा __XFS_MRU_CACHE_H__

काष्ठा xfs_mru_cache;

काष्ठा xfs_mru_cache_elem अणु
	काष्ठा list_head list_node;
	अचिन्हित दीर्घ	key;
पूर्ण;

/* Function poपूर्णांकer type क्रम callback to मुक्त a client's data poपूर्णांकer. */
प्रकार व्योम (*xfs_mru_cache_मुक्त_func_t)(व्योम *, काष्ठा xfs_mru_cache_elem *);

पूर्णांक xfs_mru_cache_init(व्योम);
व्योम xfs_mru_cache_uninit(व्योम);
पूर्णांक xfs_mru_cache_create(काष्ठा xfs_mru_cache **mrup, व्योम *data,
		अचिन्हित पूर्णांक lअगरeसमय_ms, अचिन्हित पूर्णांक grp_count,
		xfs_mru_cache_मुक्त_func_t मुक्त_func);
व्योम xfs_mru_cache_destroy(काष्ठा xfs_mru_cache *mru);
पूर्णांक xfs_mru_cache_insert(काष्ठा xfs_mru_cache *mru, अचिन्हित दीर्घ key,
		काष्ठा xfs_mru_cache_elem *elem);
काष्ठा xfs_mru_cache_elem *
xfs_mru_cache_हटाओ(काष्ठा xfs_mru_cache *mru, अचिन्हित दीर्घ key);
व्योम xfs_mru_cache_delete(काष्ठा xfs_mru_cache *mru, अचिन्हित दीर्घ key);
काष्ठा xfs_mru_cache_elem *
xfs_mru_cache_lookup(काष्ठा xfs_mru_cache *mru, अचिन्हित दीर्घ key);
व्योम xfs_mru_cache_करोne(काष्ठा xfs_mru_cache *mru);

#पूर्ण_अगर /* __XFS_MRU_CACHE_H__ */
