<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utresdecode - Resource descriptor keyword strings
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utresdecode")

#अगर defined (ACPI_DEBUG_OUTPUT) || \
	defined (ACPI_DISASSEMBLER) || \
	defined (ACPI_DEBUGGER)
/*
 * Strings used to decode resource descriptors.
 * Used by both the disassembler and the debugger resource dump routines
 */
स्थिर अक्षर *acpi_gbl_bm_decode[] = अणु
	"NotBusMaster",
	"BusMaster"
पूर्ण;

स्थिर अक्षर *acpi_gbl_config_decode[] = अणु
	"0 - Good Configuration",
	"1 - Acceptable Configuration",
	"2 - Suboptimal Configuration",
	"3 - ***Invalid Configuration***",
पूर्ण;

स्थिर अक्षर *acpi_gbl_consume_decode[] = अणु
	"ResourceProducer",
	"ResourceConsumer"
पूर्ण;

स्थिर अक्षर *acpi_gbl_dec_decode[] = अणु
	"PosDecode",
	"SubDecode"
पूर्ण;

स्थिर अक्षर *acpi_gbl_he_decode[] = अणु
	"Level",
	"Edge"
पूर्ण;

स्थिर अक्षर *acpi_gbl_io_decode[] = अणु
	"Decode10",
	"Decode16"
पूर्ण;

स्थिर अक्षर *acpi_gbl_ll_decode[] = अणु
	"ActiveHigh",
	"ActiveLow",
	"ActiveBoth",
	"Reserved"
पूर्ण;

स्थिर अक्षर *acpi_gbl_max_decode[] = अणु
	"MaxNotFixed",
	"MaxFixed"
पूर्ण;

स्थिर अक्षर *acpi_gbl_mem_decode[] = अणु
	"NonCacheable",
	"Cacheable",
	"WriteCombining",
	"Prefetchable"
पूर्ण;

स्थिर अक्षर *acpi_gbl_min_decode[] = अणु
	"MinNotFixed",
	"MinFixed"
पूर्ण;

स्थिर अक्षर *acpi_gbl_mtp_decode[] = अणु
	"AddressRangeMemory",
	"AddressRangeReserved",
	"AddressRangeACPI",
	"AddressRangeNVS"
पूर्ण;

स्थिर अक्षर *acpi_gbl_phy_decode[] = अणु
	"Type C",
	"Type D",
	"Unknown Type",
	"Unknown Type"
पूर्ण;

स्थिर अक्षर *acpi_gbl_rng_decode[] = अणु
	"InvalidRanges",
	"NonISAOnlyRanges",
	"ISAOnlyRanges",
	"EntireRange"
पूर्ण;

स्थिर अक्षर *acpi_gbl_rw_decode[] = अणु
	"ReadOnly",
	"ReadWrite"
पूर्ण;

स्थिर अक्षर *acpi_gbl_shr_decode[] = अणु
	"Exclusive",
	"Shared",
	"ExclusiveAndWake",	/* ACPI 5.0 */
	"SharedAndWake"		/* ACPI 5.0 */
पूर्ण;

स्थिर अक्षर *acpi_gbl_siz_decode[] = अणु
	"Transfer8",
	"Transfer8_16",
	"Transfer16",
	"InvalidSize"
पूर्ण;

स्थिर अक्षर *acpi_gbl_trs_decode[] = अणु
	"DenseTranslation",
	"SparseTranslation"
पूर्ण;

स्थिर अक्षर *acpi_gbl_ttp_decode[] = अणु
	"TypeStatic",
	"TypeTranslation"
पूर्ण;

स्थिर अक्षर *acpi_gbl_typ_decode[] = अणु
	"Compatibility",
	"TypeA",
	"TypeB",
	"TypeF"
पूर्ण;

स्थिर अक्षर *acpi_gbl_ppc_decode[] = अणु
	"PullDefault",
	"PullUp",
	"PullDown",
	"PullNone"
पूर्ण;

स्थिर अक्षर *acpi_gbl_ior_decode[] = अणु
	"IoRestrictionNone",
	"IoRestrictionInputOnly",
	"IoRestrictionOutputOnly",
	"IoRestrictionNoneAndPreserve"
