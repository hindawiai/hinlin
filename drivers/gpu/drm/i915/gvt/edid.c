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

#समावेश "i915_drv.h"
#समावेश "gvt.h"

#घोषणा GMBUS1_TOTAL_BYTES_SHIFT 16
#घोषणा GMBUS1_TOTAL_BYTES_MASK 0x1ff
#घोषणा gmbus1_total_byte_count(v) (((v) >> \
	GMBUS1_TOTAL_BYTES_SHIFT) & GMBUS1_TOTAL_BYTES_MASK)
#घोषणा gmbus1_slave_addr(v) (((v) & 0xff) >> 1)
#घोषणा gmbus1_slave_index(v) (((v) >> 8) & 0xff)
#घोषणा gmbus1_bus_cycle(v) (((v) >> 25) & 0x7)

/* GMBUS0 bits definitions */
#घोषणा _GMBUS_PIN_SEL_MASK     (0x7)

अटल अचिन्हित अक्षर edid_get_byte(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_vgpu_i2c_edid *edid = &vgpu->display.i2c_edid;
	अचिन्हित अक्षर chr = 0;

	अगर (edid->state == I2C_NOT_SPECIFIED || !edid->slave_selected) अणु
		gvt_vgpu_err("Driver tries to read EDID without proper sequence!\n");
		वापस 0;
	पूर्ण
	अगर (edid->current_edid_पढ़ो >= EDID_SIZE) अणु
		gvt_vgpu_err("edid_get_byte() exceeds the size of EDID!\n");
		वापस 0;
	पूर्ण

	अगर (!edid->edid_available) अणु
		gvt_vgpu_err("Reading EDID but EDID is not available!\n");
		वापस 0;
	पूर्ण

	अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, edid->port)) अणु
		काष्ठा पूर्णांकel_vgpu_edid_data *edid_data =
			पूर्णांकel_vgpu_port(vgpu, edid->port)->edid;

		chr = edid_data->edid_block[edid->current_edid_पढ़ो];
		edid->current_edid_पढ़ो++;
	पूर्ण अन्यथा अणु
		gvt_vgpu_err("No EDID available during the reading?\n");
	पूर्ण
	वापस chr;
पूर्ण

अटल अंतरभूत पूर्णांक cnp_get_port_from_gmbus0(u32 gmbus0)
अणु
	पूर्णांक port_select = gmbus0 & _GMBUS_PIN_SEL_MASK;
	पूर्णांक port = -EINVAL;

	अगर (port_select == GMBUS_PIN_1_BXT)
		port = PORT_B;
	अन्यथा अगर (port_select == GMBUS_PIN_2_BXT)
		port = PORT_C;
	अन्यथा अगर (port_select == GMBUS_PIN_3_BXT)
		port = PORT_D;
	अन्यथा अगर (port_select == GMBUS_PIN_4_CNP)
		port = PORT_E;
	वापस port;
पूर्ण

अटल अंतरभूत पूर्णांक bxt_get_port_from_gmbus0(u32 gmbus0)
अणु
	पूर्णांक port_select = gmbus0 & _GMBUS_PIN_SEL_MASK;
	पूर्णांक port = -EINVAL;

	अगर (port_select == GMBUS_PIN_1_BXT)
		port = PORT_B;
	अन्यथा अगर (port_select == GMBUS_PIN_2_BXT)
		port = PORT_C;
	अन्यथा अगर (port_select == GMBUS_PIN_3_BXT)
		port = PORT_D;
	वापस port;
पूर्ण

अटल अंतरभूत पूर्णांक get_port_from_gmbus0(u32 gmbus0)
अणु
	पूर्णांक port_select = gmbus0 & _GMBUS_PIN_SEL_MASK;
	पूर्णांक port = -EINVAL;

	अगर (port_select == GMBUS_PIN_VGADDC)
		port = PORT_E;
	अन्यथा अगर (port_select == GMBUS_PIN_DPC)
		port = PORT_C;
	अन्यथा अगर (port_select == GMBUS_PIN_DPB)
		port = PORT_B;
	अन्यथा अगर (port_select == GMBUS_PIN_DPD)
		port = PORT_D;
	वापस port;
पूर्ण

