<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * heartbeat.h
 *
 * Function prototypes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_HEARTBEAT_H
#घोषणा OCFS2_HEARTBEAT_H

व्योम ocfs2_init_node_maps(काष्ठा ocfs2_super *osb);

व्योम ocfs2_करो_node_करोwn(पूर्णांक node_num, व्योम *data);

/* node map functions - used to keep track of mounted and in-recovery
 * nodes. */
व्योम ocfs2_node_map_set_bit(काष्ठा ocfs2_super *osb,
			    काष्ठा ocfs2_node_map *map,
			    पूर्णांक bit);
व्योम ocfs2_node_map_clear_bit(काष्ठा ocfs2_super *osb,
			      काष्ठा ocfs2_node_map *map,
			      पूर्णांक bit);
पूर्णांक ocfs2_node_map_test_bit(काष्ठा ocfs2_super *osb,
			    काष्ठा ocfs2_node_map *map,
			    पूर्णांक bit);

#पूर्ण_अगर /* OCFS2_HEARTBEAT_H */
