<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
  Madge Ambassaकरोr ATM Adapter driver.
  Copyright (C) 1995-1999  Madge Networks Ltd.

*/

/* * dedicated to the memory of Graham Gorकरोn 1971-1998 * */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/poison.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/firmware.h>
#समावेश <linux/ihex.h>
#समावेश <linux/slab.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>

#समावेश "ambassador.h"

#घोषणा मुख्यtainer_string "Giuliano Procida at Madge Networks <gprocida@madge.com>"
#घोषणा description_string "Madge ATM Ambassador driver"
#घोषणा version_string "1.2.4"

अटल अंतरभूत व्योम __init show_version (व्योम) अणु
  prपूर्णांकk ("%s version %s\n", description_string, version_string);
पूर्ण

/*
  
  Theory of Operation
  
  I Hardware, detection, initialisation and shutकरोwn.
  
  1. Supported Hardware
  
  This driver is क्रम the PCI ATMizer-based Ambassaकरोr card (except
  very early versions). It is not suitable क्रम the similar EISA "TR7"
  card. Commercially, both cards are known as Collage Server ATM
  adapters.
  
  The loader supports image transfer to the card, image start and few
  other miscellaneous commands.
  
  Only AAL5 is supported with vpi = 0 and vci in the range 0 to 1023.
  
  The cards are big-endian.
  
  2. Detection
  
  Standard PCI stuff, the early cards are detected and rejected.
  
  3. Initialisation
  
  The cards are reset and the self-test results are checked. The
  microcode image is then transferred and started. This रुकोs क्रम a
  poपूर्णांकer to a descriptor containing details of the host-based queues
  and buffers and various parameters etc. Once they are processed
  normal operations may begin. The BIA is पढ़ो using a microcode
  command.
  
  4. Shutकरोwn
  
  This may be accomplished either by a card reset or via the microcode
  shutकरोwn command. Further investigation required.
  
  5. Persistent state
  
  The card reset करोes not affect PCI configuration (good) or the
  contents of several other "shared run-time registers" (bad) which
  include करोorbell and पूर्णांकerrupt control as well as EEPROM and PCI
  control. The driver must be careful when modअगरying these रेजिस्टरs
  not to touch bits it करोes not use and to unकरो any changes at निकास.
  
  II Driver software
  
  0. Generalities
  
  The adapter is quite पूर्णांकelligent (fast) and has a simple पूर्णांकerface
  (few features). VPI is always zero, 1024 VCIs are supported. There
  is limited cell rate support. UBR channels can be capped and ABR
  (explicit rate, but not EFCI) is supported. There is no CBR or VBR
  support.
  
  1. Driver <-> Adapter Communication
  
  Apart from the basic loader commands, the driver communicates
  through three entities: the command queue (CQ), the transmit queue
  pair (TXQ) and the receive queue pairs (RXQ). These three entities
  are set up by the host and passed to the microcode just after it has
  been started.
  
  All queues are host-based circular queues. They are contiguous and
  (due to hardware limitations) have some restrictions as to their
  locations in (bus) memory. They are of the "full means the same as
  empty so करोn't करो that" variety since the adapter uses poपूर्णांकers
  पूर्णांकernally.
  
  The queue pairs work as follows: one queue is क्रम supply to the
  adapter, items in it are pending and are owned by the adapter; the
  other is the queue क्रम वापस from the adapter, items in it have
  been dealt with by the adapter. The host adds items to the supply
  (TX descriptors and मुक्त RX buffer descriptors) and हटाओs items
  from the वापस (TX and RX completions). The adapter deals with out
  of order completions.
  
  Interrupts (card to host) and the करोorbell (host to card) are used
  क्रम संकेतling.
  
  1. CQ
  
  This is to communicate "open VC", "close VC", "get stats" etc. to
  the adapter. At most one command is retired every millisecond by the
  card. There is no out of order completion or notअगरication. The
  driver needs to check the वापस code of the command, रुकोing as
  appropriate.
  
  2. TXQ
  
  TX supply items are of variable length (scatter gather support) and
  so the queue items are (more or less) poपूर्णांकers to the real thing.
  Each TX supply item contains a unique, host-supplied handle (the skb
  bus address seems most sensible as this works क्रम Alphas as well,
  there is no need to करो any endian conversions on the handles).
  
  TX वापस items consist of just the handles above.
  
  3. RXQ (up to 4 of these with dअगरferent lengths and buffer sizes)
  
  RX supply items consist of a unique, host-supplied handle (the skb
  bus address again) and a poपूर्णांकer to the buffer data area.
  
  RX वापस items consist of the handle above, the VC, length and a
  status word. This just screams "oh so easy" करोesn't it?

  Note on RX pool sizes:
   
  Each pool should have enough buffers to handle a back-to-back stream
  of minimum sized frames on a single VC. For example:
  
    frame spacing = 3us (about right)
    
    delay = IRQ lat + RX handling + RX buffer replenish = 20 (us)  (a guess)
    
    min number of buffers क्रम one VC = 1 + delay/spacing (buffers)

    delay/spacing = latency = (20+2)/3 = 7 (buffers)  (rounding up)
    
  The 20us delay assumes that there is no need to sleep; अगर we need to
  sleep to get buffers we are going to drop frames anyway.
  
  In fact, each pool should have enough buffers to support the
  simultaneous reassembly of a separate frame on each VC and cope with
  the हाल in which frames complete in round robin cell fashion on
  each VC.
  
  Only one frame can complete at each cell arrival, so अगर "n" VCs are
  खोलो, the worst हाल is to have them all complete frames together
  followed by all starting new frames together.
  
    desired number of buffers = n + delay/spacing
    
  These are the extreme requirements, however, they are "n+k" क्रम some
  "k" so we have only the स्थिरant to choose. This is the argument
  rx_lats which current शेषs to 7.
  
  Actually, "n ? n+k : 0" is better and this is what is implemented,
  subject to the limit given by the pool size.
  
  4. Driver locking
  
  Simple spinlocks are used around the TX and RX queue mechanisms.
  Anyone with a faster, working method is welcome to implement it.
  
  The adapter command queue is रक्षित with a spinlock. We always
  रुको क्रम commands to complete.
  
  A more complex क्रमm of locking is used around parts of the VC खोलो
  and बंद functions. There are three reasons क्रम a lock: 1. we need
  to करो atomic rate reservation and release (not used yet), 2. Opening
  someबार involves two adapter commands which must not be separated
  by another command on the same VC, 3. the changes to RX pool size
  must be atomic. The lock needs to work over context चयनes, so we
  use a semaphore.
  
  III Hardware Features and Microcode Bugs
  
  1. Byte Ordering
  
  *%^"$&%^$*&^"$(%^$#&^%$(&#%$*(&^#%!"!"!*!
  
  2. Memory access
  
  All काष्ठाures that are not accessed using DMA must be 4-byte
  aligned (not a problem) and must not cross 4MB boundaries.
  
  There is a DMA memory hole at E0000000-E00000FF (groan).
  
  TX fragments (DMA पढ़ो) must not cross 4MB boundaries (would be 16MB
  but क्रम a hardware bug).
  
  RX buffers (DMA ग_लिखो) must not cross 16MB boundaries and must
  include spare trailing bytes up to the next 4-byte boundary; they
  will be written with rubbish.
  
  The PLX likes to prefetch; अगर पढ़ोing up to 4 u32 past the end of
  each TX fragment is not a problem, then TX can be made to go a
  little faster by passing a flag at init that disables a prefetch
  workaround. We करो not pass this flag. (new microcode only)
  
  Now we:
  . Note that alloc_skb rounds up size to a 16byte boundary.  
  . Ensure all areas करो not traverse 4MB boundaries.
  . Ensure all areas करो not start at a E00000xx bus address.
  (I cannot be certain, but this may always hold with Linux)
  . Make all failures cause a loud message.
  . Discard non-conक्रमming SKBs (causes TX failure or RX fill delay).
  . Discard non-conक्रमming TX fragment descriptors (the TX fails).
  In the future we could:
  . Allow RX areas that traverse 4MB (but not 16MB) boundaries.
  . Segment TX areas पूर्णांकo some/more fragments, when necessary.
  . Relax checks क्रम non-DMA items (ignore hole).
  . Give scatter-gather (iovec) requirements using ???. (?)
  
  3. VC बंद is broken (only क्रम new microcode)
  
  The VC बंद adapter microcode command fails to करो anything अगर any
  frames have been received on the VC but none have been transmitted.
  Frames जारी to be reassembled and passed (with IRQ) to the
  driver.
  
  IV To Do List
  
  . Fix bugs!
  
  . Timer code may be broken.
  
  . Deal with buggy VC बंद (somehow) in microcode 12.
  
  . Handle पूर्णांकerrupted and/or non-blocking ग_लिखोs - is this a job क्रम
    the protocol layer?
  
  . Add code to अवरोध up TX fragments when they span 4MB boundaries.
  
  . Add SUNI phy layer (need to know where SUNI lives on card).
  
  . Implement a tx_alloc fn to (a) satisfy TX alignment etc. and (b)
    leave extra headroom space क्रम Ambassaकरोr TX descriptors.
  
  . Understand these elements of काष्ठा aपंचांग_vcc: recvq (proto?),
    sleep, callback, listenq, backlog_quota, reply and user_back.
  
  . Adjust TX/RX skb allocation to favour IP with LANE/CLIP (configurable).
  
  . Impose a TX-pending limit (2?) on each VC, help aव्योम TX q overflow.
  
  . Decide whether RX buffer recycling is or can be made completely safe;
    turn it back on. It looks like Werner is going to axe this.
  
  . Implement QoS changes on खोलो VCs (involves extracting parts of VC खोलो
    and बंद पूर्णांकo separate functions and using them to make changes).
  
  . Hack on command queue so that someone can issue multiple commands and रुको
    on the last one (OR only "no-op" or "wait" commands are रुकोed क्रम).
  
  . Eliminate need क्रम जबतक-schedule around करो_command.
  
*/

अटल व्योम करो_housekeeping (काष्ठा समयr_list *t);
/********** globals **********/

अटल अचिन्हित लघु debug = 0;
अटल अचिन्हित पूर्णांक cmds = 8;
अटल अचिन्हित पूर्णांक txs = 32;
अटल अचिन्हित पूर्णांक rxs[NUM_RX_POOLS] = अणु 64, 64, 64, 64 पूर्ण;
अटल अचिन्हित पूर्णांक rxs_bs[NUM_RX_POOLS] = अणु 4080, 12240, 36720, 65535 पूर्ण;
अटल अचिन्हित पूर्णांक rx_lats = 7;
अटल अचिन्हित अक्षर pci_lat = 0;

अटल स्थिर अचिन्हित दीर्घ onegigmask = -1 << 30;

/********** access to adapter **********/

अटल अंतरभूत व्योम wr_plain (स्थिर amb_dev * dev, माप_प्रकार addr, u32 data) अणु
  PRINTD (DBG_FLOW|DBG_REGS, "wr: %08zx <- %08x", addr, data);
#अगर_घोषित AMB_MMIO
  dev->membase[addr / माप(u32)] = data;
#अन्यथा
  outl (data, dev->iobase + addr);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u32 rd_plain (स्थिर amb_dev * dev, माप_प्रकार addr) अणु
#अगर_घोषित AMB_MMIO
  u32 data = dev->membase[addr / माप(u32)];
#अन्यथा
  u32 data = inl (dev->iobase + addr);
#पूर्ण_अगर
  PRINTD (DBG_FLOW|DBG_REGS, "rd: %08zx -> %08x", addr, data);
  वापस data;
पूर्ण

अटल अंतरभूत व्योम wr_mem (स्थिर amb_dev * dev, माप_प्रकार addr, u32 data) अणु
  __be32 be = cpu_to_be32 (data);
  PRINTD (DBG_FLOW|DBG_REGS, "wr: %08zx <- %08x b[%08x]", addr, data, be);
#अगर_घोषित AMB_MMIO
  dev->membase[addr / माप(u32)] = be;
#अन्यथा
  outl (be, dev->iobase + addr);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u32 rd_mem (स्थिर amb_dev * dev, माप_प्रकार addr) अणु
#अगर_घोषित AMB_MMIO
  __be32 be = dev->membase[addr / माप(u32)];
#अन्यथा
  __be32 be = inl (dev->iobase + addr);
#पूर्ण_अगर
  u32 data = be32_to_cpu (be);
  PRINTD (DBG_FLOW|DBG_REGS, "rd: %08zx -> %08x b[%08x]", addr, data, be);
  वापस data;
पूर्ण

/********** dump routines **********/

अटल अंतरभूत व्योम dump_रेजिस्टरs (स्थिर amb_dev * dev) अणु
#अगर_घोषित DEBUG_AMBASSADOR
  अगर (debug & DBG_REGS) अणु
    माप_प्रकार i;
    PRINTD (DBG_REGS, "reading PLX control: ");
    क्रम (i = 0x00; i < 0x30; i += माप(u32))
      rd_mem (dev, i);
    PRINTD (DBG_REGS, "reading mailboxes: ");
    क्रम (i = 0x40; i < 0x60; i += माप(u32))
      rd_mem (dev, i);
    PRINTD (DBG_REGS, "reading doorb irqev irqen reset:");
    क्रम (i = 0x60; i < 0x70; i += माप(u32))
      rd_mem (dev, i);
  पूर्ण
#अन्यथा
  (व्योम) dev;
#पूर्ण_अगर
  वापस;
पूर्ण

अटल अंतरभूत व्योम dump_loader_block (अस्थिर loader_block * lb) अणु
#अगर_घोषित DEBUG_AMBASSADOR
  अचिन्हित पूर्णांक i;
  PRINTDB (DBG_LOAD, "lb @ %p; res: %d, cmd: %d, pay:",
	   lb, be32_to_cpu (lb->result), be32_to_cpu (lb->command));
  क्रम (i = 0; i < MAX_COMMAND_DATA; ++i)
    PRINTDM (DBG_LOAD, " %08x", be32_to_cpu (lb->payload.data[i]));
  PRINTDE (DBG_LOAD, ", vld: %08x", be32_to_cpu (lb->valid));
#अन्यथा
  (व्योम) lb;
#पूर्ण_अगर
  वापस;
पूर्ण

अटल अंतरभूत व्योम dump_command (command * cmd) अणु
#अगर_घोषित DEBUG_AMBASSADOR
  अचिन्हित पूर्णांक i;
  PRINTDB (DBG_CMD, "cmd @ %p, req: %08x, pars:",
	   cmd, /*be32_to_cpu*/ (cmd->request));
  क्रम (i = 0; i < 3; ++i)
    PRINTDM (DBG_CMD, " %08x", /*be32_to_cpu*/ (cmd->args.par[i]));
  PRINTDE (DBG_CMD, "");
#अन्यथा
  (व्योम) cmd;
#पूर्ण_अगर
  वापस;
पूर्ण

अटल अंतरभूत व्योम dump_skb (अक्षर * prefix, अचिन्हित पूर्णांक vc, काष्ठा sk_buff * skb) अणु
#अगर_घोषित DEBUG_AMBASSADOR
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

/********** check memory areas क्रम use by Ambassaकरोr **********/

/* see limitations under Hardware Features */

अटल पूर्णांक check_area (व्योम * start, माप_प्रकार length) अणु
  // assumes length > 0
  स्थिर u32 fourmegmask = -1 << 22;
  स्थिर u32 twofivesixmask = -1 << 8;
  स्थिर u32 starthole = 0xE0000000;
  u32 startaddress = virt_to_bus (start);
  u32 lastaddress = startaddress+length-1;
  अगर ((startaddress ^ lastaddress) & fourmegmask ||
      (startaddress & twofivesixmask) == starthole) अणु
    PRINTK (KERN_ERR, "check_area failure: [%x,%x] - mail maintainer!",
	    startaddress, lastaddress);
    वापस -1;
  पूर्ण अन्यथा अणु
    वापस 0;
  पूर्ण
पूर्ण

/********** मुक्त an skb (as per ATM device driver करोcumentation) **********/

अटल व्योम amb_kमुक्त_skb (काष्ठा sk_buff * skb) अणु
  अगर (ATM_SKB(skb)->vcc->pop) अणु
    ATM_SKB(skb)->vcc->pop (ATM_SKB(skb)->vcc, skb);
  पूर्ण अन्यथा अणु
    dev_kमुक्त_skb_any (skb);
  पूर्ण
पूर्ण

/********** TX completion **********/

अटल व्योम tx_complete (amb_dev * dev, tx_out * tx) अणु
  tx_simple * tx_descr = bus_to_virt (tx->handle);
  काष्ठा sk_buff * skb = tx_descr->skb;
  
  PRINTD (DBG_FLOW|DBG_TX, "tx_complete %p %p", dev, tx);
  
  // VC layer stats
  atomic_inc(&ATM_SKB(skb)->vcc->stats->tx);
  
  // मुक्त the descriptor
  kमुक्त (tx_descr);
  
  // मुक्त the skb
  amb_kमुक्त_skb (skb);
  
  dev->stats.tx_ok++;
  वापस;
पूर्ण

/********** RX completion **********/

अटल व्योम rx_complete (amb_dev * dev, rx_out * rx) अणु
  काष्ठा sk_buff * skb = bus_to_virt (rx->handle);
  u16 vc = be16_to_cpu (rx->vc);
  // unused: u16 lec_id = be16_to_cpu (rx->lec_id);
  u16 status = be16_to_cpu (rx->status);
  u16 rx_len = be16_to_cpu (rx->length);
  
  PRINTD (DBG_FLOW|DBG_RX, "rx_complete %p %p (len=%hu)", dev, rx, rx_len);
  
  // XXX move this in and add to VC stats ???
  अगर (!status) अणु
    काष्ठा aपंचांग_vcc * aपंचांग_vcc = dev->rxer[vc];
    dev->stats.rx.ok++;
    
    अगर (aपंचांग_vcc) अणु
      
      अगर (rx_len <= aपंचांग_vcc->qos.rxtp.max_sdu) अणु
	
	अगर (aपंचांग_अक्षरge (aपंचांग_vcc, skb->truesize)) अणु
	  
	  // prepare socket buffer
	  ATM_SKB(skb)->vcc = aपंचांग_vcc;
	  skb_put (skb, rx_len);
	  
	  dump_skb ("<<<", vc, skb);
	  
	  // VC layer stats
	  atomic_inc(&aपंचांग_vcc->stats->rx);
	  __net_बारtamp(skb);
	  // end of our responsibility
	  aपंचांग_vcc->push (aपंचांग_vcc, skb);
	  वापस;
	  
	पूर्ण अन्यथा अणु
	  // someone fix this (message), please!
	  PRINTD (DBG_INFO|DBG_RX, "dropped thanks to atm_charge (vc %hu, truesize %u)", vc, skb->truesize);
	  // drop stats incremented in aपंचांग_अक्षरge
	पूर्ण
	
      पूर्ण अन्यथा अणु
      	PRINTK (KERN_INFO, "dropped over-size frame");
	// should we count this?
	atomic_inc(&aपंचांग_vcc->stats->rx_drop);
      पूर्ण
      
    पूर्ण अन्यथा अणु
      PRINTD (DBG_WARN|DBG_RX, "got frame but RX closed for channel %hu", vc);
      // this is an adapter bug, only in new version of microcode
    पूर्ण
    
  पूर्ण अन्यथा अणु
    dev->stats.rx.error++;
    अगर (status & CRC_ERR)
      dev->stats.rx.badcrc++;
    अगर (status & LEN_ERR)
      dev->stats.rx.tooदीर्घ++;
    अगर (status & ABORT_ERR)
      dev->stats.rx.पातed++;
    अगर (status & UNUSED_ERR)
      dev->stats.rx.unused++;
  पूर्ण
  
  dev_kमुक्त_skb_any (skb);
  वापस;
पूर्ण

/*
  
  Note on queue handling.
  
  Here "give" and "take" refer to queue entries and a queue (pair)
  rather than frames to or from the host or adapter. Empty frame
  buffers are given to the RX queue pair and वापसed unused or
  containing RX frames. TX frames (well, poपूर्णांकers to TX fragment
  lists) are given to the TX queue pair, completions are वापसed.
  
*/

/********** command queue **********/

// I really करोn't like this, but it's the best I can करो at the moment

// also, the callers are responsible क्रम byte order as the microcode
// someबार करोes 16-bit accesses (yuk yuk yuk)

अटल पूर्णांक command_करो (amb_dev * dev, command * cmd) अणु
  amb_cq * cq = &dev->cq;
  अस्थिर amb_cq_ptrs * ptrs = &cq->ptrs;
  command * my_slot;
  
  PRINTD (DBG_FLOW|DBG_CMD, "command_do %p", dev);
  
  अगर (test_bit (dead, &dev->flags))
    वापस 0;
  
  spin_lock (&cq->lock);
  
  // अगर not full...
  अगर (cq->pending < cq->maximum) अणु
    // remember my slot क्रम later
    my_slot = ptrs->in;
    PRINTD (DBG_CMD, "command in slot %p", my_slot);
    
    dump_command (cmd);
    
    // copy command in
    *ptrs->in = *cmd;
    cq->pending++;
    ptrs->in = NEXTQ (ptrs->in, ptrs->start, ptrs->limit);
    
    // mail the command
    wr_mem (dev, दुरत्व(amb_mem, mb.adapter.cmd_address), virt_to_bus (ptrs->in));
    
    अगर (cq->pending > cq->high)
      cq->high = cq->pending;
    spin_unlock (&cq->lock);
    
    // these comments were in a जबतक-loop beक्रमe, msleep हटाओs the loop
    // go to sleep
    // PRINTD (DBG_CMD, "wait: sleeping %lu for command", समयout);
    msleep(cq->pending);
    
    // रुको क्रम my slot to be reached (all रुकोers are here or above, until...)
    जबतक (ptrs->out != my_slot) अणु
      PRINTD (DBG_CMD, "wait: command slot (now at %p)", ptrs->out);
      set_current_state(TASK_UNINTERRUPTIBLE);
      schedule();
    पूर्ण
    
    // रुको on my slot (... one माला_लो to its slot, and... )
    जबतक (ptrs->out->request != cpu_to_be32 (SRB_COMPLETE)) अणु
      PRINTD (DBG_CMD, "wait: command slot completion");
      set_current_state(TASK_UNINTERRUPTIBLE);
      schedule();
    पूर्ण
    
    PRINTD (DBG_CMD, "command complete");
    // update queue (... moves the queue aदीर्घ to the next slot)
    spin_lock (&cq->lock);
    cq->pending--;
    // copy command out
    *cmd = *ptrs->out;
    ptrs->out = NEXTQ (ptrs->out, ptrs->start, ptrs->limit);
    spin_unlock (&cq->lock);
    
    वापस 0;
  पूर्ण अन्यथा अणु
    cq->filled++;
    spin_unlock (&cq->lock);
    वापस -EAGAIN;
  पूर्ण
  
पूर्ण

/********** TX queue pair **********/

