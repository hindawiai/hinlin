<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ring buffer tester and benchmark
 *
 * Copyright (C) 2009 Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <linux/ring_buffer.h>
#समावेश <linux/completion.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kसमय.स>
#समावेश <यंत्र/local.h>

काष्ठा rb_page अणु
	u64		ts;
	local_t		commit;
	अक्षर		data[4080];
पूर्ण;

/* run समय and sleep समय in seconds */
#घोषणा RUN_TIME	10ULL
#घोषणा SLEEP_TIME	10

/* number of events क्रम ग_लिखोr to wake up the पढ़ोer */
अटल पूर्णांक wakeup_पूर्णांकerval = 100;

अटल पूर्णांक पढ़ोer_finish;
अटल DECLARE_COMPLETION(पढ़ो_start);
अटल DECLARE_COMPLETION(पढ़ो_करोne);

अटल काष्ठा trace_buffer *buffer;
अटल काष्ठा task_काष्ठा *producer;
अटल काष्ठा task_काष्ठा *consumer;
अटल अचिन्हित दीर्घ पढ़ो;

अटल अचिन्हित पूर्णांक disable_पढ़ोer;
module_param(disable_पढ़ोer, uपूर्णांक, 0644);
MODULE_PARM_DESC(disable_पढ़ोer, "only run producer");

अटल अचिन्हित पूर्णांक ग_लिखो_iteration = 50;
module_param(ग_लिखो_iteration, uपूर्णांक, 0644);
MODULE_PARM_DESC(ग_लिखो_iteration, "# of writes between timestamp readings");

अटल पूर्णांक producer_nice = MAX_NICE;
अटल पूर्णांक consumer_nice = MAX_NICE;

अटल पूर्णांक producer_fअगरo;
अटल पूर्णांक consumer_fअगरo;

module_param(producer_nice, पूर्णांक, 0644);
MODULE_PARM_DESC(producer_nice, "nice prio for producer");

module_param(consumer_nice, पूर्णांक, 0644);
MODULE_PARM_DESC(consumer_nice, "nice prio for consumer");

module_param(producer_fअगरo, पूर्णांक, 0644);
MODULE_PARM_DESC(producer_fअगरo, "use fifo for producer: 0 - disabled, 1 - low prio, 2 - fifo");

module_param(consumer_fअगरo, पूर्णांक, 0644);
MODULE_PARM_DESC(consumer_fअगरo, "use fifo for consumer: 0 - disabled, 1 - low prio, 2 - fifo");

अटल पूर्णांक पढ़ो_events;

अटल पूर्णांक test_error;

#घोषणा TEST_ERROR()				\
	करो अणु					\
		अगर (!test_error) अणु		\
			test_error = 1;		\
			WARN_ON(1);		\
		पूर्ण				\
	पूर्ण जबतक (0)

क्रमागत event_status अणु
	EVENT_FOUND,
	EVENT_DROPPED,
पूर्ण;

अटल bool अवरोध_test(व्योम)
अणु
	वापस test_error || kthपढ़ो_should_stop();
पूर्ण

