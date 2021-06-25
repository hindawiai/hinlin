<शैली गुरु>
/*
 * Copyright 2004 The Unichrome Project. All Rights Reserved.
 * Copyright 2005 Thomas Hellstrom. All Rights Reserved.
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
 * THE AUTHOR(S), AND/OR THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Author: Thomas Hellstrom 2004, 2005.
 * This code was written using करोcs obtained under NDA from VIA Inc.
 *
 * Don't run this code directly on an AGP buffer. Due to cache problems it will
 * be very slow.
 */

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_legacy.h>
#समावेश <drm/via_drm.h>

#समावेश "via_3d_reg.h"
#समावेश "via_drv.h"
#समावेश "via_verifier.h"

प्रकार क्रमागत अणु
	state_command,
	state_header2,
	state_header1,
	state_vheader5,
	state_vheader6,
	state_error
पूर्ण verअगरier_state_t;

प्रकार क्रमागत अणु
	no_check = 0,
	check_क्रम_header2,
	check_क्रम_header1,
	check_क्रम_header2_err,
	check_क्रम_header1_err,
	check_क्रम_fire,
	check_z_buffer_addr0,
	check_z_buffer_addr1,
	check_z_buffer_addr_mode,
	check_destination_addr0,
	check_destination_addr1,
	check_destination_addr_mode,
	check_क्रम_dummy,
	check_क्रम_dd,
	check_texture_addr0,
	check_texture_addr1,
	check_texture_addr2,
	check_texture_addr3,
	check_texture_addr4,
	check_texture_addr5,
	check_texture_addr6,
	check_texture_addr7,
	check_texture_addr8,
	check_texture_addr_mode,
	check_क्रम_vertex_count,
	check_number_texunits,
	क्रमbidden_command
पूर्ण hazard_t;

/*
 * Associates each hazard above with a possible multi-command
 * sequence. For example an address that is split over multiple
 * commands and that needs to be checked at the first command
 * that करोes not include any part of the address.
 */

अटल drm_via_sequence_t seqs[] = अणु
	no_sequence,
	no_sequence,
	no_sequence,
	no_sequence,
	no_sequence,
	no_sequence,
	z_address,
	z_address,
	z_address,
	dest_address,
	dest_address,
	dest_address,
	no_sequence,
	no_sequence,
	tex_address,
	tex_address,
	tex_address,
	tex_address,
	tex_address,
	tex_address,
	tex_address,
	tex_address,
	tex_address,
	tex_address,
	no_sequence
पूर्ण;

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक code;
	hazard_t hz;
पूर्ण hz_init_t;

अटल hz_init_t init_table1[] = अणु
	अणु0xf2, check_क्रम_header2_errपूर्ण,
	अणु0xf0, check_क्रम_header1_errपूर्ण,
	अणु0xee, check_क्रम_fireपूर्ण,
	अणु0xcc, check_क्रम_dummyपूर्ण,
	अणु0xdd, check_क्रम_ddपूर्ण,
	अणु0x00, no_checkपूर्ण,
	अणु0x10, check_z_buffer_addr0पूर्ण,
	अणु0x11, check_z_buffer_addr1पूर्ण,
	अणु0x12, check_z_buffer_addr_modeपूर्ण,
	अणु0x13, no_checkपूर्ण,
	अणु0x14, no_checkपूर्ण,
	अणु0x15, no_checkपूर्ण,
	अणु0x23, no_checkपूर्ण,
	अणु0x24, no_checkपूर्ण,
	अणु0x33, no_checkपूर्ण,
	अणु0x34, no_checkपूर्ण,
	अणु0x35, no_checkपूर्ण,
	अणु0x36, no_checkपूर्ण,
	अणु0x37, no_checkपूर्ण,
	अणु0x38, no_checkपूर्ण,
	अणु0x39, no_checkपूर्ण,
	अणु0x3A, no_checkपूर्ण,
	अणु0x3B, no_checkपूर्ण,
	अणु0x3C, no_checkपूर्ण,
	अणु0x3D, no_checkपूर्ण,
	अणु0x3E, no_checkपूर्ण,
	अणु0x40, check_destination_addr0पूर्ण,
	अणु0x41, check_destination_addr1पूर्ण,
	अणु0x42, check_destination_addr_modeपूर्ण,
	अणु0x43, no_checkपूर्ण,
	अणु0x44, no_checkपूर्ण,
	अणु0x50, no_checkपूर्ण,
	अणु0x51, no_checkपूर्ण,
	अणु0x52, no_checkपूर्ण,
	अणु0x53, no_checkपूर्ण,
	अणु0x54, no_checkपूर्ण,
	अणु0x55, no_checkपूर्ण,
	अणु0x56, no_checkपूर्ण,
	अणु0x57, no_checkपूर्ण,
	अणु0x58, no_checkपूर्ण,
	अणु0x70, no_checkपूर्ण,
	अणु0x71, no_checkपूर्ण,
	अणु0x78, no_checkपूर्ण,
	अणु0x79, no_checkपूर्ण,
	अणु0x7A, no_checkपूर्ण,
	अणु0x7B, no_checkपूर्ण,
	अणु0x7C, no_checkपूर्ण,
	अणु0x7D, check_क्रम_vertex_countपूर्ण
पूर्ण;

