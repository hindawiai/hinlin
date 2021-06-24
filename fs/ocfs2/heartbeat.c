<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * heartbeat.c
 *
 * Register ourselves with the heartbaet service, keep our node maps
 * up to date, and fire off recovery when needed.
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/highस्मृति.स>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "heartbeat.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "ocfs2_trace.h"

#समावेश "buffer_head_io.h"

अटल अंतरभूत व्योम __ocfs2_node_map_set_bit(काष्ठा ocfs2_node_map *map,
					    पूर्णांक bit);
अटल अंतरभूत व्योम __ocfs2_node_map_clear_bit(काष्ठा ocfs2_node_map *map,
					      पूर्णांक bit);

/* special हाल -1 क्रम now
 * TODO: should *really* make sure the calling func never passes -1!!  */
अटल व्योम ocfs2_node_map_init(काष्ठा ocfs2_node_map *map)
अणु
	map->num_nodes = OCFS2_NODE_MAP_MAX_NODES;
	स_रखो(map->map, 0, BITS_TO_LONGS(OCFS2_NODE_MAP_MAX_NODES) *
	       माप(अचिन्हित दीर्घ));
पूर्ण

व्योम ocfs2_init_node_maps(काष्ठा ocfs2_super *osb)
अणु
	spin_lock_init(&osb->node_map_lock);
	ocfs2_node_map_init(&osb->osb_recovering_orphan_dirs);
पूर्ण

व्योम ocfs2_करो_node_करोwn(पूर्णांक node_num, व्योम *data)
अणु
	काष्ठा ocfs2_super *osb = data;

	BUG_ON(osb->node_num == node_num);

	trace_ocfs2_करो_node_करोwn(node_num);

	अगर (!osb->cconn) अणु
		/*
		 * No cluster connection means we're not even पढ़ोy to
		 * participate yet.  We check the slots after the cluster
		 * comes up, so we will notice the node death then.  We
		 * can safely ignore it here.
		 */
		वापस;
	पूर्ण

	ocfs2_recovery_thपढ़ो(osb, node_num);
पूर्ण

अटल अंतरभूत व्योम __ocfs2_node_map_set_bit(काष्ठा ocfs2_node_map *map,
					    पूर्णांक bit)
अणु
	set_bit(bit, map->map);
पूर्ण

व्योम ocfs2_node_map_set_bit(काष्ठा ocfs2_super *osb,
			    काष्ठा ocfs2_node_map *map,
			    पूर्णांक bit)
अणु
	अगर (bit==-1)
		वापस;
	BUG_ON(bit >= map->num_nodes);
	spin_lock(&osb->node_map_lock);
	__ocfs2_node_map_set_bit(map, bit);
	spin_unlock(&osb->node_map_lock);
पूर्ण

अटल अंतरभूत व्योम __ocfs2_node_map_clear_bit(काष्ठा ocfs2_node_map *map,
					      पूर्णांक bit)
अणु
	clear_bit(bit, map->map);
पूर्ण

व्योम ocfs2_node_map_clear_bit(काष्ठा ocfs2_super *osb,
			      काष्ठा ocfs2_node_map *map,
			      पूर्णांक bit)
अणु
	अगर (bit==-1)
		वापस;
	BUG_ON(bit >= map->num_nodes);
	spin_lock(&osb->node_map_lock);
	__ocfs2_node_map_clear_bit(map, bit);
	spin_unlock(&osb->node_map_lock);
पूर्ण

पूर्णांक ocfs2_node_map_test_bit(काष्ठा ocfs2_super *osb,
			    काष्ठा ocfs2_node_map *map,
			    पूर्णांक bit)
अणु
	पूर्णांक ret;
	अगर (bit >= map->num_nodes) अणु
		mlog(ML_ERROR, "bit=%d map->num_nodes=%d\n", bit, map->num_nodes);
		BUG();
	पूर्ण
	spin_lock(&osb->node_map_lock);
	ret = test_bit(bit, map->map);
	spin_unlock(&osb->node_map_lock);
	वापस ret;
पूर्ण