अटल क्रमागत event_status पढ़ो_event(पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_event *event;
	पूर्णांक *entry;
	u64 ts;

	event = ring_buffer_consume(buffer, cpu, &ts, शून्य);
	अगर (!event)
		वापस EVENT_DROPPED;

	entry = ring_buffer_event_data(event);
	अगर (*entry != cpu) अणु
		TEST_ERROR();
		वापस EVENT_DROPPED;
	पूर्ण

	पढ़ो++;
	वापस EVENT_FOUND;
पूर्ण

अटल क्रमागत event_status पढ़ो_page(पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा rb_page *rpage;
	अचिन्हित दीर्घ commit;
	व्योम *bpage;
	पूर्णांक *entry;
	पूर्णांक ret;
	पूर्णांक inc;
	पूर्णांक i;

	bpage = ring_buffer_alloc_पढ़ो_page(buffer, cpu);
	अगर (IS_ERR(bpage))
		वापस EVENT_DROPPED;

	ret = ring_buffer_पढ़ो_page(buffer, &bpage, PAGE_SIZE, cpu, 1);
	अगर (ret >= 0) अणु
		rpage = bpage;
		/* The commit may have missed event flags set, clear them */
		commit = local_पढ़ो(&rpage->commit) & 0xfffff;
		क्रम (i = 0; i < commit && !test_error ; i += inc) अणु

			अगर (i >= (PAGE_SIZE - दुरत्व(काष्ठा rb_page, data))) अणु
				TEST_ERROR();
				अवरोध;
			पूर्ण

			inc = -1;
			event = (व्योम *)&rpage->data[i];
			चयन (event->type_len) अणु
			हाल RINGBUF_TYPE_PADDING:
				/* failed ग_लिखोs may be discarded events */
				अगर (!event->समय_delta)
					TEST_ERROR();
				inc = event->array[0] + 4;
				अवरोध;
			हाल RINGBUF_TYPE_TIME_EXTEND:
				inc = 8;
				अवरोध;
			हाल 0:
				entry = ring_buffer_event_data(event);
				अगर (*entry != cpu) अणु
					TEST_ERROR();
					अवरोध;
				पूर्ण
				पढ़ो++;
				अगर (!event->array[0]) अणु
					TEST_ERROR();
					अवरोध;
				पूर्ण
				inc = event->array[0] + 4;
				अवरोध;
			शेष:
				entry = ring_buffer_event_data(event);
				अगर (*entry != cpu) अणु
					TEST_ERROR();
					अवरोध;
				पूर्ण
				पढ़ो++;
				inc = ((event->type_len + 1) * 4);
			पूर्ण
			अगर (test_error)
				अवरोध;

			अगर (inc <= 0) अणु
				TEST_ERROR();
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	ring_buffer_मुक्त_पढ़ो_page(buffer, cpu, bpage);

	अगर (ret < 0)
		वापस EVENT_DROPPED;
	वापस EVENT_FOUND;
पूर्ण

अटल व्योम ring_buffer_consumer(व्योम)
अणु
	/* toggle between पढ़ोing pages and events */
	पढ़ो_events ^= 1;

	पढ़ो = 0;
	/*
	 * Continue running until the producer specअगरically asks to stop
	 * and is पढ़ोy क्रम the completion.
	 */
	जबतक (!READ_ONCE(पढ़ोer_finish)) अणु
		पूर्णांक found = 1;

		जबतक (found && !test_error) अणु
			पूर्णांक cpu;

			found = 0;
			क्रम_each_online_cpu(cpu) अणु
				क्रमागत event_status stat;

				अगर (पढ़ो_events)
					stat = पढ़ो_event(cpu);
				अन्यथा
					stat = पढ़ो_page(cpu);

				अगर (test_error)
					अवरोध;

				अगर (stat == EVENT_FOUND)
					found = 1;

			पूर्ण
		पूर्ण

		/* Wait till the producer wakes us up when there is more data
		 * available or when the producer wants us to finish पढ़ोing.
		 */
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (पढ़ोer_finish)
			अवरोध;

		schedule();
	पूर्ण
	__set_current_state(TASK_RUNNING);
	पढ़ोer_finish = 0;
	complete(&पढ़ो_करोne);
पूर्ण

अटल व्योम ring_buffer_producer(व्योम)
अणु
	kसमय_प्रकार start_समय, end_समय, समयout;
	अचिन्हित दीर्घ दीर्घ समय;
	अचिन्हित दीर्घ दीर्घ entries;
	अचिन्हित दीर्घ दीर्घ overruns;
	अचिन्हित दीर्घ missed = 0;
	अचिन्हित दीर्घ hit = 0;
	अचिन्हित दीर्घ avg;
	पूर्णांक cnt = 0;

	/*
	 * Hammer the buffer क्रम 10 secs (this may
	 * make the प्रणाली stall)
	 */
	trace_prपूर्णांकk("Starting ring buffer hammer\n");
	start_समय = kसमय_get();
	समयout = kसमय_add_ns(start_समय, RUN_TIME * NSEC_PER_SEC);
	करो अणु
		काष्ठा ring_buffer_event *event;
		पूर्णांक *entry;
		पूर्णांक i;

		क्रम (i = 0; i < ग_लिखो_iteration; i++) अणु
			event = ring_buffer_lock_reserve(buffer, 10);
			अगर (!event) अणु
				missed++;
			पूर्ण अन्यथा अणु
				hit++;
				entry = ring_buffer_event_data(event);
				*entry = smp_processor_id();
				ring_buffer_unlock_commit(buffer, event);
			पूर्ण
		पूर्ण
		end_समय = kसमय_get();

		cnt++;
		अगर (consumer && !(cnt % wakeup_पूर्णांकerval))
			wake_up_process(consumer);

#अगर_अघोषित CONFIG_PREEMPTION
		/*
		 * If we are a non preempt kernel, the 10 seconds run will
		 * stop everything जबतक it runs. Instead, we will call
		 * cond_resched and also add any समय that was lost by a
		 * reschedule.
		 *
		 * Do a cond resched at the same frequency we would wake up
		 * the पढ़ोer.
		 */
		अगर (cnt % wakeup_पूर्णांकerval)
			cond_resched();
#पूर्ण_अगर
	पूर्ण जबतक (kसमय_beक्रमe(end_समय, समयout) && !अवरोध_test());
	trace_prपूर्णांकk("End ring buffer hammer\n");

	अगर (consumer) अणु
		/* Init both completions here to aव्योम races */
		init_completion(&पढ़ो_start);
		init_completion(&पढ़ो_करोne);
		/* the completions must be visible beक्रमe the finish var */
		smp_wmb();
		पढ़ोer_finish = 1;
		wake_up_process(consumer);
		रुको_क्रम_completion(&पढ़ो_करोne);
	पूर्ण

	समय = kसमय_us_delta(end_समय, start_समय);

	entries = ring_buffer_entries(buffer);
	overruns = ring_buffer_overruns(buffer);

	अगर (test_error)
		trace_prपूर्णांकk("ERROR!\n");

	अगर (!disable_पढ़ोer) अणु
		अगर (consumer_fअगरo)
			trace_prपूर्णांकk("Running Consumer at SCHED_FIFO %s\n",
				     consumer_fअगरo == 1 ? "low" : "high");
		अन्यथा
			trace_prपूर्णांकk("Running Consumer at nice: %d\n",
				     consumer_nice);
	पूर्ण
	अगर (producer_fअगरo)
		trace_prपूर्णांकk("Running Producer at SCHED_FIFO %s\n",
			     producer_fअगरo == 1 ? "low" : "high");
	अन्यथा
		trace_prपूर्णांकk("Running Producer at nice: %d\n",
			     producer_nice);

	/* Let the user know that the test is running at low priority */
	अगर (!producer_fअगरo && !consumer_fअगरo &&
	    producer_nice == MAX_NICE && consumer_nice == MAX_NICE)
		trace_prपूर्णांकk("WARNING!!! This test is running at lowest priority.\n");

	trace_prपूर्णांकk("Time:     %lld (usecs)\n", समय);
	trace_prपूर्णांकk("Overruns: %lld\n", overruns);
	अगर (disable_पढ़ोer)
		trace_prपूर्णांकk("Read:     (reader disabled)\n");
	अन्यथा
		trace_prपूर्णांकk("Read:     %ld  (by %s)\n", पढ़ो,
			पढ़ो_events ? "events" : "pages");
	trace_prपूर्णांकk("Entries:  %lld\n", entries);
	trace_prपूर्णांकk("Total:    %lld\n", entries + overruns + पढ़ो);
	trace_prपूर्णांकk("Missed:   %ld\n", missed);
	trace_prपूर्णांकk("Hit:      %ld\n", hit);

	/* Convert समय from usecs to millisecs */
	करो_भाग(समय, USEC_PER_MSEC);
	अगर (समय)
		hit /= (दीर्घ)समय;
	अन्यथा
		trace_prपूर्णांकk("TIME IS ZERO??\n");

	trace_prपूर्णांकk("Entries per millisec: %ld\n", hit);

	अगर (hit) अणु
		/* Calculate the average समय in nanosecs */
		avg = NSEC_PER_MSEC / hit;
		trace_prपूर्णांकk("%ld ns per entry\n", avg);
	पूर्ण

	अगर (missed) अणु
		अगर (समय)
			missed /= (दीर्घ)समय;

		trace_prपूर्णांकk("Total iterations per millisec: %ld\n",
			     hit + missed);

		/* it is possible that hit + missed will overflow and be zero */
		अगर (!(hit + missed)) अणु
			trace_prपूर्णांकk("hit + missed overflowed and totalled zero!\n");
			hit--; /* make it non zero */
		पूर्ण

		/* Calculate the average समय in nanosecs */
		avg = NSEC_PER_MSEC / (hit + missed);
		trace_prपूर्णांकk("%ld ns per entry\n", avg);
	पूर्ण
पूर्ण

अटल व्योम रुको_to_die(व्योम)
अणु
	set_current_state(TASK_INTERRUPTIBLE);
	जबतक (!kthपढ़ो_should_stop()) अणु
		schedule();
		set_current_state(TASK_INTERRUPTIBLE);
	पूर्ण
	__set_current_state(TASK_RUNNING);
पूर्ण

अटल पूर्णांक ring_buffer_consumer_thपढ़ो(व्योम *arg)
अणु
	जबतक (!अवरोध_test()) अणु
		complete(&पढ़ो_start);

		ring_buffer_consumer();

		set_current_state(TASK_INTERRUPTIBLE);
		अगर (अवरोध_test())
			अवरोध;
		schedule();
	पूर्ण
	__set_current_state(TASK_RUNNING);

	अगर (!kthपढ़ो_should_stop())
		रुको_to_die();

	वापस 0;
पूर्ण

अटल पूर्णांक ring_buffer_producer_thपढ़ो(व्योम *arg)
अणु
	जबतक (!अवरोध_test()) अणु
		ring_buffer_reset(buffer);

		अगर (consumer) अणु
			wake_up_process(consumer);
			रुको_क्रम_completion(&पढ़ो_start);
		पूर्ण

		ring_buffer_producer();
		अगर (अवरोध_test())
			जाओ out_समाप्त;

		trace_prपूर्णांकk("Sleeping for 10 secs\n");
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (अवरोध_test())
			जाओ out_समाप्त;
		schedule_समयout(HZ * SLEEP_TIME);
	पूर्ण

out_समाप्त:
	__set_current_state(TASK_RUNNING);
	अगर (!kthपढ़ो_should_stop())
		रुको_to_die();

	वापस 0;
पूर्ण

अटल पूर्णांक __init ring_buffer_benchmark_init(व्योम)
अणु
	पूर्णांक ret;

	/* make a one meg buffer in overwite mode */
	buffer = ring_buffer_alloc(1000000, RB_FL_OVERWRITE);
	अगर (!buffer)
		वापस -ENOMEM;

	अगर (!disable_पढ़ोer) अणु
		consumer = kthपढ़ो_create(ring_buffer_consumer_thपढ़ो,
					  शून्य, "rb_consumer");
		ret = PTR_ERR(consumer);
		अगर (IS_ERR(consumer))
			जाओ out_fail;
	पूर्ण

	producer = kthपढ़ो_run(ring_buffer_producer_thपढ़ो,
			       शून्य, "rb_producer");
	ret = PTR_ERR(producer);

	अगर (IS_ERR(producer))
		जाओ out_समाप्त;

	/*
	 * Run them as low-prio background tasks by शेष:
	 */
	अगर (!disable_पढ़ोer) अणु
		अगर (consumer_fअगरo >= 2)
			sched_set_fअगरo(consumer);
		अन्यथा अगर (consumer_fअगरo == 1)
			sched_set_fअगरo_low(consumer);
		अन्यथा
			set_user_nice(consumer, consumer_nice);
	पूर्ण

	अगर (producer_fअगरo >= 2)
		sched_set_fअगरo(producer);
	अन्यथा अगर (producer_fअगरo == 1)
		sched_set_fअगरo_low(producer);
	अन्यथा
		set_user_nice(producer, producer_nice);

	वापस 0;

 out_समाप्त:
	अगर (consumer)
		kthपढ़ो_stop(consumer);

 out_fail:
	ring_buffer_मुक्त(buffer);
	वापस ret;
पूर्ण

अटल व्योम __निकास ring_buffer_benchmark_निकास(व्योम)
अणु
	kthपढ़ो_stop(producer);
	अगर (consumer)
		kthपढ़ो_stop(consumer);
	ring_buffer_मुक्त(buffer);
पूर्ण

module_init(ring_buffer_benchmark_init);
module_निकास(ring_buffer_benchmark_निकास);

MODULE_AUTHOR("Steven Rostedt");
MODULE_DESCRIPTION("ring_buffer_benchmark");
MODULE_LICENSE("GPL");
