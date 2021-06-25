<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Voltage Protocol
 *
 * Copyright (C) 2020-2021 ARM Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/scmi_protocol.h>

#समावेश "common.h"

#घोषणा VOLTAGE_DOMS_NUM_MASK		GENMASK(15, 0)
#घोषणा REMAINING_LEVELS_MASK		GENMASK(31, 16)
#घोषणा RETURNED_LEVELS_MASK		GENMASK(11, 0)

क्रमागत scmi_voltage_protocol_cmd अणु
	VOLTAGE_DOMAIN_ATTRIBUTES = 0x3,
	VOLTAGE_DESCRIBE_LEVELS = 0x4,
	VOLTAGE_CONFIG_SET = 0x5,
	VOLTAGE_CONFIG_GET = 0x6,
	VOLTAGE_LEVEL_SET = 0x7,
	VOLTAGE_LEVEL_GET = 0x8,
पूर्ण;

#घोषणा NUM_VOLTAGE_DOMAINS(x)	((u16)(FIELD_GET(VOLTAGE_DOMS_NUM_MASK, (x))))

काष्ठा scmi_msg_resp_करोमुख्य_attributes अणु
	__le32 attr;
	u8 name[SCMI_MAX_STR_SIZE];
पूर्ण;

काष्ठा scmi_msg_cmd_describe_levels अणु
	__le32 करोमुख्य_id;
	__le32 level_index;
पूर्ण;

काष्ठा scmi_msg_resp_describe_levels अणु
	__le32 flags;
#घोषणा NUM_REMAINING_LEVELS(f)	((u16)(FIELD_GET(REMAINING_LEVELS_MASK, (f))))
#घोषणा NUM_RETURNED_LEVELS(f)	((u16)(FIELD_GET(RETURNED_LEVELS_MASK, (f))))
#घोषणा SUPPORTS_SEGMENTED_LEVELS(f)	((f) & BIT(12))
	__le32 voltage[];
पूर्ण;

काष्ठा scmi_msg_cmd_config_set अणु
	__le32 करोमुख्य_id;
	__le32 config;
पूर्ण;

काष्ठा scmi_msg_cmd_level_set अणु
	__le32 करोमुख्य_id;
	__le32 flags;
	__le32 voltage_level;
पूर्ण;

काष्ठा voltage_info अणु
	अचिन्हित पूर्णांक version;
	अचिन्हित पूर्णांक num_करोमुख्यs;
	काष्ठा scmi_voltage_info *करोमुख्यs;
पूर्ण;

अटल पूर्णांक scmi_protocol_attributes_get(स्थिर काष्ठा scmi_protocol_handle *ph,
					काष्ठा voltage_info *vinfo)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;

	ret = ph->xops->xfer_get_init(ph, PROTOCOL_ATTRIBUTES, 0,
				      माप(__le32), &t);
	अगर (ret)
		वापस ret;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret)
		vinfo->num_करोमुख्यs =
			NUM_VOLTAGE_DOMAINS(get_unaligned_le32(t->rx.buf));

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_init_voltage_levels(काष्ठा device *dev,
				    काष्ठा scmi_voltage_info *v,
				    u32 num_वापसed, u32 num_reमुख्यing,
				    bool segmented)
अणु
	u32 num_levels;

	num_levels = num_वापसed + num_reमुख्यing;
	/*
	 * segmented levels entries are represented by a single triplet
	 * वापसed all in one go.
	 */
	अगर (!num_levels ||
	    (segmented && (num_reमुख्यing || num_वापसed != 3))) अणु
		dev_err(dev,
			"Invalid level descriptor(%d/%d/%d) for voltage dom %d\n",
			num_levels, num_वापसed, num_reमुख्यing, v->id);
		वापस -EINVAL;
	पूर्ण

	v->levels_uv = devm_kसुस्मृति(dev, num_levels, माप(u32), GFP_KERNEL);
	अगर (!v->levels_uv)
		वापस -ENOMEM;

	v->num_levels = num_levels;
	v->segmented = segmented;

	वापस 0;
पूर्ण

अटल पूर्णांक scmi_voltage_descriptors_get(स्थिर काष्ठा scmi_protocol_handle *ph,
					काष्ठा voltage_info *vinfo)
अणु
	पूर्णांक ret, करोm;
	काष्ठा scmi_xfer *td, *tl;
	काष्ठा device *dev = ph->dev;
	काष्ठा scmi_msg_resp_करोमुख्य_attributes *resp_करोm;
	काष्ठा scmi_msg_resp_describe_levels *resp_levels;

	ret = ph->xops->xfer_get_init(ph, VOLTAGE_DOMAIN_ATTRIBUTES,
				      माप(__le32), माप(*resp_करोm), &td);
	अगर (ret)
		वापस ret;
	resp_करोm = td->rx.buf;

	ret = ph->xops->xfer_get_init(ph, VOLTAGE_DESCRIBE_LEVELS,
				      माप(__le64), 0, &tl);
	अगर (ret)
		जाओ outd;
	resp_levels = tl->rx.buf;

	क्रम (करोm = 0; करोm < vinfo->num_करोमुख्यs; करोm++) अणु
		u32 desc_index = 0;
		u16 num_वापसed = 0, num_reमुख्यing = 0;
		काष्ठा scmi_msg_cmd_describe_levels *cmd;
		काष्ठा scmi_voltage_info *v;

		/* Retrieve करोमुख्य attributes at first ... */
		put_unaligned_le32(करोm, td->tx.buf);
		ret = ph->xops->करो_xfer(ph, td);
		/* Skip करोमुख्य on comms error */
		अगर (ret)
			जारी;

		v = vinfo->करोमुख्यs + करोm;
		v->id = करोm;
		v->attributes = le32_to_cpu(resp_करोm->attr);
		strlcpy(v->name, resp_करोm->name, SCMI_MAX_STR_SIZE);

		cmd = tl->tx.buf;
		/* ...then retrieve करोमुख्य levels descriptions */
		करो अणु
			u32 flags;
			पूर्णांक cnt;

			cmd->करोमुख्य_id = cpu_to_le32(v->id);
			cmd->level_index = desc_index;
			ret = ph->xops->करो_xfer(ph, tl);
			अगर (ret)
				अवरोध;

			flags = le32_to_cpu(resp_levels->flags);
			num_वापसed = NUM_RETURNED_LEVELS(flags);
			num_reमुख्यing = NUM_REMAINING_LEVELS(flags);

			/* Allocate space क्रम num_levels अगर not alपढ़ोy करोne */
			अगर (!v->num_levels) अणु
				ret = scmi_init_voltage_levels(dev, v,
							       num_वापसed,
							       num_reमुख्यing,
					      SUPPORTS_SEGMENTED_LEVELS(flags));
				अगर (ret)
					अवरोध;
			पूर्ण

			अगर (desc_index + num_वापसed > v->num_levels) अणु
				dev_err(ph->dev,
					"No. of voltage levels can't exceed %d\n",
					v->num_levels);
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			क्रम (cnt = 0; cnt < num_वापसed; cnt++) अणु
				s32 val;

				val =
				    (s32)le32_to_cpu(resp_levels->voltage[cnt]);
				v->levels_uv[desc_index + cnt] = val;
				अगर (val < 0)
					v->negative_volts_allowed = true;
			पूर्ण

			desc_index += num_वापसed;

			ph->xops->reset_rx_to_maxsz(ph, tl);
			/* check both to aव्योम infinite loop due to buggy fw */
		पूर्ण जबतक (num_वापसed && num_reमुख्यing);

		अगर (ret) अणु
			v->num_levels = 0;
			devm_kमुक्त(dev, v->levels_uv);
		पूर्ण

		ph->xops->reset_rx_to_maxsz(ph, td);
	पूर्ण

	ph->xops->xfer_put(ph, tl);
outd:
	ph->xops->xfer_put(ph, td);

	वापस ret;
पूर्ण

अटल पूर्णांक __scmi_voltage_get_u32(स्थिर काष्ठा scmi_protocol_handle *ph,
				  u8 cmd_id, u32 करोमुख्य_id, u32 *value)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा voltage_info *vinfo = ph->get_priv(ph);

	अगर (करोमुख्य_id >= vinfo->num_करोमुख्यs)
		वापस -EINVAL;

	ret = ph->xops->xfer_get_init(ph, cmd_id, माप(__le32), 0, &t);
	अगर (ret)
		वापस ret;

	put_unaligned_le32(करोमुख्य_id, t->tx.buf);
	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret)
		*value = get_unaligned_le32(t->rx.buf);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_voltage_config_set(स्थिर काष्ठा scmi_protocol_handle *ph,
				   u32 करोमुख्य_id, u32 config)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा voltage_info *vinfo = ph->get_priv(ph);
	काष्ठा scmi_msg_cmd_config_set *cmd;

	अगर (करोमुख्य_id >= vinfo->num_करोमुख्यs)
		वापस -EINVAL;

	ret = ph->xops->xfer_get_init(ph, VOLTAGE_CONFIG_SET,
				     माप(*cmd), 0, &t);
	अगर (ret)
		वापस ret;

	cmd = t->tx.buf;
	cmd->करोमुख्य_id = cpu_to_le32(करोमुख्य_id);
	cmd->config = cpu_to_le32(config & GENMASK(3, 0));

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_voltage_config_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				   u32 करोमुख्य_id, u32 *config)
अणु
	वापस __scmi_voltage_get_u32(ph, VOLTAGE_CONFIG_GET,
				      करोमुख्य_id, config);
पूर्ण

अटल पूर्णांक scmi_voltage_level_set(स्थिर काष्ठा scmi_protocol_handle *ph,
				  u32 करोमुख्य_id, u32 flags, s32 volt_uV)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा voltage_info *vinfo = ph->get_priv(ph);
	काष्ठा scmi_msg_cmd_level_set *cmd;

	अगर (करोमुख्य_id >= vinfo->num_करोमुख्यs)
		वापस -EINVAL;

	ret = ph->xops->xfer_get_init(ph, VOLTAGE_LEVEL_SET,
				      माप(*cmd), 0, &t);
	अगर (ret)
		वापस ret;

	cmd = t->tx.buf;
	cmd->करोमुख्य_id = cpu_to_le32(करोमुख्य_id);
	cmd->flags = cpu_to_le32(flags);
	cmd->voltage_level = cpu_to_le32(volt_uV);

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_voltage_level_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				  u32 करोमुख्य_id, s32 *volt_uV)
अणु
	वापस __scmi_voltage_get_u32(ph, VOLTAGE_LEVEL_GET,
				      करोमुख्य_id, (u32 *)volt_uV);
पूर्ण

अटल स्थिर काष्ठा scmi_voltage_info * __must_check
scmi_voltage_info_get(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य_id)
अणु
	काष्ठा voltage_info *vinfo = ph->get_priv(ph);

	अगर (करोमुख्य_id >= vinfo->num_करोमुख्यs ||
	    !vinfo->करोमुख्यs[करोमुख्य_id].num_levels)
		वापस शून्य;

	वापस vinfo->करोमुख्यs + करोमुख्य_id;
पूर्ण

अटल पूर्णांक scmi_voltage_करोमुख्यs_num_get(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	काष्ठा voltage_info *vinfo = ph->get_priv(ph);

	वापस vinfo->num_करोमुख्यs;
पूर्ण

अटल काष्ठा scmi_voltage_proto_ops voltage_proto_ops = अणु
	.num_करोमुख्यs_get = scmi_voltage_करोमुख्यs_num_get,
	.info_get = scmi_voltage_info_get,
	.config_set = scmi_voltage_config_set,
	.config_get = scmi_voltage_config_get,
	.level_set = scmi_voltage_level_set,
	.level_get = scmi_voltage_level_get,
पूर्ण;

अटल पूर्णांक scmi_voltage_protocol_init(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	पूर्णांक ret;
	u32 version;
	काष्ठा voltage_info *vinfo;

	ret = ph->xops->version_get(ph, &version);
	अगर (ret)
		वापस ret;

	dev_dbg(ph->dev, "Voltage Version %d.%d\n",
		PROTOCOL_REV_MAJOR(version), PROTOCOL_REV_MINOR(version));

	vinfo = devm_kzalloc(ph->dev, माप(*vinfo), GFP_KERNEL);
	अगर (!vinfo)
		वापस -ENOMEM;
	vinfo->version = version;

	ret = scmi_protocol_attributes_get(ph, vinfo);
	अगर (ret)
		वापस ret;

	अगर (vinfo->num_करोमुख्यs) अणु
		vinfo->करोमुख्यs = devm_kसुस्मृति(ph->dev, vinfo->num_करोमुख्यs,
					      माप(*vinfo->करोमुख्यs),
					      GFP_KERNEL);
		अगर (!vinfo->करोमुख्यs)
			वापस -ENOMEM;
		ret = scmi_voltage_descriptors_get(ph, vinfo);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		dev_warn(ph->dev, "No Voltage domains found.\n");
	पूर्ण

	वापस ph->set_priv(ph, vinfo);
पूर्ण

अटल स्थिर काष्ठा scmi_protocol scmi_voltage = अणु
	.id = SCMI_PROTOCOL_VOLTAGE,
	.owner = THIS_MODULE,
	.instance_init = &scmi_voltage_protocol_init,
	.ops = &voltage_proto_ops,
पूर्ण;

DEFINE_SCMI_PROTOCOL_REGISTER_UNREGISTER(voltage, scmi_voltage)
