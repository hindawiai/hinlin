<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <bcm47xx.h>
#समावेश <bcm47xx_board.h>

काष्ठा bcm47xx_board_type अणु
	स्थिर क्रमागत bcm47xx_board board;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा bcm47xx_board_type_list1 अणु
	काष्ठा bcm47xx_board_type board;
	स्थिर अक्षर *value1;
पूर्ण;

काष्ठा bcm47xx_board_type_list2 अणु
	काष्ठा bcm47xx_board_type board;
	स्थिर अक्षर *value1;
	स्थिर अक्षर *value2;
पूर्ण;

काष्ठा bcm47xx_board_type_list3 अणु
	काष्ठा bcm47xx_board_type board;
	स्थिर अक्षर *value1;
	स्थिर अक्षर *value2;
	स्थिर अक्षर *value3;
पूर्ण;

काष्ठा bcm47xx_board_store अणु
	क्रमागत bcm47xx_board board;
	अक्षर name[BCM47XX_BOARD_MAX_NAME];
पूर्ण;

/* model_name */
अटल स्थिर
काष्ठा bcm47xx_board_type_list1 bcm47xx_board_list_model_name[] __initस्थिर = अणु
	अणुअणुBCM47XX_BOARD_DLINK_सूची130, "D-Link DIR-130"पूर्ण, "DIR-130"पूर्ण,
	अणुअणुBCM47XX_BOARD_DLINK_सूची330, "D-Link DIR-330"पूर्ण, "DIR-330"पूर्ण,
	अणु अणु0पूर्ण, शून्यपूर्ण,
पूर्ण;

/* hardware_version */
अटल स्थिर
काष्ठा bcm47xx_board_type_list1 bcm47xx_board_list_hardware_version[] __initस्थिर = अणु
	अणुअणुBCM47XX_BOARD_ASUS_RTN10U, "Asus RT-N10U"पूर्ण, "RTN10U"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN10D, "Asus RT-N10D"पूर्ण, "RTN10D"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN12, "Asus RT-N12"पूर्ण, "RT-N12"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN12B1, "Asus RT-N12B1"पूर्ण, "RTN12B1"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN12C1, "Asus RT-N12C1"पूर्ण, "RTN12C1"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN12D1, "Asus RT-N12D1"पूर्ण, "RTN12D1"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN12HP, "Asus RT-N12HP"पूर्ण, "RTN12HP"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN16, "Asus RT-N16"पूर्ण, "RT-N16-"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_WL320GE, "Asus WL320GE"पूर्ण, "WL320G-"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_WL330GE, "Asus WL330GE"पूर्ण, "WL330GE-"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_WL500GD, "Asus WL500GD"पूर्ण, "WL500gd-"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_WL500GPV1, "Asus WL500GP V1"पूर्ण, "WL500gp-"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_WL500GPV2, "Asus WL500GP V2"पूर्ण, "WL500GPV2-"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_WL500W, "Asus WL500W"पूर्ण, "WL500gW-"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_WL520GC, "Asus WL520GC"पूर्ण, "WL520GC-"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_WL520GU, "Asus WL520GU"पूर्ण, "WL520GU-"पूर्ण,
	अणुअणुBCM47XX_BOARD_BELKIN_F7D3301, "Belkin F7D3301"पूर्ण, "F7D3301"पूर्ण,
	अणुअणुBCM47XX_BOARD_BELKIN_F7D3302, "Belkin F7D3302"पूर्ण, "F7D3302"पूर्ण,
	अणुअणुBCM47XX_BOARD_BELKIN_F7D4301, "Belkin F7D4301"पूर्ण, "F7D4301"पूर्ण,
	अणुअणुBCM47XX_BOARD_BELKIN_F7D4302, "Belkin F7D4302"पूर्ण, "F7D4302"पूर्ण,
	अणुअणुBCM47XX_BOARD_BELKIN_F7D4401, "Belkin F7D4401"पूर्ण, "F7D4401"पूर्ण,
	अणु अणु0पूर्ण, शून्यपूर्ण,
पूर्ण;

/* hardware_version, boardnum */
अटल स्थिर
काष्ठा bcm47xx_board_type_list2 bcm47xx_board_list_hw_version_num[] __initस्थिर = अणु
	अणुअणुBCM47XX_BOARD_MICROSOFT_MN700, "Microsoft MN-700"पूर्ण, "WL500-", "mn700"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_WL500G, "Asus WL500G"पूर्ण, "WL500-", "asusX"पूर्ण,
	अणु अणु0पूर्ण, शून्यपूर्ण,
पूर्ण;

/* productid */
अटल स्थिर
काष्ठा bcm47xx_board_type_list1 bcm47xx_board_list_productid[] __initस्थिर = अणु
	अणुअणुBCM47XX_BOARD_ASUS_RTAC66U, "Asus RT-AC66U"पूर्ण, "RT-AC66U"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN10, "Asus RT-N10"पूर्ण, "RT-N10"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN10D, "Asus RT-N10D"पूर्ण, "RT-N10D"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN15U, "Asus RT-N15U"पूर्ण, "RT-N15U"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN16, "Asus RT-N16"पूर्ण, "RT-N16"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN53, "Asus RT-N53"पूर्ण, "RT-N53"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_RTN66U, "Asus RT-N66U"पूर्ण, "RT-N66U"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_WL300G, "Asus WL300G"पूर्ण, "WL300g"पूर्ण,
	अणुअणुBCM47XX_BOARD_ASUS_WLHDD, "Asus WLHDD"पूर्ण, "WLHDD"पूर्ण,
	अणु अणु0पूर्ण, शून्यपूर्ण,
पूर्ण;

/* ModelId */
अटल स्थिर
काष्ठा bcm47xx_board_type_list1 bcm47xx_board_list_ModelId[] __initस्थिर = अणु
	अणुअणुBCM47XX_BOARD_DELL_TM2300, "Dell TrueMobile 2300"पूर्ण, "WX-5565"पूर्ण,
	अणुअणुBCM47XX_BOARD_MOTOROLA_WE800G, "Motorola WE800G"पूर्ण, "WE800G"पूर्ण,
	अणुअणुBCM47XX_BOARD_MOTOROLA_WR850GP, "Motorola WR850GP"पूर्ण, "WR850GP"पूर्ण,
	अणुअणुBCM47XX_BOARD_MOTOROLA_WR850GV2V3, "Motorola WR850G"पूर्ण, "WR850G"पूर्ण,
	अणु अणु0पूर्ण, शून्यपूर्ण,
पूर्ण;

/* melco_id or buf1falo_id */
अटल स्थिर
काष्ठा bcm47xx_board_type_list1 bcm47xx_board_list_melco_id[] __initस्थिर = अणु
	अणुअणुBCM47XX_BOARD_BUFFALO_WBR2_G54, "Buffalo WBR2-G54"पूर्ण, "29bb0332"पूर्ण,
	अणुअणुBCM47XX_BOARD_BUFFALO_WHR2_A54G54, "Buffalo WHR2-A54G54"पूर्ण, "290441dd"पूर्ण,
	अणुअणुBCM47XX_BOARD_BUFFALO_WHR_G125, "Buffalo WHR-G125"पूर्ण, "32093"पूर्ण,
	अणुअणुBCM47XX_BOARD_BUFFALO_WHR_G54S, "Buffalo WHR-G54S"पूर्ण, "30182"पूर्ण,
	अणुअणुBCM47XX_BOARD_BUFFALO_WHR_HP_G54, "Buffalo WHR-HP-G54"पूर्ण, "30189"पूर्ण,
	अणुअणुBCM47XX_BOARD_BUFFALO_WLA2_G54L, "Buffalo WLA2-G54L"पूर्ण, "29129"पूर्ण,
	अणुअणुBCM47XX_BOARD_BUFFALO_WZR_G300N, "Buffalo WZR-G300N"पूर्ण, "31120"पूर्ण,
	अणुअणुBCM47XX_BOARD_BUFFALO_WZR_RS_G54, "Buffalo WZR-RS-G54"पूर्ण, "30083"पूर्ण,
	अणुअणुBCM47XX_BOARD_BUFFALO_WZR_RS_G54HP, "Buffalo WZR-RS-G54HP"पूर्ण, "30103"पूर्ण,
	अणु अणु0पूर्ण, शून्यपूर्ण,
