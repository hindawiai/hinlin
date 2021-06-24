<शैली गुरु>
/*
 * Copyright 2004 The Unichrome Project. All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE UNICHROME PROJECT, AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Author: Thomas Hellstrथघm 2004.
 */

#अगर_अघोषित _VIA_VERIFIER_H_
#घोषणा _VIA_VERIFIER_H_

प्रकार क्रमागत अणु
	no_sequence = 0,
	z_address,
	dest_address,
	tex_address
पूर्ण drm_via_sequence_t;

प्रकार काष्ठा अणु
	अचिन्हित texture;
	uपूर्णांक32_t z_addr;
	uपूर्णांक32_t d_addr;
	uपूर्णांक32_t t_addr[2][10];
	uपूर्णांक32_t pitch[2][10];
	uपूर्णांक32_t height[2][10];
	uपूर्णांक32_t tex_level_lo[2];
	uपूर्णांक32_t tex_level_hi[2];
	uपूर्णांक32_t tex_palette_size[2];
	uपूर्णांक32_t tex_npot[2];
	drm_via_sequence_t unfinished;
	पूर्णांक agp_texture;
	पूर्णांक multitex;
	काष्ठा drm_device *dev;
	drm_local_map_t *map_cache;
	uपूर्णांक32_t vertex_count;
	पूर्णांक agp;
	स्थिर uपूर्णांक32_t *buf_start;
पूर्ण drm_via_state_t;

बाह्य पूर्णांक via_verअगरy_command_stream(स्थिर uपूर्णांक32_t *buf, अचिन्हित पूर्णांक size,
				     काष्ठा drm_device *dev, पूर्णांक agp);
बाह्य पूर्णांक via_parse_command_stream(काष्ठा drm_device *dev, स्थिर uपूर्णांक32_t *buf,
				    अचिन्हित पूर्णांक size);

#पूर्ण_अगर
