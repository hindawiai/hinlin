<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* FS-Cache latency histogram
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा FSCACHE_DEBUG_LEVEL THREAD
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश "internal.h"

atomic_t fscache_obj_instantiate_histogram[HZ];
atomic_t fscache_objs_histogram[HZ];
atomic_t fscache_ops_histogram[HZ];
atomic_t fscache_retrieval_delay_histogram[HZ];
atomic_t fscache_retrieval_histogram[HZ];

/*
 * display the समय-taken histogram
 */
अटल पूर्णांक fscache_histogram_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ index;
	अचिन्हित n[5], t;

	चयन ((अचिन्हित दीर्घ) v) अणु
	हाल 1:
		seq_माला_दो(m, "JIFS  SECS  OBJ INST  OP RUNS   OBJ RUNS  RETRV DLY RETRIEVLS\n");
		वापस 0;
	हाल 2:
		seq_माला_दो(m, "===== ===== ========= ========= ========= ========= =========\n");
		वापस 0;
	शेष:
		index = (अचिन्हित दीर्घ) v - 3;
		n[0] = atomic_पढ़ो(&fscache_obj_instantiate_histogram[index]);
		n[1] = atomic_पढ़ो(&fscache_ops_histogram[index]);
		n[2] = atomic_पढ़ो(&fscache_objs_histogram[index]);
		n[3] = atomic_पढ़ो(&fscache_retrieval_delay_histogram[index]);
		n[4] = atomic_पढ़ो(&fscache_retrieval_histogram[index]);
		अगर (!(n[0] | n[1] | n[2] | n[3] | n[4]))
			वापस 0;

		t = (index * 1000) / HZ;

		seq_म_लिखो(m, "%4lu  0.%03u %9u %9u %9u %9u %9u\n",
			   index, t, n[0], n[1], n[2], n[3], n[4]);
		वापस 0;
	पूर्ण
पूर्ण

/*
 * set up the iterator to start पढ़ोing from the first line
 */
अटल व्योम *fscache_histogram_start(काष्ठा seq_file *m, loff_t *_pos)
अणु
	अगर ((अचिन्हित दीर्घ दीर्घ)*_pos >= HZ + 2)
		वापस शून्य;
	अगर (*_pos == 0)
		*_pos = 1;
	वापस (व्योम *)(अचिन्हित दीर्घ) *_pos;
पूर्ण

/*
 * move to the next line
 */
अटल व्योम *fscache_histogram_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस (अचिन्हित दीर्घ दीर्घ)*pos > HZ + 2 ?
		शून्य : (व्योम *)(अचिन्हित दीर्घ) *pos;
पूर्ण

/*
 * clean up after पढ़ोing
 */
अटल व्योम fscache_histogram_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations fscache_histogram_ops = अणु
	.start		= fscache_histogram_start,
	.stop		= fscache_histogram_stop,
	.next		= fscache_histogram_next,
	.show		= fscache_histogram_show,
पूर्ण;
