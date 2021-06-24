<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Standalone EHCI usb debug driver
 *
 * Originally written by:
 *  Eric W. Biederman" <ebiederm@xmission.com> and
 *  Yinghai Lu <yhlu.kernel@gmail.com>
 *
 * Changes क्रम early/late prपूर्णांकk and HW errata:
 *  Jason Wessel <jason.wessel@windriver.com>
 *  Copyright (C) 2009 Wind River Systems, Inc.
 *
 */

#अगर_अघोषित __LINUX_USB_EHCI_DBGP_H
#घोषणा __LINUX_USB_EHCI_DBGP_H

#समावेश <linux/console.h>
#समावेश <linux/types.h>

/* Appendix C, Debug port ... पूर्णांकended क्रम use with special "debug devices"
 * that can help अगर there's no serial console.  (nonstandard क्रमागतeration.)
 */
काष्ठा ehci_dbg_port अणु
	u32	control;
#घोषणा DBGP_OWNER	(1<<30)
#घोषणा DBGP_ENABLED	(1<<28)
#घोषणा DBGP_DONE	(1<<16)
#घोषणा DBGP_INUSE	(1<<10)
#घोषणा DBGP_ERRCODE(x)	(((x)>>7)&0x07)
#	define DBGP_ERR_BAD	1
#	define DBGP_ERR_SIGNAL	2
#घोषणा DBGP_ERROR	(1<<6)
#घोषणा DBGP_GO		(1<<5)
#घोषणा DBGP_OUT	(1<<4)
#घोषणा DBGP_LEN(x)	(((x)>>0)&0x0f)
	u32	pids;
#घोषणा DBGP_PID_GET(x)		(((x)>>16)&0xff)
#घोषणा DBGP_PID_SET(data, tok)	(((data)<<8)|(tok))
	u32	data03;
	u32	data47;
	u32	address;
#घोषणा DBGP_EPADDR(dev, ep)	(((dev)<<8)|(ep))
पूर्ण;

#अगर_घोषित CONFIG_EARLY_PRINTK_DBGP
बाह्य पूर्णांक early_dbgp_init(अक्षर *s);
बाह्य काष्ठा console early_dbgp_console;
#पूर्ण_अगर /* CONFIG_EARLY_PRINTK_DBGP */

काष्ठा usb_hcd;

#अगर_घोषित CONFIG_XEN_DOM0
बाह्य पूर्णांक xen_dbgp_reset_prep(काष्ठा usb_hcd *);
बाह्य पूर्णांक xen_dbgp_बाह्यal_startup(काष्ठा usb_hcd *);
#अन्यथा
अटल अंतरभूत पूर्णांक xen_dbgp_reset_prep(काष्ठा usb_hcd *hcd)
अणु
	वापस 1; /* Shouldn't this be 0? */
पूर्ण

अटल अंतरभूत पूर्णांक xen_dbgp_बाह्यal_startup(काष्ठा usb_hcd *hcd)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_EARLY_PRINTK_DBGP
/* Call backs from ehci host driver to ehci debug driver */
बाह्य पूर्णांक dbgp_बाह्यal_startup(काष्ठा usb_hcd *);
बाह्य पूर्णांक dbgp_reset_prep(काष्ठा usb_hcd *);
#अन्यथा
अटल अंतरभूत पूर्णांक dbgp_reset_prep(काष्ठा usb_hcd *hcd)
अणु
	वापस xen_dbgp_reset_prep(hcd);
पूर्ण

अटल अंतरभूत पूर्णांक dbgp_बाह्यal_startup(काष्ठा usb_hcd *hcd)
अणु
	वापस xen_dbgp_बाह्यal_startup(hcd);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_USB_EHCI_DBGP_H */
