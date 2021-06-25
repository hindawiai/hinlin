<शैली गुरु>
/*
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */

#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"

#समावेश "atom.h"
#समावेश "atom-bits.h"
#समावेश "atombios_encoders.h"
#समावेश "atombios_dp.h"
#समावेश "amdgpu_connectors.h"
#समावेश "amdgpu_atombios.h"
#समावेश <drm/drm_dp_helper.h>

/* move these to drm_dp_helper.c/h */
#घोषणा DP_LINK_CONFIGURATION_SIZE 9
#घोषणा DP_DPCD_SIZE DP_RECEIVER_CAP_SIZE

अटल अक्षर *voltage_names[] = अणु
	"0.4V", "0.6V", "0.8V", "1.2V"
पूर्ण;
अटल अक्षर *pre_emph_names[] = अणु
	"0dB", "3.5dB", "6dB", "9.5dB"
पूर्ण;

/***** amdgpu AUX functions *****/

जोड़ aux_channel_transaction अणु
	PROCESS_AUX_CHANNEL_TRANSACTION_PS_ALLOCATION v1;
	PROCESS_AUX_CHANNEL_TRANSACTION_PARAMETERS_V2 v2;
पूर्ण;

अटल पूर्णांक amdgpu_atombios_dp_process_aux_ch(काष्ठा amdgpu_i2c_chan *chan,
				      u8 *send, पूर्णांक send_bytes,
				      u8 *recv, पूर्णांक recv_size,
				      u8 delay, u8 *ack)
अणु
	काष्ठा drm_device *dev = chan->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	जोड़ aux_channel_transaction args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, ProcessAuxChannelTransaction);
	अचिन्हित अक्षर *base;
	पूर्णांक recv_bytes;
	पूर्णांक r = 0;

	स_रखो(&args, 0, माप(args));

	mutex_lock(&chan->mutex);

	base = (अचिन्हित अक्षर *)(adev->mode_info.atom_context->scratch + 1);

	amdgpu_atombios_copy_swap(base, send, send_bytes, true);

	args.v2.lpAuxRequest = cpu_to_le16((u16)(0 + 4));
	args.v2.lpDataOut = cpu_to_le16((u16)(16 + 4));
	args.v2.ucDataOutLen = 0;
	args.v2.ucChannelID = chan->rec.i2c_id;
	args.v2.ucDelay = delay / 10;
	args.v2.ucHPD_ID = chan->rec.hpd;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

	*ack = args.v2.ucReplyStatus;

	/* समयout */
	अगर (args.v2.ucReplyStatus == 1) अणु
		r = -ETIMEDOUT;
		जाओ करोne;
	पूर्ण

	/* flags not zero */
	अगर (args.v2.ucReplyStatus == 2) अणु
		DRM_DEBUG_KMS("dp_aux_ch flags not zero\n");
		r = -EIO;
		जाओ करोne;
	पूर्ण

	/* error */
	अगर (args.v2.ucReplyStatus == 3) अणु
		DRM_DEBUG_KMS("dp_aux_ch error\n");
		r = -EIO;
		जाओ करोne;
	पूर्ण

	recv_bytes = args.v1.ucDataOutLen;
	अगर (recv_bytes > recv_size)
		recv_bytes = recv_size;

	अगर (recv && recv_size)
		amdgpu_atombios_copy_swap(recv, base + 16, recv_bytes, false);

	r = recv_bytes;
करोne:
	mutex_unlock(&chan->mutex);

	वापस r;
पूर्ण

#घोषणा BARE_ADDRESS_SIZE 3
#घोषणा HEADER_SIZE (BARE_ADDRESS_SIZE + 1)

