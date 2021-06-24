<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Incremental bus scan, based on bus topology
 *
 * Copyright (C) 2004-2006 Kristian Hoegsberg <krh@bitplanet.net>
 */

#समावेश <linux/bug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "core.h"

#घोषणा SELF_ID_PHY_ID(q)		(((q) >> 24) & 0x3f)
#घोषणा SELF_ID_EXTENDED(q)		(((q) >> 23) & 0x01)
#घोषणा SELF_ID_LINK_ON(q)		(((q) >> 22) & 0x01)
#घोषणा SELF_ID_GAP_COUNT(q)		(((q) >> 16) & 0x3f)
#घोषणा SELF_ID_PHY_SPEED(q)		(((q) >> 14) & 0x03)
#घोषणा SELF_ID_CONTENDER(q)		(((q) >> 11) & 0x01)
#घोषणा SELF_ID_PHY_INITIATOR(q)	(((q) >>  1) & 0x01)
#घोषणा SELF_ID_MORE_PACKETS(q)		(((q) >>  0) & 0x01)

#घोषणा SELF_ID_EXT_SEQUENCE(q)		(((q) >> 20) & 0x07)

#घोषणा SELFID_PORT_CHILD	0x3
#घोषणा SELFID_PORT_PARENT	0x2
#घोषणा SELFID_PORT_NCONN	0x1
#घोषणा SELFID_PORT_NONE	0x0

अटल u32 *count_ports(u32 *sid, पूर्णांक *total_port_count, पूर्णांक *child_port_count)
अणु
	u32 q;
	पूर्णांक port_type, shअगरt, seq;

	*total_port_count = 0;
	*child_port_count = 0;

	shअगरt = 6;
	q = *sid;
	seq = 0;

	जबतक (1) अणु
		port_type = (q >> shअगरt) & 0x03;
		चयन (port_type) अणु
		हाल SELFID_PORT_CHILD:
			(*child_port_count)++;
			fallthrough;
		हाल SELFID_PORT_PARENT:
		हाल SELFID_PORT_NCONN:
			(*total_port_count)++;
		हाल SELFID_PORT_NONE:
			अवरोध;
		पूर्ण

		shअगरt -= 2;
		अगर (shअगरt == 0) अणु
			अगर (!SELF_ID_MORE_PACKETS(q))
				वापस sid + 1;

			shअगरt = 16;
			sid++;
			q = *sid;

			/*
			 * Check that the extra packets actually are
			 * extended self ID packets and that the
			 * sequence numbers in the extended self ID
			 * packets increase as expected.
			 */

			अगर (!SELF_ID_EXTENDED(q) ||
			    seq != SELF_ID_EXT_SEQUENCE(q))
				वापस शून्य;

			seq++;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक get_port_type(u32 *sid, पूर्णांक port_index)
अणु
	पूर्णांक index, shअगरt;

	index = (port_index + 5) / 8;
	shअगरt = 16 - ((port_index + 5) & 7) * 2;
	वापस (sid[index] >> shअगरt) & 0x03;
पूर्ण

अटल काष्ठा fw_node *fw_node_create(u32 sid, पूर्णांक port_count, पूर्णांक color)
अणु
	काष्ठा fw_node *node;

	node = kzalloc(काष्ठा_size(node, ports, port_count), GFP_ATOMIC);
	अगर (node == शून्य)
		वापस शून्य;

	node->color = color;
	node->node_id = LOCAL_BUS | SELF_ID_PHY_ID(sid);
	node->link_on = SELF_ID_LINK_ON(sid);
	node->phy_speed = SELF_ID_PHY_SPEED(sid);
	node->initiated_reset = SELF_ID_PHY_INITIATOR(sid);
	node->port_count = port_count;

	refcount_set(&node->ref_count, 1);
	INIT_LIST_HEAD(&node->link);

	वापस node;
पूर्ण

/*
 * Compute the maximum hop count क्रम this node and it's children.  The
 * maximum hop count is the maximum number of connections between any
 * two nodes in the subtree rooted at this node.  We need this क्रम
 * setting the gap count.  As we build the tree bottom up in
 * build_tree() below, this is fairly easy to करो: क्रम each node we
 * मुख्यtain the max hop count and the max depth, ie the number of hops
 * to the furthest leaf.  Computing the max hop count अवरोधs करोwn पूर्णांकo
 * two हालs: either the path goes through this node, in which हाल
 * the hop count is the sum of the two biggest child depths plus 2.
 * Or it could be the हाल that the max hop path is entirely
 * contaपूर्णांकed in a child tree, in which हाल the max hop count is just
 * the max hop count of this child.
 */