अटल hz_init_t init_table2[] = अणु
	अणु0xf2, check_क्रम_header2_errपूर्ण,
	अणु0xf0, check_क्रम_header1_errपूर्ण,
	अणु0xee, check_क्रम_fireपूर्ण,
	अणु0xcc, check_क्रम_dummyपूर्ण,
	अणु0x00, check_texture_addr0पूर्ण,
	अणु0x01, check_texture_addr0पूर्ण,
	अणु0x02, check_texture_addr0पूर्ण,
	अणु0x03, check_texture_addr0पूर्ण,
	अणु0x04, check_texture_addr0पूर्ण,
	अणु0x05, check_texture_addr0पूर्ण,
	अणु0x06, check_texture_addr0पूर्ण,
	अणु0x07, check_texture_addr0पूर्ण,
	अणु0x08, check_texture_addr0पूर्ण,
	अणु0x09, check_texture_addr0पूर्ण,
	अणु0x20, check_texture_addr1पूर्ण,
	अणु0x21, check_texture_addr1पूर्ण,
	अणु0x22, check_texture_addr1पूर्ण,
	अणु0x23, check_texture_addr4पूर्ण,
	अणु0x2B, check_texture_addr3पूर्ण,
	अणु0x2C, check_texture_addr3पूर्ण,
	अणु0x2D, check_texture_addr3पूर्ण,
	अणु0x2E, check_texture_addr3पूर्ण,
	अणु0x2F, check_texture_addr3पूर्ण,
	अणु0x30, check_texture_addr3पूर्ण,
	अणु0x31, check_texture_addr3पूर्ण,
	अणु0x32, check_texture_addr3पूर्ण,
	अणु0x33, check_texture_addr3पूर्ण,
	अणु0x34, check_texture_addr3पूर्ण,
	अणु0x4B, check_texture_addr5पूर्ण,
	अणु0x4C, check_texture_addr6पूर्ण,
	अणु0x51, check_texture_addr7पूर्ण,
	अणु0x52, check_texture_addr8पूर्ण,
	अणु0x77, check_texture_addr2पूर्ण,
	अणु0x78, no_checkपूर्ण,
	अणु0x79, no_checkपूर्ण,
	अणु0x7A, no_checkपूर्ण,
	अणु0x7B, check_texture_addr_modeपूर्ण,
	अणु0x7C, no_checkपूर्ण,
	अणु0x7D, no_checkपूर्ण,
	अणु0x7E, no_checkपूर्ण,
	अणु0x7F, no_checkपूर्ण,
	अणु0x80, no_checkपूर्ण,
	अणु0x81, no_checkपूर्ण,
	अणु0x82, no_checkपूर्ण,
	अणु0x83, no_checkपूर्ण,
	अणु0x85, no_checkपूर्ण,
	अणु0x86, no_checkपूर्ण,
	अणु0x87, no_checkपूर्ण,
	अणु0x88, no_checkपूर्ण,
	अणु0x89, no_checkपूर्ण,
	अणु0x8A, no_checkपूर्ण,
	अणु0x90, no_checkपूर्ण,
	अणु0x91, no_checkपूर्ण,
	अणु0x92, no_checkपूर्ण,
	अणु0x93, no_checkपूर्ण
पूर्ण;

अटल hz_init_t init_table3[] = अणु
	अणु0xf2, check_क्रम_header2_errपूर्ण,
	अणु0xf0, check_क्रम_header1_errपूर्ण,
	अणु0xcc, check_क्रम_dummyपूर्ण,
	अणु0x00, check_number_texunitsपूर्ण
पूर्ण;

अटल hazard_t table1[256];
अटल hazard_t table2[256];
अटल hazard_t table3[256];

अटल __अंतरभूत__ पूर्णांक
eat_words(स्थिर uपूर्णांक32_t **buf, स्थिर uपूर्णांक32_t *buf_end, अचिन्हित num_words)
अणु
	अगर ((buf_end - *buf) >= num_words) अणु
		*buf += num_words;
		वापस 0;
	पूर्ण
	DRM_ERROR("Illegal termination of DMA command buffer\n");
	वापस 1;
पूर्ण

/*
 * Partially stolen from drm_memory.h
 */

अटल __अंतरभूत__ drm_local_map_t *via_drm_lookup_agp_map(drm_via_state_t *seq,
						    अचिन्हित दीर्घ offset,
						    अचिन्हित दीर्घ size,
						    काष्ठा drm_device *dev)
अणु
	काष्ठा drm_map_list *r_list;
	drm_local_map_t *map = seq->map_cache;

	अगर (map && map->offset <= offset
	    && (offset + size) <= (map->offset + map->size)) अणु
		वापस map;
	पूर्ण

	list_क्रम_each_entry(r_list, &dev->maplist, head) अणु
		map = r_list->map;
		अगर (!map)
			जारी;
		अगर (map->offset <= offset
		    && (offset + size) <= (map->offset + map->size)
		    && !(map->flags & _DRM_RESTRICTED)
		    && (map->type == _DRM_AGP)) अणु
			seq->map_cache = map;
			वापस map;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Require that all AGP texture levels reside in the same AGP map which should
 * be mappable by the client. This is not a big restriction.
 * FIXME: To actually enक्रमce this security policy strictly, drm_rmmap
 * would have to रुको क्रम dma quiescent beक्रमe removing an AGP map.
 * The via_drm_lookup_agp_map call in reality seems to take
 * very little CPU समय.
 */

अटल __अंतरभूत__ पूर्णांक finish_current_sequence(drm_via_state_t * cur_seq)
अणु
	चयन (cur_seq->unfinished) अणु
	हाल z_address:
		DRM_DEBUG("Z Buffer start address is 0x%x\n", cur_seq->z_addr);
		अवरोध;
	हाल dest_address:
		DRM_DEBUG("Destination start address is 0x%x\n",
			  cur_seq->d_addr);
		अवरोध;
	हाल tex_address:
		अगर (cur_seq->agp_texture) अणु
			अचिन्हित start =
			    cur_seq->tex_level_lo[cur_seq->texture];
			अचिन्हित end = cur_seq->tex_level_hi[cur_seq->texture];
			अचिन्हित दीर्घ lo = ~0, hi = 0, पंचांगp;
			uपूर्णांक32_t *addr, *pitch, *height, tex;
			अचिन्हित i;
			पूर्णांक npot;

			अगर (end > 9)
				end = 9;
			अगर (start > 9)
				start = 9;

			addr =
			    &(cur_seq->t_addr[tex = cur_seq->texture][start]);
			pitch = &(cur_seq->pitch[tex][start]);
			height = &(cur_seq->height[tex][start]);
			npot = cur_seq->tex_npot[tex];
			क्रम (i = start; i <= end; ++i) अणु
				पंचांगp = *addr++;
				अगर (पंचांगp < lo)
					lo = पंचांगp;
				अगर (i == 0 && npot)
					पंचांगp += (*height++ * *pitch++);
				अन्यथा
					पंचांगp += (*height++ << *pitch++);
				अगर (पंचांगp > hi)
					hi = पंचांगp;
			पूर्ण

			अगर (!via_drm_lookup_agp_map
			    (cur_seq, lo, hi - lo, cur_seq->dev)) अणु
				DRM_ERROR
				    ("AGP texture is not in allowed map\n");
				वापस 2;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	cur_seq->unfinished = no_sequence;
	वापस 0;
पूर्ण

अटल __अंतरभूत__ पूर्णांक
investigate_hazard(uपूर्णांक32_t cmd, hazard_t hz, drm_via_state_t *cur_seq)
अणु
	रेजिस्टर uपूर्णांक32_t पंचांगp, *पंचांगp_addr;

	अगर (cur_seq->unfinished && (cur_seq->unfinished != seqs[hz])) अणु
		पूर्णांक ret;
		अगर ((ret = finish_current_sequence(cur_seq)))
			वापस ret;
	पूर्ण

	चयन (hz) अणु
	हाल check_क्रम_header2:
		अगर (cmd == HALCYON_HEADER2)
			वापस 1;
		वापस 0;
	हाल check_क्रम_header1:
		अगर ((cmd & HALCYON_HEADER1MASK) == HALCYON_HEADER1)
			वापस 1;
		वापस 0;
	हाल check_क्रम_header2_err:
		अगर (cmd == HALCYON_HEADER2)
			वापस 1;
		DRM_ERROR("Illegal DMA HALCYON_HEADER2 command\n");
		अवरोध;
	हाल check_क्रम_header1_err:
		अगर ((cmd & HALCYON_HEADER1MASK) == HALCYON_HEADER1)
			वापस 1;
		DRM_ERROR("Illegal DMA HALCYON_HEADER1 command\n");
		अवरोध;
	हाल check_क्रम_fire:
		अगर ((cmd & HALCYON_FIREMASK) == HALCYON_FIRECMD)
			वापस 1;
		DRM_ERROR("Illegal DMA HALCYON_FIRECMD command\n");
		अवरोध;
	हाल check_क्रम_dummy:
		अगर (HC_DUMMY == cmd)
			वापस 0;
		DRM_ERROR("Illegal DMA HC_DUMMY command\n");
		अवरोध;
	हाल check_क्रम_dd:
		अगर (0xdddddddd == cmd)
			वापस 0;
		DRM_ERROR("Illegal DMA 0xdddddddd command\n");
		अवरोध;
	हाल check_z_buffer_addr0:
		cur_seq->unfinished = z_address;
		cur_seq->z_addr = (cur_seq->z_addr & 0xFF000000) |
		    (cmd & 0x00FFFFFF);
		वापस 0;
	हाल check_z_buffer_addr1:
		cur_seq->unfinished = z_address;
		cur_seq->z_addr = (cur_seq->z_addr & 0x00FFFFFF) |
		    ((cmd & 0xFF) << 24);
		वापस 0;
	हाल check_z_buffer_addr_mode:
		cur_seq->unfinished = z_address;
		अगर ((cmd & 0x0000C000) == 0)
			वापस 0;
		DRM_ERROR("Attempt to place Z buffer in system memory\n");
		वापस 2;
	हाल check_destination_addr0:
		cur_seq->unfinished = dest_address;
		cur_seq->d_addr = (cur_seq->d_addr & 0xFF000000) |
		    (cmd & 0x00FFFFFF);
		वापस 0;
	हाल check_destination_addr1:
		cur_seq->unfinished = dest_address;
		cur_seq->d_addr = (cur_seq->d_addr & 0x00FFFFFF) |
		    ((cmd & 0xFF) << 24);
		वापस 0;
	हाल check_destination_addr_mode:
		cur_seq->unfinished = dest_address;
		अगर ((cmd & 0x0000C000) == 0)
			वापस 0;
		DRM_ERROR
		    ("Attempt to place 3D drawing buffer in system memory\n");
		वापस 2;
	हाल check_texture_addr0:
		cur_seq->unfinished = tex_address;
		पंचांगp = (cmd >> 24);
		पंचांगp_addr = &cur_seq->t_addr[cur_seq->texture][पंचांगp];
		*पंचांगp_addr = (*पंचांगp_addr & 0xFF000000) | (cmd & 0x00FFFFFF);
		वापस 0;
	हाल check_texture_addr1:
		cur_seq->unfinished = tex_address;
		पंचांगp = ((cmd >> 24) - 0x20);
		पंचांगp += पंचांगp << 1;
		पंचांगp_addr = &cur_seq->t_addr[cur_seq->texture][पंचांगp];
		*पंचांगp_addr = (*पंचांगp_addr & 0x00FFFFFF) | ((cmd & 0xFF) << 24);
		पंचांगp_addr++;
		*पंचांगp_addr = (*पंचांगp_addr & 0x00FFFFFF) | ((cmd & 0xFF00) << 16);
		पंचांगp_addr++;
		*पंचांगp_addr = (*पंचांगp_addr & 0x00FFFFFF) | ((cmd & 0xFF0000) << 8);
		वापस 0;
	हाल check_texture_addr2:
		cur_seq->unfinished = tex_address;
		cur_seq->tex_level_lo[पंचांगp = cur_seq->texture] = cmd & 0x3F;
		cur_seq->tex_level_hi[पंचांगp] = (cmd & 0xFC0) >> 6;
		वापस 0;
	हाल check_texture_addr3:
		cur_seq->unfinished = tex_address;
		पंचांगp = ((cmd >> 24) - HC_SubA_HTXnL0Pit);
		अगर (पंचांगp == 0 &&
		    (cmd & HC_HTXnEnPit_MASK)) अणु
			cur_seq->pitch[cur_seq->texture][पंचांगp] =
				(cmd & HC_HTXnLnPit_MASK);
			cur_seq->tex_npot[cur_seq->texture] = 1;
		पूर्ण अन्यथा अणु
			cur_seq->pitch[cur_seq->texture][पंचांगp] =
				(cmd & HC_HTXnLnPitE_MASK) >> HC_HTXnLnPitE_SHIFT;
			cur_seq->tex_npot[cur_seq->texture] = 0;
			अगर (cmd & 0x000FFFFF) अणु
				DRM_ERROR
					("Unimplemented texture level 0 pitch mode.\n");
				वापस 2;
			पूर्ण
		पूर्ण
		वापस 0;
	हाल check_texture_addr4:
		cur_seq->unfinished = tex_address;
		पंचांगp_addr = &cur_seq->t_addr[cur_seq->texture][9];
		*पंचांगp_addr = (*पंचांगp_addr & 0x00FFFFFF) | ((cmd & 0xFF) << 24);
		वापस 0;
	हाल check_texture_addr5:
	हाल check_texture_addr6:
		cur_seq->unfinished = tex_address;
		/*
		 * Texture width. We करोn't care since we have the pitch.
		 */
		वापस 0;
	हाल check_texture_addr7:
		cur_seq->unfinished = tex_address;
		पंचांगp_addr = &(cur_seq->height[cur_seq->texture][0]);
		पंचांगp_addr[5] = 1 << ((cmd & 0x00F00000) >> 20);
		पंचांगp_addr[4] = 1 << ((cmd & 0x000F0000) >> 16);
		पंचांगp_addr[3] = 1 << ((cmd & 0x0000F000) >> 12);
		पंचांगp_addr[2] = 1 << ((cmd & 0x00000F00) >> 8);
		पंचांगp_addr[1] = 1 << ((cmd & 0x000000F0) >> 4);
		पंचांगp_addr[0] = 1 << (cmd & 0x0000000F);
		वापस 0;
	हाल check_texture_addr8:
		cur_seq->unfinished = tex_address;
		पंचांगp_addr = &(cur_seq->height[cur_seq->texture][0]);
		पंचांगp_addr[9] = 1 << ((cmd & 0x0000F000) >> 12);
		पंचांगp_addr[8] = 1 << ((cmd & 0x00000F00) >> 8);
		पंचांगp_addr[7] = 1 << ((cmd & 0x000000F0) >> 4);
		पंचांगp_addr[6] = 1 << (cmd & 0x0000000F);
		वापस 0;
	हाल check_texture_addr_mode:
		cur_seq->unfinished = tex_address;
		अगर (2 == (पंचांगp = cmd & 0x00000003)) अणु
			DRM_ERROR
			    ("Attempt to fetch texture from system memory.\n");
			वापस 2;
		पूर्ण
		cur_seq->agp_texture = (पंचांगp == 3);
		cur_seq->tex_palette_size[cur_seq->texture] =
		    (cmd >> 16) & 0x000000007;
		वापस 0;
	हाल check_क्रम_vertex_count:
		cur_seq->vertex_count = cmd & 0x0000FFFF;
		वापस 0;
	हाल check_number_texunits:
		cur_seq->multitex = (cmd >> 3) & 1;
		वापस 0;
	शेष:
		DRM_ERROR("Illegal DMA data: 0x%x\n", cmd);
		वापस 2;
	पूर्ण
	वापस 2;
पूर्ण

अटल __अंतरभूत__ पूर्णांक
via_check_prim_list(uपूर्णांक32_t स्थिर **buffer, स्थिर uपूर्णांक32_t * buf_end,
		    drm_via_state_t *cur_seq)
अणु
	drm_via_निजी_t *dev_priv =
	    (drm_via_निजी_t *) cur_seq->dev->dev_निजी;
	uपूर्णांक32_t a_fire, bcmd, dw_count;
	पूर्णांक ret = 0;
	पूर्णांक have_fire;
	स्थिर uपूर्णांक32_t *buf = *buffer;

	जबतक (buf < buf_end) अणु
		have_fire = 0;
		अगर ((buf_end - buf) < 2) अणु
			DRM_ERROR
			    ("Unexpected termination of primitive list.\n");
			ret = 1;
			अवरोध;
		पूर्ण
		अगर ((*buf & HC_ACMD_MASK) != HC_ACMD_HCmdB)
			अवरोध;
		bcmd = *buf++;
		अगर ((*buf & HC_ACMD_MASK) != HC_ACMD_HCmdA) अणु
			DRM_ERROR("Expected Vertex List A command, got 0x%x\n",
				  *buf);
			ret = 1;
			अवरोध;
		पूर्ण
		a_fire =
		    *buf++ | HC_HPLEND_MASK | HC_HPMValidN_MASK |
		    HC_HE3Fire_MASK;

		/*
		 * How many dwords per vertex ?
		 */

		अगर (cur_seq->agp && ((bcmd & (0xF << 11)) == 0)) अणु
			DRM_ERROR("Illegal B command vertex data for AGP.\n");
			ret = 1;
			अवरोध;
		पूर्ण

		dw_count = 0;
		अगर (bcmd & (1 << 7))
			dw_count += (cur_seq->multitex) ? 2 : 1;
		अगर (bcmd & (1 << 8))
			dw_count += (cur_seq->multitex) ? 2 : 1;
		अगर (bcmd & (1 << 9))
			dw_count++;
		अगर (bcmd & (1 << 10))
			dw_count++;
		अगर (bcmd & (1 << 11))
			dw_count++;
		अगर (bcmd & (1 << 12))
			dw_count++;
		अगर (bcmd & (1 << 13))
			dw_count++;
		अगर (bcmd & (1 << 14))
			dw_count++;

		जबतक (buf < buf_end) अणु
			अगर (*buf == a_fire) अणु
				अगर (dev_priv->num_fire_offsets >=
				    VIA_FIRE_BUF_SIZE) अणु
					DRM_ERROR("Fire offset buffer full.\n");
					ret = 1;
					अवरोध;
				पूर्ण
				dev_priv->fire_offsets[dev_priv->
						       num_fire_offsets++] =
				    buf;
				have_fire = 1;
				buf++;
				अगर (buf < buf_end && *buf == a_fire)
					buf++;
				अवरोध;
			पूर्ण
			अगर ((*buf == HALCYON_HEADER2) ||
			    ((*buf & HALCYON_FIREMASK) == HALCYON_FIRECMD)) अणु
				DRM_ERROR("Missing Vertex Fire command, "
					  "Stray Vertex Fire command  or verifier "
					  "lost sync.\n");
				ret = 1;
				अवरोध;
			पूर्ण
			अगर ((ret = eat_words(&buf, buf_end, dw_count)))
				अवरोध;
		पूर्ण
		अगर (buf >= buf_end && !have_fire) अणु
			DRM_ERROR("Missing Vertex Fire command or verifier "
				  "lost sync.\n");
			ret = 1;
			अवरोध;
		पूर्ण
		अगर (cur_seq->agp && ((buf - cur_seq->buf_start) & 0x01)) अणु
			DRM_ERROR("AGP Primitive list end misaligned.\n");
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	*buffer = buf;
	वापस ret;
पूर्ण

अटल __अंतरभूत__ verअगरier_state_t
via_check_header2(uपूर्णांक32_t स्थिर **buffer, स्थिर uपूर्णांक32_t *buf_end,
		  drm_via_state_t *hc_state)
अणु
	uपूर्णांक32_t cmd;
	पूर्णांक hz_mode;
	hazard_t hz;
	स्थिर uपूर्णांक32_t *buf = *buffer;
	स्थिर hazard_t *hz_table;

	अगर ((buf_end - buf) < 2) अणु
		DRM_ERROR
		    ("Illegal termination of DMA HALCYON_HEADER2 sequence.\n");
		वापस state_error;
	पूर्ण
	buf++;
	cmd = (*buf++ & 0xFFFF0000) >> 16;

	चयन (cmd) अणु
	हाल HC_ParaType_CmdVdata:
		अगर (via_check_prim_list(&buf, buf_end, hc_state))
			वापस state_error;
		*buffer = buf;
		वापस state_command;
	हाल HC_ParaType_NotTex:
		hz_table = table1;
		अवरोध;
	हाल HC_ParaType_Tex:
		hc_state->texture = 0;
		hz_table = table2;
		अवरोध;
	हाल (HC_ParaType_Tex | (HC_SubType_Tex1 << 8)):
		hc_state->texture = 1;
		hz_table = table2;
		अवरोध;
	हाल (HC_ParaType_Tex | (HC_SubType_TexGeneral << 8)):
		hz_table = table3;
		अवरोध;
	हाल HC_ParaType_Auto:
		अगर (eat_words(&buf, buf_end, 2))
			वापस state_error;
		*buffer = buf;
		वापस state_command;
	हाल (HC_ParaType_Palette | (HC_SubType_Stipple << 8)):
		अगर (eat_words(&buf, buf_end, 32))
			वापस state_error;
		*buffer = buf;
		वापस state_command;
	हाल (HC_ParaType_Palette | (HC_SubType_TexPalette0 << 8)):
	हाल (HC_ParaType_Palette | (HC_SubType_TexPalette1 << 8)):
		DRM_ERROR("Texture palettes are rejected because of "
			  "lack of info how to determine their size.\n");
		वापस state_error;
	हाल (HC_ParaType_Palette | (HC_SubType_FogTable << 8)):
		DRM_ERROR("Fog factor palettes are rejected because of "
			  "lack of info how to determine their size.\n");
		वापस state_error;
	शेष:

		/*
		 * There are some unimplemented HC_ParaTypes here, that
		 * need to be implemented अगर the Mesa driver is extended.
		 */

		DRM_ERROR("Invalid or unimplemented HALCYON_HEADER2 "
			  "DMA subcommand: 0x%x. Previous dword: 0x%x\n",
			  cmd, *(buf - 2));
		*buffer = buf;
		वापस state_error;
	पूर्ण

	जबतक (buf < buf_end) अणु
		cmd = *buf++;
		अगर ((hz = hz_table[cmd >> 24])) अणु
			अगर ((hz_mode = investigate_hazard(cmd, hz, hc_state))) अणु
				अगर (hz_mode == 1) अणु
					buf--;
					अवरोध;
				पूर्ण
				वापस state_error;
			पूर्ण
		पूर्ण अन्यथा अगर (hc_state->unfinished &&
			   finish_current_sequence(hc_state)) अणु
			वापस state_error;
		पूर्ण
	पूर्ण
	अगर (hc_state->unfinished && finish_current_sequence(hc_state))
		वापस state_error;
	*buffer = buf;
	वापस state_command;
पूर्ण

अटल __अंतरभूत__ verअगरier_state_t
via_parse_header2(drm_via_निजी_t *dev_priv, uपूर्णांक32_t स्थिर **buffer,
		  स्थिर uपूर्णांक32_t *buf_end, पूर्णांक *fire_count)
अणु
	uपूर्णांक32_t cmd;
	स्थिर uपूर्णांक32_t *buf = *buffer;
	स्थिर uपूर्णांक32_t *next_fire;
	पूर्णांक burst = 0;

	next_fire = dev_priv->fire_offsets[*fire_count];
	buf++;
	cmd = (*buf & 0xFFFF0000) >> 16;
	via_ग_लिखो(dev_priv, HC_REG_TRANS_SET + HC_REG_BASE, *buf++);
	चयन (cmd) अणु
	हाल HC_ParaType_CmdVdata:
		जबतक ((buf < buf_end) &&
		       (*fire_count < dev_priv->num_fire_offsets) &&
		       (*buf & HC_ACMD_MASK) == HC_ACMD_HCmdB) अणु
			जबतक (buf <= next_fire) अणु
				via_ग_लिखो(dev_priv, HC_REG_TRANS_SPACE + HC_REG_BASE +
					  (burst & 63), *buf++);
				burst += 4;
			पूर्ण
			अगर ((buf < buf_end)
			    && ((*buf & HALCYON_FIREMASK) == HALCYON_FIRECMD))
				buf++;

			अगर (++(*fire_count) < dev_priv->num_fire_offsets)
				next_fire = dev_priv->fire_offsets[*fire_count];
		पूर्ण
		अवरोध;
	शेष:
		जबतक (buf < buf_end) अणु

			अगर (*buf == HC_HEADER2 ||
			    (*buf & HALCYON_HEADER1MASK) == HALCYON_HEADER1 ||
			    (*buf & VIA_VIDEOMASK) == VIA_VIDEO_HEADER5 ||
			    (*buf & VIA_VIDEOMASK) == VIA_VIDEO_HEADER6)
				अवरोध;

			via_ग_लिखो(dev_priv, HC_REG_TRANS_SPACE + HC_REG_BASE +
				  (burst & 63), *buf++);
			burst += 4;
		पूर्ण
	पूर्ण
	*buffer = buf;
	वापस state_command;
पूर्ण

अटल __अंतरभूत__ पूर्णांक verअगरy_mmio_address(uपूर्णांक32_t address)
अणु
	अगर ((address > 0x3FF) && (address < 0xC00)) अणु
		DRM_ERROR("Invalid VIDEO DMA command. "
			  "Attempt to access 3D- or command burst area.\n");
		वापस 1;
	पूर्ण अन्यथा अगर ((address > 0xCFF) && (address < 0x1300)) अणु
		DRM_ERROR("Invalid VIDEO DMA command. "
			  "Attempt to access PCI DMA area.\n");
		वापस 1;
	पूर्ण अन्यथा अगर (address > 0x13FF) अणु
		DRM_ERROR("Invalid VIDEO DMA command. "
			  "Attempt to access VGA registers.\n");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल __अंतरभूत__ पूर्णांक
verअगरy_video_tail(uपूर्णांक32_t स्थिर **buffer, स्थिर uपूर्णांक32_t * buf_end,
		  uपूर्णांक32_t dwords)
अणु
	स्थिर uपूर्णांक32_t *buf = *buffer;

	अगर (buf_end - buf < dwords) अणु
		DRM_ERROR("Illegal termination of video command.\n");
		वापस 1;
	पूर्ण
	जबतक (dwords--) अणु
		अगर (*buf++) अणु
			DRM_ERROR("Illegal video command tail.\n");
			वापस 1;
		पूर्ण
	पूर्ण
	*buffer = buf;
	वापस 0;
पूर्ण

अटल __अंतरभूत__ verअगरier_state_t
via_check_header1(uपूर्णांक32_t स्थिर **buffer, स्थिर uपूर्णांक32_t * buf_end)
अणु
	uपूर्णांक32_t cmd;
	स्थिर uपूर्णांक32_t *buf = *buffer;
	verअगरier_state_t ret = state_command;

	जबतक (buf < buf_end) अणु
		cmd = *buf;
		अगर ((cmd > ((0x3FF >> 2) | HALCYON_HEADER1)) &&
		    (cmd < ((0xC00 >> 2) | HALCYON_HEADER1))) अणु
			अगर ((cmd & HALCYON_HEADER1MASK) != HALCYON_HEADER1)
				अवरोध;
			DRM_ERROR("Invalid HALCYON_HEADER1 command. "
				  "Attempt to access 3D- or command burst area.\n");
			ret = state_error;
			अवरोध;
		पूर्ण अन्यथा अगर (cmd > ((0xCFF >> 2) | HALCYON_HEADER1)) अणु
			अगर ((cmd & HALCYON_HEADER1MASK) != HALCYON_HEADER1)
				अवरोध;
			DRM_ERROR("Invalid HALCYON_HEADER1 command. "
				  "Attempt to access VGA registers.\n");
			ret = state_error;
			अवरोध;
		पूर्ण अन्यथा अणु
			buf += 2;
		पूर्ण
	पूर्ण
	*buffer = buf;
	वापस ret;
पूर्ण

अटल __अंतरभूत__ verअगरier_state_t
via_parse_header1(drm_via_निजी_t *dev_priv, uपूर्णांक32_t स्थिर **buffer,
		  स्थिर uपूर्णांक32_t *buf_end)
अणु
	रेजिस्टर uपूर्णांक32_t cmd;
	स्थिर uपूर्णांक32_t *buf = *buffer;

	जबतक (buf < buf_end) अणु
		cmd = *buf;
		अगर ((cmd & HALCYON_HEADER1MASK) != HALCYON_HEADER1)
			अवरोध;
		via_ग_लिखो(dev_priv, (cmd & ~HALCYON_HEADER1MASK) << 2, *++buf);
		buf++;
	पूर्ण
	*buffer = buf;
	वापस state_command;
पूर्ण

अटल __अंतरभूत__ verअगरier_state_t
via_check_vheader5(uपूर्णांक32_t स्थिर **buffer, स्थिर uपूर्णांक32_t *buf_end)
अणु
	uपूर्णांक32_t data;
	स्थिर uपूर्णांक32_t *buf = *buffer;

	अगर (buf_end - buf < 4) अणु
		DRM_ERROR("Illegal termination of video header5 command\n");
		वापस state_error;
	पूर्ण

	data = *buf++ & ~VIA_VIDEOMASK;
	अगर (verअगरy_mmio_address(data))
		वापस state_error;

	data = *buf++;
	अगर (*buf++ != 0x00F50000) अणु
		DRM_ERROR("Illegal header5 header data\n");
		वापस state_error;
	पूर्ण
	अगर (*buf++ != 0x00000000) अणु
		DRM_ERROR("Illegal header5 header data\n");
		वापस state_error;
	पूर्ण
	अगर (eat_words(&buf, buf_end, data))
		वापस state_error;
	अगर ((data & 3) && verअगरy_video_tail(&buf, buf_end, 4 - (data & 3)))
		वापस state_error;
	*buffer = buf;
	वापस state_command;

पूर्ण

अटल __अंतरभूत__ verअगरier_state_t
via_parse_vheader5(drm_via_निजी_t *dev_priv, uपूर्णांक32_t स्थिर **buffer,
		   स्थिर uपूर्णांक32_t *buf_end)
अणु
	uपूर्णांक32_t addr, count, i;
	स्थिर uपूर्णांक32_t *buf = *buffer;

	addr = *buf++ & ~VIA_VIDEOMASK;
	i = count = *buf;
	buf += 3;
	जबतक (i--)
		via_ग_लिखो(dev_priv, addr, *buf++);
	अगर (count & 3)
		buf += 4 - (count & 3);
	*buffer = buf;
	वापस state_command;
पूर्ण

अटल __अंतरभूत__ verअगरier_state_t
via_check_vheader6(uपूर्णांक32_t स्थिर **buffer, स्थिर uपूर्णांक32_t * buf_end)
अणु
	uपूर्णांक32_t data;
	स्थिर uपूर्णांक32_t *buf = *buffer;
	uपूर्णांक32_t i;

	अगर (buf_end - buf < 4) अणु
		DRM_ERROR("Illegal termination of video header6 command\n");
		वापस state_error;
	पूर्ण
	buf++;
	data = *buf++;
	अगर (*buf++ != 0x00F60000) अणु
		DRM_ERROR("Illegal header6 header data\n");
		वापस state_error;
	पूर्ण
	अगर (*buf++ != 0x00000000) अणु
		DRM_ERROR("Illegal header6 header data\n");
		वापस state_error;
	पूर्ण
	अगर ((buf_end - buf) < (data << 1)) अणु
		DRM_ERROR("Illegal termination of video header6 command\n");
		वापस state_error;
	पूर्ण
	क्रम (i = 0; i < data; ++i) अणु
		अगर (verअगरy_mmio_address(*buf++))
			वापस state_error;
		buf++;
	पूर्ण
	data <<= 1;
	अगर ((data & 3) && verअगरy_video_tail(&buf, buf_end, 4 - (data & 3)))
		वापस state_error;
	*buffer = buf;
	वापस state_command;
पूर्ण

अटल __अंतरभूत__ verअगरier_state_t
via_parse_vheader6(drm_via_निजी_t *dev_priv, uपूर्णांक32_t स्थिर **buffer,
		   स्थिर uपूर्णांक32_t *buf_end)
