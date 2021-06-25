<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *
 *  bttv - Bt848 frame grabber driver
 *
 *  card ID's and बाह्यal पूर्णांकerfaces of the bttv driver
 *  basically stuff needed by other drivers (i2c, lirc, ...)
 *  and is supported not to change much over समय.
 *
 *  Copyright (C) 1996,97 Ralph Metzler (rjkm@thp.uni-koeln.de)
 *  (c) 1999,2000 Gerd Knorr <kraxel@goldbach.in-berlin.de>
 *
 */

#अगर_अघोषित _BTTV_H_
#घोषणा _BTTV_H_

#समावेश <linux/videodev2.h>
#समावेश <linux/i2c.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/tuner.h>

/* ---------------------------------------------------------- */
/* exported by bttv-cards.c                                   */

#घोषणा BTTV_BOARD_UNKNOWN                 0x00
#घोषणा BTTV_BOARD_MIRO                    0x01
#घोषणा BTTV_BOARD_HAUPPAUGE               0x02
#घोषणा BTTV_BOARD_STB                     0x03
#घोषणा BTTV_BOARD_INTEL                   0x04
#घोषणा BTTV_BOARD_DIAMOND                 0x05
#घोषणा BTTV_BOARD_AVERMEDIA               0x06
#घोषणा BTTV_BOARD_MATRIX_VISION           0x07
#घोषणा BTTV_BOARD_FLYVIDEO                0x08
#घोषणा BTTV_BOARD_TURBOTV                 0x09
#घोषणा BTTV_BOARD_HAUPPAUGE878            0x0a
#घोषणा BTTV_BOARD_MIROPRO                 0x0b
#घोषणा BTTV_BOARD_ADSTECH_TV              0x0c
#घोषणा BTTV_BOARD_AVERMEDIA98             0x0d
#घोषणा BTTV_BOARD_VHX                     0x0e
#घोषणा BTTV_BOARD_ZOLTRIX                 0x0f
#घोषणा BTTV_BOARD_PIXVIEWPLAYTV           0x10
#घोषणा BTTV_BOARD_WINVIEW_601             0x11
#घोषणा BTTV_BOARD_AVEC_INTERCAP           0x12
#घोषणा BTTV_BOARD_LIFE_FLYKIT             0x13
#घोषणा BTTV_BOARD_CEI_RAFFLES             0x14
#घोषणा BTTV_BOARD_CONFERENCETV            0x15
#घोषणा BTTV_BOARD_PHOEBE_TVMAS            0x16
#घोषणा BTTV_BOARD_MODTEC_205              0x17
#घोषणा BTTV_BOARD_MAGICTVIEW061           0x18
#घोषणा BTTV_BOARD_VOBIS_BOOSTAR           0x19
#घोषणा BTTV_BOARD_HAUPPAUG_WCAM           0x1a
#घोषणा BTTV_BOARD_MAXI                    0x1b
#घोषणा BTTV_BOARD_TERRATV                 0x1c
#घोषणा BTTV_BOARD_PXC200                  0x1d
#घोषणा BTTV_BOARD_FLYVIDEO_98             0x1e
#घोषणा BTTV_BOARD_IPROTV                  0x1f
#घोषणा BTTV_BOARD_INTEL_C_S_PCI           0x20
#घोषणा BTTV_BOARD_TERRATVALUE             0x21
#घोषणा BTTV_BOARD_WINFAST2000             0x22
#घोषणा BTTV_BOARD_CHRONOS_VS2             0x23
#घोषणा BTTV_BOARD_TYPHOON_TVIEW           0x24
#घोषणा BTTV_BOARD_PXELVWPLTVPRO           0x25
#घोषणा BTTV_BOARD_MAGICTVIEW063           0x26
#घोषणा BTTV_BOARD_PINNACLE                0x27
#घोषणा BTTV_BOARD_STB2                    0x28
#घोषणा BTTV_BOARD_AVPHONE98               0x29
#घोषणा BTTV_BOARD_PV951                   0x2a
#घोषणा BTTV_BOARD_ONAIR_TV                0x2b
#घोषणा BTTV_BOARD_SIGMA_TVII_FM           0x2c
#घोषणा BTTV_BOARD_MATRIX_VISION2          0x2d
#घोषणा BTTV_BOARD_ZOLTRIX_GENIE           0x2e
#घोषणा BTTV_BOARD_TERRATVRADIO            0x2f
#घोषणा BTTV_BOARD_DYNALINK                0x30
#घोषणा BTTV_BOARD_GVBCTV3PCI              0x31
#घोषणा BTTV_BOARD_PXELVWPLTVPAK           0x32
#घोषणा BTTV_BOARD_EAGLE                   0x33
#घोषणा BTTV_BOARD_PINNACLEPRO             0x34
#घोषणा BTTV_BOARD_TVIEW_RDS_FM            0x35
#घोषणा BTTV_BOARD_LIFETEC_9415            0x36
#घोषणा BTTV_BOARD_BESTBUY_EASYTV          0x37
#घोषणा BTTV_BOARD_FLYVIDEO_98FM           0x38
#घोषणा BTTV_BOARD_GRANDTEC                0x39
#घोषणा BTTV_BOARD_ASKEY_CPH060            0x3a
#घोषणा BTTV_BOARD_ASKEY_CPH03X            0x3b
#घोषणा BTTV_BOARD_MM100PCTV               0x3c
#घोषणा BTTV_BOARD_GMV1                    0x3d
#घोषणा BTTV_BOARD_BESTBUY_EASYTV2         0x3e
#घोषणा BTTV_BOARD_ATI_TVWONDER            0x3f
#घोषणा BTTV_BOARD_ATI_TVWONDERVE          0x40
#घोषणा BTTV_BOARD_FLYVIDEO2000            0x41
#घोषणा BTTV_BOARD_TERRATVALUER            0x42
#घोषणा BTTV_BOARD_GVBCTV4PCI              0x43
#घोषणा BTTV_BOARD_VOODOOTV_FM             0x44
#घोषणा BTTV_BOARD_AIMMS                   0x45
#घोषणा BTTV_BOARD_PV_BT878P_PLUS          0x46
#घोषणा BTTV_BOARD_FLYVIDEO98EZ            0x47
#घोषणा BTTV_BOARD_PV_BT878P_9B            0x48
#घोषणा BTTV_BOARD_SENSORAY311_611         0x49
#घोषणा BTTV_BOARD_RV605                   0x4a
#घोषणा BTTV_BOARD_POWERCLR_MTV878         0x4b
#घोषणा BTTV_BOARD_WINDVR                  0x4c
#घोषणा BTTV_BOARD_GRANDTEC_MULTI          0x4d
#घोषणा BTTV_BOARD_KWORLD                  0x4e
#घोषणा BTTV_BOARD_DSP_TCVIDEO             0x4f
#घोषणा BTTV_BOARD_HAUPPAUGEPVR            0x50
#घोषणा BTTV_BOARD_GVBCTV5PCI              0x51
#घोषणा BTTV_BOARD_OSPREY1x0               0x52
#घोषणा BTTV_BOARD_OSPREY1x0_848           0x53
#घोषणा BTTV_BOARD_OSPREY101_848           0x54
#घोषणा BTTV_BOARD_OSPREY1x1               0x55
#घोषणा BTTV_BOARD_OSPREY1x1_SVID          0x56
#घोषणा BTTV_BOARD_OSPREY2xx               0x57
#घोषणा BTTV_BOARD_OSPREY2x0_SVID          0x58
#घोषणा BTTV_BOARD_OSPREY2x0               0x59
#घोषणा BTTV_BOARD_OSPREY500               0x5a
#घोषणा BTTV_BOARD_OSPREY540               0x5b
#घोषणा BTTV_BOARD_OSPREY2000              0x5c
#घोषणा BTTV_BOARD_IDS_EAGLE               0x5d
#घोषणा BTTV_BOARD_PINNACLESAT             0x5e
#घोषणा BTTV_BOARD_FORMAC_PROTV            0x5f
#घोषणा BTTV_BOARD_MACHTV                  0x60
#घोषणा BTTV_BOARD_EURESYS_PICOLO          0x61
#घोषणा BTTV_BOARD_PV150                   0x62
#घोषणा BTTV_BOARD_AD_TVK503               0x63
#घोषणा BTTV_BOARD_HERCULES_SM_TV          0x64
#घोषणा BTTV_BOARD_PACETV                  0x65
#घोषणा BTTV_BOARD_IVC200                  0x66
#घोषणा BTTV_BOARD_XGUARD                  0x67
#घोषणा BTTV_BOARD_NEBULA_DIGITV           0x68
#घोषणा BTTV_BOARD_PV143                   0x69
#घोषणा BTTV_BOARD_VD009X1_VD011_MINIDIN   0x6a
#घोषणा BTTV_BOARD_VD009X1_VD011_COMBI     0x6b
#घोषणा BTTV_BOARD_VD009_MINIDIN           0x6c
#घोषणा BTTV_BOARD_VD009_COMBI             0x6d
#घोषणा BTTV_BOARD_IVC100                  0x6e
#घोषणा BTTV_BOARD_IVC120                  0x6f
#घोषणा BTTV_BOARD_PC_HDTV                 0x70
#घोषणा BTTV_BOARD_TWINHAN_DST             0x71
#घोषणा BTTV_BOARD_WINFASTVC100            0x72
#घोषणा BTTV_BOARD_TEV560                  0x73
#घोषणा BTTV_BOARD_SIMUS_GVC1100           0x74
#घोषणा BTTV_BOARD_NGSTV_PLUS              0x75
#घोषणा BTTV_BOARD_LMLBT4                  0x76
#घोषणा BTTV_BOARD_TEKRAM_M205             0x77
#घोषणा BTTV_BOARD_CONTVFMI                0x78
#घोषणा BTTV_BOARD_PICOLO_TETRA_CHIP       0x79
#घोषणा BTTV_BOARD_SPIRIT_TV               0x7a
#घोषणा BTTV_BOARD_AVDVBT_771              0x7b
#घोषणा BTTV_BOARD_AVDVBT_761              0x7c
#घोषणा BTTV_BOARD_MATRIX_VISIONSQ         0x7d
#घोषणा BTTV_BOARD_MATRIX_VISIONSLC        0x7e
#घोषणा BTTV_BOARD_APAC_VIEWCOMP           0x7f
#घोषणा BTTV_BOARD_DVICO_DVBT_LITE         0x80
#घोषणा BTTV_BOARD_VGEAR_MYVCD             0x81
#घोषणा BTTV_BOARD_SUPER_TV                0x82
#घोषणा BTTV_BOARD_TIBET_CS16              0x83
#घोषणा BTTV_BOARD_KODICOM_4400R           0x84
#घोषणा BTTV_BOARD_KODICOM_4400R_SL        0x85
#घोषणा BTTV_BOARD_ADLINK_RTV24            0x86
#घोषणा BTTV_BOARD_DVICO_FUSIONHDTV_5_LITE 0x87
#घोषणा BTTV_BOARD_ACORP_Y878F             0x88
#घोषणा BTTV_BOARD_CONCEPTRONIC_CTVFMI2    0x89
#घोषणा BTTV_BOARD_PV_BT878P_2E            0x8a
#घोषणा BTTV_BOARD_PV_M4900                0x8b
#घोषणा BTTV_BOARD_OSPREY440               0x8c
#घोषणा BTTV_BOARD_ASOUND_SKYEYE	   0x8d
#घोषणा BTTV_BOARD_SABRENT_TVFM		   0x8e
#घोषणा BTTV_BOARD_HAUPPAUGE_IMPACTVCB     0x8f
#घोषणा BTTV_BOARD_MACHTV_MAGICTV          0x90
#घोषणा BTTV_BOARD_SSAI_SECURITY	   0x91
#घोषणा BTTV_BOARD_SSAI_ULTRASOUND	   0x92
#घोषणा BTTV_BOARD_VOODOOTV_200		   0x93
#घोषणा BTTV_BOARD_DVICO_FUSIONHDTV_2	   0x94
#घोषणा BTTV_BOARD_TYPHOON_TVTUNERPCI	   0x95
#घोषणा BTTV_BOARD_GEOVISION_GV600	   0x96
#घोषणा BTTV_BOARD_KOZUMI_KTV_01C          0x97
#घोषणा BTTV_BOARD_ENLTV_FM_2		   0x98
#घोषणा BTTV_BOARD_VD012		   0x99
#घोषणा BTTV_BOARD_VD012_X1		   0x9a
#घोषणा BTTV_BOARD_VD012_X2		   0x9b
#घोषणा BTTV_BOARD_IVCE8784		   0x9c
#घोषणा BTTV_BOARD_GEOVISION_GV800S	   0x9d
#घोषणा BTTV_BOARD_GEOVISION_GV800S_SL	   0x9e
#घोषणा BTTV_BOARD_PV183                   0x9f
#घोषणा BTTV_BOARD_TVT_TD3116		   0xa0
#घोषणा BTTV_BOARD_APOSONIC_WDVR           0xa1
#घोषणा BTTV_BOARD_ADLINK_MPG24            0xa2
#घोषणा BTTV_BOARD_BT848_CAP_14            0xa3
#घोषणा BTTV_BOARD_CYBERVISION_CV06        0xa4
#घोषणा BTTV_BOARD_KWORLD_VSTREAM_XPERT    0xa5
#घोषणा BTTV_BOARD_PCI_8604PW              0xa6

/* more card-specअगरic defines */
#घोषणा PT2254_L_CHANNEL 0x10
#घोषणा PT2254_R_CHANNEL 0x08
#घोषणा PT2254_DBS_IN_2 0x400
#घोषणा PT2254_DBS_IN_10 0x20000
#घोषणा WINVIEW_PT2254_CLK  0x40
#घोषणा WINVIEW_PT2254_DATA 0x20
#घोषणा WINVIEW_PT2254_STROBE 0x80

काष्ठा bttv_core अणु
	/* device काष्ठाs */
	काष्ठा v4l2_device   v4l2_dev;
	काष्ठा pci_dev       *pci;
	काष्ठा i2c_adapter   i2c_adap;
	काष्ठा list_head     subs;     /* काष्ठा bttv_sub_device */

	/* device config */
	अचिन्हित पूर्णांक         nr;       /* dev nr (क्रम prपूर्णांकk("bttv%d: ...");  */
	अचिन्हित पूर्णांक         type;     /* card type (poपूर्णांकer पूर्णांकo tvcards[])  */
पूर्ण;

काष्ठा bttv;

काष्ठा tvcard अणु
	अक्षर *name;
	व्योम (*volume_gpio)(काष्ठा bttv *btv, __u16 volume);
	व्योम (*audio_mode_gpio)(काष्ठा bttv *btv, काष्ठा v4l2_tuner *tuner, पूर्णांक set);
	व्योम (*muxsel_hook)(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);

	/* MUX bits क्रम each input, two bits per input starting with the LSB */
	u32 muxsel; /* Use MUXSEL() to set */

	u32 gpiomask;
	u32 gpiomux[4];  /* Tuner, Radio, बाह्यal, पूर्णांकernal */
	u32 gpiomute;    /* GPIO mute setting */
	u32 gpiomask2;   /* GPIO MUX mask */

	अचिन्हित पूर्णांक tuner_type;
	u8 tuner_addr;
	u8 video_inमाला_दो;	/* Number of inमाला_दो */
	अचिन्हित पूर्णांक svhs:4;	/* Which input is s-video */
