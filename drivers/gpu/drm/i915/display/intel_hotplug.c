<शैली गुरु>
/*
 * Copyright तऊ 2015 Intel Corporation
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
 */

#समावेश <linux/kernel.h>

#समावेश "i915_drv.h"
#समावेश "intel_display_types.h"
#समावेश "intel_hotplug.h"

/**
 * DOC: Hotplug
 *
 * Simply put, hotplug occurs when a display is connected to or disconnected
 * from the प्रणाली. However, there may be adapters and करोcking stations and
 * Display Port लघु pulses and MST devices involved, complicating matters.
 *
 * Hotplug in i915 is handled in many dअगरferent levels of असलtraction.
 *
 * The platक्रमm dependent पूर्णांकerrupt handling code in i915_irq.c enables,
 * disables, and करोes preliminary handling of the पूर्णांकerrupts. The पूर्णांकerrupt
 * handlers gather the hotplug detect (HPD) inक्रमmation from relevant रेजिस्टरs
 * पूर्णांकo a platक्रमm independent mask of hotplug pins that have fired.
 *
 * The platक्रमm independent पूर्णांकerrupt handler पूर्णांकel_hpd_irq_handler() in
 * पूर्णांकel_hotplug.c करोes hotplug irq storm detection and mitigation, and passes
 * further processing to appropriate bottom halves (Display Port specअगरic and
 * regular hotplug).
 *
 * The Display Port work function i915_digport_work_func() calls पूर्णांकo
 * पूर्णांकel_dp_hpd_pulse() via hooks, which handles DP लघु pulses and DP MST दीर्घ
 * pulses, with failures and non-MST दीर्घ pulses triggering regular hotplug
 * processing on the connector.
 *
 * The regular hotplug work function i915_hotplug_work_func() calls connector
 * detect hooks, and, अगर connector status changes, triggers sending of hotplug
 * uevent to userspace via drm_kms_helper_hotplug_event().
 *
 * Finally, the userspace is responsible क्रम triggering a modeset upon receiving
 * the hotplug uevent, disabling or enabling the crtc as needed.
 *
 * The hotplug पूर्णांकerrupt storm detection and mitigation code keeps track of the
 * number of पूर्णांकerrupts per hotplug pin per a period of समय, and अगर the number
 * of पूर्णांकerrupts exceeds a certain threshold, the पूर्णांकerrupt is disabled क्रम a
 * जबतक beक्रमe being re-enabled. The पूर्णांकention is to mitigate issues raising
 * from broken hardware triggering massive amounts of पूर्णांकerrupts and grinding
 * the प्रणाली to a halt.
 *
 * Current implementation expects that hotplug पूर्णांकerrupt storm will not be
 * seen when display port sink is connected, hence on platक्रमms whose DP
 * callback is handled by i915_digport_work_func reenabling of hpd is not
 * perक्रमmed (it was never expected to be disabled in the first place ;) )
 * this is specअगरic to DP sinks handled by this routine and any other display
 * such as HDMI or DVI enabled on the same port will have proper logic since
 * it will use i915_hotplug_work_func where this logic is handled.
 */

/**
 * पूर्णांकel_hpd_pin_शेष - वापस शेष pin associated with certain port.
 * @dev_priv: निजी driver data poपूर्णांकer
 * @port: the hpd port to get associated pin
 *
 * It is only valid and used by digital port encoder.
 *
 * Return pin that is associatade with @port.
 */
क्रमागत hpd_pin पूर्णांकel_hpd_pin_शेष(काष्ठा drm_i915_निजी *dev_priv,
				   क्रमागत port port)
अणु
	वापस HPD_PORT_A + port - PORT_A;
पूर्ण

#घोषणा HPD_STORM_DETECT_PERIOD		1000
#घोषणा HPD_STORM_REENABLE_DELAY	(2 * 60 * 1000)
#घोषणा HPD_RETRY_DELAY			1000

