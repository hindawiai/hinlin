<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Miscellaneous cgroup controller
 *
 * Copyright 2020 Google LLC
 * Author: Vipin Sharma <vipinsh@google.com>
 */

#समावेश <linux/सीमा.स>
#समावेश <linux/cgroup.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/atomic.h>
#समावेश <linux/slab.h>
#समावेश <linux/misc_cgroup.h>

#घोषणा MAX_STR "max"
#घोषणा MAX_NUM अच_दीर्घ_उच्च

/* Miscellaneous res name, keep it in sync with क्रमागत misc_res_type */
अटल स्थिर अक्षर *स्थिर misc_res_name[] = अणु
#अगर_घोषित CONFIG_KVM_AMD_SEV
	/* AMD SEV ASIDs resource */
	"sev",
	/* AMD SEV-ES ASIDs resource */
	"sev_es",
#पूर्ण_अगर
पूर्ण;

/* Root misc cgroup */
अटल काष्ठा misc_cg root_cg;

/*
 * Miscellaneous resources capacity क्रम the entire machine. 0 capacity means
 * resource is not initialized or not present in the host.
 *
 * root_cg.max and capacity are independent of each other. root_cg.max can be
 * more than the actual capacity. We are using Limits resource distribution
 * model of cgroup क्रम miscellaneous controller.
 */
अटल अचिन्हित दीर्घ misc_res_capacity[MISC_CG_RES_TYPES];

/**
 * parent_misc() - Get the parent of the passed misc cgroup.
 * @cgroup: cgroup whose parent needs to be fetched.
 *
 * Context: Any context.
 * Return:
 * * काष्ठा misc_cg* - Parent of the @cgroup.
 * * %शून्य - If @cgroup is null or the passed cgroup करोes not have a parent.
 */
अटल काष्ठा misc_cg *parent_misc(काष्ठा misc_cg *cgroup)
अणु
	वापस cgroup ? css_misc(cgroup->css.parent) : शून्य;
पूर्ण

/**
 * valid_type() - Check अगर @type is valid or not.
 * @type: misc res type.
 *
 * Context: Any context.
 * Return:
 * * true - If valid type.
 * * false - If not valid type.
 */
अटल अंतरभूत bool valid_type(क्रमागत misc_res_type type)
अणु
	वापस type >= 0 && type < MISC_CG_RES_TYPES;
पूर्ण

/**
 * misc_cg_res_total_usage() - Get the current total usage of the resource.
 * @type: misc res type.
 *
 * Context: Any context.
 * Return: Current total usage of the resource.
 */
अचिन्हित दीर्घ misc_cg_res_total_usage(क्रमागत misc_res_type type)
अणु
	अगर (valid_type(type))
		वापस atomic_दीर्घ_पढ़ो(&root_cg.res[type].usage);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(misc_cg_res_total_usage);

/**
 * misc_cg_set_capacity() - Set the capacity of the misc cgroup res.
 * @type: Type of the misc res.
 * @capacity: Supported capacity of the misc res on the host.
 *
 * If capacity is 0 then the अक्षरging a misc cgroup fails क्रम that type.
 *
 * Context: Any context.
 * Return:
 * * %0 - Successfully रेजिस्टरed the capacity.
 * * %-EINVAL - If @type is invalid.
 */
पूर्णांक misc_cg_set_capacity(क्रमागत misc_res_type type, अचिन्हित दीर्घ capacity)
अणु
	अगर (!valid_type(type))
		वापस -EINVAL;

	WRITE_ONCE(misc_res_capacity[type], capacity);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(misc_cg_set_capacity);

/**
 * misc_cg_cancel_अक्षरge() - Cancel the अक्षरge from the misc cgroup.
 * @type: Misc res type in misc cg to cancel the अक्षरge from.
 * @cg: Misc cgroup to cancel अक्षरge from.
 * @amount: Amount to cancel.
 *
 * Context: Any context.
 */
अटल व्योम misc_cg_cancel_अक्षरge(क्रमागत misc_res_type type, काष्ठा misc_cg *cg,
				  अचिन्हित दीर्घ amount)
अणु
	WARN_ONCE(atomic_दीर्घ_add_negative(-amount, &cg->res[type].usage),
		  "misc cgroup resource %s became less than 0",
		  misc_res_name[type]);
पूर्ण

/**
 * misc_cg_try_अक्षरge() - Try अक्षरging the misc cgroup.
 * @type: Misc res type to अक्षरge.
 * @cg: Misc cgroup which will be अक्षरged.
 * @amount: Amount to अक्षरge.
 *
 * Charge @amount to the misc cgroup. Caller must use the same cgroup during
 * the unअक्षरge call.
 *
 * Context: Any context.
 * Return:
 * * %0 - If successfully अक्षरged.
 * * -EINVAL - If @type is invalid or misc res has 0 capacity.
 * * -EBUSY - If max limit will be crossed or total usage will be more than the
 *	      capacity.
 */
पूर्णांक misc_cg_try_अक्षरge(क्रमागत misc_res_type type, काष्ठा misc_cg *cg,
		       अचिन्हित दीर्घ amount)
अणु
	काष्ठा misc_cg *i, *j;
	पूर्णांक ret;
	काष्ठा misc_res *res;
	पूर्णांक new_usage;

	अगर (!(valid_type(type) && cg && READ_ONCE(misc_res_capacity[type])))
		वापस -EINVAL;

	अगर (!amount)
		वापस 0;

	क्रम (i = cg; i; i = parent_misc(i)) अणु
		res = &i->res[type];

		new_usage = atomic_दीर्घ_add_वापस(amount, &res->usage);
		अगर (new_usage > READ_ONCE(res->max) ||
		    new_usage > READ_ONCE(misc_res_capacity[type])) अणु
			अगर (!res->failed) अणु
				pr_info("cgroup: charge rejected by the misc controller for %s resource in ",
					misc_res_name[type]);
				pr_cont_cgroup_path(i->css.cgroup);
				pr_cont("\n");
				res->failed = true;
			पूर्ण
			ret = -EBUSY;
			जाओ err_अक्षरge;
		पूर्ण
	पूर्ण
	वापस 0;

err_अक्षरge:
	क्रम (j = cg; j != i; j = parent_misc(j))
		misc_cg_cancel_अक्षरge(type, j, amount);
	misc_cg_cancel_अक्षरge(type, i, amount);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(misc_cg_try_अक्षरge);

/**
 * misc_cg_unअक्षरge() - Unअक्षरge the misc cgroup.
 * @type: Misc res type which was अक्षरged.
 * @cg: Misc cgroup which will be unअक्षरged.
 * @amount: Charged amount.
 *
 * Context: Any context.
 */
व्योम misc_cg_unअक्षरge(क्रमागत misc_res_type type, काष्ठा misc_cg *cg,
		      अचिन्हित दीर्घ amount)
अणु
	काष्ठा misc_cg *i;

	अगर (!(amount && valid_type(type) && cg))
		वापस;

	क्रम (i = cg; i; i = parent_misc(i))
		misc_cg_cancel_अक्षरge(type, i, amount);
पूर्ण
EXPORT_SYMBOL_GPL(misc_cg_unअक्षरge);

/**
 * misc_cg_max_show() - Show the misc cgroup max limit.
 * @sf: Interface file
 * @v: Arguments passed
 *
 * Context: Any context.
 * Return: 0 to denote successful prपूर्णांक.
 */
अटल पूर्णांक misc_cg_max_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	पूर्णांक i;
	काष्ठा misc_cg *cg = css_misc(seq_css(sf));
	अचिन्हित दीर्घ max;

	क्रम (i = 0; i < MISC_CG_RES_TYPES; i++) अणु
		अगर (READ_ONCE(misc_res_capacity[i])) अणु
			max = READ_ONCE(cg->res[i].max);
			अगर (max == MAX_NUM)
				seq_म_लिखो(sf, "%s max\n", misc_res_name[i]);
			अन्यथा
				seq_म_लिखो(sf, "%s %lu\n", misc_res_name[i],
					   max);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * misc_cg_max_ग_लिखो() - Update the maximum limit of the cgroup.
 * @of: Handler क्रम the file.
 * @buf: Data from the user. It should be either "max", 0, or a positive
 *	 पूर्णांकeger.
 * @nbytes: Number of bytes of the data.
 * @off: Offset in the file.
 *
 * User can pass data like:
 * echo sev 23 > misc.max, OR
 * echo sev max > misc.max
 *
 * Context: Any context.
 * Return:
 * * >= 0 - Number of bytes processed in the input.
 * * -EINVAL - If buf is not valid.
 * * -दुस्फल - If number is bigger than the अचिन्हित दीर्घ capacity.
 */
अटल sमाप_प्रकार misc_cg_max_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
				 माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा misc_cg *cg;
	अचिन्हित दीर्घ max;
	पूर्णांक ret = 0, i;
	क्रमागत misc_res_type type = MISC_CG_RES_TYPES;
	अक्षर *token;

	buf = म_मालाip(buf);
	token = strsep(&buf, " ");

	अगर (!token || !buf)
		वापस -EINVAL;

	क्रम (i = 0; i < MISC_CG_RES_TYPES; i++) अणु
		अगर (!म_भेद(misc_res_name[i], token)) अणु
			type = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (type == MISC_CG_RES_TYPES)
		वापस -EINVAL;

	अगर (!म_भेद(MAX_STR, buf)) अणु
		max = MAX_NUM;
	पूर्ण अन्यथा अणु
		ret = kम_से_अदीर्घ(buf, 0, &max);
		अगर (ret)
			वापस ret;
	पूर्ण

	cg = css_misc(of_css(of));

	अगर (READ_ONCE(misc_res_capacity[type]))
		WRITE_ONCE(cg->res[type].max, max);
	अन्यथा
		ret = -EINVAL;

	वापस ret ? ret : nbytes;
पूर्ण

/**
 * misc_cg_current_show() - Show the current usage of the misc cgroup.
 * @sf: Interface file
 * @v: Arguments passed
 *
 * Context: Any context.
 * Return: 0 to denote successful prपूर्णांक.
 */
अटल पूर्णांक misc_cg_current_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ usage;
	काष्ठा misc_cg *cg = css_misc(seq_css(sf));

	क्रम (i = 0; i < MISC_CG_RES_TYPES; i++) अणु
		usage = atomic_दीर्घ_पढ़ो(&cg->res[i].usage);
		अगर (READ_ONCE(misc_res_capacity[i]) || usage)
			seq_म_लिखो(sf, "%s %lu\n", misc_res_name[i], usage);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * misc_cg_capacity_show() - Show the total capacity of misc res on the host.
 * @sf: Interface file
 * @v: Arguments passed
 *
 * Only present in the root cgroup directory.
 *
 * Context: Any context.
 * Return: 0 to denote successful prपूर्णांक.
 */
अटल पूर्णांक misc_cg_capacity_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ cap;

	क्रम (i = 0; i < MISC_CG_RES_TYPES; i++) अणु
		cap = READ_ONCE(misc_res_capacity[i]);
		अगर (cap)
			seq_म_लिखो(sf, "%s %lu\n", misc_res_name[i], cap);
	पूर्ण

	वापस 0;
पूर्ण

/* Misc cgroup पूर्णांकerface files */
अटल काष्ठा cftype misc_cg_files[] = अणु
	अणु
		.name = "max",
		.ग_लिखो = misc_cg_max_ग_लिखो,
		.seq_show = misc_cg_max_show,
		.flags = CFTYPE_NOT_ON_ROOT,
	पूर्ण,
	अणु
		.name = "current",
		.seq_show = misc_cg_current_show,
		.flags = CFTYPE_NOT_ON_ROOT,
	पूर्ण,
	अणु
		.name = "capacity",
		.seq_show = misc_cg_capacity_show,
		.flags = CFTYPE_ONLY_ON_ROOT,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/**
 * misc_cg_alloc() - Allocate misc cgroup.
 * @parent_css: Parent cgroup.
 *
 * Context: Process context.
 * Return:
 * * काष्ठा cgroup_subsys_state* - css of the allocated cgroup.
 * * ERR_PTR(-ENOMEM) - No memory available to allocate.
 */
अटल काष्ठा cgroup_subsys_state *
misc_cg_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	क्रमागत misc_res_type i;
	काष्ठा misc_cg *cg;

	अगर (!parent_css) अणु
		cg = &root_cg;
	पूर्ण अन्यथा अणु
		cg = kzalloc(माप(*cg), GFP_KERNEL);
		अगर (!cg)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (i = 0; i < MISC_CG_RES_TYPES; i++) अणु
		WRITE_ONCE(cg->res[i].max, MAX_NUM);
		atomic_दीर्घ_set(&cg->res[i].usage, 0);
	पूर्ण

	वापस &cg->css;
पूर्ण

/**
 * misc_cg_मुक्त() - Free the misc cgroup.
 * @css: cgroup subsys object.
 *
 * Context: Any context.
 */
अटल व्योम misc_cg_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	kमुक्त(css_misc(css));
पूर्ण

/* Cgroup controller callbacks */
काष्ठा cgroup_subsys misc_cgrp_subsys = अणु
	.css_alloc = misc_cg_alloc,
	.css_मुक्त = misc_cg_मुक्त,
	.legacy_cftypes = misc_cg_files,
	.dfl_cftypes = misc_cg_files,
पूर्ण;
