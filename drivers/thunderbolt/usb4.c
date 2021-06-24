<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB4 specअगरic functionality
 *
 * Copyright (C) 2019, Intel Corporation
 * Authors: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 *	    Rajmohan Mani <rajmohan.mani@पूर्णांकel.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/kसमय.स>

#समावेश "sb_regs.h"
#समावेश "tb.h"

#घोषणा USB4_DATA_DWORDS		16
#घोषणा USB4_DATA_RETRIES		3

क्रमागत usb4_sb_target अणु
	USB4_SB_TARGET_ROUTER,
	USB4_SB_TARGET_PARTNER,
	USB4_SB_TARGET_RETIMER,
पूर्ण;

#घोषणा USB4_NVM_READ_OFFSET_MASK	GENMASK(23, 2)
#घोषणा USB4_NVM_READ_OFFSET_SHIFT	2
#घोषणा USB4_NVM_READ_LENGTH_MASK	GENMASK(27, 24)
#घोषणा USB4_NVM_READ_LENGTH_SHIFT	24

#घोषणा USB4_NVM_SET_OFFSET_MASK	USB4_NVM_READ_OFFSET_MASK
#घोषणा USB4_NVM_SET_OFFSET_SHIFT	USB4_NVM_READ_OFFSET_SHIFT

#घोषणा USB4_DROM_ADDRESS_MASK		GENMASK(14, 2)
#घोषणा USB4_DROM_ADDRESS_SHIFT		2
#घोषणा USB4_DROM_SIZE_MASK		GENMASK(19, 15)
#घोषणा USB4_DROM_SIZE_SHIFT		15

#घोषणा USB4_NVM_SECTOR_SIZE_MASK	GENMASK(23, 0)

प्रकार पूर्णांक (*पढ़ो_block_fn)(व्योम *, अचिन्हित पूर्णांक, व्योम *, माप_प्रकार);
प्रकार पूर्णांक (*ग_लिखो_block_fn)(व्योम *, स्थिर व्योम *, माप_प्रकार);

अटल पूर्णांक usb4_चयन_रुको_क्रम_bit(काष्ठा tb_चयन *sw, u32 offset, u32 bit,
				    u32 value, पूर्णांक समयout_msec)
अणु
	kसमय_प्रकार समयout = kसमय_add_ms(kसमय_get(), समयout_msec);

	करो अणु
		u32 val;
		पूर्णांक ret;

		ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH, offset, 1);
		अगर (ret)
			वापस ret;

		अगर ((val & bit) == value)
			वापस 0;

		usleep_range(50, 100);
	पूर्ण जबतक (kसमय_beक्रमe(kसमय_get(), समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक usb4_करो_पढ़ो_data(u16 address, व्योम *buf, माप_प्रकार size,
			     पढ़ो_block_fn पढ़ो_block, व्योम *पढ़ो_block_data)
अणु
	अचिन्हित पूर्णांक retries = USB4_DATA_RETRIES;
	अचिन्हित पूर्णांक offset;

	करो अणु
		अचिन्हित पूर्णांक dwaddress, dwords;
		u8 data[USB4_DATA_DWORDS * 4];
		माप_प्रकार nbytes;
		पूर्णांक ret;

		offset = address & 3;
		nbytes = min_t(माप_प्रकार, size + offset, USB4_DATA_DWORDS * 4);

		dwaddress = address / 4;
		dwords = ALIGN(nbytes, 4) / 4;

		ret = पढ़ो_block(पढ़ो_block_data, dwaddress, data, dwords);
		अगर (ret) अणु
			अगर (ret != -ENODEV && retries--)
				जारी;
			वापस ret;
		पूर्ण

		nbytes -= offset;
		स_नकल(buf, data + offset, nbytes);

		size -= nbytes;
		address += nbytes;
		buf += nbytes;
	पूर्ण जबतक (size > 0);

	वापस 0;
पूर्ण

अटल पूर्णांक usb4_करो_ग_लिखो_data(अचिन्हित पूर्णांक address, स्थिर व्योम *buf, माप_प्रकार size,
	ग_लिखो_block_fn ग_लिखो_next_block, व्योम *ग_लिखो_block_data)
अणु
	अचिन्हित पूर्णांक retries = USB4_DATA_RETRIES;
	अचिन्हित पूर्णांक offset;

	offset = address & 3;
	address = address & ~3;

	करो अणु
		u32 nbytes = min_t(u32, size, USB4_DATA_DWORDS * 4);
		u8 data[USB4_DATA_DWORDS * 4];
		पूर्णांक ret;

		स_नकल(data + offset, buf, nbytes);

		ret = ग_लिखो_next_block(ग_लिखो_block_data, data, nbytes / 4);
		अगर (ret) अणु
			अगर (ret == -ETIMEDOUT) अणु
				अगर (retries--)
					जारी;
				ret = -EIO;
			पूर्ण
			वापस ret;
		पूर्ण

		size -= nbytes;
		address += nbytes;
		buf += nbytes;
	पूर्ण जबतक (size > 0);

	वापस 0;
पूर्ण

अटल पूर्णांक usb4_native_चयन_op(काष्ठा tb_चयन *sw, u16 opcode,
				 u32 *metadata, u8 *status,
				 स्थिर व्योम *tx_data, माप_प्रकार tx_dwords,
				 व्योम *rx_data, माप_प्रकार rx_dwords)
अणु
	u32 val;
	पूर्णांक ret;

	अगर (metadata) अणु
		ret = tb_sw_ग_लिखो(sw, metadata, TB_CFG_SWITCH, ROUTER_CS_25, 1);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (tx_dwords) अणु
		ret = tb_sw_ग_लिखो(sw, tx_data, TB_CFG_SWITCH, ROUTER_CS_9,
				  tx_dwords);
		अगर (ret)
			वापस ret;
	पूर्ण

	val = opcode | ROUTER_CS_26_OV;
	ret = tb_sw_ग_लिखो(sw, &val, TB_CFG_SWITCH, ROUTER_CS_26, 1);
	अगर (ret)
		वापस ret;

	ret = usb4_चयन_रुको_क्रम_bit(sw, ROUTER_CS_26, ROUTER_CS_26_OV, 0, 500);
	अगर (ret)
		वापस ret;

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH, ROUTER_CS_26, 1);
	अगर (ret)
		वापस ret;

	अगर (val & ROUTER_CS_26_ONS)
		वापस -EOPNOTSUPP;

	अगर (status)
		*status = (val & ROUTER_CS_26_STATUS_MASK) >>
			ROUTER_CS_26_STATUS_SHIFT;

	अगर (metadata) अणु
		ret = tb_sw_पढ़ो(sw, metadata, TB_CFG_SWITCH, ROUTER_CS_25, 1);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (rx_dwords) अणु
		ret = tb_sw_पढ़ो(sw, rx_data, TB_CFG_SWITCH, ROUTER_CS_9,
				 rx_dwords);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __usb4_चयन_op(काष्ठा tb_चयन *sw, u16 opcode, u32 *metadata,
			    u8 *status, स्थिर व्योम *tx_data, माप_प्रकार tx_dwords,
			    व्योम *rx_data, माप_प्रकार rx_dwords)
अणु
	स्थिर काष्ठा tb_cm_ops *cm_ops = sw->tb->cm_ops;

	अगर (tx_dwords > USB4_DATA_DWORDS || rx_dwords > USB4_DATA_DWORDS)
		वापस -EINVAL;

	/*
	 * If the connection manager implementation provides USB4 router
	 * operation proxy callback, call it here instead of running the
	 * operation natively.
	 */
	अगर (cm_ops->usb4_चयन_op) अणु
		पूर्णांक ret;

		ret = cm_ops->usb4_चयन_op(sw, opcode, metadata, status,
					     tx_data, tx_dwords, rx_data,
					     rx_dwords);
		अगर (ret != -EOPNOTSUPP)
			वापस ret;

		/*
		 * If the proxy was not supported then run the native
		 * router operation instead.
		 */
	पूर्ण

	वापस usb4_native_चयन_op(sw, opcode, metadata, status, tx_data,
				     tx_dwords, rx_data, rx_dwords);
पूर्ण

अटल अंतरभूत पूर्णांक usb4_चयन_op(काष्ठा tb_चयन *sw, u16 opcode,
				 u32 *metadata, u8 *status)
अणु
	वापस __usb4_चयन_op(sw, opcode, metadata, status, शून्य, 0, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक usb4_चयन_op_data(काष्ठा tb_चयन *sw, u16 opcode,
				      u32 *metadata, u8 *status,
				      स्थिर व्योम *tx_data, माप_प्रकार tx_dwords,
				      व्योम *rx_data, माप_प्रकार rx_dwords)
अणु
	वापस __usb4_चयन_op(sw, opcode, metadata, status, tx_data,
				tx_dwords, rx_data, rx_dwords);
पूर्ण

अटल व्योम usb4_चयन_check_wakes(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;
	bool wakeup = false;
	u32 val;

	अगर (!device_may_wakeup(&sw->dev))
		वापस;

	अगर (tb_route(sw)) अणु
		अगर (tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH, ROUTER_CS_6, 1))
			वापस;

		tb_sw_dbg(sw, "PCIe wake: %s, USB3 wake: %s\n",
			  (val & ROUTER_CS_6_WOPS) ? "yes" : "no",
			  (val & ROUTER_CS_6_WOUS) ? "yes" : "no");

		wakeup = val & (ROUTER_CS_6_WOPS | ROUTER_CS_6_WOUS);
	पूर्ण

	/* Check क्रम any connected करोwnstream ports क्रम USB4 wake */
	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (!tb_port_has_remote(port))
			जारी;

		अगर (tb_port_पढ़ो(port, &val, TB_CFG_PORT,
				 port->cap_usb4 + PORT_CS_18, 1))
			अवरोध;

		tb_port_dbg(port, "USB4 wake: %s\n",
			    (val & PORT_CS_18_WOU4S) ? "yes" : "no");

		अगर (val & PORT_CS_18_WOU4S)
			wakeup = true;
	पूर्ण

	अगर (wakeup)
		pm_wakeup_event(&sw->dev, 0);
पूर्ण

अटल bool link_is_usb4(काष्ठा tb_port *port)
अणु
	u32 val;

	अगर (!port->cap_usb4)
		वापस false;

	अगर (tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			 port->cap_usb4 + PORT_CS_18, 1))
		वापस false;

	वापस !(val & PORT_CS_18_TCM);
पूर्ण

/**
 * usb4_चयन_setup() - Additional setup क्रम USB4 device
 * @sw: USB4 router to setup
 *
 * USB4 routers need additional settings in order to enable all the
 * tunneling. This function enables USB and PCIe tunneling अगर it can be
 * enabled (e.g the parent चयन also supports them). If USB tunneling
 * is not available क्रम some reason (like that there is Thunderbolt 3
 * चयन upstream) then the पूर्णांकernal xHCI controller is enabled
 * instead.
 */
पूर्णांक usb4_चयन_setup(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *करोwnstream_port;
	काष्ठा tb_चयन *parent;
	bool tbt3, xhci;
	u32 val = 0;
	पूर्णांक ret;

	usb4_चयन_check_wakes(sw);

	अगर (!tb_route(sw))
		वापस 0;

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH, ROUTER_CS_6, 1);
	अगर (ret)
		वापस ret;

	parent = tb_चयन_parent(sw);
	करोwnstream_port = tb_port_at(tb_route(sw), parent);
	sw->link_usb4 = link_is_usb4(करोwnstream_port);
	tb_sw_dbg(sw, "link: %s\n", sw->link_usb4 ? "USB4" : "TBT3");

	xhci = val & ROUTER_CS_6_HCI;
	tbt3 = !(val & ROUTER_CS_6_TNS);

	tb_sw_dbg(sw, "TBT3 support: %s, xHCI: %s\n",
		  tbt3 ? "yes" : "no", xhci ? "yes" : "no");

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH, ROUTER_CS_5, 1);
	अगर (ret)
		वापस ret;

	अगर (tb_acpi_may_tunnel_usb3() && sw->link_usb4 &&
	    tb_चयन_find_port(parent, TB_TYPE_USB3_DOWN)) अणु
		val |= ROUTER_CS_5_UTO;
		xhci = false;
	पूर्ण

	/*
	 * Only enable PCIe tunneling अगर the parent router supports it
	 * and it is not disabled.
	 */
	अगर (tb_acpi_may_tunnel_pcie() &&
	    tb_चयन_find_port(parent, TB_TYPE_PCIE_DOWN)) अणु
		val |= ROUTER_CS_5_PTO;
		/*
		 * xHCI can be enabled अगर PCIe tunneling is supported
		 * and the parent करोes not have any USB3 करोwstream
		 * adapters (so we cannot करो USB 3.x tunneling).
		 */
		अगर (xhci)
			val |= ROUTER_CS_5_HCO;
	पूर्ण

	/* TBT3 supported by the CM */
	val |= ROUTER_CS_5_C3S;
	/* Tunneling configuration is पढ़ोy now */
	val |= ROUTER_CS_5_CV;

	ret = tb_sw_ग_लिखो(sw, &val, TB_CFG_SWITCH, ROUTER_CS_5, 1);
	अगर (ret)
		वापस ret;

	वापस usb4_चयन_रुको_क्रम_bit(sw, ROUTER_CS_6, ROUTER_CS_6_CR,
					ROUTER_CS_6_CR, 50);
