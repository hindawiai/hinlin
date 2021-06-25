<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/aपंचांगmpc.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>

#समावेश "mpoa_caches.h"
#समावेश "mpc.h"

/*
 * mpoa_caches.c: Implementation of ingress and egress cache
 * handling functions
 */

#अगर 0
#घोषणा dprपूर्णांकk(क्रमmat, args...)					\
	prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __खाता__, ##args)  /* debug */
#अन्यथा
#घोषणा dprपूर्णांकk(क्रमmat, args...)					\
	करो अणु अगर (0)							\
		prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __खाता__, ##args);\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर 0
#घोषणा ddprपूर्णांकk(क्रमmat, args...)					\
	prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __खाता__, ##args)  /* debug */
#अन्यथा
#घोषणा ddprपूर्णांकk(क्रमmat, args...)					\
	करो अणु अगर (0)							\
		prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __खाता__, ##args);\
	पूर्ण जबतक (0)
#पूर्ण_अगर

अटल in_cache_entry *in_cache_get(__be32 dst_ip,
				    काष्ठा mpoa_client *client)
अणु
	in_cache_entry *entry;

	पढ़ो_lock_bh(&client->ingress_lock);
	entry = client->in_cache;
	जबतक (entry != शून्य) अणु
		अगर (entry->ctrl_info.in_dst_ip == dst_ip) अणु
			refcount_inc(&entry->use);
			पढ़ो_unlock_bh(&client->ingress_lock);
			वापस entry;
		पूर्ण
		entry = entry->next;
	पूर्ण
	पढ़ो_unlock_bh(&client->ingress_lock);

	वापस शून्य;
पूर्ण

अटल in_cache_entry *in_cache_get_with_mask(__be32 dst_ip,
					      काष्ठा mpoa_client *client,
					      __be32 mask)
अणु
	in_cache_entry *entry;

	पढ़ो_lock_bh(&client->ingress_lock);
	entry = client->in_cache;
	जबतक (entry != शून्य) अणु
		अगर ((entry->ctrl_info.in_dst_ip & mask) == (dst_ip & mask)) अणु
			refcount_inc(&entry->use);
			पढ़ो_unlock_bh(&client->ingress_lock);
			वापस entry;
		पूर्ण
		entry = entry->next;
	पूर्ण
	पढ़ो_unlock_bh(&client->ingress_lock);

	वापस शून्य;

पूर्ण

अटल in_cache_entry *in_cache_get_by_vcc(काष्ठा aपंचांग_vcc *vcc,
					   काष्ठा mpoa_client *client)
अणु
	in_cache_entry *entry;

	पढ़ो_lock_bh(&client->ingress_lock);
	entry = client->in_cache;
	जबतक (entry != शून्य) अणु
		अगर (entry->लघुcut == vcc) अणु
			refcount_inc(&entry->use);
			पढ़ो_unlock_bh(&client->ingress_lock);
			वापस entry;
		पूर्ण
		entry = entry->next;
	पूर्ण
	पढ़ो_unlock_bh(&client->ingress_lock);

	वापस शून्य;
पूर्ण

अटल in_cache_entry *in_cache_add_entry(__be32 dst_ip,
					  काष्ठा mpoa_client *client)
अणु
	in_cache_entry *entry = kzalloc(माप(in_cache_entry), GFP_KERNEL);

	अगर (entry == शून्य) अणु
		pr_info("mpoa: mpoa_caches.c: new_in_cache_entry: out of memory\n");
		वापस शून्य;
	पूर्ण

	dprपूर्णांकk("adding an ingress entry, ip = %pI4\n", &dst_ip);

	refcount_set(&entry->use, 1);
	dprपूर्णांकk("new_in_cache_entry: about to lock\n");
	ग_लिखो_lock_bh(&client->ingress_lock);
	entry->next = client->in_cache;
	entry->prev = शून्य;
	अगर (client->in_cache != शून्य)
		client->in_cache->prev = entry;
	client->in_cache = entry;

	स_नकल(entry->MPS_ctrl_ATM_addr, client->mps_ctrl_addr, ATM_ESA_LEN);
	entry->ctrl_info.in_dst_ip = dst_ip;
	entry->समय = kसमय_get_seconds();
	entry->retry_समय = client->parameters.mpc_p4;
	entry->count = 1;
	entry->entry_state = INGRESS_INVALID;
	entry->ctrl_info.holding_समय = HOLDING_TIME_DEFAULT;
	refcount_inc(&entry->use);

	ग_लिखो_unlock_bh(&client->ingress_lock);
	dprपूर्णांकk("new_in_cache_entry: unlocked\n");

	वापस entry;