#घोषणा NO_SVHS	15
	अचिन्हित पूर्णांक pll:2;
#घोषणा PLL_NONE 0
#घोषणा PLL_28   1
#घोषणा PLL_35   2
#घोषणा PLL_14   3

	/* i2c audio flags */
	अचिन्हित पूर्णांक no_msp34xx:1;
	अचिन्हित पूर्णांक no_tda7432:1;
	अचिन्हित पूर्णांक msp34xx_alt:1;
	/* Note: currently no card definition needs to mark the presence
	   of a RDS saa6588 chip. If this is ever needed, then add a new
	   'has_saa6588' bit here. */

	अचिन्हित पूर्णांक no_video:1; /* video pci function is unused */
	अचिन्हित पूर्णांक has_dvb:1;
	अचिन्हित पूर्णांक has_remote:1;
	अचिन्हित पूर्णांक has_radio:1;
	अचिन्हित पूर्णांक has_dig_in:1; /* Has digital input (always last input) */
	अचिन्हित पूर्णांक no_gpioirq:1;
पूर्ण;

बाह्य काष्ठा tvcard bttv_tvcards[];

/*
 * This bit of cpp vooकरोo is used to create a macro with a variable number of
 * arguments (1 to 16).  It will pack each argument पूर्णांकo a word two bits at a
 * समय.  It can't be a function because it needs to be compile समय स्थिरant to
 * initialize काष्ठाures.  Since each argument must fit in two bits, it's ok
 * that they are changed to octal.  One should not use hex number, macros, or
 * anything अन्यथा with this macro.  Just use plain पूर्णांकegers from 0 to 3.
 */
