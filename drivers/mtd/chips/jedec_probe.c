<शैली गुरु>
/*
   Common Flash Interface probe code.
   (C) 2000 Red Hat. GPL'd.
   See JEDEC (http://www.jedec.org/) standard JESD21C (section 3.5)
   क्रम the standard this probe goes back to.

   Occasionally मुख्यtained by Thayne Harbaugh tharbaugh at lnxi करोt com
*/

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/mtd/gen_probe.h>

/* AMD */
#घोषणा AM29DL800BB	0x22CB
#घोषणा AM29DL800BT	0x224A

#घोषणा AM29F800BB	0x2258
#घोषणा AM29F800BT	0x22D6
#घोषणा AM29LV400BB	0x22BA
#घोषणा AM29LV400BT	0x22B9
#घोषणा AM29LV800BB	0x225B
#घोषणा AM29LV800BT	0x22DA
#घोषणा AM29LV160DT	0x22C4
#घोषणा AM29LV160DB	0x2249
#घोषणा AM29F017D	0x003D
#घोषणा AM29F016D	0x00AD
#घोषणा AM29F080	0x00D5
#घोषणा AM29F040	0x00A4
#घोषणा AM29LV040B	0x004F
#घोषणा AM29F032B	0x0041
#घोषणा AM29F002T	0x00B0
#घोषणा AM29SL800DB	0x226B
#घोषणा AM29SL800DT	0x22EA

/* Aपंचांगel */
#घोषणा AT49BV512	0x0003
#घोषणा AT29LV512	0x003d
#घोषणा AT49BV16X	0x00C0
#घोषणा AT49BV16XT	0x00C2
#घोषणा AT49BV32X	0x00C8
#घोषणा AT49BV32XT	0x00C9

/* Eon */
#घोषणा EN29LV400AT	0x22B9
#घोषणा EN29LV400AB	0x22BA
#घोषणा EN29SL800BB	0x226B
#घोषणा EN29SL800BT	0x22EA

/* Fujitsu */
#घोषणा MBM29F040C	0x00A4
#घोषणा MBM29F800BA	0x2258
#घोषणा MBM29LV650UE	0x22D7
#घोषणा MBM29LV320TE	0x22F6
#घोषणा MBM29LV320BE	0x22F9
#घोषणा MBM29LV160TE	0x22C4
#घोषणा MBM29LV160BE	0x2249
#घोषणा MBM29LV800BA	0x225B
#घोषणा MBM29LV800TA	0x22DA
#घोषणा MBM29LV400TC	0x22B9
#घोषणा MBM29LV400BC	0x22BA

/* Hyundai */
#घोषणा HY29F002T	0x00B0

/* Intel */
#घोषणा I28F004B3T	0x00d4
#घोषणा I28F004B3B	0x00d5
#घोषणा I28F400B3T	0x8894
#घोषणा I28F400B3B	0x8895
#घोषणा I28F008S5	0x00a6
#घोषणा I28F016S5	0x00a0
#घोषणा I28F008SA	0x00a2
#घोषणा I28F008B3T	0x00d2
#घोषणा I28F008B3B	0x00d3
#घोषणा I28F800B3T	0x8892
#घोषणा I28F800B3B	0x8893
#घोषणा I28F016S3	0x00aa
#घोषणा I28F016B3T	0x00d0
#घोषणा I28F016B3B	0x00d1
#घोषणा I28F160B3T	0x8890
#घोषणा I28F160B3B	0x8891
#घोषणा I28F320B3T	0x8896
#घोषणा I28F320B3B	0x8897
#घोषणा I28F640B3T	0x8898
#घोषणा I28F640B3B	0x8899
#घोषणा I28F640C3B	0x88CD
#घोषणा I28F160F3T	0x88F3
#घोषणा I28F160F3B	0x88F4
#घोषणा I28F160C3T	0x88C2
#घोषणा I28F160C3B	0x88C3
#घोषणा I82802AB	0x00ad
#घोषणा I82802AC	0x00ac

/* Macronix */
#घोषणा MX29LV040C	0x004F
#घोषणा MX29LV160T	0x22C4
#घोषणा MX29LV160B	0x2249
#घोषणा MX29F040	0x00A4
#घोषणा MX29F016	0x00AD
#घोषणा MX29F002T	0x00B0
#घोषणा MX29F004T	0x0045
#घोषणा MX29F004B	0x0046

/* NEC */
#घोषणा UPD29F064115	0x221C

/* PMC */
#घोषणा PM49FL002	0x006D
#घोषणा PM49FL004	0x006E
#घोषणा PM49FL008	0x006A

/* Sharp */
#घोषणा LH28F640BF	0x00B0

/* ST - www.st.com */
#घोषणा M29F800AB	0x0058
#घोषणा M29W800DT	0x22D7
#घोषणा M29W800DB	0x225B
#घोषणा M29W400DT	0x00EE
#घोषणा M29W400DB	0x00EF
#घोषणा M29W160DT	0x22C4
#घोषणा M29W160DB	0x2249
#घोषणा M29W040B	0x00E3
#घोषणा M50FW040	0x002C
#घोषणा M50FW080	0x002D
#घोषणा M50FW016	0x002E
#घोषणा M50LPW080       0x002F
#घोषणा M50FLW080A	0x0080
#घोषणा M50FLW080B	0x0081
#घोषणा PSD4256G6V	0x00e9