अटल पूर्णांक tx_give (amb_dev * dev, tx_in * tx) अणु
  amb_txq * txq = &dev->txq;
  अचिन्हित दीर्घ flags;
  
  PRINTD (DBG_FLOW|DBG_TX, "tx_give %p", dev);

  अगर (test_bit (dead, &dev->flags))
    वापस 0;
  
  spin_lock_irqsave (&txq->lock, flags);
  
  अगर (txq->pending < txq->maximum) अणु
    PRINTD (DBG_TX, "TX in slot %p", txq->in.ptr);

    *txq->in.ptr = *tx;
    txq->pending++;
    txq->in.ptr = NEXTQ (txq->in.ptr, txq->in.start, txq->in.limit);
    // hand over the TX and ring the bell
    wr_mem (dev, दुरत्व(amb_mem, mb.adapter.tx_address), virt_to_bus (txq->in.ptr));
    wr_mem (dev, दुरत्व(amb_mem, करोorbell), TX_FRAME);
    
    अगर (txq->pending > txq->high)
      txq->high = txq->pending;
    spin_unlock_irqrestore (&txq->lock, flags);
    वापस 0;
  पूर्ण अन्यथा अणु
    txq->filled++;
    spin_unlock_irqrestore (&txq->lock, flags);
    वापस -EAGAIN;
  पूर्ण
पूर्ण

अटल पूर्णांक tx_take (amb_dev * dev) अणु
  amb_txq * txq = &dev->txq;
  अचिन्हित दीर्घ flags;
  
  PRINTD (DBG_FLOW|DBG_TX, "tx_take %p", dev);
  
  spin_lock_irqsave (&txq->lock, flags);
  
  अगर (txq->pending && txq->out.ptr->handle) अणु
    // deal with TX completion
    tx_complete (dev, txq->out.ptr);
    // mark unused again
    txq->out.ptr->handle = 0;
    // हटाओ item
    txq->pending--;
    txq->out.ptr = NEXTQ (txq->out.ptr, txq->out.start, txq->out.limit);
    
    spin_unlock_irqrestore (&txq->lock, flags);
    वापस 0;
  पूर्ण अन्यथा अणु
    
    spin_unlock_irqrestore (&txq->lock, flags);
    वापस -1;
  पूर्ण
पूर्ण

/********** RX queue pairs **********/

अटल पूर्णांक rx_give (amb_dev * dev, rx_in * rx, अचिन्हित अक्षर pool) अणु
  amb_rxq * rxq = &dev->rxq[pool];
  अचिन्हित दीर्घ flags;
  
  PRINTD (DBG_FLOW|DBG_RX, "rx_give %p[%hu]", dev, pool);
  
  spin_lock_irqsave (&rxq->lock, flags);
  
  अगर (rxq->pending < rxq->maximum) अणु
    PRINTD (DBG_RX, "RX in slot %p", rxq->in.ptr);

    *rxq->in.ptr = *rx;
    rxq->pending++;
    rxq->in.ptr = NEXTQ (rxq->in.ptr, rxq->in.start, rxq->in.limit);
    // hand over the RX buffer
    wr_mem (dev, दुरत्व(amb_mem, mb.adapter.rx_address[pool]), virt_to_bus (rxq->in.ptr));
    
    spin_unlock_irqrestore (&rxq->lock, flags);
    वापस 0;
  पूर्ण अन्यथा अणु
    spin_unlock_irqrestore (&rxq->lock, flags);
    वापस -1;
  पूर्ण
पूर्ण

अटल पूर्णांक rx_take (amb_dev * dev, अचिन्हित अक्षर pool) अणु
  amb_rxq * rxq = &dev->rxq[pool];
  अचिन्हित दीर्घ flags;
  
  PRINTD (DBG_FLOW|DBG_RX, "rx_take %p[%hu]", dev, pool);
  
  spin_lock_irqsave (&rxq->lock, flags);
  
  अगर (rxq->pending && (rxq->out.ptr->status || rxq->out.ptr->length)) अणु
    // deal with RX completion
    rx_complete (dev, rxq->out.ptr);
    // mark unused again
    rxq->out.ptr->status = 0;
    rxq->out.ptr->length = 0;
    // हटाओ item
    rxq->pending--;
    rxq->out.ptr = NEXTQ (rxq->out.ptr, rxq->out.start, rxq->out.limit);
    
    अगर (rxq->pending < rxq->low)
      rxq->low = rxq->pending;
    spin_unlock_irqrestore (&rxq->lock, flags);
    वापस 0;
  पूर्ण अन्यथा अणु
    अगर (!rxq->pending && rxq->buffers_wanted)
      rxq->emptied++;
    spin_unlock_irqrestore (&rxq->lock, flags);
    वापस -1;
  पूर्ण
पूर्ण

/********** RX Pool handling **********/

/* pre: buffers_wanted = 0, post: pending = 0 */
अटल व्योम drain_rx_pool (amb_dev * dev, अचिन्हित अक्षर pool) अणु
  amb_rxq * rxq = &dev->rxq[pool];
  
  PRINTD (DBG_FLOW|DBG_POOL, "drain_rx_pool %p %hu", dev, pool);
  
  अगर (test_bit (dead, &dev->flags))
    वापस;
  
  /* we are not quite like the fill pool routines as we cannot just
     हटाओ one buffer, we have to हटाओ all of them, but we might as
     well pretend... */
  अगर (rxq->pending > rxq->buffers_wanted) अणु
    command cmd;
    cmd.request = cpu_to_be32 (SRB_FLUSH_BUFFER_Q);
    cmd.args.flush.flags = cpu_to_be32 (pool << SRB_POOL_SHIFT);
    जबतक (command_करो (dev, &cmd))
      schedule();
    /* the pool may also be emptied via the पूर्णांकerrupt handler */
    जबतक (rxq->pending > rxq->buffers_wanted)
      अगर (rx_take (dev, pool))
	schedule();
  पूर्ण
  
  वापस;
पूर्ण

अटल व्योम drain_rx_pools (amb_dev * dev) अणु
  अचिन्हित अक्षर pool;
  
  PRINTD (DBG_FLOW|DBG_POOL, "drain_rx_pools %p", dev);
  
  क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool)
    drain_rx_pool (dev, pool);
पूर्ण

अटल व्योम fill_rx_pool (amb_dev * dev, अचिन्हित अक्षर pool,
                                 gfp_t priority)
अणु
  rx_in rx;
  amb_rxq * rxq;
  
  PRINTD (DBG_FLOW|DBG_POOL, "fill_rx_pool %p %hu %x", dev, pool, priority);
  
  अगर (test_bit (dead, &dev->flags))
    वापस;
  
  rxq = &dev->rxq[pool];
  जबतक (rxq->pending < rxq->maximum && rxq->pending < rxq->buffers_wanted) अणु
    
    काष्ठा sk_buff * skb = alloc_skb (rxq->buffer_size, priority);
    अगर (!skb) अणु
      PRINTD (DBG_SKB|DBG_POOL, "failed to allocate skb for RX pool %hu", pool);
      वापस;
    पूर्ण
    अगर (check_area (skb->data, skb->truesize)) अणु
      dev_kमुक्त_skb_any (skb);
      वापस;
    पूर्ण
    // cast needed as there is no %? क्रम poपूर्णांकer dअगरferences
    PRINTD (DBG_SKB, "allocated skb at %p, head %p, area %li",
	    skb, skb->head, (दीर्घ) skb_end_offset(skb));
    rx.handle = virt_to_bus (skb);
    rx.host_address = cpu_to_be32 (virt_to_bus (skb->data));
    अगर (rx_give (dev, &rx, pool))
      dev_kमुक्त_skb_any (skb);
    
  पूर्ण
  
  वापस;
पूर्ण

// top up all RX pools
अटल व्योम fill_rx_pools (amb_dev * dev) अणु
  अचिन्हित अक्षर pool;
  
  PRINTD (DBG_FLOW|DBG_POOL, "fill_rx_pools %p", dev);
  
  क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool)
    fill_rx_pool (dev, pool, GFP_ATOMIC);
  
  वापस;
पूर्ण

/********** enable host पूर्णांकerrupts **********/

अटल व्योम पूर्णांकerrupts_on (amb_dev * dev) अणु
  wr_plain (dev, दुरत्व(amb_mem, पूर्णांकerrupt_control),
	    rd_plain (dev, दुरत्व(amb_mem, पूर्णांकerrupt_control))
	    | AMB_INTERRUPT_BITS);
पूर्ण

/********** disable host पूर्णांकerrupts **********/

अटल व्योम पूर्णांकerrupts_off (amb_dev * dev) अणु
  wr_plain (dev, दुरत्व(amb_mem, पूर्णांकerrupt_control),
	    rd_plain (dev, दुरत्व(amb_mem, पूर्णांकerrupt_control))
	    &~ AMB_INTERRUPT_BITS);
पूर्ण

/********** पूर्णांकerrupt handling **********/

अटल irqवापस_t पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *dev_id) अणु
  amb_dev * dev = dev_id;
  
  PRINTD (DBG_IRQ|DBG_FLOW, "interrupt_handler: %p", dev_id);
  
  अणु
    u32 पूर्णांकerrupt = rd_plain (dev, दुरत्व(amb_mem, पूर्णांकerrupt));
  
    // क्रम us or someone अन्यथा sharing the same पूर्णांकerrupt
    अगर (!पूर्णांकerrupt) अणु
      PRINTD (DBG_IRQ, "irq not for me: %d", irq);
      वापस IRQ_NONE;
    पूर्ण
    
    // definitely क्रम us
    PRINTD (DBG_IRQ, "FYI: interrupt was %08x", पूर्णांकerrupt);
    wr_plain (dev, दुरत्व(amb_mem, पूर्णांकerrupt), -1);
  पूर्ण
  
  अणु
    अचिन्हित पूर्णांक irq_work = 0;
    अचिन्हित अक्षर pool;
    क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool)
      जबतक (!rx_take (dev, pool))
	++irq_work;
    जबतक (!tx_take (dev))
      ++irq_work;
  
    अगर (irq_work) अणु
      fill_rx_pools (dev);

      PRINTD (DBG_IRQ, "work done: %u", irq_work);
    पूर्ण अन्यथा अणु
      PRINTD (DBG_IRQ|DBG_WARN, "no work done");
    पूर्ण
  पूर्ण
  
  PRINTD (DBG_IRQ|DBG_FLOW, "interrupt_handler done: %p", dev_id);
  वापस IRQ_HANDLED;
पूर्ण

/********** make rate (not quite as much fun as Horizon) **********/

अटल पूर्णांक make_rate (अचिन्हित पूर्णांक rate, rounding r,
		      u16 * bits, अचिन्हित पूर्णांक * actual) अणु
  अचिन्हित अक्षर exp = -1; // hush gcc
  अचिन्हित पूर्णांक man = -1;  // hush gcc
  
  PRINTD (DBG_FLOW|DBG_QOS, "make_rate %u", rate);
  
  // rates in cells per second, ITU क्रमmat (nasty 16-bit भग्नing-poपूर्णांक)
  // given 5-bit e and 9-bit m:
  // rate = EITHER (1+m/2^9)*2^e    OR 0
  // bits = EITHER 1<<14 | e<<9 | m OR 0
  // (bit 15 is "reserved", bit 14 "non-zero")
  // smallest rate is 0 (special representation)
  // largest rate is (1+511/512)*2^31 = 4290772992 (< 2^32-1)
  // smallest non-zero rate is (1+0/512)*2^0 = 1 (> 0)
  // simple algorithm:
  // find position of top bit, this gives e
  // हटाओ top bit and shअगरt (rounding अगर feeling clever) by 9-e
  
  // ucode bug: please करोn't set bit 14! so 0 rate not representable
  
  अगर (rate > 0xffc00000U) अणु
    // larger than largest representable rate
    
    अगर (r == round_up) अणु
	वापस -EINVAL;
    पूर्ण अन्यथा अणु
      exp = 31;
      man = 511;
    पूर्ण
    
  पूर्ण अन्यथा अगर (rate) अणु
    // representable rate
    
    exp = 31;
    man = rate;
    
    // invariant: rate = man*2^(exp-31)
    जबतक (!(man & (1<<31))) अणु
      exp = exp - 1;
      man = man<<1;
    पूर्ण
    
    // man has top bit set
    // rate = (2^31+(man-2^31))*2^(exp-31)
    // rate = (1+(man-2^31)/2^31)*2^exp
    man = man<<1;
    man &= 0xffffffffU; // a nop on 32-bit प्रणालीs
    // rate = (1+man/2^32)*2^exp
    
    // exp is in the range 0 to 31, man is in the range 0 to 2^32-1
    // समय to lose signअगरicance... we want m in the range 0 to 2^9-1
    // rounding presents a minor problem... we first decide which way
    // we are rounding (based on given rounding direction and possibly
    // the bits of the mantissa that are to be discarded).
    
    चयन (r) अणु
      हाल round_करोwn: अणु
	// just truncate
	man = man>>(32-9);
	अवरोध;
      पूर्ण
      हाल round_up: अणु
	// check all bits that we are discarding
	अगर (man & (~0U>>9)) अणु
	  man = (man>>(32-9)) + 1;
	  अगर (man == (1<<9)) अणु
	    // no need to check क्रम round up outside of range
	    man = 0;
	    exp += 1;
	  पूर्ण
	पूर्ण अन्यथा अणु
	  man = (man>>(32-9));
	पूर्ण
	अवरोध;
      पूर्ण
      हाल round_nearest: अणु
	// check msb that we are discarding
	अगर (man & (1<<(32-9-1))) अणु
	  man = (man>>(32-9)) + 1;
	  अगर (man == (1<<9)) अणु
	    // no need to check क्रम round up outside of range
	    man = 0;
	    exp += 1;
	  पूर्ण
	पूर्ण अन्यथा अणु
	  man = (man>>(32-9));
	पूर्ण
	अवरोध;
      पूर्ण
    पूर्ण
    
  पूर्ण अन्यथा अणु
    // zero rate - not representable
    
    अगर (r == round_करोwn) अणु
      वापस -EINVAL;
    पूर्ण अन्यथा अणु
      exp = 0;
      man = 0;
    पूर्ण
    
  पूर्ण
  
  PRINTD (DBG_QOS, "rate: man=%u, exp=%hu", man, exp);
  
  अगर (bits)
    *bits = /* (1<<14) | */ (exp<<9) | man;
  
  अगर (actual)
    *actual = (exp >= 9)
      ? (1 << exp) + (man << (exp-9))
      : (1 << exp) + ((man + (1<<(9-exp-1))) >> (9-exp));
  
  वापस 0;
पूर्ण

/********** Linux ATM Operations **********/

// some are not yet implemented जबतक others करो not make sense क्रम
// this device

/********** Open a VC **********/

अटल पूर्णांक amb_खोलो (काष्ठा aपंचांग_vcc * aपंचांग_vcc)
अणु
  पूर्णांक error;
  
  काष्ठा aपंचांग_qos * qos;
  काष्ठा aपंचांग_trafprm * txtp;
  काष्ठा aपंचांग_trafprm * rxtp;
  u16 tx_rate_bits = -1; // hush gcc
  u16 tx_vc_bits = -1; // hush gcc
  u16 tx_frame_bits = -1; // hush gcc
  
  amb_dev * dev = AMB_DEV(aपंचांग_vcc->dev);
  amb_vcc * vcc;
  अचिन्हित अक्षर pool = -1; // hush gcc
  लघु vpi = aपंचांग_vcc->vpi;
  पूर्णांक vci = aपंचांग_vcc->vci;
  
  PRINTD (DBG_FLOW|DBG_VCC, "amb_open %x %x", vpi, vci);
  
#अगर_घोषित ATM_VPI_UNSPEC
  // UNSPEC is deprecated, हटाओ this code eventually
  अगर (vpi == ATM_VPI_UNSPEC || vci == ATM_VCI_UNSPEC) अणु
    PRINTK (KERN_WARNING, "rejecting open with unspecified VPI/VCI (deprecated)");
    वापस -EINVAL;
  पूर्ण
#पूर्ण_अगर
  
  अगर (!(0 <= vpi && vpi < (1<<NUM_VPI_BITS) &&
	0 <= vci && vci < (1<<NUM_VCI_BITS))) अणु
    PRINTD (DBG_WARN|DBG_VCC, "VPI/VCI out of range: %hd/%d", vpi, vci);
    वापस -EINVAL;
  पूर्ण
  
  qos = &aपंचांग_vcc->qos;
  
  अगर (qos->aal != ATM_AAL5) अणु
    PRINTD (DBG_QOS, "AAL not supported");
    वापस -EINVAL;
  पूर्ण
  
  // traffic parameters
  
  PRINTD (DBG_QOS, "TX:");
  txtp = &qos->txtp;
  अगर (txtp->traffic_class != ATM_NONE) अणु
    चयन (txtp->traffic_class) अणु
      हाल ATM_UBR: अणु
	// we take "the PCR" as a rate-cap
	पूर्णांक pcr = aपंचांग_pcr_goal (txtp);
	अगर (!pcr) अणु
	  // no rate cap
	  tx_rate_bits = 0;
	  tx_vc_bits = TX_UBR;
	  tx_frame_bits = TX_FRAME_NOTCAP;
	पूर्ण अन्यथा अणु
	  rounding r;
	  अगर (pcr < 0) अणु
	    r = round_करोwn;
	    pcr = -pcr;
	  पूर्ण अन्यथा अणु
	    r = round_up;
	  पूर्ण
	  error = make_rate (pcr, r, &tx_rate_bits, शून्य);
	  अगर (error)
	    वापस error;
	  tx_vc_bits = TX_UBR_CAPPED;
	  tx_frame_bits = TX_FRAME_CAPPED;
	पूर्ण
	अवरोध;
      पूर्ण
#अगर 0
      हाल ATM_ABR: अणु
	pcr = aपंचांग_pcr_goal (txtp);
	PRINTD (DBG_QOS, "pcr goal = %d", pcr);
	अवरोध;
      पूर्ण
#पूर्ण_अगर
      शेष: अणु
	// PRINTD (DBG_QOS, "request for non-UBR/ABR denied");
	PRINTD (DBG_QOS, "request for non-UBR denied");
	वापस -EINVAL;
      पूर्ण
    पूर्ण
    PRINTD (DBG_QOS, "tx_rate_bits=%hx, tx_vc_bits=%hx",
	    tx_rate_bits, tx_vc_bits);
  पूर्ण
  
  PRINTD (DBG_QOS, "RX:");
  rxtp = &qos->rxtp;
  अगर (rxtp->traffic_class == ATM_NONE) अणु
    // करो nothing
  पूर्ण अन्यथा अणु
    // choose an RX pool (arranged in increasing size)
    क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool)
      अगर ((अचिन्हित पूर्णांक) rxtp->max_sdu <= dev->rxq[pool].buffer_size) अणु
	PRINTD (DBG_VCC|DBG_QOS|DBG_POOL, "chose pool %hu (max_sdu %u <= %u)",
		pool, rxtp->max_sdu, dev->rxq[pool].buffer_size);
	अवरोध;
      पूर्ण
    अगर (pool == NUM_RX_POOLS) अणु
      PRINTD (DBG_WARN|DBG_VCC|DBG_QOS|DBG_POOL,
	      "no pool suitable for VC (RX max_sdu %d is too large)",
	      rxtp->max_sdu);
      वापस -EINVAL;
    पूर्ण
    
    चयन (rxtp->traffic_class) अणु
      हाल ATM_UBR: अणु
	अवरोध;
      पूर्ण
#अगर 0
      हाल ATM_ABR: अणु
	pcr = aपंचांग_pcr_goal (rxtp);
	PRINTD (DBG_QOS, "pcr goal = %d", pcr);
	अवरोध;
      पूर्ण
#पूर्ण_अगर
      शेष: अणु
	// PRINTD (DBG_QOS, "request for non-UBR/ABR denied");
	PRINTD (DBG_QOS, "request for non-UBR denied");
	वापस -EINVAL;
      पूर्ण
    पूर्ण
  पूर्ण
  
  // get space क्रम our vcc stuff
  vcc = kदो_स्मृति (माप(amb_vcc), GFP_KERNEL);
  अगर (!vcc) अणु
    PRINTK (KERN_ERR, "out of memory!");
    वापस -ENOMEM;
  पूर्ण
  aपंचांग_vcc->dev_data = (व्योम *) vcc;
  
  // no failures beyond this poपूर्णांक
  
  // we are not really "immediately beक्रमe allocating the connection
  // identअगरier in hardware", but it will just have to करो!
  set_bit(ATM_VF_ADDR,&aपंचांग_vcc->flags);
  
  अगर (txtp->traffic_class != ATM_NONE) अणु
    command cmd;
    
    vcc->tx_frame_bits = tx_frame_bits;
    
    mutex_lock(&dev->vcc_sf);
    अगर (dev->rxer[vci]) अणु
      // RXer on the channel alपढ़ोy, just modअगरy rate...
      cmd.request = cpu_to_be32 (SRB_MODIFY_VC_RATE);
      cmd.args.modअगरy_rate.vc = cpu_to_be32 (vci);  // vpi 0
      cmd.args.modअगरy_rate.rate = cpu_to_be32 (tx_rate_bits << SRB_RATE_SHIFT);
      जबतक (command_करो (dev, &cmd))
	schedule();
      // ... and TX flags, preserving the RX pool
      cmd.request = cpu_to_be32 (SRB_MODIFY_VC_FLAGS);
      cmd.args.modअगरy_flags.vc = cpu_to_be32 (vci);  // vpi 0
      cmd.args.modअगरy_flags.flags = cpu_to_be32
	( (AMB_VCC(dev->rxer[vci])->rx_info.pool << SRB_POOL_SHIFT)
	  | (tx_vc_bits << SRB_FLAGS_SHIFT) );
      जबतक (command_करो (dev, &cmd))
	schedule();
    पूर्ण अन्यथा अणु
      // no RXer on the channel, just खोलो (with pool zero)
      cmd.request = cpu_to_be32 (SRB_OPEN_VC);
      cmd.args.खोलो.vc = cpu_to_be32 (vci);  // vpi 0
      cmd.args.खोलो.flags = cpu_to_be32 (tx_vc_bits << SRB_FLAGS_SHIFT);
      cmd.args.खोलो.rate = cpu_to_be32 (tx_rate_bits << SRB_RATE_SHIFT);
      जबतक (command_करो (dev, &cmd))
	schedule();
    पूर्ण
    dev->txer[vci].tx_present = 1;
    mutex_unlock(&dev->vcc_sf);
  पूर्ण
  
  अगर (rxtp->traffic_class != ATM_NONE) अणु
    command cmd;
    
    vcc->rx_info.pool = pool;
    
    mutex_lock(&dev->vcc_sf);
    /* grow RX buffer pool */
    अगर (!dev->rxq[pool].buffers_wanted)
      dev->rxq[pool].buffers_wanted = rx_lats;
    dev->rxq[pool].buffers_wanted += 1;
    fill_rx_pool (dev, pool, GFP_KERNEL);
    
    अगर (dev->txer[vci].tx_present) अणु
      // TXer on the channel alपढ़ोy
      // चयन (from pool zero) to this pool, preserving the TX bits
      cmd.request = cpu_to_be32 (SRB_MODIFY_VC_FLAGS);
      cmd.args.modअगरy_flags.vc = cpu_to_be32 (vci);  // vpi 0
      cmd.args.modअगरy_flags.flags = cpu_to_be32
	( (pool << SRB_POOL_SHIFT)
	  | (dev->txer[vci].tx_vc_bits << SRB_FLAGS_SHIFT) );
    पूर्ण अन्यथा अणु
      // no TXer on the channel, खोलो the VC (with no rate info)
      cmd.request = cpu_to_be32 (SRB_OPEN_VC);
      cmd.args.खोलो.vc = cpu_to_be32 (vci);  // vpi 0
      cmd.args.खोलो.flags = cpu_to_be32 (pool << SRB_POOL_SHIFT);
      cmd.args.खोलो.rate = cpu_to_be32 (0);
    पूर्ण
    जबतक (command_करो (dev, &cmd))
      schedule();
    // this link allows RX frames through
    dev->rxer[vci] = aपंचांग_vcc;
    mutex_unlock(&dev->vcc_sf);
  पूर्ण
  
  // indicate पढ़ोiness
  set_bit(ATM_VF_READY,&aपंचांग_vcc->flags);
  
  वापस 0;
