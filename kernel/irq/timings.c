<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2016, Linaro Ltd - Daniel Lezcano <daniel.lezcano@linaro.org>
#घोषणा pr_fmt(fmt) "irq_timings: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/idr.h>
#समावेश <linux/irq.h>
#समावेश <linux/math64.h>
#समावेश <linux/log2.h>

#समावेश <trace/events/irq.h>

#समावेश "internals.h"

DEFINE_STATIC_KEY_FALSE(irq_timing_enabled);

DEFINE_PER_CPU(काष्ठा irq_timings, irq_timings);

अटल DEFINE_IDR(irqt_stats);

व्योम irq_timings_enable(व्योम)
अणु
	अटल_branch_enable(&irq_timing_enabled);
पूर्ण

व्योम irq_timings_disable(व्योम)
अणु
	अटल_branch_disable(&irq_timing_enabled);
पूर्ण

/*
 * The मुख्य goal of this algorithm is to predict the next पूर्णांकerrupt
 * occurrence on the current CPU.
 *
 * Currently, the पूर्णांकerrupt timings are stored in a circular array
 * buffer every समय there is an पूर्णांकerrupt, as a tuple: the पूर्णांकerrupt
 * number and the associated बारtamp when the event occurred <irq,
 * बारtamp>.
 *
 * For every पूर्णांकerrupt occurring in a लघु period of समय, we can
 * measure the elapsed समय between the occurrences क्रम the same
 * पूर्णांकerrupt and we end up with a suite of पूर्णांकervals. The experience
 * showed the पूर्णांकerrupts are often coming following a periodic
 * pattern.
 *
 * The objective of the algorithm is to find out this periodic pattern
 * in a fastest way and use its period to predict the next irq event.
 *
 * When the next पूर्णांकerrupt event is requested, we are in the situation
 * where the पूर्णांकerrupts are disabled and the circular buffer
 * containing the timings is filled with the events which happened
 * after the previous next-पूर्णांकerrupt-event request.
 *
 * At this poपूर्णांक, we पढ़ो the circular buffer and we fill the irq
 * related statistics काष्ठाure. After this step, the circular array
 * containing the timings is empty because all the values are
 * dispatched in their corresponding buffers.
 *
 * Now क्रम each पूर्णांकerrupt, we can predict the next event by using the
 * suffix array, log पूर्णांकerval and exponential moving average
 *
 * 1. Suffix array
 *
 * Suffix array is an array of all the suffixes of a string. It is
 * widely used as a data काष्ठाure क्रम compression, text search, ...
 * For instance क्रम the word 'banana', the suffixes will be: 'banana'
 * 'anana' 'nana' 'ana' 'na' 'a'
 *
 * Usually, the suffix array is sorted but क्रम our purpose it is
 * not necessary and won't provide any improvement in the context of
 * the solved problem where we clearly define the boundaries of the
 * search by a max period and min period.
 *
 * The suffix array will build a suite of पूर्णांकervals of dअगरferent
 * length and will look क्रम the repetition of each suite. If the suite
 * is repeating then we have the period because it is the length of
 * the suite whatever its position in the buffer.
 *
 * 2. Log पूर्णांकerval
 *
 * We saw the irq timings allow to compute the पूर्णांकerval of the
 * occurrences क्रम a specअगरic पूर्णांकerrupt. We can reasonably assume the
 * दीर्घer is the पूर्णांकerval, the higher is the error क्रम the next event
 * and we can consider storing those पूर्णांकerval values पूर्णांकo an array
 * where each slot in the array correspond to an पूर्णांकerval at the घातer
 * of 2 of the index. For example, index 12 will contain values
 * between 2^11 and 2^12.
 *
 * At the end we have an array of values where at each index defines a
 * [2^index - 1, 2 ^ index] पूर्णांकerval values allowing to store a large
 * number of values inside a small array.
 *
 * For example, अगर we have the value 1123, then we store it at
 * ilog2(1123) = 10 index value.
 *
 * Storing those value at the specअगरic index is करोne by computing an
 * exponential moving average क्रम this specअगरic slot. For instance,
 * क्रम values 1800, 1123, 1453, ... fall under the same slot (10) and
 * the exponential moving average is computed every समय a new value
 * is stored at this slot.
 *
 * 3. Exponential Moving Average
 *
 * The EMA is largely used to track a संकेत क्रम stocks or as a low
 * pass filter. The magic of the क्रमmula, is it is very simple and the
 * reactivity of the average can be tuned with the factors called
 * alpha.
 *
 * The higher the alphas are, the faster the average respond to the
 * संकेत change. In our हाल, अगर a slot in the array is a big
 * पूर्णांकerval, we can have numbers with a big dअगरference between
 * them. The impact of those dअगरferences in the average computation
 * can be tuned by changing the alpha value.
 *
 *
 *  -- The algorithm --
 *
 * We saw the dअगरferent processing above, now let's see how they are
 * used together.
 *
 * For each पूर्णांकerrupt:
 *	For each पूर्णांकerval:
 *		Compute the index = ilog2(पूर्णांकerval)
 *		Compute a new_ema(buffer[index], पूर्णांकerval)
 *		Store the index in a circular buffer
 *
 *	Compute the suffix array of the indexes
 *
 *	For each suffix:
 *		If the suffix is reverse-found 3 बार
 *			Return suffix
 *
 *	Return Not found
 *
 * However we can not have endless suffix array to be build, it won't
 * make sense and it will add an extra overhead, so we can restrict
 * this to a maximum suffix length of 5 and a minimum suffix length of
 * 2. The experience showed 5 is the majority of the maximum pattern
 * period found क्रम dअगरferent devices.
 *
 * The result is a pattern finding less than 1us क्रम an पूर्णांकerrupt.
 *
 * Example based on real values:
 *
 * Example 1 : MMC ग_लिखो/पढ़ो पूर्णांकerrupt पूर्णांकerval:
 *
 *	223947, 1240, 1384, 1386, 1386,
 *	217416, 1236, 1384, 1386, 1387,
 *	214719, 1241, 1386, 1387, 1384,
 *	213696, 1234, 1384, 1386, 1388,
 *	219904, 1240, 1385, 1389, 1385,
 *	212240, 1240, 1386, 1386, 1386,
 *	214415, 1236, 1384, 1386, 1387,
 *	214276, 1234, 1384, 1388, ?
 *
 * For each element, apply ilog2(value)
 *
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, ?
 *
 * Max period of 5, we take the last (max_period * 3) 15 elements as
 * we can be confident अगर the pattern repeats itself three बार it is
 * a repeating pattern.
 *
 *	             8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, ?
 *
 * Suffixes are:
 *
 *  1) 8, 15, 8, 8, 8  <- max period
 *  2) 8, 15, 8, 8
 *  3) 8, 15, 8
 *  4) 8, 15           <- min period
 *
 * From there we search the repeating pattern क्रम each suffix.
 *
 * buffer: 8, 15, 8, 8, 8, 8, 15, 8, 8, 8, 8, 15, 8, 8, 8
 *         |   |  |  |  |  |   |  |  |  |  |   |  |  |  |
 *         8, 15, 8, 8, 8  |   |  |  |  |  |   |  |  |  |
 *                         8, 15, 8, 8, 8  |   |  |  |  |
 *                                         8, 15, 8, 8, 8
 *
 * When moving the suffix, we found exactly 3 matches.
 *
 * The first suffix with period 5 is repeating.
 *
 * The next event is (3 * max_period) % suffix_period
 *
 * In this example, the result 0, so the next event is suffix[0] => 8
 *
 * However, 8 is the index in the array of exponential moving average
 * which was calculated on the fly when storing the values, so the
 * पूर्णांकerval is ema[8] = 1366
 *
 *
 * Example 2:
 *
 *	4, 3, 5, 100,
 *	3, 3, 5, 117,
 *	4, 4, 5, 112,
 *	4, 3, 4, 110,
 *	3, 5, 3, 117,
 *	4, 4, 5, 112,
 *	4, 3, 4, 110,
 *	3, 4, 5, 112,
 *	4, 3, 4, 110
 *
 * ilog2
 *
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4
 *
 * Max period 5:
 *	   0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4
 *
 * Suffixes:
 *
 *  1) 0, 0, 4, 0, 0
 *  2) 0, 0, 4, 0
 *  3) 0, 0, 4
 *  4) 0, 0
 *
 * buffer: 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4
 *         |  |  |  |  |  |  X
 *         0, 0, 4, 0, 0, |  X
 *                        0, 0
 *
 * buffer: 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4
 *         |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 *         0, 0, 4, 0, |  |  |  |  |  |  |  |  |  |  |
 *                     0, 0, 4, 0, |  |  |  |  |  |  |
 *                                 0, 0, 4, 0, |  |  |
 *                                             0  0  4
 *
 * Pattern is found 3 बार, the reमुख्यing is 1 which results from
 * (max_period * 3) % suffix_period. This value is the index in the
 * suffix arrays. The suffix array क्रम a period 4 has the value 4
 * at index 1.
 */
#घोषणा EMA_ALPHA_VAL		64
#घोषणा EMA_ALPHA_SHIFT		7

#घोषणा PREDICTION_PERIOD_MIN	3
#घोषणा PREDICTION_PERIOD_MAX	5
#घोषणा PREDICTION_FACTOR	4
#घोषणा PREDICTION_MAX		10 /* 2 ^ PREDICTION_MAX useconds */
#घोषणा PREDICTION_BUFFER_SIZE	16 /* slots क्रम EMAs, hardly more than 16 */

/*
 * Number of elements in the circular buffer: If it happens it was
 * flushed beक्रमe, then the number of elements could be smaller than
 * IRQ_TIMINGS_SIZE, so the count is used, otherwise the array size is
 * used as we wrapped. The index begins from zero when we did not
 * wrap. That could be करोne in a nicer way with the proper circular
 * array काष्ठाure type but with the cost of extra computation in the
 * पूर्णांकerrupt handler hot path. We choose efficiency.
 */
#घोषणा क्रम_each_irqts(i, irqts)					\
	क्रम (i = irqts->count < IRQ_TIMINGS_SIZE ?			\
		     0 : irqts->count & IRQ_TIMINGS_MASK,		\
		     irqts->count = min(IRQ_TIMINGS_SIZE,		\
					irqts->count);			\
	     irqts->count > 0; irqts->count--,				\
		     i = (i + 1) & IRQ_TIMINGS_MASK)

काष्ठा irqt_stat अणु
	u64	last_ts;
	u64	ema_समय[PREDICTION_BUFFER_SIZE];
	पूर्णांक	timings[IRQ_TIMINGS_SIZE];
	पूर्णांक	circ_timings[IRQ_TIMINGS_SIZE];
	पूर्णांक	count;
पूर्ण;

/*
 * Exponential moving average computation
 */
अटल u64 irq_timings_ema_new(u64 value, u64 ema_old)
अणु
	s64 dअगरf;

	अगर (unlikely(!ema_old))
		वापस value;

	dअगरf = (value - ema_old) * EMA_ALPHA_VAL;
	/*
	 * We can use a s64 type variable to be added with the u64
	 * ema_old variable as this one will never have its topmost
	 * bit set, it will be always smaller than 2^63 nanosec
	 * पूर्णांकerrupt पूर्णांकerval (292 years).
	 */
	वापस ema_old + (dअगरf >> EMA_ALPHA_SHIFT);
पूर्ण

अटल पूर्णांक irq_timings_next_event_index(पूर्णांक *buffer, माप_प्रकार len, पूर्णांक period_max)
अणु
	पूर्णांक period;

	/*
	 * Move the beginning poपूर्णांकer to the end minus the max period x 3.
	 * We are at the poपूर्णांक we can begin searching the pattern
	 */
	buffer = &buffer[len - (period_max * 3)];

	/* Adjust the length to the maximum allowed period x 3 */
	len = period_max * 3;

	/*
	 * The buffer contains the suite of पूर्णांकervals, in a ilog2
	 * basis, we are looking क्रम a repetition. We poपूर्णांक the
	 * beginning of the search three बार the length of the
	 * period beginning at the end of the buffer. We करो that क्रम
	 * each suffix.
	 */
	क्रम (period = period_max; period >= PREDICTION_PERIOD_MIN; period--) अणु

		/*
		 * The first comparison always succeed because the
		 * suffix is deduced from the first n-period bytes of
		 * the buffer and we compare the initial suffix with
		 * itself, so we can skip the first iteration.
		 */
		पूर्णांक idx = period;
		माप_प्रकार size = period;

		/*
		 * We look अगर the suite with period 'i' repeat
		 * itself. If it is truncated at the end, as it
		 * repeats we can use the period to find out the next
		 * element with the modulo.
		 */
		जबतक (!स_भेद(buffer, &buffer[idx], size * माप(पूर्णांक))) अणु

			/*
			 * Move the index in a period basis
			 */
			idx += size;

			/*
			 * If this condition is reached, all previous
			 * स_भेद were successful, so the period is
			 * found.
			 */
			अगर (idx == len)
				वापस buffer[len % period];

			/*
			 * If the reमुख्यing elements to compare are
			 * smaller than the period, पढ़ोjust the size
			 * of the comparison क्रम the last iteration.
			 */
			अगर (len - idx < period)
				size = len - idx;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल u64 __irq_timings_next_event(काष्ठा irqt_stat *irqs, पूर्णांक irq, u64 now)
