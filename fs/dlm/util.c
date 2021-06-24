<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) 2005-2008 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश "dlm_internal.h"
#समावेश "rcom.h"
#समावेश "util.h"

#घोषणा DLM_ERRNO_EDEADLK		35
#घोषणा DLM_ERRNO_EBADR			53
#घोषणा DLM_ERRNO_EBADSLT		57
#घोषणा DLM_ERRNO_EPROTO		71
#घोषणा DLM_ERRNO_EOPNOTSUPP		95
#घोषणा DLM_ERRNO_ETIMEDOUT	       110
#घोषणा DLM_ERRNO_EINPROGRESS	       115

अटल व्योम header_out(काष्ठा dlm_header *hd)
अणु
	hd->h_version		= cpu_to_le32(hd->h_version);
	hd->h_lockspace		= cpu_to_le32(hd->h_lockspace);
	hd->h_nodeid		= cpu_to_le32(hd->h_nodeid);
	hd->h_length		= cpu_to_le16(hd->h_length);
पूर्ण

अटल व्योम header_in(काष्ठा dlm_header *hd)
अणु
	hd->h_version		= le32_to_cpu(hd->h_version);
	hd->h_lockspace		= le32_to_cpu(hd->h_lockspace);
	hd->h_nodeid		= le32_to_cpu(hd->h_nodeid);
	hd->h_length		= le16_to_cpu(hd->h_length);
पूर्ण

/* higher त्रुटि_सं values are inconsistent across architectures, so select
   one set of values क्रम on the wire */

अटल पूर्णांक to_dlm_त्रुटि_सं(पूर्णांक err)
अणु
	चयन (err) अणु
	हाल -EDEADLK:
		वापस -DLM_ERRNO_EDEADLK;
	हाल -EBADR:
		वापस -DLM_ERRNO_EBADR;
	हाल -EBADSLT:
		वापस -DLM_ERRNO_EBADSLT;
	हाल -EPROTO:
		वापस -DLM_ERRNO_EPROTO;
	हाल -EOPNOTSUPP:
		वापस -DLM_ERRNO_EOPNOTSUPP;
	हाल -ETIMEDOUT:
		वापस -DLM_ERRNO_ETIMEDOUT;
	हाल -EINPROGRESS:
		वापस -DLM_ERRNO_EINPROGRESS;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक from_dlm_त्रुटि_सं(पूर्णांक err)
अणु
	चयन (err) अणु
	हाल -DLM_ERRNO_EDEADLK:
		वापस -EDEADLK;
	हाल -DLM_ERRNO_EBADR:
		वापस -EBADR;
	हाल -DLM_ERRNO_EBADSLT:
		वापस -EBADSLT;
	हाल -DLM_ERRNO_EPROTO:
		वापस -EPROTO;
	हाल -DLM_ERRNO_EOPNOTSUPP:
		वापस -EOPNOTSUPP;
	हाल -DLM_ERRNO_ETIMEDOUT:
		वापस -ETIMEDOUT;
	हाल -DLM_ERRNO_EINPROGRESS:
		वापस -EINPROGRESS;
	पूर्ण
	वापस err;
पूर्ण

व्योम dlm_message_out(काष्ठा dlm_message *ms)
अणु
	header_out(&ms->m_header);

	ms->m_type		= cpu_to_le32(ms->m_type);
	ms->m_nodeid		= cpu_to_le32(ms->m_nodeid);
	ms->m_pid		= cpu_to_le32(ms->m_pid);
	ms->m_lkid		= cpu_to_le32(ms->m_lkid);
	ms->m_remid		= cpu_to_le32(ms->m_remid);
	ms->m_parent_lkid	= cpu_to_le32(ms->m_parent_lkid);
	ms->m_parent_remid	= cpu_to_le32(ms->m_parent_remid);
	ms->m_exflags		= cpu_to_le32(ms->m_exflags);
	ms->m_sbflags		= cpu_to_le32(ms->m_sbflags);
	ms->m_flags		= cpu_to_le32(ms->m_flags);
	ms->m_lvbseq		= cpu_to_le32(ms->m_lvbseq);
	ms->m_hash		= cpu_to_le32(ms->m_hash);
	ms->m_status		= cpu_to_le32(ms->m_status);
	ms->m_grmode		= cpu_to_le32(ms->m_grmode);
	ms->m_rqmode		= cpu_to_le32(ms->m_rqmode);
	ms->m_basपंचांगode		= cpu_to_le32(ms->m_basपंचांगode);
	ms->m_asts		= cpu_to_le32(ms->m_asts);
	ms->m_result		= cpu_to_le32(to_dlm_त्रुटि_सं(ms->m_result));
पूर्ण

व्योम dlm_message_in(काष्ठा dlm_message *ms)
अणु
	header_in(&ms->m_header);

	ms->m_type		= le32_to_cpu(ms->m_type);
	ms->m_nodeid		= le32_to_cpu(ms->m_nodeid);
	ms->m_pid		= le32_to_cpu(ms->m_pid);
	ms->m_lkid		= le32_to_cpu(ms->m_lkid);
	ms->m_remid		= le32_to_cpu(ms->m_remid);
	ms->m_parent_lkid	= le32_to_cpu(ms->m_parent_lkid);
	ms->m_parent_remid	= le32_to_cpu(ms->m_parent_remid);
	ms->m_exflags		= le32_to_cpu(ms->m_exflags);
	ms->m_sbflags		= le32_to_cpu(ms->m_sbflags);
	ms->m_flags		= le32_to_cpu(ms->m_flags);
	ms->m_lvbseq		= le32_to_cpu(ms->m_lvbseq);
	ms->m_hash		= le32_to_cpu(ms->m_hash);
	ms->m_status		= le32_to_cpu(ms->m_status);
	ms->m_grmode		= le32_to_cpu(ms->m_grmode);
	ms->m_rqmode		= le32_to_cpu(ms->m_rqmode);
	ms->m_basपंचांगode		= le32_to_cpu(ms->m_basपंचांगode);
	ms->m_asts		= le32_to_cpu(ms->m_asts);
	ms->m_result		= from_dlm_त्रुटि_सं(le32_to_cpu(ms->m_result));
पूर्ण

व्योम dlm_rcom_out(काष्ठा dlm_rcom *rc)
अणु
	header_out(&rc->rc_header);

	rc->rc_type		= cpu_to_le32(rc->rc_type);
	rc->rc_result		= cpu_to_le32(rc->rc_result);
	rc->rc_id		= cpu_to_le64(rc->rc_id);
	rc->rc_seq		= cpu_to_le64(rc->rc_seq);
	rc->rc_seq_reply	= cpu_to_le64(rc->rc_seq_reply);
पूर्ण

व्योम dlm_rcom_in(काष्ठा dlm_rcom *rc)
अणु
	header_in(&rc->rc_header);

	rc->rc_type		= le32_to_cpu(rc->rc_type);
	rc->rc_result		= le32_to_cpu(rc->rc_result);
	rc->rc_id		= le64_to_cpu(rc->rc_id);
	rc->rc_seq		= le64_to_cpu(rc->rc_seq);
	rc->rc_seq_reply	= le64_to_cpu(rc->rc_seq_reply);
पूर्ण
