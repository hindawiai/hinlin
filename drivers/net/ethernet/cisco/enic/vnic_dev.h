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

#अगर_अघोषित _VNIC_DEV_H_
#घोषणा _VNIC_DEV_H_

#समावेश "vnic_resource.h"
#समावेश "vnic_devcmd.h"

#अगर_अघोषित VNIC_PADDR_TARGET
#घोषणा VNIC_PADDR_TARGET	0x0000000000000000ULL
#पूर्ण_अगर

#अगर_अघोषित पढ़ोq
अटल अंतरभूत u64 पढ़ोq(व्योम __iomem *reg)
अणु
	वापस (((u64)पढ़ोl(reg + 0x4UL) << 32) |
		(u64)पढ़ोl(reg));
पूर्ण

अटल अंतरभूत व्योम ग_लिखोq(u64 val, व्योम __iomem *reg)
अणु
	ग_लिखोl(val & 0xffffffff, reg);
	ग_लिखोl(val >> 32, reg + 0x4UL);
पूर्ण
#पूर्ण_अगर

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

क्रमागत vnic_dev_पूर्णांकr_mode अणु
	VNIC_DEV_INTR_MODE_UNKNOWN,
	VNIC_DEV_INTR_MODE_INTX,
	VNIC_DEV_INTR_MODE_MSI,
	VNIC_DEV_INTR_MODE_MSIX,
पूर्ण;

काष्ठा vnic_dev_bar अणु
	व्योम __iomem *vaddr;
	dma_addr_t bus_addr;
	अचिन्हित दीर्घ len;
पूर्ण;

काष्ठा vnic_dev_ring अणु
	व्योम *descs;
	माप_प्रकार size;
	dma_addr_t base_addr;
	माप_प्रकार base_align;
	व्योम *descs_unaligned;
	माप_प्रकार size_unaligned;
	dma_addr_t base_addr_unaligned;
	अचिन्हित पूर्णांक desc_size;
	अचिन्हित पूर्णांक desc_count;
	अचिन्हित पूर्णांक desc_avail;
पूर्ण;

क्रमागत vnic_proxy_type अणु
	PROXY_NONE,
	PROXY_BY_BDF,
	PROXY_BY_INDEX,
पूर्ण;

काष्ठा vnic_res अणु
	व्योम __iomem *vaddr;
	dma_addr_t bus_addr;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा vnic_पूर्णांकr_coal_समयr_info अणु
	u32 mul;
	u32 भाग;
	u32 max_usec;
पूर्ण;

काष्ठा vnic_dev अणु
	व्योम *priv;
	काष्ठा pci_dev *pdev;
	काष्ठा vnic_res res[RES_TYPE_MAX];
	क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode;
	काष्ठा vnic_devcmd __iomem *devcmd;
	काष्ठा vnic_devcmd_notअगरy *notअगरy;
	काष्ठा vnic_devcmd_notअगरy notअगरy_copy;
	dma_addr_t notअगरy_pa;
	u32 notअगरy_sz;
	dma_addr_t linkstatus_pa;
	काष्ठा vnic_stats *stats;
	dma_addr_t stats_pa;
	काष्ठा vnic_devcmd_fw_info *fw_info;
	dma_addr_t fw_info_pa;
	क्रमागत vnic_proxy_type proxy;
	u32 proxy_index;
	u64 args[VNIC_DEVCMD_NARGS];
	काष्ठा vnic_पूर्णांकr_coal_समयr_info पूर्णांकr_coal_समयr_info;
	काष्ठा devcmd2_controller *devcmd2;
	पूर्णांक (*devcmd_rtn)(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
			  पूर्णांक रुको);
पूर्ण;

काष्ठा vnic_stats;

व्योम *vnic_dev_priv(काष्ठा vnic_dev *vdev);
अचिन्हित पूर्णांक vnic_dev_get_res_count(काष्ठा vnic_dev *vdev,
	क्रमागत vnic_res_type type);
व्योम __iomem *vnic_dev_get_res(काष्ठा vnic_dev *vdev, क्रमागत vnic_res_type type,
	अचिन्हित पूर्णांक index);
व्योम vnic_dev_clear_desc_ring(काष्ठा vnic_dev_ring *ring);
पूर्णांक vnic_dev_alloc_desc_ring(काष्ठा vnic_dev *vdev, काष्ठा vnic_dev_ring *ring,
	अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size);
व्योम vnic_dev_मुक्त_desc_ring(काष्ठा vnic_dev *vdev,
	काष्ठा vnic_dev_ring *ring);
पूर्णांक vnic_dev_cmd(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
	u64 *a0, u64 *a1, पूर्णांक रुको);
