<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright IBM Corp. 2016
 *  Author(s): Harald Freudenberger <freude@de.ibm.com>
 */
#अगर_अघोषित AP_DEBUG_H
#घोषणा AP_DEBUG_H

#समावेश <यंत्र/debug.h>

#घोषणा DBF_ERR		3	/* error conditions   */
#घोषणा DBF_WARN	4	/* warning conditions */
#घोषणा DBF_INFO	5	/* inक्रमmational      */
#घोषणा DBF_DEBUG	6	/* क्रम debugging only */

#घोषणा RC2ERR(rc) ((rc) ? DBF_ERR : DBF_INFO)
#घोषणा RC2WARN(rc) ((rc) ? DBF_WARN : DBF_INFO)

#घोषणा DBF_MAX_SPRINTF_ARGS 5

#घोषणा AP_DBF(...)					\
	debug_प्र_लिखो_event(ap_dbf_info, ##__VA_ARGS__)
#घोषणा AP_DBF_ERR(...)					\
	debug_प्र_लिखो_event(ap_dbf_info, DBF_ERR, ##__VA_ARGS__)
#घोषणा AP_DBF_WARN(...)					\
	debug_प्र_लिखो_event(ap_dbf_info, DBF_WARN, ##__VA_ARGS__)
#घोषणा AP_DBF_INFO(...)					\
	debug_प्र_लिखो_event(ap_dbf_info, DBF_INFO, ##__VA_ARGS__)
#घोषणा AP_DBF_DBG(...)					\
	debug_प्र_लिखो_event(ap_dbf_info, DBF_DEBUG, ##__VA_ARGS__)

बाह्य debug_info_t *ap_dbf_info;

#पूर्ण_अगर /* AP_DEBUG_H */
