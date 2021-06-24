<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* hvapi.c: Hypervisor API management.
 *
 * Copyright (C) 2007 David S. Miller <davem@davemloft.net>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/oplib.h>

/* If the hypervisor indicates that the API setting
 * calls are unsupported, by वापसing HV_EBADTRAP or
 * HV_ENOTSUPPORTED, we assume that API groups with the
 * PRE_API flag set are major 1 minor 0.
 */
काष्ठा api_info अणु
	अचिन्हित दीर्घ group;
	अचिन्हित दीर्घ major;
	अचिन्हित दीर्घ minor;
	अचिन्हित पूर्णांक refcnt;
	अचिन्हित पूर्णांक flags;
#घोषणा FLAG_PRE_API		0x00000001
पूर्ण;

अटल काष्ठा api_info api_table[] = अणु
	अणु .group = HV_GRP_SUN4V,	.flags = FLAG_PRE_API	पूर्ण,
	अणु .group = HV_GRP_CORE,		.flags = FLAG_PRE_API	पूर्ण,
	अणु .group = HV_GRP_INTR,					पूर्ण,
	अणु .group = HV_GRP_SOFT_STATE,				पूर्ण,
	अणु .group = HV_GRP_TM,					पूर्ण,
	अणु .group = HV_GRP_PCI,		.flags = FLAG_PRE_API	पूर्ण,
	अणु .group = HV_GRP_LDOM,					पूर्ण,
	अणु .group = HV_GRP_SVC_CHAN,	.flags = FLAG_PRE_API	पूर्ण,
	अणु .group = HV_GRP_NCS,		.flags = FLAG_PRE_API	पूर्ण,
	अणु .group = HV_GRP_RNG,					पूर्ण,
	अणु .group = HV_GRP_PBOOT,				पूर्ण,
	अणु .group = HV_GRP_TPM,					पूर्ण,
	अणु .group = HV_GRP_SDIO,					पूर्ण,
	अणु .group = HV_GRP_SDIO_ERR,				पूर्ण,
	अणु .group = HV_GRP_REBOOT_DATA,				पूर्ण,
	अणु .group = HV_GRP_ATU,		.flags = FLAG_PRE_API	पूर्ण,
	अणु .group = HV_GRP_DAX,					पूर्ण,
	अणु .group = HV_GRP_NIAG_PERF,	.flags = FLAG_PRE_API	पूर्ण,
	अणु .group = HV_GRP_FIRE_PERF,				पूर्ण,
	अणु .group = HV_GRP_N2_CPU,				पूर्ण,
	अणु .group = HV_GRP_NIU,					पूर्ण,
	अणु .group = HV_GRP_VF_CPU,				पूर्ण,
	अणु .group = HV_GRP_KT_CPU,				पूर्ण,
	अणु .group = HV_GRP_VT_CPU,				पूर्ण,
	अणु .group = HV_GRP_T5_CPU,				पूर्ण,
	अणु .group = HV_GRP_DIAG,		.flags = FLAG_PRE_API	पूर्ण,
	अणु .group = HV_GRP_M7_PERF,				पूर्ण,
पूर्ण;

अटल DEFINE_SPINLOCK(hvapi_lock);

अटल काष्ठा api_info *__get_info(अचिन्हित दीर्घ group)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(api_table); i++) अणु
		अगर (api_table[i].group == group)
			वापस &api_table[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम __get_ref(काष्ठा api_info *p)
अणु
	p->refcnt++;
पूर्ण

अटल व्योम __put_ref(काष्ठा api_info *p)
अणु
	अगर (--p->refcnt == 0) अणु
		अचिन्हित दीर्घ ignore;

		sun4v_set_version(p->group, 0, 0, &ignore);
		p->major = p->minor = 0;
	पूर्ण
पूर्ण

/* Register a hypervisor API specअगरication.  It indicates the
 * API group and desired major+minor.
 *
 * If an existing API registration exists '0' (success) will
 * be वापसed अगर it is compatible with the one being रेजिस्टरed.
 * Otherwise a negative error code will be वापसed.
 *
 * Otherwise an attempt will be made to negotiate the requested
 * API group/major/minor with the hypervisor, and errors वापसed
 * अगर that करोes not succeed.
 */
पूर्णांक sun4v_hvapi_रेजिस्टर(अचिन्हित दीर्घ group, अचिन्हित दीर्घ major,
			 अचिन्हित दीर्घ *minor)
अणु
	काष्ठा api_info *p;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&hvapi_lock, flags);
	p = __get_info(group);
	ret = -EINVAL;
	अगर (p) अणु
		अगर (p->refcnt) अणु
			ret = -EINVAL;
			अगर (p->major == major) अणु
				*minor = p->minor;
				ret = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ actual_minor;
			अचिन्हित दीर्घ hv_ret;

			hv_ret = sun4v_set_version(group, major, *minor,
						   &actual_minor);
			ret = -EINVAL;
			अगर (hv_ret == HV_EOK) अणु
				*minor = actual_minor;
				p->major = major;
				p->minor = actual_minor;
				ret = 0;
			पूर्ण अन्यथा अगर (hv_ret == HV_EBADTRAP ||
				   hv_ret == HV_ENOTSUPPORTED) अणु
				अगर (p->flags & FLAG_PRE_API) अणु
					अगर (major == 1) अणु
						p->major = 1;
						p->minor = 0;
						*minor = 0;
						ret = 0;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (ret == 0)
			__get_ref(p);
	पूर्ण
	spin_unlock_irqrestore(&hvapi_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sun4v_hvapi_रेजिस्टर);

व्योम sun4v_hvapi_unरेजिस्टर(अचिन्हित दीर्घ group)
अणु
	काष्ठा api_info *p;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hvapi_lock, flags);
	p = __get_info(group);
	अगर (p)
		__put_ref(p);
	spin_unlock_irqrestore(&hvapi_lock, flags);
पूर्ण
EXPORT_SYMBOL(sun4v_hvapi_unरेजिस्टर);

पूर्णांक sun4v_hvapi_get(अचिन्हित दीर्घ group,
		    अचिन्हित दीर्घ *major,
		    अचिन्हित दीर्घ *minor)
अणु
	काष्ठा api_info *p;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&hvapi_lock, flags);
	ret = -EINVAL;
	p = __get_info(group);
	अगर (p && p->refcnt) अणु
		*major = p->major;
		*minor = p->minor;
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&hvapi_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sun4v_hvapi_get);

व्योम __init sun4v_hvapi_init(व्योम)
अणु
	अचिन्हित दीर्घ group, major, minor;

	group = HV_GRP_SUN4V;
	major = 1;
	minor = 0;
	अगर (sun4v_hvapi_रेजिस्टर(group, major, &minor))
		जाओ bad;

	group = HV_GRP_CORE;
	major = 1;
	minor = 6;
	अगर (sun4v_hvapi_रेजिस्टर(group, major, &minor))
		जाओ bad;

	वापस;

bad:
	prom_म_लिखो("HVAPI: Cannot register API group "
		    "%lx with major(%lu) minor(%lu)\n",
		    group, major, minor);
	prom_halt();
पूर्ण
