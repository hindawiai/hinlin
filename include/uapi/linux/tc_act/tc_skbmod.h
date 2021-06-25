<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright (c) 2016, Jamal Hadi Salim
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
*/

#अगर_अघोषित __LINUX_TC_SKBMOD_H
#घोषणा __LINUX_TC_SKBMOD_H

#समावेश <linux/pkt_cls.h>

#घोषणा SKBMOD_F_DMAC	0x1
#घोषणा SKBMOD_F_SMAC	0x2
#घोषणा SKBMOD_F_ETYPE	0x4
#घोषणा SKBMOD_F_SWAPMAC 0x8

काष्ठा tc_skbmod अणु
	tc_gen;
	__u64 flags;
पूर्ण;

क्रमागत अणु
	TCA_SKBMOD_UNSPEC,
	TCA_SKBMOD_TM,
	TCA_SKBMOD_PARMS,
	TCA_SKBMOD_DMAC,
	TCA_SKBMOD_SMAC,
	TCA_SKBMOD_ETYPE,
	TCA_SKBMOD_PAD,
	__TCA_SKBMOD_MAX
पूर्ण;
#घोषणा TCA_SKBMOD_MAX (__TCA_SKBMOD_MAX - 1)

#पूर्ण_अगर
