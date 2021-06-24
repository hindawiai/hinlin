<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Tomi Manninen OH2BNS (oh2bns@sral.fi)
 * Copyright (C) Darryl Miles G7LED (dlm@g7led.demon.co.uk)
 * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)
 * Copyright (C) Frederic Rible F1OAT (frible@teaser.fr)
 * Copyright (C) 2002 Ralf Baechle DO1GRB (ralf@gnu.org)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>

अटल व्योम ax25_heartbeat_expiry(काष्ठा समयr_list *);
अटल व्योम ax25_t1समयr_expiry(काष्ठा समयr_list *);
अटल व्योम ax25_t2समयr_expiry(काष्ठा समयr_list *);
अटल व्योम ax25_t3समयr_expiry(काष्ठा समयr_list *);
अटल व्योम ax25_idleसमयr_expiry(काष्ठा समयr_list *);

व्योम ax25_setup_समयrs(ax25_cb *ax25)
अणु
	समयr_setup(&ax25->समयr, ax25_heartbeat_expiry, 0);
	समयr_setup(&ax25->t1समयr, ax25_t1समयr_expiry, 0);
	समयr_setup(&ax25->t2समयr, ax25_t2समयr_expiry, 0);
	समयr_setup(&ax25->t3समयr, ax25_t3समयr_expiry, 0);
	समयr_setup(&ax25->idleसमयr, ax25_idleसमयr_expiry, 0);
पूर्ण

व्योम ax25_start_heartbeat(ax25_cb *ax25)
अणु
	mod_समयr(&ax25->समयr, jअगरfies + 5 * HZ);
पूर्ण

व्योम ax25_start_t1समयr(ax25_cb *ax25)
अणु
	mod_समयr(&ax25->t1समयr, jअगरfies + ax25->t1);
पूर्ण

व्योम ax25_start_t2समयr(ax25_cb *ax25)
अणु
	mod_समयr(&ax25->t2समयr, jअगरfies + ax25->t2);
पूर्ण

व्योम ax25_start_t3समयr(ax25_cb *ax25)
अणु
	अगर (ax25->t3 > 0)
		mod_समयr(&ax25->t3समयr, jअगरfies + ax25->t3);
	अन्यथा
		del_समयr(&ax25->t3समयr);
पूर्ण

व्योम ax25_start_idleसमयr(ax25_cb *ax25)
अणु
	अगर (ax25->idle > 0)
		mod_समयr(&ax25->idleसमयr, jअगरfies + ax25->idle);
	अन्यथा
		del_समयr(&ax25->idleसमयr);
पूर्ण

व्योम ax25_stop_heartbeat(ax25_cb *ax25)
अणु
	del_समयr(&ax25->समयr);
पूर्ण

व्योम ax25_stop_t1समयr(ax25_cb *ax25)
अणु
	del_समयr(&ax25->t1समयr);
पूर्ण

व्योम ax25_stop_t2समयr(ax25_cb *ax25)
अणु
	del_समयr(&ax25->t2समयr);
पूर्ण

व्योम ax25_stop_t3समयr(ax25_cb *ax25)
अणु
	del_समयr(&ax25->t3समयr);
पूर्ण

व्योम ax25_stop_idleसमयr(ax25_cb *ax25)
अणु
	del_समयr(&ax25->idleसमयr);
पूर्ण

पूर्णांक ax25_t1समयr_running(ax25_cb *ax25)
अणु
	वापस समयr_pending(&ax25->t1समयr);
पूर्ण

अचिन्हित दीर्घ ax25_display_समयr(काष्ठा समयr_list *समयr)
अणु
	अगर (!समयr_pending(समयr))
		वापस 0;

	वापस समयr->expires - jअगरfies;
पूर्ण

EXPORT_SYMBOL(ax25_display_समयr);

अटल व्योम ax25_heartbeat_expiry(काष्ठा समयr_list *t)
अणु
	पूर्णांक proto = AX25_PROTO_STD_SIMPLEX;
	ax25_cb *ax25 = from_समयr(ax25, t, समयr);

	अगर (ax25->ax25_dev)
		proto = ax25->ax25_dev->values[AX25_VALUES_PROTOCOL];

	चयन (proto) अणु
	हाल AX25_PROTO_STD_SIMPLEX:
	हाल AX25_PROTO_STD_DUPLEX:
		ax25_std_heartbeat_expiry(ax25);
		अवरोध;

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	हाल AX25_PROTO_DAMA_SLAVE:
		अगर (ax25->ax25_dev->dama.slave)
			ax25_ds_heartbeat_expiry(ax25);
		अन्यथा
			ax25_std_heartbeat_expiry(ax25);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम ax25_t1समयr_expiry(काष्ठा समयr_list *t)
अणु
	ax25_cb *ax25 = from_समयr(ax25, t, t1समयr);

	चयन (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) अणु
	हाल AX25_PROTO_STD_SIMPLEX:
	हाल AX25_PROTO_STD_DUPLEX:
		ax25_std_t1समयr_expiry(ax25);
		अवरोध;

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	हाल AX25_PROTO_DAMA_SLAVE:
		अगर (!ax25->ax25_dev->dama.slave)
			ax25_std_t1समयr_expiry(ax25);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम ax25_t2समयr_expiry(काष्ठा समयr_list *t)
अणु
	ax25_cb *ax25 = from_समयr(ax25, t, t2समयr);

	चयन (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) अणु
	हाल AX25_PROTO_STD_SIMPLEX:
	हाल AX25_PROTO_STD_DUPLEX:
		ax25_std_t2समयr_expiry(ax25);
		अवरोध;

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	हाल AX25_PROTO_DAMA_SLAVE:
		अगर (!ax25->ax25_dev->dama.slave)
			ax25_std_t2समयr_expiry(ax25);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम ax25_t3समयr_expiry(काष्ठा समयr_list *t)
अणु
	ax25_cb *ax25 = from_समयr(ax25, t, t3समयr);

	चयन (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) अणु
	हाल AX25_PROTO_STD_SIMPLEX:
	हाल AX25_PROTO_STD_DUPLEX:
		ax25_std_t3समयr_expiry(ax25);
		अवरोध;

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	हाल AX25_PROTO_DAMA_SLAVE:
		अगर (ax25->ax25_dev->dama.slave)
			ax25_ds_t3समयr_expiry(ax25);
		अन्यथा
			ax25_std_t3समयr_expiry(ax25);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम ax25_idleसमयr_expiry(काष्ठा समयr_list *t)
अणु
	ax25_cb *ax25 = from_समयr(ax25, t, idleसमयr);

	चयन (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) अणु
	हाल AX25_PROTO_STD_SIMPLEX:
	हाल AX25_PROTO_STD_DUPLEX:
		ax25_std_idleसमयr_expiry(ax25);
		अवरोध;

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	हाल AX25_PROTO_DAMA_SLAVE:
		अगर (ax25->ax25_dev->dama.slave)
			ax25_ds_idleसमयr_expiry(ax25);
		अन्यथा
			ax25_std_idleसमयr_expiry(ax25);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण
