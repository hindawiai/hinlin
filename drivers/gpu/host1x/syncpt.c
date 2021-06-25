<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra host1x Syncpoपूर्णांकs
 *
 * Copyright (c) 2010-2015, NVIDIA Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश <trace/events/host1x.h>

#समावेश "syncpt.h"
#समावेश "dev.h"
#समावेश "intr.h"
#समावेश "debug.h"

#घोषणा SYNCPT_CHECK_PERIOD (2 * HZ)
#घोषणा MAX_STUCK_CHECK_COUNT 15

अटल काष्ठा host1x_syncpt_base *
host1x_syncpt_base_request(काष्ठा host1x *host)
अणु
	काष्ठा host1x_syncpt_base *bases = host->bases;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < host->info->nb_bases; i++)
		अगर (!bases[i].requested)
			अवरोध;

	अगर (i >= host->info->nb_bases)
		वापस शून्य;

	bases[i].requested = true;
	वापस &bases[i];
पूर्ण

अटल व्योम host1x_syncpt_base_मुक्त(काष्ठा host1x_syncpt_base *base)
अणु
	अगर (base)
		base->requested = false;
पूर्ण

/**
 * host1x_syncpt_alloc() - allocate a syncpoपूर्णांक
 * @host: host1x device data
 * @flags: bitfield of HOST1X_SYNCPT_* flags
 * @name: name क्रम the syncpoपूर्णांक क्रम use in debug prपूर्णांकs
 *
 * Allocates a hardware syncpoपूर्णांक क्रम the caller's use. The caller then has
 * the sole authority to mutate the syncpoपूर्णांक's value until it is मुक्तd again.
 *
 * If no मुक्त syncpoपूर्णांकs are available, or a शून्य name was specअगरied, वापसs
 * शून्य.
 */
काष्ठा host1x_syncpt *host1x_syncpt_alloc(काष्ठा host1x *host,
					  अचिन्हित दीर्घ flags,
					  स्थिर अक्षर *name)
अणु
	काष्ठा host1x_syncpt *sp = host->syncpt;
	अक्षर *full_name;
	अचिन्हित पूर्णांक i;

	अगर (!name)
		वापस शून्य;

	mutex_lock(&host->syncpt_mutex);

	क्रम (i = 0; i < host->info->nb_pts && kref_पढ़ो(&sp->ref); i++, sp++)
		;

	अगर (i >= host->info->nb_pts)
		जाओ unlock;

	अगर (flags & HOST1X_SYNCPT_HAS_BASE) अणु
		sp->base = host1x_syncpt_base_request(host);
		अगर (!sp->base)
			जाओ unlock;
	पूर्ण

	full_name = kaप्र_लिखो(GFP_KERNEL, "%u-%s", sp->id, name);
	अगर (!full_name)
		जाओ मुक्त_base;

	sp->name = full_name;

	अगर (flags & HOST1X_SYNCPT_CLIENT_MANAGED)
		sp->client_managed = true;
	अन्यथा
		sp->client_managed = false;

	kref_init(&sp->ref);

	mutex_unlock(&host->syncpt_mutex);
	वापस sp;

मुक्त_base:
	host1x_syncpt_base_मुक्त(sp->base);
	sp->base = शून्य;
unlock:
	mutex_unlock(&host->syncpt_mutex);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_alloc);

/**
 * host1x_syncpt_id() - retrieve syncpoपूर्णांक ID
 * @sp: host1x syncpoपूर्णांक
 *
 * Given a poपूर्णांकer to a काष्ठा host1x_syncpt, retrieves its ID. This ID is
 * often used as a value to program पूर्णांकo रेजिस्टरs that control how hardware
 * blocks पूर्णांकeract with syncpoपूर्णांकs.
 */
u32 host1x_syncpt_id(काष्ठा host1x_syncpt *sp)
अणु
	वापस sp->id;
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_id);

/**
 * host1x_syncpt_incr_max() - update the value sent to hardware
 * @sp: host1x syncpoपूर्णांक
 * @incrs: number of increments
 */
