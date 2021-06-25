<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	History
 *	03-01-2007	Added क्रमwarding क्रम x.25	Andrew Hendry
 */

#घोषणा pr_fmt(fmt) "X25: " fmt

#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <net/x25.h>

LIST_HEAD(x25_क्रमward_list);
DEFINE_RWLOCK(x25_क्रमward_list_lock);

पूर्णांक x25_क्रमward_call(काष्ठा x25_address *dest_addr, काष्ठा x25_neigh *from,
			काष्ठा sk_buff *skb, पूर्णांक lci)
अणु
	काष्ठा x25_route *rt;
	काष्ठा x25_neigh *neigh_new = शून्य;
	काष्ठा list_head *entry;
	काष्ठा x25_क्रमward *x25_frwd, *new_frwd;
	काष्ठा sk_buff *skbn;
	लघु same_lci = 0;
	पूर्णांक rc = 0;

	अगर ((rt = x25_get_route(dest_addr)) == शून्य)
		जाओ out_no_route;

	अगर ((neigh_new = x25_get_neigh(rt->dev)) == शून्य) अणु
		/* This shouldn't happen, अगर it occurs somehow
		 * करो something sensible
		 */
		जाओ out_put_route;
	पूर्ण

	/* Aव्योम a loop. This is the normal निकास path क्रम a
	 * प्रणाली with only one x.25 अगरace and शेष route
	 */
	अगर (rt->dev == from->dev) अणु
		जाओ out_put_nb;
	पूर्ण

	/* Remote end sending a call request on an alपढ़ोy
	 * established LCI? It shouldn't happen, just in हाल..
	 */
	पढ़ो_lock_bh(&x25_क्रमward_list_lock);
	list_क्रम_each(entry, &x25_क्रमward_list) अणु
		x25_frwd = list_entry(entry, काष्ठा x25_क्रमward, node);
		अगर (x25_frwd->lci == lci) अणु
			pr_warn("call request for lci which is already registered!, transmitting but not registering new pair\n");
			same_lci = 1;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&x25_क्रमward_list_lock);

	/* Save the क्रमwarding details क्रम future traffic */
	अगर (!same_lci)अणु
		अगर ((new_frwd = kदो_स्मृति(माप(काष्ठा x25_क्रमward),
						GFP_ATOMIC)) == शून्य)अणु
			rc = -ENOMEM;
			जाओ out_put_nb;
		पूर्ण
		new_frwd->lci = lci;
		new_frwd->dev1 = rt->dev;
		new_frwd->dev2 = from->dev;
		ग_लिखो_lock_bh(&x25_क्रमward_list_lock);
		list_add(&new_frwd->node, &x25_क्रमward_list);
		ग_लिखो_unlock_bh(&x25_क्रमward_list_lock);
	पूर्ण

	/* Forward the call request */
	अगर ( (skbn = skb_clone(skb, GFP_ATOMIC)) == शून्य)अणु
		जाओ out_put_nb;
	पूर्ण
	x25_transmit_link(skbn, neigh_new);
	rc = 1;


out_put_nb:
	x25_neigh_put(neigh_new);

out_put_route:
	x25_route_put(rt);

out_no_route:
	वापस rc;
पूर्ण


पूर्णांक x25_क्रमward_data(पूर्णांक lci, काष्ठा x25_neigh *from, काष्ठा sk_buff *skb) अणु

	काष्ठा x25_क्रमward *frwd;
	काष्ठा list_head *entry;
	काष्ठा net_device *peer = शून्य;
	काष्ठा x25_neigh *nb;
	काष्ठा sk_buff *skbn;
	पूर्णांक rc = 0;

	पढ़ो_lock_bh(&x25_क्रमward_list_lock);
	list_क्रम_each(entry, &x25_क्रमward_list) अणु
		frwd = list_entry(entry, काष्ठा x25_क्रमward, node);
		अगर (frwd->lci == lci) अणु
			/* The call is established, either side can send */
			अगर (from->dev == frwd->dev1) अणु
				peer = frwd->dev2;
			पूर्ण अन्यथा अणु
				peer = frwd->dev1;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&x25_क्रमward_list_lock);

	अगर ( (nb = x25_get_neigh(peer)) == शून्य)
		जाओ out;

	अगर ( (skbn = pskb_copy(skb, GFP_ATOMIC)) == शून्य)अणु
		जाओ output;

	पूर्ण
	x25_transmit_link(skbn, nb);

	rc = 1;
output:
	x25_neigh_put(nb);
out:
	वापस rc;
पूर्ण

व्योम x25_clear_क्रमward_by_lci(अचिन्हित पूर्णांक lci)
अणु
	काष्ठा x25_क्रमward *fwd, *पंचांगp;

	ग_लिखो_lock_bh(&x25_क्रमward_list_lock);

	list_क्रम_each_entry_safe(fwd, पंचांगp, &x25_क्रमward_list, node) अणु
		अगर (fwd->lci == lci) अणु
			list_del(&fwd->node);
			kमुक्त(fwd);
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_bh(&x25_क्रमward_list_lock);
पूर्ण


व्योम x25_clear_क्रमward_by_dev(काष्ठा net_device *dev)
अणु
	काष्ठा x25_क्रमward *fwd, *पंचांगp;

	ग_लिखो_lock_bh(&x25_क्रमward_list_lock);

	list_क्रम_each_entry_safe(fwd, पंचांगp, &x25_क्रमward_list, node) अणु
		अगर ((fwd->dev1 == dev) || (fwd->dev2 == dev))अणु
			list_del(&fwd->node);
			kमुक्त(fwd);
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_bh(&x25_क्रमward_list_lock);
पूर्ण
