<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * This file has definitions क्रम the hub and snac पूर्णांकerfaces.
 *
 * Copyright (C) 1992 - 1997, 1999, 2000 Silcon Graphics, Inc.
 * Copyright (C) 1999, 2000 Ralf Baechle (ralf@gnu.org)
 */
#अगर_अघोषित _ASM_SGI_SN_AGENT_H
#घोषणा _ASM_SGI_SN_AGENT_H

#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/arch.h>

#अगर defined(CONFIG_SGI_IP27)
#समावेश <यंत्र/sn/sn0/hub.h>
#या_अगर defined(CONFIG_SGI_IP35)
#समावेश <यंत्र/sn/sn1/hub.h>
#पूर्ण_अगर	/* !CONFIG_SGI_IP27 && !CONFIG_SGI_IP35 */

/*
 * NIC रेजिस्टर macros
 */

#अगर defined(CONFIG_SGI_IP27)
#घोषणा HUB_NIC_ADDR(_cpuid)						   \
	REMOTE_HUB_ADDR(cpu_to_node(_cpuid),				   \
		MD_MLAN_CTL)
#पूर्ण_अगर

#घोषणा SET_HUB_NIC(_my_cpuid, _val)					   \
	(HUB_S(HUB_NIC_ADDR(_my_cpuid), (_val)))

#घोषणा SET_MY_HUB_NIC(_v)						   \
	SET_HUB_NIC(cpuid(), (_v))

#घोषणा GET_HUB_NIC(_my_cpuid)						   \
	(HUB_L(HUB_NIC_ADDR(_my_cpuid)))

#घोषणा GET_MY_HUB_NIC()						   \
	GET_HUB_NIC(cpuid())

#पूर्ण_अगर /* _ASM_SGI_SN_AGENT_H */
