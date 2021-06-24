<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Generic OPP Interface
 *
 * Copyright (C) 2009-2010 Texas Instruments Incorporated.
 *	Nishanth Menon
 *	Romit Dasgupta
 *	Kevin Hilman
 */

#अगर_अघोषित __LINUX_OPP_H__
#घोषणा __LINUX_OPP_H__

#समावेश <linux/energy_model.h>
#समावेश <linux/err.h>
#समावेश <linux/notअगरier.h>

काष्ठा clk;
काष्ठा regulator;
काष्ठा dev_pm_opp;
काष्ठा device;
काष्ठा opp_table;

क्रमागत dev_pm_opp_event अणु
	OPP_EVENT_ADD, OPP_EVENT_REMOVE, OPP_EVENT_ENABLE, OPP_EVENT_DISABLE,
	OPP_EVENT_ADJUST_VOLTAGE,
पूर्ण;

/**
 * काष्ठा dev_pm_opp_supply - Power supply voltage/current values
 * @u_volt:	Target voltage in microvolts corresponding to this OPP
 * @u_volt_min:	Minimum voltage in microvolts corresponding to this OPP
 * @u_volt_max:	Maximum voltage in microvolts corresponding to this OPP
 * @u_amp:	Maximum current drawn by the device in microamperes
 *
 * This काष्ठाure stores the voltage/current values क्रम a single घातer supply.
 */
काष्ठा dev_pm_opp_supply अणु
	अचिन्हित दीर्घ u_volt;
	अचिन्हित दीर्घ u_volt_min;
	अचिन्हित दीर्घ u_volt_max;
	अचिन्हित दीर्घ u_amp;
पूर्ण;

/**
 * काष्ठा dev_pm_opp_icc_bw - Interconnect bandwidth values
 * @avg:	Average bandwidth corresponding to this OPP (in icc units)
 * @peak:	Peak bandwidth corresponding to this OPP (in icc units)
 *
 * This काष्ठाure stores the bandwidth values क्रम a single पूर्णांकerconnect path.
 */
काष्ठा dev_pm_opp_icc_bw अणु
	u32 avg;
	u32 peak;
पूर्ण;

/**
 * काष्ठा dev_pm_opp_info - OPP freq/voltage/current values
 * @rate:	Target clk rate in hz
 * @supplies:	Array of voltage/current values क्रम all घातer supplies
 *
 * This काष्ठाure stores the freq/voltage/current values क्रम a single OPP.
 */
काष्ठा dev_pm_opp_info अणु
	अचिन्हित दीर्घ rate;
	काष्ठा dev_pm_opp_supply *supplies;
पूर्ण;

/**
 * काष्ठा dev_pm_set_opp_data - Set OPP data
 * @old_opp:	Old OPP info
 * @new_opp:	New OPP info
 * @regulators:	Array of regulator poपूर्णांकers
 * @regulator_count: Number of regulators
 * @clk:	Poपूर्णांकer to clk
 * @dev:	Poपूर्णांकer to the काष्ठा device
 *
 * This काष्ठाure contains all inक्रमmation required क्रम setting an OPP.
 */
काष्ठा dev_pm_set_opp_data अणु
	काष्ठा dev_pm_opp_info old_opp;
	काष्ठा dev_pm_opp_info new_opp;

	काष्ठा regulator **regulators;
	अचिन्हित पूर्णांक regulator_count;
	काष्ठा clk *clk;
	काष्ठा device *dev;
पूर्ण;

#अगर defined(CONFIG_PM_OPP)

काष्ठा opp_table *dev_pm_opp_get_opp_table(काष्ठा device *dev);
व्योम dev_pm_opp_put_opp_table(काष्ठा opp_table *opp_table);

अचिन्हित दीर्घ dev_pm_opp_get_voltage(काष्ठा dev_pm_opp *opp);

अचिन्हित दीर्घ dev_pm_opp_get_freq(काष्ठा dev_pm_opp *opp);

अचिन्हित पूर्णांक dev_pm_opp_get_level(काष्ठा dev_pm_opp *opp);

अचिन्हित पूर्णांक dev_pm_opp_get_required_pstate(काष्ठा dev_pm_opp *opp,
					    अचिन्हित पूर्णांक index);

bool dev_pm_opp_is_turbo(काष्ठा dev_pm_opp *opp);

पूर्णांक dev_pm_opp_get_opp_count(काष्ठा device *dev);
अचिन्हित दीर्घ dev_pm_opp_get_max_घड़ी_latency(काष्ठा device *dev);
अचिन्हित दीर्घ dev_pm_opp_get_max_volt_latency(काष्ठा device *dev);
अचिन्हित दीर्घ dev_pm_opp_get_max_transition_latency(काष्ठा device *dev);
अचिन्हित दीर्घ dev_pm_opp_get_suspend_opp_freq(काष्ठा device *dev);

काष्ठा dev_pm_opp *dev_pm_opp_find_freq_exact(काष्ठा device *dev,
					      अचिन्हित दीर्घ freq,
					      bool available);
काष्ठा dev_pm_opp *dev_pm_opp_find_level_exact(काष्ठा device *dev,
					       अचिन्हित पूर्णांक level);
काष्ठा dev_pm_opp *dev_pm_opp_find_level_उच्चमान(काष्ठा device *dev,
					      अचिन्हित पूर्णांक *level);

काष्ठा dev_pm_opp *dev_pm_opp_find_freq_न्यूनमान(काष्ठा device *dev,
					      अचिन्हित दीर्घ *freq);
काष्ठा dev_pm_opp *dev_pm_opp_find_freq_उच्चमान_by_volt(काष्ठा device *dev,
						     अचिन्हित दीर्घ u_volt);

काष्ठा dev_pm_opp *dev_pm_opp_find_freq_उच्चमान(काष्ठा device *dev,
					     अचिन्हित दीर्घ *freq);
व्योम dev_pm_opp_put(काष्ठा dev_pm_opp *opp);

पूर्णांक dev_pm_opp_add(काष्ठा device *dev, अचिन्हित दीर्घ freq,
		   अचिन्हित दीर्घ u_volt);
व्योम dev_pm_opp_हटाओ(काष्ठा device *dev, अचिन्हित दीर्घ freq);
व्योम dev_pm_opp_हटाओ_all_dynamic(काष्ठा device *dev);

पूर्णांक dev_pm_opp_adjust_voltage(काष्ठा device *dev, अचिन्हित दीर्घ freq,
			      अचिन्हित दीर्घ u_volt, अचिन्हित दीर्घ u_volt_min,
			      अचिन्हित दीर्घ u_volt_max);

पूर्णांक dev_pm_opp_enable(काष्ठा device *dev, अचिन्हित दीर्घ freq);

पूर्णांक dev_pm_opp_disable(काष्ठा device *dev, अचिन्हित दीर्घ freq);

पूर्णांक dev_pm_opp_रेजिस्टर_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb);
पूर्णांक dev_pm_opp_unरेजिस्टर_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb);

