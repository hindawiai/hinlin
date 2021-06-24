<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#समावेश <linux/slab.h>

#समावेश "dm_services.h"
#समावेश "atomfirmware.h"
#समावेश "dm_helpers.h"
#समावेश "dc.h"
#समावेश "grph_object_id.h"
#समावेश "gpio_service_interface.h"
#समावेश "core_status.h"
#समावेश "dc_link_dp.h"
#समावेश "dc_link_ddc.h"
#समावेश "link_hwss.h"
#समावेश "opp.h"

#समावेश "link_encoder.h"
#समावेश "hw_sequencer.h"
#समावेश "resource.h"
#समावेश "abm.h"
#समावेश "fixed31_32.h"
#समावेश "dpcd_defs.h"
#समावेश "dmcu.h"
#समावेश "hw/clk_mgr.h"
#समावेश "dce/dmub_psr.h"
#समावेश "dmub/dmub_srv.h"
#समावेश "inc/hw/panel_cntl.h"

#घोषणा DC_LOGGER_INIT(logger)

#घोषणा LINK_INFO(...) \
	DC_LOG_HW_HOTPLUG(  \
		__VA_ARGS__)

#घोषणा RETIMER_REDRIVER_INFO(...) \
	DC_LOG_RETIMER_REDRIVER(  \
		__VA_ARGS__)
/*******************************************************************************
 * Private काष्ठाures
 ******************************************************************************/

क्रमागत अणु
	PEAK_FACTOR_X1000 = 1006,
	/*
	 * Some receivers fail to train on first try and are good
	 * on subsequent tries. 2 retries should be plenty. If we
	 * करोn't have a successful training then we don't expect to
	 * ever get one.
	 */
	LINK_TRAINING_MAX_VERIFY_RETRY = 2
पूर्ण;

/*******************************************************************************
 * Private functions
 ******************************************************************************/
अटल व्योम dc_link_deकाष्ठा(काष्ठा dc_link *link)
अणु
	पूर्णांक i;

	अगर (link->hpd_gpio) अणु
		dal_gpio_destroy_irq(&link->hpd_gpio);
		link->hpd_gpio = शून्य;
	पूर्ण

	अगर (link->ddc)
		dal_ddc_service_destroy(&link->ddc);

	अगर (link->panel_cntl)
		link->panel_cntl->funcs->destroy(&link->panel_cntl);

	अगर (link->link_enc) अणु
		/* Update link encoder resource tracking variables. These are used क्रम
		 * the dynamic assignment of link encoders to streams. Virtual links
		 * are not asचिन्हित encoder resources on creation.
		 */
		अगर (link->link_id.id != CONNECTOR_ID_VIRTUAL) अणु
			link->dc->res_pool->link_encoders[link->eng_id - ENGINE_ID_DIGA] = शून्य;
			link->dc->res_pool->dig_link_enc_count--;
		पूर्ण
		link->link_enc->funcs->destroy(&link->link_enc);
	पूर्ण

	अगर (link->local_sink)
		dc_sink_release(link->local_sink);

	क्रम (i = 0; i < link->sink_count; ++i)
		dc_sink_release(link->remote_sinks[i]);
पूर्ण

काष्ठा gpio *get_hpd_gpio(काष्ठा dc_bios *dcb,
			  काष्ठा graphics_object_id link_id,
			  काष्ठा gpio_service *gpio_service)
अणु
	क्रमागत bp_result bp_result;
	काष्ठा graphics_object_hpd_info hpd_info;
	काष्ठा gpio_pin_info pin_info;

	अगर (dcb->funcs->get_hpd_info(dcb, link_id, &hpd_info) != BP_RESULT_OK)
		वापस शून्य;

	bp_result = dcb->funcs->get_gpio_pin_info(dcb,
		hpd_info.hpd_पूर्णांक_gpio_uid, &pin_info);

	अगर (bp_result != BP_RESULT_OK) अणु
		ASSERT(bp_result == BP_RESULT_NORECORD);
		वापस शून्य;
	पूर्ण

	वापस dal_gpio_service_create_irq(gpio_service,
					   pin_info.offset,
					   pin_info.mask);
पूर्ण

/*
 *  Function: program_hpd_filter
 *
 *  @brief
 *     Programs HPD filter on associated HPD line
 *
 *  @param [in] delay_on_connect_in_ms: Connect filter समयout
 *  @param [in] delay_on_disconnect_in_ms: Disconnect filter समयout
 *
 *  @वापस
 *     true on success, false otherwise
 */
अटल bool program_hpd_filter(स्थिर काष्ठा dc_link *link)
अणु
	bool result = false;
	काष्ठा gpio *hpd;
	पूर्णांक delay_on_connect_in_ms = 0;
	पूर्णांक delay_on_disconnect_in_ms = 0;

	अगर (link->is_hpd_filter_disabled)
		वापस false;
	/* Verअगरy feature is supported */
	चयन (link->connector_संकेत) अणु
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		/* Program hpd filter */
		delay_on_connect_in_ms = 500;
		delay_on_disconnect_in_ms = 100;
		अवरोध;
	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		/* Program hpd filter to allow DP संकेत to settle */
		/* 500:	not able to detect MST <-> SST चयन as HPD is low क्रम
		 * only 100ms on DELL U2413
		 * 0: some passive करोngle still show aux mode instead of i2c
		 * 20-50: not enough to hide bouncing HPD with passive करोngle.
		 * also see पूर्णांकermittent i2c पढ़ो issues.
		 */
		delay_on_connect_in_ms = 80;
		delay_on_disconnect_in_ms = 0;
		अवरोध;
	हाल SIGNAL_TYPE_LVDS:
	हाल SIGNAL_TYPE_EDP:
	शेष:
		/* Don't program hpd filter */
		वापस false;
	पूर्ण

	/* Obtain HPD handle */
	hpd = get_hpd_gpio(link->ctx->dc_bios, link->link_id,
			   link->ctx->gpio_service);

	अगर (!hpd)
		वापस result;

	/* Setup HPD filtering */
	अगर (dal_gpio_खोलो(hpd, GPIO_MODE_INTERRUPT) == GPIO_RESULT_OK) अणु
		काष्ठा gpio_hpd_config config;

		config.delay_on_connect = delay_on_connect_in_ms;
		config.delay_on_disconnect = delay_on_disconnect_in_ms;

		dal_irq_setup_hpd_filter(hpd, &config);

		dal_gpio_बंद(hpd);

		result = true;
	पूर्ण अन्यथा अणु
		ASSERT_CRITICAL(false);
	पूर्ण

	/* Release HPD handle */
	dal_gpio_destroy_irq(&hpd);

	वापस result;
पूर्ण

bool dc_link_रुको_क्रम_t12(काष्ठा dc_link *link)
अणु
	अगर (link->connector_संकेत == SIGNAL_TYPE_EDP && link->dc->hwss.edp_रुको_क्रम_T12) अणु
		link->dc->hwss.edp_रुको_क्रम_T12(link);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * dc_link_detect_sink() - Determine अगर there is a sink connected
 *
 * @link: poपूर्णांकer to the dc link
 * @type: Returned connection type
 * Does not detect करोwnstream devices, such as MST sinks
 * or display connected through active करोngles
 */
bool dc_link_detect_sink(काष्ठा dc_link *link, क्रमागत dc_connection_type *type)
अणु
	uपूर्णांक32_t is_hpd_high = 0;
	काष्ठा gpio *hpd_pin;

	अगर (link->connector_संकेत == SIGNAL_TYPE_LVDS) अणु
		*type = dc_connection_single;
		वापस true;
	पूर्ण

	अगर (link->connector_संकेत == SIGNAL_TYPE_EDP) अणु
		/*in हाल it is not on*/
		link->dc->hwss.edp_घातer_control(link, true);
		link->dc->hwss.edp_रुको_क्रम_hpd_पढ़ोy(link, true);
	पूर्ण

	/* toकरो: may need to lock gpio access */
	hpd_pin = get_hpd_gpio(link->ctx->dc_bios, link->link_id,
			       link->ctx->gpio_service);
	अगर (!hpd_pin)
		जाओ hpd_gpio_failure;

	dal_gpio_खोलो(hpd_pin, GPIO_MODE_INTERRUPT);
	dal_gpio_get_value(hpd_pin, &is_hpd_high);
	dal_gpio_बंद(hpd_pin);
	dal_gpio_destroy_irq(&hpd_pin);

	अगर (is_hpd_high) अणु
		*type = dc_connection_single;
		/* TODO: need to करो the actual detection */
	पूर्ण अन्यथा अणु
		*type = dc_connection_none;
	पूर्ण

	वापस true;

hpd_gpio_failure:
	वापस false;
पूर्ण

अटल क्रमागत ddc_transaction_type get_ddc_transaction_type(क्रमागत संकेत_type sink_संकेत)
अणु
	क्रमागत ddc_transaction_type transaction_type = DDC_TRANSACTION_TYPE_NONE;

	चयन (sink_संकेत) अणु
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
	हाल SIGNAL_TYPE_LVDS:
	हाल SIGNAL_TYPE_RGB:
		transaction_type = DDC_TRANSACTION_TYPE_I2C;
		अवरोध;

	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_EDP:
		transaction_type = DDC_TRANSACTION_TYPE_I2C_OVER_AUX;
		अवरोध;

	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		/* MST करोes not use I2COverAux, but there is the
		 * SPECIAL use हाल क्रम "immediate dwnstrm device
		 * access" (EPR#370830).
		 */
		transaction_type = DDC_TRANSACTION_TYPE_I2C_OVER_AUX;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस transaction_type;
पूर्ण

अटल क्रमागत संकेत_type get_basic_संकेत_type(काष्ठा graphics_object_id encoder,
					      काष्ठा graphics_object_id करोwnstream)
अणु
	अगर (करोwnstream.type == OBJECT_TYPE_CONNECTOR) अणु
		चयन (करोwnstream.id) अणु
		हाल CONNECTOR_ID_SINGLE_LINK_DVII:
			चयन (encoder.id) अणु
			हाल ENCODER_ID_INTERNAL_DAC1:
			हाल ENCODER_ID_INTERNAL_KLDSCP_DAC1:
			हाल ENCODER_ID_INTERNAL_DAC2:
			हाल ENCODER_ID_INTERNAL_KLDSCP_DAC2:
				वापस SIGNAL_TYPE_RGB;
			शेष:
				वापस SIGNAL_TYPE_DVI_SINGLE_LINK;
			पूर्ण
		अवरोध;
		हाल CONNECTOR_ID_DUAL_LINK_DVII:
		अणु
			चयन (encoder.id) अणु
			हाल ENCODER_ID_INTERNAL_DAC1:
			हाल ENCODER_ID_INTERNAL_KLDSCP_DAC1:
			हाल ENCODER_ID_INTERNAL_DAC2:
			हाल ENCODER_ID_INTERNAL_KLDSCP_DAC2:
				वापस SIGNAL_TYPE_RGB;
			शेष:
				वापस SIGNAL_TYPE_DVI_DUAL_LINK;
			पूर्ण
		पूर्ण
		अवरोध;
		हाल CONNECTOR_ID_SINGLE_LINK_DVID:
			वापस SIGNAL_TYPE_DVI_SINGLE_LINK;
		हाल CONNECTOR_ID_DUAL_LINK_DVID:
			वापस SIGNAL_TYPE_DVI_DUAL_LINK;
		हाल CONNECTOR_ID_VGA:
			वापस SIGNAL_TYPE_RGB;
		हाल CONNECTOR_ID_HDMI_TYPE_A:
			वापस SIGNAL_TYPE_HDMI_TYPE_A;
		हाल CONNECTOR_ID_LVDS:
			वापस SIGNAL_TYPE_LVDS;
		हाल CONNECTOR_ID_DISPLAY_PORT:
			वापस SIGNAL_TYPE_DISPLAY_PORT;
		हाल CONNECTOR_ID_EDP:
			वापस SIGNAL_TYPE_EDP;
		शेष:
			वापस SIGNAL_TYPE_NONE;
		पूर्ण
	पूर्ण अन्यथा अगर (करोwnstream.type == OBJECT_TYPE_ENCODER) अणु
		चयन (करोwnstream.id) अणु
		हाल ENCODER_ID_EXTERNAL_NUTMEG:
		हाल ENCODER_ID_EXTERNAL_TRAVIS:
			वापस SIGNAL_TYPE_DISPLAY_PORT;
		शेष:
			वापस SIGNAL_TYPE_NONE;
		पूर्ण
	पूर्ण

	वापस SIGNAL_TYPE_NONE;
पूर्ण

/*
 * dc_link_is_dp_sink_present() - Check अगर there is a native DP
 * or passive DP-HDMI करोngle connected
 */
bool dc_link_is_dp_sink_present(काष्ठा dc_link *link)
अणु
	क्रमागत gpio_result gpio_result;
	uपूर्णांक32_t घड़ी_pin = 0;
	uपूर्णांक8_t retry = 0;
	काष्ठा ddc *ddc;

	क्रमागत connector_id connector_id =
		dal_graphics_object_id_get_connector_id(link->link_id);

	bool present =
		((connector_id == CONNECTOR_ID_DISPLAY_PORT) ||
		(connector_id == CONNECTOR_ID_EDP));

	ddc = dal_ddc_service_get_ddc_pin(link->ddc);

	अगर (!ddc) अणु
		BREAK_TO_DEBUGGER();
		वापस present;
	पूर्ण

	/* Open GPIO and set it to I2C mode */
	/* Note: this GpioMode_Input will be converted
	 * to GpioConfigType_I2cAuxDualMode in GPIO component,
	 * which indicates we need additional delay
	 */

	अगर (dal_ddc_खोलो(ddc, GPIO_MODE_INPUT,
			 GPIO_DDC_CONFIG_TYPE_MODE_I2C) != GPIO_RESULT_OK) अणु
		dal_ddc_बंद(ddc);

		वापस present;
	पूर्ण

	/*
	 * Read GPIO: DP sink is present अगर both घड़ी and data pins are zero
	 *
	 * [W/A] plug-unplug DP cable, someबार customer board has
	 * one लघु pulse on clk_pin(1V, < 1ms). DP will be config to HDMI/DVI
	 * then monitor can't br light up. Add retry 3 बार
	 * But in real passive करोngle, it need additional 3ms to detect
	 */
	करो अणु
		gpio_result = dal_gpio_get_value(ddc->pin_घड़ी, &घड़ी_pin);
		ASSERT(gpio_result == GPIO_RESULT_OK);
		अगर (घड़ी_pin)
			udelay(1000);
		अन्यथा
			अवरोध;
	पूर्ण जबतक (retry++ < 3);

	present = (gpio_result == GPIO_RESULT_OK) && !घड़ी_pin;

	dal_ddc_बंद(ddc);

	वापस present;
पूर्ण

/*
 * @brief
 * Detect output sink type
 */
अटल क्रमागत संकेत_type link_detect_sink(काष्ठा dc_link *link,
					 क्रमागत dc_detect_reason reason)
अणु
	क्रमागत संकेत_type result = get_basic_संकेत_type(link->link_enc->id,
							link->link_id);

	/* Internal digital encoder will detect only करोngles
	 * that require digital संकेत
	 */

	/* Detection mechanism is dअगरferent
	 * क्रम dअगरferent native connectors.
	 * LVDS connector supports only LVDS संकेत;
	 * PCIE is a bus slot, the actual connector needs to be detected first;
	 * eDP connector supports only eDP संकेत;
	 * HDMI should check straps क्रम audio
	 */

	/* PCIE detects the actual connector on add-on board */
	अगर (link->link_id.id == CONNECTOR_ID_PCIE) अणु
		/* ZAZTODO implement PCIE add-on card detection */
	पूर्ण

	चयन (link->link_id.id) अणु
	हाल CONNECTOR_ID_HDMI_TYPE_A: अणु
		/* check audio support:
		 * अगर native HDMI is not supported, चयन to DVI
		 */
		काष्ठा audio_support *aud_support =
					&link->dc->res_pool->audio_support;

		अगर (!aud_support->hdmi_audio_native)
			अगर (link->link_id.id == CONNECTOR_ID_HDMI_TYPE_A)
				result = SIGNAL_TYPE_DVI_SINGLE_LINK;
	पूर्ण
	अवरोध;
	हाल CONNECTOR_ID_DISPLAY_PORT: अणु
		/* DP HPD लघु pulse. Passive DP करोngle will not
		 * have लघु pulse
		 */
		अगर (reason != DETECT_REASON_HPDRX) अणु
			/* Check whether DP संकेत detected: अगर not -
			 * we assume संकेत is DVI; it could be corrected
			 * to HDMI after करोngle detection
			 */
			अगर (!dm_helpers_is_dp_sink_present(link))
				result = SIGNAL_TYPE_DVI_SINGLE_LINK;
		पूर्ण
	पूर्ण
	अवरोध;
	शेष:
	अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल क्रमागत संकेत_type decide_संकेत_from_strap_and_करोngle_type(क्रमागत display_करोngle_type करोngle_type,
								 काष्ठा audio_support *audio_support)
अणु
	क्रमागत संकेत_type संकेत = SIGNAL_TYPE_NONE;

	चयन (करोngle_type) अणु
	हाल DISPLAY_DONGLE_DP_HDMI_DONGLE:
		अगर (audio_support->hdmi_audio_on_करोngle)
			संकेत = SIGNAL_TYPE_HDMI_TYPE_A;
		अन्यथा
			संकेत = SIGNAL_TYPE_DVI_SINGLE_LINK;
		अवरोध;
	हाल DISPLAY_DONGLE_DP_DVI_DONGLE:
		संकेत = SIGNAL_TYPE_DVI_SINGLE_LINK;
		अवरोध;
	हाल DISPLAY_DONGLE_DP_HDMI_MISMATCHED_DONGLE:
		अगर (audio_support->hdmi_audio_native)
			संकेत =  SIGNAL_TYPE_HDMI_TYPE_A;
		अन्यथा
			संकेत = SIGNAL_TYPE_DVI_SINGLE_LINK;
		अवरोध;
	शेष:
		संकेत = SIGNAL_TYPE_NONE;
		अवरोध;
	पूर्ण

	वापस संकेत;
पूर्ण