अणु

	uपूर्णांक32_t addr, count, i;
	स्थिर uपूर्णांक32_t *buf = *buffer;

	i = count = *++buf;
	buf += 3;
	जबतक (i--) अणु
		addr = *buf++;
		via_ग_लिखो(dev_priv, addr, *buf++);
	पूर्ण
	count <<= 1;
	अगर (count & 3)
		buf += 4 - (count & 3);
	*buffer = buf;
	वापस state_command;
पूर्ण

पूर्णांक
via_verअगरy_command_stream(स्थिर uपूर्णांक32_t * buf, अचिन्हित पूर्णांक size,
			  काष्ठा drm_device * dev, पूर्णांक agp)
अणु

	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;
	drm_via_state_t *hc_state = &dev_priv->hc_state;
	drm_via_state_t saved_state = *hc_state;
	uपूर्णांक32_t cmd;
	स्थिर uपूर्णांक32_t *buf_end = buf + (size >> 2);
	verअगरier_state_t state = state_command;
	पूर्णांक cme_video;
	पूर्णांक supported_3d;

	cme_video = (dev_priv->chipset == VIA_PRO_GROUP_A ||
		     dev_priv->chipset == VIA_DX9_0);

	supported_3d = dev_priv->chipset != VIA_DX9_0;

	hc_state->dev = dev;
	hc_state->unfinished = no_sequence;
	hc_state->map_cache = शून्य;
	hc_state->agp = agp;
	hc_state->buf_start = buf;
	dev_priv->num_fire_offsets = 0;

	जबतक (buf < buf_end) अणु

		चयन (state) अणु
		हाल state_header2:
			state = via_check_header2(&buf, buf_end, hc_state);
			अवरोध;
		हाल state_header1:
			state = via_check_header1(&buf, buf_end);
			अवरोध;
		हाल state_vheader5:
			state = via_check_vheader5(&buf, buf_end);
			अवरोध;
		हाल state_vheader6:
			state = via_check_vheader6(&buf, buf_end);
			अवरोध;
		हाल state_command:
			cmd = *buf;
			अगर ((cmd == HALCYON_HEADER2) && supported_3d)
				state = state_header2;
			अन्यथा अगर ((cmd & HALCYON_HEADER1MASK) == HALCYON_HEADER1)
				state = state_header1;
			अन्यथा अगर (cme_video
				 && (cmd & VIA_VIDEOMASK) == VIA_VIDEO_HEADER5)
				state = state_vheader5;
			अन्यथा अगर (cme_video
				 && (cmd & VIA_VIDEOMASK) == VIA_VIDEO_HEADER6)
				state = state_vheader6;
			अन्यथा अगर ((cmd == HALCYON_HEADER2) && !supported_3d) अणु
				DRM_ERROR("Accelerated 3D is not supported on this chipset yet.\n");
				state = state_error;
			पूर्ण अन्यथा अणु
				DRM_ERROR
				    ("Invalid / Unimplemented DMA HEADER command. 0x%x\n",
				     cmd);
				state = state_error;
			पूर्ण
			अवरोध;
		हाल state_error:
		शेष:
			*hc_state = saved_state;
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (state == state_error) अणु
		*hc_state = saved_state;
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
via_parse_command_stream(काष्ठा drm_device *dev, स्थिर uपूर्णांक32_t *buf,
			 अचिन्हित पूर्णांक size)
अणु

	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;
	uपूर्णांक32_t cmd;
	स्थिर uपूर्णांक32_t *buf_end = buf + (size >> 2);
	verअगरier_state_t state = state_command;
	पूर्णांक fire_count = 0;

	जबतक (buf < buf_end) अणु

		चयन (state) अणु
		हाल state_header2:
			state =
			    via_parse_header2(dev_priv, &buf, buf_end,
					      &fire_count);
			अवरोध;
		हाल state_header1:
			state = via_parse_header1(dev_priv, &buf, buf_end);
			अवरोध;
		हाल state_vheader5:
			state = via_parse_vheader5(dev_priv, &buf, buf_end);
			अवरोध;
		हाल state_vheader6:
			state = via_parse_vheader6(dev_priv, &buf, buf_end);
			अवरोध;
		हाल state_command:
			cmd = *buf;
			अगर (cmd == HALCYON_HEADER2)
				state = state_header2;
			अन्यथा अगर ((cmd & HALCYON_HEADER1MASK) == HALCYON_HEADER1)
				state = state_header1;
			अन्यथा अगर ((cmd & VIA_VIDEOMASK) == VIA_VIDEO_HEADER5)
				state = state_vheader5;
			अन्यथा अगर ((cmd & VIA_VIDEOMASK) == VIA_VIDEO_HEADER6)
				state = state_vheader6;
			अन्यथा अणु
				DRM_ERROR
				    ("Invalid / Unimplemented DMA HEADER command. 0x%x\n",
				     cmd);
				state = state_error;
			पूर्ण
			अवरोध;
		हाल state_error:
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (state == state_error)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम
setup_hazard_table(hz_init_t init_table[], hazard_t table[], पूर्णांक size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 256; ++i)
		table[i] = क्रमbidden_command;

	क्रम (i = 0; i < size; ++i)
		table[init_table[i].code] = init_table[i].hz;
पूर्ण

व्योम via_init_command_verअगरier(व्योम)
अणु
	setup_hazard_table(init_table1, table1, ARRAY_SIZE(init_table1));
	setup_hazard_table(init_table2, table2, ARRAY_SIZE(init_table2));
	setup_hazard_table(init_table3, table3, ARRAY_SIZE(init_table3));
पूर्ण
