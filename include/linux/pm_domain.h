<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * pm_करोमुख्य.h - Definitions and headers related to device घातer करोमुख्यs.
 *
 * Copyright (C) 2011 Rafael J. Wysocki <rjw@sisk.pl>, Renesas Electronics Corp.
 */

#अगर_अघोषित _LINUX_PM_DOMAIN_H
#घोषणा _LINUX_PM_DOMAIN_H

#समावेश <linux/device.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/pm.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cpumask.h>

/*
 * Flags to control the behaviour of a genpd.
 *
 * These flags may be set in the काष्ठा generic_pm_करोमुख्य's flags field by a
 * genpd backend driver. The flags must be set beक्रमe it calls pm_genpd_init(),
 * which initializes a genpd.
 *
 * GENPD_FLAG_PM_CLK:		Inकाष्ठाs genpd to use the PM clk framework,
 *				जबतक घातering on/off attached devices.
 *
 * GENPD_FLAG_IRQ_SAFE:		This inक्रमms genpd that its backend callbacks,
 *				->घातer_on|off(), करोesn't sleep. Hence, these
 *				can be invoked from within atomic context, which
 *				enables genpd to घातer on/off the PM करोमुख्य,
 *				even when pm_runसमय_is_irq_safe() वापसs true,
 *				क्रम any of its attached devices. Note that, a
 *				genpd having this flag set, requires its
 *				masterकरोमुख्यs to also have it set.
 *
 * GENPD_FLAG_ALWAYS_ON:	Inकाष्ठाs genpd to always keep the PM करोमुख्य
 *				घातered on.
 *
 * GENPD_FLAG_ACTIVE_WAKEUP:	Inकाष्ठाs genpd to keep the PM करोमुख्य घातered
 *				on, in हाल any of its attached devices is used
 *				in the wakeup path to serve प्रणाली wakeups.
 *
 * GENPD_FLAG_CPU_DOMAIN:	Inकाष्ठाs genpd that it should expect to get
 *				devices attached, which may beदीर्घ to CPUs or
 *				possibly have subकरोमुख्यs with CPUs attached.
 *				This flag enables the genpd backend driver to
 *				deploy idle घातer management support क्रम CPUs
 *				and groups of CPUs. Note that, the backend
 *				driver must then comply with the so called,
 *				last-man-standing algorithm, क्रम the CPUs in the
 *				PM करोमुख्य.
 *
 * GENPD_FLAG_RPM_ALWAYS_ON:	Inकाष्ठाs genpd to always keep the PM करोमुख्य
 *				घातered on except क्रम प्रणाली suspend.
 *
 * GENPD_FLAG_MIN_RESIDENCY:	Enable the genpd governor to consider its
 *				components' next wakeup when determining the
 *				optimal idle state.
 */
#घोषणा GENPD_FLAG_PM_CLK	 (1U << 0)
#घोषणा GENPD_FLAG_IRQ_SAFE	 (1U << 1)
#घोषणा GENPD_FLAG_ALWAYS_ON	 (1U << 2)
#घोषणा GENPD_FLAG_ACTIVE_WAKEUP (1U << 3)
#घोषणा GENPD_FLAG_CPU_DOMAIN	 (1U << 4)
#घोषणा GENPD_FLAG_RPM_ALWAYS_ON (1U << 5)
#घोषणा GENPD_FLAG_MIN_RESIDENCY (1U << 6)

क्रमागत gpd_status अणु
	GENPD_STATE_ON = 0,	/* PM करोमुख्य is on */
	GENPD_STATE_OFF,	/* PM करोमुख्य is off */
पूर्ण;

क्रमागत genpd_notication अणु
	GENPD_NOTIFY_PRE_OFF = 0,
	GENPD_NOTIFY_OFF,
	GENPD_NOTIFY_PRE_ON,
	GENPD_NOTIFY_ON,
पूर्ण;

काष्ठा dev_घातer_governor अणु
	bool (*घातer_करोwn_ok)(काष्ठा dev_pm_करोमुख्य *करोमुख्य);
	bool (*suspend_ok)(काष्ठा device *dev);
पूर्ण;

काष्ठा gpd_dev_ops अणु
	पूर्णांक (*start)(काष्ठा device *dev);
	पूर्णांक (*stop)(काष्ठा device *dev);
पूर्ण;

काष्ठा genpd_घातer_state अणु
	s64 घातer_off_latency_ns;
	s64 घातer_on_latency_ns;
	s64 residency_ns;
	u64 usage;
	u64 rejected;
	काष्ठा fwnode_handle *fwnode;
	kसमय_प्रकार idle_समय;
	व्योम *data;
पूर्ण;

काष्ठा genpd_lock_ops;
काष्ठा dev_pm_opp;
काष्ठा opp_table;

काष्ठा generic_pm_करोमुख्य अणु
	काष्ठा device dev;
	काष्ठा dev_pm_करोमुख्य करोमुख्य;	/* PM करोमुख्य operations */
	काष्ठा list_head gpd_list_node;	/* Node in the global PM करोमुख्यs list */
	काष्ठा list_head parent_links;	/* Links with PM करोमुख्य as a parent */
	काष्ठा list_head child_links;	/* Links with PM करोमुख्य as a child */
	काष्ठा list_head dev_list;	/* List of devices */
	काष्ठा dev_घातer_governor *gov;
	काष्ठा work_काष्ठा घातer_off_work;
	काष्ठा fwnode_handle *provider;	/* Identity of the करोमुख्य provider */
	bool has_provider;
	स्थिर अक्षर *name;
	atomic_t sd_count;	/* Number of subकरोमुख्यs with घातer "on" */
	क्रमागत gpd_status status;	/* Current state of the करोमुख्य */
	अचिन्हित पूर्णांक device_count;	/* Number of devices */
	अचिन्हित पूर्णांक suspended_count;	/* System suspend device counter */
	अचिन्हित पूर्णांक prepared_count;	/* Suspend counter of prepared devices */
	अचिन्हित पूर्णांक perक्रमmance_state;	/* Aggregated max perक्रमmance state */
	cpumask_var_t cpus;		/* A cpumask of the attached CPUs */
	पूर्णांक (*घातer_off)(काष्ठा generic_pm_करोमुख्य *करोमुख्य);
	पूर्णांक (*घातer_on)(काष्ठा generic_pm_करोमुख्य *करोमुख्य);
	काष्ठा raw_notअगरier_head घातer_notअगरiers; /* Power on/off notअगरiers */
	काष्ठा opp_table *opp_table;	/* OPP table of the genpd */
	अचिन्हित पूर्णांक (*opp_to_perक्रमmance_state)(काष्ठा generic_pm_करोमुख्य *genpd,
						 काष्ठा dev_pm_opp *opp);
	पूर्णांक (*set_perक्रमmance_state)(काष्ठा generic_pm_करोमुख्य *genpd,
				     अचिन्हित पूर्णांक state);
	काष्ठा gpd_dev_ops dev_ops;
	s64 max_off_समय_ns;	/* Maximum allowed "suspended" समय. */
	kसमय_प्रकार next_wakeup;	/* Maपूर्णांकained by the करोमुख्य governor */
	bool max_off_समय_changed;
	bool cached_घातer_करोwn_ok;
	bool cached_घातer_करोwn_state_idx;
	पूर्णांक (*attach_dev)(काष्ठा generic_pm_करोमुख्य *करोमुख्य,
			  काष्ठा device *dev);
	व्योम (*detach_dev)(काष्ठा generic_pm_करोमुख्य *करोमुख्य,
			   काष्ठा device *dev);
	अचिन्हित पूर्णांक flags;		/* Bit field of configs क्रम genpd */
	काष्ठा genpd_घातer_state *states;
	व्योम (*मुक्त_states)(काष्ठा genpd_घातer_state *states,
			    अचिन्हित पूर्णांक state_count);
	अचिन्हित पूर्णांक state_count; /* number of states */
	अचिन्हित पूर्णांक state_idx; /* state that genpd will go to when off */
	kसमय_प्रकार on_समय;
	kसमय_प्रकार accounting_समय;
	स्थिर काष्ठा genpd_lock_ops *lock_ops;
	जोड़ अणु
		काष्ठा mutex mlock;
		काष्ठा अणु
			spinlock_t slock;
			अचिन्हित दीर्घ lock_flags;
		पूर्ण;
	पूर्ण;