पूर्ण

/********** Close a VC **********/

अटल व्योम amb_बंद (काष्ठा aपंचांग_vcc * aपंचांग_vcc) अणु
  amb_dev * dev = AMB_DEV (aपंचांग_vcc->dev);
  amb_vcc * vcc = AMB_VCC (aपंचांग_vcc);
  u16 vci = aपंचांग_vcc->vci;
  
  PRINTD (DBG_VCC|DBG_FLOW, "amb_close");
  
  // indicate unपढ़ोiness
  clear_bit(ATM_VF_READY,&aपंचांग_vcc->flags);
  
  // disable TXing
  अगर (aपंचांग_vcc->qos.txtp.traffic_class != ATM_NONE) अणु
    command cmd;
    
    mutex_lock(&dev->vcc_sf);
    अगर (dev->rxer[vci]) अणु
      // RXer still on the channel, just modअगरy rate... XXX not really needed
      cmd.request = cpu_to_be32 (SRB_MODIFY_VC_RATE);
      cmd.args.modअगरy_rate.vc = cpu_to_be32 (vci);  // vpi 0
      cmd.args.modअगरy_rate.rate = cpu_to_be32 (0);
      // ... and clear TX rate flags (XXX to stop RM cell output?), preserving RX pool
    पूर्ण अन्यथा अणु
      // no RXer on the channel, बंद channel
      cmd.request = cpu_to_be32 (SRB_CLOSE_VC);
      cmd.args.बंद.vc = cpu_to_be32 (vci); // vpi 0
    पूर्ण
    dev->txer[vci].tx_present = 0;
    जबतक (command_करो (dev, &cmd))
      schedule();
    mutex_unlock(&dev->vcc_sf);
  पूर्ण
  
  // disable RXing
  अगर (aपंचांग_vcc->qos.rxtp.traffic_class != ATM_NONE) अणु
    command cmd;
    
    // this is (the?) one reason why we need the amb_vcc काष्ठा
    अचिन्हित अक्षर pool = vcc->rx_info.pool;
    
    mutex_lock(&dev->vcc_sf);
    अगर (dev->txer[vci].tx_present) अणु
      // TXer still on the channel, just go to pool zero XXX not really needed
      cmd.request = cpu_to_be32 (SRB_MODIFY_VC_FLAGS);
      cmd.args.modअगरy_flags.vc = cpu_to_be32 (vci);  // vpi 0
      cmd.args.modअगरy_flags.flags = cpu_to_be32
	(dev->txer[vci].tx_vc_bits << SRB_FLAGS_SHIFT);
    पूर्ण अन्यथा अणु
      // no TXer on the channel, बंद the VC
      cmd.request = cpu_to_be32 (SRB_CLOSE_VC);
      cmd.args.बंद.vc = cpu_to_be32 (vci); // vpi 0
    पूर्ण
    // क्रमget the rxer - no more skbs will be pushed
    अगर (aपंचांग_vcc != dev->rxer[vci])
      PRINTK (KERN_ERR, "%s vcc=%p rxer[vci]=%p",
	      "arghhh! we're going to die!",
	      vcc, dev->rxer[vci]);
    dev->rxer[vci] = शून्य;
    जबतक (command_करो (dev, &cmd))
      schedule();
    
    /* shrink RX buffer pool */
    dev->rxq[pool].buffers_wanted -= 1;
    अगर (dev->rxq[pool].buffers_wanted == rx_lats) अणु
      dev->rxq[pool].buffers_wanted = 0;
      drain_rx_pool (dev, pool);
    पूर्ण
    mutex_unlock(&dev->vcc_sf);
  पूर्ण
  
  // मुक्त our काष्ठाure
  kमुक्त (vcc);
  
  // say the VPI/VCI is मुक्त again
  clear_bit(ATM_VF_ADDR,&aपंचांग_vcc->flags);

  वापस;
पूर्ण

/********** Send **********/

अटल पूर्णांक amb_send (काष्ठा aपंचांग_vcc * aपंचांग_vcc, काष्ठा sk_buff * skb) अणु
  amb_dev * dev = AMB_DEV(aपंचांग_vcc->dev);
  amb_vcc * vcc = AMB_VCC(aपंचांग_vcc);
  u16 vc = aपंचांग_vcc->vci;
  अचिन्हित पूर्णांक tx_len = skb->len;
  अचिन्हित अक्षर * tx_data = skb->data;
  tx_simple * tx_descr;
  tx_in tx;
  
  अगर (test_bit (dead, &dev->flags))
    वापस -EIO;
  
  PRINTD (DBG_FLOW|DBG_TX, "amb_send vc %x data %p len %u",
	  vc, tx_data, tx_len);
  
  dump_skb (">>>", vc, skb);
  
  अगर (!dev->txer[vc].tx_present) अणु
    PRINTK (KERN_ERR, "attempt to send on RX-only VC %x", vc);
    वापस -EBADFD;
  पूर्ण
  
  // this is a driver निजी field so we have to set it ourselves,
  // despite the fact that we are _required_ to use it to check क्रम a
  // pop function
  ATM_SKB(skb)->vcc = aपंचांग_vcc;
  
  अगर (skb->len > (माप_प्रकार) aपंचांग_vcc->qos.txtp.max_sdu) अणु
    PRINTK (KERN_ERR, "sk_buff length greater than agreed max_sdu, dropping...");
    वापस -EIO;
  पूर्ण
  
  अगर (check_area (skb->data, skb->len)) अणु
    atomic_inc(&aपंचांग_vcc->stats->tx_err);
    वापस -ENOMEM; // ?
  पूर्ण
  
  // allocate memory क्रम fragments
  tx_descr = kदो_स्मृति (माप(tx_simple), GFP_KERNEL);
  अगर (!tx_descr) अणु
    PRINTK (KERN_ERR, "could not allocate TX descriptor");
    वापस -ENOMEM;
  पूर्ण
  अगर (check_area (tx_descr, माप(tx_simple))) अणु
    kमुक्त (tx_descr);
    वापस -ENOMEM;
  पूर्ण
  PRINTD (DBG_TX, "fragment list allocated at %p", tx_descr);
  
  tx_descr->skb = skb;
  
  tx_descr->tx_frag.bytes = cpu_to_be32 (tx_len);
  tx_descr->tx_frag.address = cpu_to_be32 (virt_to_bus (tx_data));
  
  tx_descr->tx_frag_end.handle = virt_to_bus (tx_descr);
  tx_descr->tx_frag_end.vc = 0;
  tx_descr->tx_frag_end.next_descriptor_length = 0;
  tx_descr->tx_frag_end.next_descriptor = 0;
#अगर_घोषित AMB_NEW_MICROCODE
  tx_descr->tx_frag_end.cpcs_uu = 0;
  tx_descr->tx_frag_end.cpi = 0;
  tx_descr->tx_frag_end.pad = 0;
#पूर्ण_अगर
  
  tx.vc = cpu_to_be16 (vcc->tx_frame_bits | vc);
  tx.tx_descr_length = cpu_to_be16 (माप(tx_frag)+माप(tx_frag_end));
  tx.tx_descr_addr = cpu_to_be32 (virt_to_bus (&tx_descr->tx_frag));
  
  जबतक (tx_give (dev, &tx))
    schedule();
  वापस 0;
पूर्ण

/********** Change QoS on a VC **********/

// पूर्णांक amb_change_qos (काष्ठा aपंचांग_vcc * aपंचांग_vcc, काष्ठा aपंचांग_qos * qos, पूर्णांक flags);

/********** Free RX Socket Buffer **********/

#अगर 0
अटल व्योम amb_मुक्त_rx_skb (काष्ठा aपंचांग_vcc * aपंचांग_vcc, काष्ठा sk_buff * skb) अणु
  amb_dev * dev = AMB_DEV (aपंचांग_vcc->dev);
  amb_vcc * vcc = AMB_VCC (aपंचांग_vcc);
  अचिन्हित अक्षर pool = vcc->rx_info.pool;
  rx_in rx;
  
  // This may be unsafe क्रम various reasons that I cannot really guess
  // at. However, I note that the ATM layer calls kमुक्त_skb rather
  // than dev_kमुक्त_skb at this poपूर्णांक so we are least covered as far
  // as buffer locking goes. There may be bugs अगर pcap clones RX skbs.

  PRINTD (DBG_FLOW|DBG_SKB, "amb_rx_free skb %p (atm_vcc %p, vcc %p)",
	  skb, aपंचांग_vcc, vcc);
  
  rx.handle = virt_to_bus (skb);
  rx.host_address = cpu_to_be32 (virt_to_bus (skb->data));
  
  skb->data = skb->head;
  skb_reset_tail_poपूर्णांकer(skb);
  skb->len = 0;
  
  अगर (!rx_give (dev, &rx, pool)) अणु
    // success
    PRINTD (DBG_SKB|DBG_POOL, "recycled skb for pool %hu", pool);
    वापस;
  पूर्ण
  
  // just करो what the ATM layer would have करोne
  dev_kमुक्त_skb_any (skb);
  
  वापस;
पूर्ण
#पूर्ण_अगर

/********** Proc File Output **********/

अटल पूर्णांक amb_proc_पढ़ो (काष्ठा aपंचांग_dev * aपंचांग_dev, loff_t * pos, अक्षर * page) अणु
  amb_dev * dev = AMB_DEV (aपंचांग_dev);
  पूर्णांक left = *pos;
  अचिन्हित अक्षर pool;
  
  PRINTD (DBG_FLOW, "amb_proc_read");
  
  /* more diagnostics here? */
  
  अगर (!left--) अणु
    amb_stats * s = &dev->stats;
    वापस प्र_लिखो (page,
		    "frames: TX OK %lu, RX OK %lu, RX bad %lu "
		    "(CRC %lu, long %lu, aborted %lu, unused %lu).\n",
		    s->tx_ok, s->rx.ok, s->rx.error,
		    s->rx.badcrc, s->rx.tooदीर्घ,
		    s->rx.पातed, s->rx.unused);
  पूर्ण
  
  अगर (!left--) अणु
    amb_cq * c = &dev->cq;
    वापस प्र_लिखो (page, "cmd queue [cur/hi/max]: %u/%u/%u. ",
		    c->pending, c->high, c->maximum);
  पूर्ण
  
  अगर (!left--) अणु
    amb_txq * t = &dev->txq;
    वापस प्र_लिखो (page, "TX queue [cur/max high full]: %u/%u %u %u.\n",
		    t->pending, t->maximum, t->high, t->filled);
  पूर्ण
  
  अगर (!left--) अणु
    अचिन्हित पूर्णांक count = प्र_लिखो (page, "RX queues [cur/max/req low empty]:");
    क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool) अणु
      amb_rxq * r = &dev->rxq[pool];
      count += प्र_लिखो (page+count, " %u/%u/%u %u %u",
			r->pending, r->maximum, r->buffers_wanted, r->low, r->emptied);
    पूर्ण
    count += प्र_लिखो (page+count, ".\n");
    वापस count;
  पूर्ण
  
  अगर (!left--) अणु
    अचिन्हित पूर्णांक count = प्र_लिखो (page, "RX buffer sizes:");
    क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool) अणु
      amb_rxq * r = &dev->rxq[pool];
      count += प्र_लिखो (page+count, " %u", r->buffer_size);
    पूर्ण
    count += प्र_लिखो (page+count, ".\n");
    वापस count;
  पूर्ण
  
