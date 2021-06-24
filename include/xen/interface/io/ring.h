<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * ring.h
 *
 * Shared producer-consumer ring macros.
 *
 * Tim Deegan and Andrew Warfield November 2004.
 */

#अगर_अघोषित __XEN_PUBLIC_IO_RING_H__
#घोषणा __XEN_PUBLIC_IO_RING_H__

#समावेश <xen/पूर्णांकerface/grant_table.h>

प्रकार अचिन्हित पूर्णांक RING_IDX;

/* Round a 32-bit अचिन्हित स्थिरant करोwn to the nearest घातer of two. */
#घोषणा __RD2(_x)  (((_x) & 0x00000002) ? 0x2		       : ((_x) & 0x1))
#घोषणा __RD4(_x)  (((_x) & 0x0000000c) ? __RD2((_x)>>2)<<2    : __RD2(_x))
#घोषणा __RD8(_x)  (((_x) & 0x000000f0) ? __RD4((_x)>>4)<<4    : __RD4(_x))
#घोषणा __RD16(_x) (((_x) & 0x0000ff00) ? __RD8((_x)>>8)<<8    : __RD8(_x))
#घोषणा __RD32(_x) (((_x) & 0xffff0000) ? __RD16((_x)>>16)<<16 : __RD16(_x))

/*
 * Calculate size of a shared ring, given the total available space क्रम the
 * ring and indexes (_sz), and the name tag of the request/response काष्ठाure.
 * A ring contains as many entries as will fit, rounded करोwn to the nearest
 * घातer of two (so we can mask with (size-1) to loop around).
 */
