<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PAGE_COUNTER_H
#घोषणा _LINUX_PAGE_COUNTER_H

#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/page.h>

काष्ठा page_counter अणु
	atomic_दीर्घ_t usage;
	अचिन्हित दीर्घ min;
	अचिन्हित दीर्घ low;
	अचिन्हित दीर्घ high;
	अचिन्हित दीर्घ max;

	/* effective memory.min and memory.min usage tracking */
	अचिन्हित दीर्घ emin;
	atomic_दीर्घ_t min_usage;
	atomic_दीर्घ_t children_min_usage;

	/* effective memory.low and memory.low usage tracking */
	अचिन्हित दीर्घ elow;
	atomic_दीर्घ_t low_usage;
	atomic_दीर्घ_t children_low_usage;

	/* legacy */
	अचिन्हित दीर्घ watermark;
	अचिन्हित दीर्घ failcnt;

	/*
	 * 'parent' is placed here to be far from 'usage' to reduce
	 * cache false sharing, as 'usage' is written mostly जबतक
	 * parent is frequently पढ़ो क्रम cgroup's hierarchical
	 * counting nature.
	 */
	काष्ठा page_counter *parent;
पूर्ण;

#अगर BITS_PER_LONG == 32
#घोषणा PAGE_COUNTER_MAX दीर्घ_उच्च
#अन्यथा
#घोषणा PAGE_COUNTER_MAX (दीर्घ_उच्च / PAGE_SIZE)
#पूर्ण_अगर

अटल अंतरभूत व्योम page_counter_init(काष्ठा page_counter *counter,
				     काष्ठा page_counter *parent)
अणु
	atomic_दीर्घ_set(&counter->usage, 0);
	counter->max = PAGE_COUNTER_MAX;
	counter->parent = parent;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ page_counter_पढ़ो(काष्ठा page_counter *counter)
अणु
	वापस atomic_दीर्घ_पढ़ो(&counter->usage);
पूर्ण

व्योम page_counter_cancel(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages);
व्योम page_counter_अक्षरge(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages);
bool page_counter_try_अक्षरge(काष्ठा page_counter *counter,
			     अचिन्हित दीर्घ nr_pages,
			     काष्ठा page_counter **fail);
व्योम page_counter_unअक्षरge(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages);
व्योम page_counter_set_min(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages);
व्योम page_counter_set_low(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages);

अटल अंतरभूत व्योम page_counter_set_high(काष्ठा page_counter *counter,
					 अचिन्हित दीर्घ nr_pages)
अणु
	WRITE_ONCE(counter->high, nr_pages);
पूर्ण

पूर्णांक page_counter_set_max(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages);
पूर्णांक page_counter_memparse(स्थिर अक्षर *buf, स्थिर अक्षर *max,
			  अचिन्हित दीर्घ *nr_pages);

अटल अंतरभूत व्योम page_counter_reset_watermark(काष्ठा page_counter *counter)
अणु
	counter->watermark = page_counter_पढ़ो(counter);
पूर्ण

#पूर्ण_अगर /* _LINUX_PAGE_COUNTER_H */
