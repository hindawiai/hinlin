<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम ADB (Apple Desktop Bus) support.
 */
#अगर_अघोषित __ADB_H
#घोषणा __ADB_H

#समावेश <uapi/linux/adb.h>


काष्ठा adb_request अणु
	अचिन्हित अक्षर data[32];
	पूर्णांक nbytes;
	अचिन्हित अक्षर reply[32];
	पूर्णांक reply_len;
	अचिन्हित अक्षर reply_expected;
	अचिन्हित अक्षर sent;
	अचिन्हित अक्षर complete;
	व्योम (*करोne)(काष्ठा adb_request *);
	व्योम *arg;
	काष्ठा adb_request *next;
पूर्ण;

काष्ठा adb_ids अणु
	पूर्णांक nids;
	अचिन्हित अक्षर id[16];
पूर्ण;

/* Structure which encapsulates a low-level ADB driver */

काष्ठा adb_driver अणु
	अक्षर name[16];
	पूर्णांक (*probe)(व्योम);
	पूर्णांक (*init)(व्योम);
	पूर्णांक (*send_request)(काष्ठा adb_request *req, पूर्णांक sync);
	पूर्णांक (*स्वतःpoll)(पूर्णांक devs);
	व्योम (*poll)(व्योम);
	पूर्णांक (*reset_bus)(व्योम);
पूर्ण;

/* Values क्रम adb_request flags */
#घोषणा ADBREQ_REPLY	1	/* expect reply */
#घोषणा ADBREQ_SYNC	2	/* poll until करोne */
#घोषणा ADBREQ_NOSEND	4	/* build the request, but करोn't send it */

/* Messages sent thru the client_list notअगरier. You should NOT stop
   the operation, at least not with this version */
क्रमागत adb_message अणु
    ADB_MSG_POWERDOWN,	/* Currently called beक्रमe sleep only */
    ADB_MSG_PRE_RESET,	/* Called beक्रमe resetting the bus */
    ADB_MSG_POST_RESET	/* Called after resetting the bus (re-करो init & रेजिस्टर) */
पूर्ण;
बाह्य काष्ठा blocking_notअगरier_head adb_client_list;

पूर्णांक adb_request(काष्ठा adb_request *req, व्योम (*करोne)(काष्ठा adb_request *),
		पूर्णांक flags, पूर्णांक nbytes, ...);
पूर्णांक adb_रेजिस्टर(पूर्णांक शेष_id,पूर्णांक handler_id,काष्ठा adb_ids *ids,
		 व्योम (*handler)(अचिन्हित अक्षर *, पूर्णांक, पूर्णांक));
पूर्णांक adb_unरेजिस्टर(पूर्णांक index);
व्योम adb_poll(व्योम);
व्योम adb_input(अचिन्हित अक्षर *, पूर्णांक, पूर्णांक);
पूर्णांक adb_reset_bus(व्योम);

पूर्णांक adb_try_handler_change(पूर्णांक address, पूर्णांक new_id);
पूर्णांक adb_get_infos(पूर्णांक address, पूर्णांक *original_address, पूर्णांक *handler_id);

#पूर्ण_अगर /* __ADB_H */
