<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * अक्रमom utiility code, क्रम bcache but in theory not specअगरic to bcache
 *
 * Copyright 2010, 2011 Kent Overstreet <kent.overstreet@gmail.com>
 * Copyright 2012 Google, Inc.
 */

#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/types.h>
#समावेश <linux/sched/घड़ी.h>

#समावेश "util.h"

#घोषणा simple_strtoपूर्णांक(c, end, base)	simple_म_से_दीर्घ(c, end, base)
#घोषणा simple_strtouपूर्णांक(c, end, base)	simple_म_से_अदीर्घ(c, end, base)

#घोषणा STRTO_H(name, type)					\
पूर्णांक bch_ ## name ## _h(स्थिर अक्षर *cp, type *res)		\
अणु								\
	पूर्णांक u = 0;						\
	अक्षर *e;						\
	type i = simple_ ## name(cp, &e, 10);			\
								\
	चयन (छोटे(*e)) अणु					\
	शेष:						\
		वापस -EINVAL;					\
	हाल 'y':						\
	हाल 'z':						\
		u++;						\
		fallthrough;					\
	हाल 'e':						\
		u++;						\
		fallthrough;					\
	हाल 'p':						\
		u++;						\
		fallthrough;					\
	हाल 't':						\
		u++;						\
		fallthrough;					\
	हाल 'g':						\
		u++;						\
		fallthrough;					\
	हाल 'm':						\
		u++;						\
		fallthrough;					\
	हाल 'k':						\
		u++;						\
		अगर (e++ == cp)					\
			वापस -EINVAL;				\
		fallthrough;					\
	हाल '\n':						\
	हाल '\0':						\
		अगर (*e == '\n')					\
			e++;					\
	पूर्ण							\
								\
	अगर (*e)							\
		वापस -EINVAL;					\
								\
	जबतक (u--) अणु						\
		अगर ((type) ~0 > 0 &&				\
		    (type) ~0 / 1024 <= i)			\
			वापस -EINVAL;				\
		अगर ((i > 0 && ANYSपूर्णांक_उच्च(type) / 1024 < i) ||	\
		    (i < 0 && -ANYSपूर्णांक_उच्च(type) / 1024 > i))	\
			वापस -EINVAL;				\
		i *= 1024;					\
	पूर्ण							\
								\
	*res = i;						\
	वापस 0;						\
पूर्ण								\

STRTO_H(strtoपूर्णांक, पूर्णांक)
STRTO_H(strtouपूर्णांक, अचिन्हित पूर्णांक)
STRTO_H(म_से_दीर्घl, दीर्घ दीर्घ)
STRTO_H(म_से_अदीर्घl, अचिन्हित दीर्घ दीर्घ)

/**
 * bch_hprपूर्णांक - क्रमmats @v to human पढ़ोable string क्रम sysfs.
 * @buf: the (at least 8 byte) buffer to क्रमmat the result पूर्णांकo.
 * @v: चिन्हित 64 bit पूर्णांकeger
 *
 * Returns the number of bytes used by क्रमmat.
 */
sमाप_प्रकार bch_hprपूर्णांक(अक्षर *buf, पूर्णांक64_t v)
अणु
	अटल स्थिर अक्षर units[] = "?kMGTPEZY";
	पूर्णांक u = 0, t;

	uपूर्णांक64_t q;

	अगर (v < 0)
		q = -v;
	अन्यथा
		q = v;

	/* For as दीर्घ as the number is more than 3 digits, but at least
	 * once, shअगरt right / भागide by 1024.  Keep the reमुख्यder क्रम
	 * a digit after the decimal poपूर्णांक.
	 */
	करो अणु
		u++;

		t = q & ~(~0 << 10);
		q >>= 10;
	पूर्ण जबतक (q >= 1000);

	अगर (v < 0)
		/* '-', up to 3 digits, '.', 1 digit, 1 अक्षरacter, null;
		 * yields 8 bytes.
		 */
		वापस प्र_लिखो(buf, "-%llu.%i%c", q, t * 10 / 1024, units[u]);
	अन्यथा
		वापस प्र_लिखो(buf, "%llu.%i%c", q, t * 10 / 1024, units[u]);
पूर्ण

bool bch_is_zero(स्थिर अक्षर *p, माप_प्रकार n)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < n; i++)
		अगर (p[i])
			वापस false;
	वापस true;
पूर्ण

पूर्णांक bch_parse_uuid(स्थिर अक्षर *s, अक्षर *uuid)
अणु
	माप_प्रकार i, j, x;

	स_रखो(uuid, 0, 16);

	क्रम (i = 0, j = 0;
	     i < म_अखोज(s, "-0123456789:ABCDEFabcdef") && j < 32;
	     i++) अणु
		x = s[i] | 32;

		चयन (x) अणु
		हाल '0'...'9':
			x -= '0';
			अवरोध;
		हाल 'a'...'f':
			x -= 'a' - 10;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		अगर (!(j & 1))
			x <<= 4;
		uuid[j++ >> 1] |= x;
	पूर्ण
	वापस i;