अणु
	पूर्णांक index, i, period_max, count, start, min = पूर्णांक_उच्च;

	अगर ((now - irqs->last_ts) >= NSEC_PER_SEC) अणु
		irqs->count = irqs->last_ts = 0;
		वापस U64_MAX;
	पूर्ण

	/*
	 * As we want to find three बार the repetition, we need a
	 * number of पूर्णांकervals greater or equal to three बार the
	 * maximum period, otherwise we truncate the max period.
	 */
	period_max = irqs->count > (3 * PREDICTION_PERIOD_MAX) ?
		PREDICTION_PERIOD_MAX : irqs->count / 3;

	/*
	 * If we करोn't have enough irq timings क्रम this prediction,
	 * just bail out.
	 */
	अगर (period_max <= PREDICTION_PERIOD_MIN)
		वापस U64_MAX;

	/*
	 * 'count' will depends अगर the circular buffer wrapped or not
	 */
	count = irqs->count < IRQ_TIMINGS_SIZE ?
		irqs->count : IRQ_TIMINGS_SIZE;

	start = irqs->count < IRQ_TIMINGS_SIZE ?
		0 : (irqs->count & IRQ_TIMINGS_MASK);

	/*
	 * Copy the content of the circular buffer पूर्णांकo another buffer
	 * in order to linearize the buffer instead of dealing with
	 * wrapping indexes and shअगरted array which will be prone to
	 * error and extremely dअगरficult to debug.
	 */
	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक index = (start + i) & IRQ_TIMINGS_MASK;

		irqs->timings[i] = irqs->circ_timings[index];
		min = min_t(पूर्णांक, irqs->timings[i], min);
	पूर्ण

	index = irq_timings_next_event_index(irqs->timings, count, period_max);
	अगर (index < 0)
		वापस irqs->last_ts + irqs->ema_समय[min];

	वापस irqs->last_ts + irqs->ema_समय[index];
पूर्ण

अटल __always_अंतरभूत पूर्णांक irq_timings_पूर्णांकerval_index(u64 पूर्णांकerval)
अणु
	/*
	 * The PREDICTION_FACTOR increase the पूर्णांकerval size क्रम the
	 * array of exponential average.
	 */
	u64 पूर्णांकerval_us = (पूर्णांकerval >> 10) / PREDICTION_FACTOR;

	वापस likely(पूर्णांकerval_us) ? ilog2(पूर्णांकerval_us) : 0;
पूर्ण

