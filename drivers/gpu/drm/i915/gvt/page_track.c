<शैली गुरु>
/*
 * Copyright(c) 2011-2017 Intel Corporation. All rights reserved.
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
 */
#समावेश "i915_drv.h"
#समावेश "gvt.h"

/**
 * पूर्णांकel_vgpu_find_page_track - find page track rcord of guest page
 * @vgpu: a vGPU
 * @gfn: the gfn of guest page
 *
 * Returns:
 * A poपूर्णांकer to काष्ठा पूर्णांकel_vgpu_page_track अगर found, अन्यथा शून्य वापसed.
 */
काष्ठा पूर्णांकel_vgpu_page_track *पूर्णांकel_vgpu_find_page_track(
		काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn)
अणु
	वापस radix_tree_lookup(&vgpu->page_track_tree, gfn);
पूर्ण

/**
 * पूर्णांकel_vgpu_रेजिस्टर_page_track - रेजिस्टर a guest page to be tacked
 * @vgpu: a vGPU
 * @gfn: the gfn of guest page
 * @handler: page track handler
 * @priv: tracker निजी
 *
 * Returns:
 * zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_रेजिस्टर_page_track(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn,
		gvt_page_track_handler_t handler, व्योम *priv)
अणु
	काष्ठा पूर्णांकel_vgpu_page_track *track;
	पूर्णांक ret;

	track = पूर्णांकel_vgpu_find_page_track(vgpu, gfn);
	अगर (track)
		वापस -EEXIST;

	track = kzalloc(माप(*track), GFP_KERNEL);
	अगर (!track)
		वापस -ENOMEM;

	track->handler = handler;
	track->priv_data = priv;

	ret = radix_tree_insert(&vgpu->page_track_tree, gfn, track);
	अगर (ret) अणु
		kमुक्त(track);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_unरेजिस्टर_page_track - unरेजिस्टर the tracked guest page
 * @vgpu: a vGPU
 * @gfn: the gfn of guest page
 *
 */
व्योम पूर्णांकel_vgpu_unरेजिस्टर_page_track(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित दीर्घ gfn)
अणु
	काष्ठा पूर्णांकel_vgpu_page_track *track;

	track = radix_tree_delete(&vgpu->page_track_tree, gfn);
	अगर (track) अणु
		अगर (track->tracked)
			पूर्णांकel_gvt_hypervisor_disable_page_track(vgpu, gfn);
		kमुक्त(track);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_vgpu_enable_page_track - set ग_लिखो-protection on guest page
 * @vgpu: a vGPU
 * @gfn: the gfn of guest page
 *
 * Returns:
 * zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_enable_page_track(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn)
अणु
	काष्ठा पूर्णांकel_vgpu_page_track *track;
	पूर्णांक ret;

	track = पूर्णांकel_vgpu_find_page_track(vgpu, gfn);
	अगर (!track)
		वापस -ENXIO;

	अगर (track->tracked)
		वापस 0;

	ret = पूर्णांकel_gvt_hypervisor_enable_page_track(vgpu, gfn);
	अगर (ret)
		वापस ret;
	track->tracked = true;
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_enable_page_track - cancel ग_लिखो-protection on guest page
 * @vgpu: a vGPU
 * @gfn: the gfn of guest page
 *
 * Returns:
 * zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_disable_page_track(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn)
अणु
	काष्ठा पूर्णांकel_vgpu_page_track *track;
	पूर्णांक ret;

	track = पूर्णांकel_vgpu_find_page_track(vgpu, gfn);
	अगर (!track)
		वापस -ENXIO;

	अगर (!track->tracked)
		वापस 0;

	ret = पूर्णांकel_gvt_hypervisor_disable_page_track(vgpu, gfn);
	अगर (ret)
		वापस ret;
	track->tracked = false;
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_page_track_handler - called when ग_लिखो to ग_लिखो-रक्षित page
 * @vgpu: a vGPU
 * @gpa: the gpa of this ग_लिखो
 * @data: the ग_लिखोd data
 * @bytes: the length of this ग_लिखो
 *
 * Returns:
 * zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_page_track_handler(काष्ठा पूर्णांकel_vgpu *vgpu, u64 gpa,
		व्योम *data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_vgpu_page_track *page_track;
	पूर्णांक ret = 0;

	mutex_lock(&vgpu->vgpu_lock);

	page_track = पूर्णांकel_vgpu_find_page_track(vgpu, gpa >> PAGE_SHIFT);
	अगर (!page_track) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	अगर (unlikely(vgpu->failsafe)) अणु
		/* Remove ग_लिखो protection to prevent furture traps. */
		पूर्णांकel_vgpu_disable_page_track(vgpu, gpa >> PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		ret = page_track->handler(page_track, gpa, data, bytes);
		अगर (ret)
			gvt_err("guest page write error, gpa %llx\n", gpa);
	पूर्ण

out:
	mutex_unlock(&vgpu->vgpu_lock);
	वापस ret;
पूर्ण
