<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* $Id: lmc_media.c,v 1.13 2000/04/11 05:25:26 asj Exp $ */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inet.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/processor.h>             /* Processor type क्रम cache alignment. */
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

#समावेश <linux/uaccess.h>

#समावेश "lmc.h"
#समावेश "lmc_var.h"
#समावेश "lmc_ioctl.h"
#समावेश "lmc_debug.h"

#घोषणा CONFIG_LMC_IGNORE_HARDWARE_HANDSHAKE 1

 /*
  * Copyright (c) 1997-2000 LAN Media Corporation (LMC)
  * All rights reserved.  www.lanmedia.com
  *
  * This code is written by:
  * Andrew Stanley-Jones (asj@cban.com)
  * Rob Braun (bbraun@vix.com),
  * Michael Graff (explorer@vix.com) and
  * Matt Thomas (matt@3am-software.com).
  */

/*
 * protocol independent method.
 */
अटल व्योम lmc_set_protocol (lmc_softc_t * स्थिर, lmc_ctl_t *);

/*
 * media independent methods to check on media status, link, light LEDs,
 * etc.
 */
अटल व्योम lmc_ds3_init (lmc_softc_t * स्थिर);
अटल व्योम lmc_ds3_शेष (lmc_softc_t * स्थिर);
अटल व्योम lmc_ds3_set_status (lmc_softc_t * स्थिर, lmc_ctl_t *);
अटल व्योम lmc_ds3_set_100ft (lmc_softc_t * स्थिर, पूर्णांक);
अटल पूर्णांक lmc_ds3_get_link_status (lmc_softc_t * स्थिर);
अटल व्योम lmc_ds3_set_crc_length (lmc_softc_t * स्थिर, पूर्णांक);
अटल व्योम lmc_ds3_set_scram (lmc_softc_t * स्थिर, पूर्णांक);
अटल व्योम lmc_ds3_watchकरोg (lmc_softc_t * स्थिर);

अटल व्योम lmc_hssi_init (lmc_softc_t * स्थिर);
अटल व्योम lmc_hssi_शेष (lmc_softc_t * स्थिर);
अटल व्योम lmc_hssi_set_status (lmc_softc_t * स्थिर, lmc_ctl_t *);
अटल व्योम lmc_hssi_set_घड़ी (lmc_softc_t * स्थिर, पूर्णांक);
अटल पूर्णांक lmc_hssi_get_link_status (lmc_softc_t * स्थिर);
अटल व्योम lmc_hssi_set_link_status (lmc_softc_t * स्थिर, पूर्णांक);
अटल व्योम lmc_hssi_set_crc_length (lmc_softc_t * स्थिर, पूर्णांक);
अटल व्योम lmc_hssi_watchकरोg (lmc_softc_t * स्थिर);

अटल व्योम lmc_ssi_init (lmc_softc_t * स्थिर);
अटल व्योम lmc_ssi_शेष (lmc_softc_t * स्थिर);
अटल व्योम lmc_ssi_set_status (lmc_softc_t * स्थिर, lmc_ctl_t *);
अटल व्योम lmc_ssi_set_घड़ी (lmc_softc_t * स्थिर, पूर्णांक);
अटल व्योम lmc_ssi_set_speed (lmc_softc_t * स्थिर, lmc_ctl_t *);
अटल पूर्णांक lmc_ssi_get_link_status (lmc_softc_t * स्थिर);
अटल व्योम lmc_ssi_set_link_status (lmc_softc_t * स्थिर, पूर्णांक);
अटल व्योम lmc_ssi_set_crc_length (lmc_softc_t * स्थिर, पूर्णांक);
अटल व्योम lmc_ssi_watchकरोg (lmc_softc_t * स्थिर);

अटल व्योम lmc_t1_init (lmc_softc_t * स्थिर);
अटल व्योम lmc_t1_शेष (lmc_softc_t * स्थिर);
अटल व्योम lmc_t1_set_status (lmc_softc_t * स्थिर, lmc_ctl_t *);
अटल पूर्णांक lmc_t1_get_link_status (lmc_softc_t * स्थिर);
अटल व्योम lmc_t1_set_circuit_type (lmc_softc_t * स्थिर, पूर्णांक);
अटल व्योम lmc_t1_set_crc_length (lmc_softc_t * स्थिर, पूर्णांक);
अटल व्योम lmc_t1_set_घड़ी (lmc_softc_t * स्थिर, पूर्णांक);
अटल व्योम lmc_t1_watchकरोg (lmc_softc_t * स्थिर);

अटल व्योम lmc_dummy_set_1 (lmc_softc_t * स्थिर, पूर्णांक);
अटल व्योम lmc_dummy_set2_1 (lmc_softc_t * स्थिर, lmc_ctl_t *);

अटल अंतरभूत व्योम ग_लिखो_av9110_bit (lmc_softc_t *, पूर्णांक);
अटल व्योम ग_लिखो_av9110(lmc_softc_t *, u32, u32, u32, u32, u32);

lmc_media_t lmc_ds3_media = अणु
  .init = lmc_ds3_init,				/* special media init stuff */
  .शेषs = lmc_ds3_शेष,			/* reset to शेष state */
  .set_status = lmc_ds3_set_status,		/* reset status to state provided */
  .set_घड़ी_source = lmc_dummy_set_1,		/* set घड़ी source */
  .set_speed = lmc_dummy_set2_1,		/* set line speed */
  .set_cable_length = lmc_ds3_set_100ft,	/* set cable length */
  .set_scrambler = lmc_ds3_set_scram,		/* set scrambler */
  .get_link_status = lmc_ds3_get_link_status,	/* get link status */
  .set_link_status = lmc_dummy_set_1,		/* set link status */
  .set_crc_length = lmc_ds3_set_crc_length,	/* set CRC length */
  .set_circuit_type = lmc_dummy_set_1,		/* set T1 or E1 circuit type */
  .watchकरोg = lmc_ds3_watchकरोg
पूर्ण;

lmc_media_t lmc_hssi_media = अणु
  .init = lmc_hssi_init,			/* special media init stuff */
  .शेषs = lmc_hssi_शेष,			/* reset to शेष state */
  .set_status = lmc_hssi_set_status,		/* reset status to state provided */
  .set_घड़ी_source = lmc_hssi_set_घड़ी,	/* set घड़ी source */
  .set_speed = lmc_dummy_set2_1,		/* set line speed */
  .set_cable_length = lmc_dummy_set_1,		/* set cable length */
  .set_scrambler = lmc_dummy_set_1,		/* set scrambler */
  .get_link_status = lmc_hssi_get_link_status,	/* get link status */
  .set_link_status = lmc_hssi_set_link_status,	/* set link status */
  .set_crc_length = lmc_hssi_set_crc_length,	/* set CRC length */
  .set_circuit_type = lmc_dummy_set_1,		/* set T1 or E1 circuit type */
  .watchकरोg = lmc_hssi_watchकरोg
पूर्ण;

lmc_media_t lmc_ssi_media = अणु
  .init = lmc_ssi_init,				/* special media init stuff */
  .शेषs = lmc_ssi_शेष,			/* reset to शेष state */
  .set_status = lmc_ssi_set_status,		/* reset status to state provided */
  .set_घड़ी_source = lmc_ssi_set_घड़ी,	/* set घड़ी source */
  .set_speed = lmc_ssi_set_speed,		/* set line speed */
  .set_cable_length = lmc_dummy_set_1,		/* set cable length */
  .set_scrambler = lmc_dummy_set_1,		/* set scrambler */
  .get_link_status = lmc_ssi_get_link_status,	/* get link status */
  .set_link_status = lmc_ssi_set_link_status,	/* set link status */
  .set_crc_length = lmc_ssi_set_crc_length,	/* set CRC length */
  .set_circuit_type = lmc_dummy_set_1,		/* set T1 or E1 circuit type */
  .watchकरोg = lmc_ssi_watchकरोg
पूर्ण;

lmc_media_t lmc_t1_media = अणु
  .init = lmc_t1_init,				/* special media init stuff */
  .शेषs = lmc_t1_शेष,			/* reset to शेष state */
  .set_status = lmc_t1_set_status,		/* reset status to state provided */
  .set_घड़ी_source = lmc_t1_set_घड़ी,		/* set घड़ी source */
  .set_speed = lmc_dummy_set2_1,		/* set line speed */
  .set_cable_length = lmc_dummy_set_1,		/* set cable length */
  .set_scrambler = lmc_dummy_set_1,		/* set scrambler */
  .get_link_status = lmc_t1_get_link_status,	/* get link status */
  .set_link_status = lmc_dummy_set_1,		/* set link status */
  .set_crc_length = lmc_t1_set_crc_length,	/* set CRC length */
  .set_circuit_type = lmc_t1_set_circuit_type,	/* set T1 or E1 circuit type */
  .watchकरोg = lmc_t1_watchकरोg
पूर्ण;

अटल व्योम
lmc_dummy_set_1 (lmc_softc_t * स्थिर sc, पूर्णांक a)
अणु
पूर्ण

अटल व्योम
lmc_dummy_set2_1 (lmc_softc_t * स्थिर sc, lmc_ctl_t * a)
अणु
पूर्ण

/*
 *  HSSI methods
 */

अटल व्योम
lmc_hssi_init (lmc_softc_t * स्थिर sc)
अणु
  sc->ictl.cardtype = LMC_CTL_CARDTYPE_LMC5200;

  lmc_gpio_mkoutput (sc, LMC_GEP_HSSI_CLOCK);
पूर्ण

अटल व्योम
lmc_hssi_शेष (lmc_softc_t * स्थिर sc)
अणु
  sc->lmc_miireg16 = LMC_MII16_LED_ALL;

  sc->lmc_media->set_link_status (sc, LMC_LINK_DOWN);
  sc->lmc_media->set_घड़ी_source (sc, LMC_CTL_CLOCK_SOURCE_EXT);
  sc->lmc_media->set_crc_length (sc, LMC_CTL_CRC_LENGTH_16);
पूर्ण

/*
 * Given a user provided state, set ourselves up to match it.  This will
 * always reset the card अगर needed.
 */
अटल व्योम
lmc_hssi_set_status (lmc_softc_t * स्थिर sc, lmc_ctl_t * ctl)
अणु
  अगर (ctl == शून्य)
    अणु
      sc->lmc_media->set_घड़ी_source (sc, sc->ictl.घड़ी_source);
      lmc_set_protocol (sc, शून्य);

      वापस;
    पूर्ण

  /*
   * check क्रम change in घड़ी source
   */
  अगर (ctl->घड़ी_source && !sc->ictl.घड़ी_source)
    अणु
      sc->lmc_media->set_घड़ी_source (sc, LMC_CTL_CLOCK_SOURCE_INT);
      sc->lmc_timing = LMC_CTL_CLOCK_SOURCE_INT;
    पूर्ण
  अन्यथा अगर (!ctl->घड़ी_source && sc->ictl.घड़ी_source)
    अणु
      sc->lmc_timing = LMC_CTL_CLOCK_SOURCE_EXT;
      sc->lmc_media->set_घड़ी_source (sc, LMC_CTL_CLOCK_SOURCE_EXT);
    पूर्ण

  lmc_set_protocol (sc, ctl);
पूर्ण

/*
 * 1 == पूर्णांकernal, 0 == बाह्यal
 */
अटल व्योम
lmc_hssi_set_घड़ी (lmc_softc_t * स्थिर sc, पूर्णांक ie)
अणु
  पूर्णांक old;
  old = sc->ictl.घड़ी_source;
  अगर (ie == LMC_CTL_CLOCK_SOURCE_EXT)
    अणु
      sc->lmc_gpio |= LMC_GEP_HSSI_CLOCK;
      LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);
      sc->ictl.घड़ी_source = LMC_CTL_CLOCK_SOURCE_EXT;
      अगर(old != ie)
        prपूर्णांकk (LMC_PRINTF_FMT ": clock external\n", LMC_PRINTF_ARGS);
    पूर्ण
  अन्यथा
    अणु
      sc->lmc_gpio &= ~(LMC_GEP_HSSI_CLOCK);
      LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);
      sc->ictl.घड़ी_source = LMC_CTL_CLOCK_SOURCE_INT;
      अगर(old != ie)
        prपूर्णांकk (LMC_PRINTF_FMT ": clock internal\n", LMC_PRINTF_ARGS);
    पूर्ण
पूर्ण

/*
 * वापस hardware link status.
 * 0 == link is करोwn, 1 == link is up.
 */
अटल पूर्णांक
lmc_hssi_get_link_status (lmc_softc_t * स्थिर sc)
अणु
    /*
     * We're using the same code as SSI since
     * they're practically the same
     */
    वापस lmc_ssi_get_link_status(sc);
पूर्ण

अटल व्योम
lmc_hssi_set_link_status (lmc_softc_t * स्थिर sc, पूर्णांक state)
अणु
  अगर (state == LMC_LINK_UP)
    sc->lmc_miireg16 |= LMC_MII16_HSSI_TA;
  अन्यथा
    sc->lmc_miireg16 &= ~LMC_MII16_HSSI_TA;

  lmc_mii_ग_लिखोreg (sc, 0, 16, sc->lmc_miireg16);
पूर्ण

/*
 * 0 == 16bit, 1 == 32bit
 */
