<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#समावेश "main.h"

#समावेश <linux/byteorder/generic.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <uapi/linux/batadv_packet.h>

#समावेश "originator.h"
#समावेश "send.h"
#समावेश "tvlv.h"

/**
 * batadv_tvlv_handler_release() - release tvlv handler from lists and queue क्रम
 *  मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the tvlv
 */
अटल व्योम batadv_tvlv_handler_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_tvlv_handler *tvlv_handler;

	tvlv_handler = container_of(ref, काष्ठा batadv_tvlv_handler, refcount);
	kमुक्त_rcu(tvlv_handler, rcu);
पूर्ण

/**
 * batadv_tvlv_handler_put() - decrement the tvlv container refcounter and
 *  possibly release it
 * @tvlv_handler: the tvlv handler to मुक्त
 */
अटल व्योम batadv_tvlv_handler_put(काष्ठा batadv_tvlv_handler *tvlv_handler)
अणु
	kref_put(&tvlv_handler->refcount, batadv_tvlv_handler_release);
पूर्ण

/**
 * batadv_tvlv_handler_get() - retrieve tvlv handler from the tvlv handler list
 *  based on the provided type and version (both need to match)
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @type: tvlv handler type to look क्रम
 * @version: tvlv handler version to look क्रम
 *
 * Return: tvlv handler अगर found or शून्य otherwise.
 */
अटल काष्ठा batadv_tvlv_handler *
batadv_tvlv_handler_get(काष्ठा batadv_priv *bat_priv, u8 type, u8 version)
अणु
	काष्ठा batadv_tvlv_handler *tvlv_handler_पंचांगp, *tvlv_handler = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(tvlv_handler_पंचांगp,
				 &bat_priv->tvlv.handler_list, list) अणु
		अगर (tvlv_handler_पंचांगp->type != type)
			जारी;

		अगर (tvlv_handler_पंचांगp->version != version)
			जारी;

		अगर (!kref_get_unless_zero(&tvlv_handler_पंचांगp->refcount))
			जारी;

		tvlv_handler = tvlv_handler_पंचांगp;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस tvlv_handler;
पूर्ण

/**
 * batadv_tvlv_container_release() - release tvlv from lists and मुक्त
 * @ref: kref poपूर्णांकer of the tvlv
 */
अटल व्योम batadv_tvlv_container_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_tvlv_container *tvlv;

	tvlv = container_of(ref, काष्ठा batadv_tvlv_container, refcount);
	kमुक्त(tvlv);
पूर्ण

/**
 * batadv_tvlv_container_put() - decrement the tvlv container refcounter and
 *  possibly release it
 * @tvlv: the tvlv container to मुक्त
 */
अटल व्योम batadv_tvlv_container_put(काष्ठा batadv_tvlv_container *tvlv)
अणु
	kref_put(&tvlv->refcount, batadv_tvlv_container_release);
पूर्ण

/**
 * batadv_tvlv_container_get() - retrieve tvlv container from the tvlv container
 *  list based on the provided type and version (both need to match)
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @type: tvlv container type to look क्रम
 * @version: tvlv container version to look क्रम
 *
 * Has to be called with the appropriate locks being acquired
 * (tvlv.container_list_lock).
 *
 * Return: tvlv container अगर found or शून्य otherwise.
 */
अटल काष्ठा batadv_tvlv_container *
batadv_tvlv_container_get(काष्ठा batadv_priv *bat_priv, u8 type, u8 version)
अणु
	काष्ठा batadv_tvlv_container *tvlv_पंचांगp, *tvlv = शून्य;

	lockdep_निश्चित_held(&bat_priv->tvlv.container_list_lock);

	hlist_क्रम_each_entry(tvlv_पंचांगp, &bat_priv->tvlv.container_list, list) अणु
		अगर (tvlv_पंचांगp->tvlv_hdr.type != type)
			जारी;

		अगर (tvlv_पंचांगp->tvlv_hdr.version != version)
			जारी;

		kref_get(&tvlv_पंचांगp->refcount);
		tvlv = tvlv_पंचांगp;
		अवरोध;
	पूर्ण

	वापस tvlv;
