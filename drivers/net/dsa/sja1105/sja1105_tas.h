<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Vladimir Oltean <olteanv@gmail.com>
 */
#अगर_अघोषित _SJA1105_TAS_H
#घोषणा _SJA1105_TAS_H

#समावेश <net/pkt_sched.h>

#घोषणा SJA1105_TAS_MAX_DELTA		BIT(18)

काष्ठा sja1105_निजी;

#अगर IS_ENABLED(CONFIG_NET_DSA_SJA1105_TAS)

क्रमागत sja1105_tas_state अणु
	SJA1105_TAS_STATE_DISABLED,
	SJA1105_TAS_STATE_ENABLED_NOT_RUNNING,
	SJA1105_TAS_STATE_RUNNING,
पूर्ण;

क्रमागत sja1105_ptp_op अणु
	SJA1105_PTP_NONE,
	SJA1105_PTP_CLOCKSTEP,
	SJA1105_PTP_ADJUSTFREQ,
पूर्ण;

काष्ठा sja1105_gate_entry अणु
	काष्ठा list_head list;
	काष्ठा sja1105_rule *rule;
	s64 पूर्णांकerval;
	u8 gate_state;
पूर्ण;

काष्ठा sja1105_gating_config अणु
	u64 cycle_समय;
	s64 base_समय;
	पूर्णांक num_entries;
	काष्ठा list_head entries;
पूर्ण;

काष्ठा sja1105_tas_data अणु
	काष्ठा tc_taprio_qopt_offload *offload[SJA1105_NUM_PORTS];
	काष्ठा sja1105_gating_config gating_cfg;
	क्रमागत sja1105_tas_state state;
	क्रमागत sja1105_ptp_op last_op;
	काष्ठा work_काष्ठा tas_work;
	s64 earliest_base_समय;
	s64 oper_base_समय;
	u64 max_cycle_समय;
	bool enabled;
पूर्ण;

पूर्णांक sja1105_setup_tc_taprio(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    काष्ठा tc_taprio_qopt_offload *admin);

व्योम sja1105_tas_setup(काष्ठा dsa_चयन *ds);

व्योम sja1105_tas_tearकरोwn(काष्ठा dsa_चयन *ds);

व्योम sja1105_tas_घड़ीstep(काष्ठा dsa_चयन *ds);

व्योम sja1105_tas_adjfreq(काष्ठा dsa_चयन *ds);

bool sja1105_gating_check_conflicts(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				    काष्ठा netlink_ext_ack *extack);

पूर्णांक sja1105_init_scheduling(काष्ठा sja1105_निजी *priv);

#अन्यथा

/* C करोesn't allow empty काष्ठाures, bah! */
काष्ठा sja1105_tas_data अणु
	u8 dummy;
पूर्ण;

अटल अंतरभूत पूर्णांक sja1105_setup_tc_taprio(काष्ठा dsa_चयन *ds, पूर्णांक port,
					  काष्ठा tc_taprio_qopt_offload *admin)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम sja1105_tas_setup(काष्ठा dsa_चयन *ds) अणु पूर्ण

अटल अंतरभूत व्योम sja1105_tas_tearकरोwn(काष्ठा dsa_चयन *ds) अणु पूर्ण

अटल अंतरभूत व्योम sja1105_tas_घड़ीstep(काष्ठा dsa_चयन *ds) अणु पूर्ण

अटल अंतरभूत व्योम sja1105_tas_adjfreq(काष्ठा dsa_चयन *ds) अणु पूर्ण

अटल अंतरभूत bool
sja1105_gating_check_conflicts(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा netlink_ext_ack *extack)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक sja1105_init_scheduling(काष्ठा sja1105_निजी *priv)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_NET_DSA_SJA1105_TAS) */

#पूर्ण_अगर /* _SJA1105_TAS_H */
