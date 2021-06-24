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

#अगर_अघोषित _GVT_EDID_H_
#घोषणा _GVT_EDID_H_

#समावेश <linux/types.h>

काष्ठा पूर्णांकel_vgpu;

#घोषणा EDID_SIZE		128
#घोषणा EDID_ADDR		0x50 /* Linux hvm EDID addr */

#घोषणा GVT_AUX_NATIVE_WRITE			0x8
#घोषणा GVT_AUX_NATIVE_READ			0x9
#घोषणा GVT_AUX_I2C_WRITE			0x0
#घोषणा GVT_AUX_I2C_READ			0x1
#घोषणा GVT_AUX_I2C_STATUS			0x2
#घोषणा GVT_AUX_I2C_MOT				0x4
#घोषणा GVT_AUX_I2C_REPLY_ACK			0x0

काष्ठा पूर्णांकel_vgpu_edid_data अणु
	bool data_valid;
	अचिन्हित अक्षर edid_block[EDID_SIZE];
पूर्ण;

क्रमागत gmbus_cycle_type अणु
	GMBUS_NOCYCLE	= 0x0,
	NIDX_NS_W	= 0x1,
	IDX_NS_W	= 0x3,
	GMBUS_STOP	= 0x4,
	NIDX_STOP	= 0x5,
	IDX_STOP	= 0x7
पूर्ण;

/*
 * States of GMBUS
 *
 * GMBUS0-3 could be related to the EDID भवization. Another two GMBUS
 * रेजिस्टरs, GMBUS4 (पूर्णांकerrupt mask) and GMBUS5 (2 byte indes रेजिस्टर), are
 * not considered here. Below describes the usage of GMBUS रेजिस्टरs that are
 * cared by the EDID भवization
 *
 * GMBUS0:
 *      R/W
 *      port selection. value of bit0 - bit2 corresponds to the GPIO रेजिस्टरs.
 *
 * GMBUS1:
 *      R/W Protect
 *      Command and Status.
 *      bit0 is the direction bit: 1 is पढ़ो; 0 is ग_लिखो.
 *      bit1 - bit7 is slave 7-bit address.
 *      bit16 - bit24 total byte count (ignore?)
 *
 * GMBUS2:
 *      Most of bits are पढ़ो only except bit 15 (IN_USE)
 *      Status रेजिस्टर
 *      bit0 - bit8 current byte count
 *      bit 11: hardware पढ़ोy;
 *
 * GMBUS3:
 *      Read/Write
 *      Data क्रम transfer
 */

/* From hw specs, Other phases like START, ADDRESS, INDEX
 * are invisible to GMBUS MMIO पूर्णांकerface. So no definitions
 * in below क्रमागत types
 */
क्रमागत gvt_gmbus_phase अणु
	GMBUS_IDLE_PHASE = 0,
	GMBUS_DATA_PHASE,
	GMBUS_WAIT_PHASE,
	//GMBUS_STOP_PHASE,
	GMBUS_MAX_PHASE
पूर्ण;

काष्ठा पूर्णांकel_vgpu_i2c_gmbus अणु
	अचिन्हित पूर्णांक total_byte_count; /* from GMBUS1 */
	क्रमागत gmbus_cycle_type cycle_type;
	क्रमागत gvt_gmbus_phase phase;
पूर्ण;

काष्ठा पूर्णांकel_vgpu_i2c_aux_ch अणु
	bool i2c_over_aux_ch;
	bool aux_ch_mot;
पूर्ण;

क्रमागत i2c_state अणु
	I2C_NOT_SPECIFIED = 0,
	I2C_GMBUS = 1,
	I2C_AUX_CH = 2
पूर्ण;

/* I2C sequences cannot पूर्णांकerleave.
 * GMBUS and AUX_CH sequences cannot पूर्णांकerleave.
 */
काष्ठा पूर्णांकel_vgpu_i2c_edid अणु
	क्रमागत i2c_state state;

	अचिन्हित पूर्णांक port;
	bool slave_selected;
	bool edid_available;
	अचिन्हित पूर्णांक current_edid_पढ़ो;

	काष्ठा पूर्णांकel_vgpu_i2c_gmbus gmbus;
	काष्ठा पूर्णांकel_vgpu_i2c_aux_ch aux_ch;
पूर्ण;

व्योम पूर्णांकel_vgpu_init_i2c_edid(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_gvt_i2c_handle_gmbus_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes);

पूर्णांक पूर्णांकel_gvt_i2c_handle_gmbus_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes);

व्योम पूर्णांकel_gvt_i2c_handle_aux_ch_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		पूर्णांक port_idx,
		अचिन्हित पूर्णांक offset,
		व्योम *p_data);

#पूर्ण_अगर /*_GVT_EDID_H_*/
