<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mpls in net namespaces
 */

#अगर_अघोषित __NETNS_MPLS_H__
#घोषणा __NETNS_MPLS_H__

काष्ठा mpls_route;
काष्ठा ctl_table_header;

काष्ठा netns_mpls अणु
	पूर्णांक ip_ttl_propagate;
	पूर्णांक शेष_ttl;
	माप_प्रकार platक्रमm_labels;
	काष्ठा mpls_route __rcu * __rcu *platक्रमm_label;

	काष्ठा ctl_table_header *ctl;
पूर्ण;

#पूर्ण_अगर /* __NETNS_MPLS_H__ */
