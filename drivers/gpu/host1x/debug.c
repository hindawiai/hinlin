<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Google, Inc.
 * Author: Erik Gilling <konkers@android.com>
 *
 * Copyright (C) 2011-2013 NVIDIA Corporation
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/पन.स>

#समावेश "dev.h"
#समावेश "debug.h"
#समावेश "channel.h"

अटल DEFINE_MUTEX(debug_lock);

अचिन्हित पूर्णांक host1x_debug_trace_cmdbuf;

अटल pid_t host1x_debug_क्रमce_समयout_pid;
अटल u32 host1x_debug_क्रमce_समयout_val;
अटल u32 host1x_debug_क्रमce_समयout_channel;

व्योम host1x_debug_output(काष्ठा output *o, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक len;

	बहु_शुरू(args, fmt);
	len = vsnम_लिखो(o->buf, माप(o->buf), fmt, args);
	बहु_पूर्ण(args);

	o->fn(o->ctx, o->buf, len, false);
पूर्ण

व्योम host1x_debug_cont(काष्ठा output *o, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक len;

	बहु_शुरू(args, fmt);
	len = vsnम_लिखो(o->buf, माप(o->buf), fmt, args);
	बहु_पूर्ण(args);

	o->fn(o->ctx, o->buf, len, true);
पूर्ण

अटल पूर्णांक show_channel(काष्ठा host1x_channel *ch, व्योम *data, bool show_fअगरo)
अणु
	काष्ठा host1x *m = dev_get_drvdata(ch->dev->parent);
	काष्ठा output *o = data;

	mutex_lock(&ch->cdma.lock);
	mutex_lock(&debug_lock);

	अगर (show_fअगरo)
		host1x_hw_show_channel_fअगरo(m, ch, o);

	host1x_hw_show_channel_cdma(m, ch, o);

	mutex_unlock(&debug_lock);
	mutex_unlock(&ch->cdma.lock);

	वापस 0;
पूर्ण

अटल व्योम show_syncpts(काष्ठा host1x *m, काष्ठा output *o)
अणु
	काष्ठा list_head *pos;
	अचिन्हित पूर्णांक i;

	host1x_debug_output(o, "---- syncpts ----\n");

	क्रम (i = 0; i < host1x_syncpt_nb_pts(m); i++) अणु
		u32 max = host1x_syncpt_पढ़ो_max(m->syncpt + i);
		u32 min = host1x_syncpt_load(m->syncpt + i);
		अचिन्हित पूर्णांक रुकोers = 0;

		spin_lock(&m->syncpt[i].पूर्णांकr.lock);
		list_क्रम_each(pos, &m->syncpt[i].पूर्णांकr.रुको_head)
			रुकोers++;
		spin_unlock(&m->syncpt[i].पूर्णांकr.lock);

		अगर (!min && !max && !रुकोers)
			जारी;

		host1x_debug_output(o,
				    "id %u (%s) min %d max %d (%d waiters)\n",
				    i, m->syncpt[i].name, min, max, रुकोers);
	पूर्ण

	क्रम (i = 0; i < host1x_syncpt_nb_bases(m); i++) अणु
		u32 base_val;

		base_val = host1x_syncpt_load_रुको_base(m->syncpt + i);
		अगर (base_val)
			host1x_debug_output(o, "waitbase id %u val %d\n", i,
					    base_val);
	पूर्ण

	host1x_debug_output(o, "\n");
पूर्ण

अटल व्योम show_all(काष्ठा host1x *m, काष्ठा output *o, bool show_fअगरo)
अणु
	अचिन्हित पूर्णांक i;

	host1x_hw_show_mlocks(m, o);
	show_syncpts(m, o);
	host1x_debug_output(o, "---- channels ----\n");

	क्रम (i = 0; i < m->info->nb_channels; ++i) अणु
		काष्ठा host1x_channel *ch = host1x_channel_get_index(m, i);

		अगर (ch) अणु
			show_channel(ch, o, show_fअगरo);
			host1x_channel_put(ch);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक host1x_debug_show_all(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा output o = अणु
		.fn = ग_लिखो_to_seqfile,
		.ctx = s
	पूर्ण;

	show_all(s->निजी, &o, true);

	वापस 0;
पूर्ण

अटल पूर्णांक host1x_debug_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा output o = अणु
		.fn = ग_लिखो_to_seqfile,
		.ctx = s
	पूर्ण;

	show_all(s->निजी, &o, false);

	वापस 0;
पूर्ण

अटल पूर्णांक host1x_debug_खोलो_all(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, host1x_debug_show_all, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations host1x_debug_all_fops = अणु
	.खोलो = host1x_debug_खोलो_all,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल पूर्णांक host1x_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, host1x_debug_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations host1x_debug_fops = अणु
	.खोलो = host1x_debug_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल व्योम host1x_debugfs_init(काष्ठा host1x *host1x)
अणु
	काष्ठा dentry *de = debugfs_create_dir("tegra-host1x", शून्य);

	/* Store the created entry */
	host1x->debugfs = de;

	debugfs_create_file("status", S_IRUGO, de, host1x, &host1x_debug_fops);
	debugfs_create_file("status_all", S_IRUGO, de, host1x,
			    &host1x_debug_all_fops);

	debugfs_create_u32("trace_cmdbuf", S_IRUGO|S_IWUSR, de,
			   &host1x_debug_trace_cmdbuf);

	host1x_hw_debug_init(host1x, de);

	debugfs_create_u32("force_timeout_pid", S_IRUGO|S_IWUSR, de,
			   &host1x_debug_क्रमce_समयout_pid);
	debugfs_create_u32("force_timeout_val", S_IRUGO|S_IWUSR, de,
			   &host1x_debug_क्रमce_समयout_val);
	debugfs_create_u32("force_timeout_channel", S_IRUGO|S_IWUSR, de,
			   &host1x_debug_क्रमce_समयout_channel);
पूर्ण

अटल व्योम host1x_debugfs_निकास(काष्ठा host1x *host1x)
अणु
	debugfs_हटाओ_recursive(host1x->debugfs);
पूर्ण

व्योम host1x_debug_init(काष्ठा host1x *host1x)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_FS))
		host1x_debugfs_init(host1x);
पूर्ण

व्योम host1x_debug_deinit(काष्ठा host1x *host1x)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_FS))
		host1x_debugfs_निकास(host1x);
पूर्ण

व्योम host1x_debug_dump(काष्ठा host1x *host1x)
अणु
	काष्ठा output o = अणु
		.fn = ग_लिखो_to_prपूर्णांकk
	पूर्ण;

	show_all(host1x, &o, true);
पूर्ण

व्योम host1x_debug_dump_syncpts(काष्ठा host1x *host1x)
अणु
	काष्ठा output o = अणु
		.fn = ग_लिखो_to_prपूर्णांकk
	पूर्ण;

	show_syncpts(host1x, &o);
पूर्ण
