<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright (c) 2014 Jiri Pirko <jiri@resnulli.us>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#अगर_अघोषित __LINUX_TC_VLAN_H
#घोषणा __LINUX_TC_VLAN_H

#समावेश <linux/pkt_cls.h>

#घोषणा TCA_VLAN_ACT_POP	1
#घोषणा TCA_VLAN_ACT_PUSH	2
#घोषणा TCA_VLAN_ACT_MODIFY	3
#घोषणा TCA_VLAN_ACT_POP_ETH	4
#घोषणा TCA_VLAN_ACT_PUSH_ETH	5

काष्ठा tc_vlan अणु
	tc_gen;
	पूर्णांक v_action;
पूर्ण;

क्रमागत अणु
	TCA_VLAN_UNSPEC,
	TCA_VLAN_TM,
	TCA_VLAN_PARMS,
	TCA_VLAN_PUSH_VLAN_ID,
	TCA_VLAN_PUSH_VLAN_PROTOCOL,
	TCA_VLAN_PAD,
	TCA_VLAN_PUSH_VLAN_PRIORITY,
	TCA_VLAN_PUSH_ETH_DST,
	TCA_VLAN_PUSH_ETH_SRC,
	__TCA_VLAN_MAX,
पूर्ण;
#घोषणा TCA_VLAN_MAX (__TCA_VLAN_MAX - 1)

#पूर्ण_अगर