#अगर 0
  अगर (!left--) अणु
    // suni block etc?
  पूर्ण
#पूर्ण_अगर
  
  वापस 0;
पूर्ण

/********** Operation Structure **********/

अटल स्थिर काष्ठा aपंचांगdev_ops amb_ops = अणु
  .खोलो         = amb_खोलो,
  .बंद	= amb_बंद,
  .send         = amb_send,
  .proc_पढ़ो	= amb_proc_पढ़ो,
  .owner	= THIS_MODULE,
पूर्ण;

/********** housekeeping **********/
अटल व्योम करो_housekeeping (काष्ठा समयr_list *t) अणु
  amb_dev * dev = from_समयr(dev, t, housekeeping);
  
  // could collect device-specअगरic (not driver/aपंचांग-linux) stats here
      
  // last resort refill once every ten seconds
  fill_rx_pools (dev);
  mod_समयr(&dev->housekeeping, jअगरfies + 10*HZ);
  
  वापस;
पूर्ण

/********** creation of communication queues **********/

अटल पूर्णांक create_queues(amb_dev *dev, अचिन्हित पूर्णांक cmds, अचिन्हित पूर्णांक txs,
			 अचिन्हित पूर्णांक *rxs, अचिन्हित पूर्णांक *rx_buffer_sizes)
अणु
  अचिन्हित अक्षर pool;
  माप_प्रकार total = 0;
  व्योम * memory;
  व्योम * limit;
  
  PRINTD (DBG_FLOW, "create_queues %p", dev);
  
  total += cmds * माप(command);
  
  total += txs * (माप(tx_in) + माप(tx_out));
  
  क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool)
    total += rxs[pool] * (माप(rx_in) + माप(rx_out));
  
  memory = kदो_स्मृति (total, GFP_KERNEL);
  अगर (!memory) अणु
    PRINTK (KERN_ERR, "could not allocate queues");
    वापस -ENOMEM;
  पूर्ण
  अगर (check_area (memory, total)) अणु
    PRINTK (KERN_ERR, "queues allocated in nasty area");
    kमुक्त (memory);
    वापस -ENOMEM;
  पूर्ण
  
  limit = memory + total;
  PRINTD (DBG_INIT, "queues from %p to %p", memory, limit);
  
  PRINTD (DBG_CMD, "command queue at %p", memory);
  
  अणु
    command * cmd = memory;
    amb_cq * cq = &dev->cq;
    
    cq->pending = 0;
    cq->high = 0;
    cq->maximum = cmds - 1;
    
    cq->ptrs.start = cmd;
    cq->ptrs.in = cmd;
    cq->ptrs.out = cmd;
    cq->ptrs.limit = cmd + cmds;
    
    memory = cq->ptrs.limit;
  पूर्ण
  
  PRINTD (DBG_TX, "TX queue pair at %p", memory);
  
  अणु
    tx_in * in = memory;
    tx_out * out;
    amb_txq * txq = &dev->txq;
    
    txq->pending = 0;
    txq->high = 0;
    txq->filled = 0;
    txq->maximum = txs - 1;
    
    txq->in.start = in;
    txq->in.ptr = in;
    txq->in.limit = in + txs;
    
    memory = txq->in.limit;
    out = memory;
    
    txq->out.start = out;
    txq->out.ptr = out;
    txq->out.limit = out + txs;
    
    memory = txq->out.limit;
  पूर्ण
  
  PRINTD (DBG_RX, "RX queue pairs at %p", memory);
  
  क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool) अणु
    rx_in * in = memory;
    rx_out * out;
    amb_rxq * rxq = &dev->rxq[pool];
    
    rxq->buffer_size = rx_buffer_sizes[pool];
    rxq->buffers_wanted = 0;
    
    rxq->pending = 0;
    rxq->low = rxs[pool] - 1;
    rxq->emptied = 0;
    rxq->maximum = rxs[pool] - 1;
    
    rxq->in.start = in;
    rxq->in.ptr = in;
    rxq->in.limit = in + rxs[pool];
    
    memory = rxq->in.limit;
    out = memory;
    
    rxq->out.start = out;
    rxq->out.ptr = out;
    rxq->out.limit = out + rxs[pool];
    
    memory = rxq->out.limit;
  पूर्ण
  
  अगर (memory == limit) अणु
    वापस 0;
  पूर्ण अन्यथा अणु
    PRINTK (KERN_ERR, "bad queue alloc %p != %p (tell maintainer)", memory, limit);
    kमुक्त (limit - total);
    वापस -ENOMEM;
  पूर्ण
  
पूर्ण

/********** deकाष्ठाion of communication queues **********/

अटल व्योम destroy_queues (amb_dev * dev) अणु
  // all queues assumed empty
  व्योम * memory = dev->cq.ptrs.start;
  // includes txq.in, txq.out, rxq[].in and rxq[].out
  
  PRINTD (DBG_FLOW, "destroy_queues %p", dev);
  
  PRINTD (DBG_INIT, "freeing queues at %p", memory);
  kमुक्त (memory);
  
  वापस;
पूर्ण

/********** basic loader commands and error handling **********/
// centisecond समयouts - guessing away here
अटल अचिन्हित पूर्णांक command_समयouts [] = अणु
	[host_memory_test]     = 15,
	[पढ़ो_adapter_memory]  = 2,
	[ग_लिखो_adapter_memory] = 2,
	[adapter_start]        = 50,
	[get_version_number]   = 10,
	[पूर्णांकerrupt_host]       = 1,
	[flash_erase_sector]   = 1,
	[adap_करोwnload_block]  = 1,
	[adap_erase_flash]     = 1,
	[adap_run_in_iram]     = 1,
	[adap_end_करोwnload]    = 1
पूर्ण;


अटल अचिन्हित पूर्णांक command_successes [] = अणु
	[host_memory_test]     = COMMAND_PASSED_TEST,
	[पढ़ो_adapter_memory]  = COMMAND_READ_DATA_OK,
	[ग_लिखो_adapter_memory] = COMMAND_WRITE_DATA_OK,
	[adapter_start]        = COMMAND_COMPLETE,
	[get_version_number]   = COMMAND_COMPLETE,
	[पूर्णांकerrupt_host]       = COMMAND_COMPLETE,
	[flash_erase_sector]   = COMMAND_COMPLETE,
	[adap_करोwnload_block]  = COMMAND_COMPLETE,
	[adap_erase_flash]     = COMMAND_COMPLETE,
	[adap_run_in_iram]     = COMMAND_COMPLETE,
	[adap_end_करोwnload]    = COMMAND_COMPLETE
पूर्ण;
  
अटल  पूर्णांक decode_loader_result (loader_command cmd, u32 result)
अणु
	पूर्णांक res;
	स्थिर अक्षर *msg;

	अगर (result == command_successes[cmd])
		वापस 0;

	चयन (result) अणु
		हाल BAD_COMMAND:
			res = -EINVAL;
			msg = "bad command";
			अवरोध;
		हाल COMMAND_IN_PROGRESS:
			res = -ETIMEDOUT;
			msg = "command in progress";
			अवरोध;
		हाल COMMAND_PASSED_TEST:
			res = 0;
			msg = "command passed test";
			अवरोध;
		हाल COMMAND_FAILED_TEST:
			res = -EIO;
			msg = "command failed test";
			अवरोध;
		हाल COMMAND_READ_DATA_OK:
			res = 0;
			msg = "command read data ok";
			अवरोध;
		हाल COMMAND_READ_BAD_ADDRESS:
			res = -EINVAL;
			msg = "command read bad address";
			अवरोध;
		हाल COMMAND_WRITE_DATA_OK:
			res = 0;
			msg = "command write data ok";
			अवरोध;
		हाल COMMAND_WRITE_BAD_ADDRESS:
			res = -EINVAL;
			msg = "command write bad address";
			अवरोध;
		हाल COMMAND_WRITE_FLASH_FAILURE:
			res = -EIO;
			msg = "command write flash failure";
			अवरोध;
		हाल COMMAND_COMPLETE:
			res = 0;
			msg = "command complete";
			अवरोध;
		हाल COMMAND_FLASH_ERASE_FAILURE:
			res = -EIO;
			msg = "command flash erase failure";
			अवरोध;
		हाल COMMAND_WRITE_BAD_DATA:
			res = -EINVAL;
			msg = "command write bad data";
			अवरोध;
		शेष:
			res = -EINVAL;
			msg = "unknown error";
			PRINTD (DBG_LOAD|DBG_ERR,
				"decode_loader_result got %d=%x !",
				result, result);
			अवरोध;
	पूर्ण

	PRINTK (KERN_ERR, "%s", msg);
	वापस res;
पूर्ण

अटल पूर्णांक करो_loader_command(अस्थिर loader_block *lb, स्थिर amb_dev *dev,
			     loader_command cmd)
अणु
  
  अचिन्हित दीर्घ समयout;
  
  PRINTD (DBG_FLOW|DBG_LOAD, "do_loader_command");
  
  /* करो a command
     
     Set the वापस value to zero, set the command type and set the
     valid entry to the right magic value. The payload is alपढ़ोy
     correctly byte-ordered so we leave it alone. Hit the करोorbell
     with the bus address of this काष्ठाure.
     
  */
  
  lb->result = 0;
  lb->command = cpu_to_be32 (cmd);
  lb->valid = cpu_to_be32 (DMA_VALID);
  // dump_रेजिस्टरs (dev);
  // dump_loader_block (lb);
  wr_mem (dev, दुरत्व(amb_mem, करोorbell), virt_to_bus (lb) & ~onegigmask);
  
  समयout = command_समयouts[cmd] * 10;
  
  जबतक (!lb->result || lb->result == cpu_to_be32 (COMMAND_IN_PROGRESS))
    अगर (समयout) अणु
      समयout = msleep_पूर्णांकerruptible(समयout);
    पूर्ण अन्यथा अणु
      PRINTD (DBG_LOAD|DBG_ERR, "command %d timed out", cmd);
      dump_रेजिस्टरs (dev);
      dump_loader_block (lb);
      वापस -ETIMEDOUT;
    पूर्ण
  
  अगर (cmd == adapter_start) अणु
    // रुको क्रम start command to acknowledge...
    समयout = 100;
    जबतक (rd_plain (dev, दुरत्व(amb_mem, करोorbell)))
      अगर (समयout) अणु
	समयout = msleep_पूर्णांकerruptible(समयout);
      पूर्ण अन्यथा अणु
	PRINTD (DBG_LOAD|DBG_ERR, "start command did not clear doorbell, res=%08x",
		be32_to_cpu (lb->result));
	dump_रेजिस्टरs (dev);
	वापस -ETIMEDOUT;
      पूर्ण
    वापस 0;
  पूर्ण अन्यथा अणु
    वापस decode_loader_result (cmd, be32_to_cpu (lb->result));
  पूर्ण
  
पूर्ण

/* loader: determine loader version */

अटल पूर्णांक get_loader_version(loader_block *lb, स्थिर amb_dev *dev,
			      u32 *version)
अणु
  पूर्णांक res;
  
  PRINTD (DBG_FLOW|DBG_LOAD, "get_loader_version");
  
  res = करो_loader_command (lb, dev, get_version_number);
  अगर (res)
    वापस res;
  अगर (version)
    *version = be32_to_cpu (lb->payload.version);
  वापस 0;
पूर्ण

/* loader: ग_लिखो memory data blocks */

अटल पूर्णांक loader_ग_लिखो(loader_block *lb, स्थिर amb_dev *dev,
			स्थिर काष्ठा ihex_binrec *rec)
अणु
  transfer_block * tb = &lb->payload.transfer;
  
  PRINTD (DBG_FLOW|DBG_LOAD, "loader_write");

  tb->address = rec->addr;
  tb->count = cpu_to_be32(be16_to_cpu(rec->len) / 4);
  स_नकल(tb->data, rec->data, be16_to_cpu(rec->len));
  वापस करो_loader_command (lb, dev, ग_लिखो_adapter_memory);
