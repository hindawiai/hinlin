<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2010-2011 EIA Electronics,
//                         Kurt Van Dijck <kurt.van.dijck@eia.be>
// Copyright (c) 2017-2019 Pengutronix,
//                         Marc Kleine-Budde <kernel@pengutronix.de>
// Copyright (c) 2017-2019 Pengutronix,
//                         Oleksij Rempel <kernel@pengutronix.de>

/* bus क्रम j1939 remote devices
 * Since rtnetlink, no real bus is used.
 */

#समावेश <net/sock.h>

#समावेश "j1939-priv.h"

अटल व्योम __j1939_ecu_release(काष्ठा kref *kref)
अणु
	काष्ठा j1939_ecu *ecu = container_of(kref, काष्ठा j1939_ecu, kref);
	काष्ठा j1939_priv *priv = ecu->priv;

	list_del(&ecu->list);
	kमुक्त(ecu);
	j1939_priv_put(priv);
पूर्ण

व्योम j1939_ecu_put(काष्ठा j1939_ecu *ecu)
अणु
	kref_put(&ecu->kref, __j1939_ecu_release);
पूर्ण

अटल व्योम j1939_ecu_get(काष्ठा j1939_ecu *ecu)
अणु
	kref_get(&ecu->kref);
पूर्ण

अटल bool j1939_ecu_is_mapped_locked(काष्ठा j1939_ecu *ecu)
अणु
	काष्ठा j1939_priv *priv = ecu->priv;

	lockdep_निश्चित_held(&priv->lock);

	वापस j1939_ecu_find_by_addr_locked(priv, ecu->addr) == ecu;
पूर्ण

/* ECU device पूर्णांकerface */
/* map ECU to a bus address space */
अटल व्योम j1939_ecu_map_locked(काष्ठा j1939_ecu *ecu)
अणु
	काष्ठा j1939_priv *priv = ecu->priv;
	काष्ठा j1939_addr_ent *ent;

	lockdep_निश्चित_held(&priv->lock);

	अगर (!j1939_address_is_unicast(ecu->addr))
		वापस;

	ent = &priv->ents[ecu->addr];

	अगर (ent->ecu) अणु
		netdev_warn(priv->ndev, "Trying to map already mapped ECU, addr: 0x%02x, name: 0x%016llx. Skip it.\n",
			    ecu->addr, ecu->name);
		वापस;
	पूर्ण

	j1939_ecu_get(ecu);
	ent->ecu = ecu;
	ent->nusers += ecu->nusers;
पूर्ण

/* unmap ECU from a bus address space */
व्योम j1939_ecu_unmap_locked(काष्ठा j1939_ecu *ecu)
अणु
	काष्ठा j1939_priv *priv = ecu->priv;
	काष्ठा j1939_addr_ent *ent;

	lockdep_निश्चित_held(&priv->lock);

	अगर (!j1939_address_is_unicast(ecu->addr))
		वापस;

	अगर (!j1939_ecu_is_mapped_locked(ecu))
		वापस;

	ent = &priv->ents[ecu->addr];
	ent->ecu = शून्य;
	ent->nusers -= ecu->nusers;
	j1939_ecu_put(ecu);
पूर्ण

व्योम j1939_ecu_unmap(काष्ठा j1939_ecu *ecu)
अणु
	ग_लिखो_lock_bh(&ecu->priv->lock);
	j1939_ecu_unmap_locked(ecu);
	ग_लिखो_unlock_bh(&ecu->priv->lock);
पूर्ण

व्योम j1939_ecu_unmap_all(काष्ठा j1939_priv *priv)
अणु
	पूर्णांक i;

	ग_लिखो_lock_bh(&priv->lock);
	क्रम (i = 0; i < ARRAY_SIZE(priv->ents); i++)
		अगर (priv->ents[i].ecu)
			j1939_ecu_unmap_locked(priv->ents[i].ecu);
	ग_लिखो_unlock_bh(&priv->lock);
