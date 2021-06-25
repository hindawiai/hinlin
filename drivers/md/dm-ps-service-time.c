<शैली गुरु>
/*
 * Copyright (C) 2007-2009 NEC Corporation.  All Rights Reserved.
 *
 * Module Author: Kiyoshi Ueda
 *
 * This file is released under the GPL.
 *
 * Throughput oriented path selector.
 */

#समावेश "dm.h"
#समावेश "dm-path-selector.h"

#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा DM_MSG_PREFIX	"multipath service-time"
#घोषणा ST_MIN_IO	1
#घोषणा ST_MAX_RELATIVE_THROUGHPUT	100
#घोषणा ST_MAX_RELATIVE_THROUGHPUT_SHIFT	7
#घोषणा ST_MAX_INFLIGHT_SIZE	((माप_प्रकार)-1 >> ST_MAX_RELATIVE_THROUGHPUT_SHIFT)
#घोषणा ST_VERSION	"0.3.0"

काष्ठा selector अणु
	काष्ठा list_head valid_paths;
	काष्ठा list_head failed_paths;
	spinlock_t lock;
पूर्ण;

काष्ठा path_info अणु
	काष्ठा list_head list;
	काष्ठा dm_path *path;
	अचिन्हित repeat_count;
	अचिन्हित relative_throughput;
	atomic_t in_flight_size;	/* Total size of in-flight I/Os */
पूर्ण;

अटल काष्ठा selector *alloc_selector(व्योम)
अणु
	काष्ठा selector *s = kदो_स्मृति(माप(*s), GFP_KERNEL);

	अगर (s) अणु
		INIT_LIST_HEAD(&s->valid_paths);
		INIT_LIST_HEAD(&s->failed_paths);
		spin_lock_init(&s->lock);
	पूर्ण

	वापस s;
पूर्ण

अटल पूर्णांक st_create(काष्ठा path_selector *ps, अचिन्हित argc, अक्षर **argv)
अणु
	काष्ठा selector *s = alloc_selector();

	अगर (!s)
		वापस -ENOMEM;

	ps->context = s;
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

अटल व्योम st_destroy(काष्ठा path_selector *ps)
अणु
	काष्ठा selector *s = ps->context;

	मुक्त_paths(&s->valid_paths);
	मुक्त_paths(&s->failed_paths);
	kमुक्त(s);
	ps->context = शून्य;
पूर्ण

अटल पूर्णांक st_status(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		     status_type_t type, अक्षर *result, अचिन्हित maxlen)
अणु
	अचिन्हित sz = 0;
	काष्ठा path_info *pi;

	अगर (!path)
		DMEMIT("0 ");
	अन्यथा अणु
		pi = path->pscontext;

		चयन (type) अणु
		हाल STATUSTYPE_INFO:
			DMEMIT("%d %u ", atomic_पढ़ो(&pi->in_flight_size),
			       pi->relative_throughput);
			अवरोध;
		हाल STATUSTYPE_TABLE:
			DMEMIT("%u %u ", pi->repeat_count,
			       pi->relative_throughput);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस sz;
पूर्ण

