<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * पूर्णांकel_soc_dts_iosf.h
 * Copyright (c) 2015, Intel Corporation.
 */

#अगर_अघोषित _INTEL_SOC_DTS_IOSF_CORE_H
#घोषणा _INTEL_SOC_DTS_IOSF_CORE_H

#समावेश <linux/thermal.h>

/* DTS0 and DTS 1 */
#घोषणा SOC_MAX_DTS_SENSORS	2

क्रमागत पूर्णांकel_soc_dts_पूर्णांकerrupt_type अणु
	INTEL_SOC_DTS_INTERRUPT_NONE,
	INTEL_SOC_DTS_INTERRUPT_APIC,
	INTEL_SOC_DTS_INTERRUPT_MSI,
	INTEL_SOC_DTS_INTERRUPT_SCI,
	INTEL_SOC_DTS_INTERRUPT_SMI,
पूर्ण;

काष्ठा पूर्णांकel_soc_dts_sensors;

काष्ठा पूर्णांकel_soc_dts_sensor_entry अणु
	पूर्णांक id;
	u32 store_status;
	u32 trip_mask;
	u32 trip_count;
	क्रमागत thermal_trip_type trip_types[2];
	काष्ठा thermal_zone_device *tzone;
	काष्ठा पूर्णांकel_soc_dts_sensors *sensors;
पूर्ण;

काष्ठा पूर्णांकel_soc_dts_sensors अणु
	u32 tj_max;
	spinlock_t पूर्णांकr_notअगरy_lock;
	काष्ठा mutex dts_update_lock;
	क्रमागत पूर्णांकel_soc_dts_पूर्णांकerrupt_type पूर्णांकr_type;
	काष्ठा पूर्णांकel_soc_dts_sensor_entry soc_dts[SOC_MAX_DTS_SENSORS];
पूर्ण;

काष्ठा पूर्णांकel_soc_dts_sensors *पूर्णांकel_soc_dts_iosf_init(
	क्रमागत पूर्णांकel_soc_dts_पूर्णांकerrupt_type पूर्णांकr_type, पूर्णांक trip_count,
	पूर्णांक पढ़ो_only_trip_count);
व्योम पूर्णांकel_soc_dts_iosf_निकास(काष्ठा पूर्णांकel_soc_dts_sensors *sensors);
व्योम पूर्णांकel_soc_dts_iosf_पूर्णांकerrupt_handler(
				काष्ठा पूर्णांकel_soc_dts_sensors *sensors);
पूर्णांक पूर्णांकel_soc_dts_iosf_add_पढ़ो_only_critical_trip(
	काष्ठा पूर्णांकel_soc_dts_sensors *sensors, पूर्णांक critical_offset);
#पूर्ण_अगर
