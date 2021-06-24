<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* aपंचांग_tcp.h - Driver-specअगरic declarations of the ATMTCP driver (क्रम use by
	       driver-specअगरic utilities) */

/* Written 1997-2000 by Werner Almesberger, EPFL LRC/ICA */

#अगर_अघोषित LINUX_ATM_TCP_H
#घोषणा LINUX_ATM_TCP_H

#समावेश <uapi/linux/aपंचांग_tcp.h>


काष्ठा aपंचांग_tcp_ops अणु
	पूर्णांक (*attach)(काष्ठा aपंचांग_vcc *vcc,पूर्णांक itf);
	पूर्णांक (*create_persistent)(पूर्णांक itf);
	पूर्णांक (*हटाओ_persistent)(पूर्णांक itf);
	काष्ठा module *owner;
पूर्ण;

बाह्य काष्ठा aपंचांग_tcp_ops aपंचांग_tcp_ops;

#पूर्ण_अगर
