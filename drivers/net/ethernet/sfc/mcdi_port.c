<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2009-2013 Solarflare Communications Inc.
 */

/*
 * Driver क्रम PHY related operations via MCDI.
 */

#समावेश <linux/slab.h>
#समावेश "efx.h"
#समावेश "mcdi_port.h"
#समावेश "mcdi.h"
#समावेश "mcdi_pcol.h"
#समावेश "nic.h"
#समावेश "selftest.h"
#समावेश "mcdi_port_common.h"

अटल पूर्णांक efx_mcdi_mdio_पढ़ो(काष्ठा net_device *net_dev,
			      पूर्णांक prtad, पूर्णांक devad, u16 addr)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	MCDI_DECLARE_BUF(inbuf, MC_CMD_MDIO_READ_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_MDIO_READ_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, MDIO_READ_IN_BUS, efx->mdio_bus);
	MCDI_SET_DWORD(inbuf, MDIO_READ_IN_PRTAD, prtad);
	MCDI_SET_DWORD(inbuf, MDIO_READ_IN_DEVAD, devad);
	MCDI_SET_DWORD(inbuf, MDIO_READ_IN_ADDR, addr);

	rc = efx_mcdi_rpc(efx, MC_CMD_MDIO_READ, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;

	अगर (MCDI_DWORD(outbuf, MDIO_READ_OUT_STATUS) !=
	    MC_CMD_MDIO_STATUS_GOOD)
		वापस -EIO;

	वापस (u16)MCDI_DWORD(outbuf, MDIO_READ_OUT_VALUE);
पूर्ण

अटल पूर्णांक efx_mcdi_mdio_ग_लिखो(काष्ठा net_device *net_dev,
			       पूर्णांक prtad, पूर्णांक devad, u16 addr, u16 value)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	MCDI_DECLARE_BUF(inbuf, MC_CMD_MDIO_WRITE_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_MDIO_WRITE_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, MDIO_WRITE_IN_BUS, efx->mdio_bus);
	MCDI_SET_DWORD(inbuf, MDIO_WRITE_IN_PRTAD, prtad);
	MCDI_SET_DWORD(inbuf, MDIO_WRITE_IN_DEVAD, devad);
	MCDI_SET_DWORD(inbuf, MDIO_WRITE_IN_ADDR, addr);
	MCDI_SET_DWORD(inbuf, MDIO_WRITE_IN_VALUE, value);

	rc = efx_mcdi_rpc(efx, MC_CMD_MDIO_WRITE, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;

	अगर (MCDI_DWORD(outbuf, MDIO_WRITE_OUT_STATUS) !=
	    MC_CMD_MDIO_STATUS_GOOD)
		वापस -EIO;

	वापस 0;
पूर्ण

u32 efx_mcdi_phy_get_caps(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_phy_data *phy_data = efx->phy_data;

	वापस phy_data->supported_cap;
पूर्ण

bool efx_mcdi_mac_check_fault(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_LINK_OUT_LEN);
	माप_प्रकार outlength;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_GET_LINK_IN_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_LINK, शून्य, 0,
			  outbuf, माप(outbuf), &outlength);
	अगर (rc)
		वापस true;

	वापस MCDI_DWORD(outbuf, GET_LINK_OUT_MAC_FAULT) != 0;
पूर्ण

पूर्णांक efx_mcdi_port_probe(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	/* Set up MDIO काष्ठाure क्रम PHY */
	efx->mdio.mode_support = MDIO_SUPPORTS_C45 | MDIO_EMULATE_C22;
	efx->mdio.mdio_पढ़ो = efx_mcdi_mdio_पढ़ो;
	efx->mdio.mdio_ग_लिखो = efx_mcdi_mdio_ग_लिखो;

	/* Fill out MDIO काष्ठाure, loopback modes, and initial link state */
	rc = efx_mcdi_phy_probe(efx);
	अगर (rc != 0)
		वापस rc;

	वापस efx_mcdi_mac_init_stats(efx);
पूर्ण

व्योम efx_mcdi_port_हटाओ(काष्ठा efx_nic *efx)
अणु
	efx_mcdi_phy_हटाओ(efx);
	efx_mcdi_mac_fini_stats(efx);
पूर्ण
