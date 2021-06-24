<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Historical Service Time
 *
 *  Keeps a समय-weighted exponential moving average of the historical
 *  service समय. Estimates future service समय based on the historical
 *  service समय and the number of outstanding requests.
 *
 *  Marks paths stale अगर they have not finished within hst *
 *  num_paths. If a path is stale and unused, we will send a single
 *  request to probe in हाल the path has improved. This situation
 *  generally arises अगर the path is so much worse than others that it
 *  will never have the best estimated service समय, or अगर the entire
 *  multipath device is unused. If a path is stale and in use, limit the
 *  number of requests it can receive with the assumption that the path
 *  has become degraded.
 *
 *  To aव्योम repeatedly calculating exponents क्रम समय weighting, बार
 *  are split पूर्णांकo HST_WEIGHT_COUNT buckets each (1 >> HST_BUCKET_SHIFT)
 *  ns, and the weighting is pre-calculated.
 *
 */

#समावेश "dm.h"
#समावेश "dm-path-selector.h"

#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>


#घोषणा DM_MSG_PREFIX	"multipath historical-service-time"
#घोषणा HST_MIN_IO 1
#घोषणा HST_VERSION "0.1.1"

#घोषणा HST_FIXED_SHIFT 10  /* 10 bits of decimal precision */
#घोषणा HST_FIXED_MAX (ULदीर्घ_उच्च >> HST_FIXED_SHIFT)
#घोषणा HST_FIXED_1 (1 << HST_FIXED_SHIFT)
#घोषणा HST_FIXED_95 972
#घोषणा HST_MAX_INFLIGHT HST_FIXED_1
#घोषणा HST_BUCKET_SHIFT 24 /* Buckets are ~ 16ms */
#घोषणा HST_WEIGHT_COUNT 64ULL

काष्ठा selector अणु
	काष्ठा list_head valid_paths;
	काष्ठा list_head failed_paths;
	पूर्णांक valid_count;
	spinlock_t lock;

	अचिन्हित पूर्णांक weights[HST_WEIGHT_COUNT];
	अचिन्हित पूर्णांक threshold_multiplier;
पूर्ण;

काष्ठा path_info अणु
	काष्ठा list_head list;
	काष्ठा dm_path *path;
	अचिन्हित पूर्णांक repeat_count;

	spinlock_t lock;

	u64 historical_service_समय; /* Fixed poपूर्णांक */

	u64 stale_after;
	u64 last_finish;

	u64 outstanding;
पूर्ण;

/**
 * fixed_घातer - compute: x^n, in O(log n) समय
 *
 * @x:         base of the घातer
 * @frac_bits: fractional bits of @x
 * @n:         घातer to उठाओ @x to.
 *
 * By exploiting the relation between the definition of the natural घातer
 * function: x^n := x*x*...*x (x multiplied by itself क्रम n बार), and
 * the binary encoding of numbers used by computers: n := \Sum n_i * 2^i,
 * (where: n_i \elem अणु0, 1पूर्ण, the binary vector representing n),
 * we find: x^n := x^(\Sum n_i * 2^i) := \Prod x^(n_i * 2^i), which is
 * of course trivially computable in O(log_2 n), the length of our binary
 * vector.
 *
 * (see: kernel/sched/loadavg.c)
 */
