<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Miscellaneous cgroup controller.
 *
 * Copyright 2020 Google LLC
 * Author: Vipin Sharma <vipinsh@google.com>
 */
#अगर_अघोषित _MISC_CGROUP_H_
#घोषणा _MISC_CGROUP_H_

/**
 * Types of misc cgroup entries supported by the host.
 */
क्रमागत misc_res_type अणु
#अगर_घोषित CONFIG_KVM_AMD_SEV
	/* AMD SEV ASIDs resource */
	MISC_CG_RES_SEV,
	/* AMD SEV-ES ASIDs resource */
	MISC_CG_RES_SEV_ES,
#पूर्ण_अगर
	MISC_CG_RES_TYPES
पूर्ण;

काष्ठा misc_cg;

#अगर_घोषित CONFIG_CGROUP_MISC

#समावेश <linux/cgroup.h>

/**
 * काष्ठा misc_res: Per cgroup per misc type resource
 * @max: Maximum limit on the resource.
 * @usage: Current usage of the resource.
 * @failed: True अगर अक्षरged failed क्रम the resource in a cgroup.
 */
काष्ठा misc_res अणु
	अचिन्हित दीर्घ max;
	atomic_दीर्घ_t usage;
	bool failed;
पूर्ण;

/**
 * काष्ठा misc_cg - Miscellaneous controller's cgroup काष्ठाure.
 * @css: cgroup subsys state object.
 * @res: Array of misc resources usage in the cgroup.
 */
काष्ठा misc_cg अणु
	काष्ठा cgroup_subsys_state css;
	काष्ठा misc_res res[MISC_CG_RES_TYPES];
पूर्ण;

अचिन्हित दीर्घ misc_cg_res_total_usage(क्रमागत misc_res_type type);
पूर्णांक misc_cg_set_capacity(क्रमागत misc_res_type type, अचिन्हित दीर्घ capacity);
पूर्णांक misc_cg_try_अक्षरge(क्रमागत misc_res_type type, काष्ठा misc_cg *cg,
		       अचिन्हित दीर्घ amount);
व्योम misc_cg_unअक्षरge(क्रमागत misc_res_type type, काष्ठा misc_cg *cg,
		      अचिन्हित दीर्घ amount);

/**
 * css_misc() - Get misc cgroup from the css.
 * @css: cgroup subsys state object.
 *
 * Context: Any context.
 * Return:
 * * %शून्य - If @css is null.
 * * काष्ठा misc_cg* - misc cgroup poपूर्णांकer of the passed css.
 */
अटल अंतरभूत काष्ठा misc_cg *css_misc(काष्ठा cgroup_subsys_state *css)
अणु
	वापस css ? container_of(css, काष्ठा misc_cg, css) : शून्य;
पूर्ण

/*
 * get_current_misc_cg() - Find and get the misc cgroup of the current task.
 *
 * Returned cgroup has its ref count increased by 1. Caller must call
 * put_misc_cg() to वापस the reference.
 *
 * Return: Misc cgroup to which the current task beदीर्घs to.
 */
अटल अंतरभूत काष्ठा misc_cg *get_current_misc_cg(व्योम)
अणु
	वापस css_misc(task_get_css(current, misc_cgrp_id));
पूर्ण

/*
 * put_misc_cg() - Put the misc cgroup and reduce its ref count.
 * @cg - cgroup to put.
 */
अटल अंतरभूत व्योम put_misc_cg(काष्ठा misc_cg *cg)
अणु
	अगर (cg)
		css_put(&cg->css);
पूर्ण

#अन्यथा /* !CONFIG_CGROUP_MISC */

अटल अंतरभूत अचिन्हित दीर्घ misc_cg_res_total_usage(क्रमागत misc_res_type type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक misc_cg_set_capacity(क्रमागत misc_res_type type,
				       अचिन्हित दीर्घ capacity)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक misc_cg_try_अक्षरge(क्रमागत misc_res_type type,
				     काष्ठा misc_cg *cg,
				     अचिन्हित दीर्घ amount)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम misc_cg_unअक्षरge(क्रमागत misc_res_type type,
				    काष्ठा misc_cg *cg,
				    अचिन्हित दीर्घ amount)
अणु
पूर्ण

अटल अंतरभूत काष्ठा misc_cg *get_current_misc_cg(व्योम)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम put_misc_cg(काष्ठा misc_cg *cg)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_CGROUP_MISC */
#पूर्ण_अगर /* _MISC_CGROUP_H_ */