पूर्ण;

/* boot_hw_model, boot_hw_ver */
अटल स्थिर
काष्ठा bcm47xx_board_type_list2 bcm47xx_board_list_boot_hw[] __initस्थिर = अणु
	/* like WRT160N v3.0 */
	अणुअणुBCM47XX_BOARD_CISCO_M10V1, "Cisco M10"पूर्ण, "M10", "1.0"पूर्ण,
	/* like WRT310N v2.0 */
	अणुअणुBCM47XX_BOARD_CISCO_M20V1, "Cisco M20"पूर्ण, "M20", "1.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_E900V1, "Linksys E900 V1"पूर्ण, "E900", "1.0"पूर्ण,
	/* like WRT160N v3.0 */
	अणुअणुBCM47XX_BOARD_LINKSYS_E1000V1, "Linksys E1000 V1"पूर्ण, "E100", "1.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_E1000V2, "Linksys E1000 V2"पूर्ण, "E1000", "2.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_E1000V21, "Linksys E1000 V2.1"पूर्ण, "E1000", "2.1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_E1200V2, "Linksys E1200 V2"पूर्ण, "E1200", "2.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_E2000V1, "Linksys E2000 V1"पूर्ण, "Linksys E2000", "1.0"पूर्ण,
	/* like WRT610N v2.0 */
	अणुअणुBCM47XX_BOARD_LINKSYS_E3000V1, "Linksys E3000 V1"पूर्ण, "E300", "1.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_E3200V1, "Linksys E3200 V1"पूर्ण, "E3200", "1.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_E4200V1, "Linksys E4200 V1"पूर्ण, "E4200", "1.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT150NV11, "Linksys WRT150N V1.1"पूर्ण, "WRT150N", "1.1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT150NV1, "Linksys WRT150N V1"पूर्ण, "WRT150N", "1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT160NV1, "Linksys WRT160N V1"पूर्ण, "WRT160N", "1.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT160NV3, "Linksys WRT160N V3"पूर्ण, "WRT160N", "3.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT300NV11, "Linksys WRT300N V1.1"पूर्ण, "WRT300N", "1.1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT310NV1, "Linksys WRT310N V1"पूर्ण, "WRT310N", "1.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT310NV2, "Linksys WRT310N V2"पूर्ण, "WRT310N", "2.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT54G3GV2, "Linksys WRT54G3GV2-VF"पूर्ण, "WRT54G3GV2-VF", "1.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT610NV1, "Linksys WRT610N V1"पूर्ण, "WRT610N", "1.0"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT610NV2, "Linksys WRT610N V2"पूर्ण, "WRT610N", "2.0"पूर्ण,
	अणु अणु0पूर्ण, शून्यपूर्ण,
पूर्ण;

/* board_id */
अटल स्थिर
काष्ठा bcm47xx_board_type_list1 bcm47xx_board_list_board_id[] __initस्थिर = अणु
	अणुअणुBCM47XX_BOARD_LUXUL_ABR_4400_V1, "Luxul ABR-4400 V1"पूर्ण, "luxul_abr4400_v1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LUXUL_XAP_310_V1, "Luxul XAP-310 V1"पूर्ण, "luxul_xap310_v1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LUXUL_XAP_1210_V1, "Luxul XAP-1210 V1"पूर्ण, "luxul_xap1210_v1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LUXUL_XAP_1230_V1, "Luxul XAP-1230 V1"पूर्ण, "luxul_xap1230_v1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LUXUL_XAP_1240_V1, "Luxul XAP-1240 V1"पूर्ण, "luxul_xap1240_v1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LUXUL_XAP_1500_V1, "Luxul XAP-1500 V1"पूर्ण, "luxul_xap1500_v1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LUXUL_XBR_4400_V1, "Luxul XBR-4400 V1"पूर्ण, "luxul_xbr4400_v1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LUXUL_XVW_P30_V1, "Luxul XVW-P30 V1"पूर्ण, "luxul_xvwp30_v1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LUXUL_XWR_600_V1, "Luxul XWR-600 V1"पूर्ण, "luxul_xwr600_v1"पूर्ण,
	अणुअणुBCM47XX_BOARD_LUXUL_XWR_1750_V1, "Luxul XWR-1750 V1"पूर्ण, "luxul_xwr1750_v1"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_R6200_V1, "Netgear R6200 V1"पूर्ण, "U12H192T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WGR614V8, "Netgear WGR614 V8"पूर्ण, "U12H072T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WGR614V9, "Netgear WGR614 V9"पूर्ण, "U12H094T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WGR614_V10, "Netgear WGR614 V10"पूर्ण, "U12H139T01_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNDR3300, "Netgear WNDR3300"पूर्ण, "U12H093T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNDR3400V1, "Netgear WNDR3400 V1"पूर्ण, "U12H155T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNDR3400V2, "Netgear WNDR3400 V2"पूर्ण, "U12H187T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNDR3400_V3, "Netgear WNDR3400 V3"पूर्ण, "U12H208T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNDR3400VCNA, "Netgear WNDR3400 Vcna"पूर्ण, "U12H155T01_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNDR3700V3, "Netgear WNDR3700 V3"पूर्ण, "U12H194T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNDR4000, "Netgear WNDR4000"पूर्ण, "U12H181T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNDR4500V1, "Netgear WNDR4500 V1"पूर्ण, "U12H189T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNDR4500V2, "Netgear WNDR4500 V2"पूर्ण, "U12H224T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNR1000_V3, "Netgear WNR1000 V3"पूर्ण, "U12H139T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNR1000_V3, "Netgear WNR1000 V3"पूर्ण, "U12H139T50_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNR2000, "Netgear WNR2000"पूर्ण, "U12H114T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNR3500L, "Netgear WNR3500L"पूर्ण, "U12H136T99_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNR3500U, "Netgear WNR3500U"पूर्ण, "U12H136T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNR3500V2, "Netgear WNR3500 V2"पूर्ण, "U12H127T00_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNR3500V2VC, "Netgear WNR3500 V2vc"पूर्ण, "U12H127T70_NETGEAR"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNR834BV2, "Netgear WNR834B V2"पूर्ण, "U12H081T00_NETGEAR"पूर्ण,
	अणु अणु0पूर्ण, शून्यपूर्ण,
पूर्ण;

/* boardtype, boardnum, boardrev */
अटल स्थिर
काष्ठा bcm47xx_board_type_list3 bcm47xx_board_list_board[] __initस्थिर = अणु
	अणुअणुBCM47XX_BOARD_HUAWEI_E970, "Huawei E970"पूर्ण, "0x048e", "0x5347", "0x11"पूर्ण,
	अणुअणुBCM47XX_BOARD_PHICOMM_M1, "Phicomm M1"पूर्ण, "0x0590", "80", "0x1104"पूर्ण,
	अणुअणुBCM47XX_BOARD_ZTE_H218N, "ZTE H218N"पूर्ण, "0x053d", "1234", "0x1305"पूर्ण,
	अणुअणुBCM47XX_BOARD_NETGEAR_WNR3500L, "Netgear WNR3500L"पूर्ण, "0x04CF", "3500", "02"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT54G_TYPE_0101, "Linksys WRT54G/GS/GL"पूर्ण, "0x0101", "42", "0x10"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT54G_TYPE_0467, "Linksys WRT54G/GS/GL"पूर्ण, "0x0467", "42", "0x10"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT54G_TYPE_0708, "Linksys WRT54G/GS/GL"पूर्ण, "0x0708", "42", "0x10"पूर्ण,
	अणु अणु0पूर्ण, शून्यपूर्ण,
पूर्ण;

/* boardtype, boardrev */
अटल स्थिर
काष्ठा bcm47xx_board_type_list2 bcm47xx_board_list_board_type_rev[] __initस्थिर = अणु
	अणुअणुBCM47XX_BOARD_SIEMENS_SE505V2, "Siemens SE505 V2"पूर्ण, "0x0101", "0x10"पूर्ण,
	अणु अणु0पूर्ण, शून्यपूर्ण,
