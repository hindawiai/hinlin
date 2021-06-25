<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* viohs.c: LDOM Virtual I/O handshake helper layer.
 *
 * Copyright (C) 2007 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/ldc.h>
#समावेश <यंत्र/vपन.स>

पूर्णांक vio_ldc_send(काष्ठा vio_driver_state *vio, व्योम *data, पूर्णांक len)
अणु
	पूर्णांक err, limit = 1000;

	err = -EINVAL;
	जबतक (limit-- > 0) अणु
		err = ldc_ग_लिखो(vio->lp, data, len);
		अगर (!err || (err != -EAGAIN))
			अवरोध;
		udelay(1);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(vio_ldc_send);

अटल पूर्णांक send_ctrl(काष्ठा vio_driver_state *vio,
		     काष्ठा vio_msg_tag *tag, पूर्णांक len)
अणु
	tag->sid = vio_send_sid(vio);
	वापस vio_ldc_send(vio, tag, len);
पूर्ण

अटल व्योम init_tag(काष्ठा vio_msg_tag *tag, u8 type, u8 stype, u16 stype_env)
अणु
	tag->type = type;
	tag->stype = stype;
	tag->stype_env = stype_env;
पूर्ण

अटल पूर्णांक send_version(काष्ठा vio_driver_state *vio, u16 major, u16 minor)
अणु
	काष्ठा vio_ver_info pkt;

	vio->_local_sid = (u32) sched_घड़ी();

	स_रखो(&pkt, 0, माप(pkt));
	init_tag(&pkt.tag, VIO_TYPE_CTRL, VIO_SUBTYPE_INFO, VIO_VER_INFO);
	pkt.major = major;
	pkt.minor = minor;
	pkt.dev_class = vio->dev_class;

	viodbg(HS, "SEND VERSION INFO maj[%u] min[%u] devclass[%u]\n",
	       major, minor, vio->dev_class);

	वापस send_ctrl(vio, &pkt.tag, माप(pkt));
पूर्ण

अटल पूर्णांक start_handshake(काष्ठा vio_driver_state *vio)
अणु
	पूर्णांक err;

	viodbg(HS, "START HANDSHAKE\n");

	vio->hs_state = VIO_HS_INVALID;

	err = send_version(vio,
			   vio->ver_table[0].major,
			   vio->ver_table[0].minor);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम flush_rx_dring(काष्ठा vio_driver_state *vio)
अणु
	काष्ठा vio_dring_state *dr;
	u64 ident;

	BUG_ON(!(vio->dr_state & VIO_DR_STATE_RXREG));

	dr = &vio->drings[VIO_DRIVER_RX_RING];
	ident = dr->ident;

	BUG_ON(!vio->desc_buf);
	kमुक्त(vio->desc_buf);
	vio->desc_buf = शून्य;

	स_रखो(dr, 0, माप(*dr));
	dr->ident = ident;
पूर्ण

व्योम vio_link_state_change(काष्ठा vio_driver_state *vio, पूर्णांक event)
अणु
	अगर (event == LDC_EVENT_UP) अणु
		vio->hs_state = VIO_HS_INVALID;

		चयन (vio->dev_class) अणु
		हाल VDEV_NETWORK:
		हाल VDEV_NETWORK_SWITCH:
			vio->dr_state = (VIO_DR_STATE_TXREQ |
					 VIO_DR_STATE_RXREQ);
			अवरोध;

		हाल VDEV_DISK:
			vio->dr_state = VIO_DR_STATE_TXREQ;
			अवरोध;
		हाल VDEV_DISK_SERVER:
			vio->dr_state = VIO_DR_STATE_RXREQ;
			अवरोध;
		पूर्ण
		start_handshake(vio);
	पूर्ण अन्यथा अगर (event == LDC_EVENT_RESET) अणु
		vio->hs_state = VIO_HS_INVALID;

		अगर (vio->dr_state & VIO_DR_STATE_RXREG)
			flush_rx_dring(vio);

		vio->dr_state = 0x00;
		स_रखो(&vio->ver, 0, माप(vio->ver));

		ldc_disconnect(vio->lp);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(vio_link_state_change);

