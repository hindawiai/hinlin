<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AMD MP2 Sensors transport driver
 *
 * Authors: Nehal Bakulchandra Shah <Nehal-bakulchandra.shah@amd.com>
 *	    Sandeep Singh <sandeep.singh@amd.com>
 */
#समावेश <linux/hid.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>

#समावेश "amd_sfh_hid.h"

#घोषणा AMD_SFH_RESPONSE_TIMEOUT	1500

/**
 * amdtp_hid_parse() - hid-core .parse() callback
 * @hid:	hid device instance
 *
 * This function माला_लो called during call to hid_add_device
 *
 * Return: 0 on success and non zero on error
 */
अटल पूर्णांक amdtp_hid_parse(काष्ठा hid_device *hid)
अणु
	काष्ठा amdtp_hid_data *hid_data = hid->driver_data;
	काष्ठा amdtp_cl_data *cli_data = hid_data->cli_data;

	वापस hid_parse_report(hid, cli_data->report_descr[hid_data->index],
			      cli_data->report_descr_sz[hid_data->index]);
पूर्ण

/* Empty callbacks with success वापस code */
अटल पूर्णांक amdtp_hid_start(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण

अटल व्योम amdtp_hid_stop(काष्ठा hid_device *hid)
अणु
पूर्ण

अटल पूर्णांक amdtp_hid_खोलो(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण

अटल व्योम amdtp_hid_बंद(काष्ठा hid_device *hid)
अणु
पूर्ण

अटल पूर्णांक amdtp_raw_request(काष्ठा hid_device *hdev, u8 reportnum,
			     u8 *buf, माप_प्रकार len, u8 rtype, पूर्णांक reqtype)
अणु
	वापस 0;
पूर्ण

अटल व्योम amdtp_hid_request(काष्ठा hid_device *hid, काष्ठा hid_report *rep, पूर्णांक reqtype)
अणु
	पूर्णांक rc;

	चयन (reqtype) अणु
	हाल HID_REQ_GET_REPORT:
		rc = amd_sfh_get_report(hid, rep->id, rep->type);
		अगर (rc)
			dev_err(&hid->dev, "AMDSFH  get report error\n");
		अवरोध;
	हाल HID_REQ_SET_REPORT:
		amd_sfh_set_report(hid, rep->id, reqtype);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक amdtp_रुको_क्रम_response(काष्ठा hid_device *hid)
अणु
	काष्ठा amdtp_hid_data *hid_data =  hid->driver_data;
	काष्ठा amdtp_cl_data *cli_data = hid_data->cli_data;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < cli_data->num_hid_devices; i++) अणु
		अगर (cli_data->hid_sensor_hubs[i] == hid)
			अवरोध;
	पूर्ण

	अगर (!cli_data->request_करोne[i])
		ret = रुको_event_पूर्णांकerruptible_समयout(hid_data->hid_रुको,
						       cli_data->request_करोne[i],
						       msecs_to_jअगरfies(AMD_SFH_RESPONSE_TIMEOUT));
	अगर (ret == -ERESTARTSYS)
		वापस -ERESTARTSYS;
	अन्यथा अगर (ret < 0)
		वापस -ETIMEDOUT;
	अन्यथा
		वापस 0;
पूर्ण

व्योम amdtp_hid_wakeup(काष्ठा hid_device *hid)
अणु
	काष्ठा amdtp_hid_data *hid_data = hid->driver_data;
	काष्ठा amdtp_cl_data *cli_data = hid_data->cli_data;

	cli_data->request_करोne[cli_data->cur_hid_dev] = true;
	wake_up_पूर्णांकerruptible(&hid_data->hid_रुको);
पूर्ण

अटल काष्ठा hid_ll_driver amdtp_hid_ll_driver = अणु
	.parse	=	amdtp_hid_parse,
	.start	=	amdtp_hid_start,
	.stop	=	amdtp_hid_stop,
	.खोलो	=	amdtp_hid_खोलो,
	.बंद	=	amdtp_hid_बंद,
	.request  =	amdtp_hid_request,
	.रुको	=	amdtp_रुको_क्रम_response,
	.raw_request  =	amdtp_raw_request,
पूर्ण;

पूर्णांक amdtp_hid_probe(u32 cur_hid_dev, काष्ठा amdtp_cl_data *cli_data)
अणु
	काष्ठा hid_device *hid;
	काष्ठा amdtp_hid_data *hid_data;
	पूर्णांक rc;

	hid = hid_allocate_device();
	अगर (IS_ERR(hid))
		वापस PTR_ERR(hid);

	hid_data = kzalloc(माप(*hid_data), GFP_KERNEL);
	अगर (!hid_data) अणु
		rc = -ENOMEM;
		जाओ err_hid_data;
	पूर्ण

	hid->ll_driver = &amdtp_hid_ll_driver;
	hid_data->index = cur_hid_dev;
	hid_data->cli_data = cli_data;
	init_रुकोqueue_head(&hid_data->hid_रुको);

	hid->driver_data = hid_data;
	cli_data->hid_sensor_hubs[cur_hid_dev] = hid;
	hid->bus = BUS_AMD_AMDTP;
	hid->venकरोr = AMD_SFH_HID_VENDOR;
	hid->product = AMD_SFH_HID_PRODUCT;
	snम_लिखो(hid->name, माप(hid->name), "%s %04X:%04X", "hid-amdtp",
		 hid->venकरोr, hid->product);

	rc = hid_add_device(hid);
	अगर (rc)
		जाओ err_hid_device;
	वापस 0;

err_hid_device:
	kमुक्त(hid_data);
err_hid_data:
	hid_destroy_device(hid);
	वापस rc;
पूर्ण

व्योम amdtp_hid_हटाओ(काष्ठा amdtp_cl_data *cli_data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cli_data->num_hid_devices; ++i) अणु
		अगर (cli_data->hid_sensor_hubs[i]) अणु
			kमुक्त(cli_data->hid_sensor_hubs[i]->driver_data);
			hid_destroy_device(cli_data->hid_sensor_hubs[i]);
			cli_data->hid_sensor_hubs[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
