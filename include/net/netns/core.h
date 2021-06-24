<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NETNS_CORE_H__
#घोषणा __NETNS_CORE_H__

काष्ठा ctl_table_header;
काष्ठा prot_inuse;

काष्ठा netns_core अणु
	/* core sysctls */
	काष्ठा ctl_table_header	*sysctl_hdr;

	पूर्णांक	sysctl_somaxconn;

#अगर_घोषित CONFIG_PROC_FS
	पूर्णांक __percpu *sock_inuse;
	काष्ठा prot_inuse __percpu *prot_inuse;
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर
