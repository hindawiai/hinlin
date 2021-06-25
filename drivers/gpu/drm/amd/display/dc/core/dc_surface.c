<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश <linux/mm.h>

/* DC पूर्णांकerface (खुला) */
#समावेश "dm_services.h"
#समावेश "dc.h"

/* DC core (निजी) */
#समावेश "core_types.h"
#समावेश "transform.h"
#समावेश "dpp.h"

/*******************************************************************************
 * Private functions
 ******************************************************************************/
अटल व्योम dc_plane_स्थिरruct(काष्ठा dc_context *ctx, काष्ठा dc_plane_state *plane_state)
अणु
	plane_state->ctx = ctx;

	plane_state->gamma_correction = dc_create_gamma();
	अगर (plane_state->gamma_correction != शून्य)
		plane_state->gamma_correction->is_identity = true;

	plane_state->in_transfer_func = dc_create_transfer_func();
	अगर (plane_state->in_transfer_func != शून्य) अणु
		plane_state->in_transfer_func->type = TF_TYPE_BYPASS;
	पूर्ण
	plane_state->in_shaper_func = dc_create_transfer_func();
	अगर (plane_state->in_shaper_func != शून्य) अणु
		plane_state->in_shaper_func->type = TF_TYPE_BYPASS;
	पूर्ण

	plane_state->lut3d_func = dc_create_3dlut_func();

	plane_state->blend_tf = dc_create_transfer_func();
	अगर (plane_state->blend_tf != शून्य) अणु
		plane_state->blend_tf->type = TF_TYPE_BYPASS;
	पूर्ण

पूर्ण

अटल व्योम dc_plane_deकाष्ठा(काष्ठा dc_plane_state *plane_state)
अणु
	अगर (plane_state->gamma_correction != शून्य) अणु
		dc_gamma_release(&plane_state->gamma_correction);
	पूर्ण
	अगर (plane_state->in_transfer_func != शून्य) अणु
		dc_transfer_func_release(
				plane_state->in_transfer_func);
		plane_state->in_transfer_func = शून्य;
	पूर्ण
	अगर (plane_state->in_shaper_func != शून्य) अणु
		dc_transfer_func_release(
				plane_state->in_shaper_func);
		plane_state->in_shaper_func = शून्य;
	पूर्ण
	अगर (plane_state->lut3d_func != शून्य) अणु
		dc_3dlut_func_release(
				plane_state->lut3d_func);
		plane_state->lut3d_func = शून्य;
	पूर्ण
	अगर (plane_state->blend_tf != शून्य) अणु
		dc_transfer_func_release(
				plane_state->blend_tf);
		plane_state->blend_tf = शून्य;
	पूर्ण

पूर्ण

/*******************************************************************************
 * Public functions
 ******************************************************************************/
व्योम enable_surface_flip_reporting(काष्ठा dc_plane_state *plane_state,
		uपूर्णांक32_t controller_id)
अणु
	plane_state->irq_source = controller_id + DC_IRQ_SOURCE_PFLIP1 - 1;
	/*रेजिस्टर_flip_पूर्णांकerrupt(surface);*/
पूर्ण

काष्ठा dc_plane_state *dc_create_plane_state(काष्ठा dc *dc)
अणु
	काष्ठा dc_plane_state *plane_state = kvzalloc(माप(*plane_state),
							GFP_KERNEL);

	अगर (शून्य == plane_state)
		वापस शून्य;

	kref_init(&plane_state->refcount);
	dc_plane_स्थिरruct(dc->ctx, plane_state);

	वापस plane_state;
पूर्ण

/*
 *****************************************************************************
 *  Function: dc_plane_get_status
 *
 *  @brief
 *     Looks up the pipe context of plane_state and updates the pending status
 *     of the pipe context. Then वापसs plane_state->status
 *
 *  @param [in] plane_state: poपूर्णांकer to the plane_state to get the status of
 *****************************************************************************
 */
