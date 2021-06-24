<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (c) 2008, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program; अगर not, ग_लिखो to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 *
 * Author: Alexander Duyck <alexander.h.duyck@पूर्णांकel.com>
 */

#अगर_अघोषित __LINUX_TC_SKBEDIT_H
#घोषणा __LINUX_TC_SKBEDIT_H

#समावेश <linux/pkt_cls.h>

#घोषणा SKBEDIT_F_PRIORITY		0x1
#घोषणा SKBEDIT_F_QUEUE_MAPPING		0x2
#घोषणा SKBEDIT_F_MARK			0x4
#घोषणा SKBEDIT_F_PTYPE			0x8
#घोषणा SKBEDIT_F_MASK			0x10
#घोषणा SKBEDIT_F_INHERITDSFIELD	0x20

काष्ठा tc_skbedit अणु
	tc_gen;
पूर्ण;

क्रमागत अणु
	TCA_SKBEDIT_UNSPEC,
	TCA_SKBEDIT_TM,
	TCA_SKBEDIT_PARMS,
	TCA_SKBEDIT_PRIORITY,
	TCA_SKBEDIT_QUEUE_MAPPING,
	TCA_SKBEDIT_MARK,
	TCA_SKBEDIT_PAD,
	TCA_SKBEDIT_PTYPE,
	TCA_SKBEDIT_MASK,
	TCA_SKBEDIT_FLAGS,
	__TCA_SKBEDIT_MAX
पूर्ण;
#घोषणा TCA_SKBEDIT_MAX (__TCA_SKBEDIT_MAX - 1)

#पूर्ण_अगर
