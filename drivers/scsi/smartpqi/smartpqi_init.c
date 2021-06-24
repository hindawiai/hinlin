<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    driver क्रम Microsemi PQI-based storage controllers
 *    Copyright (c) 2019-2020 Microchip Technology Inc. and its subsidiaries
 *    Copyright (c) 2016-2018 Microsemi Corporation
 *    Copyright (c) 2016 PMC-Sierra, Inc.
 *
 *    Questions/Comments/Bugfixes to storagedev@microchip.com
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/reboot.h>
#समावेश <linux/cciss_ioctl.h>
#समावेश <linux/blk-mq-pci.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "smartpqi.h"
#समावेश "smartpqi_sis.h"

#अगर !defined(BUILD_TIMESTAMP)
#घोषणा BUILD_TIMESTAMP
#पूर्ण_अगर

#घोषणा DRIVER_VERSION		"2.1.8-045"
#घोषणा DRIVER_MAJOR		2
#घोषणा DRIVER_MINOR		1
#घोषणा DRIVER_RELEASE		8
#घोषणा DRIVER_REVISION		45

#घोषणा DRIVER_NAME		"Microsemi PQI Driver (v" \
				DRIVER_VERSION BUILD_TIMESTAMP ")"
#घोषणा DRIVER_NAME_SHORT	"smartpqi"

#घोषणा PQI_EXTRA_SGL_MEMORY	(12 * माप(काष्ठा pqi_sg_descriptor))

#घोषणा PQI_POST_RESET_DELAY_SECS			5
#घोषणा PQI_POST_OFA_RESET_DELAY_UPON_TIMEOUT_SECS	10

MODULE_AUTHOR("Microsemi");
MODULE_DESCRIPTION("Driver for Microsemi Smart Family Controller version "
	DRIVER_VERSION);
MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL");

अटल व्योम pqi_take_ctrl_offline(काष्ठा pqi_ctrl_info *ctrl_info);
अटल व्योम pqi_ctrl_offline_worker(काष्ठा work_काष्ठा *work);
अटल पूर्णांक pqi_scan_scsi_devices(काष्ठा pqi_ctrl_info *ctrl_info);
अटल व्योम pqi_scan_start(काष्ठा Scsi_Host *shost);
अटल व्योम pqi_start_io(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_queue_group *queue_group, क्रमागत pqi_io_path path,
	काष्ठा pqi_io_request *io_request);
अटल पूर्णांक pqi_submit_raid_request_synchronous(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_iu_header *request, अचिन्हित पूर्णांक flags,
	काष्ठा pqi_raid_error_info *error_info);
अटल पूर्णांक pqi_aio_submit_io(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा scsi_cmnd *scmd, u32 aio_handle, u8 *cdb,
	अचिन्हित पूर्णांक cdb_length, काष्ठा pqi_queue_group *queue_group,
	काष्ठा pqi_encryption_info *encryption_info, bool raid_bypass);
अटल  पूर्णांक pqi_aio_submit_r1_ग_लिखो_io(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा scsi_cmnd *scmd, काष्ठा pqi_queue_group *queue_group,
	काष्ठा pqi_encryption_info *encryption_info, काष्ठा pqi_scsi_dev *device,
	काष्ठा pqi_scsi_dev_raid_map_data *rmd);
अटल पूर्णांक pqi_aio_submit_r56_ग_लिखो_io(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा scsi_cmnd *scmd, काष्ठा pqi_queue_group *queue_group,
	काष्ठा pqi_encryption_info *encryption_info, काष्ठा pqi_scsi_dev *device,
	काष्ठा pqi_scsi_dev_raid_map_data *rmd);
अटल व्योम pqi_ofa_ctrl_quiesce(काष्ठा pqi_ctrl_info *ctrl_info);
अटल व्योम pqi_ofa_ctrl_unquiesce(काष्ठा pqi_ctrl_info *ctrl_info);
अटल पूर्णांक pqi_ofa_ctrl_restart(काष्ठा pqi_ctrl_info *ctrl_info, अचिन्हित पूर्णांक delay_secs);
अटल व्योम pqi_ofa_setup_host_buffer(काष्ठा pqi_ctrl_info *ctrl_info);
अटल व्योम pqi_ofa_मुक्त_host_buffer(काष्ठा pqi_ctrl_info *ctrl_info);
अटल पूर्णांक pqi_ofa_host_memory_update(काष्ठा pqi_ctrl_info *ctrl_info);
अटल पूर्णांक pqi_device_रुको_क्रम_pending_io(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device, अचिन्हित दीर्घ समयout_msecs);

/* क्रम flags argument to pqi_submit_raid_request_synchronous() */
#घोषणा PQI_SYNC_FLAGS_INTERRUPTABLE	0x1

अटल काष्ठा scsi_transport_ढाँचा *pqi_sas_transport_ढाँचा;

अटल atomic_t pqi_controller_count = ATOMIC_INIT(0);

क्रमागत pqi_lockup_action अणु
	NONE,
	REBOOT,
	PANIC
पूर्ण;

अटल क्रमागत pqi_lockup_action pqi_lockup_action = NONE;

अटल काष्ठा अणु
	क्रमागत pqi_lockup_action	action;
	अक्षर			*name;
पूर्ण pqi_lockup_actions[] = अणु
	अणु
		.action = NONE,
		.name = "none",
	पूर्ण,
	अणु
		.action = REBOOT,
		.name = "reboot",
	पूर्ण,
	अणु
		.action = PANIC,
		.name = "panic",
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक pqi_supported_event_types[] = अणु
	PQI_EVENT_TYPE_HOTPLUG,
	PQI_EVENT_TYPE_HARDWARE,
	PQI_EVENT_TYPE_PHYSICAL_DEVICE,
	PQI_EVENT_TYPE_LOGICAL_DEVICE,
	PQI_EVENT_TYPE_OFA,
	PQI_EVENT_TYPE_AIO_STATE_CHANGE,
	PQI_EVENT_TYPE_AIO_CONFIG_CHANGE,
पूर्ण;

अटल पूर्णांक pqi_disable_device_id_wildcards;
module_param_named(disable_device_id_wildcards,
	pqi_disable_device_id_wildcards, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_device_id_wildcards,
	"Disable device ID wildcards.");

अटल पूर्णांक pqi_disable_heartbeat;
module_param_named(disable_heartbeat,
	pqi_disable_heartbeat, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_heartbeat,
	"Disable heartbeat.");

अटल पूर्णांक pqi_disable_ctrl_shutकरोwn;
module_param_named(disable_ctrl_shutकरोwn,
	pqi_disable_ctrl_shutकरोwn, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_ctrl_shutकरोwn,
	"Disable controller shutdown when controller locked up.");

अटल अक्षर *pqi_lockup_action_param;
module_param_named(lockup_action,
	pqi_lockup_action_param, अक्षरp, 0644);
MODULE_PARM_DESC(lockup_action, "Action to take when controller locked up.\n"
	"\t\tSupported: none, reboot, panic\n"
	"\t\tDefault: none");

अटल पूर्णांक pqi_expose_ld_first;
module_param_named(expose_ld_first,
	pqi_expose_ld_first, पूर्णांक, 0644);
MODULE_PARM_DESC(expose_ld_first, "Expose logical drives before physical drives.");

अटल पूर्णांक pqi_hide_vsep;
module_param_named(hide_vsep,
	pqi_hide_vsep, पूर्णांक, 0644);
MODULE_PARM_DESC(hide_vsep, "Hide the virtual SEP for direct attached drives.");

अटल अक्षर *raid_levels[] = अणु
	"RAID-0",
	"RAID-4",
	"RAID-1(1+0)",
	"RAID-5",
	"RAID-5+1",
	"RAID-6",
	"RAID-1(Triple)",
पूर्ण;

अटल अक्षर *pqi_raid_level_to_string(u8 raid_level)
अणु
	अगर (raid_level < ARRAY_SIZE(raid_levels))
		वापस raid_levels[raid_level];

	वापस "RAID UNKNOWN";
पूर्ण

#घोषणा SA_RAID_0		0
#घोषणा SA_RAID_4		1
#घोषणा SA_RAID_1		2	/* also used क्रम RAID 10 */
#घोषणा SA_RAID_5		3	/* also used क्रम RAID 50 */
#घोषणा SA_RAID_51		4
#घोषणा SA_RAID_6		5	/* also used क्रम RAID 60 */
#घोषणा SA_RAID_TRIPLE		6	/* also used क्रम RAID 1+0 Triple */
#घोषणा SA_RAID_MAX		SA_RAID_TRIPLE
#घोषणा SA_RAID_UNKNOWN		0xff

अटल अंतरभूत व्योम pqi_scsi_करोne(काष्ठा scsi_cmnd *scmd)
अणु
	pqi_prep_क्रम_scsi_करोne(scmd);
	scmd->scsi_करोne(scmd);
पूर्ण

अटल अंतरभूत व्योम pqi_disable_ग_लिखो_same(काष्ठा scsi_device *sdev)
अणु
	sdev->no_ग_लिखो_same = 1;
पूर्ण

अटल अंतरभूत bool pqi_scsi3addr_equal(u8 *scsi3addr1, u8 *scsi3addr2)
अणु
	वापस स_भेद(scsi3addr1, scsi3addr2, 8) == 0;
पूर्ण

अटल अंतरभूत bool pqi_is_logical_device(काष्ठा pqi_scsi_dev *device)
अणु
	वापस !device->is_physical_device;
पूर्ण

अटल अंतरभूत bool pqi_is_बाह्यal_raid_addr(u8 *scsi3addr)
अणु
	वापस scsi3addr[2] != 0;
पूर्ण

अटल अंतरभूत bool pqi_ctrl_offline(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस !ctrl_info->controller_online;
पूर्ण

अटल अंतरभूत व्योम pqi_check_ctrl_health(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अगर (ctrl_info->controller_online)
		अगर (!sis_is_firmware_running(ctrl_info))
			pqi_take_ctrl_offline(ctrl_info);
पूर्ण

अटल अंतरभूत bool pqi_is_hba_lunid(u8 *scsi3addr)
अणु
	वापस pqi_scsi3addr_equal(scsi3addr, RAID_CTLR_LUNID);
पूर्ण

अटल अंतरभूत क्रमागत pqi_ctrl_mode pqi_get_ctrl_mode(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस sis_पढ़ो_driver_scratch(ctrl_info);
पूर्ण

अटल अंतरभूत व्योम pqi_save_ctrl_mode(काष्ठा pqi_ctrl_info *ctrl_info,
	क्रमागत pqi_ctrl_mode mode)
अणु
	sis_ग_लिखो_driver_scratch(ctrl_info, mode);
पूर्ण

अटल अंतरभूत व्योम pqi_ctrl_block_scan(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	ctrl_info->scan_blocked = true;
	mutex_lock(&ctrl_info->scan_mutex);
पूर्ण

अटल अंतरभूत व्योम pqi_ctrl_unblock_scan(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	ctrl_info->scan_blocked = false;
	mutex_unlock(&ctrl_info->scan_mutex);
पूर्ण

अटल अंतरभूत bool pqi_ctrl_scan_blocked(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस ctrl_info->scan_blocked;
पूर्ण

अटल अंतरभूत व्योम pqi_ctrl_block_device_reset(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	mutex_lock(&ctrl_info->lun_reset_mutex);
पूर्ण

अटल अंतरभूत व्योम pqi_ctrl_unblock_device_reset(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	mutex_unlock(&ctrl_info->lun_reset_mutex);
पूर्ण

अटल अंतरभूत व्योम pqi_scsi_block_requests(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	काष्ठा Scsi_Host *shost;
	अचिन्हित पूर्णांक num_loops;
	पूर्णांक msecs_sleep;

	shost = ctrl_info->scsi_host;

	scsi_block_requests(shost);

	num_loops = 0;
	msecs_sleep = 20;
	जबतक (scsi_host_busy(shost)) अणु
		num_loops++;
		अगर (num_loops == 10)
			msecs_sleep = 500;
		msleep(msecs_sleep);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pqi_scsi_unblock_requests(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	scsi_unblock_requests(ctrl_info->scsi_host);
पूर्ण

अटल अंतरभूत व्योम pqi_ctrl_busy(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	atomic_inc(&ctrl_info->num_busy_thपढ़ोs);
पूर्ण

अटल अंतरभूत व्योम pqi_ctrl_unbusy(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	atomic_dec(&ctrl_info->num_busy_thपढ़ोs);
पूर्ण

अटल अंतरभूत bool pqi_ctrl_blocked(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस ctrl_info->block_requests;
पूर्ण

अटल अंतरभूत व्योम pqi_ctrl_block_requests(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	ctrl_info->block_requests = true;
पूर्ण

अटल अंतरभूत व्योम pqi_ctrl_unblock_requests(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	ctrl_info->block_requests = false;
	wake_up_all(&ctrl_info->block_requests_रुको);
पूर्ण

अटल व्योम pqi_रुको_अगर_ctrl_blocked(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अगर (!pqi_ctrl_blocked(ctrl_info))
		वापस;

	atomic_inc(&ctrl_info->num_blocked_thपढ़ोs);
	रुको_event(ctrl_info->block_requests_रुको,
		!pqi_ctrl_blocked(ctrl_info));
	atomic_dec(&ctrl_info->num_blocked_thपढ़ोs);
पूर्ण

#घोषणा PQI_QUIESCE_WARNING_TIMEOUT_SECS		10

अटल अंतरभूत व्योम pqi_ctrl_रुको_until_quiesced(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अचिन्हित दीर्घ start_jअगरfies;
	अचिन्हित दीर्घ warning_समयout;
	bool displayed_warning;

	displayed_warning = false;
	start_jअगरfies = jअगरfies;
	warning_समयout = (PQI_QUIESCE_WARNING_TIMEOUT_SECS * PQI_HZ) + start_jअगरfies;

	जबतक (atomic_पढ़ो(&ctrl_info->num_busy_thपढ़ोs) >
		atomic_पढ़ो(&ctrl_info->num_blocked_thपढ़ोs)) अणु
		अगर (समय_after(jअगरfies, warning_समयout)) अणु
			dev_warn(&ctrl_info->pci_dev->dev,
				"waiting %u seconds for driver activity to quiesce\n",
				jअगरfies_to_msecs(jअगरfies - start_jअगरfies) / 1000);
			displayed_warning = true;
			warning_समयout = (PQI_QUIESCE_WARNING_TIMEOUT_SECS * PQI_HZ) + jअगरfies;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण

	अगर (displayed_warning)
		dev_warn(&ctrl_info->pci_dev->dev,
			"driver activity quiesced after waiting for %u seconds\n",
			jअगरfies_to_msecs(jअगरfies - start_jअगरfies) / 1000);
पूर्ण

अटल अंतरभूत bool pqi_device_offline(काष्ठा pqi_scsi_dev *device)
अणु
	वापस device->device_offline;
पूर्ण

अटल अंतरभूत व्योम pqi_ctrl_ofa_start(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	mutex_lock(&ctrl_info->ofa_mutex);
पूर्ण

अटल अंतरभूत व्योम pqi_ctrl_ofa_करोne(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	mutex_unlock(&ctrl_info->ofa_mutex);
पूर्ण

अटल अंतरभूत व्योम pqi_रुको_until_ofa_finished(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	mutex_lock(&ctrl_info->ofa_mutex);
	mutex_unlock(&ctrl_info->ofa_mutex);
पूर्ण

अटल अंतरभूत bool pqi_ofa_in_progress(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस mutex_is_locked(&ctrl_info->ofa_mutex);
पूर्ण

अटल अंतरभूत व्योम pqi_device_हटाओ_start(काष्ठा pqi_scsi_dev *device)
अणु
	device->in_हटाओ = true;
पूर्ण

अटल अंतरभूत bool pqi_device_in_हटाओ(काष्ठा pqi_scsi_dev *device)
अणु
	वापस device->in_हटाओ;
पूर्ण

अटल अंतरभूत पूर्णांक pqi_event_type_to_event_index(अचिन्हित पूर्णांक event_type)
अणु
	पूर्णांक index;

	क्रम (index = 0; index < ARRAY_SIZE(pqi_supported_event_types); index++)
		अगर (event_type == pqi_supported_event_types[index])
			वापस index;

	वापस -1;
पूर्ण

अटल अंतरभूत bool pqi_is_supported_event(अचिन्हित पूर्णांक event_type)
अणु
	वापस pqi_event_type_to_event_index(event_type) != -1;
पूर्ण

अटल अंतरभूत व्योम pqi_schedule_rescan_worker_with_delay(काष्ठा pqi_ctrl_info *ctrl_info,
	अचिन्हित दीर्घ delay)
अणु
	अगर (pqi_ctrl_offline(ctrl_info))
		वापस;

	schedule_delayed_work(&ctrl_info->rescan_work, delay);
पूर्ण

अटल अंतरभूत व्योम pqi_schedule_rescan_worker(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	pqi_schedule_rescan_worker_with_delay(ctrl_info, 0);
पूर्ण

#घोषणा PQI_RESCAN_WORK_DELAY	(10 * PQI_HZ)

अटल अंतरभूत व्योम pqi_schedule_rescan_worker_delayed(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	pqi_schedule_rescan_worker_with_delay(ctrl_info, PQI_RESCAN_WORK_DELAY);
पूर्ण

अटल अंतरभूत व्योम pqi_cancel_rescan_worker(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	cancel_delayed_work_sync(&ctrl_info->rescan_work);
पूर्ण

अटल अंतरभूत u32 pqi_पढ़ो_heartbeat_counter(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अगर (!ctrl_info->heartbeat_counter)
		वापस 0;

	वापस पढ़ोl(ctrl_info->heartbeat_counter);
पूर्ण

अटल अंतरभूत u8 pqi_पढ़ो_soft_reset_status(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस पढ़ोb(ctrl_info->soft_reset_status);
पूर्ण

अटल अंतरभूत व्योम pqi_clear_soft_reset_status(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	u8 status;

	status = pqi_पढ़ो_soft_reset_status(ctrl_info);
	status &= ~PQI_SOFT_RESET_ABORT;
	ग_लिखोb(status, ctrl_info->soft_reset_status);
पूर्ण

अटल पूर्णांक pqi_map_single(काष्ठा pci_dev *pci_dev,
	काष्ठा pqi_sg_descriptor *sg_descriptor, व्योम *buffer,
	माप_प्रकार buffer_length, क्रमागत dma_data_direction data_direction)
अणु
	dma_addr_t bus_address;

	अगर (!buffer || buffer_length == 0 || data_direction == DMA_NONE)
		वापस 0;

	bus_address = dma_map_single(&pci_dev->dev, buffer, buffer_length,
		data_direction);
	अगर (dma_mapping_error(&pci_dev->dev, bus_address))
		वापस -ENOMEM;

	put_unaligned_le64((u64)bus_address, &sg_descriptor->address);
	put_unaligned_le32(buffer_length, &sg_descriptor->length);
	put_unaligned_le32(CISS_SG_LAST, &sg_descriptor->flags);

	वापस 0;
पूर्ण

अटल व्योम pqi_pci_unmap(काष्ठा pci_dev *pci_dev,
	काष्ठा pqi_sg_descriptor *descriptors, पूर्णांक num_descriptors,
	क्रमागत dma_data_direction data_direction)
अणु
	पूर्णांक i;

	अगर (data_direction == DMA_NONE)
		वापस;

	क्रम (i = 0; i < num_descriptors; i++)
		dma_unmap_single(&pci_dev->dev,
			(dma_addr_t)get_unaligned_le64(&descriptors[i].address),
			get_unaligned_le32(&descriptors[i].length),
			data_direction);
पूर्ण

अटल पूर्णांक pqi_build_raid_path_request(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_raid_path_request *request, u8 cmd,
	u8 *scsi3addr, व्योम *buffer, माप_प्रकार buffer_length,
	u16 vpd_page, क्रमागत dma_data_direction *dir)
अणु
	u8 *cdb;
	माप_प्रकार cdb_length = buffer_length;

	स_रखो(request, 0, माप(*request));

	request->header.iu_type = PQI_REQUEST_IU_RAID_PATH_IO;
	put_unaligned_le16(दुरत्व(काष्ठा pqi_raid_path_request,
		sg_descriptors[1]) - PQI_REQUEST_HEADER_LENGTH,
		&request->header.iu_length);
	put_unaligned_le32(buffer_length, &request->buffer_length);
	स_नकल(request->lun_number, scsi3addr, माप(request->lun_number));
	request->task_attribute = SOP_TASK_ATTRIBUTE_SIMPLE;
	request->additional_cdb_bytes_usage = SOP_ADDITIONAL_CDB_BYTES_0;

	cdb = request->cdb;

	चयन (cmd) अणु
	हाल INQUIRY:
		request->data_direction = SOP_READ_FLAG;
		cdb[0] = INQUIRY;
		अगर (vpd_page & VPD_PAGE) अणु
			cdb[1] = 0x1;
			cdb[2] = (u8)vpd_page;
		पूर्ण
		cdb[4] = (u8)cdb_length;
		अवरोध;
	हाल CISS_REPORT_LOG:
	हाल CISS_REPORT_PHYS:
		request->data_direction = SOP_READ_FLAG;
		cdb[0] = cmd;
		अगर (cmd == CISS_REPORT_PHYS)
			cdb[1] = CISS_REPORT_PHYS_FLAG_OTHER;
		अन्यथा
			cdb[1] = ctrl_info->ciss_report_log_flags;
		put_unaligned_be32(cdb_length, &cdb[6]);
		अवरोध;
	हाल CISS_GET_RAID_MAP:
		request->data_direction = SOP_READ_FLAG;
		cdb[0] = CISS_READ;
		cdb[1] = CISS_GET_RAID_MAP;
		put_unaligned_be32(cdb_length, &cdb[6]);
		अवरोध;
	हाल SA_FLUSH_CACHE:
		request->header.driver_flags = PQI_DRIVER_NONBLOCKABLE_REQUEST;
		request->data_direction = SOP_WRITE_FLAG;
		cdb[0] = BMIC_WRITE;
		cdb[6] = BMIC_FLUSH_CACHE;
		put_unaligned_be16(cdb_length, &cdb[7]);
		अवरोध;
	हाल BMIC_SENSE_DIAG_OPTIONS:
		cdb_length = 0;
		fallthrough;
	हाल BMIC_IDENTIFY_CONTROLLER:
	हाल BMIC_IDENTIFY_PHYSICAL_DEVICE:
	हाल BMIC_SENSE_SUBSYSTEM_INFORMATION:
	हाल BMIC_SENSE_FEATURE:
		request->data_direction = SOP_READ_FLAG;
		cdb[0] = BMIC_READ;
		cdb[6] = cmd;
		put_unaligned_be16(cdb_length, &cdb[7]);
		अवरोध;
	हाल BMIC_SET_DIAG_OPTIONS:
		cdb_length = 0;
		fallthrough;
	हाल BMIC_WRITE_HOST_WELLNESS:
		request->data_direction = SOP_WRITE_FLAG;
		cdb[0] = BMIC_WRITE;
		cdb[6] = cmd;
		put_unaligned_be16(cdb_length, &cdb[7]);
		अवरोध;
	हाल BMIC_CSMI_PASSTHRU:
		request->data_direction = SOP_BIसूचीECTIONAL;
		cdb[0] = BMIC_WRITE;
		cdb[5] = CSMI_CC_SAS_SMP_PASSTHRU;
		cdb[6] = cmd;
		put_unaligned_be16(cdb_length, &cdb[7]);
		अवरोध;
	शेष:
		dev_err(&ctrl_info->pci_dev->dev, "unknown command 0x%c\n", cmd);
		अवरोध;
	पूर्ण

	चयन (request->data_direction) अणु
	हाल SOP_READ_FLAG:
		*dir = DMA_FROM_DEVICE;
		अवरोध;
	हाल SOP_WRITE_FLAG:
		*dir = DMA_TO_DEVICE;
		अवरोध;
	हाल SOP_NO_सूचीECTION_FLAG:
		*dir = DMA_NONE;
		अवरोध;
	शेष:
		*dir = DMA_BIसूचीECTIONAL;
		अवरोध;
	पूर्ण

	वापस pqi_map_single(ctrl_info->pci_dev, &request->sg_descriptors[0],
		buffer, buffer_length, *dir);
पूर्ण

अटल अंतरभूत व्योम pqi_reinit_io_request(काष्ठा pqi_io_request *io_request)
अणु
	io_request->scmd = शून्य;
	io_request->status = 0;
	io_request->error_info = शून्य;
	io_request->raid_bypass = false;
पूर्ण

अटल काष्ठा pqi_io_request *pqi_alloc_io_request(
	काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	काष्ठा pqi_io_request *io_request;
	u16 i = ctrl_info->next_io_request_slot;	/* benignly racy */

	जबतक (1) अणु
		io_request = &ctrl_info->io_request_pool[i];
		अगर (atomic_inc_वापस(&io_request->refcount) == 1)
			अवरोध;
		atomic_dec(&io_request->refcount);
		i = (i + 1) % ctrl_info->max_io_slots;
	पूर्ण

	/* benignly racy */
	ctrl_info->next_io_request_slot = (i + 1) % ctrl_info->max_io_slots;

	pqi_reinit_io_request(io_request);

	वापस io_request;
पूर्ण

अटल व्योम pqi_मुक्त_io_request(काष्ठा pqi_io_request *io_request)
अणु
	atomic_dec(&io_request->refcount);
पूर्ण

अटल पूर्णांक pqi_send_scsi_raid_request(काष्ठा pqi_ctrl_info *ctrl_info, u8 cmd,
	u8 *scsi3addr, व्योम *buffer, माप_प्रकार buffer_length, u16 vpd_page,
	काष्ठा pqi_raid_error_info *error_info)
अणु
	पूर्णांक rc;
	काष्ठा pqi_raid_path_request request;
	क्रमागत dma_data_direction dir;

	rc = pqi_build_raid_path_request(ctrl_info, &request, cmd, scsi3addr,
		buffer, buffer_length, vpd_page, &dir);
	अगर (rc)
		वापस rc;

	rc = pqi_submit_raid_request_synchronous(ctrl_info, &request.header, 0, error_info);

	pqi_pci_unmap(ctrl_info->pci_dev, request.sg_descriptors, 1, dir);

	वापस rc;
पूर्ण

/* helper functions क्रम pqi_send_scsi_raid_request */

अटल अंतरभूत पूर्णांक pqi_send_ctrl_raid_request(काष्ठा pqi_ctrl_info *ctrl_info,
	u8 cmd, व्योम *buffer, माप_प्रकार buffer_length)
अणु
	वापस pqi_send_scsi_raid_request(ctrl_info, cmd, RAID_CTLR_LUNID,
		buffer, buffer_length, 0, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक pqi_send_ctrl_raid_with_error(काष्ठा pqi_ctrl_info *ctrl_info,
	u8 cmd, व्योम *buffer, माप_प्रकार buffer_length,
	काष्ठा pqi_raid_error_info *error_info)
अणु
	वापस pqi_send_scsi_raid_request(ctrl_info, cmd, RAID_CTLR_LUNID,
		buffer, buffer_length, 0, error_info);
पूर्ण

अटल अंतरभूत पूर्णांक pqi_identअगरy_controller(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा bmic_identअगरy_controller *buffer)
अणु
	वापस pqi_send_ctrl_raid_request(ctrl_info, BMIC_IDENTIFY_CONTROLLER,
		buffer, माप(*buffer));
पूर्ण

अटल अंतरभूत पूर्णांक pqi_sense_subप्रणाली_info(काष्ठा  pqi_ctrl_info *ctrl_info,
	काष्ठा bmic_sense_subप्रणाली_info *sense_info)
अणु
	वापस pqi_send_ctrl_raid_request(ctrl_info,
		BMIC_SENSE_SUBSYSTEM_INFORMATION, sense_info,
		माप(*sense_info));
पूर्ण

अटल अंतरभूत पूर्णांक pqi_scsi_inquiry(काष्ठा pqi_ctrl_info *ctrl_info,
	u8 *scsi3addr, u16 vpd_page, व्योम *buffer, माप_प्रकार buffer_length)
अणु
	वापस pqi_send_scsi_raid_request(ctrl_info, INQUIRY, scsi3addr,
		buffer, buffer_length, vpd_page, शून्य);
पूर्ण

अटल पूर्णांक pqi_identअगरy_physical_device(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device,
	काष्ठा bmic_identअगरy_physical_device *buffer, माप_प्रकार buffer_length)
अणु
	पूर्णांक rc;
	क्रमागत dma_data_direction dir;
	u16 bmic_device_index;
	काष्ठा pqi_raid_path_request request;

	rc = pqi_build_raid_path_request(ctrl_info, &request,
		BMIC_IDENTIFY_PHYSICAL_DEVICE, RAID_CTLR_LUNID, buffer,
		buffer_length, 0, &dir);
	अगर (rc)
		वापस rc;

	bmic_device_index = CISS_GET_DRIVE_NUMBER(device->scsi3addr);
	request.cdb[2] = (u8)bmic_device_index;
	request.cdb[9] = (u8)(bmic_device_index >> 8);

	rc = pqi_submit_raid_request_synchronous(ctrl_info, &request.header, 0, शून्य);

	pqi_pci_unmap(ctrl_info->pci_dev, request.sg_descriptors, 1, dir);

	वापस rc;
पूर्ण

अटल अंतरभूत u32 pqi_aio_limit_to_bytes(__le16 *limit)
अणु
	u32 bytes;

	bytes = get_unaligned_le16(limit);
	अगर (bytes == 0)
		bytes = ~0;
	अन्यथा
		bytes *= 1024;

	वापस bytes;
पूर्ण

#आशय pack(1)

काष्ठा bmic_sense_feature_buffer अणु
	काष्ठा bmic_sense_feature_buffer_header header;
	काष्ठा bmic_sense_feature_io_page_aio_subpage aio_subpage;
पूर्ण;

#आशय pack()

#घोषणा MINIMUM_AIO_SUBPAGE_BUFFER_LENGTH	\
	दुरत्वend(काष्ठा bmic_sense_feature_buffer, \
		aio_subpage.max_ग_लिखो_raid_1_10_3drive)

#घोषणा MINIMUM_AIO_SUBPAGE_LENGTH	\
	(दुरत्वend(काष्ठा bmic_sense_feature_io_page_aio_subpage, \
		max_ग_लिखो_raid_1_10_3drive) - \
		माप_field(काष्ठा bmic_sense_feature_io_page_aio_subpage, header))

अटल पूर्णांक pqi_get_advanced_raid_bypass_config(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	क्रमागत dma_data_direction dir;
	काष्ठा pqi_raid_path_request request;
	काष्ठा bmic_sense_feature_buffer *buffer;

	buffer = kदो_स्मृति(माप(*buffer), GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	rc = pqi_build_raid_path_request(ctrl_info, &request, BMIC_SENSE_FEATURE, RAID_CTLR_LUNID,
		buffer, माप(*buffer), 0, &dir);
	अगर (rc)
		जाओ error;

	request.cdb[2] = BMIC_SENSE_FEATURE_IO_PAGE;
	request.cdb[3] = BMIC_SENSE_FEATURE_IO_PAGE_AIO_SUBPAGE;

	rc = pqi_submit_raid_request_synchronous(ctrl_info, &request.header, 0, शून्य);

	pqi_pci_unmap(ctrl_info->pci_dev, request.sg_descriptors, 1, dir);

	अगर (rc)
		जाओ error;

	अगर (buffer->header.page_code != BMIC_SENSE_FEATURE_IO_PAGE ||
		buffer->header.subpage_code !=
			BMIC_SENSE_FEATURE_IO_PAGE_AIO_SUBPAGE ||
		get_unaligned_le16(&buffer->header.buffer_length) <
			MINIMUM_AIO_SUBPAGE_BUFFER_LENGTH ||
		buffer->aio_subpage.header.page_code !=
			BMIC_SENSE_FEATURE_IO_PAGE ||
		buffer->aio_subpage.header.subpage_code !=
			BMIC_SENSE_FEATURE_IO_PAGE_AIO_SUBPAGE ||
		get_unaligned_le16(&buffer->aio_subpage.header.page_length) <
			MINIMUM_AIO_SUBPAGE_LENGTH) अणु
		जाओ error;
	पूर्ण

	ctrl_info->max_transfer_encrypted_sas_sata =
		pqi_aio_limit_to_bytes(
			&buffer->aio_subpage.max_transfer_encrypted_sas_sata);

	ctrl_info->max_transfer_encrypted_nvme =
		pqi_aio_limit_to_bytes(
			&buffer->aio_subpage.max_transfer_encrypted_nvme);

	ctrl_info->max_ग_लिखो_raid_5_6 =
		pqi_aio_limit_to_bytes(
			&buffer->aio_subpage.max_ग_लिखो_raid_5_6);

	ctrl_info->max_ग_लिखो_raid_1_10_2drive =
		pqi_aio_limit_to_bytes(
			&buffer->aio_subpage.max_ग_लिखो_raid_1_10_2drive);

	ctrl_info->max_ग_लिखो_raid_1_10_3drive =
		pqi_aio_limit_to_bytes(
			&buffer->aio_subpage.max_ग_लिखो_raid_1_10_3drive);

error:
	kमुक्त(buffer);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_flush_cache(काष्ठा pqi_ctrl_info *ctrl_info,
	क्रमागत bmic_flush_cache_shutकरोwn_event shutकरोwn_event)
अणु
	पूर्णांक rc;
	काष्ठा bmic_flush_cache *flush_cache;

	flush_cache = kzalloc(माप(*flush_cache), GFP_KERNEL);
	अगर (!flush_cache)
		वापस -ENOMEM;

	flush_cache->shutकरोwn_event = shutकरोwn_event;

	rc = pqi_send_ctrl_raid_request(ctrl_info, SA_FLUSH_CACHE, flush_cache,
		माप(*flush_cache));

	kमुक्त(flush_cache);

	वापस rc;
पूर्ण

पूर्णांक pqi_csmi_smp_passthru(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा bmic_csmi_smp_passthru_buffer *buffer, माप_प्रकार buffer_length,
	काष्ठा pqi_raid_error_info *error_info)
अणु
	वापस pqi_send_ctrl_raid_with_error(ctrl_info, BMIC_CSMI_PASSTHRU,
		buffer, buffer_length, error_info);
पूर्ण

#घोषणा PQI_FETCH_PTRAID_DATA		(1 << 31)

अटल पूर्णांक pqi_set_diag_rescan(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	काष्ठा bmic_diag_options *diag;

	diag = kzalloc(माप(*diag), GFP_KERNEL);
	अगर (!diag)
		वापस -ENOMEM;

	rc = pqi_send_ctrl_raid_request(ctrl_info, BMIC_SENSE_DIAG_OPTIONS,
		diag, माप(*diag));
	अगर (rc)
		जाओ out;

	diag->options |= cpu_to_le32(PQI_FETCH_PTRAID_DATA);

	rc = pqi_send_ctrl_raid_request(ctrl_info, BMIC_SET_DIAG_OPTIONS, diag,
		माप(*diag));

out:
	kमुक्त(diag);

	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक pqi_ग_लिखो_host_wellness(काष्ठा pqi_ctrl_info *ctrl_info,
	व्योम *buffer, माप_प्रकार buffer_length)
अणु
	वापस pqi_send_ctrl_raid_request(ctrl_info, BMIC_WRITE_HOST_WELLNESS,
		buffer, buffer_length);
पूर्ण

#आशय pack(1)

काष्ठा bmic_host_wellness_driver_version अणु
	u8	start_tag[4];
	u8	driver_version_tag[2];
	__le16	driver_version_length;
	अक्षर	driver_version[32];
	u8	करोnt_ग_लिखो_tag[2];
	u8	end_tag[2];
पूर्ण;

#आशय pack()

अटल पूर्णांक pqi_ग_लिखो_driver_version_to_host_wellness(
	काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	काष्ठा bmic_host_wellness_driver_version *buffer;
	माप_प्रकार buffer_length;

	buffer_length = माप(*buffer);

	buffer = kदो_स्मृति(buffer_length, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	buffer->start_tag[0] = '<';
	buffer->start_tag[1] = 'H';
	buffer->start_tag[2] = 'W';
	buffer->start_tag[3] = '>';
	buffer->driver_version_tag[0] = 'D';
	buffer->driver_version_tag[1] = 'V';
	put_unaligned_le16(माप(buffer->driver_version),
		&buffer->driver_version_length);
	म_नकलन(buffer->driver_version, "Linux " DRIVER_VERSION,
		माप(buffer->driver_version) - 1);
	buffer->driver_version[माप(buffer->driver_version) - 1] = '\0';
	buffer->करोnt_ग_लिखो_tag[0] = 'D';
	buffer->करोnt_ग_लिखो_tag[1] = 'W';
	buffer->end_tag[0] = 'Z';
	buffer->end_tag[1] = 'Z';

	rc = pqi_ग_लिखो_host_wellness(ctrl_info, buffer, buffer_length);

	kमुक्त(buffer);

	वापस rc;
पूर्ण

#आशय pack(1)

काष्ठा bmic_host_wellness_समय अणु
	u8	start_tag[4];
	u8	समय_प्रकारag[2];
	__le16	समय_length;
	u8	समय[8];
	u8	करोnt_ग_लिखो_tag[2];
	u8	end_tag[2];
पूर्ण;

#आशय pack()

अटल पूर्णांक pqi_ग_लिखो_current_समय_प्रकारo_host_wellness(
	काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	काष्ठा bmic_host_wellness_समय *buffer;
	माप_प्रकार buffer_length;
	समय64_t local_समय;
	अचिन्हित पूर्णांक year;
	काष्ठा पंचांग पंचांग;

	buffer_length = माप(*buffer);

	buffer = kदो_स्मृति(buffer_length, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	buffer->start_tag[0] = '<';
	buffer->start_tag[1] = 'H';
	buffer->start_tag[2] = 'W';
	buffer->start_tag[3] = '>';
	buffer->समय_प्रकारag[0] = 'T';
	buffer->समय_प्रकारag[1] = 'D';
	put_unaligned_le16(माप(buffer->समय),
		&buffer->समय_length);

	local_समय = kसमय_get_real_seconds();
	समय64_to_पंचांग(local_समय, -sys_tz.tz_minuteswest * 60, &पंचांग);
	year = पंचांग.पंचांग_year + 1900;

	buffer->समय[0] = bin2bcd(पंचांग.पंचांग_hour);
	buffer->समय[1] = bin2bcd(पंचांग.पंचांग_min);
	buffer->समय[2] = bin2bcd(पंचांग.पंचांग_sec);
	buffer->समय[3] = 0;
	buffer->समय[4] = bin2bcd(पंचांग.पंचांग_mon + 1);
	buffer->समय[5] = bin2bcd(पंचांग.पंचांग_mday);
	buffer->समय[6] = bin2bcd(year / 100);
	buffer->समय[7] = bin2bcd(year % 100);

	buffer->करोnt_ग_लिखो_tag[0] = 'D';
	buffer->करोnt_ग_लिखो_tag[1] = 'W';
	buffer->end_tag[0] = 'Z';
	buffer->end_tag[1] = 'Z';

	rc = pqi_ग_लिखो_host_wellness(ctrl_info, buffer, buffer_length);

	kमुक्त(buffer);

	वापस rc;
पूर्ण

#घोषणा PQI_UPDATE_TIME_WORK_INTERVAL	(24UL * 60 * 60 * PQI_HZ)

अटल व्योम pqi_update_समय_worker(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक rc;
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = container_of(to_delayed_work(work), काष्ठा pqi_ctrl_info,
		update_समय_work);

	rc = pqi_ग_लिखो_current_समय_प्रकारo_host_wellness(ctrl_info);
	अगर (rc)
		dev_warn(&ctrl_info->pci_dev->dev,
			"error updating time on controller\n");

	schedule_delayed_work(&ctrl_info->update_समय_work,
		PQI_UPDATE_TIME_WORK_INTERVAL);
पूर्ण

अटल अंतरभूत व्योम pqi_schedule_update_समय_worker(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	schedule_delayed_work(&ctrl_info->update_समय_work, 0);
पूर्ण

अटल अंतरभूत व्योम pqi_cancel_update_समय_worker(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	cancel_delayed_work_sync(&ctrl_info->update_समय_work);
पूर्ण

अटल अंतरभूत पूर्णांक pqi_report_luns(काष्ठा pqi_ctrl_info *ctrl_info, u8 cmd, व्योम *buffer,
	माप_प्रकार buffer_length)
अणु
	वापस pqi_send_ctrl_raid_request(ctrl_info, cmd, buffer, buffer_length);
पूर्ण

अटल पूर्णांक pqi_report_phys_logical_luns(काष्ठा pqi_ctrl_info *ctrl_info, u8 cmd, व्योम **buffer)
अणु
	पूर्णांक rc;
	माप_प्रकार lun_list_length;
	माप_प्रकार lun_data_length;
	माप_प्रकार new_lun_list_length;
	व्योम *lun_data = शून्य;
	काष्ठा report_lun_header *report_lun_header;

	report_lun_header = kदो_स्मृति(माप(*report_lun_header), GFP_KERNEL);
	अगर (!report_lun_header) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	rc = pqi_report_luns(ctrl_info, cmd, report_lun_header, माप(*report_lun_header));
	अगर (rc)
		जाओ out;

	lun_list_length = get_unaligned_be32(&report_lun_header->list_length);

again:
	lun_data_length = माप(काष्ठा report_lun_header) + lun_list_length;

	lun_data = kदो_स्मृति(lun_data_length, GFP_KERNEL);
	अगर (!lun_data) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (lun_list_length == 0) अणु
		स_नकल(lun_data, report_lun_header, माप(*report_lun_header));
		जाओ out;
	पूर्ण

	rc = pqi_report_luns(ctrl_info, cmd, lun_data, lun_data_length);
	अगर (rc)
		जाओ out;

	new_lun_list_length =
		get_unaligned_be32(&((काष्ठा report_lun_header *)lun_data)->list_length);

	अगर (new_lun_list_length > lun_list_length) अणु
		lun_list_length = new_lun_list_length;
		kमुक्त(lun_data);
		जाओ again;
	पूर्ण

out:
	kमुक्त(report_lun_header);

	अगर (rc) अणु
		kमुक्त(lun_data);
		lun_data = शून्य;
	पूर्ण

	*buffer = lun_data;

	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक pqi_report_phys_luns(काष्ठा pqi_ctrl_info *ctrl_info, व्योम **buffer)
अणु
	वापस pqi_report_phys_logical_luns(ctrl_info, CISS_REPORT_PHYS, buffer);
पूर्ण

अटल अंतरभूत पूर्णांक pqi_report_logical_luns(काष्ठा pqi_ctrl_info *ctrl_info, व्योम **buffer)
अणु
	वापस pqi_report_phys_logical_luns(ctrl_info, CISS_REPORT_LOG, buffer);
पूर्ण

अटल पूर्णांक pqi_get_device_lists(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा report_phys_lun_extended **physdev_list,
	काष्ठा report_log_lun_extended **logdev_list)
अणु
	पूर्णांक rc;
	माप_प्रकार logdev_list_length;
	माप_प्रकार logdev_data_length;
	काष्ठा report_log_lun_extended *पूर्णांकernal_logdev_list;
	काष्ठा report_log_lun_extended *logdev_data;
	काष्ठा report_lun_header report_lun_header;

	rc = pqi_report_phys_luns(ctrl_info, (व्योम **)physdev_list);
	अगर (rc)
		dev_err(&ctrl_info->pci_dev->dev,
			"report physical LUNs failed\n");

	rc = pqi_report_logical_luns(ctrl_info, (व्योम **)logdev_list);
	अगर (rc)
		dev_err(&ctrl_info->pci_dev->dev,
			"report logical LUNs failed\n");

	/*
	 * Tack the controller itself onto the end of the logical device list.
	 */

	logdev_data = *logdev_list;

	अगर (logdev_data) अणु
		logdev_list_length =
			get_unaligned_be32(&logdev_data->header.list_length);
	पूर्ण अन्यथा अणु
		स_रखो(&report_lun_header, 0, माप(report_lun_header));
		logdev_data =
			(काष्ठा report_log_lun_extended *)&report_lun_header;
		logdev_list_length = 0;
	पूर्ण

	logdev_data_length = माप(काष्ठा report_lun_header) +
		logdev_list_length;

	पूर्णांकernal_logdev_list = kदो_स्मृति(logdev_data_length +
		माप(काष्ठा report_log_lun_extended), GFP_KERNEL);
	अगर (!पूर्णांकernal_logdev_list) अणु
		kमुक्त(*logdev_list);
		*logdev_list = शून्य;
		वापस -ENOMEM;
	पूर्ण

	स_नकल(पूर्णांकernal_logdev_list, logdev_data, logdev_data_length);
	स_रखो((u8 *)पूर्णांकernal_logdev_list + logdev_data_length, 0,
		माप(काष्ठा report_log_lun_extended_entry));
	put_unaligned_be32(logdev_list_length +
		माप(काष्ठा report_log_lun_extended_entry),
		&पूर्णांकernal_logdev_list->header.list_length);

	kमुक्त(*logdev_list);
	*logdev_list = पूर्णांकernal_logdev_list;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pqi_set_bus_target_lun(काष्ठा pqi_scsi_dev *device,
	पूर्णांक bus, पूर्णांक target, पूर्णांक lun)
अणु
	device->bus = bus;
	device->target = target;
	device->lun = lun;
पूर्ण

अटल व्योम pqi_assign_bus_target_lun(काष्ठा pqi_scsi_dev *device)
अणु
	u8 *scsi3addr;
	u32 lunid;
	पूर्णांक bus;
	पूर्णांक target;
	पूर्णांक lun;

	scsi3addr = device->scsi3addr;
	lunid = get_unaligned_le32(scsi3addr);

	अगर (pqi_is_hba_lunid(scsi3addr)) अणु
		/* The specअगरied device is the controller. */
		pqi_set_bus_target_lun(device, PQI_HBA_BUS, 0, lunid & 0x3fff);
		device->target_lun_valid = true;
		वापस;
	पूर्ण

	अगर (pqi_is_logical_device(device)) अणु
		अगर (device->is_बाह्यal_raid_device) अणु
			bus = PQI_EXTERNAL_RAID_VOLUME_BUS;
			target = (lunid >> 16) & 0x3fff;
			lun = lunid & 0xff;
		पूर्ण अन्यथा अणु
			bus = PQI_RAID_VOLUME_BUS;
			target = 0;
			lun = lunid & 0x3fff;
		पूर्ण
		pqi_set_bus_target_lun(device, bus, target, lun);
		device->target_lun_valid = true;
		वापस;
	पूर्ण

	/*
	 * Defer target and LUN assignment क्रम non-controller physical devices
	 * because the SAS transport layer will make these assignments later.
	 */
	pqi_set_bus_target_lun(device, PQI_PHYSICAL_DEVICE_BUS, 0, 0);
पूर्ण

अटल व्योम pqi_get_raid_level(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक rc;
	u8 raid_level;
	u8 *buffer;

	raid_level = SA_RAID_UNKNOWN;

	buffer = kदो_स्मृति(64, GFP_KERNEL);
	अगर (buffer) अणु
		rc = pqi_scsi_inquiry(ctrl_info, device->scsi3addr,
			VPD_PAGE | CISS_VPD_LV_DEVICE_GEOMETRY, buffer, 64);
		अगर (rc == 0) अणु
			raid_level = buffer[8];
			अगर (raid_level > SA_RAID_MAX)
				raid_level = SA_RAID_UNKNOWN;
		पूर्ण
		kमुक्त(buffer);
	पूर्ण

	device->raid_level = raid_level;
पूर्ण

अटल पूर्णांक pqi_validate_raid_map(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device, काष्ठा raid_map *raid_map)
अणु
	अक्षर *err_msg;
	u32 raid_map_size;
	u32 r5or6_blocks_per_row;

	raid_map_size = get_unaligned_le32(&raid_map->काष्ठाure_size);

	अगर (raid_map_size < दुरत्व(काष्ठा raid_map, disk_data)) अणु
		err_msg = "RAID map too small";
		जाओ bad_raid_map;
	पूर्ण

	अगर (device->raid_level == SA_RAID_1) अणु
		अगर (get_unaligned_le16(&raid_map->layout_map_count) != 2) अणु
			err_msg = "invalid RAID-1 map";
			जाओ bad_raid_map;
		पूर्ण
	पूर्ण अन्यथा अगर (device->raid_level == SA_RAID_TRIPLE) अणु
		अगर (get_unaligned_le16(&raid_map->layout_map_count) != 3) अणु
			err_msg = "invalid RAID-1(Triple) map";
			जाओ bad_raid_map;
		पूर्ण
	पूर्ण अन्यथा अगर ((device->raid_level == SA_RAID_5 ||
		device->raid_level == SA_RAID_6) &&
		get_unaligned_le16(&raid_map->layout_map_count) > 1) अणु
		/* RAID 50/60 */
		r5or6_blocks_per_row =
			get_unaligned_le16(&raid_map->strip_size) *
			get_unaligned_le16(&raid_map->data_disks_per_row);
		अगर (r5or6_blocks_per_row == 0) अणु
			err_msg = "invalid RAID-5 or RAID-6 map";
			जाओ bad_raid_map;
		पूर्ण
	पूर्ण

	वापस 0;

bad_raid_map:
	dev_warn(&ctrl_info->pci_dev->dev,
		"logical device %08x%08x %s\n",
		*((u32 *)&device->scsi3addr),
		*((u32 *)&device->scsi3addr[4]), err_msg);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pqi_get_raid_map(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक rc;
	u32 raid_map_size;
	काष्ठा raid_map *raid_map;

	raid_map = kदो_स्मृति(माप(*raid_map), GFP_KERNEL);
	अगर (!raid_map)
		वापस -ENOMEM;

	rc = pqi_send_scsi_raid_request(ctrl_info, CISS_GET_RAID_MAP,
		device->scsi3addr, raid_map, माप(*raid_map), 0, शून्य);
	अगर (rc)
		जाओ error;

	raid_map_size = get_unaligned_le32(&raid_map->काष्ठाure_size);

	अगर (raid_map_size > माप(*raid_map)) अणु

		kमुक्त(raid_map);

		raid_map = kदो_स्मृति(raid_map_size, GFP_KERNEL);
		अगर (!raid_map)
			वापस -ENOMEM;

		rc = pqi_send_scsi_raid_request(ctrl_info, CISS_GET_RAID_MAP,
			device->scsi3addr, raid_map, raid_map_size, 0, शून्य);
		अगर (rc)
			जाओ error;

		अगर (get_unaligned_le32(&raid_map->काष्ठाure_size)
			!= raid_map_size) अणु
			dev_warn(&ctrl_info->pci_dev->dev,
				"requested %u bytes, received %u bytes\n",
				raid_map_size,
				get_unaligned_le32(&raid_map->काष्ठाure_size));
			जाओ error;
		पूर्ण
	पूर्ण

	rc = pqi_validate_raid_map(ctrl_info, device, raid_map);
	अगर (rc)
		जाओ error;

	device->raid_map = raid_map;

	वापस 0;

error:
	kमुक्त(raid_map);

	वापस rc;
पूर्ण

अटल व्योम pqi_set_max_transfer_encrypted(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device)
अणु
	अगर (!ctrl_info->lv_drive_type_mix_valid) अणु
		device->max_transfer_encrypted = ~0;
		वापस;
	पूर्ण

	चयन (LV_GET_DRIVE_TYPE_MIX(device->scsi3addr)) अणु
	हाल LV_DRIVE_TYPE_MIX_SAS_HDD_ONLY:
	हाल LV_DRIVE_TYPE_MIX_SATA_HDD_ONLY:
	हाल LV_DRIVE_TYPE_MIX_SAS_OR_SATA_SSD_ONLY:
	हाल LV_DRIVE_TYPE_MIX_SAS_SSD_ONLY:
	हाल LV_DRIVE_TYPE_MIX_SATA_SSD_ONLY:
	हाल LV_DRIVE_TYPE_MIX_SAS_ONLY:
	हाल LV_DRIVE_TYPE_MIX_SATA_ONLY:
		device->max_transfer_encrypted =
			ctrl_info->max_transfer_encrypted_sas_sata;
		अवरोध;
	हाल LV_DRIVE_TYPE_MIX_NVME_ONLY:
		device->max_transfer_encrypted =
			ctrl_info->max_transfer_encrypted_nvme;
		अवरोध;
	हाल LV_DRIVE_TYPE_MIX_UNKNOWN:
	हाल LV_DRIVE_TYPE_MIX_NO_RESTRICTION:
	शेष:
		device->max_transfer_encrypted =
			min(ctrl_info->max_transfer_encrypted_sas_sata,
				ctrl_info->max_transfer_encrypted_nvme);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pqi_get_raid_bypass_status(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक rc;
	u8 *buffer;
	u8 bypass_status;

	buffer = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!buffer)
		वापस;

	rc = pqi_scsi_inquiry(ctrl_info, device->scsi3addr,
		VPD_PAGE | CISS_VPD_LV_BYPASS_STATUS, buffer, 64);
	अगर (rc)
		जाओ out;

#घोषणा RAID_BYPASS_STATUS		4
#घोषणा RAID_BYPASS_CONFIGURED		0x1
#घोषणा RAID_BYPASS_ENABLED		0x2

	bypass_status = buffer[RAID_BYPASS_STATUS];
	device->raid_bypass_configured =
		(bypass_status & RAID_BYPASS_CONFIGURED) != 0;
	अगर (device->raid_bypass_configured &&
		(bypass_status & RAID_BYPASS_ENABLED) &&
		pqi_get_raid_map(ctrl_info, device) == 0) अणु
		device->raid_bypass_enabled = true;
		अगर (get_unaligned_le16(&device->raid_map->flags) &
			RAID_MAP_ENCRYPTION_ENABLED)
			pqi_set_max_transfer_encrypted(ctrl_info, device);
	पूर्ण

out:
	kमुक्त(buffer);
पूर्ण

/*
 * Use venकरोr-specअगरic VPD to determine online/offline status of a volume.
 */

अटल व्योम pqi_get_volume_status(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक rc;
	माप_प्रकार page_length;
	u8 volume_status = CISS_LV_STATUS_UNAVAILABLE;
	bool volume_offline = true;
	u32 volume_flags;
	काष्ठा ciss_vpd_logical_volume_status *vpd;

	vpd = kदो_स्मृति(माप(*vpd), GFP_KERNEL);
	अगर (!vpd)
		जाओ no_buffer;

	rc = pqi_scsi_inquiry(ctrl_info, device->scsi3addr,
		VPD_PAGE | CISS_VPD_LV_STATUS, vpd, माप(*vpd));
	अगर (rc)
		जाओ out;

	अगर (vpd->page_code != CISS_VPD_LV_STATUS)
		जाओ out;

	page_length = दुरत्व(काष्ठा ciss_vpd_logical_volume_status,
		volume_status) + vpd->page_length;
	अगर (page_length < माप(*vpd))
		जाओ out;

	volume_status = vpd->volume_status;
	volume_flags = get_unaligned_be32(&vpd->flags);
	volume_offline = (volume_flags & CISS_LV_FLAGS_NO_HOST_IO) != 0;

out:
	kमुक्त(vpd);
no_buffer:
	device->volume_status = volume_status;
	device->volume_offline = volume_offline;
पूर्ण

#घोषणा PQI_DEVICE_PHY_MAP_SUPPORTED	0x10

अटल पूर्णांक pqi_get_physical_device_info(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device,
	काष्ठा bmic_identअगरy_physical_device *id_phys)
अणु
	पूर्णांक rc;

	स_रखो(id_phys, 0, माप(*id_phys));

	rc = pqi_identअगरy_physical_device(ctrl_info, device,
		id_phys, माप(*id_phys));
	अगर (rc) अणु
		device->queue_depth = PQI_PHYSICAL_DISK_DEFAULT_MAX_QUEUE_DEPTH;
		वापस rc;
	पूर्ण

	scsi_sanitize_inquiry_string(&id_phys->model[0], 8);
	scsi_sanitize_inquiry_string(&id_phys->model[8], 16);

	स_नकल(device->venकरोr, &id_phys->model[0], माप(device->venकरोr));
	स_नकल(device->model, &id_phys->model[8], माप(device->model));

	device->box_index = id_phys->box_index;
	device->phys_box_on_bus = id_phys->phys_box_on_bus;
	device->phy_connected_dev_type = id_phys->phy_connected_dev_type[0];
	device->queue_depth =
		get_unaligned_le16(&id_phys->current_queue_depth_limit);
	device->active_path_index = id_phys->active_path_number;
	device->path_map = id_phys->redundant_path_present_map;
	स_नकल(&device->box,
		&id_phys->alternate_paths_phys_box_on_port,
		माप(device->box));
	स_नकल(&device->phys_connector,
		&id_phys->alternate_paths_phys_connector,
		माप(device->phys_connector));
	device->bay = id_phys->phys_bay_in_box;

	स_नकल(&device->page_83_identअगरier, &id_phys->page_83_identअगरier,
		माप(device->page_83_identअगरier));

	अगर ((id_phys->even_more_flags & PQI_DEVICE_PHY_MAP_SUPPORTED) &&
		id_phys->phy_count)
		device->phy_id =
			id_phys->phy_to_phy_map[device->active_path_index];
	अन्यथा
		device->phy_id = 0xFF;

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_get_logical_device_info(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक rc;
	u8 *buffer;

	buffer = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	/* Send an inquiry to the device to see what it is. */
	rc = pqi_scsi_inquiry(ctrl_info, device->scsi3addr, 0, buffer, 64);
	अगर (rc)
		जाओ out;

	scsi_sanitize_inquiry_string(&buffer[8], 8);
	scsi_sanitize_inquiry_string(&buffer[16], 16);

	device->devtype = buffer[0] & 0x1f;
	स_नकल(device->venकरोr, &buffer[8], माप(device->venकरोr));
	स_नकल(device->model, &buffer[16], माप(device->model));

	अगर (device->devtype == TYPE_DISK) अणु
		अगर (device->is_बाह्यal_raid_device) अणु
			device->raid_level = SA_RAID_UNKNOWN;
			device->volume_status = CISS_LV_OK;
			device->volume_offline = false;
		पूर्ण अन्यथा अणु
			pqi_get_raid_level(ctrl_info, device);
			pqi_get_raid_bypass_status(ctrl_info, device);
			pqi_get_volume_status(ctrl_info, device);
		पूर्ण
	पूर्ण

out:
	kमुक्त(buffer);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_get_device_info(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device,
	काष्ठा bmic_identअगरy_physical_device *id_phys)
अणु
	पूर्णांक rc;

	अगर (device->is_expander_smp_device)
		वापस 0;

	अगर (pqi_is_logical_device(device))
		rc = pqi_get_logical_device_info(ctrl_info, device);
	अन्यथा
		rc = pqi_get_physical_device_info(ctrl_info, device, id_phys);

	वापस rc;
पूर्ण

अटल व्योम pqi_show_volume_status(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device)
अणु
	अक्षर *status;
	अटल स्थिर अक्षर unknown_state_str[] =
		"Volume is in an unknown state (%u)";
	अक्षर unknown_state_buffer[माप(unknown_state_str) + 10];

	चयन (device->volume_status) अणु
	हाल CISS_LV_OK:
		status = "Volume online";
		अवरोध;
	हाल CISS_LV_FAILED:
		status = "Volume failed";
		अवरोध;
	हाल CISS_LV_NOT_CONFIGURED:
		status = "Volume not configured";
		अवरोध;
	हाल CISS_LV_DEGRADED:
		status = "Volume degraded";
		अवरोध;
	हाल CISS_LV_READY_FOR_RECOVERY:
		status = "Volume ready for recovery operation";
		अवरोध;
	हाल CISS_LV_UNDERGOING_RECOVERY:
		status = "Volume undergoing recovery";
		अवरोध;
	हाल CISS_LV_WRONG_PHYSICAL_DRIVE_REPLACED:
		status = "Wrong physical drive was replaced";
		अवरोध;
	हाल CISS_LV_PHYSICAL_DRIVE_CONNECTION_PROBLEM:
		status = "A physical drive not properly connected";
		अवरोध;
	हाल CISS_LV_HARDWARE_OVERHEATING:
		status = "Hardware is overheating";
		अवरोध;
	हाल CISS_LV_HARDWARE_HAS_OVERHEATED:
		status = "Hardware has overheated";
		अवरोध;
	हाल CISS_LV_UNDERGOING_EXPANSION:
		status = "Volume undergoing expansion";
		अवरोध;
	हाल CISS_LV_NOT_AVAILABLE:
		status = "Volume waiting for transforming volume";
		अवरोध;
	हाल CISS_LV_QUEUED_FOR_EXPANSION:
		status = "Volume queued for expansion";
		अवरोध;
	हाल CISS_LV_DISABLED_SCSI_ID_CONFLICT:
		status = "Volume disabled due to SCSI ID conflict";
		अवरोध;
	हाल CISS_LV_EJECTED:
		status = "Volume has been ejected";
		अवरोध;
	हाल CISS_LV_UNDERGOING_ERASE:
		status = "Volume undergoing background erase";
		अवरोध;
	हाल CISS_LV_READY_FOR_PREDICTIVE_SPARE_REBUILD:
		status = "Volume ready for predictive spare rebuild";
		अवरोध;
	हाल CISS_LV_UNDERGOING_RPI:
		status = "Volume undergoing rapid parity initialization";
		अवरोध;
	हाल CISS_LV_PENDING_RPI:
		status = "Volume queued for rapid parity initialization";
		अवरोध;
	हाल CISS_LV_ENCRYPTED_NO_KEY:
		status = "Encrypted volume inaccessible - key not present";
		अवरोध;
	हाल CISS_LV_UNDERGOING_ENCRYPTION:
		status = "Volume undergoing encryption process";
		अवरोध;
	हाल CISS_LV_UNDERGOING_ENCRYPTION_REKEYING:
		status = "Volume undergoing encryption re-keying process";
		अवरोध;
	हाल CISS_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER:
		status = "Volume encrypted but encryption is disabled";
		अवरोध;
	हाल CISS_LV_PENDING_ENCRYPTION:
		status = "Volume pending migration to encrypted state";
		अवरोध;
	हाल CISS_LV_PENDING_ENCRYPTION_REKEYING:
		status = "Volume pending encryption rekeying";
		अवरोध;
	हाल CISS_LV_NOT_SUPPORTED:
		status = "Volume not supported on this controller";
		अवरोध;
	हाल CISS_LV_STATUS_UNAVAILABLE:
		status = "Volume status not available";
		अवरोध;
	शेष:
		snम_लिखो(unknown_state_buffer, माप(unknown_state_buffer),
			unknown_state_str, device->volume_status);
		status = unknown_state_buffer;
		अवरोध;
	पूर्ण

	dev_info(&ctrl_info->pci_dev->dev,
		"scsi %d:%d:%d:%d %s\n",
		ctrl_info->scsi_host->host_no,
		device->bus, device->target, device->lun, status);
पूर्ण

अटल व्योम pqi_rescan_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = container_of(to_delayed_work(work), काष्ठा pqi_ctrl_info,
		rescan_work);

	pqi_scan_scsi_devices(ctrl_info);
पूर्ण

अटल पूर्णांक pqi_add_device(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक rc;

	अगर (pqi_is_logical_device(device))
		rc = scsi_add_device(ctrl_info->scsi_host, device->bus,
			device->target, device->lun);
	अन्यथा
		rc = pqi_add_sas_device(ctrl_info->sas_host, device);

	वापस rc;
पूर्ण

#घोषणा PQI_REMOVE_DEVICE_PENDING_IO_TIMEOUT_MSECS	(20 * 1000)

अटल अंतरभूत व्योम pqi_हटाओ_device(काष्ठा pqi_ctrl_info *ctrl_info, काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक rc;

	pqi_device_हटाओ_start(device);

	rc = pqi_device_रुको_क्रम_pending_io(ctrl_info, device,
		PQI_REMOVE_DEVICE_PENDING_IO_TIMEOUT_MSECS);
	अगर (rc)
		dev_err(&ctrl_info->pci_dev->dev,
			"scsi %d:%d:%d:%d removing device with %d outstanding command(s)\n",
			ctrl_info->scsi_host->host_no, device->bus,
			device->target, device->lun,
			atomic_पढ़ो(&device->scsi_cmds_outstanding));

	अगर (pqi_is_logical_device(device))
		scsi_हटाओ_device(device->sdev);
	अन्यथा
		pqi_हटाओ_sas_device(device);
पूर्ण

/* Assumes the SCSI device list lock is held. */

अटल काष्ठा pqi_scsi_dev *pqi_find_scsi_dev(काष्ठा pqi_ctrl_info *ctrl_info,
	पूर्णांक bus, पूर्णांक target, पूर्णांक lun)
अणु
	काष्ठा pqi_scsi_dev *device;

	list_क्रम_each_entry(device, &ctrl_info->scsi_device_list, scsi_device_list_entry)
		अगर (device->bus == bus && device->target == target && device->lun == lun)
			वापस device;

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool pqi_device_equal(काष्ठा pqi_scsi_dev *dev1, काष्ठा pqi_scsi_dev *dev2)
अणु
	अगर (dev1->is_physical_device != dev2->is_physical_device)
		वापस false;

	अगर (dev1->is_physical_device)
		वापस dev1->wwid == dev2->wwid;

	वापस स_भेद(dev1->volume_id, dev2->volume_id, माप(dev1->volume_id)) == 0;
पूर्ण

क्रमागत pqi_find_result अणु
	DEVICE_NOT_FOUND,
	DEVICE_CHANGED,
	DEVICE_SAME,
पूर्ण;

अटल क्रमागत pqi_find_result pqi_scsi_find_entry(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device_to_find, काष्ठा pqi_scsi_dev **matching_device)
अणु
	काष्ठा pqi_scsi_dev *device;

	list_क्रम_each_entry(device, &ctrl_info->scsi_device_list, scsi_device_list_entry) अणु
		अगर (pqi_scsi3addr_equal(device_to_find->scsi3addr, device->scsi3addr)) अणु
			*matching_device = device;
			अगर (pqi_device_equal(device_to_find, device)) अणु
				अगर (device_to_find->volume_offline)
					वापस DEVICE_CHANGED;
				वापस DEVICE_SAME;
			पूर्ण
			वापस DEVICE_CHANGED;
		पूर्ण
	पूर्ण

	वापस DEVICE_NOT_FOUND;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *pqi_device_type(काष्ठा pqi_scsi_dev *device)
अणु
	अगर (device->is_expander_smp_device)
		वापस "Enclosure SMP    ";

	वापस scsi_device_type(device->devtype);
पूर्ण

#घोषणा PQI_DEV_INFO_BUFFER_LENGTH	128

अटल व्योम pqi_dev_info(काष्ठा pqi_ctrl_info *ctrl_info,
	अक्षर *action, काष्ठा pqi_scsi_dev *device)
अणु
	sमाप_प्रकार count;
	अक्षर buffer[PQI_DEV_INFO_BUFFER_LENGTH];

	count = scnम_लिखो(buffer, PQI_DEV_INFO_BUFFER_LENGTH,
		"%d:%d:", ctrl_info->scsi_host->host_no, device->bus);

	अगर (device->target_lun_valid)
		count += scnम_लिखो(buffer + count,
			PQI_DEV_INFO_BUFFER_LENGTH - count,
			"%d:%d",
			device->target,
			device->lun);
	अन्यथा
		count += scnम_लिखो(buffer + count,
			PQI_DEV_INFO_BUFFER_LENGTH - count,
			"-:-");

	अगर (pqi_is_logical_device(device))
		count += scnम_लिखो(buffer + count,
			PQI_DEV_INFO_BUFFER_LENGTH - count,
			" %08x%08x",
			*((u32 *)&device->scsi3addr),
			*((u32 *)&device->scsi3addr[4]));
	अन्यथा
		count += scnम_लिखो(buffer + count,
			PQI_DEV_INFO_BUFFER_LENGTH - count,
			" %016llx", device->sas_address);

	count += scnम_लिखो(buffer + count, PQI_DEV_INFO_BUFFER_LENGTH - count,
		" %s %.8s %.16s ",
		pqi_device_type(device),
		device->venकरोr,
		device->model);

	अगर (pqi_is_logical_device(device)) अणु
		अगर (device->devtype == TYPE_DISK)
			count += scnम_लिखो(buffer + count,
				PQI_DEV_INFO_BUFFER_LENGTH - count,
				"SSDSmartPathCap%c En%c %-12s",
				device->raid_bypass_configured ? '+' : '-',
				device->raid_bypass_enabled ? '+' : '-',
				pqi_raid_level_to_string(device->raid_level));
	पूर्ण अन्यथा अणु
		count += scnम_लिखो(buffer + count,
			PQI_DEV_INFO_BUFFER_LENGTH - count,
			"AIO%c", device->aio_enabled ? '+' : '-');
		अगर (device->devtype == TYPE_DISK ||
			device->devtype == TYPE_ZBC)
			count += scnम_लिखो(buffer + count,
				PQI_DEV_INFO_BUFFER_LENGTH - count,
				" qd=%-6d", device->queue_depth);
	पूर्ण

	dev_info(&ctrl_info->pci_dev->dev, "%s %s\n", action, buffer);
पूर्ण

/* Assumes the SCSI device list lock is held. */

अटल व्योम pqi_scsi_update_device(काष्ठा pqi_scsi_dev *existing_device,
	काष्ठा pqi_scsi_dev *new_device)
अणु
	existing_device->device_type = new_device->device_type;
	existing_device->bus = new_device->bus;
	अगर (new_device->target_lun_valid) अणु
		existing_device->target = new_device->target;
		existing_device->lun = new_device->lun;
		existing_device->target_lun_valid = true;
	पूर्ण

	अगर ((existing_device->volume_status == CISS_LV_QUEUED_FOR_EXPANSION ||
		existing_device->volume_status == CISS_LV_UNDERGOING_EXPANSION) &&
		new_device->volume_status == CISS_LV_OK)
		existing_device->rescan = true;

	/* By definition, the scsi3addr and wwid fields are alपढ़ोy the same. */

	existing_device->is_physical_device = new_device->is_physical_device;
	existing_device->is_बाह्यal_raid_device =
		new_device->is_बाह्यal_raid_device;
	existing_device->is_expander_smp_device =
		new_device->is_expander_smp_device;
	existing_device->aio_enabled = new_device->aio_enabled;
	स_नकल(existing_device->venकरोr, new_device->venकरोr,
		माप(existing_device->venकरोr));
	स_नकल(existing_device->model, new_device->model,
		माप(existing_device->model));
	existing_device->sas_address = new_device->sas_address;
	existing_device->raid_level = new_device->raid_level;
	existing_device->queue_depth = new_device->queue_depth;
	existing_device->aio_handle = new_device->aio_handle;
	existing_device->volume_status = new_device->volume_status;
	existing_device->active_path_index = new_device->active_path_index;
	existing_device->phy_id = new_device->phy_id;
	existing_device->path_map = new_device->path_map;
	existing_device->bay = new_device->bay;
	existing_device->box_index = new_device->box_index;
	existing_device->phys_box_on_bus = new_device->phys_box_on_bus;
	existing_device->phy_connected_dev_type = new_device->phy_connected_dev_type;
	स_नकल(existing_device->box, new_device->box,
		माप(existing_device->box));
	स_नकल(existing_device->phys_connector, new_device->phys_connector,
		माप(existing_device->phys_connector));
	existing_device->next_bypass_group = 0;
	kमुक्त(existing_device->raid_map);
	existing_device->raid_map = new_device->raid_map;
	existing_device->raid_bypass_configured =
		new_device->raid_bypass_configured;
	existing_device->raid_bypass_enabled =
		new_device->raid_bypass_enabled;
	existing_device->device_offline = false;

	/* To prevent this from being मुक्तd later. */
	new_device->raid_map = शून्य;
पूर्ण

अटल अंतरभूत व्योम pqi_मुक्त_device(काष्ठा pqi_scsi_dev *device)
अणु
	अगर (device) अणु
		kमुक्त(device->raid_map);
		kमुक्त(device);
	पूर्ण
पूर्ण

/*
 * Called when exposing a new device to the OS fails in order to re-adjust
 * our पूर्णांकernal SCSI device list to match the SCSI ML's view.
 */

अटल अंतरभूत व्योम pqi_fixup_botched_add(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);
	list_del(&device->scsi_device_list_entry);
	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	/* Allow the device काष्ठाure to be मुक्तd later. */
	device->keep_device = false;
पूर्ण

अटल अंतरभूत bool pqi_is_device_added(काष्ठा pqi_scsi_dev *device)
अणु
	अगर (device->is_expander_smp_device)
		वापस device->sas_port != शून्य;

	वापस device->sdev != शून्य;
पूर्ण

अटल व्योम pqi_update_device_list(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *new_device_list[], अचिन्हित पूर्णांक num_new_devices)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;
	क्रमागत pqi_find_result find_result;
	काष्ठा pqi_scsi_dev *device;
	काष्ठा pqi_scsi_dev *next;
	काष्ठा pqi_scsi_dev *matching_device;
	LIST_HEAD(add_list);
	LIST_HEAD(delete_list);

	/*
	 * The idea here is to करो as little work as possible जबतक holding the
	 * spinlock.  That's why we go to great pains to defer anything other
	 * than updating the पूर्णांकernal device list until after we release the
	 * spinlock.
	 */

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);

	/* Assume that all devices in the existing list have gone away. */
	list_क्रम_each_entry(device, &ctrl_info->scsi_device_list, scsi_device_list_entry)
		device->device_gone = true;

	क्रम (i = 0; i < num_new_devices; i++) अणु
		device = new_device_list[i];

		find_result = pqi_scsi_find_entry(ctrl_info, device,
			&matching_device);

		चयन (find_result) अणु
		हाल DEVICE_SAME:
			/*
			 * The newly found device is alपढ़ोy in the existing
			 * device list.
			 */
			device->new_device = false;
			matching_device->device_gone = false;
			pqi_scsi_update_device(matching_device, device);
			अवरोध;
		हाल DEVICE_NOT_FOUND:
			/*
			 * The newly found device is NOT in the existing device
			 * list.
			 */
			device->new_device = true;
			अवरोध;
		हाल DEVICE_CHANGED:
			/*
			 * The original device has gone away and we need to add
			 * the new device.
			 */
			device->new_device = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Process all devices that have gone away. */
	list_क्रम_each_entry_safe(device, next, &ctrl_info->scsi_device_list,
		scsi_device_list_entry) अणु
		अगर (device->device_gone) अणु
			list_del_init(&device->scsi_device_list_entry);
			list_add_tail(&device->delete_list_entry, &delete_list);
		पूर्ण
	पूर्ण

	/* Process all new devices. */
	क्रम (i = 0; i < num_new_devices; i++) अणु
		device = new_device_list[i];
		अगर (!device->new_device)
			जारी;
		अगर (device->volume_offline)
			जारी;
		list_add_tail(&device->scsi_device_list_entry,
			&ctrl_info->scsi_device_list);
		list_add_tail(&device->add_list_entry, &add_list);
		/* To prevent this device काष्ठाure from being मुक्तd later. */
		device->keep_device = true;
	पूर्ण

	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	/*
	 * If OFA is in progress and there are devices that need to be deleted,
	 * allow any pending reset operations to जारी and unblock any SCSI
	 * requests beक्रमe removal.
	 */
	अगर (pqi_ofa_in_progress(ctrl_info)) अणु
		list_क्रम_each_entry_safe(device, next, &delete_list, delete_list_entry)
			अगर (pqi_is_device_added(device))
				pqi_device_हटाओ_start(device);
		pqi_ctrl_unblock_device_reset(ctrl_info);
		pqi_scsi_unblock_requests(ctrl_info);
	पूर्ण

	/* Remove all devices that have gone away. */
	list_क्रम_each_entry_safe(device, next, &delete_list, delete_list_entry) अणु
		अगर (device->volume_offline) अणु
			pqi_dev_info(ctrl_info, "offline", device);
			pqi_show_volume_status(ctrl_info, device);
		पूर्ण
		list_del(&device->delete_list_entry);
		अगर (pqi_is_device_added(device)) अणु
			pqi_हटाओ_device(ctrl_info, device);
		पूर्ण अन्यथा अणु
			अगर (!device->volume_offline)
				pqi_dev_info(ctrl_info, "removed", device);
			pqi_मुक्त_device(device);
		पूर्ण
	पूर्ण

	/*
	 * Notअगरy the SCSI ML अगर the queue depth of any existing device has
	 * changed.
	 */
	list_क्रम_each_entry(device, &ctrl_info->scsi_device_list, scsi_device_list_entry) अणु
		अगर (device->sdev && device->queue_depth != device->advertised_queue_depth) अणु
			device->advertised_queue_depth = device->queue_depth;
			scsi_change_queue_depth(device->sdev, device->advertised_queue_depth);
			अगर (device->rescan) अणु
				scsi_rescan_device(&device->sdev->sdev_gendev);
				device->rescan = false;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Expose any new devices. */
	list_क्रम_each_entry_safe(device, next, &add_list, add_list_entry) अणु
		अगर (!pqi_is_device_added(device)) अणु
			rc = pqi_add_device(ctrl_info, device);
			अगर (rc == 0) अणु
				pqi_dev_info(ctrl_info, "added", device);
			पूर्ण अन्यथा अणु
				dev_warn(&ctrl_info->pci_dev->dev,
					"scsi %d:%d:%d:%d addition failed, device not added\n",
					ctrl_info->scsi_host->host_no,
					device->bus, device->target,
					device->lun);
				pqi_fixup_botched_add(ctrl_info, device);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत bool pqi_is_supported_device(काष्ठा pqi_scsi_dev *device)
अणु
	/*
	 * Only support the HBA controller itself as a RAID
	 * controller.  If it's a RAID controller other than
	 * the HBA itself (an बाह्यal RAID controller, क्रम
	 * example), we करोn't support it.
	 */
	अगर (device->device_type == SA_DEVICE_TYPE_CONTROLLER &&
		!pqi_is_hba_lunid(device->scsi3addr))
			वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत bool pqi_skip_device(u8 *scsi3addr)
अणु
	/* Ignore all masked devices. */
	अगर (MASKED_DEVICE(scsi3addr))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत व्योम pqi_mask_device(u8 *scsi3addr)
अणु
	scsi3addr[3] |= 0xc0;
पूर्ण

अटल अंतरभूत bool pqi_is_device_with_sas_address(काष्ठा pqi_scsi_dev *device)
अणु
	चयन (device->device_type) अणु
	हाल SA_DEVICE_TYPE_SAS:
	हाल SA_DEVICE_TYPE_EXPANDER_SMP:
	हाल SA_DEVICE_TYPE_SES:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत bool pqi_expose_device(काष्ठा pqi_scsi_dev *device)
अणु
	वापस !device->is_physical_device || !pqi_skip_device(device->scsi3addr);
पूर्ण

अटल अंतरभूत व्योम pqi_set_physical_device_wwid(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device, काष्ठा report_phys_lun_extended_entry *phys_lun_ext_entry)
अणु
	अगर (ctrl_info->unique_wwid_in_report_phys_lun_supported ||
		pqi_is_device_with_sas_address(device))
		device->wwid = phys_lun_ext_entry->wwid;
	अन्यथा
		device->wwid = cpu_to_be64(get_unaligned_be64(&device->page_83_identअगरier));
पूर्ण

अटल पूर्णांक pqi_update_scsi_devices(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक i;
	पूर्णांक rc;
	LIST_HEAD(new_device_list_head);
	काष्ठा report_phys_lun_extended *physdev_list = शून्य;
	काष्ठा report_log_lun_extended *logdev_list = शून्य;
	काष्ठा report_phys_lun_extended_entry *phys_lun_ext_entry;
	काष्ठा report_log_lun_extended_entry *log_lun_ext_entry;
	काष्ठा bmic_identअगरy_physical_device *id_phys = शून्य;
	u32 num_physicals;
	u32 num_logicals;
	काष्ठा pqi_scsi_dev **new_device_list = शून्य;
	काष्ठा pqi_scsi_dev *device;
	काष्ठा pqi_scsi_dev *next;
	अचिन्हित पूर्णांक num_new_devices;
	अचिन्हित पूर्णांक num_valid_devices;
	bool is_physical_device;
	u8 *scsi3addr;
	अचिन्हित पूर्णांक physical_index;
	अचिन्हित पूर्णांक logical_index;
	अटल अक्षर *out_of_memory_msg =
		"failed to allocate memory, device discovery stopped";

	rc = pqi_get_device_lists(ctrl_info, &physdev_list, &logdev_list);
	अगर (rc)
		जाओ out;

	अगर (physdev_list)
		num_physicals =
			get_unaligned_be32(&physdev_list->header.list_length)
				/ माप(physdev_list->lun_entries[0]);
	अन्यथा
		num_physicals = 0;

	अगर (logdev_list)
		num_logicals =
			get_unaligned_be32(&logdev_list->header.list_length)
				/ माप(logdev_list->lun_entries[0]);
	अन्यथा
		num_logicals = 0;

	अगर (num_physicals) अणु
		/*
		 * We need this buffer क्रम calls to pqi_get_physical_disk_info()
		 * below.  We allocate it here instead of inside
		 * pqi_get_physical_disk_info() because it's a fairly large
		 * buffer.
		 */
		id_phys = kदो_स्मृति(माप(*id_phys), GFP_KERNEL);
		अगर (!id_phys) अणु
			dev_warn(&ctrl_info->pci_dev->dev, "%s\n",
				out_of_memory_msg);
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		अगर (pqi_hide_vsep) अणु
			क्रम (i = num_physicals - 1; i >= 0; i--) अणु
				phys_lun_ext_entry =
						&physdev_list->lun_entries[i];
				अगर (CISS_GET_DRIVE_NUMBER(phys_lun_ext_entry->lunid) == PQI_VSEP_CISS_BTL) अणु
					pqi_mask_device(phys_lun_ext_entry->lunid);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (num_logicals &&
		(logdev_list->header.flags & CISS_REPORT_LOG_FLAG_DRIVE_TYPE_MIX))
		ctrl_info->lv_drive_type_mix_valid = true;

	num_new_devices = num_physicals + num_logicals;

	new_device_list = kदो_स्मृति_array(num_new_devices,
					माप(*new_device_list),
					GFP_KERNEL);
	अगर (!new_device_list) अणु
		dev_warn(&ctrl_info->pci_dev->dev, "%s\n", out_of_memory_msg);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_new_devices; i++) अणु
		device = kzalloc(माप(*device), GFP_KERNEL);
		अगर (!device) अणु
			dev_warn(&ctrl_info->pci_dev->dev, "%s\n",
				out_of_memory_msg);
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		list_add_tail(&device->new_device_list_entry,
			&new_device_list_head);
	पूर्ण

	device = शून्य;
	num_valid_devices = 0;
	physical_index = 0;
	logical_index = 0;

	क्रम (i = 0; i < num_new_devices; i++) अणु

		अगर ((!pqi_expose_ld_first && i < num_physicals) ||
			(pqi_expose_ld_first && i >= num_logicals)) अणु
			is_physical_device = true;
			phys_lun_ext_entry =
				&physdev_list->lun_entries[physical_index++];
			log_lun_ext_entry = शून्य;
			scsi3addr = phys_lun_ext_entry->lunid;
		पूर्ण अन्यथा अणु
			is_physical_device = false;
			phys_lun_ext_entry = शून्य;
			log_lun_ext_entry =
				&logdev_list->lun_entries[logical_index++];
			scsi3addr = log_lun_ext_entry->lunid;
		पूर्ण

		अगर (is_physical_device && pqi_skip_device(scsi3addr))
			जारी;

		अगर (device)
			device = list_next_entry(device, new_device_list_entry);
		अन्यथा
			device = list_first_entry(&new_device_list_head,
				काष्ठा pqi_scsi_dev, new_device_list_entry);

		स_नकल(device->scsi3addr, scsi3addr, माप(device->scsi3addr));
		device->is_physical_device = is_physical_device;
		अगर (is_physical_device) अणु
			device->device_type = phys_lun_ext_entry->device_type;
			अगर (device->device_type == SA_DEVICE_TYPE_EXPANDER_SMP)
				device->is_expander_smp_device = true;
		पूर्ण अन्यथा अणु
			device->is_बाह्यal_raid_device =
				pqi_is_बाह्यal_raid_addr(scsi3addr);
		पूर्ण

		अगर (!pqi_is_supported_device(device))
			जारी;

		/* Gather inक्रमmation about the device. */
		rc = pqi_get_device_info(ctrl_info, device, id_phys);
		अगर (rc == -ENOMEM) अणु
			dev_warn(&ctrl_info->pci_dev->dev, "%s\n",
				out_of_memory_msg);
			जाओ out;
		पूर्ण
		अगर (rc) अणु
			अगर (device->is_physical_device)
				dev_warn(&ctrl_info->pci_dev->dev,
					"obtaining device info failed, skipping physical device %016llx\n",
					get_unaligned_be64(&phys_lun_ext_entry->wwid));
			अन्यथा
				dev_warn(&ctrl_info->pci_dev->dev,
					"obtaining device info failed, skipping logical device %08x%08x\n",
					*((u32 *)&device->scsi3addr),
					*((u32 *)&device->scsi3addr[4]));
			rc = 0;
			जारी;
		पूर्ण

		pqi_assign_bus_target_lun(device);

		अगर (device->is_physical_device) अणु
			pqi_set_physical_device_wwid(ctrl_info, device, phys_lun_ext_entry);
			अगर ((phys_lun_ext_entry->device_flags &
				CISS_REPORT_PHYS_DEV_FLAG_AIO_ENABLED) &&
				phys_lun_ext_entry->aio_handle) अणु
					device->aio_enabled = true;
					device->aio_handle =
						phys_lun_ext_entry->aio_handle;
			पूर्ण
		पूर्ण अन्यथा अणु
			स_नकल(device->volume_id, log_lun_ext_entry->volume_id,
				माप(device->volume_id));
		पूर्ण

		अगर (pqi_is_device_with_sas_address(device))
			device->sas_address = get_unaligned_be64(&device->wwid);

		new_device_list[num_valid_devices++] = device;
	पूर्ण

	pqi_update_device_list(ctrl_info, new_device_list, num_valid_devices);

out:
	list_क्रम_each_entry_safe(device, next, &new_device_list_head,
		new_device_list_entry) अणु
		अगर (device->keep_device)
			जारी;
		list_del(&device->new_device_list_entry);
		pqi_मुक्त_device(device);
	पूर्ण

	kमुक्त(new_device_list);
	kमुक्त(physdev_list);
	kमुक्त(logdev_list);
	kमुक्त(id_phys);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_scan_scsi_devices(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	पूर्णांक mutex_acquired;

	अगर (pqi_ctrl_offline(ctrl_info))
		वापस -ENXIO;

	mutex_acquired = mutex_trylock(&ctrl_info->scan_mutex);

	अगर (!mutex_acquired) अणु
		अगर (pqi_ctrl_scan_blocked(ctrl_info))
			वापस -EBUSY;
		pqi_schedule_rescan_worker_delayed(ctrl_info);
		वापस -EINPROGRESS;
	पूर्ण

	rc = pqi_update_scsi_devices(ctrl_info);
	अगर (rc && !pqi_ctrl_scan_blocked(ctrl_info))
		pqi_schedule_rescan_worker_delayed(ctrl_info);

	mutex_unlock(&ctrl_info->scan_mutex);

	वापस rc;
पूर्ण

अटल व्योम pqi_scan_start(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = shost_to_hba(shost);

	pqi_scan_scsi_devices(ctrl_info);
पूर्ण

/* Returns TRUE अगर scan is finished. */

अटल पूर्णांक pqi_scan_finished(काष्ठा Scsi_Host *shost,
	अचिन्हित दीर्घ elapsed_समय)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = shost_priv(shost);

	वापस !mutex_is_locked(&ctrl_info->scan_mutex);
पूर्ण

अटल अंतरभूत व्योम pqi_set_encryption_info(काष्ठा pqi_encryption_info *encryption_info,
	काष्ठा raid_map *raid_map, u64 first_block)
अणु
	u32 volume_blk_size;

	/*
	 * Set the encryption tweak values based on logical block address.
	 * If the block size is 512, the tweak value is equal to the LBA.
	 * For other block sizes, tweak value is (LBA * block size) / 512.
	 */
	volume_blk_size = get_unaligned_le32(&raid_map->volume_blk_size);
	अगर (volume_blk_size != 512)
		first_block = (first_block * volume_blk_size) / 512;

	encryption_info->data_encryption_key_index =
		get_unaligned_le16(&raid_map->data_encryption_key_index);
	encryption_info->encrypt_tweak_lower = lower_32_bits(first_block);
	encryption_info->encrypt_tweak_upper = upper_32_bits(first_block);
पूर्ण

/*
 * Attempt to perक्रमm RAID bypass mapping क्रम a logical volume I/O.
 */

अटल bool pqi_aio_raid_level_supported(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev_raid_map_data *rmd)
अणु
	bool is_supported = true;

	चयन (rmd->raid_level) अणु
	हाल SA_RAID_0:
		अवरोध;
	हाल SA_RAID_1:
		अगर (rmd->is_ग_लिखो && (!ctrl_info->enable_r1_ग_लिखोs ||
			rmd->data_length > ctrl_info->max_ग_लिखो_raid_1_10_2drive))
			is_supported = false;
		अवरोध;
	हाल SA_RAID_TRIPLE:
		अगर (rmd->is_ग_लिखो && (!ctrl_info->enable_r1_ग_लिखोs ||
			rmd->data_length > ctrl_info->max_ग_लिखो_raid_1_10_3drive))
			is_supported = false;
		अवरोध;
	हाल SA_RAID_5:
		अगर (rmd->is_ग_लिखो && (!ctrl_info->enable_r5_ग_लिखोs ||
			rmd->data_length > ctrl_info->max_ग_लिखो_raid_5_6))
			is_supported = false;
		अवरोध;
	हाल SA_RAID_6:
		अगर (rmd->is_ग_लिखो && (!ctrl_info->enable_r6_ग_लिखोs ||
			rmd->data_length > ctrl_info->max_ग_लिखो_raid_5_6))
			is_supported = false;
		अवरोध;
	शेष:
		is_supported = false;
		अवरोध;
	पूर्ण

	वापस is_supported;
पूर्ण

#घोषणा PQI_RAID_BYPASS_INELIGIBLE	1

अटल पूर्णांक pqi_get_aio_lba_and_block_count(काष्ठा scsi_cmnd *scmd,
	काष्ठा pqi_scsi_dev_raid_map_data *rmd)
अणु
	/* Check क्रम valid opcode, get LBA and block count. */
	चयन (scmd->cmnd[0]) अणु
	हाल WRITE_6:
		rmd->is_ग_लिखो = true;
		fallthrough;
	हाल READ_6:
		rmd->first_block = (u64)(((scmd->cmnd[1] & 0x1f) << 16) |
			(scmd->cmnd[2] << 8) | scmd->cmnd[3]);
		rmd->block_cnt = (u32)scmd->cmnd[4];
		अगर (rmd->block_cnt == 0)
			rmd->block_cnt = 256;
		अवरोध;
	हाल WRITE_10:
		rmd->is_ग_लिखो = true;
		fallthrough;
	हाल READ_10:
		rmd->first_block = (u64)get_unaligned_be32(&scmd->cmnd[2]);
		rmd->block_cnt = (u32)get_unaligned_be16(&scmd->cmnd[7]);
		अवरोध;
	हाल WRITE_12:
		rmd->is_ग_लिखो = true;
		fallthrough;
	हाल READ_12:
		rmd->first_block = (u64)get_unaligned_be32(&scmd->cmnd[2]);
		rmd->block_cnt = get_unaligned_be32(&scmd->cmnd[6]);
		अवरोध;
	हाल WRITE_16:
		rmd->is_ग_लिखो = true;
		fallthrough;
	हाल READ_16:
		rmd->first_block = get_unaligned_be64(&scmd->cmnd[2]);
		rmd->block_cnt = get_unaligned_be32(&scmd->cmnd[10]);
		अवरोध;
	शेष:
		/* Process via normal I/O path. */
		वापस PQI_RAID_BYPASS_INELIGIBLE;
	पूर्ण

	put_unaligned_le32(scsi_bufflen(scmd), &rmd->data_length);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_get_aio_common_raid_map_values(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev_raid_map_data *rmd, काष्ठा raid_map *raid_map)
अणु
#अगर BITS_PER_LONG == 32
	u64 पंचांगpभाग;
#पूर्ण_अगर

	rmd->last_block = rmd->first_block + rmd->block_cnt - 1;

	/* Check क्रम invalid block or wraparound. */
	अगर (rmd->last_block >=
		get_unaligned_le64(&raid_map->volume_blk_cnt) ||
		rmd->last_block < rmd->first_block)
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	rmd->data_disks_per_row =
		get_unaligned_le16(&raid_map->data_disks_per_row);
	rmd->strip_size = get_unaligned_le16(&raid_map->strip_size);
	rmd->layout_map_count = get_unaligned_le16(&raid_map->layout_map_count);

	/* Calculate stripe inक्रमmation क्रम the request. */
	rmd->blocks_per_row = rmd->data_disks_per_row * rmd->strip_size;
	अगर (rmd->blocks_per_row == 0) /* Used as a भागisor in many calculations */
		वापस PQI_RAID_BYPASS_INELIGIBLE;
#अगर BITS_PER_LONG == 32
	पंचांगpभाग = rmd->first_block;
	करो_भाग(पंचांगpभाग, rmd->blocks_per_row);
	rmd->first_row = पंचांगpभाग;
	पंचांगpभाग = rmd->last_block;
	करो_भाग(पंचांगpभाग, rmd->blocks_per_row);
	rmd->last_row = पंचांगpभाग;
	rmd->first_row_offset = (u32)(rmd->first_block - (rmd->first_row * rmd->blocks_per_row));
	rmd->last_row_offset = (u32)(rmd->last_block - (rmd->last_row * rmd->blocks_per_row));
	पंचांगpभाग = rmd->first_row_offset;
	करो_भाग(पंचांगpभाग, rmd->strip_size);
	rmd->first_column = पंचांगpभाग;
	पंचांगpभाग = rmd->last_row_offset;
	करो_भाग(पंचांगpभाग, rmd->strip_size);
	rmd->last_column = पंचांगpभाग;
#अन्यथा
	rmd->first_row = rmd->first_block / rmd->blocks_per_row;
	rmd->last_row = rmd->last_block / rmd->blocks_per_row;
	rmd->first_row_offset = (u32)(rmd->first_block -
		(rmd->first_row * rmd->blocks_per_row));
	rmd->last_row_offset = (u32)(rmd->last_block - (rmd->last_row *
		rmd->blocks_per_row));
	rmd->first_column = rmd->first_row_offset / rmd->strip_size;
	rmd->last_column = rmd->last_row_offset / rmd->strip_size;
#पूर्ण_अगर

	/* If this isn't a single row/column then give to the controller. */
	अगर (rmd->first_row != rmd->last_row ||
		rmd->first_column != rmd->last_column)
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	/* Proceeding with driver mapping. */
	rmd->total_disks_per_row = rmd->data_disks_per_row +
		get_unaligned_le16(&raid_map->metadata_disks_per_row);
	rmd->map_row = ((u32)(rmd->first_row >>
		raid_map->parity_rotation_shअगरt)) %
		get_unaligned_le16(&raid_map->row_cnt);
	rmd->map_index = (rmd->map_row * rmd->total_disks_per_row) +
		rmd->first_column;

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_calc_aio_r5_or_r6(काष्ठा pqi_scsi_dev_raid_map_data *rmd,
	काष्ठा raid_map *raid_map)
अणु
#अगर BITS_PER_LONG == 32
	u64 पंचांगpभाग;
#पूर्ण_अगर

	अगर (rmd->blocks_per_row == 0) /* Used as a भागisor in many calculations */
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	/* RAID 50/60 */
	/* Verअगरy first and last block are in same RAID group. */
	rmd->stripesize = rmd->blocks_per_row * rmd->layout_map_count;
#अगर BITS_PER_LONG == 32
	पंचांगpभाग = rmd->first_block;
	rmd->first_group = करो_भाग(पंचांगpभाग, rmd->stripesize);
	पंचांगpभाग = rmd->first_group;
	करो_भाग(पंचांगpभाग, rmd->blocks_per_row);
	rmd->first_group = पंचांगpभाग;
	पंचांगpभाग = rmd->last_block;
	rmd->last_group = करो_भाग(पंचांगpभाग, rmd->stripesize);
	पंचांगpभाग = rmd->last_group;
	करो_भाग(पंचांगpभाग, rmd->blocks_per_row);
	rmd->last_group = पंचांगpभाग;
#अन्यथा
	rmd->first_group = (rmd->first_block % rmd->stripesize) / rmd->blocks_per_row;
	rmd->last_group = (rmd->last_block % rmd->stripesize) / rmd->blocks_per_row;
#पूर्ण_अगर
	अगर (rmd->first_group != rmd->last_group)
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	/* Verअगरy request is in a single row of RAID 5/6. */
#अगर BITS_PER_LONG == 32
	पंचांगpभाग = rmd->first_block;
	करो_भाग(पंचांगpभाग, rmd->stripesize);
	rmd->first_row = पंचांगpभाग;
	rmd->r5or6_first_row = पंचांगpभाग;
	पंचांगpभाग = rmd->last_block;
	करो_भाग(पंचांगpभाग, rmd->stripesize);
	rmd->r5or6_last_row = पंचांगpभाग;
#अन्यथा
	rmd->first_row = rmd->r5or6_first_row =
		rmd->first_block / rmd->stripesize;
	rmd->r5or6_last_row = rmd->last_block / rmd->stripesize;
#पूर्ण_अगर
	अगर (rmd->r5or6_first_row != rmd->r5or6_last_row)
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	/* Verअगरy request is in a single column. */
#अगर BITS_PER_LONG == 32
	पंचांगpभाग = rmd->first_block;
	rmd->first_row_offset = करो_भाग(पंचांगpभाग, rmd->stripesize);
	पंचांगpभाग = rmd->first_row_offset;
	rmd->first_row_offset = (u32)करो_भाग(पंचांगpभाग, rmd->blocks_per_row);
	rmd->r5or6_first_row_offset = rmd->first_row_offset;
	पंचांगpभाग = rmd->last_block;
	rmd->r5or6_last_row_offset = करो_भाग(पंचांगpभाग, rmd->stripesize);
	पंचांगpभाग = rmd->r5or6_last_row_offset;
	rmd->r5or6_last_row_offset = करो_भाग(पंचांगpभाग, rmd->blocks_per_row);
	पंचांगpभाग = rmd->r5or6_first_row_offset;
	करो_भाग(पंचांगpभाग, rmd->strip_size);
	rmd->first_column = rmd->r5or6_first_column = पंचांगpभाग;
	पंचांगpभाग = rmd->r5or6_last_row_offset;
	करो_भाग(पंचांगpभाग, rmd->strip_size);
	rmd->r5or6_last_column = पंचांगpभाग;
#अन्यथा
	rmd->first_row_offset = rmd->r5or6_first_row_offset =
		(u32)((rmd->first_block % rmd->stripesize) %
		rmd->blocks_per_row);

	rmd->r5or6_last_row_offset =
		(u32)((rmd->last_block % rmd->stripesize) %
		rmd->blocks_per_row);

	rmd->first_column =
		rmd->r5or6_first_row_offset / rmd->strip_size;
	rmd->r5or6_first_column = rmd->first_column;
	rmd->r5or6_last_column = rmd->r5or6_last_row_offset / rmd->strip_size;
#पूर्ण_अगर
	अगर (rmd->r5or6_first_column != rmd->r5or6_last_column)
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	/* Request is eligible. */
	rmd->map_row =
		((u32)(rmd->first_row >> raid_map->parity_rotation_shअगरt)) %
		get_unaligned_le16(&raid_map->row_cnt);

	rmd->map_index = (rmd->first_group *
		(get_unaligned_le16(&raid_map->row_cnt) *
		rmd->total_disks_per_row)) +
		(rmd->map_row * rmd->total_disks_per_row) + rmd->first_column;

	अगर (rmd->is_ग_लिखो) अणु
		u32 index;

		/*
		 * p_parity_it_nexus and q_parity_it_nexus are poपूर्णांकers to the
		 * parity entries inside the device's raid_map.
		 *
		 * A device's RAID map is bounded by: number of RAID disks squared.
		 *
		 * The devices RAID map size is checked during device
		 * initialization.
		 */
		index = DIV_ROUND_UP(rmd->map_index + 1, rmd->total_disks_per_row);
		index *= rmd->total_disks_per_row;
		index -= get_unaligned_le16(&raid_map->metadata_disks_per_row);

		rmd->p_parity_it_nexus = raid_map->disk_data[index].aio_handle;
		अगर (rmd->raid_level == SA_RAID_6) अणु
			rmd->q_parity_it_nexus = raid_map->disk_data[index + 1].aio_handle;
			rmd->xor_mult = raid_map->disk_data[rmd->map_index].xor_mult[1];
		पूर्ण
#अगर BITS_PER_LONG == 32
		पंचांगpभाग = rmd->first_block;
		करो_भाग(पंचांगpभाग, rmd->blocks_per_row);
		rmd->row = पंचांगpभाग;
#अन्यथा
		rmd->row = rmd->first_block / rmd->blocks_per_row;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pqi_set_aio_cdb(काष्ठा pqi_scsi_dev_raid_map_data *rmd)
अणु
	/* Build the new CDB क्रम the physical disk I/O. */
	अगर (rmd->disk_block > 0xffffffff) अणु
		rmd->cdb[0] = rmd->is_ग_लिखो ? WRITE_16 : READ_16;
		rmd->cdb[1] = 0;
		put_unaligned_be64(rmd->disk_block, &rmd->cdb[2]);
		put_unaligned_be32(rmd->disk_block_cnt, &rmd->cdb[10]);
		rmd->cdb[14] = 0;
		rmd->cdb[15] = 0;
		rmd->cdb_length = 16;
	पूर्ण अन्यथा अणु
		rmd->cdb[0] = rmd->is_ग_लिखो ? WRITE_10 : READ_10;
		rmd->cdb[1] = 0;
		put_unaligned_be32((u32)rmd->disk_block, &rmd->cdb[2]);
		rmd->cdb[6] = 0;
		put_unaligned_be16((u16)rmd->disk_block_cnt, &rmd->cdb[7]);
		rmd->cdb[9] = 0;
		rmd->cdb_length = 10;
	पूर्ण
पूर्ण

अटल व्योम pqi_calc_aio_r1_nexus(काष्ठा raid_map *raid_map,
	काष्ठा pqi_scsi_dev_raid_map_data *rmd)
अणु
	u32 index;
	u32 group;

	group = rmd->map_index / rmd->data_disks_per_row;

	index = rmd->map_index - (group * rmd->data_disks_per_row);
	rmd->it_nexus[0] = raid_map->disk_data[index].aio_handle;
	index += rmd->data_disks_per_row;
	rmd->it_nexus[1] = raid_map->disk_data[index].aio_handle;
	अगर (rmd->layout_map_count > 2) अणु
		index += rmd->data_disks_per_row;
		rmd->it_nexus[2] = raid_map->disk_data[index].aio_handle;
	पूर्ण

	rmd->num_it_nexus_entries = rmd->layout_map_count;
पूर्ण

अटल पूर्णांक pqi_raid_bypass_submit_scsi_cmd(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device, काष्ठा scsi_cmnd *scmd,
	काष्ठा pqi_queue_group *queue_group)
अणु
	पूर्णांक rc;
	काष्ठा raid_map *raid_map;
	u32 group;
	u32 next_bypass_group;
	काष्ठा pqi_encryption_info *encryption_info_ptr;
	काष्ठा pqi_encryption_info encryption_info;
	काष्ठा pqi_scsi_dev_raid_map_data rmd = अणु 0 पूर्ण;

	rc = pqi_get_aio_lba_and_block_count(scmd, &rmd);
	अगर (rc)
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	rmd.raid_level = device->raid_level;

	अगर (!pqi_aio_raid_level_supported(ctrl_info, &rmd))
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	अगर (unlikely(rmd.block_cnt == 0))
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	raid_map = device->raid_map;

	rc = pci_get_aio_common_raid_map_values(ctrl_info, &rmd, raid_map);
	अगर (rc)
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	अगर (device->raid_level == SA_RAID_1 ||
		device->raid_level == SA_RAID_TRIPLE) अणु
		अगर (rmd.is_ग_लिखो) अणु
			pqi_calc_aio_r1_nexus(raid_map, &rmd);
		पूर्ण अन्यथा अणु
			group = device->next_bypass_group;
			next_bypass_group = group + 1;
			अगर (next_bypass_group >= rmd.layout_map_count)
				next_bypass_group = 0;
			device->next_bypass_group = next_bypass_group;
			rmd.map_index += group * rmd.data_disks_per_row;
		पूर्ण
	पूर्ण अन्यथा अगर ((device->raid_level == SA_RAID_5 ||
		device->raid_level == SA_RAID_6) &&
		(rmd.layout_map_count > 1 || rmd.is_ग_लिखो)) अणु
		rc = pqi_calc_aio_r5_or_r6(&rmd, raid_map);
		अगर (rc)
			वापस PQI_RAID_BYPASS_INELIGIBLE;
	पूर्ण

	अगर (unlikely(rmd.map_index >= RAID_MAP_MAX_ENTRIES))
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	rmd.aio_handle = raid_map->disk_data[rmd.map_index].aio_handle;
	rmd.disk_block = get_unaligned_le64(&raid_map->disk_starting_blk) +
		rmd.first_row * rmd.strip_size +
		(rmd.first_row_offset - rmd.first_column * rmd.strip_size);
	rmd.disk_block_cnt = rmd.block_cnt;

	/* Handle dअगरfering logical/physical block sizes. */
	अगर (raid_map->phys_blk_shअगरt) अणु
		rmd.disk_block <<= raid_map->phys_blk_shअगरt;
		rmd.disk_block_cnt <<= raid_map->phys_blk_shअगरt;
	पूर्ण

	अगर (unlikely(rmd.disk_block_cnt > 0xffff))
		वापस PQI_RAID_BYPASS_INELIGIBLE;

	pqi_set_aio_cdb(&rmd);

	अगर (get_unaligned_le16(&raid_map->flags) & RAID_MAP_ENCRYPTION_ENABLED) अणु
		अगर (rmd.data_length > device->max_transfer_encrypted)
			वापस PQI_RAID_BYPASS_INELIGIBLE;
		pqi_set_encryption_info(&encryption_info, raid_map, rmd.first_block);
		encryption_info_ptr = &encryption_info;
	पूर्ण अन्यथा अणु
		encryption_info_ptr = शून्य;
	पूर्ण

	अगर (rmd.is_ग_लिखो) अणु
		चयन (device->raid_level) अणु
		हाल SA_RAID_1:
		हाल SA_RAID_TRIPLE:
			वापस pqi_aio_submit_r1_ग_लिखो_io(ctrl_info, scmd, queue_group,
				encryption_info_ptr, device, &rmd);
		हाल SA_RAID_5:
		हाल SA_RAID_6:
			वापस pqi_aio_submit_r56_ग_लिखो_io(ctrl_info, scmd, queue_group,
				encryption_info_ptr, device, &rmd);
		पूर्ण
	पूर्ण

	वापस pqi_aio_submit_io(ctrl_info, scmd, rmd.aio_handle,
		rmd.cdb, rmd.cdb_length, queue_group,
		encryption_info_ptr, true);
पूर्ण

#घोषणा PQI_STATUS_IDLE		0x0

#घोषणा PQI_CREATE_ADMIN_QUEUE_PAIR	1
#घोषणा PQI_DELETE_ADMIN_QUEUE_PAIR	2

#घोषणा PQI_DEVICE_STATE_POWER_ON_AND_RESET		0x0
#घोषणा PQI_DEVICE_STATE_STATUS_AVAILABLE		0x1
#घोषणा PQI_DEVICE_STATE_ALL_REGISTERS_READY		0x2
#घोषणा PQI_DEVICE_STATE_ADMIN_QUEUE_PAIR_READY		0x3
#घोषणा PQI_DEVICE_STATE_ERROR				0x4

#घोषणा PQI_MODE_READY_TIMEOUT_SECS		30
#घोषणा PQI_MODE_READY_POLL_INTERVAL_MSECS	1

अटल पूर्णांक pqi_रुको_क्रम_pqi_mode_पढ़ोy(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	काष्ठा pqi_device_रेजिस्टरs __iomem *pqi_रेजिस्टरs;
	अचिन्हित दीर्घ समयout;
	u64 signature;
	u8 status;

	pqi_रेजिस्टरs = ctrl_info->pqi_रेजिस्टरs;
	समयout = (PQI_MODE_READY_TIMEOUT_SECS * PQI_HZ) + jअगरfies;

	जबतक (1) अणु
		signature = पढ़ोq(&pqi_रेजिस्टरs->signature);
		अगर (स_भेद(&signature, PQI_DEVICE_SIGNATURE,
			माप(signature)) == 0)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"timed out waiting for PQI signature\n");
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(PQI_MODE_READY_POLL_INTERVAL_MSECS);
	पूर्ण

	जबतक (1) अणु
		status = पढ़ोb(&pqi_रेजिस्टरs->function_and_status_code);
		अगर (status == PQI_STATUS_IDLE)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"timed out waiting for PQI IDLE\n");
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(PQI_MODE_READY_POLL_INTERVAL_MSECS);
	पूर्ण

	जबतक (1) अणु
		अगर (पढ़ोl(&pqi_रेजिस्टरs->device_status) ==
			PQI_DEVICE_STATE_ALL_REGISTERS_READY)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"timed out waiting for PQI all registers ready\n");
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(PQI_MODE_READY_POLL_INTERVAL_MSECS);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pqi_aio_path_disabled(काष्ठा pqi_io_request *io_request)
अणु
	काष्ठा pqi_scsi_dev *device;

	device = io_request->scmd->device->hostdata;
	device->raid_bypass_enabled = false;
	device->aio_enabled = false;
पूर्ण

अटल अंतरभूत व्योम pqi_take_device_offline(काष्ठा scsi_device *sdev, अक्षर *path)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा pqi_scsi_dev *device;

	device = sdev->hostdata;
	अगर (device->device_offline)
		वापस;

	device->device_offline = true;
	ctrl_info = shost_to_hba(sdev->host);
	pqi_schedule_rescan_worker(ctrl_info);
	dev_err(&ctrl_info->pci_dev->dev, "re-scanning %s scsi %d:%d:%d:%d\n",
		path, ctrl_info->scsi_host->host_no, device->bus,
		device->target, device->lun);
पूर्ण

अटल व्योम pqi_process_raid_io_error(काष्ठा pqi_io_request *io_request)
अणु
	u8 scsi_status;
	u8 host_byte;
	काष्ठा scsi_cmnd *scmd;
	काष्ठा pqi_raid_error_info *error_info;
	माप_प्रकार sense_data_length;
	पूर्णांक residual_count;
	पूर्णांक xfer_count;
	काष्ठा scsi_sense_hdr sshdr;

	scmd = io_request->scmd;
	अगर (!scmd)
		वापस;

	error_info = io_request->error_info;
	scsi_status = error_info->status;
	host_byte = DID_OK;

	चयन (error_info->data_out_result) अणु
	हाल PQI_DATA_IN_OUT_GOOD:
		अवरोध;
	हाल PQI_DATA_IN_OUT_UNDERFLOW:
		xfer_count =
			get_unaligned_le32(&error_info->data_out_transferred);
		residual_count = scsi_bufflen(scmd) - xfer_count;
		scsi_set_resid(scmd, residual_count);
		अगर (xfer_count < scmd->underflow)
			host_byte = DID_SOFT_ERROR;
		अवरोध;
	हाल PQI_DATA_IN_OUT_UNSOLICITED_ABORT:
	हाल PQI_DATA_IN_OUT_ABORTED:
		host_byte = DID_ABORT;
		अवरोध;
	हाल PQI_DATA_IN_OUT_TIMEOUT:
		host_byte = DID_TIME_OUT;
		अवरोध;
	हाल PQI_DATA_IN_OUT_BUFFER_OVERFLOW:
	हाल PQI_DATA_IN_OUT_PROTOCOL_ERROR:
	हाल PQI_DATA_IN_OUT_BUFFER_ERROR:
	हाल PQI_DATA_IN_OUT_BUFFER_OVERFLOW_DESCRIPTOR_AREA:
	हाल PQI_DATA_IN_OUT_BUFFER_OVERFLOW_BRIDGE:
	हाल PQI_DATA_IN_OUT_ERROR:
	हाल PQI_DATA_IN_OUT_HARDWARE_ERROR:
	हाल PQI_DATA_IN_OUT_PCIE_FABRIC_ERROR:
	हाल PQI_DATA_IN_OUT_PCIE_COMPLETION_TIMEOUT:
	हाल PQI_DATA_IN_OUT_PCIE_COMPLETER_ABORT_RECEIVED:
	हाल PQI_DATA_IN_OUT_PCIE_UNSUPPORTED_REQUEST_RECEIVED:
	हाल PQI_DATA_IN_OUT_PCIE_ECRC_CHECK_FAILED:
	हाल PQI_DATA_IN_OUT_PCIE_UNSUPPORTED_REQUEST:
	हाल PQI_DATA_IN_OUT_PCIE_ACS_VIOLATION:
	हाल PQI_DATA_IN_OUT_PCIE_TLP_PREFIX_BLOCKED:
	हाल PQI_DATA_IN_OUT_PCIE_POISONED_MEMORY_READ:
	शेष:
		host_byte = DID_ERROR;
		अवरोध;
	पूर्ण

	sense_data_length = get_unaligned_le16(&error_info->sense_data_length);
	अगर (sense_data_length == 0)
		sense_data_length =
			get_unaligned_le16(&error_info->response_data_length);
	अगर (sense_data_length) अणु
		अगर (sense_data_length > माप(error_info->data))
			sense_data_length = माप(error_info->data);

		अगर (scsi_status == SAM_STAT_CHECK_CONDITION &&
			scsi_normalize_sense(error_info->data,
				sense_data_length, &sshdr) &&
				sshdr.sense_key == HARDWARE_ERROR &&
				sshdr.asc == 0x3e) अणु
			काष्ठा pqi_ctrl_info *ctrl_info = shost_to_hba(scmd->device->host);
			काष्ठा pqi_scsi_dev *device = scmd->device->hostdata;

			चयन (sshdr.ascq) अणु
			हाल 0x1: /* LOGICAL UNIT FAILURE */
				अगर (prपूर्णांकk_ratelimit())
					scmd_prपूर्णांकk(KERN_ERR, scmd, "received 'logical unit failure' from controller for scsi %d:%d:%d:%d\n",
						ctrl_info->scsi_host->host_no, device->bus, device->target, device->lun);
				pqi_take_device_offline(scmd->device, "RAID");
				host_byte = DID_NO_CONNECT;
				अवरोध;

			शेष: /* See http://www.t10.org/lists/asc-num.hपंचांग#ASC_3E */
				अगर (prपूर्णांकk_ratelimit())
					scmd_prपूर्णांकk(KERN_ERR, scmd, "received unhandled error %d from controller for scsi %d:%d:%d:%d\n",
						sshdr.ascq, ctrl_info->scsi_host->host_no, device->bus, device->target, device->lun);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (sense_data_length > SCSI_SENSE_BUFFERSIZE)
			sense_data_length = SCSI_SENSE_BUFFERSIZE;
		स_नकल(scmd->sense_buffer, error_info->data,
			sense_data_length);
	पूर्ण

	scmd->result = scsi_status;
	set_host_byte(scmd, host_byte);
पूर्ण

अटल व्योम pqi_process_aio_io_error(काष्ठा pqi_io_request *io_request)
अणु
	u8 scsi_status;
	u8 host_byte;
	काष्ठा scsi_cmnd *scmd;
	काष्ठा pqi_aio_error_info *error_info;
	माप_प्रकार sense_data_length;
	पूर्णांक residual_count;
	पूर्णांक xfer_count;
	bool device_offline;

	scmd = io_request->scmd;
	error_info = io_request->error_info;
	host_byte = DID_OK;
	sense_data_length = 0;
	device_offline = false;

	चयन (error_info->service_response) अणु
	हाल PQI_AIO_SERV_RESPONSE_COMPLETE:
		scsi_status = error_info->status;
		अवरोध;
	हाल PQI_AIO_SERV_RESPONSE_FAILURE:
		चयन (error_info->status) अणु
		हाल PQI_AIO_STATUS_IO_ABORTED:
			scsi_status = SAM_STAT_TASK_ABORTED;
			अवरोध;
		हाल PQI_AIO_STATUS_UNDERRUN:
			scsi_status = SAM_STAT_GOOD;
			residual_count = get_unaligned_le32(
						&error_info->residual_count);
			scsi_set_resid(scmd, residual_count);
			xfer_count = scsi_bufflen(scmd) - residual_count;
			अगर (xfer_count < scmd->underflow)
				host_byte = DID_SOFT_ERROR;
			अवरोध;
		हाल PQI_AIO_STATUS_OVERRUN:
			scsi_status = SAM_STAT_GOOD;
			अवरोध;
		हाल PQI_AIO_STATUS_AIO_PATH_DISABLED:
			pqi_aio_path_disabled(io_request);
			scsi_status = SAM_STAT_GOOD;
			io_request->status = -EAGAIN;
			अवरोध;
		हाल PQI_AIO_STATUS_NO_PATH_TO_DEVICE:
		हाल PQI_AIO_STATUS_INVALID_DEVICE:
			अगर (!io_request->raid_bypass) अणु
				device_offline = true;
				pqi_take_device_offline(scmd->device, "AIO");
				host_byte = DID_NO_CONNECT;
			पूर्ण
			scsi_status = SAM_STAT_CHECK_CONDITION;
			अवरोध;
		हाल PQI_AIO_STATUS_IO_ERROR:
		शेष:
			scsi_status = SAM_STAT_CHECK_CONDITION;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PQI_AIO_SERV_RESPONSE_TMF_COMPLETE:
	हाल PQI_AIO_SERV_RESPONSE_TMF_SUCCEEDED:
		scsi_status = SAM_STAT_GOOD;
		अवरोध;
	हाल PQI_AIO_SERV_RESPONSE_TMF_REJECTED:
	हाल PQI_AIO_SERV_RESPONSE_TMF_INCORRECT_LUN:
	शेष:
		scsi_status = SAM_STAT_CHECK_CONDITION;
		अवरोध;
	पूर्ण

	अगर (error_info->data_present) अणु
		sense_data_length =
			get_unaligned_le16(&error_info->data_length);
		अगर (sense_data_length) अणु
			अगर (sense_data_length > माप(error_info->data))
				sense_data_length = माप(error_info->data);
			अगर (sense_data_length > SCSI_SENSE_BUFFERSIZE)
				sense_data_length = SCSI_SENSE_BUFFERSIZE;
			स_नकल(scmd->sense_buffer, error_info->data,
				sense_data_length);
		पूर्ण
	पूर्ण

	अगर (device_offline && sense_data_length == 0)
		scsi_build_sense_buffer(0, scmd->sense_buffer, HARDWARE_ERROR,
			0x3e, 0x1);

	scmd->result = scsi_status;
	set_host_byte(scmd, host_byte);
पूर्ण

अटल व्योम pqi_process_io_error(अचिन्हित पूर्णांक iu_type,
	काष्ठा pqi_io_request *io_request)
अणु
	चयन (iu_type) अणु
	हाल PQI_RESPONSE_IU_RAID_PATH_IO_ERROR:
		pqi_process_raid_io_error(io_request);
		अवरोध;
	हाल PQI_RESPONSE_IU_AIO_PATH_IO_ERROR:
		pqi_process_aio_io_error(io_request);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pqi_पूर्णांकerpret_task_management_response(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_task_management_response *response)
अणु
	पूर्णांक rc;

	चयन (response->response_code) अणु
	हाल SOP_TMF_COMPLETE:
	हाल SOP_TMF_FUNCTION_SUCCEEDED:
		rc = 0;
		अवरोध;
	हाल SOP_TMF_REJECTED:
		rc = -EAGAIN;
		अवरोध;
	शेष:
		rc = -EIO;
		अवरोध;
	पूर्ण

	अगर (rc)
		dev_err(&ctrl_info->pci_dev->dev,
			"Task Management Function error: %d (response code: %u)\n", rc, response->response_code);

	वापस rc;
पूर्ण

अटल अंतरभूत व्योम pqi_invalid_response(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	pqi_take_ctrl_offline(ctrl_info);
पूर्ण

अटल पूर्णांक pqi_process_io_पूर्णांकr(काष्ठा pqi_ctrl_info *ctrl_info, काष्ठा pqi_queue_group *queue_group)
अणु
	पूर्णांक num_responses;
	pqi_index_t oq_pi;
	pqi_index_t oq_ci;
	काष्ठा pqi_io_request *io_request;
	काष्ठा pqi_io_response *response;
	u16 request_id;

	num_responses = 0;
	oq_ci = queue_group->oq_ci_copy;

	जबतक (1) अणु
		oq_pi = पढ़ोl(queue_group->oq_pi);
		अगर (oq_pi >= ctrl_info->num_elements_per_oq) अणु
			pqi_invalid_response(ctrl_info);
			dev_err(&ctrl_info->pci_dev->dev,
				"I/O interrupt: producer index (%u) out of range (0-%u): consumer index: %u\n",
				oq_pi, ctrl_info->num_elements_per_oq - 1, oq_ci);
			वापस -1;
		पूर्ण
		अगर (oq_pi == oq_ci)
			अवरोध;

		num_responses++;
		response = queue_group->oq_element_array +
			(oq_ci * PQI_OPERATIONAL_OQ_ELEMENT_LENGTH);

		request_id = get_unaligned_le16(&response->request_id);
		अगर (request_id >= ctrl_info->max_io_slots) अणु
			pqi_invalid_response(ctrl_info);
			dev_err(&ctrl_info->pci_dev->dev,
				"request ID in response (%u) out of range (0-%u): producer index: %u  consumer index: %u\n",
				request_id, ctrl_info->max_io_slots - 1, oq_pi, oq_ci);
			वापस -1;
		पूर्ण

		io_request = &ctrl_info->io_request_pool[request_id];
		अगर (atomic_पढ़ो(&io_request->refcount) == 0) अणु
			pqi_invalid_response(ctrl_info);
			dev_err(&ctrl_info->pci_dev->dev,
				"request ID in response (%u) does not match an outstanding I/O request: producer index: %u  consumer index: %u\n",
				request_id, oq_pi, oq_ci);
			वापस -1;
		पूर्ण

		चयन (response->header.iu_type) अणु
		हाल PQI_RESPONSE_IU_RAID_PATH_IO_SUCCESS:
		हाल PQI_RESPONSE_IU_AIO_PATH_IO_SUCCESS:
			अगर (io_request->scmd)
				io_request->scmd->result = 0;
			fallthrough;
		हाल PQI_RESPONSE_IU_GENERAL_MANAGEMENT:
			अवरोध;
		हाल PQI_RESPONSE_IU_VENDOR_GENERAL:
			io_request->status =
				get_unaligned_le16(
				&((काष्ठा pqi_venकरोr_general_response *)response)->status);
			अवरोध;
		हाल PQI_RESPONSE_IU_TASK_MANAGEMENT:
			io_request->status = pqi_पूर्णांकerpret_task_management_response(ctrl_info,
				(व्योम *)response);
			अवरोध;
		हाल PQI_RESPONSE_IU_AIO_PATH_DISABLED:
			pqi_aio_path_disabled(io_request);
			io_request->status = -EAGAIN;
			अवरोध;
		हाल PQI_RESPONSE_IU_RAID_PATH_IO_ERROR:
		हाल PQI_RESPONSE_IU_AIO_PATH_IO_ERROR:
			io_request->error_info = ctrl_info->error_buffer +
				(get_unaligned_le16(&response->error_index) *
				PQI_ERROR_BUFFER_ELEMENT_LENGTH);
			pqi_process_io_error(response->header.iu_type, io_request);
			अवरोध;
		शेष:
			pqi_invalid_response(ctrl_info);
			dev_err(&ctrl_info->pci_dev->dev,
				"unexpected IU type: 0x%x: producer index: %u  consumer index: %u\n",
				response->header.iu_type, oq_pi, oq_ci);
			वापस -1;
		पूर्ण

		io_request->io_complete_callback(io_request, io_request->context);

		/*
		 * Note that the I/O request काष्ठाure CANNOT BE TOUCHED after
		 * वापसing from the I/O completion callback!
		 */
		oq_ci = (oq_ci + 1) % ctrl_info->num_elements_per_oq;
	पूर्ण

	अगर (num_responses) अणु
		queue_group->oq_ci_copy = oq_ci;
		ग_लिखोl(oq_ci, queue_group->oq_ci);
	पूर्ण

	वापस num_responses;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pqi_num_elements_मुक्त(अचिन्हित पूर्णांक pi,
	अचिन्हित पूर्णांक ci, अचिन्हित पूर्णांक elements_in_queue)
अणु
	अचिन्हित पूर्णांक num_elements_used;

	अगर (pi >= ci)
		num_elements_used = pi - ci;
	अन्यथा
		num_elements_used = elements_in_queue - ci + pi;

	वापस elements_in_queue - num_elements_used - 1;
पूर्ण

अटल व्योम pqi_send_event_ack(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_event_acknowledge_request *iu, माप_प्रकार iu_length)
अणु
	pqi_index_t iq_pi;
	pqi_index_t iq_ci;
	अचिन्हित दीर्घ flags;
	व्योम *next_element;
	काष्ठा pqi_queue_group *queue_group;

	queue_group = &ctrl_info->queue_groups[PQI_DEFAULT_QUEUE_GROUP];
	put_unaligned_le16(queue_group->oq_id, &iu->header.response_queue_id);

	जबतक (1) अणु
		spin_lock_irqsave(&queue_group->submit_lock[RAID_PATH], flags);

		iq_pi = queue_group->iq_pi_copy[RAID_PATH];
		iq_ci = पढ़ोl(queue_group->iq_ci[RAID_PATH]);

		अगर (pqi_num_elements_मुक्त(iq_pi, iq_ci,
			ctrl_info->num_elements_per_iq))
			अवरोध;

		spin_unlock_irqrestore(
			&queue_group->submit_lock[RAID_PATH], flags);

		अगर (pqi_ctrl_offline(ctrl_info))
			वापस;
	पूर्ण

	next_element = queue_group->iq_element_array[RAID_PATH] +
		(iq_pi * PQI_OPERATIONAL_IQ_ELEMENT_LENGTH);

	स_नकल(next_element, iu, iu_length);

	iq_pi = (iq_pi + 1) % ctrl_info->num_elements_per_iq;
	queue_group->iq_pi_copy[RAID_PATH] = iq_pi;

	/*
	 * This ग_लिखो notअगरies the controller that an IU is available to be
	 * processed.
	 */
	ग_लिखोl(iq_pi, queue_group->iq_pi[RAID_PATH]);

	spin_unlock_irqrestore(&queue_group->submit_lock[RAID_PATH], flags);
पूर्ण

अटल व्योम pqi_acknowledge_event(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_event *event)
अणु
	काष्ठा pqi_event_acknowledge_request request;

	स_रखो(&request, 0, माप(request));

	request.header.iu_type = PQI_REQUEST_IU_ACKNOWLEDGE_VENDOR_EVENT;
	put_unaligned_le16(माप(request) - PQI_REQUEST_HEADER_LENGTH,
		&request.header.iu_length);
	request.event_type = event->event_type;
	put_unaligned_le16(event->event_id, &request.event_id);
	put_unaligned_le32(event->additional_event_id, &request.additional_event_id);

	pqi_send_event_ack(ctrl_info, &request, माप(request));
पूर्ण

#घोषणा PQI_SOFT_RESET_STATUS_TIMEOUT_SECS		30
#घोषणा PQI_SOFT_RESET_STATUS_POLL_INTERVAL_SECS	1

अटल क्रमागत pqi_soft_reset_status pqi_poll_क्रम_soft_reset_status(
	काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	u8 status;
	अचिन्हित दीर्घ समयout;

	समयout = (PQI_SOFT_RESET_STATUS_TIMEOUT_SECS * PQI_HZ) + jअगरfies;

	जबतक (1) अणु
		status = pqi_पढ़ो_soft_reset_status(ctrl_info);
		अगर (status & PQI_SOFT_RESET_INITIATE)
			वापस RESET_INITIATE_DRIVER;

		अगर (status & PQI_SOFT_RESET_ABORT)
			वापस RESET_ABORT;

		अगर (!sis_is_firmware_running(ctrl_info))
			वापस RESET_NORESPONSE;

		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_warn(&ctrl_info->pci_dev->dev,
				"timed out waiting for soft reset status\n");
			वापस RESET_TIMEDOUT;
		पूर्ण

		ssleep(PQI_SOFT_RESET_STATUS_POLL_INTERVAL_SECS);
	पूर्ण
पूर्ण

अटल व्योम pqi_process_soft_reset(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक delay_secs;
	क्रमागत pqi_soft_reset_status reset_status;

	अगर (ctrl_info->soft_reset_handshake_supported)
		reset_status = pqi_poll_क्रम_soft_reset_status(ctrl_info);
	अन्यथा
		reset_status = RESET_INITIATE_FIRMWARE;

	delay_secs = PQI_POST_RESET_DELAY_SECS;

	चयन (reset_status) अणु
	हाल RESET_TIMEDOUT:
		delay_secs = PQI_POST_OFA_RESET_DELAY_UPON_TIMEOUT_SECS;
		fallthrough;
	हाल RESET_INITIATE_DRIVER:
		dev_info(&ctrl_info->pci_dev->dev,
				"Online Firmware Activation: resetting controller\n");
		sis_soft_reset(ctrl_info);
		fallthrough;
	हाल RESET_INITIATE_FIRMWARE:
		ctrl_info->pqi_mode_enabled = false;
		pqi_save_ctrl_mode(ctrl_info, SIS_MODE);
		rc = pqi_ofa_ctrl_restart(ctrl_info, delay_secs);
		pqi_ofa_मुक्त_host_buffer(ctrl_info);
		pqi_ctrl_ofa_करोne(ctrl_info);
		dev_info(&ctrl_info->pci_dev->dev,
				"Online Firmware Activation: %s\n",
				rc == 0 ? "SUCCESS" : "FAILED");
		अवरोध;
	हाल RESET_ABORT:
		dev_info(&ctrl_info->pci_dev->dev,
				"Online Firmware Activation ABORTED\n");
		अगर (ctrl_info->soft_reset_handshake_supported)
			pqi_clear_soft_reset_status(ctrl_info);
		pqi_ofa_मुक्त_host_buffer(ctrl_info);
		pqi_ctrl_ofa_करोne(ctrl_info);
		pqi_ofa_ctrl_unquiesce(ctrl_info);
		अवरोध;
	हाल RESET_NORESPONSE:
		fallthrough;
	शेष:
		dev_err(&ctrl_info->pci_dev->dev,
			"unexpected Online Firmware Activation reset status: 0x%x\n",
			reset_status);
		pqi_ofa_मुक्त_host_buffer(ctrl_info);
		pqi_ctrl_ofa_करोne(ctrl_info);
		pqi_ofa_ctrl_unquiesce(ctrl_info);
		pqi_take_ctrl_offline(ctrl_info);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pqi_ofa_memory_alloc_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = container_of(work, काष्ठा pqi_ctrl_info, ofa_memory_alloc_work);

	pqi_ctrl_ofa_start(ctrl_info);
	pqi_ofa_setup_host_buffer(ctrl_info);
	pqi_ofa_host_memory_update(ctrl_info);
पूर्ण

अटल व्योम pqi_ofa_quiesce_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा pqi_event *event;

	ctrl_info = container_of(work, काष्ठा pqi_ctrl_info, ofa_quiesce_work);

	event = &ctrl_info->events[pqi_event_type_to_event_index(PQI_EVENT_TYPE_OFA)];

	pqi_ofa_ctrl_quiesce(ctrl_info);
	pqi_acknowledge_event(ctrl_info, event);
	pqi_process_soft_reset(ctrl_info);
पूर्ण

अटल bool pqi_ofa_process_event(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_event *event)
अणु
	bool ack_event;

	ack_event = true;

	चयन (event->event_id) अणु
	हाल PQI_EVENT_OFA_MEMORY_ALLOCATION:
		dev_info(&ctrl_info->pci_dev->dev,
			"received Online Firmware Activation memory allocation request\n");
		schedule_work(&ctrl_info->ofa_memory_alloc_work);
		अवरोध;
	हाल PQI_EVENT_OFA_QUIESCE:
		dev_info(&ctrl_info->pci_dev->dev,
			"received Online Firmware Activation quiesce request\n");
		schedule_work(&ctrl_info->ofa_quiesce_work);
		ack_event = false;
		अवरोध;
	हाल PQI_EVENT_OFA_CANCELED:
		dev_info(&ctrl_info->pci_dev->dev,
			"received Online Firmware Activation cancel request: reason: %u\n",
			ctrl_info->ofa_cancel_reason);
		pqi_ofa_मुक्त_host_buffer(ctrl_info);
		pqi_ctrl_ofa_करोne(ctrl_info);
		अवरोध;
	शेष:
		dev_err(&ctrl_info->pci_dev->dev,
			"received unknown Online Firmware Activation request: event ID: %u\n",
			event->event_id);
		अवरोध;
	पूर्ण

	वापस ack_event;
पूर्ण

अटल व्योम pqi_event_worker(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित पूर्णांक i;
	bool rescan_needed;
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा pqi_event *event;
	bool ack_event;

	ctrl_info = container_of(work, काष्ठा pqi_ctrl_info, event_work);

	pqi_ctrl_busy(ctrl_info);
	pqi_रुको_अगर_ctrl_blocked(ctrl_info);
	अगर (pqi_ctrl_offline(ctrl_info))
		जाओ out;

	rescan_needed = false;
	event = ctrl_info->events;
	क्रम (i = 0; i < PQI_NUM_SUPPORTED_EVENTS; i++) अणु
		अगर (event->pending) अणु
			event->pending = false;
			अगर (event->event_type == PQI_EVENT_TYPE_OFA) अणु
				ack_event = pqi_ofa_process_event(ctrl_info, event);
			पूर्ण अन्यथा अणु
				ack_event = true;
				rescan_needed = true;
			पूर्ण
			अगर (ack_event)
				pqi_acknowledge_event(ctrl_info, event);
		पूर्ण
		event++;
	पूर्ण

	अगर (rescan_needed)
		pqi_schedule_rescan_worker_delayed(ctrl_info);

out:
	pqi_ctrl_unbusy(ctrl_info);
पूर्ण

#घोषणा PQI_HEARTBEAT_TIMER_INTERVAL	(10 * PQI_HZ)

अटल व्योम pqi_heartbeat_समयr_handler(काष्ठा समयr_list *t)
अणु
	पूर्णांक num_पूर्णांकerrupts;
	u32 heartbeat_count;
	काष्ठा pqi_ctrl_info *ctrl_info = from_समयr(ctrl_info, t, heartbeat_समयr);

	pqi_check_ctrl_health(ctrl_info);
	अगर (pqi_ctrl_offline(ctrl_info))
		वापस;

	num_पूर्णांकerrupts = atomic_पढ़ो(&ctrl_info->num_पूर्णांकerrupts);
	heartbeat_count = pqi_पढ़ो_heartbeat_counter(ctrl_info);

	अगर (num_पूर्णांकerrupts == ctrl_info->previous_num_पूर्णांकerrupts) अणु
		अगर (heartbeat_count == ctrl_info->previous_heartbeat_count) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"no heartbeat detected - last heartbeat count: %u\n",
				heartbeat_count);
			pqi_take_ctrl_offline(ctrl_info);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctrl_info->previous_num_पूर्णांकerrupts = num_पूर्णांकerrupts;
	पूर्ण

	ctrl_info->previous_heartbeat_count = heartbeat_count;
	mod_समयr(&ctrl_info->heartbeat_समयr,
		jअगरfies + PQI_HEARTBEAT_TIMER_INTERVAL);
पूर्ण

अटल व्योम pqi_start_heartbeat_समयr(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अगर (!ctrl_info->heartbeat_counter)
		वापस;

	ctrl_info->previous_num_पूर्णांकerrupts =
		atomic_पढ़ो(&ctrl_info->num_पूर्णांकerrupts);
	ctrl_info->previous_heartbeat_count =
		pqi_पढ़ो_heartbeat_counter(ctrl_info);

	ctrl_info->heartbeat_समयr.expires =
		jअगरfies + PQI_HEARTBEAT_TIMER_INTERVAL;
	add_समयr(&ctrl_info->heartbeat_समयr);
पूर्ण

अटल अंतरभूत व्योम pqi_stop_heartbeat_समयr(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	del_समयr_sync(&ctrl_info->heartbeat_समयr);
पूर्ण

अटल व्योम pqi_ofa_capture_event_payload(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_event *event, काष्ठा pqi_event_response *response)
अणु
	चयन (event->event_id) अणु
	हाल PQI_EVENT_OFA_MEMORY_ALLOCATION:
		ctrl_info->ofa_bytes_requested =
			get_unaligned_le32(&response->data.ofa_memory_allocation.bytes_requested);
		अवरोध;
	हाल PQI_EVENT_OFA_CANCELED:
		ctrl_info->ofa_cancel_reason =
			get_unaligned_le16(&response->data.ofa_cancelled.reason);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pqi_process_event_पूर्णांकr(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक num_events;
	pqi_index_t oq_pi;
	pqi_index_t oq_ci;
	काष्ठा pqi_event_queue *event_queue;
	काष्ठा pqi_event_response *response;
	काष्ठा pqi_event *event;
	पूर्णांक event_index;

	event_queue = &ctrl_info->event_queue;
	num_events = 0;
	oq_ci = event_queue->oq_ci_copy;

	जबतक (1) अणु
		oq_pi = पढ़ोl(event_queue->oq_pi);
		अगर (oq_pi >= PQI_NUM_EVENT_QUEUE_ELEMENTS) अणु
			pqi_invalid_response(ctrl_info);
			dev_err(&ctrl_info->pci_dev->dev,
				"event interrupt: producer index (%u) out of range (0-%u): consumer index: %u\n",
				oq_pi, PQI_NUM_EVENT_QUEUE_ELEMENTS - 1, oq_ci);
			वापस -1;
		पूर्ण

		अगर (oq_pi == oq_ci)
			अवरोध;

		num_events++;
		response = event_queue->oq_element_array + (oq_ci * PQI_EVENT_OQ_ELEMENT_LENGTH);

		event_index = pqi_event_type_to_event_index(response->event_type);

		अगर (event_index >= 0 && response->request_acknowledge) अणु
			event = &ctrl_info->events[event_index];
			event->pending = true;
			event->event_type = response->event_type;
			event->event_id = get_unaligned_le16(&response->event_id);
			event->additional_event_id =
				get_unaligned_le32(&response->additional_event_id);
			अगर (event->event_type == PQI_EVENT_TYPE_OFA)
				pqi_ofa_capture_event_payload(ctrl_info, event, response);
		पूर्ण

		oq_ci = (oq_ci + 1) % PQI_NUM_EVENT_QUEUE_ELEMENTS;
	पूर्ण

	अगर (num_events) अणु
		event_queue->oq_ci_copy = oq_ci;
		ग_लिखोl(oq_ci, event_queue->oq_ci);
		schedule_work(&ctrl_info->event_work);
	पूर्ण

	वापस num_events;
पूर्ण

#घोषणा PQI_LEGACY_INTX_MASK	0x1

अटल अंतरभूत व्योम pqi_configure_legacy_पूर्णांकx(काष्ठा pqi_ctrl_info *ctrl_info, bool enable_पूर्णांकx)
अणु
	u32 पूर्णांकx_mask;
	काष्ठा pqi_device_रेजिस्टरs __iomem *pqi_रेजिस्टरs;
	अस्थिर व्योम __iomem *रेजिस्टर_addr;

	pqi_रेजिस्टरs = ctrl_info->pqi_रेजिस्टरs;

	अगर (enable_पूर्णांकx)
		रेजिस्टर_addr = &pqi_रेजिस्टरs->legacy_पूर्णांकx_mask_clear;
	अन्यथा
		रेजिस्टर_addr = &pqi_रेजिस्टरs->legacy_पूर्णांकx_mask_set;

	पूर्णांकx_mask = पढ़ोl(रेजिस्टर_addr);
	पूर्णांकx_mask |= PQI_LEGACY_INTX_MASK;
	ग_लिखोl(पूर्णांकx_mask, रेजिस्टर_addr);
पूर्ण

अटल व्योम pqi_change_irq_mode(काष्ठा pqi_ctrl_info *ctrl_info,
	क्रमागत pqi_irq_mode new_mode)
अणु
	चयन (ctrl_info->irq_mode) अणु
	हाल IRQ_MODE_MSIX:
		चयन (new_mode) अणु
		हाल IRQ_MODE_MSIX:
			अवरोध;
		हाल IRQ_MODE_INTX:
			pqi_configure_legacy_पूर्णांकx(ctrl_info, true);
			sis_enable_पूर्णांकx(ctrl_info);
			अवरोध;
		हाल IRQ_MODE_NONE:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IRQ_MODE_INTX:
		चयन (new_mode) अणु
		हाल IRQ_MODE_MSIX:
			pqi_configure_legacy_पूर्णांकx(ctrl_info, false);
			sis_enable_msix(ctrl_info);
			अवरोध;
		हाल IRQ_MODE_INTX:
			अवरोध;
		हाल IRQ_MODE_NONE:
			pqi_configure_legacy_पूर्णांकx(ctrl_info, false);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IRQ_MODE_NONE:
		चयन (new_mode) अणु
		हाल IRQ_MODE_MSIX:
			sis_enable_msix(ctrl_info);
			अवरोध;
		हाल IRQ_MODE_INTX:
			pqi_configure_legacy_पूर्णांकx(ctrl_info, true);
			sis_enable_पूर्णांकx(ctrl_info);
			अवरोध;
		हाल IRQ_MODE_NONE:
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	ctrl_info->irq_mode = new_mode;
पूर्ण

#घोषणा PQI_LEGACY_INTX_PENDING		0x1

अटल अंतरभूत bool pqi_is_valid_irq(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	bool valid_irq;
	u32 पूर्णांकx_status;

	चयन (ctrl_info->irq_mode) अणु
	हाल IRQ_MODE_MSIX:
		valid_irq = true;
		अवरोध;
	हाल IRQ_MODE_INTX:
		पूर्णांकx_status = पढ़ोl(&ctrl_info->pqi_रेजिस्टरs->legacy_पूर्णांकx_status);
		अगर (पूर्णांकx_status & PQI_LEGACY_INTX_PENDING)
			valid_irq = true;
		अन्यथा
			valid_irq = false;
		अवरोध;
	हाल IRQ_MODE_NONE:
	शेष:
		valid_irq = false;
		अवरोध;
	पूर्ण

	वापस valid_irq;
पूर्ण

अटल irqवापस_t pqi_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा pqi_queue_group *queue_group;
	पूर्णांक num_io_responses_handled;
	पूर्णांक num_events_handled;

	queue_group = data;
	ctrl_info = queue_group->ctrl_info;

	अगर (!pqi_is_valid_irq(ctrl_info))
		वापस IRQ_NONE;

	num_io_responses_handled = pqi_process_io_पूर्णांकr(ctrl_info, queue_group);
	अगर (num_io_responses_handled < 0)
		जाओ out;

	अगर (irq == ctrl_info->event_irq) अणु
		num_events_handled = pqi_process_event_पूर्णांकr(ctrl_info);
		अगर (num_events_handled < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		num_events_handled = 0;
	पूर्ण

	अगर (num_io_responses_handled + num_events_handled > 0)
		atomic_inc(&ctrl_info->num_पूर्णांकerrupts);

	pqi_start_io(ctrl_info, queue_group, RAID_PATH, शून्य);
	pqi_start_io(ctrl_info, queue_group, AIO_PATH, शून्य);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pqi_request_irqs(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	काष्ठा pci_dev *pci_dev = ctrl_info->pci_dev;
	पूर्णांक i;
	पूर्णांक rc;

	ctrl_info->event_irq = pci_irq_vector(pci_dev, 0);

	क्रम (i = 0; i < ctrl_info->num_msix_vectors_enabled; i++) अणु
		rc = request_irq(pci_irq_vector(pci_dev, i), pqi_irq_handler, 0,
			DRIVER_NAME_SHORT, &ctrl_info->queue_groups[i]);
		अगर (rc) अणु
			dev_err(&pci_dev->dev,
				"irq %u init failed with error %d\n",
				pci_irq_vector(pci_dev, i), rc);
			वापस rc;
		पूर्ण
		ctrl_info->num_msix_vectors_initialized++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pqi_मुक्त_irqs(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ctrl_info->num_msix_vectors_initialized; i++)
		मुक्त_irq(pci_irq_vector(ctrl_info->pci_dev, i),
			&ctrl_info->queue_groups[i]);

	ctrl_info->num_msix_vectors_initialized = 0;
पूर्ण

अटल पूर्णांक pqi_enable_msix_पूर्णांकerrupts(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक num_vectors_enabled;

	num_vectors_enabled = pci_alloc_irq_vectors(ctrl_info->pci_dev,
			PQI_MIN_MSIX_VECTORS, ctrl_info->num_queue_groups,
			PCI_IRQ_MSIX | PCI_IRQ_AFFINITY);
	अगर (num_vectors_enabled < 0) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"MSI-X init failed with error %d\n",
			num_vectors_enabled);
		वापस num_vectors_enabled;
	पूर्ण

	ctrl_info->num_msix_vectors_enabled = num_vectors_enabled;
	ctrl_info->irq_mode = IRQ_MODE_MSIX;
	वापस 0;
पूर्ण

अटल व्योम pqi_disable_msix_पूर्णांकerrupts(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अगर (ctrl_info->num_msix_vectors_enabled) अणु
		pci_मुक्त_irq_vectors(ctrl_info->pci_dev);
		ctrl_info->num_msix_vectors_enabled = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक pqi_alloc_operational_queues(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अचिन्हित पूर्णांक i;
	माप_प्रकार alloc_length;
	माप_प्रकार element_array_length_per_iq;
	माप_प्रकार element_array_length_per_oq;
	व्योम *element_array;
	व्योम __iomem *next_queue_index;
	व्योम *aligned_poपूर्णांकer;
	अचिन्हित पूर्णांक num_inbound_queues;
	अचिन्हित पूर्णांक num_outbound_queues;
	अचिन्हित पूर्णांक num_queue_indexes;
	काष्ठा pqi_queue_group *queue_group;

	element_array_length_per_iq =
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH *
		ctrl_info->num_elements_per_iq;
	element_array_length_per_oq =
		PQI_OPERATIONAL_OQ_ELEMENT_LENGTH *
		ctrl_info->num_elements_per_oq;
	num_inbound_queues = ctrl_info->num_queue_groups * 2;
	num_outbound_queues = ctrl_info->num_queue_groups;
	num_queue_indexes = (ctrl_info->num_queue_groups * 3) + 1;

	aligned_poपूर्णांकer = शून्य;

	क्रम (i = 0; i < num_inbound_queues; i++) अणु
		aligned_poपूर्णांकer = PTR_ALIGN(aligned_poपूर्णांकer,
			PQI_QUEUE_ELEMENT_ARRAY_ALIGNMENT);
		aligned_poपूर्णांकer += element_array_length_per_iq;
	पूर्ण

	क्रम (i = 0; i < num_outbound_queues; i++) अणु
		aligned_poपूर्णांकer = PTR_ALIGN(aligned_poपूर्णांकer,
			PQI_QUEUE_ELEMENT_ARRAY_ALIGNMENT);
		aligned_poपूर्णांकer += element_array_length_per_oq;
	पूर्ण

	aligned_poपूर्णांकer = PTR_ALIGN(aligned_poपूर्णांकer,
		PQI_QUEUE_ELEMENT_ARRAY_ALIGNMENT);
	aligned_poपूर्णांकer += PQI_NUM_EVENT_QUEUE_ELEMENTS *
		PQI_EVENT_OQ_ELEMENT_LENGTH;

	क्रम (i = 0; i < num_queue_indexes; i++) अणु
		aligned_poपूर्णांकer = PTR_ALIGN(aligned_poपूर्णांकer,
			PQI_OPERATIONAL_INDEX_ALIGNMENT);
		aligned_poपूर्णांकer += माप(pqi_index_t);
	पूर्ण

	alloc_length = (माप_प्रकार)aligned_poपूर्णांकer +
		PQI_QUEUE_ELEMENT_ARRAY_ALIGNMENT;

	alloc_length += PQI_EXTRA_SGL_MEMORY;

	ctrl_info->queue_memory_base =
		dma_alloc_coherent(&ctrl_info->pci_dev->dev, alloc_length,
				   &ctrl_info->queue_memory_base_dma_handle,
				   GFP_KERNEL);

	अगर (!ctrl_info->queue_memory_base)
		वापस -ENOMEM;

	ctrl_info->queue_memory_length = alloc_length;

	element_array = PTR_ALIGN(ctrl_info->queue_memory_base,
		PQI_QUEUE_ELEMENT_ARRAY_ALIGNMENT);

	क्रम (i = 0; i < ctrl_info->num_queue_groups; i++) अणु
		queue_group = &ctrl_info->queue_groups[i];
		queue_group->iq_element_array[RAID_PATH] = element_array;
		queue_group->iq_element_array_bus_addr[RAID_PATH] =
			ctrl_info->queue_memory_base_dma_handle +
				(element_array - ctrl_info->queue_memory_base);
		element_array += element_array_length_per_iq;
		element_array = PTR_ALIGN(element_array,
			PQI_QUEUE_ELEMENT_ARRAY_ALIGNMENT);
		queue_group->iq_element_array[AIO_PATH] = element_array;
		queue_group->iq_element_array_bus_addr[AIO_PATH] =
			ctrl_info->queue_memory_base_dma_handle +
			(element_array - ctrl_info->queue_memory_base);
		element_array += element_array_length_per_iq;
		element_array = PTR_ALIGN(element_array,
			PQI_QUEUE_ELEMENT_ARRAY_ALIGNMENT);
	पूर्ण

	क्रम (i = 0; i < ctrl_info->num_queue_groups; i++) अणु
		queue_group = &ctrl_info->queue_groups[i];
		queue_group->oq_element_array = element_array;
		queue_group->oq_element_array_bus_addr =
			ctrl_info->queue_memory_base_dma_handle +
			(element_array - ctrl_info->queue_memory_base);
		element_array += element_array_length_per_oq;
		element_array = PTR_ALIGN(element_array,
			PQI_QUEUE_ELEMENT_ARRAY_ALIGNMENT);
	पूर्ण

	ctrl_info->event_queue.oq_element_array = element_array;
	ctrl_info->event_queue.oq_element_array_bus_addr =
		ctrl_info->queue_memory_base_dma_handle +
		(element_array - ctrl_info->queue_memory_base);
	element_array += PQI_NUM_EVENT_QUEUE_ELEMENTS *
		PQI_EVENT_OQ_ELEMENT_LENGTH;

	next_queue_index = (व्योम __iomem *)PTR_ALIGN(element_array,
		PQI_OPERATIONAL_INDEX_ALIGNMENT);

	क्रम (i = 0; i < ctrl_info->num_queue_groups; i++) अणु
		queue_group = &ctrl_info->queue_groups[i];
		queue_group->iq_ci[RAID_PATH] = next_queue_index;
		queue_group->iq_ci_bus_addr[RAID_PATH] =
			ctrl_info->queue_memory_base_dma_handle +
			(next_queue_index -
			(व्योम __iomem *)ctrl_info->queue_memory_base);
		next_queue_index += माप(pqi_index_t);
		next_queue_index = PTR_ALIGN(next_queue_index,
			PQI_OPERATIONAL_INDEX_ALIGNMENT);
		queue_group->iq_ci[AIO_PATH] = next_queue_index;
		queue_group->iq_ci_bus_addr[AIO_PATH] =
			ctrl_info->queue_memory_base_dma_handle +
			(next_queue_index -
			(व्योम __iomem *)ctrl_info->queue_memory_base);
		next_queue_index += माप(pqi_index_t);
		next_queue_index = PTR_ALIGN(next_queue_index,
			PQI_OPERATIONAL_INDEX_ALIGNMENT);
		queue_group->oq_pi = next_queue_index;
		queue_group->oq_pi_bus_addr =
			ctrl_info->queue_memory_base_dma_handle +
			(next_queue_index -
			(व्योम __iomem *)ctrl_info->queue_memory_base);
		next_queue_index += माप(pqi_index_t);
		next_queue_index = PTR_ALIGN(next_queue_index,
			PQI_OPERATIONAL_INDEX_ALIGNMENT);
	पूर्ण

	ctrl_info->event_queue.oq_pi = next_queue_index;
	ctrl_info->event_queue.oq_pi_bus_addr =
		ctrl_info->queue_memory_base_dma_handle +
		(next_queue_index -
		(व्योम __iomem *)ctrl_info->queue_memory_base);

	वापस 0;
पूर्ण

अटल व्योम pqi_init_operational_queues(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अचिन्हित पूर्णांक i;
	u16 next_iq_id = PQI_MIN_OPERATIONAL_QUEUE_ID;
	u16 next_oq_id = PQI_MIN_OPERATIONAL_QUEUE_ID;

	/*
	 * Initialize the backpoपूर्णांकers to the controller काष्ठाure in
	 * each operational queue group काष्ठाure.
	 */
	क्रम (i = 0; i < ctrl_info->num_queue_groups; i++)
		ctrl_info->queue_groups[i].ctrl_info = ctrl_info;

	/*
	 * Assign IDs to all operational queues.  Note that the IDs
	 * asचिन्हित to operational IQs are independent of the IDs
	 * asचिन्हित to operational OQs.
	 */
	ctrl_info->event_queue.oq_id = next_oq_id++;
	क्रम (i = 0; i < ctrl_info->num_queue_groups; i++) अणु
		ctrl_info->queue_groups[i].iq_id[RAID_PATH] = next_iq_id++;
		ctrl_info->queue_groups[i].iq_id[AIO_PATH] = next_iq_id++;
		ctrl_info->queue_groups[i].oq_id = next_oq_id++;
	पूर्ण

	/*
	 * Assign MSI-X table entry indexes to all queues.  Note that the
	 * पूर्णांकerrupt क्रम the event queue is shared with the first queue group.
	 */
	ctrl_info->event_queue.पूर्णांक_msg_num = 0;
	क्रम (i = 0; i < ctrl_info->num_queue_groups; i++)
		ctrl_info->queue_groups[i].पूर्णांक_msg_num = i;

	क्रम (i = 0; i < ctrl_info->num_queue_groups; i++) अणु
		spin_lock_init(&ctrl_info->queue_groups[i].submit_lock[0]);
		spin_lock_init(&ctrl_info->queue_groups[i].submit_lock[1]);
		INIT_LIST_HEAD(&ctrl_info->queue_groups[i].request_list[0]);
		INIT_LIST_HEAD(&ctrl_info->queue_groups[i].request_list[1]);
	पूर्ण
पूर्ण

अटल पूर्णांक pqi_alloc_admin_queues(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	माप_प्रकार alloc_length;
	काष्ठा pqi_admin_queues_aligned *admin_queues_aligned;
	काष्ठा pqi_admin_queues *admin_queues;

	alloc_length = माप(काष्ठा pqi_admin_queues_aligned) +
		PQI_QUEUE_ELEMENT_ARRAY_ALIGNMENT;

	ctrl_info->admin_queue_memory_base =
		dma_alloc_coherent(&ctrl_info->pci_dev->dev, alloc_length,
				   &ctrl_info->admin_queue_memory_base_dma_handle,
				   GFP_KERNEL);

	अगर (!ctrl_info->admin_queue_memory_base)
		वापस -ENOMEM;

	ctrl_info->admin_queue_memory_length = alloc_length;

	admin_queues = &ctrl_info->admin_queues;
	admin_queues_aligned = PTR_ALIGN(ctrl_info->admin_queue_memory_base,
		PQI_QUEUE_ELEMENT_ARRAY_ALIGNMENT);
	admin_queues->iq_element_array =
		&admin_queues_aligned->iq_element_array;
	admin_queues->oq_element_array =
		&admin_queues_aligned->oq_element_array;
	admin_queues->iq_ci =
		(pqi_index_t __iomem *)&admin_queues_aligned->iq_ci;
	admin_queues->oq_pi =
		(pqi_index_t __iomem *)&admin_queues_aligned->oq_pi;

	admin_queues->iq_element_array_bus_addr =
		ctrl_info->admin_queue_memory_base_dma_handle +
		(admin_queues->iq_element_array -
		ctrl_info->admin_queue_memory_base);
	admin_queues->oq_element_array_bus_addr =
		ctrl_info->admin_queue_memory_base_dma_handle +
		(admin_queues->oq_element_array -
		ctrl_info->admin_queue_memory_base);
	admin_queues->iq_ci_bus_addr =
		ctrl_info->admin_queue_memory_base_dma_handle +
		((व्योम __iomem *)admin_queues->iq_ci -
		(व्योम __iomem *)ctrl_info->admin_queue_memory_base);
	admin_queues->oq_pi_bus_addr =
		ctrl_info->admin_queue_memory_base_dma_handle +
		((व्योम __iomem *)admin_queues->oq_pi -
		(व्योम __iomem *)ctrl_info->admin_queue_memory_base);

	वापस 0;
पूर्ण

#घोषणा PQI_ADMIN_QUEUE_CREATE_TIMEOUT_JIFFIES		PQI_HZ
#घोषणा PQI_ADMIN_QUEUE_CREATE_POLL_INTERVAL_MSECS	1

अटल पूर्णांक pqi_create_admin_queues(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	काष्ठा pqi_device_रेजिस्टरs __iomem *pqi_रेजिस्टरs;
	काष्ठा pqi_admin_queues *admin_queues;
	अचिन्हित दीर्घ समयout;
	u8 status;
	u32 reg;

	pqi_रेजिस्टरs = ctrl_info->pqi_रेजिस्टरs;
	admin_queues = &ctrl_info->admin_queues;

	ग_लिखोq((u64)admin_queues->iq_element_array_bus_addr,
		&pqi_रेजिस्टरs->admin_iq_element_array_addr);
	ग_लिखोq((u64)admin_queues->oq_element_array_bus_addr,
		&pqi_रेजिस्टरs->admin_oq_element_array_addr);
	ग_लिखोq((u64)admin_queues->iq_ci_bus_addr,
		&pqi_रेजिस्टरs->admin_iq_ci_addr);
	ग_लिखोq((u64)admin_queues->oq_pi_bus_addr,
		&pqi_रेजिस्टरs->admin_oq_pi_addr);

	reg = PQI_ADMIN_IQ_NUM_ELEMENTS |
		(PQI_ADMIN_OQ_NUM_ELEMENTS << 8) |
		(admin_queues->पूर्णांक_msg_num << 16);
	ग_लिखोl(reg, &pqi_रेजिस्टरs->admin_iq_num_elements);

	ग_लिखोl(PQI_CREATE_ADMIN_QUEUE_PAIR,
		&pqi_रेजिस्टरs->function_and_status_code);

	समयout = PQI_ADMIN_QUEUE_CREATE_TIMEOUT_JIFFIES + jअगरfies;
	जबतक (1) अणु
		status = पढ़ोb(&pqi_रेजिस्टरs->function_and_status_code);
		अगर (status == PQI_STATUS_IDLE)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
		msleep(PQI_ADMIN_QUEUE_CREATE_POLL_INTERVAL_MSECS);
	पूर्ण

	/*
	 * The offset रेजिस्टरs are not initialized to the correct
	 * offsets until *after* the create admin queue pair command
	 * completes successfully.
	 */
	admin_queues->iq_pi = ctrl_info->iomem_base +
		PQI_DEVICE_REGISTERS_OFFSET +
		पढ़ोq(&pqi_रेजिस्टरs->admin_iq_pi_offset);
	admin_queues->oq_ci = ctrl_info->iomem_base +
		PQI_DEVICE_REGISTERS_OFFSET +
		पढ़ोq(&pqi_रेजिस्टरs->admin_oq_ci_offset);

	वापस 0;
पूर्ण

अटल व्योम pqi_submit_admin_request(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_general_admin_request *request)
अणु
	काष्ठा pqi_admin_queues *admin_queues;
	व्योम *next_element;
	pqi_index_t iq_pi;

	admin_queues = &ctrl_info->admin_queues;
	iq_pi = admin_queues->iq_pi_copy;

	next_element = admin_queues->iq_element_array +
		(iq_pi * PQI_ADMIN_IQ_ELEMENT_LENGTH);

	स_नकल(next_element, request, माप(*request));

	iq_pi = (iq_pi + 1) % PQI_ADMIN_IQ_NUM_ELEMENTS;
	admin_queues->iq_pi_copy = iq_pi;

	/*
	 * This ग_लिखो notअगरies the controller that an IU is available to be
	 * processed.
	 */
	ग_लिखोl(iq_pi, admin_queues->iq_pi);
पूर्ण

#घोषणा PQI_ADMIN_REQUEST_TIMEOUT_SECS	60

अटल पूर्णांक pqi_poll_क्रम_admin_response(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_general_admin_response *response)
अणु
	काष्ठा pqi_admin_queues *admin_queues;
	pqi_index_t oq_pi;
	pqi_index_t oq_ci;
	अचिन्हित दीर्घ समयout;

	admin_queues = &ctrl_info->admin_queues;
	oq_ci = admin_queues->oq_ci_copy;

	समयout = (PQI_ADMIN_REQUEST_TIMEOUT_SECS * PQI_HZ) + jअगरfies;

	जबतक (1) अणु
		oq_pi = पढ़ोl(admin_queues->oq_pi);
		अगर (oq_pi != oq_ci)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"timed out waiting for admin response\n");
			वापस -ETIMEDOUT;
		पूर्ण
		अगर (!sis_is_firmware_running(ctrl_info))
			वापस -ENXIO;
		usleep_range(1000, 2000);
	पूर्ण

	स_नकल(response, admin_queues->oq_element_array +
		(oq_ci * PQI_ADMIN_OQ_ELEMENT_LENGTH), माप(*response));

	oq_ci = (oq_ci + 1) % PQI_ADMIN_OQ_NUM_ELEMENTS;
	admin_queues->oq_ci_copy = oq_ci;
	ग_लिखोl(oq_ci, admin_queues->oq_ci);

	वापस 0;
पूर्ण

अटल व्योम pqi_start_io(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_queue_group *queue_group, क्रमागत pqi_io_path path,
	काष्ठा pqi_io_request *io_request)
अणु
	काष्ठा pqi_io_request *next;
	व्योम *next_element;
	pqi_index_t iq_pi;
	pqi_index_t iq_ci;
	माप_प्रकार iu_length;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक num_elements_needed;
	अचिन्हित पूर्णांक num_elements_to_end_of_queue;
	माप_प्रकार copy_count;
	काष्ठा pqi_iu_header *request;

	spin_lock_irqsave(&queue_group->submit_lock[path], flags);

	अगर (io_request) अणु
		io_request->queue_group = queue_group;
		list_add_tail(&io_request->request_list_entry,
			&queue_group->request_list[path]);
	पूर्ण

	iq_pi = queue_group->iq_pi_copy[path];

	list_क्रम_each_entry_safe(io_request, next,
		&queue_group->request_list[path], request_list_entry) अणु

		request = io_request->iu;

		iu_length = get_unaligned_le16(&request->iu_length) +
			PQI_REQUEST_HEADER_LENGTH;
		num_elements_needed =
			DIV_ROUND_UP(iu_length,
				PQI_OPERATIONAL_IQ_ELEMENT_LENGTH);

		iq_ci = पढ़ोl(queue_group->iq_ci[path]);

		अगर (num_elements_needed > pqi_num_elements_मुक्त(iq_pi, iq_ci,
			ctrl_info->num_elements_per_iq))
			अवरोध;

		put_unaligned_le16(queue_group->oq_id,
			&request->response_queue_id);

		next_element = queue_group->iq_element_array[path] +
			(iq_pi * PQI_OPERATIONAL_IQ_ELEMENT_LENGTH);

		num_elements_to_end_of_queue =
			ctrl_info->num_elements_per_iq - iq_pi;

		अगर (num_elements_needed <= num_elements_to_end_of_queue) अणु
			स_नकल(next_element, request, iu_length);
		पूर्ण अन्यथा अणु
			copy_count = num_elements_to_end_of_queue *
				PQI_OPERATIONAL_IQ_ELEMENT_LENGTH;
			स_नकल(next_element, request, copy_count);
			स_नकल(queue_group->iq_element_array[path],
				(u8 *)request + copy_count,
				iu_length - copy_count);
		पूर्ण

		iq_pi = (iq_pi + num_elements_needed) %
			ctrl_info->num_elements_per_iq;

		list_del(&io_request->request_list_entry);
	पूर्ण

	अगर (iq_pi != queue_group->iq_pi_copy[path]) अणु
		queue_group->iq_pi_copy[path] = iq_pi;
		/*
		 * This ग_लिखो notअगरies the controller that one or more IUs are
		 * available to be processed.
		 */
		ग_लिखोl(iq_pi, queue_group->iq_pi[path]);
	पूर्ण

	spin_unlock_irqrestore(&queue_group->submit_lock[path], flags);
पूर्ण

#घोषणा PQI_WAIT_FOR_COMPLETION_IO_TIMEOUT_SECS		10

अटल पूर्णांक pqi_रुको_क्रम_completion_io(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा completion *रुको)
अणु
	पूर्णांक rc;

	जबतक (1) अणु
		अगर (रुको_क्रम_completion_io_समयout(रुको,
			PQI_WAIT_FOR_COMPLETION_IO_TIMEOUT_SECS * PQI_HZ)) अणु
			rc = 0;
			अवरोध;
		पूर्ण

		pqi_check_ctrl_health(ctrl_info);
		अगर (pqi_ctrl_offline(ctrl_info)) अणु
			rc = -ENXIO;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम pqi_raid_synchronous_complete(काष्ठा pqi_io_request *io_request,
	व्योम *context)
अणु
	काष्ठा completion *रुकोing = context;

	complete(रुकोing);
पूर्ण

अटल पूर्णांक pqi_process_raid_io_error_synchronous(
	काष्ठा pqi_raid_error_info *error_info)
अणु
	पूर्णांक rc = -EIO;

	चयन (error_info->data_out_result) अणु
	हाल PQI_DATA_IN_OUT_GOOD:
		अगर (error_info->status == SAM_STAT_GOOD)
			rc = 0;
		अवरोध;
	हाल PQI_DATA_IN_OUT_UNDERFLOW:
		अगर (error_info->status == SAM_STAT_GOOD ||
			error_info->status == SAM_STAT_CHECK_CONDITION)
			rc = 0;
		अवरोध;
	हाल PQI_DATA_IN_OUT_ABORTED:
		rc = PQI_CMD_STATUS_ABORTED;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल अंतरभूत bool pqi_is_blockable_request(काष्ठा pqi_iu_header *request)
अणु
	वापस (request->driver_flags & PQI_DRIVER_NONBLOCKABLE_REQUEST) == 0;
पूर्ण

अटल पूर्णांक pqi_submit_raid_request_synchronous(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_iu_header *request, अचिन्हित पूर्णांक flags,
	काष्ठा pqi_raid_error_info *error_info)
अणु
	पूर्णांक rc = 0;
	काष्ठा pqi_io_request *io_request;
	माप_प्रकार iu_length;
	DECLARE_COMPLETION_ONSTACK(रुको);

	अगर (flags & PQI_SYNC_FLAGS_INTERRUPTABLE) अणु
		अगर (करोwn_पूर्णांकerruptible(&ctrl_info->sync_request_sem))
			वापस -ERESTARTSYS;
	पूर्ण अन्यथा अणु
		करोwn(&ctrl_info->sync_request_sem);
	पूर्ण

	pqi_ctrl_busy(ctrl_info);
	/*
	 * Wait क्रम other admin queue updates such as;
	 * config table changes, OFA memory updates, ...
	 */
	अगर (pqi_is_blockable_request(request))
		pqi_रुको_अगर_ctrl_blocked(ctrl_info);

	अगर (pqi_ctrl_offline(ctrl_info)) अणु
		rc = -ENXIO;
		जाओ out;
	पूर्ण

	io_request = pqi_alloc_io_request(ctrl_info);

	put_unaligned_le16(io_request->index,
		&(((काष्ठा pqi_raid_path_request *)request)->request_id));

	अगर (request->iu_type == PQI_REQUEST_IU_RAID_PATH_IO)
		((काष्ठा pqi_raid_path_request *)request)->error_index =
			((काष्ठा pqi_raid_path_request *)request)->request_id;

	iu_length = get_unaligned_le16(&request->iu_length) +
		PQI_REQUEST_HEADER_LENGTH;
	स_नकल(io_request->iu, request, iu_length);

	io_request->io_complete_callback = pqi_raid_synchronous_complete;
	io_request->context = &रुको;

	pqi_start_io(ctrl_info, &ctrl_info->queue_groups[PQI_DEFAULT_QUEUE_GROUP], RAID_PATH,
		io_request);

	pqi_रुको_क्रम_completion_io(ctrl_info, &रुको);

	अगर (error_info) अणु
		अगर (io_request->error_info)
			स_नकल(error_info, io_request->error_info, माप(*error_info));
		अन्यथा
			स_रखो(error_info, 0, माप(*error_info));
	पूर्ण अन्यथा अगर (rc == 0 && io_request->error_info) अणु
		rc = pqi_process_raid_io_error_synchronous(io_request->error_info);
	पूर्ण

	pqi_मुक्त_io_request(io_request);

out:
	pqi_ctrl_unbusy(ctrl_info);
	up(&ctrl_info->sync_request_sem);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_validate_admin_response(
	काष्ठा pqi_general_admin_response *response, u8 expected_function_code)
अणु
	अगर (response->header.iu_type != PQI_RESPONSE_IU_GENERAL_ADMIN)
		वापस -EINVAL;

	अगर (get_unaligned_le16(&response->header.iu_length) !=
		PQI_GENERAL_ADMIN_IU_LENGTH)
		वापस -EINVAL;

	अगर (response->function_code != expected_function_code)
		वापस -EINVAL;

	अगर (response->status != PQI_GENERAL_ADMIN_STATUS_SUCCESS)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_submit_admin_request_synchronous(
	काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_general_admin_request *request,
	काष्ठा pqi_general_admin_response *response)
अणु
	पूर्णांक rc;

	pqi_submit_admin_request(ctrl_info, request);

	rc = pqi_poll_क्रम_admin_response(ctrl_info, response);

	अगर (rc == 0)
		rc = pqi_validate_admin_response(response, request->function_code);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_report_device_capability(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	काष्ठा pqi_general_admin_request request;
	काष्ठा pqi_general_admin_response response;
	काष्ठा pqi_device_capability *capability;
	काष्ठा pqi_iu_layer_descriptor *sop_iu_layer_descriptor;

	capability = kदो_स्मृति(माप(*capability), GFP_KERNEL);
	अगर (!capability)
		वापस -ENOMEM;

	स_रखो(&request, 0, माप(request));

	request.header.iu_type = PQI_REQUEST_IU_GENERAL_ADMIN;
	put_unaligned_le16(PQI_GENERAL_ADMIN_IU_LENGTH,
		&request.header.iu_length);
	request.function_code =
		PQI_GENERAL_ADMIN_FUNCTION_REPORT_DEVICE_CAPABILITY;
	put_unaligned_le32(माप(*capability),
		&request.data.report_device_capability.buffer_length);

	rc = pqi_map_single(ctrl_info->pci_dev,
		&request.data.report_device_capability.sg_descriptor,
		capability, माप(*capability),
		DMA_FROM_DEVICE);
	अगर (rc)
		जाओ out;

	rc = pqi_submit_admin_request_synchronous(ctrl_info, &request, &response);

	pqi_pci_unmap(ctrl_info->pci_dev,
		&request.data.report_device_capability.sg_descriptor, 1,
		DMA_FROM_DEVICE);

	अगर (rc)
		जाओ out;

	अगर (response.status != PQI_GENERAL_ADMIN_STATUS_SUCCESS) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण

	ctrl_info->max_inbound_queues =
		get_unaligned_le16(&capability->max_inbound_queues);
	ctrl_info->max_elements_per_iq =
		get_unaligned_le16(&capability->max_elements_per_iq);
	ctrl_info->max_iq_element_length =
		get_unaligned_le16(&capability->max_iq_element_length)
		* 16;
	ctrl_info->max_outbound_queues =
		get_unaligned_le16(&capability->max_outbound_queues);
	ctrl_info->max_elements_per_oq =
		get_unaligned_le16(&capability->max_elements_per_oq);
	ctrl_info->max_oq_element_length =
		get_unaligned_le16(&capability->max_oq_element_length)
		* 16;

	sop_iu_layer_descriptor =
		&capability->iu_layer_descriptors[PQI_PROTOCOL_SOP];

	ctrl_info->max_inbound_iu_length_per_firmware =
		get_unaligned_le16(
			&sop_iu_layer_descriptor->max_inbound_iu_length);
	ctrl_info->inbound_spanning_supported =
		sop_iu_layer_descriptor->inbound_spanning_supported;
	ctrl_info->outbound_spanning_supported =
		sop_iu_layer_descriptor->outbound_spanning_supported;

out:
	kमुक्त(capability);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_validate_device_capability(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अगर (ctrl_info->max_iq_element_length <
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"max. inbound queue element length of %d is less than the required length of %d\n",
			ctrl_info->max_iq_element_length,
			PQI_OPERATIONAL_IQ_ELEMENT_LENGTH);
		वापस -EINVAL;
	पूर्ण

	अगर (ctrl_info->max_oq_element_length <
		PQI_OPERATIONAL_OQ_ELEMENT_LENGTH) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"max. outbound queue element length of %d is less than the required length of %d\n",
			ctrl_info->max_oq_element_length,
			PQI_OPERATIONAL_OQ_ELEMENT_LENGTH);
		वापस -EINVAL;
	पूर्ण

	अगर (ctrl_info->max_inbound_iu_length_per_firmware <
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"max. inbound IU length of %u is less than the min. required length of %d\n",
			ctrl_info->max_inbound_iu_length_per_firmware,
			PQI_OPERATIONAL_IQ_ELEMENT_LENGTH);
		वापस -EINVAL;
	पूर्ण

	अगर (!ctrl_info->inbound_spanning_supported) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"the controller does not support inbound spanning\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ctrl_info->outbound_spanning_supported) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"the controller supports outbound spanning but this driver does not\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_create_event_queue(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	काष्ठा pqi_event_queue *event_queue;
	काष्ठा pqi_general_admin_request request;
	काष्ठा pqi_general_admin_response response;

	event_queue = &ctrl_info->event_queue;

	/*
	 * Create OQ (Outbound Queue - device to host queue) to dedicate
	 * to events.
	 */
	स_रखो(&request, 0, माप(request));
	request.header.iu_type = PQI_REQUEST_IU_GENERAL_ADMIN;
	put_unaligned_le16(PQI_GENERAL_ADMIN_IU_LENGTH,
		&request.header.iu_length);
	request.function_code = PQI_GENERAL_ADMIN_FUNCTION_CREATE_OQ;
	put_unaligned_le16(event_queue->oq_id,
		&request.data.create_operational_oq.queue_id);
	put_unaligned_le64((u64)event_queue->oq_element_array_bus_addr,
		&request.data.create_operational_oq.element_array_addr);
	put_unaligned_le64((u64)event_queue->oq_pi_bus_addr,
		&request.data.create_operational_oq.pi_addr);
	put_unaligned_le16(PQI_NUM_EVENT_QUEUE_ELEMENTS,
		&request.data.create_operational_oq.num_elements);
	put_unaligned_le16(PQI_EVENT_OQ_ELEMENT_LENGTH / 16,
		&request.data.create_operational_oq.element_length);
	request.data.create_operational_oq.queue_protocol = PQI_PROTOCOL_SOP;
	put_unaligned_le16(event_queue->पूर्णांक_msg_num,
		&request.data.create_operational_oq.पूर्णांक_msg_num);

	rc = pqi_submit_admin_request_synchronous(ctrl_info, &request,
		&response);
	अगर (rc)
		वापस rc;

	event_queue->oq_ci = ctrl_info->iomem_base +
		PQI_DEVICE_REGISTERS_OFFSET +
		get_unaligned_le64(
			&response.data.create_operational_oq.oq_ci_offset);

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_create_queue_group(काष्ठा pqi_ctrl_info *ctrl_info,
	अचिन्हित पूर्णांक group_number)
अणु
	पूर्णांक rc;
	काष्ठा pqi_queue_group *queue_group;
	काष्ठा pqi_general_admin_request request;
	काष्ठा pqi_general_admin_response response;

	queue_group = &ctrl_info->queue_groups[group_number];

	/*
	 * Create IQ (Inbound Queue - host to device queue) क्रम
	 * RAID path.
	 */
	स_रखो(&request, 0, माप(request));
	request.header.iu_type = PQI_REQUEST_IU_GENERAL_ADMIN;
	put_unaligned_le16(PQI_GENERAL_ADMIN_IU_LENGTH,
		&request.header.iu_length);
	request.function_code = PQI_GENERAL_ADMIN_FUNCTION_CREATE_IQ;
	put_unaligned_le16(queue_group->iq_id[RAID_PATH],
		&request.data.create_operational_iq.queue_id);
	put_unaligned_le64(
		(u64)queue_group->iq_element_array_bus_addr[RAID_PATH],
		&request.data.create_operational_iq.element_array_addr);
	put_unaligned_le64((u64)queue_group->iq_ci_bus_addr[RAID_PATH],
		&request.data.create_operational_iq.ci_addr);
	put_unaligned_le16(ctrl_info->num_elements_per_iq,
		&request.data.create_operational_iq.num_elements);
	put_unaligned_le16(PQI_OPERATIONAL_IQ_ELEMENT_LENGTH / 16,
		&request.data.create_operational_iq.element_length);
	request.data.create_operational_iq.queue_protocol = PQI_PROTOCOL_SOP;

	rc = pqi_submit_admin_request_synchronous(ctrl_info, &request,
		&response);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error creating inbound RAID queue\n");
		वापस rc;
	पूर्ण

	queue_group->iq_pi[RAID_PATH] = ctrl_info->iomem_base +
		PQI_DEVICE_REGISTERS_OFFSET +
		get_unaligned_le64(
			&response.data.create_operational_iq.iq_pi_offset);

	/*
	 * Create IQ (Inbound Queue - host to device queue) क्रम
	 * Advanced I/O (AIO) path.
	 */
	स_रखो(&request, 0, माप(request));
	request.header.iu_type = PQI_REQUEST_IU_GENERAL_ADMIN;
	put_unaligned_le16(PQI_GENERAL_ADMIN_IU_LENGTH,
		&request.header.iu_length);
	request.function_code = PQI_GENERAL_ADMIN_FUNCTION_CREATE_IQ;
	put_unaligned_le16(queue_group->iq_id[AIO_PATH],
		&request.data.create_operational_iq.queue_id);
	put_unaligned_le64((u64)queue_group->
		iq_element_array_bus_addr[AIO_PATH],
		&request.data.create_operational_iq.element_array_addr);
	put_unaligned_le64((u64)queue_group->iq_ci_bus_addr[AIO_PATH],
		&request.data.create_operational_iq.ci_addr);
	put_unaligned_le16(ctrl_info->num_elements_per_iq,
		&request.data.create_operational_iq.num_elements);
	put_unaligned_le16(PQI_OPERATIONAL_IQ_ELEMENT_LENGTH / 16,
		&request.data.create_operational_iq.element_length);
	request.data.create_operational_iq.queue_protocol = PQI_PROTOCOL_SOP;

	rc = pqi_submit_admin_request_synchronous(ctrl_info, &request,
		&response);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error creating inbound AIO queue\n");
		वापस rc;
	पूर्ण

	queue_group->iq_pi[AIO_PATH] = ctrl_info->iomem_base +
		PQI_DEVICE_REGISTERS_OFFSET +
		get_unaligned_le64(
			&response.data.create_operational_iq.iq_pi_offset);

	/*
	 * Designate the 2nd IQ as the AIO path.  By शेष, all IQs are
	 * assumed to be क्रम RAID path I/O unless we change the queue's
	 * property.
	 */
	स_रखो(&request, 0, माप(request));
	request.header.iu_type = PQI_REQUEST_IU_GENERAL_ADMIN;
	put_unaligned_le16(PQI_GENERAL_ADMIN_IU_LENGTH,
		&request.header.iu_length);
	request.function_code = PQI_GENERAL_ADMIN_FUNCTION_CHANGE_IQ_PROPERTY;
	put_unaligned_le16(queue_group->iq_id[AIO_PATH],
		&request.data.change_operational_iq_properties.queue_id);
	put_unaligned_le32(PQI_IQ_PROPERTY_IS_AIO_QUEUE,
		&request.data.change_operational_iq_properties.venकरोr_specअगरic);

	rc = pqi_submit_admin_request_synchronous(ctrl_info, &request,
		&response);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error changing queue property\n");
		वापस rc;
	पूर्ण

	/*
	 * Create OQ (Outbound Queue - device to host queue).
	 */
	स_रखो(&request, 0, माप(request));
	request.header.iu_type = PQI_REQUEST_IU_GENERAL_ADMIN;
	put_unaligned_le16(PQI_GENERAL_ADMIN_IU_LENGTH,
		&request.header.iu_length);
	request.function_code = PQI_GENERAL_ADMIN_FUNCTION_CREATE_OQ;
	put_unaligned_le16(queue_group->oq_id,
		&request.data.create_operational_oq.queue_id);
	put_unaligned_le64((u64)queue_group->oq_element_array_bus_addr,
		&request.data.create_operational_oq.element_array_addr);
	put_unaligned_le64((u64)queue_group->oq_pi_bus_addr,
		&request.data.create_operational_oq.pi_addr);
	put_unaligned_le16(ctrl_info->num_elements_per_oq,
		&request.data.create_operational_oq.num_elements);
	put_unaligned_le16(PQI_OPERATIONAL_OQ_ELEMENT_LENGTH / 16,
		&request.data.create_operational_oq.element_length);
	request.data.create_operational_oq.queue_protocol = PQI_PROTOCOL_SOP;
	put_unaligned_le16(queue_group->पूर्णांक_msg_num,
		&request.data.create_operational_oq.पूर्णांक_msg_num);

	rc = pqi_submit_admin_request_synchronous(ctrl_info, &request,
		&response);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error creating outbound queue\n");
		वापस rc;
	पूर्ण

	queue_group->oq_ci = ctrl_info->iomem_base +
		PQI_DEVICE_REGISTERS_OFFSET +
		get_unaligned_le64(
			&response.data.create_operational_oq.oq_ci_offset);

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_create_queues(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक i;

	rc = pqi_create_event_queue(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error creating event queue\n");
		वापस rc;
	पूर्ण

	क्रम (i = 0; i < ctrl_info->num_queue_groups; i++) अणु
		rc = pqi_create_queue_group(ctrl_info, i);
		अगर (rc) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"error creating queue group number %u/%u\n",
				i, ctrl_info->num_queue_groups);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा PQI_REPORT_EVENT_CONFIG_BUFFER_LENGTH	\
	(दुरत्व(काष्ठा pqi_event_config, descriptors) + \
	(PQI_MAX_EVENT_DESCRIPTORS * माप(काष्ठा pqi_event_descriptor)))

अटल पूर्णांक pqi_configure_events(काष्ठा pqi_ctrl_info *ctrl_info,
	bool enable_events)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक i;
	काष्ठा pqi_event_config *event_config;
	काष्ठा pqi_event_descriptor *event_descriptor;
	काष्ठा pqi_general_management_request request;

	event_config = kदो_स्मृति(PQI_REPORT_EVENT_CONFIG_BUFFER_LENGTH,
		GFP_KERNEL);
	अगर (!event_config)
		वापस -ENOMEM;

	स_रखो(&request, 0, माप(request));

	request.header.iu_type = PQI_REQUEST_IU_REPORT_VENDOR_EVENT_CONFIG;
	put_unaligned_le16(दुरत्व(काष्ठा pqi_general_management_request,
		data.report_event_configuration.sg_descriptors[1]) -
		PQI_REQUEST_HEADER_LENGTH, &request.header.iu_length);
	put_unaligned_le32(PQI_REPORT_EVENT_CONFIG_BUFFER_LENGTH,
		&request.data.report_event_configuration.buffer_length);

	rc = pqi_map_single(ctrl_info->pci_dev,
		request.data.report_event_configuration.sg_descriptors,
		event_config, PQI_REPORT_EVENT_CONFIG_BUFFER_LENGTH,
		DMA_FROM_DEVICE);
	अगर (rc)
		जाओ out;

	rc = pqi_submit_raid_request_synchronous(ctrl_info, &request.header, 0, शून्य);

	pqi_pci_unmap(ctrl_info->pci_dev,
		request.data.report_event_configuration.sg_descriptors, 1,
		DMA_FROM_DEVICE);

	अगर (rc)
		जाओ out;

	क्रम (i = 0; i < event_config->num_event_descriptors; i++) अणु
		event_descriptor = &event_config->descriptors[i];
		अगर (enable_events &&
			pqi_is_supported_event(event_descriptor->event_type))
				put_unaligned_le16(ctrl_info->event_queue.oq_id,
					&event_descriptor->oq_id);
		अन्यथा
			put_unaligned_le16(0, &event_descriptor->oq_id);
	पूर्ण

	स_रखो(&request, 0, माप(request));

	request.header.iu_type = PQI_REQUEST_IU_SET_VENDOR_EVENT_CONFIG;
	put_unaligned_le16(दुरत्व(काष्ठा pqi_general_management_request,
		data.report_event_configuration.sg_descriptors[1]) -
		PQI_REQUEST_HEADER_LENGTH, &request.header.iu_length);
	put_unaligned_le32(PQI_REPORT_EVENT_CONFIG_BUFFER_LENGTH,
		&request.data.report_event_configuration.buffer_length);

	rc = pqi_map_single(ctrl_info->pci_dev,
		request.data.report_event_configuration.sg_descriptors,
		event_config, PQI_REPORT_EVENT_CONFIG_BUFFER_LENGTH,
		DMA_TO_DEVICE);
	अगर (rc)
		जाओ out;

	rc = pqi_submit_raid_request_synchronous(ctrl_info, &request.header, 0, शून्य);

	pqi_pci_unmap(ctrl_info->pci_dev,
		request.data.report_event_configuration.sg_descriptors, 1,
		DMA_TO_DEVICE);

out:
	kमुक्त(event_config);

	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक pqi_enable_events(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस pqi_configure_events(ctrl_info, true);
पूर्ण

अटल व्योम pqi_मुक्त_all_io_requests(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा device *dev;
	माप_प्रकार sg_chain_buffer_length;
	काष्ठा pqi_io_request *io_request;

	अगर (!ctrl_info->io_request_pool)
		वापस;

	dev = &ctrl_info->pci_dev->dev;
	sg_chain_buffer_length = ctrl_info->sg_chain_buffer_length;
	io_request = ctrl_info->io_request_pool;

	क्रम (i = 0; i < ctrl_info->max_io_slots; i++) अणु
		kमुक्त(io_request->iu);
		अगर (!io_request->sg_chain_buffer)
			अवरोध;
		dma_मुक्त_coherent(dev, sg_chain_buffer_length,
			io_request->sg_chain_buffer,
			io_request->sg_chain_buffer_dma_handle);
		io_request++;
	पूर्ण

	kमुक्त(ctrl_info->io_request_pool);
	ctrl_info->io_request_pool = शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक pqi_alloc_error_buffer(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	ctrl_info->error_buffer = dma_alloc_coherent(&ctrl_info->pci_dev->dev,
				     ctrl_info->error_buffer_length,
				     &ctrl_info->error_buffer_dma_handle,
				     GFP_KERNEL);
	अगर (!ctrl_info->error_buffer)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_alloc_io_resources(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अचिन्हित पूर्णांक i;
	व्योम *sg_chain_buffer;
	माप_प्रकार sg_chain_buffer_length;
	dma_addr_t sg_chain_buffer_dma_handle;
	काष्ठा device *dev;
	काष्ठा pqi_io_request *io_request;

	ctrl_info->io_request_pool = kसुस्मृति(ctrl_info->max_io_slots,
		माप(ctrl_info->io_request_pool[0]), GFP_KERNEL);

	अगर (!ctrl_info->io_request_pool) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to allocate I/O request pool\n");
		जाओ error;
	पूर्ण

	dev = &ctrl_info->pci_dev->dev;
	sg_chain_buffer_length = ctrl_info->sg_chain_buffer_length;
	io_request = ctrl_info->io_request_pool;

	क्रम (i = 0; i < ctrl_info->max_io_slots; i++) अणु
		io_request->iu = kदो_स्मृति(ctrl_info->max_inbound_iu_length, GFP_KERNEL);

		अगर (!io_request->iu) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"failed to allocate IU buffers\n");
			जाओ error;
		पूर्ण

		sg_chain_buffer = dma_alloc_coherent(dev,
			sg_chain_buffer_length, &sg_chain_buffer_dma_handle,
			GFP_KERNEL);

		अगर (!sg_chain_buffer) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"failed to allocate PQI scatter-gather chain buffers\n");
			जाओ error;
		पूर्ण

		io_request->index = i;
		io_request->sg_chain_buffer = sg_chain_buffer;
		io_request->sg_chain_buffer_dma_handle = sg_chain_buffer_dma_handle;
		io_request++;
	पूर्ण

	वापस 0;

error:
	pqi_मुक्त_all_io_requests(ctrl_info);

	वापस -ENOMEM;
पूर्ण

/*
 * Calculate required resources that are sized based on max. outstanding
 * requests and max. transfer size.
 */

अटल व्योम pqi_calculate_io_resources(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	u32 max_transfer_size;
	u32 max_sg_entries;

	ctrl_info->scsi_ml_can_queue =
		ctrl_info->max_outstanding_requests - PQI_RESERVED_IO_SLOTS;
	ctrl_info->max_io_slots = ctrl_info->max_outstanding_requests;

	ctrl_info->error_buffer_length =
		ctrl_info->max_io_slots * PQI_ERROR_BUFFER_ELEMENT_LENGTH;

	अगर (reset_devices)
		max_transfer_size = min(ctrl_info->max_transfer_size,
			PQI_MAX_TRANSFER_SIZE_KDUMP);
	अन्यथा
		max_transfer_size = min(ctrl_info->max_transfer_size,
			PQI_MAX_TRANSFER_SIZE);

	max_sg_entries = max_transfer_size / PAGE_SIZE;

	/* +1 to cover when the buffer is not page-aligned. */
	max_sg_entries++;

	max_sg_entries = min(ctrl_info->max_sg_entries, max_sg_entries);

	max_transfer_size = (max_sg_entries - 1) * PAGE_SIZE;

	ctrl_info->sg_chain_buffer_length =
		(max_sg_entries * माप(काष्ठा pqi_sg_descriptor)) +
		PQI_EXTRA_SGL_MEMORY;
	ctrl_info->sg_tablesize = max_sg_entries;
	ctrl_info->max_sectors = max_transfer_size / 512;
पूर्ण

अटल व्योम pqi_calculate_queue_resources(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक num_queue_groups;
	u16 num_elements_per_iq;
	u16 num_elements_per_oq;

	अगर (reset_devices) अणु
		num_queue_groups = 1;
	पूर्ण अन्यथा अणु
		पूर्णांक num_cpus;
		पूर्णांक max_queue_groups;

		max_queue_groups = min(ctrl_info->max_inbound_queues / 2,
			ctrl_info->max_outbound_queues - 1);
		max_queue_groups = min(max_queue_groups, PQI_MAX_QUEUE_GROUPS);

		num_cpus = num_online_cpus();
		num_queue_groups = min(num_cpus, ctrl_info->max_msix_vectors);
		num_queue_groups = min(num_queue_groups, max_queue_groups);
	पूर्ण

	ctrl_info->num_queue_groups = num_queue_groups;
	ctrl_info->max_hw_queue_index = num_queue_groups - 1;

	/*
	 * Make sure that the max. inbound IU length is an even multiple
	 * of our inbound element length.
	 */
	ctrl_info->max_inbound_iu_length =
		(ctrl_info->max_inbound_iu_length_per_firmware /
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH) *
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH;

	num_elements_per_iq =
		(ctrl_info->max_inbound_iu_length /
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH);

	/* Add one because one element in each queue is unusable. */
	num_elements_per_iq++;

	num_elements_per_iq = min(num_elements_per_iq,
		ctrl_info->max_elements_per_iq);

	num_elements_per_oq = ((num_elements_per_iq - 1) * 2) + 1;
	num_elements_per_oq = min(num_elements_per_oq,
		ctrl_info->max_elements_per_oq);

	ctrl_info->num_elements_per_iq = num_elements_per_iq;
	ctrl_info->num_elements_per_oq = num_elements_per_oq;

	ctrl_info->max_sg_per_iu =
		((ctrl_info->max_inbound_iu_length -
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH) /
		माप(काष्ठा pqi_sg_descriptor)) +
		PQI_MAX_EMBEDDED_SG_DESCRIPTORS;

	ctrl_info->max_sg_per_r56_iu =
		((ctrl_info->max_inbound_iu_length -
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH) /
		माप(काष्ठा pqi_sg_descriptor)) +
		PQI_MAX_EMBEDDED_R56_SG_DESCRIPTORS;
पूर्ण

अटल अंतरभूत व्योम pqi_set_sg_descriptor(काष्ठा pqi_sg_descriptor *sg_descriptor,
	काष्ठा scatterlist *sg)
अणु
	u64 address = (u64)sg_dma_address(sg);
	अचिन्हित पूर्णांक length = sg_dma_len(sg);

	put_unaligned_le64(address, &sg_descriptor->address);
	put_unaligned_le32(length, &sg_descriptor->length);
	put_unaligned_le32(0, &sg_descriptor->flags);
पूर्ण

अटल अचिन्हित पूर्णांक pqi_build_sg_list(काष्ठा pqi_sg_descriptor *sg_descriptor,
	काष्ठा scatterlist *sg, पूर्णांक sg_count, काष्ठा pqi_io_request *io_request,
	पूर्णांक max_sg_per_iu, bool *chained)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक num_sg_in_iu;

	*chained = false;
	i = 0;
	num_sg_in_iu = 0;
	max_sg_per_iu--;	/* Subtract 1 to leave room क्रम chain marker. */

	जबतक (1) अणु
		pqi_set_sg_descriptor(sg_descriptor, sg);
		अगर (!*chained)
			num_sg_in_iu++;
		i++;
		अगर (i == sg_count)
			अवरोध;
		sg_descriptor++;
		अगर (i == max_sg_per_iu) अणु
			put_unaligned_le64((u64)io_request->sg_chain_buffer_dma_handle,
				&sg_descriptor->address);
			put_unaligned_le32((sg_count - num_sg_in_iu) * माप(*sg_descriptor),
				&sg_descriptor->length);
			put_unaligned_le32(CISS_SG_CHAIN, &sg_descriptor->flags);
			*chained = true;
			num_sg_in_iu++;
			sg_descriptor = io_request->sg_chain_buffer;
		पूर्ण
		sg = sg_next(sg);
	पूर्ण

	put_unaligned_le32(CISS_SG_LAST, &sg_descriptor->flags);

	वापस num_sg_in_iu;
पूर्ण

अटल पूर्णांक pqi_build_raid_sg_list(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_raid_path_request *request, काष्ठा scsi_cmnd *scmd,
	काष्ठा pqi_io_request *io_request)
अणु
	u16 iu_length;
	पूर्णांक sg_count;
	bool chained;
	अचिन्हित पूर्णांक num_sg_in_iu;
	काष्ठा scatterlist *sg;
	काष्ठा pqi_sg_descriptor *sg_descriptor;

	sg_count = scsi_dma_map(scmd);
	अगर (sg_count < 0)
		वापस sg_count;

	iu_length = दुरत्व(काष्ठा pqi_raid_path_request, sg_descriptors) -
		PQI_REQUEST_HEADER_LENGTH;

	अगर (sg_count == 0)
		जाओ out;

	sg = scsi_sglist(scmd);
	sg_descriptor = request->sg_descriptors;

	num_sg_in_iu = pqi_build_sg_list(sg_descriptor, sg, sg_count, io_request,
		ctrl_info->max_sg_per_iu, &chained);

	request->partial = chained;
	iu_length += num_sg_in_iu * माप(*sg_descriptor);

out:
	put_unaligned_le16(iu_length, &request->header.iu_length);

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_build_aio_r1_sg_list(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_aio_r1_path_request *request, काष्ठा scsi_cmnd *scmd,
	काष्ठा pqi_io_request *io_request)
अणु
	u16 iu_length;
	पूर्णांक sg_count;
	bool chained;
	अचिन्हित पूर्णांक num_sg_in_iu;
	काष्ठा scatterlist *sg;
	काष्ठा pqi_sg_descriptor *sg_descriptor;

	sg_count = scsi_dma_map(scmd);
	अगर (sg_count < 0)
		वापस sg_count;

	iu_length = दुरत्व(काष्ठा pqi_aio_r1_path_request, sg_descriptors) -
		PQI_REQUEST_HEADER_LENGTH;
	num_sg_in_iu = 0;

	अगर (sg_count == 0)
		जाओ out;

	sg = scsi_sglist(scmd);
	sg_descriptor = request->sg_descriptors;

	num_sg_in_iu = pqi_build_sg_list(sg_descriptor, sg, sg_count, io_request,
		ctrl_info->max_sg_per_iu, &chained);

	request->partial = chained;
	iu_length += num_sg_in_iu * माप(*sg_descriptor);

out:
	put_unaligned_le16(iu_length, &request->header.iu_length);
	request->num_sg_descriptors = num_sg_in_iu;

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_build_aio_r56_sg_list(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_aio_r56_path_request *request, काष्ठा scsi_cmnd *scmd,
	काष्ठा pqi_io_request *io_request)
अणु
	u16 iu_length;
	पूर्णांक sg_count;
	bool chained;
	अचिन्हित पूर्णांक num_sg_in_iu;
	काष्ठा scatterlist *sg;
	काष्ठा pqi_sg_descriptor *sg_descriptor;

	sg_count = scsi_dma_map(scmd);
	अगर (sg_count < 0)
		वापस sg_count;

	iu_length = दुरत्व(काष्ठा pqi_aio_r56_path_request, sg_descriptors) -
		PQI_REQUEST_HEADER_LENGTH;
	num_sg_in_iu = 0;

	अगर (sg_count != 0) अणु
		sg = scsi_sglist(scmd);
		sg_descriptor = request->sg_descriptors;

		num_sg_in_iu = pqi_build_sg_list(sg_descriptor, sg, sg_count, io_request,
			ctrl_info->max_sg_per_r56_iu, &chained);

		request->partial = chained;
		iu_length += num_sg_in_iu * माप(*sg_descriptor);
	पूर्ण

	put_unaligned_le16(iu_length, &request->header.iu_length);
	request->num_sg_descriptors = num_sg_in_iu;

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_build_aio_sg_list(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_aio_path_request *request, काष्ठा scsi_cmnd *scmd,
	काष्ठा pqi_io_request *io_request)
अणु
	u16 iu_length;
	पूर्णांक sg_count;
	bool chained;
	अचिन्हित पूर्णांक num_sg_in_iu;
	काष्ठा scatterlist *sg;
	काष्ठा pqi_sg_descriptor *sg_descriptor;

	sg_count = scsi_dma_map(scmd);
	अगर (sg_count < 0)
		वापस sg_count;

	iu_length = दुरत्व(काष्ठा pqi_aio_path_request, sg_descriptors) -
		PQI_REQUEST_HEADER_LENGTH;
	num_sg_in_iu = 0;

	अगर (sg_count == 0)
		जाओ out;

	sg = scsi_sglist(scmd);
	sg_descriptor = request->sg_descriptors;

	num_sg_in_iu = pqi_build_sg_list(sg_descriptor, sg, sg_count, io_request,
		ctrl_info->max_sg_per_iu, &chained);

	request->partial = chained;
	iu_length += num_sg_in_iu * माप(*sg_descriptor);

out:
	put_unaligned_le16(iu_length, &request->header.iu_length);
	request->num_sg_descriptors = num_sg_in_iu;

	वापस 0;
पूर्ण

अटल व्योम pqi_raid_io_complete(काष्ठा pqi_io_request *io_request,
	व्योम *context)
अणु
	काष्ठा scsi_cmnd *scmd;

	scmd = io_request->scmd;
	pqi_मुक्त_io_request(io_request);
	scsi_dma_unmap(scmd);
	pqi_scsi_करोne(scmd);
पूर्ण

अटल पूर्णांक pqi_raid_submit_scsi_cmd_with_io_request(
	काष्ठा pqi_ctrl_info *ctrl_info, काष्ठा pqi_io_request *io_request,
	काष्ठा pqi_scsi_dev *device, काष्ठा scsi_cmnd *scmd,
	काष्ठा pqi_queue_group *queue_group)
अणु
	पूर्णांक rc;
	माप_प्रकार cdb_length;
	काष्ठा pqi_raid_path_request *request;

	io_request->io_complete_callback = pqi_raid_io_complete;
	io_request->scmd = scmd;

	request = io_request->iu;
	स_रखो(request, 0, दुरत्व(काष्ठा pqi_raid_path_request, sg_descriptors));

	request->header.iu_type = PQI_REQUEST_IU_RAID_PATH_IO;
	put_unaligned_le32(scsi_bufflen(scmd), &request->buffer_length);
	request->task_attribute = SOP_TASK_ATTRIBUTE_SIMPLE;
	put_unaligned_le16(io_request->index, &request->request_id);
	request->error_index = request->request_id;
	स_नकल(request->lun_number, device->scsi3addr, माप(request->lun_number));

	cdb_length = min_t(माप_प्रकार, scmd->cmd_len, माप(request->cdb));
	स_नकल(request->cdb, scmd->cmnd, cdb_length);

	चयन (cdb_length) अणु
	हाल 6:
	हाल 10:
	हाल 12:
	हाल 16:
		request->additional_cdb_bytes_usage = SOP_ADDITIONAL_CDB_BYTES_0;
		अवरोध;
	हाल 20:
		request->additional_cdb_bytes_usage = SOP_ADDITIONAL_CDB_BYTES_4;
		अवरोध;
	हाल 24:
		request->additional_cdb_bytes_usage = SOP_ADDITIONAL_CDB_BYTES_8;
		अवरोध;
	हाल 28:
		request->additional_cdb_bytes_usage = SOP_ADDITIONAL_CDB_BYTES_12;
		अवरोध;
	हाल 32:
	शेष:
		request->additional_cdb_bytes_usage = SOP_ADDITIONAL_CDB_BYTES_16;
		अवरोध;
	पूर्ण

	चयन (scmd->sc_data_direction) अणु
	हाल DMA_TO_DEVICE:
		request->data_direction = SOP_READ_FLAG;
		अवरोध;
	हाल DMA_FROM_DEVICE:
		request->data_direction = SOP_WRITE_FLAG;
		अवरोध;
	हाल DMA_NONE:
		request->data_direction = SOP_NO_सूचीECTION_FLAG;
		अवरोध;
	हाल DMA_BIसूचीECTIONAL:
		request->data_direction = SOP_BIसूचीECTIONAL;
		अवरोध;
	शेष:
		dev_err(&ctrl_info->pci_dev->dev,
			"unknown data direction: %d\n",
			scmd->sc_data_direction);
		अवरोध;
	पूर्ण

	rc = pqi_build_raid_sg_list(ctrl_info, request, scmd, io_request);
	अगर (rc) अणु
		pqi_मुक्त_io_request(io_request);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	pqi_start_io(ctrl_info, queue_group, RAID_PATH, io_request);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pqi_raid_submit_scsi_cmd(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device, काष्ठा scsi_cmnd *scmd,
	काष्ठा pqi_queue_group *queue_group)
अणु
	काष्ठा pqi_io_request *io_request;

	io_request = pqi_alloc_io_request(ctrl_info);

	वापस pqi_raid_submit_scsi_cmd_with_io_request(ctrl_info, io_request,
		device, scmd, queue_group);
पूर्ण

अटल bool pqi_raid_bypass_retry_needed(काष्ठा pqi_io_request *io_request)
अणु
	काष्ठा scsi_cmnd *scmd;
	काष्ठा pqi_scsi_dev *device;
	काष्ठा pqi_ctrl_info *ctrl_info;

	अगर (!io_request->raid_bypass)
		वापस false;

	scmd = io_request->scmd;
	अगर ((scmd->result & 0xff) == SAM_STAT_GOOD)
		वापस false;
	अगर (host_byte(scmd->result) == DID_NO_CONNECT)
		वापस false;

	device = scmd->device->hostdata;
	अगर (pqi_device_offline(device) || pqi_device_in_हटाओ(device))
		वापस false;

	ctrl_info = shost_to_hba(scmd->device->host);
	अगर (pqi_ctrl_offline(ctrl_info))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम pqi_aio_io_complete(काष्ठा pqi_io_request *io_request,
	व्योम *context)
अणु
	काष्ठा scsi_cmnd *scmd;

	scmd = io_request->scmd;
	scsi_dma_unmap(scmd);
	अगर (io_request->status == -EAGAIN || pqi_raid_bypass_retry_needed(io_request)) अणु
		set_host_byte(scmd, DID_IMM_RETRY);
		scmd->SCp.this_residual++;
	पूर्ण

	pqi_मुक्त_io_request(io_request);
	pqi_scsi_करोne(scmd);
पूर्ण

अटल अंतरभूत पूर्णांक pqi_aio_submit_scsi_cmd(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device, काष्ठा scsi_cmnd *scmd,
	काष्ठा pqi_queue_group *queue_group)
अणु
	वापस pqi_aio_submit_io(ctrl_info, scmd, device->aio_handle,
		scmd->cmnd, scmd->cmd_len, queue_group, शून्य, false);
पूर्ण

अटल पूर्णांक pqi_aio_submit_io(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा scsi_cmnd *scmd, u32 aio_handle, u8 *cdb,
	अचिन्हित पूर्णांक cdb_length, काष्ठा pqi_queue_group *queue_group,
	काष्ठा pqi_encryption_info *encryption_info, bool raid_bypass)
अणु
	पूर्णांक rc;
	काष्ठा pqi_io_request *io_request;
	काष्ठा pqi_aio_path_request *request;

	io_request = pqi_alloc_io_request(ctrl_info);
	io_request->io_complete_callback = pqi_aio_io_complete;
	io_request->scmd = scmd;
	io_request->raid_bypass = raid_bypass;

	request = io_request->iu;
	स_रखो(request, 0, दुरत्व(काष्ठा pqi_raid_path_request, sg_descriptors));

	request->header.iu_type = PQI_REQUEST_IU_AIO_PATH_IO;
	put_unaligned_le32(aio_handle, &request->nexus_id);
	put_unaligned_le32(scsi_bufflen(scmd), &request->buffer_length);
	request->task_attribute = SOP_TASK_ATTRIBUTE_SIMPLE;
	put_unaligned_le16(io_request->index, &request->request_id);
	request->error_index = request->request_id;
	अगर (cdb_length > माप(request->cdb))
		cdb_length = माप(request->cdb);
	request->cdb_length = cdb_length;
	स_नकल(request->cdb, cdb, cdb_length);

	चयन (scmd->sc_data_direction) अणु
	हाल DMA_TO_DEVICE:
		request->data_direction = SOP_READ_FLAG;
		अवरोध;
	हाल DMA_FROM_DEVICE:
		request->data_direction = SOP_WRITE_FLAG;
		अवरोध;
	हाल DMA_NONE:
		request->data_direction = SOP_NO_सूचीECTION_FLAG;
		अवरोध;
	हाल DMA_BIसूचीECTIONAL:
		request->data_direction = SOP_BIसूचीECTIONAL;
		अवरोध;
	शेष:
		dev_err(&ctrl_info->pci_dev->dev,
			"unknown data direction: %d\n",
			scmd->sc_data_direction);
		अवरोध;
	पूर्ण

	अगर (encryption_info) अणु
		request->encryption_enable = true;
		put_unaligned_le16(encryption_info->data_encryption_key_index,
			&request->data_encryption_key_index);
		put_unaligned_le32(encryption_info->encrypt_tweak_lower,
			&request->encrypt_tweak_lower);
		put_unaligned_le32(encryption_info->encrypt_tweak_upper,
			&request->encrypt_tweak_upper);
	पूर्ण

	rc = pqi_build_aio_sg_list(ctrl_info, request, scmd, io_request);
	अगर (rc) अणु
		pqi_मुक्त_io_request(io_request);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	pqi_start_io(ctrl_info, queue_group, AIO_PATH, io_request);

	वापस 0;
पूर्ण

अटल  पूर्णांक pqi_aio_submit_r1_ग_लिखो_io(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा scsi_cmnd *scmd, काष्ठा pqi_queue_group *queue_group,
	काष्ठा pqi_encryption_info *encryption_info, काष्ठा pqi_scsi_dev *device,
	काष्ठा pqi_scsi_dev_raid_map_data *rmd)
अणु
	पूर्णांक rc;
	काष्ठा pqi_io_request *io_request;
	काष्ठा pqi_aio_r1_path_request *r1_request;

	io_request = pqi_alloc_io_request(ctrl_info);
	io_request->io_complete_callback = pqi_aio_io_complete;
	io_request->scmd = scmd;
	io_request->raid_bypass = true;

	r1_request = io_request->iu;
	स_रखो(r1_request, 0, दुरत्व(काष्ठा pqi_aio_r1_path_request, sg_descriptors));

	r1_request->header.iu_type = PQI_REQUEST_IU_AIO_PATH_RAID1_IO;
	put_unaligned_le16(*(u16 *)device->scsi3addr & 0x3fff, &r1_request->volume_id);
	r1_request->num_drives = rmd->num_it_nexus_entries;
	put_unaligned_le32(rmd->it_nexus[0], &r1_request->it_nexus_1);
	put_unaligned_le32(rmd->it_nexus[1], &r1_request->it_nexus_2);
	अगर (rmd->num_it_nexus_entries == 3)
		put_unaligned_le32(rmd->it_nexus[2], &r1_request->it_nexus_3);

	put_unaligned_le32(scsi_bufflen(scmd), &r1_request->data_length);
	r1_request->task_attribute = SOP_TASK_ATTRIBUTE_SIMPLE;
	put_unaligned_le16(io_request->index, &r1_request->request_id);
	r1_request->error_index = r1_request->request_id;
	अगर (rmd->cdb_length > माप(r1_request->cdb))
		rmd->cdb_length = माप(r1_request->cdb);
	r1_request->cdb_length = rmd->cdb_length;
	स_नकल(r1_request->cdb, rmd->cdb, rmd->cdb_length);

	/* The direction is always ग_लिखो. */
	r1_request->data_direction = SOP_READ_FLAG;

	अगर (encryption_info) अणु
		r1_request->encryption_enable = true;
		put_unaligned_le16(encryption_info->data_encryption_key_index,
				&r1_request->data_encryption_key_index);
		put_unaligned_le32(encryption_info->encrypt_tweak_lower,
				&r1_request->encrypt_tweak_lower);
		put_unaligned_le32(encryption_info->encrypt_tweak_upper,
				&r1_request->encrypt_tweak_upper);
	पूर्ण

	rc = pqi_build_aio_r1_sg_list(ctrl_info, r1_request, scmd, io_request);
	अगर (rc) अणु
		pqi_मुक्त_io_request(io_request);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	pqi_start_io(ctrl_info, queue_group, AIO_PATH, io_request);

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_aio_submit_r56_ग_लिखो_io(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा scsi_cmnd *scmd, काष्ठा pqi_queue_group *queue_group,
	काष्ठा pqi_encryption_info *encryption_info, काष्ठा pqi_scsi_dev *device,
	काष्ठा pqi_scsi_dev_raid_map_data *rmd)
अणु
	पूर्णांक rc;
	काष्ठा pqi_io_request *io_request;
	काष्ठा pqi_aio_r56_path_request *r56_request;

	io_request = pqi_alloc_io_request(ctrl_info);
	io_request->io_complete_callback = pqi_aio_io_complete;
	io_request->scmd = scmd;
	io_request->raid_bypass = true;

	r56_request = io_request->iu;
	स_रखो(r56_request, 0, दुरत्व(काष्ठा pqi_aio_r56_path_request, sg_descriptors));

	अगर (device->raid_level == SA_RAID_5 || device->raid_level == SA_RAID_51)
		r56_request->header.iu_type = PQI_REQUEST_IU_AIO_PATH_RAID5_IO;
	अन्यथा
		r56_request->header.iu_type = PQI_REQUEST_IU_AIO_PATH_RAID6_IO;

	put_unaligned_le16(*(u16 *)device->scsi3addr & 0x3fff, &r56_request->volume_id);
	put_unaligned_le32(rmd->aio_handle, &r56_request->data_it_nexus);
	put_unaligned_le32(rmd->p_parity_it_nexus, &r56_request->p_parity_it_nexus);
	अगर (rmd->raid_level == SA_RAID_6) अणु
		put_unaligned_le32(rmd->q_parity_it_nexus, &r56_request->q_parity_it_nexus);
		r56_request->xor_multiplier = rmd->xor_mult;
	पूर्ण
	put_unaligned_le32(scsi_bufflen(scmd), &r56_request->data_length);
	r56_request->task_attribute = SOP_TASK_ATTRIBUTE_SIMPLE;
	put_unaligned_le64(rmd->row, &r56_request->row);

	put_unaligned_le16(io_request->index, &r56_request->request_id);
	r56_request->error_index = r56_request->request_id;

	अगर (rmd->cdb_length > माप(r56_request->cdb))
		rmd->cdb_length = माप(r56_request->cdb);
	r56_request->cdb_length = rmd->cdb_length;
	स_नकल(r56_request->cdb, rmd->cdb, rmd->cdb_length);

	/* The direction is always ग_लिखो. */
	r56_request->data_direction = SOP_READ_FLAG;

	अगर (encryption_info) अणु
		r56_request->encryption_enable = true;
		put_unaligned_le16(encryption_info->data_encryption_key_index,
				&r56_request->data_encryption_key_index);
		put_unaligned_le32(encryption_info->encrypt_tweak_lower,
				&r56_request->encrypt_tweak_lower);
		put_unaligned_le32(encryption_info->encrypt_tweak_upper,
				&r56_request->encrypt_tweak_upper);
	पूर्ण

	rc = pqi_build_aio_r56_sg_list(ctrl_info, r56_request, scmd, io_request);
	अगर (rc) अणु
		pqi_मुक्त_io_request(io_request);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	pqi_start_io(ctrl_info, queue_group, AIO_PATH, io_request);

	वापस 0;
पूर्ण

अटल अंतरभूत u16 pqi_get_hw_queue(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा scsi_cmnd *scmd)
अणु
	u16 hw_queue;

	hw_queue = blk_mq_unique_tag_to_hwq(blk_mq_unique_tag(scmd->request));
	अगर (hw_queue > ctrl_info->max_hw_queue_index)
		hw_queue = 0;

	वापस hw_queue;
पूर्ण

अटल अंतरभूत bool pqi_is_bypass_eligible_request(काष्ठा scsi_cmnd *scmd)
अणु
	अगर (blk_rq_is_passthrough(scmd->request))
		वापस false;

	वापस scmd->SCp.this_residual == 0;
पूर्ण

/*
 * This function माला_लो called just beक्रमe we hand the completed SCSI request
 * back to the SML.
 */

व्योम pqi_prep_क्रम_scsi_करोne(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा pqi_scsi_dev *device;

	अगर (!scmd->device) अणु
		set_host_byte(scmd, DID_NO_CONNECT);
		वापस;
	पूर्ण

	device = scmd->device->hostdata;
	अगर (!device) अणु
		set_host_byte(scmd, DID_NO_CONNECT);
		वापस;
	पूर्ण

	atomic_dec(&device->scsi_cmds_outstanding);
पूर्ण

अटल bool pqi_is_parity_ग_लिखो_stream(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा scsi_cmnd *scmd)
अणु
	u32 oldest_jअगरfies;
	u8 lru_index;
	पूर्णांक i;
	पूर्णांक rc;
	काष्ठा pqi_scsi_dev *device;
	काष्ठा pqi_stream_data *pqi_stream_data;
	काष्ठा pqi_scsi_dev_raid_map_data rmd;

	अगर (!ctrl_info->enable_stream_detection)
		वापस false;

	rc = pqi_get_aio_lba_and_block_count(scmd, &rmd);
	अगर (rc)
		वापस false;

	/* Check ग_लिखोs only. */
	अगर (!rmd.is_ग_लिखो)
		वापस false;

	device = scmd->device->hostdata;

	/* Check क्रम RAID 5/6 streams. */
	अगर (device->raid_level != SA_RAID_5 && device->raid_level != SA_RAID_6)
		वापस false;

	/*
	 * If controller करोes not support AIO RAIDअणु5,6पूर्ण ग_लिखोs, need to send
	 * requests करोwn non-AIO path.
	 */
	अगर ((device->raid_level == SA_RAID_5 && !ctrl_info->enable_r5_ग_लिखोs) ||
		(device->raid_level == SA_RAID_6 && !ctrl_info->enable_r6_ग_लिखोs))
		वापस true;

	lru_index = 0;
	oldest_jअगरfies = पूर्णांक_उच्च;
	क्रम (i = 0; i < NUM_STREAMS_PER_LUN; i++) अणु
		pqi_stream_data = &device->stream_data[i];
		/*
		 * Check क्रम adjacent request or request is within
		 * the previous request.
		 */
		अगर ((pqi_stream_data->next_lba &&
			rmd.first_block >= pqi_stream_data->next_lba) &&
			rmd.first_block <= pqi_stream_data->next_lba +
				rmd.block_cnt) अणु
			pqi_stream_data->next_lba = rmd.first_block +
				rmd.block_cnt;
			pqi_stream_data->last_accessed = jअगरfies;
			वापस true;
		पूर्ण

		/* unused entry */
		अगर (pqi_stream_data->last_accessed == 0) अणु
			lru_index = i;
			अवरोध;
		पूर्ण

		/* Find entry with oldest last accessed समय. */
		अगर (pqi_stream_data->last_accessed <= oldest_jअगरfies) अणु
			oldest_jअगरfies = pqi_stream_data->last_accessed;
			lru_index = i;
		पूर्ण
	पूर्ण

	/* Set LRU entry. */
	pqi_stream_data = &device->stream_data[lru_index];
	pqi_stream_data->last_accessed = jअगरfies;
	pqi_stream_data->next_lba = rmd.first_block + rmd.block_cnt;

	वापस false;
पूर्ण

अटल पूर्णांक pqi_scsi_queue_command(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *scmd)
अणु
	पूर्णांक rc;
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा pqi_scsi_dev *device;
	u16 hw_queue;
	काष्ठा pqi_queue_group *queue_group;
	bool raid_bypassed;

	device = scmd->device->hostdata;

	अगर (!device) अणु
		set_host_byte(scmd, DID_NO_CONNECT);
		pqi_scsi_करोne(scmd);
		वापस 0;
	पूर्ण

	atomic_inc(&device->scsi_cmds_outstanding);

	ctrl_info = shost_to_hba(shost);

	अगर (pqi_ctrl_offline(ctrl_info) || pqi_device_in_हटाओ(device)) अणु
		set_host_byte(scmd, DID_NO_CONNECT);
		pqi_scsi_करोne(scmd);
		वापस 0;
	पूर्ण

	अगर (pqi_ctrl_blocked(ctrl_info)) अणु
		rc = SCSI_MLQUEUE_HOST_BUSY;
		जाओ out;
	पूर्ण

	/*
	 * This is necessary because the SML करोesn't zero out this field during
	 * error recovery.
	 */
	scmd->result = 0;

	hw_queue = pqi_get_hw_queue(ctrl_info, scmd);
	queue_group = &ctrl_info->queue_groups[hw_queue];

	अगर (pqi_is_logical_device(device)) अणु
		raid_bypassed = false;
		अगर (device->raid_bypass_enabled &&
			pqi_is_bypass_eligible_request(scmd) &&
			!pqi_is_parity_ग_लिखो_stream(ctrl_info, scmd)) अणु
			rc = pqi_raid_bypass_submit_scsi_cmd(ctrl_info, device, scmd, queue_group);
			अगर (rc == 0 || rc == SCSI_MLQUEUE_HOST_BUSY) अणु
				raid_bypassed = true;
				atomic_inc(&device->raid_bypass_cnt);
			पूर्ण
		पूर्ण
		अगर (!raid_bypassed)
			rc = pqi_raid_submit_scsi_cmd(ctrl_info, device, scmd, queue_group);
	पूर्ण अन्यथा अणु
		अगर (device->aio_enabled)
			rc = pqi_aio_submit_scsi_cmd(ctrl_info, device, scmd, queue_group);
		अन्यथा
			rc = pqi_raid_submit_scsi_cmd(ctrl_info, device, scmd, queue_group);
	पूर्ण

out:
	अगर (rc)
		atomic_dec(&device->scsi_cmds_outstanding);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_रुको_until_queued_io_drained(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_queue_group *queue_group)
अणु
	अचिन्हित पूर्णांक path;
	अचिन्हित दीर्घ flags;
	bool list_is_empty;

	क्रम (path = 0; path < 2; path++) अणु
		जबतक (1) अणु
			spin_lock_irqsave(
				&queue_group->submit_lock[path], flags);
			list_is_empty =
				list_empty(&queue_group->request_list[path]);
			spin_unlock_irqrestore(
				&queue_group->submit_lock[path], flags);
			अगर (list_is_empty)
				अवरोध;
			pqi_check_ctrl_health(ctrl_info);
			अगर (pqi_ctrl_offline(ctrl_info))
				वापस -ENXIO;
			usleep_range(1000, 2000);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_रुको_until_inbound_queues_empty(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक path;
	काष्ठा pqi_queue_group *queue_group;
	pqi_index_t iq_pi;
	pqi_index_t iq_ci;

	क्रम (i = 0; i < ctrl_info->num_queue_groups; i++) अणु
		queue_group = &ctrl_info->queue_groups[i];

		rc = pqi_रुको_until_queued_io_drained(ctrl_info, queue_group);
		अगर (rc)
			वापस rc;

		क्रम (path = 0; path < 2; path++) अणु
			iq_pi = queue_group->iq_pi_copy[path];

			जबतक (1) अणु
				iq_ci = पढ़ोl(queue_group->iq_ci[path]);
				अगर (iq_ci == iq_pi)
					अवरोध;
				pqi_check_ctrl_health(ctrl_info);
				अगर (pqi_ctrl_offline(ctrl_info))
					वापस -ENXIO;
				usleep_range(1000, 2000);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pqi_fail_io_queued_क्रम_device(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक path;
	काष्ठा pqi_queue_group *queue_group;
	अचिन्हित दीर्घ flags;
	काष्ठा pqi_io_request *io_request;
	काष्ठा pqi_io_request *next;
	काष्ठा scsi_cmnd *scmd;
	काष्ठा pqi_scsi_dev *scsi_device;

	क्रम (i = 0; i < ctrl_info->num_queue_groups; i++) अणु
		queue_group = &ctrl_info->queue_groups[i];

		क्रम (path = 0; path < 2; path++) अणु
			spin_lock_irqsave(
				&queue_group->submit_lock[path], flags);

			list_क्रम_each_entry_safe(io_request, next,
				&queue_group->request_list[path],
				request_list_entry) अणु

				scmd = io_request->scmd;
				अगर (!scmd)
					जारी;

				scsi_device = scmd->device->hostdata;
				अगर (scsi_device != device)
					जारी;

				list_del(&io_request->request_list_entry);
				set_host_byte(scmd, DID_RESET);
				pqi_मुक्त_io_request(io_request);
				scsi_dma_unmap(scmd);
				pqi_scsi_करोne(scmd);
			पूर्ण

			spin_unlock_irqrestore(
				&queue_group->submit_lock[path], flags);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा PQI_PENDING_IO_WARNING_TIMEOUT_SECS	10

अटल पूर्णांक pqi_device_रुको_क्रम_pending_io(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device, अचिन्हित दीर्घ समयout_msecs)
अणु
	पूर्णांक cmds_outstanding;
	अचिन्हित दीर्घ start_jअगरfies;
	अचिन्हित दीर्घ warning_समयout;
	अचिन्हित दीर्घ msecs_रुकोing;

	start_jअगरfies = jअगरfies;
	warning_समयout = (PQI_PENDING_IO_WARNING_TIMEOUT_SECS * PQI_HZ) + start_jअगरfies;

	जबतक ((cmds_outstanding = atomic_पढ़ो(&device->scsi_cmds_outstanding)) > 0) अणु
		pqi_check_ctrl_health(ctrl_info);
		अगर (pqi_ctrl_offline(ctrl_info))
			वापस -ENXIO;
		msecs_रुकोing = jअगरfies_to_msecs(jअगरfies - start_jअगरfies);
		अगर (msecs_रुकोing > समयout_msecs) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"scsi %d:%d:%d:%d: timed out after %lu seconds waiting for %d outstanding command(s)\n",
				ctrl_info->scsi_host->host_no, device->bus, device->target,
				device->lun, msecs_रुकोing / 1000, cmds_outstanding);
			वापस -ETIMEDOUT;
		पूर्ण
		अगर (समय_after(jअगरfies, warning_समयout)) अणु
			dev_warn(&ctrl_info->pci_dev->dev,
				"scsi %d:%d:%d:%d: waiting %lu seconds for %d outstanding command(s)\n",
				ctrl_info->scsi_host->host_no, device->bus, device->target,
				device->lun, msecs_रुकोing / 1000, cmds_outstanding);
			warning_समयout = (PQI_PENDING_IO_WARNING_TIMEOUT_SECS * PQI_HZ) + jअगरfies;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pqi_lun_reset_complete(काष्ठा pqi_io_request *io_request,
	व्योम *context)
अणु
	काष्ठा completion *रुकोing = context;

	complete(रुकोing);
पूर्ण

#घोषणा PQI_LUN_RESET_POLL_COMPLETION_SECS	10

अटल पूर्णांक pqi_रुको_क्रम_lun_reset_completion(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device, काष्ठा completion *रुको)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक रुको_secs;

	रुको_secs = 0;

	जबतक (1) अणु
		अगर (रुको_क्रम_completion_io_समयout(रुको,
			PQI_LUN_RESET_POLL_COMPLETION_SECS * PQI_HZ)) अणु
			rc = 0;
			अवरोध;
		पूर्ण

		pqi_check_ctrl_health(ctrl_info);
		अगर (pqi_ctrl_offline(ctrl_info)) अणु
			rc = -ENXIO;
			अवरोध;
		पूर्ण

		रुको_secs += PQI_LUN_RESET_POLL_COMPLETION_SECS;

		dev_warn(&ctrl_info->pci_dev->dev,
			"scsi %d:%d:%d:%d: waiting %u seconds for LUN reset to complete\n",
			ctrl_info->scsi_host->host_no, device->bus, device->target, device->lun,
			रुको_secs);
	पूर्ण

	वापस rc;
पूर्ण

#घोषणा PQI_LUN_RESET_FIRMWARE_TIMEOUT_SECS	30

अटल पूर्णांक pqi_lun_reset(काष्ठा pqi_ctrl_info *ctrl_info, काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक rc;
	काष्ठा pqi_io_request *io_request;
	DECLARE_COMPLETION_ONSTACK(रुको);
	काष्ठा pqi_task_management_request *request;

	io_request = pqi_alloc_io_request(ctrl_info);
	io_request->io_complete_callback = pqi_lun_reset_complete;
	io_request->context = &रुको;

	request = io_request->iu;
	स_रखो(request, 0, माप(*request));

	request->header.iu_type = PQI_REQUEST_IU_TASK_MANAGEMENT;
	put_unaligned_le16(माप(*request) - PQI_REQUEST_HEADER_LENGTH,
		&request->header.iu_length);
	put_unaligned_le16(io_request->index, &request->request_id);
	स_नकल(request->lun_number, device->scsi3addr,
		माप(request->lun_number));
	request->task_management_function = SOP_TASK_MANAGEMENT_LUN_RESET;
	अगर (ctrl_info->पंचांगf_iu_समयout_supported)
		put_unaligned_le16(PQI_LUN_RESET_FIRMWARE_TIMEOUT_SECS, &request->समयout);

	pqi_start_io(ctrl_info, &ctrl_info->queue_groups[PQI_DEFAULT_QUEUE_GROUP], RAID_PATH,
		io_request);

	rc = pqi_रुको_क्रम_lun_reset_completion(ctrl_info, device, &रुको);
	अगर (rc == 0)
		rc = io_request->status;

	pqi_मुक्त_io_request(io_request);

	वापस rc;
पूर्ण

#घोषणा PQI_LUN_RESET_RETRIES				3
#घोषणा PQI_LUN_RESET_RETRY_INTERVAL_MSECS		(10 * 1000)
#घोषणा PQI_LUN_RESET_PENDING_IO_TIMEOUT_MSECS		(10 * 60 * 1000)
#घोषणा PQI_LUN_RESET_FAILED_PENDING_IO_TIMEOUT_MSECS	(2 * 60 * 1000)

अटल पूर्णांक pqi_lun_reset_with_retries(काष्ठा pqi_ctrl_info *ctrl_info, काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक reset_rc;
	पूर्णांक रुको_rc;
	अचिन्हित पूर्णांक retries;
	अचिन्हित दीर्घ समयout_msecs;

	क्रम (retries = 0;;) अणु
		reset_rc = pqi_lun_reset(ctrl_info, device);
		अगर (reset_rc == 0 || ++retries > PQI_LUN_RESET_RETRIES)
			अवरोध;
		msleep(PQI_LUN_RESET_RETRY_INTERVAL_MSECS);
	पूर्ण

	समयout_msecs = reset_rc ? PQI_LUN_RESET_FAILED_PENDING_IO_TIMEOUT_MSECS :
		PQI_LUN_RESET_PENDING_IO_TIMEOUT_MSECS;

	रुको_rc = pqi_device_रुको_क्रम_pending_io(ctrl_info, device, समयout_msecs);
	अगर (रुको_rc && reset_rc == 0)
		reset_rc = रुको_rc;

	वापस reset_rc == 0 ? SUCCESS : FAILED;
पूर्ण

अटल पूर्णांक pqi_device_reset(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक rc;

	pqi_ctrl_block_requests(ctrl_info);
	pqi_ctrl_रुको_until_quiesced(ctrl_info);
	pqi_fail_io_queued_क्रम_device(ctrl_info, device);
	rc = pqi_रुको_until_inbound_queues_empty(ctrl_info);
	अगर (rc)
		rc = FAILED;
	अन्यथा
		rc = pqi_lun_reset_with_retries(ctrl_info, device);
	pqi_ctrl_unblock_requests(ctrl_info);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_eh_device_reset_handler(काष्ठा scsi_cmnd *scmd)
अणु
	पूर्णांक rc;
	काष्ठा Scsi_Host *shost;
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा pqi_scsi_dev *device;

	shost = scmd->device->host;
	ctrl_info = shost_to_hba(shost);
	device = scmd->device->hostdata;

	mutex_lock(&ctrl_info->lun_reset_mutex);

	dev_err(&ctrl_info->pci_dev->dev,
		"resetting scsi %d:%d:%d:%d\n",
		shost->host_no, device->bus, device->target, device->lun);

	pqi_check_ctrl_health(ctrl_info);
	अगर (pqi_ctrl_offline(ctrl_info))
		rc = FAILED;
	अन्यथा
		rc = pqi_device_reset(ctrl_info, device);

	dev_err(&ctrl_info->pci_dev->dev,
		"reset of scsi %d:%d:%d:%d: %s\n",
		shost->host_no, device->bus, device->target, device->lun,
		rc == SUCCESS ? "SUCCESS" : "FAILED");

	mutex_unlock(&ctrl_info->lun_reset_mutex);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा pqi_scsi_dev *device;
	अचिन्हित दीर्घ flags;
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा scsi_target *starget;
	काष्ठा sas_rphy *rphy;

	ctrl_info = shost_to_hba(sdev->host);

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);

	अगर (sdev_channel(sdev) == PQI_PHYSICAL_DEVICE_BUS) अणु
		starget = scsi_target(sdev);
		rphy = target_to_rphy(starget);
		device = pqi_find_device_by_sas_rphy(ctrl_info, rphy);
		अगर (device) अणु
			device->target = sdev_id(sdev);
			device->lun = sdev->lun;
			device->target_lun_valid = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		device = pqi_find_scsi_dev(ctrl_info, sdev_channel(sdev),
			sdev_id(sdev), sdev->lun);
	पूर्ण

	अगर (device) अणु
		sdev->hostdata = device;
		device->sdev = sdev;
		अगर (device->queue_depth) अणु
			device->advertised_queue_depth = device->queue_depth;
			scsi_change_queue_depth(sdev,
				device->advertised_queue_depth);
		पूर्ण
		अगर (pqi_is_logical_device(device)) अणु
			pqi_disable_ग_लिखो_same(sdev);
		पूर्ण अन्यथा अणु
			sdev->allow_restart = 1;
			अगर (device->device_type == SA_DEVICE_TYPE_NVME)
				pqi_disable_ग_लिखो_same(sdev);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_map_queues(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info = shost_to_hba(shost);

	वापस blk_mq_pci_map_queues(&shost->tag_set.map[HCTX_TYPE_DEFAULT],
					ctrl_info->pci_dev, 0);
पूर्ण

अटल पूर्णांक pqi_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा pqi_scsi_dev *device;

	device = sdev->hostdata;
	device->devtype = sdev->type;

	वापस 0;
पूर्ण

अटल व्योम pqi_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pqi_scsi_dev *device;
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = shost_to_hba(sdev->host);

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);

	device = sdev->hostdata;
	अगर (device) अणु
		sdev->hostdata = शून्य;
		अगर (!list_empty(&device->scsi_device_list_entry))
			list_del(&device->scsi_device_list_entry);
	पूर्ण

	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	अगर (device) अणु
		pqi_dev_info(ctrl_info, "removed", device);
		pqi_मुक्त_device(device);
	पूर्ण
पूर्ण

अटल पूर्णांक pqi_getpciinfo_ioctl(काष्ठा pqi_ctrl_info *ctrl_info, व्योम __user *arg)
अणु
	काष्ठा pci_dev *pci_dev;
	u32 subप्रणाली_venकरोr;
	u32 subप्रणाली_device;
	cciss_pci_info_काष्ठा pciinfo;

	अगर (!arg)
		वापस -EINVAL;

	pci_dev = ctrl_info->pci_dev;

	pciinfo.करोमुख्य = pci_करोमुख्य_nr(pci_dev->bus);
	pciinfo.bus = pci_dev->bus->number;
	pciinfo.dev_fn = pci_dev->devfn;
	subप्रणाली_venकरोr = pci_dev->subप्रणाली_venकरोr;
	subप्रणाली_device = pci_dev->subप्रणाली_device;
	pciinfo.board_id = ((subप्रणाली_device << 16) & 0xffff0000) | subप्रणाली_venकरोr;

	अगर (copy_to_user(arg, &pciinfo, माप(pciinfo)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_getdrivver_ioctl(व्योम __user *arg)
अणु
	u32 version;

	अगर (!arg)
		वापस -EINVAL;

	version = (DRIVER_MAJOR << 28) | (DRIVER_MINOR << 24) |
		(DRIVER_RELEASE << 16) | DRIVER_REVISION;

	अगर (copy_to_user(arg, &version, माप(version)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

काष्ठा ciss_error_info अणु
	u8	scsi_status;
	पूर्णांक	command_status;
	माप_प्रकार	sense_data_length;
पूर्ण;

अटल व्योम pqi_error_info_to_ciss(काष्ठा pqi_raid_error_info *pqi_error_info,
	काष्ठा ciss_error_info *ciss_error_info)
अणु
	पूर्णांक ciss_cmd_status;
	माप_प्रकार sense_data_length;

	चयन (pqi_error_info->data_out_result) अणु
	हाल PQI_DATA_IN_OUT_GOOD:
		ciss_cmd_status = CISS_CMD_STATUS_SUCCESS;
		अवरोध;
	हाल PQI_DATA_IN_OUT_UNDERFLOW:
		ciss_cmd_status = CISS_CMD_STATUS_DATA_UNDERRUN;
		अवरोध;
	हाल PQI_DATA_IN_OUT_BUFFER_OVERFLOW:
		ciss_cmd_status = CISS_CMD_STATUS_DATA_OVERRUN;
		अवरोध;
	हाल PQI_DATA_IN_OUT_PROTOCOL_ERROR:
	हाल PQI_DATA_IN_OUT_BUFFER_ERROR:
	हाल PQI_DATA_IN_OUT_BUFFER_OVERFLOW_DESCRIPTOR_AREA:
	हाल PQI_DATA_IN_OUT_BUFFER_OVERFLOW_BRIDGE:
	हाल PQI_DATA_IN_OUT_ERROR:
		ciss_cmd_status = CISS_CMD_STATUS_PROTOCOL_ERROR;
		अवरोध;
	हाल PQI_DATA_IN_OUT_HARDWARE_ERROR:
	हाल PQI_DATA_IN_OUT_PCIE_FABRIC_ERROR:
	हाल PQI_DATA_IN_OUT_PCIE_COMPLETION_TIMEOUT:
	हाल PQI_DATA_IN_OUT_PCIE_COMPLETER_ABORT_RECEIVED:
	हाल PQI_DATA_IN_OUT_PCIE_UNSUPPORTED_REQUEST_RECEIVED:
	हाल PQI_DATA_IN_OUT_PCIE_ECRC_CHECK_FAILED:
	हाल PQI_DATA_IN_OUT_PCIE_UNSUPPORTED_REQUEST:
	हाल PQI_DATA_IN_OUT_PCIE_ACS_VIOLATION:
	हाल PQI_DATA_IN_OUT_PCIE_TLP_PREFIX_BLOCKED:
	हाल PQI_DATA_IN_OUT_PCIE_POISONED_MEMORY_READ:
		ciss_cmd_status = CISS_CMD_STATUS_HARDWARE_ERROR;
		अवरोध;
	हाल PQI_DATA_IN_OUT_UNSOLICITED_ABORT:
		ciss_cmd_status = CISS_CMD_STATUS_UNSOLICITED_ABORT;
		अवरोध;
	हाल PQI_DATA_IN_OUT_ABORTED:
		ciss_cmd_status = CISS_CMD_STATUS_ABORTED;
		अवरोध;
	हाल PQI_DATA_IN_OUT_TIMEOUT:
		ciss_cmd_status = CISS_CMD_STATUS_TIMEOUT;
		अवरोध;
	शेष:
		ciss_cmd_status = CISS_CMD_STATUS_TARGET_STATUS;
		अवरोध;
	पूर्ण

	sense_data_length =
		get_unaligned_le16(&pqi_error_info->sense_data_length);
	अगर (sense_data_length == 0)
		sense_data_length =
		get_unaligned_le16(&pqi_error_info->response_data_length);
	अगर (sense_data_length)
		अगर (sense_data_length > माप(pqi_error_info->data))
			sense_data_length = माप(pqi_error_info->data);

	ciss_error_info->scsi_status = pqi_error_info->status;
	ciss_error_info->command_status = ciss_cmd_status;
	ciss_error_info->sense_data_length = sense_data_length;
पूर्ण

अटल पूर्णांक pqi_passthru_ioctl(काष्ठा pqi_ctrl_info *ctrl_info, व्योम __user *arg)
अणु
	पूर्णांक rc;
	अक्षर *kernel_buffer = शून्य;
	u16 iu_length;
	माप_प्रकार sense_data_length;
	IOCTL_Command_काष्ठा iocommand;
	काष्ठा pqi_raid_path_request request;
	काष्ठा pqi_raid_error_info pqi_error_info;
	काष्ठा ciss_error_info ciss_error_info;

	अगर (pqi_ctrl_offline(ctrl_info))
		वापस -ENXIO;
	अगर (pqi_ofa_in_progress(ctrl_info) && pqi_ctrl_blocked(ctrl_info))
		वापस -EBUSY;
	अगर (!arg)
		वापस -EINVAL;
	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;
	अगर (copy_from_user(&iocommand, arg, माप(iocommand)))
		वापस -EFAULT;
	अगर (iocommand.buf_size < 1 &&
		iocommand.Request.Type.Direction != XFER_NONE)
		वापस -EINVAL;
	अगर (iocommand.Request.CDBLen > माप(request.cdb))
		वापस -EINVAL;
	अगर (iocommand.Request.Type.Type != TYPE_CMD)
		वापस -EINVAL;

	चयन (iocommand.Request.Type.Direction) अणु
	हाल XFER_NONE:
	हाल XFER_WRITE:
	हाल XFER_READ:
	हाल XFER_READ | XFER_WRITE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (iocommand.buf_size > 0) अणु
		kernel_buffer = kदो_स्मृति(iocommand.buf_size, GFP_KERNEL);
		अगर (!kernel_buffer)
			वापस -ENOMEM;
		अगर (iocommand.Request.Type.Direction & XFER_WRITE) अणु
			अगर (copy_from_user(kernel_buffer, iocommand.buf,
				iocommand.buf_size)) अणु
				rc = -EFAULT;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			स_रखो(kernel_buffer, 0, iocommand.buf_size);
		पूर्ण
	पूर्ण

	स_रखो(&request, 0, माप(request));

	request.header.iu_type = PQI_REQUEST_IU_RAID_PATH_IO;
	iu_length = दुरत्व(काष्ठा pqi_raid_path_request, sg_descriptors) -
		PQI_REQUEST_HEADER_LENGTH;
	स_नकल(request.lun_number, iocommand.LUN_info.LunAddrBytes,
		माप(request.lun_number));
	स_नकल(request.cdb, iocommand.Request.CDB, iocommand.Request.CDBLen);
	request.additional_cdb_bytes_usage = SOP_ADDITIONAL_CDB_BYTES_0;

	चयन (iocommand.Request.Type.Direction) अणु
	हाल XFER_NONE:
		request.data_direction = SOP_NO_सूचीECTION_FLAG;
		अवरोध;
	हाल XFER_WRITE:
		request.data_direction = SOP_WRITE_FLAG;
		अवरोध;
	हाल XFER_READ:
		request.data_direction = SOP_READ_FLAG;
		अवरोध;
	हाल XFER_READ | XFER_WRITE:
		request.data_direction = SOP_BIसूचीECTIONAL;
		अवरोध;
	पूर्ण

	request.task_attribute = SOP_TASK_ATTRIBUTE_SIMPLE;

	अगर (iocommand.buf_size > 0) अणु
		put_unaligned_le32(iocommand.buf_size, &request.buffer_length);

		rc = pqi_map_single(ctrl_info->pci_dev,
			&request.sg_descriptors[0], kernel_buffer,
			iocommand.buf_size, DMA_BIसूचीECTIONAL);
		अगर (rc)
			जाओ out;

		iu_length += माप(request.sg_descriptors[0]);
	पूर्ण

	put_unaligned_le16(iu_length, &request.header.iu_length);

	अगर (ctrl_info->raid_iu_समयout_supported)
		put_unaligned_le32(iocommand.Request.Timeout, &request.समयout);

	rc = pqi_submit_raid_request_synchronous(ctrl_info, &request.header,
		PQI_SYNC_FLAGS_INTERRUPTABLE, &pqi_error_info);

	अगर (iocommand.buf_size > 0)
		pqi_pci_unmap(ctrl_info->pci_dev, request.sg_descriptors, 1,
			DMA_BIसूचीECTIONAL);

	स_रखो(&iocommand.error_info, 0, माप(iocommand.error_info));

	अगर (rc == 0) अणु
		pqi_error_info_to_ciss(&pqi_error_info, &ciss_error_info);
		iocommand.error_info.ScsiStatus = ciss_error_info.scsi_status;
		iocommand.error_info.CommandStatus =
			ciss_error_info.command_status;
		sense_data_length = ciss_error_info.sense_data_length;
		अगर (sense_data_length) अणु
			अगर (sense_data_length >
				माप(iocommand.error_info.SenseInfo))
				sense_data_length =
					माप(iocommand.error_info.SenseInfo);
			स_नकल(iocommand.error_info.SenseInfo,
				pqi_error_info.data, sense_data_length);
			iocommand.error_info.SenseLen = sense_data_length;
		पूर्ण
	पूर्ण

	अगर (copy_to_user(arg, &iocommand, माप(iocommand))) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (rc == 0 && iocommand.buf_size > 0 &&
		(iocommand.Request.Type.Direction & XFER_READ)) अणु
		अगर (copy_to_user(iocommand.buf, kernel_buffer,
			iocommand.buf_size)) अणु
			rc = -EFAULT;
		पूर्ण
	पूर्ण

out:
	kमुक्त(kernel_buffer);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_ioctl(काष्ठा scsi_device *sdev, अचिन्हित पूर्णांक cmd,
		     व्योम __user *arg)
अणु
	पूर्णांक rc;
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = shost_to_hba(sdev->host);

	चयन (cmd) अणु
	हाल CCISS_DEREGDISK:
	हाल CCISS_REGNEWDISK:
	हाल CCISS_REGNEWD:
		rc = pqi_scan_scsi_devices(ctrl_info);
		अवरोध;
	हाल CCISS_GETPCIINFO:
		rc = pqi_getpciinfo_ioctl(ctrl_info, arg);
		अवरोध;
	हाल CCISS_GETDRIVVER:
		rc = pqi_getdrivver_ioctl(arg);
		अवरोध;
	हाल CCISS_PASSTHRU:
		rc = pqi_passthru_ioctl(ctrl_info, arg);
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल sमाप_प्रकार pqi_firmware_version_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा pqi_ctrl_info *ctrl_info;

	shost = class_to_shost(dev);
	ctrl_info = shost_to_hba(shost);

	वापस scnम_लिखो(buffer, PAGE_SIZE, "%s\n", ctrl_info->firmware_version);
पूर्ण

अटल sमाप_प्रकार pqi_driver_version_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	वापस scnम_लिखो(buffer, PAGE_SIZE, "%s\n", DRIVER_VERSION BUILD_TIMESTAMP);
पूर्ण

अटल sमाप_प्रकार pqi_serial_number_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा pqi_ctrl_info *ctrl_info;

	shost = class_to_shost(dev);
	ctrl_info = shost_to_hba(shost);

	वापस scnम_लिखो(buffer, PAGE_SIZE, "%s\n", ctrl_info->serial_number);
पूर्ण

अटल sमाप_प्रकार pqi_model_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा pqi_ctrl_info *ctrl_info;

	shost = class_to_shost(dev);
	ctrl_info = shost_to_hba(shost);

	वापस scnम_लिखो(buffer, PAGE_SIZE, "%s\n", ctrl_info->model);
पूर्ण

अटल sमाप_प्रकार pqi_venकरोr_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा pqi_ctrl_info *ctrl_info;

	shost = class_to_shost(dev);
	ctrl_info = shost_to_hba(shost);

	वापस scnम_लिखो(buffer, PAGE_SIZE, "%s\n", ctrl_info->venकरोr);
पूर्ण

अटल sमाप_प्रकार pqi_host_rescan_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);

	pqi_scan_start(shost);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pqi_lockup_action_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	पूर्णांक count = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pqi_lockup_actions); i++) अणु
		अगर (pqi_lockup_actions[i].action == pqi_lockup_action)
			count += scnम_लिखो(buffer + count, PAGE_SIZE - count,
				"[%s] ", pqi_lockup_actions[i].name);
		अन्यथा
			count += scnम_लिखो(buffer + count, PAGE_SIZE - count,
				"%s ", pqi_lockup_actions[i].name);
	पूर्ण

	count += scnम_लिखो(buffer + count, PAGE_SIZE - count, "\n");

	वापस count;
पूर्ण

अटल sमाप_प्रकार pqi_lockup_action_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक i;
	अक्षर *action_name;
	अक्षर action_name_buffer[32];

	strlcpy(action_name_buffer, buffer, माप(action_name_buffer));
	action_name = म_मालाip(action_name_buffer);

	क्रम (i = 0; i < ARRAY_SIZE(pqi_lockup_actions); i++) अणु
		अगर (म_भेद(action_name, pqi_lockup_actions[i].name) == 0) अणु
			pqi_lockup_action = pqi_lockup_actions[i].action;
			वापस count;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार pqi_host_enable_stream_detection_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा pqi_ctrl_info *ctrl_info = shost_to_hba(shost);

	वापस scnम_लिखो(buffer, 10, "%x\n",
			ctrl_info->enable_stream_detection);
पूर्ण

अटल sमाप_प्रकार pqi_host_enable_stream_detection_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा pqi_ctrl_info *ctrl_info = shost_to_hba(shost);
	u8 set_stream_detection = 0;

	अगर (kstrtou8(buffer, 0, &set_stream_detection))
		वापस -EINVAL;

	अगर (set_stream_detection > 0)
		set_stream_detection = 1;

	ctrl_info->enable_stream_detection = set_stream_detection;

	वापस count;
पूर्ण

अटल sमाप_प्रकार pqi_host_enable_r5_ग_लिखोs_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा pqi_ctrl_info *ctrl_info = shost_to_hba(shost);

	वापस scnम_लिखो(buffer, 10, "%x\n", ctrl_info->enable_r5_ग_लिखोs);
पूर्ण

अटल sमाप_प्रकार pqi_host_enable_r5_ग_लिखोs_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा pqi_ctrl_info *ctrl_info = shost_to_hba(shost);
	u8 set_r5_ग_लिखोs = 0;

	अगर (kstrtou8(buffer, 0, &set_r5_ग_लिखोs))
		वापस -EINVAL;

	अगर (set_r5_ग_लिखोs > 0)
		set_r5_ग_लिखोs = 1;

	ctrl_info->enable_r5_ग_लिखोs = set_r5_ग_लिखोs;

	वापस count;
पूर्ण

अटल sमाप_प्रकार pqi_host_enable_r6_ग_लिखोs_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा pqi_ctrl_info *ctrl_info = shost_to_hba(shost);

	वापस scnम_लिखो(buffer, 10, "%x\n", ctrl_info->enable_r6_ग_लिखोs);
पूर्ण

अटल sमाप_प्रकार pqi_host_enable_r6_ग_लिखोs_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा pqi_ctrl_info *ctrl_info = shost_to_hba(shost);
	u8 set_r6_ग_लिखोs = 0;

	अगर (kstrtou8(buffer, 0, &set_r6_ग_लिखोs))
		वापस -EINVAL;

	अगर (set_r6_ग_लिखोs > 0)
		set_r6_ग_लिखोs = 1;

	ctrl_info->enable_r6_ग_लिखोs = set_r6_ग_लिखोs;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(driver_version, 0444, pqi_driver_version_show, शून्य);
अटल DEVICE_ATTR(firmware_version, 0444, pqi_firmware_version_show, शून्य);
अटल DEVICE_ATTR(model, 0444, pqi_model_show, शून्य);
अटल DEVICE_ATTR(serial_number, 0444, pqi_serial_number_show, शून्य);
अटल DEVICE_ATTR(venकरोr, 0444, pqi_venकरोr_show, शून्य);
अटल DEVICE_ATTR(rescan, 0200, शून्य, pqi_host_rescan_store);
अटल DEVICE_ATTR(lockup_action, 0644, pqi_lockup_action_show,
	pqi_lockup_action_store);
अटल DEVICE_ATTR(enable_stream_detection, 0644,
	pqi_host_enable_stream_detection_show,
	pqi_host_enable_stream_detection_store);
अटल DEVICE_ATTR(enable_r5_ग_लिखोs, 0644,
	pqi_host_enable_r5_ग_लिखोs_show, pqi_host_enable_r5_ग_लिखोs_store);
अटल DEVICE_ATTR(enable_r6_ग_लिखोs, 0644,
	pqi_host_enable_r6_ग_लिखोs_show, pqi_host_enable_r6_ग_लिखोs_store);

अटल काष्ठा device_attribute *pqi_shost_attrs[] = अणु
	&dev_attr_driver_version,
	&dev_attr_firmware_version,
	&dev_attr_model,
	&dev_attr_serial_number,
	&dev_attr_venकरोr,
	&dev_attr_rescan,
	&dev_attr_lockup_action,
	&dev_attr_enable_stream_detection,
	&dev_attr_enable_r5_ग_लिखोs,
	&dev_attr_enable_r6_ग_लिखोs,
	शून्य
पूर्ण;

अटल sमाप_प्रकार pqi_unique_id_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा scsi_device *sdev;
	काष्ठा pqi_scsi_dev *device;
	अचिन्हित दीर्घ flags;
	u8 unique_id[16];

	sdev = to_scsi_device(dev);
	ctrl_info = shost_to_hba(sdev->host);

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);

	device = sdev->hostdata;
	अगर (!device) अणु
		spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);
		वापस -ENODEV;
	पूर्ण

	अगर (device->is_physical_device) अणु
		स_रखो(unique_id, 0, 8);
		स_नकल(unique_id + 8, &device->wwid, माप(device->wwid));
	पूर्ण अन्यथा अणु
		स_नकल(unique_id, device->volume_id, माप(device->volume_id));
	पूर्ण

	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	वापस scnम_लिखो(buffer, PAGE_SIZE,
		"%02X%02X%02X%02X%02X%02X%02X%02X"
		"%02X%02X%02X%02X%02X%02X%02X%02X\n",
		unique_id[0], unique_id[1], unique_id[2], unique_id[3],
		unique_id[4], unique_id[5], unique_id[6], unique_id[7],
		unique_id[8], unique_id[9], unique_id[10], unique_id[11],
		unique_id[12], unique_id[13], unique_id[14], unique_id[15]);
पूर्ण

अटल sमाप_प्रकार pqi_lunid_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा scsi_device *sdev;
	काष्ठा pqi_scsi_dev *device;
	अचिन्हित दीर्घ flags;
	u8 lunid[8];

	sdev = to_scsi_device(dev);
	ctrl_info = shost_to_hba(sdev->host);

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);

	device = sdev->hostdata;
	अगर (!device) अणु
		spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);
		वापस -ENODEV;
	पूर्ण

	स_नकल(lunid, device->scsi3addr, माप(lunid));

	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	वापस scnम_लिखो(buffer, PAGE_SIZE, "0x%8phN\n", lunid);
पूर्ण

#घोषणा MAX_PATHS	8

अटल sमाप_प्रकार pqi_path_info_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा scsi_device *sdev;
	काष्ठा pqi_scsi_dev *device;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक output_len = 0;
	u8 box;
	u8 bay;
	u8 path_map_index;
	अक्षर *active;
	u8 phys_connector[2];

	sdev = to_scsi_device(dev);
	ctrl_info = shost_to_hba(sdev->host);

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);

	device = sdev->hostdata;
	अगर (!device) अणु
		spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);
		वापस -ENODEV;
	पूर्ण

	bay = device->bay;
	क्रम (i = 0; i < MAX_PATHS; i++) अणु
		path_map_index = 1 << i;
		अगर (i == device->active_path_index)
			active = "Active";
		अन्यथा अगर (device->path_map & path_map_index)
			active = "Inactive";
		अन्यथा
			जारी;

		output_len += scnम_लिखो(buf + output_len,
					PAGE_SIZE - output_len,
					"[%d:%d:%d:%d] %20.20s ",
					ctrl_info->scsi_host->host_no,
					device->bus, device->target,
					device->lun,
					scsi_device_type(device->devtype));

		अगर (device->devtype == TYPE_RAID ||
			pqi_is_logical_device(device))
			जाओ end_buffer;

		स_नकल(&phys_connector, &device->phys_connector[i],
			माप(phys_connector));
		अगर (phys_connector[0] < '0')
			phys_connector[0] = '0';
		अगर (phys_connector[1] < '0')
			phys_connector[1] = '0';

		output_len += scnम_लिखो(buf + output_len,
					PAGE_SIZE - output_len,
					"PORT: %.2s ", phys_connector);

		box = device->box[i];
		अगर (box != 0 && box != 0xFF)
			output_len += scnम_लिखो(buf + output_len,
						PAGE_SIZE - output_len,
						"BOX: %hhu ", box);

		अगर ((device->devtype == TYPE_DISK ||
			device->devtype == TYPE_ZBC) &&
			pqi_expose_device(device))
			output_len += scnम_लिखो(buf + output_len,
						PAGE_SIZE - output_len,
						"BAY: %hhu ", bay);

end_buffer:
		output_len += scnम_लिखो(buf + output_len,
					PAGE_SIZE - output_len,
					"%s\n", active);
	पूर्ण

	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	वापस output_len;
पूर्ण

अटल sमाप_प्रकार pqi_sas_address_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा scsi_device *sdev;
	काष्ठा pqi_scsi_dev *device;
	अचिन्हित दीर्घ flags;
	u64 sas_address;

	sdev = to_scsi_device(dev);
	ctrl_info = shost_to_hba(sdev->host);

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);

	device = sdev->hostdata;
	अगर (!device || !pqi_is_device_with_sas_address(device)) अणु
		spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);
		वापस -ENODEV;
	पूर्ण

	sas_address = device->sas_address;

	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	वापस scnम_लिखो(buffer, PAGE_SIZE, "0x%016llx\n", sas_address);
पूर्ण

अटल sमाप_प्रकार pqi_ssd_smart_path_enabled_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा scsi_device *sdev;
	काष्ठा pqi_scsi_dev *device;
	अचिन्हित दीर्घ flags;

	sdev = to_scsi_device(dev);
	ctrl_info = shost_to_hba(sdev->host);

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);

	device = sdev->hostdata;
	अगर (!device) अणु
		spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);
		वापस -ENODEV;
	पूर्ण

	buffer[0] = device->raid_bypass_enabled ? '1' : '0';
	buffer[1] = '\n';
	buffer[2] = '\0';

	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	वापस 2;
पूर्ण

अटल sमाप_प्रकार pqi_raid_level_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा scsi_device *sdev;
	काष्ठा pqi_scsi_dev *device;
	अचिन्हित दीर्घ flags;
	अक्षर *raid_level;

	sdev = to_scsi_device(dev);
	ctrl_info = shost_to_hba(sdev->host);

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);

	device = sdev->hostdata;
	अगर (!device) अणु
		spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);
		वापस -ENODEV;
	पूर्ण

	अगर (pqi_is_logical_device(device))
		raid_level = pqi_raid_level_to_string(device->raid_level);
	अन्यथा
		raid_level = "N/A";

	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	वापस scnम_लिखो(buffer, PAGE_SIZE, "%s\n", raid_level);
पूर्ण

अटल sमाप_प्रकार pqi_raid_bypass_cnt_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा scsi_device *sdev;
	काष्ठा pqi_scsi_dev *device;
	अचिन्हित दीर्घ flags;
	पूर्णांक raid_bypass_cnt;

	sdev = to_scsi_device(dev);
	ctrl_info = shost_to_hba(sdev->host);

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);

	device = sdev->hostdata;
	अगर (!device) अणु
		spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);
		वापस -ENODEV;
	पूर्ण

	raid_bypass_cnt = atomic_पढ़ो(&device->raid_bypass_cnt);

	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	वापस scnम_लिखो(buffer, PAGE_SIZE, "0x%x\n", raid_bypass_cnt);
पूर्ण

अटल DEVICE_ATTR(lunid, 0444, pqi_lunid_show, शून्य);
अटल DEVICE_ATTR(unique_id, 0444, pqi_unique_id_show, शून्य);
अटल DEVICE_ATTR(path_info, 0444, pqi_path_info_show, शून्य);
अटल DEVICE_ATTR(sas_address, 0444, pqi_sas_address_show, शून्य);
अटल DEVICE_ATTR(ssd_smart_path_enabled, 0444, pqi_ssd_smart_path_enabled_show, शून्य);
अटल DEVICE_ATTR(raid_level, 0444, pqi_raid_level_show, शून्य);
अटल DEVICE_ATTR(raid_bypass_cnt, 0444, pqi_raid_bypass_cnt_show, शून्य);

अटल काष्ठा device_attribute *pqi_sdev_attrs[] = अणु
	&dev_attr_lunid,
	&dev_attr_unique_id,
	&dev_attr_path_info,
	&dev_attr_sas_address,
	&dev_attr_ssd_smart_path_enabled,
	&dev_attr_raid_level,
	&dev_attr_raid_bypass_cnt,
	शून्य
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा pqi_driver_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = DRIVER_NAME_SHORT,
	.proc_name = DRIVER_NAME_SHORT,
	.queuecommand = pqi_scsi_queue_command,
	.scan_start = pqi_scan_start,
	.scan_finished = pqi_scan_finished,
	.this_id = -1,
	.eh_device_reset_handler = pqi_eh_device_reset_handler,
	.ioctl = pqi_ioctl,
	.slave_alloc = pqi_slave_alloc,
	.slave_configure = pqi_slave_configure,
	.slave_destroy = pqi_slave_destroy,
	.map_queues = pqi_map_queues,
	.sdev_attrs = pqi_sdev_attrs,
	.shost_attrs = pqi_shost_attrs,
पूर्ण;

अटल पूर्णांक pqi_रेजिस्टर_scsi(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	काष्ठा Scsi_Host *shost;

	shost = scsi_host_alloc(&pqi_driver_ढाँचा, माप(ctrl_info));
	अगर (!shost) अणु
		dev_err(&ctrl_info->pci_dev->dev, "scsi_host_alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	shost->io_port = 0;
	shost->n_io_port = 0;
	shost->this_id = -1;
	shost->max_channel = PQI_MAX_BUS;
	shost->max_cmd_len = MAX_COMMAND_SIZE;
	shost->max_lun = ~0;
	shost->max_id = ~0;
	shost->max_sectors = ctrl_info->max_sectors;
	shost->can_queue = ctrl_info->scsi_ml_can_queue;
	shost->cmd_per_lun = shost->can_queue;
	shost->sg_tablesize = ctrl_info->sg_tablesize;
	shost->transportt = pqi_sas_transport_ढाँचा;
	shost->irq = pci_irq_vector(ctrl_info->pci_dev, 0);
	shost->unique_id = shost->irq;
	shost->nr_hw_queues = ctrl_info->num_queue_groups;
	shost->host_tagset = 1;
	shost->hostdata[0] = (अचिन्हित दीर्घ)ctrl_info;

	rc = scsi_add_host(shost, &ctrl_info->pci_dev->dev);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev, "scsi_add_host failed\n");
		जाओ मुक्त_host;
	पूर्ण

	rc = pqi_add_sas_host(shost, ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev, "add SAS host failed\n");
		जाओ हटाओ_host;
	पूर्ण

	ctrl_info->scsi_host = shost;

	वापस 0;

हटाओ_host:
	scsi_हटाओ_host(shost);
मुक्त_host:
	scsi_host_put(shost);

	वापस rc;
पूर्ण

अटल व्योम pqi_unरेजिस्टर_scsi(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	काष्ठा Scsi_Host *shost;

	pqi_delete_sas_host(ctrl_info);

	shost = ctrl_info->scsi_host;
	अगर (!shost)
		वापस;

	scsi_हटाओ_host(shost);
	scsi_host_put(shost);
पूर्ण

अटल पूर्णांक pqi_रुको_क्रम_pqi_reset_completion(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc = 0;
	काष्ठा pqi_device_रेजिस्टरs __iomem *pqi_रेजिस्टरs;
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक समयout_msecs;
	जोड़ pqi_reset_रेजिस्टर reset_reg;

	pqi_रेजिस्टरs = ctrl_info->pqi_रेजिस्टरs;
	समयout_msecs = पढ़ोw(&pqi_रेजिस्टरs->max_reset_समयout) * 100;
	समयout = msecs_to_jअगरfies(समयout_msecs) + jअगरfies;

	जबतक (1) अणु
		msleep(PQI_RESET_POLL_INTERVAL_MSECS);
		reset_reg.all_bits = पढ़ोl(&pqi_रेजिस्टरs->device_reset);
		अगर (reset_reg.bits.reset_action == PQI_RESET_ACTION_COMPLETED)
			अवरोध;
		pqi_check_ctrl_health(ctrl_info);
		अगर (pqi_ctrl_offline(ctrl_info)) अणु
			rc = -ENXIO;
			अवरोध;
		पूर्ण
		अगर (समय_after(jअगरfies, समयout)) अणु
			rc = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_reset(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	जोड़ pqi_reset_रेजिस्टर reset_reg;

	अगर (ctrl_info->pqi_reset_quiesce_supported) अणु
		rc = sis_pqi_reset_quiesce(ctrl_info);
		अगर (rc) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"PQI reset failed during quiesce with error %d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	reset_reg.all_bits = 0;
	reset_reg.bits.reset_type = PQI_RESET_TYPE_HARD_RESET;
	reset_reg.bits.reset_action = PQI_RESET_ACTION_RESET;

	ग_लिखोl(reset_reg.all_bits, &ctrl_info->pqi_रेजिस्टरs->device_reset);

	rc = pqi_रुको_क्रम_pqi_reset_completion(ctrl_info);
	अगर (rc)
		dev_err(&ctrl_info->pci_dev->dev,
			"PQI reset failed with error %d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_get_ctrl_serial_number(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	काष्ठा bmic_sense_subप्रणाली_info *sense_info;

	sense_info = kzalloc(माप(*sense_info), GFP_KERNEL);
	अगर (!sense_info)
		वापस -ENOMEM;

	rc = pqi_sense_subप्रणाली_info(ctrl_info, sense_info);
	अगर (rc)
		जाओ out;

	स_नकल(ctrl_info->serial_number, sense_info->ctrl_serial_number,
		माप(sense_info->ctrl_serial_number));
	ctrl_info->serial_number[माप(sense_info->ctrl_serial_number)] = '\0';

out:
	kमुक्त(sense_info);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_get_ctrl_product_details(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	काष्ठा bmic_identअगरy_controller *identअगरy;

	identअगरy = kदो_स्मृति(माप(*identअगरy), GFP_KERNEL);
	अगर (!identअगरy)
		वापस -ENOMEM;

	rc = pqi_identअगरy_controller(ctrl_info, identअगरy);
	अगर (rc)
		जाओ out;

	अगर (get_unaligned_le32(&identअगरy->extra_controller_flags) &
		BMIC_IDENTIFY_EXTRA_FLAGS_LONG_FW_VERSION_SUPPORTED) अणु
		स_नकल(ctrl_info->firmware_version,
			identअगरy->firmware_version_दीर्घ,
			माप(identअगरy->firmware_version_दीर्घ));
	पूर्ण अन्यथा अणु
		स_नकल(ctrl_info->firmware_version,
			identअगरy->firmware_version_लघु,
			माप(identअगरy->firmware_version_लघु));
		ctrl_info->firmware_version
			[माप(identअगरy->firmware_version_लघु)] = '\0';
		snम_लिखो(ctrl_info->firmware_version +
			म_माप(ctrl_info->firmware_version),
			माप(ctrl_info->firmware_version) -
			माप(identअगरy->firmware_version_लघु),
			"-%u",
			get_unaligned_le16(&identअगरy->firmware_build_number));
	पूर्ण

	स_नकल(ctrl_info->model, identअगरy->product_id,
		माप(identअगरy->product_id));
	ctrl_info->model[माप(identअगरy->product_id)] = '\0';

	स_नकल(ctrl_info->venकरोr, identअगरy->venकरोr_id,
		माप(identअगरy->venकरोr_id));
	ctrl_info->venकरोr[माप(identअगरy->venकरोr_id)] = '\0';

out:
	kमुक्त(identअगरy);

	वापस rc;
पूर्ण

काष्ठा pqi_config_table_section_info अणु
	काष्ठा pqi_ctrl_info *ctrl_info;
	व्योम		*section;
	u32		section_offset;
	व्योम __iomem	*section_iomem_addr;
पूर्ण;

अटल अंतरभूत bool pqi_is_firmware_feature_supported(
	काष्ठा pqi_config_table_firmware_features *firmware_features,
	अचिन्हित पूर्णांक bit_position)
अणु
	अचिन्हित पूर्णांक byte_index;

	byte_index = bit_position / BITS_PER_BYTE;

	अगर (byte_index >= le16_to_cpu(firmware_features->num_elements))
		वापस false;

	वापस firmware_features->features_supported[byte_index] &
		(1 << (bit_position % BITS_PER_BYTE)) ? true : false;
पूर्ण

अटल अंतरभूत bool pqi_is_firmware_feature_enabled(
	काष्ठा pqi_config_table_firmware_features *firmware_features,
	व्योम __iomem *firmware_features_iomem_addr,
	अचिन्हित पूर्णांक bit_position)
अणु
	अचिन्हित पूर्णांक byte_index;
	u8 __iomem *features_enabled_iomem_addr;

	byte_index = (bit_position / BITS_PER_BYTE) +
		(le16_to_cpu(firmware_features->num_elements) * 2);

	features_enabled_iomem_addr = firmware_features_iomem_addr +
		दुरत्व(काष्ठा pqi_config_table_firmware_features,
			features_supported) + byte_index;

	वापस *((__क्रमce u8 *)features_enabled_iomem_addr) &
		(1 << (bit_position % BITS_PER_BYTE)) ? true : false;
पूर्ण

अटल अंतरभूत व्योम pqi_request_firmware_feature(
	काष्ठा pqi_config_table_firmware_features *firmware_features,
	अचिन्हित पूर्णांक bit_position)
अणु
	अचिन्हित पूर्णांक byte_index;

	byte_index = (bit_position / BITS_PER_BYTE) +
		le16_to_cpu(firmware_features->num_elements);

	firmware_features->features_supported[byte_index] |=
		(1 << (bit_position % BITS_PER_BYTE));
पूर्ण

अटल पूर्णांक pqi_config_table_update(काष्ठा pqi_ctrl_info *ctrl_info,
	u16 first_section, u16 last_section)
अणु
	काष्ठा pqi_venकरोr_general_request request;

	स_रखो(&request, 0, माप(request));

	request.header.iu_type = PQI_REQUEST_IU_VENDOR_GENERAL;
	put_unaligned_le16(माप(request) - PQI_REQUEST_HEADER_LENGTH,
		&request.header.iu_length);
	put_unaligned_le16(PQI_VENDOR_GENERAL_CONFIG_TABLE_UPDATE,
		&request.function_code);
	put_unaligned_le16(first_section,
		&request.data.config_table_update.first_section);
	put_unaligned_le16(last_section,
		&request.data.config_table_update.last_section);

	वापस pqi_submit_raid_request_synchronous(ctrl_info, &request.header, 0, शून्य);
पूर्ण

अटल पूर्णांक pqi_enable_firmware_features(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_config_table_firmware_features *firmware_features,
	व्योम __iomem *firmware_features_iomem_addr)
अणु
	व्योम *features_requested;
	व्योम __iomem *features_requested_iomem_addr;
	व्योम __iomem *host_max_known_feature_iomem_addr;

	features_requested = firmware_features->features_supported +
		le16_to_cpu(firmware_features->num_elements);

	features_requested_iomem_addr = firmware_features_iomem_addr +
		(features_requested - (व्योम *)firmware_features);

	स_नकल_toio(features_requested_iomem_addr, features_requested,
		le16_to_cpu(firmware_features->num_elements));

	अगर (pqi_is_firmware_feature_supported(firmware_features,
		PQI_FIRMWARE_FEATURE_MAX_KNOWN_FEATURE)) अणु
		host_max_known_feature_iomem_addr =
			features_requested_iomem_addr +
			(le16_to_cpu(firmware_features->num_elements) * 2) +
			माप(__le16);
		ग_लिखोw(PQI_FIRMWARE_FEATURE_MAXIMUM,
			host_max_known_feature_iomem_addr);
	पूर्ण

	वापस pqi_config_table_update(ctrl_info,
		PQI_CONFIG_TABLE_SECTION_FIRMWARE_FEATURES,
		PQI_CONFIG_TABLE_SECTION_FIRMWARE_FEATURES);
पूर्ण

काष्ठा pqi_firmware_feature अणु
	अक्षर		*feature_name;
	अचिन्हित पूर्णांक	feature_bit;
	bool		supported;
	bool		enabled;
	व्योम (*feature_status)(काष्ठा pqi_ctrl_info *ctrl_info,
		काष्ठा pqi_firmware_feature *firmware_feature);
पूर्ण;

अटल व्योम pqi_firmware_feature_status(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_firmware_feature *firmware_feature)
अणु
	अगर (!firmware_feature->supported) अणु
		dev_info(&ctrl_info->pci_dev->dev, "%s not supported by controller\n",
			firmware_feature->feature_name);
		वापस;
	पूर्ण

	अगर (firmware_feature->enabled) अणु
		dev_info(&ctrl_info->pci_dev->dev,
			"%s enabled\n", firmware_feature->feature_name);
		वापस;
	पूर्ण

	dev_err(&ctrl_info->pci_dev->dev, "failed to enable %s\n",
		firmware_feature->feature_name);
पूर्ण

अटल व्योम pqi_ctrl_update_feature_flags(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_firmware_feature *firmware_feature)
अणु
	चयन (firmware_feature->feature_bit) अणु
	हाल PQI_FIRMWARE_FEATURE_RAID_1_WRITE_BYPASS:
		ctrl_info->enable_r1_ग_लिखोs = firmware_feature->enabled;
		अवरोध;
	हाल PQI_FIRMWARE_FEATURE_RAID_5_WRITE_BYPASS:
		ctrl_info->enable_r5_ग_लिखोs = firmware_feature->enabled;
		अवरोध;
	हाल PQI_FIRMWARE_FEATURE_RAID_6_WRITE_BYPASS:
		ctrl_info->enable_r6_ग_लिखोs = firmware_feature->enabled;
		अवरोध;
	हाल PQI_FIRMWARE_FEATURE_SOFT_RESET_HANDSHAKE:
		ctrl_info->soft_reset_handshake_supported =
			firmware_feature->enabled &&
			pqi_पढ़ो_soft_reset_status(ctrl_info);
		अवरोध;
	हाल PQI_FIRMWARE_FEATURE_RAID_IU_TIMEOUT:
		ctrl_info->raid_iu_समयout_supported = firmware_feature->enabled;
		अवरोध;
	हाल PQI_FIRMWARE_FEATURE_TMF_IU_TIMEOUT:
		ctrl_info->पंचांगf_iu_समयout_supported = firmware_feature->enabled;
		अवरोध;
	हाल PQI_FIRMWARE_FEATURE_UNIQUE_WWID_IN_REPORT_PHYS_LUN:
		ctrl_info->unique_wwid_in_report_phys_lun_supported =
			firmware_feature->enabled;
		अवरोध;
	पूर्ण

	pqi_firmware_feature_status(ctrl_info, firmware_feature);
पूर्ण

अटल अंतरभूत व्योम pqi_firmware_feature_update(काष्ठा pqi_ctrl_info *ctrl_info,
	काष्ठा pqi_firmware_feature *firmware_feature)
अणु
	अगर (firmware_feature->feature_status)
		firmware_feature->feature_status(ctrl_info, firmware_feature);
पूर्ण

अटल DEFINE_MUTEX(pqi_firmware_features_mutex);

अटल काष्ठा pqi_firmware_feature pqi_firmware_features[] = अणु
	अणु
		.feature_name = "Online Firmware Activation",
		.feature_bit = PQI_FIRMWARE_FEATURE_OFA,
		.feature_status = pqi_firmware_feature_status,
	पूर्ण,
	अणु
		.feature_name = "Serial Management Protocol",
		.feature_bit = PQI_FIRMWARE_FEATURE_SMP,
		.feature_status = pqi_firmware_feature_status,
	पूर्ण,
	अणु
		.feature_name = "Maximum Known Feature",
		.feature_bit = PQI_FIRMWARE_FEATURE_MAX_KNOWN_FEATURE,
		.feature_status = pqi_firmware_feature_status,
	पूर्ण,
	अणु
		.feature_name = "RAID 0 Read Bypass",
		.feature_bit = PQI_FIRMWARE_FEATURE_RAID_0_READ_BYPASS,
		.feature_status = pqi_firmware_feature_status,
	पूर्ण,
	अणु
		.feature_name = "RAID 1 Read Bypass",
		.feature_bit = PQI_FIRMWARE_FEATURE_RAID_1_READ_BYPASS,
		.feature_status = pqi_firmware_feature_status,
	पूर्ण,
	अणु
		.feature_name = "RAID 5 Read Bypass",
		.feature_bit = PQI_FIRMWARE_FEATURE_RAID_5_READ_BYPASS,
		.feature_status = pqi_firmware_feature_status,
	पूर्ण,
	अणु
		.feature_name = "RAID 6 Read Bypass",
		.feature_bit = PQI_FIRMWARE_FEATURE_RAID_6_READ_BYPASS,
		.feature_status = pqi_firmware_feature_status,
	पूर्ण,
	अणु
		.feature_name = "RAID 0 Write Bypass",
		.feature_bit = PQI_FIRMWARE_FEATURE_RAID_0_WRITE_BYPASS,
		.feature_status = pqi_firmware_feature_status,
	पूर्ण,
	अणु
		.feature_name = "RAID 1 Write Bypass",
		.feature_bit = PQI_FIRMWARE_FEATURE_RAID_1_WRITE_BYPASS,
		.feature_status = pqi_ctrl_update_feature_flags,
	पूर्ण,
	अणु
		.feature_name = "RAID 5 Write Bypass",
		.feature_bit = PQI_FIRMWARE_FEATURE_RAID_5_WRITE_BYPASS,
		.feature_status = pqi_ctrl_update_feature_flags,
	पूर्ण,
	अणु
		.feature_name = "RAID 6 Write Bypass",
		.feature_bit = PQI_FIRMWARE_FEATURE_RAID_6_WRITE_BYPASS,
		.feature_status = pqi_ctrl_update_feature_flags,
	पूर्ण,
	अणु
		.feature_name = "New Soft Reset Handshake",
		.feature_bit = PQI_FIRMWARE_FEATURE_SOFT_RESET_HANDSHAKE,
		.feature_status = pqi_ctrl_update_feature_flags,
	पूर्ण,
	अणु
		.feature_name = "RAID IU Timeout",
		.feature_bit = PQI_FIRMWARE_FEATURE_RAID_IU_TIMEOUT,
		.feature_status = pqi_ctrl_update_feature_flags,
	पूर्ण,
	अणु
		.feature_name = "TMF IU Timeout",
		.feature_bit = PQI_FIRMWARE_FEATURE_TMF_IU_TIMEOUT,
		.feature_status = pqi_ctrl_update_feature_flags,
	पूर्ण,
	अणु
		.feature_name = "RAID Bypass on encrypted logical volumes on NVMe",
		.feature_bit = PQI_FIRMWARE_FEATURE_RAID_BYPASS_ON_ENCRYPTED_NVME,
		.feature_status = pqi_firmware_feature_status,
	पूर्ण,
	अणु
		.feature_name = "Unique WWID in Report Physical LUN",
		.feature_bit = PQI_FIRMWARE_FEATURE_UNIQUE_WWID_IN_REPORT_PHYS_LUN,
		.feature_status = pqi_ctrl_update_feature_flags,
	पूर्ण,
पूर्ण;

अटल व्योम pqi_process_firmware_features(
	काष्ठा pqi_config_table_section_info *section_info)
अणु
	पूर्णांक rc;
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा pqi_config_table_firmware_features *firmware_features;
	व्योम __iomem *firmware_features_iomem_addr;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक num_features_supported;

	ctrl_info = section_info->ctrl_info;
	firmware_features = section_info->section;
	firmware_features_iomem_addr = section_info->section_iomem_addr;

	क्रम (i = 0, num_features_supported = 0;
		i < ARRAY_SIZE(pqi_firmware_features); i++) अणु
		अगर (pqi_is_firmware_feature_supported(firmware_features,
			pqi_firmware_features[i].feature_bit)) अणु
			pqi_firmware_features[i].supported = true;
			num_features_supported++;
		पूर्ण अन्यथा अणु
			pqi_firmware_feature_update(ctrl_info,
				&pqi_firmware_features[i]);
		पूर्ण
	पूर्ण

	अगर (num_features_supported == 0)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(pqi_firmware_features); i++) अणु
		अगर (!pqi_firmware_features[i].supported)
			जारी;
		pqi_request_firmware_feature(firmware_features,
			pqi_firmware_features[i].feature_bit);
	पूर्ण

	rc = pqi_enable_firmware_features(ctrl_info, firmware_features,
		firmware_features_iomem_addr);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to enable firmware features in PQI configuration table\n");
		क्रम (i = 0; i < ARRAY_SIZE(pqi_firmware_features); i++) अणु
			अगर (!pqi_firmware_features[i].supported)
				जारी;
			pqi_firmware_feature_update(ctrl_info,
				&pqi_firmware_features[i]);
		पूर्ण
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(pqi_firmware_features); i++) अणु
		अगर (!pqi_firmware_features[i].supported)
			जारी;
		अगर (pqi_is_firmware_feature_enabled(firmware_features,
			firmware_features_iomem_addr,
			pqi_firmware_features[i].feature_bit)) अणु
				pqi_firmware_features[i].enabled = true;
		पूर्ण
		pqi_firmware_feature_update(ctrl_info,
			&pqi_firmware_features[i]);
	पूर्ण
पूर्ण

अटल व्योम pqi_init_firmware_features(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pqi_firmware_features); i++) अणु
		pqi_firmware_features[i].supported = false;
		pqi_firmware_features[i].enabled = false;
	पूर्ण
पूर्ण

अटल व्योम pqi_process_firmware_features_section(
	काष्ठा pqi_config_table_section_info *section_info)
अणु
	mutex_lock(&pqi_firmware_features_mutex);
	pqi_init_firmware_features();
	pqi_process_firmware_features(section_info);
	mutex_unlock(&pqi_firmware_features_mutex);
पूर्ण

/*
 * Reset all controller settings that can be initialized during the processing
 * of the PQI Configuration Table.
 */

अटल व्योम pqi_ctrl_reset_config(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	ctrl_info->heartbeat_counter = शून्य;
	ctrl_info->soft_reset_status = शून्य;
	ctrl_info->soft_reset_handshake_supported = false;
	ctrl_info->enable_r1_ग_लिखोs = false;
	ctrl_info->enable_r5_ग_लिखोs = false;
	ctrl_info->enable_r6_ग_लिखोs = false;
	ctrl_info->raid_iu_समयout_supported = false;
	ctrl_info->पंचांगf_iu_समयout_supported = false;
	ctrl_info->unique_wwid_in_report_phys_lun_supported = false;
पूर्ण

अटल पूर्णांक pqi_process_config_table(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	u32 table_length;
	u32 section_offset;
	bool firmware_feature_section_present;
	व्योम __iomem *table_iomem_addr;
	काष्ठा pqi_config_table *config_table;
	काष्ठा pqi_config_table_section_header *section;
	काष्ठा pqi_config_table_section_info section_info;
	काष्ठा pqi_config_table_section_info feature_section_info;

	table_length = ctrl_info->config_table_length;
	अगर (table_length == 0)
		वापस 0;

	config_table = kदो_स्मृति(table_length, GFP_KERNEL);
	अगर (!config_table) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to allocate memory for PQI configuration table\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Copy the config table contents from I/O memory space पूर्णांकo the
	 * temporary buffer.
	 */
	table_iomem_addr = ctrl_info->iomem_base + ctrl_info->config_table_offset;
	स_नकल_fromio(config_table, table_iomem_addr, table_length);

	firmware_feature_section_present = false;
	section_info.ctrl_info = ctrl_info;
	section_offset = get_unaligned_le32(&config_table->first_section_offset);

	जबतक (section_offset) अणु
		section = (व्योम *)config_table + section_offset;

		section_info.section = section;
		section_info.section_offset = section_offset;
		section_info.section_iomem_addr = table_iomem_addr + section_offset;

		चयन (get_unaligned_le16(&section->section_id)) अणु
		हाल PQI_CONFIG_TABLE_SECTION_FIRMWARE_FEATURES:
			firmware_feature_section_present = true;
			feature_section_info = section_info;
			अवरोध;
		हाल PQI_CONFIG_TABLE_SECTION_HEARTBEAT:
			अगर (pqi_disable_heartbeat)
				dev_warn(&ctrl_info->pci_dev->dev,
				"heartbeat disabled by module parameter\n");
			अन्यथा
				ctrl_info->heartbeat_counter =
					table_iomem_addr +
					section_offset +
					दुरत्व(काष्ठा pqi_config_table_heartbeat,
						heartbeat_counter);
			अवरोध;
		हाल PQI_CONFIG_TABLE_SECTION_SOFT_RESET:
			ctrl_info->soft_reset_status =
				table_iomem_addr +
				section_offset +
				दुरत्व(काष्ठा pqi_config_table_soft_reset,
					soft_reset_status);
			अवरोध;
		पूर्ण

		section_offset = get_unaligned_le16(&section->next_section_offset);
	पूर्ण

	/*
	 * We process the firmware feature section after all other sections
	 * have been processed so that the feature bit callbacks can take
	 * पूर्णांकo account the settings configured by other sections.
	 */
	अगर (firmware_feature_section_present)
		pqi_process_firmware_features_section(&feature_section_info);

	kमुक्त(config_table);

	वापस 0;
पूर्ण

/* Switches the controller from PQI mode back पूर्णांकo SIS mode. */

अटल पूर्णांक pqi_revert_to_sis_mode(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;

	pqi_change_irq_mode(ctrl_info, IRQ_MODE_NONE);
	rc = pqi_reset(ctrl_info);
	अगर (rc)
		वापस rc;
	rc = sis_reenable_sis_mode(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"re-enabling SIS mode failed with error %d\n", rc);
		वापस rc;
	पूर्ण
	pqi_save_ctrl_mode(ctrl_info, SIS_MODE);

	वापस 0;
पूर्ण

/*
 * If the controller isn't alपढ़ोy in SIS mode, this function क्रमces it पूर्णांकo
 * SIS mode.
 */

अटल पूर्णांक pqi_क्रमce_sis_mode(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अगर (!sis_is_firmware_running(ctrl_info))
		वापस -ENXIO;

	अगर (pqi_get_ctrl_mode(ctrl_info) == SIS_MODE)
		वापस 0;

	अगर (sis_is_kernel_up(ctrl_info)) अणु
		pqi_save_ctrl_mode(ctrl_info, SIS_MODE);
		वापस 0;
	पूर्ण

	वापस pqi_revert_to_sis_mode(ctrl_info);
पूर्ण

अटल पूर्णांक pqi_ctrl_init(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	u32 product_id;

	अगर (reset_devices) अणु
		sis_soft_reset(ctrl_info);
		msleep(PQI_POST_RESET_DELAY_SECS * PQI_HZ);
	पूर्ण अन्यथा अणु
		rc = pqi_क्रमce_sis_mode(ctrl_info);
		अगर (rc)
			वापस rc;
	पूर्ण

	/*
	 * Wait until the controller is पढ़ोy to start accepting SIS
	 * commands.
	 */
	rc = sis_रुको_क्रम_ctrl_पढ़ोy(ctrl_info);
	अगर (rc)
		वापस rc;

	/*
	 * Get the controller properties.  This allows us to determine
	 * whether or not it supports PQI mode.
	 */
	rc = sis_get_ctrl_properties(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining controller properties\n");
		वापस rc;
	पूर्ण

	rc = sis_get_pqi_capabilities(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining controller capabilities\n");
		वापस rc;
	पूर्ण

	product_id = sis_get_product_id(ctrl_info);
	ctrl_info->product_id = (u8)product_id;
	ctrl_info->product_revision = (u8)(product_id >> 8);

	अगर (reset_devices) अणु
		अगर (ctrl_info->max_outstanding_requests >
			PQI_MAX_OUTSTANDING_REQUESTS_KDUMP)
				ctrl_info->max_outstanding_requests =
					PQI_MAX_OUTSTANDING_REQUESTS_KDUMP;
	पूर्ण अन्यथा अणु
		अगर (ctrl_info->max_outstanding_requests >
			PQI_MAX_OUTSTANDING_REQUESTS)
				ctrl_info->max_outstanding_requests =
					PQI_MAX_OUTSTANDING_REQUESTS;
	पूर्ण

	pqi_calculate_io_resources(ctrl_info);

	rc = pqi_alloc_error_buffer(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to allocate PQI error buffer\n");
		वापस rc;
	पूर्ण

	/*
	 * If the function we are about to call succeeds, the
	 * controller will transition from legacy SIS mode
	 * पूर्णांकo PQI mode.
	 */
	rc = sis_init_base_काष्ठा_addr(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error initializing PQI mode\n");
		वापस rc;
	पूर्ण

	/* Wait क्रम the controller to complete the SIS -> PQI transition. */
	rc = pqi_रुको_क्रम_pqi_mode_पढ़ोy(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"transition to PQI mode failed\n");
		वापस rc;
	पूर्ण

	/* From here on, we are running in PQI mode. */
	ctrl_info->pqi_mode_enabled = true;
	pqi_save_ctrl_mode(ctrl_info, PQI_MODE);

	rc = pqi_alloc_admin_queues(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to allocate admin queues\n");
		वापस rc;
	पूर्ण

	rc = pqi_create_admin_queues(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error creating admin queues\n");
		वापस rc;
	पूर्ण

	rc = pqi_report_device_capability(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"obtaining device capability failed\n");
		वापस rc;
	पूर्ण

	rc = pqi_validate_device_capability(ctrl_info);
	अगर (rc)
		वापस rc;

	pqi_calculate_queue_resources(ctrl_info);

	rc = pqi_enable_msix_पूर्णांकerrupts(ctrl_info);
	अगर (rc)
		वापस rc;

	अगर (ctrl_info->num_msix_vectors_enabled < ctrl_info->num_queue_groups) अणु
		ctrl_info->max_msix_vectors =
			ctrl_info->num_msix_vectors_enabled;
		pqi_calculate_queue_resources(ctrl_info);
	पूर्ण

	rc = pqi_alloc_io_resources(ctrl_info);
	अगर (rc)
		वापस rc;

	rc = pqi_alloc_operational_queues(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to allocate operational queues\n");
		वापस rc;
	पूर्ण

	pqi_init_operational_queues(ctrl_info);

	rc = pqi_request_irqs(ctrl_info);
	अगर (rc)
		वापस rc;

	rc = pqi_create_queues(ctrl_info);
	अगर (rc)
		वापस rc;

	pqi_change_irq_mode(ctrl_info, IRQ_MODE_MSIX);

	ctrl_info->controller_online = true;

	rc = pqi_process_config_table(ctrl_info);
	अगर (rc)
		वापस rc;

	pqi_start_heartbeat_समयr(ctrl_info);

	अगर (ctrl_info->enable_r5_ग_लिखोs || ctrl_info->enable_r6_ग_लिखोs) अणु
		rc = pqi_get_advanced_raid_bypass_config(ctrl_info);
		अगर (rc) अणु /* Supported features not वापसed correctly. */
			dev_err(&ctrl_info->pci_dev->dev,
				"error obtaining advanced RAID bypass configuration\n");
			वापस rc;
		पूर्ण
		ctrl_info->ciss_report_log_flags |=
			CISS_REPORT_LOG_FLAG_DRIVE_TYPE_MIX;
	पूर्ण

	rc = pqi_enable_events(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error enabling events\n");
		वापस rc;
	पूर्ण

	/* Register with the SCSI subप्रणाली. */
	rc = pqi_रेजिस्टर_scsi(ctrl_info);
	अगर (rc)
		वापस rc;

	rc = pqi_get_ctrl_product_details(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining product details\n");
		वापस rc;
	पूर्ण

	rc = pqi_get_ctrl_serial_number(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining ctrl serial number\n");
		वापस rc;
	पूर्ण

	rc = pqi_set_diag_rescan(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error enabling multi-lun rescan\n");
		वापस rc;
	पूर्ण

	rc = pqi_ग_लिखो_driver_version_to_host_wellness(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error updating host wellness\n");
		वापस rc;
	पूर्ण

	pqi_schedule_update_समय_worker(ctrl_info);

	pqi_scan_scsi_devices(ctrl_info);

	वापस 0;
पूर्ण

अटल व्योम pqi_reinit_queues(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा pqi_admin_queues *admin_queues;
	काष्ठा pqi_event_queue *event_queue;

	admin_queues = &ctrl_info->admin_queues;
	admin_queues->iq_pi_copy = 0;
	admin_queues->oq_ci_copy = 0;
	ग_लिखोl(0, admin_queues->oq_pi);

	क्रम (i = 0; i < ctrl_info->num_queue_groups; i++) अणु
		ctrl_info->queue_groups[i].iq_pi_copy[RAID_PATH] = 0;
		ctrl_info->queue_groups[i].iq_pi_copy[AIO_PATH] = 0;
		ctrl_info->queue_groups[i].oq_ci_copy = 0;

		ग_लिखोl(0, ctrl_info->queue_groups[i].iq_ci[RAID_PATH]);
		ग_लिखोl(0, ctrl_info->queue_groups[i].iq_ci[AIO_PATH]);
		ग_लिखोl(0, ctrl_info->queue_groups[i].oq_pi);
	पूर्ण

	event_queue = &ctrl_info->event_queue;
	ग_लिखोl(0, event_queue->oq_pi);
	event_queue->oq_ci_copy = 0;
पूर्ण

अटल पूर्णांक pqi_ctrl_init_resume(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;

	rc = pqi_क्रमce_sis_mode(ctrl_info);
	अगर (rc)
		वापस rc;

	/*
	 * Wait until the controller is पढ़ोy to start accepting SIS
	 * commands.
	 */
	rc = sis_रुको_क्रम_ctrl_पढ़ोy_resume(ctrl_info);
	अगर (rc)
		वापस rc;

	/*
	 * Get the controller properties.  This allows us to determine
	 * whether or not it supports PQI mode.
	 */
	rc = sis_get_ctrl_properties(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining controller properties\n");
		वापस rc;
	पूर्ण

	rc = sis_get_pqi_capabilities(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining controller capabilities\n");
		वापस rc;
	पूर्ण

	/*
	 * If the function we are about to call succeeds, the
	 * controller will transition from legacy SIS mode
	 * पूर्णांकo PQI mode.
	 */
	rc = sis_init_base_काष्ठा_addr(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error initializing PQI mode\n");
		वापस rc;
	पूर्ण

	/* Wait क्रम the controller to complete the SIS -> PQI transition. */
	rc = pqi_रुको_क्रम_pqi_mode_पढ़ोy(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"transition to PQI mode failed\n");
		वापस rc;
	पूर्ण

	/* From here on, we are running in PQI mode. */
	ctrl_info->pqi_mode_enabled = true;
	pqi_save_ctrl_mode(ctrl_info, PQI_MODE);

	pqi_reinit_queues(ctrl_info);

	rc = pqi_create_admin_queues(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error creating admin queues\n");
		वापस rc;
	पूर्ण

	rc = pqi_create_queues(ctrl_info);
	अगर (rc)
		वापस rc;

	pqi_change_irq_mode(ctrl_info, IRQ_MODE_MSIX);

	ctrl_info->controller_online = true;
	pqi_ctrl_unblock_requests(ctrl_info);

	pqi_ctrl_reset_config(ctrl_info);

	rc = pqi_process_config_table(ctrl_info);
	अगर (rc)
		वापस rc;

	pqi_start_heartbeat_समयr(ctrl_info);

	अगर (ctrl_info->enable_r5_ग_लिखोs || ctrl_info->enable_r6_ग_लिखोs) अणु
		rc = pqi_get_advanced_raid_bypass_config(ctrl_info);
		अगर (rc) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"error obtaining advanced RAID bypass configuration\n");
			वापस rc;
		पूर्ण
		ctrl_info->ciss_report_log_flags |=
			CISS_REPORT_LOG_FLAG_DRIVE_TYPE_MIX;
	पूर्ण

	rc = pqi_enable_events(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error enabling events\n");
		वापस rc;
	पूर्ण

	rc = pqi_get_ctrl_product_details(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining product details\n");
		वापस rc;
	पूर्ण

	rc = pqi_set_diag_rescan(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error enabling multi-lun rescan\n");
		वापस rc;
	पूर्ण

	rc = pqi_ग_लिखो_driver_version_to_host_wellness(ctrl_info);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"error updating host wellness\n");
		वापस rc;
	पूर्ण

	अगर (pqi_ofa_in_progress(ctrl_info))
		pqi_ctrl_unblock_scan(ctrl_info);

	pqi_scan_scsi_devices(ctrl_info);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pqi_set_pcie_completion_समयout(काष्ठा pci_dev *pci_dev, u16 समयout)
अणु
	पूर्णांक rc;

	rc = pcie_capability_clear_and_set_word(pci_dev, PCI_EXP_DEVCTL2,
		PCI_EXP_DEVCTL2_COMP_TIMEOUT, समयout);

	वापस pcibios_err_to_त्रुटि_सं(rc);
पूर्ण

अटल पूर्णांक pqi_pci_init(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	u64 mask;

	rc = pci_enable_device(ctrl_info->pci_dev);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to enable PCI device\n");
		वापस rc;
	पूर्ण

	अगर (माप(dma_addr_t) > 4)
		mask = DMA_BIT_MASK(64);
	अन्यथा
		mask = DMA_BIT_MASK(32);

	rc = dma_set_mask_and_coherent(&ctrl_info->pci_dev->dev, mask);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev, "failed to set DMA mask\n");
		जाओ disable_device;
	पूर्ण

	rc = pci_request_regions(ctrl_info->pci_dev, DRIVER_NAME_SHORT);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to obtain PCI resources\n");
		जाओ disable_device;
	पूर्ण

	ctrl_info->iomem_base = ioremap(pci_resource_start(
		ctrl_info->pci_dev, 0),
		माप(काष्ठा pqi_ctrl_रेजिस्टरs));
	अगर (!ctrl_info->iomem_base) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to map memory for controller registers\n");
		rc = -ENOMEM;
		जाओ release_regions;
	पूर्ण

#घोषणा PCI_EXP_COMP_TIMEOUT_65_TO_210_MS		0x6

	/* Increase the PCIe completion समयout. */
	rc = pqi_set_pcie_completion_समयout(ctrl_info->pci_dev,
		PCI_EXP_COMP_TIMEOUT_65_TO_210_MS);
	अगर (rc) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to set PCIe completion timeout\n");
		जाओ release_regions;
	पूर्ण

	/* Enable bus mastering. */
	pci_set_master(ctrl_info->pci_dev);

	ctrl_info->रेजिस्टरs = ctrl_info->iomem_base;
	ctrl_info->pqi_रेजिस्टरs = &ctrl_info->रेजिस्टरs->pqi_रेजिस्टरs;

	pci_set_drvdata(ctrl_info->pci_dev, ctrl_info);

	वापस 0;

release_regions:
	pci_release_regions(ctrl_info->pci_dev);
disable_device:
	pci_disable_device(ctrl_info->pci_dev);

	वापस rc;
पूर्ण

अटल व्योम pqi_cleanup_pci_init(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	iounmap(ctrl_info->iomem_base);
	pci_release_regions(ctrl_info->pci_dev);
	अगर (pci_is_enabled(ctrl_info->pci_dev))
		pci_disable_device(ctrl_info->pci_dev);
	pci_set_drvdata(ctrl_info->pci_dev, शून्य);
पूर्ण

अटल काष्ठा pqi_ctrl_info *pqi_alloc_ctrl_info(पूर्णांक numa_node)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = kzalloc_node(माप(काष्ठा pqi_ctrl_info),
			GFP_KERNEL, numa_node);
	अगर (!ctrl_info)
		वापस शून्य;

	mutex_init(&ctrl_info->scan_mutex);
	mutex_init(&ctrl_info->lun_reset_mutex);
	mutex_init(&ctrl_info->ofa_mutex);

	INIT_LIST_HEAD(&ctrl_info->scsi_device_list);
	spin_lock_init(&ctrl_info->scsi_device_list_lock);

	INIT_WORK(&ctrl_info->event_work, pqi_event_worker);
	atomic_set(&ctrl_info->num_पूर्णांकerrupts, 0);

	INIT_DELAYED_WORK(&ctrl_info->rescan_work, pqi_rescan_worker);
	INIT_DELAYED_WORK(&ctrl_info->update_समय_work, pqi_update_समय_worker);

	समयr_setup(&ctrl_info->heartbeat_समयr, pqi_heartbeat_समयr_handler, 0);
	INIT_WORK(&ctrl_info->ctrl_offline_work, pqi_ctrl_offline_worker);

	INIT_WORK(&ctrl_info->ofa_memory_alloc_work, pqi_ofa_memory_alloc_worker);
	INIT_WORK(&ctrl_info->ofa_quiesce_work, pqi_ofa_quiesce_worker);

	sema_init(&ctrl_info->sync_request_sem,
		PQI_RESERVED_IO_SLOTS_SYNCHRONOUS_REQUESTS);
	init_रुकोqueue_head(&ctrl_info->block_requests_रुको);

	ctrl_info->ctrl_id = atomic_inc_वापस(&pqi_controller_count) - 1;
	ctrl_info->irq_mode = IRQ_MODE_NONE;
	ctrl_info->max_msix_vectors = PQI_MAX_MSIX_VECTORS;

	ctrl_info->ciss_report_log_flags = CISS_REPORT_LOG_FLAG_UNIQUE_LUN_ID;
	ctrl_info->max_transfer_encrypted_sas_sata =
		PQI_DEFAULT_MAX_TRANSFER_ENCRYPTED_SAS_SATA;
	ctrl_info->max_transfer_encrypted_nvme =
		PQI_DEFAULT_MAX_TRANSFER_ENCRYPTED_NVME;
	ctrl_info->max_ग_लिखो_raid_5_6 = PQI_DEFAULT_MAX_WRITE_RAID_5_6;
	ctrl_info->max_ग_लिखो_raid_1_10_2drive = ~0;
	ctrl_info->max_ग_लिखो_raid_1_10_3drive = ~0;

	वापस ctrl_info;
पूर्ण

अटल अंतरभूत व्योम pqi_मुक्त_ctrl_info(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	kमुक्त(ctrl_info);
पूर्ण

अटल व्योम pqi_मुक्त_पूर्णांकerrupts(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	pqi_मुक्त_irqs(ctrl_info);
	pqi_disable_msix_पूर्णांकerrupts(ctrl_info);
पूर्ण

अटल व्योम pqi_मुक्त_ctrl_resources(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	pqi_stop_heartbeat_समयr(ctrl_info);
	pqi_मुक्त_पूर्णांकerrupts(ctrl_info);
	अगर (ctrl_info->queue_memory_base)
		dma_मुक्त_coherent(&ctrl_info->pci_dev->dev,
			ctrl_info->queue_memory_length,
			ctrl_info->queue_memory_base,
			ctrl_info->queue_memory_base_dma_handle);
	अगर (ctrl_info->admin_queue_memory_base)
		dma_मुक्त_coherent(&ctrl_info->pci_dev->dev,
			ctrl_info->admin_queue_memory_length,
			ctrl_info->admin_queue_memory_base,
			ctrl_info->admin_queue_memory_base_dma_handle);
	pqi_मुक्त_all_io_requests(ctrl_info);
	अगर (ctrl_info->error_buffer)
		dma_मुक्त_coherent(&ctrl_info->pci_dev->dev,
			ctrl_info->error_buffer_length,
			ctrl_info->error_buffer,
			ctrl_info->error_buffer_dma_handle);
	अगर (ctrl_info->iomem_base)
		pqi_cleanup_pci_init(ctrl_info);
	pqi_मुक्त_ctrl_info(ctrl_info);
पूर्ण

अटल व्योम pqi_हटाओ_ctrl(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	pqi_cancel_rescan_worker(ctrl_info);
	pqi_cancel_update_समय_worker(ctrl_info);
	pqi_unरेजिस्टर_scsi(ctrl_info);
	अगर (ctrl_info->pqi_mode_enabled)
		pqi_revert_to_sis_mode(ctrl_info);
	pqi_मुक्त_ctrl_resources(ctrl_info);
पूर्ण

अटल व्योम pqi_ofa_ctrl_quiesce(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	pqi_ctrl_block_scan(ctrl_info);
	pqi_scsi_block_requests(ctrl_info);
	pqi_ctrl_block_device_reset(ctrl_info);
	pqi_ctrl_block_requests(ctrl_info);
	pqi_ctrl_रुको_until_quiesced(ctrl_info);
	pqi_stop_heartbeat_समयr(ctrl_info);
पूर्ण

अटल व्योम pqi_ofa_ctrl_unquiesce(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	pqi_start_heartbeat_समयr(ctrl_info);
	pqi_ctrl_unblock_requests(ctrl_info);
	pqi_ctrl_unblock_device_reset(ctrl_info);
	pqi_scsi_unblock_requests(ctrl_info);
	pqi_ctrl_unblock_scan(ctrl_info);
पूर्ण

अटल पूर्णांक pqi_ofa_alloc_mem(काष्ठा pqi_ctrl_info *ctrl_info, u32 total_size, u32 chunk_size)
अणु
	पूर्णांक i;
	u32 sg_count;
	काष्ठा device *dev;
	काष्ठा pqi_ofa_memory *ofap;
	काष्ठा pqi_sg_descriptor *mem_descriptor;
	dma_addr_t dma_handle;

	ofap = ctrl_info->pqi_ofa_mem_virt_addr;

	sg_count = DIV_ROUND_UP(total_size, chunk_size);
	अगर (sg_count == 0 || sg_count > PQI_OFA_MAX_SG_DESCRIPTORS)
		जाओ out;

	ctrl_info->pqi_ofa_chunk_virt_addr = kदो_स्मृति_array(sg_count, माप(व्योम *), GFP_KERNEL);
	अगर (!ctrl_info->pqi_ofa_chunk_virt_addr)
		जाओ out;

	dev = &ctrl_info->pci_dev->dev;

	क्रम (i = 0; i < sg_count; i++) अणु
		ctrl_info->pqi_ofa_chunk_virt_addr[i] =
			dma_alloc_coherent(dev, chunk_size, &dma_handle, GFP_KERNEL);
		अगर (!ctrl_info->pqi_ofa_chunk_virt_addr[i])
			जाओ out_मुक्त_chunks;
		mem_descriptor = &ofap->sg_descriptor[i];
		put_unaligned_le64((u64)dma_handle, &mem_descriptor->address);
		put_unaligned_le32(chunk_size, &mem_descriptor->length);
	पूर्ण

	put_unaligned_le32(CISS_SG_LAST, &mem_descriptor->flags);
	put_unaligned_le16(sg_count, &ofap->num_memory_descriptors);
	put_unaligned_le32(sg_count * chunk_size, &ofap->bytes_allocated);

	वापस 0;

out_मुक्त_chunks:
	जबतक (--i >= 0) अणु
		mem_descriptor = &ofap->sg_descriptor[i];
		dma_मुक्त_coherent(dev, chunk_size,
			ctrl_info->pqi_ofa_chunk_virt_addr[i],
			get_unaligned_le64(&mem_descriptor->address));
	पूर्ण
	kमुक्त(ctrl_info->pqi_ofa_chunk_virt_addr);

out:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक pqi_ofa_alloc_host_buffer(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	u32 total_size;
	u32 chunk_size;
	u32 min_chunk_size;

	अगर (ctrl_info->ofa_bytes_requested == 0)
		वापस 0;

	total_size = PAGE_ALIGN(ctrl_info->ofa_bytes_requested);
	min_chunk_size = DIV_ROUND_UP(total_size, PQI_OFA_MAX_SG_DESCRIPTORS);
	min_chunk_size = PAGE_ALIGN(min_chunk_size);

	क्रम (chunk_size = total_size; chunk_size >= min_chunk_size;) अणु
		अगर (pqi_ofa_alloc_mem(ctrl_info, total_size, chunk_size) == 0)
			वापस 0;
		chunk_size /= 2;
		chunk_size = PAGE_ALIGN(chunk_size);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल व्योम pqi_ofa_setup_host_buffer(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	काष्ठा device *dev;
	काष्ठा pqi_ofa_memory *ofap;

	dev = &ctrl_info->pci_dev->dev;

	ofap = dma_alloc_coherent(dev, माप(*ofap),
		&ctrl_info->pqi_ofa_mem_dma_handle, GFP_KERNEL);
	अगर (!ofap)
		वापस;

	ctrl_info->pqi_ofa_mem_virt_addr = ofap;

	अगर (pqi_ofa_alloc_host_buffer(ctrl_info) < 0) अणु
		dev_err(dev,
			"failed to allocate host buffer for Online Firmware Activation\n");
		dma_मुक्त_coherent(dev, माप(*ofap), ofap, ctrl_info->pqi_ofa_mem_dma_handle);
		ctrl_info->pqi_ofa_mem_virt_addr = शून्य;
		वापस;
	पूर्ण

	put_unaligned_le16(PQI_OFA_VERSION, &ofap->version);
	स_नकल(&ofap->signature, PQI_OFA_SIGNATURE, माप(ofap->signature));
पूर्ण

अटल व्योम pqi_ofa_मुक्त_host_buffer(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा device *dev;
	काष्ठा pqi_ofa_memory *ofap;
	काष्ठा pqi_sg_descriptor *mem_descriptor;
	अचिन्हित पूर्णांक num_memory_descriptors;

	ofap = ctrl_info->pqi_ofa_mem_virt_addr;
	अगर (!ofap)
		वापस;

	dev = &ctrl_info->pci_dev->dev;

	अगर (get_unaligned_le32(&ofap->bytes_allocated) == 0)
		जाओ out;

	mem_descriptor = ofap->sg_descriptor;
	num_memory_descriptors =
		get_unaligned_le16(&ofap->num_memory_descriptors);

	क्रम (i = 0; i < num_memory_descriptors; i++) अणु
		dma_मुक्त_coherent(dev,
			get_unaligned_le32(&mem_descriptor[i].length),
			ctrl_info->pqi_ofa_chunk_virt_addr[i],
			get_unaligned_le64(&mem_descriptor[i].address));
	पूर्ण
	kमुक्त(ctrl_info->pqi_ofa_chunk_virt_addr);

out:
	dma_मुक्त_coherent(dev, माप(*ofap), ofap,
		ctrl_info->pqi_ofa_mem_dma_handle);
	ctrl_info->pqi_ofa_mem_virt_addr = शून्य;
पूर्ण

अटल पूर्णांक pqi_ofa_host_memory_update(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	u32 buffer_length;
	काष्ठा pqi_venकरोr_general_request request;
	काष्ठा pqi_ofa_memory *ofap;

	स_रखो(&request, 0, माप(request));

	request.header.iu_type = PQI_REQUEST_IU_VENDOR_GENERAL;
	put_unaligned_le16(माप(request) - PQI_REQUEST_HEADER_LENGTH,
		&request.header.iu_length);
	put_unaligned_le16(PQI_VENDOR_GENERAL_HOST_MEMORY_UPDATE,
		&request.function_code);

	ofap = ctrl_info->pqi_ofa_mem_virt_addr;

	अगर (ofap) अणु
		buffer_length = दुरत्व(काष्ठा pqi_ofa_memory, sg_descriptor) +
			get_unaligned_le16(&ofap->num_memory_descriptors) *
			माप(काष्ठा pqi_sg_descriptor);

		put_unaligned_le64((u64)ctrl_info->pqi_ofa_mem_dma_handle,
			&request.data.ofa_memory_allocation.buffer_address);
		put_unaligned_le32(buffer_length,
			&request.data.ofa_memory_allocation.buffer_length);
	पूर्ण

	वापस pqi_submit_raid_request_synchronous(ctrl_info, &request.header, 0, शून्य);
पूर्ण

अटल पूर्णांक pqi_ofa_ctrl_restart(काष्ठा pqi_ctrl_info *ctrl_info, अचिन्हित पूर्णांक delay_secs)
अणु
	ssleep(delay_secs);

	वापस pqi_ctrl_init_resume(ctrl_info);
पूर्ण

अटल व्योम pqi_perक्रमm_lockup_action(व्योम)
अणु
	चयन (pqi_lockup_action) अणु
	हाल PANIC:
		panic("FATAL: Smart Family Controller lockup detected");
		अवरोध;
	हाल REBOOT:
		emergency_restart();
		अवरोध;
	हाल NONE:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा pqi_raid_error_info pqi_ctrl_offline_raid_error_info = अणु
	.data_out_result = PQI_DATA_IN_OUT_HARDWARE_ERROR,
	.status = SAM_STAT_CHECK_CONDITION,
पूर्ण;

अटल व्योम pqi_fail_all_outstanding_requests(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा pqi_io_request *io_request;
	काष्ठा scsi_cmnd *scmd;

	क्रम (i = 0; i < ctrl_info->max_io_slots; i++) अणु
		io_request = &ctrl_info->io_request_pool[i];
		अगर (atomic_पढ़ो(&io_request->refcount) == 0)
			जारी;

		scmd = io_request->scmd;
		अगर (scmd) अणु
			set_host_byte(scmd, DID_NO_CONNECT);
		पूर्ण अन्यथा अणु
			io_request->status = -ENXIO;
			io_request->error_info =
				&pqi_ctrl_offline_raid_error_info;
		पूर्ण

		io_request->io_complete_callback(io_request,
			io_request->context);
	पूर्ण
पूर्ण

अटल व्योम pqi_take_ctrl_offline_deferred(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	pqi_perक्रमm_lockup_action();
	pqi_stop_heartbeat_समयr(ctrl_info);
	pqi_मुक्त_पूर्णांकerrupts(ctrl_info);
	pqi_cancel_rescan_worker(ctrl_info);
	pqi_cancel_update_समय_worker(ctrl_info);
	pqi_ctrl_रुको_until_quiesced(ctrl_info);
	pqi_fail_all_outstanding_requests(ctrl_info);
	pqi_ctrl_unblock_requests(ctrl_info);
पूर्ण

अटल व्योम pqi_ctrl_offline_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = container_of(work, काष्ठा pqi_ctrl_info, ctrl_offline_work);
	pqi_take_ctrl_offline_deferred(ctrl_info);
पूर्ण

अटल व्योम pqi_take_ctrl_offline(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अगर (!ctrl_info->controller_online)
		वापस;

	ctrl_info->controller_online = false;
	ctrl_info->pqi_mode_enabled = false;
	pqi_ctrl_block_requests(ctrl_info);
	अगर (!pqi_disable_ctrl_shutकरोwn)
		sis_shutकरोwn_ctrl(ctrl_info);
	pci_disable_device(ctrl_info->pci_dev);
	dev_err(&ctrl_info->pci_dev->dev, "controller offline\n");
	schedule_work(&ctrl_info->ctrl_offline_work);
पूर्ण

अटल व्योम pqi_prपूर्णांक_ctrl_info(काष्ठा pci_dev *pci_dev,
	स्थिर काष्ठा pci_device_id *id)
अणु
	अक्षर *ctrl_description;

	अगर (id->driver_data)
		ctrl_description = (अक्षर *)id->driver_data;
	अन्यथा
		ctrl_description = "Microsemi Smart Family Controller";

	dev_info(&pci_dev->dev, "%s found\n", ctrl_description);
पूर्ण

अटल पूर्णांक pqi_pci_probe(काष्ठा pci_dev *pci_dev,
	स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक rc;
	पूर्णांक node, cp_node;
	काष्ठा pqi_ctrl_info *ctrl_info;

	pqi_prपूर्णांक_ctrl_info(pci_dev, id);

	अगर (pqi_disable_device_id_wildcards &&
		id->subvenकरोr == PCI_ANY_ID &&
		id->subdevice == PCI_ANY_ID) अणु
		dev_warn(&pci_dev->dev,
			"controller not probed because device ID wildcards are disabled\n");
		वापस -ENODEV;
	पूर्ण

	अगर (id->subvenकरोr == PCI_ANY_ID || id->subdevice == PCI_ANY_ID)
		dev_warn(&pci_dev->dev,
			"controller device ID matched using wildcards\n");

	node = dev_to_node(&pci_dev->dev);
	अगर (node == NUMA_NO_NODE) अणु
		cp_node = cpu_to_node(0);
		अगर (cp_node == NUMA_NO_NODE)
			cp_node = 0;
		set_dev_node(&pci_dev->dev, cp_node);
	पूर्ण

	ctrl_info = pqi_alloc_ctrl_info(node);
	अगर (!ctrl_info) अणु
		dev_err(&pci_dev->dev,
			"failed to allocate controller info block\n");
		वापस -ENOMEM;
	पूर्ण

	ctrl_info->pci_dev = pci_dev;

	rc = pqi_pci_init(ctrl_info);
	अगर (rc)
		जाओ error;

	rc = pqi_ctrl_init(ctrl_info);
	अगर (rc)
		जाओ error;

	वापस 0;

error:
	pqi_हटाओ_ctrl(ctrl_info);

	वापस rc;
पूर्ण

अटल व्योम pqi_pci_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = pci_get_drvdata(pci_dev);
	अगर (!ctrl_info)
		वापस;

	pqi_हटाओ_ctrl(ctrl_info);
पूर्ण

अटल व्योम pqi_crash_अगर_pending_command(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा pqi_io_request *io_request;
	काष्ठा scsi_cmnd *scmd;

	क्रम (i = 0; i < ctrl_info->max_io_slots; i++) अणु
		io_request = &ctrl_info->io_request_pool[i];
		अगर (atomic_पढ़ो(&io_request->refcount) == 0)
			जारी;
		scmd = io_request->scmd;
		WARN_ON(scmd != शून्य); /* IO command from SML */
		WARN_ON(scmd == शून्य); /* Non-IO cmd or driver initiated*/
	पूर्ण
पूर्ण

अटल व्योम pqi_shutकरोwn(काष्ठा pci_dev *pci_dev)
अणु
	पूर्णांक rc;
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = pci_get_drvdata(pci_dev);
	अगर (!ctrl_info) अणु
		dev_err(&pci_dev->dev,
			"cache could not be flushed\n");
		वापस;
	पूर्ण

	pqi_रुको_until_ofa_finished(ctrl_info);

	pqi_scsi_block_requests(ctrl_info);
	pqi_ctrl_block_device_reset(ctrl_info);
	pqi_ctrl_block_requests(ctrl_info);
	pqi_ctrl_रुको_until_quiesced(ctrl_info);

	/*
	 * Write all data in the controller's battery-backed cache to
	 * storage.
	 */
	rc = pqi_flush_cache(ctrl_info, SHUTDOWN);
	अगर (rc)
		dev_err(&pci_dev->dev,
			"unable to flush controller cache\n");

	pqi_crash_अगर_pending_command(ctrl_info);
	pqi_reset(ctrl_info);
पूर्ण

अटल व्योम pqi_process_lockup_action_param(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!pqi_lockup_action_param)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(pqi_lockup_actions); i++) अणु
		अगर (म_भेद(pqi_lockup_action_param,
			pqi_lockup_actions[i].name) == 0) अणु
			pqi_lockup_action = pqi_lockup_actions[i].action;
			वापस;
		पूर्ण
	पूर्ण

	pr_warn("%s: invalid lockup action setting \"%s\" - supported settings: none, reboot, panic\n",
		DRIVER_NAME_SHORT, pqi_lockup_action_param);
पूर्ण

अटल व्योम pqi_process_module_params(व्योम)
अणु
	pqi_process_lockup_action_param();
पूर्ण

अटल __maybe_unused पूर्णांक pqi_suspend(काष्ठा pci_dev *pci_dev, pm_message_t state)
अणु
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = pci_get_drvdata(pci_dev);

	pqi_रुको_until_ofa_finished(ctrl_info);

	pqi_ctrl_block_scan(ctrl_info);
	pqi_scsi_block_requests(ctrl_info);
	pqi_ctrl_block_device_reset(ctrl_info);
	pqi_ctrl_block_requests(ctrl_info);
	pqi_ctrl_रुको_until_quiesced(ctrl_info);
	pqi_flush_cache(ctrl_info, SUSPEND);
	pqi_stop_heartbeat_समयr(ctrl_info);

	pqi_crash_अगर_pending_command(ctrl_info);

	अगर (state.event == PM_EVENT_FREEZE)
		वापस 0;

	pci_save_state(pci_dev);
	pci_set_घातer_state(pci_dev, pci_choose_state(pci_dev, state));

	ctrl_info->controller_online = false;
	ctrl_info->pqi_mode_enabled = false;

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक pqi_resume(काष्ठा pci_dev *pci_dev)
अणु
	पूर्णांक rc;
	काष्ठा pqi_ctrl_info *ctrl_info;

	ctrl_info = pci_get_drvdata(pci_dev);

	अगर (pci_dev->current_state != PCI_D0) अणु
		ctrl_info->max_hw_queue_index = 0;
		pqi_मुक्त_पूर्णांकerrupts(ctrl_info);
		pqi_change_irq_mode(ctrl_info, IRQ_MODE_INTX);
		rc = request_irq(pci_irq_vector(pci_dev, 0), pqi_irq_handler,
			IRQF_SHARED, DRIVER_NAME_SHORT,
			&ctrl_info->queue_groups[0]);
		अगर (rc) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"irq %u init failed with error %d\n",
				pci_dev->irq, rc);
			वापस rc;
		पूर्ण
		pqi_ctrl_unblock_device_reset(ctrl_info);
		pqi_ctrl_unblock_requests(ctrl_info);
		pqi_scsi_unblock_requests(ctrl_info);
		pqi_ctrl_unblock_scan(ctrl_info);
		वापस 0;
	पूर्ण

	pci_set_घातer_state(pci_dev, PCI_D0);
	pci_restore_state(pci_dev);

	pqi_ctrl_unblock_device_reset(ctrl_info);
	pqi_ctrl_unblock_requests(ctrl_info);
	pqi_scsi_unblock_requests(ctrl_info);
	pqi_ctrl_unblock_scan(ctrl_info);

	वापस pqi_ctrl_init_resume(ctrl_info);
पूर्ण

/* Define the PCI IDs क्रम the controllers that we support. */
अटल स्थिर काष्ठा pci_device_id pqi_pci_id_table[] = अणु
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x105b, 0x1211)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x105b, 0x1321)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x152d, 0x8a22)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x152d, 0x8a23)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x152d, 0x8a24)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x152d, 0x8a36)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x152d, 0x8a37)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x193d, 0x8460)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x193d, 0x1104)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x193d, 0x1105)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x193d, 0x1106)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x193d, 0x1107)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x193d, 0x8460)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x193d, 0x8461)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x193d, 0xc460)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x193d, 0xc461)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x193d, 0xf460)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x193d, 0xf461)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x0045)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x0046)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x0047)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x0048)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x004a)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x004b)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x004c)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x004f)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x0051)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x0052)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x0053)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1bd4, 0x0054)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x19e5, 0xd227)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x19e5, 0xd228)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x19e5, 0xd229)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x19e5, 0xd22a)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x19e5, 0xd22b)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x19e5, 0xd22c)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0110)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0608)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0800)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0801)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0802)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0803)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0804)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0805)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0806)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0807)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0808)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0809)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x080a)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0900)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0901)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0902)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0903)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0904)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0905)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0906)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0907)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x0908)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x090a)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1200)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1201)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1202)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1280)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1281)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1282)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1300)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1301)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1302)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1303)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1380)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1400)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1402)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1410)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1411)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1412)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1420)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1430)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1440)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1441)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1450)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1452)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1460)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1461)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1462)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1470)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1471)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1472)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1480)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1490)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x1491)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x14a0)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x14a1)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x14b0)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x14b1)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x14c0)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x14c1)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x14d0)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x14e0)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADAPTEC2, 0x14f0)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_ADVANTECH, 0x8312)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_DELL, 0x1fe0)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0600)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0601)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0602)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0603)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0609)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0650)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0651)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0652)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0653)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0654)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0655)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0700)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x0701)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x1001)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x1002)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x1100)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_HP, 0x1101)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1590, 0x0294)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1590, 0x02db)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1590, 0x02dc)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1590, 0x032e)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1d8d, 0x0800)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1d8d, 0x0908)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1d8d, 0x0806)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       0x1d8d, 0x0916)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_VENDOR_ID_GIGABYTE, 0x1000)
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x028f,
			       PCI_ANY_ID, PCI_ANY_ID)
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pqi_pci_id_table);

अटल काष्ठा pci_driver pqi_pci_driver = अणु
	.name = DRIVER_NAME_SHORT,
	.id_table = pqi_pci_id_table,
	.probe = pqi_pci_probe,
	.हटाओ = pqi_pci_हटाओ,
	.shutकरोwn = pqi_shutकरोwn,
#अगर defined(CONFIG_PM)
	.suspend = pqi_suspend,
	.resume = pqi_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init pqi_init(व्योम)
अणु
	पूर्णांक rc;

	pr_info(DRIVER_NAME "\n");

	pqi_sas_transport_ढाँचा = sas_attach_transport(&pqi_sas_transport_functions);
	अगर (!pqi_sas_transport_ढाँचा)
		वापस -ENODEV;

	pqi_process_module_params();

	rc = pci_रेजिस्टर_driver(&pqi_pci_driver);
	अगर (rc)
		sas_release_transport(pqi_sas_transport_ढाँचा);

	वापस rc;
पूर्ण

अटल व्योम __निकास pqi_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pqi_pci_driver);
	sas_release_transport(pqi_sas_transport_ढाँचा);
पूर्ण

module_init(pqi_init);
module_निकास(pqi_cleanup);

अटल व्योम __attribute__((unused)) verअगरy_काष्ठाures(व्योम)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_ctrl_रेजिस्टरs,
		sis_host_to_ctrl_करोorbell) != 0x20);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_ctrl_रेजिस्टरs,
		sis_पूर्णांकerrupt_mask) != 0x34);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_ctrl_रेजिस्टरs,
		sis_ctrl_to_host_करोorbell) != 0x9c);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_ctrl_रेजिस्टरs,
		sis_ctrl_to_host_करोorbell_clear) != 0xa0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_ctrl_रेजिस्टरs,
		sis_driver_scratch) != 0xb0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_ctrl_रेजिस्टरs,
		sis_product_identअगरier) != 0xb4);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_ctrl_रेजिस्टरs,
		sis_firmware_status) != 0xbc);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_ctrl_रेजिस्टरs,
		sis_mailbox) != 0x1000);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_ctrl_रेजिस्टरs,
		pqi_रेजिस्टरs) != 0x4000);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_iu_header,
		iu_type) != 0x0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_iu_header,
		iu_length) != 0x2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_iu_header,
		response_queue_id) != 0x4);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_iu_header,
		driver_flags) != 0x6);
	BUILD_BUG_ON(माप(काष्ठा pqi_iu_header) != 0x8);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_error_info,
		status) != 0x0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_error_info,
		service_response) != 0x1);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_error_info,
		data_present) != 0x2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_error_info,
		reserved) != 0x3);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_error_info,
		residual_count) != 0x4);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_error_info,
		data_length) != 0x8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_error_info,
		reserved1) != 0xa);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_error_info,
		data) != 0xc);
	BUILD_BUG_ON(माप(काष्ठा pqi_aio_error_info) != 0x10c);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_error_info,
		data_in_result) != 0x0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_error_info,
		data_out_result) != 0x1);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_error_info,
		reserved) != 0x2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_error_info,
		status) != 0x5);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_error_info,
		status_qualअगरier) != 0x6);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_error_info,
		sense_data_length) != 0x8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_error_info,
		response_data_length) != 0xa);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_error_info,
		data_in_transferred) != 0xc);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_error_info,
		data_out_transferred) != 0x10);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_error_info,
		data) != 0x14);
	BUILD_BUG_ON(माप(काष्ठा pqi_raid_error_info) != 0x114);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		signature) != 0x0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		function_and_status_code) != 0x8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		max_admin_iq_elements) != 0x10);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		max_admin_oq_elements) != 0x11);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		admin_iq_element_length) != 0x12);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		admin_oq_element_length) != 0x13);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		max_reset_समयout) != 0x14);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		legacy_पूर्णांकx_status) != 0x18);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		legacy_पूर्णांकx_mask_set) != 0x1c);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		legacy_पूर्णांकx_mask_clear) != 0x20);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		device_status) != 0x40);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		admin_iq_pi_offset) != 0x48);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		admin_oq_ci_offset) != 0x50);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		admin_iq_element_array_addr) != 0x58);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		admin_oq_element_array_addr) != 0x60);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		admin_iq_ci_addr) != 0x68);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		admin_oq_pi_addr) != 0x70);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		admin_iq_num_elements) != 0x78);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		admin_oq_num_elements) != 0x79);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		admin_queue_पूर्णांक_msg_num) != 0x7a);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		device_error) != 0x80);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		error_details) != 0x88);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		device_reset) != 0x90);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_रेजिस्टरs,
		घातer_action) != 0x94);
	BUILD_BUG_ON(माप(काष्ठा pqi_device_रेजिस्टरs) != 0x100);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		header.iu_type) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		header.iu_length) != 2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		header.driver_flags) != 6);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		request_id) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		function_code) != 10);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.report_device_capability.buffer_length) != 44);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.report_device_capability.sg_descriptor) != 48);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_iq.queue_id) != 12);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_iq.element_array_addr) != 16);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_iq.ci_addr) != 24);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_iq.num_elements) != 32);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_iq.element_length) != 34);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_iq.queue_protocol) != 36);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_oq.queue_id) != 12);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_oq.element_array_addr) != 16);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_oq.pi_addr) != 24);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_oq.num_elements) != 32);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_oq.element_length) != 34);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_oq.queue_protocol) != 36);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_oq.पूर्णांक_msg_num) != 40);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_oq.coalescing_count) != 42);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_oq.min_coalescing_समय) != 44);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.create_operational_oq.max_coalescing_समय) != 48);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_request,
		data.delete_operational_queue.queue_id) != 12);
	BUILD_BUG_ON(माप(काष्ठा pqi_general_admin_request) != 64);
	BUILD_BUG_ON(माप_field(काष्ठा pqi_general_admin_request,
		data.create_operational_iq) != 64 - 11);
	BUILD_BUG_ON(माप_field(काष्ठा pqi_general_admin_request,
		data.create_operational_oq) != 64 - 11);
	BUILD_BUG_ON(माप_field(काष्ठा pqi_general_admin_request,
		data.delete_operational_queue) != 64 - 11);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_response,
		header.iu_type) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_response,
		header.iu_length) != 2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_response,
		header.driver_flags) != 6);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_response,
		request_id) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_response,
		function_code) != 10);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_response,
		status) != 11);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_response,
		data.create_operational_iq.status_descriptor) != 12);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_response,
		data.create_operational_iq.iq_pi_offset) != 16);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_response,
		data.create_operational_oq.status_descriptor) != 12);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_admin_response,
		data.create_operational_oq.oq_ci_offset) != 16);
	BUILD_BUG_ON(माप(काष्ठा pqi_general_admin_response) != 64);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		header.iu_type) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		header.iu_length) != 2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		header.response_queue_id) != 4);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		header.driver_flags) != 6);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		request_id) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		nexus_id) != 10);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		buffer_length) != 12);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		lun_number) != 16);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		protocol_specअगरic) != 24);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		error_index) != 27);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		cdb) != 32);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		समयout) != 60);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_raid_path_request,
		sg_descriptors) != 64);
	BUILD_BUG_ON(माप(काष्ठा pqi_raid_path_request) !=
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		header.iu_type) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		header.iu_length) != 2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		header.response_queue_id) != 4);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		header.driver_flags) != 6);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		request_id) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		nexus_id) != 12);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		buffer_length) != 16);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		data_encryption_key_index) != 22);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		encrypt_tweak_lower) != 24);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		encrypt_tweak_upper) != 28);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		cdb) != 32);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		error_index) != 48);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		num_sg_descriptors) != 50);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		cdb_length) != 51);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		lun_number) != 52);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_aio_path_request,
		sg_descriptors) != 64);
	BUILD_BUG_ON(माप(काष्ठा pqi_aio_path_request) !=
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_io_response,
		header.iu_type) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_io_response,
		header.iu_length) != 2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_io_response,
		request_id) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_io_response,
		error_index) != 10);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_management_request,
		header.iu_type) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_management_request,
		header.iu_length) != 2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_management_request,
		header.response_queue_id) != 4);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_management_request,
		request_id) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_management_request,
		data.report_event_configuration.buffer_length) != 12);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_management_request,
		data.report_event_configuration.sg_descriptors) != 16);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_management_request,
		data.set_event_configuration.global_event_oq_id) != 10);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_management_request,
		data.set_event_configuration.buffer_length) != 12);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_general_management_request,
		data.set_event_configuration.sg_descriptors) != 16);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_iu_layer_descriptor,
		max_inbound_iu_length) != 6);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_iu_layer_descriptor,
		max_outbound_iu_length) != 14);
	BUILD_BUG_ON(माप(काष्ठा pqi_iu_layer_descriptor) != 16);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		data_length) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		iq_arbitration_priority_support_biपंचांगask) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		maximum_aw_a) != 9);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		maximum_aw_b) != 10);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		maximum_aw_c) != 11);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		max_inbound_queues) != 16);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		max_elements_per_iq) != 18);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		max_iq_element_length) != 24);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		min_iq_element_length) != 26);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		max_outbound_queues) != 30);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		max_elements_per_oq) != 32);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		पूर्णांकr_coalescing_समय_granularity) != 34);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		max_oq_element_length) != 36);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		min_oq_element_length) != 38);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_device_capability,
		iu_layer_descriptors) != 64);
	BUILD_BUG_ON(माप(काष्ठा pqi_device_capability) != 576);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_descriptor,
		event_type) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_descriptor,
		oq_id) != 2);
	BUILD_BUG_ON(माप(काष्ठा pqi_event_descriptor) != 4);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_config,
		num_event_descriptors) != 2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_config,
		descriptors) != 4);

	BUILD_BUG_ON(PQI_NUM_SUPPORTED_EVENTS !=
		ARRAY_SIZE(pqi_supported_event_types));

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_response,
		header.iu_type) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_response,
		header.iu_length) != 2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_response,
		event_type) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_response,
		event_id) != 10);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_response,
		additional_event_id) != 12);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_response,
		data) != 16);
	BUILD_BUG_ON(माप(काष्ठा pqi_event_response) != 32);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_acknowledge_request,
		header.iu_type) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_acknowledge_request,
		header.iu_length) != 2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_acknowledge_request,
		event_type) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_acknowledge_request,
		event_id) != 10);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_event_acknowledge_request,
		additional_event_id) != 12);
	BUILD_BUG_ON(माप(काष्ठा pqi_event_acknowledge_request) != 16);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_request,
		header.iu_type) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_request,
		header.iu_length) != 2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_request,
		request_id) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_request,
		nexus_id) != 10);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_request,
		समयout) != 14);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_request,
		lun_number) != 16);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_request,
		protocol_specअगरic) != 24);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_request,
		outbound_queue_id_to_manage) != 26);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_request,
		request_id_to_manage) != 28);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_request,
		task_management_function) != 30);
	BUILD_BUG_ON(माप(काष्ठा pqi_task_management_request) != 32);

	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_response,
		header.iu_type) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_response,
		header.iu_length) != 2);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_response,
		request_id) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_response,
		nexus_id) != 10);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_response,
		additional_response_info) != 12);
	BUILD_BUG_ON(दुरत्व(काष्ठा pqi_task_management_response,
		response_code) != 15);
	BUILD_BUG_ON(माप(काष्ठा pqi_task_management_response) != 16);

	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_controller,
		configured_logical_drive_count) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_controller,
		configuration_signature) != 1);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_controller,
		firmware_version_लघु) != 5);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_controller,
		extended_logical_unit_count) != 154);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_controller,
		firmware_build_number) != 190);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_controller,
		venकरोr_id) != 200);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_controller,
		product_id) != 208);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_controller,
		extra_controller_flags) != 286);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_controller,
		controller_mode) != 292);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_controller,
		spare_part_number) != 293);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_controller,
		firmware_version_दीर्घ) != 325);

	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_physical_device,
		phys_bay_in_box) != 115);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_physical_device,
		device_type) != 120);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_physical_device,
		redundant_path_present_map) != 1736);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_physical_device,
		active_path_number) != 1738);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_physical_device,
		alternate_paths_phys_connector) != 1739);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_physical_device,
		alternate_paths_phys_box_on_port) != 1755);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_identअगरy_physical_device,
		current_queue_depth_limit) != 1796);
	BUILD_BUG_ON(माप(काष्ठा bmic_identअगरy_physical_device) != 2560);

	BUILD_BUG_ON(माप(काष्ठा bmic_sense_feature_buffer_header) != 4);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_buffer_header,
		page_code) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_buffer_header,
		subpage_code) != 1);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_buffer_header,
		buffer_length) != 2);

	BUILD_BUG_ON(माप(काष्ठा bmic_sense_feature_page_header) != 4);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_page_header,
		page_code) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_page_header,
		subpage_code) != 1);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_page_header,
		page_length) != 2);

	BUILD_BUG_ON(माप(काष्ठा bmic_sense_feature_io_page_aio_subpage)
		!= 18);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_io_page_aio_subpage,
		header) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_io_page_aio_subpage,
		firmware_पढ़ो_support) != 4);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_io_page_aio_subpage,
		driver_पढ़ो_support) != 5);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_io_page_aio_subpage,
		firmware_ग_लिखो_support) != 6);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_io_page_aio_subpage,
		driver_ग_लिखो_support) != 7);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_io_page_aio_subpage,
		max_transfer_encrypted_sas_sata) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_io_page_aio_subpage,
		max_transfer_encrypted_nvme) != 10);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_io_page_aio_subpage,
		max_ग_लिखो_raid_5_6) != 12);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_io_page_aio_subpage,
		max_ग_लिखो_raid_1_10_2drive) != 14);
	BUILD_BUG_ON(दुरत्व(काष्ठा bmic_sense_feature_io_page_aio_subpage,
		max_ग_लिखो_raid_1_10_3drive) != 16);

	BUILD_BUG_ON(PQI_ADMIN_IQ_NUM_ELEMENTS > 255);
	BUILD_BUG_ON(PQI_ADMIN_OQ_NUM_ELEMENTS > 255);
	BUILD_BUG_ON(PQI_ADMIN_IQ_ELEMENT_LENGTH %
		PQI_QUEUE_ELEMENT_LENGTH_ALIGNMENT != 0);
	BUILD_BUG_ON(PQI_ADMIN_OQ_ELEMENT_LENGTH %
		PQI_QUEUE_ELEMENT_LENGTH_ALIGNMENT != 0);
	BUILD_BUG_ON(PQI_OPERATIONAL_IQ_ELEMENT_LENGTH > 1048560);
	BUILD_BUG_ON(PQI_OPERATIONAL_IQ_ELEMENT_LENGTH %
		PQI_QUEUE_ELEMENT_LENGTH_ALIGNMENT != 0);
	BUILD_BUG_ON(PQI_OPERATIONAL_OQ_ELEMENT_LENGTH > 1048560);
	BUILD_BUG_ON(PQI_OPERATIONAL_OQ_ELEMENT_LENGTH %
		PQI_QUEUE_ELEMENT_LENGTH_ALIGNMENT != 0);

	BUILD_BUG_ON(PQI_RESERVED_IO_SLOTS >= PQI_MAX_OUTSTANDING_REQUESTS);
	BUILD_BUG_ON(PQI_RESERVED_IO_SLOTS >=
		PQI_MAX_OUTSTANDING_REQUESTS_KDUMP);
पूर्ण
