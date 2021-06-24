<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */

/*
 * AF_XDP user-space access library.
 *
 * Copyright (c) 2018 - 2019 Intel Corporation.
 * Copyright (c) 2019 Facebook
 *
 * Author(s): Magnus Karlsson <magnus.karlsson@पूर्णांकel.com>
 */

#अगर_अघोषित __LIBBPF_XSK_H
#घोषणा __LIBBPF_XSK_H

#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <linux/अगर_xdp.h>

#समावेश "libbpf.h"

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

/* Load-Acquire Store-Release barriers used by the XDP socket
 * library. The following macros should *NOT* be considered part of
 * the xsk.h API, and is subject to change anyसमय.
 *
 * LIBRARY INTERNAL
 */

#घोषणा __XSK_READ_ONCE(x) (*(अस्थिर typeof(x) *)&x)
#घोषणा __XSK_WRITE_ONCE(x, v) (*(अस्थिर typeof(x) *)&x) = (v)

#अगर defined(__i386__) || defined(__x86_64__)
# define libbpf_smp_store_release(p, v)					\
	करो अणु								\
		यंत्र अस्थिर("" : : : "memory");			\
		__XSK_WRITE_ONCE(*p, v);				\
	पूर्ण जबतक (0)
# define libbpf_smp_load_acquire(p)					\
	(अणु								\
		typeof(*p) ___p1 = __XSK_READ_ONCE(*p);			\
		यंत्र अस्थिर("" : : : "memory");			\
		___p1;							\
	पूर्ण)
#या_अगर defined(__aarch64__)
# define libbpf_smp_store_release(p, v)					\
		यंत्र अस्थिर ("stlr %w1, %0" : "=Q" (*p) : "r" (v) : "memory")
# define libbpf_smp_load_acquire(p)					\
	(अणु								\
		typeof(*p) ___p1;					\
		यंत्र अस्थिर ("ldar %w0, %1"				\
			      : "=r" (___p1) : "Q" (*p) : "memory");	\
		___p1;							\
	पूर्ण)
#या_अगर defined(__riscv)
# define libbpf_smp_store_release(p, v)					\
	करो अणु								\
		यंत्र अस्थिर ("fence rw,w" : : : "memory");		\
		__XSK_WRITE_ONCE(*p, v);				\
	पूर्ण जबतक (0)
