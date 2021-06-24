<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * heartbeat.h
 *
 * Function prototypes
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित O2CLUSTER_HEARTBEAT_H
#घोषणा O2CLUSTER_HEARTBEAT_H

#समावेश "ocfs2_heartbeat.h"

#घोषणा O2HB_REGION_TIMEOUT_MS		2000

#घोषणा O2HB_MAX_REGION_NAME_LEN	32

/* number of changes to be seen as live */
#घोषणा O2HB_LIVE_THRESHOLD	   2
/* number of equal samples to be seen as dead */
बाह्य अचिन्हित पूर्णांक o2hb_dead_threshold;
#घोषणा O2HB_DEFAULT_DEAD_THRESHOLD	   31
/* Otherwise MAX_WRITE_TIMEOUT will be zero... */
#घोषणा O2HB_MIN_DEAD_THRESHOLD	  2
#घोषणा O2HB_MAX_WRITE_TIMEOUT_MS (O2HB_REGION_TIMEOUT_MS * (o2hb_dead_threshold - 1))

#घोषणा O2HB_CB_MAGIC		0x51d1e4ec

/* callback stuff */
क्रमागत o2hb_callback_type अणु
	O2HB_NODE_DOWN_CB = 0,
	O2HB_NODE_UP_CB,
	O2HB_NUM_CB
पूर्ण;

काष्ठा o2nm_node;
प्रकार व्योम (o2hb_cb_func)(काष्ठा o2nm_node *, पूर्णांक, व्योम *);

काष्ठा o2hb_callback_func अणु
	u32			hc_magic;
	काष्ठा list_head	hc_item;
	o2hb_cb_func		*hc_func;
	व्योम			*hc_data;
	पूर्णांक			hc_priority;
	क्रमागत o2hb_callback_type hc_type;
पूर्ण;

काष्ठा config_group *o2hb_alloc_hb_set(व्योम);
व्योम o2hb_मुक्त_hb_set(काष्ठा config_group *group);

व्योम o2hb_setup_callback(काष्ठा o2hb_callback_func *hc,
			 क्रमागत o2hb_callback_type type,
			 o2hb_cb_func *func,
			 व्योम *data,
			 पूर्णांक priority);
पूर्णांक o2hb_रेजिस्टर_callback(स्थिर अक्षर *region_uuid,
			   काष्ठा o2hb_callback_func *hc);
व्योम o2hb_unरेजिस्टर_callback(स्थिर अक्षर *region_uuid,
			      काष्ठा o2hb_callback_func *hc);
व्योम o2hb_fill_node_map(अचिन्हित दीर्घ *map,
			अचिन्हित bytes);
व्योम o2hb_निकास(व्योम);
व्योम o2hb_init(व्योम);
पूर्णांक o2hb_check_node_heartbeating_no_sem(u8 node_num);
पूर्णांक o2hb_check_node_heartbeating_from_callback(u8 node_num);
व्योम o2hb_stop_all_regions(व्योम);
पूर्णांक o2hb_get_all_regions(अक्षर *region_uuids, u8 numregions);
पूर्णांक o2hb_global_heartbeat_active(व्योम);

#पूर्ण_अगर /* O2CLUSTER_HEARTBEAT_H */
