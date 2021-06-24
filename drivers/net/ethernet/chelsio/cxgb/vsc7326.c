<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* $Date: 2006/04/28 19:20:06 $ $RCSfile: vsc7326.c,v $ $Revision: 1.19 $ */

/* Driver क्रम Vitesse VSC7326 (Schaumburg) MAC */

#समावेश "gmac.h"
#समावेश "elmer0.h"
#समावेश "vsc7326_reg.h"

/* Update fast changing statistics every 15 seconds */
#घोषणा STATS_TICK_SECS 15
/* 30 minutes क्रम full statistics update */
#घोषणा MAJOR_UPDATE_TICKS (1800 / STATS_TICK_SECS)

/* The egress WM value 0x01a01fff should be used only when the
 * पूर्णांकerface is करोwn (MAC port disabled). This is a workaround
 * क्रम disabling the T2/MAC flow-control. When the पूर्णांकerface is
 * enabled, the WM value should be set to 0x014a03F0.
 */
#घोषणा WM_DISABLE	0x01a01fff
#घोषणा WM_ENABLE	0x014a03F0

काष्ठा init_table अणु
	u32 addr;
	u32 data;
पूर्ण;

काष्ठा _cmac_instance अणु
	u32 index;
	u32 ticks;
पूर्ण;

#घोषणा INITBLOCK_SLEEP	0xffffffff

अटल व्योम vsc_पढ़ो(adapter_t *adapter, u32 addr, u32 *val)
अणु
	u32 status, vlo, vhi;
	पूर्णांक i;

	spin_lock_bh(&adapter->mac_lock);
	t1_tpi_पढ़ो(adapter, (addr << 2) + 4, &vlo);
	i = 0;
	करो अणु
		t1_tpi_पढ़ो(adapter, (REG_LOCAL_STATUS << 2) + 4, &vlo);
		t1_tpi_पढ़ो(adapter, REG_LOCAL_STATUS << 2, &vhi);
		status = (vhi << 16) | vlo;
		i++;
	पूर्ण जबतक (((status & 1) == 0) && (i < 50));
	अगर (i == 50)
		pr_err("Invalid tpi read from MAC, breaking loop.\n");

	t1_tpi_पढ़ो(adapter, (REG_LOCAL_DATA << 2) + 4, &vlo);
	t1_tpi_पढ़ो(adapter, REG_LOCAL_DATA << 2, &vhi);

	*val = (vhi << 16) | vlo;

	/* pr_err("rd: block: 0x%x  sublock: 0x%x  reg: 0x%x  data: 0x%x\n",
		((addr&0xe000)>>13), ((addr&0x1e00)>>9),
		((addr&0x01fe)>>1), *val); */
	spin_unlock_bh(&adapter->mac_lock);
पूर्ण

अटल व्योम vsc_ग_लिखो(adapter_t *adapter, u32 addr, u32 data)
अणु
	spin_lock_bh(&adapter->mac_lock);
	t1_tpi_ग_लिखो(adapter, (addr << 2) + 4, data & 0xFFFF);
	t1_tpi_ग_लिखो(adapter, addr << 2, (data >> 16) & 0xFFFF);
	/* pr_err("wr: block: 0x%x  sublock: 0x%x  reg: 0x%x  data: 0x%x\n",
		((addr&0xe000)>>13), ((addr&0x1e00)>>9),
		((addr&0x01fe)>>1), data); */
	spin_unlock_bh(&adapter->mac_lock);
पूर्ण

/* Hard reset the MAC.  This wipes out *all* configuration. */
अटल व्योम vsc7326_full_reset(adapter_t* adapter)
अणु
	u32 val;
	u32 result = 0xffff;

	t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val &= ~1;
	t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	udelay(2);
	val |= 0x1;	/* Enable mac MAC itself */
	val |= 0x800;	/* Turn off the red LED */
	t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	mdelay(1);
	vsc_ग_लिखो(adapter, REG_SW_RESET, 0x80000001);
	करो अणु
		mdelay(1);
		vsc_पढ़ो(adapter, REG_SW_RESET, &result);
	पूर्ण जबतक (result != 0x0);
पूर्ण

अटल काष्ठा init_table vsc7326_reset[] = अणु
	अणु      REG_IFACE_MODE, 0x00000000 पूर्ण,
	अणु         REG_CRC_CFG, 0x00000020 पूर्ण,
	अणु   REG_PLL_CLK_SPEED, 0x00050c00 पूर्ण,
	अणु   REG_PLL_CLK_SPEED, 0x00050c00 पूर्ण,
	अणु            REG_MSCH, 0x00002f14 पूर्ण,
	अणु       REG_SPI4_MISC, 0x00040409 पूर्ण,
	अणु     REG_SPI4_DESKEW, 0x00080000 पूर्ण,
	अणु REG_SPI4_ING_SETUP2, 0x08080004 पूर्ण,
	अणु REG_SPI4_ING_SETUP0, 0x04111004 पूर्ण,
	अणु REG_SPI4_EGR_SETUP0, 0x80001a04 पूर्ण,
	अणु REG_SPI4_ING_SETUP1, 0x02010000 पूर्ण,
	अणु      REG_AGE_INC(0), 0x00000000 पूर्ण,
	अणु      REG_AGE_INC(1), 0x00000000 पूर्ण,
	अणु     REG_ING_CONTROL, 0x0a200011 पूर्ण,
	अणु     REG_EGR_CONTROL, 0xa0010091 पूर्ण,
पूर्ण;

अटल काष्ठा init_table vsc7326_portinit[4][22] = अणु
	अणु	/* Port 0 */
			/* FIFO setup */
		अणु           REG_DBG(0), 0x000004f0 पूर्ण,
		अणु           REG_HDX(0), 0x00073101 पूर्ण,
		अणु        REG_TEST(0,0), 0x00000022 पूर्ण,
		अणु        REG_TEST(1,0), 0x00000022 पूर्ण,
		अणु  REG_TOP_BOTTOM(0,0), 0x003f0000 पूर्ण,
		अणु  REG_TOP_BOTTOM(1,0), 0x00120000 पूर्ण,
		अणु REG_HIGH_LOW_WM(0,0), 0x07460757 पूर्ण,
		अणु REG_HIGH_LOW_WM(1,0), WM_DISABLE पूर्ण,
		अणु   REG_CT_THRHLD(0,0), 0x00000000 पूर्ण,
		अणु   REG_CT_THRHLD(1,0), 0x00000000 पूर्ण,
		अणु         REG_BUCKE(0), 0x0002ffff पूर्ण,
		अणु         REG_BUCKI(0), 0x0002ffff पूर्ण,
		अणु        REG_TEST(0,0), 0x00000020 पूर्ण,
		अणु        REG_TEST(1,0), 0x00000020 पूर्ण,
			/* Port config */
		अणु       REG_MAX_LEN(0), 0x00002710 पूर्ण,
		अणु     REG_PORT_FAIL(0), 0x00000002 पूर्ण,
		अणु    REG_NORMALIZER(0), 0x00000a64 पूर्ण,
		अणु        REG_DENORM(0), 0x00000010 पूर्ण,
		अणु     REG_STICK_BIT(0), 0x03baa370 पूर्ण,
		अणु     REG_DEV_SETUP(0), 0x00000083 पूर्ण,
		अणु     REG_DEV_SETUP(0), 0x00000082 पूर्ण,
		अणु      REG_MODE_CFG(0), 0x0200259f पूर्ण,
	पूर्ण,
	अणु	/* Port 1 */
			/* FIFO setup */
		अणु           REG_DBG(1), 0x000004f0 पूर्ण,
		अणु           REG_HDX(1), 0x00073101 पूर्ण,
		अणु        REG_TEST(0,1), 0x00000022 पूर्ण,
		अणु        REG_TEST(1,1), 0x00000022 पूर्ण,
		अणु  REG_TOP_BOTTOM(0,1), 0x007e003f पूर्ण,
		अणु  REG_TOP_BOTTOM(1,1), 0x00240012 पूर्ण,
		अणु REG_HIGH_LOW_WM(0,1), 0x07460757 पूर्ण,
		अणु REG_HIGH_LOW_WM(1,1), WM_DISABLE पूर्ण,
		अणु   REG_CT_THRHLD(0,1), 0x00000000 पूर्ण,
		अणु   REG_CT_THRHLD(1,1), 0x00000000 पूर्ण,
		अणु         REG_BUCKE(1), 0x0002ffff पूर्ण,
		अणु         REG_BUCKI(1), 0x0002ffff पूर्ण,
		अणु        REG_TEST(0,1), 0x00000020 पूर्ण,
		अणु        REG_TEST(1,1), 0x00000020 पूर्ण,
			/* Port config */
		अणु       REG_MAX_LEN(1), 0x00002710 पूर्ण,
		अणु     REG_PORT_FAIL(1), 0x00000002 पूर्ण,
		अणु    REG_NORMALIZER(1), 0x00000a64 पूर्ण,
		अणु        REG_DENORM(1), 0x00000010 पूर्ण,
		अणु     REG_STICK_BIT(1), 0x03baa370 पूर्ण,
		अणु     REG_DEV_SETUP(1), 0x00000083 पूर्ण,
		अणु     REG_DEV_SETUP(1), 0x00000082 पूर्ण,
		अणु      REG_MODE_CFG(1), 0x0200259f पूर्ण,
	पूर्ण,
	अणु	/* Port 2 */
			/* FIFO setup */
		अणु           REG_DBG(2), 0x000004f0 पूर्ण,
		अणु           REG_HDX(2), 0x00073101 पूर्ण,
		अणु        REG_TEST(0,2), 0x00000022 पूर्ण,
		अणु        REG_TEST(1,2), 0x00000022 पूर्ण,
		अणु  REG_TOP_BOTTOM(0,2), 0x00bd007e पूर्ण,
		अणु  REG_TOP_BOTTOM(1,2), 0x00360024 पूर्ण,
		अणु REG_HIGH_LOW_WM(0,2), 0x07460757 पूर्ण,
		अणु REG_HIGH_LOW_WM(1,2), WM_DISABLE पूर्ण,
		अणु   REG_CT_THRHLD(0,2), 0x00000000 पूर्ण,
		अणु   REG_CT_THRHLD(1,2), 0x00000000 पूर्ण,
		अणु         REG_BUCKE(2), 0x0002ffff पूर्ण,
		अणु         REG_BUCKI(2), 0x0002ffff पूर्ण,
		अणु        REG_TEST(0,2), 0x00000020 पूर्ण,
		अणु        REG_TEST(1,2), 0x00000020 पूर्ण,
			/* Port config */
		अणु       REG_MAX_LEN(2), 0x00002710 पूर्ण,
		अणु     REG_PORT_FAIL(2), 0x00000002 पूर्ण,
		अणु    REG_NORMALIZER(2), 0x00000a64 पूर्ण,
		अणु        REG_DENORM(2), 0x00000010 पूर्ण,
		अणु     REG_STICK_BIT(2), 0x03baa370 पूर्ण,
		अणु     REG_DEV_SETUP(2), 0x00000083 पूर्ण,
		अणु     REG_DEV_SETUP(2), 0x00000082 पूर्ण,
		अणु      REG_MODE_CFG(2), 0x0200259f पूर्ण,
	पूर्ण,
	अणु	/* Port 3 */
			/* FIFO setup */
		अणु           REG_DBG(3), 0x000004f0 पूर्ण,
		अणु           REG_HDX(3), 0x00073101 पूर्ण,
		अणु        REG_TEST(0,3), 0x00000022 पूर्ण,
		अणु        REG_TEST(1,3), 0x00000022 पूर्ण,
		अणु  REG_TOP_BOTTOM(0,3), 0x00fc00bd पूर्ण,
		अणु  REG_TOP_BOTTOM(1,3), 0x00480036 पूर्ण,
		अणु REG_HIGH_LOW_WM(0,3), 0x07460757 पूर्ण,
		अणु REG_HIGH_LOW_WM(1,3), WM_DISABLE पूर्ण,
		अणु   REG_CT_THRHLD(0,3), 0x00000000 पूर्ण,
		अणु   REG_CT_THRHLD(1,3), 0x00000000 पूर्ण,
		अणु         REG_BUCKE(3), 0x0002ffff पूर्ण,
		अणु         REG_BUCKI(3), 0x0002ffff पूर्ण,
		अणु        REG_TEST(0,3), 0x00000020 पूर्ण,
		अणु        REG_TEST(1,3), 0x00000020 पूर्ण,
			/* Port config */
		अणु       REG_MAX_LEN(3), 0x00002710 पूर्ण,
		अणु     REG_PORT_FAIL(3), 0x00000002 पूर्ण,
		अणु    REG_NORMALIZER(3), 0x00000a64 पूर्ण,
		अणु        REG_DENORM(3), 0x00000010 पूर्ण,
		अणु     REG_STICK_BIT(3), 0x03baa370 पूर्ण,
		अणु     REG_DEV_SETUP(3), 0x00000083 पूर्ण,
		अणु     REG_DEV_SETUP(3), 0x00000082 पूर्ण,
		अणु      REG_MODE_CFG(3), 0x0200259f पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम run_table(adapter_t *adapter, काष्ठा init_table *ib, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (ib[i].addr == INITBLOCK_SLEEP) अणु
			udelay( ib[i].data );
			pr_err("sleep %d us\n",ib[i].data);
		पूर्ण अन्यथा
			vsc_ग_लिखो( adapter, ib[i].addr, ib[i].data );
	पूर्ण
पूर्ण

अटल पूर्णांक bist_rd(adapter_t *adapter, पूर्णांक moduleid, पूर्णांक address)
अणु
	पूर्णांक data = 0;
	u32 result = 0;

	अगर ((address != 0x0) &&
	    (address != 0x1) &&
	    (address != 0x2) &&
	    (address != 0xd) &&
	    (address != 0xe))
			pr_err("No bist address: 0x%x\n", address);

	data = ((0x00 << 24) | ((address & 0xff) << 16) | (0x00 << 8) |
		((moduleid & 0xff) << 0));
	vsc_ग_लिखो(adapter, REG_RAM_BIST_CMD, data);

	udelay(10);

	vsc_पढ़ो(adapter, REG_RAM_BIST_RESULT, &result);
	अगर ((result & (1 << 9)) != 0x0)
		pr_err("Still in bist read: 0x%x\n", result);
	अन्यथा अगर ((result & (1 << 8)) != 0x0)
		pr_err("bist read error: 0x%x\n", result);

	वापस result & 0xff;
पूर्ण

अटल पूर्णांक bist_wr(adapter_t *adapter, पूर्णांक moduleid, पूर्णांक address, पूर्णांक value)
अणु
	पूर्णांक data = 0;
	u32 result = 0;

	अगर ((address != 0x0) &&
	    (address != 0x1) &&
	    (address != 0x2) &&
	    (address != 0xd) &&
	    (address != 0xe))
			pr_err("No bist address: 0x%x\n", address);

	अगर (value > 255)
		pr_err("Suspicious write out of range value: 0x%x\n", value);

	data = ((0x01 << 24) | ((address & 0xff) << 16) | (value << 8) |
		((moduleid & 0xff) << 0));
	vsc_ग_लिखो(adapter, REG_RAM_BIST_CMD, data);

	udelay(5);

	vsc_पढ़ो(adapter, REG_RAM_BIST_CMD, &result);
	अगर ((result & (1 << 27)) != 0x0)
		pr_err("Still in bist write: 0x%x\n", result);
	अन्यथा अगर ((result & (1 << 26)) != 0x0)
		pr_err("bist write error: 0x%x\n", result);

	वापस 0;
पूर्ण

अटल पूर्णांक run_bist(adapter_t *adapter, पूर्णांक moduleid)
अणु
	/*run bist*/
	(व्योम) bist_wr(adapter,moduleid, 0x00, 0x02);
	(व्योम) bist_wr(adapter,moduleid, 0x01, 0x01);

	वापस 0;
पूर्ण

अटल पूर्णांक check_bist(adapter_t *adapter, पूर्णांक moduleid)
अणु
	पूर्णांक result=0;
	पूर्णांक column=0;
	/*check bist*/
	result = bist_rd(adapter,moduleid, 0x02);
	column = ((bist_rd(adapter,moduleid, 0x0e)<<8) +
			(bist_rd(adapter,moduleid, 0x0d)));
	अगर ((result & 3) != 0x3)
		pr_err("Result: 0x%x  BIST error in ram %d, column: 0x%04x\n",
			result, moduleid, column);
	वापस 0;
पूर्ण

अटल पूर्णांक enable_mem(adapter_t *adapter, पूर्णांक moduleid)
अणु
	/*enable mem*/
	(व्योम) bist_wr(adapter,moduleid, 0x00, 0x00);
	वापस 0;
पूर्ण

अटल पूर्णांक run_bist_all(adapter_t *adapter)
अणु
	पूर्णांक port = 0;
	u32 val = 0;

	vsc_ग_लिखो(adapter, REG_MEM_BIST, 0x5);
	vsc_पढ़ो(adapter, REG_MEM_BIST, &val);

	क्रम (port = 0; port < 12; port++)
		vsc_ग_लिखो(adapter, REG_DEV_SETUP(port), 0x0);

	udelay(300);
	vsc_ग_लिखो(adapter, REG_SPI4_MISC, 0x00040409);
	udelay(300);

	(व्योम) run_bist(adapter,13);
	(व्योम) run_bist(adapter,14);
	(व्योम) run_bist(adapter,20);
	(व्योम) run_bist(adapter,21);
	mdelay(200);
	(व्योम) check_bist(adapter,13);
	(व्योम) check_bist(adapter,14);
	(व्योम) check_bist(adapter,20);
	(व्योम) check_bist(adapter,21);
	udelay(100);
	(व्योम) enable_mem(adapter,13);
	(व्योम) enable_mem(adapter,14);
	(व्योम) enable_mem(adapter,20);
	(व्योम) enable_mem(adapter,21);
	udelay(300);
	vsc_ग_लिखो(adapter, REG_SPI4_MISC, 0x60040400);
	udelay(300);
	क्रम (port = 0; port < 12; port++)
		vsc_ग_लिखो(adapter, REG_DEV_SETUP(port), 0x1);

	udelay(300);
	vsc_ग_लिखो(adapter, REG_MEM_BIST, 0x0);
	mdelay(10);
	वापस 0;
पूर्ण

अटल पूर्णांक mac_पूर्णांकr_handler(काष्ठा cmac *mac)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mac_पूर्णांकr_enable(काष्ठा cmac *mac)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mac_पूर्णांकr_disable(काष्ठा cmac *mac)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mac_पूर्णांकr_clear(काष्ठा cmac *mac)
अणु
	वापस 0;
पूर्ण

/* Expect MAC address to be in network byte order. */
अटल पूर्णांक mac_set_address(काष्ठा cmac* mac, u8 addr[6])
अणु
	u32 val;
	पूर्णांक port = mac->instance->index;

	vsc_ग_लिखो(mac->adapter, REG_MAC_LOW_ADDR(port),
		  (addr[3] << 16) | (addr[4] << 8) | addr[5]);
	vsc_ग_लिखो(mac->adapter, REG_MAC_HIGH_ADDR(port),
		  (addr[0] << 16) | (addr[1] << 8) | addr[2]);

	vsc_पढ़ो(mac->adapter, REG_ING_FFILT_UM_EN, &val);
	val &= ~0xf0000000;
	vsc_ग_लिखो(mac->adapter, REG_ING_FFILT_UM_EN, val | (port << 28));

	vsc_ग_लिखो(mac->adapter, REG_ING_FFILT_MASK0,
		  0xffff0000 | (addr[4] << 8) | addr[5]);
	vsc_ग_लिखो(mac->adapter, REG_ING_FFILT_MASK1,
		  0xffff0000 | (addr[2] << 8) | addr[3]);
	vsc_ग_लिखो(mac->adapter, REG_ING_FFILT_MASK2,
		  0xffff0000 | (addr[0] << 8) | addr[1]);
	वापस 0;
पूर्ण

अटल पूर्णांक mac_get_address(काष्ठा cmac *mac, u8 addr[6])
अणु
	u32 addr_lo, addr_hi;
	पूर्णांक port = mac->instance->index;

	vsc_पढ़ो(mac->adapter, REG_MAC_LOW_ADDR(port), &addr_lo);
	vsc_पढ़ो(mac->adapter, REG_MAC_HIGH_ADDR(port), &addr_hi);

	addr[0] = (u8) (addr_hi >> 16);
	addr[1] = (u8) (addr_hi >> 8);
	addr[2] = (u8) addr_hi;
	addr[3] = (u8) (addr_lo >> 16);
	addr[4] = (u8) (addr_lo >> 8);
	addr[5] = (u8) addr_lo;
	वापस 0;
पूर्ण

/* This is पूर्णांकended to reset a port, not the whole MAC */
अटल पूर्णांक mac_reset(काष्ठा cmac *mac)
अणु
	पूर्णांक index = mac->instance->index;

	run_table(mac->adapter, vsc7326_portinit[index],
		  ARRAY_SIZE(vsc7326_portinit[index]));

	वापस 0;
पूर्ण

अटल पूर्णांक mac_set_rx_mode(काष्ठा cmac *mac, काष्ठा t1_rx_mode *rm)
अणु
	u32 v;
	पूर्णांक port = mac->instance->index;

	vsc_पढ़ो(mac->adapter, REG_ING_FFILT_UM_EN, &v);
	v |= 1 << 12;

	अगर (t1_rx_mode_promisc(rm))
		v &= ~(1 << (port + 16));
	अन्यथा
		v |= 1 << (port + 16);

	vsc_ग_लिखो(mac->adapter, REG_ING_FFILT_UM_EN, v);
	वापस 0;
पूर्ण

अटल पूर्णांक mac_set_mtu(काष्ठा cmac *mac, पूर्णांक mtu)
अणु
	पूर्णांक port = mac->instance->index;

	/* max_len includes header and FCS */
	vsc_ग_लिखो(mac->adapter, REG_MAX_LEN(port), mtu + 14 + 4);
	वापस 0;
पूर्ण

अटल पूर्णांक mac_set_speed_duplex_fc(काष्ठा cmac *mac, पूर्णांक speed, पूर्णांक duplex,
				   पूर्णांक fc)
अणु
	u32 v;
	पूर्णांक enable, port = mac->instance->index;

	अगर (speed >= 0 && speed != SPEED_10 && speed != SPEED_100 &&
	    speed != SPEED_1000)
		वापस -1;
	अगर (duplex > 0 && duplex != DUPLEX_FULL)
		वापस -1;

	अगर (speed >= 0) अणु
		vsc_पढ़ो(mac->adapter, REG_MODE_CFG(port), &v);
		enable = v & 3;             /* save tx/rx enables */
		v &= ~0xf;
		v |= 4;                     /* full duplex */
		अगर (speed == SPEED_1000)
			v |= 8;             /* GigE */
		enable |= v;
		vsc_ग_लिखो(mac->adapter, REG_MODE_CFG(port), v);

		अगर (speed == SPEED_1000)
			v = 0x82;
		अन्यथा अगर (speed == SPEED_100)
			v = 0x84;
		अन्यथा	/* SPEED_10 */
			v = 0x86;
		vsc_ग_लिखो(mac->adapter, REG_DEV_SETUP(port), v | 1); /* reset */
		vsc_ग_लिखो(mac->adapter, REG_DEV_SETUP(port), v);
		vsc_पढ़ो(mac->adapter, REG_DBG(port), &v);
		v &= ~0xff00;
		अगर (speed == SPEED_1000)
			v |= 0x400;
		अन्यथा अगर (speed == SPEED_100)
			v |= 0x2000;
		अन्यथा	/* SPEED_10 */
			v |= 0xff00;
		vsc_ग_लिखो(mac->adapter, REG_DBG(port), v);

		vsc_ग_लिखो(mac->adapter, REG_TX_IFG(port),
			  speed == SPEED_1000 ? 5 : 0x11);
		अगर (duplex == DUPLEX_HALF)
			enable = 0x0;	/* 100 or 10 */
		अन्यथा अगर (speed == SPEED_1000)
			enable = 0xc;
		अन्यथा	/* SPEED_100 or 10 */
			enable = 0x4;
		enable |= 0x9 << 10;	/* IFG1 */
		enable |= 0x6 << 6;	/* IFG2 */
		enable |= 0x1 << 4;	/* VLAN */
		enable |= 0x3;		/* RX/TX EN */
		vsc_ग_लिखो(mac->adapter, REG_MODE_CFG(port), enable);

	पूर्ण

	vsc_पढ़ो(mac->adapter, REG_PAUSE_CFG(port), &v);
	v &= 0xfff0ffff;
	v |= 0x20000;      /* xon/xoff */
	अगर (fc & PAUSE_RX)
		v |= 0x40000;
	अगर (fc & PAUSE_TX)
		v |= 0x80000;
	अगर (fc == (PAUSE_RX | PAUSE_TX))
		v |= 0x10000;
	vsc_ग_लिखो(mac->adapter, REG_PAUSE_CFG(port), v);
	वापस 0;
पूर्ण

अटल पूर्णांक mac_enable(काष्ठा cmac *mac, पूर्णांक which)
अणु
	u32 val;
	पूर्णांक port = mac->instance->index;

	/* Write the correct WM value when the port is enabled. */
	vsc_ग_लिखो(mac->adapter, REG_HIGH_LOW_WM(1,port), WM_ENABLE);

	vsc_पढ़ो(mac->adapter, REG_MODE_CFG(port), &val);
	अगर (which & MAC_सूचीECTION_RX)
		val |= 0x2;
	अगर (which & MAC_सूचीECTION_TX)
		val |= 1;
	vsc_ग_लिखो(mac->adapter, REG_MODE_CFG(port), val);
	वापस 0;
पूर्ण

अटल पूर्णांक mac_disable(काष्ठा cmac *mac, पूर्णांक which)
अणु
	u32 val;
	पूर्णांक i, port = mac->instance->index;

	/* Reset the port, this also ग_लिखोs the correct WM value */
	mac_reset(mac);

	vsc_पढ़ो(mac->adapter, REG_MODE_CFG(port), &val);
	अगर (which & MAC_सूचीECTION_RX)
		val &= ~0x2;
	अगर (which & MAC_सूचीECTION_TX)
		val &= ~0x1;
	vsc_ग_लिखो(mac->adapter, REG_MODE_CFG(port), val);
	vsc_पढ़ो(mac->adapter, REG_MODE_CFG(port), &val);

	/* Clear stats */
	क्रम (i = 0; i <= 0x3a; ++i)
		vsc_ग_लिखो(mac->adapter, CRA(4, port, i), 0);

	/* Clear software counters */
	स_रखो(&mac->stats, 0, माप(काष्ठा cmac_statistics));

	वापस 0;
पूर्ण

अटल व्योम rmon_update(काष्ठा cmac *mac, अचिन्हित पूर्णांक addr, u64 *stat)
अणु
	u32 v, lo;

	vsc_पढ़ो(mac->adapter, addr, &v);
	lo = *stat;
	*stat = *stat - lo + v;

	अगर (v == 0)
		वापस;

	अगर (v < lo)
		*stat += (1ULL << 32);
पूर्ण

अटल व्योम port_stats_update(काष्ठा cmac *mac)
अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक reg;
		अचिन्हित पूर्णांक offset;
	पूर्ण hw_stats[] = अणु

#घोषणा HW_STAT(reg, stat_name) \
	अणु reg, (&((काष्ठा cmac_statistics *)शून्य)->stat_name) - (u64 *)शून्य पूर्ण

		/* Rx stats */
		HW_STAT(RxUnicast, RxUnicastFramesOK),
		HW_STAT(RxMulticast, RxMulticastFramesOK),
		HW_STAT(RxBroadcast, RxBroadcastFramesOK),
		HW_STAT(Crc, RxFCSErrors),
		HW_STAT(RxAlignment, RxAlignErrors),
		HW_STAT(RxOversize, RxFrameTooLongErrors),
		HW_STAT(RxPause, RxPauseFrames),
		HW_STAT(RxJabbers, RxJabberErrors),
		HW_STAT(RxFragments, RxRuntErrors),
		HW_STAT(RxUndersize, RxRuntErrors),
		HW_STAT(RxSymbolCarrier, RxSymbolErrors),
		HW_STAT(RxSize1519ToMax, RxJumboFramesOK),

		/* Tx stats (skip collision stats as we are full-duplex only) */
		HW_STAT(TxUnicast, TxUnicastFramesOK),
		HW_STAT(TxMulticast, TxMulticastFramesOK),
		HW_STAT(TxBroadcast, TxBroadcastFramesOK),
		HW_STAT(TxPause, TxPauseFrames),
		HW_STAT(TxUnderrun, TxUnderrun),
		HW_STAT(TxSize1519ToMax, TxJumboFramesOK),
	पूर्ण, *p = hw_stats;
	अचिन्हित पूर्णांक port = mac->instance->index;
	u64 *stats = (u64 *)&mac->stats;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hw_stats); i++)
		rmon_update(mac, CRA(0x4, port, p->reg), stats + p->offset);

	rmon_update(mac, REG_TX_OK_BYTES(port), &mac->stats.TxOctetsOK);
	rmon_update(mac, REG_RX_OK_BYTES(port), &mac->stats.RxOctetsOK);
	rmon_update(mac, REG_RX_BAD_BYTES(port), &mac->stats.RxOctetsBad);
पूर्ण

/*
 * This function is called periodically to accumulate the current values of the
 * RMON counters पूर्णांकo the port statistics.  Since the counters are only 32 bits
 * some of them can overflow in less than a minute at GigE speeds, so this
 * function should be called every 30 seconds or so.
 *
 * To cut करोwn on पढ़ोing costs we update only the octet counters at each tick
 * and करो a full update at major ticks, which can be every 30 minutes or more.
 */
अटल स्थिर काष्ठा cmac_statistics *mac_update_statistics(काष्ठा cmac *mac,
							   पूर्णांक flag)
अणु
	अगर (flag == MAC_STATS_UPDATE_FULL ||
	    mac->instance->ticks >= MAJOR_UPDATE_TICKS) अणु
		port_stats_update(mac);
		mac->instance->ticks = 0;
	पूर्ण अन्यथा अणु
		पूर्णांक port = mac->instance->index;

		rmon_update(mac, REG_RX_OK_BYTES(port),
			    &mac->stats.RxOctetsOK);
		rmon_update(mac, REG_RX_BAD_BYTES(port),
			    &mac->stats.RxOctetsBad);
		rmon_update(mac, REG_TX_OK_BYTES(port),
			    &mac->stats.TxOctetsOK);
		mac->instance->ticks++;
	पूर्ण
	वापस &mac->stats;
