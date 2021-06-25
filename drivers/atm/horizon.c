<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
  Madge Horizon ATM Adapter driver.
  Copyright (C) 1995-1999  Madge Networks Ltd.
  
*/

/*
  IMPORTANT NOTE: Madge Networks no दीर्घer makes the adapters
  supported by this driver and makes no commiपंचांगent to मुख्यtain it.
*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/sonet.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समय.स>
#समावेश <linux/delay.h>
#समावेश <linux/uपन.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/माला.स>
#समावेश <यंत्र/byteorder.h>

#समावेश "horizon.h"

#घोषणा मुख्यtainer_string "Giuliano Procida at Madge Networks <gprocida@madge.com>"
#घोषणा description_string "Madge ATM Horizon [Ultra] driver"
#घोषणा version_string "1.2.1"

अटल अंतरभूत व्योम __init show_version (व्योम) अणु
  prपूर्णांकk ("%s version %s\n", description_string, version_string);
पूर्ण

/*
  
  CREDITS
  
  Driver and करोcumentation by:
  
  Chris Aston        Madge Networks
  Giuliano Procida   Madge Networks
  Simon Benham       Madge Networks
  Simon Johnson      Madge Networks
  Various Others     Madge Networks
  
  Some inspiration taken from other drivers by:
  
  Alexandru Cucos    UTBv
  Kari Mettinen      University of Helsinki
  Werner Almesberger EPFL LRC
  
  Theory of Operation
  
  I Hardware, detection, initialisation and shutकरोwn.
  
  1. Supported Hardware
  
  This driver should handle all variants of the PCI Madge ATM adapters
  with the Horizon chipset. These are all PCI cards supporting PIO, BM
  DMA and a क्रमm of MMIO (रेजिस्टरs only, not पूर्णांकernal RAM).
  
  The driver is only known to work with SONET and UTP Horizon Ultra
  cards at 155Mb/s. However, code is in place to deal with both the
  original Horizon and 25Mb/s operation.
  
  There are two revisions of the Horizon ASIC: the original and the
  Ultra. Details of hardware bugs are in section III.
  
  The ASIC version can be distinguished by chip markings but is NOT
  indicated by the PCI revision (all adapters seem to have PCI rev 1).
  
  I believe that:
  
  Horizon       => Collage  25 PCI Adapter (UTP and STP)
  Horizon Ultra => Collage 155 PCI Client (UTP or SONET)
  Ambassaकरोr x  => Collage 155 PCI Server (completely dअगरferent)
  
  Horizon (25Mb/s) is fitted with UTP and STP connectors. It seems to
  have a Madge B154 plus glue logic serializer. I have also found a
  really ancient version of this with slightly dअगरferent glue. It
  comes with the revision 0 (140-025-01) ASIC.
  
  Horizon Ultra (155Mb/s) is fitted with either a Pulse Medialink
  output (UTP) or an HP HFBR 5205 output (SONET). It has either
  Madge's SAMBA framer or a SUNI-lite device (early versions). It
  comes with the revision 1 (140-027-01) ASIC.
  
  2. Detection
  
  All Horizon-based cards present with the same PCI Venकरोr and Device
  IDs. The standard Linux 2.2 PCI API is used to locate any cards and
  to enable bus-mastering (with appropriate latency).
  
  ATM_LAYER_STATUS in the control रेजिस्टर distinguishes between the
  two possible physical layers (25 and 155). It is not clear whether
  the 155 cards can also operate at 25Mbps. We rely on the fact that a
  card operates at 155 अगर and only अगर it has the newer Horizon Ultra
  ASIC.
  
  For 155 cards the two possible framers are probed क्रम and then set
  up क्रम loop-timing.
  
  3. Initialisation
  
  The card is reset and then put पूर्णांकo a known state. The physical
  layer is configured क्रम normal operation at the appropriate speed;
  in the हाल of the 155 cards, the framer is initialised with
  line-based timing; the पूर्णांकernal RAM is zeroed and the allocation of
  buffers क्रम RX and TX is made; the Burnt In Address is पढ़ो and
  copied to the ATM ESI; various policy settings क्रम RX (VPI bits,
  unknown VCs, oam cells) are made. Ideally all policy items should be
  configurable at module load (अगर not actually on-demand), however,
  only the vpi vs vci bit allocation can be specअगरied at insmod.
  
  4. Shutकरोwn
  
  This is in response to module_cleaup. No VCs are in use and the card
  should be idle; it is reset.
  
  II Driver software (as it should be)
  
  0. Traffic Parameters
  
  The traffic classes (not an क्रमागतeration) are currently: ATM_NONE (no
  traffic), ATM_UBR, ATM_CBR, ATM_VBR and ATM_ABR, ATM_ANYCLASS
  (compatible with everything). Together with (perhaps only some of)
  the following items they make up the traffic specअगरication.
  
  काष्ठा aपंचांग_trafprm अणु
    अचिन्हित अक्षर traffic_class; traffic class (ATM_UBR, ...)
    पूर्णांक           max_pcr;       maximum PCR in cells per second
    पूर्णांक           pcr;           desired PCR in cells per second
    पूर्णांक           min_pcr;       minimum PCR in cells per second
    पूर्णांक           max_cdv;       maximum CDV in microseconds
    पूर्णांक           max_sdu;       maximum SDU in bytes
  पूर्ण;
  
  Note that these denote bandwidth available not bandwidth used; the
  possibilities according to ATMF are:
  
  Real Time (cdv and max CDT given)
  
  CBR(pcr)             pcr bandwidth always available
  rtVBR(pcr,scr,mbs)   scr bandwidth always available, up to pcr at mbs too
  
  Non Real Time
  
  nrtVBR(pcr,scr,mbs)  scr bandwidth always available, up to pcr at mbs too
  UBR()
  ABR(mcr,pcr)         mcr bandwidth always available, up to pcr (depending) too
  
  mbs is max burst size (bucket)
  pcr and scr have associated cdvt values
  mcr is like scr but has no cdtv
  cdtv may dअगरfer at each hop
  
  Some of the above items are qos items (as opposed to traffic
  parameters). We have nothing to करो with qos. All except ABR can have
  their traffic parameters converted to GCRA parameters. The GCRA may
  be implemented as a (real-number) leaky bucket. The GCRA can be used
  in complicated ways by चयनes and in simpler ways by end-stations.
  It can be used both to filter incoming cells and shape out-going
  cells.
  
  ATM Linux actually supports:
  
  ATM_NONE() (no traffic in this direction)
  ATM_UBR(max_frame_size)
  ATM_CBR(max/min_pcr, max_cdv, max_frame_size)
  
  0 or ATM_MAX_PCR are used to indicate maximum available PCR
  
  A traffic specअगरication consists of the AAL type and separate
  traffic specअगरications क्रम either direction. In ATM Linux it is:
  
  काष्ठा aपंचांग_qos अणु
  काष्ठा aपंचांग_trafprm txtp;
  काष्ठा aपंचांग_trafprm rxtp;
  अचिन्हित अक्षर aal;
  पूर्ण;
  
  AAL types are:
  
  ATM_NO_AAL    AAL not specअगरied
  ATM_AAL0      "raw" ATM cells
  ATM_AAL1      AAL1 (CBR)
  ATM_AAL2      AAL2 (VBR)
  ATM_AAL34     AAL3/4 (data)
  ATM_AAL5      AAL5 (data)
  ATM_SAAL      संकेतing AAL
  
  The Horizon has support क्रम AAL frame types: 0, 3/4 and 5. However,
  it करोes not implement AAL 3/4 SAR and it has a dअगरferent notion of
  "raw cell" to ATM Linux's (48 bytes vs. 52 bytes) so neither are
  supported by this driver.
  
  The Horizon has limited support क्रम ABR (including UBR), VBR and
  CBR. Each TX channel has a bucket (containing up to 31 cell units)
  and two समयrs (PCR and SCR) associated with it that can be used to
  govern cell emissions and host notअगरication (in the हाल of ABR this
  is presumably so that RM cells may be emitted at appropriate बार).
  The समयrs may either be disabled or may be set to any of 240 values
  (determined by the घड़ी crystal, a fixed (?) per-device भागider, a
  configurable भागider and a configurable समयr preload value).
  
  At the moment only UBR and CBR are supported by the driver. VBR will
  be supported as soon as ATM क्रम Linux supports it. ABR support is
  very unlikely as RM cell handling is completely up to the driver.
  
  1. TX (TX channel setup and TX transfer)
  
  The TX half of the driver owns the TX Horizon रेजिस्टरs. The TX
  component in the IRQ handler is the BM completion handler. This can
  only be entered when tx_busy is true (enक्रमced by hardware). The
  other TX component can only be entered when tx_busy is false
  (enक्रमced by driver). So TX is single-thपढ़ोed.
  
  Apart from a minor optimisation to not re-select the last channel,
  the TX send component works as follows:
  
  Atomic test and set tx_busy until we succeed; we should implement
  some sort of समयout so that tx_busy will never be stuck at true.
  
  If no TX channel is set up क्रम this VC we रुको क्रम an idle one (अगर
  necessary) and set it up.
  
  At this poपूर्णांक we have a TX channel पढ़ोy क्रम use. We रुको क्रम enough
  buffers to become available then start a TX transmit (set the TX
  descriptor, schedule transfer, निकास).
  
  The IRQ component handles TX completion (stats, मुक्त buffer, tx_busy
  unset, निकास). We also re-schedule further transfers क्रम the same
  frame अगर needed.
  
  TX setup in more detail:
  
  TX खोलो is a nop, the relevant inक्रमmation is held in the hrz_vcc
  (vcc->dev_data) काष्ठाure and is "cached" on the card.
  
  TX बंद माला_लो the TX lock and clears the channel from the "cache".
  
  2. RX (Data Available and RX transfer)
  
  The RX half of the driver owns the RX रेजिस्टरs. There are two RX
  components in the IRQ handler: the data available handler deals with
  fresh data that has arrived on the card, the BM completion handler
  is very similar to the TX completion handler. The data available
  handler grअसल the rx_lock and it is only released once the data has
  been discarded or completely transferred to the host. The BM
  completion handler only runs when the lock is held; the data
  available handler is locked out over the same period.
  
  Data available on the card triggers an पूर्णांकerrupt. If the data is not
  suitable क्रम our existing RX channels or we cannot allocate a buffer
  it is flushed. Otherwise an RX receive is scheduled. Multiple RX
  transfers may be scheduled क्रम the same frame.
  
  RX setup in more detail:
  
  RX खोलो...
  RX बंद...
  
  III Hardware Bugs
  
  0. Byte vs Word addressing of adapter RAM.
  
  A design feature; see the .h file (especially the memory map).
  
  1. Bus Master Data Transfers (original Horizon only, fixed in Ultra)
  
  The host must not start a transmit direction transfer at a
  non-four-byte boundary in host memory. Instead the host should
  perक्रमm a byte, or a two byte, or one byte followed by two byte
  transfer in order to start the rest of the transfer on a four byte
  boundary. RX is OK.
  
  Simultaneous transmit and receive direction bus master transfers are
  not allowed.
  
  The simplest solution to these two is to always करो PIO (never DMA)
  in the TX direction on the original Horizon. More complicated
  solutions are likely to hurt my brain.
  
  2. Loss of buffer on बंद VC
  
  When a VC is being बंदd, the buffer associated with it is not
  वापसed to the pool. The host must store the reference to this
  buffer and when खोलोing a new VC then give it to that new VC.
  
  The host पूर्णांकervention currently consists of stacking such a buffer
  poपूर्णांकer at VC बंद and checking the stack at VC खोलो.
  
  3. Failure to बंद a VC
  
  If a VC is currently receiving a frame then closing the VC may fail
  and the frame जारीs to be received.
  
  The solution is to make sure any received frames are flushed when
  पढ़ोy. This is currently करोne just beक्रमe the solution to 2.
  
  4. PCI bus (original Horizon only, fixed in Ultra)
  
  Reading from the data port prior to initialisation will hang the PCI
  bus. Just करोn't do that then! We don't.
  
  IV To Do List
  
  . Timer code may be broken.
  
  . Allow users to specअगरy buffer allocation split क्रम TX and RX.
  
  . Deal once and क्रम all with buggy VC बंद.
  
  . Handle पूर्णांकerrupted and/or non-blocking operations.
  
  . Change some macros to functions and move from .h to .c.
  
  . Try to limit the number of TX frames each VC may have queued, in
    order to reduce the chances of TX buffer exhaustion.
  
  . Implement VBR (bucket and समयrs not understood) and ABR (need to
    करो RM cells manually); also no Linux support क्रम either.
  
  . Implement QoS changes on खोलो VCs (involves extracting parts of VC खोलो
    and बंद पूर्णांकo separate functions and using them to make changes).
  
*/

/********** globals **********/

अटल व्योम करो_housekeeping (काष्ठा समयr_list *t);

अटल अचिन्हित लघु debug = 0;
अटल अचिन्हित लघु vpi_bits = 0;
अटल पूर्णांक max_tx_size = 9000;
अटल पूर्णांक max_rx_size = 9000;
अटल अचिन्हित अक्षर pci_lat = 0;

/********** access functions **********/

/* Read / Write Horizon रेजिस्टरs */
अटल अंतरभूत व्योम wr_regl (स्थिर hrz_dev * dev, अचिन्हित अक्षर reg, u32 data) अणु
  outl (cpu_to_le32 (data), dev->iobase + reg);
पूर्ण

अटल अंतरभूत u32 rd_regl (स्थिर hrz_dev * dev, अचिन्हित अक्षर reg) अणु
  वापस le32_to_cpu (inl (dev->iobase + reg));
पूर्ण

अटल अंतरभूत व्योम wr_regw (स्थिर hrz_dev * dev, अचिन्हित अक्षर reg, u16 data) अणु
  outw (cpu_to_le16 (data), dev->iobase + reg);
पूर्ण

अटल अंतरभूत u16 rd_regw (स्थिर hrz_dev * dev, अचिन्हित अक्षर reg) अणु
  वापस le16_to_cpu (inw (dev->iobase + reg));
पूर्ण

अटल अंतरभूत व्योम wrs_regb (स्थिर hrz_dev * dev, अचिन्हित अक्षर reg, व्योम * addr, u32 len) अणु
  outsb (dev->iobase + reg, addr, len);
पूर्ण

अटल अंतरभूत व्योम rds_regb (स्थिर hrz_dev * dev, अचिन्हित अक्षर reg, व्योम * addr, u32 len) अणु
  insb (dev->iobase + reg, addr, len);
पूर्ण

/* Read / Write to a given address in Horizon buffer memory.
   Interrupts must be disabled between the address रेजिस्टर and data
   port accesses as these must क्रमm an atomic operation. */
अटल अंतरभूत व्योम wr_mem (स्थिर hrz_dev * dev, HDW * addr, u32 data) अणु
  // wr_regl (dev, MEM_WR_ADDR_REG_OFF, (u32) addr);
  wr_regl (dev, MEM_WR_ADDR_REG_OFF, (addr - (HDW *) 0) * माप(HDW));
  wr_regl (dev, MEMORY_PORT_OFF, data);