अटल क्रमागत संकेत_type dp_passive_करोngle_detection(काष्ठा ddc_service *ddc,
						    काष्ठा display_sink_capability *sink_cap,
						    काष्ठा audio_support *audio_support)
अणु
	dal_ddc_service_i2c_query_dp_dual_mode_adaptor(ddc, sink_cap);

	वापस decide_संकेत_from_strap_and_करोngle_type(sink_cap->करोngle_type,
							audio_support);
पूर्ण

अटल व्योम link_disconnect_sink(काष्ठा dc_link *link)
अणु
	अगर (link->local_sink) अणु
		dc_sink_release(link->local_sink);
		link->local_sink = शून्य;
	पूर्ण

	link->dpcd_sink_count = 0;
पूर्ण

अटल व्योम link_disconnect_remap(काष्ठा dc_sink *prev_sink, काष्ठा dc_link *link)
अणु
	dc_sink_release(link->local_sink);
	link->local_sink = prev_sink;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
bool dc_link_is_hdcp14(काष्ठा dc_link *link, क्रमागत संकेत_type संकेत)
अणु
	bool ret = false;

	चयन (संकेत)	अणु
	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		ret = link->hdcp_caps.bcaps.bits.HDCP_CAPABLE;
		अवरोध;
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
	/* HDMI करोesn't tell us its HDCP(1.4) capability, so assume to always be capable,
	 * we can poll क्रम bksv but some displays have an issue with this. Since its so rare
	 * क्रम a display to not be 1.4 capable, this assumtion is ok
	 */
		ret = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

bool dc_link_is_hdcp22(काष्ठा dc_link *link, क्रमागत संकेत_type संकेत)
अणु
	bool ret = false;

	चयन (संकेत)	अणु
	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		ret = (link->hdcp_caps.bcaps.bits.HDCP_CAPABLE &&
				link->hdcp_caps.rx_caps.fields.byte0.hdcp_capable &&
				(link->hdcp_caps.rx_caps.fields.version == 0x2)) ? 1 : 0;
		अवरोध;
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		ret = (link->hdcp_caps.rx_caps.fields.version == 0x4) ? 1:0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम query_hdcp_capability(क्रमागत संकेत_type संकेत, काष्ठा dc_link *link)
अणु
	काष्ठा hdcp_protection_message msg22;
	काष्ठा hdcp_protection_message msg14;

	स_रखो(&msg22, 0, माप(काष्ठा hdcp_protection_message));
	स_रखो(&msg14, 0, माप(काष्ठा hdcp_protection_message));
	स_रखो(link->hdcp_caps.rx_caps.raw, 0,
		माप(link->hdcp_caps.rx_caps.raw));

	अगर ((link->connector_संकेत == SIGNAL_TYPE_DISPLAY_PORT &&
			link->ddc->transaction_type ==
			DDC_TRANSACTION_TYPE_I2C_OVER_AUX) ||
			link->connector_संकेत == SIGNAL_TYPE_EDP) अणु
		msg22.data = link->hdcp_caps.rx_caps.raw;
		msg22.length = माप(link->hdcp_caps.rx_caps.raw);
		msg22.msg_id = HDCP_MESSAGE_ID_RX_CAPS;
	पूर्ण अन्यथा अणु
		msg22.data = &link->hdcp_caps.rx_caps.fields.version;
		msg22.length = माप(link->hdcp_caps.rx_caps.fields.version);
		msg22.msg_id = HDCP_MESSAGE_ID_HDCP2VERSION;
	पूर्ण
	msg22.version = HDCP_VERSION_22;
	msg22.link = HDCP_LINK_PRIMARY;
	msg22.max_retries = 5;
	dc_process_hdcp_msg(संकेत, link, &msg22);

	अगर (संकेत == SIGNAL_TYPE_DISPLAY_PORT || संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST) अणु
		msg14.data = &link->hdcp_caps.bcaps.raw;
		msg14.length = माप(link->hdcp_caps.bcaps.raw);
		msg14.msg_id = HDCP_MESSAGE_ID_READ_BCAPS;
		msg14.version = HDCP_VERSION_14;
		msg14.link = HDCP_LINK_PRIMARY;
		msg14.max_retries = 5;

		dc_process_hdcp_msg(संकेत, link, &msg14);
	पूर्ण

पूर्ण
#पूर्ण_अगर

अटल व्योम पढ़ो_current_link_settings_on_detect(काष्ठा dc_link *link)
अणु
	जोड़ lane_count_set lane_count_set = अणु अणु0पूर्ण पूर्ण;
	uपूर्णांक8_t link_bw_set;
	uपूर्णांक8_t link_rate_set;
	uपूर्णांक32_t पढ़ो_dpcd_retry_cnt = 10;
	क्रमागत dc_status status = DC_ERROR_UNEXPECTED;
	पूर्णांक i;
	जोड़ max_करोwn_spपढ़ो max_करोwn_spपढ़ो = अणु अणु0पूर्ण पूर्ण;

	// Read DPCD 00101h to find out the number of lanes currently set
	क्रम (i = 0; i < पढ़ो_dpcd_retry_cnt; i++) अणु
		status = core_link_पढ़ो_dpcd(link,
					     DP_LANE_COUNT_SET,
					     &lane_count_set.raw,
					     माप(lane_count_set));
		/* First DPCD पढ़ो after VDD ON can fail अगर the particular board
		 * करोes not have HPD pin wired correctly. So अगर DPCD पढ़ो fails,
		 * which it should never happen, retry a few बार. Target worst
		 * हाल scenario of 80 ms.
		 */
		अगर (status == DC_OK) अणु
			link->cur_link_settings.lane_count =
					lane_count_set.bits.LANE_COUNT_SET;
			अवरोध;
		पूर्ण

		msleep(8);
	पूर्ण

	// Read DPCD 00100h to find अगर standard link rates are set
	core_link_पढ़ो_dpcd(link, DP_LINK_BW_SET,
			    &link_bw_set, माप(link_bw_set));

	अगर (link_bw_set == 0) अणु
		अगर (link->connector_संकेत == SIGNAL_TYPE_EDP) अणु
			/* If standard link rates are not being used,
			 * Read DPCD 00115h to find the edp link rate set used
			 */
			core_link_पढ़ो_dpcd(link, DP_LINK_RATE_SET,
					    &link_rate_set, माप(link_rate_set));

			// edp_supported_link_rates_count = 0 क्रम DP
			अगर (link_rate_set < link->dpcd_caps.edp_supported_link_rates_count) अणु
				link->cur_link_settings.link_rate =
					link->dpcd_caps.edp_supported_link_rates[link_rate_set];
				link->cur_link_settings.link_rate_set = link_rate_set;
				link->cur_link_settings.use_link_rate_set = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			// Link Rate not found. Seamless boot may not work.
			ASSERT(false);
		पूर्ण
	पूर्ण अन्यथा अणु
		link->cur_link_settings.link_rate = link_bw_set;
		link->cur_link_settings.use_link_rate_set = false;
	पूर्ण
	// Read DPCD 00003h to find the max करोwn spपढ़ो.
	core_link_पढ़ो_dpcd(link, DP_MAX_DOWNSPREAD,
			    &max_करोwn_spपढ़ो.raw, माप(max_करोwn_spपढ़ो));
	link->cur_link_settings.link_spपढ़ो =
		max_करोwn_spपढ़ो.bits.MAX_DOWN_SPREAD ?
		LINK_SPREAD_05_DOWNSPREAD_30KHZ : LINK_SPREAD_DISABLED;
पूर्ण

अटल bool detect_dp(काष्ठा dc_link *link,
		      काष्ठा display_sink_capability *sink_caps,
		      bool *converter_disable_audio,
		      काष्ठा audio_support *audio_support,
		      क्रमागत dc_detect_reason reason)
अणु
	bool boot = false;

	sink_caps->संकेत = link_detect_sink(link, reason);
	sink_caps->transaction_type =
		get_ddc_transaction_type(sink_caps->संकेत);

	अगर (sink_caps->transaction_type == DDC_TRANSACTION_TYPE_I2C_OVER_AUX) अणु
		sink_caps->संकेत = SIGNAL_TYPE_DISPLAY_PORT;
		अगर (!detect_dp_sink_caps(link))
			वापस false;
		अगर (is_mst_supported(link)) अणु
			sink_caps->संकेत = SIGNAL_TYPE_DISPLAY_PORT_MST;
			link->type = dc_connection_mst_branch;

			dal_ddc_service_set_transaction_type(link->ddc,
							     sink_caps->transaction_type);

#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
			/* In हाल of fallback to SST when topology discovery below fails
			 * HDCP caps will be querried again later by the upper layer (caller
			 * of this function). */
			query_hdcp_capability(SIGNAL_TYPE_DISPLAY_PORT_MST, link);
#पूर्ण_अगर
			/*
			 * This call will initiate MST topology discovery. Which
			 * will detect MST ports and add new DRM connector DRM
			 * framework. Then पढ़ो EDID via remote i2c over aux. In
			 * the end, will notअगरy DRM detect result and save EDID
			 * पूर्णांकo DRM framework.
			 *
			 * .detect is called by .fill_modes.
			 * .fill_modes is called by user mode ioctl
			 * DRM_IOCTL_MODE_GETCONNECTOR.
			 *
			 * .get_modes is called by .fill_modes.
			 *
			 * call .get_modes, AMDGPU DM implementation will create
			 * new dc_sink and add to dc_link. For दीर्घ HPD plug
			 * in/out, MST has its own handle.
			 *
			 * Thereक्रमe, just after dc_create, link->sink is not
			 * created क्रम MST until user mode app calls
			 * DRM_IOCTL_MODE_GETCONNECTOR.
			 *
			 * Need check ->sink usages in हाल ->sink = शून्य
			 * TODO: s3 resume check
			 */
			अगर (reason == DETECT_REASON_BOOT)
				boot = true;

			dm_helpers_dp_update_branch_info(link->ctx, link);

			अगर (!dm_helpers_dp_mst_start_top_mgr(link->ctx,
							     link, boot)) अणु
				/* MST not supported */
				link->type = dc_connection_single;
				sink_caps->संकेत = SIGNAL_TYPE_DISPLAY_PORT;
			पूर्ण
		पूर्ण

		अगर (link->type != dc_connection_mst_branch &&
		    is_dp_active_करोngle(link)) अणु
			/* DP active करोngles */
			link->type = dc_connection_active_करोngle;
			अगर (!link->dpcd_caps.sink_count.bits.SINK_COUNT) अणु
				/*
				 * active करोngle unplug processing क्रम लघु irq
				 */
				link_disconnect_sink(link);
				वापस true;
			पूर्ण

			अगर (link->dpcd_caps.करोngle_type !=
			    DISPLAY_DONGLE_DP_HDMI_CONVERTER)
				*converter_disable_audio = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* DP passive करोngles */
		sink_caps->संकेत = dp_passive_करोngle_detection(link->ddc,
								sink_caps,
								audio_support);
		link->dpcd_caps.करोngle_type = sink_caps->करोngle_type;
	पूर्ण

	वापस true;
पूर्ण

अटल bool is_same_edid(काष्ठा dc_edid *old_edid, काष्ठा dc_edid *new_edid)
अणु
	अगर (old_edid->length != new_edid->length)
		वापस false;

	अगर (new_edid->length == 0)
		वापस false;

	वापस (स_भेद(old_edid->raw_edid,
		       new_edid->raw_edid, new_edid->length) == 0);
पूर्ण

अटल bool रुको_क्रम_entering_dp_alt_mode(काष्ठा dc_link *link)
अणु
	/**
	 * something is terribly wrong अगर समय out is > 200ms. (5Hz)
	 * 500 microseconds * 400 tries us 200 ms
	 **/
	अचिन्हित पूर्णांक sleep_समय_in_microseconds = 500;
	अचिन्हित पूर्णांक tries_allowed = 400;
	bool is_in_alt_mode;
	अचिन्हित दीर्घ दीर्घ enter_बारtamp;
	अचिन्हित दीर्घ दीर्घ finish_बारtamp;
	अचिन्हित दीर्घ दीर्घ समय_प्रकारaken_in_ns;
	पूर्णांक tries_taken;

	DC_LOGGER_INIT(link->ctx->logger);

	अगर (!link->link_enc->funcs->is_in_alt_mode)
		वापस true;

	is_in_alt_mode = link->link_enc->funcs->is_in_alt_mode(link->link_enc);
	DC_LOG_WARNING("DP Alt mode state on HPD: %d\n", is_in_alt_mode);

	अगर (is_in_alt_mode)
		वापस true;

	enter_बारtamp = dm_get_बारtamp(link->ctx);

	क्रम (tries_taken = 0; tries_taken < tries_allowed; tries_taken++) अणु
		udelay(sleep_समय_in_microseconds);
		/* ask the link अगर alt mode is enabled, अगर so वापस ok */
		अगर (link->link_enc->funcs->is_in_alt_mode(link->link_enc)) अणु
			finish_बारtamp = dm_get_बारtamp(link->ctx);
			समय_प्रकारaken_in_ns =
				dm_get_elapse_समय_in_ns(link->ctx,
							 finish_बारtamp,
							 enter_बारtamp);
			DC_LOG_WARNING("Alt mode entered finished after %llu ms\n",
				       भाग_u64(समय_प्रकारaken_in_ns, 1000000));
			वापस true;
		पूर्ण
	पूर्ण
	finish_बारtamp = dm_get_बारtamp(link->ctx);
	समय_प्रकारaken_in_ns = dm_get_elapse_समय_in_ns(link->ctx, finish_बारtamp,
						    enter_बारtamp);
	DC_LOG_WARNING("Alt mode has timed out after %llu ms\n",
		       भाग_u64(समय_प्रकारaken_in_ns, 1000000));
	वापस false;
पूर्ण

/*
 * dc_link_detect() - Detect अगर a sink is attached to a given link
 *
 * link->local_sink is created or destroyed as needed.
 *
 * This करोes not create remote sinks but will trigger DM
 * to start MST detection अगर a branch is detected.
 */
अटल bool dc_link_detect_helper(काष्ठा dc_link *link,
				  क्रमागत dc_detect_reason reason)
