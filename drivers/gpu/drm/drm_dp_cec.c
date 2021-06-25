<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DisplayPort CEC-Tunneling-over-AUX support
 *
 * Copyright 2018 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <media/cec.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_dp_helper.h>

/*
 * Unक्रमtunately it turns out that we have a chicken-and-egg situation
 * here. Quite a few active (mini-)DP-to-HDMI or USB-C-to-HDMI adapters
 * have a converter chip that supports CEC-Tunneling-over-AUX (usually the
 * Parade PS176), but they करो not wire up the CEC pin, thus making CEC
 * useless. Note that MegaChips 2900-based adapters appear to have good
 * support क्रम CEC tunneling. Those adapters that I have tested using
 * this chipset all have the CEC line connected.
 *
 * Sadly there is no way क्रम this driver to know this. What happens is
 * that a /dev/cecX device is created that is isolated and unable to see
 * any of the other CEC devices. Quite literally the CEC wire is cut
 * (or in this हाल, never connected in the first place).
 *
 * The reason so few adapters support this is that this tunneling protocol
 * was never supported by any OS. So there was no easy way of testing it,
 * and no incentive to correctly wire up the CEC pin.
 *
 * Hopefully by creating this driver it will be easier क्रम venकरोrs to
 * finally fix their adapters and test the CEC functionality.
 *
 * I keep a list of known working adapters here:
 *
 * https://hverkuil.home.xs4all.nl/cec-status.txt
 *
 * Please mail me (hverkuil@xs4all.nl) अगर you find an adapter that works
 * and is not yet listed there.
 *
 * Note that the current implementation करोes not support CEC over an MST hub.
 * As far as I can see there is no mechanism defined in the DisplayPort
 * standard to transport CEC पूर्णांकerrupts over an MST device. It might be
 * possible to करो this through polling, but I have not been able to get that
 * to work.
 */

/**
 * DOC: dp cec helpers
 *
 * These functions take care of supporting the CEC-Tunneling-over-AUX
 * feature of DisplayPort-to-HDMI adapters.
 */

/*
 * When the EDID is unset because the HPD went low, then the CEC DPCD रेजिस्टरs
 * typically can no दीर्घer be पढ़ो (true क्रम a DP-to-HDMI adapter since it is
 * घातered by the HPD). However, some displays toggle the HPD off and on क्रम a
 * लघु period क्रम one reason or another, and that would cause the CEC adapter
 * to be हटाओd and added again, even though nothing अन्यथा changed.
 *
 * This module parameter sets a delay in seconds beक्रमe the CEC adapter is
 * actually unरेजिस्टरed. Only अगर the HPD करोes not वापस within that समय will
 * the CEC adapter be unरेजिस्टरed.
 *
 * If it is set to a value >= NEVER_UNREG_DELAY, then the CEC adapter will never
 * be unरेजिस्टरed क्रम as दीर्घ as the connector reमुख्यs रेजिस्टरed.
 *
 * If it is set to 0, then the CEC adapter will be unरेजिस्टरed immediately as
 * soon as the HPD disappears.
 *
 * The शेष is one second to prevent लघु HPD glitches from unरेजिस्टरing
 * the CEC adapter.
 *
 * Note that क्रम पूर्णांकegrated HDMI branch devices that support CEC the DPCD
 * रेजिस्टरs reमुख्य available even अगर the HPD goes low since it is not घातered
 * by the HPD. In that हाल the CEC adapter will never be unरेजिस्टरed during
 * the lअगरe समय of the connector. At least, this is the theory since I करो not
 * have hardware with an पूर्णांकegrated HDMI branch device that supports CEC.
 */
#घोषणा NEVER_UNREG_DELAY 1000
अटल अचिन्हित पूर्णांक drm_dp_cec_unरेजिस्टर_delay = 1;
module_param(drm_dp_cec_unरेजिस्टर_delay, uपूर्णांक, 0600);
MODULE_PARM_DESC(drm_dp_cec_unरेजिस्टर_delay,
		 "CEC unregister delay in seconds, 0: no delay, >= 1000: never unregister");