पूर्ण

व्योम bch_समय_stats_update(काष्ठा समय_stats *stats, uपूर्णांक64_t start_समय)
अणु
	uपूर्णांक64_t now, duration, last;

	spin_lock(&stats->lock);

	now		= local_घड़ी();
	duration	= समय_after64(now, start_समय)
		? now - start_समय : 0;
	last		= समय_after64(now, stats->last)
		? now - stats->last : 0;

	stats->max_duration = max(stats->max_duration, duration);

	अगर (stats->last) अणु
		ewma_add(stats->average_duration, duration, 8, 8);

		अगर (stats->average_frequency)
			ewma_add(stats->average_frequency, last, 8, 8);
		अन्यथा
			stats->average_frequency  = last << 8;
	पूर्ण अन्यथा अणु
		stats->average_duration  = duration << 8;
	पूर्ण

	stats->last = now ?: 1;

	spin_unlock(&stats->lock);
पूर्ण

/**
 * bch_next_delay() - update ratelimiting statistics and calculate next delay
 * @d: the काष्ठा bch_ratelimit to update
 * @करोne: the amount of work करोne, in arbitrary units
 *
 * Increment @d by the amount of work करोne, and वापस how दीर्घ to delay in
 * jअगरfies until the next समय to करो some work.
 */
uपूर्णांक64_t bch_next_delay(काष्ठा bch_ratelimit *d, uपूर्णांक64_t करोne)
अणु
	uपूर्णांक64_t now = local_घड़ी();

	d->next += भाग_u64(करोne * NSEC_PER_SEC, atomic_दीर्घ_पढ़ो(&d->rate));

	/* Bound the समय.  Don't let us fall further than 2 seconds behind
	 * (this prevents unnecessary backlog that would make it impossible
	 * to catch up).  If we're ahead of the desired ग_लिखोback rate,
	 * करोn't let us sleep more than 2.5 seconds (so we can notice/respond
	 * अगर the control प्रणाली tells us to speed up!).
	 */
	अगर (समय_beक्रमe64(now + NSEC_PER_SEC * 5LLU / 2LLU, d->next))
		d->next = now + NSEC_PER_SEC * 5LLU / 2LLU;

	अगर (समय_after64(now - NSEC_PER_SEC * 2, d->next))
		d->next = now - NSEC_PER_SEC * 2;

	वापस समय_after64(d->next, now)
		? भाग_u64(d->next - now, NSEC_PER_SEC / HZ)
		: 0;
पूर्ण

/*
 * Generally it isn't good to access .bi_io_vec and .bi_vcnt directly,
 * the preferred way is bio_add_page, but in this हाल, bch_bio_map()
 * supposes that the bvec table is empty, so it is safe to access
 * .bi_vcnt & .bi_io_vec in this way even after multipage bvec is
 * supported.
 */
व्योम bch_bio_map(काष्ठा bio *bio, व्योम *base)
अणु
	माप_प्रकार size = bio->bi_iter.bi_size;
	काष्ठा bio_vec *bv = bio->bi_io_vec;

	BUG_ON(!bio->bi_iter.bi_size);
	BUG_ON(bio->bi_vcnt);

	bv->bv_offset = base ? offset_in_page(base) : 0;
	जाओ start;

	क्रम (; size; bio->bi_vcnt++, bv++) अणु
		bv->bv_offset	= 0;
start:		bv->bv_len	= min_t(माप_प्रकार, PAGE_SIZE - bv->bv_offset,
					size);
		अगर (base) अणु
			bv->bv_page = is_vदो_स्मृति_addr(base)
				? vदो_स्मृति_to_page(base)
				: virt_to_page(base);

			base += bv->bv_len;
		पूर्ण

		size -= bv->bv_len;
	पूर्ण
पूर्ण

/**
 * bch_bio_alloc_pages - allocates a single page क्रम each bvec in a bio
 * @bio: bio to allocate pages क्रम
 * @gfp_mask: flags क्रम allocation
 *
 * Allocates pages up to @bio->bi_vcnt.
 *
 * Returns 0 on success, -ENOMEM on failure. On failure, any allocated pages are
 * मुक्तd.
 */
पूर्णांक bch_bio_alloc_pages(काष्ठा bio *bio, gfp_t gfp_mask)
अणु
	पूर्णांक i;
	काष्ठा bio_vec *bv;

	/*
	 * This is called on freshly new bio, so it is safe to access the
	 * bvec table directly.
	 */
	क्रम (i = 0, bv = bio->bi_io_vec; i < bio->bi_vcnt; bv++, i++) अणु
		bv->bv_page = alloc_page(gfp_mask);
		अगर (!bv->bv_page) अणु
			जबतक (--bv >= bio->bi_io_vec)
				__मुक्त_page(bv->bv_page);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
