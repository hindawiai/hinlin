<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
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
	ग_लिखोl(lower_32_bits(val), reg);
	ग_लिखोl(upper_32_bits(val), reg + 0x4UL);
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

व्योम *svnic_dev_priv(काष्ठा vnic_dev *vdev);
अचिन्हित पूर्णांक svnic_dev_get_res_count(काष्ठा vnic_dev *vdev,
				    क्रमागत vnic_res_type type);
व्योम __iomem *svnic_dev_get_res(काष्ठा vnic_dev *vdev, क्रमागत vnic_res_type type,
			       अचिन्हित पूर्णांक index);
अचिन्हित पूर्णांक svnic_dev_desc_ring_size(काष्ठा vnic_dev_ring *ring,
				     अचिन्हित पूर्णांक desc_count,
				     अचिन्हित पूर्णांक desc_size);
व्योम svnic_dev_clear_desc_ring(काष्ठा vnic_dev_ring *ring);
पूर्णांक svnic_dev_alloc_desc_ring(काष्ठा vnic_dev *vdev, काष्ठा vnic_dev_ring *ring,
			     अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size);
व्योम svnic_dev_मुक्त_desc_ring(काष्ठा vnic_dev *vdev,
			     काष्ठा vnic_dev_ring *ring);
पूर्णांक svnic_dev_cmd(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
		 u64 *a0, u64 *a1, पूर्णांक रुको);
पूर्णांक svnic_dev_fw_info(काष्ठा vnic_dev *vdev,
		     काष्ठा vnic_devcmd_fw_info **fw_info);
पूर्णांक svnic_dev_spec(काष्ठा vnic_dev *vdev, अचिन्हित पूर्णांक offset,
		  अचिन्हित पूर्णांक size, व्योम *value);
पूर्णांक svnic_dev_stats_clear(काष्ठा vnic_dev *vdev);
पूर्णांक svnic_dev_stats_dump(काष्ठा vnic_dev *vdev, काष्ठा vnic_stats **stats);
पूर्णांक svnic_dev_notअगरy_set(काष्ठा vnic_dev *vdev, u16 पूर्णांकr);
व्योम svnic_dev_notअगरy_unset(काष्ठा vnic_dev *vdev);
पूर्णांक svnic_dev_link_status(काष्ठा vnic_dev *vdev);
u32 svnic_dev_link_करोwn_cnt(काष्ठा vnic_dev *vdev);
पूर्णांक svnic_dev_बंद(काष्ठा vnic_dev *vdev);
पूर्णांक svnic_dev_enable_रुको(काष्ठा vnic_dev *vdev);
पूर्णांक svnic_dev_disable(काष्ठा vnic_dev *vdev);
पूर्णांक svnic_dev_खोलो(काष्ठा vnic_dev *vdev, पूर्णांक arg);
पूर्णांक svnic_dev_खोलो_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *करोne);
पूर्णांक svnic_dev_init(काष्ठा vnic_dev *vdev, पूर्णांक arg);
काष्ठा vnic_dev *svnic_dev_alloc_discover(काष्ठा vnic_dev *vdev,
					 व्योम *priv, काष्ठा pci_dev *pdev,
					 काष्ठा vnic_dev_bar *bar,
					 अचिन्हित पूर्णांक num_bars);
व्योम svnic_dev_set_पूर्णांकr_mode(काष्ठा vnic_dev *vdev,
			    क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode);
क्रमागत vnic_dev_पूर्णांकr_mode svnic_dev_get_पूर्णांकr_mode(काष्ठा vnic_dev *vdev);
व्योम svnic_dev_unरेजिस्टर(काष्ठा vnic_dev *vdev);
पूर्णांक svnic_dev_cmd_init(काष्ठा vnic_dev *vdev, पूर्णांक fallback);
#पूर्ण_अगर /* _VNIC_DEV_H_ */
