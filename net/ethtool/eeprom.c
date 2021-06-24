<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/ethtool.h>
#समावेश <linux/sfp.h>
#समावेश "netlink.h"
#समावेश "common.h"

काष्ठा eeprom_req_info अणु
	काष्ठा ethnl_req_info	base;
	u32			offset;
	u32			length;
	u8			page;
	u8			bank;
	u8			i2c_address;
पूर्ण;

काष्ठा eeprom_reply_data अणु
	काष्ठा ethnl_reply_data base;
	u32			length;
	u8			*data;
पूर्ण;

#घोषणा MODULE_EEPROM_REQINFO(__req_base) \
	container_of(__req_base, काष्ठा eeprom_req_info, base)

#घोषणा MODULE_EEPROM_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा eeprom_reply_data, base)

अटल पूर्णांक fallback_set_params(काष्ठा eeprom_req_info *request,
			       काष्ठा ethtool_modinfo *modinfo,
			       काष्ठा ethtool_eeprom *eeprom)
अणु
	u32 offset = request->offset;
	u32 length = request->length;

	अगर (request->page)
		offset = request->page * ETH_MODULE_EEPROM_PAGE_LEN + offset;

	अगर (modinfo->type == ETH_MODULE_SFF_8079 &&
	    request->i2c_address == 0x51)
		offset += ETH_MODULE_EEPROM_PAGE_LEN * 2;

	अगर (offset >= modinfo->eeprom_len)
		वापस -EINVAL;

	eeprom->cmd = ETHTOOL_GMODULEEEPROM;
	eeprom->len = length;
	eeprom->offset = offset;

	वापस 0;
पूर्ण

अटल पूर्णांक eeprom_fallback(काष्ठा eeprom_req_info *request,
			   काष्ठा eeprom_reply_data *reply,
			   काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev = reply->base.dev;
	काष्ठा ethtool_modinfo modinfo = अणु0पूर्ण;
	काष्ठा ethtool_eeprom eeprom = अणु0पूर्ण;
	u8 *data;
	पूर्णांक err;

	modinfo.cmd = ETHTOOL_GMODULEINFO;
	err = ethtool_get_module_info_call(dev, &modinfo);
	अगर (err < 0)
		वापस err;

	err = fallback_set_params(request, &modinfo, &eeprom);
	अगर (err < 0)
		वापस err;

	data = kदो_स्मृति(eeprom.len, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	err = ethtool_get_module_eeprom_call(dev, &eeprom, data);
	अगर (err < 0)
		जाओ err_out;

	reply->data = data;
	reply->length = eeprom.len;

	वापस 0;

err_out:
	kमुक्त(data);
	वापस err;
पूर्ण

अटल पूर्णांक get_module_eeprom_by_page(काष्ठा net_device *dev,
				     काष्ठा ethtool_module_eeprom *page_data,
				     काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;

	अगर (dev->sfp_bus)
		वापस sfp_get_module_eeprom_by_page(dev->sfp_bus, page_data, extack);

	अगर (ops->get_module_eeprom_by_page)
		वापस ops->get_module_eeprom_by_page(dev, page_data, extack);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक eeprom_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
			       काष्ठा ethnl_reply_data *reply_base,
			       काष्ठा genl_info *info)
अणु
	काष्ठा eeprom_reply_data *reply = MODULE_EEPROM_REPDATA(reply_base);
	काष्ठा eeprom_req_info *request = MODULE_EEPROM_REQINFO(req_base);
	काष्ठा ethtool_module_eeprom page_data = अणु0पूर्ण;
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	page_data.offset = request->offset;
	page_data.length = request->length;
	page_data.i2c_address = request->i2c_address;
	page_data.page = request->page;
	page_data.bank = request->bank;
	page_data.data = kदो_स्मृति(page_data.length, GFP_KERNEL);
	अगर (!page_data.data)
		वापस -ENOMEM;

	ret = ethnl_ops_begin(dev);
	अगर (ret)
		जाओ err_मुक्त;

	ret = get_module_eeprom_by_page(dev, &page_data, info->extack);
	अगर (ret < 0)
		जाओ err_ops;

	reply->length = ret;
	reply->data = page_data.data;

	ethnl_ops_complete(dev);
	वापस 0;

err_ops:
	ethnl_ops_complete(dev);
err_मुक्त:
	kमुक्त(page_data.data);

	अगर (ret == -EOPNOTSUPP)
		वापस eeprom_fallback(request, reply, info);
	वापस ret;
पूर्ण

अटल पूर्णांक eeprom_parse_request(काष्ठा ethnl_req_info *req_info, काष्ठा nlattr **tb,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा eeprom_req_info *request = MODULE_EEPROM_REQINFO(req_info);

	अगर (!tb[ETHTOOL_A_MODULE_EEPROM_OFFSET] ||
	    !tb[ETHTOOL_A_MODULE_EEPROM_LENGTH] ||
	    !tb[ETHTOOL_A_MODULE_EEPROM_PAGE] ||
	    !tb[ETHTOOL_A_MODULE_EEPROM_I2C_ADDRESS])
		वापस -EINVAL;

	request->i2c_address = nla_get_u8(tb[ETHTOOL_A_MODULE_EEPROM_I2C_ADDRESS]);
	request->offset = nla_get_u32(tb[ETHTOOL_A_MODULE_EEPROM_OFFSET]);
	request->length = nla_get_u32(tb[ETHTOOL_A_MODULE_EEPROM_LENGTH]);

	अगर (!request->length)
		वापस -EINVAL;

	/* The following set of conditions limit the API to only dump 1/2
	 * EEPROM page without crossing low page boundary located at offset 128.
	 * This means user may only request dumps of length limited to 128 from
	 * either low 128 bytes or high 128 bytes.
	 * For pages higher than 0 only high 128 bytes are accessible.
	 */
	request->page = nla_get_u8(tb[ETHTOOL_A_MODULE_EEPROM_PAGE]);
	अगर (request->page && request->offset < ETH_MODULE_EEPROM_PAGE_LEN) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb[ETHTOOL_A_MODULE_EEPROM_PAGE],
				    "reading from lower half page is allowed for page 0 only");
		वापस -EINVAL;
	पूर्ण

	अगर (request->offset < ETH_MODULE_EEPROM_PAGE_LEN &&
	    request->offset + request->length > ETH_MODULE_EEPROM_PAGE_LEN) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb[ETHTOOL_A_MODULE_EEPROM_LENGTH],
				    "reading cross half page boundary is illegal");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (request->offset >= ETH_MODULE_EEPROM_PAGE_LEN * 2) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb[ETHTOOL_A_MODULE_EEPROM_OFFSET],
				    "offset is out of bounds");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (request->offset + request->length > ETH_MODULE_EEPROM_PAGE_LEN * 2) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb[ETHTOOL_A_MODULE_EEPROM_LENGTH],
				    "reading cross page boundary is illegal");
		वापस -EINVAL;
	पूर्ण

	अगर (tb[ETHTOOL_A_MODULE_EEPROM_BANK])
		request->bank = nla_get_u8(tb[ETHTOOL_A_MODULE_EEPROM_BANK]);

	वापस 0;
