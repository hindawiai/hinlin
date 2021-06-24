<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2005 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश "dlm_internal.h"
#समावेश "lockspace.h"
#समावेश "member.h"
#समावेश "lowcomms.h"
#समावेश "rcom.h"
#समावेश "config.h"
#समावेश "memory.h"
#समावेश "recover.h"
#समावेश "util.h"
#समावेश "lock.h"
#समावेश "dir.h"

/*
 * We use the upper 16 bits of the hash value to select the directory node.
 * Low bits are used क्रम distribution of rsb's among hash buckets on each node.
 *
 * To give the exact range wanted (0 to num_nodes-1), we apply a modulus of
 * num_nodes to the hash value.  This value in the desired range is used as an
 * offset पूर्णांकo the sorted list of nodeid's to give the particular nodeid.
 */

पूर्णांक dlm_hash2nodeid(काष्ठा dlm_ls *ls, uपूर्णांक32_t hash)
अणु
	uपूर्णांक32_t node;

	अगर (ls->ls_num_nodes == 1)
		वापस dlm_our_nodeid();
	अन्यथा अणु
		node = (hash >> 16) % ls->ls_total_weight;
		वापस ls->ls_node_array[node];
	पूर्ण
पूर्ण

पूर्णांक dlm_dir_nodeid(काष्ठा dlm_rsb *r)
अणु
	वापस r->res_dir_nodeid;
पूर्ण

