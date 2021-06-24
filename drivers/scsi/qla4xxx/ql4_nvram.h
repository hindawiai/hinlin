<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */

#अगर_अघोषित _QL4XNVRM_H_
#घोषणा _QL4XNVRM_H_

/**
 * AM29LV Flash definitions
 **/
#घोषणा FM93C56A_SIZE_8	 0x100
#घोषणा FM93C56A_SIZE_16 0x80
#घोषणा FM93C66A_SIZE_8	 0x200
#घोषणा FM93C66A_SIZE_16 0x100/* 4010 */
#घोषणा FM93C86A_SIZE_16 0x400/* 4022 */

#घोषणा	 FM93C56A_START	      0x1

/* Commands */
#घोषणा	 FM93C56A_READ	      0x2
#घोषणा	 FM93C56A_WEN	      0x0
#घोषणा	 FM93C56A_WRITE	      0x1
#घोषणा	 FM93C56A_WRITE_ALL   0x0
#घोषणा	 FM93C56A_WDS	      0x0
#घोषणा	 FM93C56A_ERASE	      0x3
#घोषणा	 FM93C56A_ERASE_ALL   0x0

/* Command Extensions */
#घोषणा	 FM93C56A_WEN_EXT	 0x3
#घोषणा	 FM93C56A_WRITE_ALL_EXT	 0x1
#घोषणा	 FM93C56A_WDS_EXT	 0x0
#घोषणा	 FM93C56A_ERASE_ALL_EXT	 0x2

/* Address Bits */
#घोषणा	 FM93C56A_NO_ADDR_BITS_16   8	/* 4010 */
#घोषणा	 FM93C56A_NO_ADDR_BITS_8    9	/* 4010 */
#घोषणा	 FM93C86A_NO_ADDR_BITS_16   10	/* 4022 */

/* Data Bits */
#घोषणा	 FM93C56A_DATA_BITS_16	 16
#घोषणा	 FM93C56A_DATA_BITS_8	 8

/* Special Bits */
#घोषणा	 FM93C56A_READ_DUMMY_BITS   1
#घोषणा	 FM93C56A_READY		    0
#घोषणा	 FM93C56A_BUSY		    1
#घोषणा	 FM93C56A_CMD_BITS	    2

/* Auburn Bits */
#घोषणा	 AUBURN_EEPROM_DI	    0x8
#घोषणा	 AUBURN_EEPROM_DI_0	    0x0
#घोषणा	 AUBURN_EEPROM_DI_1	    0x8
#घोषणा	 AUBURN_EEPROM_DO	    0x4
#घोषणा	 AUBURN_EEPROM_DO_0	    0x0
#घोषणा	 AUBURN_EEPROM_DO_1	    0x4
#घोषणा	 AUBURN_EEPROM_CS	    0x2
#घोषणा	 AUBURN_EEPROM_CS_0	    0x0
#घोषणा	 AUBURN_EEPROM_CS_1	    0x2
#घोषणा	 AUBURN_EEPROM_CLK_RISE	    0x1
#घोषणा	 AUBURN_EEPROM_CLK_FALL	    0x0

/**/
/* EEPROM क्रमmat */
/**/
काष्ठा bios_params अणु
	uपूर्णांक16_t SpinUpDelay:1;
	uपूर्णांक16_t BIOSDisable:1;
	uपूर्णांक16_t MMAPEnable:1;
	uपूर्णांक16_t BootEnable:1;
	uपूर्णांक16_t Reserved0:12;
	uपूर्णांक8_t bootID0:7;
	uपूर्णांक8_t bootID0Valid:1;
	uपूर्णांक8_t bootLUN0[8];
	uपूर्णांक8_t bootID1:7;
	uपूर्णांक8_t bootID1Valid:1;
	uपूर्णांक8_t bootLUN1[8];
	uपूर्णांक16_t MaxLunsPerTarget;
	uपूर्णांक8_t Reserved1[10];
पूर्ण;

