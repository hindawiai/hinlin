<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Copyright 2020-2021 NXP Semiconductors
 */
#समावेश <net/devlink.h>
#समावेश "ocelot.h"

/* The queue प्रणाली tracks four resource consumptions:
 * Resource 0: Memory tracked per source port
 * Resource 1: Frame references tracked per source port
 * Resource 2: Memory tracked per destination port
 * Resource 3: Frame references tracked per destination port
 */
#घोषणा OCELOT_RESOURCE_SZ		256
#घोषणा OCELOT_NUM_RESOURCES		4

#घोषणा BUF_xxxx_I			(0 * OCELOT_RESOURCE_SZ)
#घोषणा REF_xxxx_I			(1 * OCELOT_RESOURCE_SZ)
#घोषणा BUF_xxxx_E			(2 * OCELOT_RESOURCE_SZ)
#घोषणा REF_xxxx_E			(3 * OCELOT_RESOURCE_SZ)

/* For each resource type there are 4 types of watermarks:
 * Q_RSRV: reservation per QoS class per port
 * PRIO_SHR: sharing watermark per QoS class across all ports
 * P_RSRV: reservation per port
 * COL_SHR: sharing watermark per color (drop precedence) across all ports
 */
#घोषणा xxx_Q_RSRV_x			0
#घोषणा xxx_PRIO_SHR_x			216
#घोषणा xxx_P_RSRV_x			224
#घोषणा xxx_COL_SHR_x			254

/* Reservation Watermarks
 * ----------------------
 *
 * For setting up the reserved areas, egress watermarks exist per port and per
 * QoS class क्रम both ingress and egress.
 */

/*  Amount of packet buffer
 *  |  per QoS class
 *  |  |  reserved
 *  |  |  |   per egress port
 *  |  |  |   |
 *  V  V  v   v
 * BUF_Q_RSRV_E
 */
#घोषणा BUF_Q_RSRV_E(port, prio) \
	(BUF_xxxx_E + xxx_Q_RSRV_x + OCELOT_NUM_TC * (port) + (prio))

/*  Amount of packet buffer
 *  |  क्रम all port's traffic classes
 *  |  |  reserved
 *  |  |  |   per egress port
 *  |  |  |   |
 *  V  V  v   v
 * BUF_P_RSRV_E
 */
#घोषणा BUF_P_RSRV_E(port) \
	(BUF_xxxx_E + xxx_P_RSRV_x + (port))

/*  Amount of packet buffer
 *  |  per QoS class
 *  |  |  reserved
 *  |  |  |   per ingress port
 *  |  |  |   |
 *  V  V  v   v
 * BUF_Q_RSRV_I
 */
#घोषणा BUF_Q_RSRV_I(port, prio) \
	(BUF_xxxx_I + xxx_Q_RSRV_x + OCELOT_NUM_TC * (port) + (prio))

/*  Amount of packet buffer
 *  |  क्रम all port's traffic classes
 *  |  |  reserved
 *  |  |  |   per ingress port
 *  |  |  |   |
 *  V  V  v   v
 * BUF_P_RSRV_I
 */
#घोषणा BUF_P_RSRV_I(port) \
	(BUF_xxxx_I + xxx_P_RSRV_x + (port))

/*  Amount of frame references
 *  |  per QoS class
 *  |  |  reserved
 *  |  |  |   per egress port
 *  |  |  |   |
 *  V  V  v   v
 * REF_Q_RSRV_E
 */
#घोषणा REF_Q_RSRV_E(port, prio) \
	(REF_xxxx_E + xxx_Q_RSRV_x + OCELOT_NUM_TC * (port) + (prio))

/*  Amount of frame references
 *  |  क्रम all port's traffic classes
 *  |  |  reserved
 *  |  |  |   per egress port
 *  |  |  |   |
 *  V  V  v   v
 * REF_P_RSRV_E
 */
#घोषणा REF_P_RSRV_E(port) \
	(REF_xxxx_E + xxx_P_RSRV_x + (port))

/*  Amount of frame references
 *  |  per QoS class
 *  |  |  reserved
 *  |  |  |   per ingress port
 *  |  |  |   |
 *  V  V  v   v
 * REF_Q_RSRV_I
 */
#घोषणा REF_Q_RSRV_I(port, prio) \
	(REF_xxxx_I + xxx_Q_RSRV_x + OCELOT_NUM_TC * (port) + (prio))

/*  Amount of frame references
 *  |  क्रम all port's traffic classes
 *  |  |  reserved
 *  |  |  |   per ingress port
 *  |  |  |   |
 *  V  V  v   v
 * REF_P_RSRV_I
 */
#घोषणा REF_P_RSRV_I(port) \
	(REF_xxxx_I + xxx_P_RSRV_x + (port))

/* Sharing Watermarks
 * ------------------
 *
 * The shared memory area is shared between all ports.
 */