अटल __always_अंतरभूत व्योम __irq_timings_store(पूर्णांक irq, काष्ठा irqt_stat *irqs,
						u64 पूर्णांकerval)
अणु
	पूर्णांक index;

	/*
	 * Get the index in the ema table क्रम this पूर्णांकerrupt.
	 */
	index = irq_timings_पूर्णांकerval_index(पूर्णांकerval);

	/*
	 * Store the index as an element of the pattern in another
	 * circular array.
	 */
	irqs->circ_timings[irqs->count & IRQ_TIMINGS_MASK] = index;

	irqs->ema_समय[index] = irq_timings_ema_new(पूर्णांकerval,
						    irqs->ema_समय[index]);

	irqs->count++;
पूर्ण

अटल अंतरभूत व्योम irq_timings_store(पूर्णांक irq, काष्ठा irqt_stat *irqs, u64 ts)
अणु
	u64 old_ts = irqs->last_ts;
	u64 पूर्णांकerval;

	/*
	 * The बारtamps are असलolute समय values, we need to compute
	 * the timing पूर्णांकerval between two पूर्णांकerrupts.
	 */
	irqs->last_ts = ts;

	/*
	 * The पूर्णांकerval type is u64 in order to deal with the same
	 * type in our computation, that prevent mindfuck issues with
	 * overflow, sign and भागision.
	 */
	पूर्णांकerval = ts - old_ts;

	/*
	 * The पूर्णांकerrupt triggered more than one second apart, that
	 * ends the sequence as predictable क्रम our purpose. In this
	 * हाल, assume we have the beginning of a sequence and the
	 * बारtamp is the first value. As it is impossible to
	 * predict anything at this poपूर्णांक, वापस.
	 *
	 * Note the first बारtamp of the sequence will always fall
	 * in this test because the old_ts is zero. That is what we
	 * want as we need another बारtamp to compute an पूर्णांकerval.
	 */
	अगर (पूर्णांकerval >= NSEC_PER_SEC) अणु
		irqs->count = 0;
		वापस;
	पूर्ण

	__irq_timings_store(irq, irqs, पूर्णांकerval);
पूर्ण

/**
 * irq_timings_next_event - Return when the next event is supposed to arrive
 *
 * During the last busy cycle, the number of पूर्णांकerrupts is incremented
 * and stored in the irq_timings काष्ठाure. This inक्रमmation is
 * necessary to:
 *
 * - know अगर the index in the table wrapped up:
 *
 *      If more than the array size पूर्णांकerrupts happened during the
 *      last busy/idle cycle, the index wrapped up and we have to
 *      begin with the next element in the array which is the last one
 *      in the sequence, otherwise it is at the index 0.
 *
 * - have an indication of the पूर्णांकerrupts activity on this CPU
 *   (eg. irq/sec)
 *
 * The values are 'consumed' after inserting in the statistical model,
 * thus the count is reinitialized.
 *
 * The array of values **must** be browsed in the समय direction, the
 * बारtamp must increase between an element and the next one.
 *
 * Returns a nanosec समय based estimation of the earliest पूर्णांकerrupt,
 * U64_MAX otherwise.
 */
