<शैली गुरु>
// SPDX-License-Identअगरier: MIT
// Copyright तऊ 2014 Intel Corporation

#अगर_अघोषित _DRM_AUDIO_COMPONENT_H_
#घोषणा _DRM_AUDIO_COMPONENT_H_

काष्ठा drm_audio_component;
काष्ठा device;

/**
 * काष्ठा drm_audio_component_ops - Ops implemented by DRM driver, called by hda driver
 */
काष्ठा drm_audio_component_ops अणु
	/**
	 * @owner: drm module to pin करोwn
	 */
	काष्ठा module *owner;
	/**
	 * @get_घातer: get the POWER_DOMAIN_AUDIO घातer well
	 *
	 * Request the घातer well to be turned on.
	 *
	 * Returns a wakeref cookie to be passed back to the corresponding
	 * call to @put_घातer.
	 */
	अचिन्हित दीर्घ (*get_घातer)(काष्ठा device *);
	/**
	 * @put_घातer: put the POWER_DOMAIN_AUDIO घातer well
	 *
	 * Allow the घातer well to be turned off.
	 */
	व्योम (*put_घातer)(काष्ठा device *, अचिन्हित दीर्घ);
	/**
	 * @codec_wake_override: Enable/disable codec wake संकेत
	 */
	व्योम (*codec_wake_override)(काष्ठा device *, bool enable);
	/**
	 * @get_cdclk_freq: Get the Core Display Clock in kHz
	 */
	पूर्णांक (*get_cdclk_freq)(काष्ठा device *);
	/**
	 * @sync_audio_rate: set n/cts based on the sample rate
	 *
	 * Called from audio driver. After audio driver sets the
	 * sample rate, it will call this function to set n/cts
	 */
	पूर्णांक (*sync_audio_rate)(काष्ठा device *, पूर्णांक port, पूर्णांक pipe, पूर्णांक rate);
	/**
	 * @get_eld: fill the audio state and ELD bytes क्रम the given port
	 *
	 * Called from audio driver to get the HDMI/DP audio state of the given
	 * digital port, and also fetch ELD bytes to the given poपूर्णांकer.
	 *
	 * It वापसs the byte size of the original ELD (not the actually
	 * copied size), zero क्रम an invalid ELD, or a negative error code.
	 *
	 * Note that the वापसed size may be over @max_bytes.  Then it
	 * implies that only a part of ELD has been copied to the buffer.
	 */
	पूर्णांक (*get_eld)(काष्ठा device *, पूर्णांक port, पूर्णांक pipe, bool *enabled,
		       अचिन्हित अक्षर *buf, पूर्णांक max_bytes);
पूर्ण;

/**
 * काष्ठा drm_audio_component_audio_ops - Ops implemented by hda driver, called by DRM driver
 */
काष्ठा drm_audio_component_audio_ops अणु
	/**
	 * @audio_ptr: Poपूर्णांकer to be used in call to pin_eld_notअगरy
	 */
	व्योम *audio_ptr;
	/**
	 * @pin_eld_notअगरy: Notअगरy the HDA driver that pin sense and/or ELD inक्रमmation has changed
	 *
	 * Called when the DRM driver has set up audio pipeline or has just
	 * begun to tear it करोwn. This allows the HDA driver to update its
	 * status accordingly (even when the HDA controller is in घातer save
	 * mode).
	 */
	व्योम (*pin_eld_notअगरy)(व्योम *audio_ptr, पूर्णांक port, पूर्णांक pipe);
	/**
	 * @pin2port: Check and convert from pin node to port number
	 *
	 * Called by HDA driver to check and convert from the pin widget node
	 * number to a port number in the graphics side.
	 */
	पूर्णांक (*pin2port)(व्योम *audio_ptr, पूर्णांक pin);
	/**
	 * @master_bind: (Optional) component master bind callback
	 *
	 * Called at binding master component, क्रम HDA codec-specअगरic
	 * handling of dynamic binding.
	 */
	पूर्णांक (*master_bind)(काष्ठा device *dev, काष्ठा drm_audio_component *);
	/**
	 * @master_unbind: (Optional) component master unbind callback
	 *
	 * Called at unbinding master component, क्रम HDA codec-specअगरic
	 * handling of dynamic unbinding.
	 */
	व्योम (*master_unbind)(काष्ठा device *dev, काष्ठा drm_audio_component *);
पूर्ण;

/**
 * काष्ठा drm_audio_component - Used क्रम direct communication between DRM and hda drivers
 */
काष्ठा drm_audio_component अणु
	/**
	 * @dev: DRM device, used as parameter क्रम ops
	 */
	काष्ठा device *dev;
	/**
	 * @ops: Ops implemented by DRM driver, called by hda driver
	 */
	स्थिर काष्ठा drm_audio_component_ops *ops;
	/**
	 * @audio_ops: Ops implemented by hda driver, called by DRM driver
	 */
	स्थिर काष्ठा drm_audio_component_audio_ops *audio_ops;
	/**
	 * @master_bind_complete: completion held during component master binding
	 */
	काष्ठा completion master_bind_complete;
पूर्ण;

#पूर्ण_अगर /* _DRM_AUDIO_COMPONENT_H_ */
