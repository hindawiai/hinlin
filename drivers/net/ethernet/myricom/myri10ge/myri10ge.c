<शैली गुरु>
/*************************************************************************
 * myri10ge.c: Myricom Myri-10G Ethernet driver.
 *
 * Copyright (C) 2005 - 2011 Myricom, Inc.
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
 * 3. Neither the name of Myricom, Inc. nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * If the eeprom on your board is not recent enough, you will need to get a
 * newer firmware image at:
 *   http://www.myri.com/scs/करोwnload-Myri10GE.hपंचांगl
 *
 * Contact Inक्रमmation:
 *   <help@myri.com>
 *   Myricom, Inc., 325N Santa Anita Avenue, Arcadia, CA 91006
 *************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/tcp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/dca.h>
#समावेश <linux/ip.h>
#समावेश <linux/inet.h>
#समावेश <linux/in.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/crc32.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/slab.h>
#समावेश <linux/prefetch.h>
#समावेश <net/checksum.h>
#समावेश <net/ip.h>
#समावेश <net/tcp.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/processor.h>

#समावेश "myri10ge_mcp.h"
#समावेश "myri10ge_mcp_gen_header.h"

#घोषणा MYRI10GE_VERSION_STR "1.5.3-1.534"

MODULE_DESCRIPTION("Myricom 10G driver (10GbE)");
MODULE_AUTHOR("Maintainer: help@myri.com");
MODULE_VERSION(MYRI10GE_VERSION_STR);
MODULE_LICENSE("Dual BSD/GPL");

#घोषणा MYRI10GE_MAX_ETHER_MTU 9014

#घोषणा MYRI10GE_ETH_STOPPED 0
#घोषणा MYRI10GE_ETH_STOPPING 1
#घोषणा MYRI10GE_ETH_STARTING 2
#घोषणा MYRI10GE_ETH_RUNNING 3
#घोषणा MYRI10GE_ETH_OPEN_FAILED 4

#घोषणा MYRI10GE_EEPROM_STRINGS_SIZE 256
#घोषणा MYRI10GE_MAX_SEND_DESC_TSO ((65536 / 2048) * 2)

#घोषणा MYRI10GE_NO_CONFIRM_DATA htonl(0xffffffff)
#घोषणा MYRI10GE_NO_RESPONSE_RESULT 0xffffffff

#घोषणा MYRI10GE_ALLOC_ORDER 0
#घोषणा MYRI10GE_ALLOC_SIZE ((1 << MYRI10GE_ALLOC_ORDER) * PAGE_SIZE)
#घोषणा MYRI10GE_MAX_FRAGS_PER_FRAME (MYRI10GE_MAX_ETHER_MTU/MYRI10GE_ALLOC_SIZE + 1)

#घोषणा MYRI10GE_MAX_SLICES 32

काष्ठा myri10ge_rx_buffer_state अणु
	काष्ठा page *page;
	पूर्णांक page_offset;
	DEFINE_DMA_UNMAP_ADDR(bus);
	DEFINE_DMA_UNMAP_LEN(len);
पूर्ण;

काष्ठा myri10ge_tx_buffer_state अणु
	काष्ठा sk_buff *skb;
	पूर्णांक last;
	DEFINE_DMA_UNMAP_ADDR(bus);
	DEFINE_DMA_UNMAP_LEN(len);
पूर्ण;

काष्ठा myri10ge_cmd अणु
	u32 data0;
	u32 data1;
	u32 data2;
पूर्ण;

काष्ठा myri10ge_rx_buf अणु
	काष्ठा mcp_kreq_ether_recv __iomem *lanai;	/* lanai ptr क्रम recv ring */
	काष्ठा mcp_kreq_ether_recv *shaकरोw;	/* host shaकरोw of recv ring */
	काष्ठा myri10ge_rx_buffer_state *info;
	काष्ठा page *page;
	dma_addr_t bus;
	पूर्णांक page_offset;
	पूर्णांक cnt;
	पूर्णांक fill_cnt;
	पूर्णांक alloc_fail;
	पूर्णांक mask;		/* number of rx slots -1 */
	पूर्णांक watchकरोg_needed;
पूर्ण;

काष्ठा myri10ge_tx_buf अणु
	काष्ठा mcp_kreq_ether_send __iomem *lanai;	/* lanai ptr क्रम sendq */
	__be32 __iomem *send_go;	/* "go" करोorbell ptr */
	__be32 __iomem *send_stop;	/* "stop" करोorbell ptr */
	काष्ठा mcp_kreq_ether_send *req_list;	/* host shaकरोw of sendq */
	अक्षर *req_bytes;
	काष्ठा myri10ge_tx_buffer_state *info;
	पूर्णांक mask;		/* number of transmit slots -1  */
	पूर्णांक req ____cacheline_aligned;	/* transmit slots submitted     */
	पूर्णांक pkt_start;		/* packets started */
	पूर्णांक stop_queue;
	पूर्णांक linearized;
	पूर्णांक करोne ____cacheline_aligned;	/* transmit slots completed     */
	पूर्णांक pkt_करोne;		/* packets completed */
	पूर्णांक wake_queue;
	पूर्णांक queue_active;
पूर्ण;

काष्ठा myri10ge_rx_करोne अणु
	काष्ठा mcp_slot *entry;
	dma_addr_t bus;
	पूर्णांक cnt;
	पूर्णांक idx;
पूर्ण;

काष्ठा myri10ge_slice_netstats अणु
	अचिन्हित दीर्घ rx_packets;
	अचिन्हित दीर्घ tx_packets;
	अचिन्हित दीर्घ rx_bytes;
	अचिन्हित दीर्घ tx_bytes;
	अचिन्हित दीर्घ rx_dropped;
	अचिन्हित दीर्घ tx_dropped;
पूर्ण;

काष्ठा myri10ge_slice_state अणु
	काष्ठा myri10ge_tx_buf tx;	/* transmit ring        */
	काष्ठा myri10ge_rx_buf rx_small;
	काष्ठा myri10ge_rx_buf rx_big;
	काष्ठा myri10ge_rx_करोne rx_करोne;
	काष्ठा net_device *dev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा myri10ge_priv *mgp;
	काष्ठा myri10ge_slice_netstats stats;
	__be32 __iomem *irq_claim;
	काष्ठा mcp_irq_data *fw_stats;
	dma_addr_t fw_stats_bus;
	पूर्णांक watchकरोg_tx_करोne;
	पूर्णांक watchकरोg_tx_req;
	पूर्णांक watchकरोg_rx_करोne;
	पूर्णांक stuck;
#अगर_घोषित CONFIG_MYRI10GE_DCA
	पूर्णांक cached_dca_tag;
	पूर्णांक cpu;
	__be32 __iomem *dca_tag;
#पूर्ण_अगर
	अक्षर irq_desc[32];
पूर्ण;

काष्ठा myri10ge_priv अणु
	काष्ठा myri10ge_slice_state *ss;
	पूर्णांक tx_boundary;	/* boundary transmits cannot cross */
	पूर्णांक num_slices;
	पूर्णांक running;		/* running?             */
	पूर्णांक small_bytes;
	पूर्णांक big_bytes;
	पूर्णांक max_पूर्णांकr_slots;
	काष्ठा net_device *dev;
	u8 __iomem *sram;
	पूर्णांक sram_size;
	अचिन्हित दीर्घ board_span;
	अचिन्हित दीर्घ iomem_base;
	__be32 __iomem *irq_deनिश्चित;
	अक्षर *mac_addr_string;
	काष्ठा mcp_cmd_response *cmd;
	dma_addr_t cmd_bus;
	काष्ठा pci_dev *pdev;
	पूर्णांक msi_enabled;
	पूर्णांक msix_enabled;
	काष्ठा msix_entry *msix_vectors;
#अगर_घोषित CONFIG_MYRI10GE_DCA
	पूर्णांक dca_enabled;
	पूर्णांक relaxed_order;
#पूर्ण_अगर
	u32 link_state;
	अचिन्हित पूर्णांक rdma_tags_available;
	पूर्णांक पूर्णांकr_coal_delay;
	__be32 __iomem *पूर्णांकr_coal_delay_ptr;
	पूर्णांक wc_cookie;
	पूर्णांक करोwn_cnt;
	रुको_queue_head_t करोwn_wq;
	काष्ठा work_काष्ठा watchकरोg_work;
	काष्ठा समयr_list watchकरोg_समयr;
	पूर्णांक watchकरोg_resets;
	पूर्णांक watchकरोg_छोड़ो;
	पूर्णांक छोड़ो;
	bool fw_name_allocated;
	अक्षर *fw_name;
	अक्षर eeprom_strings[MYRI10GE_EEPROM_STRINGS_SIZE];
	अक्षर *product_code_string;
	अक्षर fw_version[128];
	पूर्णांक fw_ver_major;
	पूर्णांक fw_ver_minor;
	पूर्णांक fw_ver_tiny;
	पूर्णांक aकरोpted_rx_filter_bug;
	u8 mac_addr[ETH_ALEN];		/* eeprom mac address */
	अचिन्हित दीर्घ serial_number;
	पूर्णांक venकरोr_specअगरic_offset;
	पूर्णांक fw_multicast_support;
	u32 features;
	u32 max_tso6;
	u32 पढ़ो_dma;
	u32 ग_लिखो_dma;
	u32 पढ़ो_ग_लिखो_dma;
	u32 link_changes;
	u32 msg_enable;
	अचिन्हित पूर्णांक board_number;
	पूर्णांक rebooted;
पूर्ण;

अटल अक्षर *myri10ge_fw_unaligned = "myri10ge_ethp_z8e.dat";
अटल अक्षर *myri10ge_fw_aligned = "myri10ge_eth_z8e.dat";
अटल अक्षर *myri10ge_fw_rss_unaligned = "myri10ge_rss_ethp_z8e.dat";
अटल अक्षर *myri10ge_fw_rss_aligned = "myri10ge_rss_eth_z8e.dat";
MODULE_FIRMWARE("myri10ge_ethp_z8e.dat");
MODULE_FIRMWARE("myri10ge_eth_z8e.dat");
MODULE_FIRMWARE("myri10ge_rss_ethp_z8e.dat");
MODULE_FIRMWARE("myri10ge_rss_eth_z8e.dat");

/* Careful: must be accessed under kernel_param_lock() */
अटल अक्षर *myri10ge_fw_name = शून्य;
module_param(myri10ge_fw_name, अक्षरp, 0644);
MODULE_PARM_DESC(myri10ge_fw_name, "Firmware image name");

#घोषणा MYRI10GE_MAX_BOARDS 8
अटल अक्षर *myri10ge_fw_names[MYRI10GE_MAX_BOARDS] =
    अणु[0 ... (MYRI10GE_MAX_BOARDS - 1)] = शून्य पूर्ण;
module_param_array_named(myri10ge_fw_names, myri10ge_fw_names, अक्षरp, शून्य,
			 0444);
MODULE_PARM_DESC(myri10ge_fw_names, "Firmware image names per board");

