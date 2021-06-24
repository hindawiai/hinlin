<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_POWERPC_PERF_HV_COMMON_H_
#घोषणा LINUX_POWERPC_PERF_HV_COMMON_H_

#समावेश <linux/perf_event.h>
#समावेश <linux/types.h>

काष्ठा hv_perf_caps अणु
	u16 version;
	u16 collect_privileged:1,
	    ga:1,
	    expanded:1,
	    lab:1,
	    unused:12;
पूर्ण;

अचिन्हित दीर्घ hv_perf_caps_get(काष्ठा hv_perf_caps *caps);


#घोषणा EVENT_DEFINE_RANGE_FORMAT(name, attr_var, bit_start, bit_end)	\
PMU_FORMAT_ATTR(name, #attr_var ":" #bit_start "-" #bit_end);		\
EVENT_DEFINE_RANGE(name, attr_var, bit_start, bit_end)

/*
 * The EVENT_DEFINE_RANGE_FORMAT() macro above includes helper functions
 * क्रम the fields (eg: event_get_starting_index()). For some fields we
 * need the bit-range definition, but no the helper functions. Define a
 * lite version of the above macro without the helpers and silence
 * compiler warnings unused अटल functions.
 */
#घोषणा EVENT_DEFINE_RANGE_FORMAT_LITE(name, attr_var, bit_start, bit_end) \
PMU_FORMAT_ATTR(name, #attr_var ":" #bit_start "-" #bit_end);

#घोषणा EVENT_DEFINE_RANGE(name, attr_var, bit_start, bit_end)	\
अटल u64 event_get_##name##_max(व्योम)					\
अणु									\
	BUILD_BUG_ON((bit_start > bit_end)				\
		    || (bit_end >= (माप(1ull) * 8)));		\
	वापस (((1ull << (bit_end - bit_start)) - 1) << 1) + 1;	\
पूर्ण									\
अटल u64 event_get_##name(काष्ठा perf_event *event)			\
अणु									\
	वापस (event->attr.attr_var >> (bit_start)) &			\
		event_get_##name##_max();				\
पूर्ण

#पूर्ण_अगर
