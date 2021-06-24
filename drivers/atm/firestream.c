<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/* drivers/aपंचांग/firestream.c - FireStream 155 (MB86697) and
 *                            FireStream  50 (MB86695) device driver 
 */
 
/* Written & (C) 2000 by R.E.Wolff@BitWizard.nl 
 * Copied snippets from zaपंचांग.c by Werner Almesberger, EPFL LRC/ICA 
 * and ambassaकरोr.c Copyright (C) 1995-1999  Madge Networks Ltd 
 */

/*
*/


#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/pci.h>
#समावेश <linux/poison.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/sonet.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h> /* क्रम request_region */
#समावेश <linux/uपन.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/capability.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/माला.स>
#समावेश <यंत्र/पन.स>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>

#समावेश "firestream.h"

अटल पूर्णांक loopback = 0;
अटल पूर्णांक num=0x5a;

/* According to measurements (but they look suspicious to me!) करोne in
 * '97, 37% of the packets are one cell in size. So it pays to have
 * buffers allocated at that size. A large jump in percentage of
 * packets occurs at packets around 536 bytes in length. So it also
 * pays to have those pre-allocated. Unक्रमtunately, we can't fully
 * take advantage of this as the majority of the packets is likely to
 * be TCP/IP (As where obviously the measurement comes from) There the
 * link would be खोलोed with say a 1500 byte MTU, and we can't handle
 * smaller buffers more efficiently than the larger ones. -- REW
 */

/* Due to the way Linux memory management works, specअगरying "576" as
 * an allocation size here isn't going to help. They are allocated
 * from 1024-byte regions anyway. With the size of the sk_buffs (quite
 * large), it करोesn't pay to allocate the smallest size (64) -- REW */

/* This is all guesswork. Hard numbers to back this up or disprove this, 
 * are appreciated. -- REW */

/* The last entry should be about 64k. However, the "buffer size" is
 * passed to the chip in a 16 bit field. I करोn't know how "65536"
 * would be पूर्णांकerpreted. -- REW */

#घोषणा NP FS_NR_FREE_POOLS
अटल पूर्णांक rx_buf_sizes[NP]  = अणु128,  256,  512, 1024, 2048, 4096, 16384, 65520पूर्ण;
/* log2:                 7     8     9    10    11    12    14     16 */

#अगर 0
अटल पूर्णांक rx_pool_sizes[NP] = अणु1024, 1024, 512, 256,  128,  64,   32,    32पूर्ण;
#अन्यथा
/* debug */
अटल पूर्णांक rx_pool_sizes[NP] = अणु128,  128,  128, 64,   64,   64,   32,    32पूर्ण;
#पूर्ण_अगर
/* log2:                 10    10    9    8     7     6     5      5  */
/* sumlog2:              17    18    18   18    18    18    19     21 */
/* mem allocated:        128k  256k  256k 256k  256k  256k  512k   2M */
/* tot mem: almost 4M */

/* NP is लघुer, so that it fits on a single line. */
#अघोषित NP


/* Small hardware gotcha:

   The FS50 CAM (VP/VC match रेजिस्टरs) always take the lowest channel
   number that matches. This is not a problem.

   However, they also ignore whether the channel is enabled or
   not. This means that अगर you allocate channel 0 to 1.2 and then
   channel 1 to 0.0, then disabeling channel 0 and writing 0 to the
   match channel क्रम channel 0 will "steal" the traffic from channel
   1, even अगर you correctly disable channel 0.

   Workaround: 

   - When disabling channels, ग_लिखो an invalid VP/VC value to the
   match रेजिस्टर. (We use 0xffffffff, which in the worst हाल 
   matches VP/VC = <maxVP>/<maxVC>, but I expect it not to match
   anything as some "when not in use, program to 0" bits are now
   programmed to 1...)

   - Don't initialize the match रेजिस्टरs to 0, as 0.0 is a valid
   channel.
*/


/* Optimization hपूर्णांकs and tips.

   The FireStream chips are very capable of reducing the amount of
   "interrupt-traffic" क्रम the CPU. This driver requests an पूर्णांकerrupt on EVERY
   action. You could try to minimize this a bit. 

   Besides that, the userspace->kernel copy and the PCI bus are the
   perक्रमmance limiting issues क्रम this driver.

   You could queue up a bunch of outgoing packets without telling the
   FireStream. I'm not sure that's going to win you much though. The
   Linux layer won't tell us in advance when it's not going to give us
   any more packets in a जबतक. So this is tricky to implement right without
   पूर्णांकroducing extra delays. 
  
   -- REW
 */




/* The strings that define what the RX queue entry is all about. */
/* Fujitsu: Please tell me which ones can have a poपूर्णांकer to a 
   मुक्तpool descriptor! */
अटल अक्षर *res_strings[] = अणु
	"RX OK: streaming not EOP", 
	"RX OK: streaming EOP", 
	"RX OK: Single buffer packet", 
	"RX OK: packet mode", 
	"RX OK: F4 OAM (end to end)", 
	"RX OK: F4 OAM (Segment)", 
	"RX OK: F5 OAM (end to end)", 
	"RX OK: F5 OAM (Segment)", 
	"RX OK: RM cell", 
	"RX OK: TRANSP cell", 
	"RX OK: TRANSPC cell", 
	"Unmatched cell", 
	"reserved 12", 
	"reserved 13", 
	"reserved 14", 
	"Unrecognized cell", 
	"reserved 16", 
	"reassembly abort: AAL5 abort", 
	"packet purged", 
	"packet ageing timeout", 
	"channel ageing timeout", 
	"calculated length error", 
	"programmed length limit error", 
	"aal5 crc32 error", 
	"oam transp or transpc crc10 error", 
	"reserved 25", 
	"reserved 26", 
	"reserved 27", 
	"reserved 28", 
	"reserved 29", 
	"reserved 30", /* FIXME: The strings between 30-40 might be wrong. */
	"reassembly abort: no buffers", 
	"receive buffer overflow", 
	"change in GFC", 
	"receive buffer full", 
	"low priority discard - no receive descriptor", 
	"low priority discard - missing end of packet", 
	"reserved 37",
	"reserved 38",
	"reserved 39",
	"reserved 40",
	"reserved 41", 
	"reserved 42", 
	"reserved 43", 
	"reserved 44", 
	"reserved 45", 
	"reserved 46", 
	"reserved 47", 
	"reserved 48", 
	"reserved 49", 
	"reserved 50", 
	"reserved 51", 
	"reserved 52", 
	"reserved 53", 
	"reserved 54", 
	"reserved 55", 
	"reserved 56", 
	"reserved 57", 
	"reserved 58", 
	"reserved 59", 
	"reserved 60", 
	"reserved 61", 
	"reserved 62", 
	"reserved 63", 
पूर्ण;  

अटल अक्षर *irq_bitname[] = अणु
	"LPCO",
	"DPCO",
	"RBRQ0_W",
	"RBRQ1_W",
	"RBRQ2_W",
	"RBRQ3_W",
	"RBRQ0_NF",
	"RBRQ1_NF",
	"RBRQ2_NF",
	"RBRQ3_NF",
	"BFP_SC",
	"INIT",
	"INIT_ERR",
	"USCEO",
	"UPEC0",
	"VPFCO",
	"CRCCO",
	"HECO",
	"TBRQ_W",
	"TBRQ_NF",
	"CTPQ_E",
	"GFC_C0",
	"PCI_FTL",
	"CSQ_W",
	"CSQ_NF",
	"EXT_INT",
	"RXDMA_S"
पूर्ण;


#घोषणा PHY_खातापूर्ण -1
#घोषणा PHY_CLEARALL -2

काष्ठा reginit_item अणु
	पूर्णांक reg, val;
पूर्ण;


अटल काष्ठा reginit_item PHY_NTC_INIT[] = अणु
	अणु PHY_CLEARALL, 0x40 पूर्ण, 
	अणु 0x12,  0x0001 पूर्ण,
	अणु 0x13,  0x7605 पूर्ण,
	अणु 0x1A,  0x0001 पूर्ण,
	अणु 0x1B,  0x0005 पूर्ण,
	अणु 0x38,  0x0003 पूर्ण,
	अणु 0x39,  0x0006 पूर्ण,   /* changed here to make loopback */
	अणु 0x01,  0x5262 पूर्ण,
	अणु 0x15,  0x0213 पूर्ण,
	अणु 0x00,  0x0003 पूर्ण,
	अणु PHY_खातापूर्ण, 0पूर्ण,    /* -1 संकेतs end of list */
पूर्ण;


/* Safetyfeature: If the card पूर्णांकerrupts more than this number of बार
   in a jअगरfy (1/100th of a second) then we just disable the पूर्णांकerrupt and
   prपूर्णांक a message. This prevents the प्रणाली from hanging. 

   150000 packets per second is बंद to the limit a PC is going to have
   anyway. We thereक्रमe have to disable this क्रम production. -- REW */
#अघोषित IRQ_RATE_LIMIT // 100

/* Interrupts work now. Unlike serial cards, ATM cards करोn't work all
   that great without पूर्णांकerrupts. -- REW */
#अघोषित FS_POLL_FREQ // 100

/* 
   This driver can spew a whole lot of debugging output at you. If you
   need maximum perक्रमmance, you should disable the DEBUG define. To
   aid in debugging in the field, I'm leaving the compile-समय debug
   features enabled, and disable them "runtime". That allows me to
   inकाष्ठा people with problems to enable debugging without requiring
   them to recompile... -- REW
*/
#घोषणा DEBUG

#अगर_घोषित DEBUG
#घोषणा fs_dprपूर्णांकk(f, str...) अगर (fs_debug & f) prपूर्णांकk (str)
#अन्यथा
#घोषणा fs_dprपूर्णांकk(f, str...) /* nothing */
#पूर्ण_अगर


अटल पूर्णांक fs_keystream = 0;

#अगर_घोषित DEBUG
/* I didn't क्रमget to set this to zero beक्रमe shipping. Hit me with a stick 
   अगर you get this with the debug शेष not set to zero again. -- REW */
अटल पूर्णांक fs_debug = 0;
#अन्यथा
#घोषणा fs_debug 0
#पूर्ण_अगर

#अगर_घोषित MODULE
#अगर_घोषित DEBUG 
module_param(fs_debug, पूर्णांक, 0644);
#पूर्ण_अगर
module_param(loopback, पूर्णांक, 0);
module_param(num, पूर्णांक, 0);
module_param(fs_keystream, पूर्णांक, 0);
/* XXX Add rx_buf_sizes, and rx_pool_sizes As per request Amar. -- REW */
#पूर्ण_अगर


#घोषणा FS_DEBUG_FLOW    0x00000001
#घोषणा FS_DEBUG_OPEN    0x00000002
#घोषणा FS_DEBUG_QUEUE   0x00000004
#घोषणा FS_DEBUG_IRQ     0x00000008
#घोषणा FS_DEBUG_INIT    0x00000010
#घोषणा FS_DEBUG_SEND    0x00000020
#घोषणा FS_DEBUG_PHY     0x00000040
#घोषणा FS_DEBUG_CLEANUP 0x00000080
#घोषणा FS_DEBUG_QOS     0x00000100
#घोषणा FS_DEBUG_TXQ     0x00000200
#घोषणा FS_DEBUG_ALLOC   0x00000400
#घोषणा FS_DEBUG_TXMEM   0x00000800
#घोषणा FS_DEBUG_QSIZE   0x00001000


#घोषणा func_enter() fs_dprपूर्णांकk(FS_DEBUG_FLOW, "fs: enter %s\n", __func__)
#घोषणा func_निकास()  fs_dprपूर्णांकk(FS_DEBUG_FLOW, "fs: exit  %s\n", __func__)


अटल काष्ठा fs_dev *fs_boards = शून्य;

#अगर_घोषित DEBUG

अटल व्योम my_hd (व्योम *addr, पूर्णांक len)
अणु
	पूर्णांक j, ch;
	अचिन्हित अक्षर *ptr = addr;

	जबतक (len > 0) अणु
		prपूर्णांकk ("%p ", ptr);
		क्रम (j=0;j < ((len < 16)?len:16);j++) अणु
			prपूर्णांकk ("%02x %s", ptr[j], (j==7)?" ":"");
		पूर्ण
		क्रम (  ;j < 16;j++) अणु
			prपूर्णांकk ("   %s", (j==7)?" ":"");
		पूर्ण
		क्रम (j=0;j < ((len < 16)?len:16);j++) अणु
			ch = ptr[j];
			prपूर्णांकk ("%c", (ch < 0x20)?'.':((ch > 0x7f)?'.':ch));
		पूर्ण
		prपूर्णांकk ("\n");
		ptr += 16;
		len -= 16;
	पूर्ण
पूर्ण
#अन्यथा /* DEBUG */
अटल व्योम my_hd (व्योम *addr, पूर्णांक len)अणुपूर्ण
#पूर्ण_अगर /* DEBUG */

/********** मुक्त an skb (as per ATM device driver करोcumentation) **********/

/* Hmm. If this is ATM specअगरic, why isn't there an ATM routine क्रम this?
 * I copied it over from the ambassaकरोr driver. -- REW */

अटल अंतरभूत व्योम fs_kमुक्त_skb (काष्ठा sk_buff * skb) 
अणु
	अगर (ATM_SKB(skb)->vcc->pop)
		ATM_SKB(skb)->vcc->pop (ATM_SKB(skb)->vcc, skb);
	अन्यथा
		dev_kमुक्त_skb_any (skb);
पूर्ण




/* It seems the ATM क्रमum recommends this horribly complicated 16bit
 * भग्नing poपूर्णांक क्रमmat. Turns out the Ambassaकरोr uses the exact same
 * encoding. I just copied it over. If Mitch agrees, I'll move it over
 * to the aपंचांग_misc file or something like that. (and हटाओ it from 
 * here and the ambassaकरोr driver) -- REW
 */

/* The good thing about this क्रमmat is that it is monotonic. So, 
   a conversion routine need not be very complicated. To be able to
   round "nearest" we need to take aदीर्घ a few extra bits. Lets
   put these after 16 bits, so that we can just वापस the top 16
   bits of the 32bit number as the result:

   पूर्णांक mr (अचिन्हित पूर्णांक rate, पूर्णांक r) 
     अणु
     पूर्णांक e = 16+9;
     अटल पूर्णांक round[4]=अणु0, 0, 0xffff, 0x8000पूर्ण;
     अगर (!rate) वापस 0;
     जबतक (rate & 0xfc000000) अणु
       rate >>= 1;
       e++;
     पूर्ण
     जबतक (! (rate & 0xfe000000)) अणु
       rate <<= 1;
       e--;
     पूर्ण

// Now the mantissa is in positions bit 16-25. Excepf क्रम the "hidden 1" that's in bit 26.
     rate &= ~0x02000000;
// Next add in the exponent
     rate |= e << (16+9);
// And perक्रमm the rounding:
     वापस (rate + round[r]) >> 16;
   पूर्ण

   14 lines-of-code. Compare that with the 120 that the Ambassaकरोr
   guys needed. (would be 8 lines लघुer अगर I'd try to really reduce
   the number of lines:

   पूर्णांक mr (अचिन्हित पूर्णांक rate, पूर्णांक r) 
   अणु
     पूर्णांक e = 16+9;
     अटल पूर्णांक round[4]=अणु0, 0, 0xffff, 0x8000पूर्ण;
     अगर (!rate) वापस 0;
     क्रम (;  rate & 0xfc000000 ;rate >>= 1, e++);
     क्रम (;!(rate & 0xfe000000);rate <<= 1, e--);
     वापस ((rate & ~0x02000000) | (e << (16+9)) + round[r]) >> 16;
   पूर्ण

   Exercise क्रम the पढ़ोer: Remove one more line-of-code, without
   cheating. (Just joining two lines is cheating). (I know it's
   possible, करोn't think you've beat me अगर you found it... If you
   manage to lose two lines or more, keep me updated! ;-)

   -- REW */


#घोषणा ROUND_UP      1
#घोषणा ROUND_DOWN    2
#घोषणा ROUND_NEAREST 3
/********** make rate (not quite as much fun as Horizon) **********/

अटल पूर्णांक make_rate(अचिन्हित पूर्णांक rate, पूर्णांक r,
		      u16 *bits, अचिन्हित पूर्णांक *actual)
अणु
	अचिन्हित अक्षर exp = -1; /* hush gcc */
	अचिन्हित पूर्णांक man = -1;  /* hush gcc */
  
	fs_dprपूर्णांकk (FS_DEBUG_QOS, "make_rate %u", rate);
  
	/* rates in cells per second, ITU क्रमmat (nasty 16-bit भग्नing-poपूर्णांक)
	   given 5-bit e and 9-bit m:
	   rate = EITHER (1+m/2^9)*2^e    OR 0
	   bits = EITHER 1<<14 | e<<9 | m OR 0
	   (bit 15 is "reserved", bit 14 "non-zero")
	   smallest rate is 0 (special representation)
	   largest rate is (1+511/512)*2^31 = 4290772992 (< 2^32-1)
	   smallest non-zero rate is (1+0/512)*2^0 = 1 (> 0)
	   simple algorithm:
	   find position of top bit, this gives e
	   हटाओ top bit and shअगरt (rounding अगर feeling clever) by 9-e
	*/
	/* Ambassaकरोr ucode bug: please करोn't set bit 14! so 0 rate not
	   representable. // This should move पूर्णांकo the ambassaकरोr driver
	   when properly merged. -- REW */
  
	अगर (rate > 0xffc00000U) अणु
		/* larger than largest representable rate */
    
		अगर (r == ROUND_UP) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			exp = 31;
			man = 511;
		पूर्ण
    
	पूर्ण अन्यथा अगर (rate) अणु
		/* representable rate */
    
		exp = 31;
		man = rate;
    
		/* invariant: rate = man*2^(exp-31) */
		जबतक (!(man & (1<<31))) अणु
			exp = exp - 1;
			man = man<<1;
		पूर्ण
    
		/* man has top bit set
		   rate = (2^31+(man-2^31))*2^(exp-31)
		   rate = (1+(man-2^31)/2^31)*2^exp 
		*/
		man = man<<1;
		man &= 0xffffffffU; /* a nop on 32-bit प्रणालीs */
		/* rate = (1+man/2^32)*2^exp
    
		   exp is in the range 0 to 31, man is in the range 0 to 2^32-1
		   समय to lose signअगरicance... we want m in the range 0 to 2^9-1
		   rounding presents a minor problem... we first decide which way
		   we are rounding (based on given rounding direction and possibly
		   the bits of the mantissa that are to be discarded).
		*/

		चयन (r) अणु
		हाल ROUND_DOWN: अणु
			/* just truncate */
			man = man>>(32-9);
			अवरोध;
		पूर्ण
		हाल ROUND_UP: अणु
			/* check all bits that we are discarding */
			अगर (man & (~0U>>9)) अणु
				man = (man>>(32-9)) + 1;
				अगर (man == (1<<9)) अणु
					/* no need to check क्रम round up outside of range */
					man = 0;
					exp += 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				man = (man>>(32-9));
			पूर्ण
			अवरोध;
		पूर्ण
		हाल ROUND_NEAREST: अणु
			/* check msb that we are discarding */
			अगर (man & (1<<(32-9-1))) अणु
				man = (man>>(32-9)) + 1;
				अगर (man == (1<<9)) अणु
					/* no need to check क्रम round up outside of range */
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
		/* zero rate - not representable */
    
		अगर (r == ROUND_DOWN) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			exp = 0;
			man = 0;
		पूर्ण
	पूर्ण
  
	fs_dprपूर्णांकk (FS_DEBUG_QOS, "rate: man=%u, exp=%hu", man, exp);
  
	अगर (bits)
		*bits = /* (1<<14) | */ (exp<<9) | man;
  
	अगर (actual)
		*actual = (exp >= 9)
			? (1 << exp) + (man << (exp-9))
			: (1 << exp) + ((man + (1<<(9-exp-1))) >> (9-exp));
  
	वापस 0;
पूर्ण




/* FireStream access routines */
/* For DEEP-DOWN debugging these can be rigged to पूर्णांकercept accesses to
   certain रेजिस्टरs or to just log all accesses. */

अटल अंतरभूत व्योम ग_लिखो_fs (काष्ठा fs_dev *dev, पूर्णांक offset, u32 val)
अणु
	ग_लिखोl (val, dev->base + offset);
पूर्ण


अटल अंतरभूत u32  पढ़ो_fs (काष्ठा fs_dev *dev, पूर्णांक offset)
अणु
	वापस पढ़ोl (dev->base + offset);
पूर्ण



अटल अंतरभूत काष्ठा FS_QENTRY *get_qentry (काष्ठा fs_dev *dev, काष्ठा queue *q)
अणु
	वापस bus_to_virt (पढ़ो_fs (dev, Q_WP(q->offset)) & Q_ADDR_MASK);
पूर्ण


अटल व्योम submit_qentry (काष्ठा fs_dev *dev, काष्ठा queue *q, काष्ठा FS_QENTRY *qe)
अणु
	u32 wp;
	काष्ठा FS_QENTRY *cqe;

	/* XXX Sanity check: the ग_लिखो poपूर्णांकer can be checked to be 
	   still the same as the value passed as qe... -- REW */
	/*  udelay (5); */
	जबतक ((wp = पढ़ो_fs (dev, Q_WP (q->offset))) & Q_FULL) अणु
		fs_dprपूर्णांकk (FS_DEBUG_TXQ, "Found queue at %x full. Waiting.\n", 
			    q->offset);
		schedule ();
	पूर्ण

	wp &= ~0xf;
	cqe = bus_to_virt (wp);
	अगर (qe != cqe) अणु
		fs_dprपूर्णांकk (FS_DEBUG_TXQ, "q mismatch! %p %p\n", qe, cqe);
	पूर्ण

	ग_लिखो_fs (dev, Q_WP(q->offset), Q_INCWRAP);

	अणु
		अटल पूर्णांक c;
		अगर (!(c++ % 100))
			अणु
				पूर्णांक rp, wp;
				rp =  पढ़ो_fs (dev, Q_RP(q->offset));
				wp =  पढ़ो_fs (dev, Q_WP(q->offset));
				fs_dprपूर्णांकk (FS_DEBUG_TXQ, "q at %d: %x-%x: %x entries.\n", 
					    q->offset, rp, wp, wp-rp);
			पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित DEBUG_EXTRA
अटल काष्ठा FS_QENTRY pq[60];
अटल पूर्णांक qp;

अटल काष्ठा FS_BPENTRY dq[60];
अटल पूर्णांक qd;
अटल व्योम *da[60];
#पूर्ण_अगर 

अटल व्योम submit_queue (काष्ठा fs_dev *dev, काष्ठा queue *q, 
			  u32 cmd, u32 p1, u32 p2, u32 p3)
अणु
	काष्ठा FS_QENTRY *qe;

	qe = get_qentry (dev, q);
	qe->cmd = cmd;
	qe->p0 = p1;
	qe->p1 = p2;
	qe->p2 = p3;
	submit_qentry (dev,  q, qe);

#अगर_घोषित DEBUG_EXTRA
	pq[qp].cmd = cmd;
	pq[qp].p0 = p1;
	pq[qp].p1 = p2;
	pq[qp].p2 = p3;
	qp++;
	अगर (qp >= 60) qp = 0;
#पूर्ण_अगर
पूर्ण

/* Test the "other" way one day... -- REW */
#अगर 1
#घोषणा submit_command submit_queue
#अन्यथा

अटल व्योम submit_command (काष्ठा fs_dev *dev, काष्ठा queue *q, 
			    u32 cmd, u32 p1, u32 p2, u32 p3)
अणु
	ग_लिखो_fs (dev, CMDR0, cmd);
	ग_लिखो_fs (dev, CMDR1, p1);
	ग_लिखो_fs (dev, CMDR2, p2);
	ग_लिखो_fs (dev, CMDR3, p3);
पूर्ण
#पूर्ण_अगर



अटल व्योम process_वापस_queue (काष्ठा fs_dev *dev, काष्ठा queue *q)
अणु
	दीर्घ rq;
	काष्ठा FS_QENTRY *qe;
	व्योम *tc;
  
	जबतक (!((rq = पढ़ो_fs (dev, Q_RP(q->offset))) & Q_EMPTY)) अणु
		fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "reaping return queue entry at %lx\n", rq); 
		qe = bus_to_virt (rq);
    
		fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "queue entry: %08x %08x %08x %08x. (%d)\n", 
			    qe->cmd, qe->p0, qe->p1, qe->p2, STATUS_CODE (qe));

		चयन (STATUS_CODE (qe)) अणु
		हाल 5:
			tc = bus_to_virt (qe->p0);
			fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free tc: %p\n", tc);
			kमुक्त (tc);
			अवरोध;
		पूर्ण
    
		ग_लिखो_fs (dev, Q_RP(q->offset), Q_INCWRAP);
	पूर्ण
पूर्ण


अटल व्योम process_txकरोne_queue (काष्ठा fs_dev *dev, काष्ठा queue *q)
अणु
	दीर्घ rq;
	दीर्घ पंचांगp;
	काष्ठा FS_QENTRY *qe;
	काष्ठा sk_buff *skb;
	काष्ठा FS_BPENTRY *td;

	जबतक (!((rq = पढ़ो_fs (dev, Q_RP(q->offset))) & Q_EMPTY)) अणु
		fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "reaping txdone entry at %lx\n", rq); 
		qe = bus_to_virt (rq);
    
		fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "queue entry: %08x %08x %08x %08x: %d\n", 
			    qe->cmd, qe->p0, qe->p1, qe->p2, STATUS_CODE (qe));

		अगर (STATUS_CODE (qe) != 2)
			fs_dprपूर्णांकk (FS_DEBUG_TXMEM, "queue entry: %08x %08x %08x %08x: %d\n", 
				    qe->cmd, qe->p0, qe->p1, qe->p2, STATUS_CODE (qe));


		चयन (STATUS_CODE (qe)) अणु
		हाल 0x01: /* This is क्रम AAL0 where we put the chip in streaming mode */
			fallthrough;
		हाल 0x02:
			/* Process a real txकरोne entry. */
			पंचांगp = qe->p0;
			अगर (पंचांगp & 0x0f)
				prपूर्णांकk (KERN_WARNING "td not aligned: %ld\n", पंचांगp);
			पंचांगp &= ~0x0f;
			td = bus_to_virt (पंचांगp);

			fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "Pool entry: %08x %08x %08x %08x %p.\n", 
				    td->flags, td->next, td->bsa, td->aal_bufsize, td->skb );
      
			skb = td->skb;
			अगर (skb == FS_VCC (ATM_SKB(skb)->vcc)->last_skb) अणु
				FS_VCC (ATM_SKB(skb)->vcc)->last_skb = शून्य;
				wake_up_पूर्णांकerruptible (& FS_VCC (ATM_SKB(skb)->vcc)->बंद_रुको);
			पूर्ण
			td->dev->ntxpckts--;

			अणु
				अटल पूर्णांक c=0;
	
				अगर (!(c++ % 100)) अणु
					fs_dprपूर्णांकk (FS_DEBUG_QSIZE, "[%d]", td->dev->ntxpckts);
				पूर्ण
			पूर्ण

			atomic_inc(&ATM_SKB(skb)->vcc->stats->tx);

			fs_dprपूर्णांकk (FS_DEBUG_TXMEM, "i");
			fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free t-skb: %p\n", skb);
			fs_kमुक्त_skb (skb);

			fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free trans-d: %p\n", td); 
			स_रखो (td, ATM_POISON_FREE, माप(काष्ठा FS_BPENTRY));
			kमुक्त (td);
			अवरोध;
		शेष:
			/* Here we get the tx purge inhibit command ... */
			/* Action, I believe, is "don't do anything". -- REW */
			;
		पूर्ण
    
		ग_लिखो_fs (dev, Q_RP(q->offset), Q_INCWRAP);
	पूर्ण
पूर्ण


अटल व्योम process_incoming (काष्ठा fs_dev *dev, काष्ठा queue *q)
अणु
	दीर्घ rq;
	काष्ठा FS_QENTRY *qe;
	काष्ठा FS_BPENTRY *pe;    
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक channo;
	काष्ठा aपंचांग_vcc *aपंचांग_vcc;

	जबतक (!((rq = पढ़ो_fs (dev, Q_RP(q->offset))) & Q_EMPTY)) अणु
		fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "reaping incoming queue entry at %lx\n", rq); 
		qe = bus_to_virt (rq);
    
		fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "queue entry: %08x %08x %08x %08x.  ", 
			    qe->cmd, qe->p0, qe->p1, qe->p2);

		fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "-> %x: %s\n", 
			    STATUS_CODE (qe), 
			    res_strings[STATUS_CODE(qe)]);

		pe = bus_to_virt (qe->p0);
		fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "Pool entry: %08x %08x %08x %08x %p %p.\n", 
			    pe->flags, pe->next, pe->bsa, pe->aal_bufsize, 
			    pe->skb, pe->fp);
      
		channo = qe->cmd & 0xffff;

		अगर (channo < dev->nchannels)
			aपंचांग_vcc = dev->aपंचांग_vccs[channo];
		अन्यथा
			aपंचांग_vcc = शून्य;

		/* Single buffer packet */
		चयन (STATUS_CODE (qe)) अणु
		हाल 0x1:
			/* Fall through क्रम streaming mode */
			fallthrough;
		हाल 0x2:/* Packet received OK.... */
			अगर (aपंचांग_vcc) अणु
				skb = pe->skb;
				pe->fp->n--;
#अगर 0
				fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "Got skb: %p\n", skb);
				अगर (FS_DEBUG_QUEUE & fs_debug) my_hd (bus_to_virt (pe->bsa), 0x20);
#पूर्ण_अगर
				skb_put (skb, qe->p1 & 0xffff); 
				ATM_SKB(skb)->vcc = aपंचांग_vcc;
				atomic_inc(&aपंचांग_vcc->stats->rx);
				__net_बारtamp(skb);
				fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free rec-skb: %p (pushed)\n", skb);
				aपंचांग_vcc->push (aपंचांग_vcc, skb);
				fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free rec-d: %p\n", pe);
				kमुक्त (pe);
			पूर्ण अन्यथा अणु
				prपूर्णांकk (KERN_ERR "Got a receive on a non-open channel %d.\n", channo);
			पूर्ण
			अवरोध;
		हाल 0x17:/* AAL 5 CRC32 error. IFF the length field is nonzero, a buffer
			     has been consumed and needs to be processed. -- REW */
			अगर (qe->p1 & 0xffff) अणु
				pe = bus_to_virt (qe->p0);
				pe->fp->n--;
				fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free rec-skb: %p\n", pe->skb);
				dev_kमुक्त_skb_any (pe->skb);
				fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free rec-d: %p\n", pe);
				kमुक्त (pe);
			पूर्ण
			अगर (aपंचांग_vcc)
				atomic_inc(&aपंचांग_vcc->stats->rx_drop);
			अवरोध;
		हाल 0x1f: /*  Reassembly पात: no buffers. */
			/* Silently increment error counter. */
			अगर (aपंचांग_vcc)
				atomic_inc(&aपंचांग_vcc->stats->rx_drop);
			अवरोध;
		शेष: /* Hmm. Haven't written the code to handle the others yet... -- REW */
			prपूर्णांकk (KERN_WARNING "Don't know what to do with RX status %x: %s.\n", 
				STATUS_CODE(qe), res_strings[STATUS_CODE (qe)]);
		पूर्ण
		ग_लिखो_fs (dev, Q_RP(q->offset), Q_INCWRAP);
	पूर्ण
पूर्ण



#घोषणा DO_सूचीECTION(tp) ((tp)->traffic_class != ATM_NONE)

अटल पूर्णांक fs_खोलो(काष्ठा aपंचांग_vcc *aपंचांग_vcc)
अणु
	काष्ठा fs_dev *dev;
	काष्ठा fs_vcc *vcc;
	काष्ठा fs_transmit_config *tc;
	काष्ठा aपंचांग_trafprm * txtp;
	काष्ठा aपंचांग_trafprm * rxtp;
	/*  काष्ठा fs_receive_config *rc;*/
	/*  काष्ठा FS_QENTRY *qe; */
	पूर्णांक error;
	पूर्णांक bfp;
	पूर्णांक to;
	अचिन्हित लघु पंचांगc0;
	लघु vpi = aपंचांग_vcc->vpi;
	पूर्णांक vci = aपंचांग_vcc->vci;

	func_enter ();

	dev = FS_DEV(aपंचांग_vcc->dev);
	fs_dprपूर्णांकk (FS_DEBUG_OPEN, "fs: open on dev: %p, vcc at %p\n", 
		    dev, aपंचांग_vcc);

	अगर (vci != ATM_VPI_UNSPEC && vpi != ATM_VCI_UNSPEC)
		set_bit(ATM_VF_ADDR, &aपंचांग_vcc->flags);

	अगर ((aपंचांग_vcc->qos.aal != ATM_AAL5) &&
	    (aपंचांग_vcc->qos.aal != ATM_AAL2))
	  वापस -EINVAL; /* XXX AAL0 */

	fs_dprपूर्णांकk (FS_DEBUG_OPEN, "fs: (itf %d): open %d.%d\n", 
		    aपंचांग_vcc->dev->number, aपंचांग_vcc->vpi, aपंचांग_vcc->vci);	

	/* XXX handle qos parameters (rate limiting) ? */

	vcc = kदो_स्मृति(माप(काष्ठा fs_vcc), GFP_KERNEL);
	fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Alloc VCC: %p(%zd)\n", vcc, माप(काष्ठा fs_vcc));
	अगर (!vcc) अणु
		clear_bit(ATM_VF_ADDR, &aपंचांग_vcc->flags);
		वापस -ENOMEM;
	पूर्ण
  
	aपंचांग_vcc->dev_data = vcc;
	vcc->last_skb = शून्य;

	init_रुकोqueue_head (&vcc->बंद_रुको);

	txtp = &aपंचांग_vcc->qos.txtp;
	rxtp = &aपंचांग_vcc->qos.rxtp;

	अगर (!test_bit(ATM_VF_PARTIAL, &aपंचांग_vcc->flags)) अणु
		अगर (IS_FS50(dev)) अणु
			/* Increment the channel numer: take a मुक्त one next समय.  */
			क्रम (to=33;to;to--, dev->channo++) अणु
				/* We only have 32 channels */
				अगर (dev->channo >= 32)
					dev->channo = 0;
				/* If we need to करो RX, AND the RX is inuse, try the next */
				अगर (DO_सूचीECTION(rxtp) && dev->aपंचांग_vccs[dev->channo])
					जारी;
				/* If we need to करो TX, AND the TX is inuse, try the next */
				अगर (DO_सूचीECTION(txtp) && test_bit (dev->channo, dev->tx_inuse))
					जारी;
				/* Ok, both are मुक्त! (or not needed) */
				अवरोध;
			पूर्ण
			अगर (!to) अणु
				prपूर्णांकk ("No more free channels for FS50..\n");
				kमुक्त(vcc);
				वापस -EBUSY;
			पूर्ण
			vcc->channo = dev->channo;
			dev->channo &= dev->channel_mask;
      
		पूर्ण अन्यथा अणु
			vcc->channo = (vpi << FS155_VCI_BITS) | (vci);
			अगर (((DO_सूचीECTION(rxtp) && dev->aपंचांग_vccs[vcc->channo])) ||
			    ( DO_सूचीECTION(txtp) && test_bit (vcc->channo, dev->tx_inuse))) अणु
				prपूर्णांकk ("Channel is in use for FS155.\n");
				kमुक्त(vcc);
				वापस -EBUSY;
			पूर्ण
		पूर्ण
		fs_dprपूर्णांकk (FS_DEBUG_OPEN, "OK. Allocated channel %x(%d).\n", 
			    vcc->channo, vcc->channo);
	पूर्ण

	अगर (DO_सूचीECTION (txtp)) अणु
		tc = kदो_स्मृति (माप (काष्ठा fs_transmit_config), GFP_KERNEL);
		fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Alloc tc: %p(%zd)\n",
			    tc, माप (काष्ठा fs_transmit_config));
		अगर (!tc) अणु
			fs_dprपूर्णांकk (FS_DEBUG_OPEN, "fs: can't alloc transmit_config.\n");
			kमुक्त(vcc);
			वापस -ENOMEM;
		पूर्ण

		/* Allocate the "open" entry from the high priority txq. This makes
		   it most likely that the chip will notice it. It also prevents us
		   from having to रुको क्रम completion. On the other hand, we may
		   need to रुको क्रम completion anyway, to see अगर it completed
		   successfully. */

		चयन (aपंचांग_vcc->qos.aal) अणु
		हाल ATM_AAL2:
		हाल ATM_AAL0:
		  tc->flags = 0
		    | TC_FLAGS_TRANSPARENT_PAYLOAD
		    | TC_FLAGS_PACKET
		    | (1 << 28)
		    | TC_FLAGS_TYPE_UBR /* XXX Change to VBR -- PVDL */
		    | TC_FLAGS_CAL0;
		  अवरोध;
		हाल ATM_AAL5:
		  tc->flags = 0
			| TC_FLAGS_AAL5
			| TC_FLAGS_PACKET  /* ??? */
			| TC_FLAGS_TYPE_CBR
			| TC_FLAGS_CAL0;
		  अवरोध;
		शेष:
			prपूर्णांकk ("Unknown aal: %d\n", aपंचांग_vcc->qos.aal);
			tc->flags = 0;
		पूर्ण
		/* Docs are vague about this aपंचांग_hdr field. By the way, the FS
		 * chip makes odd errors अगर lower bits are set.... -- REW */
		tc->aपंचांग_hdr =  (vpi << 20) | (vci << 4); 
		पंचांगc0 = 0;
		अणु
			पूर्णांक pcr = aपंचांग_pcr_goal (txtp);

			fs_dprपूर्णांकk (FS_DEBUG_OPEN, "pcr = %d.\n", pcr);

			/* XXX Hmm. officially we're only allowed to करो this अगर rounding 
			   is round_करोwn -- REW */
			अगर (IS_FS50(dev)) अणु
				अगर (pcr > 51840000/53/8)  pcr = 51840000/53/8;
			पूर्ण अन्यथा अणु
				अगर (pcr > 155520000/53/8) pcr = 155520000/53/8;
			पूर्ण
			अगर (!pcr) अणु
				/* no rate cap */
				पंचांगc0 = IS_FS50(dev)?0x61BE:0x64c9; /* Just copied over the bits from Fujitsu -- REW */
			पूर्ण अन्यथा अणु
				पूर्णांक r;
				अगर (pcr < 0) अणु
					r = ROUND_DOWN;
					pcr = -pcr;
				पूर्ण अन्यथा अणु
					r = ROUND_UP;
				पूर्ण
				error = make_rate (pcr, r, &पंचांगc0, शून्य);
				अगर (error) अणु
					kमुक्त(tc);
					kमुक्त(vcc);
					वापस error;
				पूर्ण
			पूर्ण
			fs_dprपूर्णांकk (FS_DEBUG_OPEN, "pcr = %d.\n", pcr);
		पूर्ण
      
		tc->TMC[0] = पंचांगc0 | 0x4000;
		tc->TMC[1] = 0; /* Unused */
		tc->TMC[2] = 0; /* Unused */
		tc->TMC[3] = 0; /* Unused */
    
		tc->spec = 0;    /* UTOPIA address, UDF, HEC: Unused -> 0 */
		tc->rtag[0] = 0; /* What should I करो with routing tags??? 
				    -- Not used -- AS -- Thanks -- REW*/
		tc->rtag[1] = 0;
		tc->rtag[2] = 0;

		अगर (fs_debug & FS_DEBUG_OPEN) अणु
			fs_dprपूर्णांकk (FS_DEBUG_OPEN, "TX config record:\n");
			my_hd (tc, माप (*tc));
		पूर्ण

		/* We now use the "submit_command" function to submit commands to
		   the firestream. There is a define up near the definition of
		   that routine that चयनes this routine between immediate ग_लिखो
		   to the immediate command रेजिस्टरs and queuing the commands in
		   the HPTXQ क्रम execution. This last technique might be more
		   efficient अगर we know we're going to submit a whole lot of
		   commands in one go, but this driver is not setup to be able to
		   use such a स्थिरruct. So it probably करोen't matter much right
		   now. -- REW */
    
		/* The command is IMMediate and INQueue. The parameters are out-of-line.. */
		submit_command (dev, &dev->hp_txq, 
				QE_CMD_CONFIG_TX | QE_CMD_IMM_INQ | vcc->channo,
				virt_to_bus (tc), 0, 0);

		submit_command (dev, &dev->hp_txq, 
				QE_CMD_TX_EN | QE_CMD_IMM_INQ | vcc->channo,
				0, 0, 0);
		set_bit (vcc->channo, dev->tx_inuse);
	पूर्ण

	अगर (DO_सूचीECTION (rxtp)) अणु
		dev->aपंचांग_vccs[vcc->channo] = aपंचांग_vcc;

		क्रम (bfp = 0;bfp < FS_NR_FREE_POOLS; bfp++)
			अगर (aपंचांग_vcc->qos.rxtp.max_sdu <= dev->rx_fp[bfp].bufsize) अवरोध;
		अगर (bfp >= FS_NR_FREE_POOLS) अणु
			fs_dprपूर्णांकk (FS_DEBUG_OPEN, "No free pool fits sdu: %d.\n", 
				    aपंचांग_vcc->qos.rxtp.max_sdu);
			/* XXX Cleanup? -- Would just calling fs_बंद work??? -- REW */

			/* XXX clear tx inuse. Close TX part? */
			dev->aपंचांग_vccs[vcc->channo] = शून्य;
			kमुक्त (vcc);
			वापस -EINVAL;
		पूर्ण

		चयन (aपंचांग_vcc->qos.aal) अणु
		हाल ATM_AAL0:
		हाल ATM_AAL2:
			submit_command (dev, &dev->hp_txq,
					QE_CMD_CONFIG_RX | QE_CMD_IMM_INQ | vcc->channo,
					RC_FLAGS_TRANSP |
					RC_FLAGS_BFPS_BFP * bfp |
					RC_FLAGS_RXBM_PSB, 0, 0);
			अवरोध;
		हाल ATM_AAL5:
			submit_command (dev, &dev->hp_txq,
					QE_CMD_CONFIG_RX | QE_CMD_IMM_INQ | vcc->channo,
					RC_FLAGS_AAL5 |
					RC_FLAGS_BFPS_BFP * bfp |
					RC_FLAGS_RXBM_PSB, 0, 0);
			अवरोध;
		पूर्ण
		अगर (IS_FS50 (dev)) अणु
			submit_command (dev, &dev->hp_txq, 
					QE_CMD_REG_WR | QE_CMD_IMM_INQ,
					0x80 + vcc->channo,
					(vpi << 16) | vci, 0 ); /* XXX -- Use defines. */
		पूर्ण
		submit_command (dev, &dev->hp_txq, 
				QE_CMD_RX_EN | QE_CMD_IMM_INQ | vcc->channo,
				0, 0, 0);
	पूर्ण
    
	/* Indicate we're करोne! */
	set_bit(ATM_VF_READY, &aपंचांग_vcc->flags);

	func_निकास ();
	वापस 0;
पूर्ण


अटल व्योम fs_बंद(काष्ठा aपंचांग_vcc *aपंचांग_vcc)
अणु
	काष्ठा fs_dev *dev = FS_DEV (aपंचांग_vcc->dev);
	काष्ठा fs_vcc *vcc = FS_VCC (aपंचांग_vcc);
	काष्ठा aपंचांग_trafprm * txtp;
	काष्ठा aपंचांग_trafprm * rxtp;

	func_enter ();

	clear_bit(ATM_VF_READY, &aपंचांग_vcc->flags);

	fs_dprपूर्णांकk (FS_DEBUG_QSIZE, "--==**[%d]**==--", dev->ntxpckts);
	अगर (vcc->last_skb) अणु
		fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "Waiting for skb %p to be sent.\n", 
			    vcc->last_skb);
		/* We're going to रुको क्रम the last packet to get sent on this VC. It would
		   be impolite not to send them करोn't you think? 
		   XXX
		   We करोn't know which packets didn't get sent. So अगर we get पूर्णांकerrupted in 
		   this sleep_on, we'll lose any reference to these packets. Memory leak!
		   On the other hand, it's awfully convenient that we can पात a "close" that
		   is taking too दीर्घ. Maybe just use non-पूर्णांकerruptible sleep on? -- REW */
		रुको_event_पूर्णांकerruptible(vcc->बंद_रुको, !vcc->last_skb);
	पूर्ण

	txtp = &aपंचांग_vcc->qos.txtp;
	rxtp = &aपंचांग_vcc->qos.rxtp;
  

	/* See App note XXX (Unpublished as of now) क्रम the reason क्रम the 
	   removal of the "CMD_IMM_INQ" part of the TX_PURGE_INH... -- REW */

	अगर (DO_सूचीECTION (txtp)) अणु
		submit_command (dev,  &dev->hp_txq,
				QE_CMD_TX_PURGE_INH | /*QE_CMD_IMM_INQ|*/ vcc->channo, 0,0,0);
		clear_bit (vcc->channo, dev->tx_inuse);
	पूर्ण

	अगर (DO_सूचीECTION (rxtp)) अणु
		submit_command (dev,  &dev->hp_txq,
				QE_CMD_RX_PURGE_INH | QE_CMD_IMM_INQ | vcc->channo, 0,0,0);
		dev->aपंचांग_vccs [vcc->channo] = शून्य;
  
		/* This means that this is configured as a receive channel */
		अगर (IS_FS50 (dev)) अणु
			/* Disable the receive filter. Is 0/0 indeed an invalid receive
			   channel? -- REW.  Yes it is. -- Hang. Ok. I'll use -1
			   (0xfff...) -- REW */
			submit_command (dev, &dev->hp_txq, 
					QE_CMD_REG_WR | QE_CMD_IMM_INQ,
					0x80 + vcc->channo, -1, 0 ); 
		पूर्ण
	पूर्ण

	fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free vcc: %p\n", vcc);
	kमुक्त (vcc);

	func_निकास ();
पूर्ण


अटल पूर्णांक fs_send (काष्ठा aपंचांग_vcc *aपंचांग_vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा fs_dev *dev = FS_DEV (aपंचांग_vcc->dev);
	काष्ठा fs_vcc *vcc = FS_VCC (aपंचांग_vcc);
	काष्ठा FS_BPENTRY *td;

	func_enter ();

	fs_dprपूर्णांकk (FS_DEBUG_TXMEM, "I");
	fs_dprपूर्णांकk (FS_DEBUG_SEND, "Send: atm_vcc %p skb %p vcc %p dev %p\n", 
		    aपंचांग_vcc, skb, vcc, dev);

	fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Alloc t-skb: %p (atm_send)\n", skb);

	ATM_SKB(skb)->vcc = aपंचांग_vcc;

	vcc->last_skb = skb;

	td = kदो_स्मृति (माप (काष्ठा FS_BPENTRY), GFP_ATOMIC);
	fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Alloc transd: %p(%zd)\n", td, माप (काष्ठा FS_BPENTRY));
	अगर (!td) अणु
		/* Oops out of mem */
		वापस -ENOMEM;
	पूर्ण

	fs_dprपूर्णांकk (FS_DEBUG_SEND, "first word in buffer: %x\n", 
		    *(पूर्णांक *) skb->data);

	td->flags =  TD_EPI | TD_DATA | skb->len;
	td->next = 0;
	td->bsa  = virt_to_bus (skb->data);
	td->skb = skb;
	td->dev = dev;
	dev->ntxpckts++;

#अगर_घोषित DEBUG_EXTRA
	da[qd] = td;
	dq[qd].flags = td->flags;
	dq[qd].next  = td->next;
	dq[qd].bsa   = td->bsa;
	dq[qd].skb   = td->skb;
	dq[qd].dev   = td->dev;
	qd++;
	अगर (qd >= 60) qd = 0;
#पूर्ण_अगर

	submit_queue (dev, &dev->hp_txq, 
		      QE_TRANSMIT_DE | vcc->channo,
		      virt_to_bus (td), 0, 
		      virt_to_bus (td));

	fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "in send: txq %d txrq %d\n", 
		    पढ़ो_fs (dev, Q_EA (dev->hp_txq.offset)) -
		    पढ़ो_fs (dev, Q_SA (dev->hp_txq.offset)),
		    पढ़ो_fs (dev, Q_EA (dev->tx_relq.offset)) -
		    पढ़ो_fs (dev, Q_SA (dev->tx_relq.offset)));

	func_निकास ();
	वापस 0;
पूर्ण


/* Some function placeholders क्रम functions we करोn't yet support. */

#अगर 0
अटल पूर्णांक fs_ioctl(काष्ठा aपंचांग_dev *dev,अचिन्हित पूर्णांक cmd,व्योम __user *arg)
अणु
	func_enter ();
	func_निकास ();
	वापस -ENOIOCTLCMD;
पूर्ण


अटल पूर्णांक fs_माला_लोockopt(काष्ठा aपंचांग_vcc *vcc,पूर्णांक level,पूर्णांक optname,
			 व्योम __user *optval,पूर्णांक optlen)
अणु
	func_enter ();
	func_निकास ();
	वापस 0;
पूर्ण


अटल पूर्णांक fs_setsockopt(काष्ठा aपंचांग_vcc *vcc,पूर्णांक level,पूर्णांक optname,
			 व्योम __user *optval,अचिन्हित पूर्णांक optlen)
अणु
	func_enter ();
	func_निकास ();
	वापस 0;
पूर्ण


अटल व्योम fs_phy_put(काष्ठा aपंचांग_dev *dev,अचिन्हित अक्षर value,
		       अचिन्हित दीर्घ addr)
अणु
	func_enter ();
	func_निकास ();
पूर्ण


अटल अचिन्हित अक्षर fs_phy_get(काष्ठा aपंचांग_dev *dev,अचिन्हित दीर्घ addr)
अणु
	func_enter ();
	func_निकास ();
	वापस 0;
पूर्ण


अटल पूर्णांक fs_change_qos(काष्ठा aपंचांग_vcc *vcc,काष्ठा aपंचांग_qos *qos,पूर्णांक flags)
अणु
	func_enter ();
	func_निकास ();
	वापस 0;
पूर्ण;

#पूर्ण_अगर


अटल स्थिर काष्ठा aपंचांगdev_ops ops = अणु
	.खोलो =         fs_खोलो,
	.बंद =        fs_बंद,
	.send =         fs_send,
	.owner =        THIS_MODULE,
	/* ioctl:          fs_ioctl, */
	/* change_qos:     fs_change_qos, */

	/* For now implement these पूर्णांकernally here... */  
	/* phy_put:        fs_phy_put, */
	/* phy_get:        fs_phy_get, */
पूर्ण;


अटल व्योम unकरोcumented_pci_fix(काष्ठा pci_dev *pdev)
अणु
	u32 tपूर्णांक;

	/* The Winकरोws driver says: */
	/* Switch off FireStream Retry Limit Threshold 
	 */

	/* The रेजिस्टर at 0x28 is करोcumented as "reserved", no further
	   comments. */

	pci_पढ़ो_config_dword (pdev, 0x28, &tपूर्णांक);
	अगर (tपूर्णांक != 0x80) अणु
		tपूर्णांक = 0x80;
		pci_ग_लिखो_config_dword (pdev, 0x28, tपूर्णांक);
	पूर्ण
पूर्ण



/**************************************************************************
 *                              PHY routines                              *
 **************************************************************************/

अटल व्योम ग_लिखो_phy(काष्ठा fs_dev *dev, पूर्णांक regnum, पूर्णांक val)
अणु
	submit_command (dev,  &dev->hp_txq, QE_CMD_PRP_WR | QE_CMD_IMM_INQ,
			regnum, val, 0);
पूर्ण

अटल पूर्णांक init_phy(काष्ठा fs_dev *dev, काष्ठा reginit_item *reginit)
अणु
	पूर्णांक i;

	func_enter ();
	जबतक (reginit->reg != PHY_खातापूर्ण) अणु
		अगर (reginit->reg == PHY_CLEARALL) अणु
			/* "PHY_CLEARALL means clear all registers. Numregisters is in "val". */
			क्रम (i=0;i<reginit->val;i++) अणु
				ग_लिखो_phy (dev, i, 0);
			पूर्ण
		पूर्ण अन्यथा अणु
			ग_लिखो_phy (dev, reginit->reg, reginit->val);
		पूर्ण
		reginit++;
	पूर्ण
	func_निकास ();
	वापस 0;
पूर्ण

अटल व्योम reset_chip (काष्ठा fs_dev *dev)
अणु
	पूर्णांक i;

	ग_लिखो_fs (dev, SARMODE0, SARMODE0_SRTS0);

	/* Unकरोcumented delay */
	udelay (128);

	/* The "पूर्णांकernal रेजिस्टरs are करोcumented to all reset to zero, but 
	   comments & code in the Winकरोws driver indicates that the pools are
	   NOT reset. */
	क्रम (i=0;i < FS_NR_FREE_POOLS;i++) अणु
		ग_लिखो_fs (dev, FP_CNF (RXB_FP(i)), 0);
		ग_लिखो_fs (dev, FP_SA  (RXB_FP(i)), 0);
		ग_लिखो_fs (dev, FP_EA  (RXB_FP(i)), 0);
		ग_लिखो_fs (dev, FP_CNT (RXB_FP(i)), 0);
		ग_लिखो_fs (dev, FP_CTU (RXB_FP(i)), 0);
	पूर्ण

	/* The same goes क्रम the match channel रेजिस्टरs, although those are
	   NOT करोcumented that way in the Winकरोws driver. -- REW */
	/* The Winकरोws driver DOES ग_लिखो 0 to these रेजिस्टरs somewhere in
	   the init sequence. However, a small hardware-feature, will
	   prevent reception of data on VPI/VCI = 0/0 (Unless the channel
	   allocated happens to have no disabled channels that have a lower
	   number. -- REW */

	/* Clear the match channel रेजिस्टरs. */
	अगर (IS_FS50 (dev)) अणु
		क्रम (i=0;i<FS50_NR_CHANNELS;i++) अणु
			ग_लिखो_fs (dev, 0x200 + i * 4, -1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम *aligned_kदो_स्मृति(पूर्णांक size, gfp_t flags, पूर्णांक alignment)
अणु
	व्योम  *t;

	अगर (alignment <= 0x10) अणु
		t = kदो_स्मृति (size, flags);
		अगर ((अचिन्हित दीर्घ)t & (alignment-1)) अणु
			prपूर्णांकk ("Kmalloc doesn't align things correctly! %p\n", t);
			kमुक्त (t);
			वापस aligned_kदो_स्मृति (size, flags, alignment * 4);
		पूर्ण
		वापस t;
	पूर्ण
	prपूर्णांकk (KERN_ERR "Request for > 0x10 alignment not yet implemented (hard!)\n");
	वापस शून्य;
पूर्ण

अटल पूर्णांक init_q(काष्ठा fs_dev *dev, काष्ठा queue *txq, पूर्णांक queue,
		  पूर्णांक nentries, पूर्णांक is_rq)
अणु
	पूर्णांक sz = nentries * माप (काष्ठा FS_QENTRY);
	काष्ठा FS_QENTRY *p;

	func_enter ();

	fs_dprपूर्णांकk (FS_DEBUG_INIT, "Initializing queue at %x: %d entries:\n",
		    queue, nentries);

	p = aligned_kदो_स्मृति (sz, GFP_KERNEL, 0x10);
	fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Alloc queue: %p(%d)\n", p, sz);

	अगर (!p) वापस 0;

	ग_लिखो_fs (dev, Q_SA(queue), virt_to_bus(p));
	ग_लिखो_fs (dev, Q_EA(queue), virt_to_bus(p+nentries-1));
	ग_लिखो_fs (dev, Q_WP(queue), virt_to_bus(p));
	ग_लिखो_fs (dev, Q_RP(queue), virt_to_bus(p));
	अगर (is_rq) अणु
		/* Configuration क्रम the receive queue: 0: पूर्णांकerrupt immediately,
		   no pre-warning to empty queues: We करो our best to keep the
		   queue filled anyway. */
		ग_लिखो_fs (dev, Q_CNF(queue), 0 ); 
	पूर्ण

	txq->sa = p;
	txq->ea = p;
	txq->offset = queue; 

	func_निकास ();
	वापस 1;
पूर्ण


अटल पूर्णांक init_fp(काष्ठा fs_dev *dev, काष्ठा मुक्तpool *fp, पूर्णांक queue,
		   पूर्णांक bufsize, पूर्णांक nr_buffers)
अणु
	func_enter ();

	fs_dprपूर्णांकk (FS_DEBUG_INIT, "Initializing free pool at %x:\n", queue);

	ग_लिखो_fs (dev, FP_CNF(queue), (bufsize * RBFP_RBS) | RBFP_RBSVAL | RBFP_CME);
	ग_लिखो_fs (dev, FP_SA(queue),  0);
	ग_लिखो_fs (dev, FP_EA(queue),  0);
	ग_लिखो_fs (dev, FP_CTU(queue), 0);
	ग_लिखो_fs (dev, FP_CNT(queue), 0);

	fp->offset = queue; 
	fp->bufsize = bufsize;
	fp->nr_buffers = nr_buffers;

	func_निकास ();
	वापस 1;
पूर्ण


अटल अंतरभूत पूर्णांक nr_buffers_in_मुक्तpool (काष्ठा fs_dev *dev, काष्ठा मुक्तpool *fp)
अणु
#अगर 0
	/* This seems to be unreliable.... */
	वापस पढ़ो_fs (dev, FP_CNT (fp->offset));
#अन्यथा
	वापस fp->n;
#पूर्ण_अगर
पूर्ण


/* Check अगर this माला_लो going again अगर a pool ever runs out.  -- Yes, it
   करोes. I've seen "receive abort: no buffers" and things started
   working again after that...  -- REW */

अटल व्योम top_off_fp (काष्ठा fs_dev *dev, काष्ठा मुक्तpool *fp,
			gfp_t gfp_flags)
अणु
	काष्ठा FS_BPENTRY *qe, *ne;
	काष्ठा sk_buff *skb;
	पूर्णांक n = 0;
	u32 qe_पंचांगp;

	fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "Topping off queue at %x (%d-%d/%d)\n", 
		    fp->offset, पढ़ो_fs (dev, FP_CNT (fp->offset)), fp->n, 
		    fp->nr_buffers);
	जबतक (nr_buffers_in_मुक्तpool(dev, fp) < fp->nr_buffers) अणु

		skb = alloc_skb (fp->bufsize, gfp_flags);
		fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Alloc rec-skb: %p(%d)\n", skb, fp->bufsize);
		अगर (!skb) अवरोध;
		ne = kदो_स्मृति (माप (काष्ठा FS_BPENTRY), gfp_flags);
		fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Alloc rec-d: %p(%zd)\n", ne, माप (काष्ठा FS_BPENTRY));
		अगर (!ne) अणु
			fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free rec-skb: %p\n", skb);
			dev_kमुक्त_skb_any (skb);
			अवरोध;
		पूर्ण

		fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "Adding skb %p desc %p -> %p(%p) ", 
			    skb, ne, skb->data, skb->head);
		n++;
		ne->flags = FP_FLAGS_EPI | fp->bufsize;
		ne->next  = virt_to_bus (शून्य);
		ne->bsa   = virt_to_bus (skb->data);
		ne->aal_bufsize = fp->bufsize;
		ne->skb = skb;
		ne->fp = fp;

		/*
		 * FIXME: following code encodes and decodes
		 * machine poपूर्णांकers (could be 64-bit) पूर्णांकo a
		 * 32-bit रेजिस्टर.
		 */

		qe_पंचांगp = पढ़ो_fs (dev, FP_EA(fp->offset));
		fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "link at %x\n", qe_पंचांगp);
		अगर (qe_पंचांगp) अणु
			qe = bus_to_virt ((दीर्घ) qe_पंचांगp);
			qe->next = virt_to_bus(ne);
			qe->flags &= ~FP_FLAGS_EPI;
		पूर्ण अन्यथा
			ग_लिखो_fs (dev, FP_SA(fp->offset), virt_to_bus(ne));

		ग_लिखो_fs (dev, FP_EA(fp->offset), virt_to_bus (ne));
		fp->n++;   /* XXX Atomic_inc? */
		ग_लिखो_fs (dev, FP_CTU(fp->offset), 1);
	पूर्ण

	fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "Added %d entries. \n", n);
पूर्ण

अटल व्योम मुक्त_queue(काष्ठा fs_dev *dev, काष्ठा queue *txq)
अणु
	func_enter ();

	ग_लिखो_fs (dev, Q_SA(txq->offset), 0);
	ग_लिखो_fs (dev, Q_EA(txq->offset), 0);
	ग_लिखो_fs (dev, Q_RP(txq->offset), 0);
	ग_लिखो_fs (dev, Q_WP(txq->offset), 0);
	/* Configuration ? */

	fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free queue: %p\n", txq->sa);
	kमुक्त (txq->sa);

	func_निकास ();
पूर्ण

अटल व्योम मुक्त_मुक्तpool(काष्ठा fs_dev *dev, काष्ठा मुक्तpool *fp)
अणु
	func_enter ();

	ग_लिखो_fs (dev, FP_CNF(fp->offset), 0);
	ग_लिखो_fs (dev, FP_SA (fp->offset), 0);
	ग_लिखो_fs (dev, FP_EA (fp->offset), 0);
	ग_लिखो_fs (dev, FP_CNT(fp->offset), 0);
	ग_लिखो_fs (dev, FP_CTU(fp->offset), 0);

	func_निकास ();
पूर्ण



अटल irqवापस_t fs_irq (पूर्णांक irq, व्योम *dev_id) 
अणु
	पूर्णांक i;
	u32 status;
	काष्ठा fs_dev *dev = dev_id;

	status = पढ़ो_fs (dev, ISR);
	अगर (!status)
		वापस IRQ_NONE;

	func_enter ();