अटल sमाप_प्रकार
amdgpu_atombios_dp_aux_transfer(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा amdgpu_i2c_chan *chan =
		container_of(aux, काष्ठा amdgpu_i2c_chan, aux);
	पूर्णांक ret;
	u8 tx_buf[20];
	माप_प्रकार tx_size;
	u8 ack, delay = 0;

	अगर (WARN_ON(msg->size > 16))
		वापस -E2BIG;

	tx_buf[0] = msg->address & 0xff;
	tx_buf[1] = msg->address >> 8;
	tx_buf[2] = (msg->request << 4) |
		((msg->address >> 16) & 0xf);
	tx_buf[3] = msg->size ? (msg->size - 1) : 0;

	चयन (msg->request & ~DP_AUX_I2C_MOT) अणु
	हाल DP_AUX_NATIVE_WRITE:
	हाल DP_AUX_I2C_WRITE:
		/* tx_size needs to be 4 even क्रम bare address packets since the atom
		 * table needs the info in tx_buf[3].
		 */
		tx_size = HEADER_SIZE + msg->size;
		अगर (msg->size == 0)
			tx_buf[3] |= BARE_ADDRESS_SIZE << 4;
		अन्यथा
			tx_buf[3] |= tx_size << 4;
		स_नकल(tx_buf + HEADER_SIZE, msg->buffer, msg->size);
		ret = amdgpu_atombios_dp_process_aux_ch(chan,
						 tx_buf, tx_size, शून्य, 0, delay, &ack);
		अगर (ret >= 0)
			/* Return payload size. */
			ret = msg->size;
		अवरोध;
	हाल DP_AUX_NATIVE_READ:
	हाल DP_AUX_I2C_READ:
		/* tx_size needs to be 4 even क्रम bare address packets since the atom
		 * table needs the info in tx_buf[3].
		 */
		tx_size = HEADER_SIZE;
		अगर (msg->size == 0)
			tx_buf[3] |= BARE_ADDRESS_SIZE << 4;
		अन्यथा
			tx_buf[3] |= tx_size << 4;
		ret = amdgpu_atombios_dp_process_aux_ch(chan,
						 tx_buf, tx_size, msg->buffer, msg->size, delay, &ack);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret >= 0)
		msg->reply = ack >> 4;

	वापस ret;
पूर्ण

व्योम amdgpu_atombios_dp_aux_init(काष्ठा amdgpu_connector *amdgpu_connector)
अणु
	amdgpu_connector->ddc_bus->rec.hpd = amdgpu_connector->hpd.hpd;
	amdgpu_connector->ddc_bus->aux.transfer = amdgpu_atombios_dp_aux_transfer;
	drm_dp_aux_init(&amdgpu_connector->ddc_bus->aux);
	amdgpu_connector->ddc_bus->has_aux = true;
पूर्ण

/***** general DP utility functions *****/

#घोषणा DP_VOLTAGE_MAX         DP_TRAIN_VOLTAGE_SWING_LEVEL_3
#घोषणा DP_PRE_EMPHASIS_MAX    DP_TRAIN_PRE_EMPH_LEVEL_3

अटल व्योम amdgpu_atombios_dp_get_adjust_train(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
						पूर्णांक lane_count,
						u8 train_set[4])
अणु
	u8 v = 0;
	u8 p = 0;
	पूर्णांक lane;

	क्रम (lane = 0; lane < lane_count; lane++) अणु
		u8 this_v = drm_dp_get_adjust_request_voltage(link_status, lane);
		u8 this_p = drm_dp_get_adjust_request_pre_emphasis(link_status, lane);

		DRM_DEBUG_KMS("requested signal parameters: lane %d voltage %s pre_emph %s\n",
			  lane,
			  voltage_names[this_v >> DP_TRAIN_VOLTAGE_SWING_SHIFT],
			  pre_emph_names[this_p >> DP_TRAIN_PRE_EMPHASIS_SHIFT]);

		अगर (this_v > v)
			v = this_v;
		अगर (this_p > p)
			p = this_p;
	पूर्ण

	अगर (v >= DP_VOLTAGE_MAX)
		v |= DP_TRAIN_MAX_SWING_REACHED;

	अगर (p >= DP_PRE_EMPHASIS_MAX)
		p |= DP_TRAIN_MAX_PRE_EMPHASIS_REACHED;

	DRM_DEBUG_KMS("using signal parameters: voltage %s pre_emph %s\n",
		  voltage_names[(v & DP_TRAIN_VOLTAGE_SWING_MASK) >> DP_TRAIN_VOLTAGE_SWING_SHIFT],
		  pre_emph_names[(p & DP_TRAIN_PRE_EMPHASIS_MASK) >> DP_TRAIN_PRE_EMPHASIS_SHIFT]);

	क्रम (lane = 0; lane < 4; lane++)
		train_set[lane] = v | p;
पूर्ण

/* convert bits per color to bits per pixel */
/* get bpc from the EDID */
अटल अचिन्हित amdgpu_atombios_dp_convert_bpc_to_bpp(पूर्णांक bpc)
अणु
	अगर (bpc == 0)
		वापस 24;
	अन्यथा
		वापस bpc * 3;
