<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020-2021 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "i915_trace.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dp_aux.h"
#समावेश "intel_pps.h"
#समावेश "intel_tc.h"

u32 पूर्णांकel_dp_pack_aux(स्थिर u8 *src, पूर्णांक src_bytes)
अणु
	पूर्णांक i;
	u32 v = 0;

	अगर (src_bytes > 4)
		src_bytes = 4;
	क्रम (i = 0; i < src_bytes; i++)
		v |= ((u32)src[i]) << ((3 - i) * 8);
	वापस v;
पूर्ण

अटल व्योम पूर्णांकel_dp_unpack_aux(u32 src, u8 *dst, पूर्णांक dst_bytes)
अणु
	पूर्णांक i;

	अगर (dst_bytes > 4)
		dst_bytes = 4;
	क्रम (i = 0; i < dst_bytes; i++)
		dst[i] = src >> ((3 - i) * 8);
पूर्ण

अटल u32
पूर्णांकel_dp_aux_रुको_करोne(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	i915_reg_t ch_ctl = पूर्णांकel_dp->aux_ch_ctl_reg(पूर्णांकel_dp);
	स्थिर अचिन्हित पूर्णांक समयout_ms = 10;
	u32 status;
	bool करोne;

#घोषणा C (((status = पूर्णांकel_uncore_पढ़ो_notrace(&i915->uncore, ch_ctl)) & DP_AUX_CH_CTL_SEND_BUSY) == 0)
	करोne = रुको_event_समयout(i915->gmbus_रुको_queue, C,
				  msecs_to_jअगरfies_समयout(समयout_ms));

	/* just trace the final value */
	trace_i915_reg_rw(false, ch_ctl, status, माप(status), true);

	अगर (!करोne)
		drm_err(&i915->drm,
			"%s: did not complete or timeout within %ums (status 0x%08x)\n",
			पूर्णांकel_dp->aux.name, समयout_ms, status);
#अघोषित C

	वापस status;
पूर्ण

अटल u32 g4x_get_aux_घड़ी_भागider(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक index)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	अगर (index)
		वापस 0;

	/*
	 * The घड़ी भागider is based off the hrawclk, and would like to run at
	 * 2MHz.  So, take the hrawclk value and भागide by 2000 and use that
	 */
	वापस DIV_ROUND_CLOSEST(RUNTIME_INFO(dev_priv)->rawclk_freq, 2000);
पूर्ण

अटल u32 ilk_get_aux_घड़ी_भागider(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक index)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	u32 freq;

	अगर (index)
		वापस 0;

	/*
	 * The घड़ी भागider is based off the cdclk or PCH rawclk, and would
	 * like to run at 2MHz.  So, take the cdclk or PCH rawclk value and
	 * भागide by 2000 and use that
	 */
	अगर (dig_port->aux_ch == AUX_CH_A)
		freq = dev_priv->cdclk.hw.cdclk;
	अन्यथा
		freq = RUNTIME_INFO(dev_priv)->rawclk_freq;
	वापस DIV_ROUND_CLOSEST(freq, 2000);
पूर्ण

अटल u32 hsw_get_aux_घड़ी_भागider(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक index)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);

	अगर (dig_port->aux_ch != AUX_CH_A && HAS_PCH_LPT_H(dev_priv)) अणु
		/* Workaround क्रम non-ULT HSW */
		चयन (index) अणु
		हाल 0: वापस 63;
		हाल 1: वापस 72;
		शेष: वापस 0;
		पूर्ण
	पूर्ण

	वापस ilk_get_aux_घड़ी_भागider(पूर्णांकel_dp, index);
पूर्ण

अटल u32 skl_get_aux_घड़ी_भागider(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक index)
अणु
	/*
	 * SKL करोesn't need us to program the AUX घड़ी भागider (Hardware will
	 * derive the घड़ी from CDCLK स्वतःmatically). We still implement the
	 * get_aux_घड़ी_भागider vfunc to plug-in पूर्णांकo the existing code.
	 */
	वापस index ? 0 : 1;
पूर्ण

अटल u32 g4x_get_aux_send_ctl(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				पूर्णांक send_bytes,
				u32 aux_घड़ी_भागider)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *dev_priv =
			to_i915(dig_port->base.base.dev);
	u32 preअक्षरge, समयout;

	अगर (IS_SANDYBRIDGE(dev_priv))
		preअक्षरge = 3;
	अन्यथा
		preअक्षरge = 5;

	/* Max समयout value on G4x-BDW: 1.6ms */
	अगर (IS_BROADWELL(dev_priv))
		समयout = DP_AUX_CH_CTL_TIME_OUT_600us;
	अन्यथा
		समयout = DP_AUX_CH_CTL_TIME_OUT_400us;

	वापस DP_AUX_CH_CTL_SEND_BUSY |
	       DP_AUX_CH_CTL_DONE |
	       DP_AUX_CH_CTL_INTERRUPT |
	       DP_AUX_CH_CTL_TIME_OUT_ERROR |
	       समयout |
	       DP_AUX_CH_CTL_RECEIVE_ERROR |
	       (send_bytes << DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT) |
	       (preअक्षरge << DP_AUX_CH_CTL_PRECHARGE_2US_SHIFT) |
	       (aux_घड़ी_भागider << DP_AUX_CH_CTL_BIT_CLOCK_2X_SHIFT);
पूर्ण

अटल u32 skl_get_aux_send_ctl(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				पूर्णांक send_bytes,
				u32 unused)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *i915 =
			to_i915(dig_port->base.base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, dig_port->base.port);
	u32 ret;

	/*
	 * Max समयout values:
	 * SKL-GLK: 1.6ms
	 * CNL: 3.2ms
	 * ICL+: 4ms
	 */
	ret = DP_AUX_CH_CTL_SEND_BUSY |
	      DP_AUX_CH_CTL_DONE |
	      DP_AUX_CH_CTL_INTERRUPT |
	      DP_AUX_CH_CTL_TIME_OUT_ERROR |
	      DP_AUX_CH_CTL_TIME_OUT_MAX |
	      DP_AUX_CH_CTL_RECEIVE_ERROR |
	      (send_bytes << DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT) |
	      DP_AUX_CH_CTL_FW_SYNC_PULSE_SKL(32) |
	      DP_AUX_CH_CTL_SYNC_PULSE_SKL(32);

	अगर (पूर्णांकel_phy_is_tc(i915, phy) &&
	    dig_port->tc_mode == TC_PORT_TBT_ALT)
		ret |= DP_AUX_CH_CTL_TBT_IO;

	वापस ret;
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_aux_xfer(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		  स्थिर u8 *send, पूर्णांक send_bytes,
		  u8 *recv, पूर्णांक recv_size,
		  u32 aux_send_ctl_flags)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *i915 =
			to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, dig_port->base.port);
	bool is_tc_port = पूर्णांकel_phy_is_tc(i915, phy);
	i915_reg_t ch_ctl, ch_data[5];
	u32 aux_घड़ी_भागider;
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य aux_करोमुख्य;
	पूर्णांकel_wakeref_t aux_wakeref;
	पूर्णांकel_wakeref_t pps_wakeref;
	पूर्णांक i, ret, recv_bytes;
	पूर्णांक try, घड़ी = 0;
	u32 status;
	bool vdd;

	ch_ctl = पूर्णांकel_dp->aux_ch_ctl_reg(पूर्णांकel_dp);
	क्रम (i = 0; i < ARRAY_SIZE(ch_data); i++)
		ch_data[i] = पूर्णांकel_dp->aux_ch_data_reg(पूर्णांकel_dp, i);

	अगर (is_tc_port)
		पूर्णांकel_tc_port_lock(dig_port);

	aux_करोमुख्य = पूर्णांकel_aux_घातer_करोमुख्य(dig_port);

	aux_wakeref = पूर्णांकel_display_घातer_get(i915, aux_करोमुख्य);
	pps_wakeref = पूर्णांकel_pps_lock(पूर्णांकel_dp);

	/*
	 * We will be called with VDD alपढ़ोy enabled क्रम dpcd/edid/oui पढ़ोs.
	 * In such हालs we want to leave VDD enabled and it's up to upper layers
	 * to turn it off. But क्रम eg. i2c-dev access we need to turn it on/off
	 * ourselves.
	 */
	vdd = पूर्णांकel_pps_vdd_on_unlocked(पूर्णांकel_dp);

	/*
	 * dp aux is extremely sensitive to irq latency, hence request the
	 * lowest possible wakeup latency and so prevent the cpu from going पूर्णांकo
	 * deep sleep states.
	 */
	cpu_latency_qos_update_request(&पूर्णांकel_dp->pm_qos, 0);

	पूर्णांकel_pps_check_घातer_unlocked(पूर्णांकel_dp);

	/* Try to रुको क्रम any previous AUX channel activity */
	क्रम (try = 0; try < 3; try++) अणु
		status = पूर्णांकel_uncore_पढ़ो_notrace(uncore, ch_ctl);
		अगर ((status & DP_AUX_CH_CTL_SEND_BUSY) == 0)
			अवरोध;
		msleep(1);
	पूर्ण
	/* just trace the final value */
	trace_i915_reg_rw(false, ch_ctl, status, माप(status), true);

	अगर (try == 3) अणु
		स्थिर u32 status = पूर्णांकel_uncore_पढ़ो(uncore, ch_ctl);

		अगर (status != पूर्णांकel_dp->aux_busy_last_status) अणु
			drm_WARN(&i915->drm, 1,
				 "%s: not started (status 0x%08x)\n",
				 पूर्णांकel_dp->aux.name, status);
			पूर्णांकel_dp->aux_busy_last_status = status;
		पूर्ण

		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* Only 5 data रेजिस्टरs! */
	अगर (drm_WARN_ON(&i915->drm, send_bytes > 20 || recv_size > 20)) अणु
		ret = -E2BIG;
		जाओ out;
	पूर्ण

	जबतक ((aux_घड़ी_भागider = पूर्णांकel_dp->get_aux_घड़ी_भागider(पूर्णांकel_dp, घड़ी++))) अणु
		u32 send_ctl = पूर्णांकel_dp->get_aux_send_ctl(पूर्णांकel_dp,
							  send_bytes,
							  aux_घड़ी_भागider);

		send_ctl |= aux_send_ctl_flags;

		/* Must try at least 3 बार according to DP spec */
		क्रम (try = 0; try < 5; try++) अणु
			/* Load the send data पूर्णांकo the aux channel data रेजिस्टरs */
			क्रम (i = 0; i < send_bytes; i += 4)
				पूर्णांकel_uncore_ग_लिखो(uncore,
						   ch_data[i >> 2],
						   पूर्णांकel_dp_pack_aux(send + i,
								     send_bytes - i));

			/* Send the command and रुको क्रम it to complete */
			पूर्णांकel_uncore_ग_लिखो(uncore, ch_ctl, send_ctl);

			status = पूर्णांकel_dp_aux_रुको_करोne(पूर्णांकel_dp);

			/* Clear करोne status and any errors */
			पूर्णांकel_uncore_ग_लिखो(uncore,
					   ch_ctl,
					   status |
					   DP_AUX_CH_CTL_DONE |
					   DP_AUX_CH_CTL_TIME_OUT_ERROR |
					   DP_AUX_CH_CTL_RECEIVE_ERROR);

			/*
			 * DP CTS 1.2 Core Rev 1.1, 4.2.1.1 & 4.2.1.2
			 *   400us delay required क्रम errors and समयouts
			 *   Timeout errors from the HW alपढ़ोy meet this
			 *   requirement so skip to next iteration
			 */
			अगर (status & DP_AUX_CH_CTL_TIME_OUT_ERROR)
				जारी;

			अगर (status & DP_AUX_CH_CTL_RECEIVE_ERROR) अणु
				usleep_range(400, 500);
				जारी;
			पूर्ण
			अगर (status & DP_AUX_CH_CTL_DONE)
				जाओ करोne;
		पूर्ण
	पूर्ण

	अगर ((status & DP_AUX_CH_CTL_DONE) == 0) अणु
		drm_err(&i915->drm, "%s: not done (status 0x%08x)\n",
			पूर्णांकel_dp->aux.name, status);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

