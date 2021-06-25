<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
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
 * Authors:
 *    Anhua Xu
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *
 * Contributors:
 *    Min He <min.he@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#अगर_अघोषित __GVT_SCHED_POLICY__
#घोषणा __GVT_SCHED_POLICY__

काष्ठा पूर्णांकel_gvt;
काष्ठा पूर्णांकel_vgpu;

काष्ठा पूर्णांकel_gvt_sched_policy_ops अणु
	पूर्णांक (*init)(काष्ठा पूर्णांकel_gvt *gvt);
	व्योम (*clean)(काष्ठा पूर्णांकel_gvt *gvt);
	पूर्णांक (*init_vgpu)(काष्ठा पूर्णांकel_vgpu *vgpu);
	व्योम (*clean_vgpu)(काष्ठा पूर्णांकel_vgpu *vgpu);
	व्योम (*start_schedule)(काष्ठा पूर्णांकel_vgpu *vgpu);
	व्योम (*stop_schedule)(काष्ठा पूर्णांकel_vgpu *vgpu);
पूर्ण;

व्योम पूर्णांकel_gvt_schedule(काष्ठा पूर्णांकel_gvt *gvt);

पूर्णांक पूर्णांकel_gvt_init_sched_policy(काष्ठा पूर्णांकel_gvt *gvt);

व्योम पूर्णांकel_gvt_clean_sched_policy(काष्ठा पूर्णांकel_gvt *gvt);

पूर्णांक पूर्णांकel_vgpu_init_sched_policy(काष्ठा पूर्णांकel_vgpu *vgpu);

व्योम पूर्णांकel_vgpu_clean_sched_policy(काष्ठा पूर्णांकel_vgpu *vgpu);

व्योम पूर्णांकel_vgpu_start_schedule(काष्ठा पूर्णांकel_vgpu *vgpu);

व्योम पूर्णांकel_vgpu_stop_schedule(काष्ठा पूर्णांकel_vgpu *vgpu);

व्योम पूर्णांकel_gvt_kick_schedule(काष्ठा पूर्णांकel_gvt *gvt);

#पूर्ण_अगर