पूर्ण

/***** amdgpu specअगरic DP functions *****/

अटल पूर्णांक amdgpu_atombios_dp_get_dp_link_config(काष्ठा drm_connector *connector,
						 स्थिर u8 dpcd[DP_DPCD_SIZE],
						 अचिन्हित pix_घड़ी,
						 अचिन्हित *dp_lanes, अचिन्हित *dp_rate)
अणु
	अचिन्हित bpp =
		amdgpu_atombios_dp_convert_bpc_to_bpp(amdgpu_connector_get_monitor_bpc(connector));
	अटल स्थिर अचिन्हित link_rates[3] = अणु 162000, 270000, 540000 पूर्ण;
	अचिन्हित max_link_rate = drm_dp_max_link_rate(dpcd);
	अचिन्हित max_lane_num = drm_dp_max_lane_count(dpcd);
	अचिन्हित lane_num, i, max_pix_घड़ी;

	अगर (amdgpu_connector_encoder_get_dp_bridge_encoder_id(connector) ==
	    ENCODER_OBJECT_ID_NUTMEG) अणु
		क्रम (lane_num = 1; lane_num <= max_lane_num; lane_num <<= 1) अणु
			max_pix_घड़ी = (lane_num * 270000 * 8) / bpp;
			अगर (max_pix_घड़ी >= pix_घड़ी) अणु
				*dp_lanes = lane_num;
				*dp_rate = 270000;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(link_rates) && link_rates[i] <= max_link_rate; i++) अणु
			क्रम (lane_num = 1; lane_num <= max_lane_num; lane_num <<= 1) अणु
				max_pix_घड़ी = (lane_num * link_rates[i] * 8) / bpp;
				अगर (max_pix_घड़ी >= pix_घड़ी) अणु
					*dp_lanes = lane_num;
					*dp_rate = link_rates[i];
					वापस 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल u8 amdgpu_atombios_dp_encoder_service(काष्ठा amdgpu_device *adev,
				      पूर्णांक action, पूर्णांक dp_घड़ी,
				      u8 ucconfig, u8 lane_num)
अणु
	DP_ENCODER_SERVICE_PARAMETERS args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, DPEncoderService);

	स_रखो(&args, 0, माप(args));
	args.ucLinkClock = dp_घड़ी / 10;
	args.ucConfig = ucconfig;
	args.ucAction = action;
	args.ucLaneNum = lane_num;
	args.ucStatus = 0;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
	वापस args.ucStatus;
पूर्ण

u8 amdgpu_atombios_dp_get_sinktype(काष्ठा amdgpu_connector *amdgpu_connector)
अणु
	काष्ठा drm_device *dev = amdgpu_connector->base.dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	वापस amdgpu_atombios_dp_encoder_service(adev, ATOM_DP_ACTION_GET_SINK_TYPE, 0,
					   amdgpu_connector->ddc_bus->rec.i2c_id, 0);
पूर्ण

अटल व्योम amdgpu_atombios_dp_probe_oui(काष्ठा amdgpu_connector *amdgpu_connector)
अणु
	काष्ठा amdgpu_connector_atom_dig *dig_connector = amdgpu_connector->con_priv;
	u8 buf[3];

	अगर (!(dig_connector->dpcd[DP_DOWN_STREAM_PORT_COUNT] & DP_OUI_SUPPORT))
		वापस;

	अगर (drm_dp_dpcd_पढ़ो(&amdgpu_connector->ddc_bus->aux, DP_SINK_OUI, buf, 3) == 3)
		DRM_DEBUG_KMS("Sink OUI: %02hx%02hx%02hx\n",
			      buf[0], buf[1], buf[2]);

	अगर (drm_dp_dpcd_पढ़ो(&amdgpu_connector->ddc_bus->aux, DP_BRANCH_OUI, buf, 3) == 3)
		DRM_DEBUG_KMS("Branch OUI: %02hx%02hx%02hx\n",
			      buf[0], buf[1], buf[2]);
पूर्ण