अटल पूर्णांक myri10ge_ecrc_enable = 1;
module_param(myri10ge_ecrc_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(myri10ge_ecrc_enable, "Enable Extended CRC on PCI-E");

अटल पूर्णांक myri10ge_small_bytes = -1;	/* -1 == स्वतः */
module_param(myri10ge_small_bytes, पूर्णांक, 0644);
MODULE_PARM_DESC(myri10ge_small_bytes, "Threshold of small packets");

अटल पूर्णांक myri10ge_msi = 1;	/* enable msi by शेष */
module_param(myri10ge_msi, पूर्णांक, 0644);
MODULE_PARM_DESC(myri10ge_msi, "Enable Message Signalled Interrupts");

अटल पूर्णांक myri10ge_पूर्णांकr_coal_delay = 75;
module_param(myri10ge_पूर्णांकr_coal_delay, पूर्णांक, 0444);
MODULE_PARM_DESC(myri10ge_पूर्णांकr_coal_delay, "Interrupt coalescing delay");

अटल पूर्णांक myri10ge_flow_control = 1;
module_param(myri10ge_flow_control, पूर्णांक, 0444);
MODULE_PARM_DESC(myri10ge_flow_control, "Pause parameter");

अटल पूर्णांक myri10ge_deनिश्चित_रुको = 1;
module_param(myri10ge_deनिश्चित_रुको, पूर्णांक, 0644);
MODULE_PARM_DESC(myri10ge_deनिश्चित_रुको,
		 "Wait when deasserting legacy interrupts");

अटल पूर्णांक myri10ge_क्रमce_firmware = 0;
module_param(myri10ge_क्रमce_firmware, पूर्णांक, 0444);
MODULE_PARM_DESC(myri10ge_क्रमce_firmware,
		 "Force firmware to assume aligned completions");

अटल पूर्णांक myri10ge_initial_mtu = MYRI10GE_MAX_ETHER_MTU - ETH_HLEN;
module_param(myri10ge_initial_mtu, पूर्णांक, 0444);
MODULE_PARM_DESC(myri10ge_initial_mtu, "Initial MTU");

अटल पूर्णांक myri10ge_napi_weight = 64;
module_param(myri10ge_napi_weight, पूर्णांक, 0444);
MODULE_PARM_DESC(myri10ge_napi_weight, "Set NAPI weight");

अटल पूर्णांक myri10ge_watchकरोg_समयout = 1;
module_param(myri10ge_watchकरोg_समयout, पूर्णांक, 0444);
MODULE_PARM_DESC(myri10ge_watchकरोg_समयout, "Set watchdog timeout");

अटल पूर्णांक myri10ge_max_irq_loops = 1048576;
module_param(myri10ge_max_irq_loops, पूर्णांक, 0444);
MODULE_PARM_DESC(myri10ge_max_irq_loops,
		 "Set stuck legacy IRQ detection threshold");

#घोषणा MYRI10GE_MSG_DEFAULT NETIF_MSG_LINK

अटल पूर्णांक myri10ge_debug = -1;	/* शेषs above */
module_param(myri10ge_debug, पूर्णांक, 0);
MODULE_PARM_DESC(myri10ge_debug, "Debug level (0=none,...,16=all)");

अटल पूर्णांक myri10ge_fill_thresh = 256;
module_param(myri10ge_fill_thresh, पूर्णांक, 0644);
MODULE_PARM_DESC(myri10ge_fill_thresh, "Number of empty rx slots allowed");

अटल पूर्णांक myri10ge_reset_recover = 1;

अटल पूर्णांक myri10ge_max_slices = 1;
module_param(myri10ge_max_slices, पूर्णांक, 0444);
MODULE_PARM_DESC(myri10ge_max_slices, "Max tx/rx queues");

अटल पूर्णांक myri10ge_rss_hash = MXGEFW_RSS_HASH_TYPE_SRC_DST_PORT;
module_param(myri10ge_rss_hash, पूर्णांक, 0444);
MODULE_PARM_DESC(myri10ge_rss_hash, "Type of RSS hashing to do");

अटल पूर्णांक myri10ge_dca = 1;
module_param(myri10ge_dca, पूर्णांक, 0444);
MODULE_PARM_DESC(myri10ge_dca, "Enable DCA if possible");

#घोषणा MYRI10GE_FW_OFFSET 1024*1024
#घोषणा MYRI10GE_HIGHPART_TO_U32(X) \
(माप (X) == 8) ? ((u32)((u64)(X) >> 32)) : (0)
#घोषणा MYRI10GE_LOWPART_TO_U32(X) ((u32)(X))

#घोषणा myri10ge_pio_copy(to,from,size) __ioग_लिखो64_copy(to,from,size/8)

अटल व्योम myri10ge_set_multicast_list(काष्ठा net_device *dev);
अटल netdev_tx_t myri10ge_sw_tso(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev);

अटल अंतरभूत व्योम put_be32(__be32 val, __be32 __iomem * p)
अणु
	__raw_ग_लिखोl((__क्रमce __u32) val, (__क्रमce व्योम __iomem *)p);
पूर्ण

अटल व्योम myri10ge_get_stats(काष्ठा net_device *dev,
			       काष्ठा rtnl_link_stats64 *stats);

अटल व्योम set_fw_name(काष्ठा myri10ge_priv *mgp, अक्षर *name, bool allocated)
अणु
	अगर (mgp->fw_name_allocated)
		kमुक्त(mgp->fw_name);
	mgp->fw_name = name;
	mgp->fw_name_allocated = allocated;
पूर्ण

अटल पूर्णांक
myri10ge_send_cmd(काष्ठा myri10ge_priv *mgp, u32 cmd,
		  काष्ठा myri10ge_cmd *data, पूर्णांक atomic)
अणु
	काष्ठा mcp_cmd *buf;
	अक्षर buf_bytes[माप(*buf) + 8];
	काष्ठा mcp_cmd_response *response = mgp->cmd;
	अक्षर __iomem *cmd_addr = mgp->sram + MXGEFW_ETH_CMD;
	u32 dma_low, dma_high, result, value;
	पूर्णांक sleep_total = 0;

	/* ensure buf is aligned to 8 bytes */
	buf = (काष्ठा mcp_cmd *)ALIGN((अचिन्हित दीर्घ)buf_bytes, 8);

	buf->data0 = htonl(data->data0);
	buf->data1 = htonl(data->data1);
	buf->data2 = htonl(data->data2);
	buf->cmd = htonl(cmd);
	dma_low = MYRI10GE_LOWPART_TO_U32(mgp->cmd_bus);
	dma_high = MYRI10GE_HIGHPART_TO_U32(mgp->cmd_bus);

	buf->response_addr.low = htonl(dma_low);
	buf->response_addr.high = htonl(dma_high);
	response->result = htonl(MYRI10GE_NO_RESPONSE_RESULT);
	mb();
	myri10ge_pio_copy(cmd_addr, buf, माप(*buf));

	/* रुको up to 15ms. Longest command is the DMA benchmark,
	 * which is capped at 5ms, but runs from a समयout handler
	 * that runs every 7.8ms. So a 15ms समयout leaves us with
	 * a 2.2ms margin
	 */
	अगर (atomic) अणु
		/* अगर atomic is set, करो not sleep,
		 * and try to get the completion quickly
		 * (1ms will be enough क्रम those commands) */
		क्रम (sleep_total = 0;
		     sleep_total < 1000 &&
		     response->result == htonl(MYRI10GE_NO_RESPONSE_RESULT);
		     sleep_total += 10) अणु
			udelay(10);
			mb();
		पूर्ण
	पूर्ण अन्यथा अणु
		/* use msleep क्रम most command */
		क्रम (sleep_total = 0;
		     sleep_total < 15 &&
		     response->result == htonl(MYRI10GE_NO_RESPONSE_RESULT);
		     sleep_total++)
			msleep(1);
	पूर्ण

	result = ntohl(response->result);
	value = ntohl(response->data);
	अगर (result != MYRI10GE_NO_RESPONSE_RESULT) अणु
		अगर (result == 0) अणु
			data->data0 = value;
			वापस 0;
		पूर्ण अन्यथा अगर (result == MXGEFW_CMD_UNKNOWN) अणु
			वापस -ENOSYS;
		पूर्ण अन्यथा अगर (result == MXGEFW_CMD_ERROR_UNALIGNED) अणु
			वापस -E2BIG;
		पूर्ण अन्यथा अगर (result == MXGEFW_CMD_ERROR_RANGE &&
			   cmd == MXGEFW_CMD_ENABLE_RSS_QUEUES &&
			   (data->
			    data1 & MXGEFW_SLICE_ENABLE_MULTIPLE_TX_QUEUES) !=
			   0) अणु
			वापस -दुस्फल;
		पूर्ण अन्यथा अणु
			dev_err(&mgp->pdev->dev,
				"command %d failed, result = %d\n",
				cmd, result);
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	dev_err(&mgp->pdev->dev, "command %d timed out, result = %d\n",
		cmd, result);
	वापस -EAGAIN;
पूर्ण

/*
 * The eeprom strings on the lanaiX have the क्रमmat
 * SN=x\0
 * MAC=x:x:x:x:x:x\0
 * PT:ddd mmm xx xx:xx:xx xx\0
 * PV:ddd mmm xx xx:xx:xx xx\0
 */
अटल पूर्णांक myri10ge_पढ़ो_mac_addr(काष्ठा myri10ge_priv *mgp)
अणु
	अक्षर *ptr, *limit;
	पूर्णांक i;

	ptr = mgp->eeprom_strings;
	limit = mgp->eeprom_strings + MYRI10GE_EEPROM_STRINGS_SIZE;

	जबतक (*ptr != '\0' && ptr < limit) अणु
		अगर (स_भेद(ptr, "MAC=", 4) == 0) अणु
			ptr += 4;
			mgp->mac_addr_string = ptr;
			क्रम (i = 0; i < 6; i++) अणु
				अगर ((ptr + 2) > limit)
					जाओ पात;
				mgp->mac_addr[i] =
				    simple_म_से_अदीर्घ(ptr, &ptr, 16);
				ptr += 1;
			पूर्ण
		पूर्ण
		अगर (स_भेद(ptr, "PC=", 3) == 0) अणु
			ptr += 3;
			mgp->product_code_string = ptr;
		पूर्ण
		अगर (स_भेद((स्थिर व्योम *)ptr, "SN=", 3) == 0) अणु
			ptr += 3;
			mgp->serial_number = simple_म_से_अदीर्घ(ptr, &ptr, 10);
		पूर्ण
		जबतक (ptr < limit && *ptr++) ;
	पूर्ण

	वापस 0;

पात:
	dev_err(&mgp->pdev->dev, "failed to parse eeprom_strings\n");
	वापस -ENXIO;
पूर्ण

/*
 * Enable or disable periodic RDMAs from the host to make certain
 * chipsets resend dropped PCIe messages
 */

अटल व्योम myri10ge_dummy_rdma(काष्ठा myri10ge_priv *mgp, पूर्णांक enable)
अणु
	अक्षर __iomem *submit;
	__be32 buf[16] __attribute__ ((__aligned__(8)));
	u32 dma_low, dma_high;
	पूर्णांक i;

	/* clear confirmation addr */
	mgp->cmd->data = 0;
	mb();

	/* send a rdma command to the PCIe engine, and रुको क्रम the
	 * response in the confirmation address.  The firmware should
	 * ग_लिखो a -1 there to indicate it is alive and well
	 */
	dma_low = MYRI10GE_LOWPART_TO_U32(mgp->cmd_bus);
	dma_high = MYRI10GE_HIGHPART_TO_U32(mgp->cmd_bus);

	buf[0] = htonl(dma_high);	/* confirm addr MSW */
	buf[1] = htonl(dma_low);	/* confirm addr LSW */
	buf[2] = MYRI10GE_NO_CONFIRM_DATA;	/* confirm data */
	buf[3] = htonl(dma_high);	/* dummy addr MSW */
	buf[4] = htonl(dma_low);	/* dummy addr LSW */
	buf[5] = htonl(enable);	/* enable? */

	submit = mgp->sram + MXGEFW_BOOT_DUMMY_RDMA;

	myri10ge_pio_copy(submit, &buf, माप(buf));
	क्रम (i = 0; mgp->cmd->data != MYRI10GE_NO_CONFIRM_DATA && i < 20; i++)
		msleep(1);
	अगर (mgp->cmd->data != MYRI10GE_NO_CONFIRM_DATA)
		dev_err(&mgp->pdev->dev, "dummy rdma %s failed\n",
			(enable ? "enable" : "disable"));
पूर्ण

अटल पूर्णांक
myri10ge_validate_firmware(काष्ठा myri10ge_priv *mgp,
			   काष्ठा mcp_gen_header *hdr)
अणु
	काष्ठा device *dev = &mgp->pdev->dev;

	/* check firmware type */
	अगर (ntohl(hdr->mcp_type) != MCP_TYPE_ETH) अणु
		dev_err(dev, "Bad firmware type: 0x%x\n", ntohl(hdr->mcp_type));
		वापस -EINVAL;
	पूर्ण

	/* save firmware version क्रम ethtool */
	म_नकलन(mgp->fw_version, hdr->version, माप(mgp->fw_version));
	mgp->fw_version[माप(mgp->fw_version) - 1] = '\0';

	माला_पूछो(mgp->fw_version, "%d.%d.%d", &mgp->fw_ver_major,
	       &mgp->fw_ver_minor, &mgp->fw_ver_tiny);

	अगर (!(mgp->fw_ver_major == MXGEFW_VERSION_MAJOR &&
	      mgp->fw_ver_minor == MXGEFW_VERSION_MINOR)) अणु
		dev_err(dev, "Found firmware version %s\n", mgp->fw_version);
		dev_err(dev, "Driver needs %d.%d\n", MXGEFW_VERSION_MAJOR,
			MXGEFW_VERSION_MINOR);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक myri10ge_load_hotplug_firmware(काष्ठा myri10ge_priv *mgp, u32 * size)
अणु
	अचिन्हित crc, reपढ़ो_crc;
	स्थिर काष्ठा firmware *fw;
	काष्ठा device *dev = &mgp->pdev->dev;
	अचिन्हित अक्षर *fw_पढ़ोback;
	काष्ठा mcp_gen_header *hdr;
	माप_प्रकार hdr_offset;
	पूर्णांक status;
	अचिन्हित i;

	अगर ((status = request_firmware(&fw, mgp->fw_name, dev)) < 0) अणु
		dev_err(dev, "Unable to load %s firmware image via hotplug\n",
			mgp->fw_name);
		status = -EINVAL;
		जाओ पात_with_nothing;
	पूर्ण

	/* check size */

	अगर (fw->size >= mgp->sram_size - MYRI10GE_FW_OFFSET ||
	    fw->size < MCP_HEADER_PTR_OFFSET + 4) अणु
		dev_err(dev, "Firmware size invalid:%d\n", (पूर्णांक)fw->size);
		status = -EINVAL;
		जाओ पात_with_fw;
	पूर्ण

	/* check id */
	hdr_offset = ntohl(*(__be32 *) (fw->data + MCP_HEADER_PTR_OFFSET));
	अगर ((hdr_offset & 3) || hdr_offset + माप(*hdr) > fw->size) अणु
		dev_err(dev, "Bad firmware file\n");
		status = -EINVAL;
		जाओ पात_with_fw;
	पूर्ण
	hdr = (व्योम *)(fw->data + hdr_offset);

	status = myri10ge_validate_firmware(mgp, hdr);
	अगर (status != 0)
		जाओ पात_with_fw;

	crc = crc32(~0, fw->data, fw->size);
	क्रम (i = 0; i < fw->size; i += 256) अणु
		myri10ge_pio_copy(mgp->sram + MYRI10GE_FW_OFFSET + i,
				  fw->data + i,
				  min(256U, (अचिन्हित)(fw->size - i)));
		mb();
		पढ़ोb(mgp->sram);
	पूर्ण
	fw_पढ़ोback = vदो_स्मृति(fw->size);
	अगर (!fw_पढ़ोback) अणु
		status = -ENOMEM;
		जाओ पात_with_fw;
	पूर्ण
	/* corruption checking is good क्रम parity recovery and buggy chipset */
	स_नकल_fromio(fw_पढ़ोback, mgp->sram + MYRI10GE_FW_OFFSET, fw->size);
	reपढ़ो_crc = crc32(~0, fw_पढ़ोback, fw->size);
	vमुक्त(fw_पढ़ोback);
	अगर (crc != reपढ़ो_crc) अणु
		dev_err(dev, "CRC failed(fw-len=%u), got 0x%x (expect 0x%x)\n",
			(अचिन्हित)fw->size, reपढ़ो_crc, crc);
		status = -EIO;
		जाओ पात_with_fw;
	पूर्ण
	*size = (u32) fw->size;

पात_with_fw:
	release_firmware(fw);

पात_with_nothing:
	वापस status;
पूर्ण

अटल पूर्णांक myri10ge_aकरोpt_running_firmware(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा mcp_gen_header *hdr;
	काष्ठा device *dev = &mgp->pdev->dev;
	स्थिर माप_प्रकार bytes = माप(काष्ठा mcp_gen_header);
	माप_प्रकार hdr_offset;
	पूर्णांक status;

	/* find running firmware header */
	hdr_offset = swab32(पढ़ोl(mgp->sram + MCP_HEADER_PTR_OFFSET));

	अगर ((hdr_offset & 3) || hdr_offset + माप(*hdr) > mgp->sram_size) अणु
		dev_err(dev, "Running firmware has bad header offset (%d)\n",
			(पूर्णांक)hdr_offset);
		वापस -EIO;
	पूर्ण

	/* copy header of running firmware from SRAM to host memory to
	 * validate firmware */
	hdr = kदो_स्मृति(bytes, GFP_KERNEL);
	अगर (hdr == शून्य)
		वापस -ENOMEM;

	स_नकल_fromio(hdr, mgp->sram + hdr_offset, bytes);
	status = myri10ge_validate_firmware(mgp, hdr);
	kमुक्त(hdr);

	/* check to see अगर aकरोpted firmware has bug where aकरोpting
	 * it will cause broadcasts to be filtered unless the NIC
	 * is kept in ALLMULTI mode */
	अगर (mgp->fw_ver_major == 1 && mgp->fw_ver_minor == 4 &&
	    mgp->fw_ver_tiny >= 4 && mgp->fw_ver_tiny <= 11) अणु
		mgp->aकरोpted_rx_filter_bug = 1;
		dev_warn(dev, "Adopting fw %d.%d.%d: "
			 "working around rx filter bug\n",
			 mgp->fw_ver_major, mgp->fw_ver_minor,
			 mgp->fw_ver_tiny);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक myri10ge_get_firmware_capabilities(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा myri10ge_cmd cmd;
	पूर्णांक status;

	/* probe क्रम IPv6 TSO support */
	mgp->features = NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_TSO;
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_MAX_TSO6_HDR_SIZE,
				   &cmd, 0);
	अगर (status == 0) अणु
		mgp->max_tso6 = cmd.data0;
		mgp->features |= NETIF_F_TSO6;
	पूर्ण

	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_RX_RING_SIZE, &cmd, 0);
	अगर (status != 0) अणु
		dev_err(&mgp->pdev->dev,
			"failed MXGEFW_CMD_GET_RX_RING_SIZE\n");
		वापस -ENXIO;
	पूर्ण

	mgp->max_पूर्णांकr_slots = 2 * (cmd.data0 / माप(काष्ठा mcp_dma_addr));

	वापस 0;
पूर्ण

अटल पूर्णांक myri10ge_load_firmware(काष्ठा myri10ge_priv *mgp, पूर्णांक aकरोpt)
अणु
	अक्षर __iomem *submit;
	__be32 buf[16] __attribute__ ((__aligned__(8)));
	u32 dma_low, dma_high, size;
	पूर्णांक status, i;

	size = 0;
	status = myri10ge_load_hotplug_firmware(mgp, &size);
	अगर (status) अणु
		अगर (!aकरोpt)
			वापस status;
		dev_warn(&mgp->pdev->dev, "hotplug firmware loading failed\n");

		/* Do not attempt to aकरोpt firmware अगर there
		 * was a bad crc */
		अगर (status == -EIO)
			वापस status;

		status = myri10ge_aकरोpt_running_firmware(mgp);
		अगर (status != 0) अणु
			dev_err(&mgp->pdev->dev,
				"failed to adopt running firmware\n");
			वापस status;
		पूर्ण
		dev_info(&mgp->pdev->dev,
			 "Successfully adopted running firmware\n");
		अगर (mgp->tx_boundary == 4096) अणु
			dev_warn(&mgp->pdev->dev,
				 "Using firmware currently running on NIC"
				 ".  For optimal\n");
			dev_warn(&mgp->pdev->dev,
				 "performance consider loading optimized "
				 "firmware\n");
			dev_warn(&mgp->pdev->dev, "via hotplug\n");
		पूर्ण

		set_fw_name(mgp, "adopted", false);
		mgp->tx_boundary = 2048;
		myri10ge_dummy_rdma(mgp, 1);
		status = myri10ge_get_firmware_capabilities(mgp);
		वापस status;
	पूर्ण

	/* clear confirmation addr */
	mgp->cmd->data = 0;
	mb();

	/* send a reload command to the bootstrap MCP, and रुको क्रम the
	 *  response in the confirmation address.  The firmware should
	 * ग_लिखो a -1 there to indicate it is alive and well
	 */
	dma_low = MYRI10GE_LOWPART_TO_U32(mgp->cmd_bus);
	dma_high = MYRI10GE_HIGHPART_TO_U32(mgp->cmd_bus);

	buf[0] = htonl(dma_high);	/* confirm addr MSW */
	buf[1] = htonl(dma_low);	/* confirm addr LSW */
	buf[2] = MYRI10GE_NO_CONFIRM_DATA;	/* confirm data */

	/* FIX: All newest firmware should un-protect the bottom of
	 * the sram beक्रमe hanकरोff. However, the very first पूर्णांकerfaces
	 * करो not. Thereक्रमe the hanकरोff copy must skip the first 8 bytes
	 */
	buf[3] = htonl(MYRI10GE_FW_OFFSET + 8);	/* where the code starts */
	buf[4] = htonl(size - 8);	/* length of code */
	buf[5] = htonl(8);	/* where to copy to */
	buf[6] = htonl(0);	/* where to jump to */

	submit = mgp->sram + MXGEFW_BOOT_HANDOFF;

	myri10ge_pio_copy(submit, &buf, माप(buf));
	mb();
	msleep(1);
	mb();
	i = 0;
	जबतक (mgp->cmd->data != MYRI10GE_NO_CONFIRM_DATA && i < 9) अणु
		msleep(1 << i);
		i++;
	पूर्ण
	अगर (mgp->cmd->data != MYRI10GE_NO_CONFIRM_DATA) अणु
		dev_err(&mgp->pdev->dev, "handoff failed\n");
		वापस -ENXIO;
	पूर्ण
	myri10ge_dummy_rdma(mgp, 1);
	status = myri10ge_get_firmware_capabilities(mgp);

	वापस status;
पूर्ण

अटल पूर्णांक myri10ge_update_mac_address(काष्ठा myri10ge_priv *mgp, u8 * addr)
अणु
	काष्ठा myri10ge_cmd cmd;
	पूर्णांक status;

	cmd.data0 = ((addr[0] << 24) | (addr[1] << 16)
		     | (addr[2] << 8) | addr[3]);

	cmd.data1 = ((addr[4] << 8) | (addr[5]));

	status = myri10ge_send_cmd(mgp, MXGEFW_SET_MAC_ADDRESS, &cmd, 0);
	वापस status;
पूर्ण

अटल पूर्णांक myri10ge_change_छोड़ो(काष्ठा myri10ge_priv *mgp, पूर्णांक छोड़ो)
अणु
	काष्ठा myri10ge_cmd cmd;
	पूर्णांक status, ctl;

	ctl = छोड़ो ? MXGEFW_ENABLE_FLOW_CONTROL : MXGEFW_DISABLE_FLOW_CONTROL;
	status = myri10ge_send_cmd(mgp, ctl, &cmd, 0);

	अगर (status) अणु
		netdev_err(mgp->dev, "Failed to set flow control mode\n");
		वापस status;
	पूर्ण
	mgp->छोड़ो = छोड़ो;
	वापस 0;
पूर्ण

अटल व्योम
myri10ge_change_promisc(काष्ठा myri10ge_priv *mgp, पूर्णांक promisc, पूर्णांक atomic)
अणु
	काष्ठा myri10ge_cmd cmd;
	पूर्णांक status, ctl;

	ctl = promisc ? MXGEFW_ENABLE_PROMISC : MXGEFW_DISABLE_PROMISC;
	status = myri10ge_send_cmd(mgp, ctl, &cmd, atomic);
	अगर (status)
		netdev_err(mgp->dev, "Failed to set promisc mode\n");
पूर्ण

अटल पूर्णांक myri10ge_dma_test(काष्ठा myri10ge_priv *mgp, पूर्णांक test_type)
अणु
	काष्ठा myri10ge_cmd cmd;
	पूर्णांक status;
	u32 len;
	काष्ठा page *dmatest_page;
	dma_addr_t dmatest_bus;
	अक्षर *test = " ";

	dmatest_page = alloc_page(GFP_KERNEL);
	अगर (!dmatest_page)
		वापस -ENOMEM;
	dmatest_bus = pci_map_page(mgp->pdev, dmatest_page, 0, PAGE_SIZE,
				   DMA_BIसूचीECTIONAL);
	अगर (unlikely(pci_dma_mapping_error(mgp->pdev, dmatest_bus))) अणु
		__मुक्त_page(dmatest_page);
		वापस -ENOMEM;
	पूर्ण

	/* Run a small DMA test.
	 * The magic multipliers to the length tell the firmware
	 * to करो DMA पढ़ो, ग_लिखो, or पढ़ो+ग_लिखो tests.  The
	 * results are वापसed in cmd.data0.  The upper 16
	 * bits or the वापस is the number of transfers completed.
	 * The lower 16 bits is the समय in 0.5us ticks that the
	 * transfers took to complete.
	 */

	len = mgp->tx_boundary;

	cmd.data0 = MYRI10GE_LOWPART_TO_U32(dmatest_bus);
	cmd.data1 = MYRI10GE_HIGHPART_TO_U32(dmatest_bus);
	cmd.data2 = len * 0x10000;
	status = myri10ge_send_cmd(mgp, test_type, &cmd, 0);
	अगर (status != 0) अणु
		test = "read";
		जाओ पात;
	पूर्ण
	mgp->पढ़ो_dma = ((cmd.data0 >> 16) * len * 2) / (cmd.data0 & 0xffff);
	cmd.data0 = MYRI10GE_LOWPART_TO_U32(dmatest_bus);
	cmd.data1 = MYRI10GE_HIGHPART_TO_U32(dmatest_bus);
	cmd.data2 = len * 0x1;
	status = myri10ge_send_cmd(mgp, test_type, &cmd, 0);
	अगर (status != 0) अणु
		test = "write";
		जाओ पात;
	पूर्ण
	mgp->ग_लिखो_dma = ((cmd.data0 >> 16) * len * 2) / (cmd.data0 & 0xffff);

	cmd.data0 = MYRI10GE_LOWPART_TO_U32(dmatest_bus);
	cmd.data1 = MYRI10GE_HIGHPART_TO_U32(dmatest_bus);
	cmd.data2 = len * 0x10001;
	status = myri10ge_send_cmd(mgp, test_type, &cmd, 0);
	अगर (status != 0) अणु
		test = "read/write";
		जाओ पात;
	पूर्ण
	mgp->पढ़ो_ग_लिखो_dma = ((cmd.data0 >> 16) * len * 2 * 2) /
	    (cmd.data0 & 0xffff);

पात:
	pci_unmap_page(mgp->pdev, dmatest_bus, PAGE_SIZE, DMA_BIसूचीECTIONAL);
	put_page(dmatest_page);

	अगर (status != 0 && test_type != MXGEFW_CMD_UNALIGNED_TEST)
		dev_warn(&mgp->pdev->dev, "DMA %s benchmark failed: %d\n",
			 test, status);

	वापस status;
पूर्ण

अटल पूर्णांक myri10ge_reset(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा myri10ge_cmd cmd;
	काष्ठा myri10ge_slice_state *ss;
	पूर्णांक i, status;
	माप_प्रकार bytes;
#अगर_घोषित CONFIG_MYRI10GE_DCA
	अचिन्हित दीर्घ dca_tag_off;
#पूर्ण_अगर

	/* try to send a reset command to the card to see अगर it
	 * is alive */
	स_रखो(&cmd, 0, माप(cmd));
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_RESET, &cmd, 0);
	अगर (status != 0) अणु
		dev_err(&mgp->pdev->dev, "failed reset\n");
		वापस -ENXIO;
	पूर्ण

	(व्योम)myri10ge_dma_test(mgp, MXGEFW_DMA_TEST);
	/*
	 * Use non-ndis mcp_slot (eg, 4 bytes total,
	 * no toeplitz hash value वापसed.  Older firmware will
	 * not understand this command, but will use the correct
	 * sized mcp_slot, so we ignore error वापसs
	 */
	cmd.data0 = MXGEFW_RSS_MCP_SLOT_TYPE_MIN;
	(व्योम)myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_RSS_MCP_SLOT_TYPE, &cmd, 0);

	/* Now exchange inक्रमmation about पूर्णांकerrupts  */

	bytes = mgp->max_पूर्णांकr_slots * माप(*mgp->ss[0].rx_करोne.entry);
	cmd.data0 = (u32) bytes;
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_INTRQ_SIZE, &cmd, 0);

	/*
	 * Even though we alपढ़ोy know how many slices are supported
	 * via myri10ge_probe_slices() MXGEFW_CMD_GET_MAX_RSS_QUEUES
	 * has magic side effects, and must be called after a reset.
	 * It must be called prior to calling any RSS related cmds,
	 * including assigning an पूर्णांकerrupt queue क्रम anything but
	 * slice 0.  It must also be called *after*
	 * MXGEFW_CMD_SET_INTRQ_SIZE, since the पूर्णांकrq size is used by
	 * the firmware to compute offsets.
	 */

	अगर (mgp->num_slices > 1) अणु

		/* ask the maximum number of slices it supports */
		status = myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_MAX_RSS_QUEUES,
					   &cmd, 0);
		अगर (status != 0) अणु
			dev_err(&mgp->pdev->dev,
				"failed to get number of slices\n");
		पूर्ण

		/*
		 * MXGEFW_CMD_ENABLE_RSS_QUEUES must be called prior
		 * to setting up the पूर्णांकerrupt queue DMA
		 */

		cmd.data0 = mgp->num_slices;
		cmd.data1 = MXGEFW_SLICE_INTR_MODE_ONE_PER_SLICE;
		अगर (mgp->dev->real_num_tx_queues > 1)
			cmd.data1 |= MXGEFW_SLICE_ENABLE_MULTIPLE_TX_QUEUES;
		status = myri10ge_send_cmd(mgp, MXGEFW_CMD_ENABLE_RSS_QUEUES,
					   &cmd, 0);

		/* Firmware older than 1.4.32 only supports multiple
		 * RX queues, so अगर we get an error, first retry using a
		 * single TX queue beक्रमe giving up */
		अगर (status != 0 && mgp->dev->real_num_tx_queues > 1) अणु
			netअगर_set_real_num_tx_queues(mgp->dev, 1);
			cmd.data0 = mgp->num_slices;
			cmd.data1 = MXGEFW_SLICE_INTR_MODE_ONE_PER_SLICE;
			status = myri10ge_send_cmd(mgp,
						   MXGEFW_CMD_ENABLE_RSS_QUEUES,
						   &cmd, 0);
		पूर्ण

		अगर (status != 0) अणु
			dev_err(&mgp->pdev->dev,
				"failed to set number of slices\n");

			वापस status;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < mgp->num_slices; i++) अणु
		ss = &mgp->ss[i];
		cmd.data0 = MYRI10GE_LOWPART_TO_U32(ss->rx_करोne.bus);
		cmd.data1 = MYRI10GE_HIGHPART_TO_U32(ss->rx_करोne.bus);
		cmd.data2 = i;
		status |= myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_INTRQ_DMA,
					    &cmd, 0);
	पूर्ण

	status |=
	    myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_IRQ_ACK_OFFSET, &cmd, 0);
	क्रम (i = 0; i < mgp->num_slices; i++) अणु
		ss = &mgp->ss[i];
		ss->irq_claim =
		    (__iomem __be32 *) (mgp->sram + cmd.data0 + 8 * i);
	पूर्ण
	status |= myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_IRQ_DEASSERT_OFFSET,
				    &cmd, 0);
	mgp->irq_deनिश्चित = (__iomem __be32 *) (mgp->sram + cmd.data0);

	status |= myri10ge_send_cmd
	    (mgp, MXGEFW_CMD_GET_INTR_COAL_DELAY_OFFSET, &cmd, 0);
	mgp->पूर्णांकr_coal_delay_ptr = (__iomem __be32 *) (mgp->sram + cmd.data0);
	अगर (status != 0) अणु
		dev_err(&mgp->pdev->dev, "failed set interrupt parameters\n");
		वापस status;
	पूर्ण
	put_be32(htonl(mgp->पूर्णांकr_coal_delay), mgp->पूर्णांकr_coal_delay_ptr);

#अगर_घोषित CONFIG_MYRI10GE_DCA
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_DCA_OFFSET, &cmd, 0);
	dca_tag_off = cmd.data0;
	क्रम (i = 0; i < mgp->num_slices; i++) अणु
		ss = &mgp->ss[i];
		अगर (status == 0) अणु
			ss->dca_tag = (__iomem __be32 *)
			    (mgp->sram + dca_tag_off + 4 * i);
		पूर्ण अन्यथा अणु
			ss->dca_tag = शून्य;
		पूर्ण
	पूर्ण
#पूर्ण_अगर				/* CONFIG_MYRI10GE_DCA */

	/* reset mcp/driver shared state back to 0 */

	mgp->link_changes = 0;
	क्रम (i = 0; i < mgp->num_slices; i++) अणु
		ss = &mgp->ss[i];

		स_रखो(ss->rx_करोne.entry, 0, bytes);
		ss->tx.req = 0;
		ss->tx.करोne = 0;
		ss->tx.pkt_start = 0;
		ss->tx.pkt_करोne = 0;
		ss->rx_big.cnt = 0;
		ss->rx_small.cnt = 0;
		ss->rx_करोne.idx = 0;
		ss->rx_करोne.cnt = 0;
		ss->tx.wake_queue = 0;
		ss->tx.stop_queue = 0;
	पूर्ण

	status = myri10ge_update_mac_address(mgp, mgp->dev->dev_addr);
	myri10ge_change_छोड़ो(mgp, mgp->छोड़ो);
	myri10ge_set_multicast_list(mgp->dev);
	वापस status;
पूर्ण

#अगर_घोषित CONFIG_MYRI10GE_DCA
अटल पूर्णांक myri10ge_toggle_relaxed(काष्ठा pci_dev *pdev, पूर्णांक on)
अणु
	पूर्णांक ret;
	u16 ctl;

	pcie_capability_पढ़ो_word(pdev, PCI_EXP_DEVCTL, &ctl);

	ret = (ctl & PCI_EXP_DEVCTL_RELAX_EN) >> 4;
	अगर (ret != on) अणु
		ctl &= ~PCI_EXP_DEVCTL_RELAX_EN;
		ctl |= (on << 4);
		pcie_capability_ग_लिखो_word(pdev, PCI_EXP_DEVCTL, ctl);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
myri10ge_ग_लिखो_dca(काष्ठा myri10ge_slice_state *ss, पूर्णांक cpu, पूर्णांक tag)
अणु
	ss->cached_dca_tag = tag;
	put_be32(htonl(tag), ss->dca_tag);
पूर्ण

अटल अंतरभूत व्योम myri10ge_update_dca(काष्ठा myri10ge_slice_state *ss)
अणु
	पूर्णांक cpu = get_cpu();
	पूर्णांक tag;

	अगर (cpu != ss->cpu) अणु
		tag = dca3_get_tag(&ss->mgp->pdev->dev, cpu);
		अगर (ss->cached_dca_tag != tag)
			myri10ge_ग_लिखो_dca(ss, cpu, tag);
		ss->cpu = cpu;
	पूर्ण
	put_cpu();
पूर्ण

अटल व्योम myri10ge_setup_dca(काष्ठा myri10ge_priv *mgp)
अणु
	पूर्णांक err, i;
	काष्ठा pci_dev *pdev = mgp->pdev;

	अगर (mgp->ss[0].dca_tag == शून्य || mgp->dca_enabled)
		वापस;
	अगर (!myri10ge_dca) अणु
		dev_err(&pdev->dev, "dca disabled by administrator\n");
		वापस;
	पूर्ण
	err = dca_add_requester(&pdev->dev);
	अगर (err) अणु
		अगर (err != -ENODEV)
			dev_err(&pdev->dev,
				"dca_add_requester() failed, err=%d\n", err);
		वापस;
	पूर्ण
	mgp->relaxed_order = myri10ge_toggle_relaxed(pdev, 0);
	mgp->dca_enabled = 1;
	क्रम (i = 0; i < mgp->num_slices; i++) अणु
		mgp->ss[i].cpu = -1;
		mgp->ss[i].cached_dca_tag = -1;
		myri10ge_update_dca(&mgp->ss[i]);
	पूर्ण
पूर्ण

अटल व्योम myri10ge_tearकरोwn_dca(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा pci_dev *pdev = mgp->pdev;

	अगर (!mgp->dca_enabled)
		वापस;
	mgp->dca_enabled = 0;
	अगर (mgp->relaxed_order)
		myri10ge_toggle_relaxed(pdev, 1);
	dca_हटाओ_requester(&pdev->dev);
पूर्ण

अटल पूर्णांक myri10ge_notअगरy_dca_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा myri10ge_priv *mgp;
	अचिन्हित दीर्घ event;

	mgp = dev_get_drvdata(dev);
	event = *(अचिन्हित दीर्घ *)data;

	अगर (event == DCA_PROVIDER_ADD)
		myri10ge_setup_dca(mgp);
	अन्यथा अगर (event == DCA_PROVIDER_REMOVE)
		myri10ge_tearकरोwn_dca(mgp);
	वापस 0;
पूर्ण
#पूर्ण_अगर				/* CONFIG_MYRI10GE_DCA */

अटल अंतरभूत व्योम
myri10ge_submit_8rx(काष्ठा mcp_kreq_ether_recv __iomem * dst,
		    काष्ठा mcp_kreq_ether_recv *src)
अणु
	__be32 low;

	low = src->addr_low;
	src->addr_low = htonl(DMA_BIT_MASK(32));
	myri10ge_pio_copy(dst, src, 4 * माप(*src));
	mb();
	myri10ge_pio_copy(dst + 4, src + 4, 4 * माप(*src));
	mb();
	src->addr_low = low;
	put_be32(low, &dst->addr_low);
	mb();
पूर्ण

अटल व्योम
myri10ge_alloc_rx_pages(काष्ठा myri10ge_priv *mgp, काष्ठा myri10ge_rx_buf *rx,
			पूर्णांक bytes, पूर्णांक watchकरोg)
अणु
	काष्ठा page *page;
	dma_addr_t bus;
	पूर्णांक idx;
#अगर MYRI10GE_ALLOC_SIZE > 4096
	पूर्णांक end_offset;
#पूर्ण_अगर

	अगर (unlikely(rx->watchकरोg_needed && !watchकरोg))
		वापस;

	/* try to refill entire ring */
	जबतक (rx->fill_cnt != (rx->cnt + rx->mask + 1)) अणु
		idx = rx->fill_cnt & rx->mask;
		अगर (rx->page_offset + bytes <= MYRI10GE_ALLOC_SIZE) अणु
			/* we can use part of previous page */
			get_page(rx->page);
		पूर्ण अन्यथा अणु
			/* we need a new page */
			page =
			    alloc_pages(GFP_ATOMIC | __GFP_COMP,
					MYRI10GE_ALLOC_ORDER);
			अगर (unlikely(page == शून्य)) अणु
				अगर (rx->fill_cnt - rx->cnt < 16)
					rx->watchकरोg_needed = 1;
				वापस;
			पूर्ण

			bus = pci_map_page(mgp->pdev, page, 0,
					   MYRI10GE_ALLOC_SIZE,
					   PCI_DMA_FROMDEVICE);
			अगर (unlikely(pci_dma_mapping_error(mgp->pdev, bus))) अणु
				__मुक्त_pages(page, MYRI10GE_ALLOC_ORDER);
				अगर (rx->fill_cnt - rx->cnt < 16)
					rx->watchकरोg_needed = 1;
				वापस;
			पूर्ण

			rx->page = page;
			rx->page_offset = 0;
			rx->bus = bus;

		पूर्ण
		rx->info[idx].page = rx->page;
		rx->info[idx].page_offset = rx->page_offset;
		/* note that this is the address of the start of the
		 * page */
		dma_unmap_addr_set(&rx->info[idx], bus, rx->bus);
		rx->shaकरोw[idx].addr_low =
		    htonl(MYRI10GE_LOWPART_TO_U32(rx->bus) + rx->page_offset);
		rx->shaकरोw[idx].addr_high =
		    htonl(MYRI10GE_HIGHPART_TO_U32(rx->bus));

		/* start next packet on a cacheline boundary */
		rx->page_offset += SKB_DATA_ALIGN(bytes);

#अगर MYRI10GE_ALLOC_SIZE > 4096
		/* करोn't cross a 4KB boundary */
		end_offset = rx->page_offset + bytes - 1;
		अगर ((अचिन्हित)(rx->page_offset ^ end_offset) > 4095)
			rx->page_offset = end_offset & ~4095;
#पूर्ण_अगर
		rx->fill_cnt++;

		/* copy 8 descriptors to the firmware at a समय */
		अगर ((idx & 7) == 7) अणु
			myri10ge_submit_8rx(&rx->lanai[idx - 7],
					    &rx->shaकरोw[idx - 7]);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
myri10ge_unmap_rx_page(काष्ठा pci_dev *pdev,
		       काष्ठा myri10ge_rx_buffer_state *info, पूर्णांक bytes)
अणु
	/* unmap the recvd page अगर we're the only or last user of it */
	अगर (bytes >= MYRI10GE_ALLOC_SIZE / 2 ||
	    (info->page_offset + 2 * bytes) > MYRI10GE_ALLOC_SIZE) अणु
		pci_unmap_page(pdev, (dma_unmap_addr(info, bus)
				      & ~(MYRI10GE_ALLOC_SIZE - 1)),
			       MYRI10GE_ALLOC_SIZE, PCI_DMA_FROMDEVICE);
	पूर्ण
पूर्ण

/*
 * GRO करोes not support acceleration of tagged vlan frames, and
 * this NIC करोes not support vlan tag offload, so we must pop
 * the tag ourselves to be able to achieve GRO perक्रमmance that
 * is comparable to LRO.
 */

अटल अंतरभूत व्योम
myri10ge_vlan_rx(काष्ठा net_device *dev, व्योम *addr, काष्ठा sk_buff *skb)
अणु
	u8 *va;
	काष्ठा vlan_ethhdr *veh;
	skb_frag_t *frag;
	__wsum vsum;

	va = addr;
	va += MXGEFW_PAD;
	veh = (काष्ठा vlan_ethhdr *)va;
	अगर ((dev->features & NETIF_F_HW_VLAN_CTAG_RX) ==
	    NETIF_F_HW_VLAN_CTAG_RX &&
	    veh->h_vlan_proto == htons(ETH_P_8021Q)) अणु
		/* fixup csum अगर needed */
		अगर (skb->ip_summed == CHECKSUM_COMPLETE) अणु
			vsum = csum_partial(va + ETH_HLEN, VLAN_HLEN, 0);
			skb->csum = csum_sub(skb->csum, vsum);
		पूर्ण
		/* pop tag */
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(veh->h_vlan_TCI));
		स_हटाओ(va + VLAN_HLEN, va, 2 * ETH_ALEN);
		skb->len -= VLAN_HLEN;
		skb->data_len -= VLAN_HLEN;
		frag = skb_shinfo(skb)->frags;
		skb_frag_off_add(frag, VLAN_HLEN);
		skb_frag_size_sub(frag, VLAN_HLEN);
	पूर्ण
पूर्ण

#घोषणा MYRI10GE_HLEN 64 /* Bytes to copy from page to skb linear memory */

अटल अंतरभूत पूर्णांक
myri10ge_rx_करोne(काष्ठा myri10ge_slice_state *ss, पूर्णांक len, __wsum csum)
अणु
	काष्ठा myri10ge_priv *mgp = ss->mgp;
	काष्ठा sk_buff *skb;
	skb_frag_t *rx_frags;
	काष्ठा myri10ge_rx_buf *rx;
	पूर्णांक i, idx, reमुख्यder, bytes;
	काष्ठा pci_dev *pdev = mgp->pdev;
	काष्ठा net_device *dev = mgp->dev;
	u8 *va;

	अगर (len <= mgp->small_bytes) अणु
		rx = &ss->rx_small;
		bytes = mgp->small_bytes;
	पूर्ण अन्यथा अणु
		rx = &ss->rx_big;
		bytes = mgp->big_bytes;
	पूर्ण

	len += MXGEFW_PAD;
	idx = rx->cnt & rx->mask;
	va = page_address(rx->info[idx].page) + rx->info[idx].page_offset;
	prefetch(va);

	skb = napi_get_frags(&ss->napi);
	अगर (unlikely(skb == शून्य)) अणु
		ss->stats.rx_dropped++;
		क्रम (i = 0, reमुख्यder = len; reमुख्यder > 0; i++) अणु
			myri10ge_unmap_rx_page(pdev, &rx->info[idx], bytes);
			put_page(rx->info[idx].page);
			rx->cnt++;
			idx = rx->cnt & rx->mask;
			reमुख्यder -= MYRI10GE_ALLOC_SIZE;
		पूर्ण
		वापस 0;
	पूर्ण
	rx_frags = skb_shinfo(skb)->frags;
	/* Fill skb_frag_t(s) with data from our receive */
	क्रम (i = 0, reमुख्यder = len; reमुख्यder > 0; i++) अणु
		myri10ge_unmap_rx_page(pdev, &rx->info[idx], bytes);
		skb_fill_page_desc(skb, i, rx->info[idx].page,
				   rx->info[idx].page_offset,
				   reमुख्यder < MYRI10GE_ALLOC_SIZE ?
				   reमुख्यder : MYRI10GE_ALLOC_SIZE);
		rx->cnt++;
		idx = rx->cnt & rx->mask;
		reमुख्यder -= MYRI10GE_ALLOC_SIZE;
	पूर्ण

	/* हटाओ padding */
	skb_frag_off_add(&rx_frags[0], MXGEFW_PAD);
	skb_frag_size_sub(&rx_frags[0], MXGEFW_PAD);
	len -= MXGEFW_PAD;

	skb->len = len;
	skb->data_len = len;
	skb->truesize += len;
	अगर (dev->features & NETIF_F_RXCSUM) अणु
		skb->ip_summed = CHECKSUM_COMPLETE;
		skb->csum = csum;
	पूर्ण
	myri10ge_vlan_rx(mgp->dev, va, skb);
	skb_record_rx_queue(skb, ss - &mgp->ss[0]);

	napi_gro_frags(&ss->napi);

	वापस 1;
पूर्ण

अटल अंतरभूत व्योम
myri10ge_tx_करोne(काष्ठा myri10ge_slice_state *ss, पूर्णांक mcp_index)
अणु
	काष्ठा pci_dev *pdev = ss->mgp->pdev;
	काष्ठा myri10ge_tx_buf *tx = &ss->tx;
	काष्ठा netdev_queue *dev_queue;
	काष्ठा sk_buff *skb;
	पूर्णांक idx, len;

	जबतक (tx->pkt_करोne != mcp_index) अणु
		idx = tx->करोne & tx->mask;
		skb = tx->info[idx].skb;

		/* Mark as मुक्त */
		tx->info[idx].skb = शून्य;
		अगर (tx->info[idx].last) अणु
			tx->pkt_करोne++;
			tx->info[idx].last = 0;
		पूर्ण
		tx->करोne++;
		len = dma_unmap_len(&tx->info[idx], len);
		dma_unmap_len_set(&tx->info[idx], len, 0);
		अगर (skb) अणु
			ss->stats.tx_bytes += skb->len;
			ss->stats.tx_packets++;
			dev_consume_skb_irq(skb);
			अगर (len)
				pci_unmap_single(pdev,
						 dma_unmap_addr(&tx->info[idx],
								bus), len,
						 PCI_DMA_TODEVICE);
		पूर्ण अन्यथा अणु
			अगर (len)
				pci_unmap_page(pdev,
					       dma_unmap_addr(&tx->info[idx],
							      bus), len,
					       PCI_DMA_TODEVICE);
		पूर्ण
	पूर्ण

	dev_queue = netdev_get_tx_queue(ss->dev, ss - ss->mgp->ss);
	/*
	 * Make a minimal efक्रमt to prevent the NIC from polling an
	 * idle tx queue.  If we can't get the lock we leave the queue
	 * active. In this हाल, either a thपढ़ो was about to start
	 * using the queue anyway, or we lost a race and the NIC will
	 * waste some of its resources polling an inactive queue क्रम a
	 * जबतक.
	 */

	अगर ((ss->mgp->dev->real_num_tx_queues > 1) &&
	    __netअगर_tx_trylock(dev_queue)) अणु
		अगर (tx->req == tx->करोne) अणु
			tx->queue_active = 0;
			put_be32(htonl(1), tx->send_stop);
			mb();
		पूर्ण
		__netअगर_tx_unlock(dev_queue);
	पूर्ण

	/* start the queue अगर we've stopped it */
	अगर (netअगर_tx_queue_stopped(dev_queue) &&
	    tx->req - tx->करोne < (tx->mask >> 1) &&
	    ss->mgp->running == MYRI10GE_ETH_RUNNING) अणु
		tx->wake_queue++;
		netअगर_tx_wake_queue(dev_queue);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
myri10ge_clean_rx_करोne(काष्ठा myri10ge_slice_state *ss, पूर्णांक budget)
अणु
	काष्ठा myri10ge_rx_करोne *rx_करोne = &ss->rx_करोne;
	काष्ठा myri10ge_priv *mgp = ss->mgp;
	अचिन्हित दीर्घ rx_bytes = 0;
	अचिन्हित दीर्घ rx_packets = 0;
	अचिन्हित दीर्घ rx_ok;
	पूर्णांक idx = rx_करोne->idx;
	पूर्णांक cnt = rx_करोne->cnt;
	पूर्णांक work_करोne = 0;
	u16 length;
	__wsum checksum;

	जबतक (rx_करोne->entry[idx].length != 0 && work_करोne < budget) अणु
		length = ntohs(rx_करोne->entry[idx].length);
		rx_करोne->entry[idx].length = 0;
		checksum = csum_unfold(rx_करोne->entry[idx].checksum);
		rx_ok = myri10ge_rx_करोne(ss, length, checksum);
		rx_packets += rx_ok;
		rx_bytes += rx_ok * (अचिन्हित दीर्घ)length;
		cnt++;
		idx = cnt & (mgp->max_पूर्णांकr_slots - 1);
		work_करोne++;
	पूर्ण
	rx_करोne->idx = idx;
	rx_करोne->cnt = cnt;
	ss->stats.rx_packets += rx_packets;
	ss->stats.rx_bytes += rx_bytes;

	/* restock receive rings अगर needed */
	अगर (ss->rx_small.fill_cnt - ss->rx_small.cnt < myri10ge_fill_thresh)
		myri10ge_alloc_rx_pages(mgp, &ss->rx_small,
					mgp->small_bytes + MXGEFW_PAD, 0);
	अगर (ss->rx_big.fill_cnt - ss->rx_big.cnt < myri10ge_fill_thresh)
		myri10ge_alloc_rx_pages(mgp, &ss->rx_big, mgp->big_bytes, 0);

	वापस work_करोne;
पूर्ण

अटल अंतरभूत व्योम myri10ge_check_statblock(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा mcp_irq_data *stats = mgp->ss[0].fw_stats;

	अगर (unlikely(stats->stats_updated)) अणु
		अचिन्हित link_up = ntohl(stats->link_up);
		अगर (mgp->link_state != link_up) अणु
			mgp->link_state = link_up;

			अगर (mgp->link_state == MXGEFW_LINK_UP) अणु
				netअगर_info(mgp, link, mgp->dev, "link up\n");
				netअगर_carrier_on(mgp->dev);
				mgp->link_changes++;
			पूर्ण अन्यथा अणु
				netअगर_info(mgp, link, mgp->dev, "link %s\n",
					   (link_up == MXGEFW_LINK_MYRINET ?
					    "mismatch (Myrinet detected)" :
					    "down"));
				netअगर_carrier_off(mgp->dev);
				mgp->link_changes++;
			पूर्ण
		पूर्ण
		अगर (mgp->rdma_tags_available !=
		    ntohl(stats->rdma_tags_available)) अणु
			mgp->rdma_tags_available =
			    ntohl(stats->rdma_tags_available);
			netdev_warn(mgp->dev, "RDMA timed out! %d tags left\n",
				    mgp->rdma_tags_available);
		पूर्ण
		mgp->करोwn_cnt += stats->link_करोwn;
		अगर (stats->link_करोwn)
			wake_up(&mgp->करोwn_wq);
	पूर्ण
पूर्ण

अटल पूर्णांक myri10ge_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा myri10ge_slice_state *ss =
	    container_of(napi, काष्ठा myri10ge_slice_state, napi);
	पूर्णांक work_करोne;

#अगर_घोषित CONFIG_MYRI10GE_DCA
	अगर (ss->mgp->dca_enabled)
		myri10ge_update_dca(ss);
#पूर्ण_अगर
	/* process as many rx events as NAPI will allow */
	work_करोne = myri10ge_clean_rx_करोne(ss, budget);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		put_be32(htonl(3), ss->irq_claim);
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल irqवापस_t myri10ge_पूर्णांकr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा myri10ge_slice_state *ss = arg;
	काष्ठा myri10ge_priv *mgp = ss->mgp;
	काष्ठा mcp_irq_data *stats = ss->fw_stats;
	काष्ठा myri10ge_tx_buf *tx = &ss->tx;
	u32 send_करोne_count;
	पूर्णांक i;

	/* an पूर्णांकerrupt on a non-zero receive-only slice is implicitly
	 * valid  since MSI-X irqs are not shared */
	अगर ((mgp->dev->real_num_tx_queues == 1) && (ss != mgp->ss)) अणु
		napi_schedule(&ss->napi);
		वापस IRQ_HANDLED;
	पूर्ण

	/* make sure it is our IRQ, and that the DMA has finished */
	अगर (unlikely(!stats->valid))
		वापस IRQ_NONE;

	/* low bit indicates receives are present, so schedule
	 * napi poll handler */
	अगर (stats->valid & 1)
		napi_schedule(&ss->napi);

	अगर (!mgp->msi_enabled && !mgp->msix_enabled) अणु
		put_be32(0, mgp->irq_deनिश्चित);
		अगर (!myri10ge_deनिश्चित_रुको)
			stats->valid = 0;
		mb();
	पूर्ण अन्यथा
		stats->valid = 0;

	/* Wait क्रम IRQ line to go low, अगर using INTx */
	i = 0;
	जबतक (1) अणु
		i++;
		/* check क्रम transmit completes and receives */
		send_करोne_count = ntohl(stats->send_करोne_count);
		अगर (send_करोne_count != tx->pkt_करोne)
			myri10ge_tx_करोne(ss, (पूर्णांक)send_करोne_count);
		अगर (unlikely(i > myri10ge_max_irq_loops)) अणु
			netdev_warn(mgp->dev, "irq stuck?\n");
			stats->valid = 0;
			schedule_work(&mgp->watchकरोg_work);
		पूर्ण
		अगर (likely(stats->valid == 0))
			अवरोध;
		cpu_relax();
		barrier();
	पूर्ण

	/* Only slice 0 updates stats */
	अगर (ss == mgp->ss)
		myri10ge_check_statblock(mgp);

	put_be32(htonl(3), ss->irq_claim + 1);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
myri10ge_get_link_ksettings(काष्ठा net_device *netdev,
			    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);
	अक्षर *ptr;
	पूर्णांक i;

	cmd->base.स्वतःneg = AUTONEG_DISABLE;
	cmd->base.speed = SPEED_10000;
	cmd->base.duplex = DUPLEX_FULL;

	/*
	 * parse the product code to deterimine the पूर्णांकerface type
	 * (CX4, XFP, Quad Ribbon Fiber) by looking at the अक्षरacter
	 * after the 3rd dash in the driver's cached copy of the
	 * EEPROM's product code string.
	 */
	ptr = mgp->product_code_string;
	अगर (ptr == शून्य) अणु
		netdev_err(netdev, "Missing product code\n");
		वापस 0;
	पूर्ण
	क्रम (i = 0; i < 3; i++, ptr++) अणु
		ptr = म_अक्षर(ptr, '-');
		अगर (ptr == शून्य) अणु
			netdev_err(netdev, "Invalid product code %s\n",
				   mgp->product_code_string);
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (*ptr == '2')
		ptr++;
	अगर (*ptr == 'R' || *ptr == 'Q' || *ptr == 'S') अणु
		/* We've found either an XFP, quad ribbon fiber, or SFP+ */
		cmd->base.port = PORT_FIBRE;
		ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(cmd, advertising, FIBRE);
	पूर्ण अन्यथा अणु
		cmd->base.port = PORT_OTHER;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
myri10ge_get_drvinfo(काष्ठा net_device *netdev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);

	strlcpy(info->driver, "myri10ge", माप(info->driver));
	strlcpy(info->version, MYRI10GE_VERSION_STR, माप(info->version));
	strlcpy(info->fw_version, mgp->fw_version, माप(info->fw_version));
	strlcpy(info->bus_info, pci_name(mgp->pdev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक
myri10ge_get_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);

	coal->rx_coalesce_usecs = mgp->पूर्णांकr_coal_delay;
	वापस 0;
पूर्ण

अटल पूर्णांक
myri10ge_set_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);

	mgp->पूर्णांकr_coal_delay = coal->rx_coalesce_usecs;
	put_be32(htonl(mgp->पूर्णांकr_coal_delay), mgp->पूर्णांकr_coal_delay_ptr);
	वापस 0;
पूर्ण

अटल व्योम
myri10ge_get_छोड़ोparam(काष्ठा net_device *netdev,
			काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);

	छोड़ो->स्वतःneg = 0;
	छोड़ो->rx_छोड़ो = mgp->छोड़ो;
	छोड़ो->tx_छोड़ो = mgp->छोड़ो;
पूर्ण

अटल पूर्णांक
myri10ge_set_छोड़ोparam(काष्ठा net_device *netdev,
			काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);

	अगर (छोड़ो->tx_छोड़ो != mgp->छोड़ो)
		वापस myri10ge_change_छोड़ो(mgp, छोड़ो->tx_छोड़ो);
	अगर (छोड़ो->rx_छोड़ो != mgp->छोड़ो)
		वापस myri10ge_change_छोड़ो(mgp, छोड़ो->rx_छोड़ो);
	अगर (छोड़ो->स्वतःneg != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम
myri10ge_get_ringparam(काष्ठा net_device *netdev,
		       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);

	ring->rx_mini_max_pending = mgp->ss[0].rx_small.mask + 1;
	ring->rx_max_pending = mgp->ss[0].rx_big.mask + 1;
	ring->rx_jumbo_max_pending = 0;
	ring->tx_max_pending = mgp->ss[0].tx.mask + 1;
	ring->rx_mini_pending = ring->rx_mini_max_pending;
	ring->rx_pending = ring->rx_max_pending;
	ring->rx_jumbo_pending = ring->rx_jumbo_max_pending;
	ring->tx_pending = ring->tx_max_pending;
पूर्ण

अटल स्थिर अक्षर myri10ge_gstrings_मुख्य_stats[][ETH_GSTRING_LEN] = अणु
	"rx_packets", "tx_packets", "rx_bytes", "tx_bytes", "rx_errors",
	"tx_errors", "rx_dropped", "tx_dropped", "multicast", "collisions",
	"rx_length_errors", "rx_over_errors", "rx_crc_errors",
	"rx_frame_errors", "rx_fifo_errors", "rx_missed_errors",
	"tx_aborted_errors", "tx_carrier_errors", "tx_fifo_errors",
	"tx_heartbeat_errors", "tx_window_errors",
	/* device-specअगरic stats */
	"tx_boundary", "irq", "MSI", "MSIX",
	"read_dma_bw_MBs", "write_dma_bw_MBs", "read_write_dma_bw_MBs",
	"serial_number", "watchdog_resets",
#अगर_घोषित CONFIG_MYRI10GE_DCA
	"dca_capable_firmware", "dca_device_present",
#पूर्ण_अगर
	"link_changes", "link_up", "dropped_link_overflow",
	"dropped_link_error_or_filtered",
	"dropped_pause", "dropped_bad_phy", "dropped_bad_crc32",
	"dropped_unicast_filtered", "dropped_multicast_filtered",
	"dropped_runt", "dropped_overrun", "dropped_no_small_buffer",
	"dropped_no_big_buffer"
पूर्ण;

अटल स्थिर अक्षर myri10ge_gstrings_slice_stats[][ETH_GSTRING_LEN] = अणु
	"----------- slice ---------",
	"tx_pkt_start", "tx_pkt_done", "tx_req", "tx_done",
	"rx_small_cnt", "rx_big_cnt",
	"wake_queue", "stop_queue", "tx_linearized",
पूर्ण;

#घोषणा MYRI10GE_NET_STATS_LEN      21
#घोषणा MYRI10GE_MAIN_STATS_LEN  ARRAY_SIZE(myri10ge_gstrings_मुख्य_stats)
#घोषणा MYRI10GE_SLICE_STATS_LEN  ARRAY_SIZE(myri10ge_gstrings_slice_stats)

अटल व्योम
myri10ge_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 * data)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(data, *myri10ge_gstrings_मुख्य_stats,
		       माप(myri10ge_gstrings_मुख्य_stats));
		data += माप(myri10ge_gstrings_मुख्य_stats);
		क्रम (i = 0; i < mgp->num_slices; i++) अणु
			स_नकल(data, *myri10ge_gstrings_slice_stats,
			       माप(myri10ge_gstrings_slice_stats));
			data += माप(myri10ge_gstrings_slice_stats);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक myri10ge_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस MYRI10GE_MAIN_STATS_LEN +
		    mgp->num_slices * MYRI10GE_SLICE_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम
myri10ge_get_ethtool_stats(काष्ठा net_device *netdev,
			   काष्ठा ethtool_stats *stats, u64 * data)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);
	काष्ठा myri10ge_slice_state *ss;
	काष्ठा rtnl_link_stats64 link_stats;
	पूर्णांक slice;
	पूर्णांक i;

	/* क्रमce stats update */
	स_रखो(&link_stats, 0, माप(link_stats));
	(व्योम)myri10ge_get_stats(netdev, &link_stats);
	क्रम (i = 0; i < MYRI10GE_NET_STATS_LEN; i++)
		data[i] = ((u64 *)&link_stats)[i];

	data[i++] = (अचिन्हित पूर्णांक)mgp->tx_boundary;
	data[i++] = (अचिन्हित पूर्णांक)mgp->pdev->irq;
	data[i++] = (अचिन्हित पूर्णांक)mgp->msi_enabled;
	data[i++] = (अचिन्हित पूर्णांक)mgp->msix_enabled;
	data[i++] = (अचिन्हित पूर्णांक)mgp->पढ़ो_dma;
	data[i++] = (अचिन्हित पूर्णांक)mgp->ग_लिखो_dma;
	data[i++] = (अचिन्हित पूर्णांक)mgp->पढ़ो_ग_लिखो_dma;
	data[i++] = (अचिन्हित पूर्णांक)mgp->serial_number;
	data[i++] = (अचिन्हित पूर्णांक)mgp->watchकरोg_resets;
#अगर_घोषित CONFIG_MYRI10GE_DCA
	data[i++] = (अचिन्हित पूर्णांक)(mgp->ss[0].dca_tag != शून्य);
	data[i++] = (अचिन्हित पूर्णांक)(mgp->dca_enabled);
#पूर्ण_अगर
	data[i++] = (अचिन्हित पूर्णांक)mgp->link_changes;

	/* firmware stats are useful only in the first slice */
	ss = &mgp->ss[0];
	data[i++] = (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->link_up);
	data[i++] = (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->dropped_link_overflow);
	data[i++] =
	    (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->dropped_link_error_or_filtered);
	data[i++] = (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->dropped_छोड़ो);
	data[i++] = (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->dropped_bad_phy);
	data[i++] = (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->dropped_bad_crc32);
	data[i++] = (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->dropped_unicast_filtered);
	data[i++] =
	    (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->dropped_multicast_filtered);
	data[i++] = (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->dropped_runt);
	data[i++] = (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->dropped_overrun);
	data[i++] = (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->dropped_no_small_buffer);
	data[i++] = (अचिन्हित पूर्णांक)ntohl(ss->fw_stats->dropped_no_big_buffer);

	क्रम (slice = 0; slice < mgp->num_slices; slice++) अणु
		ss = &mgp->ss[slice];
		data[i++] = slice;
		data[i++] = (अचिन्हित पूर्णांक)ss->tx.pkt_start;
		data[i++] = (अचिन्हित पूर्णांक)ss->tx.pkt_करोne;
		data[i++] = (अचिन्हित पूर्णांक)ss->tx.req;
		data[i++] = (अचिन्हित पूर्णांक)ss->tx.करोne;
		data[i++] = (अचिन्हित पूर्णांक)ss->rx_small.cnt;
		data[i++] = (अचिन्हित पूर्णांक)ss->rx_big.cnt;
		data[i++] = (अचिन्हित पूर्णांक)ss->tx.wake_queue;
		data[i++] = (अचिन्हित पूर्णांक)ss->tx.stop_queue;
		data[i++] = (अचिन्हित पूर्णांक)ss->tx.linearized;
	पूर्ण
पूर्ण

अटल व्योम myri10ge_set_msglevel(काष्ठा net_device *netdev, u32 value)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);
	mgp->msg_enable = value;
पूर्ण

अटल u32 myri10ge_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);
	वापस mgp->msg_enable;
पूर्ण

/*
 * Use a low-level command to change the LED behavior. Rather than
 * blinking (which is the normal हाल), when identअगरy is used, the
 * yellow LED turns solid.
 */
अटल पूर्णांक myri10ge_led(काष्ठा myri10ge_priv *mgp, पूर्णांक on)
अणु
	काष्ठा mcp_gen_header *hdr;
	काष्ठा device *dev = &mgp->pdev->dev;
	माप_प्रकार hdr_off, pattern_off, hdr_len;
	u32 pattern = 0xfffffffe;

	/* find running firmware header */
	hdr_off = swab32(पढ़ोl(mgp->sram + MCP_HEADER_PTR_OFFSET));
	अगर ((hdr_off & 3) || hdr_off + माप(*hdr) > mgp->sram_size) अणु
		dev_err(dev, "Running firmware has bad header offset (%d)\n",
			(पूर्णांक)hdr_off);
		वापस -EIO;
	पूर्ण
	hdr_len = swab32(पढ़ोl(mgp->sram + hdr_off +
			       दुरत्व(काष्ठा mcp_gen_header, header_length)));
	pattern_off = hdr_off + दुरत्व(काष्ठा mcp_gen_header, led_pattern);
	अगर (pattern_off >= (hdr_len + hdr_off)) अणु
		dev_info(dev, "Firmware does not support LED identification\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!on)
		pattern = swab32(पढ़ोl(mgp->sram + pattern_off + 4));
	ग_लिखोl(swab32(pattern), mgp->sram + pattern_off);
	वापस 0;
पूर्ण

अटल पूर्णांक
myri10ge_phys_id(काष्ठा net_device *netdev, क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(netdev);
	पूर्णांक rc;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		rc = myri10ge_led(mgp, 1);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		rc =  myri10ge_led(mgp, 0);
		अवरोध;

	शेष:
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops myri10ge_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS,
	.get_drvinfo = myri10ge_get_drvinfo,
	.get_coalesce = myri10ge_get_coalesce,
	.set_coalesce = myri10ge_set_coalesce,
	.get_छोड़ोparam = myri10ge_get_छोड़ोparam,
	.set_छोड़ोparam = myri10ge_set_छोड़ोparam,
	.get_ringparam = myri10ge_get_ringparam,
	.get_link = ethtool_op_get_link,
	.get_strings = myri10ge_get_strings,
	.get_sset_count = myri10ge_get_sset_count,
	.get_ethtool_stats = myri10ge_get_ethtool_stats,
	.set_msglevel = myri10ge_set_msglevel,
	.get_msglevel = myri10ge_get_msglevel,
	.set_phys_id = myri10ge_phys_id,
	.get_link_ksettings = myri10ge_get_link_ksettings,
पूर्ण;

अटल पूर्णांक myri10ge_allocate_rings(काष्ठा myri10ge_slice_state *ss)
अणु
	काष्ठा myri10ge_priv *mgp = ss->mgp;
	काष्ठा myri10ge_cmd cmd;
	काष्ठा net_device *dev = mgp->dev;
	पूर्णांक tx_ring_size, rx_ring_size;
	पूर्णांक tx_ring_entries, rx_ring_entries;
	पूर्णांक i, slice, status;
	माप_प्रकार bytes;

	/* get ring sizes */
	slice = ss - mgp->ss;
	cmd.data0 = slice;
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_SEND_RING_SIZE, &cmd, 0);
	tx_ring_size = cmd.data0;
	cmd.data0 = slice;
	status |= myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_RX_RING_SIZE, &cmd, 0);
	अगर (status != 0)
		वापस status;
	rx_ring_size = cmd.data0;

	tx_ring_entries = tx_ring_size / माप(काष्ठा mcp_kreq_ether_send);
	rx_ring_entries = rx_ring_size / माप(काष्ठा mcp_dma_addr);
	ss->tx.mask = tx_ring_entries - 1;
	ss->rx_small.mask = ss->rx_big.mask = rx_ring_entries - 1;

	status = -ENOMEM;

	/* allocate the host shaकरोw rings */

	bytes = 8 + (MYRI10GE_MAX_SEND_DESC_TSO + 4)
	    * माप(*ss->tx.req_list);
	ss->tx.req_bytes = kzalloc(bytes, GFP_KERNEL);
	अगर (ss->tx.req_bytes == शून्य)
		जाओ पात_with_nothing;

	/* ensure req_list entries are aligned to 8 bytes */
	ss->tx.req_list = (काष्ठा mcp_kreq_ether_send *)
	    ALIGN((अचिन्हित दीर्घ)ss->tx.req_bytes, 8);
	ss->tx.queue_active = 0;

	bytes = rx_ring_entries * माप(*ss->rx_small.shaकरोw);
	ss->rx_small.shaकरोw = kzalloc(bytes, GFP_KERNEL);
	अगर (ss->rx_small.shaकरोw == शून्य)
		जाओ पात_with_tx_req_bytes;

	bytes = rx_ring_entries * माप(*ss->rx_big.shaकरोw);
	ss->rx_big.shaकरोw = kzalloc(bytes, GFP_KERNEL);
	अगर (ss->rx_big.shaकरोw == शून्य)
		जाओ पात_with_rx_small_shaकरोw;

	/* allocate the host info rings */

	bytes = tx_ring_entries * माप(*ss->tx.info);
	ss->tx.info = kzalloc(bytes, GFP_KERNEL);
	अगर (ss->tx.info == शून्य)
		जाओ पात_with_rx_big_shaकरोw;

	bytes = rx_ring_entries * माप(*ss->rx_small.info);
	ss->rx_small.info = kzalloc(bytes, GFP_KERNEL);
	अगर (ss->rx_small.info == शून्य)
		जाओ पात_with_tx_info;

	bytes = rx_ring_entries * माप(*ss->rx_big.info);
	ss->rx_big.info = kzalloc(bytes, GFP_KERNEL);
	अगर (ss->rx_big.info == शून्य)
		जाओ पात_with_rx_small_info;

	/* Fill the receive rings */
	ss->rx_big.cnt = 0;
	ss->rx_small.cnt = 0;
	ss->rx_big.fill_cnt = 0;
	ss->rx_small.fill_cnt = 0;
	ss->rx_small.page_offset = MYRI10GE_ALLOC_SIZE;
	ss->rx_big.page_offset = MYRI10GE_ALLOC_SIZE;
	ss->rx_small.watchकरोg_needed = 0;
	ss->rx_big.watchकरोg_needed = 0;
	अगर (mgp->small_bytes == 0) अणु
		ss->rx_small.fill_cnt = ss->rx_small.mask + 1;
	पूर्ण अन्यथा अणु
		myri10ge_alloc_rx_pages(mgp, &ss->rx_small,
					mgp->small_bytes + MXGEFW_PAD, 0);
	पूर्ण

	अगर (ss->rx_small.fill_cnt < ss->rx_small.mask + 1) अणु
		netdev_err(dev, "slice-%d: alloced only %d small bufs\n",
			   slice, ss->rx_small.fill_cnt);
		जाओ पात_with_rx_small_ring;
	पूर्ण

	myri10ge_alloc_rx_pages(mgp, &ss->rx_big, mgp->big_bytes, 0);
	अगर (ss->rx_big.fill_cnt < ss->rx_big.mask + 1) अणु
		netdev_err(dev, "slice-%d: alloced only %d big bufs\n",
			   slice, ss->rx_big.fill_cnt);
		जाओ पात_with_rx_big_ring;
	पूर्ण

	वापस 0;

पात_with_rx_big_ring:
	क्रम (i = ss->rx_big.cnt; i < ss->rx_big.fill_cnt; i++) अणु
		पूर्णांक idx = i & ss->rx_big.mask;
		myri10ge_unmap_rx_page(mgp->pdev, &ss->rx_big.info[idx],
				       mgp->big_bytes);
		put_page(ss->rx_big.info[idx].page);
	पूर्ण

पात_with_rx_small_ring:
	अगर (mgp->small_bytes == 0)
		ss->rx_small.fill_cnt = ss->rx_small.cnt;
	क्रम (i = ss->rx_small.cnt; i < ss->rx_small.fill_cnt; i++) अणु
		पूर्णांक idx = i & ss->rx_small.mask;
		myri10ge_unmap_rx_page(mgp->pdev, &ss->rx_small.info[idx],
				       mgp->small_bytes + MXGEFW_PAD);
		put_page(ss->rx_small.info[idx].page);
	पूर्ण

	kमुक्त(ss->rx_big.info);

पात_with_rx_small_info:
	kमुक्त(ss->rx_small.info);

पात_with_tx_info:
	kमुक्त(ss->tx.info);

पात_with_rx_big_shaकरोw:
	kमुक्त(ss->rx_big.shaकरोw);

पात_with_rx_small_shaकरोw:
	kमुक्त(ss->rx_small.shaकरोw);

पात_with_tx_req_bytes:
	kमुक्त(ss->tx.req_bytes);
	ss->tx.req_bytes = शून्य;
	ss->tx.req_list = शून्य;

पात_with_nothing:
	वापस status;
पूर्ण

अटल व्योम myri10ge_मुक्त_rings(काष्ठा myri10ge_slice_state *ss)
अणु
	काष्ठा myri10ge_priv *mgp = ss->mgp;
	काष्ठा sk_buff *skb;
	काष्ठा myri10ge_tx_buf *tx;
	पूर्णांक i, len, idx;

	/* If not allocated, skip it */
	अगर (ss->tx.req_list == शून्य)
		वापस;

	क्रम (i = ss->rx_big.cnt; i < ss->rx_big.fill_cnt; i++) अणु
		idx = i & ss->rx_big.mask;
		अगर (i == ss->rx_big.fill_cnt - 1)
			ss->rx_big.info[idx].page_offset = MYRI10GE_ALLOC_SIZE;
		myri10ge_unmap_rx_page(mgp->pdev, &ss->rx_big.info[idx],
				       mgp->big_bytes);
		put_page(ss->rx_big.info[idx].page);
	पूर्ण

	अगर (mgp->small_bytes == 0)
		ss->rx_small.fill_cnt = ss->rx_small.cnt;
	क्रम (i = ss->rx_small.cnt; i < ss->rx_small.fill_cnt; i++) अणु
		idx = i & ss->rx_small.mask;
		अगर (i == ss->rx_small.fill_cnt - 1)
			ss->rx_small.info[idx].page_offset =
			    MYRI10GE_ALLOC_SIZE;
		myri10ge_unmap_rx_page(mgp->pdev, &ss->rx_small.info[idx],
				       mgp->small_bytes + MXGEFW_PAD);
		put_page(ss->rx_small.info[idx].page);
	पूर्ण
	tx = &ss->tx;
	जबतक (tx->करोne != tx->req) अणु
		idx = tx->करोne & tx->mask;
		skb = tx->info[idx].skb;

		/* Mark as मुक्त */
		tx->info[idx].skb = शून्य;
		tx->करोne++;
		len = dma_unmap_len(&tx->info[idx], len);
		dma_unmap_len_set(&tx->info[idx], len, 0);
		अगर (skb) अणु
			ss->stats.tx_dropped++;
			dev_kमुक्त_skb_any(skb);
			अगर (len)
				pci_unmap_single(mgp->pdev,
						 dma_unmap_addr(&tx->info[idx],
								bus), len,
						 PCI_DMA_TODEVICE);
		पूर्ण अन्यथा अणु
			अगर (len)
				pci_unmap_page(mgp->pdev,
					       dma_unmap_addr(&tx->info[idx],
							      bus), len,
					       PCI_DMA_TODEVICE);
		पूर्ण
	पूर्ण
	kमुक्त(ss->rx_big.info);

	kमुक्त(ss->rx_small.info);

	kमुक्त(ss->tx.info);

	kमुक्त(ss->rx_big.shaकरोw);

	kमुक्त(ss->rx_small.shaकरोw);

	kमुक्त(ss->tx.req_bytes);
	ss->tx.req_bytes = शून्य;
	ss->tx.req_list = शून्य;
पूर्ण

अटल पूर्णांक myri10ge_request_irq(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा pci_dev *pdev = mgp->pdev;
	काष्ठा myri10ge_slice_state *ss;
	काष्ठा net_device *netdev = mgp->dev;
	पूर्णांक i;
	पूर्णांक status;

	mgp->msi_enabled = 0;
	mgp->msix_enabled = 0;
	status = 0;
	अगर (myri10ge_msi) अणु
		अगर (mgp->num_slices > 1) अणु
			status = pci_enable_msix_range(pdev, mgp->msix_vectors,
					mgp->num_slices, mgp->num_slices);
			अगर (status < 0) अणु
				dev_err(&pdev->dev,
					"Error %d setting up MSI-X\n", status);
				वापस status;
			पूर्ण
			mgp->msix_enabled = 1;
		पूर्ण
		अगर (mgp->msix_enabled == 0) अणु
			status = pci_enable_msi(pdev);
			अगर (status != 0) अणु
				dev_err(&pdev->dev,
					"Error %d setting up MSI; falling back to xPIC\n",
					status);
			पूर्ण अन्यथा अणु
				mgp->msi_enabled = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (mgp->msix_enabled) अणु
		क्रम (i = 0; i < mgp->num_slices; i++) अणु
			ss = &mgp->ss[i];
			snम_लिखो(ss->irq_desc, माप(ss->irq_desc),
				 "%s:slice-%d", netdev->name, i);
			status = request_irq(mgp->msix_vectors[i].vector,
					     myri10ge_पूर्णांकr, 0, ss->irq_desc,
					     ss);
			अगर (status != 0) अणु
				dev_err(&pdev->dev,
					"slice %d failed to allocate IRQ\n", i);
				i--;
				जबतक (i >= 0) अणु
					मुक्त_irq(mgp->msix_vectors[i].vector,
						 &mgp->ss[i]);
					i--;
				पूर्ण
				pci_disable_msix(pdev);
				वापस status;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		status = request_irq(pdev->irq, myri10ge_पूर्णांकr, IRQF_SHARED,
				     mgp->dev->name, &mgp->ss[0]);
		अगर (status != 0) अणु
			dev_err(&pdev->dev, "failed to allocate IRQ\n");
			अगर (mgp->msi_enabled)
				pci_disable_msi(pdev);
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम myri10ge_मुक्त_irq(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा pci_dev *pdev = mgp->pdev;
	पूर्णांक i;

	अगर (mgp->msix_enabled) अणु
		क्रम (i = 0; i < mgp->num_slices; i++)
			मुक्त_irq(mgp->msix_vectors[i].vector, &mgp->ss[i]);
	पूर्ण अन्यथा अणु
		मुक्त_irq(pdev->irq, &mgp->ss[0]);
	पूर्ण
	अगर (mgp->msi_enabled)
		pci_disable_msi(pdev);
	अगर (mgp->msix_enabled)
		pci_disable_msix(pdev);
पूर्ण

अटल पूर्णांक myri10ge_get_txrx(काष्ठा myri10ge_priv *mgp, पूर्णांक slice)
अणु
	काष्ठा myri10ge_cmd cmd;
	काष्ठा myri10ge_slice_state *ss;
	पूर्णांक status;

	ss = &mgp->ss[slice];
	status = 0;
	अगर (slice == 0 || (mgp->dev->real_num_tx_queues > 1)) अणु
		cmd.data0 = slice;
		status = myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_SEND_OFFSET,
					   &cmd, 0);
		ss->tx.lanai = (काष्ठा mcp_kreq_ether_send __iomem *)
		    (mgp->sram + cmd.data0);
	पूर्ण
	cmd.data0 = slice;
	status |= myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_SMALL_RX_OFFSET,
				    &cmd, 0);
	ss->rx_small.lanai = (काष्ठा mcp_kreq_ether_recv __iomem *)
	    (mgp->sram + cmd.data0);

	cmd.data0 = slice;
	status |= myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_BIG_RX_OFFSET, &cmd, 0);
	ss->rx_big.lanai = (काष्ठा mcp_kreq_ether_recv __iomem *)
	    (mgp->sram + cmd.data0);

	ss->tx.send_go = (__iomem __be32 *)
	    (mgp->sram + MXGEFW_ETH_SEND_GO + 64 * slice);
	ss->tx.send_stop = (__iomem __be32 *)
	    (mgp->sram + MXGEFW_ETH_SEND_STOP + 64 * slice);
	वापस status;

पूर्ण

अटल पूर्णांक myri10ge_set_stats(काष्ठा myri10ge_priv *mgp, पूर्णांक slice)
अणु
	काष्ठा myri10ge_cmd cmd;
	काष्ठा myri10ge_slice_state *ss;
	पूर्णांक status;

	ss = &mgp->ss[slice];
	cmd.data0 = MYRI10GE_LOWPART_TO_U32(ss->fw_stats_bus);
	cmd.data1 = MYRI10GE_HIGHPART_TO_U32(ss->fw_stats_bus);
	cmd.data2 = माप(काष्ठा mcp_irq_data) | (slice << 16);
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_STATS_DMA_V2, &cmd, 0);
	अगर (status == -ENOSYS) अणु
		dma_addr_t bus = ss->fw_stats_bus;
		अगर (slice != 0)
			वापस -EINVAL;
		bus += दुरत्व(काष्ठा mcp_irq_data, send_करोne_count);
		cmd.data0 = MYRI10GE_LOWPART_TO_U32(bus);
		cmd.data1 = MYRI10GE_HIGHPART_TO_U32(bus);
		status = myri10ge_send_cmd(mgp,
					   MXGEFW_CMD_SET_STATS_DMA_OBSOLETE,
					   &cmd, 0);
		/* Firmware cannot support multicast without STATS_DMA_V2 */
		mgp->fw_multicast_support = 0;
	पूर्ण अन्यथा अणु
		mgp->fw_multicast_support = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक myri10ge_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा myri10ge_slice_state *ss;
	काष्ठा myri10ge_priv *mgp = netdev_priv(dev);
	काष्ठा myri10ge_cmd cmd;
	पूर्णांक i, status, big_घात2, slice;
	u8 __iomem *itable;

	अगर (mgp->running != MYRI10GE_ETH_STOPPED)
		वापस -EBUSY;

	mgp->running = MYRI10GE_ETH_STARTING;
	status = myri10ge_reset(mgp);
	अगर (status != 0) अणु
		netdev_err(dev, "failed reset\n");
		जाओ पात_with_nothing;
	पूर्ण

	अगर (mgp->num_slices > 1) अणु
		cmd.data0 = mgp->num_slices;
		cmd.data1 = MXGEFW_SLICE_INTR_MODE_ONE_PER_SLICE;
		अगर (mgp->dev->real_num_tx_queues > 1)
			cmd.data1 |= MXGEFW_SLICE_ENABLE_MULTIPLE_TX_QUEUES;
		status = myri10ge_send_cmd(mgp, MXGEFW_CMD_ENABLE_RSS_QUEUES,
					   &cmd, 0);
		अगर (status != 0) अणु
			netdev_err(dev, "failed to set number of slices\n");
			जाओ पात_with_nothing;
		पूर्ण
		/* setup the indirection table */
		cmd.data0 = mgp->num_slices;
		status = myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_RSS_TABLE_SIZE,
					   &cmd, 0);

		status |= myri10ge_send_cmd(mgp,
					    MXGEFW_CMD_GET_RSS_TABLE_OFFSET,
					    &cmd, 0);
		अगर (status != 0) अणु
			netdev_err(dev, "failed to setup rss tables\n");
			जाओ पात_with_nothing;
		पूर्ण

		/* just enable an identity mapping */
		itable = mgp->sram + cmd.data0;
		क्रम (i = 0; i < mgp->num_slices; i++)
			__raw_ग_लिखोb(i, &itable[i]);

		cmd.data0 = 1;
		cmd.data1 = myri10ge_rss_hash;
		status = myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_RSS_ENABLE,
					   &cmd, 0);
		अगर (status != 0) अणु
			netdev_err(dev, "failed to enable slices\n");
			जाओ पात_with_nothing;
		पूर्ण
	पूर्ण

	status = myri10ge_request_irq(mgp);
	अगर (status != 0)
		जाओ पात_with_nothing;

	/* decide what small buffer size to use.  For good TCP rx
	 * perक्रमmance, it is important to not receive 1514 byte
	 * frames पूर्णांकo jumbo buffers, as it confuses the socket buffer
	 * accounting code, leading to drops and erratic perक्रमmance.
	 */

	अगर (dev->mtu <= ETH_DATA_LEN)
		/* enough क्रम a TCP header */
		mgp->small_bytes = (128 > SMP_CACHE_BYTES)
		    ? (128 - MXGEFW_PAD)
		    : (SMP_CACHE_BYTES - MXGEFW_PAD);
	अन्यथा
		/* enough क्रम a vlan encapsulated ETH_DATA_LEN frame */
		mgp->small_bytes = VLAN_ETH_FRAME_LEN;

	/* Override the small buffer size? */
	अगर (myri10ge_small_bytes >= 0)
		mgp->small_bytes = myri10ge_small_bytes;

	/* Firmware needs the big buff size as a घातer of 2.  Lie and
	 * tell him the buffer is larger, because we only use 1
	 * buffer/pkt, and the mtu will prevent overruns.
	 */
	big_घात2 = dev->mtu + ETH_HLEN + VLAN_HLEN + MXGEFW_PAD;
	अगर (big_घात2 < MYRI10GE_ALLOC_SIZE / 2) अणु
		जबतक (!is_घातer_of_2(big_घात2))
			big_घात2++;
		mgp->big_bytes = dev->mtu + ETH_HLEN + VLAN_HLEN + MXGEFW_PAD;
	पूर्ण अन्यथा अणु
		big_घात2 = MYRI10GE_ALLOC_SIZE;
		mgp->big_bytes = big_घात2;
	पूर्ण

	/* setup the per-slice data काष्ठाures */
	क्रम (slice = 0; slice < mgp->num_slices; slice++) अणु
		ss = &mgp->ss[slice];

		status = myri10ge_get_txrx(mgp, slice);
		अगर (status != 0) अणु
			netdev_err(dev, "failed to get ring sizes or locations\n");
			जाओ पात_with_rings;
		पूर्ण
		status = myri10ge_allocate_rings(ss);
		अगर (status != 0)
			जाओ पात_with_rings;

		/* only firmware which supports multiple TX queues
		 * supports setting up the tx stats on non-zero
		 * slices */
		अगर (slice == 0 || mgp->dev->real_num_tx_queues > 1)
			status = myri10ge_set_stats(mgp, slice);
		अगर (status) अणु
			netdev_err(dev, "Couldn't set stats DMA\n");
			जाओ पात_with_rings;
		पूर्ण

		/* must happen prior to any irq */
		napi_enable(&(ss)->napi);
	पूर्ण

	/* now give firmware buffers sizes, and MTU */
	cmd.data0 = dev->mtu + ETH_HLEN + VLAN_HLEN;
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_MTU, &cmd, 0);
	cmd.data0 = mgp->small_bytes;
	status |=
	    myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_SMALL_BUFFER_SIZE, &cmd, 0);
	cmd.data0 = big_घात2;
	status |=
	    myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_BIG_BUFFER_SIZE, &cmd, 0);
	अगर (status) अणु
		netdev_err(dev, "Couldn't set buffer sizes\n");
		जाओ पात_with_rings;
	पूर्ण

	/*
	 * Set Linux style TSO mode; this is needed only on newer
	 *  firmware versions.  Older versions शेष to Linux
	 *  style TSO
	 */
	cmd.data0 = 0;
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_TSO_MODE, &cmd, 0);
	अगर (status && status != -ENOSYS) अणु
		netdev_err(dev, "Couldn't set TSO mode\n");
		जाओ पात_with_rings;
	पूर्ण

	mgp->link_state = ~0U;
	mgp->rdma_tags_available = 15;

	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_ETHERNET_UP, &cmd, 0);
	अगर (status) अणु
		netdev_err(dev, "Couldn't bring up link\n");
		जाओ पात_with_rings;
	पूर्ण

	mgp->running = MYRI10GE_ETH_RUNNING;
	mgp->watchकरोg_समयr.expires = jअगरfies + myri10ge_watchकरोg_समयout * HZ;
	add_समयr(&mgp->watchकरोg_समयr);
	netअगर_tx_wake_all_queues(dev);

	वापस 0;

पात_with_rings:
	जबतक (slice) अणु
		slice--;
		napi_disable(&mgp->ss[slice].napi);
	पूर्ण
	क्रम (i = 0; i < mgp->num_slices; i++)
		myri10ge_मुक्त_rings(&mgp->ss[i]);

	myri10ge_मुक्त_irq(mgp);

पात_with_nothing:
	mgp->running = MYRI10GE_ETH_STOPPED;
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक myri10ge_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(dev);
	काष्ठा myri10ge_cmd cmd;
	पूर्णांक status, old_करोwn_cnt;
	पूर्णांक i;

	अगर (mgp->running != MYRI10GE_ETH_RUNNING)
		वापस 0;

	अगर (mgp->ss[0].tx.req_bytes == शून्य)
		वापस 0;

	del_समयr_sync(&mgp->watchकरोg_समयr);
	mgp->running = MYRI10GE_ETH_STOPPING;
	क्रम (i = 0; i < mgp->num_slices; i++)
		napi_disable(&mgp->ss[i].napi);

	netअगर_carrier_off(dev);

	netअगर_tx_stop_all_queues(dev);
	अगर (mgp->rebooted == 0) अणु
		old_करोwn_cnt = mgp->करोwn_cnt;
		mb();
		status =
		    myri10ge_send_cmd(mgp, MXGEFW_CMD_ETHERNET_DOWN, &cmd, 0);
		अगर (status)
			netdev_err(dev, "Couldn't bring down link\n");

		रुको_event_समयout(mgp->करोwn_wq, old_करोwn_cnt != mgp->करोwn_cnt,
				   HZ);
		अगर (old_करोwn_cnt == mgp->करोwn_cnt)
			netdev_err(dev, "never got down irq\n");
	पूर्ण
	netअगर_tx_disable(dev);
	myri10ge_मुक्त_irq(mgp);
	क्रम (i = 0; i < mgp->num_slices; i++)
		myri10ge_मुक्त_rings(&mgp->ss[i]);

	mgp->running = MYRI10GE_ETH_STOPPED;
	वापस 0;
पूर्ण

/* copy an array of काष्ठा mcp_kreq_ether_send's to the mcp.  Copy
 * backwards one at a समय and handle ring wraps */

अटल अंतरभूत व्योम
myri10ge_submit_req_backwards(काष्ठा myri10ge_tx_buf *tx,
			      काष्ठा mcp_kreq_ether_send *src, पूर्णांक cnt)
अणु
	पूर्णांक idx, starting_slot;
	starting_slot = tx->req;
	जबतक (cnt > 1) अणु
		cnt--;
		idx = (starting_slot + cnt) & tx->mask;
		myri10ge_pio_copy(&tx->lanai[idx], &src[cnt], माप(*src));
		mb();
	पूर्ण
पूर्ण

/*
 * copy an array of काष्ठा mcp_kreq_ether_send's to the mcp.  Copy
 * at most 32 bytes at a समय, so as to aव्योम involving the software
 * pio handler in the nic.   We re-ग_लिखो the first segment's flags
 * to mark them valid only after writing the entire chain.
 */

अटल अंतरभूत व्योम
myri10ge_submit_req(काष्ठा myri10ge_tx_buf *tx, काष्ठा mcp_kreq_ether_send *src,
		    पूर्णांक cnt)
अणु
	पूर्णांक idx, i;
	काष्ठा mcp_kreq_ether_send __iomem *dstp, *dst;
	काष्ठा mcp_kreq_ether_send *srcp;
	u8 last_flags;

	idx = tx->req & tx->mask;

	last_flags = src->flags;
	src->flags = 0;
	mb();
	dst = dstp = &tx->lanai[idx];
	srcp = src;

	अगर ((idx + cnt) < tx->mask) अणु
		क्रम (i = 0; i < (cnt - 1); i += 2) अणु
			myri10ge_pio_copy(dstp, srcp, 2 * माप(*src));
			mb();	/* क्रमce ग_लिखो every 32 bytes */
			srcp += 2;
			dstp += 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* submit all but the first request, and ensure
		 * that it is submitted below */
		myri10ge_submit_req_backwards(tx, src, cnt);
		i = 0;
	पूर्ण
	अगर (i < cnt) अणु
		/* submit the first request */
		myri10ge_pio_copy(dstp, srcp, माप(*src));
		mb();		/* barrier beक्रमe setting valid flag */
	पूर्ण

	/* re-ग_लिखो the last 32-bits with the valid flags */
	src->flags = last_flags;
	put_be32(*((__be32 *) src + 3), (__be32 __iomem *) dst + 3);
	tx->req += cnt;
	mb();
पूर्ण