काष्ठा eeprom_port_cfg अणु

	/* MTU MAC 0 */
	u16 etherMtu_mac;

	/* Flow Control MAC 0 */
	u16 छोड़ोThreshold_mac;
	u16 resumeThreshold_mac;
	u16 reserved[13];
पूर्ण;

काष्ठा eeprom_function_cfg अणु
	u8 reserved[30];

	/* MAC ADDR */
	u8 macAddress[6];
	u8 macAddressSecondary[6];
	u16 subsysVenकरोrId;
	u16 subsysDeviceId;
पूर्ण;

काष्ठा eeprom_data अणु
	जोड़ अणु
		काष्ठा अणु	/* isp4010 */
			u8 asic_id[4]; /* x00 */
			u8 version;	/* x04 */
			u8 reserved;	/* x05 */
			u16 board_id;	/* x06 */
#घोषणा	  EEPROM_BOARDID_ELDORADO    1
#घोषणा	  EEPROM_BOARDID_PLACER	     2

#घोषणा EEPROM_SERIAL_NUM_SIZE	     16
			u8 serial_number[EEPROM_SERIAL_NUM_SIZE]; /* x08 */

			/* ExtHwConfig: */
			/* Offset = 24bytes
			 *
			 * | SSRAM Size|     |ST|PD|SDRAM SZ| W| B| SP	|  |
			 * |15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|
			 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
			 */
			u16 ext_hw_conf; /* x18 */
			u8 mac0[6];	/* x1A */
			u8 mac1[6];	/* x20 */
			u8 mac2[6];	/* x26 */
			u8 mac3[6];	/* x2C */
			u16 etherMtu;	/* x32 */
			u16 macConfig;	/* x34 */
#घोषणा	 MAC_CONFIG_ENABLE_ANEG	    0x0001
#घोषणा	 MAC_CONFIG_ENABLE_PAUSE    0x0002
			u16 phyConfig;	/* x36 */
#घोषणा	 PHY_CONFIG_PHY_ADDR_MASK	      0x1f
#घोषणा	 PHY_CONFIG_ENABLE_FW_MANAGEMENT_MASK 0x20
			u16 reserved_56;	/* x38 */

#घोषणा EEPROM_UNUSED_1_SIZE   2
			u8 unused_1[EEPROM_UNUSED_1_SIZE]; /* x3A */
			u16 bufletSize;	/* x3C */
			u16 bufletCount;	/* x3E */
			u16 bufletPauseThreshold; /* x40 */
			u16 tcpWinकरोwThreshold50; /* x42 */
			u16 tcpWinकरोwThreshold25; /* x44 */
			u16 tcpWinकरोwThreshold0; /* x46 */
			u16 ipHashTableBaseHi;	/* x48 */
			u16 ipHashTableBaseLo;	/* x4A */
			u16 ipHashTableSize;	/* x4C */
			u16 tcpHashTableBaseHi;	/* x4E */
			u16 tcpHashTableBaseLo;	/* x50 */
			u16 tcpHashTableSize;	/* x52 */
			u16 ncbTableBaseHi;	/* x54 */
			u16 ncbTableBaseLo;	/* x56 */
			u16 ncbTableSize;	/* x58 */
			u16 drbTableBaseHi;	/* x5A */
			u16 drbTableBaseLo;	/* x5C */
			u16 drbTableSize;	/* x5E */

#घोषणा EEPROM_UNUSED_2_SIZE   4
			u8 unused_2[EEPROM_UNUSED_2_SIZE]; /* x60 */
			u16 ipReassemblyTimeout; /* x64 */
			u16 tcpMaxWinकरोwSizeHi;	/* x66 */
			u16 tcpMaxWinकरोwSizeLo;	/* x68 */
			u32 net_ip_addr0;	/* x6A Added क्रम TOE
						 * functionality. */
			u32 net_ip_addr1;	/* x6E */
			u32 scsi_ip_addr0;	/* x72 */
			u32 scsi_ip_addr1;	/* x76 */
