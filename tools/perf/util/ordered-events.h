<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ORDERED_EVENTS_H
#घोषणा __ORDERED_EVENTS_H

#समावेश <linux/types.h>

काष्ठा perf_sample;

काष्ठा ordered_event अणु
	u64			बारtamp;
	u64			file_offset;
	जोड़ perf_event	*event;
	काष्ठा list_head	list;
पूर्ण;

क्रमागत oe_flush अणु
	OE_FLUSH__NONE,
	OE_FLUSH__FINAL,
	OE_FLUSH__ROUND,
	OE_FLUSH__HALF,
	OE_FLUSH__TOP,
	OE_FLUSH__TIME,
पूर्ण;

काष्ठा ordered_events;

प्रकार पूर्णांक (*ordered_events__deliver_t)(काष्ठा ordered_events *oe,
					 काष्ठा ordered_event *event);

काष्ठा ordered_events_buffer अणु
	काष्ठा list_head	list;
	काष्ठा ordered_event	event[];
पूर्ण;

काष्ठा ordered_events अणु
	u64				 last_flush;
	u64				 next_flush;
	u64				 max_बारtamp;
	u64				 max_alloc_size;
	u64				 cur_alloc_size;
	काष्ठा list_head		 events;
	काष्ठा list_head		 cache;
	काष्ठा list_head		 to_मुक्त;
	काष्ठा ordered_events_buffer	*buffer;
	काष्ठा ordered_event		*last;
	ordered_events__deliver_t	 deliver;
	पूर्णांक				 buffer_idx;
	अचिन्हित पूर्णांक			 nr_events;
	क्रमागत oe_flush			 last_flush_type;
	u32				 nr_unordered_events;
	bool				 copy_on_queue;
	व्योम				*data;
पूर्ण;

पूर्णांक ordered_events__queue(काष्ठा ordered_events *oe, जोड़ perf_event *event,
			  u64 बारtamp, u64 file_offset);
व्योम ordered_events__delete(काष्ठा ordered_events *oe, काष्ठा ordered_event *event);
पूर्णांक ordered_events__flush(काष्ठा ordered_events *oe, क्रमागत oe_flush how);
पूर्णांक ordered_events__flush_समय(काष्ठा ordered_events *oe, u64 बारtamp);
व्योम ordered_events__init(काष्ठा ordered_events *oe, ordered_events__deliver_t deliver,
			  व्योम *data);
व्योम ordered_events__मुक्त(काष्ठा ordered_events *oe);
व्योम ordered_events__reinit(काष्ठा ordered_events *oe);
u64 ordered_events__first_समय(काष्ठा ordered_events *oe);

अटल अंतरभूत
व्योम ordered_events__set_alloc_size(काष्ठा ordered_events *oe, u64 size)
अणु
	oe->max_alloc_size = size;
पूर्ण

अटल अंतरभूत
व्योम ordered_events__set_copy_on_queue(काष्ठा ordered_events *oe, bool copy)
अणु
	oe->copy_on_queue = copy;
पूर्ण
#पूर्ण_अगर /* __ORDERED_EVENTS_H */
