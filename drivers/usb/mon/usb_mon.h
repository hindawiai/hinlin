<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * The USB Monitor, inspired by Dave Harding's USBMon.
 *
 * Copyright (C) 2005 Pete Zaitcev (zaitcev@redhat.com)
 */

#अगर_अघोषित __USB_MON_H
#घोषणा __USB_MON_H

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/kref.h>
/* #समावेश <linux/usb.h> */	/* We use काष्ठा poपूर्णांकers only in this header */

#घोषणा TAG "usbmon"

काष्ठा mon_bus अणु
	काष्ठा list_head bus_link;
	spinlock_t lock;
	काष्ठा usb_bus *u_bus;

	पूर्णांक text_inited;
	पूर्णांक bin_inited;
	काष्ठा dentry *dent_s;		/* Debugging file */
	काष्ठा dentry *dent_t;		/* Text पूर्णांकerface file */
	काष्ठा dentry *dent_u;		/* Second text पूर्णांकerface file */
	काष्ठा device *classdev;	/* Device in usbmon class */

	/* Ref */
	पूर्णांक nपढ़ोers;			/* Under mon_lock AND mbus->lock */
	काष्ठा list_head r_list;	/* Chain of पढ़ोers (usually one) */
	काष्ठा kref ref;		/* Under mon_lock */

	/* Stats */
	अचिन्हित पूर्णांक cnt_events;
	अचिन्हित पूर्णांक cnt_text_lost;
पूर्ण;

/*
 * An instance of a process which खोलोed a file (but can विभाजन later)
 */
काष्ठा mon_पढ़ोer अणु
	काष्ठा list_head r_link;
	काष्ठा mon_bus *m_bus;
	व्योम *r_data;		/* Use container_of instead? */

	व्योम (*rnf_submit)(व्योम *data, काष्ठा urb *urb);
	व्योम (*rnf_error)(व्योम *data, काष्ठा urb *urb, पूर्णांक error);
	व्योम (*rnf_complete)(व्योम *data, काष्ठा urb *urb, पूर्णांक status);
पूर्ण;

व्योम mon_पढ़ोer_add(काष्ठा mon_bus *mbus, काष्ठा mon_पढ़ोer *r);
व्योम mon_पढ़ोer_del(काष्ठा mon_bus *mbus, काष्ठा mon_पढ़ोer *r);

काष्ठा mon_bus *mon_bus_lookup(अचिन्हित पूर्णांक num);

पूर्णांक /*bool*/ mon_text_add(काष्ठा mon_bus *mbus, स्थिर काष्ठा usb_bus *ubus);
व्योम mon_text_del(काष्ठा mon_bus *mbus);
पूर्णांक /*bool*/ mon_bin_add(काष्ठा mon_bus *mbus, स्थिर काष्ठा usb_bus *ubus);
व्योम mon_bin_del(काष्ठा mon_bus *mbus);

पूर्णांक __init mon_text_init(व्योम);
व्योम mon_text_निकास(व्योम);
पूर्णांक __init mon_bin_init(व्योम);
व्योम mon_bin_निकास(व्योम);

/*
 */
बाह्य काष्ठा mutex mon_lock;

बाह्य स्थिर काष्ठा file_operations mon_fops_stat;

बाह्य काष्ठा mon_bus mon_bus0;		/* Only क्रम redundant checks */

#पूर्ण_अगर /* __USB_MON_H */
