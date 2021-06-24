<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt XDoमुख्य discovery protocol support
 *
 * Copyright (C) 2017, Intel Corporation
 * Authors: Michael Jamet <michael.jamet@पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/kmod.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pअक्रमom.h>
#समावेश <linux/utsname.h>
#समावेश <linux/uuid.h>
#समावेश <linux/workqueue.h>

#समावेश "tb.h"

#घोषणा XDOMAIN_DEFAULT_TIMEOUT			1000 /* ms */
#घोषणा XDOMAIN_UUID_RETRIES			10
#घोषणा XDOMAIN_PROPERTIES_RETRIES		10
#घोषणा XDOMAIN_PROPERTIES_CHANGED_RETRIES	10
#घोषणा XDOMAIN_BONDING_WAIT			100  /* ms */
#घोषणा XDOMAIN_DEFAULT_MAX_HOPID		15

काष्ठा xकरोमुख्य_request_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा tb_xdp_header *pkg;
	काष्ठा tb *tb;
पूर्ण;

अटल bool tb_xकरोमुख्य_enabled = true;
module_param_named(xकरोमुख्य, tb_xकरोमुख्य_enabled, bool, 0444);
MODULE_PARM_DESC(xकरोमुख्य, "allow XDomain protocol (default: true)");

/*
 * Serializes access to the properties and protocol handlers below. If
 * you need to take both this lock and the काष्ठा tb_xकरोमुख्य lock, take
 * this one first.
 */
अटल DEFINE_MUTEX(xकरोमुख्य_lock);

/* Properties exposed to the remote करोमुख्यs */
अटल काष्ठा tb_property_dir *xकरोमुख्य_property_dir;
अटल u32 xकरोमुख्य_property_block_gen;

/* Additional protocol handlers */
अटल LIST_HEAD(protocol_handlers);

/* UUID क्रम XDoमुख्य discovery protocol: b638d70e-42ff-40bb-97c2-90e2c0b2ff07 */
अटल स्थिर uuid_t tb_xdp_uuid =
	UUID_INIT(0xb638d70e, 0x42ff, 0x40bb,
		  0x97, 0xc2, 0x90, 0xe2, 0xc0, 0xb2, 0xff, 0x07);

bool tb_is_xकरोमुख्य_enabled(व्योम)
अणु
	वापस tb_xकरोमुख्य_enabled && tb_acpi_is_xकरोमुख्य_allowed();
पूर्ण

अटल bool tb_xकरोमुख्य_match(स्थिर काष्ठा tb_cfg_request *req,
			     स्थिर काष्ठा ctl_pkg *pkg)
अणु
	चयन (pkg->frame.eof) अणु
	हाल TB_CFG_PKG_ERROR:
		वापस true;

	हाल TB_CFG_PKG_XDOMAIN_RESP: अणु
		स्थिर काष्ठा tb_xdp_header *res_hdr = pkg->buffer;
		स्थिर काष्ठा tb_xdp_header *req_hdr = req->request;

		अगर (pkg->frame.size < req->response_size / 4)
			वापस false;

		/* Make sure route matches */
		अगर ((res_hdr->xd_hdr.route_hi & ~BIT(31)) !=
		     req_hdr->xd_hdr.route_hi)
			वापस false;
		अगर ((res_hdr->xd_hdr.route_lo) != req_hdr->xd_hdr.route_lo)
			वापस false;

		/* Check that the XDoमुख्य protocol matches */
		अगर (!uuid_equal(&res_hdr->uuid, &req_hdr->uuid))
			वापस false;

		वापस true;
	पूर्ण

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tb_xकरोमुख्य_copy(काष्ठा tb_cfg_request *req,
			    स्थिर काष्ठा ctl_pkg *pkg)
अणु
	स_नकल(req->response, pkg->buffer, req->response_size);
	req->result.err = 0;
	वापस true;
पूर्ण

अटल व्योम response_पढ़ोy(व्योम *data)
अणु
	tb_cfg_request_put(data);
पूर्ण

अटल पूर्णांक __tb_xकरोमुख्य_response(काष्ठा tb_ctl *ctl, स्थिर व्योम *response,
				 माप_प्रकार size, क्रमागत tb_cfg_pkg_type type)
अणु
	काष्ठा tb_cfg_request *req;

	req = tb_cfg_request_alloc();
	अगर (!req)
		वापस -ENOMEM;

	req->match = tb_xकरोमुख्य_match;
	req->copy = tb_xकरोमुख्य_copy;
	req->request = response;
	req->request_size = size;
	req->request_type = type;

	वापस tb_cfg_request(ctl, req, response_पढ़ोy, req);
पूर्ण

/**
 * tb_xकरोमुख्य_response() - Send a XDoमुख्य response message
 * @xd: XDoमुख्य to send the message
 * @response: Response to send
 * @size: Size of the response
 * @type: PDF type of the response
 *
 * This can be used to send a XDoमुख्य response message to the other
 * करोमुख्य. No response क्रम the message is expected.
 *
 * Return: %0 in हाल of success and negative त्रुटि_सं in हाल of failure
 */
पूर्णांक tb_xकरोमुख्य_response(काष्ठा tb_xकरोमुख्य *xd, स्थिर व्योम *response,
			माप_प्रकार size, क्रमागत tb_cfg_pkg_type type)
अणु
	वापस __tb_xकरोमुख्य_response(xd->tb->ctl, response, size, type);
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_response);

अटल पूर्णांक __tb_xकरोमुख्य_request(काष्ठा tb_ctl *ctl, स्थिर व्योम *request,
	माप_प्रकार request_size, क्रमागत tb_cfg_pkg_type request_type, व्योम *response,
	माप_प्रकार response_size, क्रमागत tb_cfg_pkg_type response_type,
	अचिन्हित पूर्णांक समयout_msec)
अणु
	काष्ठा tb_cfg_request *req;
	काष्ठा tb_cfg_result res;

	req = tb_cfg_request_alloc();
	अगर (!req)
		वापस -ENOMEM;

	req->match = tb_xकरोमुख्य_match;
	req->copy = tb_xकरोमुख्य_copy;
	req->request = request;
	req->request_size = request_size;
	req->request_type = request_type;
	req->response = response;
	req->response_size = response_size;
	req->response_type = response_type;

	res = tb_cfg_request_sync(ctl, req, समयout_msec);

	tb_cfg_request_put(req);

	वापस res.err == 1 ? -EIO : res.err;
पूर्ण

/**
 * tb_xकरोमुख्य_request() - Send a XDoमुख्य request
 * @xd: XDoमुख्य to send the request
 * @request: Request to send
 * @request_size: Size of the request in bytes
 * @request_type: PDF type of the request
 * @response: Response is copied here
 * @response_size: Expected size of the response in bytes
 * @response_type: Expected PDF type of the response
 * @समयout_msec: Timeout in milliseconds to रुको क्रम the response
 *
 * This function can be used to send XDoमुख्य control channel messages to
 * the other करोमुख्य. The function रुकोs until the response is received
 * or when समयout triggers. Whichever comes first.
 *
 * Return: %0 in हाल of success and negative त्रुटि_सं in हाल of failure
 */
पूर्णांक tb_xकरोमुख्य_request(काष्ठा tb_xकरोमुख्य *xd, स्थिर व्योम *request,
	माप_प्रकार request_size, क्रमागत tb_cfg_pkg_type request_type,
	व्योम *response, माप_प्रकार response_size,
	क्रमागत tb_cfg_pkg_type response_type, अचिन्हित पूर्णांक समयout_msec)
अणु
	वापस __tb_xकरोमुख्य_request(xd->tb->ctl, request, request_size,
				    request_type, response, response_size,
				    response_type, समयout_msec);
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_request);

अटल अंतरभूत व्योम tb_xdp_fill_header(काष्ठा tb_xdp_header *hdr, u64 route,
	u8 sequence, क्रमागत tb_xdp_type type, माप_प्रकार size)
अणु
	u32 length_sn;

	length_sn = (size - माप(hdr->xd_hdr)) / 4;
	length_sn |= (sequence << TB_XDOMAIN_SN_SHIFT) & TB_XDOMAIN_SN_MASK;

	hdr->xd_hdr.route_hi = upper_32_bits(route);
	hdr->xd_hdr.route_lo = lower_32_bits(route);
	hdr->xd_hdr.length_sn = length_sn;
	hdr->type = type;
	स_नकल(&hdr->uuid, &tb_xdp_uuid, माप(tb_xdp_uuid));
पूर्ण

अटल पूर्णांक tb_xdp_handle_error(स्थिर काष्ठा tb_xdp_header *hdr)
अणु
	स्थिर काष्ठा tb_xdp_error_response *error;

	अगर (hdr->type != ERROR_RESPONSE)
		वापस 0;

	error = (स्थिर काष्ठा tb_xdp_error_response *)hdr;

	चयन (error->error) अणु
	हाल ERROR_UNKNOWN_PACKET:
	हाल ERROR_UNKNOWN_DOMAIN:
		वापस -EIO;
	हाल ERROR_NOT_SUPPORTED:
		वापस -ENOTSUPP;
	हाल ERROR_NOT_READY:
		वापस -EAGAIN;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tb_xdp_uuid_request(काष्ठा tb_ctl *ctl, u64 route, पूर्णांक retry,
			       uuid_t *uuid)
अणु
	काष्ठा tb_xdp_uuid_response res;
	काष्ठा tb_xdp_uuid req;
	पूर्णांक ret;

	स_रखो(&req, 0, माप(req));
	tb_xdp_fill_header(&req.hdr, route, retry % 4, UUID_REQUEST,
			   माप(req));

	स_रखो(&res, 0, माप(res));
	ret = __tb_xकरोमुख्य_request(ctl, &req, माप(req),
				   TB_CFG_PKG_XDOMAIN_REQ, &res, माप(res),
				   TB_CFG_PKG_XDOMAIN_RESP,
				   XDOMAIN_DEFAULT_TIMEOUT);
	अगर (ret)
		वापस ret;

	ret = tb_xdp_handle_error(&res.hdr);
	अगर (ret)
		वापस ret;

	uuid_copy(uuid, &res.src_uuid);
	वापस 0;
पूर्ण

अटल पूर्णांक tb_xdp_uuid_response(काष्ठा tb_ctl *ctl, u64 route, u8 sequence,
				स्थिर uuid_t *uuid)
अणु
	काष्ठा tb_xdp_uuid_response res;

	स_रखो(&res, 0, माप(res));
	tb_xdp_fill_header(&res.hdr, route, sequence, UUID_RESPONSE,
			   माप(res));

	uuid_copy(&res.src_uuid, uuid);
	res.src_route_hi = upper_32_bits(route);
	res.src_route_lo = lower_32_bits(route);

	वापस __tb_xकरोमुख्य_response(ctl, &res, माप(res),
				     TB_CFG_PKG_XDOMAIN_RESP);
पूर्ण

अटल पूर्णांक tb_xdp_error_response(काष्ठा tb_ctl *ctl, u64 route, u8 sequence,
				 क्रमागत tb_xdp_error error)
अणु
	काष्ठा tb_xdp_error_response res;

	स_रखो(&res, 0, माप(res));
	tb_xdp_fill_header(&res.hdr, route, sequence, ERROR_RESPONSE,
			   माप(res));
	res.error = error;

	वापस __tb_xकरोमुख्य_response(ctl, &res, माप(res),
				     TB_CFG_PKG_XDOMAIN_RESP);
पूर्ण

अटल पूर्णांक tb_xdp_properties_request(काष्ठा tb_ctl *ctl, u64 route,
	स्थिर uuid_t *src_uuid, स्थिर uuid_t *dst_uuid, पूर्णांक retry,
	u32 **block, u32 *generation)