पूर्ण

/**
 * usb4_चयन_पढ़ो_uid() - Read UID from USB4 router
 * @sw: USB4 router
 * @uid: UID is stored here
 *
 * Reads 64-bit UID from USB4 router config space.
 */
पूर्णांक usb4_चयन_पढ़ो_uid(काष्ठा tb_चयन *sw, u64 *uid)
अणु
	वापस tb_sw_पढ़ो(sw, uid, TB_CFG_SWITCH, ROUTER_CS_7, 2);
पूर्ण

अटल पूर्णांक usb4_चयन_drom_पढ़ो_block(व्योम *data,
				       अचिन्हित पूर्णांक dwaddress, व्योम *buf,
				       माप_प्रकार dwords)
अणु
	काष्ठा tb_चयन *sw = data;
	u8 status = 0;
	u32 metadata;
	पूर्णांक ret;

	metadata = (dwords << USB4_DROM_SIZE_SHIFT) & USB4_DROM_SIZE_MASK;
	metadata |= (dwaddress << USB4_DROM_ADDRESS_SHIFT) &
		USB4_DROM_ADDRESS_MASK;

	ret = usb4_चयन_op_data(sw, USB4_SWITCH_OP_DROM_READ, &metadata,
				  &status, शून्य, 0, buf, dwords);
	अगर (ret)
		वापस ret;

	वापस status ? -EIO : 0;
पूर्ण

/**
 * usb4_चयन_drom_पढ़ो() - Read arbitrary bytes from USB4 router DROM
 * @sw: USB4 router
 * @address: Byte address inside DROM to start पढ़ोing
 * @buf: Buffer where the DROM content is stored
 * @size: Number of bytes to पढ़ो from DROM
 *
 * Uses USB4 router operations to पढ़ो router DROM. For devices this
 * should always work but क्रम hosts it may वापस %-EOPNOTSUPP in which
 * हाल the host router करोes not have DROM.
 */
पूर्णांक usb4_चयन_drom_पढ़ो(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक address, व्योम *buf,
			  माप_प्रकार size)
अणु
	वापस usb4_करो_पढ़ो_data(address, buf, size,
				 usb4_चयन_drom_पढ़ो_block, sw);
पूर्ण

/**
 * usb4_चयन_lane_bonding_possible() - Are conditions met क्रम lane bonding
 * @sw: USB4 router
 *
 * Checks whether conditions are met so that lane bonding can be
 * established with the upstream router. Call only क्रम device routers.
 */
bool usb4_चयन_lane_bonding_possible(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *up;
	पूर्णांक ret;
	u32 val;

	up = tb_upstream_port(sw);
	ret = tb_port_पढ़ो(up, &val, TB_CFG_PORT, up->cap_usb4 + PORT_CS_18, 1);
	अगर (ret)
		वापस false;

	वापस !!(val & PORT_CS_18_BE);
पूर्ण

/**
 * usb4_चयन_set_wake() - Enabled/disable wake
 * @sw: USB4 router
 * @flags: Wakeup flags (%0 to disable)
 *
 * Enables/disables router to wake up from sleep.
 */
पूर्णांक usb4_चयन_set_wake(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा tb_port *port;
	u64 route = tb_route(sw);
	u32 val;
	पूर्णांक ret;

	/*
	 * Enable wakes coming from all USB4 करोwnstream ports (from
	 * child routers). For device routers करो this also क्रम the
	 * upstream USB4 port.
	 */
	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (!tb_port_is_null(port))
			जारी;
		अगर (!route && tb_is_upstream_port(port))
			जारी;
		अगर (!port->cap_usb4)
			जारी;

		ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
				   port->cap_usb4 + PORT_CS_19, 1);
		अगर (ret)
			वापस ret;

		val &= ~(PORT_CS_19_WOC | PORT_CS_19_WOD | PORT_CS_19_WOU4);

		अगर (flags & TB_WAKE_ON_CONNECT)
			val |= PORT_CS_19_WOC;
		अगर (flags & TB_WAKE_ON_DISCONNECT)
			val |= PORT_CS_19_WOD;
		अगर (flags & TB_WAKE_ON_USB4)
			val |= PORT_CS_19_WOU4;

		ret = tb_port_ग_लिखो(port, &val, TB_CFG_PORT,
				    port->cap_usb4 + PORT_CS_19, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Enable wakes from PCIe and USB 3.x on this router. Only
	 * needed क्रम device routers.
	 */
	अगर (route) अणु
		ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH, ROUTER_CS_5, 1);
		अगर (ret)
			वापस ret;

		val &= ~(ROUTER_CS_5_WOP | ROUTER_CS_5_WOU);
		अगर (flags & TB_WAKE_ON_USB3)
			val |= ROUTER_CS_5_WOU;
		अगर (flags & TB_WAKE_ON_PCIE)
			val |= ROUTER_CS_5_WOP;

		ret = tb_sw_ग_लिखो(sw, &val, TB_CFG_SWITCH, ROUTER_CS_5, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * usb4_चयन_set_sleep() - Prepare the router to enter sleep
 * @sw: USB4 router
 *
 * Sets sleep bit क्रम the router. Returns when the router sleep पढ़ोy
 * bit has been निश्चितed.
 */
पूर्णांक usb4_चयन_set_sleep(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक ret;
	u32 val;

	/* Set sleep bit and रुको क्रम sleep पढ़ोy to be निश्चितed */
	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH, ROUTER_CS_5, 1);
	अगर (ret)
		वापस ret;

	val |= ROUTER_CS_5_SLP;

	ret = tb_sw_ग_लिखो(sw, &val, TB_CFG_SWITCH, ROUTER_CS_5, 1);
	अगर (ret)
		वापस ret;

	वापस usb4_चयन_रुको_क्रम_bit(sw, ROUTER_CS_6, ROUTER_CS_6_SLPR,
					ROUTER_CS_6_SLPR, 500);
पूर्ण

/**
 * usb4_चयन_nvm_sector_size() - Return router NVM sector size
 * @sw: USB4 router
 *
 * If the router supports NVM operations this function वापसs the NVM
 * sector size in bytes. If NVM operations are not supported वापसs
 * %-EOPNOTSUPP.
 */
पूर्णांक usb4_चयन_nvm_sector_size(काष्ठा tb_चयन *sw)
अणु
	u32 metadata;
	u8 status;
	पूर्णांक ret;

	ret = usb4_चयन_op(sw, USB4_SWITCH_OP_NVM_SECTOR_SIZE, &metadata,
			     &status);
	अगर (ret)
		वापस ret;

	अगर (status)
		वापस status == 0x2 ? -EOPNOTSUPP : -EIO;

	वापस metadata & USB4_NVM_SECTOR_SIZE_MASK;
पूर्ण

अटल पूर्णांक usb4_चयन_nvm_पढ़ो_block(व्योम *data,
	अचिन्हित पूर्णांक dwaddress, व्योम *buf, माप_प्रकार dwords)
अणु
	काष्ठा tb_चयन *sw = data;
	u8 status = 0;
	u32 metadata;
	पूर्णांक ret;

	metadata = (dwords << USB4_NVM_READ_LENGTH_SHIFT) &
		   USB4_NVM_READ_LENGTH_MASK;
	metadata |= (dwaddress << USB4_NVM_READ_OFFSET_SHIFT) &
		   USB4_NVM_READ_OFFSET_MASK;

	ret = usb4_चयन_op_data(sw, USB4_SWITCH_OP_NVM_READ, &metadata,
				  &status, शून्य, 0, buf, dwords);
	अगर (ret)
		वापस ret;

	वापस status ? -EIO : 0;
पूर्ण

/**
 * usb4_चयन_nvm_पढ़ो() - Read arbitrary bytes from router NVM
 * @sw: USB4 router
 * @address: Starting address in bytes
 * @buf: Read data is placed here
 * @size: How many bytes to पढ़ो
 *
 * Reads NVM contents of the router. If NVM is not supported वापसs
 * %-EOPNOTSUPP.
 */
पूर्णांक usb4_चयन_nvm_पढ़ो(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक address, व्योम *buf,
			 माप_प्रकार size)
अणु
	वापस usb4_करो_पढ़ो_data(address, buf, size,
				 usb4_चयन_nvm_पढ़ो_block, sw);
पूर्ण

अटल पूर्णांक usb4_चयन_nvm_set_offset(काष्ठा tb_चयन *sw,
				      अचिन्हित पूर्णांक address)
अणु
	u32 metadata, dwaddress;
	u8 status = 0;
	पूर्णांक ret;

	dwaddress = address / 4;
	metadata = (dwaddress << USB4_NVM_SET_OFFSET_SHIFT) &
		   USB4_NVM_SET_OFFSET_MASK;

	ret = usb4_चयन_op(sw, USB4_SWITCH_OP_NVM_SET_OFFSET, &metadata,
			     &status);
	अगर (ret)
		वापस ret;

	वापस status ? -EIO : 0;
पूर्ण

अटल पूर्णांक usb4_चयन_nvm_ग_लिखो_next_block(व्योम *data, स्थिर व्योम *buf,
					    माप_प्रकार dwords)
अणु
	काष्ठा tb_चयन *sw = data;
	u8 status;
	पूर्णांक ret;

	ret = usb4_चयन_op_data(sw, USB4_SWITCH_OP_NVM_WRITE, शून्य, &status,
				  buf, dwords, शून्य, 0);
	अगर (ret)
		वापस ret;

	वापस status ? -EIO : 0;
पूर्ण

/**
 * usb4_चयन_nvm_ग_लिखो() - Write to the router NVM
 * @sw: USB4 router
 * @address: Start address where to ग_लिखो in bytes
 * @buf: Poपूर्णांकer to the data to ग_लिखो
 * @size: Size of @buf in bytes
 *
 * Writes @buf to the router NVM using USB4 router operations. If NVM
 * ग_लिखो is not supported वापसs %-EOPNOTSUPP.
 */
पूर्णांक usb4_चयन_nvm_ग_लिखो(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक address,
			  स्थिर व्योम *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = usb4_चयन_nvm_set_offset(sw, address);
	अगर (ret)
		वापस ret;

	वापस usb4_करो_ग_लिखो_data(address, buf, size,
				  usb4_चयन_nvm_ग_लिखो_next_block, sw);
पूर्ण

/**
 * usb4_चयन_nvm_authenticate() - Authenticate new NVM
 * @sw: USB4 router
 *
 * After the new NVM has been written via usb4_चयन_nvm_ग_लिखो(), this
 * function triggers NVM authentication process. The router माला_लो घातer
 * cycled and अगर the authentication is successful the new NVM starts
 * running. In हाल of failure वापसs negative त्रुटि_सं.
 *
 * The caller should call usb4_चयन_nvm_authenticate_status() to पढ़ो
 * the status of the authentication after घातer cycle. It should be the
 * first router operation to aव्योम the status being lost.
 */
पूर्णांक usb4_चयन_nvm_authenticate(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक ret;

	ret = usb4_चयन_op(sw, USB4_SWITCH_OP_NVM_AUTH, शून्य, शून्य);
	चयन (ret) अणु
	/*
	 * The router is घातer cycled once NVM_AUTH is started so it is
	 * expected to get any of the following errors back.
	 */
	हाल -EACCES:
	हाल -ENOTCONN:
	हाल -ETIMEDOUT:
		वापस 0;

	शेष:
		वापस ret;
	पूर्ण
पूर्ण

/**
 * usb4_चयन_nvm_authenticate_status() - Read status of last NVM authenticate
 * @sw: USB4 router
 * @status: Status code of the operation
 *
 * The function checks अगर there is status available from the last NVM
 * authenticate router operation. If there is status then %0 is वापसed
 * and the status code is placed in @status. Returns negative त्रुटि_सं in हाल
 * of failure.
 *
 * Must be called beक्रमe any other router operation.
 */
पूर्णांक usb4_चयन_nvm_authenticate_status(काष्ठा tb_चयन *sw, u32 *status)
अणु
	स्थिर काष्ठा tb_cm_ops *cm_ops = sw->tb->cm_ops;
	u16 opcode;
	u32 val;
	पूर्णांक ret;

	अगर (cm_ops->usb4_चयन_nvm_authenticate_status) अणु
		ret = cm_ops->usb4_चयन_nvm_authenticate_status(sw, status);
		अगर (ret != -EOPNOTSUPP)
			वापस ret;
	पूर्ण

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH, ROUTER_CS_26, 1);
	अगर (ret)
		वापस ret;

	/* Check that the opcode is correct */
	opcode = val & ROUTER_CS_26_OPCODE_MASK;
	अगर (opcode == USB4_SWITCH_OP_NVM_AUTH) अणु
		अगर (val & ROUTER_CS_26_OV)
			वापस -EBUSY;
		अगर (val & ROUTER_CS_26_ONS)
			वापस -EOPNOTSUPP;

		*status = (val & ROUTER_CS_26_STATUS_MASK) >>
			ROUTER_CS_26_STATUS_SHIFT;
	पूर्ण अन्यथा अणु
		*status = 0;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * usb4_चयन_query_dp_resource() - Query availability of DP IN resource
 * @sw: USB4 router
 * @in: DP IN adapter
 *
 * For DP tunneling this function can be used to query availability of
 * DP IN resource. Returns true अगर the resource is available क्रम DP
 * tunneling, false otherwise.
 */
bool usb4_चयन_query_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in)
अणु
	u32 metadata = in->port;
	u8 status;
	पूर्णांक ret;

	ret = usb4_चयन_op(sw, USB4_SWITCH_OP_QUERY_DP_RESOURCE, &metadata,
			     &status);
	/*
	 * If DP resource allocation is not supported assume it is
	 * always available.
	 */
	अगर (ret == -EOPNOTSUPP)
		वापस true;
	अन्यथा अगर (ret)
		वापस false;

	वापस !status;
पूर्ण

/**
 * usb4_चयन_alloc_dp_resource() - Allocate DP IN resource
 * @sw: USB4 router
 * @in: DP IN adapter
 *
 * Allocates DP IN resource क्रम DP tunneling using USB4 router
 * operations. If the resource was allocated वापसs %0. Otherwise
 * वापसs negative त्रुटि_सं, in particular %-EBUSY अगर the resource is
 * alपढ़ोy allocated.
 */
पूर्णांक usb4_चयन_alloc_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in)
अणु
	u32 metadata = in->port;
	u8 status;
	पूर्णांक ret;

	ret = usb4_चयन_op(sw, USB4_SWITCH_OP_ALLOC_DP_RESOURCE, &metadata,
			     &status);
	अगर (ret == -EOPNOTSUPP)
		वापस 0;
	अन्यथा अगर (ret)
		वापस ret;

	वापस status ? -EBUSY : 0;
पूर्ण

/**
 * usb4_चयन_dealloc_dp_resource() - Releases allocated DP IN resource
 * @sw: USB4 router
 * @in: DP IN adapter
 *
 * Releases the previously allocated DP IN resource.
 */
पूर्णांक usb4_चयन_dealloc_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in)
अणु
	u32 metadata = in->port;
	u8 status;
	पूर्णांक ret;

	ret = usb4_चयन_op(sw, USB4_SWITCH_OP_DEALLOC_DP_RESOURCE, &metadata,
			     &status);
	अगर (ret == -EOPNOTSUPP)
		वापस 0;
	अन्यथा अगर (ret)
		वापस ret;

	वापस status ? -EIO : 0;
पूर्ण

अटल पूर्णांक usb4_port_idx(स्थिर काष्ठा tb_चयन *sw, स्थिर काष्ठा tb_port *port)
अणु
	काष्ठा tb_port *p;
	पूर्णांक usb4_idx = 0;

	/* Assume port is primary */
	tb_चयन_क्रम_each_port(sw, p) अणु
		अगर (!tb_port_is_null(p))
			जारी;
		अगर (tb_is_upstream_port(p))
			जारी;
		अगर (!p->link_nr) अणु
			अगर (p == port)
				अवरोध;
			usb4_idx++;
		पूर्ण
	पूर्ण

	वापस usb4_idx;
पूर्ण

/**
 * usb4_चयन_map_pcie_करोwn() - Map USB4 port to a PCIe करोwnstream adapter
 * @sw: USB4 router
 * @port: USB4 port
 *
 * USB4 routers have direct mapping between USB4 ports and PCIe
 * करोwnstream adapters where the PCIe topology is extended. This
 * function वापसs the corresponding करोwnstream PCIe adapter or %शून्य
 * अगर no such mapping was possible.
 */
काष्ठा tb_port *usb4_चयन_map_pcie_करोwn(काष्ठा tb_चयन *sw,
					  स्थिर काष्ठा tb_port *port)
अणु
	पूर्णांक usb4_idx = usb4_port_idx(sw, port);
	काष्ठा tb_port *p;
	पूर्णांक pcie_idx = 0;

	/* Find PCIe करोwn port matching usb4_port */
	tb_चयन_क्रम_each_port(sw, p) अणु
		अगर (!tb_port_is_pcie_करोwn(p))
			जारी;

		अगर (pcie_idx == usb4_idx)
			वापस p;

		pcie_idx++;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * usb4_चयन_map_usb3_करोwn() - Map USB4 port to a USB3 करोwnstream adapter
 * @sw: USB4 router
 * @port: USB4 port
 *
 * USB4 routers have direct mapping between USB4 ports and USB 3.x
 * करोwnstream adapters where the USB 3.x topology is extended. This
 * function वापसs the corresponding करोwnstream USB 3.x adapter or
 * %शून्य अगर no such mapping was possible.
 */
काष्ठा tb_port *usb4_चयन_map_usb3_करोwn(काष्ठा tb_चयन *sw,
					  स्थिर काष्ठा tb_port *port)
अणु
	पूर्णांक usb4_idx = usb4_port_idx(sw, port);
	काष्ठा tb_port *p;
	पूर्णांक usb_idx = 0;

	/* Find USB3 करोwn port matching usb4_port */
	tb_चयन_क्रम_each_port(sw, p) अणु
		अगर (!tb_port_is_usb3_करोwn(p))
			जारी;

		अगर (usb_idx == usb4_idx)
			वापस p;

		usb_idx++;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * usb4_port_unlock() - Unlock USB4 करोwnstream port
 * @port: USB4 port to unlock
 *
 * Unlocks USB4 करोwnstream port so that the connection manager can
 * access the router below this port.
 */
पूर्णांक usb4_port_unlock(काष्ठा tb_port *port)
अणु
	पूर्णांक ret;
	u32 val;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT, ADP_CS_4, 1);
	अगर (ret)
		वापस ret;

	val &= ~ADP_CS_4_LCK;
	वापस tb_port_ग_लिखो(port, &val, TB_CFG_PORT, ADP_CS_4, 1);
पूर्ण

अटल पूर्णांक usb4_port_set_configured(काष्ठा tb_port *port, bool configured)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (!port->cap_usb4)
		वापस -EINVAL;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_usb4 + PORT_CS_19, 1);
	अगर (ret)
		वापस ret;

	अगर (configured)
		val |= PORT_CS_19_PC;
	अन्यथा
		val &= ~PORT_CS_19_PC;

	वापस tb_port_ग_लिखो(port, &val, TB_CFG_PORT,
			     port->cap_usb4 + PORT_CS_19, 1);
पूर्ण

/**
 * usb4_port_configure() - Set USB4 port configured
 * @port: USB4 router
 *
 * Sets the USB4 link to be configured क्रम घातer management purposes.
 */
पूर्णांक usb4_port_configure(काष्ठा tb_port *port)
अणु
	वापस usb4_port_set_configured(port, true);
पूर्ण

/**
 * usb4_port_unconfigure() - Set USB4 port unconfigured
 * @port: USB4 router
 *
 * Sets the USB4 link to be unconfigured क्रम घातer management purposes.
 */
व्योम usb4_port_unconfigure(काष्ठा tb_port *port)
अणु
	usb4_port_set_configured(port, false);
पूर्ण

अटल पूर्णांक usb4_set_xकरोमुख्य_configured(काष्ठा tb_port *port, bool configured)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (!port->cap_usb4)
		वापस -EINVAL;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_usb4 + PORT_CS_19, 1);
	अगर (ret)
		वापस ret;

	अगर (configured)
		val |= PORT_CS_19_PID;
	अन्यथा
		val &= ~PORT_CS_19_PID;

	वापस tb_port_ग_लिखो(port, &val, TB_CFG_PORT,
			     port->cap_usb4 + PORT_CS_19, 1);
पूर्ण

/**
 * usb4_port_configure_xकरोमुख्य() - Configure port क्रम XDoमुख्य
 * @port: USB4 port connected to another host
 *
 * Marks the USB4 port as being connected to another host. Returns %0 in
 * success and negative त्रुटि_सं in failure.
 */
पूर्णांक usb4_port_configure_xकरोमुख्य(काष्ठा tb_port *port)
अणु
	वापस usb4_set_xकरोमुख्य_configured(port, true);
पूर्ण

/**
 * usb4_port_unconfigure_xकरोमुख्य() - Unconfigure port क्रम XDoमुख्य
 * @port: USB4 port that was connected to another host
 *
 * Clears USB4 port from being marked as XDoमुख्य.
 */
व्योम usb4_port_unconfigure_xकरोमुख्य(काष्ठा tb_port *port)
अणु
	usb4_set_xकरोमुख्य_configured(port, false);
पूर्ण

अटल पूर्णांक usb4_port_रुको_क्रम_bit(काष्ठा tb_port *port, u32 offset, u32 bit,
				  u32 value, पूर्णांक समयout_msec)
अणु
	kसमय_प्रकार समयout = kसमय_add_ms(kसमय_get(), समयout_msec);

	करो अणु
		u32 val;
		पूर्णांक ret;

		ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT, offset, 1);
		अगर (ret)
			वापस ret;

		अगर ((val & bit) == value)
			वापस 0;

		usleep_range(50, 100);
	पूर्ण जबतक (kसमय_beक्रमe(kसमय_get(), समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक usb4_port_पढ़ो_data(काष्ठा tb_port *port, व्योम *data, माप_प्रकार dwords)
अणु
	अगर (dwords > USB4_DATA_DWORDS)
		वापस -EINVAL;

	वापस tb_port_पढ़ो(port, data, TB_CFG_PORT, port->cap_usb4 + PORT_CS_2,
			    dwords);
पूर्ण

अटल पूर्णांक usb4_port_ग_लिखो_data(काष्ठा tb_port *port, स्थिर व्योम *data,
				माप_प्रकार dwords)
अणु
	अगर (dwords > USB4_DATA_DWORDS)
		वापस -EINVAL;

	वापस tb_port_ग_लिखो(port, data, TB_CFG_PORT, port->cap_usb4 + PORT_CS_2,
			     dwords);
पूर्ण

अटल पूर्णांक usb4_port_sb_पढ़ो(काष्ठा tb_port *port, क्रमागत usb4_sb_target target,
			     u8 index, u8 reg, व्योम *buf, u8 size)
अणु
	माप_प्रकार dwords = DIV_ROUND_UP(size, 4);
	पूर्णांक ret;
	u32 val;

	अगर (!port->cap_usb4)
		वापस -EINVAL;

	val = reg;
	val |= size << PORT_CS_1_LENGTH_SHIFT;
	val |= (target << PORT_CS_1_TARGET_SHIFT) & PORT_CS_1_TARGET_MASK;
	अगर (target == USB4_SB_TARGET_RETIMER)
		val |= (index << PORT_CS_1_RETIMER_INDEX_SHIFT);
	val |= PORT_CS_1_PND;

	ret = tb_port_ग_लिखो(port, &val, TB_CFG_PORT,
			    port->cap_usb4 + PORT_CS_1, 1);
	अगर (ret)
		वापस ret;

	ret = usb4_port_रुको_क्रम_bit(port, port->cap_usb4 + PORT_CS_1,
				     PORT_CS_1_PND, 0, 500);
	अगर (ret)
		वापस ret;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			    port->cap_usb4 + PORT_CS_1, 1);
	अगर (ret)
		वापस ret;

	अगर (val & PORT_CS_1_NR)
		वापस -ENODEV;
	अगर (val & PORT_CS_1_RC)
		वापस -EIO;

	वापस buf ? usb4_port_पढ़ो_data(port, buf, dwords) : 0;
पूर्ण

अटल पूर्णांक usb4_port_sb_ग_लिखो(काष्ठा tb_port *port, क्रमागत usb4_sb_target target,
			      u8 index, u8 reg, स्थिर व्योम *buf, u8 size)
अणु
	माप_प्रकार dwords = DIV_ROUND_UP(size, 4);
	पूर्णांक ret;
	u32 val;

	अगर (!port->cap_usb4)
		वापस -EINVAL;

	अगर (buf) अणु
		ret = usb4_port_ग_लिखो_data(port, buf, dwords);
		अगर (ret)
			वापस ret;
	पूर्ण

	val = reg;
	val |= size << PORT_CS_1_LENGTH_SHIFT;
	val |= PORT_CS_1_WNR_WRITE;
	val |= (target << PORT_CS_1_TARGET_SHIFT) & PORT_CS_1_TARGET_MASK;
	अगर (target == USB4_SB_TARGET_RETIMER)
		val |= (index << PORT_CS_1_RETIMER_INDEX_SHIFT);
	val |= PORT_CS_1_PND;

	ret = tb_port_ग_लिखो(port, &val, TB_CFG_PORT,
			    port->cap_usb4 + PORT_CS_1, 1);
	अगर (ret)
		वापस ret;

	ret = usb4_port_रुको_क्रम_bit(port, port->cap_usb4 + PORT_CS_1,
				     PORT_CS_1_PND, 0, 500);
	अगर (ret)
		वापस ret;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			    port->cap_usb4 + PORT_CS_1, 1);
	अगर (ret)
		वापस ret;

	अगर (val & PORT_CS_1_NR)
		वापस -ENODEV;
	अगर (val & PORT_CS_1_RC)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक usb4_port_sb_op(काष्ठा tb_port *port, क्रमागत usb4_sb_target target,
			   u8 index, क्रमागत usb4_sb_opcode opcode, पूर्णांक समयout_msec)
अणु
	kसमय_प्रकार समयout;
	u32 val;
	पूर्णांक ret;

	val = opcode;
	ret = usb4_port_sb_ग_लिखो(port, target, index, USB4_SB_OPCODE, &val,
				 माप(val));
	अगर (ret)
		वापस ret;

	समयout = kसमय_add_ms(kसमय_get(), समयout_msec);

	करो अणु
		/* Check results */
		ret = usb4_port_sb_पढ़ो(port, target, index, USB4_SB_OPCODE,
					&val, माप(val));
		अगर (ret)
			वापस ret;

		चयन (val) अणु
		हाल 0:
			वापस 0;

		हाल USB4_SB_OPCODE_ERR:
			वापस -EAGAIN;

		हाल USB4_SB_OPCODE_ONS:
			वापस -EOPNOTSUPP;

		शेष:
			अगर (val != opcode)
				वापस -EIO;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (kसमय_beक्रमe(kसमय_get(), समयout));

	वापस -ETIMEDOUT;
पूर्ण

/**
 * usb4_port_क्रमागतerate_reसमयrs() - Send RT broadcast transaction
 * @port: USB4 port
 *
 * This क्रमces the USB4 port to send broadcast RT transaction which
 * makes the reसमयrs on the link to assign index to themselves. Returns
 * %0 in हाल of success and negative त्रुटि_सं अगर there was an error.
 */
पूर्णांक usb4_port_क्रमागतerate_reसमयrs(काष्ठा tb_port *port)
अणु
	u32 val;

	val = USB4_SB_OPCODE_ENUMERATE_RETIMERS;
	वापस usb4_port_sb_ग_लिखो(port, USB4_SB_TARGET_ROUTER, 0,
				  USB4_SB_OPCODE, &val, माप(val));
पूर्ण

अटल अंतरभूत पूर्णांक usb4_port_reसमयr_op(काष्ठा tb_port *port, u8 index,
				       क्रमागत usb4_sb_opcode opcode,
				       पूर्णांक समयout_msec)
अणु
	वापस usb4_port_sb_op(port, USB4_SB_TARGET_RETIMER, index, opcode,
			       समयout_msec);
पूर्ण

/**
 * usb4_port_reसमयr_पढ़ो() - Read from reसमयr sideband रेजिस्टरs
 * @port: USB4 port
 * @index: Reसमयr index
 * @reg: Sideband रेजिस्टर to पढ़ो
 * @buf: Data from @reg is stored here
 * @size: Number of bytes to पढ़ो
 *
 * Function पढ़ोs reसमयr sideband रेजिस्टरs starting from @reg. The
 * reसमयr is connected to @port at @index. Returns %0 in हाल of
 * success, and पढ़ो data is copied to @buf. If there is no reसमयr
 * present at given @index वापसs %-ENODEV. In any other failure
 * वापसs negative त्रुटि_सं.
 */
पूर्णांक usb4_port_reसमयr_पढ़ो(काष्ठा tb_port *port, u8 index, u8 reg, व्योम *buf,
			   u8 size)
अणु
	वापस usb4_port_sb_पढ़ो(port, USB4_SB_TARGET_RETIMER, index, reg, buf,
				 size);
पूर्ण

/**
 * usb4_port_reसमयr_ग_लिखो() - Write to reसमयr sideband रेजिस्टरs
 * @port: USB4 port
 * @index: Reसमयr index
 * @reg: Sideband रेजिस्टर to ग_लिखो
 * @buf: Data that is written starting from @reg
 * @size: Number of bytes to ग_लिखो
 *
 * Writes reसमयr sideband रेजिस्टरs starting from @reg. The reसमयr is
 * connected to @port at @index. Returns %0 in हाल of success. If there
 * is no reसमयr present at given @index वापसs %-ENODEV. In any other
 * failure वापसs negative त्रुटि_सं.
 */
पूर्णांक usb4_port_reसमयr_ग_लिखो(काष्ठा tb_port *port, u8 index, u8 reg,
			    स्थिर व्योम *buf, u8 size)
अणु
	वापस usb4_port_sb_ग_लिखो(port, USB4_SB_TARGET_RETIMER, index, reg, buf,
				  size);
पूर्ण

/**
 * usb4_port_reसमयr_is_last() - Is the reसमयr last on-board reसमयr
 * @port: USB4 port
 * @index: Reसमयr index
 *
 * If the reसमयr at @index is last one (connected directly to the
 * Type-C port) this function वापसs %1. If it is not वापसs %0. If
 * the reसमयr is not present वापसs %-ENODEV. Otherwise वापसs
 * negative त्रुटि_सं.
 */
पूर्णांक usb4_port_reसमयr_is_last(काष्ठा tb_port *port, u8 index)
अणु
	u32 metadata;
	पूर्णांक ret;

	ret = usb4_port_reसमयr_op(port, index, USB4_SB_OPCODE_QUERY_LAST_RETIMER,
				   500);
	अगर (ret)
		वापस ret;

	ret = usb4_port_reसमयr_पढ़ो(port, index, USB4_SB_METADATA, &metadata,
				     माप(metadata));
	वापस ret ? ret : metadata & 1;
पूर्ण

/**
 * usb4_port_reसमयr_nvm_sector_size() - Read reसमयr NVM sector size
 * @port: USB4 port
 * @index: Reसमयr index
 *
 * Reads NVM sector size (in bytes) of a reसमयr at @index. This
 * operation can be used to determine whether the reसमयr supports NVM
 * upgrade क्रम example. Returns sector size in bytes or negative त्रुटि_सं
 * in हाल of error. Specअगरically वापसs %-ENODEV अगर there is no
 * reसमयr at @index.
 */
पूर्णांक usb4_port_reसमयr_nvm_sector_size(काष्ठा tb_port *port, u8 index)
अणु
	u32 metadata;
	पूर्णांक ret;

	ret = usb4_port_reसमयr_op(port, index, USB4_SB_OPCODE_GET_NVM_SECTOR_SIZE,
				   500);
	अगर (ret)
		वापस ret;

	ret = usb4_port_reसमयr_पढ़ो(port, index, USB4_SB_METADATA, &metadata,
				     माप(metadata));
	वापस ret ? ret : metadata & USB4_NVM_SECTOR_SIZE_MASK;
पूर्ण

अटल पूर्णांक usb4_port_reसमयr_nvm_set_offset(काष्ठा tb_port *port, u8 index,
					    अचिन्हित पूर्णांक address)
अणु
	u32 metadata, dwaddress;
	पूर्णांक ret;

	dwaddress = address / 4;
	metadata = (dwaddress << USB4_NVM_SET_OFFSET_SHIFT) &
		  USB4_NVM_SET_OFFSET_MASK;

	ret = usb4_port_reसमयr_ग_लिखो(port, index, USB4_SB_METADATA, &metadata,
				      माप(metadata));
	अगर (ret)
		वापस ret;

	वापस usb4_port_reसमयr_op(port, index, USB4_SB_OPCODE_NVM_SET_OFFSET,
				    500);
पूर्ण

काष्ठा reसमयr_info अणु
	काष्ठा tb_port *port;
	u8 index;
पूर्ण;

अटल पूर्णांक usb4_port_reसमयr_nvm_ग_लिखो_next_block(व्योम *data, स्थिर व्योम *buf,
						  माप_प्रकार dwords)

अणु
	स्थिर काष्ठा reसमयr_info *info = data;
	काष्ठा tb_port *port = info->port;
	u8 index = info->index;
	पूर्णांक ret;

	ret = usb4_port_reसमयr_ग_लिखो(port, index, USB4_SB_DATA,
				      buf, dwords * 4);
	अगर (ret)
		वापस ret;

	वापस usb4_port_reसमयr_op(port, index,
			USB4_SB_OPCODE_NVM_BLOCK_WRITE, 1000);
पूर्ण

/**
 * usb4_port_reसमयr_nvm_ग_लिखो() - Write to reसमयr NVM
 * @port: USB4 port
 * @index: Reसमयr index
 * @address: Byte address where to start the ग_लिखो
 * @buf: Data to ग_लिखो
 * @size: Size in bytes how much to ग_लिखो
 *
 * Writes @size bytes from @buf to the reसमयr NVM. Used क्रम NVM
 * upgrade. Returns %0 अगर the data was written successfully and negative
 * त्रुटि_सं in हाल of failure. Specअगरically वापसs %-ENODEV अगर there is
 * no reसमयr at @index.
 */
पूर्णांक usb4_port_reसमयr_nvm_ग_लिखो(काष्ठा tb_port *port, u8 index, अचिन्हित पूर्णांक address,
				स्थिर व्योम *buf, माप_प्रकार size)
अणु
	काष्ठा reसमयr_info info = अणु .port = port, .index = index पूर्ण;
	पूर्णांक ret;

	ret = usb4_port_reसमयr_nvm_set_offset(port, index, address);
	अगर (ret)
		वापस ret;

	वापस usb4_करो_ग_लिखो_data(address, buf, size,
			usb4_port_reसमयr_nvm_ग_लिखो_next_block, &info);
पूर्ण

/**
 * usb4_port_reसमयr_nvm_authenticate() - Start reसमयr NVM upgrade
 * @port: USB4 port
 * @index: Reसमयr index
 *
 * After the new NVM image has been written via usb4_port_reसमयr_nvm_ग_लिखो()
 * this function can be used to trigger the NVM upgrade process. If
 * successful the reसमयr restarts with the new NVM and may not have the
 * index set so one needs to call usb4_port_क्रमागतerate_reसमयrs() to
 * क्रमce index to be asचिन्हित.
 */
पूर्णांक usb4_port_reसमयr_nvm_authenticate(काष्ठा tb_port *port, u8 index)
अणु
	u32 val;

	/*
	 * We need to use the raw operation here because once the
	 * authentication completes the reसमयr index is not set anymore
	 * so we करो not get back the status now.
	 */
	val = USB4_SB_OPCODE_NVM_AUTH_WRITE;
	वापस usb4_port_sb_ग_लिखो(port, USB4_SB_TARGET_RETIMER, index,
				  USB4_SB_OPCODE, &val, माप(val));
पूर्ण

/**
 * usb4_port_reसमयr_nvm_authenticate_status() - Read status of NVM upgrade
 * @port: USB4 port
 * @index: Reसमयr index
 * @status: Raw status code पढ़ो from metadata
 *
 * This can be called after usb4_port_reसमयr_nvm_authenticate() and
 * usb4_port_क्रमागतerate_reसमयrs() to fetch status of the NVM upgrade.
 *
 * Returns %0 अगर the authentication status was successfully पढ़ो. The
 * completion metadata (the result) is then stored पूर्णांकo @status. If
 * पढ़ोing the status fails, वापसs negative त्रुटि_सं.
 */
पूर्णांक usb4_port_reसमयr_nvm_authenticate_status(काष्ठा tb_port *port, u8 index,
					      u32 *status)
अणु
	u32 metadata, val;
	पूर्णांक ret;

	ret = usb4_port_reसमयr_पढ़ो(port, index, USB4_SB_OPCODE, &val,
				     माप(val));
	अगर (ret)
		वापस ret;

	चयन (val) अणु
	हाल 0:
		*status = 0;
		वापस 0;

	हाल USB4_SB_OPCODE_ERR:
		ret = usb4_port_reसमयr_पढ़ो(port, index, USB4_SB_METADATA,
					     &metadata, माप(metadata));
		अगर (ret)
			वापस ret;

		*status = metadata & USB4_SB_METADATA_NVM_AUTH_WRITE_MASK;
		वापस 0;

	हाल USB4_SB_OPCODE_ONS:
		वापस -EOPNOTSUPP;

	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक usb4_port_reसमयr_nvm_पढ़ो_block(व्योम *data, अचिन्हित पूर्णांक dwaddress,
					    व्योम *buf, माप_प्रकार dwords)
अणु
	स्थिर काष्ठा reसमयr_info *info = data;
	काष्ठा tb_port *port = info->port;
	u8 index = info->index;
	u32 metadata;
	पूर्णांक ret;

	metadata = dwaddress << USB4_NVM_READ_OFFSET_SHIFT;
	अगर (dwords < USB4_DATA_DWORDS)
		metadata |= dwords << USB4_NVM_READ_LENGTH_SHIFT;

	ret = usb4_port_reसमयr_ग_लिखो(port, index, USB4_SB_METADATA, &metadata,
				      माप(metadata));
	अगर (ret)
		वापस ret;

	ret = usb4_port_reसमयr_op(port, index, USB4_SB_OPCODE_NVM_READ, 500);
	अगर (ret)
		वापस ret;

	वापस usb4_port_reसमयr_पढ़ो(port, index, USB4_SB_DATA, buf,
				      dwords * 4);
पूर्ण

/**
 * usb4_port_reसमयr_nvm_पढ़ो() - Read contents of reसमयr NVM
 * @port: USB4 port
 * @index: Reसमयr index
 * @address: NVM address (in bytes) to start पढ़ोing
 * @buf: Data पढ़ो from NVM is stored here
 * @size: Number of bytes to पढ़ो
 *
 * Reads reसमयr NVM and copies the contents to @buf. Returns %0 अगर the
 * पढ़ो was successful and negative त्रुटि_सं in हाल of failure.
 * Specअगरically वापसs %-ENODEV अगर there is no reसमयr at @index.
 */
पूर्णांक usb4_port_reसमयr_nvm_पढ़ो(काष्ठा tb_port *port, u8 index,
			       अचिन्हित पूर्णांक address, व्योम *buf, माप_प्रकार size)
अणु
	काष्ठा reसमयr_info info = अणु .port = port, .index = index पूर्ण;

	वापस usb4_करो_पढ़ो_data(address, buf, size,
			usb4_port_reसमयr_nvm_पढ़ो_block, &info);
पूर्ण

/**
 * usb4_usb3_port_max_link_rate() - Maximum support USB3 link rate
 * @port: USB3 adapter port
 *
 * Return maximum supported link rate of a USB3 adapter in Mb/s.
 * Negative त्रुटि_सं in हाल of error.
 */
पूर्णांक usb4_usb3_port_max_link_rate(काष्ठा tb_port *port)
अणु
	पूर्णांक ret, lr;
	u32 val;

	अगर (!tb_port_is_usb3_करोwn(port) && !tb_port_is_usb3_up(port))
		वापस -EINVAL;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_adap + ADP_USB3_CS_4, 1);
	अगर (ret)
		वापस ret;

	lr = (val & ADP_USB3_CS_4_MSLR_MASK) >> ADP_USB3_CS_4_MSLR_SHIFT;
	वापस lr == ADP_USB3_CS_4_MSLR_20G ? 20000 : 10000;
पूर्ण

/**
 * usb4_usb3_port_actual_link_rate() - Established USB3 link rate
 * @port: USB3 adapter port
 *
 * Return actual established link rate of a USB3 adapter in Mb/s. If the
 * link is not up वापसs %0 and negative त्रुटि_सं in हाल of failure.
 */
पूर्णांक usb4_usb3_port_actual_link_rate(काष्ठा tb_port *port)
अणु
	पूर्णांक ret, lr;
	u32 val;

	अगर (!tb_port_is_usb3_करोwn(port) && !tb_port_is_usb3_up(port))
		वापस -EINVAL;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_adap + ADP_USB3_CS_4, 1);
	अगर (ret)
		वापस ret;

	अगर (!(val & ADP_USB3_CS_4_ULV))
		वापस 0;

	lr = val & ADP_USB3_CS_4_ALR_MASK;
	वापस lr == ADP_USB3_CS_4_ALR_20G ? 20000 : 10000;
पूर्ण

अटल पूर्णांक usb4_usb3_port_cm_request(काष्ठा tb_port *port, bool request)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (!tb_port_is_usb3_करोwn(port))
		वापस -EINVAL;
	अगर (tb_route(port->sw))
		वापस -EINVAL;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_adap + ADP_USB3_CS_2, 1);
	अगर (ret)
		वापस ret;

	अगर (request)
		val |= ADP_USB3_CS_2_CMR;
	अन्यथा
		val &= ~ADP_USB3_CS_2_CMR;

	ret = tb_port_ग_लिखो(port, &val, TB_CFG_PORT,
			    port->cap_adap + ADP_USB3_CS_2, 1);
	अगर (ret)
		वापस ret;

	/*
	 * We can use val here directly as the CMR bit is in the same place
	 * as HCA. Just mask out others.
	 */
	val &= ADP_USB3_CS_2_CMR;
	वापस usb4_port_रुको_क्रम_bit(port, port->cap_adap + ADP_USB3_CS_1,
				      ADP_USB3_CS_1_HCA, val, 1500);
पूर्ण

अटल अंतरभूत पूर्णांक usb4_usb3_port_set_cm_request(काष्ठा tb_port *port)
अणु
	वापस usb4_usb3_port_cm_request(port, true);
पूर्ण

अटल अंतरभूत पूर्णांक usb4_usb3_port_clear_cm_request(काष्ठा tb_port *port)
अणु
	वापस usb4_usb3_port_cm_request(port, false);
पूर्ण

अटल अचिन्हित पूर्णांक usb3_bw_to_mbps(u32 bw, u8 scale)
अणु
	अचिन्हित दीर्घ uframes;

	uframes = bw * 512UL << scale;
	वापस DIV_ROUND_CLOSEST(uframes * 8000, 1000 * 1000);
पूर्ण

अटल u32 mbps_to_usb3_bw(अचिन्हित पूर्णांक mbps, u8 scale)
अणु
	अचिन्हित दीर्घ uframes;

	/* 1 uframe is 1/8 ms (125 us) -> 1 / 8000 s */
	uframes = ((अचिन्हित दीर्घ)mbps * 1000 *  1000) / 8000;
	वापस DIV_ROUND_UP(uframes, 512UL << scale);