/* SST */
#घोषणा SST29EE020	0x0010
#घोषणा SST29LE020	0x0012
#घोषणा SST29EE512	0x005d
#घोषणा SST29LE512	0x003d
#घोषणा SST39LF800	0x2781
#घोषणा SST39LF160	0x2782
#घोषणा SST39VF1601	0x234b
#घोषणा SST39VF3201	0x235b
#घोषणा SST39WF1601	0x274b
#घोषणा SST39WF1602	0x274a
#घोषणा SST39LF512	0x00D4
#घोषणा SST39LF010	0x00D5
#घोषणा SST39LF020	0x00D6
#घोषणा SST39LF040	0x00D7
#घोषणा SST39SF010A	0x00B5
#घोषणा SST39SF020A	0x00B6
#घोषणा SST39SF040	0x00B7
#घोषणा SST49LF004B	0x0060
#घोषणा SST49LF040B	0x0050
#घोषणा SST49LF008A	0x005a
#घोषणा SST49LF030A	0x001C
#घोषणा SST49LF040A	0x0051
#घोषणा SST49LF080A	0x005B
#घोषणा SST36VF3203	0x7354

/* Toshiba */
#घोषणा TC58FVT160	0x00C2
#घोषणा TC58FVB160	0x0043
#घोषणा TC58FVT321	0x009A
#घोषणा TC58FVB321	0x009C
#घोषणा TC58FVT641	0x0093
#घोषणा TC58FVB641	0x0095

/* Winbond */
#घोषणा W49V002A	0x00b0


/*
 * Unlock address sets क्रम AMD command sets.
 * Intel command sets use the MTD_UADDR_UNNECESSARY.
 * Each identअगरier, except MTD_UADDR_UNNECESSARY, and
 * MTD_UADDR_NO_SUPPORT must be defined below in unlock_addrs[].
 * MTD_UADDR_NOT_SUPPORTED must be 0 so that काष्ठाure
 * initialization need not require initializing all of the
 * unlock addresses क्रम all bit widths.
 */
क्रमागत uaddr अणु
	MTD_UADDR_NOT_SUPPORTED = 0,	/* data width not supported */
	MTD_UADDR_0x0555_0x02AA,
	MTD_UADDR_0x0555_0x0AAA,
	MTD_UADDR_0x5555_0x2AAA,
	MTD_UADDR_0x0AAA_0x0554,
	MTD_UADDR_0x0AAA_0x0555,
	MTD_UADDR_0xAAAA_0x5555,
	MTD_UADDR_DONT_CARE,		/* Requires an arbitrary address */
	MTD_UADDR_UNNECESSARY,		/* Does not require any address */
पूर्ण;


काष्ठा unlock_addr अणु
	uपूर्णांक32_t addr1;
	uपूर्णांक32_t addr2;
पूर्ण;


/*
 * I करोn't like the fact that the first entry in unlock_addrs[]
 * exists, but is क्रम MTD_UADDR_NOT_SUPPORTED - and, thereक्रमe,
 * should not be used.  The  problem is that काष्ठाures with
 * initializers have extra fields initialized to 0.  It is _very_
 * desirable to have the unlock address entries क्रम unsupported
 * data widths स्वतःmatically initialized - that means that
 * MTD_UADDR_NOT_SUPPORTED must be 0 and the first entry here
 * must go unused.
 */
अटल स्थिर काष्ठा unlock_addr  unlock_addrs[] = अणु
	[MTD_UADDR_NOT_SUPPORTED] = अणु
		.addr1 = 0xffff,
		.addr2 = 0xffff
	पूर्ण,

	[MTD_UADDR_0x0555_0x02AA] = अणु
		.addr1 = 0x0555,
		.addr2 = 0x02aa
	पूर्ण,

	[MTD_UADDR_0x0555_0x0AAA] = अणु
		.addr1 = 0x0555,
		.addr2 = 0x0aaa
	पूर्ण,

	[MTD_UADDR_0x5555_0x2AAA] = अणु
		.addr1 = 0x5555,
		.addr2 = 0x2aaa
	पूर्ण,

	[MTD_UADDR_0x0AAA_0x0554] = अणु
		.addr1 = 0x0AAA,
		.addr2 = 0x0554
	पूर्ण,

	[MTD_UADDR_0x0AAA_0x0555] = अणु
		.addr1 = 0x0AAA,
		.addr2 = 0x0555
	पूर्ण,

	[MTD_UADDR_0xAAAA_0x5555] = अणु
		.addr1 = 0xaaaa,
		.addr2 = 0x5555
	पूर्ण,

	[MTD_UADDR_DONT_CARE] = अणु
		.addr1 = 0x0000,      /* Doesn't matter which address */
		.addr2 = 0x0000       /* is used - must be last entry */
	पूर्ण,

	[MTD_UADDR_UNNECESSARY] = अणु
		.addr1 = 0x0000,
		.addr2 = 0x0000
	पूर्ण
पूर्ण;

काष्ठा amd_flash_info अणु
	स्थिर अक्षर *name;
	स्थिर uपूर्णांक16_t mfr_id;
	स्थिर uपूर्णांक16_t dev_id;
	स्थिर uपूर्णांक8_t dev_size;
	स्थिर uपूर्णांक8_t nr_regions;
	स्थिर uपूर्णांक16_t cmd_set;
	स्थिर uपूर्णांक32_t regions[6];
	स्थिर uपूर्णांक8_t devtypes;		/* Biपंचांगask क्रम x8, x16 etc. */
	स्थिर uपूर्णांक8_t uaddr;		/* unlock addrs क्रम 8, 16, 32, 64 */
पूर्ण;

#घोषणा ERASEINFO(size,blocks) (size<<8)|(blocks-1)

#घोषणा SIZE_64KiB  16
#घोषणा SIZE_128KiB 17
#घोषणा SIZE_256KiB 18
#घोषणा SIZE_512KiB 19
#घोषणा SIZE_1MiB   20
#घोषणा SIZE_2MiB   21
#घोषणा SIZE_4MiB   22
#घोषणा SIZE_8MiB   23


/*
 * Please keep this list ordered by manufacturer!
 * Fortunately, the list isn't searched often and so a
 * slow, linear search isn't so bad.
 */
