<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/svc.c
 *
 * High-level RPC service routines
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 *
 * Multiple thपढ़ोs pools and NUMAisation
 * Copyright (c) 2006 Silicon Graphics, Inc.
 * by Greg Banks <gnb@melbourne.sgi.com>
 */

#समावेश <linux/linkage.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/net.h>
#समावेश <linux/in.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>

#समावेश <linux/sunrpc/types.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/bc_xprt.h>

#समावेश <trace/events/sunrpc.h>

#घोषणा RPCDBG_FACILITY	RPCDBG_SVCDSP

अटल व्योम svc_unरेजिस्टर(स्थिर काष्ठा svc_serv *serv, काष्ठा net *net);

#घोषणा svc_serv_is_pooled(serv)    ((serv)->sv_ops->svo_function)

#घोषणा SVC_POOL_DEFAULT	SVC_POOL_GLOBAL

/*
 * Structure क्रम mapping cpus to pools and vice versa.
 * Setup once during sunrpc initialisation.
 */
काष्ठा svc_pool_map svc_pool_map = अणु
	.mode = SVC_POOL_DEFAULT
पूर्ण;
EXPORT_SYMBOL_GPL(svc_pool_map);

अटल DEFINE_MUTEX(svc_pool_map_mutex);/* protects svc_pool_map.count only */

अटल पूर्णांक
param_set_pool_mode(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक *ip = (पूर्णांक *)kp->arg;
	काष्ठा svc_pool_map *m = &svc_pool_map;
	पूर्णांक err;

	mutex_lock(&svc_pool_map_mutex);

	err = -EBUSY;
	अगर (m->count)
		जाओ out;

	err = 0;
	अगर (!म_भेदन(val, "auto", 4))
		*ip = SVC_POOL_AUTO;
	अन्यथा अगर (!म_भेदन(val, "global", 6))
		*ip = SVC_POOL_GLOBAL;
	अन्यथा अगर (!म_भेदन(val, "percpu", 6))
		*ip = SVC_POOL_PERCPU;
	अन्यथा अगर (!म_भेदन(val, "pernode", 7))
		*ip = SVC_POOL_PERNODE;
	अन्यथा
		err = -EINVAL;

out:
	mutex_unlock(&svc_pool_map_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक
param_get_pool_mode(अक्षर *buf, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक *ip = (पूर्णांक *)kp->arg;

	चयन (*ip)
	अणु
	हाल SVC_POOL_AUTO:
		वापस strlcpy(buf, "auto\n", 20);
	हाल SVC_POOL_GLOBAL:
		वापस strlcpy(buf, "global\n", 20);
	हाल SVC_POOL_PERCPU:
		वापस strlcpy(buf, "percpu\n", 20);
	हाल SVC_POOL_PERNODE:
		वापस strlcpy(buf, "pernode\n", 20);
	शेष:
		वापस प्र_लिखो(buf, "%d\n", *ip);
	पूर्ण
पूर्ण

module_param_call(pool_mode, param_set_pool_mode, param_get_pool_mode,
		 &svc_pool_map.mode, 0644);

/*
 * Detect best pool mapping mode heuristically,
 * according to the machine's topology.
 */
अटल पूर्णांक
svc_pool_map_choose_mode(व्योम)
अणु
	अचिन्हित पूर्णांक node;

	अगर (nr_online_nodes > 1) अणु
		/*
		 * Actually have multiple NUMA nodes,
		 * so split pools on NUMA node boundaries
		 */
		वापस SVC_POOL_PERNODE;
	पूर्ण

	node = first_online_node;
	अगर (nr_cpus_node(node) > 2) अणु
		/*
		 * Non-trivial SMP, or CONFIG_NUMA on
		 * non-NUMA hardware, e.g. with a generic
		 * x86_64 kernel on Xeons.  In this हाल we
		 * want to भागide the pools on cpu boundaries.
		 */
		वापस SVC_POOL_PERCPU;
	पूर्ण

	/* शेष: one global pool */
	वापस SVC_POOL_GLOBAL;
पूर्ण

/*
 * Allocate the to_pool[] and pool_to[] arrays.
 * Returns 0 on success or an त्रुटि_सं.
 */
अटल पूर्णांक
svc_pool_map_alloc_arrays(काष्ठा svc_pool_map *m, अचिन्हित पूर्णांक maxpools)
अणु
	m->to_pool = kसुस्मृति(maxpools, माप(अचिन्हित पूर्णांक), GFP_KERNEL);
	अगर (!m->to_pool)
		जाओ fail;
	m->pool_to = kसुस्मृति(maxpools, माप(अचिन्हित पूर्णांक), GFP_KERNEL);
	अगर (!m->pool_to)
		जाओ fail_मुक्त;

	वापस 0;

fail_मुक्त:
	kमुक्त(m->to_pool);
	m->to_pool = शून्य;
fail:
	वापस -ENOMEM;
पूर्ण

/*
 * Initialise the pool map क्रम SVC_POOL_PERCPU mode.
 * Returns number of pools or <0 on error.
 */
अटल पूर्णांक
svc_pool_map_init_percpu(काष्ठा svc_pool_map *m)
अणु
	अचिन्हित पूर्णांक maxpools = nr_cpu_ids;
	अचिन्हित पूर्णांक pidx = 0;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक err;

	err = svc_pool_map_alloc_arrays(m, maxpools);
	अगर (err)
		वापस err;

	क्रम_each_online_cpu(cpu) अणु
		BUG_ON(pidx >= maxpools);
		m->to_pool[cpu] = pidx;
		m->pool_to[pidx] = cpu;
		pidx++;
	पूर्ण
	/* cpus brought online later all get mapped to pool0, sorry */

	वापस pidx;
पूर्ण;


/*
 * Initialise the pool map क्रम SVC_POOL_PERNODE mode.
 * Returns number of pools or <0 on error.
 */
अटल पूर्णांक
svc_pool_map_init_pernode(काष्ठा svc_pool_map *m)
अणु
	अचिन्हित पूर्णांक maxpools = nr_node_ids;
	अचिन्हित पूर्णांक pidx = 0;
	अचिन्हित पूर्णांक node;
	पूर्णांक err;

	err = svc_pool_map_alloc_arrays(m, maxpools);
	अगर (err)
		वापस err;

	क्रम_each_node_with_cpus(node) अणु
		/* some architectures (e.g. SN2) have cpuless nodes */
		BUG_ON(pidx > maxpools);
		m->to_pool[node] = pidx;
		m->pool_to[pidx] = node;
		pidx++;
	पूर्ण
	/* nodes brought online later all get mapped to pool0, sorry */

	वापस pidx;
पूर्ण


/*
 * Add a reference to the global map of cpus to pools (and
 * vice versa).  Initialise the map अगर we're the first user.
 * Returns the number of pools.
 */
अचिन्हित पूर्णांक
svc_pool_map_get(व्योम)
अणु
	काष्ठा svc_pool_map *m = &svc_pool_map;
	पूर्णांक npools = -1;

	mutex_lock(&svc_pool_map_mutex);

	अगर (m->count++) अणु
		mutex_unlock(&svc_pool_map_mutex);
		वापस m->npools;
	पूर्ण

	अगर (m->mode == SVC_POOL_AUTO)
		m->mode = svc_pool_map_choose_mode();

	चयन (m->mode) अणु
	हाल SVC_POOL_PERCPU:
		npools = svc_pool_map_init_percpu(m);
		अवरोध;
	हाल SVC_POOL_PERNODE:
		npools = svc_pool_map_init_pernode(m);
		अवरोध;
	पूर्ण

	अगर (npools < 0) अणु
		/* शेष, or memory allocation failure */
		npools = 1;
		m->mode = SVC_POOL_GLOBAL;
	पूर्ण
	m->npools = npools;

	mutex_unlock(&svc_pool_map_mutex);
	वापस m->npools;
पूर्ण
EXPORT_SYMBOL_GPL(svc_pool_map_get);

/*
 * Drop a reference to the global map of cpus to pools.
 * When the last reference is dropped, the map data is
 * मुक्तd; this allows the sysadmin to change the pool
 * mode using the pool_mode module option without
 * rebooting or re-loading sunrpc.ko.
 */
व्योम
svc_pool_map_put(व्योम)
अणु
	काष्ठा svc_pool_map *m = &svc_pool_map;

	mutex_lock(&svc_pool_map_mutex);

	अगर (!--m->count) अणु
		kमुक्त(m->to_pool);
		m->to_pool = शून्य;
		kमुक्त(m->pool_to);
		m->pool_to = शून्य;
		m->npools = 0;
	पूर्ण

	mutex_unlock(&svc_pool_map_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(svc_pool_map_put);

अटल पूर्णांक svc_pool_map_get_node(अचिन्हित पूर्णांक pidx)
अणु
	स्थिर काष्ठा svc_pool_map *m = &svc_pool_map;

	अगर (m->count) अणु
		अगर (m->mode == SVC_POOL_PERCPU)
			वापस cpu_to_node(m->pool_to[pidx]);
		अगर (m->mode == SVC_POOL_PERNODE)
			वापस m->pool_to[pidx];
	पूर्ण
	वापस NUMA_NO_NODE;
पूर्ण
/*
 * Set the given thपढ़ो's cpus_allowed mask so that it
 * will only run on cpus in the given pool.
 */
अटल अंतरभूत व्योम
svc_pool_map_set_cpumask(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक pidx)
अणु
	काष्ठा svc_pool_map *m = &svc_pool_map;
	अचिन्हित पूर्णांक node = m->pool_to[pidx];

	/*
	 * The caller checks क्रम sv_nrpools > 1, which
	 * implies that we've been initialized.
	 */
	WARN_ON_ONCE(m->count == 0);
	अगर (m->count == 0)
		वापस;

	चयन (m->mode) अणु
	हाल SVC_POOL_PERCPU:
	अणु
		set_cpus_allowed_ptr(task, cpumask_of(node));
		अवरोध;
	पूर्ण
	हाल SVC_POOL_PERNODE:
	अणु
		set_cpus_allowed_ptr(task, cpumask_of_node(node));
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

/*
 * Use the mapping mode to choose a pool क्रम a given CPU.
 * Used when enqueueing an incoming RPC.  Always वापसs
 * a non-शून्य pool poपूर्णांकer.
 */
काष्ठा svc_pool *
svc_pool_क्रम_cpu(काष्ठा svc_serv *serv, पूर्णांक cpu)
अणु
	काष्ठा svc_pool_map *m = &svc_pool_map;
	अचिन्हित पूर्णांक pidx = 0;

	/*
	 * An uninitialised map happens in a pure client when
	 * lockd is brought up, so silently treat it the
	 * same as SVC_POOL_GLOBAL.
	 */
	अगर (svc_serv_is_pooled(serv)) अणु
		चयन (m->mode) अणु
		हाल SVC_POOL_PERCPU:
			pidx = m->to_pool[cpu];
			अवरोध;
		हाल SVC_POOL_PERNODE:
			pidx = m->to_pool[cpu_to_node(cpu)];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस &serv->sv_pools[pidx % serv->sv_nrpools];
पूर्ण

पूर्णांक svc_rpcb_setup(काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	पूर्णांक err;

	err = rpcb_create_local(net);
	अगर (err)
		वापस err;

	/* Remove any stale porपंचांगap registrations */
	svc_unरेजिस्टर(serv, net);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(svc_rpcb_setup);

व्योम svc_rpcb_cleanup(काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	svc_unरेजिस्टर(serv, net);
	rpcb_put_local(net);
पूर्ण
EXPORT_SYMBOL_GPL(svc_rpcb_cleanup);

अटल पूर्णांक svc_uses_rpcbind(काष्ठा svc_serv *serv)
अणु
	काष्ठा svc_program	*progp;
	अचिन्हित पूर्णांक		i;

	क्रम (progp = serv->sv_program; progp; progp = progp->pg_next) अणु
		क्रम (i = 0; i < progp->pg_nvers; i++) अणु
			अगर (progp->pg_vers[i] == शून्य)
				जारी;
			अगर (!progp->pg_vers[i]->vs_hidden)
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक svc_bind(काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	अगर (!svc_uses_rpcbind(serv))
		वापस 0;
	वापस svc_rpcb_setup(serv, net);
पूर्ण
EXPORT_SYMBOL_GPL(svc_bind);

#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
अटल व्योम
__svc_init_bc(काष्ठा svc_serv *serv)
अणु
	INIT_LIST_HEAD(&serv->sv_cb_list);
	spin_lock_init(&serv->sv_cb_lock);
	init_रुकोqueue_head(&serv->sv_cb_रुकोq);
पूर्ण
#अन्यथा
अटल व्योम
__svc_init_bc(काष्ठा svc_serv *serv)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Create an RPC service
 */
अटल काष्ठा svc_serv *
__svc_create(काष्ठा svc_program *prog, अचिन्हित पूर्णांक bufsize, पूर्णांक npools,
	     स्थिर काष्ठा svc_serv_ops *ops)
अणु
	काष्ठा svc_serv	*serv;
	अचिन्हित पूर्णांक vers;
	अचिन्हित पूर्णांक xdrsize;
	अचिन्हित पूर्णांक i;

	अगर (!(serv = kzalloc(माप(*serv), GFP_KERNEL)))
		वापस शून्य;
	serv->sv_name      = prog->pg_name;
	serv->sv_program   = prog;
	serv->sv_nrthपढ़ोs = 1;
	serv->sv_stats     = prog->pg_stats;
	अगर (bufsize > RPCSVC_MAXPAYLOAD)
		bufsize = RPCSVC_MAXPAYLOAD;
	serv->sv_max_payload = bufsize? bufsize : 4096;
	serv->sv_max_mesg  = roundup(serv->sv_max_payload + PAGE_SIZE, PAGE_SIZE);
	serv->sv_ops = ops;
	xdrsize = 0;
	जबतक (prog) अणु
		prog->pg_lovers = prog->pg_nvers-1;
		क्रम (vers=0; vers<prog->pg_nvers ; vers++)
			अगर (prog->pg_vers[vers]) अणु
				prog->pg_hivers = vers;
				अगर (prog->pg_lovers > vers)
					prog->pg_lovers = vers;
				अगर (prog->pg_vers[vers]->vs_xdrsize > xdrsize)
					xdrsize = prog->pg_vers[vers]->vs_xdrsize;
			पूर्ण
		prog = prog->pg_next;
	पूर्ण
	serv->sv_xdrsize   = xdrsize;
	INIT_LIST_HEAD(&serv->sv_tempsocks);
	INIT_LIST_HEAD(&serv->sv_permsocks);
	समयr_setup(&serv->sv_tempसमयr, शून्य, 0);
	spin_lock_init(&serv->sv_lock);

	__svc_init_bc(serv);

	serv->sv_nrpools = npools;
	serv->sv_pools =
		kसुस्मृति(serv->sv_nrpools, माप(काष्ठा svc_pool),
			GFP_KERNEL);
	अगर (!serv->sv_pools) अणु
		kमुक्त(serv);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < serv->sv_nrpools; i++) अणु
		काष्ठा svc_pool *pool = &serv->sv_pools[i];

		dprपूर्णांकk("svc: initialising pool %u for %s\n",
				i, serv->sv_name);

		pool->sp_id = i;
		INIT_LIST_HEAD(&pool->sp_sockets);
		INIT_LIST_HEAD(&pool->sp_all_thपढ़ोs);
		spin_lock_init(&pool->sp_lock);
	पूर्ण

	वापस serv;
पूर्ण

काष्ठा svc_serv *
svc_create(काष्ठा svc_program *prog, अचिन्हित पूर्णांक bufsize,
	   स्थिर काष्ठा svc_serv_ops *ops)
अणु
	वापस __svc_create(prog, bufsize, /*npools*/1, ops);
पूर्ण
EXPORT_SYMBOL_GPL(svc_create);

काष्ठा svc_serv *
svc_create_pooled(काष्ठा svc_program *prog, अचिन्हित पूर्णांक bufsize,
		  स्थिर काष्ठा svc_serv_ops *ops)
अणु
	काष्ठा svc_serv *serv;
	अचिन्हित पूर्णांक npools = svc_pool_map_get();

	serv = __svc_create(prog, bufsize, npools, ops);
	अगर (!serv)
		जाओ out_err;
	वापस serv;
out_err:
	svc_pool_map_put();
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(svc_create_pooled);

व्योम svc_shutकरोwn_net(काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	svc_बंद_net(serv, net);

	अगर (serv->sv_ops->svo_shutकरोwn)
		serv->sv_ops->svo_shutकरोwn(serv, net);
पूर्ण
EXPORT_SYMBOL_GPL(svc_shutकरोwn_net);

/*
 * Destroy an RPC service. Should be called with appropriate locking to
 * protect the sv_nrthपढ़ोs, sv_permsocks and sv_tempsocks.
 */
व्योम
svc_destroy(काष्ठा svc_serv *serv)
अणु
	dprपूर्णांकk("svc: svc_destroy(%s, %d)\n",
				serv->sv_program->pg_name,
				serv->sv_nrthपढ़ोs);

	अगर (serv->sv_nrthपढ़ोs) अणु
		अगर (--(serv->sv_nrthपढ़ोs) != 0) अणु
			svc_sock_update_bufs(serv);
			वापस;
		पूर्ण
	पूर्ण अन्यथा
		prपूर्णांकk("svc_destroy: no threads for serv=%p!\n", serv);

	del_समयr_sync(&serv->sv_tempसमयr);

	/*
	 * The last user is gone and thus all sockets have to be destroyed to
	 * the poपूर्णांक. Check this.
	 */
	BUG_ON(!list_empty(&serv->sv_permsocks));
	BUG_ON(!list_empty(&serv->sv_tempsocks));

	cache_clean_deferred(serv);

	अगर (svc_serv_is_pooled(serv))
		svc_pool_map_put();

	kमुक्त(serv->sv_pools);
	kमुक्त(serv);
पूर्ण
EXPORT_SYMBOL_GPL(svc_destroy);

/*
 * Allocate an RPC server's buffer space.
 * We allocate pages and place them in rq_pages.
 */
अटल पूर्णांक
svc_init_buffer(काष्ठा svc_rqst *rqstp, अचिन्हित पूर्णांक size, पूर्णांक node)
अणु
	अचिन्हित पूर्णांक pages, arghi;

	/* bc_xprt uses क्रमe channel allocated buffers */
	अगर (svc_is_backchannel(rqstp))
		वापस 1;

	pages = size / PAGE_SIZE + 1; /* extra page as we hold both request and reply.
				       * We assume one is at most one page
				       */
	arghi = 0;
	WARN_ON_ONCE(pages > RPCSVC_MAXPAGES);
	अगर (pages > RPCSVC_MAXPAGES)
		pages = RPCSVC_MAXPAGES;
	जबतक (pages) अणु
		काष्ठा page *p = alloc_pages_node(node, GFP_KERNEL, 0);
		अगर (!p)
			अवरोध;
		rqstp->rq_pages[arghi++] = p;
		pages--;
	पूर्ण
	वापस pages == 0;
पूर्ण

/*
 * Release an RPC server buffer
 */
अटल व्योम
svc_release_buffer(काष्ठा svc_rqst *rqstp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rqstp->rq_pages); i++)
		अगर (rqstp->rq_pages[i])
			put_page(rqstp->rq_pages[i]);
पूर्ण

काष्ठा svc_rqst *
svc_rqst_alloc(काष्ठा svc_serv *serv, काष्ठा svc_pool *pool, पूर्णांक node)
अणु
	काष्ठा svc_rqst	*rqstp;

	rqstp = kzalloc_node(माप(*rqstp), GFP_KERNEL, node);
	अगर (!rqstp)
		वापस rqstp;

	__set_bit(RQ_BUSY, &rqstp->rq_flags);
	spin_lock_init(&rqstp->rq_lock);
	rqstp->rq_server = serv;
	rqstp->rq_pool = pool;

	rqstp->rq_scratch_page = alloc_pages_node(node, GFP_KERNEL, 0);
	अगर (!rqstp->rq_scratch_page)
		जाओ out_enomem;

	rqstp->rq_argp = kदो_स्मृति_node(serv->sv_xdrsize, GFP_KERNEL, node);
	अगर (!rqstp->rq_argp)
		जाओ out_enomem;

	rqstp->rq_resp = kदो_स्मृति_node(serv->sv_xdrsize, GFP_KERNEL, node);
	अगर (!rqstp->rq_resp)
		जाओ out_enomem;

	अगर (!svc_init_buffer(rqstp, serv->sv_max_mesg, node))
		जाओ out_enomem;

	वापस rqstp;
out_enomem:
	svc_rqst_मुक्त(rqstp);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(svc_rqst_alloc);

काष्ठा svc_rqst *
svc_prepare_thपढ़ो(काष्ठा svc_serv *serv, काष्ठा svc_pool *pool, पूर्णांक node)
अणु
	काष्ठा svc_rqst	*rqstp;

	rqstp = svc_rqst_alloc(serv, pool, node);
	अगर (!rqstp)
		वापस ERR_PTR(-ENOMEM);

	serv->sv_nrthपढ़ोs++;
	spin_lock_bh(&pool->sp_lock);
	pool->sp_nrthपढ़ोs++;
	list_add_rcu(&rqstp->rq_all, &pool->sp_all_thपढ़ोs);
	spin_unlock_bh(&pool->sp_lock);
	वापस rqstp;
पूर्ण
EXPORT_SYMBOL_GPL(svc_prepare_thपढ़ो);

/*
 * Choose a pool in which to create a new thपढ़ो, क्रम svc_set_num_thपढ़ोs
 */
अटल अंतरभूत काष्ठा svc_pool *
choose_pool(काष्ठा svc_serv *serv, काष्ठा svc_pool *pool, अचिन्हित पूर्णांक *state)
अणु
	अगर (pool != शून्य)
		वापस pool;

	वापस &serv->sv_pools[(*state)++ % serv->sv_nrpools];
पूर्ण

/*
 * Choose a thपढ़ो to समाप्त, क्रम svc_set_num_thपढ़ोs
 */
अटल अंतरभूत काष्ठा task_काष्ठा *
choose_victim(काष्ठा svc_serv *serv, काष्ठा svc_pool *pool, अचिन्हित पूर्णांक *state)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा task_काष्ठा *task = शून्य;

	अगर (pool != शून्य) अणु
		spin_lock_bh(&pool->sp_lock);
	पूर्ण अन्यथा अणु
		/* choose a pool in round-robin fashion */
		क्रम (i = 0; i < serv->sv_nrpools; i++) अणु
			pool = &serv->sv_pools[--(*state) % serv->sv_nrpools];
			spin_lock_bh(&pool->sp_lock);
			अगर (!list_empty(&pool->sp_all_thपढ़ोs))
				जाओ found_pool;
			spin_unlock_bh(&pool->sp_lock);
		पूर्ण
		वापस शून्य;
	पूर्ण

found_pool:
	अगर (!list_empty(&pool->sp_all_thपढ़ोs)) अणु
		काष्ठा svc_rqst *rqstp;

		/*
		 * Remove from the pool->sp_all_thपढ़ोs list
		 * so we करोn't try to समाप्त it again.
		 */
		rqstp = list_entry(pool->sp_all_thपढ़ोs.next, काष्ठा svc_rqst, rq_all);
		set_bit(RQ_VICTIM, &rqstp->rq_flags);
		list_del_rcu(&rqstp->rq_all);
		task = rqstp->rq_task;
	पूर्ण
	spin_unlock_bh(&pool->sp_lock);

	वापस task;
पूर्ण

/* create new thपढ़ोs */
अटल पूर्णांक
svc_start_kthपढ़ोs(काष्ठा svc_serv *serv, काष्ठा svc_pool *pool, पूर्णांक nrservs)
अणु
	काष्ठा svc_rqst	*rqstp;
	काष्ठा task_काष्ठा *task;
	काष्ठा svc_pool *chosen_pool;
	अचिन्हित पूर्णांक state = serv->sv_nrthपढ़ोs-1;
	पूर्णांक node;

	करो अणु
		nrservs--;
		chosen_pool = choose_pool(serv, pool, &state);

		node = svc_pool_map_get_node(chosen_pool->sp_id);
		rqstp = svc_prepare_thपढ़ो(serv, chosen_pool, node);
		अगर (IS_ERR(rqstp))
			वापस PTR_ERR(rqstp);

		__module_get(serv->sv_ops->svo_module);
		task = kthपढ़ो_create_on_node(serv->sv_ops->svo_function, rqstp,
					      node, "%s", serv->sv_name);
		अगर (IS_ERR(task)) अणु
			module_put(serv->sv_ops->svo_module);
			svc_निकास_thपढ़ो(rqstp);
			वापस PTR_ERR(task);
		पूर्ण

		rqstp->rq_task = task;
		अगर (serv->sv_nrpools > 1)
			svc_pool_map_set_cpumask(task, chosen_pool->sp_id);

		svc_sock_update_bufs(serv);
		wake_up_process(task);
	पूर्ण जबतक (nrservs > 0);

	वापस 0;
पूर्ण


/* destroy old thपढ़ोs */
अटल पूर्णांक
svc_संकेत_kthपढ़ोs(काष्ठा svc_serv *serv, काष्ठा svc_pool *pool, पूर्णांक nrservs)
अणु
	काष्ठा task_काष्ठा *task;
	अचिन्हित पूर्णांक state = serv->sv_nrthपढ़ोs-1;

	/* destroy old thपढ़ोs */
	करो अणु
		task = choose_victim(serv, pool, &state);
		अगर (task == शून्य)
			अवरोध;
		send_sig(संक_विघ्न, task, 1);
		nrservs++;
	पूर्ण जबतक (nrservs < 0);

	वापस 0;
पूर्ण

/*
 * Create or destroy enough new thपढ़ोs to make the number
 * of thपढ़ोs the given number.  If `pool' is non-शून्य, applies
 * only to thपढ़ोs in that pool, otherwise round-robins between
 * all pools.  Caller must ensure that mutual exclusion between this and
 * server startup or shutकरोwn.
 *
 * Destroying thपढ़ोs relies on the service thपढ़ोs filling in
 * rqstp->rq_task, which only the nfs ones करो.  Assumes the serv
 * has been created using svc_create_pooled().
 *
 * Based on code that used to be in nfsd_svc() but tweaked
 * to be pool-aware.
 */
पूर्णांक
svc_set_num_thपढ़ोs(काष्ठा svc_serv *serv, काष्ठा svc_pool *pool, पूर्णांक nrservs)
अणु
	अगर (pool == शून्य) अणु
		/* The -1 assumes caller has करोne a svc_get() */
		nrservs -= (serv->sv_nrthपढ़ोs-1);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&pool->sp_lock);
		nrservs -= pool->sp_nrthपढ़ोs;
		spin_unlock_bh(&pool->sp_lock);
	पूर्ण

	अगर (nrservs > 0)
		वापस svc_start_kthपढ़ोs(serv, pool, nrservs);
	अगर (nrservs < 0)
		वापस svc_संकेत_kthपढ़ोs(serv, pool, nrservs);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(svc_set_num_thपढ़ोs);

/* destroy old thपढ़ोs */
अटल पूर्णांक
svc_stop_kthपढ़ोs(काष्ठा svc_serv *serv, काष्ठा svc_pool *pool, पूर्णांक nrservs)
अणु
	काष्ठा task_काष्ठा *task;
	अचिन्हित पूर्णांक state = serv->sv_nrthपढ़ोs-1;

	/* destroy old thपढ़ोs */
	करो अणु
		task = choose_victim(serv, pool, &state);
		अगर (task == शून्य)
			अवरोध;
		kthपढ़ो_stop(task);
		nrservs++;
	पूर्ण जबतक (nrservs < 0);
	वापस 0;
पूर्ण

पूर्णांक
svc_set_num_thपढ़ोs_sync(काष्ठा svc_serv *serv, काष्ठा svc_pool *pool, पूर्णांक nrservs)
अणु
	अगर (pool == शून्य) अणु
		/* The -1 assumes caller has करोne a svc_get() */
		nrservs -= (serv->sv_nrthपढ़ोs-1);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&pool->sp_lock);
		nrservs -= pool->sp_nrthपढ़ोs;
		spin_unlock_bh(&pool->sp_lock);
	पूर्ण

	अगर (nrservs > 0)
		वापस svc_start_kthपढ़ोs(serv, pool, nrservs);
	अगर (nrservs < 0)
		वापस svc_stop_kthपढ़ोs(serv, pool, nrservs);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(svc_set_num_thपढ़ोs_sync);

/*
 * Called from a server thपढ़ो as it's निकासing. Caller must hold the "service
 * mutex" क्रम the service.
 */
व्योम
svc_rqst_मुक्त(काष्ठा svc_rqst *rqstp)
अणु
	svc_release_buffer(rqstp);
	अगर (rqstp->rq_scratch_page)
		put_page(rqstp->rq_scratch_page);
	kमुक्त(rqstp->rq_resp);
	kमुक्त(rqstp->rq_argp);
	kमुक्त(rqstp->rq_auth_data);
	kमुक्त_rcu(rqstp, rq_rcu_head);
पूर्ण
EXPORT_SYMBOL_GPL(svc_rqst_मुक्त);

व्योम
svc_निकास_thपढ़ो(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_serv	*serv = rqstp->rq_server;
	काष्ठा svc_pool	*pool = rqstp->rq_pool;

	spin_lock_bh(&pool->sp_lock);
	pool->sp_nrthपढ़ोs--;
	अगर (!test_and_set_bit(RQ_VICTIM, &rqstp->rq_flags))
		list_del_rcu(&rqstp->rq_all);
	spin_unlock_bh(&pool->sp_lock);

	svc_rqst_मुक्त(rqstp);

	/* Release the server */
	अगर (serv)
		svc_destroy(serv);
पूर्ण
EXPORT_SYMBOL_GPL(svc_निकास_thपढ़ो);

/*
 * Register an "inet" protocol family netid with the local
 * rpcbind daemon via an rpcbind v4 SET request.
 *
 * No netconfig infraकाष्ठाure is available in the kernel, so
 * we map IP_ protocol numbers to netids by hand.
 *
 * Returns zero on success; a negative त्रुटि_सं value is वापसed
 * अगर any error occurs.
 */
अटल पूर्णांक __svc_rpcb_रेजिस्टर4(काष्ठा net *net, स्थिर u32 program,
				स्थिर u32 version,
				स्थिर अचिन्हित लघु protocol,
				स्थिर अचिन्हित लघु port)
अणु
	स्थिर काष्ठा sockaddr_in sin = अणु
		.sin_family		= AF_INET,
		.sin_addr.s_addr	= htonl(INADDR_ANY),
		.sin_port		= htons(port),
	पूर्ण;
	स्थिर अक्षर *netid;
	पूर्णांक error;

	चयन (protocol) अणु
	हाल IPPROTO_UDP:
		netid = RPCBIND_NETID_UDP;
		अवरोध;
	हाल IPPROTO_TCP:
		netid = RPCBIND_NETID_TCP;
		अवरोध;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	error = rpcb_v4_रेजिस्टर(net, program, version,
					(स्थिर काष्ठा sockaddr *)&sin, netid);

	/*
	 * User space didn't support rpcbind v4, so retry this
	 * registration request with the legacy rpcbind v2 protocol.
	 */
	अगर (error == -EPROTONOSUPPORT)
		error = rpcb_रेजिस्टर(net, program, version, protocol, port);

	वापस error;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/*
 * Register an "inet6" protocol family netid with the local
 * rpcbind daemon via an rpcbind v4 SET request.
 *
 * No netconfig infraकाष्ठाure is available in the kernel, so
 * we map IP_ protocol numbers to netids by hand.
 *
 * Returns zero on success; a negative त्रुटि_सं value is वापसed
 * अगर any error occurs.
 */
अटल पूर्णांक __svc_rpcb_रेजिस्टर6(काष्ठा net *net, स्थिर u32 program,
				स्थिर u32 version,
				स्थिर अचिन्हित लघु protocol,
				स्थिर अचिन्हित लघु port)
अणु
	स्थिर काष्ठा sockaddr_in6 sin6 = अणु
		.sin6_family		= AF_INET6,
		.sin6_addr		= IN6ADDR_ANY_INIT,
		.sin6_port		= htons(port),
	पूर्ण;
	स्थिर अक्षर *netid;
	पूर्णांक error;

	चयन (protocol) अणु
	हाल IPPROTO_UDP:
		netid = RPCBIND_NETID_UDP6;
		अवरोध;
	हाल IPPROTO_TCP:
		netid = RPCBIND_NETID_TCP6;
		अवरोध;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	error = rpcb_v4_रेजिस्टर(net, program, version,
					(स्थिर काष्ठा sockaddr *)&sin6, netid);

	/*
	 * User space didn't support rpcbind version 4, so we won't
	 * use a PF_INET6 listener.
	 */
	अगर (error == -EPROTONOSUPPORT)
		error = -EAFNOSUPPORT;

	वापस error;
पूर्ण
#पूर्ण_अगर	/* IS_ENABLED(CONFIG_IPV6) */

/*
 * Register a kernel RPC service via rpcbind version 4.
 *
 * Returns zero on success; a negative त्रुटि_सं value is वापसed
 * अगर any error occurs.
 */
अटल पूर्णांक __svc_रेजिस्टर(काष्ठा net *net, स्थिर अक्षर *progname,
			  स्थिर u32 program, स्थिर u32 version,
			  स्थिर पूर्णांक family,
			  स्थिर अचिन्हित लघु protocol,
			  स्थिर अचिन्हित लघु port)
अणु
	पूर्णांक error = -EAFNOSUPPORT;

	चयन (family) अणु
	हाल PF_INET:
		error = __svc_rpcb_रेजिस्टर4(net, program, version,
						protocol, port);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल PF_INET6:
		error = __svc_rpcb_रेजिस्टर6(net, program, version,
						protocol, port);
#पूर्ण_अगर
	पूर्ण

	trace_svc_रेजिस्टर(progname, version, protocol, port, family, error);
	वापस error;
पूर्ण

पूर्णांक svc_rpcbind_set_version(काष्ठा net *net,
			    स्थिर काष्ठा svc_program *progp,
			    u32 version, पूर्णांक family,
			    अचिन्हित लघु proto,
			    अचिन्हित लघु port)
अणु
	वापस __svc_रेजिस्टर(net, progp->pg_name, progp->pg_prog,
				version, family, proto, port);

पूर्ण
EXPORT_SYMBOL_GPL(svc_rpcbind_set_version);

पूर्णांक svc_generic_rpcbind_set(काष्ठा net *net,
			    स्थिर काष्ठा svc_program *progp,
			    u32 version, पूर्णांक family,
			    अचिन्हित लघु proto,
			    अचिन्हित लघु port)
अणु
	स्थिर काष्ठा svc_version *vers = progp->pg_vers[version];
	पूर्णांक error;

	अगर (vers == शून्य)
		वापस 0;

	अगर (vers->vs_hidden) अणु
		trace_svc_noरेजिस्टर(progp->pg_name, version, proto,
				     port, family, 0);
		वापस 0;
	पूर्ण

	/*
	 * Don't रेजिस्टर a UDP port अगर we need congestion
	 * control.
	 */
	अगर (vers->vs_need_cong_ctrl && proto == IPPROTO_UDP)
		वापस 0;

	error = svc_rpcbind_set_version(net, progp, version,
					family, proto, port);

	वापस (vers->vs_rpcb_optnl) ? 0 : error;
पूर्ण
EXPORT_SYMBOL_GPL(svc_generic_rpcbind_set);

/**
 * svc_रेजिस्टर - रेजिस्टर an RPC service with the local porपंचांगapper
 * @serv: svc_serv काष्ठा क्रम the service to रेजिस्टर
 * @net: net namespace क्रम the service to रेजिस्टर
 * @family: protocol family of service's listener socket
 * @proto: transport protocol number to advertise
 * @port: port to advertise
 *
 * Service is रेजिस्टरed क्रम any address in the passed-in protocol family
 */
पूर्णांक svc_रेजिस्टर(स्थिर काष्ठा svc_serv *serv, काष्ठा net *net,
		 स्थिर पूर्णांक family, स्थिर अचिन्हित लघु proto,
		 स्थिर अचिन्हित लघु port)
अणु
	काष्ठा svc_program	*progp;
	अचिन्हित पूर्णांक		i;
	पूर्णांक			error = 0;

	WARN_ON_ONCE(proto == 0 && port == 0);
	अगर (proto == 0 && port == 0)
		वापस -EINVAL;

	क्रम (progp = serv->sv_program; progp; progp = progp->pg_next) अणु
		क्रम (i = 0; i < progp->pg_nvers; i++) अणु

			error = progp->pg_rpcbind_set(net, progp, i,
					family, proto, port);
			अगर (error < 0) अणु
				prपूर्णांकk(KERN_WARNING "svc: failed to register "
					"%sv%u RPC service (errno %d).\n",
					progp->pg_name, i, -error);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस error;
पूर्ण

/*
 * If user space is running rpcbind, it should take the v4 UNSET
 * and clear everything क्रम this [program, version].  If user space
 * is running porपंचांगap, it will reject the v4 UNSET, but won't have
 * any "inet6" entries anyway.  So a PMAP_UNSET should be sufficient
 * in this हाल to clear all existing entries क्रम [program, version].
 */
अटल व्योम __svc_unरेजिस्टर(काष्ठा net *net, स्थिर u32 program, स्थिर u32 version,
			     स्थिर अक्षर *progname)
अणु
	पूर्णांक error;

	error = rpcb_v4_रेजिस्टर(net, program, version, शून्य, "");

	/*
	 * User space didn't support rpcbind v4, so retry this
	 * request with the legacy rpcbind v2 protocol.
	 */
	अगर (error == -EPROTONOSUPPORT)
		error = rpcb_रेजिस्टर(net, program, version, 0, 0);

	trace_svc_unरेजिस्टर(progname, version, error);
पूर्ण

/*
 * All netids, bind addresses and ports रेजिस्टरed क्रम [program, version]
 * are हटाओd from the local rpcbind database (अगर the service is not
 * hidden) to make way क्रम a new instance of the service.
 *
 * The result of unregistration is reported via dprपूर्णांकk क्रम those who want
 * verअगरication of the result, but is otherwise not important.
 */
अटल व्योम svc_unरेजिस्टर(स्थिर काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	काष्ठा svc_program *progp;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	clear_thपढ़ो_flag(TIF_SIGPENDING);

	क्रम (progp = serv->sv_program; progp; progp = progp->pg_next) अणु
		क्रम (i = 0; i < progp->pg_nvers; i++) अणु
			अगर (progp->pg_vers[i] == शून्य)
				जारी;
			अगर (progp->pg_vers[i]->vs_hidden)
				जारी;
			__svc_unरेजिस्टर(net, progp->pg_prog, i, progp->pg_name);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&current->sighand->siglock, flags);
	recalc_संक_बाकी();
	spin_unlock_irqrestore(&current->sighand->siglock, flags);
पूर्ण

/*
 * dprपूर्णांकk the given error with the address of the client that caused it.
 */
#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
अटल __म_लिखो(2, 3)
व्योम svc_prपूर्णांकk(काष्ठा svc_rqst *rqstp, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	अक्षर 	buf[RPC_MAX_ADDRBUFLEN];

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	dprपूर्णांकk("svc: %s: %pV", svc_prपूर्णांक_addr(rqstp, buf, माप(buf)), &vaf);

	बहु_पूर्ण(args);
पूर्ण
#अन्यथा
अटल __म_लिखो(2,3) व्योम svc_prपूर्णांकk(काष्ठा svc_rqst *rqstp, स्थिर अक्षर *fmt, ...) अणुपूर्ण
#पूर्ण_अगर

__be32
svc_वापस_autherr(काष्ठा svc_rqst *rqstp, __be32 auth_err)
अणु
	set_bit(RQ_AUTHERR, &rqstp->rq_flags);
	वापस auth_err;
पूर्ण
EXPORT_SYMBOL_GPL(svc_वापस_autherr);

अटल __be32
svc_get_autherr(काष्ठा svc_rqst *rqstp, __be32 *statp)
अणु
	अगर (test_and_clear_bit(RQ_AUTHERR, &rqstp->rq_flags))
		वापस *statp;
	वापस rpc_auth_ok;
पूर्ण

अटल पूर्णांक
svc_generic_dispatch(काष्ठा svc_rqst *rqstp, __be32 *statp)
अणु
	काष्ठा kvec *argv = &rqstp->rq_arg.head[0];
	काष्ठा kvec *resv = &rqstp->rq_res.head[0];
	स्थिर काष्ठा svc_procedure *procp = rqstp->rq_procinfo;

	/*
	 * Decode arguments
	 * XXX: why करो we ignore the वापस value?
	 */
	अगर (procp->pc_decode &&
	    !procp->pc_decode(rqstp, argv->iov_base)) अणु
		*statp = rpc_garbage_args;
		वापस 1;
	पूर्ण

	*statp = procp->pc_func(rqstp);

	अगर (*statp == rpc_drop_reply ||
	    test_bit(RQ_DROPME, &rqstp->rq_flags))
		वापस 0;

	अगर (test_bit(RQ_AUTHERR, &rqstp->rq_flags))
		वापस 1;

	अगर (*statp != rpc_success)
		वापस 1;

	/* Encode reply */
	अगर (procp->pc_encode &&
	    !procp->pc_encode(rqstp, resv->iov_base + resv->iov_len)) अणु
		dprपूर्णांकk("svc: failed to encode reply\n");
		/* serv->sv_stats->rpcप्रणालीerr++; */
		*statp = rpc_प्रणाली_err;
	पूर्ण
	वापस 1;
पूर्ण

__be32
svc_generic_init_request(काष्ठा svc_rqst *rqstp,
		स्थिर काष्ठा svc_program *progp,
		काष्ठा svc_process_info *ret)
अणु
	स्थिर काष्ठा svc_version *versp = शून्य;	/* compiler food */
	स्थिर काष्ठा svc_procedure *procp = शून्य;

	अगर (rqstp->rq_vers >= progp->pg_nvers )
		जाओ err_bad_vers;
	versp = progp->pg_vers[rqstp->rq_vers];
	अगर (!versp)
		जाओ err_bad_vers;

	/*
	 * Some protocol versions (namely NFSv4) require some क्रमm of
	 * congestion control.  (See RFC 7530 section 3.1 paragraph 2)
	 * In other words, UDP is not allowed. We mark those when setting
	 * up the svc_xprt, and verअगरy that here.
	 *
	 * The spec is not very clear about what error should be वापसed
	 * when someone tries to access a server that is listening on UDP
	 * क्रम lower versions. RPC_PROG_MISMATCH seems to be the बंदst
	 * fit.
	 */
	अगर (versp->vs_need_cong_ctrl && rqstp->rq_xprt &&
	    !test_bit(XPT_CONG_CTRL, &rqstp->rq_xprt->xpt_flags))
		जाओ err_bad_vers;

	अगर (rqstp->rq_proc >= versp->vs_nproc)
		जाओ err_bad_proc;
	rqstp->rq_procinfo = procp = &versp->vs_proc[rqstp->rq_proc];
	अगर (!procp)
		जाओ err_bad_proc;

	/* Initialize storage क्रम argp and resp */
	स_रखो(rqstp->rq_argp, 0, procp->pc_argsize);
	स_रखो(rqstp->rq_resp, 0, procp->pc_ressize);

	/* Bump per-procedure stats counter */
	versp->vs_count[rqstp->rq_proc]++;

	ret->dispatch = versp->vs_dispatch;
	वापस rpc_success;
err_bad_vers:
	ret->mismatch.lovers = progp->pg_lovers;
	ret->mismatch.hivers = progp->pg_hivers;
	वापस rpc_prog_mismatch;
err_bad_proc:
	वापस rpc_proc_unavail;
पूर्ण
EXPORT_SYMBOL_GPL(svc_generic_init_request);

/*
 * Common routine क्रम processing the RPC request.
 */
अटल पूर्णांक
svc_process_common(काष्ठा svc_rqst *rqstp, काष्ठा kvec *argv, काष्ठा kvec *resv)
अणु
	काष्ठा svc_program	*progp;
	स्थिर काष्ठा svc_procedure *procp = शून्य;
	काष्ठा svc_serv		*serv = rqstp->rq_server;
	काष्ठा svc_process_info process;
	__be32			*statp;
	u32			prog, vers;
	__be32			auth_stat, rpc_stat;
	पूर्णांक			auth_res;
	__be32			*reply_statp;

	rpc_stat = rpc_success;

	अगर (argv->iov_len < 6*4)
		जाओ err_लघु_len;

	/* Will be turned off by GSS पूर्णांकegrity and privacy services */
	set_bit(RQ_SPLICE_OK, &rqstp->rq_flags);
	/* Will be turned off only when NFSv4 Sessions are used */
	set_bit(RQ_USEDEFERRAL, &rqstp->rq_flags);
	clear_bit(RQ_DROPME, &rqstp->rq_flags);

	svc_putu32(resv, rqstp->rq_xid);

	vers = svc_getnl(argv);

	/* First words of reply: */
	svc_putnl(resv, 1);		/* REPLY */

	अगर (vers != 2)		/* RPC version number */
		जाओ err_bad_rpc;

	/* Save position in हाल we later decide to reject: */
	reply_statp = resv->iov_base + resv->iov_len;

	svc_putnl(resv, 0);		/* ACCEPT */

	rqstp->rq_prog = prog = svc_getnl(argv);	/* program number */
	rqstp->rq_vers = svc_getnl(argv);	/* version number */
	rqstp->rq_proc = svc_getnl(argv);	/* procedure number */

	क्रम (progp = serv->sv_program; progp; progp = progp->pg_next)
		अगर (prog == progp->pg_prog)
			अवरोध;

	/*
	 * Decode auth data, and add verअगरier to reply buffer.
	 * We करो this beक्रमe anything अन्यथा in order to get a decent
	 * auth verअगरier.
	 */
	auth_res = svc_authenticate(rqstp, &auth_stat);
	/* Also give the program a chance to reject this call: */
	अगर (auth_res == SVC_OK && progp) अणु
		auth_stat = rpc_autherr_badcred;
		auth_res = progp->pg_authenticate(rqstp);
	पूर्ण
	अगर (auth_res != SVC_OK)
		trace_svc_authenticate(rqstp, auth_res, auth_stat);
	चयन (auth_res) अणु
	हाल SVC_OK:
		अवरोध;
	हाल SVC_GARBAGE:
		जाओ err_garbage;
	हाल SVC_SYSERR:
		rpc_stat = rpc_प्रणाली_err;
		जाओ err_bad;
	हाल SVC_DENIED:
		जाओ err_bad_auth;
	हाल SVC_CLOSE:
		जाओ बंद;
	हाल SVC_DROP:
		जाओ dropit;
	हाल SVC_COMPLETE:
		जाओ sendit;
	पूर्ण

	अगर (progp == शून्य)
		जाओ err_bad_prog;

	rpc_stat = progp->pg_init_request(rqstp, progp, &process);
	चयन (rpc_stat) अणु
	हाल rpc_success:
		अवरोध;
	हाल rpc_prog_unavail:
		जाओ err_bad_prog;
	हाल rpc_prog_mismatch:
		जाओ err_bad_vers;
	हाल rpc_proc_unavail:
		जाओ err_bad_proc;
	पूर्ण

	procp = rqstp->rq_procinfo;
	/* Should this check go पूर्णांकo the dispatcher? */
	अगर (!procp || !procp->pc_func)
		जाओ err_bad_proc;

	/* Syntactic check complete */
	serv->sv_stats->rpccnt++;
	trace_svc_process(rqstp, progp->pg_name);

	/* Build the reply header. */
	statp = resv->iov_base +resv->iov_len;
	svc_putnl(resv, RPC_SUCCESS);

	/* un-reserve some of the out-queue now that we have a
	 * better idea of reply size
	 */
	अगर (procp->pc_xdrressize)
		svc_reserve_auth(rqstp, procp->pc_xdrressize<<2);

	/* Call the function that processes the request. */
	अगर (!process.dispatch) अणु
		अगर (!svc_generic_dispatch(rqstp, statp))
			जाओ release_dropit;
		अगर (*statp == rpc_garbage_args)
			जाओ err_garbage;
		auth_stat = svc_get_autherr(rqstp, statp);
		अगर (auth_stat != rpc_auth_ok)
			जाओ err_release_bad_auth;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("svc: calling dispatcher\n");
		अगर (!process.dispatch(rqstp, statp))
			जाओ release_dropit; /* Release reply info */
	पूर्ण

	/* Check RPC status result */
	अगर (*statp != rpc_success)
		resv->iov_len = ((व्योम*)statp)  - resv->iov_base + 4;

	/* Release reply info */
	अगर (procp->pc_release)
		procp->pc_release(rqstp);

	अगर (procp->pc_encode == शून्य)
		जाओ dropit;

 sendit:
	अगर (svc_authorise(rqstp))
		जाओ बंद_xprt;
	वापस 1;		/* Caller can now send it */

release_dropit:
	अगर (procp->pc_release)
		procp->pc_release(rqstp);
 dropit:
	svc_authorise(rqstp);	/* करोesn't hurt to call this twice */
	dprपूर्णांकk("svc: svc_process dropit\n");
	वापस 0;

 बंद:
	svc_authorise(rqstp);
बंद_xprt:
	अगर (rqstp->rq_xprt && test_bit(XPT_TEMP, &rqstp->rq_xprt->xpt_flags))
		svc_बंद_xprt(rqstp->rq_xprt);
	dprपूर्णांकk("svc: svc_process close\n");
	वापस 0;

err_लघु_len:
	svc_prपूर्णांकk(rqstp, "short len %zd, dropping request\n",
			argv->iov_len);
	जाओ बंद_xprt;

err_bad_rpc:
	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, 1);	/* REJECT */
	svc_putnl(resv, 0);	/* RPC_MISMATCH */
	svc_putnl(resv, 2);	/* Only RPCv2 supported */
	svc_putnl(resv, 2);
	जाओ sendit;

err_release_bad_auth:
	अगर (procp->pc_release)
		procp->pc_release(rqstp);
err_bad_auth:
	dprपूर्णांकk("svc: authentication failed (%d)\n", ntohl(auth_stat));
	serv->sv_stats->rpcbadauth++;
	/* Restore ग_लिखो poपूर्णांकer to location of accept status: */
	xdr_ressize_check(rqstp, reply_statp);
	svc_putnl(resv, 1);	/* REJECT */
	svc_putnl(resv, 1);	/* AUTH_ERROR */
	svc_putnl(resv, ntohl(auth_stat));	/* status */
	जाओ sendit;

err_bad_prog:
	dprपूर्णांकk("svc: unknown program %d\n", prog);
	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, RPC_PROG_UNAVAIL);
	जाओ sendit;

err_bad_vers:
	svc_prपूर्णांकk(rqstp, "unknown version (%d for prog %d, %s)\n",
		       rqstp->rq_vers, rqstp->rq_prog, progp->pg_name);

	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, RPC_PROG_MISMATCH);
	svc_putnl(resv, process.mismatch.lovers);
	svc_putnl(resv, process.mismatch.hivers);
	जाओ sendit;

err_bad_proc:
	svc_prपूर्णांकk(rqstp, "unknown procedure (%d)\n", rqstp->rq_proc);

	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, RPC_PROC_UNAVAIL);
	जाओ sendit;

err_garbage:
	svc_prपूर्णांकk(rqstp, "failed to decode args\n");

	rpc_stat = rpc_garbage_args;
err_bad:
	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, ntohl(rpc_stat));
	जाओ sendit;
पूर्ण

/*
 * Process the RPC request.
 */
पूर्णांक
svc_process(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा kvec		*argv = &rqstp->rq_arg.head[0];
	काष्ठा kvec		*resv = &rqstp->rq_res.head[0];
	काष्ठा svc_serv		*serv = rqstp->rq_server;
	u32			dir;

	/*
	 * Setup response xdr_buf.
	 * Initially it has just one page
	 */
	rqstp->rq_next_page = &rqstp->rq_respages[1];
	resv->iov_base = page_address(rqstp->rq_respages[0]);
	resv->iov_len = 0;
	rqstp->rq_res.pages = rqstp->rq_respages + 1;
	rqstp->rq_res.len = 0;
	rqstp->rq_res.page_base = 0;
	rqstp->rq_res.page_len = 0;
	rqstp->rq_res.buflen = PAGE_SIZE;
	rqstp->rq_res.tail[0].iov_base = शून्य;
	rqstp->rq_res.tail[0].iov_len = 0;

	dir  = svc_getnl(argv);
	अगर (dir != 0) अणु
		/* direction != CALL */
		svc_prपूर्णांकk(rqstp, "bad direction %d, dropping request\n", dir);
		serv->sv_stats->rpcbadfmt++;
		जाओ out_drop;
	पूर्ण

	/* Returns 1 क्रम send, 0 क्रम drop */
	अगर (likely(svc_process_common(rqstp, argv, resv)))
		वापस svc_send(rqstp);

out_drop:
	svc_drop(rqstp);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(svc_process);

#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
/*
 * Process a backchannel RPC request that arrived over an existing
 * outbound connection
 */
पूर्णांक
bc_svc_process(काष्ठा svc_serv *serv, काष्ठा rpc_rqst *req,
	       काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा kvec	*argv = &rqstp->rq_arg.head[0];
	काष्ठा kvec	*resv = &rqstp->rq_res.head[0];
	काष्ठा rpc_task *task;
	पूर्णांक proc_error;
	पूर्णांक error;

	dprपूर्णांकk("svc: %s(%p)\n", __func__, req);

	/* Build the svc_rqst used by the common processing routine */
	rqstp->rq_xid = req->rq_xid;
	rqstp->rq_prot = req->rq_xprt->prot;
	rqstp->rq_server = serv;
	rqstp->rq_bc_net = req->rq_xprt->xprt_net;

	rqstp->rq_addrlen = माप(req->rq_xprt->addr);
	स_नकल(&rqstp->rq_addr, &req->rq_xprt->addr, rqstp->rq_addrlen);
	स_नकल(&rqstp->rq_arg, &req->rq_rcv_buf, माप(rqstp->rq_arg));
	स_नकल(&rqstp->rq_res, &req->rq_snd_buf, माप(rqstp->rq_res));

	/* Adjust the argument buffer length */
	rqstp->rq_arg.len = req->rq_निजी_buf.len;
	अगर (rqstp->rq_arg.len <= rqstp->rq_arg.head[0].iov_len) अणु
		rqstp->rq_arg.head[0].iov_len = rqstp->rq_arg.len;
		rqstp->rq_arg.page_len = 0;
	पूर्ण अन्यथा अगर (rqstp->rq_arg.len <= rqstp->rq_arg.head[0].iov_len +
			rqstp->rq_arg.page_len)
		rqstp->rq_arg.page_len = rqstp->rq_arg.len -
			rqstp->rq_arg.head[0].iov_len;
	अन्यथा
		rqstp->rq_arg.len = rqstp->rq_arg.head[0].iov_len +
			rqstp->rq_arg.page_len;

	/* reset result send buffer "put" position */
	resv->iov_len = 0;

	/*
	 * Skip the next two words because they've alपढ़ोy been
	 * processed in the transport
	 */
	svc_getu32(argv);	/* XID */
	svc_getnl(argv);	/* CALLसूची */

	/* Parse and execute the bc call */
	proc_error = svc_process_common(rqstp, argv, resv);

	atomic_dec(&req->rq_xprt->bc_slot_count);
	अगर (!proc_error) अणु
		/* Processing error: drop the request */
		xprt_मुक्त_bc_request(req);
		error = -EINVAL;
		जाओ out;
	पूर्ण
	/* Finally, send the reply synchronously */
	स_नकल(&req->rq_snd_buf, &rqstp->rq_res, माप(req->rq_snd_buf));
	task = rpc_run_bc_task(req);
	अगर (IS_ERR(task)) अणु
		error = PTR_ERR(task);
		जाओ out;
	पूर्ण

	WARN_ON_ONCE(atomic_पढ़ो(&task->tk_count) != 1);
	error = task->tk_status;
	rpc_put_task(task);

out:
	dprपूर्णांकk("svc: %s(), error=%d\n", __func__, error);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(bc_svc_process);
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANNEL */

/*
 * Return (transport-specअगरic) limit on the rpc payload.
 */
u32 svc_max_payload(स्थिर काष्ठा svc_rqst *rqstp)
अणु
	u32 max = rqstp->rq_xprt->xpt_class->xcl_max_payload;

	अगर (rqstp->rq_server->sv_max_payload < max)
		max = rqstp->rq_server->sv_max_payload;
	वापस max;
पूर्ण
EXPORT_SYMBOL_GPL(svc_max_payload);

/**
 * svc_encode_result_payload - mark a range of bytes as a result payload
 * @rqstp: svc_rqst to operate on
 * @offset: payload's byte offset in rqstp->rq_res
 * @length: size of payload, in bytes
 *
 * Returns zero on success, or a negative त्रुटि_सं अगर a permanent
 * error occurred.
 */
पूर्णांक svc_encode_result_payload(काष्ठा svc_rqst *rqstp, अचिन्हित पूर्णांक offset,
			      अचिन्हित पूर्णांक length)
अणु
	वापस rqstp->rq_xprt->xpt_ops->xpo_result_payload(rqstp, offset,
							   length);
पूर्ण
EXPORT_SYMBOL_GPL(svc_encode_result_payload);

/**
 * svc_fill_ग_लिखो_vector - Conकाष्ठा data argument क्रम VFS ग_लिखो call
 * @rqstp: svc_rqst to operate on
 * @pages: list of pages containing data payload
 * @first: buffer containing first section of ग_लिखो payload
 * @total: total number of bytes of ग_लिखो payload
 *
 * Fills in rqstp::rq_vec, and वापसs the number of elements.
 */
अचिन्हित पूर्णांक svc_fill_ग_लिखो_vector(काष्ठा svc_rqst *rqstp, काष्ठा page **pages,
				   काष्ठा kvec *first, माप_प्रकार total)
अणु
	काष्ठा kvec *vec = rqstp->rq_vec;
	अचिन्हित पूर्णांक i;

	/* Some types of transport can present the ग_लिखो payload
	 * entirely in rq_arg.pages. In this हाल, @first is empty.
	 */
	i = 0;
	अगर (first->iov_len) अणु
		vec[i].iov_base = first->iov_base;
		vec[i].iov_len = min_t(माप_प्रकार, total, first->iov_len);
		total -= vec[i].iov_len;
		++i;
	पूर्ण

	जबतक (total) अणु
		vec[i].iov_base = page_address(*pages);
		vec[i].iov_len = min_t(माप_प्रकार, total, PAGE_SIZE);
		total -= vec[i].iov_len;
		++i;
		++pages;
	पूर्ण

	WARN_ON_ONCE(i > ARRAY_SIZE(rqstp->rq_vec));
	वापस i;
पूर्ण
EXPORT_SYMBOL_GPL(svc_fill_ग_लिखो_vector);

/**
 * svc_fill_symlink_pathname - Conकाष्ठा pathname argument क्रम VFS symlink call
 * @rqstp: svc_rqst to operate on
 * @first: buffer containing first section of pathname
 * @p: buffer containing reमुख्यing section of pathname
 * @total: total length of the pathname argument
 *
 * The VFS symlink API demands a NUL-terminated pathname in mapped memory.
 * Returns poपूर्णांकer to a NUL-terminated string, or an ERR_PTR. Caller must मुक्त
 * the वापसed string.
 */
अक्षर *svc_fill_symlink_pathname(काष्ठा svc_rqst *rqstp, काष्ठा kvec *first,
				व्योम *p, माप_प्रकार total)
अणु
	माप_प्रकार len, reमुख्यing;
	अक्षर *result, *dst;

	result = kदो_स्मृति(total + 1, GFP_KERNEL);
	अगर (!result)
		वापस ERR_PTR(-ESERVERFAULT);

	dst = result;
	reमुख्यing = total;

	len = min_t(माप_प्रकार, total, first->iov_len);
	अगर (len) अणु
		स_नकल(dst, first->iov_base, len);
		dst += len;
		reमुख्यing -= len;
	पूर्ण

	अगर (reमुख्यing) अणु
		len = min_t(माप_प्रकार, reमुख्यing, PAGE_SIZE);
		स_नकल(dst, p, len);
		dst += len;
	पूर्ण

	*dst = '\0';

	/* Sanity check: Linux करोesn't allow the pathname argument to
	 * contain a NUL byte.
	 */
	अगर (म_माप(result) != total) अणु
		kमुक्त(result);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(svc_fill_symlink_pathname);
