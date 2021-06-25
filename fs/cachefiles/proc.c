<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* CacheFiles statistics
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश "internal.h"

atomic_t cachefiles_lookup_histogram[HZ];
atomic_t cachefiles_सूची_गढ़ो_histogram[HZ];
atomic_t cachefiles_create_histogram[HZ];

/*
 * display the latency histogram
 */
अटल पूर्णांक cachefiles_histogram_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ index;
	अचिन्हित x, y, z, t;

	चयन ((अचिन्हित दीर्घ) v) अणु
	हाल 1:
		seq_माला_दो(m, "JIFS  SECS  LOOKUPS   MKDIRS    CREATES\n");
		वापस 0;
	हाल 2:
		seq_माला_दो(m, "===== ===== ========= ========= =========\n");
		वापस 0;
	शेष:
		index = (अचिन्हित दीर्घ) v - 3;
		x = atomic_पढ़ो(&cachefiles_lookup_histogram[index]);
		y = atomic_पढ़ो(&cachefiles_सूची_गढ़ो_histogram[index]);
		z = atomic_पढ़ो(&cachefiles_create_histogram[index]);
		अगर (x == 0 && y == 0 && z == 0)
			वापस 0;

		t = (index * 1000) / HZ;

		seq_म_लिखो(m, "%4lu  0.%03u %9u %9u %9u\n", index, t, x, y, z);
		वापस 0;
	पूर्ण
पूर्ण

/*
 * set up the iterator to start पढ़ोing from the first line
 */
अटल व्योम *cachefiles_histogram_start(काष्ठा seq_file *m, loff_t *_pos)
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
अटल व्योम *cachefiles_histogram_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस (अचिन्हित दीर्घ दीर्घ)*pos > HZ + 2 ?
		शून्य : (व्योम *)(अचिन्हित दीर्घ) *pos;
पूर्ण

/*
 * clean up after पढ़ोing
 */
अटल व्योम cachefiles_histogram_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations cachefiles_histogram_ops = अणु
	.start		= cachefiles_histogram_start,
	.stop		= cachefiles_histogram_stop,
	.next		= cachefiles_histogram_next,
	.show		= cachefiles_histogram_show,
पूर्ण;

/*
 * initialise the /proc/fs/cachefiles/ directory
 */
पूर्णांक __init cachefiles_proc_init(व्योम)
अणु
	_enter("");

	अगर (!proc_सूची_गढ़ो("fs/cachefiles", शून्य))
		जाओ error_dir;

	अगर (!proc_create_seq("fs/cachefiles/histogram", S_IFREG | 0444, शून्य,
			 &cachefiles_histogram_ops))
		जाओ error_histogram;

	_leave(" = 0");
	वापस 0;

error_histogram:
	हटाओ_proc_entry("fs/cachefiles", शून्य);
error_dir:
	_leave(" = -ENOMEM");
	वापस -ENOMEM;
पूर्ण

/*
 * clean up the /proc/fs/cachefiles/ directory
 */
व्योम cachefiles_proc_cleanup(व्योम)
अणु
	हटाओ_proc_entry("fs/cachefiles/histogram", शून्य);
	हटाओ_proc_entry("fs/cachefiles", शून्य);
पूर्ण
