<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#अगर_अघोषित _CORESIGHT_ETM_PERF_H
#घोषणा _CORESIGHT_ETM_PERF_H

#समावेश <linux/percpu-defs.h>
#समावेश "coresight-priv.h"

काष्ठा coresight_device;

/*
 * In both ETMv3 and v4 the maximum number of address comparator implentable
 * is 8.  The actual number is implementation specअगरic and will be checked
 * when filters are applied.
 */
#घोषणा ETM_ADDR_CMP_MAX	8

/**
 * काष्ठा eपंचांग_filter - single inकाष्ठाion range or start/stop configuration.
 * @start_addr:	The address to start tracing on.
 * @stop_addr:	The address to stop tracing on.
 * @type:	Is this a range or start/stop filter.
 */
काष्ठा eपंचांग_filter अणु
	अचिन्हित दीर्घ start_addr;
	अचिन्हित दीर्घ stop_addr;
	क्रमागत eपंचांग_addr_type type;
पूर्ण;

/**
 * काष्ठा eपंचांग_filters - set of filters क्रम a session
 * @eपंचांग_filter:	All the filters क्रम this session.
 * @nr_filters:	Number of filters
 * @ssstatus:	Status of the start/stop logic.
 */
काष्ठा eपंचांग_filters अणु
	काष्ठा eपंचांग_filter	eपंचांग_filter[ETM_ADDR_CMP_MAX];
	अचिन्हित पूर्णांक		nr_filters;
	bool			ssstatus;
पूर्ण;

/**
 * काष्ठा eपंचांग_event_data - Coresight specअगरics associated to an event
 * @work:		Handle to मुक्त allocated memory outside IRQ context.
 * @mask:		Hold the CPU(s) this event was set क्रम.
 * @snk_config:		The sink configuration.
 * @path:		An array of path, each slot क्रम one CPU.
 */
काष्ठा eपंचांग_event_data अणु
	काष्ठा work_काष्ठा work;
	cpumask_t mask;
	व्योम *snk_config;
	काष्ठा list_head * __percpu *path;
पूर्ण;

#अगर IS_ENABLED(CONFIG_CORESIGHT)
पूर्णांक eपंचांग_perf_symlink(काष्ठा coresight_device *csdev, bool link);
पूर्णांक eपंचांग_perf_add_symlink_sink(काष्ठा coresight_device *csdev);
व्योम eपंचांग_perf_del_symlink_sink(काष्ठा coresight_device *csdev);
अटल अंतरभूत व्योम *eपंचांग_perf_sink_config(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा eपंचांग_event_data *data = perf_get_aux(handle);

	अगर (data)
		वापस data->snk_config;
	वापस शून्य;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक eपंचांग_perf_symlink(काष्ठा coresight_device *csdev, bool link)
अणु वापस -EINVAL; पूर्ण
पूर्णांक eपंचांग_perf_add_symlink_sink(काष्ठा coresight_device *csdev)
अणु वापस -EINVAL; पूर्ण
व्योम eपंचांग_perf_del_symlink_sink(काष्ठा coresight_device *csdev) अणुपूर्ण
अटल अंतरभूत व्योम *eपंचांग_perf_sink_config(काष्ठा perf_output_handle *handle)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_CORESIGHT */

पूर्णांक __init eपंचांग_perf_init(व्योम);
व्योम __निकास eपंचांग_perf_निकास(व्योम);

#पूर्ण_अगर