/* Amount of buffer
 *  |   per QoS class
 *  |   |    from the shared memory area
 *  |   |    |  क्रम egress traffic
 *  |   |    |  |
 *  V   V    v  v
 * BUF_PRIO_SHR_E
 */
#घोषणा BUF_PRIO_SHR_E(prio) \
	(BUF_xxxx_E + xxx_PRIO_SHR_x + (prio))

/* Amount of buffer
 *  |   per color (drop precedence level)
 *  |   |   from the shared memory area
 *  |   |   |  क्रम egress traffic
 *  |   |   |  |
 *  V   V   v  v
 * BUF_COL_SHR_E
 */
#घोषणा BUF_COL_SHR_E(dp) \
	(BUF_xxxx_E + xxx_COL_SHR_x + (1 - (dp)))

/* Amount of buffer
 *  |   per QoS class
 *  |   |    from the shared memory area
 *  |   |    |  क्रम ingress traffic
 *  |   |    |  |
 *  V   V    v  v
 * BUF_PRIO_SHR_I
 */
#घोषणा BUF_PRIO_SHR_I(prio) \
	(BUF_xxxx_I + xxx_PRIO_SHR_x + (prio))

/* Amount of buffer
 *  |   per color (drop precedence level)
 *  |   |   from the shared memory area
 *  |   |   |  क्रम ingress traffic
 *  |   |   |  |
 *  V   V   v  v
 * BUF_COL_SHR_I
 */
#घोषणा BUF_COL_SHR_I(dp) \
	(BUF_xxxx_I + xxx_COL_SHR_x + (1 - (dp)))

/* Amount of frame references
 *  |   per QoS class
 *  |   |    from the shared area
 *  |   |    |  क्रम egress traffic
 *  |   |    |  |
 *  V   V    v  v
 * REF_PRIO_SHR_E
 */
#घोषणा REF_PRIO_SHR_E(prio) \
	(REF_xxxx_E + xxx_PRIO_SHR_x + (prio))

/* Amount of frame references
 *  |   per color (drop precedence level)
 *  |   |   from the shared area
 *  |   |   |  क्रम egress traffic
 *  |   |   |  |
 *  V   V   v  v
 * REF_COL_SHR_E
 */
#घोषणा REF_COL_SHR_E(dp) \
	(REF_xxxx_E + xxx_COL_SHR_x + (1 - (dp)))

/* Amount of frame references
 *  |   per QoS class
 *  |   |    from the shared area
 *  |   |    |  क्रम ingress traffic
 *  |   |    |  |
 *  V   V    v  v
 * REF_PRIO_SHR_I
 */
#घोषणा REF_PRIO_SHR_I(prio) \
	(REF_xxxx_I + xxx_PRIO_SHR_x + (prio))

/* Amount of frame references
 *  |   per color (drop precedence level)
 *  |   |   from the shared area
 *  |   |   |  क्रम ingress traffic
 *  |   |   |  |
 *  V   V   v  v
 * REF_COL_SHR_I
 */
#घोषणा REF_COL_SHR_I(dp) \
	(REF_xxxx_I + xxx_COL_SHR_x + (1 - (dp)))

अटल u32 ocelot_wm_पढ़ो(काष्ठा ocelot *ocelot, पूर्णांक index)
अणु
	पूर्णांक wm = ocelot_पढ़ो_gix(ocelot, QSYS_RES_CFG, index);

	वापस ocelot->ops->wm_dec(wm);
पूर्ण

अटल व्योम ocelot_wm_ग_लिखो(काष्ठा ocelot *ocelot, पूर्णांक index, u32 val)
अणु
	u32 wm = ocelot->ops->wm_enc(val);

	ocelot_ग_लिखो_gix(ocelot, wm, QSYS_RES_CFG, index);
पूर्ण

अटल व्योम ocelot_wm_status(काष्ठा ocelot *ocelot, पूर्णांक index, u32 *inuse,
			     u32 *maxuse)
अणु
	पूर्णांक res_stat = ocelot_पढ़ो_gix(ocelot, QSYS_RES_STAT, index);

	वापस ocelot->ops->wm_stat(res_stat, inuse, maxuse);
पूर्ण

/* The hardware comes out of reset with strange शेषs: the sum of all
 * reservations क्रम frame memory is larger than the total buffer size.
 * One has to wonder how can the reservation watermarks still guarantee
 * anything under congestion.
 * Bring some sense पूर्णांकo the hardware by changing the शेषs to disable all
 * reservations and rely only on the sharing watermark क्रम frames with drop
 * precedence 0. The user can still explicitly request reservations per port
 * and per port-tc through devlink-sb.
 */
अटल व्योम ocelot_disable_reservation_watermarks(काष्ठा ocelot *ocelot,
						  पूर्णांक port)
अणु
	पूर्णांक prio;

	क्रम (prio = 0; prio < OCELOT_NUM_TC; prio++) अणु
		ocelot_wm_ग_लिखो(ocelot, BUF_Q_RSRV_I(port, prio), 0);
		ocelot_wm_ग_लिखो(ocelot, BUF_Q_RSRV_E(port, prio), 0);
		ocelot_wm_ग_लिखो(ocelot, REF_Q_RSRV_I(port, prio), 0);
		ocelot_wm_ग_लिखो(ocelot, REF_Q_RSRV_E(port, prio), 0);
	पूर्ण

	ocelot_wm_ग_लिखो(ocelot, BUF_P_RSRV_I(port), 0);
	ocelot_wm_ग_लिखो(ocelot, BUF_P_RSRV_E(port), 0);
	ocelot_wm_ग_लिखो(ocelot, REF_P_RSRV_I(port), 0);
	ocelot_wm_ग_लिखो(ocelot, REF_P_RSRV_E(port), 0);
पूर्ण

/* We want the sharing watermarks to consume all nonreserved resources, क्रम
 * efficient resource utilization (a single traffic flow should be able to use
 * up the entire buffer space and frame resources as दीर्घ as there's no
 * पूर्णांकerference).
 * The चयन has 10 sharing watermarks per lookup: 8 per traffic class and 2
 * per color (drop precedence).
 * The trouble with configuring these sharing watermarks is that:
 * (1) There's a risk that we overcommit the resources अगर we configure
 *     (a) all 8 per-TC sharing watermarks to the max
 *     (b) all 2 per-color sharing watermarks to the max
 * (2) There's a risk that we undercommit the resources अगर we configure
 *     (a) all 8 per-TC sharing watermarks to "max / 8"
 *     (b) all 2 per-color sharing watermarks to "max / 2"
 * So क्रम Linux, let's just disable the sharing watermarks per traffic class
 * (setting them to 0 will make them always exceeded), and rely only on the
 * sharing watermark क्रम drop priority 0. So frames with drop priority set to 1
 * by QoS classअगरication or policing will still be allowed, but only as दीर्घ as
 * the port and port-TC reservations are not exceeded.
 */