#अगर_घोषित IRQ_RATE_LIMIT
	/* Aaargh! I'm ashamed. This costs more lines-of-code than the actual 
	   पूर्णांकerrupt routine!. (Well, used to when I wrote that comment) -- REW */
	अणु
		अटल पूर्णांक lastjअगर;
		अटल पूर्णांक nपूर्णांकr=0;
    
		अगर (lastjअगर == jअगरfies) अणु
			अगर (++nपूर्णांकr > IRQ_RATE_LIMIT) अणु
				मुक्त_irq (dev->irq, dev_id);
				prपूर्णांकk (KERN_ERR "fs: Too many interrupts. Turning off interrupt %d.\n", 
					dev->irq);
			पूर्ण
		पूर्ण अन्यथा अणु
			lastjअगर = jअगरfies;
			nपूर्णांकr = 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	fs_dprपूर्णांकk (FS_DEBUG_QUEUE, "in intr: txq %d txrq %d\n", 
		    पढ़ो_fs (dev, Q_EA (dev->hp_txq.offset)) -
		    पढ़ो_fs (dev, Q_SA (dev->hp_txq.offset)),
		    पढ़ो_fs (dev, Q_EA (dev->tx_relq.offset)) -
		    पढ़ो_fs (dev, Q_SA (dev->tx_relq.offset)));

	/* prपूर्णांक the bits in the ISR रेजिस्टर. */
	अगर (fs_debug & FS_DEBUG_IRQ) अणु
		/* The FS_DEBUG things are unnecessary here. But this way it is
		   clear क्रम grep that these are debug prपूर्णांकs. */
		fs_dprपूर्णांकk (FS_DEBUG_IRQ,  "IRQ status:");
		क्रम (i=0;i<27;i++) 
			अगर (status & (1 << i)) 
				fs_dprपूर्णांकk (FS_DEBUG_IRQ, " %s", irq_bitname[i]);
		fs_dprपूर्णांकk (FS_DEBUG_IRQ, "\n");
	पूर्ण
  
	अगर (status & ISR_RBRQ0_W) अणु
		fs_dprपूर्णांकk (FS_DEBUG_IRQ, "Iiiin-coming (0)!!!!\n");
		process_incoming (dev, &dev->rx_rq[0]);
		/* items mentioned on RBRQ0 are from FP 0 or 1. */
		top_off_fp (dev, &dev->rx_fp[0], GFP_ATOMIC);
		top_off_fp (dev, &dev->rx_fp[1], GFP_ATOMIC);
	पूर्ण

	अगर (status & ISR_RBRQ1_W) अणु
		fs_dprपूर्णांकk (FS_DEBUG_IRQ, "Iiiin-coming (1)!!!!\n");
		process_incoming (dev, &dev->rx_rq[1]);
		top_off_fp (dev, &dev->rx_fp[2], GFP_ATOMIC);
		top_off_fp (dev, &dev->rx_fp[3], GFP_ATOMIC);
	पूर्ण

	अगर (status & ISR_RBRQ2_W) अणु
		fs_dprपूर्णांकk (FS_DEBUG_IRQ, "Iiiin-coming (2)!!!!\n");
		process_incoming (dev, &dev->rx_rq[2]);
		top_off_fp (dev, &dev->rx_fp[4], GFP_ATOMIC);
		top_off_fp (dev, &dev->rx_fp[5], GFP_ATOMIC);
	पूर्ण

	अगर (status & ISR_RBRQ3_W) अणु
		fs_dprपूर्णांकk (FS_DEBUG_IRQ, "Iiiin-coming (3)!!!!\n");
		process_incoming (dev, &dev->rx_rq[3]);
		top_off_fp (dev, &dev->rx_fp[6], GFP_ATOMIC);
		top_off_fp (dev, &dev->rx_fp[7], GFP_ATOMIC);
	पूर्ण

	अगर (status & ISR_CSQ_W) अणु
		fs_dprपूर्णांकk (FS_DEBUG_IRQ, "Command executed ok!\n");
		process_वापस_queue (dev, &dev->st_q);
	पूर्ण

	अगर (status & ISR_TBRQ_W) अणु
		fs_dprपूर्णांकk (FS_DEBUG_IRQ, "Data transmitted!\n");
		process_txकरोne_queue (dev, &dev->tx_relq);
	पूर्ण

	func_निकास ();
	वापस IRQ_HANDLED;
पूर्ण


#अगर_घोषित FS_POLL_FREQ
अटल व्योम fs_poll (काष्ठा समयr_list *t)
अणु
	काष्ठा fs_dev *dev = from_समयr(dev, t, समयr);
  
	fs_irq (0, dev);
	dev->समयr.expires = jअगरfies + FS_POLL_FREQ;
	add_समयr (&dev->समयr);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक fs_init(काष्ठा fs_dev *dev)
अणु
	काष्ठा pci_dev  *pci_dev;
	पूर्णांक isr, to;
	पूर्णांक i;

	func_enter ();
	pci_dev = dev->pci_dev;

	prपूर्णांकk (KERN_INFO "found a FireStream %d card, base %16llx, irq%d.\n",
		IS_FS50(dev)?50:155,
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci_dev, 0),
		dev->pci_dev->irq);

	अगर (fs_debug & FS_DEBUG_INIT)
		my_hd ((अचिन्हित अक्षर *) dev, माप (*dev));

	unकरोcumented_pci_fix (pci_dev);

	dev->hw_base = pci_resource_start(pci_dev, 0);

	dev->base = ioremap(dev->hw_base, 0x1000);

	reset_chip (dev);
  
	ग_लिखो_fs (dev, SARMODE0, 0 
		  | (0 * SARMODE0_SHADEN) /* We करोn't use shaकरोw रेजिस्टरs. */
		  | (1 * SARMODE0_INTMODE_READCLEAR)
		  | (1 * SARMODE0_CWRE)
		  | (IS_FS50(dev) ? SARMODE0_PRPWT_FS50_5:
			  SARMODE0_PRPWT_FS155_3)
		  | (1 * SARMODE0_CALSUP_1)
		  | (IS_FS50(dev) ? (0
				   | SARMODE0_RXVCS_32
				   | SARMODE0_ABRVCS_32 
				   | SARMODE0_TXVCS_32):
		                  (0
				   | SARMODE0_RXVCS_1k
				   | SARMODE0_ABRVCS_1k 
				   | SARMODE0_TXVCS_1k)));

	/* 10ms * 100 is 1 second. That should be enough, as AN3:9 says it takes
	   1ms. */
	to = 100;
	जबतक (--to) अणु
		isr = पढ़ो_fs (dev, ISR);

		/* This bit is करोcumented as "RESERVED" */
		अगर (isr & ISR_INIT_ERR) अणु
			prपूर्णांकk (KERN_ERR "Error initializing the FS... \n");
			जाओ unmap;
		पूर्ण
		अगर (isr & ISR_INIT) अणु
			fs_dprपूर्णांकk (FS_DEBUG_INIT, "Ha! Initialized OK!\n");
			अवरोध;
		पूर्ण

		/* Try again after 10ms. */
		msleep(10);
	पूर्ण

	अगर (!to) अणु
		prपूर्णांकk (KERN_ERR "timeout initializing the FS... \n");
		जाओ unmap;
	पूर्ण

	/* XXX fix क्रम fs155 */
	dev->channel_mask = 0x1f; 
	dev->channo = 0;

	/* AN3: 10 */
	ग_लिखो_fs (dev, SARMODE1, 0 
		  | (fs_keystream * SARMODE1_DEFHEC) /* XXX PHY */
		  | ((loopback == 1) * SARMODE1_TSTLP) /* XXX Loopback mode enable... */
		  | (1 * SARMODE1_DCRM)
		  | (1 * SARMODE1_DCOAM)
		  | (0 * SARMODE1_OAMCRC)
		  | (0 * SARMODE1_DUMPE)
		  | (0 * SARMODE1_GPLEN) 
		  | (0 * SARMODE1_GNAM)
		  | (0 * SARMODE1_GVAS)
		  | (0 * SARMODE1_GPAS)
		  | (1 * SARMODE1_GPRI)
		  | (0 * SARMODE1_PMS)
		  | (0 * SARMODE1_GFCR)
		  | (1 * SARMODE1_HECM2)
		  | (1 * SARMODE1_HECM1)
		  | (1 * SARMODE1_HECM0)
		  | (1 << 12) /* That's what hang's driver करोes. Program to 0 */
		  | (0 * 0xff) /* XXX FS155 */);


	/* Cal prescale etc */

	/* AN3: 11 */
	ग_लिखो_fs (dev, TMCONF, 0x0000000f);
	ग_लिखो_fs (dev, CALPRESCALE, 0x01010101 * num);
	ग_लिखो_fs (dev, 0x80, 0x000F00E4);

	/* AN3: 12 */
	ग_लिखो_fs (dev, CELLOSCONF, 0
		  | (   0 * CELLOSCONF_CEN)
		  | (       CELLOSCONF_SC1)
		  | (0x80 * CELLOSCONF_COBS)
		  | (num  * CELLOSCONF_COPK)  /* Changed from 0xff to 0x5a */
		  | (num  * CELLOSCONF_COST));/* after a hपूर्णांक from Hang. 
					       * perक्रमmance jumped 50->70... */

	/* Magic value by Hang */
	ग_लिखो_fs (dev, CELLOSCONF_COST, 0x0B809191);

	अगर (IS_FS50 (dev)) अणु
		ग_लिखो_fs (dev, RAS0, RAS0_DCD_XHLT);
		dev->aपंचांग_dev->ci_range.vpi_bits = 12;
		dev->aपंचांग_dev->ci_range.vci_bits = 16;
		dev->nchannels = FS50_NR_CHANNELS;
	पूर्ण अन्यथा अणु
		ग_लिखो_fs (dev, RAS0, RAS0_DCD_XHLT 
			  | (((1 << FS155_VPI_BITS) - 1) * RAS0_VPSEL)
			  | (((1 << FS155_VCI_BITS) - 1) * RAS0_VCSEL));
		/* We can chose the split arbitrarily. We might be able to 
		   support more. Whatever. This should करो क्रम now. */
		dev->aपंचांग_dev->ci_range.vpi_bits = FS155_VPI_BITS;
		dev->aपंचांग_dev->ci_range.vci_bits = FS155_VCI_BITS;
    
		/* Address bits we can't use should be compared to 0. */
		ग_लिखो_fs (dev, RAC, 0);

		/* Manual (AN9, page 6) says ASF1=0 means compare Utopia address
		 * too.  I can't find ASF1 anywhere. Anyway, we AND with just the
		 * other bits, then compare with 0, which is exactly what we
		 * want. */
		ग_लिखो_fs (dev, RAM, (1 << (28 - FS155_VPI_BITS - FS155_VCI_BITS)) - 1);
		dev->nchannels = FS155_NR_CHANNELS;
	पूर्ण
	dev->aपंचांग_vccs = kसुस्मृति (dev->nchannels, माप (काष्ठा aपंचांग_vcc *),
				 GFP_KERNEL);
	fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Alloc atmvccs: %p(%zd)\n",
		    dev->aपंचांग_vccs, dev->nchannels * माप (काष्ठा aपंचांग_vcc *));

	अगर (!dev->aपंचांग_vccs) अणु
		prपूर्णांकk (KERN_WARNING "Couldn't allocate memory for VCC buffers. Woops!\n");
		/* XXX Clean up..... */
		जाओ unmap;
	पूर्ण

	dev->tx_inuse = kzalloc (dev->nchannels / 8 /* bits/byte */ , GFP_KERNEL);
	fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Alloc tx_inuse: %p(%d)\n", 
		    dev->aपंचांग_vccs, dev->nchannels / 8);

	अगर (!dev->tx_inuse) अणु
		prपूर्णांकk (KERN_WARNING "Couldn't allocate memory for tx_inuse bits!\n");
		/* XXX Clean up..... */
		जाओ unmap;
	पूर्ण
	/* -- RAS1 : FS155 and 50 dअगरfer. Default (0) should be OK क्रम both */
	/* -- RAS2 : FS50 only: Default is OK. */

	/* DMAMODE, शेष should be OK. -- REW */
	ग_लिखो_fs (dev, DMAMR, DMAMR_TX_MODE_FULL);

	init_q (dev, &dev->hp_txq, TX_PQ(TXQ_HP), TXQ_NENTRIES, 0);
	init_q (dev, &dev->lp_txq, TX_PQ(TXQ_LP), TXQ_NENTRIES, 0);
	init_q (dev, &dev->tx_relq, TXB_RQ, TXQ_NENTRIES, 1);
	init_q (dev, &dev->st_q, ST_Q, TXQ_NENTRIES, 1);

	क्रम (i=0;i < FS_NR_FREE_POOLS;i++) अणु
		init_fp (dev, &dev->rx_fp[i], RXB_FP(i), 
			 rx_buf_sizes[i], rx_pool_sizes[i]);
		top_off_fp (dev, &dev->rx_fp[i], GFP_KERNEL);
	पूर्ण


	क्रम (i=0;i < FS_NR_RX_QUEUES;i++)
		init_q (dev, &dev->rx_rq[i], RXB_RQ(i), RXRQ_NENTRIES, 1);

	dev->irq = pci_dev->irq;
	अगर (request_irq (dev->irq, fs_irq, IRQF_SHARED, "firestream", dev)) अणु
		prपूर्णांकk (KERN_WARNING "couldn't get irq %d for firestream.\n", pci_dev->irq);
		/* XXX unकरो all previous stuff... */
		जाओ unmap;
	पूर्ण
	fs_dprपूर्णांकk (FS_DEBUG_INIT, "Grabbed irq %d for dev at %p.\n", dev->irq, dev);
  
	/* We want to be notअगरied of most things. Just the statistics count
	   overflows are not पूर्णांकeresting */
	ग_लिखो_fs (dev, IMR, 0
		  | ISR_RBRQ0_W 
		  | ISR_RBRQ1_W 
		  | ISR_RBRQ2_W 
		  | ISR_RBRQ3_W 
		  | ISR_TBRQ_W
		  | ISR_CSQ_W);

	ग_लिखो_fs (dev, SARMODE0, 0 
		  | (0 * SARMODE0_SHADEN) /* We करोn't use shaकरोw रेजिस्टरs. */
		  | (1 * SARMODE0_GINT)
		  | (1 * SARMODE0_INTMODE_READCLEAR)
		  | (0 * SARMODE0_CWRE)
		  | (IS_FS50(dev)?SARMODE0_PRPWT_FS50_5: 
		                  SARMODE0_PRPWT_FS155_3)
		  | (1 * SARMODE0_CALSUP_1)
		  | (IS_FS50 (dev)?(0
				    | SARMODE0_RXVCS_32
				    | SARMODE0_ABRVCS_32 
				    | SARMODE0_TXVCS_32):
		                   (0
				    | SARMODE0_RXVCS_1k
				    | SARMODE0_ABRVCS_1k 
				    | SARMODE0_TXVCS_1k))
		  | (1 * SARMODE0_RUN));

	init_phy (dev, PHY_NTC_INIT);

	अगर (loopback == 2) अणु
		ग_लिखो_phy (dev, 0x39, 0x000e);
	पूर्ण

