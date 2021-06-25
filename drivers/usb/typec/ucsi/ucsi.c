<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Type-C Connector System Software Interface driver
 *
 * Copyright (C) 2017, Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/completion.h>
#समावेश <linux/property.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/typec_dp.h>

#समावेश "ucsi.h"
#समावेश "trace.h"

/*
 * UCSI_TIMEOUT_MS - PPM communication समयout
 *
 * Ideally we could use MIN_TIME_TO_RESPOND_WITH_BUSY (which is defined in UCSI
 * specअगरication) here as reference, but unक्रमtunately we can't. It is very
 * dअगरficult to estimate the समय it takes क्रम the प्रणाली to process the command
 * beक्रमe it is actually passed to the PPM.
 */
#घोषणा UCSI_TIMEOUT_MS		5000

/*
 * UCSI_SWAP_TIMEOUT_MS - Timeout क्रम role swap requests
 *
 * 5 seconds is बंद to the समय it takes क्रम CapsCounter to reach 0, so even
 * अगर the PPM करोes not generate Connector Change events beक्रमe that with
 * partners that करो not support USB Power Delivery, this should still work.
 */
#घोषणा UCSI_SWAP_TIMEOUT_MS	5000

अटल पूर्णांक ucsi_acknowledge_command(काष्ठा ucsi *ucsi)
अणु
	u64 ctrl;

	ctrl = UCSI_ACK_CC_CI;
	ctrl |= UCSI_ACK_COMMAND_COMPLETE;

	वापस ucsi->ops->sync_ग_लिखो(ucsi, UCSI_CONTROL, &ctrl, माप(ctrl));
पूर्ण

अटल पूर्णांक ucsi_acknowledge_connector_change(काष्ठा ucsi *ucsi)
अणु
	u64 ctrl;

	ctrl = UCSI_ACK_CC_CI;
	ctrl |= UCSI_ACK_CONNECTOR_CHANGE;

	वापस ucsi->ops->sync_ग_लिखो(ucsi, UCSI_CONTROL, &ctrl, माप(ctrl));
पूर्ण

अटल पूर्णांक ucsi_exec_command(काष्ठा ucsi *ucsi, u64 command);

अटल पूर्णांक ucsi_पढ़ो_error(काष्ठा ucsi *ucsi)
अणु
	u16 error;
	पूर्णांक ret;

	/* Acknowledge the command that failed */
	ret = ucsi_acknowledge_command(ucsi);
	अगर (ret)
		वापस ret;

	ret = ucsi_exec_command(ucsi, UCSI_GET_ERROR_STATUS);
	अगर (ret < 0)
		वापस ret;

	ret = ucsi->ops->पढ़ो(ucsi, UCSI_MESSAGE_IN, &error, माप(error));
	अगर (ret)
		वापस ret;

	चयन (error) अणु
	हाल UCSI_ERROR_INCOMPATIBLE_PARTNER:
		वापस -EOPNOTSUPP;
	हाल UCSI_ERROR_CC_COMMUNICATION_ERR:
		वापस -ECOMM;
	हाल UCSI_ERROR_CONTRACT_NEGOTIATION_FAIL:
		वापस -EPROTO;
	हाल UCSI_ERROR_DEAD_BATTERY:
		dev_warn(ucsi->dev, "Dead battery condition!\n");
		वापस -EPERM;
	हाल UCSI_ERROR_INVALID_CON_NUM:
	हाल UCSI_ERROR_UNREGONIZED_CMD:
	हाल UCSI_ERROR_INVALID_CMD_ARGUMENT:
		dev_err(ucsi->dev, "possible UCSI driver bug %u\n", error);
		वापस -EINVAL;
	हाल UCSI_ERROR_OVERCURRENT:
		dev_warn(ucsi->dev, "Overcurrent condition\n");
		अवरोध;
	हाल UCSI_ERROR_PARTNER_REJECTED_SWAP:
		dev_warn(ucsi->dev, "Partner rejected swap\n");
		अवरोध;
	हाल UCSI_ERROR_HARD_RESET:
		dev_warn(ucsi->dev, "Hard reset occurred\n");
		अवरोध;
	हाल UCSI_ERROR_PPM_POLICY_CONFLICT:
		dev_warn(ucsi->dev, "PPM Policy conflict\n");
		अवरोध;
	हाल UCSI_ERROR_SWAP_REJECTED:
		dev_warn(ucsi->dev, "Swap rejected\n");
		अवरोध;
	हाल UCSI_ERROR_UNDEFINED:
	शेष:
		dev_err(ucsi->dev, "unknown error %u\n", error);
		अवरोध;
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक ucsi_exec_command(काष्ठा ucsi *ucsi, u64 cmd)
अणु
	u32 cci;
	पूर्णांक ret;

	ret = ucsi->ops->sync_ग_लिखो(ucsi, UCSI_CONTROL, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	ret = ucsi->ops->पढ़ो(ucsi, UCSI_CCI, &cci, माप(cci));
	अगर (ret)
		वापस ret;

	अगर (cci & UCSI_CCI_BUSY)
		वापस -EBUSY;

	अगर (!(cci & UCSI_CCI_COMMAND_COMPLETE))
		वापस -EIO;

	अगर (cci & UCSI_CCI_NOT_SUPPORTED)
		वापस -EOPNOTSUPP;

	अगर (cci & UCSI_CCI_ERROR) अणु
		अगर (cmd == UCSI_GET_ERROR_STATUS)
			वापस -EIO;
		वापस ucsi_पढ़ो_error(ucsi);
	पूर्ण

	वापस UCSI_CCI_LENGTH(cci);
पूर्ण

पूर्णांक ucsi_send_command(काष्ठा ucsi *ucsi, u64 command,
		      व्योम *data, माप_प्रकार size)
अणु
	u8 length;
	पूर्णांक ret;

	mutex_lock(&ucsi->ppm_lock);

	ret = ucsi_exec_command(ucsi, command);
	अगर (ret < 0)
		जाओ out;

	length = ret;

	अगर (data) अणु
		ret = ucsi->ops->पढ़ो(ucsi, UCSI_MESSAGE_IN, data, size);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = ucsi_acknowledge_command(ucsi);
	अगर (ret)
		जाओ out;

	ret = length;
out:
	mutex_unlock(&ucsi->ppm_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ucsi_send_command);

पूर्णांक ucsi_resume(काष्ठा ucsi *ucsi)
अणु
	u64 command;

	/* Restore UCSI notअगरication enable mask after प्रणाली resume */
	command = UCSI_SET_NOTIFICATION_ENABLE | ucsi->ntfy;

	वापस ucsi_send_command(ucsi, command, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ucsi_resume);
/* -------------------------------------------------------------------------- */

व्योम ucsi_alपंचांगode_update_active(काष्ठा ucsi_connector *con)
अणु
	स्थिर काष्ठा typec_alपंचांगode *alपंचांगode = शून्य;
	u64 command;
	पूर्णांक ret;
	u8 cur;
	पूर्णांक i;

	command = UCSI_GET_CURRENT_CAM | UCSI_CONNECTOR_NUMBER(con->num);
	ret = ucsi_send_command(con->ucsi, command, &cur, माप(cur));
	अगर (ret < 0) अणु
		अगर (con->ucsi->version > 0x0100) अणु
			dev_err(con->ucsi->dev,
				"GET_CURRENT_CAM command failed\n");
			वापस;
		पूर्ण
		cur = 0xff;
	पूर्ण

	अगर (cur < UCSI_MAX_ALTMODES)
		alपंचांगode = typec_alपंचांगode_get_partner(con->port_alपंचांगode[cur]);

	क्रम (i = 0; con->partner_alपंचांगode[i]; i++)
		typec_alपंचांगode_update_active(con->partner_alपंचांगode[i],
					    con->partner_alपंचांगode[i] == alपंचांगode);
पूर्ण

अटल पूर्णांक ucsi_alपंचांगode_next_mode(काष्ठा typec_alपंचांगode **alt, u16 svid)
अणु
	u8 mode = 1;
	पूर्णांक i;

	क्रम (i = 0; alt[i]; i++) अणु
		अगर (i > MODE_DISCOVERY_MAX)
			वापस -दुस्फल;

		अगर (alt[i]->svid == svid)
			mode++;
	पूर्ण

	वापस mode;
पूर्ण

अटल पूर्णांक ucsi_next_alपंचांगode(काष्ठा typec_alपंचांगode **alt)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < UCSI_MAX_ALTMODES; i++)
		अगर (!alt[i])
			वापस i;

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक ucsi_रेजिस्टर_alपंचांगode(काष्ठा ucsi_connector *con,
				 काष्ठा typec_alपंचांगode_desc *desc,
				 u8 recipient)
अणु
	काष्ठा typec_alपंचांगode *alt;
	bool override;
	पूर्णांक ret;
	पूर्णांक i;

	override = !!(con->ucsi->cap.features & UCSI_CAP_ALT_MODE_OVERRIDE);

	चयन (recipient) अणु
	हाल UCSI_RECIPIENT_CON:
		i = ucsi_next_alपंचांगode(con->port_alपंचांगode);
		अगर (i < 0) अणु
			ret = i;
			जाओ err;
		पूर्ण

		ret = ucsi_alपंचांगode_next_mode(con->port_alपंचांगode, desc->svid);
		अगर (ret < 0)
			वापस ret;

		desc->mode = ret;

		चयन (desc->svid) अणु
		हाल USB_TYPEC_DP_SID:
			alt = ucsi_रेजिस्टर_displayport(con, override, i, desc);
			अवरोध;
		हाल USB_TYPEC_NVIDIA_VLINK_SID:
			अगर (desc->vकरो == USB_TYPEC_NVIDIA_VLINK_DBG_VDO)
				alt = typec_port_रेजिस्टर_alपंचांगode(con->port,
								  desc);
			अन्यथा
				alt = ucsi_रेजिस्टर_displayport(con, override,
								i, desc);
			अवरोध;
		शेष:
			alt = typec_port_रेजिस्टर_alपंचांगode(con->port, desc);
			अवरोध;
		पूर्ण

		अगर (IS_ERR(alt)) अणु
			ret = PTR_ERR(alt);
			जाओ err;
		पूर्ण

		con->port_alपंचांगode[i] = alt;
		अवरोध;
	हाल UCSI_RECIPIENT_SOP:
		i = ucsi_next_alपंचांगode(con->partner_alपंचांगode);
		अगर (i < 0) अणु
			ret = i;
			जाओ err;
		पूर्ण

		ret = ucsi_alपंचांगode_next_mode(con->partner_alपंचांगode, desc->svid);
		अगर (ret < 0)
			वापस ret;

		desc->mode = ret;

		alt = typec_partner_रेजिस्टर_alपंचांगode(con->partner, desc);
		अगर (IS_ERR(alt)) अणु
			ret = PTR_ERR(alt);
			जाओ err;
		पूर्ण

		con->partner_alपंचांगode[i] = alt;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	trace_ucsi_रेजिस्टर_alपंचांगode(recipient, alt);

	वापस 0;

err:
	dev_err(con->ucsi->dev, "failed to registers svid 0x%04x mode %d\n",
		desc->svid, desc->mode);

	वापस ret;
पूर्ण

अटल पूर्णांक
ucsi_रेजिस्टर_alपंचांगodes_nvidia(काष्ठा ucsi_connector *con, u8 recipient)
अणु
	पूर्णांक max_alपंचांगodes = UCSI_MAX_ALTMODES;
	काष्ठा typec_alपंचांगode_desc desc;
	काष्ठा ucsi_alपंचांगode alt;
	काष्ठा ucsi_alपंचांगode orig[UCSI_MAX_ALTMODES];
	काष्ठा ucsi_alपंचांगode updated[UCSI_MAX_ALTMODES];
	काष्ठा ucsi *ucsi = con->ucsi;
	bool multi_dp = false;
	u64 command;
	पूर्णांक ret;
	पूर्णांक len;
	पूर्णांक i;
	पूर्णांक k = 0;

	अगर (recipient == UCSI_RECIPIENT_CON)
		max_alपंचांगodes = con->ucsi->cap.num_alt_modes;

	स_रखो(orig, 0, माप(orig));
	स_रखो(updated, 0, माप(updated));

	/* First get all the alternate modes */
	क्रम (i = 0; i < max_alपंचांगodes; i++) अणु
		स_रखो(&alt, 0, माप(alt));
		command = UCSI_GET_ALTERNATE_MODES;
		command |= UCSI_GET_ALTMODE_RECIPIENT(recipient);
		command |= UCSI_GET_ALTMODE_CONNECTOR_NUMBER(con->num);
		command |= UCSI_GET_ALTMODE_OFFSET(i);
		len = ucsi_send_command(con->ucsi, command, &alt, माप(alt));
		/*
		 * We are collecting all alपंचांगodes first and then रेजिस्टरing.
		 * Some type-C device will वापस zero length data beyond last
		 * alternate modes. We should not वापस अगर length is zero.
		 */
		अगर (len < 0)
			वापस len;

		/* We got all alपंचांगodes, now अवरोध out and रेजिस्टर them */
		अगर (!len || !alt.svid)
			अवरोध;

		orig[k].mid = alt.mid;
		orig[k].svid = alt.svid;
		k++;
	पूर्ण
	/*
	 * Update the original alपंचांगode table as some ppms may report
	 * multiple DP alपंचांगodes.
	 */
	अगर (recipient == UCSI_RECIPIENT_CON)
		multi_dp = ucsi->ops->update_alपंचांगodes(ucsi, orig, updated);

	/* now रेजिस्टर alपंचांगodes */
	क्रम (i = 0; i < max_alपंचांगodes; i++) अणु
		स_रखो(&desc, 0, माप(desc));
		अगर (multi_dp && recipient == UCSI_RECIPIENT_CON) अणु
			desc.svid = updated[i].svid;
			desc.vकरो = updated[i].mid;
		पूर्ण अन्यथा अणु
			desc.svid = orig[i].svid;
			desc.vकरो = orig[i].mid;
		पूर्ण
		desc.roles = TYPEC_PORT_DRD;

		अगर (!desc.svid)
			वापस 0;

		ret = ucsi_रेजिस्टर_alपंचांगode(con, &desc, recipient);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_रेजिस्टर_alपंचांगodes(काष्ठा ucsi_connector *con, u8 recipient)
अणु
	पूर्णांक max_alपंचांगodes = UCSI_MAX_ALTMODES;
	काष्ठा typec_alपंचांगode_desc desc;
	काष्ठा ucsi_alपंचांगode alt[2];
	u64 command;
	पूर्णांक num;
	पूर्णांक ret;
	पूर्णांक len;
	पूर्णांक j;
	पूर्णांक i;

	अगर (!(con->ucsi->cap.features & UCSI_CAP_ALT_MODE_DETAILS))
		वापस 0;

	अगर (recipient == UCSI_RECIPIENT_SOP && con->partner_alपंचांगode[0])
		वापस 0;

	अगर (con->ucsi->ops->update_alपंचांगodes)
		वापस ucsi_रेजिस्टर_alपंचांगodes_nvidia(con, recipient);

	अगर (recipient == UCSI_RECIPIENT_CON)
		max_alपंचांगodes = con->ucsi->cap.num_alt_modes;

	क्रम (i = 0; i < max_alपंचांगodes;) अणु
		स_रखो(alt, 0, माप(alt));
		command = UCSI_GET_ALTERNATE_MODES;
		command |= UCSI_GET_ALTMODE_RECIPIENT(recipient);
		command |= UCSI_GET_ALTMODE_CONNECTOR_NUMBER(con->num);
		command |= UCSI_GET_ALTMODE_OFFSET(i);
		len = ucsi_send_command(con->ucsi, command, alt, माप(alt));
		अगर (len <= 0)
			वापस len;

		/*
		 * This code is requesting one alt mode at a समय, but some PPMs
		 * may still वापस two. If that happens both alt modes need be
		 * रेजिस्टरed and the offset क्रम the next alt mode has to be
		 * incremented.
		 */
		num = len / माप(alt[0]);
		i += num;

		क्रम (j = 0; j < num; j++) अणु
			अगर (!alt[j].svid)
				वापस 0;

			स_रखो(&desc, 0, माप(desc));
			desc.vकरो = alt[j].mid;
			desc.svid = alt[j].svid;
			desc.roles = TYPEC_PORT_DRD;

			ret = ucsi_रेजिस्टर_alपंचांगode(con, &desc, recipient);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ucsi_unरेजिस्टर_alपंचांगodes(काष्ठा ucsi_connector *con, u8 recipient)
अणु
	स्थिर काष्ठा typec_alपंचांगode *pdev;
	काष्ठा typec_alपंचांगode **adev;
	पूर्णांक i = 0;

	चयन (recipient) अणु
	हाल UCSI_RECIPIENT_CON:
		adev = con->port_alपंचांगode;
		अवरोध;
	हाल UCSI_RECIPIENT_SOP:
		adev = con->partner_alपंचांगode;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	जबतक (adev[i]) अणु
		अगर (recipient == UCSI_RECIPIENT_SOP &&
		    (adev[i]->svid == USB_TYPEC_DP_SID ||
			(adev[i]->svid == USB_TYPEC_NVIDIA_VLINK_SID &&
			adev[i]->vकरो != USB_TYPEC_NVIDIA_VLINK_DBG_VDO))) अणु
			pdev = typec_alपंचांगode_get_partner(adev[i]);
			ucsi_displayport_हटाओ_partner((व्योम *)pdev);
		पूर्ण
		typec_unरेजिस्टर_alपंचांगode(adev[i]);
		adev[i++] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ucsi_get_pकरोs(काष्ठा ucsi_connector *con, पूर्णांक is_partner,
			 u32 *pकरोs, पूर्णांक offset, पूर्णांक num_pकरोs)
अणु
	काष्ठा ucsi *ucsi = con->ucsi;
	u64 command;
	पूर्णांक ret;

	command = UCSI_COMMAND(UCSI_GET_PDOS) | UCSI_CONNECTOR_NUMBER(con->num);
	command |= UCSI_GET_PDOS_PARTNER_PDO(is_partner);
	command |= UCSI_GET_PDOS_PDO_OFFSET(offset);
	command |= UCSI_GET_PDOS_NUM_PDOS(num_pकरोs - 1);
	command |= UCSI_GET_PDOS_SRC_PDOS;
	ret = ucsi_send_command(ucsi, command, pकरोs + offset,
				num_pकरोs * माप(u32));
	अगर (ret < 0)
		dev_err(ucsi->dev, "UCSI_GET_PDOS failed (%d)\n", ret);
	अगर (ret == 0 && offset == 0)
		dev_warn(ucsi->dev, "UCSI_GET_PDOS returned 0 bytes\n");

	वापस ret;
पूर्ण

अटल व्योम ucsi_get_src_pकरोs(काष्ठा ucsi_connector *con, पूर्णांक is_partner)
अणु
	पूर्णांक ret;

	/* UCSI max payload means only getting at most 4 PDOs at a समय */
	ret = ucsi_get_pकरोs(con, 1, con->src_pकरोs, 0, UCSI_MAX_PDOS);
	अगर (ret < 0)
		वापस;

	con->num_pकरोs = ret / माप(u32); /* number of bytes to 32-bit PDOs */
	अगर (con->num_pकरोs < UCSI_MAX_PDOS)
		वापस;

	/* get the reमुख्यing PDOs, अगर any */
	ret = ucsi_get_pकरोs(con, 1, con->src_pकरोs, UCSI_MAX_PDOS,
			    PDO_MAX_OBJECTS - UCSI_MAX_PDOS);
	अगर (ret < 0)
		वापस;

	con->num_pकरोs += ret / माप(u32);
पूर्ण

अटल व्योम ucsi_pwr_opmode_change(काष्ठा ucsi_connector *con)
अणु
	चयन (UCSI_CONSTAT_PWR_OPMODE(con->status.flags)) अणु
	हाल UCSI_CONSTAT_PWR_OPMODE_PD:
		con->rकरो = con->status.request_data_obj;
		typec_set_pwr_opmode(con->port, TYPEC_PWR_MODE_PD);
		ucsi_get_src_pकरोs(con, 1);
		अवरोध;
	हाल UCSI_CONSTAT_PWR_OPMODE_TYPEC1_5:
		con->rकरो = 0;
		typec_set_pwr_opmode(con->port, TYPEC_PWR_MODE_1_5A);
		अवरोध;
	हाल UCSI_CONSTAT_PWR_OPMODE_TYPEC3_0:
		con->rकरो = 0;
		typec_set_pwr_opmode(con->port, TYPEC_PWR_MODE_3_0A);
		अवरोध;
	शेष:
		con->rकरो = 0;
		typec_set_pwr_opmode(con->port, TYPEC_PWR_MODE_USB);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ucsi_रेजिस्टर_partner(काष्ठा ucsi_connector *con)
अणु
	u8 pwr_opmode = UCSI_CONSTAT_PWR_OPMODE(con->status.flags);
	काष्ठा typec_partner_desc desc;
	काष्ठा typec_partner *partner;

	अगर (con->partner)
		वापस 0;

	स_रखो(&desc, 0, माप(desc));

	चयन (UCSI_CONSTAT_PARTNER_TYPE(con->status.flags)) अणु
	हाल UCSI_CONSTAT_PARTNER_TYPE_DEBUG:
		desc.accessory = TYPEC_ACCESSORY_DEBUG;
		अवरोध;
	हाल UCSI_CONSTAT_PARTNER_TYPE_AUDIO:
		desc.accessory = TYPEC_ACCESSORY_AUDIO;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	desc.usb_pd = pwr_opmode == UCSI_CONSTAT_PWR_OPMODE_PD;

	partner = typec_रेजिस्टर_partner(con->port, &desc);
	अगर (IS_ERR(partner)) अणु
		dev_err(con->ucsi->dev,
			"con%d: failed to register partner (%ld)\n", con->num,
			PTR_ERR(partner));
		वापस PTR_ERR(partner);
	पूर्ण

	con->partner = partner;

	वापस 0;
पूर्ण

अटल व्योम ucsi_unरेजिस्टर_partner(काष्ठा ucsi_connector *con)
अणु
	अगर (!con->partner)
		वापस;

	ucsi_unरेजिस्टर_alपंचांगodes(con, UCSI_RECIPIENT_SOP);
	typec_unरेजिस्टर_partner(con->partner);
	con->partner = शून्य;
पूर्ण

अटल व्योम ucsi_partner_change(काष्ठा ucsi_connector *con)
अणु
	क्रमागत usb_role u_role = USB_ROLE_NONE;
	पूर्णांक ret;

	अगर (!con->partner)
		वापस;

	चयन (UCSI_CONSTAT_PARTNER_TYPE(con->status.flags)) अणु
	हाल UCSI_CONSTAT_PARTNER_TYPE_UFP:
	हाल UCSI_CONSTAT_PARTNER_TYPE_CABLE_AND_UFP:
		u_role = USB_ROLE_HOST;
		fallthrough;
	हाल UCSI_CONSTAT_PARTNER_TYPE_CABLE:
		typec_set_data_role(con->port, TYPEC_HOST);
		अवरोध;
	हाल UCSI_CONSTAT_PARTNER_TYPE_DFP:
		u_role = USB_ROLE_DEVICE;
		typec_set_data_role(con->port, TYPEC_DEVICE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Complete pending data role swap */
	अगर (!completion_करोne(&con->complete))
		complete(&con->complete);

	/* Only notअगरy USB controller अगर partner supports USB data */
	अगर (!(UCSI_CONSTAT_PARTNER_FLAGS(con->status.flags) & UCSI_CONSTAT_PARTNER_FLAG_USB))
		u_role = USB_ROLE_NONE;

	ret = usb_role_चयन_set_role(con->usb_role_sw, u_role);
	अगर (ret)
		dev_err(con->ucsi->dev, "con:%d: failed to set usb role:%d\n",
			con->num, u_role);

	/* Can't rely on Partner Flags field. Always checking the alt modes. */
	ret = ucsi_रेजिस्टर_alपंचांगodes(con, UCSI_RECIPIENT_SOP);
	अगर (ret)
		dev_err(con->ucsi->dev,
			"con%d: failed to register partner alternate modes\n",
			con->num);
	अन्यथा
		ucsi_alपंचांगode_update_active(con);
पूर्ण

अटल व्योम ucsi_handle_connector_change(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ucsi_connector *con = container_of(work, काष्ठा ucsi_connector,
						  work);
	काष्ठा ucsi *ucsi = con->ucsi;
	काष्ठा ucsi_connector_status pre_ack_status;
	काष्ठा ucsi_connector_status post_ack_status;
	क्रमागत typec_role role;
	क्रमागत usb_role u_role = USB_ROLE_NONE;
	u16 inferred_changes;
	u16 changed_flags;
	u64 command;
	पूर्णांक ret;

	mutex_lock(&con->lock);

	/*
	 * Some/many PPMs have an issue where all fields in the change bitfield
	 * are cleared when an ACK is send. This will causes any change
	 * between GET_CONNECTOR_STATUS and ACK to be lost.
	 *
	 * We work around this by re-fetching the connector status afterwards.
	 * We then infer any changes that we see have happened but that may not
	 * be represented in the change bitfield.
	 *
	 * Also, even though we करोn't need to know the currently supported alt
	 * modes, we run the GET_CAM_SUPPORTED command to ensure the PPM करोes
	 * not get stuck in हाल it assumes we करो.
	 * Always करो this, rather than relying on UCSI_CONSTAT_CAM_CHANGE to be
	 * set in the change bitfield.
	 *
	 * We end up with the following actions:
	 *  1. UCSI_GET_CONNECTOR_STATUS, store result, update unprocessed_changes
	 *  2. UCSI_GET_CAM_SUPPORTED, discard result
	 *  3. ACK connector change
	 *  4. UCSI_GET_CONNECTOR_STATUS, store result
	 *  5. Infere lost changes by comparing UCSI_GET_CONNECTOR_STATUS results
	 *  6. If PPM reported a new change, then restart in order to ACK
	 *  7. Process everything as usual.
	 *
	 * We may end up seeing a change twice, but we can only miss extremely
	 * लघु transitional changes.
	 */

	/* 1. First UCSI_GET_CONNECTOR_STATUS */
	command = UCSI_GET_CONNECTOR_STATUS | UCSI_CONNECTOR_NUMBER(con->num);
	ret = ucsi_send_command(ucsi, command, &pre_ack_status,
				माप(pre_ack_status));
	अगर (ret < 0) अणु
		dev_err(ucsi->dev, "%s: GET_CONNECTOR_STATUS failed (%d)\n",
			__func__, ret);
		जाओ out_unlock;
	पूर्ण
	con->unprocessed_changes |= pre_ack_status.change;

	/* 2. Run UCSI_GET_CAM_SUPPORTED and discard the result. */
	command = UCSI_GET_CAM_SUPPORTED;
	command |= UCSI_CONNECTOR_NUMBER(con->num);
	ucsi_send_command(con->ucsi, command, शून्य, 0);

	/* 3. ACK connector change */
	ret = ucsi_acknowledge_connector_change(ucsi);
	clear_bit(EVENT_PENDING, &ucsi->flags);
	अगर (ret) अणु
		dev_err(ucsi->dev, "%s: ACK failed (%d)", __func__, ret);
		जाओ out_unlock;
	पूर्ण

	/* 4. Second UCSI_GET_CONNECTOR_STATUS */
	command = UCSI_GET_CONNECTOR_STATUS | UCSI_CONNECTOR_NUMBER(con->num);
	ret = ucsi_send_command(ucsi, command, &post_ack_status,
				माप(post_ack_status));
	अगर (ret < 0) अणु
		dev_err(ucsi->dev, "%s: GET_CONNECTOR_STATUS failed (%d)\n",
			__func__, ret);
		जाओ out_unlock;
	पूर्ण

	/* 5. Inferre any missing changes */
	changed_flags = pre_ack_status.flags ^ post_ack_status.flags;
	inferred_changes = 0;
	अगर (UCSI_CONSTAT_PWR_OPMODE(changed_flags) != 0)
		inferred_changes |= UCSI_CONSTAT_POWER_OPMODE_CHANGE;

	अगर (changed_flags & UCSI_CONSTAT_CONNECTED)
		inferred_changes |= UCSI_CONSTAT_CONNECT_CHANGE;

	अगर (changed_flags & UCSI_CONSTAT_PWR_सूची)
		inferred_changes |= UCSI_CONSTAT_POWER_सूची_CHANGE;

	अगर (UCSI_CONSTAT_PARTNER_FLAGS(changed_flags) != 0)
		inferred_changes |= UCSI_CONSTAT_PARTNER_CHANGE;

	अगर (UCSI_CONSTAT_PARTNER_TYPE(changed_flags) != 0)
		inferred_changes |= UCSI_CONSTAT_PARTNER_CHANGE;

	/* Mask out anything that was correctly notअगरied in the later call. */
	inferred_changes &= ~post_ack_status.change;
	अगर (inferred_changes)
		dev_dbg(ucsi->dev, "%s: Inferred changes that would have been lost: 0x%04x\n",
			__func__, inferred_changes);

	con->unprocessed_changes |= inferred_changes;

	/* 6. If PPM reported a new change, then restart in order to ACK */
	अगर (post_ack_status.change)
		जाओ out_unlock;

	/* 7. Continue as अगर nothing happened */
	con->status = post_ack_status;
	con->status.change = con->unprocessed_changes;
	con->unprocessed_changes = 0;

	role = !!(con->status.flags & UCSI_CONSTAT_PWR_सूची);

	अगर (con->status.change & UCSI_CONSTAT_POWER_OPMODE_CHANGE ||
	    con->status.change & UCSI_CONSTAT_POWER_LEVEL_CHANGE) अणु
		ucsi_pwr_opmode_change(con);
		ucsi_port_psy_changed(con);
	पूर्ण

	अगर (con->status.change & UCSI_CONSTAT_POWER_सूची_CHANGE) अणु
		typec_set_pwr_role(con->port, role);

		/* Complete pending घातer role swap */
		अगर (!completion_करोne(&con->complete))
			complete(&con->complete);
	पूर्ण

	अगर (con->status.change & UCSI_CONSTAT_CONNECT_CHANGE) अणु
		typec_set_pwr_role(con->port, role);

		चयन (UCSI_CONSTAT_PARTNER_TYPE(con->status.flags)) अणु
		हाल UCSI_CONSTAT_PARTNER_TYPE_UFP:
		हाल UCSI_CONSTAT_PARTNER_TYPE_CABLE_AND_UFP:
			u_role = USB_ROLE_HOST;
			fallthrough;
		हाल UCSI_CONSTAT_PARTNER_TYPE_CABLE:
			typec_set_data_role(con->port, TYPEC_HOST);
			अवरोध;
		हाल UCSI_CONSTAT_PARTNER_TYPE_DFP:
			u_role = USB_ROLE_DEVICE;
			typec_set_data_role(con->port, TYPEC_DEVICE);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (con->status.flags & UCSI_CONSTAT_CONNECTED)
			ucsi_रेजिस्टर_partner(con);
		अन्यथा
			ucsi_unरेजिस्टर_partner(con);

		ucsi_port_psy_changed(con);

		/* Only notअगरy USB controller अगर partner supports USB data */
		अगर (!(UCSI_CONSTAT_PARTNER_FLAGS(con->status.flags) &
				UCSI_CONSTAT_PARTNER_FLAG_USB))
			u_role = USB_ROLE_NONE;

		ret = usb_role_चयन_set_role(con->usb_role_sw, u_role);
		अगर (ret)
			dev_err(ucsi->dev, "con:%d: failed to set usb role:%d\n",
				con->num, u_role);
	पूर्ण

	अगर (con->status.change & UCSI_CONSTAT_PARTNER_CHANGE)
		ucsi_partner_change(con);

	trace_ucsi_connector_change(con->num, &con->status);

out_unlock:
	अगर (test_and_clear_bit(EVENT_PENDING, &ucsi->flags)) अणु
		schedule_work(&con->work);
		mutex_unlock(&con->lock);
		वापस;
	पूर्ण

	clear_bit(EVENT_PROCESSING, &ucsi->flags);
	mutex_unlock(&con->lock);
पूर्ण

/**
 * ucsi_connector_change - Process Connector Change Event
 * @ucsi: UCSI Interface
 * @num: Connector number
 */
व्योम ucsi_connector_change(काष्ठा ucsi *ucsi, u8 num)
अणु
	काष्ठा ucsi_connector *con = &ucsi->connector[num - 1];

	अगर (!(ucsi->ntfy & UCSI_ENABLE_NTFY_CONNECTOR_CHANGE)) अणु
		dev_dbg(ucsi->dev, "Bogus connector change event\n");
		वापस;
	पूर्ण

	set_bit(EVENT_PENDING, &ucsi->flags);

	अगर (!test_and_set_bit(EVENT_PROCESSING, &ucsi->flags))
		schedule_work(&con->work);
पूर्ण
EXPORT_SYMBOL_GPL(ucsi_connector_change);

/* -------------------------------------------------------------------------- */

अटल पूर्णांक ucsi_reset_connector(काष्ठा ucsi_connector *con, bool hard)
अणु
	u64 command;

	command = UCSI_CONNECTOR_RESET | UCSI_CONNECTOR_NUMBER(con->num);
	command |= hard ? UCSI_CONNECTOR_RESET_HARD : 0;

	वापस ucsi_send_command(con->ucsi, command, शून्य, 0);
पूर्ण

अटल पूर्णांक ucsi_reset_ppm(काष्ठा ucsi *ucsi)
अणु
	u64 command = UCSI_PPM_RESET;
	अचिन्हित दीर्घ पंचांगo;
	u32 cci;
	पूर्णांक ret;

	mutex_lock(&ucsi->ppm_lock);

	ret = ucsi->ops->async_ग_लिखो(ucsi, UCSI_CONTROL, &command,
				     माप(command));
	अगर (ret < 0)
		जाओ out;

	पंचांगo = jअगरfies + msecs_to_jअगरfies(UCSI_TIMEOUT_MS);

	करो अणु
		अगर (समय_is_beक्रमe_jअगरfies(पंचांगo)) अणु
			ret = -ETIMEDOUT;
			जाओ out;
		पूर्ण

		ret = ucsi->ops->पढ़ो(ucsi, UCSI_CCI, &cci, माप(cci));
		अगर (ret)
			जाओ out;

		/* If the PPM is still करोing something अन्यथा, reset it again. */
		अगर (cci & ~UCSI_CCI_RESET_COMPLETE) अणु
			ret = ucsi->ops->async_ग_लिखो(ucsi, UCSI_CONTROL,
						     &command,
						     माप(command));
			अगर (ret < 0)
				जाओ out;
		पूर्ण

		msleep(20);
	पूर्ण जबतक (!(cci & UCSI_CCI_RESET_COMPLETE));

out:
	mutex_unlock(&ucsi->ppm_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ucsi_role_cmd(काष्ठा ucsi_connector *con, u64 command)
अणु
	पूर्णांक ret;

	ret = ucsi_send_command(con->ucsi, command, शून्य, 0);
	अगर (ret == -ETIMEDOUT) अणु
		u64 c;

		/* PPM most likely stopped responding. Resetting everything. */
		ucsi_reset_ppm(con->ucsi);

		c = UCSI_SET_NOTIFICATION_ENABLE | con->ucsi->ntfy;
		ucsi_send_command(con->ucsi, c, शून्य, 0);

		ucsi_reset_connector(con, true);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ucsi_dr_swap(काष्ठा typec_port *port, क्रमागत typec_data_role role)
अणु
	काष्ठा ucsi_connector *con = typec_get_drvdata(port);
	u8 partner_type;
	u64 command;
	पूर्णांक ret = 0;

	mutex_lock(&con->lock);

	अगर (!con->partner) अणु
		ret = -ENOTCONN;
		जाओ out_unlock;
	पूर्ण

	partner_type = UCSI_CONSTAT_PARTNER_TYPE(con->status.flags);
	अगर ((partner_type == UCSI_CONSTAT_PARTNER_TYPE_DFP &&
	     role == TYPEC_DEVICE) ||
	    (partner_type == UCSI_CONSTAT_PARTNER_TYPE_UFP &&
	     role == TYPEC_HOST))
		जाओ out_unlock;

	command = UCSI_SET_UOR | UCSI_CONNECTOR_NUMBER(con->num);
	command |= UCSI_SET_UOR_ROLE(role);
	command |= UCSI_SET_UOR_ACCEPT_ROLE_SWAPS;
	ret = ucsi_role_cmd(con, command);
	अगर (ret < 0)
		जाओ out_unlock;

	अगर (!रुको_क्रम_completion_समयout(&con->complete,
					msecs_to_jअगरfies(UCSI_SWAP_TIMEOUT_MS)))
		ret = -ETIMEDOUT;

out_unlock:
	mutex_unlock(&con->lock);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक ucsi_pr_swap(काष्ठा typec_port *port, क्रमागत typec_role role)
अणु
	काष्ठा ucsi_connector *con = typec_get_drvdata(port);
	क्रमागत typec_role cur_role;
	u64 command;
	पूर्णांक ret = 0;

	mutex_lock(&con->lock);

	अगर (!con->partner) अणु
		ret = -ENOTCONN;
		जाओ out_unlock;
	पूर्ण

	cur_role = !!(con->status.flags & UCSI_CONSTAT_PWR_सूची);

	अगर (cur_role == role)
		जाओ out_unlock;

	command = UCSI_SET_PDR | UCSI_CONNECTOR_NUMBER(con->num);
	command |= UCSI_SET_PDR_ROLE(role);
	command |= UCSI_SET_PDR_ACCEPT_ROLE_SWAPS;
	ret = ucsi_role_cmd(con, command);
	अगर (ret < 0)
		जाओ out_unlock;

	अगर (!रुको_क्रम_completion_समयout(&con->complete,
				msecs_to_jअगरfies(UCSI_SWAP_TIMEOUT_MS))) अणु
		ret = -ETIMEDOUT;
		जाओ out_unlock;
	पूर्ण

	/* Something has gone wrong जबतक swapping the role */
	अगर (UCSI_CONSTAT_PWR_OPMODE(con->status.flags) !=
	    UCSI_CONSTAT_PWR_OPMODE_PD) अणु
		ucsi_reset_connector(con, true);
		ret = -EPROTO;
	पूर्ण

out_unlock:
	mutex_unlock(&con->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा typec_operations ucsi_ops = अणु
	.dr_set = ucsi_dr_swap,
	.pr_set = ucsi_pr_swap
पूर्ण;

/* Caller must call fwnode_handle_put() after use */
अटल काष्ठा fwnode_handle *ucsi_find_fwnode(काष्ठा ucsi_connector *con)
अणु
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक i = 1;

	device_क्रम_each_child_node(con->ucsi->dev, fwnode)
		अगर (i++ == con->num)
			वापस fwnode;
	वापस शून्य;
पूर्ण

अटल पूर्णांक ucsi_रेजिस्टर_port(काष्ठा ucsi *ucsi, पूर्णांक index)
अणु
	काष्ठा ucsi_connector *con = &ucsi->connector[index];
	काष्ठा typec_capability *cap = &con->typec_cap;
	क्रमागत typec_accessory *accessory = cap->accessory;
	क्रमागत usb_role u_role = USB_ROLE_NONE;
	u64 command;
	पूर्णांक ret;

	INIT_WORK(&con->work, ucsi_handle_connector_change);
	init_completion(&con->complete);
	mutex_init(&con->lock);
	con->num = index + 1;
	con->ucsi = ucsi;

	/* Delay other पूर्णांकeractions with the con until registration is complete */
	mutex_lock(&con->lock);

	/* Get connector capability */
	command = UCSI_GET_CONNECTOR_CAPABILITY;
	command |= UCSI_CONNECTOR_NUMBER(con->num);
	ret = ucsi_send_command(ucsi, command, &con->cap, माप(con->cap));
	अगर (ret < 0)
		जाओ out_unlock;

	अगर (con->cap.op_mode & UCSI_CONCAP_OPMODE_DRP)
		cap->data = TYPEC_PORT_DRD;
	अन्यथा अगर (con->cap.op_mode & UCSI_CONCAP_OPMODE_DFP)
		cap->data = TYPEC_PORT_DFP;
	अन्यथा अगर (con->cap.op_mode & UCSI_CONCAP_OPMODE_UFP)
		cap->data = TYPEC_PORT_UFP;

	अगर ((con->cap.flags & UCSI_CONCAP_FLAG_PROVIDER) &&
	    (con->cap.flags & UCSI_CONCAP_FLAG_CONSUMER))
		cap->type = TYPEC_PORT_DRP;
	अन्यथा अगर (con->cap.flags & UCSI_CONCAP_FLAG_PROVIDER)
		cap->type = TYPEC_PORT_SRC;
	अन्यथा अगर (con->cap.flags & UCSI_CONCAP_FLAG_CONSUMER)
		cap->type = TYPEC_PORT_SNK;

	cap->revision = ucsi->cap.typec_version;
	cap->pd_revision = ucsi->cap.pd_version;
	cap->svdm_version = SVDM_VER_2_0;
	cap->prefer_role = TYPEC_NO_PREFERRED_ROLE;

	अगर (con->cap.op_mode & UCSI_CONCAP_OPMODE_AUDIO_ACCESSORY)
		*accessory++ = TYPEC_ACCESSORY_AUDIO;
	अगर (con->cap.op_mode & UCSI_CONCAP_OPMODE_DEBUG_ACCESSORY)
		*accessory = TYPEC_ACCESSORY_DEBUG;

	cap->fwnode = ucsi_find_fwnode(con);
	cap->driver_data = con;
	cap->ops = &ucsi_ops;

	ret = ucsi_रेजिस्टर_port_psy(con);
	अगर (ret)
		जाओ out;

	/* Register the connector */
	con->port = typec_रेजिस्टर_port(ucsi->dev, cap);
	अगर (IS_ERR(con->port)) अणु
		ret = PTR_ERR(con->port);
		जाओ out;
	पूर्ण

	/* Alternate modes */
	ret = ucsi_रेजिस्टर_alपंचांगodes(con, UCSI_RECIPIENT_CON);
	अगर (ret) अणु
		dev_err(ucsi->dev, "con%d: failed to register alt modes\n",
			con->num);
		जाओ out;
	पूर्ण

	/* Get the status */
	command = UCSI_GET_CONNECTOR_STATUS | UCSI_CONNECTOR_NUMBER(con->num);
	ret = ucsi_send_command(ucsi, command, &con->status, माप(con->status));
	अगर (ret < 0) अणु
		dev_err(ucsi->dev, "con%d: failed to get status\n", con->num);
		ret = 0;
		जाओ out;
	पूर्ण
	ret = 0; /* ucsi_send_command() वापसs length on success */

	चयन (UCSI_CONSTAT_PARTNER_TYPE(con->status.flags)) अणु
	हाल UCSI_CONSTAT_PARTNER_TYPE_UFP:
	हाल UCSI_CONSTAT_PARTNER_TYPE_CABLE_AND_UFP:
		u_role = USB_ROLE_HOST;
		fallthrough;
	हाल UCSI_CONSTAT_PARTNER_TYPE_CABLE:
		typec_set_data_role(con->port, TYPEC_HOST);
		अवरोध;
	हाल UCSI_CONSTAT_PARTNER_TYPE_DFP:
		u_role = USB_ROLE_DEVICE;
		typec_set_data_role(con->port, TYPEC_DEVICE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Check अगर there is alपढ़ोy something connected */
	अगर (con->status.flags & UCSI_CONSTAT_CONNECTED) अणु
		typec_set_pwr_role(con->port,
				  !!(con->status.flags & UCSI_CONSTAT_PWR_सूची));
		ucsi_pwr_opmode_change(con);
		ucsi_रेजिस्टर_partner(con);
		ucsi_port_psy_changed(con);
	पूर्ण

	con->usb_role_sw = fwnode_usb_role_चयन_get(cap->fwnode);
	अगर (IS_ERR(con->usb_role_sw)) अणु
		dev_err(ucsi->dev, "con%d: failed to get usb role switch\n",
			con->num);
		con->usb_role_sw = शून्य;
	पूर्ण

	/* Only notअगरy USB controller अगर partner supports USB data */
	अगर (!(UCSI_CONSTAT_PARTNER_FLAGS(con->status.flags) & UCSI_CONSTAT_PARTNER_FLAG_USB))
		u_role = USB_ROLE_NONE;

	ret = usb_role_चयन_set_role(con->usb_role_sw, u_role);
	अगर (ret) अणु
		dev_err(ucsi->dev, "con:%d: failed to set usb role:%d\n",
			con->num, u_role);
		ret = 0;
	पूर्ण

	अगर (con->partner) अणु
		ret = ucsi_रेजिस्टर_alपंचांगodes(con, UCSI_RECIPIENT_SOP);
		अगर (ret) अणु
			dev_err(ucsi->dev,
				"con%d: failed to register alternate modes\n",
				con->num);
			ret = 0;
		पूर्ण अन्यथा अणु
			ucsi_alपंचांगode_update_active(con);
		पूर्ण
	पूर्ण

	trace_ucsi_रेजिस्टर_port(con->num, &con->status);

out:
	fwnode_handle_put(cap->fwnode);
out_unlock:
	mutex_unlock(&con->lock);
	वापस ret;
पूर्ण

/**
 * ucsi_init - Initialize UCSI पूर्णांकerface
 * @ucsi: UCSI to be initialized
 *
 * Registers all ports @ucsi has and enables all notअगरication events.
 */
अटल पूर्णांक ucsi_init(काष्ठा ucsi *ucsi)
अणु
	काष्ठा ucsi_connector *con;
	u64 command;
	पूर्णांक ret;
	पूर्णांक i;

	/* Reset the PPM */
	ret = ucsi_reset_ppm(ucsi);
	अगर (ret) अणु
		dev_err(ucsi->dev, "failed to reset PPM!\n");
		जाओ err;
	पूर्ण

	/* Enable basic notअगरications */
	ucsi->ntfy = UCSI_ENABLE_NTFY_CMD_COMPLETE | UCSI_ENABLE_NTFY_ERROR;
	command = UCSI_SET_NOTIFICATION_ENABLE | ucsi->ntfy;
	ret = ucsi_send_command(ucsi, command, शून्य, 0);
	अगर (ret < 0)
		जाओ err_reset;

	/* Get PPM capabilities */
	command = UCSI_GET_CAPABILITY;
	ret = ucsi_send_command(ucsi, command, &ucsi->cap, माप(ucsi->cap));
	अगर (ret < 0)
		जाओ err_reset;

	अगर (!ucsi->cap.num_connectors) अणु
		ret = -ENODEV;
		जाओ err_reset;
	पूर्ण

	/* Allocate the connectors. Released in ucsi_unरेजिस्टर_ppm() */
	ucsi->connector = kसुस्मृति(ucsi->cap.num_connectors + 1,
				  माप(*ucsi->connector), GFP_KERNEL);
	अगर (!ucsi->connector) अणु
		ret = -ENOMEM;
		जाओ err_reset;
	पूर्ण

	/* Register all connectors */
	क्रम (i = 0; i < ucsi->cap.num_connectors; i++) अणु
		ret = ucsi_रेजिस्टर_port(ucsi, i);
		अगर (ret)
			जाओ err_unरेजिस्टर;
	पूर्ण

	/* Enable all notअगरications */
	ucsi->ntfy = UCSI_ENABLE_NTFY_ALL;
	command = UCSI_SET_NOTIFICATION_ENABLE | ucsi->ntfy;
	ret = ucsi_send_command(ucsi, command, शून्य, 0);
	अगर (ret < 0)
		जाओ err_unरेजिस्टर;

	वापस 0;

err_unरेजिस्टर:
	क्रम (con = ucsi->connector; con->port; con++) अणु
		ucsi_unरेजिस्टर_partner(con);
		ucsi_unरेजिस्टर_alपंचांगodes(con, UCSI_RECIPIENT_CON);
		ucsi_unरेजिस्टर_port_psy(con);
		typec_unरेजिस्टर_port(con->port);
		con->port = शून्य;
	पूर्ण

err_reset:
	स_रखो(&ucsi->cap, 0, माप(ucsi->cap));
	ucsi_reset_ppm(ucsi);
err:
	वापस ret;
पूर्ण

अटल व्योम ucsi_init_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ucsi *ucsi = container_of(work, काष्ठा ucsi, work);
	पूर्णांक ret;

	ret = ucsi_init(ucsi);
	अगर (ret)
		dev_err(ucsi->dev, "PPM init failed (%d)\n", ret);
पूर्ण

/**
 * ucsi_get_drvdata - Return निजी driver data poपूर्णांकer
 * @ucsi: UCSI पूर्णांकerface
 */
व्योम *ucsi_get_drvdata(काष्ठा ucsi *ucsi)
अणु
	वापस ucsi->driver_data;
पूर्ण
EXPORT_SYMBOL_GPL(ucsi_get_drvdata);

/**
 * ucsi_get_drvdata - Assign निजी driver data poपूर्णांकer
 * @ucsi: UCSI पूर्णांकerface
 * @data: Private data poपूर्णांकer
 */
व्योम ucsi_set_drvdata(काष्ठा ucsi *ucsi, व्योम *data)
अणु
	ucsi->driver_data = data;
पूर्ण
EXPORT_SYMBOL_GPL(ucsi_set_drvdata);

/**
 * ucsi_create - Allocate UCSI instance
 * @dev: Device पूर्णांकerface to the PPM (Platक्रमm Policy Manager)
 * @ops: I/O routines
 */
काष्ठा ucsi *ucsi_create(काष्ठा device *dev, स्थिर काष्ठा ucsi_operations *ops)
अणु
	काष्ठा ucsi *ucsi;

	अगर (!ops || !ops->पढ़ो || !ops->sync_ग_लिखो || !ops->async_ग_लिखो)
		वापस ERR_PTR(-EINVAL);

	ucsi = kzalloc(माप(*ucsi), GFP_KERNEL);
	अगर (!ucsi)
		वापस ERR_PTR(-ENOMEM);

	INIT_WORK(&ucsi->work, ucsi_init_work);
	mutex_init(&ucsi->ppm_lock);
	ucsi->dev = dev;
	ucsi->ops = ops;

	वापस ucsi;
पूर्ण
EXPORT_SYMBOL_GPL(ucsi_create);

/**
 * ucsi_destroy - Free UCSI instance
 * @ucsi: UCSI instance to be मुक्तd
 */
व्योम ucsi_destroy(काष्ठा ucsi *ucsi)
अणु
	kमुक्त(ucsi);
पूर्ण
EXPORT_SYMBOL_GPL(ucsi_destroy);

/**
 * ucsi_रेजिस्टर - Register UCSI पूर्णांकerface
 * @ucsi: UCSI instance
 */
पूर्णांक ucsi_रेजिस्टर(काष्ठा ucsi *ucsi)
अणु
	पूर्णांक ret;

	ret = ucsi->ops->पढ़ो(ucsi, UCSI_VERSION, &ucsi->version,
			      माप(ucsi->version));
	अगर (ret)
		वापस ret;

	अगर (!ucsi->version)
		वापस -ENODEV;

	queue_work(प्रणाली_दीर्घ_wq, &ucsi->work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ucsi_रेजिस्टर);

/**
 * ucsi_unरेजिस्टर - Unरेजिस्टर UCSI पूर्णांकerface
 * @ucsi: UCSI पूर्णांकerface to be unरेजिस्टरed
 *
 * Unरेजिस्टर UCSI पूर्णांकerface that was created with ucsi_रेजिस्टर().
 */
व्योम ucsi_unरेजिस्टर(काष्ठा ucsi *ucsi)
अणु
	u64 cmd = UCSI_SET_NOTIFICATION_ENABLE;
	पूर्णांक i;

	/* Make sure that we are not in the middle of driver initialization */
	cancel_work_sync(&ucsi->work);

	/* Disable notअगरications */
	ucsi->ops->async_ग_लिखो(ucsi, UCSI_CONTROL, &cmd, माप(cmd));

	क्रम (i = 0; i < ucsi->cap.num_connectors; i++) अणु
		cancel_work_sync(&ucsi->connector[i].work);
		ucsi_unरेजिस्टर_partner(&ucsi->connector[i]);
		ucsi_unरेजिस्टर_alपंचांगodes(&ucsi->connector[i],
					 UCSI_RECIPIENT_CON);
		ucsi_unरेजिस्टर_port_psy(&ucsi->connector[i]);
		typec_unरेजिस्टर_port(ucsi->connector[i].port);
	पूर्ण

	kमुक्त(ucsi->connector);
पूर्ण
EXPORT_SYMBOL_GPL(ucsi_unरेजिस्टर);

MODULE_AUTHOR("Heikki Krogerus <heikki.krogerus@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("USB Type-C Connector System Software Interface driver");