पूर्ण

व्योम j1939_ecu_समयr_start(काष्ठा j1939_ecu *ecu)
अणु
	/* The ECU is held here and released in the
	 * j1939_ecu_समयr_handler() or j1939_ecu_समयr_cancel().
	 */
	j1939_ecu_get(ecu);

	/* Schedule समयr in 250 msec to commit address change. */
	hrसमयr_start(&ecu->ac_समयr, ms_to_kसमय(250),
		      HRTIMER_MODE_REL_SOFT);
पूर्ण

व्योम j1939_ecu_समयr_cancel(काष्ठा j1939_ecu *ecu)
अणु
	अगर (hrसमयr_cancel(&ecu->ac_समयr))
		j1939_ecu_put(ecu);
पूर्ण

अटल क्रमागत hrसमयr_restart j1939_ecu_समयr_handler(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा j1939_ecu *ecu =
		container_of(hrसमयr, काष्ठा j1939_ecu, ac_समयr);
	काष्ठा j1939_priv *priv = ecu->priv;

	ग_लिखो_lock_bh(&priv->lock);
	/* TODO: can we test अगर ecu->addr is unicast beक्रमe starting
	 * the समयr?
	 */
	j1939_ecu_map_locked(ecu);

	/* The corresponding j1939_ecu_get() is in
	 * j1939_ecu_समयr_start().
	 */
	j1939_ecu_put(ecu);
	ग_लिखो_unlock_bh(&priv->lock);

	वापस HRTIMER_NORESTART;
पूर्ण

काष्ठा j1939_ecu *j1939_ecu_create_locked(काष्ठा j1939_priv *priv, name_t name)
अणु
	काष्ठा j1939_ecu *ecu;

	lockdep_निश्चित_held(&priv->lock);

	ecu = kzalloc(माप(*ecu), gfp_any());
	अगर (!ecu)
		वापस ERR_PTR(-ENOMEM);
	kref_init(&ecu->kref);
	ecu->addr = J1939_IDLE_ADDR;
	ecu->name = name;

	hrसमयr_init(&ecu->ac_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_SOFT);
	ecu->ac_समयr.function = j1939_ecu_समयr_handler;
	INIT_LIST_HEAD(&ecu->list);

	j1939_priv_get(priv);
	ecu->priv = priv;
	list_add_tail(&ecu->list, &priv->ecus);

	वापस ecu;
पूर्ण

काष्ठा j1939_ecu *j1939_ecu_find_by_addr_locked(काष्ठा j1939_priv *priv,
						u8 addr)
अणु
	lockdep_निश्चित_held(&priv->lock);

	वापस priv->ents[addr].ecu;
पूर्ण

काष्ठा j1939_ecu *j1939_ecu_get_by_addr_locked(काष्ठा j1939_priv *priv, u8 addr)
अणु
	काष्ठा j1939_ecu *ecu;

	lockdep_निश्चित_held(&priv->lock);

	अगर (!j1939_address_is_unicast(addr))
		वापस शून्य;

	ecu = j1939_ecu_find_by_addr_locked(priv, addr);
	अगर (ecu)
		j1939_ecu_get(ecu);

	वापस ecu;
पूर्ण

काष्ठा j1939_ecu *j1939_ecu_get_by_addr(काष्ठा j1939_priv *priv, u8 addr)
अणु
	काष्ठा j1939_ecu *ecu;

	पढ़ो_lock_bh(&priv->lock);
	ecu = j1939_ecu_get_by_addr_locked(priv, addr);
	पढ़ो_unlock_bh(&priv->lock);

	वापस ecu;
पूर्ण

/* get poपूर्णांकer to ecu without increasing ref counter */
अटल काष्ठा j1939_ecu *j1939_ecu_find_by_name_locked(काष्ठा j1939_priv *priv,
						       name_t name)
अणु
	काष्ठा j1939_ecu *ecu;

	lockdep_निश्चित_held(&priv->lock);

	list_क्रम_each_entry(ecu, &priv->ecus, list) अणु
		अगर (ecu->name == name)
			वापस ecu;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा j1939_ecu *j1939_ecu_get_by_name_locked(काष्ठा j1939_priv *priv,
					       name_t name)
अणु
	काष्ठा j1939_ecu *ecu;

	lockdep_निश्चित_held(&priv->lock);

	अगर (!name)
		वापस शून्य;

	ecu = j1939_ecu_find_by_name_locked(priv, name);
	अगर (ecu)
		j1939_ecu_get(ecu);

	वापस ecu;
पूर्ण

काष्ठा j1939_ecu *j1939_ecu_get_by_name(काष्ठा j1939_priv *priv, name_t name)
अणु
	काष्ठा j1939_ecu *ecu;

	पढ़ो_lock_bh(&priv->lock);
	ecu = j1939_ecu_get_by_name_locked(priv, name);
	पढ़ो_unlock_bh(&priv->lock);

	वापस ecu;
पूर्ण

u8 j1939_name_to_addr(काष्ठा j1939_priv *priv, name_t name)
अणु
	काष्ठा j1939_ecu *ecu;
	पूर्णांक addr = J1939_IDLE_ADDR;

	अगर (!name)
		वापस J1939_NO_ADDR;

	पढ़ो_lock_bh(&priv->lock);
	ecu = j1939_ecu_find_by_name_locked(priv, name);
	अगर (ecu && j1939_ecu_is_mapped_locked(ecu))
		/* ecu's SA is रेजिस्टरed */
		addr = ecu->addr;

	पढ़ो_unlock_bh(&priv->lock);

	वापस addr;
पूर्ण

/* TX addr/name accounting
 * Transport protocol needs to know अगर a SA is local or not
 * These functions originate from userspace manipulating sockets,
 * so locking is straigक्रमward
 */

पूर्णांक j1939_local_ecu_get(काष्ठा j1939_priv *priv, name_t name, u8 sa)
अणु
	काष्ठा j1939_ecu *ecu;
	पूर्णांक err = 0;

	ग_लिखो_lock_bh(&priv->lock);

	अगर (j1939_address_is_unicast(sa))
		priv->ents[sa].nusers++;

	अगर (!name)
		जाओ करोne;

	ecu = j1939_ecu_get_by_name_locked(priv, name);
	अगर (!ecu)
		ecu = j1939_ecu_create_locked(priv, name);
	err = PTR_ERR_OR_ZERO(ecu);
	अगर (err)
		जाओ करोne;

	ecu->nusers++;
	/* TODO: करो we care अगर ecu->addr != sa? */
	अगर (j1939_ecu_is_mapped_locked(ecu))
		/* ecu's sa is active alपढ़ोy */
		priv->ents[ecu->addr].nusers++;

 करोne:
	ग_लिखो_unlock_bh(&priv->lock);

	वापस err;
पूर्ण

व्योम j1939_local_ecu_put(काष्ठा j1939_priv *priv, name_t name, u8 sa)
अणु
	काष्ठा j1939_ecu *ecu;

	ग_लिखो_lock_bh(&priv->lock);

	अगर (j1939_address_is_unicast(sa))
		priv->ents[sa].nusers--;

	अगर (!name)
		जाओ करोne;

	ecu = j1939_ecu_find_by_name_locked(priv, name);
	अगर (WARN_ON_ONCE(!ecu))
		जाओ करोne;

	ecu->nusers--;
	/* TODO: करो we care अगर ecu->addr != sa? */
	अगर (j1939_ecu_is_mapped_locked(ecu))
		/* ecu's sa is active alपढ़ोy */
		priv->ents[ecu->addr].nusers--;
	j1939_ecu_put(ecu);

 करोne:
	ग_लिखो_unlock_bh(&priv->lock);
पूर्ण
