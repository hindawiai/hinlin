<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/* gw.c - CAN frame Gateway/Router/Bridge with netlink पूर्णांकerface
 *
 * Copyright (c) 2019 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rculist.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/can.h>
#समावेश <linux/can/core.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/can/gw.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>

#घोषणा CAN_GW_NAME "can-gw"

MODULE_DESCRIPTION("PF_CAN netlink gateway");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Oliver Hartkopp <oliver.hartkopp@volkswagen.de>");
MODULE_ALIAS(CAN_GW_NAME);

#घोषणा CGW_MIN_HOPS 1
#घोषणा CGW_MAX_HOPS 6
#घोषणा CGW_DEFAULT_HOPS 1

अटल अचिन्हित पूर्णांक max_hops __पढ़ो_mostly = CGW_DEFAULT_HOPS;
module_param(max_hops, uपूर्णांक, 0444);
MODULE_PARM_DESC(max_hops,
		 "maximum " CAN_GW_NAME " routing hops for CAN frames "
		 "(valid values: " __stringअगरy(CGW_MIN_HOPS) "-"
		 __stringअगरy(CGW_MAX_HOPS) " hops, "
		 "default: " __stringअगरy(CGW_DEFAULT_HOPS) ")");

अटल काष्ठा notअगरier_block notअगरier;
अटल काष्ठा kmem_cache *cgw_cache __पढ़ो_mostly;

/* काष्ठाure that contains the (on-the-fly) CAN frame modअगरications */
काष्ठा cf_mod अणु
	काष्ठा अणु
		काष्ठा canfd_frame and;
		काष्ठा canfd_frame or;
		काष्ठा canfd_frame xor;
		काष्ठा canfd_frame set;
	पूर्ण modframe;
	काष्ठा अणु
		u8 and;
		u8 or;
		u8 xor;
		u8 set;
	पूर्ण modtype;
	व्योम (*modfunc[MAX_MODFUNCTIONS])(काष्ठा canfd_frame *cf,
					  काष्ठा cf_mod *mod);

	/* CAN frame checksum calculation after CAN frame modअगरications */
	काष्ठा अणु
		काष्ठा cgw_csum_xor xor;
		काष्ठा cgw_csum_crc8 crc8;
	पूर्ण csum;
	काष्ठा अणु
		व्योम (*xor)(काष्ठा canfd_frame *cf,
			    काष्ठा cgw_csum_xor *xor);
		व्योम (*crc8)(काष्ठा canfd_frame *cf,
			     काष्ठा cgw_csum_crc8 *crc8);
	पूर्ण csumfunc;
	u32 uid;
पूर्ण;

/* So far we just support CAN -> CAN routing and frame modअगरications.
 *
 * The पूर्णांकernal can_can_gw काष्ठाure contains data and attributes क्रम
 * a CAN -> CAN gateway job.
 */
काष्ठा can_can_gw अणु
	काष्ठा can_filter filter;
	पूर्णांक src_idx;
	पूर्णांक dst_idx;
पूर्ण;

/* list entry क्रम CAN gateways jobs */
काष्ठा cgw_job अणु
	काष्ठा hlist_node list;
	काष्ठा rcu_head rcu;
	u32 handled_frames;
	u32 dropped_frames;
	u32 deleted_frames;
	काष्ठा cf_mod mod;
	जोड़ अणु
		/* CAN frame data source */
		काष्ठा net_device *dev;
	पूर्ण src;
	जोड़ अणु
		/* CAN frame data destination */
		काष्ठा net_device *dev;
	पूर्ण dst;
	जोड़ अणु
		काष्ठा can_can_gw ccgw;
		/* tbc */
	पूर्ण;
	u8 gwtype;
	u8 limit_hops;
	u16 flags;
पूर्ण;

/* modअगरication functions that are invoked in the hot path in can_can_gw_rcv */

#घोषणा MODFUNC(func, op) अटल व्योम func(काष्ठा canfd_frame *cf, \
					   काष्ठा cf_mod *mod) अणु op ; पूर्ण

MODFUNC(mod_and_id, cf->can_id &= mod->modframe.and.can_id)
MODFUNC(mod_and_len, cf->len &= mod->modframe.and.len)
MODFUNC(mod_and_flags, cf->flags &= mod->modframe.and.flags)
MODFUNC(mod_and_data, *(u64 *)cf->data &= *(u64 *)mod->modframe.and.data)
MODFUNC(mod_or_id, cf->can_id |= mod->modframe.or.can_id)
MODFUNC(mod_or_len, cf->len |= mod->modframe.or.len)
MODFUNC(mod_or_flags, cf->flags |= mod->modframe.or.flags)
MODFUNC(mod_or_data, *(u64 *)cf->data |= *(u64 *)mod->modframe.or.data)
MODFUNC(mod_xor_id, cf->can_id ^= mod->modframe.xor.can_id)
MODFUNC(mod_xor_len, cf->len ^= mod->modframe.xor.len)
MODFUNC(mod_xor_flags, cf->flags ^= mod->modframe.xor.flags)
MODFUNC(mod_xor_data, *(u64 *)cf->data ^= *(u64 *)mod->modframe.xor.data)
MODFUNC(mod_set_id, cf->can_id = mod->modframe.set.can_id)
MODFUNC(mod_set_len, cf->len = mod->modframe.set.len)
MODFUNC(mod_set_flags, cf->flags = mod->modframe.set.flags)
MODFUNC(mod_set_data, *(u64 *)cf->data = *(u64 *)mod->modframe.set.data)

अटल व्योम mod_and_fddata(काष्ठा canfd_frame *cf, काष्ठा cf_mod *mod)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CANFD_MAX_DLEN; i += 8)
		*(u64 *)(cf->data + i) &= *(u64 *)(mod->modframe.and.data + i);
पूर्ण

अटल व्योम mod_or_fddata(काष्ठा canfd_frame *cf, काष्ठा cf_mod *mod)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CANFD_MAX_DLEN; i += 8)
		*(u64 *)(cf->data + i) |= *(u64 *)(mod->modframe.or.data + i);
पूर्ण

अटल व्योम mod_xor_fddata(काष्ठा canfd_frame *cf, काष्ठा cf_mod *mod)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CANFD_MAX_DLEN; i += 8)
		*(u64 *)(cf->data + i) ^= *(u64 *)(mod->modframe.xor.data + i);