अटल व्योम myri10ge_unmap_tx_dma(काष्ठा myri10ge_priv *mgp,
				  काष्ठा myri10ge_tx_buf *tx, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक len;
	पूर्णांक last_idx;

	/* Free any DMA resources we've alloced and clear out the skb slot */
	last_idx = (idx + 1) & tx->mask;
	idx = tx->req & tx->mask;
	करो अणु
		len = dma_unmap_len(&tx->info[idx], len);
		अगर (len) अणु
			अगर (tx->info[idx].skb != शून्य)
				pci_unmap_single(mgp->pdev,
						 dma_unmap_addr(&tx->info[idx],
								bus), len,
						 PCI_DMA_TODEVICE);
			अन्यथा
				pci_unmap_page(mgp->pdev,
					       dma_unmap_addr(&tx->info[idx],
							      bus), len,
					       PCI_DMA_TODEVICE);
			dma_unmap_len_set(&tx->info[idx], len, 0);
			tx->info[idx].skb = शून्य;
		पूर्ण
		idx = (idx + 1) & tx->mask;
	पूर्ण जबतक (idx != last_idx);
पूर्ण

/*
 * Transmit a packet.  We need to split the packet so that a single
 * segment करोes not cross myri10ge->tx_boundary, so this makes segment
 * counting tricky.  So rather than try to count segments up front, we
 * just give up अगर there are too few segments to hold a reasonably
 * fragmented packet currently available.  If we run
 * out of segments जबतक preparing a packet क्रम DMA, we just linearize
 * it and try again.
 */

अटल netdev_tx_t myri10ge_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(dev);
	काष्ठा myri10ge_slice_state *ss;
	काष्ठा mcp_kreq_ether_send *req;
	काष्ठा myri10ge_tx_buf *tx;
	skb_frag_t *frag;
	काष्ठा netdev_queue *netdev_queue;
	dma_addr_t bus;
	u32 low;
	__be32 high_swapped;
	अचिन्हित पूर्णांक len;
	पूर्णांक idx, avail, frag_cnt, frag_idx, count, mss, max_segments;
	u16 pseuकरो_hdr_offset, cksum_offset, queue;
	पूर्णांक cum_len, seglen, boundary, rdma_count;
	u8 flags, odd_flag;

	queue = skb_get_queue_mapping(skb);
	ss = &mgp->ss[queue];
	netdev_queue = netdev_get_tx_queue(mgp->dev, queue);
	tx = &ss->tx;

again:
	req = tx->req_list;
	avail = tx->mask - 1 - (tx->req - tx->करोne);

	mss = 0;
	max_segments = MXGEFW_MAX_SEND_DESC;

	अगर (skb_is_gso(skb)) अणु
		mss = skb_shinfo(skb)->gso_size;
		max_segments = MYRI10GE_MAX_SEND_DESC_TSO;
	पूर्ण

	अगर ((unlikely(avail < max_segments))) अणु
		/* we are out of transmit resources */
		tx->stop_queue++;
		netअगर_tx_stop_queue(netdev_queue);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Setup checksum offloading, अगर needed */
	cksum_offset = 0;
	pseuकरो_hdr_offset = 0;
	odd_flag = 0;
	flags = (MXGEFW_FLAGS_NO_TSO | MXGEFW_FLAGS_FIRST);
	अगर (likely(skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		cksum_offset = skb_checksum_start_offset(skb);
		pseuकरो_hdr_offset = cksum_offset + skb->csum_offset;
		/* If the headers are excessively large, then we must
		 * fall back to a software checksum */
		अगर (unlikely(!mss && (cksum_offset > 255 ||
				      pseuकरो_hdr_offset > 127))) अणु
			अगर (skb_checksum_help(skb))
				जाओ drop;
			cksum_offset = 0;
			pseuकरो_hdr_offset = 0;
		पूर्ण अन्यथा अणु
			odd_flag = MXGEFW_FLAGS_ALIGN_ODD;
			flags |= MXGEFW_FLAGS_CKSUM;
		पूर्ण
	पूर्ण

	cum_len = 0;

	अगर (mss) अणु		/* TSO */
		/* this हटाओs any CKSUM flag from beक्रमe */
		flags = (MXGEFW_FLAGS_TSO_HDR | MXGEFW_FLAGS_FIRST);

		/* negative cum_len signअगरies to the
		 * send loop that we are still in the
		 * header portion of the TSO packet.
		 * TSO header can be at most 1KB दीर्घ */
		cum_len = -(skb_transport_offset(skb) + tcp_hdrlen(skb));

		/* क्रम IPv6 TSO, the checksum offset stores the
		 * TCP header length, to save the firmware from
		 * the need to parse the headers */
		अगर (skb_is_gso_v6(skb)) अणु
			cksum_offset = tcp_hdrlen(skb);
			/* Can only handle headers <= max_tso6 दीर्घ */
			अगर (unlikely(-cum_len > mgp->max_tso6))
				वापस myri10ge_sw_tso(skb, dev);
		पूर्ण
		/* क्रम TSO, pseuकरो_hdr_offset holds mss.
		 * The firmware figures out where to put
		 * the checksum by parsing the header. */
		pseuकरो_hdr_offset = mss;
	पूर्ण अन्यथा
		/* Mark small packets, and pad out tiny packets */
	अगर (skb->len <= MXGEFW_SEND_SMALL_SIZE) अणु
		flags |= MXGEFW_FLAGS_SMALL;

		/* pad frames to at least ETH_ZLEN bytes */
		अगर (eth_skb_pad(skb)) अणु
			/* The packet is gone, so we must
			 * वापस 0 */
			ss->stats.tx_dropped += 1;
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण

	/* map the skb क्रम DMA */
	len = skb_headlen(skb);
	bus = pci_map_single(mgp->pdev, skb->data, len, PCI_DMA_TODEVICE);
	अगर (unlikely(pci_dma_mapping_error(mgp->pdev, bus)))
		जाओ drop;

	idx = tx->req & tx->mask;
	tx->info[idx].skb = skb;
	dma_unmap_addr_set(&tx->info[idx], bus, bus);
	dma_unmap_len_set(&tx->info[idx], len, len);

	frag_cnt = skb_shinfo(skb)->nr_frags;
	frag_idx = 0;
	count = 0;
	rdma_count = 0;

	/* "rdma_count" is the number of RDMAs beदीर्घing to the
	 * current packet BEFORE the current send request. For
	 * non-TSO packets, this is equal to "count".
	 * For TSO packets, rdma_count needs to be reset
	 * to 0 after a segment cut.
	 *
	 * The rdma_count field of the send request is
	 * the number of RDMAs of the packet starting at
	 * that request. For TSO send requests with one ore more cuts
	 * in the middle, this is the number of RDMAs starting
	 * after the last cut in the request. All previous
	 * segments beक्रमe the last cut implicitly have 1 RDMA.
	 *
	 * Since the number of RDMAs is not known beक्रमehand,
	 * it must be filled-in retroactively - after each
	 * segmentation cut or at the end of the entire packet.
	 */

	जबतक (1) अणु
		/* Break the SKB or Fragment up पूर्णांकo pieces which
		 * करो not cross mgp->tx_boundary */
		low = MYRI10GE_LOWPART_TO_U32(bus);
		high_swapped = htonl(MYRI10GE_HIGHPART_TO_U32(bus));
		जबतक (len) अणु
			u8 flags_next;
			पूर्णांक cum_len_next;

			अगर (unlikely(count == max_segments))
				जाओ पात_linearize;

			boundary =
			    (low + mgp->tx_boundary) & ~(mgp->tx_boundary - 1);
			seglen = boundary - low;
			अगर (seglen > len)
				seglen = len;
			flags_next = flags & ~MXGEFW_FLAGS_FIRST;
			cum_len_next = cum_len + seglen;
			अगर (mss) अणु	/* TSO */
				(req - rdma_count)->rdma_count = rdma_count + 1;

				अगर (likely(cum_len >= 0)) अणु	/* payload */
					पूर्णांक next_is_first, chop;

					chop = (cum_len_next > mss);
					cum_len_next = cum_len_next % mss;
					next_is_first = (cum_len_next == 0);
					flags |= chop * MXGEFW_FLAGS_TSO_CHOP;
					flags_next |= next_is_first *
					    MXGEFW_FLAGS_FIRST;
					rdma_count |= -(chop | next_is_first);
					rdma_count += chop & ~next_is_first;
				पूर्ण अन्यथा अगर (likely(cum_len_next >= 0)) अणु	/* header ends */
					पूर्णांक small;

					rdma_count = -1;
					cum_len_next = 0;
					seglen = -cum_len;
					small = (mss <= MXGEFW_SEND_SMALL_SIZE);
					flags_next = MXGEFW_FLAGS_TSO_PLD |
					    MXGEFW_FLAGS_FIRST |
					    (small * MXGEFW_FLAGS_SMALL);
				पूर्ण
			पूर्ण
			req->addr_high = high_swapped;
			req->addr_low = htonl(low);
			req->pseuकरो_hdr_offset = htons(pseuकरो_hdr_offset);
			req->pad = 0;	/* complete solid 16-byte block; करोes this matter? */
			req->rdma_count = 1;
			req->length = htons(seglen);
			req->cksum_offset = cksum_offset;
			req->flags = flags | ((cum_len & 1) * odd_flag);

			low += seglen;
			len -= seglen;
			cum_len = cum_len_next;
			flags = flags_next;
			req++;
			count++;
			rdma_count++;
			अगर (cksum_offset != 0 && !(mss && skb_is_gso_v6(skb))) अणु
				अगर (unlikely(cksum_offset > seglen))
					cksum_offset -= seglen;
				अन्यथा
					cksum_offset = 0;
			पूर्ण
		पूर्ण
		अगर (frag_idx == frag_cnt)
			अवरोध;

		/* map next fragment क्रम DMA */
		frag = &skb_shinfo(skb)->frags[frag_idx];
		frag_idx++;
		len = skb_frag_size(frag);
		bus = skb_frag_dma_map(&mgp->pdev->dev, frag, 0, len,
				       DMA_TO_DEVICE);
		अगर (unlikely(pci_dma_mapping_error(mgp->pdev, bus))) अणु
			myri10ge_unmap_tx_dma(mgp, tx, idx);
			जाओ drop;
		पूर्ण
		idx = (count + tx->req) & tx->mask;
		dma_unmap_addr_set(&tx->info[idx], bus, bus);
		dma_unmap_len_set(&tx->info[idx], len, len);
	पूर्ण

	(req - rdma_count)->rdma_count = rdma_count;
	अगर (mss)
		करो अणु
			req--;
			req->flags |= MXGEFW_FLAGS_TSO_LAST;
		पूर्ण जबतक (!(req->flags & (MXGEFW_FLAGS_TSO_CHOP |
					 MXGEFW_FLAGS_FIRST)));
	idx = ((count - 1) + tx->req) & tx->mask;
	tx->info[idx].last = 1;
	myri10ge_submit_req(tx, tx->req_list, count);
	/* अगर using multiple tx queues, make sure NIC polls the
	 * current slice */
	अगर ((mgp->dev->real_num_tx_queues > 1) && tx->queue_active == 0) अणु
		tx->queue_active = 1;
		put_be32(htonl(1), tx->send_go);
		mb();
	पूर्ण
	tx->pkt_start++;
	अगर ((avail - count) < MXGEFW_MAX_SEND_DESC) अणु
		tx->stop_queue++;
		netअगर_tx_stop_queue(netdev_queue);
	पूर्ण
	वापस NETDEV_TX_OK;

पात_linearize:
	myri10ge_unmap_tx_dma(mgp, tx, idx);

	अगर (skb_is_gso(skb)) अणु
		netdev_err(mgp->dev, "TSO but wanted to linearize?!?!?\n");
		जाओ drop;
	पूर्ण

	अगर (skb_linearize(skb))
		जाओ drop;

	tx->linearized++;
	जाओ again;

drop:
	dev_kमुक्त_skb_any(skb);
	ss->stats.tx_dropped += 1;
	वापस NETDEV_TX_OK;

पूर्ण

अटल netdev_tx_t myri10ge_sw_tso(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	काष्ठा sk_buff *segs, *curr, *next;
	काष्ठा myri10ge_priv *mgp = netdev_priv(dev);
	काष्ठा myri10ge_slice_state *ss;
	netdev_tx_t status;

	segs = skb_gso_segment(skb, dev->features & ~NETIF_F_TSO6);
	अगर (IS_ERR(segs))
		जाओ drop;

	skb_list_walk_safe(segs, curr, next) अणु
		skb_mark_not_on_list(curr);
		status = myri10ge_xmit(curr, dev);
		अगर (status != 0) अणु
			dev_kमुक्त_skb_any(curr);
			अगर (segs != शून्य) अणु
				curr = segs;
				segs = next;
				curr->next = शून्य;
				dev_kमुक्त_skb_any(segs);
			पूर्ण
			जाओ drop;
		पूर्ण
	पूर्ण
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;

drop:
	ss = &mgp->ss[skb_get_queue_mapping(skb)];
	dev_kमुक्त_skb_any(skb);
	ss->stats.tx_dropped += 1;
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम myri10ge_get_stats(काष्ठा net_device *dev,
			       काष्ठा rtnl_link_stats64 *stats)
अणु
	स्थिर काष्ठा myri10ge_priv *mgp = netdev_priv(dev);
	स्थिर काष्ठा myri10ge_slice_netstats *slice_stats;
	पूर्णांक i;

	क्रम (i = 0; i < mgp->num_slices; i++) अणु
		slice_stats = &mgp->ss[i].stats;
		stats->rx_packets += slice_stats->rx_packets;
		stats->tx_packets += slice_stats->tx_packets;
		stats->rx_bytes += slice_stats->rx_bytes;
		stats->tx_bytes += slice_stats->tx_bytes;
		stats->rx_dropped += slice_stats->rx_dropped;
		stats->tx_dropped += slice_stats->tx_dropped;
	पूर्ण
पूर्ण

अटल व्योम myri10ge_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(dev);
	काष्ठा myri10ge_cmd cmd;
	काष्ठा netdev_hw_addr *ha;
	__be32 data[2] = अणु 0, 0 पूर्ण;
	पूर्णांक err;

	/* can be called from atomic contexts,
	 * pass 1 to क्रमce atomicity in myri10ge_send_cmd() */
	myri10ge_change_promisc(mgp, dev->flags & IFF_PROMISC, 1);

	/* This firmware is known to not support multicast */
	अगर (!mgp->fw_multicast_support)
		वापस;

	/* Disable multicast filtering */

	err = myri10ge_send_cmd(mgp, MXGEFW_ENABLE_ALLMULTI, &cmd, 1);
	अगर (err != 0) अणु
		netdev_err(dev, "Failed MXGEFW_ENABLE_ALLMULTI, error status: %d\n",
			   err);
		जाओ पात;
	पूर्ण

	अगर ((dev->flags & IFF_ALLMULTI) || mgp->aकरोpted_rx_filter_bug) अणु
		/* request to disable multicast filtering, so quit here */
		वापस;
	पूर्ण

	/* Flush the filters */

	err = myri10ge_send_cmd(mgp, MXGEFW_LEAVE_ALL_MULTICAST_GROUPS,
				&cmd, 1);
	अगर (err != 0) अणु
		netdev_err(dev, "Failed MXGEFW_LEAVE_ALL_MULTICAST_GROUPS, error status: %d\n",
			   err);
		जाओ पात;
	पूर्ण

	/* Walk the multicast list, and add each address */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		स_नकल(data, &ha->addr, ETH_ALEN);
		cmd.data0 = ntohl(data[0]);
		cmd.data1 = ntohl(data[1]);
		err = myri10ge_send_cmd(mgp, MXGEFW_JOIN_MULTICAST_GROUP,
					&cmd, 1);

		अगर (err != 0) अणु
			netdev_err(dev, "Failed MXGEFW_JOIN_MULTICAST_GROUP, error status:%d %pM\n",
				   err, ha->addr);
			जाओ पात;
		पूर्ण
	पूर्ण
	/* Enable multicast filtering */
	err = myri10ge_send_cmd(mgp, MXGEFW_DISABLE_ALLMULTI, &cmd, 1);
	अगर (err != 0) अणु
		netdev_err(dev, "Failed MXGEFW_DISABLE_ALLMULTI, error status: %d\n",
			   err);
		जाओ पात;
	पूर्ण

	वापस;

पात:
	वापस;
पूर्ण

अटल पूर्णांक myri10ge_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = addr;
	काष्ठा myri10ge_priv *mgp = netdev_priv(dev);
	पूर्णांक status;

	अगर (!is_valid_ether_addr(sa->sa_data))
		वापस -EADDRNOTAVAIL;

	status = myri10ge_update_mac_address(mgp, sa->sa_data);
	अगर (status != 0) अणु
		netdev_err(dev, "changing mac address failed with %d\n",
			   status);
		वापस status;
	पूर्ण

	/* change the dev काष्ठाure */
	स_नकल(dev->dev_addr, sa->sa_data, ETH_ALEN);
	वापस 0;
पूर्ण

अटल पूर्णांक myri10ge_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा myri10ge_priv *mgp = netdev_priv(dev);

	netdev_info(dev, "changing mtu from %d to %d\n", dev->mtu, new_mtu);
	अगर (mgp->running) अणु
		/* अगर we change the mtu on an active device, we must
		 * reset the device so the firmware sees the change */
		myri10ge_बंद(dev);
		dev->mtu = new_mtu;
		myri10ge_खोलो(dev);
	पूर्ण अन्यथा
		dev->mtu = new_mtu;

	वापस 0;
पूर्ण

/*
 * Enable ECRC to align PCI-E Completion packets on an 8-byte boundary.
 * Only करो it अगर the bridge is a root port since we करोn't want to disturb
 * any other device, except अगर क्रमced with myri10ge_ecrc_enable > 1.
 */

अटल व्योम myri10ge_enable_ecrc(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा pci_dev *bridge = mgp->pdev->bus->self;
	काष्ठा device *dev = &mgp->pdev->dev;
	पूर्णांक cap;
	अचिन्हित err_cap;
	पूर्णांक ret;

	अगर (!myri10ge_ecrc_enable || !bridge)
		वापस;

	/* check that the bridge is a root port */
	अगर (pci_pcie_type(bridge) != PCI_EXP_TYPE_ROOT_PORT) अणु
		अगर (myri10ge_ecrc_enable > 1) अणु
			काष्ठा pci_dev *prev_bridge, *old_bridge = bridge;

			/* Walk the hierarchy up to the root port
			 * where ECRC has to be enabled */
			करो अणु
				prev_bridge = bridge;
				bridge = bridge->bus->self;
				अगर (!bridge || prev_bridge == bridge) अणु
					dev_err(dev,
						"Failed to find root port"
						" to force ECRC\n");
					वापस;
				पूर्ण
			पूर्ण जबतक (pci_pcie_type(bridge) !=
				 PCI_EXP_TYPE_ROOT_PORT);

			dev_info(dev,
				 "Forcing ECRC on non-root port %s"
				 " (enabling on root port %s)\n",
				 pci_name(old_bridge), pci_name(bridge));
		पूर्ण अन्यथा अणु
			dev_err(dev,
				"Not enabling ECRC on non-root port %s\n",
				pci_name(bridge));
			वापस;
		पूर्ण
	पूर्ण

	cap = pci_find_ext_capability(bridge, PCI_EXT_CAP_ID_ERR);
	अगर (!cap)
		वापस;

	ret = pci_पढ़ो_config_dword(bridge, cap + PCI_ERR_CAP, &err_cap);
	अगर (ret) अणु
		dev_err(dev, "failed reading ext-conf-space of %s\n",
			pci_name(bridge));
		dev_err(dev, "\t pci=nommconf in use? "
			"or buggy/incomplete/absent ACPI MCFG attr?\n");
		वापस;
	पूर्ण
	अगर (!(err_cap & PCI_ERR_CAP_ECRC_GENC))
		वापस;

	err_cap |= PCI_ERR_CAP_ECRC_GENE;
	pci_ग_लिखो_config_dword(bridge, cap + PCI_ERR_CAP, err_cap);
	dev_info(dev, "Enabled ECRC on upstream bridge %s\n", pci_name(bridge));
पूर्ण

/*
 * The Lanai Z8E PCI-E पूर्णांकerface achieves higher Read-DMA throughput
 * when the PCI-E Completion packets are aligned on an 8-byte
 * boundary.  Some PCI-E chip sets always align Completion packets; on
 * the ones that करो not, the alignment can be enक्रमced by enabling
 * ECRC generation (अगर supported).
 *
 * When PCI-E Completion packets are not aligned, it is actually more
 * efficient to limit Read-DMA transactions to 2KB, rather than 4KB.
 *
 * If the driver can neither enable ECRC nor verअगरy that it has
 * alपढ़ोy been enabled, then it must use a firmware image which works
 * around unaligned completion packets (myri10ge_rss_ethp_z8e.dat), and it
 * should also ensure that it never gives the device a Read-DMA which is
 * larger than 2KB by setting the tx_boundary to 2KB.  If ECRC is
 * enabled, then the driver should use the aligned (myri10ge_rss_eth_z8e.dat)
 * firmware image, and set tx_boundary to 4KB.
 */

अटल व्योम myri10ge_firmware_probe(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा pci_dev *pdev = mgp->pdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक status;

	mgp->tx_boundary = 4096;
	/*
	 * Verअगरy the max पढ़ो request size was set to 4KB
	 * beक्रमe trying the test with 4KB.
	 */
	status = pcie_get_पढ़ोrq(pdev);
	अगर (status < 0) अणु
		dev_err(dev, "Couldn't read max read req size: %d\n", status);
		जाओ पात;
	पूर्ण
	अगर (status != 4096) अणु
		dev_warn(dev, "Max Read Request size != 4096 (%d)\n", status);
		mgp->tx_boundary = 2048;
	पूर्ण
	/*
	 * load the optimized firmware (which assumes aligned PCIe
	 * completions) in order to see अगर it works on this host.
	 */
	set_fw_name(mgp, myri10ge_fw_aligned, false);
	status = myri10ge_load_firmware(mgp, 1);
	अगर (status != 0) अणु
		जाओ पात;
	पूर्ण

	/*
	 * Enable ECRC अगर possible
	 */
	myri10ge_enable_ecrc(mgp);

	/*
	 * Run a DMA test which watches क्रम unaligned completions and
	 * पातs on the first one seen.
	 */

	status = myri10ge_dma_test(mgp, MXGEFW_CMD_UNALIGNED_TEST);
	अगर (status == 0)
		वापस;		/* keep the aligned firmware */

	अगर (status != -E2BIG)
		dev_warn(dev, "DMA test failed: %d\n", status);
	अगर (status == -ENOSYS)
		dev_warn(dev, "Falling back to ethp! "
			 "Please install up to date fw\n");
पात:
	/* fall back to using the unaligned firmware */
	mgp->tx_boundary = 2048;
	set_fw_name(mgp, myri10ge_fw_unaligned, false);
पूर्ण

अटल व्योम myri10ge_select_firmware(काष्ठा myri10ge_priv *mgp)
अणु
	पूर्णांक overridden = 0;

	अगर (myri10ge_क्रमce_firmware == 0) अणु
		पूर्णांक link_width;
		u16 lnk;

		pcie_capability_पढ़ो_word(mgp->pdev, PCI_EXP_LNKSTA, &lnk);
		link_width = (lnk >> 4) & 0x3f;

		/* Check to see अगर Link is less than 8 or अगर the
		 * upstream bridge is known to provide aligned
		 * completions */
		अगर (link_width < 8) अणु
			dev_info(&mgp->pdev->dev, "PCIE x%d Link\n",
				 link_width);
			mgp->tx_boundary = 4096;
			set_fw_name(mgp, myri10ge_fw_aligned, false);
		पूर्ण अन्यथा अणु
			myri10ge_firmware_probe(mgp);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (myri10ge_क्रमce_firmware == 1) अणु
			dev_info(&mgp->pdev->dev,
				 "Assuming aligned completions (forced)\n");
			mgp->tx_boundary = 4096;
			set_fw_name(mgp, myri10ge_fw_aligned, false);
		पूर्ण अन्यथा अणु
			dev_info(&mgp->pdev->dev,
				 "Assuming unaligned completions (forced)\n");
			mgp->tx_boundary = 2048;
			set_fw_name(mgp, myri10ge_fw_unaligned, false);
		पूर्ण
	पूर्ण

	kernel_param_lock(THIS_MODULE);
	अगर (myri10ge_fw_name != शून्य) अणु
		अक्षर *fw_name = kstrdup(myri10ge_fw_name, GFP_KERNEL);
		अगर (fw_name) अणु
			overridden = 1;
			set_fw_name(mgp, fw_name, true);
		पूर्ण
	पूर्ण
	kernel_param_unlock(THIS_MODULE);

	अगर (mgp->board_number < MYRI10GE_MAX_BOARDS &&
	    myri10ge_fw_names[mgp->board_number] != शून्य &&
	    म_माप(myri10ge_fw_names[mgp->board_number])) अणु
		set_fw_name(mgp, myri10ge_fw_names[mgp->board_number], false);
		overridden = 1;
	पूर्ण
	अगर (overridden)
		dev_info(&mgp->pdev->dev, "overriding firmware to %s\n",
			 mgp->fw_name);
पूर्ण

अटल व्योम myri10ge_mask_surprise_करोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *bridge = pdev->bus->self;
	पूर्णांक cap;
	u32 mask;

	अगर (bridge == शून्य)
		वापस;

	cap = pci_find_ext_capability(bridge, PCI_EXT_CAP_ID_ERR);
	अगर (cap) अणु
		/* a sram parity error can cause a surprise link
		 * करोwn; since we expect and can recover from sram
		 * parity errors, mask surprise link करोwn events */
		pci_पढ़ो_config_dword(bridge, cap + PCI_ERR_UNCOR_MASK, &mask);
		mask |= 0x20;
		pci_ग_लिखो_config_dword(bridge, cap + PCI_ERR_UNCOR_MASK, mask);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused myri10ge_suspend(काष्ठा device *dev)
अणु
	काष्ठा myri10ge_priv *mgp;
	काष्ठा net_device *netdev;

	mgp = dev_get_drvdata(dev);
	अगर (mgp == शून्य)
		वापस -EINVAL;
	netdev = mgp->dev;

	netअगर_device_detach(netdev);
	अगर (netअगर_running(netdev)) अणु
		netdev_info(netdev, "closing\n");
		rtnl_lock();
		myri10ge_बंद(netdev);
		rtnl_unlock();
	पूर्ण
	myri10ge_dummy_rdma(mgp, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused myri10ge_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा myri10ge_priv *mgp;
	काष्ठा net_device *netdev;
	पूर्णांक status;
	u16 venकरोr;

	mgp = pci_get_drvdata(pdev);
	अगर (mgp == शून्य)
		वापस -EINVAL;
	netdev = mgp->dev;
	msleep(5);		/* give card समय to respond */
	pci_पढ़ो_config_word(mgp->pdev, PCI_VENDOR_ID, &venकरोr);
	अगर (venकरोr == 0xffff) अणु
		netdev_err(mgp->dev, "device disappeared!\n");
		वापस -EIO;
	पूर्ण

	myri10ge_reset(mgp);
	myri10ge_dummy_rdma(mgp, 1);

	अगर (netअगर_running(netdev)) अणु
		rtnl_lock();
		status = myri10ge_खोलो(netdev);
		rtnl_unlock();
		अगर (status != 0)
			जाओ पात_with_enabled;

	पूर्ण
	netअगर_device_attach(netdev);

	वापस 0;

पात_with_enabled:
	वापस -EIO;
पूर्ण

अटल u32 myri10ge_पढ़ो_reboot(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा pci_dev *pdev = mgp->pdev;
	पूर्णांक vs = mgp->venकरोr_specअगरic_offset;
	u32 reboot;

	/*enter पढ़ो32 mode */
	pci_ग_लिखो_config_byte(pdev, vs + 0x10, 0x3);

	/*पढ़ो REBOOT_STATUS (0xfffffff0) */
	pci_ग_लिखो_config_dword(pdev, vs + 0x18, 0xfffffff0);
	pci_पढ़ो_config_dword(pdev, vs + 0x14, &reboot);
	वापस reboot;
पूर्ण

अटल व्योम
myri10ge_check_slice(काष्ठा myri10ge_slice_state *ss, पूर्णांक *reset_needed,
		     पूर्णांक *busy_slice_cnt, u32 rx_छोड़ो_cnt)
अणु
	काष्ठा myri10ge_priv *mgp = ss->mgp;
	पूर्णांक slice = ss - mgp->ss;

	अगर (ss->tx.req != ss->tx.करोne &&
	    ss->tx.करोne == ss->watchकरोg_tx_करोne &&
	    ss->watchकरोg_tx_req != ss->watchकरोg_tx_करोne) अणु
		/* nic seems like it might be stuck.. */
		अगर (rx_छोड़ो_cnt != mgp->watchकरोg_छोड़ो) अणु
			अगर (net_ratelimit())
				netdev_warn(mgp->dev, "slice %d: TX paused, "
					    "check link partner\n", slice);
		पूर्ण अन्यथा अणु
			netdev_warn(mgp->dev,
				    "slice %d: TX stuck %d %d %d %d %d %d\n",
				    slice, ss->tx.queue_active, ss->tx.req,
				    ss->tx.करोne, ss->tx.pkt_start,
				    ss->tx.pkt_करोne,
				    (पूर्णांक)ntohl(mgp->ss[slice].fw_stats->
					       send_करोne_count));
			*reset_needed = 1;
			ss->stuck = 1;
		पूर्ण
	पूर्ण
	अगर (ss->watchकरोg_tx_करोne != ss->tx.करोne ||
	    ss->watchकरोg_rx_करोne != ss->rx_करोne.cnt) अणु
		*busy_slice_cnt += 1;
	पूर्ण
	ss->watchकरोg_tx_करोne = ss->tx.करोne;
	ss->watchकरोg_tx_req = ss->tx.req;
	ss->watchकरोg_rx_करोne = ss->rx_करोne.cnt;
पूर्ण

/*
 * This watchकरोg is used to check whether the board has suffered
 * from a parity error and needs to be recovered.
 */
अटल व्योम myri10ge_watchकरोg(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा myri10ge_priv *mgp =
	    container_of(work, काष्ठा myri10ge_priv, watchकरोg_work);
	काष्ठा myri10ge_slice_state *ss;
	u32 reboot, rx_छोड़ो_cnt;
	पूर्णांक status, rebooted;
	पूर्णांक i;
	पूर्णांक reset_needed = 0;
	पूर्णांक busy_slice_cnt = 0;
	u16 cmd, venकरोr;

	mgp->watchकरोg_resets++;
	pci_पढ़ो_config_word(mgp->pdev, PCI_COMMAND, &cmd);
	rebooted = 0;
	अगर ((cmd & PCI_COMMAND_MASTER) == 0) अणु
		/* Bus master DMA disabled?  Check to see
		 * अगर the card rebooted due to a parity error
		 * For now, just report it */
		reboot = myri10ge_पढ़ो_reboot(mgp);
		netdev_err(mgp->dev, "NIC rebooted (0x%x),%s resetting\n",
			   reboot, myri10ge_reset_recover ? "" : " not");
		अगर (myri10ge_reset_recover == 0)
			वापस;
		rtnl_lock();
		mgp->rebooted = 1;
		rebooted = 1;
		myri10ge_बंद(mgp->dev);
		myri10ge_reset_recover--;
		mgp->rebooted = 0;
		/*
		 * A rebooted nic will come back with config space as
		 * it was after घातer was applied to PCIe bus.
		 * Attempt to restore config space which was saved
		 * when the driver was loaded, or the last समय the
		 * nic was resumed from घातer saving mode.
		 */
		pci_restore_state(mgp->pdev);

		/* save state again क्रम accounting reasons */
		pci_save_state(mgp->pdev);

	पूर्ण अन्यथा अणु
		/* अगर we get back -1's from our slot, perhaps somebody
		 * घातered off our card.  Don't try to reset it in
		 * this हाल */
		अगर (cmd == 0xffff) अणु
			pci_पढ़ो_config_word(mgp->pdev, PCI_VENDOR_ID, &venकरोr);
			अगर (venकरोr == 0xffff) अणु
				netdev_err(mgp->dev, "device disappeared!\n");
				वापस;
			पूर्ण
		पूर्ण
		/* Perhaps it is a software error. See अगर stuck slice
		 * has recovered, reset अगर not */
		rx_छोड़ो_cnt = ntohl(mgp->ss[0].fw_stats->dropped_छोड़ो);
		क्रम (i = 0; i < mgp->num_slices; i++) अणु
			ss = mgp->ss;
			अगर (ss->stuck) अणु
				myri10ge_check_slice(ss, &reset_needed,
						     &busy_slice_cnt,
						     rx_छोड़ो_cnt);
				ss->stuck = 0;
			पूर्ण
		पूर्ण
		अगर (!reset_needed) अणु
			netdev_dbg(mgp->dev, "not resetting\n");
			वापस;
		पूर्ण

		netdev_err(mgp->dev, "device timeout, resetting\n");
	पूर्ण

	अगर (!rebooted) अणु
		rtnl_lock();
		myri10ge_बंद(mgp->dev);
	पूर्ण
	status = myri10ge_load_firmware(mgp, 1);
	अगर (status != 0)
		netdev_err(mgp->dev, "failed to load firmware\n");
	अन्यथा
		myri10ge_खोलो(mgp->dev);
	rtnl_unlock();
पूर्ण

/*
 * We use our own समयr routine rather than relying upon
 * netdev->tx_समयout because we have a very large hardware transmit
 * queue.  Due to the large queue, the netdev->tx_समयout function
 * cannot detect a NIC with a parity error in a समयly fashion अगर the
 * NIC is lightly loaded.
 */
अटल व्योम myri10ge_watchकरोg_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा myri10ge_priv *mgp;
	काष्ठा myri10ge_slice_state *ss;
	पूर्णांक i, reset_needed, busy_slice_cnt;
	u32 rx_छोड़ो_cnt;
	u16 cmd;

	mgp = from_समयr(mgp, t, watchकरोg_समयr);

	rx_छोड़ो_cnt = ntohl(mgp->ss[0].fw_stats->dropped_छोड़ो);
	busy_slice_cnt = 0;
	क्रम (i = 0, reset_needed = 0;
	     i < mgp->num_slices && reset_needed == 0; ++i) अणु

		ss = &mgp->ss[i];
		अगर (ss->rx_small.watchकरोg_needed) अणु
			myri10ge_alloc_rx_pages(mgp, &ss->rx_small,
						mgp->small_bytes + MXGEFW_PAD,
						1);
			अगर (ss->rx_small.fill_cnt - ss->rx_small.cnt >=
			    myri10ge_fill_thresh)
				ss->rx_small.watchकरोg_needed = 0;
		पूर्ण
		अगर (ss->rx_big.watchकरोg_needed) अणु
			myri10ge_alloc_rx_pages(mgp, &ss->rx_big,
						mgp->big_bytes, 1);
			अगर (ss->rx_big.fill_cnt - ss->rx_big.cnt >=
			    myri10ge_fill_thresh)
				ss->rx_big.watchकरोg_needed = 0;
		पूर्ण
		myri10ge_check_slice(ss, &reset_needed, &busy_slice_cnt,
				     rx_छोड़ो_cnt);
	पूर्ण
	/* अगर we've sent or received no traffic, poll the NIC to
	 * ensure it is still there.  Otherwise, we risk not noticing
	 * an error in a समयly fashion */
	अगर (busy_slice_cnt == 0) अणु
		pci_पढ़ो_config_word(mgp->pdev, PCI_COMMAND, &cmd);
		अगर ((cmd & PCI_COMMAND_MASTER) == 0) अणु
			reset_needed = 1;
		पूर्ण
	पूर्ण
	mgp->watchकरोg_छोड़ो = rx_छोड़ो_cnt;

	अगर (reset_needed) अणु
		schedule_work(&mgp->watchकरोg_work);
	पूर्ण अन्यथा अणु
		/* rearm समयr */
		mod_समयr(&mgp->watchकरोg_समयr,
			  jअगरfies + myri10ge_watchकरोg_समयout * HZ);
	पूर्ण
पूर्ण

अटल व्योम myri10ge_मुक्त_slices(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा myri10ge_slice_state *ss;
	काष्ठा pci_dev *pdev = mgp->pdev;
	माप_प्रकार bytes;
	पूर्णांक i;

	अगर (mgp->ss == शून्य)
		वापस;

	क्रम (i = 0; i < mgp->num_slices; i++) अणु
		ss = &mgp->ss[i];
		अगर (ss->rx_करोne.entry != शून्य) अणु
			bytes = mgp->max_पूर्णांकr_slots *
			    माप(*ss->rx_करोne.entry);
			dma_मुक्त_coherent(&pdev->dev, bytes,
					  ss->rx_करोne.entry, ss->rx_करोne.bus);
			ss->rx_करोne.entry = शून्य;
		पूर्ण
		अगर (ss->fw_stats != शून्य) अणु
			bytes = माप(*ss->fw_stats);
			dma_मुक्त_coherent(&pdev->dev, bytes,
					  ss->fw_stats, ss->fw_stats_bus);
			ss->fw_stats = शून्य;
		पूर्ण
		__netअगर_napi_del(&ss->napi);
	पूर्ण
	/* Wait till napi काष्ठाs are no दीर्घer used, and then मुक्त ss. */
	synchronize_net();
	kमुक्त(mgp->ss);
	mgp->ss = शून्य;
पूर्ण

अटल पूर्णांक myri10ge_alloc_slices(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा myri10ge_slice_state *ss;
	काष्ठा pci_dev *pdev = mgp->pdev;
	माप_प्रकार bytes;
	पूर्णांक i;

	bytes = माप(*mgp->ss) * mgp->num_slices;
	mgp->ss = kzalloc(bytes, GFP_KERNEL);
	अगर (mgp->ss == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < mgp->num_slices; i++) अणु
		ss = &mgp->ss[i];
		bytes = mgp->max_पूर्णांकr_slots * माप(*ss->rx_करोne.entry);
		ss->rx_करोne.entry = dma_alloc_coherent(&pdev->dev, bytes,
						       &ss->rx_करोne.bus,
						       GFP_KERNEL);
		अगर (ss->rx_करोne.entry == शून्य)
			जाओ पात;
		bytes = माप(*ss->fw_stats);
		ss->fw_stats = dma_alloc_coherent(&pdev->dev, bytes,
						  &ss->fw_stats_bus,
						  GFP_KERNEL);
		अगर (ss->fw_stats == शून्य)
			जाओ पात;
		ss->mgp = mgp;
		ss->dev = mgp->dev;
		netअगर_napi_add(ss->dev, &ss->napi, myri10ge_poll,
			       myri10ge_napi_weight);
	पूर्ण
	वापस 0;
पात:
	myri10ge_मुक्त_slices(mgp);
	वापस -ENOMEM;
पूर्ण

/*
 * This function determines the number of slices supported.
 * The number slices is the minimum of the number of CPUS,
 * the number of MSI-X irqs supported, the number of slices
 * supported by the firmware
 */
अटल व्योम myri10ge_probe_slices(काष्ठा myri10ge_priv *mgp)
अणु
	काष्ठा myri10ge_cmd cmd;
	काष्ठा pci_dev *pdev = mgp->pdev;
	अक्षर *old_fw;
	bool old_allocated;
	पूर्णांक i, status, ncpus;

	mgp->num_slices = 1;
	ncpus = netअगर_get_num_शेष_rss_queues();

	अगर (myri10ge_max_slices == 1 || !pdev->msix_cap ||
	    (myri10ge_max_slices == -1 && ncpus < 2))
		वापस;

	/* try to load the slice aware rss firmware */
	old_fw = mgp->fw_name;
	old_allocated = mgp->fw_name_allocated;
	/* करोn't मुक्त old_fw अगर we override it. */
	mgp->fw_name_allocated = false;

	अगर (myri10ge_fw_name != शून्य) अणु
		dev_info(&mgp->pdev->dev, "overriding rss firmware to %s\n",
			 myri10ge_fw_name);
		set_fw_name(mgp, myri10ge_fw_name, false);
	पूर्ण अन्यथा अगर (old_fw == myri10ge_fw_aligned)
		set_fw_name(mgp, myri10ge_fw_rss_aligned, false);
	अन्यथा
		set_fw_name(mgp, myri10ge_fw_rss_unaligned, false);
	status = myri10ge_load_firmware(mgp, 0);
	अगर (status != 0) अणु
		dev_info(&pdev->dev, "Rss firmware not found\n");
		अगर (old_allocated)
			kमुक्त(old_fw);
		वापस;
	पूर्ण

	/* hit the board with a reset to ensure it is alive */
	स_रखो(&cmd, 0, माप(cmd));
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_RESET, &cmd, 0);
	अगर (status != 0) अणु
		dev_err(&mgp->pdev->dev, "failed reset\n");
		जाओ पात_with_fw;
	पूर्ण

	mgp->max_पूर्णांकr_slots = cmd.data0 / माप(काष्ठा mcp_slot);

	/* tell it the size of the पूर्णांकerrupt queues */
	cmd.data0 = mgp->max_पूर्णांकr_slots * माप(काष्ठा mcp_slot);
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_INTRQ_SIZE, &cmd, 0);
	अगर (status != 0) अणु
		dev_err(&mgp->pdev->dev, "failed MXGEFW_CMD_SET_INTRQ_SIZE\n");
		जाओ पात_with_fw;
	पूर्ण

	/* ask the maximum number of slices it supports */
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_MAX_RSS_QUEUES, &cmd, 0);
	अगर (status != 0)
		जाओ पात_with_fw;
	अन्यथा
		mgp->num_slices = cmd.data0;

	/* Only allow multiple slices अगर MSI-X is usable */
	अगर (!myri10ge_msi) अणु
		जाओ पात_with_fw;
	पूर्ण

	/* अगर the admin did not specअगरy a limit to how many
	 * slices we should use, cap it स्वतःmatically to the
	 * number of CPUs currently online */
	अगर (myri10ge_max_slices == -1)
		myri10ge_max_slices = ncpus;

	अगर (mgp->num_slices > myri10ge_max_slices)
		mgp->num_slices = myri10ge_max_slices;

	/* Now try to allocate as many MSI-X vectors as we have
	 * slices. We give up on MSI-X अगर we can only get a single
	 * vector. */

	mgp->msix_vectors = kसुस्मृति(mgp->num_slices, माप(*mgp->msix_vectors),
				    GFP_KERNEL);
	अगर (mgp->msix_vectors == शून्य)
		जाओ no_msix;
	क्रम (i = 0; i < mgp->num_slices; i++) अणु
		mgp->msix_vectors[i].entry = i;
	पूर्ण

	जबतक (mgp->num_slices > 1) अणु
		mgp->num_slices = roundकरोwn_घात_of_two(mgp->num_slices);
		अगर (mgp->num_slices == 1)
			जाओ no_msix;
		status = pci_enable_msix_range(pdev,
					       mgp->msix_vectors,
					       mgp->num_slices,
					       mgp->num_slices);
		अगर (status < 0)
			जाओ no_msix;

		pci_disable_msix(pdev);

		अगर (status == mgp->num_slices) अणु
			अगर (old_allocated)
				kमुक्त(old_fw);
			वापस;
		पूर्ण अन्यथा अणु
			mgp->num_slices = status;
		पूर्ण
	पूर्ण

no_msix:
	अगर (mgp->msix_vectors != शून्य) अणु
		kमुक्त(mgp->msix_vectors);
		mgp->msix_vectors = शून्य;
	पूर्ण

पात_with_fw:
	mgp->num_slices = 1;
	set_fw_name(mgp, old_fw, old_allocated);
	myri10ge_load_firmware(mgp, 0);
पूर्ण

अटल स्थिर काष्ठा net_device_ops myri10ge_netdev_ops = अणु
	.nकरो_खोलो		= myri10ge_खोलो,
	.nकरो_stop		= myri10ge_बंद,
	.nकरो_start_xmit		= myri10ge_xmit,
	.nकरो_get_stats64	= myri10ge_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_mtu		= myri10ge_change_mtu,
	.nकरो_set_rx_mode	= myri10ge_set_multicast_list,
	.nकरो_set_mac_address	= myri10ge_set_mac_address,
पूर्ण;

अटल पूर्णांक myri10ge_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा myri10ge_priv *mgp;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i;
	पूर्णांक status = -ENXIO;
	पूर्णांक dac_enabled;
	अचिन्हित hdr_offset, ss_offset;
	अटल पूर्णांक board_number;

	netdev = alloc_etherdev_mq(माप(*mgp), MYRI10GE_MAX_SLICES);
	अगर (netdev == शून्य)
		वापस -ENOMEM;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	mgp = netdev_priv(netdev);
	mgp->dev = netdev;
	mgp->pdev = pdev;
	mgp->छोड़ो = myri10ge_flow_control;
	mgp->पूर्णांकr_coal_delay = myri10ge_पूर्णांकr_coal_delay;
	mgp->msg_enable = netअगर_msg_init(myri10ge_debug, MYRI10GE_MSG_DEFAULT);
	mgp->board_number = board_number;
	init_रुकोqueue_head(&mgp->करोwn_wq);

	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev, "pci_enable_device call failed\n");
		status = -ENODEV;
		जाओ पात_with_netdev;
	पूर्ण

	/* Find the venकरोr-specअगरic cap so we can check
	 * the reboot रेजिस्टर later on */
	mgp->venकरोr_specअगरic_offset
	    = pci_find_capability(pdev, PCI_CAP_ID_VNDR);

	/* Set our max पढ़ो request to 4KB */
	status = pcie_set_पढ़ोrq(pdev, 4096);
	अगर (status != 0) अणु
		dev_err(&pdev->dev, "Error %d writing PCI_EXP_DEVCTL\n",
			status);
		जाओ पात_with_enabled;
	पूर्ण

	myri10ge_mask_surprise_करोwn(pdev);
	pci_set_master(pdev);
	dac_enabled = 1;
	status = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (status != 0) अणु
		dac_enabled = 0;
		dev_err(&pdev->dev,
			"64-bit pci address mask was refused, "
			"trying 32-bit\n");
		status = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	पूर्ण
	अगर (status != 0) अणु
		dev_err(&pdev->dev, "Error %d setting DMA mask\n", status);
		जाओ पात_with_enabled;
	पूर्ण
	(व्योम)pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	mgp->cmd = dma_alloc_coherent(&pdev->dev, माप(*mgp->cmd),
				      &mgp->cmd_bus, GFP_KERNEL);
	अगर (!mgp->cmd) अणु
		status = -ENOMEM;
		जाओ पात_with_enabled;
	पूर्ण

	mgp->board_span = pci_resource_len(pdev, 0);
	mgp->iomem_base = pci_resource_start(pdev, 0);
	mgp->wc_cookie = arch_phys_wc_add(mgp->iomem_base, mgp->board_span);
	mgp->sram = ioremap_wc(mgp->iomem_base, mgp->board_span);
	अगर (mgp->sram == शून्य) अणु
		dev_err(&pdev->dev, "ioremap failed for %ld bytes at 0x%lx\n",
			mgp->board_span, mgp->iomem_base);
		status = -ENXIO;
		जाओ पात_with_mtrr;
	पूर्ण
	hdr_offset =
	    swab32(पढ़ोl(mgp->sram + MCP_HEADER_PTR_OFFSET)) & 0xffffc;
	ss_offset = hdr_offset + दुरत्व(काष्ठा mcp_gen_header, string_specs);
	mgp->sram_size = swab32(पढ़ोl(mgp->sram + ss_offset));
	अगर (mgp->sram_size > mgp->board_span ||
	    mgp->sram_size <= MYRI10GE_FW_OFFSET) अणु
		dev_err(&pdev->dev,
			"invalid sram_size %dB or board span %ldB\n",
			mgp->sram_size, mgp->board_span);
		status = -EINVAL;
		जाओ पात_with_ioremap;
	पूर्ण
	स_नकल_fromio(mgp->eeprom_strings,
		      mgp->sram + mgp->sram_size, MYRI10GE_EEPROM_STRINGS_SIZE);
	स_रखो(mgp->eeprom_strings + MYRI10GE_EEPROM_STRINGS_SIZE - 2, 0, 2);
	status = myri10ge_पढ़ो_mac_addr(mgp);
	अगर (status)
		जाओ पात_with_ioremap;

	क्रम (i = 0; i < ETH_ALEN; i++)
		netdev->dev_addr[i] = mgp->mac_addr[i];

	myri10ge_select_firmware(mgp);

	status = myri10ge_load_firmware(mgp, 1);
	अगर (status != 0) अणु
		dev_err(&pdev->dev, "failed to load firmware\n");
		जाओ पात_with_ioremap;
	पूर्ण
	myri10ge_probe_slices(mgp);
	status = myri10ge_alloc_slices(mgp);
	अगर (status != 0) अणु
		dev_err(&pdev->dev, "failed to alloc slice state\n");
		जाओ पात_with_firmware;
	पूर्ण
	netअगर_set_real_num_tx_queues(netdev, mgp->num_slices);
	netअगर_set_real_num_rx_queues(netdev, mgp->num_slices);
	status = myri10ge_reset(mgp);
	अगर (status != 0) अणु
		dev_err(&pdev->dev, "failed reset\n");
		जाओ पात_with_slices;
	पूर्ण
#अगर_घोषित CONFIG_MYRI10GE_DCA
	myri10ge_setup_dca(mgp);
#पूर्ण_अगर
	pci_set_drvdata(pdev, mgp);

	/* MTU range: 68 - 9000 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = MYRI10GE_MAX_ETHER_MTU - ETH_HLEN;

	अगर (myri10ge_initial_mtu > netdev->max_mtu)
		myri10ge_initial_mtu = netdev->max_mtu;
	अगर (myri10ge_initial_mtu < netdev->min_mtu)
		myri10ge_initial_mtu = netdev->min_mtu;

	netdev->mtu = myri10ge_initial_mtu;

	netdev->netdev_ops = &myri10ge_netdev_ops;
	netdev->hw_features = mgp->features | NETIF_F_RXCSUM;

	/* fake NETIF_F_HW_VLAN_CTAG_RX क्रम good GRO perक्रमmance */
	netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_RX;

	netdev->features = netdev->hw_features;

	अगर (dac_enabled)
		netdev->features |= NETIF_F_HIGHDMA;

	netdev->vlan_features |= mgp->features;
	अगर (mgp->fw_ver_tiny < 37)
		netdev->vlan_features &= ~NETIF_F_TSO6;
	अगर (mgp->fw_ver_tiny < 32)
		netdev->vlan_features &= ~NETIF_F_TSO;

	/* make sure we can get an irq, and that MSI can be
	 * setup (अगर available). */
	status = myri10ge_request_irq(mgp);
	अगर (status != 0)
		जाओ पात_with_slices;
	myri10ge_मुक्त_irq(mgp);

	/* Save configuration space to be restored अगर the
	 * nic resets due to a parity error */
	pci_save_state(pdev);

	/* Setup the watchकरोg समयr */
	समयr_setup(&mgp->watchकरोg_समयr, myri10ge_watchकरोg_समयr, 0);

	netdev->ethtool_ops = &myri10ge_ethtool_ops;
	INIT_WORK(&mgp->watchकरोg_work, myri10ge_watchकरोg);
	status = रेजिस्टर_netdev(netdev);
	अगर (status != 0) अणु
		dev_err(&pdev->dev, "register_netdev failed: %d\n", status);
		जाओ पात_with_state;
	पूर्ण
	अगर (mgp->msix_enabled)
		dev_info(dev, "%d MSI-X IRQs, tx bndry %d, fw %s, MTRR %s, WC Enabled\n",
			 mgp->num_slices, mgp->tx_boundary, mgp->fw_name,
			 (mgp->wc_cookie > 0 ? "Enabled" : "Disabled"));
	अन्यथा
		dev_info(dev, "%s IRQ %d, tx bndry %d, fw %s, MTRR %s, WC Enabled\n",
			 mgp->msi_enabled ? "MSI" : "xPIC",
			 pdev->irq, mgp->tx_boundary, mgp->fw_name,
			 (mgp->wc_cookie > 0 ? "Enabled" : "Disabled"));

	board_number++;
	वापस 0;

पात_with_state:
	pci_restore_state(pdev);

पात_with_slices:
	myri10ge_मुक्त_slices(mgp);

पात_with_firmware:
	myri10ge_dummy_rdma(mgp, 0);

पात_with_ioremap:
	अगर (mgp->mac_addr_string != शून्य)
		dev_err(&pdev->dev,
			"myri10ge_probe() failed: MAC=%s, SN=%ld\n",
			mgp->mac_addr_string, mgp->serial_number);
	iounmap(mgp->sram);

पात_with_mtrr:
	arch_phys_wc_del(mgp->wc_cookie);
	dma_मुक्त_coherent(&pdev->dev, माप(*mgp->cmd),
			  mgp->cmd, mgp->cmd_bus);

पात_with_enabled:
	pci_disable_device(pdev);

पात_with_netdev:
	set_fw_name(mgp, शून्य, false);
	मुक्त_netdev(netdev);
	वापस status;
पूर्ण

/*
 * myri10ge_हटाओ
 *
 * Does what is necessary to shutकरोwn one Myrinet device. Called
 *   once क्रम each Myrinet card by the kernel when a module is
 *   unloaded.
 */
अटल व्योम myri10ge_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा myri10ge_priv *mgp;
	काष्ठा net_device *netdev;

	mgp = pci_get_drvdata(pdev);
	अगर (mgp == शून्य)
		वापस;

	cancel_work_sync(&mgp->watchकरोg_work);
	netdev = mgp->dev;
	unरेजिस्टर_netdev(netdev);

#अगर_घोषित CONFIG_MYRI10GE_DCA
	myri10ge_tearकरोwn_dca(mgp);
#पूर्ण_अगर
	myri10ge_dummy_rdma(mgp, 0);

	/* aव्योम a memory leak */
	pci_restore_state(pdev);

	iounmap(mgp->sram);
	arch_phys_wc_del(mgp->wc_cookie);
	myri10ge_मुक्त_slices(mgp);
	kमुक्त(mgp->msix_vectors);
	dma_मुक्त_coherent(&pdev->dev, माप(*mgp->cmd),
			  mgp->cmd, mgp->cmd_bus);

	set_fw_name(mgp, शून्य, false);
	मुक्त_netdev(netdev);
	pci_disable_device(pdev);
पूर्ण

#घोषणा PCI_DEVICE_ID_MYRICOM_MYRI10GE_Z8E 	0x0008
#घोषणा PCI_DEVICE_ID_MYRICOM_MYRI10GE_Z8E_9	0x0009

अटल स्थिर काष्ठा pci_device_id myri10ge_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_MYRICOM, PCI_DEVICE_ID_MYRICOM_MYRI10GE_Z8E)पूर्ण,
	अणुPCI_DEVICE
	 (PCI_VENDOR_ID_MYRICOM, PCI_DEVICE_ID_MYRICOM_MYRI10GE_Z8E_9)पूर्ण,
	अणु0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, myri10ge_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(myri10ge_pm_ops, myri10ge_suspend, myri10ge_resume);

अटल काष्ठा pci_driver myri10ge_driver = अणु
	.name = "myri10ge",
	.probe = myri10ge_probe,
	.हटाओ = myri10ge_हटाओ,
	.id_table = myri10ge_pci_tbl,
	.driver.pm = &myri10ge_pm_ops,
पूर्ण;

#अगर_घोषित CONFIG_MYRI10GE_DCA
अटल पूर्णांक
myri10ge_notअगरy_dca(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *p)
अणु
	पूर्णांक err = driver_क्रम_each_device(&myri10ge_driver.driver,
					 शून्य, &event,
					 myri10ge_notअगरy_dca_device);

	अगर (err)
		वापस NOTIFY_BAD;
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block myri10ge_dca_notअगरier = अणु
	.notअगरier_call = myri10ge_notअगरy_dca,
	.next = शून्य,
	.priority = 0,
पूर्ण;
#पूर्ण_अगर				/* CONFIG_MYRI10GE_DCA */

अटल __init पूर्णांक myri10ge_init_module(व्योम)
अणु
	pr_info("Version %s\n", MYRI10GE_VERSION_STR);

	अगर (myri10ge_rss_hash > MXGEFW_RSS_HASH_TYPE_MAX) अणु
		pr_err("Illegal rssh hash type %d, defaulting to source port\n",
		       myri10ge_rss_hash);
		myri10ge_rss_hash = MXGEFW_RSS_HASH_TYPE_SRC_PORT;
	पूर्ण
#अगर_घोषित CONFIG_MYRI10GE_DCA
	dca_रेजिस्टर_notअगरy(&myri10ge_dca_notअगरier);
#पूर्ण_अगर
	अगर (myri10ge_max_slices > MYRI10GE_MAX_SLICES)
		myri10ge_max_slices = MYRI10GE_MAX_SLICES;

	वापस pci_रेजिस्टर_driver(&myri10ge_driver);
पूर्ण

module_init(myri10ge_init_module);

अटल __निकास व्योम myri10ge_cleanup_module(व्योम)
अणु
#अगर_घोषित CONFIG_MYRI10GE_DCA
	dca_unरेजिस्टर_notअगरy(&myri10ge_dca_notअगरier);
#पूर्ण_अगर
	pci_unरेजिस्टर_driver(&myri10ge_driver);
पूर्ण

module_निकास(myri10ge_cleanup_module);
