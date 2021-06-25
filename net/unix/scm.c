<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/net.h>
#समावेश <linux/fs.h>
#समावेश <net/af_unix.h>
#समावेश <net/scm.h>
#समावेश <linux/init.h>
#समावेश <linux/io_uring.h>

#समावेश "scm.h"

अचिन्हित पूर्णांक unix_tot_inflight;
EXPORT_SYMBOL(unix_tot_inflight);

LIST_HEAD(gc_inflight_list);
EXPORT_SYMBOL(gc_inflight_list);

DEFINE_SPINLOCK(unix_gc_lock);
EXPORT_SYMBOL(unix_gc_lock);

काष्ठा sock *unix_get_socket(काष्ठा file *filp)
अणु
	काष्ठा sock *u_sock = शून्य;
	काष्ठा inode *inode = file_inode(filp);

	/* Socket ? */
	अगर (S_ISSOCK(inode->i_mode) && !(filp->f_mode & FMODE_PATH)) अणु
		काष्ठा socket *sock = SOCKET_I(inode);
		काष्ठा sock *s = sock->sk;

		/* PF_UNIX ? */
		अगर (s && sock->ops && sock->ops->family == PF_UNIX)
			u_sock = s;
	पूर्ण अन्यथा अणु
		/* Could be an io_uring instance */
		u_sock = io_uring_get_socket(filp);
	पूर्ण
	वापस u_sock;
पूर्ण
EXPORT_SYMBOL(unix_get_socket);

/* Keep the number of बार in flight count क्रम the file
 * descriptor अगर it is क्रम an AF_UNIX socket.
 */
व्योम unix_inflight(काष्ठा user_काष्ठा *user, काष्ठा file *fp)
अणु
	काष्ठा sock *s = unix_get_socket(fp);

	spin_lock(&unix_gc_lock);

	अगर (s) अणु
		काष्ठा unix_sock *u = unix_sk(s);

		अगर (atomic_दीर्घ_inc_वापस(&u->inflight) == 1) अणु
			BUG_ON(!list_empty(&u->link));
			list_add_tail(&u->link, &gc_inflight_list);
		पूर्ण अन्यथा अणु
			BUG_ON(list_empty(&u->link));
		पूर्ण
		unix_tot_inflight++;
	पूर्ण
	user->unix_inflight++;
	spin_unlock(&unix_gc_lock);
पूर्ण

व्योम unix_notinflight(काष्ठा user_काष्ठा *user, काष्ठा file *fp)
अणु
	काष्ठा sock *s = unix_get_socket(fp);

	spin_lock(&unix_gc_lock);

	अगर (s) अणु
		काष्ठा unix_sock *u = unix_sk(s);

		BUG_ON(!atomic_दीर्घ_पढ़ो(&u->inflight));
		BUG_ON(list_empty(&u->link));

		अगर (atomic_दीर्घ_dec_and_test(&u->inflight))
			list_del_init(&u->link);
		unix_tot_inflight--;
	पूर्ण
	user->unix_inflight--;
	spin_unlock(&unix_gc_lock);
पूर्ण

/*
 * The "user->unix_inflight" variable is रक्षित by the garbage
 * collection lock, and we just पढ़ो it locklessly here. If you go
 * over the limit, there might be a tiny race in actually noticing
 * it across thपढ़ोs. Tough.
 */
अटल अंतरभूत bool too_many_unix_fds(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा user_काष्ठा *user = current_user();

	अगर (unlikely(user->unix_inflight > task_rlimit(p, RLIMIT_NOखाता)))
		वापस !capable(CAP_SYS_RESOURCE) && !capable(CAP_SYS_ADMIN);
	वापस false;
पूर्ण

पूर्णांक unix_attach_fds(काष्ठा scm_cookie *scm, काष्ठा sk_buff *skb)
अणु
	पूर्णांक i;

	अगर (too_many_unix_fds(current))
		वापस -ETOOMANYREFS;

	/*
	 * Need to duplicate file references क्रम the sake of garbage
	 * collection.  Otherwise a socket in the fps might become a
	 * candidate क्रम GC जबतक the skb is not yet queued.
	 */
	UNIXCB(skb).fp = scm_fp_dup(scm->fp);
	अगर (!UNIXCB(skb).fp)
		वापस -ENOMEM;

	क्रम (i = scm->fp->count - 1; i >= 0; i--)
		unix_inflight(scm->fp->user, scm->fp->fp[i]);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(unix_attach_fds);

व्योम unix_detach_fds(काष्ठा scm_cookie *scm, काष्ठा sk_buff *skb)
अणु
	पूर्णांक i;

	scm->fp = UNIXCB(skb).fp;
	UNIXCB(skb).fp = शून्य;

	क्रम (i = scm->fp->count-1; i >= 0; i--)
		unix_notinflight(scm->fp->user, scm->fp->fp[i]);
पूर्ण
EXPORT_SYMBOL(unix_detach_fds);

व्योम unix_deकाष्ठा_scm(काष्ठा sk_buff *skb)
अणु
	काष्ठा scm_cookie scm;

	स_रखो(&scm, 0, माप(scm));
	scm.pid  = UNIXCB(skb).pid;
	अगर (UNIXCB(skb).fp)
		unix_detach_fds(&scm, skb);

	/* Alas, it calls VFS */
	/* So fscking what? fput() had been SMP-safe since the last Summer */
	scm_destroy(&scm);
	sock_wमुक्त(skb);
पूर्ण
EXPORT_SYMBOL(unix_deकाष्ठा_scm);
