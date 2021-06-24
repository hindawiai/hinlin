<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* /proc पूर्णांकerface क्रम AFS
 *
 * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश "internal.h"

काष्ठा afs_vl_seq_net_निजी अणु
	काष्ठा seq_net_निजी		seq;	/* Must be first */
	काष्ठा afs_vlserver_list	*vllist;
पूर्ण;

अटल अंतरभूत काष्ठा afs_net *afs_seq2net(काष्ठा seq_file *m)
अणु
	वापस afs_net(seq_file_net(m));
पूर्ण

अटल अंतरभूत काष्ठा afs_net *afs_seq2net_single(काष्ठा seq_file *m)
अणु
	वापस afs_net(seq_file_single_net(m));
पूर्ण

/*
 * Display the list of cells known to the namespace.
 */
अटल पूर्णांक afs_proc_cells_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा afs_vlserver_list *vllist;
	काष्ठा afs_cell *cell;

	अगर (v == SEQ_START_TOKEN) अणु
		/* display header on line 1 */
		seq_माला_दो(m, "USE ACT    TTL SV ST NAME\n");
		वापस 0;
	पूर्ण

	cell = list_entry(v, काष्ठा afs_cell, proc_link);
	vllist = rcu_dereference(cell->vl_servers);

	/* display one cell per line on subsequent lines */
	seq_म_लिखो(m, "%3u %3u %6lld %2u %2u %s\n",
		   atomic_पढ़ो(&cell->ref),
		   atomic_पढ़ो(&cell->active),
		   cell->dns_expiry - kसमय_get_real_seconds(),
		   vllist ? vllist->nr_servers : 0,
		   cell->state,
		   cell->name);
	वापस 0;
पूर्ण

अटल व्योम *afs_proc_cells_start(काष्ठा seq_file *m, loff_t *_pos)
	__acquires(rcu)
अणु
	rcu_पढ़ो_lock();
	वापस seq_hlist_start_head_rcu(&afs_seq2net(m)->proc_cells, *_pos);
पूर्ण

अटल व्योम *afs_proc_cells_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	वापस seq_hlist_next_rcu(v, &afs_seq2net(m)->proc_cells, pos);
पूर्ण

अटल व्योम afs_proc_cells_stop(काष्ठा seq_file *m, व्योम *v)
	__releases(rcu)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल स्थिर काष्ठा seq_operations afs_proc_cells_ops = अणु
	.start	= afs_proc_cells_start,
	.next	= afs_proc_cells_next,
	.stop	= afs_proc_cells_stop,
	.show	= afs_proc_cells_show,
पूर्ण;

/*
 * handle ग_लिखोs to /proc/fs/afs/cells
 * - to add cells: echo "add <cellname> <IP>[:<IP>][:<IP>]"
 */
