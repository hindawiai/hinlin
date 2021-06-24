<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel SOC Telemetry Driver Header File
 * Copyright (C) 2015, Intel Corporation.
 * All Rights Reserved.
 */
#अगर_अघोषित INTEL_TELEMETRY_H
#घोषणा INTEL_TELEMETRY_H

#घोषणा TELEM_MAX_EVENTS_SRAM		28
#घोषणा TELEM_MAX_OS_ALLOCATED_EVENTS	20

#समावेश <यंत्र/पूर्णांकel_scu_ipc.h>

क्रमागत telemetry_unit अणु
	TELEM_PSS = 0,
	TELEM_IOSS,
	TELEM_UNIT_NONE
पूर्ण;

काष्ठा telemetry_evtlog अणु
	u32 telem_evtid;
	u64 telem_evtlog;
पूर्ण;

काष्ठा telemetry_evtconfig अणु
	/* Array of Event-IDs to Enable */
	u32 *evपंचांगap;

	/* Number of Events (<29) in evपंचांगap */
	u8 num_evts;

	/* Sampling period */
	u8 period;
पूर्ण;

काष्ठा telemetry_evपंचांगap अणु
	स्थिर अक्षर *name;
	u32 evt_id;
पूर्ण;

काष्ठा telemetry_unit_config अणु
	काष्ठा telemetry_evपंचांगap *telem_evts;
	व्योम __iomem *regmap;
	u8 ssram_evts_used;
	u8 curr_period;
	u8 max_period;
	u8 min_period;
पूर्ण;

काष्ठा telemetry_plt_config अणु
	काष्ठा telemetry_unit_config pss_config;
	काष्ठा telemetry_unit_config ioss_config;
	काष्ठा mutex telem_trace_lock;
	काष्ठा mutex telem_lock;
	काष्ठा पूर्णांकel_pmc_dev *pmc;
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;
	bool telem_in_use;
पूर्ण;

काष्ठा telemetry_core_ops अणु
	पूर्णांक (*get_sampling_period)(u8 *pss_min_period, u8 *pss_max_period,
				   u8 *ioss_min_period, u8 *ioss_max_period);

	पूर्णांक (*get_eventconfig)(काष्ठा telemetry_evtconfig *pss_evtconfig,
			       काष्ठा telemetry_evtconfig *ioss_evtconfig,
			       पूर्णांक pss_len, पूर्णांक ioss_len);

	पूर्णांक (*update_events)(काष्ठा telemetry_evtconfig pss_evtconfig,
			     काष्ठा telemetry_evtconfig ioss_evtconfig);

	पूर्णांक (*set_sampling_period)(u8 pss_period, u8 ioss_period);

	पूर्णांक (*get_trace_verbosity)(क्रमागत telemetry_unit telem_unit,
				   u32 *verbosity);

	पूर्णांक (*set_trace_verbosity)(क्रमागत telemetry_unit telem_unit,
				   u32 verbosity);

	पूर्णांक (*raw_पढ़ो_eventlog)(क्रमागत telemetry_unit telem_unit,
				 काष्ठा telemetry_evtlog *evtlog,
				 पूर्णांक len, पूर्णांक log_all_evts);

	पूर्णांक (*पढ़ो_eventlog)(क्रमागत telemetry_unit telem_unit,
			     काष्ठा telemetry_evtlog *evtlog,
			     पूर्णांक len, पूर्णांक log_all_evts);

	पूर्णांक (*add_events)(u8 num_pss_evts, u8 num_ioss_evts,
			  u32 *pss_evपंचांगap, u32 *ioss_evपंचांगap);

	पूर्णांक (*reset_events)(व्योम);
पूर्ण;

पूर्णांक telemetry_set_pltdata(स्थिर काष्ठा telemetry_core_ops *ops,
			  काष्ठा telemetry_plt_config *pltconfig);

पूर्णांक telemetry_clear_pltdata(व्योम);

काष्ठा telemetry_plt_config *telemetry_get_pltdata(व्योम);

पूर्णांक telemetry_get_evtname(क्रमागत telemetry_unit telem_unit,
			  स्थिर अक्षर **name, पूर्णांक len);

पूर्णांक telemetry_update_events(काष्ठा telemetry_evtconfig pss_evtconfig,
			    काष्ठा telemetry_evtconfig ioss_evtconfig);

पूर्णांक telemetry_add_events(u8 num_pss_evts, u8 num_ioss_evts,
			 u32 *pss_evपंचांगap, u32 *ioss_evपंचांगap);

पूर्णांक telemetry_reset_events(व्योम);

पूर्णांक telemetry_get_eventconfig(काष्ठा telemetry_evtconfig *pss_config,
			      काष्ठा telemetry_evtconfig *ioss_config,
			      पूर्णांक pss_len, पूर्णांक ioss_len);

पूर्णांक telemetry_पढ़ो_events(क्रमागत telemetry_unit telem_unit,
			  काष्ठा telemetry_evtlog *evtlog, पूर्णांक len);

पूर्णांक telemetry_raw_पढ़ो_events(क्रमागत telemetry_unit telem_unit,
			      काष्ठा telemetry_evtlog *evtlog, पूर्णांक len);

पूर्णांक telemetry_पढ़ो_eventlog(क्रमागत telemetry_unit telem_unit,
			    काष्ठा telemetry_evtlog *evtlog, पूर्णांक len);

पूर्णांक telemetry_raw_पढ़ो_eventlog(क्रमागत telemetry_unit telem_unit,
				काष्ठा telemetry_evtlog *evtlog, पूर्णांक len);

पूर्णांक telemetry_get_sampling_period(u8 *pss_min_period, u8 *pss_max_period,
				  u8 *ioss_min_period, u8 *ioss_max_period);

पूर्णांक telemetry_set_sampling_period(u8 pss_period, u8 ioss_period);

पूर्णांक telemetry_set_trace_verbosity(क्रमागत telemetry_unit telem_unit,
				  u32 verbosity);

पूर्णांक telemetry_get_trace_verbosity(क्रमागत telemetry_unit telem_unit,
				  u32 *verbosity);

#पूर्ण_अगर /* INTEL_TELEMETRY_H */