अटल पूर्णांक drm_dp_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा drm_dp_aux *aux = cec_get_drvdata(adap);
	u32 val = enable ? DP_CEC_TUNNELING_ENABLE : 0;
	sमाप_प्रकार err = 0;

	err = drm_dp_dpcd_ग_लिखोb(aux, DP_CEC_TUNNELING_CONTROL, val);
	वापस (enable && err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक drm_dp_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 addr)
अणु
	काष्ठा drm_dp_aux *aux = cec_get_drvdata(adap);
	/* Bit 15 (logical address 15) should always be set */
	u16 la_mask = 1 << CEC_LOG_ADDR_BROADCAST;
	u8 mask[2];
	sमाप_प्रकार err;

	अगर (addr != CEC_LOG_ADDR_INVALID)
		la_mask |= adap->log_addrs.log_addr_mask | (1 << addr);
	mask[0] = la_mask & 0xff;
	mask[1] = la_mask >> 8;
	err = drm_dp_dpcd_ग_लिखो(aux, DP_CEC_LOGICAL_ADDRESS_MASK, mask, 2);
	वापस (addr != CEC_LOG_ADDR_INVALID && err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक drm_dp_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				    u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा drm_dp_aux *aux = cec_get_drvdata(adap);
	अचिन्हित पूर्णांक retries = min(5, attempts - 1);
	sमाप_प्रकार err;

	err = drm_dp_dpcd_ग_लिखो(aux, DP_CEC_TX_MESSAGE_BUFFER,
				msg->msg, msg->len);
	अगर (err < 0)
		वापस err;

	err = drm_dp_dpcd_ग_लिखोb(aux, DP_CEC_TX_MESSAGE_INFO,
				 (msg->len - 1) | (retries << 4) |
				 DP_CEC_TX_MESSAGE_SEND);
	वापस err < 0 ? err : 0;
पूर्ण

अटल पूर्णांक drm_dp_cec_adap_monitor_all_enable(काष्ठा cec_adapter *adap,
					      bool enable)
अणु
	काष्ठा drm_dp_aux *aux = cec_get_drvdata(adap);
	sमाप_प्रकार err;
	u8 val;

	अगर (!(adap->capabilities & CEC_CAP_MONITOR_ALL))
		वापस 0;

	err = drm_dp_dpcd_पढ़ोb(aux, DP_CEC_TUNNELING_CONTROL, &val);
	अगर (err >= 0) अणु
		अगर (enable)
			val |= DP_CEC_SNOOPING_ENABLE;
		अन्यथा
			val &= ~DP_CEC_SNOOPING_ENABLE;
		err = drm_dp_dpcd_ग_लिखोb(aux, DP_CEC_TUNNELING_CONTROL, val);
	पूर्ण
	वापस (enable && err < 0) ? err : 0;
पूर्ण

अटल व्योम drm_dp_cec_adap_status(काष्ठा cec_adapter *adap,
				   काष्ठा seq_file *file)
अणु
	काष्ठा drm_dp_aux *aux = cec_get_drvdata(adap);
	काष्ठा drm_dp_desc desc;
	काष्ठा drm_dp_dpcd_ident *id = &desc.ident;

	अगर (drm_dp_पढ़ो_desc(aux, &desc, true))
		वापस;
	seq_म_लिखो(file, "OUI: %*phD\n",
		   (पूर्णांक)माप(id->oui), id->oui);
	seq_म_लिखो(file, "ID: %*pE\n",
		   (पूर्णांक)strnlen(id->device_id, माप(id->device_id)),
		   id->device_id);
	seq_म_लिखो(file, "HW Rev: %d.%d\n", id->hw_rev >> 4, id->hw_rev & 0xf);
	/*
	 * Show this both in decimal and hex: at least one venकरोr
	 * always reports this in hex.
	 */
	seq_म_लिखो(file, "FW/SW Rev: %d.%d (0x%02x.0x%02x)\n",
		   id->sw_major_rev, id->sw_minor_rev,
		   id->sw_major_rev, id->sw_minor_rev);
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops drm_dp_cec_adap_ops = अणु
	.adap_enable = drm_dp_cec_adap_enable,
	.adap_log_addr = drm_dp_cec_adap_log_addr,
	.adap_transmit = drm_dp_cec_adap_transmit,
	.adap_monitor_all_enable = drm_dp_cec_adap_monitor_all_enable,
	.adap_status = drm_dp_cec_adap_status,
पूर्ण;

अटल पूर्णांक drm_dp_cec_received(काष्ठा drm_dp_aux *aux)
अणु
	काष्ठा cec_adapter *adap = aux->cec.adap;
	काष्ठा cec_msg msg;
	u8 rx_msg_info;
	sमाप_प्रकार err;

	err = drm_dp_dpcd_पढ़ोb(aux, DP_CEC_RX_MESSAGE_INFO, &rx_msg_info);
	अगर (err < 0)
		वापस err;

	अगर (!(rx_msg_info & DP_CEC_RX_MESSAGE_ENDED))
		वापस 0;

	msg.len = (rx_msg_info & DP_CEC_RX_MESSAGE_LEN_MASK) + 1;
	err = drm_dp_dpcd_पढ़ो(aux, DP_CEC_RX_MESSAGE_BUFFER, msg.msg, msg.len);
	अगर (err < 0)
		वापस err;

	cec_received_msg(adap, &msg);
	वापस 0;
पूर्ण

अटल व्योम drm_dp_cec_handle_irq(काष्ठा drm_dp_aux *aux)
अणु
	काष्ठा cec_adapter *adap = aux->cec.adap;
	u8 flags;

	अगर (drm_dp_dpcd_पढ़ोb(aux, DP_CEC_TUNNELING_IRQ_FLAGS, &flags) < 0)
		वापस;

	अगर (flags & DP_CEC_RX_MESSAGE_INFO_VALID)
		drm_dp_cec_received(aux);

	अगर (flags & DP_CEC_TX_MESSAGE_SENT)
		cec_transmit_attempt_करोne(adap, CEC_TX_STATUS_OK);
	अन्यथा अगर (flags & DP_CEC_TX_LINE_ERROR)
		cec_transmit_attempt_करोne(adap, CEC_TX_STATUS_ERROR |
						CEC_TX_STATUS_MAX_RETRIES);
	अन्यथा अगर (flags &
		 (DP_CEC_TX_ADDRESS_NACK_ERROR | DP_CEC_TX_DATA_NACK_ERROR))
		cec_transmit_attempt_करोne(adap, CEC_TX_STATUS_NACK |
						CEC_TX_STATUS_MAX_RETRIES);
	drm_dp_dpcd_ग_लिखोb(aux, DP_CEC_TUNNELING_IRQ_FLAGS, flags);
पूर्ण

/**
 * drm_dp_cec_irq() - handle CEC पूर्णांकerrupt, अगर any
 * @aux: DisplayPort AUX channel
 *
 * Should be called when handling an IRQ_HPD request. If CEC-tunneling-over-AUX
 * is present, then it will check क्रम a CEC_IRQ and handle it accordingly.
 */
व्योम drm_dp_cec_irq(काष्ठा drm_dp_aux *aux)
अणु
	u8 cec_irq;
	पूर्णांक ret;

	/* No transfer function was set, so not a DP connector */
	अगर (!aux->transfer)
		वापस;

	mutex_lock(&aux->cec.lock);
	अगर (!aux->cec.adap)
		जाओ unlock;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_DEVICE_SERVICE_IRQ_VECTOR_ESI1,
				&cec_irq);
	अगर (ret < 0 || !(cec_irq & DP_CEC_IRQ))
		जाओ unlock;

	drm_dp_cec_handle_irq(aux);
	drm_dp_dpcd_ग_लिखोb(aux, DP_DEVICE_SERVICE_IRQ_VECTOR_ESI1, DP_CEC_IRQ);
