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
 *    Zhiyuan Lv <zhiyuan.lv@पूर्णांकel.com>
 *
 * Contributors:
 *    Terrence Xu <terrence.xu@पूर्णांकel.com>
 *    Changbin Du <changbin.du@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#अगर_अघोषित _GVT_DISPLAY_H_
#घोषणा _GVT_DISPLAY_H_

#समावेश <linux/types.h>
#समावेश <linux/hrसमयr.h>

काष्ठा पूर्णांकel_gvt;
काष्ठा पूर्णांकel_vgpu;

#घोषणा SBI_REG_MAX	20
#घोषणा DPCD_SIZE	0x700

#घोषणा पूर्णांकel_vgpu_port(vgpu, port) \
	(&(vgpu->display.ports[port]))

#घोषणा पूर्णांकel_vgpu_has_monitor_on_port(vgpu, port) \
	(पूर्णांकel_vgpu_port(vgpu, port)->edid && \
		पूर्णांकel_vgpu_port(vgpu, port)->edid->data_valid)

#घोषणा पूर्णांकel_vgpu_port_is_dp(vgpu, port) \
	((पूर्णांकel_vgpu_port(vgpu, port)->type == GVT_DP_A) || \
	(पूर्णांकel_vgpu_port(vgpu, port)->type == GVT_DP_B) || \
	(पूर्णांकel_vgpu_port(vgpu, port)->type == GVT_DP_C) || \
	(पूर्णांकel_vgpu_port(vgpu, port)->type == GVT_DP_D))

#घोषणा INTEL_GVT_MAX_UEVENT_VARS	3

/* DPCD start */
#घोषणा DPCD_SIZE	0x700

/* DPCD */
#घोषणा DP_SET_POWER            0x600
#घोषणा DP_SET_POWER_D0         0x1
#घोषणा AUX_NATIVE_WRITE        0x8
#घोषणा AUX_NATIVE_READ         0x9

#घोषणा AUX_NATIVE_REPLY_MASK   (0x3 << 4)
#घोषणा AUX_NATIVE_REPLY_ACK    (0x0 << 4)
#घोषणा AUX_NATIVE_REPLY_NAK    (0x1 << 4)
#घोषणा AUX_NATIVE_REPLY_DEFER  (0x2 << 4)

#घोषणा AUX_BURST_SIZE          20

/* DPCD addresses */
#घोषणा DPCD_REV			0x000
#घोषणा DPCD_MAX_LINK_RATE		0x001
#घोषणा DPCD_MAX_LANE_COUNT		0x002

#घोषणा DPCD_TRAINING_PATTERN_SET	0x102
#घोषणा	DPCD_SINK_COUNT			0x200
#घोषणा DPCD_LANE0_1_STATUS		0x202
#घोषणा DPCD_LANE2_3_STATUS		0x203
#घोषणा DPCD_LANE_ALIGN_STATUS_UPDATED	0x204
#घोषणा DPCD_SINK_STATUS		0x205

/* link training */
#घोषणा DPCD_TRAINING_PATTERN_SET_MASK	0x03
#घोषणा DPCD_LINK_TRAINING_DISABLED	0x00
#घोषणा DPCD_TRAINING_PATTERN_1		0x01
#घोषणा DPCD_TRAINING_PATTERN_2		0x02

#घोषणा DPCD_CP_READY_MASK		(1 << 6)

/* lane status */
#घोषणा DPCD_LANES_CR_DONE		0x11
#घोषणा DPCD_LANES_EQ_DONE		0x22
#घोषणा DPCD_SYMBOL_LOCKED		0x44

#घोषणा DPCD_INTERLANE_ALIGN_DONE	0x01

#घोषणा DPCD_SINK_IN_SYNC		0x03
/* DPCD end */

