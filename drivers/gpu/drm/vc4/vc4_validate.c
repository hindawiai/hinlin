<शैली गुरु>
/*
 * Copyright तऊ 2014 Broadcom
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
 * DOC: Command list validator क्रम VC4.
 *
 * Since the VC4 has no IOMMU between it and प्रणाली memory, a user
 * with access to execute command lists could escalate privilege by
 * overwriting प्रणाली memory (drawing to it as a framebuffer) or
 * पढ़ोing प्रणाली memory it shouldn't (पढ़ोing it as a vertex buffer
 * or index buffer)
 *
 * We validate binner command lists to ensure that all accesses are
 * within the bounds of the GEM objects referenced by the submitted
 * job.  It explicitly whitelists packets, and looks at the offsets in
 * any address fields to make sure they're contained within the BOs
 * they reference.
 *
 * Note that because CL validation is alपढ़ोy पढ़ोing the
 * user-submitted CL and writing the validated copy out to the memory
 * that the GPU will actually पढ़ो, this is also where GEM relocation
 * processing (turning BO references पूर्णांकo actual addresses क्रम the GPU
 * to use) happens.
 */

#समावेश "uapi/drm/vc4_drm.h"
#समावेश "vc4_drv.h"
#समावेश "vc4_packet.h"

#घोषणा VALIDATE_ARGS \
	काष्ठा vc4_exec_info *exec,			\
	व्योम *validated,				\
	व्योम *untrusted

/** Return the width in pixels of a 64-byte microtile. */
अटल uपूर्णांक32_t
utile_width(पूर्णांक cpp)
अणु
	चयन (cpp) अणु
	हाल 1:
	हाल 2:
		वापस 8;
	हाल 4:
		वापस 4;
	हाल 8:
		वापस 2;
	शेष:
		DRM_ERROR("unknown cpp: %d\n", cpp);
		वापस 1;
	पूर्ण
पूर्ण

/** Return the height in pixels of a 64-byte microtile. */
अटल uपूर्णांक32_t
utile_height(पूर्णांक cpp)
अणु
	चयन (cpp) अणु
	हाल 1:
		वापस 8;
	हाल 2:
	हाल 4:
	हाल 8:
		वापस 4;
	शेष:
		DRM_ERROR("unknown cpp: %d\n", cpp);
		वापस 1;
	पूर्ण
पूर्ण

/**
 * size_is_lt() - Returns whether a miplevel of the given size will
 * use the lineartile (LT) tiling layout rather than the normal T
 * tiling layout.
 * @width: Width in pixels of the miplevel
 * @height: Height in pixels of the miplevel
 * @cpp: Bytes per pixel of the pixel क्रमmat
 */
अटल bool
size_is_lt(uपूर्णांक32_t width, uपूर्णांक32_t height, पूर्णांक cpp)
अणु
	वापस (width <= 4 * utile_width(cpp) ||
		height <= 4 * utile_height(cpp));
पूर्ण

काष्ठा drm_gem_cma_object *
vc4_use_bo(काष्ठा vc4_exec_info *exec, uपूर्णांक32_t hindex)
अणु
	काष्ठा drm_gem_cma_object *obj;
	काष्ठा vc4_bo *bo;

	अगर (hindex >= exec->bo_count) अणु
		DRM_DEBUG("BO index %d greater than BO count %d\n",
			  hindex, exec->bo_count);
		वापस शून्य;
	पूर्ण
	obj = exec->bo[hindex];
	bo = to_vc4_bo(&obj->base);

	अगर (bo->validated_shader) अणु
		DRM_DEBUG("Trying to use shader BO as something other than "
			  "a shader\n");
		वापस शून्य;
	पूर्ण

	वापस obj;
पूर्ण

अटल काष्ठा drm_gem_cma_object *
vc4_use_handle(काष्ठा vc4_exec_info *exec, uपूर्णांक32_t gem_handles_packet_index)
अणु
	वापस vc4_use_bo(exec, exec->bo_index[gem_handles_packet_index]);
पूर्ण

अटल bool
validate_bin_pos(काष्ठा vc4_exec_info *exec, व्योम *untrusted, uपूर्णांक32_t pos)
अणु
	/* Note that the untrusted poपूर्णांकer passed to these functions is
	 * incremented past the packet byte.
	 */
	वापस (untrusted - 1 == exec->bin_u + pos);
पूर्ण

अटल uपूर्णांक32_t
gl_shader_rec_size(uपूर्णांक32_t poपूर्णांकer_bits)
अणु
	uपूर्णांक32_t attribute_count = poपूर्णांकer_bits & 7;
	bool extended = poपूर्णांकer_bits & 8;

	अगर (attribute_count == 0)
		attribute_count = 8;

	अगर (extended)
		वापस 100 + attribute_count * 4;
	अन्यथा
		वापस 36 + attribute_count * 8;
पूर्ण