u64 irq_timings_next_event(u64 now)
अणु
	काष्ठा irq_timings *irqts = this_cpu_ptr(&irq_timings);
	काष्ठा irqt_stat *irqs;
	काष्ठा irqt_stat __percpu *s;
	u64 ts, next_evt = U64_MAX;
	पूर्णांक i, irq = 0;

	/*
	 * This function must be called with the local irq disabled in
	 * order to prevent the timings circular buffer to be updated
	 * जबतक we are पढ़ोing it.
	 */
	lockdep_निश्चित_irqs_disabled();

	अगर (!irqts->count)
		वापस next_evt;

	/*
	 * Number of elements in the circular buffer: If it happens it
	 * was flushed beक्रमe, then the number of elements could be
	 * smaller than IRQ_TIMINGS_SIZE, so the count is used,
	 * otherwise the array size is used as we wrapped. The index
	 * begins from zero when we did not wrap. That could be करोne
	 * in a nicer way with the proper circular array काष्ठाure
	 * type but with the cost of extra computation in the
	 * पूर्णांकerrupt handler hot path. We choose efficiency.
	 *
	 * Inject measured irq/बारtamp to the pattern prediction
	 * model जबतक decrementing the counter because we consume the
	 * data from our circular buffer.
	 */
	क्रम_each_irqts(i, irqts) अणु
		irq = irq_timing_decode(irqts->values[i], &ts);
		s = idr_find(&irqt_stats, irq);
		अगर (s)
			irq_timings_store(irq, this_cpu_ptr(s), ts);
	पूर्ण

	/*
	 * Look in the list of पूर्णांकerrupts' statistics, the earliest
	 * next event.
	 */
	idr_क्रम_each_entry(&irqt_stats, s, i) अणु

		irqs = this_cpu_ptr(s);

		ts = __irq_timings_next_event(irqs, i, now);
		अगर (ts <= now)
			वापस now;

		अगर (ts < next_evt)
			next_evt = ts;
	पूर्ण

	वापस next_evt;
पूर्ण

व्योम irq_timings_मुक्त(पूर्णांक irq)
अणु
	काष्ठा irqt_stat __percpu *s;

	s = idr_find(&irqt_stats, irq);
	अगर (s) अणु
		मुक्त_percpu(s);
		idr_हटाओ(&irqt_stats, irq);
	पूर्ण
पूर्ण

पूर्णांक irq_timings_alloc(पूर्णांक irq)
अणु
	काष्ठा irqt_stat __percpu *s;
	पूर्णांक id;

	/*
	 * Some platक्रमms can have the same निजी पूर्णांकerrupt per cpu,
	 * so this function may be called several बार with the
	 * same पूर्णांकerrupt number. Just bail out in हाल the per cpu
	 * stat काष्ठाure is alपढ़ोy allocated.
	 */
	s = idr_find(&irqt_stats, irq);
	अगर (s)
		वापस 0;

	s = alloc_percpu(*s);
	अगर (!s)
		वापस -ENOMEM;

	idr_preload(GFP_KERNEL);
	id = idr_alloc(&irqt_stats, s, irq, irq + 1, GFP_NOWAIT);
	idr_preload_end();

	अगर (id < 0) अणु
		मुक्त_percpu(s);
		वापस id;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_TEST_IRQ_TIMINGS
काष्ठा timings_पूर्णांकervals अणु
	u64 *पूर्णांकervals;
	माप_प्रकार count;
पूर्ण;

/*
 * Intervals are given in nanosecond base
 */
अटल u64 पूर्णांकervals0[] __initdata = अणु
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000,
पूर्ण;

अटल u64 पूर्णांकervals1[] __initdata = अणु
	223947000, 1240000, 1384000, 1386000, 1386000,
	217416000, 1236000, 1384000, 1386000, 1387000,
	214719000, 1241000, 1386000, 1387000, 1384000,
	213696000, 1234000, 1384000, 1386000, 1388000,
	219904000, 1240000, 1385000, 1389000, 1385000,
	212240000, 1240000, 1386000, 1386000, 1386000,
	214415000, 1236000, 1384000, 1386000, 1387000,
	214276000, 1234000,
पूर्ण;

अटल u64 पूर्णांकervals2[] __initdata = अणु
	4000, 3000, 5000, 100000,
	3000, 3000, 5000, 117000,
	4000, 4000, 5000, 112000,
	4000, 3000, 4000, 110000,
	3000, 5000, 3000, 117000,
	4000, 4000, 5000, 112000,
	4000, 3000, 4000, 110000,
	3000, 4000, 5000, 112000,
	4000,
पूर्ण;

अटल u64 पूर्णांकervals3[] __initdata = अणु
	1385000, 212240000, 1240000,
	1386000, 214415000, 1236000,
	1384000, 214276000, 1234000,
	1386000, 214415000, 1236000,
	1385000, 212240000, 1240000,
	1386000, 214415000, 1236000,
	1384000, 214276000, 1234000,
	1386000, 214415000, 1236000,
	1385000, 212240000, 1240000,