अटल व्योम amdgpu_atombios_dp_ds_ports(काष्ठा amdgpu_connector *amdgpu_connector)
अणु
	काष्ठा amdgpu_connector_atom_dig *dig_connector = amdgpu_connector->con_priv;
	पूर्णांक ret;

	अगर (dig_connector->dpcd[DP_DPCD_REV] > 0x10) अणु
		ret = drm_dp_dpcd_पढ़ो(&amdgpu_connector->ddc_bus->aux,
				       DP_DOWNSTREAM_PORT_0,
				       dig_connector->करोwnstream_ports,
				       DP_MAX_DOWNSTREAM_PORTS);
		अगर (ret)
			स_रखो(dig_connector->करोwnstream_ports, 0,
			       DP_MAX_DOWNSTREAM_PORTS);
	पूर्ण
पूर्ण

पूर्णांक amdgpu_atombios_dp_get_dpcd(काष्ठा amdgpu_connector *amdgpu_connector)
अणु
	काष्ठा amdgpu_connector_atom_dig *dig_connector = amdgpu_connector->con_priv;
	u8 msg[DP_DPCD_SIZE];
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ो(&amdgpu_connector->ddc_bus->aux, DP_DPCD_REV,
			       msg, DP_DPCD_SIZE);
	अगर (ret == DP_DPCD_SIZE) अणु
		स_नकल(dig_connector->dpcd, msg, DP_DPCD_SIZE);

		DRM_DEBUG_KMS("DPCD: %*ph\n", (पूर्णांक)माप(dig_connector->dpcd),
			      dig_connector->dpcd);

		amdgpu_atombios_dp_probe_oui(amdgpu_connector);
		amdgpu_atombios_dp_ds_ports(amdgpu_connector);
		वापस 0;
	पूर्ण

	dig_connector->dpcd[0] = 0;
	वापस -EINVAL;
पूर्ण

पूर्णांक amdgpu_atombios_dp_get_panel_mode(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	पूर्णांक panel_mode = DP_PANEL_MODE_EXTERNAL_DP_MODE;
	u16 dp_bridge = amdgpu_connector_encoder_get_dp_bridge_encoder_id(connector);
	u8 पंचांगp;

	अगर (!amdgpu_connector->con_priv)
		वापस panel_mode;

	अगर (dp_bridge != ENCODER_OBJECT_ID_NONE) अणु
		/* DP bridge chips */
		अगर (drm_dp_dpcd_पढ़ोb(&amdgpu_connector->ddc_bus->aux,
				      DP_EDP_CONFIGURATION_CAP, &पंचांगp) == 1) अणु
			अगर (पंचांगp & 1)
				panel_mode = DP_PANEL_MODE_INTERNAL_DP2_MODE;
			अन्यथा अगर ((dp_bridge == ENCODER_OBJECT_ID_NUTMEG) ||
				 (dp_bridge == ENCODER_OBJECT_ID_TRAVIS))
				panel_mode = DP_PANEL_MODE_INTERNAL_DP1_MODE;
			अन्यथा
				panel_mode = DP_PANEL_MODE_EXTERNAL_DP_MODE;
		पूर्ण
	पूर्ण अन्यथा अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP) अणु
		/* eDP */
		अगर (drm_dp_dpcd_पढ़ोb(&amdgpu_connector->ddc_bus->aux,
				      DP_EDP_CONFIGURATION_CAP, &पंचांगp) == 1) अणु
			अगर (पंचांगp & 1)
				panel_mode = DP_PANEL_MODE_INTERNAL_DP2_MODE;
		पूर्ण
	पूर्ण

	वापस panel_mode;
पूर्ण