पूर्ण;

/*
 * Some devices करोn't use any common NVRAM entry क्रम identअगरication and they
 * have only one model specअगरic variable.
 * They करोn't deserve own arrays, let's group them there using key-value array.
 */
अटल स्थिर
काष्ठा bcm47xx_board_type_list2 bcm47xx_board_list_key_value[] __initस्थिर = अणु
	अणुअणुBCM47XX_BOARD_ASUS_WL700GE, "Asus WL700"पूर्ण, "model_no", "WL700"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT300N_V1, "Linksys WRT300N V1"पूर्ण, "router_name", "WRT300N"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRT600N_V11, "Linksys WRT600N V1.1"पूर्ण, "Model_Name", "WRT600N"पूर्ण,
	अणुअणुBCM47XX_BOARD_LINKSYS_WRTSL54GS, "Linksys WRTSL54GS"पूर्ण, "machine_name", "WRTSL54GS"पूर्ण,
	अणु अणु0पूर्ण, शून्यपूर्ण,
पूर्ण;

अटल स्थिर
काष्ठा bcm47xx_board_type bcm47xx_board_unknown[] __initस्थिर = अणु
	अणुBCM47XX_BOARD_UNKNOWN, "Unknown Board"पूर्ण,
पूर्ण;

अटल काष्ठा bcm47xx_board_store bcm47xx_board = अणुBCM47XX_BOARD_NO, "Unknown Board"पूर्ण;