अटल व्योम update_hop_count(काष्ठा fw_node *node)
अणु
	पूर्णांक depths[2] = अणु -1, -1 पूर्ण;
	पूर्णांक max_child_hops = 0;
	पूर्णांक i;

	क्रम (i = 0; i < node->port_count; i++) अणु
		अगर (node->ports[i] == शून्य)
			जारी;

		अगर (node->ports[i]->max_hops > max_child_hops)
			max_child_hops = node->ports[i]->max_hops;

		अगर (node->ports[i]->max_depth > depths[0]) अणु
			depths[1] = depths[0];
			depths[0] = node->ports[i]->max_depth;
		पूर्ण अन्यथा अगर (node->ports[i]->max_depth > depths[1])
			depths[1] = node->ports[i]->max_depth;
	पूर्ण

	node->max_depth = depths[0] + 1;
	node->max_hops = max(max_child_hops, depths[0] + depths[1] + 2);
पूर्ण

अटल अंतरभूत काष्ठा fw_node *fw_node(काष्ठा list_head *l)
अणु
	वापस list_entry(l, काष्ठा fw_node, link);
पूर्ण

/*
 * This function builds the tree representation of the topology given
 * by the self IDs from the latest bus reset.  During the स्थिरruction
 * of the tree, the function checks that the self IDs are valid and
 * पूर्णांकernally consistent.  On success this function वापसs the
 * fw_node corresponding to the local card otherwise शून्य.
 */
अटल काष्ठा fw_node *build_tree(काष्ठा fw_card *card,
				  u32 *sid, पूर्णांक self_id_count)
अणु
	काष्ठा fw_node *node, *child, *local_node, *irm_node;
	काष्ठा list_head stack, *h;
	u32 *next_sid, *end, q;
	पूर्णांक i, port_count, child_port_count, phy_id, parent_count, stack_depth;
	पूर्णांक gap_count;
	bool beta_repeaters_present;

	local_node = शून्य;
	node = शून्य;
	INIT_LIST_HEAD(&stack);
	stack_depth = 0;
	end = sid + self_id_count;
	phy_id = 0;
	irm_node = शून्य;
	gap_count = SELF_ID_GAP_COUNT(*sid);
	beta_repeaters_present = false;

	जबतक (sid < end) अणु
		next_sid = count_ports(sid, &port_count, &child_port_count);

		अगर (next_sid == शून्य) अणु
			fw_err(card, "inconsistent extended self IDs\n");
			वापस शून्य;
		पूर्ण

		q = *sid;
		अगर (phy_id != SELF_ID_PHY_ID(q)) अणु
			fw_err(card, "PHY ID mismatch in self ID: %d != %d\n",
			       phy_id, SELF_ID_PHY_ID(q));
			वापस शून्य;
		पूर्ण

		अगर (child_port_count > stack_depth) अणु
			fw_err(card, "topology stack underflow\n");
			वापस शून्य;
		पूर्ण

		/*
		 * Seek back from the top of our stack to find the
		 * start of the child nodes क्रम this node.
		 */
		क्रम (i = 0, h = &stack; i < child_port_count; i++)
			h = h->prev;
		/*
		 * When the stack is empty, this yields an invalid value,
		 * but that poपूर्णांकer will never be dereferenced.
		 */
		child = fw_node(h);

		node = fw_node_create(q, port_count, card->color);
		अगर (node == शून्य) अणु
			fw_err(card, "out of memory while building topology\n");
			वापस शून्य;
		पूर्ण

		अगर (phy_id == (card->node_id & 0x3f))
			local_node = node;

		अगर (SELF_ID_CONTENDER(q))
			irm_node = node;

		parent_count = 0;

		क्रम (i = 0; i < port_count; i++) अणु
			चयन (get_port_type(sid, i)) अणु
			हाल SELFID_PORT_PARENT:
				/*
				 * Who's your daddy?  We करोnt know the
				 * parent node at this समय, so we
				 * temporarily abuse node->color क्रम
				 * remembering the entry in the
				 * node->ports array where the parent
				 * node should be.  Later, when we
				 * handle the parent node, we fix up
				 * the reference.
				 */
				parent_count++;
				node->color = i;
				अवरोध;

			हाल SELFID_PORT_CHILD:
				node->ports[i] = child;
				/*
				 * Fix up parent reference क्रम this
				 * child node.
				 */
				child->ports[child->color] = node;
				child->color = card->color;
				child = fw_node(child->link.next);
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * Check that the node reports exactly one parent
		 * port, except क्रम the root, which of course should
		 * have no parents.
		 */
		अगर ((next_sid == end && parent_count != 0) ||
		    (next_sid < end && parent_count != 1)) अणु
			fw_err(card, "parent port inconsistency for node %d: "
			       "parent_count=%d\n", phy_id, parent_count);
			वापस शून्य;
		पूर्ण

		/* Pop the child nodes off the stack and push the new node. */
		__list_del(h->prev, &stack);
		list_add_tail(&node->link, &stack);
		stack_depth += 1 - child_port_count;

		अगर (node->phy_speed == SCODE_BETA &&
		    parent_count + child_port_count > 1)
			beta_repeaters_present = true;

		/*
		 * If PHYs report dअगरferent gap counts, set an invalid count
		 * which will क्रमce a gap count reconfiguration and a reset.
		 */
		अगर (SELF_ID_GAP_COUNT(q) != gap_count)
			gap_count = 0;

		update_hop_count(node);

		sid = next_sid;
		phy_id++;
	पूर्ण

	card->root_node = node;
	card->irm_node = irm_node;
	card->gap_count = gap_count;
	card->beta_repeaters_present = beta_repeaters_present;

	वापस local_node;