व्योम amdgpu_atombios_dp_set_link_config(काष्ठा drm_connector *connector,
				 स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	काष्ठा amdgpu_connector_atom_dig *dig_connector;
	पूर्णांक ret;

	अगर (!amdgpu_connector->con_priv)
		वापस;
	dig_connector = amdgpu_connector->con_priv;

	अगर ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
	    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP)) अणु
		ret = amdgpu_atombios_dp_get_dp_link_config(connector, dig_connector->dpcd,
							    mode->घड़ी,
							    &dig_connector->dp_lane_count,
							    &dig_connector->dp_घड़ी);
		अगर (ret) अणु
			dig_connector->dp_घड़ी = 0;
			dig_connector->dp_lane_count = 0;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक amdgpu_atombios_dp_mode_valid_helper(काष्ठा drm_connector *connector,
				  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	काष्ठा amdgpu_connector_atom_dig *dig_connector;
	अचिन्हित dp_lanes, dp_घड़ी;
	पूर्णांक ret;

	अगर (!amdgpu_connector->con_priv)
		वापस MODE_CLOCK_HIGH;
	dig_connector = amdgpu_connector->con_priv;

	ret = amdgpu_atombios_dp_get_dp_link_config(connector, dig_connector->dpcd,
						    mode->घड़ी, &dp_lanes, &dp_घड़ी);
	अगर (ret)
		वापस MODE_CLOCK_HIGH;

	अगर ((dp_घड़ी == 540000) &&
	    (!amdgpu_connector_is_dp12_capable(connector)))
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

bool amdgpu_atombios_dp_needs_link_train(काष्ठा amdgpu_connector *amdgpu_connector)
अणु
	u8 link_status[DP_LINK_STATUS_SIZE];
	काष्ठा amdgpu_connector_atom_dig *dig = amdgpu_connector->con_priv;

	अगर (drm_dp_dpcd_पढ़ो_link_status(&amdgpu_connector->ddc_bus->aux, link_status)
	    <= 0)
		वापस false;
	अगर (drm_dp_channel_eq_ok(link_status, dig->dp_lane_count))
		वापस false;
	वापस true;
पूर्ण

व्योम amdgpu_atombios_dp_set_rx_घातer_state(काष्ठा drm_connector *connector,
				    u8 घातer_state)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	काष्ठा amdgpu_connector_atom_dig *dig_connector;

	अगर (!amdgpu_connector->con_priv)
		वापस;

	dig_connector = amdgpu_connector->con_priv;

	/* घातer up/करोwn the sink */
	अगर (dig_connector->dpcd[0] >= 0x11) अणु
		drm_dp_dpcd_ग_लिखोb(&amdgpu_connector->ddc_bus->aux,
				   DP_SET_POWER, घातer_state);
		usleep_range(1000, 2000);
	पूर्ण
पूर्ण

काष्ठा amdgpu_atombios_dp_link_train_info अणु
	काष्ठा amdgpu_device *adev;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;
	पूर्णांक dp_घड़ी;
	पूर्णांक dp_lane_count;
	bool tp3_supported;
	u8 dpcd[DP_RECEIVER_CAP_SIZE];
	u8 train_set[4];
	u8 link_status[DP_LINK_STATUS_SIZE];
	u8 tries;
	काष्ठा drm_dp_aux *aux;
पूर्ण;

अटल व्योम
amdgpu_atombios_dp_update_vs_emph(काष्ठा amdgpu_atombios_dp_link_train_info *dp_info)
अणु
	/* set the initial vs/emph on the source */
	amdgpu_atombios_encoder_setup_dig_transmitter(dp_info->encoder,
					       ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH,
					       0, dp_info->train_set[0]); /* sets all lanes at once */

	/* set the vs/emph on the sink */
	drm_dp_dpcd_ग_लिखो(dp_info->aux, DP_TRAINING_LANE0_SET,
			  dp_info->train_set, dp_info->dp_lane_count);
पूर्ण

अटल व्योम
amdgpu_atombios_dp_set_tp(काष्ठा amdgpu_atombios_dp_link_train_info *dp_info, पूर्णांक tp)
अणु
	पूर्णांक rtp = 0;

	/* set training pattern on the source */
	चयन (tp) अणु
	हाल DP_TRAINING_PATTERN_1:
		rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN1;
		अवरोध;
	हाल DP_TRAINING_PATTERN_2:
		rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN2;
		अवरोध;
	हाल DP_TRAINING_PATTERN_3:
		rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN3;
			अवरोध;
	पूर्ण
	amdgpu_atombios_encoder_setup_dig_encoder(dp_info->encoder, rtp, 0);

	/* enable training pattern on the sink */
	drm_dp_dpcd_ग_लिखोb(dp_info->aux, DP_TRAINING_PATTERN_SET, tp);
पूर्ण

अटल पूर्णांक
amdgpu_atombios_dp_link_train_init(काष्ठा amdgpu_atombios_dp_link_train_info *dp_info)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(dp_info->encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	u8 पंचांगp;

	/* घातer up the sink */
	amdgpu_atombios_dp_set_rx_घातer_state(dp_info->connector, DP_SET_POWER_D0);

	/* possibly enable करोwnspपढ़ो on the sink */
	अगर (dp_info->dpcd[3] & 0x1)
		drm_dp_dpcd_ग_लिखोb(dp_info->aux,
				   DP_DOWNSPREAD_CTRL, DP_SPREAD_AMP_0_5);
	अन्यथा
		drm_dp_dpcd_ग_लिखोb(dp_info->aux,
				   DP_DOWNSPREAD_CTRL, 0);

	अगर (dig->panel_mode == DP_PANEL_MODE_INTERNAL_DP2_MODE)
		drm_dp_dpcd_ग_लिखोb(dp_info->aux, DP_EDP_CONFIGURATION_SET, 1);

	/* set the lane count on the sink */
	पंचांगp = dp_info->dp_lane_count;
	अगर (drm_dp_enhanced_frame_cap(dp_info->dpcd))
		पंचांगp |= DP_LANE_COUNT_ENHANCED_FRAME_EN;
	drm_dp_dpcd_ग_लिखोb(dp_info->aux, DP_LANE_COUNT_SET, पंचांगp);

	/* set the link rate on the sink */
	पंचांगp = drm_dp_link_rate_to_bw_code(dp_info->dp_घड़ी);
	drm_dp_dpcd_ग_लिखोb(dp_info->aux, DP_LINK_BW_SET, पंचांगp);

	/* start training on the source */
	amdgpu_atombios_encoder_setup_dig_encoder(dp_info->encoder,
					   ATOM_ENCODER_CMD_DP_LINK_TRAINING_START, 0);

	/* disable the training pattern on the sink */
	drm_dp_dpcd_ग_लिखोb(dp_info->aux,
			   DP_TRAINING_PATTERN_SET,
			   DP_TRAINING_PATTERN_DISABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक
amdgpu_atombios_dp_link_train_finish(काष्ठा amdgpu_atombios_dp_link_train_info *dp_info)
अणु
	udelay(400);

	/* disable the training pattern on the sink */
	drm_dp_dpcd_ग_लिखोb(dp_info->aux,
			   DP_TRAINING_PATTERN_SET,
			   DP_TRAINING_PATTERN_DISABLE);

	/* disable the training pattern on the source */
	amdgpu_atombios_encoder_setup_dig_encoder(dp_info->encoder,
					   ATOM_ENCODER_CMD_DP_LINK_TRAINING_COMPLETE, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
amdgpu_atombios_dp_link_train_cr(काष्ठा amdgpu_atombios_dp_link_train_info *dp_info)
अणु
	bool घड़ी_recovery;
	u8 voltage;
	पूर्णांक i;

	amdgpu_atombios_dp_set_tp(dp_info, DP_TRAINING_PATTERN_1);
	स_रखो(dp_info->train_set, 0, 4);
	amdgpu_atombios_dp_update_vs_emph(dp_info);

	udelay(400);

	/* घड़ी recovery loop */
	घड़ी_recovery = false;
	dp_info->tries = 0;
	voltage = 0xff;
	जबतक (1) अणु
		drm_dp_link_train_घड़ी_recovery_delay(dp_info->dpcd);

		अगर (drm_dp_dpcd_पढ़ो_link_status(dp_info->aux,
						 dp_info->link_status) <= 0) अणु
			DRM_ERROR("displayport link status failed\n");
			अवरोध;
		पूर्ण

		अगर (drm_dp_घड़ी_recovery_ok(dp_info->link_status, dp_info->dp_lane_count)) अणु
			घड़ी_recovery = true;
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < dp_info->dp_lane_count; i++) अणु
			अगर ((dp_info->train_set[i] & DP_TRAIN_MAX_SWING_REACHED) == 0)
				अवरोध;
		पूर्ण
		अगर (i == dp_info->dp_lane_count) अणु
			DRM_ERROR("clock recovery reached max voltage\n");
			अवरोध;
		पूर्ण

		अगर ((dp_info->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK) == voltage) अणु
			++dp_info->tries;
			अगर (dp_info->tries == 5) अणु
				DRM_ERROR("clock recovery tried 5 times\n");
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			dp_info->tries = 0;

		voltage = dp_info->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK;

		/* Compute new train_set as requested by sink */
		amdgpu_atombios_dp_get_adjust_train(dp_info->link_status, dp_info->dp_lane_count,
					     dp_info->train_set);

		amdgpu_atombios_dp_update_vs_emph(dp_info);
	पूर्ण
	अगर (!घड़ी_recovery) अणु
		DRM_ERROR("clock recovery failed\n");
		वापस -1;
	पूर्ण अन्यथा अणु
		DRM_DEBUG_KMS("clock recovery at voltage %d pre-emphasis %d\n",
			  dp_info->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK,
			  (dp_info->train_set[0] & DP_TRAIN_PRE_EMPHASIS_MASK) >>
			  DP_TRAIN_PRE_EMPHASIS_SHIFT);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
amdgpu_atombios_dp_link_train_ce(काष्ठा amdgpu_atombios_dp_link_train_info *dp_info)
अणु
	bool channel_eq;

	अगर (dp_info->tp3_supported)
		amdgpu_atombios_dp_set_tp(dp_info, DP_TRAINING_PATTERN_3);
	अन्यथा
		amdgpu_atombios_dp_set_tp(dp_info, DP_TRAINING_PATTERN_2);

	/* channel equalization loop */
	dp_info->tries = 0;
	channel_eq = false;
	जबतक (1) अणु
		drm_dp_link_train_channel_eq_delay(dp_info->dpcd);

		अगर (drm_dp_dpcd_पढ़ो_link_status(dp_info->aux,
						 dp_info->link_status) <= 0) अणु
			DRM_ERROR("displayport link status failed\n");
			अवरोध;
		पूर्ण

		अगर (drm_dp_channel_eq_ok(dp_info->link_status, dp_info->dp_lane_count)) अणु
			channel_eq = true;
			अवरोध;
		पूर्ण

		/* Try 5 बार */
		अगर (dp_info->tries > 5) अणु
			DRM_ERROR("channel eq failed: 5 tries\n");
			अवरोध;
		पूर्ण

		/* Compute new train_set as requested by sink */
		amdgpu_atombios_dp_get_adjust_train(dp_info->link_status, dp_info->dp_lane_count,
					     dp_info->train_set);

		amdgpu_atombios_dp_update_vs_emph(dp_info);
		dp_info->tries++;
	पूर्ण

	अगर (!channel_eq) अणु
		DRM_ERROR("channel eq failed\n");
		वापस -1;
	पूर्ण अन्यथा अणु
		DRM_DEBUG_KMS("channel eq at voltage %d pre-emphasis %d\n",
			  dp_info->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK,
			  (dp_info->train_set[0] & DP_TRAIN_PRE_EMPHASIS_MASK)
			  >> DP_TRAIN_PRE_EMPHASIS_SHIFT);
		वापस 0;
	पूर्ण
पूर्ण

व्योम amdgpu_atombios_dp_link_train(काष्ठा drm_encoder *encoder,
			    काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_connector *amdgpu_connector;
	काष्ठा amdgpu_connector_atom_dig *dig_connector;
	काष्ठा amdgpu_atombios_dp_link_train_info dp_info;
	u8 पंचांगp;

	अगर (!amdgpu_encoder->enc_priv)
		वापस;

	amdgpu_connector = to_amdgpu_connector(connector);
	अगर (!amdgpu_connector->con_priv)
		वापस;
	dig_connector = amdgpu_connector->con_priv;

	अगर ((dig_connector->dp_sink_type != CONNECTOR_OBJECT_ID_DISPLAYPORT) &&
	    (dig_connector->dp_sink_type != CONNECTOR_OBJECT_ID_eDP))
		वापस;

	अगर (drm_dp_dpcd_पढ़ोb(&amdgpu_connector->ddc_bus->aux, DP_MAX_LANE_COUNT, &पंचांगp)
	    == 1) अणु
		अगर (पंचांगp & DP_TPS3_SUPPORTED)
			dp_info.tp3_supported = true;
		अन्यथा
			dp_info.tp3_supported = false;
	पूर्ण अन्यथा अणु
		dp_info.tp3_supported = false;
	पूर्ण

	स_नकल(dp_info.dpcd, dig_connector->dpcd, DP_RECEIVER_CAP_SIZE);
	dp_info.adev = adev;
	dp_info.encoder = encoder;
	dp_info.connector = connector;
	dp_info.dp_lane_count = dig_connector->dp_lane_count;
	dp_info.dp_घड़ी = dig_connector->dp_घड़ी;
	dp_info.aux = &amdgpu_connector->ddc_bus->aux;

	अगर (amdgpu_atombios_dp_link_train_init(&dp_info))
		जाओ करोne;
	अगर (amdgpu_atombios_dp_link_train_cr(&dp_info))
		जाओ करोne;
	अगर (amdgpu_atombios_dp_link_train_ce(&dp_info))
		जाओ करोne;
करोne:
	अगर (amdgpu_atombios_dp_link_train_finish(&dp_info))
		वापस;
पूर्ण
