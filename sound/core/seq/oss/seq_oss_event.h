<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OSS compatible sequencer driver
 *
 * seq_oss_event.h - OSS event queue record
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SEQ_OSS_EVENT_H
#घोषणा __SEQ_OSS_EVENT_H

#समावेश "seq_oss_device.h"

#घोषणा SHORT_EVENT_SIZE	4
#घोषणा LONG_EVENT_SIZE		8

/* लघु event (4bytes) */
काष्ठा evrec_लघु अणु
	अचिन्हित अक्षर code;
	अचिन्हित अक्षर parm1;
	अचिन्हित अक्षर dev;
	अचिन्हित अक्षर parm2;
पूर्ण;
	
/* लघु note events (4bytes) */
काष्ठा evrec_note अणु
	अचिन्हित अक्षर code;
	अचिन्हित अक्षर chn;
	अचिन्हित अक्षर note;
	अचिन्हित अक्षर vel;
पूर्ण;
	
/* दीर्घ समयr events (8bytes) */
काष्ठा evrec_समयr अणु
	अचिन्हित अक्षर code;
	अचिन्हित अक्षर cmd;
	अचिन्हित अक्षर dummy1, dummy2;
	अचिन्हित पूर्णांक समय;
पूर्ण;

/* दीर्घ extended events (8bytes) */
काष्ठा evrec_extended अणु
	अचिन्हित अक्षर code;
	अचिन्हित अक्षर cmd;
	अचिन्हित अक्षर dev;
	अचिन्हित अक्षर chn;
	अचिन्हित अक्षर p1, p2, p3, p4;
पूर्ण;

/* दीर्घ channel events (8bytes) */
काष्ठा evrec_दीर्घ अणु
	अचिन्हित अक्षर code;
	अचिन्हित अक्षर dev;
	अचिन्हित अक्षर cmd;
	अचिन्हित अक्षर chn;
	अचिन्हित अक्षर p1, p2;
	अचिन्हित लघु val;
पूर्ण;
	
/* channel voice events (8bytes) */
काष्ठा evrec_voice अणु
	अचिन्हित अक्षर code;
	अचिन्हित अक्षर dev;
	अचिन्हित अक्षर cmd;
	अचिन्हित अक्षर chn;
	अचिन्हित अक्षर note, parm;
	अचिन्हित लघु dummy;
पूर्ण;

/* sysex events (8bytes) */
काष्ठा evrec_sysex अणु
	अचिन्हित अक्षर code;
	अचिन्हित अक्षर dev;
	अचिन्हित अक्षर buf[6];
पूर्ण;

/* event record */
जोड़ evrec अणु
	काष्ठा evrec_लघु s;
	काष्ठा evrec_note n;
	काष्ठा evrec_दीर्घ l;
	काष्ठा evrec_voice v;
	काष्ठा evrec_समयr t;
	काष्ठा evrec_extended e;
	काष्ठा evrec_sysex x;
	अचिन्हित पूर्णांक echo;
	अचिन्हित अक्षर c[LONG_EVENT_SIZE];
पूर्ण;

#घोषणा ev_is_दीर्घ(ev) ((ev)->s.code >= 128)
#घोषणा ev_length(ev) ((ev)->s.code >= 128 ? LONG_EVENT_SIZE : SHORT_EVENT_SIZE)

पूर्णांक snd_seq_oss_process_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *q, काष्ठा snd_seq_event *ev);
पूर्णांक snd_seq_oss_process_समयr_event(काष्ठा seq_oss_समयr *rec, जोड़ evrec *q);
पूर्णांक snd_seq_oss_event_input(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी_data, पूर्णांक atomic, पूर्णांक hop);


#पूर्ण_अगर /* __SEQ_OSS_EVENT_H */
