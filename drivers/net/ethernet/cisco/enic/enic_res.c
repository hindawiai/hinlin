<शैली गुरु>
/*
 * Copyright 2008-2010 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
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

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>

#समावेश "wq_enet_desc.h"
#समावेश "rq_enet_desc.h"
#समावेश "cq_enet_desc.h"
#समावेश "vnic_resource.h"
#समावेश "vnic_enet.h"
#समावेश "vnic_dev.h"
#समावेश "vnic_wq.h"
#समावेश "vnic_rq.h"
#समावेश "vnic_cq.h"
#समावेश "vnic_intr.h"
#समावेश "vnic_stats.h"
#समावेश "vnic_nic.h"
#समावेश "vnic_rss.h"
#समावेश "enic_res.h"
#समावेश "enic.h"

पूर्णांक enic_get_vnic_config(काष्ठा enic *enic)
अणु
	काष्ठा vnic_enet_config *c = &enic->config;
	पूर्णांक err;

	err = vnic_dev_get_mac_addr(enic->vdev, enic->mac_addr);
	अगर (err) अणु
		dev_err(enic_get_dev(enic),
			"Error getting MAC addr, %d\n", err);
		वापस err;
	पूर्ण

#घोषणा GET_CONFIG(m) \
	करो अणु \
		err = vnic_dev_spec(enic->vdev, \
			दुरत्व(काष्ठा vnic_enet_config, m), \
			माप(c->m), &c->m); \
		अगर (err) अणु \
			dev_err(enic_get_dev(enic), \
				"Error getting %s, %d\n", #m, err); \
			वापस err; \
		पूर्ण \
	पूर्ण जबतक (0)

	GET_CONFIG(flags);
	GET_CONFIG(wq_desc_count);
	GET_CONFIG(rq_desc_count);
	GET_CONFIG(mtu);
	GET_CONFIG(पूर्णांकr_समयr_type);
	GET_CONFIG(पूर्णांकr_mode);
	GET_CONFIG(पूर्णांकr_समयr_usec);
	GET_CONFIG(loop_tag);
	GET_CONFIG(num_arfs);

	c->wq_desc_count =
		min_t(u32, ENIC_MAX_WQ_DESCS,
		max_t(u32, ENIC_MIN_WQ_DESCS,
		c->wq_desc_count));
	c->wq_desc_count &= 0xffffffe0; /* must be aligned to groups of 32 */

	c->rq_desc_count =
		min_t(u32, ENIC_MAX_RQ_DESCS,
		max_t(u32, ENIC_MIN_RQ_DESCS,
		c->rq_desc_count));
	c->rq_desc_count &= 0xffffffe0; /* must be aligned to groups of 32 */

	अगर (c->mtu == 0)
		c->mtu = 1500;
	c->mtu = min_t(u16, ENIC_MAX_MTU,
		max_t(u16, ENIC_MIN_MTU,
		c->mtu));

	c->पूर्णांकr_समयr_usec = min_t(u32, c->पूर्णांकr_समयr_usec,
		vnic_dev_get_पूर्णांकr_coal_समयr_max(enic->vdev));

	dev_info(enic_get_dev(enic),
		"vNIC MAC addr %pM wq/rq %d/%d mtu %d\n",
		enic->mac_addr, c->wq_desc_count, c->rq_desc_count, c->mtu);

	dev_info(enic_get_dev(enic), "vNIC csum tx/rx %s/%s "
		"tso/lro %s/%s rss %s intr mode %s type %s timer %d usec "
		"loopback tag 0x%04x\n",
		ENIC_SETTING(enic, TXCSUM) ? "yes" : "no",
		ENIC_SETTING(enic, RXCSUM) ? "yes" : "no",
		ENIC_SETTING(enic, TSO) ? "yes" : "no",
		ENIC_SETTING(enic, LRO) ? "yes" : "no",
		ENIC_SETTING(enic, RSS) ? "yes" : "no",
		c->पूर्णांकr_mode == VENET_INTR_MODE_INTX ? "INTx" :
		c->पूर्णांकr_mode == VENET_INTR_MODE_MSI ? "MSI" :
		c->पूर्णांकr_mode == VENET_INTR_MODE_ANY ? "any" :
		"unknown",
		c->पूर्णांकr_समयr_type == VENET_INTR_TYPE_MIN ? "min" :
		c->पूर्णांकr_समयr_type == VENET_INTR_TYPE_IDLE ? "idle" :
		"unknown",
		c->पूर्णांकr_समयr_usec,
		c->loop_tag);

	वापस 0;
पूर्ण

पूर्णांक enic_add_vlan(काष्ठा enic *enic, u16 vlanid)
अणु
	u64 a0 = vlanid, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	err = vnic_dev_cmd(enic->vdev, CMD_VLAN_ADD, &a0, &a1, रुको);
	अगर (err)
		dev_err(enic_get_dev(enic), "Can't add vlan id, %d\n", err);

	वापस err;
पूर्ण

