<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * rc-map.h - define RC map names used by RC drivers
 *
 * Copyright (c) 2010 by Mauro Carvalho Chehab
 */

#अगर_अघोषित _MEDIA_RC_MAP_H
#घोषणा _MEDIA_RC_MAP_H

#समावेश <linux/input.h>
#समावेश <uapi/linux/lirc.h>

#घोषणा RC_PROTO_BIT_NONE		0ULL
#घोषणा RC_PROTO_BIT_UNKNOWN		BIT_ULL(RC_PROTO_UNKNOWN)
#घोषणा RC_PROTO_BIT_OTHER		BIT_ULL(RC_PROTO_OTHER)
#घोषणा RC_PROTO_BIT_RC5		BIT_ULL(RC_PROTO_RC5)
#घोषणा RC_PROTO_BIT_RC5X_20		BIT_ULL(RC_PROTO_RC5X_20)
#घोषणा RC_PROTO_BIT_RC5_SZ		BIT_ULL(RC_PROTO_RC5_SZ)
#घोषणा RC_PROTO_BIT_JVC		BIT_ULL(RC_PROTO_JVC)
#घोषणा RC_PROTO_BIT_SONY12		BIT_ULL(RC_PROTO_SONY12)
#घोषणा RC_PROTO_BIT_SONY15		BIT_ULL(RC_PROTO_SONY15)
#घोषणा RC_PROTO_BIT_SONY20		BIT_ULL(RC_PROTO_SONY20)
#घोषणा RC_PROTO_BIT_NEC		BIT_ULL(RC_PROTO_NEC)
#घोषणा RC_PROTO_BIT_NECX		BIT_ULL(RC_PROTO_NECX)
#घोषणा RC_PROTO_BIT_NEC32		BIT_ULL(RC_PROTO_NEC32)
#घोषणा RC_PROTO_BIT_SANYO		BIT_ULL(RC_PROTO_SANYO)
#घोषणा RC_PROTO_BIT_MCIR2_KBD		BIT_ULL(RC_PROTO_MCIR2_KBD)
#घोषणा RC_PROTO_BIT_MCIR2_MSE		BIT_ULL(RC_PROTO_MCIR2_MSE)
#घोषणा RC_PROTO_BIT_RC6_0		BIT_ULL(RC_PROTO_RC6_0)
#घोषणा RC_PROTO_BIT_RC6_6A_20		BIT_ULL(RC_PROTO_RC6_6A_20)
#घोषणा RC_PROTO_BIT_RC6_6A_24		BIT_ULL(RC_PROTO_RC6_6A_24)
#घोषणा RC_PROTO_BIT_RC6_6A_32		BIT_ULL(RC_PROTO_RC6_6A_32)
#घोषणा RC_PROTO_BIT_RC6_MCE		BIT_ULL(RC_PROTO_RC6_MCE)
#घोषणा RC_PROTO_BIT_SHARP		BIT_ULL(RC_PROTO_SHARP)
#घोषणा RC_PROTO_BIT_XMP		BIT_ULL(RC_PROTO_XMP)
#घोषणा RC_PROTO_BIT_CEC		BIT_ULL(RC_PROTO_CEC)
#घोषणा RC_PROTO_BIT_IMON		BIT_ULL(RC_PROTO_IMON)
#घोषणा RC_PROTO_BIT_RCMM12		BIT_ULL(RC_PROTO_RCMM12)
#घोषणा RC_PROTO_BIT_RCMM24		BIT_ULL(RC_PROTO_RCMM24)
#घोषणा RC_PROTO_BIT_RCMM32		BIT_ULL(RC_PROTO_RCMM32)
#घोषणा RC_PROTO_BIT_XBOX_DVD		BIT_ULL(RC_PROTO_XBOX_DVD)

#अगर IS_ENABLED(CONFIG_IR_RC5_DECODER)
#घोषणा __RC_PROTO_RC5_CODEC \
	(RC_PROTO_BIT_RC5 | RC_PROTO_BIT_RC5X_20 |  RC_PROTO_BIT_RC5_SZ)
