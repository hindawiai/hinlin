<शैली गुरु>
/*
 * Copyright तऊ 2012 Intel Corporation
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Keith Packard <keithp@keithp.com>
 *
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "gma_display.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

/**
 * काष्ठा i2c_algo_dp_aux_data - driver पूर्णांकerface काष्ठाure क्रम i2c over dp
 * 				 aux algorithm
 * @running: set by the algo indicating whether an i2c is ongoing or whether
 * 	     the i2c bus is quiescent
 * @address: i2c target address क्रम the currently ongoing transfer
 * @aux_ch: driver callback to transfer a single byte of the i2c payload
 */
काष्ठा i2c_algo_dp_aux_data अणु
	bool running;
	u16 address;
	पूर्णांक (*aux_ch) (काष्ठा i2c_adapter *adapter,
		       पूर्णांक mode, uपूर्णांक8_t ग_लिखो_byte,
		       uपूर्णांक8_t *पढ़ो_byte);
पूर्ण;

/* Run a single AUX_CH I2C transaction, writing/पढ़ोing data as necessary */
अटल पूर्णांक
i2c_algo_dp_aux_transaction(काष्ठा i2c_adapter *adapter, पूर्णांक mode,
			    uपूर्णांक8_t ग_लिखो_byte, uपूर्णांक8_t *पढ़ो_byte)
अणु
	काष्ठा i2c_algo_dp_aux_data *algo_data = adapter->algo_data;
	पूर्णांक ret;

	ret = (*algo_data->aux_ch)(adapter, mode,
				   ग_लिखो_byte, पढ़ो_byte);
	वापस ret;
पूर्ण

/*
 * I2C over AUX CH
 */

/*
 * Send the address. If the I2C link is running, this 'restarts'
 * the connection with the new address, this is used क्रम करोing
 * a ग_लिखो followed by a पढ़ो (as needed क्रम DDC)
 */
अटल पूर्णांक
i2c_algo_dp_aux_address(काष्ठा i2c_adapter *adapter, u16 address, bool पढ़ोing)
अणु
	काष्ठा i2c_algo_dp_aux_data *algo_data = adapter->algo_data;
	पूर्णांक mode = MODE_I2C_START;
	पूर्णांक ret;

	अगर (पढ़ोing)
		mode |= MODE_I2C_READ;
	अन्यथा
		mode |= MODE_I2C_WRITE;
	algo_data->address = address;
	algo_data->running = true;
	ret = i2c_algo_dp_aux_transaction(adapter, mode, 0, शून्य);
	वापस ret;
पूर्ण

/*
 * Stop the I2C transaction. This बंदs out the link, sending
 * a bare address packet with the MOT bit turned off
 */
अटल व्योम
i2c_algo_dp_aux_stop(काष्ठा i2c_adapter *adapter, bool पढ़ोing)
अणु
	काष्ठा i2c_algo_dp_aux_data *algo_data = adapter->algo_data;
	पूर्णांक mode = MODE_I2C_STOP;

	अगर (पढ़ोing)
		mode |= MODE_I2C_READ;
	अन्यथा
		mode |= MODE_I2C_WRITE;
	अगर (algo_data->running) अणु
		(व्योम) i2c_algo_dp_aux_transaction(adapter, mode, 0, शून्य);
		algo_data->running = false;
	पूर्ण
पूर्ण

/*
 * Write a single byte to the current I2C address, the
 * the I2C link must be running or this वापसs -EIO
 */
अटल पूर्णांक
i2c_algo_dp_aux_put_byte(काष्ठा i2c_adapter *adapter, u8 byte)
अणु
	काष्ठा i2c_algo_dp_aux_data *algo_data = adapter->algo_data;
	पूर्णांक ret;

	अगर (!algo_data->running)
		वापस -EIO;

	ret = i2c_algo_dp_aux_transaction(adapter, MODE_I2C_WRITE, byte, शून्य);
	वापस ret;
पूर्ण

/*
 * Read a single byte from the current I2C address, the
 * I2C link must be running or this वापसs -EIO
 */
अटल पूर्णांक
i2c_algo_dp_aux_get_byte(काष्ठा i2c_adapter *adapter, u8 *byte_ret)
अणु
	काष्ठा i2c_algo_dp_aux_data *algo_data = adapter->algo_data;
	पूर्णांक ret;

	अगर (!algo_data->running)
		वापस -EIO;

	ret = i2c_algo_dp_aux_transaction(adapter, MODE_I2C_READ, 0, byte_ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
i2c_algo_dp_aux_xfer(काष्ठा i2c_adapter *adapter,
		     काष्ठा i2c_msg *msgs,
		     पूर्णांक num)
अणु
	पूर्णांक ret = 0;
	bool पढ़ोing = false;
	पूर्णांक m;
	पूर्णांक b;

	क्रम (m = 0; m < num; m++) अणु
		u16 len = msgs[m].len;
		u8 *buf = msgs[m].buf;
		पढ़ोing = (msgs[m].flags & I2C_M_RD) != 0;
		ret = i2c_algo_dp_aux_address(adapter, msgs[m].addr, पढ़ोing);
		अगर (ret < 0)
			अवरोध;
		अगर (पढ़ोing) अणु
			क्रम (b = 0; b < len; b++) अणु
				ret = i2c_algo_dp_aux_get_byte(adapter, &buf[b]);
				अगर (ret < 0)
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (b = 0; b < len; b++) अणु
				ret = i2c_algo_dp_aux_put_byte(adapter, buf[b]);
				अगर (ret < 0)
					अवरोध;
			पूर्ण
		पूर्ण
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	अगर (ret >= 0)
		ret = num;
	i2c_algo_dp_aux_stop(adapter, पढ़ोing);
	DRM_DEBUG_KMS("dp_aux_xfer return %d\n", ret);
	वापस ret;
पूर्ण

अटल u32
i2c_algo_dp_aux_functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
	       I2C_FUNC_SMBUS_READ_BLOCK_DATA |
	       I2C_FUNC_SMBUS_BLOCK_PROC_CALL |
	       I2C_FUNC_10BIT_ADDR;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm i2c_dp_aux_algo = अणु
	.master_xfer	= i2c_algo_dp_aux_xfer,
	.functionality	= i2c_algo_dp_aux_functionality,
पूर्ण;

अटल व्योम
i2c_dp_aux_reset_bus(काष्ठा i2c_adapter *adapter)
अणु
	(व्योम) i2c_algo_dp_aux_address(adapter, 0, false);
	(व्योम) i2c_algo_dp_aux_stop(adapter, false);
पूर्ण

अटल पूर्णांक
i2c_dp_aux_prepare_bus(काष्ठा i2c_adapter *adapter)
अणु
	adapter->algo = &i2c_dp_aux_algo;
	adapter->retries = 3;
	i2c_dp_aux_reset_bus(adapter);
	वापस 0;
पूर्ण

/*
 * FIXME: This is the old dp aux helper, gma500 is the last driver that needs to
 * be ported over to the new helper code in drm_dp_helper.c like i915 or radeon.
 */
अटल पूर्णांक
i2c_dp_aux_add_bus(काष्ठा i2c_adapter *adapter)
अणु
	पूर्णांक error;

	error = i2c_dp_aux_prepare_bus(adapter);
	अगर (error)
		वापस error;
	error = i2c_add_adapter(adapter);
	वापस error;
पूर्ण

#घोषणा _रुको_क्रम(COND, MS, W) (अणु \
        अचिन्हित दीर्घ समयout__ = jअगरfies + msecs_to_jअगरfies(MS);       \
        पूर्णांक ret__ = 0;                                                  \
        जबतक (! (COND)) अणु                                              \
                अगर (समय_after(jअगरfies, समयout__)) अणु                   \
                        ret__ = -ETIMEDOUT;                             \
                        अवरोध;                                          \
                पूर्ण                                                       \
                अगर (W && !in_dbg_master()) msleep(W);                   \
        पूर्ण                                                               \
        ret__;                                                          \
पूर्ण)      

#घोषणा रुको_क्रम(COND, MS) _रुको_क्रम(COND, MS, 1)

#घोषणा DP_LINK_CHECK_TIMEOUT	(10 * 1000)

#घोषणा DP_LINK_CONFIGURATION_SIZE	9

#घोषणा CDV_FAST_LINK_TRAIN	1

काष्ठा cdv_पूर्णांकel_dp अणु
	uपूर्णांक32_t output_reg;
	uपूर्णांक32_t DP;
	uपूर्णांक8_t  link_configuration[DP_LINK_CONFIGURATION_SIZE];
	bool has_audio;
	पूर्णांक क्रमce_audio;
	uपूर्णांक32_t color_range;
	uपूर्णांक8_t link_bw;
	uपूर्णांक8_t lane_count;
	uपूर्णांक8_t dpcd[4];
	काष्ठा gma_encoder *encoder;
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_algo_dp_aux_data algo;
	uपूर्णांक8_t	train_set[4];
	uपूर्णांक8_t link_status[DP_LINK_STATUS_SIZE];
	पूर्णांक panel_घातer_up_delay;
	पूर्णांक panel_घातer_करोwn_delay;
	पूर्णांक panel_घातer_cycle_delay;
	पूर्णांक backlight_on_delay;
	पूर्णांक backlight_off_delay;
	काष्ठा drm_display_mode *panel_fixed_mode;  /* क्रम eDP */
	bool panel_on;
पूर्ण;

काष्ठा ddi_regoff अणु
	uपूर्णांक32_t	PreEmph1;
	uपूर्णांक32_t	PreEmph2;
	uपूर्णांक32_t	VSwing1;
	uपूर्णांक32_t	VSwing2;
	uपूर्णांक32_t	VSwing3;
	uपूर्णांक32_t	VSwing4;
	uपूर्णांक32_t	VSwing5;
पूर्ण;

अटल काष्ठा ddi_regoff ddi_DP_train_table[] = अणु
	अणु.PreEmph1 = 0x812c, .PreEmph2 = 0x8124, .VSwing1 = 0x8154,
	.VSwing2 = 0x8148, .VSwing3 = 0x814C, .VSwing4 = 0x8150,
	.VSwing5 = 0x8158,पूर्ण,
	अणु.PreEmph1 = 0x822c, .PreEmph2 = 0x8224, .VSwing1 = 0x8254,
	.VSwing2 = 0x8248, .VSwing3 = 0x824C, .VSwing4 = 0x8250,
	.VSwing5 = 0x8258,पूर्ण,
पूर्ण;

अटल uपूर्णांक32_t dp_vswing_premph_table[] = अणु
        0x55338954,	0x4000,
        0x554d8954,	0x2000,
        0x55668954,	0,
        0x559ac0d4,	0x6000,
पूर्ण;
/**
 * is_edp - is the given port attached to an eDP panel (either CPU or PCH)
 * @encoder: GMA encoder काष्ठा
 *
 * If a CPU or PCH DP output is attached to an eDP panel, this function
 * will वापस true, and false otherwise.
 */