अटल व्योम
lmc_hssi_set_crc_length (lmc_softc_t * स्थिर sc, पूर्णांक state)
अणु
  अगर (state == LMC_CTL_CRC_LENGTH_32)
    अणु
      /* 32 bit */
      sc->lmc_miireg16 |= LMC_MII16_HSSI_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_32;
    पूर्ण
  अन्यथा
    अणु
      /* 16 bit */
      sc->lmc_miireg16 &= ~LMC_MII16_HSSI_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_16;
    पूर्ण

  lmc_mii_ग_लिखोreg (sc, 0, 16, sc->lmc_miireg16);
पूर्ण

अटल व्योम
lmc_hssi_watchकरोg (lmc_softc_t * स्थिर sc)
अणु
  /* HSSI is blank */
पूर्ण

/*
 *  DS3 methods
 */

/*
 * Set cable length
 */
अटल व्योम
lmc_ds3_set_100ft (lmc_softc_t * स्थिर sc, पूर्णांक ie)
अणु
  अगर (ie == LMC_CTL_CABLE_LENGTH_GT_100FT)
    अणु
      sc->lmc_miireg16 &= ~LMC_MII16_DS3_ZERO;
      sc->ictl.cable_length = LMC_CTL_CABLE_LENGTH_GT_100FT;
    पूर्ण
  अन्यथा अगर (ie == LMC_CTL_CABLE_LENGTH_LT_100FT)
    अणु
      sc->lmc_miireg16 |= LMC_MII16_DS3_ZERO;
      sc->ictl.cable_length = LMC_CTL_CABLE_LENGTH_LT_100FT;
    पूर्ण
  lmc_mii_ग_लिखोreg (sc, 0, 16, sc->lmc_miireg16);
पूर्ण

अटल व्योम
lmc_ds3_शेष (lmc_softc_t * स्थिर sc)
अणु
  sc->lmc_miireg16 = LMC_MII16_LED_ALL;

  sc->lmc_media->set_link_status (sc, LMC_LINK_DOWN);
  sc->lmc_media->set_cable_length (sc, LMC_CTL_CABLE_LENGTH_LT_100FT);
  sc->lmc_media->set_scrambler (sc, LMC_CTL_OFF);
  sc->lmc_media->set_crc_length (sc, LMC_CTL_CRC_LENGTH_16);
पूर्ण

/*
 * Given a user provided state, set ourselves up to match it.  This will
 * always reset the card अगर needed.
 */
अटल व्योम
lmc_ds3_set_status (lmc_softc_t * स्थिर sc, lmc_ctl_t * ctl)
अणु
  अगर (ctl == शून्य)
    अणु
      sc->lmc_media->set_cable_length (sc, sc->ictl.cable_length);
      sc->lmc_media->set_scrambler (sc, sc->ictl.scrambler_onoff);
      lmc_set_protocol (sc, शून्य);

      वापस;
    पूर्ण

  /*
   * check क्रम change in cable length setting
   */
  अगर (ctl->cable_length && !sc->ictl.cable_length)
    lmc_ds3_set_100ft (sc, LMC_CTL_CABLE_LENGTH_GT_100FT);
  अन्यथा अगर (!ctl->cable_length && sc->ictl.cable_length)
    lmc_ds3_set_100ft (sc, LMC_CTL_CABLE_LENGTH_LT_100FT);

  /*
   * Check क्रम change in scrambler setting (requires reset)
   */
  अगर (ctl->scrambler_onoff && !sc->ictl.scrambler_onoff)
    lmc_ds3_set_scram (sc, LMC_CTL_ON);
  अन्यथा अगर (!ctl->scrambler_onoff && sc->ictl.scrambler_onoff)
    lmc_ds3_set_scram (sc, LMC_CTL_OFF);

  lmc_set_protocol (sc, ctl);
पूर्ण

अटल व्योम
lmc_ds3_init (lmc_softc_t * स्थिर sc)
अणु
  पूर्णांक i;

  sc->ictl.cardtype = LMC_CTL_CARDTYPE_LMC5245;

  /* ग_लिखोs zeros everywhere */
  क्रम (i = 0; i < 21; i++)
    अणु
      lmc_mii_ग_लिखोreg (sc, 0, 17, i);
      lmc_mii_ग_लिखोreg (sc, 0, 18, 0);
    पूर्ण

  /* set some essential bits */
  lmc_mii_ग_लिखोreg (sc, 0, 17, 1);
  lmc_mii_ग_लिखोreg (sc, 0, 18, 0x25);	/* ser, xtx */

  lmc_mii_ग_लिखोreg (sc, 0, 17, 5);
  lmc_mii_ग_लिखोreg (sc, 0, 18, 0x80);	/* emode */

  lmc_mii_ग_लिखोreg (sc, 0, 17, 14);
  lmc_mii_ग_लिखोreg (sc, 0, 18, 0x30);	/* rcgen, tcgen */

  /* clear counters and latched bits */
  क्रम (i = 0; i < 21; i++)
    अणु
      lmc_mii_ग_लिखोreg (sc, 0, 17, i);
      lmc_mii_पढ़ोreg (sc, 0, 18);
    पूर्ण
पूर्ण

/*
 * 1 == DS3 payload scrambled, 0 == not scrambled
 */
अटल व्योम
lmc_ds3_set_scram (lmc_softc_t * स्थिर sc, पूर्णांक ie)
अणु
  अगर (ie == LMC_CTL_ON)
    अणु
      sc->lmc_miireg16 |= LMC_MII16_DS3_SCRAM;
      sc->ictl.scrambler_onoff = LMC_CTL_ON;
    पूर्ण
  अन्यथा
    अणु
      sc->lmc_miireg16 &= ~LMC_MII16_DS3_SCRAM;
      sc->ictl.scrambler_onoff = LMC_CTL_OFF;
    पूर्ण
  lmc_mii_ग_लिखोreg (sc, 0, 16, sc->lmc_miireg16);
पूर्ण

/*
 * वापस hardware link status.
 * 0 == link is करोwn, 1 == link is up.
 */
