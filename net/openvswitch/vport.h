<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2007-2012 Nicira, Inc.
 */

#अगर_अघोषित VPORT_H
#घोषणा VPORT_H 1

#समावेश <linux/अगर_tunnel.h>
#समावेश <linux/list.h>
#समावेश <linux/netlink.h>
#समावेश <linux/खोलोvचयन.h>
#समावेश <linux/reciprocal_भाग.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/u64_stats_sync.h>

#समावेश "datapath.h"

काष्ठा vport;
काष्ठा vport_parms;

/* The following definitions are क्रम users of the vport subप्रणाली: */

पूर्णांक ovs_vport_init(व्योम);
व्योम ovs_vport_निकास(व्योम);

काष्ठा vport *ovs_vport_add(स्थिर काष्ठा vport_parms *);
व्योम ovs_vport_del(काष्ठा vport *);

काष्ठा vport *ovs_vport_locate(स्थिर काष्ठा net *net, स्थिर अक्षर *name);

व्योम ovs_vport_get_stats(काष्ठा vport *, काष्ठा ovs_vport_stats *);

पूर्णांक ovs_vport_set_options(काष्ठा vport *, काष्ठा nlattr *options);
पूर्णांक ovs_vport_get_options(स्थिर काष्ठा vport *, काष्ठा sk_buff *);

पूर्णांक ovs_vport_set_upcall_portids(काष्ठा vport *, स्थिर काष्ठा nlattr *pids);
पूर्णांक ovs_vport_get_upcall_portids(स्थिर काष्ठा vport *, काष्ठा sk_buff *);
u32 ovs_vport_find_upcall_portid(स्थिर काष्ठा vport *, काष्ठा sk_buff *);

/**
 * काष्ठा vport_portids - array of netlink portids of a vport.
 *                        must be रक्षित by rcu.
 * @rn_ids: The reciprocal value of @n_ids.
 * @rcu: RCU callback head क्रम deferred deकाष्ठाion.
 * @n_ids: Size of @ids array.
 * @ids: Array storing the Netlink socket pids to be used क्रम packets received
 * on this port that miss the flow table.
 */
काष्ठा vport_portids अणु
	काष्ठा reciprocal_value rn_ids;
	काष्ठा rcu_head rcu;
	u32 n_ids;
	u32 ids[];
पूर्ण;

/**
 * काष्ठा vport - one port within a datapath
 * @dev: Poपूर्णांकer to net_device.
 * @dp: Datapath to which this port beदीर्घs.
 * @upcall_portids: RCU रक्षित 'struct vport_portids'.
 * @port_no: Index पूर्णांकo @dp's @ports array.
 * @hash_node: Element in @dev_table hash table in vport.c.
 * @dp_hash_node: Element in @datapath->ports hash table in datapath.c.
 * @ops: Class काष्ठाure.
 * @detach_list: list used क्रम detaching vport in net-निकास call.
 * @rcu: RCU callback head क्रम deferred deकाष्ठाion.
 */
काष्ठा vport अणु
	काष्ठा net_device *dev;
	काष्ठा datapath	*dp;
	काष्ठा vport_portids __rcu *upcall_portids;
	u16 port_no;

	काष्ठा hlist_node hash_node;
	काष्ठा hlist_node dp_hash_node;
	स्थिर काष्ठा vport_ops *ops;

	काष्ठा list_head detach_list;
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा vport_parms - parameters क्रम creating a new vport
 *
 * @name: New vport's name.
 * @type: New vport's type.
 * @options: %OVS_VPORT_ATTR_OPTIONS attribute from Netlink message, %शून्य अगर
 * none was supplied.
 * @dp: New vport's datapath.
 * @port_no: New vport's port number.
 */
काष्ठा vport_parms अणु
	स्थिर अक्षर *name;
	क्रमागत ovs_vport_type type;
	काष्ठा nlattr *options;

	/* For ovs_vport_alloc(). */
	काष्ठा datapath *dp;
	u16 port_no;
	काष्ठा nlattr *upcall_portids;
पूर्ण;

/**
 * काष्ठा vport_ops - definition of a type of भव port
 *
 * @type: %OVS_VPORT_TYPE_* value क्रम this type of भव port.
 * @create: Create a new vport configured as specअगरied.  On success वापसs
 * a new vport allocated with ovs_vport_alloc(), otherwise an ERR_PTR() value.
 * @destroy: Destroys a vport.  Must call vport_मुक्त() on the vport but not
 * beक्रमe an RCU grace period has elapsed.
 * @set_options: Modअगरy the configuration of an existing vport.  May be %शून्य
 * अगर modअगरication is not supported.
 * @get_options: Appends vport-specअगरic attributes क्रम the configuration of an
 * existing vport to a &काष्ठा sk_buff.  May be %शून्य क्रम a vport that करोes not
 * have any configuration.
 * @send: Send a packet on the device.
 * zero क्रम dropped packets or negative क्रम error.
 */
काष्ठा vport_ops अणु
	क्रमागत ovs_vport_type type;

	/* Called with ovs_mutex. */
	काष्ठा vport *(*create)(स्थिर काष्ठा vport_parms *);
	व्योम (*destroy)(काष्ठा vport *);

	पूर्णांक (*set_options)(काष्ठा vport *, काष्ठा nlattr *);
	पूर्णांक (*get_options)(स्थिर काष्ठा vport *, काष्ठा sk_buff *);

	netdev_tx_t (*send) (काष्ठा sk_buff *skb);
	काष्ठा module *owner;
	काष्ठा list_head list;
पूर्ण;

काष्ठा vport *ovs_vport_alloc(पूर्णांक priv_size, स्थिर काष्ठा vport_ops *,
			      स्थिर काष्ठा vport_parms *);
व्योम ovs_vport_मुक्त(काष्ठा vport *);

#घोषणा VPORT_ALIGN 8

/**
 *	vport_priv - access निजी data area of vport
 *
 * @vport: vport to access
 *
 * If a nonzero size was passed in priv_size of vport_alloc() a निजी data
 * area was allocated on creation.  This allows that area to be accessed and
 * used क्रम any purpose needed by the vport implementer.
 */
अटल अंतरभूत व्योम *vport_priv(स्थिर काष्ठा vport *vport)
अणु
	वापस (u8 *)(uपूर्णांकptr_t)vport + ALIGN(माप(काष्ठा vport), VPORT_ALIGN);
पूर्ण

/**
 *	vport_from_priv - lookup vport from निजी data poपूर्णांकer
 *
 * @priv: Start of निजी data area.
 *
 * It is someबार useful to translate from a poपूर्णांकer to the निजी data
 * area to the vport, such as in the हाल where the निजी data poपूर्णांकer is
 * the result of a hash table lookup.  @priv must poपूर्णांक to the start of the
 * निजी data area.
 */
अटल अंतरभूत काष्ठा vport *vport_from_priv(व्योम *priv)
अणु
	वापस (काष्ठा vport *)((u8 *)priv - ALIGN(माप(काष्ठा vport), VPORT_ALIGN));
पूर्ण

पूर्णांक ovs_vport_receive(काष्ठा vport *, काष्ठा sk_buff *,
		      स्थिर काष्ठा ip_tunnel_info *);

अटल अंतरभूत स्थिर अक्षर *ovs_vport_name(काष्ठा vport *vport)
अणु
	वापस vport->dev->name;
पूर्ण

पूर्णांक __ovs_vport_ops_रेजिस्टर(काष्ठा vport_ops *ops);
#घोषणा ovs_vport_ops_रेजिस्टर(ops)		\
	(अणु					\
		(ops)->owner = THIS_MODULE;	\
		__ovs_vport_ops_रेजिस्टर(ops);	\
	पूर्ण)

व्योम ovs_vport_ops_unरेजिस्टर(काष्ठा vport_ops *ops);
व्योम ovs_vport_send(काष्ठा vport *vport, काष्ठा sk_buff *skb, u8 mac_proto);

#पूर्ण_अगर /* vport.h */
