<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel SoC Core Telemetry Driver
 * Copyright (C) 2015, Intel Corporation.
 * All Rights Reserved.
 *
 * Telemetry Framework provides platक्रमm related PM and perक्रमmance statistics.
 * This file provides the core telemetry API implementation.
 */
#समावेश <linux/device.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/पूर्णांकel_telemetry.h>

#घोषणा DRIVER_NAME "intel_telemetry_core"

काष्ठा telemetry_core_config अणु
	काष्ठा telemetry_plt_config *plt_config;
	स्थिर काष्ठा telemetry_core_ops *telem_ops;
पूर्ण;

अटल काष्ठा telemetry_core_config telm_core_conf;

अटल पूर्णांक telemetry_def_update_events(काष्ठा telemetry_evtconfig pss_evtconfig,
				      काष्ठा telemetry_evtconfig ioss_evtconfig)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक telemetry_def_set_sampling_period(u8 pss_period, u8 ioss_period)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक telemetry_def_get_sampling_period(u8 *pss_min_period,
					     u8 *pss_max_period,
					     u8 *ioss_min_period,
					     u8 *ioss_max_period)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक telemetry_def_get_eventconfig(
			काष्ठा telemetry_evtconfig *pss_evtconfig,
			काष्ठा telemetry_evtconfig *ioss_evtconfig,
			पूर्णांक pss_len, पूर्णांक ioss_len)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक telemetry_def_get_trace_verbosity(क्रमागत telemetry_unit telem_unit,
					     u32 *verbosity)
अणु
	वापस 0;
पूर्ण


अटल पूर्णांक telemetry_def_set_trace_verbosity(क्रमागत telemetry_unit telem_unit,
					     u32 verbosity)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक telemetry_def_raw_पढ़ो_eventlog(क्रमागत telemetry_unit telem_unit,
					   काष्ठा telemetry_evtlog *evtlog,
					   पूर्णांक len, पूर्णांक log_all_evts)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक telemetry_def_पढ़ो_eventlog(क्रमागत telemetry_unit telem_unit,
				       काष्ठा telemetry_evtlog *evtlog,
				       पूर्णांक len, पूर्णांक log_all_evts)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक telemetry_def_add_events(u8 num_pss_evts, u8 num_ioss_evts,
				    u32 *pss_evपंचांगap, u32 *ioss_evपंचांगap)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक telemetry_def_reset_events(व्योम)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा telemetry_core_ops telm_defpltops = अणु
	.set_sampling_period = telemetry_def_set_sampling_period,
	.get_sampling_period = telemetry_def_get_sampling_period,
	.get_trace_verbosity = telemetry_def_get_trace_verbosity,
	.set_trace_verbosity = telemetry_def_set_trace_verbosity,
	.raw_पढ़ो_eventlog = telemetry_def_raw_पढ़ो_eventlog,
	.get_eventconfig = telemetry_def_get_eventconfig,
	.पढ़ो_eventlog = telemetry_def_पढ़ो_eventlog,
	.update_events = telemetry_def_update_events,
	.reset_events = telemetry_def_reset_events,
	.add_events = telemetry_def_add_events,
पूर्ण;

/**
 * telemetry_update_events() - Update telemetry Configuration
 * @pss_evtconfig: PSS related config. No change अगर num_evts = 0.
 * @pss_evtconfig: IOSS related config. No change अगर num_evts = 0.
 *
 * This API updates the IOSS & PSS Telemetry configuration. Old config
 * is overwritten. Call telemetry_reset_events when logging is over
 * All sample period values should be in the क्रमm of:
 * bits[6:3] -> value; bits [0:2]-> Exponent; Period = (Value *16^Exponent)
 *
 * Return: 0 success, < 0 क्रम failure
 */
पूर्णांक telemetry_update_events(काष्ठा telemetry_evtconfig pss_evtconfig,
			    काष्ठा telemetry_evtconfig ioss_evtconfig)
अणु
	वापस telm_core_conf.telem_ops->update_events(pss_evtconfig,
						       ioss_evtconfig);
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_update_events);


