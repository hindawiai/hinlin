<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) 2005-2011 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश "dlm_internal.h"
#समावेश "lockspace.h"
#समावेश "member.h"
#समावेश "recoverd.h"
#समावेश "recover.h"
#समावेश "rcom.h"
#समावेश "config.h"
#समावेश "lowcomms.h"

पूर्णांक dlm_slots_version(काष्ठा dlm_header *h)
अणु
	अगर ((h->h_version & 0x0000FFFF) < DLM_HEADER_SLOTS)
		वापस 0;
	वापस 1;
पूर्ण

व्योम dlm_slot_save(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc,
		   काष्ठा dlm_member *memb)
अणु
	काष्ठा rcom_config *rf = (काष्ठा rcom_config *)rc->rc_buf;

	अगर (!dlm_slots_version(&rc->rc_header))
		वापस;

	memb->slot = le16_to_cpu(rf->rf_our_slot);
	memb->generation = le32_to_cpu(rf->rf_generation);
पूर्ण

व्योम dlm_slots_copy_out(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc)
अणु
	काष्ठा dlm_slot *slot;
	काष्ठा rcom_slot *ro;
	पूर्णांक i;

	ro = (काष्ठा rcom_slot *)(rc->rc_buf + माप(काष्ठा rcom_config));

	/* ls_slots array is sparse, but not rcom_slots */

	क्रम (i = 0; i < ls->ls_slots_size; i++) अणु
		slot = &ls->ls_slots[i];
		अगर (!slot->nodeid)
			जारी;
		ro->ro_nodeid = cpu_to_le32(slot->nodeid);
		ro->ro_slot = cpu_to_le16(slot->slot);
		ro++;
	पूर्ण
पूर्ण

#घोषणा SLOT_DEBUG_LINE 128

अटल व्योम log_slots(काष्ठा dlm_ls *ls, uपूर्णांक32_t gen, पूर्णांक num_slots,
		      काष्ठा rcom_slot *ro0, काष्ठा dlm_slot *array,
		      पूर्णांक array_size)
अणु
	अक्षर line[SLOT_DEBUG_LINE];
	पूर्णांक len = SLOT_DEBUG_LINE - 1;
	पूर्णांक pos = 0;
	पूर्णांक ret, i;

	स_रखो(line, 0, माप(line));

	अगर (array) अणु
		क्रम (i = 0; i < array_size; i++) अणु
			अगर (!array[i].nodeid)
				जारी;

			ret = snम_लिखो(line + pos, len - pos, " %d:%d",
				       array[i].slot, array[i].nodeid);
			अगर (ret >= len - pos)
				अवरोध;
			pos += ret;
		पूर्ण
	पूर्ण अन्यथा अगर (ro0) अणु
		क्रम (i = 0; i < num_slots; i++) अणु
			ret = snम_लिखो(line + pos, len - pos, " %d:%d",
				       ro0[i].ro_slot, ro0[i].ro_nodeid);
			अगर (ret >= len - pos)
				अवरोध;
			pos += ret;
		पूर्ण
	पूर्ण

	log_rinfo(ls, "generation %u slots %d%s", gen, num_slots, line);
पूर्ण

