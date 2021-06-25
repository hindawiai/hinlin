<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Access vector cache पूर्णांकerface क्रम the security server.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
#अगर_अघोषित _SELINUX_AVC_SS_H_
#घोषणा _SELINUX_AVC_SS_H_

#समावेश "flask.h"

काष्ठा selinux_avc;
पूर्णांक avc_ss_reset(काष्ठा selinux_avc *avc, u32 seqno);

/* Class/perm mapping support */
काष्ठा security_class_mapping अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *perms[माप(u32) * 8 + 1];
पूर्ण;

बाह्य काष्ठा security_class_mapping secclass_map[];

#पूर्ण_अगर /* _SELINUX_AVC_SS_H_ */

