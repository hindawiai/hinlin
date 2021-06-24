<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/mcpm.h
 *
 * Created by:  Nicolas Pitre, April 2012
 * Copyright:   (C) 2012-2013  Linaro Limited
 */

#अगर_अघोषित MCPM_H
#घोषणा MCPM_H

/*
 * Maximum number of possible clusters / CPUs per cluster.
 *
 * This should be sufficient क्रम quite a जबतक, जबतक keeping the
 * (assembly) code simpler.  When this starts to grow then we'll have
 * to consider dynamic allocation.
 */
#घोषणा MAX_CPUS_PER_CLUSTER	4

#अगर_घोषित CONFIG_MCPM_QUAD_CLUSTER
#घोषणा MAX_NR_CLUSTERS		4
#अन्यथा
#घोषणा MAX_NR_CLUSTERS		2
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <यंत्र/cacheflush.h>

/*
 * Platक्रमm specअगरic code should use this symbol to set up secondary
 * entry location क्रम processors to use when released from reset.
 */
बाह्य व्योम mcpm_entry_poपूर्णांक(व्योम);

/*
 * This is used to indicate where the given CPU from given cluster should
 * branch once it is पढ़ोy to re-enter the kernel using ptr, or शून्य अगर it
 * should be gated.  A gated CPU is held in a WFE loop until its vector
 * becomes non शून्य.
 */
व्योम mcpm_set_entry_vector(अचिन्हित cpu, अचिन्हित cluster, व्योम *ptr);

/*
 * This sets an early poke i.e a value to be poked पूर्णांकo some address
 * from very early assembly code beक्रमe the CPU is ungated.  The
 * address must be physical, and अगर 0 then nothing will happen.
 */
व्योम mcpm_set_early_poke(अचिन्हित cpu, अचिन्हित cluster,
			 अचिन्हित दीर्घ poke_phys_addr, अचिन्हित दीर्घ poke_val);

/*
 * CPU/cluster घातer operations API क्रम higher subप्रणालीs to use.
 */

/**
 * mcpm_is_available - वापसs whether MCPM is initialized and available
 *
 * This वापसs true or false accordingly.
 */
bool mcpm_is_available(व्योम);

/**
 * mcpm_cpu_घातer_up - make given CPU in given cluster runable
 *
 * @cpu: CPU number within given cluster
 * @cluster: cluster number क्रम the CPU
 *
 * The identअगरied CPU is brought out of reset.  If the cluster was घातered
 * करोwn then it is brought up as well, taking care not to let the other CPUs
 * in the cluster run, and ensuring appropriate cluster setup.
 *
 * Caller must ensure the appropriate entry vector is initialized with
 * mcpm_set_entry_vector() prior to calling this.
 *
 * This must be called in a sleepable context.  However, the implementation
 * is strongly encouraged to वापस early and let the operation happen
 * asynchronously, especially when signअगरicant delays are expected.
 *
 * If the operation cannot be perक्रमmed then an error code is वापसed.
 */
पूर्णांक mcpm_cpu_घातer_up(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster);

/**
 * mcpm_cpu_घातer_करोwn - घातer the calling CPU करोwn
 *
 * The calling CPU is घातered करोwn.
 *
 * If this CPU is found to be the "last man standing" in the cluster
 * then the cluster is prepared क्रम घातer-करोwn too.
 *
 * This must be called with पूर्णांकerrupts disabled.
 *
 * On success this करोes not वापस.  Re-entry in the kernel is expected
 * via mcpm_entry_poपूर्णांक.
 *
 * This will वापस अगर mcpm_platक्रमm_रेजिस्टर() has not been called
 * previously in which हाल the caller should take appropriate action.
 *
 * On success, the CPU is not guaranteed to be truly halted until
 * mcpm_रुको_क्रम_cpu_घातerकरोwn() subsequently वापसs non-zero क्रम the
 * specअगरied cpu.  Until then, other CPUs should make sure they करो not
 * trash memory the target CPU might be executing/accessing.
 */
व्योम mcpm_cpu_घातer_करोwn(व्योम);

/**
 * mcpm_रुको_क्रम_cpu_घातerकरोwn - रुको क्रम a specअगरied CPU to halt, and
 *	make sure it is घातered off
 *
 * @cpu: CPU number within given cluster
 * @cluster: cluster number क्रम the CPU
 *
 * Call this function to ensure that a pending घातerकरोwn has taken
 * effect and the CPU is safely parked beक्रमe perक्रमming non-mcpm
 * operations that may affect the CPU (such as kexec trashing the
 * kernel text).
 *
 * It is *not* necessary to call this function अगर you only need to
 * serialise a pending घातerकरोwn with mcpm_cpu_घातer_up() or a wakeup
 * event.
 *
 * Do not call this function unless the specअगरied CPU has alपढ़ोy
 * called mcpm_cpu_घातer_करोwn() or has committed to करोing so.
 *
 * @वापस:
 *	- zero अगर the CPU is in a safely parked state
 *	- nonzero otherwise (e.g., समयout)
 */
पूर्णांक mcpm_रुको_क्रम_cpu_घातerकरोwn(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster);

/**
 * mcpm_cpu_suspend - bring the calling CPU in a suspended state
 *
 * The calling CPU is suspended.  This is similar to mcpm_cpu_घातer_करोwn()
 * except क्रम possible extra platक्रमm specअगरic configuration steps to allow
 * an asynchronous wake-up e.g. with a pending पूर्णांकerrupt.
 *
 * If this CPU is found to be the "last man standing" in the cluster
 * then the cluster may be prepared क्रम घातer-करोwn too.
 *
 * This must be called with पूर्णांकerrupts disabled.
 *
 * On success this करोes not वापस.  Re-entry in the kernel is expected
 * via mcpm_entry_poपूर्णांक.
 *
 * This will वापस अगर mcpm_platक्रमm_रेजिस्टर() has not been called
 * previously in which हाल the caller should take appropriate action.
 */
व्योम mcpm_cpu_suspend(व्योम);

/**
 * mcpm_cpu_घातered_up - housekeeping workafter a CPU has been घातered up
 *
 * This lets the platक्रमm specअगरic backend code perक्रमm needed housekeeping
 * work.  This must be called by the newly activated CPU as soon as it is
 * fully operational in kernel space, beक्रमe it enables पूर्णांकerrupts.
 *
 * If the operation cannot be perक्रमmed then an error code is वापसed.
 */
पूर्णांक mcpm_cpu_घातered_up(व्योम);

/*
 * Platक्रमm specअगरic callbacks used in the implementation of the above API.
 *
 * cpu_घातerup:
 * Make given CPU runable. Called with MCPM lock held and IRQs disabled.
 * The given cluster is assumed to be set up (cluster_घातerup would have
 * been called beक्रमehand). Must वापस 0 क्रम success or negative error code.
 *
 * cluster_घातerup:
 * Set up घातer क्रम given cluster. Called with MCPM lock held and IRQs
 * disabled. Called beक्रमe first cpu_घातerup when cluster is करोwn. Must
 * वापस 0 क्रम success or negative error code.
 *
 * cpu_suspend_prepare:
 * Special suspend configuration. Called on target CPU with MCPM lock held
 * and IRQs disabled. This callback is optional. If provided, it is called
 * beक्रमe cpu_घातerकरोwn_prepare.
 *
 * cpu_घातerकरोwn_prepare:
 * Configure given CPU क्रम घातer करोwn. Called on target CPU with MCPM lock
 * held and IRQs disabled. Power करोwn must be effective only at the next WFI inकाष्ठाion.
 *
 * cluster_घातerकरोwn_prepare:
 * Configure given cluster क्रम घातer करोwn. Called on one CPU from target
 * cluster with MCPM lock held and IRQs disabled. A cpu_घातerकरोwn_prepare
 * क्रम each CPU in the cluster has happened when this occurs.
 *
 * cpu_cache_disable:
 * Clean and disable CPU level cache क्रम the calling CPU. Called on with IRQs
 * disabled only. The CPU is no दीर्घer cache coherent with the rest of the
 * प्रणाली when this वापसs.
 *
 * cluster_cache_disable:
 * Clean and disable the cluster wide cache as well as the CPU level cache
 * क्रम the calling CPU. No call to cpu_cache_disable will happen क्रम this
 * CPU. Called with IRQs disabled and only when all the other CPUs are करोne
 * with their own cpu_cache_disable. The cluster is no दीर्घer cache coherent
 * with the rest of the प्रणाली when this वापसs.
 *
 * cpu_is_up:
 * Called on given CPU after it has been घातered up or resumed. The MCPM lock
 * is held and IRQs disabled. This callback is optional.
 *
 * cluster_is_up:
 * Called by the first CPU to be घातered up or resumed in given cluster.
 * The MCPM lock is held and IRQs disabled. This callback is optional. If
 * provided, it is called beक्रमe cpu_is_up क्रम that CPU.
 *
 * रुको_क्रम_घातerकरोwn:
 * Wait until given CPU is घातered करोwn. This is called in sleeping context.
 * Some reasonable समयout must be considered. Must वापस 0 क्रम success or
 * negative error code.
 */
काष्ठा mcpm_platक्रमm_ops अणु
	पूर्णांक (*cpu_घातerup)(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster);
	पूर्णांक (*cluster_घातerup)(अचिन्हित पूर्णांक cluster);
	व्योम (*cpu_suspend_prepare)(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster);
	व्योम (*cpu_घातerकरोwn_prepare)(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster);
	व्योम (*cluster_घातerकरोwn_prepare)(अचिन्हित पूर्णांक cluster);
	व्योम (*cpu_cache_disable)(व्योम);
	व्योम (*cluster_cache_disable)(व्योम);
	व्योम (*cpu_is_up)(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster);
	व्योम (*cluster_is_up)(अचिन्हित पूर्णांक cluster);
	पूर्णांक (*रुको_क्रम_घातerकरोwn)(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster);
पूर्ण;

/**
 * mcpm_platक्रमm_रेजिस्टर - रेजिस्टर platक्रमm specअगरic घातer methods
 *
 * @ops: mcpm_platक्रमm_ops काष्ठाure to रेजिस्टर
 *
 * An error is वापसed अगर the registration has been करोne previously.
 */
पूर्णांक __init mcpm_platक्रमm_रेजिस्टर(स्थिर काष्ठा mcpm_platक्रमm_ops *ops);

/**
 * mcpm_sync_init - Initialize the cluster synchronization support
 *
 * @घातer_up_setup: platक्रमm specअगरic function invoked during very
 * 		    early CPU/cluster bringup stage.
 *
 * This prepares memory used by vlocks and the MCPM state machine used
 * across CPUs that may have their caches active or inactive. Must be
 * called only after a successful call to mcpm_platक्रमm_रेजिस्टर().
 *
 * The घातer_up_setup argument is a poपूर्णांकer to assembly code called when
 * the MMU and caches are still disabled during boot  and no stack space is
 * available. The affinity level passed to that code corresponds to the
 * resource that needs to be initialized (e.g. 1 क्रम cluster level, 0 क्रम
 * CPU level).  Proper exclusion mechanisms are alपढ़ोy activated at that
 * poपूर्णांक.
 */
पूर्णांक __init mcpm_sync_init(
	व्योम (*घातer_up_setup)(अचिन्हित पूर्णांक affinity_level));

/**
 * mcpm_loopback - make a run through the MCPM low-level code
 *
 * @cache_disable: poपूर्णांकer to function perक्रमming cache disabling
 *
 * This exercises the MCPM machinery by soft resetting the CPU and branching
 * to the MCPM low-level entry code beक्रमe वापसing to the caller.
 * The @cache_disable function must करो the necessary cache disabling to
 * let the regular kernel init code turn it back on as अगर the CPU was
 * hotplugged in. The MCPM state machine is set as अगर the cluster was
 * initialized meaning the घातer_up_setup callback passed to mcpm_sync_init()
 * will be invoked क्रम all affinity levels. This may be useful to initialize
 * some resources such as enabling the CCI that requires the cache to be off, or simply क्रम testing purposes.
 */
पूर्णांक __init mcpm_loopback(व्योम (*cache_disable)(व्योम));

व्योम __init mcpm_smp_set_ops(व्योम);

/*
 * Synchronisation काष्ठाures क्रम coordinating safe cluster setup/tearकरोwn.
 * This is निजी to the MCPM core code and shared between C and assembly.
 * When modअगरying this काष्ठाure, make sure you update the MCPM_SYNC_ defines
 * to match.
 */
काष्ठा mcpm_sync_काष्ठा अणु
	/* inभागidual CPU states */
	काष्ठा अणु
		s8 cpu __aligned(__CACHE_WRITEBACK_GRANULE);
	पूर्ण cpus[MAX_CPUS_PER_CLUSTER];

	/* cluster state */
	s8 cluster __aligned(__CACHE_WRITEBACK_GRANULE);

	/* inbound-side state */
	s8 inbound __aligned(__CACHE_WRITEBACK_GRANULE);
पूर्ण;

काष्ठा sync_काष्ठा अणु
	काष्ठा mcpm_sync_काष्ठा clusters[MAX_NR_CLUSTERS];
पूर्ण;

#अन्यथा

/* 
 * यंत्र-offsets.h causes trouble when included in .c files, and cacheflush.h
 * cannot be included in यंत्र files.  Let's work around the conflict like this.
 */
#समावेश <यंत्र/यंत्र-offsets.h>
#घोषणा __CACHE_WRITEBACK_GRANULE CACHE_WRITEBACK_GRANULE

#पूर्ण_अगर /* ! __ASSEMBLY__ */

/* Definitions क्रम mcpm_sync_काष्ठा */
#घोषणा CPU_DOWN		0x11
#घोषणा CPU_COMING_UP		0x12
#घोषणा CPU_UP			0x13
#घोषणा CPU_GOING_DOWN		0x14

#घोषणा CLUSTER_DOWN		0x21
#घोषणा CLUSTER_UP		0x22
#घोषणा CLUSTER_GOING_DOWN	0x23

#घोषणा INBOUND_NOT_COMING_UP	0x31
#घोषणा INBOUND_COMING_UP	0x32

/*
 * Offsets क्रम the mcpm_sync_काष्ठा members, क्रम use in यंत्र.
 * We करोn't want to make them global to the kernel via यंत्र-offsets.c.
 */
#घोषणा MCPM_SYNC_CLUSTER_CPUS	0
#घोषणा MCPM_SYNC_CPU_SIZE	__CACHE_WRITEBACK_GRANULE
#घोषणा MCPM_SYNC_CLUSTER_CLUSTER \
	(MCPM_SYNC_CLUSTER_CPUS + MCPM_SYNC_CPU_SIZE * MAX_CPUS_PER_CLUSTER)
#घोषणा MCPM_SYNC_CLUSTER_INBOUND \
	(MCPM_SYNC_CLUSTER_CLUSTER + __CACHE_WRITEBACK_GRANULE)
#घोषणा MCPM_SYNC_CLUSTER_SIZE \
	(MCPM_SYNC_CLUSTER_INBOUND + __CACHE_WRITEBACK_GRANULE)

#पूर्ण_अगर
