<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/* Copyright 2020 NXP */

#अगर_अघोषित __LINUX_TC_GATE_H
#घोषणा __LINUX_TC_GATE_H

#समावेश <linux/pkt_cls.h>

काष्ठा tc_gate अणु
	tc_gen;
पूर्ण;

क्रमागत अणु
	TCA_GATE_ENTRY_UNSPEC,
	TCA_GATE_ENTRY_INDEX,
	TCA_GATE_ENTRY_GATE,
	TCA_GATE_ENTRY_INTERVAL,
	TCA_GATE_ENTRY_IPV,
	TCA_GATE_ENTRY_MAX_OCTETS,
	__TCA_GATE_ENTRY_MAX,
पूर्ण;
#घोषणा TCA_GATE_ENTRY_MAX (__TCA_GATE_ENTRY_MAX - 1)

क्रमागत अणु
	TCA_GATE_ONE_ENTRY_UNSPEC,
	TCA_GATE_ONE_ENTRY,
	__TCA_GATE_ONE_ENTRY_MAX,
पूर्ण;
#घोषणा TCA_GATE_ONE_ENTRY_MAX (__TCA_GATE_ONE_ENTRY_MAX - 1)

क्रमागत अणु
	TCA_GATE_UNSPEC,
	TCA_GATE_TM,
	TCA_GATE_PARMS,
	TCA_GATE_PAD,
	TCA_GATE_PRIORITY,
	TCA_GATE_ENTRY_LIST,
	TCA_GATE_BASE_TIME,
	TCA_GATE_CYCLE_TIME,
	TCA_GATE_CYCLE_TIME_EXT,
	TCA_GATE_FLAGS,
	TCA_GATE_CLOCKID,
	__TCA_GATE_MAX,
पूर्ण;
#घोषणा TCA_GATE_MAX (__TCA_GATE_MAX - 1)

#पूर्ण_अगर