अणु
	काष्ठा tb_xdp_properties_response *res;
	काष्ठा tb_xdp_properties req;
	u16 data_len, len;
	माप_प्रकार total_size;
	u32 *data = शून्य;
	पूर्णांक ret;

	total_size = माप(*res) + TB_XDP_PROPERTIES_MAX_DATA_LENGTH * 4;
	res = kzalloc(total_size, GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	स_रखो(&req, 0, माप(req));
	tb_xdp_fill_header(&req.hdr, route, retry % 4, PROPERTIES_REQUEST,
			   माप(req));
	स_नकल(&req.src_uuid, src_uuid, माप(*src_uuid));
	स_नकल(&req.dst_uuid, dst_uuid, माप(*dst_uuid));

	len = 0;
	data_len = 0;

	करो अणु
		ret = __tb_xकरोमुख्य_request(ctl, &req, माप(req),
					   TB_CFG_PKG_XDOMAIN_REQ, res,
					   total_size, TB_CFG_PKG_XDOMAIN_RESP,
					   XDOMAIN_DEFAULT_TIMEOUT);
		अगर (ret)
			जाओ err;

		ret = tb_xdp_handle_error(&res->hdr);
		अगर (ret)
			जाओ err;

		/*
		 * Package length includes the whole payload without the
		 * XDoमुख्य header. Validate first that the package is at
		 * least size of the response काष्ठाure.
		 */
		len = res->hdr.xd_hdr.length_sn & TB_XDOMAIN_LENGTH_MASK;
		अगर (len < माप(*res) / 4) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		len += माप(res->hdr.xd_hdr) / 4;
		len -= माप(*res) / 4;

		अगर (res->offset != req.offset) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		/*
		 * First समय allocate block that has enough space क्रम
		 * the whole properties block.
		 */
		अगर (!data) अणु
			data_len = res->data_length;
			अगर (data_len > TB_XDP_PROPERTIES_MAX_LENGTH) अणु
				ret = -E2BIG;
				जाओ err;
			पूर्ण

			data = kसुस्मृति(data_len, माप(u32), GFP_KERNEL);
			अगर (!data) अणु
				ret = -ENOMEM;
				जाओ err;
			पूर्ण
		पूर्ण

		स_नकल(data + req.offset, res->data, len * 4);
		req.offset += len;
	पूर्ण जबतक (!data_len || req.offset < data_len);

	*block = data;
	*generation = res->generation;

	kमुक्त(res);

	वापस data_len;

err:
	kमुक्त(data);
	kमुक्त(res);

	वापस ret;
पूर्ण

अटल पूर्णांक tb_xdp_properties_response(काष्ठा tb *tb, काष्ठा tb_ctl *ctl,
	काष्ठा tb_xकरोमुख्य *xd, u8 sequence, स्थिर काष्ठा tb_xdp_properties *req)
अणु
	काष्ठा tb_xdp_properties_response *res;
	माप_प्रकार total_size;
	u16 len;
	पूर्णांक ret;

	/*
	 * Currently we expect all requests to be directed to us. The
	 * protocol supports क्रमwarding, though which we might add
	 * support later on.
	 */
	अगर (!uuid_equal(xd->local_uuid, &req->dst_uuid)) अणु
		tb_xdp_error_response(ctl, xd->route, sequence,
				      ERROR_UNKNOWN_DOMAIN);
		वापस 0;
	पूर्ण

	mutex_lock(&xd->lock);

	अगर (req->offset >= xd->local_property_block_len) अणु
		mutex_unlock(&xd->lock);
		वापस -EINVAL;
	पूर्ण

	len = xd->local_property_block_len - req->offset;
	len = min_t(u16, len, TB_XDP_PROPERTIES_MAX_DATA_LENGTH);
	total_size = माप(*res) + len * 4;

	res = kzalloc(total_size, GFP_KERNEL);
	अगर (!res) अणु
		mutex_unlock(&xd->lock);
		वापस -ENOMEM;
	पूर्ण

	tb_xdp_fill_header(&res->hdr, xd->route, sequence, PROPERTIES_RESPONSE,
			   total_size);
	res->generation = xd->local_property_block_gen;
	res->data_length = xd->local_property_block_len;
	res->offset = req->offset;
	uuid_copy(&res->src_uuid, xd->local_uuid);
	uuid_copy(&res->dst_uuid, &req->src_uuid);
	स_नकल(res->data, &xd->local_property_block[req->offset], len * 4);

	mutex_unlock(&xd->lock);

	ret = __tb_xकरोमुख्य_response(ctl, res, total_size,
				    TB_CFG_PKG_XDOMAIN_RESP);

	kमुक्त(res);
	वापस ret;
पूर्ण

अटल पूर्णांक tb_xdp_properties_changed_request(काष्ठा tb_ctl *ctl, u64 route,
					     पूर्णांक retry, स्थिर uuid_t *uuid)
अणु
	काष्ठा tb_xdp_properties_changed_response res;
	काष्ठा tb_xdp_properties_changed req;
	पूर्णांक ret;

	स_रखो(&req, 0, माप(req));
	tb_xdp_fill_header(&req.hdr, route, retry % 4,
			   PROPERTIES_CHANGED_REQUEST, माप(req));
	uuid_copy(&req.src_uuid, uuid);

	स_रखो(&res, 0, माप(res));
	ret = __tb_xकरोमुख्य_request(ctl, &req, माप(req),
				   TB_CFG_PKG_XDOMAIN_REQ, &res, माप(res),
				   TB_CFG_PKG_XDOMAIN_RESP,
				   XDOMAIN_DEFAULT_TIMEOUT);
	अगर (ret)
		वापस ret;

	वापस tb_xdp_handle_error(&res.hdr);
पूर्ण

अटल पूर्णांक
tb_xdp_properties_changed_response(काष्ठा tb_ctl *ctl, u64 route, u8 sequence)
अणु
	काष्ठा tb_xdp_properties_changed_response res;

	स_रखो(&res, 0, माप(res));
	tb_xdp_fill_header(&res.hdr, route, sequence,
			   PROPERTIES_CHANGED_RESPONSE, माप(res));
	वापस __tb_xकरोमुख्य_response(ctl, &res, माप(res),
				     TB_CFG_PKG_XDOMAIN_RESP);
पूर्ण

/**
 * tb_रेजिस्टर_protocol_handler() - Register protocol handler
 * @handler: Handler to रेजिस्टर
 *
 * This allows XDoमुख्य service drivers to hook पूर्णांकo incoming XDoमुख्य
 * messages. After this function is called the service driver needs to
 * be able to handle calls to callback whenever a package with the
 * रेजिस्टरed protocol is received.
 */
पूर्णांक tb_रेजिस्टर_protocol_handler(काष्ठा tb_protocol_handler *handler)
अणु
	अगर (!handler->uuid || !handler->callback)
		वापस -EINVAL;
	अगर (uuid_equal(handler->uuid, &tb_xdp_uuid))
		वापस -EINVAL;

	mutex_lock(&xकरोमुख्य_lock);
	list_add_tail(&handler->list, &protocol_handlers);
	mutex_unlock(&xकरोमुख्य_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tb_रेजिस्टर_protocol_handler);

/**
 * tb_unरेजिस्टर_protocol_handler() - Unरेजिस्टर protocol handler
 * @handler: Handler to unरेजिस्टर
 *
 * Removes the previously रेजिस्टरed protocol handler.
 */
व्योम tb_unरेजिस्टर_protocol_handler(काष्ठा tb_protocol_handler *handler)
अणु
	mutex_lock(&xकरोमुख्य_lock);
	list_del_init(&handler->list);
	mutex_unlock(&xकरोमुख्य_lock);
पूर्ण
EXPORT_SYMBOL_GPL(tb_unरेजिस्टर_protocol_handler);

अटल व्योम update_property_block(काष्ठा tb_xकरोमुख्य *xd)
अणु
	mutex_lock(&xकरोमुख्य_lock);
	mutex_lock(&xd->lock);
	/*
	 * If the local property block is not up-to-date, rebuild it now
	 * based on the global property ढाँचा.
	 */
	अगर (!xd->local_property_block ||
	    xd->local_property_block_gen < xकरोमुख्य_property_block_gen) अणु
		काष्ठा tb_property_dir *dir;
		पूर्णांक ret, block_len;
		u32 *block;

		dir = tb_property_copy_dir(xकरोमुख्य_property_dir);
		अगर (!dir) अणु
			dev_warn(&xd->dev, "failed to copy properties\n");
			जाओ out_unlock;
		पूर्ण

		/* Fill in non-अटल properties now */
		tb_property_add_text(dir, "deviceid", utsname()->nodename);
		tb_property_add_immediate(dir, "maxhopid", xd->local_max_hopid);

		ret = tb_property_क्रमmat_dir(dir, शून्य, 0);
		अगर (ret < 0) अणु
			dev_warn(&xd->dev, "local property block creation failed\n");
			tb_property_मुक्त_dir(dir);
			जाओ out_unlock;
		पूर्ण

		block_len = ret;
		block = kसुस्मृति(block_len, माप(*block), GFP_KERNEL);
		अगर (!block) अणु
			tb_property_मुक्त_dir(dir);
			जाओ out_unlock;
		पूर्ण

		ret = tb_property_क्रमmat_dir(dir, block, block_len);
		अगर (ret) अणु
			dev_warn(&xd->dev, "property block generation failed\n");
			tb_property_मुक्त_dir(dir);
			kमुक्त(block);
			जाओ out_unlock;
		पूर्ण

		tb_property_मुक्त_dir(dir);
		/* Release the previous block */
		kमुक्त(xd->local_property_block);
		/* Assign new one */
		xd->local_property_block = block;
		xd->local_property_block_len = block_len;
		xd->local_property_block_gen = xकरोमुख्य_property_block_gen;
	पूर्ण

out_unlock:
	mutex_unlock(&xd->lock);
	mutex_unlock(&xकरोमुख्य_lock);
पूर्ण

अटल व्योम tb_xdp_handle_request(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xकरोमुख्य_request_work *xw = container_of(work, typeof(*xw), work);
	स्थिर काष्ठा tb_xdp_header *pkg = xw->pkg;
	स्थिर काष्ठा tb_xकरोमुख्य_header *xhdr = &pkg->xd_hdr;
	काष्ठा tb *tb = xw->tb;
	काष्ठा tb_ctl *ctl = tb->ctl;
	काष्ठा tb_xकरोमुख्य *xd;
	स्थिर uuid_t *uuid;
	पूर्णांक ret = 0;
	u32 sequence;
	u64 route;

	route = ((u64)xhdr->route_hi << 32 | xhdr->route_lo) & ~BIT_ULL(63);
	sequence = xhdr->length_sn & TB_XDOMAIN_SN_MASK;
	sequence >>= TB_XDOMAIN_SN_SHIFT;

	mutex_lock(&tb->lock);
	अगर (tb->root_चयन)
		uuid = tb->root_चयन->uuid;
	अन्यथा
		uuid = शून्य;
	mutex_unlock(&tb->lock);

	अगर (!uuid) अणु
		tb_xdp_error_response(ctl, route, sequence, ERROR_NOT_READY);
		जाओ out;
	पूर्ण

	tb_dbg(tb, "%llx: received XDomain request %#x\n", route, pkg->type);

	xd = tb_xकरोमुख्य_find_by_route_locked(tb, route);
	अगर (xd)
		update_property_block(xd);

	चयन (pkg->type) अणु
	हाल PROPERTIES_REQUEST:
		अगर (xd) अणु
			ret = tb_xdp_properties_response(tb, ctl, xd, sequence,
				(स्थिर काष्ठा tb_xdp_properties *)pkg);
		पूर्ण
		अवरोध;

	हाल PROPERTIES_CHANGED_REQUEST:
		ret = tb_xdp_properties_changed_response(ctl, route, sequence);

		/*
		 * Since the properties have been changed, let's update
		 * the xकरोमुख्य related to this connection as well in
		 * हाल there is a change in services it offers.
		 */
		अगर (xd && device_is_रेजिस्टरed(&xd->dev)) अणु
			queue_delayed_work(tb->wq, &xd->get_properties_work,
					   msecs_to_jअगरfies(50));
		पूर्ण
		अवरोध;

	हाल UUID_REQUEST_OLD:
	हाल UUID_REQUEST:
		ret = tb_xdp_uuid_response(ctl, route, sequence, uuid);
		अवरोध;

	शेष:
		tb_xdp_error_response(ctl, route, sequence,
				      ERROR_NOT_SUPPORTED);
		अवरोध;
	पूर्ण

	tb_xकरोमुख्य_put(xd);

	अगर (ret) अणु
		tb_warn(tb, "failed to send XDomain response for %#x\n",
			pkg->type);
	पूर्ण

out:
	kमुक्त(xw->pkg);
	kमुक्त(xw);

	tb_करोमुख्य_put(tb);
पूर्ण

अटल bool
tb_xdp_schedule_request(काष्ठा tb *tb, स्थिर काष्ठा tb_xdp_header *hdr,
			माप_प्रकार size)
अणु
	काष्ठा xकरोमुख्य_request_work *xw;

	xw = kदो_स्मृति(माप(*xw), GFP_KERNEL);
	अगर (!xw)
		वापस false;

	INIT_WORK(&xw->work, tb_xdp_handle_request);
	xw->pkg = kmemdup(hdr, size, GFP_KERNEL);
	अगर (!xw->pkg) अणु
		kमुक्त(xw);
		वापस false;
	पूर्ण
	xw->tb = tb_करोमुख्य_get(tb);

	schedule_work(&xw->work);
	वापस true;
पूर्ण

/**
 * tb_रेजिस्टर_service_driver() - Register XDoमुख्य service driver
 * @drv: Driver to रेजिस्टर
 *
 * Registers new service driver from @drv to the bus.
 */
पूर्णांक tb_रेजिस्टर_service_driver(काष्ठा tb_service_driver *drv)
अणु
	drv->driver.bus = &tb_bus_type;
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(tb_रेजिस्टर_service_driver);

/**
 * tb_unरेजिस्टर_service_driver() - Unरेजिस्टर XDoमुख्य service driver
 * @drv: Driver to unरेजिस्टर
 *
 * Unरेजिस्टरs XDoमुख्य service driver from the bus.
 */
व्योम tb_unरेजिस्टर_service_driver(काष्ठा tb_service_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(tb_unरेजिस्टर_service_driver);

अटल sमाप_प्रकार key_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा tb_service *svc = container_of(dev, काष्ठा tb_service, dev);

	/*
	 * It should be null terminated but anything अन्यथा is pretty much
	 * allowed.
	 */
	वापस प्र_लिखो(buf, "%*pE\n", (पूर्णांक)म_माप(svc->key), svc->key);
पूर्ण
अटल DEVICE_ATTR_RO(key);

अटल पूर्णांक get_modalias(काष्ठा tb_service *svc, अक्षर *buf, माप_प्रकार size)
अणु
	वापस snम_लिखो(buf, size, "tbsvc:k%sp%08Xv%08Xr%08X", svc->key,
			svc->prtcid, svc->prtcvers, svc->prtcrevs);
पूर्ण

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा tb_service *svc = container_of(dev, काष्ठा tb_service, dev);

	/* Full buffer size except new line and null termination */
	get_modalias(svc, buf, PAGE_SIZE - 2);
	वापस प्र_लिखो(buf, "%s\n", buf);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार prtcid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा tb_service *svc = container_of(dev, काष्ठा tb_service, dev);

	वापस प्र_लिखो(buf, "%u\n", svc->prtcid);
पूर्ण
अटल DEVICE_ATTR_RO(prtcid);

अटल sमाप_प्रकार prtcvers_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा tb_service *svc = container_of(dev, काष्ठा tb_service, dev);

	वापस प्र_लिखो(buf, "%u\n", svc->prtcvers);
पूर्ण
अटल DEVICE_ATTR_RO(prtcvers);

अटल sमाप_प्रकार prtcrevs_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा tb_service *svc = container_of(dev, काष्ठा tb_service, dev);

	वापस प्र_लिखो(buf, "%u\n", svc->prtcrevs);
पूर्ण
अटल DEVICE_ATTR_RO(prtcrevs);

अटल sमाप_प्रकार prtcstns_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा tb_service *svc = container_of(dev, काष्ठा tb_service, dev);

	वापस प्र_लिखो(buf, "0x%08x\n", svc->prtcstns);
पूर्ण
अटल DEVICE_ATTR_RO(prtcstns);

अटल काष्ठा attribute *tb_service_attrs[] = अणु
	&dev_attr_key.attr,
	&dev_attr_modalias.attr,
	&dev_attr_prtcid.attr,
	&dev_attr_prtcvers.attr,
	&dev_attr_prtcrevs.attr,
	&dev_attr_prtcstns.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group tb_service_attr_group = अणु
	.attrs = tb_service_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *tb_service_attr_groups[] = अणु
	&tb_service_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक tb_service_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा tb_service *svc = container_of(dev, काष्ठा tb_service, dev);
	अक्षर modalias[64];

	get_modalias(svc, modalias, माप(modalias));
	वापस add_uevent_var(env, "MODALIAS=%s", modalias);
पूर्ण

अटल व्योम tb_service_release(काष्ठा device *dev)
अणु
	काष्ठा tb_service *svc = container_of(dev, काष्ठा tb_service, dev);
	काष्ठा tb_xकरोमुख्य *xd = tb_service_parent(svc);

	tb_service_debugfs_हटाओ(svc);
	ida_simple_हटाओ(&xd->service_ids, svc->id);
	kमुक्त(svc->key);
	kमुक्त(svc);
पूर्ण

काष्ठा device_type tb_service_type = अणु
	.name = "thunderbolt_service",
	.groups = tb_service_attr_groups,
	.uevent = tb_service_uevent,
	.release = tb_service_release,
पूर्ण;
EXPORT_SYMBOL_GPL(tb_service_type);

अटल पूर्णांक हटाओ_missing_service(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा tb_xकरोमुख्य *xd = data;
	काष्ठा tb_service *svc;

	svc = tb_to_service(dev);
	अगर (!svc)
		वापस 0;

	अगर (!tb_property_find(xd->remote_properties, svc->key,
			      TB_PROPERTY_TYPE_सूचीECTORY))
		device_unरेजिस्टर(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक find_service(काष्ठा device *dev, व्योम *data)
अणु
	स्थिर काष्ठा tb_property *p = data;
	काष्ठा tb_service *svc;

	svc = tb_to_service(dev);
	अगर (!svc)
		वापस 0;

	वापस !म_भेद(svc->key, p->key);
पूर्ण

अटल पूर्णांक populate_service(काष्ठा tb_service *svc,
			    काष्ठा tb_property *property)
अणु
	काष्ठा tb_property_dir *dir = property->value.dir;
	काष्ठा tb_property *p;

	/* Fill in standard properties */
	p = tb_property_find(dir, "prtcid", TB_PROPERTY_TYPE_VALUE);
	अगर (p)
		svc->prtcid = p->value.immediate;
	p = tb_property_find(dir, "prtcvers", TB_PROPERTY_TYPE_VALUE);
	अगर (p)
		svc->prtcvers = p->value.immediate;
	p = tb_property_find(dir, "prtcrevs", TB_PROPERTY_TYPE_VALUE);
	अगर (p)
		svc->prtcrevs = p->value.immediate;
	p = tb_property_find(dir, "prtcstns", TB_PROPERTY_TYPE_VALUE);
	अगर (p)
		svc->prtcstns = p->value.immediate;

	svc->key = kstrdup(property->key, GFP_KERNEL);
	अगर (!svc->key)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम क्रमागतerate_services(काष्ठा tb_xकरोमुख्य *xd)
अणु
	काष्ठा tb_service *svc;
	काष्ठा tb_property *p;
	काष्ठा device *dev;
	पूर्णांक id;

	/*
	 * First हटाओ all services that are not available anymore in
	 * the updated property block.
	 */
	device_क्रम_each_child_reverse(&xd->dev, xd, हटाओ_missing_service);

	/* Then re-क्रमागतerate properties creating new services as we go */
	tb_property_क्रम_each(xd->remote_properties, p) अणु
		अगर (p->type != TB_PROPERTY_TYPE_सूचीECTORY)
			जारी;

		/* If the service exists alपढ़ोy we are fine */
		dev = device_find_child(&xd->dev, p, find_service);
		अगर (dev) अणु
			put_device(dev);
			जारी;
		पूर्ण

		svc = kzalloc(माप(*svc), GFP_KERNEL);
		अगर (!svc)
			अवरोध;

		अगर (populate_service(svc, p)) अणु
			kमुक्त(svc);
			अवरोध;
		पूर्ण

		id = ida_simple_get(&xd->service_ids, 0, 0, GFP_KERNEL);
		अगर (id < 0) अणु
			kमुक्त(svc->key);
			kमुक्त(svc);
			अवरोध;
		पूर्ण
		svc->id = id;
		svc->dev.bus = &tb_bus_type;
		svc->dev.type = &tb_service_type;
		svc->dev.parent = &xd->dev;
		dev_set_name(&svc->dev, "%s.%d", dev_name(&xd->dev), svc->id);

		tb_service_debugfs_init(svc);

		अगर (device_रेजिस्टर(&svc->dev)) अणु
			put_device(&svc->dev);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक populate_properties(काष्ठा tb_xकरोमुख्य *xd,
			       काष्ठा tb_property_dir *dir)
अणु
	स्थिर काष्ठा tb_property *p;

	/* Required properties */
	p = tb_property_find(dir, "deviceid", TB_PROPERTY_TYPE_VALUE);
	अगर (!p)
		वापस -EINVAL;
	xd->device = p->value.immediate;

	p = tb_property_find(dir, "vendorid", TB_PROPERTY_TYPE_VALUE);
	अगर (!p)
		वापस -EINVAL;
	xd->venकरोr = p->value.immediate;

	p = tb_property_find(dir, "maxhopid", TB_PROPERTY_TYPE_VALUE);
	/*
	 * USB4 पूर्णांकer-करोमुख्य spec suggests using 15 as HopID अगर the
	 * other end करोes not announce it in a property. This is क्रम
	 * TBT3 compatibility.
	 */
	xd->remote_max_hopid = p ? p->value.immediate : XDOMAIN_DEFAULT_MAX_HOPID;

	kमुक्त(xd->device_name);
	xd->device_name = शून्य;
	kमुक्त(xd->venकरोr_name);
	xd->venकरोr_name = शून्य;

	/* Optional properties */
	p = tb_property_find(dir, "deviceid", TB_PROPERTY_TYPE_TEXT);
	अगर (p)
		xd->device_name = kstrdup(p->value.text, GFP_KERNEL);
	p = tb_property_find(dir, "vendorid", TB_PROPERTY_TYPE_TEXT);
	अगर (p)
		xd->venकरोr_name = kstrdup(p->value.text, GFP_KERNEL);

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा tb_चयन *tb_xकरोमुख्य_parent(काष्ठा tb_xकरोमुख्य *xd)
अणु
	वापस tb_to_चयन(xd->dev.parent);
पूर्ण

अटल पूर्णांक tb_xकरोमुख्य_update_link_attributes(काष्ठा tb_xकरोमुख्य *xd)
अणु
	bool change = false;
	काष्ठा tb_port *port;
	पूर्णांक ret;

	port = tb_port_at(xd->route, tb_xकरोमुख्य_parent(xd));

	ret = tb_port_get_link_speed(port);
	अगर (ret < 0)
		वापस ret;

	अगर (xd->link_speed != ret)
		change = true;

	xd->link_speed = ret;

	ret = tb_port_get_link_width(port);
	अगर (ret < 0)
		वापस ret;

	अगर (xd->link_width != ret)
		change = true;

	xd->link_width = ret;

	अगर (change)
		kobject_uevent(&xd->dev.kobj, KOBJ_CHANGE);

	वापस 0;
पूर्ण

अटल व्योम tb_xकरोमुख्य_get_uuid(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(work, typeof(*xd),
					     get_uuid_work.work);
	काष्ठा tb *tb = xd->tb;
	uuid_t uuid;
	पूर्णांक ret;

	dev_dbg(&xd->dev, "requesting remote UUID\n");

	ret = tb_xdp_uuid_request(tb->ctl, xd->route, xd->uuid_retries, &uuid);
	अगर (ret < 0) अणु
		अगर (xd->uuid_retries-- > 0) अणु
			dev_dbg(&xd->dev, "failed to request UUID, retrying\n");
			queue_delayed_work(xd->tb->wq, &xd->get_uuid_work,
					   msecs_to_jअगरfies(100));
		पूर्ण अन्यथा अणु
			dev_dbg(&xd->dev, "failed to read remote UUID\n");
		पूर्ण
		वापस;
	पूर्ण

	dev_dbg(&xd->dev, "got remote UUID %pUb\n", &uuid);

	अगर (uuid_equal(&uuid, xd->local_uuid))
		dev_dbg(&xd->dev, "intra-domain loop detected\n");

	/*
	 * If the UUID is dअगरferent, there is another करोमुख्य connected
	 * so mark this one unplugged and रुको क्रम the connection
	 * manager to replace it.
	 */
	अगर (xd->remote_uuid && !uuid_equal(&uuid, xd->remote_uuid)) अणु
		dev_dbg(&xd->dev, "remote UUID is different, unplugging\n");
		xd->is_unplugged = true;
		वापस;
	पूर्ण

	/* First समय fill in the missing UUID */
	अगर (!xd->remote_uuid) अणु
		xd->remote_uuid = kmemdup(&uuid, माप(uuid_t), GFP_KERNEL);
		अगर (!xd->remote_uuid)
			वापस;
	पूर्ण

	/* Now we can start the normal properties exchange */
	queue_delayed_work(xd->tb->wq, &xd->properties_changed_work,
			   msecs_to_jअगरfies(100));
	queue_delayed_work(xd->tb->wq, &xd->get_properties_work,
			   msecs_to_jअगरfies(1000));
पूर्ण

अटल व्योम tb_xकरोमुख्य_get_properties(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(work, typeof(*xd),
					     get_properties_work.work);
	काष्ठा tb_property_dir *dir;
	काष्ठा tb *tb = xd->tb;
	bool update = false;
	u32 *block = शून्य;
	u32 gen = 0;
	पूर्णांक ret;

	dev_dbg(&xd->dev, "requesting remote properties\n");

	ret = tb_xdp_properties_request(tb->ctl, xd->route, xd->local_uuid,
					xd->remote_uuid, xd->properties_retries,
					&block, &gen);
	अगर (ret < 0) अणु
		अगर (xd->properties_retries-- > 0) अणु
			dev_dbg(&xd->dev,
				"failed to request remote properties, retrying\n");
			queue_delayed_work(xd->tb->wq, &xd->get_properties_work,
					   msecs_to_jअगरfies(1000));
		पूर्ण अन्यथा अणु
			/* Give up now */
			dev_err(&xd->dev,
				"failed read XDomain properties from %pUb\n",
				xd->remote_uuid);
		पूर्ण
		वापस;
	पूर्ण

	xd->properties_retries = XDOMAIN_PROPERTIES_RETRIES;

	mutex_lock(&xd->lock);

	/* Only accept newer generation properties */
	अगर (xd->remote_properties && gen <= xd->remote_property_block_gen)
		जाओ err_मुक्त_block;

	dir = tb_property_parse_dir(block, ret);
	अगर (!dir) अणु
		dev_err(&xd->dev, "failed to parse XDomain properties\n");
		जाओ err_मुक्त_block;
	पूर्ण

	ret = populate_properties(xd, dir);
	अगर (ret) अणु
		dev_err(&xd->dev, "missing XDomain properties in response\n");
		जाओ err_मुक्त_dir;
	पूर्ण

	/* Release the existing one */
	अगर (xd->remote_properties) अणु
		tb_property_मुक्त_dir(xd->remote_properties);
		update = true;
	पूर्ण

	xd->remote_properties = dir;
	xd->remote_property_block_gen = gen;

	tb_xकरोमुख्य_update_link_attributes(xd);

	mutex_unlock(&xd->lock);

	kमुक्त(block);

	/*
	 * Now the device should be पढ़ोy enough so we can add it to the
	 * bus and let userspace know about it. If the device is alपढ़ोy
	 * रेजिस्टरed, we notअगरy the userspace that it has changed.
	 */
	अगर (!update) अणु
		अगर (device_add(&xd->dev)) अणु
			dev_err(&xd->dev, "failed to add XDomain device\n");
			वापस;
		पूर्ण
		dev_info(&xd->dev, "new host found, vendor=%#x device=%#x\n",
			 xd->venकरोr, xd->device);
		अगर (xd->venकरोr_name && xd->device_name)
			dev_info(&xd->dev, "%s %s\n", xd->venकरोr_name,
				 xd->device_name);
	पूर्ण अन्यथा अणु
		kobject_uevent(&xd->dev.kobj, KOBJ_CHANGE);
	पूर्ण

	क्रमागतerate_services(xd);
	वापस;

err_मुक्त_dir:
	tb_property_मुक्त_dir(dir);
err_मुक्त_block:
	kमुक्त(block);
	mutex_unlock(&xd->lock);
पूर्ण

अटल व्योम tb_xकरोमुख्य_properties_changed(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(work, typeof(*xd),
					     properties_changed_work.work);
	पूर्णांक ret;

	dev_dbg(&xd->dev, "sending properties changed notification\n");

	ret = tb_xdp_properties_changed_request(xd->tb->ctl, xd->route,
				xd->properties_changed_retries, xd->local_uuid);
	अगर (ret) अणु
		अगर (xd->properties_changed_retries-- > 0) अणु
			dev_dbg(&xd->dev,
				"failed to send properties changed notification, retrying\n");
			queue_delayed_work(xd->tb->wq,
					   &xd->properties_changed_work,
					   msecs_to_jअगरfies(1000));
		पूर्ण
		dev_err(&xd->dev, "failed to send properties changed notification\n");
		वापस;
	पूर्ण

	xd->properties_changed_retries = XDOMAIN_PROPERTIES_CHANGED_RETRIES;
पूर्ण

अटल sमाप_प्रकार device_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(dev, काष्ठा tb_xकरोमुख्य, dev);

	वापस प्र_लिखो(buf, "%#x\n", xd->device);
पूर्ण
अटल DEVICE_ATTR_RO(device);

अटल sमाप_प्रकार
device_name_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(dev, काष्ठा tb_xकरोमुख्य, dev);
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&xd->lock))
		वापस -ERESTARTSYS;
	ret = प्र_लिखो(buf, "%s\n", xd->device_name ? xd->device_name : "");
	mutex_unlock(&xd->lock);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(device_name);

अटल sमाप_प्रकार maxhopid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(dev, काष्ठा tb_xकरोमुख्य, dev);

	वापस प्र_लिखो(buf, "%d\n", xd->remote_max_hopid);
पूर्ण
अटल DEVICE_ATTR_RO(maxhopid);

अटल sमाप_प्रकार venकरोr_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(dev, काष्ठा tb_xकरोमुख्य, dev);

	वापस प्र_लिखो(buf, "%#x\n", xd->venकरोr);
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr);

अटल sमाप_प्रकार
venकरोr_name_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(dev, काष्ठा tb_xकरोमुख्य, dev);
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&xd->lock))
		वापस -ERESTARTSYS;
	ret = प्र_लिखो(buf, "%s\n", xd->venकरोr_name ? xd->venकरोr_name : "");
	mutex_unlock(&xd->lock);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr_name);

अटल sमाप_प्रकार unique_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(dev, काष्ठा tb_xकरोमुख्य, dev);

	वापस प्र_लिखो(buf, "%pUb\n", xd->remote_uuid);
पूर्ण
अटल DEVICE_ATTR_RO(unique_id);

अटल sमाप_प्रकार speed_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(dev, काष्ठा tb_xकरोमुख्य, dev);

	वापस प्र_लिखो(buf, "%u.0 Gb/s\n", xd->link_speed);
पूर्ण

अटल DEVICE_ATTR(rx_speed, 0444, speed_show, शून्य);
अटल DEVICE_ATTR(tx_speed, 0444, speed_show, शून्य);

अटल sमाप_प्रकार lanes_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(dev, काष्ठा tb_xकरोमुख्य, dev);

	वापस प्र_लिखो(buf, "%u\n", xd->link_width);
पूर्ण

अटल DEVICE_ATTR(rx_lanes, 0444, lanes_show, शून्य);
अटल DEVICE_ATTR(tx_lanes, 0444, lanes_show, शून्य);

अटल काष्ठा attribute *xकरोमुख्य_attrs[] = अणु
	&dev_attr_device.attr,
	&dev_attr_device_name.attr,
	&dev_attr_maxhopid.attr,
	&dev_attr_rx_lanes.attr,
	&dev_attr_rx_speed.attr,
	&dev_attr_tx_lanes.attr,
	&dev_attr_tx_speed.attr,
	&dev_attr_unique_id.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_venकरोr_name.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group xकरोमुख्य_attr_group = अणु
	.attrs = xकरोमुख्य_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *xकरोमुख्य_attr_groups[] = अणु
	&xकरोमुख्य_attr_group,
	शून्य,
पूर्ण;

अटल व्योम tb_xकरोमुख्य_release(काष्ठा device *dev)
अणु
	काष्ठा tb_xकरोमुख्य *xd = container_of(dev, काष्ठा tb_xकरोमुख्य, dev);

	put_device(xd->dev.parent);

	kमुक्त(xd->local_property_block);
	tb_property_मुक्त_dir(xd->remote_properties);
	ida_destroy(&xd->out_hopids);
	ida_destroy(&xd->in_hopids);
	ida_destroy(&xd->service_ids);

	kमुक्त(xd->local_uuid);
	kमुक्त(xd->remote_uuid);
	kमुक्त(xd->device_name);
	kमुक्त(xd->venकरोr_name);
	kमुक्त(xd);
पूर्ण

अटल व्योम start_handshake(काष्ठा tb_xकरोमुख्य *xd)
अणु
	xd->uuid_retries = XDOMAIN_UUID_RETRIES;
	xd->properties_retries = XDOMAIN_PROPERTIES_RETRIES;
	xd->properties_changed_retries = XDOMAIN_PROPERTIES_CHANGED_RETRIES;

	अगर (xd->needs_uuid) अणु
		queue_delayed_work(xd->tb->wq, &xd->get_uuid_work,
				   msecs_to_jअगरfies(100));
	पूर्ण अन्यथा अणु
		/* Start exchanging properties with the other host */
		queue_delayed_work(xd->tb->wq, &xd->properties_changed_work,
				   msecs_to_jअगरfies(100));
		queue_delayed_work(xd->tb->wq, &xd->get_properties_work,
				   msecs_to_jअगरfies(1000));
	पूर्ण
पूर्ण

अटल व्योम stop_handshake(काष्ठा tb_xकरोमुख्य *xd)
अणु
	xd->uuid_retries = 0;
	xd->properties_retries = 0;
	xd->properties_changed_retries = 0;

	cancel_delayed_work_sync(&xd->get_uuid_work);
	cancel_delayed_work_sync(&xd->get_properties_work);
	cancel_delayed_work_sync(&xd->properties_changed_work);
पूर्ण

अटल पूर्णांक __maybe_unused tb_xकरोमुख्य_suspend(काष्ठा device *dev)
अणु
	stop_handshake(tb_to_xकरोमुख्य(dev));
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tb_xकरोमुख्य_resume(काष्ठा device *dev)
अणु
	start_handshake(tb_to_xकरोमुख्य(dev));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tb_xकरोमुख्य_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tb_xकरोमुख्य_suspend, tb_xकरोमुख्य_resume)
पूर्ण;

काष्ठा device_type tb_xकरोमुख्य_type = अणु
	.name = "thunderbolt_xdomain",
	.release = tb_xकरोमुख्य_release,
	.pm = &tb_xकरोमुख्य_pm_ops,
पूर्ण;
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_type);