अटल पूर्णांक
lmc_ds3_get_link_status (lmc_softc_t * स्थिर sc)
अणु
    u16 link_status, link_status_11;
    पूर्णांक ret = 1;

    lmc_mii_ग_लिखोreg (sc, 0, 17, 7);
    link_status = lmc_mii_पढ़ोreg (sc, 0, 18);

    /* LMC5245 (DS3) & LMC1200 (DS1) LED definitions
     * led0 yellow = far-end adapter is in Red alarm condition
     * led1 blue   = received an Alarm Indication संकेत
     *               (upstream failure)
     * led2 Green  = घातer to adapter, Gate Array loaded & driver
     *               attached
     * led3 red    = Loss of Signal (LOS) or out of frame (OOF)
     *               conditions detected on T3 receive संकेत
     */

    lmc_led_on(sc, LMC_DS3_LED2);

    अगर ((link_status & LMC_FRAMER_REG0_DLOS) ||
        (link_status & LMC_FRAMER_REG0_OOFS))अणु
        ret = 0;
        अगर(sc->last_led_err[3] != 1)अणु
	    u16 r1;
            lmc_mii_ग_लिखोreg (sc, 0, 17, 01); /* Turn on Xbit error as our cisco करोes */
            r1 = lmc_mii_पढ़ोreg (sc, 0, 18);
            r1 &= 0xfe;
            lmc_mii_ग_लिखोreg(sc, 0, 18, r1);
            prपूर्णांकk(KERN_WARNING "%s: Red Alarm - Loss of Signal or Loss of Framing\n", sc->name);
        पूर्ण
        lmc_led_on(sc, LMC_DS3_LED3);	/* turn on red LED */
        sc->last_led_err[3] = 1;
    पूर्ण
    अन्यथा अणु
        lmc_led_off(sc, LMC_DS3_LED3);	/* turn on red LED */
        अगर(sc->last_led_err[3] == 1)अणु
	    u16 r1;
            lmc_mii_ग_लिखोreg (sc, 0, 17, 01); /* Turn off Xbit error */
            r1 = lmc_mii_पढ़ोreg (sc, 0, 18);
            r1 |= 0x01;
            lmc_mii_ग_लिखोreg(sc, 0, 18, r1);
        पूर्ण
        sc->last_led_err[3] = 0;
    पूर्ण

    lmc_mii_ग_लिखोreg(sc, 0, 17, 0x10);
    link_status_11 = lmc_mii_पढ़ोreg(sc, 0, 18);
    अगर((link_status & LMC_FRAMER_REG0_AIS) ||
       (link_status_11 & LMC_FRAMER_REG10_XBIT)) अणु
        ret = 0;
        अगर(sc->last_led_err[0] != 1)अणु
            prपूर्णांकk(KERN_WARNING "%s: AIS Alarm or XBit Error\n", sc->name);
            prपूर्णांकk(KERN_WARNING "%s: Remote end has loss of signal or framing\n", sc->name);
        पूर्ण
        lmc_led_on(sc, LMC_DS3_LED0);
        sc->last_led_err[0] = 1;
    पूर्ण
    अन्यथा अणु
        lmc_led_off(sc, LMC_DS3_LED0);
        sc->last_led_err[0] = 0;
    पूर्ण

    lmc_mii_ग_लिखोreg (sc, 0, 17, 9);
    link_status = lmc_mii_पढ़ोreg (sc, 0, 18);
    
    अगर(link_status & LMC_FRAMER_REG9_RBLUE)अणु
        ret = 0;
        अगर(sc->last_led_err[1] != 1)अणु
            prपूर्णांकk(KERN_WARNING "%s: Blue Alarm - Receiving all 1's\n", sc->name);
        पूर्ण
        lmc_led_on(sc, LMC_DS3_LED1);
        sc->last_led_err[1] = 1;
    पूर्ण
    अन्यथा अणु
        lmc_led_off(sc, LMC_DS3_LED1);
        sc->last_led_err[1] = 0;
    पूर्ण

    वापस ret;
पूर्ण

/*
 * 0 == 16bit, 1 == 32bit
 */
अटल व्योम
lmc_ds3_set_crc_length (lmc_softc_t * स्थिर sc, पूर्णांक state)
अणु
  अगर (state == LMC_CTL_CRC_LENGTH_32)
    अणु
      /* 32 bit */
      sc->lmc_miireg16 |= LMC_MII16_DS3_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_32;
    पूर्ण
  अन्यथा
    अणु
      /* 16 bit */
      sc->lmc_miireg16 &= ~LMC_MII16_DS3_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_16;
    पूर्ण

  lmc_mii_ग_लिखोreg (sc, 0, 16, sc->lmc_miireg16);
पूर्ण

अटल व्योम
lmc_ds3_watchकरोg (lmc_softc_t * स्थिर sc)
अणु
    
पूर्ण


/*
 *  SSI methods
 */

अटल व्योम lmc_ssi_init(lmc_softc_t * स्थिर sc)
अणु
	u16 mii17;
	पूर्णांक cable;

	sc->ictl.cardtype = LMC_CTL_CARDTYPE_LMC1000;

	mii17 = lmc_mii_पढ़ोreg(sc, 0, 17);

	cable = (mii17 & LMC_MII17_SSI_CABLE_MASK) >> LMC_MII17_SSI_CABLE_SHIFT;
	sc->ictl.cable_type = cable;

	lmc_gpio_mkoutput(sc, LMC_GEP_SSI_TXCLOCK);
पूर्ण

अटल व्योम
lmc_ssi_शेष (lmc_softc_t * स्थिर sc)
अणु
  sc->lmc_miireg16 = LMC_MII16_LED_ALL;

  /*
   * make TXCLOCK always be an output
   */
  lmc_gpio_mkoutput (sc, LMC_GEP_SSI_TXCLOCK);

  sc->lmc_media->set_link_status (sc, LMC_LINK_DOWN);
  sc->lmc_media->set_घड़ी_source (sc, LMC_CTL_CLOCK_SOURCE_EXT);
  sc->lmc_media->set_speed (sc, शून्य);
  sc->lmc_media->set_crc_length (sc, LMC_CTL_CRC_LENGTH_16);
पूर्ण

/*
 * Given a user provided state, set ourselves up to match it.  This will
 * always reset the card अगर needed.
 */
अटल व्योम
lmc_ssi_set_status (lmc_softc_t * स्थिर sc, lmc_ctl_t * ctl)
अणु
  अगर (ctl == शून्य)
    अणु
      sc->lmc_media->set_घड़ी_source (sc, sc->ictl.घड़ी_source);
      sc->lmc_media->set_speed (sc, &sc->ictl);
      lmc_set_protocol (sc, शून्य);

      वापस;
    पूर्ण

  /*
   * check क्रम change in घड़ी source
   */
  अगर (ctl->घड़ी_source == LMC_CTL_CLOCK_SOURCE_INT
      && sc->ictl.घड़ी_source == LMC_CTL_CLOCK_SOURCE_EXT)
    अणु
      sc->lmc_media->set_घड़ी_source (sc, LMC_CTL_CLOCK_SOURCE_INT);
      sc->lmc_timing = LMC_CTL_CLOCK_SOURCE_INT;
    पूर्ण
  अन्यथा अगर (ctl->घड़ी_source == LMC_CTL_CLOCK_SOURCE_EXT
	   && sc->ictl.घड़ी_source == LMC_CTL_CLOCK_SOURCE_INT)
    अणु
      sc->lmc_media->set_घड़ी_source (sc, LMC_CTL_CLOCK_SOURCE_EXT);
      sc->lmc_timing = LMC_CTL_CLOCK_SOURCE_EXT;
    पूर्ण

  अगर (ctl->घड़ी_rate != sc->ictl.घड़ी_rate)
    sc->lmc_media->set_speed (sc, ctl);

  lmc_set_protocol (sc, ctl);
पूर्ण

/*
 * 1 == पूर्णांकernal, 0 == बाह्यal
 */
अटल व्योम
lmc_ssi_set_घड़ी (lmc_softc_t * स्थिर sc, पूर्णांक ie)
अणु
  पूर्णांक old;
  old = ie;
  अगर (ie == LMC_CTL_CLOCK_SOURCE_EXT)
    अणु
      sc->lmc_gpio &= ~(LMC_GEP_SSI_TXCLOCK);
      LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);
      sc->ictl.घड़ी_source = LMC_CTL_CLOCK_SOURCE_EXT;
      अगर(ie != old)
        prपूर्णांकk (LMC_PRINTF_FMT ": clock external\n", LMC_PRINTF_ARGS);
    पूर्ण
  अन्यथा
    अणु
      sc->lmc_gpio |= LMC_GEP_SSI_TXCLOCK;
      LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);
      sc->ictl.घड़ी_source = LMC_CTL_CLOCK_SOURCE_INT;
      अगर(ie != old)
        prपूर्णांकk (LMC_PRINTF_FMT ": clock internal\n", LMC_PRINTF_ARGS);
    पूर्ण
पूर्ण

अटल व्योम
lmc_ssi_set_speed (lmc_softc_t * स्थिर sc, lmc_ctl_t * ctl)
अणु
  lmc_ctl_t *ictl = &sc->ictl;
  lmc_av9110_t *av;

  /* original settings क्रम घड़ी rate of:
   *  100 Khz (8,25,0,0,2) were incorrect
   *  they should have been 80,125,1,3,3
   *  There are 17 param combinations to produce this freq.
   *  For 1.5 Mhz use 120,100,1,1,2 (226 param. combinations)
   */
  अगर (ctl == शून्य)
    अणु
      av = &ictl->cardspec.ssi;
      ictl->घड़ी_rate = 1500000;
      av->f = ictl->घड़ी_rate;
      av->n = 120;
      av->m = 100;
      av->v = 1;
      av->x = 1;
      av->r = 2;

      ग_लिखो_av9110 (sc, av->n, av->m, av->v, av->x, av->r);
      वापस;
    पूर्ण

  av = &ctl->cardspec.ssi;

  अगर (av->f == 0)
    वापस;

  ictl->घड़ी_rate = av->f;	/* really, this is the rate we are */
  ictl->cardspec.ssi = *av;

  ग_लिखो_av9110 (sc, av->n, av->m, av->v, av->x, av->r);
पूर्ण

/*
 * वापस hardware link status.
 * 0 == link is करोwn, 1 == link is up.
 */
अटल पूर्णांक
lmc_ssi_get_link_status (lmc_softc_t * स्थिर sc)
अणु
  u16 link_status;
  u32 ticks;
  पूर्णांक ret = 1;
  पूर्णांक hw_hdsk = 1;

  /*
   * missing CTS?  Hmm.  If we require CTS on, we may never get the
   * link to come up, so omit it in this test.
   *
   * Also, it seems that with a loopback cable, DCD isn't निश्चितed,
   * so just check क्रम things like this:
   *      DSR _must_ be निश्चितed.
   *      One of DCD or CTS must be निश्चितed.
   */

  /* LMC 1000 (SSI) LED definitions
   * led0 Green = घातer to adapter, Gate Array loaded &
   *              driver attached
   * led1 Green = DSR and DTR and RTS and CTS are set
   * led2 Green = Cable detected
   * led3 red   = No timing is available from the
   *              cable or the on-board frequency
   *              generator.
   */

  link_status = lmc_mii_पढ़ोreg (sc, 0, 16);

  /* Is the transmit घड़ी still available */
  ticks = LMC_CSR_READ (sc, csr_gp_समयr);
  ticks = 0x0000ffff - (ticks & 0x0000ffff);

  lmc_led_on (sc, LMC_MII16_LED0);

  /* ====== transmit घड़ी determination ===== */
  अगर (sc->lmc_timing == LMC_CTL_CLOCK_SOURCE_INT) अणु
      lmc_led_off(sc, LMC_MII16_LED3);
  पूर्ण
  अन्यथा अगर (ticks == 0 ) अणु				/* no घड़ी found ? */
      ret = 0;
      अगर (sc->last_led_err[3] != 1) अणु
	      sc->extra_stats.tx_lossOfClockCnt++;
	      prपूर्णांकk(KERN_WARNING "%s: Lost Clock, Link Down\n", sc->name);
      पूर्ण
      sc->last_led_err[3] = 1;
      lmc_led_on (sc, LMC_MII16_LED3);	/* turn ON red LED */
  पूर्ण
  अन्यथा अणु
      अगर(sc->last_led_err[3] == 1)
          prपूर्णांकk(KERN_WARNING "%s: Clock Returned\n", sc->name);
      sc->last_led_err[3] = 0;
      lmc_led_off (sc, LMC_MII16_LED3);		/* turn OFF red LED */
  पूर्ण

  अगर ((link_status & LMC_MII16_SSI_DSR) == 0) अणु /* Also HSSI CA */
      ret = 0;
      hw_hdsk = 0;
  पूर्ण

#अगर_घोषित CONFIG_LMC_IGNORE_HARDWARE_HANDSHAKE
  अगर ((link_status & (LMC_MII16_SSI_CTS | LMC_MII16_SSI_DCD)) == 0)अणु
      ret = 0;
      hw_hdsk = 0;
  पूर्ण
#पूर्ण_अगर

  अगर(hw_hdsk == 0)अणु
      अगर(sc->last_led_err[1] != 1)
          prपूर्णांकk(KERN_WARNING "%s: DSR not asserted\n", sc->name);
      sc->last_led_err[1] = 1;
      lmc_led_off(sc, LMC_MII16_LED1);
  पूर्ण
  अन्यथा अणु
      अगर(sc->last_led_err[1] != 0)
          prपूर्णांकk(KERN_WARNING "%s: DSR now asserted\n", sc->name);
      sc->last_led_err[1] = 0;
      lmc_led_on(sc, LMC_MII16_LED1);
  पूर्ण

  अगर(ret == 1) अणु
      lmc_led_on(sc, LMC_MII16_LED2); /* Over all good status? */
  पूर्ण
  
  वापस ret;
पूर्ण

अटल व्योम
lmc_ssi_set_link_status (lmc_softc_t * स्थिर sc, पूर्णांक state)
अणु
  अगर (state == LMC_LINK_UP)
    अणु
      sc->lmc_miireg16 |= (LMC_MII16_SSI_DTR | LMC_MII16_SSI_RTS);
      prपूर्णांकk (LMC_PRINTF_FMT ": asserting DTR and RTS\n", LMC_PRINTF_ARGS);
    पूर्ण
  अन्यथा
    अणु
      sc->lmc_miireg16 &= ~(LMC_MII16_SSI_DTR | LMC_MII16_SSI_RTS);
      prपूर्णांकk (LMC_PRINTF_FMT ": deasserting DTR and RTS\n", LMC_PRINTF_ARGS);
    पूर्ण

  lmc_mii_ग_लिखोreg (sc, 0, 16, sc->lmc_miireg16);

पूर्ण

/*
 * 0 == 16bit, 1 == 32bit
 */
अटल व्योम
lmc_ssi_set_crc_length (lmc_softc_t * स्थिर sc, पूर्णांक state)
अणु
  अगर (state == LMC_CTL_CRC_LENGTH_32)
    अणु
      /* 32 bit */
      sc->lmc_miireg16 |= LMC_MII16_SSI_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_32;
      sc->lmc_crcSize = LMC_CTL_CRC_BYTESIZE_4;

    पूर्ण
  अन्यथा
    अणु
      /* 16 bit */
      sc->lmc_miireg16 &= ~LMC_MII16_SSI_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_16;
      sc->lmc_crcSize = LMC_CTL_CRC_BYTESIZE_2;
    पूर्ण

  lmc_mii_ग_लिखोreg (sc, 0, 16, sc->lmc_miireg16);
पूर्ण

/*
 * These are bits to program the ssi frequency generator
 */
अटल अंतरभूत व्योम
ग_लिखो_av9110_bit (lmc_softc_t * sc, पूर्णांक c)
अणु
  /*
   * set the data bit as we need it.
   */
  sc->lmc_gpio &= ~(LMC_GEP_CLK);
  अगर (c & 0x01)
    sc->lmc_gpio |= LMC_GEP_DATA;
  अन्यथा
    sc->lmc_gpio &= ~(LMC_GEP_DATA);
  LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);

  /*
   * set the घड़ी to high
   */
  sc->lmc_gpio |= LMC_GEP_CLK;
  LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);

  /*
   * set the घड़ी to low again.
   */
  sc->lmc_gpio &= ~(LMC_GEP_CLK);
  LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);
पूर्ण

अटल व्योम ग_लिखो_av9110(lmc_softc_t *sc, u32 n, u32 m, u32 v, u32 x, u32 r)
अणु
  पूर्णांक i;

#अगर 0
  prपूर्णांकk (LMC_PRINTF_FMT ": speed %u, %d %d %d %d %d\n",
	  LMC_PRINTF_ARGS, sc->ictl.घड़ी_rate, n, m, v, x, r);
#पूर्ण_अगर

  sc->lmc_gpio |= LMC_GEP_SSI_GENERATOR;
  sc->lmc_gpio &= ~(LMC_GEP_DATA | LMC_GEP_CLK);
  LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);

  /*
   * Set the TXCLOCK, GENERATOR, SERIAL, and SERIALCLK
   * as outमाला_दो.
   */
  lmc_gpio_mkoutput (sc, (LMC_GEP_DATA | LMC_GEP_CLK
			  | LMC_GEP_SSI_GENERATOR));

  sc->lmc_gpio &= ~(LMC_GEP_SSI_GENERATOR);
  LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);

  /*
   * a shअगरting we will go...
   */
  क्रम (i = 0; i < 7; i++)
    ग_लिखो_av9110_bit (sc, n >> i);
  क्रम (i = 0; i < 7; i++)
    ग_लिखो_av9110_bit (sc, m >> i);
  क्रम (i = 0; i < 1; i++)
    ग_लिखो_av9110_bit (sc, v >> i);
  क्रम (i = 0; i < 2; i++)
    ग_लिखो_av9110_bit (sc, x >> i);
  क्रम (i = 0; i < 2; i++)
    ग_लिखो_av9110_bit (sc, r >> i);
  क्रम (i = 0; i < 5; i++)
    ग_लिखो_av9110_bit (sc, 0x17 >> i);

  /*
   * stop driving serial-related संकेतs
   */
  lmc_gpio_mkinput (sc,
		    (LMC_GEP_DATA | LMC_GEP_CLK
		     | LMC_GEP_SSI_GENERATOR));
पूर्ण

अटल व्योम lmc_ssi_watchकरोg(lmc_softc_t * स्थिर sc)
अणु
	u16 mii17 = lmc_mii_पढ़ोreg(sc, 0, 17);
	अगर (((mii17 >> 3) & 7) == 7)
		lmc_led_off(sc, LMC_MII16_LED2);
	अन्यथा
		lmc_led_on(sc, LMC_MII16_LED2);
पूर्ण

/*
 *  T1 methods
 */

/*
 * The framer regs are multiplexed through MII regs 17 & 18
 *  ग_लिखो the रेजिस्टर address to MII reg 17 and the *  data to MII reg 18. */
अटल व्योम
lmc_t1_ग_लिखो (lmc_softc_t * स्थिर sc, पूर्णांक a, पूर्णांक d)
अणु
  lmc_mii_ग_लिखोreg (sc, 0, 17, a);
  lmc_mii_ग_लिखोreg (sc, 0, 18, d);
पूर्ण

/* Save a warning
अटल पूर्णांक
lmc_t1_पढ़ो (lmc_softc_t * स्थिर sc, पूर्णांक a)
अणु
  lmc_mii_ग_लिखोreg (sc, 0, 17, a);
  वापस lmc_mii_पढ़ोreg (sc, 0, 18);
पूर्ण
*/


अटल व्योम
lmc_t1_init (lmc_softc_t * स्थिर sc)
अणु
  u16 mii16;
  पूर्णांक i;

  sc->ictl.cardtype = LMC_CTL_CARDTYPE_LMC1200;
  mii16 = lmc_mii_पढ़ोreg (sc, 0, 16);

  /* reset 8370 */
  mii16 &= ~LMC_MII16_T1_RST;
  lmc_mii_ग_लिखोreg (sc, 0, 16, mii16 | LMC_MII16_T1_RST);
  lmc_mii_ग_लिखोreg (sc, 0, 16, mii16);

  /* set T1 or E1 line.  Uses sc->lmcmii16 reg in function so update it */
  sc->lmc_miireg16 = mii16;
  lmc_t1_set_circuit_type(sc, LMC_CTL_CIRCUIT_TYPE_T1);
  mii16 = sc->lmc_miireg16;

  lmc_t1_ग_लिखो (sc, 0x01, 0x1B);	/* CR0     - primary control             */
  lmc_t1_ग_लिखो (sc, 0x02, 0x42);	/* JAT_CR  - jitter atten config         */
  lmc_t1_ग_लिखो (sc, 0x14, 0x00);	/* LOOP    - loopback config             */
  lmc_t1_ग_लिखो (sc, 0x15, 0x00);	/* DL3_TS  - बाह्यal data link बारlot */
  lmc_t1_ग_लिखो (sc, 0x18, 0xFF);	/* PIO     - programmable I/O            */
  lmc_t1_ग_लिखो (sc, 0x19, 0x30);	/* POE     - programmable OE             */
  lmc_t1_ग_लिखो (sc, 0x1A, 0x0F);	/* CMUX    - घड़ी input mux             */
  lmc_t1_ग_लिखो (sc, 0x20, 0x41);	/* LIU_CR  - RX LIU config               */
  lmc_t1_ग_लिखो (sc, 0x22, 0x76);	/* RLIU_CR - RX LIU config               */
  lmc_t1_ग_लिखो (sc, 0x40, 0x03);	/* RCR0    - RX config                   */
  lmc_t1_ग_लिखो (sc, 0x45, 0x00);	/* RALM    - RX alarm config             */
  lmc_t1_ग_लिखो (sc, 0x46, 0x05);	/* LATCH   - RX alarm/err/cntr latch     */
  lmc_t1_ग_लिखो (sc, 0x68, 0x40);	/* TLIU_CR - TX LIU config               */
  lmc_t1_ग_लिखो (sc, 0x70, 0x0D);	/* TCR0    - TX framer config            */
  lmc_t1_ग_लिखो (sc, 0x71, 0x05);	/* TCR1    - TX config                   */
  lmc_t1_ग_लिखो (sc, 0x72, 0x0B);	/* TFRM    - TX frame क्रमmat             */
  lmc_t1_ग_लिखो (sc, 0x73, 0x00);	/* TERROR  - TX error insert             */
  lmc_t1_ग_लिखो (sc, 0x74, 0x00);	/* TMAN    - TX manual Sa/FEBE config    */
  lmc_t1_ग_लिखो (sc, 0x75, 0x00);	/* TALM    - TX alarm संकेत config      */
  lmc_t1_ग_लिखो (sc, 0x76, 0x00);	/* TPATT   - TX test pattern config      */
  lmc_t1_ग_लिखो (sc, 0x77, 0x00);	/* TLB     - TX inband loopback config   */
  lmc_t1_ग_लिखो (sc, 0x90, 0x05);	/* CLAD_CR - घड़ी rate adapter config   */
  lmc_t1_ग_लिखो (sc, 0x91, 0x05);	/* CSEL    - clad freq sel               */
  lmc_t1_ग_लिखो (sc, 0xA6, 0x00);	/* DL1_CTL - DL1 control                 */
  lmc_t1_ग_लिखो (sc, 0xB1, 0x00);	/* DL2_CTL - DL2 control                 */
  lmc_t1_ग_लिखो (sc, 0xD0, 0x47);	/* SBI_CR  - sys bus अगरace config        */
  lmc_t1_ग_लिखो (sc, 0xD1, 0x70);	/* RSB_CR  - RX sys bus config           */
  lmc_t1_ग_लिखो (sc, 0xD4, 0x30);	/* TSB_CR  - TX sys bus config           */
  क्रम (i = 0; i < 32; i++)
    अणु
      lmc_t1_ग_लिखो (sc, 0x0E0 + i, 0x00);	/* SBCn - sys bus per-channel ctl    */
      lmc_t1_ग_लिखो (sc, 0x100 + i, 0x00);	/* TPCn - TX per-channel ctl         */
      lmc_t1_ग_लिखो (sc, 0x180 + i, 0x00);	/* RPCn - RX per-channel ctl         */
    पूर्ण
  क्रम (i = 1; i < 25; i++)
    अणु
      lmc_t1_ग_लिखो (sc, 0x0E0 + i, 0x0D);	/* SBCn - sys bus per-channel ctl    */
    पूर्ण

  mii16 |= LMC_MII16_T1_XOE;
  lmc_mii_ग_लिखोreg (sc, 0, 16, mii16);
  sc->lmc_miireg16 = mii16;
पूर्ण

अटल व्योम
lmc_t1_शेष (lmc_softc_t * स्थिर sc)
अणु
  sc->lmc_miireg16 = LMC_MII16_LED_ALL;
  sc->lmc_media->set_link_status (sc, LMC_LINK_DOWN);
  sc->lmc_media->set_circuit_type (sc, LMC_CTL_CIRCUIT_TYPE_T1);
  sc->lmc_media->set_crc_length (sc, LMC_CTL_CRC_LENGTH_16);
  /* Right now we can only घड़ी from out पूर्णांकernal source */
  sc->ictl.घड़ी_source = LMC_CTL_CLOCK_SOURCE_INT;
पूर्ण
/* * Given a user provided state, set ourselves up to match it.  This will * always reset the card अगर needed.
 */
अटल व्योम
lmc_t1_set_status (lmc_softc_t * स्थिर sc, lmc_ctl_t * ctl)
अणु
  अगर (ctl == शून्य)
    अणु
      sc->lmc_media->set_circuit_type (sc, sc->ictl.circuit_type);
      lmc_set_protocol (sc, शून्य);

      वापस;
    पूर्ण
  /*
   * check क्रम change in circuit type         */
  अगर (ctl->circuit_type == LMC_CTL_CIRCUIT_TYPE_T1
      && sc->ictl.circuit_type ==
      LMC_CTL_CIRCUIT_TYPE_E1) sc->lmc_media->set_circuit_type (sc,
								LMC_CTL_CIRCUIT_TYPE_E1);
  अन्यथा अगर (ctl->circuit_type == LMC_CTL_CIRCUIT_TYPE_E1
	   && sc->ictl.circuit_type == LMC_CTL_CIRCUIT_TYPE_T1)
    sc->lmc_media->set_circuit_type (sc, LMC_CTL_CIRCUIT_TYPE_T1);
  lmc_set_protocol (sc, ctl);
पूर्ण
/*
 * वापस hardware link status.
 * 0 == link is करोwn, 1 == link is up.
 */ अटल पूर्णांक