अटल क्रमागत hpd_pin
पूर्णांकel_connector_hpd_pin(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = पूर्णांकel_attached_encoder(connector);

	/*
	 * MST connectors get their encoder attached dynamically
	 * so need to make sure we have an encoder here. But since
	 * MST encoders have their hpd_pin set to HPD_NONE we करोn't
	 * have to special हाल them beyond that.
	 */
	वापस encoder ? encoder->hpd_pin : HPD_NONE;
पूर्ण

/**
 * पूर्णांकel_hpd_irq_storm_detect - gather stats and detect HPD IRQ storm on a pin
 * @dev_priv: निजी driver data poपूर्णांकer
 * @pin: the pin to gather stats on
 * @दीर्घ_hpd: whether the HPD IRQ was दीर्घ or लघु
 *
 * Gather stats about HPD IRQs from the specअगरied @pin, and detect IRQ
 * storms. Only the pin specअगरic stats and state are changed, the caller is
 * responsible क्रम further action.
 *
 * The number of IRQs that are allowed within @HPD_STORM_DETECT_PERIOD is
 * stored in @dev_priv->hotplug.hpd_storm_threshold which शेषs to
 * @HPD_STORM_DEFAULT_THRESHOLD. Long IRQs count as +10 to this threshold, and
 * लघु IRQs count as +1. If this threshold is exceeded, it's considered an
 * IRQ storm and the IRQ state is set to @HPD_MARK_DISABLED.
 *
 * By शेष, most प्रणालीs will only count दीर्घ IRQs towards
 * &dev_priv->hotplug.hpd_storm_threshold. However, some older प्रणालीs also
 * suffer from लघु IRQ storms and must also track these. Because लघु IRQ
 * storms are naturally caused by sideband पूर्णांकeractions with DP MST devices,
 * लघु IRQ detection is only enabled क्रम प्रणालीs without DP MST support.
 * Systems which are new enough to support DP MST are far less likely to
 * suffer from IRQ storms at all, so this is fine.
 *
 * The HPD threshold can be controlled through i915_hpd_storm_ctl in debugfs,
 * and should only be adjusted क्रम स्वतःmated hotplug testing.
 *
 * Return true अगर an IRQ storm was detected on @pin.
 */
अटल bool पूर्णांकel_hpd_irq_storm_detect(काष्ठा drm_i915_निजी *dev_priv,
				       क्रमागत hpd_pin pin, bool दीर्घ_hpd)
अणु
	काष्ठा i915_hotplug *hpd = &dev_priv->hotplug;
	अचिन्हित दीर्घ start = hpd->stats[pin].last_jअगरfies;
	अचिन्हित दीर्घ end = start + msecs_to_jअगरfies(HPD_STORM_DETECT_PERIOD);
	स्थिर पूर्णांक increment = दीर्घ_hpd ? 10 : 1;
	स्थिर पूर्णांक threshold = hpd->hpd_storm_threshold;
	bool storm = false;

	अगर (!threshold ||
	    (!दीर्घ_hpd && !dev_priv->hotplug.hpd_लघु_storm_enabled))
		वापस false;

	अगर (!समय_in_range(jअगरfies, start, end)) अणु
		hpd->stats[pin].last_jअगरfies = jअगरfies;
		hpd->stats[pin].count = 0;
	पूर्ण

	hpd->stats[pin].count += increment;
	अगर (hpd->stats[pin].count > threshold) अणु
		hpd->stats[pin].state = HPD_MARK_DISABLED;
		drm_dbg_kms(&dev_priv->drm,
			    "HPD interrupt storm detected on PIN %d\n", pin);
		storm = true;
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Received HPD interrupt on PIN %d - cnt: %d\n",
			      pin,
			      hpd->stats[pin].count);
	पूर्ण

	वापस storm;
पूर्ण