पूर्ण

अटल व्योम mod_set_fddata(काष्ठा canfd_frame *cf, काष्ठा cf_mod *mod)
अणु
	स_नकल(cf->data, mod->modframe.set.data, CANFD_MAX_DLEN);
पूर्ण

/* retrieve valid CC DLC value and store it पूर्णांकo 'len' */
अटल व्योम mod_retrieve_ccdlc(काष्ठा canfd_frame *cf)
अणु
	काष्ठा can_frame *ccf = (काष्ठा can_frame *)cf;

	/* len8_dlc is only valid अगर len == CAN_MAX_DLEN */
	अगर (ccf->len != CAN_MAX_DLEN)
		वापस;

	/* करो we have a valid len8_dlc value from 9 .. 15 ? */
	अगर (ccf->len8_dlc > CAN_MAX_DLEN && ccf->len8_dlc <= CAN_MAX_RAW_DLC)
		ccf->len = ccf->len8_dlc;
पूर्ण

/* convert valid CC DLC value in 'len' पूर्णांकo काष्ठा can_frame elements */
अटल व्योम mod_store_ccdlc(काष्ठा canfd_frame *cf)
अणु
	काष्ठा can_frame *ccf = (काष्ठा can_frame *)cf;

	/* clear potential leftovers */
	ccf->len8_dlc = 0;

	/* plain data length 0 .. 8 - that was easy */
	अगर (ccf->len <= CAN_MAX_DLEN)
		वापस;

	/* potentially broken values are caught in can_can_gw_rcv() */
	अगर (ccf->len > CAN_MAX_RAW_DLC)
		वापस;

	/* we have a valid dlc value from 9 .. 15 in ccf->len */
	ccf->len8_dlc = ccf->len;
	ccf->len = CAN_MAX_DLEN;
पूर्ण

अटल व्योम mod_and_ccdlc(काष्ठा canfd_frame *cf, काष्ठा cf_mod *mod)
अणु
	mod_retrieve_ccdlc(cf);
	mod_and_len(cf, mod);
	mod_store_ccdlc(cf);
पूर्ण

अटल व्योम mod_or_ccdlc(काष्ठा canfd_frame *cf, काष्ठा cf_mod *mod)
अणु
	mod_retrieve_ccdlc(cf);
	mod_or_len(cf, mod);
	mod_store_ccdlc(cf);
पूर्ण

अटल व्योम mod_xor_ccdlc(काष्ठा canfd_frame *cf, काष्ठा cf_mod *mod)
अणु
	mod_retrieve_ccdlc(cf);
	mod_xor_len(cf, mod);
	mod_store_ccdlc(cf);
पूर्ण

अटल व्योम mod_set_ccdlc(काष्ठा canfd_frame *cf, काष्ठा cf_mod *mod)
अणु
	mod_set_len(cf, mod);
	mod_store_ccdlc(cf);
पूर्ण

अटल व्योम canframecpy(काष्ठा canfd_frame *dst, काष्ठा can_frame *src)
अणु
	/* Copy the काष्ठा members separately to ensure that no uninitialized
	 * data are copied in the 3 bytes hole of the काष्ठा. This is needed
	 * to make easy compares of the data in the काष्ठा cf_mod.
	 */

	dst->can_id = src->can_id;
	dst->len = src->len;
	*(u64 *)dst->data = *(u64 *)src->data;
पूर्ण

अटल व्योम canfdframecpy(काष्ठा canfd_frame *dst, काष्ठा canfd_frame *src)
अणु
	/* Copy the काष्ठा members separately to ensure that no uninitialized
	 * data are copied in the 2 bytes hole of the काष्ठा. This is needed
	 * to make easy compares of the data in the काष्ठा cf_mod.
	 */

	dst->can_id = src->can_id;
	dst->flags = src->flags;
	dst->len = src->len;
	स_नकल(dst->data, src->data, CANFD_MAX_DLEN);
पूर्ण

अटल पूर्णांक cgw_chk_csum_parms(s8 fr, s8 to, s8 re, काष्ठा rtcanmsg *r)
अणु
	s8 dlen = CAN_MAX_DLEN;

	अगर (r->flags & CGW_FLAGS_CAN_FD)
		dlen = CANFD_MAX_DLEN;

	/* असलolute dlc values 0 .. 7 => 0 .. 7, e.g. data [0]
	 * relative to received dlc -1 .. -8 :
	 * e.g. क्रम received dlc = 8
	 * -1 => index = 7 (data[7])
	 * -3 => index = 5 (data[5])
	 * -8 => index = 0 (data[0])
	 */

	अगर (fr >= -dlen && fr < dlen &&
	    to >= -dlen && to < dlen &&
	    re >= -dlen && re < dlen)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक calc_idx(पूर्णांक idx, पूर्णांक rx_len)
अणु
	अगर (idx < 0)
		वापस rx_len + idx;
	अन्यथा
		वापस idx;
पूर्ण

अटल व्योम cgw_csum_xor_rel(काष्ठा canfd_frame *cf, काष्ठा cgw_csum_xor *xor)
अणु
	पूर्णांक from = calc_idx(xor->from_idx, cf->len);
	पूर्णांक to = calc_idx(xor->to_idx, cf->len);
	पूर्णांक res = calc_idx(xor->result_idx, cf->len);
	u8 val = xor->init_xor_val;
	पूर्णांक i;

	अगर (from < 0 || to < 0 || res < 0)
		वापस;

	अगर (from <= to) अणु
		क्रम (i = from; i <= to; i++)
			val ^= cf->data[i];
	पूर्ण अन्यथा अणु
		क्रम (i = from; i >= to; i--)
			val ^= cf->data[i];
	पूर्ण

	cf->data[res] = val;
पूर्ण

अटल व्योम cgw_csum_xor_pos(काष्ठा canfd_frame *cf, काष्ठा cgw_csum_xor *xor)
अणु
	u8 val = xor->init_xor_val;
	पूर्णांक i;

	क्रम (i = xor->from_idx; i <= xor->to_idx; i++)
		val ^= cf->data[i];

	cf->data[xor->result_idx] = val;
