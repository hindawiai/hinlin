<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित MPOA_CACHES_H
#घोषणा MPOA_CACHES_H

#समावेश <linux/समय64.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांगmpc.h>
#समावेश <linux/refcount.h>

काष्ठा mpoa_client;

व्योम aपंचांग_mpoa_init_cache(काष्ठा mpoa_client *mpc);

प्रकार काष्ठा in_cache_entry अणु
	काष्ठा in_cache_entry *next;
	काष्ठा in_cache_entry *prev;
	समय64_t  समय;
	समय64_t  reply_रुको;
	समय64_t  hold_करोwn;
	uपूर्णांक32_t  packets_fwded;
	uपूर्णांक16_t  entry_state;
	uपूर्णांक32_t retry_समय;
	uपूर्णांक32_t refresh_समय;
	uपूर्णांक32_t count;
	काष्ठा   aपंचांग_vcc *लघुcut;
	uपूर्णांक8_t  MPS_ctrl_ATM_addr[ATM_ESA_LEN];
	काष्ठा   in_ctrl_info ctrl_info;
	refcount_t use;
पूर्ण in_cache_entry;

काष्ठा in_cache_opsअणु
	in_cache_entry *(*add_entry)(__be32 dst_ip,
				      काष्ठा mpoa_client *client);
	in_cache_entry *(*get)(__be32 dst_ip, काष्ठा mpoa_client *client);
	in_cache_entry *(*get_with_mask)(__be32 dst_ip,
					 काष्ठा mpoa_client *client,
					 __be32 mask);
	in_cache_entry *(*get_by_vcc)(काष्ठा aपंचांग_vcc *vcc,
				      काष्ठा mpoa_client *client);
	व्योम            (*put)(in_cache_entry *entry);
	व्योम            (*हटाओ_entry)(in_cache_entry *delEntry,
					काष्ठा mpoa_client *client );
	पूर्णांक             (*cache_hit)(in_cache_entry *entry,
				     काष्ठा mpoa_client *client);
	व्योम            (*clear_count)(काष्ठा mpoa_client *client);
	व्योम            (*check_resolving)(काष्ठा mpoa_client *client);
	व्योम            (*refresh)(काष्ठा mpoa_client *client);
	व्योम            (*destroy_cache)(काष्ठा mpoa_client *mpc);
पूर्ण;

प्रकार काष्ठा eg_cache_entryअणु
	काष्ठा               eg_cache_entry *next;
	काष्ठा               eg_cache_entry *prev;
	समय64_t	     समय;
	uपूर्णांक8_t              MPS_ctrl_ATM_addr[ATM_ESA_LEN];
	काष्ठा aपंचांग_vcc       *लघुcut;
	uपूर्णांक32_t             packets_rcvd;
	uपूर्णांक16_t             entry_state;
	__be32             latest_ip_addr;    /* The src IP address of the last packet */
	काष्ठा eg_ctrl_info  ctrl_info;
	refcount_t             use;
पूर्ण eg_cache_entry;

काष्ठा eg_cache_opsअणु
	eg_cache_entry *(*add_entry)(काष्ठा k_message *msg, काष्ठा mpoa_client *client);
	eg_cache_entry *(*get_by_cache_id)(__be32 cache_id, काष्ठा mpoa_client *client);
	eg_cache_entry *(*get_by_tag)(__be32 cache_id, काष्ठा mpoa_client *client);
	eg_cache_entry *(*get_by_vcc)(काष्ठा aपंचांग_vcc *vcc, काष्ठा mpoa_client *client);
	eg_cache_entry *(*get_by_src_ip)(__be32 ipaddr, काष्ठा mpoa_client *client);
	व्योम            (*put)(eg_cache_entry *entry);
	व्योम            (*हटाओ_entry)(eg_cache_entry *entry, काष्ठा mpoa_client *client);
	व्योम            (*update)(eg_cache_entry *entry, uपूर्णांक16_t holding_समय);
	व्योम            (*clear_expired)(काष्ठा mpoa_client *client);
	व्योम            (*destroy_cache)(काष्ठा mpoa_client *mpc);
पूर्ण;


/* Ingress cache entry states */

#घोषणा INGRESS_REFRESHING 3
#घोषणा INGRESS_RESOLVED   2
#घोषणा INGRESS_RESOLVING  1
#घोषणा INGRESS_INVALID    0

/* VCC states */

#घोषणा OPEN   1
#घोषणा CLOSED 0

/* Egress cache entry states */

#घोषणा EGRESS_RESOLVED 2
#घोषणा EGRESS_PURGE    1
#घोषणा EGRESS_INVALID  0

#पूर्ण_अगर
