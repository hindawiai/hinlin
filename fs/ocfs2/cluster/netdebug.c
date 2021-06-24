<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * netdebug.c
 *
 * debug functionality क्रम o2net
 *
 * Copyright (C) 2005, 2008 Oracle.  All rights reserved.
 */

#अगर_घोषित CONFIG_DEBUG_FS

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/kref.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>

#समावेश <linux/uaccess.h>

#समावेश "tcp.h"
#समावेश "nodemanager.h"
#घोषणा MLOG_MASK_PREFIX ML_TCP
#समावेश "masklog.h"

#समावेश "tcp_internal.h"

#घोषणा O2NET_DEBUG_सूची		"o2net"
#घोषणा SC_DEBUG_NAME		"sock_containers"
#घोषणा NST_DEBUG_NAME		"send_tracking"
#घोषणा STATS_DEBUG_NAME	"stats"
#घोषणा NODES_DEBUG_NAME	"connected_nodes"

#घोषणा SHOW_SOCK_CONTAINERS	0
#घोषणा SHOW_SOCK_STATS		1

अटल काष्ठा dentry *o2net_dentry;

अटल DEFINE_SPINLOCK(o2net_debug_lock);

अटल LIST_HEAD(sock_containers);
अटल LIST_HEAD(send_tracking);

व्योम o2net_debug_add_nst(काष्ठा o2net_send_tracking *nst)
अणु
	spin_lock(&o2net_debug_lock);
	list_add(&nst->st_net_debug_item, &send_tracking);
	spin_unlock(&o2net_debug_lock);
पूर्ण

व्योम o2net_debug_del_nst(काष्ठा o2net_send_tracking *nst)
अणु
	spin_lock(&o2net_debug_lock);
	अगर (!list_empty(&nst->st_net_debug_item))
		list_del_init(&nst->st_net_debug_item);
	spin_unlock(&o2net_debug_lock);
पूर्ण

अटल काष्ठा o2net_send_tracking
			*next_nst(काष्ठा o2net_send_tracking *nst_start)
अणु
	काष्ठा o2net_send_tracking *nst, *ret = शून्य;

	निश्चित_spin_locked(&o2net_debug_lock);

	list_क्रम_each_entry(nst, &nst_start->st_net_debug_item,
			    st_net_debug_item) अणु
		/* discover the head of the list */
		अगर (&nst->st_net_debug_item == &send_tracking)
			अवरोध;

		/* use st_task to detect real nsts in the list */
		अगर (nst->st_task != शून्य) अणु
			ret = nst;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम *nst_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा o2net_send_tracking *nst, *dummy_nst = seq->निजी;

	spin_lock(&o2net_debug_lock);
	nst = next_nst(dummy_nst);
	spin_unlock(&o2net_debug_lock);

	वापस nst;
पूर्ण

अटल व्योम *nst_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा o2net_send_tracking *nst, *dummy_nst = seq->निजी;

	spin_lock(&o2net_debug_lock);
	nst = next_nst(dummy_nst);
	list_del_init(&dummy_nst->st_net_debug_item);
	अगर (nst)
		list_add(&dummy_nst->st_net_debug_item,
			 &nst->st_net_debug_item);
	spin_unlock(&o2net_debug_lock);

	वापस nst; /* unused, just needs to be null when करोne */
पूर्ण

अटल पूर्णांक nst_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा o2net_send_tracking *nst, *dummy_nst = seq->निजी;
	kसमय_प्रकार now;
	s64 sock, send, status;

	spin_lock(&o2net_debug_lock);
	nst = next_nst(dummy_nst);
	अगर (!nst)
		जाओ out;

	now = kसमय_get();
	sock = kसमय_प्रकारo_us(kसमय_sub(now, nst->st_sock_समय));
	send = kसमय_प्रकारo_us(kसमय_sub(now, nst->st_send_समय));
	status = kसमय_प्रकारo_us(kसमय_sub(now, nst->st_status_समय));

	/* get_task_comm isn't exported.  oh well. */
	seq_म_लिखो(seq, "%p:\n"
		   "  pid:          %lu\n"
		   "  tgid:         %lu\n"
		   "  process name: %s\n"
		   "  node:         %u\n"
		   "  sc:           %p\n"
		   "  message id:   %d\n"
		   "  message type: %u\n"
		   "  message key:  0x%08x\n"
		   "  sock acquiry: %lld usecs ago\n"
		   "  send start:   %lld usecs ago\n"
		   "  wait start:   %lld usecs ago\n",
		   nst, (अचिन्हित दीर्घ)task_pid_nr(nst->st_task),
		   (अचिन्हित दीर्घ)nst->st_task->tgid,
		   nst->st_task->comm, nst->st_node,
		   nst->st_sc, nst->st_id, nst->st_msg_type,
		   nst->st_msg_key,
		   (दीर्घ दीर्घ)sock,
		   (दीर्घ दीर्घ)send,
		   (दीर्घ दीर्घ)status);

