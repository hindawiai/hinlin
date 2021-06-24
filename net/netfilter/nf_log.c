<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/seq_file.h>
#समावेश <net/protocol.h>
#समावेश <net/netfilter/nf_log.h>

#समावेश "nf_internals.h"

/* Internal logging पूर्णांकerface, which relies on the real
   LOG target modules */

#घोषणा NFLOGGER_NAME_LEN		64

पूर्णांक sysctl_nf_log_all_netns __पढ़ो_mostly;
EXPORT_SYMBOL(sysctl_nf_log_all_netns);

अटल काष्ठा nf_logger __rcu *loggers[NFPROTO_NUMPROTO][NF_LOG_TYPE_MAX] __पढ़ो_mostly;
अटल DEFINE_MUTEX(nf_log_mutex);

#घोषणा nft_log_dereference(logger) \
	rcu_dereference_रक्षित(logger, lockdep_is_held(&nf_log_mutex))

अटल काष्ठा nf_logger *__find_logger(पूर्णांक pf, स्थिर अक्षर *str_logger)
अणु
	काष्ठा nf_logger *log;
	पूर्णांक i;

	क्रम (i = 0; i < NF_LOG_TYPE_MAX; i++) अणु
		अगर (loggers[pf][i] == शून्य)
			जारी;

		log = nft_log_dereference(loggers[pf][i]);
		अगर (!strnहालcmp(str_logger, log->name, म_माप(log->name)))
			वापस log;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक nf_log_set(काष्ठा net *net, u_पूर्णांक8_t pf, स्थिर काष्ठा nf_logger *logger)
अणु
	स्थिर काष्ठा nf_logger *log;

	अगर (pf == NFPROTO_UNSPEC || pf >= ARRAY_SIZE(net->nf.nf_loggers))
		वापस -EOPNOTSUPP;

	mutex_lock(&nf_log_mutex);
	log = nft_log_dereference(net->nf.nf_loggers[pf]);
	अगर (log == शून्य)
		rcu_assign_poपूर्णांकer(net->nf.nf_loggers[pf], logger);

	mutex_unlock(&nf_log_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nf_log_set);

व्योम nf_log_unset(काष्ठा net *net, स्थिर काष्ठा nf_logger *logger)
अणु
	पूर्णांक i;
	स्थिर काष्ठा nf_logger *log;

	mutex_lock(&nf_log_mutex);
	क्रम (i = 0; i < NFPROTO_NUMPROTO; i++) अणु
		log = nft_log_dereference(net->nf.nf_loggers[i]);
		अगर (log == logger)
			RCU_INIT_POINTER(net->nf.nf_loggers[i], शून्य);
	पूर्ण
	mutex_unlock(&nf_log_mutex);
पूर्ण
EXPORT_SYMBOL(nf_log_unset);

/* वापस EEXIST अगर the same logger is रेजिस्टरed, 0 on success. */
पूर्णांक nf_log_रेजिस्टर(u_पूर्णांक8_t pf, काष्ठा nf_logger *logger)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (pf >= ARRAY_SIZE(init_net.nf.nf_loggers))
		वापस -EINVAL;

	mutex_lock(&nf_log_mutex);

	अगर (pf == NFPROTO_UNSPEC) अणु
		क्रम (i = NFPROTO_UNSPEC; i < NFPROTO_NUMPROTO; i++) अणु
			अगर (rcu_access_poपूर्णांकer(loggers[i][logger->type])) अणु
				ret = -EEXIST;
				जाओ unlock;
			पूर्ण
		पूर्ण
		क्रम (i = NFPROTO_UNSPEC; i < NFPROTO_NUMPROTO; i++)
			rcu_assign_poपूर्णांकer(loggers[i][logger->type], logger);
	पूर्ण अन्यथा अणु
		अगर (rcu_access_poपूर्णांकer(loggers[pf][logger->type])) अणु
			ret = -EEXIST;
			जाओ unlock;
		पूर्ण
		rcu_assign_poपूर्णांकer(loggers[pf][logger->type], logger);
	पूर्ण

