<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NETNS_NETFILTER_H
#घोषणा __NETNS_NETFILTER_H

#समावेश <linux/netfilter_defs.h>

काष्ठा proc_dir_entry;
काष्ठा nf_logger;
काष्ठा nf_queue_handler;

काष्ठा netns_nf अणु
#अगर defined CONFIG_PROC_FS
	काष्ठा proc_dir_entry *proc_netfilter;
#पूर्ण_अगर
	स्थिर काष्ठा nf_queue_handler __rcu *queue_handler;
	स्थिर काष्ठा nf_logger __rcu *nf_loggers[NFPROTO_NUMPROTO];
#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table_header *nf_log_dir_header;
#पूर्ण_अगर
	काष्ठा nf_hook_entries __rcu *hooks_ipv4[NF_INET_NUMHOOKS];
	काष्ठा nf_hook_entries __rcu *hooks_ipv6[NF_INET_NUMHOOKS];
#अगर_घोषित CONFIG_NETFILTER_FAMILY_ARP
	काष्ठा nf_hook_entries __rcu *hooks_arp[NF_ARP_NUMHOOKS];
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETFILTER_FAMILY_BRIDGE
	काष्ठा nf_hook_entries __rcu *hooks_bridge[NF_INET_NUMHOOKS];
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_DECNET)
	काष्ठा nf_hook_entries __rcu *hooks_decnet[NF_DN_NUMHOOKS];
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर
