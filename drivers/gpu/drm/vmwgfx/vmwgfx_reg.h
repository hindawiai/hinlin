<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright 2009-2014 VMware, Inc., Palo Alto, CA., USA
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
 **************************************************************************/

/**
 * This file contains भव hardware defines क्रम kernel space.
 */

#अगर_अघोषित _VMWGFX_REG_H_
#घोषणा _VMWGFX_REG_H_

#समावेश <linux/types.h>

#घोषणा VMWGFX_INDEX_PORT     0x0
#घोषणा VMWGFX_VALUE_PORT     0x1
#घोषणा VMWGFX_IRQSTATUS_PORT 0x8

काष्ठा svga_guest_mem_descriptor अणु
	u32 ppn;
	u32 num_pages;
पूर्ण;

काष्ठा svga_fअगरo_cmd_fence अणु
	u32 fence;
पूर्ण;

#घोषणा SVGA_SYNC_GENERIC         1
#घोषणा SVGA_SYNC_FIFOFULL        2

#समावेश "device_include/svga3d_reg.h"

#पूर्ण_अगर