अटल स्थिर काष्ठा amd_flash_info jedec_table[] = अणु
	अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29F032B,
		.name		= "AMD AM29F032B",
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.devtypes	= CFI_DEVICETYPE_X8,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,64)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29LV160DT,
		.name		= "AMD AM29LV160DT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,31),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29LV160DB,
		.name		= "AMD AM29LV160DB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,31)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29LV400BB,
		.name		= "AMD AM29LV400BB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,7)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29LV400BT,
		.name		= "AMD AM29LV400BT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,7),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29LV800BB,
		.name		= "AMD AM29LV800BB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,15),
		पूर्ण
	पूर्ण, अणु
/* add DL */
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29DL800BB,
		.name		= "AMD AM29DL800BB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 6,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,4),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x04000,1),
			ERASEINFO(0x10000,14)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29DL800BT,
		.name		= "AMD AM29DL800BT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 6,
		.regions	= अणु
			ERASEINFO(0x10000,14),
			ERASEINFO(0x04000,1),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,4),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29F800BB,
		.name		= "AMD AM29F800BB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,15),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29LV800BT,
		.name		= "AMD AM29LV800BT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,15),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29F800BT,
		.name		= "AMD AM29F800BT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,15),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29F017D,
		.name		= "AMD AM29F017D",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_DONT_CARE,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,32),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29F016D,
		.name		= "AMD AM29F016D",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,32),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29F080,
		.name		= "AMD AM29F080",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,16),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29F040,
		.name		= "AMD AM29F040",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29LV040B,
		.name		= "AMD AM29LV040B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29F002T,
		.name		= "AMD AM29F002T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,3),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29SL800DT,
		.name		= "AMD AM29SL800DT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,15),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_AMD,
		.dev_id		= AM29SL800DB,
		.name		= "AMD AM29SL800DB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,15),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ATMEL,
		.dev_id		= AT49BV512,
		.name		= "Atmel AT49BV512",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_64KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ATMEL,
		.dev_id		= AT29LV512,
		.name		= "Atmel AT29LV512",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_64KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x80,256),
			ERASEINFO(0x80,256)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ATMEL,
		.dev_id		= AT49BV16X,
		.name		= "Atmel AT49BV16X",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x0AAA,	/* ???? */
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000,8),
			ERASEINFO(0x10000,31)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ATMEL,
		.dev_id		= AT49BV16XT,
		.name		= "Atmel AT49BV16XT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x0AAA,	/* ???? */
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000,31),
			ERASEINFO(0x02000,8)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ATMEL,
		.dev_id		= AT49BV32X,
		.name		= "Atmel AT49BV32X",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x0AAA,	/* ???? */
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000,8),
			ERASEINFO(0x10000,63)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ATMEL,
		.dev_id		= AT49BV32XT,
		.name		= "Atmel AT49BV32XT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x0AAA,	/* ???? */
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000,63),
			ERASEINFO(0x02000,8)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_EON,
		.dev_id		= EN29LV400AT,
		.name		= "Eon EN29LV400AT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,7),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_EON,
		.dev_id		= EN29LV400AB,
		.name		= "Eon EN29LV400AB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,7),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_EON,
		.dev_id		= EN29SL800BT,
		.name		= "Eon EN29SL800BT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,15),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_EON,
		.dev_id		= EN29SL800BB,
		.name		= "Eon EN29SL800BB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,15),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_FUJITSU,
		.dev_id		= MBM29F040C,
		.name		= "Fujitsu MBM29F040C",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,8)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_FUJITSU,
		.dev_id		= MBM29F800BA,
		.name		= "Fujitsu MBM29F800BA",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,15),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_FUJITSU,
		.dev_id		= MBM29LV650UE,
		.name		= "Fujitsu MBM29LV650UE",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_DONT_CARE,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,128)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_FUJITSU,
		.dev_id		= MBM29LV320TE,
		.name		= "Fujitsu MBM29LV320TE",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000,63),
			ERASEINFO(0x02000,8)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_FUJITSU,
		.dev_id		= MBM29LV320BE,
		.name		= "Fujitsu MBM29LV320BE",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000,8),
			ERASEINFO(0x10000,63)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_FUJITSU,
		.dev_id		= MBM29LV160TE,
		.name		= "Fujitsu MBM29LV160TE",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,31),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_FUJITSU,
		.dev_id		= MBM29LV160BE,
		.name		= "Fujitsu MBM29LV160BE",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,31)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_FUJITSU,
		.dev_id		= MBM29LV800BA,
		.name		= "Fujitsu MBM29LV800BA",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,15)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_FUJITSU,
		.dev_id		= MBM29LV800TA,
		.name		= "Fujitsu MBM29LV800TA",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,15),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_FUJITSU,
		.dev_id		= MBM29LV400BC,
		.name		= "Fujitsu MBM29LV400BC",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,7)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_FUJITSU,
		.dev_id		= MBM29LV400TC,
		.name		= "Fujitsu MBM29LV400TC",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,7),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_HYUNDAI,
		.dev_id		= HY29F002T,
		.name		= "Hyundai HY29F002T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,3),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F004B3B,
		.name		= "Intel 28F004B3B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000, 8),
			ERASEINFO(0x10000, 7),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F004B3T,
		.name		= "Intel 28F004B3T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000, 7),
			ERASEINFO(0x02000, 8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F400B3B,
		.name		= "Intel 28F400B3B",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000, 8),
			ERASEINFO(0x10000, 7),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F400B3T,
		.name		= "Intel 28F400B3T",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000, 7),
			ERASEINFO(0x02000, 8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F008B3B,
		.name		= "Intel 28F008B3B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000, 8),
			ERASEINFO(0x10000, 15),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F008B3T,
		.name		= "Intel 28F008B3T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000, 15),
			ERASEINFO(0x02000, 8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F008S5,
		.name		= "Intel 28F008S5",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEL_EXT,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,16),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F016S5,
		.name		= "Intel 28F016S5",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEL_EXT,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,32),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F008SA,
		.name		= "Intel 28F008SA",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000, 16),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F800B3B,
		.name		= "Intel 28F800B3B",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000, 8),
			ERASEINFO(0x10000, 15),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F800B3T,
		.name		= "Intel 28F800B3T",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000, 15),
			ERASEINFO(0x02000, 8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F016B3B,
		.name		= "Intel 28F016B3B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000, 8),
			ERASEINFO(0x10000, 31),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F016S3,
		.name		= "Intel I28F016S3",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000, 32),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F016B3T,
		.name		= "Intel 28F016B3T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000, 31),
			ERASEINFO(0x02000, 8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F160B3B,
		.name		= "Intel 28F160B3B",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000, 8),
			ERASEINFO(0x10000, 31),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F160B3T,
		.name		= "Intel 28F160B3T",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000, 31),
			ERASEINFO(0x02000, 8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F320B3B,
		.name		= "Intel 28F320B3B",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000, 8),
			ERASEINFO(0x10000, 63),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F320B3T,
		.name		= "Intel 28F320B3T",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000, 63),
			ERASEINFO(0x02000, 8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F640B3B,
		.name		= "Intel 28F640B3B",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000, 8),
			ERASEINFO(0x10000, 127),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F640B3T,
		.name		= "Intel 28F640B3T",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000, 127),
			ERASEINFO(0x02000, 8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I28F640C3B,
		.name		= "Intel 28F640C3B",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_INTEL_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000, 8),
			ERASEINFO(0x10000, 127),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I82802AB,
		.name		= "Intel 82802AB",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEL_EXT,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_INTEL,
		.dev_id		= I82802AC,
		.name		= "Intel 82802AC",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEL_EXT,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,16),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_MACRONIX,
		.dev_id		= MX29LV040C,
		.name		= "Macronix MX29LV040C",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_MACRONIX,
		.dev_id		= MX29LV160T,
		.name		= "MXIC MX29LV160T",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,31),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_NEC,
		.dev_id		= UPD29F064115,
		.name		= "NEC uPD29F064115",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_0xAAAA_0x5555,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 3,
		.regions	= अणु
			ERASEINFO(0x2000,8),
			ERASEINFO(0x10000,126),
			ERASEINFO(0x2000,8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_MACRONIX,
		.dev_id		= MX29LV160B,
		.name		= "MXIC MX29LV160B",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,31)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_MACRONIX,
		.dev_id		= MX29F040,
		.name		= "Macronix MX29F040",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_MACRONIX,
		.dev_id		= MX29F016,
		.name		= "Macronix MX29F016",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,32),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_MACRONIX,
		.dev_id		= MX29F004T,
		.name		= "Macronix MX29F004T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,7),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_MACRONIX,
		.dev_id		= MX29F004B,
		.name		= "Macronix MX29F004B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,7),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_MACRONIX,
		.dev_id		= MX29F002T,
		.name		= "Macronix MX29F002T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,3),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_PMC,
		.dev_id		= PM49FL002,
		.name		= "PMC Pm49FL002",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO( 0x01000, 64 )
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_PMC,
		.dev_id		= PM49FL004,
		.name		= "PMC Pm49FL004",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO( 0x01000, 128 )
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_PMC,
		.dev_id		= PM49FL008,
		.name		= "PMC Pm49FL008",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO( 0x01000, 256 )
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SHARP,
		.dev_id		= LH28F640BF,
		.name		= "LH28F640BF",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_INTEL_EXT,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000, 127),
			ERASEINFO(0x02000, 8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST39LF512,
		.name		= "SST 39LF512",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_64KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,16),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST39LF010,
		.name		= "SST 39LF010",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_128KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,32),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST29EE020,
		.name		= "SST 29EE020",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_SST_PAGE,
		.nr_regions	= 1,
		.regions = अणुERASEINFO(0x01000,64),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST29LE020,
		.name		= "SST 29LE020",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_SST_PAGE,
		.nr_regions	= 1,
		.regions = अणुERASEINFO(0x01000,64),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST39LF020,
		.name		= "SST 39LF020",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,64),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST39LF040,
		.name		= "SST 39LF040",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,128),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST39SF010A,
		.name		= "SST 39SF010A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_128KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,32),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST39SF020A,
		.name		= "SST 39SF020A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,64),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST39SF040,
		.name		= "SST 39SF040",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,128),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST49LF040B,
		.name		= "SST 49LF040B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,128),
		पूर्ण
	पूर्ण, अणु

		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST49LF004B,
		.name		= "SST 49LF004B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,128),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST49LF008A,
		.name		= "SST 49LF008A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,256),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST49LF030A,
		.name		= "SST 49LF030A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,96),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST49LF040A,
		.name		= "SST 49LF040A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,128),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST49LF080A,
		.name		= "SST 49LF080A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x01000,256),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,     /* should be CFI */
		.dev_id		= SST39LF160,
		.name		= "SST 39LF160",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_0xAAAA_0x5555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x1000,256),
			ERASEINFO(0x1000,256)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,     /* should be CFI */
		.dev_id		= SST39VF1601,
		.name		= "SST 39VF1601",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_0xAAAA_0x5555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x1000,256),
			ERASEINFO(0x1000,256)
		पूर्ण
	पूर्ण, अणु
		/* CFI is broken: reports AMD_STD, but needs custom uaddr */
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST39WF1601,
		.name		= "SST 39WF1601",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_0xAAAA_0x5555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x1000,256),
			ERASEINFO(0x1000,256)
		पूर्ण
	पूर्ण, अणु
		/* CFI is broken: reports AMD_STD, but needs custom uaddr */
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST39WF1602,
		.name		= "SST 39WF1602",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_0xAAAA_0x5555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x1000,256),
			ERASEINFO(0x1000,256)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,     /* should be CFI */
		.dev_id		= SST39VF3201,
		.name		= "SST 39VF3201",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_0xAAAA_0x5555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x1000,256),
			ERASEINFO(0x1000,256),
			ERASEINFO(0x1000,256),
			ERASEINFO(0x1000,256)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_SST,
		.dev_id		= SST36VF3203,
		.name		= "SST 36VF3203",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,64),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,
		.dev_id		= M29F800AB,
		.name		= "ST M29F800AB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,15),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,	/* FIXME - CFI device? */
		.dev_id		= M29W800DT,
		.name		= "ST M29W800DT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,15),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,	/* FIXME - CFI device? */
		.dev_id		= M29W800DB,
		.name		= "ST M29W800DB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,15)
		पूर्ण
	पूर्ण,  अणु
		.mfr_id         = CFI_MFR_ST,
		.dev_id         = M29W400DT,
		.name           = "ST M29W400DT",
		.devtypes       = CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr          = MTD_UADDR_0x0AAA_0x0555,
		.dev_size       = SIZE_512KiB,
		.cmd_set        = P_ID_AMD_STD,
		.nr_regions     = 4,
		.regions        = अणु
			ERASEINFO(0x04000,7),
			ERASEINFO(0x02000,1),
			ERASEINFO(0x08000,2),
			ERASEINFO(0x10000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id         = CFI_MFR_ST,
		.dev_id         = M29W400DB,
		.name           = "ST M29W400DB",
		.devtypes       = CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr          = MTD_UADDR_0x0AAA_0x0555,
		.dev_size       = SIZE_512KiB,
		.cmd_set        = P_ID_AMD_STD,
		.nr_regions     = 4,
		.regions        = अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,7)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,	/* FIXME - CFI device? */
		.dev_id		= M29W160DT,
		.name		= "ST M29W160DT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,	/* ???? */
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,31),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,	/* FIXME - CFI device? */
		.dev_id		= M29W160DB,
		.name		= "ST M29W160DB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,	/* ???? */
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,31)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,
		.dev_id		= M29W040B,
		.name		= "ST M29W040B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,
		.dev_id		= M50FW040,
		.name		= "ST M50FW040",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEL_EXT,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,8),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,
		.dev_id		= M50FW080,
		.name		= "ST M50FW080",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEL_EXT,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,16),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,
		.dev_id		= M50FW016,
		.name		= "ST M50FW016",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEL_EXT,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,32),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,
		.dev_id		= M50LPW080,
		.name		= "ST M50LPW080",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEL_EXT,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,16),
		पूर्ण,
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,
		.dev_id		= M50FLW080A,
		.name		= "ST M50FLW080A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEL_EXT,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x1000,16),
			ERASEINFO(0x10000,13),
			ERASEINFO(0x1000,16),
			ERASEINFO(0x1000,16),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_ST,
		.dev_id		= M50FLW080B,
		.name		= "ST M50FLW080B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_UNNECESSARY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEL_EXT,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x1000,16),
			ERASEINFO(0x1000,16),
			ERASEINFO(0x10000,13),
			ERASEINFO(0x1000,16),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= 0xff00 | CFI_MFR_ST,
		.dev_id		= 0xff00 | PSD4256G6V,
		.name		= "ST PSD4256G6V",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddr		= MTD_UADDR_0x0AAA_0x0554,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 1,
		.regions	= अणु
			ERASEINFO(0x10000,16),
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_TOSHIBA,
		.dev_id		= TC58FVT160,
		.name		= "Toshiba TC58FVT160",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000,31),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x04000,1)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_TOSHIBA,
		.dev_id		= TC58FVB160,
		.name		= "Toshiba TC58FVB160",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x04000,1),
			ERASEINFO(0x02000,2),
			ERASEINFO(0x08000,1),
			ERASEINFO(0x10000,31)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_TOSHIBA,
		.dev_id		= TC58FVB321,
		.name		= "Toshiba TC58FVB321",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000,8),
			ERASEINFO(0x10000,63)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_TOSHIBA,
		.dev_id		= TC58FVT321,
		.name		= "Toshiba TC58FVT321",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000,63),
			ERASEINFO(0x02000,8)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_TOSHIBA,
		.dev_id		= TC58FVB641,
		.name		= "Toshiba TC58FVB641",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x02000,8),
			ERASEINFO(0x10000,127)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_TOSHIBA,
		.dev_id		= TC58FVT641,
		.name		= "Toshiba TC58FVT641",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x0AAA_0x0555,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 2,
		.regions	= अणु
			ERASEINFO(0x10000,127),
			ERASEINFO(0x02000,8)
		पूर्ण
	पूर्ण, अणु
		.mfr_id		= CFI_MFR_WINBOND,
		.dev_id		= W49V002A,
		.name		= "Winbond W49V002A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddr		= MTD_UADDR_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nr_regions	= 4,
		.regions	= अणु
			ERASEINFO(0x10000, 3),
			ERASEINFO(0x08000, 1),
			ERASEINFO(0x02000, 2),
			ERASEINFO(0x04000, 1),
		पूर्ण
	पूर्ण
पूर्ण;

अटल अंतरभूत u32 jedec_पढ़ो_mfr(काष्ठा map_info *map, uपूर्णांक32_t base,
	काष्ठा cfi_निजी *cfi)
अणु
	map_word result;
	अचिन्हित दीर्घ mask;
	पूर्णांक bank = 0;

	/* According to JEDEC "Standard Manufacturer's Identification Code"
	 * (http://www.jedec.org/करोwnload/search/jep106W.pdf)
	 * several first banks can contain 0x7f instead of actual ID
	 */
	करो अणु
		uपूर्णांक32_t ofs = cfi_build_cmd_addr(0 + (bank << 8), map, cfi);
		mask = (1 << (cfi->device_type * 8)) - 1;
		अगर (ofs >= map->size)
			वापस 0;
		result = map_पढ़ो(map, base + ofs);
		bank++;
	पूर्ण जबतक ((result.x[0] & mask) == CFI_MFR_CONTINUATION);

	वापस result.x[0] & mask;
पूर्ण

अटल अंतरभूत u32 jedec_पढ़ो_id(काष्ठा map_info *map, uपूर्णांक32_t base,
	काष्ठा cfi_निजी *cfi)
अणु
	map_word result;
	अचिन्हित दीर्घ mask;
	u32 ofs = cfi_build_cmd_addr(1, map, cfi);
	mask = (1 << (cfi->device_type * 8)) -1;
	result = map_पढ़ो(map, base + ofs);
	वापस result.x[0] & mask;
पूर्ण

अटल व्योम jedec_reset(u32 base, काष्ठा map_info *map, काष्ठा cfi_निजी *cfi)
अणु
	/* Reset */

	/* after checking the datasheets क्रम SST, MACRONIX and ATMEL
	 * (oh and incidentaly the jedec spec - 3.5.3.3) the reset
	 * sequence is *supposed* to be 0xaa at 0x5555, 0x55 at
	 * 0x2aaa, 0xF0 at 0x5555 this will not affect the AMD chips
	 * as they will ignore the ग_लिखोs and करोn't care what address
	 * the F0 is written to */
	अगर (cfi->addr_unlock1) अणु
		pr_debug( "reset unlock called %x %x \n",
		       cfi->addr_unlock1,cfi->addr_unlock2);
		cfi_send_gen_cmd(0xaa, cfi->addr_unlock1, base, map, cfi, cfi->device_type, शून्य);
		cfi_send_gen_cmd(0x55, cfi->addr_unlock2, base, map, cfi, cfi->device_type, शून्य);
	पूर्ण

	cfi_send_gen_cmd(0xF0, cfi->addr_unlock1, base, map, cfi, cfi->device_type, शून्य);
	/* Some misdeचिन्हित Intel chips करो not respond क्रम 0xF0 क्रम a reset,
	 * so ensure we're in पढ़ो mode.  Send both the Intel and the AMD command
	 * क्रम this.  Intel uses 0xff क्रम this, AMD uses 0xff क्रम NOP, so
	 * this should be safe.
	 */
	cfi_send_gen_cmd(0xFF, 0, base, map, cfi, cfi->device_type, शून्य);
	/* FIXME - should have reset delay beक्रमe continuing */
पूर्ण


अटल पूर्णांक cfi_jedec_setup(काष्ठा map_info *map, काष्ठा cfi_निजी *cfi, पूर्णांक index)
अणु
	पूर्णांक i,num_erase_regions;
	uपूर्णांक8_t uaddr;

	अगर (!(jedec_table[index].devtypes & cfi->device_type)) अणु
		pr_debug("Rejecting potential %s with incompatible %d-bit device type\n",
		      jedec_table[index].name, 4 * (1<<cfi->device_type));
		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Found: %s\n",jedec_table[index].name);

	num_erase_regions = jedec_table[index].nr_regions;

	cfi->cfiq = kदो_स्मृति(माप(काष्ठा cfi_ident) + num_erase_regions * 4, GFP_KERNEL);
	अगर (!cfi->cfiq) अणु
		//xx prपूर्णांकk(KERN_WARNING "%s: kmalloc failed for CFI ident structure\n", map->name);
		वापस 0;
	पूर्ण

	स_रखो(cfi->cfiq, 0, माप(काष्ठा cfi_ident));

	cfi->cfiq->P_ID = jedec_table[index].cmd_set;
	cfi->cfiq->NumEraseRegions = jedec_table[index].nr_regions;
	cfi->cfiq->DevSize = jedec_table[index].dev_size;
	cfi->cfi_mode = CFI_MODE_JEDEC;
	cfi->sector_erase_cmd = CMD(0x30);

	क्रम (i=0; i<num_erase_regions; i++)अणु
		cfi->cfiq->EraseRegionInfo[i] = jedec_table[index].regions[i];
	पूर्ण
	cfi->cmdset_priv = शून्य;

	/* This may be redundant क्रम some हालs, but it करोesn't hurt */
	cfi->mfr = jedec_table[index].mfr_id;
	cfi->id = jedec_table[index].dev_id;

	uaddr = jedec_table[index].uaddr;

	/* The table has unlock addresses in _bytes_, and we try not to let
	   our brains explode when we see the datasheets talking about address
	   lines numbered from A-1 to A18. The CFI table has unlock addresses
	   in device-words according to the mode the device is connected in */
	cfi->addr_unlock1 = unlock_addrs[uaddr].addr1 / cfi->device_type;
	cfi->addr_unlock2 = unlock_addrs[uaddr].addr2 / cfi->device_type;

	वापस 1;	/* ok */
पूर्ण


/*
 * There is a BIG problem properly ID'ing the JEDEC device and guaranteeing
 * the mapped address, unlock addresses, and proper chip ID.  This function
 * attempts to minimize errors.  It is करोubtfull that this probe will ever
 * be perfect - consequently there should be some module parameters that
 * could be manually specअगरied to क्रमce the chip info.
 */
अटल अंतरभूत पूर्णांक jedec_match( uपूर्णांक32_t base,
			       काष्ठा map_info *map,
			       काष्ठा cfi_निजी *cfi,
			       स्थिर काष्ठा amd_flash_info *finfo )
अणु
	पूर्णांक rc = 0;           /* failure until all tests pass */
	u32 mfr, id;
	uपूर्णांक8_t uaddr;

	/*
	 * The IDs must match.  For X16 and X32 devices operating in
	 * a lower width ( X8 or X16 ), the device ID's are usually just
	 * the lower byte(s) of the larger device ID क्रम wider mode.  If
	 * a part is found that करोesn't fit this assumption (device id क्रम
	 * smaller width mode is completely unrealated to full-width mode)
	 * then the jedec_table[] will have to be augmented with the IDs
	 * क्रम dअगरferent widths.
	 */
	चयन (cfi->device_type) अणु
	हाल CFI_DEVICETYPE_X8:
		mfr = (uपूर्णांक8_t)finfo->mfr_id;
		id = (uपूर्णांक8_t)finfo->dev_id;

		/* bjd: it seems that अगर we करो this, we can end up
		 * detecting 16bit flashes as an 8bit device, even though
		 * there aren't.
		 */
		अगर (finfo->dev_id > 0xff) अणु
			pr_debug("%s(): ID is not 8bit\n",
			       __func__);
			जाओ match_करोne;
		पूर्ण
		अवरोध;
	हाल CFI_DEVICETYPE_X16:
		mfr = (uपूर्णांक16_t)finfo->mfr_id;
		id = (uपूर्णांक16_t)finfo->dev_id;
		अवरोध;
	हाल CFI_DEVICETYPE_X32:
		mfr = (uपूर्णांक16_t)finfo->mfr_id;
		id = (uपूर्णांक32_t)finfo->dev_id;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING
		       "MTD %s(): Unsupported device type %d\n",
		       __func__, cfi->device_type);
		जाओ match_करोne;
	पूर्ण
	अगर ( cfi->mfr != mfr || cfi->id != id ) अणु
		जाओ match_करोne;
	पूर्ण

	/* the part size must fit in the memory winकरोw */
	pr_debug("MTD %s(): Check fit 0x%.8x + 0x%.8x = 0x%.8x\n",
	       __func__, base, 1 << finfo->dev_size, base + (1 << finfo->dev_size) );
	अगर ( base + cfi_पूर्णांकerleave(cfi) * ( 1 << finfo->dev_size ) > map->size ) अणु
		pr_debug("MTD %s(): 0x%.4x 0x%.4x %dKiB doesn't fit\n",
		       __func__, finfo->mfr_id, finfo->dev_id,
		       1 << finfo->dev_size );
		जाओ match_करोne;
	पूर्ण

	अगर (! (finfo->devtypes & cfi->device_type))
		जाओ match_करोne;

	uaddr = finfo->uaddr;

	pr_debug("MTD %s(): check unlock addrs 0x%.4x 0x%.4x\n",
	       __func__, cfi->addr_unlock1, cfi->addr_unlock2 );
	अगर ( MTD_UADDR_UNNECESSARY != uaddr && MTD_UADDR_DONT_CARE != uaddr
	     && ( unlock_addrs[uaddr].addr1 / cfi->device_type != cfi->addr_unlock1 ||
		  unlock_addrs[uaddr].addr2 / cfi->device_type != cfi->addr_unlock2 ) ) अणु
		pr_debug("MTD %s(): 0x%.4x 0x%.4x did not match\n",
			__func__,
			unlock_addrs[uaddr].addr1,
			unlock_addrs[uaddr].addr2);
		जाओ match_करोne;
	पूर्ण

	/*
	 * Make sure the ID's disappear when the device is taken out of
	 * ID mode.  The only समय this should fail when it should succeed
	 * is when the ID's are written as data to the same
	 * addresses.  For this rare and unक्रमtunate हाल the chip
	 * cannot be probed correctly.
	 * FIXME - ग_लिखो a driver that takes all of the chip info as
	 * module parameters, करोesn't probe but क्रमces a load.
	 */
	pr_debug("MTD %s(): check ID's disappear when not in ID mode\n",
	       __func__ );
	jedec_reset( base, map, cfi );
	mfr = jedec_पढ़ो_mfr( map, base, cfi );
	id = jedec_पढ़ो_id( map, base, cfi );
	अगर ( mfr == cfi->mfr && id == cfi->id ) अणु
		pr_debug("MTD %s(): ID 0x%.2x:0x%.2x did not change after reset:\n"
		       "You might need to manually specify JEDEC parameters.\n",
			__func__, cfi->mfr, cfi->id );
		जाओ match_करोne;
	पूर्ण

	/* all tests passed - mark  as success */
	rc = 1;

	/*
	 * Put the device back in ID mode - only need to करो this अगर we
	 * were truly frobbing a real device.
	 */
	pr_debug("MTD %s(): return to ID mode\n", __func__ );
	अगर (cfi->addr_unlock1) अणु
		cfi_send_gen_cmd(0xaa, cfi->addr_unlock1, base, map, cfi, cfi->device_type, शून्य);
		cfi_send_gen_cmd(0x55, cfi->addr_unlock2, base, map, cfi, cfi->device_type, शून्य);
	पूर्ण
	cfi_send_gen_cmd(0x90, cfi->addr_unlock1, base, map, cfi, cfi->device_type, शून्य);
	/* FIXME - should have a delay beक्रमe continuing */

 match_करोne:
	वापस rc;
पूर्ण


अटल पूर्णांक jedec_probe_chip(काष्ठा map_info *map, __u32 base,
			    अचिन्हित दीर्घ *chip_map, काष्ठा cfi_निजी *cfi)