#अन्यथा
#घोषणा __RC_PROTO_RC5_CODEC 0
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IR_JVC_DECODER)
#घोषणा __RC_PROTO_JVC_CODEC RC_PROTO_BIT_JVC
#अन्यथा
#घोषणा __RC_PROTO_JVC_CODEC 0
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_SONY_DECODER)
#घोषणा __RC_PROTO_SONY_CODEC \
	(RC_PROTO_BIT_SONY12 | RC_PROTO_BIT_SONY15 |  RC_PROTO_BIT_SONY20)
#अन्यथा
#घोषणा __RC_PROTO_SONY_CODEC 0
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_NEC_DECODER)
#घोषणा __RC_PROTO_NEC_CODEC \
	(RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX | RC_PROTO_BIT_NEC32)
#अन्यथा
#घोषणा __RC_PROTO_NEC_CODEC 0
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_SANYO_DECODER)
#घोषणा __RC_PROTO_SANYO_CODEC RC_PROTO_BIT_SANYO
#अन्यथा
#घोषणा __RC_PROTO_SANYO_CODEC 0
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_MCE_KBD_DECODER)
#घोषणा __RC_PROTO_MCE_KBD_CODEC \
	(RC_PROTO_BIT_MCIR2_KBD |  RC_PROTO_BIT_MCIR2_MSE)
#अन्यथा
#घोषणा __RC_PROTO_MCE_KBD_CODEC 0
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_RC6_DECODER)
#घोषणा __RC_PROTO_RC6_CODEC \
	(RC_PROTO_BIT_RC6_0 | RC_PROTO_BIT_RC6_6A_20 | \
	 RC_PROTO_BIT_RC6_6A_24 |  RC_PROTO_BIT_RC6_6A_32 | \
	 RC_PROTO_BIT_RC6_MCE)
#अन्यथा
#घोषणा __RC_PROTO_RC6_CODEC 0
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_SHARP_DECODER)
#घोषणा __RC_PROTO_SHARP_CODEC RC_PROTO_BIT_SHARP
#अन्यथा
#घोषणा __RC_PROTO_SHARP_CODEC 0
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_XMP_DECODER)
#घोषणा __RC_PROTO_XMP_CODEC RC_PROTO_BIT_XMP
#अन्यथा
#घोषणा __RC_PROTO_XMP_CODEC 0
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_IMON_DECODER)
#घोषणा __RC_PROTO_IMON_CODEC RC_PROTO_BIT_IMON
#अन्यथा
#घोषणा __RC_PROTO_IMON_CODEC 0
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_RCMM_DECODER)
#घोषणा __RC_PROTO_RCMM_CODEC \
	(RC_PROTO_BIT_RCMM12 | RC_PROTO_BIT_RCMM24 | RC_PROTO_BIT_RCMM32)
#अन्यथा
#घोषणा __RC_PROTO_RCMM_CODEC 0
#पूर्ण_अगर

/* All kernel-based codecs have encoders and decoders */
#घोषणा RC_PROTO_BIT_ALL_IR_DECODER \
	(__RC_PROTO_RC5_CODEC | __RC_PROTO_JVC_CODEC | __RC_PROTO_SONY_CODEC | \
	 __RC_PROTO_NEC_CODEC | __RC_PROTO_SANYO_CODEC | \
	 __RC_PROTO_MCE_KBD_CODEC | __RC_PROTO_RC6_CODEC | \
	 __RC_PROTO_SHARP_CODEC | __RC_PROTO_XMP_CODEC | \
	 __RC_PROTO_IMON_CODEC | __RC_PROTO_RCMM_CODEC)

#घोषणा RC_PROTO_BIT_ALL_IR_ENCODER \
	(__RC_PROTO_RC5_CODEC | __RC_PROTO_JVC_CODEC | __RC_PROTO_SONY_CODEC | \
	 __RC_PROTO_NEC_CODEC | __RC_PROTO_SANYO_CODEC | \
	 __RC_PROTO_MCE_KBD_CODEC | __RC_PROTO_RC6_CODEC | \
	 __RC_PROTO_SHARP_CODEC | __RC_PROTO_XMP_CODEC | \
	 __RC_PROTO_IMON_CODEC | __RC_PROTO_RCMM_CODEC)

#घोषणा RC_SCANCODE_UNKNOWN(x)			(x)
#घोषणा RC_SCANCODE_OTHER(x)			(x)
#घोषणा RC_SCANCODE_NEC(addr, cmd)		(((addr) << 8) | (cmd))
#घोषणा RC_SCANCODE_NECX(addr, cmd)		(((addr) << 8) | (cmd))
#घोषणा RC_SCANCODE_NEC32(data)			((data) & 0xffffffff)
#घोषणा RC_SCANCODE_RC5(sys, cmd)		(((sys) << 8) | (cmd))
#घोषणा RC_SCANCODE_RC5_SZ(sys, cmd)		(((sys) << 8) | (cmd))
#घोषणा RC_SCANCODE_RC6_0(sys, cmd)		(((sys) << 8) | (cmd))
#घोषणा RC_SCANCODE_RC6_6A(venकरोr, sys, cmd)	(((venकरोr) << 16) | ((sys) << 8) | (cmd))

/**
 * काष्ठा rc_map_table - represents a scancode/keycode pair
 *
 * @scancode: scan code (u64)
 * @keycode: Linux input keycode
 */
काष्ठा rc_map_table अणु
	u64	scancode;
	u32	keycode;
पूर्ण;

/**
 * काष्ठा rc_map - represents a keycode map table
 *
 * @scan: poपूर्णांकer to काष्ठा &rc_map_table
 * @size: Max number of entries
 * @len: Number of entries that are in use
 * @alloc: size of \*scan, in bytes
 * @rc_proto: type of the remote controller protocol, as defined at
 *	     क्रमागत &rc_proto
 * @name: name of the key map table
 * @lock: lock to protect access to this काष्ठाure
 */
काष्ठा rc_map अणु
	काष्ठा rc_map_table	*scan;
	अचिन्हित पूर्णांक		size;
	अचिन्हित पूर्णांक		len;
	अचिन्हित पूर्णांक		alloc;
	क्रमागत rc_proto		rc_proto;
	स्थिर अक्षर		*name;
	spinlock_t		lock;
पूर्ण;

/**
 * काष्ठा rc_map_list - list of the रेजिस्टरed &rc_map maps
 *
 * @list: poपूर्णांकer to काष्ठा &list_head
 * @map: poपूर्णांकer to काष्ठा &rc_map
 */
काष्ठा rc_map_list अणु
	काष्ठा list_head	 list;
	काष्ठा rc_map map;
पूर्ण;

#अगर_घोषित CONFIG_MEDIA_CEC_RC
/*
 * rc_map_list from rc-cec.c
 */
बाह्य काष्ठा rc_map_list cec_map;
#पूर्ण_अगर

/* Routines from rc-map.c */

/**
 * rc_map_रेजिस्टर() - Registers a Remote Controller scancode map
 *
 * @map:	poपूर्णांकer to काष्ठा rc_map_list
 */
पूर्णांक rc_map_रेजिस्टर(काष्ठा rc_map_list *map);

/**
 * rc_map_unरेजिस्टर() - Unरेजिस्टरs a Remote Controller scancode map
 *
 * @map:	poपूर्णांकer to काष्ठा rc_map_list
 */
व्योम rc_map_unरेजिस्टर(काष्ठा rc_map_list *map);

/**
 * rc_map_get - माला_लो an RC map from its name
 * @name: name of the RC scancode map
 */
काष्ठा rc_map *rc_map_get(स्थिर अक्षर *name);

/* Names of the several keytables defined in-kernel */

