<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS cell alias detection
 *
 * Copyright (C) 2020 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/namei.h>
#समावेश <keys/rxrpc-type.h>
#समावेश "internal.h"

/*
 * Sample a volume.
 */
अटल काष्ठा afs_volume *afs_sample_volume(काष्ठा afs_cell *cell, काष्ठा key *key,
					    स्थिर अक्षर *name, अचिन्हित पूर्णांक namelen)
अणु
	काष्ठा afs_volume *volume;
	काष्ठा afs_fs_context fc = अणु
		.type		= 0, /* Explicitly leave it to the VLDB */
		.volnamesz	= namelen,
		.volname	= name,
		.net		= cell->net,
		.cell		= cell,
		.key		= key, /* This might need to be something */
	पूर्ण;

	volume = afs_create_volume(&fc);
	_leave(" = %p", volume);
	वापस volume;
पूर्ण

/*
 * Compare two addresses.
 */
अटल पूर्णांक afs_compare_addrs(स्थिर काष्ठा sockaddr_rxrpc *srx_a,
			     स्थिर काष्ठा sockaddr_rxrpc *srx_b)
अणु
	लघु port_a, port_b;
	पूर्णांक addr_a, addr_b, dअगरf;

	dअगरf = (लघु)srx_a->transport_type - (लघु)srx_b->transport_type;
	अगर (dअगरf)
		जाओ out;

	चयन (srx_a->transport_type) अणु
	हाल AF_INET: अणु
		स्थिर काष्ठा sockaddr_in *a = &srx_a->transport.sin;
		स्थिर काष्ठा sockaddr_in *b = &srx_b->transport.sin;
		addr_a = ntohl(a->sin_addr.s_addr);
		addr_b = ntohl(b->sin_addr.s_addr);
		dअगरf = addr_a - addr_b;
		अगर (dअगरf == 0) अणु
			port_a = ntohs(a->sin_port);
			port_b = ntohs(b->sin_port);
			dअगरf = port_a - port_b;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल AF_INET6: अणु
		स्थिर काष्ठा sockaddr_in6 *a = &srx_a->transport.sin6;
		स्थिर काष्ठा sockaddr_in6 *b = &srx_b->transport.sin6;
		dअगरf = स_भेद(&a->sin6_addr, &b->sin6_addr, 16);
		अगर (dअगरf == 0) अणु
			port_a = ntohs(a->sin6_port);
			port_b = ntohs(b->sin6_port);
			dअगरf = port_a - port_b;
		पूर्ण
		अवरोध;
	पूर्ण

	शेष:
		WARN_ON(1);
		dअगरf = 1;
	पूर्ण

out:
	वापस dअगरf;
पूर्ण

/*
 * Compare the address lists of a pair of fileservers.
 */
अटल पूर्णांक afs_compare_fs_alists(स्थिर काष्ठा afs_server *server_a,
				 स्थिर काष्ठा afs_server *server_b)
अणु
	स्थिर काष्ठा afs_addr_list *la, *lb;
	पूर्णांक a = 0, b = 0, addr_matches = 0;

	la = rcu_dereference(server_a->addresses);
	lb = rcu_dereference(server_b->addresses);

	जबतक (a < la->nr_addrs && b < lb->nr_addrs) अणु
		स्थिर काष्ठा sockaddr_rxrpc *srx_a = &la->addrs[a];
		स्थिर काष्ठा sockaddr_rxrpc *srx_b = &lb->addrs[b];
		पूर्णांक dअगरf = afs_compare_addrs(srx_a, srx_b);

		अगर (dअगरf < 0) अणु
			a++;
		पूर्ण अन्यथा अगर (dअगरf > 0) अणु
			b++;
		पूर्ण अन्यथा अणु
			addr_matches++;
			a++;
			b++;
		पूर्ण
	पूर्ण

	वापस addr_matches;
पूर्ण

/*
 * Compare the fileserver lists of two volumes.  The server lists are sorted in
 * order of ascending UUID.
 */
अटल पूर्णांक afs_compare_volume_slists(स्थिर काष्ठा afs_volume *vol_a,
				     स्थिर काष्ठा afs_volume *vol_b)
अणु
	स्थिर काष्ठा afs_server_list *la, *lb;
	पूर्णांक i, a = 0, b = 0, uuid_matches = 0, addr_matches = 0;

	la = rcu_dereference(vol_a->servers);
	lb = rcu_dereference(vol_b->servers);

	क्रम (i = 0; i < AFS_MAXTYPES; i++)
		अगर (la->vids[i] != lb->vids[i])
			वापस 0;

	जबतक (a < la->nr_servers && b < lb->nr_servers) अणु
		स्थिर काष्ठा afs_server *server_a = la->servers[a].server;
		स्थिर काष्ठा afs_server *server_b = lb->servers[b].server;
		पूर्णांक dअगरf = स_भेद(&server_a->uuid, &server_b->uuid, माप(uuid_t));

		अगर (dअगरf < 0) अणु
			a++;
		पूर्ण अन्यथा अगर (dअगरf > 0) अणु
			b++;
		पूर्ण अन्यथा अणु
			uuid_matches++;
			addr_matches += afs_compare_fs_alists(server_a, server_b);
			a++;
			b++;
		पूर्ण
	पूर्ण

	_leave(" = %d [um %d]", addr_matches, uuid_matches);
	वापस addr_matches;
पूर्ण

/*
 * Compare root.cell volumes.
 */
अटल पूर्णांक afs_compare_cell_roots(काष्ठा afs_cell *cell)
अणु
	काष्ठा afs_cell *p;

	_enter("");

	rcu_पढ़ो_lock();

	hlist_क्रम_each_entry_rcu(p, &cell->net->proc_cells, proc_link) अणु
		अगर (p == cell || p->alias_of)
			जारी;
		अगर (!p->root_volume)
			जारी; /* Ignore cells that करोn't have a root.cell volume. */

		अगर (afs_compare_volume_slists(cell->root_volume, p->root_volume) != 0)
			जाओ is_alias;
	पूर्ण

	rcu_पढ़ो_unlock();
	_leave(" = 0");
	वापस 0;

is_alias:
	rcu_पढ़ो_unlock();
	cell->alias_of = afs_use_cell(p, afs_cell_trace_use_alias);
	वापस 1;
पूर्ण

/*
 * Query the new cell क्रम a volume from a cell we're alपढ़ोy using.
 */
अटल पूर्णांक afs_query_क्रम_alias_one(काष्ठा afs_cell *cell, काष्ठा key *key,
				   काष्ठा afs_cell *p)
अणु
	काष्ठा afs_volume *volume, *pvol = शून्य;
	पूर्णांक ret;

	/* Arbitrarily pick a volume from the list. */
	पढ़ो_seqlock_excl(&p->volume_lock);
	अगर (!RB_EMPTY_ROOT(&p->volumes))
		pvol = afs_get_volume(rb_entry(p->volumes.rb_node,
					       काष्ठा afs_volume, cell_node),
				      afs_volume_trace_get_query_alias);
	पढ़ो_sequnlock_excl(&p->volume_lock);
	अगर (!pvol)
		वापस 0;

	_enter("%s:%s", cell->name, pvol->name);

	/* And see अगर it's in the new cell. */
	volume = afs_sample_volume(cell, key, pvol->name, pvol->name_len);
	अगर (IS_ERR(volume)) अणु
		afs_put_volume(cell->net, pvol, afs_volume_trace_put_query_alias);
		अगर (PTR_ERR(volume) != -ENOMEDIUM)
			वापस PTR_ERR(volume);
		/* That volume is not in the new cell, so not an alias */
		वापस 0;
	पूर्ण

	/* The new cell has a like-named volume also - compare volume ID,
	 * server and address lists.
	 */
	ret = 0;
	अगर (pvol->vid == volume->vid) अणु
		rcu_पढ़ो_lock();
		अगर (afs_compare_volume_slists(volume, pvol))
			ret = 1;
		rcu_पढ़ो_unlock();
	पूर्ण

	afs_put_volume(cell->net, volume, afs_volume_trace_put_query_alias);
	afs_put_volume(cell->net, pvol, afs_volume_trace_put_query_alias);
	वापस ret;
पूर्ण

/*
 * Query the new cell क्रम volumes we know exist in cells we're alपढ़ोy using.
 */
अटल पूर्णांक afs_query_क्रम_alias(काष्ठा afs_cell *cell, काष्ठा key *key)
अणु
	काष्ठा afs_cell *p;

	_enter("%s", cell->name);

	अगर (mutex_lock_पूर्णांकerruptible(&cell->net->proc_cells_lock) < 0)
		वापस -ERESTARTSYS;

	hlist_क्रम_each_entry(p, &cell->net->proc_cells, proc_link) अणु
		अगर (p == cell || p->alias_of)
			जारी;
		अगर (RB_EMPTY_ROOT(&p->volumes))
			जारी;
		अगर (p->root_volume)
			जारी; /* Ignore cells that have a root.cell volume. */
		afs_use_cell(p, afs_cell_trace_use_check_alias);
		mutex_unlock(&cell->net->proc_cells_lock);

		अगर (afs_query_क्रम_alias_one(cell, key, p) != 0)
			जाओ is_alias;

		अगर (mutex_lock_पूर्णांकerruptible(&cell->net->proc_cells_lock) < 0) अणु
			afs_unuse_cell(cell->net, p, afs_cell_trace_unuse_check_alias);
			वापस -ERESTARTSYS;
		पूर्ण

		afs_unuse_cell(cell->net, p, afs_cell_trace_unuse_check_alias);
	पूर्ण

	mutex_unlock(&cell->net->proc_cells_lock);
	_leave(" = 0");
	वापस 0;

