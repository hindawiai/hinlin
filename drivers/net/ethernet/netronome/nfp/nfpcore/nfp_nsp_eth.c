<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2017 Netronome Systems, Inc. */

/* Authors: David Brunecz <david.brunecz@netronome.com>
 *          Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Jason Mcmullan <jason.mcmullan@netronome.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "nfp.h"
#समावेश "nfp_nsp.h"
#समावेश "nfp6000/nfp6000.h"

#घोषणा NSP_ETH_NBI_PORT_COUNT		24
#घोषणा NSP_ETH_MAX_COUNT		(2 * NSP_ETH_NBI_PORT_COUNT)
#घोषणा NSP_ETH_TABLE_SIZE		(NSP_ETH_MAX_COUNT *		\
					 माप(जोड़ eth_table_entry))

#घोषणा NSP_ETH_PORT_LANES		GENMASK_ULL(3, 0)
#घोषणा NSP_ETH_PORT_INDEX		GENMASK_ULL(15, 8)
#घोषणा NSP_ETH_PORT_LABEL		GENMASK_ULL(53, 48)
#घोषणा NSP_ETH_PORT_PHYLABEL		GENMASK_ULL(59, 54)
#घोषणा NSP_ETH_PORT_FEC_SUPP_BASER	BIT_ULL(60)
#घोषणा NSP_ETH_PORT_FEC_SUPP_RS	BIT_ULL(61)

#घोषणा NSP_ETH_PORT_LANES_MASK		cpu_to_le64(NSP_ETH_PORT_LANES)

#घोषणा NSP_ETH_STATE_CONFIGURED	BIT_ULL(0)
#घोषणा NSP_ETH_STATE_ENABLED		BIT_ULL(1)
#घोषणा NSP_ETH_STATE_TX_ENABLED	BIT_ULL(2)
#घोषणा NSP_ETH_STATE_RX_ENABLED	BIT_ULL(3)
#घोषणा NSP_ETH_STATE_RATE		GENMASK_ULL(11, 8)
#घोषणा NSP_ETH_STATE_INTERFACE		GENMASK_ULL(19, 12)
#घोषणा NSP_ETH_STATE_MEDIA		GENMASK_ULL(21, 20)
#घोषणा NSP_ETH_STATE_OVRD_CHNG		BIT_ULL(22)
#घोषणा NSP_ETH_STATE_ANEG		GENMASK_ULL(25, 23)
#घोषणा NSP_ETH_STATE_FEC		GENMASK_ULL(27, 26)

#घोषणा NSP_ETH_CTRL_CONFIGURED		BIT_ULL(0)
#घोषणा NSP_ETH_CTRL_ENABLED		BIT_ULL(1)
#घोषणा NSP_ETH_CTRL_TX_ENABLED		BIT_ULL(2)
#घोषणा NSP_ETH_CTRL_RX_ENABLED		BIT_ULL(3)
#घोषणा NSP_ETH_CTRL_SET_RATE		BIT_ULL(4)
#घोषणा NSP_ETH_CTRL_SET_LANES		BIT_ULL(5)
#घोषणा NSP_ETH_CTRL_SET_ANEG		BIT_ULL(6)
#घोषणा NSP_ETH_CTRL_SET_FEC		BIT_ULL(7)

क्रमागत nfp_eth_raw अणु
	NSP_ETH_RAW_PORT = 0,
	NSP_ETH_RAW_STATE,
	NSP_ETH_RAW_MAC,
	NSP_ETH_RAW_CONTROL,

	NSP_ETH_NUM_RAW
पूर्ण;

क्रमागत nfp_eth_rate अणु
	RATE_INVALID = 0,
	RATE_10M,
	RATE_100M,
	RATE_1G,
	RATE_10G,
	RATE_25G,
पूर्ण;

जोड़ eth_table_entry अणु
	काष्ठा अणु
		__le64 port;
		__le64 state;
		u8 mac_addr[6];
		u8 resv[2];
		__le64 control;
	पूर्ण;
	__le64 raw[NSP_ETH_NUM_RAW];
पूर्ण;

अटल स्थिर काष्ठा अणु
	क्रमागत nfp_eth_rate rate;
	अचिन्हित पूर्णांक speed;
पूर्ण nsp_eth_rate_tbl[] = अणु
	अणु RATE_INVALID,	0, पूर्ण,
	अणु RATE_10M,	SPEED_10, पूर्ण,
	अणु RATE_100M,	SPEED_100, पूर्ण,
	अणु RATE_1G,	SPEED_1000, पूर्ण,
	अणु RATE_10G,	SPEED_10000, पूर्ण,
	अणु RATE_25G,	SPEED_25000, पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक nfp_eth_rate2speed(क्रमागत nfp_eth_rate rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nsp_eth_rate_tbl); i++)
		अगर (nsp_eth_rate_tbl[i].rate == rate)
			वापस nsp_eth_rate_tbl[i].speed;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक nfp_eth_speed2rate(अचिन्हित पूर्णांक speed)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nsp_eth_rate_tbl); i++)
		अगर (nsp_eth_rate_tbl[i].speed == speed)
			वापस nsp_eth_rate_tbl[i].rate;

	वापस RATE_INVALID;
पूर्ण

अटल व्योम nfp_eth_copy_mac_reverse(u8 *dst, स्थिर u8 *src)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		dst[ETH_ALEN - i - 1] = src[i];
पूर्ण

अटल व्योम
nfp_eth_port_translate(काष्ठा nfp_nsp *nsp, स्थिर जोड़ eth_table_entry *src,
		       अचिन्हित पूर्णांक index, काष्ठा nfp_eth_table_port *dst)
अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक fec;
	u64 port, state;

	port = le64_to_cpu(src->port);
	state = le64_to_cpu(src->state);

	dst->eth_index = FIELD_GET(NSP_ETH_PORT_INDEX, port);
	dst->index = index;
	dst->nbi = index / NSP_ETH_NBI_PORT_COUNT;
	dst->base = index % NSP_ETH_NBI_PORT_COUNT;
	dst->lanes = FIELD_GET(NSP_ETH_PORT_LANES, port);

	dst->enabled = FIELD_GET(NSP_ETH_STATE_ENABLED, state);
	dst->tx_enabled = FIELD_GET(NSP_ETH_STATE_TX_ENABLED, state);
	dst->rx_enabled = FIELD_GET(NSP_ETH_STATE_RX_ENABLED, state);

	rate = nfp_eth_rate2speed(FIELD_GET(NSP_ETH_STATE_RATE, state));
	dst->speed = dst->lanes * rate;

	dst->पूर्णांकerface = FIELD_GET(NSP_ETH_STATE_INTERFACE, state);
	dst->media = FIELD_GET(NSP_ETH_STATE_MEDIA, state);

	nfp_eth_copy_mac_reverse(dst->mac_addr, src->mac_addr);

	dst->label_port = FIELD_GET(NSP_ETH_PORT_PHYLABEL, port);
	dst->label_subport = FIELD_GET(NSP_ETH_PORT_LABEL, port);

	अगर (nfp_nsp_get_abi_ver_minor(nsp) < 17)
		वापस;

	dst->override_changed = FIELD_GET(NSP_ETH_STATE_OVRD_CHNG, state);
	dst->aneg = FIELD_GET(NSP_ETH_STATE_ANEG, state);

	अगर (nfp_nsp_get_abi_ver_minor(nsp) < 22)
		वापस;

	fec = FIELD_GET(NSP_ETH_PORT_FEC_SUPP_BASER, port);
	dst->fec_modes_supported |= fec << NFP_FEC_BASER_BIT;
	fec = FIELD_GET(NSP_ETH_PORT_FEC_SUPP_RS, port);
	dst->fec_modes_supported |= fec << NFP_FEC_REED_SOLOMON_BIT;
	अगर (dst->fec_modes_supported)
		dst->fec_modes_supported |= NFP_FEC_AUTO | NFP_FEC_DISABLED;

	dst->fec = 1 << FIELD_GET(NSP_ETH_STATE_FEC, state);
पूर्ण

अटल व्योम
nfp_eth_calc_port_geometry(काष्ठा nfp_cpp *cpp, काष्ठा nfp_eth_table *table)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < table->count; i++) अणु
		table->max_index = max(table->max_index, table->ports[i].index);

		क्रम (j = 0; j < table->count; j++) अणु
			अगर (table->ports[i].label_port !=
			    table->ports[j].label_port)
				जारी;
			table->ports[i].port_lanes += table->ports[j].lanes;

			अगर (i == j)
				जारी;
			अगर (table->ports[i].label_subport ==
			    table->ports[j].label_subport)
				nfp_warn(cpp,
					 "Port %d subport %d is a duplicate\n",
					 table->ports[i].label_port,
					 table->ports[i].label_subport);

			table->ports[i].is_split = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
nfp_eth_calc_port_type(काष्ठा nfp_cpp *cpp, काष्ठा nfp_eth_table_port *entry)
अणु
	अगर (entry->पूर्णांकerface == NFP_INTERFACE_NONE) अणु
		entry->port_type = PORT_NONE;
		वापस;
	पूर्ण अन्यथा अगर (entry->पूर्णांकerface == NFP_INTERFACE_RJ45) अणु
		entry->port_type = PORT_TP;
		वापस;
	पूर्ण

	अगर (entry->media == NFP_MEDIA_FIBRE)
		entry->port_type = PORT_FIBRE;
	अन्यथा
		entry->port_type = PORT_DA;
पूर्ण

/**
 * nfp_eth_पढ़ो_ports() - retrieve port inक्रमmation
 * @cpp:	NFP CPP handle
 *
 * Read the port inक्रमmation from the device.  Returned काष्ठाure should
 * be मुक्तd with kमुक्त() once no दीर्घer needed.
 *
 * Return: populated ETH table or शून्य on error.
 */
