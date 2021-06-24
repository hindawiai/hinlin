<शैली गुरु>
/*
 * Copyright 2008 Cisco Systems, Inc.  All rights reserved.
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
 */
#अगर_अघोषित _VNIC_DEV_H_
#घोषणा _VNIC_DEV_H_

#समावेश "vnic_resource.h"
#समावेश "vnic_devcmd.h"

/*
 * These defines aव्योम symbol clash between fnic and enic (Cisco 10G Eth
 * Driver) when both are built with CONFIG options =y
 */
#घोषणा vnic_dev_priv fnic_dev_priv
#घोषणा vnic_dev_get_res_count fnic_dev_get_res_count
#घोषणा vnic_dev_get_res fnic_dev_get_res
#घोषणा vnic_dev_desc_ring_size fnic_dev_desc_ring_siz
#घोषणा vnic_dev_clear_desc_ring fnic_dev_clear_desc_ring
#घोषणा vnic_dev_alloc_desc_ring fnic_dev_alloc_desc_ring
#घोषणा vnic_dev_मुक्त_desc_ring fnic_dev_मुक्त_desc_ring
#घोषणा vnic_dev_cmd fnic_dev_cmd
#घोषणा vnic_dev_fw_info fnic_dev_fw_info
#घोषणा vnic_dev_spec fnic_dev_spec
#घोषणा vnic_dev_stats_clear fnic_dev_stats_clear
#घोषणा vnic_dev_cmd_init fnic_dev_cmd_init
#घोषणा vnic_dev_stats_dump fnic_dev_stats_dump
#घोषणा vnic_dev_hang_notअगरy fnic_dev_hang_notअगरy
#घोषणा vnic_dev_packet_filter fnic_dev_packet_filter
#घोषणा vnic_dev_add_addr fnic_dev_add_addr
#घोषणा vnic_dev_del_addr fnic_dev_del_addr
#घोषणा vnic_dev_mac_addr fnic_dev_mac_addr
#घोषणा vnic_dev_notअगरy_set fnic_dev_notअगरy_set
#घोषणा vnic_dev_notअगरy_unset fnic_dev_notअगरy_unset
#घोषणा vnic_dev_link_status fnic_dev_link_status
#घोषणा vnic_dev_port_speed fnic_dev_port_speed
#घोषणा vnic_dev_msg_lvl fnic_dev_msg_lvl
#घोषणा vnic_dev_mtu fnic_dev_mtu
#घोषणा vnic_dev_link_करोwn_cnt fnic_dev_link_करोwn_cnt
#घोषणा vnic_dev_बंद fnic_dev_बंद
#घोषणा vnic_dev_enable fnic_dev_enable
#घोषणा vnic_dev_disable fnic_dev_disable
#घोषणा vnic_dev_खोलो fnic_dev_खोलो
#घोषणा vnic_dev_खोलो_करोne fnic_dev_खोलो_करोne
#घोषणा vnic_dev_init fnic_dev_init
#घोषणा vnic_dev_soft_reset fnic_dev_soft_reset
#घोषणा vnic_dev_soft_reset_करोne fnic_dev_soft_reset_करोne
#घोषणा vnic_dev_set_पूर्णांकr_mode fnic_dev_set_पूर्णांकr_mode
#घोषणा vnic_dev_get_पूर्णांकr_mode fnic_dev_get_पूर्णांकr_mode
#घोषणा vnic_dev_unरेजिस्टर fnic_dev_unरेजिस्टर
#घोषणा vnic_dev_रेजिस्टर fnic_dev_रेजिस्टर

#अगर_अघोषित VNIC_PADDR_TARGET
#घोषणा VNIC_PADDR_TARGET	0x0000000000000000ULL
#पूर्ण_अगर