पूर्ण

प्रकार व्योम (*fw_node_callback_t)(काष्ठा fw_card * card,
				   काष्ठा fw_node * node,
				   काष्ठा fw_node * parent);

अटल व्योम क्रम_each_fw_node(काष्ठा fw_card *card, काष्ठा fw_node *root,
			     fw_node_callback_t callback)
अणु
	काष्ठा list_head list;
	काष्ठा fw_node *node, *next, *child, *parent;
	पूर्णांक i;

	INIT_LIST_HEAD(&list);

	fw_node_get(root);
	list_add_tail(&root->link, &list);
	parent = शून्य;
	list_क्रम_each_entry(node, &list, link) अणु
		node->color = card->color;

		क्रम (i = 0; i < node->port_count; i++) अणु
			child = node->ports[i];
			अगर (!child)
				जारी;
			अगर (child->color == card->color)
				parent = child;
			अन्यथा अणु
				fw_node_get(child);
				list_add_tail(&child->link, &list);
			पूर्ण
		पूर्ण

		callback(card, node, parent);
	पूर्ण

	list_क्रम_each_entry_safe(node, next, &list, link)
		fw_node_put(node);
पूर्ण

अटल व्योम report_lost_node(काष्ठा fw_card *card,
			     काष्ठा fw_node *node, काष्ठा fw_node *parent)
अणु
	fw_node_event(card, node, FW_NODE_DESTROYED);
	fw_node_put(node);

	/* Topology has changed - reset bus manager retry counter */
	card->bm_retries = 0;
पूर्ण

अटल व्योम report_found_node(काष्ठा fw_card *card,
			      काष्ठा fw_node *node, काष्ठा fw_node *parent)
अणु
	पूर्णांक b_path = (node->phy_speed == SCODE_BETA);

	अगर (parent != शून्य) अणु
		/* min() macro करोesn't work here with gcc 3.4 */
		node->max_speed = parent->max_speed < node->phy_speed ?
					parent->max_speed : node->phy_speed;
		node->b_path = parent->b_path && b_path;
	पूर्ण अन्यथा अणु
		node->max_speed = node->phy_speed;
		node->b_path = b_path;
	पूर्ण

	fw_node_event(card, node, FW_NODE_CREATED);

	/* Topology has changed - reset bus manager retry counter */
	card->bm_retries = 0;
पूर्ण

व्योम fw_destroy_nodes(काष्ठा fw_card *card)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->lock, flags);
	card->color++;
	अगर (card->local_node != शून्य)
		क्रम_each_fw_node(card, card->local_node, report_lost_node);
	card->local_node = शून्य;
	spin_unlock_irqrestore(&card->lock, flags);
पूर्ण

अटल व्योम move_tree(काष्ठा fw_node *node0, काष्ठा fw_node *node1, पूर्णांक port)
अणु
	काष्ठा fw_node *tree;
	पूर्णांक i;

	tree = node1->ports[port];
	node0->ports[port] = tree;
	क्रम (i = 0; i < tree->port_count; i++) अणु
		अगर (tree->ports[i] == node1) अणु
			tree->ports[i] = node0;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Compare the old topology tree क्रम card with the new one specअगरied by root.
 * Queue the nodes and mark them as either found, lost or updated.
 * Update the nodes in the card topology tree as we go.
 */
