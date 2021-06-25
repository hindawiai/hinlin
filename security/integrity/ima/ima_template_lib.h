<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Politecnico di Torino, Italy
 *                    TORSEC group -- https://security.polito.it
 *
 * Author: Roberto Sassu <roberto.sassu@polito.it>
 *
 * File: ima_ढाँचा_lib.h
 *      Header क्रम the library of supported ढाँचा fields.
 */
#अगर_अघोषित __LINUX_IMA_TEMPLATE_LIB_H
#घोषणा __LINUX_IMA_TEMPLATE_LIB_H

#समावेश <linux/seq_file.h>
#समावेश "ima.h"

#घोषणा ENFORCE_FIELDS 0x00000001
#घोषणा ENFORCE_BUFEND 0x00000002

व्योम ima_show_ढाँचा_digest(काष्ठा seq_file *m, क्रमागत ima_show_type show,
			      काष्ठा ima_field_data *field_data);
व्योम ima_show_ढाँचा_digest_ng(काष्ठा seq_file *m, क्रमागत ima_show_type show,
				 काष्ठा ima_field_data *field_data);
व्योम ima_show_ढाँचा_string(काष्ठा seq_file *m, क्रमागत ima_show_type show,
			      काष्ठा ima_field_data *field_data);
व्योम ima_show_ढाँचा_sig(काष्ठा seq_file *m, क्रमागत ima_show_type show,
			   काष्ठा ima_field_data *field_data);
व्योम ima_show_ढाँचा_buf(काष्ठा seq_file *m, क्रमागत ima_show_type show,
			   काष्ठा ima_field_data *field_data);
पूर्णांक ima_parse_buf(व्योम *bufstartp, व्योम *bufendp, व्योम **bufcurp,
		  पूर्णांक maxfields, काष्ठा ima_field_data *fields, पूर्णांक *curfields,
		  अचिन्हित दीर्घ *len_mask, पूर्णांक enक्रमce_mask, अक्षर *bufname);
पूर्णांक ima_eventdigest_init(काष्ठा ima_event_data *event_data,
			 काष्ठा ima_field_data *field_data);
पूर्णांक ima_eventname_init(काष्ठा ima_event_data *event_data,
		       काष्ठा ima_field_data *field_data);
पूर्णांक ima_eventdigest_ng_init(काष्ठा ima_event_data *event_data,
			    काष्ठा ima_field_data *field_data);
पूर्णांक ima_eventdigest_modsig_init(काष्ठा ima_event_data *event_data,
				काष्ठा ima_field_data *field_data);
पूर्णांक ima_eventname_ng_init(काष्ठा ima_event_data *event_data,
			  काष्ठा ima_field_data *field_data);
पूर्णांक ima_eventsig_init(काष्ठा ima_event_data *event_data,
		      काष्ठा ima_field_data *field_data);
पूर्णांक ima_eventbuf_init(काष्ठा ima_event_data *event_data,
		      काष्ठा ima_field_data *field_data);
पूर्णांक ima_evenपंचांगodsig_init(काष्ठा ima_event_data *event_data,
			 काष्ठा ima_field_data *field_data);
#पूर्ण_अगर /* __LINUX_IMA_TEMPLATE_LIB_H */
