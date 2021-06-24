<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 */
/*
 * Copyright (C) 2012 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */
#अगर_अघोषित _KBUFFER_H
#घोषणा _KBUFFER_H

#अगर_अघोषित TS_SHIFT
#घोषणा TS_SHIFT		27
#पूर्ण_अगर

क्रमागत kbuffer_endian अणु
	KBUFFER_ENDIAN_BIG,
	KBUFFER_ENDIAN_LITTLE,
पूर्ण;

क्रमागत kbuffer_दीर्घ_size अणु
	KBUFFER_LSIZE_4,
	KBUFFER_LSIZE_8,
पूर्ण;

क्रमागत अणु
	KBUFFER_TYPE_PADDING		= 29,
	KBUFFER_TYPE_TIME_EXTEND	= 30,
	KBUFFER_TYPE_TIME_STAMP		= 31,
पूर्ण;

काष्ठा kbuffer;

काष्ठा kbuffer *kbuffer_alloc(क्रमागत kbuffer_दीर्घ_size size, क्रमागत kbuffer_endian endian);
व्योम kbuffer_मुक्त(काष्ठा kbuffer *kbuf);
पूर्णांक kbuffer_load_subbuffer(काष्ठा kbuffer *kbuf, व्योम *subbuffer);
व्योम *kbuffer_पढ़ो_event(काष्ठा kbuffer *kbuf, अचिन्हित दीर्घ दीर्घ *ts);
व्योम *kbuffer_next_event(काष्ठा kbuffer *kbuf, अचिन्हित दीर्घ दीर्घ *ts);
अचिन्हित दीर्घ दीर्घ kbuffer_बारtamp(काष्ठा kbuffer *kbuf);
अचिन्हित दीर्घ दीर्घ kbuffer_subbuf_बारtamp(काष्ठा kbuffer *kbuf, व्योम *subbuf);
अचिन्हित पूर्णांक kbuffer_ptr_delta(काष्ठा kbuffer *kbuf, व्योम *ptr);

व्योम *kbuffer_translate_data(पूर्णांक swap, व्योम *data, अचिन्हित पूर्णांक *size);

व्योम *kbuffer_पढ़ो_at_offset(काष्ठा kbuffer *kbuf, पूर्णांक offset, अचिन्हित दीर्घ दीर्घ *ts);

पूर्णांक kbuffer_curr_index(काष्ठा kbuffer *kbuf);

पूर्णांक kbuffer_curr_offset(काष्ठा kbuffer *kbuf);
पूर्णांक kbuffer_curr_size(काष्ठा kbuffer *kbuf);
पूर्णांक kbuffer_event_size(काष्ठा kbuffer *kbuf);
पूर्णांक kbuffer_missed_events(काष्ठा kbuffer *kbuf);
पूर्णांक kbuffer_subbuffer_size(काष्ठा kbuffer *kbuf);

व्योम kbuffer_set_old_क्रमmat(काष्ठा kbuffer *kbuf);
पूर्णांक kbuffer_start_of_data(काष्ठा kbuffer *kbuf);

/* Debugging */

काष्ठा kbuffer_raw_info अणु
	पूर्णांक			type;
	पूर्णांक			length;
	अचिन्हित दीर्घ दीर्घ	delta;
	व्योम			*next;
पूर्ण;

/* Read raw data */
काष्ठा kbuffer_raw_info *kbuffer_raw_get(काष्ठा kbuffer *kbuf, व्योम *subbuf,
					 काष्ठा kbuffer_raw_info *info);

#पूर्ण_अगर /* _K_BUFFER_H */