अटल पूर्णांक st_add_path(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		       पूर्णांक argc, अक्षर **argv, अक्षर **error)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi;
	अचिन्हित repeat_count = ST_MIN_IO;
	अचिन्हित relative_throughput = 1;
	अक्षर dummy;
	अचिन्हित दीर्घ flags;

	/*
	 * Arguments: [<repeat_count> [<relative_throughput>]]
	 * 	<repeat_count>: The number of I/Os beक्रमe चयनing path.
	 * 			If not given, शेष (ST_MIN_IO) is used.
	 * 	<relative_throughput>: The relative throughput value of
	 *			the path among all paths in the path-group.
	 * 			The valid range: 0-<ST_MAX_RELATIVE_THROUGHPUT>
	 *			If not given, minimum value '1' is used.
	 *			If '0' is given, the path isn't selected जबतक
	 * 			other paths having a positive value are
	 * 			available.
	 */
	अगर (argc > 2) अणु
		*error = "service-time ps: incorrect number of arguments";
		वापस -EINVAL;
	पूर्ण

	अगर (argc && (माला_पूछो(argv[0], "%u%c", &repeat_count, &dummy) != 1)) अणु
		*error = "service-time ps: invalid repeat count";
		वापस -EINVAL;
	पूर्ण

	अगर (repeat_count > 1) अणु
		DMWARN_LIMIT("repeat_count > 1 is deprecated, using 1 instead");
		repeat_count = 1;
	पूर्ण

	अगर ((argc == 2) &&
	    (माला_पूछो(argv[1], "%u%c", &relative_throughput, &dummy) != 1 ||
	     relative_throughput > ST_MAX_RELATIVE_THROUGHPUT)) अणु
		*error = "service-time ps: invalid relative_throughput value";
		वापस -EINVAL;
	पूर्ण

	/* allocate the path */
	pi = kदो_स्मृति(माप(*pi), GFP_KERNEL);
	अगर (!pi) अणु
		*error = "service-time ps: Error allocating path context";
		वापस -ENOMEM;
	पूर्ण

	pi->path = path;
	pi->repeat_count = repeat_count;
	pi->relative_throughput = relative_throughput;
	atomic_set(&pi->in_flight_size, 0);

	path->pscontext = pi;

	spin_lock_irqsave(&s->lock, flags);
	list_add_tail(&pi->list, &s->valid_paths);
	spin_unlock_irqrestore(&s->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम st_fail_path(काष्ठा path_selector *ps, काष्ठा dm_path *path)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = path->pscontext;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	list_move(&pi->list, &s->failed_paths);
	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल पूर्णांक st_reinstate_path(काष्ठा path_selector *ps, काष्ठा dm_path *path)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = path->pscontext;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	list_move_tail(&pi->list, &s->valid_paths);
	spin_unlock_irqrestore(&s->lock, flags);

	वापस 0;
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
 * Description:
 * Basically, the service समय is estimated by:
 *     ('pi->in-flight-size' + 'incoming') / 'pi->relative_throughput'
 * To reduce the calculation, some optimizations are made.
 * (See comments अंतरभूत)
 */
अटल पूर्णांक st_compare_load(काष्ठा path_info *pi1, काष्ठा path_info *pi2,
			   माप_प्रकार incoming)
अणु
	माप_प्रकार sz1, sz2, st1, st2;

	sz1 = atomic_पढ़ो(&pi1->in_flight_size);
	sz2 = atomic_पढ़ो(&pi2->in_flight_size);

	/*
	 * Case 1: Both have same throughput value. Choose less loaded path.
	 */
	अगर (pi1->relative_throughput == pi2->relative_throughput)
		वापस sz1 - sz2;

	/*
	 * Case 2a: Both have same load. Choose higher throughput path.
	 * Case 2b: One path has no throughput value. Choose the other one.
	 */
	अगर (sz1 == sz2 ||
	    !pi1->relative_throughput || !pi2->relative_throughput)
		वापस pi2->relative_throughput - pi1->relative_throughput;

	/*
	 * Case 3: Calculate service समय. Choose faster path.
	 *         Service समय using pi1:
	 *             st1 = (sz1 + incoming) / pi1->relative_throughput
	 *         Service समय using pi2:
	 *             st2 = (sz2 + incoming) / pi2->relative_throughput
	 *
	 *         To aव्योम the भागision, transक्रमm the expression to use
	 *         multiplication.
	 *         Because ->relative_throughput > 0 here, अगर st1 < st2,
	 *         the expressions below are the same meaning:
	 *             (sz1 + incoming) / pi1->relative_throughput <
	 *                 (sz2 + incoming) / pi2->relative_throughput
	 *             (sz1 + incoming) * pi2->relative_throughput <
	 *                 (sz2 + incoming) * pi1->relative_throughput
	 *         So use the later one.
	 */
	sz1 += incoming;
	sz2 += incoming;
	अगर (unlikely(sz1 >= ST_MAX_INFLIGHT_SIZE ||
		     sz2 >= ST_MAX_INFLIGHT_SIZE)) अणु
		/*
		 * Size may be too big क्रम multiplying pi->relative_throughput
		 * and overflow.
		 * To aव्योम the overflow and mis-selection, shअगरt करोwn both.
		 */
		sz1 >>= ST_MAX_RELATIVE_THROUGHPUT_SHIFT;
		sz2 >>= ST_MAX_RELATIVE_THROUGHPUT_SHIFT;
	पूर्ण
	st1 = sz1 * pi2->relative_throughput;
	st2 = sz2 * pi1->relative_throughput;
	अगर (st1 != st2)
		वापस st1 - st2;

	/*
	 * Case 4: Service समय is equal. Choose higher throughput path.
	 */
	वापस pi2->relative_throughput - pi1->relative_throughput;
पूर्ण

अटल काष्ठा dm_path *st_select_path(काष्ठा path_selector *ps, माप_प्रकार nr_bytes)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = शून्य, *best = शून्य;
	काष्ठा dm_path *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	अगर (list_empty(&s->valid_paths))
		जाओ out;

	list_क्रम_each_entry(pi, &s->valid_paths, list)
		अगर (!best || (st_compare_load(pi, best, nr_bytes) < 0))
			best = pi;

	अगर (!best)
		जाओ out;

	/* Move most recently used to least preferred to evenly balance. */
	list_move_tail(&best->list, &s->valid_paths);

	ret = best->path;
out:
	spin_unlock_irqrestore(&s->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक st_start_io(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		       माप_प्रकार nr_bytes)
अणु
	काष्ठा path_info *pi = path->pscontext;

	atomic_add(nr_bytes, &pi->in_flight_size);

	वापस 0;
पूर्ण

अटल पूर्णांक st_end_io(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		     माप_प्रकार nr_bytes, u64 start_समय)
अणु
	काष्ठा path_info *pi = path->pscontext;

	atomic_sub(nr_bytes, &pi->in_flight_size);

	वापस 0;
पूर्ण

अटल काष्ठा path_selector_type st_ps = अणु
	.name		= "service-time",
	.module		= THIS_MODULE,
	.table_args	= 2,
	.info_args	= 2,
	.create		= st_create,
	.destroy	= st_destroy,
	.status		= st_status,
	.add_path	= st_add_path,
	.fail_path	= st_fail_path,
	.reinstate_path	= st_reinstate_path,
	.select_path	= st_select_path,
	.start_io	= st_start_io,
	.end_io		= st_end_io,
पूर्ण;

अटल पूर्णांक __init dm_st_init(व्योम)
अणु
	पूर्णांक r = dm_रेजिस्टर_path_selector(&st_ps);

	अगर (r < 0)
		DMERR("register failed %d", r);

	DMINFO("version " ST_VERSION " loaded");

	वापस r;
पूर्ण

अटल व्योम __निकास dm_st_निकास(व्योम)
अणु
	पूर्णांक r = dm_unरेजिस्टर_path_selector(&st_ps);

	अगर (r < 0)
		DMERR("unregister failed %d", r);
पूर्ण

module_init(dm_st_init);
module_निकास(dm_st_निकास);

MODULE_DESCRIPTION(DM_NAME " throughput oriented path selector");
MODULE_AUTHOR("Kiyoshi Ueda <k-ueda@ct.jp.nec.com>");
MODULE_LICENSE("GPL");