unlock:
	mutex_unlock(&aux->cec.lock);
पूर्ण
EXPORT_SYMBOL(drm_dp_cec_irq);

अटल bool drm_dp_cec_cap(काष्ठा drm_dp_aux *aux, u8 *cec_cap)
अणु
	u8 cap = 0;

	अगर (drm_dp_dpcd_पढ़ोb(aux, DP_CEC_TUNNELING_CAPABILITY, &cap) != 1 ||
	    !(cap & DP_CEC_TUNNELING_CAPABLE))
		वापस false;
	अगर (cec_cap)
		*cec_cap = cap;
	वापस true;
पूर्ण

/*
 * Called अगर the HPD was low क्रम more than drm_dp_cec_unरेजिस्टर_delay
 * seconds. This unरेजिस्टरs the CEC adapter.
 */
अटल व्योम drm_dp_cec_unरेजिस्टर_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_dp_aux *aux = container_of(work, काष्ठा drm_dp_aux,
					      cec.unरेजिस्टर_work.work);

	mutex_lock(&aux->cec.lock);
	cec_unरेजिस्टर_adapter(aux->cec.adap);
	aux->cec.adap = शून्य;
	mutex_unlock(&aux->cec.lock);
पूर्ण

/*
 * A new EDID is set. If there is no CEC adapter, then create one. If
 * there was a CEC adapter, then check अगर the CEC adapter properties
 * were unchanged and just update the CEC physical address. Otherwise
 * unरेजिस्टर the old CEC adapter and create a new one.
 */
व्योम drm_dp_cec_set_edid(काष्ठा drm_dp_aux *aux, स्थिर काष्ठा edid *edid)
अणु
	काष्ठा drm_connector *connector = aux->cec.connector;
	u32 cec_caps = CEC_CAP_DEFAULTS | CEC_CAP_NEEDS_HPD |
		       CEC_CAP_CONNECTOR_INFO;
	काष्ठा cec_connector_info conn_info;
	अचिन्हित पूर्णांक num_las = 1;
	u8 cap;

	/* No transfer function was set, so not a DP connector */
	अगर (!aux->transfer)
		वापस;

#अगर_अघोषित CONFIG_MEDIA_CEC_RC
	/*
	 * CEC_CAP_RC is part of CEC_CAP_DEFAULTS, but it is stripped by
	 * cec_allocate_adapter() अगर CONFIG_MEDIA_CEC_RC is undefined.
	 *
	 * Do this here as well to ensure the tests against cec_caps are
	 * correct.
	 */
	cec_caps &= ~CEC_CAP_RC;
#पूर्ण_अगर
	cancel_delayed_work_sync(&aux->cec.unरेजिस्टर_work);

	mutex_lock(&aux->cec.lock);
	अगर (!drm_dp_cec_cap(aux, &cap)) अणु
		/* CEC is not supported, unरेजिस्टर any existing adapter */
		cec_unरेजिस्टर_adapter(aux->cec.adap);
		aux->cec.adap = शून्य;
		जाओ unlock;
	पूर्ण

	अगर (cap & DP_CEC_SNOOPING_CAPABLE)
		cec_caps |= CEC_CAP_MONITOR_ALL;
	अगर (cap & DP_CEC_MULTIPLE_LA_CAPABLE)
		num_las = CEC_MAX_LOG_ADDRS;

	अगर (aux->cec.adap) अणु
		अगर (aux->cec.adap->capabilities == cec_caps &&
		    aux->cec.adap->available_log_addrs == num_las) अणु
			/* Unchanged, so just set the phys addr */
			cec_s_phys_addr_from_edid(aux->cec.adap, edid);
			जाओ unlock;
		पूर्ण
		/*
		 * The capabilities changed, so unरेजिस्टर the old
		 * adapter first.
		 */
		cec_unरेजिस्टर_adapter(aux->cec.adap);
	पूर्ण

	/* Create a new adapter */
	aux->cec.adap = cec_allocate_adapter(&drm_dp_cec_adap_ops,
					     aux, connector->name, cec_caps,
					     num_las);
	अगर (IS_ERR(aux->cec.adap)) अणु
		aux->cec.adap = शून्य;
		जाओ unlock;
	पूर्ण

	cec_fill_conn_info_from_drm(&conn_info, connector);
	cec_s_conn_info(aux->cec.adap, &conn_info);

	अगर (cec_रेजिस्टर_adapter(aux->cec.adap, connector->dev->dev)) अणु
		cec_delete_adapter(aux->cec.adap);
		aux->cec.adap = शून्य;
	पूर्ण अन्यथा अणु
		/*
		 * Update the phys addr क्रम the new CEC adapter. When called
		 * from drm_dp_cec_रेजिस्टर_connector() edid == शून्य, so in
		 * that हाल the phys addr is just invalidated.
		 */
		cec_s_phys_addr_from_edid(aux->cec.adap, edid);
	पूर्ण
unlock:
	mutex_unlock(&aux->cec.lock);
पूर्ण
EXPORT_SYMBOL(drm_dp_cec_set_edid);

/*
 * The EDID disappeared (likely because of the HPD going करोwn).
 */
व्योम drm_dp_cec_unset_edid(काष्ठा drm_dp_aux *aux)
अणु
	/* No transfer function was set, so not a DP connector */
	अगर (!aux->transfer)
		वापस;

	cancel_delayed_work_sync(&aux->cec.unरेजिस्टर_work);

	mutex_lock(&aux->cec.lock);
	अगर (!aux->cec.adap)
		जाओ unlock;

	cec_phys_addr_invalidate(aux->cec.adap);
	/*
	 * We're करोne अगर we want to keep the CEC device
	 * (drm_dp_cec_unरेजिस्टर_delay is >= NEVER_UNREG_DELAY) or अगर the
	 * DPCD still indicates the CEC capability (expected क्रम an पूर्णांकegrated
	 * HDMI branch device).
	 */
	अगर (drm_dp_cec_unरेजिस्टर_delay < NEVER_UNREG_DELAY &&
	    !drm_dp_cec_cap(aux, शून्य)) अणु
		/*
		 * Unरेजिस्टर the CEC adapter after drm_dp_cec_unरेजिस्टर_delay
		 * seconds. This to debounce लघु HPD off-and-on cycles from
		 * displays.
		 */
		schedule_delayed_work(&aux->cec.unरेजिस्टर_work,
				      drm_dp_cec_unरेजिस्टर_delay * HZ);
	पूर्ण
unlock:
	mutex_unlock(&aux->cec.lock);
पूर्ण
EXPORT_SYMBOL(drm_dp_cec_unset_edid);

/**
 * drm_dp_cec_रेजिस्टर_connector() - रेजिस्टर a new connector
 * @aux: DisplayPort AUX channel
 * @connector: drm connector
 *
 * A new connector was रेजिस्टरed with associated CEC adapter name and
 * CEC adapter parent device. After रेजिस्टरing the name and parent
 * drm_dp_cec_set_edid() is called to check अगर the connector supports
 * CEC and to रेजिस्टर a CEC adapter अगर that is the हाल.
 */
व्योम drm_dp_cec_रेजिस्टर_connector(काष्ठा drm_dp_aux *aux,
				   काष्ठा drm_connector *connector)
अणु
	WARN_ON(aux->cec.adap);
	अगर (WARN_ON(!aux->transfer))
		वापस;
	aux->cec.connector = connector;
	INIT_DELAYED_WORK(&aux->cec.unरेजिस्टर_work,
			  drm_dp_cec_unरेजिस्टर_work);
पूर्ण
EXPORT_SYMBOL(drm_dp_cec_रेजिस्टर_connector);

/**
 * drm_dp_cec_unरेजिस्टर_connector() - unरेजिस्टर the CEC adapter, अगर any
 * @aux: DisplayPort AUX channel
 */
व्योम drm_dp_cec_unरेजिस्टर_connector(काष्ठा drm_dp_aux *aux)
अणु
	अगर (!aux->cec.adap)
		वापस;
	cancel_delayed_work_sync(&aux->cec.unरेजिस्टर_work);
	cec_unरेजिस्टर_adapter(aux->cec.adap);
	aux->cec.adap = शून्य;
पूर्ण
EXPORT_SYMBOL(drm_dp_cec_unरेजिस्टर_connector);
