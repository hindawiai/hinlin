<शैली गुरु>
/*
 * Copyright (c) 2002, 2007 Red Hat, Inc. All rights reserved.
 *
 * This software may be मुक्तly redistributed under the terms of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Authors: David Woodhouse <dwmw2@infradead.org>
 *          David Howells <dhowells@redhat.com>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/sched.h>
#समावेश "internal.h"

/*
 * Allow the fileserver to request callback state (re-)initialisation.
 * Unक्रमtunately, UUIDs are not guaranteed unique.
 */
व्योम afs_init_callback_state(काष्ठा afs_server *server)
अणु
	rcu_पढ़ो_lock();
	करो अणु
		server->cb_s_अवरोध++;
		server = rcu_dereference(server->uuid_next);
	पूर्ण जबतक (0);
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * actually अवरोध a callback
 */
व्योम __afs_अवरोध_callback(काष्ठा afs_vnode *vnode, क्रमागत afs_cb_अवरोध_reason reason)
अणु
	_enter("");

	clear_bit(AFS_VNODE_NEW_CONTENT, &vnode->flags);
	अगर (test_and_clear_bit(AFS_VNODE_CB_PROMISED, &vnode->flags)) अणु
		vnode->cb_अवरोध++;
		afs_clear_permits(vnode);

		अगर (vnode->lock_state == AFS_VNODE_LOCK_WAITING_FOR_CB)
			afs_lock_may_be_available(vnode);

		trace_afs_cb_अवरोध(&vnode->fid, vnode->cb_अवरोध, reason, true);
	पूर्ण अन्यथा अणु
		trace_afs_cb_अवरोध(&vnode->fid, vnode->cb_अवरोध, reason, false);
	पूर्ण
पूर्ण

व्योम afs_अवरोध_callback(काष्ठा afs_vnode *vnode, क्रमागत afs_cb_अवरोध_reason reason)
अणु
	ग_लिखो_seqlock(&vnode->cb_lock);
	__afs_अवरोध_callback(vnode, reason);
	ग_लिखो_sequnlock(&vnode->cb_lock);
पूर्ण

/*
 * Look up a volume by volume ID under RCU conditions.
 */
अटल काष्ठा afs_volume *afs_lookup_volume_rcu(काष्ठा afs_cell *cell,
						afs_volid_t vid)
अणु
	काष्ठा afs_volume *volume = शून्य;
	काष्ठा rb_node *p;
	पूर्णांक seq = 0;

	करो अणु
		/* Unक्रमtunately, rbtree walking करोesn't give reliable results
		 * under just the RCU पढ़ो lock, so we have to check क्रम
		 * changes.
		 */
		पढ़ो_seqbegin_or_lock(&cell->volume_lock, &seq);

		p = rcu_dereference_raw(cell->volumes.rb_node);
		जबतक (p) अणु
			volume = rb_entry(p, काष्ठा afs_volume, cell_node);

			अगर (volume->vid < vid)
				p = rcu_dereference_raw(p->rb_left);
			अन्यथा अगर (volume->vid > vid)
				p = rcu_dereference_raw(p->rb_right);
			अन्यथा
				अवरोध;
			volume = शून्य;
		पूर्ण

	पूर्ण जबतक (need_seqretry(&cell->volume_lock, seq));

	करोne_seqretry(&cell->volume_lock, seq);
	वापस volume;
पूर्ण

/*
 * allow the fileserver to explicitly अवरोध one callback
 * - happens when
 *   - the backing file is changed
 *   - a lock is released
 */
अटल व्योम afs_अवरोध_one_callback(काष्ठा afs_volume *volume,
				   काष्ठा afs_fid *fid)
अणु
	काष्ठा super_block *sb;
	काष्ठा afs_vnode *vnode;
	काष्ठा inode *inode;

	अगर (fid->vnode == 0 && fid->unique == 0) अणु
		/* The callback अवरोध applies to an entire volume. */
		ग_लिखो_lock(&volume->cb_v_अवरोध_lock);
		volume->cb_v_अवरोध++;
		trace_afs_cb_अवरोध(fid, volume->cb_v_अवरोध,
				   afs_cb_अवरोध_क्रम_volume_callback, false);
		ग_लिखो_unlock(&volume->cb_v_अवरोध_lock);
		वापस;
	पूर्ण

	/* See अगर we can find a matching inode - even an I_NEW inode needs to
	 * be marked as it can have its callback broken beक्रमe we finish
	 * setting up the local inode.
	 */
	sb = rcu_dereference(volume->sb);
	अगर (!sb)
		वापस;

	inode = find_inode_rcu(sb, fid->vnode, afs_ilookup5_test_by_fid, fid);
	अगर (inode) अणु
		vnode = AFS_FS_I(inode);
		afs_अवरोध_callback(vnode, afs_cb_अवरोध_क्रम_callback);
	पूर्ण अन्यथा अणु
		trace_afs_cb_miss(fid, afs_cb_अवरोध_क्रम_callback);
	पूर्ण
पूर्ण

अटल व्योम afs_अवरोध_some_callbacks(काष्ठा afs_server *server,
				     काष्ठा afs_callback_अवरोध *cbb,
				     माप_प्रकार *_count)
अणु
	काष्ठा afs_callback_अवरोध *residue = cbb;
	काष्ठा afs_volume *volume;
	afs_volid_t vid = cbb->fid.vid;
	माप_प्रकार i;

	volume = afs_lookup_volume_rcu(server->cell, vid);

	/* TODO: Find all matching volumes अगर we couldn't match the server and
	 * अवरोध them anyway.
	 */

	क्रम (i = *_count; i > 0; cbb++, i--) अणु
		अगर (cbb->fid.vid == vid) अणु
			_debug("- Fid { vl=%08llx n=%llu u=%u }",
			       cbb->fid.vid,
			       cbb->fid.vnode,
			       cbb->fid.unique);
			--*_count;
			अगर (volume)
				afs_अवरोध_one_callback(volume, &cbb->fid);
		पूर्ण अन्यथा अणु
			*residue++ = *cbb;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * allow the fileserver to अवरोध callback promises
 */
व्योम afs_अवरोध_callbacks(काष्ठा afs_server *server, माप_प्रकार count,
			 काष्ठा afs_callback_अवरोध *callbacks)
अणु
	_enter("%p,%zu,", server, count);

	ASSERT(server != शून्य);

	rcu_पढ़ो_lock();

	जबतक (count > 0)
		afs_अवरोध_some_callbacks(server, callbacks, &count);

	rcu_पढ़ो_unlock();
	वापस;
पूर्ण