पूर्ण

अटल अंतरभूत u32 rd_mem (स्थिर hrz_dev * dev, HDW * addr) अणु
  // wr_regl (dev, MEM_RD_ADDR_REG_OFF, (u32) addr);
  wr_regl (dev, MEM_RD_ADDR_REG_OFF, (addr - (HDW *) 0) * माप(HDW));
  वापस rd_regl (dev, MEMORY_PORT_OFF);
पूर्ण

अटल अंतरभूत व्योम wr_framer (स्थिर hrz_dev * dev, u32 addr, u32 data) अणु
  wr_regl (dev, MEM_WR_ADDR_REG_OFF, (u32) addr | 0x80000000);
  wr_regl (dev, MEMORY_PORT_OFF, data);
पूर्ण

अटल अंतरभूत u32 rd_framer (स्थिर hrz_dev * dev, u32 addr) अणु
  wr_regl (dev, MEM_RD_ADDR_REG_OFF, (u32) addr | 0x80000000);
  वापस rd_regl (dev, MEMORY_PORT_OFF);
पूर्ण

/********** specialised access functions **********/

/* RX */

अटल अंतरभूत व्योम FLUSH_RX_CHANNEL (hrz_dev * dev, u16 channel) अणु
  wr_regw (dev, RX_CHANNEL_PORT_OFF, FLUSH_CHANNEL | channel);
  वापस;
पूर्ण

अटल व्योम WAIT_FLUSH_RX_COMPLETE (hrz_dev * dev) अणु
  जबतक (rd_regw (dev, RX_CHANNEL_PORT_OFF) & FLUSH_CHANNEL)
    ;
  वापस;
पूर्ण

अटल अंतरभूत व्योम SELECT_RX_CHANNEL (hrz_dev * dev, u16 channel) अणु
  wr_regw (dev, RX_CHANNEL_PORT_OFF, channel);
  वापस;
पूर्ण

अटल व्योम WAIT_UPDATE_COMPLETE (hrz_dev * dev) अणु
  जबतक (rd_regw (dev, RX_CHANNEL_PORT_OFF) & RX_CHANNEL_UPDATE_IN_PROGRESS)
    ;
  वापस;
पूर्ण

/* TX */

अटल अंतरभूत व्योम SELECT_TX_CHANNEL (hrz_dev * dev, u16 tx_channel) अणु
  wr_regl (dev, TX_CHANNEL_PORT_OFF, tx_channel);
  वापस;
पूर्ण

/* Update or query one configuration parameter of a particular channel. */

अटल अंतरभूत व्योम update_tx_channel_config (hrz_dev * dev, लघु chan, u8 mode, u16 value) अणु
  wr_regw (dev, TX_CHANNEL_CONFIG_COMMAND_OFF,
	   chan * TX_CHANNEL_CONFIG_MULT | mode);
    wr_regw (dev, TX_CHANNEL_CONFIG_DATA_OFF, value);
    वापस;
पूर्ण

/********** dump functions **********/

अटल अंतरभूत व्योम dump_skb (अक्षर * prefix, अचिन्हित पूर्णांक vc, काष्ठा sk_buff * skb) अणु
#अगर_घोषित DEBUG_HORIZON
  अचिन्हित पूर्णांक i;
  अचिन्हित अक्षर * data = skb->data;
  PRINTDB (DBG_DATA, "%s(%u) ", prefix, vc);
  क्रम (i=0; i<skb->len && i < 256;i++)
    PRINTDM (DBG_DATA, "%02x ", data[i]);
  PRINTDE (DBG_DATA,"");
#अन्यथा
  (व्योम) prefix;
  (व्योम) vc;
  (व्योम) skb;
#पूर्ण_अगर
  वापस;
पूर्ण

अटल अंतरभूत व्योम dump_regs (hrz_dev * dev) अणु
#अगर_घोषित DEBUG_HORIZON
  PRINTD (DBG_REGS, "CONTROL 0: %#x", rd_regl (dev, CONTROL_0_REG));
  PRINTD (DBG_REGS, "RX CONFIG: %#x", rd_regw (dev, RX_CONFIG_OFF));
  PRINTD (DBG_REGS, "TX CONFIG: %#x", rd_regw (dev, TX_CONFIG_OFF));
  PRINTD (DBG_REGS, "TX STATUS: %#x", rd_regw (dev, TX_STATUS_OFF));
  PRINTD (DBG_REGS, "IRQ ENBLE: %#x", rd_regl (dev, INT_ENABLE_REG_OFF));
  PRINTD (DBG_REGS, "IRQ SORCE: %#x", rd_regl (dev, INT_SOURCE_REG_OFF));
#अन्यथा
  (व्योम) dev;
#पूर्ण_अगर
  वापस;
पूर्ण

अटल अंतरभूत व्योम dump_framer (hrz_dev * dev) अणु
#अगर_घोषित DEBUG_HORIZON
  अचिन्हित पूर्णांक i;
  PRINTDB (DBG_REGS, "framer registers:");
  क्रम (i = 0; i < 0x10; ++i)
    PRINTDM (DBG_REGS, " %02x", rd_framer (dev, i));
  PRINTDE (DBG_REGS,"");
#अन्यथा
  (व्योम) dev;
#पूर्ण_अगर
  वापस;
पूर्ण

/********** VPI/VCI <-> (RX) channel conversions **********/

/* RX channels are 10 bit पूर्णांकegers, these fns are quite paranoid */

अटल अंतरभूत पूर्णांक vpivci_to_channel (u16 * channel, स्थिर लघु vpi, स्थिर पूर्णांक vci) अणु
  अचिन्हित लघु vci_bits = 10 - vpi_bits;
  अगर (0 <= vpi && vpi < 1<<vpi_bits && 0 <= vci && vci < 1<<vci_bits) अणु
    *channel = vpi<<vci_bits | vci;
    वापस *channel ? 0 : -EINVAL;
  पूर्ण
  वापस -EINVAL;
पूर्ण

/********** decode RX queue entries **********/

अटल अंतरभूत u16 rx_q_entry_to_length (u32 x) अणु
  वापस x & RX_Q_ENTRY_LENGTH_MASK;
पूर्ण

अटल अंतरभूत u16 rx_q_entry_to_rx_channel (u32 x) अणु
  वापस (x>>RX_Q_ENTRY_CHANNEL_SHIFT) & RX_CHANNEL_MASK;
पूर्ण

/* Cell Transmit Rate Values
 *
 * the cell transmit rate (cells per sec) can be set to a variety of
 * dअगरferent values by specअगरying two parameters: a समयr preload from
 * 1 to 16 (stored as 0 to 15) and a घड़ी भागider (2 to the घातer of
 * an exponent from 0 to 14; the special value 15 disables the समयr).
 *
 * cellrate = baserate / (preload * 2^भागider)
 *
 * The maximum cell rate that can be specअगरied is thereक्रमe just the
 * base rate. Halving the preload is equivalent to adding 1 to the
 * भागider and so values 1 to 8 of the preload are redundant except
 * in the हाल of a maximal भागider (14).
 *
 * Given a desired cell rate, an algorithm to determine the preload
 * and भागider is:
 * 
 * a) x = baserate / cellrate, want p * 2^d = x (as far as possible)
 * b) अगर x > 16 * 2^14 then set p = 16, d = 14 (min rate), करोne
 *    अगर x <= 16 then set p = x, d = 0 (high rates), करोne
 * c) now have 16 < x <= 2^18, or 1 < x/16 <= 2^14 and we want to
 *    know n such that 2^(n-1) < x/16 <= 2^n, so slide a bit until
 *    we find the range (n will be between 1 and 14), set d = n
 * d) Also have 8 < x/2^n <= 16, so set p nearest x/2^n
 *
 * The algorithm used below is a minor variant of the above.
 *
 * The base rate is derived from the oscillator frequency (Hz) using a
 * fixed भागider:
 *
 * baserate = freq / 32 in the हाल of some Unknown Card
 * baserate = freq / 8  in the हाल of the Horizon        25
 * baserate = freq / 8  in the हाल of the Horizon Ultra 155
 *
 * The Horizon cards have oscillators and base rates as follows:
 *
 * Card               Oscillator  Base Rate
 * Unknown Card       33 MHz      1.03125 MHz (33 MHz = PCI freq)
 * Horizon        25  32 MHz      4       MHz
 * Horizon Ultra 155  40 MHz      5       MHz
 *
 * The following defines give the base rates in Hz. These were
 * previously a factor of 100 larger, no करोubt someone was using
 * cps*100.
 */

#घोषणा BR_UKN 1031250l
#घोषणा BR_HRZ 4000000l
#घोषणा BR_ULT 5000000l

// d is an exponent
#घोषणा CR_MIND 0
#घोषणा CR_MAXD 14

// p ranges from 1 to a घातer of 2
#घोषणा CR_MAXPEXP 4
 
अटल पूर्णांक make_rate (स्थिर hrz_dev * dev, u32 c, rounding r,
		      u16 * bits, अचिन्हित पूर्णांक * actual)
अणु
	// note: rounding the rate करोwn means rounding 'p' up
	स्थिर अचिन्हित दीर्घ br = test_bit(ultra, &dev->flags) ? BR_ULT : BR_HRZ;
  
	u32 भाग = CR_MIND;
	u32 pre;
  
	// br_exp and br_man are used to aव्योम overflowing (c*maxp*2^d) in
	// the tests below. We could think harder about exact possibilities
	// of failure...
  
	अचिन्हित दीर्घ br_man = br;
	अचिन्हित पूर्णांक br_exp = 0;
  
	PRINTD (DBG_QOS|DBG_FLOW, "make_rate b=%lu, c=%u, %s", br, c,
		r == round_up ? "up" : r == round_करोwn ? "down" : "nearest");
  
	// aव्योम भाग by zero
	अगर (!c) अणु
		PRINTD (DBG_QOS|DBG_ERR, "zero rate is not allowed!");
		वापस -EINVAL;
	पूर्ण
  
	जबतक (br_exp < CR_MAXPEXP + CR_MIND && (br_man % 2 == 0)) अणु
		br_man = br_man >> 1;
		++br_exp;
	पूर्ण
	// (br >>br_exp) <<br_exp == br and
	// br_exp <= CR_MAXPEXP+CR_MIND
  
	अगर (br_man <= (c << (CR_MAXPEXP+CR_MIND-br_exp))) अणु
		// Equivalent to: B <= (c << (MAXPEXP+MIND))
		// take care of rounding
		चयन (r) अणु
			हाल round_करोwn:
				pre = DIV_ROUND_UP(br, c<<भाग);
				// but p must be non-zero
				अगर (!pre)
					pre = 1;
				अवरोध;
			हाल round_nearest:
				pre = DIV_ROUND_CLOSEST(br, c<<भाग);
				// but p must be non-zero
				अगर (!pre)
					pre = 1;
				अवरोध;
			शेष:	/* round_up */
				pre = br/(c<<भाग);
				// but p must be non-zero
				अगर (!pre)
					वापस -EINVAL;
		पूर्ण
		PRINTD (DBG_QOS, "A: p=%u, d=%u", pre, भाग);
		जाओ got_it;
	पूर्ण
  
	// at this poपूर्णांक we have
	// d == MIND and (c << (MAXPEXP+MIND)) < B
	जबतक (भाग < CR_MAXD) अणु
		भाग++;
		अगर (br_man <= (c << (CR_MAXPEXP+भाग-br_exp))) अणु
			// Equivalent to: B <= (c << (MAXPEXP+d))
			// c << (MAXPEXP+d-1) < B <= c << (MAXPEXP+d)
			// 1 << (MAXPEXP-1) < B/2^d/c <= 1 << MAXPEXP
			// MAXP/2 < B/c2^d <= MAXP
			// take care of rounding
			चयन (r) अणु
				हाल round_करोwn:
					pre = DIV_ROUND_UP(br, c<<भाग);
					अवरोध;
				हाल round_nearest:
					pre = DIV_ROUND_CLOSEST(br, c<<भाग);
					अवरोध;
				शेष: /* round_up */
					pre = br/(c<<भाग);
			पूर्ण
			PRINTD (DBG_QOS, "B: p=%u, d=%u", pre, भाग);
			जाओ got_it;
		पूर्ण
	पूर्ण
	// at this poपूर्णांक we have
	// d == MAXD and (c << (MAXPEXP+MAXD)) < B
	// but we cannot go any higher
	// take care of rounding
	अगर (r == round_करोwn)
		वापस -EINVAL;
	pre = 1 << CR_MAXPEXP;
	PRINTD (DBG_QOS, "C: p=%u, d=%u", pre, भाग);
got_it:
	// paranoia
	अगर (भाग > CR_MAXD || (!pre) || pre > 1<<CR_MAXPEXP) अणु
		PRINTD (DBG_QOS, "set_cr internal failure: d=%u p=%u",
			भाग, pre);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (bits)
			*bits = (भाग<<CLOCK_SELECT_SHIFT) | (pre-1);
		अगर (actual) अणु
			*actual = DIV_ROUND_UP(br, pre<<भाग);
			PRINTD (DBG_QOS, "actual rate: %u", *actual);
		पूर्ण
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक make_rate_with_tolerance (स्थिर hrz_dev * dev, u32 c, rounding r, अचिन्हित पूर्णांक tol,
				     u16 * bit_pattern, अचिन्हित पूर्णांक * actual) अणु
  अचिन्हित पूर्णांक my_actual;
  
  PRINTD (DBG_QOS|DBG_FLOW, "make_rate_with_tolerance c=%u, %s, tol=%u",
	  c, (r == round_up) ? "up" : (r == round_करोwn) ? "down" : "nearest", tol);
  
  अगर (!actual)
    // actual rate is not वापसed
    actual = &my_actual;
  
  अगर (make_rate (dev, c, round_nearest, bit_pattern, actual))
    // should never happen as round_nearest always succeeds
    वापस -1;
  
  अगर (c - tol <= *actual && *actual <= c + tol)
    // within tolerance
    वापस 0;
  अन्यथा
    // पूर्णांकolerant, try rounding instead
    वापस make_rate (dev, c, r, bit_pattern, actual);
पूर्ण

/********** Listen on a VC **********/

अटल पूर्णांक hrz_खोलो_rx (hrz_dev * dev, u16 channel) अणु
  // is there any guarantee that we करोn't get two simulataneous
  // identical calls of this function from dअगरferent processes? yes
  // rate_lock
  अचिन्हित दीर्घ flags;
  u32 channel_type; // u16?
  
  u16 buf_ptr = RX_CHANNEL_IDLE;
  
  rx_ch_desc * rx_desc = &memmap->rx_descs[channel];
  
  PRINTD (DBG_FLOW, "hrz_open_rx %x", channel);
  
  spin_lock_irqsave (&dev->mem_lock, flags);
  channel_type = rd_mem (dev, &rx_desc->wr_buf_type) & BUFFER_PTR_MASK;
  spin_unlock_irqrestore (&dev->mem_lock, flags);
  
  // very serious error, should never occur
  अगर (channel_type != RX_CHANNEL_DISABLED) अणु
    PRINTD (DBG_ERR|DBG_VCC, "RX channel for VC already open");
    वापस -EBUSY; // clean up?
  पूर्ण
  
  // Give back spare buffer
  अगर (dev->noof_spare_buffers) अणु
    buf_ptr = dev->spare_buffers[--dev->noof_spare_buffers];
    PRINTD (DBG_VCC, "using a spare buffer: %u", buf_ptr);
    // should never occur
    अगर (buf_ptr == RX_CHANNEL_DISABLED || buf_ptr == RX_CHANNEL_IDLE) अणु
      // but easy to recover from
      PRINTD (DBG_ERR|DBG_VCC, "bad spare buffer pointer, using IDLE");
      buf_ptr = RX_CHANNEL_IDLE;
    पूर्ण
  पूर्ण अन्यथा अणु
    PRINTD (DBG_VCC, "using IDLE buffer pointer");
  पूर्ण
  
  // Channel is currently disabled so change its status to idle
  
  // करो we really need to save the flags again?
  spin_lock_irqsave (&dev->mem_lock, flags);
  
  wr_mem (dev, &rx_desc->wr_buf_type,
	  buf_ptr | CHANNEL_TYPE_AAL5 | FIRST_CELL_OF_AAL5_FRAME);
  अगर (buf_ptr != RX_CHANNEL_IDLE)
    wr_mem (dev, &rx_desc->rd_buf_type, buf_ptr);
  
  spin_unlock_irqrestore (&dev->mem_lock, flags);
  
  // rxer->rate = make_rate (qos->peak_cells);
  
  PRINTD (DBG_FLOW, "hrz_open_rx ok");
  
  वापस 0;
पूर्ण

#अगर 0
/********** change vc rate क्रम a given vc **********/

अटल व्योम hrz_change_vc_qos (ATM_RXER * rxer, MAAL_QOS * qos) अणु
  rxer->rate = make_rate (qos->peak_cells);
पूर्ण
#पूर्ण_अगर

/********** मुक्त an skb (as per ATM device driver करोcumentation) **********/

अटल व्योम hrz_kमुक्त_skb (काष्ठा sk_buff * skb) अणु
  अगर (ATM_SKB(skb)->vcc->pop) अणु
    ATM_SKB(skb)->vcc->pop (ATM_SKB(skb)->vcc, skb);
  पूर्ण अन्यथा अणु
    dev_kमुक्त_skb_any (skb);
  पूर्ण
पूर्ण

/********** cancel listen on a VC **********/

अटल व्योम hrz_बंद_rx (hrz_dev * dev, u16 vc) अणु
  अचिन्हित दीर्घ flags;
  
  u32 value;
  
  u32 r1, r2;
  
  rx_ch_desc * rx_desc = &memmap->rx_descs[vc];
  
  पूर्णांक was_idle = 0;
  
  spin_lock_irqsave (&dev->mem_lock, flags);
  value = rd_mem (dev, &rx_desc->wr_buf_type) & BUFFER_PTR_MASK;
  spin_unlock_irqrestore (&dev->mem_lock, flags);
  
  अगर (value == RX_CHANNEL_DISABLED) अणु
    // I suppose this could happen once we deal with _NONE traffic properly
    PRINTD (DBG_VCC, "closing VC: RX channel %u already disabled", vc);
    वापस;
  पूर्ण
  अगर (value == RX_CHANNEL_IDLE)
    was_idle = 1;
  
  spin_lock_irqsave (&dev->mem_lock, flags);
  
  क्रम (;;) अणु
    wr_mem (dev, &rx_desc->wr_buf_type, RX_CHANNEL_DISABLED);
    
    अगर ((rd_mem (dev, &rx_desc->wr_buf_type) & BUFFER_PTR_MASK) == RX_CHANNEL_DISABLED)
      अवरोध;
    
    was_idle = 0;
  पूर्ण
  
  अगर (was_idle) अणु
    spin_unlock_irqrestore (&dev->mem_lock, flags);
    वापस;
  पूर्ण
  
  WAIT_FLUSH_RX_COMPLETE(dev);
  
  // XXX Is this all really necessary? We can rely on the rx_data_av
  // handler to discard frames that reमुख्य queued क्रम delivery. If the
  // worry is that immediately reखोलोing the channel (perhaps by a
  // dअगरferent process) may cause some data to be mis-delivered then
  // there may still be a simpler solution (such as busy-रुकोing on
  // rx_busy once the channel is disabled or beक्रमe a new one is
  // खोलोed - करोes this leave any holes?). Arguably setting up and
  // tearing करोwn the TX and RX halves of each भव circuit could
  // most safely be करोne within ?x_busy रक्षित regions.
  
  // OK, current changes are that Simon's marker is disabled and we DO
  // look क्रम शून्य rxer अन्यथाwhere. The code here seems flush frames
  // and then remember the last dead cell beदीर्घing to the channel
  // just disabled - the cell माला_लो relinked at the next vc_खोलो.
  // However, when all VCs are बंदd or only a few खोलोed there are a
  // handful of buffers that are unusable.
  
  // Does anyone feel like करोcumenting spare_buffers properly?
  // Does anyone feel like fixing this in a nicer way?
  
  // Flush any data which is left in the channel
  क्रम (;;) अणु
    // Change the rx channel port to something dअगरferent to the RX
    // channel we are trying to बंद to क्रमce Horizon to flush the rx
    // channel पढ़ो and ग_लिखो poपूर्णांकers.
    
    u16 other = vc^(RX_CHANS/2);
    
    SELECT_RX_CHANNEL (dev, other);
    WAIT_UPDATE_COMPLETE (dev);
    
    r1 = rd_mem (dev, &rx_desc->rd_buf_type);
    
    // Select this RX channel. Flush करोesn't seem to work unless we
    // select an RX channel beक्रमe hand
    
    SELECT_RX_CHANNEL (dev, vc);
    WAIT_UPDATE_COMPLETE (dev);
    
    // Attempt to flush a frame on this RX channel
    
    FLUSH_RX_CHANNEL (dev, vc);
    WAIT_FLUSH_RX_COMPLETE (dev);
    
    // Force Horizon to flush rx channel पढ़ो and ग_लिखो poपूर्णांकers as beक्रमe
    
    SELECT_RX_CHANNEL (dev, other);
    WAIT_UPDATE_COMPLETE (dev);
    
    r2 = rd_mem (dev, &rx_desc->rd_buf_type);
    
    PRINTD (DBG_VCC|DBG_RX, "r1 = %u, r2 = %u", r1, r2);
    
    अगर (r1 == r2) अणु
      dev->spare_buffers[dev->noof_spare_buffers++] = (u16)r1;
      अवरोध;
    पूर्ण
  पूर्ण
  
#अगर 0
  अणु
    rx_q_entry * wr_ptr = &memmap->rx_q_entries[rd_regw (dev, RX_QUEUE_WR_PTR_OFF)];
    rx_q_entry * rd_ptr = dev->rx_q_entry;
    
    PRINTD (DBG_VCC|DBG_RX, "rd_ptr = %u, wr_ptr = %u", rd_ptr, wr_ptr);
    
    जबतक (rd_ptr != wr_ptr) अणु
      u32 x = rd_mem (dev, (HDW *) rd_ptr);
      
      अगर (vc == rx_q_entry_to_rx_channel (x)) अणु
	x |= SIMONS_DODGEY_MARKER;
	
	PRINTD (DBG_RX|DBG_VCC|DBG_WARN, "marking a frame as dodgey");
	
	wr_mem (dev, (HDW *) rd_ptr, x);
      पूर्ण
      
      अगर (rd_ptr == dev->rx_q_wrap)
	rd_ptr = dev->rx_q_reset;
      अन्यथा
	rd_ptr++;
    पूर्ण
  पूर्ण
#पूर्ण_अगर
  
  spin_unlock_irqrestore (&dev->mem_lock, flags);
  
  वापस;
पूर्ण

/********** schedule RX transfers **********/

// Note on tail recursion: a GCC developer said that it is not likely
// to be fixed soon, so करो not define TAILRECUSRIONWORKS unless you
// are sure it करोes as you may otherwise overflow the kernel stack.

// giving this fn a वापस value would help GCC, allegedly

अटल व्योम rx_schedule (hrz_dev * dev, पूर्णांक irq) अणु
  अचिन्हित पूर्णांक rx_bytes;
  
  पूर्णांक pio_instead = 0;
#अगर_अघोषित TAILRECURSIONWORKS
  pio_instead = 1;
  जबतक (pio_instead) अणु
#पूर्ण_अगर
    // bytes रुकोing क्रम RX transfer
    rx_bytes = dev->rx_bytes;
    
#अगर 0
    spin_count = 0;
    जबतक (rd_regl (dev, MASTER_RX_COUNT_REG_OFF)) अणु
      PRINTD (DBG_RX|DBG_WARN, "RX error: other PCI Bus Master RX still in progress!");
      अगर (++spin_count > 10) अणु
	PRINTD (DBG_RX|DBG_ERR, "spun out waiting PCI Bus Master RX completion");
	wr_regl (dev, MASTER_RX_COUNT_REG_OFF, 0);
	clear_bit (rx_busy, &dev->flags);
	hrz_kमुक्त_skb (dev->rx_skb);
	वापस;
      पूर्ण
    पूर्ण
#पूर्ण_अगर
    
    // this code follows the TX code but (at the moment) there is only
    // one region - the skb itself. I करोn't know अगर this will change,
    // but it करोesn't hurt to have the code here, disabled.
    
    अगर (rx_bytes) अणु
      // start next transfer within same region
      अगर (rx_bytes <= MAX_PIO_COUNT) अणु
	PRINTD (DBG_RX|DBG_BUS, "(pio)");
	pio_instead = 1;
      पूर्ण
      अगर (rx_bytes <= MAX_TRANSFER_COUNT) अणु
	PRINTD (DBG_RX|DBG_BUS, "(simple or last multi)");
	dev->rx_bytes = 0;
      पूर्ण अन्यथा अणु
	PRINTD (DBG_RX|DBG_BUS, "(continuing multi)");
	dev->rx_bytes = rx_bytes - MAX_TRANSFER_COUNT;
	rx_bytes = MAX_TRANSFER_COUNT;
      पूर्ण
    पूर्ण अन्यथा अणु
      // rx_bytes == 0 -- we're between regions
      // regions reमुख्यing to transfer
#अगर 0
      अचिन्हित पूर्णांक rx_regions = dev->rx_regions;
#अन्यथा
      अचिन्हित पूर्णांक rx_regions = 0;
#पूर्ण_अगर
      
      अगर (rx_regions) अणु
#अगर 0
	// start a new region
	dev->rx_addr = dev->rx_iovec->iov_base;
	rx_bytes = dev->rx_iovec->iov_len;
	++dev->rx_iovec;
	dev->rx_regions = rx_regions - 1;
	
	अगर (rx_bytes <= MAX_PIO_COUNT) अणु
	  PRINTD (DBG_RX|DBG_BUS, "(pio)");
	  pio_instead = 1;
	पूर्ण
	अगर (rx_bytes <= MAX_TRANSFER_COUNT) अणु
	  PRINTD (DBG_RX|DBG_BUS, "(full region)");
	  dev->rx_bytes = 0;
	पूर्ण अन्यथा अणु
	  PRINTD (DBG_RX|DBG_BUS, "(start multi region)");
	  dev->rx_bytes = rx_bytes - MAX_TRANSFER_COUNT;
	  rx_bytes = MAX_TRANSFER_COUNT;
	पूर्ण
#पूर्ण_अगर
      पूर्ण अन्यथा अणु
	// rx_regions == 0
	// that's all folks - end of frame
	काष्ठा sk_buff * skb = dev->rx_skb;
	// dev->rx_iovec = 0;
	
	FLUSH_RX_CHANNEL (dev, dev->rx_channel);
	
	dump_skb ("<<<", dev->rx_channel, skb);
	
	PRINTD (DBG_RX|DBG_SKB, "push %p %u", skb->data, skb->len);
	
	अणु
	  काष्ठा aपंचांग_vcc * vcc = ATM_SKB(skb)->vcc;
	  // VC layer stats
	  atomic_inc(&vcc->stats->rx);
	  __net_बारtamp(skb);
	  // end of our responsibility
	  vcc->push (vcc, skb);
	पूर्ण
      पूर्ण
    पूर्ण
    
    // note: writing RX_COUNT clears any पूर्णांकerrupt condition
    अगर (rx_bytes) अणु
      अगर (pio_instead) अणु
	अगर (irq)
	  wr_regl (dev, MASTER_RX_COUNT_REG_OFF, 0);
	rds_regb (dev, DATA_PORT_OFF, dev->rx_addr, rx_bytes);
      पूर्ण अन्यथा अणु
	wr_regl (dev, MASTER_RX_ADDR_REG_OFF, virt_to_bus (dev->rx_addr));
	wr_regl (dev, MASTER_RX_COUNT_REG_OFF, rx_bytes);
      पूर्ण
      dev->rx_addr += rx_bytes;
    पूर्ण अन्यथा अणु
      अगर (irq)
	wr_regl (dev, MASTER_RX_COUNT_REG_OFF, 0);
      // allow another RX thपढ़ो to start
      YELLOW_LED_ON(dev);
      clear_bit (rx_busy, &dev->flags);
      PRINTD (DBG_RX, "cleared rx_busy for dev %p", dev);
    पूर्ण
    
#अगर_घोषित TAILRECURSIONWORKS
    // and we all bless optimised tail calls
    अगर (pio_instead)
      वापस rx_schedule (dev, 0);
    वापस;
#अन्यथा
    // grrrrrrr!
    irq = 0;
  पूर्ण
  वापस;
#पूर्ण_अगर
पूर्ण

/********** handle RX bus master complete events **********/

अटल व्योम rx_bus_master_complete_handler (hrz_dev * dev) अणु
  अगर (test_bit (rx_busy, &dev->flags)) अणु
    rx_schedule (dev, 1);
  पूर्ण अन्यथा अणु
    PRINTD (DBG_RX|DBG_ERR, "unexpected RX bus master completion");
    // clear पूर्णांकerrupt condition on adapter
    wr_regl (dev, MASTER_RX_COUNT_REG_OFF, 0);
  पूर्ण
  वापस;
पूर्ण

/********** (queue to) become the next TX thपढ़ो **********/

अटल पूर्णांक tx_hold (hrz_dev * dev) अणु
  PRINTD (DBG_TX, "sleeping at tx lock %p %lu", dev, dev->flags);
  रुको_event_पूर्णांकerruptible(dev->tx_queue, (!test_and_set_bit(tx_busy, &dev->flags)));
  PRINTD (DBG_TX, "woken at tx lock %p %lu", dev, dev->flags);
  अगर (संकेत_pending (current))
    वापस -1;
  PRINTD (DBG_TX, "set tx_busy for dev %p", dev);
  वापस 0;
पूर्ण

/********** allow another TX thपढ़ो to start **********/

अटल अंतरभूत व्योम tx_release (hrz_dev * dev) अणु
  clear_bit (tx_busy, &dev->flags);
  PRINTD (DBG_TX, "cleared tx_busy for dev %p", dev);
  wake_up_पूर्णांकerruptible (&dev->tx_queue);