व्योम vnic_dev_cmd_proxy_by_index_start(काष्ठा vnic_dev *vdev, u16 index);
व्योम vnic_dev_cmd_proxy_end(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_fw_info(काष्ठा vnic_dev *vdev,
	काष्ठा vnic_devcmd_fw_info **fw_info);
पूर्णांक vnic_dev_spec(काष्ठा vnic_dev *vdev, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक size,
	व्योम *value);
पूर्णांक vnic_dev_stats_dump(काष्ठा vnic_dev *vdev, काष्ठा vnic_stats **stats);
पूर्णांक vnic_dev_hang_notअगरy(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_packet_filter(काष्ठा vnic_dev *vdev, पूर्णांक directed, पूर्णांक multicast,
	पूर्णांक broadcast, पूर्णांक promisc, पूर्णांक allmulti);
पूर्णांक vnic_dev_add_addr(काष्ठा vnic_dev *vdev, स्थिर u8 *addr);
पूर्णांक vnic_dev_del_addr(काष्ठा vnic_dev *vdev, स्थिर u8 *addr);
पूर्णांक vnic_dev_get_mac_addr(काष्ठा vnic_dev *vdev, u8 *mac_addr);
पूर्णांक vnic_dev_notअगरy_set(काष्ठा vnic_dev *vdev, u16 पूर्णांकr);
पूर्णांक vnic_dev_notअगरy_unset(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_link_status(काष्ठा vnic_dev *vdev);
u32 vnic_dev_port_speed(काष्ठा vnic_dev *vdev);
u32 vnic_dev_msg_lvl(काष्ठा vnic_dev *vdev);
u32 vnic_dev_mtu(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_बंद(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_enable_रुको(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_disable(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_खोलो(काष्ठा vnic_dev *vdev, पूर्णांक arg);
पूर्णांक vnic_dev_खोलो_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *करोne);
पूर्णांक vnic_dev_init(काष्ठा vnic_dev *vdev, पूर्णांक arg);
पूर्णांक vnic_dev_deinit(काष्ठा vnic_dev *vdev);
व्योम vnic_dev_पूर्णांकr_coal_समयr_info_शेष(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_पूर्णांकr_coal_समयr_info(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_hang_reset(काष्ठा vnic_dev *vdev, पूर्णांक arg);
पूर्णांक vnic_dev_soft_reset(काष्ठा vnic_dev *vdev, पूर्णांक arg);
पूर्णांक vnic_dev_hang_reset_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *करोne);
पूर्णांक vnic_dev_soft_reset_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *करोne);
व्योम vnic_dev_set_पूर्णांकr_mode(काष्ठा vnic_dev *vdev,
	क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode);
क्रमागत vnic_dev_पूर्णांकr_mode vnic_dev_get_पूर्णांकr_mode(काष्ठा vnic_dev *vdev);
u32 vnic_dev_पूर्णांकr_coal_समयr_usec_to_hw(काष्ठा vnic_dev *vdev, u32 usec);
u32 vnic_dev_पूर्णांकr_coal_समयr_hw_to_usec(काष्ठा vnic_dev *vdev, u32 hw_cycles);
u32 vnic_dev_get_पूर्णांकr_coal_समयr_max(काष्ठा vnic_dev *vdev);
व्योम vnic_dev_unरेजिस्टर(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_set_ig_vlan_reग_लिखो_mode(काष्ठा vnic_dev *vdev,
	u8 ig_vlan_reग_लिखो_mode);
काष्ठा vnic_dev *vnic_dev_रेजिस्टर(काष्ठा vnic_dev *vdev,
	व्योम *priv, काष्ठा pci_dev *pdev, काष्ठा vnic_dev_bar *bar,
	अचिन्हित पूर्णांक num_bars);
काष्ठा pci_dev *vnic_dev_get_pdev(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_init_prov2(काष्ठा vnic_dev *vdev, u8 *buf, u32 len);
पूर्णांक vnic_dev_enable2(काष्ठा vnic_dev *vdev, पूर्णांक active);
पूर्णांक vnic_dev_enable2_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *status);
पूर्णांक vnic_dev_deinit_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *status);
पूर्णांक vnic_dev_set_mac_addr(काष्ठा vnic_dev *vdev, u8 *mac_addr);
पूर्णांक vnic_dev_classअगरier(काष्ठा vnic_dev *vdev, u8 cmd, u16 *entry,
			काष्ठा filter *data);
पूर्णांक vnic_devcmd_init(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_overlay_offload_ctrl(काष्ठा vnic_dev *vdev, u8 overlay, u8 config);
पूर्णांक vnic_dev_overlay_offload_cfg(काष्ठा vnic_dev *vdev, u8 overlay,
				 u16 vxlan_udp_port_number);
पूर्णांक vnic_dev_get_supported_feature_ver(काष्ठा vnic_dev *vdev, u8 feature,
				       u64 *supported_versions, u64 *a1);
पूर्णांक vnic_dev_capable_rss_hash_type(काष्ठा vnic_dev *vdev, u8 *rss_hash_type);

#पूर्ण_अगर /* _VNIC_DEV_H_ */
