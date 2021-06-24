<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2008 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

/*
 * midcomms.c
 *
 * This is the appallingly named "mid-level" comms layer.
 *
 * Its purpose is to take packets from the "real" comms layer,
 * split them up पूर्णांकo packets and pass them to the पूर्णांकerested
 * part of the locking mechanism.
 *
 * It also takes messages from the locking layer, क्रमmats them
 * पूर्णांकo packets and sends them to the comms layer.
 */

#समावेश "dlm_internal.h"
#समावेश "lowcomms.h"
#समावेश "config.h"
#समावेश "lock.h"
#समावेश "midcomms.h"

/*
 * Called from the low-level comms layer to process a buffer of
 * commands.
 */

पूर्णांक dlm_process_incoming_buffer(पूर्णांक nodeid, अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	स्थिर अचिन्हित अक्षर *ptr = buf;
	स्थिर काष्ठा dlm_header *hd;
	uपूर्णांक16_t msglen;
	पूर्णांक ret = 0;

	जबतक (len >= माप(काष्ठा dlm_header)) अणु
		hd = (काष्ठा dlm_header *)ptr;

		/* no message should be more than DEFAULT_BUFFER_SIZE or
		 * less than dlm_header size.
		 *
		 * Some messages करोes not have a 8 byte length boundary yet
		 * which can occur in a unaligned memory access of some dlm
		 * messages. However this problem need to be fixed at the
		 * sending side, क्रम now it seems nobody run पूर्णांकo architecture
		 * related issues yet but it slows करोwn some processing.
		 * Fixing this issue should be scheduled in future by करोing
		 * the next major version bump.
		 */
		msglen = le16_to_cpu(hd->h_length);
		अगर (msglen > DEFAULT_BUFFER_SIZE ||
		    msglen < माप(काष्ठा dlm_header)) अणु
			log_prपूर्णांक("received invalid length header: %u from node %d, will abort message parsing",
				  msglen, nodeid);
			वापस -EBADMSG;
		पूर्ण

		/* caller will take care that leftover
		 * will be parsed next call with more data
		 */
		अगर (msglen > len)
			अवरोध;

		चयन (hd->h_cmd) अणु
		हाल DLM_MSG:
			अगर (msglen < माप(काष्ठा dlm_message)) अणु
				log_prपूर्णांक("dlm msg too small: %u, will skip this message",
					  msglen);
				जाओ skip;
			पूर्ण

			अवरोध;
		हाल DLM_RCOM:
			अगर (msglen < माप(काष्ठा dlm_rcom)) अणु
				log_prपूर्णांक("dlm rcom msg too small: %u, will skip this message",
					  msglen);
				जाओ skip;
			पूर्ण

			अवरोध;
		शेष:
			log_prपूर्णांक("unsupported h_cmd received: %u, will skip this message",
				  hd->h_cmd);
			जाओ skip;
		पूर्ण

		dlm_receive_buffer((जोड़ dlm_packet *)ptr, nodeid);

skip:
		ret += msglen;
		len -= msglen;
		ptr += msglen;
	पूर्ण

	वापस ret;
पूर्ण

