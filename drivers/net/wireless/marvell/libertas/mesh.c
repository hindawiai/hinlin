<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/kfअगरo.h>
#समावेश <net/cfg80211.h>

#समावेश "mesh.h"
#समावेश "decl.h"
#समावेश "cmd.h"


अटल पूर्णांक lbs_add_mesh(काष्ठा lbs_निजी *priv);

/***************************************************************************
 * Mesh command handling
 */

अटल पूर्णांक lbs_mesh_access(काष्ठा lbs_निजी *priv, uपूर्णांक16_t cmd_action,
		    काष्ठा cmd_ds_mesh_access *cmd)
अणु
	पूर्णांक ret;

	cmd->hdr.command = cpu_to_le16(CMD_MESH_ACCESS);
	cmd->hdr.size = cpu_to_le16(माप(*cmd));
	cmd->hdr.result = 0;

	cmd->action = cpu_to_le16(cmd_action);

	ret = lbs_cmd_with_response(priv, CMD_MESH_ACCESS, cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक __lbs_mesh_config_send(काष्ठा lbs_निजी *priv,
				  काष्ठा cmd_ds_mesh_config *cmd,
				  uपूर्णांक16_t action, uपूर्णांक16_t type)
अणु
	पूर्णांक ret;
	u16 command = CMD_MESH_CONFIG_OLD;

	/*
	 * Command id is 0xac क्रम v10 FW aदीर्घ with mesh पूर्णांकerface
	 * id in bits 14-13-12.
	 */
	अगर (priv->mesh_tlv == TLV_TYPE_MESH_ID)
		command = CMD_MESH_CONFIG |
			  (MESH_IFACE_ID << MESH_IFACE_BIT_OFFSET);

	cmd->hdr.command = cpu_to_le16(command);
	cmd->hdr.size = cpu_to_le16(माप(काष्ठा cmd_ds_mesh_config));
	cmd->hdr.result = 0;

	cmd->type = cpu_to_le16(type);
	cmd->action = cpu_to_le16(action);

	ret = lbs_cmd_with_response(priv, command, cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक lbs_mesh_config_send(काष्ठा lbs_निजी *priv,
			 काष्ठा cmd_ds_mesh_config *cmd,
			 uपूर्णांक16_t action, uपूर्णांक16_t type)
अणु
	पूर्णांक ret;

	अगर (!(priv->fwcapinfo & FW_CAPINFO_PERSISTENT_CONFIG))
		वापस -EOPNOTSUPP;

	ret = __lbs_mesh_config_send(priv, cmd, action, type);
	वापस ret;
पूर्ण

/* This function is the CMD_MESH_CONFIG legacy function.  It only handles the
 * START and STOP actions.  The extended actions supported by CMD_MESH_CONFIG
 * are all handled by preparing a काष्ठा cmd_ds_mesh_config and passing it to
 * lbs_mesh_config_send.
 */
अटल पूर्णांक lbs_mesh_config(काष्ठा lbs_निजी *priv, uपूर्णांक16_t action,
		uपूर्णांक16_t chan)
अणु
	काष्ठा wireless_dev *mesh_wdev;
	काष्ठा cmd_ds_mesh_config cmd;
	काष्ठा mrvl_meshie *ie;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.channel = cpu_to_le16(chan);
	ie = (काष्ठा mrvl_meshie *)cmd.data;

	चयन (action) अणु
	हाल CMD_ACT_MESH_CONFIG_START:
		ie->id = WLAN_EID_VENDOR_SPECIFIC;
		ie->val.oui[0] = 0x00;
		ie->val.oui[1] = 0x50;
		ie->val.oui[2] = 0x43;
		ie->val.type = MARVELL_MESH_IE_TYPE;
		ie->val.subtype = MARVELL_MESH_IE_SUBTYPE;
		ie->val.version = MARVELL_MESH_IE_VERSION;
		ie->val.active_protocol_id = MARVELL_MESH_PROTO_ID_HWMP;
		ie->val.active_metric_id = MARVELL_MESH_METRIC_ID;
		ie->val.mesh_capability = MARVELL_MESH_CAPABILITY;

		अगर (priv->mesh_dev) अणु
			mesh_wdev = priv->mesh_dev->ieee80211_ptr;
			ie->val.mesh_id_len = mesh_wdev->mesh_id_up_len;
			स_नकल(ie->val.mesh_id, mesh_wdev->ssid,
						mesh_wdev->mesh_id_up_len);
		पूर्ण

		ie->len = माप(काष्ठा mrvl_meshie_val) -
			IEEE80211_MAX_SSID_LEN + ie->val.mesh_id_len;

		cmd.length = cpu_to_le16(माप(काष्ठा mrvl_meshie_val));
		अवरोध;
	हाल CMD_ACT_MESH_CONFIG_STOP:
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	lbs_deb_cmd("mesh config action %d type %x channel %d SSID %*pE\n",
		    action, priv->mesh_tlv, chan, ie->val.mesh_id_len,
		    ie->val.mesh_id);

	वापस __lbs_mesh_config_send(priv, &cmd, action, priv->mesh_tlv);
पूर्ण

पूर्णांक lbs_mesh_set_channel(काष्ठा lbs_निजी *priv, u8 channel)
अणु
	priv->mesh_channel = channel;
	वापस lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_START, channel);
पूर्ण

अटल uपूर्णांक16_t lbs_mesh_get_channel(काष्ठा lbs_निजी *priv)
अणु
	वापस priv->mesh_channel ?: 1;
पूर्ण

/***************************************************************************
 * Mesh sysfs support
 */

/*
 * Attributes exported through sysfs
 */

/**
 * lbs_anycast_get - Get function क्रम sysfs attribute anycast_mask
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer where data will be वापसed
 */
अटल sमाप_प्रकार lbs_anycast_get(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर * buf)
अणु
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	काष्ठा cmd_ds_mesh_access mesh_access;
	पूर्णांक ret;

	स_रखो(&mesh_access, 0, माप(mesh_access));

	ret = lbs_mesh_access(priv, CMD_ACT_MESH_GET_ANYCAST, &mesh_access);
	अगर (ret)
		वापस ret;

	वापस snम_लिखो(buf, 12, "0x%X\n", le32_to_cpu(mesh_access.data[0]));
पूर्ण

/**
 * lbs_anycast_set - Set function क्रम sysfs attribute anycast_mask
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer that contains new attribute value
 * @count: size of buffer
 */
अटल sमाप_प्रकार lbs_anycast_set(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर * buf, माप_प्रकार count)
अणु
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	काष्ठा cmd_ds_mesh_access mesh_access;
	uपूर्णांक32_t datum;
	पूर्णांक ret;

	स_रखो(&mesh_access, 0, माप(mesh_access));
	माला_पूछो(buf, "%x", &datum);
	mesh_access.data[0] = cpu_to_le32(datum);

	ret = lbs_mesh_access(priv, CMD_ACT_MESH_SET_ANYCAST, &mesh_access);
	अगर (ret)
		वापस ret;

	वापस म_माप(buf);
पूर्ण

/**
 * lbs_prb_rsp_limit_get - Get function क्रम sysfs attribute prb_rsp_limit
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer where data will be वापसed
 */
अटल sमाप_प्रकार lbs_prb_rsp_limit_get(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	काष्ठा cmd_ds_mesh_access mesh_access;
	पूर्णांक ret;
	u32 retry_limit;

	स_रखो(&mesh_access, 0, माप(mesh_access));
	mesh_access.data[0] = cpu_to_le32(CMD_ACT_GET);

	ret = lbs_mesh_access(priv, CMD_ACT_MESH_SET_GET_PRB_RSP_LIMIT,
			&mesh_access);
	अगर (ret)
		वापस ret;

	retry_limit = le32_to_cpu(mesh_access.data[1]);
	वापस snम_लिखो(buf, 10, "%d\n", retry_limit);
पूर्ण

/**
 * lbs_prb_rsp_limit_set - Set function क्रम sysfs attribute prb_rsp_limit
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer that contains new attribute value
 * @count: size of buffer
 */
अटल sमाप_प्रकार lbs_prb_rsp_limit_set(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	काष्ठा cmd_ds_mesh_access mesh_access;
	पूर्णांक ret;
	अचिन्हित दीर्घ retry_limit;

	स_रखो(&mesh_access, 0, माप(mesh_access));
	mesh_access.data[0] = cpu_to_le32(CMD_ACT_SET);

	ret = kम_से_अदीर्घ(buf, 10, &retry_limit);
	अगर (ret)
		वापस ret;
	अगर (retry_limit > 15)
		वापस -ENOTSUPP;

	mesh_access.data[1] = cpu_to_le32(retry_limit);

	ret = lbs_mesh_access(priv, CMD_ACT_MESH_SET_GET_PRB_RSP_LIMIT,
			&mesh_access);
	अगर (ret)
		वापस ret;

	वापस म_माप(buf);
पूर्ण

/**
 * lbs_mesh_get - Get function क्रम sysfs attribute mesh
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer where data will be वापसed
 */
अटल sमाप_प्रकार lbs_mesh_get(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर * buf)
अणु
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	वापस snम_लिखो(buf, 5, "0x%X\n", !!priv->mesh_dev);
पूर्ण

/**
 * lbs_mesh_set - Set function क्रम sysfs attribute mesh
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer that contains new attribute value
 * @count: size of buffer
 */
अटल sमाप_प्रकार lbs_mesh_set(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर * buf, माप_प्रकार count)
अणु
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	पूर्णांक enable;

	माला_पूछो(buf, "%x", &enable);
	enable = !!enable;
	अगर (enable == !!priv->mesh_dev)
		वापस count;

	अगर (enable)
		lbs_add_mesh(priv);
	अन्यथा
		lbs_हटाओ_mesh(priv);

	वापस count;
पूर्ण

/*
 * lbs_mesh attribute to be exported per ethX पूर्णांकerface
 * through sysfs (/sys/class/net/ethX/lbs_mesh)
 */
अटल DEVICE_ATTR(lbs_mesh, 0644, lbs_mesh_get, lbs_mesh_set);

/*
 * anycast_mask attribute to be exported per mshX पूर्णांकerface
 * through sysfs (/sys/class/net/mshX/anycast_mask)
 */
अटल DEVICE_ATTR(anycast_mask, 0644, lbs_anycast_get, lbs_anycast_set);

/*
 * prb_rsp_limit attribute to be exported per mshX पूर्णांकerface
 * through sysfs (/sys/class/net/mshX/prb_rsp_limit)
 */
अटल DEVICE_ATTR(prb_rsp_limit, 0644, lbs_prb_rsp_limit_get,
		lbs_prb_rsp_limit_set);

अटल काष्ठा attribute *lbs_mesh_sysfs_entries[] = अणु
	&dev_attr_anycast_mask.attr,
	&dev_attr_prb_rsp_limit.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group lbs_mesh_attr_group = अणु
	.attrs = lbs_mesh_sysfs_entries,
पूर्ण;


/***************************************************************************
 * Persistent configuration support
 */

अटल पूर्णांक mesh_get_शेष_parameters(काष्ठा device *dev,
				       काष्ठा mrvl_mesh_शेषs *defs)
अणु
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	काष्ठा cmd_ds_mesh_config cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(काष्ठा cmd_ds_mesh_config));
	ret = lbs_mesh_config_send(priv, &cmd, CMD_ACT_MESH_CONFIG_GET,
				   CMD_TYPE_MESH_GET_DEFAULTS);

	अगर (ret)
		वापस -EOPNOTSUPP;

	स_नकल(defs, &cmd.data[0], माप(काष्ठा mrvl_mesh_शेषs));

	वापस 0;
पूर्ण

/**
 * bootflag_get - Get function क्रम sysfs attribute bootflag
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer where data will be वापसed
 */
अटल sमाप_प्रकार bootflag_get(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mrvl_mesh_शेषs defs;
	पूर्णांक ret;

	ret = mesh_get_शेष_parameters(dev, &defs);

	अगर (ret)
		वापस ret;

	वापस snम_लिखो(buf, 12, "%d\n", le32_to_cpu(defs.bootflag));
पूर्ण

/**
 * bootflag_set - Set function क्रम sysfs attribute bootflag
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer that contains new attribute value
 * @count: size of buffer
 */
अटल sमाप_प्रकार bootflag_set(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	काष्ठा cmd_ds_mesh_config cmd;
	uपूर्णांक32_t datum;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	ret = माला_पूछो(buf, "%d", &datum);
	अगर ((ret != 1) || (datum > 1))
		वापस -EINVAL;

	*((__le32 *)&cmd.data[0]) = cpu_to_le32(!!datum);
	cmd.length = cpu_to_le16(माप(uपूर्णांक32_t));
	ret = lbs_mesh_config_send(priv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_BOOTFLAG);
	अगर (ret)
		वापस ret;

	वापस म_माप(buf);
पूर्ण

/**
 * bootसमय_get - Get function क्रम sysfs attribute bootसमय
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer where data will be वापसed
 */
अटल sमाप_प्रकार bootसमय_get(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mrvl_mesh_शेषs defs;
	पूर्णांक ret;

	ret = mesh_get_शेष_parameters(dev, &defs);

	अगर (ret)
		वापस ret;

	वापस snम_लिखो(buf, 12, "%d\n", defs.bootसमय);
पूर्ण

/**
 * bootसमय_set - Set function क्रम sysfs attribute bootसमय
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer that contains new attribute value
 * @count: size of buffer
 */
अटल sमाप_प्रकार bootसमय_set(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	काष्ठा cmd_ds_mesh_config cmd;
	uपूर्णांक32_t datum;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	ret = माला_पूछो(buf, "%d", &datum);
	अगर ((ret != 1) || (datum > 255))
		वापस -EINVAL;

	/* A too small boot समय will result in the device booting पूर्णांकo
	 * standalone (no-host) mode beक्रमe the host can take control of it,
	 * so the change will be hard to revert.  This may be a desired
	 * feature (e.g to configure a very fast boot समय क्रम devices that
	 * will not be attached to a host), but dangerous.  So I'm enक्रमcing a
	 * lower limit of 20 seconds:  हटाओ and recompile the driver अगर this
	 * करोes not work क्रम you.
	 */
	datum = (datum < 20) ? 20 : datum;
	cmd.data[0] = datum;
	cmd.length = cpu_to_le16(माप(uपूर्णांक8_t));
	ret = lbs_mesh_config_send(priv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_BOOTTIME);
	अगर (ret)
		वापस ret;

	वापस म_माप(buf);
पूर्ण

/**
 * channel_get - Get function क्रम sysfs attribute channel
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer where data will be वापसed
 */
अटल sमाप_प्रकार channel_get(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mrvl_mesh_शेषs defs;
	पूर्णांक ret;

	ret = mesh_get_शेष_parameters(dev, &defs);

	अगर (ret)
		वापस ret;

	वापस snम_लिखो(buf, 12, "%d\n", le16_to_cpu(defs.channel));
पूर्ण

/**
 * channel_set - Set function क्रम sysfs attribute channel
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer that contains new attribute value
 * @count: size of buffer
 */
अटल sमाप_प्रकार channel_set(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	काष्ठा cmd_ds_mesh_config cmd;
	uपूर्णांक32_t datum;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	ret = माला_पूछो(buf, "%d", &datum);
	अगर (ret != 1 || datum < 1 || datum > 11)
		वापस -EINVAL;

	*((__le16 *)&cmd.data[0]) = cpu_to_le16(datum);
	cmd.length = cpu_to_le16(माप(uपूर्णांक16_t));
	ret = lbs_mesh_config_send(priv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_DEF_CHANNEL);
	अगर (ret)
		वापस ret;

	वापस म_माप(buf);
पूर्ण

/**
 * mesh_id_get - Get function क्रम sysfs attribute mesh_id
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer where data will be वापसed
 */
अटल sमाप_प्रकार mesh_id_get(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा mrvl_mesh_शेषs defs;
	पूर्णांक ret;

	ret = mesh_get_शेष_parameters(dev, &defs);

	अगर (ret)
		वापस ret;

	अगर (defs.meshie.val.mesh_id_len > IEEE80211_MAX_SSID_LEN) अणु
		dev_err(dev, "inconsistent mesh ID length\n");
		defs.meshie.val.mesh_id_len = IEEE80211_MAX_SSID_LEN;
	पूर्ण

	स_नकल(buf, defs.meshie.val.mesh_id, defs.meshie.val.mesh_id_len);
	buf[defs.meshie.val.mesh_id_len] = '\n';
	buf[defs.meshie.val.mesh_id_len + 1] = '\0';

	वापस defs.meshie.val.mesh_id_len + 1;
पूर्ण

/**
 * mesh_id_set - Set function क्रम sysfs attribute mesh_id
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer that contains new attribute value
 * @count: size of buffer
 */
अटल sमाप_प्रकार mesh_id_set(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cmd_ds_mesh_config cmd;
	काष्ठा mrvl_mesh_शेषs defs;
	काष्ठा mrvl_meshie *ie;
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	पूर्णांक len;
	पूर्णांक ret;

	अगर (count < 2 || count > IEEE80211_MAX_SSID_LEN + 1)
		वापस -EINVAL;

	स_रखो(&cmd, 0, माप(काष्ठा cmd_ds_mesh_config));
	ie = (काष्ठा mrvl_meshie *) &cmd.data[0];

	/* fetch all other Inक्रमmation Element parameters */
	ret = mesh_get_शेष_parameters(dev, &defs);

	cmd.length = cpu_to_le16(माप(काष्ठा mrvl_meshie));

	/* transfer IE elements */
	स_नकल(ie, &defs.meshie, माप(काष्ठा mrvl_meshie));

	len = count - 1;
	स_नकल(ie->val.mesh_id, buf, len);
	/* SSID len */
	ie->val.mesh_id_len = len;
	/* IE len */
	ie->len = माप(काष्ठा mrvl_meshie_val) - IEEE80211_MAX_SSID_LEN + len;

	ret = lbs_mesh_config_send(priv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_MESH_IE);
	अगर (ret)
		वापस ret;

	वापस म_माप(buf);
पूर्ण

/**
 * protocol_id_get - Get function क्रम sysfs attribute protocol_id
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer where data will be वापसed
 */
अटल sमाप_प्रकार protocol_id_get(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mrvl_mesh_शेषs defs;
	पूर्णांक ret;

	ret = mesh_get_शेष_parameters(dev, &defs);

	अगर (ret)
		वापस ret;

	वापस snम_लिखो(buf, 5, "%d\n", defs.meshie.val.active_protocol_id);
पूर्ण

/**
 * protocol_id_set - Set function क्रम sysfs attribute protocol_id
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer that contains new attribute value
 * @count: size of buffer
 */
अटल sमाप_प्रकार protocol_id_set(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cmd_ds_mesh_config cmd;
	काष्ठा mrvl_mesh_शेषs defs;
	काष्ठा mrvl_meshie *ie;
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	uपूर्णांक32_t datum;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	ret = माला_पूछो(buf, "%d", &datum);
	अगर ((ret != 1) || (datum > 255))
		वापस -EINVAL;

	/* fetch all other Inक्रमmation Element parameters */
	ret = mesh_get_शेष_parameters(dev, &defs);

	cmd.length = cpu_to_le16(माप(काष्ठा mrvl_meshie));

	/* transfer IE elements */
	ie = (काष्ठा mrvl_meshie *) &cmd.data[0];
	स_नकल(ie, &defs.meshie, माप(काष्ठा mrvl_meshie));
	/* update protocol id */
	ie->val.active_protocol_id = datum;

	ret = lbs_mesh_config_send(priv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_MESH_IE);
	अगर (ret)
		वापस ret;

	वापस म_माप(buf);
पूर्ण

/**
 * metric_id_get - Get function क्रम sysfs attribute metric_id
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer where data will be वापसed
 */
अटल sमाप_प्रकार metric_id_get(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mrvl_mesh_शेषs defs;
	पूर्णांक ret;

	ret = mesh_get_शेष_parameters(dev, &defs);

	अगर (ret)
		वापस ret;

	वापस snम_लिखो(buf, 5, "%d\n", defs.meshie.val.active_metric_id);
पूर्ण

/**
 * metric_id_set - Set function क्रम sysfs attribute metric_id
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer that contains new attribute value
 * @count: size of buffer
 */
अटल sमाप_प्रकार metric_id_set(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cmd_ds_mesh_config cmd;
	काष्ठा mrvl_mesh_शेषs defs;
	काष्ठा mrvl_meshie *ie;
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	uपूर्णांक32_t datum;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	ret = माला_पूछो(buf, "%d", &datum);
	अगर ((ret != 1) || (datum > 255))
		वापस -EINVAL;

	/* fetch all other Inक्रमmation Element parameters */
	ret = mesh_get_शेष_parameters(dev, &defs);

	cmd.length = cpu_to_le16(माप(काष्ठा mrvl_meshie));

	/* transfer IE elements */
	ie = (काष्ठा mrvl_meshie *) &cmd.data[0];
	स_नकल(ie, &defs.meshie, माप(काष्ठा mrvl_meshie));
	/* update metric id */
	ie->val.active_metric_id = datum;

	ret = lbs_mesh_config_send(priv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_MESH_IE);
	अगर (ret)
		वापस ret;

	वापस म_माप(buf);
पूर्ण

/**
 * capability_get - Get function क्रम sysfs attribute capability
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer where data will be वापसed
 */
अटल sमाप_प्रकार capability_get(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mrvl_mesh_शेषs defs;
	पूर्णांक ret;

	ret = mesh_get_शेष_parameters(dev, &defs);

	अगर (ret)
		वापस ret;

	वापस snम_लिखो(buf, 5, "%d\n", defs.meshie.val.mesh_capability);
पूर्ण

/**
 * capability_set - Set function क्रम sysfs attribute capability
 * @dev: the &काष्ठा device
 * @attr: device attributes
 * @buf: buffer that contains new attribute value
 * @count: size of buffer
 */
अटल sमाप_प्रकार capability_set(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cmd_ds_mesh_config cmd;
	काष्ठा mrvl_mesh_शेषs defs;
	काष्ठा mrvl_meshie *ie;
	काष्ठा lbs_निजी *priv = to_net_dev(dev)->ml_priv;
	uपूर्णांक32_t datum;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	ret = माला_पूछो(buf, "%d", &datum);
	अगर ((ret != 1) || (datum > 255))
		वापस -EINVAL;

	/* fetch all other Inक्रमmation Element parameters */
	ret = mesh_get_शेष_parameters(dev, &defs);

	cmd.length = cpu_to_le16(माप(काष्ठा mrvl_meshie));

	/* transfer IE elements */
	ie = (काष्ठा mrvl_meshie *) &cmd.data[0];
	स_नकल(ie, &defs.meshie, माप(काष्ठा mrvl_meshie));
	/* update value */
	ie->val.mesh_capability = datum;

	ret = lbs_mesh_config_send(priv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_MESH_IE);
	अगर (ret)
		वापस ret;

	वापस म_माप(buf);
पूर्ण


अटल DEVICE_ATTR(bootflag, 0644, bootflag_get, bootflag_set);
अटल DEVICE_ATTR(bootसमय, 0644, bootसमय_get, bootसमय_set);
अटल DEVICE_ATTR(channel, 0644, channel_get, channel_set);
अटल DEVICE_ATTR(mesh_id, 0644, mesh_id_get, mesh_id_set);
अटल DEVICE_ATTR(protocol_id, 0644, protocol_id_get, protocol_id_set);
अटल DEVICE_ATTR(metric_id, 0644, metric_id_get, metric_id_set);
अटल DEVICE_ATTR(capability, 0644, capability_get, capability_set);

अटल काष्ठा attribute *boot_opts_attrs[] = अणु
	&dev_attr_bootflag.attr,
	&dev_attr_bootसमय.attr,
	&dev_attr_channel.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group boot_opts_group = अणु
	.name = "boot_options",
	.attrs = boot_opts_attrs,
पूर्ण;

अटल काष्ठा attribute *mesh_ie_attrs[] = अणु
	&dev_attr_mesh_id.attr,
	&dev_attr_protocol_id.attr,
	&dev_attr_metric_id.attr,
	&dev_attr_capability.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mesh_ie_group = अणु
	.name = "mesh_ie",
	.attrs = mesh_ie_attrs,
पूर्ण;


/***************************************************************************
 * Initializing and starting, stopping mesh
 */

/*
 * Check mesh FW version and appropriately send the mesh start
 * command
 */
व्योम lbs_init_mesh(काष्ठा lbs_निजी *priv)
अणु
	/* Determine mesh_fw_ver from fwrelease and fwcapinfo */
	/* 5.0.16p0 9.0.0.p0 is known to NOT support any mesh */
	/* 5.110.22 have mesh command with 0xa3 command id */
	/* 10.0.0.p0 FW brings in mesh config command with dअगरferent id */
	/* Check FW version MSB and initialize mesh_fw_ver */
	अगर (MRVL_FW_MAJOR_REV(priv->fwrelease) == MRVL_FW_V5) अणु
		/* Enable mesh, अगर supported, and work out which TLV it uses.
		   0x100 + 291 is an unofficial value used in 5.110.20.pXX
		   0x100 + 37 is the official value used in 5.110.21.pXX
		   but we check them in that order because 20.pXX करोesn't
		   give an error -- it just silently fails. */

		/* 5.110.20.pXX firmware will fail the command अगर the channel
		   करोesn't match the existing channel. But only अगर the TLV
		   is correct. If the channel is wrong, _BOTH_ versions will
		   give an error to 0x100+291, and allow 0x100+37 to succeed.
		   It's just that 5.110.20.pXX will not have करोne anything
		   useful */

		priv->mesh_tlv = TLV_TYPE_OLD_MESH_ID;
		अगर (lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_START, 1)) अणु
			priv->mesh_tlv = TLV_TYPE_MESH_ID;
			अगर (lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_START, 1))
				priv->mesh_tlv = 0;
		पूर्ण
	पूर्ण अन्यथा
	अगर ((MRVL_FW_MAJOR_REV(priv->fwrelease) >= MRVL_FW_V10) &&
		(priv->fwcapinfo & MESH_CAPINFO_ENABLE_MASK)) अणु
		/* 10.0.0.pXX new firmwares should succeed with TLV
		 * 0x100+37; Do not invoke command with old TLV.
		 */
		priv->mesh_tlv = TLV_TYPE_MESH_ID;
		अगर (lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_START, 1))
			priv->mesh_tlv = 0;
	पूर्ण

	/* Stop meshing until पूर्णांकerface is brought up */
	lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_STOP, 1);
पूर्ण

व्योम lbs_start_mesh(काष्ठा lbs_निजी *priv)
अणु
	lbs_add_mesh(priv);

	अगर (device_create_file(&priv->dev->dev, &dev_attr_lbs_mesh))
		netdev_err(priv->dev, "cannot register lbs_mesh attribute\n");
पूर्ण

पूर्णांक lbs_deinit_mesh(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->dev;
	पूर्णांक ret = 0;

	अगर (priv->mesh_tlv) अणु
		device_हटाओ_file(&dev->dev, &dev_attr_lbs_mesh);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण


/**
 * lbs_mesh_stop - बंद the mshX पूर्णांकerface
 *
 * @dev:	A poपूर्णांकer to &net_device काष्ठाure
 * वापसs:	0
 */
अटल पूर्णांक lbs_mesh_stop(काष्ठा net_device *dev)
अणु
	काष्ठा lbs_निजी *priv = dev->ml_priv;

	lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_STOP,
		lbs_mesh_get_channel(priv));

	spin_lock_irq(&priv->driver_lock);

	netअगर_stop_queue(dev);
	netअगर_carrier_off(dev);

	spin_unlock_irq(&priv->driver_lock);

	lbs_update_mcast(priv);
	अगर (!lbs_अगरace_active(priv))
		lbs_stop_अगरace(priv);

	वापस 0;
पूर्ण

/**
 * lbs_mesh_dev_खोलो - खोलो the mshX पूर्णांकerface
 *
 * @dev:	A poपूर्णांकer to &net_device काष्ठाure
 * वापसs:	0 or -EBUSY अगर monitor mode active
 */
अटल पूर्णांक lbs_mesh_dev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा lbs_निजी *priv = dev->ml_priv;
	पूर्णांक ret = 0;

	अगर (!priv->अगरace_running) अणु
		ret = lbs_start_अगरace(priv);
		अगर (ret)
			जाओ out;
	पूर्ण

	spin_lock_irq(&priv->driver_lock);

	अगर (priv->wdev->अगरtype == NL80211_IFTYPE_MONITOR) अणु
		ret = -EBUSY;
		spin_unlock_irq(&priv->driver_lock);
		जाओ out;
	पूर्ण

	netअगर_carrier_on(dev);

	अगर (!priv->tx_pending_len)
		netअगर_wake_queue(dev);

	spin_unlock_irq(&priv->driver_lock);

	ret = lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_START,
		lbs_mesh_get_channel(priv));

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops mesh_netdev_ops = अणु
	.nकरो_खोलो		= lbs_mesh_dev_खोलो,
	.nकरो_stop 		= lbs_mesh_stop,
	.nकरो_start_xmit		= lbs_hard_start_xmit,
	.nकरो_set_mac_address	= lbs_set_mac_address,
	.nकरो_set_rx_mode	= lbs_set_multicast_list,
पूर्ण;

/**
 * lbs_add_mesh - add mshX पूर्णांकerface
 *
 * @priv:	A poपूर्णांकer to the &काष्ठा lbs_निजी काष्ठाure
 * वापसs:	0 अगर successful, -X otherwise
 */
अटल पूर्णांक lbs_add_mesh(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा net_device *mesh_dev = शून्य;
	काष्ठा wireless_dev *mesh_wdev;
	पूर्णांक ret = 0;

	/* Allocate a भव mesh device */
	mesh_wdev = kzalloc(माप(काष्ठा wireless_dev), GFP_KERNEL);
	अगर (!mesh_wdev) अणु
		lbs_deb_mesh("init mshX wireless device failed\n");
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	mesh_dev = alloc_netdev(0, "msh%d", NET_NAME_UNKNOWN, ether_setup);
	अगर (!mesh_dev) अणु
		lbs_deb_mesh("init mshX device failed\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_wdev;
	पूर्ण

	mesh_wdev->अगरtype = NL80211_IFTYPE_MESH_POINT;
	mesh_wdev->wiphy = priv->wdev->wiphy;

	अगर (priv->mesh_tlv) अणु
		प्र_लिखो(mesh_wdev->ssid, "mesh");
		mesh_wdev->mesh_id_up_len = 4;
	पूर्ण

	mesh_wdev->netdev = mesh_dev;

	mesh_dev->ml_priv = priv;
	mesh_dev->ieee80211_ptr = mesh_wdev;
	priv->mesh_dev = mesh_dev;

	mesh_dev->netdev_ops = &mesh_netdev_ops;
	mesh_dev->ethtool_ops = &lbs_ethtool_ops;
	eth_hw_addr_inherit(mesh_dev, priv->dev);

	SET_NETDEV_DEV(priv->mesh_dev, priv->dev->dev.parent);

	mesh_dev->flags |= IFF_BROADCAST | IFF_MULTICAST;
	mesh_dev->sysfs_groups[0] = &lbs_mesh_attr_group;
	mesh_dev->sysfs_groups[1] = &boot_opts_group;
	mesh_dev->sysfs_groups[2] = &mesh_ie_group;

	/* Register भव mesh पूर्णांकerface */
	ret = रेजिस्टर_netdev(mesh_dev);
	अगर (ret) अणु
		pr_err("cannot register mshX virtual interface\n");
		जाओ err_मुक्त_netdev;
	पूर्ण

	/* Everything successful */
	ret = 0;
	जाओ करोne;

err_मुक्त_netdev:
	मुक्त_netdev(mesh_dev);

err_मुक्त_wdev:
	kमुक्त(mesh_wdev);

करोne:
	वापस ret;
पूर्ण

व्योम lbs_हटाओ_mesh(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा net_device *mesh_dev;

	mesh_dev = priv->mesh_dev;
	अगर (!mesh_dev)
		वापस;

	netअगर_stop_queue(mesh_dev);
	netअगर_carrier_off(mesh_dev);
	unरेजिस्टर_netdev(mesh_dev);
	priv->mesh_dev = शून्य;
	kमुक्त(mesh_dev->ieee80211_ptr);
	मुक्त_netdev(mesh_dev);
पूर्ण


/***************************************************************************
 * Sending and receiving
 */
काष्ठा net_device *lbs_mesh_set_dev(काष्ठा lbs_निजी *priv,
	काष्ठा net_device *dev, काष्ठा rxpd *rxpd)
अणु
	अगर (priv->mesh_dev) अणु
		अगर (priv->mesh_tlv == TLV_TYPE_OLD_MESH_ID) अणु
			अगर (rxpd->rx_control & RxPD_MESH_FRAME)
				dev = priv->mesh_dev;
		पूर्ण अन्यथा अगर (priv->mesh_tlv == TLV_TYPE_MESH_ID) अणु
			अगर (rxpd->u.bss.bss_num == MESH_IFACE_ID)
				dev = priv->mesh_dev;
		पूर्ण
	पूर्ण
	वापस dev;
पूर्ण


व्योम lbs_mesh_set_txpd(काष्ठा lbs_निजी *priv,
	काष्ठा net_device *dev, काष्ठा txpd *txpd)
अणु
	अगर (dev == priv->mesh_dev) अणु
		अगर (priv->mesh_tlv == TLV_TYPE_OLD_MESH_ID)
			txpd->tx_control |= cpu_to_le32(TxPD_MESH_FRAME);
		अन्यथा अगर (priv->mesh_tlv == TLV_TYPE_MESH_ID)
			txpd->u.bss.bss_num = MESH_IFACE_ID;
	पूर्ण
पूर्ण


/***************************************************************************
 * Ethtool related
 */

अटल स्थिर अक्षर mesh_stat_strings[MESH_STATS_NUM][ETH_GSTRING_LEN] = अणु
	"drop_duplicate_bcast",
	"drop_ttl_zero",
	"drop_no_fwd_route",
	"drop_no_buffers",
	"fwded_unicast_cnt",
	"fwded_bcast_cnt",
	"drop_blind_table",
	"tx_failed_cnt"
पूर्ण;

व्योम lbs_mesh_ethtool_get_stats(काष्ठा net_device *dev,
	काष्ठा ethtool_stats *stats, uपूर्णांक64_t *data)
अणु
	काष्ठा lbs_निजी *priv = dev->ml_priv;
	काष्ठा cmd_ds_mesh_access mesh_access;
	पूर्णांक ret;

	/* Get Mesh Statistics */
	ret = lbs_mesh_access(priv, CMD_ACT_MESH_GET_STATS, &mesh_access);

	अगर (ret) अणु
		स_रखो(data, 0, MESH_STATS_NUM*(माप(uपूर्णांक64_t)));
		वापस;
	पूर्ण

	priv->mstats.fwd_drop_rbt = le32_to_cpu(mesh_access.data[0]);
	priv->mstats.fwd_drop_ttl = le32_to_cpu(mesh_access.data[1]);
	priv->mstats.fwd_drop_noroute = le32_to_cpu(mesh_access.data[2]);
	priv->mstats.fwd_drop_nobuf = le32_to_cpu(mesh_access.data[3]);
	priv->mstats.fwd_unicast_cnt = le32_to_cpu(mesh_access.data[4]);
	priv->mstats.fwd_bcast_cnt = le32_to_cpu(mesh_access.data[5]);
	priv->mstats.drop_blind = le32_to_cpu(mesh_access.data[6]);
	priv->mstats.tx_failed_cnt = le32_to_cpu(mesh_access.data[7]);

	data[0] = priv->mstats.fwd_drop_rbt;
	data[1] = priv->mstats.fwd_drop_ttl;
	data[2] = priv->mstats.fwd_drop_noroute;
	data[3] = priv->mstats.fwd_drop_nobuf;
	data[4] = priv->mstats.fwd_unicast_cnt;
	data[5] = priv->mstats.fwd_bcast_cnt;
	data[6] = priv->mstats.drop_blind;
	data[7] = priv->mstats.tx_failed_cnt;
पूर्ण

पूर्णांक lbs_mesh_ethtool_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा lbs_निजी *priv = dev->ml_priv;

	अगर (sset == ETH_SS_STATS && dev == priv->mesh_dev)
		वापस MESH_STATS_NUM;

	वापस -EOPNOTSUPP;
पूर्ण

व्योम lbs_mesh_ethtool_get_strings(काष्ठा net_device *dev,
	uपूर्णांक32_t stringset, uपूर्णांक8_t *s)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(s, mesh_stat_strings, माप(mesh_stat_strings));
		अवरोध;
	पूर्ण
पूर्ण