स्थिर काष्ठा dc_plane_status *dc_plane_get_status(
		स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	स्थिर काष्ठा dc_plane_status *plane_status;
	काष्ठा dc  *dc;
	पूर्णांक i;

	अगर (!plane_state ||
		!plane_state->ctx ||
		!plane_state->ctx->dc) अणु
		ASSERT(0);
		वापस शून्य; /* हटाओ this अगर above निश्चित never hit */
	पूर्ण

	plane_status = &plane_state->status;
	dc = plane_state->ctx->dc;

	अगर (dc->current_state == शून्य)
		वापस शून्य;

	/* Find the current plane state and set its pending bit to false */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx =
				&dc->current_state->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->plane_state != plane_state)
			जारी;

		pipe_ctx->plane_state->status.is_flip_pending = false;

		अवरोध;
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx =
				&dc->current_state->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->plane_state != plane_state)
			जारी;

		dc->hwss.update_pending_status(pipe_ctx);
	पूर्ण

	वापस plane_status;
पूर्ण

व्योम dc_plane_state_retain(काष्ठा dc_plane_state *plane_state)
अणु
	kref_get(&plane_state->refcount);
पूर्ण

अटल व्योम dc_plane_state_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा dc_plane_state *plane_state = container_of(kref, काष्ठा dc_plane_state, refcount);
	dc_plane_deकाष्ठा(plane_state);
	kvमुक्त(plane_state);
पूर्ण

व्योम dc_plane_state_release(काष्ठा dc_plane_state *plane_state)
अणु
	kref_put(&plane_state->refcount, dc_plane_state_मुक्त);
पूर्ण

व्योम dc_gamma_retain(काष्ठा dc_gamma *gamma)
अणु
	kref_get(&gamma->refcount);
पूर्ण

अटल व्योम dc_gamma_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा dc_gamma *gamma = container_of(kref, काष्ठा dc_gamma, refcount);
	kvमुक्त(gamma);
पूर्ण

व्योम dc_gamma_release(काष्ठा dc_gamma **gamma)
अणु
	kref_put(&(*gamma)->refcount, dc_gamma_मुक्त);
	*gamma = शून्य;
पूर्ण

काष्ठा dc_gamma *dc_create_gamma(व्योम)
अणु
	काष्ठा dc_gamma *gamma = kvzalloc(माप(*gamma), GFP_KERNEL);

	अगर (gamma == शून्य)
		जाओ alloc_fail;

	kref_init(&gamma->refcount);
	वापस gamma;

alloc_fail:
	वापस शून्य;
पूर्ण

व्योम dc_transfer_func_retain(काष्ठा dc_transfer_func *tf)
अणु
	kref_get(&tf->refcount);
पूर्ण

अटल व्योम dc_transfer_func_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा dc_transfer_func *tf = container_of(kref, काष्ठा dc_transfer_func, refcount);
	kvमुक्त(tf);
पूर्ण

व्योम dc_transfer_func_release(काष्ठा dc_transfer_func *tf)
अणु
	kref_put(&tf->refcount, dc_transfer_func_मुक्त);
पूर्ण

काष्ठा dc_transfer_func *dc_create_transfer_func(व्योम)
अणु
	काष्ठा dc_transfer_func *tf = kvzalloc(माप(*tf), GFP_KERNEL);

	अगर (tf == शून्य)
		जाओ alloc_fail;

	kref_init(&tf->refcount);

	वापस tf;

alloc_fail:
	वापस शून्य;
पूर्ण

अटल व्योम dc_3dlut_func_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा dc_3dlut *lut = container_of(kref, काष्ठा dc_3dlut, refcount);

	kvमुक्त(lut);
पूर्ण

काष्ठा dc_3dlut *dc_create_3dlut_func(व्योम)
अणु
	काष्ठा dc_3dlut *lut = kvzalloc(माप(*lut), GFP_KERNEL);

	अगर (lut == शून्य)
		जाओ alloc_fail;

	kref_init(&lut->refcount);
	lut->state.raw = 0;

	वापस lut;

alloc_fail:
	वापस शून्य;

पूर्ण

व्योम dc_3dlut_func_release(काष्ठा dc_3dlut *lut)
अणु
	kref_put(&lut->refcount, dc_3dlut_func_मुक्त);
पूर्ण

व्योम dc_3dlut_func_retain(काष्ठा dc_3dlut *lut)
अणु
	kref_get(&lut->refcount);
पूर्ण


