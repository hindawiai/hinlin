<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS fileserver list management.
 *
 * Copyright (C) 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

व्योम afs_put_serverlist(काष्ठा afs_net *net, काष्ठा afs_server_list *slist)
अणु
	पूर्णांक i;

	अगर (slist && refcount_dec_and_test(&slist->usage)) अणु
		क्रम (i = 0; i < slist->nr_servers; i++)
			afs_unuse_server(net, slist->servers[i].server,
					 afs_server_trace_put_slist);
		kमुक्त(slist);
	पूर्ण
पूर्ण

/*
 * Build a server list from a VLDB record.
 */
काष्ठा afs_server_list *afs_alloc_server_list(काष्ठा afs_cell *cell,
					      काष्ठा key *key,
					      काष्ठा afs_vldb_entry *vldb,
					      u8 type_mask)
अणु
	काष्ठा afs_server_list *slist;
	काष्ठा afs_server *server;
	पूर्णांक ret = -ENOMEM, nr_servers = 0, i, j;

	क्रम (i = 0; i < vldb->nr_servers; i++)
		अगर (vldb->fs_mask[i] & type_mask)
			nr_servers++;

	slist = kzalloc(काष्ठा_size(slist, servers, nr_servers), GFP_KERNEL);
	अगर (!slist)
		जाओ error;

	refcount_set(&slist->usage, 1);
	rwlock_init(&slist->lock);

	क्रम (i = 0; i < AFS_MAXTYPES; i++)
		slist->vids[i] = vldb->vid[i];

	/* Make sure a records exists क्रम each server in the list. */
	क्रम (i = 0; i < vldb->nr_servers; i++) अणु
		अगर (!(vldb->fs_mask[i] & type_mask))
			जारी;

		server = afs_lookup_server(cell, key, &vldb->fs_server[i],
					   vldb->addr_version[i]);
		अगर (IS_ERR(server)) अणु
			ret = PTR_ERR(server);
			अगर (ret == -ENOENT ||
			    ret == -ENOMEDIUM)
				जारी;
			जाओ error_2;
		पूर्ण

		/* Insertion-sort by UUID */
		क्रम (j = 0; j < slist->nr_servers; j++)
			अगर (स_भेद(&slist->servers[j].server->uuid,
				   &server->uuid,
				   माप(server->uuid)) >= 0)
				अवरोध;
		अगर (j < slist->nr_servers) अणु
			अगर (slist->servers[j].server == server) अणु
				afs_put_server(cell->net, server,
					       afs_server_trace_put_slist_isort);
				जारी;
			पूर्ण

			स_हटाओ(slist->servers + j + 1,
				slist->servers + j,
				(slist->nr_servers - j) * माप(काष्ठा afs_server_entry));
		पूर्ण

		slist->servers[j].server = server;
		slist->nr_servers++;
	पूर्ण

	अगर (slist->nr_servers == 0) अणु
		ret = -EDESTADDRREQ;
		जाओ error_2;
	पूर्ण

	वापस slist;

error_2:
	afs_put_serverlist(cell->net, slist);
error:
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Copy the annotations from an old server list to its potential replacement.
 */
bool afs_annotate_server_list(काष्ठा afs_server_list *new,
			      काष्ठा afs_server_list *old)
अणु
	काष्ठा afs_server *cur;
	पूर्णांक i, j;

	अगर (old->nr_servers != new->nr_servers)
		जाओ changed;

	क्रम (i = 0; i < old->nr_servers; i++)
		अगर (old->servers[i].server != new->servers[i].server)
			जाओ changed;

	वापस false;

changed:
	/* Maपूर्णांकain the same preferred server as beक्रमe अगर possible. */
	cur = old->servers[old->preferred].server;
	क्रम (j = 0; j < new->nr_servers; j++) अणु
		अगर (new->servers[j].server == cur) अणु
			new->preferred = j;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण
