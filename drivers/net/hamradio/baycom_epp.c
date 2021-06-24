<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*****************************************************************************/

/*
 *	baycom_epp.c  -- baycom epp radio modem driver.
 *
 *	Copyright (C) 1998-2000
 *          Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *  Please note that the GPL allows you to use the driver, NOT the radio.
 *  In order to use the radio, you need a license from the communications
 *  authority of your country.
 *
 *  History:
 *   0.1  xx.xx.1998  Initial version by Matthias Welwarsky (dg2fef)
 *   0.2  21.04.1998  Massive rework by Thomas Sailer
 *                    Integrated FPGA EPP modem configuration routines
 *   0.3  11.05.1998  Took FPGA config out and moved it पूर्णांकo a separate program
 *   0.4  26.07.1999  Adapted to new lowlevel parport driver पूर्णांकerface
 *   0.5  03.08.1999  adapt to Linus' new __setup/__initcall
 *                    हटाओd some pre-2.2 kernel compatibility cruft
 *   0.6  10.08.1999  Check अगर parport can करो SPP and is safe to access during पूर्णांकerrupt contexts
 *   0.7  12.02.2000  adapted to softnet driver पूर्णांकerface
 */

/*****************************************************************************/

#समावेश <linux/crc-ccitt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/fs.h>
#समावेश <linux/parport.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/hdlcdrv.h>
#समावेश <linux/baycom.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/अक्रमom.h>
#समावेश <net/ax25.h> 
#समावेश <linux/uaccess.h>

/* --------------------------------------------------------------------- */

#घोषणा BAYCOM_DEBUG
#घोषणा BAYCOM_MAGIC 19730510

/* --------------------------------------------------------------------- */

अटल स्थिर अक्षर paranoia_str[] = KERN_ERR 
	"baycom_epp: bad magic number for hdlcdrv_state struct in routine %s\n";

अटल स्थिर अक्षर bc_drvname[] = "baycom_epp";
अटल स्थिर अक्षर bc_drvinfo[] = KERN_INFO "baycom_epp: (C) 1998-2000 Thomas Sailer, HB9JNX/AE4WA\n"
"baycom_epp: version 0.7\n";

/* --------------------------------------------------------------------- */

#घोषणा NR_PORTS 4

अटल काष्ठा net_device *baycom_device[NR_PORTS];

/* --------------------------------------------------------------------- */

/* EPP status रेजिस्टर */
#घोषणा EPP_DCDBIT      0x80
#घोषणा EPP_PTTBIT      0x08
#घोषणा EPP_NREF        0x01
#घोषणा EPP_NRAEF       0x02
#घोषणा EPP_NRHF        0x04
#घोषणा EPP_NTHF        0x20
#घोषणा EPP_NTAEF       0x10
#घोषणा EPP_NTEF        EPP_PTTBIT

/* EPP control रेजिस्टर */
#घोषणा EPP_TX_FIFO_ENABLE 0x10
#घोषणा EPP_RX_FIFO_ENABLE 0x08
#घोषणा EPP_MODEM_ENABLE   0x20
#घोषणा EPP_LEDS           0xC0
#घोषणा EPP_IRQ_ENABLE     0x10

/* LPT रेजिस्टरs */
#घोषणा LPTREG_ECONTROL       0x402
#घोषणा LPTREG_CONFIGB        0x401
#घोषणा LPTREG_CONFIGA        0x400
#घोषणा LPTREG_EPPDATA        0x004
#घोषणा LPTREG_EPPADDR        0x003
#घोषणा LPTREG_CONTROL        0x002
#घोषणा LPTREG_STATUS         0x001
#घोषणा LPTREG_DATA           0x000

/* LPT control रेजिस्टर */
#घोषणा LPTCTRL_PROGRAM       0x04   /* 0 to reprogram */
#घोषणा LPTCTRL_WRITE         0x01
#घोषणा LPTCTRL_ADDRSTB       0x08
#घोषणा LPTCTRL_DATASTB       0x02
#घोषणा LPTCTRL_INTEN         0x10

/* LPT status रेजिस्टर */
#घोषणा LPTSTAT_SHIFT_NINTR   6
#घोषणा LPTSTAT_WAIT          0x80
#घोषणा LPTSTAT_NINTR         (1<<LPTSTAT_SHIFT_NINTR)
#घोषणा LPTSTAT_PE            0x20
#घोषणा LPTSTAT_DONE          0x10
#घोषणा LPTSTAT_NERROR        0x08
#घोषणा LPTSTAT_EPPTIMEOUT    0x01

/* LPT data रेजिस्टर */
#घोषणा LPTDATA_SHIFT_TDI     0
#घोषणा LPTDATA_SHIFT_TMS     2
#घोषणा LPTDATA_TDI           (1<<LPTDATA_SHIFT_TDI)
#घोषणा LPTDATA_TCK           0x02
#घोषणा LPTDATA_TMS           (1<<LPTDATA_SHIFT_TMS)
#घोषणा LPTDATA_INITBIAS      0x80


/* EPP modem config/status bits */
#घोषणा EPP_DCDBIT            0x80
#घोषणा EPP_PTTBIT            0x08
#घोषणा EPP_RXEBIT            0x01
#घोषणा EPP_RXAEBIT           0x02
#घोषणा EPP_RXHFULL           0x04

#घोषणा EPP_NTHF              0x20
#घोषणा EPP_NTAEF             0x10
#घोषणा EPP_NTEF              EPP_PTTBIT

#घोषणा EPP_TX_FIFO_ENABLE    0x10
#घोषणा EPP_RX_FIFO_ENABLE    0x08
#घोषणा EPP_MODEM_ENABLE      0x20
#घोषणा EPP_LEDS              0xC0
#घोषणा EPP_IRQ_ENABLE        0x10

/* Xilinx 4k JTAG inकाष्ठाions */
#घोषणा XC4K_IRLENGTH   3
#घोषणा XC4K_EXTEST     0
#घोषणा XC4K_PRELOAD    1
#घोषणा XC4K_CONFIGURE  5
#घोषणा XC4K_BYPASS     7

#घोषणा EPP_CONVENTIONAL  0
#घोषणा EPP_FPGA          1
#घोषणा EPP_FPGAEXTSTATUS 2

#घोषणा TXBUFFER_SIZE     ((HDLCDRV_MAXFLEN*6/5)+8)

/* ---------------------------------------------------------------------- */
/*
 * Inक्रमmation that need to be kept क्रम each board.
 */

काष्ठा baycom_state अणु
	पूर्णांक magic;

        काष्ठा pardevice *pdev;
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक work_running;
	काष्ठा delayed_work run_work;
	अचिन्हित पूर्णांक modem;
	अचिन्हित पूर्णांक bitrate;
	अचिन्हित अक्षर stat;

	काष्ठा अणु
		अचिन्हित पूर्णांक पूर्णांकclk;
		अचिन्हित पूर्णांक fclk;
		अचिन्हित पूर्णांक bps;
		अचिन्हित पूर्णांक exपंचांगodem;
		अचिन्हित पूर्णांक loopback;
	पूर्ण cfg;

        काष्ठा hdlcdrv_channel_params ch_params;

        काष्ठा अणु
		अचिन्हित पूर्णांक bitbuf, bitstream, numbits, state;
		अचिन्हित अक्षर *bufptr;
		पूर्णांक bufcnt;
		अचिन्हित अक्षर buf[TXBUFFER_SIZE];
        पूर्ण hdlcrx;

        काष्ठा अणु
		पूर्णांक calibrate;
                पूर्णांक slotcnt;
		पूर्णांक flags;
		क्रमागत अणु tx_idle = 0, tx_keyup, tx_data, tx_tail पूर्ण state;
		अचिन्हित अक्षर *bufptr;
		पूर्णांक bufcnt;
		अचिन्हित अक्षर buf[TXBUFFER_SIZE];
        पूर्ण hdlctx;

	अचिन्हित पूर्णांक ptt_keyed;
	काष्ठा sk_buff *skb;  /* next transmit packet  */

#अगर_घोषित BAYCOM_DEBUG
	काष्ठा debug_vals अणु
		अचिन्हित दीर्घ last_jअगरfies;
		अचिन्हित cur_पूर्णांकcnt;
		अचिन्हित last_पूर्णांकcnt;
		पूर्णांक cur_pllcorr;
		पूर्णांक last_pllcorr;
		अचिन्हित पूर्णांक mod_cycles;
		अचिन्हित पूर्णांक demod_cycles;
	पूर्ण debug_vals;
#पूर्ण_अगर /* BAYCOM_DEBUG */
पूर्ण;

/* --------------------------------------------------------------------- */

#घोषणा KISS_VERBOSE

/* --------------------------------------------------------------------- */

#घोषणा PARAM_TXDELAY   1
#घोषणा PARAM_PERSIST   2
#घोषणा PARAM_SLOTTIME  3
#घोषणा PARAM_TXTAIL    4
#घोषणा PARAM_FULLDUP   5
#घोषणा PARAM_HARDWARE  6
#घोषणा PARAM_RETURN    255

/* --------------------------------------------------------------------- */
/*
 * the CRC routines are stolen from WAMPES
 * by Dieter Deyke
 */


/*---------------------------------------------------------------------------*/

#अगर 0
अटल अंतरभूत व्योम append_crc_ccitt(अचिन्हित अक्षर *buffer, पूर्णांक len)
अणु
 	अचिन्हित पूर्णांक crc = 0xffff;

	क्रम (;len>0;len--)
		crc = (crc >> 8) ^ crc_ccitt_table[(crc ^ *buffer++) & 0xff];
	crc ^= 0xffff;
	*buffer++ = crc;
	*buffer++ = crc >> 8;
पूर्ण
#पूर्ण_अगर

/*---------------------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक check_crc_ccitt(स्थिर अचिन्हित अक्षर *buf, पूर्णांक cnt)
अणु
	वापस (crc_ccitt(0xffff, buf, cnt) & 0xffff) == 0xf0b8;
पूर्ण

/*---------------------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक calc_crc_ccitt(स्थिर अचिन्हित अक्षर *buf, पूर्णांक cnt)
अणु
	वापस (crc_ccitt(0xffff, buf, cnt) ^ 0xffff) & 0xffff;
पूर्ण

/* ---------------------------------------------------------------------- */

#घोषणा tenms_to_flags(bc,tenms) ((tenms * bc->bitrate) / 800)

/* --------------------------------------------------------------------- */

अटल अंतरभूत व्योम baycom_पूर्णांक_freq(काष्ठा baycom_state *bc)
अणु
#अगर_घोषित BAYCOM_DEBUG
	अचिन्हित दीर्घ cur_jअगरfies = jअगरfies;
	/*
	 * measure the पूर्णांकerrupt frequency
	 */
	bc->debug_vals.cur_पूर्णांकcnt++;
	अगर (समय_after_eq(cur_jअगरfies, bc->debug_vals.last_jअगरfies + HZ)) अणु
		bc->debug_vals.last_jअगरfies = cur_jअगरfies;
		bc->debug_vals.last_पूर्णांकcnt = bc->debug_vals.cur_पूर्णांकcnt;
		bc->debug_vals.cur_पूर्णांकcnt = 0;
		bc->debug_vals.last_pllcorr = bc->debug_vals.cur_pllcorr;
		bc->debug_vals.cur_pllcorr = 0;
	पूर्ण
#पूर्ण_अगर /* BAYCOM_DEBUG */
पूर्ण

/* ---------------------------------------------------------------------- */
/*
 *    eppconfig_path should be setable  via /proc/sys.
 */

अटल अक्षर स्थिर eppconfig_path[] = "/usr/sbin/eppfpga";

अटल अक्षर *envp[] = अणु "HOME=/", "TERM=linux", "PATH=/usr/bin:/bin", शून्य पूर्ण;

/* eppconfig: called during अगरconfig up to configure the modem */
अटल पूर्णांक eppconfig(काष्ठा baycom_state *bc)
अणु
	अक्षर modearg[256];
	अक्षर portarg[16];
        अक्षर *argv[] = अणु
		(अक्षर *)eppconfig_path,
		"-s",
		"-p", portarg,
		"-m", modearg,
		शून्य पूर्ण;

	/* set up arguments */
	प्र_लिखो(modearg, "%sclk,%smodem,fclk=%d,bps=%d,divider=%d%s,extstat",
		bc->cfg.पूर्णांकclk ? "int" : "ext",
		bc->cfg.exपंचांगodem ? "ext" : "int", bc->cfg.fclk, bc->cfg.bps,
		(bc->cfg.fclk + 8 * bc->cfg.bps) / (16 * bc->cfg.bps),
		bc->cfg.loopback ? ",loopback" : "");
	प्र_लिखो(portarg, "%ld", bc->pdev->port->base);
	prपूर्णांकk(KERN_DEBUG "%s: %s -s -p %s -m %s\n", bc_drvname, eppconfig_path, portarg, modearg);

	वापस call_usermodehelper(eppconfig_path, argv, envp, UMH_WAIT_PROC);
पूर्ण

/* ---------------------------------------------------------------------- */

अटल अंतरभूत व्योम करो_kiss_params(काष्ठा baycom_state *bc,
				  अचिन्हित अक्षर *data, अचिन्हित दीर्घ len)
अणु

#अगर_घोषित KISS_VERBOSE
#घोषणा PKP(a,b) prपूर्णांकk(KERN_INFO "baycomm_epp: channel params: " a "\n", b)
#अन्यथा /* KISS_VERBOSE */	      
#घोषणा PKP(a,b) 
#पूर्ण_अगर /* KISS_VERBOSE */	      

	अगर (len < 2)
		वापस;
	चयन(data[0]) अणु
	हाल PARAM_TXDELAY:
		bc->ch_params.tx_delay = data[1];
		PKP("TX delay = %ums", 10 * bc->ch_params.tx_delay);
		अवरोध;
	हाल PARAM_PERSIST:   
		bc->ch_params.ppersist = data[1];
		PKP("p persistence = %u", bc->ch_params.ppersist);
		अवरोध;
	हाल PARAM_SLOTTIME:  
		bc->ch_params.slotसमय = data[1];
		PKP("slot time = %ums", bc->ch_params.slotसमय);
		अवरोध;
	हाल PARAM_TXTAIL:    
		bc->ch_params.tx_tail = data[1];
		PKP("TX tail = %ums", bc->ch_params.tx_tail);
		अवरोध;
	हाल PARAM_FULLDUP:   
		bc->ch_params.fulldup = !!data[1];
		PKP("%s duplex", bc->ch_params.fulldup ? "full" : "half");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
#अघोषित PKP
पूर्ण

/* --------------------------------------------------------------------- */

अटल व्योम encode_hdlc(काष्ठा baycom_state *bc)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *wp, *bp;
	पूर्णांक pkt_len;
        अचिन्हित bitstream, notbitstream, bitbuf, numbit, crc;
	अचिन्हित अक्षर crcarr[2];
	पूर्णांक j;
	
	अगर (bc->hdlctx.bufcnt > 0)
		वापस;
	skb = bc->skb;
	अगर (!skb)
		वापस;
	bc->skb = शून्य;
	pkt_len = skb->len-1; /* strip KISS byte */
	wp = bc->hdlctx.buf;
	bp = skb->data+1;
	crc = calc_crc_ccitt(bp, pkt_len);
	crcarr[0] = crc;
	crcarr[1] = crc >> 8;
	*wp++ = 0x7e;
	bitstream = bitbuf = numbit = 0;
	जबतक (pkt_len > -2) अणु
		bitstream >>= 8;
		bitstream |= ((अचिन्हित पूर्णांक)*bp) << 8;
		bitbuf |= ((अचिन्हित पूर्णांक)*bp) << numbit;
		notbitstream = ~bitstream;
		bp++;
		pkt_len--;
		अगर (!pkt_len)
			bp = crcarr;
		क्रम (j = 0; j < 8; j++)
			अगर (unlikely(!(notbitstream & (0x1f0 << j)))) अणु
				bitstream &= ~(0x100 << j);
 				bitbuf = (bitbuf & (((2 << j) << numbit) - 1)) |
					((bitbuf & ~(((2 << j) << numbit) - 1)) << 1);
				numbit++;
				notbitstream = ~bitstream;
			पूर्ण
		numbit += 8;
		जबतक (numbit >= 8) अणु
			*wp++ = bitbuf;
			bitbuf >>= 8;
			numbit -= 8;
		पूर्ण
	पूर्ण
	bitbuf |= 0x7e7e << numbit;
	numbit += 16;
	जबतक (numbit >= 8) अणु
		*wp++ = bitbuf;
		bitbuf >>= 8;
		numbit -= 8;
	पूर्ण
	bc->hdlctx.bufptr = bc->hdlctx.buf;
	bc->hdlctx.bufcnt = wp - bc->hdlctx.buf;
	dev_kमुक्त_skb(skb);
	bc->dev->stats.tx_packets++;
पूर्ण

/* ---------------------------------------------------------------------- */

अटल पूर्णांक transmit(काष्ठा baycom_state *bc, पूर्णांक cnt, अचिन्हित अक्षर stat)
अणु
	काष्ठा parport *pp = bc->pdev->port;
	अचिन्हित अक्षर पंचांगp[128];
	पूर्णांक i, j;

	अगर (bc->hdlctx.state == tx_tail && !(stat & EPP_PTTBIT))
		bc->hdlctx.state = tx_idle;
	अगर (bc->hdlctx.state == tx_idle && bc->hdlctx.calibrate <= 0) अणु
		अगर (bc->hdlctx.bufcnt <= 0)
			encode_hdlc(bc);
		अगर (bc->hdlctx.bufcnt <= 0)
			वापस 0;
		अगर (!bc->ch_params.fulldup) अणु
			अगर (!(stat & EPP_DCDBIT)) अणु
				bc->hdlctx.slotcnt = bc->ch_params.slotसमय;
				वापस 0;
			पूर्ण
			अगर ((--bc->hdlctx.slotcnt) > 0)
				वापस 0;
			bc->hdlctx.slotcnt = bc->ch_params.slotसमय;
			अगर ((pअक्रमom_u32() % 256) > bc->ch_params.ppersist)
				वापस 0;
		पूर्ण
	पूर्ण
	अगर (bc->hdlctx.state == tx_idle && bc->hdlctx.bufcnt > 0) अणु
		bc->hdlctx.state = tx_keyup;
		bc->hdlctx.flags = tenms_to_flags(bc, bc->ch_params.tx_delay);
		bc->ptt_keyed++;
	पूर्ण
	जबतक (cnt > 0) अणु
		चयन (bc->hdlctx.state) अणु
		हाल tx_keyup:
			i = min_t(पूर्णांक, cnt, bc->hdlctx.flags);
			cnt -= i;
			bc->hdlctx.flags -= i;
			अगर (bc->hdlctx.flags <= 0)
				bc->hdlctx.state = tx_data;
			स_रखो(पंचांगp, 0x7e, माप(पंचांगp));
			जबतक (i > 0) अणु
				j = (i > माप(पंचांगp)) ? माप(पंचांगp) : i;
				अगर (j != pp->ops->epp_ग_लिखो_data(pp, पंचांगp, j, 0))
					वापस -1;
				i -= j;
			पूर्ण
			अवरोध;

		हाल tx_data:
			अगर (bc->hdlctx.bufcnt <= 0) अणु
				encode_hdlc(bc);
				अगर (bc->hdlctx.bufcnt <= 0) अणु
					bc->hdlctx.state = tx_tail;
					bc->hdlctx.flags = tenms_to_flags(bc, bc->ch_params.tx_tail);
					अवरोध;
				पूर्ण
			पूर्ण
			i = min_t(पूर्णांक, cnt, bc->hdlctx.bufcnt);
			bc->hdlctx.bufcnt -= i;
			cnt -= i;
			अगर (i != pp->ops->epp_ग_लिखो_data(pp, bc->hdlctx.bufptr, i, 0))
					वापस -1;
			bc->hdlctx.bufptr += i;
			अवरोध;
			
		हाल tx_tail:
			encode_hdlc(bc);
			अगर (bc->hdlctx.bufcnt > 0) अणु
				bc->hdlctx.state = tx_data;
				अवरोध;
			पूर्ण
			i = min_t(पूर्णांक, cnt, bc->hdlctx.flags);
			अगर (i) अणु
				cnt -= i;
				bc->hdlctx.flags -= i;
				स_रखो(पंचांगp, 0x7e, माप(पंचांगp));
				जबतक (i > 0) अणु
					j = (i > माप(पंचांगp)) ? माप(पंचांगp) : i;
					अगर (j != pp->ops->epp_ग_लिखो_data(pp, पंचांगp, j, 0))
						वापस -1;
					i -= j;
				पूर्ण
				अवरोध;
			पूर्ण
			fallthrough;

		शेष:
			अगर (bc->hdlctx.calibrate <= 0)
				वापस 0;
			i = min_t(पूर्णांक, cnt, bc->hdlctx.calibrate);
			cnt -= i;
			bc->hdlctx.calibrate -= i;
			स_रखो(पंचांगp, 0, माप(पंचांगp));
			जबतक (i > 0) अणु
				j = (i > माप(पंचांगp)) ? माप(पंचांगp) : i;
				अगर (j != pp->ops->epp_ग_लिखो_data(pp, पंचांगp, j, 0))
					वापस -1;
				i -= j;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------- */

अटल व्योम करो_rxpacket(काष्ठा net_device *dev)
अणु
	काष्ठा baycom_state *bc = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *cp;
	अचिन्हित pktlen;

	अगर (bc->hdlcrx.bufcnt < 4) 
		वापस;
	अगर (!check_crc_ccitt(bc->hdlcrx.buf, bc->hdlcrx.bufcnt)) 
		वापस;
	pktlen = bc->hdlcrx.bufcnt-2+1; /* KISS kludge */
	अगर (!(skb = dev_alloc_skb(pktlen))) अणु
		prपूर्णांकk("%s: memory squeeze, dropping packet\n", dev->name);
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण
	cp = skb_put(skb, pktlen);
	*cp++ = 0; /* KISS kludge */
	स_नकल(cp, bc->hdlcrx.buf, pktlen - 1);
	skb->protocol = ax25_type_trans(skb, dev);
	netअगर_rx(skb);
	dev->stats.rx_packets++;
पूर्ण

अटल पूर्णांक receive(काष्ठा net_device *dev, पूर्णांक cnt)
अणु
	काष्ठा baycom_state *bc = netdev_priv(dev);
	काष्ठा parport *pp = bc->pdev->port;
        अचिन्हित पूर्णांक bitbuf, notbitstream, bitstream, numbits, state;
	अचिन्हित अक्षर पंचांगp[128];
        अचिन्हित अक्षर *cp;
	पूर्णांक cnt2, ret = 0;
	पूर्णांक j;
        
        numbits = bc->hdlcrx.numbits;
	state = bc->hdlcrx.state;
	bitstream = bc->hdlcrx.bitstream;
	bitbuf = bc->hdlcrx.bitbuf;
	जबतक (cnt > 0) अणु
		cnt2 = (cnt > माप(पंचांगp)) ? माप(पंचांगp) : cnt;
		cnt -= cnt2;
		अगर (cnt2 != pp->ops->epp_पढ़ो_data(pp, पंचांगp, cnt2, 0)) अणु
			ret = -1;
			अवरोध;
		पूर्ण
		cp = पंचांगp;
		क्रम (; cnt2 > 0; cnt2--, cp++) अणु
			bitstream >>= 8;
			bitstream |= (*cp) << 8;
			bitbuf >>= 8;
			bitbuf |= (*cp) << 8;
			numbits += 8;
			notbitstream = ~bitstream;
			क्रम (j = 0; j < 8; j++) अणु

				/* flag or पात */
			        अगर (unlikely(!(notbitstream & (0x0fc << j)))) अणु

					/* पात received */
					अगर (!(notbitstream & (0x1fc << j)))
						state = 0;

					/* flag received */
					अन्यथा अगर ((bitstream & (0x1fe << j)) == (0x0fc << j)) अणु
						अगर (state)
							करो_rxpacket(dev);
						bc->hdlcrx.bufcnt = 0;
						bc->hdlcrx.bufptr = bc->hdlcrx.buf;
						state = 1;
						numbits = 7-j;
					पूर्ण
				पूर्ण

				/* stuffed bit */
				अन्यथा अगर (unlikely((bitstream & (0x1f8 << j)) == (0xf8 << j))) अणु
					numbits--;
					bitbuf = (bitbuf & ((~0xff) << j)) | ((bitbuf & ~((~0xff) << j)) << 1);
					पूर्ण
				पूर्ण
			जबतक (state && numbits >= 8) अणु
				अगर (bc->hdlcrx.bufcnt >= TXBUFFER_SIZE) अणु
					state = 0;
				पूर्ण अन्यथा अणु
					*(bc->hdlcrx.bufptr)++ = bitbuf >> (16-numbits);
					bc->hdlcrx.bufcnt++;
					numbits -= 8;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
        bc->hdlcrx.numbits = numbits;
	bc->hdlcrx.state = state;
	bc->hdlcrx.bitstream = bitstream;
	bc->hdlcrx.bitbuf = bitbuf;
	वापस ret;
पूर्ण

/* --------------------------------------------------------------------- */

#अगर_घोषित __i386__
#समावेश <यंत्र/msr.h>
#घोषणा GETTICK(x)						\
(अणु								\
	अगर (boot_cpu_has(X86_FEATURE_TSC))			\
		x = (अचिन्हित पूर्णांक)rdtsc();			\
पूर्ण)
#अन्यथा /* __i386__ */
#घोषणा GETTICK(x)
#पूर्ण_अगर /* __i386__ */

अटल व्योम epp_bh(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा net_device *dev;
	काष्ठा baycom_state *bc;
	काष्ठा parport *pp;
	अचिन्हित अक्षर stat;
	अचिन्हित अक्षर पंचांगp[2];
	अचिन्हित पूर्णांक समय1 = 0, समय2 = 0, समय3 = 0;
	पूर्णांक cnt, cnt2;

	bc = container_of(work, काष्ठा baycom_state, run_work.work);
	dev = bc->dev;
	अगर (!bc->work_running)
		वापस;
	baycom_पूर्णांक_freq(bc);
	pp = bc->pdev->port;
	/* update status */
	अगर (pp->ops->epp_पढ़ो_addr(pp, &stat, 1, 0) != 1)
		जाओ eppसमयout;
	bc->stat = stat;
	bc->debug_vals.last_pllcorr = stat;
	GETTICK(समय1);
	अगर (bc->modem == EPP_FPGAEXTSTATUS) अणु
		/* get input count */
		पंचांगp[0] = EPP_TX_FIFO_ENABLE|EPP_RX_FIFO_ENABLE|EPP_MODEM_ENABLE|1;
		अगर (pp->ops->epp_ग_लिखो_addr(pp, पंचांगp, 1, 0) != 1)
			जाओ eppसमयout;
		अगर (pp->ops->epp_पढ़ो_addr(pp, पंचांगp, 2, 0) != 2)
			जाओ eppसमयout;
		cnt = पंचांगp[0] | (पंचांगp[1] << 8);
		cnt &= 0x7fff;
		/* get output count */
		पंचांगp[0] = EPP_TX_FIFO_ENABLE|EPP_RX_FIFO_ENABLE|EPP_MODEM_ENABLE|2;
		अगर (pp->ops->epp_ग_लिखो_addr(pp, पंचांगp, 1, 0) != 1)
			जाओ eppसमयout;
		अगर (pp->ops->epp_पढ़ो_addr(pp, पंचांगp, 2, 0) != 2)
			जाओ eppसमयout;
		cnt2 = पंचांगp[0] | (पंचांगp[1] << 8);
		cnt2 = 16384 - (cnt2 & 0x7fff);
		/* वापस to normal */
		पंचांगp[0] = EPP_TX_FIFO_ENABLE|EPP_RX_FIFO_ENABLE|EPP_MODEM_ENABLE;
		अगर (pp->ops->epp_ग_लिखो_addr(pp, पंचांगp, 1, 0) != 1)
			जाओ eppसमयout;
		अगर (transmit(bc, cnt2, stat))
			जाओ eppसमयout;
		GETTICK(समय2);
		अगर (receive(dev, cnt))
			जाओ eppसमयout;
		अगर (pp->ops->epp_पढ़ो_addr(pp, &stat, 1, 0) != 1)
			जाओ eppसमयout;
		bc->stat = stat;
	पूर्ण अन्यथा अणु
		/* try to tx */
		चयन (stat & (EPP_NTAEF|EPP_NTHF)) अणु
		हाल EPP_NTHF:
			cnt = 2048 - 256;
			अवरोध;
		
		हाल EPP_NTAEF:
			cnt = 2048 - 1793;
			अवरोध;
		
		हाल 0:
			cnt = 0;
			अवरोध;
		
		शेष:
			cnt = 2048 - 1025;
			अवरोध;
		पूर्ण
		अगर (transmit(bc, cnt, stat))
			जाओ eppसमयout;
		GETTICK(समय2);
		/* करो receiver */
		जबतक ((stat & (EPP_NRAEF|EPP_NRHF)) != EPP_NRHF) अणु
			चयन (stat & (EPP_NRAEF|EPP_NRHF)) अणु
			हाल EPP_NRAEF:
				cnt = 1025;
				अवरोध;

			हाल 0:
				cnt = 1793;
				अवरोध;

			शेष:
				cnt = 256;
				अवरोध;
			पूर्ण
			अगर (receive(dev, cnt))
				जाओ eppसमयout;
			अगर (pp->ops->epp_पढ़ो_addr(pp, &stat, 1, 0) != 1)
				जाओ eppसमयout;
		पूर्ण
		cnt = 0;
		अगर (bc->bitrate < 50000)
			cnt = 256;
		अन्यथा अगर (bc->bitrate < 100000)
			cnt = 128;
		जबतक (cnt > 0 && stat & EPP_NREF) अणु
			अगर (receive(dev, 1))
				जाओ eppसमयout;
			cnt--;
			अगर (pp->ops->epp_पढ़ो_addr(pp, &stat, 1, 0) != 1)
				जाओ eppसमयout;
		पूर्ण
	पूर्ण
	GETTICK(समय3);
#अगर_घोषित BAYCOM_DEBUG
	bc->debug_vals.mod_cycles = समय2 - समय1;
	bc->debug_vals.demod_cycles = समय3 - समय2;
#पूर्ण_अगर /* BAYCOM_DEBUG */
	schedule_delayed_work(&bc->run_work, 1);
	अगर (!bc->skb)
		netअगर_wake_queue(dev);
	वापस;
 eppसमयout:
	prपूर्णांकk(KERN_ERR "%s: EPP timeout!\n", bc_drvname);
पूर्ण

/* ---------------------------------------------------------------------- */
/*
 * ===================== network driver पूर्णांकerface =========================
 */

अटल पूर्णांक baycom_send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा baycom_state *bc = netdev_priv(dev);

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस ax25_ip_xmit(skb);

	अगर (skb->data[0] != 0) अणु
		करो_kiss_params(bc, skb->data, skb->len);
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (bc->skb) अणु
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	/* strip KISS byte */
	अगर (skb->len >= HDLCDRV_MAXFLEN+1 || skb->len < 3) अणु
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	netअगर_stop_queue(dev);
	bc->skb = skb;
	वापस NETDEV_TX_OK;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक baycom_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = (काष्ठा sockaddr *)addr;

	/* addr is an AX.25 shअगरted ASCII mac address */
	स_नकल(dev->dev_addr, sa->sa_data, dev->addr_len); 
	वापस 0;                                         
पूर्ण

/* --------------------------------------------------------------------- */

अटल व्योम epp_wakeup(व्योम *handle)
अणु
        काष्ठा net_device *dev = (काष्ठा net_device *)handle;
        काष्ठा baycom_state *bc = netdev_priv(dev);

        prपूर्णांकk(KERN_DEBUG "baycom_epp: %s: why am I being woken up?\n", dev->name);
        अगर (!parport_claim(bc->pdev))
                prपूर्णांकk(KERN_DEBUG "baycom_epp: %s: I'm broken.\n", dev->name);
पूर्ण

/* --------------------------------------------------------------------- */

/*
 * Open/initialize the board. This is called (in the current kernel)
 * someसमय after booting when the 'ifconfig' program is run.
 *
 * This routine should set everything up anew at each खोलो, even
 * रेजिस्टरs that "should" only need to be set once at boot, so that
 * there is non-reboot way to recover अगर something goes wrong.
 */

अटल पूर्णांक epp_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा baycom_state *bc = netdev_priv(dev);
        काष्ठा parport *pp = parport_find_base(dev->base_addr);
	अचिन्हित पूर्णांक i, j;
	अचिन्हित अक्षर पंचांगp[128];
	अचिन्हित अक्षर stat;
	अचिन्हित दीर्घ tstart;
	काष्ठा pardev_cb par_cb;
	
        अगर (!pp) अणु
                prपूर्णांकk(KERN_ERR "%s: parport at 0x%lx unknown\n", bc_drvname, dev->base_addr);
                वापस -ENXIO;
        पूर्ण
#अगर 0
        अगर (pp->irq < 0) अणु
                prपूर्णांकk(KERN_ERR "%s: parport at 0x%lx has no irq\n", bc_drvname, pp->base);
		parport_put_port(pp);
                वापस -ENXIO;
        पूर्ण
#पूर्ण_अगर
	अगर ((~pp->modes) & (PARPORT_MODE_TRISTATE | PARPORT_MODE_PCSPP | PARPORT_MODE_SAFEININT)) अणु
                prपूर्णांकk(KERN_ERR "%s: parport at 0x%lx cannot be used\n",
		       bc_drvname, pp->base);
		parport_put_port(pp);
                वापस -EIO;
	पूर्ण
	स_रखो(&bc->modem, 0, माप(bc->modem));
	स_रखो(&par_cb, 0, माप(par_cb));
	par_cb.wakeup = epp_wakeup;
	par_cb.निजी = (व्योम *)dev;
	par_cb.flags = PARPORT_DEV_EXCL;
	क्रम (i = 0; i < NR_PORTS; i++)
		अगर (baycom_device[i] == dev)
			अवरोध;

	अगर (i == NR_PORTS) अणु
		pr_err("%s: no device found\n", bc_drvname);
		parport_put_port(pp);
		वापस -ENODEV;
	पूर्ण

	bc->pdev = parport_रेजिस्टर_dev_model(pp, dev->name, &par_cb, i);
	parport_put_port(pp);
        अगर (!bc->pdev) अणु
                prपूर्णांकk(KERN_ERR "%s: cannot register parport at 0x%lx\n", bc_drvname, pp->base);
                वापस -ENXIO;
        पूर्ण
        अगर (parport_claim(bc->pdev)) अणु
                prपूर्णांकk(KERN_ERR "%s: parport at 0x%lx busy\n", bc_drvname, pp->base);
                parport_unरेजिस्टर_device(bc->pdev);
                वापस -EBUSY;
        पूर्ण
        dev->irq = /*pp->irq*/ 0;
	INIT_DELAYED_WORK(&bc->run_work, epp_bh);
	bc->work_running = 1;
	bc->modem = EPP_CONVENTIONAL;
	अगर (eppconfig(bc))
		prपूर्णांकk(KERN_INFO "%s: no FPGA detected, assuming conventional EPP modem\n", bc_drvname);
	अन्यथा
		bc->modem = /*EPP_FPGA*/ EPP_FPGAEXTSTATUS;
	parport_ग_लिखो_control(pp, LPTCTRL_PROGRAM); /* prepare EPP mode; we aren't using पूर्णांकerrupts */
	/* reset the modem */
	पंचांगp[0] = 0;
	पंचांगp[1] = EPP_TX_FIFO_ENABLE|EPP_RX_FIFO_ENABLE|EPP_MODEM_ENABLE;
	अगर (pp->ops->epp_ग_लिखो_addr(pp, पंचांगp, 2, 0) != 2)
		जाओ eppसमयout;
	/* स्वतःprobe baud rate */
	tstart = jअगरfies;
	i = 0;
	जबतक (समय_beक्रमe(jअगरfies, tstart + HZ/3)) अणु
		अगर (pp->ops->epp_पढ़ो_addr(pp, &stat, 1, 0) != 1)
			जाओ eppसमयout;
		अगर ((stat & (EPP_NRAEF|EPP_NRHF)) == EPP_NRHF) अणु
			schedule();
			जारी;
		पूर्ण
		अगर (pp->ops->epp_पढ़ो_data(pp, पंचांगp, 128, 0) != 128)
			जाओ eppसमयout;
		अगर (pp->ops->epp_पढ़ो_data(pp, पंचांगp, 128, 0) != 128)
			जाओ eppसमयout;
		i += 256;
	पूर्ण
	क्रम (j = 0; j < 256; j++) अणु
		अगर (pp->ops->epp_पढ़ो_addr(pp, &stat, 1, 0) != 1)
			जाओ eppसमयout;
		अगर (!(stat & EPP_NREF))
			अवरोध;
		अगर (pp->ops->epp_पढ़ो_data(pp, पंचांगp, 1, 0) != 1)
			जाओ eppसमयout;
		i++;
	पूर्ण
	tstart = jअगरfies - tstart;
	bc->bitrate = i * (8 * HZ) / tstart;
	j = 1;
	i = bc->bitrate >> 3;
	जबतक (j < 7 && i > 150) अणु
		j++;
		i >>= 1;
	पूर्ण
	prपूर्णांकk(KERN_INFO "%s: autoprobed bitrate: %d  int divider: %d  int rate: %d\n", 
	       bc_drvname, bc->bitrate, j, bc->bitrate >> (j+2));
	पंचांगp[0] = EPP_TX_FIFO_ENABLE|EPP_RX_FIFO_ENABLE|EPP_MODEM_ENABLE/*|j*/;
	अगर (pp->ops->epp_ग_लिखो_addr(pp, पंचांगp, 1, 0) != 1)
		जाओ eppसमयout;
	/*
	 * initialise hdlc variables
	 */
	bc->hdlcrx.state = 0;
	bc->hdlcrx.numbits = 0;
	bc->hdlctx.state = tx_idle;
	bc->hdlctx.bufcnt = 0;
	bc->hdlctx.slotcnt = bc->ch_params.slotसमय;
	bc->hdlctx.calibrate = 0;
	/* start the bottom half stuff */
	schedule_delayed_work(&bc->run_work, 1);
	netअगर_start_queue(dev);
	वापस 0;

 eppसमयout:
	prपूर्णांकk(KERN_ERR "%s: epp timeout during bitrate probe\n", bc_drvname);
	parport_ग_लिखो_control(pp, 0); /* reset the adapter */
        parport_release(bc->pdev);
        parport_unरेजिस्टर_device(bc->pdev);
	वापस -EIO;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक epp_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा baycom_state *bc = netdev_priv(dev);
	काष्ठा parport *pp = bc->pdev->port;
	अचिन्हित अक्षर पंचांगp[1];

	bc->work_running = 0;
	cancel_delayed_work_sync(&bc->run_work);
	bc->stat = EPP_DCDBIT;
	पंचांगp[0] = 0;
	pp->ops->epp_ग_लिखो_addr(pp, पंचांगp, 1, 0);
	parport_ग_लिखो_control(pp, 0); /* reset the adapter */
        parport_release(bc->pdev);
        parport_unरेजिस्टर_device(bc->pdev);
	dev_kमुक्त_skb(bc->skb);
	bc->skb = शून्य;
	prपूर्णांकk(KERN_INFO "%s: close epp at iobase 0x%lx irq %u\n",
	       bc_drvname, dev->base_addr, dev->irq);
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक baycom_seपंचांगode(काष्ठा baycom_state *bc, स्थिर अक्षर *modestr)
अणु
	स्थिर अक्षर *cp;

	अगर (म_माला(modestr,"intclk"))
		bc->cfg.पूर्णांकclk = 1;
	अगर (म_माला(modestr,"extclk"))
		bc->cfg.पूर्णांकclk = 0;
	अगर (म_माला(modestr,"intmodem"))
		bc->cfg.exपंचांगodem = 0;
	अगर (म_माला(modestr,"extmodem"))
		bc->cfg.exपंचांगodem = 1;
	अगर (म_माला(modestr,"noloopback"))
		bc->cfg.loopback = 0;
	अगर (म_माला(modestr,"loopback"))
		bc->cfg.loopback = 1;
	अगर ((cp = म_माला(modestr,"fclk="))) अणु
		bc->cfg.fclk = simple_म_से_अदीर्घ(cp+5, शून्य, 0);
		अगर (bc->cfg.fclk < 1000000)
			bc->cfg.fclk = 1000000;
		अगर (bc->cfg.fclk > 25000000)
			bc->cfg.fclk = 25000000;
	पूर्ण
	अगर ((cp = म_माला(modestr,"bps="))) अणु
		bc->cfg.bps = simple_म_से_अदीर्घ(cp+4, शून्य, 0);
		अगर (bc->cfg.bps < 1000)
			bc->cfg.bps = 1000;
		अगर (bc->cfg.bps > 1500000)
			bc->cfg.bps = 1500000;
	पूर्ण
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक baycom_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा baycom_state *bc = netdev_priv(dev);
	काष्ठा hdlcdrv_ioctl hi;

	अगर (cmd != SIOCDEVPRIVATE)
		वापस -ENOIOCTLCMD;

	अगर (copy_from_user(&hi, अगरr->अगरr_data, माप(hi)))
		वापस -EFAULT;
	चयन (hi.cmd) अणु
	शेष:
		वापस -ENOIOCTLCMD;

	हाल HDLCDRVCTL_GETCHANNELPAR:
		hi.data.cp.tx_delay = bc->ch_params.tx_delay;
		hi.data.cp.tx_tail = bc->ch_params.tx_tail;
		hi.data.cp.slotसमय = bc->ch_params.slotसमय;
		hi.data.cp.ppersist = bc->ch_params.ppersist;
		hi.data.cp.fulldup = bc->ch_params.fulldup;
		अवरोध;

	हाल HDLCDRVCTL_SETCHANNELPAR:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EACCES;
		bc->ch_params.tx_delay = hi.data.cp.tx_delay;
		bc->ch_params.tx_tail = hi.data.cp.tx_tail;
		bc->ch_params.slotसमय = hi.data.cp.slotसमय;
		bc->ch_params.ppersist = hi.data.cp.ppersist;
		bc->ch_params.fulldup = hi.data.cp.fulldup;
		bc->hdlctx.slotcnt = 1;
		वापस 0;
		
	हाल HDLCDRVCTL_GETMODEMPAR:
		hi.data.mp.iobase = dev->base_addr;
		hi.data.mp.irq = dev->irq;
		hi.data.mp.dma = dev->dma;
		hi.data.mp.dma2 = 0;
		hi.data.mp.seriobase = 0;
		hi.data.mp.pariobase = 0;
		hi.data.mp.midiiobase = 0;
		अवरोध;

	हाल HDLCDRVCTL_SETMODEMPAR:
		अगर ((!capable(CAP_SYS_RAWIO)) || netअगर_running(dev))
			वापस -EACCES;
		dev->base_addr = hi.data.mp.iobase;
		dev->irq = /*hi.data.mp.irq*/0;
		dev->dma = /*hi.data.mp.dma*/0;
		वापस 0;	
		
	हाल HDLCDRVCTL_GETSTAT:
		hi.data.cs.ptt = !!(bc->stat & EPP_PTTBIT);
		hi.data.cs.dcd = !(bc->stat & EPP_DCDBIT);
		hi.data.cs.ptt_keyed = bc->ptt_keyed;
		hi.data.cs.tx_packets = dev->stats.tx_packets;
		hi.data.cs.tx_errors = dev->stats.tx_errors;
		hi.data.cs.rx_packets = dev->stats.rx_packets;
		hi.data.cs.rx_errors = dev->stats.rx_errors;
		अवरोध;		

	हाल HDLCDRVCTL_OLDGETSTAT:
		hi.data.ocs.ptt = !!(bc->stat & EPP_PTTBIT);
		hi.data.ocs.dcd = !(bc->stat & EPP_DCDBIT);
		hi.data.ocs.ptt_keyed = bc->ptt_keyed;
		अवरोध;		

	हाल HDLCDRVCTL_CALIBRATE:
		अगर (!capable(CAP_SYS_RAWIO))
			वापस -EACCES;
		bc->hdlctx.calibrate = hi.data.calibrate * bc->bitrate / 8;
		वापस 0;

	हाल HDLCDRVCTL_DRIVERNAME:
		म_नकलन(hi.data.drivername, "baycom_epp", माप(hi.data.drivername));
		अवरोध;
		
	हाल HDLCDRVCTL_GETMODE:
		प्र_लिखो(hi.data.modename, "%sclk,%smodem,fclk=%d,bps=%d%s", 
			bc->cfg.पूर्णांकclk ? "int" : "ext",
			bc->cfg.exपंचांगodem ? "ext" : "int", bc->cfg.fclk, bc->cfg.bps,
			bc->cfg.loopback ? ",loopback" : "");
		अवरोध;

	हाल HDLCDRVCTL_SETMODE:
		अगर (!capable(CAP_NET_ADMIN) || netअगर_running(dev))
			वापस -EACCES;
		hi.data.modename[माप(hi.data.modename)-1] = '\0';
		वापस baycom_seपंचांगode(bc, hi.data.modename);

	हाल HDLCDRVCTL_MODELIST:
		म_नकलन(hi.data.modename, "intclk,extclk,intmodem,extmodem,divider=x",
			माप(hi.data.modename));
		अवरोध;

	हाल HDLCDRVCTL_MODEMPARMASK:
		वापस HDLCDRV_PARMASK_IOBASE;

	पूर्ण
	अगर (copy_to_user(अगरr->अगरr_data, &hi, माप(hi)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल स्थिर काष्ठा net_device_ops baycom_netdev_ops = अणु
	.nकरो_खोलो	     = epp_खोलो,
	.nकरो_stop	     = epp_बंद,
	.nकरो_करो_ioctl	     = baycom_ioctl,
	.nकरो_start_xmit      = baycom_send_packet,
	.nकरो_set_mac_address = baycom_set_mac_address,
पूर्ण;

/*
 * Check क्रम a network adaptor of this type, and वापस '0' अगर one exists.
 * If dev->base_addr == 0, probe all likely locations.
 * If dev->base_addr == 1, always वापस failure.
 * If dev->base_addr == 2, allocate space क्रम the device and वापस success
 * (detachable devices only).
 */
अटल व्योम baycom_probe(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा hdlcdrv_channel_params dflt_ch_params = अणु 
		20, 2, 10, 40, 0 
	पूर्ण;
	काष्ठा baycom_state *bc;

	/*
	 * not a real probe! only initialize data काष्ठाures
	 */
	bc = netdev_priv(dev);
	/*
	 * initialize the baycom_state काष्ठा
	 */
	bc->ch_params = dflt_ch_params;
	bc->ptt_keyed = 0;

	/*
	 * initialize the device काष्ठा
	 */

	/* Fill in the fields of the device काष्ठाure */
	bc->skb = शून्य;
	
	dev->netdev_ops = &baycom_netdev_ops;
	dev->header_ops = &ax25_header_ops;
	
	dev->type = ARPHRD_AX25;           /* AF_AX25 device */
	dev->hard_header_len = AX25_MAX_HEADER_LEN + AX25_BPQ_HEADER_LEN;
	dev->mtu = AX25_DEF_PACLEN;        /* eth_mtu is the शेष */
	dev->addr_len = AX25_ADDR_LEN;     /* माप an ax.25 address */
	स_नकल(dev->broadcast, &ax25_bcast, AX25_ADDR_LEN);
	स_नकल(dev->dev_addr, &null_ax25_address, AX25_ADDR_LEN);
	dev->tx_queue_len = 16;

	/* New style flags */
	dev->flags = 0;
पूर्ण

/* --------------------------------------------------------------------- */

/*
 * command line settable parameters
 */
अटल अक्षर *mode[NR_PORTS] = अणु "", पूर्ण;
अटल पूर्णांक iobase[NR_PORTS] = अणु 0x378, पूर्ण;

module_param_array(mode, अक्षरp, शून्य, 0);
MODULE_PARM_DESC(mode, "baycom operating mode");
module_param_hw_array(iobase, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(iobase, "baycom io base address");

MODULE_AUTHOR("Thomas M. Sailer, sailer@ife.ee.ethz.ch, hb9jnx@hb9w.che.eu");
MODULE_DESCRIPTION("Baycom epp amateur radio modem driver");
MODULE_LICENSE("GPL");

/* --------------------------------------------------------------------- */

अटल पूर्णांक baycom_epp_par_probe(काष्ठा pardevice *par_dev)
अणु
	काष्ठा device_driver *drv = par_dev->dev.driver;
	पूर्णांक len = म_माप(drv->name);

	अगर (म_भेदन(par_dev->name, drv->name, len))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल काष्ठा parport_driver baycom_epp_par_driver = अणु
	.name = "bce",
	.probe = baycom_epp_par_probe,
	.devmodel = true,
पूर्ण;

अटल व्योम __init baycom_epp_dev_setup(काष्ठा net_device *dev)
अणु
	काष्ठा baycom_state *bc = netdev_priv(dev);

	/*
	 * initialize part of the baycom_state काष्ठा
	 */
	bc->dev = dev;
	bc->magic = BAYCOM_MAGIC;
	bc->cfg.fclk = 19666600;
	bc->cfg.bps = 9600;
	/*
	 * initialize part of the device काष्ठा
	 */
	baycom_probe(dev);
पूर्ण

अटल पूर्णांक __init init_baycomepp(व्योम)
अणु
	पूर्णांक i, found = 0, ret;
	अक्षर set_hw = 1;

	prपूर्णांकk(bc_drvinfo);

	ret = parport_रेजिस्टर_driver(&baycom_epp_par_driver);
	अगर (ret)
		वापस ret;

	/*
	 * रेजिस्टर net devices
	 */
	क्रम (i = 0; i < NR_PORTS; i++) अणु
		काष्ठा net_device *dev;
		
		dev = alloc_netdev(माप(काष्ठा baycom_state), "bce%d",
				   NET_NAME_UNKNOWN, baycom_epp_dev_setup);

		अगर (!dev) अणु
			prपूर्णांकk(KERN_WARNING "bce%d : out of memory\n", i);
			वापस found ? 0 : -ENOMEM;
		पूर्ण
			
		प्र_लिखो(dev->name, "bce%d", i);
		dev->base_addr = iobase[i];

		अगर (!mode[i])
			set_hw = 0;
		अगर (!set_hw)
			iobase[i] = 0;

		अगर (रेजिस्टर_netdev(dev)) अणु
			prपूर्णांकk(KERN_WARNING "%s: cannot register net device %s\n", bc_drvname, dev->name);
			मुक्त_netdev(dev);
			अवरोध;
		पूर्ण
		अगर (set_hw && baycom_seपंचांगode(netdev_priv(dev), mode[i]))
			set_hw = 0;
		baycom_device[i] = dev;
		found++;
	पूर्ण

	अगर (found == 0) अणु
		parport_unरेजिस्टर_driver(&baycom_epp_par_driver);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास cleanup_baycomepp(व्योम)
अणु
	पूर्णांक i;

	क्रम(i = 0; i < NR_PORTS; i++) अणु
		काष्ठा net_device *dev = baycom_device[i];

		अगर (dev) अणु
			काष्ठा baycom_state *bc = netdev_priv(dev);
			अगर (bc->magic == BAYCOM_MAGIC) अणु
				unरेजिस्टर_netdev(dev);
				मुक्त_netdev(dev);
			पूर्ण अन्यथा
				prपूर्णांकk(paranoia_str, "cleanup_module");
		पूर्ण
	पूर्ण
	parport_unरेजिस्टर_driver(&baycom_epp_par_driver);
पूर्ण

module_init(init_baycomepp);
module_निकास(cleanup_baycomepp);

/* --------------------------------------------------------------------- */

#अगर_अघोषित MODULE

/*
 * क्रमmat: baycom_epp=io,mode
 * mode: fpga config options
 */

अटल पूर्णांक __init baycom_epp_setup(अक्षर *str)
अणु
        अटल अचिन्हित __initdata nr_dev = 0;
	पूर्णांक पूर्णांकs[2];

        अगर (nr_dev >= NR_PORTS)
                वापस 0;
	str = get_options(str, 2, पूर्णांकs);
	अगर (पूर्णांकs[0] < 1)
		वापस 0;
	mode[nr_dev] = str;
	iobase[nr_dev] = पूर्णांकs[1];
	nr_dev++;
	वापस 1;
पूर्ण

__setup("baycom_epp=", baycom_epp_setup);

#पूर्ण_अगर /* MODULE */
/* --------------------------------------------------------------------- */