अटल व्योम reset_gmbus_controller(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	vgpu_vreg_t(vgpu, PCH_GMBUS2) = GMBUS_HW_RDY;
	अगर (!vgpu->display.i2c_edid.edid_available)
		vgpu_vreg_t(vgpu, PCH_GMBUS2) |= GMBUS_SATOER;
	vgpu->display.i2c_edid.gmbus.phase = GMBUS_IDLE_PHASE;
पूर्ण

/* GMBUS0 */
अटल पूर्णांक gmbus0_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
			अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	पूर्णांक port, pin_select;

	स_नकल(&vgpu_vreg(vgpu, offset), p_data, bytes);

	pin_select = vgpu_vreg(vgpu, offset) & _GMBUS_PIN_SEL_MASK;

	पूर्णांकel_vgpu_init_i2c_edid(vgpu);

	अगर (pin_select == 0)
		वापस 0;

	अगर (IS_BROXTON(i915))
		port = bxt_get_port_from_gmbus0(pin_select);
	अन्यथा अगर (IS_COFFEELAKE(i915) || IS_COMETLAKE(i915))
		port = cnp_get_port_from_gmbus0(pin_select);
	अन्यथा
		port = get_port_from_gmbus0(pin_select);
	अगर (drm_WARN_ON(&i915->drm, port < 0))
		वापस 0;

	vgpu->display.i2c_edid.state = I2C_GMBUS;
	vgpu->display.i2c_edid.gmbus.phase = GMBUS_IDLE_PHASE;

	vgpu_vreg_t(vgpu, PCH_GMBUS2) &= ~GMBUS_ACTIVE;
	vgpu_vreg_t(vgpu, PCH_GMBUS2) |= GMBUS_HW_RDY | GMBUS_HW_WAIT_PHASE;

	अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, port) &&
			!पूर्णांकel_vgpu_port_is_dp(vgpu, port)) अणु
		vgpu->display.i2c_edid.port = port;
		vgpu->display.i2c_edid.edid_available = true;
		vgpu_vreg_t(vgpu, PCH_GMBUS2) &= ~GMBUS_SATOER;
	पूर्ण अन्यथा
		vgpu_vreg_t(vgpu, PCH_GMBUS2) |= GMBUS_SATOER;
	वापस 0;
पूर्ण

अटल पूर्णांक gmbus1_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_vgpu_i2c_edid *i2c_edid = &vgpu->display.i2c_edid;
	u32 slave_addr;
	u32 wvalue = *(u32 *)p_data;

	अगर (vgpu_vreg(vgpu, offset) & GMBUS_SW_CLR_INT) अणु
		अगर (!(wvalue & GMBUS_SW_CLR_INT)) अणु
			vgpu_vreg(vgpu, offset) &= ~GMBUS_SW_CLR_INT;
			reset_gmbus_controller(vgpu);
		पूर्ण
		/*
		 * TODO: "This bit is cleared to zero when an event
		 * causes the HW_RDY bit transition to occur "
		 */
	पूर्ण अन्यथा अणु
		/*
		 * per bspec setting this bit can cause:
		 * 1) INT status bit cleared
		 * 2) HW_RDY bit निश्चितed
		 */
		अगर (wvalue & GMBUS_SW_CLR_INT) अणु
			vgpu_vreg_t(vgpu, PCH_GMBUS2) &= ~GMBUS_INT;
			vgpu_vreg_t(vgpu, PCH_GMBUS2) |= GMBUS_HW_RDY;
		पूर्ण

		/* For भवization, we suppose that HW is always पढ़ोy,
		 * so GMBUS_SW_RDY should always be cleared
		 */
		अगर (wvalue & GMBUS_SW_RDY)
			wvalue &= ~GMBUS_SW_RDY;

		i2c_edid->gmbus.total_byte_count =
			gmbus1_total_byte_count(wvalue);
		slave_addr = gmbus1_slave_addr(wvalue);

		/* vgpu gmbus only support EDID */
		अगर (slave_addr == EDID_ADDR) अणु
			i2c_edid->slave_selected = true;
		पूर्ण अन्यथा अगर (slave_addr != 0) अणु
			gvt_dbg_dpy(
				"vgpu%d: unsupported gmbus slave addr(0x%x)\n"
				"	gmbus operations will be ignored.\n",
					vgpu->id, slave_addr);
		पूर्ण

		अगर (wvalue & GMBUS_CYCLE_INDEX)
			i2c_edid->current_edid_पढ़ो =
				gmbus1_slave_index(wvalue);

		i2c_edid->gmbus.cycle_type = gmbus1_bus_cycle(wvalue);
		चयन (gmbus1_bus_cycle(wvalue)) अणु
		हाल GMBUS_NOCYCLE:
			अवरोध;
		हाल GMBUS_STOP:
			/* From spec:
			 * This can only cause a STOP to be generated
			 * अगर a GMBUS cycle is generated, the GMBUS is
			 * currently in a data/रुको/idle phase, or it is in a
			 * WAIT phase
			 */
			अगर (gmbus1_bus_cycle(vgpu_vreg(vgpu, offset))
				!= GMBUS_NOCYCLE) अणु
				पूर्णांकel_vgpu_init_i2c_edid(vgpu);
				/* After the 'stop' cycle, hw state would become
				 * 'stop phase' and then 'idle phase' after a
				 * few milliseconds. In emulation, we just set
				 * it as 'idle phase' ('stop phase' is not
				 * visible in gmbus पूर्णांकerface)
				 */
				i2c_edid->gmbus.phase = GMBUS_IDLE_PHASE;
				vgpu_vreg_t(vgpu, PCH_GMBUS2) &= ~GMBUS_ACTIVE;
			पूर्ण
			अवरोध;
		हाल NIDX_NS_W:
		हाल IDX_NS_W:
		हाल NIDX_STOP:
		हाल IDX_STOP:
			/* From hw spec the GMBUS phase
			 * transition like this:
			 * START (-->INDEX) -->DATA
			 */
			i2c_edid->gmbus.phase = GMBUS_DATA_PHASE;
			vgpu_vreg_t(vgpu, PCH_GMBUS2) |= GMBUS_ACTIVE;
			अवरोध;
		शेष:
			gvt_vgpu_err("Unknown/reserved GMBUS cycle detected!\n");
			अवरोध;
		पूर्ण
		/*
		 * From hw spec the WAIT state will be
		 * cleared:
		 * (1) in a new GMBUS cycle
		 * (2) by generating a stop
		 */
		vgpu_vreg(vgpu, offset) = wvalue;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gmbus3_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
	व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;

	drm_WARN_ON(&i915->drm, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक gmbus3_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर byte_data;
	काष्ठा पूर्णांकel_vgpu_i2c_edid *i2c_edid = &vgpu->display.i2c_edid;
	पूर्णांक byte_left = i2c_edid->gmbus.total_byte_count -
				i2c_edid->current_edid_पढ़ो;
	पूर्णांक byte_count = byte_left;
	u32 reg_data = 0;

	/* Data can only be recevied अगर previous settings correct */
	अगर (vgpu_vreg_t(vgpu, PCH_GMBUS1) & GMBUS_SLAVE_READ) अणु
		अगर (byte_left <= 0) अणु
			स_नकल(p_data, &vgpu_vreg(vgpu, offset), bytes);
			वापस 0;
		पूर्ण

		अगर (byte_count > 4)
			byte_count = 4;
		क्रम (i = 0; i < byte_count; i++) अणु
			byte_data = edid_get_byte(vgpu);
			reg_data |= (byte_data << (i << 3));
		पूर्ण

		स_नकल(&vgpu_vreg(vgpu, offset), &reg_data, byte_count);
		स_नकल(p_data, &vgpu_vreg(vgpu, offset), bytes);

		अगर (byte_left <= 4) अणु
			चयन (i2c_edid->gmbus.cycle_type) अणु
			हाल NIDX_STOP:
			हाल IDX_STOP:
				i2c_edid->gmbus.phase = GMBUS_IDLE_PHASE;
				अवरोध;
			हाल NIDX_NS_W:
			हाल IDX_NS_W:
			शेष:
				i2c_edid->gmbus.phase = GMBUS_WAIT_PHASE;
				अवरोध;
			पूर्ण
			पूर्णांकel_vgpu_init_i2c_edid(vgpu);
		पूर्ण
		/*
		 * Read GMBUS3 during send operation,
		 * वापस the latest written value
		 */
	पूर्ण अन्यथा अणु
		स_नकल(p_data, &vgpu_vreg(vgpu, offset), bytes);
		gvt_vgpu_err("warning: gmbus3 read with nothing returned\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gmbus2_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 value = vgpu_vreg(vgpu, offset);

	अगर (!(vgpu_vreg(vgpu, offset) & GMBUS_INUSE))
		vgpu_vreg(vgpu, offset) |= GMBUS_INUSE;
	स_नकल(p_data, (व्योम *)&value, bytes);
	वापस 0;
पूर्ण

अटल पूर्णांक gmbus2_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 wvalue = *(u32 *)p_data;

	अगर (wvalue & GMBUS_INUSE)
		vgpu_vreg(vgpu, offset) &= ~GMBUS_INUSE;
	/* All other bits are पढ़ो-only */
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_gvt_i2c_handle_gmbus_पढ़ो - emulate gmbus रेजिस्टर mmio पढ़ो
 * @vgpu: a vGPU
 * @offset: reg offset
 * @p_data: data वापस buffer
 * @bytes: access data length
 *
 * This function is used to emulate gmbus रेजिस्टर mmio पढ़ो
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_gvt_i2c_handle_gmbus_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;

	अगर (drm_WARN_ON(&i915->drm, bytes > 8 && (offset & (bytes - 1))))
		वापस -EINVAL;

	अगर (offset == i915_mmio_reg_offset(PCH_GMBUS2))
		वापस gmbus2_mmio_पढ़ो(vgpu, offset, p_data, bytes);
	अन्यथा अगर (offset == i915_mmio_reg_offset(PCH_GMBUS3))
		वापस gmbus3_mmio_पढ़ो(vgpu, offset, p_data, bytes);

	स_नकल(p_data, &vgpu_vreg(vgpu, offset), bytes);
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_gvt_i2c_handle_gmbus_ग_लिखो - emulate gmbus रेजिस्टर mmio ग_लिखो
 * @vgpu: a vGPU
 * @offset: reg offset
 * @p_data: data वापस buffer
 * @bytes: access data length
 *
 * This function is used to emulate gmbus रेजिस्टर mmio ग_लिखो
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_gvt_i2c_handle_gmbus_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;

	अगर (drm_WARN_ON(&i915->drm, bytes > 8 && (offset & (bytes - 1))))
		वापस -EINVAL;

	अगर (offset == i915_mmio_reg_offset(PCH_GMBUS0))
		वापस gmbus0_mmio_ग_लिखो(vgpu, offset, p_data, bytes);
	अन्यथा अगर (offset == i915_mmio_reg_offset(PCH_GMBUS1))
		वापस gmbus1_mmio_ग_लिखो(vgpu, offset, p_data, bytes);
	अन्यथा अगर (offset == i915_mmio_reg_offset(PCH_GMBUS2))
		वापस gmbus2_mmio_ग_लिखो(vgpu, offset, p_data, bytes);
	अन्यथा अगर (offset == i915_mmio_reg_offset(PCH_GMBUS3))
		वापस gmbus3_mmio_ग_लिखो(vgpu, offset, p_data, bytes);

	स_नकल(&vgpu_vreg(vgpu, offset), p_data, bytes);
	वापस 0;
पूर्ण

क्रमागत अणु
	AUX_CH_CTL = 0,
	AUX_CH_DATA1,
	AUX_CH_DATA2,
	AUX_CH_DATA3,
	AUX_CH_DATA4,
	AUX_CH_DATA5
पूर्ण;

अटल अंतरभूत पूर्णांक get_aux_ch_reg(अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक reg;

	चयन (offset & 0xff) अणु
	हाल 0x10:
		reg = AUX_CH_CTL;
		अवरोध;
	हाल 0x14:
		reg = AUX_CH_DATA1;
		अवरोध;
	हाल 0x18:
		reg = AUX_CH_DATA2;
		अवरोध;
	हाल 0x1c:
		reg = AUX_CH_DATA3;
		अवरोध;
	हाल 0x20:
		reg = AUX_CH_DATA4;
		अवरोध;
	हाल 0x24:
		reg = AUX_CH_DATA5;
		अवरोध;
	शेष:
		reg = -1;
		अवरोध;
	पूर्ण
	वापस reg;
पूर्ण

#घोषणा AUX_CTL_MSG_LENGTH(reg) \
	((reg & DP_AUX_CH_CTL_MESSAGE_SIZE_MASK) >> \
		DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT)

/**
 * पूर्णांकel_gvt_i2c_handle_aux_ch_ग_लिखो - emulate AUX channel रेजिस्टर ग_लिखो
 * @vgpu: a vGPU
 * @port_idx: port index
 * @offset: reg offset
 * @p_data: ग_लिखो ptr
 *
 * This function is used to emulate AUX channel रेजिस्टर ग_लिखो
 *
 */
व्योम पूर्णांकel_gvt_i2c_handle_aux_ch_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
				पूर्णांक port_idx,
				अचिन्हित पूर्णांक offset,
				व्योम *p_data)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_vgpu_i2c_edid *i2c_edid = &vgpu->display.i2c_edid;
	पूर्णांक msg_length, ret_msg_size;
	पूर्णांक msg, addr, ctrl, op;
	u32 value = *(u32 *)p_data;
	पूर्णांक aux_data_क्रम_ग_लिखो = 0;
	पूर्णांक reg = get_aux_ch_reg(offset);

	अगर (reg != AUX_CH_CTL) अणु
		vgpu_vreg(vgpu, offset) = value;
		वापस;
	पूर्ण

	msg_length = AUX_CTL_MSG_LENGTH(value);
	// check the msg in DATA रेजिस्टर.
	msg = vgpu_vreg(vgpu, offset + 4);
	addr = (msg >> 8) & 0xffff;
	ctrl = (msg >> 24) & 0xff;
	op = ctrl >> 4;
	अगर (!(value & DP_AUX_CH_CTL_SEND_BUSY)) अणु
		/* The ctl ग_लिखो to clear some states */
		वापस;
	पूर्ण

	/* Always set the wanted value क्रम vms. */
	ret_msg_size = (((op & 0x1) == GVT_AUX_I2C_READ) ? 2 : 1);
	vgpu_vreg(vgpu, offset) =
		DP_AUX_CH_CTL_DONE |
		((ret_msg_size << DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT) &
		DP_AUX_CH_CTL_MESSAGE_SIZE_MASK);

	अगर (msg_length == 3) अणु
		अगर (!(op & GVT_AUX_I2C_MOT)) अणु
			/* stop */
			पूर्णांकel_vgpu_init_i2c_edid(vgpu);
		पूर्ण अन्यथा अणु
			/* start or restart */
			i2c_edid->aux_ch.i2c_over_aux_ch = true;
			i2c_edid->aux_ch.aux_ch_mot = true;
			अगर (addr == 0) अणु
				/* reset the address */
				पूर्णांकel_vgpu_init_i2c_edid(vgpu);
			पूर्ण अन्यथा अगर (addr == EDID_ADDR) अणु
				i2c_edid->state = I2C_AUX_CH;
				i2c_edid->port = port_idx;
				i2c_edid->slave_selected = true;
				अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu,
					port_idx) &&
					पूर्णांकel_vgpu_port_is_dp(vgpu, port_idx))
					i2c_edid->edid_available = true;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर ((op & 0x1) == GVT_AUX_I2C_WRITE) अणु
		/* TODO
		 * We only support EDID पढ़ोing from I2C_over_AUX. And
		 * we करो not expect the index mode to be used. Right now
		 * the WRITE operation is ignored. It is good enough to
		 * support the gfx driver to करो EDID access.
		 */
	पूर्ण अन्यथा अणु
		अगर (drm_WARN_ON(&i915->drm, (op & 0x1) != GVT_AUX_I2C_READ))
			वापस;
		अगर (drm_WARN_ON(&i915->drm, msg_length != 4))
			वापस;
		अगर (i2c_edid->edid_available && i2c_edid->slave_selected) अणु
			अचिन्हित अक्षर val = edid_get_byte(vgpu);

			aux_data_क्रम_ग_लिखो = (val << 16);
		पूर्ण अन्यथा
			aux_data_क्रम_ग_लिखो = (0xff << 16);
	पूर्ण
	/* ग_लिखो the वापस value in AUX_CH_DATA reg which includes:
	 * ACK of I2C_WRITE
	 * वापसed byte अगर it is READ
	 */
	aux_data_क्रम_ग_लिखो |= GVT_AUX_I2C_REPLY_ACK << 24;
	vgpu_vreg(vgpu, offset + 4) = aux_data_क्रम_ग_लिखो;
पूर्ण

/**
 * पूर्णांकel_vgpu_init_i2c_edid - initialize vGPU i2c edid emulation
 * @vgpu: a vGPU
 *
 * This function is used to initialize vGPU i2c edid emulation stuffs
 *
 */
व्योम पूर्णांकel_vgpu_init_i2c_edid(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_vgpu_i2c_edid *edid = &vgpu->display.i2c_edid;

	edid->state = I2C_NOT_SPECIFIED;

	edid->port = -1;
	edid->slave_selected = false;
	edid->edid_available = false;
	edid->current_edid_पढ़ो = 0;

	स_रखो(&edid->gmbus, 0, माप(काष्ठा पूर्णांकel_vgpu_i2c_gmbus));

	edid->aux_ch.i2c_over_aux_ch = false;
	edid->aux_ch.aux_ch_mot = false;
पूर्ण
