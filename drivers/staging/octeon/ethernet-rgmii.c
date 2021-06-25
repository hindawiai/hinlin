<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2007 Cavium Networks
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/phy.h>
#समावेश <linux/ratelimit.h>
#समावेश <net/dst.h>

#समावेश "octeon-ethernet.h"
#समावेश "ethernet-defines.h"
#समावेश "ethernet-util.h"
#समावेश "ethernet-mdio.h"

अटल DEFINE_SPINLOCK(global_रेजिस्टर_lock);

अटल व्योम cvm_oct_set_hw_preamble(काष्ठा octeon_ethernet *priv, bool enable)
अणु
	जोड़ cvmx_gmxx_rxx_frm_ctl gmxx_rxx_frm_ctl;
	जोड़ cvmx_ipd_sub_port_fcs ipd_sub_port_fcs;
	जोड़ cvmx_gmxx_rxx_पूर्णांक_reg gmxx_rxx_पूर्णांक_reg;
	पूर्णांक पूर्णांकerface = INTERFACE(priv->port);
	पूर्णांक index = INDEX(priv->port);

	/* Set preamble checking. */
	gmxx_rxx_frm_ctl.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_RXX_FRM_CTL(index,
								   पूर्णांकerface));
	gmxx_rxx_frm_ctl.s.pre_chk = enable;
	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_FRM_CTL(index, पूर्णांकerface),
		       gmxx_rxx_frm_ctl.u64);

	/* Set FCS stripping. */
	ipd_sub_port_fcs.u64 = cvmx_पढ़ो_csr(CVMX_IPD_SUB_PORT_FCS);
	अगर (enable)
		ipd_sub_port_fcs.s.port_bit |= 1ull << priv->port;
	अन्यथा
		ipd_sub_port_fcs.s.port_bit &=
					0xffffffffull ^ (1ull << priv->port);
	cvmx_ग_लिखो_csr(CVMX_IPD_SUB_PORT_FCS, ipd_sub_port_fcs.u64);

	/* Clear any error bits. */
	gmxx_rxx_पूर्णांक_reg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_RXX_INT_REG(index,
								   पूर्णांकerface));
	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_INT_REG(index, पूर्णांकerface),
		       gmxx_rxx_पूर्णांक_reg.u64);
पूर्ण

अटल व्योम cvm_oct_check_preamble_errors(काष्ठा net_device *dev)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	जोड़ cvmx_helper_link_info link_info;
	अचिन्हित दीर्घ flags;

	link_info.u64 = priv->link_info;

	/*
	 * Take the global रेजिस्टर lock since we are going to
	 * touch रेजिस्टरs that affect more than one port.
	 */
	spin_lock_irqsave(&global_रेजिस्टर_lock, flags);

	अगर (link_info.s.speed == 10 && priv->last_speed == 10) अणु
		/*
		 * Read the GMXX_RXX_INT_REG[PCTERR] bit and see अगर we are
		 * getting preamble errors.
		 */
		पूर्णांक पूर्णांकerface = INTERFACE(priv->port);
		पूर्णांक index = INDEX(priv->port);
		जोड़ cvmx_gmxx_rxx_पूर्णांक_reg gmxx_rxx_पूर्णांक_reg;

		gmxx_rxx_पूर्णांक_reg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_RXX_INT_REG
							(index, पूर्णांकerface));
		अगर (gmxx_rxx_पूर्णांक_reg.s.pcterr) अणु
			/*
			 * We are getting preamble errors at 10Mbps. Most
			 * likely the PHY is giving us packets with misaligned
			 * preambles. In order to get these packets we need to
			 * disable preamble checking and करो it in software.
			 */
			cvm_oct_set_hw_preamble(priv, false);
			prपूर्णांकk_ratelimited("%s: Using 10Mbps with software preamble removal\n",
					   dev->name);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Since the 10Mbps preamble workaround is allowed we need to
		 * enable preamble checking, FCS stripping, and clear error
		 * bits on every speed change. If errors occur during 10Mbps
		 * operation the above code will change this stuff
		 */
		अगर (priv->last_speed != link_info.s.speed)
			cvm_oct_set_hw_preamble(priv, true);
		priv->last_speed = link_info.s.speed;
	पूर्ण
	spin_unlock_irqrestore(&global_रेजिस्टर_lock, flags);
पूर्ण

अटल व्योम cvm_oct_rgmii_poll(काष्ठा net_device *dev)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	जोड़ cvmx_helper_link_info link_info;
	bool status_change;

	link_info = cvmx_helper_link_get(priv->port);
	अगर (priv->link_info != link_info.u64 &&
	    cvmx_helper_link_set(priv->port, link_info))
		link_info.u64 = priv->link_info;
	status_change = priv->link_info != link_info.u64;
	priv->link_info = link_info.u64;

	cvm_oct_check_preamble_errors(dev);

	अगर (likely(!status_change))
		वापस;

	/* Tell core. */
	अगर (link_info.s.link_up) अणु
		अगर (!netअगर_carrier_ok(dev))
			netअगर_carrier_on(dev);
	पूर्ण अन्यथा अगर (netअगर_carrier_ok(dev)) अणु
		netअगर_carrier_off(dev);
	पूर्ण
	cvm_oct_note_carrier(priv, link_info);
पूर्ण

पूर्णांक cvm_oct_rgmii_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	पूर्णांक ret;

	ret = cvm_oct_common_खोलो(dev, cvm_oct_rgmii_poll);
	अगर (ret)
		वापस ret;

	अगर (dev->phydev) अणु
		/*
		 * In phydev mode, we need still periodic polling क्रम the
		 * preamble error checking, and we also need to call this
		 * function on every link state change.
		 *
		 * Only true RGMII ports need to be polled. In GMII mode, port
		 * 0 is really a RGMII port.
		 */
		अगर ((priv->imode == CVMX_HELPER_INTERFACE_MODE_GMII &&
		     priv->port  == 0) ||
		    (priv->imode == CVMX_HELPER_INTERFACE_MODE_RGMII)) अणु
			priv->poll = cvm_oct_check_preamble_errors;
			cvm_oct_check_preamble_errors(dev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
