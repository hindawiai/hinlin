<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* net/aपंचांग/aपंचांगarp.h - RFC1577 ATM ARP */
 
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
 
 
#अगर_अघोषित _ATMCLIP_H
#घोषणा _ATMCLIP_H

#समावेश <linux/netdevice.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांगarp.h>
#समावेश <linux/spinlock.h>
#समावेश <net/neighbour.h>


#घोषणा CLIP_VCC(vcc) ((काष्ठा clip_vcc *) ((vcc)->user_back))

काष्ठा sk_buff;

काष्ठा clip_vcc अणु
	काष्ठा aपंचांग_vcc	*vcc;		/* VCC descriptor */
	काष्ठा aपंचांगarp_entry *entry;	/* ATMARP table entry, शून्य अगर IP addr.
					   isn't known yet */
	पूर्णांक		xoff;		/* 1 अगर send buffer is full */
	अचिन्हित अक्षर	encap;		/* 0: शून्य, 1: LLC/SNAP */
	अचिन्हित दीर्घ	last_use;	/* last send or receive operation */
	अचिन्हित दीर्घ	idle_समयout;	/* keep खोलो idle क्रम so many jअगरfies*/
	व्योम (*old_push)(काष्ठा aपंचांग_vcc *vcc,काष्ठा sk_buff *skb);
					/* keep old push fn क्रम chaining */
	व्योम (*old_pop)(काष्ठा aपंचांग_vcc *vcc,काष्ठा sk_buff *skb);
					/* keep old pop fn क्रम chaining */
	काष्ठा clip_vcc	*next;		/* next VCC */
पूर्ण;


काष्ठा aपंचांगarp_entry अणु
	काष्ठा clip_vcc	*vccs;		/* active VCCs; शून्य अगर resolution is
					   pending */
	अचिन्हित दीर्घ	expires;	/* entry expiration समय */
	काष्ठा neighbour *neigh;	/* neighbour back-poपूर्णांकer */
पूर्ण;

#घोषणा PRIV(dev) ((काष्ठा clip_priv *) netdev_priv(dev))

काष्ठा clip_priv अणु
	पूर्णांक number;			/* क्रम convenience ... */
	spinlock_t xoff_lock;		/* ensures that pop is atomic (SMP) */
	काष्ठा net_device *next;	/* next CLIP पूर्णांकerface */
पूर्ण;

#पूर्ण_अगर
