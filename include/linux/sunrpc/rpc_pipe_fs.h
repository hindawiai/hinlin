<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SUNRPC_RPC_PIPE_FS_H
#घोषणा _LINUX_SUNRPC_RPC_PIPE_FS_H

#समावेश <linux/workqueue.h>

काष्ठा rpc_pipe_dir_head अणु
	काष्ठा list_head pdh_entries;
	काष्ठा dentry *pdh_dentry;
पूर्ण;

काष्ठा rpc_pipe_dir_object_ops;
काष्ठा rpc_pipe_dir_object अणु
	काष्ठा list_head pकरो_head;
	स्थिर काष्ठा rpc_pipe_dir_object_ops *pकरो_ops;

	व्योम *pकरो_data;
पूर्ण;

काष्ठा rpc_pipe_dir_object_ops अणु
	पूर्णांक (*create)(काष्ठा dentry *dir,
			काष्ठा rpc_pipe_dir_object *pकरो);
	व्योम (*destroy)(काष्ठा dentry *dir,
			काष्ठा rpc_pipe_dir_object *pकरो);
पूर्ण;

काष्ठा rpc_pipe_msg अणु
	काष्ठा list_head list;
	व्योम *data;
	माप_प्रकार len;
	माप_प्रकार copied;
	पूर्णांक त्रुटि_सं;
पूर्ण;

काष्ठा rpc_pipe_ops अणु
	sमाप_प्रकार (*upcall)(काष्ठा file *, काष्ठा rpc_pipe_msg *, अक्षर __user *, माप_प्रकार);
	sमाप_प्रकार (*करोwncall)(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार);
	व्योम (*release_pipe)(काष्ठा inode *);
	पूर्णांक (*खोलो_pipe)(काष्ठा inode *);
	व्योम (*destroy_msg)(काष्ठा rpc_pipe_msg *);
पूर्ण;

काष्ठा rpc_pipe अणु
	काष्ठा list_head pipe;
	काष्ठा list_head in_upcall;
	काष्ठा list_head in_करोwncall;
	पूर्णांक pipelen;
	पूर्णांक nपढ़ोers;
	पूर्णांक nग_लिखोrs;
#घोषणा RPC_PIPE_WAIT_FOR_OPEN	1
	पूर्णांक flags;
	काष्ठा delayed_work queue_समयout;
	स्थिर काष्ठा rpc_pipe_ops *ops;
	spinlock_t lock;
	काष्ठा dentry *dentry;
पूर्ण;

काष्ठा rpc_inode अणु
	काष्ठा inode vfs_inode;
	व्योम *निजी;
	काष्ठा rpc_pipe *pipe;
	रुको_queue_head_t रुकोq;
पूर्ण;

अटल अंतरभूत काष्ठा rpc_inode *
RPC_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा rpc_inode, vfs_inode);
पूर्ण

क्रमागत अणु
	SUNRPC_PIPEFS_NFS_PRIO,
	SUNRPC_PIPEFS_RPC_PRIO,
पूर्ण;

बाह्य पूर्णांक rpc_pipefs_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *);
बाह्य व्योम rpc_pipefs_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *);

क्रमागत अणु
	RPC_PIPEFS_MOUNT,
	RPC_PIPEFS_UMOUNT,
पूर्ण;

बाह्य काष्ठा dentry *rpc_d_lookup_sb(स्थिर काष्ठा super_block *sb,
				      स्थिर अचिन्हित अक्षर *dir_name);
बाह्य पूर्णांक rpc_pipefs_init_net(काष्ठा net *net);
बाह्य व्योम rpc_pipefs_निकास_net(काष्ठा net *net);
बाह्य काष्ठा super_block *rpc_get_sb_net(स्थिर काष्ठा net *net);
बाह्य व्योम rpc_put_sb_net(स्थिर काष्ठा net *net);

बाह्य sमाप_प्रकार rpc_pipe_generic_upcall(काष्ठा file *, काष्ठा rpc_pipe_msg *,
				       अक्षर __user *, माप_प्रकार);
बाह्य पूर्णांक rpc_queue_upcall(काष्ठा rpc_pipe *, काष्ठा rpc_pipe_msg *);

काष्ठा rpc_clnt;
बाह्य काष्ठा dentry *rpc_create_client_dir(काष्ठा dentry *, स्थिर अक्षर *, काष्ठा rpc_clnt *);
बाह्य पूर्णांक rpc_हटाओ_client_dir(काष्ठा rpc_clnt *);

बाह्य व्योम rpc_init_pipe_dir_head(काष्ठा rpc_pipe_dir_head *pdh);
बाह्य व्योम rpc_init_pipe_dir_object(काष्ठा rpc_pipe_dir_object *pकरो,
		स्थिर काष्ठा rpc_pipe_dir_object_ops *pकरो_ops,
		व्योम *pकरो_data);
बाह्य पूर्णांक rpc_add_pipe_dir_object(काष्ठा net *net,
		काष्ठा rpc_pipe_dir_head *pdh,
		काष्ठा rpc_pipe_dir_object *pकरो);
बाह्य व्योम rpc_हटाओ_pipe_dir_object(काष्ठा net *net,
		काष्ठा rpc_pipe_dir_head *pdh,
		काष्ठा rpc_pipe_dir_object *pकरो);
बाह्य काष्ठा rpc_pipe_dir_object *rpc_find_or_alloc_pipe_dir_object(
		काष्ठा net *net,
		काष्ठा rpc_pipe_dir_head *pdh,
		पूर्णांक (*match)(काष्ठा rpc_pipe_dir_object *, व्योम *),
		काष्ठा rpc_pipe_dir_object *(*alloc)(व्योम *),
		व्योम *data);

काष्ठा cache_detail;
बाह्य काष्ठा dentry *rpc_create_cache_dir(काष्ठा dentry *,
					   स्थिर अक्षर *,
					   umode_t umode,
					   काष्ठा cache_detail *);
बाह्य व्योम rpc_हटाओ_cache_dir(काष्ठा dentry *);

काष्ठा rpc_pipe *rpc_mkpipe_data(स्थिर काष्ठा rpc_pipe_ops *ops, पूर्णांक flags);
व्योम rpc_destroy_pipe_data(काष्ठा rpc_pipe *pipe);
बाह्य काष्ठा dentry *rpc_mkpipe_dentry(काष्ठा dentry *, स्थिर अक्षर *, व्योम *,
					काष्ठा rpc_pipe *);
बाह्य पूर्णांक rpc_unlink(काष्ठा dentry *);
बाह्य पूर्णांक रेजिस्टर_rpc_pipefs(व्योम);
बाह्य व्योम unरेजिस्टर_rpc_pipefs(व्योम);

बाह्य bool gssd_running(काष्ठा net *net);

#पूर्ण_अगर