अटल पूर्णांक afs_proc_cells_ग_लिखो(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा afs_net *net = afs_seq2net(m);
	अक्षर *name, *args;
	पूर्णांक ret;

	/* trim to first NL */
	name = स_प्रथम(buf, '\n', size);
	अगर (name)
		*name = 0;

	/* split पूर्णांकo command, name and argslist */
	name = म_अक्षर(buf, ' ');
	अगर (!name)
		जाओ inval;
	करो अणु
		*name++ = 0;
	पूर्ण जबतक(*name == ' ');
	अगर (!*name)
		जाओ inval;

	args = म_अक्षर(name, ' ');
	अगर (args) अणु
		करो अणु
			*args++ = 0;
		पूर्ण जबतक(*args == ' ');
		अगर (!*args)
			जाओ inval;
	पूर्ण

	/* determine command to perक्रमm */
	_debug("cmd=%s name=%s args=%s", buf, name, args);

	अगर (म_भेद(buf, "add") == 0) अणु
		काष्ठा afs_cell *cell;

		cell = afs_lookup_cell(net, name, म_माप(name), args, true);
		अगर (IS_ERR(cell)) अणु
			ret = PTR_ERR(cell);
			जाओ करोne;
		पूर्ण

		अगर (test_and_set_bit(AFS_CELL_FL_NO_GC, &cell->flags))
			afs_unuse_cell(net, cell, afs_cell_trace_unuse_no_pin);
	पूर्ण अन्यथा अणु
		जाओ inval;
	पूर्ण

	ret = 0;

करोne:
	_leave(" = %d", ret);
	वापस ret;

inval:
	ret = -EINVAL;
	prपूर्णांकk("kAFS: Invalid Command on /proc/fs/afs/cells file\n");
	जाओ करोne;
पूर्ण

/*
 * Display the name of the current workstation cell.
 */
अटल पूर्णांक afs_proc_rootcell_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा afs_cell *cell;
	काष्ठा afs_net *net;

	net = afs_seq2net_single(m);
	करोwn_पढ़ो(&net->cells_lock);
	cell = net->ws_cell;
	अगर (cell)
		seq_म_लिखो(m, "%s\n", cell->name);
	up_पढ़ो(&net->cells_lock);
	वापस 0;
पूर्ण

/*
 * Set the current workstation cell and optionally supply its list of volume
 * location servers.
 *
 *	echo "cell.name:192.168.231.14" >/proc/fs/afs/rootcell
 */
अटल पूर्णांक afs_proc_rootcell_ग_लिखो(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा afs_net *net = afs_seq2net_single(m);
	अक्षर *s;
	पूर्णांक ret;

	ret = -EINVAL;
	अगर (buf[0] == '.')
		जाओ out;
	अगर (स_प्रथम(buf, '/', size))
		जाओ out;

	/* trim to first NL */
	s = स_प्रथम(buf, '\n', size);
	अगर (s)
		*s = 0;

	/* determine command to perक्रमm */
	_debug("rootcell=%s", buf);

	ret = afs_cell_init(net, buf);

out:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर afs_vol_types[3][3] = अणु
	[AFSVL_RWVOL]	= "RW",
	[AFSVL_ROVOL]	= "RO",
	[AFSVL_BACKVOL]	= "BK",
पूर्ण;

/*
 * Display the list of volumes known to a cell.
 */
अटल पूर्णांक afs_proc_cell_volumes_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा afs_volume *vol = hlist_entry(v, काष्ठा afs_volume, proc_link);

	/* Display header on line 1 */
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(m, "USE VID      TY NAME\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(m, "%3d %08llx %s %s\n",
		   atomic_पढ़ो(&vol->usage), vol->vid,
		   afs_vol_types[vol->type],
		   vol->name);

	वापस 0;
पूर्ण

अटल व्योम *afs_proc_cell_volumes_start(काष्ठा seq_file *m, loff_t *_pos)
	__acquires(cell->proc_lock)
अणु
	काष्ठा afs_cell *cell = PDE_DATA(file_inode(m->file));

	rcu_पढ़ो_lock();
	वापस seq_hlist_start_head_rcu(&cell->proc_volumes, *_pos);
पूर्ण

अटल व्योम *afs_proc_cell_volumes_next(काष्ठा seq_file *m, व्योम *v,
					loff_t *_pos)
अणु
	काष्ठा afs_cell *cell = PDE_DATA(file_inode(m->file));

	वापस seq_hlist_next_rcu(v, &cell->proc_volumes, _pos);
पूर्ण

अटल व्योम afs_proc_cell_volumes_stop(काष्ठा seq_file *m, व्योम *v)
	__releases(cell->proc_lock)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल स्थिर काष्ठा seq_operations afs_proc_cell_volumes_ops = अणु
	.start	= afs_proc_cell_volumes_start,
	.next	= afs_proc_cell_volumes_next,
	.stop	= afs_proc_cell_volumes_stop,
	.show	= afs_proc_cell_volumes_show,
पूर्ण;

अटल स्थिर अक्षर *स्थिर dns_record_sources[NR__dns_record_source + 1] = अणु
	[DNS_RECORD_UNAVAILABLE]	= "unav",
	[DNS_RECORD_FROM_CONFIG]	= "cfg",
	[DNS_RECORD_FROM_DNS_A]		= "A",
	[DNS_RECORD_FROM_DNS_AFSDB]	= "AFSDB",
	[DNS_RECORD_FROM_DNS_SRV]	= "SRV",
	[DNS_RECORD_FROM_NSS]		= "nss",
	[NR__dns_record_source]		= "[weird]"
पूर्ण;

अटल स्थिर अक्षर *स्थिर dns_lookup_statuses[NR__dns_lookup_status + 1] = अणु
	[DNS_LOOKUP_NOT_DONE]		= "no-lookup",
	[DNS_LOOKUP_GOOD]		= "good",
	[DNS_LOOKUP_GOOD_WITH_BAD]	= "good/bad",
	[DNS_LOOKUP_BAD]		= "bad",
	[DNS_LOOKUP_GOT_NOT_FOUND]	= "not-found",
	[DNS_LOOKUP_GOT_LOCAL_FAILURE]	= "local-failure",
	[DNS_LOOKUP_GOT_TEMP_FAILURE]	= "temp-failure",
	[DNS_LOOKUP_GOT_NS_FAILURE]	= "ns-failure",
	[NR__dns_lookup_status]		= "[weird]"
पूर्ण;

/*
 * Display the list of Volume Location servers we're using क्रम a cell.
 */
अटल पूर्णांक afs_proc_cell_vlservers_show(काष्ठा seq_file *m, व्योम *v)
अणु
	स्थिर काष्ठा afs_vl_seq_net_निजी *priv = m->निजी;
	स्थिर काष्ठा afs_vlserver_list *vllist = priv->vllist;
	स्थिर काष्ठा afs_vlserver_entry *entry;
	स्थिर काष्ठा afs_vlserver *vlserver;
	स्थिर काष्ठा afs_addr_list *alist;
	पूर्णांक i;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(m, "# source %s, status %s\n",
			   dns_record_sources[vllist ? vllist->source : 0],
			   dns_lookup_statuses[vllist ? vllist->status : 0]);
		वापस 0;
	पूर्ण

	entry = v;
	vlserver = entry->server;
	alist = rcu_dereference(vlserver->addresses);

	seq_म_लिखो(m, "%s [p=%hu w=%hu s=%s,%s]:\n",
		   vlserver->name, entry->priority, entry->weight,
		   dns_record_sources[alist ? alist->source : entry->source],
		   dns_lookup_statuses[alist ? alist->status : entry->status]);
	अगर (alist) अणु
		क्रम (i = 0; i < alist->nr_addrs; i++)
			seq_म_लिखो(m, " %c %pISpc\n",
				   alist->preferred == i ? '>' : '-',
				   &alist->addrs[i].transport);
	पूर्ण
	seq_म_लिखो(m, " info: fl=%lx rtt=%d\n", vlserver->flags, vlserver->rtt);
	seq_म_लिखो(m, " probe: fl=%x e=%d ac=%d out=%d\n",
		   vlserver->probe.flags, vlserver->probe.error,
		   vlserver->probe.पात_code,
		   atomic_पढ़ो(&vlserver->probe_outstanding));
	वापस 0;
पूर्ण

अटल व्योम *afs_proc_cell_vlservers_start(काष्ठा seq_file *m, loff_t *_pos)
	__acquires(rcu)
अणु
	काष्ठा afs_vl_seq_net_निजी *priv = m->निजी;
	काष्ठा afs_vlserver_list *vllist;
	काष्ठा afs_cell *cell = PDE_DATA(file_inode(m->file));
	loff_t pos = *_pos;

	rcu_पढ़ो_lock();

	vllist = rcu_dereference(cell->vl_servers);
	priv->vllist = vllist;

	अगर (pos < 0)
		*_pos = pos = 0;
	अगर (pos == 0)
		वापस SEQ_START_TOKEN;

	अगर (pos - 1 >= vllist->nr_servers)
		वापस शून्य;

	वापस &vllist->servers[pos - 1];
पूर्ण

अटल व्योम *afs_proc_cell_vlservers_next(काष्ठा seq_file *m, व्योम *v,
					  loff_t *_pos)
अणु
	काष्ठा afs_vl_seq_net_निजी *priv = m->निजी;
	काष्ठा afs_vlserver_list *vllist = priv->vllist;
	loff_t pos;

	pos = *_pos;
	pos++;
	*_pos = pos;
	अगर (!vllist || pos - 1 >= vllist->nr_servers)
		वापस शून्य;

	वापस &vllist->servers[pos - 1];
पूर्ण

अटल व्योम afs_proc_cell_vlservers_stop(काष्ठा seq_file *m, व्योम *v)
	__releases(rcu)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल स्थिर काष्ठा seq_operations afs_proc_cell_vlservers_ops = अणु
	.start	= afs_proc_cell_vlservers_start,
	.next	= afs_proc_cell_vlservers_next,
	.stop	= afs_proc_cell_vlservers_stop,
	.show	= afs_proc_cell_vlservers_show,
पूर्ण;

/*
 * Display the list of fileservers we're using within a namespace.
 */
अटल पूर्णांक afs_proc_servers_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा afs_server *server;
	काष्ठा afs_addr_list *alist;
	पूर्णांक i;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(m, "UUID                                 REF ACT\n");
		वापस 0;
	पूर्ण

	server = list_entry(v, काष्ठा afs_server, proc_link);
	alist = rcu_dereference(server->addresses);
	seq_म_लिखो(m, "%pU %3d %3d\n",
		   &server->uuid,
		   atomic_पढ़ो(&server->ref),
		   atomic_पढ़ो(&server->active));
	seq_म_लिखो(m, "  - info: fl=%lx rtt=%u brk=%x\n",
		   server->flags, server->rtt, server->cb_s_अवरोध);
	seq_म_लिखो(m, "  - probe: last=%d out=%d\n",
		   (पूर्णांक)(jअगरfies - server->probed_at) / HZ,
		   atomic_पढ़ो(&server->probe_outstanding));
	seq_म_लिखो(m, "  - ALIST v=%u rsp=%lx f=%lx\n",
		   alist->version, alist->responded, alist->failed);
	क्रम (i = 0; i < alist->nr_addrs; i++)
		seq_म_लिखो(m, "    [%x] %pISpc%s\n",
			   i, &alist->addrs[i].transport,
			   alist->preferred == i ? "*" : "");
	वापस 0;
पूर्ण

अटल व्योम *afs_proc_servers_start(काष्ठा seq_file *m, loff_t *_pos)
	__acquires(rcu)
अणु
	rcu_पढ़ो_lock();
	वापस seq_hlist_start_head_rcu(&afs_seq2net(m)->fs_proc, *_pos);
पूर्ण

अटल व्योम *afs_proc_servers_next(काष्ठा seq_file *m, व्योम *v, loff_t *_pos)
अणु
	वापस seq_hlist_next_rcu(v, &afs_seq2net(m)->fs_proc, _pos);
पूर्ण

अटल व्योम afs_proc_servers_stop(काष्ठा seq_file *m, व्योम *v)
	__releases(rcu)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल स्थिर काष्ठा seq_operations afs_proc_servers_ops = अणु
	.start	= afs_proc_servers_start,
	.next	= afs_proc_servers_next,
	.stop	= afs_proc_servers_stop,
	.show	= afs_proc_servers_show,
पूर्ण;

/*
 * Display the list of strings that may be substituted क्रम the @sys pathname
 * macro.
 */
अटल पूर्णांक afs_proc_sysname_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा afs_net *net = afs_seq2net(m);
	काष्ठा afs_sysnames *sysnames = net->sysnames;
	अचिन्हित पूर्णांक i = (अचिन्हित दीर्घ)v - 1;

	अगर (i < sysnames->nr)
		seq_म_लिखो(m, "%s\n", sysnames->subs[i]);
	वापस 0;
पूर्ण

अटल व्योम *afs_proc_sysname_start(काष्ठा seq_file *m, loff_t *pos)
	__acquires(&net->sysnames_lock)
अणु
	काष्ठा afs_net *net = afs_seq2net(m);
	काष्ठा afs_sysnames *names;

	पढ़ो_lock(&net->sysnames_lock);

	names = net->sysnames;
	अगर (*pos >= names->nr)
		वापस शून्य;
	वापस (व्योम *)(अचिन्हित दीर्घ)(*pos + 1);
पूर्ण

अटल व्योम *afs_proc_sysname_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा afs_net *net = afs_seq2net(m);
	काष्ठा afs_sysnames *names = net->sysnames;

	*pos += 1;
	अगर (*pos >= names->nr)
		वापस शून्य;
	वापस (व्योम *)(अचिन्हित दीर्घ)(*pos + 1);
पूर्ण

अटल व्योम afs_proc_sysname_stop(काष्ठा seq_file *m, व्योम *v)
	__releases(&net->sysnames_lock)
अणु
	काष्ठा afs_net *net = afs_seq2net(m);

	पढ़ो_unlock(&net->sysnames_lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations afs_proc_sysname_ops = अणु
	.start	= afs_proc_sysname_start,
	.next	= afs_proc_sysname_next,
	.stop	= afs_proc_sysname_stop,
	.show	= afs_proc_sysname_show,
पूर्ण;

/*
 * Allow the @sys substitution to be configured.
 */
अटल पूर्णांक afs_proc_sysname_ग_लिखो(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा afs_sysnames *sysnames, *समाप्त;
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा afs_net *net = afs_seq2net(m);
	अक्षर *s, *p, *sub;
	पूर्णांक ret, len;

	sysnames = kzalloc(माप(*sysnames), GFP_KERNEL);
	अगर (!sysnames)
		वापस -ENOMEM;
	refcount_set(&sysnames->usage, 1);
	समाप्त = sysnames;

	p = buf;
	जबतक ((s = strsep(&p, " \t\n"))) अणु
		len = म_माप(s);
		अगर (len == 0)
			जारी;
		ret = -ENAMETOOLONG;
		अगर (len >= AFSNAMEMAX)
			जाओ error;

		अगर (len >= 4 &&
		    s[len - 4] == '@' &&
		    s[len - 3] == 's' &&
		    s[len - 2] == 'y' &&
		    s[len - 1] == 's')
			/* Protect against recursion */
			जाओ invalid;

		अगर (s[0] == '.' &&
		    (len < 2 || (len == 2 && s[1] == '.')))
			जाओ invalid;

		अगर (स_प्रथम(s, '/', len))
			जाओ invalid;

		ret = -EFBIG;
		अगर (sysnames->nr >= AFS_NR_SYSNAME)
			जाओ out;

		अगर (म_भेद(s, afs_init_sysname) == 0) अणु
			sub = (अक्षर *)afs_init_sysname;
		पूर्ण अन्यथा अणु
			ret = -ENOMEM;
			sub = kmemdup(s, len + 1, GFP_KERNEL);
			अगर (!sub)
				जाओ out;
		पूर्ण

		sysnames->subs[sysnames->nr] = sub;
		sysnames->nr++;
	पूर्ण

	अगर (sysnames->nr == 0) अणु
		sysnames->subs[0] = sysnames->blank;
		sysnames->nr++;
	पूर्ण

	ग_लिखो_lock(&net->sysnames_lock);
	समाप्त = net->sysnames;
	net->sysnames = sysnames;
	ग_लिखो_unlock(&net->sysnames_lock);
	ret = 0;
out:
	afs_put_sysnames(समाप्त);
	वापस ret;

invalid:
	ret = -EINVAL;
error:
	जाओ out;
पूर्ण

व्योम afs_put_sysnames(काष्ठा afs_sysnames *sysnames)
अणु
	पूर्णांक i;

	अगर (sysnames && refcount_dec_and_test(&sysnames->usage)) अणु
		क्रम (i = 0; i < sysnames->nr; i++)
			अगर (sysnames->subs[i] != afs_init_sysname &&
			    sysnames->subs[i] != sysnames->blank)
				kमुक्त(sysnames->subs[i]);
		kमुक्त(sysnames);
	पूर्ण
पूर्ण

/*
 * Display general per-net namespace statistics
 */
अटल पूर्णांक afs_proc_stats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा afs_net *net = afs_seq2net_single(m);

	seq_माला_दो(m, "kAFS statistics\n");

	seq_म_लिखो(m, "dir-mgmt: look=%u reval=%u inval=%u relpg=%u\n",
		   atomic_पढ़ो(&net->n_lookup),
		   atomic_पढ़ो(&net->n_reval),
		   atomic_पढ़ो(&net->n_inval),
		   atomic_पढ़ो(&net->n_relpg));

	seq_म_लिखो(m, "dir-data: rdpg=%u\n",
		   atomic_पढ़ो(&net->n_पढ़ो_dir));

	seq_म_लिखो(m, "dir-edit: cr=%u rm=%u\n",
		   atomic_पढ़ो(&net->n_dir_cr),
		   atomic_पढ़ो(&net->n_dir_rm));

	seq_म_लिखो(m, "file-rd : n=%u nb=%lu\n",
		   atomic_पढ़ो(&net->n_fetches),
		   atomic_दीर्घ_पढ़ो(&net->n_fetch_bytes));
	seq_म_लिखो(m, "file-wr : n=%u nb=%lu\n",
		   atomic_पढ़ो(&net->n_stores),
		   atomic_दीर्घ_पढ़ो(&net->n_store_bytes));
	वापस 0;
पूर्ण

/*
 * initialise /proc/fs/afs/<cell>/
 */
पूर्णांक afs_proc_cell_setup(काष्ठा afs_cell *cell)
अणु
	काष्ठा proc_dir_entry *dir;
	काष्ठा afs_net *net = cell->net;

	_enter("%p{%s},%p", cell, cell->name, net->proc_afs);

	dir = proc_net_सूची_गढ़ो(net->net, cell->name, net->proc_afs);
	अगर (!dir)
		जाओ error_dir;

	अगर (!proc_create_net_data("vlservers", 0444, dir,
				  &afs_proc_cell_vlservers_ops,
				  माप(काष्ठा afs_vl_seq_net_निजी),
				  cell) ||
	    !proc_create_net_data("volumes", 0444, dir,
				  &afs_proc_cell_volumes_ops,
				  माप(काष्ठा seq_net_निजी),
				  cell))
		जाओ error_tree;

	_leave(" = 0");
	वापस 0;

error_tree:
	हटाओ_proc_subtree(cell->name, net->proc_afs);
error_dir:
	_leave(" = -ENOMEM");
	वापस -ENOMEM;
पूर्ण

/*
 * हटाओ /proc/fs/afs/<cell>/
 */
व्योम afs_proc_cell_हटाओ(काष्ठा afs_cell *cell)
अणु
	काष्ठा afs_net *net = cell->net;

	_enter("");
	हटाओ_proc_subtree(cell->name, net->proc_afs);
	_leave("");
पूर्ण

/*
 * initialise the /proc/fs/afs/ directory
 */
पूर्णांक afs_proc_init(काष्ठा afs_net *net)
अणु
	काष्ठा proc_dir_entry *p;

	_enter("");

	p = proc_net_सूची_गढ़ो(net->net, "afs", net->net->proc_net);
	अगर (!p)
		जाओ error_dir;

	अगर (!proc_create_net_data_ग_लिखो("cells", 0644, p,
					&afs_proc_cells_ops,
					afs_proc_cells_ग_लिखो,
					माप(काष्ठा seq_net_निजी),
					शून्य) ||
	    !proc_create_net_single_ग_लिखो("rootcell", 0644, p,
					  afs_proc_rootcell_show,
					  afs_proc_rootcell_ग_लिखो,
					  शून्य) ||
	    !proc_create_net("servers", 0444, p, &afs_proc_servers_ops,
			     माप(काष्ठा seq_net_निजी)) ||
	    !proc_create_net_single("stats", 0444, p, afs_proc_stats_show, शून्य) ||
	    !proc_create_net_data_ग_लिखो("sysname", 0644, p,
					&afs_proc_sysname_ops,
					afs_proc_sysname_ग_लिखो,
					माप(काष्ठा seq_net_निजी),
					शून्य))
		जाओ error_tree;

	net->proc_afs = p;
	_leave(" = 0");
	वापस 0;

error_tree:
	proc_हटाओ(p);
error_dir:
	_leave(" = -ENOMEM");
	वापस -ENOMEM;
पूर्ण

/*
 * clean up the /proc/fs/afs/ directory
 */
व्योम afs_proc_cleanup(काष्ठा afs_net *net)
अणु
	proc_हटाओ(net->proc_afs);
	net->proc_afs = शून्य;
पूर्ण
