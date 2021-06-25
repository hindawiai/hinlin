<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* net/aपंचांग/addr.h - Local ATM address registry */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */


#अगर_अघोषित NET_ATM_ADDR_H
#घोषणा NET_ATM_ADDR_H

#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>

व्योम aपंचांग_reset_addr(काष्ठा aपंचांग_dev *dev, क्रमागत aपंचांग_addr_type_t type);
पूर्णांक aपंचांग_add_addr(काष्ठा aपंचांग_dev *dev, स्थिर काष्ठा sockaddr_aपंचांगsvc *addr,
		 क्रमागत aपंचांग_addr_type_t type);
पूर्णांक aपंचांग_del_addr(काष्ठा aपंचांग_dev *dev, स्थिर काष्ठा sockaddr_aपंचांगsvc *addr,
		 क्रमागत aपंचांग_addr_type_t type);
पूर्णांक aपंचांग_get_addr(काष्ठा aपंचांग_dev *dev, काष्ठा sockaddr_aपंचांगsvc __user *buf,
		 माप_प्रकार size, क्रमागत aपंचांग_addr_type_t type);

#पूर्ण_अगर
