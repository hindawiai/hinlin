<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _X_TABLES_H
#घोषणा _X_TABLES_H


#समावेश <linux/netdevice.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/netfilter.h>
#समावेश <uapi/linux/netfilter/x_tables.h>

/* Test a काष्ठा->invflags and a boolean क्रम inequality */
#घोषणा NF_INVF(ptr, flag, boolean)					\
	((boolean) ^ !!((ptr)->invflags & (flag)))

/**
 * काष्ठा xt_action_param - parameters क्रम matches/tarमाला_लो
 *
 * @match:	the match extension
 * @target:	the target extension
 * @matchinfo:	per-match data
 * @targetinfo:	per-target data
 * @state:	poपूर्णांकer to hook state this packet came from
 * @fragoff:	packet is a fragment, this is the data offset
 * @thoff:	position of transport header relative to skb->data
 *
 * Fields written to by extensions:
 *
 * @hotdrop:	drop packet अगर we had inspection problems
 */
काष्ठा xt_action_param अणु
	जोड़ अणु
		स्थिर काष्ठा xt_match *match;
		स्थिर काष्ठा xt_target *target;
	पूर्ण;
	जोड़ अणु
		स्थिर व्योम *matchinfo, *targinfo;
	पूर्ण;
	स्थिर काष्ठा nf_hook_state *state;
	पूर्णांक fragoff;
	अचिन्हित पूर्णांक thoff;
	bool hotdrop;
पूर्ण;

अटल अंतरभूत काष्ठा net *xt_net(स्थिर काष्ठा xt_action_param *par)
अणु
	वापस par->state->net;
पूर्ण

अटल अंतरभूत काष्ठा net_device *xt_in(स्थिर काष्ठा xt_action_param *par)
अणु
	वापस par->state->in;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *xt_inname(स्थिर काष्ठा xt_action_param *par)
अणु
	वापस par->state->in->name;
पूर्ण

अटल अंतरभूत काष्ठा net_device *xt_out(स्थिर काष्ठा xt_action_param *par)
अणु
	वापस par->state->out;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *xt_outname(स्थिर काष्ठा xt_action_param *par)
अणु
	वापस par->state->out->name;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xt_hooknum(स्थिर काष्ठा xt_action_param *par)
अणु
	वापस par->state->hook;
पूर्ण

अटल अंतरभूत u_पूर्णांक8_t xt_family(स्थिर काष्ठा xt_action_param *par)
अणु
	वापस par->state->pf;
पूर्ण

/**
 * काष्ठा xt_mtchk_param - parameters क्रम match extensions'
 * checkentry functions
 *
 * @net:	network namespace through which the check was invoked
 * @table:	table the rule is tried to be inserted पूर्णांकo
 * @entryinfo:	the family-specअगरic rule data
 * 		(काष्ठा ipt_ip, ip6t_ip, arpt_arp or (note) ebt_entry)
 * @match:	काष्ठा xt_match through which this function was invoked
 * @matchinfo:	per-match data
 * @hook_mask:	via which hooks the new rule is reachable
 * Other fields as above.
 */
काष्ठा xt_mtchk_param अणु
	काष्ठा net *net;
	स्थिर अक्षर *table;
	स्थिर व्योम *entryinfo;
	स्थिर काष्ठा xt_match *match;
	व्योम *matchinfo;
	अचिन्हित पूर्णांक hook_mask;
	u_पूर्णांक8_t family;
	bool nft_compat;
पूर्ण;

/**
 * काष्ठा xt_mdtor_param - match deकाष्ठाor parameters
 * Fields as above.
 */
काष्ठा xt_mtdtor_param अणु
	काष्ठा net *net;
	स्थिर काष्ठा xt_match *match;
	व्योम *matchinfo;
	u_पूर्णांक8_t family;
पूर्ण;