अटल bool is_edp(काष्ठा gma_encoder *encoder)
अणु
	वापस encoder->type == INTEL_OUTPUT_EDP;
पूर्ण


अटल व्योम cdv_पूर्णांकel_dp_start_link_train(काष्ठा gma_encoder *encoder);
अटल व्योम cdv_पूर्णांकel_dp_complete_link_train(काष्ठा gma_encoder *encoder);
अटल व्योम cdv_पूर्णांकel_dp_link_करोwn(काष्ठा gma_encoder *encoder);

अटल पूर्णांक
cdv_पूर्णांकel_dp_max_lane_count(काष्ठा gma_encoder *encoder)
अणु
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	पूर्णांक max_lane_count = 4;

	अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] >= 0x11) अणु
		max_lane_count = पूर्णांकel_dp->dpcd[DP_MAX_LANE_COUNT] & 0x1f;
		चयन (max_lane_count) अणु
		हाल 1: हाल 2: हाल 4:
			अवरोध;
		शेष:
			max_lane_count = 4;
		पूर्ण
	पूर्ण
	वापस max_lane_count;
पूर्ण

अटल पूर्णांक
cdv_पूर्णांकel_dp_max_link_bw(काष्ठा gma_encoder *encoder)
अणु
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	पूर्णांक max_link_bw = पूर्णांकel_dp->dpcd[DP_MAX_LINK_RATE];

	चयन (max_link_bw) अणु
	हाल DP_LINK_BW_1_62:
	हाल DP_LINK_BW_2_7:
		अवरोध;
	शेष:
		max_link_bw = DP_LINK_BW_1_62;
		अवरोध;
	पूर्ण
	वापस max_link_bw;
पूर्ण

अटल पूर्णांक
cdv_पूर्णांकel_dp_link_घड़ी(uपूर्णांक8_t link_bw)
अणु
	अगर (link_bw == DP_LINK_BW_2_7)
		वापस 270000;
	अन्यथा
		वापस 162000;
पूर्ण

अटल पूर्णांक
cdv_पूर्णांकel_dp_link_required(पूर्णांक pixel_घड़ी, पूर्णांक bpp)
अणु
	वापस (pixel_घड़ी * bpp + 7) / 8;
पूर्ण

अटल पूर्णांक
cdv_पूर्णांकel_dp_max_data_rate(पूर्णांक max_link_घड़ी, पूर्णांक max_lanes)
अणु
	वापस (max_link_घड़ी * max_lanes * 19) / 20;
पूर्ण

अटल व्योम cdv_पूर्णांकel_edp_panel_vdd_on(काष्ठा gma_encoder *पूर्णांकel_encoder)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_encoder->base.dev;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_encoder->dev_priv;
	u32 pp;

	अगर (पूर्णांकel_dp->panel_on) अणु
		DRM_DEBUG_KMS("Skip VDD on because of panel on\n");
		वापस;
	पूर्ण	
	DRM_DEBUG_KMS("\n");

	pp = REG_READ(PP_CONTROL);

	pp |= EDP_FORCE_VDD;
	REG_WRITE(PP_CONTROL, pp);
	REG_READ(PP_CONTROL);
	msleep(पूर्णांकel_dp->panel_घातer_up_delay);
पूर्ण

अटल व्योम cdv_पूर्णांकel_edp_panel_vdd_off(काष्ठा gma_encoder *पूर्णांकel_encoder)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_encoder->base.dev;
	u32 pp;

	DRM_DEBUG_KMS("\n");
	pp = REG_READ(PP_CONTROL);

	pp &= ~EDP_FORCE_VDD;
	REG_WRITE(PP_CONTROL, pp);
	REG_READ(PP_CONTROL);

पूर्ण

/* Returns true अगर the panel was alपढ़ोy on when called */
अटल bool cdv_पूर्णांकel_edp_panel_on(काष्ठा gma_encoder *पूर्णांकel_encoder)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_encoder->base.dev;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_encoder->dev_priv;
	u32 pp, idle_on_mask = PP_ON | PP_SEQUENCE_NONE;

	अगर (पूर्णांकel_dp->panel_on)
		वापस true;

	DRM_DEBUG_KMS("\n");
	pp = REG_READ(PP_CONTROL);
	pp &= ~PANEL_UNLOCK_MASK;

	pp |= (PANEL_UNLOCK_REGS | POWER_TARGET_ON);
	REG_WRITE(PP_CONTROL, pp);
	REG_READ(PP_CONTROL);

	अगर (रुको_क्रम(((REG_READ(PP_STATUS) & idle_on_mask) == idle_on_mask), 1000)) अणु
		DRM_DEBUG_KMS("Error in Powering up eDP panel, status %x\n", REG_READ(PP_STATUS));
		पूर्णांकel_dp->panel_on = false;
	पूर्ण अन्यथा
		पूर्णांकel_dp->panel_on = true;	
	msleep(पूर्णांकel_dp->panel_घातer_up_delay);

	वापस false;
पूर्ण

अटल व्योम cdv_पूर्णांकel_edp_panel_off (काष्ठा gma_encoder *पूर्णांकel_encoder)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_encoder->base.dev;
	u32 pp, idle_off_mask = PP_ON ;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_encoder->dev_priv;

	DRM_DEBUG_KMS("\n");

	pp = REG_READ(PP_CONTROL);

	अगर ((pp & POWER_TARGET_ON) == 0) 
		वापस;

	पूर्णांकel_dp->panel_on = false;
	pp &= ~PANEL_UNLOCK_MASK;
	/* ILK workaround: disable reset around घातer sequence */

	pp &= ~POWER_TARGET_ON;
	pp &= ~EDP_FORCE_VDD;
	pp &= ~EDP_BLC_ENABLE;
	REG_WRITE(PP_CONTROL, pp);
	REG_READ(PP_CONTROL);
	DRM_DEBUG_KMS("PP_STATUS %x\n", REG_READ(PP_STATUS));

	अगर (रुको_क्रम((REG_READ(PP_STATUS) & idle_off_mask) == 0, 1000)) अणु
		DRM_DEBUG_KMS("Error in turning off Panel\n");	
	पूर्ण

	msleep(पूर्णांकel_dp->panel_घातer_cycle_delay);
	DRM_DEBUG_KMS("Over\n");
पूर्ण

अटल व्योम cdv_पूर्णांकel_edp_backlight_on (काष्ठा gma_encoder *पूर्णांकel_encoder)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_encoder->base.dev;
	u32 pp;

	DRM_DEBUG_KMS("\n");
	/*
	 * If we enable the backlight right away following a panel घातer
	 * on, we may see slight flicker as the panel syncs with the eDP
	 * link.  So delay a bit to make sure the image is solid beक्रमe
	 * allowing it to appear.
	 */
	msleep(300);
	pp = REG_READ(PP_CONTROL);

	pp |= EDP_BLC_ENABLE;
	REG_WRITE(PP_CONTROL, pp);
	gma_backlight_enable(dev);
पूर्ण

अटल व्योम cdv_पूर्णांकel_edp_backlight_off (काष्ठा gma_encoder *पूर्णांकel_encoder)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_encoder->base.dev;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_encoder->dev_priv;
	u32 pp;

	DRM_DEBUG_KMS("\n");
	gma_backlight_disable(dev);
	msleep(10);
	pp = REG_READ(PP_CONTROL);

	pp &= ~EDP_BLC_ENABLE;
	REG_WRITE(PP_CONTROL, pp);
	msleep(पूर्णांकel_dp->backlight_off_delay);
पूर्ण

अटल क्रमागत drm_mode_status
cdv_पूर्णांकel_dp_mode_valid(काष्ठा drm_connector *connector,
		    काष्ठा drm_display_mode *mode)
अणु
	काष्ठा gma_encoder *encoder = gma_attached_encoder(connector);
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	पूर्णांक max_link_घड़ी = cdv_पूर्णांकel_dp_link_घड़ी(cdv_पूर्णांकel_dp_max_link_bw(encoder));
	पूर्णांक max_lanes = cdv_पूर्णांकel_dp_max_lane_count(encoder);
	काष्ठा drm_psb_निजी *dev_priv = connector->dev->dev_निजी;

	अगर (is_edp(encoder) && पूर्णांकel_dp->panel_fixed_mode) अणु
		अगर (mode->hdisplay > पूर्णांकel_dp->panel_fixed_mode->hdisplay)
			वापस MODE_PANEL;
		अगर (mode->vdisplay > पूर्णांकel_dp->panel_fixed_mode->vdisplay)
			वापस MODE_PANEL;
	पूर्ण

	/* only refuse the mode on non eDP since we have seen some weird eDP panels
	   which are outside spec tolerances but somehow work by magic */
	अगर (!is_edp(encoder) &&
	    (cdv_पूर्णांकel_dp_link_required(mode->घड़ी, dev_priv->edp.bpp)
	     > cdv_पूर्णांकel_dp_max_data_rate(max_link_घड़ी, max_lanes)))
		वापस MODE_CLOCK_HIGH;

	अगर (is_edp(encoder)) अणु
	    अगर (cdv_पूर्णांकel_dp_link_required(mode->घड़ी, 24)
	     	> cdv_पूर्णांकel_dp_max_data_rate(max_link_घड़ी, max_lanes))
		वापस MODE_CLOCK_HIGH;
		
	पूर्ण
	अगर (mode->घड़ी < 10000)
		वापस MODE_CLOCK_LOW;

	वापस MODE_OK;
पूर्ण

अटल uपूर्णांक32_t
pack_aux(uपूर्णांक8_t *src, पूर्णांक src_bytes)
अणु
	पूर्णांक	i;
	uपूर्णांक32_t v = 0;

	अगर (src_bytes > 4)
		src_bytes = 4;
	क्रम (i = 0; i < src_bytes; i++)
		v |= ((uपूर्णांक32_t) src[i]) << ((3-i) * 8);
	वापस v;
पूर्ण

अटल व्योम
unpack_aux(uपूर्णांक32_t src, uपूर्णांक8_t *dst, पूर्णांक dst_bytes)
अणु
	पूर्णांक i;
	अगर (dst_bytes > 4)
		dst_bytes = 4;
	क्रम (i = 0; i < dst_bytes; i++)
		dst[i] = src >> ((3-i) * 8);
पूर्ण

अटल पूर्णांक
cdv_पूर्णांकel_dp_aux_ch(काष्ठा gma_encoder *encoder,
		uपूर्णांक8_t *send, पूर्णांक send_bytes,
		uपूर्णांक8_t *recv, पूर्णांक recv_size)
अणु
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	uपूर्णांक32_t output_reg = पूर्णांकel_dp->output_reg;
	काष्ठा drm_device *dev = encoder->base.dev;
	uपूर्णांक32_t ch_ctl = output_reg + 0x10;
	uपूर्णांक32_t ch_data = ch_ctl + 4;
	पूर्णांक i;
	पूर्णांक recv_bytes;
	uपूर्णांक32_t status;
	uपूर्णांक32_t aux_घड़ी_भागider;
	पूर्णांक try, preअक्षरge;

	/* The घड़ी भागider is based off the hrawclk,
	 * and would like to run at 2MHz. So, take the
	 * hrawclk value and भागide by 2 and use that
	 * On CDV platक्रमm it uses 200MHz as hrawclk.
	 *
	 */
	aux_घड़ी_भागider = 200 / 2;

	preअक्षरge = 4;
	अगर (is_edp(encoder))
		preअक्षरge = 10;

	अगर (REG_READ(ch_ctl) & DP_AUX_CH_CTL_SEND_BUSY) अणु
		DRM_ERROR("dp_aux_ch not started status 0x%08x\n",
			  REG_READ(ch_ctl));
		वापस -EBUSY;
	पूर्ण

	/* Must try at least 3 बार according to DP spec */
	क्रम (try = 0; try < 5; try++) अणु
		/* Load the send data पूर्णांकo the aux channel data रेजिस्टरs */
		क्रम (i = 0; i < send_bytes; i += 4)
			REG_WRITE(ch_data + i,
				   pack_aux(send + i, send_bytes - i));
	
		/* Send the command and रुको क्रम it to complete */
		REG_WRITE(ch_ctl,
			   DP_AUX_CH_CTL_SEND_BUSY |
			   DP_AUX_CH_CTL_TIME_OUT_400us |
			   (send_bytes << DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT) |
			   (preअक्षरge << DP_AUX_CH_CTL_PRECHARGE_2US_SHIFT) |
			   (aux_घड़ी_भागider << DP_AUX_CH_CTL_BIT_CLOCK_2X_SHIFT) |
			   DP_AUX_CH_CTL_DONE |
			   DP_AUX_CH_CTL_TIME_OUT_ERROR |
			   DP_AUX_CH_CTL_RECEIVE_ERROR);
		क्रम (;;) अणु
			status = REG_READ(ch_ctl);
			अगर ((status & DP_AUX_CH_CTL_SEND_BUSY) == 0)
				अवरोध;
			udelay(100);
		पूर्ण
	
		/* Clear करोne status and any errors */
		REG_WRITE(ch_ctl,
			   status |
			   DP_AUX_CH_CTL_DONE |
			   DP_AUX_CH_CTL_TIME_OUT_ERROR |
			   DP_AUX_CH_CTL_RECEIVE_ERROR);
		अगर (status & DP_AUX_CH_CTL_DONE)
			अवरोध;
	पूर्ण

	अगर ((status & DP_AUX_CH_CTL_DONE) == 0) अणु
		DRM_ERROR("dp_aux_ch not done status 0x%08x\n", status);
		वापस -EBUSY;
	पूर्ण

	/* Check क्रम समयout or receive error.
	 * Timeouts occur when the sink is not connected
	 */
	अगर (status & DP_AUX_CH_CTL_RECEIVE_ERROR) अणु
		DRM_ERROR("dp_aux_ch receive error status 0x%08x\n", status);
		वापस -EIO;
	पूर्ण

	/* Timeouts occur when the device isn't connected, so they're
	 * "normal" -- करोn't fill the kernel log with these */
	अगर (status & DP_AUX_CH_CTL_TIME_OUT_ERROR) अणु
		DRM_DEBUG_KMS("dp_aux_ch timeout status 0x%08x\n", status);
		वापस -ETIMEDOUT;
	पूर्ण

	/* Unload any bytes sent back from the other side */
	recv_bytes = ((status & DP_AUX_CH_CTL_MESSAGE_SIZE_MASK) >>
		      DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT);
	अगर (recv_bytes > recv_size)
		recv_bytes = recv_size;
	
	क्रम (i = 0; i < recv_bytes; i += 4)
		unpack_aux(REG_READ(ch_data + i),
			   recv + i, recv_bytes - i);

	वापस recv_bytes;
पूर्ण

/* Write data to the aux channel in native mode */
अटल पूर्णांक
cdv_पूर्णांकel_dp_aux_native_ग_लिखो(काष्ठा gma_encoder *encoder,
			  uपूर्णांक16_t address, uपूर्णांक8_t *send, पूर्णांक send_bytes)
अणु
	पूर्णांक ret;
	uपूर्णांक8_t	msg[20];
	पूर्णांक msg_bytes;
	uपूर्णांक8_t	ack;

	अगर (send_bytes > 16)
		वापस -1;
	msg[0] = DP_AUX_NATIVE_WRITE << 4;
	msg[1] = address >> 8;
	msg[2] = address & 0xff;
	msg[3] = send_bytes - 1;
	स_नकल(&msg[4], send, send_bytes);
	msg_bytes = send_bytes + 4;
	क्रम (;;) अणु
		ret = cdv_पूर्णांकel_dp_aux_ch(encoder, msg, msg_bytes, &ack, 1);
		अगर (ret < 0)
			वापस ret;
		ack >>= 4;
		अगर ((ack & DP_AUX_NATIVE_REPLY_MASK) == DP_AUX_NATIVE_REPLY_ACK)
			अवरोध;
		अन्यथा अगर ((ack & DP_AUX_NATIVE_REPLY_MASK) == DP_AUX_NATIVE_REPLY_DEFER)
			udelay(100);
		अन्यथा
			वापस -EIO;
	पूर्ण
	वापस send_bytes;
पूर्ण

/* Write a single byte to the aux channel in native mode */
अटल पूर्णांक
cdv_पूर्णांकel_dp_aux_native_ग_लिखो_1(काष्ठा gma_encoder *encoder,
			    uपूर्णांक16_t address, uपूर्णांक8_t byte)
अणु
	वापस cdv_पूर्णांकel_dp_aux_native_ग_लिखो(encoder, address, &byte, 1);
पूर्ण

/* पढ़ो bytes from a native aux channel */
अटल पूर्णांक
cdv_पूर्णांकel_dp_aux_native_पढ़ो(काष्ठा gma_encoder *encoder,
			 uपूर्णांक16_t address, uपूर्णांक8_t *recv, पूर्णांक recv_bytes)
अणु
	uपूर्णांक8_t msg[4];
	पूर्णांक msg_bytes;
	uपूर्णांक8_t reply[20];
	पूर्णांक reply_bytes;
	uपूर्णांक8_t ack;
	पूर्णांक ret;

	msg[0] = DP_AUX_NATIVE_READ << 4;
	msg[1] = address >> 8;
	msg[2] = address & 0xff;
	msg[3] = recv_bytes - 1;

	msg_bytes = 4;
	reply_bytes = recv_bytes + 1;

	क्रम (;;) अणु
		ret = cdv_पूर्णांकel_dp_aux_ch(encoder, msg, msg_bytes,
				      reply, reply_bytes);
		अगर (ret == 0)
			वापस -EPROTO;
		अगर (ret < 0)
			वापस ret;
		ack = reply[0] >> 4;
		अगर ((ack & DP_AUX_NATIVE_REPLY_MASK) == DP_AUX_NATIVE_REPLY_ACK) अणु
			स_नकल(recv, reply + 1, ret - 1);
			वापस ret - 1;
		पूर्ण
		अन्यथा अगर ((ack & DP_AUX_NATIVE_REPLY_MASK) == DP_AUX_NATIVE_REPLY_DEFER)
			udelay(100);
		अन्यथा
			वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक
cdv_पूर्णांकel_dp_i2c_aux_ch(काष्ठा i2c_adapter *adapter, पूर्णांक mode,
		    uपूर्णांक8_t ग_लिखो_byte, uपूर्णांक8_t *पढ़ो_byte)
अणु
	काष्ठा i2c_algo_dp_aux_data *algo_data = adapter->algo_data;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = container_of(adapter,
						काष्ठा cdv_पूर्णांकel_dp,
						adapter);
	काष्ठा gma_encoder *encoder = पूर्णांकel_dp->encoder;
	uपूर्णांक16_t address = algo_data->address;
	uपूर्णांक8_t msg[5];
	uपूर्णांक8_t reply[2];
	अचिन्हित retry;
	पूर्णांक msg_bytes;
	पूर्णांक reply_bytes;
	पूर्णांक ret;

	/* Set up the command byte */
	अगर (mode & MODE_I2C_READ)
		msg[0] = DP_AUX_I2C_READ << 4;
	अन्यथा
		msg[0] = DP_AUX_I2C_WRITE << 4;

	अगर (!(mode & MODE_I2C_STOP))
		msg[0] |= DP_AUX_I2C_MOT << 4;

	msg[1] = address >> 8;
	msg[2] = address;

	चयन (mode) अणु
	हाल MODE_I2C_WRITE:
		msg[3] = 0;
		msg[4] = ग_लिखो_byte;
		msg_bytes = 5;
		reply_bytes = 1;
		अवरोध;
	हाल MODE_I2C_READ:
		msg[3] = 0;
		msg_bytes = 4;
		reply_bytes = 2;
		अवरोध;
	शेष:
		msg_bytes = 3;
		reply_bytes = 1;
		अवरोध;
	पूर्ण

	क्रम (retry = 0; retry < 5; retry++) अणु
		ret = cdv_पूर्णांकel_dp_aux_ch(encoder,
				      msg, msg_bytes,
				      reply, reply_bytes);
		अगर (ret < 0) अणु
			DRM_DEBUG_KMS("aux_ch failed %d\n", ret);
			वापस ret;
		पूर्ण

		चयन ((reply[0] >> 4) & DP_AUX_NATIVE_REPLY_MASK) अणु
		हाल DP_AUX_NATIVE_REPLY_ACK:
			/* I2C-over-AUX Reply field is only valid
			 * when paired with AUX ACK.
			 */
			अवरोध;
		हाल DP_AUX_NATIVE_REPLY_NACK:
			DRM_DEBUG_KMS("aux_ch native nack\n");
			वापस -EREMOTEIO;
		हाल DP_AUX_NATIVE_REPLY_DEFER:
			udelay(100);
			जारी;
		शेष:
			DRM_ERROR("aux_ch invalid native reply 0x%02x\n",
				  reply[0]);
			वापस -EREMOTEIO;
		पूर्ण

		चयन ((reply[0] >> 4) & DP_AUX_I2C_REPLY_MASK) अणु
		हाल DP_AUX_I2C_REPLY_ACK:
			अगर (mode == MODE_I2C_READ) अणु
				*पढ़ो_byte = reply[1];
			पूर्ण
			वापस reply_bytes - 1;
		हाल DP_AUX_I2C_REPLY_NACK:
			DRM_DEBUG_KMS("aux_i2c nack\n");
			वापस -EREMOTEIO;
		हाल DP_AUX_I2C_REPLY_DEFER:
			DRM_DEBUG_KMS("aux_i2c defer\n");
			udelay(100);
			अवरोध;
		शेष:
			DRM_ERROR("aux_i2c invalid reply 0x%02x\n", reply[0]);
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण

	DRM_ERROR("too many retries, giving up\n");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक
cdv_पूर्णांकel_dp_i2c_init(काष्ठा gma_connector *connector,
		      काष्ठा gma_encoder *encoder, स्थिर अक्षर *name)
अणु
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	पूर्णांक ret;

	DRM_DEBUG_KMS("i2c_init %s\n", name);

	पूर्णांकel_dp->algo.running = false;
	पूर्णांकel_dp->algo.address = 0;
	पूर्णांकel_dp->algo.aux_ch = cdv_पूर्णांकel_dp_i2c_aux_ch;

	स_रखो(&पूर्णांकel_dp->adapter, '\0', माप (पूर्णांकel_dp->adapter));
	पूर्णांकel_dp->adapter.owner = THIS_MODULE;
	पूर्णांकel_dp->adapter.class = I2C_CLASS_DDC;
	म_नकलन (पूर्णांकel_dp->adapter.name, name, माप(पूर्णांकel_dp->adapter.name) - 1);
	पूर्णांकel_dp->adapter.name[माप(पूर्णांकel_dp->adapter.name) - 1] = '\0';
	पूर्णांकel_dp->adapter.algo_data = &पूर्णांकel_dp->algo;
	पूर्णांकel_dp->adapter.dev.parent = connector->base.kdev;

	अगर (is_edp(encoder))
		cdv_पूर्णांकel_edp_panel_vdd_on(encoder);
	ret = i2c_dp_aux_add_bus(&पूर्णांकel_dp->adapter);
	अगर (is_edp(encoder))
		cdv_पूर्णांकel_edp_panel_vdd_off(encoder);
	
	वापस ret;
पूर्ण

अटल व्योम cdv_पूर्णांकel_fixed_panel_mode(काष्ठा drm_display_mode *fixed_mode,
	काष्ठा drm_display_mode *adjusted_mode)
अणु
	adjusted_mode->hdisplay = fixed_mode->hdisplay;
	adjusted_mode->hsync_start = fixed_mode->hsync_start;
	adjusted_mode->hsync_end = fixed_mode->hsync_end;
	adjusted_mode->htotal = fixed_mode->htotal;

	adjusted_mode->vdisplay = fixed_mode->vdisplay;
	adjusted_mode->vsync_start = fixed_mode->vsync_start;
	adjusted_mode->vsync_end = fixed_mode->vsync_end;
	adjusted_mode->vtotal = fixed_mode->vtotal;

	adjusted_mode->घड़ी = fixed_mode->घड़ी;

	drm_mode_set_crtcinfo(adjusted_mode, CRTC_INTERLACE_HALVE_V);
पूर्ण

अटल bool
cdv_पूर्णांकel_dp_mode_fixup(काष्ठा drm_encoder *encoder, स्थिर काष्ठा drm_display_mode *mode,
		    काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_psb_निजी *dev_priv = encoder->dev->dev_निजी;
	काष्ठा gma_encoder *पूर्णांकel_encoder = to_gma_encoder(encoder);
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_encoder->dev_priv;
	पूर्णांक lane_count, घड़ी;
	पूर्णांक max_lane_count = cdv_पूर्णांकel_dp_max_lane_count(पूर्णांकel_encoder);
	पूर्णांक max_घड़ी = cdv_पूर्णांकel_dp_max_link_bw(पूर्णांकel_encoder) == DP_LINK_BW_2_7 ? 1 : 0;
	अटल पूर्णांक bws[2] = अणु DP_LINK_BW_1_62, DP_LINK_BW_2_7 पूर्ण;
	पूर्णांक refघड़ी = mode->घड़ी;
	पूर्णांक bpp = 24;

	अगर (is_edp(पूर्णांकel_encoder) && पूर्णांकel_dp->panel_fixed_mode) अणु
		cdv_पूर्णांकel_fixed_panel_mode(पूर्णांकel_dp->panel_fixed_mode, adjusted_mode);
		refघड़ी = पूर्णांकel_dp->panel_fixed_mode->घड़ी;
		bpp = dev_priv->edp.bpp;
	पूर्ण

	क्रम (lane_count = 1; lane_count <= max_lane_count; lane_count <<= 1) अणु
		क्रम (घड़ी = max_घड़ी; घड़ी >= 0; घड़ी--) अणु
			पूर्णांक link_avail = cdv_पूर्णांकel_dp_max_data_rate(cdv_पूर्णांकel_dp_link_घड़ी(bws[घड़ी]), lane_count);

			अगर (cdv_पूर्णांकel_dp_link_required(refघड़ी, bpp) <= link_avail) अणु
				पूर्णांकel_dp->link_bw = bws[घड़ी];
				पूर्णांकel_dp->lane_count = lane_count;
				adjusted_mode->घड़ी = cdv_पूर्णांकel_dp_link_घड़ी(पूर्णांकel_dp->link_bw);
				DRM_DEBUG_KMS("Display port link bw %02x lane "
						"count %d clock %d\n",
				       पूर्णांकel_dp->link_bw, पूर्णांकel_dp->lane_count,
				       adjusted_mode->घड़ी);
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (is_edp(पूर्णांकel_encoder)) अणु
		/* okay we failed just pick the highest */
		पूर्णांकel_dp->lane_count = max_lane_count;
		पूर्णांकel_dp->link_bw = bws[max_घड़ी];
		adjusted_mode->घड़ी = cdv_पूर्णांकel_dp_link_घड़ी(पूर्णांकel_dp->link_bw);
		DRM_DEBUG_KMS("Force picking display port link bw %02x lane "
			      "count %d clock %d\n",
			      पूर्णांकel_dp->link_bw, पूर्णांकel_dp->lane_count,
			      adjusted_mode->घड़ी);

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

काष्ठा cdv_पूर्णांकel_dp_m_n अणु
	uपूर्णांक32_t	tu;
	uपूर्णांक32_t	gmch_m;
	uपूर्णांक32_t	gmch_n;
	uपूर्णांक32_t	link_m;
	uपूर्णांक32_t	link_n;
पूर्ण;

अटल व्योम
cdv_पूर्णांकel_reduce_ratio(uपूर्णांक32_t *num, uपूर्णांक32_t *den)
अणु
	/*
	जबतक (*num > 0xffffff || *den > 0xffffff) अणु
		*num >>= 1;
		*den >>= 1;
	पूर्ण*/
	uपूर्णांक64_t value, m;
	m = *num;
	value = m * (0x800000);
	m = करो_भाग(value, *den);
	*num = value;
	*den = 0x800000;
पूर्ण

अटल व्योम
cdv_पूर्णांकel_dp_compute_m_n(पूर्णांक bpp,
		     पूर्णांक nlanes,
		     पूर्णांक pixel_घड़ी,
		     पूर्णांक link_घड़ी,
		     काष्ठा cdv_पूर्णांकel_dp_m_n *m_n)
अणु
	m_n->tu = 64;
	m_n->gmch_m = (pixel_घड़ी * bpp + 7) >> 3;
	m_n->gmch_n = link_घड़ी * nlanes;
	cdv_पूर्णांकel_reduce_ratio(&m_n->gmch_m, &m_n->gmch_n);
	m_n->link_m = pixel_घड़ी;
	m_n->link_n = link_घड़ी;
	cdv_पूर्णांकel_reduce_ratio(&m_n->link_m, &m_n->link_n);
पूर्ण

व्योम
cdv_पूर्णांकel_dp_set_m_n(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode,
		 काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	काष्ठा drm_encoder *encoder;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	पूर्णांक lane_count = 4, bpp = 24;
	काष्ठा cdv_पूर्णांकel_dp_m_n m_n;
	पूर्णांक pipe = gma_crtc->pipe;

	/*
	 * Find the lane count in the पूर्णांकel_encoder निजी
	 */
	list_क्रम_each_entry(encoder, &mode_config->encoder_list, head) अणु
		काष्ठा gma_encoder *पूर्णांकel_encoder;
		काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp;

		अगर (encoder->crtc != crtc)
			जारी;

		पूर्णांकel_encoder = to_gma_encoder(encoder);
		पूर्णांकel_dp = पूर्णांकel_encoder->dev_priv;
		अगर (पूर्णांकel_encoder->type == INTEL_OUTPUT_DISPLAYPORT) अणु
			lane_count = पूर्णांकel_dp->lane_count;
			अवरोध;
		पूर्ण अन्यथा अगर (is_edp(पूर्णांकel_encoder)) अणु
			lane_count = पूर्णांकel_dp->lane_count;
			bpp = dev_priv->edp.bpp;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Compute the GMCH and Link ratios. The '3' here is
	 * the number of bytes_per_pixel post-LUT, which we always
	 * set up क्रम 8-bits of R/G/B, or 3 bytes total.
	 */
	cdv_पूर्णांकel_dp_compute_m_n(bpp, lane_count,
			     mode->घड़ी, adjusted_mode->घड़ी, &m_n);

	अणु
		REG_WRITE(PIPE_GMCH_DATA_M(pipe),
			   ((m_n.tu - 1) << PIPE_GMCH_DATA_M_TU_SIZE_SHIFT) |
			   m_n.gmch_m);
		REG_WRITE(PIPE_GMCH_DATA_N(pipe), m_n.gmch_n);
		REG_WRITE(PIPE_DP_LINK_M(pipe), m_n.link_m);
		REG_WRITE(PIPE_DP_LINK_N(pipe), m_n.link_n);
	पूर्ण
पूर्ण

अटल व्योम
cdv_पूर्णांकel_dp_mode_set(काष्ठा drm_encoder *encoder, काष्ठा drm_display_mode *mode,
		  काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा gma_encoder *पूर्णांकel_encoder = to_gma_encoder(encoder);
	काष्ठा drm_crtc *crtc = encoder->crtc;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_encoder->dev_priv;
	काष्ठा drm_device *dev = encoder->dev;

	पूर्णांकel_dp->DP = DP_VOLTAGE_0_4 | DP_PRE_EMPHASIS_0;
	पूर्णांकel_dp->DP |= पूर्णांकel_dp->color_range;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		पूर्णांकel_dp->DP |= DP_SYNC_HS_HIGH;
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		पूर्णांकel_dp->DP |= DP_SYNC_VS_HIGH;

	पूर्णांकel_dp->DP |= DP_LINK_TRAIN_OFF;

	चयन (पूर्णांकel_dp->lane_count) अणु
	हाल 1:
		पूर्णांकel_dp->DP |= DP_PORT_WIDTH_1;
		अवरोध;
	हाल 2:
		पूर्णांकel_dp->DP |= DP_PORT_WIDTH_2;
		अवरोध;
	हाल 4:
		पूर्णांकel_dp->DP |= DP_PORT_WIDTH_4;
		अवरोध;
	पूर्ण
	अगर (पूर्णांकel_dp->has_audio)
		पूर्णांकel_dp->DP |= DP_AUDIO_OUTPUT_ENABLE;

	स_रखो(पूर्णांकel_dp->link_configuration, 0, DP_LINK_CONFIGURATION_SIZE);
	पूर्णांकel_dp->link_configuration[0] = पूर्णांकel_dp->link_bw;
	पूर्णांकel_dp->link_configuration[1] = पूर्णांकel_dp->lane_count;

	/*
	 * Check क्रम DPCD version > 1.1 and enhanced framing support
	 */
	अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] >= 0x11 &&
	    (पूर्णांकel_dp->dpcd[DP_MAX_LANE_COUNT] & DP_ENHANCED_FRAME_CAP)) अणु
		पूर्णांकel_dp->link_configuration[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;
		पूर्णांकel_dp->DP |= DP_ENHANCED_FRAMING;
	पूर्ण

	/* CPT DP's pipe select is decided in TRANS_DP_CTL */
	अगर (gma_crtc->pipe == 1)
		पूर्णांकel_dp->DP |= DP_PIPEB_SELECT;

	REG_WRITE(पूर्णांकel_dp->output_reg, (पूर्णांकel_dp->DP | DP_PORT_EN));
	DRM_DEBUG_KMS("DP expected reg is %x\n", पूर्णांकel_dp->DP);
	अगर (is_edp(पूर्णांकel_encoder)) अणु
		uपूर्णांक32_t pfit_control;
		cdv_पूर्णांकel_edp_panel_on(पूर्णांकel_encoder);

		अगर (mode->hdisplay != adjusted_mode->hdisplay ||
			    mode->vdisplay != adjusted_mode->vdisplay)
			pfit_control = PFIT_ENABLE;
		अन्यथा
			pfit_control = 0;

		pfit_control |= gma_crtc->pipe << PFIT_PIPE_SHIFT;

		REG_WRITE(PFIT_CONTROL, pfit_control);
	पूर्ण
पूर्ण


/* If the sink supports it, try to set the घातer state appropriately */
अटल व्योम cdv_पूर्णांकel_dp_sink_dpms(काष्ठा gma_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	पूर्णांक ret, i;

	/* Should have a valid DPCD by this poपूर्णांक */
	अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] < 0x11)
		वापस;

	अगर (mode != DRM_MODE_DPMS_ON) अणु
		ret = cdv_पूर्णांकel_dp_aux_native_ग_लिखो_1(encoder, DP_SET_POWER,
						  DP_SET_POWER_D3);
		अगर (ret != 1)
			DRM_DEBUG_DRIVER("failed to write sink power state\n");
	पूर्ण अन्यथा अणु
		/*
		 * When turning on, we need to retry क्रम 1ms to give the sink
		 * समय to wake up.
		 */
		क्रम (i = 0; i < 3; i++) अणु
			ret = cdv_पूर्णांकel_dp_aux_native_ग_लिखो_1(encoder,
							  DP_SET_POWER,
							  DP_SET_POWER_D0);
			अगर (ret == 1)
				अवरोध;
			udelay(1000);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cdv_पूर्णांकel_dp_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा gma_encoder *पूर्णांकel_encoder = to_gma_encoder(encoder);
	पूर्णांक edp = is_edp(पूर्णांकel_encoder);

	अगर (edp) अणु
		cdv_पूर्णांकel_edp_backlight_off(पूर्णांकel_encoder);
		cdv_पूर्णांकel_edp_panel_off(पूर्णांकel_encoder);
		cdv_पूर्णांकel_edp_panel_vdd_on(पूर्णांकel_encoder);
        पूर्ण
	/* Wake up the sink first */
	cdv_पूर्णांकel_dp_sink_dpms(पूर्णांकel_encoder, DRM_MODE_DPMS_ON);
	cdv_पूर्णांकel_dp_link_करोwn(पूर्णांकel_encoder);
	अगर (edp)
		cdv_पूर्णांकel_edp_panel_vdd_off(पूर्णांकel_encoder);
पूर्ण

अटल व्योम cdv_पूर्णांकel_dp_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा gma_encoder *पूर्णांकel_encoder = to_gma_encoder(encoder);
	पूर्णांक edp = is_edp(पूर्णांकel_encoder);

	अगर (edp)
		cdv_पूर्णांकel_edp_panel_on(पूर्णांकel_encoder);
	cdv_पूर्णांकel_dp_start_link_train(पूर्णांकel_encoder);
	cdv_पूर्णांकel_dp_complete_link_train(पूर्णांकel_encoder);
	अगर (edp)
		cdv_पूर्णांकel_edp_backlight_on(पूर्णांकel_encoder);
पूर्ण

अटल व्योम
cdv_पूर्णांकel_dp_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा gma_encoder *पूर्णांकel_encoder = to_gma_encoder(encoder);
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_encoder->dev_priv;
	काष्ठा drm_device *dev = encoder->dev;
	uपूर्णांक32_t dp_reg = REG_READ(पूर्णांकel_dp->output_reg);
	पूर्णांक edp = is_edp(पूर्णांकel_encoder);

	अगर (mode != DRM_MODE_DPMS_ON) अणु
		अगर (edp) अणु
			cdv_पूर्णांकel_edp_backlight_off(पूर्णांकel_encoder);
			cdv_पूर्णांकel_edp_panel_vdd_on(पूर्णांकel_encoder);
		पूर्ण
		cdv_पूर्णांकel_dp_sink_dpms(पूर्णांकel_encoder, mode);
		cdv_पूर्णांकel_dp_link_करोwn(पूर्णांकel_encoder);
		अगर (edp) अणु
			cdv_पूर्णांकel_edp_panel_vdd_off(पूर्णांकel_encoder);
			cdv_पूर्णांकel_edp_panel_off(पूर्णांकel_encoder);
		पूर्ण
	पूर्ण अन्यथा अणु
        	अगर (edp)
			cdv_पूर्णांकel_edp_panel_on(पूर्णांकel_encoder);
		cdv_पूर्णांकel_dp_sink_dpms(पूर्णांकel_encoder, mode);
		अगर (!(dp_reg & DP_PORT_EN)) अणु
			cdv_पूर्णांकel_dp_start_link_train(पूर्णांकel_encoder);
			cdv_पूर्णांकel_dp_complete_link_train(पूर्णांकel_encoder);
		पूर्ण
		अगर (edp)
        		cdv_पूर्णांकel_edp_backlight_on(पूर्णांकel_encoder);
	पूर्ण
पूर्ण

/*
 * Native पढ़ो with retry क्रम link status and receiver capability पढ़ोs क्रम
 * हालs where the sink may still be asleep.
 */
अटल bool
cdv_पूर्णांकel_dp_aux_native_पढ़ो_retry(काष्ठा gma_encoder *encoder, uपूर्णांक16_t address,
			       uपूर्णांक8_t *recv, पूर्णांक recv_bytes)
अणु
	पूर्णांक ret, i;

	/*
	 * Sinks are *supposed* to come up within 1ms from an off state,
	 * but we're also supposed to retry 3 बार per the spec.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		ret = cdv_पूर्णांकel_dp_aux_native_पढ़ो(encoder, address, recv,
					       recv_bytes);
		अगर (ret == recv_bytes)
			वापस true;
		udelay(1000);
	पूर्ण

	वापस false;
पूर्ण

/*
 * Fetch AUX CH रेजिस्टरs 0x202 - 0x207 which contain
 * link status inक्रमmation
 */
अटल bool
cdv_पूर्णांकel_dp_get_link_status(काष्ठा gma_encoder *encoder)
अणु
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	वापस cdv_पूर्णांकel_dp_aux_native_पढ़ो_retry(encoder,
					      DP_LANE0_1_STATUS,
					      पूर्णांकel_dp->link_status,
					      DP_LINK_STATUS_SIZE);
पूर्ण

अटल uपूर्णांक8_t
cdv_पूर्णांकel_dp_link_status(uपूर्णांक8_t link_status[DP_LINK_STATUS_SIZE],
		     पूर्णांक r)
अणु
	वापस link_status[r - DP_LANE0_1_STATUS];
पूर्ण

अटल uपूर्णांक8_t
cdv_पूर्णांकel_get_adjust_request_voltage(uपूर्णांक8_t link_status[DP_LINK_STATUS_SIZE],
				 पूर्णांक lane)
अणु
	पूर्णांक	    i = DP_ADJUST_REQUEST_LANE0_1 + (lane >> 1);
	पूर्णांक	    s = ((lane & 1) ?
			 DP_ADJUST_VOLTAGE_SWING_LANE1_SHIFT :
			 DP_ADJUST_VOLTAGE_SWING_LANE0_SHIFT);
	uपूर्णांक8_t l = cdv_पूर्णांकel_dp_link_status(link_status, i);

	वापस ((l >> s) & 3) << DP_TRAIN_VOLTAGE_SWING_SHIFT;
पूर्ण

अटल uपूर्णांक8_t
cdv_पूर्णांकel_get_adjust_request_pre_emphasis(uपूर्णांक8_t link_status[DP_LINK_STATUS_SIZE],
				      पूर्णांक lane)
अणु
	पूर्णांक	    i = DP_ADJUST_REQUEST_LANE0_1 + (lane >> 1);
	पूर्णांक	    s = ((lane & 1) ?
			 DP_ADJUST_PRE_EMPHASIS_LANE1_SHIFT :
			 DP_ADJUST_PRE_EMPHASIS_LANE0_SHIFT);
	uपूर्णांक8_t l = cdv_पूर्णांकel_dp_link_status(link_status, i);

	वापस ((l >> s) & 3) << DP_TRAIN_PRE_EMPHASIS_SHIFT;
पूर्ण

#घोषणा CDV_DP_VOLTAGE_MAX	    DP_TRAIN_VOLTAGE_SWING_LEVEL_3

अटल व्योम
cdv_पूर्णांकel_get_adjust_train(काष्ठा gma_encoder *encoder)
अणु
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	uपूर्णांक8_t v = 0;
	uपूर्णांक8_t p = 0;
	पूर्णांक lane;

	क्रम (lane = 0; lane < पूर्णांकel_dp->lane_count; lane++) अणु
		uपूर्णांक8_t this_v = cdv_पूर्णांकel_get_adjust_request_voltage(पूर्णांकel_dp->link_status, lane);
		uपूर्णांक8_t this_p = cdv_पूर्णांकel_get_adjust_request_pre_emphasis(पूर्णांकel_dp->link_status, lane);

		अगर (this_v > v)
			v = this_v;
		अगर (this_p > p)
			p = this_p;
	पूर्ण
	
	अगर (v >= CDV_DP_VOLTAGE_MAX)
		v = CDV_DP_VOLTAGE_MAX | DP_TRAIN_MAX_SWING_REACHED;

	अगर (p == DP_TRAIN_PRE_EMPHASIS_MASK)
		p |= DP_TRAIN_MAX_PRE_EMPHASIS_REACHED;
		
	क्रम (lane = 0; lane < 4; lane++)
		पूर्णांकel_dp->train_set[lane] = v | p;
पूर्ण


अटल uपूर्णांक8_t
cdv_पूर्णांकel_get_lane_status(uपूर्णांक8_t link_status[DP_LINK_STATUS_SIZE],
		      पूर्णांक lane)
अणु
	पूर्णांक i = DP_LANE0_1_STATUS + (lane >> 1);
	पूर्णांक s = (lane & 1) * 4;
	uपूर्णांक8_t l = cdv_पूर्णांकel_dp_link_status(link_status, i);

	वापस (l >> s) & 0xf;
पूर्ण

/* Check क्रम घड़ी recovery is करोne on all channels */
अटल bool
cdv_पूर्णांकel_घड़ी_recovery_ok(uपूर्णांक8_t link_status[DP_LINK_STATUS_SIZE], पूर्णांक lane_count)
अणु
	पूर्णांक lane;
	uपूर्णांक8_t lane_status;

	क्रम (lane = 0; lane < lane_count; lane++) अणु
		lane_status = cdv_पूर्णांकel_get_lane_status(link_status, lane);
		अगर ((lane_status & DP_LANE_CR_DONE) == 0)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* Check to see अगर channel eq is करोne on all channels */
#घोषणा CHANNEL_EQ_BITS (DP_LANE_CR_DONE|\
			 DP_LANE_CHANNEL_EQ_DONE|\
			 DP_LANE_SYMBOL_LOCKED)
अटल bool
cdv_पूर्णांकel_channel_eq_ok(काष्ठा gma_encoder *encoder)
अणु
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	uपूर्णांक8_t lane_align;
	uपूर्णांक8_t lane_status;
	पूर्णांक lane;

	lane_align = cdv_पूर्णांकel_dp_link_status(पूर्णांकel_dp->link_status,
					  DP_LANE_ALIGN_STATUS_UPDATED);
	अगर ((lane_align & DP_INTERLANE_ALIGN_DONE) == 0)
		वापस false;
	क्रम (lane = 0; lane < पूर्णांकel_dp->lane_count; lane++) अणु
		lane_status = cdv_पूर्णांकel_get_lane_status(पूर्णांकel_dp->link_status, lane);
		अगर ((lane_status & CHANNEL_EQ_BITS) != CHANNEL_EQ_BITS)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool
cdv_पूर्णांकel_dp_set_link_train(काष्ठा gma_encoder *encoder,
			uपूर्णांक32_t dp_reg_value,
			uपूर्णांक8_t dp_train_pat)
अणु
	
	काष्ठा drm_device *dev = encoder->base.dev;
	पूर्णांक ret;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;

	REG_WRITE(पूर्णांकel_dp->output_reg, dp_reg_value);
	REG_READ(पूर्णांकel_dp->output_reg);

	ret = cdv_पूर्णांकel_dp_aux_native_ग_लिखो_1(encoder,
				    DP_TRAINING_PATTERN_SET,
				    dp_train_pat);

	अगर (ret != 1) अणु
		DRM_DEBUG_KMS("Failure in setting link pattern %x\n",
				dp_train_pat);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण


अटल bool
cdv_पूर्णांकel_dplink_set_level(काष्ठा gma_encoder *encoder,
			uपूर्णांक8_t dp_train_pat)
अणु
	
	पूर्णांक ret;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;

	ret = cdv_पूर्णांकel_dp_aux_native_ग_लिखो(encoder,
					DP_TRAINING_LANE0_SET,
					पूर्णांकel_dp->train_set,
					पूर्णांकel_dp->lane_count);

	अगर (ret != पूर्णांकel_dp->lane_count) अणु
		DRM_DEBUG_KMS("Failure in setting level %d, lane_cnt= %d\n",
				पूर्णांकel_dp->train_set[0], पूर्णांकel_dp->lane_count);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम
cdv_पूर्णांकel_dp_set_vswing_premph(काष्ठा gma_encoder *encoder, uपूर्णांक8_t संकेत_level)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	काष्ठा ddi_regoff *ddi_reg;
	पूर्णांक vswing, premph, index;

	अगर (पूर्णांकel_dp->output_reg == DP_B)
		ddi_reg = &ddi_DP_train_table[0];
	अन्यथा
		ddi_reg = &ddi_DP_train_table[1];

	vswing = (संकेत_level & DP_TRAIN_VOLTAGE_SWING_MASK);
	premph = ((संकेत_level & DP_TRAIN_PRE_EMPHASIS_MASK)) >>
				DP_TRAIN_PRE_EMPHASIS_SHIFT;

	अगर (vswing + premph > 3)
		वापस;
#अगर_घोषित CDV_FAST_LINK_TRAIN
	वापस;
#पूर्ण_अगर
	DRM_DEBUG_KMS("Test2\n");
	//वापस ;
	cdv_sb_reset(dev);
	/* ;Swing voltage programming
        ;gfx_dpio_set_reg(0xc058, 0x0505313A) */
	cdv_sb_ग_लिखो(dev, ddi_reg->VSwing5, 0x0505313A);

	/* ;gfx_dpio_set_reg(0x8154, 0x43406055) */
	cdv_sb_ग_लिखो(dev, ddi_reg->VSwing1, 0x43406055);

	/* ;gfx_dpio_set_reg(0x8148, 0x55338954)
	 * The VSwing_PreEmph table is also considered based on the vswing/premp
	 */
	index = (vswing + premph) * 2;
	अगर (premph == 1 && vswing == 1) अणु
		cdv_sb_ग_लिखो(dev, ddi_reg->VSwing2, 0x055738954);
	पूर्ण अन्यथा
		cdv_sb_ग_लिखो(dev, ddi_reg->VSwing2, dp_vswing_premph_table[index]);

	/* ;gfx_dpio_set_reg(0x814c, 0x40802040) */
	अगर ((vswing + premph) == DP_TRAIN_VOLTAGE_SWING_LEVEL_3)
		cdv_sb_ग_लिखो(dev, ddi_reg->VSwing3, 0x70802040);
	अन्यथा
		cdv_sb_ग_लिखो(dev, ddi_reg->VSwing3, 0x40802040);

	/* ;gfx_dpio_set_reg(0x8150, 0x2b405555) */
	/* cdv_sb_ग_लिखो(dev, ddi_reg->VSwing4, 0x2b405555); */

	/* ;gfx_dpio_set_reg(0x8154, 0xc3406055) */
	cdv_sb_ग_लिखो(dev, ddi_reg->VSwing1, 0xc3406055);

	/* ;Pre emphasis programming
	 * ;gfx_dpio_set_reg(0xc02c, 0x1f030040)
	 */
	cdv_sb_ग_लिखो(dev, ddi_reg->PreEmph1, 0x1f030040);

	/* ;gfx_dpio_set_reg(0x8124, 0x00004000) */
	index = 2 * premph + 1;
	cdv_sb_ग_लिखो(dev, ddi_reg->PreEmph2, dp_vswing_premph_table[index]);
	वापस;	
पूर्ण