/**
 * tb_xकरोमुख्य_alloc() - Allocate new XDoमुख्य object
 * @tb: Doमुख्य where the XDoमुख्य beदीर्घs
 * @parent: Parent device (the चयन through the connection to the
 *	    other करोमुख्य is reached).
 * @route: Route string used to reach the other करोमुख्य
 * @local_uuid: Our local करोमुख्य UUID
 * @remote_uuid: UUID of the other करोमुख्य (optional)
 *
 * Allocates new XDoमुख्य काष्ठाure and वापसs poपूर्णांकer to that. The
 * object must be released by calling tb_xकरोमुख्य_put().
 */
काष्ठा tb_xकरोमुख्य *tb_xकरोमुख्य_alloc(काष्ठा tb *tb, काष्ठा device *parent,
				    u64 route, स्थिर uuid_t *local_uuid,
				    स्थिर uuid_t *remote_uuid)
अणु
	काष्ठा tb_चयन *parent_sw = tb_to_चयन(parent);
	काष्ठा tb_xकरोमुख्य *xd;
	काष्ठा tb_port *करोwn;

	/* Make sure the करोwnstream करोमुख्य is accessible */
	करोwn = tb_port_at(route, parent_sw);
	tb_port_unlock(करोwn);

	xd = kzalloc(माप(*xd), GFP_KERNEL);
	अगर (!xd)
		वापस शून्य;

	xd->tb = tb;
	xd->route = route;
	xd->local_max_hopid = करोwn->config.max_in_hop_id;
	ida_init(&xd->service_ids);
	ida_init(&xd->in_hopids);
	ida_init(&xd->out_hopids);
	mutex_init(&xd->lock);
	INIT_DELAYED_WORK(&xd->get_uuid_work, tb_xकरोमुख्य_get_uuid);
	INIT_DELAYED_WORK(&xd->get_properties_work, tb_xकरोमुख्य_get_properties);
	INIT_DELAYED_WORK(&xd->properties_changed_work,
			  tb_xकरोमुख्य_properties_changed);

	xd->local_uuid = kmemdup(local_uuid, माप(uuid_t), GFP_KERNEL);
	अगर (!xd->local_uuid)
		जाओ err_मुक्त;

	अगर (remote_uuid) अणु
		xd->remote_uuid = kmemdup(remote_uuid, माप(uuid_t),
					  GFP_KERNEL);
		अगर (!xd->remote_uuid)
			जाओ err_मुक्त_local_uuid;
	पूर्ण अन्यथा अणु
		xd->needs_uuid = true;
	पूर्ण

	device_initialize(&xd->dev);
	xd->dev.parent = get_device(parent);
	xd->dev.bus = &tb_bus_type;
	xd->dev.type = &tb_xकरोमुख्य_type;
	xd->dev.groups = xकरोमुख्य_attr_groups;
	dev_set_name(&xd->dev, "%u-%llx", tb->index, route);

	dev_dbg(&xd->dev, "local UUID %pUb\n", local_uuid);
	अगर (remote_uuid)
		dev_dbg(&xd->dev, "remote UUID %pUb\n", remote_uuid);

	/*
	 * This keeps the DMA घातered on as दीर्घ as we have active
	 * connection to another host.
	 */
	pm_runसमय_set_active(&xd->dev);
	pm_runसमय_get_noresume(&xd->dev);
	pm_runसमय_enable(&xd->dev);

	वापस xd;

