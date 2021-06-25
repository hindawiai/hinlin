<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* net/aपंचांग/संकेतing.h - ATM संकेतing */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */


#अगर_अघोषित NET_ATM_SIGNALING_H
#घोषणा NET_ATM_SIGNALING_H

#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांगsvc.h>


बाह्य काष्ठा aपंचांग_vcc *sigd; /* needed in svc_release */


/*
 * sigd_enq is a wrapper क्रम sigd_enq2, covering the more common हालs, and
 * aव्योमing huge lists of null values.
 */

व्योम sigd_enq2(काष्ठा aपंचांग_vcc *vcc,क्रमागत aपंचांगsvc_msg_type type,
    काष्ठा aपंचांग_vcc *listen_vcc,स्थिर काष्ठा sockaddr_aपंचांगpvc *pvc,
    स्थिर काष्ठा sockaddr_aपंचांगsvc *svc,स्थिर काष्ठा aपंचांग_qos *qos,पूर्णांक reply);
व्योम sigd_enq(काष्ठा aपंचांग_vcc *vcc,क्रमागत aपंचांगsvc_msg_type type,
    काष्ठा aपंचांग_vcc *listen_vcc,स्थिर काष्ठा sockaddr_aपंचांगpvc *pvc,
    स्थिर काष्ठा sockaddr_aपंचांगsvc *svc);
पूर्णांक sigd_attach(काष्ठा aपंचांग_vcc *vcc);

#पूर्ण_अगर
