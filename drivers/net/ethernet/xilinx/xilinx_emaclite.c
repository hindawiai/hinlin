<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Xilinx EmacLite Linux driver क्रम the Xilinx Ethernet MAC Lite device.
 *
 * This is a new flat driver which is based on the original emac_lite
 * driver from John Williams <john.williams@xilinx.com>.
 *
 * 2007 - 2013 (c) Xilinx, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>

#घोषणा DRIVER_NAME "xilinx_emaclite"

/* Register offsets क्रम the EmacLite Core */
#घोषणा XEL_TXBUFF_OFFSET	0x0		/* Transmit Buffer */
#घोषणा XEL_MDIOADDR_OFFSET	0x07E4		/* MDIO Address Register */
#घोषणा XEL_MDIOWR_OFFSET	0x07E8		/* MDIO Write Data Register */
#घोषणा XEL_MDIORD_OFFSET	0x07EC		/* MDIO Read Data Register */
#घोषणा XEL_MDIOCTRL_OFFSET	0x07F0		/* MDIO Control Register */
#घोषणा XEL_GIER_OFFSET		0x07F8		/* GIE Register */
#घोषणा XEL_TSR_OFFSET		0x07FC		/* Tx status */
#घोषणा XEL_TPLR_OFFSET		0x07F4		/* Tx packet length */

#घोषणा XEL_RXBUFF_OFFSET	0x1000		/* Receive Buffer */
#घोषणा XEL_RPLR_OFFSET		0x100C		/* Rx packet length */
#घोषणा XEL_RSR_OFFSET		0x17FC		/* Rx status */

#घोषणा XEL_BUFFER_OFFSET	0x0800		/* Next Tx/Rx buffer's offset */

/* MDIO Address Register Bit Masks */
#घोषणा XEL_MDIOADDR_REGADR_MASK  0x0000001F	/* Register Address */
#घोषणा XEL_MDIOADDR_PHYADR_MASK  0x000003E0	/* PHY Address */
#घोषणा XEL_MDIOADDR_PHYADR_SHIFT 5
#घोषणा XEL_MDIOADDR_OP_MASK	  0x00000400	/* RD/WR Operation */

/* MDIO Write Data Register Bit Masks */
#घोषणा XEL_MDIOWR_WRDATA_MASK	  0x0000FFFF	/* Data to be Written */

/* MDIO Read Data Register Bit Masks */
#घोषणा XEL_MDIORD_RDDATA_MASK	  0x0000FFFF	/* Data to be Read */

/* MDIO Control Register Bit Masks */
#घोषणा XEL_MDIOCTRL_MDIOSTS_MASK 0x00000001	/* MDIO Status Mask */
#घोषणा XEL_MDIOCTRL_MDIOEN_MASK  0x00000008	/* MDIO Enable */

/* Global Interrupt Enable Register (GIER) Bit Masks */
#घोषणा XEL_GIER_GIE_MASK	0x80000000	/* Global Enable */

/* Transmit Status Register (TSR) Bit Masks */
#घोषणा XEL_TSR_XMIT_BUSY_MASK	 0x00000001	/* Tx complete */
#घोषणा XEL_TSR_PROGRAM_MASK	 0x00000002	/* Program the MAC address */
#घोषणा XEL_TSR_XMIT_IE_MASK	 0x00000008	/* Tx पूर्णांकerrupt enable bit */
#घोषणा XEL_TSR_XMIT_ACTIVE_MASK 0x80000000	/* Buffer is active, SW bit
						 * only. This is not करोcumented
						 * in the HW spec
						 */

/* Define क्रम programming the MAC address पूर्णांकo the EmacLite */
#घोषणा XEL_TSR_PROG_MAC_ADDR	(XEL_TSR_XMIT_BUSY_MASK | XEL_TSR_PROGRAM_MASK)

/* Receive Status Register (RSR) */
#घोषणा XEL_RSR_RECV_DONE_MASK	0x00000001	/* Rx complete */
#घोषणा XEL_RSR_RECV_IE_MASK	0x00000008	/* Rx पूर्णांकerrupt enable bit */

/* Transmit Packet Length Register (TPLR) */
#घोषणा XEL_TPLR_LENGTH_MASK	0x0000FFFF	/* Tx packet length */

/* Receive Packet Length Register (RPLR) */
#घोषणा XEL_RPLR_LENGTH_MASK	0x0000FFFF	/* Rx packet length */

#घोषणा XEL_HEADER_OFFSET	12		/* Offset to length field */
#घोषणा XEL_HEADER_SHIFT	16		/* Shअगरt value क्रम length */

/* General Ethernet Definitions */
#घोषणा XEL_ARP_PACKET_SIZE		28	/* Max ARP packet size */
#घोषणा XEL_HEADER_IP_LENGTH_OFFSET	16	/* IP Length Offset */



#घोषणा TX_TIMEOUT		(60 * HZ)	/* Tx समयout is 60 seconds. */
#घोषणा ALIGNMENT		4

/* BUFFER_ALIGN(adr) calculates the number of bytes to the next alignment. */
#घोषणा BUFFER_ALIGN(adr) ((ALIGNMENT - ((uपूर्णांकptr_t)adr)) % ALIGNMENT)

#अगर_घोषित __BIG_ENDIAN
#घोषणा xemaclite_पढ़ोl		ioपढ़ो32be
#घोषणा xemaclite_ग_लिखोl	ioग_लिखो32be
#अन्यथा
#घोषणा xemaclite_पढ़ोl		ioपढ़ो32
#घोषणा xemaclite_ग_लिखोl	ioग_लिखो32
#पूर्ण_अगर

/**
 * काष्ठा net_local - Our निजी per device data
 * @ndev:		instance of the network device
 * @tx_ping_pong:	indicates whether Tx Pong buffer is configured in HW
 * @rx_ping_pong:	indicates whether Rx Pong buffer is configured in HW
 * @next_tx_buf_to_use:	next Tx buffer to ग_लिखो to
 * @next_rx_buf_to_use:	next Rx buffer to पढ़ो from
 * @base_addr:		base address of the Emaclite device
 * @reset_lock:		lock used क्रम synchronization
 * @deferred_skb:	holds an skb (क्रम transmission at a later समय) when the
 *			Tx buffer is not मुक्त
 * @phy_dev:		poपूर्णांकer to the PHY device
 * @phy_node:		poपूर्णांकer to the PHY device node
 * @mii_bus:		poपूर्णांकer to the MII bus
 * @last_link:		last link status
 */
काष्ठा net_local अणु

	काष्ठा net_device *ndev;

	bool tx_ping_pong;
	bool rx_ping_pong;
	u32 next_tx_buf_to_use;
	u32 next_rx_buf_to_use;
	व्योम __iomem *base_addr;

	spinlock_t reset_lock;
	काष्ठा sk_buff *deferred_skb;

	काष्ठा phy_device *phy_dev;
	काष्ठा device_node *phy_node;

	काष्ठा mii_bus *mii_bus;

	पूर्णांक last_link;
पूर्ण;


/*************************/
/* EmacLite driver calls */
/*************************/

/**
 * xemaclite_enable_पूर्णांकerrupts - Enable the पूर्णांकerrupts क्रम the EmacLite device
 * @drvdata:	Poपूर्णांकer to the Emaclite device निजी data
 *
 * This function enables the Tx and Rx पूर्णांकerrupts क्रम the Emaclite device aदीर्घ
 * with the Global Interrupt Enable.
 */
अटल व्योम xemaclite_enable_पूर्णांकerrupts(काष्ठा net_local *drvdata)
अणु
	u32 reg_data;

	/* Enable the Tx पूर्णांकerrupts क्रम the first Buffer */
	reg_data = xemaclite_पढ़ोl(drvdata->base_addr + XEL_TSR_OFFSET);
	xemaclite_ग_लिखोl(reg_data | XEL_TSR_XMIT_IE_MASK,
			 drvdata->base_addr + XEL_TSR_OFFSET);

	/* Enable the Rx पूर्णांकerrupts क्रम the first buffer */
	xemaclite_ग_लिखोl(XEL_RSR_RECV_IE_MASK, drvdata->base_addr + XEL_RSR_OFFSET);

	/* Enable the Global Interrupt Enable */
	xemaclite_ग_लिखोl(XEL_GIER_GIE_MASK, drvdata->base_addr + XEL_GIER_OFFSET);
पूर्ण

/**
 * xemaclite_disable_पूर्णांकerrupts - Disable the पूर्णांकerrupts क्रम the EmacLite device
 * @drvdata:	Poपूर्णांकer to the Emaclite device निजी data
 *
 * This function disables the Tx and Rx पूर्णांकerrupts क्रम the Emaclite device,
 * aदीर्घ with the Global Interrupt Enable.
 */
अटल व्योम xemaclite_disable_पूर्णांकerrupts(काष्ठा net_local *drvdata)
अणु
	u32 reg_data;

	/* Disable the Global Interrupt Enable */
	xemaclite_ग_लिखोl(XEL_GIER_GIE_MASK, drvdata->base_addr + XEL_GIER_OFFSET);

	/* Disable the Tx पूर्णांकerrupts क्रम the first buffer */
	reg_data = xemaclite_पढ़ोl(drvdata->base_addr + XEL_TSR_OFFSET);
	xemaclite_ग_लिखोl(reg_data & (~XEL_TSR_XMIT_IE_MASK),
			 drvdata->base_addr + XEL_TSR_OFFSET);

	/* Disable the Rx पूर्णांकerrupts क्रम the first buffer */
	reg_data = xemaclite_पढ़ोl(drvdata->base_addr + XEL_RSR_OFFSET);
	xemaclite_ग_लिखोl(reg_data & (~XEL_RSR_RECV_IE_MASK),
			 drvdata->base_addr + XEL_RSR_OFFSET);
पूर्ण

/**
 * xemaclite_aligned_ग_लिखो - Write from 16-bit aligned to 32-bit aligned address
 * @src_ptr:	Void poपूर्णांकer to the 16-bit aligned source address
 * @dest_ptr:	Poपूर्णांकer to the 32-bit aligned destination address
 * @length:	Number bytes to ग_लिखो from source to destination
 *
 * This function ग_लिखोs data from a 16-bit aligned buffer to a 32-bit aligned
 * address in the EmacLite device.
 */
अटल व्योम xemaclite_aligned_ग_लिखो(व्योम *src_ptr, u32 *dest_ptr,
				    अचिन्हित length)
अणु
	u32 align_buffer;
	u32 *to_u32_ptr;
	u16 *from_u16_ptr, *to_u16_ptr;

	to_u32_ptr = dest_ptr;
	from_u16_ptr = src_ptr;
	align_buffer = 0;

	क्रम (; length > 3; length -= 4) अणु
		to_u16_ptr = (u16 *)&align_buffer;
		*to_u16_ptr++ = *from_u16_ptr++;
		*to_u16_ptr++ = *from_u16_ptr++;

		/* This barrier resolves occasional issues seen around
		 * हालs where the data is not properly flushed out
		 * from the processor store buffers to the destination
		 * memory locations.
		 */
		wmb();

		/* Output a word */
		*to_u32_ptr++ = align_buffer;
	पूर्ण
	अगर (length) अणु
		u8 *from_u8_ptr, *to_u8_ptr;

		/* Set up to output the reमुख्यing data */
		align_buffer = 0;
		to_u8_ptr = (u8 *)&align_buffer;
		from_u8_ptr = (u8 *)from_u16_ptr;

		/* Output the reमुख्यing data */
		क्रम (; length > 0; length--)
			*to_u8_ptr++ = *from_u8_ptr++;

		/* This barrier resolves occasional issues seen around
		 * हालs where the data is not properly flushed out
		 * from the processor store buffers to the destination
		 * memory locations.
		 */
		wmb();
		*to_u32_ptr = align_buffer;
	पूर्ण
पूर्ण

/**
 * xemaclite_aligned_पढ़ो - Read from 32-bit aligned to 16-bit aligned buffer
 * @src_ptr:	Poपूर्णांकer to the 32-bit aligned source address
 * @dest_ptr:	Poपूर्णांकer to the 16-bit aligned destination address
 * @length:	Number bytes to पढ़ो from source to destination
 *
 * This function पढ़ोs data from a 32-bit aligned address in the EmacLite device
 * to a 16-bit aligned buffer.
 */
अटल व्योम xemaclite_aligned_पढ़ो(u32 *src_ptr, u8 *dest_ptr,
				   अचिन्हित length)
अणु
	u16 *to_u16_ptr, *from_u16_ptr;
	u32 *from_u32_ptr;
	u32 align_buffer;

	from_u32_ptr = src_ptr;
	to_u16_ptr = (u16 *)dest_ptr;

	क्रम (; length > 3; length -= 4) अणु
		/* Copy each word पूर्णांकo the temporary buffer */
		align_buffer = *from_u32_ptr++;
		from_u16_ptr = (u16 *)&align_buffer;

		/* Read data from source */
		*to_u16_ptr++ = *from_u16_ptr++;
		*to_u16_ptr++ = *from_u16_ptr++;
	पूर्ण

	अगर (length) अणु
		u8 *to_u8_ptr, *from_u8_ptr;

		/* Set up to पढ़ो the reमुख्यing data */
		to_u8_ptr = (u8 *)to_u16_ptr;
		align_buffer = *from_u32_ptr++;
		from_u8_ptr = (u8 *)&align_buffer;

		/* Read the reमुख्यing data */
		क्रम (; length > 0; length--)
			*to_u8_ptr = *from_u8_ptr;
	पूर्ण
पूर्ण

/**
 * xemaclite_send_data - Send an Ethernet frame
 * @drvdata:	Poपूर्णांकer to the Emaclite device निजी data
 * @data:	Poपूर्णांकer to the data to be sent
 * @byte_count:	Total frame size, including header
 *
 * This function checks अगर the Tx buffer of the Emaclite device is मुक्त to send
 * data. If so, it fills the Tx buffer with data क्रम transmission. Otherwise, it
 * वापसs an error.
 *
 * Return:	0 upon success or -1 अगर the buffer(s) are full.
 *
 * Note:	The maximum Tx packet size can not be more than Ethernet header
 *		(14 Bytes) + Maximum MTU (1500 bytes). This is excluding FCS.
 */
अटल पूर्णांक xemaclite_send_data(काष्ठा net_local *drvdata, u8 *data,
			       अचिन्हित पूर्णांक byte_count)
अणु
	u32 reg_data;
	व्योम __iomem *addr;

	/* Determine the expected Tx buffer address */
	addr = drvdata->base_addr + drvdata->next_tx_buf_to_use;

	/* If the length is too large, truncate it */
	अगर (byte_count > ETH_FRAME_LEN)
		byte_count = ETH_FRAME_LEN;

	/* Check अगर the expected buffer is available */
	reg_data = xemaclite_पढ़ोl(addr + XEL_TSR_OFFSET);
	अगर ((reg_data & (XEL_TSR_XMIT_BUSY_MASK |
	     XEL_TSR_XMIT_ACTIVE_MASK)) == 0) अणु

		/* Switch to next buffer अगर configured */
		अगर (drvdata->tx_ping_pong != 0)
			drvdata->next_tx_buf_to_use ^= XEL_BUFFER_OFFSET;
	पूर्ण अन्यथा अगर (drvdata->tx_ping_pong != 0) अणु
		/* If the expected buffer is full, try the other buffer,
		 * अगर it is configured in HW
		 */

		addr = (व्योम __iomem __क्रमce *)((uपूर्णांकptr_t __क्रमce)addr ^
						 XEL_BUFFER_OFFSET);
		reg_data = xemaclite_पढ़ोl(addr + XEL_TSR_OFFSET);

		अगर ((reg_data & (XEL_TSR_XMIT_BUSY_MASK |
		     XEL_TSR_XMIT_ACTIVE_MASK)) != 0)
			वापस -1; /* Buffers were full, वापस failure */
	पूर्ण अन्यथा
		वापस -1; /* Buffer was full, वापस failure */

	/* Write the frame to the buffer */
	xemaclite_aligned_ग_लिखो(data, (u32 __क्रमce *)addr, byte_count);

	xemaclite_ग_लिखोl((byte_count & XEL_TPLR_LENGTH_MASK),
			 addr + XEL_TPLR_OFFSET);

	/* Update the Tx Status Register to indicate that there is a
	 * frame to send. Set the XEL_TSR_XMIT_ACTIVE_MASK flag which
	 * is used by the पूर्णांकerrupt handler to check whether a frame
	 * has been transmitted
	 */
	reg_data = xemaclite_पढ़ोl(addr + XEL_TSR_OFFSET);
	reg_data |= (XEL_TSR_XMIT_BUSY_MASK | XEL_TSR_XMIT_ACTIVE_MASK);
	xemaclite_ग_लिखोl(reg_data, addr + XEL_TSR_OFFSET);

	वापस 0;
पूर्ण

/**
 * xemaclite_recv_data - Receive a frame
 * @drvdata:	Poपूर्णांकer to the Emaclite device निजी data
 * @data:	Address where the data is to be received
 * @maxlen:    Maximum supported ethernet packet length
 *
 * This function is पूर्णांकended to be called from the पूर्णांकerrupt context or
 * with a wrapper which रुकोs क्रम the receive frame to be available.
 *
 * Return:	Total number of bytes received
 */
अटल u16 xemaclite_recv_data(काष्ठा net_local *drvdata, u8 *data, पूर्णांक maxlen)
अणु
	व्योम __iomem *addr;
	u16 length, proto_type;
	u32 reg_data;

	/* Determine the expected buffer address */
	addr = (drvdata->base_addr + drvdata->next_rx_buf_to_use);

	/* Verअगरy which buffer has valid data */
	reg_data = xemaclite_पढ़ोl(addr + XEL_RSR_OFFSET);

	अगर ((reg_data & XEL_RSR_RECV_DONE_MASK) == XEL_RSR_RECV_DONE_MASK) अणु
		अगर (drvdata->rx_ping_pong != 0)
			drvdata->next_rx_buf_to_use ^= XEL_BUFFER_OFFSET;
	पूर्ण अन्यथा अणु
		/* The instance is out of sync, try other buffer अगर other
		 * buffer is configured, वापस 0 otherwise. If the instance is
		 * out of sync, करो not update the 'next_rx_buf_to_use' since it
		 * will correct on subsequent calls
		 */
		अगर (drvdata->rx_ping_pong != 0)
			addr = (व्योम __iomem __क्रमce *)
				((uपूर्णांकptr_t __क्रमce)addr ^
				 XEL_BUFFER_OFFSET);
		अन्यथा
			वापस 0;	/* No data was available */

		/* Verअगरy that buffer has valid data */
		reg_data = xemaclite_पढ़ोl(addr + XEL_RSR_OFFSET);
		अगर ((reg_data & XEL_RSR_RECV_DONE_MASK) !=
		     XEL_RSR_RECV_DONE_MASK)
			वापस 0;	/* No data was available */
	पूर्ण

	/* Get the protocol type of the ethernet frame that arrived
	 */
	proto_type = ((ntohl(xemaclite_पढ़ोl(addr + XEL_HEADER_OFFSET +
			XEL_RXBUFF_OFFSET)) >> XEL_HEADER_SHIFT) &
			XEL_RPLR_LENGTH_MASK);

	/* Check अगर received ethernet frame is a raw ethernet frame
	 * or an IP packet or an ARP packet
	 */
	अगर (proto_type > ETH_DATA_LEN) अणु

		अगर (proto_type == ETH_P_IP) अणु
			length = ((ntohl(xemaclite_पढ़ोl(addr +
					XEL_HEADER_IP_LENGTH_OFFSET +
					XEL_RXBUFF_OFFSET)) >>
					XEL_HEADER_SHIFT) &
					XEL_RPLR_LENGTH_MASK);
			length = min_t(u16, length, ETH_DATA_LEN);
			length += ETH_HLEN + ETH_FCS_LEN;

		पूर्ण अन्यथा अगर (proto_type == ETH_P_ARP)
			length = XEL_ARP_PACKET_SIZE + ETH_HLEN + ETH_FCS_LEN;
		अन्यथा
			/* Field contains type other than IP or ARP, use max
			 * frame size and let user parse it
			 */
			length = ETH_FRAME_LEN + ETH_FCS_LEN;
	पूर्ण अन्यथा
		/* Use the length in the frame, plus the header and trailer */
		length = proto_type + ETH_HLEN + ETH_FCS_LEN;

	अगर (WARN_ON(length > maxlen))
		length = maxlen;

	/* Read from the EmacLite device */
	xemaclite_aligned_पढ़ो((u32 __क्रमce *)(addr + XEL_RXBUFF_OFFSET),
				data, length);

	/* Acknowledge the frame */
	reg_data = xemaclite_पढ़ोl(addr + XEL_RSR_OFFSET);
	reg_data &= ~XEL_RSR_RECV_DONE_MASK;
	xemaclite_ग_लिखोl(reg_data, addr + XEL_RSR_OFFSET);

	वापस length;
पूर्ण

/**
 * xemaclite_update_address - Update the MAC address in the device
 * @drvdata:	Poपूर्णांकer to the Emaclite device निजी data
 * @address_ptr:Poपूर्णांकer to the MAC address (MAC address is a 48-bit value)
 *
 * Tx must be idle and Rx should be idle क्रम deterministic results.
 * It is recommended that this function should be called after the
 * initialization and beक्रमe transmission of any packets from the device.
 * The MAC address can be programmed using any of the two transmit
 * buffers (अगर configured).
 */
अटल व्योम xemaclite_update_address(काष्ठा net_local *drvdata,
				     u8 *address_ptr)
अणु
	व्योम __iomem *addr;
	u32 reg_data;

	/* Determine the expected Tx buffer address */
	addr = drvdata->base_addr + drvdata->next_tx_buf_to_use;

	xemaclite_aligned_ग_लिखो(address_ptr, (u32 __क्रमce *)addr, ETH_ALEN);

	xemaclite_ग_लिखोl(ETH_ALEN, addr + XEL_TPLR_OFFSET);

	/* Update the MAC address in the EmacLite */
	reg_data = xemaclite_पढ़ोl(addr + XEL_TSR_OFFSET);
	xemaclite_ग_लिखोl(reg_data | XEL_TSR_PROG_MAC_ADDR, addr + XEL_TSR_OFFSET);

	/* Wait क्रम EmacLite to finish with the MAC address update */
	जबतक ((xemaclite_पढ़ोl(addr + XEL_TSR_OFFSET) &
		XEL_TSR_PROG_MAC_ADDR) != 0)
		;
पूर्ण

/**
 * xemaclite_set_mac_address - Set the MAC address क्रम this device
 * @dev:	Poपूर्णांकer to the network device instance
 * @address:	Void poपूर्णांकer to the sockaddr काष्ठाure
 *
 * This function copies the HW address from the sockaddr strucutre to the
 * net_device काष्ठाure and updates the address in HW.
 *
 * Return:	Error अगर the net device is busy or 0 अगर the addr is set
 *		successfully
 */
अटल पूर्णांक xemaclite_set_mac_address(काष्ठा net_device *dev, व्योम *address)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	काष्ठा sockaddr *addr = address;

	अगर (netअगर_running(dev))
		वापस -EBUSY;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	xemaclite_update_address(lp, dev->dev_addr);
	वापस 0;
पूर्ण

/**
 * xemaclite_tx_समयout - Callback क्रम Tx Timeout
 * @dev:	Poपूर्णांकer to the network device
 * @txqueue:	Unused
 *
 * This function is called when Tx समय out occurs क्रम Emaclite device.
 */
अटल व्योम xemaclite_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	dev_err(&lp->ndev->dev, "Exceeded transmit timeout of %lu ms\n",
		TX_TIMEOUT * 1000UL / HZ);

	dev->stats.tx_errors++;

	/* Reset the device */
	spin_lock_irqsave(&lp->reset_lock, flags);

	/* Shouldn't really be necessary, but shouldn't hurt */
	netअगर_stop_queue(dev);

	xemaclite_disable_पूर्णांकerrupts(lp);
	xemaclite_enable_पूर्णांकerrupts(lp);

	अगर (lp->deferred_skb) अणु
		dev_kमुक्त_skb(lp->deferred_skb);
		lp->deferred_skb = शून्य;
		dev->stats.tx_errors++;
	पूर्ण

	/* To exclude tx समयout */
	netअगर_trans_update(dev); /* prevent tx समयout */

	/* We're all पढ़ोy to go. Start the queue */
	netअगर_wake_queue(dev);
	spin_unlock_irqrestore(&lp->reset_lock, flags);
पूर्ण

/**********************/
/* Interrupt Handlers */
/**********************/

/**
 * xemaclite_tx_handler - Interrupt handler क्रम frames sent
 * @dev:	Poपूर्णांकer to the network device
 *
 * This function updates the number of packets transmitted and handles the
 * deferred skb, अगर there is one.
 */
अटल व्योम xemaclite_tx_handler(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);

	dev->stats.tx_packets++;

	अगर (!lp->deferred_skb)
		वापस;

	अगर (xemaclite_send_data(lp, (u8 *)lp->deferred_skb->data,
				lp->deferred_skb->len))
		वापस;

	dev->stats.tx_bytes += lp->deferred_skb->len;
	dev_consume_skb_irq(lp->deferred_skb);
	lp->deferred_skb = शून्य;
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);
पूर्ण

/**
 * xemaclite_rx_handler- Interrupt handler क्रम frames received
 * @dev:	Poपूर्णांकer to the network device
 *
 * This function allocates memory क्रम a socket buffer, fills it with data
 * received and hands it over to the TCP/IP stack.
 */
अटल व्योम xemaclite_rx_handler(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक align;
	u32 len;

	len = ETH_FRAME_LEN + ETH_FCS_LEN;
	skb = netdev_alloc_skb(dev, len + ALIGNMENT);
	अगर (!skb) अणु
		/* Couldn't get memory. */
		dev->stats.rx_dropped++;
		dev_err(&lp->ndev->dev, "Could not allocate receive buffer\n");
		वापस;
	पूर्ण

	/* A new skb should have the data halfword aligned, but this code is
	 * here just in हाल that isn't true. Calculate how many
	 * bytes we should reserve to get the data to start on a word
	 * boundary
	 */
	align = BUFFER_ALIGN(skb->data);
	अगर (align)
		skb_reserve(skb, align);

	skb_reserve(skb, 2);

	len = xemaclite_recv_data(lp, (u8 *)skb->data, len);

	अगर (!len) अणु
		dev->stats.rx_errors++;
		dev_kमुक्त_skb_irq(skb);
		वापस;
	पूर्ण

	skb_put(skb, len);	/* Tell the skb how much data we got */

	skb->protocol = eth_type_trans(skb, dev);
	skb_checksum_none_निश्चित(skb);

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;

	अगर (!skb_defer_rx_बारtamp(skb))
		netअगर_rx(skb);	/* Send the packet upstream */
पूर्ण

/**
 * xemaclite_पूर्णांकerrupt - Interrupt handler क्रम this driver
 * @irq:	Irq of the Emaclite device
 * @dev_id:	Void poपूर्णांकer to the network device instance used as callback
 *		reference
 *
 * Return:	IRQ_HANDLED
 *
 * This function handles the Tx and Rx पूर्णांकerrupts of the EmacLite device.
 */
अटल irqवापस_t xemaclite_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	bool tx_complete = false;
	काष्ठा net_device *dev = dev_id;
	काष्ठा net_local *lp = netdev_priv(dev);
	व्योम __iomem *base_addr = lp->base_addr;
	u32 tx_status;

	/* Check अगर there is Rx Data available */
	अगर ((xemaclite_पढ़ोl(base_addr + XEL_RSR_OFFSET) &
			 XEL_RSR_RECV_DONE_MASK) ||
	    (xemaclite_पढ़ोl(base_addr + XEL_BUFFER_OFFSET + XEL_RSR_OFFSET)
			 & XEL_RSR_RECV_DONE_MASK))

		xemaclite_rx_handler(dev);

	/* Check अगर the Transmission क्रम the first buffer is completed */
	tx_status = xemaclite_पढ़ोl(base_addr + XEL_TSR_OFFSET);
	अगर (((tx_status & XEL_TSR_XMIT_BUSY_MASK) == 0) &&
		(tx_status & XEL_TSR_XMIT_ACTIVE_MASK) != 0) अणु

		tx_status &= ~XEL_TSR_XMIT_ACTIVE_MASK;
		xemaclite_ग_लिखोl(tx_status, base_addr + XEL_TSR_OFFSET);

		tx_complete = true;
	पूर्ण

	/* Check अगर the Transmission क्रम the second buffer is completed */
	tx_status = xemaclite_पढ़ोl(base_addr + XEL_BUFFER_OFFSET + XEL_TSR_OFFSET);
	अगर (((tx_status & XEL_TSR_XMIT_BUSY_MASK) == 0) &&
		(tx_status & XEL_TSR_XMIT_ACTIVE_MASK) != 0) अणु

		tx_status &= ~XEL_TSR_XMIT_ACTIVE_MASK;
		xemaclite_ग_लिखोl(tx_status, base_addr + XEL_BUFFER_OFFSET +
				 XEL_TSR_OFFSET);

		tx_complete = true;
	पूर्ण

	/* If there was a Tx पूर्णांकerrupt, call the Tx Handler */
	अगर (tx_complete != 0)
		xemaclite_tx_handler(dev);

	वापस IRQ_HANDLED;
पूर्ण

/**********************/
/* MDIO Bus functions */
/**********************/

/**
 * xemaclite_mdio_रुको - Wait क्रम the MDIO to be पढ़ोy to use
 * @lp:		Poपूर्णांकer to the Emaclite device निजी data
 *
 * This function रुकोs till the device is पढ़ोy to accept a new MDIO
 * request.
 *
 * Return:	0 क्रम success or ETIMEDOUT क्रम a समयout
 */

अटल पूर्णांक xemaclite_mdio_रुको(काष्ठा net_local *lp)
अणु
	u32 val;

	/* रुको क्रम the MDIO पूर्णांकerface to not be busy or समयout
	 * after some समय.
	 */
	वापस पढ़ोx_poll_समयout(xemaclite_पढ़ोl,
				  lp->base_addr + XEL_MDIOCTRL_OFFSET,
				  val, !(val & XEL_MDIOCTRL_MDIOSTS_MASK),
				  1000, 20000);
पूर्ण

/**
 * xemaclite_mdio_पढ़ो - Read from a given MII management रेजिस्टर
 * @bus:	the mii_bus काष्ठा
 * @phy_id:	the phy address
 * @reg:	रेजिस्टर number to पढ़ो from
 *
 * This function रुकोs till the device is पढ़ोy to accept a new MDIO
 * request and then ग_लिखोs the phy address to the MDIO Address रेजिस्टर
 * and पढ़ोs data from MDIO Read Data रेजिस्टर, when its available.
 *
 * Return:	Value पढ़ो from the MII management रेजिस्टर
 */
अटल पूर्णांक xemaclite_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा net_local *lp = bus->priv;
	u32 ctrl_reg;
	u32 rc;

	अगर (xemaclite_mdio_रुको(lp))
		वापस -ETIMEDOUT;

	/* Write the PHY address, रेजिस्टर number and set the OP bit in the
	 * MDIO Address रेजिस्टर. Set the Status bit in the MDIO Control
	 * रेजिस्टर to start a MDIO पढ़ो transaction.
	 */
	ctrl_reg = xemaclite_पढ़ोl(lp->base_addr + XEL_MDIOCTRL_OFFSET);
	xemaclite_ग_लिखोl(XEL_MDIOADDR_OP_MASK |
			 ((phy_id << XEL_MDIOADDR_PHYADR_SHIFT) | reg),
			 lp->base_addr + XEL_MDIOADDR_OFFSET);
	xemaclite_ग_लिखोl(ctrl_reg | XEL_MDIOCTRL_MDIOSTS_MASK,
			 lp->base_addr + XEL_MDIOCTRL_OFFSET);

	अगर (xemaclite_mdio_रुको(lp))
		वापस -ETIMEDOUT;

	rc = xemaclite_पढ़ोl(lp->base_addr + XEL_MDIORD_OFFSET);

	dev_dbg(&lp->ndev->dev,
		"%s(phy_id=%i, reg=%x) == %x\n", __func__,
		phy_id, reg, rc);

	वापस rc;
पूर्ण

/**
 * xemaclite_mdio_ग_लिखो - Write to a given MII management रेजिस्टर
 * @bus:	the mii_bus काष्ठा
 * @phy_id:	the phy address
 * @reg:	रेजिस्टर number to ग_लिखो to
 * @val:	value to ग_लिखो to the रेजिस्टर number specअगरied by reg
 *
 * This function रुकोs till the device is पढ़ोy to accept a new MDIO
 * request and then ग_लिखोs the val to the MDIO Write Data रेजिस्टर.
 *
 * Return:      0 upon success or a negative error upon failure
 */
अटल पूर्णांक xemaclite_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg,
				u16 val)
अणु
	काष्ठा net_local *lp = bus->priv;
	u32 ctrl_reg;

	dev_dbg(&lp->ndev->dev,
		"%s(phy_id=%i, reg=%x, val=%x)\n", __func__,
		phy_id, reg, val);

	अगर (xemaclite_mdio_रुको(lp))
		वापस -ETIMEDOUT;

	/* Write the PHY address, रेजिस्टर number and clear the OP bit in the
	 * MDIO Address रेजिस्टर and then ग_लिखो the value पूर्णांकo the MDIO Write
	 * Data रेजिस्टर. Finally, set the Status bit in the MDIO Control
	 * रेजिस्टर to start a MDIO ग_लिखो transaction.
	 */
	ctrl_reg = xemaclite_पढ़ोl(lp->base_addr + XEL_MDIOCTRL_OFFSET);
	xemaclite_ग_लिखोl(~XEL_MDIOADDR_OP_MASK &
			 ((phy_id << XEL_MDIOADDR_PHYADR_SHIFT) | reg),
			 lp->base_addr + XEL_MDIOADDR_OFFSET);
	xemaclite_ग_लिखोl(val, lp->base_addr + XEL_MDIOWR_OFFSET);
	xemaclite_ग_लिखोl(ctrl_reg | XEL_MDIOCTRL_MDIOSTS_MASK,
			 lp->base_addr + XEL_MDIOCTRL_OFFSET);

	वापस 0;
पूर्ण

/**
 * xemaclite_mdio_setup - Register mii_bus क्रम the Emaclite device
 * @lp:		Poपूर्णांकer to the Emaclite device निजी data
 * @dev:	Poपूर्णांकer to OF device काष्ठाure
 *
 * This function enables MDIO bus in the Emaclite device and रेजिस्टरs a
 * mii_bus.
 *
 * Return:	0 upon success or a negative error upon failure
 */
अटल पूर्णांक xemaclite_mdio_setup(काष्ठा net_local *lp, काष्ठा device *dev)
अणु
	काष्ठा mii_bus *bus;
	पूर्णांक rc;
	काष्ठा resource res;
	काष्ठा device_node *np = of_get_parent(lp->phy_node);
	काष्ठा device_node *npp;

	/* Don't रेजिस्टर the MDIO bus अगर the phy_node or its parent node
	 * can't be found.
	 */
	अगर (!np) अणु
		dev_err(dev, "Failed to register mdio bus.\n");
		वापस -ENODEV;
	पूर्ण
	npp = of_get_parent(np);

	of_address_to_resource(npp, 0, &res);
	अगर (lp->ndev->mem_start != res.start) अणु
		काष्ठा phy_device *phydev;
		phydev = of_phy_find_device(lp->phy_node);
		अगर (!phydev)
			dev_info(dev,
				 "MDIO of the phy is not registered yet\n");
		अन्यथा
			put_device(&phydev->mdio.dev);
		वापस 0;
	पूर्ण

	/* Enable the MDIO bus by निश्चितing the enable bit in MDIO Control
	 * रेजिस्टर.
	 */
	xemaclite_ग_लिखोl(XEL_MDIOCTRL_MDIOEN_MASK,
			 lp->base_addr + XEL_MDIOCTRL_OFFSET);

	bus = mdiobus_alloc();
	अगर (!bus) अणु
		dev_err(dev, "Failed to allocate mdiobus\n");
		वापस -ENOMEM;
	पूर्ण

	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%.8llx",
		 (अचिन्हित दीर्घ दीर्घ)res.start);
	bus->priv = lp;
	bus->name = "Xilinx Emaclite MDIO";
	bus->पढ़ो = xemaclite_mdio_पढ़ो;
	bus->ग_लिखो = xemaclite_mdio_ग_लिखो;
	bus->parent = dev;

	rc = of_mdiobus_रेजिस्टर(bus, np);
	अगर (rc) अणु
		dev_err(dev, "Failed to register mdio bus.\n");
		जाओ err_रेजिस्टर;
	पूर्ण

	lp->mii_bus = bus;

	वापस 0;

err_रेजिस्टर:
	mdiobus_मुक्त(bus);
	वापस rc;
पूर्ण

/**
 * xemaclite_adjust_link - Link state callback क्रम the Emaclite device
 * @ndev: poपूर्णांकer to net_device काष्ठा
 *
 * There's nothing in the Emaclite device to be configured when the link
 * state changes. We just prपूर्णांक the status.
 */
अटल व्योम xemaclite_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा net_local *lp = netdev_priv(ndev);
	काष्ठा phy_device *phy = lp->phy_dev;
	पूर्णांक link_state;

	/* hash together the state values to decide अगर something has changed */
	link_state = phy->speed | (phy->duplex << 1) | phy->link;

	अगर (lp->last_link != link_state) अणु
		lp->last_link = link_state;
		phy_prपूर्णांक_status(phy);
	पूर्ण
पूर्ण

/**
 * xemaclite_खोलो - Open the network device
 * @dev:	Poपूर्णांकer to the network device
 *
 * This function sets the MAC address, requests an IRQ and enables पूर्णांकerrupts
 * क्रम the Emaclite device and starts the Tx queue.
 * It also connects to the phy device, अगर MDIO is included in Emaclite device.
 *
 * Return:	0 on success. -ENODEV, अगर PHY cannot be connected.
 *		Non-zero error value on failure.
 */
अटल पूर्णांक xemaclite_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	पूर्णांक retval;

	/* Just to be safe, stop the device first */
	xemaclite_disable_पूर्णांकerrupts(lp);

	अगर (lp->phy_node) अणु
		u32 bmcr;

		lp->phy_dev = of_phy_connect(lp->ndev, lp->phy_node,
					     xemaclite_adjust_link, 0,
					     PHY_INTERFACE_MODE_MII);
		अगर (!lp->phy_dev) अणु
			dev_err(&lp->ndev->dev, "of_phy_connect() failed\n");
			वापस -ENODEV;
		पूर्ण

		/* EmacLite करोesn't support giga-bit speeds */
		phy_set_max_speed(lp->phy_dev, SPEED_100);

		/* Don't advertise 1000BASE-T Full/Half duplex speeds */
		phy_ग_लिखो(lp->phy_dev, MII_CTRL1000, 0);

		/* Advertise only 10 and 100mbps full/half duplex speeds */
		phy_ग_लिखो(lp->phy_dev, MII_ADVERTISE, ADVERTISE_ALL |
			  ADVERTISE_CSMA);

		/* Restart स्वतः negotiation */
		bmcr = phy_पढ़ो(lp->phy_dev, MII_BMCR);
		bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
		phy_ग_लिखो(lp->phy_dev, MII_BMCR, bmcr);

		phy_start(lp->phy_dev);
	पूर्ण

	/* Set the MAC address each समय खोलोed */
	xemaclite_update_address(lp, dev->dev_addr);

	/* Grab the IRQ */
	retval = request_irq(dev->irq, xemaclite_पूर्णांकerrupt, 0, dev->name, dev);
	अगर (retval) अणु
		dev_err(&lp->ndev->dev, "Could not allocate interrupt %d\n",
			dev->irq);
		अगर (lp->phy_dev)
			phy_disconnect(lp->phy_dev);
		lp->phy_dev = शून्य;

		वापस retval;
	पूर्ण

	/* Enable Interrupts */
	xemaclite_enable_पूर्णांकerrupts(lp);

	/* We're पढ़ोy to go */
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

/**
 * xemaclite_बंद - Close the network device
 * @dev:	Poपूर्णांकer to the network device
 *
 * This function stops the Tx queue, disables पूर्णांकerrupts and मुक्तs the IRQ क्रम
 * the Emaclite device.
 * It also disconnects the phy device associated with the Emaclite device.
 *
 * Return:	0, always.
 */
अटल पूर्णांक xemaclite_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);

	netअगर_stop_queue(dev);
	xemaclite_disable_पूर्णांकerrupts(lp);
	मुक्त_irq(dev->irq, dev);

	अगर (lp->phy_dev)
		phy_disconnect(lp->phy_dev);
	lp->phy_dev = शून्य;

	वापस 0;
पूर्ण

/**
 * xemaclite_send - Transmit a frame
 * @orig_skb:	Poपूर्णांकer to the socket buffer to be transmitted
 * @dev:	Poपूर्णांकer to the network device
 *
 * This function checks अगर the Tx buffer of the Emaclite device is मुक्त to send
 * data. If so, it fills the Tx buffer with data from socket buffer data,
 * updates the stats and मुक्तs the socket buffer. The Tx completion is संकेतed
 * by an पूर्णांकerrupt. If the Tx buffer isn't मुक्त, then the socket buffer is
 * deferred and the Tx queue is stopped so that the deferred socket buffer can
 * be transmitted when the Emaclite device is मुक्त to transmit data.
 *
 * Return:	NETDEV_TX_OK, always.
 */