lmc_t1_get_link_status (lmc_softc_t * स्थिर sc)
अणु
    u16 link_status;
    पूर्णांक ret = 1;

  /* LMC5245 (DS3) & LMC1200 (DS1) LED definitions
   * led0 yellow = far-end adapter is in Red alarm condition
   * led1 blue   = received an Alarm Indication संकेत
   *               (upstream failure)
   * led2 Green  = घातer to adapter, Gate Array loaded & driver
   *               attached
   * led3 red    = Loss of Signal (LOS) or out of frame (OOF)
   *               conditions detected on T3 receive संकेत
   */
    lmc_led_on(sc, LMC_DS3_LED2);

    lmc_mii_ग_लिखोreg (sc, 0, 17, T1FRAMER_ALARM1_STATUS);
    link_status = lmc_mii_पढ़ोreg (sc, 0, 18);


    अगर (link_status & T1F_RAIS) अणु			/* turn on blue LED */
        ret = 0;
        अगर(sc->last_led_err[1] != 1)अणु
            prपूर्णांकk(KERN_WARNING "%s: Receive AIS/Blue Alarm. Far end in RED alarm\n", sc->name);
        पूर्ण
        lmc_led_on(sc, LMC_DS3_LED1);
        sc->last_led_err[1] = 1;
    पूर्ण
    अन्यथा अणु
        अगर(sc->last_led_err[1] != 0)अणु
            prपूर्णांकk(KERN_WARNING "%s: End AIS/Blue Alarm\n", sc->name);
        पूर्ण
        lmc_led_off (sc, LMC_DS3_LED1);
        sc->last_led_err[1] = 0;
    पूर्ण

    /*
     * Yellow Alarm is nasty evil stuff, looks at data patterns
     * inside the channel and confuses it with HDLC framing
     * ignore all yellow alarms.
     *
     * Do listen to MultiFrame Yellow alarm which जबतक implemented
     * dअगरferent ways isn't in the channel and hence somewhat
     * more reliable
     */

    अगर (link_status & T1F_RMYEL) अणु
        ret = 0;
        अगर(sc->last_led_err[0] != 1)अणु
            prपूर्णांकk(KERN_WARNING "%s: Receive Yellow AIS Alarm\n", sc->name);
        पूर्ण
        lmc_led_on(sc, LMC_DS3_LED0);
        sc->last_led_err[0] = 1;
    पूर्ण
    अन्यथा अणु
        अगर(sc->last_led_err[0] != 0)अणु
            prपूर्णांकk(KERN_WARNING "%s: End of Yellow AIS Alarm\n", sc->name);
        पूर्ण
        lmc_led_off(sc, LMC_DS3_LED0);
        sc->last_led_err[0] = 0;
    पूर्ण

    /*
     * Loss of संकेत and los of frame
     * Use the green bit to identअगरy which one lit the led
     */
    अगर(link_status & T1F_RLOF)अणु
        ret = 0;
        अगर(sc->last_led_err[3] != 1)अणु
            prपूर्णांकk(KERN_WARNING "%s: Local Red Alarm: Loss of Framing\n", sc->name);
        पूर्ण
        lmc_led_on(sc, LMC_DS3_LED3);
        sc->last_led_err[3] = 1;

    पूर्ण
    अन्यथा अणु
        अगर(sc->last_led_err[3] != 0)अणु
            prपूर्णांकk(KERN_WARNING "%s: End Red Alarm (LOF)\n", sc->name);
        पूर्ण
        अगर( ! (link_status & T1F_RLOS))
            lmc_led_off(sc, LMC_DS3_LED3);
        sc->last_led_err[3] = 0;
    पूर्ण
    
    अगर(link_status & T1F_RLOS)अणु
        ret = 0;
        अगर(sc->last_led_err[2] != 1)अणु
            prपूर्णांकk(KERN_WARNING "%s: Local Red Alarm: Loss of Signal\n", sc->name);
        पूर्ण
        lmc_led_on(sc, LMC_DS3_LED3);
        sc->last_led_err[2] = 1;

    पूर्ण
    अन्यथा अणु
        अगर(sc->last_led_err[2] != 0)अणु
            prपूर्णांकk(KERN_WARNING "%s: End Red Alarm (LOS)\n", sc->name);
        पूर्ण
        अगर( ! (link_status & T1F_RLOF))
            lmc_led_off(sc, LMC_DS3_LED3);
        sc->last_led_err[2] = 0;
    पूर्ण

    sc->lmc_xinfo.t1_alarm1_status = link_status;

    lmc_mii_ग_लिखोreg (sc, 0, 17, T1FRAMER_ALARM2_STATUS);
    sc->lmc_xinfo.t1_alarm2_status = lmc_mii_पढ़ोreg (sc, 0, 18);

    वापस ret;
पूर्ण

/*
 * 1 == T1 Circuit Type , 0 == E1 Circuit Type
 */
अटल व्योम
lmc_t1_set_circuit_type (lmc_softc_t * स्थिर sc, पूर्णांक ie)
अणु
  अगर (ie == LMC_CTL_CIRCUIT_TYPE_T1) अणु
      sc->lmc_miireg16 |= LMC_MII16_T1_Z;
      sc->ictl.circuit_type = LMC_CTL_CIRCUIT_TYPE_T1;
      prपूर्णांकk(KERN_INFO "%s: In T1 Mode\n", sc->name);
  पूर्ण
  अन्यथा अणु
      sc->lmc_miireg16 &= ~LMC_MII16_T1_Z;
      sc->ictl.circuit_type = LMC_CTL_CIRCUIT_TYPE_E1;
      prपूर्णांकk(KERN_INFO "%s: In E1 Mode\n", sc->name);
  पूर्ण

  lmc_mii_ग_लिखोreg (sc, 0, 16, sc->lmc_miireg16);
  
पूर्ण

/*
 * 0 == 16bit, 1 == 32bit */
अटल व्योम
lmc_t1_set_crc_length (lmc_softc_t * स्थिर sc, पूर्णांक state)
अणु
  अगर (state == LMC_CTL_CRC_LENGTH_32)
    अणु
      /* 32 bit */
      sc->lmc_miireg16 |= LMC_MII16_T1_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_32;
      sc->lmc_crcSize = LMC_CTL_CRC_BYTESIZE_4;

    पूर्ण
  अन्यथा
    अणु
      /* 16 bit */ sc->lmc_miireg16 &= ~LMC_MII16_T1_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_16;
      sc->lmc_crcSize = LMC_CTL_CRC_BYTESIZE_2;

    पूर्ण

  lmc_mii_ग_लिखोreg (sc, 0, 16, sc->lmc_miireg16);
पूर्ण

/*
 * 1 == पूर्णांकernal, 0 == बाह्यal
 */
अटल व्योम
lmc_t1_set_घड़ी (lmc_softc_t * स्थिर sc, पूर्णांक ie)
अणु
  पूर्णांक old;
  old = ie;
  अगर (ie == LMC_CTL_CLOCK_SOURCE_EXT)
    अणु
      sc->lmc_gpio &= ~(LMC_GEP_SSI_TXCLOCK);
      LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);
      sc->ictl.घड़ी_source = LMC_CTL_CLOCK_SOURCE_EXT;
      अगर(old != ie)
        prपूर्णांकk (LMC_PRINTF_FMT ": clock external\n", LMC_PRINTF_ARGS);
    पूर्ण
  अन्यथा
    अणु
      sc->lmc_gpio |= LMC_GEP_SSI_TXCLOCK;
      LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);
      sc->ictl.घड़ी_source = LMC_CTL_CLOCK_SOURCE_INT;
      अगर(old != ie)
        prपूर्णांकk (LMC_PRINTF_FMT ": clock internal\n", LMC_PRINTF_ARGS);
    पूर्ण
पूर्ण

अटल व्योम
lmc_t1_watchकरोg (lmc_softc_t * स्थिर sc)
अणु
पूर्ण

अटल व्योम
lmc_set_protocol (lmc_softc_t * स्थिर sc, lmc_ctl_t * ctl)
अणु
	अगर (!ctl)
		sc->ictl.keepalive_onoff = LMC_CTL_ON;
पूर्ण
