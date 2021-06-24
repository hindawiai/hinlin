<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AMD MP2 Sensors transport driver
 *
 * Authors: Nehal Bakulchandra Shah <Nehal-bakulchandra.shah@amd.com>
 *	    Sandeep Singh <sandeep.singh@amd.com>
 */

#अगर_अघोषित AMDSFH_HID_H
#घोषणा AMDSFH_HID_H

#घोषणा MAX_HID_DEVICES		4
#घोषणा BUS_AMD_AMDTP		0x20
#घोषणा AMD_SFH_HID_VENDOR	0x1022
#घोषणा AMD_SFH_HID_PRODUCT	0x0001

काष्ठा amdtp_cl_data अणु
	u8 init_करोne;
	u32 cur_hid_dev;
	u32 hid_dev_count;
	u32 num_hid_devices;
	काष्ठा device_info *hid_devices;
	u8  *report_descr[MAX_HID_DEVICES];
	पूर्णांक report_descr_sz[MAX_HID_DEVICES];
	काष्ठा hid_device *hid_sensor_hubs[MAX_HID_DEVICES];
	u8 *hid_descr[MAX_HID_DEVICES];
	पूर्णांक hid_descr_size[MAX_HID_DEVICES];
	phys_addr_t phys_addr_base;
	u32 *sensor_virt_addr[MAX_HID_DEVICES];
	dma_addr_t sensor_dma_addr[MAX_HID_DEVICES];
	u32 sensor_sts[MAX_HID_DEVICES];
	u32 sensor_requested_cnt[MAX_HID_DEVICES];
	u8 report_type[MAX_HID_DEVICES];
	u8 report_id[MAX_HID_DEVICES];
	u8 sensor_idx[MAX_HID_DEVICES];
	u8 *feature_report[MAX_HID_DEVICES];
	u8 *input_report[MAX_HID_DEVICES];
	u8 request_करोne[MAX_HID_DEVICES];
	काष्ठा delayed_work work;
	काष्ठा delayed_work work_buffer;
पूर्ण;

/**
 * काष्ठा amdtp_hid_data - Per instance HID data
 * @index:		Device index in the order of क्रमागतeration
 * @request_करोne:	Get Feature/Input report complete flag
 *			used during get/set request from hid core
 * @cli_data:		Link to the client instance
 * @hid_रुको:		Completion रुकोq
 *
 * Used to tie hid->driver data to driver client instance
 */
काष्ठा amdtp_hid_data अणु
	पूर्णांक index;
	काष्ठा amdtp_cl_data *cli_data;
	रुको_queue_head_t hid_रुको;
पूर्ण;

/* Interface functions between HID LL driver and AMD SFH client */
व्योम hid_amdtp_set_feature(काष्ठा hid_device *hid, अक्षर *buf, u32 len, पूर्णांक report_id);
व्योम hid_amdtp_get_report(काष्ठा hid_device *hid, पूर्णांक report_id, पूर्णांक report_type);
पूर्णांक amdtp_hid_probe(u32 cur_hid_dev, काष्ठा amdtp_cl_data *cli_data);
व्योम amdtp_hid_हटाओ(काष्ठा amdtp_cl_data *cli_data);
पूर्णांक amd_sfh_get_report(काष्ठा hid_device *hid, पूर्णांक report_id, पूर्णांक report_type);
व्योम amd_sfh_set_report(काष्ठा hid_device *hid, पूर्णांक report_id, पूर्णांक report_type);
व्योम amdtp_hid_wakeup(काष्ठा hid_device *hid);
#पूर्ण_अगर
