<शैली गुरु>
/*
 * Copyright 2011 Cisco Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>

#समावेश "vnic_dev.h"
#समावेश "vnic_vic.h"
#समावेश "enic_res.h"
#समावेश "enic.h"
#समावेश "enic_dev.h"

पूर्णांक enic_dev_fw_info(काष्ठा enic *enic, काष्ठा vnic_devcmd_fw_info **fw_info)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_fw_info(enic->vdev, fw_info);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_stats_dump(काष्ठा enic *enic, काष्ठा vnic_stats **vstats)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_stats_dump(enic->vdev, vstats);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_add_station_addr(काष्ठा enic *enic)
अणु
	पूर्णांक err;

	अगर (!is_valid_ether_addr(enic->netdev->dev_addr))
		वापस -EADDRNOTAVAIL;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_add_addr(enic->vdev, enic->netdev->dev_addr);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_del_station_addr(काष्ठा enic *enic)
अणु
	पूर्णांक err;

	अगर (!is_valid_ether_addr(enic->netdev->dev_addr))
		वापस -EADDRNOTAVAIL;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_del_addr(enic->vdev, enic->netdev->dev_addr);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_packet_filter(काष्ठा enic *enic, पूर्णांक directed, पूर्णांक multicast,
	पूर्णांक broadcast, पूर्णांक promisc, पूर्णांक allmulti)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_packet_filter(enic->vdev, directed,
		multicast, broadcast, promisc, allmulti);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_add_addr(काष्ठा enic *enic, स्थिर u8 *addr)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_add_addr(enic->vdev, addr);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_del_addr(काष्ठा enic *enic, स्थिर u8 *addr)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_del_addr(enic->vdev, addr);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_notअगरy_unset(काष्ठा enic *enic)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_notअगरy_unset(enic->vdev);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_hang_notअगरy(काष्ठा enic *enic)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_hang_notअगरy(enic->vdev);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_set_ig_vlan_reग_लिखो_mode(काष्ठा enic *enic)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_set_ig_vlan_reग_लिखो_mode(enic->vdev,
		IG_VLAN_REWRITE_MODE_PRIORITY_TAG_DEFAULT_VLAN);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_enable(काष्ठा enic *enic)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_enable_रुको(enic->vdev);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_disable(काष्ठा enic *enic)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_disable(enic->vdev);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_पूर्णांकr_coal_समयr_info(काष्ठा enic *enic)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_पूर्णांकr_coal_समयr_info(enic->vdev);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

/* rtnl lock is held */
पूर्णांक enic_vlan_rx_add_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = enic_add_vlan(enic, vid);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

/* rtnl lock is held */
पूर्णांक enic_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	err = enic_del_vlan(enic, vid);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

पूर्णांक enic_dev_status_to_त्रुटि_सं(पूर्णांक devcmd_status)
अणु
	चयन (devcmd_status) अणु
	हाल ERR_SUCCESS:
		वापस 0;
	हाल ERR_EINVAL:
		वापस -EINVAL;
	हाल ERR_EFAULT:
		वापस -EFAULT;
	हाल ERR_EPERM:
		वापस -EPERM;
	हाल ERR_EBUSY:
		वापस -EBUSY;
	हाल ERR_ECMDUNKNOWN:
	हाल ERR_ENOTSUPPORTED:
		वापस -EOPNOTSUPP;
	हाल ERR_EBADSTATE:
		वापस -EINVAL;
	हाल ERR_ENOMEM:
		वापस -ENOMEM;
	हाल ERR_ETIMEDOUT:
		वापस -ETIMEDOUT;
	हाल ERR_ELINKDOWN:
		वापस -ENETDOWN;
	हाल ERR_EINPROGRESS:
		वापस -EINPROGRESS;
	हाल ERR_EMAXRES:
	शेष:
		वापस (devcmd_status < 0) ? devcmd_status : -1;
	पूर्ण
पूर्ण