अणु
	काष्ठा dc_sink_init_data sink_init_data = अणु 0 पूर्ण;
	काष्ठा display_sink_capability sink_caps = अणु 0 पूर्ण;
	uपूर्णांक8_t i;
	bool converter_disable_audio = false;
	काष्ठा audio_support *aud_support = &link->dc->res_pool->audio_support;
	bool same_edid = false;
	क्रमागत dc_edid_status edid_status;
	काष्ठा dc_context *dc_ctx = link->ctx;
	काष्ठा dc_sink *sink = शून्य;
	काष्ठा dc_sink *prev_sink = शून्य;
	काष्ठा dpcd_caps prev_dpcd_caps;
	bool same_dpcd = true;
	क्रमागत dc_connection_type new_connection_type = dc_connection_none;
	क्रमागत dc_connection_type pre_connection_type = dc_connection_none;
	bool perक्रमm_dp_seamless_boot = false;
	स्थिर uपूर्णांक32_t post_oui_delay = 30; // 30ms

	DC_LOGGER_INIT(link->ctx->logger);

	अगर (dc_is_भव_संकेत(link->connector_संकेत))
		वापस false;

	अगर ((link->connector_संकेत == SIGNAL_TYPE_LVDS ||
	     link->connector_संकेत == SIGNAL_TYPE_EDP) &&
	    link->local_sink) अणु
		// need to re-ग_लिखो OUI and brightness in resume हाल
		अगर (link->connector_संकेत == SIGNAL_TYPE_EDP) अणु
			dpcd_set_source_specअगरic_data(link);
			msleep(post_oui_delay);
			dc_link_set_शेष_brightness_aux(link);
			//TODO: use cached
		पूर्ण

		वापस true;
	पूर्ण

	अगर (!dc_link_detect_sink(link, &new_connection_type)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	prev_sink = link->local_sink;
	अगर (prev_sink) अणु
		dc_sink_retain(prev_sink);
		स_नकल(&prev_dpcd_caps, &link->dpcd_caps, माप(काष्ठा dpcd_caps));
	पूर्ण

	link_disconnect_sink(link);
	अगर (new_connection_type != dc_connection_none) अणु
		pre_connection_type = link->type;
		link->type = new_connection_type;
		link->link_state_valid = false;

		/* From Disconnected-to-Connected. */
		चयन (link->connector_संकेत) अणु
		हाल SIGNAL_TYPE_HDMI_TYPE_A: अणु
			sink_caps.transaction_type = DDC_TRANSACTION_TYPE_I2C;
			अगर (aud_support->hdmi_audio_native)
				sink_caps.संकेत = SIGNAL_TYPE_HDMI_TYPE_A;
			अन्यथा
				sink_caps.संकेत = SIGNAL_TYPE_DVI_SINGLE_LINK;
			अवरोध;
		पूर्ण

		हाल SIGNAL_TYPE_DVI_SINGLE_LINK: अणु
			sink_caps.transaction_type = DDC_TRANSACTION_TYPE_I2C;
			sink_caps.संकेत = SIGNAL_TYPE_DVI_SINGLE_LINK;
			अवरोध;
		पूर्ण

		हाल SIGNAL_TYPE_DVI_DUAL_LINK: अणु
			sink_caps.transaction_type = DDC_TRANSACTION_TYPE_I2C;
			sink_caps.संकेत = SIGNAL_TYPE_DVI_DUAL_LINK;
			अवरोध;
		पूर्ण

		हाल SIGNAL_TYPE_LVDS: अणु
			sink_caps.transaction_type = DDC_TRANSACTION_TYPE_I2C;
			sink_caps.संकेत = SIGNAL_TYPE_LVDS;
			अवरोध;
		पूर्ण

		हाल SIGNAL_TYPE_EDP: अणु
			पढ़ो_current_link_settings_on_detect(link);

			detect_edp_sink_caps(link);
			पढ़ो_current_link_settings_on_detect(link);
			sink_caps.transaction_type = DDC_TRANSACTION_TYPE_I2C_OVER_AUX;
			sink_caps.संकेत = SIGNAL_TYPE_EDP;
			अवरोध;
		पूर्ण

		हाल SIGNAL_TYPE_DISPLAY_PORT: अणु
			/* wa HPD high coming too early*/
			अगर (link->link_enc->features.flags.bits.DP_IS_USB_C == 1) अणु
				/* अगर alt mode बार out, वापस false */
				अगर (!रुको_क्रम_entering_dp_alt_mode(link))
					वापस false;
			पूर्ण

			अगर (!detect_dp(link, &sink_caps,
				       &converter_disable_audio,
				       aud_support, reason)) अणु
				अगर (prev_sink)
					dc_sink_release(prev_sink);
				वापस false;
			पूर्ण

			// Check अगर dpcp block is the same
			अगर (prev_sink) अणु
				अगर (स_भेद(&link->dpcd_caps, &prev_dpcd_caps,
					   माप(काष्ठा dpcd_caps)))
					same_dpcd = false;
			पूर्ण
			/* Active करोngle करोwnstream unplug*/
			अगर (link->type == dc_connection_active_करोngle &&
			    link->dpcd_caps.sink_count.bits.SINK_COUNT == 0) अणु
				अगर (prev_sink)
					/* Downstream unplug */
					dc_sink_release(prev_sink);
				वापस true;
			पूर्ण

			// link चयन from MST to non-MST stop topology manager
			अगर (pre_connection_type == dc_connection_mst_branch &&
				link->type != dc_connection_mst_branch) अणु
				dm_helpers_dp_mst_stop_top_mgr(link->ctx, link);
			पूर्ण

			अगर (link->type == dc_connection_mst_branch) अणु
				LINK_INFO("link=%d, mst branch is now Connected\n",
					  link->link_index);
				/* Need to setup mst link_cap काष्ठा here
				 * otherwise dc_link_detect() will leave mst link_cap
				 * empty which leads to allocate_mst_payload() has "0"
				 * pbn_per_slot value leading to exception on dc_fixpt_भाग()
				 */
				dp_verअगरy_mst_link_cap(link);

				अगर (prev_sink)
					dc_sink_release(prev_sink);
				वापस false;
			पूर्ण

			// For seamless boot, to skip verअगरy link cap, we पढ़ो UEFI settings and set them as verअगरied.
			अगर (reason == DETECT_REASON_BOOT &&
			    !dc_ctx->dc->config.घातer_करोwn_display_on_boot &&
			    link->link_status.link_active)
				perक्रमm_dp_seamless_boot = true;

			अगर (perक्रमm_dp_seamless_boot) अणु
				पढ़ो_current_link_settings_on_detect(link);
				link->verअगरied_link_cap = link->reported_link_cap;
			पूर्ण

			अवरोध;
		पूर्ण

		शेष:
			DC_ERROR("Invalid connector type! signal:%d\n",
				 link->connector_संकेत);
			अगर (prev_sink)
				dc_sink_release(prev_sink);
			वापस false;
		पूर्ण /* चयन() */

		अगर (link->dpcd_caps.sink_count.bits.SINK_COUNT)
			link->dpcd_sink_count =
				link->dpcd_caps.sink_count.bits.SINK_COUNT;
		अन्यथा
			link->dpcd_sink_count = 1;

		dal_ddc_service_set_transaction_type(link->ddc,
						     sink_caps.transaction_type);

		link->aux_mode =
			dal_ddc_service_is_in_aux_transaction_mode(link->ddc);

		sink_init_data.link = link;
		sink_init_data.sink_संकेत = sink_caps.संकेत;

		sink = dc_sink_create(&sink_init_data);
		अगर (!sink) अणु
			DC_ERROR("Failed to create sink!\n");
			अगर (prev_sink)
				dc_sink_release(prev_sink);
			वापस false;
		पूर्ण

		sink->link->करोngle_max_pix_clk = sink_caps.max_hdmi_pixel_घड़ी;
		sink->converter_disable_audio = converter_disable_audio;

		/* dc_sink_create वापसs a new reference */
		link->local_sink = sink;

		edid_status = dm_helpers_पढ़ो_local_edid(link->ctx,
							 link, sink);

		चयन (edid_status) अणु
		हाल EDID_BAD_CHECKSUM:
			DC_LOG_ERROR("EDID checksum invalid.\n");
			अवरोध;
		हाल EDID_NO_RESPONSE:
			DC_LOG_ERROR("No EDID read.\n");
			/*
			 * Abort detection क्रम non-DP connectors अगर we have
			 * no EDID
			 *
			 * DP needs to report as connected अगर HDP is high
			 * even अगर we have no EDID in order to go to
			 * fail-safe mode
			 */
			अगर (dc_is_hdmi_संकेत(link->connector_संकेत) ||
			    dc_is_dvi_संकेत(link->connector_संकेत)) अणु
				अगर (prev_sink)
					dc_sink_release(prev_sink);
				link_disconnect_sink(link);

				वापस false;
			पूर्ण
			/*
			 * Abort detection क्रम DP connectors अगर we have
			 * no EDID and connector is active converter
			 * as there are no display करोwnstream
			 *
			 */
			अगर (dc_is_dp_sst_संकेत(link->connector_संकेत) &&
				(link->dpcd_caps.करोngle_type ==
						DISPLAY_DONGLE_DP_VGA_CONVERTER ||
				link->dpcd_caps.करोngle_type ==
						DISPLAY_DONGLE_DP_DVI_CONVERTER)) अणु
				अगर (prev_sink)
					dc_sink_release(prev_sink);
				link_disconnect_sink(link);

				वापस false;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		// Check अगर edid is the same
		अगर ((prev_sink) &&
		    (edid_status == EDID_THE_SAME || edid_status == EDID_OK))
			same_edid = is_same_edid(&prev_sink->dc_edid,
						 &sink->dc_edid);

		अगर (sink->edid_caps.panel_patch.skip_scdc_overग_लिखो)
			link->ctx->dc->debug.hdmi20_disable = true;

		अगर (link->connector_संकेत == SIGNAL_TYPE_DISPLAY_PORT &&
		    sink_caps.transaction_type ==
		    DDC_TRANSACTION_TYPE_I2C_OVER_AUX) अणु
			/*
			 * TODO debug why Dell 2413 करोesn't like
			 *  two link trainings
			 */
#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
			query_hdcp_capability(sink->sink_संकेत, link);
#पूर्ण_अगर

			// verअगरy link cap क्रम SST non-seamless boot
			अगर (!perक्रमm_dp_seamless_boot)
				dp_verअगरy_link_cap_with_retries(link,
								&link->reported_link_cap,
								LINK_TRAINING_MAX_VERIFY_RETRY);
		पूर्ण अन्यथा अणु
			// If edid is the same, then discard new sink and revert back to original sink
			अगर (same_edid) अणु
				link_disconnect_remap(prev_sink, link);
				sink = prev_sink;
				prev_sink = शून्य;
			पूर्ण
#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
			query_hdcp_capability(sink->sink_संकेत, link);
#पूर्ण_अगर
		पूर्ण

		/* HDMI-DVI Dongle */
		अगर (sink->sink_संकेत == SIGNAL_TYPE_HDMI_TYPE_A &&
		    !sink->edid_caps.edid_hdmi)
			sink->sink_संकेत = SIGNAL_TYPE_DVI_SINGLE_LINK;

		/* Connectivity log: detection */
		क्रम (i = 0; i < sink->dc_edid.length / DC_EDID_BLOCK_SIZE; i++) अणु
			CONN_DATA_DETECT(link,
					 &sink->dc_edid.raw_edid[i * DC_EDID_BLOCK_SIZE],
					 DC_EDID_BLOCK_SIZE,
					 "%s: [Block %d] ", sink->edid_caps.display_name, i);
		पूर्ण

		DC_LOG_DETECTION_EDID_PARSER("%s: "
			"manufacturer_id = %X, "
			"product_id = %X, "
			"serial_number = %X, "
			"manufacture_week = %d, "
			"manufacture_year = %d, "
			"display_name = %s, "
			"speaker_flag = %d, "
			"audio_mode_count = %d\n",
			__func__,
			sink->edid_caps.manufacturer_id,
			sink->edid_caps.product_id,
			sink->edid_caps.serial_number,
			sink->edid_caps.manufacture_week,
			sink->edid_caps.manufacture_year,
			sink->edid_caps.display_name,
			sink->edid_caps.speaker_flags,
			sink->edid_caps.audio_mode_count);

		क्रम (i = 0; i < sink->edid_caps.audio_mode_count; i++) अणु
			DC_LOG_DETECTION_EDID_PARSER("%s: mode number = %d, "
				"format_code = %d, "
				"channel_count = %d, "
				"sample_rate = %d, "
				"sample_size = %d\n",
				__func__,
				i,
				sink->edid_caps.audio_modes[i].क्रमmat_code,
				sink->edid_caps.audio_modes[i].channel_count,
				sink->edid_caps.audio_modes[i].sample_rate,
				sink->edid_caps.audio_modes[i].sample_size);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* From Connected-to-Disconnected. */
		अगर (link->type == dc_connection_mst_branch) अणु
			LINK_INFO("link=%d, mst branch is now Disconnected\n",
				  link->link_index);

			dm_helpers_dp_mst_stop_top_mgr(link->ctx, link);

			link->mst_stream_alloc_table.stream_count = 0;
			स_रखो(link->mst_stream_alloc_table.stream_allocations,
			       0,
			       माप(link->mst_stream_alloc_table.stream_allocations));
		पूर्ण

		link->type = dc_connection_none;
		sink_caps.संकेत = SIGNAL_TYPE_NONE;
		/* When we unplug a passive DP-HDMI करोngle connection, करोngle_max_pix_clk
		 *  is not cleared. If we emulate a DP संकेत on this connection, it thinks
		 *  the करोngle is still there and limits the number of modes we can emulate.
		 *  Clear करोngle_max_pix_clk on disconnect to fix this
		 */
		link->करोngle_max_pix_clk = 0;
	पूर्ण

	LINK_INFO("link=%d, dc_sink_in=%p is now %s prev_sink=%p dpcd same=%d edid same=%d\n",
		  link->link_index, sink,
		  (sink_caps.संकेत ==
		   SIGNAL_TYPE_NONE ? "Disconnected" : "Connected"),
		  prev_sink, same_dpcd, same_edid);

	अगर (prev_sink)
		dc_sink_release(prev_sink);

	वापस true;
पूर्ण

bool dc_link_detect(काष्ठा dc_link *link, क्रमागत dc_detect_reason reason)
अणु
	स्थिर काष्ठा dc *dc = link->dc;
	bool ret;

	/* get out of low घातer state */
	clk_mgr_निकास_optimized_pwr_state(dc, dc->clk_mgr);

	ret = dc_link_detect_helper(link, reason);

	/* Go back to घातer optimized state */
	clk_mgr_optimize_pwr_state(dc, dc->clk_mgr);

	वापस ret;
पूर्ण

bool dc_link_get_hpd_state(काष्ठा dc_link *dc_link)
अणु
	uपूर्णांक32_t state;

	dal_gpio_lock_pin(dc_link->hpd_gpio);
	dal_gpio_get_value(dc_link->hpd_gpio, &state);
	dal_gpio_unlock_pin(dc_link->hpd_gpio);

	वापस state;
पूर्ण

अटल क्रमागत hpd_source_id get_hpd_line(काष्ठा dc_link *link)
अणु
	काष्ठा gpio *hpd;
	क्रमागत hpd_source_id hpd_id = HPD_SOURCEID_UNKNOWN;

	hpd = get_hpd_gpio(link->ctx->dc_bios, link->link_id,
			   link->ctx->gpio_service);

	अगर (hpd) अणु
		चयन (dal_irq_get_source(hpd)) अणु
		हाल DC_IRQ_SOURCE_HPD1:
			hpd_id = HPD_SOURCEID1;
		अवरोध;
		हाल DC_IRQ_SOURCE_HPD2:
			hpd_id = HPD_SOURCEID2;
		अवरोध;
		हाल DC_IRQ_SOURCE_HPD3:
			hpd_id = HPD_SOURCEID3;
		अवरोध;
		हाल DC_IRQ_SOURCE_HPD4:
			hpd_id = HPD_SOURCEID4;
		अवरोध;
		हाल DC_IRQ_SOURCE_HPD5:
			hpd_id = HPD_SOURCEID5;
		अवरोध;
		हाल DC_IRQ_SOURCE_HPD6:
			hpd_id = HPD_SOURCEID6;
		अवरोध;
		शेष:
			BREAK_TO_DEBUGGER();
		अवरोध;
		पूर्ण

		dal_gpio_destroy_irq(&hpd);
	पूर्ण

	वापस hpd_id;
पूर्ण

अटल क्रमागत channel_id get_ddc_line(काष्ठा dc_link *link)
अणु
	काष्ठा ddc *ddc;
	क्रमागत channel_id channel = CHANNEL_ID_UNKNOWN;

	ddc = dal_ddc_service_get_ddc_pin(link->ddc);

	अगर (ddc) अणु
		चयन (dal_ddc_get_line(ddc)) अणु
		हाल GPIO_DDC_LINE_DDC1:
			channel = CHANNEL_ID_DDC1;
			अवरोध;
		हाल GPIO_DDC_LINE_DDC2:
			channel = CHANNEL_ID_DDC2;
			अवरोध;
		हाल GPIO_DDC_LINE_DDC3:
			channel = CHANNEL_ID_DDC3;
			अवरोध;
		हाल GPIO_DDC_LINE_DDC4:
			channel = CHANNEL_ID_DDC4;
			अवरोध;
		हाल GPIO_DDC_LINE_DDC5:
			channel = CHANNEL_ID_DDC5;
			अवरोध;
		हाल GPIO_DDC_LINE_DDC6:
			channel = CHANNEL_ID_DDC6;
			अवरोध;
		हाल GPIO_DDC_LINE_DDC_VGA:
			channel = CHANNEL_ID_DDC_VGA;
			अवरोध;
		हाल GPIO_DDC_LINE_I2C_PAD:
			channel = CHANNEL_ID_I2C_PAD;
			अवरोध;
		शेष:
			BREAK_TO_DEBUGGER();
			अवरोध;
		पूर्ण
	पूर्ण

	वापस channel;
पूर्ण

अटल क्रमागत transmitter translate_encoder_to_transmitter(काष्ठा graphics_object_id encoder)
अणु
	चयन (encoder.id) अणु
	हाल ENCODER_ID_INTERNAL_UNIPHY:
		चयन (encoder.क्रमागत_id) अणु
		हाल ENUM_ID_1:
			वापस TRANSMITTER_UNIPHY_A;
		हाल ENUM_ID_2:
			वापस TRANSMITTER_UNIPHY_B;
		शेष:
			वापस TRANSMITTER_UNKNOWN;
		पूर्ण
	अवरोध;
	हाल ENCODER_ID_INTERNAL_UNIPHY1:
		चयन (encoder.क्रमागत_id) अणु
		हाल ENUM_ID_1:
			वापस TRANSMITTER_UNIPHY_C;
		हाल ENUM_ID_2:
			वापस TRANSMITTER_UNIPHY_D;
		शेष:
			वापस TRANSMITTER_UNKNOWN;
		पूर्ण
	अवरोध;
	हाल ENCODER_ID_INTERNAL_UNIPHY2:
		चयन (encoder.क्रमागत_id) अणु
		हाल ENUM_ID_1:
			वापस TRANSMITTER_UNIPHY_E;
		हाल ENUM_ID_2:
			वापस TRANSMITTER_UNIPHY_F;
		शेष:
			वापस TRANSMITTER_UNKNOWN;
		पूर्ण
	अवरोध;
	हाल ENCODER_ID_INTERNAL_UNIPHY3:
		चयन (encoder.क्रमागत_id) अणु
		हाल ENUM_ID_1:
			वापस TRANSMITTER_UNIPHY_G;
		शेष:
			वापस TRANSMITTER_UNKNOWN;
		पूर्ण
	अवरोध;
	हाल ENCODER_ID_EXTERNAL_NUTMEG:
		चयन (encoder.क्रमागत_id) अणु
		हाल ENUM_ID_1:
			वापस TRANSMITTER_NUTMEG_CRT;
		शेष:
			वापस TRANSMITTER_UNKNOWN;
		पूर्ण
	अवरोध;
	हाल ENCODER_ID_EXTERNAL_TRAVIS:
		चयन (encoder.क्रमागत_id) अणु
		हाल ENUM_ID_1:
			वापस TRANSMITTER_TRAVIS_CRT;
		हाल ENUM_ID_2:
			वापस TRANSMITTER_TRAVIS_LCD;
		शेष:
			वापस TRANSMITTER_UNKNOWN;
		पूर्ण
	अवरोध;
	शेष:
		वापस TRANSMITTER_UNKNOWN;
	पूर्ण
पूर्ण

अटल bool dc_link_स्थिरruct(काष्ठा dc_link *link,
			      स्थिर काष्ठा link_init_data *init_params)
अणु
	uपूर्णांक8_t i;
	काष्ठा ddc_service_init_data ddc_service_init_data = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा dc_context *dc_ctx = init_params->ctx;
	काष्ठा encoder_init_data enc_init_data = अणु 0 पूर्ण;
	काष्ठा panel_cntl_init_data panel_cntl_init_data = अणु 0 पूर्ण;
	काष्ठा पूर्णांकegrated_info *info;
	काष्ठा dc_bios *bios = init_params->dc->ctx->dc_bios;
	स्थिर काष्ठा dc_vbios_funcs *bp_funcs = bios->funcs;
	काष्ठा bp_disp_connector_caps_info disp_connect_caps_info = अणु 0 पूर्ण;

	DC_LOGGER_INIT(dc_ctx->logger);

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		जाओ create_fail;

	link->irq_source_hpd = DC_IRQ_SOURCE_INVALID;
	link->irq_source_hpd_rx = DC_IRQ_SOURCE_INVALID;

	link->link_status.dpcd_caps = &link->dpcd_caps;

	link->dc = init_params->dc;
	link->ctx = dc_ctx;
	link->link_index = init_params->link_index;

	स_रखो(&link->preferred_training_settings, 0,
	       माप(काष्ठा dc_link_training_overrides));
	स_रखो(&link->preferred_link_setting, 0,
	       माप(काष्ठा dc_link_settings));

	link->link_id =
		bios->funcs->get_connector_id(bios, init_params->connector_index);

	link->ep_type = DISPLAY_ENDPOINT_PHY;

	DC_LOG_DC("BIOS object table - link_id: %d", link->link_id.id);

	अगर (bios->funcs->get_disp_connector_caps_info) अणु
		bios->funcs->get_disp_connector_caps_info(bios, link->link_id, &disp_connect_caps_info);
		link->is_पूर्णांकernal_display = disp_connect_caps_info.INTERNAL_DISPLAY;
		DC_LOG_DC("BIOS object table - is_internal_display: %d", link->is_पूर्णांकernal_display);
	पूर्ण

	अगर (link->link_id.type != OBJECT_TYPE_CONNECTOR) अणु
		dm_output_to_console("%s: Invalid Connector ObjectID from Adapter Service for connector index:%d! type %d expected %d\n",
				     __func__, init_params->connector_index,
				     link->link_id.type, OBJECT_TYPE_CONNECTOR);
		जाओ create_fail;
	पूर्ण

	अगर (link->dc->res_pool->funcs->link_init)
		link->dc->res_pool->funcs->link_init(link);

	link->hpd_gpio = get_hpd_gpio(link->ctx->dc_bios, link->link_id,
				      link->ctx->gpio_service);

	अगर (link->hpd_gpio) अणु
		dal_gpio_खोलो(link->hpd_gpio, GPIO_MODE_INTERRUPT);
		dal_gpio_unlock_pin(link->hpd_gpio);
		link->irq_source_hpd = dal_irq_get_source(link->hpd_gpio);

		DC_LOG_DC("BIOS object table - hpd_gpio id: %d", link->hpd_gpio->id);
		DC_LOG_DC("BIOS object table - hpd_gpio en: %d", link->hpd_gpio->en);
	पूर्ण

	चयन (link->link_id.id) अणु
	हाल CONNECTOR_ID_HDMI_TYPE_A:
		link->connector_संकेत = SIGNAL_TYPE_HDMI_TYPE_A;

		अवरोध;
	हाल CONNECTOR_ID_SINGLE_LINK_DVID:
	हाल CONNECTOR_ID_SINGLE_LINK_DVII:
		link->connector_संकेत = SIGNAL_TYPE_DVI_SINGLE_LINK;
		अवरोध;
	हाल CONNECTOR_ID_DUAL_LINK_DVID:
	हाल CONNECTOR_ID_DUAL_LINK_DVII:
		link->connector_संकेत = SIGNAL_TYPE_DVI_DUAL_LINK;
		अवरोध;
	हाल CONNECTOR_ID_DISPLAY_PORT:
		link->connector_संकेत = SIGNAL_TYPE_DISPLAY_PORT;

		अगर (link->hpd_gpio)
			link->irq_source_hpd_rx =
					dal_irq_get_rx_source(link->hpd_gpio);

		अवरोध;
	हाल CONNECTOR_ID_EDP:
		link->connector_संकेत = SIGNAL_TYPE_EDP;

		अगर (link->hpd_gpio) अणु
			link->irq_source_hpd = DC_IRQ_SOURCE_INVALID;
			link->irq_source_hpd_rx =
					dal_irq_get_rx_source(link->hpd_gpio);
		पूर्ण

		अवरोध;
	हाल CONNECTOR_ID_LVDS:
		link->connector_संकेत = SIGNAL_TYPE_LVDS;
		अवरोध;
	शेष:
		DC_LOG_WARNING("Unsupported Connector type:%d!\n",
			       link->link_id.id);
		जाओ create_fail;
	पूर्ण

	/* TODO: #DAL3 Implement id to str function.*/
	LINK_INFO("Connector[%d] description:"
		  "signal %d\n",
		  init_params->connector_index,
		  link->connector_संकेत);

	ddc_service_init_data.ctx = link->ctx;
	ddc_service_init_data.id = link->link_id;
	ddc_service_init_data.link = link;
	link->ddc = dal_ddc_service_create(&ddc_service_init_data);

	अगर (!link->ddc) अणु
		DC_ERROR("Failed to create ddc_service!\n");
		जाओ ddc_create_fail;
	पूर्ण

	अगर (!link->ddc->ddc_pin) अणु
		DC_ERROR("Failed to get I2C info for connector!\n");
		जाओ ddc_create_fail;
	पूर्ण

	link->ddc_hw_inst =
		dal_ddc_get_line(dal_ddc_service_get_ddc_pin(link->ddc));


	अगर (link->dc->res_pool->funcs->panel_cntl_create &&
		(link->link_id.id == CONNECTOR_ID_EDP ||
			link->link_id.id == CONNECTOR_ID_LVDS)) अणु
		panel_cntl_init_data.ctx = dc_ctx;
		panel_cntl_init_data.inst =
			panel_cntl_init_data.ctx->dc_edp_id_count;
		link->panel_cntl =
			link->dc->res_pool->funcs->panel_cntl_create(
								&panel_cntl_init_data);
		panel_cntl_init_data.ctx->dc_edp_id_count++;

		अगर (link->panel_cntl == शून्य) अणु
			DC_ERROR("Failed to create link panel_cntl!\n");
			जाओ panel_cntl_create_fail;
		पूर्ण
	पूर्ण

	enc_init_data.ctx = dc_ctx;
	bp_funcs->get_src_obj(dc_ctx->dc_bios, link->link_id, 0,
			      &enc_init_data.encoder);
	enc_init_data.connector = link->link_id;
	enc_init_data.channel = get_ddc_line(link);
	enc_init_data.hpd_source = get_hpd_line(link);

	link->hpd_src = enc_init_data.hpd_source;

	enc_init_data.transmitter =
		translate_encoder_to_transmitter(enc_init_data.encoder);
	link->link_enc =
		link->dc->res_pool->funcs->link_enc_create(&enc_init_data);

	अगर (!link->link_enc) अणु
		DC_ERROR("Failed to create link encoder!\n");
		जाओ link_enc_create_fail;
	पूर्ण

	DC_LOG_DC("BIOS object table - DP_IS_USB_C: %d", link->link_enc->features.flags.bits.DP_IS_USB_C);

	/* Update link encoder tracking variables. These are used क्रम the dynamic
	 * assignment of link encoders to streams.
	 */
	link->eng_id = link->link_enc->preferred_engine;
	link->dc->res_pool->link_encoders[link->eng_id - ENGINE_ID_DIGA] = link->link_enc;
	link->dc->res_pool->dig_link_enc_count++;

	link->link_enc_hw_inst = link->link_enc->transmitter;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (bp_funcs->get_device_tag(dc_ctx->dc_bios,
					     link->link_id, i,
					     &link->device_tag) != BP_RESULT_OK) अणु
			DC_ERROR("Failed to find device tag!\n");
			जाओ device_tag_fail;
		पूर्ण

		/* Look क्रम device tag that matches connector संकेत,
		 * CRT क्रम rgb, LCD क्रम other supported संकेत tyes
		 */
		अगर (!bp_funcs->is_device_id_supported(dc_ctx->dc_bios,
						      link->device_tag.dev_id))
			जारी;
		अगर (link->device_tag.dev_id.device_type == DEVICE_TYPE_CRT &&
		    link->connector_संकेत != SIGNAL_TYPE_RGB)
			जारी;
		अगर (link->device_tag.dev_id.device_type == DEVICE_TYPE_LCD &&
		    link->connector_संकेत == SIGNAL_TYPE_RGB)
			जारी;

		DC_LOG_DC("BIOS object table - device_tag.acpi_device: %d", link->device_tag.acpi_device);
		DC_LOG_DC("BIOS object table - device_tag.dev_id.device_type: %d", link->device_tag.dev_id.device_type);
		DC_LOG_DC("BIOS object table - device_tag.dev_id.enum_id: %d", link->device_tag.dev_id.क्रमागत_id);
		अवरोध;
	पूर्ण

	अगर (bios->पूर्णांकegrated_info)
		स_नकल(info, bios->पूर्णांकegrated_info, माप(*info));

	/* Look क्रम channel mapping corresponding to connector and device tag */
	क्रम (i = 0; i < MAX_NUMBER_OF_EXT_DISPLAY_PATH; i++) अणु
		काष्ठा बाह्यal_display_path *path =
			&info->ext_disp_conn_info.path[i];

		अगर (path->device_connector_id.क्रमागत_id == link->link_id.क्रमागत_id &&
		    path->device_connector_id.id == link->link_id.id &&
		    path->device_connector_id.type == link->link_id.type) अणु
			अगर (link->device_tag.acpi_device != 0 &&
			    path->device_acpi_क्रमागत == link->device_tag.acpi_device) अणु
				link->ddi_channel_mapping = path->channel_mapping;
				link->chip_caps = path->caps;
				DC_LOG_DC("BIOS object table - ddi_channel_mapping: 0x%04X", link->ddi_channel_mapping.raw);
				DC_LOG_DC("BIOS object table - chip_caps: %d", link->chip_caps);
			पूर्ण अन्यथा अगर (path->device_tag ==
				   link->device_tag.dev_id.raw_device_tag) अणु
				link->ddi_channel_mapping = path->channel_mapping;
				link->chip_caps = path->caps;
				DC_LOG_DC("BIOS object table - ddi_channel_mapping: 0x%04X", link->ddi_channel_mapping.raw);
				DC_LOG_DC("BIOS object table - chip_caps: %d", link->chip_caps);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (bios->funcs->get_atom_dc_golden_table)
		bios->funcs->get_atom_dc_golden_table(bios);

	/*
	 * TODO check अगर GPIO programmed correctly
	 *
	 * If GPIO isn't programmed correctly HPD might not rise or drain
	 * fast enough, leading to bounces.
	 */
	program_hpd_filter(link);

	link->psr_settings.psr_version = DC_PSR_VERSION_UNSUPPORTED;

	DC_LOG_DC("BIOS object table - %s finished successfully.\n", __func__);
	kमुक्त(info);
	वापस true;
device_tag_fail:
	link->link_enc->funcs->destroy(&link->link_enc);
link_enc_create_fail:
	अगर (link->panel_cntl != शून्य)
		link->panel_cntl->funcs->destroy(&link->panel_cntl);
panel_cntl_create_fail:
	dal_ddc_service_destroy(&link->ddc);
ddc_create_fail:
create_fail:

	अगर (link->hpd_gpio) अणु
		dal_gpio_destroy_irq(&link->hpd_gpio);
		link->hpd_gpio = शून्य;
	पूर्ण

	DC_LOG_DC("BIOS object table - %s failed.\n", __func__);
	kमुक्त(info);

	वापस false;
पूर्ण

/*******************************************************************************
 * Public functions
 ******************************************************************************/
काष्ठा dc_link *link_create(स्थिर काष्ठा link_init_data *init_params)
अणु
	काष्ठा dc_link *link =
			kzalloc(माप(*link), GFP_KERNEL);

	अगर (शून्य == link)
		जाओ alloc_fail;

	अगर (false == dc_link_स्थिरruct(link, init_params))
		जाओ स्थिरruct_fail;

	वापस link;

स्थिरruct_fail:
	kमुक्त(link);

alloc_fail:
	वापस शून्य;
पूर्ण

व्योम link_destroy(काष्ठा dc_link **link)
अणु
	dc_link_deकाष्ठा(*link);
	kमुक्त(*link);
	*link = शून्य;
पूर्ण

अटल व्योम enable_stream_features(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;

	अगर (pipe_ctx->stream->संकेत != SIGNAL_TYPE_DISPLAY_PORT_MST) अणु
		काष्ठा dc_link *link = stream->link;
		जोड़ करोwn_spपढ़ो_ctrl old_करोwnspपढ़ो;
		जोड़ करोwn_spपढ़ो_ctrl new_करोwnspपढ़ो;

		core_link_पढ़ो_dpcd(link, DP_DOWNSPREAD_CTRL,
				&old_करोwnspपढ़ो.raw, माप(old_करोwnspपढ़ो));

		new_करोwnspपढ़ो.raw = old_करोwnspपढ़ो.raw;

		new_करोwnspपढ़ो.bits.IGNORE_MSA_TIMING_PARAM =
				(stream->ignore_msa_timing_param) ? 1 : 0;

		अगर (new_करोwnspपढ़ो.raw != old_करोwnspपढ़ो.raw) अणु
			core_link_ग_लिखो_dpcd(link, DP_DOWNSPREAD_CTRL,
				&new_करोwnspपढ़ो.raw, माप(new_करोwnspपढ़ो));
		पूर्ण

	पूर्ण अन्यथा अणु
		dm_helpers_mst_enable_stream_features(stream);
	पूर्ण
पूर्ण

अटल क्रमागत dc_status enable_link_dp(काष्ठा dc_state *state,
				     काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	क्रमागत dc_status status;
	bool skip_video_pattern;
	काष्ठा dc_link *link = stream->link;
	काष्ठा dc_link_settings link_settings = अणु0पूर्ण;
	bool fec_enable;
	पूर्णांक i;
	bool apply_seamless_boot_optimization = false;
	uपूर्णांक32_t bl_oled_enable_delay = 50; // in ms
	स्थिर uपूर्णांक32_t post_oui_delay = 30; // 30ms

	// check क्रम seamless boot
	क्रम (i = 0; i < state->stream_count; i++) अणु
		अगर (state->streams[i]->apply_seamless_boot_optimization) अणु
			apply_seamless_boot_optimization = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* get link settings क्रम video mode timing */
	decide_link_settings(stream, &link_settings);

	अगर (pipe_ctx->stream->संकेत == SIGNAL_TYPE_EDP) अणु
		/*in हाल it is not on*/
		link->dc->hwss.edp_घातer_control(link, true);
		link->dc->hwss.edp_रुको_क्रम_hpd_पढ़ोy(link, true);
	पूर्ण

	pipe_ctx->stream_res.pix_clk_params.requested_sym_clk =
			link_settings.link_rate * LINK_RATE_REF_FREQ_IN_KHZ;
	अगर (state->clk_mgr && !apply_seamless_boot_optimization)
		state->clk_mgr->funcs->update_घड़ीs(state->clk_mgr,
						     state, false);

	// during mode चयन we करो DP_SET_POWER off then on, and OUI is lost
	dpcd_set_source_specअगरic_data(link);
	अगर (link->dpcd_sink_ext_caps.raw != 0)
		msleep(post_oui_delay);

	skip_video_pattern = true;

	अगर (link_settings.link_rate == LINK_RATE_LOW)
		skip_video_pattern = false;

	अगर (perक्रमm_link_training_with_retries(&link_settings,
					       skip_video_pattern,
					       LINK_TRAINING_ATTEMPTS,
					       pipe_ctx,
					       pipe_ctx->stream->संकेत)) अणु
		link->cur_link_settings = link_settings;
		status = DC_OK;
	पूर्ण अन्यथा अणु
		status = DC_FAIL_DP_LINK_TRAINING;
	पूर्ण

	अगर (link->preferred_training_settings.fec_enable)
		fec_enable = *link->preferred_training_settings.fec_enable;
	अन्यथा
		fec_enable = true;

	dp_set_fec_enable(link, fec_enable);

	// during mode set we करो DP_SET_POWER off then on, aux ग_लिखोs are lost
	अगर (link->dpcd_sink_ext_caps.bits.oled == 1 ||
		link->dpcd_sink_ext_caps.bits.sdr_aux_backlight_control == 1 ||
		link->dpcd_sink_ext_caps.bits.hdr_aux_backlight_control == 1) अणु
		dc_link_set_शेष_brightness_aux(link); // TODO: use cached अगर known
		अगर (link->dpcd_sink_ext_caps.bits.oled == 1)
			msleep(bl_oled_enable_delay);
		dc_link_backlight_enable_aux(link, true);
	पूर्ण

	वापस status;
पूर्ण

अटल क्रमागत dc_status enable_link_edp(
		काष्ठा dc_state *state,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	क्रमागत dc_status status;

	status = enable_link_dp(state, pipe_ctx);

	वापस status;
पूर्ण

अटल क्रमागत dc_status enable_link_dp_mst(
		काष्ठा dc_state *state,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_link *link = pipe_ctx->stream->link;

	/* sink संकेत type after MST branch is MST. Multiple MST sinks
	 * share one link. Link DP PHY is enable or training only once.
	 */
	अगर (link->link_status.link_active)
		वापस DC_OK;

	/* clear payload table */
	dm_helpers_dp_mst_clear_payload_allocation_table(link->ctx, link);

	/* to make sure the pending करोwn rep can be processed
	 * beक्रमe enabling the link
	 */
	dm_helpers_dp_mst_poll_pending_करोwn_reply(link->ctx, link);

	/* set the sink to MST mode beक्रमe enabling the link */
	dp_enable_mst_on_sink(link, true);

	वापस enable_link_dp(state, pipe_ctx);
पूर्ण

अटल bool get_ext_hdmi_settings(काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत engine_id eng_id,
		काष्ठा ext_hdmi_settings *settings)
अणु
	bool result = false;
	पूर्णांक i = 0;
	काष्ठा पूर्णांकegrated_info *पूर्णांकegrated_info =
			pipe_ctx->stream->ctx->dc_bios->पूर्णांकegrated_info;

	अगर (पूर्णांकegrated_info == शून्य)
		वापस false;

	/*
	 * Get reसमयr settings from sbios क्रम passing SI eye test क्रम DCE11
	 * The setting values are varied based on board revision and port id
	 * Thereक्रमe the setting values of each ports is passed by sbios.
	 */

	// Check अगर current bios contains ext Hdmi settings
	अगर (पूर्णांकegrated_info->gpu_cap_info & 0x20) अणु
		चयन (eng_id) अणु
		हाल ENGINE_ID_DIGA:
			settings->slv_addr = पूर्णांकegrated_info->dp0_ext_hdmi_slv_addr;
			settings->reg_num = पूर्णांकegrated_info->dp0_ext_hdmi_6g_reg_num;
			settings->reg_num_6g = पूर्णांकegrated_info->dp0_ext_hdmi_6g_reg_num;
			स_हटाओ(settings->reg_settings,
					पूर्णांकegrated_info->dp0_ext_hdmi_reg_settings,
					माप(पूर्णांकegrated_info->dp0_ext_hdmi_reg_settings));
			स_हटाओ(settings->reg_settings_6g,
					पूर्णांकegrated_info->dp0_ext_hdmi_6g_reg_settings,
					माप(पूर्णांकegrated_info->dp0_ext_hdmi_6g_reg_settings));
			result = true;
			अवरोध;
		हाल ENGINE_ID_DIGB:
			settings->slv_addr = पूर्णांकegrated_info->dp1_ext_hdmi_slv_addr;
			settings->reg_num = पूर्णांकegrated_info->dp1_ext_hdmi_6g_reg_num;
			settings->reg_num_6g = पूर्णांकegrated_info->dp1_ext_hdmi_6g_reg_num;
			स_हटाओ(settings->reg_settings,
					पूर्णांकegrated_info->dp1_ext_hdmi_reg_settings,
					माप(पूर्णांकegrated_info->dp1_ext_hdmi_reg_settings));
			स_हटाओ(settings->reg_settings_6g,
					पूर्णांकegrated_info->dp1_ext_hdmi_6g_reg_settings,
					माप(पूर्णांकegrated_info->dp1_ext_hdmi_6g_reg_settings));
			result = true;
			अवरोध;
		हाल ENGINE_ID_DIGC:
			settings->slv_addr = पूर्णांकegrated_info->dp2_ext_hdmi_slv_addr;
			settings->reg_num = पूर्णांकegrated_info->dp2_ext_hdmi_6g_reg_num;
			settings->reg_num_6g = पूर्णांकegrated_info->dp2_ext_hdmi_6g_reg_num;
			स_हटाओ(settings->reg_settings,
					पूर्णांकegrated_info->dp2_ext_hdmi_reg_settings,
					माप(पूर्णांकegrated_info->dp2_ext_hdmi_reg_settings));
			स_हटाओ(settings->reg_settings_6g,
					पूर्णांकegrated_info->dp2_ext_hdmi_6g_reg_settings,
					माप(पूर्णांकegrated_info->dp2_ext_hdmi_6g_reg_settings));
			result = true;
			अवरोध;
		हाल ENGINE_ID_DIGD:
			settings->slv_addr = पूर्णांकegrated_info->dp3_ext_hdmi_slv_addr;
			settings->reg_num = पूर्णांकegrated_info->dp3_ext_hdmi_6g_reg_num;
			settings->reg_num_6g = पूर्णांकegrated_info->dp3_ext_hdmi_6g_reg_num;
			स_हटाओ(settings->reg_settings,
					पूर्णांकegrated_info->dp3_ext_hdmi_reg_settings,
					माप(पूर्णांकegrated_info->dp3_ext_hdmi_reg_settings));
			स_हटाओ(settings->reg_settings_6g,
					पूर्णांकegrated_info->dp3_ext_hdmi_6g_reg_settings,
					माप(पूर्णांकegrated_info->dp3_ext_hdmi_6g_reg_settings));
			result = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (result == true) अणु
			// Validate settings from bios पूर्णांकegrated info table
			अगर (settings->slv_addr == 0)
				वापस false;
			अगर (settings->reg_num > 9)
				वापस false;
			अगर (settings->reg_num_6g > 3)
				वापस false;

			क्रम (i = 0; i < settings->reg_num; i++) अणु
				अगर (settings->reg_settings[i].i2c_reg_index > 0x20)
					वापस false;
			पूर्ण

			क्रम (i = 0; i < settings->reg_num_6g; i++) अणु
				अगर (settings->reg_settings_6g[i].i2c_reg_index > 0x20)
					वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल bool i2c_ग_लिखो(काष्ठा pipe_ctx *pipe_ctx,
		uपूर्णांक8_t address, uपूर्णांक8_t *buffer, uपूर्णांक32_t length)
अणु
	काष्ठा i2c_command cmd = अणु0पूर्ण;
	काष्ठा i2c_payload payload = अणु0पूर्ण;

	स_रखो(&payload, 0, माप(payload));
	स_रखो(&cmd, 0, माप(cmd));

	cmd.number_of_payloads = 1;
	cmd.engine = I2C_COMMAND_ENGINE_DEFAULT;
	cmd.speed = pipe_ctx->stream->ctx->dc->caps.i2c_speed_in_khz;

	payload.address = address;
	payload.data = buffer;
	payload.length = length;
	payload.ग_लिखो = true;
	cmd.payloads = &payload;

	अगर (dm_helpers_submit_i2c(pipe_ctx->stream->ctx,
			pipe_ctx->stream->link, &cmd))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम ग_लिखो_i2c_reसमयr_setting(
		काष्ठा pipe_ctx *pipe_ctx,
		bool is_vga_mode,
		bool is_over_340mhz,
		काष्ठा ext_hdmi_settings *settings)
अणु
	uपूर्णांक8_t slave_address = (settings->slv_addr >> 1);
	uपूर्णांक8_t buffer[2];
	स्थिर uपूर्णांक8_t apply_rx_tx_change = 0x4;
	uपूर्णांक8_t offset = 0xA;
	uपूर्णांक8_t value = 0;
	पूर्णांक i = 0;
	bool i2c_success = false;
	DC_LOGGER_INIT(pipe_ctx->stream->ctx->logger);

	स_रखो(&buffer, 0, माप(buffer));

	/* Start Ext-Hdmi programming*/

	क्रम (i = 0; i < settings->reg_num; i++) अणु
		/* Apply 3G settings */
		अगर (settings->reg_settings[i].i2c_reg_index <= 0x20) अणु

			buffer[0] = settings->reg_settings[i].i2c_reg_index;
			buffer[1] = settings->reg_settings[i].i2c_reg_val;
			i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
						buffer, माप(buffer));
			RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_address = 0x%x,\
				offset = 0x%x, reg_val= 0x%x, i2c_success = %d\न",
				slave_address, buffer[0], buffer[1], i2c_success?1:0);

			अगर (!i2c_success)
				जाओ i2c_ग_लिखो_fail;

			/* Based on DP159 specs, APPLY_RX_TX_CHANGE bit in 0x0A
			 * needs to be set to 1 on every 0xA-0xC ग_लिखो.
			 */
			अगर (settings->reg_settings[i].i2c_reg_index == 0xA ||
				settings->reg_settings[i].i2c_reg_index == 0xB ||
				settings->reg_settings[i].i2c_reg_index == 0xC) अणु

				/* Query current value from offset 0xA */
				अगर (settings->reg_settings[i].i2c_reg_index == 0xA)
					value = settings->reg_settings[i].i2c_reg_val;
				अन्यथा अणु
					i2c_success =
						dal_ddc_service_query_ddc_data(
						pipe_ctx->stream->link->ddc,
						slave_address, &offset, 1, &value, 1);
					अगर (!i2c_success)
						जाओ i2c_ग_लिखो_fail;
				पूर्ण

				buffer[0] = offset;
				/* Set APPLY_RX_TX_CHANGE bit to 1 */
				buffer[1] = value | apply_rx_tx_change;
				i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
						buffer, माप(buffer));
				RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_address = 0x%x,\
					offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
					slave_address, buffer[0], buffer[1], i2c_success?1:0);
				अगर (!i2c_success)
					जाओ i2c_ग_लिखो_fail;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Apply 3G settings */
	अगर (is_over_340mhz) अणु
		क्रम (i = 0; i < settings->reg_num_6g; i++) अणु
			/* Apply 3G settings */
			अगर (settings->reg_settings[i].i2c_reg_index <= 0x20) अणु

				buffer[0] = settings->reg_settings_6g[i].i2c_reg_index;
				buffer[1] = settings->reg_settings_6g[i].i2c_reg_val;
				i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
							buffer, माप(buffer));
				RETIMER_REDRIVER_INFO("above 340Mhz: reसमयr ग_लिखो to slave_address = 0x%x,\
					offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
					slave_address, buffer[0], buffer[1], i2c_success?1:0);

				अगर (!i2c_success)
					जाओ i2c_ग_लिखो_fail;

				/* Based on DP159 specs, APPLY_RX_TX_CHANGE bit in 0x0A
				 * needs to be set to 1 on every 0xA-0xC ग_लिखो.
				 */
				अगर (settings->reg_settings_6g[i].i2c_reg_index == 0xA ||
					settings->reg_settings_6g[i].i2c_reg_index == 0xB ||
					settings->reg_settings_6g[i].i2c_reg_index == 0xC) अणु

					/* Query current value from offset 0xA */
					अगर (settings->reg_settings_6g[i].i2c_reg_index == 0xA)
						value = settings->reg_settings_6g[i].i2c_reg_val;
					अन्यथा अणु
						i2c_success =
								dal_ddc_service_query_ddc_data(
								pipe_ctx->stream->link->ddc,
								slave_address, &offset, 1, &value, 1);
						अगर (!i2c_success)
							जाओ i2c_ग_लिखो_fail;
					पूर्ण

					buffer[0] = offset;
					/* Set APPLY_RX_TX_CHANGE bit to 1 */
					buffer[1] = value | apply_rx_tx_change;
					i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
							buffer, माप(buffer));
					RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_address = 0x%x,\
						offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
						slave_address, buffer[0], buffer[1], i2c_success?1:0);
					अगर (!i2c_success)
						जाओ i2c_ग_लिखो_fail;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (is_vga_mode) अणु
		/* Program additional settings अगर using 640x480 resolution */

		/* Write offset 0xFF to 0x01 */
		buffer[0] = 0xff;
		buffer[1] = 0x01;
		i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
				buffer, माप(buffer));
		RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_address = 0x%x,\
				offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
				slave_address, buffer[0], buffer[1], i2c_success?1:0);
		अगर (!i2c_success)
			जाओ i2c_ग_लिखो_fail;

		/* Write offset 0x00 to 0x23 */
		buffer[0] = 0x00;
		buffer[1] = 0x23;
		i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
				buffer, माप(buffer));
		RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_address = 0x%x,\
			offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
			slave_address, buffer[0], buffer[1], i2c_success?1:0);
		अगर (!i2c_success)
			जाओ i2c_ग_लिखो_fail;

		/* Write offset 0xff to 0x00 */
		buffer[0] = 0xff;
		buffer[1] = 0x00;
		i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
				buffer, माप(buffer));
		RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_address = 0x%x,\
			offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
			slave_address, buffer[0], buffer[1], i2c_success?1:0);
		अगर (!i2c_success)
			जाओ i2c_ग_लिखो_fail;

	पूर्ण

	वापस;

i2c_ग_लिखो_fail:
	DC_LOG_DEBUG("Set retimer failed");
पूर्ण

अटल व्योम ग_लिखो_i2c_शेष_reसमयr_setting(
		काष्ठा pipe_ctx *pipe_ctx,
		bool is_vga_mode,
		bool is_over_340mhz)
अणु
	uपूर्णांक8_t slave_address = (0xBA >> 1);
	uपूर्णांक8_t buffer[2];
	bool i2c_success = false;
	DC_LOGGER_INIT(pipe_ctx->stream->ctx->logger);

	स_रखो(&buffer, 0, माप(buffer));

	/* Program Slave Address क्रम tuning single पूर्णांकegrity */
	/* Write offset 0x0A to 0x13 */
	buffer[0] = 0x0A;
	buffer[1] = 0x13;
	i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
			buffer, माप(buffer));
	RETIMER_REDRIVER_INFO("reसमयr ग_लिखोs शेष setting to slave_address = 0x%x,\
		offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
		slave_address, buffer[0], buffer[1], i2c_success?1:0);
	अगर (!i2c_success)
		जाओ i2c_ग_लिखो_fail;

	/* Write offset 0x0A to 0x17 */
	buffer[0] = 0x0A;
	buffer[1] = 0x17;
	i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
			buffer, माप(buffer));
	RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_addr = 0x%x,\
		offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
		slave_address, buffer[0], buffer[1], i2c_success?1:0);
	अगर (!i2c_success)
		जाओ i2c_ग_लिखो_fail;

	/* Write offset 0x0B to 0xDA or 0xD8 */
	buffer[0] = 0x0B;
	buffer[1] = is_over_340mhz ? 0xDA : 0xD8;
	i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
			buffer, माप(buffer));
	RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_addr = 0x%x,\
		offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
		slave_address, buffer[0], buffer[1], i2c_success?1:0);
	अगर (!i2c_success)
		जाओ i2c_ग_लिखो_fail;

	/* Write offset 0x0A to 0x17 */
	buffer[0] = 0x0A;
	buffer[1] = 0x17;
	i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
			buffer, माप(buffer));
	RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_addr = 0x%x,\
		offset = 0x%x, reg_val= 0x%x, i2c_success = %d\न",
		slave_address, buffer[0], buffer[1], i2c_success?1:0);
	अगर (!i2c_success)
		जाओ i2c_ग_लिखो_fail;

	/* Write offset 0x0C to 0x1D or 0x91 */
	buffer[0] = 0x0C;
	buffer[1] = is_over_340mhz ? 0x1D : 0x91;
	i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
			buffer, माप(buffer));
	RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_addr = 0x%x,\
		offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
		slave_address, buffer[0], buffer[1], i2c_success?1:0);
	अगर (!i2c_success)
		जाओ i2c_ग_लिखो_fail;

	/* Write offset 0x0A to 0x17 */
	buffer[0] = 0x0A;
	buffer[1] = 0x17;
	i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
			buffer, माप(buffer));
	RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_addr = 0x%x,\
		offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
		slave_address, buffer[0], buffer[1], i2c_success?1:0);
	अगर (!i2c_success)
		जाओ i2c_ग_लिखो_fail;


	अगर (is_vga_mode) अणु
		/* Program additional settings अगर using 640x480 resolution */

		/* Write offset 0xFF to 0x01 */
		buffer[0] = 0xff;
		buffer[1] = 0x01;
		i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
				buffer, माप(buffer));
		RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_addr = 0x%x,\
			offset = 0x%x, reg_val = 0x%x, i2c_success = %d\न",
			slave_address, buffer[0], buffer[1], i2c_success?1:0);
		अगर (!i2c_success)
			जाओ i2c_ग_लिखो_fail;

		/* Write offset 0x00 to 0x23 */
		buffer[0] = 0x00;
		buffer[1] = 0x23;
		i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
				buffer, माप(buffer));
		RETIMER_REDRIVER_INFO("reसमयr ग_लिखो to slave_addr = 0x%x,\
			offset = 0x%x, reg_val= 0x%x, i2c_success = %d\न",
			slave_address, buffer[0], buffer[1], i2c_success?1:0);
		अगर (!i2c_success)
			जाओ i2c_ग_लिखो_fail;

		/* Write offset 0xff to 0x00 */
		buffer[0] = 0xff;
		buffer[1] = 0x00;
		i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
				buffer, माप(buffer));
		RETIMER_REDRIVER_INFO("reसमयr ग_लिखो शेष setting to slave_addr = 0x%x,\
			offset = 0x%x, reg_val= 0x%x, i2c_success = %d end here\न",
			slave_address, buffer[0], buffer[1], i2c_success?1:0);
		अगर (!i2c_success)
			जाओ i2c_ग_लिखो_fail;
	पूर्ण

	वापस;