काष्ठा nfp_eth_table *nfp_eth_पढ़ो_ports(काष्ठा nfp_cpp *cpp)
अणु
	काष्ठा nfp_eth_table *ret;
	काष्ठा nfp_nsp *nsp;

	nsp = nfp_nsp_खोलो(cpp);
	अगर (IS_ERR(nsp))
		वापस शून्य;

	ret = __nfp_eth_पढ़ो_ports(cpp, nsp);
	nfp_nsp_बंद(nsp);

	वापस ret;
पूर्ण

काष्ठा nfp_eth_table *
__nfp_eth_पढ़ो_ports(काष्ठा nfp_cpp *cpp, काष्ठा nfp_nsp *nsp)
अणु
	जोड़ eth_table_entry *entries;
	काष्ठा nfp_eth_table *table;
	पूर्णांक i, j, ret, cnt = 0;

	entries = kzalloc(NSP_ETH_TABLE_SIZE, GFP_KERNEL);
	अगर (!entries)
		वापस शून्य;

	ret = nfp_nsp_पढ़ो_eth_table(nsp, entries, NSP_ETH_TABLE_SIZE);
	अगर (ret < 0) अणु
		nfp_err(cpp, "reading port table failed %d\n", ret);
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < NSP_ETH_MAX_COUNT; i++)
		अगर (entries[i].port & NSP_ETH_PORT_LANES_MASK)
			cnt++;

	/* Some versions of flash will give us 0 instead of port count.
	 * For those that give a port count, verअगरy it against the value
	 * calculated above.
	 */
	अगर (ret && ret != cnt) अणु
		nfp_err(cpp, "table entry count reported (%d) does not match entries present (%d)\n",
			ret, cnt);
		जाओ err;
	पूर्ण

	table = kzalloc(काष्ठा_size(table, ports, cnt), GFP_KERNEL);
	अगर (!table)
		जाओ err;

	table->count = cnt;
	क्रम (i = 0, j = 0; i < NSP_ETH_MAX_COUNT; i++)
		अगर (entries[i].port & NSP_ETH_PORT_LANES_MASK)
			nfp_eth_port_translate(nsp, &entries[i], i,
					       &table->ports[j++]);

	nfp_eth_calc_port_geometry(cpp, table);
	क्रम (i = 0; i < table->count; i++)
		nfp_eth_calc_port_type(cpp, &table->ports[i]);

	kमुक्त(entries);

	वापस table;

err:
	kमुक्त(entries);
	वापस शून्य;
पूर्ण

काष्ठा nfp_nsp *nfp_eth_config_start(काष्ठा nfp_cpp *cpp, अचिन्हित पूर्णांक idx)
अणु
	जोड़ eth_table_entry *entries;
	काष्ठा nfp_nsp *nsp;
	पूर्णांक ret;

	entries = kzalloc(NSP_ETH_TABLE_SIZE, GFP_KERNEL);
	अगर (!entries)
		वापस ERR_PTR(-ENOMEM);

	nsp = nfp_nsp_खोलो(cpp);
	अगर (IS_ERR(nsp)) अणु
		kमुक्त(entries);
		वापस nsp;
	पूर्ण

	ret = nfp_nsp_पढ़ो_eth_table(nsp, entries, NSP_ETH_TABLE_SIZE);
	अगर (ret < 0) अणु
		nfp_err(cpp, "reading port table failed %d\n", ret);
		जाओ err;
	पूर्ण

	अगर (!(entries[idx].port & NSP_ETH_PORT_LANES_MASK)) अणु
		nfp_warn(cpp, "trying to set port state on disabled port %d\n",
			 idx);
		जाओ err;
	पूर्ण

	nfp_nsp_config_set_state(nsp, entries, idx);
	वापस nsp;

