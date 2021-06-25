<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित CIO_DEBUG_H
#घोषणा CIO_DEBUG_H

#समावेश <यंत्र/debug.h>

/* क्रम use of debug feature */
बाह्य debug_info_t *cio_debug_msg_id;
बाह्य debug_info_t *cio_debug_trace_id;
बाह्य debug_info_t *cio_debug_crw_id;

#घोषणा CIO_TRACE_EVENT(imp, txt) करो अणु				\
		debug_text_event(cio_debug_trace_id, imp, txt); \
	पूर्ण जबतक (0)

#घोषणा CIO_MSG_EVENT(imp, args...) करो अणु				\
		debug_प्र_लिखो_event(cio_debug_msg_id, imp , ##args);	\
	पूर्ण जबतक (0)

#घोषणा CIO_CRW_EVENT(imp, args...) करो अणु				\
		debug_प्र_लिखो_event(cio_debug_crw_id, imp , ##args);	\
	पूर्ण जबतक (0)

अटल अंतरभूत व्योम CIO_HEX_EVENT(पूर्णांक level, व्योम *data, पूर्णांक length)
अणु
	debug_event(cio_debug_trace_id, level, data, length);
पूर्ण

/* For the CIO debugfs related features */
बाह्य काष्ठा dentry *cio_debugfs_dir;

#पूर्ण_अगर
