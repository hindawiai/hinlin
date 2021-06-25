<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	X.25 Packet Layer release 002
 *
 *	This is ALPHA test software. This code may अवरोध your machine,
 *	अक्रमomly fail to work with new releases, misbehave and/or generally
 *	screw up. It might even work.
 *
 *	This code REQUIRES 2.4 with seq_file support
 *
 *	History
 *	2002/10/06	Arnalकरो Carvalho de Melo  seq_file support
 */

#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/export.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/x25.h>

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम *x25_seq_route_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(x25_route_list_lock)
अणु
	पढ़ो_lock_bh(&x25_route_list_lock);
	वापस seq_list_start_head(&x25_route_list, *pos);
पूर्ण

अटल व्योम *x25_seq_route_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &x25_route_list, pos);
पूर्ण

अटल व्योम x25_seq_route_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(x25_route_list_lock)
अणु
	पढ़ो_unlock_bh(&x25_route_list_lock);
पूर्ण

अटल पूर्णांक x25_seq_route_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा x25_route *rt = list_entry(v, काष्ठा x25_route, node);

	अगर (v == &x25_route_list) अणु
		seq_माला_दो(seq, "Address          Digits  Device\n");
		जाओ out;
	पूर्ण

	rt = v;
	seq_म_लिखो(seq, "%-15s  %-6d  %-5s\n",
		   rt->address.x25_addr, rt->sigdigits,
		   rt->dev ? rt->dev->name : "???");
out:
	वापस 0;
पूर्ण

अटल व्योम *x25_seq_socket_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(x25_list_lock)
अणु
	पढ़ो_lock_bh(&x25_list_lock);
	वापस seq_hlist_start_head(&x25_list, *pos);
पूर्ण

अटल व्योम *x25_seq_socket_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_hlist_next(v, &x25_list, pos);
पूर्ण

अटल व्योम x25_seq_socket_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(x25_list_lock)
अणु
	पढ़ो_unlock_bh(&x25_list_lock);
पूर्ण

अटल पूर्णांक x25_seq_socket_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा sock *s;
	काष्ठा x25_sock *x25;
	काष्ठा net_device *dev;
	स्थिर अक्षर *devname;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq, "dest_addr  src_addr   dev   lci st vs vr "
				"va   t  t2 t21 t22 t23 Snd-Q Rcv-Q inode\n");
		जाओ out;
	पूर्ण

	s = sk_entry(v);
	x25 = x25_sk(s);

	अगर (!x25->neighbour || (dev = x25->neighbour->dev) == शून्य)
		devname = "???";
	अन्यथा
		devname = x25->neighbour->dev->name;

	seq_म_लिखो(seq, "%-10s %-10s %-5s %3.3X  %d  %d  %d  %d %3lu %3lu "
			"%3lu %3lu %3lu %5d %5d %ld\n",
		   !x25->dest_addr.x25_addr[0] ? "*" : x25->dest_addr.x25_addr,
		   !x25->source_addr.x25_addr[0] ? "*" : x25->source_addr.x25_addr,
		   devname, x25->lci & 0x0FFF, x25->state, x25->vs, x25->vr,
		   x25->va, x25_display_समयr(s) / HZ, x25->t2  / HZ,
		   x25->t21 / HZ, x25->t22 / HZ, x25->t23 / HZ,
		   sk_wmem_alloc_get(s),
		   sk_rmem_alloc_get(s),
		   s->sk_socket ? SOCK_INODE(s->sk_socket)->i_ino : 0L);
out:
	वापस 0;
पूर्ण

अटल व्योम *x25_seq_क्रमward_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(x25_क्रमward_list_lock)
अणु
	पढ़ो_lock_bh(&x25_क्रमward_list_lock);
	वापस seq_list_start_head(&x25_क्रमward_list, *pos);
पूर्ण

अटल व्योम *x25_seq_क्रमward_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &x25_क्रमward_list, pos);
पूर्ण

अटल व्योम x25_seq_क्रमward_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(x25_क्रमward_list_lock)
अणु
	पढ़ो_unlock_bh(&x25_क्रमward_list_lock);
पूर्ण

अटल पूर्णांक x25_seq_क्रमward_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा x25_क्रमward *f = list_entry(v, काष्ठा x25_क्रमward, node);

	अगर (v == &x25_क्रमward_list) अणु
		seq_म_लिखो(seq, "lci dev1       dev2\n");
		जाओ out;
	पूर्ण

	f = v;

	seq_म_लिखो(seq, "%d %-10s %-10s\n",
			f->lci, f->dev1->name, f->dev2->name);
out:
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations x25_seq_route_ops = अणु
	.start  = x25_seq_route_start,
	.next   = x25_seq_route_next,
	.stop   = x25_seq_route_stop,
	.show   = x25_seq_route_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations x25_seq_socket_ops = अणु
	.start  = x25_seq_socket_start,
	.next   = x25_seq_socket_next,
	.stop   = x25_seq_socket_stop,
	.show   = x25_seq_socket_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations x25_seq_क्रमward_ops = अणु
	.start  = x25_seq_क्रमward_start,
	.next   = x25_seq_क्रमward_next,
	.stop   = x25_seq_क्रमward_stop,
	.show   = x25_seq_क्रमward_show,
पूर्ण;

पूर्णांक __init x25_proc_init(व्योम)
अणु
	अगर (!proc_सूची_गढ़ो("x25", init_net.proc_net))
		वापस -ENOMEM;

	अगर (!proc_create_seq("x25/route", 0444, init_net.proc_net,
			 &x25_seq_route_ops))
		जाओ out;

	अगर (!proc_create_seq("x25/socket", 0444, init_net.proc_net,
			 &x25_seq_socket_ops))
		जाओ out;

	अगर (!proc_create_seq("x25/forward", 0444, init_net.proc_net,
			 &x25_seq_क्रमward_ops))
		जाओ out;
	वापस 0;

out:
	हटाओ_proc_subtree("x25", init_net.proc_net);
	वापस -ENOMEM;
पूर्ण

व्योम __निकास x25_proc_निकास(व्योम)
अणु
	हटाओ_proc_subtree("x25", init_net.proc_net);
पूर्ण

#अन्यथा /* CONFIG_PROC_FS */

पूर्णांक __init x25_proc_init(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम __निकास x25_proc_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */
