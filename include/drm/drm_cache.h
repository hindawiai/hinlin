<शैली गुरु>
/**************************************************************************
 *
 * Copyright 2009 Red Hat Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 **************************************************************************/
/*
 * Authors:
 * Dave Airlie <airlied@redhat.com>
 */

#अगर_अघोषित _DRM_CACHE_H_
#घोषणा _DRM_CACHE_H_

#समावेश <linux/scatterlist.h>

व्योम drm_clflush_pages(काष्ठा page *pages[], अचिन्हित दीर्घ num_pages);
व्योम drm_clflush_sg(काष्ठा sg_table *st);
व्योम drm_clflush_virt_range(व्योम *addr, अचिन्हित दीर्घ length);
bool drm_need_swiotlb(पूर्णांक dma_bits);


अटल अंतरभूत bool drm_arch_can_wc_memory(व्योम)
अणु
#अगर defined(CONFIG_PPC) && !defined(CONFIG_NOT_COHERENT_CACHE)
	वापस false;
#या_अगर defined(CONFIG_MIPS) && defined(CONFIG_CPU_LOONGSON64)
	वापस false;
#या_अगर defined(CONFIG_ARM) || defined(CONFIG_ARM64)
	/*
	 * The DRM driver stack is deचिन्हित to work with cache coherent devices
	 * only, but permits an optimization to be enabled in some हालs, where
	 * क्रम some buffers, both the CPU and the GPU use uncached mappings,
	 * removing the need क्रम DMA snooping and allocation in the CPU caches.
	 *
	 * The use of uncached GPU mappings relies on the correct implementation
	 * of the PCIe NoSnoop TLP attribute by the platक्रमm, otherwise the GPU
	 * will use cached mappings nonetheless. On x86 platक्रमms, this करोes not
	 * seem to matter, as uncached CPU mappings will snoop the caches in any
	 * हाल. However, on ARM and arm64, enabling this optimization on a
	 * platक्रमm where NoSnoop is ignored results in loss of coherency, which
	 * अवरोधs correct operation of the device. Since we have no way of
	 * detecting whether NoSnoop works or not, just disable this
	 * optimization entirely क्रम ARM and arm64.
	 */
	वापस false;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर
