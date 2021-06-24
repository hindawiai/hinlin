<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#अगर_अघोषित MIDIBUF_H
#घोषणा MIDIBUF_H

काष्ठा midi_buffer अणु
	अचिन्हित अक्षर *buf;
	पूर्णांक size;
	पूर्णांक split;
	पूर्णांक pos_पढ़ो, pos_ग_लिखो;
	पूर्णांक full;
	पूर्णांक command_prev;
पूर्ण;

बाह्य पूर्णांक line6_midibuf_bytes_used(काष्ठा midi_buffer *mb);
बाह्य पूर्णांक line6_midibuf_bytes_मुक्त(काष्ठा midi_buffer *mb);
बाह्य व्योम line6_midibuf_destroy(काष्ठा midi_buffer *mb);
बाह्य पूर्णांक line6_midibuf_ignore(काष्ठा midi_buffer *mb, पूर्णांक length);
बाह्य पूर्णांक line6_midibuf_init(काष्ठा midi_buffer *mb, पूर्णांक size, पूर्णांक split);
बाह्य पूर्णांक line6_midibuf_पढ़ो(काष्ठा midi_buffer *mb, अचिन्हित अक्षर *data,
			      पूर्णांक length);
बाह्य व्योम line6_midibuf_reset(काष्ठा midi_buffer *mb);
बाह्य पूर्णांक line6_midibuf_ग_लिखो(काष्ठा midi_buffer *mb, अचिन्हित अक्षर *data,
			       पूर्णांक length);

#पूर्ण_अगर