अटल पूर्णांक handshake_failure(काष्ठा vio_driver_state *vio)
अणु
	काष्ठा vio_dring_state *dr;

	/* XXX Put policy here...  Perhaps start a समयr to fire
	 * XXX in 100 ms, which will bring the link up and retry
	 * XXX the handshake.
	 */

	viodbg(HS, "HANDSHAKE FAILURE\n");

	vio->dr_state &= ~(VIO_DR_STATE_TXREG |
			   VIO_DR_STATE_RXREG);

	dr = &vio->drings[VIO_DRIVER_RX_RING];
	स_रखो(dr, 0, माप(*dr));

	kमुक्त(vio->desc_buf);
	vio->desc_buf = शून्य;
	vio->desc_buf_len = 0;

	vio->hs_state = VIO_HS_INVALID;

	वापस -ECONNRESET;
पूर्ण

अटल पूर्णांक process_unknown(काष्ठा vio_driver_state *vio, व्योम *arg)
अणु
	काष्ठा vio_msg_tag *pkt = arg;

	viodbg(HS, "UNKNOWN CONTROL [%02x:%02x:%04x:%08x]\n",
	       pkt->type, pkt->stype, pkt->stype_env, pkt->sid);

	prपूर्णांकk(KERN_ERR "vio: ID[%lu] Resetting connection.\n",
	       vio->vdev->channel_id);

	ldc_disconnect(vio->lp);

	वापस -ECONNRESET;
पूर्ण

अटल पूर्णांक send_dreg(काष्ठा vio_driver_state *vio)
अणु
	काष्ठा vio_dring_state *dr = &vio->drings[VIO_DRIVER_TX_RING];
	जोड़ अणु
		काष्ठा vio_dring_रेजिस्टर pkt;
		अक्षर all[माप(काष्ठा vio_dring_रेजिस्टर) +
			 (माप(काष्ठा ldc_trans_cookie) *
			  VIO_MAX_RING_COOKIES)];
	पूर्ण u;
	माप_प्रकार bytes = माप(काष्ठा vio_dring_रेजिस्टर) +
		       (माप(काष्ठा ldc_trans_cookie) *
			dr->ncookies);
	पूर्णांक i;

	अगर (WARN_ON(bytes > माप(u)))
		वापस -EINVAL;

	स_रखो(&u, 0, bytes);
	init_tag(&u.pkt.tag, VIO_TYPE_CTRL, VIO_SUBTYPE_INFO, VIO_DRING_REG);
	u.pkt.dring_ident = 0;
	u.pkt.num_descr = dr->num_entries;
	u.pkt.descr_size = dr->entry_size;
	u.pkt.options = VIO_TX_DRING;
	u.pkt.num_cookies = dr->ncookies;

	viodbg(HS, "SEND DRING_REG INFO ndesc[%u] dsz[%u] opt[0x%x] "
	       "ncookies[%u]\n",
	       u.pkt.num_descr, u.pkt.descr_size, u.pkt.options,
	       u.pkt.num_cookies);

	क्रम (i = 0; i < dr->ncookies; i++) अणु
		u.pkt.cookies[i] = dr->cookies[i];

		viodbg(HS, "DRING COOKIE(%d) [%016llx:%016llx]\n",
		       i,
		       (अचिन्हित दीर्घ दीर्घ) u.pkt.cookies[i].cookie_addr,
		       (अचिन्हित दीर्घ दीर्घ) u.pkt.cookies[i].cookie_size);
	पूर्ण

	वापस send_ctrl(vio, &u.pkt.tag, bytes);
पूर्ण

अटल पूर्णांक send_rdx(काष्ठा vio_driver_state *vio)
अणु
	काष्ठा vio_rdx pkt;

	स_रखो(&pkt, 0, माप(pkt));

	init_tag(&pkt.tag, VIO_TYPE_CTRL, VIO_SUBTYPE_INFO, VIO_RDX);

	viodbg(HS, "SEND RDX INFO\n");

	वापस send_ctrl(vio, &pkt.tag, माप(pkt));
पूर्ण

अटल पूर्णांक send_attr(काष्ठा vio_driver_state *vio)
अणु
	अगर (!vio->ops)
		वापस -EINVAL;

	वापस vio->ops->send_attr(vio);
पूर्ण

अटल काष्ठा vio_version *find_by_major(काष्ठा vio_driver_state *vio,
					 u16 major)
