<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UCSI DisplayPort Alternate Mode Support
 *
 * Copyright (C) 2018, Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/usb/typec_dp.h>
#समावेश <linux/usb/pd_vकरो.h>

#समावेश "ucsi.h"

#घोषणा UCSI_CMD_SET_NEW_CAM(_con_num_, _enter_, _cam_, _am_)		\
	 (UCSI_SET_NEW_CAM | ((_con_num_) << 16) | ((_enter_) << 23) |	\
	  ((_cam_) << 24) | ((u64)(_am_) << 32))

काष्ठा ucsi_dp अणु
	काष्ठा typec_displayport_data data;
	काष्ठा ucsi_connector *con;
	काष्ठा typec_alपंचांगode *alt;
	काष्ठा work_काष्ठा work;
	पूर्णांक offset;

	bool override;
	bool initialized;

	u32 header;
	u32 *vकरो_data;
	u8 vकरो_size;
पूर्ण;

/*
 * Note. Alternate mode control is optional feature in UCSI. It means that even
 * अगर the प्रणाली supports alternate modes, the OS may not be aware of them.
 *
 * In most हालs however, the OS will be able to see the supported alternate
 * modes, but it may still not be able to configure them, not even enter or निकास
 * them. That is because UCSI defines alt mode details and alt mode "overriding"
 * as separate options.
 *
 * In हाल alt mode details are supported, but overriding is not, the driver
 * will still display the supported pin assignments and configuration, but any
 * changes the user attempts to करो will lead पूर्णांकo failure with वापस value of
 * -EOPNOTSUPP.
 */

अटल पूर्णांक ucsi_displayport_enter(काष्ठा typec_alपंचांगode *alt, u32 *vकरो)
अणु
	काष्ठा ucsi_dp *dp = typec_alपंचांगode_get_drvdata(alt);
	काष्ठा ucsi *ucsi = dp->con->ucsi;
	पूर्णांक svdm_version;
	u64 command;
	u8 cur = 0;
	पूर्णांक ret;

	mutex_lock(&dp->con->lock);

	अगर (!dp->override && dp->initialized) अणु
		स्थिर काष्ठा typec_alपंचांगode *p = typec_alपंचांगode_get_partner(alt);

		dev_warn(&p->dev,
			 "firmware doesn't support alternate mode overriding\n");
		ret = -EOPNOTSUPP;
		जाओ err_unlock;
	पूर्ण

	command = UCSI_GET_CURRENT_CAM | UCSI_CONNECTOR_NUMBER(dp->con->num);
	ret = ucsi_send_command(ucsi, command, &cur, माप(cur));
	अगर (ret < 0) अणु
		अगर (ucsi->version > 0x0100)
			जाओ err_unlock;
		cur = 0xff;
	पूर्ण

	अगर (cur != 0xff) अणु
		ret = dp->con->port_alपंचांगode[cur] == alt ? 0 : -EBUSY;
		जाओ err_unlock;
	पूर्ण

	/*
	 * We can't send the New CAM command yet to the PPM as it needs the
	 * configuration value as well. Pretending that we have now entered the
	 * mode, and letting the alt mode driver जारी.
	 */

	svdm_version = typec_alपंचांगode_get_svdm_version(alt);
	अगर (svdm_version < 0) अणु
		ret = svdm_version;
		जाओ err_unlock;
	पूर्ण

	dp->header = VDO(USB_TYPEC_DP_SID, 1, svdm_version, CMD_ENTER_MODE);
	dp->header |= VDO_OPOS(USB_TYPEC_DP_MODE);
	dp->header |= VDO_CMDT(CMDT_RSP_ACK);

	dp->vकरो_data = शून्य;
	dp->vकरो_size = 1;

	schedule_work(&dp->work);
	ret = 0;
err_unlock:
	mutex_unlock(&dp->con->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ucsi_displayport_निकास(काष्ठा typec_alपंचांगode *alt)
अणु
	काष्ठा ucsi_dp *dp = typec_alपंचांगode_get_drvdata(alt);
	पूर्णांक svdm_version;
	u64 command;
	पूर्णांक ret = 0;

	mutex_lock(&dp->con->lock);

	अगर (!dp->override) अणु
		स्थिर काष्ठा typec_alपंचांगode *p = typec_alपंचांगode_get_partner(alt);

		dev_warn(&p->dev,
			 "firmware doesn't support alternate mode overriding\n");
		ret = -EOPNOTSUPP;
		जाओ out_unlock;
	पूर्ण

	command = UCSI_CMD_SET_NEW_CAM(dp->con->num, 0, dp->offset, 0);
	ret = ucsi_send_command(dp->con->ucsi, command, शून्य, 0);
	अगर (ret < 0)
		जाओ out_unlock;

	svdm_version = typec_alपंचांगode_get_svdm_version(alt);
	अगर (svdm_version < 0) अणु
		ret = svdm_version;
		जाओ out_unlock;
	पूर्ण

	dp->header = VDO(USB_TYPEC_DP_SID, 1, svdm_version, CMD_EXIT_MODE);
	dp->header |= VDO_OPOS(USB_TYPEC_DP_MODE);
	dp->header |= VDO_CMDT(CMDT_RSP_ACK);

	dp->vकरो_data = शून्य;
	dp->vकरो_size = 1;

	schedule_work(&dp->work);

out_unlock:
	mutex_unlock(&dp->con->lock);

	वापस ret;
पूर्ण

/*
 * We करो not actually have access to the Status Update VDO, so we have to guess
 * things.
 */
अटल पूर्णांक ucsi_displayport_status_update(काष्ठा ucsi_dp *dp)
अणु
	u32 cap = dp->alt->vकरो;

	dp->data.status = DP_STATUS_ENABLED;

	/*
	 * If pin assignement D is supported, claiming always
	 * that Multi-function is preferred.
	 */
	अगर (DP_CAP_CAPABILITY(cap) & DP_CAP_UFP_D) अणु
		dp->data.status |= DP_STATUS_CON_UFP_D;

		अगर (DP_CAP_UFP_D_PIN_ASSIGN(cap) & BIT(DP_PIN_ASSIGN_D))
			dp->data.status |= DP_STATUS_PREFER_MULTI_FUNC;
	पूर्ण अन्यथा अणु
		dp->data.status |= DP_STATUS_CON_DFP_D;

		अगर (DP_CAP_DFP_D_PIN_ASSIGN(cap) & BIT(DP_PIN_ASSIGN_D))
			dp->data.status |= DP_STATUS_PREFER_MULTI_FUNC;
	पूर्ण

	dp->vकरो_data = &dp->data.status;
	dp->vकरो_size = 2;

	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_displayport_configure(काष्ठा ucsi_dp *dp)
अणु
	u32 pins = DP_CONF_GET_PIN_ASSIGN(dp->data.conf);
	u64 command;

	अगर (!dp->override)
		वापस 0;

	command = UCSI_CMD_SET_NEW_CAM(dp->con->num, 1, dp->offset, pins);

	वापस ucsi_send_command(dp->con->ucsi, command, शून्य, 0);
पूर्ण

अटल पूर्णांक ucsi_displayport_vdm(काष्ठा typec_alपंचांगode *alt,
				u32 header, स्थिर u32 *data, पूर्णांक count)
अणु
	काष्ठा ucsi_dp *dp = typec_alपंचांगode_get_drvdata(alt);
	पूर्णांक cmd_type = PD_VDO_CMDT(header);
	पूर्णांक cmd = PD_VDO_CMD(header);
	पूर्णांक svdm_version;

	mutex_lock(&dp->con->lock);

	अगर (!dp->override && dp->initialized) अणु
		स्थिर काष्ठा typec_alपंचांगode *p = typec_alपंचांगode_get_partner(alt);

		dev_warn(&p->dev,
			 "firmware doesn't support alternate mode overriding\n");
		mutex_unlock(&dp->con->lock);
		वापस -EOPNOTSUPP;
	पूर्ण

	svdm_version = typec_alपंचांगode_get_svdm_version(alt);
	अगर (svdm_version < 0) अणु
		mutex_unlock(&dp->con->lock);
		वापस svdm_version;
	पूर्ण

	चयन (cmd_type) अणु
	हाल CMDT_INIT:
		अगर (PD_VDO_SVDM_VER(header) < svdm_version) अणु
			typec_partner_set_svdm_version(dp->con->partner, PD_VDO_SVDM_VER(header));
			svdm_version = PD_VDO_SVDM_VER(header);
		पूर्ण

		dp->header = VDO(USB_TYPEC_DP_SID, 1, svdm_version, cmd);
		dp->header |= VDO_OPOS(USB_TYPEC_DP_MODE);

		चयन (cmd) अणु
		हाल DP_CMD_STATUS_UPDATE:
			अगर (ucsi_displayport_status_update(dp))
				dp->header |= VDO_CMDT(CMDT_RSP_NAK);
			अन्यथा
				dp->header |= VDO_CMDT(CMDT_RSP_ACK);
			अवरोध;
		हाल DP_CMD_CONFIGURE:
			dp->data.conf = *data;
			अगर (ucsi_displayport_configure(dp)) अणु
				dp->header |= VDO_CMDT(CMDT_RSP_NAK);
			पूर्ण अन्यथा अणु
				dp->header |= VDO_CMDT(CMDT_RSP_ACK);
				अगर (dp->initialized)
					ucsi_alपंचांगode_update_active(dp->con);
				अन्यथा
					dp->initialized = true;
			पूर्ण
			अवरोध;
		शेष:
			dp->header |= VDO_CMDT(CMDT_RSP_ACK);
			अवरोध;
		पूर्ण

		schedule_work(&dp->work);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&dp->con->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा typec_alपंचांगode_ops ucsi_displayport_ops = अणु
	.enter = ucsi_displayport_enter,
	.निकास = ucsi_displayport_निकास,
	.vdm = ucsi_displayport_vdm,
पूर्ण;

अटल व्योम ucsi_displayport_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ucsi_dp *dp = container_of(work, काष्ठा ucsi_dp, work);
	पूर्णांक ret;

	mutex_lock(&dp->con->lock);

	ret = typec_alपंचांगode_vdm(dp->alt, dp->header,
				dp->vकरो_data, dp->vकरो_size);
	अगर (ret)
		dev_err(&dp->alt->dev, "VDM 0x%x failed\n", dp->header);

	dp->vकरो_data = शून्य;
	dp->vकरो_size = 0;
	dp->header = 0;

	mutex_unlock(&dp->con->lock);
पूर्ण

व्योम ucsi_displayport_हटाओ_partner(काष्ठा typec_alपंचांगode *alt)
अणु
	काष्ठा ucsi_dp *dp;

	अगर (!alt)
		वापस;

	dp = typec_alपंचांगode_get_drvdata(alt);
	अगर (!dp)
		वापस;

	dp->data.conf = 0;
	dp->data.status = 0;
	dp->initialized = false;
पूर्ण

काष्ठा typec_alपंचांगode *ucsi_रेजिस्टर_displayport(काष्ठा ucsi_connector *con,
						bool override, पूर्णांक offset,
						काष्ठा typec_alपंचांगode_desc *desc)
अणु
	u8 all_assignments = BIT(DP_PIN_ASSIGN_C) | BIT(DP_PIN_ASSIGN_D) |
			     BIT(DP_PIN_ASSIGN_E);
	काष्ठा typec_alपंचांगode *alt;
	काष्ठा ucsi_dp *dp;

	/* We can't rely on the firmware with the capabilities. */
	desc->vकरो |= DP_CAP_DP_SIGNALING | DP_CAP_RECEPTACLE;

	/* Claiming that we support all pin assignments */
	desc->vकरो |= all_assignments << 8;
	desc->vकरो |= all_assignments << 16;

	alt = typec_port_रेजिस्टर_alपंचांगode(con->port, desc);
	अगर (IS_ERR(alt))
		वापस alt;

	dp = devm_kzalloc(&alt->dev, माप(*dp), GFP_KERNEL);
	अगर (!dp) अणु
		typec_unरेजिस्टर_alपंचांगode(alt);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	INIT_WORK(&dp->work, ucsi_displayport_work);
	dp->override = override;
	dp->offset = offset;
	dp->con = con;
	dp->alt = alt;

	alt->ops = &ucsi_displayport_ops;
	typec_alपंचांगode_set_drvdata(alt, dp);

	वापस alt;
पूर्ण
