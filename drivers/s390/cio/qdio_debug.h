<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright IBM Corp. 2008
 *
 *  Author: Jan Glauber (jang@linux.vnet.ibm.com)
 */
#अगर_अघोषित QDIO_DEBUG_H
#घोषणा QDIO_DEBUG_H

#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/qdपन.स>
#समावेश "qdio.h"

/* that gives us 15 अक्षरacters in the text event views */
#घोषणा QDIO_DBF_LEN	32

बाह्य debug_info_t *qdio_dbf_setup;
बाह्य debug_info_t *qdio_dbf_error;

#घोषणा DBF_ERR		3	/* error conditions	*/
#घोषणा DBF_WARN	4	/* warning conditions	*/
#घोषणा DBF_INFO	6	/* inक्रमmational	*/

#अघोषित DBF_EVENT
#अघोषित DBF_ERROR
#अघोषित DBF_DEV_EVENT

#घोषणा DBF_EVENT(text...) \
	करो अणु \
		अक्षर debug_buffer[QDIO_DBF_LEN]; \
		snम_लिखो(debug_buffer, QDIO_DBF_LEN, text); \
		debug_text_event(qdio_dbf_setup, DBF_ERR, debug_buffer); \
	पूर्ण जबतक (0)

अटल अंतरभूत व्योम DBF_HEX(व्योम *addr, पूर्णांक len)
अणु
	debug_event(qdio_dbf_setup, DBF_ERR, addr, len);
पूर्ण

#घोषणा DBF_ERROR(text...) \
	करो अणु \
		अक्षर debug_buffer[QDIO_DBF_LEN]; \
		snम_लिखो(debug_buffer, QDIO_DBF_LEN, text); \
		debug_text_event(qdio_dbf_error, DBF_ERR, debug_buffer); \
	पूर्ण जबतक (0)

अटल अंतरभूत व्योम DBF_ERROR_HEX(व्योम *addr, पूर्णांक len)
अणु
	debug_event(qdio_dbf_error, DBF_ERR, addr, len);
पूर्ण

#घोषणा DBF_DEV_EVENT(level, device, text...) \
	करो अणु \
		अक्षर debug_buffer[QDIO_DBF_LEN]; \
		अगर (debug_level_enabled(device->debug_area, level)) अणु \
			snम_लिखो(debug_buffer, QDIO_DBF_LEN, text); \
			debug_text_event(device->debug_area, level, debug_buffer); \
		पूर्ण \
	पूर्ण जबतक (0)

अटल अंतरभूत व्योम DBF_DEV_HEX(काष्ठा qdio_irq *dev, व्योम *addr,
			       पूर्णांक len, पूर्णांक level)
अणु
	debug_event(dev->debug_area, level, addr, len);
पूर्ण

पूर्णांक qdio_allocate_dbf(काष्ठा qdio_irq *irq_ptr);
व्योम qdio_setup_debug_entries(काष्ठा qdio_irq *irq_ptr);
व्योम qdio_shutकरोwn_debug_entries(काष्ठा qdio_irq *irq_ptr);
पूर्णांक qdio_debug_init(व्योम);
व्योम qdio_debug_निकास(व्योम);

#पूर्ण_अगर