अटल u64 fixed_घातer(u64 x, अचिन्हित पूर्णांक frac_bits, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ result = 1UL << frac_bits;

	अगर (n) अणु
		क्रम (;;) अणु
			अगर (n & 1) अणु
				result *= x;
				result += 1UL << (frac_bits - 1);
				result >>= frac_bits;
			पूर्ण
			n >>= 1;
			अगर (!n)
				अवरोध;
			x *= x;
			x += 1UL << (frac_bits - 1);
			x >>= frac_bits;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

/*
 * Calculate the next value of an exponential moving average
 * a_1 = a_0 * e + a * (1 - e)
 *
 * @last: [0, ULदीर्घ_उच्च >> HST_FIXED_SHIFT]
 * @next: [0, ULदीर्घ_उच्च >> HST_FIXED_SHIFT]
 * @weight: [0, HST_FIXED_1]
 *
 * Note:
 *   To account क्रम multiple periods in the same calculation,
 *   a_n = a_0 * e^n + a * (1 - e^n),
 *   so call fixed_ema(last, next, घात(weight, N))
 */
अटल u64 fixed_ema(u64 last, u64 next, u64 weight)
अणु
	last *= weight;
	last += next * (HST_FIXED_1 - weight);
	last += 1ULL << (HST_FIXED_SHIFT - 1);
	वापस last >> HST_FIXED_SHIFT;
पूर्ण

अटल काष्ठा selector *alloc_selector(व्योम)
अणु
	काष्ठा selector *s = kदो_स्मृति(माप(*s), GFP_KERNEL);

	अगर (s) अणु
		INIT_LIST_HEAD(&s->valid_paths);
		INIT_LIST_HEAD(&s->failed_paths);
		spin_lock_init(&s->lock);
		s->valid_count = 0;
	पूर्ण

	वापस s;
पूर्ण

/*
 * Get the weight क्रम a given समय span.
 */
अटल u64 hst_weight(काष्ठा path_selector *ps, u64 delta)
अणु
	काष्ठा selector *s = ps->context;
	पूर्णांक bucket = clamp(delta >> HST_BUCKET_SHIFT, 0ULL,
			   HST_WEIGHT_COUNT - 1);

	वापस s->weights[bucket];
पूर्ण

/*
 * Set up the weights array.
 *
 * weights[len-1] = 0
 * weights[n] = base ^ (n + 1)
 */
अटल व्योम hst_set_weights(काष्ठा path_selector *ps, अचिन्हित पूर्णांक base)
अणु
	काष्ठा selector *s = ps->context;
	पूर्णांक i;

	अगर (base >= HST_FIXED_1)
		वापस;

	क्रम (i = 0; i < HST_WEIGHT_COUNT - 1; i++)
		s->weights[i] = fixed_घातer(base, HST_FIXED_SHIFT, i + 1);
	s->weights[HST_WEIGHT_COUNT - 1] = 0;
पूर्ण

अटल पूर्णांक hst_create(काष्ठा path_selector *ps, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा selector *s;
	अचिन्हित पूर्णांक base_weight = HST_FIXED_95;
	अचिन्हित पूर्णांक threshold_multiplier = 0;
	अक्षर dummy;

	/*
	 * Arguments: [<base_weight> [<threshold_multiplier>]]
	 *   <base_weight>: Base weight क्रम ema [0, 1024) 10-bit fixed poपूर्णांक. A
	 *                  value of 0 will completely ignore any history.
	 *                  If not given, शेष (HST_FIXED_95) is used.
	 *   <threshold_multiplier>: Minimum threshold multiplier क्रम paths to
	 *                  be considered dअगरferent. That is, a path is
	 *                  considered dअगरferent अगरf (p1 > N * p2) where p1
	 *                  is the path with higher service समय. A threshold
	 *                  of 1 or 0 has no effect. Defaults to 0.
	 */
	अगर (argc > 2)
		वापस -EINVAL;

	अगर (argc && (माला_पूछो(argv[0], "%u%c", &base_weight, &dummy) != 1 ||
	     base_weight >= HST_FIXED_1)) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (argc > 1 && (माला_पूछो(argv[1], "%u%c",
				&threshold_multiplier, &dummy) != 1)) अणु
		वापस -EINVAL;
	पूर्ण

	s = alloc_selector();
	अगर (!s)
		वापस -ENOMEM;

	ps->context = s;

	hst_set_weights(ps, base_weight);
	s->threshold_multiplier = threshold_multiplier;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_paths(काष्ठा list_head *paths)
अणु
	काष्ठा path_info *pi, *next;

	list_क्रम_each_entry_safe(pi, next, paths, list) अणु
		list_del(&pi->list);
		kमुक्त(pi);
	पूर्ण
पूर्ण

अटल व्योम hst_destroy(काष्ठा path_selector *ps)
अणु
	काष्ठा selector *s = ps->context;

	मुक्त_paths(&s->valid_paths);
	मुक्त_paths(&s->failed_paths);
	kमुक्त(s);
	ps->context = शून्य;
पूर्ण

अटल पूर्णांक hst_status(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		     status_type_t type, अक्षर *result, अचिन्हित पूर्णांक maxlen)
अणु
	अचिन्हित पूर्णांक sz = 0;
	काष्ठा path_info *pi;

	अगर (!path) अणु
		काष्ठा selector *s = ps->context;

		DMEMIT("2 %u %u ", s->weights[0], s->threshold_multiplier);
	पूर्ण अन्यथा अणु
		pi = path->pscontext;

		चयन (type) अणु
		हाल STATUSTYPE_INFO:
			DMEMIT("%llu %llu %llu ", pi->historical_service_समय,
			       pi->outstanding, pi->stale_after);
			अवरोध;
		हाल STATUSTYPE_TABLE:
			DMEMIT("0 ");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस sz;
पूर्ण

अटल पूर्णांक hst_add_path(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		       पूर्णांक argc, अक्षर **argv, अक्षर **error)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi;
	अचिन्हित पूर्णांक repeat_count = HST_MIN_IO;
	अक्षर dummy;
	अचिन्हित दीर्घ flags;

	/*
	 * Arguments: [<repeat_count>]
	 *   <repeat_count>: The number of I/Os beक्रमe चयनing path.
	 *                   If not given, शेष (HST_MIN_IO) is used.
	 */
	अगर (argc > 1) अणु
		*error = "historical-service-time ps: incorrect number of arguments";
		वापस -EINVAL;
	पूर्ण

	अगर (argc && (माला_पूछो(argv[0], "%u%c", &repeat_count, &dummy) != 1)) अणु
		*error = "historical-service-time ps: invalid repeat count";
		वापस -EINVAL;
	पूर्ण

	/* allocate the path */
	pi = kदो_स्मृति(माप(*pi), GFP_KERNEL);
	अगर (!pi) अणु
		*error = "historical-service-time ps: Error allocating path context";
		वापस -ENOMEM;
	पूर्ण

	pi->path = path;
	pi->repeat_count = repeat_count;

	pi->historical_service_समय = HST_FIXED_1;

	spin_lock_init(&pi->lock);
	pi->outstanding = 0;

	pi->stale_after = 0;
	pi->last_finish = 0;

	path->pscontext = pi;

	spin_lock_irqsave(&s->lock, flags);
	list_add_tail(&pi->list, &s->valid_paths);
	s->valid_count++;
	spin_unlock_irqrestore(&s->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम hst_fail_path(काष्ठा path_selector *ps, काष्ठा dm_path *path)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = path->pscontext;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	list_move(&pi->list, &s->failed_paths);
	s->valid_count--;
	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल पूर्णांक hst_reinstate_path(काष्ठा path_selector *ps, काष्ठा dm_path *path)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = path->pscontext;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	list_move_tail(&pi->list, &s->valid_paths);
	s->valid_count++;
	spin_unlock_irqrestore(&s->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम hst_fill_compare(काष्ठा path_info *pi, u64 *hst,
			     u64 *out, u64 *stale)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pi->lock, flags);
	*hst = pi->historical_service_समय;
	*out = pi->outstanding;
	*stale = pi->stale_after;
	spin_unlock_irqrestore(&pi->lock, flags);
पूर्ण

/*
 * Compare the estimated service समय of 2 paths, pi1 and pi2,
 * क्रम the incoming I/O.
 *
 * Returns:
 * < 0 : pi1 is better
 * 0   : no dअगरference between pi1 and pi2
 * > 0 : pi2 is better
 *
 */
अटल दीर्घ दीर्घ hst_compare(काष्ठा path_info *pi1, काष्ठा path_info *pi2,
			     u64 समय_now, काष्ठा path_selector *ps)
अणु
	काष्ठा selector *s = ps->context;
	u64 hst1, hst2;
	दीर्घ दीर्घ out1, out2, stale1, stale2;
	पूर्णांक pi2_better, over_threshold;

	hst_fill_compare(pi1, &hst1, &out1, &stale1);
	hst_fill_compare(pi2, &hst2, &out2, &stale2);

	/* Check here अगर estimated latency क्रम two paths are too similar.
	 * If this is the हाल, we skip extra calculation and just compare
	 * outstanding requests. In this हाल, any unloaded paths will
	 * be preferred.
	 */
	अगर (hst1 > hst2)
		over_threshold = hst1 > (s->threshold_multiplier * hst2);
	अन्यथा
		over_threshold = hst2 > (s->threshold_multiplier * hst1);

	अगर (!over_threshold)
		वापस out1 - out2;

	/*
	 * If an unloaded path is stale, choose it. If both paths are unloaded,
	 * choose path that is the most stale.
	 * (If one path is loaded, choose the other)
	 */
	अगर ((!out1 && stale1 < समय_now) || (!out2 && stale2 < समय_now) ||
	    (!out1 && !out2))
		वापस (!out2 * stale1) - (!out1 * stale2);

	/* Compare estimated service समय. If outstanding is the same, we
	 * करोn't need to multiply
	 */
	अगर (out1 == out2) अणु
		pi2_better = hst1 > hst2;
	पूर्ण अन्यथा अणु
		/* Potential overflow with out >= 1024 */
		अगर (unlikely(out1 >= HST_MAX_INFLIGHT ||
			     out2 >= HST_MAX_INFLIGHT)) अणु
			/* If over 1023 in-flights, we may overflow अगर hst
			 * is at max. (With this shअगरt we still overflow at
			 * 1048576 in-flights, which is high enough).
			 */
			hst1 >>= HST_FIXED_SHIFT;
			hst2 >>= HST_FIXED_SHIFT;
		पूर्ण
		pi2_better = (1 + out1) * hst1 > (1 + out2) * hst2;
	पूर्ण

	/* In the हाल that the 'winner' is stale, limit to equal usage. */
	अगर (pi2_better) अणु
		अगर (stale2 < समय_now)
			वापस out1 - out2;
		वापस 1;
	पूर्ण
	अगर (stale1 < समय_now)
		वापस out1 - out2;
	वापस -1;
पूर्ण

अटल काष्ठा dm_path *hst_select_path(काष्ठा path_selector *ps,
				       माप_प्रकार nr_bytes)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = शून्य, *best = शून्य;
	u64 समय_now = sched_घड़ी();
	काष्ठा dm_path *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	अगर (list_empty(&s->valid_paths))
		जाओ out;

	list_क्रम_each_entry(pi, &s->valid_paths, list) अणु
		अगर (!best || (hst_compare(pi, best, समय_now, ps) < 0))
			best = pi;
	पूर्ण

	अगर (!best)
		जाओ out;

	/* Move last used path to end (least preferred in हाल of ties) */
	list_move_tail(&best->list, &s->valid_paths);

	ret = best->path;

out:
	spin_unlock_irqrestore(&s->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक hst_start_io(काष्ठा path_selector *ps, काष्ठा dm_path *path,
			माप_प्रकार nr_bytes)
अणु
	काष्ठा path_info *pi = path->pscontext;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pi->lock, flags);
	pi->outstanding++;
	spin_unlock_irqrestore(&pi->lock, flags);

	वापस 0;
पूर्ण

अटल u64 path_service_समय(काष्ठा path_info *pi, u64 start_समय)
अणु
	u64 sched_now = kसमय_get_ns();

	/* अगर a previous disk request has finished after this IO was
	 * sent to the hardware, pretend the submission happened
	 * serially.
	 */
	अगर (समय_after64(pi->last_finish, start_समय))
		start_समय = pi->last_finish;

	pi->last_finish = sched_now;
	अगर (समय_beक्रमe64(sched_now, start_समय))
		वापस 0;

	वापस sched_now - start_समय;
पूर्ण

अटल पूर्णांक hst_end_io(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		      माप_प्रकार nr_bytes, u64 start_समय)
अणु
	काष्ठा path_info *pi = path->pscontext;
	काष्ठा selector *s = ps->context;
	अचिन्हित दीर्घ flags;
	u64 st;

	spin_lock_irqsave(&pi->lock, flags);

	st = path_service_समय(pi, start_समय);
	pi->outstanding--;
	pi->historical_service_समय =
		fixed_ema(pi->historical_service_समय,
			  min(st * HST_FIXED_1, HST_FIXED_MAX),
			  hst_weight(ps, st));

	/*
	 * On request end, mark path as fresh. If a path hasn't
	 * finished any requests within the fresh period, the estimated
	 * service समय is considered too optimistic and we limit the
	 * maximum requests on that path.
	 */
	pi->stale_after = pi->last_finish +
		(s->valid_count * (pi->historical_service_समय >> HST_FIXED_SHIFT));

	spin_unlock_irqrestore(&pi->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा path_selector_type hst_ps = अणु
	.name		= "historical-service-time",
	.module		= THIS_MODULE,
	.table_args	= 1,
	.info_args	= 3,
	.create		= hst_create,
	.destroy	= hst_destroy,
	.status		= hst_status,
	.add_path	= hst_add_path,
	.fail_path	= hst_fail_path,
	.reinstate_path	= hst_reinstate_path,
	.select_path	= hst_select_path,
	.start_io	= hst_start_io,
	.end_io		= hst_end_io,
पूर्ण;

अटल पूर्णांक __init dm_hst_init(व्योम)
अणु
	पूर्णांक r = dm_रेजिस्टर_path_selector(&hst_ps);

	अगर (r < 0)
		DMERR("register failed %d", r);

	DMINFO("version " HST_VERSION " loaded");

	वापस r;
पूर्ण

अटल व्योम __निकास dm_hst_निकास(व्योम)
अणु
	पूर्णांक r = dm_unरेजिस्टर_path_selector(&hst_ps);

	अगर (r < 0)
		DMERR("unregister failed %d", r);
पूर्ण

module_init(dm_hst_init);
module_निकास(dm_hst_निकास);

MODULE_DESCRIPTION(DM_NAME " measured service time oriented path selector");
MODULE_AUTHOR("Khazhismel Kumykov <khazhy@google.com>");
MODULE_LICENSE("GPL");
