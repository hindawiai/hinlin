<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
  Madge Ambassaकरोr ATM Adapter driver.
  Copyright (C) 1995-1999  Madge Networks Ltd.

*/

#अगर_अघोषित AMBASSADOR_H
#घोषणा AMBASSADOR_H


#अगर_घोषित CONFIG_ATM_AMBASSADOR_DEBUG
#घोषणा DEBUG_AMBASSADOR
#पूर्ण_अगर

#घोषणा DEV_LABEL                          "amb"

#अगर_अघोषित PCI_VENDOR_ID_MADGE
#घोषणा PCI_VENDOR_ID_MADGE                0x10B6
#पूर्ण_अगर
#अगर_अघोषित PCI_VENDOR_ID_MADGE_AMBASSADOR
#घोषणा PCI_DEVICE_ID_MADGE_AMBASSADOR     0x1001
#पूर्ण_अगर
#अगर_अघोषित PCI_VENDOR_ID_MADGE_AMBASSADOR_BAD
#घोषणा PCI_DEVICE_ID_MADGE_AMBASSADOR_BAD 0x1002
#पूर्ण_अगर

// diagnostic output

#घोषणा PRINTK(severity,क्रमmat,args...) \
  prपूर्णांकk(severity DEV_LABEL ": " क्रमmat "\n" , ## args)

#अगर_घोषित DEBUG_AMBASSADOR

#घोषणा DBG_ERR  0x0001
#घोषणा DBG_WARN 0x0002
#घोषणा DBG_INFO 0x0004
#घोषणा DBG_INIT 0x0008
#घोषणा DBG_LOAD 0x0010
#घोषणा DBG_VCC  0x0020
#घोषणा DBG_QOS  0x0040
#घोषणा DBG_CMD  0x0080
#घोषणा DBG_TX   0x0100
#घोषणा DBG_RX   0x0200
#घोषणा DBG_SKB  0x0400
#घोषणा DBG_POOL 0x0800
#घोषणा DBG_IRQ  0x1000
#घोषणा DBG_FLOW 0x2000
#घोषणा DBG_REGS 0x4000
#घोषणा DBG_DATA 0x8000
#घोषणा DBG_MASK 0xffff

/* the ## prevents the annoying द्विगुन expansion of the macro arguments */
/* KERN_INFO is used since KERN_DEBUG often करोes not make it to the console */
#घोषणा PRINTDB(bits,क्रमmat,args...) \
  ( (debug & (bits)) ? prपूर्णांकk (KERN_INFO DEV_LABEL ": " क्रमmat , ## args) : 1 )
#घोषणा PRINTDM(bits,क्रमmat,args...) \
  ( (debug & (bits)) ? prपूर्णांकk (क्रमmat , ## args) : 1 )
#घोषणा PRINTDE(bits,क्रमmat,args...) \
  ( (debug & (bits)) ? prपूर्णांकk (क्रमmat "\n" , ## args) : 1 )
#घोषणा PRINTD(bits,क्रमmat,args...) \
  ( (debug & (bits)) ? prपूर्णांकk (KERN_INFO DEV_LABEL ": " क्रमmat "\n" , ## args) : 1 )

#अन्यथा

#घोषणा PRINTD(bits,क्रमmat,args...)
#घोषणा PRINTDB(bits,क्रमmat,args...)
#घोषणा PRINTDM(bits,क्रमmat,args...)
#घोषणा PRINTDE(bits,क्रमmat,args...)

#पूर्ण_अगर

#घोषणा PRINTDD(bits,क्रमmat,args...)
#घोषणा PRINTDDB(sec,fmt,args...)
#घोषणा PRINTDDM(sec,fmt,args...)
#घोषणा PRINTDDE(sec,fmt,args...)

// tunable values (?)

/* MUST be घातers of two -- why ? */
#घोषणा COM_Q_ENTRIES        8
#घोषणा TX_Q_ENTRIES        32
#घोषणा RX_Q_ENTRIES        64

// fixed values

// guessing
#घोषणा AMB_EXTENT         0x80

// Minimum allowed size क्रम an Ambassaकरोr queue
#घोषणा MIN_QUEUE_SIZE     2

// Ambassaकरोr microcode allows 1 to 4 pools, we use 4 (simpler)
#घोषणा NUM_RX_POOLS	   4

// minimum RX buffers required to cope with replenishing delay
#घोषणा MIN_RX_BUFFERS	   1

// minimum PCI latency we will tolerate (32 IS TOO SMALL)
#घोषणा MIN_PCI_LATENCY   64 // 255

// VCs supported by card (VPI always 0)
#घोषणा NUM_VPI_BITS       0
#घोषणा NUM_VCI_BITS      10
#घोषणा NUM_VCS         1024

/* The status field bits defined so far. */
#घोषणा RX_ERR		0x8000 // always present अगर there is an error (hmm)
#घोषणा CRC_ERR		0x4000 // AAL5 CRC error
#घोषणा LEN_ERR		0x2000 // overlength frame
#घोषणा ABORT_ERR	0x1000 // zero length field in received frame
#घोषणा UNUSED_ERR	0x0800 // buffer वापसed unused

// Adaptor commands

#घोषणा SRB_OPEN_VC		0
/* par_0: dwordswap(VC_number) */
/* par_1: dwordswap(flags<<16) or wordswap(flags)*/ 
/* flags:		*/

/* LANE:	0x0004		*/
/* NOT_UBR:	0x0008		*/
/* ABR:		0x0010		*/

/* RxPool0:	0x0000		*/
/* RxPool1:	0x0020		*/
/* RxPool2:	0x0040		*/
/* RxPool3:	0x0060		*/

/* par_2: dwordswap(fp_rate<<16) or wordswap(fp_rate) */

#घोषणा	SRB_CLOSE_VC		1
/* par_0: dwordswap(VC_number) */

#घोषणा	SRB_GET_BIA		2
/* वापसs 		*/
/* par_0: dwordswap(half BIA) */
/* par_1: dwordswap(half BIA) */

#घोषणा	SRB_GET_SUNI_STATS	3
/* par_0: dwordswap(physical_host_address) */

#घोषणा	SRB_SET_BITS_8		4
#घोषणा	SRB_SET_BITS_16		5
#घोषणा	SRB_SET_BITS_32		6
#घोषणा	SRB_CLEAR_BITS_8	7
#घोषणा	SRB_CLEAR_BITS_16	8
#घोषणा	SRB_CLEAR_BITS_32	9
/* par_0: dwordswap(ATMizer address)	*/
/* par_1: dwordswap(mask) */

#घोषणा	SRB_SET_8		10
#घोषणा	SRB_SET_16		11
#घोषणा	SRB_SET_32		12
/* par_0: dwordswap(ATMizer address)	*/
/* par_1: dwordswap(data) */

#घोषणा	SRB_GET_32		13
/* par_0: dwordswap(ATMizer address)	*/
/* वापसs			*/
/* par_1: dwordswap(ATMizer data) */

#घोषणा SRB_GET_VERSION		14
/* वापसs 		*/
/* par_0: dwordswap(Major Version) */
/* par_1: dwordswap(Minor Version) */

#घोषणा SRB_FLUSH_BUFFER_Q	15
/* Only flags to define which buffer pool; all others must be zero */
/* par_0: dwordswap(flags<<16) or wordswap(flags)*/ 

#घोषणा	SRB_GET_DMA_SPEEDS	16
/* वापसs 		*/
/* par_0: dwordswap(Read speed (bytes/sec)) */
/* par_1: dwordswap(Write speed (bytes/sec)) */

#घोषणा SRB_MODIFY_VC_RATE	17
/* par_0: dwordswap(VC_number) */
/* par_1: dwordswap(fp_rate<<16) or wordswap(fp_rate) */

#घोषणा SRB_MODIFY_VC_FLAGS	18
/* par_0: dwordswap(VC_number) */
/* par_1: dwordswap(flags<<16) or wordswap(flags)*/ 

/* flags:		*/

/* LANE:	0x0004		*/
/* NOT_UBR:	0x0008		*/
/* ABR:		0x0010		*/

/* RxPool0:	0x0000		*/
/* RxPool1:	0x0020		*/
/* RxPool2:	0x0040		*/
/* RxPool3:	0x0060		*/

#घोषणा SRB_RATE_SHIFT          16
#घोषणा SRB_POOL_SHIFT          (SRB_FLAGS_SHIFT+5)
#घोषणा SRB_FLAGS_SHIFT         16

#घोषणा	SRB_STOP_TASKING	19
#घोषणा	SRB_START_TASKING	20
#घोषणा SRB_SHUT_DOWN		21
#घोषणा MAX_SRB			21

#घोषणा SRB_COMPLETE		0xffffffff

#घोषणा TX_FRAME          	0x80000000

// number of types of SRB MUST be a घातer of two -- why?
#घोषणा NUM_OF_SRB	32

// number of bits of period info क्रम rate
#घोषणा MAX_RATE_BITS	6

#घोषणा TX_UBR          0x0000
#घोषणा TX_UBR_CAPPED   0x0008
#घोषणा TX_ABR          0x0018
#घोषणा TX_FRAME_NOTCAP 0x0000
#घोषणा TX_FRAME_CAPPED 0x8000

#घोषणा FP_155_RATE	0x24b1
#घोषणा FP_25_RATE	0x1f9d

/* #घोषणा VERSION_NUMBER 0x01000000 // initial release */
/* #घोषणा VERSION_NUMBER 0x01010000 // fixed startup probs PLX MB0 not cleared */
/* #घोषणा VERSION_NUMBER 0x01020000 // changed SUNI reset timings; allowed r/w onchip */

/* #घोषणा VERSION_NUMBER 0x01030000 // clear local करोorbell पूर्णांक reg on reset */
/* #घोषणा VERSION_NUMBER 0x01040000 // PLX bug work around version PLUS */
/* हटाओ race conditions on basic पूर्णांकerface */
/* indicate to the host that diagnostics */
/* have finished; अगर failed, how and what  */
/* failed */
/* fix host memory test to fix PLX bug */
/* allow flash upgrade and BIA upgrade directly */
/*  */
#घोषणा VERSION_NUMBER 0x01050025 /* Jason's first hacked version. */
/* Change in करोwnload algorithm */

#घोषणा DMA_VALID 0xb728e149 /* completely अक्रमom */

#घोषणा FLASH_BASE 0xa0c00000
#घोषणा FLASH_SIZE 0x00020000			/* 128K */
#घोषणा BIA_BASE (FLASH_BASE+0x0001c000)	/* Flash Sector 7 */
#घोषणा BIA_ADDRESS ((व्योम *)0xa0c1c000)
#घोषणा PLX_BASE 0xe0000000

प्रकार क्रमागत अणु
  host_memory_test = 1,
  पढ़ो_adapter_memory,
  ग_लिखो_adapter_memory,
  adapter_start,
  get_version_number,
  पूर्णांकerrupt_host,
  flash_erase_sector,
  adap_करोwnload_block = 0x20,
  adap_erase_flash,
  adap_run_in_iram,
  adap_end_करोwnload
पूर्ण loader_command;

#घोषणा BAD_COMMAND                     (-1)
#घोषणा COMMAND_IN_PROGRESS             1
#घोषणा COMMAND_PASSED_TEST             2
#घोषणा COMMAND_FAILED_TEST             3
#घोषणा COMMAND_READ_DATA_OK            4
#घोषणा COMMAND_READ_BAD_ADDRESS        5
#घोषणा COMMAND_WRITE_DATA_OK           6
#घोषणा COMMAND_WRITE_BAD_ADDRESS       7
#घोषणा COMMAND_WRITE_FLASH_FAILURE     8
#घोषणा COMMAND_COMPLETE                9
#घोषणा COMMAND_FLASH_ERASE_FAILURE	10
#घोषणा COMMAND_WRITE_BAD_DATA		11

/* bit fields क्रम mailbox[0] वापस values */

#घोषणा GPINT_TST_FAILURE               0x00000001      
#घोषणा SUNI_DATA_PATTERN_FAILURE       0x00000002
#घोषणा SUNI_DATA_BITS_FAILURE          0x00000004
#घोषणा SUNI_UTOPIA_FAILURE             0x00000008
#घोषणा SUNI_FIFO_FAILURE               0x00000010
#घोषणा SRAM_FAILURE                    0x00000020
#घोषणा SELF_TEST_FAILURE               0x0000003f

/* mailbox[1] = 0 in progress, -1 on completion */
/* mailbox[2] = current test 00 00 test(8 bit) phase(8 bit) */
/* mailbox[3] = last failure, 00 00 test(8 bit) phase(8 bit) */
/* mailbox[4],mailbox[5],mailbox[6] अक्रमom failure values */

/* PLX/etc. memory map including command काष्ठाure */

/* These रेजिस्टरs may also be memory mapped in PCI memory */

#घोषणा UNUSED_LOADER_MAILBOXES 6

प्रकार काष्ठा अणु
  u32 stuff[16];
  जोड़ अणु
    काष्ठा अणु
      u32 result;
      u32 पढ़ोy;
      u32 stuff[UNUSED_LOADER_MAILBOXES];
    पूर्ण loader;
    काष्ठा अणु
      u32 cmd_address;
      u32 tx_address;
      u32 rx_address[NUM_RX_POOLS];
      u32 gen_counter;
      u32 spare;
    पूर्ण adapter;
  पूर्ण mb;
  u32 करोorbell;
  u32 पूर्णांकerrupt;
  u32 पूर्णांकerrupt_control;
  u32 reset_control;
पूर्ण amb_mem;

/* RESET bit, IRQ (card to host) and करोorbell (host to card) enable bits */
#घोषणा AMB_RESET_BITS	   0x40000000
#घोषणा AMB_INTERRUPT_BITS 0x00000300
#घोषणा AMB_DOORBELL_BITS  0x00030000

/* loader commands */

#घोषणा MAX_COMMAND_DATA 13
#घोषणा MAX_TRANSFER_DATA 11

प्रकार काष्ठा अणु
  __be32 address;
  __be32 count;
  __be32 data[MAX_TRANSFER_DATA];
पूर्ण transfer_block;

प्रकार काष्ठा अणु
  __be32 result;
  __be32 command;
  जोड़ अणु
    transfer_block transfer;
    __be32 version;
    __be32 start;
    __be32 data[MAX_COMMAND_DATA];
  पूर्ण payload;
  __be32 valid;
पूर्ण loader_block;

/* command queue */

/* Again all data are BIG ENDIAN */

प्रकार	काष्ठा अणु
  जोड़ अणु
    काष्ठा अणु
      __be32 vc;
      __be32 flags;
      __be32 rate;
    पूर्ण खोलो;
    काष्ठा अणु
      __be32 vc;
      __be32 rate;
    पूर्ण modअगरy_rate;
    काष्ठा अणु
      __be32 vc;
      __be32 flags;
    पूर्ण modअगरy_flags;
    काष्ठा अणु
      __be32 vc;
    पूर्ण बंद;
    काष्ठा अणु
      __be32 lower4;
      __be32 upper2;
    पूर्ण bia;
    काष्ठा अणु
      __be32 address;
    पूर्ण suni;
    काष्ठा अणु
      __be32 major;
      __be32 minor;
    पूर्ण version;
    काष्ठा अणु
      __be32 पढ़ो;
      __be32 ग_लिखो;
    पूर्ण speed;
    काष्ठा अणु
      __be32 flags;
    पूर्ण flush;
    काष्ठा अणु
      __be32 address;
      __be32 data;
    पूर्ण memory;
    __be32 par[3];
  पूर्ण args;
  __be32 request;
पूर्ण command;

/* transmit queues and associated काष्ठाures */

/* The hosts transmit काष्ठाure. All BIG ENDIAN; host address
   restricted to first 1GByte, but address passed to the card must
   have the top MS bit or'ed in. -- check this */

/* TX is described by 1+ tx_frags followed by a tx_frag_end */

प्रकार काष्ठा अणु
  __be32 bytes;
  __be32 address;
पूर्ण tx_frag;

/* apart from handle the fields here are क्रम the adapter to play with
   and should be set to zero */

प्रकार काष्ठा अणु
  u32	handle;
  u16	vc;
  u16	next_descriptor_length;
  u32	next_descriptor;
#अगर_घोषित AMB_NEW_MICROCODE
  u8    cpcs_uu;
  u8    cpi;
  u16   pad;
#पूर्ण_अगर
पूर्ण tx_frag_end;

प्रकार काष्ठा अणु
  tx_frag tx_frag;
  tx_frag_end tx_frag_end;
  काष्ठा sk_buff * skb;
पूर्ण tx_simple;

#अगर 0
प्रकार जोड़ अणु
  tx_frag	fragment;
  tx_frag_end	end_of_list;
पूर्ण tx_descr;
#पूर्ण_अगर

/* this "points" to the sequence of fragments and trailer */

प्रकार	काष्ठा अणु
  __be16	vc;
  __be16	tx_descr_length;
  __be32	tx_descr_addr;
पूर्ण tx_in;

/* handle is the handle from tx_in */

प्रकार	काष्ठा अणु
  u32 handle;
पूर्ण tx_out;

/* receive frame काष्ठाure */

/* All BIG ENDIAN; handle is as passed from host; length is zero क्रम
   पातed frames, and frames with errors. Header is actually VC
   number, lec-id is NOT yet supported. */

प्रकार काष्ठा अणु
  u32  handle;
  __be16  vc;
  __be16  lec_id; // unused
  __be16  status;
  __be16  length;
पूर्ण rx_out;

/* buffer supply काष्ठाure */

प्रकार	काष्ठा अणु
  u32 handle;
  __be32 host_address;
पूर्ण rx_in;

/* This first काष्ठाure is the area in host memory where the adapter
   ग_लिखोs its poपूर्णांकer values. These poपूर्णांकer values are BIG ENDIAN and
   reside in the same 4MB 'page' as this काष्ठाure. The host gives the
   adapter the address of this block by sending a करोorbell पूर्णांकerrupt
   to the adapter after करोwnloading the code and setting it going. The
   addresses have the top 10 bits set to 1010000010b -- really?
   
   The host must initialise these beक्रमe handing the block to the
   adapter. */

प्रकार काष्ठा अणु
  __be32 command_start;		/* SRB commands completions */
  __be32 command_end;		/* SRB commands completions */
  __be32 tx_start;
  __be32 tx_end;
  __be32 txcom_start;		/* tx completions */
  __be32 txcom_end;		/* tx completions */
  काष्ठा अणु
    __be32 buffer_start;
    __be32 buffer_end;
    u32 buffer_q_get;
    u32 buffer_q_end;
    u32 buffer_aptr;
    __be32 rx_start;		/* rx completions */
    __be32 rx_end;
    u32 rx_ptr;
    __be32 buffer_size;		/* size of host buffer */
  पूर्ण rec_काष्ठा[NUM_RX_POOLS];
#अगर_घोषित AMB_NEW_MICROCODE
  u16 init_flags;
  u16 talk_block_spare;
#पूर्ण_अगर
पूर्ण adap_talk_block;

/* This काष्ठाure must be kept in line with the vcr image in sarमुख्य.h
   
   This is the काष्ठाure in the host filled in by the adapter by
   GET_SUNI_STATS */

प्रकार काष्ठा अणु
  u8	racp_chcs;
  u8	racp_uhcs;
  u16	spare;
  u32	racp_rcell;
  u32	tacp_tcell;
  u32	flags;
  u32	dropped_cells;
  u32	dropped_frames;
पूर्ण suni_stats;

प्रकार क्रमागत अणु
  dead
पूर्ण amb_flags;

#घोषणा NEXTQ(current,start,limit) \
  ( (current)+1 < (limit) ? (current)+1 : (start) ) 

प्रकार काष्ठा अणु
  command * start;
  command * in;
  command * out;
  command * limit;
पूर्ण amb_cq_ptrs;

प्रकार काष्ठा अणु
  spinlock_t lock;
  अचिन्हित पूर्णांक pending;
  अचिन्हित पूर्णांक high;
  अचिन्हित पूर्णांक filled;
  अचिन्हित पूर्णांक maximum; // size - 1 (q implementation)
  amb_cq_ptrs ptrs;
पूर्ण amb_cq;

प्रकार काष्ठा अणु
  spinlock_t lock;
  अचिन्हित पूर्णांक pending;
  अचिन्हित पूर्णांक high;
  अचिन्हित पूर्णांक filled;
  अचिन्हित पूर्णांक maximum; // size - 1 (q implementation)
  काष्ठा अणु
    tx_in * start;
    tx_in * ptr;
    tx_in * limit;
  पूर्ण in;
  काष्ठा अणु
    tx_out * start;
    tx_out * ptr;
    tx_out * limit;
  पूर्ण out;
पूर्ण amb_txq;

प्रकार काष्ठा अणु
  spinlock_t lock;
  अचिन्हित पूर्णांक pending;
  अचिन्हित पूर्णांक low;
  अचिन्हित पूर्णांक emptied;
  अचिन्हित पूर्णांक maximum; // size - 1 (q implementation)
  काष्ठा अणु
    rx_in * start;
    rx_in * ptr;
    rx_in * limit;
  पूर्ण in;
  काष्ठा अणु
    rx_out * start;
    rx_out * ptr;
    rx_out * limit;
  पूर्ण out;
  अचिन्हित पूर्णांक buffers_wanted;
  अचिन्हित पूर्णांक buffer_size;
पूर्ण amb_rxq;

प्रकार काष्ठा अणु
  अचिन्हित दीर्घ tx_ok;
  काष्ठा अणु
    अचिन्हित दीर्घ ok;
    अचिन्हित दीर्घ error;
    अचिन्हित दीर्घ badcrc;
    अचिन्हित दीर्घ tooदीर्घ;
    अचिन्हित दीर्घ पातed;
    अचिन्हित दीर्घ unused;
  पूर्ण rx;
पूर्ण amb_stats;

// a single काष्ठा poपूर्णांकed to by aपंचांग_vcc->dev_data

प्रकार काष्ठा अणु
  u8               tx_vc_bits:7;
  u8               tx_present:1;
पूर्ण amb_tx_info;

प्रकार काष्ठा अणु
  अचिन्हित अक्षर    pool;
पूर्ण amb_rx_info;

प्रकार काष्ठा अणु
  amb_rx_info      rx_info;
  u16              tx_frame_bits;
  अचिन्हित पूर्णांक     tx_rate;
  अचिन्हित पूर्णांक     rx_rate;
पूर्ण amb_vcc;

काष्ठा amb_dev अणु
  u8               irq;
  अचिन्हित दीर्घ	   flags;
  u32              iobase;
  u32 *            membase;

  amb_cq           cq;
  amb_txq          txq;
  amb_rxq          rxq[NUM_RX_POOLS];
  
  काष्ठा mutex     vcc_sf;
  amb_tx_info      txer[NUM_VCS];
  काष्ठा aपंचांग_vcc * rxer[NUM_VCS];
  अचिन्हित पूर्णांक     tx_avail;
  अचिन्हित पूर्णांक     rx_avail;
  
  amb_stats        stats;
  
  काष्ठा aपंचांग_dev * aपंचांग_dev;
  काष्ठा pci_dev * pci_dev;
  काष्ठा समयr_list housekeeping;
पूर्ण;

प्रकार काष्ठा amb_dev amb_dev;

#घोषणा AMB_DEV(aपंचांग_dev) ((amb_dev *) (aपंचांग_dev)->dev_data)
#घोषणा AMB_VCC(aपंचांग_vcc) ((amb_vcc *) (aपंचांग_vcc)->dev_data)

/* rate rounding */

प्रकार क्रमागत अणु
  round_up,
  round_करोwn,
  round_nearest
पूर्ण rounding;

#पूर्ण_अगर
