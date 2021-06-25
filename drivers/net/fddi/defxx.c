<शैली गुरु>
/*
 * File Name:
 *   defxx.c
 *
 * Copyright Inक्रमmation:
 *   Copyright Digital Equipment Corporation 1996.
 *
 *   This software may be used and distributed according to the terms of
 *   the GNU General Public License, incorporated herein by reference.
 *
 * Abstract:
 *   A Linux device driver supporting the Digital Equipment Corporation
 *   FDDI TURBOchannel, EISA and PCI controller families.  Supported
 *   adapters include:
 *
 *		DEC FDDIcontroller/TURBOchannel (DEFTA)
 *		DEC FDDIcontroller/EISA         (DEFEA)
 *		DEC FDDIcontroller/PCI          (DEFPA)
 *
 * The original author:
 *   LVS	Lawrence V. Stefani <lstefani@yahoo.com>
 *
 * Maपूर्णांकainers:
 *   macro	Maciej W. Rozycki <macro@orcam.me.uk>
 *
 * Credits:
 *   I'd like to thank Patricia Cross क्रम helping me get started with
 *   Linux, David Davies क्रम a lot of help upgrading and configuring
 *   my development प्रणाली and क्रम answering many OS and driver
 *   development questions, and Alan Cox क्रम recommendations and
 *   पूर्णांकegration help on getting FDDI support पूर्णांकo Linux.  LVS
 *
 * Driver Architecture:
 *   The driver architecture is largely based on previous driver work
 *   क्रम other operating प्रणालीs.  The upper edge पूर्णांकerface and
 *   functions were largely taken from existing Linux device drivers
 *   such as David Davies' DE4X5.C driver and Donald Becker's TULIP.C
 *   driver.
 *
 *   Adapter Probe -
 *		The driver scans क्रम supported EISA adapters by पढ़ोing the
 *		SLOT ID रेजिस्टर क्रम each EISA slot and making a match
 *		against the expected value.
 *
 *   Bus-Specअगरic Initialization -
 *		This driver currently supports both EISA and PCI controller
 *		families.  While the custom DMA chip and FDDI logic is similar
 *		or identical, the bus logic is very dअगरferent.  After
 *		initialization, the	only bus-specअगरic dअगरferences is in how the
 *		driver enables and disables पूर्णांकerrupts.  Other than that, the
 *		run-समय critical code behaves the same on both families.
 *		It's important to note that both adapter families are configured
 *		to I/O map, rather than memory map, the adapter रेजिस्टरs.
 *
 *   Driver Open/Close -
 *		In the driver खोलो routine, the driver ISR (पूर्णांकerrupt service
 *		routine) is रेजिस्टरed and the adapter is brought to an
 *		operational state.  In the driver बंद routine, the opposite
 *		occurs; the driver ISR is deरेजिस्टरed and the adapter is
 *		brought to a safe, but बंदd state.  Users may use consecutive
 *		commands to bring the adapter up and करोwn as in the following
 *		example:
 *					अगरconfig fddi0 up
 *					अगरconfig fddi0 करोwn
 *					अगरconfig fddi0 up
 *
 *   Driver Shutकरोwn -
 *		Apparently, there is no shutकरोwn or halt routine support under
 *		Linux.  This routine would be called during "reboot" or
 *		"shutdown" to allow the driver to place the adapter in a safe
 *		state beक्रमe a warm reboot occurs.  To be really safe, the user
 *		should बंद the adapter beक्रमe shutकरोwn (eg. अगरconfig fddi0 करोwn)
 *		to ensure that the adapter DMA engine is taken off-line.  However,
 *		the current driver code anticipates this problem and always issues
 *		a soft reset of the adapter	at the beginning of driver initialization.
 *		A future driver enhancement in this area may occur in 2.1.X where
 *		Alan indicated that a shutकरोwn handler may be implemented.
 *
 *   Interrupt Service Routine -
 *		The driver supports shared पूर्णांकerrupts, so the ISR is रेजिस्टरed क्रम
 *		each board with the appropriate flag and the poपूर्णांकer to that board's
 *		device काष्ठाure.  This provides the context during पूर्णांकerrupt
 *		processing to support shared पूर्णांकerrupts and multiple boards.
 *
 *		Interrupt enabling/disabling can occur at many levels.  At the host
 *		end, you can disable प्रणाली पूर्णांकerrupts, or disable पूर्णांकerrupts at the
 *		PIC (on Intel प्रणालीs).  Across the bus, both EISA and PCI adapters
 *		have a bus-logic chip पूर्णांकerrupt enable/disable as well as a DMA
 *		controller पूर्णांकerrupt enable/disable.
 *
 *		The driver currently enables and disables adapter पूर्णांकerrupts at the
 *		bus-logic chip and assumes that Linux will take care of clearing or
 *		acknowledging any host-based पूर्णांकerrupt chips.
 *
 *   Control Functions -
 *		Control functions are those used to support functions such as adding
 *		or deleting multicast addresses, enabling or disabling packet
 *		reception filters, or other custom/proprietary commands.  Presently,
 *		the driver supports the "get statistics", "set multicast list", and
 *		"set mac address" functions defined by Linux.  A list of possible
 *		enhancements include:
 *
 *				- Custom ioctl पूर्णांकerface क्रम executing port पूर्णांकerface commands
 *				- Custom ioctl पूर्णांकerface क्रम adding unicast addresses to
 *				  adapter CAM (to support bridge functions).
 *				- Custom ioctl पूर्णांकerface क्रम supporting firmware upgrades.
 *
 *   Hardware (port पूर्णांकerface) Support Routines -
 *		The driver function names that start with "dfx_hw_" represent
 *		low-level port पूर्णांकerface routines that are called frequently.  They
 *		include issuing a DMA or port control command to the adapter,
 *		resetting the adapter, or पढ़ोing the adapter state.  Since the
 *		driver initialization and run-समय code must make calls पूर्णांकo the
 *		port पूर्णांकerface, these routines were written to be as generic and
 *		usable as possible.
 *
 *   Receive Path -
 *		The adapter DMA engine supports a 256 entry receive descriptor block
 *		of which up to 255 entries can be used at any given समय.  The
 *		architecture is a standard producer, consumer, completion model in
 *		which the driver "produces" receive buffers to the adapter, the
 *		adapter "consumes" the receive buffers by DMAing incoming packet data,
 *		and the driver "completes" the receive buffers by servicing the
 *		incoming packet, then "produces" a new buffer and starts the cycle
 *		again.  Receive buffers can be fragmented in up to 16 fragments
 *		(descriptor	entries).  For simplicity, this driver posts
 *		single-fragment receive buffers of 4608 bytes, then allocates a
 *		sk_buff, copies the data, then reposts the buffer.  To reduce CPU
 *		utilization, a better approach would be to pass up the receive
 *		buffer (no extra copy) then allocate and post a replacement buffer.
 *		This is a perक्रमmance enhancement that should be looked पूर्णांकo at
 *		some poपूर्णांक.
 *
 *   Transmit Path -
 *		Like the receive path, the adapter DMA engine supports a 256 entry
 *		transmit descriptor block of which up to 255 entries can be used at
 *		any	given समय.  Transmit buffers can be fragmented	in up to 255
 *		fragments (descriptor entries).  This driver always posts one
 *		fragment per transmit packet request.
 *
 *		The fragment contains the entire packet from FC to end of data.
 *		Beक्रमe posting the buffer to the adapter, the driver sets a three-byte
 *		packet request header (PRH) which is required by the Motorola MAC chip
 *		used on the adapters.  The PRH tells the MAC the type of token to
 *		receive/send, whether or not to generate and append the CRC, whether
 *		synchronous or asynchronous framing is used, etc.  Since the PRH
 *		definition is not necessarily consistent across all FDDI chipsets,
 *		the driver, rather than the common FDDI packet handler routines,
 *		sets these bytes.
 *
 *		To reduce the amount of descriptor fetches needed per transmit request,
 *		the driver takes advantage of the fact that there are at least three
 *		bytes available beक्रमe the skb->data field on the outgoing transmit
 *		request.  This is guaranteed by having fddi_setup() in net_init.c set
 *		dev->hard_header_len to 24 bytes.  21 bytes accounts क्रम the largest
 *		header in an 802.2 SNAP frame.  The other 3 bytes are the extra "pad"
 *		bytes which we'll use to store the PRH.
 *
 *		There's a subtle advantage to adding these pad bytes to the
 *		hard_header_len, it ensures that the data portion of the packet क्रम
 *		an 802.2 SNAP frame is दीर्घword aligned.  Other FDDI driver
 *		implementations may not need the extra padding and can start copying
 *		or DMAing directly from the FC byte which starts at skb->data.  Should
 *		another driver implementation need ADDITIONAL padding, the net_init.c
 *		module should be updated and dev->hard_header_len should be increased.
 *		NOTE: To मुख्यtain the alignment on the data portion of the packet,
 *		dev->hard_header_len should always be evenly भागisible by 4 and at
 *		least 24 bytes in size.
 *
 * Modअगरication History:
 *		Date		Name	Description
 *		16-Aug-96	LVS		Created.
 *		20-Aug-96	LVS		Updated dfx_probe so that version inक्रमmation
 *							string is only displayed अगर 1 or more cards are
 *							found.  Changed dfx_rcv_queue_process to copy
 *							3 शून्य bytes beक्रमe FC to ensure that data is
 *							दीर्घword aligned in receive buffer.
 *		09-Sep-96	LVS		Updated dfx_ctl_set_multicast_list to enable
 *							LLC group promiscuous mode अगर multicast list
 *							is too large.  LLC inभागidual/group promiscuous
 *							mode is now disabled अगर IFF_PROMISC flag not set.
 *							dfx_xmt_queue_pkt no दीर्घer checks क्रम शून्य skb
 *							on Alan Cox recommendation.  Added node address
 *							override support.
 *		12-Sep-96	LVS		Reset current address to factory address during
 *							device खोलो.  Updated transmit path to post a
 *							single fragment which includes PRH->end of data.
 *		Mar 2000	AC		Did various cleanups क्रम 2.3.x
 *		Jun 2000	jgarzik		PCI and resource alloc cleanups
 *		Jul 2000	tjeerd		Much cleanup and some bug fixes
 *		Sep 2000	tjeerd		Fix leak on unload, cosmetic code cleanup
 *		Feb 2001			Skb allocation fixes
 *		Feb 2001	davej		PCI enable cleanups.
 *		04 Aug 2003	macro		Converted to the DMA API.
 *		14 Aug 2004	macro		Fix device names reported.
 *		14 Jun 2005	macro		Use irqवापस_t.
 *		23 Oct 2006	macro		Big-endian host support.
 *		14 Dec 2006	macro		TURBOchannel support.
 *		01 Jul 2014	macro		Fixes क्रम DMA on 64-bit hosts.
 *		10 Mar 2021	macro		Dynamic MMIO vs port I/O.
 */

/* Include files */
#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/eisa.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fddidevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/tc.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>

#समावेश "defxx.h"

/* Version inक्रमmation string should be updated prior to each new release!  */
#घोषणा DRV_NAME "defxx"
#घोषणा DRV_VERSION "v1.12"
#घोषणा DRV_RELDATE "2021/03/10"

अटल स्थिर अक्षर version[] =
	DRV_NAME ": " DRV_VERSION " " DRV_RELDATE
	"  Lawrence V. Stefani and others\n";

#घोषणा DYNAMIC_BUFFERS 1

#घोषणा SKBUFF_RX_COPYBREAK 200
/*
 * NEW_SKB_SIZE = PI_RCV_DATA_K_SIZE_MAX+128 to allow 128 byte
 * alignment क्रम compatibility with old EISA boards.
 */
#घोषणा NEW_SKB_SIZE (PI_RCV_DATA_K_SIZE_MAX+128)

#अगर_घोषित CONFIG_EISA
#घोषणा DFX_BUS_EISA(dev) (dev->bus == &eisa_bus_type)
#अन्यथा
#घोषणा DFX_BUS_EISA(dev) 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_TC
#घोषणा DFX_BUS_TC(dev) (dev->bus == &tc_bus_type)
#अन्यथा
#घोषणा DFX_BUS_TC(dev) 0
#पूर्ण_अगर

#अगर defined(CONFIG_EISA) || defined(CONFIG_PCI)
#घोषणा dfx_use_mmio bp->mmio
#अन्यथा
#घोषणा dfx_use_mmio true
#पूर्ण_अगर

/* Define module-wide (अटल) routines */

अटल व्योम		dfx_bus_init(काष्ठा net_device *dev);
अटल व्योम		dfx_bus_uninit(काष्ठा net_device *dev);
अटल व्योम		dfx_bus_config_check(DFX_board_t *bp);

अटल पूर्णांक		dfx_driver_init(काष्ठा net_device *dev,
					स्थिर अक्षर *prपूर्णांक_name,
					resource_माप_प्रकार bar_start);
अटल पूर्णांक		dfx_adap_init(DFX_board_t *bp, पूर्णांक get_buffers);

अटल पूर्णांक		dfx_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक		dfx_बंद(काष्ठा net_device *dev);

अटल व्योम		dfx_पूर्णांक_pr_halt_id(DFX_board_t *bp);
अटल व्योम		dfx_पूर्णांक_type_0_process(DFX_board_t *bp);
अटल व्योम		dfx_पूर्णांक_common(काष्ठा net_device *dev);
अटल irqवापस_t	dfx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

अटल काष्ठा		net_device_stats *dfx_ctl_get_stats(काष्ठा net_device *dev);
अटल व्योम		dfx_ctl_set_multicast_list(काष्ठा net_device *dev);
अटल पूर्णांक		dfx_ctl_set_mac_address(काष्ठा net_device *dev, व्योम *addr);
अटल पूर्णांक		dfx_ctl_update_cam(DFX_board_t *bp);
अटल पूर्णांक		dfx_ctl_update_filters(DFX_board_t *bp);

अटल पूर्णांक		dfx_hw_dma_cmd_req(DFX_board_t *bp);
अटल पूर्णांक		dfx_hw_port_ctrl_req(DFX_board_t *bp, PI_UINT32	command, PI_UINT32 data_a, PI_UINT32 data_b, PI_UINT32 *host_data);
अटल व्योम		dfx_hw_adap_reset(DFX_board_t *bp, PI_UINT32 type);
अटल पूर्णांक		dfx_hw_adap_state_rd(DFX_board_t *bp);
अटल पूर्णांक		dfx_hw_dma_uninit(DFX_board_t *bp, PI_UINT32 type);

अटल पूर्णांक		dfx_rcv_init(DFX_board_t *bp, पूर्णांक get_buffers);
अटल व्योम		dfx_rcv_queue_process(DFX_board_t *bp);
#अगर_घोषित DYNAMIC_BUFFERS
अटल व्योम		dfx_rcv_flush(DFX_board_t *bp);
#अन्यथा
अटल अंतरभूत व्योम	dfx_rcv_flush(DFX_board_t *bp) अणुपूर्ण
#पूर्ण_अगर

अटल netdev_tx_t dfx_xmt_queue_pkt(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev);
अटल पूर्णांक		dfx_xmt_करोne(DFX_board_t *bp);
अटल व्योम		dfx_xmt_flush(DFX_board_t *bp);

/* Define module-wide (अटल) variables */

अटल काष्ठा pci_driver dfx_pci_driver;
अटल काष्ठा eisa_driver dfx_eisa_driver;
अटल काष्ठा tc_driver dfx_tc_driver;


/*
 * =======================
 * = dfx_port_ग_लिखो_दीर्घ =
 * = dfx_port_पढ़ो_दीर्घ  =
 * =======================
 *
 * Overview:
 *   Routines क्रम पढ़ोing and writing values from/to adapter
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp		- poपूर्णांकer to board inक्रमmation
 *   offset	- रेजिस्टर offset from base I/O address
 *   data	- क्रम dfx_port_ग_लिखो_दीर्घ, this is a value to ग_लिखो;
 *		  क्रम dfx_port_पढ़ो_दीर्घ, this is a poपूर्णांकer to store
 *		  the पढ़ो value
 *
 * Functional Description:
 *   These routines perक्रमm the correct operation to पढ़ो or ग_लिखो
 *   the adapter रेजिस्टर.
 *
 *   EISA port block base addresses are based on the slot number in which the
 *   controller is installed.  For example, अगर the EISA controller is installed
 *   in slot 4, the port block base address is 0x4000.  If the controller is
 *   installed in slot 2, the port block base address is 0x2000, and so on.
 *   This port block can be used to access PDQ, ESIC, and DEFEA on-board
 *   रेजिस्टरs using the रेजिस्टर offsets defined in DEFXX.H.
 *
 *   PCI port block base addresses are asचिन्हित by the PCI BIOS or प्रणाली
 *   firmware.  There is one 128 byte port block which can be accessed.  It
 *   allows क्रम I/O mapping of both PDQ and PFI रेजिस्टरs using the रेजिस्टर
 *   offsets defined in DEFXX.H.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   bp->base is a valid base I/O address क्रम this adapter.
 *   offset is a valid रेजिस्टर offset क्रम this adapter.
 *
 * Side Effects:
 *   Rather than produce macros क्रम these functions, these routines
 *   are defined using "inline" to ensure that the compiler will
 *   generate अंतरभूत code and not waste a procedure call and वापस.
 *   This provides all the benefits of macros, but with the
 *   advantage of strict data type checking.
 */

अटल अंतरभूत व्योम dfx_ग_लिखोl(DFX_board_t *bp, पूर्णांक offset, u32 data)
अणु
	ग_लिखोl(data, bp->base.mem + offset);
	mb();
पूर्ण

अटल अंतरभूत व्योम dfx_outl(DFX_board_t *bp, पूर्णांक offset, u32 data)
अणु
	outl(data, bp->base.port + offset);
पूर्ण

अटल व्योम dfx_port_ग_लिखो_दीर्घ(DFX_board_t *bp, पूर्णांक offset, u32 data)
अणु
	काष्ठा device __maybe_unused *bdev = bp->bus_dev;

	अगर (dfx_use_mmio)
		dfx_ग_लिखोl(bp, offset, data);
	अन्यथा
		dfx_outl(bp, offset, data);
पूर्ण


अटल अंतरभूत व्योम dfx_पढ़ोl(DFX_board_t *bp, पूर्णांक offset, u32 *data)
अणु
	mb();
	*data = पढ़ोl(bp->base.mem + offset);
पूर्ण

अटल अंतरभूत व्योम dfx_inl(DFX_board_t *bp, पूर्णांक offset, u32 *data)
अणु
	*data = inl(bp->base.port + offset);
पूर्ण

अटल व्योम dfx_port_पढ़ो_दीर्घ(DFX_board_t *bp, पूर्णांक offset, u32 *data)
अणु
	काष्ठा device __maybe_unused *bdev = bp->bus_dev;

	अगर (dfx_use_mmio)
		dfx_पढ़ोl(bp, offset, data);
	अन्यथा
		dfx_inl(bp, offset, data);
पूर्ण


/*
 * ================
 * = dfx_get_bars =
 * ================
 *
 * Overview:
 *   Retrieves the address ranges used to access control and status
 *   रेजिस्टरs.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp		- poपूर्णांकer to board inक्रमmation
 *   bar_start	- poपूर्णांकer to store the start addresses
 *   bar_len	- poपूर्णांकer to store the lengths of the areas
 *
 * Assumptions:
 *   I am sure there are some.
 *
 * Side Effects:
 *   None
 */
अटल व्योम dfx_get_bars(DFX_board_t *bp,
			 resource_माप_प्रकार *bar_start, resource_माप_प्रकार *bar_len)
