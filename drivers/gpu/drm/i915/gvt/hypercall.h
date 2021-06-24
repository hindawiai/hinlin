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

#अगर_अघोषित _GVT_HYPERCALL_H_
#घोषणा _GVT_HYPERCALL_H_

#समावेश <linux/types.h>

काष्ठा device;

क्रमागत hypervisor_type अणु
	INTEL_GVT_HYPERVISOR_XEN = 0,
	INTEL_GVT_HYPERVISOR_KVM,
पूर्ण;

/*
 * Specअगरic GVT-g MPT modules function collections. Currently GVT-g supports
 * both Xen and KVM by providing dedicated hypervisor-related MPT modules.
 */
काष्ठा पूर्णांकel_gvt_mpt अणु
	क्रमागत hypervisor_type type;
	पूर्णांक (*host_init)(काष्ठा device *dev, व्योम *gvt, स्थिर व्योम *ops);
	व्योम (*host_निकास)(काष्ठा device *dev, व्योम *gvt);
	पूर्णांक (*attach_vgpu)(व्योम *vgpu, अचिन्हित दीर्घ *handle);
	व्योम (*detach_vgpu)(व्योम *vgpu);
	पूर्णांक (*inject_msi)(अचिन्हित दीर्घ handle, u32 addr, u16 data);
	अचिन्हित दीर्घ (*from_virt_to_mfn)(व्योम *p);
	पूर्णांक (*enable_page_track)(अचिन्हित दीर्घ handle, u64 gfn);
	पूर्णांक (*disable_page_track)(अचिन्हित दीर्घ handle, u64 gfn);
	पूर्णांक (*पढ़ो_gpa)(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gpa, व्योम *buf,
			अचिन्हित दीर्घ len);
	पूर्णांक (*ग_लिखो_gpa)(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gpa, व्योम *buf,
			 अचिन्हित दीर्घ len);
	अचिन्हित दीर्घ (*gfn_to_mfn)(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gfn);

	पूर्णांक (*dma_map_guest_page)(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gfn,
				  अचिन्हित दीर्घ size, dma_addr_t *dma_addr);
	व्योम (*dma_unmap_guest_page)(अचिन्हित दीर्घ handle, dma_addr_t dma_addr);

	पूर्णांक (*dma_pin_guest_page)(अचिन्हित दीर्घ handle, dma_addr_t dma_addr);

	पूर्णांक (*map_gfn_to_mfn)(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gfn,
			      अचिन्हित दीर्घ mfn, अचिन्हित पूर्णांक nr, bool map);
	पूर्णांक (*set_trap_area)(अचिन्हित दीर्घ handle, u64 start, u64 end,
			     bool map);
	पूर्णांक (*set_opregion)(व्योम *vgpu);
	पूर्णांक (*set_edid)(व्योम *vgpu, पूर्णांक port_num);
	पूर्णांक (*get_vfio_device)(व्योम *vgpu);
	व्योम (*put_vfio_device)(व्योम *vgpu);
	bool (*is_valid_gfn)(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gfn);
पूर्ण;

#पूर्ण_अगर /* _GVT_HYPERCALL_H_ */
