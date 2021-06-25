<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2020 IBM Corporation
 *
 */

#अगर_अघोषित _NXU_DBG_H_
#घोषणा _NXU_DBG_H_

#समावेश <sys/file.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <समय.स>
#समावेश <pthपढ़ो.h>

बाह्य खाता * nx_gzip_log;
बाह्य पूर्णांक nx_gzip_trace;
बाह्य अचिन्हित पूर्णांक nx_gzip_inflate_impl;
बाह्य अचिन्हित पूर्णांक nx_gzip_deflate_impl;
बाह्य अचिन्हित पूर्णांक nx_gzip_inflate_flags;
बाह्य अचिन्हित पूर्णांक nx_gzip_deflate_flags;

बाह्य पूर्णांक nx_dbg;
pthपढ़ो_mutex_t mutex_log;

#घोषणा nx_gzip_trace_enabled()       (nx_gzip_trace & 0x1)
#घोषणा nx_gzip_hw_trace_enabled()    (nx_gzip_trace & 0x2)
#घोषणा nx_gzip_sw_trace_enabled()    (nx_gzip_trace & 0x4)
#घोषणा nx_gzip_gather_statistics()   (nx_gzip_trace & 0x8)
#घोषणा nx_gzip_per_stream_stat()     (nx_gzip_trace & 0x10)

#घोषणा prt(fmt, ...) करो अणु \
	pthपढ़ो_mutex_lock(&mutex_log);					\
	flock(nx_gzip_log->_fileno, LOCK_EX);				\
	समय_प्रकार t; काष्ठा पंचांग *m; समय(&t); m = स_स्थानीय(&t);		\
	ख_लिखो(nx_gzip_log, "[%04d/%02d/%02d %02d:%02d:%02d] "		\
		"pid %d: " fmt,	\
		(पूर्णांक)m->पंचांग_year + 1900, (पूर्णांक)m->पंचांग_mon+1, (पूर्णांक)m->पंचांग_mday, \
		(पूर्णांक)m->पंचांग_hour, (पूर्णांक)m->पंचांग_min, (पूर्णांक)m->पंचांग_sec,	\
		(पूर्णांक)getpid(), ## __VA_ARGS__);				\
	ख_साफ(nx_gzip_log);						\
	flock(nx_gzip_log->_fileno, LOCK_UN);				\
	pthपढ़ो_mutex_unlock(&mutex_log);				\
पूर्ण जबतक (0)

/* Use in हाल of an error */
#घोषणा prt_err(fmt, ...) करो अणु अगर (nx_dbg >= 0) अणु			\
	prt("%s:%u: Error: "fmt,					\
		__खाता__, __LINE__, ## __VA_ARGS__);			\
पूर्णपूर्ण जबतक (0)

/* Use in हाल of an warning */
#घोषणा prt_warn(fmt, ...) करो अणु	अगर (nx_dbg >= 1) अणु			\
	prt("%s:%u: Warning: "fmt,					\
		__खाता__, __LINE__, ## __VA_ARGS__);			\
पूर्णपूर्ण जबतक (0)

/* Inक्रमmational prपूर्णांकouts */
#घोषणा prt_info(fmt, ...) करो अणु	अगर (nx_dbg >= 2) अणु			\
	prt("Info: "fmt, ## __VA_ARGS__);				\
पूर्णपूर्ण जबतक (0)

/* Trace zlib wrapper code */
#घोषणा prt_trace(fmt, ...) करो अणु अगर (nx_gzip_trace_enabled()) अणु		\
	prt("### "fmt, ## __VA_ARGS__);					\
पूर्णपूर्ण जबतक (0)

/* Trace statistics */
#घोषणा prt_stat(fmt, ...) करो अणु	अगर (nx_gzip_gather_statistics()) अणु	\
	prt("### "fmt, ## __VA_ARGS__);					\
पूर्णपूर्ण जबतक (0)

/* Trace zlib hardware implementation */
#घोषणा hw_trace(fmt, ...) करो अणु						\
		अगर (nx_gzip_hw_trace_enabled())				\
			ख_लिखो(nx_gzip_log, "hhh " fmt, ## __VA_ARGS__); \
	पूर्ण जबतक (0)

/* Trace zlib software implementation */
#घोषणा sw_trace(fmt, ...) करो अणु						\
		अगर (nx_gzip_sw_trace_enabled())				\
			ख_लिखो(nx_gzip_log, "sss " fmt, ## __VA_ARGS__); \
	पूर्ण जबतक (0)


/**
 * str_to_num - Convert string पूर्णांकo number and copy with endings like
 *              KiB क्रम kilobyte
 *              MiB क्रम megabyte
 *              GiB क्रम gigabyte
 */
uपूर्णांक64_t str_to_num(अक्षर *str);
व्योम nx_lib_debug(पूर्णांक onoff);

#पूर्ण_अगर	/* _NXU_DBG_H_ */
