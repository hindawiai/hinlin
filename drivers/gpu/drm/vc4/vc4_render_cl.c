<शैली गुरु>
/*
 * Copyright तऊ 2014-2015 Broadcom
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/**
 * DOC: Render command list generation
 *
 * In the V3D hardware, render command lists are what load and store
 * tiles of a framebuffer and optionally call out to binner-generated
 * command lists to करो the 3D drawing क्रम that tile.
 *
 * In the VC4 driver, render command list generation is perक्रमmed by the
 * kernel instead of userspace.  We करो this because validating a
 * user-submitted command list is hard to get right and has high CPU overhead,
 * जबतक the number of valid configurations क्रम render command lists is
 * actually fairly low.
 */

#समावेश "uapi/drm/vc4_drm.h"
#समावेश "vc4_drv.h"
#समावेश "vc4_packet.h"

काष्ठा vc4_rcl_setup अणु
	काष्ठा drm_gem_cma_object *color_पढ़ो;
	काष्ठा drm_gem_cma_object *color_ग_लिखो;
	काष्ठा drm_gem_cma_object *zs_पढ़ो;
	काष्ठा drm_gem_cma_object *zs_ग_लिखो;
	काष्ठा drm_gem_cma_object *msaa_color_ग_लिखो;
	काष्ठा drm_gem_cma_object *msaa_zs_ग_लिखो;

	काष्ठा drm_gem_cma_object *rcl;
	u32 next_offset;

	u32 next_ग_लिखो_bo_index;
पूर्ण;

अटल अंतरभूत व्योम rcl_u8(काष्ठा vc4_rcl_setup *setup, u8 val)
अणु
	*(u8 *)(setup->rcl->vaddr + setup->next_offset) = val;
	setup->next_offset += 1;
पूर्ण

अटल अंतरभूत व्योम rcl_u16(काष्ठा vc4_rcl_setup *setup, u16 val)
अणु
	*(u16 *)(setup->rcl->vaddr + setup->next_offset) = val;
	setup->next_offset += 2;
पूर्ण

अटल अंतरभूत व्योम rcl_u32(काष्ठा vc4_rcl_setup *setup, u32 val)
अणु
	*(u32 *)(setup->rcl->vaddr + setup->next_offset) = val;
	setup->next_offset += 4;
पूर्ण

/*
 * Emits a no-op STORE_TILE_BUFFER_GENERAL.
 *
 * If we emit a PACKET_TILE_COORDINATES, it must be followed by a store of
 * some sort beक्रमe another load is triggered.
 */
अटल व्योम vc4_store_beक्रमe_load(काष्ठा vc4_rcl_setup *setup)
अणु
	rcl_u8(setup, VC4_PACKET_STORE_TILE_BUFFER_GENERAL);
	rcl_u16(setup,
		VC4_SET_FIELD(VC4_LOADSTORE_TILE_BUFFER_NONE,
			      VC4_LOADSTORE_TILE_BUFFER_BUFFER) |
		VC4_STORE_TILE_BUFFER_DISABLE_COLOR_CLEAR |
		VC4_STORE_TILE_BUFFER_DISABLE_ZS_CLEAR |
		VC4_STORE_TILE_BUFFER_DISABLE_VG_MASK_CLEAR);
	rcl_u32(setup, 0); /* no address, since we're in None mode */
पूर्ण

/*
 * Calculates the physical address of the start of a tile in a RCL surface.
 *
 * Unlike the other load/store packets,
 * VC4_PACKET_LOAD/STORE_FULL_RES_TILE_BUFFER करोn't look at the tile
 * coordinates packet, and instead just store to the address given.
 */
अटल uपूर्णांक32_t vc4_full_res_offset(काष्ठा vc4_exec_info *exec,
				    काष्ठा drm_gem_cma_object *bo,
				    काष्ठा drm_vc4_submit_rcl_surface *surf,
				    uपूर्णांक8_t x, uपूर्णांक8_t y)
अणु
	वापस bo->paddr + surf->offset + VC4_TILE_BUFFER_SIZE *
		(DIV_ROUND_UP(exec->args->width, 32) * y + x);
पूर्ण

/*
 * Emits a PACKET_TILE_COORDINATES अगर one isn't alपढ़ोy pending.
 *
 * The tile coordinates packet triggers a pending load अगर there is one, are
 * used क्रम clipping during rendering, and determine where loads/stores happen
 * relative to their base address.
 */
अटल व्योम vc4_tile_coordinates(काष्ठा vc4_rcl_setup *setup,
				 uपूर्णांक32_t x, uपूर्णांक32_t y)
अणु
	rcl_u8(setup, VC4_PACKET_TILE_COORDINATES);
	rcl_u8(setup, x);
	rcl_u8(setup, y);
पूर्ण

अटल व्योम emit_tile(काष्ठा vc4_exec_info *exec,
		      काष्ठा vc4_rcl_setup *setup,
		      uपूर्णांक8_t x, uपूर्णांक8_t y, bool first, bool last)
अणु
	काष्ठा drm_vc4_submit_cl *args = exec->args;
	bool has_bin = args->bin_cl_size != 0;

	/* Note that the load करोesn't actually occur until the
	 * tile coords packet is processed, and only one load
	 * may be outstanding at a समय.
	 */
	अगर (setup->color_पढ़ो) अणु
		अगर (args->color_पढ़ो.flags &
		    VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES) अणु
			rcl_u8(setup, VC4_PACKET_LOAD_FULL_RES_TILE_BUFFER);
			rcl_u32(setup,
				vc4_full_res_offset(exec, setup->color_पढ़ो,
						    &args->color_पढ़ो, x, y) |
				VC4_LOADSTORE_FULL_RES_DISABLE_ZS);
		पूर्ण अन्यथा अणु
			rcl_u8(setup, VC4_PACKET_LOAD_TILE_BUFFER_GENERAL);
			rcl_u16(setup, args->color_पढ़ो.bits);
			rcl_u32(setup, setup->color_पढ़ो->paddr +
				args->color_पढ़ो.offset);
		पूर्ण
	पूर्ण

	अगर (setup->zs_पढ़ो) अणु
		अगर (setup->color_पढ़ो) अणु
			/* Exec previous load. */
			vc4_tile_coordinates(setup, x, y);
			vc4_store_beक्रमe_load(setup);
		पूर्ण

		अगर (args->zs_पढ़ो.flags &
		    VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES) अणु
			rcl_u8(setup, VC4_PACKET_LOAD_FULL_RES_TILE_BUFFER);
			rcl_u32(setup,
				vc4_full_res_offset(exec, setup->zs_पढ़ो,
						    &args->zs_पढ़ो, x, y) |
				VC4_LOADSTORE_FULL_RES_DISABLE_COLOR);
		पूर्ण अन्यथा अणु
			rcl_u8(setup, VC4_PACKET_LOAD_TILE_BUFFER_GENERAL);
			rcl_u16(setup, args->zs_पढ़ो.bits);
			rcl_u32(setup, setup->zs_पढ़ो->paddr +
				args->zs_पढ़ो.offset);
		पूर्ण
	पूर्ण

	/* Clipping depends on tile coordinates having been
	 * emitted, so we always need one here.
	 */
	vc4_tile_coordinates(setup, x, y);

	/* Wait क्रम the binner beक्रमe jumping to the first
	 * tile's lists.
	 */
	अगर (first && has_bin)
		rcl_u8(setup, VC4_PACKET_WAIT_ON_SEMAPHORE);

	अगर (has_bin) अणु
		rcl_u8(setup, VC4_PACKET_BRANCH_TO_SUB_LIST);
		rcl_u32(setup, (exec->tile_alloc_offset +
				(y * exec->bin_tiles_x + x) * 32));
	पूर्ण

	अगर (setup->msaa_color_ग_लिखो) अणु
		bool last_tile_ग_लिखो = (!setup->msaa_zs_ग_लिखो &&
					!setup->zs_ग_लिखो &&
					!setup->color_ग_लिखो);
		uपूर्णांक32_t bits = VC4_LOADSTORE_FULL_RES_DISABLE_ZS;

		अगर (!last_tile_ग_लिखो)
			bits |= VC4_LOADSTORE_FULL_RES_DISABLE_CLEAR_ALL;
		अन्यथा अगर (last)
			bits |= VC4_LOADSTORE_FULL_RES_खातापूर्ण;
		rcl_u8(setup, VC4_PACKET_STORE_FULL_RES_TILE_BUFFER);
		rcl_u32(setup,
			vc4_full_res_offset(exec, setup->msaa_color_ग_लिखो,
					    &args->msaa_color_ग_लिखो, x, y) |
			bits);
	पूर्ण

	अगर (setup->msaa_zs_ग_लिखो) अणु
		bool last_tile_ग_लिखो = (!setup->zs_ग_लिखो &&
					!setup->color_ग_लिखो);
		uपूर्णांक32_t bits = VC4_LOADSTORE_FULL_RES_DISABLE_COLOR;

		अगर (setup->msaa_color_ग_लिखो)
			vc4_tile_coordinates(setup, x, y);
		अगर (!last_tile_ग_लिखो)
			bits |= VC4_LOADSTORE_FULL_RES_DISABLE_CLEAR_ALL;
		अन्यथा अगर (last)
			bits |= VC4_LOADSTORE_FULL_RES_खातापूर्ण;
		rcl_u8(setup, VC4_PACKET_STORE_FULL_RES_TILE_BUFFER);
		rcl_u32(setup,
			vc4_full_res_offset(exec, setup->msaa_zs_ग_लिखो,
					    &args->msaa_zs_ग_लिखो, x, y) |
			bits);
	पूर्ण

	अगर (setup->zs_ग_लिखो) अणु
		bool last_tile_ग_लिखो = !setup->color_ग_लिखो;

		अगर (setup->msaa_color_ग_लिखो || setup->msaa_zs_ग_लिखो)
			vc4_tile_coordinates(setup, x, y);

		rcl_u8(setup, VC4_PACKET_STORE_TILE_BUFFER_GENERAL);
		rcl_u16(setup, args->zs_ग_लिखो.bits |
			(last_tile_ग_लिखो ?
			 0 : VC4_STORE_TILE_BUFFER_DISABLE_COLOR_CLEAR));
		rcl_u32(setup,
			(setup->zs_ग_लिखो->paddr + args->zs_ग_लिखो.offset) |
			((last && last_tile_ग_लिखो) ?
			 VC4_LOADSTORE_TILE_BUFFER_खातापूर्ण : 0));
	पूर्ण

	अगर (setup->color_ग_लिखो) अणु
		अगर (setup->msaa_color_ग_लिखो || setup->msaa_zs_ग_लिखो ||
		    setup->zs_ग_लिखो) अणु
			vc4_tile_coordinates(setup, x, y);
		पूर्ण

		अगर (last)
			rcl_u8(setup, VC4_PACKET_STORE_MS_TILE_BUFFER_AND_खातापूर्ण);
		अन्यथा
			rcl_u8(setup, VC4_PACKET_STORE_MS_TILE_BUFFER);
	पूर्ण
पूर्ण

अटल पूर्णांक vc4_create_rcl_bo(काष्ठा drm_device *dev, काष्ठा vc4_exec_info *exec,
			     काष्ठा vc4_rcl_setup *setup)
अणु
	काष्ठा drm_vc4_submit_cl *args = exec->args;
	bool has_bin = args->bin_cl_size != 0;
	uपूर्णांक8_t min_x_tile = args->min_x_tile;
	uपूर्णांक8_t min_y_tile = args->min_y_tile;
	uपूर्णांक8_t max_x_tile = args->max_x_tile;
	uपूर्णांक8_t max_y_tile = args->max_y_tile;
	uपूर्णांक8_t xtiles = max_x_tile - min_x_tile + 1;
	uपूर्णांक8_t ytiles = max_y_tile - min_y_tile + 1;
	uपूर्णांक8_t xi, yi;
	uपूर्णांक32_t size, loop_body_size;
	bool positive_x = true;
	bool positive_y = true;

	अगर (args->flags & VC4_SUBMIT_CL_FIXED_RCL_ORDER) अणु
		अगर (!(args->flags & VC4_SUBMIT_CL_RCL_ORDER_INCREASING_X))
			positive_x = false;
		अगर (!(args->flags & VC4_SUBMIT_CL_RCL_ORDER_INCREASING_Y))
			positive_y = false;
	पूर्ण

	size = VC4_PACKET_TILE_RENDERING_MODE_CONFIG_SIZE;
	loop_body_size = VC4_PACKET_TILE_COORDINATES_SIZE;

	अगर (args->flags & VC4_SUBMIT_CL_USE_CLEAR_COLOR) अणु
		size += VC4_PACKET_CLEAR_COLORS_SIZE +
			VC4_PACKET_TILE_COORDINATES_SIZE +
			VC4_PACKET_STORE_TILE_BUFFER_GENERAL_SIZE;
	पूर्ण

	अगर (setup->color_पढ़ो) अणु
		अगर (args->color_पढ़ो.flags &
		    VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES) अणु
			loop_body_size += VC4_PACKET_LOAD_FULL_RES_TILE_BUFFER_SIZE;
		पूर्ण अन्यथा अणु
			loop_body_size += VC4_PACKET_LOAD_TILE_BUFFER_GENERAL_SIZE;
		पूर्ण
	पूर्ण
	अगर (setup->zs_पढ़ो) अणु
		अगर (setup->color_पढ़ो) अणु
			loop_body_size += VC4_PACKET_TILE_COORDINATES_SIZE;
			loop_body_size += VC4_PACKET_STORE_TILE_BUFFER_GENERAL_SIZE;
		पूर्ण

		अगर (args->zs_पढ़ो.flags &
		    VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES) अणु
			loop_body_size += VC4_PACKET_LOAD_FULL_RES_TILE_BUFFER_SIZE;
		पूर्ण अन्यथा अणु
			loop_body_size += VC4_PACKET_LOAD_TILE_BUFFER_GENERAL_SIZE;
		पूर्ण
	पूर्ण

	अगर (has_bin) अणु
		size += VC4_PACKET_WAIT_ON_SEMAPHORE_SIZE;
		loop_body_size += VC4_PACKET_BRANCH_TO_SUB_LIST_SIZE;
	पूर्ण

	अगर (setup->msaa_color_ग_लिखो)
		loop_body_size += VC4_PACKET_STORE_FULL_RES_TILE_BUFFER_SIZE;
	अगर (setup->msaa_zs_ग_लिखो)
		loop_body_size += VC4_PACKET_STORE_FULL_RES_TILE_BUFFER_SIZE;

	अगर (setup->zs_ग_लिखो)
		loop_body_size += VC4_PACKET_STORE_TILE_BUFFER_GENERAL_SIZE;
	अगर (setup->color_ग_लिखो)
		loop_body_size += VC4_PACKET_STORE_MS_TILE_BUFFER_SIZE;

	/* We need a VC4_PACKET_TILE_COORDINATES in between each store. */
	loop_body_size += VC4_PACKET_TILE_COORDINATES_SIZE *
		((setup->msaa_color_ग_लिखो != शून्य) +
		 (setup->msaa_zs_ग_लिखो != शून्य) +
		 (setup->color_ग_लिखो != शून्य) +
		 (setup->zs_ग_लिखो != शून्य) - 1);

	size += xtiles * ytiles * loop_body_size;

	setup->rcl = &vc4_bo_create(dev, size, true, VC4_BO_TYPE_RCL)->base;
	अगर (IS_ERR(setup->rcl))
		वापस PTR_ERR(setup->rcl);
	list_add_tail(&to_vc4_bo(&setup->rcl->base)->unref_head,
		      &exec->unref_list);

	/* The tile buffer माला_लो cleared when the previous tile is stored.  If
	 * the clear values changed between frames, then the tile buffer has
	 * stale clear values in it, so we have to करो a store in None mode (no
	 * ग_लिखोs) so that we trigger the tile buffer clear.
	 */
	अगर (args->flags & VC4_SUBMIT_CL_USE_CLEAR_COLOR) अणु
		rcl_u8(setup, VC4_PACKET_CLEAR_COLORS);
		rcl_u32(setup, args->clear_color[0]);
		rcl_u32(setup, args->clear_color[1]);
		rcl_u32(setup, args->clear_z);
		rcl_u8(setup, args->clear_s);

		vc4_tile_coordinates(setup, 0, 0);

		rcl_u8(setup, VC4_PACKET_STORE_TILE_BUFFER_GENERAL);
		rcl_u16(setup, VC4_LOADSTORE_TILE_BUFFER_NONE);
		rcl_u32(setup, 0); /* no address, since we're in None mode */
	पूर्ण

	rcl_u8(setup, VC4_PACKET_TILE_RENDERING_MODE_CONFIG);
	rcl_u32(setup,
		(setup->color_ग_लिखो ? (setup->color_ग_लिखो->paddr +
				       args->color_ग_लिखो.offset) :
		 0));
	rcl_u16(setup, args->width);
	rcl_u16(setup, args->height);
	rcl_u16(setup, args->color_ग_लिखो.bits);

	क्रम (yi = 0; yi < ytiles; yi++) अणु
		पूर्णांक y = positive_y ? min_y_tile + yi : max_y_tile - yi;
		क्रम (xi = 0; xi < xtiles; xi++) अणु
			पूर्णांक x = positive_x ? min_x_tile + xi : max_x_tile - xi;
			bool first = (xi == 0 && yi == 0);
			bool last = (xi == xtiles - 1 && yi == ytiles - 1);

			emit_tile(exec, setup, x, y, first, last);
		पूर्ण
	पूर्ण

	BUG_ON(setup->next_offset != size);
	exec->ct1ca = setup->rcl->paddr;
	exec->ct1ea = setup->rcl->paddr + setup->next_offset;

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_full_res_bounds_check(काष्ठा vc4_exec_info *exec,
				     काष्ठा drm_gem_cma_object *obj,
				     काष्ठा drm_vc4_submit_rcl_surface *surf)
अणु
	काष्ठा drm_vc4_submit_cl *args = exec->args;
	u32 render_tiles_stride = DIV_ROUND_UP(exec->args->width, 32);

	अगर (surf->offset > obj->base.size) अणु
		DRM_DEBUG("surface offset %d > BO size %zd\n",
			  surf->offset, obj->base.size);
		वापस -EINVAL;
	पूर्ण

	अगर ((obj->base.size - surf->offset) / VC4_TILE_BUFFER_SIZE <
	    render_tiles_stride * args->max_y_tile + args->max_x_tile) अणु
		DRM_DEBUG("MSAA tile %d, %d out of bounds "
			  "(bo size %zd, offset %d).\n",
			  args->max_x_tile, args->max_y_tile,
			  obj->base.size,
			  surf->offset);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_rcl_msaa_surface_setup(काष्ठा vc4_exec_info *exec,
				      काष्ठा drm_gem_cma_object **obj,
				      काष्ठा drm_vc4_submit_rcl_surface *surf)
अणु
	अगर (surf->flags != 0 || surf->bits != 0) अणु
		DRM_DEBUG("MSAA surface had nonzero flags/bits\n");
		वापस -EINVAL;
	पूर्ण

	अगर (surf->hindex == ~0)
		वापस 0;

	*obj = vc4_use_bo(exec, surf->hindex);
	अगर (!*obj)
		वापस -EINVAL;

	exec->rcl_ग_लिखो_bo[exec->rcl_ग_लिखो_bo_count++] = *obj;

	अगर (surf->offset & 0xf) अणु
		DRM_DEBUG("MSAA write must be 16b aligned.\n");
		वापस -EINVAL;
	पूर्ण

	वापस vc4_full_res_bounds_check(exec, *obj, surf);
पूर्ण

अटल पूर्णांक vc4_rcl_surface_setup(काष्ठा vc4_exec_info *exec,
				 काष्ठा drm_gem_cma_object **obj,
				 काष्ठा drm_vc4_submit_rcl_surface *surf,
				 bool is_ग_लिखो)
अणु
	uपूर्णांक8_t tiling = VC4_GET_FIELD(surf->bits,
				       VC4_LOADSTORE_TILE_BUFFER_TILING);
	uपूर्णांक8_t buffer = VC4_GET_FIELD(surf->bits,
				       VC4_LOADSTORE_TILE_BUFFER_BUFFER);
	uपूर्णांक8_t क्रमmat = VC4_GET_FIELD(surf->bits,
				       VC4_LOADSTORE_TILE_BUFFER_FORMAT);
	पूर्णांक cpp;
	पूर्णांक ret;

	अगर (surf->flags & ~VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES) अणु
		DRM_DEBUG("Extra flags set\n");
		वापस -EINVAL;
	पूर्ण

	अगर (surf->hindex == ~0)
		वापस 0;

	*obj = vc4_use_bo(exec, surf->hindex);
	अगर (!*obj)
		वापस -EINVAL;

	अगर (is_ग_लिखो)
		exec->rcl_ग_लिखो_bo[exec->rcl_ग_लिखो_bo_count++] = *obj;

	अगर (surf->flags & VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES) अणु
		अगर (surf == &exec->args->zs_ग_लिखो) अणु
			DRM_DEBUG("general zs write may not be a full-res.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (surf->bits != 0) अणु
			DRM_DEBUG("load/store general bits set with "
				  "full res load/store.\n");
			वापस -EINVAL;
		पूर्ण

		ret = vc4_full_res_bounds_check(exec, *obj, surf);
		अगर (ret)
			वापस ret;

		वापस 0;
	पूर्ण

	अगर (surf->bits & ~(VC4_LOADSTORE_TILE_BUFFER_TILING_MASK |
			   VC4_LOADSTORE_TILE_BUFFER_BUFFER_MASK |
			   VC4_LOADSTORE_TILE_BUFFER_FORMAT_MASK)) अणु
		DRM_DEBUG("Unknown bits in load/store: 0x%04x\n",
			  surf->bits);
		वापस -EINVAL;
	पूर्ण

	अगर (tiling > VC4_TILING_FORMAT_LT) अणु
		DRM_DEBUG("Bad tiling format\n");
		वापस -EINVAL;
	पूर्ण

	अगर (buffer == VC4_LOADSTORE_TILE_BUFFER_ZS) अणु
		अगर (क्रमmat != 0) अणु
			DRM_DEBUG("No color format should be set for ZS\n");
			वापस -EINVAL;
		पूर्ण
		cpp = 4;
	पूर्ण अन्यथा अगर (buffer == VC4_LOADSTORE_TILE_BUFFER_COLOR) अणु
		चयन (क्रमmat) अणु
		हाल VC4_LOADSTORE_TILE_BUFFER_BGR565:
		हाल VC4_LOADSTORE_TILE_BUFFER_BGR565_DITHER:
			cpp = 2;
			अवरोध;
		हाल VC4_LOADSTORE_TILE_BUFFER_RGBA8888:
			cpp = 4;
			अवरोध;
		शेष:
			DRM_DEBUG("Bad tile buffer format\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_DEBUG("Bad load/store buffer %d.\n", buffer);
		वापस -EINVAL;
	पूर्ण

	अगर (surf->offset & 0xf) अणु
		DRM_DEBUG("load/store buffer must be 16b aligned.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!vc4_check_tex_size(exec, *obj, surf->offset, tiling,
				exec->args->width, exec->args->height, cpp)) अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
vc4_rcl_render_config_surface_setup(काष्ठा vc4_exec_info *exec,
				    काष्ठा vc4_rcl_setup *setup,
				    काष्ठा drm_gem_cma_object **obj,
				    काष्ठा drm_vc4_submit_rcl_surface *surf)
अणु
	uपूर्णांक8_t tiling = VC4_GET_FIELD(surf->bits,
				       VC4_RENDER_CONFIG_MEMORY_FORMAT);
	uपूर्णांक8_t क्रमmat = VC4_GET_FIELD(surf->bits,
				       VC4_RENDER_CONFIG_FORMAT);
	पूर्णांक cpp;

	अगर (surf->flags != 0) अणु
		DRM_DEBUG("No flags supported on render config.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (surf->bits & ~(VC4_RENDER_CONFIG_MEMORY_FORMAT_MASK |
			   VC4_RENDER_CONFIG_FORMAT_MASK |
			   VC4_RENDER_CONFIG_MS_MODE_4X |
			   VC4_RENDER_CONFIG_DECIMATE_MODE_4X)) अणु
		DRM_DEBUG("Unknown bits in render config: 0x%04x\n",
			  surf->bits);
		वापस -EINVAL;
	पूर्ण

	अगर (surf->hindex == ~0)
		वापस 0;

	*obj = vc4_use_bo(exec, surf->hindex);
	अगर (!*obj)
		वापस -EINVAL;

	exec->rcl_ग_लिखो_bo[exec->rcl_ग_लिखो_bo_count++] = *obj;

	अगर (tiling > VC4_TILING_FORMAT_LT) अणु
		DRM_DEBUG("Bad tiling format\n");
		वापस -EINVAL;
	पूर्ण

	चयन (क्रमmat) अणु
	हाल VC4_RENDER_CONFIG_FORMAT_BGR565_DITHERED:
	हाल VC4_RENDER_CONFIG_FORMAT_BGR565:
		cpp = 2;
		अवरोध;
	हाल VC4_RENDER_CONFIG_FORMAT_RGBA8888:
		cpp = 4;
		अवरोध;
	शेष:
		DRM_DEBUG("Bad tile buffer format\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!vc4_check_tex_size(exec, *obj, surf->offset, tiling,
				exec->args->width, exec->args->height, cpp)) अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vc4_get_rcl(काष्ठा drm_device *dev, काष्ठा vc4_exec_info *exec)
अणु
	काष्ठा vc4_rcl_setup setup = अणु0पूर्ण;
	काष्ठा drm_vc4_submit_cl *args = exec->args;
	bool has_bin = args->bin_cl_size != 0;
	पूर्णांक ret;

	अगर (args->min_x_tile > args->max_x_tile ||
	    args->min_y_tile > args->max_y_tile) अणु
		DRM_DEBUG("Bad render tile set (%d,%d)-(%d,%d)\n",
			  args->min_x_tile, args->min_y_tile,
			  args->max_x_tile, args->max_y_tile);
		वापस -EINVAL;
	पूर्ण

	अगर (has_bin &&
	    (args->max_x_tile > exec->bin_tiles_x ||
	     args->max_y_tile > exec->bin_tiles_y)) अणु
		DRM_DEBUG("Render tiles (%d,%d) outside of bin config "
			  "(%d,%d)\n",
			  args->max_x_tile, args->max_y_tile,
			  exec->bin_tiles_x, exec->bin_tiles_y);
		वापस -EINVAL;
	पूर्ण

	ret = vc4_rcl_render_config_surface_setup(exec, &setup,
						  &setup.color_ग_लिखो,
						  &args->color_ग_लिखो);
	अगर (ret)
		वापस ret;

	ret = vc4_rcl_surface_setup(exec, &setup.color_पढ़ो, &args->color_पढ़ो,
				    false);
	अगर (ret)
		वापस ret;

	ret = vc4_rcl_surface_setup(exec, &setup.zs_पढ़ो, &args->zs_पढ़ो,
				    false);
	अगर (ret)
		वापस ret;

	ret = vc4_rcl_surface_setup(exec, &setup.zs_ग_लिखो, &args->zs_ग_लिखो,
				    true);
	अगर (ret)
		वापस ret;

	ret = vc4_rcl_msaa_surface_setup(exec, &setup.msaa_color_ग_लिखो,
					 &args->msaa_color_ग_लिखो);
	अगर (ret)
		वापस ret;

	ret = vc4_rcl_msaa_surface_setup(exec, &setup.msaa_zs_ग_लिखो,
					 &args->msaa_zs_ग_लिखो);
	अगर (ret)
		वापस ret;

	/* We shouldn't even have the job submitted to us if there's no
	 * surface to ग_लिखो out.
	 */
	अगर (!setup.color_ग_लिखो && !setup.zs_ग_लिखो &&
	    !setup.msaa_color_ग_लिखो && !setup.msaa_zs_ग_लिखो) अणु
		DRM_DEBUG("RCL requires color or Z/S write\n");
		वापस -EINVAL;
	पूर्ण

	वापस vc4_create_rcl_bo(dev, exec, &setup);
पूर्ण