i2c_ग_लिखो_fail:
	DC_LOG_DEBUG("Set default retimer failed");
पूर्ण

अटल व्योम ग_लिखो_i2c_redriver_setting(
		काष्ठा pipe_ctx *pipe_ctx,
		bool is_over_340mhz)
अणु
	uपूर्णांक8_t slave_address = (0xF0 >> 1);
	uपूर्णांक8_t buffer[16];
	bool i2c_success = false;
	DC_LOGGER_INIT(pipe_ctx->stream->ctx->logger);

	स_रखो(&buffer, 0, माप(buffer));

	// Program Slave Address क्रम tuning single पूर्णांकegrity
	buffer[3] = 0x4E;
	buffer[4] = 0x4E;
	buffer[5] = 0x4E;
	buffer[6] = is_over_340mhz ? 0x4E : 0x4A;

	i2c_success = i2c_ग_लिखो(pipe_ctx, slave_address,
					buffer, माप(buffer));
	RETIMER_REDRIVER_INFO("redriver ग_लिखो 0 to all 16 reg offset expect following:\न\
		\ट slave_addr = 0x%x, offset[3] = 0x%x, offset[4] = 0x%x,\
		offset[5] = 0x%x,offset[6] is_over_340mhz = 0x%x,\
		i2c_success = %d\न",
		slave_address, buffer[3], buffer[4], buffer[5], buffer[6], i2c_success?1:0);

	अगर (!i2c_success)
		DC_LOG_DEBUG("Set redriver failed");
पूर्ण

अटल व्योम disable_link(काष्ठा dc_link *link, क्रमागत संकेत_type संकेत)
अणु
	/*
	 * TODO: implement call क्रम dp_set_hw_test_pattern
	 * it is needed क्रम compliance testing
	 */

	/* Here we need to specअगरy that encoder output settings
	 * need to be calculated as क्रम the set mode,
	 * it will lead to querying dynamic link capabilities
	 * which should be करोne beक्रमe enable output
	 */

	अगर (dc_is_dp_संकेत(संकेत)) अणु
		/* SST DP, eDP */
		अगर (dc_is_dp_sst_संकेत(संकेत))
			dp_disable_link_phy(link, संकेत);
		अन्यथा
			dp_disable_link_phy_mst(link, संकेत);

		अगर (dc_is_dp_sst_संकेत(संकेत) ||
				link->mst_stream_alloc_table.stream_count == 0) अणु
			dp_set_fec_enable(link, false);
			dp_set_fec_पढ़ोy(link, false);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (संकेत != SIGNAL_TYPE_VIRTUAL)
			link->link_enc->funcs->disable_output(link->link_enc, संकेत);
	पूर्ण

	अगर (संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST) अणु
		/* MST disable link only when no stream use the link */
		अगर (link->mst_stream_alloc_table.stream_count <= 0)
			link->link_status.link_active = false;
	पूर्ण अन्यथा अणु
		link->link_status.link_active = false;
	पूर्ण
पूर्ण

