<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors: Dave Airlie <airlied@redhat.com>
 */

#समावेश <linux/pci.h>

#समावेश <drm/drm_gem_vram_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "ast_drv.h"

अटल u32 ast_get_vram_size(काष्ठा ast_निजी *ast)
अणु
	u8 jreg;
	u32 vram_size;

	ast_खोलो_key(ast);

	vram_size = AST_VIDMEM_DEFAULT_SIZE;
	jreg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xaa, 0xff);
	चयन (jreg & 3) अणु
	हाल 0:
		vram_size = AST_VIDMEM_SIZE_8M;
		अवरोध;
	हाल 1:
		vram_size = AST_VIDMEM_SIZE_16M;
		अवरोध;
	हाल 2:
		vram_size = AST_VIDMEM_SIZE_32M;
		अवरोध;
	हाल 3:
		vram_size = AST_VIDMEM_SIZE_64M;
		अवरोध;
	पूर्ण

	jreg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x99, 0xff);
	चयन (jreg & 0x03) अणु
	हाल 1:
		vram_size -= 0x100000;
		अवरोध;
	हाल 2:
		vram_size -= 0x200000;
		अवरोध;
	हाल 3:
		vram_size -= 0x400000;
		अवरोध;
	पूर्ण

	वापस vram_size;
पूर्ण

अटल व्योम ast_mm_release(काष्ठा drm_device *dev, व्योम *ptr)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	arch_phys_wc_del(ast->fb_mtrr);
	arch_io_मुक्त_memtype_wc(pci_resource_start(pdev, 0),
				pci_resource_len(pdev, 0));
पूर्ण

पूर्णांक ast_mm_init(काष्ठा ast_निजी *ast)
अणु
	काष्ठा drm_device *dev = &ast->base;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	u32 vram_size;
	पूर्णांक ret;

	vram_size = ast_get_vram_size(ast);

	ret = drmm_vram_helper_init(dev, pci_resource_start(pdev, 0), vram_size);
	अगर (ret) अणु
		drm_err(dev, "Error initializing VRAM MM; %d\n", ret);
		वापस ret;
	पूर्ण

	arch_io_reserve_memtype_wc(pci_resource_start(pdev, 0),
				   pci_resource_len(pdev, 0));
	ast->fb_mtrr = arch_phys_wc_add(pci_resource_start(pdev, 0),
					pci_resource_len(pdev, 0));

	वापस drmm_add_action_or_reset(dev, ast_mm_release, शून्य);
पूर्ण
