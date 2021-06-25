<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * devfreq_cooling: Thermal cooling device implementation क्रम devices using
 *                  devfreq
 *
 * Copyright (C) 2014-2015 ARM Limited
 *
 */

#अगर_अघोषित __DEVFREQ_COOLING_H__
#घोषणा __DEVFREQ_COOLING_H__

#समावेश <linux/devfreq.h>
#समावेश <linux/thermal.h>


/**
 * काष्ठा devfreq_cooling_घातer - Devfreq cooling घातer ops
 * @get_real_घातer:	When this is set, the framework uses it to ask the
 *			device driver क्रम the actual घातer.
 *			Some devices have more sophisticated methods
 *			(like घातer counters) to approximate the actual घातer
 *			that they use.
 *			This function provides more accurate data to the
 *			thermal governor. When the driver करोes not provide
 *			such function, framework just uses pre-calculated
 *			table and scale the घातer by 'utilization'
 *			(based on 'busy_time' and 'total_time' taken from
 *			devfreq 'last_status').
 *			The value वापसed by this function must be lower
 *			or equal than the maximum घातer value
 *			क्रम the current	state
 *			(which can be found in घातer_table[state]).
 *			When this पूर्णांकerface is used, the घातer_table holds
 *			max total (अटल + dynamic) घातer value क्रम each OPP.
 */
काष्ठा devfreq_cooling_घातer अणु
	पूर्णांक (*get_real_घातer)(काष्ठा devfreq *df, u32 *घातer,
			      अचिन्हित दीर्घ freq, अचिन्हित दीर्घ voltage);
पूर्ण;

#अगर_घोषित CONFIG_DEVFREQ_THERMAL

काष्ठा thermal_cooling_device *
of_devfreq_cooling_रेजिस्टर_घातer(काष्ठा device_node *np, काष्ठा devfreq *df,
				  काष्ठा devfreq_cooling_घातer *dfc_घातer);
काष्ठा thermal_cooling_device *
of_devfreq_cooling_रेजिस्टर(काष्ठा device_node *np, काष्ठा devfreq *df);
काष्ठा thermal_cooling_device *devfreq_cooling_रेजिस्टर(काष्ठा devfreq *df);
व्योम devfreq_cooling_unरेजिस्टर(काष्ठा thermal_cooling_device *dfc);
काष्ठा thermal_cooling_device *
devfreq_cooling_em_रेजिस्टर(काष्ठा devfreq *df,
			    काष्ठा devfreq_cooling_घातer *dfc_घातer);

#अन्यथा /* !CONFIG_DEVFREQ_THERMAL */

अटल अंतरभूत काष्ठा thermal_cooling_device *
of_devfreq_cooling_रेजिस्टर_घातer(काष्ठा device_node *np, काष्ठा devfreq *df,
				  काष्ठा devfreq_cooling_घातer *dfc_घातer)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत काष्ठा thermal_cooling_device *
of_devfreq_cooling_रेजिस्टर(काष्ठा device_node *np, काष्ठा devfreq *df)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत काष्ठा thermal_cooling_device *
devfreq_cooling_रेजिस्टर(काष्ठा devfreq *df)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत काष्ठा thermal_cooling_device *
devfreq_cooling_em_रेजिस्टर(काष्ठा devfreq *df,
			    काष्ठा devfreq_cooling_घातer *dfc_घातer)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत व्योम
devfreq_cooling_unरेजिस्टर(काष्ठा thermal_cooling_device *dfc)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_DEVFREQ_THERMAL */
#पूर्ण_अगर /* __DEVFREQ_COOLING_H__ */
