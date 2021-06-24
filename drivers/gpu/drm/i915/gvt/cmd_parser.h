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
 *    Ke Yu
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *    Zhiyuan Lv <zhiyuan.lv@पूर्णांकel.com>
 *
 * Contributors:
 *    Min He <min.he@पूर्णांकel.com>
 *    Ping Gao <ping.a.gao@पूर्णांकel.com>
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *    Yulei Zhang <yulei.zhang@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */
#अगर_अघोषित _GVT_CMD_PARSER_H_
#घोषणा _GVT_CMD_PARSER_H_

#घोषणा GVT_CMD_HASH_BITS 7

काष्ठा पूर्णांकel_gvt;
काष्ठा पूर्णांकel_shaकरोw_wa_ctx;
काष्ठा पूर्णांकel_vgpu;
काष्ठा पूर्णांकel_vgpu_workload;

व्योम पूर्णांकel_gvt_clean_cmd_parser(काष्ठा पूर्णांकel_gvt *gvt);

पूर्णांक पूर्णांकel_gvt_init_cmd_parser(काष्ठा पूर्णांकel_gvt *gvt);

पूर्णांक पूर्णांकel_gvt_scan_and_shaकरोw_ringbuffer(काष्ठा पूर्णांकel_vgpu_workload *workload);

पूर्णांक पूर्णांकel_gvt_scan_and_shaकरोw_wa_ctx(काष्ठा पूर्णांकel_shaकरोw_wa_ctx *wa_ctx);

व्योम पूर्णांकel_gvt_update_reg_whitelist(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_gvt_scan_engine_context(काष्ठा पूर्णांकel_vgpu_workload *workload);

#पूर्ण_अगर