पूर्ण

अटल पूर्णांक cache_hit(in_cache_entry *entry, काष्ठा mpoa_client *mpc)
अणु
	काष्ठा aपंचांग_mpoa_qos *qos;
	काष्ठा k_message msg;

	entry->count++;
	अगर (entry->entry_state == INGRESS_RESOLVED && entry->लघुcut != शून्य)
		वापस OPEN;

	अगर (entry->entry_state == INGRESS_REFRESHING) अणु
		अगर (entry->count > mpc->parameters.mpc_p1) अणु
			msg.type = SND_MPOA_RES_RQST;
			msg.content.in_info = entry->ctrl_info;
			स_नकल(msg.MPS_ctrl, mpc->mps_ctrl_addr, ATM_ESA_LEN);
			qos = aपंचांग_mpoa_search_qos(entry->ctrl_info.in_dst_ip);
			अगर (qos != शून्य)
				msg.qos = qos->qos;
			msg_to_mpoad(&msg, mpc);
			entry->reply_रुको = kसमय_get_seconds();
			entry->entry_state = INGRESS_RESOLVING;
		पूर्ण
		अगर (entry->लघुcut != शून्य)
			वापस OPEN;
		वापस CLOSED;
	पूर्ण

	अगर (entry->entry_state == INGRESS_RESOLVING && entry->लघुcut != शून्य)
		वापस OPEN;

	अगर (entry->count > mpc->parameters.mpc_p1 &&
	    entry->entry_state == INGRESS_INVALID) अणु
		dprपूर्णांकk("(%s) threshold exceeded for ip %pI4, sending MPOA res req\n",
			mpc->dev->name, &entry->ctrl_info.in_dst_ip);
		entry->entry_state = INGRESS_RESOLVING;
		msg.type = SND_MPOA_RES_RQST;
		स_नकल(msg.MPS_ctrl, mpc->mps_ctrl_addr, ATM_ESA_LEN);
		msg.content.in_info = entry->ctrl_info;
		qos = aपंचांग_mpoa_search_qos(entry->ctrl_info.in_dst_ip);
		अगर (qos != शून्य)
			msg.qos = qos->qos;
		msg_to_mpoad(&msg, mpc);
		entry->reply_रुको = kसमय_get_seconds();
	पूर्ण

	वापस CLOSED;
पूर्ण

अटल व्योम in_cache_put(in_cache_entry *entry)
अणु
	अगर (refcount_dec_and_test(&entry->use)) अणु
		kमुक्त_sensitive(entry);
	पूर्ण
पूर्ण

/*
 * This should be called with ग_लिखो lock on
 */
अटल व्योम in_cache_हटाओ_entry(in_cache_entry *entry,
				  काष्ठा mpoa_client *client)
अणु
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा k_message msg;

	vcc = entry->लघुcut;
	dprपूर्णांकk("removing an ingress entry, ip = %pI4\n",
		&entry->ctrl_info.in_dst_ip);

	अगर (entry->prev != शून्य)
		entry->prev->next = entry->next;
	अन्यथा
		client->in_cache = entry->next;
	अगर (entry->next != शून्य)
		entry->next->prev = entry->prev;
	client->in_ops->put(entry);
	अगर (client->in_cache == शून्य && client->eg_cache == शून्य) अणु
		msg.type = STOP_KEEP_ALIVE_SM;
		msg_to_mpoad(&msg, client);
	पूर्ण

	/* Check अगर the egress side still uses this VCC */
	अगर (vcc != शून्य) अणु
		eg_cache_entry *eg_entry = client->eg_ops->get_by_vcc(vcc,
								      client);
		अगर (eg_entry != शून्य) अणु
			client->eg_ops->put(eg_entry);
			वापस;
		पूर्ण
		vcc_release_async(vcc, -EPIPE);
	पूर्ण
पूर्ण

/* Call this every MPC-p2 seconds... Not exactly correct solution,
   but an easy one... */
