<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NET3:	Garbage Collector For AF_UNIX sockets
 *
 * Garbage Collector:
 *	Copyright (C) Barak A. Pearlmutter.
 *
 * Chopped about by Alan Cox 22/3/96 to make it fit the AF_UNIX socket problem.
 * If it करोesn't work blame me, it worked when Barak sent it.
 *
 * Assumptions:
 *
 *  - object w/ a bit
 *  - मुक्त list
 *
 * Current optimizations:
 *
 *  - explicit stack instead of recursion
 *  - tail recurse on first born instead of immediate push/pop
 *  - we gather the stuff that should not be समाप्तed पूर्णांकo tree
 *    and stack is just a path from root to the current poपूर्णांकer.
 *
 *  Future optimizations:
 *
 *  - करोn't just push entire root set; process in place
 *
 *  Fixes:
 *	Alan Cox	07 Sept	1997	Vदो_स्मृति पूर्णांकernal stack as needed.
 *					Cope with changing max_files.
 *	Al Viro		11 Oct 1998
 *		Graph may have cycles. That is, we can send the descriptor
 *		of foo to bar and vice versa. Current code chokes on that.
 *		Fix: move SCM_RIGHTS ones पूर्णांकo the separate list and then
 *		skb_मुक्त() them all instead of करोing explicit fput's.
 *		Another problem: since fput() may block somebody may
 *		create a new unix_socket when we are in the middle of sweep
 *		phase. Fix: revert the logic wrt MARKED. Mark everything
 *		upon the beginning and unmark non-junk ones.
 *
 *		[12 Oct 1998] AAARGH! New code purges all SCM_RIGHTS
 *		sent to connect()'ed but still not accept()'ed sockets.
 *		Fixed. Old code had slightly dअगरferent problem here:
 *		extra fput() in situation when we passed the descriptor via
 *		such socket and बंदd it (descriptor). That would happen on
 *		each unix_gc() until the accept(). Since the काष्ठा file in
 *		question would go to the मुक्त list and might be reused...
 *		That might be the reason of अक्रमom oopses on filp_बंद()
 *		in unrelated processes.
 *
 *	AV		28 Feb 1999
 *		Kill the explicit allocation of stack. Now we keep the tree
 *		with root in dummy + poपूर्णांकer (gc_current) to one of the nodes.
 *		Stack is represented as path from gc_current to dummy. Unmark
 *		now means "add to tree". Push == "make it a son of gc_current".
 *		Pop == "move gc_current to parent". We keep only poपूर्णांकers to
 *		parents (->gc_tree).
 *	AV		1 Mar 1999
 *		Damn. Added missing check क्रम ->dead in listen queues scanning.
 *
 *	Miklos Szeredi 25 Jun 2007
 *		Reimplement with a cycle collecting algorithm. This should
 *		solve several problems with the previous code, like being racy
 *		wrt receive and holding up unrelated socket operations.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/un.h>
#समावेश <linux/net.h>
#समावेश <linux/fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/रुको.h>

#समावेश <net/sock.h>
#समावेश <net/af_unix.h>
#समावेश <net/scm.h>
#समावेश <net/tcp_states.h>

#समावेश "scm.h"

/* Internal data काष्ठाures and अक्रमom procedures: */

अटल LIST_HEAD(gc_candidates);
अटल DECLARE_WAIT_QUEUE_HEAD(unix_gc_रुको);

अटल व्योम scan_inflight(काष्ठा sock *x, व्योम (*func)(काष्ठा unix_sock *),
			  काष्ठा sk_buff_head *hitlist)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *next;

	spin_lock(&x->sk_receive_queue.lock);
	skb_queue_walk_safe(&x->sk_receive_queue, skb, next) अणु
		/* Do we have file descriptors ? */
		अगर (UNIXCB(skb).fp) अणु
			bool hit = false;
			/* Process the descriptors of this socket */
			पूर्णांक nfd = UNIXCB(skb).fp->count;
			काष्ठा file **fp = UNIXCB(skb).fp->fp;

			जबतक (nfd--) अणु
				/* Get the socket the fd matches अगर it indeed करोes so */
				काष्ठा sock *sk = unix_get_socket(*fp++);

				अगर (sk) अणु
					काष्ठा unix_sock *u = unix_sk(sk);

					/* Ignore non-candidates, they could
					 * have been added to the queues after
					 * starting the garbage collection
					 */
					अगर (test_bit(UNIX_GC_CANDIDATE, &u->gc_flags)) अणु
						hit = true;

						func(u);
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (hit && hitlist != शून्य) अणु
				__skb_unlink(skb, &x->sk_receive_queue);
				__skb_queue_tail(hitlist, skb);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&x->sk_receive_queue.lock);
पूर्ण

अटल व्योम scan_children(काष्ठा sock *x, व्योम (*func)(काष्ठा unix_sock *),
			  काष्ठा sk_buff_head *hitlist)
अणु
	अगर (x->sk_state != TCP_LISTEN) अणु
		scan_inflight(x, func, hitlist);
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *skb;
		काष्ठा sk_buff *next;
		काष्ठा unix_sock *u;
		LIST_HEAD(embryos);

		/* For a listening socket collect the queued embryos
		 * and perक्रमm a scan on them as well.
		 */
		spin_lock(&x->sk_receive_queue.lock);
		skb_queue_walk_safe(&x->sk_receive_queue, skb, next) अणु
			u = unix_sk(skb->sk);

			/* An embryo cannot be in-flight, so it's safe
			 * to use the list link.
			 */
			BUG_ON(!list_empty(&u->link));
			list_add_tail(&u->link, &embryos);
		पूर्ण
		spin_unlock(&x->sk_receive_queue.lock);

		जबतक (!list_empty(&embryos)) अणु
			u = list_entry(embryos.next, काष्ठा unix_sock, link);
			scan_inflight(&u->sk, func, hitlist);
			list_del_init(&u->link);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dec_inflight(काष्ठा unix_sock *usk)