अणु
	काष्ठा device *bdev = bp->bus_dev;
	पूर्णांक dfx_bus_pci = dev_is_pci(bdev);
	पूर्णांक dfx_bus_eisa = DFX_BUS_EISA(bdev);
	पूर्णांक dfx_bus_tc = DFX_BUS_TC(bdev);

	अगर (dfx_bus_pci) अणु
		पूर्णांक num = dfx_use_mmio ? 0 : 1;

		bar_start[0] = pci_resource_start(to_pci_dev(bdev), num);
		bar_len[0] = pci_resource_len(to_pci_dev(bdev), num);
		bar_start[2] = bar_start[1] = 0;
		bar_len[2] = bar_len[1] = 0;
	पूर्ण
	अगर (dfx_bus_eisa) अणु
		अचिन्हित दीर्घ base_addr = to_eisa_device(bdev)->base_addr;
		resource_माप_प्रकार bar_lo;
		resource_माप_प्रकार bar_hi;

		अगर (dfx_use_mmio) अणु
			bar_lo = inb(base_addr + PI_ESIC_K_MEM_ADD_LO_CMP_2);
			bar_lo <<= 8;
			bar_lo |= inb(base_addr + PI_ESIC_K_MEM_ADD_LO_CMP_1);
			bar_lo <<= 8;
			bar_lo |= inb(base_addr + PI_ESIC_K_MEM_ADD_LO_CMP_0);
			bar_lo <<= 8;
			bar_start[0] = bar_lo;
			bar_hi = inb(base_addr + PI_ESIC_K_MEM_ADD_HI_CMP_2);
			bar_hi <<= 8;
			bar_hi |= inb(base_addr + PI_ESIC_K_MEM_ADD_HI_CMP_1);
			bar_hi <<= 8;
			bar_hi |= inb(base_addr + PI_ESIC_K_MEM_ADD_HI_CMP_0);
			bar_hi <<= 8;
			bar_len[0] = ((bar_hi - bar_lo) | PI_MEM_ADD_MASK_M) +
				     1;
		पूर्ण अन्यथा अणु
			bar_start[0] = base_addr;
			bar_len[0] = PI_ESIC_K_CSR_IO_LEN;
		पूर्ण
		bar_start[1] = base_addr + PI_DEFEA_K_BURST_HOLDOFF;
		bar_len[1] = PI_ESIC_K_BURST_HOLDOFF_LEN;
		bar_start[2] = base_addr + PI_ESIC_K_ESIC_CSR;
		bar_len[2] = PI_ESIC_K_ESIC_CSR_LEN;
	पूर्ण
	अगर (dfx_bus_tc) अणु
		bar_start[0] = to_tc_dev(bdev)->resource.start +
			       PI_TC_K_CSR_OFFSET;
		bar_len[0] = PI_TC_K_CSR_LEN;
		bar_start[2] = bar_start[1] = 0;
		bar_len[2] = bar_len[1] = 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops dfx_netdev_ops = अणु
	.nकरो_खोलो		= dfx_खोलो,
	.nकरो_stop		= dfx_बंद,
	.nकरो_start_xmit		= dfx_xmt_queue_pkt,
	.nकरो_get_stats		= dfx_ctl_get_stats,
	.nकरो_set_rx_mode	= dfx_ctl_set_multicast_list,
	.nकरो_set_mac_address	= dfx_ctl_set_mac_address,
पूर्ण;

अटल व्योम dfx_रेजिस्टर_res_err(स्थिर अक्षर *prपूर्णांक_name, bool mmio,
				 अचिन्हित दीर्घ start, अचिन्हित दीर्घ len)
अणु
	pr_err("%s: Cannot reserve %s resource 0x%lx @ 0x%lx, aborting\n",
	       prपूर्णांक_name, mmio ? "MMIO" : "I/O", len, start);
पूर्ण

/*
 * ================
 * = dfx_रेजिस्टर =
 * ================
 *
 * Overview:
 *   Initializes a supported FDDI controller
 *
 * Returns:
 *   Condition code
 *
 * Arguments:
 *   bdev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *
 * Return Codes:
 *   0		 - This device (fddi0, fddi1, etc) configured successfully
 *   -EBUSY      - Failed to get resources, or dfx_driver_init failed.
 *
 * Assumptions:
 *   It compiles so it should work :-( (PCI cards करो :-)
 *
 * Side Effects:
 *   Device काष्ठाures क्रम FDDI adapters (fddi0, fddi1, etc) are
 *   initialized and the board resources are पढ़ो and stored in
 *   the device काष्ठाure.
 */
अटल पूर्णांक dfx_रेजिस्टर(काष्ठा device *bdev)
अणु
	अटल पूर्णांक version_disp;
	पूर्णांक dfx_bus_pci = dev_is_pci(bdev);
	पूर्णांक dfx_bus_eisa = DFX_BUS_EISA(bdev);
	स्थिर अक्षर *prपूर्णांक_name = dev_name(bdev);
	काष्ठा net_device *dev;
	DFX_board_t	  *bp;			/* board poपूर्णांकer */
	resource_माप_प्रकार bar_start[3] = अणु0पूर्ण;	/* poपूर्णांकers to ports */
	resource_माप_प्रकार bar_len[3] = अणु0पूर्ण;	/* resource length */
	पूर्णांक alloc_size;				/* total buffer size used */
	काष्ठा resource *region;
	पूर्णांक err = 0;

	अगर (!version_disp) अणु	/* display version info अगर adapter is found */
		version_disp = 1;	/* set display flag to TRUE so that */
		prपूर्णांकk(version);	/* we only display this string ONCE */
	पूर्ण

	dev = alloc_fddidev(माप(*bp));
	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR "%s: Unable to allocate fddidev, aborting\n",
		       prपूर्णांक_name);
		वापस -ENOMEM;
	पूर्ण

	/* Enable PCI device. */
	अगर (dfx_bus_pci) अणु
		err = pci_enable_device(to_pci_dev(bdev));
		अगर (err) अणु
			pr_err("%s: Cannot enable PCI device, aborting\n",
			       prपूर्णांक_name);
			जाओ err_out;
		पूर्ण
	पूर्ण

	SET_NETDEV_DEV(dev, bdev);

	bp = netdev_priv(dev);
	bp->bus_dev = bdev;
	dev_set_drvdata(bdev, dev);

	bp->mmio = true;

	dfx_get_bars(bp, bar_start, bar_len);
	अगर (bar_len[0] == 0 ||
	    (dfx_bus_eisa && dfx_use_mmio && bar_start[0] == 0)) अणु
		bp->mmio = false;
		dfx_get_bars(bp, bar_start, bar_len);
	पूर्ण

	अगर (dfx_use_mmio) अणु
		region = request_mem_region(bar_start[0], bar_len[0],
					    bdev->driver->name);
		अगर (!region && (dfx_bus_eisa || dfx_bus_pci)) अणु
			bp->mmio = false;
			dfx_get_bars(bp, bar_start, bar_len);
		पूर्ण
	पूर्ण
	अगर (!dfx_use_mmio)
		region = request_region(bar_start[0], bar_len[0],
					bdev->driver->name);
	अगर (!region) अणु
		dfx_रेजिस्टर_res_err(prपूर्णांक_name, dfx_use_mmio,
				     bar_start[0], bar_len[0]);
		err = -EBUSY;
		जाओ err_out_disable;
	पूर्ण
	अगर (bar_start[1] != 0) अणु
		region = request_region(bar_start[1], bar_len[1],
					bdev->driver->name);
		अगर (!region) अणु
			dfx_रेजिस्टर_res_err(prपूर्णांक_name, 0,
					     bar_start[1], bar_len[1]);
			err = -EBUSY;
			जाओ err_out_csr_region;
		पूर्ण
	पूर्ण
	अगर (bar_start[2] != 0) अणु
		region = request_region(bar_start[2], bar_len[2],
					bdev->driver->name);
		अगर (!region) अणु
			dfx_रेजिस्टर_res_err(prपूर्णांक_name, 0,
					     bar_start[2], bar_len[2]);
			err = -EBUSY;
			जाओ err_out_bh_region;
		पूर्ण
	पूर्ण

	/* Set up I/O base address. */
	अगर (dfx_use_mmio) अणु
		bp->base.mem = ioremap(bar_start[0], bar_len[0]);
		अगर (!bp->base.mem) अणु
			prपूर्णांकk(KERN_ERR "%s: Cannot map MMIO\n", prपूर्णांक_name);
			err = -ENOMEM;
			जाओ err_out_esic_region;
		पूर्ण
	पूर्ण अन्यथा अणु
		bp->base.port = bar_start[0];
		dev->base_addr = bar_start[0];
	पूर्ण

	/* Initialize new device काष्ठाure */
	dev->netdev_ops			= &dfx_netdev_ops;

	अगर (dfx_bus_pci)
		pci_set_master(to_pci_dev(bdev));

	अगर (dfx_driver_init(dev, prपूर्णांक_name, bar_start[0]) != DFX_K_SUCCESS) अणु
		err = -ENODEV;
		जाओ err_out_unmap;
	पूर्ण

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ err_out_kमुक्त;

	prपूर्णांकk("%s: registered as %s\n", prपूर्णांक_name, dev->name);
	वापस 0;

err_out_kमुक्त:
	alloc_size = माप(PI_DESCR_BLOCK) +
		     PI_CMD_REQ_K_SIZE_MAX + PI_CMD_RSP_K_SIZE_MAX +
#अगर_अघोषित DYNAMIC_BUFFERS
		     (bp->rcv_bufs_to_post * PI_RCV_DATA_K_SIZE_MAX) +
#पूर्ण_अगर
		     माप(PI_CONSUMER_BLOCK) +
		     (PI_ALIGN_K_DESC_BLK - 1);
	अगर (bp->kदो_स्मृतिed)
		dma_मुक्त_coherent(bdev, alloc_size,
				  bp->kदो_स्मृतिed, bp->kदो_स्मृतिed_dma);

err_out_unmap:
	अगर (dfx_use_mmio)
		iounmap(bp->base.mem);

err_out_esic_region:
	अगर (bar_start[2] != 0)
		release_region(bar_start[2], bar_len[2]);

err_out_bh_region:
	अगर (bar_start[1] != 0)
		release_region(bar_start[1], bar_len[1]);

err_out_csr_region:
	अगर (dfx_use_mmio)
		release_mem_region(bar_start[0], bar_len[0]);
	अन्यथा
		release_region(bar_start[0], bar_len[0]);

err_out_disable:
	अगर (dfx_bus_pci)
		pci_disable_device(to_pci_dev(bdev));

err_out:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण


/*
 * ================
 * = dfx_bus_init =
 * ================
 *
 * Overview:
 *   Initializes the bus-specअगरic controller logic.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   Determine and save adapter IRQ in device table,
 *   then perक्रमm bus-specअगरic logic initialization.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   bp->base has alपढ़ोy been set with the proper
 *	 base I/O address क्रम this device.
 *
 * Side Effects:
 *   Interrupts are enabled at the adapter bus-specअगरic logic.
 *   Note:  Interrupts at the DMA engine (PDQ chip) are not
 *   enabled yet.
 */

अटल व्योम dfx_bus_init(काष्ठा net_device *dev)
अणु
	DFX_board_t *bp = netdev_priv(dev);
	काष्ठा device *bdev = bp->bus_dev;
	पूर्णांक dfx_bus_pci = dev_is_pci(bdev);
	पूर्णांक dfx_bus_eisa = DFX_BUS_EISA(bdev);
	पूर्णांक dfx_bus_tc = DFX_BUS_TC(bdev);
	u8 val;

	DBG_prपूर्णांकk("In dfx_bus_init...\n");

	/* Initialize a poपूर्णांकer back to the net_device काष्ठा */
	bp->dev = dev;

	/* Initialize adapter based on bus type */

	अगर (dfx_bus_tc)
		dev->irq = to_tc_dev(bdev)->पूर्णांकerrupt;
	अगर (dfx_bus_eisa) अणु
		अचिन्हित दीर्घ base_addr = to_eisa_device(bdev)->base_addr;

		/* Disable the board beक्रमe fiddling with the decoders.  */
		outb(0, base_addr + PI_ESIC_K_SLOT_CNTRL);

		/* Get the पूर्णांकerrupt level from the ESIC chip.  */
		val = inb(base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);
		val &= PI_CONFIG_STAT_0_M_IRQ;
		val >>= PI_CONFIG_STAT_0_V_IRQ;

		चयन (val) अणु
		हाल PI_CONFIG_STAT_0_IRQ_K_9:
			dev->irq = 9;
			अवरोध;

		हाल PI_CONFIG_STAT_0_IRQ_K_10:
			dev->irq = 10;
			अवरोध;

		हाल PI_CONFIG_STAT_0_IRQ_K_11:
			dev->irq = 11;
			अवरोध;

		हाल PI_CONFIG_STAT_0_IRQ_K_15:
			dev->irq = 15;
			अवरोध;
		पूर्ण

		/*
		 * Enable memory decoding (MEMCS1) and/or port decoding
		 * (IOCS1/IOCS0) as appropriate in Function Control
		 * Register.  MEMCS1 or IOCS0 is used क्रम PDQ रेजिस्टरs,
		 * taking 16 32-bit words, जबतक IOCS1 is used क्रम the
		 * Burst Holकरोff रेजिस्टर, taking a single 32-bit word
		 * only.  We use the slot-specअगरic I/O range as per the
		 * ESIC spec, that is set bits 15:12 in the mask रेजिस्टरs
		 * to mask them out.
		 */

		/* Set the decode range of the board.  */
		val = 0;
		outb(val, base_addr + PI_ESIC_K_IO_ADD_CMP_0_1);
		val = PI_DEFEA_K_CSR_IO;
		outb(val, base_addr + PI_ESIC_K_IO_ADD_CMP_0_0);

		val = PI_IO_CMP_M_SLOT;
		outb(val, base_addr + PI_ESIC_K_IO_ADD_MASK_0_1);
		val = (PI_ESIC_K_CSR_IO_LEN - 1) & ~3;
		outb(val, base_addr + PI_ESIC_K_IO_ADD_MASK_0_0);

		val = 0;
		outb(val, base_addr + PI_ESIC_K_IO_ADD_CMP_1_1);
		val = PI_DEFEA_K_BURST_HOLDOFF;
		outb(val, base_addr + PI_ESIC_K_IO_ADD_CMP_1_0);

		val = PI_IO_CMP_M_SLOT;
		outb(val, base_addr + PI_ESIC_K_IO_ADD_MASK_1_1);
		val = (PI_ESIC_K_BURST_HOLDOFF_LEN - 1) & ~3;
		outb(val, base_addr + PI_ESIC_K_IO_ADD_MASK_1_0);

		/* Enable the decoders.  */
		val = PI_FUNCTION_CNTRL_M_IOCS1;
		अगर (dfx_use_mmio)
			val |= PI_FUNCTION_CNTRL_M_MEMCS1;
		अन्यथा
			val |= PI_FUNCTION_CNTRL_M_IOCS0;
		outb(val, base_addr + PI_ESIC_K_FUNCTION_CNTRL);

		/*
		 * Enable access to the rest of the module
		 * (including PDQ and packet memory).
		 */
		val = PI_SLOT_CNTRL_M_ENB;
		outb(val, base_addr + PI_ESIC_K_SLOT_CNTRL);

		/*
		 * Map PDQ रेजिस्टरs पूर्णांकo memory or port space.  This is
		 * करोne with a bit in the Burst Holकरोff रेजिस्टर.
		 */
		val = inb(base_addr + PI_DEFEA_K_BURST_HOLDOFF);
		अगर (dfx_use_mmio)
			val |= PI_BURST_HOLDOFF_M_MEM_MAP;
		अन्यथा
			val &= ~PI_BURST_HOLDOFF_M_MEM_MAP;
		outb(val, base_addr + PI_DEFEA_K_BURST_HOLDOFF);

		/* Enable पूर्णांकerrupts at EISA bus पूर्णांकerface chip (ESIC) */
		val = inb(base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);
		val |= PI_CONFIG_STAT_0_M_INT_ENB;
		outb(val, base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);
	पूर्ण
	अगर (dfx_bus_pci) अणु
		काष्ठा pci_dev *pdev = to_pci_dev(bdev);

		/* Get the पूर्णांकerrupt level from the PCI Configuration Table */

		dev->irq = pdev->irq;

		/* Check Latency Timer and set अगर less than minimal */

		pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &val);
		अगर (val < PFI_K_LAT_TIMER_MIN) अणु
			val = PFI_K_LAT_TIMER_DEF;
			pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, val);
		पूर्ण

		/* Enable पूर्णांकerrupts at PCI bus पूर्णांकerface chip (PFI) */
		val = PFI_MODE_M_PDQ_INT_ENB | PFI_MODE_M_DMA_ENB;
		dfx_port_ग_लिखो_दीर्घ(bp, PFI_K_REG_MODE_CTRL, val);
	पूर्ण
पूर्ण

/*
 * ==================
 * = dfx_bus_uninit =
 * ==================
 *
 * Overview:
 *   Uninitializes the bus-specअगरic controller logic.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   Perक्रमm bus-specअगरic logic uninitialization.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   bp->base has alपढ़ोy been set with the proper
 *	 base I/O address क्रम this device.
 *
 * Side Effects:
 *   Interrupts are disabled at the adapter bus-specअगरic logic.
 */

अटल व्योम dfx_bus_uninit(काष्ठा net_device *dev)
अणु
	DFX_board_t *bp = netdev_priv(dev);
	काष्ठा device *bdev = bp->bus_dev;
	पूर्णांक dfx_bus_pci = dev_is_pci(bdev);
	पूर्णांक dfx_bus_eisa = DFX_BUS_EISA(bdev);
	u8 val;

	DBG_prपूर्णांकk("In dfx_bus_uninit...\n");

	/* Uninitialize adapter based on bus type */

	अगर (dfx_bus_eisa) अणु
		अचिन्हित दीर्घ base_addr = to_eisa_device(bdev)->base_addr;

		/* Disable पूर्णांकerrupts at EISA bus पूर्णांकerface chip (ESIC) */
		val = inb(base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);
		val &= ~PI_CONFIG_STAT_0_M_INT_ENB;
		outb(val, base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);

		/* Disable the board.  */
		outb(0, base_addr + PI_ESIC_K_SLOT_CNTRL);

		/* Disable memory and port decoders.  */
		outb(0, base_addr + PI_ESIC_K_FUNCTION_CNTRL);
	पूर्ण
	अगर (dfx_bus_pci) अणु
		/* Disable पूर्णांकerrupts at PCI bus पूर्णांकerface chip (PFI) */
		dfx_port_ग_लिखो_दीर्घ(bp, PFI_K_REG_MODE_CTRL, 0);
	पूर्ण
पूर्ण


/*
 * ========================
 * = dfx_bus_config_check =
 * ========================
 *
 * Overview:
 *   Checks the configuration (burst size, full-duplex, etc.)  If any parameters
 *   are illegal, then this routine will set new शेषs.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   For Revision 1 FDDI EISA, Revision 2 or later FDDI EISA with rev E or later
 *   PDQ, and all FDDI PCI controllers, all values are legal.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   dfx_adap_init has NOT been called yet so burst size and other items have
 *   not been set.
 *
 * Side Effects:
 *   None
 */

अटल व्योम dfx_bus_config_check(DFX_board_t *bp)
अणु
	काष्ठा device __maybe_unused *bdev = bp->bus_dev;
	पूर्णांक dfx_bus_eisa = DFX_BUS_EISA(bdev);
	पूर्णांक	status;				/* वापस code from adapter port control call */
	u32	host_data;			/* LW data वापसed from port control call */

	DBG_prपूर्णांकk("In dfx_bus_config_check...\n");

	/* Configuration check only valid क्रम EISA adapter */

	अगर (dfx_bus_eisa) अणु
		/*
		 * First check अगर revision 2 EISA controller.  Rev. 1 cards used
		 * PDQ revision B, so no workaround needed in this हाल.  Rev. 3
		 * cards used PDQ revision E, so no workaround needed in this
		 * हाल, either.  Only Rev. 2 cards used either Rev. D or E
		 * chips, so we must verअगरy the chip revision on Rev. 2 cards.
		 */
		अगर (to_eisa_device(bdev)->id.driver_data == DEFEA_PROD_ID_2) अणु
			/*
			 * Revision 2 FDDI EISA controller found,
			 * so let's check PDQ revision of adapter.
			 */
			status = dfx_hw_port_ctrl_req(bp,
											PI_PCTRL_M_SUB_CMD,
											PI_SUB_CMD_K_PDQ_REV_GET,
											0,
											&host_data);
			अगर ((status != DFX_K_SUCCESS) || (host_data == 2))
				अणु
				/*
				 * Either we couldn't determine the PDQ revision, or
				 * we determined that it is at revision D.  In either हाल,
				 * we need to implement the workaround.
				 */

				/* Ensure that the burst size is set to 8 दीर्घwords or less */

				चयन (bp->burst_size)
					अणु
					हाल PI_PDATA_B_DMA_BURST_SIZE_32:
					हाल PI_PDATA_B_DMA_BURST_SIZE_16:
						bp->burst_size = PI_PDATA_B_DMA_BURST_SIZE_8;
						अवरोध;

					शेष:
						अवरोध;
					पूर्ण

				/* Ensure that full-duplex mode is not enabled */

				bp->full_duplex_enb = PI_SNMP_K_FALSE;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण


/*
 * ===================
 * = dfx_driver_init =
 * ===================
 *
 * Overview:
 *   Initializes reमुख्यing adapter board काष्ठाure inक्रमmation
 *   and makes sure adapter is in a safe state prior to dfx_खोलो().
 *
 * Returns:
 *   Condition code
 *
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *   prपूर्णांक_name - prपूर्णांकable device name
 *
 * Functional Description:
 *   This function allocates additional resources such as the host memory
 *   blocks needed by the adapter (eg. descriptor and consumer blocks).
 *	 Reमुख्यing bus initialization steps are also completed.  The adapter
 *   is also reset so that it is in the DMA_UNAVAILABLE state.  The OS
 *   must call dfx_खोलो() to खोलो the adapter and bring it on-line.
 *
 * Return Codes:
 *   DFX_K_SUCCESS	- initialization succeeded
 *   DFX_K_FAILURE	- initialization failed - could not allocate memory
 *						or पढ़ो adapter MAC address
 *
 * Assumptions:
 *   Memory allocated from pci_alloc_consistent() call is physically
 *   contiguous, locked memory.
 *
 * Side Effects:
 *   Adapter is reset and should be in DMA_UNAVAILABLE state beक्रमe
 *   वापसing from this routine.
 */

अटल पूर्णांक dfx_driver_init(काष्ठा net_device *dev, स्थिर अक्षर *prपूर्णांक_name,
			   resource_माप_प्रकार bar_start)
अणु
	DFX_board_t *bp = netdev_priv(dev);
	काष्ठा device *bdev = bp->bus_dev;
	पूर्णांक dfx_bus_pci = dev_is_pci(bdev);
	पूर्णांक dfx_bus_eisa = DFX_BUS_EISA(bdev);
	पूर्णांक dfx_bus_tc = DFX_BUS_TC(bdev);
	पूर्णांक alloc_size;			/* total buffer size needed */
	अक्षर *top_v, *curr_v;		/* भव addrs पूर्णांकo memory block */
	dma_addr_t top_p, curr_p;	/* physical addrs पूर्णांकo memory block */
	u32 data;			/* host data रेजिस्टर value */
	__le32 le32;
	अक्षर *board_name = शून्य;

	DBG_prपूर्णांकk("In dfx_driver_init...\n");

	/* Initialize bus-specअगरic hardware रेजिस्टरs */

	dfx_bus_init(dev);

	/*
	 * Initialize शेष values क्रम configurable parameters
	 *
	 * Note: All of these parameters are ones that a user may
	 *       want to customize.  It'd be nice to अवरोध these
	 *		 out पूर्णांकo Space.c or someplace अन्यथा that's more
	 *		 accessible/understandable than this file.
	 */

	bp->full_duplex_enb		= PI_SNMP_K_FALSE;
	bp->req_ttrt			= 8 * 12500;		/* 8ms in 80 nanosec units */
	bp->burst_size			= PI_PDATA_B_DMA_BURST_SIZE_DEF;
	bp->rcv_bufs_to_post	= RCV_BUFS_DEF;

	/*
	 * Ensure that HW configuration is OK
	 *
	 * Note: Depending on the hardware revision, we may need to modअगरy
	 *       some of the configurable parameters to workaround hardware
	 *       limitations.  We'll perक्रमm this configuration check AFTER
	 *       setting the parameters to their शेष values.
	 */

	dfx_bus_config_check(bp);

	/* Disable PDQ पूर्णांकerrupts first */

	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_HOST_INT_ENB, PI_HOST_INT_K_DISABLE_ALL_INTS);

	/* Place adapter in DMA_UNAVAILABLE state by resetting adapter */

	(व्योम) dfx_hw_dma_uninit(bp, PI_PDATA_A_RESET_M_SKIP_ST);

	/*  Read the factory MAC address from the adapter then save it */

	अगर (dfx_hw_port_ctrl_req(bp, PI_PCTRL_M_MLA, PI_PDATA_A_MLA_K_LO, 0,
				 &data) != DFX_K_SUCCESS) अणु
		prपूर्णांकk("%s: Could not read adapter factory MAC address!\n",
		       prपूर्णांक_name);
		वापस DFX_K_FAILURE;
	पूर्ण
	le32 = cpu_to_le32(data);
	स_नकल(&bp->factory_mac_addr[0], &le32, माप(u32));

	अगर (dfx_hw_port_ctrl_req(bp, PI_PCTRL_M_MLA, PI_PDATA_A_MLA_K_HI, 0,
				 &data) != DFX_K_SUCCESS) अणु
		prपूर्णांकk("%s: Could not read adapter factory MAC address!\n",
		       prपूर्णांक_name);
		वापस DFX_K_FAILURE;
	पूर्ण
	le32 = cpu_to_le32(data);
	स_नकल(&bp->factory_mac_addr[4], &le32, माप(u16));

	/*
	 * Set current address to factory address
	 *
	 * Note: Node address override support is handled through
	 *       dfx_ctl_set_mac_address.
	 */

	स_नकल(dev->dev_addr, bp->factory_mac_addr, FDDI_K_ALEN);
	अगर (dfx_bus_tc)
		board_name = "DEFTA";
	अगर (dfx_bus_eisa)
		board_name = "DEFEA";
	अगर (dfx_bus_pci)
		board_name = "DEFPA";
	pr_info("%s: %s at %s addr = 0x%llx, IRQ = %d, Hardware addr = %pMF\n",
		prपूर्णांक_name, board_name, dfx_use_mmio ? "MMIO" : "I/O",
		(दीर्घ दीर्घ)bar_start, dev->irq, dev->dev_addr);

	/*
	 * Get memory क्रम descriptor block, consumer block, and other buffers
	 * that need to be DMA पढ़ो or written to by the adapter.
	 */

	alloc_size = माप(PI_DESCR_BLOCK) +
					PI_CMD_REQ_K_SIZE_MAX +
					PI_CMD_RSP_K_SIZE_MAX +
#अगर_अघोषित DYNAMIC_BUFFERS
					(bp->rcv_bufs_to_post * PI_RCV_DATA_K_SIZE_MAX) +
#पूर्ण_अगर
					माप(PI_CONSUMER_BLOCK) +
					(PI_ALIGN_K_DESC_BLK - 1);
	bp->kदो_स्मृतिed = top_v = dma_alloc_coherent(bp->bus_dev, alloc_size,
						   &bp->kदो_स्मृतिed_dma,
						   GFP_ATOMIC);
	अगर (top_v == शून्य)
		वापस DFX_K_FAILURE;

	top_p = bp->kदो_स्मृतिed_dma;	/* get physical address of buffer */

	/*
	 *  To guarantee the 8K alignment required क्रम the descriptor block, 8K - 1
	 *  plus the amount of memory needed was allocated.  The physical address
	 *	is now 8K aligned.  By carving up the memory in a specअगरic order,
	 *  we'll guarantee the alignment requirements क्रम all other काष्ठाures.
	 *
	 *  Note: If the assumptions change regarding the non-paged, non-cached,
	 *		  physically contiguous nature of the memory block or the address
	 *		  alignments, then we'll need to implement a dअगरferent algorithm
	 *		  क्रम allocating the needed memory.
	 */

	curr_p = ALIGN(top_p, PI_ALIGN_K_DESC_BLK);
	curr_v = top_v + (curr_p - top_p);

	/* Reserve space क्रम descriptor block */

	bp->descr_block_virt = (PI_DESCR_BLOCK *) curr_v;
	bp->descr_block_phys = curr_p;
	curr_v += माप(PI_DESCR_BLOCK);
	curr_p += माप(PI_DESCR_BLOCK);

	/* Reserve space क्रम command request buffer */

	bp->cmd_req_virt = (PI_DMA_CMD_REQ *) curr_v;
	bp->cmd_req_phys = curr_p;
	curr_v += PI_CMD_REQ_K_SIZE_MAX;
	curr_p += PI_CMD_REQ_K_SIZE_MAX;

	/* Reserve space क्रम command response buffer */

	bp->cmd_rsp_virt = (PI_DMA_CMD_RSP *) curr_v;
	bp->cmd_rsp_phys = curr_p;
	curr_v += PI_CMD_RSP_K_SIZE_MAX;
	curr_p += PI_CMD_RSP_K_SIZE_MAX;

	/* Reserve space क्रम the LLC host receive queue buffers */

	bp->rcv_block_virt = curr_v;
	bp->rcv_block_phys = curr_p;

#अगर_अघोषित DYNAMIC_BUFFERS
	curr_v += (bp->rcv_bufs_to_post * PI_RCV_DATA_K_SIZE_MAX);
	curr_p += (bp->rcv_bufs_to_post * PI_RCV_DATA_K_SIZE_MAX);
#पूर्ण_अगर

	/* Reserve space क्रम the consumer block */

	bp->cons_block_virt = (PI_CONSUMER_BLOCK *) curr_v;
	bp->cons_block_phys = curr_p;

	/* Display भव and physical addresses अगर debug driver */

	DBG_prपूर्णांकk("%s: Descriptor block virt = %p, phys = %pad\n",
		   prपूर्णांक_name, bp->descr_block_virt, &bp->descr_block_phys);
	DBG_prपूर्णांकk("%s: Command Request buffer virt = %p, phys = %pad\n",
		   prपूर्णांक_name, bp->cmd_req_virt, &bp->cmd_req_phys);
	DBG_prपूर्णांकk("%s: Command Response buffer virt = %p, phys = %pad\n",
		   prपूर्णांक_name, bp->cmd_rsp_virt, &bp->cmd_rsp_phys);
	DBG_prपूर्णांकk("%s: Receive buffer block virt = %p, phys = %pad\n",
		   prपूर्णांक_name, bp->rcv_block_virt, &bp->rcv_block_phys);
	DBG_prपूर्णांकk("%s: Consumer block virt = %p, phys = %pad\n",
		   prपूर्णांक_name, bp->cons_block_virt, &bp->cons_block_phys);

	वापस DFX_K_SUCCESS;
पूर्ण


/*
 * =================
 * = dfx_adap_init =
 * =================
 *
 * Overview:
 *   Brings the adapter to the link avail/link unavailable state.
 *
 * Returns:
 *   Condition code
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *   get_buffers - non-zero अगर buffers to be allocated
 *
 * Functional Description:
 *   Issues the low-level firmware/hardware calls necessary to bring
 *   the adapter up, or to properly reset and restore adapter during
 *   run-समय.
 *
 * Return Codes:
 *   DFX_K_SUCCESS - Adapter brought up successfully
 *   DFX_K_FAILURE - Adapter initialization failed
 *
 * Assumptions:
 *   bp->reset_type should be set to a valid reset type value beक्रमe
 *   calling this routine.
 *
 * Side Effects:
 *   Adapter should be in LINK_AVAILABLE or LINK_UNAVAILABLE state
 *   upon a successful वापस of this routine.
 */

अटल पूर्णांक dfx_adap_init(DFX_board_t *bp, पूर्णांक get_buffers)
	अणु
	DBG_prपूर्णांकk("In dfx_adap_init...\n");

	/* Disable PDQ पूर्णांकerrupts first */

	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_HOST_INT_ENB, PI_HOST_INT_K_DISABLE_ALL_INTS);

	/* Place adapter in DMA_UNAVAILABLE state by resetting adapter */

	अगर (dfx_hw_dma_uninit(bp, bp->reset_type) != DFX_K_SUCCESS)
		अणु
		prपूर्णांकk("%s: Could not uninitialize/reset adapter!\n", bp->dev->name);
		वापस DFX_K_FAILURE;
		पूर्ण

	/*
	 * When the PDQ is reset, some false Type 0 पूर्णांकerrupts may be pending,
	 * so we'll acknowledge all Type 0 पूर्णांकerrupts now beक्रमe continuing.
	 */

	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_TYPE_0_STATUS, PI_HOST_INT_K_ACK_ALL_TYPE_0);

	/*
	 * Clear Type 1 and Type 2 रेजिस्टरs beक्रमe going to DMA_AVAILABLE state
	 *
	 * Note: We only need to clear host copies of these रेजिस्टरs.  The PDQ reset
	 *       takes care of the on-board रेजिस्टर values.
	 */

	bp->cmd_req_reg.lword	= 0;
	bp->cmd_rsp_reg.lword	= 0;
	bp->rcv_xmt_reg.lword	= 0;

	/* Clear consumer block beक्रमe going to DMA_AVAILABLE state */

	स_रखो(bp->cons_block_virt, 0, माप(PI_CONSUMER_BLOCK));

	/* Initialize the DMA Burst Size */

	अगर (dfx_hw_port_ctrl_req(bp,
							PI_PCTRL_M_SUB_CMD,
							PI_SUB_CMD_K_BURST_SIZE_SET,
							bp->burst_size,
							शून्य) != DFX_K_SUCCESS)
		अणु
		prपूर्णांकk("%s: Could not set adapter burst size!\n", bp->dev->name);
		वापस DFX_K_FAILURE;
		पूर्ण

	/*
	 * Set base address of Consumer Block
	 *
	 * Assumption: 32-bit physical address of consumer block is 64 byte
	 *			   aligned.  That is, bits 0-5 of the address must be zero.
	 */

	अगर (dfx_hw_port_ctrl_req(bp,
							PI_PCTRL_M_CONS_BLOCK,
							bp->cons_block_phys,
							0,
							शून्य) != DFX_K_SUCCESS)
		अणु
		prपूर्णांकk("%s: Could not set consumer block address!\n", bp->dev->name);
		वापस DFX_K_FAILURE;
		पूर्ण

	/*
	 * Set the base address of Descriptor Block and bring adapter
	 * to DMA_AVAILABLE state.
	 *
	 * Note: We also set the literal and data swapping requirements
	 *       in this command.
	 *
	 * Assumption: 32-bit physical address of descriptor block
	 *       is 8Kbyte aligned.
	 */
	अगर (dfx_hw_port_ctrl_req(bp, PI_PCTRL_M_INIT,
				 (u32)(bp->descr_block_phys |
				       PI_PDATA_A_INIT_M_BSWAP_INIT),
				 0, शून्य) != DFX_K_SUCCESS) अणु
		prपूर्णांकk("%s: Could not set descriptor block address!\n",
		       bp->dev->name);
		वापस DFX_K_FAILURE;
	पूर्ण

	/* Set transmit flush समयout value */

	bp->cmd_req_virt->cmd_type = PI_CMD_K_CHARS_SET;
	bp->cmd_req_virt->अक्षर_set.item[0].item_code	= PI_ITEM_K_FLUSH_TIME;
	bp->cmd_req_virt->अक्षर_set.item[0].value		= 3;	/* 3 seconds */
	bp->cmd_req_virt->अक्षर_set.item[0].item_index	= 0;
	bp->cmd_req_virt->अक्षर_set.item[1].item_code	= PI_ITEM_K_EOL;
	अगर (dfx_hw_dma_cmd_req(bp) != DFX_K_SUCCESS)
		अणु
		prपूर्णांकk("%s: DMA command request failed!\n", bp->dev->name);
		वापस DFX_K_FAILURE;
		पूर्ण

	/* Set the initial values क्रम eFDXEnable and MACTReq MIB objects */

	bp->cmd_req_virt->cmd_type = PI_CMD_K_SNMP_SET;
	bp->cmd_req_virt->snmp_set.item[0].item_code	= PI_ITEM_K_FDX_ENB_DIS;
	bp->cmd_req_virt->snmp_set.item[0].value		= bp->full_duplex_enb;
	bp->cmd_req_virt->snmp_set.item[0].item_index	= 0;
	bp->cmd_req_virt->snmp_set.item[1].item_code	= PI_ITEM_K_MAC_T_REQ;
	bp->cmd_req_virt->snmp_set.item[1].value		= bp->req_ttrt;
	bp->cmd_req_virt->snmp_set.item[1].item_index	= 0;
	bp->cmd_req_virt->snmp_set.item[2].item_code	= PI_ITEM_K_EOL;
	अगर (dfx_hw_dma_cmd_req(bp) != DFX_K_SUCCESS)
		अणु
		prपूर्णांकk("%s: DMA command request failed!\n", bp->dev->name);
		वापस DFX_K_FAILURE;
		पूर्ण

	/* Initialize adapter CAM */

	अगर (dfx_ctl_update_cam(bp) != DFX_K_SUCCESS)
		अणु
		prपूर्णांकk("%s: Adapter CAM update failed!\n", bp->dev->name);
		वापस DFX_K_FAILURE;
		पूर्ण

	/* Initialize adapter filters */

	अगर (dfx_ctl_update_filters(bp) != DFX_K_SUCCESS)
		अणु
		prपूर्णांकk("%s: Adapter filters update failed!\n", bp->dev->name);
		वापस DFX_K_FAILURE;
		पूर्ण

	/*
	 * Remove any existing dynamic buffers (i.e. अगर the adapter is being
	 * reinitialized)
	 */

	अगर (get_buffers)
		dfx_rcv_flush(bp);

	/* Initialize receive descriptor block and produce buffers */

	अगर (dfx_rcv_init(bp, get_buffers))
	        अणु
		prपूर्णांकk("%s: Receive buffer allocation failed\n", bp->dev->name);
		अगर (get_buffers)
			dfx_rcv_flush(bp);
		वापस DFX_K_FAILURE;
		पूर्ण

	/* Issue START command and bring adapter to LINK_(UN)AVAILABLE state */

	bp->cmd_req_virt->cmd_type = PI_CMD_K_START;
	अगर (dfx_hw_dma_cmd_req(bp) != DFX_K_SUCCESS)
		अणु
		prपूर्णांकk("%s: Start command failed\n", bp->dev->name);
		अगर (get_buffers)
			dfx_rcv_flush(bp);
		वापस DFX_K_FAILURE;
		पूर्ण

	/* Initialization succeeded, reenable PDQ पूर्णांकerrupts */

	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_HOST_INT_ENB, PI_HOST_INT_K_ENABLE_DEF_INTS);
	वापस DFX_K_SUCCESS;
	पूर्ण


/*
 * ============
 * = dfx_खोलो =
 * ============
 *
 * Overview:
 *   Opens the adapter
 *
 * Returns:
 *   Condition code
 *
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   This function brings the adapter to an operational state.
 *
 * Return Codes:
 *   0		 - Adapter was successfully खोलोed
 *   -EAGAIN - Could not रेजिस्टर IRQ or adapter initialization failed
 *
 * Assumptions:
 *   This routine should only be called क्रम a device that was
 *   initialized successfully.
 *
 * Side Effects:
 *   Adapter should be in LINK_AVAILABLE or LINK_UNAVAILABLE state
 *   अगर the खोलो is successful.
 */

अटल पूर्णांक dfx_खोलो(काष्ठा net_device *dev)
अणु
	DFX_board_t *bp = netdev_priv(dev);
	पूर्णांक ret;

	DBG_prपूर्णांकk("In dfx_open...\n");

	/* Register IRQ - support shared पूर्णांकerrupts by passing device ptr */

	ret = request_irq(dev->irq, dfx_पूर्णांकerrupt, IRQF_SHARED, dev->name,
			  dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: Requested IRQ %d is busy\n", dev->name, dev->irq);
		वापस ret;
	पूर्ण

	/*
	 * Set current address to factory MAC address
	 *
	 * Note: We've alपढ़ोy करोne this step in dfx_driver_init.
	 *       However, it's possible that a user has set a node
	 *		 address override, then बंदd and reखोलोed the
	 *		 adapter.  Unless we reset the device address field
	 *		 now, we'll जारी to use the existing modअगरied
	 *		 address.
	 */

	स_नकल(dev->dev_addr, bp->factory_mac_addr, FDDI_K_ALEN);

	/* Clear local unicast/multicast address tables and counts */

	स_रखो(bp->uc_table, 0, माप(bp->uc_table));
	स_रखो(bp->mc_table, 0, माप(bp->mc_table));
	bp->uc_count = 0;
	bp->mc_count = 0;

	/* Disable promiscuous filter settings */

	bp->ind_group_prom	= PI_FSTATE_K_BLOCK;
	bp->group_prom		= PI_FSTATE_K_BLOCK;

	spin_lock_init(&bp->lock);

	/* Reset and initialize adapter */

	bp->reset_type = PI_PDATA_A_RESET_M_SKIP_ST;	/* skip self-test */
	अगर (dfx_adap_init(bp, 1) != DFX_K_SUCCESS)
	अणु
		prपूर्णांकk(KERN_ERR "%s: Adapter open failed!\n", dev->name);
		मुक्त_irq(dev->irq, dev);
		वापस -EAGAIN;
	पूर्ण

	/* Set device काष्ठाure info */
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण


/*
 * =============
 * = dfx_बंद =
 * =============
 *
 * Overview:
 *   Closes the device/module.
 *
 * Returns:
 *   Condition code
 *
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   This routine बंदs the adapter and brings it to a safe state.
 *   The पूर्णांकerrupt service routine is deरेजिस्टरed with the OS.
 *   The adapter can be खोलोed again with another call to dfx_खोलो().
 *
 * Return Codes:
 *   Always वापस 0.
 *
 * Assumptions:
 *   No further requests क्रम this adapter are made after this routine is
 *   called.  dfx_खोलो() can be called to reset and reinitialize the
 *   adapter.
 *
 * Side Effects:
 *   Adapter should be in DMA_UNAVAILABLE state upon completion of this
 *   routine.
 */

अटल पूर्णांक dfx_बंद(काष्ठा net_device *dev)
अणु
	DFX_board_t *bp = netdev_priv(dev);

	DBG_prपूर्णांकk("In dfx_close...\n");

	/* Disable PDQ पूर्णांकerrupts first */

	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_HOST_INT_ENB, PI_HOST_INT_K_DISABLE_ALL_INTS);

	/* Place adapter in DMA_UNAVAILABLE state by resetting adapter */

	(व्योम) dfx_hw_dma_uninit(bp, PI_PDATA_A_RESET_M_SKIP_ST);

	/*
	 * Flush any pending transmit buffers
	 *
	 * Note: It's important that we flush the transmit buffers
	 *		 BEFORE we clear our copy of the Type 2 रेजिस्टर.
	 *		 Otherwise, we'll have no idea how many buffers
	 *		 we need to मुक्त.
	 */

	dfx_xmt_flush(bp);

	/*
	 * Clear Type 1 and Type 2 रेजिस्टरs after adapter reset
	 *
	 * Note: Even though we're closing the adapter, it's
	 *       possible that an पूर्णांकerrupt will occur after
	 *		 dfx_बंद is called.  Without some assurance to
	 *		 the contrary we want to make sure that we करोn't
	 *		 process receive and transmit LLC frames and update
	 *		 the Type 2 रेजिस्टर with bad inक्रमmation.
	 */

	bp->cmd_req_reg.lword	= 0;
	bp->cmd_rsp_reg.lword	= 0;
	bp->rcv_xmt_reg.lword	= 0;

	/* Clear consumer block क्रम the same reason given above */

	स_रखो(bp->cons_block_virt, 0, माप(PI_CONSUMER_BLOCK));

	/* Release all dynamically allocate skb in the receive ring. */

	dfx_rcv_flush(bp);

	/* Clear device काष्ठाure flags */

	netअगर_stop_queue(dev);

	/* Deरेजिस्टर (मुक्त) IRQ */

	मुक्त_irq(dev->irq, dev);

	वापस 0;
पूर्ण


/*
 * ======================
 * = dfx_पूर्णांक_pr_halt_id =
 * ======================
 *
 * Overview:
 *   Displays halt id's in string क्रमm.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   Determine current halt id and display appropriate string.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   None
 *
 * Side Effects:
 *   None
 */

अटल व्योम dfx_पूर्णांक_pr_halt_id(DFX_board_t	*bp)
	अणु
	PI_UINT32	port_status;			/* PDQ port status रेजिस्टर value */
	PI_UINT32	halt_id;				/* PDQ port status halt ID */

	/* Read the latest port status */

	dfx_port_पढ़ो_दीर्घ(bp, PI_PDQ_K_REG_PORT_STATUS, &port_status);

	/* Display halt state transition inक्रमmation */

	halt_id = (port_status & PI_PSTATUS_M_HALT_ID) >> PI_PSTATUS_V_HALT_ID;
	चयन (halt_id)
		अणु
		हाल PI_HALT_ID_K_SELFTEST_TIMEOUT:
			prपूर्णांकk("%s: Halt ID: Selftest Timeout\n", bp->dev->name);
			अवरोध;

		हाल PI_HALT_ID_K_PARITY_ERROR:
			prपूर्णांकk("%s: Halt ID: Host Bus Parity Error\n", bp->dev->name);
			अवरोध;

		हाल PI_HALT_ID_K_HOST_सूची_HALT:
			prपूर्णांकk("%s: Halt ID: Host-Directed Halt\n", bp->dev->name);
			अवरोध;

		हाल PI_HALT_ID_K_SW_FAULT:
			prपूर्णांकk("%s: Halt ID: Adapter Software Fault\n", bp->dev->name);
			अवरोध;

		हाल PI_HALT_ID_K_HW_FAULT:
			prपूर्णांकk("%s: Halt ID: Adapter Hardware Fault\n", bp->dev->name);
			अवरोध;

		हाल PI_HALT_ID_K_PC_TRACE:
			prपूर्णांकk("%s: Halt ID: FDDI Network PC Trace Path Test\n", bp->dev->name);
			अवरोध;

		हाल PI_HALT_ID_K_DMA_ERROR:
			prपूर्णांकk("%s: Halt ID: Adapter DMA Error\n", bp->dev->name);
			अवरोध;

		हाल PI_HALT_ID_K_IMAGE_CRC_ERROR:
			prपूर्णांकk("%s: Halt ID: Firmware Image CRC Error\n", bp->dev->name);
			अवरोध;

		हाल PI_HALT_ID_K_BUS_EXCEPTION:
			prपूर्णांकk("%s: Halt ID: 68000 Bus Exception\n", bp->dev->name);
			अवरोध;

		शेष:
			prपूर्णांकk("%s: Halt ID: Unknown (code = %X)\n", bp->dev->name, halt_id);
			अवरोध;
		पूर्ण
	पूर्ण


/*
 * ==========================
 * = dfx_पूर्णांक_type_0_process =
 * ==========================
 *
 * Overview:
 *   Processes Type 0 पूर्णांकerrupts.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   Processes all enabled Type 0 पूर्णांकerrupts.  If the reason क्रम the पूर्णांकerrupt
 *   is a serious fault on the adapter, then an error message is displayed
 *   and the adapter is reset.
 *
 *   One tricky potential timing winकरोw is the rapid succession of "link avail"
 *   "link unavail" state change पूर्णांकerrupts.  The acknowledgement of the Type 0
 *   पूर्णांकerrupt must be करोne beक्रमe पढ़ोing the state from the Port Status
 *   रेजिस्टर.  This is true because a state change could occur after पढ़ोing
 *   the data, but beक्रमe acknowledging the पूर्णांकerrupt.  If this state change
 *   करोes happen, it would be lost because the driver is using the old state,
 *   and it will never know about the new state because it subsequently
 *   acknowledges the state change पूर्णांकerrupt.
 *
 *          INCORRECT                                      CORRECT
 *      पढ़ो type 0 पूर्णांक reasons                   पढ़ो type 0 पूर्णांक reasons
 *      पढ़ो adapter state                        ack type 0 पूर्णांकerrupts
 *      ack type 0 पूर्णांकerrupts                     पढ़ो adapter state
 *      ... process पूर्णांकerrupt ...                 ... process पूर्णांकerrupt ...
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   None
 *
 * Side Effects:
 *   An adapter reset may occur अगर the adapter has any Type 0 error पूर्णांकerrupts
 *   or अगर the port status indicates that the adapter is halted.  The driver
 *   is responsible क्रम reinitializing the adapter with the current CAM
 *   contents and adapter filter settings.
 */

अटल व्योम dfx_पूर्णांक_type_0_process(DFX_board_t	*bp)

	अणु
	PI_UINT32	type_0_status;		/* Host Interrupt Type 0 रेजिस्टर */
	PI_UINT32	state;				/* current adap state (from port status) */

	/*
	 * Read host पूर्णांकerrupt Type 0 रेजिस्टर to determine which Type 0
	 * पूर्णांकerrupts are pending.  Immediately ग_लिखो it back out to clear
	 * those पूर्णांकerrupts.
	 */

	dfx_port_पढ़ो_दीर्घ(bp, PI_PDQ_K_REG_TYPE_0_STATUS, &type_0_status);
	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_TYPE_0_STATUS, type_0_status);

	/* Check क्रम Type 0 error पूर्णांकerrupts */

	अगर (type_0_status & (PI_TYPE_0_STAT_M_NXM |
							PI_TYPE_0_STAT_M_PM_PAR_ERR |
							PI_TYPE_0_STAT_M_BUS_PAR_ERR))
		अणु
		/* Check क्रम Non-Existent Memory error */

		अगर (type_0_status & PI_TYPE_0_STAT_M_NXM)
			prपूर्णांकk("%s: Non-Existent Memory Access Error\n", bp->dev->name);

		/* Check क्रम Packet Memory Parity error */

		अगर (type_0_status & PI_TYPE_0_STAT_M_PM_PAR_ERR)
			prपूर्णांकk("%s: Packet Memory Parity Error\n", bp->dev->name);

		/* Check क्रम Host Bus Parity error */

		अगर (type_0_status & PI_TYPE_0_STAT_M_BUS_PAR_ERR)
			prपूर्णांकk("%s: Host Bus Parity Error\n", bp->dev->name);

		/* Reset adapter and bring it back on-line */

		bp->link_available = PI_K_FALSE;	/* link is no दीर्घer available */
		bp->reset_type = 0;					/* rerun on-board diagnostics */
		prपूर्णांकk("%s: Resetting adapter...\n", bp->dev->name);
		अगर (dfx_adap_init(bp, 0) != DFX_K_SUCCESS)
			अणु
			prपूर्णांकk("%s: Adapter reset failed!  Disabling adapter interrupts.\n", bp->dev->name);
			dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_HOST_INT_ENB, PI_HOST_INT_K_DISABLE_ALL_INTS);
			वापस;
			पूर्ण
		prपूर्णांकk("%s: Adapter reset successful!\n", bp->dev->name);
		वापस;
		पूर्ण

	/* Check क्रम transmit flush पूर्णांकerrupt */

	अगर (type_0_status & PI_TYPE_0_STAT_M_XMT_FLUSH)
		अणु
		/* Flush any pending xmt's and acknowledge the flush पूर्णांकerrupt */

		bp->link_available = PI_K_FALSE;		/* link is no दीर्घer available */
		dfx_xmt_flush(bp);						/* flush any outstanding packets */
		(व्योम) dfx_hw_port_ctrl_req(bp,
									PI_PCTRL_M_XMT_DATA_FLUSH_DONE,
									0,
									0,
									शून्य);
		पूर्ण

	/* Check क्रम adapter state change */

	अगर (type_0_status & PI_TYPE_0_STAT_M_STATE_CHANGE)
		अणु
		/* Get latest adapter state */

		state = dfx_hw_adap_state_rd(bp);	/* get adapter state */
		अगर (state == PI_STATE_K_HALTED)
			अणु
			/*
			 * Adapter has transitioned to HALTED state, try to reset
			 * adapter to bring it back on-line.  If reset fails,
			 * leave the adapter in the broken state.
			 */

			prपूर्णांकk("%s: Controller has transitioned to HALTED state!\n", bp->dev->name);
			dfx_पूर्णांक_pr_halt_id(bp);			/* display halt id as string */

			/* Reset adapter and bring it back on-line */

			bp->link_available = PI_K_FALSE;	/* link is no दीर्घer available */
			bp->reset_type = 0;					/* rerun on-board diagnostics */
			prपूर्णांकk("%s: Resetting adapter...\n", bp->dev->name);
			अगर (dfx_adap_init(bp, 0) != DFX_K_SUCCESS)
				अणु
				prपूर्णांकk("%s: Adapter reset failed!  Disabling adapter interrupts.\n", bp->dev->name);
				dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_HOST_INT_ENB, PI_HOST_INT_K_DISABLE_ALL_INTS);
				वापस;
				पूर्ण
			prपूर्णांकk("%s: Adapter reset successful!\n", bp->dev->name);
			पूर्ण
		अन्यथा अगर (state == PI_STATE_K_LINK_AVAIL)
			अणु
			bp->link_available = PI_K_TRUE;		/* set link available flag */
			पूर्ण
		पूर्ण
	पूर्ण


/*
 * ==================
 * = dfx_पूर्णांक_common =
 * ==================
 *
 * Overview:
 *   Interrupt service routine (ISR)
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   This is the ISR which processes incoming adapter पूर्णांकerrupts.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   This routine assumes PDQ पूर्णांकerrupts have not been disabled.
 *   When पूर्णांकerrupts are disabled at the PDQ, the Port Status रेजिस्टर
 *   is स्वतःmatically cleared.  This routine uses the Port Status
 *   रेजिस्टर value to determine whether a Type 0 पूर्णांकerrupt occurred,
 *   so it's important that adapter पूर्णांकerrupts are not normally
 *   enabled/disabled at the PDQ.
 *
 *   It's vital that this routine is NOT reentered क्रम the
 *   same board and that the OS is not in another section of
 *   code (eg. dfx_xmt_queue_pkt) क्रम the same board on a
 *   dअगरferent thपढ़ो.
 *
 * Side Effects:
 *   Pending पूर्णांकerrupts are serviced.  Depending on the type of
 *   पूर्णांकerrupt, acknowledging and clearing the पूर्णांकerrupt at the
 *   PDQ involves writing a रेजिस्टर to clear the पूर्णांकerrupt bit
 *   or updating completion indices.
 */

अटल व्योम dfx_पूर्णांक_common(काष्ठा net_device *dev)
अणु
	DFX_board_t *bp = netdev_priv(dev);
	PI_UINT32	port_status;		/* Port Status रेजिस्टर */

	/* Process xmt पूर्णांकerrupts - frequent हाल, so always call this routine */

	अगर(dfx_xmt_करोne(bp))				/* मुक्त consumed xmt packets */
		netअगर_wake_queue(dev);

	/* Process rcv पूर्णांकerrupts - frequent हाल, so always call this routine */

	dfx_rcv_queue_process(bp);		/* service received LLC frames */

	/*
	 * Transmit and receive producer and completion indices are updated on the
	 * adapter by writing to the Type 2 Producer रेजिस्टर.  Since the frequent
	 * हाल is that we'll be processing either LLC transmit or receive buffers,
	 * we'll optimize I/O ग_लिखोs by करोing a single रेजिस्टर ग_लिखो here.
	 */

	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_TYPE_2_PROD, bp->rcv_xmt_reg.lword);

	/* Read PDQ Port Status रेजिस्टर to find out which पूर्णांकerrupts need processing */

	dfx_port_पढ़ो_दीर्घ(bp, PI_PDQ_K_REG_PORT_STATUS, &port_status);

	/* Process Type 0 पूर्णांकerrupts (अगर any) - infrequent, so only call when needed */

	अगर (port_status & PI_PSTATUS_M_TYPE_0_PENDING)
		dfx_पूर्णांक_type_0_process(bp);	/* process Type 0 पूर्णांकerrupts */
	पूर्ण


/*
 * =================
 * = dfx_पूर्णांकerrupt =
 * =================
 *
 * Overview:
 *   Interrupt processing routine
 *
 * Returns:
 *   Whether a valid पूर्णांकerrupt was seen.
 *
 * Arguments:
 *   irq	- पूर्णांकerrupt vector
 *   dev_id	- poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   This routine calls the पूर्णांकerrupt processing routine क्रम this adapter.  It
 *   disables and reenables adapter पूर्णांकerrupts, as appropriate.  We can support
 *   shared पूर्णांकerrupts since the incoming dev_id poपूर्णांकer provides our device
 *   काष्ठाure context.
 *
 * Return Codes:
 *   IRQ_HANDLED - an IRQ was handled.
 *   IRQ_NONE    - no IRQ was handled.
 *
 * Assumptions:
 *   The पूर्णांकerrupt acknowledgement at the hardware level (eg. ACKing the PIC
 *   on Intel-based प्रणालीs) is करोne by the operating प्रणाली outside this
 *   routine.
 *
 *	 System पूर्णांकerrupts are enabled through this call.
 *
 * Side Effects:
 *   Interrupts are disabled, then reenabled at the adapter.
 */

अटल irqवापस_t dfx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	DFX_board_t *bp = netdev_priv(dev);
	काष्ठा device *bdev = bp->bus_dev;
	पूर्णांक dfx_bus_pci = dev_is_pci(bdev);
	पूर्णांक dfx_bus_eisa = DFX_BUS_EISA(bdev);
	पूर्णांक dfx_bus_tc = DFX_BUS_TC(bdev);

	/* Service adapter पूर्णांकerrupts */

	अगर (dfx_bus_pci) अणु
		u32 status;

		dfx_port_पढ़ो_दीर्घ(bp, PFI_K_REG_STATUS, &status);
		अगर (!(status & PFI_STATUS_M_PDQ_INT))
			वापस IRQ_NONE;

		spin_lock(&bp->lock);

		/* Disable PDQ-PFI पूर्णांकerrupts at PFI */
		dfx_port_ग_लिखो_दीर्घ(bp, PFI_K_REG_MODE_CTRL,
				    PFI_MODE_M_DMA_ENB);

		/* Call पूर्णांकerrupt service routine क्रम this adapter */
		dfx_पूर्णांक_common(dev);

		/* Clear PDQ पूर्णांकerrupt status bit and reenable पूर्णांकerrupts */
		dfx_port_ग_लिखो_दीर्घ(bp, PFI_K_REG_STATUS,
				    PFI_STATUS_M_PDQ_INT);
		dfx_port_ग_लिखो_दीर्घ(bp, PFI_K_REG_MODE_CTRL,
				    (PFI_MODE_M_PDQ_INT_ENB |
				     PFI_MODE_M_DMA_ENB));

		spin_unlock(&bp->lock);
	पूर्ण
	अगर (dfx_bus_eisa) अणु
		अचिन्हित दीर्घ base_addr = to_eisa_device(bdev)->base_addr;
		u8 status;

		status = inb(base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);
		अगर (!(status & PI_CONFIG_STAT_0_M_PEND))
			वापस IRQ_NONE;

		spin_lock(&bp->lock);

		/* Disable पूर्णांकerrupts at the ESIC */
		status &= ~PI_CONFIG_STAT_0_M_INT_ENB;
		outb(status, base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);

		/* Call पूर्णांकerrupt service routine क्रम this adapter */
		dfx_पूर्णांक_common(dev);

		/* Reenable पूर्णांकerrupts at the ESIC */
		status = inb(base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);
		status |= PI_CONFIG_STAT_0_M_INT_ENB;
		outb(status, base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);

		spin_unlock(&bp->lock);
	पूर्ण
	अगर (dfx_bus_tc) अणु
		u32 status;

		dfx_port_पढ़ो_दीर्घ(bp, PI_PDQ_K_REG_PORT_STATUS, &status);
		अगर (!(status & (PI_PSTATUS_M_RCV_DATA_PENDING |
				PI_PSTATUS_M_XMT_DATA_PENDING |
				PI_PSTATUS_M_SMT_HOST_PENDING |
				PI_PSTATUS_M_UNSOL_PENDING |
				PI_PSTATUS_M_CMD_RSP_PENDING |
				PI_PSTATUS_M_CMD_REQ_PENDING |
				PI_PSTATUS_M_TYPE_0_PENDING)))
			वापस IRQ_NONE;

		spin_lock(&bp->lock);

		/* Call पूर्णांकerrupt service routine क्रम this adapter */
		dfx_पूर्णांक_common(dev);

		spin_unlock(&bp->lock);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण


/*
 * =====================
 * = dfx_ctl_get_stats =
 * =====================
 *
 * Overview:
 *   Get statistics क्रम FDDI adapter
 *
 * Returns:
 *   Poपूर्णांकer to FDDI statistics काष्ठाure
 *
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   Gets current MIB objects from adapter, then
 *   वापसs FDDI statistics काष्ठाure as defined
 *   in अगर_fddi.h.
 *
 *   Note: Since the FDDI statistics काष्ठाure is
 *   still new and the device काष्ठाure करोesn't
 *   have an FDDI-specअगरic get statistics handler,
 *   we'll वापस the FDDI statistics काष्ठाure as
 *   a poपूर्णांकer to an Ethernet statistics काष्ठाure.
 *   That way, at least the first part of the statistics
 *   काष्ठाure can be decoded properly, and it allows
 *   "smart" applications to perक्रमm a second cast to
 *   decode the FDDI-specअगरic statistics.
 *
 *   We'll have to pay attention to this routine as the
 *   device काष्ठाure becomes more mature and LAN media
 *   independent.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   None
 *
 * Side Effects:
 *   None
 */

अटल काष्ठा net_device_stats *dfx_ctl_get_stats(काष्ठा net_device *dev)
	अणु
	DFX_board_t *bp = netdev_priv(dev);

	/* Fill the bp->stats काष्ठाure with driver-मुख्यtained counters */

	bp->stats.gen.rx_packets = bp->rcv_total_frames;
	bp->stats.gen.tx_packets = bp->xmt_total_frames;
	bp->stats.gen.rx_bytes   = bp->rcv_total_bytes;
	bp->stats.gen.tx_bytes   = bp->xmt_total_bytes;
	bp->stats.gen.rx_errors  = bp->rcv_crc_errors +
				   bp->rcv_frame_status_errors +
				   bp->rcv_length_errors;
	bp->stats.gen.tx_errors  = bp->xmt_length_errors;
	bp->stats.gen.rx_dropped = bp->rcv_discards;
	bp->stats.gen.tx_dropped = bp->xmt_discards;
	bp->stats.gen.multicast  = bp->rcv_multicast_frames;
	bp->stats.gen.collisions = 0;		/* always zero (0) क्रम FDDI */

	/* Get FDDI SMT MIB objects */

	bp->cmd_req_virt->cmd_type = PI_CMD_K_SMT_MIB_GET;
	अगर (dfx_hw_dma_cmd_req(bp) != DFX_K_SUCCESS)
		वापस (काष्ठा net_device_stats *)&bp->stats;

	/* Fill the bp->stats काष्ठाure with the SMT MIB object values */

	स_नकल(bp->stats.smt_station_id, &bp->cmd_rsp_virt->smt_mib_get.smt_station_id, माप(bp->cmd_rsp_virt->smt_mib_get.smt_station_id));
	bp->stats.smt_op_version_id					= bp->cmd_rsp_virt->smt_mib_get.smt_op_version_id;
	bp->stats.smt_hi_version_id					= bp->cmd_rsp_virt->smt_mib_get.smt_hi_version_id;
	bp->stats.smt_lo_version_id					= bp->cmd_rsp_virt->smt_mib_get.smt_lo_version_id;
	स_नकल(bp->stats.smt_user_data, &bp->cmd_rsp_virt->smt_mib_get.smt_user_data, माप(bp->cmd_rsp_virt->smt_mib_get.smt_user_data));
	bp->stats.smt_mib_version_id				= bp->cmd_rsp_virt->smt_mib_get.smt_mib_version_id;
	bp->stats.smt_mac_cts						= bp->cmd_rsp_virt->smt_mib_get.smt_mac_ct;
	bp->stats.smt_non_master_cts				= bp->cmd_rsp_virt->smt_mib_get.smt_non_master_ct;
	bp->stats.smt_master_cts					= bp->cmd_rsp_virt->smt_mib_get.smt_master_ct;
	bp->stats.smt_available_paths				= bp->cmd_rsp_virt->smt_mib_get.smt_available_paths;
	bp->stats.smt_config_capabilities			= bp->cmd_rsp_virt->smt_mib_get.smt_config_capabilities;
	bp->stats.smt_config_policy					= bp->cmd_rsp_virt->smt_mib_get.smt_config_policy;
	bp->stats.smt_connection_policy				= bp->cmd_rsp_virt->smt_mib_get.smt_connection_policy;
	bp->stats.smt_t_notअगरy						= bp->cmd_rsp_virt->smt_mib_get.smt_t_notअगरy;
	bp->stats.smt_stat_rpt_policy				= bp->cmd_rsp_virt->smt_mib_get.smt_stat_rpt_policy;
	bp->stats.smt_trace_max_expiration			= bp->cmd_rsp_virt->smt_mib_get.smt_trace_max_expiration;
	bp->stats.smt_bypass_present				= bp->cmd_rsp_virt->smt_mib_get.smt_bypass_present;
	bp->stats.smt_ecm_state						= bp->cmd_rsp_virt->smt_mib_get.smt_ecm_state;
	bp->stats.smt_cf_state						= bp->cmd_rsp_virt->smt_mib_get.smt_cf_state;
	bp->stats.smt_remote_disconnect_flag		= bp->cmd_rsp_virt->smt_mib_get.smt_remote_disconnect_flag;
	bp->stats.smt_station_status				= bp->cmd_rsp_virt->smt_mib_get.smt_station_status;
	bp->stats.smt_peer_wrap_flag				= bp->cmd_rsp_virt->smt_mib_get.smt_peer_wrap_flag;
	bp->stats.smt_समय_stamp					= bp->cmd_rsp_virt->smt_mib_get.smt_msg_समय_stamp.ls;
	bp->stats.smt_transition_समय_stamp			= bp->cmd_rsp_virt->smt_mib_get.smt_transition_समय_stamp.ls;
	bp->stats.mac_frame_status_functions		= bp->cmd_rsp_virt->smt_mib_get.mac_frame_status_functions;
	bp->stats.mac_t_max_capability				= bp->cmd_rsp_virt->smt_mib_get.mac_t_max_capability;
	bp->stats.mac_tvx_capability				= bp->cmd_rsp_virt->smt_mib_get.mac_tvx_capability;
	bp->stats.mac_available_paths				= bp->cmd_rsp_virt->smt_mib_get.mac_available_paths;
	bp->stats.mac_current_path					= bp->cmd_rsp_virt->smt_mib_get.mac_current_path;
	स_नकल(bp->stats.mac_upstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_upstream_nbr, FDDI_K_ALEN);
	स_नकल(bp->stats.mac_करोwnstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_करोwnstream_nbr, FDDI_K_ALEN);
	स_नकल(bp->stats.mac_old_upstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_old_upstream_nbr, FDDI_K_ALEN);
	स_नकल(bp->stats.mac_old_करोwnstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_old_करोwnstream_nbr, FDDI_K_ALEN);
	bp->stats.mac_dup_address_test				= bp->cmd_rsp_virt->smt_mib_get.mac_dup_address_test;
	bp->stats.mac_requested_paths				= bp->cmd_rsp_virt->smt_mib_get.mac_requested_paths;
	bp->stats.mac_करोwnstream_port_type			= bp->cmd_rsp_virt->smt_mib_get.mac_करोwnstream_port_type;
	स_नकल(bp->stats.mac_smt_address, &bp->cmd_rsp_virt->smt_mib_get.mac_smt_address, FDDI_K_ALEN);
	bp->stats.mac_t_req							= bp->cmd_rsp_virt->smt_mib_get.mac_t_req;
	bp->stats.mac_t_neg							= bp->cmd_rsp_virt->smt_mib_get.mac_t_neg;
	bp->stats.mac_t_max							= bp->cmd_rsp_virt->smt_mib_get.mac_t_max;
	bp->stats.mac_tvx_value						= bp->cmd_rsp_virt->smt_mib_get.mac_tvx_value;
	bp->stats.mac_frame_error_threshold			= bp->cmd_rsp_virt->smt_mib_get.mac_frame_error_threshold;
	bp->stats.mac_frame_error_ratio				= bp->cmd_rsp_virt->smt_mib_get.mac_frame_error_ratio;
	bp->stats.mac_rmt_state						= bp->cmd_rsp_virt->smt_mib_get.mac_rmt_state;
	bp->stats.mac_da_flag						= bp->cmd_rsp_virt->smt_mib_get.mac_da_flag;
	bp->stats.mac_una_da_flag					= bp->cmd_rsp_virt->smt_mib_get.mac_unda_flag;
	bp->stats.mac_frame_error_flag				= bp->cmd_rsp_virt->smt_mib_get.mac_frame_error_flag;
	bp->stats.mac_ma_unitdata_available			= bp->cmd_rsp_virt->smt_mib_get.mac_ma_unitdata_available;
	bp->stats.mac_hardware_present				= bp->cmd_rsp_virt->smt_mib_get.mac_hardware_present;
	bp->stats.mac_ma_unitdata_enable			= bp->cmd_rsp_virt->smt_mib_get.mac_ma_unitdata_enable;
	bp->stats.path_tvx_lower_bound				= bp->cmd_rsp_virt->smt_mib_get.path_tvx_lower_bound;
	bp->stats.path_t_max_lower_bound			= bp->cmd_rsp_virt->smt_mib_get.path_t_max_lower_bound;
	bp->stats.path_max_t_req					= bp->cmd_rsp_virt->smt_mib_get.path_max_t_req;
	स_नकल(bp->stats.path_configuration, &bp->cmd_rsp_virt->smt_mib_get.path_configuration, माप(bp->cmd_rsp_virt->smt_mib_get.path_configuration));
	bp->stats.port_my_type[0]					= bp->cmd_rsp_virt->smt_mib_get.port_my_type[0];
	bp->stats.port_my_type[1]					= bp->cmd_rsp_virt->smt_mib_get.port_my_type[1];
	bp->stats.port_neighbor_type[0]				= bp->cmd_rsp_virt->smt_mib_get.port_neighbor_type[0];
	bp->stats.port_neighbor_type[1]				= bp->cmd_rsp_virt->smt_mib_get.port_neighbor_type[1];
	bp->stats.port_connection_policies[0]		= bp->cmd_rsp_virt->smt_mib_get.port_connection_policies[0];
	bp->stats.port_connection_policies[1]		= bp->cmd_rsp_virt->smt_mib_get.port_connection_policies[1];
	bp->stats.port_mac_indicated[0]				= bp->cmd_rsp_virt->smt_mib_get.port_mac_indicated[0];
	bp->stats.port_mac_indicated[1]				= bp->cmd_rsp_virt->smt_mib_get.port_mac_indicated[1];
	bp->stats.port_current_path[0]				= bp->cmd_rsp_virt->smt_mib_get.port_current_path[0];
	bp->stats.port_current_path[1]				= bp->cmd_rsp_virt->smt_mib_get.port_current_path[1];
	स_नकल(&bp->stats.port_requested_paths[0*3], &bp->cmd_rsp_virt->smt_mib_get.port_requested_paths[0], 3);
	स_नकल(&bp->stats.port_requested_paths[1*3], &bp->cmd_rsp_virt->smt_mib_get.port_requested_paths[1], 3);
	bp->stats.port_mac_placement[0]				= bp->cmd_rsp_virt->smt_mib_get.port_mac_placement[0];
	bp->stats.port_mac_placement[1]				= bp->cmd_rsp_virt->smt_mib_get.port_mac_placement[1];
	bp->stats.port_available_paths[0]			= bp->cmd_rsp_virt->smt_mib_get.port_available_paths[0];
	bp->stats.port_available_paths[1]			= bp->cmd_rsp_virt->smt_mib_get.port_available_paths[1];
	bp->stats.port_pmd_class[0]					= bp->cmd_rsp_virt->smt_mib_get.port_pmd_class[0];
	bp->stats.port_pmd_class[1]					= bp->cmd_rsp_virt->smt_mib_get.port_pmd_class[1];
	bp->stats.port_connection_capabilities[0]	= bp->cmd_rsp_virt->smt_mib_get.port_connection_capabilities[0];
	bp->stats.port_connection_capabilities[1]	= bp->cmd_rsp_virt->smt_mib_get.port_connection_capabilities[1];
	bp->stats.port_bs_flag[0]					= bp->cmd_rsp_virt->smt_mib_get.port_bs_flag[0];
	bp->stats.port_bs_flag[1]					= bp->cmd_rsp_virt->smt_mib_get.port_bs_flag[1];
	bp->stats.port_ler_estimate[0]				= bp->cmd_rsp_virt->smt_mib_get.port_ler_estimate[0];
	bp->stats.port_ler_estimate[1]				= bp->cmd_rsp_virt->smt_mib_get.port_ler_estimate[1];
	bp->stats.port_ler_cutoff[0]				= bp->cmd_rsp_virt->smt_mib_get.port_ler_cutoff[0];
	bp->stats.port_ler_cutoff[1]				= bp->cmd_rsp_virt->smt_mib_get.port_ler_cutoff[1];
	bp->stats.port_ler_alarm[0]					= bp->cmd_rsp_virt->smt_mib_get.port_ler_alarm[0];
	bp->stats.port_ler_alarm[1]					= bp->cmd_rsp_virt->smt_mib_get.port_ler_alarm[1];
	bp->stats.port_connect_state[0]				= bp->cmd_rsp_virt->smt_mib_get.port_connect_state[0];
	bp->stats.port_connect_state[1]				= bp->cmd_rsp_virt->smt_mib_get.port_connect_state[1];
	bp->stats.port_pcm_state[0]					= bp->cmd_rsp_virt->smt_mib_get.port_pcm_state[0];
	bp->stats.port_pcm_state[1]					= bp->cmd_rsp_virt->smt_mib_get.port_pcm_state[1];
	bp->stats.port_pc_withhold[0]				= bp->cmd_rsp_virt->smt_mib_get.port_pc_withhold[0];
	bp->stats.port_pc_withhold[1]				= bp->cmd_rsp_virt->smt_mib_get.port_pc_withhold[1];
	bp->stats.port_ler_flag[0]					= bp->cmd_rsp_virt->smt_mib_get.port_ler_flag[0];
	bp->stats.port_ler_flag[1]					= bp->cmd_rsp_virt->smt_mib_get.port_ler_flag[1];
	bp->stats.port_hardware_present[0]			= bp->cmd_rsp_virt->smt_mib_get.port_hardware_present[0];
	bp->stats.port_hardware_present[1]			= bp->cmd_rsp_virt->smt_mib_get.port_hardware_present[1];

	/* Get FDDI counters */

	bp->cmd_req_virt->cmd_type = PI_CMD_K_CNTRS_GET;
	अगर (dfx_hw_dma_cmd_req(bp) != DFX_K_SUCCESS)
		वापस (काष्ठा net_device_stats *)&bp->stats;

	/* Fill the bp->stats काष्ठाure with the FDDI counter values */

	bp->stats.mac_frame_cts				= bp->cmd_rsp_virt->cntrs_get.cntrs.frame_cnt.ls;
	bp->stats.mac_copied_cts			= bp->cmd_rsp_virt->cntrs_get.cntrs.copied_cnt.ls;
	bp->stats.mac_transmit_cts			= bp->cmd_rsp_virt->cntrs_get.cntrs.transmit_cnt.ls;
	bp->stats.mac_error_cts				= bp->cmd_rsp_virt->cntrs_get.cntrs.error_cnt.ls;
	bp->stats.mac_lost_cts				= bp->cmd_rsp_virt->cntrs_get.cntrs.lost_cnt.ls;
	bp->stats.port_lct_fail_cts[0]		= bp->cmd_rsp_virt->cntrs_get.cntrs.lct_rejects[0].ls;
	bp->stats.port_lct_fail_cts[1]		= bp->cmd_rsp_virt->cntrs_get.cntrs.lct_rejects[1].ls;
	bp->stats.port_lem_reject_cts[0]	= bp->cmd_rsp_virt->cntrs_get.cntrs.lem_rejects[0].ls;
	bp->stats.port_lem_reject_cts[1]	= bp->cmd_rsp_virt->cntrs_get.cntrs.lem_rejects[1].ls;
	bp->stats.port_lem_cts[0]			= bp->cmd_rsp_virt->cntrs_get.cntrs.link_errors[0].ls;
	bp->stats.port_lem_cts[1]			= bp->cmd_rsp_virt->cntrs_get.cntrs.link_errors[1].ls;

	वापस (काष्ठा net_device_stats *)&bp->stats;
	पूर्ण


/*
 * ==============================
 * = dfx_ctl_set_multicast_list =
 * ==============================
 *
 * Overview:
 *   Enable/Disable LLC frame promiscuous mode reception
 *   on the adapter and/or update multicast address table.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   This routine follows a fairly simple algorithm क्रम setting the
 *   adapter filters and CAM:
 *
 *		अगर IFF_PROMISC flag is set
 *			enable LLC inभागidual/group promiscuous mode
 *		अन्यथा
 *			disable LLC inभागidual/group promiscuous mode
 *			अगर number of incoming multicast addresses >
 *					(CAM max size - number of unicast addresses in CAM)
 *				enable LLC group promiscuous mode
 *				set driver-मुख्यtained multicast address count to zero
 *			अन्यथा
 *				disable LLC group promiscuous mode
 *				set driver-मुख्यtained multicast address count to incoming count
 *			update adapter CAM
 *		update adapter filters
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   Multicast addresses are presented in canonical (LSB) क्रमmat.
 *
 * Side Effects:
 *   On-board adapter CAM and filters are updated.
 */

अटल व्योम dfx_ctl_set_multicast_list(काष्ठा net_device *dev)
अणु
	DFX_board_t *bp = netdev_priv(dev);
	पूर्णांक					i;			/* used as index in क्रम loop */
	काष्ठा netdev_hw_addr *ha;

	/* Enable LLC frame promiscuous mode, अगर necessary */

	अगर (dev->flags & IFF_PROMISC)
		bp->ind_group_prom = PI_FSTATE_K_PASS;		/* Enable LLC ind/group prom mode */

	/* Else, update multicast address table */

	अन्यथा
		अणु
		bp->ind_group_prom = PI_FSTATE_K_BLOCK;		/* Disable LLC ind/group prom mode */
		/*
		 * Check whether incoming multicast address count exceeds table size
		 *
		 * Note: The adapters utilize an on-board 64 entry CAM क्रम
		 *       supporting perfect filtering of multicast packets
		 *		 and bridge functions when adding unicast addresses.
		 *		 There is no hash function available.  To support
		 *		 additional multicast addresses, the all multicast
		 *		 filter (LLC group promiscuous mode) must be enabled.
		 *
		 *		 The firmware reserves two CAM entries क्रम SMT-related
		 *		 multicast addresses, which leaves 62 entries available.
		 *		 The following code ensures that we're not being asked
		 *		 to add more than 62 addresses to the CAM.  If we are,
		 *		 the driver will enable the all multicast filter.
		 *		 Should the number of multicast addresses drop below
		 *		 the high water mark, the filter will be disabled and
		 *		 perfect filtering will be used.
		 */

		अगर (netdev_mc_count(dev) > (PI_CMD_ADDR_FILTER_K_SIZE - bp->uc_count))
			अणु
			bp->group_prom	= PI_FSTATE_K_PASS;		/* Enable LLC group prom mode */
			bp->mc_count	= 0;					/* Don't add mc addrs to CAM */
			पूर्ण
		अन्यथा
			अणु
			bp->group_prom	= PI_FSTATE_K_BLOCK;	/* Disable LLC group prom mode */
			bp->mc_count	= netdev_mc_count(dev);		/* Add mc addrs to CAM */
			पूर्ण

		/* Copy addresses to multicast address table, then update adapter CAM */

		i = 0;
		netdev_क्रम_each_mc_addr(ha, dev)
			स_नकल(&bp->mc_table[i++ * FDDI_K_ALEN],
			       ha->addr, FDDI_K_ALEN);

		अगर (dfx_ctl_update_cam(bp) != DFX_K_SUCCESS)
			अणु
			DBG_prपूर्णांकk("%s: Could not update multicast address table!\n", dev->name);
			पूर्ण
		अन्यथा
			अणु
			DBG_prपूर्णांकk("%s: Multicast address table updated!  Added %d addresses.\n", dev->name, bp->mc_count);
			पूर्ण
		पूर्ण

	/* Update adapter filters */

	अगर (dfx_ctl_update_filters(bp) != DFX_K_SUCCESS)
		अणु
		DBG_prपूर्णांकk("%s: Could not update adapter filters!\n", dev->name);
		पूर्ण
	अन्यथा
		अणु
		DBG_prपूर्णांकk("%s: Adapter filters updated!\n", dev->name);
		पूर्ण
	पूर्ण


/*
 * ===========================
 * = dfx_ctl_set_mac_address =
 * ===========================
 *
 * Overview:
 *   Add node address override (unicast address) to adapter
 *   CAM and update dev_addr field in device table.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   dev  - poपूर्णांकer to device inक्रमmation
 *   addr - poपूर्णांकer to sockaddr काष्ठाure containing unicast address to add
 *
 * Functional Description:
 *   The adapter supports node address overrides by adding one or more
 *   unicast addresses to the adapter CAM.  This is similar to adding
 *   multicast addresses.  In this routine we'll update the driver and
 *   device काष्ठाures with the new address, then update the adapter CAM
 *   to ensure that the adapter will copy and strip frames destined and
 *   sourced by that address.
 *
 * Return Codes:
 *   Always वापसs zero.
 *
 * Assumptions:
 *   The address poपूर्णांकed to by addr->sa_data is a valid unicast
 *   address and is presented in canonical (LSB) क्रमmat.
 *
 * Side Effects:
 *   On-board adapter CAM is updated.  On-board adapter filters
 *   may be updated.
 */

अटल पूर्णांक dfx_ctl_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
	अणु
	काष्ठा sockaddr	*p_sockaddr = (काष्ठा sockaddr *)addr;
	DFX_board_t *bp = netdev_priv(dev);

	/* Copy unicast address to driver-मुख्यtained काष्ठाs and update count */

	स_नकल(dev->dev_addr, p_sockaddr->sa_data, FDDI_K_ALEN);	/* update device काष्ठा */
	स_नकल(&bp->uc_table[0], p_sockaddr->sa_data, FDDI_K_ALEN);	/* update driver काष्ठा */
	bp->uc_count = 1;

	/*
	 * Verअगरy we're not exceeding the CAM size by adding unicast address
	 *
	 * Note: It's possible that before entering this routine we've
	 *       alपढ़ोy filled the CAM with 62 multicast addresses.
	 *		 Since we need to place the node address override पूर्णांकo
	 *		 the CAM, we have to check to see that we're not
	 *		 exceeding the CAM size.  If we are, we have to enable
	 *		 the LLC group (multicast) promiscuous mode filter as
	 *		 in dfx_ctl_set_multicast_list.
	 */

	अगर ((bp->uc_count + bp->mc_count) > PI_CMD_ADDR_FILTER_K_SIZE)
		अणु
		bp->group_prom	= PI_FSTATE_K_PASS;		/* Enable LLC group prom mode */
		bp->mc_count	= 0;					/* Don't add mc addrs to CAM */

		/* Update adapter filters */

		अगर (dfx_ctl_update_filters(bp) != DFX_K_SUCCESS)
			अणु
			DBG_prपूर्णांकk("%s: Could not update adapter filters!\n", dev->name);
			पूर्ण
		अन्यथा
			अणु
			DBG_prपूर्णांकk("%s: Adapter filters updated!\n", dev->name);
			पूर्ण
		पूर्ण

	/* Update adapter CAM with new unicast address */

	अगर (dfx_ctl_update_cam(bp) != DFX_K_SUCCESS)
		अणु
		DBG_prपूर्णांकk("%s: Could not set new MAC address!\n", dev->name);
		पूर्ण
	अन्यथा
		अणु
		DBG_prपूर्णांकk("%s: Adapter CAM updated with new MAC address\n", dev->name);
		पूर्ण
	वापस 0;			/* always वापस zero */
	पूर्ण


/*
 * ======================
 * = dfx_ctl_update_cam =
 * ======================
 *
 * Overview:
 *   Procedure to update adapter CAM (Content Addressable Memory)
 *   with desired unicast and multicast address entries.
 *
 * Returns:
 *   Condition code
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   Updates adapter CAM with current contents of board काष्ठाure
 *   unicast and multicast address tables.  Since there are only 62
 *   मुक्त entries in CAM, this routine ensures that the command
 *   request buffer is not overrun.
 *
 * Return Codes:
 *   DFX_K_SUCCESS - Request succeeded
 *   DFX_K_FAILURE - Request failed
 *
 * Assumptions:
 *   All addresses being added (unicast and multicast) are in canonical
 *   order.
 *
 * Side Effects:
 *   On-board adapter CAM is updated.
 */

अटल पूर्णांक dfx_ctl_update_cam(DFX_board_t *bp)
	अणु
	पूर्णांक			i;				/* used as index */
	PI_LAN_ADDR	*p_addr;		/* poपूर्णांकer to CAM entry */

	/*
	 * Fill in command request inक्रमmation
	 *
	 * Note: Even though both the unicast and multicast address
	 *       table entries are stored as contiguous 6 byte entries,
	 *		 the firmware address filter set command expects each
	 *		 entry to be two दीर्घwords (8 bytes total).  We must be
	 *		 careful to only copy the six bytes of each unicast and
	 *		 multicast table entry पूर्णांकo each command entry.  This
	 *		 is also why we must first clear the entire command
	 *		 request buffer.
	 */

	स_रखो(bp->cmd_req_virt, 0, PI_CMD_REQ_K_SIZE_MAX);	/* first clear buffer */
	bp->cmd_req_virt->cmd_type = PI_CMD_K_ADDR_FILTER_SET;
	p_addr = &bp->cmd_req_virt->addr_filter_set.entry[0];

	/* Now add unicast addresses to command request buffer, अगर any */

	क्रम (i=0; i < (पूर्णांक)bp->uc_count; i++)
		अणु
		अगर (i < PI_CMD_ADDR_FILTER_K_SIZE)
			अणु
			स_नकल(p_addr, &bp->uc_table[i*FDDI_K_ALEN], FDDI_K_ALEN);
			p_addr++;			/* poपूर्णांक to next command entry */
			पूर्ण
		पूर्ण

	/* Now add multicast addresses to command request buffer, अगर any */

	क्रम (i=0; i < (पूर्णांक)bp->mc_count; i++)
		अणु
		अगर ((i + bp->uc_count) < PI_CMD_ADDR_FILTER_K_SIZE)
			अणु
			स_नकल(p_addr, &bp->mc_table[i*FDDI_K_ALEN], FDDI_K_ALEN);
			p_addr++;			/* poपूर्णांक to next command entry */
			पूर्ण
		पूर्ण

	/* Issue command to update adapter CAM, then वापस */

	अगर (dfx_hw_dma_cmd_req(bp) != DFX_K_SUCCESS)
		वापस DFX_K_FAILURE;
	वापस DFX_K_SUCCESS;
	पूर्ण


/*
 * ==========================
 * = dfx_ctl_update_filters =
 * ==========================
 *
 * Overview:
 *   Procedure to update adapter filters with desired
 *   filter settings.
 *
 * Returns:
 *   Condition code
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   Enables or disables filter using current filter settings.
 *
 * Return Codes:
 *   DFX_K_SUCCESS - Request succeeded.
 *   DFX_K_FAILURE - Request failed.
 *
 * Assumptions:
 *   We must always pass up packets destined to the broadcast
 *   address (FF-FF-FF-FF-FF-FF), so we'll always keep the
 *   broadcast filter enabled.
 *
 * Side Effects:
 *   On-board adapter filters are updated.
 */

अटल पूर्णांक dfx_ctl_update_filters(DFX_board_t *bp)
	अणु
	पूर्णांक	i = 0;					/* used as index */

	/* Fill in command request inक्रमmation */

	bp->cmd_req_virt->cmd_type = PI_CMD_K_FILTERS_SET;

	/* Initialize Broadcast filter - * ALWAYS ENABLED * */

	bp->cmd_req_virt->filter_set.item[i].item_code	= PI_ITEM_K_BROADCAST;
	bp->cmd_req_virt->filter_set.item[i++].value	= PI_FSTATE_K_PASS;

	/* Initialize LLC Inभागidual/Group Promiscuous filter */

	bp->cmd_req_virt->filter_set.item[i].item_code	= PI_ITEM_K_IND_GROUP_PROM;
	bp->cmd_req_virt->filter_set.item[i++].value	= bp->ind_group_prom;

	/* Initialize LLC Group Promiscuous filter */

	bp->cmd_req_virt->filter_set.item[i].item_code	= PI_ITEM_K_GROUP_PROM;
	bp->cmd_req_virt->filter_set.item[i++].value	= bp->group_prom;

	/* Terminate the item code list */

	bp->cmd_req_virt->filter_set.item[i].item_code	= PI_ITEM_K_EOL;

	/* Issue command to update adapter filters, then वापस */

	अगर (dfx_hw_dma_cmd_req(bp) != DFX_K_SUCCESS)
		वापस DFX_K_FAILURE;
	वापस DFX_K_SUCCESS;
	पूर्ण


/*
 * ======================
 * = dfx_hw_dma_cmd_req =
 * ======================
 *
 * Overview:
 *   Sends PDQ DMA command to adapter firmware
 *
 * Returns:
 *   Condition code
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   The command request and response buffers are posted to the adapter in the manner
 *   described in the PDQ Port Specअगरication:
 *
 *		1. Command Response Buffer is posted to adapter.
 *		2. Command Request Buffer is posted to adapter.
 *		3. Command Request consumer index is polled until it indicates that request
 *         buffer has been DMA'd to adapter.
 *		4. Command Response consumer index is polled until it indicates that response
 *         buffer has been DMA'd from adapter.
 *
 *   This ordering ensures that a response buffer is alपढ़ोy available क्रम the firmware
 *   to use once it's करोne processing the request buffer.
 *
 * Return Codes:
 *   DFX_K_SUCCESS	  - DMA command succeeded
 * 	 DFX_K_OUTSTATE   - Adapter is NOT in proper state
 *   DFX_K_HW_TIMEOUT - DMA command समयd out
 *
 * Assumptions:
 *   Command request buffer has alपढ़ोy been filled with desired DMA command.
 *
 * Side Effects:
 *   None
 */

अटल पूर्णांक dfx_hw_dma_cmd_req(DFX_board_t *bp)
	अणु
	पूर्णांक status;			/* adapter status */
	पूर्णांक समयout_cnt;	/* used in क्रम loops */

	/* Make sure the adapter is in a state that we can issue the DMA command in */

	status = dfx_hw_adap_state_rd(bp);
	अगर ((status == PI_STATE_K_RESET)		||
		(status == PI_STATE_K_HALTED)		||
		(status == PI_STATE_K_DMA_UNAVAIL)	||
		(status == PI_STATE_K_UPGRADE))
		वापस DFX_K_OUTSTATE;

	/* Put response buffer on the command response queue */

	bp->descr_block_virt->cmd_rsp[bp->cmd_rsp_reg.index.prod].दीर्घ_0 = (u32) (PI_RCV_DESCR_M_SOP |
			((PI_CMD_RSP_K_SIZE_MAX / PI_ALIGN_K_CMD_RSP_BUFF) << PI_RCV_DESCR_V_SEG_LEN));
	bp->descr_block_virt->cmd_rsp[bp->cmd_rsp_reg.index.prod].दीर्घ_1 = bp->cmd_rsp_phys;

	/* Bump (and wrap) the producer index and ग_लिखो out to रेजिस्टर */

	bp->cmd_rsp_reg.index.prod += 1;
	bp->cmd_rsp_reg.index.prod &= PI_CMD_RSP_K_NUM_ENTRIES-1;
	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_CMD_RSP_PROD, bp->cmd_rsp_reg.lword);

	/* Put request buffer on the command request queue */

	bp->descr_block_virt->cmd_req[bp->cmd_req_reg.index.prod].दीर्घ_0 = (u32) (PI_XMT_DESCR_M_SOP |
			PI_XMT_DESCR_M_EOP | (PI_CMD_REQ_K_SIZE_MAX << PI_XMT_DESCR_V_SEG_LEN));
	bp->descr_block_virt->cmd_req[bp->cmd_req_reg.index.prod].दीर्घ_1 = bp->cmd_req_phys;

	/* Bump (and wrap) the producer index and ग_लिखो out to रेजिस्टर */

	bp->cmd_req_reg.index.prod += 1;
	bp->cmd_req_reg.index.prod &= PI_CMD_REQ_K_NUM_ENTRIES-1;
	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_CMD_REQ_PROD, bp->cmd_req_reg.lword);

	/*
	 * Here we रुको क्रम the command request consumer index to be equal
	 * to the producer, indicating that the adapter has DMAed the request.
	 */

	क्रम (समयout_cnt = 20000; समयout_cnt > 0; समयout_cnt--)
		अणु
		अगर (bp->cmd_req_reg.index.prod == (u8)(bp->cons_block_virt->cmd_req))
			अवरोध;
		udelay(100);			/* रुको क्रम 100 microseconds */
		पूर्ण
	अगर (समयout_cnt == 0)
		वापस DFX_K_HW_TIMEOUT;

	/* Bump (and wrap) the completion index and ग_लिखो out to रेजिस्टर */

	bp->cmd_req_reg.index.comp += 1;
	bp->cmd_req_reg.index.comp &= PI_CMD_REQ_K_NUM_ENTRIES-1;
	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_CMD_REQ_PROD, bp->cmd_req_reg.lword);

	/*
	 * Here we रुको क्रम the command response consumer index to be equal
	 * to the producer, indicating that the adapter has DMAed the response.
	 */

	क्रम (समयout_cnt = 20000; समयout_cnt > 0; समयout_cnt--)
		अणु
		अगर (bp->cmd_rsp_reg.index.prod == (u8)(bp->cons_block_virt->cmd_rsp))
			अवरोध;
		udelay(100);			/* रुको क्रम 100 microseconds */
		पूर्ण
	अगर (समयout_cnt == 0)
		वापस DFX_K_HW_TIMEOUT;

	/* Bump (and wrap) the completion index and ग_लिखो out to रेजिस्टर */

	bp->cmd_rsp_reg.index.comp += 1;
	bp->cmd_rsp_reg.index.comp &= PI_CMD_RSP_K_NUM_ENTRIES-1;
	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_CMD_RSP_PROD, bp->cmd_rsp_reg.lword);
	वापस DFX_K_SUCCESS;
	पूर्ण


/*
 * ========================
 * = dfx_hw_port_ctrl_req =
 * ========================
 *
 * Overview:
 *   Sends PDQ port control command to adapter firmware
 *
 * Returns:
 *   Host data रेजिस्टर value in host_data अगर ptr is not शून्य
 *
 * Arguments:
 *   bp			- poपूर्णांकer to board inक्रमmation
 *	 command	- port control command
 *	 data_a		- port data A रेजिस्टर value
 *	 data_b		- port data B रेजिस्टर value
 *	 host_data	- ptr to host data रेजिस्टर value
 *
 * Functional Description:
 *   Send generic port control command to adapter by writing
 *   to various PDQ port रेजिस्टरs, then polling क्रम completion.
 *
 * Return Codes:
 *   DFX_K_SUCCESS	  - port control command succeeded
 *   DFX_K_HW_TIMEOUT - port control command समयd out
 *
 * Assumptions:
 *   None
 *
 * Side Effects:
 *   None
 */

अटल पूर्णांक dfx_hw_port_ctrl_req(
	DFX_board_t	*bp,
	PI_UINT32	command,
	PI_UINT32	data_a,
	PI_UINT32	data_b,
	PI_UINT32	*host_data
	)

	अणु
	PI_UINT32	port_cmd;		/* Port Control command रेजिस्टर value */
	पूर्णांक			समयout_cnt;	/* used in क्रम loops */

	/* Set Command Error bit in command दीर्घword */

	port_cmd = (PI_UINT32) (command | PI_PCTRL_M_CMD_ERROR);

	/* Issue port command to the adapter */

	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_PORT_DATA_A, data_a);
	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_PORT_DATA_B, data_b);
	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_PORT_CTRL, port_cmd);

	/* Now रुको क्रम command to complete */

	अगर (command == PI_PCTRL_M_BLAST_FLASH)
		समयout_cnt = 600000;	/* set command समयout count to 60 seconds */
	अन्यथा
		समयout_cnt = 20000;	/* set command समयout count to 2 seconds */

	क्रम (; समयout_cnt > 0; समयout_cnt--)
		अणु
		dfx_port_पढ़ो_दीर्घ(bp, PI_PDQ_K_REG_PORT_CTRL, &port_cmd);
		अगर (!(port_cmd & PI_PCTRL_M_CMD_ERROR))
			अवरोध;
		udelay(100);			/* रुको क्रम 100 microseconds */
		पूर्ण
	अगर (समयout_cnt == 0)
		वापस DFX_K_HW_TIMEOUT;

	/*
	 * If the address of host_data is non-zero, assume caller has supplied a
	 * non शून्य poपूर्णांकer, and वापस the contents of the HOST_DATA रेजिस्टर in
	 * it.
	 */

	अगर (host_data != शून्य)
		dfx_port_पढ़ो_दीर्घ(bp, PI_PDQ_K_REG_HOST_DATA, host_data);
	वापस DFX_K_SUCCESS;
	पूर्ण


/*
 * =====================
 * = dfx_hw_adap_reset =
 * =====================
 *
 * Overview:
 *   Resets adapter
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp   - poपूर्णांकer to board inक्रमmation
 *   type - type of reset to perक्रमm
 *
 * Functional Description:
 *   Issue soft reset to adapter by writing to PDQ Port Reset
 *   रेजिस्टर.  Use incoming reset type to tell adapter what
 *   kind of reset operation to perक्रमm.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   This routine merely issues a soft reset to the adapter.
 *   It is expected that after this routine वापसs, the caller
 *   will appropriately poll the Port Status रेजिस्टर क्रम the
 *   adapter to enter the proper state.
 *
 * Side Effects:
 *   Internal adapter रेजिस्टरs are cleared.
 */

अटल व्योम dfx_hw_adap_reset(
	DFX_board_t	*bp,
	PI_UINT32	type
	)

	अणु
	/* Set Reset type and निश्चित reset */

	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_PORT_DATA_A, type);	/* tell adapter type of reset */
	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_PORT_RESET, PI_RESET_M_ASSERT_RESET);

	/* Wait क्रम at least 1 Microsecond according to the spec. We रुको 20 just to be safe */

	udelay(20);

	/* Deनिश्चित reset */

	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_PORT_RESET, 0);
	पूर्ण


/*
 * ========================
 * = dfx_hw_adap_state_rd =
 * ========================
 *
 * Overview:
 *   Returns current adapter state
 *
 * Returns:
 *   Adapter state per PDQ Port Specअगरication
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   Reads PDQ Port Status रेजिस्टर and वापसs adapter state.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   None
 *
 * Side Effects:
 *   None
 */

अटल पूर्णांक dfx_hw_adap_state_rd(DFX_board_t *bp)
	अणु
	PI_UINT32 port_status;		/* Port Status रेजिस्टर value */

	dfx_port_पढ़ो_दीर्घ(bp, PI_PDQ_K_REG_PORT_STATUS, &port_status);
	वापस (port_status & PI_PSTATUS_M_STATE) >> PI_PSTATUS_V_STATE;
	पूर्ण


/*
 * =====================
 * = dfx_hw_dma_uninit =
 * =====================
 *
 * Overview:
 *   Brings adapter to DMA_UNAVAILABLE state
 *
 * Returns:
 *   Condition code
 *
 * Arguments:
 *   bp   - poपूर्णांकer to board inक्रमmation
 *   type - type of reset to perक्रमm
 *
 * Functional Description:
 *   Bring adapter to DMA_UNAVAILABLE state by perक्रमming the following:
 *		1. Set reset type bit in Port Data A Register then reset adapter.
 *		2. Check that adapter is in DMA_UNAVAILABLE state.
 *
 * Return Codes:
 *   DFX_K_SUCCESS	  - adapter is in DMA_UNAVAILABLE state
 *   DFX_K_HW_TIMEOUT - adapter did not reset properly
 *
 * Assumptions:
 *   None
 *
 * Side Effects:
 *   Internal adapter रेजिस्टरs are cleared.
 */

अटल पूर्णांक dfx_hw_dma_uninit(DFX_board_t *bp, PI_UINT32 type)
	अणु
	पूर्णांक समयout_cnt;	/* used in क्रम loops */

	/* Set reset type bit and reset adapter */

	dfx_hw_adap_reset(bp, type);

	/* Now रुको क्रम adapter to enter DMA_UNAVAILABLE state */

	क्रम (समयout_cnt = 100000; समयout_cnt > 0; समयout_cnt--)
		अणु
		अगर (dfx_hw_adap_state_rd(bp) == PI_STATE_K_DMA_UNAVAIL)
			अवरोध;
		udelay(100);					/* रुको क्रम 100 microseconds */
		पूर्ण
	अगर (समयout_cnt == 0)
		वापस DFX_K_HW_TIMEOUT;
	वापस DFX_K_SUCCESS;
	पूर्ण

/*
 *	Align an sk_buff to a boundary घातer of 2
 *
 */
#अगर_घोषित DYNAMIC_BUFFERS
अटल व्योम my_skb_align(काष्ठा sk_buff *skb, पूर्णांक n)
अणु
	अचिन्हित दीर्घ x = (अचिन्हित दीर्घ)skb->data;
	अचिन्हित दीर्घ v;

	v = ALIGN(x, n);	/* Where we want to be */

	skb_reserve(skb, v - x);
पूर्ण
#पूर्ण_अगर

/*
 * ================
 * = dfx_rcv_init =
 * ================
 *
 * Overview:
 *   Produces buffers to adapter LLC Host receive descriptor block
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *   get_buffers - non-zero अगर buffers to be allocated
 *
 * Functional Description:
 *   This routine can be called during dfx_adap_init() or during an adapter
 *	 reset.  It initializes the descriptor block and produces all allocated
 *   LLC Host queue receive buffers.
 *
 * Return Codes:
 *   Return 0 on success or -ENOMEM अगर buffer allocation failed (when using
 *   dynamic buffer allocation). If the buffer allocation failed, the
 *   alपढ़ोy allocated buffers will not be released and the caller should करो
 *   this.
 *
 * Assumptions:
 *   The PDQ has been reset and the adapter and driver मुख्यtained Type 2
 *   रेजिस्टर indices are cleared.
 *
 * Side Effects:
 *   Receive buffers are posted to the adapter LLC queue and the adapter
 *   is notअगरied.
 */

अटल पूर्णांक dfx_rcv_init(DFX_board_t *bp, पूर्णांक get_buffers)
	अणु
	पूर्णांक	i, j;					/* used in क्रम loop */

	/*
	 *  Since each receive buffer is a single fragment of same length, initialize
	 *  first दीर्घword in each receive descriptor क्रम entire LLC Host descriptor
	 *  block.  Also initialize second दीर्घword in each receive descriptor with
	 *  physical address of receive buffer.  We'll always allocate receive
	 *  buffers in घातers of 2 so that we can easily fill the 256 entry descriptor
	 *  block and produce new receive buffers by simply updating the receive
	 *  producer index.
	 *
	 * 	Assumptions:
	 *		To support all shipping versions of PDQ, the receive buffer size
	 *		must be mod 128 in length and the physical address must be 128 byte
	 *		aligned.  In other words, bits 0-6 of the length and address must
	 *		be zero क्रम the following descriptor field entries to be correct on
	 *		all PDQ-based boards.  We guaranteed both requirements during
	 *		driver initialization when we allocated memory क्रम the receive buffers.
	 */

	अगर (get_buffers) अणु
#अगर_घोषित DYNAMIC_BUFFERS
	क्रम (i = 0; i < (पूर्णांक)(bp->rcv_bufs_to_post); i++)
		क्रम (j = 0; (i + j) < (पूर्णांक)PI_RCV_DATA_K_NUM_ENTRIES; j += bp->rcv_bufs_to_post)
		अणु
			काष्ठा sk_buff *newskb;
			dma_addr_t dma_addr;

			newskb = __netdev_alloc_skb(bp->dev, NEW_SKB_SIZE,
						    GFP_NOIO);
			अगर (!newskb)
				वापस -ENOMEM;
			/*
			 * align to 128 bytes क्रम compatibility with
			 * the old EISA boards.
			 */

			my_skb_align(newskb, 128);
			dma_addr = dma_map_single(bp->bus_dev,
						  newskb->data,
						  PI_RCV_DATA_K_SIZE_MAX,
						  DMA_FROM_DEVICE);
			अगर (dma_mapping_error(bp->bus_dev, dma_addr)) अणु
				dev_kमुक्त_skb(newskb);
				वापस -ENOMEM;
			पूर्ण
			bp->descr_block_virt->rcv_data[i + j].दीर्घ_0 =
				(u32)(PI_RCV_DESCR_M_SOP |
				      ((PI_RCV_DATA_K_SIZE_MAX /
					PI_ALIGN_K_RCV_DATA_BUFF) <<
				       PI_RCV_DESCR_V_SEG_LEN));
			bp->descr_block_virt->rcv_data[i + j].दीर्घ_1 =
				(u32)dma_addr;

			/*
			 * p_rcv_buff_va is only used inside the
			 * kernel so we put the skb poपूर्णांकer here.
			 */
			bp->p_rcv_buff_va[i+j] = (अक्षर *) newskb;
		पूर्ण
#अन्यथा
	क्रम (i=0; i < (पूर्णांक)(bp->rcv_bufs_to_post); i++)
		क्रम (j=0; (i + j) < (पूर्णांक)PI_RCV_DATA_K_NUM_ENTRIES; j += bp->rcv_bufs_to_post)
			अणु
			bp->descr_block_virt->rcv_data[i+j].दीर्घ_0 = (u32) (PI_RCV_DESCR_M_SOP |
				((PI_RCV_DATA_K_SIZE_MAX / PI_ALIGN_K_RCV_DATA_BUFF) << PI_RCV_DESCR_V_SEG_LEN));
			bp->descr_block_virt->rcv_data[i+j].दीर्घ_1 = (u32) (bp->rcv_block_phys + (i * PI_RCV_DATA_K_SIZE_MAX));
			bp->p_rcv_buff_va[i+j] = (bp->rcv_block_virt + (i * PI_RCV_DATA_K_SIZE_MAX));
			पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Update receive producer and Type 2 रेजिस्टर */

	bp->rcv_xmt_reg.index.rcv_prod = bp->rcv_bufs_to_post;
	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_TYPE_2_PROD, bp->rcv_xmt_reg.lword);
	वापस 0;
	पूर्ण


/*
 * =========================
 * = dfx_rcv_queue_process =
 * =========================
 *
 * Overview:
 *   Process received LLC frames.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   Received LLC frames are processed until there are no more consumed frames.
 *   Once all frames are processed, the receive buffers are वापसed to the
 *   adapter.  Note that this algorithm fixes the length of समय that can be spent
 *   in this routine, because there are a fixed number of receive buffers to
 *   process and buffers are not produced until this routine निकासs and वापसs
 *   to the ISR.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   None
 *
 * Side Effects:
 *   None
 */

अटल व्योम dfx_rcv_queue_process(
	DFX_board_t *bp
	)

	अणु
	PI_TYPE_2_CONSUMER	*p_type_2_cons;		/* ptr to rcv/xmt consumer block रेजिस्टर */
	अक्षर				*p_buff;			/* ptr to start of packet receive buffer (FMC descriptor) */
	u32					descr, pkt_len;		/* FMC descriptor field and packet length */
	काष्ठा sk_buff		*skb = शून्य;			/* poपूर्णांकer to a sk_buff to hold incoming packet data */

	/* Service all consumed LLC receive frames */

	p_type_2_cons = (PI_TYPE_2_CONSUMER *)(&bp->cons_block_virt->xmt_rcv_data);
	जबतक (bp->rcv_xmt_reg.index.rcv_comp != p_type_2_cons->index.rcv_cons)
		अणु
		/* Process any errors */
		dma_addr_t dma_addr;
		पूर्णांक entry;

		entry = bp->rcv_xmt_reg.index.rcv_comp;
#अगर_घोषित DYNAMIC_BUFFERS
		p_buff = (अक्षर *) (((काष्ठा sk_buff *)bp->p_rcv_buff_va[entry])->data);
#अन्यथा
		p_buff = bp->p_rcv_buff_va[entry];
#पूर्ण_अगर
		dma_addr = bp->descr_block_virt->rcv_data[entry].दीर्घ_1;
		dma_sync_single_क्रम_cpu(bp->bus_dev,
					dma_addr + RCV_BUFF_K_DESCR,
					माप(u32),
					DMA_FROM_DEVICE);
		स_नकल(&descr, p_buff + RCV_BUFF_K_DESCR, माप(u32));

		अगर (descr & PI_FMC_DESCR_M_RCC_FLUSH)
			अणु
			अगर (descr & PI_FMC_DESCR_M_RCC_CRC)
				bp->rcv_crc_errors++;
			अन्यथा
				bp->rcv_frame_status_errors++;
			पूर्ण
		अन्यथा
		अणु
			पूर्णांक rx_in_place = 0;

			/* The frame was received without errors - verअगरy packet length */

			pkt_len = (u32)((descr & PI_FMC_DESCR_M_LEN) >> PI_FMC_DESCR_V_LEN);
			pkt_len -= 4;				/* subtract 4 byte CRC */
			अगर (!IN_RANGE(pkt_len, FDDI_K_LLC_ZLEN, FDDI_K_LLC_LEN))
				bp->rcv_length_errors++;
			अन्यथाअणु
#अगर_घोषित DYNAMIC_BUFFERS
				काष्ठा sk_buff *newskb = शून्य;

				अगर (pkt_len > SKBUFF_RX_COPYBREAK) अणु
					dma_addr_t new_dma_addr;

					newskb = netdev_alloc_skb(bp->dev,
								  NEW_SKB_SIZE);
					अगर (newskb)अणु
						my_skb_align(newskb, 128);
						new_dma_addr = dma_map_single(
								bp->bus_dev,
								newskb->data,
								PI_RCV_DATA_K_SIZE_MAX,
								DMA_FROM_DEVICE);
						अगर (dma_mapping_error(
								bp->bus_dev,
								new_dma_addr)) अणु
							dev_kमुक्त_skb(newskb);
							newskb = शून्य;
						पूर्ण
					पूर्ण
					अगर (newskb) अणु
						rx_in_place = 1;

						skb = (काष्ठा sk_buff *)bp->p_rcv_buff_va[entry];
						dma_unmap_single(bp->bus_dev,
							dma_addr,
							PI_RCV_DATA_K_SIZE_MAX,
							DMA_FROM_DEVICE);
						skb_reserve(skb, RCV_BUFF_K_PADDING);
						bp->p_rcv_buff_va[entry] = (अक्षर *)newskb;
						bp->descr_block_virt->rcv_data[entry].दीर्घ_1 = (u32)new_dma_addr;
					पूर्ण
				पूर्ण
				अगर (!newskb)
#पूर्ण_अगर
					/* Alloc new buffer to pass up,
					 * add room क्रम PRH. */
					skb = netdev_alloc_skb(bp->dev,
							       pkt_len + 3);
				अगर (skb == शून्य)
					अणु
					prपूर्णांकk("%s: Could not allocate receive buffer.  Dropping packet.\n", bp->dev->name);
					bp->rcv_discards++;
					अवरोध;
					पूर्ण
				अन्यथा अणु
					अगर (!rx_in_place) अणु
						/* Receive buffer allocated, pass receive packet up */
						dma_sync_single_क्रम_cpu(
							bp->bus_dev,
							dma_addr +
							RCV_BUFF_K_PADDING,
							pkt_len + 3,
							DMA_FROM_DEVICE);

						skb_copy_to_linear_data(skb,
							       p_buff + RCV_BUFF_K_PADDING,
							       pkt_len + 3);
					पूर्ण

					skb_reserve(skb,3);		/* adjust data field so that it poपूर्णांकs to FC byte */
					skb_put(skb, pkt_len);		/* pass up packet length, NOT including CRC */
					skb->protocol = fddi_type_trans(skb, bp->dev);
					bp->rcv_total_bytes += skb->len;
					netअगर_rx(skb);

					/* Update the rcv counters */
					bp->rcv_total_frames++;
					अगर (*(p_buff + RCV_BUFF_K_DA) & 0x01)
						bp->rcv_multicast_frames++;
				पूर्ण
			पूर्ण
			पूर्ण

		/*
		 * Advance the producer (क्रम recycling) and advance the completion
		 * (क्रम servicing received frames).  Note that it is okay to
		 * advance the producer without checking that it passes the
		 * completion index because they are both advanced at the same
		 * rate.
		 */

		bp->rcv_xmt_reg.index.rcv_prod += 1;
		bp->rcv_xmt_reg.index.rcv_comp += 1;
		पूर्ण
	पूर्ण


/*
 * =====================
 * = dfx_xmt_queue_pkt =
 * =====================
 *
 * Overview:
 *   Queues packets क्रम transmission
 *
 * Returns:
 *   Condition code
 *
 * Arguments:
 *   skb - poपूर्णांकer to sk_buff to queue क्रम transmission
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   Here we assume that an incoming skb transmit request
 *   is contained in a single physically contiguous buffer
 *   in which the भव address of the start of packet
 *   (skb->data) can be converted to a physical address
 *   by using pci_map_single().
 *
 *   Since the adapter architecture requires a three byte
 *   packet request header to prepend the start of packet,
 *   we'll ग_लिखो the three byte field immediately prior to
 *   the FC byte.  This assumption is valid because we've
 *   ensured that dev->hard_header_len includes three pad
 *   bytes.  By posting a single fragment to the adapter,
 *   we'll reduce the number of descriptor fetches and
 *   bus traffic needed to send the request.
 *
 *   Also, we can't free the skb until after it's been DMA'd
 *   out by the adapter, so we'll queue it in the driver and
 *   वापस it in dfx_xmt_करोne.
 *
 * Return Codes:
 *   0 - driver queued packet, link is unavailable, or skbuff was bad
 *	 1 - caller should requeue the sk_buff क्रम later transmission
 *
 * Assumptions:
 *	 First and क्रमemost, we assume the incoming skb poपूर्णांकer
 *   is NOT शून्य and is poपूर्णांकing to a valid sk_buff काष्ठाure.
 *
 *   The outgoing packet is complete, starting with the
 *   frame control byte including the last byte of data,
 *   but NOT including the 4 byte CRC.  We'll let the
 *   adapter hardware generate and append the CRC.
 *
 *   The entire packet is stored in one physically
 *   contiguous buffer which is not cached and whose
 *   32-bit physical address can be determined.
 *
 *   It's vital that this routine is NOT reentered क्रम the
 *   same board and that the OS is not in another section of
 *   code (eg. dfx_पूर्णांक_common) क्रम the same board on a
 *   dअगरferent thपढ़ो.
 *
 * Side Effects:
 *   None
 */