अटल व्योम enable_link_hdmi(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->link;
	क्रमागत dc_color_depth display_color_depth;
	क्रमागत engine_id eng_id;
	काष्ठा ext_hdmi_settings settings = अणु0पूर्ण;
	bool is_over_340mhz = false;
	bool is_vga_mode = (stream->timing.h_addressable == 640)
			&& (stream->timing.v_addressable == 480);

	अगर (stream->phy_pix_clk == 0)
		stream->phy_pix_clk = stream->timing.pix_clk_100hz / 10;
	अगर (stream->phy_pix_clk > 340000)
		is_over_340mhz = true;

	अगर (dc_is_hdmi_संकेत(pipe_ctx->stream->संकेत)) अणु
		अचिन्हित लघु masked_chip_caps = pipe_ctx->stream->link->chip_caps &
				EXT_DISPLAY_PATH_CAPS__EXT_CHIP_MASK;
		अगर (masked_chip_caps == EXT_DISPLAY_PATH_CAPS__HDMI20_TISN65DP159RSBT) अणु
			/* DP159, Reसमयr settings */
			eng_id = pipe_ctx->stream_res.stream_enc->id;

			अगर (get_ext_hdmi_settings(pipe_ctx, eng_id, &settings)) अणु
				ग_लिखो_i2c_reसमयr_setting(pipe_ctx,
						is_vga_mode, is_over_340mhz, &settings);
			पूर्ण अन्यथा अणु
				ग_लिखो_i2c_शेष_reसमयr_setting(pipe_ctx,
						is_vga_mode, is_over_340mhz);
			पूर्ण
		पूर्ण अन्यथा अगर (masked_chip_caps == EXT_DISPLAY_PATH_CAPS__HDMI20_PI3EQX1204) अणु
			/* PI3EQX1204, Redriver settings */
			ग_लिखो_i2c_redriver_setting(pipe_ctx, is_over_340mhz);
		पूर्ण
	पूर्ण

	अगर (dc_is_hdmi_संकेत(pipe_ctx->stream->संकेत))
		dal_ddc_service_ग_लिखो_scdc_data(
			stream->link->ddc,
			stream->phy_pix_clk,
			stream->timing.flags.LTE_340MCSC_SCRAMBLE);

	स_रखो(&stream->link->cur_link_settings, 0,
			माप(काष्ठा dc_link_settings));

	display_color_depth = stream->timing.display_color_depth;
	अगर (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR422)
		display_color_depth = COLOR_DEPTH_888;

	link->link_enc->funcs->enable_पंचांगds_output(
			link->link_enc,
			pipe_ctx->घड़ी_source->id,
			display_color_depth,
			pipe_ctx->stream->संकेत,
			stream->phy_pix_clk);

	अगर (dc_is_hdmi_संकेत(pipe_ctx->stream->संकेत))
		dal_ddc_service_पढ़ो_scdc_data(link->ddc);
पूर्ण

अटल व्योम enable_link_lvds(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->link;

	अगर (stream->phy_pix_clk == 0)
		stream->phy_pix_clk = stream->timing.pix_clk_100hz / 10;

	स_रखो(&stream->link->cur_link_settings, 0,
			माप(काष्ठा dc_link_settings));

	link->link_enc->funcs->enable_lvds_output(
			link->link_enc,
			pipe_ctx->घड़ी_source->id,
			stream->phy_pix_clk);

पूर्ण

/****************************enable_link***********************************/
अटल क्रमागत dc_status enable_link(
		काष्ठा dc_state *state,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	क्रमागत dc_status status = DC_ERROR_UNEXPECTED;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->link;

	/* There's some scenarios where driver is unloaded with display
	 * still enabled. When driver is reloaded, it may cause a display
	 * to not light up अगर there is a mismatch between old and new
	 * link settings. Need to call disable first beक्रमe enabling at
	 * new link settings.
	 */
	अगर (link->link_status.link_active) अणु
		disable_link(link, pipe_ctx->stream->संकेत);
	पूर्ण

	चयन (pipe_ctx->stream->संकेत) अणु
	हाल SIGNAL_TYPE_DISPLAY_PORT:
		status = enable_link_dp(state, pipe_ctx);
		अवरोध;
	हाल SIGNAL_TYPE_EDP:
		status = enable_link_edp(state, pipe_ctx);
		अवरोध;
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		status = enable_link_dp_mst(state, pipe_ctx);
		msleep(200);
		अवरोध;
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		enable_link_hdmi(pipe_ctx);
		status = DC_OK;
		अवरोध;
	हाल SIGNAL_TYPE_LVDS:
		enable_link_lvds(pipe_ctx);
		status = DC_OK;
		अवरोध;
	हाल SIGNAL_TYPE_VIRTUAL:
		status = DC_OK;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (status == DC_OK)
		pipe_ctx->stream->link->link_status.link_active = true;

	वापस status;
पूर्ण

अटल uपूर्णांक32_t get_timing_pixel_घड़ी_100hz(स्थिर काष्ठा dc_crtc_timing *timing)
अणु

	uपूर्णांक32_t pxl_clk = timing->pix_clk_100hz;

	अगर (timing->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		pxl_clk /= 2;
	अन्यथा अगर (timing->pixel_encoding == PIXEL_ENCODING_YCBCR422)
		pxl_clk = pxl_clk * 2 / 3;

	अगर (timing->display_color_depth == COLOR_DEPTH_101010)
		pxl_clk = pxl_clk * 10 / 8;
	अन्यथा अगर (timing->display_color_depth == COLOR_DEPTH_121212)
		pxl_clk = pxl_clk * 12 / 8;

	वापस pxl_clk;
पूर्ण

अटल bool dp_active_करोngle_validate_timing(
		स्थिर काष्ठा dc_crtc_timing *timing,
		स्थिर काष्ठा dpcd_caps *dpcd_caps)
अणु
	स्थिर काष्ठा dc_करोngle_caps *करोngle_caps = &dpcd_caps->करोngle_caps;

	चयन (dpcd_caps->करोngle_type) अणु
	हाल DISPLAY_DONGLE_DP_VGA_CONVERTER:
	हाल DISPLAY_DONGLE_DP_DVI_CONVERTER:
	हाल DISPLAY_DONGLE_DP_DVI_DONGLE:
		अगर (timing->pixel_encoding == PIXEL_ENCODING_RGB)
			वापस true;
		अन्यथा
			वापस false;
	शेष:
		अवरोध;
	पूर्ण

	अगर (dpcd_caps->करोngle_type != DISPLAY_DONGLE_DP_HDMI_CONVERTER ||
		करोngle_caps->extendedCapValid == false)
		वापस true;

	/* Check Pixel Encoding */
	चयन (timing->pixel_encoding) अणु
	हाल PIXEL_ENCODING_RGB:
	हाल PIXEL_ENCODING_YCBCR444:
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR422:
		अगर (!करोngle_caps->is_dp_hdmi_ycbcr422_pass_through)
			वापस false;
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR420:
		अगर (!करोngle_caps->is_dp_hdmi_ycbcr420_pass_through)
			वापस false;
		अवरोध;
	शेष:
		/* Invalid Pixel Encoding*/
		वापस false;
	पूर्ण

	चयन (timing->display_color_depth) अणु
	हाल COLOR_DEPTH_666:
	हाल COLOR_DEPTH_888:
		/*888 and 666 should always be supported*/
		अवरोध;
	हाल COLOR_DEPTH_101010:
		अगर (करोngle_caps->dp_hdmi_max_bpc < 10)
			वापस false;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		अगर (करोngle_caps->dp_hdmi_max_bpc < 12)
			वापस false;
		अवरोध;
	हाल COLOR_DEPTH_141414:
	हाल COLOR_DEPTH_161616:
	शेष:
		/* These color depths are currently not supported */
		वापस false;
	पूर्ण

	अगर (get_timing_pixel_घड़ी_100hz(timing) > (करोngle_caps->dp_hdmi_max_pixel_clk_in_khz * 10))
		वापस false;

	वापस true;
पूर्ण

क्रमागत dc_status dc_link_validate_mode_timing(
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा dc_link *link,
		स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	uपूर्णांक32_t max_pix_clk = stream->link->करोngle_max_pix_clk * 10;
	काष्ठा dpcd_caps *dpcd_caps = &link->dpcd_caps;

	/* A hack to aव्योम failing any modes क्रम EDID override feature on
	 * topology change such as lower quality cable क्रम DP or dअगरferent करोngle
	 */
	अगर (link->remote_sinks[0] && link->remote_sinks[0]->sink_संकेत == SIGNAL_TYPE_VIRTUAL)
		वापस DC_OK;

	/* Passive Dongle */
	अगर (max_pix_clk != 0 && get_timing_pixel_घड़ी_100hz(timing) > max_pix_clk)
		वापस DC_EXCEED_DONGLE_CAP;

	/* Active Dongle*/
	अगर (!dp_active_करोngle_validate_timing(timing, dpcd_caps))
		वापस DC_EXCEED_DONGLE_CAP;

	चयन (stream->संकेत) अणु
	हाल SIGNAL_TYPE_EDP:
	हाल SIGNAL_TYPE_DISPLAY_PORT:
		अगर (!dp_validate_mode_timing(
				link,
				timing))
			वापस DC_NO_DP_LINK_BANDWIDTH;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस DC_OK;
पूर्ण

अटल काष्ठा abm *get_abm_from_stream_res(स्थिर काष्ठा dc_link *link)
अणु
	पूर्णांक i;
	काष्ठा dc *dc = शून्य;
	काष्ठा abm *abm = शून्य;

	अगर (!link || !link->ctx)
		वापस शून्य;

	dc = link->ctx->dc;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा pipe_ctx pipe_ctx = dc->current_state->res_ctx.pipe_ctx[i];
		काष्ठा dc_stream_state *stream = pipe_ctx.stream;

		अगर (stream && stream->link == link) अणु
			abm = pipe_ctx.stream_res.abm;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस abm;
पूर्ण

पूर्णांक dc_link_get_backlight_level(स्थिर काष्ठा dc_link *link)
अणु

	काष्ठा abm *abm = get_abm_from_stream_res(link);

	अगर (abm == शून्य || abm->funcs->get_current_backlight == शून्य)
		वापस DC_ERROR_UNEXPECTED;

	वापस (पूर्णांक) abm->funcs->get_current_backlight(abm);
पूर्ण

पूर्णांक dc_link_get_target_backlight_pwm(स्थिर काष्ठा dc_link *link)
अणु
	काष्ठा abm *abm = get_abm_from_stream_res(link);

	अगर (abm == शून्य || abm->funcs->get_target_backlight == शून्य)
		वापस DC_ERROR_UNEXPECTED;

	वापस (पूर्णांक) abm->funcs->get_target_backlight(abm);
पूर्ण

अटल काष्ठा pipe_ctx *get_pipe_from_link(स्थिर काष्ठा dc_link *link)
अणु
	पूर्णांक i;
	काष्ठा dc *dc = link->ctx->dc;
	काष्ठा pipe_ctx *pipe_ctx = शून्य;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (dc->current_state->res_ctx.pipe_ctx[i].stream) अणु
			अगर (dc->current_state->res_ctx.pipe_ctx[i].stream->link == link) अणु
				pipe_ctx = &dc->current_state->res_ctx.pipe_ctx[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस pipe_ctx;
पूर्ण

bool dc_link_set_backlight_level(स्थिर काष्ठा dc_link *link,
		uपूर्णांक32_t backlight_pwm_u16_16,
		uपूर्णांक32_t frame_ramp)
अणु
	काष्ठा dc  *dc = link->ctx->dc;

	DC_LOGGER_INIT(link->ctx->logger);
	DC_LOG_BACKLIGHT("New Backlight level: %d (0x%X)\n",
			backlight_pwm_u16_16, backlight_pwm_u16_16);

	अगर (dc_is_embedded_संकेत(link->connector_संकेत)) अणु
		काष्ठा pipe_ctx *pipe_ctx = get_pipe_from_link(link);

		अगर (pipe_ctx) अणु
			/* Disable brightness ramping when the display is blanked
			 * as it can hang the DMCU
			 */
			अगर (pipe_ctx->plane_state == शून्य)
				frame_ramp = 0;
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण

		dc->hwss.set_backlight_level(
				pipe_ctx,
				backlight_pwm_u16_16,
				frame_ramp);
	पूर्ण
	वापस true;
पूर्ण

bool dc_link_set_psr_allow_active(काष्ठा dc_link *link, bool allow_active,
		bool रुको, bool क्रमce_अटल)
अणु
	काष्ठा dc  *dc = link->ctx->dc;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;
	काष्ठा dmub_psr *psr = dc->res_pool->psr;

	अगर (psr == शून्य && क्रमce_अटल)
		वापस false;

	link->psr_settings.psr_allow_active = allow_active;

	अगर (psr != शून्य && link->psr_settings.psr_feature_enabled) अणु
		अगर (क्रमce_अटल && psr->funcs->psr_क्रमce_अटल)
			psr->funcs->psr_क्रमce_अटल(psr);
		psr->funcs->psr_enable(psr, allow_active, रुको);
	पूर्ण अन्यथा अगर ((dmcu != शून्य && dmcu->funcs->is_dmcu_initialized(dmcu)) && link->psr_settings.psr_feature_enabled)
		dmcu->funcs->set_psr_enable(dmcu, allow_active, रुको);
	अन्यथा
		वापस false;

	वापस true;
पूर्ण

bool dc_link_get_psr_state(स्थिर काष्ठा dc_link *link, क्रमागत dc_psr_state *state)
अणु
	काष्ठा dc  *dc = link->ctx->dc;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;
	काष्ठा dmub_psr *psr = dc->res_pool->psr;

	अगर (psr != शून्य && link->psr_settings.psr_feature_enabled)
		psr->funcs->psr_get_state(psr, state);
	अन्यथा अगर (dmcu != शून्य && link->psr_settings.psr_feature_enabled)
		dmcu->funcs->get_psr_state(dmcu, state);

	वापस true;
पूर्ण

अटल अंतरभूत क्रमागत physical_phy_id
transmitter_to_phy_id(क्रमागत transmitter transmitter_value)
अणु
	चयन (transmitter_value) अणु
	हाल TRANSMITTER_UNIPHY_A:
		वापस PHYLD_0;
	हाल TRANSMITTER_UNIPHY_B:
		वापस PHYLD_1;
	हाल TRANSMITTER_UNIPHY_C:
		वापस PHYLD_2;
	हाल TRANSMITTER_UNIPHY_D:
		वापस PHYLD_3;
	हाल TRANSMITTER_UNIPHY_E:
		वापस PHYLD_4;
	हाल TRANSMITTER_UNIPHY_F:
		वापस PHYLD_5;
	हाल TRANSMITTER_NUTMEG_CRT:
		वापस PHYLD_6;
	हाल TRANSMITTER_TRAVIS_CRT:
		वापस PHYLD_7;
	हाल TRANSMITTER_TRAVIS_LCD:
		वापस PHYLD_8;
	हाल TRANSMITTER_UNIPHY_G:
		वापस PHYLD_9;
	हाल TRANSMITTER_COUNT:
		वापस PHYLD_COUNT;
	हाल TRANSMITTER_UNKNOWN:
		वापस PHYLD_UNKNOWN;
	शेष:
		WARN_ONCE(1, "Unknown transmitter value %d\n",
			  transmitter_value);
		वापस PHYLD_UNKNOWN;
	पूर्ण
पूर्ण

bool dc_link_setup_psr(काष्ठा dc_link *link,
		स्थिर काष्ठा dc_stream_state *stream, काष्ठा psr_config *psr_config,
		काष्ठा psr_context *psr_context)
अणु
	काष्ठा dc *dc;
	काष्ठा dmcu *dmcu;
	काष्ठा dmub_psr *psr;
	पूर्णांक i;
	/* updateSinkPsrDpcdConfig*/
	जोड़ dpcd_psr_configuration psr_configuration;

	psr_context->controllerId = CONTROLLER_ID_UNDEFINED;

	अगर (!link)
		वापस false;

	dc = link->ctx->dc;
	dmcu = dc->res_pool->dmcu;
	psr = dc->res_pool->psr;

	अगर (!dmcu && !psr)
		वापस false;


	स_रखो(&psr_configuration, 0, माप(psr_configuration));

	psr_configuration.bits.ENABLE                    = 1;
	psr_configuration.bits.CRC_VERIFICATION          = 1;
	psr_configuration.bits.FRAME_CAPTURE_INDICATION  =
			psr_config->psr_frame_capture_indication_req;

	/* Check क्रम PSR v2*/
	अगर (psr_config->psr_version == 0x2) अणु
		/* For PSR v2 selective update.
		 * Indicates whether sink should start capturing
		 * immediately following active scan line,
		 * or starting with the 2nd active scan line.
		 */
		psr_configuration.bits.LINE_CAPTURE_INDICATION = 0;
		/*For PSR v2, determines whether Sink should generate
		 * IRQ_HPD when CRC mismatch is detected.
		 */
		psr_configuration.bits.IRQ_HPD_WITH_CRC_ERROR    = 1;
	पूर्ण

	dm_helpers_dp_ग_लिखो_dpcd(
		link->ctx,
		link,
		368,
		&psr_configuration.raw,
		माप(psr_configuration.raw));

	psr_context->channel = link->ddc->ddc_pin->hw_info.ddc_channel;
	psr_context->transmitterId = link->link_enc->transmitter;
	psr_context->engineId = link->link_enc->preferred_engine;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (dc->current_state->res_ctx.pipe_ctx[i].stream
				== stream) अणु
			/* dmcu -1 क्रम all controller id values,
			 * thereक्रमe +1 here
			 */
			psr_context->controllerId =
				dc->current_state->res_ctx.
				pipe_ctx[i].stream_res.tg->inst + 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Hardcoded क्रम now.  Can be Pcie or Uniphy (or Unknown)*/
	psr_context->phyType = PHY_TYPE_UNIPHY;
	/*PhyId is associated with the transmitter id*/
	psr_context->smuPhyId =
		transmitter_to_phy_id(link->link_enc->transmitter);

	psr_context->crtcTimingVerticalTotal = stream->timing.v_total;
	psr_context->vsync_rate_hz = भाग64_u64(भाग64_u64((stream->
					timing.pix_clk_100hz * 100),
					stream->timing.v_total),
					stream->timing.h_total);

	psr_context->psrSupportedDisplayConfig = true;
	psr_context->psrExitLinkTrainingRequired =
		psr_config->psr_निकास_link_training_required;
	psr_context->sdpTransmitLineNumDeadline =
		psr_config->psr_sdp_transmit_line_num_deadline;
	psr_context->psrFrameCaptureIndicationReq =
		psr_config->psr_frame_capture_indication_req;

	psr_context->skipPsrWaitForPllLock = 0; /* only = 1 in KV */

	psr_context->numberOfControllers =
			link->dc->res_pool->timing_generator_count;

	psr_context->rfb_update_स्वतः_en = true;

	/* 2 frames beक्रमe enter PSR. */
	psr_context->समयhyst_frames = 2;
	/* half a frame
	 * (units in 100 lines, i.e. a value of 1 represents 100 lines)
	 */
	psr_context->hyst_lines = stream->timing.v_total / 2 / 100;
	psr_context->aux_repeats = 10;

	psr_context->psr_level.u32all = 0;

	/*skip घातer करोwn the single pipe since it blocks the cstate*/
	अगर (link->ctx->asic_id.chip_family >= FAMILY_RV)
		psr_context->psr_level.bits.SKIP_CRTC_DISABLE = true;

	/* SMU will perक्रमm additional घातerकरोwn sequence.
	 * For unsupported ASICs, set psr_level flag to skip PSR
	 *  अटल screen notअगरication to SMU.
	 *  (Always set क्रम DAL2, did not check ASIC)
	 */
	psr_context->allow_smu_optimizations = psr_config->allow_smu_optimizations;
	psr_context->allow_multi_disp_optimizations = psr_config->allow_multi_disp_optimizations;

	/* Complete PSR entry beक्रमe पातing to prevent पूर्णांकermittent
	 * मुक्तzes on certain eDPs
	 */
	psr_context->psr_level.bits.DISABLE_PSR_ENTRY_ABORT = 1;

	/* Controls additional delay after remote frame capture beक्रमe
	 * continuing घातer करोwn, शेष = 0
	 */
	psr_context->frame_delay = 0;

	अगर (psr)
		link->psr_settings.psr_feature_enabled = psr->funcs->psr_copy_settings(psr, link, psr_context);
	अन्यथा
		link->psr_settings.psr_feature_enabled = dmcu->funcs->setup_psr(dmcu, link, psr_context);

	/* psr_enabled == 0 indicates setup_psr did not succeed, but this
	 * should not happen since firmware should be running at this poपूर्णांक
	 */
	अगर (link->psr_settings.psr_feature_enabled == 0)
		ASSERT(0);

	वापस true;

पूर्ण

व्योम dc_link_get_psr_residency(स्थिर काष्ठा dc_link *link, uपूर्णांक32_t *residency)
अणु
	काष्ठा dc  *dc = link->ctx->dc;
	काष्ठा dmub_psr *psr = dc->res_pool->psr;

	// PSR residency measurements only supported on DMCUB
	अगर (psr != शून्य && link->psr_settings.psr_feature_enabled)
		psr->funcs->psr_get_residency(psr, residency);
	अन्यथा
		*residency = 0;
पूर्ण

स्थिर काष्ठा dc_link_status *dc_link_get_status(स्थिर काष्ठा dc_link *link)
अणु
	वापस &link->link_status;
पूर्ण

व्योम core_link_resume(काष्ठा dc_link *link)
अणु
	अगर (link->connector_संकेत != SIGNAL_TYPE_VIRTUAL)
		program_hpd_filter(link);
पूर्ण

अटल काष्ठा fixed31_32 get_pbn_per_slot(काष्ठा dc_stream_state *stream)
अणु
	काष्ठा fixed31_32 mbytes_per_sec;
	uपूर्णांक32_t link_rate_in_mbytes_per_sec = dc_link_bandwidth_kbps(stream->link,
			&stream->link->cur_link_settings);
	link_rate_in_mbytes_per_sec /= 8000; /* Kbits to MBytes */

	mbytes_per_sec = dc_fixpt_from_पूर्णांक(link_rate_in_mbytes_per_sec);

	वापस dc_fixpt_भाग_पूर्णांक(mbytes_per_sec, 54);
पूर्ण

अटल काष्ठा fixed31_32 get_pbn_from_bw_in_kbps(uपूर्णांक64_t kbps)
अणु
	काष्ठा fixed31_32 peak_kbps;
	uपूर्णांक32_t numerator = 0;
	uपूर्णांक32_t denominator = 1;

	/*
	 * margin 5300ppm + 300ppm ~ 0.6% as per spec, factor is 1.006
	 * The unit of 54/64Mbytes/sec is an arbitrary unit chosen based on
	 * common multiplier to render an पूर्णांकeger PBN क्रम all link rate/lane
	 * counts combinations
	 * calculate
	 * peak_kbps *= (1006/1000)
	 * peak_kbps *= (64/54)
	 * peak_kbps *= 8    convert to bytes
	 */

	numerator = 64 * PEAK_FACTOR_X1000;
	denominator = 54 * 8 * 1000 * 1000;
	kbps *= numerator;
	peak_kbps = dc_fixpt_from_fraction(kbps, denominator);

	वापस peak_kbps;
पूर्ण

अटल काष्ठा fixed31_32 get_pbn_from_timing(काष्ठा pipe_ctx *pipe_ctx)
अणु
	uपूर्णांक64_t kbps;

	kbps = dc_bandwidth_in_kbps_from_timing(&pipe_ctx->stream->timing);
	वापस get_pbn_from_bw_in_kbps(kbps);
पूर्ण

अटल व्योम update_mst_stream_alloc_table(
	काष्ठा dc_link *link,
	काष्ठा stream_encoder *stream_enc,
	स्थिर काष्ठा dp_mst_stream_allocation_table *proposed_table)
अणु
	काष्ठा link_mst_stream_allocation work_table[MAX_CONTROLLER_NUM] = अणु
			अणु 0 पूर्ण पूर्ण;
	काष्ठा link_mst_stream_allocation *dc_alloc;

	पूर्णांक i;
	पूर्णांक j;

	/* अगर DRM proposed_table has more than one new payload */
	ASSERT(proposed_table->stream_count -
			link->mst_stream_alloc_table.stream_count < 2);

	/* copy proposed_table to link, add stream encoder */
	क्रम (i = 0; i < proposed_table->stream_count; i++) अणु

		क्रम (j = 0; j < link->mst_stream_alloc_table.stream_count; j++) अणु
			dc_alloc =
			&link->mst_stream_alloc_table.stream_allocations[j];

			अगर (dc_alloc->vcp_id ==
				proposed_table->stream_allocations[i].vcp_id) अणु

				work_table[i] = *dc_alloc;
				work_table[i].slot_count = proposed_table->stream_allocations[i].slot_count;
				अवरोध; /* निकास j loop */
			पूर्ण
		पूर्ण

		/* new vcp_id */
		अगर (j == link->mst_stream_alloc_table.stream_count) अणु
			work_table[i].vcp_id =
				proposed_table->stream_allocations[i].vcp_id;
			work_table[i].slot_count =
				proposed_table->stream_allocations[i].slot_count;
			work_table[i].stream_enc = stream_enc;
		पूर्ण
	पूर्ण

	/* update link->mst_stream_alloc_table with work_table */
	link->mst_stream_alloc_table.stream_count =
			proposed_table->stream_count;
	क्रम (i = 0; i < MAX_CONTROLLER_NUM; i++)
		link->mst_stream_alloc_table.stream_allocations[i] =
				work_table[i];
पूर्ण

/* convert link_mst_stream_alloc_table to dm dp_mst_stream_alloc_table
 * because stream_encoder is not exposed to dm
 */
क्रमागत dc_status dc_link_allocate_mst_payload(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->link;
	काष्ठा link_encoder *link_encoder = link->link_enc;
	काष्ठा stream_encoder *stream_encoder = pipe_ctx->stream_res.stream_enc;
	काष्ठा dp_mst_stream_allocation_table proposed_table = अणु0पूर्ण;
	काष्ठा fixed31_32 avg_समय_slots_per_mtp;
	काष्ठा fixed31_32 pbn;
	काष्ठा fixed31_32 pbn_per_slot;
	uपूर्णांक8_t i;
	क्रमागत act_वापस_status ret;
	DC_LOGGER_INIT(link->ctx->logger);

	/* enable_link_dp_mst alपढ़ोy check link->enabled_stream_count
	 * and stream is in link->stream[]. This is called during set mode,
	 * stream_enc is available.
	 */

	/* get calculate VC payload क्रम stream: stream_alloc */
	अगर (dm_helpers_dp_mst_ग_लिखो_payload_allocation_table(
		stream->ctx,
		stream,
		&proposed_table,
		true)) अणु
		update_mst_stream_alloc_table(
					link, pipe_ctx->stream_res.stream_enc, &proposed_table);
	पूर्ण
	अन्यथा
		DC_LOG_WARNING("Failed to update"
				"MST allocation table for"
				"pipe idx:%d\n",
				pipe_ctx->pipe_idx);

	DC_LOG_MST("%s  "
			"stream_count: %d: \n ",
			__func__,
			link->mst_stream_alloc_table.stream_count);

	क्रम (i = 0; i < MAX_CONTROLLER_NUM; i++) अणु
		DC_LOG_MST("stream_enc[%d]: %p      "
		"stream[%d].vcp_id: %d      "
		"stream[%d].slot_count: %d\n",
		i,
		(व्योम *) link->mst_stream_alloc_table.stream_allocations[i].stream_enc,
		i,
		link->mst_stream_alloc_table.stream_allocations[i].vcp_id,
		i,
		link->mst_stream_alloc_table.stream_allocations[i].slot_count);
	पूर्ण

	ASSERT(proposed_table.stream_count > 0);

	/* program DP source TX क्रम payload */
	link_encoder->funcs->update_mst_stream_allocation_table(
		link_encoder,
		&link->mst_stream_alloc_table);

	/* send करोwn message */
	ret = dm_helpers_dp_mst_poll_क्रम_allocation_change_trigger(
			stream->ctx,
			stream);

	अगर (ret != ACT_LINK_LOST) अणु
		dm_helpers_dp_mst_send_payload_allocation(
				stream->ctx,
				stream,
				true);
	पूर्ण

	/* slot X.Y क्रम only current stream */
	pbn_per_slot = get_pbn_per_slot(stream);
	अगर (pbn_per_slot.value == 0) अणु
		DC_LOG_ERROR("Failure: pbn_per_slot==0 not allowed. Cannot continue, returning DC_UNSUPPORTED_VALUE.\n");
		वापस DC_UNSUPPORTED_VALUE;
	पूर्ण
	pbn = get_pbn_from_timing(pipe_ctx);
	avg_समय_slots_per_mtp = dc_fixpt_भाग(pbn, pbn_per_slot);

	stream_encoder->funcs->set_throttled_vcp_size(
		stream_encoder,
		avg_समय_slots_per_mtp);

	वापस DC_OK;

पूर्ण

अटल क्रमागत dc_status deallocate_mst_payload(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->link;
	काष्ठा link_encoder *link_encoder = link->link_enc;
	काष्ठा stream_encoder *stream_encoder = pipe_ctx->stream_res.stream_enc;
	काष्ठा dp_mst_stream_allocation_table proposed_table = अणु0पूर्ण;
	काष्ठा fixed31_32 avg_समय_slots_per_mtp = dc_fixpt_from_पूर्णांक(0);
	uपूर्णांक8_t i;
	bool mst_mode = (link->type == dc_connection_mst_branch);
	DC_LOGGER_INIT(link->ctx->logger);

	/* deallocate_mst_payload is called beक्रमe disable link. When mode or
	 * disable/enable monitor, new stream is created which is not in link
	 * stream[] yet. For this, payload is not allocated yet, so de-alloc
	 * should not करोne. For new mode set, map_resources will get engine
	 * क्रम new stream, so stream_enc->id should be validated until here.
	 */

	/* slot X.Y */
	stream_encoder->funcs->set_throttled_vcp_size(
		stream_encoder,
		avg_समय_slots_per_mtp);

	/* TODO: which component is responsible क्रम हटाओ payload table? */
	अगर (mst_mode) अणु
		अगर (dm_helpers_dp_mst_ग_लिखो_payload_allocation_table(
				stream->ctx,
				stream,
				&proposed_table,
				false)) अणु

			update_mst_stream_alloc_table(
				link, pipe_ctx->stream_res.stream_enc, &proposed_table);
		पूर्ण
		अन्यथा अणु
				DC_LOG_WARNING("Failed to update"
						"MST allocation table for"
						"pipe idx:%d\n",
						pipe_ctx->pipe_idx);
		पूर्ण
	पूर्ण

	DC_LOG_MST("%s"
			"stream_count: %d: ",
			__func__,
			link->mst_stream_alloc_table.stream_count);

	क्रम (i = 0; i < MAX_CONTROLLER_NUM; i++) अणु
		DC_LOG_MST("stream_enc[%d]: %p      "
		"stream[%d].vcp_id: %d      "
		"stream[%d].slot_count: %d\n",
		i,
		(व्योम *) link->mst_stream_alloc_table.stream_allocations[i].stream_enc,
		i,
		link->mst_stream_alloc_table.stream_allocations[i].vcp_id,
		i,
		link->mst_stream_alloc_table.stream_allocations[i].slot_count);
	पूर्ण

	link_encoder->funcs->update_mst_stream_allocation_table(
		link_encoder,
		&link->mst_stream_alloc_table);

	अगर (mst_mode) अणु
		dm_helpers_dp_mst_poll_क्रम_allocation_change_trigger(
			stream->ctx,
			stream);

		dm_helpers_dp_mst_send_payload_allocation(
			stream->ctx,
			stream,
			false);
	पूर्ण

	वापस DC_OK;
पूर्ण


#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
अटल व्योम update_psp_stream_config(काष्ठा pipe_ctx *pipe_ctx, bool dpms_off)
अणु
	काष्ठा cp_psp *cp_psp = &pipe_ctx->stream->ctx->cp_psp;
	अगर (cp_psp && cp_psp->funcs.update_stream_config) अणु
		काष्ठा cp_psp_stream_config config = अणु0पूर्ण;
		क्रमागत dp_panel_mode panel_mode =
				dp_get_panel_mode(pipe_ctx->stream->link);

		config.otg_inst = (uपूर्णांक8_t) pipe_ctx->stream_res.tg->inst;
		config.dig_fe = (uपूर्णांक8_t) pipe_ctx->stream_res.stream_enc->stream_enc_inst;
		config.dig_be = pipe_ctx->stream->link->link_enc_hw_inst;
		config.dpms_off = dpms_off;
		config.dm_stream_ctx = pipe_ctx->stream->dm_stream_context;
		config.assr_enabled = (panel_mode == DP_PANEL_MODE_EDP);
		config.mst_enabled = (pipe_ctx->stream->संकेत ==
				SIGNAL_TYPE_DISPLAY_PORT_MST);
		cp_psp->funcs.update_stream_config(cp_psp->handle, &config);
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम core_link_enable_stream(
		काष्ठा dc_state *state,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc *dc = pipe_ctx->stream->ctx->dc;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	क्रमागत dc_status status;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	क्रमागत otg_out_mux_dest otg_out_dest = OUT_MUX_DIO;
#पूर्ण_अगर
	DC_LOGGER_INIT(pipe_ctx->stream->ctx->logger);

	अगर (!IS_DIAG_DC(dc->ctx->dce_environment) &&
			dc_is_भव_संकेत(pipe_ctx->stream->संकेत))
		वापस;

	अगर (!dc_is_भव_संकेत(pipe_ctx->stream->संकेत)) अणु
		stream->link->link_enc->funcs->setup(
			stream->link->link_enc,
			pipe_ctx->stream->संकेत);
		pipe_ctx->stream_res.stream_enc->funcs->setup_stereo_sync(
			pipe_ctx->stream_res.stream_enc,
			pipe_ctx->stream_res.tg->inst,
			stream->timing.timing_3d_क्रमmat != TIMING_3D_FORMAT_NONE);
	पूर्ण

	अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत))
		pipe_ctx->stream_res.stream_enc->funcs->dp_set_stream_attribute(
			pipe_ctx->stream_res.stream_enc,
			&stream->timing,
			stream->output_color_space,
			stream->use_vsc_sdp_क्रम_colorimetry,
			stream->link->dpcd_caps.dprx_feature.bits.SST_SPLIT_SDP_CAP);

	अगर (dc_is_hdmi_पंचांगds_संकेत(pipe_ctx->stream->संकेत))
		pipe_ctx->stream_res.stream_enc->funcs->hdmi_set_stream_attribute(
			pipe_ctx->stream_res.stream_enc,
			&stream->timing,
			stream->phy_pix_clk,
			pipe_ctx->stream_res.audio != शून्य);

	pipe_ctx->stream->link->link_state_valid = true;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	अगर (pipe_ctx->stream_res.tg->funcs->set_out_mux)
		pipe_ctx->stream_res.tg->funcs->set_out_mux(pipe_ctx->stream_res.tg, otg_out_dest);
#पूर्ण_अगर

	अगर (dc_is_dvi_संकेत(pipe_ctx->stream->संकेत))
		pipe_ctx->stream_res.stream_enc->funcs->dvi_set_stream_attribute(
			pipe_ctx->stream_res.stream_enc,
			&stream->timing,
			(pipe_ctx->stream->संकेत == SIGNAL_TYPE_DVI_DUAL_LINK) ?
			true : false);

	अगर (dc_is_lvds_संकेत(pipe_ctx->stream->संकेत))
		pipe_ctx->stream_res.stream_enc->funcs->lvds_set_stream_attribute(
			pipe_ctx->stream_res.stream_enc,
			&stream->timing);

	अगर (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु
		bool apply_edp_fast_boot_optimization =
			pipe_ctx->stream->apply_edp_fast_boot_optimization;

		pipe_ctx->stream->apply_edp_fast_boot_optimization = false;

		resource_build_info_frame(pipe_ctx);
		dc->hwss.update_info_frame(pipe_ctx);

		/* Do not touch link on seamless boot optimization. */
		अगर (pipe_ctx->stream->apply_seamless_boot_optimization) अणु
			pipe_ctx->stream->dpms_off = false;

			/* Still enable stream features & audio on seamless boot क्रम DP बाह्यal displays */
			अगर (pipe_ctx->stream->संकेत == SIGNAL_TYPE_DISPLAY_PORT) अणु
				enable_stream_features(pipe_ctx);
				अगर (pipe_ctx->stream_res.audio != शून्य) अणु
					pipe_ctx->stream_res.stream_enc->funcs->dp_audio_enable(pipe_ctx->stream_res.stream_enc);
					dc->hwss.enable_audio_stream(pipe_ctx);
				पूर्ण
			पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
			update_psp_stream_config(pipe_ctx, false);
#पूर्ण_अगर
			वापस;
		पूर्ण

		/* eDP lit up by bios alपढ़ोy, no need to enable again. */
		अगर (pipe_ctx->stream->संकेत == SIGNAL_TYPE_EDP &&
					apply_edp_fast_boot_optimization &&
					!pipe_ctx->stream->timing.flags.DSC) अणु
			pipe_ctx->stream->dpms_off = false;
#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
			update_psp_stream_config(pipe_ctx, false);
#पूर्ण_अगर
			वापस;
		पूर्ण

		अगर (pipe_ctx->stream->dpms_off)
			वापस;

		/* Have to setup DSC beक्रमe DIG FE and BE are connected (which happens beक्रमe the
		 * link training). This is to make sure the bandwidth sent to DIG BE won't be
		 * bigger than what the link and/or DIG BE can handle. VBID[6]/CompressedStream_flag
		 * will be स्वतःmatically set at a later समय when the video is enabled
		 * (DP_VID_STREAM_EN = 1).
		 */
		अगर (pipe_ctx->stream->timing.flags.DSC) अणु
			अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत) ||
					dc_is_भव_संकेत(pipe_ctx->stream->संकेत))
				dp_set_dsc_enable(pipe_ctx, true);
		पूर्ण

		status = enable_link(state, pipe_ctx);

		अगर (status != DC_OK) अणु
			DC_LOG_WARNING("enabling link %u failed: %d\n",
			pipe_ctx->stream->link->link_index,
			status);

			/* Abort stream enable *unless* the failure was due to
			 * DP link training - some DP monitors will recover and
			 * show the stream anyway. But MST displays can't proceed
			 * without link training.
			 */
			अगर (status != DC_FAIL_DP_LINK_TRAINING ||
					pipe_ctx->stream->संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST) अणु
				BREAK_TO_DEBUGGER();
				वापस;
			पूर्ण
		पूर्ण

		/* turn off otg test pattern अगर enable */
		अगर (pipe_ctx->stream_res.tg->funcs->set_test_pattern)
			pipe_ctx->stream_res.tg->funcs->set_test_pattern(pipe_ctx->stream_res.tg,
					CONTROLLER_DP_TEST_PATTERN_VIDEOMODE,
					COLOR_DEPTH_UNDEFINED);

		/* This second call is needed to reconfigure the DIG
		 * as a workaround क्रम the incorrect value being applied
		 * from transmitter control.
		 */
		अगर (!dc_is_भव_संकेत(pipe_ctx->stream->संकेत))
			stream->link->link_enc->funcs->setup(
				stream->link->link_enc,
				pipe_ctx->stream->संकेत);

		dc->hwss.enable_stream(pipe_ctx);

		/* Set DPS PPS SDP (AKA "info frames") */
		अगर (pipe_ctx->stream->timing.flags.DSC) अणु
			अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत) ||
					dc_is_भव_संकेत(pipe_ctx->stream->संकेत)) अणु
				dp_set_dsc_on_rx(pipe_ctx, true);
				dp_set_dsc_pps_sdp(pipe_ctx, true);
			पूर्ण
		पूर्ण

		अगर (pipe_ctx->stream->संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST)
			dc_link_allocate_mst_payload(pipe_ctx);

		dc->hwss.unblank_stream(pipe_ctx,
			&pipe_ctx->stream->link->cur_link_settings);

		अगर (stream->sink_patches.delay_ignore_msa > 0)
			msleep(stream->sink_patches.delay_ignore_msa);

		अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत))
			enable_stream_features(pipe_ctx);
#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
		update_psp_stream_config(pipe_ctx, false);
#पूर्ण_अगर

		dc->hwss.enable_audio_stream(pipe_ctx);

	पूर्ण अन्यथा अणु // अगर (IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment))
		अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत) ||
				dc_is_भव_संकेत(pipe_ctx->stream->संकेत))
			dp_set_dsc_enable(pipe_ctx, true);

	पूर्ण

	अगर (pipe_ctx->stream->संकेत == SIGNAL_TYPE_HDMI_TYPE_A) अणु
		core_link_set_avmute(pipe_ctx, false);
	पूर्ण
