<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright तऊ 2000-2010 David Woodhouse <dwmw2@infradead.org> et al.
 */

#अगर_अघोषित __MTD_CFI_H__
#घोषणा __MTD_CFI_H__

#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/bug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/flashchip.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/cfi_endian.h>
#समावेश <linux/mtd/xip.h>

#अगर_घोषित CONFIG_MTD_CFI_I1
#घोषणा cfi_पूर्णांकerleave(cfi) 1
#घोषणा cfi_पूर्णांकerleave_is_1(cfi) (cfi_पूर्णांकerleave(cfi) == 1)
#अन्यथा
#घोषणा cfi_पूर्णांकerleave_is_1(cfi) (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MTD_CFI_I2
# अगरdef cfi_पूर्णांकerleave
#  undef cfi_पूर्णांकerleave
#  define cfi_पूर्णांकerleave(cfi) ((cfi)->पूर्णांकerleave)
# अन्यथा
#  define cfi_पूर्णांकerleave(cfi) 2
# endअगर
#घोषणा cfi_पूर्णांकerleave_is_2(cfi) (cfi_पूर्णांकerleave(cfi) == 2)
#अन्यथा
#घोषणा cfi_पूर्णांकerleave_is_2(cfi) (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MTD_CFI_I4
# अगरdef cfi_पूर्णांकerleave
#  undef cfi_पूर्णांकerleave
#  define cfi_पूर्णांकerleave(cfi) ((cfi)->पूर्णांकerleave)
# अन्यथा
#  define cfi_पूर्णांकerleave(cfi) 4
# endअगर
#घोषणा cfi_पूर्णांकerleave_is_4(cfi) (cfi_पूर्णांकerleave(cfi) == 4)
#अन्यथा
#घोषणा cfi_पूर्णांकerleave_is_4(cfi) (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MTD_CFI_I8
# अगरdef cfi_पूर्णांकerleave
#  undef cfi_पूर्णांकerleave
#  define cfi_पूर्णांकerleave(cfi) ((cfi)->पूर्णांकerleave)
# अन्यथा
#  define cfi_पूर्णांकerleave(cfi) 8
# endअगर
#घोषणा cfi_पूर्णांकerleave_is_8(cfi) (cfi_पूर्णांकerleave(cfi) == 8)
#अन्यथा
#घोषणा cfi_पूर्णांकerleave_is_8(cfi) (0)
#पूर्ण_अगर

#अगर_अघोषित cfi_पूर्णांकerleave
#warning No CONFIG_MTD_CFI_Ix selected. No NOR chip support can work.
अटल अंतरभूत पूर्णांक cfi_पूर्णांकerleave(व्योम *cfi)
अणु
	BUG();
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक cfi_पूर्णांकerleave_supported(पूर्णांक i)
अणु
	चयन (i) अणु
#अगर_घोषित CONFIG_MTD_CFI_I1
	हाल 1:
#पूर्ण_अगर
#अगर_घोषित CONFIG_MTD_CFI_I2
	हाल 2:
#पूर्ण_अगर
#अगर_घोषित CONFIG_MTD_CFI_I4
	हाल 4:
#पूर्ण_अगर
#अगर_घोषित CONFIG_MTD_CFI_I8
	हाल 8:
#पूर्ण_अगर
		वापस 1;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण


/* NB: these values must represents the number of bytes needed to meet the
 *     device type (x8, x16, x32).  Eg. a 32 bit device is 4 x 8 bytes.
 *     These numbers are used in calculations.
 */
#घोषणा CFI_DEVICETYPE_X8  (8 / 8)
#घोषणा CFI_DEVICETYPE_X16 (16 / 8)
#घोषणा CFI_DEVICETYPE_X32 (32 / 8)
#घोषणा CFI_DEVICETYPE_X64 (64 / 8)


/* Device Interface Code Assignments from the "Common Flash Memory Interface
 * Publication 100" dated December 1, 2001.
 */
#घोषणा CFI_INTERFACE_X8_ASYNC		0x0000
#घोषणा CFI_INTERFACE_X16_ASYNC		0x0001
#घोषणा CFI_INTERFACE_X8_BY_X16_ASYNC	0x0002
#घोषणा CFI_INTERFACE_X32_ASYNC		0x0003
#घोषणा CFI_INTERFACE_X16_BY_X32_ASYNC	0x0005
#घोषणा CFI_INTERFACE_NOT_ALLOWED	0xffff


/* NB: We keep these काष्ठाures in memory in HOST byteorder, except
 * where inभागidually noted.
 */

/* Basic Query Structure */
काष्ठा cfi_ident अणु
	uपूर्णांक8_t  qry[3];
	uपूर्णांक16_t P_ID;
	uपूर्णांक16_t P_ADR;
	uपूर्णांक16_t A_ID;
	uपूर्णांक16_t A_ADR;
	uपूर्णांक8_t  VccMin;
	uपूर्णांक8_t  VccMax;
	uपूर्णांक8_t  VppMin;
	uपूर्णांक8_t  VppMax;
	uपूर्णांक8_t  WordWriteTimeoutTyp;
	uपूर्णांक8_t  BufWriteTimeoutTyp;
	uपूर्णांक8_t  BlockEraseTimeoutTyp;
	uपूर्णांक8_t  ChipEraseTimeoutTyp;
	uपूर्णांक8_t  WordWriteTimeoutMax;
	uपूर्णांक8_t  BufWriteTimeoutMax;
	uपूर्णांक8_t  BlockEraseTimeoutMax;
	uपूर्णांक8_t  ChipEraseTimeoutMax;
	uपूर्णांक8_t  DevSize;
	uपूर्णांक16_t InterfaceDesc;
	uपूर्णांक16_t MaxBufWriteSize;
	uपूर्णांक8_t  NumEraseRegions;
	uपूर्णांक32_t EraseRegionInfo[]; /* Not host ordered */
पूर्ण __packed;

/* Extended Query Structure क्रम both PRI and ALT */

काष्ठा cfi_extquery अणु
	uपूर्णांक8_t  pri[3];
	uपूर्णांक8_t  MajorVersion;
	uपूर्णांक8_t  MinorVersion;
पूर्ण __packed;

/* Venकरोr-Specअगरic PRI क्रम Intel/Sharp Extended Command Set (0x0001) */

काष्ठा cfi_pri_पूर्णांकelext अणु
	uपूर्णांक8_t  pri[3];
	uपूर्णांक8_t  MajorVersion;
	uपूर्णांक8_t  MinorVersion;
	uपूर्णांक32_t FeatureSupport; /* अगर bit 31 is set then an additional uपूर्णांक32_t feature
				    block follows - FIXME - not currently supported */
	uपूर्णांक8_t  SuspendCmdSupport;
	uपूर्णांक16_t BlkStatusRegMask;
	uपूर्णांक8_t  VccOptimal;
	uपूर्णांक8_t  VppOptimal;
	uपूर्णांक8_t  NumProtectionFields;
	uपूर्णांक16_t ProtRegAddr;
	uपूर्णांक8_t  FactProtRegSize;
	uपूर्णांक8_t  UserProtRegSize;
	uपूर्णांक8_t  extra[];
पूर्ण __packed;

काष्ठा cfi_पूर्णांकelext_otpinfo अणु
	uपूर्णांक32_t ProtRegAddr;
	uपूर्णांक16_t FactGroups;
	uपूर्णांक8_t  FactProtRegSize;
	uपूर्णांक16_t UserGroups;
	uपूर्णांक8_t  UserProtRegSize;
पूर्ण __packed;

काष्ठा cfi_पूर्णांकelext_blockinfo अणु
	uपूर्णांक16_t NumIdentBlocks;
	uपूर्णांक16_t BlockSize;
	uपूर्णांक16_t MinBlockEraseCycles;
	uपूर्णांक8_t  BitsPerCell;
	uपूर्णांक8_t  BlockCap;
पूर्ण __packed;

काष्ठा cfi_पूर्णांकelext_regioninfo अणु
	uपूर्णांक16_t NumIdentPartitions;
	uपूर्णांक8_t  NumOpAllowed;
	uपूर्णांक8_t  NumOpAllowedSimProgMode;
	uपूर्णांक8_t  NumOpAllowedSimEraMode;
	uपूर्णांक8_t  NumBlockTypes;
	काष्ठा cfi_पूर्णांकelext_blockinfo BlockTypes[1];
पूर्ण __packed;

काष्ठा cfi_पूर्णांकelext_programming_regioninfo अणु
	uपूर्णांक8_t  ProgRegShअगरt;
	uपूर्णांक8_t  Reserved1;
	uपूर्णांक8_t  ControlValid;
	uपूर्णांक8_t  Reserved2;
	uपूर्णांक8_t  ControlInvalid;
	uपूर्णांक8_t  Reserved3;
पूर्ण __packed;

/* Venकरोr-Specअगरic PRI क्रम AMD/Fujitsu Extended Command Set (0x0002) */

काष्ठा cfi_pri_amdstd अणु
	uपूर्णांक8_t  pri[3];
	uपूर्णांक8_t  MajorVersion;
	uपूर्णांक8_t  MinorVersion;
	uपूर्णांक8_t  SiliconRevision; /* bits 1-0: Address Sensitive Unlock */
	uपूर्णांक8_t  EraseSuspend;
	uपूर्णांक8_t  BlkProt;
	uपूर्णांक8_t  TmpBlkUnprotect;
	uपूर्णांक8_t  BlkProtUnprot;
	uपूर्णांक8_t  SimultaneousOps;
	uपूर्णांक8_t  BurstMode;
	uपूर्णांक8_t  PageMode;
	uपूर्णांक8_t  VppMin;
	uपूर्णांक8_t  VppMax;
	uपूर्णांक8_t  TopBottom;
	/* Below field are added from version 1.5 */
	uपूर्णांक8_t  ProgramSuspend;
	uपूर्णांक8_t  UnlockBypass;
	uपूर्णांक8_t  SecureSiliconSector;
	uपूर्णांक8_t  SoftwareFeatures;
#घोषणा CFI_POLL_STATUS_REG	BIT(0)
#घोषणा CFI_POLL_DQ		BIT(1)
पूर्ण __packed;

/* Venकरोr-Specअगरic PRI क्रम Aपंचांगel chips (command set 0x0002) */

काष्ठा cfi_pri_aपंचांगel अणु
	uपूर्णांक8_t pri[3];
	uपूर्णांक8_t MajorVersion;
	uपूर्णांक8_t MinorVersion;
	uपूर्णांक8_t Features;
	uपूर्णांक8_t BottomBoot;
	uपूर्णांक8_t BurstMode;
	uपूर्णांक8_t PageMode;
पूर्ण __packed;

काष्ठा cfi_pri_query अणु
	uपूर्णांक8_t  NumFields;
	uपूर्णांक32_t ProtField[1]; /* Not host ordered */
पूर्ण __packed;

काष्ठा cfi_bri_query अणु
	uपूर्णांक8_t  PageModeReadCap;
	uपूर्णांक8_t  NumFields;
	uपूर्णांक32_t ConfField[1]; /* Not host ordered */
पूर्ण __packed;

#घोषणा P_ID_NONE               0x0000
#घोषणा P_ID_INTEL_EXT          0x0001
#घोषणा P_ID_AMD_STD            0x0002
#घोषणा P_ID_INTEL_STD          0x0003
#घोषणा P_ID_AMD_EXT            0x0004
#घोषणा P_ID_WINBOND            0x0006
#घोषणा P_ID_ST_ADV             0x0020
#घोषणा P_ID_MITSUBISHI_STD     0x0100
#घोषणा P_ID_MITSUBISHI_EXT     0x0101
#घोषणा P_ID_SST_PAGE           0x0102
#घोषणा P_ID_SST_OLD            0x0701
#घोषणा P_ID_INTEL_PERFORMANCE  0x0200
#घोषणा P_ID_INTEL_DATA         0x0210
#घोषणा P_ID_RESERVED           0xffff


#घोषणा CFI_MODE_CFI	1
#घोषणा CFI_MODE_JEDEC	0

काष्ठा cfi_निजी अणु
	uपूर्णांक16_t cmdset;
	व्योम *cmdset_priv;
	पूर्णांक पूर्णांकerleave;
	पूर्णांक device_type;
	पूर्णांक cfi_mode;		/* Are we a JEDEC device pretending to be CFI? */
	पूर्णांक addr_unlock1;
	पूर्णांक addr_unlock2;
	काष्ठा mtd_info *(*cmdset_setup)(काष्ठा map_info *);
	काष्ठा cfi_ident *cfiq; /* For now only one. We insist that all devs
				  must be of the same type. */
	पूर्णांक mfr, id;
	पूर्णांक numchips;
	map_word sector_erase_cmd;
	अचिन्हित दीर्घ chipshअगरt; /* Because they're of the same type */
	स्थिर अक्षर *im_name;	 /* पूर्णांकer_module name क्रम cmdset_setup */
	काष्ठा flchip chips[];  /* per-chip data काष्ठाure क्रम each chip */
पूर्ण;

uपूर्णांक32_t cfi_build_cmd_addr(uपूर्णांक32_t cmd_ofs,
				काष्ठा map_info *map, काष्ठा cfi_निजी *cfi);

map_word cfi_build_cmd(u_दीर्घ cmd, काष्ठा map_info *map, काष्ठा cfi_निजी *cfi);
#घोषणा CMD(x)  cfi_build_cmd((x), map, cfi)

अचिन्हित दीर्घ cfi_merge_status(map_word val, काष्ठा map_info *map,
					   काष्ठा cfi_निजी *cfi);
#घोषणा MERGESTATUS(x) cfi_merge_status((x), map, cfi)

uपूर्णांक32_t cfi_send_gen_cmd(u_अक्षर cmd, uपूर्णांक32_t cmd_addr, uपूर्णांक32_t base,
				काष्ठा map_info *map, काष्ठा cfi_निजी *cfi,
				पूर्णांक type, map_word *prev_val);

अटल अंतरभूत uपूर्णांक8_t cfi_पढ़ो_query(काष्ठा map_info *map, uपूर्णांक32_t addr)
अणु
	map_word val = map_पढ़ो(map, addr);

	अगर (map_bankwidth_is_1(map)) अणु
		वापस val.x[0];
	पूर्ण अन्यथा अगर (map_bankwidth_is_2(map)) अणु
		वापस cfi16_to_cpu(map, val.x[0]);
	पूर्ण अन्यथा अणु
		/* No poपूर्णांक in a 64-bit byteswap since that would just be
		   swapping the responses from dअगरferent chips, and we are
		   only पूर्णांकerested in one chip (a representative sample) */
		वापस cfi32_to_cpu(map, val.x[0]);
	पूर्ण
पूर्ण

अटल अंतरभूत uपूर्णांक16_t cfi_पढ़ो_query16(काष्ठा map_info *map, uपूर्णांक32_t addr)
अणु
	map_word val = map_पढ़ो(map, addr);

	अगर (map_bankwidth_is_1(map)) अणु
		वापस val.x[0] & 0xff;
	पूर्ण अन्यथा अगर (map_bankwidth_is_2(map)) अणु
		वापस cfi16_to_cpu(map, val.x[0]);
	पूर्ण अन्यथा अणु
		/* No poपूर्णांक in a 64-bit byteswap since that would just be
		   swapping the responses from dअगरferent chips, and we are
		   only पूर्णांकerested in one chip (a representative sample) */
		वापस cfi32_to_cpu(map, val.x[0]);
	पूर्ण
पूर्ण

व्योम cfi_udelay(पूर्णांक us);

पूर्णांक __xipram cfi_qry_present(काष्ठा map_info *map, __u32 base,
			     काष्ठा cfi_निजी *cfi);
पूर्णांक __xipram cfi_qry_mode_on(uपूर्णांक32_t base, काष्ठा map_info *map,
			     काष्ठा cfi_निजी *cfi);
व्योम __xipram cfi_qry_mode_off(uपूर्णांक32_t base, काष्ठा map_info *map,
			       काष्ठा cfi_निजी *cfi);

काष्ठा cfi_extquery *cfi_पढ़ो_pri(काष्ठा map_info *map, uपूर्णांक16_t adr, uपूर्णांक16_t size,
			     स्थिर अक्षर* name);
काष्ठा cfi_fixup अणु
	uपूर्णांक16_t mfr;
	uपूर्णांक16_t id;
	व्योम (*fixup)(काष्ठा mtd_info *mtd);
पूर्ण;

#घोषणा CFI_MFR_ANY		0xFFFF
#घोषणा CFI_ID_ANY		0xFFFF
#घोषणा CFI_MFR_CONTINUATION	0x007F

#घोषणा CFI_MFR_AMD		0x0001
#घोषणा CFI_MFR_AMIC		0x0037
#घोषणा CFI_MFR_ATMEL		0x001F
#घोषणा CFI_MFR_EON		0x001C
#घोषणा CFI_MFR_FUJITSU		0x0004
#घोषणा CFI_MFR_HYUNDAI		0x00AD
#घोषणा CFI_MFR_INTEL		0x0089
#घोषणा CFI_MFR_MACRONIX	0x00C2
#घोषणा CFI_MFR_NEC		0x0010
#घोषणा CFI_MFR_PMC		0x009D
#घोषणा CFI_MFR_SAMSUNG		0x00EC
#घोषणा CFI_MFR_SHARP		0x00B0
#घोषणा CFI_MFR_SST		0x00BF
#घोषणा CFI_MFR_ST		0x0020 /* STMicroelectronics */
#घोषणा CFI_MFR_MICRON		0x002C /* Micron */
#घोषणा CFI_MFR_TOSHIBA		0x0098
#घोषणा CFI_MFR_WINBOND		0x00DA

व्योम cfi_fixup(काष्ठा mtd_info *mtd, काष्ठा cfi_fixup* fixups);

प्रकार पूर्णांक (*varsize_frob_t)(काष्ठा map_info *map, काष्ठा flchip *chip,
			      अचिन्हित दीर्घ adr, पूर्णांक len, व्योम *thunk);

पूर्णांक cfi_varsize_frob(काष्ठा mtd_info *mtd, varsize_frob_t frob,
	loff_t ofs, माप_प्रकार len, व्योम *thunk);


#पूर्ण_अगर /* __MTD_CFI_H__ */