पूर्ण

/********** schedule TX transfers **********/

अटल व्योम tx_schedule (hrz_dev * स्थिर dev, पूर्णांक irq) अणु
  अचिन्हित पूर्णांक tx_bytes;
  
  पूर्णांक append_desc = 0;
  
  पूर्णांक pio_instead = 0;
#अगर_अघोषित TAILRECURSIONWORKS
  pio_instead = 1;
  जबतक (pio_instead) अणु
#पूर्ण_अगर
    // bytes in current region रुकोing क्रम TX transfer
    tx_bytes = dev->tx_bytes;
    
#अगर 0
    spin_count = 0;
    जबतक (rd_regl (dev, MASTER_TX_COUNT_REG_OFF)) अणु
      PRINTD (DBG_TX|DBG_WARN, "TX error: other PCI Bus Master TX still in progress!");
      अगर (++spin_count > 10) अणु
	PRINTD (DBG_TX|DBG_ERR, "spun out waiting PCI Bus Master TX completion");
	wr_regl (dev, MASTER_TX_COUNT_REG_OFF, 0);
	tx_release (dev);
	hrz_kमुक्त_skb (dev->tx_skb);
	वापस;
      पूर्ण
    पूर्ण
#पूर्ण_अगर
    
    अगर (tx_bytes) अणु
      // start next transfer within same region
      अगर (!test_bit (ultra, &dev->flags) || tx_bytes <= MAX_PIO_COUNT) अणु
	PRINTD (DBG_TX|DBG_BUS, "(pio)");
	pio_instead = 1;
      पूर्ण
      अगर (tx_bytes <= MAX_TRANSFER_COUNT) अणु
	PRINTD (DBG_TX|DBG_BUS, "(simple or last multi)");
	अगर (!dev->tx_iovec) अणु
	  // end of last region
	  append_desc = 1;
	पूर्ण
	dev->tx_bytes = 0;
      पूर्ण अन्यथा अणु
	PRINTD (DBG_TX|DBG_BUS, "(continuing multi)");
	dev->tx_bytes = tx_bytes - MAX_TRANSFER_COUNT;
	tx_bytes = MAX_TRANSFER_COUNT;
      पूर्ण
    पूर्ण अन्यथा अणु
      // tx_bytes == 0 -- we're between regions
      // regions reमुख्यing to transfer
      अचिन्हित पूर्णांक tx_regions = dev->tx_regions;
      
      अगर (tx_regions) अणु
	// start a new region
	dev->tx_addr = dev->tx_iovec->iov_base;
	tx_bytes = dev->tx_iovec->iov_len;
	++dev->tx_iovec;
	dev->tx_regions = tx_regions - 1;
	
	अगर (!test_bit (ultra, &dev->flags) || tx_bytes <= MAX_PIO_COUNT) अणु
	  PRINTD (DBG_TX|DBG_BUS, "(pio)");
	  pio_instead = 1;
	पूर्ण
	अगर (tx_bytes <= MAX_TRANSFER_COUNT) अणु
	  PRINTD (DBG_TX|DBG_BUS, "(full region)");
	  dev->tx_bytes = 0;
	पूर्ण अन्यथा अणु
	  PRINTD (DBG_TX|DBG_BUS, "(start multi region)");
	  dev->tx_bytes = tx_bytes - MAX_TRANSFER_COUNT;
	  tx_bytes = MAX_TRANSFER_COUNT;
	पूर्ण
      पूर्ण अन्यथा अणु
	// tx_regions == 0
	// that's all folks - end of frame
	काष्ठा sk_buff * skb = dev->tx_skb;
	dev->tx_iovec = शून्य;
	
	// VC layer stats
	atomic_inc(&ATM_SKB(skb)->vcc->stats->tx);
	
	// मुक्त the skb
	hrz_kमुक्त_skb (skb);
      पूर्ण
    पूर्ण
    
    // note: writing TX_COUNT clears any पूर्णांकerrupt condition
    अगर (tx_bytes) अणु
      अगर (pio_instead) अणु
	अगर (irq)
	  wr_regl (dev, MASTER_TX_COUNT_REG_OFF, 0);
	wrs_regb (dev, DATA_PORT_OFF, dev->tx_addr, tx_bytes);
	अगर (append_desc)
	  wr_regl (dev, TX_DESCRIPTOR_PORT_OFF, cpu_to_be32 (dev->tx_skb->len));
      पूर्ण अन्यथा अणु
	wr_regl (dev, MASTER_TX_ADDR_REG_OFF, virt_to_bus (dev->tx_addr));
	अगर (append_desc)
	  wr_regl (dev, TX_DESCRIPTOR_REG_OFF, cpu_to_be32 (dev->tx_skb->len));
	wr_regl (dev, MASTER_TX_COUNT_REG_OFF,
		 append_desc
		 ? tx_bytes | MASTER_TX_AUTO_APPEND_DESC
		 : tx_bytes);
      पूर्ण
      dev->tx_addr += tx_bytes;
    पूर्ण अन्यथा अणु
      अगर (irq)
	wr_regl (dev, MASTER_TX_COUNT_REG_OFF, 0);
      YELLOW_LED_ON(dev);
      tx_release (dev);
    पूर्ण
    
#अगर_घोषित TAILRECURSIONWORKS
    // and we all bless optimised tail calls
    अगर (pio_instead)
      वापस tx_schedule (dev, 0);
    वापस;
#अन्यथा
    // grrrrrrr!
    irq = 0;
  पूर्ण
  वापस;
#पूर्ण_अगर
पूर्ण

/********** handle TX bus master complete events **********/

अटल व्योम tx_bus_master_complete_handler (hrz_dev * dev) अणु
  अगर (test_bit (tx_busy, &dev->flags)) अणु
    tx_schedule (dev, 1);
  पूर्ण अन्यथा अणु
    PRINTD (DBG_TX|DBG_ERR, "unexpected TX bus master completion");
    // clear पूर्णांकerrupt condition on adapter
    wr_regl (dev, MASTER_TX_COUNT_REG_OFF, 0);
  पूर्ण
  वापस;
पूर्ण

/********** move RX Q poपूर्णांकer to next item in circular buffer **********/

// called only from IRQ sub-handler
अटल u32 rx_queue_entry_next (hrz_dev * dev) अणु
  u32 rx_queue_entry;
  spin_lock (&dev->mem_lock);
  rx_queue_entry = rd_mem (dev, &dev->rx_q_entry->entry);
  अगर (dev->rx_q_entry == dev->rx_q_wrap)
    dev->rx_q_entry = dev->rx_q_reset;
  अन्यथा
    dev->rx_q_entry++;
  wr_regw (dev, RX_QUEUE_RD_PTR_OFF, dev->rx_q_entry - dev->rx_q_reset);
  spin_unlock (&dev->mem_lock);
  वापस rx_queue_entry;
पूर्ण

/********** handle RX data received by device **********/

// called from IRQ handler
अटल व्योम rx_data_av_handler (hrz_dev * dev) अणु
  u32 rx_queue_entry;
  u32 rx_queue_entry_flags;
  u16 rx_len;
  u16 rx_channel;
  
  PRINTD (DBG_FLOW, "hrz_data_av_handler");
  
  // try to grab rx lock (not possible during RX bus mastering)
  अगर (test_and_set_bit (rx_busy, &dev->flags)) अणु
    PRINTD (DBG_RX, "locked out of rx lock");
    वापस;
  पूर्ण
  PRINTD (DBG_RX, "set rx_busy for dev %p", dev);
  // lock is cleared अगर we fail now, o/w after bus master completion
  
  YELLOW_LED_OFF(dev);
  
  rx_queue_entry = rx_queue_entry_next (dev);
  
  rx_len = rx_q_entry_to_length (rx_queue_entry);
  rx_channel = rx_q_entry_to_rx_channel (rx_queue_entry);
  
  WAIT_FLUSH_RX_COMPLETE (dev);
  
  SELECT_RX_CHANNEL (dev, rx_channel);
  
  PRINTD (DBG_RX, "rx_queue_entry is: %#x", rx_queue_entry);
  rx_queue_entry_flags = rx_queue_entry & (RX_CRC_32_OK|RX_COMPLETE_FRAME|SIMONS_DODGEY_MARKER);
  
  अगर (!rx_len) अणु
    // (at least) bus-mastering अवरोधs अगर we try to handle a
    // zero-length frame, besides AAL5 करोes not support them
    PRINTK (KERN_ERR, "zero-length frame!");
    rx_queue_entry_flags &= ~RX_COMPLETE_FRAME;
  पूर्ण
  
  अगर (rx_queue_entry_flags & SIMONS_DODGEY_MARKER) अणु
    PRINTD (DBG_RX|DBG_ERR, "Simon's marker detected!");
  पूर्ण
  अगर (rx_queue_entry_flags == (RX_CRC_32_OK | RX_COMPLETE_FRAME)) अणु
    काष्ठा aपंचांग_vcc * aपंचांग_vcc;
    
    PRINTD (DBG_RX, "got a frame on rx_channel %x len %u", rx_channel, rx_len);
    
    aपंचांग_vcc = dev->rxer[rx_channel];
    // अगर no vcc is asचिन्हित to this channel, we should drop the frame
    // (is this what SIMONS etc. was trying to achieve?)
    
    अगर (aपंचांग_vcc) अणु
      
      अगर (aपंचांग_vcc->qos.rxtp.traffic_class != ATM_NONE) अणु
	
	अगर (rx_len <= aपंचांग_vcc->qos.rxtp.max_sdu) अणु
	    
	  काष्ठा sk_buff * skb = aपंचांग_alloc_अक्षरge (aपंचांग_vcc, rx_len, GFP_ATOMIC);
	  अगर (skb) अणु
	    // remember this so we can push it later
	    dev->rx_skb = skb;
	    // remember this so we can flush it later
	    dev->rx_channel = rx_channel;
	    
	    // prepare socket buffer
	    skb_put (skb, rx_len);
	    ATM_SKB(skb)->vcc = aपंचांग_vcc;
	    
	    // simple transfer
	    // dev->rx_regions = 0;
	    // dev->rx_iovec = 0;
	    dev->rx_bytes = rx_len;
	    dev->rx_addr = skb->data;
	    PRINTD (DBG_RX, "RX start simple transfer (addr %p, len %d)",
		    skb->data, rx_len);
	    
	    // करो the business
	    rx_schedule (dev, 0);
	    वापस;
	    
	  पूर्ण अन्यथा अणु
	    PRINTD (DBG_SKB|DBG_WARN, "failed to get skb");
	  पूर्ण
	  
	पूर्ण अन्यथा अणु
	  PRINTK (KERN_INFO, "frame received on TX-only VC %x", rx_channel);
	  // करो we count this?
	पूर्ण
	
      पूर्ण अन्यथा अणु
	PRINTK (KERN_WARNING, "dropped over-size frame");
	// करो we count this?
      पूर्ण
      
    पूर्ण अन्यथा अणु
      PRINTD (DBG_WARN|DBG_VCC|DBG_RX, "no VCC for this frame (VC closed)");
      // करो we count this?
    पूर्ण
    
  पूर्ण अन्यथा अणु
    // Wait update complete ? SPONG
  पूर्ण
  
  // RX was पातed
  YELLOW_LED_ON(dev);
  
  FLUSH_RX_CHANNEL (dev,rx_channel);
  clear_bit (rx_busy, &dev->flags);
  
  वापस;
पूर्ण

/********** पूर्णांकerrupt handler **********/

अटल irqवापस_t पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *dev_id)
अणु
  hrz_dev *dev = dev_id;
  u32 पूर्णांक_source;
  अचिन्हित पूर्णांक irq_ok;
  
  PRINTD (DBG_FLOW, "interrupt_handler: %p", dev_id);
  
  // definitely क्रम us
  irq_ok = 0;
  जबतक ((पूर्णांक_source = rd_regl (dev, INT_SOURCE_REG_OFF)
	  & INTERESTING_INTERRUPTS)) अणु
    // In the पूर्णांकerests of fairness, the handlers below are
    // called in sequence and without immediate वापस to the head of
    // the जबतक loop. This is only of issue क्रम slow hosts (or when
    // debugging messages are on). Really slow hosts may find a fast
    // sender keeps them permanently in the IRQ handler. :(
    
    // (only an issue क्रम slow hosts) RX completion goes beक्रमe
    // rx_data_av as the क्रमmer implies rx_busy and so the latter
    // would just पात. If it reschedules another transfer
    // (continuing the same frame) then it will not clear rx_busy.
    
    // (only an issue क्रम slow hosts) TX completion goes beक्रमe RX
    // data available as it is a much लघुer routine - there is the
    // chance that any further transfers it schedules will be complete
    // by the समय of the वापस to the head of the जबतक loop
    
    अगर (पूर्णांक_source & RX_BUS_MASTER_COMPLETE) अणु
      ++irq_ok;
      PRINTD (DBG_IRQ|DBG_BUS|DBG_RX, "rx_bus_master_complete asserted");
      rx_bus_master_complete_handler (dev);
    पूर्ण
    अगर (पूर्णांक_source & TX_BUS_MASTER_COMPLETE) अणु
      ++irq_ok;
      PRINTD (DBG_IRQ|DBG_BUS|DBG_TX, "tx_bus_master_complete asserted");
      tx_bus_master_complete_handler (dev);
    पूर्ण
    अगर (पूर्णांक_source & RX_DATA_AV) अणु
      ++irq_ok;
      PRINTD (DBG_IRQ|DBG_RX, "rx_data_av asserted");
      rx_data_av_handler (dev);
    पूर्ण
  पूर्ण
  अगर (irq_ok) अणु
    PRINTD (DBG_IRQ, "work done: %u", irq_ok);
  पूर्ण अन्यथा अणु
    PRINTD (DBG_IRQ|DBG_WARN, "spurious interrupt source: %#x", पूर्णांक_source);
  पूर्ण
  
  PRINTD (DBG_IRQ|DBG_FLOW, "interrupt_handler done: %p", dev_id);
  अगर (irq_ok)
	वापस IRQ_HANDLED;
  वापस IRQ_NONE;
पूर्ण

/********** housekeeping **********/

अटल व्योम करो_housekeeping (काष्ठा समयr_list *t) अणु
  // just stats at the moment
  hrz_dev * dev = from_समयr(dev, t, housekeeping);

  // collect device-specअगरic (not driver/aपंचांग-linux) stats here
  dev->tx_cell_count += rd_regw (dev, TX_CELL_COUNT_OFF);
  dev->rx_cell_count += rd_regw (dev, RX_CELL_COUNT_OFF);
  dev->hec_error_count += rd_regw (dev, HEC_ERROR_COUNT_OFF);
  dev->unasचिन्हित_cell_count += rd_regw (dev, UNASSIGNED_CELL_COUNT_OFF);

  mod_समयr (&dev->housekeeping, jअगरfies + HZ/10);

  वापस;
पूर्ण

/********** find an idle channel क्रम TX and set it up **********/

