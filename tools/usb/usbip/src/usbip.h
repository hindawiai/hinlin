<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 */

#अगर_अघोषित __USBIP_H
#घोषणा __USBIP_H

#अगर_घोषित HAVE_CONFIG_H
#समावेश "../config.h"
#पूर्ण_अगर

/* usbip commands */
पूर्णांक usbip_attach(पूर्णांक argc, अक्षर *argv[]);
पूर्णांक usbip_detach(पूर्णांक argc, अक्षर *argv[]);
पूर्णांक usbip_list(पूर्णांक argc, अक्षर *argv[]);
पूर्णांक usbip_bind(पूर्णांक argc, अक्षर *argv[]);
पूर्णांक usbip_unbind(पूर्णांक argc, अक्षर *argv[]);
पूर्णांक usbip_port_show(पूर्णांक argc, अक्षर *argv[]);

व्योम usbip_attach_usage(व्योम);
व्योम usbip_detach_usage(व्योम);
व्योम usbip_list_usage(व्योम);
व्योम usbip_bind_usage(व्योम);
व्योम usbip_unbind_usage(व्योम);

#पूर्ण_अगर /* __USBIP_H */
