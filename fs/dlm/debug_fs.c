<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) 2005-2009 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश <linux/pagemap.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>

#समावेश "dlm_internal.h"
#समावेश "lock.h"

#घोषणा DLM_DEBUG_BUF_LEN 4096
अटल अक्षर debug_buf[DLM_DEBUG_BUF_LEN];
अटल काष्ठा mutex debug_buf_lock;

अटल काष्ठा dentry *dlm_root;

अटल अक्षर *prपूर्णांक_lockmode(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल DLM_LOCK_IV:
		वापस "--";
	हाल DLM_LOCK_NL:
		वापस "NL";
	हाल DLM_LOCK_CR:
		वापस "CR";
	हाल DLM_LOCK_CW:
		वापस "CW";
	हाल DLM_LOCK_PR:
		वापस "PR";
	हाल DLM_LOCK_PW:
		वापस "PW";
	हाल DLM_LOCK_EX:
		वापस "EX";
	शेष:
		वापस "??";
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_क्रमmat1_lock(काष्ठा seq_file *s, काष्ठा dlm_lkb *lkb,
			       काष्ठा dlm_rsb *res)
अणु
	seq_म_लिखो(s, "%08x %s", lkb->lkb_id, prपूर्णांक_lockmode(lkb->lkb_grmode));

	अगर (lkb->lkb_status == DLM_LKSTS_CONVERT ||
	    lkb->lkb_status == DLM_LKSTS_WAITING)
		seq_म_लिखो(s, " (%s)", prपूर्णांक_lockmode(lkb->lkb_rqmode));

	अगर (lkb->lkb_nodeid) अणु
		अगर (lkb->lkb_nodeid != res->res_nodeid)
			seq_म_लिखो(s, " Remote: %3d %08x", lkb->lkb_nodeid,
				   lkb->lkb_remid);
		अन्यथा
			seq_म_लिखो(s, " Master:     %08x", lkb->lkb_remid);
	पूर्ण

	अगर (lkb->lkb_रुको_type)
		seq_म_लिखो(s, " wait_type: %d", lkb->lkb_रुको_type);

	seq_अ_दो(s, '\n');
पूर्ण

अटल व्योम prपूर्णांक_क्रमmat1(काष्ठा dlm_rsb *res, काष्ठा seq_file *s)
अणु
	काष्ठा dlm_lkb *lkb;
	पूर्णांक i, lvblen = res->res_ls->ls_lvblen, recover_list, root_list;

	lock_rsb(res);

	seq_म_लिखो(s, "\nResource %p Name (len=%d) \"", res, res->res_length);

	क्रम (i = 0; i < res->res_length; i++) अणु
		अगर (है_छाप(res->res_name[i]))
			seq_म_लिखो(s, "%c", res->res_name[i]);
		अन्यथा
			seq_म_लिखो(s, "%c", '.');
	पूर्ण

	अगर (res->res_nodeid > 0)
		seq_म_लिखो(s, "\"\nLocal Copy, Master is node %d\n",
			   res->res_nodeid);
	अन्यथा अगर (res->res_nodeid == 0)
		seq_माला_दो(s, "\"\nMaster Copy\n");
	अन्यथा अगर (res->res_nodeid == -1)
		seq_म_लिखो(s, "\"\nLooking up master (lkid %x)\n",
			   res->res_first_lkid);
	अन्यथा
		seq_म_लिखो(s, "\"\nInvalid master %d\n", res->res_nodeid);
	अगर (seq_has_overflowed(s))
		जाओ out;

	/* Prपूर्णांक the LVB: */
	अगर (res->res_lvbptr) अणु
		seq_माला_दो(s, "LVB: ");
		क्रम (i = 0; i < lvblen; i++) अणु
			अगर (i == lvblen / 2)
				seq_माला_दो(s, "\n     ");
			seq_म_लिखो(s, "%02x ",
				   (अचिन्हित अक्षर) res->res_lvbptr[i]);
		पूर्ण
		अगर (rsb_flag(res, RSB_VALNOTVALID))
			seq_माला_दो(s, " (INVALID)");
		seq_अ_दो(s, '\n');
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण

	root_list = !list_empty(&res->res_root_list);
	recover_list = !list_empty(&res->res_recover_list);

	अगर (root_list || recover_list) अणु
		seq_म_लिखो(s, "Recovery: root %d recover %d flags %lx count %d\n",
			   root_list, recover_list,
			   res->res_flags, res->res_recover_locks_count);
	पूर्ण

	/* Prपूर्णांक the locks attached to this resource */
	seq_माला_दो(s, "Granted Queue\n");
	list_क्रम_each_entry(lkb, &res->res_grantqueue, lkb_statequeue) अणु
		prपूर्णांक_क्रमmat1_lock(s, lkb, res);
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण

	seq_माला_दो(s, "Conversion Queue\n");
	list_क्रम_each_entry(lkb, &res->res_convertqueue, lkb_statequeue) अणु
		prपूर्णांक_क्रमmat1_lock(s, lkb, res);
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण

	seq_माला_दो(s, "Waiting Queue\n");
	list_क्रम_each_entry(lkb, &res->res_रुकोqueue, lkb_statequeue) अणु
		prपूर्णांक_क्रमmat1_lock(s, lkb, res);
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण

	अगर (list_empty(&res->res_lookup))
		जाओ out;

	seq_माला_दो(s, "Lookup Queue\n");
	list_क्रम_each_entry(lkb, &res->res_lookup, lkb_rsb_lookup) अणु
		seq_म_लिखो(s, "%08x %s",
			   lkb->lkb_id, prपूर्णांक_lockmode(lkb->lkb_rqmode));
		अगर (lkb->lkb_रुको_type)
			seq_म_लिखो(s, " wait_type: %d", lkb->lkb_रुको_type);
		seq_अ_दो(s, '\n');
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण
 out:
	unlock_rsb(res);
पूर्ण

अटल व्योम prपूर्णांक_क्रमmat2_lock(काष्ठा seq_file *s, काष्ठा dlm_lkb *lkb,
			       काष्ठा dlm_rsb *r)
अणु
	u64 xid = 0;
	u64 us;

	अगर (lkb->lkb_flags & DLM_IFL_USER) अणु
		अगर (lkb->lkb_ua)
			xid = lkb->lkb_ua->xid;
	पूर्ण

	/* microseconds since lkb was added to current queue */
	us = kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), lkb->lkb_बारtamp));

	/* id nodeid remid pid xid exflags flags sts grmode rqmode समय_us
	   r_nodeid r_len r_name */

	seq_म_लिखो(s, "%x %d %x %u %llu %x %x %d %d %d %llu %u %d \"%s\"\n",
		   lkb->lkb_id,
		   lkb->lkb_nodeid,
		   lkb->lkb_remid,
		   lkb->lkb_ownpid,
		   (अचिन्हित दीर्घ दीर्घ)xid,
		   lkb->lkb_exflags,
		   lkb->lkb_flags,
		   lkb->lkb_status,
		   lkb->lkb_grmode,
		   lkb->lkb_rqmode,
		   (अचिन्हित दीर्घ दीर्घ)us,
		   r->res_nodeid,
		   r->res_length,
		   r->res_name);
पूर्ण

अटल व्योम prपूर्णांक_क्रमmat2(काष्ठा dlm_rsb *r, काष्ठा seq_file *s)
अणु
	काष्ठा dlm_lkb *lkb;

	lock_rsb(r);

	list_क्रम_each_entry(lkb, &r->res_grantqueue, lkb_statequeue) अणु
		prपूर्णांक_क्रमmat2_lock(s, lkb, r);
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण

	list_क्रम_each_entry(lkb, &r->res_convertqueue, lkb_statequeue) अणु
		prपूर्णांक_क्रमmat2_lock(s, lkb, r);
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण

	list_क्रम_each_entry(lkb, &r->res_रुकोqueue, lkb_statequeue) अणु
		prपूर्णांक_क्रमmat2_lock(s, lkb, r);
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण
 out:
	unlock_rsb(r);
पूर्ण

अटल व्योम prपूर्णांक_क्रमmat3_lock(काष्ठा seq_file *s, काष्ठा dlm_lkb *lkb,
			      पूर्णांक rsb_lookup)
अणु
	u64 xid = 0;

	अगर (lkb->lkb_flags & DLM_IFL_USER) अणु
		अगर (lkb->lkb_ua)
			xid = lkb->lkb_ua->xid;
	पूर्ण

	seq_म_लिखो(s, "lkb %x %d %x %u %llu %x %x %d %d %d %d %d %d %u %llu %llu\n",
		   lkb->lkb_id,
		   lkb->lkb_nodeid,
		   lkb->lkb_remid,
		   lkb->lkb_ownpid,
		   (अचिन्हित दीर्घ दीर्घ)xid,
		   lkb->lkb_exflags,
		   lkb->lkb_flags,
		   lkb->lkb_status,
		   lkb->lkb_grmode,
		   lkb->lkb_rqmode,
		   lkb->lkb_last_bast.mode,
		   rsb_lookup,
		   lkb->lkb_रुको_type,
		   lkb->lkb_lvbseq,
		   (अचिन्हित दीर्घ दीर्घ)kसमय_प्रकारo_ns(lkb->lkb_बारtamp),
		   (अचिन्हित दीर्घ दीर्घ)kसमय_प्रकारo_ns(lkb->lkb_last_bast_समय));
