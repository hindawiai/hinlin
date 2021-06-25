<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  AMD SFH Client Layer
 *  Copyright 2020 Advanced Micro Devices, Inc.
 *  Authors: Nehal Bakulchandra Shah <Nehal-Bakulchandra.Shah@amd.com>
 *	     Sandeep Singh <Sandeep.singh@amd.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/hid.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश "hid_descriptor/amd_sfh_hid_desc.h"
#समावेश "amd_sfh_pcie.h"
#समावेश "amd_sfh_hid.h"

#घोषणा AMD_SFH_IDLE_LOOP	200

काष्ठा request_list अणु
	काष्ठा hid_device *hid;
	काष्ठा list_head list;
	u8 report_id;
	u8 sensor_idx;
	u8 report_type;
	u8 current_index;
पूर्ण;

अटल काष्ठा request_list req_list;

व्योम amd_sfh_set_report(काष्ठा hid_device *hid, पूर्णांक report_id,
			पूर्णांक report_type)
अणु
	काष्ठा amdtp_hid_data *hid_data = hid->driver_data;
	काष्ठा amdtp_cl_data *cli_data = hid_data->cli_data;
	पूर्णांक i;

	क्रम (i = 0; i < cli_data->num_hid_devices; i++) अणु
		अगर (cli_data->hid_sensor_hubs[i] == hid) अणु
			cli_data->cur_hid_dev = i;
			अवरोध;
		पूर्ण
	पूर्ण
	amdtp_hid_wakeup(hid);
पूर्ण

पूर्णांक amd_sfh_get_report(काष्ठा hid_device *hid, पूर्णांक report_id, पूर्णांक report_type)
अणु
	काष्ठा amdtp_hid_data *hid_data = hid->driver_data;
	काष्ठा amdtp_cl_data *cli_data = hid_data->cli_data;
	पूर्णांक i;

	क्रम (i = 0; i < cli_data->num_hid_devices; i++) अणु
		अगर (cli_data->hid_sensor_hubs[i] == hid) अणु
			काष्ठा request_list *new = kzalloc(माप(*new), GFP_KERNEL);

			अगर (!new)
				वापस -ENOMEM;

			new->current_index = i;
			new->sensor_idx = cli_data->sensor_idx[i];
			new->hid = hid;
			new->report_type = report_type;
			new->report_id = report_id;
			cli_data->report_id[i] = report_id;
			cli_data->request_करोne[i] = false;
			list_add(&new->list, &req_list.list);
			अवरोध;
		पूर्ण
	पूर्ण
	schedule_delayed_work(&cli_data->work, 0);
	वापस 0;
पूर्ण

अटल व्योम amd_sfh_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdtp_cl_data *cli_data = container_of(work, काष्ठा amdtp_cl_data, work.work);
	काष्ठा request_list *req_node;
	u8 current_index, sensor_index;
	u8 report_id, node_type;
	u8 report_size = 0;

	req_node = list_last_entry(&req_list.list, काष्ठा request_list, list);
	list_del(&req_node->list);
	current_index = req_node->current_index;
	sensor_index = req_node->sensor_idx;
	report_id = req_node->report_id;
	node_type = req_node->report_type;
	kमुक्त(req_node);

	अगर (node_type == HID_FEATURE_REPORT) अणु
		report_size = get_feature_report(sensor_index, report_id,
						 cli_data->feature_report[current_index]);
		अगर (report_size)
			hid_input_report(cli_data->hid_sensor_hubs[current_index],
					 cli_data->report_type[current_index],
					 cli_data->feature_report[current_index], report_size, 0);
		अन्यथा
			pr_err("AMDSFH: Invalid report size\n");

	पूर्ण अन्यथा अगर (node_type == HID_INPUT_REPORT) अणु
		report_size = get_input_report(sensor_index, report_id,
					       cli_data->input_report[current_index],
					       cli_data->sensor_virt_addr[current_index]);
		अगर (report_size)
			hid_input_report(cli_data->hid_sensor_hubs[current_index],
					 cli_data->report_type[current_index],
					 cli_data->input_report[current_index], report_size, 0);
		अन्यथा
			pr_err("AMDSFH: Invalid report size\n");
	पूर्ण
	cli_data->cur_hid_dev = current_index;
	cli_data->sensor_requested_cnt[current_index] = 0;
	amdtp_hid_wakeup(cli_data->hid_sensor_hubs[current_index]);
पूर्ण

