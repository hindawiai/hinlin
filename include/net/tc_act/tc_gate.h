<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Copyright 2020 NXP */

#अगर_अघोषित __NET_TC_GATE_H
#घोषणा __NET_TC_GATE_H

#समावेश <net/act_api.h>
#समावेश <linux/tc_act/tc_gate.h>

काष्ठा action_gate_entry अणु
	u8			gate_state;
	u32			पूर्णांकerval;
	s32			ipv;
	s32			maxoctets;
पूर्ण;

काष्ठा tcfg_gate_entry अणु
	पूर्णांक			index;
	u8			gate_state;
	u32			पूर्णांकerval;
	s32			ipv;
	s32			maxoctets;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा tcf_gate_params अणु
	s32			tcfg_priority;
	u64			tcfg_baseसमय;
	u64			tcfg_cycleसमय;
	u64			tcfg_cycleसमय_ext;
	u32			tcfg_flags;
	s32			tcfg_घड़ीid;
	माप_प्रकार			num_entries;
	काष्ठा list_head	entries;
पूर्ण;

#घोषणा GATE_ACT_GATE_OPEN	BIT(0)
#घोषणा GATE_ACT_PENDING	BIT(1)

काष्ठा tcf_gate अणु
	काष्ठा tc_action	common;
	काष्ठा tcf_gate_params	param;
	u8			current_gate_status;
	kसमय_प्रकार			current_बंद_समय;
	u32			current_entry_octets;
	s32			current_max_octets;
	काष्ठा tcfg_gate_entry	*next_entry;
	काष्ठा hrसमयr		hiसमयr;
	क्रमागत tk_offsets		tk_offset;
पूर्ण;

#घोषणा to_gate(a) ((काष्ठा tcf_gate *)a)

अटल अंतरभूत bool is_tcf_gate(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (a->ops && a->ops->id == TCA_ID_GATE)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत u32 tcf_gate_index(स्थिर काष्ठा tc_action *a)
अणु
	वापस a->tcfa_index;
पूर्ण

अटल अंतरभूत s32 tcf_gate_prio(स्थिर काष्ठा tc_action *a)
अणु
	s32 tcfg_prio;

	tcfg_prio = to_gate(a)->param.tcfg_priority;

	वापस tcfg_prio;
पूर्ण

अटल अंतरभूत u64 tcf_gate_baseसमय(स्थिर काष्ठा tc_action *a)
अणु
	u64 tcfg_baseसमय;

	tcfg_baseसमय = to_gate(a)->param.tcfg_baseसमय;

	वापस tcfg_baseसमय;
पूर्ण

अटल अंतरभूत u64 tcf_gate_cycleसमय(स्थिर काष्ठा tc_action *a)
अणु
	u64 tcfg_cycleसमय;

	tcfg_cycleसमय = to_gate(a)->param.tcfg_cycleसमय;

	वापस tcfg_cycleसमय;
पूर्ण

अटल अंतरभूत u64 tcf_gate_cycleसमयext(स्थिर काष्ठा tc_action *a)
अणु
	u64 tcfg_cycleसमयext;

	tcfg_cycleसमयext = to_gate(a)->param.tcfg_cycleसमय_ext;

	वापस tcfg_cycleसमयext;
पूर्ण

अटल अंतरभूत u32 tcf_gate_num_entries(स्थिर काष्ठा tc_action *a)
अणु
	u32 num_entries;

	num_entries = to_gate(a)->param.num_entries;

	वापस num_entries;
पूर्ण

अटल अंतरभूत काष्ठा action_gate_entry
			*tcf_gate_get_list(स्थिर काष्ठा tc_action *a)
अणु
	काष्ठा action_gate_entry *oe;
	काष्ठा tcf_gate_params *p;
	काष्ठा tcfg_gate_entry *entry;
	u32 num_entries;
	पूर्णांक i = 0;

	p = &to_gate(a)->param;
	num_entries = p->num_entries;

	list_क्रम_each_entry(entry, &p->entries, list)
		i++;

	अगर (i != num_entries)
		वापस शून्य;

	oe = kसुस्मृति(num_entries, माप(*oe), GFP_ATOMIC);
	अगर (!oe)
		वापस शून्य;

	i = 0;
	list_क्रम_each_entry(entry, &p->entries, list) अणु
		oe[i].gate_state = entry->gate_state;
		oe[i].पूर्णांकerval = entry->पूर्णांकerval;
		oe[i].ipv = entry->ipv;
		oe[i].maxoctets = entry->maxoctets;
		i++;
	पूर्ण

	वापस oe;
पूर्ण
#पूर्ण_अगर
