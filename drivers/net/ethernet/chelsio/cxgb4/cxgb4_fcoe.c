<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2015 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_घोषित CONFIG_CHELSIO_T4_FCOE

#समावेश <scsi/fc/fc_fs.h>
#समावेश <scsi/libfcoe.h>
#समावेश "cxgb4.h"

bool cxgb_fcoe_sof_eof_supported(काष्ठा adapter *adap, काष्ठा sk_buff *skb)
अणु
	काष्ठा fcoe_hdr *fcoeh = (काष्ठा fcoe_hdr *)skb_network_header(skb);
	u8 sof = fcoeh->fcoe_sof;
	u8 eof = 0;

	अगर ((sof != FC_SOF_I3) && (sof != FC_SOF_N3)) अणु
		dev_err(adap->pdev_dev, "Unsupported SOF 0x%x\n", sof);
		वापस false;
	पूर्ण

	skb_copy_bits(skb, skb->len - 4, &eof, 1);

	अगर ((eof != FC_खातापूर्ण_N) && (eof != FC_खातापूर्ण_T)) अणु
		dev_err(adap->pdev_dev, "Unsupported EOF 0x%x\n", eof);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * cxgb_fcoe_enable - enable FCoE offload features
 * @netdev: net device
 *
 * Returns 0 on success or -EINVAL on failure.
 */
पूर्णांक cxgb_fcoe_enable(काष्ठा net_device *netdev)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा cxgb_fcoe *fcoe = &pi->fcoe;

	अगर (is_t4(adap->params.chip))
		वापस -EINVAL;

	अगर (!(adap->flags & CXGB4_FULL_INIT_DONE))
		वापस -EINVAL;

	dev_info(adap->pdev_dev, "Enabling FCoE offload features\n");

	netdev->features |= NETIF_F_FCOE_CRC;
	netdev->vlan_features |= NETIF_F_FCOE_CRC;
	netdev->features |= NETIF_F_FCOE_MTU;
	netdev->vlan_features |= NETIF_F_FCOE_MTU;

	netdev_features_change(netdev);

	fcoe->flags |= CXGB_FCOE_ENABLED;

	वापस 0;
पूर्ण

/**
 * cxgb_fcoe_disable - disable FCoE offload
 * @netdev: net device
 *
 * Returns 0 on success or -EINVAL on failure.
 */
पूर्णांक cxgb_fcoe_disable(काष्ठा net_device *netdev)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा cxgb_fcoe *fcoe = &pi->fcoe;

	अगर (!(fcoe->flags & CXGB_FCOE_ENABLED))
		वापस -EINVAL;

	dev_info(adap->pdev_dev, "Disabling FCoE offload features\n");

	fcoe->flags &= ~CXGB_FCOE_ENABLED;

	netdev->features &= ~NETIF_F_FCOE_CRC;
	netdev->vlan_features &= ~NETIF_F_FCOE_CRC;
	netdev->features &= ~NETIF_F_FCOE_MTU;
	netdev->vlan_features &= ~NETIF_F_FCOE_MTU;

	netdev_features_change(netdev);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_FCOE */
