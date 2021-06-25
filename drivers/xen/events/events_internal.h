<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Xen Event Channels (पूर्णांकernal header)
 *
 * Copyright (C) 2013 Citrix Systems R&D Ltd.
 */
#अगर_अघोषित __EVENTS_INTERNAL_H__
#घोषणा __EVENTS_INTERNAL_H__

काष्ठा evtchn_loop_ctrl;

काष्ठा evtchn_ops अणु
	अचिन्हित (*max_channels)(व्योम);
	अचिन्हित (*nr_channels)(व्योम);

	पूर्णांक (*setup)(evtchn_port_t port);
	व्योम (*हटाओ)(evtchn_port_t port, अचिन्हित पूर्णांक cpu);
	व्योम (*bind_to_cpu)(evtchn_port_t evtchn, अचिन्हित पूर्णांक cpu,
			    अचिन्हित पूर्णांक old_cpu);

	व्योम (*clear_pending)(evtchn_port_t port);
	व्योम (*set_pending)(evtchn_port_t port);
	bool (*is_pending)(evtchn_port_t port);
	व्योम (*mask)(evtchn_port_t port);
	व्योम (*unmask)(evtchn_port_t port);

	व्योम (*handle_events)(अचिन्हित cpu, काष्ठा evtchn_loop_ctrl *ctrl);
	व्योम (*resume)(व्योम);

	पूर्णांक (*percpu_init)(अचिन्हित पूर्णांक cpu);
	पूर्णांक (*percpu_deinit)(अचिन्हित पूर्णांक cpu);
पूर्ण;

बाह्य स्थिर काष्ठा evtchn_ops *evtchn_ops;

पूर्णांक get_evtchn_to_irq(evtchn_port_t evtchn);
व्योम handle_irq_क्रम_port(evtchn_port_t port, काष्ठा evtchn_loop_ctrl *ctrl);

अचिन्हित पूर्णांक cpu_from_evtchn(evtchn_port_t evtchn);

अटल अंतरभूत अचिन्हित xen_evtchn_max_channels(व्योम)
अणु
	वापस evtchn_ops->max_channels();
पूर्ण

/*
 * Do any ABI specअगरic setup क्रम a bound event channel beक्रमe it can
 * be unmasked and used.
 */
अटल अंतरभूत पूर्णांक xen_evtchn_port_setup(evtchn_port_t evtchn)
अणु
	अगर (evtchn_ops->setup)
		वापस evtchn_ops->setup(evtchn);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xen_evtchn_port_हटाओ(evtchn_port_t evtchn,
					  अचिन्हित पूर्णांक cpu)
अणु
	अगर (evtchn_ops->हटाओ)
		evtchn_ops->हटाओ(evtchn, cpu);
पूर्ण

अटल अंतरभूत व्योम xen_evtchn_port_bind_to_cpu(evtchn_port_t evtchn,
					       अचिन्हित पूर्णांक cpu,
					       अचिन्हित पूर्णांक old_cpu)
अणु
	evtchn_ops->bind_to_cpu(evtchn, cpu, old_cpu);
पूर्ण

अटल अंतरभूत व्योम clear_evtchn(evtchn_port_t port)
अणु
	evtchn_ops->clear_pending(port);
पूर्ण

अटल अंतरभूत व्योम set_evtchn(evtchn_port_t port)
अणु
	evtchn_ops->set_pending(port);
पूर्ण

अटल अंतरभूत bool test_evtchn(evtchn_port_t port)
अणु
	वापस evtchn_ops->is_pending(port);
पूर्ण

अटल अंतरभूत व्योम mask_evtchn(evtchn_port_t port)
अणु
	वापस evtchn_ops->mask(port);
पूर्ण

अटल अंतरभूत व्योम unmask_evtchn(evtchn_port_t port)
अणु
	वापस evtchn_ops->unmask(port);
पूर्ण

अटल अंतरभूत व्योम xen_evtchn_handle_events(अचिन्हित cpu,
					    काष्ठा evtchn_loop_ctrl *ctrl)
अणु
	वापस evtchn_ops->handle_events(cpu, ctrl);
पूर्ण

अटल अंतरभूत व्योम xen_evtchn_resume(व्योम)
अणु
	अगर (evtchn_ops->resume)
		evtchn_ops->resume();
पूर्ण

व्योम xen_evtchn_2l_init(व्योम);
पूर्णांक xen_evtchn_fअगरo_init(व्योम);

#पूर्ण_अगर /* #अगर_अघोषित __EVENTS_INTERNAL_H__ */