पूर्ण

अटल व्योम prपूर्णांक_क्रमmat3(काष्ठा dlm_rsb *r, काष्ठा seq_file *s)
अणु
	काष्ठा dlm_lkb *lkb;
	पूर्णांक i, lvblen = r->res_ls->ls_lvblen;
	पूर्णांक prपूर्णांक_name = 1;

	lock_rsb(r);

	seq_म_लिखो(s, "rsb %p %d %x %lx %d %d %u %d ",
		   r,
		   r->res_nodeid,
		   r->res_first_lkid,
		   r->res_flags,
		   !list_empty(&r->res_root_list),
		   !list_empty(&r->res_recover_list),
		   r->res_recover_locks_count,
		   r->res_length);
	अगर (seq_has_overflowed(s))
		जाओ out;

	क्रम (i = 0; i < r->res_length; i++) अणु
		अगर (!isascii(r->res_name[i]) || !है_छाप(r->res_name[i]))
			prपूर्णांक_name = 0;
	पूर्ण

	seq_माला_दो(s, prपूर्णांक_name ? "str " : "hex");

	क्रम (i = 0; i < r->res_length; i++) अणु
		अगर (prपूर्णांक_name)
			seq_म_लिखो(s, "%c", r->res_name[i]);
		अन्यथा
			seq_म_लिखो(s, " %02x", (अचिन्हित अक्षर)r->res_name[i]);
	पूर्ण
	seq_अ_दो(s, '\n');
	अगर (seq_has_overflowed(s))
		जाओ out;

	अगर (!r->res_lvbptr)
		जाओ करो_locks;

	seq_म_लिखो(s, "lvb %u %d", r->res_lvbseq, lvblen);

	क्रम (i = 0; i < lvblen; i++)
		seq_म_लिखो(s, " %02x", (अचिन्हित अक्षर)r->res_lvbptr[i]);
	seq_अ_दो(s, '\n');
	अगर (seq_has_overflowed(s))
		जाओ out;

 करो_locks:
	list_क्रम_each_entry(lkb, &r->res_grantqueue, lkb_statequeue) अणु
		prपूर्णांक_क्रमmat3_lock(s, lkb, 0);
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण

	list_क्रम_each_entry(lkb, &r->res_convertqueue, lkb_statequeue) अणु
		prपूर्णांक_क्रमmat3_lock(s, lkb, 0);
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण

	list_क्रम_each_entry(lkb, &r->res_रुकोqueue, lkb_statequeue) अणु
		prपूर्णांक_क्रमmat3_lock(s, lkb, 0);
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण

	list_क्रम_each_entry(lkb, &r->res_lookup, lkb_rsb_lookup) अणु
		prपूर्णांक_क्रमmat3_lock(s, lkb, 1);
		अगर (seq_has_overflowed(s))
			जाओ out;
	पूर्ण
 out:
	unlock_rsb(r);
पूर्ण

अटल व्योम prपूर्णांक_क्रमmat4(काष्ठा dlm_rsb *r, काष्ठा seq_file *s)
अणु
	पूर्णांक our_nodeid = dlm_our_nodeid();
	पूर्णांक prपूर्णांक_name = 1;
	पूर्णांक i;

	lock_rsb(r);

	seq_म_लिखो(s, "rsb %p %d %d %d %d %lu %lx %d ",
		   r,
		   r->res_nodeid,
		   r->res_master_nodeid,
		   r->res_dir_nodeid,
		   our_nodeid,
		   r->res_toss_समय,
		   r->res_flags,
		   r->res_length);

	क्रम (i = 0; i < r->res_length; i++) अणु
		अगर (!isascii(r->res_name[i]) || !है_छाप(r->res_name[i]))
			prपूर्णांक_name = 0;
	पूर्ण

	seq_माला_दो(s, prपूर्णांक_name ? "str " : "hex");

	क्रम (i = 0; i < r->res_length; i++) अणु
		अगर (prपूर्णांक_name)
			seq_म_लिखो(s, "%c", r->res_name[i]);
		अन्यथा
			seq_म_लिखो(s, " %02x", (अचिन्हित अक्षर)r->res_name[i]);
	पूर्ण
	seq_अ_दो(s, '\n');
	unlock_rsb(r);
पूर्ण

काष्ठा rsbtbl_iter अणु
	काष्ठा dlm_rsb *rsb;
	अचिन्हित bucket;
	पूर्णांक क्रमmat;
	पूर्णांक header;
पूर्ण;

/*
 * If the buffer is full, seq_म_लिखो can be called again, but it
 * करोes nothing.  So, the these prपूर्णांकing routines periodically check
 * seq_has_overflowed to aव्योम wasting too much समय trying to prपूर्णांक to
 * a full buffer.
 */

अटल पूर्णांक table_seq_show(काष्ठा seq_file *seq, व्योम *iter_ptr)
अणु
	काष्ठा rsbtbl_iter *ri = iter_ptr;

	चयन (ri->क्रमmat) अणु
	हाल 1:
		prपूर्णांक_क्रमmat1(ri->rsb, seq);
		अवरोध;
	हाल 2:
		अगर (ri->header) अणु
			seq_माला_दो(seq, "id nodeid remid pid xid exflags flags sts grmode rqmode time_ms r_nodeid r_len r_name\n");
			ri->header = 0;
		पूर्ण
		prपूर्णांक_क्रमmat2(ri->rsb, seq);
		अवरोध;
	हाल 3:
		अगर (ri->header) अणु
			seq_माला_दो(seq, "version rsb 1.1 lvb 1.1 lkb 1.1\n");
			ri->header = 0;
		पूर्ण
		prपूर्णांक_क्रमmat3(ri->rsb, seq);
		अवरोध;
	हाल 4:
		अगर (ri->header) अणु
			seq_माला_दो(seq, "version 4 rsb 2\n");
			ri->header = 0;
		पूर्ण
		prपूर्णांक_क्रमmat4(ri->rsb, seq);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations क्रमmat1_seq_ops;
अटल स्थिर काष्ठा seq_operations क्रमmat2_seq_ops;
अटल स्थिर काष्ठा seq_operations क्रमmat3_seq_ops;
अटल स्थिर काष्ठा seq_operations क्रमmat4_seq_ops;