पूर्णांक enic_del_vlan(काष्ठा enic *enic, u16 vlanid)
अणु
	u64 a0 = vlanid, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	err = vnic_dev_cmd(enic->vdev, CMD_VLAN_DEL, &a0, &a1, रुको);
	अगर (err)
		dev_err(enic_get_dev(enic), "Can't delete vlan id, %d\n", err);

	वापस err;
पूर्ण

पूर्णांक enic_set_nic_cfg(काष्ठा enic *enic, u8 rss_शेष_cpu, u8 rss_hash_type,
	u8 rss_hash_bits, u8 rss_base_cpu, u8 rss_enable, u8 tso_ipid_split_en,
	u8 ig_vlan_strip_en)
अणु
	क्रमागत vnic_devcmd_cmd cmd = CMD_NIC_CFG;
	u64 a0, a1;
	u32 nic_cfg;
	पूर्णांक रुको = 1000;

	vnic_set_nic_cfg(&nic_cfg, rss_शेष_cpu,
		rss_hash_type, rss_hash_bits, rss_base_cpu,
		rss_enable, tso_ipid_split_en, ig_vlan_strip_en);

	a0 = nic_cfg;
	a1 = 0;

	अगर (rss_hash_type & (NIC_CFG_RSS_HASH_TYPE_UDP_IPV4 |
			     NIC_CFG_RSS_HASH_TYPE_UDP_IPV6))
		cmd = CMD_NIC_CFG_CHK;

	वापस vnic_dev_cmd(enic->vdev, cmd, &a0, &a1, रुको);
पूर्ण

पूर्णांक enic_set_rss_key(काष्ठा enic *enic, dma_addr_t key_pa, u64 len)
अणु
	u64 a0 = (u64)key_pa, a1 = len;
	पूर्णांक रुको = 1000;

	वापस vnic_dev_cmd(enic->vdev, CMD_RSS_KEY, &a0, &a1, रुको);
पूर्ण

पूर्णांक enic_set_rss_cpu(काष्ठा enic *enic, dma_addr_t cpu_pa, u64 len)
अणु
	u64 a0 = (u64)cpu_pa, a1 = len;
	पूर्णांक रुको = 1000;

	वापस vnic_dev_cmd(enic->vdev, CMD_RSS_CPU, &a0, &a1, रुको);
पूर्ण

व्योम enic_मुक्त_vnic_resources(काष्ठा enic *enic)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < enic->wq_count; i++)
		vnic_wq_मुक्त(&enic->wq[i]);
	क्रम (i = 0; i < enic->rq_count; i++)
		vnic_rq_मुक्त(&enic->rq[i]);
	क्रम (i = 0; i < enic->cq_count; i++)
		vnic_cq_मुक्त(&enic->cq[i]);
	क्रम (i = 0; i < enic->पूर्णांकr_count; i++)
		vnic_पूर्णांकr_मुक्त(&enic->पूर्णांकr[i]);
पूर्ण

व्योम enic_get_res_counts(काष्ठा enic *enic)
अणु
	enic->wq_count = vnic_dev_get_res_count(enic->vdev, RES_TYPE_WQ);
	enic->rq_count = vnic_dev_get_res_count(enic->vdev, RES_TYPE_RQ);
	enic->cq_count = vnic_dev_get_res_count(enic->vdev, RES_TYPE_CQ);
	enic->पूर्णांकr_count = vnic_dev_get_res_count(enic->vdev,
		RES_TYPE_INTR_CTRL);

	dev_info(enic_get_dev(enic),
		"vNIC resources avail: wq %d rq %d cq %d intr %d\n",
		enic->wq_count, enic->rq_count,
		enic->cq_count, enic->पूर्णांकr_count);
पूर्ण

