<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test हाल क्रम drm_damage_helper functions
 */

#घोषणा pr_fmt(fmt) "drm_damage_helper: " fmt

#समावेश <drm/drm_damage_helper.h>

#समावेश "test-drm_modeset_common.h"

अटल व्योम set_plane_src(काष्ठा drm_plane_state *state, पूर्णांक x1, पूर्णांक y1, पूर्णांक x2,
			  पूर्णांक y2)
अणु
	state->src.x1 = x1;
	state->src.y1 = y1;
	state->src.x2 = x2;
	state->src.y2 = y2;
पूर्ण

अटल व्योम set_damage_clip(काष्ठा drm_mode_rect *r, पूर्णांक x1, पूर्णांक y1, पूर्णांक x2,
			    पूर्णांक y2)
अणु
	r->x1 = x1;
	r->y1 = y1;
	r->x2 = x2;
	r->y2 = y2;
पूर्ण

अटल व्योम set_damage_blob(काष्ठा drm_property_blob *damage_blob,
			    काष्ठा drm_mode_rect *r, uपूर्णांक32_t size)
अणु
	damage_blob->length = size;
	damage_blob->data = r;
पूर्ण

अटल व्योम set_plane_damage(काष्ठा drm_plane_state *state,
			     काष्ठा drm_property_blob *damage_blob)
अणु
	state->fb_damage_clips = damage_blob;
पूर्ण

अटल bool check_damage_clip(काष्ठा drm_plane_state *state, काष्ठा drm_rect *r,
			      पूर्णांक x1, पूर्णांक y1, पूर्णांक x2, पूर्णांक y2)