err_मुक्त_local_uuid:
	kमुक्त(xd->local_uuid);
err_मुक्त:
	kमुक्त(xd);

	वापस शून्य;
पूर्ण

/**
 * tb_xकरोमुख्य_add() - Add XDoमुख्य to the bus
 * @xd: XDoमुख्य to add
 *
 * This function starts XDoमुख्य discovery protocol handshake and
 * eventually adds the XDoमुख्य to the bus. After calling this function
 * the caller needs to call tb_xकरोमुख्य_हटाओ() in order to हटाओ and
 * release the object regardless whether the handshake succeeded or not.
 */
व्योम tb_xकरोमुख्य_add(काष्ठा tb_xकरोमुख्य *xd)
अणु
	/* Start exchanging properties with the other host */
	start_handshake(xd);
पूर्ण

अटल पूर्णांक unरेजिस्टर_service(काष्ठा device *dev, व्योम *data)
अणु
	device_unरेजिस्टर(dev);
	वापस 0;
पूर्ण

/**
 * tb_xकरोमुख्य_हटाओ() - Remove XDoमुख्य from the bus
 * @xd: XDoमुख्य to हटाओ
 *
 * This will stop all ongoing configuration work and हटाओ the XDoमुख्य
 * aदीर्घ with any services from the bus. When the last reference to @xd
 * is released the object will be released as well.
 */