पूर्ण;

अटल अंतरभूत काष्ठा generic_pm_करोमुख्य *pd_to_genpd(काष्ठा dev_pm_करोमुख्य *pd)
अणु
	वापस container_of(pd, काष्ठा generic_pm_करोमुख्य, करोमुख्य);
पूर्ण

काष्ठा gpd_link अणु
	काष्ठा generic_pm_करोमुख्य *parent;
	काष्ठा list_head parent_node;
	काष्ठा generic_pm_करोमुख्य *child;
	काष्ठा list_head child_node;

	/* Sub-करोमुख्य's per-master करोमुख्य perक्रमmance state */
	अचिन्हित पूर्णांक perक्रमmance_state;
	अचिन्हित पूर्णांक prev_perक्रमmance_state;
पूर्ण;

काष्ठा gpd_timing_data अणु
	s64 suspend_latency_ns;
	s64 resume_latency_ns;
	s64 effective_स्थिरraपूर्णांक_ns;
	bool स्थिरraपूर्णांक_changed;
	bool cached_suspend_ok;
पूर्ण;

काष्ठा pm_करोमुख्य_data अणु
	काष्ठा list_head list_node;
	काष्ठा device *dev;
पूर्ण;

काष्ठा generic_pm_करोमुख्य_data अणु
	काष्ठा pm_करोमुख्य_data base;
	काष्ठा gpd_timing_data td;
	काष्ठा notअगरier_block nb;
	काष्ठा notअगरier_block *घातer_nb;
	पूर्णांक cpu;
	अचिन्हित पूर्णांक perक्रमmance_state;
	kसमय_प्रकार	next_wakeup;
	व्योम *data;
पूर्ण;

#अगर_घोषित CONFIG_PM_GENERIC_DOMAINS
अटल अंतरभूत काष्ठा generic_pm_करोमुख्य_data *to_gpd_data(काष्ठा pm_करोमुख्य_data *pdd)
अणु
	वापस container_of(pdd, काष्ठा generic_pm_करोमुख्य_data, base);
पूर्ण

अटल अंतरभूत काष्ठा generic_pm_करोमुख्य_data *dev_gpd_data(काष्ठा device *dev)
अणु
	वापस to_gpd_data(dev->घातer.subsys_data->करोमुख्य_data);
पूर्ण

पूर्णांक pm_genpd_add_device(काष्ठा generic_pm_करोमुख्य *genpd, काष्ठा device *dev);
पूर्णांक pm_genpd_हटाओ_device(काष्ठा device *dev);
पूर्णांक pm_genpd_add_subकरोमुख्य(काष्ठा generic_pm_करोमुख्य *genpd,
			   काष्ठा generic_pm_करोमुख्य *subकरोमुख्य);
पूर्णांक pm_genpd_हटाओ_subकरोमुख्य(काष्ठा generic_pm_करोमुख्य *genpd,
			      काष्ठा generic_pm_करोमुख्य *subकरोमुख्य);
पूर्णांक pm_genpd_init(काष्ठा generic_pm_करोमुख्य *genpd,
		  काष्ठा dev_घातer_governor *gov, bool is_off);
पूर्णांक pm_genpd_हटाओ(काष्ठा generic_pm_करोमुख्य *genpd);
पूर्णांक dev_pm_genpd_set_perक्रमmance_state(काष्ठा device *dev, अचिन्हित पूर्णांक state);
पूर्णांक dev_pm_genpd_add_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb);
पूर्णांक dev_pm_genpd_हटाओ_notअगरier(काष्ठा device *dev);
व्योम dev_pm_genpd_set_next_wakeup(काष्ठा device *dev, kसमय_प्रकार next);

बाह्य काष्ठा dev_घातer_governor simple_qos_governor;
बाह्य काष्ठा dev_घातer_governor pm_करोमुख्य_always_on_gov;
#अगर_घोषित CONFIG_CPU_IDLE
बाह्य काष्ठा dev_घातer_governor pm_करोमुख्य_cpu_gov;
#पूर्ण_अगर
#अन्यथा

अटल अंतरभूत काष्ठा generic_pm_करोमुख्य_data *dev_gpd_data(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण
अटल अंतरभूत पूर्णांक pm_genpd_add_device(काष्ठा generic_pm_करोमुख्य *genpd,
				      काष्ठा device *dev)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक pm_genpd_हटाओ_device(काष्ठा device *dev)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक pm_genpd_add_subकरोमुख्य(काष्ठा generic_pm_करोमुख्य *genpd,
					 काष्ठा generic_pm_करोमुख्य *subकरोमुख्य)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक pm_genpd_हटाओ_subकरोमुख्य(काष्ठा generic_pm_करोमुख्य *genpd,
					    काष्ठा generic_pm_करोमुख्य *subकरोमुख्य)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक pm_genpd_init(काष्ठा generic_pm_करोमुख्य *genpd,
				काष्ठा dev_घातer_governor *gov, bool is_off)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक pm_genpd_हटाओ(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_genpd_set_perक्रमmance_state(काष्ठा device *dev,
						     अचिन्हित पूर्णांक state)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_genpd_add_notअगरier(काष्ठा device *dev,
					    काष्ठा notअगरier_block *nb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_genpd_हटाओ_notअगरier(काष्ठा device *dev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम dev_pm_genpd_set_next_wakeup(काष्ठा device *dev, kसमय_प्रकार next)
अणु पूर्ण

#घोषणा simple_qos_governor		(*(काष्ठा dev_घातer_governor *)(शून्य))
#घोषणा pm_करोमुख्य_always_on_gov		(*(काष्ठा dev_घातer_governor *)(शून्य))
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_GENERIC_DOMAINS_SLEEP
व्योम dev_pm_genpd_suspend(काष्ठा device *dev);
व्योम dev_pm_genpd_resume(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत व्योम dev_pm_genpd_suspend(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम dev_pm_genpd_resume(काष्ठा device *dev) अणुपूर्ण
#पूर्ण_अगर

/* OF PM करोमुख्य providers */
काष्ठा of_device_id;

प्रकार काष्ठा generic_pm_करोमुख्य *(*genpd_xlate_t)(काष्ठा of_phandle_args *args,
						   व्योम *data);

काष्ठा genpd_onecell_data अणु
	काष्ठा generic_pm_करोमुख्य **करोमुख्यs;
	अचिन्हित पूर्णांक num_करोमुख्यs;
	genpd_xlate_t xlate;
पूर्ण;

#अगर_घोषित CONFIG_PM_GENERIC_DOMAINS_OF
पूर्णांक of_genpd_add_provider_simple(काष्ठा device_node *np,
				 काष्ठा generic_pm_करोमुख्य *genpd);
पूर्णांक of_genpd_add_provider_onecell(काष्ठा device_node *np,
				  काष्ठा genpd_onecell_data *data);
व्योम of_genpd_del_provider(काष्ठा device_node *np);
पूर्णांक of_genpd_add_device(काष्ठा of_phandle_args *args, काष्ठा device *dev);
पूर्णांक of_genpd_add_subकरोमुख्य(काष्ठा of_phandle_args *parent_spec,
			   काष्ठा of_phandle_args *subकरोमुख्य_spec);
पूर्णांक of_genpd_हटाओ_subकरोमुख्य(काष्ठा of_phandle_args *parent_spec,
			      काष्ठा of_phandle_args *subकरोमुख्य_spec);
काष्ठा generic_pm_करोमुख्य *of_genpd_हटाओ_last(काष्ठा device_node *np);
पूर्णांक of_genpd_parse_idle_states(काष्ठा device_node *dn,
			       काष्ठा genpd_घातer_state **states, पूर्णांक *n);
अचिन्हित पूर्णांक pm_genpd_opp_to_perक्रमmance_state(काष्ठा device *genpd_dev,
					       काष्ठा dev_pm_opp *opp);

पूर्णांक genpd_dev_pm_attach(काष्ठा device *dev);
काष्ठा device *genpd_dev_pm_attach_by_id(काष्ठा device *dev,
					 अचिन्हित पूर्णांक index);
काष्ठा device *genpd_dev_pm_attach_by_name(काष्ठा device *dev,
					   स्थिर अक्षर *name);
#अन्यथा /* !CONFIG_PM_GENERIC_DOMAINS_OF */
अटल अंतरभूत पूर्णांक of_genpd_add_provider_simple(काष्ठा device_node *np,
					काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक of_genpd_add_provider_onecell(काष्ठा device_node *np,
					काष्ठा genpd_onecell_data *data)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम of_genpd_del_provider(काष्ठा device_node *np) अणुपूर्ण

अटल अंतरभूत पूर्णांक of_genpd_add_device(काष्ठा of_phandle_args *args,
				      काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक of_genpd_add_subकरोमुख्य(काष्ठा of_phandle_args *parent_spec,
					 काष्ठा of_phandle_args *subकरोमुख्य_spec)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक of_genpd_हटाओ_subकरोमुख्य(काष्ठा of_phandle_args *parent_spec,
					काष्ठा of_phandle_args *subकरोमुख्य_spec)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक of_genpd_parse_idle_states(काष्ठा device_node *dn,
			काष्ठा genpd_घातer_state **states, पूर्णांक *n)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
pm_genpd_opp_to_perक्रमmance_state(काष्ठा device *genpd_dev,
				  काष्ठा dev_pm_opp *opp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक genpd_dev_pm_attach(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा device *genpd_dev_pm_attach_by_id(काष्ठा device *dev,
						       अचिन्हित पूर्णांक index)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device *genpd_dev_pm_attach_by_name(काष्ठा device *dev,
							 स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
काष्ठा generic_pm_करोमुख्य *of_genpd_हटाओ_last(काष्ठा device_node *np)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_GENERIC_DOMAINS_OF */

#अगर_घोषित CONFIG_PM
पूर्णांक dev_pm_करोमुख्य_attach(काष्ठा device *dev, bool घातer_on);
काष्ठा device *dev_pm_करोमुख्य_attach_by_id(काष्ठा device *dev,
					  अचिन्हित पूर्णांक index);
काष्ठा device *dev_pm_करोमुख्य_attach_by_name(काष्ठा device *dev,
					    स्थिर अक्षर *name);
व्योम dev_pm_करोमुख्य_detach(काष्ठा device *dev, bool घातer_off);
पूर्णांक dev_pm_करोमुख्य_start(काष्ठा device *dev);
व्योम dev_pm_करोमुख्य_set(काष्ठा device *dev, काष्ठा dev_pm_करोमुख्य *pd);
#अन्यथा
अटल अंतरभूत पूर्णांक dev_pm_करोमुख्य_attach(काष्ठा device *dev, bool घातer_on)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत काष्ठा device *dev_pm_करोमुख्य_attach_by_id(काष्ठा device *dev,
							अचिन्हित पूर्णांक index)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा device *dev_pm_करोमुख्य_attach_by_name(काष्ठा device *dev,
							  स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम dev_pm_करोमुख्य_detach(काष्ठा device *dev, bool घातer_off) अणुपूर्ण
अटल अंतरभूत पूर्णांक dev_pm_करोमुख्य_start(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम dev_pm_करोमुख्य_set(काष्ठा device *dev,
				     काष्ठा dev_pm_करोमुख्य *pd) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_PM_DOMAIN_H */
