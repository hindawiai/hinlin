<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Shared Memory Communications Direct over ISM devices (SMC-D)
 *
 * SMC-D ISM device काष्ठाure definitions.
 *
 * Copyright IBM Corp. 2018
 */

#अगर_अघोषित SMCD_ISM_H
#घोषणा SMCD_ISM_H

#समावेश <linux/uपन.स>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>

#समावेश "smc.h"

काष्ठा smcd_dev_list अणु	/* List of SMCD devices */
	काष्ठा list_head list;
	काष्ठा mutex mutex;	/* Protects list of devices */
पूर्ण;

बाह्य काष्ठा smcd_dev_list	smcd_dev_list;	/* list of smcd devices */

काष्ठा smc_ism_vlanid अणु			/* VLAN id set on ISM device */
	काष्ठा list_head list;
	अचिन्हित लघु vlanid;		/* Vlan id */
	refcount_t refcnt;		/* Reference count */
पूर्ण;

काष्ठा smc_ism_position अणु	/* ISM device position to ग_लिखो to */
	u64 token;		/* Token of DMB */
	u32 offset;		/* Offset पूर्णांकo DMBE */
	u8 index;		/* Index of DMBE */
	u8 संकेत;		/* Generate पूर्णांकerrupt on owner side */
पूर्ण;

काष्ठा smcd_dev;

पूर्णांक smc_ism_cantalk(u64 peer_gid, अचिन्हित लघु vlan_id, काष्ठा smcd_dev *dev);
व्योम smc_ism_set_conn(काष्ठा smc_connection *conn);
व्योम smc_ism_unset_conn(काष्ठा smc_connection *conn);
पूर्णांक smc_ism_get_vlan(काष्ठा smcd_dev *dev, अचिन्हित लघु vlan_id);
पूर्णांक smc_ism_put_vlan(काष्ठा smcd_dev *dev, अचिन्हित लघु vlan_id);
पूर्णांक smc_ism_रेजिस्टर_dmb(काष्ठा smc_link_group *lgr, पूर्णांक buf_size,
			 काष्ठा smc_buf_desc *dmb_desc);
पूर्णांक smc_ism_unरेजिस्टर_dmb(काष्ठा smcd_dev *dev, काष्ठा smc_buf_desc *dmb_desc);
पूर्णांक smc_ism_ग_लिखो(काष्ठा smcd_dev *dev, स्थिर काष्ठा smc_ism_position *pos,
		  व्योम *data, माप_प्रकार len);
पूर्णांक smc_ism_संकेत_shutकरोwn(काष्ठा smc_link_group *lgr);
व्योम smc_ism_get_प्रणाली_eid(काष्ठा smcd_dev *dev, u8 **eid);
u16 smc_ism_get_chid(काष्ठा smcd_dev *dev);
bool smc_ism_is_v2_capable(व्योम);
व्योम smc_ism_init(व्योम);
पूर्णांक smcd_nl_get_device(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
#पूर्ण_अगर