#घोषणा _MUXSELf(a)		0##a << 30
#घोषणा _MUXSELe(a, b...)	0##a << 28 | _MUXSELf(b)
#घोषणा _MUXSELd(a, b...)	0##a << 26 | _MUXSELe(b)
#घोषणा _MUXSELc(a, b...)	0##a << 24 | _MUXSELd(b)
#घोषणा _MUXSELb(a, b...)	0##a << 22 | _MUXSELc(b)
#घोषणा _MUXSELa(a, b...)	0##a << 20 | _MUXSELb(b)
#घोषणा _MUXSEL9(a, b...)	0##a << 18 | _MUXSELa(b)
#घोषणा _MUXSEL8(a, b...)	0##a << 16 | _MUXSEL9(b)
#घोषणा _MUXSEL7(a, b...)	0##a << 14 | _MUXSEL8(b)
#घोषणा _MUXSEL6(a, b...)	0##a << 12 | _MUXSEL7(b)
#घोषणा _MUXSEL5(a, b...)	0##a << 10 | _MUXSEL6(b)
#घोषणा _MUXSEL4(a, b...)	0##a << 8  | _MUXSEL5(b)
#घोषणा _MUXSEL3(a, b...)	0##a << 6  | _MUXSEL4(b)
#घोषणा _MUXSEL2(a, b...)	0##a << 4  | _MUXSEL3(b)
#घोषणा _MUXSEL1(a, b...)	0##a << 2  | _MUXSEL2(b)
#घोषणा MUXSEL(a, b...)		(a | _MUXSEL1(b))