अटल व्योम
पूर्णांकel_hpd_irq_storm_चयन_to_polling(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा पूर्णांकel_connector *connector;
	bool hpd_disabled = false;

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	drm_connector_list_iter_begin(dev, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		क्रमागत hpd_pin pin;

		अगर (connector->base.polled != DRM_CONNECTOR_POLL_HPD)
			जारी;

		pin = पूर्णांकel_connector_hpd_pin(connector);
		अगर (pin == HPD_NONE ||
		    dev_priv->hotplug.stats[pin].state != HPD_MARK_DISABLED)
			जारी;

		drm_info(&dev_priv->drm,
			 "HPD interrupt storm detected on connector %s: "
			 "switching from hotplug detection to polling\n",
			 connector->base.name);

		dev_priv->hotplug.stats[pin].state = HPD_DISABLED;
		connector->base.polled = DRM_CONNECTOR_POLL_CONNECT |
			DRM_CONNECTOR_POLL_DISCONNECT;
		hpd_disabled = true;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	/* Enable polling and queue hotplug re-enabling. */
	अगर (hpd_disabled) अणु
		drm_kms_helper_poll_enable(dev);
		mod_delayed_work(प्रणाली_wq, &dev_priv->hotplug.reenable_work,
				 msecs_to_jअगरfies(HPD_STORM_REENABLE_DELAY));
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_hpd_irq_setup(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (i915->display_irqs_enabled && i915->display.hpd_irq_setup)
		i915->display.hpd_irq_setup(i915);
पूर्ण

अटल व्योम पूर्णांकel_hpd_irq_storm_reenable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		container_of(work, typeof(*dev_priv),
			     hotplug.reenable_work.work);
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा पूर्णांकel_connector *connector;
	पूर्णांकel_wakeref_t wakeref;
	क्रमागत hpd_pin pin;

	wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);

	spin_lock_irq(&dev_priv->irq_lock);

	drm_connector_list_iter_begin(dev, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		pin = पूर्णांकel_connector_hpd_pin(connector);
		अगर (pin == HPD_NONE ||
		    dev_priv->hotplug.stats[pin].state != HPD_DISABLED)
			जारी;

		अगर (connector->base.polled != connector->polled)
			drm_dbg(&dev_priv->drm,
				"Reenabling HPD on connector %s\n",
				connector->base.name);
		connector->base.polled = connector->polled;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	क्रम_each_hpd_pin(pin) अणु
		अगर (dev_priv->hotplug.stats[pin].state == HPD_DISABLED)
			dev_priv->hotplug.stats[pin].state = HPD_ENABLED;
	पूर्ण

	पूर्णांकel_hpd_irq_setup(dev_priv);

	spin_unlock_irq(&dev_priv->irq_lock);

	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);
पूर्ण

क्रमागत पूर्णांकel_hotplug_state
पूर्णांकel_encoder_hotplug(काष्ठा पूर्णांकel_encoder *encoder,
		      काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->base.dev;
	क्रमागत drm_connector_status old_status;
	u64 old_epoch_counter;
	bool ret = false;

	drm_WARN_ON(dev, !mutex_is_locked(&dev->mode_config.mutex));
	old_status = connector->base.status;
	old_epoch_counter = connector->base.epoch_counter;

	connector->base.status =
		drm_helper_probe_detect(&connector->base, शून्य, false);

	अगर (old_epoch_counter != connector->base.epoch_counter)
		ret = true;

	अगर (ret) अणु
		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] status updated from %s to %s (epoch counter %llu->%llu)\n",
			      connector->base.base.id,
			      connector->base.name,
			      drm_get_connector_status_name(old_status),
			      drm_get_connector_status_name(connector->base.status),
			      old_epoch_counter,
			      connector->base.epoch_counter);
		वापस INTEL_HOTPLUG_CHANGED;
	पूर्ण
	वापस INTEL_HOTPLUG_UNCHANGED;
पूर्ण

अटल bool पूर्णांकel_encoder_has_hpd_pulse(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस पूर्णांकel_encoder_is_dig_port(encoder) &&
		enc_to_dig_port(encoder)->hpd_pulse != शून्य;
पूर्ण

अटल व्योम i915_digport_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		container_of(work, काष्ठा drm_i915_निजी, hotplug.dig_port_work);
	u32 दीर्घ_port_mask, लघु_port_mask;
	काष्ठा पूर्णांकel_encoder *encoder;
	u32 old_bits = 0;

	spin_lock_irq(&dev_priv->irq_lock);
	दीर्घ_port_mask = dev_priv->hotplug.दीर्घ_port_mask;
	dev_priv->hotplug.दीर्घ_port_mask = 0;
	लघु_port_mask = dev_priv->hotplug.लघु_port_mask;
	dev_priv->hotplug.लघु_port_mask = 0;
	spin_unlock_irq(&dev_priv->irq_lock);

	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		काष्ठा पूर्णांकel_digital_port *dig_port;
		क्रमागत port port = encoder->port;
		bool दीर्घ_hpd, लघु_hpd;
		क्रमागत irqवापस ret;

		अगर (!पूर्णांकel_encoder_has_hpd_pulse(encoder))
			जारी;

		दीर्घ_hpd = दीर्घ_port_mask & BIT(port);
		लघु_hpd = लघु_port_mask & BIT(port);

		अगर (!दीर्घ_hpd && !लघु_hpd)
			जारी;

		dig_port = enc_to_dig_port(encoder);

		ret = dig_port->hpd_pulse(dig_port, दीर्घ_hpd);
		अगर (ret == IRQ_NONE) अणु
			/* fall back to old school hpd */
			old_bits |= BIT(encoder->hpd_pin);
		पूर्ण
	पूर्ण

	अगर (old_bits) अणु
		spin_lock_irq(&dev_priv->irq_lock);
		dev_priv->hotplug.event_bits |= old_bits;
		spin_unlock_irq(&dev_priv->irq_lock);
		queue_delayed_work(प्रणाली_wq, &dev_priv->hotplug.hotplug_work, 0);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_hpd_trigger_irq - trigger an hpd irq event क्रम a port
 * @dig_port: digital port
 *
 * Trigger an HPD पूर्णांकerrupt event क्रम the given port, emulating a लघु pulse
 * generated by the sink, and schedule the dig port work to handle it.
 */
व्योम पूर्णांकel_hpd_trigger_irq(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);

	spin_lock_irq(&i915->irq_lock);
	i915->hotplug.लघु_port_mask |= BIT(dig_port->base.port);
	spin_unlock_irq(&i915->irq_lock);

	queue_work(i915->hotplug.dp_wq, &i915->hotplug.dig_port_work);
पूर्ण

/*
 * Handle hotplug events outside the पूर्णांकerrupt handler proper.
 */
अटल व्योम i915_hotplug_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		container_of(work, काष्ठा drm_i915_निजी,
			     hotplug.hotplug_work.work);
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा पूर्णांकel_connector *connector;
	u32 changed = 0, retry = 0;
	u32 hpd_event_bits;
	u32 hpd_retry_bits;

	mutex_lock(&dev->mode_config.mutex);
	drm_dbg_kms(&dev_priv->drm, "running encoder hotplug functions\n");

	spin_lock_irq(&dev_priv->irq_lock);

	hpd_event_bits = dev_priv->hotplug.event_bits;
	dev_priv->hotplug.event_bits = 0;
	hpd_retry_bits = dev_priv->hotplug.retry_bits;
	dev_priv->hotplug.retry_bits = 0;

	/* Enable polling क्रम connectors which had HPD IRQ storms */
	पूर्णांकel_hpd_irq_storm_चयन_to_polling(dev_priv);

	spin_unlock_irq(&dev_priv->irq_lock);

	drm_connector_list_iter_begin(dev, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		क्रमागत hpd_pin pin;
		u32 hpd_bit;

		pin = पूर्णांकel_connector_hpd_pin(connector);
		अगर (pin == HPD_NONE)
			जारी;

		hpd_bit = BIT(pin);
		अगर ((hpd_event_bits | hpd_retry_bits) & hpd_bit) अणु
			काष्ठा पूर्णांकel_encoder *encoder =
				पूर्णांकel_attached_encoder(connector);

			अगर (hpd_event_bits & hpd_bit)
				connector->hotplug_retries = 0;
			अन्यथा
				connector->hotplug_retries++;

			drm_dbg_kms(&dev_priv->drm,
				    "Connector %s (pin %i) received hotplug event. (retry %d)\n",
				    connector->base.name, pin,
				    connector->hotplug_retries);

			चयन (encoder->hotplug(encoder, connector)) अणु
			हाल INTEL_HOTPLUG_UNCHANGED:
				अवरोध;
			हाल INTEL_HOTPLUG_CHANGED:
				changed |= hpd_bit;
				अवरोध;
			हाल INTEL_HOTPLUG_RETRY:
				retry |= hpd_bit;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);
	mutex_unlock(&dev->mode_config.mutex);

	अगर (changed)
		drm_kms_helper_hotplug_event(dev);

	/* Remove shared HPD pins that have changed */
	retry &= ~changed;
	अगर (retry) अणु
		spin_lock_irq(&dev_priv->irq_lock);
		dev_priv->hotplug.retry_bits |= retry;
		spin_unlock_irq(&dev_priv->irq_lock);

		mod_delayed_work(प्रणाली_wq, &dev_priv->hotplug.hotplug_work,
				 msecs_to_jअगरfies(HPD_RETRY_DELAY));
	पूर्ण
पूर्ण


/**
 * पूर्णांकel_hpd_irq_handler - मुख्य hotplug irq handler
 * @dev_priv: drm_i915_निजी
 * @pin_mask: a mask of hpd pins that have triggered the irq
 * @दीर्घ_mask: a mask of hpd pins that may be दीर्घ hpd pulses
 *
 * This is the मुख्य hotplug irq handler क्रम all platक्रमms. The platक्रमm specअगरic
 * irq handlers call the platक्रमm specअगरic hotplug irq handlers, which पढ़ो and
 * decode the appropriate रेजिस्टरs पूर्णांकo biपंचांगasks about hpd pins that have
 * triggered (@pin_mask), and which of those pins may be दीर्घ pulses
 * (@दीर्घ_mask). The @दीर्घ_mask is ignored अगर the port corresponding to the pin
 * is not a digital port.
 *
 * Here, we करो hotplug irq storm detection and mitigation, and pass further
 * processing to appropriate bottom halves.
 */
व्योम पूर्णांकel_hpd_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
			   u32 pin_mask, u32 दीर्घ_mask)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;
	bool storm_detected = false;
	bool queue_dig = false, queue_hp = false;
	u32 दीर्घ_hpd_pulse_mask = 0;
	u32 लघु_hpd_pulse_mask = 0;
	क्रमागत hpd_pin pin;

	अगर (!pin_mask)
		वापस;

	spin_lock(&dev_priv->irq_lock);

	/*
	 * Determine whether ->hpd_pulse() exists क्रम each pin, and
	 * whether we have a लघु or a दीर्घ pulse. This is needed
	 * as each pin may have up to two encoders (HDMI and DP) and
	 * only the one of them (DP) will have ->hpd_pulse().
	 */
	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		क्रमागत port port = encoder->port;
		bool दीर्घ_hpd;

		pin = encoder->hpd_pin;
		अगर (!(BIT(pin) & pin_mask))
			जारी;

		अगर (!पूर्णांकel_encoder_has_hpd_pulse(encoder))
			जारी;

		दीर्घ_hpd = दीर्घ_mask & BIT(pin);

		drm_dbg(&dev_priv->drm,
			"digital hpd on [ENCODER:%d:%s] - %s\n",
			encoder->base.base.id, encoder->base.name,
			दीर्घ_hpd ? "long" : "short");
		queue_dig = true;

		अगर (दीर्घ_hpd) अणु
			दीर्घ_hpd_pulse_mask |= BIT(pin);
			dev_priv->hotplug.दीर्घ_port_mask |= BIT(port);
		पूर्ण अन्यथा अणु
			लघु_hpd_pulse_mask |= BIT(pin);
			dev_priv->hotplug.लघु_port_mask |= BIT(port);
		पूर्ण
	पूर्ण

	/* Now process each pin just once */
	क्रम_each_hpd_pin(pin) अणु
		bool दीर्घ_hpd;

		अगर (!(BIT(pin) & pin_mask))
			जारी;

		अगर (dev_priv->hotplug.stats[pin].state == HPD_DISABLED) अणु
			/*
			 * On GMCH platक्रमms the पूर्णांकerrupt mask bits only
			 * prevent irq generation, not the setting of the
			 * hotplug bits itself. So only WARN about unexpected
			 * पूर्णांकerrupts on saner platक्रमms.
			 */
			drm_WARN_ONCE(&dev_priv->drm, !HAS_GMCH(dev_priv),
				      "Received HPD interrupt on pin %d although disabled\n",
				      pin);
			जारी;
		पूर्ण

		अगर (dev_priv->hotplug.stats[pin].state != HPD_ENABLED)
			जारी;

		/*
		 * Delegate to ->hpd_pulse() अगर one of the encoders क्रम this
		 * pin has it, otherwise let the hotplug_work deal with this
		 * pin directly.
		 */
		अगर (((लघु_hpd_pulse_mask | दीर्घ_hpd_pulse_mask) & BIT(pin))) अणु
			दीर्घ_hpd = दीर्घ_hpd_pulse_mask & BIT(pin);
		पूर्ण अन्यथा अणु
			dev_priv->hotplug.event_bits |= BIT(pin);
			दीर्घ_hpd = true;
			queue_hp = true;
		पूर्ण

		अगर (पूर्णांकel_hpd_irq_storm_detect(dev_priv, pin, दीर्घ_hpd)) अणु
			dev_priv->hotplug.event_bits &= ~BIT(pin);
			storm_detected = true;
			queue_hp = true;
		पूर्ण
	पूर्ण

	/*
	 * Disable any IRQs that storms were detected on. Polling enablement
	 * happens later in our hotplug work.
	 */
	अगर (storm_detected)
		पूर्णांकel_hpd_irq_setup(dev_priv);
	spin_unlock(&dev_priv->irq_lock);

	/*
	 * Our hotplug handler can grab modeset locks (by calling करोwn पूर्णांकo the
	 * fb helpers). Hence it must not be run on our own dev-priv->wq work
	 * queue क्रम otherwise the flush_work in the pageflip code will
	 * deadlock.
	 */
	अगर (queue_dig)
		queue_work(dev_priv->hotplug.dp_wq, &dev_priv->hotplug.dig_port_work);
	अगर (queue_hp)
		queue_delayed_work(प्रणाली_wq, &dev_priv->hotplug.hotplug_work, 0);
पूर्ण

/**
 * पूर्णांकel_hpd_init - initializes and enables hpd support
 * @dev_priv: i915 device instance
 *
 * This function enables the hotplug support. It requires that पूर्णांकerrupts have
 * alपढ़ोy been enabled with पूर्णांकel_irq_init_hw(). From this poपूर्णांक on hotplug and
 * poll request can run concurrently to other code, so locking rules must be
 * obeyed.
 *
 * This is a separate step from पूर्णांकerrupt enabling to simplअगरy the locking rules
 * in the driver load and resume code.
 *
 * Also see: पूर्णांकel_hpd_poll_enable() and पूर्णांकel_hpd_poll_disable().
 */
व्योम पूर्णांकel_hpd_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक i;

	क्रम_each_hpd_pin(i) अणु
		dev_priv->hotplug.stats[i].count = 0;
		dev_priv->hotplug.stats[i].state = HPD_ENABLED;
	पूर्ण

	/*
	 * Interrupt setup is alपढ़ोy guaranteed to be single-thपढ़ोed, this is
	 * just to make the निश्चित_spin_locked checks happy.
	 */
	spin_lock_irq(&dev_priv->irq_lock);
	पूर्णांकel_hpd_irq_setup(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);
पूर्ण

अटल व्योम i915_hpd_poll_init_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		container_of(work, काष्ठा drm_i915_निजी,
			     hotplug.poll_init_work);
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा पूर्णांकel_connector *connector;
	bool enabled;

	mutex_lock(&dev->mode_config.mutex);

	enabled = READ_ONCE(dev_priv->hotplug.poll_enabled);

	drm_connector_list_iter_begin(dev, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		क्रमागत hpd_pin pin;

		pin = पूर्णांकel_connector_hpd_pin(connector);
		अगर (pin == HPD_NONE)
			जारी;

		connector->base.polled = connector->polled;

		अगर (enabled && connector->base.polled == DRM_CONNECTOR_POLL_HPD)
			connector->base.polled = DRM_CONNECTOR_POLL_CONNECT |
				DRM_CONNECTOR_POLL_DISCONNECT;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	अगर (enabled)
		drm_kms_helper_poll_enable(dev);

	mutex_unlock(&dev->mode_config.mutex);

	/*
	 * We might have missed any hotplugs that happened जबतक we were
	 * in the middle of disabling polling
	 */
	अगर (!enabled)
		drm_helper_hpd_irq_event(dev);
पूर्ण

/**
 * पूर्णांकel_hpd_poll_enable - enable polling क्रम connectors with hpd
 * @dev_priv: i915 device instance
 *
 * This function enables polling क्रम all connectors which support HPD.
 * Under certain conditions HPD may not be functional. On most Intel GPUs,
 * this happens when we enter runसमय suspend.
 * On Valleyview and Cherryview प्रणालीs, this also happens when we shut off all
 * of the घातerwells.
 *
 * Since this function can get called in contexts where we're alपढ़ोy holding
 * dev->mode_config.mutex, we करो the actual hotplug enabling in a seperate
 * worker.
 *
 * Also see: पूर्णांकel_hpd_init() and पूर्णांकel_hpd_poll_disable().
 */
व्योम पूर्णांकel_hpd_poll_enable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	WRITE_ONCE(dev_priv->hotplug.poll_enabled, true);

	/*
	 * We might alपढ़ोy be holding dev->mode_config.mutex, so करो this in a
	 * seperate worker
	 * As well, there's no issue अगर we race here since we always reschedule
	 * this worker anyway
	 */
	schedule_work(&dev_priv->hotplug.poll_init_work);
पूर्ण

/**
 * पूर्णांकel_hpd_poll_disable - disable polling क्रम connectors with hpd
 * @dev_priv: i915 device instance
 *
 * This function disables polling क्रम all connectors which support HPD.
 * Under certain conditions HPD may not be functional. On most Intel GPUs,
 * this happens when we enter runसमय suspend.
 * On Valleyview and Cherryview प्रणालीs, this also happens when we shut off all
 * of the घातerwells.
 *
 * Since this function can get called in contexts where we're alपढ़ोy holding
 * dev->mode_config.mutex, we करो the actual hotplug enabling in a seperate
 * worker.
 *
 * Also used during driver init to initialize connector->polled
 * appropriately क्रम all connectors.
 *
 * Also see: पूर्णांकel_hpd_init() and पूर्णांकel_hpd_poll_enable().
 */
व्योम पूर्णांकel_hpd_poll_disable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	WRITE_ONCE(dev_priv->hotplug.poll_enabled, false);
	schedule_work(&dev_priv->hotplug.poll_init_work);
पूर्ण

व्योम पूर्णांकel_hpd_init_work(काष्ठा drm_i915_निजी *dev_priv)
अणु
	INIT_DELAYED_WORK(&dev_priv->hotplug.hotplug_work,
			  i915_hotplug_work_func);
	INIT_WORK(&dev_priv->hotplug.dig_port_work, i915_digport_work_func);
	INIT_WORK(&dev_priv->hotplug.poll_init_work, i915_hpd_poll_init_work);
	INIT_DELAYED_WORK(&dev_priv->hotplug.reenable_work,
			  पूर्णांकel_hpd_irq_storm_reenable_work);
पूर्ण

व्योम पूर्णांकel_hpd_cancel_work(काष्ठा drm_i915_निजी *dev_priv)
अणु
	spin_lock_irq(&dev_priv->irq_lock);

	dev_priv->hotplug.दीर्घ_port_mask = 0;
	dev_priv->hotplug.लघु_port_mask = 0;
	dev_priv->hotplug.event_bits = 0;
	dev_priv->hotplug.retry_bits = 0;

	spin_unlock_irq(&dev_priv->irq_lock);

	cancel_work_sync(&dev_priv->hotplug.dig_port_work);
	cancel_delayed_work_sync(&dev_priv->hotplug.hotplug_work);
	cancel_work_sync(&dev_priv->hotplug.poll_init_work);
	cancel_delayed_work_sync(&dev_priv->hotplug.reenable_work);
पूर्ण

bool पूर्णांकel_hpd_disable(काष्ठा drm_i915_निजी *dev_priv, क्रमागत hpd_pin pin)
अणु
	bool ret = false;

	अगर (pin == HPD_NONE)
		वापस false;

	spin_lock_irq(&dev_priv->irq_lock);
	अगर (dev_priv->hotplug.stats[pin].state == HPD_ENABLED) अणु
		dev_priv->hotplug.stats[pin].state = HPD_DISABLED;
		ret = true;
	पूर्ण
	spin_unlock_irq(&dev_priv->irq_lock);

	वापस ret;
पूर्ण

व्योम पूर्णांकel_hpd_enable(काष्ठा drm_i915_निजी *dev_priv, क्रमागत hpd_pin pin)
अणु
	अगर (pin == HPD_NONE)
		वापस;

	spin_lock_irq(&dev_priv->irq_lock);
	dev_priv->hotplug.stats[pin].state = HPD_ENABLED;
	spin_unlock_irq(&dev_priv->irq_lock);
पूर्ण