/**
 * काष्ठा xt_tgchk_param - parameters क्रम target extensions'
 * checkentry functions
 *
 * @entryinfo:	the family-specअगरic rule data
 * 		(काष्ठा ipt_entry, ip6t_entry, arpt_entry, ebt_entry)
 *
 * Other fields see above.
 */
काष्ठा xt_tgchk_param अणु
	काष्ठा net *net;
	स्थिर अक्षर *table;
	स्थिर व्योम *entryinfo;
	स्थिर काष्ठा xt_target *target;
	व्योम *targinfo;
	अचिन्हित पूर्णांक hook_mask;
	u_पूर्णांक8_t family;
	bool nft_compat;
पूर्ण;

/* Target deकाष्ठाor parameters */
काष्ठा xt_tgdtor_param अणु
	काष्ठा net *net;
	स्थिर काष्ठा xt_target *target;
	व्योम *targinfo;
	u_पूर्णांक8_t family;
पूर्ण;

काष्ठा xt_match अणु
	काष्ठा list_head list;

	स्थिर अक्षर name[XT_EXTENSION_MAXNAMELEN];
	u_पूर्णांक8_t revision;

	/* Return true or false: वापस FALSE and set *hotdrop = 1 to
           क्रमce immediate packet drop. */
	/* Arguments changed since 2.6.9, as this must now handle
	   non-linear skb, using skb_header_poपूर्णांकer and
	   skb_ip_make_writable. */
	bool (*match)(स्थिर काष्ठा sk_buff *skb,
		      काष्ठा xt_action_param *);

	/* Called when user tries to insert an entry of this type. */
	पूर्णांक (*checkentry)(स्थिर काष्ठा xt_mtchk_param *);

	/* Called when entry of this type deleted. */
	व्योम (*destroy)(स्थिर काष्ठा xt_mtdtor_param *);
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	/* Called when userspace align dअगरfers from kernel space one */
	व्योम (*compat_from_user)(व्योम *dst, स्थिर व्योम *src);
	पूर्णांक (*compat_to_user)(व्योम __user *dst, स्थिर व्योम *src);
#पूर्ण_अगर
	/* Set this to THIS_MODULE अगर you are a module, otherwise शून्य */
	काष्ठा module *me;

	स्थिर अक्षर *table;
	अचिन्हित पूर्णांक matchsize;
	अचिन्हित पूर्णांक usersize;
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	अचिन्हित पूर्णांक compatsize;
#पूर्ण_अगर
	अचिन्हित पूर्णांक hooks;
	अचिन्हित लघु proto;

	अचिन्हित लघु family;
पूर्ण;

/* Registration hooks क्रम tarमाला_लो. */
काष्ठा xt_target अणु
	काष्ठा list_head list;

	स्थिर अक्षर name[XT_EXTENSION_MAXNAMELEN];
	u_पूर्णांक8_t revision;

	/* Returns verdict. Argument order changed since 2.6.9, as this
	   must now handle non-linear skbs, using skb_copy_bits and
	   skb_ip_make_writable. */
	अचिन्हित पूर्णांक (*target)(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा xt_action_param *);

	/* Called when user tries to insert an entry of this type:
           hook_mask is a biपंचांगask of hooks from which it can be
           called. */
	/* Should वापस 0 on success or an error code otherwise (-Exxxx). */
	पूर्णांक (*checkentry)(स्थिर काष्ठा xt_tgchk_param *);

	/* Called when entry of this type deleted. */
	व्योम (*destroy)(स्थिर काष्ठा xt_tgdtor_param *);
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	/* Called when userspace align dअगरfers from kernel space one */
	व्योम (*compat_from_user)(व्योम *dst, स्थिर व्योम *src);
	पूर्णांक (*compat_to_user)(व्योम __user *dst, स्थिर व्योम *src);
#पूर्ण_अगर
	/* Set this to THIS_MODULE अगर you are a module, otherwise शून्य */
	काष्ठा module *me;

	स्थिर अक्षर *table;
	अचिन्हित पूर्णांक tarमाला_लोize;
	अचिन्हित पूर्णांक usersize;
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	अचिन्हित पूर्णांक compatsize;
#पूर्ण_अगर
	अचिन्हित पूर्णांक hooks;
	अचिन्हित लघु proto;

	अचिन्हित लघु family;
पूर्ण;

/* Furniture shopping... */
काष्ठा xt_table अणु
	काष्ठा list_head list;

	/* What hooks you will enter on */
	अचिन्हित पूर्णांक valid_hooks;

	/* Man behind the curtain... */
	काष्ठा xt_table_info *निजी;

	/* hook ops that रेजिस्टर the table with the netfilter core */
	काष्ठा nf_hook_ops *ops;

	/* Set this to THIS_MODULE अगर you are a module, otherwise शून्य */
	काष्ठा module *me;

	u_पूर्णांक8_t af;		/* address/protocol family */
	पूर्णांक priority;		/* hook order */

	/* called when table is needed in the given netns */
	पूर्णांक (*table_init)(काष्ठा net *net);

	/* A unique name... */
	स्थिर अक्षर name[XT_TABLE_MAXNAMELEN];
पूर्ण;

#समावेश <linux/netfilter_ipv4.h>

/* The table itself */
काष्ठा xt_table_info अणु
	/* Size per table */
	अचिन्हित पूर्णांक size;
	/* Number of entries: FIXME. --RR */
	अचिन्हित पूर्णांक number;
	/* Initial number of entries. Needed क्रम module usage count */
	अचिन्हित पूर्णांक initial_entries;

	/* Entry poपूर्णांकs and underflows */
	अचिन्हित पूर्णांक hook_entry[NF_INET_NUMHOOKS];
	अचिन्हित पूर्णांक underflow[NF_INET_NUMHOOKS];

	/*
	 * Number of user chains. Since tables cannot have loops, at most
	 * @stacksize jumps (number of user chains) can possibly be made.
	 */
	अचिन्हित पूर्णांक stacksize;
	व्योम ***jumpstack;

	अचिन्हित अक्षर entries[] __aligned(8);
पूर्ण;

पूर्णांक xt_रेजिस्टर_target(काष्ठा xt_target *target);
व्योम xt_unरेजिस्टर_target(काष्ठा xt_target *target);
पूर्णांक xt_रेजिस्टर_tarमाला_लो(काष्ठा xt_target *target, अचिन्हित पूर्णांक n);
व्योम xt_unरेजिस्टर_tarमाला_लो(काष्ठा xt_target *target, अचिन्हित पूर्णांक n);

पूर्णांक xt_रेजिस्टर_match(काष्ठा xt_match *target);
व्योम xt_unरेजिस्टर_match(काष्ठा xt_match *target);
पूर्णांक xt_रेजिस्टर_matches(काष्ठा xt_match *match, अचिन्हित पूर्णांक n);
व्योम xt_unरेजिस्टर_matches(काष्ठा xt_match *match, अचिन्हित पूर्णांक n);

पूर्णांक xt_check_entry_offsets(स्थिर व्योम *base, स्थिर अक्षर *elems,
			   अचिन्हित पूर्णांक target_offset,
			   अचिन्हित पूर्णांक next_offset);

पूर्णांक xt_check_table_hooks(स्थिर काष्ठा xt_table_info *info, अचिन्हित पूर्णांक valid_hooks);

अचिन्हित पूर्णांक *xt_alloc_entry_offsets(अचिन्हित पूर्णांक size);
bool xt_find_jump_offset(स्थिर अचिन्हित पूर्णांक *offsets,
			 अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक size);

पूर्णांक xt_check_proc_name(स्थिर अक्षर *name, अचिन्हित पूर्णांक size);

पूर्णांक xt_check_match(काष्ठा xt_mtchk_param *, अचिन्हित पूर्णांक size, u16 proto,
		   bool inv_proto);
पूर्णांक xt_check_target(काष्ठा xt_tgchk_param *, अचिन्हित पूर्णांक size, u16 proto,
		    bool inv_proto);

पूर्णांक xt_match_to_user(स्थिर काष्ठा xt_entry_match *m,
		     काष्ठा xt_entry_match __user *u);
पूर्णांक xt_target_to_user(स्थिर काष्ठा xt_entry_target *t,
		      काष्ठा xt_entry_target __user *u);
पूर्णांक xt_data_to_user(व्योम __user *dst, स्थिर व्योम *src,
		    पूर्णांक usersize, पूर्णांक size, पूर्णांक aligned_size);

व्योम *xt_copy_counters(sockptr_t arg, अचिन्हित पूर्णांक len,
		       काष्ठा xt_counters_info *info);
काष्ठा xt_counters *xt_counters_alloc(अचिन्हित पूर्णांक counters);

काष्ठा xt_table *xt_रेजिस्टर_table(काष्ठा net *net,
				   स्थिर काष्ठा xt_table *table,
				   काष्ठा xt_table_info *bootstrap,
				   काष्ठा xt_table_info *newinfo);
व्योम *xt_unरेजिस्टर_table(काष्ठा xt_table *table);

काष्ठा xt_table_info *xt_replace_table(काष्ठा xt_table *table,
				       अचिन्हित पूर्णांक num_counters,
				       काष्ठा xt_table_info *newinfo,
				       पूर्णांक *error);

काष्ठा xt_match *xt_find_match(u8 af, स्थिर अक्षर *name, u8 revision);
काष्ठा xt_match *xt_request_find_match(u8 af, स्थिर अक्षर *name, u8 revision);
काष्ठा xt_target *xt_request_find_target(u8 af, स्थिर अक्षर *name, u8 revision);
पूर्णांक xt_find_revision(u8 af, स्थिर अक्षर *name, u8 revision, पूर्णांक target,
		     पूर्णांक *err);

काष्ठा xt_table *xt_find_table(काष्ठा net *net, u8 af, स्थिर अक्षर *name);
काष्ठा xt_table *xt_find_table_lock(काष्ठा net *net, u_पूर्णांक8_t af,
				    स्थिर अक्षर *name);
काष्ठा xt_table *xt_request_find_table_lock(काष्ठा net *net, u_पूर्णांक8_t af,
					    स्थिर अक्षर *name);
व्योम xt_table_unlock(काष्ठा xt_table *t);

पूर्णांक xt_proto_init(काष्ठा net *net, u_पूर्णांक8_t af);
व्योम xt_proto_fini(काष्ठा net *net, u_पूर्णांक8_t af);

काष्ठा xt_table_info *xt_alloc_table_info(अचिन्हित पूर्णांक size);
व्योम xt_मुक्त_table_info(काष्ठा xt_table_info *info);

/**
 * xt_recseq - recursive seqcount क्रम netfilter use
 *
 * Packet processing changes the seqcount only अगर no recursion happened
 * get_counters() can use पढ़ो_seqcount_begin()/पढ़ो_seqcount_retry(),
 * because we use the normal seqcount convention :
 * Low order bit set to 1 अगर a ग_लिखोr is active.
 */
DECLARE_PER_CPU(seqcount_t, xt_recseq);

/* xt_tee_enabled - true अगर x_tables needs to handle reentrancy
 *
 * Enabled अगर current ip(6)tables ruleset has at least one -j TEE rule.
 */
बाह्य काष्ठा अटल_key xt_tee_enabled;

/**
 * xt_ग_लिखो_recseq_begin - start of a ग_लिखो section
 *
 * Begin packet processing : all पढ़ोers must रुको the end
 * 1) Must be called with preemption disabled
 * 2) softirqs must be disabled too (or we should use this_cpu_add())
 * Returns :
 *  1 अगर no recursion on this cpu
 *  0 अगर recursion detected
 */
अटल अंतरभूत अचिन्हित पूर्णांक xt_ग_लिखो_recseq_begin(व्योम)
अणु
	अचिन्हित पूर्णांक addend;

	/*
	 * Low order bit of sequence is set अगर we alपढ़ोy
	 * called xt_ग_लिखो_recseq_begin().
	 */
	addend = (__this_cpu_पढ़ो(xt_recseq.sequence) + 1) & 1;

	/*
	 * This is kind of a ग_लिखो_seqcount_begin(), but addend is 0 or 1
	 * We करोnt check addend value to aव्योम a test and conditional jump,
	 * since addend is most likely 1
	 */
	__this_cpu_add(xt_recseq.sequence, addend);
	smp_mb();

	वापस addend;
पूर्ण

/**
 * xt_ग_लिखो_recseq_end - end of a ग_लिखो section
 * @addend: वापस value from previous xt_ग_लिखो_recseq_begin()
 *
 * End packet processing : all पढ़ोers can proceed
 * 1) Must be called with preemption disabled
 * 2) softirqs must be disabled too (or we should use this_cpu_add())
 */
अटल अंतरभूत व्योम xt_ग_लिखो_recseq_end(अचिन्हित पूर्णांक addend)
अणु
	/* this is kind of a ग_लिखो_seqcount_end(), but addend is 0 or 1 */
	smp_wmb();
	__this_cpu_add(xt_recseq.sequence, addend);
पूर्ण

/*
 * This helper is perक्रमmance critical and must be अंतरभूतd
 */
अटल अंतरभूत अचिन्हित दीर्घ अगरname_compare_aligned(स्थिर अक्षर *_a,
						   स्थिर अक्षर *_b,
						   स्थिर अक्षर *_mask)
अणु
	स्थिर अचिन्हित दीर्घ *a = (स्थिर अचिन्हित दीर्घ *)_a;
	स्थिर अचिन्हित दीर्घ *b = (स्थिर अचिन्हित दीर्घ *)_b;
	स्थिर अचिन्हित दीर्घ *mask = (स्थिर अचिन्हित दीर्घ *)_mask;
	अचिन्हित दीर्घ ret;

	ret = (a[0] ^ b[0]) & mask[0];
	अगर (IFNAMSIZ > माप(अचिन्हित दीर्घ))
		ret |= (a[1] ^ b[1]) & mask[1];
	अगर (IFNAMSIZ > 2 * माप(अचिन्हित दीर्घ))
		ret |= (a[2] ^ b[2]) & mask[2];
	अगर (IFNAMSIZ > 3 * माप(अचिन्हित दीर्घ))
		ret |= (a[3] ^ b[3]) & mask[3];
	BUILD_BUG_ON(IFNAMSIZ > 4 * माप(अचिन्हित दीर्घ));
	वापस ret;
पूर्ण

काष्ठा xt_percpu_counter_alloc_state अणु
	अचिन्हित पूर्णांक off;
	स्थिर अक्षर __percpu *mem;
पूर्ण;

bool xt_percpu_counter_alloc(काष्ठा xt_percpu_counter_alloc_state *state,
			     काष्ठा xt_counters *counter);
व्योम xt_percpu_counter_मुक्त(काष्ठा xt_counters *cnt);

अटल अंतरभूत काष्ठा xt_counters *
xt_get_this_cpu_counter(काष्ठा xt_counters *cnt)
अणु
	अगर (nr_cpu_ids > 1)
		वापस this_cpu_ptr((व्योम __percpu *) (अचिन्हित दीर्घ) cnt->pcnt);

	वापस cnt;
पूर्ण

अटल अंतरभूत काष्ठा xt_counters *
xt_get_per_cpu_counter(काष्ठा xt_counters *cnt, अचिन्हित पूर्णांक cpu)
अणु
	अगर (nr_cpu_ids > 1)
		वापस per_cpu_ptr((व्योम __percpu *) (अचिन्हित दीर्घ) cnt->pcnt, cpu);

	वापस cnt;
पूर्ण

काष्ठा nf_hook_ops *xt_hook_ops_alloc(स्थिर काष्ठा xt_table *, nf_hookfn *);

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
#समावेश <net/compat.h>

काष्ठा compat_xt_entry_match अणु
	जोड़ अणु
		काष्ठा अणु
			u_पूर्णांक16_t match_size;
			अक्षर name[XT_FUNCTION_MAXNAMELEN - 1];
			u_पूर्णांक8_t revision;
		पूर्ण user;
		काष्ठा अणु
			u_पूर्णांक16_t match_size;
			compat_uptr_t match;
		पूर्ण kernel;
		u_पूर्णांक16_t match_size;
	पूर्ण u;
	अचिन्हित अक्षर data[];
पूर्ण;

काष्ठा compat_xt_entry_target अणु
	जोड़ अणु
		काष्ठा अणु
			u_पूर्णांक16_t target_size;
			अक्षर name[XT_FUNCTION_MAXNAMELEN - 1];
			u_पूर्णांक8_t revision;
		पूर्ण user;
		काष्ठा अणु
			u_पूर्णांक16_t target_size;
			compat_uptr_t target;
		पूर्ण kernel;
		u_पूर्णांक16_t target_size;
	पूर्ण u;
	अचिन्हित अक्षर data[];
पूर्ण;

/* FIXME: this works only on 32 bit tasks
 * need to change whole approach in order to calculate align as function of
 * current task alignment */

काष्ठा compat_xt_counters अणु
	compat_u64 pcnt, bcnt;			/* Packet and byte counters */
पूर्ण;

काष्ठा compat_xt_counters_info अणु
	अक्षर name[XT_TABLE_MAXNAMELEN];
	compat_uपूर्णांक_t num_counters;
	काष्ठा compat_xt_counters counters[];
पूर्ण;

काष्ठा _compat_xt_align अणु
	__u8 u8;
	__u16 u16;
	__u32 u32;
	compat_u64 u64;
पूर्ण;

#घोषणा COMPAT_XT_ALIGN(s) __ALIGN_KERNEL((s), __alignof__(काष्ठा _compat_xt_align))

व्योम xt_compat_lock(u_पूर्णांक8_t af);
व्योम xt_compat_unlock(u_पूर्णांक8_t af);

पूर्णांक xt_compat_add_offset(u_पूर्णांक8_t af, अचिन्हित पूर्णांक offset, पूर्णांक delta);
व्योम xt_compat_flush_offsets(u_पूर्णांक8_t af);
पूर्णांक xt_compat_init_offsets(u8 af, अचिन्हित पूर्णांक number);
पूर्णांक xt_compat_calc_jump(u_पूर्णांक8_t af, अचिन्हित पूर्णांक offset);

पूर्णांक xt_compat_match_offset(स्थिर काष्ठा xt_match *match);
व्योम xt_compat_match_from_user(काष्ठा xt_entry_match *m, व्योम **dstptr,
			      अचिन्हित पूर्णांक *size);
पूर्णांक xt_compat_match_to_user(स्थिर काष्ठा xt_entry_match *m,
			    व्योम __user **dstptr, अचिन्हित पूर्णांक *size);

पूर्णांक xt_compat_target_offset(स्थिर काष्ठा xt_target *target);
व्योम xt_compat_target_from_user(काष्ठा xt_entry_target *t, व्योम **dstptr,
				अचिन्हित पूर्णांक *size);
पूर्णांक xt_compat_target_to_user(स्थिर काष्ठा xt_entry_target *t,
			     व्योम __user **dstptr, अचिन्हित पूर्णांक *size);
पूर्णांक xt_compat_check_entry_offsets(स्थिर व्योम *base, स्थिर अक्षर *elems,
				  अचिन्हित पूर्णांक target_offset,
				  अचिन्हित पूर्णांक next_offset);

#पूर्ण_अगर /* CONFIG_NETFILTER_XTABLES_COMPAT */
#पूर्ण_अगर /* _X_TABLES_H */
