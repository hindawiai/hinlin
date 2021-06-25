<शैली गुरु>
#अगर_अघोषित __PERF_MMAP_H
#घोषणा __PERF_MMAP_H 1

#समावेश <पूर्णांकernal/mmap.h>
#समावेश <linux/compiler.h>
#समावेश <linux/refcount.h>
#समावेश <linux/types.h>
#समावेश <linux/ring_buffer.h>
#समावेश <stdbool.h>
#समावेश <pthपढ़ो.h> // क्रम cpu_set_t
#अगर_घोषित HAVE_AIO_SUPPORT
#समावेश <aपन.स>
#पूर्ण_अगर
#समावेश "auxtrace.h"
#समावेश "event.h"

काष्ठा aiocb;

काष्ठा mmap_cpu_mask अणु
	अचिन्हित दीर्घ *bits;
	माप_प्रकार nbits;
पूर्ण;

#घोषणा MMAP_CPU_MASK_BYTES(m) \
	(BITS_TO_LONGS(((काष्ठा mmap_cpu_mask *)m)->nbits) * माप(अचिन्हित दीर्घ))

/**
 * काष्ठा mmap - perf's ring buffer mmap details
 *
 * @refcnt - e.g. code using PERF_EVENT_IOC_SET_OUTPUT to share this
 */
काष्ठा mmap अणु
	काष्ठा perf_mmap	core;
	काष्ठा auxtrace_mmap auxtrace_mmap;
#अगर_घोषित HAVE_AIO_SUPPORT
	काष्ठा अणु
		व्योम		 **data;
		काष्ठा aiocb	 *cblocks;
		काष्ठा aiocb	 **aiocb;
		पूर्णांक		 nr_cblocks;
	पूर्ण aio;
#पूर्ण_अगर
	काष्ठा mmap_cpu_mask	affinity_mask;
	व्योम		*data;
	पूर्णांक		comp_level;
पूर्ण;

काष्ठा mmap_params अणु
	काष्ठा perf_mmap_param core;
	पूर्णांक nr_cblocks, affinity, flush, comp_level;
	काष्ठा auxtrace_mmap_params auxtrace_mp;
पूर्ण;

पूर्णांक mmap__mmap(काष्ठा mmap *map, काष्ठा mmap_params *mp, पूर्णांक fd, पूर्णांक cpu);
व्योम mmap__munmap(काष्ठा mmap *map);

जोड़ perf_event *perf_mmap__पढ़ो_क्रमward(काष्ठा mmap *map);

पूर्णांक perf_mmap__push(काष्ठा mmap *md, व्योम *to,
		    पूर्णांक push(काष्ठा mmap *map, व्योम *to, व्योम *buf, माप_प्रकार size));

माप_प्रकार mmap__mmap_len(काष्ठा mmap *map);

व्योम mmap_cpu_mask__scnम_लिखो(काष्ठा mmap_cpu_mask *mask, स्थिर अक्षर *tag);

#पूर्ण_अगर /*__PERF_MMAP_H */