अटल netdev_tx_t dfx_xmt_queue_pkt(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
	अणु
	DFX_board_t		*bp = netdev_priv(dev);
	u8			prod;				/* local transmit producer index */
	PI_XMT_DESCR		*p_xmt_descr;		/* ptr to transmit descriptor block entry */
	XMT_DRIVER_DESCR	*p_xmt_drv_descr;	/* ptr to transmit driver descriptor */
	dma_addr_t		dma_addr;
	अचिन्हित दीर्घ		flags;

	netअगर_stop_queue(dev);

	/*
	 * Verअगरy that incoming transmit request is OK
	 *
	 * Note: The packet size check is consistent with other
	 *		 Linux device drivers, although the correct packet
	 *		 size should be verअगरied beक्रमe calling the
	 *		 transmit routine.
	 */

	अगर (!IN_RANGE(skb->len, FDDI_K_LLC_ZLEN, FDDI_K_LLC_LEN))
	अणु
		prपूर्णांकk("%s: Invalid packet length - %u bytes\n",
			dev->name, skb->len);
		bp->xmt_length_errors++;		/* bump error counter */
		netअगर_wake_queue(dev);
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;			/* वापस "success" */
	पूर्ण
	/*
	 * See अगर adapter link is available, अगर not, मुक्त buffer
	 *
	 * Note: If the link isn't available, मुक्त buffer and वापस 0
	 *		 rather than tell the upper layer to requeue the packet.
	 *		 The methoकरोlogy here is that by the समय the link
	 *		 becomes available, the packet to be sent will be
	 *		 fairly stale.  By simply dropping the packet, the
	 *		 higher layer protocols will eventually समय out
	 *		 रुकोing क्रम response packets which it won't receive.
	 */

	अगर (bp->link_available == PI_K_FALSE)
		अणु
		अगर (dfx_hw_adap_state_rd(bp) == PI_STATE_K_LINK_AVAIL)	/* is link really available? */
			bp->link_available = PI_K_TRUE;		/* अगर so, set flag and जारी */
		अन्यथा
			अणु
			bp->xmt_discards++;					/* bump error counter */
			dev_kमुक्त_skb(skb);		/* मुक्त sk_buff now */
			netअगर_wake_queue(dev);
			वापस NETDEV_TX_OK;		/* वापस "success" */
			पूर्ण
		पूर्ण

	/* Write the three PRH bytes immediately beक्रमe the FC byte */

	skb_push(skb, 3);
	skb->data[0] = DFX_PRH0_BYTE;	/* these byte values are defined */
	skb->data[1] = DFX_PRH1_BYTE;	/* in the Motorola FDDI MAC chip */
	skb->data[2] = DFX_PRH2_BYTE;	/* specअगरication */

	dma_addr = dma_map_single(bp->bus_dev, skb->data, skb->len,
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(bp->bus_dev, dma_addr)) अणु
		skb_pull(skb, 3);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	spin_lock_irqsave(&bp->lock, flags);

	/* Get the current producer and the next मुक्त xmt data descriptor */

	prod		= bp->rcv_xmt_reg.index.xmt_prod;
	p_xmt_descr = &(bp->descr_block_virt->xmt_data[prod]);

	/*
	 * Get poपूर्णांकer to auxiliary queue entry to contain inक्रमmation
	 * क्रम this packet.
	 *
	 * Note: The current xmt producer index will become the
	 *	 current xmt completion index when we complete this
	 *	 packet later on.  So, we'll get the poपूर्णांकer to the
	 *	 next auxiliary queue entry now beक्रमe we bump the
	 *	 producer index.
	 */

	p_xmt_drv_descr = &(bp->xmt_drv_descr_blk[prod++]);	/* also bump producer index */

	/*
	 * Write the descriptor with buffer info and bump producer
	 *
	 * Note: Since we need to start DMA from the packet request
	 *		 header, we'll add 3 bytes to the DMA buffer length,
	 *		 and we'll determine the physical address of the
	 *		 buffer from the PRH, not skb->data.
	 *
	 * Assumptions:
	 *		 1. Packet starts with the frame control (FC) byte
	 *		    at skb->data.
	 *		 2. The 4-byte CRC is not appended to the buffer or
	 *			included in the length.
	 *		 3. Packet length (skb->len) is from FC to end of
	 *			data, inclusive.
	 *		 4. The packet length करोes not exceed the maximum
	 *			FDDI LLC frame length of 4491 bytes.
	 *		 5. The entire packet is contained in a physically
	 *			contiguous, non-cached, locked memory space
	 *			comprised of a single buffer poपूर्णांकed to by
	 *			skb->data.
	 *		 6. The physical address of the start of packet
	 *			can be determined from the भव address
	 *			by using pci_map_single() and is only 32-bits
	 *			wide.
	 */

	p_xmt_descr->दीर्घ_0	= (u32) (PI_XMT_DESCR_M_SOP | PI_XMT_DESCR_M_EOP | ((skb->len) << PI_XMT_DESCR_V_SEG_LEN));
	p_xmt_descr->दीर्घ_1 = (u32)dma_addr;

	/*
	 * Verअगरy that descriptor is actually available
	 *
	 * Note: If descriptor isn't available, वापस 1 which tells
	 *	 the upper layer to requeue the packet क्रम later
	 *	 transmission.
	 *
	 *       We need to ensure that the producer never reaches the
	 *	 completion, except to indicate that the queue is empty.
	 */

	अगर (prod == bp->rcv_xmt_reg.index.xmt_comp)
	अणु
		skb_pull(skb,3);
		spin_unlock_irqrestore(&bp->lock, flags);
		वापस NETDEV_TX_BUSY;	/* requeue packet क्रम later */
	पूर्ण

	/*
	 * Save info क्रम this packet क्रम xmt करोne indication routine
	 *
	 * Normally, we'd save the producer index in the p_xmt_drv_descr
	 * काष्ठाure so that we'd have it handy when we complete this
	 * packet later (in dfx_xmt_करोne).  However, since the current
	 * transmit architecture guarantees a single fragment क्रम the
	 * entire packet, we can simply bump the completion index by
	 * one (1) क्रम each completed packet.
	 *
	 * Note: If this assumption changes and we're presented with
	 *	 an inconsistent number of transmit fragments क्रम packet
	 *	 data, we'll need to modअगरy this code to save the current
	 *	 transmit producer index.
	 */

	p_xmt_drv_descr->p_skb = skb;

	/* Update Type 2 रेजिस्टर */

	bp->rcv_xmt_reg.index.xmt_prod = prod;
	dfx_port_ग_लिखो_दीर्घ(bp, PI_PDQ_K_REG_TYPE_2_PROD, bp->rcv_xmt_reg.lword);
	spin_unlock_irqrestore(&bp->lock, flags);
	netअगर_wake_queue(dev);
	वापस NETDEV_TX_OK;	/* packet queued to adapter */
	पूर्ण


/*
 * ================
 * = dfx_xmt_करोne =
 * ================
 *
 * Overview:
 *   Processes all frames that have been transmitted.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   For all consumed transmit descriptors that have not
 *   yet been completed, we'll मुक्त the skb we were holding
 *   onto using dev_kमुक्त_skb and bump the appropriate
 *   counters.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   The Type 2 रेजिस्टर is not updated in this routine.  It is
 *   assumed that it will be updated in the ISR when dfx_xmt_करोne
 *   वापसs.
 *
 * Side Effects:
 *   None
 */

अटल पूर्णांक dfx_xmt_करोne(DFX_board_t *bp)
	अणु
	XMT_DRIVER_DESCR	*p_xmt_drv_descr;	/* ptr to transmit driver descriptor */
	PI_TYPE_2_CONSUMER	*p_type_2_cons;		/* ptr to rcv/xmt consumer block रेजिस्टर */
	u8			comp;			/* local transmit completion index */
	पूर्णांक 			मुक्तd = 0;		/* buffers मुक्तd */

	/* Service all consumed transmit frames */

	p_type_2_cons = (PI_TYPE_2_CONSUMER *)(&bp->cons_block_virt->xmt_rcv_data);
	जबतक (bp->rcv_xmt_reg.index.xmt_comp != p_type_2_cons->index.xmt_cons)
		अणु
		/* Get poपूर्णांकer to the transmit driver descriptor block inक्रमmation */

		p_xmt_drv_descr = &(bp->xmt_drv_descr_blk[bp->rcv_xmt_reg.index.xmt_comp]);

		/* Increment transmit counters */

		bp->xmt_total_frames++;
		bp->xmt_total_bytes += p_xmt_drv_descr->p_skb->len;

		/* Return skb to operating प्रणाली */
		comp = bp->rcv_xmt_reg.index.xmt_comp;
		dma_unmap_single(bp->bus_dev,
				 bp->descr_block_virt->xmt_data[comp].दीर्घ_1,
				 p_xmt_drv_descr->p_skb->len,
				 DMA_TO_DEVICE);
		dev_consume_skb_irq(p_xmt_drv_descr->p_skb);

		/*
		 * Move to start of next packet by updating completion index
		 *
		 * Here we assume that a transmit packet request is always
		 * serviced by posting one fragment.  We can thereक्रमe
		 * simplअगरy the completion code by incrementing the
		 * completion index by one.  This code will need to be
		 * modअगरied अगर this assumption changes.  See comments
		 * in dfx_xmt_queue_pkt क्रम more details.
		 */

		bp->rcv_xmt_reg.index.xmt_comp += 1;
		मुक्तd++;
		पूर्ण
	वापस मुक्तd;
	पूर्ण


/*
 * =================
 * = dfx_rcv_flush =
 * =================
 *
 * Overview:
 *   Remove all skb's in the receive ring.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   Free's all the dynamically allocated skb's that are
 *   currently attached to the device receive ring. This
 *   function is typically only used when the device is
 *   initialized or reinitialized.
 *
 * Return Codes:
 *   None
 *
 * Side Effects:
 *   None
 */
#अगर_घोषित DYNAMIC_BUFFERS
अटल व्योम dfx_rcv_flush( DFX_board_t *bp )
	अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < (पूर्णांक)(bp->rcv_bufs_to_post); i++)
		क्रम (j = 0; (i + j) < (पूर्णांक)PI_RCV_DATA_K_NUM_ENTRIES; j += bp->rcv_bufs_to_post)
		अणु
			काष्ठा sk_buff *skb;
			skb = (काष्ठा sk_buff *)bp->p_rcv_buff_va[i+j];
			अगर (skb) अणु
				dma_unmap_single(bp->bus_dev,
						 bp->descr_block_virt->rcv_data[i+j].दीर्घ_1,
						 PI_RCV_DATA_K_SIZE_MAX,
						 DMA_FROM_DEVICE);
				dev_kमुक्त_skb(skb);
			पूर्ण
			bp->p_rcv_buff_va[i+j] = शून्य;
		पूर्ण

	पूर्ण
#पूर्ण_अगर /* DYNAMIC_BUFFERS */

/*
 * =================
 * = dfx_xmt_flush =
 * =================
 *
 * Overview:
 *   Processes all frames whether they've been transmitted
 *   or not.
 *
 * Returns:
 *   None
 *
 * Arguments:
 *   bp - poपूर्णांकer to board inक्रमmation
 *
 * Functional Description:
 *   For all produced transmit descriptors that have not
 *   yet been completed, we'll मुक्त the skb we were holding
 *   onto using dev_kमुक्त_skb and bump the appropriate
 *   counters.  Of course, it's possible that some of
 *   these transmit requests actually did go out, but we
 *   won't make that distinction here.  Finally, we'll
 *   update the consumer index to match the producer.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   This routine करोes NOT update the Type 2 रेजिस्टर.  It
 *   is assumed that this routine is being called during a
 *   transmit flush पूर्णांकerrupt, or a shutकरोwn or बंद routine.
 *
 * Side Effects:
 *   None
 */

अटल व्योम dfx_xmt_flush( DFX_board_t *bp )
	अणु
	u32			prod_cons;		/* rcv/xmt consumer block दीर्घword */
	XMT_DRIVER_DESCR	*p_xmt_drv_descr;	/* ptr to transmit driver descriptor */
	u8			comp;			/* local transmit completion index */

	/* Flush all outstanding transmit frames */

	जबतक (bp->rcv_xmt_reg.index.xmt_comp != bp->rcv_xmt_reg.index.xmt_prod)
		अणु
		/* Get poपूर्णांकer to the transmit driver descriptor block inक्रमmation */

		p_xmt_drv_descr = &(bp->xmt_drv_descr_blk[bp->rcv_xmt_reg.index.xmt_comp]);

		/* Return skb to operating प्रणाली */
		comp = bp->rcv_xmt_reg.index.xmt_comp;
		dma_unmap_single(bp->bus_dev,
				 bp->descr_block_virt->xmt_data[comp].दीर्घ_1,
				 p_xmt_drv_descr->p_skb->len,
				 DMA_TO_DEVICE);
		dev_kमुक्त_skb(p_xmt_drv_descr->p_skb);

		/* Increment transmit error counter */

		bp->xmt_discards++;

		/*
		 * Move to start of next packet by updating completion index
		 *
		 * Here we assume that a transmit packet request is always
		 * serviced by posting one fragment.  We can thereक्रमe
		 * simplअगरy the completion code by incrementing the
		 * completion index by one.  This code will need to be
		 * modअगरied अगर this assumption changes.  See comments
		 * in dfx_xmt_queue_pkt क्रम more details.
		 */

		bp->rcv_xmt_reg.index.xmt_comp += 1;
		पूर्ण

	/* Update the transmit consumer index in the consumer block */

	prod_cons = (u32)(bp->cons_block_virt->xmt_rcv_data & ~PI_CONS_M_XMT_INDEX);
	prod_cons |= (u32)(bp->rcv_xmt_reg.index.xmt_prod << PI_CONS_V_XMT_INDEX);
	bp->cons_block_virt->xmt_rcv_data = prod_cons;
	पूर्ण

/*
 * ==================
 * = dfx_unरेजिस्टर =
 * ==================
 *
 * Overview:
 *   Shuts करोwn an FDDI controller
 *
 * Returns:
 *   Condition code
 *
 * Arguments:
 *   bdev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   It compiles so it should work :-( (PCI cards करो :-)
 *
 * Side Effects:
 *   Device काष्ठाures क्रम FDDI adapters (fddi0, fddi1, etc) are
 *   मुक्तd.
 */
अटल व्योम dfx_unरेजिस्टर(काष्ठा device *bdev)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(bdev);
	DFX_board_t *bp = netdev_priv(dev);
	पूर्णांक dfx_bus_pci = dev_is_pci(bdev);
	resource_माप_प्रकार bar_start[3] = अणु0पूर्ण;	/* poपूर्णांकers to ports */
	resource_माप_प्रकार bar_len[3] = अणु0पूर्ण;	/* resource lengths */
	पूर्णांक		alloc_size;		/* total buffer size used */

	unरेजिस्टर_netdev(dev);

	alloc_size = माप(PI_DESCR_BLOCK) +
		     PI_CMD_REQ_K_SIZE_MAX + PI_CMD_RSP_K_SIZE_MAX +
#अगर_अघोषित DYNAMIC_BUFFERS
		     (bp->rcv_bufs_to_post * PI_RCV_DATA_K_SIZE_MAX) +
#पूर्ण_अगर
		     माप(PI_CONSUMER_BLOCK) +
		     (PI_ALIGN_K_DESC_BLK - 1);
	अगर (bp->kदो_स्मृतिed)
		dma_मुक्त_coherent(bdev, alloc_size,
				  bp->kदो_स्मृतिed, bp->kदो_स्मृतिed_dma);

	dfx_bus_uninit(dev);

	dfx_get_bars(bp, bar_start, bar_len);
	अगर (bar_start[2] != 0)
		release_region(bar_start[2], bar_len[2]);
	अगर (bar_start[1] != 0)
		release_region(bar_start[1], bar_len[1]);
	अगर (dfx_use_mmio) अणु
		iounmap(bp->base.mem);
		release_mem_region(bar_start[0], bar_len[0]);
	पूर्ण अन्यथा
		release_region(bar_start[0], bar_len[0]);

	अगर (dfx_bus_pci)
		pci_disable_device(to_pci_dev(bdev));

	मुक्त_netdev(dev);
पूर्ण


अटल पूर्णांक __maybe_unused dfx_dev_रेजिस्टर(काष्ठा device *);
अटल पूर्णांक __maybe_unused dfx_dev_unरेजिस्टर(काष्ठा device *);

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक dfx_pci_रेजिस्टर(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम dfx_pci_unरेजिस्टर(काष्ठा pci_dev *);

अटल स्थिर काष्ठा pci_device_id dfx_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_FDDI) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, dfx_pci_table);

अटल काष्ठा pci_driver dfx_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= dfx_pci_table,
	.probe		= dfx_pci_रेजिस्टर,
	.हटाओ		= dfx_pci_unरेजिस्टर,
पूर्ण;

अटल पूर्णांक dfx_pci_रेजिस्टर(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	वापस dfx_रेजिस्टर(&pdev->dev);
पूर्ण

अटल व्योम dfx_pci_unरेजिस्टर(काष्ठा pci_dev *pdev)
अणु
	dfx_unरेजिस्टर(&pdev->dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

#अगर_घोषित CONFIG_EISA
अटल स्थिर काष्ठा eisa_device_id dfx_eisa_table[] = अणु
        अणु "DEC3001", DEFEA_PROD_ID_1 पूर्ण,
        अणु "DEC3002", DEFEA_PROD_ID_2 पूर्ण,
        अणु "DEC3003", DEFEA_PROD_ID_3 पूर्ण,
        अणु "DEC3004", DEFEA_PROD_ID_4 पूर्ण,
        अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(eisa, dfx_eisa_table);

अटल काष्ठा eisa_driver dfx_eisa_driver = अणु
	.id_table	= dfx_eisa_table,
	.driver		= अणु
		.name	= DRV_NAME,
		.bus	= &eisa_bus_type,
		.probe	= dfx_dev_रेजिस्टर,
		.हटाओ	= dfx_dev_unरेजिस्टर,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_EISA */

#अगर_घोषित CONFIG_TC
अटल काष्ठा tc_device_id स्थिर dfx_tc_table[] = अणु
	अणु "DEC     ", "PMAF-FA " पूर्ण,
	अणु "DEC     ", "PMAF-FD " पूर्ण,
	अणु "DEC     ", "PMAF-FS " पूर्ण,
	अणु "DEC     ", "PMAF-FU " पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(tc, dfx_tc_table);

अटल काष्ठा tc_driver dfx_tc_driver = अणु
	.id_table	= dfx_tc_table,
	.driver		= अणु
		.name	= DRV_NAME,
		.bus	= &tc_bus_type,
		.probe	= dfx_dev_रेजिस्टर,
		.हटाओ	= dfx_dev_unरेजिस्टर,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_TC */

अटल पूर्णांक __maybe_unused dfx_dev_रेजिस्टर(काष्ठा device *dev)
अणु
	पूर्णांक status;

	status = dfx_रेजिस्टर(dev);
	अगर (!status)
		get_device(dev);
	वापस status;
पूर्ण

अटल पूर्णांक __maybe_unused dfx_dev_unरेजिस्टर(काष्ठा device *dev)
अणु
	put_device(dev);
	dfx_unरेजिस्टर(dev);
	वापस 0;
पूर्ण


अटल पूर्णांक dfx_init(व्योम)
अणु
	पूर्णांक status;

	status = pci_रेजिस्टर_driver(&dfx_pci_driver);
	अगर (!status)
		status = eisa_driver_रेजिस्टर(&dfx_eisa_driver);
	अगर (!status)
		status = tc_रेजिस्टर_driver(&dfx_tc_driver);
	वापस status;
पूर्ण

अटल व्योम dfx_cleanup(व्योम)
अणु
	tc_unरेजिस्टर_driver(&dfx_tc_driver);
	eisa_driver_unरेजिस्टर(&dfx_eisa_driver);
	pci_unरेजिस्टर_driver(&dfx_pci_driver);
पूर्ण

module_init(dfx_init);
module_निकास(dfx_cleanup);
MODULE_AUTHOR("Lawrence V. Stefani");
MODULE_DESCRIPTION("DEC FDDIcontroller TC/EISA/PCI (DEFTA/DEFEA/DEFPA) driver "
		   DRV_VERSION " " DRV_RELDATE);
MODULE_LICENSE("GPL");