#घोषणा RC_MAP_ADSTECH_DVB_T_PCI         "rc-adstech-dvb-t-pci"
#घोषणा RC_MAP_ALINK_DTU_M               "rc-alink-dtu-m"
#घोषणा RC_MAP_ANYSEE                    "rc-anysee"
#घोषणा RC_MAP_APAC_VIEWCOMP             "rc-apac-viewcomp"
#घोषणा RC_MAP_ASTROMETA_T2HYBRID        "rc-astrometa-t2hybrid"
#घोषणा RC_MAP_ASUS_PC39                 "rc-asus-pc39"
#घोषणा RC_MAP_ASUS_PS3_100              "rc-asus-ps3-100"
#घोषणा RC_MAP_ATI_TV_WONDER_HD_600      "rc-ati-tv-wonder-hd-600"
#घोषणा RC_MAP_ATI_X10                   "rc-ati-x10"
#घोषणा RC_MAP_AVERMEDIA                 "rc-avermedia"
#घोषणा RC_MAP_AVERMEDIA_A16D            "rc-avermedia-a16d"
#घोषणा RC_MAP_AVERMEDIA_CARDBUS         "rc-avermedia-cardbus"
#घोषणा RC_MAP_AVERMEDIA_DVBT            "rc-avermedia-dvbt"
#घोषणा RC_MAP_AVERMEDIA_M135A           "rc-avermedia-m135a"
#घोषणा RC_MAP_AVERMEDIA_M733A_RM_K6     "rc-avermedia-m733a-rm-k6"
#घोषणा RC_MAP_AVERMEDIA_RM_KS           "rc-avermedia-rm-ks"
#घोषणा RC_MAP_AVERTV_303                "rc-avertv-303"
#घोषणा RC_MAP_AZUREWAVE_AD_TU700        "rc-azurewave-ad-tu700"
#घोषणा RC_MAP_BEELINK_GS1               "rc-beelink-gs1"
#घोषणा RC_MAP_BEHOLD                    "rc-behold"
#घोषणा RC_MAP_BEHOLD_COLUMBUS           "rc-behold-columbus"
#घोषणा RC_MAP_BUDGET_CI_OLD             "rc-budget-ci-old"
#घोषणा RC_MAP_CEC                       "rc-cec"
#घोषणा RC_MAP_CINERGY                   "rc-cinergy"
#घोषणा RC_MAP_CINERGY_1400              "rc-cinergy-1400"
#घोषणा RC_MAP_D680_DMB                  "rc-d680-dmb"
#घोषणा RC_MAP_DELOCK_61959              "rc-delock-61959"
#घोषणा RC_MAP_DIB0700_NEC_TABLE         "rc-dib0700-nec"
#घोषणा RC_MAP_DIB0700_RC5_TABLE         "rc-dib0700-rc5"
#घोषणा RC_MAP_DIGITALNOW_TINYTWIN       "rc-digitalnow-tinytwin"
#घोषणा RC_MAP_DIGITTRADE                "rc-digittrade"
#घोषणा RC_MAP_DM1105_NEC                "rc-dm1105-nec"
#घोषणा RC_MAP_DNTV_LIVE_DVB_T           "rc-dntv-live-dvb-t"
#घोषणा RC_MAP_DNTV_LIVE_DVBT_PRO        "rc-dntv-live-dvbt-pro"
#घोषणा RC_MAP_DTT200U                   "rc-dtt200u"
#घोषणा RC_MAP_DVBSKY                    "rc-dvbsky"
#घोषणा RC_MAP_DVICO_MCE		 "rc-dvico-mce"
#घोषणा RC_MAP_DVICO_PORTABLE		 "rc-dvico-portable"
#घोषणा RC_MAP_EMPTY                     "rc-empty"
#घोषणा RC_MAP_EM_TERRATEC               "rc-em-terratec"
#घोषणा RC_MAP_ENCORE_ENLTV              "rc-encore-enltv"
#घोषणा RC_MAP_ENCORE_ENLTV2             "rc-encore-enltv2"
#घोषणा RC_MAP_ENCORE_ENLTV_FM53         "rc-encore-enltv-fm53"
#घोषणा RC_MAP_EVGA_INDTUBE              "rc-evga-indtube"
#घोषणा RC_MAP_EZTV                      "rc-eztv"
#घोषणा RC_MAP_FLYDVB                    "rc-flydvb"
#घोषणा RC_MAP_FLYVIDEO                  "rc-flyvideo"
#घोषणा RC_MAP_FUSIONHDTV_MCE            "rc-fusionhdtv-mce"
#घोषणा RC_MAP_GADMEI_RM008Z             "rc-gadmei-rm008z"
#घोषणा RC_MAP_GEEKBOX                   "rc-geekbox"
#घोषणा RC_MAP_GENIUS_TVGO_A11MCE        "rc-genius-tvgo-a11mce"
#घोषणा RC_MAP_GOTVIEW7135               "rc-gotview7135"
#घोषणा RC_MAP_HAUPPAUGE                 "rc-hauppauge"
#घोषणा RC_MAP_HAUPPAUGE_NEW             "rc-hauppauge"
#घोषणा RC_MAP_HISI_POPLAR               "rc-hisi-poplar"
#घोषणा RC_MAP_HISI_TV_DEMO              "rc-hisi-tv-demo"
#घोषणा RC_MAP_IMON_MCE                  "rc-imon-mce"
#घोषणा RC_MAP_IMON_PAD                  "rc-imon-pad"
#घोषणा RC_MAP_IMON_RSC                  "rc-imon-rsc"
#घोषणा RC_MAP_IODATA_BCTV7E             "rc-iodata-bctv7e"
#घोषणा RC_MAP_IT913X_V1                 "rc-it913x-v1"
#घोषणा RC_MAP_IT913X_V2                 "rc-it913x-v2"
#घोषणा RC_MAP_KAIOMY                    "rc-kaiomy"
#घोषणा RC_MAP_KHADAS                    "rc-khadas"
#घोषणा RC_MAP_KHAMSIN                   "rc-khamsin"
#घोषणा RC_MAP_KWORLD_315U               "rc-kworld-315u"
#घोषणा RC_MAP_KWORLD_PC150U             "rc-kworld-pc150u"
#घोषणा RC_MAP_KWORLD_PLUS_TV_ANALOG     "rc-kworld-plus-tv-analog"
#घोषणा RC_MAP_LEADTEK_Y04G0051          "rc-leadtek-y04g0051"
#घोषणा RC_MAP_LME2510                   "rc-lme2510"
#घोषणा RC_MAP_MANLI                     "rc-manli"
#घोषणा RC_MAP_MECOOL_KII_PRO            "rc-mecool-kii-pro"
#घोषणा RC_MAP_MECOOL_KIII_PRO           "rc-mecool-kiii-pro"
#घोषणा RC_MAP_MEDION_X10                "rc-medion-x10"
#घोषणा RC_MAP_MEDION_X10_DIGITAINER     "rc-medion-x10-digitainer"
#घोषणा RC_MAP_MEDION_X10_OR2X           "rc-medion-x10-or2x"
#घोषणा RC_MAP_MINIX_NEO                 "rc-minix-neo"
#घोषणा RC_MAP_MSI_DIGIVOX_II            "rc-msi-digivox-ii"
#घोषणा RC_MAP_MSI_DIGIVOX_III           "rc-msi-digivox-iii"
#घोषणा RC_MAP_MSI_TVANYWHERE            "rc-msi-tvanywhere"
#घोषणा RC_MAP_MSI_TVANYWHERE_PLUS       "rc-msi-tvanywhere-plus"
#घोषणा RC_MAP_NEBULA                    "rc-nebula"
#घोषणा RC_MAP_NEC_TERRATEC_CINERGY_XS   "rc-nec-terratec-cinergy-xs"
#घोषणा RC_MAP_NORWOOD                   "rc-norwood"
#घोषणा RC_MAP_NPGTECH                   "rc-npgtech"
#घोषणा RC_MAP_ODROID                    "rc-odroid"
#घोषणा RC_MAP_PCTV_SEDNA                "rc-pctv-sedna"
#घोषणा RC_MAP_PINE64                    "rc-pine64"
#घोषणा RC_MAP_PINNACLE_COLOR            "rc-pinnacle-color"
#घोषणा RC_MAP_PINNACLE_GREY             "rc-pinnacle-grey"
#घोषणा RC_MAP_PINNACLE_PCTV_HD          "rc-pinnacle-pctv-hd"
#घोषणा RC_MAP_PIXELVIEW                 "rc-pixelview"
#घोषणा RC_MAP_PIXELVIEW_002T            "rc-pixelview-002t"
#घोषणा RC_MAP_PIXELVIEW_MK12            "rc-pixelview-mk12"
#घोषणा RC_MAP_PIXELVIEW_NEW             "rc-pixelview-new"
#घोषणा RC_MAP_POWERCOLOR_REAL_ANGEL     "rc-powercolor-real-angel"
#घोषणा RC_MAP_PROTEUS_2309              "rc-proteus-2309"
#घोषणा RC_MAP_PURPLETV                  "rc-purpletv"
#घोषणा RC_MAP_PV951                     "rc-pv951"
#घोषणा RC_MAP_RC5_TV                    "rc-rc5-tv"
#घोषणा RC_MAP_RC6_MCE                   "rc-rc6-mce"
#घोषणा RC_MAP_REAL_AUDIO_220_32_KEYS    "rc-real-audio-220-32-keys"
#घोषणा RC_MAP_REDDO                     "rc-reddo"
#घोषणा RC_MAP_SNAPSTREAM_FIREFLY        "rc-snapstream-firefly"
#घोषणा RC_MAP_STREAMZAP                 "rc-streamzap"
#घोषणा RC_MAP_SU3000                    "rc-su3000"
#घोषणा RC_MAP_TANGO                     "rc-tango"
#घोषणा RC_MAP_TANIX_TX3MINI             "rc-tanix-tx3mini"
#घोषणा RC_MAP_TANIX_TX5MAX              "rc-tanix-tx5max"
#घोषणा RC_MAP_TBS_NEC                   "rc-tbs-nec"
#घोषणा RC_MAP_TECHNISAT_TS35            "rc-technisat-ts35"
#घोषणा RC_MAP_TECHNISAT_USB2            "rc-technisat-usb2"
#घोषणा RC_MAP_TERRATEC_CINERGY_C_PCI    "rc-terratec-cinergy-c-pci"
#घोषणा RC_MAP_TERRATEC_CINERGY_S2_HD    "rc-terratec-cinergy-s2-hd"
#घोषणा RC_MAP_TERRATEC_CINERGY_XS       "rc-terratec-cinergy-xs"
#घोषणा RC_MAP_TERRATEC_SLIM             "rc-terratec-slim"
#घोषणा RC_MAP_TERRATEC_SLIM_2           "rc-terratec-slim-2"
#घोषणा RC_MAP_TEVII_NEC                 "rc-tevii-nec"
#घोषणा RC_MAP_TIVO                      "rc-tivo"
#घोषणा RC_MAP_TOTAL_MEDIA_IN_HAND       "rc-total-media-in-hand"
#घोषणा RC_MAP_TOTAL_MEDIA_IN_HAND_02    "rc-total-media-in-hand-02"
#घोषणा RC_MAP_TREKSTOR                  "rc-trekstor"
#घोषणा RC_MAP_TT_1500                   "rc-tt-1500"
#घोषणा RC_MAP_TWINHAN_DTV_CAB_CI        "rc-twinhan-dtv-cab-ci"
#घोषणा RC_MAP_TWINHAN_VP1027_DVBS       "rc-twinhan1027"
#घोषणा RC_MAP_VEGA_S9X                  "rc-vega-s9x"
#घोषणा RC_MAP_VIDEOMATE_K100            "rc-videomate-k100"
#घोषणा RC_MAP_VIDEOMATE_S350            "rc-videomate-s350"
#घोषणा RC_MAP_VIDEOMATE_TV_PVR          "rc-videomate-tv-pvr"
#घोषणा RC_MAP_KII_PRO                   "rc-videostrong-kii-pro"
#घोषणा RC_MAP_WETEK_HUB                 "rc-wetek-hub"
#घोषणा RC_MAP_WETEK_PLAY2               "rc-wetek-play2"
#घोषणा RC_MAP_WINFAST                   "rc-winfast"
#घोषणा RC_MAP_WINFAST_USBII_DELUXE      "rc-winfast-usbii-deluxe"
#घोषणा RC_MAP_X96MAX                    "rc-x96max"
#घोषणा RC_MAP_XBOX_360                  "rc-xbox-360"
#घोषणा RC_MAP_XBOX_DVD                  "rc-xbox-dvd"
#घोषणा RC_MAP_ZX_IRDEC                  "rc-zx-irdec"

/*
 * Please, करो not just append newer Remote Controller names at the end.
 * The names should be ordered in alphabetical order
 */

#पूर्ण_अगर /* _MEDIA_RC_MAP_H */