अटल व्योम *table_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा rb_root *tree;
	काष्ठा rb_node *node;
	काष्ठा dlm_ls *ls = seq->निजी;
	काष्ठा rsbtbl_iter *ri;
	काष्ठा dlm_rsb *r;
	loff_t n = *pos;
	अचिन्हित bucket, entry;
	पूर्णांक toss = (seq->op == &क्रमmat4_seq_ops);

	bucket = n >> 32;
	entry = n & ((1LL << 32) - 1);

	अगर (bucket >= ls->ls_rsbtbl_size)
		वापस शून्य;

	ri = kzalloc(माप(*ri), GFP_NOFS);
	अगर (!ri)
		वापस शून्य;
	अगर (n == 0)
		ri->header = 1;
	अगर (seq->op == &क्रमmat1_seq_ops)
		ri->क्रमmat = 1;
	अगर (seq->op == &क्रमmat2_seq_ops)
		ri->क्रमmat = 2;
	अगर (seq->op == &क्रमmat3_seq_ops)
		ri->क्रमmat = 3;
	अगर (seq->op == &क्रमmat4_seq_ops)
		ri->क्रमmat = 4;

	tree = toss ? &ls->ls_rsbtbl[bucket].toss : &ls->ls_rsbtbl[bucket].keep;

	spin_lock(&ls->ls_rsbtbl[bucket].lock);
	अगर (!RB_EMPTY_ROOT(tree)) अणु
		क्रम (node = rb_first(tree); node; node = rb_next(node)) अणु
			r = rb_entry(node, काष्ठा dlm_rsb, res_hashnode);
			अगर (!entry--) अणु
				dlm_hold_rsb(r);
				ri->rsb = r;
				ri->bucket = bucket;
				spin_unlock(&ls->ls_rsbtbl[bucket].lock);
				वापस ri;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&ls->ls_rsbtbl[bucket].lock);

	/*
	 * move to the first rsb in the next non-empty bucket
	 */

	/* zero the entry */
	n &= ~((1LL << 32) - 1);

	जबतक (1) अणु
		bucket++;
		n += 1LL << 32;

		अगर (bucket >= ls->ls_rsbtbl_size) अणु
			kमुक्त(ri);
			वापस शून्य;
		पूर्ण
		tree = toss ? &ls->ls_rsbtbl[bucket].toss : &ls->ls_rsbtbl[bucket].keep;

		spin_lock(&ls->ls_rsbtbl[bucket].lock);
		अगर (!RB_EMPTY_ROOT(tree)) अणु
			node = rb_first(tree);
			r = rb_entry(node, काष्ठा dlm_rsb, res_hashnode);
			dlm_hold_rsb(r);
			ri->rsb = r;
			ri->bucket = bucket;
			spin_unlock(&ls->ls_rsbtbl[bucket].lock);
			*pos = n;
			वापस ri;
		पूर्ण
		spin_unlock(&ls->ls_rsbtbl[bucket].lock);
	पूर्ण
पूर्ण

अटल व्योम *table_seq_next(काष्ठा seq_file *seq, व्योम *iter_ptr, loff_t *pos)
अणु
	काष्ठा dlm_ls *ls = seq->निजी;
	काष्ठा rsbtbl_iter *ri = iter_ptr;
	काष्ठा rb_root *tree;
	काष्ठा rb_node *next;
	काष्ठा dlm_rsb *r, *rp;
	loff_t n = *pos;
	अचिन्हित bucket;
	पूर्णांक toss = (seq->op == &क्रमmat4_seq_ops);

	bucket = n >> 32;

	/*
	 * move to the next rsb in the same bucket
	 */

	spin_lock(&ls->ls_rsbtbl[bucket].lock);
	rp = ri->rsb;
	next = rb_next(&rp->res_hashnode);

	अगर (next) अणु
		r = rb_entry(next, काष्ठा dlm_rsb, res_hashnode);
		dlm_hold_rsb(r);
		ri->rsb = r;
		spin_unlock(&ls->ls_rsbtbl[bucket].lock);
		dlm_put_rsb(rp);
		++*pos;
		वापस ri;
	पूर्ण
	spin_unlock(&ls->ls_rsbtbl[bucket].lock);
	dlm_put_rsb(rp);

	/*
	 * move to the first rsb in the next non-empty bucket
	 */

	/* zero the entry */
	n &= ~((1LL << 32) - 1);

	जबतक (1) अणु
		bucket++;
		n += 1LL << 32;

		अगर (bucket >= ls->ls_rsbtbl_size) अणु
			kमुक्त(ri);
			++*pos;
			वापस शून्य;
		पूर्ण
		tree = toss ? &ls->ls_rsbtbl[bucket].toss : &ls->ls_rsbtbl[bucket].keep;

		spin_lock(&ls->ls_rsbtbl[bucket].lock);
		अगर (!RB_EMPTY_ROOT(tree)) अणु
			next = rb_first(tree);
			r = rb_entry(next, काष्ठा dlm_rsb, res_hashnode);
			dlm_hold_rsb(r);
			ri->rsb = r;
			ri->bucket = bucket;
			spin_unlock(&ls->ls_rsbtbl[bucket].lock);
			*pos = n;
			वापस ri;
		पूर्ण
		spin_unlock(&ls->ls_rsbtbl[bucket].lock);
	पूर्ण