पूर्ण

अटल पूर्णांक usb4_usb3_port_पढ़ो_allocated_bandwidth(काष्ठा tb_port *port,
						   पूर्णांक *upstream_bw,
						   पूर्णांक *करोwnstream_bw)
अणु
	u32 val, bw, scale;
	पूर्णांक ret;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_adap + ADP_USB3_CS_2, 1);
	अगर (ret)
		वापस ret;

	ret = tb_port_पढ़ो(port, &scale, TB_CFG_PORT,
			   port->cap_adap + ADP_USB3_CS_3, 1);
	अगर (ret)
		वापस ret;

	scale &= ADP_USB3_CS_3_SCALE_MASK;

	bw = val & ADP_USB3_CS_2_AUBW_MASK;
	*upstream_bw = usb3_bw_to_mbps(bw, scale);

	bw = (val & ADP_USB3_CS_2_ADBW_MASK) >> ADP_USB3_CS_2_ADBW_SHIFT;
	*करोwnstream_bw = usb3_bw_to_mbps(bw, scale);

	वापस 0;
पूर्ण

/**
 * usb4_usb3_port_allocated_bandwidth() - Bandwidth allocated क्रम USB3
 * @port: USB3 adapter port
 * @upstream_bw: Allocated upstream bandwidth is stored here
 * @करोwnstream_bw: Allocated करोwnstream bandwidth is stored here
 *
 * Stores currently allocated USB3 bandwidth पूर्णांकo @upstream_bw and
 * @करोwnstream_bw in Mb/s. Returns %0 in हाल of success and negative
 * त्रुटि_सं in failure.
 */
पूर्णांक usb4_usb3_port_allocated_bandwidth(काष्ठा tb_port *port, पूर्णांक *upstream_bw,
				       पूर्णांक *करोwnstream_bw)
अणु
	पूर्णांक ret;

	ret = usb4_usb3_port_set_cm_request(port);
	अगर (ret)
		वापस ret;

	ret = usb4_usb3_port_पढ़ो_allocated_bandwidth(port, upstream_bw,
						      करोwnstream_bw);
	usb4_usb3_port_clear_cm_request(port);

	वापस ret;
पूर्ण

अटल पूर्णांक usb4_usb3_port_पढ़ो_consumed_bandwidth(काष्ठा tb_port *port,
						  पूर्णांक *upstream_bw,
						  पूर्णांक *करोwnstream_bw)
अणु
	u32 val, bw, scale;
	पूर्णांक ret;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_adap + ADP_USB3_CS_1, 1);
	अगर (ret)
		वापस ret;

	ret = tb_port_पढ़ो(port, &scale, TB_CFG_PORT,
			   port->cap_adap + ADP_USB3_CS_3, 1);
	अगर (ret)
		वापस ret;

	scale &= ADP_USB3_CS_3_SCALE_MASK;

	bw = val & ADP_USB3_CS_1_CUBW_MASK;
	*upstream_bw = usb3_bw_to_mbps(bw, scale);

	bw = (val & ADP_USB3_CS_1_CDBW_MASK) >> ADP_USB3_CS_1_CDBW_SHIFT;
	*करोwnstream_bw = usb3_bw_to_mbps(bw, scale);

	वापस 0;
पूर्ण

अटल पूर्णांक usb4_usb3_port_ग_लिखो_allocated_bandwidth(काष्ठा tb_port *port,
						    पूर्णांक upstream_bw,
						    पूर्णांक करोwnstream_bw)
अणु
	u32 val, ubw, dbw, scale;
	पूर्णांक ret;

	/* Read the used scale, hardware शेष is 0 */
	ret = tb_port_पढ़ो(port, &scale, TB_CFG_PORT,
			   port->cap_adap + ADP_USB3_CS_3, 1);
	अगर (ret)
		वापस ret;

	scale &= ADP_USB3_CS_3_SCALE_MASK;
	ubw = mbps_to_usb3_bw(upstream_bw, scale);
	dbw = mbps_to_usb3_bw(करोwnstream_bw, scale);

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_adap + ADP_USB3_CS_2, 1);
	अगर (ret)
		वापस ret;

	val &= ~(ADP_USB3_CS_2_AUBW_MASK | ADP_USB3_CS_2_ADBW_MASK);
	val |= dbw << ADP_USB3_CS_2_ADBW_SHIFT;
	val |= ubw;

	वापस tb_port_ग_लिखो(port, &val, TB_CFG_PORT,
			     port->cap_adap + ADP_USB3_CS_2, 1);
पूर्ण

/**
 * usb4_usb3_port_allocate_bandwidth() - Allocate bandwidth क्रम USB3
 * @port: USB3 adapter port
 * @upstream_bw: New upstream bandwidth
 * @करोwnstream_bw: New करोwnstream bandwidth
 *
 * This can be used to set how much bandwidth is allocated क्रम the USB3
 * tunneled isochronous traffic. @upstream_bw and @करोwnstream_bw are the
 * new values programmed to the USB3 adapter allocation रेजिस्टरs. If
 * the values are lower than what is currently consumed the allocation
 * is set to what is currently consumed instead (consumed bandwidth
 * cannot be taken away by CM). The actual new values are वापसed in
 * @upstream_bw and @करोwnstream_bw.
 *
 * Returns %0 in हाल of success and negative त्रुटि_सं अगर there was a
 * failure.
 */
पूर्णांक usb4_usb3_port_allocate_bandwidth(काष्ठा tb_port *port, पूर्णांक *upstream_bw,
				      पूर्णांक *करोwnstream_bw)
अणु
	पूर्णांक ret, consumed_up, consumed_करोwn, allocate_up, allocate_करोwn;

	ret = usb4_usb3_port_set_cm_request(port);
	अगर (ret)
		वापस ret;

	ret = usb4_usb3_port_पढ़ो_consumed_bandwidth(port, &consumed_up,
						     &consumed_करोwn);
	अगर (ret)
		जाओ err_request;

	/* Don't allow it go lower than what is consumed */
	allocate_up = max(*upstream_bw, consumed_up);
	allocate_करोwn = max(*करोwnstream_bw, consumed_करोwn);

	ret = usb4_usb3_port_ग_लिखो_allocated_bandwidth(port, allocate_up,
						       allocate_करोwn);
	अगर (ret)
		जाओ err_request;

	*upstream_bw = allocate_up;
	*करोwnstream_bw = allocate_करोwn;

err_request:
	usb4_usb3_port_clear_cm_request(port);
	वापस ret;
पूर्ण

/**
 * usb4_usb3_port_release_bandwidth() - Release allocated USB3 bandwidth
 * @port: USB3 adapter port
 * @upstream_bw: New allocated upstream bandwidth
 * @करोwnstream_bw: New allocated करोwnstream bandwidth
 *
 * Releases USB3 allocated bandwidth करोwn to what is actually consumed.
 * The new bandwidth is वापसed in @upstream_bw and @करोwnstream_bw.
 *
 * Returns 0% in success and negative त्रुटि_सं in हाल of failure.
 */
पूर्णांक usb4_usb3_port_release_bandwidth(काष्ठा tb_port *port, पूर्णांक *upstream_bw,
				     पूर्णांक *करोwnstream_bw)
अणु
	पूर्णांक ret, consumed_up, consumed_करोwn;

	ret = usb4_usb3_port_set_cm_request(port);
	अगर (ret)
		वापस ret;

	ret = usb4_usb3_port_पढ़ो_consumed_bandwidth(port, &consumed_up,
						     &consumed_करोwn);
	अगर (ret)
		जाओ err_request;

	/*
	 * Always keep 1000 Mb/s to make sure xHCI has at least some
	 * bandwidth available क्रम isochronous traffic.
	 */
	अगर (consumed_up < 1000)
		consumed_up = 1000;
	अगर (consumed_करोwn < 1000)
		consumed_करोwn = 1000;

	ret = usb4_usb3_port_ग_लिखो_allocated_bandwidth(port, consumed_up,
						       consumed_करोwn);
	अगर (ret)
		जाओ err_request;

	*upstream_bw = consumed_up;
	*करोwnstream_bw = consumed_करोwn;

err_request:
	usb4_usb3_port_clear_cm_request(port);
	वापस ret;
पूर्ण
