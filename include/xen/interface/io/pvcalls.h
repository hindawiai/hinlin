<शैली गुरु>
#अगर_अघोषित __XEN_PUBLIC_IO_XEN_PVCALLS_H__
#घोषणा __XEN_PUBLIC_IO_XEN_PVCALLS_H__

#समावेश <linux/net.h>
#समावेश <xen/पूर्णांकerface/io/ring.h>
#समावेश <xen/पूर्णांकerface/grant_table.h>

/* "1" means socket, connect, release, bind, listen, accept and poll */
#घोषणा XENBUS_FUNCTIONS_CALLS "1"

/*
 * See करोcs/misc/pvcalls.markकरोwn in xen.git क्रम the full specअगरication:
 * https://xenbits.xen.org/करोcs/unstable/misc/pvcalls.hपंचांगl
 */
काष्ठा pvcalls_data_पूर्णांकf अणु
    RING_IDX in_cons, in_prod, in_error;

    uपूर्णांक8_t pad1[52];

    RING_IDX out_cons, out_prod, out_error;

    uपूर्णांक8_t pad2[52];

    RING_IDX ring_order;
    grant_ref_t ref[];
पूर्ण;
DEFINE_XEN_FLEX_RING(pvcalls);

#घोषणा PVCALLS_SOCKET         0
#घोषणा PVCALLS_CONNECT        1
#घोषणा PVCALLS_RELEASE        2
#घोषणा PVCALLS_BIND           3
#घोषणा PVCALLS_LISTEN         4
#घोषणा PVCALLS_ACCEPT         5
#घोषणा PVCALLS_POLL           6

काष्ठा xen_pvcalls_request अणु
    uपूर्णांक32_t req_id; /* निजी to guest, echoed in response */
    uपूर्णांक32_t cmd;    /* command to execute */
    जोड़ अणु
        काष्ठा xen_pvcalls_socket अणु
            uपूर्णांक64_t id;
            uपूर्णांक32_t करोमुख्य;
            uपूर्णांक32_t type;
            uपूर्णांक32_t protocol;
        पूर्ण socket;
        काष्ठा xen_pvcalls_connect अणु
            uपूर्णांक64_t id;
            uपूर्णांक8_t addr[28];
            uपूर्णांक32_t len;
            uपूर्णांक32_t flags;
            grant_ref_t ref;
            uपूर्णांक32_t evtchn;
        पूर्ण connect;
        काष्ठा xen_pvcalls_release अणु
            uपूर्णांक64_t id;
            uपूर्णांक8_t reuse;
        पूर्ण release;
        काष्ठा xen_pvcalls_bind अणु
            uपूर्णांक64_t id;
            uपूर्णांक8_t addr[28];
            uपूर्णांक32_t len;
        पूर्ण bind;
        काष्ठा xen_pvcalls_listen अणु
            uपूर्णांक64_t id;
            uपूर्णांक32_t backlog;
        पूर्ण listen;
        काष्ठा xen_pvcalls_accept अणु
            uपूर्णांक64_t id;
            uपूर्णांक64_t id_new;
            grant_ref_t ref;
            uपूर्णांक32_t evtchn;
        पूर्ण accept;
        काष्ठा xen_pvcalls_poll अणु
            uपूर्णांक64_t id;
        पूर्ण poll;
        /* dummy member to क्रमce माप(काष्ठा xen_pvcalls_request)
         * to match across archs */
        काष्ठा xen_pvcalls_dummy अणु
            uपूर्णांक8_t dummy[56];
        पूर्ण dummy;
    पूर्ण u;
पूर्ण;

काष्ठा xen_pvcalls_response अणु
    uपूर्णांक32_t req_id;
    uपूर्णांक32_t cmd;
    पूर्णांक32_t ret;
    uपूर्णांक32_t pad;
    जोड़ अणु
        काष्ठा _xen_pvcalls_socket अणु
            uपूर्णांक64_t id;
        पूर्ण socket;
        काष्ठा _xen_pvcalls_connect अणु
            uपूर्णांक64_t id;
        पूर्ण connect;
        काष्ठा _xen_pvcalls_release अणु
            uपूर्णांक64_t id;
        पूर्ण release;
        काष्ठा _xen_pvcalls_bind अणु
            uपूर्णांक64_t id;
        पूर्ण bind;
        काष्ठा _xen_pvcalls_listen अणु
            uपूर्णांक64_t id;
        पूर्ण listen;
        काष्ठा _xen_pvcalls_accept अणु
            uपूर्णांक64_t id;
        पूर्ण accept;
        काष्ठा _xen_pvcalls_poll अणु
            uपूर्णांक64_t id;
        पूर्ण poll;
        काष्ठा _xen_pvcalls_dummy अणु
            uपूर्णांक8_t dummy[8];
        पूर्ण dummy;
    पूर्ण u;
पूर्ण;

DEFINE_RING_TYPES(xen_pvcalls, काष्ठा xen_pvcalls_request,
                  काष्ठा xen_pvcalls_response);

#पूर्ण_अगर