// called with tx_busy set
अटल लघु setup_idle_tx_channel (hrz_dev * dev, hrz_vcc * vcc) अणु
  अचिन्हित लघु idle_channels;
  लघु tx_channel = -1;
  अचिन्हित पूर्णांक spin_count;
  PRINTD (DBG_FLOW|DBG_TX, "setup_idle_tx_channel %p", dev);
  
  // better would be to fail immediately, the caller can then decide whether
  // to रुको or drop (depending on whether this is UBR etc.)
  spin_count = 0;
  जबतक (!(idle_channels = rd_regw (dev, TX_STATUS_OFF) & IDLE_CHANNELS_MASK)) अणु
    PRINTD (DBG_TX|DBG_WARN, "waiting for idle TX channel");
    // delay a bit here
    अगर (++spin_count > 100) अणु
      PRINTD (DBG_TX|DBG_ERR, "spun out waiting for idle TX channel");
      वापस -EBUSY;
    पूर्ण
  पूर्ण
  
  // got an idle channel
  अणु
    // tx_idle ensures we look क्रम idle channels in RR order
    पूर्णांक chan = dev->tx_idle;
    
    पूर्णांक keep_going = 1;
    जबतक (keep_going) अणु
      अगर (idle_channels & (1<<chan)) अणु
	tx_channel = chan;
	keep_going = 0;
      पूर्ण
      ++chan;
      अगर (chan == TX_CHANS)
	chan = 0;
    पूर्ण
    
    dev->tx_idle = chan;
  पूर्ण
  
  // set up the channel we found
  अणु
    // Initialise the cell header in the transmit channel descriptor
    // a.k.a. prepare the channel and remember that we have करोne so.
    
    tx_ch_desc * tx_desc = &memmap->tx_descs[tx_channel];
    u32 rd_ptr;
    u32 wr_ptr;
    u16 channel = vcc->channel;
    
    अचिन्हित दीर्घ flags;
    spin_lock_irqsave (&dev->mem_lock, flags);
    
    // Update the transmit channel record.
    dev->tx_channel_record[tx_channel] = channel;
    
    // xBR channel
    update_tx_channel_config (dev, tx_channel, RATE_TYPE_ACCESS,
			      vcc->tx_xbr_bits);
    
    // Update the PCR counter preload value etc.
    update_tx_channel_config (dev, tx_channel, PCR_TIMER_ACCESS,
			      vcc->tx_pcr_bits);

#अगर 0
    अगर (vcc->tx_xbr_bits == VBR_RATE_TYPE) अणु
      // SCR समयr
      update_tx_channel_config (dev, tx_channel, SCR_TIMER_ACCESS,
				vcc->tx_scr_bits);
      
      // Bucket size...
      update_tx_channel_config (dev, tx_channel, BUCKET_CAPACITY_ACCESS,
				vcc->tx_bucket_bits);
      
      // ... and fullness
      update_tx_channel_config (dev, tx_channel, BUCKET_FULLNESS_ACCESS,
				vcc->tx_bucket_bits);
    पूर्ण
#पूर्ण_अगर

    // Initialise the पढ़ो and ग_लिखो buffer poपूर्णांकers
    rd_ptr = rd_mem (dev, &tx_desc->rd_buf_type) & BUFFER_PTR_MASK;
    wr_ptr = rd_mem (dev, &tx_desc->wr_buf_type) & BUFFER_PTR_MASK;
    
    // idle TX channels should have identical poपूर्णांकers
    अगर (rd_ptr != wr_ptr) अणु
      PRINTD (DBG_TX|DBG_ERR, "TX buffer pointers are broken!");
      // spin_unlock... वापस -E...
      // I wonder अगर gcc would get rid of one of the poपूर्णांकer aliases
    पूर्ण
    PRINTD (DBG_TX, "TX buffer pointers are: rd %x, wr %x.",
	    rd_ptr, wr_ptr);
    
    चयन (vcc->aal) अणु
      हाल aal0:
	PRINTD (DBG_QOS|DBG_TX, "tx_channel: aal0");
	rd_ptr |= CHANNEL_TYPE_RAW_CELLS;
	wr_ptr |= CHANNEL_TYPE_RAW_CELLS;
	अवरोध;
      हाल aal34:
	PRINTD (DBG_QOS|DBG_TX, "tx_channel: aal34");
	rd_ptr |= CHANNEL_TYPE_AAL3_4;
	wr_ptr |= CHANNEL_TYPE_AAL3_4;
	अवरोध;
      हाल aal5:
	rd_ptr |= CHANNEL_TYPE_AAL5;
	wr_ptr |= CHANNEL_TYPE_AAL5;
	// Initialise the CRC
	wr_mem (dev, &tx_desc->partial_crc, INITIAL_CRC);
	अवरोध;
    पूर्ण
    
    wr_mem (dev, &tx_desc->rd_buf_type, rd_ptr);
    wr_mem (dev, &tx_desc->wr_buf_type, wr_ptr);
    
    // Write the Cell Header
    // Payload Type, CLP and GFC would go here अगर non-zero
    wr_mem (dev, &tx_desc->cell_header, channel);
    
    spin_unlock_irqrestore (&dev->mem_lock, flags);
  पूर्ण
  
  वापस tx_channel;
पूर्ण

/********** send a frame **********/

अटल पूर्णांक hrz_send (काष्ठा aपंचांग_vcc * aपंचांग_vcc, काष्ठा sk_buff * skb) अणु
  अचिन्हित पूर्णांक spin_count;
  पूर्णांक मुक्त_buffers;
  hrz_dev * dev = HRZ_DEV(aपंचांग_vcc->dev);
  hrz_vcc * vcc = HRZ_VCC(aपंचांग_vcc);
  u16 channel = vcc->channel;
  
  u32 buffers_required;
  
  /* चिन्हित क्रम error वापस */
  लघु tx_channel;
  
  PRINTD (DBG_FLOW|DBG_TX, "hrz_send vc %x data %p len %u",
	  channel, skb->data, skb->len);
  
  dump_skb (">>>", channel, skb);
  
  अगर (aपंचांग_vcc->qos.txtp.traffic_class == ATM_NONE) अणु
    PRINTK (KERN_ERR, "attempt to send on RX-only VC %x", channel);
    hrz_kमुक्त_skb (skb);
    वापस -EIO;
  पूर्ण
  
  // करोn't understand this
  ATM_SKB(skb)->vcc = aपंचांग_vcc;
  
  अगर (skb->len > aपंचांग_vcc->qos.txtp.max_sdu) अणु
    PRINTK (KERN_ERR, "sk_buff length greater than agreed max_sdu, dropping...");
    hrz_kमुक्त_skb (skb);
    वापस -EIO;
  पूर्ण
  
  अगर (!channel) अणु
    PRINTD (DBG_ERR|DBG_TX, "attempt to transmit on zero (rx_)channel");
    hrz_kमुक्त_skb (skb);
    वापस -EIO;
  पूर्ण
  
#अगर 0
  अणु
    // where would be a better place क्रम this? housekeeping?
    u16 status;
    pci_पढ़ो_config_word (dev->pci_dev, PCI_STATUS, &status);
    अगर (status & PCI_STATUS_REC_MASTER_ABORT) अणु
      PRINTD (DBG_BUS|DBG_ERR, "Clearing PCI Master Abort (and cleaning up)");
      status &= ~PCI_STATUS_REC_MASTER_ABORT;
      pci_ग_लिखो_config_word (dev->pci_dev, PCI_STATUS, status);
      अगर (test_bit (tx_busy, &dev->flags)) अणु
	hrz_kमुक्त_skb (dev->tx_skb);
	tx_release (dev);
      पूर्ण
    पूर्ण
  पूर्ण
#पूर्ण_अगर
  
#अगर_घोषित DEBUG_HORIZON
  /* wey-hey! */
  अगर (channel == 1023) अणु
    अचिन्हित पूर्णांक i;
    अचिन्हित लघु d = 0;
    अक्षर * s = skb->data;
    अगर (*s++ == 'D') अणु
	क्रम (i = 0; i < 4; ++i)
		d = (d << 4) | hex_to_bin(*s++);
      PRINTK (KERN_INFO, "debug bitmap is now %hx", debug = d);
    पूर्ण
  पूर्ण
#पूर्ण_अगर
  
  // रुको until TX is मुक्त and grab lock
  अगर (tx_hold (dev)) अणु
    hrz_kमुक्त_skb (skb);
    वापस -ERESTARTSYS;
  पूर्ण
 
  // Wait क्रम enough space to be available in transmit buffer memory.
  
  // should be number of cells needed + 2 (according to hardware करोcs)
  // = ((framelen+8)+47) / 48 + 2
  // = (framelen+7) / 48 + 3, hmm... faster to put addition inside XXX
  buffers_required = (skb->len+(ATM_AAL5_TRAILER-1)) / ATM_CELL_PAYLOAD + 3;
  
  // replace with समयr and sleep, add dev->tx_buffers_queue (max 1 entry)
  spin_count = 0;
  जबतक ((मुक्त_buffers = rd_regw (dev, TX_FREE_BUFFER_COUNT_OFF)) < buffers_required) अणु
    PRINTD (DBG_TX, "waiting for free TX buffers, got %d of %d",
	    मुक्त_buffers, buffers_required);
    // what is the appropriate delay? implement a समयout? (depending on line speed?)
    // mdelay (1);
    // what happens अगर we समाप्त (current_pid, SIGKILL) ?
    schedule();
    अगर (++spin_count > 1000) अणु
      PRINTD (DBG_TX|DBG_ERR, "spun out waiting for tx buffers, got %d of %d",
	      मुक्त_buffers, buffers_required);
      tx_release (dev);
      hrz_kमुक्त_skb (skb);
      वापस -ERESTARTSYS;
    पूर्ण
  पूर्ण
  
  // Select a channel to transmit the frame on.
  अगर (channel == dev->last_vc) अणु
    PRINTD (DBG_TX, "last vc hack: hit");
    tx_channel = dev->tx_last;
  पूर्ण अन्यथा अणु
    PRINTD (DBG_TX, "last vc hack: miss");
    // Are we currently transmitting this VC on one of the channels?
    क्रम (tx_channel = 0; tx_channel < TX_CHANS; ++tx_channel)
      अगर (dev->tx_channel_record[tx_channel] == channel) अणु
	PRINTD (DBG_TX, "vc already on channel: hit");
	अवरोध;
      पूर्ण
    अगर (tx_channel == TX_CHANS) अणु 
      PRINTD (DBG_TX, "vc already on channel: miss");
      // Find and set up an idle channel.
      tx_channel = setup_idle_tx_channel (dev, vcc);
      अगर (tx_channel < 0) अणु
	PRINTD (DBG_TX|DBG_ERR, "failed to get channel");
	tx_release (dev);
	वापस tx_channel;
      पूर्ण
    पूर्ण
    
    PRINTD (DBG_TX, "got channel");
    SELECT_TX_CHANNEL(dev, tx_channel);
    
    dev->last_vc = channel;
    dev->tx_last = tx_channel;
  पूर्ण
  
  PRINTD (DBG_TX, "using channel %u", tx_channel);
  
  YELLOW_LED_OFF(dev);
  
  // TX start transfer
  
  अणु
    अचिन्हित पूर्णांक tx_len = skb->len;
    अचिन्हित पूर्णांक tx_iovcnt = skb_shinfo(skb)->nr_frags;
    // remember this so we can मुक्त it later
    dev->tx_skb = skb;
    
    अगर (tx_iovcnt) अणु
      // scatter gather transfer
      dev->tx_regions = tx_iovcnt;
      dev->tx_iovec = शून्य;		/* @@@ needs rewritten */
      dev->tx_bytes = 0;
      PRINTD (DBG_TX|DBG_BUS, "TX start scatter-gather transfer (iovec %p, len %d)",
	      skb->data, tx_len);
      tx_release (dev);
      hrz_kमुक्त_skb (skb);
      वापस -EIO;
    पूर्ण अन्यथा अणु
      // simple transfer
      dev->tx_regions = 0;
      dev->tx_iovec = शून्य;
      dev->tx_bytes = tx_len;
      dev->tx_addr = skb->data;
      PRINTD (DBG_TX|DBG_BUS, "TX start simple transfer (addr %p, len %d)",
	      skb->data, tx_len);
    पूर्ण
    
    // and करो the business
    tx_schedule (dev, 0);
    
  पूर्ण
  
  वापस 0;
पूर्ण

/********** reset a card **********/

अटल व्योम hrz_reset (स्थिर hrz_dev * dev) अणु
  u32 control_0_reg = rd_regl (dev, CONTROL_0_REG);
  
  // why not set RESET_HORIZON to one and रुको क्रम the card to
  // reनिश्चित that bit as zero? Like so:
  control_0_reg = control_0_reg & RESET_HORIZON;
  wr_regl (dev, CONTROL_0_REG, control_0_reg);
  जबतक (control_0_reg & RESET_HORIZON)
    control_0_reg = rd_regl (dev, CONTROL_0_REG);
  
  // old reset code retained:
  wr_regl (dev, CONTROL_0_REG, control_0_reg |
	   RESET_ATM | RESET_RX | RESET_TX | RESET_HOST);
  // just guessing here
  udelay (1000);
  
  wr_regl (dev, CONTROL_0_REG, control_0_reg);
पूर्ण

/********** पढ़ो the burnt in address **********/

अटल व्योम WRITE_IT_WAIT (स्थिर hrz_dev *dev, u32 ctrl)
अणु
	wr_regl (dev, CONTROL_0_REG, ctrl);
	udelay (5);
पूर्ण
  
अटल व्योम CLOCK_IT (स्थिर hrz_dev *dev, u32 ctrl)
अणु
	// DI must be valid around rising SK edge
	WRITE_IT_WAIT(dev, ctrl & ~SEEPROM_SK);
	WRITE_IT_WAIT(dev, ctrl | SEEPROM_SK);
पूर्ण

अटल u16 पढ़ो_bia(स्थिर hrz_dev *dev, u16 addr)
अणु
  u32 ctrl = rd_regl (dev, CONTROL_0_REG);
  
  स्थिर अचिन्हित पूर्णांक addr_bits = 6;
  स्थिर अचिन्हित पूर्णांक data_bits = 16;
  
  अचिन्हित पूर्णांक i;
  
  u16 res;
  
  ctrl &= ~(SEEPROM_CS | SEEPROM_SK | SEEPROM_DI);
  WRITE_IT_WAIT(dev, ctrl);
  
  // wake Serial EEPROM and send 110 (READ) command
  ctrl |=  (SEEPROM_CS | SEEPROM_DI);
  CLOCK_IT(dev, ctrl);
  
  ctrl |= SEEPROM_DI;
  CLOCK_IT(dev, ctrl);
  
  ctrl &= ~SEEPROM_DI;
  CLOCK_IT(dev, ctrl);
  
  क्रम (i=0; i<addr_bits; i++) अणु
    अगर (addr & (1 << (addr_bits-1)))
      ctrl |= SEEPROM_DI;
    अन्यथा
      ctrl &= ~SEEPROM_DI;
    
    CLOCK_IT(dev, ctrl);
    
    addr = addr << 1;
  पूर्ण
  
  // we could check that we have DO = 0 here
  ctrl &= ~SEEPROM_DI;
  
  res = 0;
  क्रम (i=0;i<data_bits;i++) अणु
    res = res >> 1;
    
    CLOCK_IT(dev, ctrl);
    
    अगर (rd_regl (dev, CONTROL_0_REG) & SEEPROM_DO)
      res |= (1 << (data_bits-1));
  पूर्ण
  
  ctrl &= ~(SEEPROM_SK | SEEPROM_CS);
  WRITE_IT_WAIT(dev, ctrl);
  
  वापस res;