#घोषणा __CONST_RING_SIZE(_s, _sz)				\
	(__RD32(((_sz) - दुरत्व(काष्ठा _s##_sring, ring)) /	\
		माप(((काष्ठा _s##_sring *)0)->ring[0])))

/*
 * The same क्रम passing in an actual poपूर्णांकer instead of a name tag.
 */
#घोषणा __RING_SIZE(_s, _sz)						\
	(__RD32(((_sz) - (दीर्घ)&(_s)->ring + (दीर्घ)(_s)) / माप((_s)->ring[0])))

/*
 * Macros to make the correct C datatypes क्रम a new kind of ring.
 *
 * To make a new ring datatype, you need to have two message काष्ठाures,
 * let's say काष्ठा request, and काष्ठा response alपढ़ोy defined.
 *
 * In a header where you want the ring datatype declared, you then करो:
 *
 *     DEFINE_RING_TYPES(mytag, काष्ठा request, काष्ठा response);
 *
 * These expand out to give you a set of types, as you can see below.
 * The most important of these are:
 *
 *     काष्ठा mytag_sring      - The shared ring.
 *     काष्ठा mytag_front_ring - The 'front' half of the ring.
 *     काष्ठा mytag_back_ring  - The 'back' half of the ring.
 *
 * To initialize a ring in your code you need to know the location and size
 * of the shared memory area (PAGE_SIZE, क्रम instance). To initialise
 * the front half:
 *
 *     काष्ठा mytag_front_ring front_ring;
 *     SHARED_RING_INIT((काष्ठा mytag_sring *)shared_page);
 *     FRONT_RING_INIT(&front_ring, (काष्ठा mytag_sring *)shared_page,
 *		       PAGE_SIZE);
 *
 * Initializing the back follows similarly (note that only the front
 * initializes the shared ring):
 *
 *     काष्ठा mytag_back_ring back_ring;
 *     BACK_RING_INIT(&back_ring, (काष्ठा mytag_sring *)shared_page,
 *		      PAGE_SIZE);
 */

#घोषणा DEFINE_RING_TYPES(__name, __req_t, __rsp_t)			\
									\
/* Shared ring entry */							\
जोड़ __name##_sring_entry अणु						\
    __req_t req;							\
    __rsp_t rsp;							\
पूर्ण;									\
									\
/* Shared ring page */							\
काष्ठा __name##_sring अणु							\
    RING_IDX req_prod, req_event;					\
    RING_IDX rsp_prod, rsp_event;					\
    uपूर्णांक8_t  pad[48];							\
    जोड़ __name##_sring_entry ring[1]; /* variable-length */		\
पूर्ण;									\
									\
/* "Front" end's निजी variables */					\
काष्ठा __name##_front_ring अणु						\
    RING_IDX req_prod_pvt;						\
    RING_IDX rsp_cons;							\
    अचिन्हित पूर्णांक nr_ents;						\
    काष्ठा __name##_sring *sring;					\
पूर्ण;									\
									\
/* "Back" end's निजी variables */					\
काष्ठा __name##_back_ring अणु						\
    RING_IDX rsp_prod_pvt;						\
    RING_IDX req_cons;							\
    अचिन्हित पूर्णांक nr_ents;						\
    काष्ठा __name##_sring *sring;					\
पूर्ण;

/*
 * Macros क्रम manipulating rings.
 *
 * FRONT_RING_whatever works on the "front end" of a ring: here
 * requests are pushed on to the ring and responses taken off it.
 *
 * BACK_RING_whatever works on the "back end" of a ring: here
 * requests are taken off the ring and responses put on.
 *
 * N.B. these macros करो NO INTERLOCKS OR FLOW CONTROL.
 * This is OK in 1-क्रम-1 request-response situations where the
 * requestor (front end) never has more than RING_SIZE()-1
 * outstanding requests.
 */

/* Initialising empty rings */
#घोषणा SHARED_RING_INIT(_s) करो अणु					\
    (_s)->req_prod  = (_s)->rsp_prod  = 0;				\
    (_s)->req_event = (_s)->rsp_event = 1;				\
    स_रखो((_s)->pad, 0, माप((_s)->pad));				\
पूर्ण जबतक(0)

#घोषणा FRONT_RING_ATTACH(_r, _s, _i, __size) करो अणु			\
    (_r)->req_prod_pvt = (_i);						\
    (_r)->rsp_cons = (_i);						\
    (_r)->nr_ents = __RING_SIZE(_s, __size);				\
    (_r)->sring = (_s);							\
पूर्ण जबतक (0)

#घोषणा FRONT_RING_INIT(_r, _s, __size) FRONT_RING_ATTACH(_r, _s, 0, __size)

#घोषणा BACK_RING_ATTACH(_r, _s, _i, __size) करो अणु			\
    (_r)->rsp_prod_pvt = (_i);						\
    (_r)->req_cons = (_i);						\
    (_r)->nr_ents = __RING_SIZE(_s, __size);				\
    (_r)->sring = (_s);							\
पूर्ण जबतक (0)

#घोषणा BACK_RING_INIT(_r, _s, __size) BACK_RING_ATTACH(_r, _s, 0, __size)

/* How big is this ring? */
#घोषणा RING_SIZE(_r)							\
    ((_r)->nr_ents)

/* Number of मुक्त requests (क्रम use on front side only). */
#घोषणा RING_FREE_REQUESTS(_r)						\
    (RING_SIZE(_r) - ((_r)->req_prod_pvt - (_r)->rsp_cons))

/* Test अगर there is an empty slot available on the front ring.
 * (This is only meaningful from the front. )
 */
#घोषणा RING_FULL(_r)							\
    (RING_FREE_REQUESTS(_r) == 0)

/* Test अगर there are outstanding messages to be processed on a ring. */
#घोषणा RING_HAS_UNCONSUMED_RESPONSES(_r)				\
    ((_r)->sring->rsp_prod - (_r)->rsp_cons)

#घोषणा RING_HAS_UNCONSUMED_REQUESTS(_r)				\
    (अणु									\
	अचिन्हित पूर्णांक req = (_r)->sring->req_prod - (_r)->req_cons;	\
	अचिन्हित पूर्णांक rsp = RING_SIZE(_r) -				\
			   ((_r)->req_cons - (_r)->rsp_prod_pvt);	\
	req < rsp ? req : rsp;						\
    पूर्ण)

/* Direct access to inभागidual ring elements, by index. */
#घोषणा RING_GET_REQUEST(_r, _idx)					\
    (&((_r)->sring->ring[((_idx) & (RING_SIZE(_r) - 1))].req))

/*
 * Get a local copy of a request.
 *
 * Use this in preference to RING_GET_REQUEST() so all processing is
 * करोne on a local copy that cannot be modअगरied by the other end.
 *
 * Note that https://gcc.gnu.org/bugzilla/show_bug.cgi?id=58145 may cause this
 * to be ineffective where _req is a काष्ठा which consists of only bitfields.
 */
#घोषणा RING_COPY_REQUEST(_r, _idx, _req) करो अणु				\
	/* Use अस्थिर to क्रमce the copy पूर्णांकo _req. */			\
	*(_req) = *(अस्थिर typeof(_req))RING_GET_REQUEST(_r, _idx);	\
पूर्ण जबतक (0)

#घोषणा RING_GET_RESPONSE(_r, _idx)					\
    (&((_r)->sring->ring[((_idx) & (RING_SIZE(_r) - 1))].rsp))

/* Loop termination condition: Would the specअगरied index overflow the ring? */
#घोषणा RING_REQUEST_CONS_OVERFLOW(_r, _cons)				\
    (((_cons) - (_r)->rsp_prod_pvt) >= RING_SIZE(_r))

/* Ill-behaved frontend determination: Can there be this many requests? */
#घोषणा RING_REQUEST_PROD_OVERFLOW(_r, _prod)               \
    (((_prod) - (_r)->rsp_prod_pvt) > RING_SIZE(_r))


#घोषणा RING_PUSH_REQUESTS(_r) करो अणु					\
    virt_wmb(); /* back sees requests /beक्रमe/ updated producer index */	\
    (_r)->sring->req_prod = (_r)->req_prod_pvt;				\
पूर्ण जबतक (0)

#घोषणा RING_PUSH_RESPONSES(_r) करो अणु					\
    virt_wmb(); /* front sees responses /beक्रमe/ updated producer index */	\
    (_r)->sring->rsp_prod = (_r)->rsp_prod_pvt;				\
पूर्ण जबतक (0)

/*
 * Notअगरication hold-off (req_event and rsp_event):
 *
 * When queueing requests or responses on a shared ring, it may not always be
 * necessary to notअगरy the remote end. For example, अगर requests are in flight
 * in a backend, the front may be able to queue further requests without
 * notअगरying the back (अगर the back checks क्रम new requests when it queues
 * responses).
 *
 * When enqueuing requests or responses:
 *
 *  Use RING_PUSH_अणुREQUESTS,RESPONSESपूर्ण_AND_CHECK_NOTIFY(). The second argument
 *  is a boolean वापस value. True indicates that the receiver requires an
 *  asynchronous notअगरication.
 *
 * After dequeuing requests or responses (beक्रमe sleeping the connection):
 *
 *  Use RING_FINAL_CHECK_FOR_REQUESTS() or RING_FINAL_CHECK_FOR_RESPONSES().
 *  The second argument is a boolean वापस value. True indicates that there
 *  are pending messages on the ring (i.e., the connection should not be put
 *  to sleep).
 *
 *  These macros will set the req_event/rsp_event field to trigger a
 *  notअगरication on the very next message that is enqueued. If you want to
 *  create batches of work (i.e., only receive a notअगरication after several
 *  messages have been enqueued) then you will need to create a customised
 *  version of the FINAL_CHECK macro in your own code, which sets the event
 *  field appropriately.
 */

#घोषणा RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(_r, _notअगरy) करो अणु		\
    RING_IDX __old = (_r)->sring->req_prod;				\
    RING_IDX __new = (_r)->req_prod_pvt;				\
    virt_wmb(); /* back sees requests /beक्रमe/ updated producer index */	\
    (_r)->sring->req_prod = __new;					\
    virt_mb(); /* back sees new requests /beक्रमe/ we check req_event */	\
    (_notअगरy) = ((RING_IDX)(__new - (_r)->sring->req_event) <		\
		 (RING_IDX)(__new - __old));				\
पूर्ण जबतक (0)

#घोषणा RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(_r, _notअगरy) करो अणु		\
    RING_IDX __old = (_r)->sring->rsp_prod;				\
    RING_IDX __new = (_r)->rsp_prod_pvt;				\
    virt_wmb(); /* front sees responses /beक्रमe/ updated producer index */	\
    (_r)->sring->rsp_prod = __new;					\
    virt_mb(); /* front sees new responses /beक्रमe/ we check rsp_event */	\
    (_notअगरy) = ((RING_IDX)(__new - (_r)->sring->rsp_event) <		\
		 (RING_IDX)(__new - __old));				\
पूर्ण जबतक (0)

#घोषणा RING_FINAL_CHECK_FOR_REQUESTS(_r, _work_to_करो) करो अणु		\
    (_work_to_करो) = RING_HAS_UNCONSUMED_REQUESTS(_r);			\
    अगर (_work_to_करो) अवरोध;						\
    (_r)->sring->req_event = (_r)->req_cons + 1;			\
    virt_mb();								\
    (_work_to_करो) = RING_HAS_UNCONSUMED_REQUESTS(_r);			\
पूर्ण जबतक (0)

#घोषणा RING_FINAL_CHECK_FOR_RESPONSES(_r, _work_to_करो) करो अणु		\
    (_work_to_करो) = RING_HAS_UNCONSUMED_RESPONSES(_r);			\
    अगर (_work_to_करो) अवरोध;						\
    (_r)->sring->rsp_event = (_r)->rsp_cons + 1;			\
    virt_mb();								\
    (_work_to_करो) = RING_HAS_UNCONSUMED_RESPONSES(_r);			\
पूर्ण जबतक (0)


/*
 * DEFINE_XEN_FLEX_RING_AND_INTF defines two monodirectional rings and
 * functions to check अगर there is data on the ring, and to पढ़ो and
 * ग_लिखो to them.
 *
 * DEFINE_XEN_FLEX_RING is similar to DEFINE_XEN_FLEX_RING_AND_INTF, but
 * करोes not define the indexes page. As dअगरferent protocols can have
 * extensions to the basic क्रमmat, this macro allow them to define their
 * own काष्ठा.
 *
 * XEN_FLEX_RING_SIZE
 *   Convenience macro to calculate the size of one of the two rings
 *   from the overall order.
 *
 * $NAME_mask
 *   Function to apply the size mask to an index, to reduce the index
 *   within the range [0-size].
 *
 * $NAME_पढ़ो_packet
 *   Function to पढ़ो data from the ring. The amount of data to पढ़ो is
 *   specअगरied by the "size" argument.
 *
 * $NAME_ग_लिखो_packet
 *   Function to ग_लिखो data to the ring. The amount of data to ग_लिखो is
 *   specअगरied by the "size" argument.
 *
 * $NAME_get_ring_ptr
 *   Convenience function that वापसs a poपूर्णांकer to पढ़ो/ग_लिखो to the
 *   ring at the right location.
 *
 * $NAME_data_पूर्णांकf
 *   Indexes page, shared between frontend and backend. It also
 *   contains the array of grant refs.
 *
 * $NAME_queued
 *   Function to calculate how many bytes are currently on the ring,
 *   पढ़ोy to be पढ़ो. It can also be used to calculate how much मुक्त
 *   space is currently on the ring (XEN_FLEX_RING_SIZE() -
 *   $NAME_queued()).
 */

#अगर_अघोषित XEN_PAGE_SHIFT
/* The PAGE_SIZE क्रम ring protocols and hypercall पूर्णांकerfaces is always
 * 4K, regardless of the architecture, and page granularity chosen by
 * operating प्रणालीs.
 */
#घोषणा XEN_PAGE_SHIFT 12
#पूर्ण_अगर
#घोषणा XEN_FLEX_RING_SIZE(order)                                             \
    (1UL << ((order) + XEN_PAGE_SHIFT - 1))

#घोषणा DEFINE_XEN_FLEX_RING(name)                                            \
अटल अंतरभूत RING_IDX name##_mask(RING_IDX idx, RING_IDX ring_size)          \
अणु                                                                             \
    वापस idx & (ring_size - 1);                                             \
पूर्ण                                                                             \
                                                                              \
अटल अंतरभूत अचिन्हित अक्षर *name##_get_ring_ptr(अचिन्हित अक्षर *buf,          \
                                                 RING_IDX idx,                \
                                                 RING_IDX ring_size)          \
अणु                                                                             \
    वापस buf + name##_mask(idx, ring_size);                                 \
पूर्ण                                                                             \
                                                                              \
अटल अंतरभूत व्योम name##_पढ़ो_packet(व्योम *opaque,                           \
                                      स्थिर अचिन्हित अक्षर *buf,               \
                                      माप_प्रकार size,                            \
                                      RING_IDX masked_prod,                   \
                                      RING_IDX *masked_cons,                  \
                                      RING_IDX ring_size)                     \
अणु                                                                             \
    अगर (*masked_cons < masked_prod ||                                         \
        size <= ring_size - *masked_cons) अणु                                   \
        स_नकल(opaque, buf + *masked_cons, size);                             \
    पूर्ण अन्यथा अणु                                                                  \
        स_नकल(opaque, buf + *masked_cons, ring_size - *masked_cons);         \
        स_नकल((अचिन्हित अक्षर *)opaque + ring_size - *masked_cons, buf,       \
               size - (ring_size - *masked_cons));                            \
    पूर्ण                                                                         \
    *masked_cons = name##_mask(*masked_cons + size, ring_size);               \
पूर्ण                                                                             \
                                                                              \
अटल अंतरभूत व्योम name##_ग_लिखो_packet(अचिन्हित अक्षर *buf,                    \
                                       स्थिर व्योम *opaque,                    \
                                       माप_प्रकार size,                           \
                                       RING_IDX *masked_prod,                 \
                                       RING_IDX masked_cons,                  \
                                       RING_IDX ring_size)                    \
अणु                                                                             \
    अगर (*masked_prod < masked_cons ||                                         \
        size <= ring_size - *masked_prod) अणु                                   \
        स_नकल(buf + *masked_prod, opaque, size);                             \
    पूर्ण अन्यथा अणु                                                                  \
        स_नकल(buf + *masked_prod, opaque, ring_size - *masked_prod);         \
        स_नकल(buf, (अचिन्हित अक्षर *)opaque + (ring_size - *masked_prod),     \
               size - (ring_size - *masked_prod));                            \
    पूर्ण                                                                         \
    *masked_prod = name##_mask(*masked_prod + size, ring_size);               \
पूर्ण                                                                             \
                                                                              \
अटल अंतरभूत RING_IDX name##_queued(RING_IDX prod,                           \
                                     RING_IDX cons,                           \
                                     RING_IDX ring_size)                      \
अणु                                                                             \
    RING_IDX size;                                                            \
                                                                              \
    अगर (prod == cons)                                                         \
        वापस 0;                                                             \
                                                                              \
    prod = name##_mask(prod, ring_size);                                      \
    cons = name##_mask(cons, ring_size);                                      \
                                                                              \
    अगर (prod == cons)                                                         \
        वापस ring_size;                                                     \
                                                                              \
    अगर (prod > cons)                                                          \
        size = prod - cons;                                                   \
    अन्यथा                                                                      \
        size = ring_size - (cons - prod);                                     \
    वापस size;                                                              \
पूर्ण                                                                             \
                                                                              \
काष्ठा name##_data अणु                                                          \
    अचिन्हित अक्षर *in; /* half of the allocation */                           \
    अचिन्हित अक्षर *out; /* half of the allocation */                          \
पूर्ण

#घोषणा DEFINE_XEN_FLEX_RING_AND_INTF(name)                                   \
काष्ठा name##_data_पूर्णांकf अणु                                                     \
    RING_IDX in_cons, in_prod;                                                \
                                                                              \
    uपूर्णांक8_t pad1[56];                                                         \
                                                                              \
    RING_IDX out_cons, out_prod;                                              \
                                                                              \
    uपूर्णांक8_t pad2[56];                                                         \
                                                                              \
    RING_IDX ring_order;                                                      \
    grant_ref_t ref[];                                                        \
पूर्ण;                                                                            \
DEFINE_XEN_FLEX_RING(name)

#पूर्ण_अगर /* __XEN_PUBLIC_IO_RING_H__ */
