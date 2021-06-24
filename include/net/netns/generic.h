<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * generic net poपूर्णांकers
 */

#अगर_अघोषित __NET_GENERIC_H__
#घोषणा __NET_GENERIC_H__

#समावेश <linux/bug.h>
#समावेश <linux/rcupdate.h>

/*
 * Generic net poपूर्णांकers are to be used by modules to put some निजी
 * stuff on the काष्ठा net without explicit काष्ठा net modअगरication
 *
 * The rules are simple:
 * 1. set pernet_operations->id.  After रेजिस्टर_pernet_device you
 *    will have the id of your निजी poपूर्णांकer.
 * 2. set pernet_operations->size to have the code allocate and मुक्त
 *    a निजी काष्ठाure poपूर्णांकed to from काष्ठा net.
 * 3. करो not change this poपूर्णांकer जबतक the net is alive;
 * 4. करो not try to have any निजी reference on the net_generic object.
 *
 * After accomplishing all of the above, the निजी poपूर्णांकer can be
 * accessed with the net_generic() call.
 */

काष्ठा net_generic अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक len;
			काष्ठा rcu_head rcu;
		पूर्ण s;

		व्योम *ptr[0];
	पूर्ण;
पूर्ण;

अटल अंतरभूत व्योम *net_generic(स्थिर काष्ठा net *net, अचिन्हित पूर्णांक id)
अणु
	काष्ठा net_generic *ng;
	व्योम *ptr;

	rcu_पढ़ो_lock();
	ng = rcu_dereference(net->gen);
	ptr = ng->ptr[id];
	rcu_पढ़ो_unlock();

	वापस ptr;
पूर्ण
#पूर्ण_अगर
