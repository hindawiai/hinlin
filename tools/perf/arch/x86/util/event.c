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

#अगर defined(__x86_64__)

पूर्णांक perf_event__synthesize_extra_kmaps(काष्ठा perf_tool *tool,
				       perf_event__handler_t process,
				       काष्ठा machine *machine)
अणु
	पूर्णांक rc = 0;
	काष्ठा map *pos;
	काष्ठा maps *kmaps = &machine->kmaps;
	जोड़ perf_event *event = zalloc(माप(event->mmap) +
					 machine->id_hdr_size);

	अगर (!event) अणु
		pr_debug("Not enough memory synthesizing mmap event "
			 "for extra kernel maps\n");
		वापस -1;
	पूर्ण

	maps__क्रम_each_entry(kmaps, pos) अणु
		काष्ठा kmap *kmap;
		माप_प्रकार size;

		अगर (!__map__is_extra_kernel_map(pos))
			जारी;

		kmap = map__kmap(pos);

		size = माप(event->mmap) - माप(event->mmap.filename) +
		       PERF_ALIGN(म_माप(kmap->name) + 1, माप(u64)) +
		       machine->id_hdr_size;

		स_रखो(event, 0, size);

		event->mmap.header.type = PERF_RECORD_MMAP;

		/*
		 * kernel uses 0 क्रम user space maps, see kernel/perf_event.c
		 * __perf_event_mmap
		 */
		अगर (machine__is_host(machine))
			event->header.misc = PERF_RECORD_MISC_KERNEL;
		अन्यथा
			event->header.misc = PERF_RECORD_MISC_GUEST_KERNEL;

		event->mmap.header.size = size;

		event->mmap.start = pos->start;
		event->mmap.len   = pos->end - pos->start;
		event->mmap.pgoff = pos->pgoff;
		event->mmap.pid   = machine->pid;

		strlcpy(event->mmap.filename, kmap->name, PATH_MAX);

		अगर (perf_tool__process_synth_event(tool, event, machine,
						   process) != 0) अणु
			rc = -1;
			अवरोध;
		पूर्ण
	पूर्ण

	मुक्त(event);
	वापस rc;
पूर्ण

#पूर्ण_अगर

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