u32 host1x_syncpt_incr_max(काष्ठा host1x_syncpt *sp, u32 incrs)
अणु
	वापस (u32)atomic_add_वापस(incrs, &sp->max_val);
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_incr_max);

 /*
 * Write cached syncpoपूर्णांक and रुकोbase values to hardware.
 */
व्योम host1x_syncpt_restore(काष्ठा host1x *host)
अणु
	काष्ठा host1x_syncpt *sp_base = host->syncpt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < host1x_syncpt_nb_pts(host); i++)
		host1x_hw_syncpt_restore(host, sp_base + i);

	क्रम (i = 0; i < host1x_syncpt_nb_bases(host); i++)
		host1x_hw_syncpt_restore_रुको_base(host, sp_base + i);

	wmb();
पूर्ण

/*
 * Update the cached syncpoपूर्णांक and रुकोbase values by पढ़ोing them
 * from the रेजिस्टरs.
  */
व्योम host1x_syncpt_save(काष्ठा host1x *host)
अणु
	काष्ठा host1x_syncpt *sp_base = host->syncpt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < host1x_syncpt_nb_pts(host); i++) अणु
		अगर (host1x_syncpt_client_managed(sp_base + i))
			host1x_hw_syncpt_load(host, sp_base + i);
		अन्यथा
			WARN_ON(!host1x_syncpt_idle(sp_base + i));
	पूर्ण

	क्रम (i = 0; i < host1x_syncpt_nb_bases(host); i++)
		host1x_hw_syncpt_load_रुको_base(host, sp_base + i);
पूर्ण

/*
 * Updates the cached syncpoपूर्णांक value by पढ़ोing a new value from the hardware
 * रेजिस्टर
 */
u32 host1x_syncpt_load(काष्ठा host1x_syncpt *sp)
अणु
	u32 val;

	val = host1x_hw_syncpt_load(sp->host, sp);
	trace_host1x_syncpt_load_min(sp->id, val);

	वापस val;
पूर्ण

/*
 * Get the current syncpoपूर्णांक base
 */
u32 host1x_syncpt_load_रुको_base(काष्ठा host1x_syncpt *sp)
अणु
	host1x_hw_syncpt_load_रुको_base(sp->host, sp);

	वापस sp->base_val;
पूर्ण

/**
 * host1x_syncpt_incr() - increment syncpoपूर्णांक value from CPU, updating cache
 * @sp: host1x syncpoपूर्णांक
 */
पूर्णांक host1x_syncpt_incr(काष्ठा host1x_syncpt *sp)
अणु
	वापस host1x_hw_syncpt_cpu_incr(sp->host, sp);
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_incr);

/*
 * Updated sync poपूर्णांक क्रमm hardware, and वापसs true अगर syncpoपूर्णांक is expired,
 * false अगर we may need to रुको
 */
अटल bool syncpt_load_min_is_expired(काष्ठा host1x_syncpt *sp, u32 thresh)
अणु
	host1x_hw_syncpt_load(sp->host, sp);

	वापस host1x_syncpt_is_expired(sp, thresh);
पूर्ण

/**
 * host1x_syncpt_रुको() - रुको क्रम a syncpoपूर्णांक to reach a given value
 * @sp: host1x syncpoपूर्णांक
 * @thresh: threshold
 * @समयout: maximum समय to रुको क्रम the syncpoपूर्णांक to reach the given value
 * @value: वापस location क्रम the syncpoपूर्णांक value
 */
पूर्णांक host1x_syncpt_रुको(काष्ठा host1x_syncpt *sp, u32 thresh, दीर्घ समयout,
		       u32 *value)
अणु
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	व्योम *ref;
	काष्ठा host1x_रुकोlist *रुकोer;
	पूर्णांक err = 0, check_count = 0;
	u32 val;

	अगर (value)
		*value = 0;

	/* first check cache */
	अगर (host1x_syncpt_is_expired(sp, thresh)) अणु
		अगर (value)
			*value = host1x_syncpt_load(sp);

		वापस 0;
	पूर्ण

	/* try to पढ़ो from रेजिस्टर */
	val = host1x_hw_syncpt_load(sp->host, sp);
	अगर (host1x_syncpt_is_expired(sp, thresh)) अणु
		अगर (value)
			*value = val;

		जाओ करोne;
	पूर्ण

	अगर (!समयout) अणु
		err = -EAGAIN;
		जाओ करोne;
	पूर्ण

	/* allocate a रुकोer */
	रुकोer = kzalloc(माप(*रुकोer), GFP_KERNEL);
	अगर (!रुकोer) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* schedule a wakeup when the syncpoपूर्णांक value is reached */
	err = host1x_पूर्णांकr_add_action(sp->host, sp, thresh,
				     HOST1X_INTR_ACTION_WAKEUP_INTERRUPTIBLE,
				     &wq, रुकोer, &ref);
	अगर (err)
		जाओ करोne;

	err = -EAGAIN;
	/* Caller-specअगरied समयout may be impractically low */
	अगर (समयout < 0)
		समयout = दीर्घ_उच्च;

	/* रुको क्रम the syncpoपूर्णांक, or समयout, or संकेत */
	जबतक (समयout) अणु
		दीर्घ check = min_t(दीर्घ, SYNCPT_CHECK_PERIOD, समयout);
		पूर्णांक reमुख्य;

		reमुख्य = रुको_event_पूर्णांकerruptible_समयout(wq,
				syncpt_load_min_is_expired(sp, thresh),
				check);
		अगर (reमुख्य > 0 || host1x_syncpt_is_expired(sp, thresh)) अणु
			अगर (value)
				*value = host1x_syncpt_load(sp);

			err = 0;

			अवरोध;
		पूर्ण

		अगर (reमुख्य < 0) अणु
			err = reमुख्य;
			अवरोध;
		पूर्ण

		समयout -= check;

		अगर (समयout && check_count <= MAX_STUCK_CHECK_COUNT) अणु
			dev_warn(sp->host->dev,
				"%s: syncpoint id %u (%s) stuck waiting %d, timeout=%ld\n",
				 current->comm, sp->id, sp->name,
				 thresh, समयout);

			host1x_debug_dump_syncpts(sp->host);

			अगर (check_count == MAX_STUCK_CHECK_COUNT)
				host1x_debug_dump(sp->host);

			check_count++;
		पूर्ण
	पूर्ण

	host1x_पूर्णांकr_put_ref(sp->host, sp->id, ref, true);

करोne:
	वापस err;
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_रुको);

/*
 * Returns true अगर syncpoपूर्णांक is expired, false अगर we may need to रुको
 */
bool host1x_syncpt_is_expired(काष्ठा host1x_syncpt *sp, u32 thresh)
अणु
	u32 current_val;

	smp_rmb();

	current_val = (u32)atomic_पढ़ो(&sp->min_val);

	वापस ((current_val - thresh) & 0x80000000U) == 0U;
पूर्ण

पूर्णांक host1x_syncpt_init(काष्ठा host1x *host)
अणु
	काष्ठा host1x_syncpt_base *bases;
	काष्ठा host1x_syncpt *syncpt;
	अचिन्हित पूर्णांक i;

	syncpt = devm_kसुस्मृति(host->dev, host->info->nb_pts, माप(*syncpt),
			      GFP_KERNEL);
	अगर (!syncpt)
		वापस -ENOMEM;

	bases = devm_kसुस्मृति(host->dev, host->info->nb_bases, माप(*bases),
			     GFP_KERNEL);
	अगर (!bases)
		वापस -ENOMEM;

	क्रम (i = 0; i < host->info->nb_pts; i++) अणु
		syncpt[i].id = i;
		syncpt[i].host = host;

		/*
		 * Unassign syncpt from channels क्रम purposes of Tegra186
		 * syncpoपूर्णांक protection. This prevents any channel from
		 * accessing it until it is reasचिन्हित.
		 */
		host1x_hw_syncpt_assign_to_channel(host, &syncpt[i], शून्य);
	पूर्ण

	क्रम (i = 0; i < host->info->nb_bases; i++)
		bases[i].id = i;

	mutex_init(&host->syncpt_mutex);
	host->syncpt = syncpt;
	host->bases = bases;

	host1x_syncpt_restore(host);
	host1x_hw_syncpt_enable_protection(host);

	/* Allocate sync poपूर्णांक to use क्रम clearing रुकोs क्रम expired fences */
	host->nop_sp = host1x_syncpt_alloc(host, 0, "reserved-nop");
	अगर (!host->nop_sp)
		वापस -ENOMEM;

	अगर (host->info->reserve_vblank_syncpts) अणु
		kref_init(&host->syncpt[26].ref);
		kref_init(&host->syncpt[27].ref);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * host1x_syncpt_request() - request a syncpoपूर्णांक
 * @client: client requesting the syncpoपूर्णांक
 * @flags: flags
 *
 * host1x client drivers can use this function to allocate a syncpoपूर्णांक क्रम
 * subsequent use. A syncpoपूर्णांक वापसed by this function will be reserved क्रम
 * use by the client exclusively. When no दीर्घer using a syncpoपूर्णांक, a host1x
 * client driver needs to release it using host1x_syncpt_put().
 */
काष्ठा host1x_syncpt *host1x_syncpt_request(काष्ठा host1x_client *client,
					    अचिन्हित दीर्घ flags)
अणु
	काष्ठा host1x *host = dev_get_drvdata(client->host->parent);

	वापस host1x_syncpt_alloc(host, flags, dev_name(client->dev));
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_request);

अटल व्योम syncpt_release(काष्ठा kref *ref)
अणु
	काष्ठा host1x_syncpt *sp = container_of(ref, काष्ठा host1x_syncpt, ref);

	atomic_set(&sp->max_val, host1x_syncpt_पढ़ो(sp));

	mutex_lock(&sp->host->syncpt_mutex);

	host1x_syncpt_base_मुक्त(sp->base);
	kमुक्त(sp->name);
	sp->base = शून्य;
	sp->name = शून्य;
	sp->client_managed = false;

	mutex_unlock(&sp->host->syncpt_mutex);
पूर्ण

/**
 * host1x_syncpt_put() - मुक्त a requested syncpoपूर्णांक
 * @sp: host1x syncpoपूर्णांक
 *
 * Release a syncpoपूर्णांक previously allocated using host1x_syncpt_request(). A
 * host1x client driver should call this when the syncpoपूर्णांक is no दीर्घer in
 * use.
 */
व्योम host1x_syncpt_put(काष्ठा host1x_syncpt *sp)
अणु
	अगर (!sp)
		वापस;

	kref_put(&sp->ref, syncpt_release);
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_put);

व्योम host1x_syncpt_deinit(काष्ठा host1x *host)
अणु
	काष्ठा host1x_syncpt *sp = host->syncpt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < host->info->nb_pts; i++, sp++)
		kमुक्त(sp->name);
पूर्ण

/**
 * host1x_syncpt_पढ़ो_max() - पढ़ो maximum syncpoपूर्णांक value
 * @sp: host1x syncpoपूर्णांक
 *
 * The maximum syncpoपूर्णांक value indicates how many operations there are in
 * queue, either in channel or in a software thपढ़ो.
 */
u32 host1x_syncpt_पढ़ो_max(काष्ठा host1x_syncpt *sp)
अणु
	smp_rmb();

	वापस (u32)atomic_पढ़ो(&sp->max_val);
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_पढ़ो_max);

/**
 * host1x_syncpt_पढ़ो_min() - पढ़ो minimum syncpoपूर्णांक value
 * @sp: host1x syncpoपूर्णांक
 *
 * The minimum syncpoपूर्णांक value is a shaकरोw of the current sync poपूर्णांक value in
 * hardware.
 */
u32 host1x_syncpt_पढ़ो_min(काष्ठा host1x_syncpt *sp)
अणु
	smp_rmb();

	वापस (u32)atomic_पढ़ो(&sp->min_val);
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_पढ़ो_min);

/**
 * host1x_syncpt_पढ़ो() - पढ़ो the current syncpoपूर्णांक value
 * @sp: host1x syncpoपूर्णांक
 */
u32 host1x_syncpt_पढ़ो(काष्ठा host1x_syncpt *sp)
अणु
	वापस host1x_syncpt_load(sp);
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_पढ़ो);

अचिन्हित पूर्णांक host1x_syncpt_nb_pts(काष्ठा host1x *host)
अणु
	वापस host->info->nb_pts;
पूर्ण

अचिन्हित पूर्णांक host1x_syncpt_nb_bases(काष्ठा host1x *host)
अणु
	वापस host->info->nb_bases;
पूर्ण

अचिन्हित पूर्णांक host1x_syncpt_nb_mlocks(काष्ठा host1x *host)
अणु
	वापस host->info->nb_mlocks;
पूर्ण

/**
 * host1x_syncpt_get_by_id() - obtain a syncpoपूर्णांक by ID
 * @host: host1x controller
 * @id: syncpoपूर्णांक ID
 */
काष्ठा host1x_syncpt *host1x_syncpt_get_by_id(काष्ठा host1x *host,
					      अचिन्हित पूर्णांक id)
अणु
	अगर (id >= host->info->nb_pts)
		वापस शून्य;

	अगर (kref_get_unless_zero(&host->syncpt[id].ref))
		वापस &host->syncpt[id];
	अन्यथा
		वापस शून्य;
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_get_by_id);

/**
 * host1x_syncpt_get_by_id_noref() - obtain a syncpoपूर्णांक by ID but करोn't
 * 	increase the refcount.
 * @host: host1x controller
 * @id: syncpoपूर्णांक ID
 */
काष्ठा host1x_syncpt *host1x_syncpt_get_by_id_noref(काष्ठा host1x *host,
						    अचिन्हित पूर्णांक id)
अणु
	अगर (id >= host->info->nb_pts)
		वापस शून्य;

	वापस &host->syncpt[id];
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_get_by_id_noref);

/**
 * host1x_syncpt_get() - increment syncpoपूर्णांक refcount
 * @sp: syncpoपूर्णांक
 */
काष्ठा host1x_syncpt *host1x_syncpt_get(काष्ठा host1x_syncpt *sp)
अणु
	kref_get(&sp->ref);

	वापस sp;
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_get);

/**
 * host1x_syncpt_get_base() - obtain the रुको base associated with a syncpoपूर्णांक
 * @sp: host1x syncpoपूर्णांक
 */
काष्ठा host1x_syncpt_base *host1x_syncpt_get_base(काष्ठा host1x_syncpt *sp)
अणु
	वापस sp ? sp->base : शून्य;
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_get_base);

/**
 * host1x_syncpt_base_id() - retrieve the ID of a syncpoपूर्णांक रुको base
 * @base: host1x syncpoपूर्णांक रुको base
 */
u32 host1x_syncpt_base_id(काष्ठा host1x_syncpt_base *base)
अणु
	वापस base->id;
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_base_id);

अटल व्योम करो_nothing(काष्ठा kref *ref)
अणु
पूर्ण

/**
 * host1x_syncpt_release_vblank_reservation() - Make VBLANK syncpoपूर्णांक
 *   available क्रम allocation
 *
 * @client: host1x bus client
 * @syncpt_id: syncpoपूर्णांक ID to make available
 *
 * Makes VBLANK<i> syncpoपूर्णांक available क्रम allocatation अगर it was
 * reserved at initialization समय. This should be called by the display
 * driver after it has ensured that any VBLANK increment programming configured
 * by the boot chain has been disabled.
 */
व्योम host1x_syncpt_release_vblank_reservation(काष्ठा host1x_client *client,
					      u32 syncpt_id)
अणु
	काष्ठा host1x *host = dev_get_drvdata(client->host->parent);

	अगर (!host->info->reserve_vblank_syncpts)
		वापस;

	kref_put(&host->syncpt[syncpt_id].ref, करो_nothing);
पूर्ण
EXPORT_SYMBOL(host1x_syncpt_release_vblank_reservation);