out:
	spin_unlock(&o2net_debug_lock);

	वापस 0;
पूर्ण

अटल व्योम nst_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations nst_seq_ops = अणु
	.start = nst_seq_start,
	.next = nst_seq_next,
	.stop = nst_seq_stop,
	.show = nst_seq_show,
पूर्ण;

अटल पूर्णांक nst_fop_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा o2net_send_tracking *dummy_nst;

	dummy_nst = __seq_खोलो_निजी(file, &nst_seq_ops, माप(*dummy_nst));
	अगर (!dummy_nst)
		वापस -ENOMEM;
	o2net_debug_add_nst(dummy_nst);

	वापस 0;
पूर्ण

अटल पूर्णांक nst_fop_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा o2net_send_tracking *dummy_nst = seq->निजी;

	o2net_debug_del_nst(dummy_nst);
	वापस seq_release_निजी(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations nst_seq_fops = अणु
	.खोलो = nst_fop_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = nst_fop_release,
पूर्ण;

व्योम o2net_debug_add_sc(काष्ठा o2net_sock_container *sc)
अणु
	spin_lock(&o2net_debug_lock);
	list_add(&sc->sc_net_debug_item, &sock_containers);
	spin_unlock(&o2net_debug_lock);
पूर्ण

व्योम o2net_debug_del_sc(काष्ठा o2net_sock_container *sc)
अणु
	spin_lock(&o2net_debug_lock);
	list_del_init(&sc->sc_net_debug_item);
	spin_unlock(&o2net_debug_lock);
पूर्ण

काष्ठा o2net_sock_debug अणु
	पूर्णांक dbg_ctxt;
	काष्ठा o2net_sock_container *dbg_sock;
पूर्ण;

अटल काष्ठा o2net_sock_container
			*next_sc(काष्ठा o2net_sock_container *sc_start)
अणु
	काष्ठा o2net_sock_container *sc, *ret = शून्य;

	निश्चित_spin_locked(&o2net_debug_lock);

	list_क्रम_each_entry(sc, &sc_start->sc_net_debug_item,
			    sc_net_debug_item) अणु
		/* discover the head of the list miscast as a sc */
		अगर (&sc->sc_net_debug_item == &sock_containers)
			अवरोध;

		/* use sc_page to detect real scs in the list */
		अगर (sc->sc_page != शून्य) अणु
			ret = sc;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम *sc_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा o2net_sock_debug *sd = seq->निजी;
	काष्ठा o2net_sock_container *sc, *dummy_sc = sd->dbg_sock;

	spin_lock(&o2net_debug_lock);
	sc = next_sc(dummy_sc);
	spin_unlock(&o2net_debug_lock);

	वापस sc;
पूर्ण

अटल व्योम *sc_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा o2net_sock_debug *sd = seq->निजी;
	काष्ठा o2net_sock_container *sc, *dummy_sc = sd->dbg_sock;

	spin_lock(&o2net_debug_lock);
	sc = next_sc(dummy_sc);
	list_del_init(&dummy_sc->sc_net_debug_item);
	अगर (sc)
		list_add(&dummy_sc->sc_net_debug_item, &sc->sc_net_debug_item);
	spin_unlock(&o2net_debug_lock);

	वापस sc; /* unused, just needs to be null when करोne */
पूर्ण

#अगर_घोषित CONFIG_OCFS2_FS_STATS
# define sc_send_count(_s)		((_s)->sc_send_count)
# define sc_recv_count(_s)		((_s)->sc_recv_count)
# define sc_tv_acquiry_total_ns(_s)	(kसमय_प्रकारo_ns((_s)->sc_tv_acquiry_total))
# define sc_tv_send_total_ns(_s)	(kसमय_प्रकारo_ns((_s)->sc_tv_send_total))
# define sc_tv_status_total_ns(_s)	(kसमय_प्रकारo_ns((_s)->sc_tv_status_total))
# define sc_tv_process_total_ns(_s)	(kसमय_प्रकारo_ns((_s)->sc_tv_process_total))
#अन्यथा
# define sc_send_count(_s)		(0U)
# define sc_recv_count(_s)		(0U)
# define sc_tv_acquiry_total_ns(_s)	(0LL)
# define sc_tv_send_total_ns(_s)	(0LL)
# define sc_tv_status_total_ns(_s)	(0LL)
# define sc_tv_process_total_ns(_s)	(0LL)
#पूर्ण_अगर

/* So that debugfs.ocfs2 can determine which क्रमmat is being used */
#घोषणा O2NET_STATS_STR_VERSION		1
अटल व्योम sc_show_sock_stats(काष्ठा seq_file *seq,
			       काष्ठा o2net_sock_container *sc)
अणु
	अगर (!sc)
		वापस;

	seq_म_लिखो(seq, "%d,%u,%lu,%lld,%lld,%lld,%lu,%lld\n", O2NET_STATS_STR_VERSION,
		   sc->sc_node->nd_num, (अचिन्हित दीर्घ)sc_send_count(sc),
		   (दीर्घ दीर्घ)sc_tv_acquiry_total_ns(sc),
		   (दीर्घ दीर्घ)sc_tv_send_total_ns(sc),
		   (दीर्घ दीर्घ)sc_tv_status_total_ns(sc),
		   (अचिन्हित दीर्घ)sc_recv_count(sc),
		   (दीर्घ दीर्घ)sc_tv_process_total_ns(sc));
पूर्ण

अटल व्योम sc_show_sock_container(काष्ठा seq_file *seq,
				   काष्ठा o2net_sock_container *sc)
अणु
	काष्ठा inet_sock *inet = शून्य;
	__be32 saddr = 0, daddr = 0;
	__be16 sport = 0, dport = 0;

	अगर (!sc)
		वापस;

	अगर (sc->sc_sock) अणु
		inet = inet_sk(sc->sc_sock->sk);
		/* the stack's structs aren't sparse endian clean */
		saddr = (__क्रमce __be32)inet->inet_saddr;
		daddr = (__क्रमce __be32)inet->inet_daddr;
		sport = (__क्रमce __be16)inet->inet_sport;
		dport = (__क्रमce __be16)inet->inet_dport;
	पूर्ण

	/* XXX sigh, inet-> करोesn't have sparse annotation so any
	 * use of it here generates a warning with -Wbitwise */
	seq_म_लिखो(seq, "%p:\n"
		   "  krefs:           %d\n"
		   "  sock:            %pI4:%u -> "
				      "%pI4:%u\n"
		   "  remote node:     %s\n"
		   "  page off:        %zu\n"
		   "  handshake ok:    %u\n"
		   "  timer:           %lld usecs\n"
		   "  data ready:      %lld usecs\n"
		   "  advance start:   %lld usecs\n"
		   "  advance stop:    %lld usecs\n"
		   "  func start:      %lld usecs\n"
		   "  func stop:       %lld usecs\n"
		   "  func key:        0x%08x\n"
		   "  func type:       %u\n",
		   sc,
		   kref_पढ़ो(&sc->sc_kref),
		   &saddr, inet ? ntohs(sport) : 0,
		   &daddr, inet ? ntohs(dport) : 0,
		   sc->sc_node->nd_name,
		   sc->sc_page_off,
		   sc->sc_handshake_ok,
		   (दीर्घ दीर्घ)kसमय_प्रकारo_us(sc->sc_tv_समयr),
		   (दीर्घ दीर्घ)kसमय_प्रकारo_us(sc->sc_tv_data_पढ़ोy),
		   (दीर्घ दीर्घ)kसमय_प्रकारo_us(sc->sc_tv_advance_start),
		   (दीर्घ दीर्घ)kसमय_प्रकारo_us(sc->sc_tv_advance_stop),
		   (दीर्घ दीर्घ)kसमय_प्रकारo_us(sc->sc_tv_func_start),
		   (दीर्घ दीर्घ)kसमय_प्रकारo_us(sc->sc_tv_func_stop),
		   sc->sc_msg_key,
		   sc->sc_msg_type);
पूर्ण

अटल पूर्णांक sc_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा o2net_sock_debug *sd = seq->निजी;
	काष्ठा o2net_sock_container *sc, *dummy_sc = sd->dbg_sock;

	spin_lock(&o2net_debug_lock);
	sc = next_sc(dummy_sc);

	अगर (sc) अणु
		अगर (sd->dbg_ctxt == SHOW_SOCK_CONTAINERS)
			sc_show_sock_container(seq, sc);
		अन्यथा
			sc_show_sock_stats(seq, sc);
	पूर्ण

	spin_unlock(&o2net_debug_lock);

	वापस 0;
पूर्ण

अटल व्योम sc_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations sc_seq_ops = अणु
	.start = sc_seq_start,
	.next = sc_seq_next,
	.stop = sc_seq_stop,
	.show = sc_seq_show,
पूर्ण;

अटल पूर्णांक sc_common_खोलो(काष्ठा file *file, पूर्णांक ctxt)
अणु
	काष्ठा o2net_sock_debug *sd;
	काष्ठा o2net_sock_container *dummy_sc;

	dummy_sc = kzalloc(माप(*dummy_sc), GFP_KERNEL);
	अगर (!dummy_sc)
		वापस -ENOMEM;

	sd = __seq_खोलो_निजी(file, &sc_seq_ops, माप(*sd));
	अगर (!sd) अणु
		kमुक्त(dummy_sc);
		वापस -ENOMEM;
	पूर्ण

	sd->dbg_ctxt = ctxt;
	sd->dbg_sock = dummy_sc;

	o2net_debug_add_sc(dummy_sc);

	वापस 0;
पूर्ण

अटल पूर्णांक sc_fop_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा o2net_sock_debug *sd = seq->निजी;
	काष्ठा o2net_sock_container *dummy_sc = sd->dbg_sock;

	o2net_debug_del_sc(dummy_sc);
	kमुक्त(dummy_sc);
	वापस seq_release_निजी(inode, file);
पूर्ण

अटल पूर्णांक stats_fop_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस sc_common_खोलो(file, SHOW_SOCK_STATS);
पूर्ण

अटल स्थिर काष्ठा file_operations stats_seq_fops = अणु
	.खोलो = stats_fop_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = sc_fop_release,
पूर्ण;

अटल पूर्णांक sc_fop_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस sc_common_खोलो(file, SHOW_SOCK_CONTAINERS);
पूर्ण

अटल स्थिर काष्ठा file_operations sc_seq_fops = अणु
	.खोलो = sc_fop_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = sc_fop_release,
पूर्ण;

अटल पूर्णांक o2net_fill_biपंचांगap(अक्षर *buf, पूर्णांक len)
अणु
	अचिन्हित दीर्घ map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	पूर्णांक i = -1, out = 0;

	o2net_fill_node_map(map, माप(map));

	जबतक ((i = find_next_bit(map, O2NM_MAX_NODES, i + 1)) < O2NM_MAX_NODES)
		out += scnम_लिखो(buf + out, PAGE_SIZE - out, "%d ", i);
	out += scnम_लिखो(buf + out, PAGE_SIZE - out, "\n");

	वापस out;
पूर्ण

अटल पूर्णांक nodes_fop_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अक्षर *buf;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	i_size_ग_लिखो(inode, o2net_fill_biपंचांगap(buf, PAGE_SIZE));

	file->निजी_data = buf;

	वापस 0;
पूर्ण

अटल पूर्णांक o2net_debug_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार o2net_debug_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार nbytes, loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(buf, nbytes, ppos, file->निजी_data,
				       i_size_पढ़ो(file->f_mapping->host));
पूर्ण

अटल स्थिर काष्ठा file_operations nodes_fops = अणु
	.खोलो		= nodes_fop_खोलो,
	.release	= o2net_debug_release,
	.पढ़ो		= o2net_debug_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

व्योम o2net_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(o2net_dentry);
पूर्ण

व्योम o2net_debugfs_init(व्योम)
अणु
	umode_t mode = S_IFREG|S_IRUSR;

	o2net_dentry = debugfs_create_dir(O2NET_DEBUG_सूची, शून्य);

	debugfs_create_file(NST_DEBUG_NAME, mode, o2net_dentry, शून्य,
			    &nst_seq_fops);
	debugfs_create_file(SC_DEBUG_NAME, mode, o2net_dentry, शून्य,
			    &sc_seq_fops);
	debugfs_create_file(STATS_DEBUG_NAME, mode, o2net_dentry, शून्य,
			    &stats_seq_fops);
	debugfs_create_file(NODES_DEBUG_NAME, mode, o2net_dentry, शून्य,
			    &nodes_fops);
पूर्ण

#पूर्ण_अगर	/* CONFIG_DEBUG_FS */