#घोषणा SBI_RESPONSE_MASK               0x3
#घोषणा SBI_RESPONSE_SHIFT              0x1
#घोषणा SBI_STAT_MASK                   0x1
#घोषणा SBI_STAT_SHIFT                  0x0
#घोषणा SBI_OPCODE_SHIFT                8
#घोषणा SBI_OPCODE_MASK			(0xff << SBI_OPCODE_SHIFT)
#घोषणा SBI_CMD_IORD                    2
#घोषणा SBI_CMD_IOWR                    3
#घोषणा SBI_CMD_CRRD                    6
#घोषणा SBI_CMD_CRWR                    7
#घोषणा SBI_ADDR_OFFSET_SHIFT           16
#घोषणा SBI_ADDR_OFFSET_MASK            (0xffff << SBI_ADDR_OFFSET_SHIFT)

काष्ठा पूर्णांकel_vgpu_sbi_रेजिस्टर अणु
	अचिन्हित पूर्णांक offset;
	u32 value;
पूर्ण;

काष्ठा पूर्णांकel_vgpu_sbi अणु
	पूर्णांक number;
	काष्ठा पूर्णांकel_vgpu_sbi_रेजिस्टर रेजिस्टरs[SBI_REG_MAX];
पूर्ण;

क्रमागत पूर्णांकel_gvt_plane_type अणु
	PRIMARY_PLANE = 0,
	CURSOR_PLANE,
	SPRITE_PLANE,
	MAX_PLANE
पूर्ण;

काष्ठा पूर्णांकel_vgpu_dpcd_data अणु
	bool data_valid;
	u8 data[DPCD_SIZE];
पूर्ण;

क्रमागत पूर्णांकel_vgpu_port_type अणु
	GVT_CRT = 0,
	GVT_DP_A,
	GVT_DP_B,
	GVT_DP_C,
	GVT_DP_D,
	GVT_HDMI_B,
	GVT_HDMI_C,
	GVT_HDMI_D,
	GVT_PORT_MAX
पूर्ण;

क्रमागत पूर्णांकel_vgpu_edid अणु
	GVT_EDID_1024_768,
	GVT_EDID_1920_1200,
	GVT_EDID_NUM,
पूर्ण;

#घोषणा GVT_DEFAULT_REFRESH_RATE 60
काष्ठा पूर्णांकel_vgpu_port अणु
	/* per display EDID inक्रमmation */
	काष्ठा पूर्णांकel_vgpu_edid_data *edid;
	/* per display DPCD inक्रमmation */
	काष्ठा पूर्णांकel_vgpu_dpcd_data *dpcd;
	पूर्णांक type;
	क्रमागत पूर्णांकel_vgpu_edid id;
	/* x1000 to get accurate 59.94, 24.976, 29.94, etc. in timing std. */
	u32 vrefresh_k;
पूर्ण;

काष्ठा पूर्णांकel_vgpu_vblank_समयr अणु
	काष्ठा hrसमयr समयr;
	u32 vrefresh_k;
	u64 period;
पूर्ण;

अटल अंतरभूत अक्षर *vgpu_edid_str(क्रमागत पूर्णांकel_vgpu_edid id)
अणु
	चयन (id) अणु
	हाल GVT_EDID_1024_768:
		वापस "1024x768";
	हाल GVT_EDID_1920_1200:
		वापस "1920x1200";
	शेष:
		वापस "";
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक vgpu_edid_xres(क्रमागत पूर्णांकel_vgpu_edid id)
अणु
	चयन (id) अणु
	हाल GVT_EDID_1024_768:
		वापस 1024;
	हाल GVT_EDID_1920_1200:
		वापस 1920;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक vgpu_edid_yres(क्रमागत पूर्णांकel_vgpu_edid id)
अणु
	चयन (id) अणु
	हाल GVT_EDID_1024_768:
		वापस 768;
	हाल GVT_EDID_1920_1200:
		वापस 1200;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

व्योम पूर्णांकel_vgpu_emulate_vblank(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम vgpu_update_vblank_emulation(काष्ठा पूर्णांकel_vgpu *vgpu, bool turnon);

पूर्णांक पूर्णांकel_vgpu_init_display(काष्ठा पूर्णांकel_vgpu *vgpu, u64 resolution);
व्योम पूर्णांकel_vgpu_reset_display(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_vgpu_clean_display(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक pipe_is_enabled(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक pipe);

#पूर्ण_अगर
