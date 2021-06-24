<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Infraकाष्ठाure क्रम statistic tracing (histogram output).
 *
 * Copyright (C) 2008-2009 Frederic Weisbecker <fweisbec@gmail.com>
 *
 * Based on the code from trace_branch.c which is
 * Copyright (C) 2008 Steven Rostedt <srostedt@redhat.com>
 *
 */

#समावेश <linux/security.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/tracefs.h>
#समावेश "trace_stat.h"
#समावेश "trace.h"


/*
 * List of stat red-black nodes from a tracer
 * We use a such tree to sort quickly the stat
 * entries from the tracer.
 */
काष्ठा stat_node अणु
	काष्ठा rb_node		node;
	व्योम			*stat;
पूर्ण;

/* A stat session is the stats output in one file */
काष्ठा stat_session अणु
	काष्ठा list_head	session_list;
	काष्ठा tracer_stat	*ts;
	काष्ठा rb_root		stat_root;
	काष्ठा mutex		stat_mutex;
	काष्ठा dentry		*file;
पूर्ण;

/* All of the sessions currently in use. Each stat file embed one session */
अटल LIST_HEAD(all_stat_sessions);
अटल DEFINE_MUTEX(all_stat_sessions_mutex);

/* The root directory क्रम all stat files */
अटल काष्ठा dentry		*stat_dir;

अटल व्योम __reset_stat_session(काष्ठा stat_session *session)
अणु
	काष्ठा stat_node *snode, *n;

	rbtree_postorder_क्रम_each_entry_safe(snode, n, &session->stat_root, node) अणु
		अगर (session->ts->stat_release)
			session->ts->stat_release(snode->stat);
		kमुक्त(snode);
	पूर्ण

	session->stat_root = RB_ROOT;
पूर्ण

अटल व्योम reset_stat_session(काष्ठा stat_session *session)
अणु
	mutex_lock(&session->stat_mutex);
	__reset_stat_session(session);
	mutex_unlock(&session->stat_mutex);
पूर्ण

अटल व्योम destroy_session(काष्ठा stat_session *session)
अणु
	tracefs_हटाओ(session->file);
	__reset_stat_session(session);
	mutex_destroy(&session->stat_mutex);
	kमुक्त(session);
पूर्ण

अटल पूर्णांक insert_stat(काष्ठा rb_root *root, व्योम *stat, cmp_func_t cmp)
अणु
	काष्ठा rb_node **new = &(root->rb_node), *parent = शून्य;
	काष्ठा stat_node *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	data->stat = stat;

	/*
	 * Figure out where to put new node
	 * This is a descendent sorting
	 */
	जबतक (*new) अणु
		काष्ठा stat_node *this;
		पूर्णांक result;

		this = container_of(*new, काष्ठा stat_node, node);
		result = cmp(data->stat, this->stat);

		parent = *new;
		अगर (result >= 0)
			new = &((*new)->rb_left);
		अन्यथा
			new = &((*new)->rb_right);
	पूर्ण

	rb_link_node(&data->node, parent, new);
	rb_insert_color(&data->node, root);
	वापस 0;
पूर्ण

/*
 * For tracers that करोn't provide a stat_cmp callback.
 * This one will क्रमce an insertion as right-most node
 * in the rbtree.
 */