/* Enable corresponding port and start training pattern 1 */
अटल व्योम
cdv_पूर्णांकel_dp_start_link_train(काष्ठा gma_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	पूर्णांक i;
	uपूर्णांक8_t voltage;
	bool घड़ी_recovery = false;
	पूर्णांक tries;
	u32 reg;
	uपूर्णांक32_t DP = पूर्णांकel_dp->DP;

	DP |= DP_PORT_EN;
	DP &= ~DP_LINK_TRAIN_MASK;
		
	reg = DP;	
	reg |= DP_LINK_TRAIN_PAT_1;
	/* Enable output, रुको क्रम it to become active */
	REG_WRITE(पूर्णांकel_dp->output_reg, reg);
	REG_READ(पूर्णांकel_dp->output_reg);
	gma_रुको_क्रम_vblank(dev);

	DRM_DEBUG_KMS("Link config\n");
	/* Write the link configuration data */
	cdv_पूर्णांकel_dp_aux_native_ग_लिखो(encoder, DP_LINK_BW_SET,
				  पूर्णांकel_dp->link_configuration,
				  2);

	स_रखो(पूर्णांकel_dp->train_set, 0, 4);
	voltage = 0;
	tries = 0;
	घड़ी_recovery = false;

	DRM_DEBUG_KMS("Start train\n");
	reg = DP | DP_LINK_TRAIN_PAT_1;

	क्रम (;;) अणु
		/* Use पूर्णांकel_dp->train_set[0] to set the voltage and pre emphasis values */
		DRM_DEBUG_KMS("DP Link Train Set %x, Link_config %x, %x\n",
				पूर्णांकel_dp->train_set[0],
				पूर्णांकel_dp->link_configuration[0],
				पूर्णांकel_dp->link_configuration[1]);

		अगर (!cdv_पूर्णांकel_dp_set_link_train(encoder, reg, DP_TRAINING_PATTERN_1)) अणु
			DRM_DEBUG_KMS("Failure in aux-transfer setting pattern 1\n");
		पूर्ण
		cdv_पूर्णांकel_dp_set_vswing_premph(encoder, पूर्णांकel_dp->train_set[0]);
		/* Set training pattern 1 */

		cdv_पूर्णांकel_dplink_set_level(encoder, DP_TRAINING_PATTERN_1);

		udelay(200);
		अगर (!cdv_पूर्णांकel_dp_get_link_status(encoder))
			अवरोध;

		DRM_DEBUG_KMS("DP Link status %x, %x, %x, %x, %x, %x\n",
				पूर्णांकel_dp->link_status[0], पूर्णांकel_dp->link_status[1], पूर्णांकel_dp->link_status[2],
				पूर्णांकel_dp->link_status[3], पूर्णांकel_dp->link_status[4], पूर्णांकel_dp->link_status[5]);

		अगर (cdv_पूर्णांकel_घड़ी_recovery_ok(पूर्णांकel_dp->link_status, पूर्णांकel_dp->lane_count)) अणु
			DRM_DEBUG_KMS("PT1 train is done\n");
			घड़ी_recovery = true;
			अवरोध;
		पूर्ण

		/* Check to see अगर we've tried the max voltage */
		क्रम (i = 0; i < पूर्णांकel_dp->lane_count; i++)
			अगर ((पूर्णांकel_dp->train_set[i] & DP_TRAIN_MAX_SWING_REACHED) == 0)
				अवरोध;
		अगर (i == पूर्णांकel_dp->lane_count)
			अवरोध;

		/* Check to see अगर we've tried the same voltage 5 बार */
		अगर ((पूर्णांकel_dp->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK) == voltage) अणु
			++tries;
			अगर (tries == 5)
				अवरोध;
		पूर्ण अन्यथा
			tries = 0;
		voltage = पूर्णांकel_dp->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK;

		/* Compute new पूर्णांकel_dp->train_set as requested by target */
		cdv_पूर्णांकel_get_adjust_train(encoder);

	पूर्ण

	अगर (!घड़ी_recovery) अणु
		DRM_DEBUG_KMS("failure in DP patter 1 training, train set %x\n", पूर्णांकel_dp->train_set[0]);
	पूर्ण
	
	पूर्णांकel_dp->DP = DP;
पूर्ण

अटल व्योम
cdv_पूर्णांकel_dp_complete_link_train(काष्ठा gma_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	पूर्णांक tries, cr_tries;
	u32 reg;
	uपूर्णांक32_t DP = पूर्णांकel_dp->DP;

	/* channel equalization */
	tries = 0;
	cr_tries = 0;

	DRM_DEBUG_KMS("\n");
	reg = DP | DP_LINK_TRAIN_PAT_2;

	क्रम (;;) अणु

		DRM_DEBUG_KMS("DP Link Train Set %x, Link_config %x, %x\n",
				पूर्णांकel_dp->train_set[0],
				पूर्णांकel_dp->link_configuration[0],
				पूर्णांकel_dp->link_configuration[1]);
        	/* channel eq pattern */

		अगर (!cdv_पूर्णांकel_dp_set_link_train(encoder, reg,
					     DP_TRAINING_PATTERN_2)) अणु
			DRM_DEBUG_KMS("Failure in aux-transfer setting pattern 2\n");
		पूर्ण
		/* Use पूर्णांकel_dp->train_set[0] to set the voltage and pre emphasis values */

		अगर (cr_tries > 5) अणु
			DRM_ERROR("failed to train DP, aborting\n");
			cdv_पूर्णांकel_dp_link_करोwn(encoder);
			अवरोध;
		पूर्ण

		cdv_पूर्णांकel_dp_set_vswing_premph(encoder, पूर्णांकel_dp->train_set[0]);

		cdv_पूर्णांकel_dplink_set_level(encoder, DP_TRAINING_PATTERN_2);

		udelay(1000);
		अगर (!cdv_पूर्णांकel_dp_get_link_status(encoder))
			अवरोध;

		DRM_DEBUG_KMS("DP Link status %x, %x, %x, %x, %x, %x\n",
				पूर्णांकel_dp->link_status[0], पूर्णांकel_dp->link_status[1], पूर्णांकel_dp->link_status[2],
				पूर्णांकel_dp->link_status[3], पूर्णांकel_dp->link_status[4], पूर्णांकel_dp->link_status[5]);

		/* Make sure घड़ी is still ok */
		अगर (!cdv_पूर्णांकel_घड़ी_recovery_ok(पूर्णांकel_dp->link_status, पूर्णांकel_dp->lane_count)) अणु
			cdv_पूर्णांकel_dp_start_link_train(encoder);
			cr_tries++;
			जारी;
		पूर्ण

		अगर (cdv_पूर्णांकel_channel_eq_ok(encoder)) अणु
			DRM_DEBUG_KMS("PT2 train is done\n");
			अवरोध;
		पूर्ण

		/* Try 5 बार, then try घड़ी recovery अगर that fails */
		अगर (tries > 5) अणु
			cdv_पूर्णांकel_dp_link_करोwn(encoder);
			cdv_पूर्णांकel_dp_start_link_train(encoder);
			tries = 0;
			cr_tries++;
			जारी;
		पूर्ण

		/* Compute new पूर्णांकel_dp->train_set as requested by target */
		cdv_पूर्णांकel_get_adjust_train(encoder);
		++tries;

	पूर्ण

	reg = DP | DP_LINK_TRAIN_OFF;

	REG_WRITE(पूर्णांकel_dp->output_reg, reg);
	REG_READ(पूर्णांकel_dp->output_reg);
	cdv_पूर्णांकel_dp_aux_native_ग_लिखो_1(encoder,
				    DP_TRAINING_PATTERN_SET, DP_TRAINING_PATTERN_DISABLE);
पूर्ण

अटल व्योम
cdv_पूर्णांकel_dp_link_करोwn(काष्ठा gma_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	uपूर्णांक32_t DP = पूर्णांकel_dp->DP;

	अगर ((REG_READ(पूर्णांकel_dp->output_reg) & DP_PORT_EN) == 0)
		वापस;

	DRM_DEBUG_KMS("\n");


	अणु
		DP &= ~DP_LINK_TRAIN_MASK;
		REG_WRITE(पूर्णांकel_dp->output_reg, DP | DP_LINK_TRAIN_PAT_IDLE);
	पूर्ण
	REG_READ(पूर्णांकel_dp->output_reg);

	msleep(17);

	REG_WRITE(पूर्णांकel_dp->output_reg, DP & ~DP_PORT_EN);
	REG_READ(पूर्णांकel_dp->output_reg);
पूर्ण

अटल क्रमागत drm_connector_status cdv_dp_detect(काष्ठा gma_encoder *encoder)
अणु
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	क्रमागत drm_connector_status status;

	status = connector_status_disconnected;
	अगर (cdv_पूर्णांकel_dp_aux_native_पढ़ो(encoder, 0x000, पूर्णांकel_dp->dpcd,
				     माप (पूर्णांकel_dp->dpcd)) == माप (पूर्णांकel_dp->dpcd))
	अणु
		अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] != 0)
			status = connector_status_connected;
	पूर्ण
	अगर (status == connector_status_connected)
		DRM_DEBUG_KMS("DPCD: Rev=%x LN_Rate=%x LN_CNT=%x LN_DOWNSP=%x\n",
			पूर्णांकel_dp->dpcd[0], पूर्णांकel_dp->dpcd[1],
			पूर्णांकel_dp->dpcd[2], पूर्णांकel_dp->dpcd[3]);
	वापस status;
पूर्ण

/*
 * Uses CRT_HOTPLUG_EN and CRT_HOTPLUG_STAT to detect DP connection.
 *
 * \लeturn true अगर DP port is connected.
 * \लeturn false अगर DP port is disconnected.
 */
अटल क्रमागत drm_connector_status
cdv_पूर्णांकel_dp_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा gma_encoder *encoder = gma_attached_encoder(connector);
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	क्रमागत drm_connector_status status;
	काष्ठा edid *edid = शून्य;
	पूर्णांक edp = is_edp(encoder);

	पूर्णांकel_dp->has_audio = false;

	अगर (edp)
		cdv_पूर्णांकel_edp_panel_vdd_on(encoder);
	status = cdv_dp_detect(encoder);
	अगर (status != connector_status_connected) अणु
		अगर (edp)
			cdv_पूर्णांकel_edp_panel_vdd_off(encoder);
		वापस status;
        पूर्ण

	अगर (पूर्णांकel_dp->क्रमce_audio) अणु
		पूर्णांकel_dp->has_audio = पूर्णांकel_dp->क्रमce_audio > 0;
	पूर्ण अन्यथा अणु
		edid = drm_get_edid(connector, &पूर्णांकel_dp->adapter);
		अगर (edid) अणु
			पूर्णांकel_dp->has_audio = drm_detect_monitor_audio(edid);
			kमुक्त(edid);
		पूर्ण
	पूर्ण
	अगर (edp)
		cdv_पूर्णांकel_edp_panel_vdd_off(encoder);

	वापस connector_status_connected;
पूर्ण

अटल पूर्णांक cdv_पूर्णांकel_dp_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा gma_encoder *पूर्णांकel_encoder = gma_attached_encoder(connector);
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_encoder->dev_priv;
	काष्ठा edid *edid = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक edp = is_edp(पूर्णांकel_encoder);


	edid = drm_get_edid(connector, &पूर्णांकel_dp->adapter);
	अगर (edid) अणु
		drm_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
	पूर्ण

	अगर (is_edp(पूर्णांकel_encoder)) अणु
		काष्ठा drm_device *dev = connector->dev;
		काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
		
		cdv_पूर्णांकel_edp_panel_vdd_off(पूर्णांकel_encoder);
		अगर (ret) अणु
			अगर (edp && !पूर्णांकel_dp->panel_fixed_mode) अणु
				काष्ठा drm_display_mode *newmode;
				list_क्रम_each_entry(newmode, &connector->probed_modes,
					    head) अणु
					अगर (newmode->type & DRM_MODE_TYPE_PREFERRED) अणु
						पूर्णांकel_dp->panel_fixed_mode =
							drm_mode_duplicate(dev, newmode);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			वापस ret;
		पूर्ण
		अगर (!पूर्णांकel_dp->panel_fixed_mode && dev_priv->lfp_lvds_vbt_mode) अणु
			पूर्णांकel_dp->panel_fixed_mode =
				drm_mode_duplicate(dev, dev_priv->lfp_lvds_vbt_mode);
			अगर (पूर्णांकel_dp->panel_fixed_mode) अणु
				पूर्णांकel_dp->panel_fixed_mode->type |=
					DRM_MODE_TYPE_PREFERRED;
			पूर्ण
		पूर्ण
		अगर (पूर्णांकel_dp->panel_fixed_mode != शून्य) अणु
			काष्ठा drm_display_mode *mode;
			mode = drm_mode_duplicate(dev, पूर्णांकel_dp->panel_fixed_mode);
			drm_mode_probed_add(connector, mode);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल bool
cdv_पूर्णांकel_dp_detect_audio(काष्ठा drm_connector *connector)
अणु
	काष्ठा gma_encoder *encoder = gma_attached_encoder(connector);
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	काष्ठा edid *edid;
	bool has_audio = false;
	पूर्णांक edp = is_edp(encoder);

	अगर (edp)
		cdv_पूर्णांकel_edp_panel_vdd_on(encoder);

	edid = drm_get_edid(connector, &पूर्णांकel_dp->adapter);
	अगर (edid) अणु
		has_audio = drm_detect_monitor_audio(edid);
		kमुक्त(edid);
	पूर्ण
	अगर (edp)
		cdv_पूर्णांकel_edp_panel_vdd_off(encoder);

	वापस has_audio;
पूर्ण

अटल पूर्णांक
cdv_पूर्णांकel_dp_set_property(काष्ठा drm_connector *connector,
		      काष्ठा drm_property *property,
		      uपूर्णांक64_t val)
अणु
	काष्ठा drm_psb_निजी *dev_priv = connector->dev->dev_निजी;
	काष्ठा gma_encoder *encoder = gma_attached_encoder(connector);
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = encoder->dev_priv;
	पूर्णांक ret;

	ret = drm_object_property_set_value(&connector->base, property, val);
	अगर (ret)
		वापस ret;

	अगर (property == dev_priv->क्रमce_audio_property) अणु
		पूर्णांक i = val;
		bool has_audio;

		अगर (i == पूर्णांकel_dp->क्रमce_audio)
			वापस 0;

		पूर्णांकel_dp->क्रमce_audio = i;

		अगर (i == 0)
			has_audio = cdv_पूर्णांकel_dp_detect_audio(connector);
		अन्यथा
			has_audio = i > 0;

		अगर (has_audio == पूर्णांकel_dp->has_audio)
			वापस 0;

		पूर्णांकel_dp->has_audio = has_audio;
		जाओ करोne;
	पूर्ण

	अगर (property == dev_priv->broadcast_rgb_property) अणु
		अगर (val == !!पूर्णांकel_dp->color_range)
			वापस 0;

		पूर्णांकel_dp->color_range = val ? DP_COLOR_RANGE_16_235 : 0;
		जाओ करोne;
	पूर्ण

	वापस -EINVAL;

करोne:
	अगर (encoder->base.crtc) अणु
		काष्ठा drm_crtc *crtc = encoder->base.crtc;
		drm_crtc_helper_set_mode(crtc, &crtc->mode,
					 crtc->x, crtc->y,
					 crtc->primary->fb);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
cdv_पूर्णांकel_dp_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp = gma_encoder->dev_priv;

	अगर (is_edp(gma_encoder)) अणु
	/*	cdv_पूर्णांकel_panel_destroy_backlight(connector->dev); */
		kमुक्त(पूर्णांकel_dp->panel_fixed_mode);
		पूर्णांकel_dp->panel_fixed_mode = शून्य;
	पूर्ण
	i2c_del_adapter(&पूर्णांकel_dp->adapter);
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs cdv_पूर्णांकel_dp_helper_funcs = अणु
	.dpms = cdv_पूर्णांकel_dp_dpms,
	.mode_fixup = cdv_पूर्णांकel_dp_mode_fixup,
	.prepare = cdv_पूर्णांकel_dp_prepare,
	.mode_set = cdv_पूर्णांकel_dp_mode_set,
	.commit = cdv_पूर्णांकel_dp_commit,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs cdv_पूर्णांकel_dp_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = cdv_पूर्णांकel_dp_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = cdv_पूर्णांकel_dp_set_property,
	.destroy = cdv_पूर्णांकel_dp_destroy,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs cdv_पूर्णांकel_dp_connector_helper_funcs = अणु
	.get_modes = cdv_पूर्णांकel_dp_get_modes,
	.mode_valid = cdv_पूर्णांकel_dp_mode_valid,
	.best_encoder = gma_best_encoder,
पूर्ण;

अटल व्योम cdv_पूर्णांकel_dp_add_properties(काष्ठा drm_connector *connector)
अणु
	cdv_पूर्णांकel_attach_क्रमce_audio_property(connector);
	cdv_पूर्णांकel_attach_broadcast_rgb_property(connector);
पूर्ण

/* check the VBT to see whether the eDP is on DP-D port */
अटल bool cdv_पूर्णांकel_dpc_is_edp(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा child_device_config *p_child;
	पूर्णांक i;

	अगर (!dev_priv->child_dev_num)
		वापस false;

	क्रम (i = 0; i < dev_priv->child_dev_num; i++) अणु
		p_child = dev_priv->child_dev + i;

		अगर (p_child->dvo_port == PORT_IDPC &&
		    p_child->device_type == DEVICE_TYPE_eDP)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Cedarview display घड़ी gating

   We need this disable करोt get correct behaviour जबतक enabling
   DP/eDP. TODO - investigate अगर we can turn it back to normality
   after enabling */
अटल व्योम cdv_disable_पूर्णांकel_घड़ी_gating(काष्ठा drm_device *dev)
अणु
	u32 reg_value;
	reg_value = REG_READ(DSPCLK_GATE_D);

	reg_value |= (DPUNIT_PIPEB_GATE_DISABLE |
			DPUNIT_PIPEA_GATE_DISABLE |
			DPCUNIT_CLOCK_GATE_DISABLE |
			DPLSUNIT_CLOCK_GATE_DISABLE |
			DPOUNIT_CLOCK_GATE_DISABLE |
		 	DPIOUNIT_CLOCK_GATE_DISABLE);	

	REG_WRITE(DSPCLK_GATE_D, reg_value);

	udelay(500);		
पूर्ण

व्योम
cdv_पूर्णांकel_dp_init(काष्ठा drm_device *dev, काष्ठा psb_पूर्णांकel_mode_device *mode_dev, पूर्णांक output_reg)
अणु
	काष्ठा gma_encoder *gma_encoder;
	काष्ठा gma_connector *gma_connector;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा cdv_पूर्णांकel_dp *पूर्णांकel_dp;
	स्थिर अक्षर *name = शून्य;
	पूर्णांक type = DRM_MODE_CONNECTOR_DisplayPort;

	gma_encoder = kzalloc(माप(काष्ठा gma_encoder), GFP_KERNEL);
	अगर (!gma_encoder)
		वापस;
        gma_connector = kzalloc(माप(काष्ठा gma_connector), GFP_KERNEL);
        अगर (!gma_connector)
                जाओ err_connector;
	पूर्णांकel_dp = kzalloc(माप(काष्ठा cdv_पूर्णांकel_dp), GFP_KERNEL);
	अगर (!पूर्णांकel_dp)
	        जाओ err_priv;

	अगर ((output_reg == DP_C) && cdv_पूर्णांकel_dpc_is_edp(dev))
		type = DRM_MODE_CONNECTOR_eDP;

	connector = &gma_connector->base;
	encoder = &gma_encoder->base;

	drm_connector_init(dev, connector, &cdv_पूर्णांकel_dp_connector_funcs, type);
	drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_TMDS);

	gma_connector_attach_encoder(gma_connector, gma_encoder);

	अगर (type == DRM_MODE_CONNECTOR_DisplayPort)
		gma_encoder->type = INTEL_OUTPUT_DISPLAYPORT;
        अन्यथा
		gma_encoder->type = INTEL_OUTPUT_EDP;


	gma_encoder->dev_priv=पूर्णांकel_dp;
	पूर्णांकel_dp->encoder = gma_encoder;
	पूर्णांकel_dp->output_reg = output_reg;
	
	drm_encoder_helper_add(encoder, &cdv_पूर्णांकel_dp_helper_funcs);
	drm_connector_helper_add(connector, &cdv_पूर्णांकel_dp_connector_helper_funcs);

	connector->polled = DRM_CONNECTOR_POLL_HPD;
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;

	drm_connector_रेजिस्टर(connector);

	/* Set up the DDC bus. */
	चयन (output_reg) अणु
		हाल DP_B:
			name = "DPDDC-B";
			gma_encoder->ddi_select = (DP_MASK | DDI0_SELECT);
			अवरोध;
		हाल DP_C:
			name = "DPDDC-C";
			gma_encoder->ddi_select = (DP_MASK | DDI1_SELECT);
			अवरोध;
	पूर्ण

	cdv_disable_पूर्णांकel_घड़ी_gating(dev);

	cdv_पूर्णांकel_dp_i2c_init(gma_connector, gma_encoder, name);
        /* FIXME:fail check */
	cdv_पूर्णांकel_dp_add_properties(connector);

	अगर (is_edp(gma_encoder)) अणु
		पूर्णांक ret;
		काष्ठा edp_घातer_seq cur;
                u32 pp_on, pp_off, pp_भाग;
		u32 pwm_ctrl;

		pp_on = REG_READ(PP_CONTROL);
		pp_on &= ~PANEL_UNLOCK_MASK;
	        pp_on |= PANEL_UNLOCK_REGS;
		
		REG_WRITE(PP_CONTROL, pp_on);

		pwm_ctrl = REG_READ(BLC_PWM_CTL2);
		pwm_ctrl |= PWM_PIPE_B;
		REG_WRITE(BLC_PWM_CTL2, pwm_ctrl);

                pp_on = REG_READ(PP_ON_DELAYS);
                pp_off = REG_READ(PP_OFF_DELAYS);
                pp_भाग = REG_READ(PP_DIVISOR);
	
		/* Pull timing values out of रेजिस्टरs */
                cur.t1_t3 = (pp_on & PANEL_POWER_UP_DELAY_MASK) >>
                        PANEL_POWER_UP_DELAY_SHIFT;

                cur.t8 = (pp_on & PANEL_LIGHT_ON_DELAY_MASK) >>
                        PANEL_LIGHT_ON_DELAY_SHIFT;

                cur.t9 = (pp_off & PANEL_LIGHT_OFF_DELAY_MASK) >>
                        PANEL_LIGHT_OFF_DELAY_SHIFT;

                cur.t10 = (pp_off & PANEL_POWER_DOWN_DELAY_MASK) >>
                        PANEL_POWER_DOWN_DELAY_SHIFT;

                cur.t11_t12 = ((pp_भाग & PANEL_POWER_CYCLE_DELAY_MASK) >>
                               PANEL_POWER_CYCLE_DELAY_SHIFT);

                DRM_DEBUG_KMS("cur t1_t3 %d t8 %d t9 %d t10 %d t11_t12 %d\n",
                              cur.t1_t3, cur.t8, cur.t9, cur.t10, cur.t11_t12);


		पूर्णांकel_dp->panel_घातer_up_delay = cur.t1_t3 / 10;
                पूर्णांकel_dp->backlight_on_delay = cur.t8 / 10;
                पूर्णांकel_dp->backlight_off_delay = cur.t9 / 10;
                पूर्णांकel_dp->panel_घातer_करोwn_delay = cur.t10 / 10;
                पूर्णांकel_dp->panel_घातer_cycle_delay = (cur.t11_t12 - 1) * 100;

                DRM_DEBUG_KMS("panel power up delay %d, power down delay %d, power cycle delay %d\n",
                              पूर्णांकel_dp->panel_घातer_up_delay, पूर्णांकel_dp->panel_घातer_करोwn_delay,
                              पूर्णांकel_dp->panel_घातer_cycle_delay);

                DRM_DEBUG_KMS("backlight on delay %d, off delay %d\n",
                              पूर्णांकel_dp->backlight_on_delay, पूर्णांकel_dp->backlight_off_delay);


		cdv_पूर्णांकel_edp_panel_vdd_on(gma_encoder);
		ret = cdv_पूर्णांकel_dp_aux_native_पढ़ो(gma_encoder, DP_DPCD_REV,
					       पूर्णांकel_dp->dpcd,
					       माप(पूर्णांकel_dp->dpcd));
		cdv_पूर्णांकel_edp_panel_vdd_off(gma_encoder);
		अगर (ret <= 0) अणु
			/* अगर this fails, presume the device is a ghost */
			DRM_INFO("failed to retrieve link info, disabling eDP\n");
			drm_encoder_cleanup(encoder);
			cdv_पूर्णांकel_dp_destroy(connector);
			जाओ err_connector;
		पूर्ण अन्यथा अणु
        		DRM_DEBUG_KMS("DPCD: Rev=%x LN_Rate=%x LN_CNT=%x LN_DOWNSP=%x\n",
				पूर्णांकel_dp->dpcd[0], पूर्णांकel_dp->dpcd[1], 
				पूर्णांकel_dp->dpcd[2], पूर्णांकel_dp->dpcd[3]);
			
		पूर्ण
		/* The CDV reference driver moves pnale backlight setup पूर्णांकo the displays that
		   have a backlight: this is a good idea and one we should probably aकरोpt, however
		   we need to migrate all the drivers beक्रमe we can करो that */
                /*cdv_पूर्णांकel_panel_setup_backlight(dev); */
	पूर्ण
	वापस;

err_priv:
	kमुक्त(gma_connector);
err_connector:
	kमुक्त(gma_encoder);
पूर्ण