unlock:
	mutex_unlock(&nf_log_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(nf_log_रेजिस्टर);

व्योम nf_log_unरेजिस्टर(काष्ठा nf_logger *logger)
अणु
	स्थिर काष्ठा nf_logger *log;
	पूर्णांक i;

	mutex_lock(&nf_log_mutex);
	क्रम (i = 0; i < NFPROTO_NUMPROTO; i++) अणु
		log = nft_log_dereference(loggers[i][logger->type]);
		अगर (log == logger)
			RCU_INIT_POINTER(loggers[i][logger->type], शून्य);
	पूर्ण
	mutex_unlock(&nf_log_mutex);
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL(nf_log_unरेजिस्टर);

पूर्णांक nf_log_bind_pf(काष्ठा net *net, u_पूर्णांक8_t pf,
		   स्थिर काष्ठा nf_logger *logger)
अणु
	अगर (pf >= ARRAY_SIZE(net->nf.nf_loggers))
		वापस -EINVAL;
	mutex_lock(&nf_log_mutex);
	अगर (__find_logger(pf, logger->name) == शून्य) अणु
		mutex_unlock(&nf_log_mutex);
		वापस -ENOENT;
	पूर्ण
	rcu_assign_poपूर्णांकer(net->nf.nf_loggers[pf], logger);
	mutex_unlock(&nf_log_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nf_log_bind_pf);

व्योम nf_log_unbind_pf(काष्ठा net *net, u_पूर्णांक8_t pf)
अणु
	अगर (pf >= ARRAY_SIZE(net->nf.nf_loggers))
		वापस;
	mutex_lock(&nf_log_mutex);
	RCU_INIT_POINTER(net->nf.nf_loggers[pf], शून्य);
	mutex_unlock(&nf_log_mutex);
पूर्ण
EXPORT_SYMBOL(nf_log_unbind_pf);

पूर्णांक nf_logger_find_get(पूर्णांक pf, क्रमागत nf_log_type type)
अणु
	काष्ठा nf_logger *logger;
	पूर्णांक ret = -ENOENT;

	अगर (pf == NFPROTO_INET) अणु
		ret = nf_logger_find_get(NFPROTO_IPV4, type);
		अगर (ret < 0)
			वापस ret;

		ret = nf_logger_find_get(NFPROTO_IPV6, type);
		अगर (ret < 0) अणु
			nf_logger_put(NFPROTO_IPV4, type);
			वापस ret;
		पूर्ण

		वापस 0;
	पूर्ण

	rcu_पढ़ो_lock();
	logger = rcu_dereference(loggers[pf][type]);
	अगर (logger == शून्य)
		जाओ out;

	अगर (try_module_get(logger->me))
		ret = 0;
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_logger_find_get);

व्योम nf_logger_put(पूर्णांक pf, क्रमागत nf_log_type type)
अणु
	काष्ठा nf_logger *logger;

	अगर (pf == NFPROTO_INET) अणु
		nf_logger_put(NFPROTO_IPV4, type);
		nf_logger_put(NFPROTO_IPV6, type);
		वापस;
	पूर्ण

	BUG_ON(loggers[pf][type] == शून्य);

	rcu_पढ़ो_lock();
	logger = rcu_dereference(loggers[pf][type]);
	module_put(logger->me);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(nf_logger_put);

व्योम nf_log_packet(काष्ठा net *net,
		   u_पूर्णांक8_t pf,
		   अचिन्हित पूर्णांक hooknum,
		   स्थिर काष्ठा sk_buff *skb,
		   स्थिर काष्ठा net_device *in,
		   स्थिर काष्ठा net_device *out,
		   स्थिर काष्ठा nf_loginfo *loginfo,
		   स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर prefix[NF_LOG_PREFIXLEN];
	स्थिर काष्ठा nf_logger *logger;

	rcu_पढ़ो_lock();
	अगर (loginfo != शून्य)
		logger = rcu_dereference(loggers[pf][loginfo->type]);
	अन्यथा
		logger = rcu_dereference(net->nf.nf_loggers[pf]);

	अगर (logger) अणु
		बहु_शुरू(args, fmt);
		vsnम_लिखो(prefix, माप(prefix), fmt, args);
		बहु_पूर्ण(args);
		logger->logfn(net, pf, hooknum, skb, in, out, loginfo, prefix);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(nf_log_packet);

व्योम nf_log_trace(काष्ठा net *net,
		  u_पूर्णांक8_t pf,
		  अचिन्हित पूर्णांक hooknum,
		  स्थिर काष्ठा sk_buff *skb,
		  स्थिर काष्ठा net_device *in,
		  स्थिर काष्ठा net_device *out,
		  स्थिर काष्ठा nf_loginfo *loginfo, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर prefix[NF_LOG_PREFIXLEN];
	स्थिर काष्ठा nf_logger *logger;

	rcu_पढ़ो_lock();
	logger = rcu_dereference(net->nf.nf_loggers[pf]);
	अगर (logger) अणु
		बहु_शुरू(args, fmt);
		vsnम_लिखो(prefix, माप(prefix), fmt, args);
		बहु_पूर्ण(args);
		logger->logfn(net, pf, hooknum, skb, in, out, loginfo, prefix);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(nf_log_trace);

#घोषणा S_SIZE (1024 - (माप(अचिन्हित पूर्णांक) + 1))

काष्ठा nf_log_buf अणु
	अचिन्हित पूर्णांक	count;
	अक्षर		buf[S_SIZE + 1];
पूर्ण;
अटल काष्ठा nf_log_buf emergency, *emergency_ptr = &emergency;

__म_लिखो(2, 3) पूर्णांक nf_log_buf_add(काष्ठा nf_log_buf *m, स्थिर अक्षर *f, ...)
अणु
	बहु_सूची args;
	पूर्णांक len;

	अगर (likely(m->count < S_SIZE)) अणु
		बहु_शुरू(args, f);
		len = vsnम_लिखो(m->buf + m->count, S_SIZE - m->count, f, args);
		बहु_पूर्ण(args);
		अगर (likely(m->count + len < S_SIZE)) अणु
			m->count += len;
			वापस 0;
		पूर्ण
	पूर्ण
	m->count = S_SIZE;
	prपूर्णांकk_once(KERN_ERR KBUILD_MODNAME " please increase S_SIZE\n");
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(nf_log_buf_add);

काष्ठा nf_log_buf *nf_log_buf_खोलो(व्योम)
अणु
	काष्ठा nf_log_buf *m = kदो_स्मृति(माप(*m), GFP_ATOMIC);

	अगर (unlikely(!m)) अणु
		local_bh_disable();
		करो अणु
			m = xchg(&emergency_ptr, शून्य);
		पूर्ण जबतक (!m);
	पूर्ण
	m->count = 0;
	वापस m;
पूर्ण
EXPORT_SYMBOL_GPL(nf_log_buf_खोलो);

व्योम nf_log_buf_बंद(काष्ठा nf_log_buf *m)
अणु
	m->buf[m->count] = 0;
	prपूर्णांकk("%s\n", m->buf);

	अगर (likely(m != &emergency))
		kमुक्त(m);
	अन्यथा अणु
		emergency_ptr = m;
		local_bh_enable();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nf_log_buf_बंद);

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा net *net = seq_file_net(seq);

	mutex_lock(&nf_log_mutex);

	अगर (*pos >= ARRAY_SIZE(net->nf.nf_loggers))
		वापस शून्य;

	वापस pos;
पूर्ण

अटल व्योम *seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा net *net = seq_file_net(s);

	(*pos)++;

	अगर (*pos >= ARRAY_SIZE(net->nf.nf_loggers))
		वापस शून्य;

	वापस pos;
पूर्ण

अटल व्योम seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	mutex_unlock(&nf_log_mutex);
पूर्ण

अटल पूर्णांक seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	loff_t *pos = v;
	स्थिर काष्ठा nf_logger *logger;
	पूर्णांक i;
	काष्ठा net *net = seq_file_net(s);

	logger = nft_log_dereference(net->nf.nf_loggers[*pos]);

	अगर (!logger)
		seq_म_लिखो(s, "%2lld NONE (", *pos);
	अन्यथा
		seq_म_लिखो(s, "%2lld %s (", *pos, logger->name);

	अगर (seq_has_overflowed(s))
		वापस -ENOSPC;

	क्रम (i = 0; i < NF_LOG_TYPE_MAX; i++) अणु
		अगर (loggers[*pos][i] == शून्य)
			जारी;

		logger = nft_log_dereference(loggers[*pos][i]);
		seq_माला_दो(s, logger->name);
		अगर (i == 0 && loggers[*pos][i + 1] != शून्य)
			seq_माला_दो(s, ",");

		अगर (seq_has_overflowed(s))
			वापस -ENOSPC;
	पूर्ण

	seq_माला_दो(s, ")\n");

	अगर (seq_has_overflowed(s))
		वापस -ENOSPC;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations nflog_seq_ops = अणु
	.start	= seq_start,
	.next	= seq_next,
	.stop	= seq_stop,
	.show	= seq_show,
पूर्ण;
#पूर्ण_अगर /* PROC_FS */

#अगर_घोषित CONFIG_SYSCTL
अटल अक्षर nf_log_sysctl_fnames[NFPROTO_NUMPROTO-NFPROTO_UNSPEC][3];
अटल काष्ठा ctl_table nf_log_sysctl_table[NFPROTO_NUMPROTO+1];
अटल काष्ठा ctl_table_header *nf_log_sysctl_fhdr;

अटल काष्ठा ctl_table nf_log_sysctl_ftable[] = अणु
	अणु
		.procname	= "nf_log_all_netns",
		.data		= &sysctl_nf_log_all_netns,
		.maxlen		= माप(sysctl_nf_log_all_netns),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक nf_log_proc_करोstring(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	स्थिर काष्ठा nf_logger *logger;
	अक्षर buf[NFLOGGER_NAME_LEN];
	पूर्णांक r = 0;
	पूर्णांक tindex = (अचिन्हित दीर्घ)table->extra1;
	काष्ठा net *net = table->extra2;

	अगर (ग_लिखो) अणु
		काष्ठा ctl_table पंचांगp = *table;

		/* proc_करोstring() can append to existing strings, so we need to
		 * initialize it as an empty string.
		 */
		buf[0] = '\0';
		पंचांगp.data = buf;
		r = proc_करोstring(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
		अगर (r)
			वापस r;

		अगर (!म_भेद(buf, "NONE")) अणु
			nf_log_unbind_pf(net, tindex);
			वापस 0;
		पूर्ण
		mutex_lock(&nf_log_mutex);
		logger = __find_logger(tindex, buf);
		अगर (logger == शून्य) अणु
			mutex_unlock(&nf_log_mutex);
			वापस -ENOENT;
		पूर्ण
		rcu_assign_poपूर्णांकer(net->nf.nf_loggers[tindex], logger);
		mutex_unlock(&nf_log_mutex);
	पूर्ण अन्यथा अणु
		काष्ठा ctl_table पंचांगp = *table;

		पंचांगp.data = buf;
		mutex_lock(&nf_log_mutex);
		logger = nft_log_dereference(net->nf.nf_loggers[tindex]);
		अगर (!logger)
			strlcpy(buf, "NONE", माप(buf));
		अन्यथा
			strlcpy(buf, logger->name, माप(buf));
		mutex_unlock(&nf_log_mutex);
		r = proc_करोstring(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक netfilter_log_sysctl_init(काष्ठा net *net)
अणु
	पूर्णांक i;
	काष्ठा ctl_table *table;

	table = nf_log_sysctl_table;
	अगर (!net_eq(net, &init_net)) अणु
		table = kmemdup(nf_log_sysctl_table,
				 माप(nf_log_sysctl_table),
				 GFP_KERNEL);
		अगर (!table)
			जाओ err_alloc;
	पूर्ण अन्यथा अणु
		क्रम (i = NFPROTO_UNSPEC; i < NFPROTO_NUMPROTO; i++) अणु
			snम_लिखो(nf_log_sysctl_fnames[i],
				 3, "%d", i);
			nf_log_sysctl_table[i].procname	=
				nf_log_sysctl_fnames[i];
			nf_log_sysctl_table[i].maxlen = NFLOGGER_NAME_LEN;
			nf_log_sysctl_table[i].mode = 0644;
			nf_log_sysctl_table[i].proc_handler =
				nf_log_proc_करोstring;
			nf_log_sysctl_table[i].extra1 =
				(व्योम *)(अचिन्हित दीर्घ) i;
		पूर्ण
		nf_log_sysctl_fhdr = रेजिस्टर_net_sysctl(net, "net/netfilter",
							 nf_log_sysctl_ftable);
		अगर (!nf_log_sysctl_fhdr)
			जाओ err_freg;
	पूर्ण

	क्रम (i = NFPROTO_UNSPEC; i < NFPROTO_NUMPROTO; i++)
		table[i].extra2 = net;

	net->nf.nf_log_dir_header = रेजिस्टर_net_sysctl(net,
						"net/netfilter/nf_log",
						table);
	अगर (!net->nf.nf_log_dir_header)
		जाओ err_reg;

	वापस 0;

err_reg:
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
	अन्यथा
		unरेजिस्टर_net_sysctl_table(nf_log_sysctl_fhdr);
err_freg:
err_alloc:
	वापस -ENOMEM;
पूर्ण

अटल व्योम netfilter_log_sysctl_निकास(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	table = net->nf.nf_log_dir_header->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->nf.nf_log_dir_header);
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
	अन्यथा
		unरेजिस्टर_net_sysctl_table(nf_log_sysctl_fhdr);
पूर्ण
#अन्यथा
अटल पूर्णांक netfilter_log_sysctl_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल व्योम netfilter_log_sysctl_निकास(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */

अटल पूर्णांक __net_init nf_log_net_init(काष्ठा net *net)
अणु
	पूर्णांक ret = -ENOMEM;

#अगर_घोषित CONFIG_PROC_FS
	अगर (!proc_create_net("nf_log", 0444, net->nf.proc_netfilter,
			&nflog_seq_ops, माप(काष्ठा seq_net_निजी)))
		वापस ret;
#पूर्ण_अगर
	ret = netfilter_log_sysctl_init(net);
	अगर (ret < 0)
		जाओ out_sysctl;

	वापस 0;

out_sysctl:
#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("nf_log", net->nf.proc_netfilter);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल व्योम __net_निकास nf_log_net_निकास(काष्ठा net *net)
अणु
	netfilter_log_sysctl_निकास(net);
#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("nf_log", net->nf.proc_netfilter);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा pernet_operations nf_log_net_ops = अणु
	.init = nf_log_net_init,
	.निकास = nf_log_net_निकास,
पूर्ण;

पूर्णांक __init netfilter_log_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&nf_log_net_ops);
पूर्ण