अणु
	/*
	 * Round करोwn x1/y1 and round up x2/y2. This is because damage is not in
	 * 16.16 fixed poपूर्णांक so to catch all pixels.
	 */
	पूर्णांक src_x1 = state->src.x1 >> 16;
	पूर्णांक src_y1 = state->src.y1 >> 16;
	पूर्णांक src_x2 = (state->src.x2 >> 16) + !!(state->src.x2 & 0xFFFF);
	पूर्णांक src_y2 = (state->src.y2 >> 16) + !!(state->src.y2 & 0xFFFF);

	अगर (x1 >= x2 || y1 >= y2) अणु
		pr_err("Cannot have damage clip with no dimension.\n");
		वापस false;
	पूर्ण

	अगर (x1 < src_x1 || y1 < src_y1 || x2 > src_x2 || y2 > src_y2) अणु
		pr_err("Damage cannot be outside rounded plane src.\n");
		वापस false;
	पूर्ण

	अगर (r->x1 != x1 || r->y1 != y1 || r->x2 != x2 || r->y2 != y2) अणु
		pr_err("Damage = %d %d %d %d\n", r->x1, r->y1, r->x2, r->y2);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक igt_damage_iter_no_damage(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	/* Plane src same as fb size. */
	set_plane_src(&old_state, 0, 0, fb.width << 16, fb.height << 16);
	set_plane_src(&state, 0, 0, fb.width << 16, fb.height << 16);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return plane src as damage.");
	FAIL_ON(!check_damage_clip(&state, &clip, 0, 0, 2048, 2048));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_no_damage_fractional_src(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	/* Plane src has fractional part. */
	set_plane_src(&old_state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	set_plane_src(&state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return rounded off plane src as damage.");
	FAIL_ON(!check_damage_clip(&state, &clip, 3, 3, 1028, 772));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_no_damage_src_moved(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	/* Plane src moved since old plane state. */
	set_plane_src(&old_state, 0, 0, 1024 << 16, 768 << 16);
	set_plane_src(&state, 10 << 16, 10 << 16,
		      (10 + 1024) << 16, (10 + 768) << 16);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return plane src as damage.");
	FAIL_ON(!check_damage_clip(&state, &clip, 10, 10, 1034, 778));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_no_damage_fractional_src_moved(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	/* Plane src has fractional part and it moved since old plane state. */
	set_plane_src(&old_state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	set_plane_src(&state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return plane src as damage.");
	FAIL_ON(!check_damage_clip(&state, &clip, 4, 4, 1029, 773));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_no_damage_not_visible(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = false,
	पूर्ण;

	set_plane_src(&old_state, 0, 0, 1024 << 16, 768 << 16);
	set_plane_src(&state, 0, 0, 1024 << 16, 768 << 16);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 0, "Should have no damage.");

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_no_damage_no_crtc(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = 0,
		.fb = &fb,
	पूर्ण;

	set_plane_src(&old_state, 0, 0, 1024 << 16, 768 << 16);
	set_plane_src(&state, 0, 0, 1024 << 16, 768 << 16);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 0, "Should have no damage.");

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_no_damage_no_fb(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = 0,
	पूर्ण;

	set_plane_src(&old_state, 0, 0, 1024 << 16, 768 << 16);
	set_plane_src(&state, 0, 0, 1024 << 16, 768 << 16);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 0, "Should have no damage.");

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_simple_damage(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	set_plane_src(&old_state, 0, 0, 1024 << 16, 768 << 16);
	set_plane_src(&state, 0, 0, 1024 << 16, 768 << 16);
	/* Damage set to plane src */
	set_damage_clip(&damage, 0, 0, 1024, 768);
	set_damage_blob(&damage_blob, &damage, माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return damage when set.");
	FAIL_ON(!check_damage_clip(&state, &clip, 0, 0, 1024, 768));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_single_damage(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	set_plane_src(&old_state, 0, 0, 1024 << 16, 768 << 16);
	set_plane_src(&state, 0, 0, 1024 << 16, 768 << 16);
	set_damage_clip(&damage, 256, 192, 768, 576);
	set_damage_blob(&damage_blob, &damage, माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return damage when set.");
	FAIL_ON(!check_damage_clip(&state, &clip, 256, 192, 768, 576));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_single_damage_पूर्णांकersect_src(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	set_plane_src(&old_state, 0, 0, 1024 << 16, 768 << 16);
	set_plane_src(&state, 0, 0, 1024 << 16, 768 << 16);
	/* Damage पूर्णांकersect with plane src. */
	set_damage_clip(&damage, 256, 192, 1360, 768);
	set_damage_blob(&damage_blob, &damage, माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return damage clipped to src.");
	FAIL_ON(!check_damage_clip(&state, &clip, 256, 192, 1024, 768));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_single_damage_outside_src(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	set_plane_src(&old_state, 0, 0, 1024 << 16, 768 << 16);
	set_plane_src(&state, 0, 0, 1024 << 16, 768 << 16);
	/* Damage clip outside plane src */
	set_damage_clip(&damage, 1360, 1360, 1380, 1380);
	set_damage_blob(&damage_blob, &damage, माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 0, "Should have no damage.");

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_single_damage_fractional_src(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	/* Plane src has fractional part. */
	set_plane_src(&old_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_plane_src(&state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_damage_clip(&damage, 10, 10, 256, 330);
	set_damage_blob(&damage_blob, &damage, माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return damage when set.");
	FAIL_ON(!check_damage_clip(&state, &clip, 10, 10, 256, 330));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_single_damage_पूर्णांकersect_fractional_src(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	/* Plane src has fractional part. */
	set_plane_src(&old_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_plane_src(&state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	/* Damage पूर्णांकersect with plane src. */
	set_damage_clip(&damage, 10, 1, 1360, 330);
	set_damage_blob(&damage_blob, &damage, माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return damage clipped to rounded off src.");
	FAIL_ON(!check_damage_clip(&state, &clip, 10, 4, 1029, 330));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_single_damage_outside_fractional_src(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	/* Plane src has fractional part. */
	set_plane_src(&old_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_plane_src(&state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	/* Damage clip outside plane src */
	set_damage_clip(&damage, 1360, 1360, 1380, 1380);
	set_damage_blob(&damage_blob, &damage, माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 0, "Should have no damage.");

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_single_damage_src_moved(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	/* Plane src moved since old plane state. */
	set_plane_src(&old_state, 0, 0, 1024 << 16, 768 << 16);
	set_plane_src(&state, 10 << 16, 10 << 16,
		      (10 + 1024) << 16, (10 + 768) << 16);
	set_damage_clip(&damage, 20, 30, 256, 256);
	set_damage_blob(&damage_blob, &damage, माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return plane src as damage.");
	FAIL_ON(!check_damage_clip(&state, &clip, 10, 10, 1034, 778));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_single_damage_fractional_src_moved(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	/* Plane src with fractional part moved since old plane state. */
	set_plane_src(&old_state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	set_plane_src(&state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	/* Damage पूर्णांकersect with plane src. */
	set_damage_clip(&damage, 20, 30, 1360, 256);
	set_damage_blob(&damage_blob, &damage, माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return rounded off plane src as damage.");
	FAIL_ON(!check_damage_clip(&state, &clip, 4, 4, 1029, 773));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_damage(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage[2];
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	set_plane_src(&old_state, 0, 0, 1024 << 16, 768 << 16);
	set_plane_src(&state, 0, 0, 1024 << 16, 768 << 16);
	/* 2 damage clips. */
	set_damage_clip(&damage[0], 20, 30, 200, 180);
	set_damage_clip(&damage[1], 240, 200, 280, 250);
	set_damage_blob(&damage_blob, &damage[0], माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip) अणु
		अगर (num_hits == 0)
			FAIL_ON(!check_damage_clip(&state, &clip, 20, 30, 200, 180));
		अगर (num_hits == 1)
			FAIL_ON(!check_damage_clip(&state, &clip, 240, 200, 280, 250));
		num_hits++;
	पूर्ण

	FAIL(num_hits != 2, "Should return damage when set.");

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_damage_one_पूर्णांकersect(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage[2];
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	set_plane_src(&old_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_plane_src(&state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	/* 2 damage clips, one पूर्णांकersect plane src. */
	set_damage_clip(&damage[0], 20, 30, 200, 180);
	set_damage_clip(&damage[1], 2, 2, 1360, 1360);
	set_damage_blob(&damage_blob, &damage[0], माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip) अणु
		अगर (num_hits == 0)
			FAIL_ON(!check_damage_clip(&state, &clip, 20, 30, 200, 180));
		अगर (num_hits == 1)
			FAIL_ON(!check_damage_clip(&state, &clip, 4, 4, 1029, 773));
		num_hits++;
	पूर्ण

	FAIL(num_hits != 2, "Should return damage when set.");

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_damage_one_outside(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage[2];
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	set_plane_src(&old_state, 0, 0, 1024 << 16, 768 << 16);
	set_plane_src(&state, 0, 0, 1024 << 16, 768 << 16);
	/* 2 damage clips, one outside plane src. */
	set_damage_clip(&damage[0], 1360, 1360, 1380, 1380);
	set_damage_clip(&damage[1], 240, 200, 280, 250);
	set_damage_blob(&damage_blob, &damage[0], माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return damage when set.");
	FAIL_ON(!check_damage_clip(&state, &clip, 240, 200, 280, 250));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_damage_src_moved(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage[2];
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = true,
	पूर्ण;

	set_plane_src(&old_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_plane_src(&state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	/* 2 damage clips, one outside plane src. */
	set_damage_clip(&damage[0], 1360, 1360, 1380, 1380);
	set_damage_clip(&damage[1], 240, 200, 280, 250);
	set_damage_blob(&damage_blob, &damage[0], माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 1, "Should return round off plane src as damage.");
	FAIL_ON(!check_damage_clip(&state, &clip, 3, 3, 1028, 772));

	वापस 0;
पूर्ण

पूर्णांक igt_damage_iter_damage_not_visible(व्योम *ignored)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_plane_state old_state;
	काष्ठा drm_property_blob damage_blob;
	काष्ठा drm_mode_rect damage[2];
	काष्ठा drm_rect clip;
	uपूर्णांक32_t num_hits = 0;

	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;

	काष्ठा drm_plane_state state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.visible = false,
	पूर्ण;

	set_plane_src(&old_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_plane_src(&state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	/* 2 damage clips, one outside plane src. */
	set_damage_clip(&damage[0], 1360, 1360, 1380, 1380);
	set_damage_clip(&damage[1], 240, 200, 280, 250);
	set_damage_blob(&damage_blob, &damage[0], माप(damage));
	set_plane_damage(&state, &damage_blob);
	drm_atomic_helper_damage_iter_init(&iter, &old_state, &state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	FAIL(num_hits != 0, "Should not return any damage.");

	वापस 0;
पूर्ण