अटल व्योम amd_sfh_work_buffer(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdtp_cl_data *cli_data = container_of(work, काष्ठा amdtp_cl_data, work_buffer.work);
	u8 report_size;
	पूर्णांक i;

	क्रम (i = 0; i < cli_data->num_hid_devices; i++) अणु
		report_size = get_input_report(cli_data->sensor_idx[i], cli_data->report_id[i],
					       cli_data->input_report[i],
					       cli_data->sensor_virt_addr[i]);
		hid_input_report(cli_data->hid_sensor_hubs[i], HID_INPUT_REPORT,
				 cli_data->input_report[i], report_size, 0);
	पूर्ण
	schedule_delayed_work(&cli_data->work_buffer, msecs_to_jअगरfies(AMD_SFH_IDLE_LOOP));
पूर्ण

पूर्णांक amd_sfh_hid_client_init(काष्ठा amd_mp2_dev *privdata)
अणु
	काष्ठा amdtp_cl_data *cl_data = privdata->cl_data;
	काष्ठा amd_mp2_sensor_info info;
	काष्ठा device *dev;
	u32 feature_report_size;
	u32 input_report_size;
	u8 cl_idx;
	पूर्णांक rc, i;

	dev = &privdata->pdev->dev;
	cl_data = devm_kzalloc(dev, माप(*cl_data), GFP_KERNEL);
	अगर (!cl_data)
		वापस -ENOMEM;

	cl_data->num_hid_devices = amd_mp2_get_sensor_num(privdata, &cl_data->sensor_idx[0]);

	INIT_DELAYED_WORK(&cl_data->work, amd_sfh_work);
	INIT_DELAYED_WORK(&cl_data->work_buffer, amd_sfh_work_buffer);
	INIT_LIST_HEAD(&req_list.list);

	क्रम (i = 0; i < cl_data->num_hid_devices; i++) अणु
		cl_data->sensor_virt_addr[i] = dma_alloc_coherent(dev, माप(पूर्णांक) * 8,
								  &cl_data->sensor_dma_addr[i],
								  GFP_KERNEL);
		cl_data->sensor_sts[i] = 0;
		cl_data->sensor_requested_cnt[i] = 0;
		cl_data->cur_hid_dev = i;
		cl_idx = cl_data->sensor_idx[i];
		cl_data->report_descr_sz[i] = get_descr_sz(cl_idx, descr_size);
		अगर (!cl_data->report_descr_sz[i]) अणु
			rc = -EINVAL;
			जाओ cleanup;
		पूर्ण
		feature_report_size = get_descr_sz(cl_idx, feature_size);
		अगर (!feature_report_size) अणु
			rc = -EINVAL;
			जाओ cleanup;
		पूर्ण
		input_report_size =  get_descr_sz(cl_idx, input_size);
		अगर (!input_report_size) अणु
			rc = -EINVAL;
			जाओ cleanup;
		पूर्ण
		cl_data->feature_report[i] = devm_kzalloc(dev, feature_report_size, GFP_KERNEL);
		अगर (!cl_data->feature_report[i]) अणु
			rc = -ENOMEM;
			जाओ cleanup;
		पूर्ण
		cl_data->input_report[i] = devm_kzalloc(dev, input_report_size, GFP_KERNEL);
		अगर (!cl_data->input_report[i]) अणु
			rc = -ENOMEM;
			जाओ cleanup;
		पूर्ण
		info.period = msecs_to_jअगरfies(AMD_SFH_IDLE_LOOP);
		info.sensor_idx = cl_idx;
		info.dma_address = cl_data->sensor_dma_addr[i];

		cl_data->report_descr[i] =
			devm_kzalloc(dev, cl_data->report_descr_sz[i], GFP_KERNEL);
		अगर (!cl_data->report_descr[i]) अणु
			rc = -ENOMEM;
			जाओ cleanup;
		पूर्ण
		rc = get_report_descriptor(cl_idx, cl_data->report_descr[i]);
		अगर (rc)
			वापस rc;
		rc = amdtp_hid_probe(cl_data->cur_hid_dev, cl_data);
		अगर (rc)
			वापस rc;
		amd_start_sensor(privdata, info);
		cl_data->sensor_sts[i] = 1;
	पूर्ण
	privdata->cl_data = cl_data;
	schedule_delayed_work(&cl_data->work_buffer, msecs_to_jअगरfies(AMD_SFH_IDLE_LOOP));
	वापस 0;

cleanup:
	क्रम (i = 0; i < cl_data->num_hid_devices; i++) अणु
		अगर (cl_data->sensor_virt_addr[i]) अणु
			dma_मुक्त_coherent(&privdata->pdev->dev, 8 * माप(पूर्णांक),
					  cl_data->sensor_virt_addr[i],
					  cl_data->sensor_dma_addr[i]);
		पूर्ण
		devm_kमुक्त(dev, cl_data->feature_report[i]);
		devm_kमुक्त(dev, cl_data->input_report[i]);
		devm_kमुक्त(dev, cl_data->report_descr[i]);
	पूर्ण
	devm_kमुक्त(dev, cl_data);
	वापस rc;
पूर्ण

पूर्णांक amd_sfh_hid_client_deinit(काष्ठा amd_mp2_dev *privdata)
अणु
	काष्ठा amdtp_cl_data *cl_data = privdata->cl_data;
	पूर्णांक i;

	क्रम (i = 0; i < cl_data->num_hid_devices; i++)
		amd_stop_sensor(privdata, i);

	cancel_delayed_work_sync(&cl_data->work);
	cancel_delayed_work_sync(&cl_data->work_buffer);
	amdtp_hid_हटाओ(cl_data);

	क्रम (i = 0; i < cl_data->num_hid_devices; i++) अणु
		अगर (cl_data->sensor_virt_addr[i]) अणु
			dma_मुक्त_coherent(&privdata->pdev->dev, 8 * माप(पूर्णांक),
					  cl_data->sensor_virt_addr[i],
					  cl_data->sensor_dma_addr[i]);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
