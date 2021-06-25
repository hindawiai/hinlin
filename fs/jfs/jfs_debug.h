<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2002
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */
#अगर_अघोषित _H_JFS_DEBUG
#घोषणा _H_JFS_DEBUG

/*
 *	jfs_debug.h
 *
 * global debug message, data काष्ठाure/macro definitions
 * under control of CONFIG_JFS_DEBUG, CONFIG_JFS_STATISTICS;
 */

/*
 * Create /proc/fs/jfs अगर procfs is enabled andeither
 * CONFIG_JFS_DEBUG or CONFIG_JFS_STATISTICS is defined
 */
#अगर defined(CONFIG_PROC_FS) && (defined(CONFIG_JFS_DEBUG) || defined(CONFIG_JFS_STATISTICS))
#घोषणा PROC_FS_JFS
बाह्य व्योम jfs_proc_init(व्योम);
बाह्य व्योम jfs_proc_clean(व्योम);
#पूर्ण_अगर

/*
 *	निश्चित with traditional म_लिखो/panic
 */
#घोषणा निश्चित(p) करो अणु	\
	अगर (!(p)) अणु	\
		prपूर्णांकk(KERN_CRIT "BUG at %s:%d assert(%s)\n",	\
		       __खाता__, __LINE__, #p);			\
		BUG();	\
	पूर्ण		\
पूर्ण जबतक (0)

/*
 *	debug ON
 *	--------
 */
#अगर_घोषित CONFIG_JFS_DEBUG
#घोषणा ASSERT(p) निश्चित(p)

/* prपूर्णांकk verbosity */
#घोषणा JFS_LOGLEVEL_ERR 1
#घोषणा JFS_LOGLEVEL_WARN 2
#घोषणा JFS_LOGLEVEL_DEBUG 3
#घोषणा JFS_LOGLEVEL_INFO 4

बाह्य पूर्णांक jfsloglevel;

पूर्णांक jfs_txanchor_proc_show(काष्ठा seq_file *m, व्योम *v);

/* inक्रमmation message: e.g., configuration, major event */
#घोषणा jfs_info(fmt, arg...) करो अणु			\
	अगर (jfsloglevel >= JFS_LOGLEVEL_INFO)		\
		prपूर्णांकk(KERN_INFO fmt "\n", ## arg);	\
पूर्ण जबतक (0)

/* debug message: ad hoc */
#घोषणा jfs_debug(fmt, arg...) करो अणु			\
	अगर (jfsloglevel >= JFS_LOGLEVEL_DEBUG)		\
		prपूर्णांकk(KERN_DEBUG fmt "\n", ## arg);	\
पूर्ण जबतक (0)

/* warn message: */
#घोषणा jfs_warn(fmt, arg...) करो अणु			\
	अगर (jfsloglevel >= JFS_LOGLEVEL_WARN)		\
		prपूर्णांकk(KERN_WARNING fmt "\n", ## arg);	\
पूर्ण जबतक (0)

/* error event message: e.g., i/o error */
#घोषणा jfs_err(fmt, arg...) करो अणु			\
	अगर (jfsloglevel >= JFS_LOGLEVEL_ERR)		\
		prपूर्णांकk(KERN_ERR fmt "\n", ## arg);	\
पूर्ण जबतक (0)

/*
 *	debug OFF
 *	---------
 */
#अन्यथा				/* CONFIG_JFS_DEBUG */
#घोषणा ASSERT(p) करो अणुपूर्ण जबतक (0)
#घोषणा jfs_info(fmt, arg...) करो अणुपूर्ण जबतक (0)
#घोषणा jfs_debug(fmt, arg...) करो अणुपूर्ण जबतक (0)
#घोषणा jfs_warn(fmt, arg...) करो अणुपूर्ण जबतक (0)
#घोषणा jfs_err(fmt, arg...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर				/* CONFIG_JFS_DEBUG */

/*
 *	statistics
 *	----------
 */
#अगर_घोषित	CONFIG_JFS_STATISTICS
पूर्णांक jfs_lmstats_proc_show(काष्ठा seq_file *m, व्योम *v);
पूर्णांक jfs_txstats_proc_show(काष्ठा seq_file *m, व्योम *v);
पूर्णांक jfs_mpstat_proc_show(काष्ठा seq_file *m, व्योम *v);
पूर्णांक jfs_xtstat_proc_show(काष्ठा seq_file *m, व्योम *v);

#घोषणा	INCREMENT(x)		((x)++)
#घोषणा	DECREMENT(x)		((x)--)
#घोषणा	HIGHWATERMARK(x,y)	((x) = max((x), (y)))
#अन्यथा
#घोषणा	INCREMENT(x)
#घोषणा	DECREMENT(x)
#घोषणा	HIGHWATERMARK(x,y)
#पूर्ण_अगर				/* CONFIG_JFS_STATISTICS */

#पूर्ण_अगर				/* _H_JFS_DEBUG */
