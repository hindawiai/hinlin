<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SCPI Message Protocol driver header
 *
 * Copyright (C) 2014 ARM Ltd.
 */

#अगर_अघोषित _LINUX_SCPI_PROTOCOL_H
#घोषणा _LINUX_SCPI_PROTOCOL_H

#समावेश <linux/types.h>

काष्ठा scpi_opp अणु
	u32 freq;
	u32 m_volt;
पूर्ण __packed;

काष्ठा scpi_dvfs_info अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक latency; /* in nanoseconds */
	काष्ठा scpi_opp *opps;
पूर्ण;

क्रमागत scpi_sensor_class अणु
	TEMPERATURE,
	VOLTAGE,
	CURRENT,
	POWER,
	ENERGY,
पूर्ण;

काष्ठा scpi_sensor_info अणु
	u16 sensor_id;
	u8 class;
	u8 trigger_type;
	अक्षर name[20];
पूर्ण __packed;

/**
 * काष्ठा scpi_ops - represents the various operations provided
 *	by SCP through SCPI message protocol
 * @get_version: वापसs the major and minor revision on the SCPI
 *	message protocol
 * @clk_get_range: माला_लो घड़ी range limit(min - max in Hz)
 * @clk_get_val: माला_लो घड़ी value(in Hz)
 * @clk_set_val: sets the घड़ी value, setting to 0 will disable the
 *	घड़ी (अगर supported)
 * @dvfs_get_idx: माला_लो the Operating Poपूर्णांक of the given घातer करोमुख्य.
 *	OPP is an index to the list वापस by @dvfs_get_info
 * @dvfs_set_idx: sets the Operating Poपूर्णांक of the given घातer करोमुख्य.
 *	OPP is an index to the list वापस by @dvfs_get_info
 * @dvfs_get_info: वापसs the DVFS capabilities of the given घातer
 *	करोमुख्य. It includes the OPP list and the latency inक्रमmation
 */
काष्ठा scpi_ops अणु
	u32 (*get_version)(व्योम);
	पूर्णांक (*clk_get_range)(u16, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);
	अचिन्हित दीर्घ (*clk_get_val)(u16);
	पूर्णांक (*clk_set_val)(u16, अचिन्हित दीर्घ);
	पूर्णांक (*dvfs_get_idx)(u8);
	पूर्णांक (*dvfs_set_idx)(u8, u8);
	काष्ठा scpi_dvfs_info *(*dvfs_get_info)(u8);
	पूर्णांक (*device_करोमुख्य_id)(काष्ठा device *);
	पूर्णांक (*get_transition_latency)(काष्ठा device *);
	पूर्णांक (*add_opps_to_device)(काष्ठा device *);
	पूर्णांक (*sensor_get_capability)(u16 *sensors);
	पूर्णांक (*sensor_get_info)(u16 sensor_id, काष्ठा scpi_sensor_info *);
	पूर्णांक (*sensor_get_value)(u16, u64 *);
	पूर्णांक (*device_get_घातer_state)(u16);
	पूर्णांक (*device_set_घातer_state)(u16, u8);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_ARM_SCPI_PROTOCOL)
काष्ठा scpi_ops *get_scpi_ops(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा scpi_ops *get_scpi_ops(व्योम) अणु वापस शून्य; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SCPI_PROTOCOL_H */