पूर्ण

अटल व्योम cgw_csum_xor_neg(काष्ठा canfd_frame *cf, काष्ठा cgw_csum_xor *xor)
अणु
	u8 val = xor->init_xor_val;
	पूर्णांक i;

	क्रम (i = xor->from_idx; i >= xor->to_idx; i--)
		val ^= cf->data[i];

	cf->data[xor->result_idx] = val;
पूर्ण

अटल व्योम cgw_csum_crc8_rel(काष्ठा canfd_frame *cf,
			      काष्ठा cgw_csum_crc8 *crc8)
अणु
	पूर्णांक from = calc_idx(crc8->from_idx, cf->len);
	पूर्णांक to = calc_idx(crc8->to_idx, cf->len);
	पूर्णांक res = calc_idx(crc8->result_idx, cf->len);
	u8 crc = crc8->init_crc_val;
	पूर्णांक i;

	अगर (from < 0 || to < 0 || res < 0)
		वापस;

	अगर (from <= to) अणु
		क्रम (i = crc8->from_idx; i <= crc8->to_idx; i++)
			crc = crc8->crctab[crc ^ cf->data[i]];
	पूर्ण अन्यथा अणु
		क्रम (i = crc8->from_idx; i >= crc8->to_idx; i--)
			crc = crc8->crctab[crc ^ cf->data[i]];
	पूर्ण

	चयन (crc8->profile) अणु
	हाल CGW_CRC8PRF_1U8:
		crc = crc8->crctab[crc ^ crc8->profile_data[0]];
		अवरोध;

	हाल  CGW_CRC8PRF_16U8:
		crc = crc8->crctab[crc ^ crc8->profile_data[cf->data[1] & 0xF]];
		अवरोध;

	हाल CGW_CRC8PRF_SFFID_XOR:
		crc = crc8->crctab[crc ^ (cf->can_id & 0xFF) ^
				   (cf->can_id >> 8 & 0xFF)];
		अवरोध;
	पूर्ण

	cf->data[crc8->result_idx] = crc ^ crc8->final_xor_val;
पूर्ण

अटल व्योम cgw_csum_crc8_pos(काष्ठा canfd_frame *cf,
			      काष्ठा cgw_csum_crc8 *crc8)
अणु
	u8 crc = crc8->init_crc_val;
	पूर्णांक i;

	क्रम (i = crc8->from_idx; i <= crc8->to_idx; i++)
		crc = crc8->crctab[crc ^ cf->data[i]];

	चयन (crc8->profile) अणु
	हाल CGW_CRC8PRF_1U8:
		crc = crc8->crctab[crc ^ crc8->profile_data[0]];
		अवरोध;

	हाल  CGW_CRC8PRF_16U8:
		crc = crc8->crctab[crc ^ crc8->profile_data[cf->data[1] & 0xF]];
		अवरोध;

	हाल CGW_CRC8PRF_SFFID_XOR:
		crc = crc8->crctab[crc ^ (cf->can_id & 0xFF) ^
				   (cf->can_id >> 8 & 0xFF)];
		अवरोध;
	पूर्ण

	cf->data[crc8->result_idx] = crc ^ crc8->final_xor_val;
पूर्ण

अटल व्योम cgw_csum_crc8_neg(काष्ठा canfd_frame *cf,
			      काष्ठा cgw_csum_crc8 *crc8)
अणु
	u8 crc = crc8->init_crc_val;
	पूर्णांक i;

	क्रम (i = crc8->from_idx; i >= crc8->to_idx; i--)
		crc = crc8->crctab[crc ^ cf->data[i]];

	चयन (crc8->profile) अणु
	हाल CGW_CRC8PRF_1U8:
		crc = crc8->crctab[crc ^ crc8->profile_data[0]];
		अवरोध;

	हाल  CGW_CRC8PRF_16U8:
		crc = crc8->crctab[crc ^ crc8->profile_data[cf->data[1] & 0xF]];
		अवरोध;

	हाल CGW_CRC8PRF_SFFID_XOR:
		crc = crc8->crctab[crc ^ (cf->can_id & 0xFF) ^
				   (cf->can_id >> 8 & 0xFF)];
		अवरोध;
	पूर्ण

	cf->data[crc8->result_idx] = crc ^ crc8->final_xor_val;
पूर्ण

/* the receive & process & send function */
अटल व्योम can_can_gw_rcv(काष्ठा sk_buff *skb, व्योम *data)
अणु
	काष्ठा cgw_job *gwj = (काष्ठा cgw_job *)data;
	काष्ठा canfd_frame *cf;
	काष्ठा sk_buff *nskb;
	पूर्णांक modidx = 0;

	/* process strictly Classic CAN or CAN FD frames */
	अगर (gwj->flags & CGW_FLAGS_CAN_FD) अणु
		अगर (skb->len != CANFD_MTU)
			वापस;
	पूर्ण अन्यथा अणु
		अगर (skb->len != CAN_MTU)
			वापस;
	पूर्ण

	/* Do not handle CAN frames routed more than 'max_hops' बार.
	 * In general we should never catch this delimiter which is पूर्णांकended
	 * to cover a misconfiguration protection (e.g. circular CAN routes).
	 *
	 * The Controller Area Network controllers only accept CAN frames with
	 * correct CRCs - which are not visible in the controller रेजिस्टरs.
	 * According to skbuff.h करोcumentation the csum_start element क्रम IP
	 * checksums is undefined/unused when ip_summed == CHECKSUM_UNNECESSARY.
	 * Only CAN skbs can be processed here which alपढ़ोy have this property.
	 */

#घोषणा cgw_hops(skb) ((skb)->csum_start)

	BUG_ON(skb->ip_summed != CHECKSUM_UNNECESSARY);

	अगर (cgw_hops(skb) >= max_hops) अणु
		/* indicate deleted frames due to misconfiguration */
		gwj->deleted_frames++;
		वापस;
	पूर्ण

	अगर (!(gwj->dst.dev->flags & IFF_UP)) अणु
		gwj->dropped_frames++;
		वापस;
	पूर्ण

	/* is sending the skb back to the incoming पूर्णांकerface not allowed? */
	अगर (!(gwj->flags & CGW_FLAGS_CAN_IIF_TX_OK) &&
	    can_skb_prv(skb)->अगरindex == gwj->dst.dev->अगरindex)
		वापस;

	/* clone the given skb, which has not been करोne in can_rcv()
	 *
	 * When there is at least one modअगरication function activated,
	 * we need to copy the skb as we want to modअगरy skb->data.
	 */
	अगर (gwj->mod.modfunc[0])
		nskb = skb_copy(skb, GFP_ATOMIC);
	अन्यथा
		nskb = skb_clone(skb, GFP_ATOMIC);

	अगर (!nskb) अणु
		gwj->dropped_frames++;
		वापस;
	पूर्ण

	/* put the incremented hop counter in the cloned skb */
	cgw_hops(nskb) = cgw_hops(skb) + 1;

	/* first processing of this CAN frame -> adjust to निजी hop limit */
	अगर (gwj->limit_hops && cgw_hops(nskb) == 1)
		cgw_hops(nskb) = max_hops - gwj->limit_hops + 1;

	nskb->dev = gwj->dst.dev;

	/* poपूर्णांकer to modअगरiable CAN frame */
	cf = (काष्ठा canfd_frame *)nskb->data;

	/* perक्रमm preprocessed modअगरication functions अगर there are any */
	जबतक (modidx < MAX_MODFUNCTIONS && gwj->mod.modfunc[modidx])
		(*gwj->mod.modfunc[modidx++])(cf, &gwj->mod);

	/* Has the CAN frame been modअगरied? */
	अगर (modidx) अणु
		/* get available space क्रम the processed CAN frame type */
		पूर्णांक max_len = nskb->len - दुरत्व(काष्ठा canfd_frame, data);

		/* dlc may have changed, make sure it fits to the CAN frame */
		अगर (cf->len > max_len) अणु
			/* delete frame due to misconfiguration */
			gwj->deleted_frames++;
			kमुक्त_skb(nskb);
			वापस;
		पूर्ण

		/* check क्रम checksum updates */
		अगर (gwj->mod.csumfunc.crc8)
			(*gwj->mod.csumfunc.crc8)(cf, &gwj->mod.csum.crc8);

		अगर (gwj->mod.csumfunc.xor)
			(*gwj->mod.csumfunc.xor)(cf, &gwj->mod.csum.xor);
	पूर्ण

	/* clear the skb बारtamp अगर not configured the other way */
	अगर (!(gwj->flags & CGW_FLAGS_CAN_SRC_TSTAMP))
		nskb->tstamp = 0;

	/* send to netdevice */
	अगर (can_send(nskb, gwj->flags & CGW_FLAGS_CAN_ECHO))
		gwj->dropped_frames++;
	अन्यथा
		gwj->handled_frames++;
पूर्ण

अटल अंतरभूत पूर्णांक cgw_रेजिस्टर_filter(काष्ठा net *net, काष्ठा cgw_job *gwj)
अणु
	वापस can_rx_रेजिस्टर(net, gwj->src.dev, gwj->ccgw.filter.can_id,
			       gwj->ccgw.filter.can_mask, can_can_gw_rcv,
			       gwj, "gw", शून्य);
पूर्ण

अटल अंतरभूत व्योम cgw_unरेजिस्टर_filter(काष्ठा net *net, काष्ठा cgw_job *gwj)
अणु
	can_rx_unरेजिस्टर(net, gwj->src.dev, gwj->ccgw.filter.can_id,
			  gwj->ccgw.filter.can_mask, can_can_gw_rcv, gwj);
पूर्ण

अटल पूर्णांक cgw_notअगरier(काष्ठा notअगरier_block *nb,
			अचिन्हित दीर्घ msg, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);

	अगर (dev->type != ARPHRD_CAN)
		वापस NOTIFY_DONE;

	अगर (msg == NETDEV_UNREGISTER) अणु
		काष्ठा cgw_job *gwj = शून्य;
		काष्ठा hlist_node *nx;

		ASSERT_RTNL();

		hlist_क्रम_each_entry_safe(gwj, nx, &net->can.cgw_list, list) अणु
			अगर (gwj->src.dev == dev || gwj->dst.dev == dev) अणु
				hlist_del(&gwj->list);
				cgw_unरेजिस्टर_filter(net, gwj);
				kmem_cache_मुक्त(cgw_cache, gwj);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक cgw_put_job(काष्ठा sk_buff *skb, काष्ठा cgw_job *gwj, पूर्णांक type,
		       u32 pid, u32 seq, पूर्णांक flags)
अणु
	काष्ठा rtcanmsg *rtcan;
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put(skb, pid, seq, type, माप(*rtcan), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	rtcan = nlmsg_data(nlh);
	rtcan->can_family = AF_CAN;
	rtcan->gwtype = gwj->gwtype;
	rtcan->flags = gwj->flags;

	/* add statistics अगर available */

	अगर (gwj->handled_frames) अणु
		अगर (nla_put_u32(skb, CGW_HANDLED, gwj->handled_frames) < 0)
			जाओ cancel;
	पूर्ण

	अगर (gwj->dropped_frames) अणु
		अगर (nla_put_u32(skb, CGW_DROPPED, gwj->dropped_frames) < 0)
			जाओ cancel;
	पूर्ण

	अगर (gwj->deleted_frames) अणु
		अगर (nla_put_u32(skb, CGW_DELETED, gwj->deleted_frames) < 0)
			जाओ cancel;
	पूर्ण

	/* check non शेष settings of attributes */

	अगर (gwj->limit_hops) अणु
		अगर (nla_put_u8(skb, CGW_LIM_HOPS, gwj->limit_hops) < 0)
			जाओ cancel;
	पूर्ण

	अगर (gwj->flags & CGW_FLAGS_CAN_FD) अणु
		काष्ठा cgw_fdframe_mod mb;

		अगर (gwj->mod.modtype.and) अणु
			स_नकल(&mb.cf, &gwj->mod.modframe.and, माप(mb.cf));
			mb.modtype = gwj->mod.modtype.and;
			अगर (nla_put(skb, CGW_FDMOD_AND, माप(mb), &mb) < 0)
				जाओ cancel;
		पूर्ण

		अगर (gwj->mod.modtype.or) अणु
			स_नकल(&mb.cf, &gwj->mod.modframe.or, माप(mb.cf));
			mb.modtype = gwj->mod.modtype.or;
			अगर (nla_put(skb, CGW_FDMOD_OR, माप(mb), &mb) < 0)
				जाओ cancel;
		पूर्ण

		अगर (gwj->mod.modtype.xor) अणु
			स_नकल(&mb.cf, &gwj->mod.modframe.xor, माप(mb.cf));
			mb.modtype = gwj->mod.modtype.xor;
			अगर (nla_put(skb, CGW_FDMOD_XOR, माप(mb), &mb) < 0)
				जाओ cancel;
		पूर्ण

		अगर (gwj->mod.modtype.set) अणु
			स_नकल(&mb.cf, &gwj->mod.modframe.set, माप(mb.cf));
			mb.modtype = gwj->mod.modtype.set;
			अगर (nla_put(skb, CGW_FDMOD_SET, माप(mb), &mb) < 0)
				जाओ cancel;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा cgw_frame_mod mb;

		अगर (gwj->mod.modtype.and) अणु
			स_नकल(&mb.cf, &gwj->mod.modframe.and, माप(mb.cf));
			mb.modtype = gwj->mod.modtype.and;
			अगर (nla_put(skb, CGW_MOD_AND, माप(mb), &mb) < 0)
				जाओ cancel;
		पूर्ण

		अगर (gwj->mod.modtype.or) अणु
			स_नकल(&mb.cf, &gwj->mod.modframe.or, माप(mb.cf));
			mb.modtype = gwj->mod.modtype.or;
			अगर (nla_put(skb, CGW_MOD_OR, माप(mb), &mb) < 0)
				जाओ cancel;
		पूर्ण

		अगर (gwj->mod.modtype.xor) अणु
			स_नकल(&mb.cf, &gwj->mod.modframe.xor, माप(mb.cf));
			mb.modtype = gwj->mod.modtype.xor;
			अगर (nla_put(skb, CGW_MOD_XOR, माप(mb), &mb) < 0)
				जाओ cancel;
		पूर्ण

		अगर (gwj->mod.modtype.set) अणु
			स_नकल(&mb.cf, &gwj->mod.modframe.set, माप(mb.cf));
			mb.modtype = gwj->mod.modtype.set;
			अगर (nla_put(skb, CGW_MOD_SET, माप(mb), &mb) < 0)
				जाओ cancel;
		पूर्ण
	पूर्ण

	अगर (gwj->mod.uid) अणु
		अगर (nla_put_u32(skb, CGW_MOD_UID, gwj->mod.uid) < 0)
			जाओ cancel;
	पूर्ण

	अगर (gwj->mod.csumfunc.crc8) अणु
		अगर (nla_put(skb, CGW_CS_CRC8, CGW_CS_CRC8_LEN,
			    &gwj->mod.csum.crc8) < 0)
			जाओ cancel;
	पूर्ण

	अगर (gwj->mod.csumfunc.xor) अणु
		अगर (nla_put(skb, CGW_CS_XOR, CGW_CS_XOR_LEN,
			    &gwj->mod.csum.xor) < 0)
			जाओ cancel;
	पूर्ण

	अगर (gwj->gwtype == CGW_TYPE_CAN_CAN) अणु
		अगर (gwj->ccgw.filter.can_id || gwj->ccgw.filter.can_mask) अणु
			अगर (nla_put(skb, CGW_FILTER, माप(काष्ठा can_filter),
				    &gwj->ccgw.filter) < 0)
				जाओ cancel;
		पूर्ण

		अगर (nla_put_u32(skb, CGW_SRC_IF, gwj->ccgw.src_idx) < 0)
			जाओ cancel;

		अगर (nla_put_u32(skb, CGW_DST_IF, gwj->ccgw.dst_idx) < 0)
			जाओ cancel;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;

cancel:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

/* Dump inक्रमmation about all CAN gateway jobs, in response to RTM_GETROUTE */
अटल पूर्णांक cgw_dump_jobs(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा cgw_job *gwj = शून्य;
	पूर्णांक idx = 0;
	पूर्णांक s_idx = cb->args[0];

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(gwj, &net->can.cgw_list, list) अणु
		अगर (idx < s_idx)
			जाओ cont;

		अगर (cgw_put_job(skb, gwj, RTM_NEWROUTE,
				NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq, NLM_F_MULTI) < 0)
			अवरोध;
cont:
		idx++;
	पूर्ण
	rcu_पढ़ो_unlock();

	cb->args[0] = idx;

	वापस skb->len;
पूर्ण

अटल स्थिर काष्ठा nla_policy cgw_policy[CGW_MAX + 1] = अणु
	[CGW_MOD_AND]	= अणु .len = माप(काष्ठा cgw_frame_mod) पूर्ण,
	[CGW_MOD_OR]	= अणु .len = माप(काष्ठा cgw_frame_mod) पूर्ण,
	[CGW_MOD_XOR]	= अणु .len = माप(काष्ठा cgw_frame_mod) पूर्ण,
	[CGW_MOD_SET]	= अणु .len = माप(काष्ठा cgw_frame_mod) पूर्ण,
	[CGW_CS_XOR]	= अणु .len = माप(काष्ठा cgw_csum_xor) पूर्ण,
	[CGW_CS_CRC8]	= अणु .len = माप(काष्ठा cgw_csum_crc8) पूर्ण,
	[CGW_SRC_IF]	= अणु .type = NLA_U32 पूर्ण,
	[CGW_DST_IF]	= अणु .type = NLA_U32 पूर्ण,
	[CGW_FILTER]	= अणु .len = माप(काष्ठा can_filter) पूर्ण,
	[CGW_LIM_HOPS]	= अणु .type = NLA_U8 पूर्ण,
	[CGW_MOD_UID]	= अणु .type = NLA_U32 पूर्ण,
	[CGW_FDMOD_AND]	= अणु .len = माप(काष्ठा cgw_fdframe_mod) पूर्ण,
	[CGW_FDMOD_OR]	= अणु .len = माप(काष्ठा cgw_fdframe_mod) पूर्ण,
	[CGW_FDMOD_XOR]	= अणु .len = माप(काष्ठा cgw_fdframe_mod) पूर्ण,
	[CGW_FDMOD_SET]	= अणु .len = माप(काष्ठा cgw_fdframe_mod) पूर्ण,
पूर्ण;

/* check क्रम common and gwtype specअगरic attributes */
अटल पूर्णांक cgw_parse_attr(काष्ठा nlmsghdr *nlh, काष्ठा cf_mod *mod,
			  u8 gwtype, व्योम *gwtypeattr, u8 *limhops)
अणु
	काष्ठा nlattr *tb[CGW_MAX + 1];
	काष्ठा rtcanmsg *r = nlmsg_data(nlh);
	पूर्णांक modidx = 0;
	पूर्णांक err = 0;

	/* initialize modअगरication & checksum data space */
	स_रखो(mod, 0, माप(*mod));

	err = nlmsg_parse_deprecated(nlh, माप(काष्ठा rtcanmsg), tb,
				     CGW_MAX, cgw_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[CGW_LIM_HOPS]) अणु
		*limhops = nla_get_u8(tb[CGW_LIM_HOPS]);

		अगर (*limhops < 1 || *limhops > max_hops)
			वापस -EINVAL;
	पूर्ण

	/* check क्रम AND/OR/XOR/SET modअगरications */
	अगर (r->flags & CGW_FLAGS_CAN_FD) अणु
		काष्ठा cgw_fdframe_mod mb;

		अगर (tb[CGW_FDMOD_AND]) अणु
			nla_स_नकल(&mb, tb[CGW_FDMOD_AND], CGW_FDMODATTR_LEN);

			canfdframecpy(&mod->modframe.and, &mb.cf);
			mod->modtype.and = mb.modtype;

			अगर (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_and_id;

			अगर (mb.modtype & CGW_MOD_LEN)
				mod->modfunc[modidx++] = mod_and_len;

			अगर (mb.modtype & CGW_MOD_FLAGS)
				mod->modfunc[modidx++] = mod_and_flags;

			अगर (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_and_fddata;
		पूर्ण

		अगर (tb[CGW_FDMOD_OR]) अणु
			nla_स_नकल(&mb, tb[CGW_FDMOD_OR], CGW_FDMODATTR_LEN);

			canfdframecpy(&mod->modframe.or, &mb.cf);
			mod->modtype.or = mb.modtype;

			अगर (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_or_id;

			अगर (mb.modtype & CGW_MOD_LEN)
				mod->modfunc[modidx++] = mod_or_len;

			अगर (mb.modtype & CGW_MOD_FLAGS)
				mod->modfunc[modidx++] = mod_or_flags;

			अगर (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_or_fddata;
		पूर्ण

		अगर (tb[CGW_FDMOD_XOR]) अणु
			nla_स_नकल(&mb, tb[CGW_FDMOD_XOR], CGW_FDMODATTR_LEN);

			canfdframecpy(&mod->modframe.xor, &mb.cf);
			mod->modtype.xor = mb.modtype;

			अगर (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_xor_id;

			अगर (mb.modtype & CGW_MOD_LEN)
				mod->modfunc[modidx++] = mod_xor_len;

			अगर (mb.modtype & CGW_MOD_FLAGS)
				mod->modfunc[modidx++] = mod_xor_flags;

			अगर (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_xor_fddata;
		पूर्ण

		अगर (tb[CGW_FDMOD_SET]) अणु
			nla_स_नकल(&mb, tb[CGW_FDMOD_SET], CGW_FDMODATTR_LEN);

			canfdframecpy(&mod->modframe.set, &mb.cf);
			mod->modtype.set = mb.modtype;

			अगर (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_set_id;

			अगर (mb.modtype & CGW_MOD_LEN)
				mod->modfunc[modidx++] = mod_set_len;

			अगर (mb.modtype & CGW_MOD_FLAGS)
				mod->modfunc[modidx++] = mod_set_flags;

			अगर (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_set_fddata;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा cgw_frame_mod mb;

		अगर (tb[CGW_MOD_AND]) अणु
			nla_स_नकल(&mb, tb[CGW_MOD_AND], CGW_MODATTR_LEN);

			canframecpy(&mod->modframe.and, &mb.cf);
			mod->modtype.and = mb.modtype;

			अगर (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_and_id;

			अगर (mb.modtype & CGW_MOD_DLC)
				mod->modfunc[modidx++] = mod_and_ccdlc;

			अगर (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_and_data;
		पूर्ण

		अगर (tb[CGW_MOD_OR]) अणु
			nla_स_नकल(&mb, tb[CGW_MOD_OR], CGW_MODATTR_LEN);

			canframecpy(&mod->modframe.or, &mb.cf);
			mod->modtype.or = mb.modtype;

			अगर (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_or_id;

			अगर (mb.modtype & CGW_MOD_DLC)
				mod->modfunc[modidx++] = mod_or_ccdlc;

			अगर (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_or_data;
		पूर्ण

		अगर (tb[CGW_MOD_XOR]) अणु
			nla_स_नकल(&mb, tb[CGW_MOD_XOR], CGW_MODATTR_LEN);

			canframecpy(&mod->modframe.xor, &mb.cf);
			mod->modtype.xor = mb.modtype;

			अगर (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_xor_id;

			अगर (mb.modtype & CGW_MOD_DLC)
				mod->modfunc[modidx++] = mod_xor_ccdlc;

			अगर (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_xor_data;
		पूर्ण

		अगर (tb[CGW_MOD_SET]) अणु
			nla_स_नकल(&mb, tb[CGW_MOD_SET], CGW_MODATTR_LEN);

			canframecpy(&mod->modframe.set, &mb.cf);
			mod->modtype.set = mb.modtype;

			अगर (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_set_id;

			अगर (mb.modtype & CGW_MOD_DLC)
				mod->modfunc[modidx++] = mod_set_ccdlc;

			अगर (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_set_data;
		पूर्ण
	पूर्ण

	/* check क्रम checksum operations after CAN frame modअगरications */
	अगर (modidx) अणु
		अगर (tb[CGW_CS_CRC8]) अणु
			काष्ठा cgw_csum_crc8 *c = nla_data(tb[CGW_CS_CRC8]);

			err = cgw_chk_csum_parms(c->from_idx, c->to_idx,
						 c->result_idx, r);
			अगर (err)
				वापस err;

			nla_स_नकल(&mod->csum.crc8, tb[CGW_CS_CRC8],
				   CGW_CS_CRC8_LEN);

			/* select dedicated processing function to reduce
			 * runसमय operations in receive hot path.
			 */
			अगर (c->from_idx < 0 || c->to_idx < 0 ||
			    c->result_idx < 0)
				mod->csumfunc.crc8 = cgw_csum_crc8_rel;
			अन्यथा अगर (c->from_idx <= c->to_idx)
				mod->csumfunc.crc8 = cgw_csum_crc8_pos;
			अन्यथा
				mod->csumfunc.crc8 = cgw_csum_crc8_neg;
		पूर्ण

		अगर (tb[CGW_CS_XOR]) अणु
			काष्ठा cgw_csum_xor *c = nla_data(tb[CGW_CS_XOR]);

			err = cgw_chk_csum_parms(c->from_idx, c->to_idx,
						 c->result_idx, r);
			अगर (err)
				वापस err;

			nla_स_नकल(&mod->csum.xor, tb[CGW_CS_XOR],
				   CGW_CS_XOR_LEN);

			/* select dedicated processing function to reduce
			 * runसमय operations in receive hot path.
			 */
			अगर (c->from_idx < 0 || c->to_idx < 0 ||
			    c->result_idx < 0)
				mod->csumfunc.xor = cgw_csum_xor_rel;
			अन्यथा अगर (c->from_idx <= c->to_idx)
				mod->csumfunc.xor = cgw_csum_xor_pos;
			अन्यथा
				mod->csumfunc.xor = cgw_csum_xor_neg;
		पूर्ण

		अगर (tb[CGW_MOD_UID])
			nla_स_नकल(&mod->uid, tb[CGW_MOD_UID], माप(u32));
	पूर्ण

	अगर (gwtype == CGW_TYPE_CAN_CAN) अणु
		/* check CGW_TYPE_CAN_CAN specअगरic attributes */
		काष्ठा can_can_gw *ccgw = (काष्ठा can_can_gw *)gwtypeattr;

		स_रखो(ccgw, 0, माप(*ccgw));

		/* check क्रम can_filter in attributes */
		अगर (tb[CGW_FILTER])
			nla_स_नकल(&ccgw->filter, tb[CGW_FILTER],
				   माप(काष्ठा can_filter));

		err = -ENODEV;

		/* specअगरying two पूर्णांकerfaces is mandatory */
		अगर (!tb[CGW_SRC_IF] || !tb[CGW_DST_IF])
			वापस err;

		ccgw->src_idx = nla_get_u32(tb[CGW_SRC_IF]);
		ccgw->dst_idx = nla_get_u32(tb[CGW_DST_IF]);

		/* both indices set to 0 क्रम flushing all routing entries */
		अगर (!ccgw->src_idx && !ccgw->dst_idx)
			वापस 0;

		/* only one index set to 0 is an error */
		अगर (!ccgw->src_idx || !ccgw->dst_idx)
			वापस err;
	पूर्ण

	/* add the checks क्रम other gwtypes here */

	वापस 0;
पूर्ण

अटल पूर्णांक cgw_create_job(काष्ठा sk_buff *skb,  काष्ठा nlmsghdr *nlh,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा rtcanmsg *r;
	काष्ठा cgw_job *gwj;
	काष्ठा cf_mod mod;
	काष्ठा can_can_gw ccgw;
	u8 limhops = 0;
	पूर्णांक err = 0;

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (nlmsg_len(nlh) < माप(*r))
		वापस -EINVAL;

	r = nlmsg_data(nlh);
	अगर (r->can_family != AF_CAN)
		वापस -EPFNOSUPPORT;

	/* so far we only support CAN -> CAN routings */
	अगर (r->gwtype != CGW_TYPE_CAN_CAN)
		वापस -EINVAL;

	err = cgw_parse_attr(nlh, &mod, CGW_TYPE_CAN_CAN, &ccgw, &limhops);
	अगर (err < 0)
		वापस err;

	अगर (mod.uid) अणु
		ASSERT_RTNL();

		/* check क्रम updating an existing job with identical uid */
		hlist_क्रम_each_entry(gwj, &net->can.cgw_list, list) अणु
			अगर (gwj->mod.uid != mod.uid)
				जारी;

			/* पूर्णांकerfaces & filters must be identical */
			अगर (स_भेद(&gwj->ccgw, &ccgw, माप(ccgw)))
				वापस -EINVAL;

			/* update modअगरications with disabled softirq & quit */
			local_bh_disable();
			स_नकल(&gwj->mod, &mod, माप(mod));
			local_bh_enable();
			वापस 0;
		पूर्ण
	पूर्ण

	/* अगरindex == 0 is not allowed क्रम job creation */
	अगर (!ccgw.src_idx || !ccgw.dst_idx)
		वापस -ENODEV;

	gwj = kmem_cache_alloc(cgw_cache, GFP_KERNEL);
	अगर (!gwj)
		वापस -ENOMEM;

	gwj->handled_frames = 0;
	gwj->dropped_frames = 0;
	gwj->deleted_frames = 0;
	gwj->flags = r->flags;
	gwj->gwtype = r->gwtype;
	gwj->limit_hops = limhops;

	/* insert alपढ़ोy parsed inक्रमmation */
	स_नकल(&gwj->mod, &mod, माप(mod));
	स_नकल(&gwj->ccgw, &ccgw, माप(ccgw));

	err = -ENODEV;

	gwj->src.dev = __dev_get_by_index(net, gwj->ccgw.src_idx);

	अगर (!gwj->src.dev)
		जाओ out;

	अगर (gwj->src.dev->type != ARPHRD_CAN)
		जाओ out;

	gwj->dst.dev = __dev_get_by_index(net, gwj->ccgw.dst_idx);

	अगर (!gwj->dst.dev)
		जाओ out;

	अगर (gwj->dst.dev->type != ARPHRD_CAN)
		जाओ out;

	ASSERT_RTNL();

	err = cgw_रेजिस्टर_filter(net, gwj);
	अगर (!err)
		hlist_add_head_rcu(&gwj->list, &net->can.cgw_list);
out:
	अगर (err)
		kmem_cache_मुक्त(cgw_cache, gwj);

	वापस err;
पूर्ण

अटल व्योम cgw_हटाओ_all_jobs(काष्ठा net *net)
अणु
	काष्ठा cgw_job *gwj = शून्य;
	काष्ठा hlist_node *nx;

	ASSERT_RTNL();

	hlist_क्रम_each_entry_safe(gwj, nx, &net->can.cgw_list, list) अणु
		hlist_del(&gwj->list);
		cgw_unरेजिस्टर_filter(net, gwj);
		kmem_cache_मुक्त(cgw_cache, gwj);
	पूर्ण
पूर्ण

अटल पूर्णांक cgw_हटाओ_job(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा cgw_job *gwj = शून्य;
	काष्ठा hlist_node *nx;
	काष्ठा rtcanmsg *r;
	काष्ठा cf_mod mod;
	काष्ठा can_can_gw ccgw;
	u8 limhops = 0;
	पूर्णांक err = 0;

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (nlmsg_len(nlh) < माप(*r))
		वापस -EINVAL;

	r = nlmsg_data(nlh);
	अगर (r->can_family != AF_CAN)
		वापस -EPFNOSUPPORT;

	/* so far we only support CAN -> CAN routings */
	अगर (r->gwtype != CGW_TYPE_CAN_CAN)
		वापस -EINVAL;

	err = cgw_parse_attr(nlh, &mod, CGW_TYPE_CAN_CAN, &ccgw, &limhops);
	अगर (err < 0)
		वापस err;

	/* two पूर्णांकerface indices both set to 0 => हटाओ all entries */
	अगर (!ccgw.src_idx && !ccgw.dst_idx) अणु
		cgw_हटाओ_all_jobs(net);
		वापस 0;
	पूर्ण

	err = -EINVAL;

	ASSERT_RTNL();

	/* हटाओ only the first matching entry */
	hlist_क्रम_each_entry_safe(gwj, nx, &net->can.cgw_list, list) अणु
		अगर (gwj->flags != r->flags)
			जारी;

		अगर (gwj->limit_hops != limhops)
			जारी;

		/* we have a match when uid is enabled and identical */
		अगर (gwj->mod.uid || mod.uid) अणु
			अगर (gwj->mod.uid != mod.uid)
				जारी;
		पूर्ण अन्यथा अणु
			/* no uid => check क्रम identical modअगरications */
			अगर (स_भेद(&gwj->mod, &mod, माप(mod)))
				जारी;
		पूर्ण

		/* अगर (r->gwtype == CGW_TYPE_CAN_CAN) - is made sure here */
		अगर (स_भेद(&gwj->ccgw, &ccgw, माप(ccgw)))
			जारी;

		hlist_del(&gwj->list);
		cgw_unरेजिस्टर_filter(net, gwj);
		kmem_cache_मुक्त(cgw_cache, gwj);
		err = 0;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __net_init cangw_pernet_init(काष्ठा net *net)
अणु
	INIT_HLIST_HEAD(&net->can.cgw_list);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास cangw_pernet_निकास(काष्ठा net *net)
अणु
	rtnl_lock();
	cgw_हटाओ_all_jobs(net);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations cangw_pernet_ops = अणु
	.init = cangw_pernet_init,
	.निकास = cangw_pernet_निकास,
पूर्ण;

अटल __init पूर्णांक cgw_module_init(व्योम)
अणु
	पूर्णांक ret;

	/* sanitize given module parameter */
	max_hops = clamp_t(अचिन्हित पूर्णांक, max_hops, CGW_MIN_HOPS, CGW_MAX_HOPS);

	pr_info("can: netlink gateway - max_hops=%d\n",	max_hops);

	ret = रेजिस्टर_pernet_subsys(&cangw_pernet_ops);
	अगर (ret)
		वापस ret;

	ret = -ENOMEM;
	cgw_cache = kmem_cache_create("can_gw", माप(काष्ठा cgw_job),
				      0, 0, शून्य);
	अगर (!cgw_cache)
		जाओ out_cache_create;

	/* set notअगरier */
	notअगरier.notअगरier_call = cgw_notअगरier;
	ret = रेजिस्टर_netdevice_notअगरier(&notअगरier);
	अगर (ret)
		जाओ out_रेजिस्टर_notअगरier;

	ret = rtnl_रेजिस्टर_module(THIS_MODULE, PF_CAN, RTM_GETROUTE,
				   शून्य, cgw_dump_jobs, 0);
	अगर (ret)
		जाओ out_rtnl_रेजिस्टर1;

	ret = rtnl_रेजिस्टर_module(THIS_MODULE, PF_CAN, RTM_NEWROUTE,
				   cgw_create_job, शून्य, 0);
	अगर (ret)
		जाओ out_rtnl_रेजिस्टर2;
	ret = rtnl_रेजिस्टर_module(THIS_MODULE, PF_CAN, RTM_DELROUTE,
				   cgw_हटाओ_job, शून्य, 0);
	अगर (ret)
		जाओ out_rtnl_रेजिस्टर3;

	वापस 0;

out_rtnl_रेजिस्टर3:
	rtnl_unरेजिस्टर(PF_CAN, RTM_NEWROUTE);
out_rtnl_रेजिस्टर2:
	rtnl_unरेजिस्टर(PF_CAN, RTM_GETROUTE);
out_rtnl_रेजिस्टर1:
	unरेजिस्टर_netdevice_notअगरier(&notअगरier);
out_रेजिस्टर_notअगरier:
	kmem_cache_destroy(cgw_cache);
out_cache_create:
	unरेजिस्टर_pernet_subsys(&cangw_pernet_ops);

	वापस ret;
पूर्ण

अटल __निकास व्योम cgw_module_निकास(व्योम)
अणु
	rtnl_unरेजिस्टर_all(PF_CAN);

	unरेजिस्टर_netdevice_notअगरier(&notअगरier);

	unरेजिस्टर_pernet_subsys(&cangw_pernet_ops);
	rcu_barrier(); /* Wait क्रम completion of call_rcu()'s */

	kmem_cache_destroy(cgw_cache);
पूर्ण

module_init(cgw_module_init);
module_निकास(cgw_module_निकास);
