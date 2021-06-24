<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित __NFIT_TEST_H__
#घोषणा __NFIT_TEST_H__
#समावेश <linux/acpi.h>
#समावेश <linux/list.h>
#समावेश <linux/uuid.h>
#समावेश <linux/ioport.h>
#समावेश <linux/spinlock_types.h>

काष्ठा nfit_test_request अणु
	काष्ठा list_head list;
	काष्ठा resource res;
पूर्ण;

काष्ठा nfit_test_resource अणु
	काष्ठा list_head requests;
	काष्ठा list_head list;
	काष्ठा resource res;
	काष्ठा device *dev;
	spinlock_t lock;
	पूर्णांक req_count;
	व्योम *buf;
पूर्ण;

#घोषणा ND_TRANSLATE_SPA_STATUS_INVALID_SPA  2
#घोषणा NFIT_ARS_INJECT_INVALID 2

क्रमागत err_inj_options अणु
	ND_ARS_ERR_INJ_OPT_NOTIFY = 0,
पूर्ण;

/* nfit commands */
क्रमागत nfit_cmd_num अणु
	NFIT_CMD_TRANSLATE_SPA = 5,
	NFIT_CMD_ARS_INJECT_SET = 7,
	NFIT_CMD_ARS_INJECT_CLEAR = 8,
	NFIT_CMD_ARS_INJECT_GET = 9,
पूर्ण;

काष्ठा nd_cmd_translate_spa अणु
	__u64 spa;
	__u32 status;
	__u8  flags;
	__u8  _reserved[3];
	__u64 translate_length;
	__u32 num_nvdimms;
	काष्ठा nd_nvdimm_device अणु
		__u32 nfit_device_handle;
		__u32 _reserved;
		__u64 dpa;
	पूर्ण __packed devices[];

पूर्ण __packed;

काष्ठा nd_cmd_ars_err_inj अणु
	__u64 err_inj_spa_range_base;
	__u64 err_inj_spa_range_length;
	__u8  err_inj_options;
	__u32 status;
पूर्ण __packed;

काष्ठा nd_cmd_ars_err_inj_clr अणु
	__u64 err_inj_clr_spa_range_base;
	__u64 err_inj_clr_spa_range_length;
	__u32 status;
पूर्ण __packed;

काष्ठा nd_cmd_ars_err_inj_stat अणु
	__u32 status;
	__u32 inj_err_rec_count;
	काष्ठा nd_error_stat_query_record अणु
		__u64 err_inj_stat_spa_range_base;
		__u64 err_inj_stat_spa_range_length;
	पूर्ण __packed record[];
पूर्ण __packed;

#घोषणा ND_INTEL_SMART			 1
#घोषणा ND_INTEL_SMART_THRESHOLD	 2
#घोषणा ND_INTEL_ENABLE_LSS_STATUS	10
#घोषणा ND_INTEL_FW_GET_INFO		12
#घोषणा ND_INTEL_FW_START_UPDATE	13
#घोषणा ND_INTEL_FW_SEND_DATA		14
#घोषणा ND_INTEL_FW_FINISH_UPDATE	15
#घोषणा ND_INTEL_FW_FINISH_QUERY	16
#घोषणा ND_INTEL_SMART_SET_THRESHOLD	17
#घोषणा ND_INTEL_SMART_INJECT		18

#घोषणा ND_INTEL_SMART_HEALTH_VALID             (1 << 0)
#घोषणा ND_INTEL_SMART_SPARES_VALID             (1 << 1)
#घोषणा ND_INTEL_SMART_USED_VALID               (1 << 2)
#घोषणा ND_INTEL_SMART_MTEMP_VALID              (1 << 3)
#घोषणा ND_INTEL_SMART_CTEMP_VALID              (1 << 4)
#घोषणा ND_INTEL_SMART_SHUTDOWN_COUNT_VALID     (1 << 5)
#घोषणा ND_INTEL_SMART_AIT_STATUS_VALID         (1 << 6)
#घोषणा ND_INTEL_SMART_PTEMP_VALID              (1 << 7)
#घोषणा ND_INTEL_SMART_ALARM_VALID              (1 << 9)
#घोषणा ND_INTEL_SMART_SHUTDOWN_VALID           (1 << 10)
#घोषणा ND_INTEL_SMART_VENDOR_VALID             (1 << 11)
#घोषणा ND_INTEL_SMART_SPARE_TRIP               (1 << 0)
#घोषणा ND_INTEL_SMART_TEMP_TRIP                (1 << 1)
#घोषणा ND_INTEL_SMART_CTEMP_TRIP               (1 << 2)
#घोषणा ND_INTEL_SMART_NON_CRITICAL_HEALTH      (1 << 0)
#घोषणा ND_INTEL_SMART_CRITICAL_HEALTH          (1 << 1)
#घोषणा ND_INTEL_SMART_FATAL_HEALTH             (1 << 2)
#घोषणा ND_INTEL_SMART_INJECT_MTEMP		(1 << 0)
#घोषणा ND_INTEL_SMART_INJECT_SPARE		(1 << 1)
#घोषणा ND_INTEL_SMART_INJECT_FATAL		(1 << 2)
#घोषणा ND_INTEL_SMART_INJECT_SHUTDOWN		(1 << 3)

काष्ठा nd_पूर्णांकel_smart_threshold अणु
	__u32 status;
	जोड़ अणु
		काष्ठा अणु
			__u16 alarm_control;
			__u8 spares;
			__u16 media_temperature;
			__u16 ctrl_temperature;
			__u8 reserved[1];
		पूर्ण __packed;
		__u8 data[8];
	पूर्ण;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_smart_set_threshold अणु
	__u16 alarm_control;
	__u8 spares;
	__u16 media_temperature;
	__u16 ctrl_temperature;
	__u32 status;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_smart_inject अणु
	__u64 flags;
	__u8 mtemp_enable;
	__u16 media_temperature;
	__u8 spare_enable;
	__u8 spares;
	__u8 fatal_enable;
	__u8 unsafe_shutकरोwn_enable;
	__u32 status;
पूर्ण __packed;

#घोषणा INTEL_FW_STORAGE_SIZE		0x100000
#घोषणा INTEL_FW_MAX_SEND_LEN		0xFFEC
#घोषणा INTEL_FW_QUERY_INTERVAL		250000
#घोषणा INTEL_FW_QUERY_MAX_TIME		3000000
#घोषणा INTEL_FW_FIS_VERSION		0x0105
#घोषणा INTEL_FW_FAKE_VERSION		0xffffffffabcd

क्रमागत पूर्णांकel_fw_update_state अणु
	FW_STATE_NEW = 0,
	FW_STATE_IN_PROGRESS,
	FW_STATE_VERIFY,
	FW_STATE_UPDATED,
पूर्ण;

काष्ठा nd_पूर्णांकel_fw_info अणु
	__u32 status;
	__u32 storage_size;
	__u32 max_send_len;
	__u32 query_पूर्णांकerval;
	__u32 max_query_समय;
	__u8 update_cap;
	__u8 reserved[3];
	__u32 fis_version;
	__u64 run_version;
	__u64 updated_version;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_fw_start अणु
	__u32 status;
	__u32 context;
पूर्ण __packed;

/* this one has the output first because the variable input data size */
काष्ठा nd_पूर्णांकel_fw_send_data अणु
	__u32 context;
	__u32 offset;
	__u32 length;
	__u8 data[];
/* this field is not declared due ot variable data from input */
/*	__u32 status; */
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_fw_finish_update अणु
	__u8 ctrl_flags;
	__u8 reserved[3];
	__u32 context;
	__u32 status;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_fw_finish_query अणु
	__u32 context;
	__u32 status;
	__u64 updated_fw_rev;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_lss अणु
	__u8 enable;
	__u32 status;
पूर्ण __packed;

प्रकार काष्ठा nfit_test_resource *(*nfit_test_lookup_fn)(resource_माप_प्रकार);
प्रकार जोड़ acpi_object *(*nfit_test_evaluate_dsm_fn)(acpi_handle handle,
		 स्थिर guid_t *guid, u64 rev, u64 func,
		 जोड़ acpi_object *argv4);
व्योम __wrap_iounmap(अस्थिर व्योम __iomem *addr);
व्योम nfit_test_setup(nfit_test_lookup_fn lookup,
		nfit_test_evaluate_dsm_fn evaluate);
व्योम nfit_test_tearकरोwn(व्योम);
काष्ठा nfit_test_resource *get_nfit_res(resource_माप_प्रकार resource);
#पूर्ण_अगर