करोne:
	/*
	 * Check क्रम समयout or receive error. Timeouts occur when the sink is
	 * not connected.
	 */
	अगर (status & DP_AUX_CH_CTL_RECEIVE_ERROR) अणु
		drm_err(&i915->drm, "%s: receive error (status 0x%08x)\n",
			पूर्णांकel_dp->aux.name, status);
		ret = -EIO;
		जाओ out;
	पूर्ण

	/*
	 * Timeouts occur when the device isn't connected, so they're "normal"
	 * -- करोn't fill the kernel log with these
	 */
	अगर (status & DP_AUX_CH_CTL_TIME_OUT_ERROR) अणु
		drm_dbg_kms(&i915->drm, "%s: timeout (status 0x%08x)\n",
			    पूर्णांकel_dp->aux.name, status);
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/* Unload any bytes sent back from the other side */
	recv_bytes = ((status & DP_AUX_CH_CTL_MESSAGE_SIZE_MASK) >>
		      DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT);

	/*
	 * By BSpec: "Message sizes of 0 or >20 are not allowed."
	 * We have no idea of what happened so we वापस -EBUSY so
	 * drm layer takes care क्रम the necessary retries.
	 */
	अगर (recv_bytes == 0 || recv_bytes > 20) अणु
		drm_dbg_kms(&i915->drm,
			    "%s: Forbidden recv_bytes = %d on aux transaction\n",
			    पूर्णांकel_dp->aux.name, recv_bytes);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (recv_bytes > recv_size)
		recv_bytes = recv_size;

	क्रम (i = 0; i < recv_bytes; i += 4)
		पूर्णांकel_dp_unpack_aux(पूर्णांकel_uncore_पढ़ो(uncore, ch_data[i >> 2]),
				    recv + i, recv_bytes - i);

	ret = recv_bytes;