#अगर_घोषित FS_POLL_FREQ
	समयr_setup(&dev->समयr, fs_poll, 0);
	dev->समयr.expires = jअगरfies + FS_POLL_FREQ;
	add_समयr (&dev->समयr);
#पूर्ण_अगर

	dev->aपंचांग_dev->dev_data = dev;
  
	func_निकास ();
	वापस 0;
unmap:
	iounmap(dev->base);
	वापस 1;
पूर्ण

अटल पूर्णांक firestream_init_one(काष्ठा pci_dev *pci_dev,
			       स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा aपंचांग_dev *aपंचांग_dev;
	काष्ठा fs_dev *fs_dev;
	
	अगर (pci_enable_device(pci_dev)) 
		जाओ err_out;

	fs_dev = kzalloc (माप (काष्ठा fs_dev), GFP_KERNEL);
	fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Alloc fs-dev: %p(%zd)\n",
		    fs_dev, माप (काष्ठा fs_dev));
	अगर (!fs_dev)
		जाओ err_out;
	aपंचांग_dev = aपंचांग_dev_रेजिस्टर("fs", &pci_dev->dev, &ops, -1, शून्य);
	अगर (!aपंचांग_dev)
		जाओ err_out_मुक्त_fs_dev;
  
	fs_dev->pci_dev = pci_dev;
	fs_dev->aपंचांग_dev = aपंचांग_dev;
	fs_dev->flags = ent->driver_data;

	अगर (fs_init(fs_dev))
		जाओ err_out_मुक्त_aपंचांग_dev;

	fs_dev->next = fs_boards;
	fs_boards = fs_dev;
	वापस 0;

 err_out_मुक्त_aपंचांग_dev:
	aपंचांग_dev_deरेजिस्टर(aपंचांग_dev);
 err_out_मुक्त_fs_dev:
 	kमुक्त(fs_dev);
 err_out:
	वापस -ENODEV;
पूर्ण

अटल व्योम firestream_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा fs_dev *dev, *nxtdev;
	काष्ठा fs_vcc *vcc;
	काष्ठा FS_BPENTRY *fp, *nxt;
  
	func_enter ();

#अगर 0
	prपूर्णांकk ("hptxq:\n");
	क्रम (i=0;i<60;i++) अणु
		prपूर्णांकk ("%d: %08x %08x %08x %08x \n", 
			i, pq[qp].cmd, pq[qp].p0, pq[qp].p1, pq[qp].p2);
		qp++;
		अगर (qp >= 60) qp = 0;
	पूर्ण

	prपूर्णांकk ("descriptors:\n");
	क्रम (i=0;i<60;i++) अणु
		prपूर्णांकk ("%d: %p: %08x %08x %p %p\n", 
			i, da[qd], dq[qd].flags, dq[qd].bsa, dq[qd].skb, dq[qd].dev);
		qd++;
		अगर (qd >= 60) qd = 0;
	पूर्ण
#पूर्ण_अगर

	क्रम (dev = fs_boards;dev != शून्य;dev=nxtdev) अणु
		fs_dprपूर्णांकk (FS_DEBUG_CLEANUP, "Releasing resources for dev at %p.\n", dev);

		/* XXX Hit all the tx channels too! */

		क्रम (i=0;i < dev->nchannels;i++) अणु
			अगर (dev->aपंचांग_vccs[i]) अणु
				vcc = FS_VCC (dev->aपंचांग_vccs[i]);
				submit_command (dev,  &dev->hp_txq,
						QE_CMD_TX_PURGE_INH | QE_CMD_IMM_INQ | vcc->channo, 0,0,0);
				submit_command (dev,  &dev->hp_txq,
						QE_CMD_RX_PURGE_INH | QE_CMD_IMM_INQ | vcc->channo, 0,0,0);

			पूर्ण
		पूर्ण

		/* XXX Wait a जबतक क्रम the chip to release all buffers. */

		क्रम (i=0;i < FS_NR_FREE_POOLS;i++) अणु
			क्रम (fp=bus_to_virt (पढ़ो_fs (dev, FP_SA(dev->rx_fp[i].offset)));
			     !(fp->flags & FP_FLAGS_EPI);fp = nxt) अणु
				fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free rec-skb: %p\n", fp->skb);
				dev_kमुक्त_skb_any (fp->skb);
				nxt = bus_to_virt (fp->next);
				fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free rec-d: %p\n", fp);
				kमुक्त (fp);
			पूर्ण
			fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free rec-skb: %p\n", fp->skb);
			dev_kमुक्त_skb_any (fp->skb);
			fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free rec-d: %p\n", fp);
			kमुक्त (fp);
		पूर्ण

		/* Hang the chip in "reset", prevent it clobbering memory that is
		   no दीर्घer ours. */
		reset_chip (dev);

		fs_dprपूर्णांकk (FS_DEBUG_CLEANUP, "Freeing irq%d.\n", dev->irq);
		मुक्त_irq (dev->irq, dev);
		del_समयr_sync (&dev->समयr);

		aपंचांग_dev_deरेजिस्टर(dev->aपंचांग_dev);
		मुक्त_queue (dev, &dev->hp_txq);
		मुक्त_queue (dev, &dev->lp_txq);
		मुक्त_queue (dev, &dev->tx_relq);
		मुक्त_queue (dev, &dev->st_q);

		fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free atmvccs: %p\n", dev->aपंचांग_vccs);
		kमुक्त (dev->aपंचांग_vccs);

		क्रम (i=0;i< FS_NR_FREE_POOLS;i++)
			मुक्त_मुक्तpool (dev, &dev->rx_fp[i]);
    
		क्रम (i=0;i < FS_NR_RX_QUEUES;i++)
			मुक्त_queue (dev, &dev->rx_rq[i]);

		iounmap(dev->base);
		fs_dprपूर्णांकk (FS_DEBUG_ALLOC, "Free fs-dev: %p\n", dev);
		nxtdev = dev->next;
		kमुक्त (dev);
	पूर्ण

	func_निकास ();
पूर्ण

अटल स्थिर काष्ठा pci_device_id firestream_pci_tbl[] = अणु
	अणु PCI_VDEVICE(FUJITSU_ME, PCI_DEVICE_ID_FUJITSU_FS50), FS_IS50पूर्ण,
	अणु PCI_VDEVICE(FUJITSU_ME, PCI_DEVICE_ID_FUJITSU_FS155), FS_IS155पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, firestream_pci_tbl);

अटल काष्ठा pci_driver firestream_driver = अणु
	.name		= "firestream",
	.id_table	= firestream_pci_tbl,
	.probe		= firestream_init_one,
	.हटाओ		= firestream_हटाओ_one,
पूर्ण;

अटल पूर्णांक __init firestream_init_module (व्योम)
अणु
	पूर्णांक error;

	func_enter ();
	error = pci_रेजिस्टर_driver(&firestream_driver);
	func_निकास ();
	वापस error;
पूर्ण

अटल व्योम __निकास firestream_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&firestream_driver);
पूर्ण

module_init(firestream_init_module);
module_निकास(firestream_cleanup_module);

MODULE_LICENSE("GPL");



