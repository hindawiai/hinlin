<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _BCACHE_UTIL_H
#घोषणा _BCACHE_UTIL_H

#समावेश <linux/blkdev.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/llist.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/crc64.h>

#समावेश "closure.h"

#घोषणा PAGE_SECTORS		(PAGE_SIZE / 512)

काष्ठा closure;

#अगर_घोषित CONFIG_BCACHE_DEBUG

#घोषणा EBUG_ON(cond)			BUG_ON(cond)
#घोषणा atomic_dec_bug(v)	BUG_ON(atomic_dec_वापस(v) < 0)
#घोषणा atomic_inc_bug(v, i)	BUG_ON(atomic_inc_वापस(v) <= i)

#अन्यथा /* DEBUG */

#घोषणा EBUG_ON(cond)		करो अणु अगर (cond) करो अणुपूर्ण जबतक (0); पूर्ण जबतक (0)
#घोषणा atomic_dec_bug(v)	atomic_dec(v)
#घोषणा atomic_inc_bug(v, i)	atomic_inc(v)

#पूर्ण_अगर

#घोषणा DECLARE_HEAP(type, name)					\
	काष्ठा अणु							\
		माप_प्रकार size, used;					\
		type *data;						\
	पूर्ण name

#घोषणा init_heap(heap, _size, gfp)					\
(अणु									\
	माप_प्रकार _bytes;							\
	(heap)->used = 0;						\
	(heap)->size = (_size);						\
	_bytes = (heap)->size * माप(*(heap)->data);			\
	(heap)->data = kvदो_स्मृति(_bytes, (gfp) & GFP_KERNEL);		\
	(heap)->data;							\
पूर्ण)

#घोषणा मुक्त_heap(heap)							\
करो अणु									\
	kvमुक्त((heap)->data);						\
	(heap)->data = शून्य;						\
पूर्ण जबतक (0)

#घोषणा heap_swap(h, i, j)	swap((h)->data[i], (h)->data[j])

#घोषणा heap_sअगरt(h, i, cmp)						\
करो अणु									\
	माप_प्रकार _r, _j = i;						\
									\
	क्रम (; _j * 2 + 1 < (h)->used; _j = _r) अणु			\
		_r = _j * 2 + 1;					\
		अगर (_r + 1 < (h)->used &&				\
		    cmp((h)->data[_r], (h)->data[_r + 1]))		\
			_r++;						\
									\
		अगर (cmp((h)->data[_r], (h)->data[_j]))			\
			अवरोध;						\
		heap_swap(h, _r, _j);					\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा heap_sअगरt_करोwn(h, i, cmp)					\
करो अणु									\
	जबतक (i) अणु							\
		माप_प्रकार p = (i - 1) / 2;					\
		अगर (cmp((h)->data[i], (h)->data[p]))			\
			अवरोध;						\
		heap_swap(h, i, p);					\
		i = p;							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा heap_add(h, d, cmp)						\
(अणु									\
	bool _r = !heap_full(h);					\
	अगर (_r) अणु							\
		माप_प्रकार _i = (h)->used++;				\
		(h)->data[_i] = d;					\
									\
		heap_sअगरt_करोwn(h, _i, cmp);				\
		heap_sअगरt(h, _i, cmp);					\
	पूर्ण								\
	_r;								\
पूर्ण)

#घोषणा heap_pop(h, d, cmp)						\
(अणु									\
	bool _r = (h)->used;						\
	अगर (_r) अणु							\
		(d) = (h)->data[0];					\
		(h)->used--;						\
		heap_swap(h, 0, (h)->used);				\
		heap_sअगरt(h, 0, cmp);					\
	पूर्ण								\
	_r;								\
पूर्ण)

#घोषणा heap_peek(h)	((h)->used ? (h)->data[0] : शून्य)

#घोषणा heap_full(h)	((h)->used == (h)->size)

#घोषणा DECLARE_FIFO(type, name)					\
	काष्ठा अणु							\
		माप_प्रकार front, back, size, mask;				\
		type *data;						\
	पूर्ण name

#घोषणा fअगरo_क्रम_each(c, fअगरo, iter)					\
	क्रम (iter = (fअगरo)->front;					\
	     c = (fअगरo)->data[iter], iter != (fअगरo)->back;		\
	     iter = (iter + 1) & (fअगरo)->mask)

#घोषणा __init_fअगरo(fअगरo, gfp)						\
(अणु									\
	माप_प्रकार _allocated_size, _bytes;					\
	BUG_ON(!(fअगरo)->size);						\
									\
	_allocated_size = roundup_घात_of_two((fअगरo)->size + 1);		\
	_bytes = _allocated_size * माप(*(fअगरo)->data);		\
									\
	(fअगरo)->mask = _allocated_size - 1;				\
	(fअगरo)->front = (fअगरo)->back = 0;				\
									\
	(fअगरo)->data = kvदो_स्मृति(_bytes, (gfp) & GFP_KERNEL);		\
	(fअगरo)->data;							\
पूर्ण)

#घोषणा init_fअगरo_exact(fअगरo, _size, gfp)				\
(अणु									\
	(fअगरo)->size = (_size);						\
	__init_fअगरo(fअगरo, gfp);						\
पूर्ण)

#घोषणा init_fअगरo(fअगरo, _size, gfp)					\
(अणु									\
	(fअगरo)->size = (_size);						\
	अगर ((fअगरo)->size > 4)						\
		(fअगरo)->size = roundup_घात_of_two((fअगरo)->size) - 1;	\
	__init_fअगरo(fअगरo, gfp);						\
पूर्ण)

#घोषणा मुक्त_fअगरo(fअगरo)							\
करो अणु									\
	kvमुक्त((fअगरo)->data);						\
	(fअगरo)->data = शून्य;						\
पूर्ण जबतक (0)

#घोषणा fअगरo_used(fअगरo)		(((fअगरo)->back - (fअगरo)->front) & (fअगरo)->mask)
#घोषणा fअगरo_मुक्त(fअगरo)		((fअगरo)->size - fअगरo_used(fअगरo))

#घोषणा fअगरo_empty(fअगरo)	(!fअगरo_used(fअगरo))
#घोषणा fअगरo_full(fअगरo)		(!fअगरo_मुक्त(fअगरo))

#घोषणा fअगरo_front(fअगरo)	((fअगरo)->data[(fअगरo)->front])
#घोषणा fअगरo_back(fअगरo)							\
	((fअगरo)->data[((fअगरo)->back - 1) & (fअगरo)->mask])

#घोषणा fअगरo_idx(fअगरo, p)	(((p) - &fअगरo_front(fअगरo)) & (fअगरo)->mask)

#घोषणा fअगरo_push_back(fअगरo, i)						\
(अणु									\
	bool _r = !fअगरo_full((fअगरo));					\
	अगर (_r) अणु							\
		(fअगरo)->data[(fअगरo)->back++] = (i);			\
		(fअगरo)->back &= (fअगरo)->mask;				\
	पूर्ण								\
	_r;								\
पूर्ण)

#घोषणा fअगरo_pop_front(fअगरo, i)						\
(अणु									\
	bool _r = !fअगरo_empty((fअगरo));					\
	अगर (_r) अणु							\
		(i) = (fअगरo)->data[(fअगरo)->front++];			\
		(fअगरo)->front &= (fअगरo)->mask;				\
	पूर्ण								\
	_r;								\
पूर्ण)

#घोषणा fअगरo_push_front(fअगरo, i)					\
(अणु									\
	bool _r = !fअगरo_full((fअगरo));					\
	अगर (_r) अणु							\
		--(fअगरo)->front;					\
		(fअगरo)->front &= (fअगरo)->mask;				\
		(fअगरo)->data[(fअगरo)->front] = (i);			\
	पूर्ण								\
	_r;								\
पूर्ण)

#घोषणा fअगरo_pop_back(fअगरo, i)						\
(अणु									\
	bool _r = !fअगरo_empty((fअगरo));					\
	अगर (_r) अणु							\
		--(fअगरo)->back;						\
		(fअगरo)->back &= (fअगरo)->mask;				\
		(i) = (fअगरo)->data[(fअगरo)->back]			\
	पूर्ण								\
	_r;								\
पूर्ण)

