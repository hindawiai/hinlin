<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_X86_EVENTS_PROBE_H__
#घोषणा __ARCH_X86_EVENTS_PROBE_H__
#समावेश <linux/sysfs.h>

काष्ठा perf_msr अणु
	u64			msr;
	काष्ठा attribute_group	*grp;
	bool			(*test)(पूर्णांक idx, व्योम *data);
	bool			no_check;
	u64			mask;
पूर्ण;

अचिन्हित दीर्घ
perf_msr_probe(काष्ठा perf_msr *msr, पूर्णांक cnt, bool no_zero, व्योम *data);

#घोषणा __PMU_EVENT_GROUP(_name)			\
अटल काष्ठा attribute *attrs_##_name[] = अणु		\
	&attr_##_name.attr.attr,			\
	शून्य,						\
पूर्ण

#घोषणा PMU_EVENT_GROUP(_grp, _name)			\
__PMU_EVENT_GROUP(_name);				\
अटल काष्ठा attribute_group group_##_name = अणु		\
	.name  = #_grp,					\
	.attrs = attrs_##_name,				\
पूर्ण

#पूर्ण_अगर /* __ARCH_X86_EVENTS_PROBE_H__ */