err:
	nfp_nsp_बंद(nsp);
	kमुक्त(entries);
	वापस ERR_PTR(-EIO);
पूर्ण

व्योम nfp_eth_config_cleanup_end(काष्ठा nfp_nsp *nsp)
अणु
	जोड़ eth_table_entry *entries = nfp_nsp_config_entries(nsp);

	nfp_nsp_config_set_modअगरied(nsp, false);
	nfp_nsp_config_clear_state(nsp);
	nfp_nsp_बंद(nsp);
	kमुक्त(entries);
पूर्ण

/**
 * nfp_eth_config_commit_end() - perक्रमm recorded configuration changes
 * @nsp:	NFP NSP handle वापसed from nfp_eth_config_start()
 *
 * Perक्रमm the configuration which was requested with __nfp_eth_set_*()
 * helpers and recorded in @nsp state.  If device was alपढ़ोy configured
 * as requested or no __nfp_eth_set_*() operations were made no NSP command
 * will be perक्रमmed.
 *
 * Return:
 * 0 - configuration successful;
 * 1 - no changes were needed;
 * -ERRNO - configuration failed.
 */
पूर्णांक nfp_eth_config_commit_end(काष्ठा nfp_nsp *nsp)
अणु
	जोड़ eth_table_entry *entries = nfp_nsp_config_entries(nsp);
	पूर्णांक ret = 1;

	अगर (nfp_nsp_config_modअगरied(nsp)) अणु
		ret = nfp_nsp_ग_लिखो_eth_table(nsp, entries, NSP_ETH_TABLE_SIZE);
		ret = ret < 0 ? ret : 0;
	पूर्ण

	nfp_eth_config_cleanup_end(nsp);

	वापस ret;
पूर्ण

/**
 * nfp_eth_set_mod_enable() - set PHY module enable control bit
 * @cpp:	NFP CPP handle
 * @idx:	NFP chip-wide port index
 * @enable:	Desired state
 *
 * Enable or disable PHY module (this usually means setting the TX lanes
 * disable bits).
 *
 * Return:
 * 0 - configuration successful;
 * 1 - no changes were needed;
 * -ERRNO - configuration failed.
 */
पूर्णांक nfp_eth_set_mod_enable(काष्ठा nfp_cpp *cpp, अचिन्हित पूर्णांक idx, bool enable)
अणु
	जोड़ eth_table_entry *entries;
	काष्ठा nfp_nsp *nsp;
	u64 reg;

	nsp = nfp_eth_config_start(cpp, idx);
	अगर (IS_ERR(nsp))
		वापस PTR_ERR(nsp);

	entries = nfp_nsp_config_entries(nsp);

	/* Check अगर we are alपढ़ोy in requested state */
	reg = le64_to_cpu(entries[idx].state);
	अगर (enable != FIELD_GET(NSP_ETH_CTRL_ENABLED, reg)) अणु
		reg = le64_to_cpu(entries[idx].control);
		reg &= ~NSP_ETH_CTRL_ENABLED;
		reg |= FIELD_PREP(NSP_ETH_CTRL_ENABLED, enable);
		entries[idx].control = cpu_to_le64(reg);

		nfp_nsp_config_set_modअगरied(nsp, true);
	पूर्ण

	वापस nfp_eth_config_commit_end(nsp);
पूर्ण

/**
 * nfp_eth_set_configured() - set PHY module configured control bit
 * @cpp:	NFP CPP handle
 * @idx:	NFP chip-wide port index
 * @configed:	Desired state
 *
 * Set the अगरup/अगरकरोwn state on the PHY.
 *
 * Return:
 * 0 - configuration successful;
 * 1 - no changes were needed;
 * -ERRNO - configuration failed.
 */
पूर्णांक nfp_eth_set_configured(काष्ठा nfp_cpp *cpp, अचिन्हित पूर्णांक idx, bool configed)
अणु
	जोड़ eth_table_entry *entries;
	काष्ठा nfp_nsp *nsp;
	u64 reg;

	nsp = nfp_eth_config_start(cpp, idx);
	अगर (IS_ERR(nsp))
		वापस PTR_ERR(nsp);

	/* Older ABI versions did support this feature, however this has only
	 * been reliable since ABI 20.
	 */
	अगर (nfp_nsp_get_abi_ver_minor(nsp) < 20) अणु
		nfp_eth_config_cleanup_end(nsp);
		वापस -EOPNOTSUPP;
	पूर्ण

	entries = nfp_nsp_config_entries(nsp);

	/* Check अगर we are alपढ़ोy in requested state */
	reg = le64_to_cpu(entries[idx].state);
	अगर (configed != FIELD_GET(NSP_ETH_STATE_CONFIGURED, reg)) अणु
		reg = le64_to_cpu(entries[idx].control);
		reg &= ~NSP_ETH_CTRL_CONFIGURED;
		reg |= FIELD_PREP(NSP_ETH_CTRL_CONFIGURED, configed);
		entries[idx].control = cpu_to_le64(reg);

		nfp_nsp_config_set_modअगरied(nsp, true);
	पूर्ण

	वापस nfp_eth_config_commit_end(nsp);
पूर्ण

अटल पूर्णांक
nfp_eth_set_bit_config(काष्ठा nfp_nsp *nsp, अचिन्हित पूर्णांक raw_idx,
		       स्थिर u64 mask, स्थिर अचिन्हित पूर्णांक shअगरt,
		       अचिन्हित पूर्णांक val, स्थिर u64 ctrl_bit)
अणु
	जोड़ eth_table_entry *entries = nfp_nsp_config_entries(nsp);
	अचिन्हित पूर्णांक idx = nfp_nsp_config_idx(nsp);
	u64 reg;

	/* Note: set features were added in ABI 0.14 but the error
	 *	 codes were initially not populated correctly.
	 */
	अगर (nfp_nsp_get_abi_ver_minor(nsp) < 17) अणु
		nfp_err(nfp_nsp_cpp(nsp),
			"set operations not supported, please update flash\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Check अगर we are alपढ़ोy in requested state */
	reg = le64_to_cpu(entries[idx].raw[raw_idx]);
	अगर (val == (reg & mask) >> shअगरt)
		वापस 0;

	reg &= ~mask;
	reg |= (val << shअगरt) & mask;
	entries[idx].raw[raw_idx] = cpu_to_le64(reg);

	entries[idx].control |= cpu_to_le64(ctrl_bit);

	nfp_nsp_config_set_modअगरied(nsp, true);

	वापस 0;
पूर्ण

#घोषणा NFP_ETH_SET_BIT_CONFIG(nsp, raw_idx, mask, val, ctrl_bit)	\
	(अणु								\
		__BF_FIELD_CHECK(mask, 0ULL, val, "NFP_ETH_SET_BIT_CONFIG: "); \
		nfp_eth_set_bit_config(nsp, raw_idx, mask, __bf_shf(mask), \
				       val, ctrl_bit);			\
	पूर्ण)

/**
 * __nfp_eth_set_aneg() - set PHY स्वतःnegotiation control bit
 * @nsp:	NFP NSP handle वापसed from nfp_eth_config_start()
 * @mode:	Desired स्वतःnegotiation mode
 *
 * Allow/disallow PHY module to advertise/perक्रमm स्वतःnegotiation.
 * Will ग_लिखो to hwinfo overrides in the flash (persistent config).
 *
 * Return: 0 or -ERRNO.
 */
पूर्णांक __nfp_eth_set_aneg(काष्ठा nfp_nsp *nsp, क्रमागत nfp_eth_aneg mode)
अणु
	वापस NFP_ETH_SET_BIT_CONFIG(nsp, NSP_ETH_RAW_STATE,
				      NSP_ETH_STATE_ANEG, mode,
				      NSP_ETH_CTRL_SET_ANEG);
पूर्ण

/**
 * __nfp_eth_set_fec() - set PHY क्रमward error correction control bit
 * @nsp:	NFP NSP handle वापसed from nfp_eth_config_start()
 * @mode:	Desired fec mode
 *
 * Set the PHY module क्रमward error correction mode.
 * Will ग_लिखो to hwinfo overrides in the flash (persistent config).
 *
 * Return: 0 or -ERRNO.
 */
अटल पूर्णांक __nfp_eth_set_fec(काष्ठा nfp_nsp *nsp, क्रमागत nfp_eth_fec mode)
अणु
	वापस NFP_ETH_SET_BIT_CONFIG(nsp, NSP_ETH_RAW_STATE,
				      NSP_ETH_STATE_FEC, mode,
				      NSP_ETH_CTRL_SET_FEC);
पूर्ण

/**
 * nfp_eth_set_fec() - set PHY क्रमward error correction control mode
 * @cpp:	NFP CPP handle
 * @idx:	NFP chip-wide port index
 * @mode:	Desired fec mode
 *
 * Return:
 * 0 - configuration successful;
 * 1 - no changes were needed;
 * -ERRNO - configuration failed.
 */
पूर्णांक
nfp_eth_set_fec(काष्ठा nfp_cpp *cpp, अचिन्हित पूर्णांक idx, क्रमागत nfp_eth_fec mode)
अणु
	काष्ठा nfp_nsp *nsp;
	पूर्णांक err;

	nsp = nfp_eth_config_start(cpp, idx);
	अगर (IS_ERR(nsp))
		वापस PTR_ERR(nsp);

	err = __nfp_eth_set_fec(nsp, mode);
	अगर (err) अणु
		nfp_eth_config_cleanup_end(nsp);
		वापस err;
	पूर्ण

	वापस nfp_eth_config_commit_end(nsp);
पूर्ण

/**
 * __nfp_eth_set_speed() - set पूर्णांकerface speed/rate
 * @nsp:	NFP NSP handle वापसed from nfp_eth_config_start()
 * @speed:	Desired speed (per lane)
 *
 * Set lane speed.  Provided @speed value should be subport speed भागided
 * by number of lanes this subport is spanning (i.e. 10000 क्रम 40G, 25000 क्रम
 * 50G, etc.)
 * Will ग_लिखो to hwinfo overrides in the flash (persistent config).
 *
 * Return: 0 or -ERRNO.
 */
पूर्णांक __nfp_eth_set_speed(काष्ठा nfp_nsp *nsp, अचिन्हित पूर्णांक speed)
अणु
	क्रमागत nfp_eth_rate rate;

	rate = nfp_eth_speed2rate(speed);
	अगर (rate == RATE_INVALID) अणु
		nfp_warn(nfp_nsp_cpp(nsp),
			 "could not find matching lane rate for speed %u\n",
			 speed);
		वापस -EINVAL;
	पूर्ण

	वापस NFP_ETH_SET_BIT_CONFIG(nsp, NSP_ETH_RAW_STATE,
				      NSP_ETH_STATE_RATE, rate,
				      NSP_ETH_CTRL_SET_RATE);
पूर्ण

/**
 * __nfp_eth_set_split() - set पूर्णांकerface lane split
 * @nsp:	NFP NSP handle वापसed from nfp_eth_config_start()
 * @lanes:	Desired lanes per port
 *
 * Set number of lanes in the port.
 * Will ग_लिखो to hwinfo overrides in the flash (persistent config).
 *
 * Return: 0 or -ERRNO.
 */
पूर्णांक __nfp_eth_set_split(काष्ठा nfp_nsp *nsp, अचिन्हित पूर्णांक lanes)
अणु
	वापस NFP_ETH_SET_BIT_CONFIG(nsp, NSP_ETH_RAW_PORT, NSP_ETH_PORT_LANES,
				      lanes, NSP_ETH_CTRL_SET_LANES);
पूर्ण
