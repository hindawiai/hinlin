<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* FS-Cache statistics viewing पूर्णांकerface
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा FSCACHE_DEBUG_LEVEL OPERATION
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश "internal.h"

/*
 * initialise the /proc/fs/fscache/ directory
 */
पूर्णांक __init fscache_proc_init(व्योम)
अणु
	_enter("");

	अगर (!proc_सूची_गढ़ो("fs/fscache", शून्य))
		जाओ error_dir;

#अगर_घोषित CONFIG_FSCACHE_STATS
	अगर (!proc_create_single("fs/fscache/stats", S_IFREG | 0444, शून्य,
			fscache_stats_show))
		जाओ error_stats;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FSCACHE_HISTOGRAM
	अगर (!proc_create_seq("fs/fscache/histogram", S_IFREG | 0444, शून्य,
			 &fscache_histogram_ops))
		जाओ error_histogram;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FSCACHE_OBJECT_LIST
	अगर (!proc_create("fs/fscache/objects", S_IFREG | 0444, शून्य,
			 &fscache_objlist_proc_ops))
		जाओ error_objects;
#पूर्ण_अगर

	_leave(" = 0");
	वापस 0;

#अगर_घोषित CONFIG_FSCACHE_OBJECT_LIST
error_objects:
#पूर्ण_अगर
#अगर_घोषित CONFIG_FSCACHE_HISTOGRAM
	हटाओ_proc_entry("fs/fscache/histogram", शून्य);
error_histogram:
#पूर्ण_अगर
#अगर_घोषित CONFIG_FSCACHE_STATS
	हटाओ_proc_entry("fs/fscache/stats", शून्य);
error_stats:
#पूर्ण_अगर
	हटाओ_proc_entry("fs/fscache", शून्य);
error_dir:
	_leave(" = -ENOMEM");
	वापस -ENOMEM;
पूर्ण

/*
 * clean up the /proc/fs/fscache/ directory
 */
व्योम fscache_proc_cleanup(व्योम)
अणु
#अगर_घोषित CONFIG_FSCACHE_OBJECT_LIST
	हटाओ_proc_entry("fs/fscache/objects", शून्य);
#पूर्ण_अगर
#अगर_घोषित CONFIG_FSCACHE_HISTOGRAM
	हटाओ_proc_entry("fs/fscache/histogram", शून्य);
#पूर्ण_अगर
#अगर_घोषित CONFIG_FSCACHE_STATS
	हटाओ_proc_entry("fs/fscache/stats", शून्य);
#पूर्ण_अगर
	हटाओ_proc_entry("fs/fscache", शून्य);
पूर्ण