#घोषणा fअगरo_push(fअगरo, i)	fअगरo_push_back(fअगरo, (i))
#घोषणा fअगरo_pop(fअगरo, i)	fअगरo_pop_front(fअगरo, (i))

#घोषणा fअगरo_swap(l, r)							\
करो अणु									\
	swap((l)->front, (r)->front);					\
	swap((l)->back, (r)->back);					\
	swap((l)->size, (r)->size);					\
	swap((l)->mask, (r)->mask);					\
	swap((l)->data, (r)->data);					\
पूर्ण जबतक (0)

#घोषणा fअगरo_move(dest, src)						\
करो अणु									\
	typeof(*((dest)->data)) _t;					\
	जबतक (!fअगरo_full(dest) &&					\
	       fअगरo_pop(src, _t))					\
		fअगरo_push(dest, _t);					\
पूर्ण जबतक (0)

/*
 * Simple array based allocator - pपुनः_स्मृतिates a number of elements and you can
 * never allocate more than that, also has no locking.
 *
 * Handy because अगर you know you only need a fixed number of elements you करोn't
 * have to worry about memory allocation failure, and someबार a mempool isn't
 * what you want.
 *
 * We treat the मुक्त elements as entries in a singly linked list, and the
 * मुक्तlist as a stack - allocating and मुक्तing push and pop off the मुक्तlist.
 */

#घोषणा DECLARE_ARRAY_ALLOCATOR(type, name, size)			\
	काष्ठा अणु							\
		type	*मुक्तlist;					\
		type	data[size];					\
	पूर्ण name

#घोषणा array_alloc(array)						\
(अणु									\
	typeof((array)->मुक्तlist) _ret = (array)->मुक्तlist;		\
									\
	अगर (_ret)							\
		(array)->मुक्तlist = *((typeof((array)->मुक्तlist) *) _ret);\
									\
	_ret;								\
पूर्ण)

#घोषणा array_मुक्त(array, ptr)						\
करो अणु									\
	typeof((array)->मुक्तlist) _ptr = ptr;				\
									\
	*((typeof((array)->मुक्तlist) *) _ptr) = (array)->मुक्तlist;	\
	(array)->मुक्तlist = _ptr;					\
पूर्ण जबतक (0)

#घोषणा array_allocator_init(array)					\
करो अणु									\
	typeof((array)->मुक्तlist) _i;					\
									\
	BUILD_BUG_ON(माप((array)->data[0]) < माप(व्योम *));	\
	(array)->मुक्तlist = शून्य;					\
									\
	क्रम (_i = (array)->data;					\
	     _i < (array)->data + ARRAY_SIZE((array)->data);		\
	     _i++)							\
		array_मुक्त(array, _i);					\
पूर्ण जबतक (0)

#घोषणा array_मुक्तlist_empty(array)	((array)->मुक्तlist == शून्य)

#घोषणा ANYSपूर्णांक_उच्च(t)							\
	((((t) 1 << (माप(t) * 8 - 2)) - (t) 1) * (t) 2 + (t) 1)

पूर्णांक bch_strtoपूर्णांक_h(स्थिर अक्षर *cp, पूर्णांक *res);
पूर्णांक bch_strtouपूर्णांक_h(स्थिर अक्षर *cp, अचिन्हित पूर्णांक *res);
पूर्णांक bch_म_से_दीर्घl_h(स्थिर अक्षर *cp, दीर्घ दीर्घ *res);
पूर्णांक bch_म_से_अदीर्घl_h(स्थिर अक्षर *cp, अचिन्हित दीर्घ दीर्घ *res);

अटल अंतरभूत पूर्णांक bch_म_से_दीर्घ_h(स्थिर अक्षर *cp, दीर्घ *res)
अणु
#अगर BITS_PER_LONG == 32
	वापस bch_strtoपूर्णांक_h(cp, (पूर्णांक *) res);
#अन्यथा
	वापस bch_म_से_दीर्घl_h(cp, (दीर्घ दीर्घ *) res);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक bch_म_से_अदीर्घ_h(स्थिर अक्षर *cp, दीर्घ *res)
अणु
#अगर BITS_PER_LONG == 32
	वापस bch_strtouपूर्णांक_h(cp, (अचिन्हित पूर्णांक *) res);
