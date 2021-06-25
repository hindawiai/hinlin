<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Procfs support क्रम lockd
 *
 * Copyright (c) 2014 Jeff Layton <jlayton@primarydata.com>
 */
#अगर_अघोषित _LOCKD_PROCFS_H
#घोषणा _LOCKD_PROCFS_H

#अगर IS_ENABLED(CONFIG_PROC_FS)
पूर्णांक lockd_create_procfs(व्योम);
व्योम lockd_हटाओ_procfs(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक
lockd_create_procfs(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
lockd_हटाओ_procfs(व्योम)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_PROC_FS) */

#पूर्ण_अगर /* _LOCKD_PROCFS_H */