अटल netdev_tx_t
xemaclite_send(काष्ठा sk_buff *orig_skb, काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	काष्ठा sk_buff *new_skb;
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ flags;

	len = orig_skb->len;

	new_skb = orig_skb;

	spin_lock_irqsave(&lp->reset_lock, flags);
	अगर (xemaclite_send_data(lp, (u8 *)new_skb->data, len) != 0) अणु
		/* If the Emaclite Tx buffer is busy, stop the Tx queue and
		 * defer the skb क्रम transmission during the ISR, after the
		 * current transmission is complete
		 */
		netअगर_stop_queue(dev);
		lp->deferred_skb = new_skb;
		/* Take the समय stamp now, since we can't करो this in an ISR. */
		skb_tx_बारtamp(new_skb);
		spin_unlock_irqrestore(&lp->reset_lock, flags);
		वापस NETDEV_TX_OK;
	पूर्ण
	spin_unlock_irqrestore(&lp->reset_lock, flags);

	skb_tx_बारtamp(new_skb);

	dev->stats.tx_bytes += len;
	dev_consume_skb_any(new_skb);

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * get_bool - Get a parameter from the OF device
 * @ofdev:	Poपूर्णांकer to OF device काष्ठाure
 * @s:		Property to be retrieved
 *
 * This function looks क्रम a property in the device node and वापसs the value
 * of the property अगर its found or 0 अगर the property is not found.
 *
 * Return:	Value of the parameter अगर the parameter is found, or 0 otherwise
 */
अटल bool get_bool(काष्ठा platक्रमm_device *ofdev, स्थिर अक्षर *s)
अणु
	u32 *p = (u32 *)of_get_property(ofdev->dev.of_node, s, शून्य);

	अगर (!p) अणु
		dev_warn(&ofdev->dev, "Parameter %s not found, defaulting to false\n", s);
		वापस false;
	पूर्ण

	वापस (bool)*p;
पूर्ण

/**
 * xemaclite_ethtools_get_drvinfo - Get various Axi Emac Lite driver info
 * @ndev:       Poपूर्णांकer to net_device काष्ठाure
 * @ed:         Poपूर्णांकer to ethtool_drvinfo काष्ठाure
 *
 * This implements ethtool command क्रम getting the driver inक्रमmation.
 * Issue "ethtool -i ethX" under linux prompt to execute this function.
 */
अटल व्योम xemaclite_ethtools_get_drvinfo(काष्ठा net_device *ndev,
					   काष्ठा ethtool_drvinfo *ed)
अणु
	strlcpy(ed->driver, DRIVER_NAME, माप(ed->driver));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops xemaclite_ethtool_ops = अणु
	.get_drvinfo    = xemaclite_ethtools_get_drvinfo,
	.get_link       = ethtool_op_get_link,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops xemaclite_netdev_ops;

/**
 * xemaclite_of_probe - Probe method क्रम the Emaclite device.
 * @ofdev:	Poपूर्णांकer to OF device काष्ठाure
 *
 * This function probes क्रम the Emaclite device in the device tree.
 * It initializes the driver data काष्ठाure and the hardware, sets the MAC
 * address and रेजिस्टरs the network device.
 * It also रेजिस्टरs a mii_bus क्रम the Emaclite device, अगर MDIO is included
 * in the device.
 *
 * Return:	0, अगर the driver is bound to the Emaclite device, or
 *		a negative error अगर there is failure.
 */
अटल पूर्णांक xemaclite_of_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा resource *res;
	काष्ठा net_device *ndev = शून्य;
	काष्ठा net_local *lp = शून्य;
	काष्ठा device *dev = &ofdev->dev;

	पूर्णांक rc = 0;

	dev_info(dev, "Device Tree Probing\n");

	/* Create an ethernet device instance */
	ndev = alloc_etherdev(माप(काष्ठा net_local));
	अगर (!ndev)
		वापस -ENOMEM;

	dev_set_drvdata(dev, ndev);
	SET_NETDEV_DEV(ndev, &ofdev->dev);

	lp = netdev_priv(ndev);
	lp->ndev = ndev;

	/* Get IRQ क्रम the device */
	res = platक्रमm_get_resource(ofdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(dev, "no IRQ found\n");
		rc = -ENXIO;
		जाओ error;
	पूर्ण

	ndev->irq = res->start;

	res = platक्रमm_get_resource(ofdev, IORESOURCE_MEM, 0);
	lp->base_addr = devm_ioremap_resource(&ofdev->dev, res);
	अगर (IS_ERR(lp->base_addr)) अणु
		rc = PTR_ERR(lp->base_addr);
		जाओ error;
	पूर्ण

	ndev->mem_start = res->start;
	ndev->mem_end = res->end;

	spin_lock_init(&lp->reset_lock);
	lp->next_tx_buf_to_use = 0x0;
	lp->next_rx_buf_to_use = 0x0;
	lp->tx_ping_pong = get_bool(ofdev, "xlnx,tx-ping-pong");
	lp->rx_ping_pong = get_bool(ofdev, "xlnx,rx-ping-pong");

	rc = of_get_mac_address(ofdev->dev.of_node, ndev->dev_addr);
	अगर (rc) अणु
		dev_warn(dev, "No MAC address found, using random\n");
		eth_hw_addr_अक्रमom(ndev);
	पूर्ण

	/* Clear the Tx CSR's in हाल this is a restart */
	xemaclite_ग_लिखोl(0, lp->base_addr + XEL_TSR_OFFSET);
	xemaclite_ग_लिखोl(0, lp->base_addr + XEL_BUFFER_OFFSET + XEL_TSR_OFFSET);

	/* Set the MAC address in the EmacLite device */
	xemaclite_update_address(lp, ndev->dev_addr);

	lp->phy_node = of_parse_phandle(ofdev->dev.of_node, "phy-handle", 0);
	xemaclite_mdio_setup(lp, &ofdev->dev);

	dev_info(dev, "MAC address is now %pM\n", ndev->dev_addr);

	ndev->netdev_ops = &xemaclite_netdev_ops;
	ndev->ethtool_ops = &xemaclite_ethtool_ops;
	ndev->flags &= ~IFF_MULTICAST;
	ndev->watchकरोg_समयo = TX_TIMEOUT;

	/* Finally, रेजिस्टर the device */
	rc = रेजिस्टर_netdev(ndev);
	अगर (rc) अणु
		dev_err(dev,
			"Cannot register network device, aborting\n");
		जाओ error;
	पूर्ण

	dev_info(dev,
		 "Xilinx EmacLite at 0x%08lX mapped to 0x%08lX, irq=%d\n",
		 (अचिन्हित दीर्घ __क्रमce)ndev->mem_start,
		 (अचिन्हित दीर्घ __क्रमce)lp->base_addr, ndev->irq);
	वापस 0;

error:
	मुक्त_netdev(ndev);
	वापस rc;
पूर्ण

/**
 * xemaclite_of_हटाओ - Unbind the driver from the Emaclite device.
 * @of_dev:	Poपूर्णांकer to OF device काष्ठाure
 *
 * This function is called अगर a device is physically हटाओd from the प्रणाली or
 * अगर the driver module is being unloaded. It मुक्तs any resources allocated to
 * the device.
 *
 * Return:	0, always.
 */
अटल पूर्णांक xemaclite_of_हटाओ(काष्ठा platक्रमm_device *of_dev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(of_dev);

	काष्ठा net_local *lp = netdev_priv(ndev);

	/* Un-रेजिस्टर the mii_bus, अगर configured */
	अगर (lp->mii_bus) अणु
		mdiobus_unरेजिस्टर(lp->mii_bus);
		mdiobus_मुक्त(lp->mii_bus);
		lp->mii_bus = शून्य;
	पूर्ण

	unरेजिस्टर_netdev(ndev);

	of_node_put(lp->phy_node);
	lp->phy_node = शून्य;

	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम
xemaclite_poll_controller(काष्ठा net_device *ndev)
अणु
	disable_irq(ndev->irq);
	xemaclite_पूर्णांकerrupt(ndev->irq, ndev);
	enable_irq(ndev->irq);
पूर्ण
#पूर्ण_अगर

/* Ioctl MII Interface */
अटल पूर्णांक xemaclite_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	अगर (!dev->phydev || !netअगर_running(dev))
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		वापस phy_mii_ioctl(dev->phydev, rq, cmd);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops xemaclite_netdev_ops = अणु
	.nकरो_खोलो		= xemaclite_खोलो,
	.nकरो_stop		= xemaclite_बंद,
	.nकरो_start_xmit		= xemaclite_send,
	.nकरो_set_mac_address	= xemaclite_set_mac_address,
	.nकरो_tx_समयout		= xemaclite_tx_समयout,
	.nकरो_करो_ioctl		= xemaclite_ioctl,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = xemaclite_poll_controller,
#पूर्ण_अगर
पूर्ण;

/* Match table क्रम OF platक्रमm binding */
अटल स्थिर काष्ठा of_device_id xemaclite_of_match[] = अणु
	अणु .compatible = "xlnx,opb-ethernetlite-1.01.a", पूर्ण,
	अणु .compatible = "xlnx,opb-ethernetlite-1.01.b", पूर्ण,
	अणु .compatible = "xlnx,xps-ethernetlite-1.00.a", पूर्ण,
	अणु .compatible = "xlnx,xps-ethernetlite-2.00.a", पूर्ण,
	अणु .compatible = "xlnx,xps-ethernetlite-2.01.a", पूर्ण,
	अणु .compatible = "xlnx,xps-ethernetlite-3.00.a", पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xemaclite_of_match);

अटल काष्ठा platक्रमm_driver xemaclite_of_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = xemaclite_of_match,
	पूर्ण,
	.probe		= xemaclite_of_probe,
	.हटाओ		= xemaclite_of_हटाओ,
पूर्ण;

module_platक्रमm_driver(xemaclite_of_driver);

MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("Xilinx Ethernet MAC Lite driver");
MODULE_LICENSE("GPL");
