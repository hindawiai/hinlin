<शैली गुरु>
#अगर_अघोषित _FS_NFSD_खाताCACHE_H
#घोषणा _FS_NFSD_खाताCACHE_H

#समावेश <linux/fsnotअगरy_backend.h>

/*
 * This is the fsnotअगरy_mark container that nfsd attaches to the files that it
 * is holding खोलो. Note that we have a separate refcount here aside from the
 * one in the fsnotअगरy_mark. We only want a single fsnotअगरy_mark attached to
 * the inode, and क्रम each nfsd_file to hold a reference to it.
 *
 * The fsnotअगरy_mark is itself refcounted, but that's not sufficient to tell us
 * how to put that reference. If there are still outstanding nfsd_files that
 * reference the mark, then we would want to call fsnotअगरy_put_mark on it.
 * If there were not, then we'd need to call fsnotअगरy_destroy_mark. Since we
 * can't really tell the dअगरference, we use the nfm_mark to keep track of how
 * many nfsd_files hold references to the mark. When that counter goes to zero
 * then we know to call fsnotअगरy_destroy_mark on it.
 */
काष्ठा nfsd_file_mark अणु
	काष्ठा fsnotअगरy_mark	nfm_mark;
	refcount_t		nfm_ref;
पूर्ण;

/*
 * A representation of a file that has been खोलोed by knfsd. These are hashed
 * in the hashtable by inode poपूर्णांकer value. Note that this object करोesn't
 * hold a reference to the inode by itself, so the nf_inode poपूर्णांकer should
 * never be dereferenced, only used क्रम comparison.
 */
काष्ठा nfsd_file अणु
	काष्ठा hlist_node	nf_node;
	काष्ठा list_head	nf_lru;
	काष्ठा rcu_head		nf_rcu;
	काष्ठा file		*nf_file;
	स्थिर काष्ठा cred	*nf_cred;
	काष्ठा net		*nf_net;
#घोषणा NFSD_खाता_HASHED	(0)
#घोषणा NFSD_खाता_PENDING	(1)
#घोषणा NFSD_खाता_BREAK_READ	(2)
#घोषणा NFSD_खाता_BREAK_WRITE	(3)
#घोषणा NFSD_खाता_REFERENCED	(4)
	अचिन्हित दीर्घ		nf_flags;
	काष्ठा inode		*nf_inode;
	अचिन्हित पूर्णांक		nf_hashval;
	refcount_t		nf_ref;
	अचिन्हित अक्षर		nf_may;
	काष्ठा nfsd_file_mark	*nf_mark;
	काष्ठा rw_semaphore	nf_rwsem;
पूर्ण;

पूर्णांक nfsd_file_cache_init(व्योम);
व्योम nfsd_file_cache_purge(काष्ठा net *);
व्योम nfsd_file_cache_shutकरोwn(व्योम);
पूर्णांक nfsd_file_cache_start_net(काष्ठा net *net);
व्योम nfsd_file_cache_shutकरोwn_net(काष्ठा net *net);
व्योम nfsd_file_put(काष्ठा nfsd_file *nf);
काष्ठा nfsd_file *nfsd_file_get(काष्ठा nfsd_file *nf);
व्योम nfsd_file_बंद_inode_sync(काष्ठा inode *inode);
bool nfsd_file_is_cached(काष्ठा inode *inode);
__be32 nfsd_file_acquire(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		  अचिन्हित पूर्णांक may_flags, काष्ठा nfsd_file **nfp);
पूर्णांक	nfsd_file_cache_stats_खोलो(काष्ठा inode *, काष्ठा file *);
#पूर्ण_अगर /* _FS_NFSD_खाताCACHE_H */