व्योम dlm_recover_dir_nodeid(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r;

	करोwn_पढ़ो(&ls->ls_root_sem);
	list_क्रम_each_entry(r, &ls->ls_root_list, res_root_list) अणु
		r->res_dir_nodeid = dlm_hash2nodeid(ls, r->res_hash);
	पूर्ण
	up_पढ़ो(&ls->ls_root_sem);
पूर्ण

पूर्णांक dlm_recover_directory(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_member *memb;
	अक्षर *b, *last_name = शून्य;
	पूर्णांक error = -ENOMEM, last_len, nodeid, result;
	uपूर्णांक16_t namelen;
	अचिन्हित पूर्णांक count = 0, count_match = 0, count_bad = 0, count_add = 0;

	log_rinfo(ls, "dlm_recover_directory");

	अगर (dlm_no_directory(ls))
		जाओ out_status;

	last_name = kदो_स्मृति(DLM_RESNAME_MAXLEN, GFP_NOFS);
	अगर (!last_name)
		जाओ out;

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		अगर (memb->nodeid == dlm_our_nodeid())
			जारी;

		स_रखो(last_name, 0, DLM_RESNAME_MAXLEN);
		last_len = 0;

		क्रम (;;) अणु
			पूर्णांक left;
			error = dlm_recovery_stopped(ls);
			अगर (error)
				जाओ out_मुक्त;

			error = dlm_rcom_names(ls, memb->nodeid,
					       last_name, last_len);
			अगर (error)
				जाओ out_मुक्त;

			cond_resched();

			/*
			 * pick namelen/name pairs out of received buffer
			 */

			b = ls->ls_recover_buf->rc_buf;
			left = ls->ls_recover_buf->rc_header.h_length;
			left -= माप(काष्ठा dlm_rcom);

			क्रम (;;) अणु
				__be16 v;

				error = -EINVAL;
				अगर (left < माप(__be16))
					जाओ out_मुक्त;

				स_नकल(&v, b, माप(__be16));
				namelen = be16_to_cpu(v);
				b += माप(__be16);
				left -= माप(__be16);

				/* namelen of 0xFFFFF marks end of names क्रम
				   this node; namelen of 0 marks end of the
				   buffer */

				अगर (namelen == 0xFFFF)
					जाओ करोne;
				अगर (!namelen)
					अवरोध;

				अगर (namelen > left)
					जाओ out_मुक्त;

				अगर (namelen > DLM_RESNAME_MAXLEN)
					जाओ out_मुक्त;

				error = dlm_master_lookup(ls, memb->nodeid,
							  b, namelen,
							  DLM_LU_RECOVER_सूची,
							  &nodeid, &result);
				अगर (error) अणु
					log_error(ls, "recover_dir lookup %d",
						  error);
					जाओ out_मुक्त;
				पूर्ण

				/* The name was found in rsbtbl, but the
				 * master nodeid is dअगरferent from
				 * memb->nodeid which says it is the master.
				 * This should not happen. */

				अगर (result == DLM_LU_MATCH &&
				    nodeid != memb->nodeid) अणु
					count_bad++;
					log_error(ls, "recover_dir lookup %d "
						  "nodeid %d memb %d bad %u",
						  result, nodeid, memb->nodeid,
						  count_bad);
					prपूर्णांक_hex_dump_bytes("dlm_recover_dir ",
							     DUMP_PREFIX_NONE,
							     b, namelen);
				पूर्ण

				/* The name was found in rsbtbl, and the
				 * master nodeid matches memb->nodeid. */

				अगर (result == DLM_LU_MATCH &&
				    nodeid == memb->nodeid) अणु
					count_match++;
				पूर्ण

				/* The name was not found in rsbtbl and was
				 * added with memb->nodeid as the master. */

				अगर (result == DLM_LU_ADD) अणु
					count_add++;
				पूर्ण

				last_len = namelen;
				स_नकल(last_name, b, namelen);
				b += namelen;
				left -= namelen;
				count++;
			पूर्ण
		पूर्ण
	 करोne:
		;
	पूर्ण

 out_status:
	error = 0;
	dlm_set_recover_status(ls, DLM_RS_सूची);

	log_rinfo(ls, "dlm_recover_directory %u in %u new",
		  count, count_add);
 out_मुक्त:
	kमुक्त(last_name);
 out:
	वापस error;
पूर्ण

अटल काष्ठा dlm_rsb *find_rsb_root(काष्ठा dlm_ls *ls, अक्षर *name, पूर्णांक len)
अणु
	काष्ठा dlm_rsb *r;
	uपूर्णांक32_t hash, bucket;
	पूर्णांक rv;

	hash = jhash(name, len, 0);
	bucket = hash & (ls->ls_rsbtbl_size - 1);

	spin_lock(&ls->ls_rsbtbl[bucket].lock);
	rv = dlm_search_rsb_tree(&ls->ls_rsbtbl[bucket].keep, name, len, &r);
	अगर (rv)
		rv = dlm_search_rsb_tree(&ls->ls_rsbtbl[bucket].toss,
					 name, len, &r);
	spin_unlock(&ls->ls_rsbtbl[bucket].lock);

	अगर (!rv)
		वापस r;

	करोwn_पढ़ो(&ls->ls_root_sem);
	list_क्रम_each_entry(r, &ls->ls_root_list, res_root_list) अणु
		अगर (len == r->res_length && !स_भेद(name, r->res_name, len)) अणु
			up_पढ़ो(&ls->ls_root_sem);
			log_debug(ls, "find_rsb_root revert to root_list %s",
				  r->res_name);
			वापस r;
		पूर्ण
	पूर्ण
	up_पढ़ो(&ls->ls_root_sem);
	वापस शून्य;
पूर्ण

/* Find the rsb where we left off (or start again), then send rsb names
   क्रम rsb's we're master of and whose directory node matches the requesting
   node.  inbuf is the rsb name last sent, inlen is the name's length */

व्योम dlm_copy_master_names(काष्ठा dlm_ls *ls, अक्षर *inbuf, पूर्णांक inlen,
 			   अक्षर *outbuf, पूर्णांक outlen, पूर्णांक nodeid)
अणु
	काष्ठा list_head *list;
	काष्ठा dlm_rsb *r;
	पूर्णांक offset = 0, dir_nodeid;
	__be16 be_namelen;

	करोwn_पढ़ो(&ls->ls_root_sem);

	अगर (inlen > 1) अणु
		r = find_rsb_root(ls, inbuf, inlen);
		अगर (!r) अणु
			inbuf[inlen - 1] = '\0';
			log_error(ls, "copy_master_names from %d start %d %s",
				  nodeid, inlen, inbuf);
			जाओ out;
		पूर्ण
		list = r->res_root_list.next;
	पूर्ण अन्यथा अणु
		list = ls->ls_root_list.next;
	पूर्ण

	क्रम (offset = 0; list != &ls->ls_root_list; list = list->next) अणु
		r = list_entry(list, काष्ठा dlm_rsb, res_root_list);
		अगर (r->res_nodeid)
			जारी;

		dir_nodeid = dlm_dir_nodeid(r);
		अगर (dir_nodeid != nodeid)
			जारी;

		/*
		 * The block ends when we can't fit the following in the
		 * reमुख्यing buffer space:
		 * namelen (uपूर्णांक16_t) +
		 * name (r->res_length) +
		 * end-of-block record 0x0000 (uपूर्णांक16_t)
		 */

		अगर (offset + माप(uपूर्णांक16_t)*2 + r->res_length > outlen) अणु
			/* Write end-of-block record */
			be_namelen = cpu_to_be16(0);
			स_नकल(outbuf + offset, &be_namelen, माप(__be16));
			offset += माप(__be16);
			ls->ls_recover_dir_sent_msg++;
			जाओ out;
		पूर्ण

		be_namelen = cpu_to_be16(r->res_length);
		स_नकल(outbuf + offset, &be_namelen, माप(__be16));
		offset += माप(__be16);
		स_नकल(outbuf + offset, r->res_name, r->res_length);
		offset += r->res_length;
		ls->ls_recover_dir_sent_res++;
	पूर्ण

	/*
	 * If we've reached the end of the list (and there's room) ग_लिखो a
	 * terminating record.
	 */

	अगर ((list == &ls->ls_root_list) &&
	    (offset + माप(uपूर्णांक16_t) <= outlen)) अणु
		be_namelen = cpu_to_be16(0xFFFF);
		स_नकल(outbuf + offset, &be_namelen, माप(__be16));
		offset += माप(__be16);
		ls->ls_recover_dir_sent_msg++;
	पूर्ण
 out:
	up_पढ़ो(&ls->ls_root_sem);
पूर्ण

