<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * event.c - exporting ACPI events via procfs
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/gfp.h>
#समावेश <linux/acpi.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>

#समावेश "internal.h"

/* ACPI notअगरier chain */
अटल BLOCKING_NOTIFIER_HEAD(acpi_chain_head);

पूर्णांक acpi_notअगरier_call_chain(काष्ठा acpi_device *dev, u32 type, u32 data)
अणु
	काष्ठा acpi_bus_event event;

	म_नकल(event.device_class, dev->pnp.device_class);
	म_नकल(event.bus_id, dev->pnp.bus_id);
	event.type = type;
	event.data = data;
	वापस (blocking_notअगरier_call_chain(&acpi_chain_head, 0, (व्योम *)&event)
			== NOTIFY_BAD) ? -EINVAL : 0;
पूर्ण
EXPORT_SYMBOL(acpi_notअगरier_call_chain);

पूर्णांक रेजिस्टर_acpi_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&acpi_chain_head, nb);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_acpi_notअगरier);

पूर्णांक unरेजिस्टर_acpi_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&acpi_chain_head, nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_acpi_notअगरier);

#अगर_घोषित CONFIG_NET
अटल अचिन्हित पूर्णांक acpi_event_seqnum;
काष्ठा acpi_genl_event अणु
	acpi_device_class device_class;
	अक्षर bus_id[15];
	u32 type;
	u32 data;
पूर्ण;

/* attributes of acpi_genl_family */
क्रमागत अणु
	ACPI_GENL_ATTR_UNSPEC,
	ACPI_GENL_ATTR_EVENT,	/* ACPI event info needed by user space */
	__ACPI_GENL_ATTR_MAX,
पूर्ण;
#घोषणा ACPI_GENL_ATTR_MAX (__ACPI_GENL_ATTR_MAX - 1)

/* commands supported by the acpi_genl_family */
क्रमागत अणु
	ACPI_GENL_CMD_UNSPEC,
	ACPI_GENL_CMD_EVENT,	/* kernel->user notअगरications क्रम ACPI events */
	__ACPI_GENL_CMD_MAX,
पूर्ण;
#घोषणा ACPI_GENL_CMD_MAX (__ACPI_GENL_CMD_MAX - 1)

#घोषणा ACPI_GENL_FAMILY_NAME		"acpi_event"
#घोषणा ACPI_GENL_VERSION		0x01
#घोषणा ACPI_GENL_MCAST_GROUP_NAME 	"acpi_mc_group"

अटल स्थिर काष्ठा genl_multicast_group acpi_event_mcgrps[] = अणु
	अणु .name = ACPI_GENL_MCAST_GROUP_NAME, पूर्ण,
पूर्ण;

अटल काष्ठा genl_family acpi_event_genl_family __ro_after_init = अणु
	.module = THIS_MODULE,
	.name = ACPI_GENL_FAMILY_NAME,
	.version = ACPI_GENL_VERSION,
	.maxattr = ACPI_GENL_ATTR_MAX,
	.mcgrps = acpi_event_mcgrps,
	.n_mcgrps = ARRAY_SIZE(acpi_event_mcgrps),
पूर्ण;

पूर्णांक acpi_bus_generate_netlink_event(स्थिर अक्षर *device_class,
				      स्थिर अक्षर *bus_id,
				      u8 type, पूर्णांक data)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nlattr *attr;
	काष्ठा acpi_genl_event *event;
	व्योम *msg_header;
	पूर्णांक size;

	/* allocate memory */
	size = nla_total_size(माप(काष्ठा acpi_genl_event)) +
	    nla_total_size(0);

	skb = genlmsg_new(size, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	/* add the genetlink message header */
	msg_header = genlmsg_put(skb, 0, acpi_event_seqnum++,
				 &acpi_event_genl_family, 0,
				 ACPI_GENL_CMD_EVENT);
	अगर (!msg_header) अणु
		nlmsg_मुक्त(skb);
		वापस -ENOMEM;
	पूर्ण

	/* fill the data */
	attr =
	    nla_reserve(skb, ACPI_GENL_ATTR_EVENT,
			माप(काष्ठा acpi_genl_event));
	अगर (!attr) अणु
		nlmsg_मुक्त(skb);
		वापस -EINVAL;
	पूर्ण

	event = nla_data(attr);
	स_रखो(event, 0, माप(काष्ठा acpi_genl_event));

	strscpy(event->device_class, device_class, माप(event->device_class));
	strscpy(event->bus_id, bus_id, माप(event->bus_id));
	event->type = type;
	event->data = data;

	/* send multicast genetlink message */
	genlmsg_end(skb, msg_header);

	genlmsg_multicast(&acpi_event_genl_family, skb, 0, 0, GFP_ATOMIC);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(acpi_bus_generate_netlink_event);

अटल पूर्णांक __init acpi_event_genetlink_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&acpi_event_genl_family);
पूर्ण

#अन्यथा
पूर्णांक acpi_bus_generate_netlink_event(स्थिर अक्षर *device_class,
				      स्थिर अक्षर *bus_id,
				      u8 type, पूर्णांक data)
अणु
	वापस 0;
पूर्ण

EXPORT_SYMBOL(acpi_bus_generate_netlink_event);

अटल पूर्णांक acpi_event_genetlink_init(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init acpi_event_init(व्योम)
अणु
	पूर्णांक error = 0;

	अगर (acpi_disabled)
		वापस 0;

	/* create genetlink क्रम acpi event */
	error = acpi_event_genetlink_init();
	अगर (error)
		prपूर्णांकk(KERN_WARNING PREFIX
		       "Failed to create genetlink family for ACPI event\n");
	वापस 0;
पूर्ण

fs_initcall(acpi_event_init);