पूर्ण

/********** initialise a card **********/

अटल पूर्णांक hrz_init(hrz_dev *dev)
अणु
  पूर्णांक onefivefive;
  
  u16 chan;
  
  पूर्णांक buff_count;
  
  HDW * mem;
  
  cell_buf * tx_desc;
  cell_buf * rx_desc;
  
  u32 ctrl;
  
  ctrl = rd_regl (dev, CONTROL_0_REG);
  PRINTD (DBG_INFO, "ctrl0reg is %#x", ctrl);
  onefivefive = ctrl & ATM_LAYER_STATUS;
  
  अगर (onefivefive)
    prपूर्णांकk (DEV_LABEL ": Horizon Ultra (at 155.52 MBps)");
  अन्यथा
    prपूर्णांकk (DEV_LABEL ": Horizon (at 25 MBps)");
  
  prपूर्णांकk (":");
  // Reset the card to get everything in a known state
  
  prपूर्णांकk (" reset");
  hrz_reset (dev);
  
  // Clear all the buffer memory
  
  prपूर्णांकk (" clearing memory");
  
  क्रम (mem = (HDW *) memmap; mem < (HDW *) (memmap + 1); ++mem)
    wr_mem (dev, mem, 0);
  
  prपूर्णांकk (" tx channels");
  
  // All transmit eight channels are set up as AAL5 ABR channels with
  // a 16us cell spacing. Why?
  
  // Channel 0 माला_लो the मुक्त buffer at 100h, channel 1 माला_लो the मुक्त
  // buffer at 110h etc.
  
  क्रम (chan = 0; chan < TX_CHANS; ++chan) अणु
    tx_ch_desc * tx_desc = &memmap->tx_descs[chan];
    cell_buf * buf = &memmap->inittxbufs[chan];
    
    // initialise the पढ़ो and ग_लिखो buffer poपूर्णांकers
    wr_mem (dev, &tx_desc->rd_buf_type, BUF_PTR(buf));
    wr_mem (dev, &tx_desc->wr_buf_type, BUF_PTR(buf));
    
    // set the status of the initial buffers to empty
    wr_mem (dev, &buf->next, BUFF_STATUS_EMPTY);
  पूर्ण
  
  // Use space bufn3 at the moment क्रम tx buffers
  
  prपूर्णांकk (" tx buffers");
  
  tx_desc = memmap->bufn3;
  
  wr_mem (dev, &memmap->txमुक्तbufstart.next, BUF_PTR(tx_desc) | BUFF_STATUS_EMPTY);
  
  क्रम (buff_count = 0; buff_count < BUFN3_SIZE-1; buff_count++) अणु
    wr_mem (dev, &tx_desc->next, BUF_PTR(tx_desc+1) | BUFF_STATUS_EMPTY);
    tx_desc++;
  पूर्ण
  
  wr_mem (dev, &tx_desc->next, BUF_PTR(&memmap->txमुक्तbufend) | BUFF_STATUS_EMPTY);
  
  // Initialise the transmit मुक्त buffer count
  wr_regw (dev, TX_FREE_BUFFER_COUNT_OFF, BUFN3_SIZE);
  
  prपूर्णांकk (" rx channels");
  
  // Initialise all of the receive channels to be AAL5 disabled with
  // an पूर्णांकerrupt threshold of 0
  
  क्रम (chan = 0; chan < RX_CHANS; ++chan) अणु
    rx_ch_desc * rx_desc = &memmap->rx_descs[chan];
    
    wr_mem (dev, &rx_desc->wr_buf_type, CHANNEL_TYPE_AAL5 | RX_CHANNEL_DISABLED);
  पूर्ण
  
  prपूर्णांकk (" rx buffers");
  
  // Use space bufn4 at the moment क्रम rx buffers
  
  rx_desc = memmap->bufn4;
  
  wr_mem (dev, &memmap->rxमुक्तbufstart.next, BUF_PTR(rx_desc) | BUFF_STATUS_EMPTY);
  
  क्रम (buff_count = 0; buff_count < BUFN4_SIZE-1; buff_count++) अणु
    wr_mem (dev, &rx_desc->next, BUF_PTR(rx_desc+1) | BUFF_STATUS_EMPTY);
    
    rx_desc++;
  पूर्ण
  
  wr_mem (dev, &rx_desc->next, BUF_PTR(&memmap->rxमुक्तbufend) | BUFF_STATUS_EMPTY);
  
  // Initialise the receive मुक्त buffer count
  wr_regw (dev, RX_FREE_BUFFER_COUNT_OFF, BUFN4_SIZE);
  
  // Initialize Horizons रेजिस्टरs
  
  // TX config
  wr_regw (dev, TX_CONFIG_OFF,
	   ABR_ROUND_ROBIN | TX_NORMAL_OPERATION | DRVR_DRVRBAR_ENABLE);
  
  // RX config. Use 10-x VC bits, x VP bits, non user cells in channel 0.
  wr_regw (dev, RX_CONFIG_OFF,
	   DISCARD_UNUSED_VPI_VCI_BITS_SET | NON_USER_CELLS_IN_ONE_CHANNEL | vpi_bits);
  
  // RX line config
  wr_regw (dev, RX_LINE_CONFIG_OFF,
	   LOCK_DETECT_ENABLE | FREQUENCY_DETECT_ENABLE | GXTALOUT_SELECT_DIV4);
  
  // Set the max AAL5 cell count to be just enough to contain the
  // largest AAL5 frame that the user wants to receive
  wr_regw (dev, MAX_AAL5_CELL_COUNT_OFF,
	   DIV_ROUND_UP(max_rx_size + ATM_AAL5_TRAILER, ATM_CELL_PAYLOAD));
  
  // Enable receive
  wr_regw (dev, RX_CONFIG_OFF, rd_regw (dev, RX_CONFIG_OFF) | RX_ENABLE);
  
  prपूर्णांकk (" control");
  
  // Drive the OE of the LEDs then turn the green LED on
  ctrl |= GREEN_LED_OE | YELLOW_LED_OE | GREEN_LED | YELLOW_LED;
  wr_regl (dev, CONTROL_0_REG, ctrl);
  
  // Test क्रम a 155-capable card
  
  अगर (onefivefive) अणु
    // Select 155 mode... make this a choice (or: how करो we detect
    // बाह्यal line speed and चयन?)
    ctrl |= ATM_LAYER_SELECT;
    wr_regl (dev, CONTROL_0_REG, ctrl);
    
    // test SUNI-lite vs SAMBA
    
    // Register 0x00 in the SUNI will have some of bits 3-7 set, and
    // they will always be zero क्रम the SAMBA.  Ha!  Bloody hardware
    // engineers.  It'll never work.
    
    अगर (rd_framer (dev, 0) & 0x00f0) अणु
      // SUNI
      prपूर्णांकk (" SUNI");
      
      // Reset, just in हाल
      wr_framer (dev, 0x00, 0x0080);
      wr_framer (dev, 0x00, 0x0000);
      
      // Configure transmit FIFO
      wr_framer (dev, 0x63, rd_framer (dev, 0x63) | 0x0002);
      
      // Set line समयd mode
      wr_framer (dev, 0x05, rd_framer (dev, 0x05) | 0x0001);
    पूर्ण अन्यथा अणु
      // SAMBA
      prपूर्णांकk (" SAMBA");
      
      // Reset, just in हाल
      wr_framer (dev, 0, rd_framer (dev, 0) | 0x0001);
      wr_framer (dev, 0, rd_framer (dev, 0) &~ 0x0001);
      
      // Turn off diagnostic loopback and enable line-समयd mode
      wr_framer (dev, 0, 0x0002);
      
      // Turn on transmit outमाला_दो
      wr_framer (dev, 2, 0x0B80);
    पूर्ण
  पूर्ण अन्यथा अणु
    // Select 25 mode
    ctrl &= ~ATM_LAYER_SELECT;
    
    // Madge B154 setup
    // none required?
  पूर्ण
  
  prपूर्णांकk (" LEDs");
  
  GREEN_LED_ON(dev);
  YELLOW_LED_ON(dev);
  
  prपूर्णांकk (" ESI=");
  
  अणु
    u16 b = 0;
    पूर्णांक i;
    u8 * esi = dev->aपंचांग_dev->esi;
    
    // in the card I have, EEPROM
    // addresses 0, 1, 2 contain 0
    // addresess 5, 6 etc. contain ffff
    // NB: Madge prefix is 00 00 f6 (which is 00 00 6f in Ethernet bit order)
    // the पढ़ो_bia routine माला_लो the BIA in Ethernet bit order
    
    क्रम (i=0; i < ESI_LEN; ++i) अणु
      अगर (i % 2 == 0)
	b = पढ़ो_bia (dev, i/2 + 2);
      अन्यथा
	b = b >> 8;
      esi[i] = b & 0xFF;
      prपूर्णांकk ("%02x", esi[i]);
    पूर्ण
  पूर्ण
  
  // Enable RX_Q and ?X_COMPLETE पूर्णांकerrupts only
  wr_regl (dev, INT_ENABLE_REG_OFF, INTERESTING_INTERRUPTS);
  prपूर्णांकk (" IRQ on");
  
  prपूर्णांकk (".\n");
  
  वापस onefivefive;
पूर्ण

/********** check max_sdu **********/

अटल पूर्णांक check_max_sdu (hrz_aal aal, काष्ठा aपंचांग_trafprm * tp, अचिन्हित पूर्णांक max_frame_size) अणु
  PRINTD (DBG_FLOW|DBG_QOS, "check_max_sdu");
  
  चयन (aal) अणु
    हाल aal0:
      अगर (!(tp->max_sdu)) अणु
	PRINTD (DBG_QOS, "defaulting max_sdu");
	tp->max_sdu = ATM_AAL0_SDU;
      पूर्ण अन्यथा अगर (tp->max_sdu != ATM_AAL0_SDU) अणु
	PRINTD (DBG_QOS|DBG_ERR, "rejecting max_sdu");
	वापस -EINVAL;
      पूर्ण
      अवरोध;
    हाल aal34:
      अगर (tp->max_sdu == 0 || tp->max_sdu > ATM_MAX_AAL34_PDU) अणु
	PRINTD (DBG_QOS, "%sing max_sdu", tp->max_sdu ? "capp" : "default");
	tp->max_sdu = ATM_MAX_AAL34_PDU;
      पूर्ण
      अवरोध;
    हाल aal5:
      अगर (tp->max_sdu == 0 || tp->max_sdu > max_frame_size) अणु
	PRINTD (DBG_QOS, "%sing max_sdu", tp->max_sdu ? "capp" : "default");
	tp->max_sdu = max_frame_size;
      पूर्ण
      अवरोध;
  पूर्ण
  वापस 0;
पूर्ण

/********** check pcr **********/

// something like this should be part of ATM Linux
अटल पूर्णांक aपंचांग_pcr_check (काष्ठा aपंचांग_trafprm * tp, अचिन्हित पूर्णांक pcr) अणु
  // we are assuming non-UBR, and non-special values of pcr
  अगर (tp->min_pcr == ATM_MAX_PCR)
    PRINTD (DBG_QOS, "luser gave min_pcr = ATM_MAX_PCR");
  अन्यथा अगर (tp->min_pcr < 0)
    PRINTD (DBG_QOS, "luser gave negative min_pcr");
  अन्यथा अगर (tp->min_pcr && tp->min_pcr > pcr)
    PRINTD (DBG_QOS, "pcr less than min_pcr");
  अन्यथा
    // !! max_pcr = UNSPEC (0) is equivalent to max_pcr = MAX (-1)
    // easier to #घोषणा ATM_MAX_PCR 0 and have all rates अचिन्हित?
    // [this would get rid of next two conditionals]
    अगर ((0) && tp->max_pcr == ATM_MAX_PCR)
      PRINTD (DBG_QOS, "luser gave max_pcr = ATM_MAX_PCR");
    अन्यथा अगर ((tp->max_pcr != ATM_MAX_PCR) && tp->max_pcr < 0)
      PRINTD (DBG_QOS, "luser gave negative max_pcr");
    अन्यथा अगर (tp->max_pcr && tp->max_pcr != ATM_MAX_PCR && tp->max_pcr < pcr)
      PRINTD (DBG_QOS, "pcr greater than max_pcr");
    अन्यथा अणु
      // each limit unspecअगरied or not violated
      PRINTD (DBG_QOS, "xBR(pcr) OK");
      वापस 0;
    पूर्ण
  PRINTD (DBG_QOS, "pcr=%u, tp: min_pcr=%d, pcr=%d, max_pcr=%d",
	  pcr, tp->min_pcr, tp->pcr, tp->max_pcr);
  वापस -EINVAL;
पूर्ण

/********** खोलो VC **********/

अटल पूर्णांक hrz_खोलो (काष्ठा aपंचांग_vcc *aपंचांग_vcc)
अणु
  पूर्णांक error;
  u16 channel;
  
  काष्ठा aपंचांग_qos * qos;
  काष्ठा aपंचांग_trafprm * txtp;
  काष्ठा aपंचांग_trafprm * rxtp;
  
  hrz_dev * dev = HRZ_DEV(aपंचांग_vcc->dev);
  hrz_vcc vcc;
  hrz_vcc * vccp; // allocated late
  लघु vpi = aपंचांग_vcc->vpi;
  पूर्णांक vci = aपंचांग_vcc->vci;
  PRINTD (DBG_FLOW|DBG_VCC, "hrz_open %x %x", vpi, vci);
  
#अगर_घोषित ATM_VPI_UNSPEC
  // UNSPEC is deprecated, हटाओ this code eventually
  अगर (vpi == ATM_VPI_UNSPEC || vci == ATM_VCI_UNSPEC) अणु
    PRINTK (KERN_WARNING, "rejecting open with unspecified VPI/VCI (deprecated)");
    वापस -EINVAL;
  पूर्ण
