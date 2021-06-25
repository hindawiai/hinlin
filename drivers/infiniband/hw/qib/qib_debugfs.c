<शैली गुरु>
/*
 * Copyright (c) 2013 - 2017 Intel Corporation.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>

#समावेश "qib.h"
#समावेश "qib_verbs.h"
#समावेश "qib_debugfs.h"

अटल काष्ठा dentry *qib_dbg_root;

#घोषणा DEBUGFS_खाता(name) \
अटल स्थिर काष्ठा seq_operations _##name##_seq_ops = अणु \
	.start = _##name##_seq_start, \
	.next  = _##name##_seq_next, \
	.stop  = _##name##_seq_stop, \
	.show  = _##name##_seq_show \
पूर्ण; \
अटल पूर्णांक _##name##_खोलो(काष्ठा inode *inode, काष्ठा file *s) \
अणु \
	काष्ठा seq_file *seq; \
	पूर्णांक ret; \
	ret =  seq_खोलो(s, &_##name##_seq_ops); \
	अगर (ret) \
		वापस ret; \
	seq = s->निजी_data; \
	seq->निजी = inode->i_निजी; \
	वापस 0; \
पूर्ण \
अटल स्थिर काष्ठा file_operations _##name##_file_ops = अणु \
	.owner   = THIS_MODULE, \
	.खोलो    = _##name##_खोलो, \
	.पढ़ो    = seq_पढ़ो, \
	.llseek  = seq_lseek, \
	.release = seq_release \
पूर्ण;

अटल व्योम *_opcode_stats_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा qib_opcode_stats_perctx *opstats;

	अगर (*pos >= ARRAY_SIZE(opstats->stats))
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम *_opcode_stats_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा qib_opcode_stats_perctx *opstats;

	++*pos;
	अगर (*pos >= ARRAY_SIZE(opstats->stats))
		वापस शून्य;
	वापस pos;
पूर्ण


अटल व्योम _opcode_stats_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	/* nothing allocated */
पूर्ण

अटल पूर्णांक _opcode_stats_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	loff_t *spos = v;
	loff_t i = *spos, j;
	u64 n_packets = 0, n_bytes = 0;
	काष्ठा qib_ibdev *ibd = (काष्ठा qib_ibdev *)s->निजी;
	काष्ठा qib_devdata *dd = dd_from_dev(ibd);

	क्रम (j = 0; j < dd->first_user_ctxt; j++) अणु
		अगर (!dd->rcd[j])
			जारी;
		n_packets += dd->rcd[j]->opstats->stats[i].n_packets;
		n_bytes += dd->rcd[j]->opstats->stats[i].n_bytes;
	पूर्ण
	अगर (!n_packets && !n_bytes)
		वापस SEQ_SKIP;
	seq_म_लिखो(s, "%02llx %llu/%llu\n", i,
		(अचिन्हित दीर्घ दीर्घ) n_packets,
		(अचिन्हित दीर्घ दीर्घ) n_bytes);

	वापस 0;
पूर्ण

DEBUGFS_खाता(opcode_stats)

अटल व्योम *_ctx_stats_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा qib_ibdev *ibd = (काष्ठा qib_ibdev *)s->निजी;
	काष्ठा qib_devdata *dd = dd_from_dev(ibd);

	अगर (!*pos)
		वापस SEQ_START_TOKEN;
	अगर (*pos >= dd->first_user_ctxt)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम *_ctx_stats_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा qib_ibdev *ibd = (काष्ठा qib_ibdev *)s->निजी;
	काष्ठा qib_devdata *dd = dd_from_dev(ibd);

	अगर (v == SEQ_START_TOKEN)
		वापस pos;

	++*pos;
	अगर (*pos >= dd->first_user_ctxt)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम _ctx_stats_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	/* nothing allocated */
पूर्ण

अटल पूर्णांक _ctx_stats_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	loff_t *spos;
	loff_t i, j;
	u64 n_packets = 0;
	काष्ठा qib_ibdev *ibd = (काष्ठा qib_ibdev *)s->निजी;
	काष्ठा qib_devdata *dd = dd_from_dev(ibd);

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(s, "Ctx:npkts\n");
		वापस 0;
	पूर्ण

	spos = v;
	i = *spos;

	अगर (!dd->rcd[i])
		वापस SEQ_SKIP;

	क्रम (j = 0; j < ARRAY_SIZE(dd->rcd[i]->opstats->stats); j++)
		n_packets += dd->rcd[i]->opstats->stats[j].n_packets;

	अगर (!n_packets)
		वापस SEQ_SKIP;

	seq_म_लिखो(s, "  %llu:%llu\n", i, n_packets);
	वापस 0;
पूर्ण

DEBUGFS_खाता(ctx_stats)

अटल व्योम *_qp_stats_seq_start(काष्ठा seq_file *s, loff_t *pos)
	__acquires(RCU)
अणु
	काष्ठा rvt_qp_iter *iter;
	loff_t n = *pos;

	iter = rvt_qp_iter_init(s->निजी, 0, शून्य);

	/* stop calls rcu_पढ़ो_unlock */
	rcu_पढ़ो_lock();

	अगर (!iter)
		वापस शून्य;

	करो अणु
		अगर (rvt_qp_iter_next(iter)) अणु
			kमुक्त(iter);
			वापस शून्य;
		पूर्ण
	पूर्ण जबतक (n--);

	वापस iter;
पूर्ण

अटल व्योम *_qp_stats_seq_next(काष्ठा seq_file *s, व्योम *iter_ptr,
				   loff_t *pos)
	__must_hold(RCU)
अणु
	काष्ठा rvt_qp_iter *iter = iter_ptr;

	(*pos)++;

	अगर (rvt_qp_iter_next(iter)) अणु
		kमुक्त(iter);
		वापस शून्य;
	पूर्ण

	वापस iter;
पूर्ण

अटल व्योम _qp_stats_seq_stop(काष्ठा seq_file *s, व्योम *iter_ptr)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक _qp_stats_seq_show(काष्ठा seq_file *s, व्योम *iter_ptr)
अणु
	काष्ठा rvt_qp_iter *iter = iter_ptr;

	अगर (!iter)
		वापस 0;

	qib_qp_iter_prपूर्णांक(s, iter);

	वापस 0;
पूर्ण

DEBUGFS_खाता(qp_stats)

व्योम qib_dbg_ibdev_init(काष्ठा qib_ibdev *ibd)
अणु
	काष्ठा dentry *root;
	अक्षर name[10];

	snम_लिखो(name, माप(name), "qib%d", dd_from_dev(ibd)->unit);
	root = debugfs_create_dir(name, qib_dbg_root);
	ibd->qib_ibdev_dbg = root;

	debugfs_create_file("opcode_stats", 0400, root, ibd,
			    &_opcode_stats_file_ops);
	debugfs_create_file("ctx_stats", 0400, root, ibd, &_ctx_stats_file_ops);
	debugfs_create_file("qp_stats", 0400, root, ibd, &_qp_stats_file_ops);
पूर्ण

व्योम qib_dbg_ibdev_निकास(काष्ठा qib_ibdev *ibd)
अणु
	अगर (!qib_dbg_root)
		जाओ out;
	debugfs_हटाओ_recursive(ibd->qib_ibdev_dbg);
out:
	ibd->qib_ibdev_dbg = शून्य;
पूर्ण

व्योम qib_dbg_init(व्योम)
अणु
	qib_dbg_root = debugfs_create_dir(QIB_DRV_NAME, शून्य);
पूर्ण

व्योम qib_dbg_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(qib_dbg_root);
	qib_dbg_root = शून्य;
पूर्ण