पूर्ण

अटल व्योम table_seq_stop(काष्ठा seq_file *seq, व्योम *iter_ptr)
अणु
	काष्ठा rsbtbl_iter *ri = iter_ptr;

	अगर (ri) अणु
		dlm_put_rsb(ri->rsb);
		kमुक्त(ri);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा seq_operations क्रमmat1_seq_ops = अणु
	.start = table_seq_start,
	.next  = table_seq_next,
	.stop  = table_seq_stop,
	.show  = table_seq_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations क्रमmat2_seq_ops = अणु
	.start = table_seq_start,
	.next  = table_seq_next,
	.stop  = table_seq_stop,
	.show  = table_seq_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations क्रमmat3_seq_ops = अणु
	.start = table_seq_start,
	.next  = table_seq_next,
	.stop  = table_seq_stop,
	.show  = table_seq_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations क्रमmat4_seq_ops = अणु
	.start = table_seq_start,
	.next  = table_seq_next,
	.stop  = table_seq_stop,
	.show  = table_seq_show,
पूर्ण;

अटल स्थिर काष्ठा file_operations क्रमmat1_fops;
अटल स्थिर काष्ठा file_operations क्रमmat2_fops;
अटल स्थिर काष्ठा file_operations क्रमmat3_fops;
अटल स्थिर काष्ठा file_operations क्रमmat4_fops;

