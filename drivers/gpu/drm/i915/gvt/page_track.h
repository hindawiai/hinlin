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
 *
 */

#अगर_अघोषित _GVT_PAGE_TRACK_H_
#घोषणा _GVT_PAGE_TRACK_H_

#समावेश <linux/types.h>

काष्ठा पूर्णांकel_vgpu;
काष्ठा पूर्णांकel_vgpu_page_track;

प्रकार पूर्णांक (*gvt_page_track_handler_t)(
			काष्ठा पूर्णांकel_vgpu_page_track *page_track,
			u64 gpa, व्योम *data, पूर्णांक bytes);

/* Track record क्रम a ग_लिखो-रक्षित guest page. */
काष्ठा पूर्णांकel_vgpu_page_track अणु
	gvt_page_track_handler_t handler;
	bool tracked;
	व्योम *priv_data;
पूर्ण;

काष्ठा पूर्णांकel_vgpu_page_track *पूर्णांकel_vgpu_find_page_track(
		काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn);

पूर्णांक पूर्णांकel_vgpu_रेजिस्टर_page_track(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित दीर्घ gfn, gvt_page_track_handler_t handler,
		व्योम *priv);
व्योम पूर्णांकel_vgpu_unरेजिस्टर_page_track(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित दीर्घ gfn);

पूर्णांक पूर्णांकel_vgpu_enable_page_track(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn);
पूर्णांक पूर्णांकel_vgpu_disable_page_track(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn);

पूर्णांक पूर्णांकel_vgpu_page_track_handler(काष्ठा पूर्णांकel_vgpu *vgpu, u64 gpa,
		व्योम *data, अचिन्हित पूर्णांक bytes);

#पूर्ण_अगर
