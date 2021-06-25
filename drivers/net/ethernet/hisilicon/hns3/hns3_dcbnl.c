<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश "hnae3.h"
#समावेश "hns3_enet.h"

अटल पूर्णांक hns3_dcbnl_ieee_getets(काष्ठा net_device *ndev, काष्ठा ieee_ets *ets)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);

	अगर (hns3_nic_resetting(ndev))
		वापस -EBUSY;

	अगर (h->kinfo.dcb_ops->ieee_getets)
		वापस h->kinfo.dcb_ops->ieee_getets(h, ets);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक hns3_dcbnl_ieee_setets(काष्ठा net_device *ndev, काष्ठा ieee_ets *ets)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);

	अगर (hns3_nic_resetting(ndev))
		वापस -EBUSY;

	अगर (h->kinfo.dcb_ops->ieee_setets)
		वापस h->kinfo.dcb_ops->ieee_setets(h, ets);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक hns3_dcbnl_ieee_getpfc(काष्ठा net_device *ndev, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);

	अगर (hns3_nic_resetting(ndev))
		वापस -EBUSY;

	अगर (h->kinfo.dcb_ops->ieee_getpfc)
		वापस h->kinfo.dcb_ops->ieee_getpfc(h, pfc);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक hns3_dcbnl_ieee_setpfc(काष्ठा net_device *ndev, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);

	अगर (hns3_nic_resetting(ndev))
		वापस -EBUSY;

	अगर (h->kinfo.dcb_ops->ieee_setpfc)
		वापस h->kinfo.dcb_ops->ieee_setpfc(h, pfc);

	वापस -EOPNOTSUPP;
पूर्ण

/* DCBX configuration */
अटल u8 hns3_dcbnl_getdcbx(काष्ठा net_device *ndev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);

	अगर (h->kinfo.dcb_ops->getdcbx)
		वापस h->kinfo.dcb_ops->getdcbx(h);

	वापस 0;
पूर्ण

/* वापस 0 अगर successful, otherwise fail */
अटल u8 hns3_dcbnl_setdcbx(काष्ठा net_device *ndev, u8 mode)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);

	अगर (h->kinfo.dcb_ops->setdcbx)
		वापस h->kinfo.dcb_ops->setdcbx(h, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dcbnl_rtnl_ops hns3_dcbnl_ops = अणु
	.ieee_getets	= hns3_dcbnl_ieee_getets,
	.ieee_setets	= hns3_dcbnl_ieee_setets,
	.ieee_getpfc	= hns3_dcbnl_ieee_getpfc,
	.ieee_setpfc	= hns3_dcbnl_ieee_setpfc,
	.getdcbx	= hns3_dcbnl_getdcbx,
	.setdcbx	= hns3_dcbnl_setdcbx,
पूर्ण;

/* hclge_dcbnl_setup - DCBNL setup
 * @handle: the corresponding vport handle
 * Set up DCBNL
 */
व्योम hns3_dcbnl_setup(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा net_device *dev = handle->kinfo.netdev;

	अगर ((!handle->kinfo.dcb_ops) || (handle->flags & HNAE3_SUPPORT_VF))
		वापस;

	dev->dcbnl_ops = &hns3_dcbnl_ops;
पूर्ण
