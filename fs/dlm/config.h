<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2011 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#अगर_अघोषित __CONFIG_DOT_H__
#घोषणा __CONFIG_DOT_H__

#घोषणा DEFAULT_BUFFER_SIZE     4096

काष्ठा dlm_config_node अणु
	पूर्णांक nodeid;
	पूर्णांक weight;
	पूर्णांक new;
	uपूर्णांक32_t comm_seq;
पूर्ण;

#घोषणा DLM_MAX_ADDR_COUNT 3

काष्ठा dlm_config_info अणु
	पूर्णांक ci_tcp_port;
	पूर्णांक ci_buffer_size;
	पूर्णांक ci_rsbtbl_size;
	पूर्णांक ci_recover_समयr;
	पूर्णांक ci_toss_secs;
	पूर्णांक ci_scan_secs;
	पूर्णांक ci_log_debug;
	पूर्णांक ci_log_info;
	पूर्णांक ci_protocol;
	पूर्णांक ci_mark;
	पूर्णांक ci_समयwarn_cs;
	पूर्णांक ci_रुकोwarn_us;
	पूर्णांक ci_new_rsb_count;
	पूर्णांक ci_recover_callbacks;
	अक्षर ci_cluster_name[DLM_LOCKSPACE_LEN];
पूर्ण;

बाह्य काष्ठा dlm_config_info dlm_config;

पूर्णांक dlm_config_init(व्योम);
व्योम dlm_config_निकास(व्योम);
पूर्णांक dlm_config_nodes(अक्षर *lsname, काष्ठा dlm_config_node **nodes_out,
		     पूर्णांक *count_out);
पूर्णांक dlm_comm_seq(पूर्णांक nodeid, uपूर्णांक32_t *seq);
पूर्णांक dlm_our_nodeid(व्योम);
पूर्णांक dlm_our_addr(काष्ठा sockaddr_storage *addr, पूर्णांक num);

#पूर्ण_अगर				/* __CONFIG_DOT_H__ */