अटल पूर्णांक table_खोलो1(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq;
	पूर्णांक ret;

	ret = seq_खोलो(file, &क्रमmat1_seq_ops);
	अगर (ret)
		वापस ret;

	seq = file->निजी_data;
	seq->निजी = inode->i_निजी; /* the dlm_ls */
	वापस 0;
पूर्ण

अटल पूर्णांक table_खोलो2(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq;
	पूर्णांक ret;

	ret = seq_खोलो(file, &क्रमmat2_seq_ops);
	अगर (ret)
		वापस ret;

	seq = file->निजी_data;
	seq->निजी = inode->i_निजी; /* the dlm_ls */
	वापस 0;
पूर्ण

अटल पूर्णांक table_खोलो3(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq;
	पूर्णांक ret;

	ret = seq_खोलो(file, &क्रमmat3_seq_ops);
	अगर (ret)
		वापस ret;

	seq = file->निजी_data;
	seq->निजी = inode->i_निजी; /* the dlm_ls */
	वापस 0;
पूर्ण

अटल पूर्णांक table_खोलो4(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq;
	पूर्णांक ret;

	ret = seq_खोलो(file, &क्रमmat4_seq_ops);
	अगर (ret)
		वापस ret;

	seq = file->निजी_data;
	seq->निजी = inode->i_निजी; /* the dlm_ls */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations क्रमmat1_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = table_खोलो1,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release
पूर्ण;

अटल स्थिर काष्ठा file_operations क्रमmat2_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = table_खोलो2,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release
पूर्ण;

अटल स्थिर काष्ठा file_operations क्रमmat3_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = table_खोलो3,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release
पूर्ण;

अटल स्थिर काष्ठा file_operations क्रमmat4_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = table_खोलो4,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release
पूर्ण;

/*
 * dump lkb's on the ls_रुकोers list
 */
अटल sमाप_प्रकार रुकोers_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dlm_ls *ls = file->निजी_data;
	काष्ठा dlm_lkb *lkb;
	माप_प्रकार len = DLM_DEBUG_BUF_LEN, pos = 0, ret, rv;

	mutex_lock(&debug_buf_lock);
	mutex_lock(&ls->ls_रुकोers_mutex);
	स_रखो(debug_buf, 0, माप(debug_buf));

	list_क्रम_each_entry(lkb, &ls->ls_रुकोers, lkb_रुको_reply) अणु
		ret = snम_लिखो(debug_buf + pos, len - pos, "%x %d %d %s\n",
			       lkb->lkb_id, lkb->lkb_रुको_type,
			       lkb->lkb_nodeid, lkb->lkb_resource->res_name);
		अगर (ret >= len - pos)
			अवरोध;
		pos += ret;
	पूर्ण
	mutex_unlock(&ls->ls_रुकोers_mutex);

	rv = simple_पढ़ो_from_buffer(userbuf, count, ppos, debug_buf, pos);
	mutex_unlock(&debug_buf_lock);
	वापस rv;
पूर्ण

अटल स्थिर काष्ठा file_operations रुकोers_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = simple_खोलो,
	.पढ़ो    = रुकोers_पढ़ो,
	.llseek  = शेष_llseek,
पूर्ण;

व्योम dlm_delete_debug_file(काष्ठा dlm_ls *ls)
अणु
	debugfs_हटाओ(ls->ls_debug_rsb_dentry);
	debugfs_हटाओ(ls->ls_debug_रुकोers_dentry);
	debugfs_हटाओ(ls->ls_debug_locks_dentry);
	debugfs_हटाओ(ls->ls_debug_all_dentry);
	debugfs_हटाओ(ls->ls_debug_toss_dentry);
पूर्ण

व्योम dlm_create_debug_file(काष्ठा dlm_ls *ls)
अणु
	अक्षर name[DLM_LOCKSPACE_LEN + 8];

	/* क्रमmat 1 */

	ls->ls_debug_rsb_dentry = debugfs_create_file(ls->ls_name,
						      S_IFREG | S_IRUGO,
						      dlm_root,
						      ls,
						      &क्रमmat1_fops);

	/* क्रमmat 2 */

	स_रखो(name, 0, माप(name));
	snम_लिखो(name, DLM_LOCKSPACE_LEN + 8, "%s_locks", ls->ls_name);

	ls->ls_debug_locks_dentry = debugfs_create_file(name,
							S_IFREG | S_IRUGO,
							dlm_root,
							ls,
							&क्रमmat2_fops);

	/* क्रमmat 3 */

	स_रखो(name, 0, माप(name));
	snम_लिखो(name, DLM_LOCKSPACE_LEN + 8, "%s_all", ls->ls_name);

	ls->ls_debug_all_dentry = debugfs_create_file(name,
						      S_IFREG | S_IRUGO,
						      dlm_root,
						      ls,
						      &क्रमmat3_fops);

	/* क्रमmat 4 */

	स_रखो(name, 0, माप(name));
	snम_लिखो(name, DLM_LOCKSPACE_LEN + 8, "%s_toss", ls->ls_name);

	ls->ls_debug_toss_dentry = debugfs_create_file(name,
						       S_IFREG | S_IRUGO,
						       dlm_root,
						       ls,
						       &क्रमmat4_fops);

	स_रखो(name, 0, माप(name));
	snम_लिखो(name, DLM_LOCKSPACE_LEN + 8, "%s_waiters", ls->ls_name);

	ls->ls_debug_रुकोers_dentry = debugfs_create_file(name,
							  S_IFREG | S_IRUGO,
							  dlm_root,
							  ls,
							  &रुकोers_fops);
पूर्ण

व्योम __init dlm_रेजिस्टर_debugfs(व्योम)
अणु
	mutex_init(&debug_buf_lock);
	dlm_root = debugfs_create_dir("dlm", शून्य);
पूर्ण

व्योम dlm_unरेजिस्टर_debugfs(व्योम)
अणु
	debugfs_हटाओ(dlm_root);
पूर्ण