अटल __init स्थिर काष्ठा bcm47xx_board_type *bcm47xx_board_get_nvram(व्योम)
अणु
	अक्षर buf1[30];
	अक्षर buf2[30];
	अक्षर buf3[30];
	स्थिर काष्ठा bcm47xx_board_type_list1 *e1;
	स्थिर काष्ठा bcm47xx_board_type_list2 *e2;
	स्थिर काष्ठा bcm47xx_board_type_list3 *e3;

	अगर (bcm47xx_nvram_दो_पर्या("model_name", buf1, माप(buf1)) >= 0) अणु
		क्रम (e1 = bcm47xx_board_list_model_name; e1->value1; e1++) अणु
			अगर (!म_भेद(buf1, e1->value1))
				वापस &e1->board;
		पूर्ण
	पूर्ण

	अगर (bcm47xx_nvram_दो_पर्या("hardware_version", buf1, माप(buf1)) >= 0) अणु
		क्रम (e1 = bcm47xx_board_list_hardware_version; e1->value1; e1++) अणु
			अगर (strstarts(buf1, e1->value1))
				वापस &e1->board;
		पूर्ण
	पूर्ण

	अगर (bcm47xx_nvram_दो_पर्या("hardware_version", buf1, माप(buf1)) >= 0 &&
	    bcm47xx_nvram_दो_पर्या("boardnum", buf2, माप(buf2)) >= 0) अणु
		क्रम (e2 = bcm47xx_board_list_hw_version_num; e2->value1; e2++) अणु
			अगर (!strstarts(buf1, e2->value1) &&
			    !म_भेद(buf2, e2->value2))
				वापस &e2->board;
		पूर्ण
	पूर्ण

	अगर (bcm47xx_nvram_दो_पर्या("productid", buf1, माप(buf1)) >= 0) अणु
		क्रम (e1 = bcm47xx_board_list_productid; e1->value1; e1++) अणु
			अगर (!म_भेद(buf1, e1->value1))
				वापस &e1->board;
		पूर्ण
	पूर्ण

	अगर (bcm47xx_nvram_दो_पर्या("ModelId", buf1, माप(buf1)) >= 0) अणु
		क्रम (e1 = bcm47xx_board_list_ModelId; e1->value1; e1++) अणु
			अगर (!म_भेद(buf1, e1->value1))
				वापस &e1->board;
		पूर्ण
	पूर्ण

	अगर (bcm47xx_nvram_दो_पर्या("melco_id", buf1, माप(buf1)) >= 0 ||
	    bcm47xx_nvram_दो_पर्या("buf1falo_id", buf1, माप(buf1)) >= 0) अणु
		/* buffalo hardware, check id क्रम specअगरic hardware matches */
		क्रम (e1 = bcm47xx_board_list_melco_id; e1->value1; e1++) अणु
			अगर (!म_भेद(buf1, e1->value1))
				वापस &e1->board;
		पूर्ण
	पूर्ण

	अगर (bcm47xx_nvram_दो_पर्या("boot_hw_model", buf1, माप(buf1)) >= 0 &&
	    bcm47xx_nvram_दो_पर्या("boot_hw_ver", buf2, माप(buf2)) >= 0) अणु
		क्रम (e2 = bcm47xx_board_list_boot_hw; e2->value1; e2++) अणु
			अगर (!म_भेद(buf1, e2->value1) &&
			    !म_भेद(buf2, e2->value2))
				वापस &e2->board;
		पूर्ण
	पूर्ण

	अगर (bcm47xx_nvram_दो_पर्या("board_id", buf1, माप(buf1)) >= 0) अणु
		क्रम (e1 = bcm47xx_board_list_board_id; e1->value1; e1++) अणु
			अगर (!म_भेद(buf1, e1->value1))
				वापस &e1->board;
		पूर्ण
	पूर्ण

	अगर (bcm47xx_nvram_दो_पर्या("boardtype", buf1, माप(buf1)) >= 0 &&
	    bcm47xx_nvram_दो_पर्या("boardnum", buf2, माप(buf2)) >= 0 &&
	    bcm47xx_nvram_दो_पर्या("boardrev", buf3, माप(buf3)) >= 0) अणु
		क्रम (e3 = bcm47xx_board_list_board; e3->value1; e3++) अणु
			अगर (!म_भेद(buf1, e3->value1) &&
			    !म_भेद(buf2, e3->value2) &&
			    !म_भेद(buf3, e3->value3))
				वापस &e3->board;
		पूर्ण
	पूर्ण

	अगर (bcm47xx_nvram_दो_पर्या("boardtype", buf1, माप(buf1)) >= 0 &&
	    bcm47xx_nvram_दो_पर्या("boardrev", buf2, माप(buf2)) >= 0 &&
	    bcm47xx_nvram_दो_पर्या("boardnum", buf3, माप(buf3)) ==  -ENOENT) अणु
		क्रम (e2 = bcm47xx_board_list_board_type_rev; e2->value1; e2++) अणु
			अगर (!म_भेद(buf1, e2->value1) &&
			    !म_भेद(buf2, e2->value2))
				वापस &e2->board;
		पूर्ण
	पूर्ण

	क्रम (e2 = bcm47xx_board_list_key_value; e2->value1; e2++) अणु
		अगर (bcm47xx_nvram_दो_पर्या(e2->value1, buf1, माप(buf1)) >= 0) अणु
			अगर (!म_भेद(buf1, e2->value2))
				वापस &e2->board;
		पूर्ण
	पूर्ण

	वापस bcm47xx_board_unknown;
पूर्ण

व्योम __init bcm47xx_board_detect(व्योम)
अणु
	पूर्णांक err;
	अक्षर buf[10];
	स्थिर काष्ठा bcm47xx_board_type *board_detected;

	अगर (bcm47xx_board.board != BCM47XX_BOARD_NO)
		वापस;

	/* check अगर the nvram is available */
	err = bcm47xx_nvram_दो_पर्या("boardtype", buf, माप(buf));

	/* init of nvram failed, probably too early now */
	अगर (err == -ENXIO)
		वापस;

	board_detected = bcm47xx_board_get_nvram();
	bcm47xx_board.board = board_detected->board;
	strlcpy(bcm47xx_board.name, board_detected->name,
		BCM47XX_BOARD_MAX_NAME);
पूर्ण

क्रमागत bcm47xx_board bcm47xx_board_get(व्योम)
अणु
	वापस bcm47xx_board.board;
पूर्ण
EXPORT_SYMBOL(bcm47xx_board_get);

स्थिर अक्षर *bcm47xx_board_get_name(व्योम)
अणु
	वापस bcm47xx_board.name;
पूर्ण
EXPORT_SYMBOL(bcm47xx_board_get_name);