अणु
	atomic_दीर्घ_dec(&usk->inflight);
पूर्ण

अटल व्योम inc_inflight(काष्ठा unix_sock *usk)
अणु
	atomic_दीर्घ_inc(&usk->inflight);
पूर्ण

अटल व्योम inc_inflight_move_tail(काष्ठा unix_sock *u)
अणु
	atomic_दीर्घ_inc(&u->inflight);
	/* If this still might be part of a cycle, move it to the end
	 * of the list, so that it's checked even अगर it was alपढ़ोy
	 * passed over
	 */
	अगर (test_bit(UNIX_GC_MAYBE_CYCLE, &u->gc_flags))
		list_move_tail(&u->link, &gc_candidates);
पूर्ण

अटल bool gc_in_progress;
#घोषणा UNIX_INFLIGHT_TRIGGER_GC 16000

व्योम रुको_क्रम_unix_gc(व्योम)
अणु
	/* If number of inflight sockets is insane,
	 * क्रमce a garbage collect right now.
	 */
	अगर (unix_tot_inflight > UNIX_INFLIGHT_TRIGGER_GC && !gc_in_progress)
		unix_gc();
	रुको_event(unix_gc_रुको, gc_in_progress == false);
पूर्ण

/* The बाह्यal entry poपूर्णांक: unix_gc() */
व्योम unix_gc(व्योम)
अणु
	काष्ठा unix_sock *u;
	काष्ठा unix_sock *next;
	काष्ठा sk_buff_head hitlist;
	काष्ठा list_head cursor;
	LIST_HEAD(not_cycle_list);

	spin_lock(&unix_gc_lock);

	/* Aव्योम a recursive GC. */
	अगर (gc_in_progress)
		जाओ out;

	gc_in_progress = true;
	/* First, select candidates क्रम garbage collection.  Only
	 * in-flight sockets are considered, and from those only ones
	 * which करोn't have any बाह्यal reference.
	 *
	 * Holding unix_gc_lock will protect these candidates from
	 * being detached, and hence from gaining an बाह्यal
	 * reference.  Since there are no possible receivers, all
	 * buffers currently on the candidates' queues stay there
	 * during the garbage collection.
	 *
	 * We also know that no new candidate can be added onto the
	 * receive queues.  Other, non candidate sockets _can_ be
	 * added to queue, so we must make sure only to touch
	 * candidates.
	 */
	list_क्रम_each_entry_safe(u, next, &gc_inflight_list, link) अणु
		दीर्घ total_refs;
		दीर्घ inflight_refs;

		total_refs = file_count(u->sk.sk_socket->file);
		inflight_refs = atomic_दीर्घ_पढ़ो(&u->inflight);

		BUG_ON(inflight_refs < 1);
		BUG_ON(total_refs < inflight_refs);
		अगर (total_refs == inflight_refs) अणु
			list_move_tail(&u->link, &gc_candidates);
			__set_bit(UNIX_GC_CANDIDATE, &u->gc_flags);
			__set_bit(UNIX_GC_MAYBE_CYCLE, &u->gc_flags);
		पूर्ण
	पूर्ण

	/* Now हटाओ all पूर्णांकernal in-flight reference to children of
	 * the candidates.
	 */
	list_क्रम_each_entry(u, &gc_candidates, link)
		scan_children(&u->sk, dec_inflight, शून्य);

	/* Restore the references क्रम children of all candidates,
	 * which have reमुख्यing references.  Do this recursively, so
	 * only those reमुख्य, which क्रमm cyclic references.
	 *
	 * Use a "cursor" link, to make the list traversal safe, even
	 * though elements might be moved about.
	 */
	list_add(&cursor, &gc_candidates);
	जबतक (cursor.next != &gc_candidates) अणु
		u = list_entry(cursor.next, काष्ठा unix_sock, link);

		/* Move cursor to after the current position. */
		list_move(&cursor, &u->link);

		अगर (atomic_दीर्घ_पढ़ो(&u->inflight) > 0) अणु
			list_move_tail(&u->link, &not_cycle_list);
			__clear_bit(UNIX_GC_MAYBE_CYCLE, &u->gc_flags);
			scan_children(&u->sk, inc_inflight_move_tail, शून्य);
		पूर्ण
	पूर्ण
	list_del(&cursor);

	/* Now gc_candidates contains only garbage.  Restore original
	 * inflight counters क्रम these as well, and हटाओ the skbuffs
	 * which are creating the cycle(s).
	 */
	skb_queue_head_init(&hitlist);
	list_क्रम_each_entry(u, &gc_candidates, link)
		scan_children(&u->sk, inc_inflight, &hitlist);

	/* not_cycle_list contains those sockets which करो not make up a
	 * cycle.  Restore these to the inflight list.
	 */
	जबतक (!list_empty(&not_cycle_list)) अणु
		u = list_entry(not_cycle_list.next, काष्ठा unix_sock, link);
		__clear_bit(UNIX_GC_CANDIDATE, &u->gc_flags);
		list_move_tail(&u->link, &gc_inflight_list);
	पूर्ण

	spin_unlock(&unix_gc_lock);

	/* Here we are. Hitlist is filled. Die. */
	__skb_queue_purge(&hitlist);

	spin_lock(&unix_gc_lock);

	/* All candidates should have been detached by now. */
	BUG_ON(!list_empty(&gc_candidates));
	gc_in_progress = false;
	wake_up(&unix_gc_रुको);

 out:
	spin_unlock(&unix_gc_lock);
पूर्ण