पूर्ण

/**
 * batadv_tvlv_container_list_size() - calculate the size of the tvlv container
 *  list entries
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Has to be called with the appropriate locks being acquired
 * (tvlv.container_list_lock).
 *
 * Return: size of all currently रेजिस्टरed tvlv containers in bytes.
 */
अटल u16 batadv_tvlv_container_list_size(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_tvlv_container *tvlv;
	u16 tvlv_len = 0;

	lockdep_निश्चित_held(&bat_priv->tvlv.container_list_lock);

	hlist_क्रम_each_entry(tvlv, &bat_priv->tvlv.container_list, list) अणु
		tvlv_len += माप(काष्ठा batadv_tvlv_hdr);
		tvlv_len += ntohs(tvlv->tvlv_hdr.len);
	पूर्ण

	वापस tvlv_len;
पूर्ण

/**
 * batadv_tvlv_container_हटाओ() - हटाओ tvlv container from the tvlv
 *  container list
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tvlv: the to be हटाओd tvlv container
 *
 * Has to be called with the appropriate locks being acquired
 * (tvlv.container_list_lock).
 */
अटल व्योम batadv_tvlv_container_हटाओ(काष्ठा batadv_priv *bat_priv,
					 काष्ठा batadv_tvlv_container *tvlv)
अणु
	lockdep_निश्चित_held(&bat_priv->tvlv.container_list_lock);

	अगर (!tvlv)
		वापस;

	hlist_del(&tvlv->list);

	/* first call to decrement the counter, second call to मुक्त */
	batadv_tvlv_container_put(tvlv);
	batadv_tvlv_container_put(tvlv);
पूर्ण

/**
 * batadv_tvlv_container_unरेजिस्टर() - unरेजिस्टर tvlv container based on the
 *  provided type and version (both need to match)
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @type: tvlv container type to unरेजिस्टर
 * @version: tvlv container type to unरेजिस्टर
 */
व्योम batadv_tvlv_container_unरेजिस्टर(काष्ठा batadv_priv *bat_priv,
				      u8 type, u8 version)
अणु
	काष्ठा batadv_tvlv_container *tvlv;

	spin_lock_bh(&bat_priv->tvlv.container_list_lock);
	tvlv = batadv_tvlv_container_get(bat_priv, type, version);
	batadv_tvlv_container_हटाओ(bat_priv, tvlv);
	spin_unlock_bh(&bat_priv->tvlv.container_list_lock);
पूर्ण

/**
 * batadv_tvlv_container_रेजिस्टर() - रेजिस्टर tvlv type, version and content
 *  to be propagated with each (primary पूर्णांकerface) OGM
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @type: tvlv container type
 * @version: tvlv container version
 * @tvlv_value: tvlv container content
 * @tvlv_value_len: tvlv container content length
 *
 * If a container of the same type and version was alपढ़ोy रेजिस्टरed the new
 * content is going to replace the old one.
 */
व्योम batadv_tvlv_container_रेजिस्टर(काष्ठा batadv_priv *bat_priv,
				    u8 type, u8 version,
				    व्योम *tvlv_value, u16 tvlv_value_len)
अणु
	काष्ठा batadv_tvlv_container *tvlv_old, *tvlv_new;

	अगर (!tvlv_value)
		tvlv_value_len = 0;

	tvlv_new = kzalloc(माप(*tvlv_new) + tvlv_value_len, GFP_ATOMIC);
	अगर (!tvlv_new)
		वापस;

	tvlv_new->tvlv_hdr.version = version;
	tvlv_new->tvlv_hdr.type = type;
	tvlv_new->tvlv_hdr.len = htons(tvlv_value_len);

	स_नकल(tvlv_new + 1, tvlv_value, ntohs(tvlv_new->tvlv_hdr.len));
	INIT_HLIST_NODE(&tvlv_new->list);
	kref_init(&tvlv_new->refcount);

	spin_lock_bh(&bat_priv->tvlv.container_list_lock);
	tvlv_old = batadv_tvlv_container_get(bat_priv, type, version);
	batadv_tvlv_container_हटाओ(bat_priv, tvlv_old);

	kref_get(&tvlv_new->refcount);
	hlist_add_head(&tvlv_new->list, &bat_priv->tvlv.container_list);
	spin_unlock_bh(&bat_priv->tvlv.container_list_lock);

	/* करोn't वापस reference to new tvlv_container */
	batadv_tvlv_container_put(tvlv_new);
पूर्ण

/**
 * batadv_tvlv_पुनः_स्मृति_packet_buff() - पुनः_स्मृतिate packet buffer to accommodate
 *  requested packet size
 * @packet_buff: packet buffer
 * @packet_buff_len: packet buffer size
 * @min_packet_len: requested packet minimum size
 * @additional_packet_len: requested additional packet size on top of minimum
 *  size
 *
 * Return: true of the packet buffer could be changed to the requested size,
 * false otherwise.
 */
अटल bool batadv_tvlv_पुनः_स्मृति_packet_buff(अचिन्हित अक्षर **packet_buff,
					    पूर्णांक *packet_buff_len,
					    पूर्णांक min_packet_len,
					    पूर्णांक additional_packet_len)
अणु
	अचिन्हित अक्षर *new_buff;

	new_buff = kदो_स्मृति(min_packet_len + additional_packet_len, GFP_ATOMIC);

	/* keep old buffer अगर kदो_स्मृति should fail */
	अगर (!new_buff)
		वापस false;

	स_नकल(new_buff, *packet_buff, min_packet_len);
	kमुक्त(*packet_buff);
	*packet_buff = new_buff;
	*packet_buff_len = min_packet_len + additional_packet_len;

	वापस true;
पूर्ण

/**
 * batadv_tvlv_container_ogm_append() - append tvlv container content to given
 *  OGM packet buffer
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @packet_buff: ogm packet buffer
 * @packet_buff_len: ogm packet buffer size including ogm header and tvlv
 *  content
 * @packet_min_len: ogm header size to be preserved क्रम the OGM itself
 *
 * The ogm packet might be enlarged or shrunk depending on the current size
 * and the size of the to-be-appended tvlv containers.
 *
 * Return: size of all appended tvlv containers in bytes.
 */
u16 batadv_tvlv_container_ogm_append(काष्ठा batadv_priv *bat_priv,
				     अचिन्हित अक्षर **packet_buff,
				     पूर्णांक *packet_buff_len, पूर्णांक packet_min_len)
अणु
	काष्ठा batadv_tvlv_container *tvlv;
	काष्ठा batadv_tvlv_hdr *tvlv_hdr;
	u16 tvlv_value_len;
	व्योम *tvlv_value;
	bool ret;

	spin_lock_bh(&bat_priv->tvlv.container_list_lock);
	tvlv_value_len = batadv_tvlv_container_list_size(bat_priv);

	ret = batadv_tvlv_पुनः_स्मृति_packet_buff(packet_buff, packet_buff_len,
					      packet_min_len, tvlv_value_len);

	अगर (!ret)
		जाओ end;

	अगर (!tvlv_value_len)
		जाओ end;

	tvlv_value = (*packet_buff) + packet_min_len;

	hlist_क्रम_each_entry(tvlv, &bat_priv->tvlv.container_list, list) अणु
		tvlv_hdr = tvlv_value;
		tvlv_hdr->type = tvlv->tvlv_hdr.type;
		tvlv_hdr->version = tvlv->tvlv_hdr.version;
		tvlv_hdr->len = tvlv->tvlv_hdr.len;
		tvlv_value = tvlv_hdr + 1;
		स_नकल(tvlv_value, tvlv + 1, ntohs(tvlv->tvlv_hdr.len));
		tvlv_value = (u8 *)tvlv_value + ntohs(tvlv->tvlv_hdr.len);
	पूर्ण

end:
	spin_unlock_bh(&bat_priv->tvlv.container_list_lock);
	वापस tvlv_value_len;
पूर्ण

/**
 * batadv_tvlv_call_handler() - parse the given tvlv buffer to call the
 *  appropriate handlers
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tvlv_handler: tvlv callback function handling the tvlv content
 * @ogm_source: flag indicating whether the tvlv is an ogm or a unicast packet
 * @orig_node: orig node emitting the ogm packet
 * @src: source mac address of the unicast packet
 * @dst: destination mac address of the unicast packet
 * @tvlv_value: tvlv content
 * @tvlv_value_len: tvlv content length
 *
 * Return: success अगर the handler was not found or the वापस value of the
 * handler callback.
 */
अटल पूर्णांक batadv_tvlv_call_handler(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_tvlv_handler *tvlv_handler,
				    bool ogm_source,
				    काष्ठा batadv_orig_node *orig_node,
				    u8 *src, u8 *dst,
				    व्योम *tvlv_value, u16 tvlv_value_len)
अणु
	अगर (!tvlv_handler)
		वापस NET_RX_SUCCESS;

	अगर (ogm_source) अणु
		अगर (!tvlv_handler->ogm_handler)
			वापस NET_RX_SUCCESS;

		अगर (!orig_node)
			वापस NET_RX_SUCCESS;

		tvlv_handler->ogm_handler(bat_priv, orig_node,
					  BATADV_NO_FLAGS,
					  tvlv_value, tvlv_value_len);
		tvlv_handler->flags |= BATADV_TVLV_HANDLER_OGM_CALLED;
	पूर्ण अन्यथा अणु
		अगर (!src)
			वापस NET_RX_SUCCESS;

		अगर (!dst)
			वापस NET_RX_SUCCESS;

		अगर (!tvlv_handler->unicast_handler)
			वापस NET_RX_SUCCESS;

		वापस tvlv_handler->unicast_handler(bat_priv, src,
						     dst, tvlv_value,
						     tvlv_value_len);
	पूर्ण

	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * batadv_tvlv_containers_process() - parse the given tvlv buffer to call the
 *  appropriate handlers
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ogm_source: flag indicating whether the tvlv is an ogm or a unicast packet
 * @orig_node: orig node emitting the ogm packet
 * @src: source mac address of the unicast packet
 * @dst: destination mac address of the unicast packet
 * @tvlv_value: tvlv content
 * @tvlv_value_len: tvlv content length
 *
 * Return: success when processing an OGM or the वापस value of all called
 * handler callbacks.
 */
पूर्णांक batadv_tvlv_containers_process(काष्ठा batadv_priv *bat_priv,
				   bool ogm_source,
				   काष्ठा batadv_orig_node *orig_node,
				   u8 *src, u8 *dst,
				   व्योम *tvlv_value, u16 tvlv_value_len)
अणु
	काष्ठा batadv_tvlv_handler *tvlv_handler;
	काष्ठा batadv_tvlv_hdr *tvlv_hdr;
	u16 tvlv_value_cont_len;
	u8 cअगरnotfound = BATADV_TVLV_HANDLER_OGM_CIFNOTFND;
	पूर्णांक ret = NET_RX_SUCCESS;

	जबतक (tvlv_value_len >= माप(*tvlv_hdr)) अणु
		tvlv_hdr = tvlv_value;
		tvlv_value_cont_len = ntohs(tvlv_hdr->len);
		tvlv_value = tvlv_hdr + 1;
		tvlv_value_len -= माप(*tvlv_hdr);

		अगर (tvlv_value_cont_len > tvlv_value_len)
			अवरोध;

		tvlv_handler = batadv_tvlv_handler_get(bat_priv,
						       tvlv_hdr->type,
						       tvlv_hdr->version);

		ret |= batadv_tvlv_call_handler(bat_priv, tvlv_handler,
						ogm_source, orig_node,
						src, dst, tvlv_value,
						tvlv_value_cont_len);
		अगर (tvlv_handler)
			batadv_tvlv_handler_put(tvlv_handler);
		tvlv_value = (u8 *)tvlv_value + tvlv_value_cont_len;
		tvlv_value_len -= tvlv_value_cont_len;
	पूर्ण

	अगर (!ogm_source)
		वापस ret;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(tvlv_handler,
				 &bat_priv->tvlv.handler_list, list) अणु
		अगर ((tvlv_handler->flags & BATADV_TVLV_HANDLER_OGM_CIFNOTFND) &&
		    !(tvlv_handler->flags & BATADV_TVLV_HANDLER_OGM_CALLED))
			tvlv_handler->ogm_handler(bat_priv, orig_node,
						  cअगरnotfound, शून्य, 0);

		tvlv_handler->flags &= ~BATADV_TVLV_HANDLER_OGM_CALLED;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * batadv_tvlv_ogm_receive() - process an incoming ogm and call the appropriate
 *  handlers
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @batadv_ogm_packet: ogm packet containing the tvlv containers
 * @orig_node: orig node emitting the ogm packet
 */
व्योम batadv_tvlv_ogm_receive(काष्ठा batadv_priv *bat_priv,
			     काष्ठा batadv_ogm_packet *batadv_ogm_packet,
			     काष्ठा batadv_orig_node *orig_node)
अणु
	व्योम *tvlv_value;
	u16 tvlv_value_len;

	अगर (!batadv_ogm_packet)
		वापस;

	tvlv_value_len = ntohs(batadv_ogm_packet->tvlv_len);
	अगर (!tvlv_value_len)
		वापस;

	tvlv_value = batadv_ogm_packet + 1;

	batadv_tvlv_containers_process(bat_priv, true, orig_node, शून्य, शून्य,
				       tvlv_value, tvlv_value_len);
पूर्ण

/**
 * batadv_tvlv_handler_रेजिस्टर() - रेजिस्टर tvlv handler based on the provided
 *  type and version (both need to match) क्रम ogm tvlv payload and/or unicast
 *  payload
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @optr: ogm tvlv handler callback function. This function receives the orig
 *  node, flags and the tvlv content as argument to process.
 * @uptr: unicast tvlv handler callback function. This function receives the
 *  source & destination of the unicast packet as well as the tvlv content
 *  to process.
 * @type: tvlv handler type to be रेजिस्टरed
 * @version: tvlv handler version to be रेजिस्टरed
 * @flags: flags to enable or disable TVLV API behavior
 */
व्योम batadv_tvlv_handler_रेजिस्टर(काष्ठा batadv_priv *bat_priv,
				  व्योम (*optr)(काष्ठा batadv_priv *bat_priv,
					       काष्ठा batadv_orig_node *orig,
					       u8 flags,
					       व्योम *tvlv_value,
					       u16 tvlv_value_len),
				  पूर्णांक (*uptr)(काष्ठा batadv_priv *bat_priv,
					      u8 *src, u8 *dst,
					      व्योम *tvlv_value,
					      u16 tvlv_value_len),
				  u8 type, u8 version, u8 flags)
अणु
	काष्ठा batadv_tvlv_handler *tvlv_handler;

	spin_lock_bh(&bat_priv->tvlv.handler_list_lock);

	tvlv_handler = batadv_tvlv_handler_get(bat_priv, type, version);
	अगर (tvlv_handler) अणु
		spin_unlock_bh(&bat_priv->tvlv.handler_list_lock);
		batadv_tvlv_handler_put(tvlv_handler);
		वापस;
	पूर्ण

	tvlv_handler = kzalloc(माप(*tvlv_handler), GFP_ATOMIC);
	अगर (!tvlv_handler) अणु
		spin_unlock_bh(&bat_priv->tvlv.handler_list_lock);
		वापस;
	पूर्ण

	tvlv_handler->ogm_handler = optr;
	tvlv_handler->unicast_handler = uptr;
	tvlv_handler->type = type;
	tvlv_handler->version = version;
	tvlv_handler->flags = flags;
	kref_init(&tvlv_handler->refcount);
	INIT_HLIST_NODE(&tvlv_handler->list);

	kref_get(&tvlv_handler->refcount);
	hlist_add_head_rcu(&tvlv_handler->list, &bat_priv->tvlv.handler_list);
	spin_unlock_bh(&bat_priv->tvlv.handler_list_lock);

	/* करोn't वापस reference to new tvlv_handler */
	batadv_tvlv_handler_put(tvlv_handler);
पूर्ण

/**
 * batadv_tvlv_handler_unरेजिस्टर() - unरेजिस्टर tvlv handler based on the
 *  provided type and version (both need to match)
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @type: tvlv handler type to be unरेजिस्टरed
 * @version: tvlv handler version to be unरेजिस्टरed
 */
व्योम batadv_tvlv_handler_unरेजिस्टर(काष्ठा batadv_priv *bat_priv,
				    u8 type, u8 version)
अणु
	काष्ठा batadv_tvlv_handler *tvlv_handler;

	tvlv_handler = batadv_tvlv_handler_get(bat_priv, type, version);
	अगर (!tvlv_handler)
		वापस;

	batadv_tvlv_handler_put(tvlv_handler);
	spin_lock_bh(&bat_priv->tvlv.handler_list_lock);
	hlist_del_rcu(&tvlv_handler->list);
	spin_unlock_bh(&bat_priv->tvlv.handler_list_lock);
	batadv_tvlv_handler_put(tvlv_handler);
पूर्ण

/**
 * batadv_tvlv_unicast_send() - send a unicast packet with tvlv payload to the
 *  specअगरied host
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @src: source mac address of the unicast packet
 * @dst: destination mac address of the unicast packet
 * @type: tvlv type
 * @version: tvlv version
 * @tvlv_value: tvlv content
 * @tvlv_value_len: tvlv content length
 */
व्योम batadv_tvlv_unicast_send(काष्ठा batadv_priv *bat_priv, u8 *src,
			      u8 *dst, u8 type, u8 version,
			      व्योम *tvlv_value, u16 tvlv_value_len)
अणु
	काष्ठा batadv_unicast_tvlv_packet *unicast_tvlv_packet;
	काष्ठा batadv_tvlv_hdr *tvlv_hdr;
	काष्ठा batadv_orig_node *orig_node;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *tvlv_buff;
	अचिन्हित पूर्णांक tvlv_len;
	sमाप_प्रकार hdr_len = माप(*unicast_tvlv_packet);

	orig_node = batadv_orig_hash_find(bat_priv, dst);
	अगर (!orig_node)
		वापस;

	tvlv_len = माप(*tvlv_hdr) + tvlv_value_len;

	skb = netdev_alloc_skb_ip_align(शून्य, ETH_HLEN + hdr_len + tvlv_len);
	अगर (!skb)
		जाओ out;

	skb->priority = TC_PRIO_CONTROL;
	skb_reserve(skb, ETH_HLEN);
	tvlv_buff = skb_put(skb, माप(*unicast_tvlv_packet) + tvlv_len);
	unicast_tvlv_packet = (काष्ठा batadv_unicast_tvlv_packet *)tvlv_buff;
	unicast_tvlv_packet->packet_type = BATADV_UNICAST_TVLV;
	unicast_tvlv_packet->version = BATADV_COMPAT_VERSION;
	unicast_tvlv_packet->ttl = BATADV_TTL;
	unicast_tvlv_packet->reserved = 0;
	unicast_tvlv_packet->tvlv_len = htons(tvlv_len);
	unicast_tvlv_packet->align = 0;
	ether_addr_copy(unicast_tvlv_packet->src, src);
	ether_addr_copy(unicast_tvlv_packet->dst, dst);

	tvlv_buff = (अचिन्हित अक्षर *)(unicast_tvlv_packet + 1);
	tvlv_hdr = (काष्ठा batadv_tvlv_hdr *)tvlv_buff;
	tvlv_hdr->version = version;
	tvlv_hdr->type = type;
	tvlv_hdr->len = htons(tvlv_value_len);
	tvlv_buff += माप(*tvlv_hdr);
	स_नकल(tvlv_buff, tvlv_value, tvlv_value_len);

	batadv_send_skb_to_orig(skb, orig_node, शून्य);
out:
	batadv_orig_node_put(orig_node);
पूर्ण
