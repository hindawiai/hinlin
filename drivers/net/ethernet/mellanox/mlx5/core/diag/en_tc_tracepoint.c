<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#घोषणा CREATE_TRACE_POINTS
#समावेश "en_tc_tracepoint.h"

व्योम put_ids_to_array(पूर्णांक *ids,
		      स्थिर काष्ठा flow_action_entry *entries,
		      अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		ids[i] = entries[i].id;
पूर्ण

#घोषणा NAME_SIZE 16

अटल स्थिर अक्षर FLOWACT2STR[NUM_FLOW_ACTIONS][NAME_SIZE] = अणु
	[FLOW_ACTION_ACCEPT]	= "ACCEPT",
	[FLOW_ACTION_DROP]	= "DROP",
	[FLOW_ACTION_TRAP]	= "TRAP",
	[FLOW_ACTION_GOTO]	= "GOTO",
	[FLOW_ACTION_REसूचीECT]	= "REDIRECT",
	[FLOW_ACTION_MIRRED]	= "MIRRED",
	[FLOW_ACTION_VLAN_PUSH]	= "VLAN_PUSH",
	[FLOW_ACTION_VLAN_POP]	= "VLAN_POP",
	[FLOW_ACTION_VLAN_MANGLE]	= "VLAN_MANGLE",
	[FLOW_ACTION_TUNNEL_ENCAP]	= "TUNNEL_ENCAP",
	[FLOW_ACTION_TUNNEL_DECAP]	= "TUNNEL_DECAP",
	[FLOW_ACTION_MANGLE]	= "MANGLE",
	[FLOW_ACTION_ADD]	= "ADD",
	[FLOW_ACTION_CSUM]	= "CSUM",
	[FLOW_ACTION_MARK]	= "MARK",
	[FLOW_ACTION_WAKE]	= "WAKE",
	[FLOW_ACTION_QUEUE]	= "QUEUE",
	[FLOW_ACTION_SAMPLE]	= "SAMPLE",
	[FLOW_ACTION_POLICE]	= "POLICE",
	[FLOW_ACTION_CT]	= "CT",
पूर्ण;

स्थिर अक्षर *parse_action(काष्ठा trace_seq *p,
			 पूर्णांक *ids,
			 अचिन्हित पूर्णांक num)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		अगर (ids[i] < NUM_FLOW_ACTIONS)
			trace_seq_म_लिखो(p, "%s ", FLOWACT2STR[ids[i]]);
		अन्यथा
			trace_seq_म_लिखो(p, "UNKNOWN ");
	पूर्ण

	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण
