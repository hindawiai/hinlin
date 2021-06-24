<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* net/aपंचांग/aपंचांग_misc.c - Various functions क्रम use by ATM drivers */

/* Written 1995-2000 by Werner Almesberger, EPFL ICA */

#समावेश <linux/module.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/sonet.h>
#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/atomic.h>

पूर्णांक aपंचांग_अक्षरge(काष्ठा aपंचांग_vcc *vcc, पूर्णांक truesize)
अणु
	aपंचांग_क्रमce_अक्षरge(vcc, truesize);
	अगर (atomic_पढ़ो(&sk_aपंचांग(vcc)->sk_rmem_alloc) <= sk_aपंचांग(vcc)->sk_rcvbuf)
		वापस 1;
	aपंचांग_वापस(vcc, truesize);
	atomic_inc(&vcc->stats->rx_drop);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(aपंचांग_अक्षरge);

काष्ठा sk_buff *aपंचांग_alloc_अक्षरge(काष्ठा aपंचांग_vcc *vcc, पूर्णांक pdu_size,
				 gfp_t gfp_flags)
अणु
	काष्ठा sock *sk = sk_aपंचांग(vcc);
	पूर्णांक guess = SKB_TRUESIZE(pdu_size);

	aपंचांग_क्रमce_अक्षरge(vcc, guess);
	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf) अणु
		काष्ठा sk_buff *skb = alloc_skb(pdu_size, gfp_flags);

		अगर (skb) अणु
			atomic_add(skb->truesize-guess,
				   &sk->sk_rmem_alloc);
			वापस skb;
		पूर्ण
	पूर्ण
	aपंचांग_वापस(vcc, guess);
	atomic_inc(&vcc->stats->rx_drop);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(aपंचांग_alloc_अक्षरge);


/*
 * aपंचांग_pcr_goal वापसs the positive PCR अगर it should be rounded up, the
 * negative PCR अगर it should be rounded करोwn, and zero अगर the maximum available
 * bandwidth should be used.
 *
 * The rules are as follows (* = maximum, - = असलent (0), x = value "x",
 * (x+ = x or next value above x, x- = x or next value below):
 *
 *	min max pcr	result		min max pcr	result
 *	-   -   -	* (UBR only)	x   -   -	x+
 *	-   -   *	*		x   -   *	*
 *	-   -   z	z-		x   -   z	z-
 *	-   *   -	*		x   *   -	x+
 *	-   *   *	*		x   *   *	*
 *	-   *   z	z-		x   *   z	z-
 *	-   y   -	y-		x   y   -	x+
 *	-   y   *	y-		x   y   *	y-
 *	-   y   z	z-		x   y   z	z-
 *
 * All non-error हालs can be converted with the following simple set of rules:
 *
 *   अगर pcr == z then z-
 *   अन्यथा अगर min == x && pcr == - then x+
 *     अन्यथा अगर max == y then y-
 *	 अन्यथा *
 */

पूर्णांक aपंचांग_pcr_goal(स्थिर काष्ठा aपंचांग_trafprm *tp)
अणु
	अगर (tp->pcr && tp->pcr != ATM_MAX_PCR)
		वापस -tp->pcr;
	अगर (tp->min_pcr && !tp->pcr)
		वापस tp->min_pcr;
	अगर (tp->max_pcr != ATM_MAX_PCR)
		वापस -tp->max_pcr;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(aपंचांग_pcr_goal);

व्योम sonet_copy_stats(काष्ठा k_sonet_stats *from, काष्ठा sonet_stats *to)
अणु
#घोषणा __HANDLE_ITEM(i) to->i = atomic_पढ़ो(&from->i)
	__SONET_ITEMS
#अघोषित __HANDLE_ITEM
पूर्ण
EXPORT_SYMBOL(sonet_copy_stats);

व्योम sonet_subtract_stats(काष्ठा k_sonet_stats *from, काष्ठा sonet_stats *to)
अणु
#घोषणा __HANDLE_ITEM(i) atomic_sub(to->i, &from->i)
	__SONET_ITEMS
#अघोषित __HANDLE_ITEM
पूर्ण
EXPORT_SYMBOL(sonet_subtract_stats);