पूर्ण;

स्थिर अक्षर *acpi_gbl_dts_decode[] = अणु
	"Width8bit",
	"Width16bit",
	"Width32bit",
	"Width64bit",
	"Width128bit",
	"Width256bit",
पूर्ण;

/* GPIO connection type */

स्थिर अक्षर *acpi_gbl_ct_decode[] = अणु
	"Interrupt",
	"I/O"
पूर्ण;

/* Serial bus type */

स्थिर अक्षर *acpi_gbl_sbt_decode[] = अणु
	"/* UNKNOWN serial bus type */",
	"I2C",
	"SPI",
	"UART",
	"CSI2"
पूर्ण;

/* I2C serial bus access mode */

स्थिर अक्षर *acpi_gbl_am_decode[] = अणु
	"AddressingMode7Bit",
	"AddressingMode10Bit"
पूर्ण;

/* I2C serial bus slave mode */

स्थिर अक्षर *acpi_gbl_sm_decode[] = अणु
	"ControllerInitiated",
	"DeviceInitiated"
पूर्ण;

/* SPI serial bus wire mode */

स्थिर अक्षर *acpi_gbl_wm_decode[] = अणु
	"FourWireMode",
	"ThreeWireMode"
पूर्ण;

/* SPI serial घड़ी phase */

स्थिर अक्षर *acpi_gbl_cph_decode[] = अणु
	"ClockPhaseFirst",
	"ClockPhaseSecond"
पूर्ण;

/* SPI serial bus घड़ी polarity */

स्थिर अक्षर *acpi_gbl_cpo_decode[] = अणु
	"ClockPolarityLow",
	"ClockPolarityHigh"
पूर्ण;

/* SPI serial bus device polarity */

स्थिर अक्षर *acpi_gbl_dp_decode[] = अणु
	"PolarityLow",
	"PolarityHigh"
पूर्ण;

/* UART serial bus endian */

स्थिर अक्षर *acpi_gbl_ed_decode[] = अणु
	"LittleEndian",
	"BigEndian"
पूर्ण;

/* UART serial bus bits per byte */

स्थिर अक्षर *acpi_gbl_bpb_decode[] = अणु
	"DataBitsFive",
	"DataBitsSix",
	"DataBitsSeven",
	"DataBitsEight",
	"DataBitsNine",
	"/* UNKNOWN Bits per byte */",
	"/* UNKNOWN Bits per byte */",
	"/* UNKNOWN Bits per byte */"
पूर्ण;

/* UART serial bus stop bits */

स्थिर अक्षर *acpi_gbl_sb_decode[] = अणु
	"StopBitsZero",
	"StopBitsOne",
	"StopBitsOnePlusHalf",
	"StopBitsTwo"
पूर्ण;

/* UART serial bus flow control */

स्थिर अक्षर *acpi_gbl_fc_decode[] = अणु
	"FlowControlNone",
	"FlowControlHardware",
	"FlowControlXON",
	"/* UNKNOWN flow control keyword */"
पूर्ण;

/* UART serial bus parity type */

स्थिर अक्षर *acpi_gbl_pt_decode[] = अणु
	"ParityTypeNone",
	"ParityTypeEven",
	"ParityTypeOdd",
	"ParityTypeMark",
	"ParityTypeSpace",
	"/* UNKNOWN parity keyword */",
	"/* UNKNOWN parity keyword */",
	"/* UNKNOWN parity keyword */"
पूर्ण;

/* pin_config type */

स्थिर अक्षर *acpi_gbl_ptyp_decode[] = अणु
	"Default",
	"Bias Pull-up",
	"Bias Pull-down",
	"Bias Default",
	"Bias Disable",
	"Bias High Impedance",
	"Bias Bus Hold",
	"Drive Open Drain",
	"Drive Open Source",
	"Drive Push Pull",
	"Drive Strength",
	"Slew Rate",
	"Input Debounce",
	"Input Schmitt Trigger",
पूर्ण;

#पूर्ण_अगर
