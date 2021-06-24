<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * procfs namespace bits
 */
#अगर_अघोषित _LINUX_PROC_NS_H
#घोषणा _LINUX_PROC_NS_H

#समावेश <linux/ns_common.h>

काष्ठा pid_namespace;
काष्ठा nsset;
काष्ठा path;
काष्ठा task_काष्ठा;
काष्ठा inode;

काष्ठा proc_ns_operations अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *real_ns_name;
	पूर्णांक type;
	काष्ठा ns_common *(*get)(काष्ठा task_काष्ठा *task);
	व्योम (*put)(काष्ठा ns_common *ns);
	पूर्णांक (*install)(काष्ठा nsset *nsset, काष्ठा ns_common *ns);
	काष्ठा user_namespace *(*owner)(काष्ठा ns_common *ns);
	काष्ठा ns_common *(*get_parent)(काष्ठा ns_common *ns);
पूर्ण __अक्रमomize_layout;

बाह्य स्थिर काष्ठा proc_ns_operations netns_operations;
बाह्य स्थिर काष्ठा proc_ns_operations utsns_operations;
बाह्य स्थिर काष्ठा proc_ns_operations ipcns_operations;
बाह्य स्थिर काष्ठा proc_ns_operations pidns_operations;
बाह्य स्थिर काष्ठा proc_ns_operations pidns_क्रम_children_operations;
बाह्य स्थिर काष्ठा proc_ns_operations userns_operations;
बाह्य स्थिर काष्ठा proc_ns_operations mntns_operations;
बाह्य स्थिर काष्ठा proc_ns_operations cgroupns_operations;
बाह्य स्थिर काष्ठा proc_ns_operations समयns_operations;
बाह्य स्थिर काष्ठा proc_ns_operations समयns_क्रम_children_operations;

/*
 * We always define these क्रमागतerators
 */
क्रमागत अणु
	PROC_ROOT_INO		= 1,
	PROC_IPC_INIT_INO	= 0xEFFFFFFFU,
	PROC_UTS_INIT_INO	= 0xEFFFFFFEU,
	PROC_USER_INIT_INO	= 0xEFFFFFFDU,
	PROC_PID_INIT_INO	= 0xEFFFFFFCU,
	PROC_CGROUP_INIT_INO	= 0xEFFFFFFBU,
	PROC_TIME_INIT_INO	= 0xEFFFFFFAU,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS

बाह्य पूर्णांक proc_alloc_inum(अचिन्हित पूर्णांक *pino);
बाह्य व्योम proc_मुक्त_inum(अचिन्हित पूर्णांक inum);

#अन्यथा /* CONFIG_PROC_FS */

अटल अंतरभूत पूर्णांक proc_alloc_inum(अचिन्हित पूर्णांक *inum)
अणु
	*inum = 1;
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम proc_मुक्त_inum(अचिन्हित पूर्णांक inum) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल अंतरभूत पूर्णांक ns_alloc_inum(काष्ठा ns_common *ns)
अणु
	atomic_दीर्घ_set(&ns->stashed, 0);
	वापस proc_alloc_inum(&ns->inum);
पूर्ण

#घोषणा ns_मुक्त_inum(ns) proc_मुक्त_inum((ns)->inum)

बाह्य काष्ठा file *proc_ns_fget(पूर्णांक fd);
#घोषणा get_proc_ns(inode) ((काष्ठा ns_common *)(inode)->i_निजी)
बाह्य पूर्णांक ns_get_path(काष्ठा path *path, काष्ठा task_काष्ठा *task,
			स्थिर काष्ठा proc_ns_operations *ns_ops);
प्रकार काष्ठा ns_common *ns_get_path_helper_t(व्योम *);
बाह्य पूर्णांक ns_get_path_cb(काष्ठा path *path, ns_get_path_helper_t ns_get_cb,
			    व्योम *निजी_data);

बाह्य bool ns_match(स्थिर काष्ठा ns_common *ns, dev_t dev, ino_t ino);

बाह्य पूर्णांक ns_get_name(अक्षर *buf, माप_प्रकार size, काष्ठा task_काष्ठा *task,
			स्थिर काष्ठा proc_ns_operations *ns_ops);
बाह्य व्योम nsfs_init(व्योम);

#पूर्ण_अगर /* _LINUX_PROC_NS_H */
