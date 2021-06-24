<शैली गुरु>
#अगर_अघोषित _ASM_INTEL_DS_H
#घोषणा _ASM_INTEL_DS_H

#समावेश <linux/percpu-defs.h>

#घोषणा BTS_BUFFER_SIZE		(PAGE_SIZE << 4)
#घोषणा PEBS_BUFFER_SIZE	(PAGE_SIZE << 4)

/* The maximal number of PEBS events: */
#घोषणा MAX_PEBS_EVENTS		8
#घोषणा MAX_FIXED_PEBS_EVENTS	4

/*
 * A debug store configuration.
 *
 * We only support architectures that use 64bit fields.
 */
काष्ठा debug_store अणु
	u64	bts_buffer_base;
	u64	bts_index;
	u64	bts_असलolute_maximum;
	u64	bts_पूर्णांकerrupt_threshold;
	u64	pebs_buffer_base;
	u64	pebs_index;
	u64	pebs_असलolute_maximum;
	u64	pebs_पूर्णांकerrupt_threshold;
	u64	pebs_event_reset[MAX_PEBS_EVENTS + MAX_FIXED_PEBS_EVENTS];
पूर्ण __aligned(PAGE_SIZE);

DECLARE_PER_CPU_PAGE_ALIGNED(काष्ठा debug_store, cpu_debug_store);

काष्ठा debug_store_buffers अणु
	अक्षर	bts_buffer[BTS_BUFFER_SIZE];
	अक्षर	pebs_buffer[PEBS_BUFFER_SIZE];
पूर्ण;

#पूर्ण_अगर
