<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Data types and headers क्रम RAPL support
 *
 *  Copyright (C) 2019  Intel Corporation.
 *
 *  Author: Zhang Rui <rui.zhang@पूर्णांकel.com>
 */

#अगर_अघोषित __INTEL_RAPL_H__
#घोषणा __INTEL_RAPL_H__

#समावेश <linux/types.h>
#समावेश <linux/घातercap.h>
#समावेश <linux/cpuhotplug.h>

क्रमागत rapl_करोमुख्य_type अणु
	RAPL_DOMAIN_PACKAGE,	/* entire package/socket */
	RAPL_DOMAIN_PP0,	/* core घातer plane */
	RAPL_DOMAIN_PP1,	/* graphics uncore */
	RAPL_DOMAIN_DRAM,	/* DRAM control_type */
	RAPL_DOMAIN_PLATFORM,	/* PSys control_type */
	RAPL_DOMAIN_MAX,
पूर्ण;

क्रमागत rapl_करोमुख्य_reg_id अणु
	RAPL_DOMAIN_REG_LIMIT,
	RAPL_DOMAIN_REG_STATUS,
	RAPL_DOMAIN_REG_PERF,
	RAPL_DOMAIN_REG_POLICY,
	RAPL_DOMAIN_REG_INFO,
	RAPL_DOMAIN_REG_PL4,
	RAPL_DOMAIN_REG_MAX,
पूर्ण;

काष्ठा rapl_करोमुख्य;

क्रमागत rapl_primitives अणु
	ENERGY_COUNTER,
	POWER_LIMIT1,
	POWER_LIMIT2,
	POWER_LIMIT4,
	FW_LOCK,

	PL1_ENABLE,		/* घातer limit 1, aka दीर्घ term */
	PL1_CLAMP,		/* allow frequency to go below OS request */
	PL2_ENABLE,		/* घातer limit 2, aka लघु term, instantaneous */
	PL2_CLAMP,
	PL4_ENABLE,		/* घातer limit 4, aka max peak घातer */

	TIME_WINDOW1,		/* दीर्घ term */
	TIME_WINDOW2,		/* लघु term */
	THERMAL_SPEC_POWER,
	MAX_POWER,

	MIN_POWER,
	MAX_TIME_WINDOW,
	THROTTLED_TIME,
	PRIORITY_LEVEL,

	/* below are not raw primitive data */
	AVERAGE_POWER,
	NR_RAPL_PRIMITIVES,
पूर्ण;

काष्ठा rapl_करोमुख्य_data अणु
	u64 primitives[NR_RAPL_PRIMITIVES];
	अचिन्हित दीर्घ बारtamp;
पूर्ण;

#घोषणा NR_POWER_LIMITS (3)
काष्ठा rapl_घातer_limit अणु
	काष्ठा घातercap_zone_स्थिरraपूर्णांक *स्थिरraपूर्णांक;
	पूर्णांक prim_id;		/* primitive ID used to enable */
	काष्ठा rapl_करोमुख्य *करोमुख्य;
	स्थिर अक्षर *name;
	u64 last_घातer_limit;
पूर्ण;

काष्ठा rapl_package;

#घोषणा RAPL_DOMAIN_NAME_LENGTH 16

काष्ठा rapl_करोमुख्य अणु
	अक्षर name[RAPL_DOMAIN_NAME_LENGTH];
	क्रमागत rapl_करोमुख्य_type id;
	u64 regs[RAPL_DOMAIN_REG_MAX];
	काष्ठा घातercap_zone घातer_zone;
	काष्ठा rapl_करोमुख्य_data rdd;
	काष्ठा rapl_घातer_limit rpl[NR_POWER_LIMITS];
	u64 attr_map;		/* track capabilities */
	अचिन्हित पूर्णांक state;
	अचिन्हित पूर्णांक करोमुख्य_energy_unit;
	काष्ठा rapl_package *rp;
पूर्ण;

काष्ठा reg_action अणु
	u64 reg;
	u64 mask;
	u64 value;
	पूर्णांक err;
पूर्ण;

/**
 * काष्ठा rapl_अगर_priv: निजी data क्रम dअगरferent RAPL पूर्णांकerfaces
 * @control_type:		Each RAPL पूर्णांकerface must have its own घातercap
 *				control type.
 * @platक्रमm_rapl_करोमुख्य:	Optional. Some RAPL पूर्णांकerface may have platक्रमm
 *				level RAPL control.
 * @pcap_rapl_online:		CPU hotplug state क्रम each RAPL पूर्णांकerface.
 * @reg_unit:			Register क्रम getting energy/घातer/समय unit.
 * @regs:			Register sets क्रम dअगरferent RAPL Doमुख्यs.
 * @limits:			Number of घातer limits supported by each करोमुख्य.
 * @पढ़ो_raw:			Callback क्रम पढ़ोing RAPL पूर्णांकerface specअगरic
 *				रेजिस्टरs.
 * @ग_लिखो_raw:			Callback क्रम writing RAPL पूर्णांकerface specअगरic
 *				रेजिस्टरs.
 */
काष्ठा rapl_अगर_priv अणु
	काष्ठा घातercap_control_type *control_type;
	काष्ठा rapl_करोमुख्य *platक्रमm_rapl_करोमुख्य;
	क्रमागत cpuhp_state pcap_rapl_online;
	u64 reg_unit;
	u64 regs[RAPL_DOMAIN_MAX][RAPL_DOMAIN_REG_MAX];
	पूर्णांक limits[RAPL_DOMAIN_MAX];
	पूर्णांक (*पढ़ो_raw)(पूर्णांक cpu, काष्ठा reg_action *ra);
	पूर्णांक (*ग_लिखो_raw)(पूर्णांक cpu, काष्ठा reg_action *ra);
पूर्ण;

/* maximum rapl package करोमुख्य name: package-%d-die-%d */
#घोषणा PACKAGE_DOMAIN_NAME_LENGTH 30

काष्ठा rapl_package अणु
	अचिन्हित पूर्णांक id;	/* logical die id, equals physical 1-die प्रणालीs */
	अचिन्हित पूर्णांक nr_करोमुख्यs;
	अचिन्हित दीर्घ करोमुख्य_map;	/* bit map of active करोमुख्यs */
	अचिन्हित पूर्णांक घातer_unit;
	अचिन्हित पूर्णांक energy_unit;
	अचिन्हित पूर्णांक समय_unit;
	काष्ठा rapl_करोमुख्य *करोमुख्यs;	/* array of करोमुख्यs, sized at runसमय */
	काष्ठा घातercap_zone *घातer_zone;	/* keep track of parent zone */
	अचिन्हित दीर्घ घातer_limit_irq;	/* keep track of package घातer limit
					 * notअगरy पूर्णांकerrupt enable status.
					 */
	काष्ठा list_head plist;
	पूर्णांक lead_cpu;		/* one active cpu per package क्रम access */
	/* Track active cpus */
	काष्ठा cpumask cpumask;
	अक्षर name[PACKAGE_DOMAIN_NAME_LENGTH];
	काष्ठा rapl_अगर_priv *priv;
पूर्ण;

काष्ठा rapl_package *rapl_find_package_करोमुख्य(पूर्णांक cpu, काष्ठा rapl_अगर_priv *priv);
काष्ठा rapl_package *rapl_add_package(पूर्णांक cpu, काष्ठा rapl_अगर_priv *priv);
व्योम rapl_हटाओ_package(काष्ठा rapl_package *rp);

#पूर्ण_अगर /* __INTEL_RAPL_H__ */
