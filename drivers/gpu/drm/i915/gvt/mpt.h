<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Eddie Dong <eddie.करोng@पूर्णांकel.com>
 *    Dexuan Cui
 *    Jike Song <jike.song@पूर्णांकel.com>
 *
 * Contributors:
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#अगर_अघोषित _GVT_MPT_H_
#घोषणा _GVT_MPT_H_

#समावेश "gvt.h"

/**
 * DOC: Hypervisor Service APIs क्रम GVT-g Core Logic
 *
 * This is the glue layer between specअगरic hypervisor MPT modules and GVT-g core
 * logic. Each kind of hypervisor MPT module provides a collection of function
 * callbacks and will be attached to GVT host when the driver is loading.
 * GVT-g core logic will call these APIs to request specअगरic services from
 * hypervisor.
 */

/**
 * पूर्णांकel_gvt_hypervisor_host_init - init GVT-g host side
 *
 * Returns:
 * Zero on success, negative error code अगर failed
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_host_init(काष्ठा device *dev,
						 व्योम *gvt, स्थिर व्योम *ops)
अणु
	अगर (!पूर्णांकel_gvt_host.mpt->host_init)
		वापस -ENODEV;

	वापस पूर्णांकel_gvt_host.mpt->host_init(dev, gvt, ops);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_host_निकास - निकास GVT-g host side
 */
अटल अंतरभूत व्योम पूर्णांकel_gvt_hypervisor_host_निकास(काष्ठा device *dev, व्योम *gvt)
अणु
	/* optional to provide */
	अगर (!पूर्णांकel_gvt_host.mpt->host_निकास)
		वापस;

	पूर्णांकel_gvt_host.mpt->host_निकास(dev, gvt);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_attach_vgpu - call hypervisor to initialize vGPU
 * related stuffs inside hypervisor.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_attach_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	/* optional to provide */
	अगर (!पूर्णांकel_gvt_host.mpt->attach_vgpu)
		वापस 0;

	वापस पूर्णांकel_gvt_host.mpt->attach_vgpu(vgpu, &vgpu->handle);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_detach_vgpu - call hypervisor to release vGPU
 * related stuffs inside hypervisor.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत व्योम पूर्णांकel_gvt_hypervisor_detach_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	/* optional to provide */
	अगर (!पूर्णांकel_gvt_host.mpt->detach_vgpu)
		वापस;

	पूर्णांकel_gvt_host.mpt->detach_vgpu(vgpu);
पूर्ण

#घोषणा MSI_CAP_CONTROL(offset) (offset + 2)
#घोषणा MSI_CAP_ADDRESS(offset) (offset + 4)
#घोषणा MSI_CAP_DATA(offset) (offset + 8)
#घोषणा MSI_CAP_EN 0x1

/**
 * पूर्णांकel_gvt_hypervisor_inject_msi - inject a MSI पूर्णांकerrupt पूर्णांकo vGPU
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_inject_msi(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	अचिन्हित दीर्घ offset = vgpu->gvt->device_info.msi_cap_offset;
	u16 control, data;
	u32 addr;
	पूर्णांक ret;

	control = *(u16 *)(vgpu_cfg_space(vgpu) + MSI_CAP_CONTROL(offset));
	addr = *(u32 *)(vgpu_cfg_space(vgpu) + MSI_CAP_ADDRESS(offset));
	data = *(u16 *)(vgpu_cfg_space(vgpu) + MSI_CAP_DATA(offset));

	/* Do not generate MSI अगर MSIEN is disable */
	अगर (!(control & MSI_CAP_EN))
		वापस 0;

	अगर (WARN(control & GENMASK(15, 1), "only support one MSI format\n"))
		वापस -EINVAL;

	trace_inject_msi(vgpu->id, addr, data);

	ret = पूर्णांकel_gvt_host.mpt->inject_msi(vgpu->handle, addr, data);
	अगर (ret)
		वापस ret;
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_set_wp_page - translate a host VA पूर्णांकo MFN
 * @p: host kernel भव address
 *
 * Returns:
 * MFN on success, INTEL_GVT_INVALID_ADDR अगर failed.
 */
अटल अंतरभूत अचिन्हित दीर्घ पूर्णांकel_gvt_hypervisor_virt_to_mfn(व्योम *p)
अणु
	वापस पूर्णांकel_gvt_host.mpt->from_virt_to_mfn(p);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_enable_page_track - track a guest page
 * @vgpu: a vGPU
 * @gfn: the gfn of guest
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_enable_page_track(
		काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn)
अणु
	वापस पूर्णांकel_gvt_host.mpt->enable_page_track(vgpu->handle, gfn);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_disable_page_track - untrack a guest page
 * @vgpu: a vGPU
 * @gfn: the gfn of guest
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_disable_page_track(
		काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn)
अणु
	वापस पूर्णांकel_gvt_host.mpt->disable_page_track(vgpu->handle, gfn);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_पढ़ो_gpa - copy data from GPA to host data buffer
 * @vgpu: a vGPU
 * @gpa: guest physical address
 * @buf: host data buffer
 * @len: data length
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित दीर्घ gpa, व्योम *buf, अचिन्हित दीर्घ len)
अणु
	वापस पूर्णांकel_gvt_host.mpt->पढ़ो_gpa(vgpu->handle, gpa, buf, len);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa - copy data from host data buffer to GPA
 * @vgpu: a vGPU
 * @gpa: guest physical address
 * @buf: host data buffer
 * @len: data length
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित दीर्घ gpa, व्योम *buf, अचिन्हित दीर्घ len)
अणु
	वापस पूर्णांकel_gvt_host.mpt->ग_लिखो_gpa(vgpu->handle, gpa, buf, len);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_gfn_to_mfn - translate a GFN to MFN
 * @vgpu: a vGPU
 * @gpfn: guest pfn
 *
 * Returns:
 * MFN on success, INTEL_GVT_INVALID_ADDR अगर failed.
 */
अटल अंतरभूत अचिन्हित दीर्घ पूर्णांकel_gvt_hypervisor_gfn_to_mfn(
		काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn)
अणु
	वापस पूर्णांकel_gvt_host.mpt->gfn_to_mfn(vgpu->handle, gfn);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_dma_map_guest_page - setup dma map क्रम guest page
 * @vgpu: a vGPU
 * @gfn: guest pfn
 * @size: page size
 * @dma_addr: retrieve allocated dma addr
 *
 * Returns:
 * 0 on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_dma_map_guest_page(
		काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn, अचिन्हित दीर्घ size,
		dma_addr_t *dma_addr)
अणु
	वापस पूर्णांकel_gvt_host.mpt->dma_map_guest_page(vgpu->handle, gfn, size,
						      dma_addr);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_dma_unmap_guest_page - cancel dma map क्रम guest page
 * @vgpu: a vGPU
 * @dma_addr: the mapped dma addr
 */
अटल अंतरभूत व्योम पूर्णांकel_gvt_hypervisor_dma_unmap_guest_page(
		काष्ठा पूर्णांकel_vgpu *vgpu, dma_addr_t dma_addr)
अणु
	पूर्णांकel_gvt_host.mpt->dma_unmap_guest_page(vgpu->handle, dma_addr);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_dma_pin_guest_page - pin guest dma buf
 * @vgpu: a vGPU
 * @dma_addr: guest dma addr
 *
 * Returns:
 * 0 on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक
पूर्णांकel_gvt_hypervisor_dma_pin_guest_page(काष्ठा पूर्णांकel_vgpu *vgpu,
					dma_addr_t dma_addr)
अणु
	वापस पूर्णांकel_gvt_host.mpt->dma_pin_guest_page(vgpu->handle, dma_addr);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_map_gfn_to_mfn - map a GFN region to MFN
 * @vgpu: a vGPU
 * @gfn: guest PFN
 * @mfn: host PFN
 * @nr: amount of PFNs
 * @map: map or unmap
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_map_gfn_to_mfn(
		काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn,
		अचिन्हित दीर्घ mfn, अचिन्हित पूर्णांक nr,
		bool map)
अणु
	/* a MPT implementation could have MMIO mapped अन्यथाwhere */
	अगर (!पूर्णांकel_gvt_host.mpt->map_gfn_to_mfn)
		वापस 0;

	वापस पूर्णांकel_gvt_host.mpt->map_gfn_to_mfn(vgpu->handle, gfn, mfn, nr,
						  map);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_set_trap_area - Trap a guest PA region
 * @vgpu: a vGPU
 * @start: the beginning of the guest physical address region
 * @end: the end of the guest physical address region
 * @map: map or unmap
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_set_trap_area(
		काष्ठा पूर्णांकel_vgpu *vgpu, u64 start, u64 end, bool map)
अणु
	/* a MPT implementation could have MMIO trapped अन्यथाwhere */
	अगर (!पूर्णांकel_gvt_host.mpt->set_trap_area)
		वापस 0;

	वापस पूर्णांकel_gvt_host.mpt->set_trap_area(vgpu->handle, start, end, map);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_set_opregion - Set opregion क्रम guest
 * @vgpu: a vGPU
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_set_opregion(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	अगर (!पूर्णांकel_gvt_host.mpt->set_opregion)
		वापस 0;

	वापस पूर्णांकel_gvt_host.mpt->set_opregion(vgpu);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_set_edid - Set EDID region क्रम guest
 * @vgpu: a vGPU
 * @port_num: display port number
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_set_edid(काष्ठा पूर्णांकel_vgpu *vgpu,
						पूर्णांक port_num)
अणु
	अगर (!पूर्णांकel_gvt_host.mpt->set_edid)
		वापस 0;

	वापस पूर्णांकel_gvt_host.mpt->set_edid(vgpu, port_num);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_get_vfio_device - increase vfio device ref count
 * @vgpu: a vGPU
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_gvt_hypervisor_get_vfio_device(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	अगर (!पूर्णांकel_gvt_host.mpt->get_vfio_device)
		वापस 0;

	वापस पूर्णांकel_gvt_host.mpt->get_vfio_device(vgpu);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_put_vfio_device - decrease vfio device ref count
 * @vgpu: a vGPU
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
अटल अंतरभूत व्योम पूर्णांकel_gvt_hypervisor_put_vfio_device(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	अगर (!पूर्णांकel_gvt_host.mpt->put_vfio_device)
		वापस;

	पूर्णांकel_gvt_host.mpt->put_vfio_device(vgpu);
पूर्ण

/**
 * पूर्णांकel_gvt_hypervisor_is_valid_gfn - check अगर a visible gfn
 * @vgpu: a vGPU
 * @gfn: guest PFN
 *
 * Returns:
 * true on valid gfn, false on not.
 */
अटल अंतरभूत bool पूर्णांकel_gvt_hypervisor_is_valid_gfn(
		काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn)
अणु
	अगर (!पूर्णांकel_gvt_host.mpt->is_valid_gfn)
		वापस true;

	वापस पूर्णांकel_gvt_host.mpt->is_valid_gfn(vgpu->handle, gfn);
पूर्ण

पूर्णांक पूर्णांकel_gvt_रेजिस्टर_hypervisor(स्थिर काष्ठा पूर्णांकel_gvt_mpt *);
व्योम पूर्णांकel_gvt_unरेजिस्टर_hypervisor(व्योम);

#पूर्ण_अगर /* _GVT_MPT_H_ */
