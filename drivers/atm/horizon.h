<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
  Madge Horizon ATM Adapter driver.
  Copyright (C) 1995-1999  Madge Networks Ltd.

*/

/*
  IMPORTANT NOTE: Madge Networks no दीर्घer makes the adapters
  supported by this driver and makes no commiपंचांगent to मुख्यtain it.
*/

/* too many macros - change to अंतरभूत functions */

#अगर_अघोषित DRIVER_ATM_HORIZON_H
#घोषणा DRIVER_ATM_HORIZON_H


#अगर_घोषित CONFIG_ATM_HORIZON_DEBUG
#घोषणा DEBUG_HORIZON
#पूर्ण_अगर

#घोषणा DEV_LABEL                         "hrz"

#अगर_अघोषित PCI_VENDOR_ID_MADGE
#घोषणा PCI_VENDOR_ID_MADGE               0x10B6
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_MADGE_HORIZON
#घोषणा PCI_DEVICE_ID_MADGE_HORIZON       0x1000
#पूर्ण_अगर

// diagnostic output

#घोषणा PRINTK(severity,क्रमmat,args...) \
  prपूर्णांकk(severity DEV_LABEL ": " क्रमmat "\n" , ## args)

#अगर_घोषित DEBUG_HORIZON

#घोषणा DBG_ERR  0x0001
#घोषणा DBG_WARN 0x0002
#घोषणा DBG_INFO 0x0004
#घोषणा DBG_VCC  0x0008
#घोषणा DBG_QOS  0x0010
#घोषणा DBG_TX   0x0020
#घोषणा DBG_RX   0x0040
#घोषणा DBG_SKB  0x0080
#घोषणा DBG_IRQ  0x0100
#घोषणा DBG_FLOW 0x0200
#घोषणा DBG_BUS  0x0400
#घोषणा DBG_REGS 0x0800
#घोषणा DBG_DATA 0x1000
#घोषणा DBG_MASK 0x1fff

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

#घोषणा PRINTDD(sec,fmt,args...)
#घोषणा PRINTDDB(sec,fmt,args...)
#घोषणा PRINTDDM(sec,fmt,args...)
#घोषणा PRINTDDE(sec,fmt,args...)

// fixed स्थिरants

#घोषणा SPARE_BUFFER_POOL_SIZE            MAX_VCS
#घोषणा HRZ_MAX_VPI                       4
#घोषणा MIN_PCI_LATENCY                   48 // 24 IS TOO SMALL

/*  Horizon specअगरic bits */
/*  Register offsets */

#घोषणा HRZ_IO_EXTENT                     0x80

#घोषणा DATA_PORT_OFF                     0x00
#घोषणा TX_CHANNEL_PORT_OFF               0x04
#घोषणा TX_DESCRIPTOR_PORT_OFF            0x08
#घोषणा MEMORY_PORT_OFF                   0x0C
#घोषणा MEM_WR_ADDR_REG_OFF               0x14
#घोषणा MEM_RD_ADDR_REG_OFF               0x18
#घोषणा CONTROL_0_REG                     0x1C
#घोषणा INT_SOURCE_REG_OFF                0x20
#घोषणा INT_ENABLE_REG_OFF                0x24
#घोषणा MASTER_RX_ADDR_REG_OFF            0x28
#घोषणा MASTER_RX_COUNT_REG_OFF           0x2C
#घोषणा MASTER_TX_ADDR_REG_OFF            0x30
#घोषणा MASTER_TX_COUNT_REG_OFF           0x34
#घोषणा TX_DESCRIPTOR_REG_OFF             0x38
#घोषणा TX_CHANNEL_CONFIG_COMMAND_OFF     0x40
#घोषणा TX_CHANNEL_CONFIG_DATA_OFF        0x44
#घोषणा TX_FREE_BUFFER_COUNT_OFF          0x48
#घोषणा RX_FREE_BUFFER_COUNT_OFF          0x4C
#घोषणा TX_CONFIG_OFF                     0x50
#घोषणा TX_STATUS_OFF                     0x54
#घोषणा RX_CONFIG_OFF                     0x58
#घोषणा RX_LINE_CONFIG_OFF                0x5C
#घोषणा RX_QUEUE_RD_PTR_OFF               0x60
#घोषणा RX_QUEUE_WR_PTR_OFF               0x64
#घोषणा MAX_AAL5_CELL_COUNT_OFF           0x68
#घोषणा RX_CHANNEL_PORT_OFF               0x6C
#घोषणा TX_CELL_COUNT_OFF                 0x70
#घोषणा RX_CELL_COUNT_OFF                 0x74
#घोषणा HEC_ERROR_COUNT_OFF               0x78
#घोषणा UNASSIGNED_CELL_COUNT_OFF         0x7C

/*  Register bit definitions */

/* Control 0 रेजिस्टर */

#घोषणा SEEPROM_DO                        0x00000001
#घोषणा SEEPROM_DI                        0x00000002
#घोषणा SEEPROM_SK                        0x00000004
#घोषणा SEEPROM_CS                        0x00000008
#घोषणा DEBUG_BIT_0                       0x00000010
#घोषणा DEBUG_BIT_1                       0x00000020
#घोषणा DEBUG_BIT_2                       0x00000040
//      RESERVED                          0x00000080
#घोषणा DEBUG_BIT_0_OE                    0x00000100
#घोषणा DEBUG_BIT_1_OE                    0x00000200
#घोषणा DEBUG_BIT_2_OE                    0x00000400
//      RESERVED                          0x00000800
#घोषणा DEBUG_BIT_0_STATE                 0x00001000
#घोषणा DEBUG_BIT_1_STATE                 0x00002000
#घोषणा DEBUG_BIT_2_STATE                 0x00004000
//      RESERVED                          0x00008000
#घोषणा GENERAL_BIT_0                     0x00010000
#घोषणा GENERAL_BIT_1                     0x00020000
#घोषणा GENERAL_BIT_2                     0x00040000
#घोषणा GENERAL_BIT_3                     0x00080000
#घोषणा RESET_HORIZON                     0x00100000
#घोषणा RESET_ATM                         0x00200000
#घोषणा RESET_RX                          0x00400000
#घोषणा RESET_TX                          0x00800000
#घोषणा RESET_HOST                        0x01000000
//      RESERVED                          0x02000000
#घोषणा TARGET_RETRY_DISABLE              0x04000000
#घोषणा ATM_LAYER_SELECT                  0x08000000
#घोषणा ATM_LAYER_STATUS                  0x10000000
//      RESERVED                          0xE0000000

/* Interrupt source and enable रेजिस्टरs */

#घोषणा RX_DATA_AV                        0x00000001
#घोषणा RX_DISABLED                       0x00000002
#घोषणा TIMING_MARKER                     0x00000004
#घोषणा FORCED                            0x00000008
#घोषणा RX_BUS_MASTER_COMPLETE            0x00000010
#घोषणा TX_BUS_MASTER_COMPLETE            0x00000020
#घोषणा ABR_TX_CELL_COUNT_INT             0x00000040
#घोषणा DEBUG_INT                         0x00000080
//      RESERVED                          0xFFFFFF00

/* PIO and Bus Mastering */

#घोषणा MAX_PIO_COUNT                     0x000000ff // 255 - make tunable?
// 8188 is a hard limit क्रम bus mastering
#घोषणा MAX_TRANSFER_COUNT                0x00001ffc // 8188
#घोषणा MASTER_TX_AUTO_APPEND_DESC        0x80000000

/* TX channel config command port */

#घोषणा PCR_TIMER_ACCESS                      0x0000
#घोषणा SCR_TIMER_ACCESS                      0x0001
#घोषणा BUCKET_CAPACITY_ACCESS                0x0002
#घोषणा BUCKET_FULLNESS_ACCESS                0x0003
#घोषणा RATE_TYPE_ACCESS                      0x0004
//      UNUSED                                0x00F8
#घोषणा TX_CHANNEL_CONFIG_MULT                0x0100
//      UNUSED                                0xF800
#घोषणा BUCKET_MAX_SIZE                       0x003f

/* TX channel config data port */

#घोषणा CLOCK_SELECT_SHIFT                    4
#घोषणा CLOCK_DISABLE                         0x00ff

#घोषणा IDLE_RATE_TYPE                       0x0
#घोषणा ABR_RATE_TYPE                        0x1
#घोषणा VBR_RATE_TYPE                        0x2
#घोषणा CBR_RATE_TYPE                        0x3

/* TX config रेजिस्टर */

#घोषणा DRVR_DRVRBAR_ENABLE                   0x0001
#घोषणा TXCLK_MUX_SELECT_RCLK                 0x0002
#घोषणा TRANSMIT_TIMING_MARKER                0x0004
#घोषणा LOOPBACK_TIMING_MARKER                0x0008
#घोषणा TX_TEST_MODE_16MHz                    0x0000
#घोषणा TX_TEST_MODE_8MHz                     0x0010
#घोषणा TX_TEST_MODE_5_33MHz                  0x0020
#घोषणा TX_TEST_MODE_4MHz                     0x0030
#घोषणा TX_TEST_MODE_3_2MHz                   0x0040
#घोषणा TX_TEST_MODE_2_66MHz                  0x0050
#घोषणा TX_TEST_MODE_2_29MHz                  0x0060
#घोषणा TX_NORMAL_OPERATION                   0x0070
#घोषणा ABR_ROUND_ROBIN                       0x0080

/* TX status रेजिस्टर */

#घोषणा IDLE_CHANNELS_MASK                    0x00FF
#घोषणा ABR_CELL_COUNT_REACHED_MULT           0x0100 
#घोषणा ABR_CELL_COUNT_REACHED_MASK           0xFF

/* RX config रेजिस्टर */

#घोषणा NON_USER_CELLS_IN_ONE_CHANNEL         0x0008
#घोषणा RX_ENABLE                             0x0010
#घोषणा IGNORE_UNUSED_VPI_VCI_BITS_SET        0x0000
#घोषणा NON_USER_UNUSED_VPI_VCI_BITS_SET      0x0020
#घोषणा DISCARD_UNUSED_VPI_VCI_BITS_SET       0x0040

/* RX line config रेजिस्टर */

#घोषणा SIGNAL_LOSS                           0x0001
#घोषणा FREQUENCY_DETECT_ERROR                0x0002
#घोषणा LOCK_DETECT_ERROR                     0x0004
#घोषणा SELECT_INTERNAL_LOOPBACK              0x0008
#घोषणा LOCK_DETECT_ENABLE                    0x0010
#घोषणा FREQUENCY_DETECT_ENABLE               0x0020
#घोषणा USER_FRAQ                             0x0040
#घोषणा GXTALOUT_SELECT_DIV4                  0x0080
#घोषणा GXTALOUT_SELECT_NO_GATING             0x0100
#घोषणा TIMING_MARKER_RECEIVED                0x0200

/* RX channel port */

#घोषणा RX_CHANNEL_MASK                       0x03FF
// UNUSED                                     0x3C00
#घोषणा FLUSH_CHANNEL                         0x4000
#घोषणा RX_CHANNEL_UPDATE_IN_PROGRESS         0x8000

/* Receive queue entry */

#घोषणा RX_Q_ENTRY_LENGTH_MASK            0x0000FFFF
#घोषणा RX_Q_ENTRY_CHANNEL_SHIFT          16
#घोषणा SIMONS_DODGEY_MARKER              0x08000000
#घोषणा RX_CONGESTION_EXPERIENCED         0x10000000
#घोषणा RX_CRC_10_OK                      0x20000000
#घोषणा RX_CRC_32_OK                      0x40000000
#घोषणा RX_COMPLETE_FRAME                 0x80000000

/*  Offsets and स्थिरants क्रम use with the buffer memory         */

/* Buffer poपूर्णांकers and channel types */

#घोषणा BUFFER_PTR_MASK                   0x0000FFFF
#घोषणा RX_INT_THRESHOLD_MULT             0x00010000
#घोषणा RX_INT_THRESHOLD_MASK             0x07FF
#घोषणा INT_EVERY_N_CELLS                 0x08000000
#घोषणा CONGESTION_EXPERIENCED            0x10000000
#घोषणा FIRST_CELL_OF_AAL5_FRAME          0x20000000
#घोषणा CHANNEL_TYPE_AAL5                 0x00000000
#घोषणा CHANNEL_TYPE_RAW_CELLS            0x40000000
#घोषणा CHANNEL_TYPE_AAL3_4               0x80000000

/* Buffer status stuff */

#घोषणा BUFF_STATUS_MASK                  0x00030000
#घोषणा BUFF_STATUS_EMPTY                 0x00000000
#घोषणा BUFF_STATUS_CELL_AV               0x00010000
#घोषणा BUFF_STATUS_LAST_CELL_AV          0x00020000

/* Transmit channel stuff */

/* Receive channel stuff */

#घोषणा RX_CHANNEL_DISABLED               0x00000000
#घोषणा RX_CHANNEL_IDLE                   0x00000001

/*  General things */

#घोषणा INITIAL_CRC                       0xFFFFFFFF

// A Horizon u32, a byte! Really nasty. Horizon poपूर्णांकers are (32 bit)
// word addresses and so standard C poपूर्णांकer operations अवरोध (as they
// assume byte addresses); so we pretend that Horizon words (and word
// poपूर्णांकers) are bytes (and byte poपूर्णांकers) क्रम the purposes of having
// a memory map that works.

प्रकार u8 HDW;

प्रकार काष्ठा cell_buf अणु
  HDW payload[12];
  HDW next;
  HDW cell_count;               // AAL5 rx bufs
  HDW res;
  जोड़ अणु
    HDW partial_crc;            // AAL5 rx bufs
    HDW cell_header;            // RAW     bufs
  पूर्ण u;
पूर्ण cell_buf;

प्रकार काष्ठा tx_ch_desc अणु
  HDW rd_buf_type;
  HDW wr_buf_type;
  HDW partial_crc;
  HDW cell_header;
पूर्ण tx_ch_desc;

प्रकार काष्ठा rx_ch_desc अणु
  HDW wr_buf_type;
  HDW rd_buf_type;
पूर्ण rx_ch_desc;

प्रकार काष्ठा rx_q_entry अणु
  HDW entry;
पूर्ण rx_q_entry;

#घोषणा TX_CHANS 8
#घोषणा RX_CHANS 1024
#घोषणा RX_QS 1024
#घोषणा MAX_VCS RX_CHANS

/* Horizon buffer memory map */

// TX Channel Descriptors         2
// TX Initial Buffers             8 // TX_CHANS
#घोषणा BUFN1_SIZE              118 // (126 - TX_CHANS)
//      RX/TX Start/End Buffers   4
#घोषणा BUFN2_SIZE              124
//      RX Queue Entries         64
#घोषणा BUFN3_SIZE              192
//      RX Channel Descriptors  128
#घोषणा BUFN4_SIZE             1408
//      TOTAL cell_buff chunks 2048

//    cell_buf             bufs[2048];
//    HDW                  dws[32768];

प्रकार काष्ठा MEMMAP अणु
  tx_ch_desc  tx_descs[TX_CHANS];     //  8 *    4 =    32 , 0x0020
  cell_buf    inittxbufs[TX_CHANS];   // these are really
  cell_buf    bufn1[BUFN1_SIZE];      // part of this pool
  cell_buf    txमुक्तbufstart;
  cell_buf    txमुक्तbufend;
  cell_buf    rxमुक्तbufstart;
  cell_buf    rxमुक्तbufend;           // 8+118+1+1+1+1+124 = 254
  cell_buf    bufn2[BUFN2_SIZE];      // 16 *  254 =  4064 , 0x1000
  rx_q_entry  rx_q_entries[RX_QS];    //  1 * 1024 =  1024 , 0x1400
  cell_buf    bufn3[BUFN3_SIZE];      // 16 *  192 =  3072 , 0x2000
  rx_ch_desc  rx_descs[MAX_VCS];      //  2 * 1024 =  2048 , 0x2800
  cell_buf    bufn4[BUFN4_SIZE];      // 16 * 1408 = 22528 , 0x8000
पूर्ण MEMMAP;

#घोषणा memmap ((MEMMAP *)0)

/* end horizon specअगरic bits */

प्रकार क्रमागत अणु
  aal0,
  aal34,
  aal5
पूर्ण hrz_aal;

प्रकार क्रमागत अणु
  tx_busy,
  rx_busy,
  ultra
पूर्ण hrz_flags;

// a single काष्ठा poपूर्णांकed to by aपंचांग_vcc->dev_data

प्रकार काष्ठा अणु
  अचिन्हित पूर्णांक        tx_rate;
  अचिन्हित पूर्णांक        rx_rate;
  u16                 channel;
  u16                 tx_xbr_bits;
  u16                 tx_pcr_bits;
#अगर 0
  u16                 tx_scr_bits;
  u16                 tx_bucket_bits;
#पूर्ण_अगर
  hrz_aal             aal;
पूर्ण hrz_vcc;

काष्ठा hrz_dev अणु
  
  u32                 iobase;
  u32 *               membase;

  काष्ठा sk_buff *    rx_skb;     // skb being RXed
  अचिन्हित पूर्णांक        rx_bytes;   // bytes reमुख्यing to RX within region
  व्योम *              rx_addr;    // addr to send bytes to (क्रम PIO)
  अचिन्हित पूर्णांक        rx_channel; // channel that the skb is going out on

  काष्ठा sk_buff *    tx_skb;     // skb being TXed
  अचिन्हित पूर्णांक        tx_bytes;   // bytes reमुख्यing to TX within region
  व्योम *              tx_addr;    // addr to send bytes from (क्रम PIO)
  काष्ठा iovec *      tx_iovec;   // reमुख्यing regions
  अचिन्हित पूर्णांक        tx_regions; // number of reमुख्यing regions

  spinlock_t          mem_lock;
  रुको_queue_head_t   tx_queue;

  u8                  irq;
  अचिन्हित दीर्घ	      flags;
  u8                  tx_last;
  u8                  tx_idle;

  rx_q_entry *        rx_q_reset;
  rx_q_entry *        rx_q_entry;
  rx_q_entry *        rx_q_wrap;

  काष्ठा aपंचांग_dev *    aपंचांग_dev;

  u32                 last_vc;
  
  पूर्णांक                 noof_spare_buffers;
  u16                 spare_buffers[SPARE_BUFFER_POOL_SIZE];

  u16                 tx_channel_record[TX_CHANS];

  // this is what we follow when we get incoming data
  u32              txer[MAX_VCS/32];
  काष्ठा aपंचांग_vcc * rxer[MAX_VCS];

  // cell rate allocation
  spinlock_t       rate_lock;
  अचिन्हित पूर्णांक     rx_avail;
  अचिन्हित पूर्णांक     tx_avail;
  
  // dev stats
  अचिन्हित दीर्घ    tx_cell_count;
  अचिन्हित दीर्घ    rx_cell_count;
  अचिन्हित दीर्घ    hec_error_count;
  अचिन्हित दीर्घ    unasचिन्हित_cell_count;

  काष्ठा pci_dev * pci_dev;
  काष्ठा समयr_list housekeeping;
पूर्ण;

प्रकार काष्ठा hrz_dev hrz_dev;

/* macros क्रम use later */

#घोषणा BUF_PTR(cbptr) ((cbptr) - (cell_buf *) 0)

#घोषणा INTERESTING_INTERRUPTS \
  (RX_DATA_AV | RX_DISABLED | TX_BUS_MASTER_COMPLETE | RX_BUS_MASTER_COMPLETE)

// 190 cells by शेष (192 TX buffers - 2 elbow room, see करोcs)
#घोषणा TX_AAL5_LIMIT (190*ATM_CELL_PAYLOAD-ATM_AAL5_TRAILER) // 9112

// Have enough RX buffers (unless we allow other buffer splits)
#घोषणा RX_AAL5_LIMIT ATM_MAX_AAL5_PDU

/* multi-statement macro protector */
#घोषणा DW(x) करोअणु x पूर्ण जबतक(0)

#घोषणा HRZ_DEV(aपंचांग_dev) ((hrz_dev *) (aपंचांग_dev)->dev_data)
#घोषणा HRZ_VCC(aपंचांग_vcc) ((hrz_vcc *) (aपंचांग_vcc)->dev_data)

/* Turn the LEDs on and off                                                 */
// The LEDs bits are upside करोwn in that setting the bit in the debug
// रेजिस्टर will turn the appropriate LED off.

#घोषणा YELLOW_LED    DEBUG_BIT_0
#घोषणा GREEN_LED     DEBUG_BIT_1
#घोषणा YELLOW_LED_OE DEBUG_BIT_0_OE
#घोषणा GREEN_LED_OE  DEBUG_BIT_1_OE

#घोषणा GREEN_LED_OFF(dev)                      \
  wr_regl (dev, CONTROL_0_REG, rd_regl (dev, CONTROL_0_REG) | GREEN_LED)
#घोषणा GREEN_LED_ON(dev)                       \
  wr_regl (dev, CONTROL_0_REG, rd_regl (dev, CONTROL_0_REG) &~ GREEN_LED)
#घोषणा YELLOW_LED_OFF(dev)                     \
  wr_regl (dev, CONTROL_0_REG, rd_regl (dev, CONTROL_0_REG) | YELLOW_LED)
#घोषणा YELLOW_LED_ON(dev)                      \
  wr_regl (dev, CONTROL_0_REG, rd_regl (dev, CONTROL_0_REG) &~ YELLOW_LED)

प्रकार क्रमागत अणु
  round_up,
  round_करोwn,
  round_nearest
पूर्ण rounding;

#पूर्ण_अगर /* DRIVER_ATM_HORIZON_H */
