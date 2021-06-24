<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * The proc fileप्रणाली स्थिरants/काष्ठाures
 */
#अगर_अघोषित _LINUX_PROC_FS_H
#घोषणा _LINUX_PROC_FS_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>

काष्ठा proc_dir_entry;
काष्ठा seq_file;
काष्ठा seq_operations;

क्रमागत अणु
	/*
	 * All /proc entries using this ->proc_ops instance are never हटाओd.
	 *
	 * If in करोubt, ignore this flag.
	 */
#अगर_घोषित MODULE
	PROC_ENTRY_PERMANENT = 0U,
#अन्यथा
	PROC_ENTRY_PERMANENT = 1U << 0,
#पूर्ण_अगर
पूर्ण;

काष्ठा proc_ops अणु
	अचिन्हित पूर्णांक proc_flags;
	पूर्णांक	(*proc_खोलो)(काष्ठा inode *, काष्ठा file *);
	sमाप_प्रकार	(*proc_पढ़ो)(काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
	sमाप_प्रकार (*proc_पढ़ो_iter)(काष्ठा kiocb *, काष्ठा iov_iter *);
	sमाप_प्रकार	(*proc_ग_लिखो)(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
	/* mandatory unless nonseekable_खोलो() or equivalent is used */
	loff_t	(*proc_lseek)(काष्ठा file *, loff_t, पूर्णांक);
	पूर्णांक	(*proc_release)(काष्ठा inode *, काष्ठा file *);
	__poll_t (*proc_poll)(काष्ठा file *, काष्ठा poll_table_काष्ठा *);
	दीर्घ	(*proc_ioctl)(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#अगर_घोषित CONFIG_COMPAT
	दीर्घ	(*proc_compat_ioctl)(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#पूर्ण_अगर
	पूर्णांक	(*proc_mmap)(काष्ठा file *, काष्ठा vm_area_काष्ठा *);
	अचिन्हित दीर्घ (*proc_get_unmapped_area)(काष्ठा file *, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
पूर्ण __अक्रमomize_layout;

/* definitions क्रम hide_pid field */
क्रमागत proc_hidepid अणु
	HIDEPID_OFF	  = 0,
	HIDEPID_NO_ACCESS = 1,
	HIDEPID_INVISIBLE = 2,
	HIDEPID_NOT_PTRACEABLE = 4, /* Limit pids to only ptraceable pids */
पूर्ण;

/* definitions क्रम proc mount option piकरोnly */
क्रमागत proc_piकरोnly अणु
	PROC_PIDONLY_OFF = 0,
	PROC_PIDONLY_ON  = 1,
पूर्ण;

काष्ठा proc_fs_info अणु
	काष्ठा pid_namespace *pid_ns;
	काष्ठा dentry *proc_self;        /* For /proc/self */
	काष्ठा dentry *proc_thपढ़ो_self; /* For /proc/thपढ़ो-self */
	kgid_t pid_gid;
	क्रमागत proc_hidepid hide_pid;
	क्रमागत proc_piकरोnly piकरोnly;
पूर्ण;

अटल अंतरभूत काष्ठा proc_fs_info *proc_sb_info(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

प्रकार पूर्णांक (*proc_ग_लिखो_t)(काष्ठा file *, अक्षर *, माप_प्रकार);

बाह्य व्योम proc_root_init(व्योम);
बाह्य व्योम proc_flush_pid(काष्ठा pid *);

बाह्य काष्ठा proc_dir_entry *proc_symlink(स्थिर अक्षर *,
		काष्ठा proc_dir_entry *, स्थिर अक्षर *);
काष्ठा proc_dir_entry *_proc_सूची_गढ़ो(स्थिर अक्षर *, umode_t, काष्ठा proc_dir_entry *, व्योम *, bool);
बाह्य काष्ठा proc_dir_entry *proc_सूची_गढ़ो(स्थिर अक्षर *, काष्ठा proc_dir_entry *);
बाह्य काष्ठा proc_dir_entry *proc_सूची_गढ़ो_data(स्थिर अक्षर *, umode_t,
					      काष्ठा proc_dir_entry *, व्योम *);
बाह्य काष्ठा proc_dir_entry *proc_सूची_गढ़ो_mode(स्थिर अक्षर *, umode_t,
					      काष्ठा proc_dir_entry *);
काष्ठा proc_dir_entry *proc_create_mount_poपूर्णांक(स्थिर अक्षर *name);

काष्ठा proc_dir_entry *proc_create_seq_निजी(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent, स्थिर काष्ठा seq_operations *ops,
		अचिन्हित पूर्णांक state_size, व्योम *data);
#घोषणा proc_create_seq_data(name, mode, parent, ops, data) \
	proc_create_seq_निजी(name, mode, parent, ops, 0, data)
#घोषणा proc_create_seq(name, mode, parent, ops) \
	proc_create_seq_निजी(name, mode, parent, ops, 0, शून्य)
काष्ठा proc_dir_entry *proc_create_single_data(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent,
		पूर्णांक (*show)(काष्ठा seq_file *, व्योम *), व्योम *data);
#घोषणा proc_create_single(name, mode, parent, show) \
	proc_create_single_data(name, mode, parent, show, शून्य)
 
बाह्य काष्ठा proc_dir_entry *proc_create_data(स्थिर अक्षर *, umode_t,
					       काष्ठा proc_dir_entry *,
					       स्थिर काष्ठा proc_ops *,
					       व्योम *);

काष्ठा proc_dir_entry *proc_create(स्थिर अक्षर *name, umode_t mode, काष्ठा proc_dir_entry *parent, स्थिर काष्ठा proc_ops *proc_ops);
बाह्य व्योम proc_set_size(काष्ठा proc_dir_entry *, loff_t);
बाह्य व्योम proc_set_user(काष्ठा proc_dir_entry *, kuid_t, kgid_t);
बाह्य व्योम *PDE_DATA(स्थिर काष्ठा inode *);
बाह्य व्योम *proc_get_parent_data(स्थिर काष्ठा inode *);
बाह्य व्योम proc_हटाओ(काष्ठा proc_dir_entry *);
बाह्य व्योम हटाओ_proc_entry(स्थिर अक्षर *, काष्ठा proc_dir_entry *);
बाह्य पूर्णांक हटाओ_proc_subtree(स्थिर अक्षर *, काष्ठा proc_dir_entry *);

काष्ठा proc_dir_entry *proc_create_net_data(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent, स्थिर काष्ठा seq_operations *ops,
		अचिन्हित पूर्णांक state_size, व्योम *data);
#घोषणा proc_create_net(name, mode, parent, ops, state_size) \
	proc_create_net_data(name, mode, parent, ops, state_size, शून्य)
काष्ठा proc_dir_entry *proc_create_net_single(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent,
		पूर्णांक (*show)(काष्ठा seq_file *, व्योम *), व्योम *data);
काष्ठा proc_dir_entry *proc_create_net_data_ग_लिखो(स्थिर अक्षर *name, umode_t mode,
						  काष्ठा proc_dir_entry *parent,
						  स्थिर काष्ठा seq_operations *ops,
						  proc_ग_लिखो_t ग_लिखो,
						  अचिन्हित पूर्णांक state_size, व्योम *data);
काष्ठा proc_dir_entry *proc_create_net_single_ग_लिखो(स्थिर अक्षर *name, umode_t mode,
						    काष्ठा proc_dir_entry *parent,
						    पूर्णांक (*show)(काष्ठा seq_file *, व्योम *),
						    proc_ग_लिखो_t ग_लिखो,
						    व्योम *data);
बाह्य काष्ठा pid *tgid_pidfd_to_pid(स्थिर काष्ठा file *file);

काष्ठा bpf_iter_aux_info;
बाह्य पूर्णांक bpf_iter_init_seq_net(व्योम *priv_data, काष्ठा bpf_iter_aux_info *aux);
बाह्य व्योम bpf_iter_fini_seq_net(व्योम *priv_data);

#अगर_घोषित CONFIG_PROC_PID_ARCH_STATUS
/*
 * The architecture which selects CONFIG_PROC_PID_ARCH_STATUS must
 * provide proc_pid_arch_status() definition.
 */
पूर्णांक proc_pid_arch_status(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			काष्ठा pid *pid, काष्ठा task_काष्ठा *task);
#पूर्ण_अगर /* CONFIG_PROC_PID_ARCH_STATUS */

#अन्यथा /* CONFIG_PROC_FS */

अटल अंतरभूत व्योम proc_root_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम proc_flush_pid(काष्ठा pid *pid)
अणु
पूर्ण

अटल अंतरभूत काष्ठा proc_dir_entry *proc_symlink(स्थिर अक्षर *name,
		काष्ठा proc_dir_entry *parent,स्थिर अक्षर *dest) अणु वापस शून्य;पूर्ण
अटल अंतरभूत काष्ठा proc_dir_entry *proc_सूची_गढ़ो(स्थिर अक्षर *name,
	काष्ठा proc_dir_entry *parent) अणुवापस शून्य;पूर्ण
अटल अंतरभूत काष्ठा proc_dir_entry *proc_create_mount_poपूर्णांक(स्थिर अक्षर *name) अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा proc_dir_entry *_proc_सूची_गढ़ो(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent, व्योम *data, bool क्रमce_lookup)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा proc_dir_entry *proc_सूची_गढ़ो_data(स्थिर अक्षर *name,
	umode_t mode, काष्ठा proc_dir_entry *parent, व्योम *data) अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा proc_dir_entry *proc_सूची_गढ़ो_mode(स्थिर अक्षर *name,
	umode_t mode, काष्ठा proc_dir_entry *parent) अणु वापस शून्य; पूर्ण
#घोषणा proc_create_seq_निजी(name, mode, parent, ops, size, data) (अणुशून्य;पूर्ण)
#घोषणा proc_create_seq_data(name, mode, parent, ops, data) (अणुशून्य;पूर्ण)
#घोषणा proc_create_seq(name, mode, parent, ops) (अणुशून्य;पूर्ण)
#घोषणा proc_create_single(name, mode, parent, show) (अणुशून्य;पूर्ण)
#घोषणा proc_create_single_data(name, mode, parent, show, data) (अणुशून्य;पूर्ण)
#घोषणा proc_create(name, mode, parent, proc_ops) (अणुशून्य;पूर्ण)
#घोषणा proc_create_data(name, mode, parent, proc_ops, data) (अणुशून्य;पूर्ण)

अटल अंतरभूत व्योम proc_set_size(काष्ठा proc_dir_entry *de, loff_t size) अणुपूर्ण
अटल अंतरभूत व्योम proc_set_user(काष्ठा proc_dir_entry *de, kuid_t uid, kgid_t gid) अणुपूर्ण
अटल अंतरभूत व्योम *PDE_DATA(स्थिर काष्ठा inode *inode) अणुBUG(); वापस शून्य;पूर्ण
अटल अंतरभूत व्योम *proc_get_parent_data(स्थिर काष्ठा inode *inode) अणु BUG(); वापस शून्य; पूर्ण

अटल अंतरभूत व्योम proc_हटाओ(काष्ठा proc_dir_entry *de) अणुपूर्ण
#घोषणा हटाओ_proc_entry(name, parent) करो अणुपूर्ण जबतक (0)
अटल अंतरभूत पूर्णांक हटाओ_proc_subtree(स्थिर अक्षर *name, काष्ठा proc_dir_entry *parent) अणु वापस 0; पूर्ण

#घोषणा proc_create_net_data(name, mode, parent, ops, state_size, data) (अणुशून्य;पूर्ण)
#घोषणा proc_create_net(name, mode, parent, state_size, ops) (अणुशून्य;पूर्ण)
#घोषणा proc_create_net_single(name, mode, parent, show, data) (अणुशून्य;पूर्ण)

अटल अंतरभूत काष्ठा pid *tgid_pidfd_to_pid(स्थिर काष्ठा file *file)
अणु
	वापस ERR_PTR(-EBADF);
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */

काष्ठा net;

अटल अंतरभूत काष्ठा proc_dir_entry *proc_net_सूची_गढ़ो(
	काष्ठा net *net, स्थिर अक्षर *name, काष्ठा proc_dir_entry *parent)
अणु
	वापस _proc_सूची_गढ़ो(name, 0, parent, net, true);
पूर्ण

काष्ठा ns_common;
पूर्णांक खोलो_related_ns(काष्ठा ns_common *ns,
		   काष्ठा ns_common *(*get_ns)(काष्ठा ns_common *ns));

/* get the associated pid namespace क्रम a file in procfs */
अटल अंतरभूत काष्ठा pid_namespace *proc_pid_ns(काष्ठा super_block *sb)
अणु
	वापस proc_sb_info(sb)->pid_ns;
पूर्ण

bool proc_ns_file(स्थिर काष्ठा file *file);

#पूर्ण_अगर /* _LINUX_PROC_FS_H */
