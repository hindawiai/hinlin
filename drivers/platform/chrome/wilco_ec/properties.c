<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Google LLC
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_data/wilco-ec.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/unaligned.h>

/* Operation code; what the EC should करो with the property */
क्रमागत ec_property_op अणु
	EC_OP_GET = 0,
	EC_OP_SET = 1,
पूर्ण;

काष्ठा ec_property_request अणु
	u8 op; /* One of क्रमागत ec_property_op */
	u8 property_id[4]; /* The 32 bit PID is stored Little Endian */
	u8 length;
	u8 data[WILCO_EC_PROPERTY_MAX_SIZE];
पूर्ण __packed;

काष्ठा ec_property_response अणु
	u8 reserved[2];
	u8 op; /* One of क्रमागत ec_property_op */
	u8 property_id[4]; /* The 32 bit PID is stored Little Endian */
	u8 length;
	u8 data[WILCO_EC_PROPERTY_MAX_SIZE];
पूर्ण __packed;

अटल पूर्णांक send_property_msg(काष्ठा wilco_ec_device *ec,
			     काष्ठा ec_property_request *rq,
			     काष्ठा ec_property_response *rs)
अणु
	काष्ठा wilco_ec_message ec_msg;
	पूर्णांक ret;

	स_रखो(&ec_msg, 0, माप(ec_msg));
	ec_msg.type = WILCO_EC_MSG_PROPERTY;
	ec_msg.request_data = rq;
	ec_msg.request_size = माप(*rq);
	ec_msg.response_data = rs;
	ec_msg.response_size = माप(*rs);

	ret = wilco_ec_mailbox(ec, &ec_msg);
	अगर (ret < 0)
		वापस ret;
	अगर (rs->op != rq->op)
		वापस -EBADMSG;
	अगर (स_भेद(rq->property_id, rs->property_id, माप(rs->property_id)))
		वापस -EBADMSG;

	वापस 0;
पूर्ण

पूर्णांक wilco_ec_get_property(काष्ठा wilco_ec_device *ec,
			  काष्ठा wilco_ec_property_msg *prop_msg)
अणु
	काष्ठा ec_property_request rq;
	काष्ठा ec_property_response rs;
	पूर्णांक ret;

	स_रखो(&rq, 0, माप(rq));
	rq.op = EC_OP_GET;
	put_unaligned_le32(prop_msg->property_id, rq.property_id);

	ret = send_property_msg(ec, &rq, &rs);
	अगर (ret < 0)
		वापस ret;

	prop_msg->length = rs.length;
	स_नकल(prop_msg->data, rs.data, rs.length);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wilco_ec_get_property);

पूर्णांक wilco_ec_set_property(काष्ठा wilco_ec_device *ec,
			  काष्ठा wilco_ec_property_msg *prop_msg)
अणु
	काष्ठा ec_property_request rq;
	काष्ठा ec_property_response rs;
	पूर्णांक ret;

	स_रखो(&rq, 0, माप(rq));
	rq.op = EC_OP_SET;
	put_unaligned_le32(prop_msg->property_id, rq.property_id);
	rq.length = prop_msg->length;
	स_नकल(rq.data, prop_msg->data, prop_msg->length);

	ret = send_property_msg(ec, &rq, &rs);
	अगर (ret < 0)
		वापस ret;
	अगर (rs.length != prop_msg->length)
		वापस -EBADMSG;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wilco_ec_set_property);

पूर्णांक wilco_ec_get_byte_property(काष्ठा wilco_ec_device *ec, u32 property_id,
			       u8 *val)
अणु
	काष्ठा wilco_ec_property_msg msg;
	पूर्णांक ret;

	msg.property_id = property_id;

	ret = wilco_ec_get_property(ec, &msg);
	अगर (ret < 0)
		वापस ret;
	अगर (msg.length != 1)
		वापस -EBADMSG;

	*val = msg.data[0];

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wilco_ec_get_byte_property);

पूर्णांक wilco_ec_set_byte_property(काष्ठा wilco_ec_device *ec, u32 property_id,
			       u8 val)
अणु
	काष्ठा wilco_ec_property_msg msg;

	msg.property_id = property_id;
	msg.data[0] = val;
	msg.length = 1;

	वापस wilco_ec_set_property(ec, &msg);
पूर्ण
EXPORT_SYMBOL_GPL(wilco_ec_set_byte_property);