#अन्यथा
	वापस bch_म_से_अदीर्घl_h(cp, (अचिन्हित दीर्घ दीर्घ *) res);
#पूर्ण_अगर
पूर्ण

#घोषणा strtoi_h(cp, res)						\
	(__builtin_types_compatible_p(typeof(*res), पूर्णांक)		\
	? bch_strtoपूर्णांक_h(cp, (व्योम *) res)				\
	: __builtin_types_compatible_p(typeof(*res), दीर्घ)		\
	? bch_म_से_दीर्घ_h(cp, (व्योम *) res)				\
	: __builtin_types_compatible_p(typeof(*res), दीर्घ दीर्घ)		\
	? bch_म_से_दीर्घl_h(cp, (व्योम *) res)				\
	: __builtin_types_compatible_p(typeof(*res), अचिन्हित पूर्णांक)	\
	? bch_strtouपूर्णांक_h(cp, (व्योम *) res)				\
	: __builtin_types_compatible_p(typeof(*res), अचिन्हित दीर्घ)	\
	? bch_म_से_अदीर्घ_h(cp, (व्योम *) res)				\
	: __builtin_types_compatible_p(typeof(*res), अचिन्हित दीर्घ दीर्घ)\
	? bch_म_से_अदीर्घl_h(cp, (व्योम *) res) : -EINVAL)

#घोषणा म_से_अदीर्घ_safe(cp, var)						\
(अणु									\
	अचिन्हित दीर्घ _v;						\
	पूर्णांक _r = kम_से_अदीर्घ(cp, 10, &_v);					\
	अगर (!_r)							\
		var = _v;						\
	_r;								\
पूर्ण)

#घोषणा म_से_अदीर्घ_safe_clamp(cp, var, min, max)				\
(अणु									\
	अचिन्हित दीर्घ _v;						\
	पूर्णांक _r = kम_से_अदीर्घ(cp, 10, &_v);					\
	अगर (!_r)							\
		var = clamp_t(typeof(var), _v, min, max);		\
	_r;								\
पूर्ण)

#घोषणा snprपूर्णांक(buf, size, var)						\
	snम_लिखो(buf, size,						\
		__builtin_types_compatible_p(typeof(var), पूर्णांक)		\
		     ? "%i\n" :						\
		__builtin_types_compatible_p(typeof(var), अचिन्हित पूर्णांक)	\
		     ? "%u\n" :						\
		__builtin_types_compatible_p(typeof(var), दीर्घ)		\
		     ? "%li\n" :					\
		__builtin_types_compatible_p(typeof(var), अचिन्हित दीर्घ)\
		     ? "%lu\n" :					\
		__builtin_types_compatible_p(typeof(var), पूर्णांक64_t)	\
		     ? "%lli\n" :					\
		__builtin_types_compatible_p(typeof(var), uपूर्णांक64_t)	\
		     ? "%llu\n" :					\
		__builtin_types_compatible_p(typeof(var), स्थिर अक्षर *)	\
		     ? "%s\n" : "%i\n", var)

sमाप_प्रकार bch_hprपूर्णांक(अक्षर *buf, पूर्णांक64_t v);

bool bch_is_zero(स्थिर अक्षर *p, माप_प्रकार n);
पूर्णांक bch_parse_uuid(स्थिर अक्षर *s, अक्षर *uuid);

काष्ठा समय_stats अणु
	spinlock_t	lock;
	/*
	 * all fields are in nanoseconds, averages are ewmas stored left shअगरted
	 * by 8
	 */
	uपूर्णांक64_t	max_duration;
	uपूर्णांक64_t	average_duration;
	uपूर्णांक64_t	average_frequency;
	uपूर्णांक64_t	last;
पूर्ण;

व्योम bch_समय_stats_update(काष्ठा समय_stats *stats, uपूर्णांक64_t समय);

अटल अंतरभूत अचिन्हित पूर्णांक local_घड़ी_us(व्योम)
अणु
	वापस local_घड़ी() >> 10;
पूर्ण