व्योम enic_init_vnic_resources(काष्ठा enic *enic)
अणु
	क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode;
	अचिन्हित पूर्णांक mask_on_निश्चितion;
	अचिन्हित पूर्णांक पूर्णांकerrupt_offset;
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_enable;
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_offset;
	अचिन्हित पूर्णांक cq_index;
	अचिन्हित पूर्णांक i;

	पूर्णांकr_mode = vnic_dev_get_पूर्णांकr_mode(enic->vdev);

	/* Init RQ/WQ resources.
	 *
	 * RQ[0 - n-1] poपूर्णांक to CQ[0 - n-1]
	 * WQ[0 - m-1] poपूर्णांक to CQ[n - n+m-1]
	 *
	 * Error पूर्णांकerrupt is not enabled क्रम MSI.
	 */

	चयन (पूर्णांकr_mode) अणु
	हाल VNIC_DEV_INTR_MODE_INTX:
	हाल VNIC_DEV_INTR_MODE_MSIX:
		error_पूर्णांकerrupt_enable = 1;
		error_पूर्णांकerrupt_offset = enic->पूर्णांकr_count - 2;
		अवरोध;
	शेष:
		error_पूर्णांकerrupt_enable = 0;
		error_पूर्णांकerrupt_offset = 0;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < enic->rq_count; i++) अणु
		cq_index = i;
		vnic_rq_init(&enic->rq[i],
			cq_index,
			error_पूर्णांकerrupt_enable,
			error_पूर्णांकerrupt_offset);
	पूर्ण

	क्रम (i = 0; i < enic->wq_count; i++) अणु
		cq_index = enic->rq_count + i;
		vnic_wq_init(&enic->wq[i],
			cq_index,
			error_पूर्णांकerrupt_enable,
			error_पूर्णांकerrupt_offset);
	पूर्ण

	/* Init CQ resources
	 *
	 * CQ[0 - n+m-1] poपूर्णांक to INTR[0] क्रम INTx, MSI
	 * CQ[0 - n+m-1] poपूर्णांक to INTR[0 - n+m-1] क्रम MSI-X
	 */

	क्रम (i = 0; i < enic->cq_count; i++) अणु

		चयन (पूर्णांकr_mode) अणु
		हाल VNIC_DEV_INTR_MODE_MSIX:
			पूर्णांकerrupt_offset = i;
			अवरोध;
		शेष:
			पूर्णांकerrupt_offset = 0;
			अवरोध;
		पूर्ण

		vnic_cq_init(&enic->cq[i],
			0 /* flow_control_enable */,
			1 /* color_enable */,
			0 /* cq_head */,
			0 /* cq_tail */,
			1 /* cq_tail_color */,
			1 /* पूर्णांकerrupt_enable */,
			1 /* cq_entry_enable */,
			0 /* cq_message_enable */,
			पूर्णांकerrupt_offset,
			0 /* cq_message_addr */);
	पूर्ण

	/* Init INTR resources
	 *
	 * mask_on_निश्चितion is not used क्रम INTx due to the level-
	 * triggered nature of INTx
	 */

	चयन (पूर्णांकr_mode) अणु
	हाल VNIC_DEV_INTR_MODE_MSI:
	हाल VNIC_DEV_INTR_MODE_MSIX:
		mask_on_निश्चितion = 1;
		अवरोध;
	शेष:
		mask_on_निश्चितion = 0;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < enic->पूर्णांकr_count; i++) अणु
		vnic_पूर्णांकr_init(&enic->पूर्णांकr[i],
			enic->config.पूर्णांकr_समयr_usec,
			enic->config.पूर्णांकr_समयr_type,
			mask_on_निश्चितion);
	पूर्ण
पूर्ण

पूर्णांक enic_alloc_vnic_resources(काष्ठा enic *enic)
अणु
	क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	पूर्णांकr_mode = vnic_dev_get_पूर्णांकr_mode(enic->vdev);

	dev_info(enic_get_dev(enic), "vNIC resources used:  "
		"wq %d rq %d cq %d intr %d intr mode %s\n",
		enic->wq_count, enic->rq_count,
		enic->cq_count, enic->पूर्णांकr_count,
		पूर्णांकr_mode == VNIC_DEV_INTR_MODE_INTX ? "legacy PCI INTx" :
		पूर्णांकr_mode == VNIC_DEV_INTR_MODE_MSI ? "MSI" :
		पूर्णांकr_mode == VNIC_DEV_INTR_MODE_MSIX ? "MSI-X" :
		"unknown");

	/* Allocate queue resources
	 */

	क्रम (i = 0; i < enic->wq_count; i++) अणु
		err = vnic_wq_alloc(enic->vdev, &enic->wq[i], i,
			enic->config.wq_desc_count,
			माप(काष्ठा wq_enet_desc));
		अगर (err)
			जाओ err_out_cleanup;
	पूर्ण

	क्रम (i = 0; i < enic->rq_count; i++) अणु
		err = vnic_rq_alloc(enic->vdev, &enic->rq[i], i,
			enic->config.rq_desc_count,
			माप(काष्ठा rq_enet_desc));
		अगर (err)
			जाओ err_out_cleanup;
	पूर्ण

	क्रम (i = 0; i < enic->cq_count; i++) अणु
		अगर (i < enic->rq_count)
			err = vnic_cq_alloc(enic->vdev, &enic->cq[i], i,
				enic->config.rq_desc_count,
				माप(काष्ठा cq_enet_rq_desc));
		अन्यथा
			err = vnic_cq_alloc(enic->vdev, &enic->cq[i], i,
				enic->config.wq_desc_count,
				माप(काष्ठा cq_enet_wq_desc));
		अगर (err)
			जाओ err_out_cleanup;
	पूर्ण

	क्रम (i = 0; i < enic->पूर्णांकr_count; i++) अणु
		err = vnic_पूर्णांकr_alloc(enic->vdev, &enic->पूर्णांकr[i], i);
		अगर (err)
			जाओ err_out_cleanup;
	पूर्ण

	/* Hook reमुख्यing resource
	 */

	enic->legacy_pba = vnic_dev_get_res(enic->vdev,
		RES_TYPE_INTR_PBA_LEGACY, 0);
	अगर (!enic->legacy_pba && पूर्णांकr_mode == VNIC_DEV_INTR_MODE_INTX) अणु
		dev_err(enic_get_dev(enic),
			"Failed to hook legacy pba resource\n");
		err = -ENODEV;
		जाओ err_out_cleanup;
	पूर्ण

	वापस 0;

err_out_cleanup:
	enic_मुक्त_vnic_resources(enic);

	वापस err;
पूर्ण
