<शैली गुरु>
/*
 * Copyright तऊ 2006 Eric Anholt
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#अगर_अघोषित __INTEL_DVO_DEV_H__
#घोषणा __INTEL_DVO_DEV_H__

#समावेश <linux/i2c.h>

#समावेश <drm/drm_crtc.h>

#समावेश "i915_reg.h"

काष्ठा पूर्णांकel_dvo_device अणु
	स्थिर अक्षर *name;
	पूर्णांक type;
	/* DVOA/B/C output रेजिस्टर */
	i915_reg_t dvo_reg;
	i915_reg_t dvo_srcdim_reg;
	/* GPIO रेजिस्टर used क्रम i2c bus to control this device */
	u32 gpio;
	पूर्णांक slave_addr;

	स्थिर काष्ठा पूर्णांकel_dvo_dev_ops *dev_ops;
	व्योम *dev_priv;
	काष्ठा i2c_adapter *i2c_bus;
पूर्ण;

काष्ठा पूर्णांकel_dvo_dev_ops अणु
	/*
	 * Initialize the device at startup समय.
	 * Returns शून्य अगर the device करोes not exist.
	 */
	bool (*init)(काष्ठा पूर्णांकel_dvo_device *dvo,
		     काष्ठा i2c_adapter *i2cbus);

	/*
	 * Called to allow the output a chance to create properties after the
	 * RandR objects have been created.
	 */
	व्योम (*create_resources)(काष्ठा पूर्णांकel_dvo_device *dvo);

	/*
	 * Turn on/off output.
	 *
	 * Because none of our dvo drivers support an पूर्णांकermediate घातer levels,
	 * we करोn't expose this in the पूर्णांकerfac.
	 */
	व्योम (*dpms)(काष्ठा पूर्णांकel_dvo_device *dvo, bool enable);

	/*
	 * Callback क्रम testing a video mode क्रम a given output.
	 *
	 * This function should only check क्रम हालs where a mode can't
	 * be supported on the output specअगरically, and not represent
	 * generic CRTC limitations.
	 *
	 * \लeturn MODE_OK अगर the mode is valid, or another MODE_* otherwise.
	 */
	पूर्णांक (*mode_valid)(काष्ठा पूर्णांकel_dvo_device *dvo,
			  काष्ठा drm_display_mode *mode);

	/*
	 * Callback क्रम preparing mode changes on an output
	 */
	व्योम (*prepare)(काष्ठा पूर्णांकel_dvo_device *dvo);

	/*
	 * Callback क्रम committing mode changes on an output
	 */
	व्योम (*commit)(काष्ठा पूर्णांकel_dvo_device *dvo);

	/*
	 * Callback क्रम setting up a video mode after fixups have been made.
	 *
	 * This is only called जबतक the output is disabled.  The dpms callback
	 * must be all that's necessary क्रम the output, to turn the output on
	 * after this function is called.
	 */
	व्योम (*mode_set)(काष्ठा पूर्णांकel_dvo_device *dvo,
			 स्थिर काष्ठा drm_display_mode *mode,
			 स्थिर काष्ठा drm_display_mode *adjusted_mode);

	/*
	 * Probe क्रम a connected output, and वापस detect_status.
	 */
	क्रमागत drm_connector_status (*detect)(काष्ठा पूर्णांकel_dvo_device *dvo);

	/*
	 * Probe the current hw status, वापसing true अगर the connected output
	 * is active.
	 */
	bool (*get_hw_state)(काष्ठा पूर्णांकel_dvo_device *dev);

	/**
	 * Query the device क्रम the modes it provides.
	 *
	 * This function may also update MonInfo, mm_width, and mm_height.
	 *
	 * \लeturn singly-linked list of modes or शून्य अगर no modes found.
	 */
	काष्ठा drm_display_mode *(*get_modes)(काष्ठा पूर्णांकel_dvo_device *dvo);

	/**
	 * Clean up driver-specअगरic bits of the output
	 */
	व्योम (*destroy) (काष्ठा पूर्णांकel_dvo_device *dvo);

	/**
	 * Debugging hook to dump device रेजिस्टरs to log file
	 */
	व्योम (*dump_regs)(काष्ठा पूर्णांकel_dvo_device *dvo);
पूर्ण;

बाह्य स्थिर काष्ठा पूर्णांकel_dvo_dev_ops sil164_ops;
बाह्य स्थिर काष्ठा पूर्णांकel_dvo_dev_ops ch7xxx_ops;
बाह्य स्थिर काष्ठा पूर्णांकel_dvo_dev_ops ivch_ops;
बाह्य स्थिर काष्ठा पूर्णांकel_dvo_dev_ops tfp410_ops;
बाह्य स्थिर काष्ठा पूर्णांकel_dvo_dev_ops ch7017_ops;
बाह्य स्थिर काष्ठा पूर्णांकel_dvo_dev_ops ns2501_ops;

#पूर्ण_अगर /* __INTEL_DVO_DEV_H__ */