#घोषणा NSEC_PER_ns			1L
#घोषणा NSEC_PER_us			NSEC_PER_USEC
#घोषणा NSEC_PER_ms			NSEC_PER_MSEC
#घोषणा NSEC_PER_sec			NSEC_PER_SEC

#घोषणा __prपूर्णांक_समय_stat(stats, name, stat, units)			\
	sysfs_prपूर्णांक(name ## _ ## stat ## _ ## units,			\
		    भाग_u64((stats)->stat >> 8, NSEC_PER_ ## units))

#घोषणा sysfs_prपूर्णांक_समय_stats(stats, name,				\
			       frequency_units,				\
			       duration_units)				\
करो अणु									\
	__prपूर्णांक_समय_stat(stats, name,					\
			  average_frequency,	frequency_units);	\
	__prपूर्णांक_समय_stat(stats, name,					\
			  average_duration,	duration_units);	\
	sysfs_prपूर्णांक(name ## _ ##max_duration ## _ ## duration_units,	\
			भाग_u64((stats)->max_duration,			\
				NSEC_PER_ ## duration_units));		\
									\
	sysfs_prपूर्णांक(name ## _last_ ## frequency_units, (stats)->last	\
		    ? भाग_s64(local_घड़ी() - (stats)->last,		\
			      NSEC_PER_ ## frequency_units)		\
		    : -1LL);						\
पूर्ण जबतक (0)

#घोषणा sysfs_समय_stats_attribute(name,				\
				   frequency_units,			\
				   duration_units)			\
पढ़ो_attribute(name ## _average_frequency_ ## frequency_units);		\
पढ़ो_attribute(name ## _average_duration_ ## duration_units);		\
पढ़ो_attribute(name ## _max_duration_ ## duration_units);		\
पढ़ो_attribute(name ## _last_ ## frequency_units)

#घोषणा sysfs_समय_stats_attribute_list(name,				\
					frequency_units,		\
					duration_units)			\
&sysfs_ ## name ## _average_frequency_ ## frequency_units,		\
&sysfs_ ## name ## _average_duration_ ## duration_units,		\
&sysfs_ ## name ## _max_duration_ ## duration_units,			\
&sysfs_ ## name ## _last_ ## frequency_units,

#घोषणा ewma_add(ewma, val, weight, factor)				\
(अणु									\
	(ewma) *= (weight) - 1;						\
	(ewma) += (val) << factor;					\
	(ewma) /= (weight);						\
	(ewma) >> factor;						\
पूर्ण)

काष्ठा bch_ratelimit अणु
	/* Next समय we want to करो some work, in nanoseconds */
	uपूर्णांक64_t		next;

	/*
	 * Rate at which we want to करो work, in units per second
	 * The units here correspond to the units passed to bch_next_delay()
	 */
	atomic_दीर्घ_t		rate;
पूर्ण;

अटल अंतरभूत व्योम bch_ratelimit_reset(काष्ठा bch_ratelimit *d)
अणु
	d->next = local_घड़ी();
पूर्ण

uपूर्णांक64_t bch_next_delay(काष्ठा bch_ratelimit *d, uपूर्णांक64_t करोne);

#घोषणा __DIV_SAFE(n, d, zero)						\
(अणु									\
	typeof(n) _n = (n);						\
	typeof(d) _d = (d);						\
	_d ? _n / _d : zero;						\
पूर्ण)

#घोषणा DIV_SAFE(n, d)	__DIV_SAFE(n, d, 0)

#घोषणा container_of_or_null(ptr, type, member)				\
(अणु									\
	typeof(ptr) _ptr = ptr;						\
	_ptr ? container_of(_ptr, type, member) : शून्य;			\
पूर्ण)

#घोषणा RB_INSERT(root, new, member, cmp)				\
(अणु									\
	__label__ dup;							\
	काष्ठा rb_node **n = &(root)->rb_node, *parent = शून्य;		\
	typeof(new) this;						\
	पूर्णांक res, ret = -1;						\
									\
	जबतक (*n) अणु							\
		parent = *n;						\
		this = container_of(*n, typeof(*(new)), member);	\
		res = cmp(new, this);					\
		अगर (!res)						\
			जाओ dup;					\
		n = res < 0						\
			? &(*n)->rb_left				\
			: &(*n)->rb_right;				\
	पूर्ण								\
									\
	rb_link_node(&(new)->member, parent, n);			\
	rb_insert_color(&(new)->member, root);				\
	ret = 0;							\
dup:									\
	ret;								\
पूर्ण)

#घोषणा RB_SEARCH(root, search, member, cmp)				\
(अणु									\
	काष्ठा rb_node *n = (root)->rb_node;				\
	typeof(&(search)) this, ret = शून्य;				\
	पूर्णांक res;							\
									\
	जबतक (n) अणु							\
		this = container_of(n, typeof(search), member);		\
		res = cmp(&(search), this);				\
		अगर (!res) अणु						\
			ret = this;					\
			अवरोध;						\
		पूर्ण							\
		n = res < 0						\
			? n->rb_left					\
			: n->rb_right;					\
	पूर्ण								\
	ret;								\
पूर्ण)

#घोषणा RB_GREATER(root, search, member, cmp)				\
(अणु									\
	काष्ठा rb_node *n = (root)->rb_node;				\
	typeof(&(search)) this, ret = शून्य;				\
	पूर्णांक res;							\
									\
	जबतक (n) अणु							\
		this = container_of(n, typeof(search), member);		\
		res = cmp(&(search), this);				\
		अगर (res < 0) अणु						\
			ret = this;					\
			n = n->rb_left;					\
		पूर्ण अन्यथा							\
			n = n->rb_right;				\
	पूर्ण								\
	ret;								\
पूर्ण)

#घोषणा RB_FIRST(root, type, member)					\
	container_of_or_null(rb_first(root), type, member)

#घोषणा RB_LAST(root, type, member)					\
	container_of_or_null(rb_last(root), type, member)

#घोषणा RB_NEXT(ptr, member)						\
	container_of_or_null(rb_next(&(ptr)->member), typeof(*ptr), member)

#घोषणा RB_PREV(ptr, member)						\
	container_of_or_null(rb_prev(&(ptr)->member), typeof(*ptr), member)

अटल अंतरभूत uपूर्णांक64_t bch_crc64(स्थिर व्योम *p, माप_प्रकार len)
अणु
	uपूर्णांक64_t crc = 0xffffffffffffffffULL;

	crc = crc64_be(crc, p, len);
	वापस crc ^ 0xffffffffffffffffULL;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t bch_crc64_update(uपूर्णांक64_t crc,
					स्थिर व्योम *p,
					माप_प्रकार len)
अणु
	crc = crc64_be(crc, p, len);
	वापस crc;
पूर्ण

/*
 * A stepwise-linear pseuकरो-exponential.  This वापसs 1 << (x >>
 * frac_bits), with the less-signअगरicant bits filled in by linear
 * पूर्णांकerpolation.
 *
 * This can also be पूर्णांकerpreted as a भग्नing-poपूर्णांक number क्रमmat,
 * where the low frac_bits are the mantissa (with implicit leading
 * 1 bit), and the more signअगरicant bits are the exponent.
 * The वापस value is 1.mantissa * 2^exponent.
 *
 * The way this is used, fract_bits is 6 and the largest possible
 * input is CONGESTED_MAX-1 = 1023 (exponent 16, mantissa 0x1.fc),
 * so the maximum output is 0x1fc00.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fract_exp_two(अचिन्हित पूर्णांक x,
					 अचिन्हित पूर्णांक fract_bits)
अणु
	अचिन्हित पूर्णांक mantissa = 1 << fract_bits;	/* Implicit bit */

	mantissa += x & (mantissa - 1);
	x >>= fract_bits;	/* The exponent */
	/* Largest पूर्णांकermediate value 0x7f0000 */
	वापस mantissa << x >> fract_bits;
पूर्ण

व्योम bch_bio_map(काष्ठा bio *bio, व्योम *base);
पूर्णांक bch_bio_alloc_pages(काष्ठा bio *bio, gfp_t gfp_mask);

अटल अंतरभूत sector_t bdev_sectors(काष्ठा block_device *bdev)
अणु
	वापस bdev->bd_inode->i_size >> 9;
पूर्ण
#पूर्ण_अगर /* _BCACHE_UTIL_H */
