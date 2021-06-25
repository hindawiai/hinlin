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

#अगर_अघोषित _ENIC_DEV_H_
#घोषणा _ENIC_DEV_H_

#समावेश "vnic_dev.h"
#समावेश "vnic_vic.h"

/*
 * Calls the devcmd function given by argument vnicdevcmdfn.
 * If vf argument is valid, it proxies the devcmd
 */
#घोषणा ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnicdevcmdfn, ...) \
	करो अणु \
		spin_lock_bh(&enic->devcmd_lock); \
		अगर (enic_is_valid_vf(enic, vf)) अणु \
			vnic_dev_cmd_proxy_by_index_start(enic->vdev, vf); \
			err = vnicdevcmdfn(enic->vdev, ##__VA_ARGS__); \
			vnic_dev_cmd_proxy_end(enic->vdev); \
		पूर्ण अन्यथा अणु \
			err = vnicdevcmdfn(enic->vdev, ##__VA_ARGS__); \
		पूर्ण \
		spin_unlock_bh(&enic->devcmd_lock); \
	पूर्ण जबतक (0)

पूर्णांक enic_dev_fw_info(काष्ठा enic *enic, काष्ठा vnic_devcmd_fw_info **fw_info);
पूर्णांक enic_dev_stats_dump(काष्ठा enic *enic, काष्ठा vnic_stats **vstats);
पूर्णांक enic_dev_add_station_addr(काष्ठा enic *enic);
पूर्णांक enic_dev_del_station_addr(काष्ठा enic *enic);
पूर्णांक enic_dev_packet_filter(काष्ठा enic *enic, पूर्णांक directed, पूर्णांक multicast,
	पूर्णांक broadcast, पूर्णांक promisc, पूर्णांक allmulti);
पूर्णांक enic_dev_add_addr(काष्ठा enic *enic, स्थिर u8 *addr);
पूर्णांक enic_dev_del_addr(काष्ठा enic *enic, स्थिर u8 *addr);
पूर्णांक enic_vlan_rx_add_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid);
पूर्णांक enic_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid);
पूर्णांक enic_dev_notअगरy_unset(काष्ठा enic *enic);
पूर्णांक enic_dev_hang_notअगरy(काष्ठा enic *enic);
पूर्णांक enic_dev_set_ig_vlan_reग_लिखो_mode(काष्ठा enic *enic);
पूर्णांक enic_dev_enable(काष्ठा enic *enic);
पूर्णांक enic_dev_disable(काष्ठा enic *enic);
पूर्णांक enic_dev_पूर्णांकr_coal_समयr_info(काष्ठा enic *enic);
पूर्णांक enic_dev_status_to_त्रुटि_सं(पूर्णांक devcmd_status);

#पूर्ण_अगर /* _ENIC_DEV_H_ */