पूर्ण

/* loader: verअगरy memory data blocks */

अटल पूर्णांक loader_verअगरy(loader_block *lb, स्थिर amb_dev *dev,
			 स्थिर काष्ठा ihex_binrec *rec)
अणु
  transfer_block * tb = &lb->payload.transfer;
  पूर्णांक res;
  
  PRINTD (DBG_FLOW|DBG_LOAD, "loader_verify");
  
  tb->address = rec->addr;
  tb->count = cpu_to_be32(be16_to_cpu(rec->len) / 4);
  res = करो_loader_command (lb, dev, पढ़ो_adapter_memory);
  अगर (!res && स_भेद(tb->data, rec->data, be16_to_cpu(rec->len)))
    res = -EINVAL;
  वापस res;
पूर्ण

/* loader: start microcode */

अटल पूर्णांक loader_start(loader_block *lb, स्थिर amb_dev *dev, u32 address)
अणु
  PRINTD (DBG_FLOW|DBG_LOAD, "loader_start");
  
  lb->payload.start = cpu_to_be32 (address);
  वापस करो_loader_command (lb, dev, adapter_start);
पूर्ण

/********** reset card **********/

अटल अंतरभूत व्योम sf (स्थिर अक्षर * msg)
अणु
	PRINTK (KERN_ERR, "self-test failed: %s", msg);
पूर्ण

अटल पूर्णांक amb_reset (amb_dev * dev, पूर्णांक diags) अणु
  u32 word;
  
  PRINTD (DBG_FLOW|DBG_LOAD, "amb_reset");
  
  word = rd_plain (dev, दुरत्व(amb_mem, reset_control));
  // put card पूर्णांकo reset state
  wr_plain (dev, दुरत्व(amb_mem, reset_control), word | AMB_RESET_BITS);
  // रुको a लघु जबतक
  udelay (10);
#अगर 1
  // put card पूर्णांकo known good state
  wr_plain (dev, दुरत्व(amb_mem, पूर्णांकerrupt_control), AMB_DOORBELL_BITS);
  // clear all पूर्णांकerrupts just in हाल
  wr_plain (dev, दुरत्व(amb_mem, पूर्णांकerrupt), -1);
#पूर्ण_अगर
  // clear self-test करोne flag
  wr_plain (dev, दुरत्व(amb_mem, mb.loader.पढ़ोy), 0);
  // take card out of reset state
  wr_plain (dev, दुरत्व(amb_mem, reset_control), word &~ AMB_RESET_BITS);
  
  अगर (diags) अणु 
    अचिन्हित दीर्घ समयout;
    // 4.2 second रुको
    msleep(4200);
    // half second समय-out
    समयout = 500;
    जबतक (!rd_plain (dev, दुरत्व(amb_mem, mb.loader.पढ़ोy)))
      अगर (समयout) अणु
	समयout = msleep_पूर्णांकerruptible(समयout);
      पूर्ण अन्यथा अणु
	PRINTD (DBG_LOAD|DBG_ERR, "reset timed out");
	वापस -ETIMEDOUT;
      पूर्ण
    
    // get results of self-test
    // XXX द्विगुन check byte-order
    word = rd_mem (dev, दुरत्व(amb_mem, mb.loader.result));
    अगर (word & SELF_TEST_FAILURE) अणु
      अगर (word & GPINT_TST_FAILURE)
	sf ("interrupt");
      अगर (word & SUNI_DATA_PATTERN_FAILURE)
	sf ("SUNI data pattern");
      अगर (word & SUNI_DATA_BITS_FAILURE)
	sf ("SUNI data bits");
      अगर (word & SUNI_UTOPIA_FAILURE)
	sf ("SUNI UTOPIA interface");
      अगर (word & SUNI_FIFO_FAILURE)
	sf ("SUNI cell buffer FIFO");
      अगर (word & SRAM_FAILURE)
	sf ("bad SRAM");
      // better वापस value?
      वापस -EIO;
    पूर्ण
    
  पूर्ण
  वापस 0;
पूर्ण

/********** transfer and start the microcode **********/

अटल पूर्णांक ucode_init(loader_block *lb, amb_dev *dev)
अणु
  स्थिर काष्ठा firmware *fw;
  अचिन्हित दीर्घ start_address;
  स्थिर काष्ठा ihex_binrec *rec;
  स्थिर अक्षर *errmsg = शून्य;
  पूर्णांक res;

  res = request_ihex_firmware(&fw, "atmsar11.fw", &dev->pci_dev->dev);
  अगर (res) अणु
    PRINTK (KERN_ERR, "Cannot load microcode data");
    वापस res;
  पूर्ण

  /* First record contains just the start address */
  rec = (स्थिर काष्ठा ihex_binrec *)fw->data;
  अगर (be16_to_cpu(rec->len) != माप(__be32) || be32_to_cpu(rec->addr)) अणु
    errmsg = "no start record";
    जाओ fail;
  पूर्ण
  start_address = be32_to_cpup((__be32 *)rec->data);

  rec = ihex_next_binrec(rec);

  PRINTD (DBG_FLOW|DBG_LOAD, "ucode_init");

  जबतक (rec) अणु
    PRINTD (DBG_LOAD, "starting region (%x, %u)", be32_to_cpu(rec->addr),
	    be16_to_cpu(rec->len));
    अगर (be16_to_cpu(rec->len) > 4 * MAX_TRANSFER_DATA) अणु
	    errmsg = "record too long";
	    जाओ fail;
    पूर्ण
    अगर (be16_to_cpu(rec->len) & 3) अणु
	    errmsg = "odd number of bytes";
	    जाओ fail;
    पूर्ण
    res = loader_ग_लिखो(lb, dev, rec);
    अगर (res)
      अवरोध;

    res = loader_verअगरy(lb, dev, rec);
    अगर (res)
      अवरोध;
    rec = ihex_next_binrec(rec);
  पूर्ण
  release_firmware(fw);
  अगर (!res)
    res = loader_start(lb, dev, start_address);

  वापस res;
fail:
  release_firmware(fw);
  PRINTK(KERN_ERR, "Bad microcode data (%s)", errmsg);
  वापस -EINVAL;
पूर्ण

/********** give adapter parameters **********/
  
अटल अंतरभूत __be32 bus_addr(व्योम * addr) अणु
    वापस cpu_to_be32 (virt_to_bus (addr));
पूर्ण

अटल पूर्णांक amb_talk(amb_dev *dev)
अणु
  adap_talk_block a;
  अचिन्हित अक्षर pool;
  अचिन्हित दीर्घ समयout;
  
  PRINTD (DBG_FLOW, "amb_talk %p", dev);
  
  a.command_start = bus_addr (dev->cq.ptrs.start);
  a.command_end   = bus_addr (dev->cq.ptrs.limit);
  a.tx_start      = bus_addr (dev->txq.in.start);
  a.tx_end        = bus_addr (dev->txq.in.limit);
  a.txcom_start   = bus_addr (dev->txq.out.start);
  a.txcom_end     = bus_addr (dev->txq.out.limit);
  
  क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool) अणु
    // the other "a" items are set up by the adapter
    a.rec_काष्ठा[pool].buffer_start = bus_addr (dev->rxq[pool].in.start);
    a.rec_काष्ठा[pool].buffer_end   = bus_addr (dev->rxq[pool].in.limit);
    a.rec_काष्ठा[pool].rx_start     = bus_addr (dev->rxq[pool].out.start);
    a.rec_काष्ठा[pool].rx_end       = bus_addr (dev->rxq[pool].out.limit);
    a.rec_काष्ठा[pool].buffer_size = cpu_to_be32 (dev->rxq[pool].buffer_size);
  पूर्ण
  
#अगर_घोषित AMB_NEW_MICROCODE
  // disable fast PLX prefetching
  a.init_flags = 0;
#पूर्ण_अगर
  
  // pass the काष्ठाure
  wr_mem (dev, दुरत्व(amb_mem, करोorbell), virt_to_bus (&a));
  
  // 2.2 second रुको (must not touch करोorbell during 2 second DMA test)
  msleep(2200);
  // give the adapter another half second?
  समयout = 500;
  जबतक (rd_plain (dev, दुरत्व(amb_mem, करोorbell)))
    अगर (समयout) अणु
      समयout = msleep_पूर्णांकerruptible(समयout);
    पूर्ण अन्यथा अणु
      PRINTD (DBG_INIT|DBG_ERR, "adapter init timed out");
      वापस -ETIMEDOUT;
    पूर्ण
  
  वापस 0;
पूर्ण

// get microcode version
अटल व्योम amb_ucode_version(amb_dev *dev)
अणु
  u32 major;
  u32 minor;
  command cmd;
  cmd.request = cpu_to_be32 (SRB_GET_VERSION);
  जबतक (command_करो (dev, &cmd)) अणु
    set_current_state(TASK_UNINTERRUPTIBLE);
    schedule();
  पूर्ण
  major = be32_to_cpu (cmd.args.version.major);
  minor = be32_to_cpu (cmd.args.version.minor);
  PRINTK (KERN_INFO, "microcode version is %u.%u", major, minor);
पूर्ण
  
// get end station address
अटल व्योम amb_esi(amb_dev *dev, u8 *esi)
अणु
  u32 lower4;
  u16 upper2;
  command cmd;
  
  cmd.request = cpu_to_be32 (SRB_GET_BIA);
  जबतक (command_करो (dev, &cmd)) अणु
    set_current_state(TASK_UNINTERRUPTIBLE);
    schedule();
  पूर्ण
  lower4 = be32_to_cpu (cmd.args.bia.lower4);
  upper2 = be32_to_cpu (cmd.args.bia.upper2);
  PRINTD (DBG_LOAD, "BIA: lower4: %08x, upper2 %04x", lower4, upper2);
  
  अगर (esi) अणु
    अचिन्हित पूर्णांक i;
    
    PRINTDB (DBG_INIT, "ESI:");
    क्रम (i = 0; i < ESI_LEN; ++i) अणु
      अगर (i < 4)
	  esi[i] = bitrev8(lower4>>(8*i));
      अन्यथा
	  esi[i] = bitrev8(upper2>>(8*(i-4)));
      PRINTDM (DBG_INIT, " %02x", esi[i]);
    पूर्ण
    
    PRINTDE (DBG_INIT, "");
  पूर्ण
  
  वापस;
पूर्ण
  
अटल व्योम fixup_plx_winकरोw (amb_dev *dev, loader_block *lb)
अणु
	// fix up the PLX-mapped winकरोw base address to match the block
	अचिन्हित दीर्घ blb;
	u32 mapreg;
	blb = virt_to_bus(lb);
	// the kernel stack had better not ever cross a 1Gb boundary!
	mapreg = rd_plain (dev, दुरत्व(amb_mem, stuff[10]));
	mapreg &= ~onegigmask;
	mapreg |= blb & onegigmask;
	wr_plain (dev, दुरत्व(amb_mem, stuff[10]), mapreg);
	वापस;
पूर्ण

अटल पूर्णांक amb_init(amb_dev *dev)
अणु
  loader_block lb;
  
  u32 version;
  
  अगर (amb_reset (dev, 1)) अणु
    PRINTK (KERN_ERR, "card reset failed!");
  पूर्ण अन्यथा अणु
    fixup_plx_winकरोw (dev, &lb);
    
    अगर (get_loader_version (&lb, dev, &version)) अणु
      PRINTK (KERN_INFO, "failed to get loader version");
    पूर्ण अन्यथा अणु
      PRINTK (KERN_INFO, "loader version is %08x", version);
      
      अगर (ucode_init (&lb, dev)) अणु
	PRINTK (KERN_ERR, "microcode failure");
      पूर्ण अन्यथा अगर (create_queues (dev, cmds, txs, rxs, rxs_bs)) अणु
	PRINTK (KERN_ERR, "failed to get memory for queues");
      पूर्ण अन्यथा अणु
	
	अगर (amb_talk (dev)) अणु
	  PRINTK (KERN_ERR, "adapter did not accept queues");
	पूर्ण अन्यथा अणु
	  
	  amb_ucode_version (dev);
	  वापस 0;
	  
	पूर्ण /* amb_talk */
	
	destroy_queues (dev);
      पूर्ण /* create_queues, ucode_init */
      
      amb_reset (dev, 0);
    पूर्ण /* get_loader_version */
    
  पूर्ण /* amb_reset */
  
  वापस -EINVAL;
पूर्ण

अटल व्योम setup_dev(amb_dev *dev, काष्ठा pci_dev *pci_dev) 
अणु
      अचिन्हित अक्षर pool;
      
      // set up known dev items straight away
      dev->pci_dev = pci_dev; 
      pci_set_drvdata(pci_dev, dev);
      
      dev->iobase = pci_resource_start (pci_dev, 1);
      dev->irq = pci_dev->irq; 
      dev->membase = bus_to_virt(pci_resource_start(pci_dev, 0));
      
      // flags (currently only dead)
      dev->flags = 0;
      
      // Allocate cell rates (fibre)
      // ATM_OC3_PCR = 1555200000/8/270*260/53 - 29/53
      // to be really pedantic, this should be ATM_OC3c_PCR
      dev->tx_avail = ATM_OC3_PCR;
      dev->rx_avail = ATM_OC3_PCR;
      
      // semaphore क्रम txer/rxer modअगरications - we cannot use a
      // spinlock as the critical region needs to चयन processes
      mutex_init(&dev->vcc_sf);
      // queue manipulation spinlocks; we want atomic पढ़ोs and
      // ग_लिखोs to the queue descriptors (handles IRQ and SMP)
      // consider replacing "int pending" -> "atomic_t available"
      // => problem related to who माला_लो to move queue poपूर्णांकers
      spin_lock_init (&dev->cq.lock);
      spin_lock_init (&dev->txq.lock);
      क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool)
	spin_lock_init (&dev->rxq[pool].lock);
पूर्ण

अटल व्योम setup_pci_dev(काष्ठा pci_dev *pci_dev)
अणु
	अचिन्हित अक्षर lat;
      
	// enable bus master accesses
	pci_set_master(pci_dev);

	// frobnicate latency (upwards, usually)
	pci_पढ़ो_config_byte (pci_dev, PCI_LATENCY_TIMER, &lat);

	अगर (!pci_lat)
		pci_lat = (lat < MIN_PCI_LATENCY) ? MIN_PCI_LATENCY : lat;

	अगर (lat != pci_lat) अणु
		PRINTK (KERN_INFO, "Changing PCI latency timer from %hu to %hu",
			lat, pci_lat);
		pci_ग_लिखो_config_byte(pci_dev, PCI_LATENCY_TIMER, pci_lat);
	पूर्ण
पूर्ण

अटल पूर्णांक amb_probe(काष्ठा pci_dev *pci_dev,
		     स्थिर काष्ठा pci_device_id *pci_ent)
अणु
	amb_dev * dev;
	पूर्णांक err;
	अचिन्हित पूर्णांक irq;
      
	err = pci_enable_device(pci_dev);
	अगर (err < 0) अणु
		PRINTK (KERN_ERR, "skipped broken (PLX rev 2) card");
		जाओ out;
	पूर्ण

	// पढ़ो resources from PCI configuration space
	irq = pci_dev->irq;

	अगर (pci_dev->device == PCI_DEVICE_ID_MADGE_AMBASSADOR_BAD) अणु
		PRINTK (KERN_ERR, "skipped broken (PLX rev 2) card");
		err = -EINVAL;
		जाओ out_disable;
	पूर्ण

	PRINTD (DBG_INFO, "found Madge ATM adapter (amb) at"
		" IO %llx, IRQ %u, MEM %p",
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci_dev, 1),
		irq, bus_to_virt(pci_resource_start(pci_dev, 0)));

	// check IO region
	err = pci_request_region(pci_dev, 1, DEV_LABEL);
	अगर (err < 0) अणु
		PRINTK (KERN_ERR, "IO range already in use!");
		जाओ out_disable;
	पूर्ण

	dev = kzalloc(माप(amb_dev), GFP_KERNEL);
	अगर (!dev) अणु
		PRINTK (KERN_ERR, "out of memory!");
		err = -ENOMEM;
		जाओ out_release;
	पूर्ण

	setup_dev(dev, pci_dev);

	err = amb_init(dev);
	अगर (err < 0) अणु
		PRINTK (KERN_ERR, "adapter initialisation failure");
		जाओ out_मुक्त;
	पूर्ण

	setup_pci_dev(pci_dev);

	// grab (but share) IRQ and install handler
	err = request_irq(irq, पूर्णांकerrupt_handler, IRQF_SHARED, DEV_LABEL, dev);
	अगर (err < 0) अणु
		PRINTK (KERN_ERR, "request IRQ failed!");
		जाओ out_reset;
	पूर्ण

	dev->aपंचांग_dev = aपंचांग_dev_रेजिस्टर (DEV_LABEL, &pci_dev->dev, &amb_ops, -1,
					 शून्य);
	अगर (!dev->aपंचांग_dev) अणु
		PRINTD (DBG_ERR, "failed to register Madge ATM adapter");
		err = -EINVAL;
		जाओ out_मुक्त_irq;
	पूर्ण

	PRINTD (DBG_INFO, "registered Madge ATM adapter (no. %d) (%p) at %p",
		dev->aपंचांग_dev->number, dev, dev->aपंचांग_dev);
	dev->aपंचांग_dev->dev_data = (व्योम *) dev;

	// रेजिस्टर our address
	amb_esi (dev, dev->aपंचांग_dev->esi);

	// 0 bits क्रम vpi, 10 bits क्रम vci
	dev->aपंचांग_dev->ci_range.vpi_bits = NUM_VPI_BITS;
	dev->aपंचांग_dev->ci_range.vci_bits = NUM_VCI_BITS;

	समयr_setup(&dev->housekeeping, करो_housekeeping, 0);
	mod_समयr(&dev->housekeeping, jअगरfies);

	// enable host पूर्णांकerrupts
	पूर्णांकerrupts_on (dev);

out:
	वापस err;

out_मुक्त_irq:
	मुक्त_irq(irq, dev);
out_reset:
	amb_reset(dev, 0);
out_मुक्त:
	kमुक्त(dev);
out_release:
	pci_release_region(pci_dev, 1);
out_disable:
	pci_disable_device(pci_dev);
	जाओ out;
पूर्ण


अटल व्योम amb_हटाओ_one(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा amb_dev *dev;

	dev = pci_get_drvdata(pci_dev);

	PRINTD(DBG_INFO|DBG_INIT, "closing %p (atm_dev = %p)", dev, dev->aपंचांग_dev);
	del_समयr_sync(&dev->housekeeping);
	// the drain should not be necessary
	drain_rx_pools(dev);
	पूर्णांकerrupts_off(dev);
	amb_reset(dev, 0);
	मुक्त_irq(dev->irq, dev);
	pci_disable_device(pci_dev);
	destroy_queues(dev);
	aपंचांग_dev_deरेजिस्टर(dev->aपंचांग_dev);
	kमुक्त(dev);
	pci_release_region(pci_dev, 1);
पूर्ण

अटल व्योम __init amb_check_args (व्योम) अणु
  अचिन्हित अक्षर pool;
  अचिन्हित पूर्णांक max_rx_size;
  
#अगर_घोषित DEBUG_AMBASSADOR
  PRINTK (KERN_NOTICE, "debug bitmap is %hx", debug &= DBG_MASK);
#अन्यथा
  अगर (debug)
    PRINTK (KERN_NOTICE, "no debugging support");
#पूर्ण_अगर
  
  अगर (cmds < MIN_QUEUE_SIZE)
    PRINTK (KERN_NOTICE, "cmds has been raised to %u",
	    cmds = MIN_QUEUE_SIZE);
  
  अगर (txs < MIN_QUEUE_SIZE)
    PRINTK (KERN_NOTICE, "txs has been raised to %u",
	    txs = MIN_QUEUE_SIZE);
  
  क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool)
    अगर (rxs[pool] < MIN_QUEUE_SIZE)
      PRINTK (KERN_NOTICE, "rxs[%hu] has been raised to %u",
	      pool, rxs[pool] = MIN_QUEUE_SIZE);
  
  // buffers sizes should be greater than zero and strictly increasing
  max_rx_size = 0;
  क्रम (pool = 0; pool < NUM_RX_POOLS; ++pool)
    अगर (rxs_bs[pool] <= max_rx_size)
      PRINTK (KERN_NOTICE, "useless pool (rxs_bs[%hu] = %u)",
	      pool, rxs_bs[pool]);
    अन्यथा
      max_rx_size = rxs_bs[pool];
  
  अगर (rx_lats < MIN_RX_BUFFERS)
    PRINTK (KERN_NOTICE, "rx_lats has been raised to %u",
	    rx_lats = MIN_RX_BUFFERS);
  
  वापस;
पूर्ण

/********** module stuff **********/

MODULE_AUTHOR(मुख्यtainer_string);
MODULE_DESCRIPTION(description_string);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("atmsar11.fw");
module_param(debug,   uलघु, 0644);
module_param(cmds,    uपूर्णांक, 0);
module_param(txs,     uपूर्णांक, 0);
module_param_array(rxs,     uपूर्णांक, शून्य, 0);
module_param_array(rxs_bs,  uपूर्णांक, शून्य, 0);
module_param(rx_lats, uपूर्णांक, 0);
module_param(pci_lat, byte, 0);
MODULE_PARM_DESC(debug,   "debug bitmap, see .h file");
MODULE_PARM_DESC(cmds,    "number of command queue entries");
MODULE_PARM_DESC(txs,     "number of TX queue entries");
MODULE_PARM_DESC(rxs,     "number of RX queue entries [" __MODULE_STRING(NUM_RX_POOLS) "]");
MODULE_PARM_DESC(rxs_bs,  "size of RX buffers [" __MODULE_STRING(NUM_RX_POOLS) "]");
MODULE_PARM_DESC(rx_lats, "number of extra buffers to cope with RX latencies");
MODULE_PARM_DESC(pci_lat, "PCI latency in bus cycles");

/********** module entry **********/

अटल स्थिर काष्ठा pci_device_id amb_pci_tbl[] = अणु
	अणु PCI_VDEVICE(MADGE, PCI_DEVICE_ID_MADGE_AMBASSADOR), 0 पूर्ण,
	अणु PCI_VDEVICE(MADGE, PCI_DEVICE_ID_MADGE_AMBASSADOR_BAD), 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, amb_pci_tbl);

अटल काष्ठा pci_driver amb_driver = अणु
	.name =		"amb",
	.probe =	amb_probe,
	.हटाओ =	amb_हटाओ_one,
	.id_table =	amb_pci_tbl,
पूर्ण;

अटल पूर्णांक __init amb_module_init (व्योम)
अणु
  PRINTD (DBG_FLOW|DBG_INIT, "init_module");
  
  BUILD_BUG_ON(माप(amb_mem) != 4*16 + 4*12);
  
  show_version();
  
  amb_check_args();
  
  // get the juice
  वापस pci_रेजिस्टर_driver(&amb_driver);
पूर्ण

/********** module निकास **********/

अटल व्योम __निकास amb_module_निकास (व्योम)
अणु
  PRINTD (DBG_FLOW|DBG_INIT, "cleanup_module");

  pci_unरेजिस्टर_driver(&amb_driver);
पूर्ण

module_init(amb_module_init);
module_निकास(amb_module_निकास);