#पूर्ण_अगर
  
  error = vpivci_to_channel (&channel, vpi, vci);
  अगर (error) अणु
    PRINTD (DBG_WARN|DBG_VCC, "VPI/VCI out of range: %hd/%d", vpi, vci);
    वापस error;
  पूर्ण
  
  vcc.channel = channel;
  // max speed क्रम the moment
  vcc.tx_rate = 0x0;
  
  qos = &aपंचांग_vcc->qos;
  
  // check AAL and remember it
  चयन (qos->aal) अणु
    हाल ATM_AAL0:
      // we would अगर it were 48 bytes and not 52!
      PRINTD (DBG_QOS|DBG_VCC, "AAL0");
      vcc.aal = aal0;
      अवरोध;
    हाल ATM_AAL34:
      // we would अगर I knew how करो the SAR!
      PRINTD (DBG_QOS|DBG_VCC, "AAL3/4");
      vcc.aal = aal34;
      अवरोध;
    हाल ATM_AAL5:
      PRINTD (DBG_QOS|DBG_VCC, "AAL5");
      vcc.aal = aal5;
      अवरोध;
    शेष:
      PRINTD (DBG_QOS|DBG_VCC, "Bad AAL!");
      वापस -EINVAL;
  पूर्ण
  
  // TX traffic parameters
  
  // there are two, पूर्णांकerrelated problems here: 1. the reservation of
  // PCR is not a binary choice, we are given bounds and/or a
  // desirable value; 2. the device is only capable of certain values,
  // most of which are not पूर्णांकegers. It is almost certainly acceptable
  // to be off by a maximum of 1 to 10 cps.
  
  // Pragmatic choice: always store an पूर्णांकegral PCR as that which has
  // been allocated, even अगर we allocate a little (or a lot) less,
  // after rounding. The actual allocation depends on what we can
  // manage with our rate selection algorithm. The rate selection
  // algorithm is given an पूर्णांकegral PCR and a tolerance and told
  // whether it should round the value up or करोwn अगर the tolerance is
  // exceeded; it वापसs: a) the actual rate selected (rounded up to
  // the nearest पूर्णांकeger), b) a bit pattern to feed to the समयr
  // रेजिस्टर, and c) a failure value अगर no applicable rate exists.
  
  // Part of the job is करोne by aपंचांग_pcr_goal which gives us a PCR
  // specअगरication which says: EITHER grab the maximum available PCR
  // (and perhaps a lower bound which we musn't pass), OR grab this
  // amount, rounding करोwn अगर you have to (and perhaps a lower bound
  // which we musn't pass) OR grab this amount, rounding up अगर you
  // have to (and perhaps an upper bound which we musn't pass). If any
  // bounds ARE passed we fail. Note that rounding is only rounding to
  // match device limitations, we करो not round करोwn to satisfy
  // bandwidth availability even अगर this would not violate any given
  // lower bound.
  
  // Note: telephony = 64kb/s = 48 byte cell payload @ 500/3 cells/s
  // (say) so this is not even a binary fixpoपूर्णांक cell rate (but this
  // device can करो it). To aव्योम this sort of hassle we use a
  // tolerance parameter (currently fixed at 10 cps).
  
  PRINTD (DBG_QOS, "TX:");
  
  txtp = &qos->txtp;
  
  // set up शेषs क्रम no traffic
  vcc.tx_rate = 0;
  // who knows what would actually happen अगर you try and send on this?
  vcc.tx_xbr_bits = IDLE_RATE_TYPE;
  vcc.tx_pcr_bits = CLOCK_DISABLE;
#अगर 0
  vcc.tx_scr_bits = CLOCK_DISABLE;
  vcc.tx_bucket_bits = 0;
#पूर्ण_अगर
  
  अगर (txtp->traffic_class != ATM_NONE) अणु
    error = check_max_sdu (vcc.aal, txtp, max_tx_size);
    अगर (error) अणु
      PRINTD (DBG_QOS, "TX max_sdu check failed");
      वापस error;
    पूर्ण
    
    चयन (txtp->traffic_class) अणु
      हाल ATM_UBR: अणु
	// we take "the PCR" as a rate-cap
	// not reserved
	vcc.tx_rate = 0;
	make_rate (dev, 1<<30, round_nearest, &vcc.tx_pcr_bits, शून्य);
	vcc.tx_xbr_bits = ABR_RATE_TYPE;
	अवरोध;
      पूर्ण
#अगर 0
      हाल ATM_ABR: अणु
	// reserve min, allow up to max
	vcc.tx_rate = 0; // ?
	make_rate (dev, 1<<30, round_nearest, &vcc.tx_pcr_bits, 0);
	vcc.tx_xbr_bits = ABR_RATE_TYPE;
	अवरोध;
      पूर्ण
#पूर्ण_अगर
      हाल ATM_CBR: अणु
	पूर्णांक pcr = aपंचांग_pcr_goal (txtp);
	rounding r;
	अगर (!pcr) अणु
	  // करोwn vs. up, reमुख्यing bandwidth vs. unlimited bandwidth!!
	  // should really have: once someone माला_लो unlimited bandwidth
	  // that no more non-UBR channels can be खोलोed until the
	  // unlimited one बंदs?? For the moment, round_करोwn means
	  // greedy people actually get something and not nothing
	  r = round_करोwn;
	  // slight race (no locking) here so we may get -EAGAIN
	  // later; the greedy bastards would deserve it :)
	  PRINTD (DBG_QOS, "snatching all remaining TX bandwidth");
	  pcr = dev->tx_avail;
	पूर्ण अन्यथा अगर (pcr < 0) अणु
	  r = round_करोwn;
	  pcr = -pcr;
	पूर्ण अन्यथा अणु
	  r = round_up;
	पूर्ण
	error = make_rate_with_tolerance (dev, pcr, r, 10,
					  &vcc.tx_pcr_bits, &vcc.tx_rate);
	अगर (error) अणु
	  PRINTD (DBG_QOS, "could not make rate from TX PCR");
	  वापस error;
	पूर्ण
	// not really clear what further checking is needed
	error = aपंचांग_pcr_check (txtp, vcc.tx_rate);
	अगर (error) अणु
	  PRINTD (DBG_QOS, "TX PCR failed consistency check");
	  वापस error;
	पूर्ण
	vcc.tx_xbr_bits = CBR_RATE_TYPE;
	अवरोध;
      पूर्ण
#अगर 0
      हाल ATM_VBR: अणु
	पूर्णांक pcr = aपंचांग_pcr_goal (txtp);
	// पूर्णांक scr = aपंचांग_scr_goal (txtp);
	पूर्णांक scr = pcr/2; // just क्रम fun
	अचिन्हित पूर्णांक mbs = 60; // just क्रम fun
	rounding pr;
	rounding sr;
	अचिन्हित पूर्णांक bucket;
	अगर (!pcr) अणु
	  pr = round_nearest;
	  pcr = 1<<30;
	पूर्ण अन्यथा अगर (pcr < 0) अणु
	  pr = round_करोwn;
	  pcr = -pcr;
	पूर्ण अन्यथा अणु
	  pr = round_up;
	पूर्ण
	error = make_rate_with_tolerance (dev, pcr, pr, 10,
					  &vcc.tx_pcr_bits, 0);
	अगर (!scr) अणु
	  // see comments क्रम PCR with CBR above
	  sr = round_करोwn;
	  // slight race (no locking) here so we may get -EAGAIN
	  // later; the greedy bastards would deserve it :)
	  PRINTD (DBG_QOS, "snatching all remaining TX bandwidth");
	  scr = dev->tx_avail;
	पूर्ण अन्यथा अगर (scr < 0) अणु
	  sr = round_करोwn;
	  scr = -scr;
	पूर्ण अन्यथा अणु
	  sr = round_up;
	पूर्ण
	error = make_rate_with_tolerance (dev, scr, sr, 10,
					  &vcc.tx_scr_bits, &vcc.tx_rate);
	अगर (error) अणु
	  PRINTD (DBG_QOS, "could not make rate from TX SCR");
	  वापस error;
	पूर्ण
	// not really clear what further checking is needed
	// error = aपंचांग_scr_check (txtp, vcc.tx_rate);
	अगर (error) अणु
	  PRINTD (DBG_QOS, "TX SCR failed consistency check");
	  वापस error;
	पूर्ण
	// bucket calculations (from a piece of paper...) cell bucket
	// capacity must be largest पूर्णांकeger smaller than m(p-s)/p + 1
	// where m = max burst size, p = pcr, s = scr
	bucket = mbs*(pcr-scr)/pcr;
	अगर (bucket*pcr != mbs*(pcr-scr))
	  bucket += 1;
	अगर (bucket > BUCKET_MAX_SIZE) अणु
	  PRINTD (DBG_QOS, "shrinking bucket from %u to %u",
		  bucket, BUCKET_MAX_SIZE);
	  bucket = BUCKET_MAX_SIZE;
	पूर्ण
	vcc.tx_xbr_bits = VBR_RATE_TYPE;
	vcc.tx_bucket_bits = bucket;
	अवरोध;
      पूर्ण
#पूर्ण_अगर
      शेष: अणु
	PRINTD (DBG_QOS, "unsupported TX traffic class");
	वापस -EINVAL;
      पूर्ण
    पूर्ण
  पूर्ण
  
  // RX traffic parameters
  
  PRINTD (DBG_QOS, "RX:");
  
  rxtp = &qos->rxtp;
  
  // set up शेषs क्रम no traffic
  vcc.rx_rate = 0;
  
  अगर (rxtp->traffic_class != ATM_NONE) अणु
    error = check_max_sdu (vcc.aal, rxtp, max_rx_size);
    अगर (error) अणु
      PRINTD (DBG_QOS, "RX max_sdu check failed");
      वापस error;
    पूर्ण
    चयन (rxtp->traffic_class) अणु
      हाल ATM_UBR: अणु
	// not reserved
	अवरोध;
      पूर्ण
#अगर 0
      हाल ATM_ABR: अणु
	// reserve min
	vcc.rx_rate = 0; // ?
	अवरोध;
      पूर्ण
#पूर्ण_अगर
      हाल ATM_CBR: अणु
	पूर्णांक pcr = aपंचांग_pcr_goal (rxtp);
	अगर (!pcr) अणु
	  // slight race (no locking) here so we may get -EAGAIN
	  // later; the greedy bastards would deserve it :)
	  PRINTD (DBG_QOS, "snatching all remaining RX bandwidth");
	  pcr = dev->rx_avail;
	पूर्ण अन्यथा अगर (pcr < 0) अणु
	  pcr = -pcr;
	पूर्ण
	vcc.rx_rate = pcr;
	// not really clear what further checking is needed
	error = aपंचांग_pcr_check (rxtp, vcc.rx_rate);
	अगर (error) अणु
	  PRINTD (DBG_QOS, "RX PCR failed consistency check");
	  वापस error;
	पूर्ण
	अवरोध;
      पूर्ण
#अगर 0
      हाल ATM_VBR: अणु
	// पूर्णांक scr = aपंचांग_scr_goal (rxtp);
	पूर्णांक scr = 1<<16; // just क्रम fun
	अगर (!scr) अणु
	  // slight race (no locking) here so we may get -EAGAIN
	  // later; the greedy bastards would deserve it :)
	  PRINTD (DBG_QOS, "snatching all remaining RX bandwidth");
	  scr = dev->rx_avail;
	पूर्ण अन्यथा अगर (scr < 0) अणु
	  scr = -scr;
	पूर्ण
	vcc.rx_rate = scr;
	// not really clear what further checking is needed
	// error = aपंचांग_scr_check (rxtp, vcc.rx_rate);
	अगर (error) अणु
	  PRINTD (DBG_QOS, "RX SCR failed consistency check");
	  वापस error;
	पूर्ण
	अवरोध;
      पूर्ण
#पूर्ण_अगर
      शेष: अणु
	PRINTD (DBG_QOS, "unsupported RX traffic class");
	वापस -EINVAL;
      पूर्ण
    पूर्ण
  पूर्ण
  
  
  // late पात useful क्रम diagnostics
  अगर (vcc.aal != aal5) अणु
    PRINTD (DBG_QOS, "AAL not supported");
    वापस -EINVAL;
  पूर्ण
  
  // get space क्रम our vcc stuff and copy parameters पूर्णांकo it
  vccp = kदो_स्मृति (माप(hrz_vcc), GFP_KERNEL);
  अगर (!vccp) अणु
    PRINTK (KERN_ERR, "out of memory!");
    वापस -ENOMEM;
  पूर्ण
  *vccp = vcc;
  
  // clear error and grab cell rate resource lock
  error = 0;
  spin_lock (&dev->rate_lock);
  
  अगर (vcc.tx_rate > dev->tx_avail) अणु
    PRINTD (DBG_QOS, "not enough TX PCR left");
    error = -EAGAIN;
  पूर्ण
  
  अगर (vcc.rx_rate > dev->rx_avail) अणु
    PRINTD (DBG_QOS, "not enough RX PCR left");
    error = -EAGAIN;
  पूर्ण
  
  अगर (!error) अणु
    // really consume cell rates
    dev->tx_avail -= vcc.tx_rate;
    dev->rx_avail -= vcc.rx_rate;
    PRINTD (DBG_QOS|DBG_VCC, "reserving %u TX PCR and %u RX PCR",
	    vcc.tx_rate, vcc.rx_rate);
  पूर्ण
  
  // release lock and निकास on error
  spin_unlock (&dev->rate_lock);
  अगर (error) अणु
    PRINTD (DBG_QOS|DBG_VCC, "insufficient cell rate resources");
    kमुक्त (vccp);
    वापस error;
  पूर्ण
  
  // this is "immediately beक्रमe allocating the connection identअगरier
  // in hardware" - so दीर्घ as the next call करोes not fail :)
  set_bit(ATM_VF_ADDR,&aपंचांग_vcc->flags);
  
  // any errors here are very serious and should never occur
  
  अगर (rxtp->traffic_class != ATM_NONE) अणु
    अगर (dev->rxer[channel]) अणु
      PRINTD (DBG_ERR|DBG_VCC, "VC already open for RX");
      error = -EBUSY;
    पूर्ण
    अगर (!error)
      error = hrz_खोलो_rx (dev, channel);
    अगर (error) अणु
      kमुक्त (vccp);
      वापस error;
    पूर्ण
    // this link allows RX frames through
    dev->rxer[channel] = aपंचांग_vcc;
  पूर्ण
  
  // success, set elements of aपंचांग_vcc
  aपंचांग_vcc->dev_data = (व्योम *) vccp;
  
  // indicate पढ़ोiness
  set_bit(ATM_VF_READY,&aपंचांग_vcc->flags);
  
  वापस 0;
पूर्ण

/********** बंद VC **********/

