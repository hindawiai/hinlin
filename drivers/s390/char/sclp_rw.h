<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * पूर्णांकerface to the SCLP-पढ़ो/ग_लिखो driver
 *
 * Copyright IBM Corporation 1999, 2009
 *
 * Author(s): Martin Peschke <mpeschke@de.ibm.com>
 *	      Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित __SCLP_RW_H__
#घोषणा __SCLP_RW_H__

#समावेश <linux/list.h>

काष्ठा mto अणु
	u16 length;
	u16 type;
	u16 line_type_flags;
	u8  alarm_control;
	u8  _reserved[3];
पूर्ण __attribute__((packed));

काष्ठा go अणु
	u16 length;
	u16 type;
	u32 करोmid;
	u8  hhmmss_समय[8];
	u8  th_समय[3];
	u8  reserved_0;
	u8  dddyyyy_date[7];
	u8  _reserved_1;
	u16 general_msg_flags;
	u8  _reserved_2[10];
	u8  originating_प्रणाली_name[8];
	u8  job_guest_name[8];
पूर्ण __attribute__((packed));

काष्ठा mdb_header अणु
	u16 length;
	u16 type;
	u32 tag;
	u32 revision_code;
पूर्ण __attribute__((packed));

काष्ठा mdb अणु
	काष्ठा mdb_header header;
	काष्ठा go go;
	काष्ठा mto mto;
पूर्ण __attribute__((packed));

काष्ठा msg_buf अणु
	काष्ठा evbuf_header header;
	काष्ठा mdb mdb;
पूर्ण __attribute__((packed));

/* The number of empty mto buffers that can be contained in a single sccb. */
#घोषणा NR_EMPTY_MSG_PER_SCCB ((PAGE_SIZE - माप(काष्ठा sclp_buffer) - \
			माप(काष्ठा sccb_header)) / माप(काष्ठा msg_buf))

/*
 * data काष्ठाure क्रम inक्रमmation about list of SCCBs (only क्रम writing),
 * will be located at the end of a SCCBs page
 */
काष्ठा sclp_buffer अणु
	काष्ठा list_head list;		/* list_head क्रम sccb_info chain */
	काष्ठा sclp_req request;
	व्योम *sccb;
	काष्ठा msg_buf *current_msg;
	अक्षर *current_line;
	पूर्णांक current_length;
	पूर्णांक retry_count;
	/* output क्रमmat settings */
	अचिन्हित लघु columns;
	अचिन्हित लघु htab;
	/* statistics about this buffer */
	अचिन्हित पूर्णांक अक्षर_sum;		/* # अक्षरs in sccb */
	अचिन्हित पूर्णांक messages;		/* # messages in sccb */
	/* Callback that is called after reaching final status. */
	व्योम (*callback)(काष्ठा sclp_buffer *, पूर्णांक);
पूर्ण;

पूर्णांक sclp_rw_init(व्योम);
काष्ठा sclp_buffer *sclp_make_buffer(व्योम *, अचिन्हित लघु, अचिन्हित लघु);
व्योम *sclp_unmake_buffer(काष्ठा sclp_buffer *);
पूर्णांक sclp_buffer_space(काष्ठा sclp_buffer *);
पूर्णांक sclp_ग_लिखो(काष्ठा sclp_buffer *buffer, स्थिर अचिन्हित अक्षर *, पूर्णांक);
पूर्णांक sclp_emit_buffer(काष्ठा sclp_buffer *,व्योम (*)(काष्ठा sclp_buffer *,पूर्णांक));
पूर्णांक sclp_अक्षरs_in_buffer(काष्ठा sclp_buffer *);

#अगर_घोषित CONFIG_SCLP_CONSOLE
व्योम sclp_console_pm_event(क्रमागत sclp_pm_event sclp_pm_event);
#अन्यथा
अटल अंतरभूत व्योम sclp_console_pm_event(क्रमागत sclp_pm_event sclp_pm_event) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* __SCLP_RW_H__ */
