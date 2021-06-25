<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ieee802154 6lowpan in net namespaces
 */

#समावेश <net/inet_frag.h>

#अगर_अघोषित __NETNS_IEEE802154_6LOWPAN_H__
#घोषणा __NETNS_IEEE802154_6LOWPAN_H__

काष्ठा netns_sysctl_lowpan अणु
#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table_header *frags_hdr;
#पूर्ण_अगर
पूर्ण;

काष्ठा netns_ieee802154_lowpan अणु
	काष्ठा netns_sysctl_lowpan sysctl;
	काष्ठा fqdir		*fqdir;
पूर्ण;

#पूर्ण_अगर