पूर्ण

अटल व्योम mac_destroy(काष्ठा cmac *mac)
अणु
	kमुक्त(mac);
पूर्ण

अटल स्थिर काष्ठा cmac_ops vsc7326_ops = अणु
	.destroy                  = mac_destroy,
	.reset                    = mac_reset,
	.पूर्णांकerrupt_handler        = mac_पूर्णांकr_handler,
	.पूर्णांकerrupt_enable         = mac_पूर्णांकr_enable,
	.पूर्णांकerrupt_disable        = mac_पूर्णांकr_disable,
	.पूर्णांकerrupt_clear          = mac_पूर्णांकr_clear,
	.enable                   = mac_enable,
	.disable                  = mac_disable,
	.set_mtu                  = mac_set_mtu,
	.set_rx_mode              = mac_set_rx_mode,
	.set_speed_duplex_fc      = mac_set_speed_duplex_fc,
	.statistics_update        = mac_update_statistics,
	.macaddress_get           = mac_get_address,
	.macaddress_set           = mac_set_address,
पूर्ण;

अटल काष्ठा cmac *vsc7326_mac_create(adapter_t *adapter, पूर्णांक index)
अणु
	काष्ठा cmac *mac;
	u32 val;
	पूर्णांक i;

	mac = kzalloc(माप(*mac) + माप(cmac_instance), GFP_KERNEL);
	अगर (!mac)
		वापस शून्य;

	mac->ops = &vsc7326_ops;
	mac->instance = (cmac_instance *)(mac + 1);
	mac->adapter  = adapter;

	mac->instance->index = index;
	mac->instance->ticks = 0;

	i = 0;
	करो अणु
		u32 vhi, vlo;

		vhi = vlo = 0;
		t1_tpi_पढ़ो(adapter, (REG_LOCAL_STATUS << 2) + 4, &vlo);
		udelay(1);
		t1_tpi_पढ़ो(adapter, REG_LOCAL_STATUS << 2, &vhi);
		udelay(5);
		val = (vhi << 16) | vlo;
	पूर्ण जबतक ((++i < 10000) && (val == 0xffffffff));

	वापस mac;
पूर्ण

अटल पूर्णांक vsc7326_mac_reset(adapter_t *adapter)
अणु
	vsc7326_full_reset(adapter);
	(व्योम) run_bist_all(adapter);
	run_table(adapter, vsc7326_reset, ARRAY_SIZE(vsc7326_reset));
	वापस 0;
पूर्ण

स्थिर काष्ठा gmac t1_vsc7326_ops = अणु
	.stats_update_period = STATS_TICK_SECS,
	.create              = vsc7326_mac_create,
	.reset               = vsc7326_mac_reset,
पूर्ण;
