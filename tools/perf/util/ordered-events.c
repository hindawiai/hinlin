<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/list.h>
#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश "ordered-events.h"
#समावेश "session.h"
#समावेश "asm/bug.h"
#समावेश "debug.h"
#समावेश "ui/progress.h"

#घोषणा pr_N(n, fmt, ...) \
	eम_लिखो(n, debug_ordered_events, fmt, ##__VA_ARGS__)

#घोषणा pr(fmt, ...) pr_N(1, pr_fmt(fmt), ##__VA_ARGS__)

अटल व्योम queue_event(काष्ठा ordered_events *oe, काष्ठा ordered_event *new)
अणु
	काष्ठा ordered_event *last = oe->last;
	u64 बारtamp = new->बारtamp;
	काष्ठा list_head *p;

	++oe->nr_events;
	oe->last = new;

	pr_oe_समय2(बारtamp, "queue_event nr_events %u\n", oe->nr_events);

	अगर (!last) अणु
		list_add(&new->list, &oe->events);
		oe->max_बारtamp = बारtamp;
		वापस;
	पूर्ण

	/*
	 * last event might poपूर्णांक to some अक्रमom place in the list as it's
	 * the last queued event. We expect that the new event is बंद to
	 * this.
	 */
	अगर (last->बारtamp <= बारtamp) अणु
		जबतक (last->बारtamp <= बारtamp) अणु
			p = last->list.next;
			अगर (p == &oe->events) अणु
				list_add_tail(&new->list, &oe->events);
				oe->max_बारtamp = बारtamp;
				वापस;
			पूर्ण
			last = list_entry(p, काष्ठा ordered_event, list);
		पूर्ण
		list_add_tail(&new->list, &last->list);
	पूर्ण अन्यथा अणु
		जबतक (last->बारtamp > बारtamp) अणु
			p = last->list.prev;
			अगर (p == &oe->events) अणु
				list_add(&new->list, &oe->events);
				वापस;
			पूर्ण
			last = list_entry(p, काष्ठा ordered_event, list);
		पूर्ण
		list_add(&new->list, &last->list);
	पूर्ण
पूर्ण

अटल जोड़ perf_event *__dup_event(काष्ठा ordered_events *oe,
				     जोड़ perf_event *event)
अणु
	जोड़ perf_event *new_event = शून्य;

	अगर (oe->cur_alloc_size < oe->max_alloc_size) अणु
		new_event = memdup(event, event->header.size);
		अगर (new_event)
			oe->cur_alloc_size += event->header.size;
	पूर्ण

	वापस new_event;
पूर्ण

अटल जोड़ perf_event *dup_event(काष्ठा ordered_events *oe,
				   जोड़ perf_event *event)
अणु
	वापस oe->copy_on_queue ? __dup_event(oe, event) : event;
पूर्ण

अटल व्योम __मुक्त_dup_event(काष्ठा ordered_events *oe, जोड़ perf_event *event)
अणु
	अगर (event) अणु
		oe->cur_alloc_size -= event->header.size;
		मुक्त(event);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_dup_event(काष्ठा ordered_events *oe, जोड़ perf_event *event)
अणु
	अगर (oe->copy_on_queue)
		__मुक्त_dup_event(oe, event);
पूर्ण

#घोषणा MAX_SAMPLE_BUFFER	(64 * 1024 / माप(काष्ठा ordered_event))
अटल काष्ठा ordered_event *alloc_event(काष्ठा ordered_events *oe,
					 जोड़ perf_event *event)
अणु
	काष्ठा list_head *cache = &oe->cache;
	काष्ठा ordered_event *new = शून्य;
	जोड़ perf_event *new_event;
	माप_प्रकार size;

	new_event = dup_event(oe, event);
	अगर (!new_event)
		वापस शून्य;

	/*
	 * We मुख्यtain the following scheme of buffers क्रम ordered
	 * event allocation:
	 *
	 *   to_मुक्त list -> buffer1 (64K)
	 *                   buffer2 (64K)
	 *                   ...
	 *
	 * Each buffer keeps an array of ordered events objects:
	 *    buffer -> event[0]
	 *              event[1]
	 *              ...
	 *
	 * Each allocated ordered event is linked to one of
	 * following lists:
	 *   - समय ordered list 'events'
	 *   - list of currently हटाओd events 'cache'
	 *
	 * Allocation of the ordered event uses the following order
	 * to get the memory:
	 *   - use recently हटाओd object from 'cache' list
	 *   - use available object in current allocation buffer
	 *   - allocate new buffer अगर the current buffer is full
	 *
	 * Removal of ordered event object moves it from events to
	 * the cache list.
	 */
	size = माप(*oe->buffer) + MAX_SAMPLE_BUFFER * माप(*new);

	अगर (!list_empty(cache)) अणु
		new = list_entry(cache->next, काष्ठा ordered_event, list);
		list_del_init(&new->list);
	पूर्ण अन्यथा अगर (oe->buffer) अणु
		new = &oe->buffer->event[oe->buffer_idx];
		अगर (++oe->buffer_idx == MAX_SAMPLE_BUFFER)
			oe->buffer = शून्य;
	पूर्ण अन्यथा अगर ((oe->cur_alloc_size + size) < oe->max_alloc_size) अणु
		oe->buffer = दो_स्मृति(size);
		अगर (!oe->buffer) अणु
			मुक्त_dup_event(oe, new_event);
			वापस शून्य;
		पूर्ण

		pr("alloc size %" PRIu64 "B (+%zu), max %" PRIu64 "B\n",
		   oe->cur_alloc_size, size, oe->max_alloc_size);

		oe->cur_alloc_size += size;
		list_add(&oe->buffer->list, &oe->to_मुक्त);

		oe->buffer_idx = 1;
		new = &oe->buffer->event[0];
	पूर्ण अन्यथा अणु
		pr("allocation limit reached %" PRIu64 "B\n", oe->max_alloc_size);
		वापस शून्य;
	पूर्ण

	new->event = new_event;
	वापस new;
पूर्ण

अटल काष्ठा ordered_event *
ordered_events__new_event(काष्ठा ordered_events *oe, u64 बारtamp,
		    जोड़ perf_event *event)
अणु
	काष्ठा ordered_event *new;

	new = alloc_event(oe, event);
	अगर (new) अणु
		new->बारtamp = बारtamp;
		queue_event(oe, new);
	पूर्ण

	वापस new;
पूर्ण

व्योम ordered_events__delete(काष्ठा ordered_events *oe, काष्ठा ordered_event *event)
अणु
	list_move(&event->list, &oe->cache);
	oe->nr_events--;
	मुक्त_dup_event(oe, event->event);
	event->event = शून्य;
पूर्ण

पूर्णांक ordered_events__queue(काष्ठा ordered_events *oe, जोड़ perf_event *event,
			  u64 बारtamp, u64 file_offset)
अणु
	काष्ठा ordered_event *oevent;

	अगर (!बारtamp || बारtamp == ~0ULL)
		वापस -ETIME;

	अगर (बारtamp < oe->last_flush) अणु
		pr_oe_समय(बारtamp,      "out of order event\n");
		pr_oe_समय(oe->last_flush, "last flush, last_flush_type %d\n",
			   oe->last_flush_type);

		oe->nr_unordered_events++;
	पूर्ण

	oevent = ordered_events__new_event(oe, बारtamp, event);
	अगर (!oevent) अणु
		ordered_events__flush(oe, OE_FLUSH__HALF);
		oevent = ordered_events__new_event(oe, बारtamp, event);
	पूर्ण

	अगर (!oevent)
		वापस -ENOMEM;

	oevent->file_offset = file_offset;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_flush(काष्ठा ordered_events *oe, bool show_progress)
अणु
	काष्ठा list_head *head = &oe->events;
	काष्ठा ordered_event *पंचांगp, *iter;
	u64 limit = oe->next_flush;
	u64 last_ts = oe->last ? oe->last->बारtamp : 0ULL;
	काष्ठा ui_progress prog;
	पूर्णांक ret;

	अगर (!limit)
		वापस 0;

	अगर (show_progress)
		ui_progress__init(&prog, oe->nr_events, "Processing time ordered events...");

	list_क्रम_each_entry_safe(iter, पंचांगp, head, list) अणु
		अगर (session_करोne())
			वापस 0;

		अगर (iter->बारtamp > limit)
			अवरोध;
		ret = oe->deliver(oe, iter);
		अगर (ret)
			वापस ret;

		ordered_events__delete(oe, iter);
		oe->last_flush = iter->बारtamp;

		अगर (show_progress)
			ui_progress__update(&prog, 1);
	पूर्ण

	अगर (list_empty(head))
		oe->last = शून्य;
	अन्यथा अगर (last_ts <= limit)
		oe->last = list_entry(head->prev, काष्ठा ordered_event, list);

	अगर (show_progress)
		ui_progress__finish();

	वापस 0;
पूर्ण

अटल पूर्णांक __ordered_events__flush(काष्ठा ordered_events *oe, क्रमागत oe_flush how,
				   u64 बारtamp)
अणु
	अटल स्थिर अक्षर * स्थिर str[] = अणु
		"NONE",
		"FINAL",
		"ROUND",
		"HALF ",
		"TOP  ",
		"TIME ",
	पूर्ण;
	पूर्णांक err;
	bool show_progress = false;

	अगर (oe->nr_events == 0)
		वापस 0;

	चयन (how) अणु
	हाल OE_FLUSH__FINAL:
		show_progress = true;
		__fallthrough;
	हाल OE_FLUSH__TOP:
		oe->next_flush = ULदीर्घ_उच्च;
		अवरोध;

	हाल OE_FLUSH__HALF:
	अणु
		काष्ठा ordered_event *first, *last;
		काष्ठा list_head *head = &oe->events;

		first = list_entry(head->next, काष्ठा ordered_event, list);
		last = oe->last;

		/* Warn अगर we are called beक्रमe any event got allocated. */
		अगर (WARN_ONCE(!last || list_empty(head), "empty queue"))
			वापस 0;

		oe->next_flush  = first->बारtamp;
		oe->next_flush += (last->बारtamp - first->बारtamp) / 2;
		अवरोध;
	पूर्ण

	हाल OE_FLUSH__TIME:
		oe->next_flush = बारtamp;
		show_progress = false;
		अवरोध;

	हाल OE_FLUSH__ROUND:
	हाल OE_FLUSH__NONE:
	शेष:
		अवरोध;
	पूर्ण

	pr_oe_समय(oe->next_flush, "next_flush - ordered_events__flush PRE  %s, nr_events %u\n",
		   str[how], oe->nr_events);
	pr_oe_समय(oe->max_बारtamp, "max_timestamp\n");

	err = करो_flush(oe, show_progress);

	अगर (!err) अणु
		अगर (how == OE_FLUSH__ROUND)
			oe->next_flush = oe->max_बारtamp;

		oe->last_flush_type = how;
	पूर्ण

	pr_oe_समय(oe->next_flush, "next_flush - ordered_events__flush POST %s, nr_events %u\n",
		   str[how], oe->nr_events);
	pr_oe_समय(oe->last_flush, "last_flush\n");

	वापस err;
पूर्ण

पूर्णांक ordered_events__flush(काष्ठा ordered_events *oe, क्रमागत oe_flush how)
अणु
	वापस __ordered_events__flush(oe, how, 0);
पूर्ण

पूर्णांक ordered_events__flush_समय(काष्ठा ordered_events *oe, u64 बारtamp)
अणु
	वापस __ordered_events__flush(oe, OE_FLUSH__TIME, बारtamp);
पूर्ण

u64 ordered_events__first_समय(काष्ठा ordered_events *oe)
अणु
	काष्ठा ordered_event *event;

	अगर (list_empty(&oe->events))
		वापस 0;

	event = list_first_entry(&oe->events, काष्ठा ordered_event, list);
	वापस event->बारtamp;
पूर्ण

व्योम ordered_events__init(काष्ठा ordered_events *oe, ordered_events__deliver_t deliver,
			  व्योम *data)
अणु
	INIT_LIST_HEAD(&oe->events);
	INIT_LIST_HEAD(&oe->cache);
	INIT_LIST_HEAD(&oe->to_मुक्त);
	oe->max_alloc_size = (u64) -1;
	oe->cur_alloc_size = 0;
	oe->deliver	   = deliver;
	oe->data	   = data;
पूर्ण

अटल व्योम
ordered_events_buffer__मुक्त(काष्ठा ordered_events_buffer *buffer,
			    अचिन्हित पूर्णांक max, काष्ठा ordered_events *oe)
अणु
	अगर (oe->copy_on_queue) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < max; i++)
			__मुक्त_dup_event(oe, buffer->event[i].event);
	पूर्ण

	मुक्त(buffer);
पूर्ण

व्योम ordered_events__मुक्त(काष्ठा ordered_events *oe)
अणु
	काष्ठा ordered_events_buffer *buffer, *पंचांगp;

	अगर (list_empty(&oe->to_मुक्त))
		वापस;

	/*
	 * Current buffer might not have all the events allocated
	 * yet, we need to मुक्त only allocated ones ...
	 */
	अगर (oe->buffer) अणु
		list_del_init(&oe->buffer->list);
		ordered_events_buffer__मुक्त(oe->buffer, oe->buffer_idx, oe);
	पूर्ण

	/* ... and जारी with the rest */
	list_क्रम_each_entry_safe(buffer, पंचांगp, &oe->to_मुक्त, list) अणु
		list_del_init(&buffer->list);
		ordered_events_buffer__मुक्त(buffer, MAX_SAMPLE_BUFFER, oe);
	पूर्ण
पूर्ण

व्योम ordered_events__reinit(काष्ठा ordered_events *oe)
अणु
	ordered_events__deliver_t old_deliver = oe->deliver;

	ordered_events__मुक्त(oe);
	स_रखो(oe, '\0', माप(*oe));
	ordered_events__init(oe, old_deliver, oe->data);
पूर्ण
