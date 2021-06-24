<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qede NIC Driver
 * Copyright (c) 2015 QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/dcbnl.h>
#समावेश "qede.h"

अटल u8 qede_dcbnl_माला_लोtate(काष्ठा net_device *netdev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->माला_लोtate(edev->cdev);
पूर्ण

अटल u8 qede_dcbnl_setstate(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->setstate(edev->cdev, state);
पूर्ण

अटल व्योम qede_dcbnl_getpermhwaddr(काष्ठा net_device *netdev,
				     u8 *perm_addr)
अणु
	स_नकल(perm_addr, netdev->dev_addr, netdev->addr_len);
पूर्ण

अटल व्योम qede_dcbnl_getpgtccfgtx(काष्ठा net_device *netdev, पूर्णांक prio,
				    u8 *prio_type, u8 *pgid, u8 *bw_pct,
				    u8 *up_map)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	edev->ops->dcb->getpgtccfgtx(edev->cdev, prio, prio_type,
				     pgid, bw_pct, up_map);
पूर्ण

अटल व्योम qede_dcbnl_getpgbwgcfgtx(काष्ठा net_device *netdev,
				     पूर्णांक pgid, u8 *bw_pct)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	edev->ops->dcb->getpgbwgcfgtx(edev->cdev, pgid, bw_pct);
पूर्ण

अटल व्योम qede_dcbnl_getpgtccfgrx(काष्ठा net_device *netdev, पूर्णांक prio,
				    u8 *prio_type, u8 *pgid, u8 *bw_pct,
				    u8 *up_map)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	edev->ops->dcb->getpgtccfgrx(edev->cdev, prio, prio_type, pgid, bw_pct,
				     up_map);
पूर्ण

अटल व्योम qede_dcbnl_getpgbwgcfgrx(काष्ठा net_device *netdev,
				     पूर्णांक pgid, u8 *bw_pct)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	edev->ops->dcb->getpgbwgcfgrx(edev->cdev, pgid, bw_pct);
पूर्ण

अटल व्योम qede_dcbnl_getpfccfg(काष्ठा net_device *netdev, पूर्णांक prio,
				 u8 *setting)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	edev->ops->dcb->getpfccfg(edev->cdev, prio, setting);
पूर्ण

अटल व्योम qede_dcbnl_setpfccfg(काष्ठा net_device *netdev, पूर्णांक prio,
				 u8 setting)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	edev->ops->dcb->setpfccfg(edev->cdev, prio, setting);
पूर्ण

अटल u8 qede_dcbnl_अ_लोap(काष्ठा net_device *netdev, पूर्णांक capid, u8 *cap)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->अ_लोap(edev->cdev, capid, cap);
पूर्ण

अटल पूर्णांक qede_dcbnl_getnumtcs(काष्ठा net_device *netdev, पूर्णांक tcid, u8 *num)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->getnumtcs(edev->cdev, tcid, num);
पूर्ण

अटल u8 qede_dcbnl_getpfcstate(काष्ठा net_device *netdev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->getpfcstate(edev->cdev);
पूर्ण

अटल पूर्णांक qede_dcbnl_getapp(काष्ठा net_device *netdev, u8 idtype, u16 id)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->getapp(edev->cdev, idtype, id);
पूर्ण

अटल u8 qede_dcbnl_getdcbx(काष्ठा net_device *netdev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->getdcbx(edev->cdev);
पूर्ण

अटल व्योम qede_dcbnl_setpgtccfgtx(काष्ठा net_device *netdev, पूर्णांक prio,
				    u8 pri_type, u8 pgid, u8 bw_pct, u8 up_map)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->setpgtccfgtx(edev->cdev, prio, pri_type, pgid,
					    bw_pct, up_map);
पूर्ण

अटल व्योम qede_dcbnl_setpgtccfgrx(काष्ठा net_device *netdev, पूर्णांक prio,
				    u8 pri_type, u8 pgid, u8 bw_pct, u8 up_map)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->setpgtccfgrx(edev->cdev, prio, pri_type, pgid,
					    bw_pct, up_map);
पूर्ण

अटल व्योम qede_dcbnl_setpgbwgcfgtx(काष्ठा net_device *netdev, पूर्णांक pgid,
				     u8 bw_pct)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->setpgbwgcfgtx(edev->cdev, pgid, bw_pct);
पूर्ण

अटल व्योम qede_dcbnl_setpgbwgcfgrx(काष्ठा net_device *netdev, पूर्णांक pgid,
				     u8 bw_pct)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->setpgbwgcfgrx(edev->cdev, pgid, bw_pct);
पूर्ण

अटल u8 qede_dcbnl_setall(काष्ठा net_device *netdev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->setall(edev->cdev);
पूर्ण

अटल पूर्णांक qede_dcbnl_setnumtcs(काष्ठा net_device *netdev, पूर्णांक tcid, u8 num)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->setnumtcs(edev->cdev, tcid, num);
पूर्ण

अटल व्योम qede_dcbnl_setpfcstate(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->setpfcstate(edev->cdev, state);
पूर्ण

अटल पूर्णांक qede_dcbnl_setapp(काष्ठा net_device *netdev, u8 idtype, u16 idval,
			     u8 up)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->setapp(edev->cdev, idtype, idval, up);
पूर्ण

अटल u8 qede_dcbnl_setdcbx(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->setdcbx(edev->cdev, state);
पूर्ण

अटल u8 qede_dcbnl_getfeatcfg(काष्ठा net_device *netdev, पूर्णांक featid,
				u8 *flags)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->getfeatcfg(edev->cdev, featid, flags);
पूर्ण

अटल u8 qede_dcbnl_setfeatcfg(काष्ठा net_device *netdev, पूर्णांक featid, u8 flags)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->setfeatcfg(edev->cdev, featid, flags);
पूर्ण

अटल पूर्णांक qede_dcbnl_peer_getappinfo(काष्ठा net_device *netdev,
				      काष्ठा dcb_peer_app_info *info,
				      u16 *count)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->peer_getappinfo(edev->cdev, info, count);
पूर्ण

अटल पूर्णांक qede_dcbnl_peer_getapptable(काष्ठा net_device *netdev,
				       काष्ठा dcb_app *app)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->peer_getapptable(edev->cdev, app);
पूर्ण

अटल पूर्णांक qede_dcbnl_cee_peer_getpfc(काष्ठा net_device *netdev,
				      काष्ठा cee_pfc *pfc)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->cee_peer_getpfc(edev->cdev, pfc);
पूर्ण

अटल पूर्णांक qede_dcbnl_cee_peer_getpg(काष्ठा net_device *netdev,
				     काष्ठा cee_pg *pg)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->cee_peer_getpg(edev->cdev, pg);
पूर्ण

अटल पूर्णांक qede_dcbnl_ieee_getpfc(काष्ठा net_device *netdev,
				  काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->ieee_getpfc(edev->cdev, pfc);
पूर्ण

अटल पूर्णांक qede_dcbnl_ieee_setpfc(काष्ठा net_device *netdev,
				  काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->ieee_setpfc(edev->cdev, pfc);
पूर्ण

अटल पूर्णांक qede_dcbnl_ieee_getets(काष्ठा net_device *netdev,
				  काष्ठा ieee_ets *ets)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->ieee_getets(edev->cdev, ets);
पूर्ण

अटल पूर्णांक qede_dcbnl_ieee_setets(काष्ठा net_device *netdev,
				  काष्ठा ieee_ets *ets)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->ieee_setets(edev->cdev, ets);
पूर्ण

अटल पूर्णांक qede_dcbnl_ieee_getapp(काष्ठा net_device *netdev,
				  काष्ठा dcb_app *app)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->ieee_getapp(edev->cdev, app);
पूर्ण

अटल पूर्णांक qede_dcbnl_ieee_setapp(काष्ठा net_device *netdev,
				  काष्ठा dcb_app *app)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);
	पूर्णांक err;

	err = dcb_ieee_setapp(netdev, app);
	अगर (err)
		वापस err;

	वापस edev->ops->dcb->ieee_setapp(edev->cdev, app);
पूर्ण

अटल पूर्णांक qede_dcbnl_ieee_peer_getpfc(काष्ठा net_device *netdev,
				       काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->ieee_peer_getpfc(edev->cdev, pfc);
पूर्ण

अटल पूर्णांक qede_dcbnl_ieee_peer_getets(काष्ठा net_device *netdev,
				       काष्ठा ieee_ets *ets)
अणु
	काष्ठा qede_dev *edev = netdev_priv(netdev);

	वापस edev->ops->dcb->ieee_peer_getets(edev->cdev, ets);
पूर्ण

अटल स्थिर काष्ठा dcbnl_rtnl_ops qede_dcbnl_ops = अणु
	.ieee_getpfc = qede_dcbnl_ieee_getpfc,
	.ieee_setpfc = qede_dcbnl_ieee_setpfc,
	.ieee_getets = qede_dcbnl_ieee_getets,
	.ieee_setets = qede_dcbnl_ieee_setets,
	.ieee_getapp = qede_dcbnl_ieee_getapp,
	.ieee_setapp = qede_dcbnl_ieee_setapp,
	.ieee_peer_getpfc = qede_dcbnl_ieee_peer_getpfc,
	.ieee_peer_getets = qede_dcbnl_ieee_peer_getets,
	.माला_लोtate = qede_dcbnl_माला_लोtate,
	.setstate = qede_dcbnl_setstate,
	.getpermhwaddr = qede_dcbnl_getpermhwaddr,
	.getpgtccfgtx = qede_dcbnl_getpgtccfgtx,
	.getpgbwgcfgtx = qede_dcbnl_getpgbwgcfgtx,
	.getpgtccfgrx = qede_dcbnl_getpgtccfgrx,
	.getpgbwgcfgrx = qede_dcbnl_getpgbwgcfgrx,
	.getpfccfg = qede_dcbnl_getpfccfg,
	.setpfccfg = qede_dcbnl_setpfccfg,
	.अ_लोap = qede_dcbnl_अ_लोap,
	.getnumtcs = qede_dcbnl_getnumtcs,
	.getpfcstate = qede_dcbnl_getpfcstate,
	.getapp = qede_dcbnl_getapp,
	.getdcbx = qede_dcbnl_getdcbx,
	.setpgtccfgtx = qede_dcbnl_setpgtccfgtx,
	.setpgtccfgrx = qede_dcbnl_setpgtccfgrx,
	.setpgbwgcfgtx = qede_dcbnl_setpgbwgcfgtx,
	.setpgbwgcfgrx = qede_dcbnl_setpgbwgcfgrx,
	.setall = qede_dcbnl_setall,
	.setnumtcs = qede_dcbnl_setnumtcs,
	.setpfcstate = qede_dcbnl_setpfcstate,
	.setapp = qede_dcbnl_setapp,
	.setdcbx = qede_dcbnl_setdcbx,
	.setfeatcfg = qede_dcbnl_setfeatcfg,
	.getfeatcfg = qede_dcbnl_getfeatcfg,
	.peer_getappinfo = qede_dcbnl_peer_getappinfo,
	.peer_getapptable = qede_dcbnl_peer_getapptable,
	.cee_peer_getpfc = qede_dcbnl_cee_peer_getpfc,
	.cee_peer_getpg = qede_dcbnl_cee_peer_getpg,
पूर्ण;

व्योम qede_set_dcbnl_ops(काष्ठा net_device *dev)
अणु
	dev->dcbnl_ops = &qede_dcbnl_ops;
पूर्ण