अणु
	पूर्णांक i;
	क्रमागत uaddr uaddr_idx = MTD_UADDR_NOT_SUPPORTED;
	u32 probe_offset1, probe_offset2;

 retry:
	अगर (!cfi->numchips) अणु
		uaddr_idx++;

		अगर (MTD_UADDR_UNNECESSARY == uaddr_idx)
			वापस 0;

		cfi->addr_unlock1 = unlock_addrs[uaddr_idx].addr1 / cfi->device_type;
		cfi->addr_unlock2 = unlock_addrs[uaddr_idx].addr2 / cfi->device_type;
	पूर्ण

	/* Make certain we aren't probing past the end of map */
	अगर (base >= map->size) अणु
		prपूर्णांकk(KERN_NOTICE
			"Probe at base(0x%08x) past the end of the map(0x%08lx)\n",
			base, map->size -1);
		वापस 0;

	पूर्ण
	/* Ensure the unlock addresses we try stay inside the map */
	probe_offset1 = cfi_build_cmd_addr(cfi->addr_unlock1, map, cfi);
	probe_offset2 = cfi_build_cmd_addr(cfi->addr_unlock2, map, cfi);
	अगर (	((base + probe_offset1 + map_bankwidth(map)) >= map->size) ||
		((base + probe_offset2 + map_bankwidth(map)) >= map->size))
		जाओ retry;

	/* Reset */
	jedec_reset(base, map, cfi);

	/* Autoselect Mode */
	अगर(cfi->addr_unlock1) अणु
		cfi_send_gen_cmd(0xaa, cfi->addr_unlock1, base, map, cfi, cfi->device_type, शून्य);
		cfi_send_gen_cmd(0x55, cfi->addr_unlock2, base, map, cfi, cfi->device_type, शून्य);
	पूर्ण
	cfi_send_gen_cmd(0x90, cfi->addr_unlock1, base, map, cfi, cfi->device_type, शून्य);
	/* FIXME - should have a delay beक्रमe continuing */

	अगर (!cfi->numchips) अणु
		/* This is the first समय we're called. Set up the CFI
		   stuff accordingly and वापस */

		cfi->mfr = jedec_पढ़ो_mfr(map, base, cfi);
		cfi->id = jedec_पढ़ो_id(map, base, cfi);
		pr_debug("Search for id:(%02x %02x) interleave(%d) type(%d)\n",
			cfi->mfr, cfi->id, cfi_पूर्णांकerleave(cfi), cfi->device_type);
		क्रम (i = 0; i < ARRAY_SIZE(jedec_table); i++) अणु
			अगर ( jedec_match( base, map, cfi, &jedec_table[i] ) ) अणु
				pr_debug("MTD %s(): matched device 0x%x,0x%x unlock_addrs: 0x%.4x 0x%.4x\n",
				       __func__, cfi->mfr, cfi->id,
				       cfi->addr_unlock1, cfi->addr_unlock2 );
				अगर (!cfi_jedec_setup(map, cfi, i))
					वापस 0;
				जाओ ok_out;
			पूर्ण
		पूर्ण
		जाओ retry;
	पूर्ण अन्यथा अणु
		uपूर्णांक16_t mfr;
		uपूर्णांक16_t id;

		/* Make sure it is a chip of the same manufacturer and id */
		mfr = jedec_पढ़ो_mfr(map, base, cfi);
		id = jedec_पढ़ो_id(map, base, cfi);

		अगर ((mfr != cfi->mfr) || (id != cfi->id)) अणु
			prपूर्णांकk(KERN_DEBUG "%s: Found different chip or no chip at all (mfr 0x%x, id 0x%x) at 0x%x\n",
			       map->name, mfr, id, base);
			jedec_reset(base, map, cfi);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Check each previous chip locations to see अगर it's an alias */
	क्रम (i=0; i < (base >> cfi->chipshअगरt); i++) अणु
		अचिन्हित दीर्घ start;
		अगर(!test_bit(i, chip_map)) अणु
			जारी; /* Skip location; no valid chip at this address */
		पूर्ण
		start = i << cfi->chipshअगरt;
		अगर (jedec_पढ़ो_mfr(map, start, cfi) == cfi->mfr &&
		    jedec_पढ़ो_id(map, start, cfi) == cfi->id) अणु
			/* Eep. This chip also looks like it's in स्वतःselect mode.
			   Is it an alias क्रम the new one? */
			jedec_reset(start, map, cfi);

			/* If the device IDs go away, it's an alias */
			अगर (jedec_पढ़ो_mfr(map, base, cfi) != cfi->mfr ||
			    jedec_पढ़ो_id(map, base, cfi) != cfi->id) अणु
				prपूर्णांकk(KERN_DEBUG "%s: Found an alias at 0x%x for the chip at 0x%lx\n",
				       map->name, base, start);
				वापस 0;
			पूर्ण

			/* Yes, it's actually got the device IDs as data. Most
			 * unक्रमtunate. Stick the new chip in पढ़ो mode
			 * too and अगर it's the same, assume it's an alias. */
			/* FIXME: Use other modes to करो a proper check */
			jedec_reset(base, map, cfi);
			अगर (jedec_पढ़ो_mfr(map, base, cfi) == cfi->mfr &&
			    jedec_पढ़ो_id(map, base, cfi) == cfi->id) अणु
				prपूर्णांकk(KERN_DEBUG "%s: Found an alias at 0x%x for the chip at 0x%lx\n",
				       map->name, base, start);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	/* OK, अगर we got to here, then none of the previous chips appear to
	   be aliases क्रम the current one. */
	set_bit((base >> cfi->chipshअगरt), chip_map); /* Update chip map */
	cfi->numchips++;

ok_out:
	/* Put it back पूर्णांकo Read Mode */
	jedec_reset(base, map, cfi);

	prपूर्णांकk(KERN_INFO "%s: Found %d x%d devices at 0x%x in %d-bit bank\n",
	       map->name, cfi_पूर्णांकerleave(cfi), cfi->device_type*8, base,
	       map->bankwidth*8);

	वापस 1;
पूर्ण

अटल काष्ठा chip_probe jedec_chip_probe = अणु
	.name = "JEDEC",
	.probe_chip = jedec_probe_chip
पूर्ण;

अटल काष्ठा mtd_info *jedec_probe(काष्ठा map_info *map)
अणु
	/*
	 * Just use the generic probe stuff to call our CFI-specअगरic
	 * chip_probe routine in all the possible permutations, etc.
	 */
	वापस mtd_करो_chip_probe(map, &jedec_chip_probe);
पूर्ण

अटल काष्ठा mtd_chip_driver jedec_chipdrv = अणु
	.probe	= jedec_probe,
	.name	= "jedec_probe",
	.module	= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init jedec_probe_init(व्योम)
अणु
	रेजिस्टर_mtd_chip_driver(&jedec_chipdrv);
	वापस 0;
पूर्ण

अटल व्योम __निकास jedec_probe_निकास(व्योम)
अणु
	unरेजिस्टर_mtd_chip_driver(&jedec_chipdrv);
पूर्ण

module_init(jedec_probe_init);
module_निकास(jedec_probe_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Erwin Authried <eauth@softsys.co.at> et al.");
MODULE_DESCRIPTION("Probe code for JEDEC-compliant flash chips");