व्योम tb_xकरोमुख्य_हटाओ(काष्ठा tb_xकरोमुख्य *xd)
अणु
	stop_handshake(xd);

	device_क्रम_each_child_reverse(&xd->dev, xd, unरेजिस्टर_service);

	/*
	 * Unकरो runसमय PM here explicitly because it is possible that
	 * the XDoमुख्य was never added to the bus and thus device_del()
	 * is not called क्रम it (device_del() would handle this otherwise).
	 */
	pm_runसमय_disable(&xd->dev);
	pm_runसमय_put_noidle(&xd->dev);
	pm_runसमय_set_suspended(&xd->dev);

	अगर (!device_is_रेजिस्टरed(&xd->dev)) अणु
		put_device(&xd->dev);
	पूर्ण अन्यथा अणु
		dev_info(&xd->dev, "host disconnected\n");
		device_unरेजिस्टर(&xd->dev);
	पूर्ण
पूर्ण

/**
 * tb_xकरोमुख्य_lane_bonding_enable() - Enable lane bonding on XDoमुख्य
 * @xd: XDoमुख्य connection
 *
 * Lane bonding is disabled by शेष क्रम XDoमुख्यs. This function tries
 * to enable bonding by first enabling the port and रुकोing क्रम the CL0
 * state.
 *
 * Return: %0 in हाल of success and negative त्रुटि_सं in हाल of error.
 */