bool
vc4_check_tex_size(काष्ठा vc4_exec_info *exec, काष्ठा drm_gem_cma_object *fbo,
		   uपूर्णांक32_t offset, uपूर्णांक8_t tiling_क्रमmat,
		   uपूर्णांक32_t width, uपूर्णांक32_t height, uपूर्णांक8_t cpp)
अणु
	uपूर्णांक32_t aligned_width, aligned_height, stride, size;
	uपूर्णांक32_t utile_w = utile_width(cpp);
	uपूर्णांक32_t utile_h = utile_height(cpp);

	/* The shaded vertex क्रमmat stores चिन्हित 12.4 fixed poपूर्णांक
	 * (-2048,2047) offsets from the viewport center, so we should
	 * never have a render target larger than 4096.  The texture
	 * unit can only sample from 2048x2048, so it's even more
	 * restricted.  This lets us aव्योम worrying about overflow in
	 * our math.
	 */
	अगर (width > 4096 || height > 4096) अणु
		DRM_DEBUG("Surface dimensions (%d,%d) too large",
			  width, height);
		वापस false;
	पूर्ण

	चयन (tiling_क्रमmat) अणु
	हाल VC4_TILING_FORMAT_LINEAR:
		aligned_width = round_up(width, utile_w);
		aligned_height = height;
		अवरोध;
	हाल VC4_TILING_FORMAT_T:
		aligned_width = round_up(width, utile_w * 8);
		aligned_height = round_up(height, utile_h * 8);
		अवरोध;
	हाल VC4_TILING_FORMAT_LT:
		aligned_width = round_up(width, utile_w);
		aligned_height = round_up(height, utile_h);
		अवरोध;
	शेष:
		DRM_DEBUG("buffer tiling %d unsupported\n", tiling_क्रमmat);
		वापस false;
	पूर्ण

	stride = aligned_width * cpp;
	size = stride * aligned_height;

	अगर (size + offset < size ||
	    size + offset > fbo->base.size) अणु
		DRM_DEBUG("Overflow in %dx%d (%dx%d) fbo size (%d + %d > %zd)\n",
			  width, height,
			  aligned_width, aligned_height,
			  size, offset, fbo->base.size);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
validate_flush(VALIDATE_ARGS)
अणु
	अगर (!validate_bin_pos(exec, untrusted, exec->args->bin_cl_size - 1)) अणु
		DRM_DEBUG("Bin CL must end with VC4_PACKET_FLUSH\n");
		वापस -EINVAL;
	पूर्ण
	exec->found_flush = true;

	वापस 0;
पूर्ण

अटल पूर्णांक
validate_start_tile_binning(VALIDATE_ARGS)
अणु
	अगर (exec->found_start_tile_binning_packet) अणु
		DRM_DEBUG("Duplicate VC4_PACKET_START_TILE_BINNING\n");
		वापस -EINVAL;
	पूर्ण
	exec->found_start_tile_binning_packet = true;

	अगर (!exec->found_tile_binning_mode_config_packet) अणु
		DRM_DEBUG("missing VC4_PACKET_TILE_BINNING_MODE_CONFIG\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
validate_increment_semaphore(VALIDATE_ARGS)
अणु
	अगर (!validate_bin_pos(exec, untrusted, exec->args->bin_cl_size - 2)) अणु
		DRM_DEBUG("Bin CL must end with "
			  "VC4_PACKET_INCREMENT_SEMAPHORE\n");
		वापस -EINVAL;
	पूर्ण
	exec->found_increment_semaphore_packet = true;

	वापस 0;
पूर्ण

अटल पूर्णांक
validate_indexed_prim_list(VALIDATE_ARGS)
अणु
	काष्ठा drm_gem_cma_object *ib;
	uपूर्णांक32_t length = *(uपूर्णांक32_t *)(untrusted + 1);
	uपूर्णांक32_t offset = *(uपूर्णांक32_t *)(untrusted + 5);
	uपूर्णांक32_t max_index = *(uपूर्णांक32_t *)(untrusted + 9);
	uपूर्णांक32_t index_size = (*(uपूर्णांक8_t *)(untrusted + 0) >> 4) ? 2 : 1;
	काष्ठा vc4_shader_state *shader_state;

	/* Check overflow condition */
	अगर (exec->shader_state_count == 0) अणु
		DRM_DEBUG("shader state must precede primitives\n");
		वापस -EINVAL;
	पूर्ण
	shader_state = &exec->shader_state[exec->shader_state_count - 1];

	अगर (max_index > shader_state->max_index)
		shader_state->max_index = max_index;

	ib = vc4_use_handle(exec, 0);
	अगर (!ib)
		वापस -EINVAL;

	exec->bin_dep_seqno = max(exec->bin_dep_seqno,
				  to_vc4_bo(&ib->base)->ग_लिखो_seqno);

	अगर (offset > ib->base.size ||
	    (ib->base.size - offset) / index_size < length) अणु
		DRM_DEBUG("IB access overflow (%d + %d*%d > %zd)\n",
			  offset, length, index_size, ib->base.size);
		वापस -EINVAL;
	पूर्ण

	*(uपूर्णांक32_t *)(validated + 5) = ib->paddr + offset;

	वापस 0;
पूर्ण

अटल पूर्णांक
validate_gl_array_primitive(VALIDATE_ARGS)
अणु
	uपूर्णांक32_t length = *(uपूर्णांक32_t *)(untrusted + 1);
	uपूर्णांक32_t base_index = *(uपूर्णांक32_t *)(untrusted + 5);
	uपूर्णांक32_t max_index;
	काष्ठा vc4_shader_state *shader_state;

	/* Check overflow condition */
	अगर (exec->shader_state_count == 0) अणु
		DRM_DEBUG("shader state must precede primitives\n");
		वापस -EINVAL;
	पूर्ण
	shader_state = &exec->shader_state[exec->shader_state_count - 1];

	अगर (length + base_index < length) अणु
		DRM_DEBUG("primitive vertex count overflow\n");
		वापस -EINVAL;
	पूर्ण
	max_index = length + base_index - 1;

	अगर (max_index > shader_state->max_index)
		shader_state->max_index = max_index;

	वापस 0;
पूर्ण

अटल पूर्णांक
validate_gl_shader_state(VALIDATE_ARGS)
अणु
	uपूर्णांक32_t i = exec->shader_state_count++;

	अगर (i >= exec->shader_state_size) अणु
		DRM_DEBUG("More requests for shader states than declared\n");
		वापस -EINVAL;
	पूर्ण

	exec->shader_state[i].addr = *(uपूर्णांक32_t *)untrusted;
	exec->shader_state[i].max_index = 0;

	अगर (exec->shader_state[i].addr & ~0xf) अणु
		DRM_DEBUG("high bits set in GL shader rec reference\n");
		वापस -EINVAL;
	पूर्ण

	*(uपूर्णांक32_t *)validated = (exec->shader_rec_p +
				  exec->shader_state[i].addr);

	exec->shader_rec_p +=
		roundup(gl_shader_rec_size(exec->shader_state[i].addr), 16);

	वापस 0;
पूर्ण

अटल पूर्णांक
validate_tile_binning_config(VALIDATE_ARGS)
अणु
	काष्ठा drm_device *dev = exec->exec_bo->base.dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	uपूर्णांक8_t flags;
	uपूर्णांक32_t tile_state_size;
	uपूर्णांक32_t tile_count, bin_addr;
	पूर्णांक bin_slot;

	अगर (exec->found_tile_binning_mode_config_packet) अणु
		DRM_DEBUG("Duplicate VC4_PACKET_TILE_BINNING_MODE_CONFIG\n");
		वापस -EINVAL;
	पूर्ण
	exec->found_tile_binning_mode_config_packet = true;

	exec->bin_tiles_x = *(uपूर्णांक8_t *)(untrusted + 12);
	exec->bin_tiles_y = *(uपूर्णांक8_t *)(untrusted + 13);
	tile_count = exec->bin_tiles_x * exec->bin_tiles_y;
	flags = *(uपूर्णांक8_t *)(untrusted + 14);

	अगर (exec->bin_tiles_x == 0 ||
	    exec->bin_tiles_y == 0) अणु
		DRM_DEBUG("Tile binning config of %dx%d too small\n",
			  exec->bin_tiles_x, exec->bin_tiles_y);
		वापस -EINVAL;
	पूर्ण

	अगर (flags & (VC4_BIN_CONFIG_DB_NON_MS |
		     VC4_BIN_CONFIG_TILE_BUFFER_64BIT)) अणु
		DRM_DEBUG("unsupported binning config flags 0x%02x\n", flags);
		वापस -EINVAL;
	पूर्ण

	bin_slot = vc4_v3d_get_bin_slot(vc4);
	अगर (bin_slot < 0) अणु
		अगर (bin_slot != -EINTR && bin_slot != -ERESTARTSYS) अणु
			DRM_ERROR("Failed to allocate binner memory: %d\n",
				  bin_slot);
		पूर्ण
		वापस bin_slot;
	पूर्ण

	/* The slot we allocated will only be used by this job, and is
	 * मुक्त when the job completes rendering.
	 */
	exec->bin_slots |= BIT(bin_slot);
	bin_addr = vc4->bin_bo->base.paddr + bin_slot * vc4->bin_alloc_size;

	/* The tile state data array is 48 bytes per tile, and we put it at
	 * the start of a BO containing both it and the tile alloc.
	 */
	tile_state_size = 48 * tile_count;

	/* Since the tile alloc array will follow us, align. */
	exec->tile_alloc_offset = bin_addr + roundup(tile_state_size, 4096);

	*(uपूर्णांक8_t *)(validated + 14) =
		((flags & ~(VC4_BIN_CONFIG_ALLOC_INIT_BLOCK_SIZE_MASK |
			    VC4_BIN_CONFIG_ALLOC_BLOCK_SIZE_MASK)) |
		 VC4_BIN_CONFIG_AUTO_INIT_TSDA |
		 VC4_SET_FIELD(VC4_BIN_CONFIG_ALLOC_INIT_BLOCK_SIZE_32,
			       VC4_BIN_CONFIG_ALLOC_INIT_BLOCK_SIZE) |
		 VC4_SET_FIELD(VC4_BIN_CONFIG_ALLOC_BLOCK_SIZE_128,
			       VC4_BIN_CONFIG_ALLOC_BLOCK_SIZE));

	/* tile alloc address. */
	*(uपूर्णांक32_t *)(validated + 0) = exec->tile_alloc_offset;
	/* tile alloc size. */
	*(uपूर्णांक32_t *)(validated + 4) = (bin_addr + vc4->bin_alloc_size -
					exec->tile_alloc_offset);
	/* tile state address. */
	*(uपूर्णांक32_t *)(validated + 8) = bin_addr;

	वापस 0;
पूर्ण

अटल पूर्णांक
validate_gem_handles(VALIDATE_ARGS)
अणु
	स_नकल(exec->bo_index, untrusted, माप(exec->bo_index));
	वापस 0;
पूर्ण

#घोषणा VC4_DEFINE_PACKET(packet, func) \
	[packet] = अणु packet ## _SIZE, #packet, func पूर्ण

अटल स्थिर काष्ठा cmd_info अणु
	uपूर्णांक16_t len;
	स्थिर अक्षर *name;
	पूर्णांक (*func)(काष्ठा vc4_exec_info *exec, व्योम *validated,
		    व्योम *untrusted);
पूर्ण cmd_info[] = अणु
	VC4_DEFINE_PACKET(VC4_PACKET_HALT, शून्य),
	VC4_DEFINE_PACKET(VC4_PACKET_NOP, शून्य),
	VC4_DEFINE_PACKET(VC4_PACKET_FLUSH, validate_flush),
	VC4_DEFINE_PACKET(VC4_PACKET_FLUSH_ALL, शून्य),
	VC4_DEFINE_PACKET(VC4_PACKET_START_TILE_BINNING,
			  validate_start_tile_binning),
	VC4_DEFINE_PACKET(VC4_PACKET_INCREMENT_SEMAPHORE,
			  validate_increment_semaphore),

	VC4_DEFINE_PACKET(VC4_PACKET_GL_INDEXED_PRIMITIVE,
			  validate_indexed_prim_list),
	VC4_DEFINE_PACKET(VC4_PACKET_GL_ARRAY_PRIMITIVE,
			  validate_gl_array_primitive),

	VC4_DEFINE_PACKET(VC4_PACKET_PRIMITIVE_LIST_FORMAT, शून्य),

	VC4_DEFINE_PACKET(VC4_PACKET_GL_SHADER_STATE, validate_gl_shader_state),

	VC4_DEFINE_PACKET(VC4_PACKET_CONFIGURATION_BITS, शून्य),
	VC4_DEFINE_PACKET(VC4_PACKET_FLAT_SHADE_FLAGS, शून्य),
	VC4_DEFINE_PACKET(VC4_PACKET_POINT_SIZE, शून्य),
	VC4_DEFINE_PACKET(VC4_PACKET_LINE_WIDTH, शून्य),
	VC4_DEFINE_PACKET(VC4_PACKET_RHT_X_BOUNDARY, शून्य),
	VC4_DEFINE_PACKET(VC4_PACKET_DEPTH_OFFSET, शून्य),
	VC4_DEFINE_PACKET(VC4_PACKET_CLIP_WINDOW, शून्य),
	VC4_DEFINE_PACKET(VC4_PACKET_VIEWPORT_OFFSET, शून्य),
	VC4_DEFINE_PACKET(VC4_PACKET_CLIPPER_XY_SCALING, शून्य),
	/* Note: The करोcs say this was also 105, but it was 106 in the
	 * initial userland code drop.
	 */
	VC4_DEFINE_PACKET(VC4_PACKET_CLIPPER_Z_SCALING, शून्य),

	VC4_DEFINE_PACKET(VC4_PACKET_TILE_BINNING_MODE_CONFIG,
			  validate_tile_binning_config),

	VC4_DEFINE_PACKET(VC4_PACKET_GEM_HANDLES, validate_gem_handles),
पूर्ण;

पूर्णांक
vc4_validate_bin_cl(काष्ठा drm_device *dev,
		    व्योम *validated,
		    व्योम *unvalidated,
		    काष्ठा vc4_exec_info *exec)
अणु
	uपूर्णांक32_t len = exec->args->bin_cl_size;
	uपूर्णांक32_t dst_offset = 0;
	uपूर्णांक32_t src_offset = 0;

	जबतक (src_offset < len) अणु
		व्योम *dst_pkt = validated + dst_offset;
		व्योम *src_pkt = unvalidated + src_offset;
		u8 cmd = *(uपूर्णांक8_t *)src_pkt;
		स्थिर काष्ठा cmd_info *info;

		अगर (cmd >= ARRAY_SIZE(cmd_info)) अणु
			DRM_DEBUG("0x%08x: packet %d out of bounds\n",
				  src_offset, cmd);
			वापस -EINVAL;
		पूर्ण

		info = &cmd_info[cmd];
		अगर (!info->name) अणु
			DRM_DEBUG("0x%08x: packet %d invalid\n",
				  src_offset, cmd);
			वापस -EINVAL;
		पूर्ण

		अगर (src_offset + info->len > len) अणु
			DRM_DEBUG("0x%08x: packet %d (%s) length 0x%08x "
				  "exceeds bounds (0x%08x)\n",
				  src_offset, cmd, info->name, info->len,
				  src_offset + len);
			वापस -EINVAL;
		पूर्ण

		अगर (cmd != VC4_PACKET_GEM_HANDLES)
			स_नकल(dst_pkt, src_pkt, info->len);

		अगर (info->func && info->func(exec,
					     dst_pkt + 1,
					     src_pkt + 1)) अणु
			DRM_DEBUG("0x%08x: packet %d (%s) failed to validate\n",
				  src_offset, cmd, info->name);
			वापस -EINVAL;
		पूर्ण

		src_offset += info->len;
		/* GEM handle loading करोesn't produce HW packets. */
		अगर (cmd != VC4_PACKET_GEM_HANDLES)
			dst_offset += info->len;

		/* When the CL hits halt, it'll stop पढ़ोing anything अन्यथा. */
		अगर (cmd == VC4_PACKET_HALT)
			अवरोध;
	पूर्ण

	exec->ct0ea = exec->ct0ca + dst_offset;

	अगर (!exec->found_start_tile_binning_packet) अणु
		DRM_DEBUG("Bin CL missing VC4_PACKET_START_TILE_BINNING\n");
		वापस -EINVAL;
	पूर्ण

	/* The bin CL must be ended with INCREMENT_SEMAPHORE and FLUSH.  The
	 * semaphore is used to trigger the render CL to start up, and the
	 * FLUSH is what caps the bin lists with
	 * VC4_PACKET_RETURN_FROM_SUB_LIST (so they jump back to the मुख्य
	 * render CL when they get called to) and actually triggers the queued
	 * semaphore increment.
	 */
	अगर (!exec->found_increment_semaphore_packet || !exec->found_flush) अणु
		DRM_DEBUG("Bin CL missing VC4_PACKET_INCREMENT_SEMAPHORE + "
			  "VC4_PACKET_FLUSH\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
reloc_tex(काष्ठा vc4_exec_info *exec,
	  व्योम *unअगरorm_data_u,
	  काष्ठा vc4_texture_sample_info *sample,
	  uपूर्णांक32_t texture_handle_index, bool is_cs)
अणु
	काष्ठा drm_gem_cma_object *tex;
	uपूर्णांक32_t p0 = *(uपूर्णांक32_t *)(unअगरorm_data_u + sample->p_offset[0]);
	uपूर्णांक32_t p1 = *(uपूर्णांक32_t *)(unअगरorm_data_u + sample->p_offset[1]);
	uपूर्णांक32_t p2 = (sample->p_offset[2] != ~0 ?
		       *(uपूर्णांक32_t *)(unअगरorm_data_u + sample->p_offset[2]) : 0);
	uपूर्णांक32_t p3 = (sample->p_offset[3] != ~0 ?
		       *(uपूर्णांक32_t *)(unअगरorm_data_u + sample->p_offset[3]) : 0);
	uपूर्णांक32_t *validated_p0 = exec->unअगरorms_v + sample->p_offset[0];
	uपूर्णांक32_t offset = p0 & VC4_TEX_P0_OFFSET_MASK;
	uपूर्णांक32_t miplevels = VC4_GET_FIELD(p0, VC4_TEX_P0_MIPLVLS);
	uपूर्णांक32_t width = VC4_GET_FIELD(p1, VC4_TEX_P1_WIDTH);
	uपूर्णांक32_t height = VC4_GET_FIELD(p1, VC4_TEX_P1_HEIGHT);
	uपूर्णांक32_t cpp, tiling_क्रमmat, utile_w, utile_h;
	uपूर्णांक32_t i;
	uपूर्णांक32_t cube_map_stride = 0;
	क्रमागत vc4_texture_data_type type;

	tex = vc4_use_bo(exec, texture_handle_index);
	अगर (!tex)
		वापस false;

	अगर (sample->is_direct) अणु
		uपूर्णांक32_t reमुख्यing_size = tex->base.size - p0;

		अगर (p0 > tex->base.size - 4) अणु
			DRM_DEBUG("UBO offset greater than UBO size\n");
			जाओ fail;
		पूर्ण
		अगर (p1 > reमुख्यing_size - 4) अणु
			DRM_DEBUG("UBO clamp would allow reads "
				  "outside of UBO\n");
			जाओ fail;
		पूर्ण
		*validated_p0 = tex->paddr + p0;
		वापस true;
	पूर्ण

	अगर (width == 0)
		width = 2048;
	अगर (height == 0)
		height = 2048;

	अगर (p0 & VC4_TEX_P0_CMMODE_MASK) अणु
		अगर (VC4_GET_FIELD(p2, VC4_TEX_P2_PTYPE) ==
		    VC4_TEX_P2_PTYPE_CUBE_MAP_STRIDE)
			cube_map_stride = p2 & VC4_TEX_P2_CMST_MASK;
		अगर (VC4_GET_FIELD(p3, VC4_TEX_P2_PTYPE) ==
		    VC4_TEX_P2_PTYPE_CUBE_MAP_STRIDE) अणु
			अगर (cube_map_stride) अणु
				DRM_DEBUG("Cube map stride set twice\n");
				जाओ fail;
			पूर्ण

			cube_map_stride = p3 & VC4_TEX_P2_CMST_MASK;
		पूर्ण
		अगर (!cube_map_stride) अणु
			DRM_DEBUG("Cube map stride not set\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	type = (VC4_GET_FIELD(p0, VC4_TEX_P0_TYPE) |
		(VC4_GET_FIELD(p1, VC4_TEX_P1_TYPE4) << 4));

	चयन (type) अणु
	हाल VC4_TEXTURE_TYPE_RGBA8888:
	हाल VC4_TEXTURE_TYPE_RGBX8888:
	हाल VC4_TEXTURE_TYPE_RGBA32R:
		cpp = 4;
		अवरोध;
	हाल VC4_TEXTURE_TYPE_RGBA4444:
	हाल VC4_TEXTURE_TYPE_RGBA5551:
	हाल VC4_TEXTURE_TYPE_RGB565:
	हाल VC4_TEXTURE_TYPE_LUMALPHA:
	हाल VC4_TEXTURE_TYPE_S16F:
	हाल VC4_TEXTURE_TYPE_S16:
		cpp = 2;
		अवरोध;
	हाल VC4_TEXTURE_TYPE_LUMIन_अंकCE:
	हाल VC4_TEXTURE_TYPE_ALPHA:
	हाल VC4_TEXTURE_TYPE_S8:
		cpp = 1;
		अवरोध;
	हाल VC4_TEXTURE_TYPE_ETC1:
		/* ETC1 is arranged as 64-bit blocks, where each block is 4x4
		 * pixels.
		 */
		cpp = 8;
		width = (width + 3) >> 2;
		height = (height + 3) >> 2;
		अवरोध;
	हाल VC4_TEXTURE_TYPE_BW1:
	हाल VC4_TEXTURE_TYPE_A4:
	हाल VC4_TEXTURE_TYPE_A1:
	हाल VC4_TEXTURE_TYPE_RGBA64:
	हाल VC4_TEXTURE_TYPE_YUV422R:
	शेष:
		DRM_DEBUG("Texture format %d unsupported\n", type);
		जाओ fail;
	पूर्ण
	utile_w = utile_width(cpp);
	utile_h = utile_height(cpp);

	अगर (type == VC4_TEXTURE_TYPE_RGBA32R) अणु
		tiling_क्रमmat = VC4_TILING_FORMAT_LINEAR;
	पूर्ण अन्यथा अणु
		अगर (size_is_lt(width, height, cpp))
			tiling_क्रमmat = VC4_TILING_FORMAT_LT;
		अन्यथा
			tiling_क्रमmat = VC4_TILING_FORMAT_T;
	पूर्ण

	अगर (!vc4_check_tex_size(exec, tex, offset + cube_map_stride * 5,
				tiling_क्रमmat, width, height, cpp)) अणु
		जाओ fail;
	पूर्ण

	/* The mipmap levels are stored beक्रमe the base of the texture.  Make
	 * sure there is actually space in the BO.
	 */
	क्रम (i = 1; i <= miplevels; i++) अणु
		uपूर्णांक32_t level_width = max(width >> i, 1u);
		uपूर्णांक32_t level_height = max(height >> i, 1u);
		uपूर्णांक32_t aligned_width, aligned_height;
		uपूर्णांक32_t level_size;

		/* Once the levels get small enough, they drop from T to LT. */
		अगर (tiling_क्रमmat == VC4_TILING_FORMAT_T &&
		    size_is_lt(level_width, level_height, cpp)) अणु
			tiling_क्रमmat = VC4_TILING_FORMAT_LT;
		पूर्ण

		चयन (tiling_क्रमmat) अणु
		हाल VC4_TILING_FORMAT_T:
			aligned_width = round_up(level_width, utile_w * 8);
			aligned_height = round_up(level_height, utile_h * 8);
			अवरोध;
		हाल VC4_TILING_FORMAT_LT:
			aligned_width = round_up(level_width, utile_w);
			aligned_height = round_up(level_height, utile_h);
			अवरोध;
		शेष:
			aligned_width = round_up(level_width, utile_w);
			aligned_height = level_height;
			अवरोध;
		पूर्ण

		level_size = aligned_width * cpp * aligned_height;

		अगर (offset < level_size) अणु
			DRM_DEBUG("Level %d (%dx%d -> %dx%d) size %db "
				  "overflowed buffer bounds (offset %d)\n",
				  i, level_width, level_height,
				  aligned_width, aligned_height,
				  level_size, offset);
			जाओ fail;
		पूर्ण

		offset -= level_size;
	पूर्ण

	*validated_p0 = tex->paddr + p0;

	अगर (is_cs) अणु
		exec->bin_dep_seqno = max(exec->bin_dep_seqno,
					  to_vc4_bo(&tex->base)->ग_लिखो_seqno);
	पूर्ण

	वापस true;
 fail:
	DRM_INFO("Texture p0 at %d: 0x%08x\n", sample->p_offset[0], p0);
	DRM_INFO("Texture p1 at %d: 0x%08x\n", sample->p_offset[1], p1);
	DRM_INFO("Texture p2 at %d: 0x%08x\n", sample->p_offset[2], p2);
	DRM_INFO("Texture p3 at %d: 0x%08x\n", sample->p_offset[3], p3);
	वापस false;
पूर्ण

अटल पूर्णांक
validate_gl_shader_rec(काष्ठा drm_device *dev,
		       काष्ठा vc4_exec_info *exec,
		       काष्ठा vc4_shader_state *state)
अणु
	uपूर्णांक32_t *src_handles;
	व्योम *pkt_u, *pkt_v;
	अटल स्थिर uपूर्णांक32_t shader_reloc_offsets[] = अणु
		4, /* fs */
		16, /* vs */
		28, /* cs */
	पूर्ण;
	uपूर्णांक32_t shader_reloc_count = ARRAY_SIZE(shader_reloc_offsets);
	काष्ठा drm_gem_cma_object *bo[ARRAY_SIZE(shader_reloc_offsets) + 8];
	uपूर्णांक32_t nr_attributes, nr_relocs, packet_size;
	पूर्णांक i;

	nr_attributes = state->addr & 0x7;
	अगर (nr_attributes == 0)
		nr_attributes = 8;
	packet_size = gl_shader_rec_size(state->addr);

	nr_relocs = ARRAY_SIZE(shader_reloc_offsets) + nr_attributes;
	अगर (nr_relocs * 4 > exec->shader_rec_size) अणु
		DRM_DEBUG("overflowed shader recs reading %d handles "
			  "from %d bytes left\n",
			  nr_relocs, exec->shader_rec_size);
		वापस -EINVAL;
	पूर्ण
	src_handles = exec->shader_rec_u;
	exec->shader_rec_u += nr_relocs * 4;
	exec->shader_rec_size -= nr_relocs * 4;

	अगर (packet_size > exec->shader_rec_size) अणु
		DRM_DEBUG("overflowed shader recs copying %db packet "
			  "from %d bytes left\n",
			  packet_size, exec->shader_rec_size);
		वापस -EINVAL;
	पूर्ण
	pkt_u = exec->shader_rec_u;
	pkt_v = exec->shader_rec_v;
	स_नकल(pkt_v, pkt_u, packet_size);
	exec->shader_rec_u += packet_size;
	/* Shader recs have to be aligned to 16 bytes (due to the attribute
	 * flags being in the low bytes), so round the next validated shader
	 * rec address up.  This should be safe, since we've got so many
	 * relocations in a shader rec packet.
	 */
	BUG_ON(roundup(packet_size, 16) - packet_size > nr_relocs * 4);
	exec->shader_rec_v += roundup(packet_size, 16);
	exec->shader_rec_size -= packet_size;

	क्रम (i = 0; i < shader_reloc_count; i++) अणु
		अगर (src_handles[i] > exec->bo_count) अणु
			DRM_DEBUG("Shader handle %d too big\n", src_handles[i]);
			वापस -EINVAL;
		पूर्ण

		bo[i] = exec->bo[src_handles[i]];
		अगर (!bo[i])
			वापस -EINVAL;
	पूर्ण
	क्रम (i = shader_reloc_count; i < nr_relocs; i++) अणु
		bo[i] = vc4_use_bo(exec, src_handles[i]);
		अगर (!bo[i])
			वापस -EINVAL;
	पूर्ण

	अगर (((*(uपूर्णांक16_t *)pkt_u & VC4_SHADER_FLAG_FS_SINGLE_THREAD) == 0) !=
	    to_vc4_bo(&bo[0]->base)->validated_shader->is_thपढ़ोed) अणु
		DRM_DEBUG("Thread mode of CL and FS do not match\n");
		वापस -EINVAL;
	पूर्ण

	अगर (to_vc4_bo(&bo[1]->base)->validated_shader->is_thपढ़ोed ||
	    to_vc4_bo(&bo[2]->base)->validated_shader->is_thपढ़ोed) अणु
		DRM_DEBUG("cs and vs cannot be threaded\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < shader_reloc_count; i++) अणु
		काष्ठा vc4_validated_shader_info *validated_shader;
		uपूर्णांक32_t o = shader_reloc_offsets[i];
		uपूर्णांक32_t src_offset = *(uपूर्णांक32_t *)(pkt_u + o);
		uपूर्णांक32_t *texture_handles_u;
		व्योम *unअगरorm_data_u;
		uपूर्णांक32_t tex, uni;

		*(uपूर्णांक32_t *)(pkt_v + o) = bo[i]->paddr + src_offset;

		अगर (src_offset != 0) अणु
			DRM_DEBUG("Shaders must be at offset 0 of "
				  "the BO.\n");
			वापस -EINVAL;
		पूर्ण

		validated_shader = to_vc4_bo(&bo[i]->base)->validated_shader;
		अगर (!validated_shader)
			वापस -EINVAL;

		अगर (validated_shader->unअगरorms_src_size >
		    exec->unअगरorms_size) अणु
			DRM_DEBUG("Uniforms src buffer overflow\n");
			वापस -EINVAL;
		पूर्ण

		texture_handles_u = exec->unअगरorms_u;
		unअगरorm_data_u = (texture_handles_u +
				  validated_shader->num_texture_samples);

		स_नकल(exec->unअगरorms_v, unअगरorm_data_u,
		       validated_shader->unअगरorms_size);

		क्रम (tex = 0;
		     tex < validated_shader->num_texture_samples;
		     tex++) अणु
			अगर (!reloc_tex(exec,
				       unअगरorm_data_u,
				       &validated_shader->texture_samples[tex],
				       texture_handles_u[tex],
				       i == 2)) अणु
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		/* Fill in the unअगरorm slots that need this shader's
		 * start-of-unअगरorms address (used क्रम resetting the unअगरorm
		 * stream in the presence of control flow).
		 */
		क्रम (uni = 0;
		     uni < validated_shader->num_unअगरorm_addr_offsets;
		     uni++) अणु
			uपूर्णांक32_t o = validated_shader->unअगरorm_addr_offsets[uni];
			((uपूर्णांक32_t *)exec->unअगरorms_v)[o] = exec->unअगरorms_p;
		पूर्ण

		*(uपूर्णांक32_t *)(pkt_v + o + 4) = exec->unअगरorms_p;

		exec->unअगरorms_u += validated_shader->unअगरorms_src_size;
		exec->unअगरorms_v += validated_shader->unअगरorms_size;
		exec->unअगरorms_p += validated_shader->unअगरorms_size;
	पूर्ण

	क्रम (i = 0; i < nr_attributes; i++) अणु
		काष्ठा drm_gem_cma_object *vbo =
			bo[ARRAY_SIZE(shader_reloc_offsets) + i];
		uपूर्णांक32_t o = 36 + i * 8;
		uपूर्णांक32_t offset = *(uपूर्णांक32_t *)(pkt_u + o + 0);
		uपूर्णांक32_t attr_size = *(uपूर्णांक8_t *)(pkt_u + o + 4) + 1;
		uपूर्णांक32_t stride = *(uपूर्णांक8_t *)(pkt_u + o + 5);
		uपूर्णांक32_t max_index;

		exec->bin_dep_seqno = max(exec->bin_dep_seqno,
					  to_vc4_bo(&vbo->base)->ग_लिखो_seqno);

		अगर (state->addr & 0x8)
			stride |= (*(uपूर्णांक32_t *)(pkt_u + 100 + i * 4)) & ~0xff;

		अगर (vbo->base.size < offset ||
		    vbo->base.size - offset < attr_size) अणु
			DRM_DEBUG("BO offset overflow (%d + %d > %zu)\n",
				  offset, attr_size, vbo->base.size);
			वापस -EINVAL;
		पूर्ण

		अगर (stride != 0) अणु
			max_index = ((vbo->base.size - offset - attr_size) /
				     stride);
			अगर (state->max_index > max_index) अणु
				DRM_DEBUG("primitives use index %d out of "
					  "supplied %d\n",
					  state->max_index, max_index);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		*(uपूर्णांक32_t *)(pkt_v + o) = vbo->paddr + offset;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
vc4_validate_shader_recs(काष्ठा drm_device *dev,
			 काष्ठा vc4_exec_info *exec)
अणु
	uपूर्णांक32_t i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < exec->shader_state_count; i++) अणु
		ret = validate_gl_shader_rec(dev, exec, &exec->shader_state[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण
