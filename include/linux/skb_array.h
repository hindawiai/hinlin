<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Definitions क्रम the 'struct skb_array' dataकाष्ठाure.
 *
 *	Author:
 *		Michael S. Tsirkin <mst@redhat.com>
 *
 *	Copyright (C) 2016 Red Hat, Inc.
 *
 *	Limited-size FIFO of skbs. Can be used more or less whenever
 *	sk_buff_head can be used, except you need to know the queue size in
 *	advance.
 *	Implemented as a type-safe wrapper around ptr_ring.
 */

#अगर_अघोषित _LINUX_SKB_ARRAY_H
#घोषणा _LINUX_SKB_ARRAY_H 1

#अगर_घोषित __KERNEL__
#समावेश <linux/ptr_ring.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>
#पूर्ण_अगर

काष्ठा skb_array अणु
	काष्ठा ptr_ring ring;
पूर्ण;

/* Might be slightly faster than skb_array_full below, but callers invoking
 * this in a loop must use a compiler barrier, क्रम example cpu_relax().
 */
अटल अंतरभूत bool __skb_array_full(काष्ठा skb_array *a)
अणु
	वापस __ptr_ring_full(&a->ring);
पूर्ण

अटल अंतरभूत bool skb_array_full(काष्ठा skb_array *a)
अणु
	वापस ptr_ring_full(&a->ring);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_produce(काष्ठा skb_array *a, काष्ठा sk_buff *skb)
अणु
	वापस ptr_ring_produce(&a->ring, skb);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_produce_irq(काष्ठा skb_array *a, काष्ठा sk_buff *skb)
अणु
	वापस ptr_ring_produce_irq(&a->ring, skb);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_produce_bh(काष्ठा skb_array *a, काष्ठा sk_buff *skb)
अणु
	वापस ptr_ring_produce_bh(&a->ring, skb);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_produce_any(काष्ठा skb_array *a, काष्ठा sk_buff *skb)
अणु
	वापस ptr_ring_produce_any(&a->ring, skb);
पूर्ण

/* Might be slightly faster than skb_array_empty below, but only safe अगर the
 * array is never resized. Also, callers invoking this in a loop must take care
 * to use a compiler barrier, क्रम example cpu_relax().
 */
अटल अंतरभूत bool __skb_array_empty(काष्ठा skb_array *a)
अणु
	वापस __ptr_ring_empty(&a->ring);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *__skb_array_peek(काष्ठा skb_array *a)
अणु
	वापस __ptr_ring_peek(&a->ring);
पूर्ण

अटल अंतरभूत bool skb_array_empty(काष्ठा skb_array *a)
अणु
	वापस ptr_ring_empty(&a->ring);
पूर्ण

अटल अंतरभूत bool skb_array_empty_bh(काष्ठा skb_array *a)
अणु
	वापस ptr_ring_empty_bh(&a->ring);
पूर्ण

अटल अंतरभूत bool skb_array_empty_irq(काष्ठा skb_array *a)
अणु
	वापस ptr_ring_empty_irq(&a->ring);
पूर्ण

अटल अंतरभूत bool skb_array_empty_any(काष्ठा skb_array *a)
अणु
	वापस ptr_ring_empty_any(&a->ring);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *__skb_array_consume(काष्ठा skb_array *a)
अणु
	वापस __ptr_ring_consume(&a->ring);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *skb_array_consume(काष्ठा skb_array *a)
अणु
	वापस ptr_ring_consume(&a->ring);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_consume_batched(काष्ठा skb_array *a,
					    काष्ठा sk_buff **array, पूर्णांक n)
अणु
	वापस ptr_ring_consume_batched(&a->ring, (व्योम **)array, n);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *skb_array_consume_irq(काष्ठा skb_array *a)
अणु
	वापस ptr_ring_consume_irq(&a->ring);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_consume_batched_irq(काष्ठा skb_array *a,
						काष्ठा sk_buff **array, पूर्णांक n)
अणु
	वापस ptr_ring_consume_batched_irq(&a->ring, (व्योम **)array, n);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *skb_array_consume_any(काष्ठा skb_array *a)
अणु
	वापस ptr_ring_consume_any(&a->ring);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_consume_batched_any(काष्ठा skb_array *a,
						काष्ठा sk_buff **array, पूर्णांक n)
अणु
	वापस ptr_ring_consume_batched_any(&a->ring, (व्योम **)array, n);
पूर्ण


अटल अंतरभूत काष्ठा sk_buff *skb_array_consume_bh(काष्ठा skb_array *a)
अणु
	वापस ptr_ring_consume_bh(&a->ring);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_consume_batched_bh(काष्ठा skb_array *a,
					       काष्ठा sk_buff **array, पूर्णांक n)
अणु
	वापस ptr_ring_consume_batched_bh(&a->ring, (व्योम **)array, n);
पूर्ण

अटल अंतरभूत पूर्णांक __skb_array_len_with_tag(काष्ठा sk_buff *skb)
अणु
	अगर (likely(skb)) अणु
		पूर्णांक len = skb->len;

		अगर (skb_vlan_tag_present(skb))
			len += VLAN_HLEN;

		वापस len;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_peek_len(काष्ठा skb_array *a)
अणु
	वापस PTR_RING_PEEK_CALL(&a->ring, __skb_array_len_with_tag);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_peek_len_irq(काष्ठा skb_array *a)
अणु
	वापस PTR_RING_PEEK_CALL_IRQ(&a->ring, __skb_array_len_with_tag);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_peek_len_bh(काष्ठा skb_array *a)
अणु
	वापस PTR_RING_PEEK_CALL_BH(&a->ring, __skb_array_len_with_tag);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_peek_len_any(काष्ठा skb_array *a)
अणु
	वापस PTR_RING_PEEK_CALL_ANY(&a->ring, __skb_array_len_with_tag);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_init(काष्ठा skb_array *a, पूर्णांक size, gfp_t gfp)
अणु
	वापस ptr_ring_init(&a->ring, size, gfp);
पूर्ण

अटल व्योम __skb_array_destroy_skb(व्योम *ptr)
अणु
	kमुक्त_skb(ptr);
पूर्ण

अटल अंतरभूत व्योम skb_array_unconsume(काष्ठा skb_array *a,
				       काष्ठा sk_buff **skbs, पूर्णांक n)
अणु
	ptr_ring_unconsume(&a->ring, (व्योम **)skbs, n, __skb_array_destroy_skb);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_resize(काष्ठा skb_array *a, पूर्णांक size, gfp_t gfp)
अणु
	वापस ptr_ring_resize(&a->ring, size, gfp, __skb_array_destroy_skb);
पूर्ण

अटल अंतरभूत पूर्णांक skb_array_resize_multiple(काष्ठा skb_array **rings,
					    पूर्णांक nrings, अचिन्हित पूर्णांक size,
					    gfp_t gfp)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा skb_array, ring));
	वापस ptr_ring_resize_multiple((काष्ठा ptr_ring **)rings,
					nrings, size, gfp,
					__skb_array_destroy_skb);
पूर्ण

अटल अंतरभूत व्योम skb_array_cleanup(काष्ठा skb_array *a)
अणु
	ptr_ring_cleanup(&a->ring, __skb_array_destroy_skb);
पूर्ण

#पूर्ण_अगर /* _LINUX_SKB_ARRAY_H  */