काष्ठा opp_table *dev_pm_opp_set_supported_hw(काष्ठा device *dev, स्थिर u32 *versions, अचिन्हित पूर्णांक count);
व्योम dev_pm_opp_put_supported_hw(काष्ठा opp_table *opp_table);
पूर्णांक devm_pm_opp_set_supported_hw(काष्ठा device *dev, स्थिर u32 *versions, अचिन्हित पूर्णांक count);
काष्ठा opp_table *dev_pm_opp_set_prop_name(काष्ठा device *dev, स्थिर अक्षर *name);
व्योम dev_pm_opp_put_prop_name(काष्ठा opp_table *opp_table);
काष्ठा opp_table *dev_pm_opp_set_regulators(काष्ठा device *dev, स्थिर अक्षर * स्थिर names[], अचिन्हित पूर्णांक count);
व्योम dev_pm_opp_put_regulators(काष्ठा opp_table *opp_table);
पूर्णांक devm_pm_opp_set_regulators(काष्ठा device *dev, स्थिर अक्षर * स्थिर names[], अचिन्हित पूर्णांक count);
काष्ठा opp_table *dev_pm_opp_set_clkname(काष्ठा device *dev, स्थिर अक्षर *name);
व्योम dev_pm_opp_put_clkname(काष्ठा opp_table *opp_table);
पूर्णांक devm_pm_opp_set_clkname(काष्ठा device *dev, स्थिर अक्षर *name);
काष्ठा opp_table *dev_pm_opp_रेजिस्टर_set_opp_helper(काष्ठा device *dev, पूर्णांक (*set_opp)(काष्ठा dev_pm_set_opp_data *data));
व्योम dev_pm_opp_unरेजिस्टर_set_opp_helper(काष्ठा opp_table *opp_table);
पूर्णांक devm_pm_opp_रेजिस्टर_set_opp_helper(काष्ठा device *dev, पूर्णांक (*set_opp)(काष्ठा dev_pm_set_opp_data *data));
काष्ठा opp_table *dev_pm_opp_attach_genpd(काष्ठा device *dev, स्थिर अक्षर **names, काष्ठा device ***virt_devs);
व्योम dev_pm_opp_detach_genpd(काष्ठा opp_table *opp_table);
पूर्णांक devm_pm_opp_attach_genpd(काष्ठा device *dev, स्थिर अक्षर **names, काष्ठा device ***virt_devs);
काष्ठा dev_pm_opp *dev_pm_opp_xlate_required_opp(काष्ठा opp_table *src_table, काष्ठा opp_table *dst_table, काष्ठा dev_pm_opp *src_opp);
पूर्णांक dev_pm_opp_xlate_perक्रमmance_state(काष्ठा opp_table *src_table, काष्ठा opp_table *dst_table, अचिन्हित पूर्णांक pstate);
पूर्णांक dev_pm_opp_set_rate(काष्ठा device *dev, अचिन्हित दीर्घ target_freq);
पूर्णांक dev_pm_opp_set_opp(काष्ठा device *dev, काष्ठा dev_pm_opp *opp);
पूर्णांक dev_pm_opp_set_sharing_cpus(काष्ठा device *cpu_dev, स्थिर काष्ठा cpumask *cpumask);
पूर्णांक dev_pm_opp_get_sharing_cpus(काष्ठा device *cpu_dev, काष्ठा cpumask *cpumask);
व्योम dev_pm_opp_हटाओ_table(काष्ठा device *dev);
व्योम dev_pm_opp_cpumask_हटाओ_table(स्थिर काष्ठा cpumask *cpumask);
पूर्णांक dev_pm_opp_sync_regulators(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत काष्ठा opp_table *dev_pm_opp_get_opp_table(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा opp_table *dev_pm_opp_get_opp_table_indexed(काष्ठा device *dev, पूर्णांक index)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_put_opp_table(काष्ठा opp_table *opp_table) अणुपूर्ण

अटल अंतरभूत अचिन्हित दीर्घ dev_pm_opp_get_voltage(काष्ठा dev_pm_opp *opp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ dev_pm_opp_get_freq(काष्ठा dev_pm_opp *opp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dev_pm_opp_get_level(काष्ठा dev_pm_opp *opp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक dev_pm_opp_get_required_pstate(काष्ठा dev_pm_opp *opp,
					    अचिन्हित पूर्णांक index)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool dev_pm_opp_is_turbo(काष्ठा dev_pm_opp *opp)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_get_opp_count(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ dev_pm_opp_get_max_घड़ी_latency(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ dev_pm_opp_get_max_volt_latency(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ dev_pm_opp_get_max_transition_latency(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ dev_pm_opp_get_suspend_opp_freq(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा dev_pm_opp *dev_pm_opp_find_freq_exact(काष्ठा device *dev,
					अचिन्हित दीर्घ freq, bool available)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा dev_pm_opp *dev_pm_opp_find_level_exact(काष्ठा device *dev,
					अचिन्हित पूर्णांक level)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा dev_pm_opp *dev_pm_opp_find_level_उच्चमान(काष्ठा device *dev,
					अचिन्हित पूर्णांक *level)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा dev_pm_opp *dev_pm_opp_find_freq_न्यूनमान(काष्ठा device *dev,
					अचिन्हित दीर्घ *freq)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा dev_pm_opp *dev_pm_opp_find_freq_उच्चमान_by_volt(काष्ठा device *dev,
					अचिन्हित दीर्घ u_volt)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा dev_pm_opp *dev_pm_opp_find_freq_उच्चमान(काष्ठा device *dev,
					अचिन्हित दीर्घ *freq)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_put(काष्ठा dev_pm_opp *opp) अणुपूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_add(काष्ठा device *dev, अचिन्हित दीर्घ freq,
					अचिन्हित दीर्घ u_volt)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_हटाओ(काष्ठा device *dev, अचिन्हित दीर्घ freq)
अणु
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_हटाओ_all_dynamic(काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
dev_pm_opp_adjust_voltage(काष्ठा device *dev, अचिन्हित दीर्घ freq,
			  अचिन्हित दीर्घ u_volt, अचिन्हित दीर्घ u_volt_min,
			  अचिन्हित दीर्घ u_volt_max)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_enable(काष्ठा device *dev, अचिन्हित दीर्घ freq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_disable(काष्ठा device *dev, अचिन्हित दीर्घ freq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_रेजिस्टर_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_unरेजिस्टर_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा opp_table *dev_pm_opp_set_supported_hw(काष्ठा device *dev,
							    स्थिर u32 *versions,
							    अचिन्हित पूर्णांक count)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_put_supported_hw(काष्ठा opp_table *opp_table) अणुपूर्ण

अटल अंतरभूत पूर्णांक devm_pm_opp_set_supported_hw(काष्ठा device *dev,
					       स्थिर u32 *versions,
					       अचिन्हित पूर्णांक count)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा opp_table *dev_pm_opp_रेजिस्टर_set_opp_helper(काष्ठा device *dev,
			पूर्णांक (*set_opp)(काष्ठा dev_pm_set_opp_data *data))
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_unरेजिस्टर_set_opp_helper(काष्ठा opp_table *opp_table) अणुपूर्ण

अटल अंतरभूत पूर्णांक devm_pm_opp_रेजिस्टर_set_opp_helper(काष्ठा device *dev,
				    पूर्णांक (*set_opp)(काष्ठा dev_pm_set_opp_data *data))
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा opp_table *dev_pm_opp_set_prop_name(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_put_prop_name(काष्ठा opp_table *opp_table) अणुपूर्ण

अटल अंतरभूत काष्ठा opp_table *dev_pm_opp_set_regulators(काष्ठा device *dev, स्थिर अक्षर * स्थिर names[], अचिन्हित पूर्णांक count)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_put_regulators(काष्ठा opp_table *opp_table) अणुपूर्ण

अटल अंतरभूत पूर्णांक devm_pm_opp_set_regulators(काष्ठा device *dev,
					     स्थिर अक्षर * स्थिर names[],
					     अचिन्हित पूर्णांक count)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा opp_table *dev_pm_opp_set_clkname(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_put_clkname(काष्ठा opp_table *opp_table) अणुपूर्ण

अटल अंतरभूत पूर्णांक devm_pm_opp_set_clkname(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा opp_table *dev_pm_opp_attach_genpd(काष्ठा device *dev, स्थिर अक्षर **names, काष्ठा device ***virt_devs)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_detach_genpd(काष्ठा opp_table *opp_table) अणुपूर्ण

अटल अंतरभूत पूर्णांक devm_pm_opp_attach_genpd(काष्ठा device *dev,
					   स्थिर अक्षर **names,
					   काष्ठा device ***virt_devs)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा dev_pm_opp *dev_pm_opp_xlate_required_opp(काष्ठा opp_table *src_table,
				काष्ठा opp_table *dst_table, काष्ठा dev_pm_opp *src_opp)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_xlate_perक्रमmance_state(काष्ठा opp_table *src_table, काष्ठा opp_table *dst_table, अचिन्हित पूर्णांक pstate)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_set_rate(काष्ठा device *dev, अचिन्हित दीर्घ target_freq)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_set_opp(काष्ठा device *dev, काष्ठा dev_pm_opp *opp)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_set_sharing_cpus(काष्ठा device *cpu_dev, स्थिर काष्ठा cpumask *cpumask)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_get_sharing_cpus(काष्ठा device *cpu_dev, काष्ठा cpumask *cpumask)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_हटाओ_table(काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_cpumask_हटाओ_table(स्थिर काष्ठा cpumask *cpumask)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_sync_regulators(काष्ठा device *dev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#पूर्ण_अगर		/* CONFIG_PM_OPP */

#अगर defined(CONFIG_PM_OPP) && defined(CONFIG_OF)
पूर्णांक dev_pm_opp_of_add_table(काष्ठा device *dev);
पूर्णांक dev_pm_opp_of_add_table_indexed(काष्ठा device *dev, पूर्णांक index);
पूर्णांक dev_pm_opp_of_add_table_noclk(काष्ठा device *dev, पूर्णांक index);
व्योम dev_pm_opp_of_हटाओ_table(काष्ठा device *dev);
पूर्णांक devm_pm_opp_of_add_table(काष्ठा device *dev);
पूर्णांक dev_pm_opp_of_cpumask_add_table(स्थिर काष्ठा cpumask *cpumask);
व्योम dev_pm_opp_of_cpumask_हटाओ_table(स्थिर काष्ठा cpumask *cpumask);
पूर्णांक dev_pm_opp_of_get_sharing_cpus(काष्ठा device *cpu_dev, काष्ठा cpumask *cpumask);
काष्ठा device_node *dev_pm_opp_of_get_opp_desc_node(काष्ठा device *dev);
काष्ठा device_node *dev_pm_opp_get_of_node(काष्ठा dev_pm_opp *opp);
पूर्णांक of_get_required_opp_perक्रमmance_state(काष्ठा device_node *np, पूर्णांक index);
पूर्णांक dev_pm_opp_of_find_icc_paths(काष्ठा device *dev, काष्ठा opp_table *opp_table);
पूर्णांक dev_pm_opp_of_रेजिस्टर_em(काष्ठा device *dev, काष्ठा cpumask *cpus);
अटल अंतरभूत व्योम dev_pm_opp_of_unरेजिस्टर_em(काष्ठा device *dev)
अणु
	em_dev_unरेजिस्टर_perf_करोमुख्य(dev);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक dev_pm_opp_of_add_table(काष्ठा device *dev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_of_add_table_indexed(काष्ठा device *dev, पूर्णांक index)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_of_add_table_noclk(काष्ठा device *dev, पूर्णांक index)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_of_हटाओ_table(काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक devm_pm_opp_of_add_table(काष्ठा device *dev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_of_cpumask_add_table(स्थिर काष्ठा cpumask *cpumask)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_of_cpumask_हटाओ_table(स्थिर काष्ठा cpumask *cpumask)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_of_get_sharing_cpus(काष्ठा device *cpu_dev, काष्ठा cpumask *cpumask)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा device_node *dev_pm_opp_of_get_opp_desc_node(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *dev_pm_opp_get_of_node(काष्ठा dev_pm_opp *opp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_of_रेजिस्टर_em(काष्ठा device *dev,
					    काष्ठा cpumask *cpus)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_of_unरेजिस्टर_em(काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक of_get_required_opp_perक्रमmance_state(काष्ठा device_node *np, पूर्णांक index)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_opp_of_find_icc_paths(काष्ठा device *dev, काष्ठा opp_table *opp_table)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर		/* __LINUX_OPP_H__ */