#अगर_अघोषित पढ़ोq
अटल अंतरभूत u64 पढ़ोq(व्योम __iomem *reg)
अणु
	वापस ((u64)पढ़ोl(reg + 0x4UL) << 32) | (u64)पढ़ोl(reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखोq(u64 val, व्योम __iomem *reg)
अणु
	ग_लिखोl(val & 0xffffffff, reg);
	ग_लिखोl(val >> 32, reg + 0x4UL);
पूर्ण
#पूर्ण_अगर

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

काष्ठा vnic_dev;
काष्ठा vnic_stats;

व्योम *vnic_dev_priv(काष्ठा vnic_dev *vdev);
अचिन्हित पूर्णांक vnic_dev_get_res_count(काष्ठा vnic_dev *vdev,
				    क्रमागत vnic_res_type type);
व्योम __iomem *vnic_dev_get_res(काष्ठा vnic_dev *vdev, क्रमागत vnic_res_type type,
			       अचिन्हित पूर्णांक index);
अचिन्हित पूर्णांक vnic_dev_desc_ring_size(काष्ठा vnic_dev_ring *ring,
				     अचिन्हित पूर्णांक desc_count,
				     अचिन्हित पूर्णांक desc_size);
व्योम vnic_dev_clear_desc_ring(काष्ठा vnic_dev_ring *ring);
पूर्णांक vnic_dev_alloc_desc_ring(काष्ठा vnic_dev *vdev, काष्ठा vnic_dev_ring *ring,
			     अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size);
व्योम vnic_dev_मुक्त_desc_ring(काष्ठा vnic_dev *vdev,
			     काष्ठा vnic_dev_ring *ring);
पूर्णांक vnic_dev_cmd(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
		 u64 *a0, u64 *a1, पूर्णांक रुको);
पूर्णांक vnic_dev_fw_info(काष्ठा vnic_dev *vdev,
		     काष्ठा vnic_devcmd_fw_info **fw_info);
पूर्णांक vnic_dev_spec(काष्ठा vnic_dev *vdev, अचिन्हित पूर्णांक offset,
		  अचिन्हित पूर्णांक size, व्योम *value);
पूर्णांक vnic_dev_stats_clear(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_cmd_init(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_stats_dump(काष्ठा vnic_dev *vdev, काष्ठा vnic_stats **stats);
पूर्णांक vnic_dev_hang_notअगरy(काष्ठा vnic_dev *vdev);
व्योम vnic_dev_packet_filter(काष्ठा vnic_dev *vdev, पूर्णांक directed, पूर्णांक multicast,
			    पूर्णांक broadcast, पूर्णांक promisc, पूर्णांक allmulti);
व्योम vnic_dev_add_addr(काष्ठा vnic_dev *vdev, u8 *addr);
व्योम vnic_dev_del_addr(काष्ठा vnic_dev *vdev, u8 *addr);
पूर्णांक vnic_dev_mac_addr(काष्ठा vnic_dev *vdev, u8 *mac_addr);
पूर्णांक vnic_dev_notअगरy_set(काष्ठा vnic_dev *vdev, u16 पूर्णांकr);
व्योम vnic_dev_notअगरy_unset(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_link_status(काष्ठा vnic_dev *vdev);
u32 vnic_dev_port_speed(काष्ठा vnic_dev *vdev);
u32 vnic_dev_msg_lvl(काष्ठा vnic_dev *vdev);
u32 vnic_dev_mtu(काष्ठा vnic_dev *vdev);
u32 vnic_dev_link_करोwn_cnt(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_बंद(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_enable(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_disable(काष्ठा vnic_dev *vdev);
पूर्णांक vnic_dev_खोलो(काष्ठा vnic_dev *vdev, पूर्णांक arg);
पूर्णांक vnic_dev_खोलो_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *करोne);
पूर्णांक vnic_dev_init(काष्ठा vnic_dev *vdev, पूर्णांक arg);
u16 vnic_dev_set_शेष_vlan(काष्ठा vnic_dev *vdev,
				u16 new_शेष_vlan);
पूर्णांक vnic_dev_soft_reset(काष्ठा vnic_dev *vdev, पूर्णांक arg);
पूर्णांक vnic_dev_soft_reset_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *करोne);
व्योम vnic_dev_set_पूर्णांकr_mode(काष्ठा vnic_dev *vdev,
			    क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode);
क्रमागत vnic_dev_पूर्णांकr_mode vnic_dev_get_पूर्णांकr_mode(काष्ठा vnic_dev *vdev);
व्योम vnic_dev_unरेजिस्टर(काष्ठा vnic_dev *vdev);
काष्ठा vnic_dev *vnic_dev_रेजिस्टर(काष्ठा vnic_dev *vdev,
				   व्योम *priv, काष्ठा pci_dev *pdev,
				   काष्ठा vnic_dev_bar *bar);

#पूर्ण_अगर /* _VNIC_DEV_H_ */
