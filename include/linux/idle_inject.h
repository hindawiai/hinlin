<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Linaro Ltd
 *
 * Author: Daniel Lezcano <daniel.lezcano@linaro.org>
 *
 */
#अगर_अघोषित __IDLE_INJECT_H__
#घोषणा __IDLE_INJECT_H__

/* निजी idle injection device काष्ठाure */
काष्ठा idle_inject_device;

काष्ठा idle_inject_device *idle_inject_रेजिस्टर(काष्ठा cpumask *cpumask);

व्योम idle_inject_unरेजिस्टर(काष्ठा idle_inject_device *ii_dev);

पूर्णांक idle_inject_start(काष्ठा idle_inject_device *ii_dev);

व्योम idle_inject_stop(काष्ठा idle_inject_device *ii_dev);

व्योम idle_inject_set_duration(काष्ठा idle_inject_device *ii_dev,
				 अचिन्हित पूर्णांक run_duration_us,
				 अचिन्हित पूर्णांक idle_duration_us);

व्योम idle_inject_get_duration(काष्ठा idle_inject_device *ii_dev,
				 अचिन्हित पूर्णांक *run_duration_us,
				 अचिन्हित पूर्णांक *idle_duration_us);

व्योम idle_inject_set_latency(काष्ठा idle_inject_device *ii_dev,
			     अचिन्हित पूर्णांक latency_us);

#पूर्ण_अगर /* __IDLE_INJECT_H__ */
