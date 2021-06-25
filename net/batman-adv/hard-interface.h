<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#अगर_अघोषित _NET_BATMAN_ADV_HARD_INTERFACE_H_
#घोषणा _NET_BATMAN_ADV_HARD_INTERFACE_H_

#समावेश "main.h"

#समावेश <linux/compiler.h>
#समावेश <linux/kref.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <net/net_namespace.h>

/**
 * क्रमागत batadv_hard_अगर_state - State of a hard पूर्णांकerface
 */
क्रमागत batadv_hard_अगर_state अणु
	/**
	 * @BATADV_IF_NOT_IN_USE: पूर्णांकerface is not used as slave पूर्णांकerface of a
	 * baपंचांगan-adv soft पूर्णांकerface
	 */
	BATADV_IF_NOT_IN_USE,

	/**
	 * @BATADV_IF_TO_BE_REMOVED: पूर्णांकerface will be हटाओd from soft
	 * पूर्णांकerface
	 */
	BATADV_IF_TO_BE_REMOVED,

	/** @BATADV_IF_INACTIVE: पूर्णांकerface is deactivated */
	BATADV_IF_INACTIVE,

	/** @BATADV_IF_ACTIVE: पूर्णांकerface is used */
	BATADV_IF_ACTIVE,

	/** @BATADV_IF_TO_BE_ACTIVATED: पूर्णांकerface is getting activated */
	BATADV_IF_TO_BE_ACTIVATED,
पूर्ण;

/**
 * क्रमागत batadv_hard_अगर_bcast - broadcast aव्योमance options
 */
क्रमागत batadv_hard_अगर_bcast अणु
	/** @BATADV_HARDIF_BCAST_OK: Do broadcast on according hard पूर्णांकerface */
	BATADV_HARDIF_BCAST_OK = 0,

	/**
	 * @BATADV_HARDIF_BCAST_NORECIPIENT: Broadcast not needed, there is no
	 *  recipient
	 */
	BATADV_HARDIF_BCAST_NORECIPIENT,

	/**
	 * @BATADV_HARDIF_BCAST_DUPFWD: There is just the neighbor we got it
	 *  from
	 */
	BATADV_HARDIF_BCAST_DUPFWD,

	/** @BATADV_HARDIF_BCAST_DUPORIG: There is just the originator */
	BATADV_HARDIF_BCAST_DUPORIG,
पूर्ण;

बाह्य काष्ठा notअगरier_block batadv_hard_अगर_notअगरier;

काष्ठा net_device *batadv_get_real_netdev(काष्ठा net_device *net_device);
bool batadv_is_cfg80211_hardअगर(काष्ठा batadv_hard_अगरace *hard_अगरace);
bool batadv_is_wअगरi_hardअगर(काष्ठा batadv_hard_अगरace *hard_अगरace);
काष्ठा batadv_hard_अगरace*
batadv_hardअगर_get_by_netdev(स्थिर काष्ठा net_device *net_dev);
पूर्णांक batadv_hardअगर_enable_पूर्णांकerface(काष्ठा batadv_hard_अगरace *hard_अगरace,
				   काष्ठा net *net, स्थिर अक्षर *अगरace_name);
व्योम batadv_hardअगर_disable_पूर्णांकerface(काष्ठा batadv_hard_अगरace *hard_अगरace);
पूर्णांक batadv_hardअगर_min_mtu(काष्ठा net_device *soft_अगरace);
व्योम batadv_update_min_mtu(काष्ठा net_device *soft_अगरace);
व्योम batadv_hardअगर_release(काष्ठा kref *ref);
पूर्णांक batadv_hardअगर_no_broadcast(काष्ठा batadv_hard_अगरace *अगर_outgoing,
			       u8 *orig_addr, u8 *orig_neigh);

/**
 * batadv_hardअगर_put() - decrement the hard पूर्णांकerface refcounter and possibly
 *  release it
 * @hard_अगरace: the hard पूर्णांकerface to मुक्त
 */
अटल अंतरभूत व्योम batadv_hardअगर_put(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	kref_put(&hard_अगरace->refcount, batadv_hardअगर_release);
पूर्ण

/**
 * batadv_primary_अगर_get_selected() - Get reference to primary पूर्णांकerface
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: primary पूर्णांकerface (with increased refcnt), otherwise शून्य
 */
अटल अंतरभूत काष्ठा batadv_hard_अगरace *
batadv_primary_अगर_get_selected(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;

	rcu_पढ़ो_lock();
	hard_अगरace = rcu_dereference(bat_priv->primary_अगर);
	अगर (!hard_अगरace)
		जाओ out;

	अगर (!kref_get_unless_zero(&hard_अगरace->refcount))
		hard_अगरace = शून्य;

out:
	rcu_पढ़ो_unlock();
	वापस hard_अगरace;
पूर्ण

#पूर्ण_अगर /* _NET_BATMAN_ADV_HARD_INTERFACE_H_ */