पूर्ण;

अटल u64 पूर्णांकervals4[] __initdata = अणु
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000,
पूर्ण;

अटल काष्ठा timings_पूर्णांकervals tis[] __initdata = अणु
	अणु पूर्णांकervals0, ARRAY_SIZE(पूर्णांकervals0) पूर्ण,
	अणु पूर्णांकervals1, ARRAY_SIZE(पूर्णांकervals1) पूर्ण,
	अणु पूर्णांकervals2, ARRAY_SIZE(पूर्णांकervals2) पूर्ण,
	अणु पूर्णांकervals3, ARRAY_SIZE(पूर्णांकervals3) पूर्ण,
	अणु पूर्णांकervals4, ARRAY_SIZE(पूर्णांकervals4) पूर्ण,
पूर्ण;

अटल पूर्णांक __init irq_timings_test_next_index(काष्ठा timings_पूर्णांकervals *ti)
अणु
	पूर्णांक _buffer[IRQ_TIMINGS_SIZE];
	पूर्णांक buffer[IRQ_TIMINGS_SIZE];
	पूर्णांक index, start, i, count, period_max;

	count = ti->count - 1;

	period_max = count > (3 * PREDICTION_PERIOD_MAX) ?
		PREDICTION_PERIOD_MAX : count / 3;

	/*
	 * Inject all values except the last one which will be used
	 * to compare with the next index result.
	 */
	pr_debug("index suite: ");

	क्रम (i = 0; i < count; i++) अणु
		index = irq_timings_पूर्णांकerval_index(ti->पूर्णांकervals[i]);
		_buffer[i & IRQ_TIMINGS_MASK] = index;
		pr_cont("%d ", index);
	पूर्ण

	start = count < IRQ_TIMINGS_SIZE ? 0 :
		count & IRQ_TIMINGS_MASK;

	count = min_t(पूर्णांक, count, IRQ_TIMINGS_SIZE);

	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक index = (start + i) & IRQ_TIMINGS_MASK;
		buffer[i] = _buffer[index];
	पूर्ण

	index = irq_timings_next_event_index(buffer, count, period_max);
	i = irq_timings_पूर्णांकerval_index(ti->पूर्णांकervals[ti->count - 1]);

	अगर (index != i) अणु
		pr_err("Expected (%d) and computed (%d) next indexes differ\n",
		       i, index);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init irq_timings_next_index_selftest(व्योम)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(tis); i++) अणु

		pr_info("---> Injecting intervals number #%d (count=%zd)\n",
			i, tis[i].count);

		ret = irq_timings_test_next_index(&tis[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init irq_timings_test_irqs(काष्ठा timings_पूर्णांकervals *ti)
अणु
	काष्ठा irqt_stat __percpu *s;
	काष्ठा irqt_stat *irqs;
	पूर्णांक i, index, ret, irq = 0xACE5;

	ret = irq_timings_alloc(irq);
	अगर (ret) अणु
		pr_err("Failed to allocate irq timings\n");
		वापस ret;
	पूर्ण

	s = idr_find(&irqt_stats, irq);
	अगर (!s) अणु
		ret = -EIDRM;
		जाओ out;
	पूर्ण

	irqs = this_cpu_ptr(s);

	क्रम (i = 0; i < ti->count; i++) अणु

		index = irq_timings_पूर्णांकerval_index(ti->पूर्णांकervals[i]);
		pr_debug("%d: interval=%llu ema_index=%d\n",
			 i, ti->पूर्णांकervals[i], index);

		__irq_timings_store(irq, irqs, ti->पूर्णांकervals[i]);
		अगर (irqs->circ_timings[i & IRQ_TIMINGS_MASK] != index) अणु
			pr_err("Failed to store in the circular buffer\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (irqs->count != ti->count) अणु
		pr_err("Count differs\n");
		जाओ out;
	पूर्ण

	ret = 0;
out:
	irq_timings_मुक्त(irq);

	वापस ret;
पूर्ण

अटल पूर्णांक __init irq_timings_irqs_selftest(व्योम)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(tis); i++) अणु
		pr_info("---> Injecting intervals number #%d (count=%zd)\n",
			i, tis[i].count);
		ret = irq_timings_test_irqs(&tis[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init irq_timings_test_irqts(काष्ठा irq_timings *irqts,
					 अचिन्हित count)
अणु
	पूर्णांक start = count >= IRQ_TIMINGS_SIZE ? count - IRQ_TIMINGS_SIZE : 0;
	पूर्णांक i, irq, oirq = 0xBEEF;
	u64 ots = 0xDEAD, ts;

	/*
	 * Fill the circular buffer by using the dedicated function.
	 */
	क्रम (i = 0; i < count; i++) अणु
		pr_debug("%d: index=%d, ts=%llX irq=%X\n",
			 i, i & IRQ_TIMINGS_MASK, ots + i, oirq + i);

		irq_timings_push(ots + i, oirq + i);
	पूर्ण

	/*
	 * Compute the first elements values after the index wrapped
	 * up or not.
	 */
	ots += start;
	oirq += start;

	/*
	 * Test the circular buffer count is correct.
	 */
	pr_debug("---> Checking timings array count (%d) is right\n", count);
	अगर (WARN_ON(irqts->count != count))
		वापस -EINVAL;

	/*
	 * Test the macro allowing to browse all the irqts.
	 */
	pr_debug("---> Checking the for_each_irqts() macro\n");
	क्रम_each_irqts(i, irqts) अणु

		irq = irq_timing_decode(irqts->values[i], &ts);

		pr_debug("index=%d, ts=%llX / %llX, irq=%X / %X\n",
			 i, ts, ots, irq, oirq);

		अगर (WARN_ON(ts != ots || irq != oirq))
			वापस -EINVAL;

		ots++; oirq++;
	पूर्ण

	/*
	 * The circular buffer should have be flushed when browsed
	 * with क्रम_each_irqts
	 */
	pr_debug("---> Checking timings array is empty after browsing it\n");
	अगर (WARN_ON(irqts->count))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __init irq_timings_irqts_selftest(व्योम)
अणु
	काष्ठा irq_timings *irqts = this_cpu_ptr(&irq_timings);
	पूर्णांक i, ret;

	/*
	 * Test the circular buffer with dअगरferent number of
	 * elements. The purpose is to test at the limits (empty, half
	 * full, full, wrapped with the cursor at the boundaries,
	 * wrapped several बार, etc ...
	 */
	पूर्णांक count[] = अणु 0,
			IRQ_TIMINGS_SIZE >> 1,
			IRQ_TIMINGS_SIZE,
			IRQ_TIMINGS_SIZE + (IRQ_TIMINGS_SIZE >> 1),
			2 * IRQ_TIMINGS_SIZE,
			(2 * IRQ_TIMINGS_SIZE) + 3,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(count); i++) अणु

		pr_info("---> Checking the timings with %d/%d values\n",
			count[i], IRQ_TIMINGS_SIZE);

		ret = irq_timings_test_irqts(irqts, count[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init irq_timings_selftest(व्योम)
अणु
	पूर्णांक ret;

	pr_info("------------------- selftest start -----------------\n");

	/*
	 * At this poपूर्णांक, we करोn't except any subप्रणाली to use the irq
	 * timings but us, so it should not be enabled.
	 */
	अगर (अटल_branch_unlikely(&irq_timing_enabled)) अणु
		pr_warn("irq timings already initialized, skipping selftest\n");
		वापस 0;
	पूर्ण

	ret = irq_timings_irqts_selftest();
	अगर (ret)
		जाओ out;

	ret = irq_timings_irqs_selftest();
	अगर (ret)
		जाओ out;

	ret = irq_timings_next_index_selftest();
out:
	pr_info("---------- selftest end with %s -----------\n",
		ret ? "failure" : "success");

	वापस ret;
पूर्ण
early_initcall(irq_timings_selftest);
#पूर्ण_अगर