#घोषणा EEPROM_UNUSED_3_SIZE   128	/* changed from 144 to account
					 * क्रम ip addresses */
			u8 unused_3[EEPROM_UNUSED_3_SIZE]; /* x7A */
			u16 subsysVenकरोrId_f0;	/* xFA */
			u16 subsysDeviceId_f0;	/* xFC */

			/* Address = 0x7F */
#घोषणा FM93C56A_SIGNATURE  0x9356
#घोषणा FM93C66A_SIGNATURE  0x9366
			u16 signature;	/* xFE */

#घोषणा EEPROM_UNUSED_4_SIZE   250
			u8 unused_4[EEPROM_UNUSED_4_SIZE]; /* x100 */
			u16 subsysVenकरोrId_f1;	/* x1FA */
			u16 subsysDeviceId_f1;	/* x1FC */
			u16 checksum;	/* x1FE */
		पूर्ण __attribute__ ((packed)) isp4010;
		काष्ठा अणु	/* isp4022 */
			u8 asicId[4];	/* x00 */
			u8 version;	/* x04 */
			u8 reserved_5;	/* x05 */
			u16 boardId;	/* x06 */
			u8 boardIdStr[16];	/* x08 */
			u8 serialNumber[16];	/* x18 */

			/* External Hardware Configuration */
			u16 ext_hw_conf;	/* x28 */

			/* MAC 0 CONFIGURATION */
			काष्ठा eeprom_port_cfg macCfg_port0; /* x2A */

			/* MAC 1 CONFIGURATION */
			काष्ठा eeprom_port_cfg macCfg_port1; /* x4A */

			/* DDR SDRAM Configuration */
			u16 bufletSize;	/* x6A */
			u16 bufletCount;	/* x6C */
			u16 tcpWinकरोwThreshold50; /* x6E */
			u16 tcpWinकरोwThreshold25; /* x70 */
			u16 tcpWinकरोwThreshold0; /* x72 */
			u16 ipHashTableBaseHi;	/* x74 */
			u16 ipHashTableBaseLo;	/* x76 */
			u16 ipHashTableSize;	/* x78 */
			u16 tcpHashTableBaseHi;	/* x7A */
			u16 tcpHashTableBaseLo;	/* x7C */
			u16 tcpHashTableSize;	/* x7E */
			u16 ncbTableBaseHi;	/* x80 */
			u16 ncbTableBaseLo;	/* x82 */
			u16 ncbTableSize;	/* x84 */
			u16 drbTableBaseHi;	/* x86 */
			u16 drbTableBaseLo;	/* x88 */
			u16 drbTableSize;	/* x8A */
			u16 reserved_142[4];	/* x8C */

			/* TCP/IP Parameters */
			u16 ipReassemblyTimeout; /* x94 */
			u16 tcpMaxWinकरोwSize;	/* x96 */
			u16 ipSecurity;	/* x98 */
			u8 reserved_156[294]; /* x9A */
			u16 qDebug[8];	/* QLOGIC USE ONLY   x1C0 */
			काष्ठा eeprom_function_cfg funcCfg_fn0;	/* x1D0 */
			u16 reserved_510; /* x1FE */

			/* Address = 512 */
			u8 oemSpace[432]; /* x200 */
			काष्ठा bios_params sBIOSParams_fn1; /* x3B0 */
			काष्ठा eeprom_function_cfg funcCfg_fn1;	/* x3D0 */
			u16 reserved_1022; /* x3FE */

			/* Address = 1024 */
			u8 reserved_1024[464];	/* x400 */
			काष्ठा eeprom_function_cfg funcCfg_fn2;	/* x5D0 */
			u16 reserved_1534; /* x5FE */

			/* Address = 1536 */
			u8 reserved_1536[432];	/* x600 */
			काष्ठा bios_params sBIOSParams_fn3; /* x7B0 */
			काष्ठा eeprom_function_cfg funcCfg_fn3;	/* x7D0 */
			u16 checksum;	/* x7FE */
		पूर्ण __attribute__ ((packed)) isp4022;
	पूर्ण;
पूर्ण;


#पूर्ण_अगर	/* _QL4XNVRM_H_ */
