<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2020, NXP Semiconductors
 */
#अगर_अघोषित _SJA1105_VL_H
#घोषणा _SJA1105_VL_H

#समावेश "sja1105.h"

#अगर IS_ENABLED(CONFIG_NET_DSA_SJA1105_VL)

पूर्णांक sja1105_vl_redirect(काष्ठा sja1105_निजी *priv, पूर्णांक port,
			काष्ठा netlink_ext_ack *extack, अचिन्हित दीर्घ cookie,
			काष्ठा sja1105_key *key, अचिन्हित दीर्घ destports,
			bool append);

पूर्णांक sja1105_vl_delete(काष्ठा sja1105_निजी *priv, पूर्णांक port,
		      काष्ठा sja1105_rule *rule,
		      काष्ठा netlink_ext_ack *extack);

पूर्णांक sja1105_vl_gate(काष्ठा sja1105_निजी *priv, पूर्णांक port,
		    काष्ठा netlink_ext_ack *extack, अचिन्हित दीर्घ cookie,
		    काष्ठा sja1105_key *key, u32 index, s32 prio,
		    u64 base_समय, u64 cycle_समय, u64 cycle_समय_ext,
		    u32 num_entries, काष्ठा action_gate_entry *entries);

पूर्णांक sja1105_vl_stats(काष्ठा sja1105_निजी *priv, पूर्णांक port,
		     काष्ठा sja1105_rule *rule, काष्ठा flow_stats *stats,
		     काष्ठा netlink_ext_ack *extack);

#अन्यथा

अटल अंतरभूत पूर्णांक sja1105_vl_redirect(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				      काष्ठा netlink_ext_ack *extack,
				      अचिन्हित दीर्घ cookie,
				      काष्ठा sja1105_key *key,
				      अचिन्हित दीर्घ destports,
				      bool append)
अणु
	NL_SET_ERR_MSG_MOD(extack, "Virtual Links not compiled in");
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक sja1105_vl_delete(काष्ठा sja1105_निजी *priv,
				    पूर्णांक port, काष्ठा sja1105_rule *rule,
				    काष्ठा netlink_ext_ack *extack)
अणु
	NL_SET_ERR_MSG_MOD(extack, "Virtual Links not compiled in");
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक sja1105_vl_gate(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				  काष्ठा netlink_ext_ack *extack,
				  अचिन्हित दीर्घ cookie,
				  काष्ठा sja1105_key *key, u32 index, s32 prio,
				  u64 base_समय, u64 cycle_समय,
				  u64 cycle_समय_ext, u32 num_entries,
				  काष्ठा action_gate_entry *entries)
अणु
	NL_SET_ERR_MSG_MOD(extack, "Virtual Links not compiled in");
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक sja1105_vl_stats(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				   काष्ठा sja1105_rule *rule,
				   काष्ठा flow_stats *stats,
				   काष्ठा netlink_ext_ack *extack)
अणु
	NL_SET_ERR_MSG_MOD(extack, "Virtual Links not compiled in");
	वापस -EOPNOTSUPP;
पूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_NET_DSA_SJA1105_VL) */

#पूर्ण_अगर /* _SJA1105_VL_H */