पूर्ण

अटल पूर्णांक eeprom_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			     स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा eeprom_req_info *request = MODULE_EEPROM_REQINFO(req_base);

	वापस nla_total_size(माप(u8) * request->length); /* _EEPROM_DATA */
पूर्ण

अटल पूर्णांक eeprom_fill_reply(काष्ठा sk_buff *skb,
			     स्थिर काष्ठा ethnl_req_info *req_base,
			     स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	काष्ठा eeprom_reply_data *reply = MODULE_EEPROM_REPDATA(reply_base);

	वापस nla_put(skb, ETHTOOL_A_MODULE_EEPROM_DATA, reply->length, reply->data);
पूर्ण

अटल व्योम eeprom_cleanup_data(काष्ठा ethnl_reply_data *reply_base)
अणु
	काष्ठा eeprom_reply_data *reply = MODULE_EEPROM_REPDATA(reply_base);

	kमुक्त(reply->data);
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_module_eeprom_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_MODULE_EEPROM_GET,
	.reply_cmd		= ETHTOOL_MSG_MODULE_EEPROM_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_MODULE_EEPROM_HEADER,
	.req_info_size		= माप(काष्ठा eeprom_req_info),
	.reply_data_size	= माप(काष्ठा eeprom_reply_data),

	.parse_request		= eeprom_parse_request,
	.prepare_data		= eeprom_prepare_data,
	.reply_size		= eeprom_reply_size,
	.fill_reply		= eeprom_fill_reply,
	.cleanup_data		= eeprom_cleanup_data,
पूर्ण;

स्थिर काष्ठा nla_policy ethnl_module_eeprom_get_policy[] = अणु
	[ETHTOOL_A_MODULE_EEPROM_HEADER]	= NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_MODULE_EEPROM_OFFSET]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_MODULE_EEPROM_LENGTH]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_MODULE_EEPROM_PAGE]		= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_MODULE_EEPROM_BANK]		= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_MODULE_EEPROM_I2C_ADDRESS]	=
		NLA_POLICY_RANGE(NLA_U8, 0, ETH_MODULE_MAX_I2C_ADDRESS),
पूर्ण;