पूर्णांक dlm_slots_copy_in(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_member *memb;
	काष्ठा dlm_rcom *rc = ls->ls_recover_buf;
	काष्ठा rcom_config *rf = (काष्ठा rcom_config *)rc->rc_buf;
	काष्ठा rcom_slot *ro0, *ro;
	पूर्णांक our_nodeid = dlm_our_nodeid();
	पूर्णांक i, num_slots;
	uपूर्णांक32_t gen;

	अगर (!dlm_slots_version(&rc->rc_header))
		वापस -1;

	gen = le32_to_cpu(rf->rf_generation);
	अगर (gen <= ls->ls_generation) अणु
		log_error(ls, "dlm_slots_copy_in gen %u old %u",
			  gen, ls->ls_generation);
	पूर्ण
	ls->ls_generation = gen;

	num_slots = le16_to_cpu(rf->rf_num_slots);
	अगर (!num_slots)
		वापस -1;

	ro0 = (काष्ठा rcom_slot *)(rc->rc_buf + माप(काष्ठा rcom_config));

	क्रम (i = 0, ro = ro0; i < num_slots; i++, ro++) अणु
		ro->ro_nodeid = le32_to_cpu(ro->ro_nodeid);
		ro->ro_slot = le16_to_cpu(ro->ro_slot);
	पूर्ण

	log_slots(ls, gen, num_slots, ro0, शून्य, 0);

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		क्रम (i = 0, ro = ro0; i < num_slots; i++, ro++) अणु
			अगर (ro->ro_nodeid != memb->nodeid)
				जारी;
			memb->slot = ro->ro_slot;
			memb->slot_prev = memb->slot;
			अवरोध;
		पूर्ण

		अगर (memb->nodeid == our_nodeid) अणु
			अगर (ls->ls_slot && ls->ls_slot != memb->slot) अणु
				log_error(ls, "dlm_slots_copy_in our slot "
					  "changed %d %d", ls->ls_slot,
					  memb->slot);
				वापस -1;
			पूर्ण

			अगर (!ls->ls_slot)
				ls->ls_slot = memb->slot;
		पूर्ण

		अगर (!memb->slot) अणु
			log_error(ls, "dlm_slots_copy_in nodeid %d no slot",
				   memb->nodeid);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* क्रम any nodes that करो not support slots, we will not have set memb->slot
   in रुको_status_all(), so memb->slot will reमुख्य -1, and we will not
   assign slots or set ls_num_slots here */

पूर्णांक dlm_slots_assign(काष्ठा dlm_ls *ls, पूर्णांक *num_slots, पूर्णांक *slots_size,
		     काष्ठा dlm_slot **slots_out, uपूर्णांक32_t *gen_out)
अणु
	काष्ठा dlm_member *memb;
	काष्ठा dlm_slot *array;
	पूर्णांक our_nodeid = dlm_our_nodeid();
	पूर्णांक array_size, max_slots, i;
	पूर्णांक need = 0;
	पूर्णांक max = 0;
	पूर्णांक num = 0;
	uपूर्णांक32_t gen = 0;

	/* our own memb काष्ठा will have slot -1 gen 0 */

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		अगर (memb->nodeid == our_nodeid) अणु
			memb->slot = ls->ls_slot;
			memb->generation = ls->ls_generation;
			अवरोध;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		अगर (memb->generation > gen)
			gen = memb->generation;

		/* node करोesn't support slots */

		अगर (memb->slot == -1)
			वापस -1;

		/* node needs a slot asचिन्हित */

		अगर (!memb->slot)
			need++;

		/* node has a slot asचिन्हित */

		num++;

		अगर (!max || max < memb->slot)
			max = memb->slot;

		/* sanity check, once slot is asचिन्हित it shouldn't change */

		अगर (memb->slot_prev && memb->slot && memb->slot_prev != memb->slot) अणु
			log_error(ls, "nodeid %d slot changed %d %d",
				  memb->nodeid, memb->slot_prev, memb->slot);
			वापस -1;
		पूर्ण
		memb->slot_prev = memb->slot;
	पूर्ण

	array_size = max + need;
	array = kसुस्मृति(array_size, माप(*array), GFP_NOFS);
	अगर (!array)
		वापस -ENOMEM;

	num = 0;

	/* fill in slots (offsets) that are used */

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		अगर (!memb->slot)
			जारी;

		अगर (memb->slot > array_size) अणु
			log_error(ls, "invalid slot number %d", memb->slot);
			kमुक्त(array);
			वापस -1;
		पूर्ण

		array[memb->slot - 1].nodeid = memb->nodeid;
		array[memb->slot - 1].slot = memb->slot;
		num++;
	पूर्ण

	/* assign new slots from unused offsets */

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		अगर (memb->slot)
			जारी;

		क्रम (i = 0; i < array_size; i++) अणु
			अगर (array[i].nodeid)
				जारी;

			memb->slot = i + 1;
			memb->slot_prev = memb->slot;
			array[i].nodeid = memb->nodeid;
			array[i].slot = memb->slot;
			num++;

			अगर (!ls->ls_slot && memb->nodeid == our_nodeid)
				ls->ls_slot = memb->slot;
			अवरोध;
		पूर्ण

		अगर (!memb->slot) अणु
			log_error(ls, "no free slot found");
			kमुक्त(array);
			वापस -1;
		पूर्ण
	पूर्ण

	gen++;

	log_slots(ls, gen, num, शून्य, array, array_size);

	max_slots = (LOWCOMMS_MAX_TX_BUFFER_LEN - माप(काष्ठा dlm_rcom) -
		     माप(काष्ठा rcom_config)) / माप(काष्ठा rcom_slot);

	अगर (num > max_slots) अणु
		log_error(ls, "num_slots %d exceeds max_slots %d",
			  num, max_slots);
		kमुक्त(array);
		वापस -1;
	पूर्ण

	*gen_out = gen;
	*slots_out = array;
	*slots_size = array_size;
	*num_slots = num;
	वापस 0;
पूर्ण

अटल व्योम add_ordered_member(काष्ठा dlm_ls *ls, काष्ठा dlm_member *new)
अणु
	काष्ठा dlm_member *memb = शून्य;
	काष्ठा list_head *पंचांगp;
	काष्ठा list_head *newlist = &new->list;
	काष्ठा list_head *head = &ls->ls_nodes;

	list_क्रम_each(पंचांगp, head) अणु
		memb = list_entry(पंचांगp, काष्ठा dlm_member, list);
		अगर (new->nodeid < memb->nodeid)
			अवरोध;
	पूर्ण

	अगर (!memb)
		list_add_tail(newlist, head);
	अन्यथा अणु
		/* FIXME: can use list macro here */
		newlist->prev = पंचांगp->prev;
		newlist->next = पंचांगp;
		पंचांगp->prev->next = newlist;
		पंचांगp->prev = newlist;
	पूर्ण
पूर्ण

अटल पूर्णांक dlm_add_member(काष्ठा dlm_ls *ls, काष्ठा dlm_config_node *node)
अणु
	काष्ठा dlm_member *memb;
	पूर्णांक error;

	memb = kzalloc(माप(*memb), GFP_NOFS);
	अगर (!memb)
		वापस -ENOMEM;

	error = dlm_lowcomms_connect_node(node->nodeid);
	अगर (error < 0) अणु
		kमुक्त(memb);
		वापस error;
	पूर्ण

	memb->nodeid = node->nodeid;
	memb->weight = node->weight;
	memb->comm_seq = node->comm_seq;
	add_ordered_member(ls, memb);
	ls->ls_num_nodes++;
	वापस 0;
पूर्ण

अटल काष्ठा dlm_member *find_memb(काष्ठा list_head *head, पूर्णांक nodeid)
अणु
	काष्ठा dlm_member *memb;

	list_क्रम_each_entry(memb, head, list) अणु
		अगर (memb->nodeid == nodeid)
			वापस memb;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक dlm_is_member(काष्ठा dlm_ls *ls, पूर्णांक nodeid)
अणु
	अगर (find_memb(&ls->ls_nodes, nodeid))
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक dlm_is_हटाओd(काष्ठा dlm_ls *ls, पूर्णांक nodeid)
अणु
	अगर (find_memb(&ls->ls_nodes_gone, nodeid))
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम clear_memb_list(काष्ठा list_head *head)
अणु
	काष्ठा dlm_member *memb;

	जबतक (!list_empty(head)) अणु
		memb = list_entry(head->next, काष्ठा dlm_member, list);
		list_del(&memb->list);
		kमुक्त(memb);
	पूर्ण
पूर्ण

व्योम dlm_clear_members(काष्ठा dlm_ls *ls)
अणु
	clear_memb_list(&ls->ls_nodes);
	ls->ls_num_nodes = 0;
पूर्ण

व्योम dlm_clear_members_gone(काष्ठा dlm_ls *ls)
अणु
	clear_memb_list(&ls->ls_nodes_gone);
पूर्ण

अटल व्योम make_member_array(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_member *memb;
	पूर्णांक i, w, x = 0, total = 0, all_zero = 0, *array;

	kमुक्त(ls->ls_node_array);
	ls->ls_node_array = शून्य;

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		अगर (memb->weight)
			total += memb->weight;
	पूर्ण

	/* all nodes revert to weight of 1 अगर all have weight 0 */

	अगर (!total) अणु
		total = ls->ls_num_nodes;
		all_zero = 1;
	पूर्ण

	ls->ls_total_weight = total;
	array = kदो_स्मृति_array(total, माप(*array), GFP_NOFS);
	अगर (!array)
		वापस;

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		अगर (!all_zero && !memb->weight)
			जारी;

		अगर (all_zero)
			w = 1;
		अन्यथा
			w = memb->weight;

		DLM_ASSERT(x < total, prपूर्णांकk("total %d x %d\n", total, x););

		क्रम (i = 0; i < w; i++)
			array[x++] = memb->nodeid;
	पूर्ण

	ls->ls_node_array = array;
पूर्ण

/* send a status request to all members just to establish comms connections */

अटल पूर्णांक ping_members(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_member *memb;
	पूर्णांक error = 0;

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		error = dlm_recovery_stopped(ls);
		अगर (error)
			अवरोध;
		error = dlm_rcom_status(ls, memb->nodeid, 0);
		अगर (error)
			अवरोध;
	पूर्ण
	अगर (error)
		log_rinfo(ls, "ping_members aborted %d last nodeid %d",
			  error, ls->ls_recover_nodeid);
	वापस error;
पूर्ण

अटल व्योम dlm_lsop_recover_prep(काष्ठा dlm_ls *ls)
अणु
	अगर (!ls->ls_ops || !ls->ls_ops->recover_prep)
		वापस;
	ls->ls_ops->recover_prep(ls->ls_ops_arg);
पूर्ण

अटल व्योम dlm_lsop_recover_slot(काष्ठा dlm_ls *ls, काष्ठा dlm_member *memb)
अणु
	काष्ठा dlm_slot slot;
	uपूर्णांक32_t seq;
	पूर्णांक error;

	अगर (!ls->ls_ops || !ls->ls_ops->recover_slot)
		वापस;

	/* अगर there is no comms connection with this node
	   or the present comms connection is newer
	   than the one when this member was added, then
	   we consider the node to have failed (versus
	   being हटाओd due to dlm_release_lockspace) */

	error = dlm_comm_seq(memb->nodeid, &seq);

	अगर (!error && seq == memb->comm_seq)
		वापस;

	slot.nodeid = memb->nodeid;
	slot.slot = memb->slot;

	ls->ls_ops->recover_slot(ls->ls_ops_arg, &slot);
पूर्ण

व्योम dlm_lsop_recover_करोne(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_member *memb;
	काष्ठा dlm_slot *slots;
	पूर्णांक i, num;

	अगर (!ls->ls_ops || !ls->ls_ops->recover_करोne)
		वापस;

	num = ls->ls_num_nodes;
	slots = kसुस्मृति(num, माप(*slots), GFP_KERNEL);
	अगर (!slots)
		वापस;

	i = 0;
	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		अगर (i == num) अणु
			log_error(ls, "dlm_lsop_recover_done bad num %d", num);
			जाओ out;
		पूर्ण
		slots[i].nodeid = memb->nodeid;
		slots[i].slot = memb->slot;
		i++;
	पूर्ण

	ls->ls_ops->recover_करोne(ls->ls_ops_arg, slots, num,
				 ls->ls_slot, ls->ls_generation);
 out:
	kमुक्त(slots);
पूर्ण

अटल काष्ठा dlm_config_node *find_config_node(काष्ठा dlm_recover *rv,
						पूर्णांक nodeid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rv->nodes_count; i++) अणु
		अगर (rv->nodes[i].nodeid == nodeid)
			वापस &rv->nodes[i];
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक dlm_recover_members(काष्ठा dlm_ls *ls, काष्ठा dlm_recover *rv, पूर्णांक *neg_out)
अणु
	काष्ठा dlm_member *memb, *safe;
	काष्ठा dlm_config_node *node;
	पूर्णांक i, error, neg = 0, low = -1;

	/* previously हटाओd members that we've not finished removing need to
	   count as a negative change so the "neg" recovery steps will happen */

	list_क्रम_each_entry(memb, &ls->ls_nodes_gone, list) अणु
		log_rinfo(ls, "prev removed member %d", memb->nodeid);
		neg++;
	पूर्ण

	/* move departed members from ls_nodes to ls_nodes_gone */

	list_क्रम_each_entry_safe(memb, safe, &ls->ls_nodes, list) अणु
		node = find_config_node(rv, memb->nodeid);
		अगर (node && !node->new)
			जारी;

		अगर (!node) अणु
			log_rinfo(ls, "remove member %d", memb->nodeid);
		पूर्ण अन्यथा अणु
			/* हटाओd and re-added */
			log_rinfo(ls, "remove member %d comm_seq %u %u",
				  memb->nodeid, memb->comm_seq, node->comm_seq);
		पूर्ण

		neg++;
		list_move(&memb->list, &ls->ls_nodes_gone);
		ls->ls_num_nodes--;
		dlm_lsop_recover_slot(ls, memb);
	पूर्ण

	/* add new members to ls_nodes */

	क्रम (i = 0; i < rv->nodes_count; i++) अणु
		node = &rv->nodes[i];
		अगर (dlm_is_member(ls, node->nodeid))
			जारी;
		dlm_add_member(ls, node);
		log_rinfo(ls, "add member %d", node->nodeid);
	पूर्ण

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		अगर (low == -1 || memb->nodeid < low)
			low = memb->nodeid;
	पूर्ण
	ls->ls_low_nodeid = low;

	make_member_array(ls);
	*neg_out = neg;

	error = ping_members(ls);
	अगर (!error || error == -EPROTO) अणु
		/* new_lockspace() may be रुकोing to know अगर the config
		   is good or bad */
		ls->ls_members_result = error;
		complete(&ls->ls_members_करोne);
	पूर्ण

	log_rinfo(ls, "dlm_recover_members %d nodes", ls->ls_num_nodes);
	वापस error;
पूर्ण

/* Userspace guarantees that dlm_ls_stop() has completed on all nodes beक्रमe
   dlm_ls_start() is called on any of them to start the new recovery. */

पूर्णांक dlm_ls_stop(काष्ठा dlm_ls *ls)
अणु
	पूर्णांक new;

	/*
	 * Prevent dlm_recv from being in the middle of something when we करो
	 * the stop.  This includes ensuring dlm_recv isn't processing a
	 * recovery message (rcom), जबतक dlm_recoverd is पातing and
	 * resetting things from an in-progress recovery.  i.e. we want
	 * dlm_recoverd to पात its recovery without worrying about dlm_recv
	 * processing an rcom at the same समय.  Stopping dlm_recv also makes
	 * it easy क्रम dlm_receive_message() to check locking stopped and add a
	 * message to the requestqueue without races.
	 */

	करोwn_ग_लिखो(&ls->ls_recv_active);

	/*
	 * Abort any recovery that's in progress (see RECOVER_STOP,
	 * dlm_recovery_stopped()) and tell any other thपढ़ोs running in the
	 * dlm to quit any processing (see RUNNING, dlm_locking_stopped()).
	 */

	spin_lock(&ls->ls_recover_lock);
	set_bit(LSFL_RECOVER_STOP, &ls->ls_flags);
	new = test_and_clear_bit(LSFL_RUNNING, &ls->ls_flags);
	ls->ls_recover_seq++;
	spin_unlock(&ls->ls_recover_lock);

	/*
	 * Let dlm_recv run again, now any normal messages will be saved on the
	 * requestqueue क्रम later.
	 */

	up_ग_लिखो(&ls->ls_recv_active);

	/*
	 * This in_recovery lock करोes two things:
	 * 1) Keeps this function from वापसing until all thपढ़ोs are out
	 *    of locking routines and locking is truly stopped.
	 * 2) Keeps any new requests from being processed until it's unlocked
	 *    when recovery is complete.
	 */

	अगर (new) अणु
		set_bit(LSFL_RECOVER_DOWN, &ls->ls_flags);
		wake_up_process(ls->ls_recoverd_task);
		रुको_event(ls->ls_recover_lock_रुको,
			   test_bit(LSFL_RECOVER_LOCK, &ls->ls_flags));
	पूर्ण

	/*
	 * The recoverd suspend/resume makes sure that dlm_recoverd (अगर
	 * running) has noticed RECOVER_STOP above and quit processing the
	 * previous recovery.
	 */

	dlm_recoverd_suspend(ls);

	spin_lock(&ls->ls_recover_lock);
	kमुक्त(ls->ls_slots);
	ls->ls_slots = शून्य;
	ls->ls_num_slots = 0;
	ls->ls_slots_size = 0;
	ls->ls_recover_status = 0;
	spin_unlock(&ls->ls_recover_lock);

	dlm_recoverd_resume(ls);

	अगर (!ls->ls_recover_begin)
		ls->ls_recover_begin = jअगरfies;

	dlm_lsop_recover_prep(ls);
	वापस 0;
पूर्ण

पूर्णांक dlm_ls_start(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_recover *rv, *rv_old;
	काष्ठा dlm_config_node *nodes = शून्य;
	पूर्णांक error, count;

	rv = kzalloc(माप(*rv), GFP_NOFS);
	अगर (!rv)
		वापस -ENOMEM;

	error = dlm_config_nodes(ls->ls_name, &nodes, &count);
	अगर (error < 0)
		जाओ fail_rv;

	spin_lock(&ls->ls_recover_lock);

	/* the lockspace needs to be stopped beक्रमe it can be started */

	अगर (!dlm_locking_stopped(ls)) अणु
		spin_unlock(&ls->ls_recover_lock);
		log_error(ls, "start ignored: lockspace running");
		error = -EINVAL;
		जाओ fail;
	पूर्ण

	rv->nodes = nodes;
	rv->nodes_count = count;
	rv->seq = ++ls->ls_recover_seq;
	rv_old = ls->ls_recover_args;
	ls->ls_recover_args = rv;
	spin_unlock(&ls->ls_recover_lock);

	अगर (rv_old) अणु
		log_error(ls, "unused recovery %llx %d",
			  (अचिन्हित दीर्घ दीर्घ)rv_old->seq, rv_old->nodes_count);
		kमुक्त(rv_old->nodes);
		kमुक्त(rv_old);
	पूर्ण

	set_bit(LSFL_RECOVER_WORK, &ls->ls_flags);
	wake_up_process(ls->ls_recoverd_task);
	वापस 0;

 fail:
	kमुक्त(nodes);
 fail_rv:
	kमुक्त(rv);
	वापस error;
पूर्ण