अटल पूर्णांक dummy_cmp(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	वापस -1;
पूर्ण

/*
 * Initialize the stat rbtree at each trace_stat file खोलोing.
 * All of these copies and sorting are required on all खोलोing
 * since the stats could have changed between two file sessions.
 */
अटल पूर्णांक stat_seq_init(काष्ठा stat_session *session)
अणु
	काष्ठा tracer_stat *ts = session->ts;
	काष्ठा rb_root *root = &session->stat_root;
	व्योम *stat;
	पूर्णांक ret = 0;
	पूर्णांक i;

	mutex_lock(&session->stat_mutex);
	__reset_stat_session(session);

	अगर (!ts->stat_cmp)
		ts->stat_cmp = dummy_cmp;

	stat = ts->stat_start(ts);
	अगर (!stat)
		जाओ निकास;

	ret = insert_stat(root, stat, ts->stat_cmp);
	अगर (ret)
		जाओ निकास;

	/*
	 * Iterate over the tracer stat entries and store them in an rbtree.
	 */
	क्रम (i = 1; ; i++) अणु
		stat = ts->stat_next(stat, i);

		/* End of insertion */
		अगर (!stat)
			अवरोध;

		ret = insert_stat(root, stat, ts->stat_cmp);
		अगर (ret)
			जाओ निकास_मुक्त_rbtree;
	पूर्ण

निकास:
	mutex_unlock(&session->stat_mutex);
	वापस ret;

निकास_मुक्त_rbtree:
	__reset_stat_session(session);
	mutex_unlock(&session->stat_mutex);
	वापस ret;
पूर्ण


अटल व्योम *stat_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा stat_session *session = s->निजी;
	काष्ठा rb_node *node;
	पूर्णांक n = *pos;
	पूर्णांक i;

	/* Prevent from tracer चयन or rbtree modअगरication */
	mutex_lock(&session->stat_mutex);

	/* If we are in the beginning of the file, prपूर्णांक the headers */
	अगर (session->ts->stat_headers) अणु
		अगर (n == 0)
			वापस SEQ_START_TOKEN;
		n--;
	पूर्ण

	node = rb_first(&session->stat_root);
	क्रम (i = 0; node && i < n; i++)
		node = rb_next(node);

	वापस node;
पूर्ण

अटल व्योम *stat_seq_next(काष्ठा seq_file *s, व्योम *p, loff_t *pos)
अणु
	काष्ठा stat_session *session = s->निजी;
	काष्ठा rb_node *node = p;

	(*pos)++;

	अगर (p == SEQ_START_TOKEN)
		वापस rb_first(&session->stat_root);

	वापस rb_next(node);
पूर्ण

अटल व्योम stat_seq_stop(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा stat_session *session = s->निजी;
	mutex_unlock(&session->stat_mutex);
पूर्ण

अटल पूर्णांक stat_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा stat_session *session = s->निजी;
	काष्ठा stat_node *l = container_of(v, काष्ठा stat_node, node);

	अगर (v == SEQ_START_TOKEN)
		वापस session->ts->stat_headers(s);

	वापस session->ts->stat_show(s, l->stat);
पूर्ण

अटल स्थिर काष्ठा seq_operations trace_stat_seq_ops = अणु
	.start		= stat_seq_start,
	.next		= stat_seq_next,
	.stop		= stat_seq_stop,
	.show		= stat_seq_show
पूर्ण;

/* The session stat is refilled and resorted at each stat file खोलोing */
अटल पूर्णांक tracing_stat_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;
	काष्ठा seq_file *m;
	काष्ठा stat_session *session = inode->i_निजी;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	ret = stat_seq_init(session);
	अगर (ret)
		वापस ret;

	ret = seq_खोलो(file, &trace_stat_seq_ops);
	अगर (ret) अणु
		reset_stat_session(session);
		वापस ret;
	पूर्ण

	m = file->निजी_data;
	m->निजी = session;
	वापस ret;
पूर्ण

/*
 * Aव्योम consuming memory with our now useless rbtree.
 */
अटल पूर्णांक tracing_stat_release(काष्ठा inode *i, काष्ठा file *f)
अणु
	काष्ठा stat_session *session = i->i_निजी;

	reset_stat_session(session);

	वापस seq_release(i, f);
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_stat_fops = अणु
	.खोलो		= tracing_stat_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= tracing_stat_release
पूर्ण;

अटल पूर्णांक tracing_stat_init(व्योम)
अणु
	पूर्णांक ret;

	ret = tracing_init_dentry();
	अगर (ret)
		वापस -ENODEV;

	stat_dir = tracefs_create_dir("trace_stat", शून्य);
	अगर (!stat_dir) अणु
		pr_warn("Could not create tracefs 'trace_stat' entry\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक init_stat_file(काष्ठा stat_session *session)
अणु
	पूर्णांक ret;

	अगर (!stat_dir && (ret = tracing_stat_init()))
		वापस ret;

	session->file = tracefs_create_file(session->ts->name, 0644,
					    stat_dir,
					    session, &tracing_stat_fops);
	अगर (!session->file)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

पूर्णांक रेजिस्टर_stat_tracer(काष्ठा tracer_stat *trace)
अणु
	काष्ठा stat_session *session, *node;
	पूर्णांक ret = -EINVAL;

	अगर (!trace)
		वापस -EINVAL;

	अगर (!trace->stat_start || !trace->stat_next || !trace->stat_show)
		वापस -EINVAL;

	/* Alपढ़ोy रेजिस्टरed? */
	mutex_lock(&all_stat_sessions_mutex);
	list_क्रम_each_entry(node, &all_stat_sessions, session_list) अणु
		अगर (node->ts == trace)
			जाओ out;
	पूर्ण

	ret = -ENOMEM;
	/* Init the session */
	session = kzalloc(माप(*session), GFP_KERNEL);
	अगर (!session)
		जाओ out;

	session->ts = trace;
	INIT_LIST_HEAD(&session->session_list);
	mutex_init(&session->stat_mutex);

	ret = init_stat_file(session);
	अगर (ret) अणु
		destroy_session(session);
		जाओ out;
	पूर्ण

	ret = 0;
	/* Register */
	list_add_tail(&session->session_list, &all_stat_sessions);
 out:
	mutex_unlock(&all_stat_sessions_mutex);

	वापस ret;
पूर्ण

व्योम unरेजिस्टर_stat_tracer(काष्ठा tracer_stat *trace)
अणु
	काष्ठा stat_session *node, *पंचांगp;

	mutex_lock(&all_stat_sessions_mutex);
	list_क्रम_each_entry_safe(node, पंचांगp, &all_stat_sessions, session_list) अणु
		अगर (node->ts == trace) अणु
			list_del(&node->session_list);
			destroy_session(node);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&all_stat_sessions_mutex);
पूर्ण
