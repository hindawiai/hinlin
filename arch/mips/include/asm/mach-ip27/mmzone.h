<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_MACH_MMZONE_H
#घोषणा _ASM_MACH_MMZONE_H

#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/arch.h>
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/sn/klkernvars.h>

#घोषणा pa_to_nid(addr)		NASID_GET(addr)

काष्ठा hub_data अणु
	kern_vars_t	kern_vars;
	DECLARE_BITMAP(h_bigwin_used, HUB_NUM_BIG_WINDOW);
	cpumask_t	h_cpus;
पूर्ण;

काष्ठा node_data अणु
	काष्ठा pglist_data pglist;
	काष्ठा hub_data hub;
पूर्ण;

बाह्य काष्ठा node_data *__node_data[];

#घोषणा NODE_DATA(n)		(&__node_data[(n)]->pglist)
#घोषणा hub_data(n)		(&__node_data[(n)]->hub)

#पूर्ण_अगर /* _ASM_MACH_MMZONE_H */