/**
 * telemetry_set_sampling_period() - Sets the IOSS & PSS sampling period
 * @pss_period:  placeholder क्रम PSS Period to be set.
 *		 Set to 0 अगर not required to be updated
 * @ioss_period: placeholder क्रम IOSS Period to be set
 *		 Set to 0 अगर not required to be updated
 *
 * All values should be in the क्रमm of:
 * bits[6:3] -> value; bits [0:2]-> Exponent; Period = (Value *16^Exponent)
 *
 * Return: 0 success, < 0 क्रम failure
 */
पूर्णांक telemetry_set_sampling_period(u8 pss_period, u8 ioss_period)
अणु
	वापस telm_core_conf.telem_ops->set_sampling_period(pss_period,
							     ioss_period);
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_set_sampling_period);

/**
 * telemetry_get_sampling_period() - Get IOSS & PSS min & max sampling period
 * @pss_min_period:  placeholder क्रम PSS Min Period supported
 * @pss_max_period:  placeholder क्रम PSS Max Period supported
 * @ioss_min_period: placeholder क्रम IOSS Min Period supported
 * @ioss_max_period: placeholder क्रम IOSS Max Period supported
 *
 * All values should be in the क्रमm of:
 * bits[6:3] -> value; bits [0:2]-> Exponent; Period = (Value *16^Exponent)
 *
 * Return: 0 success, < 0 क्रम failure
 */
पूर्णांक telemetry_get_sampling_period(u8 *pss_min_period, u8 *pss_max_period,
				  u8 *ioss_min_period, u8 *ioss_max_period)
अणु
	वापस telm_core_conf.telem_ops->get_sampling_period(pss_min_period,
							     pss_max_period,
							     ioss_min_period,
							     ioss_max_period);
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_get_sampling_period);


/**
 * telemetry_reset_events() - Restore the IOSS & PSS configuration to शेष
 *
 * Return: 0 success, < 0 क्रम failure
 */
पूर्णांक telemetry_reset_events(व्योम)
अणु
	वापस telm_core_conf.telem_ops->reset_events();
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_reset_events);

/**
 * telemetry_get_eventconfig() - Returns the pss and ioss events enabled
 * @pss_evtconfig: Poपूर्णांकer to PSS related configuration.
 * @pss_evtconfig: Poपूर्णांकer to IOSS related configuration.
 * @pss_len:	   Number of u32 elements allocated क्रम pss_evtconfig array
 * @ioss_len:	   Number of u32 elements allocated क्रम ioss_evtconfig array
 *
 * Return: 0 success, < 0 क्रम failure
 */
पूर्णांक telemetry_get_eventconfig(काष्ठा telemetry_evtconfig *pss_evtconfig,
			      काष्ठा telemetry_evtconfig *ioss_evtconfig,
			      पूर्णांक pss_len, पूर्णांक ioss_len)
अणु
	वापस telm_core_conf.telem_ops->get_eventconfig(pss_evtconfig,
							 ioss_evtconfig,
							 pss_len, ioss_len);
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_get_eventconfig);

/**
 * telemetry_add_events() - Add IOSS & PSS configuration to existing settings.
 * @num_pss_evts:  Number of PSS Events (<29) in pss_evपंचांगap. Can be 0.
 * @num_ioss_evts: Number of IOSS Events (<29) in ioss_evपंचांगap. Can be 0.
 * @pss_evपंचांगap:    Array of PSS Event-IDs to Enable
 * @ioss_evपंचांगap:   Array of PSS Event-IDs to Enable
 *
 * Events are appended to Old Configuration. In हाल of total events > 28, it
 * वापसs error. Call telemetry_reset_events to reset after eventlog करोne
 *
 * Return: 0 success, < 0 क्रम failure
 */
पूर्णांक telemetry_add_events(u8 num_pss_evts, u8 num_ioss_evts,
			 u32 *pss_evपंचांगap, u32 *ioss_evपंचांगap)
अणु
	वापस telm_core_conf.telem_ops->add_events(num_pss_evts,
						    num_ioss_evts, pss_evपंचांगap,
						    ioss_evपंचांगap);
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_add_events);

/**
 * telemetry_पढ़ो_events() - Fetches samples as specअगरied by evtlog.telem_evt_id
 * @telem_unit: Specअगरy whether IOSS or PSS Read
 * @evtlog:     Array of telemetry_evtlog काष्ठाs to fill data
 *		evtlog.telem_evt_id specअगरies the ids to पढ़ो
 * @len:	Length of array of evtlog
 *
 * Return: number of eventlogs पढ़ो क्रम success, < 0 क्रम failure
 */
पूर्णांक telemetry_पढ़ो_events(क्रमागत telemetry_unit telem_unit,
			  काष्ठा telemetry_evtlog *evtlog, पूर्णांक len)
अणु
	वापस telm_core_conf.telem_ops->पढ़ो_eventlog(telem_unit, evtlog,
						       len, 0);
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_पढ़ो_events);

/**
 * telemetry_raw_पढ़ो_events() - Fetch samples specअगरied by evtlog.telem_evt_id
 * @telem_unit: Specअगरy whether IOSS or PSS Read
 * @evtlog:	Array of telemetry_evtlog काष्ठाs to fill data
 *		evtlog.telem_evt_id specअगरies the ids to पढ़ो
 * @len:	Length of array of evtlog
 *
 * The caller must take care of locking in this हाल.
 *
 * Return: number of eventlogs पढ़ो क्रम success, < 0 क्रम failure
 */
पूर्णांक telemetry_raw_पढ़ो_events(क्रमागत telemetry_unit telem_unit,
			      काष्ठा telemetry_evtlog *evtlog, पूर्णांक len)
अणु
	वापस telm_core_conf.telem_ops->raw_पढ़ो_eventlog(telem_unit, evtlog,
							   len, 0);
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_raw_पढ़ो_events);

/**
 * telemetry_पढ़ो_eventlog() - Fetch the Telemetry log from PSS or IOSS
 * @telem_unit: Specअगरy whether IOSS or PSS Read
 * @evtlog:	Array of telemetry_evtlog काष्ठाs to fill data
 * @len:	Length of array of evtlog
 *
 * Return: number of eventlogs पढ़ो क्रम success, < 0 क्रम failure
 */
पूर्णांक telemetry_पढ़ो_eventlog(क्रमागत telemetry_unit telem_unit,
			    काष्ठा telemetry_evtlog *evtlog, पूर्णांक len)
अणु
	वापस telm_core_conf.telem_ops->पढ़ो_eventlog(telem_unit, evtlog,
						       len, 1);
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_पढ़ो_eventlog);

/**
 * telemetry_raw_पढ़ो_eventlog() - Fetch the Telemetry log from PSS or IOSS
 * @telem_unit: Specअगरy whether IOSS or PSS Read
 * @evtlog:	Array of telemetry_evtlog काष्ठाs to fill data
 * @len:	Length of array of evtlog
 *
 * The caller must take care of locking in this हाल.
 *
 * Return: number of eventlogs पढ़ो क्रम success, < 0 क्रम failure
 */
पूर्णांक telemetry_raw_पढ़ो_eventlog(क्रमागत telemetry_unit telem_unit,
				काष्ठा telemetry_evtlog *evtlog, पूर्णांक len)
अणु
	वापस telm_core_conf.telem_ops->raw_पढ़ो_eventlog(telem_unit, evtlog,
							   len, 1);
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_raw_पढ़ो_eventlog);


/**
 * telemetry_get_trace_verbosity() - Get the IOSS & PSS Trace verbosity
 * @telem_unit: Specअगरy whether IOSS or PSS Read
 * @verbosity:	Poपूर्णांकer to वापस Verbosity
 *
 * Return: 0 success, < 0 क्रम failure
 */
पूर्णांक telemetry_get_trace_verbosity(क्रमागत telemetry_unit telem_unit,
				  u32 *verbosity)
अणु
	वापस telm_core_conf.telem_ops->get_trace_verbosity(telem_unit,
							     verbosity);
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_get_trace_verbosity);


/**
 * telemetry_set_trace_verbosity() - Update the IOSS & PSS Trace verbosity
 * @telem_unit: Specअगरy whether IOSS or PSS Read
 * @verbosity:	Verbosity to set
 *
 * Return: 0 success, < 0 क्रम failure
 */
पूर्णांक telemetry_set_trace_verbosity(क्रमागत telemetry_unit telem_unit, u32 verbosity)
अणु
	वापस telm_core_conf.telem_ops->set_trace_verbosity(telem_unit,
							     verbosity);
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_set_trace_verbosity);

/**
 * telemetry_set_pltdata() - Set the platक्रमm specअगरic Data
 * @ops:	Poपूर्णांकer to ops काष्ठाure
 * @pltconfig:	Platक्रमm config data
 *
 * Usage by other than telemetry pltdrv module is invalid
 *
 * Return: 0 success, < 0 क्रम failure
 */
पूर्णांक telemetry_set_pltdata(स्थिर काष्ठा telemetry_core_ops *ops,
			  काष्ठा telemetry_plt_config *pltconfig)
अणु
	अगर (ops)
		telm_core_conf.telem_ops = ops;

	अगर (pltconfig)
		telm_core_conf.plt_config = pltconfig;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_set_pltdata);

/**
 * telemetry_clear_pltdata() - Clear the platक्रमm specअगरic Data
 *
 * Usage by other than telemetry pltdrv module is invalid
 *
 * Return: 0 success, < 0 क्रम failure
 */
पूर्णांक telemetry_clear_pltdata(व्योम)
अणु
	telm_core_conf.telem_ops = &telm_defpltops;
	telm_core_conf.plt_config = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_clear_pltdata);

/**
 * telemetry_get_pltdata() - Return telemetry platक्रमm config
 *
 * May be used by other telemetry modules to get platक्रमm specअगरic
 * configuration.
 */
काष्ठा telemetry_plt_config *telemetry_get_pltdata(व्योम)
अणु
	वापस telm_core_conf.plt_config;
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_get_pltdata);

अटल अंतरभूत पूर्णांक telemetry_get_pssevtname(क्रमागत telemetry_unit telem_unit,
					   स्थिर अक्षर **name, पूर्णांक len)
अणु
	काष्ठा telemetry_unit_config psscfg;
	पूर्णांक i;

	अगर (!telm_core_conf.plt_config)
		वापस -EINVAL;

	psscfg = telm_core_conf.plt_config->pss_config;

	अगर (len > psscfg.ssram_evts_used)
		len = psscfg.ssram_evts_used;

	क्रम (i = 0; i < len; i++)
		name[i] = psscfg.telem_evts[i].name;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक telemetry_get_iossevtname(क्रमागत telemetry_unit telem_unit,
					    स्थिर अक्षर **name, पूर्णांक len)
अणु
	काष्ठा telemetry_unit_config iosscfg;
	पूर्णांक i;

	अगर (!(telm_core_conf.plt_config))
		वापस -EINVAL;

	iosscfg = telm_core_conf.plt_config->ioss_config;

	अगर (len > iosscfg.ssram_evts_used)
		len = iosscfg.ssram_evts_used;

	क्रम (i = 0; i < len; i++)
		name[i] = iosscfg.telem_evts[i].name;

	वापस 0;

पूर्ण

/**
 * telemetry_get_evtname() - Checkअगर platक्रमm config is valid
 * @telem_unit:	Telemetry Unit to check
 * @name:	Array of अक्षरacter poपूर्णांकers to contain name
 * @len:	length of array name provided by user
 *
 * Usage by other than telemetry debugfs module is invalid
 *
 * Return: 0 success, < 0 क्रम failure
 */
पूर्णांक telemetry_get_evtname(क्रमागत telemetry_unit telem_unit,
			  स्थिर अक्षर **name, पूर्णांक len)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (telem_unit == TELEM_PSS)
		ret = telemetry_get_pssevtname(telem_unit, name, len);

	अन्यथा अगर (telem_unit == TELEM_IOSS)
		ret = telemetry_get_iossevtname(telem_unit, name, len);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(telemetry_get_evtname);

अटल पूर्णांक __init telemetry_module_init(व्योम)
अणु
	pr_info(pr_fmt(DRIVER_NAME) " Init\n");

	telm_core_conf.telem_ops = &telm_defpltops;
	वापस 0;
पूर्ण

अटल व्योम __निकास telemetry_module_निकास(व्योम)
अणु
पूर्ण

module_init(telemetry_module_init);
module_निकास(telemetry_module_निकास);

MODULE_AUTHOR("Souvik Kumar Chakravarty <souvik.k.chakravarty@intel.com>");
MODULE_DESCRIPTION("Intel SoC Telemetry Interface");
MODULE_LICENSE("GPL v2");