अटल व्योम hrz_बंद (काष्ठा aपंचांग_vcc * aपंचांग_vcc) अणु
  hrz_dev * dev = HRZ_DEV(aपंचांग_vcc->dev);
  hrz_vcc * vcc = HRZ_VCC(aपंचांग_vcc);
  u16 channel = vcc->channel;
  PRINTD (DBG_VCC|DBG_FLOW, "hrz_close");
  
  // indicate unपढ़ोiness
  clear_bit(ATM_VF_READY,&aपंचांग_vcc->flags);

  अगर (aपंचांग_vcc->qos.txtp.traffic_class != ATM_NONE) अणु
    अचिन्हित पूर्णांक i;
    
    // let any TX on this channel that has started complete
    // no restart, just keep trying
    जबतक (tx_hold (dev))
      ;
    // हटाओ record of any tx_channel having been setup क्रम this channel
    क्रम (i = 0; i < TX_CHANS; ++i)
      अगर (dev->tx_channel_record[i] == channel) अणु
	dev->tx_channel_record[i] = -1;
	अवरोध;
      पूर्ण
    अगर (dev->last_vc == channel)
      dev->tx_last = -1;
    tx_release (dev);
  पूर्ण

  अगर (aपंचांग_vcc->qos.rxtp.traffic_class != ATM_NONE) अणु
    // disable RXing - it tries quite hard
    hrz_बंद_rx (dev, channel);
    // क्रमget the vcc - no more skbs will be pushed
    अगर (aपंचांग_vcc != dev->rxer[channel])
      PRINTK (KERN_ERR, "%s atm_vcc=%p rxer[channel]=%p",
	      "arghhh! we're going to die!",
	      aपंचांग_vcc, dev->rxer[channel]);
    dev->rxer[channel] = शून्य;
  पूर्ण
  
  // atomically release our rate reservation
  spin_lock (&dev->rate_lock);
  PRINTD (DBG_QOS|DBG_VCC, "releasing %u TX PCR and %u RX PCR",
	  vcc->tx_rate, vcc->rx_rate);
  dev->tx_avail += vcc->tx_rate;
  dev->rx_avail += vcc->rx_rate;
  spin_unlock (&dev->rate_lock);
  
  // मुक्त our काष्ठाure
  kमुक्त (vcc);
  // say the VPI/VCI is मुक्त again
  clear_bit(ATM_VF_ADDR,&aपंचांग_vcc->flags);
पूर्ण

#अगर 0
अटल पूर्णांक hrz_ioctl (काष्ठा aपंचांग_dev * aपंचांग_dev, अचिन्हित पूर्णांक cmd, व्योम *arg) अणु
  hrz_dev * dev = HRZ_DEV(aपंचांग_dev);
  PRINTD (DBG_FLOW, "hrz_ioctl");
  वापस -1;
पूर्ण

अचिन्हित अक्षर hrz_phy_get (काष्ठा aपंचांग_dev * aपंचांग_dev, अचिन्हित दीर्घ addr) अणु
  hrz_dev * dev = HRZ_DEV(aपंचांग_dev);
  PRINTD (DBG_FLOW, "hrz_phy_get");
  वापस 0;
पूर्ण

अटल व्योम hrz_phy_put (काष्ठा aपंचांग_dev * aपंचांग_dev, अचिन्हित अक्षर value,
			 अचिन्हित दीर्घ addr) अणु
  hrz_dev * dev = HRZ_DEV(aपंचांग_dev);
  PRINTD (DBG_FLOW, "hrz_phy_put");
पूर्ण

अटल पूर्णांक hrz_change_qos (काष्ठा aपंचांग_vcc * aपंचांग_vcc, काष्ठा aपंचांग_qos *qos, पूर्णांक flgs) अणु
  hrz_dev * dev = HRZ_DEV(vcc->dev);
  PRINTD (DBG_FLOW, "hrz_change_qos");
  वापस -1;
पूर्ण
#पूर्ण_अगर

/********** proc file contents **********/

अटल पूर्णांक hrz_proc_पढ़ो (काष्ठा aपंचांग_dev * aपंचांग_dev, loff_t * pos, अक्षर * page) अणु
  hrz_dev * dev = HRZ_DEV(aपंचांग_dev);
  पूर्णांक left = *pos;
  PRINTD (DBG_FLOW, "hrz_proc_read");
  
  /* more diagnostics here? */
  
#अगर 0
  अगर (!left--) अणु
    अचिन्हित पूर्णांक count = प्र_लिखो (page, "vbr buckets:");
    अचिन्हित पूर्णांक i;
    क्रम (i = 0; i < TX_CHANS; ++i)
      count += प्र_लिखो (page, " %u/%u",
			query_tx_channel_config (dev, i, BUCKET_FULLNESS_ACCESS),
			query_tx_channel_config (dev, i, BUCKET_CAPACITY_ACCESS));
    count += प्र_लिखो (page+count, ".\n");
    वापस count;
  पूर्ण
#पूर्ण_अगर
  
  अगर (!left--)
    वापस प्र_लिखो (page,
		    "cells: TX %lu, RX %lu, HEC errors %lu, unassigned %lu.\n",
		    dev->tx_cell_count, dev->rx_cell_count,
		    dev->hec_error_count, dev->unasचिन्हित_cell_count);
  
  अगर (!left--)
    वापस प्र_लिखो (page,
		    "free cell buffers: TX %hu, RX %hu+%hu.\n",
		    rd_regw (dev, TX_FREE_BUFFER_COUNT_OFF),
		    rd_regw (dev, RX_FREE_BUFFER_COUNT_OFF),
		    dev->noof_spare_buffers);
  
  अगर (!left--)
    वापस प्र_लिखो (page,
		    "cps remaining: TX %u, RX %u\n",
		    dev->tx_avail, dev->rx_avail);
  
  वापस 0;
पूर्ण

अटल स्थिर काष्ठा aपंचांगdev_ops hrz_ops = अणु
  .खोलो	= hrz_खोलो,
  .बंद	= hrz_बंद,
  .send	= hrz_send,
  .proc_पढ़ो	= hrz_proc_पढ़ो,
  .owner	= THIS_MODULE,
पूर्ण;

अटल पूर्णांक hrz_probe(काष्ठा pci_dev *pci_dev,
		     स्थिर काष्ठा pci_device_id *pci_ent)
अणु
	hrz_dev * dev;
	पूर्णांक err = 0;

	// adapter slot मुक्त, पढ़ो resources from PCI configuration space
	u32 iobase = pci_resource_start (pci_dev, 0);
	u32 * membase = bus_to_virt (pci_resource_start (pci_dev, 1));
	अचिन्हित पूर्णांक irq;
	अचिन्हित अक्षर lat;

	PRINTD (DBG_FLOW, "hrz_probe");

	अगर (pci_enable_device(pci_dev))
		वापस -EINVAL;

	/* XXX DEV_LABEL is a guess */
	अगर (!request_region(iobase, HRZ_IO_EXTENT, DEV_LABEL)) अणु
		err = -EINVAL;
		जाओ out_disable;
	पूर्ण

	dev = kzalloc(माप(hrz_dev), GFP_KERNEL);
	अगर (!dev) अणु
		// perhaps we should be nice: deरेजिस्टर all adapters and पात?
		PRINTD(DBG_ERR, "out of memory");
		err = -ENOMEM;
		जाओ out_release;
	पूर्ण

	pci_set_drvdata(pci_dev, dev);

	// grab IRQ and install handler - move this someplace more sensible
	irq = pci_dev->irq;
	अगर (request_irq(irq,
			पूर्णांकerrupt_handler,
			IRQF_SHARED, /* irqflags guess */
			DEV_LABEL, /* name guess */
			dev)) अणु
		PRINTD(DBG_WARN, "request IRQ failed!");
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	PRINTD(DBG_INFO, "found Madge ATM adapter (hrz) at: IO %x, IRQ %u, MEM %p",
	       iobase, irq, membase);

	dev->aपंचांग_dev = aपंचांग_dev_रेजिस्टर(DEV_LABEL, &pci_dev->dev, &hrz_ops, -1,
					शून्य);
	अगर (!(dev->aपंचांग_dev)) अणु
		PRINTD(DBG_ERR, "failed to register Madge ATM adapter");
		err = -EINVAL;
		जाओ out_मुक्त_irq;
	पूर्ण

	PRINTD(DBG_INFO, "registered Madge ATM adapter (no. %d) (%p) at %p",
	       dev->aपंचांग_dev->number, dev, dev->aपंचांग_dev);
	dev->aपंचांग_dev->dev_data = (व्योम *) dev;
	dev->pci_dev = pci_dev; 

	// enable bus master accesses
	pci_set_master(pci_dev);

	// frobnicate latency (upwards, usually)
	pci_पढ़ो_config_byte(pci_dev, PCI_LATENCY_TIMER, &lat);
	अगर (pci_lat) अणु
		PRINTD(DBG_INFO, "%s PCI latency timer from %hu to %hu",
		       "changing", lat, pci_lat);
		pci_ग_लिखो_config_byte(pci_dev, PCI_LATENCY_TIMER, pci_lat);
	पूर्ण अन्यथा अगर (lat < MIN_PCI_LATENCY) अणु
		PRINTK(KERN_INFO, "%s PCI latency timer from %hu to %hu",
		       "increasing", lat, MIN_PCI_LATENCY);
		pci_ग_लिखो_config_byte(pci_dev, PCI_LATENCY_TIMER, MIN_PCI_LATENCY);
	पूर्ण

	dev->iobase = iobase;
	dev->irq = irq; 
	dev->membase = membase; 

	dev->rx_q_entry = dev->rx_q_reset = &memmap->rx_q_entries[0];
	dev->rx_q_wrap  = &memmap->rx_q_entries[RX_CHANS-1];

	// these next three are perक्रमmance hacks
	dev->last_vc = -1;
	dev->tx_last = -1;
	dev->tx_idle = 0;

	dev->tx_regions = 0;
	dev->tx_bytes = 0;
	dev->tx_skb = शून्य;
	dev->tx_iovec = शून्य;

	dev->tx_cell_count = 0;
	dev->rx_cell_count = 0;
	dev->hec_error_count = 0;
	dev->unasचिन्हित_cell_count = 0;

	dev->noof_spare_buffers = 0;

	अणु
		अचिन्हित पूर्णांक i;
		क्रम (i = 0; i < TX_CHANS; ++i)
			dev->tx_channel_record[i] = -1;
	पूर्ण

	dev->flags = 0;

	// Allocate cell rates and remember ASIC version
	// Fibre: ATM_OC3_PCR = 1555200000/8/270*260/53 - 29/53
	// Copper: (WRONG) we want 6 पूर्णांकo the above, बंद to 25Mb/s
	// Copper: (plagarise!) 25600000/8/270*260/53 - n/53

	अगर (hrz_init(dev)) अणु
		// to be really pedantic, this should be ATM_OC3c_PCR
		dev->tx_avail = ATM_OC3_PCR;
		dev->rx_avail = ATM_OC3_PCR;
		set_bit(ultra, &dev->flags); // NOT "|= ultra" !
	पूर्ण अन्यथा अणु
		dev->tx_avail = ((25600000/8)*26)/(27*53);
		dev->rx_avail = ((25600000/8)*26)/(27*53);
		PRINTD(DBG_WARN, "Buggy ASIC: no TX bus-mastering.");
	पूर्ण

	// rate changes spinlock
	spin_lock_init(&dev->rate_lock);

	// on-board memory access spinlock; we want atomic पढ़ोs and
	// ग_लिखोs to adapter memory (handles IRQ and SMP)
	spin_lock_init(&dev->mem_lock);

	init_रुकोqueue_head(&dev->tx_queue);

	// vpi in 0..4, vci in 6..10
	dev->aपंचांग_dev->ci_range.vpi_bits = vpi_bits;
	dev->aपंचांग_dev->ci_range.vci_bits = 10-vpi_bits;

	समयr_setup(&dev->housekeeping, करो_housekeeping, 0);
	mod_समयr(&dev->housekeeping, jअगरfies);

out:
	वापस err;

out_मुक्त_irq:
	मुक्त_irq(irq, dev);
out_मुक्त:
	kमुक्त(dev);
out_release:
	release_region(iobase, HRZ_IO_EXTENT);
out_disable:
	pci_disable_device(pci_dev);
	जाओ out;
पूर्ण

अटल व्योम hrz_हटाओ_one(काष्ठा pci_dev *pci_dev)
अणु
	hrz_dev *dev;

	dev = pci_get_drvdata(pci_dev);

	PRINTD(DBG_INFO, "closing %p (atm_dev = %p)", dev, dev->aपंचांग_dev);
	del_समयr_sync(&dev->housekeeping);
	hrz_reset(dev);
	aपंचांग_dev_deरेजिस्टर(dev->aपंचांग_dev);
	मुक्त_irq(dev->irq, dev);
	release_region(dev->iobase, HRZ_IO_EXTENT);
	kमुक्त(dev);

	pci_disable_device(pci_dev);
पूर्ण

अटल व्योम __init hrz_check_args (व्योम) अणु
#अगर_घोषित DEBUG_HORIZON
  PRINTK (KERN_NOTICE, "debug bitmap is %hx", debug &= DBG_MASK);
#अन्यथा
  अगर (debug)
    PRINTK (KERN_NOTICE, "no debug support in this image");
#पूर्ण_अगर
  
  अगर (vpi_bits > HRZ_MAX_VPI)
    PRINTK (KERN_ERR, "vpi_bits has been limited to %hu",
	    vpi_bits = HRZ_MAX_VPI);
  
  अगर (max_tx_size < 0 || max_tx_size > TX_AAL5_LIMIT)
    PRINTK (KERN_NOTICE, "max_tx_size has been limited to %hu",
	    max_tx_size = TX_AAL5_LIMIT);
  
  अगर (max_rx_size < 0 || max_rx_size > RX_AAL5_LIMIT)
    PRINTK (KERN_NOTICE, "max_rx_size has been limited to %hu",
	    max_rx_size = RX_AAL5_LIMIT);
  
  वापस;
पूर्ण

MODULE_AUTHOR(मुख्यtainer_string);
MODULE_DESCRIPTION(description_string);
MODULE_LICENSE("GPL");
module_param(debug, uलघु, 0644);
module_param(vpi_bits, uलघु, 0);
module_param(max_tx_size, पूर्णांक, 0);
module_param(max_rx_size, पूर्णांक, 0);
module_param(pci_lat, byte, 0);
MODULE_PARM_DESC(debug, "debug bitmap, see .h file");
MODULE_PARM_DESC(vpi_bits, "number of bits (0..4) to allocate to VPIs");
MODULE_PARM_DESC(max_tx_size, "maximum size of TX AAL5 frames");
MODULE_PARM_DESC(max_rx_size, "maximum size of RX AAL5 frames");
MODULE_PARM_DESC(pci_lat, "PCI latency in bus cycles");

अटल स्थिर काष्ठा pci_device_id hrz_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_MADGE, PCI_DEVICE_ID_MADGE_HORIZON, PCI_ANY_ID, PCI_ANY_ID,
	  0, 0, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, hrz_pci_tbl);

अटल काष्ठा pci_driver hrz_driver = अणु
	.name =		"horizon",
	.probe =	hrz_probe,
	.हटाओ =	hrz_हटाओ_one,
	.id_table =	hrz_pci_tbl,
पूर्ण;

/********** module entry **********/

अटल पूर्णांक __init hrz_module_init (व्योम) अणु
  BUILD_BUG_ON(माप(काष्ठा MEMMAP) != 128*1024/4);
  
  show_version();
  
  // check arguments
  hrz_check_args();
  
  // get the juice
  वापस pci_रेजिस्टर_driver(&hrz_driver);
पूर्ण

/********** module निकास **********/

अटल व्योम __निकास hrz_module_निकास (व्योम) अणु
  PRINTD (DBG_FLOW, "cleanup_module");

  pci_unरेजिस्टर_driver(&hrz_driver);
पूर्ण

module_init(hrz_module_init);
module_निकास(hrz_module_निकास);