/* identअगरication / initialization of the card */
बाह्य व्योम bttv_idcard(काष्ठा bttv *btv);
बाह्य व्योम bttv_init_card1(काष्ठा bttv *btv);
बाह्य व्योम bttv_init_card2(काष्ठा bttv *btv);
बाह्य व्योम bttv_init_tuner(काष्ठा bttv *btv);

/* card-specअगरic functions */
बाह्य व्योम tea5757_set_freq(काष्ठा bttv *btv, अचिन्हित लघु freq);
बाह्य u32 bttv_tda9880_setnorm(काष्ठा bttv *btv, u32 gpiobits);

/* extra tweaks क्रम some chipsets */
बाह्य व्योम bttv_check_chipset(व्योम);
बाह्य पूर्णांक bttv_handle_chipset(काष्ठा bttv *btv);

/* ---------------------------------------------------------- */
/* exported by bttv-अगर.c                                      */

/* this obsolete -- please use the sysfs-based
   पूर्णांकerface below क्रम new code */

बाह्य काष्ठा pci_dev* bttv_get_pcidev(अचिन्हित पूर्णांक card);

/* sets GPOE रेजिस्टर (BT848_GPIO_OUT_EN) to new value:
   data | (current_GPOE_value & ~mask)
   वापसs negative value अगर error occurred
*/
बाह्य पूर्णांक bttv_gpio_enable(अचिन्हित पूर्णांक card,
			    अचिन्हित दीर्घ mask, अचिन्हित दीर्घ data);

/* fills data with GPDATA रेजिस्टर contents
   वापसs negative value अगर error occurred
*/
बाह्य पूर्णांक bttv_पढ़ो_gpio(अचिन्हित पूर्णांक card, अचिन्हित दीर्घ *data);

/* sets GPDATA रेजिस्टर to new value:
  (data & mask) | (current_GPDATA_value & ~mask)
  वापसs negative value अगर error occurred
*/
बाह्य पूर्णांक bttv_ग_लिखो_gpio(अचिन्हित पूर्णांक card,
			   अचिन्हित दीर्घ mask, अचिन्हित दीर्घ data);




/* ---------------------------------------------------------- */
/* sysfs/driver-moded based gpio access पूर्णांकerface             */

काष्ठा bttv_sub_device अणु
	काष्ठा device    dev;
	काष्ठा bttv_core *core;
	काष्ठा list_head list;
पूर्ण;
#घोषणा to_bttv_sub_dev(x) container_of((x), काष्ठा bttv_sub_device, dev)

काष्ठा bttv_sub_driver अणु
	काष्ठा device_driver   drv;
	अक्षर                   wanted[20];
	पूर्णांक                    (*probe)(काष्ठा bttv_sub_device *sub);
	व्योम                   (*हटाओ)(काष्ठा bttv_sub_device *sub);
पूर्ण;
#घोषणा to_bttv_sub_drv(x) container_of((x), काष्ठा bttv_sub_driver, drv)

पूर्णांक bttv_sub_रेजिस्टर(काष्ठा bttv_sub_driver *drv, अक्षर *wanted);
पूर्णांक bttv_sub_unरेजिस्टर(काष्ठा bttv_sub_driver *drv);

/* gpio access functions */
व्योम bttv_gpio_inout(काष्ठा bttv_core *core, u32 mask, u32 outbits);
u32 bttv_gpio_पढ़ो(काष्ठा bttv_core *core);
व्योम bttv_gpio_ग_लिखो(काष्ठा bttv_core *core, u32 value);
व्योम bttv_gpio_bits(काष्ठा bttv_core *core, u32 mask, u32 bits);

#घोषणा gpio_inout(mask,bits)  bttv_gpio_inout(&btv->c, mask, bits)
#घोषणा gpio_पढ़ो()            bttv_gpio_पढ़ो(&btv->c)
#घोषणा gpio_ग_लिखो(value)      bttv_gpio_ग_लिखो(&btv->c, value)
#घोषणा gpio_bits(mask,bits)   bttv_gpio_bits(&btv->c, mask, bits)


/* ---------------------------------------------------------- */
/* i2c                                                        */

#घोषणा bttv_call_all(btv, o, f, args...) \
	v4l2_device_call_all(&btv->c.v4l2_dev, 0, o, f, ##args)

#घोषणा bttv_call_all_err(btv, o, f, args...) \
	v4l2_device_call_until_err(&btv->c.v4l2_dev, 0, o, f, ##args)

बाह्य पूर्णांक bttv_I2CRead(काष्ठा bttv *btv, अचिन्हित अक्षर addr, अक्षर *probe_क्रम);
बाह्य पूर्णांक bttv_I2CWrite(काष्ठा bttv *btv, अचिन्हित अक्षर addr, अचिन्हित अक्षर b1,
			 अचिन्हित अक्षर b2, पूर्णांक both);
बाह्य व्योम bttv_पढ़ोee(काष्ठा bttv *btv, अचिन्हित अक्षर *eedata, पूर्णांक addr);

बाह्य पूर्णांक bttv_input_init(काष्ठा bttv *dev);
बाह्य व्योम bttv_input_fini(काष्ठा bttv *dev);
बाह्य व्योम bttv_input_irq(काष्ठा bttv *dev);

#पूर्ण_अगर /* _BTTV_H_ */