# define libbpf_smp_load_acquire(p)					\
	(अणु								\
		typeof(*p) ___p1 = __XSK_READ_ONCE(*p);			\
		यंत्र अस्थिर ("fence r,rw" : : : "memory");		\
		___p1;							\
	पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित libbpf_smp_store_release
#घोषणा libbpf_smp_store_release(p, v)					\
	करो अणु								\
		__sync_synchronize();					\
		__XSK_WRITE_ONCE(*p, v);				\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित libbpf_smp_load_acquire
#घोषणा libbpf_smp_load_acquire(p)					\
	(अणु								\
		typeof(*p) ___p1 = __XSK_READ_ONCE(*p);			\
		__sync_synchronize();					\
		___p1;							\
	पूर्ण)
#पूर्ण_अगर

/* LIBRARY INTERNAL -- END */

/* Do not access these members directly. Use the functions below. */
#घोषणा DEFINE_XSK_RING(name) \
काष्ठा name अणु \
	__u32 cached_prod; \
	__u32 cached_cons; \
	__u32 mask; \
	__u32 size; \
	__u32 *producer; \
	__u32 *consumer; \
	व्योम *ring; \
	__u32 *flags; \
पूर्ण

DEFINE_XSK_RING(xsk_ring_prod);
DEFINE_XSK_RING(xsk_ring_cons);

/* For a detailed explanation on the memory barriers associated with the
 * ring, please take a look at net/xdp/xsk_queue.h.
 */

काष्ठा xsk_umem;
काष्ठा xsk_socket;

अटल अंतरभूत __u64 *xsk_ring_prod__fill_addr(काष्ठा xsk_ring_prod *fill,
					      __u32 idx)
अणु
	__u64 *addrs = (__u64 *)fill->ring;

	वापस &addrs[idx & fill->mask];
पूर्ण

अटल अंतरभूत स्थिर __u64 *
xsk_ring_cons__comp_addr(स्थिर काष्ठा xsk_ring_cons *comp, __u32 idx)
अणु
	स्थिर __u64 *addrs = (स्थिर __u64 *)comp->ring;

	वापस &addrs[idx & comp->mask];
पूर्ण

अटल अंतरभूत काष्ठा xdp_desc *xsk_ring_prod__tx_desc(काष्ठा xsk_ring_prod *tx,
						      __u32 idx)
अणु
	काष्ठा xdp_desc *descs = (काष्ठा xdp_desc *)tx->ring;

	वापस &descs[idx & tx->mask];
पूर्ण

अटल अंतरभूत स्थिर काष्ठा xdp_desc *
xsk_ring_cons__rx_desc(स्थिर काष्ठा xsk_ring_cons *rx, __u32 idx)
अणु
	स्थिर काष्ठा xdp_desc *descs = (स्थिर काष्ठा xdp_desc *)rx->ring;

	वापस &descs[idx & rx->mask];
पूर्ण

अटल अंतरभूत पूर्णांक xsk_ring_prod__needs_wakeup(स्थिर काष्ठा xsk_ring_prod *r)
अणु
	वापस *r->flags & XDP_RING_NEED_WAKEUP;
पूर्ण

अटल अंतरभूत __u32 xsk_prod_nb_मुक्त(काष्ठा xsk_ring_prod *r, __u32 nb)
अणु
	__u32 मुक्त_entries = r->cached_cons - r->cached_prod;

	अगर (मुक्त_entries >= nb)
		वापस मुक्त_entries;

	/* Refresh the local tail poपूर्णांकer.
	 * cached_cons is r->size bigger than the real consumer poपूर्णांकer so
	 * that this addition can be aव्योमed in the more frequently
	 * executed code that comमाला_दो मुक्त_entries in the beginning of
	 * this function. Without this optimization it whould have been
	 * मुक्त_entries = r->cached_prod - r->cached_cons + r->size.
	 */
	r->cached_cons = libbpf_smp_load_acquire(r->consumer);
	r->cached_cons += r->size;

	वापस r->cached_cons - r->cached_prod;
पूर्ण

अटल अंतरभूत __u32 xsk_cons_nb_avail(काष्ठा xsk_ring_cons *r, __u32 nb)
अणु
	__u32 entries = r->cached_prod - r->cached_cons;

	अगर (entries == 0) अणु
		r->cached_prod = libbpf_smp_load_acquire(r->producer);
		entries = r->cached_prod - r->cached_cons;
	पूर्ण

	वापस (entries > nb) ? nb : entries;
पूर्ण

अटल अंतरभूत __u32 xsk_ring_prod__reserve(काष्ठा xsk_ring_prod *prod, __u32 nb, __u32 *idx)
अणु
	अगर (xsk_prod_nb_मुक्त(prod, nb) < nb)
		वापस 0;

	*idx = prod->cached_prod;
	prod->cached_prod += nb;

	वापस nb;
पूर्ण

अटल अंतरभूत व्योम xsk_ring_prod__submit(काष्ठा xsk_ring_prod *prod, __u32 nb)
अणु
	/* Make sure everything has been written to the ring beक्रमe indicating
	 * this to the kernel by writing the producer poपूर्णांकer.
	 */
	libbpf_smp_store_release(prod->producer, *prod->producer + nb);
पूर्ण

अटल अंतरभूत __u32 xsk_ring_cons__peek(काष्ठा xsk_ring_cons *cons, __u32 nb, __u32 *idx)
अणु
	__u32 entries = xsk_cons_nb_avail(cons, nb);

	अगर (entries > 0) अणु
		*idx = cons->cached_cons;
		cons->cached_cons += entries;
	पूर्ण

	वापस entries;
पूर्ण

अटल अंतरभूत व्योम xsk_ring_cons__cancel(काष्ठा xsk_ring_cons *cons, __u32 nb)
अणु
	cons->cached_cons -= nb;
पूर्ण

अटल अंतरभूत व्योम xsk_ring_cons__release(काष्ठा xsk_ring_cons *cons, __u32 nb)
अणु
	/* Make sure data has been पढ़ो beक्रमe indicating we are करोne
	 * with the entries by updating the consumer poपूर्णांकer.
	 */
	libbpf_smp_store_release(cons->consumer, *cons->consumer + nb);

पूर्ण

अटल अंतरभूत व्योम *xsk_umem__get_data(व्योम *umem_area, __u64 addr)
अणु
	वापस &((अक्षर *)umem_area)[addr];
पूर्ण

अटल अंतरभूत __u64 xsk_umem__extract_addr(__u64 addr)
अणु
	वापस addr & XSK_UNALIGNED_BUF_ADDR_MASK;
पूर्ण

अटल अंतरभूत __u64 xsk_umem__extract_offset(__u64 addr)
अणु
	वापस addr >> XSK_UNALIGNED_BUF_OFFSET_SHIFT;
पूर्ण

अटल अंतरभूत __u64 xsk_umem__add_offset_to_addr(__u64 addr)
अणु
	वापस xsk_umem__extract_addr(addr) + xsk_umem__extract_offset(addr);
पूर्ण

LIBBPF_API पूर्णांक xsk_umem__fd(स्थिर काष्ठा xsk_umem *umem);
LIBBPF_API पूर्णांक xsk_socket__fd(स्थिर काष्ठा xsk_socket *xsk);

#घोषणा XSK_RING_CONS__DEFAULT_NUM_DESCS      2048
#घोषणा XSK_RING_PROD__DEFAULT_NUM_DESCS      2048
#घोषणा XSK_UMEM__DEFAULT_FRAME_SHIFT    12 /* 4096 bytes */
#घोषणा XSK_UMEM__DEFAULT_FRAME_SIZE     (1 << XSK_UMEM__DEFAULT_FRAME_SHIFT)
#घोषणा XSK_UMEM__DEFAULT_FRAME_HEADROOM 0
#घोषणा XSK_UMEM__DEFAULT_FLAGS 0

काष्ठा xsk_umem_config अणु
	__u32 fill_size;
	__u32 comp_size;
	__u32 frame_size;
	__u32 frame_headroom;
	__u32 flags;
पूर्ण;

LIBBPF_API पूर्णांक xsk_setup_xdp_prog(पूर्णांक अगरindex,
				  पूर्णांक *xsks_map_fd);
LIBBPF_API पूर्णांक xsk_socket__update_xskmap(काष्ठा xsk_socket *xsk,
					 पूर्णांक xsks_map_fd);

/* Flags क्रम the libbpf_flags field. */
#घोषणा XSK_LIBBPF_FLAGS__INHIBIT_PROG_LOAD (1 << 0)

काष्ठा xsk_socket_config अणु
	__u32 rx_size;
	__u32 tx_size;
	__u32 libbpf_flags;
	__u32 xdp_flags;
	__u16 bind_flags;
पूर्ण;

/* Set config to शून्य to get the शेष configuration. */
LIBBPF_API पूर्णांक xsk_umem__create(काष्ठा xsk_umem **umem,
				व्योम *umem_area, __u64 size,
				काष्ठा xsk_ring_prod *fill,
				काष्ठा xsk_ring_cons *comp,
				स्थिर काष्ठा xsk_umem_config *config);
LIBBPF_API पूर्णांक xsk_umem__create_v0_0_2(काष्ठा xsk_umem **umem,
				       व्योम *umem_area, __u64 size,
				       काष्ठा xsk_ring_prod *fill,
				       काष्ठा xsk_ring_cons *comp,
				       स्थिर काष्ठा xsk_umem_config *config);
LIBBPF_API पूर्णांक xsk_umem__create_v0_0_4(काष्ठा xsk_umem **umem,
				       व्योम *umem_area, __u64 size,
				       काष्ठा xsk_ring_prod *fill,
				       काष्ठा xsk_ring_cons *comp,
				       स्थिर काष्ठा xsk_umem_config *config);
LIBBPF_API पूर्णांक xsk_socket__create(काष्ठा xsk_socket **xsk,
				  स्थिर अक्षर *अगरname, __u32 queue_id,
				  काष्ठा xsk_umem *umem,
				  काष्ठा xsk_ring_cons *rx,
				  काष्ठा xsk_ring_prod *tx,
				  स्थिर काष्ठा xsk_socket_config *config);
LIBBPF_API पूर्णांक
xsk_socket__create_shared(काष्ठा xsk_socket **xsk_ptr,
			  स्थिर अक्षर *अगरname,
			  __u32 queue_id, काष्ठा xsk_umem *umem,
			  काष्ठा xsk_ring_cons *rx,
			  काष्ठा xsk_ring_prod *tx,
			  काष्ठा xsk_ring_prod *fill,
			  काष्ठा xsk_ring_cons *comp,
			  स्थिर काष्ठा xsk_socket_config *config);

/* Returns 0 क्रम success and -EBUSY अगर the umem is still in use. */
LIBBPF_API पूर्णांक xsk_umem__delete(काष्ठा xsk_umem *umem);
LIBBPF_API व्योम xsk_socket__delete(काष्ठा xsk_socket *xsk);

#अगर_घोषित __cplusplus
पूर्ण /* बाह्य "C" */
#पूर्ण_अगर

#पूर्ण_अगर /* __LIBBPF_XSK_H */
