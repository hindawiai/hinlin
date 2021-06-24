<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * sloपंचांगap.h
 *
 * description here
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */


#अगर_अघोषित SLOTMAP_H
#घोषणा SLOTMAP_H

पूर्णांक ocfs2_init_slot_info(काष्ठा ocfs2_super *osb);
व्योम ocfs2_मुक्त_slot_info(काष्ठा ocfs2_super *osb);

पूर्णांक ocfs2_find_slot(काष्ठा ocfs2_super *osb);
व्योम ocfs2_put_slot(काष्ठा ocfs2_super *osb);

पूर्णांक ocfs2_refresh_slot_info(काष्ठा ocfs2_super *osb);

पूर्णांक ocfs2_node_num_to_slot(काष्ठा ocfs2_super *osb, अचिन्हित पूर्णांक node_num);
पूर्णांक ocfs2_slot_to_node_num_locked(काष्ठा ocfs2_super *osb, पूर्णांक slot_num,
				  अचिन्हित पूर्णांक *node_num);

पूर्णांक ocfs2_clear_slot(काष्ठा ocfs2_super *osb, पूर्णांक slot_num);

#पूर्ण_अगर