out:
	cpu_latency_qos_update_request(&पूर्णांकel_dp->pm_qos, PM_QOS_DEFAULT_VALUE);

	अगर (vdd)
		पूर्णांकel_pps_vdd_off_unlocked(पूर्णांकel_dp, false);

	पूर्णांकel_pps_unlock(पूर्णांकel_dp, pps_wakeref);
	पूर्णांकel_display_घातer_put_async(i915, aux_करोमुख्य, aux_wakeref);

	अगर (is_tc_port)
		पूर्णांकel_tc_port_unlock(dig_port);

	वापस ret;
पूर्ण

#घोषणा BARE_ADDRESS_SIZE	3
#घोषणा HEADER_SIZE		(BARE_ADDRESS_SIZE + 1)

अटल व्योम
पूर्णांकel_dp_aux_header(u8 txbuf[HEADER_SIZE],
		    स्थिर काष्ठा drm_dp_aux_msg *msg)
अणु
	txbuf[0] = (msg->request << 4) | ((msg->address >> 16) & 0xf);
	txbuf[1] = (msg->address >> 8) & 0xff;
	txbuf[2] = msg->address & 0xff;
	txbuf[3] = msg->size - 1;
पूर्ण

अटल u32 पूर्णांकel_dp_aux_xfer_flags(स्थिर काष्ठा drm_dp_aux_msg *msg)
अणु
	/*
	 * If we're trying to send the HDCP Aksv, we need to set a the Aksv
	 * select bit to inक्रमm the hardware to send the Aksv after our header
	 * since we can't access that data from software.
	 */
	अगर ((msg->request & ~DP_AUX_I2C_MOT) == DP_AUX_NATIVE_WRITE &&
	    msg->address == DP_AUX_HDCP_AKSV)
		वापस DP_AUX_CH_CTL_AUX_AKSV_SELECT;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
पूर्णांकel_dp_aux_transfer(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = container_of(aux, काष्ठा पूर्णांकel_dp, aux);
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 txbuf[20], rxbuf[20];
	माप_प्रकार txsize, rxsize;
	u32 flags = पूर्णांकel_dp_aux_xfer_flags(msg);
	पूर्णांक ret;

	पूर्णांकel_dp_aux_header(txbuf, msg);

	चयन (msg->request & ~DP_AUX_I2C_MOT) अणु
	हाल DP_AUX_NATIVE_WRITE:
	हाल DP_AUX_I2C_WRITE:
	हाल DP_AUX_I2C_WRITE_STATUS_UPDATE:
		txsize = msg->size ? HEADER_SIZE + msg->size : BARE_ADDRESS_SIZE;
		rxsize = 2; /* 0 or 1 data bytes */

		अगर (drm_WARN_ON(&i915->drm, txsize > 20))
			वापस -E2BIG;

		drm_WARN_ON(&i915->drm, !msg->buffer != !msg->size);

		अगर (msg->buffer)
			स_नकल(txbuf + HEADER_SIZE, msg->buffer, msg->size);

		ret = पूर्णांकel_dp_aux_xfer(पूर्णांकel_dp, txbuf, txsize,
					rxbuf, rxsize, flags);
		अगर (ret > 0) अणु
			msg->reply = rxbuf[0] >> 4;

			अगर (ret > 1) अणु
				/* Number of bytes written in a लघु ग_लिखो. */
				ret = clamp_t(पूर्णांक, rxbuf[1], 0, msg->size);
			पूर्ण अन्यथा अणु
				/* Return payload size. */
				ret = msg->size;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल DP_AUX_NATIVE_READ:
	हाल DP_AUX_I2C_READ:
		txsize = msg->size ? HEADER_SIZE : BARE_ADDRESS_SIZE;
		rxsize = msg->size + 1;

		अगर (drm_WARN_ON(&i915->drm, rxsize > 20))
			वापस -E2BIG;

		ret = पूर्णांकel_dp_aux_xfer(पूर्णांकel_dp, txbuf, txsize,
					rxbuf, rxsize, flags);
		अगर (ret > 0) अणु
			msg->reply = rxbuf[0] >> 4;
			/*
			 * Assume happy day, and copy the data. The caller is
			 * expected to check msg->reply beक्रमe touching it.
			 *
			 * Return payload size.
			 */
			ret--;
			स_नकल(msg->buffer, rxbuf + 1, ret);
		पूर्ण
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल i915_reg_t g4x_aux_ctl_reg(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	क्रमागत aux_ch aux_ch = dig_port->aux_ch;

	चयन (aux_ch) अणु
	हाल AUX_CH_B:
	हाल AUX_CH_C:
	हाल AUX_CH_D:
		वापस DP_AUX_CH_CTL(aux_ch);
	शेष:
		MISSING_CASE(aux_ch);
		वापस DP_AUX_CH_CTL(AUX_CH_B);
	पूर्ण
पूर्ण

अटल i915_reg_t g4x_aux_data_reg(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक index)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	क्रमागत aux_ch aux_ch = dig_port->aux_ch;

	चयन (aux_ch) अणु
	हाल AUX_CH_B:
	हाल AUX_CH_C:
	हाल AUX_CH_D:
		वापस DP_AUX_CH_DATA(aux_ch, index);
	शेष:
		MISSING_CASE(aux_ch);
		वापस DP_AUX_CH_DATA(AUX_CH_B, index);
	पूर्ण
पूर्ण

अटल i915_reg_t ilk_aux_ctl_reg(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	क्रमागत aux_ch aux_ch = dig_port->aux_ch;

	चयन (aux_ch) अणु
	हाल AUX_CH_A:
		वापस DP_AUX_CH_CTL(aux_ch);
	हाल AUX_CH_B:
	हाल AUX_CH_C:
	हाल AUX_CH_D:
		वापस PCH_DP_AUX_CH_CTL(aux_ch);
	शेष:
		MISSING_CASE(aux_ch);
		वापस DP_AUX_CH_CTL(AUX_CH_A);
	पूर्ण
पूर्ण

अटल i915_reg_t ilk_aux_data_reg(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक index)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	क्रमागत aux_ch aux_ch = dig_port->aux_ch;

	चयन (aux_ch) अणु
	हाल AUX_CH_A:
		वापस DP_AUX_CH_DATA(aux_ch, index);
	हाल AUX_CH_B:
	हाल AUX_CH_C:
	हाल AUX_CH_D:
		वापस PCH_DP_AUX_CH_DATA(aux_ch, index);
	शेष:
		MISSING_CASE(aux_ch);
		वापस DP_AUX_CH_DATA(AUX_CH_A, index);
	पूर्ण
पूर्ण

अटल i915_reg_t skl_aux_ctl_reg(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	क्रमागत aux_ch aux_ch = dig_port->aux_ch;

	चयन (aux_ch) अणु
	हाल AUX_CH_A:
	हाल AUX_CH_B:
	हाल AUX_CH_C:
	हाल AUX_CH_D:
	हाल AUX_CH_E:
	हाल AUX_CH_F:
		वापस DP_AUX_CH_CTL(aux_ch);
	शेष:
		MISSING_CASE(aux_ch);
		वापस DP_AUX_CH_CTL(AUX_CH_A);
	पूर्ण
पूर्ण

अटल i915_reg_t skl_aux_data_reg(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक index)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	क्रमागत aux_ch aux_ch = dig_port->aux_ch;

	चयन (aux_ch) अणु
	हाल AUX_CH_A:
	हाल AUX_CH_B:
	हाल AUX_CH_C:
	हाल AUX_CH_D:
	हाल AUX_CH_E:
	हाल AUX_CH_F:
		वापस DP_AUX_CH_DATA(aux_ch, index);
	शेष:
		MISSING_CASE(aux_ch);
		वापस DP_AUX_CH_DATA(AUX_CH_A, index);
	पूर्ण
पूर्ण

अटल i915_reg_t tgl_aux_ctl_reg(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	क्रमागत aux_ch aux_ch = dig_port->aux_ch;

	चयन (aux_ch) अणु
	हाल AUX_CH_A:
	हाल AUX_CH_B:
	हाल AUX_CH_C:
	हाल AUX_CH_USBC1:
	हाल AUX_CH_USBC2:
	हाल AUX_CH_USBC3:
	हाल AUX_CH_USBC4:
	हाल AUX_CH_USBC5:
	हाल AUX_CH_USBC6:
		वापस DP_AUX_CH_CTL(aux_ch);
	शेष:
		MISSING_CASE(aux_ch);
		वापस DP_AUX_CH_CTL(AUX_CH_A);
	पूर्ण
पूर्ण

अटल i915_reg_t tgl_aux_data_reg(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक index)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	क्रमागत aux_ch aux_ch = dig_port->aux_ch;

	चयन (aux_ch) अणु
	हाल AUX_CH_A:
	हाल AUX_CH_B:
	हाल AUX_CH_C:
	हाल AUX_CH_USBC1:
	हाल AUX_CH_USBC2:
	हाल AUX_CH_USBC3:
	हाल AUX_CH_USBC4:
	हाल AUX_CH_USBC5:
	हाल AUX_CH_USBC6:
		वापस DP_AUX_CH_DATA(aux_ch, index);
	शेष:
		MISSING_CASE(aux_ch);
		वापस DP_AUX_CH_DATA(AUX_CH_A, index);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_dp_aux_fini(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	अगर (cpu_latency_qos_request_active(&पूर्णांकel_dp->pm_qos))
		cpu_latency_qos_हटाओ_request(&पूर्णांकel_dp->pm_qos);

	kमुक्त(पूर्णांकel_dp->aux.name);
पूर्ण

व्योम पूर्णांकel_dp_aux_init(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_encoder *encoder = &dig_port->base;
	क्रमागत aux_ch aux_ch = dig_port->aux_ch;

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		पूर्णांकel_dp->aux_ch_ctl_reg = tgl_aux_ctl_reg;
		पूर्णांकel_dp->aux_ch_data_reg = tgl_aux_data_reg;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 9) अणु
		पूर्णांकel_dp->aux_ch_ctl_reg = skl_aux_ctl_reg;
		पूर्णांकel_dp->aux_ch_data_reg = skl_aux_data_reg;
	पूर्ण अन्यथा अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		पूर्णांकel_dp->aux_ch_ctl_reg = ilk_aux_ctl_reg;
		पूर्णांकel_dp->aux_ch_data_reg = ilk_aux_data_reg;
	पूर्ण अन्यथा अणु
		पूर्णांकel_dp->aux_ch_ctl_reg = g4x_aux_ctl_reg;
		पूर्णांकel_dp->aux_ch_data_reg = g4x_aux_data_reg;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 9)
		पूर्णांकel_dp->get_aux_घड़ी_भागider = skl_get_aux_घड़ी_भागider;
	अन्यथा अगर (IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
		पूर्णांकel_dp->get_aux_घड़ी_भागider = hsw_get_aux_घड़ी_भागider;
	अन्यथा अगर (HAS_PCH_SPLIT(dev_priv))
		पूर्णांकel_dp->get_aux_घड़ी_भागider = ilk_get_aux_घड़ी_भागider;
	अन्यथा
		पूर्णांकel_dp->get_aux_घड़ी_भागider = g4x_get_aux_घड़ी_भागider;

	अगर (DISPLAY_VER(dev_priv) >= 9)
		पूर्णांकel_dp->get_aux_send_ctl = skl_get_aux_send_ctl;
	अन्यथा
		पूर्णांकel_dp->get_aux_send_ctl = g4x_get_aux_send_ctl;

	drm_dp_aux_init(&पूर्णांकel_dp->aux);

	/* Failure to allocate our preferred name is not critical */
	अगर (DISPLAY_VER(dev_priv) >= 12 && aux_ch >= AUX_CH_USBC1)
		पूर्णांकel_dp->aux.name = kaप्र_लिखो(GFP_KERNEL, "AUX USBC%c/%s",
					       aux_ch - AUX_CH_USBC1 + '1',
					       encoder->base.name);
	अन्यथा
		पूर्णांकel_dp->aux.name = kaप्र_लिखो(GFP_KERNEL, "AUX %c/%s",
					       aux_ch_name(aux_ch),
					       encoder->base.name);

	पूर्णांकel_dp->aux.transfer = पूर्णांकel_dp_aux_transfer;
	cpu_latency_qos_add_request(&पूर्णांकel_dp->pm_qos, PM_QOS_DEFAULT_VALUE);
पूर्ण
