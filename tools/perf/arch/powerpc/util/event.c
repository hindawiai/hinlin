<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>

#समावेश "../../../util/event.h"
#समावेश "../../../util/synthetic-events.h"
#समावेश "../../../util/machine.h"
#समावेश "../../../util/tool.h"
#समावेश "../../../util/map.h"
#समावेश "../../../util/debug.h"

व्योम arch_perf_parse_sample_weight(काष्ठा perf_sample *data,
				   स्थिर __u64 *array, u64 type)
अणु
	जोड़ perf_sample_weight weight;

	weight.full = *array;
	अगर (type & PERF_SAMPLE_WEIGHT)
		data->weight = weight.full;
	अन्यथा अणु
		data->weight = weight.var1_dw;
		data->ins_lat = weight.var2_w;
		data->p_stage_cyc = weight.var3_w;
	पूर्ण
पूर्ण

व्योम arch_perf_synthesize_sample_weight(स्थिर काष्ठा perf_sample *data,
					__u64 *array, u64 type)
अणु
	*array = data->weight;

	अगर (type & PERF_SAMPLE_WEIGHT_STRUCT) अणु
		*array &= 0xffffffff;
		*array |= ((u64)data->ins_lat << 32);
	पूर्ण
पूर्ण

स्थिर अक्षर *arch_perf_header_entry(स्थिर अक्षर *se_header)
अणु
	अगर (!म_भेद(se_header, "Local INSTR Latency"))
		वापस "Finish Cyc";
	अन्यथा अगर (!म_भेद(se_header, "Pipeline Stage Cycle"))
		वापस "Dispatch Cyc";
	वापस se_header;
पूर्ण

पूर्णांक arch_support_sort_key(स्थिर अक्षर *sort_key)
अणु
	अगर (!म_भेद(sort_key, "p_stage_cyc"))
		वापस 1;
	वापस 0;
पूर्ण