अणु
	काष्ठा vio_version *ret = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < vio->ver_table_entries; i++) अणु
		काष्ठा vio_version *v = &vio->ver_table[i];
		अगर (v->major <= major) अणु
			ret = v;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक process_ver_info(काष्ठा vio_driver_state *vio,
			    काष्ठा vio_ver_info *pkt)
अणु
	काष्ठा vio_version *vap;
	पूर्णांक err;

	viodbg(HS, "GOT VERSION INFO maj[%u] min[%u] devclass[%u]\n",
	       pkt->major, pkt->minor, pkt->dev_class);

	अगर (vio->hs_state != VIO_HS_INVALID) अणु
		/* XXX Perhaps invoke start_handshake? XXX */
		स_रखो(&vio->ver, 0, माप(vio->ver));
		vio->hs_state = VIO_HS_INVALID;
	पूर्ण

	vap = find_by_major(vio, pkt->major);

	vio->_peer_sid = pkt->tag.sid;

	अगर (!vap) अणु
		pkt->tag.stype = VIO_SUBTYPE_NACK;
		pkt->major = 0;
		pkt->minor = 0;
		viodbg(HS, "SEND VERSION NACK maj[0] min[0]\n");
		err = send_ctrl(vio, &pkt->tag, माप(*pkt));
	पूर्ण अन्यथा अगर (vap->major != pkt->major) अणु
		pkt->tag.stype = VIO_SUBTYPE_NACK;
		pkt->major = vap->major;
		pkt->minor = vap->minor;
		viodbg(HS, "SEND VERSION NACK maj[%u] min[%u]\n",
		       pkt->major, pkt->minor);
		err = send_ctrl(vio, &pkt->tag, माप(*pkt));
	पूर्ण अन्यथा अणु
		काष्ठा vio_version ver = अणु
			.major = pkt->major,
			.minor = pkt->minor,
		पूर्ण;
		अगर (ver.minor > vap->minor)
			ver.minor = vap->minor;
		pkt->minor = ver.minor;
		pkt->tag.stype = VIO_SUBTYPE_ACK;
		pkt->dev_class = vio->dev_class;
		viodbg(HS, "SEND VERSION ACK maj[%u] min[%u]\n",
		       pkt->major, pkt->minor);
		err = send_ctrl(vio, &pkt->tag, माप(*pkt));
		अगर (err > 0) अणु
			vio->ver = ver;
			vio->hs_state = VIO_HS_GOTVERS;
		पूर्ण
	पूर्ण
	अगर (err < 0)
		वापस handshake_failure(vio);

	वापस 0;
पूर्ण

अटल पूर्णांक process_ver_ack(काष्ठा vio_driver_state *vio,
			   काष्ठा vio_ver_info *pkt)
अणु
	viodbg(HS, "GOT VERSION ACK maj[%u] min[%u] devclass[%u]\n",
	       pkt->major, pkt->minor, pkt->dev_class);

	अगर (vio->hs_state & VIO_HS_GOTVERS) अणु
		अगर (vio->ver.major != pkt->major ||
		    vio->ver.minor != pkt->minor) अणु
			pkt->tag.stype = VIO_SUBTYPE_NACK;
			(व्योम) send_ctrl(vio, &pkt->tag, माप(*pkt));
			वापस handshake_failure(vio);
		पूर्ण
	पूर्ण अन्यथा अणु
		vio->ver.major = pkt->major;
		vio->ver.minor = pkt->minor;
		vio->hs_state = VIO_HS_GOTVERS;
	पूर्ण

	चयन (vio->dev_class) अणु
	हाल VDEV_NETWORK:
	हाल VDEV_DISK:
		अगर (send_attr(vio) < 0)
			वापस handshake_failure(vio);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_ver_nack(काष्ठा vio_driver_state *vio,
			    काष्ठा vio_ver_info *pkt)
अणु
	काष्ठा vio_version *nver;

	viodbg(HS, "GOT VERSION NACK maj[%u] min[%u] devclass[%u]\n",
	       pkt->major, pkt->minor, pkt->dev_class);

	अगर (pkt->major == 0 && pkt->minor == 0)
		वापस handshake_failure(vio);
	nver = find_by_major(vio, pkt->major);
	अगर (!nver)
		वापस handshake_failure(vio);

	अगर (send_version(vio, nver->major, nver->minor) < 0)
		वापस handshake_failure(vio);

	वापस 0;
पूर्ण

अटल पूर्णांक process_ver(काष्ठा vio_driver_state *vio, काष्ठा vio_ver_info *pkt)
अणु
	चयन (pkt->tag.stype) अणु
	हाल VIO_SUBTYPE_INFO:
		वापस process_ver_info(vio, pkt);

	हाल VIO_SUBTYPE_ACK:
		वापस process_ver_ack(vio, pkt);

	हाल VIO_SUBTYPE_NACK:
		वापस process_ver_nack(vio, pkt);

	शेष:
		वापस handshake_failure(vio);
	पूर्ण
पूर्ण

अटल पूर्णांक process_attr(काष्ठा vio_driver_state *vio, व्योम *pkt)
अणु
	पूर्णांक err;

	अगर (!(vio->hs_state & VIO_HS_GOTVERS))
		वापस handshake_failure(vio);

	अगर (!vio->ops)
		वापस 0;

	err = vio->ops->handle_attr(vio, pkt);
	अगर (err < 0) अणु
		वापस handshake_failure(vio);
	पूर्ण अन्यथा अणु
		vio->hs_state |= VIO_HS_GOT_ATTR;

		अगर ((vio->dr_state & VIO_DR_STATE_TXREQ) &&
		    !(vio->hs_state & VIO_HS_SENT_DREG)) अणु
			अगर (send_dreg(vio) < 0)
				वापस handshake_failure(vio);

			vio->hs_state |= VIO_HS_SENT_DREG;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक all_drings_रेजिस्टरed(काष्ठा vio_driver_state *vio)
अणु
	पूर्णांक need_rx, need_tx;

	need_rx = (vio->dr_state & VIO_DR_STATE_RXREQ);
	need_tx = (vio->dr_state & VIO_DR_STATE_TXREQ);

	अगर (need_rx &&
	    !(vio->dr_state & VIO_DR_STATE_RXREG))
		वापस 0;

	अगर (need_tx &&
	    !(vio->dr_state & VIO_DR_STATE_TXREG))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक process_dreg_info(काष्ठा vio_driver_state *vio,
			     काष्ठा vio_dring_रेजिस्टर *pkt)
अणु
	काष्ठा vio_dring_state *dr;
	पूर्णांक i;

	viodbg(HS, "GOT DRING_REG INFO ident[%llx] "
	       "ndesc[%u] dsz[%u] opt[0x%x] ncookies[%u]\n",
	       (अचिन्हित दीर्घ दीर्घ) pkt->dring_ident,
	       pkt->num_descr, pkt->descr_size, pkt->options,
	       pkt->num_cookies);

	अगर (!(vio->dr_state & VIO_DR_STATE_RXREQ))
		जाओ send_nack;

	अगर (vio->dr_state & VIO_DR_STATE_RXREG)
		जाओ send_nack;

	/* v1.6 and higher, ACK with desired, supported mode, or NACK */
	अगर (vio_version_after_eq(vio, 1, 6)) अणु
		अगर (!(pkt->options & VIO_TX_DRING))
			जाओ send_nack;
		pkt->options = VIO_TX_DRING;
	पूर्ण

	BUG_ON(vio->desc_buf);

	vio->desc_buf = kzalloc(pkt->descr_size, GFP_ATOMIC);
	अगर (!vio->desc_buf)
		जाओ send_nack;

	vio->desc_buf_len = pkt->descr_size;

	dr = &vio->drings[VIO_DRIVER_RX_RING];

	dr->num_entries = pkt->num_descr;
	dr->entry_size = pkt->descr_size;
	dr->ncookies = pkt->num_cookies;
	क्रम (i = 0; i < dr->ncookies; i++) अणु
		dr->cookies[i] = pkt->cookies[i];

		viodbg(HS, "DRING COOKIE(%d) [%016llx:%016llx]\n",
		       i,
		       (अचिन्हित दीर्घ दीर्घ)
		       pkt->cookies[i].cookie_addr,
		       (अचिन्हित दीर्घ दीर्घ)
		       pkt->cookies[i].cookie_size);
	पूर्ण

	pkt->tag.stype = VIO_SUBTYPE_ACK;
	pkt->dring_ident = ++dr->ident;

	viodbg(HS, "SEND DRING_REG ACK ident[%llx] "
	       "ndesc[%u] dsz[%u] opt[0x%x] ncookies[%u]\n",
	       (अचिन्हित दीर्घ दीर्घ) pkt->dring_ident,
	       pkt->num_descr, pkt->descr_size, pkt->options,
	       pkt->num_cookies);

	अगर (send_ctrl(vio, &pkt->tag, काष्ठा_size(pkt, cookies, dr->ncookies)) < 0)
		जाओ send_nack;

	vio->dr_state |= VIO_DR_STATE_RXREG;

	वापस 0;

send_nack:
	pkt->tag.stype = VIO_SUBTYPE_NACK;
	viodbg(HS, "SEND DRING_REG NACK\n");
	(व्योम) send_ctrl(vio, &pkt->tag, माप(*pkt));

	वापस handshake_failure(vio);
पूर्ण

अटल पूर्णांक process_dreg_ack(काष्ठा vio_driver_state *vio,
			    काष्ठा vio_dring_रेजिस्टर *pkt)
अणु
	काष्ठा vio_dring_state *dr;

	viodbg(HS, "GOT DRING_REG ACK ident[%llx] "
	       "ndesc[%u] dsz[%u] opt[0x%x] ncookies[%u]\n",
	       (अचिन्हित दीर्घ दीर्घ) pkt->dring_ident,
	       pkt->num_descr, pkt->descr_size, pkt->options,
	       pkt->num_cookies);

	dr = &vio->drings[VIO_DRIVER_TX_RING];

	अगर (!(vio->dr_state & VIO_DR_STATE_TXREQ))
		वापस handshake_failure(vio);

	dr->ident = pkt->dring_ident;
	vio->dr_state |= VIO_DR_STATE_TXREG;

	अगर (all_drings_रेजिस्टरed(vio)) अणु
		अगर (send_rdx(vio) < 0)
			वापस handshake_failure(vio);
		vio->hs_state = VIO_HS_SENT_RDX;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक process_dreg_nack(काष्ठा vio_driver_state *vio,
			     काष्ठा vio_dring_रेजिस्टर *pkt)
अणु
	viodbg(HS, "GOT DRING_REG NACK ident[%llx] "
	       "ndesc[%u] dsz[%u] opt[0x%x] ncookies[%u]\n",
	       (अचिन्हित दीर्घ दीर्घ) pkt->dring_ident,
	       pkt->num_descr, pkt->descr_size, pkt->options,
	       pkt->num_cookies);

	वापस handshake_failure(vio);
पूर्ण

अटल पूर्णांक process_dreg(काष्ठा vio_driver_state *vio,
			काष्ठा vio_dring_रेजिस्टर *pkt)
अणु
	अगर (!(vio->hs_state & VIO_HS_GOTVERS))
		वापस handshake_failure(vio);

	चयन (pkt->tag.stype) अणु
	हाल VIO_SUBTYPE_INFO:
		वापस process_dreg_info(vio, pkt);

	हाल VIO_SUBTYPE_ACK:
		वापस process_dreg_ack(vio, pkt);

	हाल VIO_SUBTYPE_NACK:
		वापस process_dreg_nack(vio, pkt);

	शेष:
		वापस handshake_failure(vio);
	पूर्ण
पूर्ण

अटल पूर्णांक process_dunreg(काष्ठा vio_driver_state *vio,
			  काष्ठा vio_dring_unरेजिस्टर *pkt)
अणु
	काष्ठा vio_dring_state *dr = &vio->drings[VIO_DRIVER_RX_RING];

	viodbg(HS, "GOT DRING_UNREG\n");

	अगर (pkt->dring_ident != dr->ident)
		वापस 0;

	vio->dr_state &= ~VIO_DR_STATE_RXREG;

	स_रखो(dr, 0, माप(*dr));

	kमुक्त(vio->desc_buf);
	vio->desc_buf = शून्य;
	vio->desc_buf_len = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक process_rdx_info(काष्ठा vio_driver_state *vio, काष्ठा vio_rdx *pkt)
अणु
	viodbg(HS, "GOT RDX INFO\n");

	pkt->tag.stype = VIO_SUBTYPE_ACK;
	viodbg(HS, "SEND RDX ACK\n");
	अगर (send_ctrl(vio, &pkt->tag, माप(*pkt)) < 0)
		वापस handshake_failure(vio);

	vio->hs_state |= VIO_HS_SENT_RDX_ACK;
	वापस 0;
पूर्ण

अटल पूर्णांक process_rdx_ack(काष्ठा vio_driver_state *vio, काष्ठा vio_rdx *pkt)
अणु
	viodbg(HS, "GOT RDX ACK\n");

	अगर (!(vio->hs_state & VIO_HS_SENT_RDX))
		वापस handshake_failure(vio);

	vio->hs_state |= VIO_HS_GOT_RDX_ACK;
	वापस 0;
पूर्ण

अटल पूर्णांक process_rdx_nack(काष्ठा vio_driver_state *vio, काष्ठा vio_rdx *pkt)
अणु
	viodbg(HS, "GOT RDX NACK\n");

	वापस handshake_failure(vio);
पूर्ण

अटल पूर्णांक process_rdx(काष्ठा vio_driver_state *vio, काष्ठा vio_rdx *pkt)
अणु
	अगर (!all_drings_रेजिस्टरed(vio))
		handshake_failure(vio);

	चयन (pkt->tag.stype) अणु
	हाल VIO_SUBTYPE_INFO:
		वापस process_rdx_info(vio, pkt);

	हाल VIO_SUBTYPE_ACK:
		वापस process_rdx_ack(vio, pkt);

	हाल VIO_SUBTYPE_NACK:
		वापस process_rdx_nack(vio, pkt);

	शेष:
		वापस handshake_failure(vio);
	पूर्ण
पूर्ण

पूर्णांक vio_control_pkt_engine(काष्ठा vio_driver_state *vio, व्योम *pkt)
अणु
	काष्ठा vio_msg_tag *tag = pkt;
	u8 prev_state = vio->hs_state;
	पूर्णांक err;

	चयन (tag->stype_env) अणु
	हाल VIO_VER_INFO:
		err = process_ver(vio, pkt);
		अवरोध;

	हाल VIO_ATTR_INFO:
		err = process_attr(vio, pkt);
		अवरोध;

	हाल VIO_DRING_REG:
		err = process_dreg(vio, pkt);
		अवरोध;

	हाल VIO_DRING_UNREG:
		err = process_dunreg(vio, pkt);
		अवरोध;

	हाल VIO_RDX:
		err = process_rdx(vio, pkt);
		अवरोध;

	शेष:
		err = process_unknown(vio, pkt);
		अवरोध;
	पूर्ण

	अगर (!err &&
	    vio->hs_state != prev_state &&
	    (vio->hs_state & VIO_HS_COMPLETE)) अणु
		अगर (vio->ops)
			vio->ops->handshake_complete(vio);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(vio_control_pkt_engine);

व्योम vio_conn_reset(काष्ठा vio_driver_state *vio)
अणु
पूर्ण
EXPORT_SYMBOL(vio_conn_reset);

/* The issue is that the Solaris भव disk server just mirrors the
 * SID values it माला_लो from the client peer.  So we work around that
 * here in vio_अणुvalidate,sendपूर्ण_sid() so that the drivers करोn't need
 * to be aware of this crap.
 */
पूर्णांक vio_validate_sid(काष्ठा vio_driver_state *vio, काष्ठा vio_msg_tag *tp)
अणु
	u32 sid;

	/* Always let VERSION+INFO packets through unchecked, they
	 * define the new SID.
	 */
	अगर (tp->type == VIO_TYPE_CTRL &&
	    tp->stype == VIO_SUBTYPE_INFO &&
	    tp->stype_env == VIO_VER_INFO)
		वापस 0;

	/* Ok, now figure out which SID to use.  */
	चयन (vio->dev_class) अणु
	हाल VDEV_NETWORK:
	हाल VDEV_NETWORK_SWITCH:
	हाल VDEV_DISK_SERVER:
	शेष:
		sid = vio->_peer_sid;
		अवरोध;

	हाल VDEV_DISK:
		sid = vio->_local_sid;
		अवरोध;
	पूर्ण

	अगर (sid == tp->sid)
		वापस 0;
	viodbg(DATA, "BAD SID tag->sid[%08x] peer_sid[%08x] local_sid[%08x]\n",
	       tp->sid, vio->_peer_sid, vio->_local_sid);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(vio_validate_sid);

u32 vio_send_sid(काष्ठा vio_driver_state *vio)
अणु
	चयन (vio->dev_class) अणु
	हाल VDEV_NETWORK:
	हाल VDEV_NETWORK_SWITCH:
	हाल VDEV_DISK:
	शेष:
		वापस vio->_local_sid;

	हाल VDEV_DISK_SERVER:
		वापस vio->_peer_sid;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(vio_send_sid);

पूर्णांक vio_ldc_alloc(काष्ठा vio_driver_state *vio,
			 काष्ठा ldc_channel_config *base_cfg,
			 व्योम *event_arg)
अणु
	काष्ठा ldc_channel_config cfg = *base_cfg;
	काष्ठा ldc_channel *lp;

	cfg.tx_irq = vio->vdev->tx_irq;
	cfg.rx_irq = vio->vdev->rx_irq;

	lp = ldc_alloc(vio->vdev->channel_id, &cfg, event_arg, vio->name);
	अगर (IS_ERR(lp))
		वापस PTR_ERR(lp);

	vio->lp = lp;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vio_ldc_alloc);

व्योम vio_ldc_मुक्त(काष्ठा vio_driver_state *vio)
अणु
	ldc_मुक्त(vio->lp);
	vio->lp = शून्य;

	kमुक्त(vio->desc_buf);
	vio->desc_buf = शून्य;
	vio->desc_buf_len = 0;
पूर्ण
EXPORT_SYMBOL(vio_ldc_मुक्त);

व्योम vio_port_up(काष्ठा vio_driver_state *vio)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err, state;

	spin_lock_irqsave(&vio->lock, flags);

	state = ldc_state(vio->lp);

	err = 0;
	अगर (state == LDC_STATE_INIT) अणु
		err = ldc_bind(vio->lp);
		अगर (err)
			prपूर्णांकk(KERN_WARNING "%s: Port %lu bind failed, "
			       "err=%d\n",
			       vio->name, vio->vdev->channel_id, err);
	पूर्ण

	अगर (!err) अणु
		अगर (ldc_mode(vio->lp) == LDC_MODE_RAW)
			ldc_set_state(vio->lp, LDC_STATE_CONNECTED);
		अन्यथा
			err = ldc_connect(vio->lp);

		अगर (err)
			prपूर्णांकk(KERN_WARNING "%s: Port %lu connect failed, "
			       "err=%d\n",
			       vio->name, vio->vdev->channel_id, err);
	पूर्ण
	अगर (err) अणु
		अचिन्हित दीर्घ expires = jअगरfies + HZ;

		expires = round_jअगरfies(expires);
		mod_समयr(&vio->समयr, expires);
	पूर्ण

	spin_unlock_irqrestore(&vio->lock, flags);
पूर्ण
EXPORT_SYMBOL(vio_port_up);

अटल व्योम vio_port_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा vio_driver_state *vio = from_समयr(vio, t, समयr);

	vio_port_up(vio);
पूर्ण

पूर्णांक vio_driver_init(काष्ठा vio_driver_state *vio, काष्ठा vio_dev *vdev,
		    u8 dev_class, काष्ठा vio_version *ver_table,
		    पूर्णांक ver_table_size, काष्ठा vio_driver_ops *ops,
		    अक्षर *name)
अणु
	चयन (dev_class) अणु
	हाल VDEV_NETWORK:
	हाल VDEV_NETWORK_SWITCH:
	हाल VDEV_DISK:
	हाल VDEV_DISK_SERVER:
	हाल VDEV_CONSOLE_CON:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (dev_class == VDEV_NETWORK ||
	    dev_class == VDEV_NETWORK_SWITCH ||
	    dev_class == VDEV_DISK ||
	    dev_class == VDEV_DISK_SERVER) अणु
		अगर (!ops || !ops->send_attr || !ops->handle_attr ||
		    !ops->handshake_complete)
			वापस -EINVAL;
	पूर्ण

	अगर (!ver_table || ver_table_size < 0)
		वापस -EINVAL;

	अगर (!name)
		वापस -EINVAL;

	spin_lock_init(&vio->lock);

	vio->name = name;

	vio->dev_class = dev_class;
	vio->vdev = vdev;

	vio->ver_table = ver_table;
	vio->ver_table_entries = ver_table_size;

	vio->ops = ops;

	समयr_setup(&vio->समयr, vio_port_समयr, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vio_driver_init);
