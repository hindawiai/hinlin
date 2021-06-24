<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Internal definitions क्रम network fileप्रणाली support
 *
 * Copyright (C) 2021 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) "netfs: " fmt

/*
 * पढ़ो_helper.c
 */
बाह्य अचिन्हित पूर्णांक netfs_debug;

/*
 * stats.c
 */
#अगर_घोषित CONFIG_NETFS_STATS
बाह्य atomic_t netfs_n_rh_पढ़ोahead;
बाह्य atomic_t netfs_n_rh_पढ़ोpage;
बाह्य atomic_t netfs_n_rh_rreq;
बाह्य atomic_t netfs_n_rh_sreq;
बाह्य atomic_t netfs_n_rh_करोwnload;
बाह्य atomic_t netfs_n_rh_करोwnload_करोne;
बाह्य atomic_t netfs_n_rh_करोwnload_failed;
बाह्य atomic_t netfs_n_rh_करोwnload_instead;
बाह्य atomic_t netfs_n_rh_पढ़ो;
बाह्य atomic_t netfs_n_rh_पढ़ो_करोne;
बाह्य atomic_t netfs_n_rh_पढ़ो_failed;
बाह्य atomic_t netfs_n_rh_zero;
बाह्य atomic_t netfs_n_rh_लघु_पढ़ो;
बाह्य atomic_t netfs_n_rh_ग_लिखो;
बाह्य atomic_t netfs_n_rh_ग_लिखो_begin;
बाह्य atomic_t netfs_n_rh_ग_लिखो_करोne;
बाह्य atomic_t netfs_n_rh_ग_लिखो_failed;
बाह्य atomic_t netfs_n_rh_ग_लिखो_zskip;


अटल अंतरभूत व्योम netfs_stat(atomic_t *stat)
अणु
	atomic_inc(stat);
पूर्ण

अटल अंतरभूत व्योम netfs_stat_d(atomic_t *stat)
अणु
	atomic_dec(stat);
पूर्ण

#अन्यथा
#घोषणा netfs_stat(x) करो अणुपूर्ण जबतक(0)
#घोषणा netfs_stat_d(x) करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर

/*****************************************************************************/
/*
 * debug tracing
 */
#घोषणा dbgprपूर्णांकk(FMT, ...) \
	prपूर्णांकk("[%-6.6s] "FMT"\n", current->comm, ##__VA_ARGS__)

#घोषणा kenter(FMT, ...) dbgprपूर्णांकk("==> %s("FMT")", __func__, ##__VA_ARGS__)
#घोषणा kleave(FMT, ...) dbgprपूर्णांकk("<== %s()"FMT"", __func__, ##__VA_ARGS__)
#घोषणा kdebug(FMT, ...) dbgprपूर्णांकk(FMT, ##__VA_ARGS__)

#अगर_घोषित __KDEBUG
#घोषणा _enter(FMT, ...) kenter(FMT, ##__VA_ARGS__)
#घोषणा _leave(FMT, ...) kleave(FMT, ##__VA_ARGS__)
#घोषणा _debug(FMT, ...) kdebug(FMT, ##__VA_ARGS__)

#या_अगर defined(CONFIG_NETFS_DEBUG)
#घोषणा _enter(FMT, ...)			\
करो अणु						\
	अगर (netfs_debug)			\
		kenter(FMT, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा _leave(FMT, ...)			\
करो अणु						\
	अगर (netfs_debug)			\
		kleave(FMT, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा _debug(FMT, ...)			\
करो अणु						\
	अगर (netfs_debug)			\
		kdebug(FMT, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#अन्यथा
#घोषणा _enter(FMT, ...) no_prपूर्णांकk("==> %s("FMT")", __func__, ##__VA_ARGS__)
#घोषणा _leave(FMT, ...) no_prपूर्णांकk("<== %s()"FMT"", __func__, ##__VA_ARGS__)
#घोषणा _debug(FMT, ...) no_prपूर्णांकk(FMT, ##__VA_ARGS__)
#पूर्ण_अगर