पूर्ण

व्योम core_link_disable_stream(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc  *dc = pipe_ctx->stream->ctx->dc;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->sink->link;

	अगर (!IS_DIAG_DC(dc->ctx->dce_environment) &&
			dc_is_भव_संकेत(pipe_ctx->stream->संकेत))
		वापस;

	अगर (!pipe_ctx->stream->sink->edid_caps.panel_patch.skip_avmute) अणु
		अगर (dc_is_hdmi_संकेत(pipe_ctx->stream->संकेत))
			core_link_set_avmute(pipe_ctx, true);
	पूर्ण

	dc->hwss.disable_audio_stream(pipe_ctx);

#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
	update_psp_stream_config(pipe_ctx, true);
#पूर्ण_अगर
	dc->hwss.blank_stream(pipe_ctx);

	अगर (pipe_ctx->stream->संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST)
		deallocate_mst_payload(pipe_ctx);

	अगर (dc_is_hdmi_संकेत(pipe_ctx->stream->संकेत)) अणु
		काष्ठा ext_hdmi_settings settings = अणु0पूर्ण;
		क्रमागत engine_id eng_id = pipe_ctx->stream_res.stream_enc->id;

		अचिन्हित लघु masked_chip_caps = link->chip_caps &
				EXT_DISPLAY_PATH_CAPS__EXT_CHIP_MASK;
		//Need to inक्रमm that sink is going to use legacy HDMI mode.
		dal_ddc_service_ग_लिखो_scdc_data(
			link->ddc,
			165000,//vbios only handles 165Mhz.
			false);
		अगर (masked_chip_caps == EXT_DISPLAY_PATH_CAPS__HDMI20_TISN65DP159RSBT) अणु
			/* DP159, Reसमयr settings */
			अगर (get_ext_hdmi_settings(pipe_ctx, eng_id, &settings))
				ग_लिखो_i2c_reसमयr_setting(pipe_ctx,
						false, false, &settings);
			अन्यथा
				ग_लिखो_i2c_शेष_reसमयr_setting(pipe_ctx,
						false, false);
		पूर्ण अन्यथा अगर (masked_chip_caps == EXT_DISPLAY_PATH_CAPS__HDMI20_PI3EQX1204) अणु
			/* PI3EQX1204, Redriver settings */
			ग_लिखो_i2c_redriver_setting(pipe_ctx, false);
		पूर्ण
	पूर्ण

	disable_link(pipe_ctx->stream->link, pipe_ctx->stream->संकेत);

	dc->hwss.disable_stream(pipe_ctx);

	अगर (pipe_ctx->stream->timing.flags.DSC) अणु
		अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत))
			dp_set_dsc_enable(pipe_ctx, false);
	पूर्ण
पूर्ण

व्योम core_link_set_avmute(काष्ठा pipe_ctx *pipe_ctx, bool enable)
अणु
	काष्ठा dc  *dc = pipe_ctx->stream->ctx->dc;

	अगर (!dc_is_hdmi_संकेत(pipe_ctx->stream->संकेत))
		वापस;

	dc->hwss.set_avmute(pipe_ctx, enable);
पूर्ण

/**
 *  dc_link_enable_hpd_filter:
 *     If enable is true, programs HPD filter on associated HPD line using
 *     delay_on_disconnect/delay_on_connect values dependent on
 *     link->connector_संकेत
 *
 *     If enable is false, programs HPD filter on associated HPD line with no
 *     delays on connect or disconnect
 *
 *  @link:   poपूर्णांकer to the dc link
 *  @enable: boolean specअगरying whether to enable hbd
 */
व्योम dc_link_enable_hpd_filter(काष्ठा dc_link *link, bool enable)
अणु
	काष्ठा gpio *hpd;

	अगर (enable) अणु
		link->is_hpd_filter_disabled = false;
		program_hpd_filter(link);
	पूर्ण अन्यथा अणु
		link->is_hpd_filter_disabled = true;
		/* Obtain HPD handle */
		hpd = get_hpd_gpio(link->ctx->dc_bios, link->link_id, link->ctx->gpio_service);

		अगर (!hpd)
			वापस;

		/* Setup HPD filtering */
		अगर (dal_gpio_खोलो(hpd, GPIO_MODE_INTERRUPT) == GPIO_RESULT_OK) अणु
			काष्ठा gpio_hpd_config config;

			config.delay_on_connect = 0;
			config.delay_on_disconnect = 0;

			dal_irq_setup_hpd_filter(hpd, &config);

			dal_gpio_बंद(hpd);
		पूर्ण अन्यथा अणु
			ASSERT_CRITICAL(false);
		पूर्ण
		/* Release HPD handle */
		dal_gpio_destroy_irq(&hpd);
	पूर्ण
पूर्ण

uपूर्णांक32_t dc_bandwidth_in_kbps_from_timing(
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	uपूर्णांक32_t bits_per_channel = 0;
	uपूर्णांक32_t kbps;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	अगर (timing->flags.DSC) अणु
		वापस dc_dsc_stream_bandwidth_in_kbps(timing->pix_clk_100hz, timing->dsc_cfg.bits_per_pixel);
	पूर्ण
#पूर्ण_अगर

	चयन (timing->display_color_depth) अणु
	हाल COLOR_DEPTH_666:
		bits_per_channel = 6;
		अवरोध;
	हाल COLOR_DEPTH_888:
		bits_per_channel = 8;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		bits_per_channel = 10;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		bits_per_channel = 12;
		अवरोध;
	हाल COLOR_DEPTH_141414:
		bits_per_channel = 14;
		अवरोध;
	हाल COLOR_DEPTH_161616:
		bits_per_channel = 16;
		अवरोध;
	शेष:
		ASSERT(bits_per_channel != 0);
		bits_per_channel = 8;
		अवरोध;
	पूर्ण

	kbps = timing->pix_clk_100hz / 10;
	kbps *= bits_per_channel;

	अगर (timing->flags.Y_ONLY != 1) अणु
		/*Only YOnly make reduce bandwidth by 1/3 compares to RGB*/
		kbps *= 3;
		अगर (timing->pixel_encoding == PIXEL_ENCODING_YCBCR420)
			kbps /= 2;
		अन्यथा अगर (timing->pixel_encoding == PIXEL_ENCODING_YCBCR422)
			kbps = kbps * 2 / 3;
	पूर्ण

	वापस kbps;

पूर्ण

व्योम dc_link_set_drive_settings(काष्ठा dc *dc,
				काष्ठा link_training_settings *lt_settings,
				स्थिर काष्ठा dc_link *link)
अणु

	पूर्णांक i;

	क्रम (i = 0; i < dc->link_count; i++) अणु
		अगर (dc->links[i] == link)
			अवरोध;
	पूर्ण

	अगर (i >= dc->link_count)
		ASSERT_CRITICAL(false);

	dc_link_dp_set_drive_settings(dc->links[i], lt_settings);
पूर्ण

व्योम dc_link_perक्रमm_link_training(काष्ठा dc *dc,
				   काष्ठा dc_link_settings *link_setting,
				   bool skip_video_pattern)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dc->link_count; i++)
		dc_link_dp_perक्रमm_link_training(
			dc->links[i],
			link_setting,
			skip_video_pattern);
पूर्ण

व्योम dc_link_set_preferred_link_settings(काष्ठा dc *dc,
					 काष्ठा dc_link_settings *link_setting,
					 काष्ठा dc_link *link)
अणु
	पूर्णांक i;
	काष्ठा pipe_ctx *pipe;
	काष्ठा dc_stream_state *link_stream;
	काष्ठा dc_link_settings store_settings = *link_setting;

	link->preferred_link_setting = store_settings;

	/* Retrain with preferred link settings only relevant क्रम
	 * DP संकेत type
	 * Check क्रम non-DP संकेत or अगर passive करोngle present
	 */
	अगर (!dc_is_dp_संकेत(link->connector_संकेत) ||
		link->करोngle_max_pix_clk > 0)
		वापस;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe = &dc->current_state->res_ctx.pipe_ctx[i];
		अगर (pipe->stream && pipe->stream->link) अणु
			अगर (pipe->stream->link == link) अणु
				link_stream = pipe->stream;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Stream not found */
	अगर (i == MAX_PIPES)
		वापस;

	/* Cannot retrain link अगर backend is off */
	अगर (link_stream->dpms_off)
		वापस;

	decide_link_settings(link_stream, &store_settings);

	अगर ((store_settings.lane_count != LANE_COUNT_UNKNOWN) &&
		(store_settings.link_rate != LINK_RATE_UNKNOWN))
		dp_retrain_link_dp_test(link, &store_settings, false);
पूर्ण

व्योम dc_link_set_preferred_training_settings(काष्ठा dc *dc,
						 काष्ठा dc_link_settings *link_setting,
						 काष्ठा dc_link_training_overrides *lt_overrides,
						 काष्ठा dc_link *link,
						 bool skip_immediate_retrain)
अणु
	अगर (lt_overrides != शून्य)
		link->preferred_training_settings = *lt_overrides;
	अन्यथा
		स_रखो(&link->preferred_training_settings, 0, माप(link->preferred_training_settings));

	अगर (link_setting != शून्य) अणु
		link->preferred_link_setting = *link_setting;
	पूर्ण अन्यथा अणु
		link->preferred_link_setting.lane_count = LANE_COUNT_UNKNOWN;
		link->preferred_link_setting.link_rate = LINK_RATE_UNKNOWN;
	पूर्ण

	/* Retrain now, or रुको until next stream update to apply */
	अगर (skip_immediate_retrain == false)
		dc_link_set_preferred_link_settings(dc, &link->preferred_link_setting, link);
पूर्ण

व्योम dc_link_enable_hpd(स्थिर काष्ठा dc_link *link)
अणु
	dc_link_dp_enable_hpd(link);
पूर्ण

व्योम dc_link_disable_hpd(स्थिर काष्ठा dc_link *link)
अणु
	dc_link_dp_disable_hpd(link);
पूर्ण

व्योम dc_link_set_test_pattern(काष्ठा dc_link *link,
			      क्रमागत dp_test_pattern test_pattern,
			      क्रमागत dp_test_pattern_color_space test_pattern_color_space,
			      स्थिर काष्ठा link_training_settings *p_link_settings,
			      स्थिर अचिन्हित अक्षर *p_custom_pattern,
			      अचिन्हित पूर्णांक cust_pattern_size)
अणु
	अगर (link != शून्य)
		dc_link_dp_set_test_pattern(
			link,
			test_pattern,
			test_pattern_color_space,
			p_link_settings,
			p_custom_pattern,
			cust_pattern_size);
पूर्ण

uपूर्णांक32_t dc_link_bandwidth_kbps(
	स्थिर काष्ठा dc_link *link,
	स्थिर काष्ठा dc_link_settings *link_setting)
अणु
	uपूर्णांक32_t link_bw_kbps =
		link_setting->link_rate * LINK_RATE_REF_FREQ_IN_KHZ; /* bytes per sec */

	link_bw_kbps *= 8;   /* 8 bits per byte*/
	link_bw_kbps *= link_setting->lane_count;

	अगर (dc_link_should_enable_fec(link)) अणु
		/* Account क्रम FEC overhead.
		 * We have to करो it based on caps,
		 * and not based on FEC being set पढ़ोy,
		 * because FEC is set पढ़ोy too late in
		 * the process to correctly be picked up
		 * by mode क्रमागतeration.
		 *
		 * There's enough zeros at the end of 'kbps'
		 * that make the below operation 100% precise
		 * क्रम our purposes.
		 * 'long long' makes it work even क्रम HDMI 2.1
		 * max bandwidth (and much, much bigger bandwidths
		 * than that, actually).
		 *
		 * NOTE: Reducing link BW by 3% may not be precise
		 * because it may be a stream BT that increases by 3%, and so
		 * 1/1.03 = 0.970873 factor should have been used instead,
		 * but the dअगरference is minimal and is in a safe direction,
		 * which all works well around potential ambiguity of DP 1.4a spec.
		 */
		दीर्घ दीर्घ fec_link_bw_kbps = link_bw_kbps * 970LL;
		link_bw_kbps = (uपूर्णांक32_t)(भाग64_s64(fec_link_bw_kbps, 1000LL));
	पूर्ण

	वापस link_bw_kbps;

पूर्ण

स्थिर काष्ठा dc_link_settings *dc_link_get_link_cap(
		स्थिर काष्ठा dc_link *link)
अणु
	अगर (link->preferred_link_setting.lane_count != LANE_COUNT_UNKNOWN &&
			link->preferred_link_setting.link_rate != LINK_RATE_UNKNOWN)
		वापस &link->preferred_link_setting;
	वापस &link->verअगरied_link_cap;
पूर्ण

व्योम dc_link_overग_लिखो_extended_receiver_cap(
		काष्ठा dc_link *link)
अणु
	dp_overग_लिखो_extended_receiver_cap(link);
पूर्ण

bool dc_link_is_fec_supported(स्थिर काष्ठा dc_link *link)
अणु
	वापस (dc_is_dp_संकेत(link->connector_संकेत) &&
			link->link_enc->features.fec_supported &&
			link->dpcd_caps.fec_cap.bits.FEC_CAPABLE &&
			!IS_FPGA_MAXIMUS_DC(link->ctx->dce_environment));
पूर्ण

bool dc_link_should_enable_fec(स्थिर काष्ठा dc_link *link)
अणु
	bool is_fec_disable = false;
	bool ret = false;

	अगर ((link->connector_संकेत != SIGNAL_TYPE_DISPLAY_PORT_MST &&
			link->local_sink &&
			link->local_sink->edid_caps.panel_patch.disable_fec) ||
			(link->connector_संकेत == SIGNAL_TYPE_EDP &&
					link->dc->debug.क्रमce_enable_edp_fec == false)) // Disable FEC क्रम eDP
		is_fec_disable = true;

	अगर (dc_link_is_fec_supported(link) && !link->dc->debug.disable_fec && !is_fec_disable)
		ret = true;

	वापस ret;
पूर्ण