पूर्णांक tb_xकरोमुख्य_lane_bonding_enable(काष्ठा tb_xकरोमुख्य *xd)
अणु
	काष्ठा tb_port *port;
	पूर्णांक ret;

	port = tb_port_at(xd->route, tb_xकरोमुख्य_parent(xd));
	अगर (!port->dual_link_port)
		वापस -ENODEV;

	ret = tb_port_enable(port->dual_link_port);
	अगर (ret)
		वापस ret;

	ret = tb_रुको_क्रम_port(port->dual_link_port, true);
	अगर (ret < 0)
		वापस ret;
	अगर (!ret)
		वापस -ENOTCONN;

	ret = tb_port_lane_bonding_enable(port);
	अगर (ret) अणु
		tb_port_warn(port, "failed to enable lane bonding\n");
		वापस ret;
	पूर्ण

	tb_xकरोमुख्य_update_link_attributes(xd);

	dev_dbg(&xd->dev, "lane bonding enabled\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_lane_bonding_enable);

/**
 * tb_xकरोमुख्य_lane_bonding_disable() - Disable lane bonding
 * @xd: XDoमुख्य connection
 *
 * Lane bonding is disabled by शेष क्रम XDoमुख्यs. If bonding has been
 * enabled, this function can be used to disable it.
 */
व्योम tb_xकरोमुख्य_lane_bonding_disable(काष्ठा tb_xकरोमुख्य *xd)
अणु
	काष्ठा tb_port *port;

	port = tb_port_at(xd->route, tb_xकरोमुख्य_parent(xd));
	अगर (port->dual_link_port) अणु
		tb_port_lane_bonding_disable(port);
		tb_port_disable(port->dual_link_port);
		tb_xकरोमुख्य_update_link_attributes(xd);

		dev_dbg(&xd->dev, "lane bonding disabled\n");
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_lane_bonding_disable);

/**
 * tb_xकरोमुख्य_alloc_in_hopid() - Allocate input HopID क्रम tunneling
 * @xd: XDoमुख्य connection
 * @hopid: Preferred HopID or %-1 क्रम next available
 *
 * Returns allocated HopID or negative त्रुटि_सं. Specअगरically वापसs
 * %-ENOSPC अगर there are no more available HopIDs. Returned HopID is
 * guaranteed to be within range supported by the input lane adapter.
 * Call tb_xकरोमुख्य_release_in_hopid() to release the allocated HopID.
 */
पूर्णांक tb_xकरोमुख्य_alloc_in_hopid(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक hopid)
अणु
	अगर (hopid < 0)
		hopid = TB_PATH_MIN_HOPID;
	अगर (hopid < TB_PATH_MIN_HOPID || hopid > xd->local_max_hopid)
		वापस -EINVAL;

	वापस ida_alloc_range(&xd->in_hopids, hopid, xd->local_max_hopid,
			       GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_alloc_in_hopid);

/**
 * tb_xकरोमुख्य_alloc_out_hopid() - Allocate output HopID क्रम tunneling
 * @xd: XDoमुख्य connection
 * @hopid: Preferred HopID or %-1 क्रम next available
 *
 * Returns allocated HopID or negative त्रुटि_सं. Specअगरically वापसs
 * %-ENOSPC अगर there are no more available HopIDs. Returned HopID is
 * guaranteed to be within range supported by the output lane adapter.
 * Call tb_xकरोमुख्य_release_in_hopid() to release the allocated HopID.
 */
पूर्णांक tb_xकरोमुख्य_alloc_out_hopid(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक hopid)
अणु
	अगर (hopid < 0)
		hopid = TB_PATH_MIN_HOPID;
	अगर (hopid < TB_PATH_MIN_HOPID || hopid > xd->remote_max_hopid)
		वापस -EINVAL;

	वापस ida_alloc_range(&xd->out_hopids, hopid, xd->remote_max_hopid,
			       GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_alloc_out_hopid);

/**
 * tb_xकरोमुख्य_release_in_hopid() - Release input HopID
 * @xd: XDoमुख्य connection
 * @hopid: HopID to release
 */
व्योम tb_xकरोमुख्य_release_in_hopid(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक hopid)
अणु
	ida_मुक्त(&xd->in_hopids, hopid);
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_release_in_hopid);

/**
 * tb_xकरोमुख्य_release_out_hopid() - Release output HopID
 * @xd: XDoमुख्य connection
 * @hopid: HopID to release
 */
व्योम tb_xकरोमुख्य_release_out_hopid(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक hopid)
अणु
	ida_मुक्त(&xd->out_hopids, hopid);
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_release_out_hopid);

/**
 * tb_xकरोमुख्य_enable_paths() - Enable DMA paths क्रम XDoमुख्य connection
 * @xd: XDoमुख्य connection
 * @transmit_path: HopID we are using to send out packets
 * @transmit_ring: DMA ring used to send out packets
 * @receive_path: HopID the other end is using to send packets to us
 * @receive_ring: DMA ring used to receive packets from @receive_path
 *
 * The function enables DMA paths accordingly so that after successful
 * वापस the caller can send and receive packets using high-speed DMA
 * path. If a transmit or receive path is not needed, pass %-1 क्रम those
 * parameters.
 *
 * Return: %0 in हाल of success and negative त्रुटि_सं in हाल of error
 */
पूर्णांक tb_xकरोमुख्य_enable_paths(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक transmit_path,
			    पूर्णांक transmit_ring, पूर्णांक receive_path,
			    पूर्णांक receive_ring)
अणु
	वापस tb_करोमुख्य_approve_xकरोमुख्य_paths(xd->tb, xd, transmit_path,
					       transmit_ring, receive_path,
					       receive_ring);
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_enable_paths);

/**
 * tb_xकरोमुख्य_disable_paths() - Disable DMA paths क्रम XDoमुख्य connection
 * @xd: XDoमुख्य connection
 * @transmit_path: HopID we are using to send out packets
 * @transmit_ring: DMA ring used to send out packets
 * @receive_path: HopID the other end is using to send packets to us
 * @receive_ring: DMA ring used to receive packets from @receive_path
 *
 * This करोes the opposite of tb_xकरोमुख्य_enable_paths(). After call to
 * this the caller is not expected to use the rings anymore. Passing %-1
 * as path/ring parameter means करोn't care. Normally the callers should
 * pass the same values here as they करो when paths are enabled.
 *
 * Return: %0 in हाल of success and negative त्रुटि_सं in हाल of error
 */
पूर्णांक tb_xकरोमुख्य_disable_paths(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक transmit_path,
			     पूर्णांक transmit_ring, पूर्णांक receive_path,
			     पूर्णांक receive_ring)
अणु
	वापस tb_करोमुख्य_disconnect_xकरोमुख्य_paths(xd->tb, xd, transmit_path,
						  transmit_ring, receive_path,
						  receive_ring);
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_disable_paths);

काष्ठा tb_xकरोमुख्य_lookup अणु
	स्थिर uuid_t *uuid;
	u8 link;
	u8 depth;
	u64 route;
पूर्ण;

अटल काष्ठा tb_xकरोमुख्य *चयन_find_xकरोमुख्य(काष्ठा tb_चयन *sw,
	स्थिर काष्ठा tb_xकरोमुख्य_lookup *lookup)
अणु
	काष्ठा tb_port *port;

	tb_चयन_क्रम_each_port(sw, port) अणु
		काष्ठा tb_xकरोमुख्य *xd;

		अगर (port->xकरोमुख्य) अणु
			xd = port->xकरोमुख्य;

			अगर (lookup->uuid) अणु
				अगर (xd->remote_uuid &&
				    uuid_equal(xd->remote_uuid, lookup->uuid))
					वापस xd;
			पूर्ण अन्यथा अगर (lookup->link &&
				   lookup->link == xd->link &&
				   lookup->depth == xd->depth) अणु
				वापस xd;
			पूर्ण अन्यथा अगर (lookup->route &&
				   lookup->route == xd->route) अणु
				वापस xd;
			पूर्ण
		पूर्ण अन्यथा अगर (tb_port_has_remote(port)) अणु
			xd = चयन_find_xकरोमुख्य(port->remote->sw, lookup);
			अगर (xd)
				वापस xd;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * tb_xकरोमुख्य_find_by_uuid() - Find an XDoमुख्य by UUID
 * @tb: Doमुख्य where the XDoमुख्य beदीर्घs to
 * @uuid: UUID to look क्रम
 *
 * Finds XDoमुख्य by walking through the Thunderbolt topology below @tb.
 * The वापसed XDoमुख्य will have its reference count increased so the
 * caller needs to call tb_xकरोमुख्य_put() when it is करोne with the
 * object.
 *
 * This will find all XDoमुख्यs including the ones that are not yet added
 * to the bus (handshake is still in progress).
 *
 * The caller needs to hold @tb->lock.
 */
काष्ठा tb_xकरोमुख्य *tb_xकरोमुख्य_find_by_uuid(काष्ठा tb *tb, स्थिर uuid_t *uuid)
अणु
	काष्ठा tb_xकरोमुख्य_lookup lookup;
	काष्ठा tb_xकरोमुख्य *xd;

	स_रखो(&lookup, 0, माप(lookup));
	lookup.uuid = uuid;

	xd = चयन_find_xकरोमुख्य(tb->root_चयन, &lookup);
	वापस tb_xकरोमुख्य_get(xd);
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_find_by_uuid);

/**
 * tb_xकरोमुख्य_find_by_link_depth() - Find an XDoमुख्य by link and depth
 * @tb: Doमुख्य where the XDoमुख्य beदीर्घs to
 * @link: Root चयन link number
 * @depth: Depth in the link
 *
 * Finds XDoमुख्य by walking through the Thunderbolt topology below @tb.
 * The वापसed XDoमुख्य will have its reference count increased so the
 * caller needs to call tb_xकरोमुख्य_put() when it is करोne with the
 * object.
 *
 * This will find all XDoमुख्यs including the ones that are not yet added
 * to the bus (handshake is still in progress).
 *
 * The caller needs to hold @tb->lock.
 */
काष्ठा tb_xकरोमुख्य *tb_xकरोमुख्य_find_by_link_depth(काष्ठा tb *tb, u8 link,
						 u8 depth)
अणु
	काष्ठा tb_xकरोमुख्य_lookup lookup;
	काष्ठा tb_xकरोमुख्य *xd;

	स_रखो(&lookup, 0, माप(lookup));
	lookup.link = link;
	lookup.depth = depth;

	xd = चयन_find_xकरोमुख्य(tb->root_चयन, &lookup);
	वापस tb_xकरोमुख्य_get(xd);
पूर्ण

/**
 * tb_xकरोमुख्य_find_by_route() - Find an XDoमुख्य by route string
 * @tb: Doमुख्य where the XDoमुख्य beदीर्घs to
 * @route: XDoमुख्य route string
 *
 * Finds XDoमुख्य by walking through the Thunderbolt topology below @tb.
 * The वापसed XDoमुख्य will have its reference count increased so the
 * caller needs to call tb_xकरोमुख्य_put() when it is करोne with the
 * object.
 *
 * This will find all XDoमुख्यs including the ones that are not yet added
 * to the bus (handshake is still in progress).
 *
 * The caller needs to hold @tb->lock.
 */
काष्ठा tb_xकरोमुख्य *tb_xकरोमुख्य_find_by_route(काष्ठा tb *tb, u64 route)
अणु
	काष्ठा tb_xकरोमुख्य_lookup lookup;
	काष्ठा tb_xकरोमुख्य *xd;

	स_रखो(&lookup, 0, माप(lookup));
	lookup.route = route;

	xd = चयन_find_xकरोमुख्य(tb->root_चयन, &lookup);
	वापस tb_xकरोमुख्य_get(xd);
पूर्ण
EXPORT_SYMBOL_GPL(tb_xकरोमुख्य_find_by_route);

bool tb_xकरोमुख्य_handle_request(काष्ठा tb *tb, क्रमागत tb_cfg_pkg_type type,
			       स्थिर व्योम *buf, माप_प्रकार size)
अणु
	स्थिर काष्ठा tb_protocol_handler *handler, *पंचांगp;
	स्थिर काष्ठा tb_xdp_header *hdr = buf;
	अचिन्हित पूर्णांक length;
	पूर्णांक ret = 0;

	/* We expect the packet is at least size of the header */
	length = hdr->xd_hdr.length_sn & TB_XDOMAIN_LENGTH_MASK;
	अगर (length != size / 4 - माप(hdr->xd_hdr) / 4)
		वापस true;
	अगर (length < माप(*hdr) / 4 - माप(hdr->xd_hdr) / 4)
		वापस true;

	/*
	 * Handle XDoमुख्य discovery protocol packets directly here. For
	 * other protocols (based on their UUID) we call रेजिस्टरed
	 * handlers in turn.
	 */
	अगर (uuid_equal(&hdr->uuid, &tb_xdp_uuid)) अणु
		अगर (type == TB_CFG_PKG_XDOMAIN_REQ)
			वापस tb_xdp_schedule_request(tb, hdr, size);
		वापस false;
	पूर्ण

	mutex_lock(&xकरोमुख्य_lock);
	list_क्रम_each_entry_safe(handler, पंचांगp, &protocol_handlers, list) अणु
		अगर (!uuid_equal(&hdr->uuid, handler->uuid))
			जारी;

		mutex_unlock(&xकरोमुख्य_lock);
		ret = handler->callback(buf, size, handler->data);
		mutex_lock(&xकरोमुख्य_lock);

		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&xकरोमुख्य_lock);

	वापस ret > 0;
पूर्ण

अटल पूर्णांक update_xकरोमुख्य(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा tb_xकरोमुख्य *xd;

	xd = tb_to_xकरोमुख्य(dev);
	अगर (xd) अणु
		queue_delayed_work(xd->tb->wq, &xd->properties_changed_work,
				   msecs_to_jअगरfies(50));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम update_all_xकरोमुख्यs(व्योम)
अणु
	bus_क्रम_each_dev(&tb_bus_type, शून्य, शून्य, update_xकरोमुख्य);
पूर्ण

अटल bool हटाओ_directory(स्थिर अक्षर *key, स्थिर काष्ठा tb_property_dir *dir)
अणु
	काष्ठा tb_property *p;

	p = tb_property_find(xकरोमुख्य_property_dir, key,
			     TB_PROPERTY_TYPE_सूचीECTORY);
	अगर (p && p->value.dir == dir) अणु
		tb_property_हटाओ(p);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * tb_रेजिस्टर_property_dir() - Register property directory to the host
 * @key: Key (name) of the directory to add
 * @dir: Directory to add
 *
 * Service drivers can use this function to add new property directory
 * to the host available properties. The other connected hosts are
 * notअगरied so they can re-पढ़ो properties of this host अगर they are
 * पूर्णांकerested.
 *
 * Return: %0 on success and negative त्रुटि_सं on failure
 */
पूर्णांक tb_रेजिस्टर_property_dir(स्थिर अक्षर *key, काष्ठा tb_property_dir *dir)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(!xकरोमुख्य_property_dir))
		वापस -EAGAIN;

	अगर (!key || म_माप(key) > 8)
		वापस -EINVAL;

	mutex_lock(&xकरोमुख्य_lock);
	अगर (tb_property_find(xकरोमुख्य_property_dir, key,
			     TB_PROPERTY_TYPE_सूचीECTORY)) अणु
		ret = -EEXIST;
		जाओ err_unlock;
	पूर्ण

	ret = tb_property_add_dir(xकरोमुख्य_property_dir, key, dir);
	अगर (ret)
		जाओ err_unlock;

	xकरोमुख्य_property_block_gen++;

	mutex_unlock(&xकरोमुख्य_lock);
	update_all_xकरोमुख्यs();
	वापस 0;

err_unlock:
	mutex_unlock(&xकरोमुख्य_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tb_रेजिस्टर_property_dir);

/**
 * tb_unरेजिस्टर_property_dir() - Removes property directory from host
 * @key: Key (name) of the directory
 * @dir: Directory to हटाओ
 *
 * This will हटाओ the existing directory from this host and notअगरy the
 * connected hosts about the change.
 */
व्योम tb_unरेजिस्टर_property_dir(स्थिर अक्षर *key, काष्ठा tb_property_dir *dir)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&xकरोमुख्य_lock);
	अगर (हटाओ_directory(key, dir))
		xकरोमुख्य_property_block_gen++;
	mutex_unlock(&xकरोमुख्य_lock);

	अगर (!ret)
		update_all_xकरोमुख्यs();
पूर्ण
EXPORT_SYMBOL_GPL(tb_unरेजिस्टर_property_dir);

पूर्णांक tb_xकरोमुख्य_init(व्योम)
अणु
	xकरोमुख्य_property_dir = tb_property_create_dir(शून्य);
	अगर (!xकरोमुख्य_property_dir)
		वापस -ENOMEM;

	/*
	 * Initialize standard set of properties without any service
	 * directories. Those will be added by service drivers
	 * themselves when they are loaded.
	 *
	 * Rest of the properties are filled dynamically based on these
	 * when the P2P connection is made.
	 */
	tb_property_add_immediate(xकरोमुख्य_property_dir, "vendorid",
				  PCI_VENDOR_ID_INTEL);
	tb_property_add_text(xकरोमुख्य_property_dir, "vendorid", "Intel Corp.");
	tb_property_add_immediate(xकरोमुख्य_property_dir, "deviceid", 0x1);
	tb_property_add_immediate(xकरोमुख्य_property_dir, "devicerv", 0x80000100);

	xकरोमुख्य_property_block_gen = pअक्रमom_u32();
	वापस 0;
पूर्ण

व्योम tb_xकरोमुख्य_निकास(व्योम)
अणु
	tb_property_मुक्त_dir(xकरोमुख्य_property_dir);
पूर्ण