अटल व्योम clear_count_and_expired(काष्ठा mpoa_client *client)
अणु
	in_cache_entry *entry, *next_entry;
	समय64_t now;

	now = kसमय_get_seconds();

	ग_लिखो_lock_bh(&client->ingress_lock);
	entry = client->in_cache;
	जबतक (entry != शून्य) अणु
		entry->count = 0;
		next_entry = entry->next;
		अगर ((now - entry->समय) > entry->ctrl_info.holding_समय) अणु
			dprपूर्णांकk("holding time expired, ip = %pI4\n",
				&entry->ctrl_info.in_dst_ip);
			client->in_ops->हटाओ_entry(entry, client);
		पूर्ण
		entry = next_entry;
	पूर्ण
	ग_लिखो_unlock_bh(&client->ingress_lock);
पूर्ण

/* Call this every MPC-p4 seconds. */
अटल व्योम check_resolving_entries(काष्ठा mpoa_client *client)
अणु

	काष्ठा aपंचांग_mpoa_qos *qos;
	in_cache_entry *entry;
	समय64_t now;
	काष्ठा k_message msg;

	now = kसमय_get_seconds();

	पढ़ो_lock_bh(&client->ingress_lock);
	entry = client->in_cache;
	जबतक (entry != शून्य) अणु
		अगर (entry->entry_state == INGRESS_RESOLVING) अणु

			अगर ((now - entry->hold_करोwn)
					< client->parameters.mpc_p6) अणु
				entry = entry->next;	/* Entry in hold करोwn */
				जारी;
			पूर्ण
			अगर ((now - entry->reply_रुको) > entry->retry_समय) अणु
				entry->retry_समय = MPC_C1 * (entry->retry_समय);
				/*
				 * Retry समय maximum exceeded,
				 * put entry in hold करोwn.
				 */
				अगर (entry->retry_समय > client->parameters.mpc_p5) अणु
					entry->hold_करोwn = kसमय_get_seconds();
					entry->retry_समय = client->parameters.mpc_p4;
					entry = entry->next;
					जारी;
				पूर्ण
				/* Ask daemon to send a resolution request. */
				स_रखो(&entry->hold_करोwn, 0, माप(समय64_t));
				msg.type = SND_MPOA_RES_RTRY;
				स_नकल(msg.MPS_ctrl, client->mps_ctrl_addr, ATM_ESA_LEN);
				msg.content.in_info = entry->ctrl_info;
				qos = aपंचांग_mpoa_search_qos(entry->ctrl_info.in_dst_ip);
				अगर (qos != शून्य)
					msg.qos = qos->qos;
				msg_to_mpoad(&msg, client);
				entry->reply_रुको = kसमय_get_seconds();
			पूर्ण
		पूर्ण
		entry = entry->next;
	पूर्ण
	पढ़ो_unlock_bh(&client->ingress_lock);
पूर्ण

/* Call this every MPC-p5 seconds. */
अटल व्योम refresh_entries(काष्ठा mpoa_client *client)
अणु
	समय64_t now;
	काष्ठा in_cache_entry *entry = client->in_cache;

	ddprपूर्णांकk("refresh_entries\n");
	now = kसमय_get_seconds();

	पढ़ो_lock_bh(&client->ingress_lock);
	जबतक (entry != शून्य) अणु
		अगर (entry->entry_state == INGRESS_RESOLVED) अणु
			अगर (!(entry->refresh_समय))
				entry->refresh_समय = (2 * (entry->ctrl_info.holding_समय))/3;
			अगर ((now - entry->reply_रुको) >
			    entry->refresh_समय) अणु
				dprपूर्णांकk("refreshing an entry.\n");
				entry->entry_state = INGRESS_REFRESHING;

			पूर्ण
		पूर्ण
		entry = entry->next;
	पूर्ण
	पढ़ो_unlock_bh(&client->ingress_lock);
पूर्ण

अटल व्योम in_destroy_cache(काष्ठा mpoa_client *mpc)
अणु
	ग_लिखो_lock_irq(&mpc->ingress_lock);
	जबतक (mpc->in_cache != शून्य)
		mpc->in_ops->हटाओ_entry(mpc->in_cache, mpc);
	ग_लिखो_unlock_irq(&mpc->ingress_lock);
पूर्ण

अटल eg_cache_entry *eg_cache_get_by_cache_id(__be32 cache_id,
						काष्ठा mpoa_client *mpc)
अणु
	eg_cache_entry *entry;

	पढ़ो_lock_irq(&mpc->egress_lock);
	entry = mpc->eg_cache;
	जबतक (entry != शून्य) अणु
		अगर (entry->ctrl_info.cache_id == cache_id) अणु
			refcount_inc(&entry->use);
			पढ़ो_unlock_irq(&mpc->egress_lock);
			वापस entry;
		पूर्ण
		entry = entry->next;
	पूर्ण
	पढ़ो_unlock_irq(&mpc->egress_lock);

	वापस शून्य;
पूर्ण

/* This can be called from any context since it saves CPU flags */
अटल eg_cache_entry *eg_cache_get_by_tag(__be32 tag, काष्ठा mpoa_client *mpc)
अणु
	अचिन्हित दीर्घ flags;
	eg_cache_entry *entry;

	पढ़ो_lock_irqsave(&mpc->egress_lock, flags);
	entry = mpc->eg_cache;
	जबतक (entry != शून्य) अणु
		अगर (entry->ctrl_info.tag == tag) अणु
			refcount_inc(&entry->use);
			पढ़ो_unlock_irqrestore(&mpc->egress_lock, flags);
			वापस entry;
		पूर्ण
		entry = entry->next;
	पूर्ण
	पढ़ो_unlock_irqrestore(&mpc->egress_lock, flags);

	वापस शून्य;
पूर्ण

/* This can be called from any context since it saves CPU flags */
अटल eg_cache_entry *eg_cache_get_by_vcc(काष्ठा aपंचांग_vcc *vcc,
					   काष्ठा mpoa_client *mpc)
अणु
	अचिन्हित दीर्घ flags;
	eg_cache_entry *entry;

	पढ़ो_lock_irqsave(&mpc->egress_lock, flags);
	entry = mpc->eg_cache;
	जबतक (entry != शून्य) अणु
		अगर (entry->लघुcut == vcc) अणु
			refcount_inc(&entry->use);
			पढ़ो_unlock_irqrestore(&mpc->egress_lock, flags);
			वापस entry;
		पूर्ण
		entry = entry->next;
	पूर्ण
	पढ़ो_unlock_irqrestore(&mpc->egress_lock, flags);

	वापस शून्य;
पूर्ण

अटल eg_cache_entry *eg_cache_get_by_src_ip(__be32 ipaddr,
					      काष्ठा mpoa_client *mpc)
अणु
	eg_cache_entry *entry;

	पढ़ो_lock_irq(&mpc->egress_lock);
	entry = mpc->eg_cache;
	जबतक (entry != शून्य) अणु
		अगर (entry->latest_ip_addr == ipaddr) अणु
			refcount_inc(&entry->use);
			पढ़ो_unlock_irq(&mpc->egress_lock);
			वापस entry;
		पूर्ण
		entry = entry->next;
	पूर्ण
	पढ़ो_unlock_irq(&mpc->egress_lock);

	वापस शून्य;
पूर्ण

अटल व्योम eg_cache_put(eg_cache_entry *entry)
अणु
	अगर (refcount_dec_and_test(&entry->use)) अणु
		kमुक्त_sensitive(entry);
	पूर्ण
पूर्ण

/*
 * This should be called with ग_लिखो lock on
 */
अटल व्योम eg_cache_हटाओ_entry(eg_cache_entry *entry,
				  काष्ठा mpoa_client *client)
अणु
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा k_message msg;

	vcc = entry->लघुcut;
	dprपूर्णांकk("removing an egress entry.\n");
	अगर (entry->prev != शून्य)
		entry->prev->next = entry->next;
	अन्यथा
		client->eg_cache = entry->next;
	अगर (entry->next != शून्य)
		entry->next->prev = entry->prev;
	client->eg_ops->put(entry);
	अगर (client->in_cache == शून्य && client->eg_cache == शून्य) अणु
		msg.type = STOP_KEEP_ALIVE_SM;
		msg_to_mpoad(&msg, client);
	पूर्ण

	/* Check अगर the ingress side still uses this VCC */
	अगर (vcc != शून्य) अणु
		in_cache_entry *in_entry = client->in_ops->get_by_vcc(vcc, client);
		अगर (in_entry != शून्य) अणु
			client->in_ops->put(in_entry);
			वापस;
		पूर्ण
		vcc_release_async(vcc, -EPIPE);
	पूर्ण
पूर्ण

अटल eg_cache_entry *eg_cache_add_entry(काष्ठा k_message *msg,
					  काष्ठा mpoa_client *client)
अणु
	eg_cache_entry *entry = kzalloc(माप(eg_cache_entry), GFP_KERNEL);

	अगर (entry == शून्य) अणु
		pr_info("out of memory\n");
		वापस शून्य;
	पूर्ण

	dprपूर्णांकk("adding an egress entry, ip = %pI4, this should be our IP\n",
		&msg->content.eg_info.eg_dst_ip);

	refcount_set(&entry->use, 1);
	dprपूर्णांकk("new_eg_cache_entry: about to lock\n");
	ग_लिखो_lock_irq(&client->egress_lock);
	entry->next = client->eg_cache;
	entry->prev = शून्य;
	अगर (client->eg_cache != शून्य)
		client->eg_cache->prev = entry;
	client->eg_cache = entry;

	स_नकल(entry->MPS_ctrl_ATM_addr, client->mps_ctrl_addr, ATM_ESA_LEN);
	entry->ctrl_info = msg->content.eg_info;
	entry->समय = kसमय_get_seconds();
	entry->entry_state = EGRESS_RESOLVED;
	dprपूर्णांकk("new_eg_cache_entry cache_id %u\n",
		ntohl(entry->ctrl_info.cache_id));
	dprपूर्णांकk("mps_ip = %pI4\n", &entry->ctrl_info.mps_ip);
	refcount_inc(&entry->use);

	ग_लिखो_unlock_irq(&client->egress_lock);
	dprपूर्णांकk("new_eg_cache_entry: unlocked\n");

	वापस entry;
पूर्ण

अटल व्योम update_eg_cache_entry(eg_cache_entry *entry, uपूर्णांक16_t holding_समय)
अणु
	entry->समय = kसमय_get_seconds();
	entry->entry_state = EGRESS_RESOLVED;
	entry->ctrl_info.holding_समय = holding_समय;
पूर्ण

अटल व्योम clear_expired(काष्ठा mpoa_client *client)
अणु
	eg_cache_entry *entry, *next_entry;
	समय64_t now;
	काष्ठा k_message msg;

	now = kसमय_get_seconds();

	ग_लिखो_lock_irq(&client->egress_lock);
	entry = client->eg_cache;
	जबतक (entry != शून्य) अणु
		next_entry = entry->next;
		अगर ((now - entry->समय) > entry->ctrl_info.holding_समय) अणु
			msg.type = SND_EGRESS_PURGE;
			msg.content.eg_info = entry->ctrl_info;
			dprपूर्णांकk("egress_cache: holding time expired, cache_id = %u.\n",
				ntohl(entry->ctrl_info.cache_id));
			msg_to_mpoad(&msg, client);
			client->eg_ops->हटाओ_entry(entry, client);
		पूर्ण
		entry = next_entry;
	पूर्ण
	ग_लिखो_unlock_irq(&client->egress_lock);
पूर्ण

अटल व्योम eg_destroy_cache(काष्ठा mpoa_client *mpc)
अणु
	ग_लिखो_lock_irq(&mpc->egress_lock);
	जबतक (mpc->eg_cache != शून्य)
		mpc->eg_ops->हटाओ_entry(mpc->eg_cache, mpc);
	ग_लिखो_unlock_irq(&mpc->egress_lock);
पूर्ण


अटल स्थिर काष्ठा in_cache_ops ingress_ops = अणु
	.add_entry = in_cache_add_entry,
	.get = in_cache_get,
	.get_with_mask = in_cache_get_with_mask,
	.get_by_vcc = in_cache_get_by_vcc,
	.put = in_cache_put,
	.हटाओ_entry = in_cache_हटाओ_entry,
	.cache_hit = cache_hit,
	.clear_count = clear_count_and_expired,
	.check_resolving = check_resolving_entries,
	.refresh = refresh_entries,
	.destroy_cache = in_destroy_cache
पूर्ण;

अटल स्थिर काष्ठा eg_cache_ops egress_ops = अणु
	.add_entry = eg_cache_add_entry,
	.get_by_cache_id = eg_cache_get_by_cache_id,
	.get_by_tag = eg_cache_get_by_tag,
	.get_by_vcc = eg_cache_get_by_vcc,
	.get_by_src_ip = eg_cache_get_by_src_ip,
	.put = eg_cache_put,
	.हटाओ_entry = eg_cache_हटाओ_entry,
	.update = update_eg_cache_entry,
	.clear_expired = clear_expired,
	.destroy_cache = eg_destroy_cache
पूर्ण;

व्योम aपंचांग_mpoa_init_cache(काष्ठा mpoa_client *mpc)
अणु
	mpc->in_ops = &ingress_ops;
	mpc->eg_ops = &egress_ops;
पूर्ण