is_alias:
	cell->alias_of = p; /* Transfer our ref */
	वापस 1;
पूर्ण

/*
 * Look up a VLDB record क्रम a volume.
 */
अटल अक्षर *afs_vl_get_cell_name(काष्ठा afs_cell *cell, काष्ठा key *key)
अणु
	काष्ठा afs_vl_cursor vc;
	अक्षर *cell_name = ERR_PTR(-EDESTADDRREQ);
	bool skipped = false, not_skipped = false;
	पूर्णांक ret;

	अगर (!afs_begin_vlserver_operation(&vc, cell, key))
		वापस ERR_PTR(-ERESTARTSYS);

	जबतक (afs_select_vlserver(&vc)) अणु
		अगर (!test_bit(AFS_VLSERVER_FL_IS_YFS, &vc.server->flags)) अणु
			vc.ac.error = -EOPNOTSUPP;
			skipped = true;
			जारी;
		पूर्ण
		not_skipped = true;
		cell_name = afs_yfsvl_get_cell_name(&vc);
	पूर्ण

	ret = afs_end_vlserver_operation(&vc);
	अगर (skipped && !not_skipped)
		ret = -EOPNOTSUPP;
	वापस ret < 0 ? ERR_PTR(ret) : cell_name;
पूर्ण

अटल पूर्णांक yfs_check_canonical_cell_name(काष्ठा afs_cell *cell, काष्ठा key *key)
अणु
	काष्ठा afs_cell *master;
	अक्षर *cell_name;

	cell_name = afs_vl_get_cell_name(cell, key);
	अगर (IS_ERR(cell_name))
		वापस PTR_ERR(cell_name);

	अगर (म_भेद(cell_name, cell->name) == 0) अणु
		kमुक्त(cell_name);
		वापस 0;
	पूर्ण

	master = afs_lookup_cell(cell->net, cell_name, म_माप(cell_name),
				 शून्य, false);
	kमुक्त(cell_name);
	अगर (IS_ERR(master))
		वापस PTR_ERR(master);

	cell->alias_of = master; /* Transfer our ref */
	वापस 1;
पूर्ण

अटल पूर्णांक afs_करो_cell_detect_alias(काष्ठा afs_cell *cell, काष्ठा key *key)
अणु
	काष्ठा afs_volume *root_volume;
	पूर्णांक ret;

	_enter("%s", cell->name);

	ret = yfs_check_canonical_cell_name(cell, key);
	अगर (ret != -EOPNOTSUPP)
		वापस ret;

	/* Try and get the root.cell volume क्रम comparison with other cells */
	root_volume = afs_sample_volume(cell, key, "root.cell", 9);
	अगर (!IS_ERR(root_volume)) अणु
		cell->root_volume = root_volume;
		वापस afs_compare_cell_roots(cell);
	पूर्ण

	अगर (PTR_ERR(root_volume) != -ENOMEDIUM)
		वापस PTR_ERR(root_volume);

	/* Okay, this cell करोesn't have an root.cell volume.  We need to
	 * locate some other अक्रमom volume and use that to check.
	 */
	वापस afs_query_क्रम_alias(cell, key);
पूर्ण

/*
 * Check to see अगर a new cell is an alias of a cell we alपढ़ोy have.  At this
 * poपूर्णांक we have the cell's volume server list.
 *
 * Returns 0 अगर we didn't detect an alias, 1 अगर we found an alias and an error
 * अगर we had problems gathering the data required.  In the हाल the we did
 * detect an alias, cell->alias_of is set to poपूर्णांक to the assumed master.
 */
पूर्णांक afs_cell_detect_alias(काष्ठा afs_cell *cell, काष्ठा key *key)
अणु
	काष्ठा afs_net *net = cell->net;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&net->cells_alias_lock) < 0)
		वापस -ERESTARTSYS;

	अगर (test_bit(AFS_CELL_FL_CHECK_ALIAS, &cell->flags)) अणु
		ret = afs_करो_cell_detect_alias(cell, key);
		अगर (ret >= 0)
			clear_bit_unlock(AFS_CELL_FL_CHECK_ALIAS, &cell->flags);
	पूर्ण अन्यथा अणु
		ret = cell->alias_of ? 1 : 0;
	पूर्ण

	mutex_unlock(&net->cells_alias_lock);

	अगर (ret == 1)
		pr_notice("kAFS: Cell %s is an alias of %s\n",
			  cell->name, cell->alias_of->name);
	वापस ret;
पूर्ण
