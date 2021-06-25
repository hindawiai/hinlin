<शैली गुरु>
/*
 * Copyright 2011 Cisco Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/ip.h>

#समावेश "vnic_vic.h"
#समावेश "enic_res.h"
#समावेश "enic.h"
#समावेश "enic_dev.h"
#समावेश "enic_pp.h"

/*
 * Checks validity of vf index that came in
 * port profile request
 */
पूर्णांक enic_is_valid_pp_vf(काष्ठा enic *enic, पूर्णांक vf, पूर्णांक *err)
अणु
	अगर (vf != PORT_SELF_VF) अणु
#अगर_घोषित CONFIG_PCI_IOV
		अगर (enic_sriov_enabled(enic)) अणु
			अगर (vf < 0 || vf >= enic->num_vfs) अणु
				*err = -EINVAL;
				जाओ err_out;
			पूर्ण
		पूर्ण अन्यथा अणु
			*err = -EOPNOTSUPP;
			जाओ err_out;
		पूर्ण
#अन्यथा
		*err = -EOPNOTSUPP;
		जाओ err_out;
#पूर्ण_अगर
	पूर्ण

	अगर (vf == PORT_SELF_VF && !enic_is_dynamic(enic)) अणु
		*err = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण

	*err = 0;
	वापस 1;

err_out:
	वापस 0;
पूर्ण

अटल पूर्णांक enic_set_port_profile(काष्ठा enic *enic, पूर्णांक vf)
अणु
	काष्ठा net_device *netdev = enic->netdev;
	काष्ठा enic_port_profile *pp;
	काष्ठा vic_provinfo *vp;
	स्थिर u8 oui[3] = VIC_PROVINFO_CISCO_OUI;
	स्थिर __be16 os_type = htons(VIC_GENERIC_PROV_OS_TYPE_LINUX);
	अक्षर uuid_str[38];
	अक्षर client_mac_str[18];
	u8 *client_mac;
	पूर्णांक err;

	ENIC_PP_BY_INDEX(enic, vf, pp, &err);
	अगर (err)
		वापस err;

	अगर (!(pp->set & ENIC_SET_NAME) || !म_माप(pp->name))
		वापस -EINVAL;

	vp = vic_provinfo_alloc(GFP_KERNEL, oui,
		VIC_PROVINFO_GENERIC_TYPE);
	अगर (!vp)
		वापस -ENOMEM;

	VIC_PROVINFO_ADD_TLV(vp,
		VIC_GENERIC_PROV_TLV_PORT_PROखाता_NAME_STR,
		म_माप(pp->name) + 1, pp->name);

	अगर (!is_zero_ether_addr(pp->mac_addr)) अणु
		client_mac = pp->mac_addr;
	पूर्ण अन्यथा अगर (vf == PORT_SELF_VF) अणु
		client_mac = netdev->dev_addr;
	पूर्ण अन्यथा अणु
		netdev_err(netdev, "Cannot find pp mac address "
			"for VF %d\n", vf);
		err = -EINVAL;
		जाओ add_tlv_failure;
	पूर्ण

	VIC_PROVINFO_ADD_TLV(vp,
		VIC_GENERIC_PROV_TLV_CLIENT_MAC_ADDR,
		ETH_ALEN, client_mac);

	snम_लिखो(client_mac_str, माप(client_mac_str), "%pM", client_mac);
	VIC_PROVINFO_ADD_TLV(vp,
		VIC_GENERIC_PROV_TLV_CLUSTER_PORT_UUID_STR,
		माप(client_mac_str), client_mac_str);

	अगर (pp->set & ENIC_SET_INSTANCE) अणु
		प्र_लिखो(uuid_str, "%pUB", pp->instance_uuid);
		VIC_PROVINFO_ADD_TLV(vp,
			VIC_GENERIC_PROV_TLV_CLIENT_UUID_STR,
			माप(uuid_str), uuid_str);
	पूर्ण

	अगर (pp->set & ENIC_SET_HOST) अणु
		प्र_लिखो(uuid_str, "%pUB", pp->host_uuid);
		VIC_PROVINFO_ADD_TLV(vp,
			VIC_GENERIC_PROV_TLV_HOST_UUID_STR,
			माप(uuid_str), uuid_str);
	पूर्ण

	VIC_PROVINFO_ADD_TLV(vp,
		VIC_GENERIC_PROV_TLV_OS_TYPE,
		माप(os_type), &os_type);

	ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnic_dev_init_prov2, (u8 *)vp,
		vic_provinfo_size(vp));
	err = enic_dev_status_to_त्रुटि_सं(err);

add_tlv_failure:
	vic_provinfo_मुक्त(vp);

	वापस err;
पूर्ण

अटल पूर्णांक enic_unset_port_profile(काष्ठा enic *enic, पूर्णांक vf)
अणु
	पूर्णांक err;

	ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnic_dev_deinit);
	अगर (err)
		वापस enic_dev_status_to_त्रुटि_सं(err);

	अगर (vf == PORT_SELF_VF)
		enic_reset_addr_lists(enic);

	वापस 0;
पूर्ण

अटल पूर्णांक enic_are_pp_dअगरferent(काष्ठा enic_port_profile *pp1,
		काष्ठा enic_port_profile *pp2)
अणु
	वापस म_भेद(pp1->name, pp2->name) | !!स_भेद(pp1->instance_uuid,
		pp2->instance_uuid, PORT_UUID_MAX) |
		!!स_भेद(pp1->host_uuid, pp2->host_uuid, PORT_UUID_MAX) |
		!ether_addr_equal(pp1->mac_addr, pp2->mac_addr);
पूर्ण

अटल पूर्णांक enic_pp_preassociate(काष्ठा enic *enic, पूर्णांक vf,
	काष्ठा enic_port_profile *prev_pp, पूर्णांक *restore_pp);
अटल पूर्णांक enic_pp_disassociate(काष्ठा enic *enic, पूर्णांक vf,
	काष्ठा enic_port_profile *prev_pp, पूर्णांक *restore_pp);
अटल पूर्णांक enic_pp_preassociate_rr(काष्ठा enic *enic, पूर्णांक vf,
	काष्ठा enic_port_profile *prev_pp, पूर्णांक *restore_pp);
अटल पूर्णांक enic_pp_associate(काष्ठा enic *enic, पूर्णांक vf,
	काष्ठा enic_port_profile *prev_pp, पूर्णांक *restore_pp);

अटल पूर्णांक (*enic_pp_handlers[])(काष्ठा enic *enic, पूर्णांक vf,
		काष्ठा enic_port_profile *prev_state,
		पूर्णांक *restore_pp) = अणु
	[PORT_REQUEST_PREASSOCIATE]	= enic_pp_preassociate,
	[PORT_REQUEST_PREASSOCIATE_RR]	= enic_pp_preassociate_rr,
	[PORT_REQUEST_ASSOCIATE]	= enic_pp_associate,
	[PORT_REQUEST_DISASSOCIATE]	= enic_pp_disassociate,
पूर्ण;

अटल स्थिर पूर्णांक enic_pp_handlers_count =
			ARRAY_SIZE(enic_pp_handlers);

अटल पूर्णांक enic_pp_preassociate(काष्ठा enic *enic, पूर्णांक vf,
	काष्ठा enic_port_profile *prev_pp, पूर्णांक *restore_pp)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक enic_pp_disassociate(काष्ठा enic *enic, पूर्णांक vf,
	काष्ठा enic_port_profile *prev_pp, पूर्णांक *restore_pp)
अणु
	काष्ठा net_device *netdev = enic->netdev;
	काष्ठा enic_port_profile *pp;
	पूर्णांक err;

	ENIC_PP_BY_INDEX(enic, vf, pp, &err);
	अगर (err)
		वापस err;

	/* Deरेजिस्टर mac addresses */
	अगर (!is_zero_ether_addr(pp->mac_addr))
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnic_dev_del_addr,
			pp->mac_addr);
	अन्यथा अगर (vf == PORT_SELF_VF && !is_zero_ether_addr(netdev->dev_addr))
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnic_dev_del_addr,
			netdev->dev_addr);

	वापस enic_unset_port_profile(enic, vf);
पूर्ण

अटल पूर्णांक enic_pp_preassociate_rr(काष्ठा enic *enic, पूर्णांक vf,
	काष्ठा enic_port_profile *prev_pp, पूर्णांक *restore_pp)
अणु
	काष्ठा enic_port_profile *pp;
	पूर्णांक err;
	पूर्णांक active = 0;

	ENIC_PP_BY_INDEX(enic, vf, pp, &err);
	अगर (err)
		वापस err;

	अगर (pp->request != PORT_REQUEST_ASSOCIATE) अणु
		/* If pre-associate is not part of an associate.
		We always disassociate first */
		err = enic_pp_handlers[PORT_REQUEST_DISASSOCIATE](enic, vf,
			prev_pp, restore_pp);
		अगर (err)
			वापस err;

		*restore_pp = 0;
	पूर्ण

	*restore_pp = 0;

	err = enic_set_port_profile(enic, vf);
	अगर (err)
		वापस err;

	/* If pre-associate is not part of an associate. */
	अगर (pp->request != PORT_REQUEST_ASSOCIATE) अणु
		/* Enable device as standby */
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnic_dev_enable2,
			active);
		err = enic_dev_status_to_त्रुटि_सं(err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक enic_pp_associate(काष्ठा enic *enic, पूर्णांक vf,
	काष्ठा enic_port_profile *prev_pp, पूर्णांक *restore_pp)
अणु
	काष्ठा net_device *netdev = enic->netdev;
	काष्ठा enic_port_profile *pp;
	पूर्णांक err;
	पूर्णांक active = 1;

	ENIC_PP_BY_INDEX(enic, vf, pp, &err);
	अगर (err)
		वापस err;

	/* Check अगर a pre-associate was called beक्रमe */
	अगर (prev_pp->request != PORT_REQUEST_PREASSOCIATE_RR ||
		(prev_pp->request == PORT_REQUEST_PREASSOCIATE_RR &&
			enic_are_pp_dअगरferent(prev_pp, pp))) अणु
		err = enic_pp_handlers[PORT_REQUEST_DISASSOCIATE](
			enic, vf, prev_pp, restore_pp);
		अगर (err)
			वापस err;

		*restore_pp = 0;
	पूर्ण

	err = enic_pp_handlers[PORT_REQUEST_PREASSOCIATE_RR](
			enic, vf, prev_pp, restore_pp);
	अगर (err)
		वापस err;

	*restore_pp = 0;

	/* Enable device as active */
	ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnic_dev_enable2, active);
	err = enic_dev_status_to_त्रुटि_सं(err);
	अगर (err)
		वापस err;

	/* Register mac address */
	अगर (!is_zero_ether_addr(pp->mac_addr))
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnic_dev_add_addr,
			pp->mac_addr);
	अन्यथा अगर (vf == PORT_SELF_VF && !is_zero_ether_addr(netdev->dev_addr))
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnic_dev_add_addr,
			netdev->dev_addr);

	वापस 0;
पूर्ण

पूर्णांक enic_process_set_pp_request(काष्ठा enic *enic, पूर्णांक vf,
	काष्ठा enic_port_profile *prev_pp, पूर्णांक *restore_pp)
अणु
	काष्ठा enic_port_profile *pp;
	पूर्णांक err;

	ENIC_PP_BY_INDEX(enic, vf, pp, &err);
	अगर (err)
		वापस err;

	अगर (pp->request >= enic_pp_handlers_count
		|| !enic_pp_handlers[pp->request])
		वापस -EOPNOTSUPP;

	वापस enic_pp_handlers[pp->request](enic, vf, prev_pp, restore_pp);
पूर्ण

पूर्णांक enic_process_get_pp_request(काष्ठा enic *enic, पूर्णांक vf,
	पूर्णांक request, u16 *response)
अणु
	पूर्णांक err, status = ERR_SUCCESS;

	चयन (request) अणु

	हाल PORT_REQUEST_PREASSOCIATE_RR:
	हाल PORT_REQUEST_ASSOCIATE:
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic,
			vnic_dev_enable2_करोne, &status);
		अवरोध;

	हाल PORT_REQUEST_DISASSOCIATE:
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic,
			vnic_dev_deinit_करोne, &status);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (err)
		status = err;

	चयन (status) अणु
	हाल ERR_SUCCESS:
		*response = PORT_PROखाता_RESPONSE_SUCCESS;
		अवरोध;
	हाल ERR_EINVAL:
		*response = PORT_PROखाता_RESPONSE_INVALID;
		अवरोध;
	हाल ERR_EBADSTATE:
		*response = PORT_PROखाता_RESPONSE_BADSTATE;
		अवरोध;
	हाल ERR_ENOMEM:
		*response = PORT_PROखाता_RESPONSE_INSUFFICIENT_RESOURCES;
		अवरोध;
	हाल ERR_EINPROGRESS:
		*response = PORT_PROखाता_RESPONSE_INPROGRESS;
		अवरोध;
	शेष:
		*response = PORT_PROखाता_RESPONSE_ERROR;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