अटल व्योम update_tree(काष्ठा fw_card *card, काष्ठा fw_node *root)
अणु
	काष्ठा list_head list0, list1;
	काष्ठा fw_node *node0, *node1, *next1;
	पूर्णांक i, event;

	INIT_LIST_HEAD(&list0);
	list_add_tail(&card->local_node->link, &list0);
	INIT_LIST_HEAD(&list1);
	list_add_tail(&root->link, &list1);

	node0 = fw_node(list0.next);
	node1 = fw_node(list1.next);

	जबतक (&node0->link != &list0) अणु
		WARN_ON(node0->port_count != node1->port_count);

		अगर (node0->link_on && !node1->link_on)
			event = FW_NODE_LINK_OFF;
		अन्यथा अगर (!node0->link_on && node1->link_on)
			event = FW_NODE_LINK_ON;
		अन्यथा अगर (node1->initiated_reset && node1->link_on)
			event = FW_NODE_INITIATED_RESET;
		अन्यथा
			event = FW_NODE_UPDATED;

		node0->node_id = node1->node_id;
		node0->color = card->color;
		node0->link_on = node1->link_on;
		node0->initiated_reset = node1->initiated_reset;
		node0->max_hops = node1->max_hops;
		node1->color = card->color;
		fw_node_event(card, node0, event);

		अगर (card->root_node == node1)
			card->root_node = node0;
		अगर (card->irm_node == node1)
			card->irm_node = node0;

		क्रम (i = 0; i < node0->port_count; i++) अणु
			अगर (node0->ports[i] && node1->ports[i]) अणु
				/*
				 * This port didn't change, queue the
				 * connected node क्रम further
				 * investigation.
				 */
				अगर (node0->ports[i]->color == card->color)
					जारी;
				list_add_tail(&node0->ports[i]->link, &list0);
				list_add_tail(&node1->ports[i]->link, &list1);
			पूर्ण अन्यथा अगर (node0->ports[i]) अणु
				/*
				 * The nodes connected here were
				 * unplugged; unref the lost nodes and
				 * queue FW_NODE_LOST callbacks क्रम
				 * them.
				 */

				क्रम_each_fw_node(card, node0->ports[i],
						 report_lost_node);
				node0->ports[i] = शून्य;
			पूर्ण अन्यथा अगर (node1->ports[i]) अणु
				/*
				 * One or more node were connected to
				 * this port. Move the new nodes पूर्णांकo
				 * the tree and queue FW_NODE_CREATED
				 * callbacks क्रम them.
				 */
				move_tree(node0, node1, i);
				क्रम_each_fw_node(card, node0->ports[i],
						 report_found_node);
			पूर्ण
		पूर्ण

		node0 = fw_node(node0->link.next);
		next1 = fw_node(node1->link.next);
		fw_node_put(node1);
		node1 = next1;
	पूर्ण
पूर्ण

अटल व्योम update_topology_map(काष्ठा fw_card *card,
				u32 *self_ids, पूर्णांक self_id_count)
अणु
	पूर्णांक node_count = (card->root_node->node_id & 0x3f) + 1;
	__be32 *map = card->topology_map;

	*map++ = cpu_to_be32((self_id_count + 2) << 16);
	*map++ = cpu_to_be32(be32_to_cpu(card->topology_map[1]) + 1);
	*map++ = cpu_to_be32((node_count << 16) | self_id_count);

	जबतक (self_id_count--)
		*map++ = cpu_to_be32p(self_ids++);

	fw_compute_block_crc(card->topology_map);
पूर्ण

व्योम fw_core_handle_bus_reset(काष्ठा fw_card *card, पूर्णांक node_id, पूर्णांक generation,
			      पूर्णांक self_id_count, u32 *self_ids, bool bm_abdicate)
अणु
	काष्ठा fw_node *local_node;
	अचिन्हित दीर्घ flags;

	/*
	 * If the selfID buffer is not the immediate successor of the
	 * previously processed one, we cannot reliably compare the
	 * old and new topologies.
	 */
	अगर (!is_next_generation(generation, card->generation) &&
	    card->local_node != शून्य) अणु
		fw_destroy_nodes(card);
		card->bm_retries = 0;
	पूर्ण

	spin_lock_irqsave(&card->lock, flags);

	card->broadcast_channel_allocated = card->broadcast_channel_स्वतः_allocated;
	card->node_id = node_id;
	/*
	 * Update node_id beक्रमe generation to prevent anybody from using
	 * a stale node_id together with a current generation.
	 */
	smp_wmb();
	card->generation = generation;
	card->reset_jअगरfies = get_jअगरfies_64();
	card->bm_node_id  = 0xffff;
	card->bm_abdicate = bm_abdicate;
	fw_schedule_bm_work(card, 0);

	local_node = build_tree(card, self_ids, self_id_count);

	update_topology_map(card, self_ids, self_id_count);

	card->color++;

	अगर (local_node == शून्य) अणु
		fw_err(card, "topology build failed\n");
		/* FIXME: We need to issue a bus reset in this हाल. */
	पूर्ण अन्यथा अगर (card->local_node == शून्य) अणु
		card->local_node = local_node;
		क्रम_each_fw_node(card, local_node, report_found_node);
	पूर्ण अन्यथा अणु
		update_tree(card, local_node);
	पूर्ण

	spin_unlock_irqrestore(&card->lock, flags);
पूर्ण
EXPORT_SYMBOL(fw_core_handle_bus_reset);