अटल व्योम ocelot_disable_tc_sharing_watermarks(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक prio;

	क्रम (prio = 0; prio < OCELOT_NUM_TC; prio++) अणु
		ocelot_wm_ग_लिखो(ocelot, BUF_PRIO_SHR_I(prio), 0);
		ocelot_wm_ग_लिखो(ocelot, BUF_PRIO_SHR_E(prio), 0);
		ocelot_wm_ग_लिखो(ocelot, REF_PRIO_SHR_I(prio), 0);
		ocelot_wm_ग_लिखो(ocelot, REF_PRIO_SHR_E(prio), 0);
	पूर्ण
पूर्ण

अटल व्योम ocelot_get_buf_rsrv(काष्ठा ocelot *ocelot, u32 *buf_rsrv_i,
				u32 *buf_rsrv_e)
अणु
	पूर्णांक port, prio;

	*buf_rsrv_i = 0;
	*buf_rsrv_e = 0;

	क्रम (port = 0; port <= ocelot->num_phys_ports; port++) अणु
		क्रम (prio = 0; prio < OCELOT_NUM_TC; prio++) अणु
			*buf_rsrv_i += ocelot_wm_पढ़ो(ocelot,
						      BUF_Q_RSRV_I(port, prio));
			*buf_rsrv_e += ocelot_wm_पढ़ो(ocelot,
						      BUF_Q_RSRV_E(port, prio));
		पूर्ण

		*buf_rsrv_i += ocelot_wm_पढ़ो(ocelot, BUF_P_RSRV_I(port));
		*buf_rsrv_e += ocelot_wm_पढ़ो(ocelot, BUF_P_RSRV_E(port));
	पूर्ण

	*buf_rsrv_i *= OCELOT_BUFFER_CELL_SZ;
	*buf_rsrv_e *= OCELOT_BUFFER_CELL_SZ;
पूर्ण

अटल व्योम ocelot_get_ref_rsrv(काष्ठा ocelot *ocelot, u32 *ref_rsrv_i,
				u32 *ref_rsrv_e)
अणु
	पूर्णांक port, prio;

	*ref_rsrv_i = 0;
	*ref_rsrv_e = 0;

	क्रम (port = 0; port <= ocelot->num_phys_ports; port++) अणु
		क्रम (prio = 0; prio < OCELOT_NUM_TC; prio++) अणु
			*ref_rsrv_i += ocelot_wm_पढ़ो(ocelot,
						      REF_Q_RSRV_I(port, prio));
			*ref_rsrv_e += ocelot_wm_पढ़ो(ocelot,
						      REF_Q_RSRV_E(port, prio));
		पूर्ण

		*ref_rsrv_i += ocelot_wm_पढ़ो(ocelot, REF_P_RSRV_I(port));
		*ref_rsrv_e += ocelot_wm_पढ़ो(ocelot, REF_P_RSRV_E(port));
	पूर्ण
पूर्ण

/* Calculate all reservations, then set up the sharing watermark क्रम DP=0 to
 * consume the reमुख्यing resources up to the pool's configured size.
 */
अटल व्योम ocelot_setup_sharing_watermarks(काष्ठा ocelot *ocelot)
अणु
	u32 buf_rsrv_i, buf_rsrv_e;
	u32 ref_rsrv_i, ref_rsrv_e;
	u32 buf_shr_i, buf_shr_e;
	u32 ref_shr_i, ref_shr_e;

	ocelot_get_buf_rsrv(ocelot, &buf_rsrv_i, &buf_rsrv_e);
	ocelot_get_ref_rsrv(ocelot, &ref_rsrv_i, &ref_rsrv_e);

	buf_shr_i = ocelot->pool_size[OCELOT_SB_BUF][OCELOT_SB_POOL_ING] -
		    buf_rsrv_i;
	buf_shr_e = ocelot->pool_size[OCELOT_SB_BUF][OCELOT_SB_POOL_EGR] -
		    buf_rsrv_e;
	ref_shr_i = ocelot->pool_size[OCELOT_SB_REF][OCELOT_SB_POOL_ING] -
		    ref_rsrv_i;
	ref_shr_e = ocelot->pool_size[OCELOT_SB_REF][OCELOT_SB_POOL_EGR] -
		    ref_rsrv_e;

	buf_shr_i /= OCELOT_BUFFER_CELL_SZ;
	buf_shr_e /= OCELOT_BUFFER_CELL_SZ;

	ocelot_wm_ग_लिखो(ocelot, BUF_COL_SHR_I(0), buf_shr_i);
	ocelot_wm_ग_लिखो(ocelot, BUF_COL_SHR_E(0), buf_shr_e);
	ocelot_wm_ग_लिखो(ocelot, REF_COL_SHR_E(0), ref_shr_e);
	ocelot_wm_ग_लिखो(ocelot, REF_COL_SHR_I(0), ref_shr_i);
	ocelot_wm_ग_लिखो(ocelot, BUF_COL_SHR_I(1), 0);
	ocelot_wm_ग_लिखो(ocelot, BUF_COL_SHR_E(1), 0);
	ocelot_wm_ग_लिखो(ocelot, REF_COL_SHR_E(1), 0);
	ocelot_wm_ग_लिखो(ocelot, REF_COL_SHR_I(1), 0);
पूर्ण

/* Ensure that all reservations can be enक्रमced */
अटल पूर्णांक ocelot_watermark_validate(काष्ठा ocelot *ocelot,
				     काष्ठा netlink_ext_ack *extack)
अणु
	u32 buf_rsrv_i, buf_rsrv_e;
	u32 ref_rsrv_i, ref_rsrv_e;

	ocelot_get_buf_rsrv(ocelot, &buf_rsrv_i, &buf_rsrv_e);
	ocelot_get_ref_rsrv(ocelot, &ref_rsrv_i, &ref_rsrv_e);

	अगर (buf_rsrv_i > ocelot->pool_size[OCELOT_SB_BUF][OCELOT_SB_POOL_ING]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Ingress frame reservations exceed pool size");
		वापस -दुस्फल;
	पूर्ण
	अगर (buf_rsrv_e > ocelot->pool_size[OCELOT_SB_BUF][OCELOT_SB_POOL_EGR]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Egress frame reservations exceed pool size");
		वापस -दुस्फल;
	पूर्ण
	अगर (ref_rsrv_i > ocelot->pool_size[OCELOT_SB_REF][OCELOT_SB_POOL_ING]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Ingress reference reservations exceed pool size");
		वापस -दुस्फल;
	पूर्ण
	अगर (ref_rsrv_e > ocelot->pool_size[OCELOT_SB_REF][OCELOT_SB_POOL_EGR]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Egress reference reservations exceed pool size");
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

/* The hardware works like this:
 *
 *                         Frame क्रमwarding decision taken
 *                                       |
 *                                       v
 *       +--------------------+--------------------+--------------------+
 *       |                    |                    |                    |
 *       v                    v                    v                    v
 * Ingress memory       Egress memory        Ingress frame        Egress frame
 *     check                check           reference check      reference check
 *       |                    |                    |                    |
 *       v                    v                    v                    v
 *  BUF_Q_RSRV_I   ok    BUF_Q_RSRV_E   ok    REF_Q_RSRV_I   ok     REF_Q_RSRV_E   ok
 *(src port, prio) -+  (dst port, prio) -+  (src port, prio) -+   (dst port, prio) -+
 *       |          |         |          |         |          |         |           |
 *       |exceeded  |         |exceeded  |         |exceeded  |         |exceeded   |
 *       v          |         v          |         v          |         v           |
 *  BUF_P_RSRV_I  ok|    BUF_P_RSRV_E  ok|    REF_P_RSRV_I  ok|    REF_P_RSRV_E   ok|
 *   (src port) ----+     (dst port) ----+     (src port) ----+     (dst port) -----+
 *       |          |         |          |         |          |         |           |
 *       |exceeded  |         |exceeded  |         |exceeded  |         |exceeded   |
 *       v          |         v          |         v          |         v           |
 * BUF_PRIO_SHR_I ok|   BUF_PRIO_SHR_E ok|   REF_PRIO_SHR_I ok|   REF_PRIO_SHR_E  ok|
 *     (prio) ------+       (prio) ------+       (prio) ------+       (prio) -------+
 *       |          |         |          |         |          |         |           |
 *       |exceeded  |         |exceeded  |         |exceeded  |         |exceeded   |
 *       v          |         v          |         v          |         v           |
 * BUF_COL_SHR_I  ok|   BUF_COL_SHR_E  ok|   REF_COL_SHR_I  ok|   REF_COL_SHR_E   ok|
 *      (dp) -------+        (dp) -------+        (dp) -------+        (dp) --------+
 *       |          |         |          |         |          |         |           |
 *       |exceeded  |         |exceeded  |         |exceeded  |         |exceeded   |
 *       v          v         v          v         v          v         v           v
 *      fail     success     fail     success     fail     success     fail      success
 *       |          |         |          |         |          |         |           |
 *       v          v         v          v         v          v         v           v
 *       +-----+----+         +-----+----+         +-----+----+         +-----+-----+
 *             |                    |                    |                    |
 *             +-------> OR <-------+                    +-------> OR <-------+
 *                        |                                        |
 *                        v                                        v
 *                        +----------------> AND <-----------------+
 *                                            |
 *                                            v
 *                                    FIFO drop / accept
 *
 * We are modeling each of the 4 parallel lookups as a devlink-sb pool.
 * At least one (ingress or egress) memory pool and one (ingress or egress)
 * frame reference pool need to have resources क्रम frame acceptance to succeed.
 *
 * The following watermarks are controlled explicitly through devlink-sb:
 * BUF_Q_RSRV_I, BUF_Q_RSRV_E, REF_Q_RSRV_I, REF_Q_RSRV_E
 * BUF_P_RSRV_I, BUF_P_RSRV_E, REF_P_RSRV_I, REF_P_RSRV_E
 * The following watermarks are controlled implicitly through devlink-sb:
 * BUF_COL_SHR_I, BUF_COL_SHR_E, REF_COL_SHR_I, REF_COL_SHR_E
 * The following watermarks are unused and disabled:
 * BUF_PRIO_SHR_I, BUF_PRIO_SHR_E, REF_PRIO_SHR_I, REF_PRIO_SHR_E
 *
 * This function overrides the hardware शेषs with more sane ones (no
 * reservations by शेष, let sharing use all resources) and disables the
 * unused watermarks.
 */
अटल व्योम ocelot_watermark_init(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक all_tcs = GENMASK(OCELOT_NUM_TC - 1, 0);
	पूर्णांक port;

	ocelot_ग_लिखो(ocelot, all_tcs, QSYS_RES_QOS_MODE);

	क्रम (port = 0; port <= ocelot->num_phys_ports; port++)
		ocelot_disable_reservation_watermarks(ocelot, port);

	ocelot_disable_tc_sharing_watermarks(ocelot);
	ocelot_setup_sharing_watermarks(ocelot);
पूर्ण

/* Pool size and type are fixed up at runसमय. Keeping this काष्ठाure to
 * look up the cell size multipliers.
 */
अटल स्थिर काष्ठा devlink_sb_pool_info ocelot_sb_pool[] = अणु
	[OCELOT_SB_BUF] = अणु
		.cell_size = OCELOT_BUFFER_CELL_SZ,
		.threshold_type = DEVLINK_SB_THRESHOLD_TYPE_STATIC,
	पूर्ण,
	[OCELOT_SB_REF] = अणु
		.cell_size = 1,
		.threshold_type = DEVLINK_SB_THRESHOLD_TYPE_STATIC,
	पूर्ण,
पूर्ण;

/* Returns the pool size configured through ocelot_sb_pool_set */
पूर्णांक ocelot_sb_pool_get(काष्ठा ocelot *ocelot, अचिन्हित पूर्णांक sb_index,
		       u16 pool_index,
		       काष्ठा devlink_sb_pool_info *pool_info)
अणु
	अगर (sb_index >= OCELOT_SB_NUM)
		वापस -ENODEV;
	अगर (pool_index >= OCELOT_SB_POOL_NUM)
		वापस -ENODEV;

	*pool_info = ocelot_sb_pool[sb_index];
	pool_info->size = ocelot->pool_size[sb_index][pool_index];
	अगर (pool_index)
		pool_info->pool_type = DEVLINK_SB_POOL_TYPE_INGRESS;
	अन्यथा
		pool_info->pool_type = DEVLINK_SB_POOL_TYPE_EGRESS;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_sb_pool_get);

/* The pool size received here configures the total amount of resources used on
 * ingress (or on egress, depending upon the pool index). The pool size, minus
 * the values क्रम the port and port-tc reservations, is written पूर्णांकo the
 * COL_SHR(dp=0) sharing watermark.
 */
पूर्णांक ocelot_sb_pool_set(काष्ठा ocelot *ocelot, अचिन्हित पूर्णांक sb_index,
		       u16 pool_index, u32 size,
		       क्रमागत devlink_sb_threshold_type threshold_type,
		       काष्ठा netlink_ext_ack *extack)
अणु
	u32 old_pool_size;
	पूर्णांक err;

	अगर (sb_index >= OCELOT_SB_NUM) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid sb, use 0 for buffers and 1 for frame references");
		वापस -ENODEV;
	पूर्ण
	अगर (pool_index >= OCELOT_SB_POOL_NUM) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid pool, use 0 for ingress and 1 for egress");
		वापस -ENODEV;
	पूर्ण
	अगर (threshold_type != DEVLINK_SB_THRESHOLD_TYPE_STATIC) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Only static threshold supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	old_pool_size = ocelot->pool_size[sb_index][pool_index];
	ocelot->pool_size[sb_index][pool_index] = size;

	err = ocelot_watermark_validate(ocelot, extack);
	अगर (err) अणु
		ocelot->pool_size[sb_index][pool_index] = old_pool_size;
		वापस err;
	पूर्ण

	ocelot_setup_sharing_watermarks(ocelot);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_sb_pool_set);

/* This retrieves the configuration made with ocelot_sb_port_pool_set */
पूर्णांक ocelot_sb_port_pool_get(काष्ठा ocelot *ocelot, पूर्णांक port,
			    अचिन्हित पूर्णांक sb_index, u16 pool_index,
			    u32 *p_threshold)
अणु
	पूर्णांक wm_index;

	चयन (sb_index) अणु
	हाल OCELOT_SB_BUF:
		अगर (pool_index == OCELOT_SB_POOL_ING)
			wm_index = BUF_P_RSRV_I(port);
		अन्यथा
			wm_index = BUF_P_RSRV_E(port);
		अवरोध;
	हाल OCELOT_SB_REF:
		अगर (pool_index == OCELOT_SB_POOL_ING)
			wm_index = REF_P_RSRV_I(port);
		अन्यथा
			wm_index = REF_P_RSRV_E(port);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	*p_threshold = ocelot_wm_पढ़ो(ocelot, wm_index);
	*p_threshold *= ocelot_sb_pool[sb_index].cell_size;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_sb_port_pool_get);

/* This configures the P_RSRV per-port reserved resource watermark */
पूर्णांक ocelot_sb_port_pool_set(काष्ठा ocelot *ocelot, पूर्णांक port,
			    अचिन्हित पूर्णांक sb_index, u16 pool_index,
			    u32 threshold, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक wm_index, err;
	u32 old_thr;

	चयन (sb_index) अणु
	हाल OCELOT_SB_BUF:
		अगर (pool_index == OCELOT_SB_POOL_ING)
			wm_index = BUF_P_RSRV_I(port);
		अन्यथा
			wm_index = BUF_P_RSRV_E(port);
		अवरोध;
	हाल OCELOT_SB_REF:
		अगर (pool_index == OCELOT_SB_POOL_ING)
			wm_index = REF_P_RSRV_I(port);
		अन्यथा
			wm_index = REF_P_RSRV_E(port);
		अवरोध;
	शेष:
		NL_SET_ERR_MSG_MOD(extack, "Invalid shared buffer");
		वापस -ENODEV;
	पूर्ण

	threshold /= ocelot_sb_pool[sb_index].cell_size;

	old_thr = ocelot_wm_पढ़ो(ocelot, wm_index);
	ocelot_wm_ग_लिखो(ocelot, wm_index, threshold);

	err = ocelot_watermark_validate(ocelot, extack);
	अगर (err) अणु
		ocelot_wm_ग_लिखो(ocelot, wm_index, old_thr);
		वापस err;
	पूर्ण

	ocelot_setup_sharing_watermarks(ocelot);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_sb_port_pool_set);

/* This retrieves the configuration करोne by ocelot_sb_tc_pool_bind_set */
पूर्णांक ocelot_sb_tc_pool_bind_get(काष्ठा ocelot *ocelot, पूर्णांक port,
			       अचिन्हित पूर्णांक sb_index, u16 tc_index,
			       क्रमागत devlink_sb_pool_type pool_type,
			       u16 *p_pool_index, u32 *p_threshold)
अणु
	पूर्णांक wm_index;

	चयन (sb_index) अणु
	हाल OCELOT_SB_BUF:
		अगर (pool_type == DEVLINK_SB_POOL_TYPE_INGRESS)
			wm_index = BUF_Q_RSRV_I(port, tc_index);
		अन्यथा
			wm_index = BUF_Q_RSRV_E(port, tc_index);
		अवरोध;
	हाल OCELOT_SB_REF:
		अगर (pool_type == DEVLINK_SB_POOL_TYPE_INGRESS)
			wm_index = REF_Q_RSRV_I(port, tc_index);
		अन्यथा
			wm_index = REF_Q_RSRV_E(port, tc_index);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	*p_threshold = ocelot_wm_पढ़ो(ocelot, wm_index);
	*p_threshold *= ocelot_sb_pool[sb_index].cell_size;

	अगर (pool_type == DEVLINK_SB_POOL_TYPE_INGRESS)
		*p_pool_index = 0;
	अन्यथा
		*p_pool_index = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_sb_tc_pool_bind_get);

/* This configures the Q_RSRV per-port-tc reserved resource watermark */
पूर्णांक ocelot_sb_tc_pool_bind_set(काष्ठा ocelot *ocelot, पूर्णांक port,
			       अचिन्हित पूर्णांक sb_index, u16 tc_index,
			       क्रमागत devlink_sb_pool_type pool_type,
			       u16 pool_index, u32 threshold,
			       काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक wm_index, err;
	u32 old_thr;

	/* Paranoid check? */
	अगर (pool_index == OCELOT_SB_POOL_ING &&
	    pool_type != DEVLINK_SB_POOL_TYPE_INGRESS)
		वापस -EINVAL;
	अगर (pool_index == OCELOT_SB_POOL_EGR &&
	    pool_type != DEVLINK_SB_POOL_TYPE_EGRESS)
		वापस -EINVAL;

	चयन (sb_index) अणु
	हाल OCELOT_SB_BUF:
		अगर (pool_type == DEVLINK_SB_POOL_TYPE_INGRESS)
			wm_index = BUF_Q_RSRV_I(port, tc_index);
		अन्यथा
			wm_index = BUF_Q_RSRV_E(port, tc_index);
		अवरोध;
	हाल OCELOT_SB_REF:
		अगर (pool_type == DEVLINK_SB_POOL_TYPE_INGRESS)
			wm_index = REF_Q_RSRV_I(port, tc_index);
		अन्यथा
			wm_index = REF_Q_RSRV_E(port, tc_index);
		अवरोध;
	शेष:
		NL_SET_ERR_MSG_MOD(extack, "Invalid shared buffer");
		वापस -ENODEV;
	पूर्ण

	threshold /= ocelot_sb_pool[sb_index].cell_size;

	old_thr = ocelot_wm_पढ़ो(ocelot, wm_index);
	ocelot_wm_ग_लिखो(ocelot, wm_index, threshold);
	err = ocelot_watermark_validate(ocelot, extack);
	अगर (err) अणु
		ocelot_wm_ग_लिखो(ocelot, wm_index, old_thr);
		वापस err;
	पूर्ण

	ocelot_setup_sharing_watermarks(ocelot);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_sb_tc_pool_bind_set);

/* The hardware करोes not support atomic snapshots, we'll पढ़ो out the
 * occupancy रेजिस्टरs inभागidually and have this as just a stub.
 */
पूर्णांक ocelot_sb_occ_snapshot(काष्ठा ocelot *ocelot, अचिन्हित पूर्णांक sb_index)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_sb_occ_snapshot);

/* The watermark occupancy रेजिस्टरs are cleared upon पढ़ो,
 * so let's पढ़ो them.
 */
पूर्णांक ocelot_sb_occ_max_clear(काष्ठा ocelot *ocelot, अचिन्हित पूर्णांक sb_index)
अणु
	u32 inuse, maxuse;
	पूर्णांक port, prio;

	चयन (sb_index) अणु
	हाल OCELOT_SB_BUF:
		क्रम (port = 0; port <= ocelot->num_phys_ports; port++) अणु
			क्रम (prio = 0; prio < OCELOT_NUM_TC; prio++) अणु
				ocelot_wm_status(ocelot, BUF_Q_RSRV_I(port, prio),
						 &inuse, &maxuse);
				ocelot_wm_status(ocelot, BUF_Q_RSRV_E(port, prio),
						 &inuse, &maxuse);
			पूर्ण
			ocelot_wm_status(ocelot, BUF_P_RSRV_I(port),
					 &inuse, &maxuse);
			ocelot_wm_status(ocelot, BUF_P_RSRV_E(port),
					 &inuse, &maxuse);
		पूर्ण
		अवरोध;
	हाल OCELOT_SB_REF:
		क्रम (port = 0; port <= ocelot->num_phys_ports; port++) अणु
			क्रम (prio = 0; prio < OCELOT_NUM_TC; prio++) अणु
				ocelot_wm_status(ocelot, REF_Q_RSRV_I(port, prio),
						 &inuse, &maxuse);
				ocelot_wm_status(ocelot, REF_Q_RSRV_E(port, prio),
						 &inuse, &maxuse);
			पूर्ण
			ocelot_wm_status(ocelot, REF_P_RSRV_I(port),
					 &inuse, &maxuse);
			ocelot_wm_status(ocelot, REF_P_RSRV_E(port),
					 &inuse, &maxuse);
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_sb_occ_max_clear);

/* This retrieves the watermark occupancy क्रम per-port P_RSRV watermarks */
पूर्णांक ocelot_sb_occ_port_pool_get(काष्ठा ocelot *ocelot, पूर्णांक port,
				अचिन्हित पूर्णांक sb_index, u16 pool_index,
				u32 *p_cur, u32 *p_max)
अणु
	पूर्णांक wm_index;

	चयन (sb_index) अणु
	हाल OCELOT_SB_BUF:
		अगर (pool_index == OCELOT_SB_POOL_ING)
			wm_index = BUF_P_RSRV_I(port);
		अन्यथा
			wm_index = BUF_P_RSRV_E(port);
		अवरोध;
	हाल OCELOT_SB_REF:
		अगर (pool_index == OCELOT_SB_POOL_ING)
			wm_index = REF_P_RSRV_I(port);
		अन्यथा
			wm_index = REF_P_RSRV_E(port);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	ocelot_wm_status(ocelot, wm_index, p_cur, p_max);
	*p_cur *= ocelot_sb_pool[sb_index].cell_size;
	*p_max *= ocelot_sb_pool[sb_index].cell_size;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_sb_occ_port_pool_get);

/* This retrieves the watermark occupancy क्रम per-port-tc Q_RSRV watermarks */
पूर्णांक ocelot_sb_occ_tc_port_bind_get(काष्ठा ocelot *ocelot, पूर्णांक port,
				   अचिन्हित पूर्णांक sb_index, u16 tc_index,
				   क्रमागत devlink_sb_pool_type pool_type,
				   u32 *p_cur, u32 *p_max)
अणु
	पूर्णांक wm_index;

	चयन (sb_index) अणु
	हाल OCELOT_SB_BUF:
		अगर (pool_type == DEVLINK_SB_POOL_TYPE_INGRESS)
			wm_index = BUF_Q_RSRV_I(port, tc_index);
		अन्यथा
			wm_index = BUF_Q_RSRV_E(port, tc_index);
		अवरोध;
	हाल OCELOT_SB_REF:
		अगर (pool_type == DEVLINK_SB_POOL_TYPE_INGRESS)
			wm_index = REF_Q_RSRV_I(port, tc_index);
		अन्यथा
			wm_index = REF_Q_RSRV_E(port, tc_index);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	ocelot_wm_status(ocelot, wm_index, p_cur, p_max);
	*p_cur *= ocelot_sb_pool[sb_index].cell_size;
	*p_max *= ocelot_sb_pool[sb_index].cell_size;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_sb_occ_tc_port_bind_get);

पूर्णांक ocelot_devlink_sb_रेजिस्टर(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक err;

	err = devlink_sb_रेजिस्टर(ocelot->devlink, OCELOT_SB_BUF,
				  ocelot->packet_buffer_size, 1, 1,
				  OCELOT_NUM_TC, OCELOT_NUM_TC);
	अगर (err)
		वापस err;

	err = devlink_sb_रेजिस्टर(ocelot->devlink, OCELOT_SB_REF,
				  ocelot->num_frame_refs, 1, 1,
				  OCELOT_NUM_TC, OCELOT_NUM_TC);
	अगर (err) अणु
		devlink_sb_unरेजिस्टर(ocelot->devlink, OCELOT_SB_BUF);
		वापस err;
	पूर्ण

	ocelot->pool_size[OCELOT_SB_BUF][OCELOT_SB_POOL_ING] = ocelot->packet_buffer_size;
	ocelot->pool_size[OCELOT_SB_BUF][OCELOT_SB_POOL_EGR] = ocelot->packet_buffer_size;
	ocelot->pool_size[OCELOT_SB_REF][OCELOT_SB_POOL_ING] = ocelot->num_frame_refs;
	ocelot->pool_size[OCELOT_SB_REF][OCELOT_SB_POOL_EGR] = ocelot->num_frame_refs;

	ocelot_watermark_init(ocelot);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_devlink_sb_रेजिस्टर);

व्योम ocelot_devlink_sb_unरेजिस्टर(काष्ठा ocelot *ocelot)
अणु
	devlink_sb_unरेजिस्टर(ocelot->devlink, OCELOT_SB_BUF);
	devlink_sb_unरेजिस्टर(ocelot->devlink, OCELOT_SB_REF);
पूर्ण
EXPORT_SYMBOL(ocelot_devlink_sb_unरेजिस्टर);
