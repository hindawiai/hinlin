<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Host communication command स्थिरants क्रम ChromeOS EC
 *
 * Copyright (C) 2012 Google, Inc
 *
 * NOTE: This file is स्वतः-generated from ChromeOS EC Open Source code from
 * https://chromium.googlesource.com/chromiumos/platक्रमm/ec/+/master/include/ec_commands.h
 */

/* Host communication command स्थिरants क्रम Chrome EC */

#अगर_अघोषित __CROS_EC_COMMANDS_H
#घोषणा __CROS_EC_COMMANDS_H




#घोषणा BUILD_ASSERT(_cond)

/*
 * Current version of this protocol
 *
 * TODO(crosbug.com/p/11223): This is effectively useless; protocol is
 * determined in other ways.  Remove this once the kernel code no दीर्घer
 * depends on it.
 */
#घोषणा EC_PROTO_VERSION          0x00000002

/* Command version mask */
#घोषणा EC_VER_MASK(version) BIT(version)

/* I/O addresses क्रम ACPI commands */
#घोषणा EC_LPC_ADDR_ACPI_DATA  0x62
#घोषणा EC_LPC_ADDR_ACPI_CMD   0x66

/* I/O addresses क्रम host command */
#घोषणा EC_LPC_ADDR_HOST_DATA  0x200
#घोषणा EC_LPC_ADDR_HOST_CMD   0x204

/* I/O addresses क्रम host command args and params */
/* Protocol version 2 */
#घोषणा EC_LPC_ADDR_HOST_ARGS    0x800  /* And 0x801, 0x802, 0x803 */
#घोषणा EC_LPC_ADDR_HOST_PARAM   0x804  /* For version 2 params; size is
					 * EC_PROTO2_MAX_PARAM_SIZE
					 */
/* Protocol version 3 */
#घोषणा EC_LPC_ADDR_HOST_PACKET  0x800  /* Offset of version 3 packet */
#घोषणा EC_LPC_HOST_PACKET_SIZE  0x100  /* Max size of version 3 packet */

/*
 * The actual block is 0x800-0x8ff, but some BIOSes think it's 0x880-0x8ff
 * and they tell the kernel that so we have to think of it as two parts.
 */
#घोषणा EC_HOST_CMD_REGION0    0x800
#घोषणा EC_HOST_CMD_REGION1    0x880
#घोषणा EC_HOST_CMD_REGION_SIZE 0x80

/* EC command रेजिस्टर bit functions */
#घोषणा EC_LPC_CMDR_DATA	BIT(0)  /* Data पढ़ोy क्रम host to पढ़ो */
#घोषणा EC_LPC_CMDR_PENDING	BIT(1)  /* Write pending to EC */
#घोषणा EC_LPC_CMDR_BUSY	BIT(2)  /* EC is busy processing a command */
#घोषणा EC_LPC_CMDR_CMD		BIT(3)  /* Last host ग_लिखो was a command */
#घोषणा EC_LPC_CMDR_ACPI_BRST	BIT(4)  /* Burst mode (not used) */
#घोषणा EC_LPC_CMDR_SCI		BIT(5)  /* SCI event is pending */
#घोषणा EC_LPC_CMDR_SMI		BIT(6)  /* SMI event is pending */

#घोषणा EC_LPC_ADDR_MEMMAP       0x900
#घोषणा EC_MEMMAP_SIZE         255 /* ACPI IO buffer max is 255 bytes */
#घोषणा EC_MEMMAP_TEXT_MAX     8   /* Size of a string in the memory map */

/* The offset address of each type of data in mapped memory. */
#घोषणा EC_MEMMAP_TEMP_SENSOR      0x00 /* Temp sensors 0x00 - 0x0f */
#घोषणा EC_MEMMAP_FAN              0x10 /* Fan speeds 0x10 - 0x17 */
#घोषणा EC_MEMMAP_TEMP_SENSOR_B    0x18 /* More temp sensors 0x18 - 0x1f */
#घोषणा EC_MEMMAP_ID               0x20 /* 0x20 == 'E', 0x21 == 'C' */
#घोषणा EC_MEMMAP_ID_VERSION       0x22 /* Version of data in 0x20 - 0x2f */
#घोषणा EC_MEMMAP_THERMAL_VERSION  0x23 /* Version of data in 0x00 - 0x1f */
#घोषणा EC_MEMMAP_BATTERY_VERSION  0x24 /* Version of data in 0x40 - 0x7f */
#घोषणा EC_MEMMAP_SWITCHES_VERSION 0x25 /* Version of data in 0x30 - 0x33 */
#घोषणा EC_MEMMAP_EVENTS_VERSION   0x26 /* Version of data in 0x34 - 0x3f */
#घोषणा EC_MEMMAP_HOST_CMD_FLAGS   0x27 /* Host cmd पूर्णांकerface flags (8 bits) */
/* Unused 0x28 - 0x2f */
#घोषणा EC_MEMMAP_SWITCHES         0x30	/* 8 bits */
/* Unused 0x31 - 0x33 */
#घोषणा EC_MEMMAP_HOST_EVENTS      0x34 /* 64 bits */
/* Battery values are all 32 bits, unless otherwise noted. */
#घोषणा EC_MEMMAP_BATT_VOLT        0x40 /* Battery Present Voltage */
#घोषणा EC_MEMMAP_BATT_RATE        0x44 /* Battery Present Rate */
#घोषणा EC_MEMMAP_BATT_CAP         0x48 /* Battery Reमुख्यing Capacity */
#घोषणा EC_MEMMAP_BATT_FLAG        0x4c /* Battery State, see below (8-bit) */
#घोषणा EC_MEMMAP_BATT_COUNT       0x4d /* Battery Count (8-bit) */
#घोषणा EC_MEMMAP_BATT_INDEX       0x4e /* Current Battery Data Index (8-bit) */
/* Unused 0x4f */
#घोषणा EC_MEMMAP_BATT_DCAP        0x50 /* Battery Design Capacity */
#घोषणा EC_MEMMAP_BATT_DVLT        0x54 /* Battery Design Voltage */
#घोषणा EC_MEMMAP_BATT_LFCC        0x58 /* Battery Last Full Charge Capacity */
#घोषणा EC_MEMMAP_BATT_CCNT        0x5c /* Battery Cycle Count */
/* Strings are all 8 bytes (EC_MEMMAP_TEXT_MAX) */
#घोषणा EC_MEMMAP_BATT_MFGR        0x60 /* Battery Manufacturer String */
#घोषणा EC_MEMMAP_BATT_MODEL       0x68 /* Battery Model Number String */
#घोषणा EC_MEMMAP_BATT_SERIAL      0x70 /* Battery Serial Number String */
#घोषणा EC_MEMMAP_BATT_TYPE        0x78 /* Battery Type String */
#घोषणा EC_MEMMAP_ALS              0x80 /* ALS पढ़ोings in lux (2 X 16 bits) */
/* Unused 0x84 - 0x8f */
#घोषणा EC_MEMMAP_ACC_STATUS       0x90 /* Accelerometer status (8 bits )*/
/* Unused 0x91 */
#घोषणा EC_MEMMAP_ACC_DATA         0x92 /* Accelerometers data 0x92 - 0x9f */
/* 0x92: Lid Angle अगर available, LID_ANGLE_UNRELIABLE otherwise */
/* 0x94 - 0x99: 1st Accelerometer */
/* 0x9a - 0x9f: 2nd Accelerometer */
#घोषणा EC_MEMMAP_GYRO_DATA        0xa0 /* Gyroscope data 0xa0 - 0xa5 */
/* Unused 0xa6 - 0xdf */

/*
 * ACPI is unable to access memory mapped data at or above this offset due to
 * limitations of the ACPI protocol. Do not place data in the range 0xe0 - 0xfe
 * which might be needed by ACPI.
 */
#घोषणा EC_MEMMAP_NO_ACPI 0xe0

/* Define the क्रमmat of the accelerometer mapped memory status byte. */
#घोषणा EC_MEMMAP_ACC_STATUS_SAMPLE_ID_MASK  0x0f
#घोषणा EC_MEMMAP_ACC_STATUS_BUSY_BIT        BIT(4)
#घोषणा EC_MEMMAP_ACC_STATUS_PRESENCE_BIT    BIT(7)

/* Number of temp sensors at EC_MEMMAP_TEMP_SENSOR */
#घोषणा EC_TEMP_SENSOR_ENTRIES     16
/*
 * Number of temp sensors at EC_MEMMAP_TEMP_SENSOR_B.
 *
 * Valid only अगर EC_MEMMAP_THERMAL_VERSION वापसs >= 2.
 */
#घोषणा EC_TEMP_SENSOR_B_ENTRIES      8

/* Special values क्रम mapped temperature sensors */
#घोषणा EC_TEMP_SENSOR_NOT_PRESENT    0xff
#घोषणा EC_TEMP_SENSOR_ERROR          0xfe
#घोषणा EC_TEMP_SENSOR_NOT_POWERED    0xfd
#घोषणा EC_TEMP_SENSOR_NOT_CALIBRATED 0xfc
/*
 * The offset of temperature value stored in mapped memory.  This allows
 * reporting a temperature range of 200K to 454K = -73C to 181C.
 */
#घोषणा EC_TEMP_SENSOR_OFFSET      200

/*
 * Number of ALS पढ़ोings at EC_MEMMAP_ALS
 */
#घोषणा EC_ALS_ENTRIES             2

/*
 * The शेष value a temperature sensor will वापस when it is present but
 * has not been पढ़ो this boot.  This is a reasonable number to aव्योम
 * triggering alarms on the host.
 */
#घोषणा EC_TEMP_SENSOR_DEFAULT     (296 - EC_TEMP_SENSOR_OFFSET)

#घोषणा EC_FAN_SPEED_ENTRIES       4       /* Number of fans at EC_MEMMAP_FAN */
#घोषणा EC_FAN_SPEED_NOT_PRESENT   0xffff  /* Entry not present */
#घोषणा EC_FAN_SPEED_STALLED       0xfffe  /* Fan stalled */

/* Battery bit flags at EC_MEMMAP_BATT_FLAG. */
#घोषणा EC_BATT_FLAG_AC_PRESENT   0x01
#घोषणा EC_BATT_FLAG_BATT_PRESENT 0x02
#घोषणा EC_BATT_FLAG_DISCHARGING  0x04
#घोषणा EC_BATT_FLAG_CHARGING     0x08
#घोषणा EC_BATT_FLAG_LEVEL_CRITICAL 0x10
/* Set अगर some of the अटल/dynamic data is invalid (or outdated). */
#घोषणा EC_BATT_FLAG_INVALID_DATA 0x20

/* Switch flags at EC_MEMMAP_SWITCHES */
#घोषणा EC_SWITCH_LID_OPEN               0x01
#घोषणा EC_SWITCH_POWER_BUTTON_PRESSED   0x02
#घोषणा EC_SWITCH_WRITE_PROTECT_DISABLED 0x04
/* Was recovery requested via keyboard; now unused. */
#घोषणा EC_SWITCH_IGNORE1		 0x08
/* Recovery requested via dedicated संकेत (from servo board) */
#घोषणा EC_SWITCH_DEDICATED_RECOVERY     0x10
/* Was fake developer mode चयन; now unused.  Remove in next refactor. */
#घोषणा EC_SWITCH_IGNORE0                0x20

/* Host command पूर्णांकerface flags */
/* Host command पूर्णांकerface supports LPC args (LPC पूर्णांकerface only) */
#घोषणा EC_HOST_CMD_FLAG_LPC_ARGS_SUPPORTED  0x01
/* Host command पूर्णांकerface supports version 3 protocol */
#घोषणा EC_HOST_CMD_FLAG_VERSION_3   0x02

/* Wireless चयन flags */
#घोषणा EC_WIRELESS_SWITCH_ALL       ~0x00  /* All flags */
#घोषणा EC_WIRELESS_SWITCH_WLAN       0x01  /* WLAN radio */
#घोषणा EC_WIRELESS_SWITCH_BLUETOOTH  0x02  /* Bluetooth radio */
#घोषणा EC_WIRELESS_SWITCH_WWAN       0x04  /* WWAN घातer */
#घोषणा EC_WIRELESS_SWITCH_WLAN_POWER 0x08  /* WLAN घातer */

/*****************************************************************************/
/*
 * ACPI commands
 *
 * These are valid ONLY on the ACPI command/data port.
 */

/*
 * ACPI Read Embedded Controller
 *
 * This पढ़ोs from ACPI memory space on the EC (EC_ACPI_MEM_*).
 *
 * Use the following sequence:
 *
 *    - Write EC_CMD_ACPI_READ to EC_LPC_ADDR_ACPI_CMD
 *    - Wait क्रम EC_LPC_CMDR_PENDING bit to clear
 *    - Write address to EC_LPC_ADDR_ACPI_DATA
 *    - Wait क्रम EC_LPC_CMDR_DATA bit to set
 *    - Read value from EC_LPC_ADDR_ACPI_DATA
 */
#घोषणा EC_CMD_ACPI_READ 0x0080

/*
 * ACPI Write Embedded Controller
 *
 * This पढ़ोs from ACPI memory space on the EC (EC_ACPI_MEM_*).
 *
 * Use the following sequence:
 *
 *    - Write EC_CMD_ACPI_WRITE to EC_LPC_ADDR_ACPI_CMD
 *    - Wait क्रम EC_LPC_CMDR_PENDING bit to clear
 *    - Write address to EC_LPC_ADDR_ACPI_DATA
 *    - Wait क्रम EC_LPC_CMDR_PENDING bit to clear
 *    - Write value to EC_LPC_ADDR_ACPI_DATA
 */
#घोषणा EC_CMD_ACPI_WRITE 0x0081

/*
 * ACPI Burst Enable Embedded Controller
 *
 * This enables burst mode on the EC to allow the host to issue several
 * commands back-to-back. While in this mode, ग_लिखोs to mapped multi-byte
 * data are locked out to ensure data consistency.
 */
#घोषणा EC_CMD_ACPI_BURST_ENABLE 0x0082

/*
 * ACPI Burst Disable Embedded Controller
 *
 * This disables burst mode on the EC and stops preventing EC ग_लिखोs to mapped
 * multi-byte data.
 */
#घोषणा EC_CMD_ACPI_BURST_DISABLE 0x0083

/*
 * ACPI Query Embedded Controller
 *
 * This clears the lowest-order bit in the currently pending host events, and
 * sets the result code to the 1-based index of the bit (event 0x00000001 = 1,
 * event 0x80000000 = 32), or 0 अगर no event was pending.
 */
#घोषणा EC_CMD_ACPI_QUERY_EVENT 0x0084

/* Valid addresses in ACPI memory space, क्रम पढ़ो/ग_लिखो commands */

/* Memory space version; set to EC_ACPI_MEM_VERSION_CURRENT */
#घोषणा EC_ACPI_MEM_VERSION            0x00
/*
 * Test location; writing value here updates test compliment byte to (0xff -
 * value).
 */
#घोषणा EC_ACPI_MEM_TEST               0x01
/* Test compliment; ग_लिखोs here are ignored. */
#घोषणा EC_ACPI_MEM_TEST_COMPLIMENT    0x02

/* Keyboard backlight brightness percent (0 - 100) */
#घोषणा EC_ACPI_MEM_KEYBOARD_BACKLIGHT 0x03
/* DPTF Target Fan Duty (0-100, 0xff क्रम स्वतः/none) */
#घोषणा EC_ACPI_MEM_FAN_DUTY           0x04

/*
 * DPTF temp thresholds. Any of the EC's temp sensors can have up to two
 * independent thresholds attached to them. The current value of the ID
 * रेजिस्टर determines which sensor is affected by the THRESHOLD and COMMIT
 * रेजिस्टरs. The THRESHOLD रेजिस्टर uses the same EC_TEMP_SENSOR_OFFSET scheme
 * as the memory-mapped sensors. The COMMIT रेजिस्टर applies those settings.
 *
 * The spec करोes not mandate any way to पढ़ो back the threshold settings
 * themselves, but when a threshold is crossed the AP needs a way to determine
 * which sensor(s) are responsible. Each पढ़ोing of the ID रेजिस्टर clears and
 * वापसs one sensor ID that has crossed one of its threshold (in either
 * direction) since the last पढ़ो. A value of 0xFF means "no new thresholds
 * have tripped". Setting or enabling the thresholds क्रम a sensor will clear
 * the unपढ़ो event count क्रम that sensor.
 */
#घोषणा EC_ACPI_MEM_TEMP_ID            0x05
#घोषणा EC_ACPI_MEM_TEMP_THRESHOLD     0x06
#घोषणा EC_ACPI_MEM_TEMP_COMMIT        0x07
/*
 * Here are the bits क्रम the COMMIT रेजिस्टर:
 *   bit 0 selects the threshold index क्रम the chosen sensor (0/1)
 *   bit 1 enables/disables the selected threshold (0 = off, 1 = on)
 * Each ग_लिखो to the commit रेजिस्टर affects one threshold.
 */
#घोषणा EC_ACPI_MEM_TEMP_COMMIT_SELECT_MASK BIT(0)
#घोषणा EC_ACPI_MEM_TEMP_COMMIT_ENABLE_MASK BIT(1)
/*
 * Example:
 *
 * Set the thresholds क्रम sensor 2 to 50 C and 60 C:
 *   ग_लिखो 2 to [0x05]      --  select temp sensor 2
 *   ग_लिखो 0x7b to [0x06]   --  C_TO_K(50) - EC_TEMP_SENSOR_OFFSET
 *   ग_लिखो 0x2 to [0x07]    --  enable threshold 0 with this value
 *   ग_लिखो 0x85 to [0x06]   --  C_TO_K(60) - EC_TEMP_SENSOR_OFFSET
 *   ग_लिखो 0x3 to [0x07]    --  enable threshold 1 with this value
 *
 * Disable the 60 C threshold, leaving the 50 C threshold unchanged:
 *   ग_लिखो 2 to [0x05]      --  select temp sensor 2
 *   ग_लिखो 0x1 to [0x07]    --  disable threshold 1
 */

/* DPTF battery अक्षरging current limit */
#घोषणा EC_ACPI_MEM_CHARGING_LIMIT     0x08

/* Charging limit is specअगरied in 64 mA steps */
#घोषणा EC_ACPI_MEM_CHARGING_LIMIT_STEP_MA   64
/* Value to disable DPTF battery अक्षरging limit */
#घोषणा EC_ACPI_MEM_CHARGING_LIMIT_DISABLED  0xff

/*
 * Report device orientation
 *  Bits       Definition
 *  3:1        Device DPTF Profile Number (DDPN)
 *               0   = Reserved क्रम backward compatibility (indicates no valid
 *                     profile number. Host should fall back to using TBMD).
 *              1..7 = DPTF Profile number to indicate to host which table needs
 *                     to be loaded.
 *   0         Tablet Mode Device Indicator (TBMD)
 */
#घोषणा EC_ACPI_MEM_DEVICE_ORIENTATION 0x09
#घोषणा EC_ACPI_MEM_TBMD_SHIFT         0
#घोषणा EC_ACPI_MEM_TBMD_MASK          0x1
#घोषणा EC_ACPI_MEM_DDPN_SHIFT         1
#घोषणा EC_ACPI_MEM_DDPN_MASK          0x7

/*
 * Report device features. Uses the same क्रमmat as the host command, except:
 *
 * bit 0 (EC_FEATURE_LIMITED) changes meaning from "EC code has a limited set
 * of features", which is of limited पूर्णांकerest when the प्रणाली is alपढ़ोy
 * पूर्णांकerpreting ACPI bytecode, to "EC_FEATURES[0-7] is not supported". Since
 * these are supported, it शेषs to 0.
 * This allows detecting the presence of this field since older versions of
 * the EC codebase would simply वापस 0xff to that unknown address. Check
 * FEATURES0 != 0xff (or FEATURES0[0] == 0) to make sure that the other bits
 * are valid.
 */
#घोषणा EC_ACPI_MEM_DEVICE_FEATURES0 0x0a
#घोषणा EC_ACPI_MEM_DEVICE_FEATURES1 0x0b
#घोषणा EC_ACPI_MEM_DEVICE_FEATURES2 0x0c
#घोषणा EC_ACPI_MEM_DEVICE_FEATURES3 0x0d
#घोषणा EC_ACPI_MEM_DEVICE_FEATURES4 0x0e
#घोषणा EC_ACPI_MEM_DEVICE_FEATURES5 0x0f
#घोषणा EC_ACPI_MEM_DEVICE_FEATURES6 0x10
#घोषणा EC_ACPI_MEM_DEVICE_FEATURES7 0x11

#घोषणा EC_ACPI_MEM_BATTERY_INDEX    0x12

/*
 * USB Port Power. Each bit indicates whether the corresponding USB ports' घातer
 * is enabled (1) or disabled (0).
 *   bit 0 USB port ID 0
 *   ...
 *   bit 7 USB port ID 7
 */
#घोषणा EC_ACPI_MEM_USB_PORT_POWER 0x13

/*
 * ACPI addresses 0x20 - 0xff map to EC_MEMMAP offset 0x00 - 0xdf.  This data
 * is पढ़ो-only from the AP.  Added in EC_ACPI_MEM_VERSION 2.
 */
#घोषणा EC_ACPI_MEM_MAPPED_BEGIN   0x20
#घोषणा EC_ACPI_MEM_MAPPED_SIZE    0xe0

/* Current version of ACPI memory address space */
#घोषणा EC_ACPI_MEM_VERSION_CURRENT 2


/*
 * This header file is used in coreboot both in C and ACPI code.  The ACPI code
 * is pre-processed to handle स्थिरants but the ASL compiler is unable to
 * handle actual C code so keep it separate.
 */


/*
 * Attributes क्रम EC request and response packets.  Just defining __packed
 * results in inefficient assembly code on ARM, अगर the काष्ठाure is actually
 * 32-bit aligned, as it should be क्रम all buffers.
 *
 * Be very careful when adding these to existing काष्ठाures.  They will round
 * up the काष्ठाure size to the specअगरied boundary.
 *
 * Also be very careful to make that अगर a काष्ठाure is included in some other
 * parent काष्ठाure that the alignment will still be true given the packing of
 * the parent काष्ठाure.  This is particularly important अगर the sub-काष्ठाure
 * will be passed as a poपूर्णांकer to another function, since that function will
 * not know about the misaligment caused by the parent काष्ठाure's packing.
 *
 * Also be very careful using __packed - particularly when nesting non-packed
 * काष्ठाures inside packed ones.  In fact, DO NOT use __packed directly;
 * always use one of these attributes.
 *
 * Once everything is annotated properly, the following search strings should
 * not वापस ANY matches in this file other than right here:
 *
 * "__packed" - generates inefficient code; all sub-काष्ठाs must also be packed
 *
 * "काष्ठा [^_]" - all काष्ठाs should be annotated, except क्रम काष्ठाs that are
 * members of other काष्ठाs/जोड़s (and their original declarations should be
 * annotated).
 */

/*
 * Packed काष्ठाures make no assumption about alignment, so they करो inefficient
 * byte-wise पढ़ोs.
 */
#घोषणा __ec_align1 __packed
#घोषणा __ec_align2 __packed
#घोषणा __ec_align4 __packed
#घोषणा __ec_align_size1 __packed
#घोषणा __ec_align_offset1 __packed
#घोषणा __ec_align_offset2 __packed
#घोषणा __ec_toकरो_packed __packed
#घोषणा __ec_toकरो_unpacked


/* LPC command status byte masks */
/* EC has written a byte in the data रेजिस्टर and host hasn't पढ़ो it yet */
#घोषणा EC_LPC_STATUS_TO_HOST     0x01
/* Host has written a command/data byte and the EC hasn't पढ़ो it yet */
#घोषणा EC_LPC_STATUS_FROM_HOST   0x02
/* EC is processing a command */
#घोषणा EC_LPC_STATUS_PROCESSING  0x04
/* Last ग_लिखो to EC was a command, not data */
#घोषणा EC_LPC_STATUS_LAST_CMD    0x08
/* EC is in burst mode */
#घोषणा EC_LPC_STATUS_BURST_MODE  0x10
/* SCI event is pending (requesting SCI query) */
#घोषणा EC_LPC_STATUS_SCI_PENDING 0x20
/* SMI event is pending (requesting SMI query) */
#घोषणा EC_LPC_STATUS_SMI_PENDING 0x40
/* (reserved) */
#घोषणा EC_LPC_STATUS_RESERVED    0x80

/*
 * EC is busy.  This covers both the EC processing a command, and the host has
 * written a new command but the EC hasn't picked it up yet.
 */
#घोषणा EC_LPC_STATUS_BUSY_MASK \
	(EC_LPC_STATUS_FROM_HOST | EC_LPC_STATUS_PROCESSING)

/*
 * Host command response codes (16-bit).  Note that response codes should be
 * stored in a uपूर्णांक16_t rather than directly in a value of this type.
 */
क्रमागत ec_status अणु
	EC_RES_SUCCESS = 0,
	EC_RES_INVALID_COMMAND = 1,
	EC_RES_ERROR = 2,
	EC_RES_INVALID_PARAM = 3,
	EC_RES_ACCESS_DENIED = 4,
	EC_RES_INVALID_RESPONSE = 5,
	EC_RES_INVALID_VERSION = 6,
	EC_RES_INVALID_CHECKSUM = 7,
	EC_RES_IN_PROGRESS = 8,		/* Accepted, command in progress */
	EC_RES_UNAVAILABLE = 9,		/* No response available */
	EC_RES_TIMEOUT = 10,		/* We got a समयout */
	EC_RES_OVERFLOW = 11,		/* Table / data overflow */
	EC_RES_INVALID_HEADER = 12,     /* Header contains invalid data */
	EC_RES_REQUEST_TRUNCATED = 13,  /* Didn't get the entire request */
	EC_RES_RESPONSE_TOO_BIG = 14,   /* Response was too big to handle */
	EC_RES_BUS_ERROR = 15,		/* Communications bus error */
	EC_RES_BUSY = 16,		/* Up but too busy.  Should retry */
	EC_RES_INVALID_HEADER_VERSION = 17,  /* Header version invalid */
	EC_RES_INVALID_HEADER_CRC = 18,      /* Header CRC invalid */
	EC_RES_INVALID_DATA_CRC = 19,        /* Data CRC invalid */
	EC_RES_DUP_UNAVAILABLE = 20,         /* Can't resend response */
पूर्ण;

/*
 * Host event codes.  Note these are 1-based, not 0-based, because ACPI query
 * EC command uses code 0 to mean "no event pending".  We explicitly specअगरy
 * each value in the क्रमागत listing so they won't change अगर we delete/insert an
 * item or rearrange the list (it needs to be stable across platक्रमms, not
 * just within a single compiled instance).
 */
क्रमागत host_event_code अणु
	EC_HOST_EVENT_LID_CLOSED = 1,
	EC_HOST_EVENT_LID_OPEN = 2,
	EC_HOST_EVENT_POWER_BUTTON = 3,
	EC_HOST_EVENT_AC_CONNECTED = 4,
	EC_HOST_EVENT_AC_DISCONNECTED = 5,
	EC_HOST_EVENT_BATTERY_LOW = 6,
	EC_HOST_EVENT_BATTERY_CRITICAL = 7,
	EC_HOST_EVENT_BATTERY = 8,
	EC_HOST_EVENT_THERMAL_THRESHOLD = 9,
	/* Event generated by a device attached to the EC */
	EC_HOST_EVENT_DEVICE = 10,
	EC_HOST_EVENT_THERMAL = 11,
	EC_HOST_EVENT_USB_CHARGER = 12,
	EC_HOST_EVENT_KEY_PRESSED = 13,
	/*
	 * EC has finished initializing the host पूर्णांकerface.  The host can check
	 * क्रम this event following sending a EC_CMD_REBOOT_EC command to
	 * determine when the EC is पढ़ोy to accept subsequent commands.
	 */
	EC_HOST_EVENT_INTERFACE_READY = 14,
	/* Keyboard recovery combo has been pressed */
	EC_HOST_EVENT_KEYBOARD_RECOVERY = 15,

	/* Shutकरोwn due to thermal overload */
	EC_HOST_EVENT_THERMAL_SHUTDOWN = 16,
	/* Shutकरोwn due to battery level too low */
	EC_HOST_EVENT_BATTERY_SHUTDOWN = 17,

	/* Suggest that the AP throttle itself */
	EC_HOST_EVENT_THROTTLE_START = 18,
	/* Suggest that the AP resume normal speed */
	EC_HOST_EVENT_THROTTLE_STOP = 19,

	/* Hang detect logic detected a hang and host event समयout expired */
	EC_HOST_EVENT_HANG_DETECT = 20,
	/* Hang detect logic detected a hang and warm rebooted the AP */
	EC_HOST_EVENT_HANG_REBOOT = 21,

	/* PD MCU triggering host event */
	EC_HOST_EVENT_PD_MCU = 22,

	/* Battery Status flags have changed */
	EC_HOST_EVENT_BATTERY_STATUS = 23,

	/* EC encountered a panic, triggering a reset */
	EC_HOST_EVENT_PANIC = 24,

	/* Keyboard fastboot combo has been pressed */
	EC_HOST_EVENT_KEYBOARD_FASTBOOT = 25,

	/* EC RTC event occurred */
	EC_HOST_EVENT_RTC = 26,

	/* Emulate MKBP event */
	EC_HOST_EVENT_MKBP = 27,

	/* EC desires to change state of host-controlled USB mux */
	EC_HOST_EVENT_USB_MUX = 28,

	/* TABLET/LAPTOP mode or detachable base attach/detach event */
	EC_HOST_EVENT_MODE_CHANGE = 29,

	/* Keyboard recovery combo with hardware reinitialization */
	EC_HOST_EVENT_KEYBOARD_RECOVERY_HW_REINIT = 30,

	/* WoV */
	EC_HOST_EVENT_WOV = 31,

	/*
	 * The high bit of the event mask is not used as a host event code.  If
	 * it पढ़ोs back as set, then the entire event mask should be
	 * considered invalid by the host.  This can happen when पढ़ोing the
	 * raw event status via EC_MEMMAP_HOST_EVENTS but the LPC पूर्णांकerface is
	 * not initialized on the EC, or improperly configured on the host.
	 */
	EC_HOST_EVENT_INVALID = 32
पूर्ण;
/* Host event mask */
#घोषणा EC_HOST_EVENT_MASK(event_code) BIT_ULL((event_code) - 1)

/**
 * काष्ठा ec_lpc_host_args - Arguments at EC_LPC_ADDR_HOST_ARGS
 * @flags: The host argument flags.
 * @command_version: Command version.
 * @data_size: The length of data.
 * @checksum: Checksum; sum of command + flags + command_version + data_size +
 *            all params/response data bytes.
 */
काष्ठा ec_lpc_host_args अणु
	uपूर्णांक8_t flags;
	uपूर्णांक8_t command_version;
	uपूर्णांक8_t data_size;
	uपूर्णांक8_t checksum;
पूर्ण __ec_align4;

/* Flags क्रम ec_lpc_host_args.flags */
/*
 * Args are from host.  Data area at EC_LPC_ADDR_HOST_PARAM contains command
 * params.
 *
 * If EC माला_लो a command and this flag is not set, this is an old-style command.
 * Command version is 0 and params from host are at EC_LPC_ADDR_OLD_PARAM with
 * unknown length.  EC must respond with an old-style response (that is,
 * without setting EC_HOST_ARGS_FLAG_TO_HOST).
 */
#घोषणा EC_HOST_ARGS_FLAG_FROM_HOST 0x01
/*
 * Args are from EC.  Data area at EC_LPC_ADDR_HOST_PARAM contains response.
 *
 * If EC responds to a command and this flag is not set, this is an old-style
 * response.  Command version is 0 and response data from EC is at
 * EC_LPC_ADDR_OLD_PARAM with unknown length.
 */
#घोषणा EC_HOST_ARGS_FLAG_TO_HOST   0x02

/*****************************************************************************/
/*
 * Byte codes वापसed by EC over SPI पूर्णांकerface.
 *
 * These can be used by the AP to debug the EC पूर्णांकerface, and to determine
 * when the EC is not in a state where it will ever get around to responding
 * to the AP.
 *
 * Example of sequence of bytes पढ़ो from EC क्रम a current good transfer:
 *   1. -                  - AP निश्चितs chip select (CS#)
 *   2. EC_SPI_OLD_READY   - AP sends first byte(s) of request
 *   3. -                  - EC starts handling CS# पूर्णांकerrupt
 *   4. EC_SPI_RECEIVING   - AP sends reमुख्यing byte(s) of request
 *   5. EC_SPI_PROCESSING  - EC starts processing request; AP is घड़ीing in
 *                           bytes looking क्रम EC_SPI_FRAME_START
 *   6. -                  - EC finishes processing and sets up response
 *   7. EC_SPI_FRAME_START - AP पढ़ोs frame byte
 *   8. (response packet)  - AP पढ़ोs response packet
 *   9. EC_SPI_PAST_END    - Any additional bytes पढ़ो by AP
 *   10 -                  - AP deनिश्चितs chip select
 *   11 -                  - EC processes CS# पूर्णांकerrupt and sets up DMA क्रम
 *                           next request
 *
 * If the AP is रुकोing क्रम EC_SPI_FRAME_START and sees any value other than
 * the following byte values:
 *   EC_SPI_OLD_READY
 *   EC_SPI_RX_READY
 *   EC_SPI_RECEIVING
 *   EC_SPI_PROCESSING
 *
 * Then the EC found an error in the request, or was not पढ़ोy क्रम the request
 * and lost data.  The AP should give up रुकोing क्रम EC_SPI_FRAME_START,
 * because the EC is unable to tell when the AP is करोne sending its request.
 */

/*
 * Framing byte which precedes a response packet from the EC.  After sending a
 * request, the AP will घड़ी in bytes until it sees the framing byte, then
 * घड़ी in the response packet.
 */
#घोषणा EC_SPI_FRAME_START    0xec

/*
 * Padding bytes which are घड़ीed out after the end of a response packet.
 */
#घोषणा EC_SPI_PAST_END       0xed

/*
 * EC is पढ़ोy to receive, and has ignored the byte sent by the AP.  EC expects
 * that the AP will send a valid packet header (starting with
 * EC_COMMAND_PROTOCOL_3) in the next 32 bytes.
 */
#घोषणा EC_SPI_RX_READY       0xf8

/*
 * EC has started receiving the request from the AP, but hasn't started
 * processing it yet.
 */
#घोषणा EC_SPI_RECEIVING      0xf9

/* EC has received the entire request from the AP and is processing it. */
#घोषणा EC_SPI_PROCESSING     0xfa

/*
 * EC received bad data from the AP, such as a packet header with an invalid
 * length.  EC will ignore all data until chip select deनिश्चितs.
 */
#घोषणा EC_SPI_RX_BAD_DATA    0xfb

/*
 * EC received data from the AP beक्रमe it was पढ़ोy.  That is, the AP निश्चितed
 * chip select and started घड़ीing data beक्रमe the EC was पढ़ोy to receive it.
 * EC will ignore all data until chip select deनिश्चितs.
 */
#घोषणा EC_SPI_NOT_READY      0xfc

/*
 * EC was पढ़ोy to receive a request from the AP.  EC has treated the byte sent
 * by the AP as part of a request packet, or (क्रम old-style ECs) is processing
 * a fully received packet but is not पढ़ोy to respond yet.
 */
#घोषणा EC_SPI_OLD_READY      0xfd

/*****************************************************************************/

/*
 * Protocol version 2 क्रम I2C and SPI send a request this way:
 *
 *	0	EC_CMD_VERSION0 + (command version)
 *	1	Command number
 *	2	Length of params = N
 *	3..N+2	Params, अगर any
 *	N+3	8-bit checksum of bytes 0..N+2
 *
 * The corresponding response is:
 *
 *	0	Result code (EC_RES_*)
 *	1	Length of params = M
 *	2..M+1	Params, अगर any
 *	M+2	8-bit checksum of bytes 0..M+1
 */
#घोषणा EC_PROTO2_REQUEST_HEADER_BYTES 3
#घोषणा EC_PROTO2_REQUEST_TRAILER_BYTES 1
#घोषणा EC_PROTO2_REQUEST_OVERHEAD (EC_PROTO2_REQUEST_HEADER_BYTES +	\
				    EC_PROTO2_REQUEST_TRAILER_BYTES)

#घोषणा EC_PROTO2_RESPONSE_HEADER_BYTES 2
#घोषणा EC_PROTO2_RESPONSE_TRAILER_BYTES 1
#घोषणा EC_PROTO2_RESPONSE_OVERHEAD (EC_PROTO2_RESPONSE_HEADER_BYTES +	\
				     EC_PROTO2_RESPONSE_TRAILER_BYTES)

/* Parameter length was limited by the LPC पूर्णांकerface */
#घोषणा EC_PROTO2_MAX_PARAM_SIZE 0xfc

/* Maximum request and response packet sizes क्रम protocol version 2 */
#घोषणा EC_PROTO2_MAX_REQUEST_SIZE (EC_PROTO2_REQUEST_OVERHEAD +	\
				    EC_PROTO2_MAX_PARAM_SIZE)
#घोषणा EC_PROTO2_MAX_RESPONSE_SIZE (EC_PROTO2_RESPONSE_OVERHEAD +	\
				     EC_PROTO2_MAX_PARAM_SIZE)

/*****************************************************************************/

/*
 * Value written to legacy command port / prefix byte to indicate protocol
 * 3+ काष्ठाs are being used.  Usage is bus-dependent.
 */
#घोषणा EC_COMMAND_PROTOCOL_3 0xda

#घोषणा EC_HOST_REQUEST_VERSION 3

/**
 * काष्ठा ec_host_request - Version 3 request from host.
 * @काष्ठा_version: Should be 3. The EC will वापस EC_RES_INVALID_HEADER अगर it
 *                  receives a header with a version it करोesn't know how to
 *                  parse.
 * @checksum: Checksum of request and data; sum of all bytes including checksum
 *            should total to 0.
 * @command: Command to send (EC_CMD_...)
 * @command_version: Command version.
 * @reserved: Unused byte in current protocol version; set to 0.
 * @data_len: Length of data which follows this header.
 */
काष्ठा ec_host_request अणु
	uपूर्णांक8_t काष्ठा_version;
	uपूर्णांक8_t checksum;
	uपूर्णांक16_t command;
	uपूर्णांक8_t command_version;
	uपूर्णांक8_t reserved;
	uपूर्णांक16_t data_len;
पूर्ण __ec_align4;

#घोषणा EC_HOST_RESPONSE_VERSION 3

/**
 * काष्ठा ec_host_response - Version 3 response from EC.
 * @काष्ठा_version: Struct version (=3).
 * @checksum: Checksum of response and data; sum of all bytes including
 *            checksum should total to 0.
 * @result: EC's response to the command (separate from communication failure)
 * @data_len: Length of data which follows this header.
 * @reserved: Unused bytes in current protocol version; set to 0.
 */
काष्ठा ec_host_response अणु
	uपूर्णांक8_t काष्ठा_version;
	uपूर्णांक8_t checksum;
	uपूर्णांक16_t result;
	uपूर्णांक16_t data_len;
	uपूर्णांक16_t reserved;
पूर्ण __ec_align4;

/*****************************************************************************/

/*
 * Host command protocol V4.
 *
 * Packets always start with a request or response header.  They are followed
 * by data_len bytes of data.  If the data_crc_present flag is set, the data
 * bytes are followed by a CRC-8 of that data, using using x^8 + x^2 + x + 1
 * polynomial.
 *
 * Host algorithm when sending a request q:
 *
 * 101) tries_left=(some value, e.g. 3);
 * 102) q.seq_num++
 * 103) q.seq_dup=0
 * 104) Calculate q.header_crc.
 * 105) Send request q to EC.
 * 106) Wait क्रम response r.  Go to 201 अगर received or 301 अगर समयout.
 *
 * 201) If r.काष्ठा_version != 4, go to 301.
 * 202) If r.header_crc mismatches calculated CRC क्रम r header, go to 301.
 * 203) If r.data_crc_present and r.data_crc mismatches, go to 301.
 * 204) If r.seq_num != q.seq_num, go to 301.
 * 205) If r.seq_dup == q.seq_dup, वापस success.
 * 207) If r.seq_dup == 1, go to 301.
 * 208) Return error.
 *
 * 301) If --tries_left <= 0, वापस error.
 * 302) If q.seq_dup == 1, go to 105.
 * 303) q.seq_dup = 1
 * 304) Go to 104.
 *
 * EC algorithm when receiving a request q.
 * EC has response buffer r, error buffer e.
 *
 * 101) If q.काष्ठा_version != 4, set e.result = EC_RES_INVALID_HEADER_VERSION
 *      and go to 301
 * 102) If q.header_crc mismatches calculated CRC, set e.result =
 *      EC_RES_INVALID_HEADER_CRC and go to 301
 * 103) If q.data_crc_present, calculate data CRC.  If that mismatches the CRC
 *      byte at the end of the packet, set e.result = EC_RES_INVALID_DATA_CRC
 *      and go to 301.
 * 104) If q.seq_dup == 0, go to 201.
 * 105) If q.seq_num != r.seq_num, go to 201.
 * 106) If q.seq_dup == r.seq_dup, go to 205, अन्यथा go to 203.
 *
 * 201) Process request q पूर्णांकo response r.
 * 202) r.seq_num = q.seq_num
 * 203) r.seq_dup = q.seq_dup
 * 204) Calculate r.header_crc
 * 205) If r.data_len > 0 and data is no दीर्घer available, set e.result =
 *      EC_RES_DUP_UNAVAILABLE and go to 301.
 * 206) Send response r.
 *
 * 301) e.seq_num = q.seq_num
 * 302) e.seq_dup = q.seq_dup
 * 303) Calculate e.header_crc.
 * 304) Send error response e.
 */

/* Version 4 request from host */
काष्ठा ec_host_request4 अणु
	/*
	 * bits 0-3: काष्ठा_version: Structure version (=4)
	 * bit    4: is_response: Is response (=0)
	 * bits 5-6: seq_num: Sequence number
	 * bit    7: seq_dup: Sequence duplicate flag
	 */
	uपूर्णांक8_t fields0;

	/*
	 * bits 0-4: command_version: Command version
	 * bits 5-6: Reserved (set 0, ignore on पढ़ो)
	 * bit    7: data_crc_present: Is data CRC present after data
	 */
	uपूर्णांक8_t fields1;

	/* Command code (EC_CMD_*) */
	uपूर्णांक16_t command;

	/* Length of data which follows this header (not including data CRC) */
	uपूर्णांक16_t data_len;

	/* Reserved (set 0, ignore on पढ़ो) */
	uपूर्णांक8_t reserved;

	/* CRC-8 of above fields, using x^8 + x^2 + x + 1 polynomial */
	uपूर्णांक8_t header_crc;
पूर्ण __ec_align4;

/* Version 4 response from EC */
काष्ठा ec_host_response4 अणु
	/*
	 * bits 0-3: काष्ठा_version: Structure version (=4)
	 * bit    4: is_response: Is response (=1)
	 * bits 5-6: seq_num: Sequence number
	 * bit    7: seq_dup: Sequence duplicate flag
	 */
	uपूर्णांक8_t fields0;

	/*
	 * bits 0-6: Reserved (set 0, ignore on पढ़ो)
	 * bit    7: data_crc_present: Is data CRC present after data
	 */
	uपूर्णांक8_t fields1;

	/* Result code (EC_RES_*) */
	uपूर्णांक16_t result;

	/* Length of data which follows this header (not including data CRC) */
	uपूर्णांक16_t data_len;

	/* Reserved (set 0, ignore on पढ़ो) */
	uपूर्णांक8_t reserved;

	/* CRC-8 of above fields, using x^8 + x^2 + x + 1 polynomial */
	uपूर्णांक8_t header_crc;
पूर्ण __ec_align4;

/* Fields in fields0 byte */
#घोषणा EC_PACKET4_0_STRUCT_VERSION_MASK	0x0f
#घोषणा EC_PACKET4_0_IS_RESPONSE_MASK		0x10
#घोषणा EC_PACKET4_0_SEQ_NUM_SHIFT		5
#घोषणा EC_PACKET4_0_SEQ_NUM_MASK		0x60
#घोषणा EC_PACKET4_0_SEQ_DUP_MASK		0x80

/* Fields in fields1 byte */
#घोषणा EC_PACKET4_1_COMMAND_VERSION_MASK	0x1f  /* (request only) */
#घोषणा EC_PACKET4_1_DATA_CRC_PRESENT_MASK	0x80

/*****************************************************************************/
/*
 * Notes on commands:
 *
 * Each command is an 16-bit command value.  Commands which take params or
 * वापस response data specअगरy काष्ठाures क्रम that data.  If no काष्ठाure is
 * specअगरied, the command करोes not input or output data, respectively.
 * Parameter/response length is implicit in the काष्ठाs.  Some underlying
 * communication protocols (I2C, SPI) may add length or checksum headers, but
 * those are implementation-dependent and not defined here.
 *
 * All commands MUST be #घोषणाd to be 4-digit UPPER CASE hex values
 * (e.g., 0x00AB, not 0xab) क्रम CONFIG_HOSTCMD_SECTION_SORTED to work.
 */

/*****************************************************************************/
/* General / test commands */

/*
 * Get protocol version, used to deal with non-backward compatible protocol
 * changes.
 */
#घोषणा EC_CMD_PROTO_VERSION 0x0000

/**
 * काष्ठा ec_response_proto_version - Response to the proto version command.
 * @version: The protocol version.
 */
काष्ठा ec_response_proto_version अणु
	uपूर्णांक32_t version;
पूर्ण __ec_align4;

/*
 * Hello.  This is a simple command to test the EC is responsive to
 * commands.
 */
#घोषणा EC_CMD_HELLO 0x0001

/**
 * काष्ठा ec_params_hello - Parameters to the hello command.
 * @in_data: Pass anything here.
 */
काष्ठा ec_params_hello अणु
	uपूर्णांक32_t in_data;
पूर्ण __ec_align4;

/**
 * काष्ठा ec_response_hello - Response to the hello command.
 * @out_data: Output will be in_data + 0x01020304.
 */
काष्ठा ec_response_hello अणु
	uपूर्णांक32_t out_data;
पूर्ण __ec_align4;

/* Get version number */
#घोषणा EC_CMD_GET_VERSION 0x0002

क्रमागत ec_current_image अणु
	EC_IMAGE_UNKNOWN = 0,
	EC_IMAGE_RO,
	EC_IMAGE_RW
पूर्ण;

/**
 * काष्ठा ec_response_get_version - Response to the get version command.
 * @version_string_ro: Null-terminated RO firmware version string.
 * @version_string_rw: Null-terminated RW firmware version string.
 * @reserved: Unused bytes; was previously RW-B firmware version string.
 * @current_image: One of ec_current_image.
 */
काष्ठा ec_response_get_version अणु
	अक्षर version_string_ro[32];
	अक्षर version_string_rw[32];
	अक्षर reserved[32];
	uपूर्णांक32_t current_image;
पूर्ण __ec_align4;

/* Read test */
#घोषणा EC_CMD_READ_TEST 0x0003

/**
 * काष्ठा ec_params_पढ़ो_test - Parameters क्रम the पढ़ो test command.
 * @offset: Starting value क्रम पढ़ो buffer.
 * @size: Size to पढ़ो in bytes.
 */
काष्ठा ec_params_पढ़ो_test अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t size;
पूर्ण __ec_align4;

/**
 * काष्ठा ec_response_पढ़ो_test - Response to the पढ़ो test command.
 * @data: Data वापसed by the पढ़ो test command.
 */
काष्ठा ec_response_पढ़ो_test अणु
	uपूर्णांक32_t data[32];
पूर्ण __ec_align4;

/*
 * Get build inक्रमmation
 *
 * Response is null-terminated string.
 */
#घोषणा EC_CMD_GET_BUILD_INFO 0x0004

/* Get chip info */
#घोषणा EC_CMD_GET_CHIP_INFO 0x0005

/**
 * काष्ठा ec_response_get_chip_info - Response to the get chip info command.
 * @venकरोr: Null-terminated string क्रम chip venकरोr.
 * @name: Null-terminated string क्रम chip name.
 * @revision: Null-terminated string क्रम chip mask version.
 */
काष्ठा ec_response_get_chip_info अणु
	अक्षर venकरोr[32];
	अक्षर name[32];
	अक्षर revision[32];
पूर्ण __ec_align4;

/* Get board HW version */
#घोषणा EC_CMD_GET_BOARD_VERSION 0x0006

/**
 * काष्ठा ec_response_board_version - Response to the board version command.
 * @board_version: A monotonously incrementing number.
 */
काष्ठा ec_response_board_version अणु
	uपूर्णांक16_t board_version;
पूर्ण __ec_align2;

/*
 * Read memory-mapped data.
 *
 * This is an alternate पूर्णांकerface to memory-mapped data क्रम bus protocols
 * which करोn't support direct-mapped memory - I2C, SPI, etc.
 *
 * Response is params.size bytes of data.
 */
#घोषणा EC_CMD_READ_MEMMAP 0x0007

/**
 * काष्ठा ec_params_पढ़ो_memmap - Parameters क्रम the पढ़ो memory map command.
 * @offset: Offset in memmap (EC_MEMMAP_*).
 * @size: Size to पढ़ो in bytes.
 */
काष्ठा ec_params_पढ़ो_memmap अणु
	uपूर्णांक8_t offset;
	uपूर्णांक8_t size;
पूर्ण __ec_align1;

/* Read versions supported क्रम a command */
#घोषणा EC_CMD_GET_CMD_VERSIONS 0x0008

/**
 * काष्ठा ec_params_get_cmd_versions - Parameters क्रम the get command versions.
 * @cmd: Command to check.
 */
काष्ठा ec_params_get_cmd_versions अणु
	uपूर्णांक8_t cmd;
पूर्ण __ec_align1;

/**
 * काष्ठा ec_params_get_cmd_versions_v1 - Parameters क्रम the get command
 *         versions (v1)
 * @cmd: Command to check.
 */
काष्ठा ec_params_get_cmd_versions_v1 अणु
	uपूर्णांक16_t cmd;
पूर्ण __ec_align2;

/**
 * काष्ठा ec_response_get_cmd_version - Response to the get command versions.
 * @version_mask: Mask of supported versions; use EC_VER_MASK() to compare with
 *                a desired version.
 */
काष्ठा ec_response_get_cmd_versions अणु
	uपूर्णांक32_t version_mask;
पूर्ण __ec_align4;

/*
 * Check EC communications status (busy). This is needed on i2c/spi but not
 * on lpc since it has its own out-of-band busy indicator.
 *
 * lpc must पढ़ो the status from the command रेजिस्टर. Attempting this on
 * lpc will overग_लिखो the args/parameter space and corrupt its data.
 */
#घोषणा EC_CMD_GET_COMMS_STATUS		0x0009

/* Aव्योम using ec_status which is क्रम वापस values */
क्रमागत ec_comms_status अणु
	EC_COMMS_STATUS_PROCESSING	= BIT(0),	/* Processing cmd */
पूर्ण;

/**
 * काष्ठा ec_response_get_comms_status - Response to the get comms status
 *         command.
 * @flags: Mask of क्रमागत ec_comms_status.
 */
काष्ठा ec_response_get_comms_status अणु
	uपूर्णांक32_t flags;		/* Mask of क्रमागत ec_comms_status */
पूर्ण __ec_align4;

/* Fake a variety of responses, purely क्रम testing purposes. */
#घोषणा EC_CMD_TEST_PROTOCOL		0x000A

/* Tell the EC what to send back to us. */
काष्ठा ec_params_test_protocol अणु
	uपूर्णांक32_t ec_result;
	uपूर्णांक32_t ret_len;
	uपूर्णांक8_t buf[32];
पूर्ण __ec_align4;

/* Here it comes... */
काष्ठा ec_response_test_protocol अणु
	uपूर्णांक8_t buf[32];
पूर्ण __ec_align4;

/* Get protocol inक्रमmation */
#घोषणा EC_CMD_GET_PROTOCOL_INFO	0x000B

/* Flags क्रम ec_response_get_protocol_info.flags */
/* EC_RES_IN_PROGRESS may be वापसed अगर a command is slow */
#घोषणा EC_PROTOCOL_INFO_IN_PROGRESS_SUPPORTED BIT(0)

/**
 * काष्ठा ec_response_get_protocol_info - Response to the get protocol info.
 * @protocol_versions: Biपंचांगask of protocol versions supported (1 << n means
 *                     version n).
 * @max_request_packet_size: Maximum request packet size in bytes.
 * @max_response_packet_size: Maximum response packet size in bytes.
 * @flags: see EC_PROTOCOL_INFO_*
 */
काष्ठा ec_response_get_protocol_info अणु
	/* Fields which exist अगर at least protocol version 3 supported */
	uपूर्णांक32_t protocol_versions;
	uपूर्णांक16_t max_request_packet_size;
	uपूर्णांक16_t max_response_packet_size;
	uपूर्णांक32_t flags;
पूर्ण __ec_align4;


/*****************************************************************************/
/* Get/Set miscellaneous values */

/* The upper byte of .flags tells what to करो (nothing means "get") */
#घोषणा EC_GSV_SET        0x80000000

/*
 * The lower three bytes of .flags identअगरies the parameter, अगर that has
 * meaning क्रम an inभागidual command.
 */
#घोषणा EC_GSV_PARAM_MASK 0x00ffffff

काष्ठा ec_params_get_set_value अणु
	uपूर्णांक32_t flags;
	uपूर्णांक32_t value;
पूर्ण __ec_align4;

काष्ठा ec_response_get_set_value अणु
	uपूर्णांक32_t flags;
	uपूर्णांक32_t value;
पूर्ण __ec_align4;

/* More than one command can use these काष्ठाs to get/set parameters. */
#घोषणा EC_CMD_GSV_PAUSE_IN_S5	0x000C

/*****************************************************************************/
/* List the features supported by the firmware */
#घोषणा EC_CMD_GET_FEATURES  0x000D

/* Supported features */
क्रमागत ec_feature_code अणु
	/*
	 * This image contains a limited set of features. Another image
	 * in RW partition may support more features.
	 */
	EC_FEATURE_LIMITED = 0,
	/*
	 * Commands क्रम probing/पढ़ोing/writing/erasing the flash in the
	 * EC are present.
	 */
	EC_FEATURE_FLASH = 1,
	/*
	 * Can control the fan speed directly.
	 */
	EC_FEATURE_PWM_FAN = 2,
	/*
	 * Can control the पूर्णांकensity of the keyboard backlight.
	 */
	EC_FEATURE_PWM_KEYB = 3,
	/*
	 * Support Google lightbar, पूर्णांकroduced on Pixel.
	 */
	EC_FEATURE_LIGHTBAR = 4,
	/* Control of LEDs  */
	EC_FEATURE_LED = 5,
	/* Exposes an पूर्णांकerface to control gyro and sensors.
	 * The host goes through the EC to access these sensors.
	 * In addition, the EC may provide composite sensors, like lid angle.
	 */
	EC_FEATURE_MOTION_SENSE = 6,
	/* The keyboard is controlled by the EC */
	EC_FEATURE_KEYB = 7,
	/* The AP can use part of the EC flash as persistent storage. */
	EC_FEATURE_PSTORE = 8,
	/* The EC monitors BIOS port 80h, and can वापस POST codes. */
	EC_FEATURE_PORT80 = 9,
	/*
	 * Thermal management: include TMP specअगरic commands.
	 * Higher level than direct fan control.
	 */
	EC_FEATURE_THERMAL = 10,
	/* Can चयन the screen backlight on/off */
	EC_FEATURE_BKLIGHT_SWITCH = 11,
	/* Can चयन the wअगरi module on/off */
	EC_FEATURE_WIFI_SWITCH = 12,
	/* Monitor host events, through क्रम example SMI or SCI */
	EC_FEATURE_HOST_EVENTS = 13,
	/* The EC exposes GPIO commands to control/monitor connected devices. */
	EC_FEATURE_GPIO = 14,
	/* The EC can send i2c messages to करोwnstream devices. */
	EC_FEATURE_I2C = 15,
	/* Command to control अक्षरger are included */
	EC_FEATURE_CHARGER = 16,
	/* Simple battery support. */
	EC_FEATURE_BATTERY = 17,
	/*
	 * Support Smart battery protocol
	 * (Common Smart Battery System Interface Specअगरication)
	 */
	EC_FEATURE_SMART_BATTERY = 18,
	/* EC can detect when the host hangs. */
	EC_FEATURE_HANG_DETECT = 19,
	/* Report घातer inक्रमmation, क्रम pit only */
	EC_FEATURE_PMU = 20,
	/* Another Cros EC device is present करोwnstream of this one */
	EC_FEATURE_SUB_MCU = 21,
	/* Support USB Power delivery (PD) commands */
	EC_FEATURE_USB_PD = 22,
	/* Control USB multiplexer, क्रम audio through USB port क्रम instance. */
	EC_FEATURE_USB_MUX = 23,
	/* Motion Sensor code has an पूर्णांकernal software FIFO */
	EC_FEATURE_MOTION_SENSE_FIFO = 24,
	/* Support temporary secure vstore */
	EC_FEATURE_VSTORE = 25,
	/* EC decides on USB-C SS mux state, muxes configured by host */
	EC_FEATURE_USBC_SS_MUX_VIRTUAL = 26,
	/* EC has RTC feature that can be controlled by host commands */
	EC_FEATURE_RTC = 27,
	/* The MCU exposes a Fingerprपूर्णांक sensor */
	EC_FEATURE_FINGERPRINT = 28,
	/* The MCU exposes a Touchpad */
	EC_FEATURE_TOUCHPAD = 29,
	/* The MCU has RWSIG task enabled */
	EC_FEATURE_RWSIG = 30,
	/* EC has device events support */
	EC_FEATURE_DEVICE_EVENT = 31,
	/* EC supports the unअगरied wake masks क्रम LPC/eSPI प्रणालीs */
	EC_FEATURE_UNIFIED_WAKE_MASKS = 32,
	/* EC supports 64-bit host events */
	EC_FEATURE_HOST_EVENT64 = 33,
	/* EC runs code in RAM (not in place, a.k.a. XIP) */
	EC_FEATURE_EXEC_IN_RAM = 34,
	/* EC supports CEC commands */
	EC_FEATURE_CEC = 35,
	/* EC supports tight sensor बारtamping. */
	EC_FEATURE_MOTION_SENSE_TIGHT_TIMESTAMPS = 36,
	/*
	 * EC supports tablet mode detection aligned to Chrome and allows
	 * setting of threshold by host command using
	 * MOTIONSENSE_CMD_TABLET_MODE_LID_ANGLE.
	 */
	EC_FEATURE_REFINED_TABLET_MODE_HYSTERESIS = 37,
	/* The MCU is a System Companion Processor (SCP). */
	EC_FEATURE_SCP = 39,
	/* The MCU is an Integrated Sensor Hub */
	EC_FEATURE_ISH = 40,
	/* New TCPMv2 TYPEC_ prefaced commands supported */
	EC_FEATURE_TYPEC_CMD = 41,
	/*
	 * The EC will रुको क्रम direction from the AP to enter Type-C alternate
	 * modes or USB4.
	 */
	EC_FEATURE_TYPEC_REQUIRE_AP_MODE_ENTRY = 42,
	/*
	 * The EC will रुको क्रम an acknowledge from the AP after setting the
	 * mux.
	 */
	EC_FEATURE_TYPEC_MUX_REQUIRE_AP_ACK = 43,
पूर्ण;

#घोषणा EC_FEATURE_MASK_0(event_code) BIT(event_code % 32)
#घोषणा EC_FEATURE_MASK_1(event_code) BIT(event_code - 32)

काष्ठा ec_response_get_features अणु
	uपूर्णांक32_t flags[2];
पूर्ण __ec_align4;

/*****************************************************************************/
/* Get the board's SKU ID from EC */
#घोषणा EC_CMD_GET_SKU_ID 0x000E

/* Set SKU ID from AP */
#घोषणा EC_CMD_SET_SKU_ID 0x000F

काष्ठा ec_sku_id_info अणु
	uपूर्णांक32_t sku_id;
पूर्ण __ec_align4;

/*****************************************************************************/
/* Flash commands */

/* Get flash info */
#घोषणा EC_CMD_FLASH_INFO 0x0010
#घोषणा EC_VER_FLASH_INFO 2

/**
 * काष्ठा ec_response_flash_info - Response to the flash info command.
 * @flash_size: Usable flash size in bytes.
 * @ग_लिखो_block_size: Write block size. Write offset and size must be a
 *                    multiple of this.
 * @erase_block_size: Erase block size. Erase offset and size must be a
 *                    multiple of this.
 * @protect_block_size: Protection block size. Protection offset and size
 *                      must be a multiple of this.
 *
 * Version 0 वापसs these fields.
 */
काष्ठा ec_response_flash_info अणु
	uपूर्णांक32_t flash_size;
	uपूर्णांक32_t ग_लिखो_block_size;
	uपूर्णांक32_t erase_block_size;
	uपूर्णांक32_t protect_block_size;
पूर्ण __ec_align4;

/*
 * Flags क्रम version 1+ flash info command
 * EC flash erases bits to 0 instead of 1.
 */
#घोषणा EC_FLASH_INFO_ERASE_TO_0 BIT(0)

/*
 * Flash must be selected क्रम पढ़ो/ग_लिखो/erase operations to succeed.  This may
 * be necessary on a chip where ग_लिखो/erase can be corrupted by other board
 * activity, or where the chip needs to enable some sort of programming voltage,
 * or where the पढ़ो/ग_लिखो/erase operations require cleanly suspending other
 * chip functionality.
 */
#घोषणा EC_FLASH_INFO_SELECT_REQUIRED BIT(1)

/**
 * काष्ठा ec_response_flash_info_1 - Response to the flash info v1 command.
 * @flash_size: Usable flash size in bytes.
 * @ग_लिखो_block_size: Write block size. Write offset and size must be a
 *                    multiple of this.
 * @erase_block_size: Erase block size. Erase offset and size must be a
 *                    multiple of this.
 * @protect_block_size: Protection block size. Protection offset and size
 *                      must be a multiple of this.
 * @ग_लिखो_ideal_size: Ideal ग_लिखो size in bytes.  Writes will be fastest अगर
 *                    size is exactly this and offset is a multiple of this.
 *                    For example, an EC may have a ग_लिखो buffer which can करो
 *                    half-page operations अगर data is aligned, and a slower
 *                    word-at-a-समय ग_लिखो mode.
 * @flags: Flags; see EC_FLASH_INFO_*
 *
 * Version 1 वापसs the same initial fields as version 0, with additional
 * fields following.
 *
 * gcc anonymous काष्ठाs करोn't seem to get aदीर्घ with the __packed directive;
 * अगर they did we'd define the version 0 काष्ठाure as a sub-काष्ठाure of this
 * one.
 *
 * Version 2 supports flash banks of dअगरferent sizes:
 * The caller specअगरied the number of banks it has pपुनः_स्मृतिated
 * (num_banks_desc)
 * The EC वापसs the number of banks describing the flash memory.
 * It adds banks descriptions up to num_banks_desc.
 */
काष्ठा ec_response_flash_info_1 अणु
	/* Version 0 fields; see above क्रम description */
	uपूर्णांक32_t flash_size;
	uपूर्णांक32_t ग_लिखो_block_size;
	uपूर्णांक32_t erase_block_size;
	uपूर्णांक32_t protect_block_size;

	/* Version 1 adds these fields: */
	uपूर्णांक32_t ग_लिखो_ideal_size;
	uपूर्णांक32_t flags;
पूर्ण __ec_align4;

काष्ठा ec_params_flash_info_2 अणु
	/* Number of banks to describe */
	uपूर्णांक16_t num_banks_desc;
	/* Reserved; set 0; ignore on पढ़ो */
	uपूर्णांक8_t reserved[2];
पूर्ण __ec_align4;

काष्ठा ec_flash_bank अणु
	/* Number of sector is in this bank. */
	uपूर्णांक16_t count;
	/* Size in घातer of 2 of each sector (8 --> 256 bytes) */
	uपूर्णांक8_t size_exp;
	/* Minimal ग_लिखो size क्रम the sectors in this bank */
	uपूर्णांक8_t ग_लिखो_size_exp;
	/* Erase size क्रम the sectors in this bank */
	uपूर्णांक8_t erase_size_exp;
	/* Size क्रम ग_लिखो protection, usually identical to erase size. */
	uपूर्णांक8_t protect_size_exp;
	/* Reserved; set 0; ignore on पढ़ो */
	uपूर्णांक8_t reserved[2];
पूर्ण;

काष्ठा ec_response_flash_info_2 अणु
	/* Total flash in the EC. */
	uपूर्णांक32_t flash_size;
	/* Flags; see EC_FLASH_INFO_* */
	uपूर्णांक32_t flags;
	/* Maximum size to use to send data to ग_लिखो to the EC. */
	uपूर्णांक32_t ग_लिखो_ideal_size;
	/* Number of banks present in the EC. */
	uपूर्णांक16_t num_banks_total;
	/* Number of banks described in banks array. */
	uपूर्णांक16_t num_banks_desc;
	काष्ठा ec_flash_bank banks[];
पूर्ण __ec_align4;

/*
 * Read flash
 *
 * Response is params.size bytes of data.
 */
#घोषणा EC_CMD_FLASH_READ 0x0011

/**
 * काष्ठा ec_params_flash_पढ़ो - Parameters क्रम the flash पढ़ो command.
 * @offset: Byte offset to पढ़ो.
 * @size: Size to पढ़ो in bytes.
 */
काष्ठा ec_params_flash_पढ़ो अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t size;
पूर्ण __ec_align4;

/* Write flash */
#घोषणा EC_CMD_FLASH_WRITE 0x0012
#घोषणा EC_VER_FLASH_WRITE 1

/* Version 0 of the flash command supported only 64 bytes of data */
#घोषणा EC_FLASH_WRITE_VER0_SIZE 64

/**
 * काष्ठा ec_params_flash_ग_लिखो - Parameters क्रम the flash ग_लिखो command.
 * @offset: Byte offset to ग_लिखो.
 * @size: Size to ग_लिखो in bytes.
 */
काष्ठा ec_params_flash_ग_लिखो अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t size;
	/* Followed by data to ग_लिखो */
पूर्ण __ec_align4;

/* Erase flash */
#घोषणा EC_CMD_FLASH_ERASE 0x0013

/**
 * काष्ठा ec_params_flash_erase - Parameters क्रम the flash erase command, v0.
 * @offset: Byte offset to erase.
 * @size: Size to erase in bytes.
 */
काष्ठा ec_params_flash_erase अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t size;
पूर्ण __ec_align4;

/*
 * v1 add async erase:
 * subcommands can वापसs:
 * EC_RES_SUCCESS : erased (see ERASE_SECTOR_ASYNC हाल below).
 * EC_RES_INVALID_PARAM : offset/size are not aligned on a erase boundary.
 * EC_RES_ERROR : other errors.
 * EC_RES_BUSY : an existing erase operation is in progress.
 * EC_RES_ACCESS_DENIED: Trying to erase running image.
 *
 * When ERASE_SECTOR_ASYNC वापसs EC_RES_SUCCESS, the operation is just
 * properly queued. The user must call ERASE_GET_RESULT subcommand to get
 * the proper result.
 * When ERASE_GET_RESULT वापसs EC_RES_BUSY, the caller must रुको and send
 * ERASE_GET_RESULT again to get the result of ERASE_SECTOR_ASYNC.
 * ERASE_GET_RESULT command may समयout on EC where flash access is not
 * permitted जबतक erasing. (For instance, STM32F4).
 */
क्रमागत ec_flash_erase_cmd अणु
	FLASH_ERASE_SECTOR,     /* Erase and रुको क्रम result */
	FLASH_ERASE_SECTOR_ASYNC,  /* Erase and वापस immediately. */
	FLASH_ERASE_GET_RESULT,  /* Ask क्रम last erase result */
पूर्ण;

/**
 * काष्ठा ec_params_flash_erase_v1 - Parameters क्रम the flash erase command, v1.
 * @cmd: One of ec_flash_erase_cmd.
 * @reserved: Pad byte; currently always contains 0.
 * @flag: No flags defined yet; set to 0.
 * @params: Same as v0 parameters.
 */
काष्ठा ec_params_flash_erase_v1 अणु
	uपूर्णांक8_t  cmd;
	uपूर्णांक8_t  reserved;
	uपूर्णांक16_t flag;
	काष्ठा ec_params_flash_erase params;
पूर्ण __ec_align4;

/*
 * Get/set flash protection.
 *
 * If mask!=0, sets/clear the requested bits of flags.  Depending on the
 * firmware ग_लिखो protect GPIO, not all flags will take effect immediately;
 * some flags require a subsequent hard reset to take effect.  Check the
 * वापसed flags bits to see what actually happened.
 *
 * If mask=0, simply वापसs the current flags state.
 */
#घोषणा EC_CMD_FLASH_PROTECT 0x0015
#घोषणा EC_VER_FLASH_PROTECT 1  /* Command version 1 */

/* Flags क्रम flash protection */
/* RO flash code रक्षित when the EC boots */
#घोषणा EC_FLASH_PROTECT_RO_AT_BOOT         BIT(0)
/*
 * RO flash code रक्षित now.  If this bit is set, at-boot status cannot
 * be changed.
 */
#घोषणा EC_FLASH_PROTECT_RO_NOW             BIT(1)
/* Entire flash code रक्षित now, until reboot. */
#घोषणा EC_FLASH_PROTECT_ALL_NOW            BIT(2)
/* Flash ग_लिखो protect GPIO is निश्चितed now */
#घोषणा EC_FLASH_PROTECT_GPIO_ASSERTED      BIT(3)
/* Error - at least one bank of flash is stuck locked, and cannot be unlocked */
#घोषणा EC_FLASH_PROTECT_ERROR_STUCK        BIT(4)
/*
 * Error - flash protection is in inconsistent state.  At least one bank of
 * flash which should be रक्षित is not रक्षित.  Usually fixed by
 * re-requesting the desired flags, or by a hard reset अगर that fails.
 */
#घोषणा EC_FLASH_PROTECT_ERROR_INCONSISTENT BIT(5)
/* Entire flash code रक्षित when the EC boots */
#घोषणा EC_FLASH_PROTECT_ALL_AT_BOOT        BIT(6)
/* RW flash code रक्षित when the EC boots */
#घोषणा EC_FLASH_PROTECT_RW_AT_BOOT         BIT(7)
/* RW flash code रक्षित now. */
#घोषणा EC_FLASH_PROTECT_RW_NOW             BIT(8)
/* Rollback inक्रमmation flash region रक्षित when the EC boots */
#घोषणा EC_FLASH_PROTECT_ROLLBACK_AT_BOOT   BIT(9)
/* Rollback inक्रमmation flash region रक्षित now */
#घोषणा EC_FLASH_PROTECT_ROLLBACK_NOW       BIT(10)


/**
 * काष्ठा ec_params_flash_protect - Parameters क्रम the flash protect command.
 * @mask: Bits in flags to apply.
 * @flags: New flags to apply.
 */
काष्ठा ec_params_flash_protect अणु
	uपूर्णांक32_t mask;
	uपूर्णांक32_t flags;
पूर्ण __ec_align4;

/**
 * काष्ठा ec_response_flash_protect - Response to the flash protect command.
 * @flags: Current value of flash protect flags.
 * @valid_flags: Flags which are valid on this platक्रमm. This allows the
 *               caller to distinguish between flags which aren't set vs. flags
 *               which can't be set on this platक्रमm.
 * @writable_flags: Flags which can be changed given the current protection
 *                  state.
 */
काष्ठा ec_response_flash_protect अणु
	uपूर्णांक32_t flags;
	uपूर्णांक32_t valid_flags;
	uपूर्णांक32_t writable_flags;
पूर्ण __ec_align4;

/*
 * Note: commands 0x14 - 0x19 version 0 were old commands to get/set flash
 * ग_लिखो protect.  These commands may be reused with version > 0.
 */

/* Get the region offset/size */
#घोषणा EC_CMD_FLASH_REGION_INFO 0x0016
#घोषणा EC_VER_FLASH_REGION_INFO 1

क्रमागत ec_flash_region अणु
	/* Region which holds पढ़ो-only EC image */
	EC_FLASH_REGION_RO = 0,
	/*
	 * Region which holds active RW image. 'Active' is dअगरferent from
	 * 'running'. Active means 'scheduled-to-run'. Since RO image always
	 * scheduled to run, active/non-active applies only to RW images (क्रम
	 * the same reason 'update' applies only to RW images. It's a state of
	 * an image on a flash. Running image can be RO, RW_A, RW_B but active
	 * image can only be RW_A or RW_B. In recovery mode, an active RW image
	 * करोesn't enter 'running' state but it's still active on a flash.
	 */
	EC_FLASH_REGION_ACTIVE,
	/*
	 * Region which should be ग_लिखो-रक्षित in the factory (a superset of
	 * EC_FLASH_REGION_RO)
	 */
	EC_FLASH_REGION_WP_RO,
	/* Region which holds updatable (non-active) RW image */
	EC_FLASH_REGION_UPDATE,
	/* Number of regions */
	EC_FLASH_REGION_COUNT,
पूर्ण;
/*
 * 'RW' is vague अगर there are multiple RW images; we mean the active one,
 * so the old स्थिरant is deprecated.
 */
#घोषणा EC_FLASH_REGION_RW EC_FLASH_REGION_ACTIVE

/**
 * काष्ठा ec_params_flash_region_info - Parameters क्रम the flash region info
 *         command.
 * @region: Flash region; see EC_FLASH_REGION_*
 */
काष्ठा ec_params_flash_region_info अणु
	uपूर्णांक32_t region;
पूर्ण __ec_align4;

काष्ठा ec_response_flash_region_info अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t size;
पूर्ण __ec_align4;

/* Read/ग_लिखो VbNvContext */
#घोषणा EC_CMD_VBNV_CONTEXT 0x0017
#घोषणा EC_VER_VBNV_CONTEXT 1
#घोषणा EC_VBNV_BLOCK_SIZE 16

क्रमागत ec_vbnvcontext_op अणु
	EC_VBNV_CONTEXT_OP_READ,
	EC_VBNV_CONTEXT_OP_WRITE,
पूर्ण;

काष्ठा ec_params_vbnvcontext अणु
	uपूर्णांक32_t op;
	uपूर्णांक8_t block[EC_VBNV_BLOCK_SIZE];
पूर्ण __ec_align4;

काष्ठा ec_response_vbnvcontext अणु
	uपूर्णांक8_t block[EC_VBNV_BLOCK_SIZE];
पूर्ण __ec_align4;


/* Get SPI flash inक्रमmation */
#घोषणा EC_CMD_FLASH_SPI_INFO 0x0018

काष्ठा ec_response_flash_spi_info अणु
	/* JEDEC info from command 0x9F (manufacturer, memory type, size) */
	uपूर्णांक8_t jedec[3];

	/* Pad byte; currently always contains 0 */
	uपूर्णांक8_t reserved0;

	/* Manufacturer / device ID from command 0x90 */
	uपूर्णांक8_t mfr_dev_id[2];

	/* Status रेजिस्टरs from command 0x05 and 0x35 */
	uपूर्णांक8_t sr1, sr2;
पूर्ण __ec_align1;


/* Select flash during flash operations */
#घोषणा EC_CMD_FLASH_SELECT 0x0019

/**
 * काष्ठा ec_params_flash_select - Parameters क्रम the flash select command.
 * @select: 1 to select flash, 0 to deselect flash
 */
काष्ठा ec_params_flash_select अणु
	uपूर्णांक8_t select;
पूर्ण __ec_align4;


/*****************************************************************************/
/* PWM commands */

/* Get fan target RPM */
#घोषणा EC_CMD_PWM_GET_FAN_TARGET_RPM 0x0020

काष्ठा ec_response_pwm_get_fan_rpm अणु
	uपूर्णांक32_t rpm;
पूर्ण __ec_align4;

/* Set target fan RPM */
#घोषणा EC_CMD_PWM_SET_FAN_TARGET_RPM 0x0021

/* Version 0 of input params */
काष्ठा ec_params_pwm_set_fan_target_rpm_v0 अणु
	uपूर्णांक32_t rpm;
पूर्ण __ec_align4;

/* Version 1 of input params */
काष्ठा ec_params_pwm_set_fan_target_rpm_v1 अणु
	uपूर्णांक32_t rpm;
	uपूर्णांक8_t fan_idx;
पूर्ण __ec_align_size1;

/* Get keyboard backlight */
/* OBSOLETE - Use EC_CMD_PWM_SET_DUTY */
#घोषणा EC_CMD_PWM_GET_KEYBOARD_BACKLIGHT 0x0022

काष्ठा ec_response_pwm_get_keyboard_backlight अणु
	uपूर्णांक8_t percent;
	uपूर्णांक8_t enabled;
पूर्ण __ec_align1;

/* Set keyboard backlight */
/* OBSOLETE - Use EC_CMD_PWM_SET_DUTY */
#घोषणा EC_CMD_PWM_SET_KEYBOARD_BACKLIGHT 0x0023

काष्ठा ec_params_pwm_set_keyboard_backlight अणु
	uपूर्णांक8_t percent;
पूर्ण __ec_align1;

/* Set target fan PWM duty cycle */
#घोषणा EC_CMD_PWM_SET_FAN_DUTY 0x0024

/* Version 0 of input params */
काष्ठा ec_params_pwm_set_fan_duty_v0 अणु
	uपूर्णांक32_t percent;
पूर्ण __ec_align4;

/* Version 1 of input params */
काष्ठा ec_params_pwm_set_fan_duty_v1 अणु
	uपूर्णांक32_t percent;
	uपूर्णांक8_t fan_idx;
पूर्ण __ec_align_size1;

#घोषणा EC_CMD_PWM_SET_DUTY 0x0025
/* 16 bit duty cycle, 0xffff = 100% */
#घोषणा EC_PWM_MAX_DUTY 0xffff

क्रमागत ec_pwm_type अणु
	/* All types, indexed by board-specअगरic क्रमागत pwm_channel */
	EC_PWM_TYPE_GENERIC = 0,
	/* Keyboard backlight */
	EC_PWM_TYPE_KB_LIGHT,
	/* Display backlight */
	EC_PWM_TYPE_DISPLAY_LIGHT,
	EC_PWM_TYPE_COUNT,
पूर्ण;

काष्ठा ec_params_pwm_set_duty अणु
	uपूर्णांक16_t duty;     /* Duty cycle, EC_PWM_MAX_DUTY = 100% */
	uपूर्णांक8_t pwm_type;  /* ec_pwm_type */
	uपूर्णांक8_t index;     /* Type-specअगरic index, or 0 अगर unique */
पूर्ण __ec_align4;

#घोषणा EC_CMD_PWM_GET_DUTY 0x0026

काष्ठा ec_params_pwm_get_duty अणु
	uपूर्णांक8_t pwm_type;  /* ec_pwm_type */
	uपूर्णांक8_t index;     /* Type-specअगरic index, or 0 अगर unique */
पूर्ण __ec_align1;

काष्ठा ec_response_pwm_get_duty अणु
	uपूर्णांक16_t duty;     /* Duty cycle, EC_PWM_MAX_DUTY = 100% */
पूर्ण __ec_align2;

/*****************************************************************************/
/*
 * Lightbar commands. This looks worse than it is. Since we only use one HOST
 * command to say "talk to the lightbar", we put the "and tell it to do X" part
 * पूर्णांकo a subcommand. We'll make separate काष्ठाs क्रम subcommands with
 * dअगरferent input args, so that we know how much to expect.
 */
#घोषणा EC_CMD_LIGHTBAR_CMD 0x0028

काष्ठा rgb_s अणु
	uपूर्णांक8_t r, g, b;
पूर्ण __ec_toकरो_unpacked;

#घोषणा LB_BATTERY_LEVELS 4

/*
 * List of tweakable parameters. NOTE: It's __packed so it can be sent in a
 * host command, but the alignment is the same regardless. Keep it that way.
 */
काष्ठा lightbar_params_v0 अणु
	/* Timing */
	पूर्णांक32_t google_ramp_up;
	पूर्णांक32_t google_ramp_करोwn;
	पूर्णांक32_t s3s0_ramp_up;
	पूर्णांक32_t s0_tick_delay[2];		/* AC=0/1 */
	पूर्णांक32_t s0a_tick_delay[2];		/* AC=0/1 */
	पूर्णांक32_t s0s3_ramp_करोwn;
	पूर्णांक32_t s3_sleep_क्रम;
	पूर्णांक32_t s3_ramp_up;
	पूर्णांक32_t s3_ramp_करोwn;

	/* Oscillation */
	uपूर्णांक8_t new_s0;
	uपूर्णांक8_t osc_min[2];			/* AC=0/1 */
	uपूर्णांक8_t osc_max[2];			/* AC=0/1 */
	uपूर्णांक8_t w_ofs[2];			/* AC=0/1 */

	/* Brightness limits based on the backlight and AC. */
	uपूर्णांक8_t bright_bl_off_fixed[2];		/* AC=0/1 */
	uपूर्णांक8_t bright_bl_on_min[2];		/* AC=0/1 */
	uपूर्णांक8_t bright_bl_on_max[2];		/* AC=0/1 */

	/* Battery level thresholds */
	uपूर्णांक8_t battery_threshold[LB_BATTERY_LEVELS - 1];

	/* Map [AC][battery_level] to color index */
	uपूर्णांक8_t s0_idx[2][LB_BATTERY_LEVELS];	/* AP is running */
	uपूर्णांक8_t s3_idx[2][LB_BATTERY_LEVELS];	/* AP is sleeping */

	/* Color palette */
	काष्ठा rgb_s color[8];			/* 0-3 are Google colors */
पूर्ण __ec_toकरो_packed;

काष्ठा lightbar_params_v1 अणु
	/* Timing */
	पूर्णांक32_t google_ramp_up;
	पूर्णांक32_t google_ramp_करोwn;
	पूर्णांक32_t s3s0_ramp_up;
	पूर्णांक32_t s0_tick_delay[2];		/* AC=0/1 */
	पूर्णांक32_t s0a_tick_delay[2];		/* AC=0/1 */
	पूर्णांक32_t s0s3_ramp_करोwn;
	पूर्णांक32_t s3_sleep_क्रम;
	पूर्णांक32_t s3_ramp_up;
	पूर्णांक32_t s3_ramp_करोwn;
	पूर्णांक32_t s5_ramp_up;
	पूर्णांक32_t s5_ramp_करोwn;
	पूर्णांक32_t tap_tick_delay;
	पूर्णांक32_t tap_gate_delay;
	पूर्णांक32_t tap_display_समय;

	/* Tap-क्रम-battery params */
	uपूर्णांक8_t tap_pct_red;
	uपूर्णांक8_t tap_pct_green;
	uपूर्णांक8_t tap_seg_min_on;
	uपूर्णांक8_t tap_seg_max_on;
	uपूर्णांक8_t tap_seg_osc;
	uपूर्णांक8_t tap_idx[3];

	/* Oscillation */
	uपूर्णांक8_t osc_min[2];			/* AC=0/1 */
	uपूर्णांक8_t osc_max[2];			/* AC=0/1 */
	uपूर्णांक8_t w_ofs[2];			/* AC=0/1 */

	/* Brightness limits based on the backlight and AC. */
	uपूर्णांक8_t bright_bl_off_fixed[2];		/* AC=0/1 */
	uपूर्णांक8_t bright_bl_on_min[2];		/* AC=0/1 */
	uपूर्णांक8_t bright_bl_on_max[2];		/* AC=0/1 */

	/* Battery level thresholds */
	uपूर्णांक8_t battery_threshold[LB_BATTERY_LEVELS - 1];

	/* Map [AC][battery_level] to color index */
	uपूर्णांक8_t s0_idx[2][LB_BATTERY_LEVELS];	/* AP is running */
	uपूर्णांक8_t s3_idx[2][LB_BATTERY_LEVELS];	/* AP is sleeping */

	/* s5: single color pulse on inhibited घातer-up */
	uपूर्णांक8_t s5_idx;

	/* Color palette */
	काष्ठा rgb_s color[8];			/* 0-3 are Google colors */
पूर्ण __ec_toकरो_packed;

/* Lightbar command params v2
 * crbug.com/467716
 *
 * lightbar_parms_v1 was too big क्रम i2c, thereक्रमe in v2, we split them up by
 * logical groups to make it more manageable ( < 120 bytes).
 *
 * NOTE: Each of these groups must be less than 120 bytes.
 */

काष्ठा lightbar_params_v2_timing अणु
	/* Timing */
	पूर्णांक32_t google_ramp_up;
	पूर्णांक32_t google_ramp_करोwn;
	पूर्णांक32_t s3s0_ramp_up;
	पूर्णांक32_t s0_tick_delay[2];		/* AC=0/1 */
	पूर्णांक32_t s0a_tick_delay[2];		/* AC=0/1 */
	पूर्णांक32_t s0s3_ramp_करोwn;
	पूर्णांक32_t s3_sleep_क्रम;
	पूर्णांक32_t s3_ramp_up;
	पूर्णांक32_t s3_ramp_करोwn;
	पूर्णांक32_t s5_ramp_up;
	पूर्णांक32_t s5_ramp_करोwn;
	पूर्णांक32_t tap_tick_delay;
	पूर्णांक32_t tap_gate_delay;
	पूर्णांक32_t tap_display_समय;
पूर्ण __ec_toकरो_packed;

काष्ठा lightbar_params_v2_tap अणु
	/* Tap-क्रम-battery params */
	uपूर्णांक8_t tap_pct_red;
	uपूर्णांक8_t tap_pct_green;
	uपूर्णांक8_t tap_seg_min_on;
	uपूर्णांक8_t tap_seg_max_on;
	uपूर्णांक8_t tap_seg_osc;
	uपूर्णांक8_t tap_idx[3];
पूर्ण __ec_toकरो_packed;

काष्ठा lightbar_params_v2_oscillation अणु
	/* Oscillation */
	uपूर्णांक8_t osc_min[2];			/* AC=0/1 */
	uपूर्णांक8_t osc_max[2];			/* AC=0/1 */
	uपूर्णांक8_t w_ofs[2];			/* AC=0/1 */
पूर्ण __ec_toकरो_packed;

काष्ठा lightbar_params_v2_brightness अणु
	/* Brightness limits based on the backlight and AC. */
	uपूर्णांक8_t bright_bl_off_fixed[2];		/* AC=0/1 */
	uपूर्णांक8_t bright_bl_on_min[2];		/* AC=0/1 */
	uपूर्णांक8_t bright_bl_on_max[2];		/* AC=0/1 */
पूर्ण __ec_toकरो_packed;

काष्ठा lightbar_params_v2_thresholds अणु
	/* Battery level thresholds */
	uपूर्णांक8_t battery_threshold[LB_BATTERY_LEVELS - 1];
पूर्ण __ec_toकरो_packed;

काष्ठा lightbar_params_v2_colors अणु
	/* Map [AC][battery_level] to color index */
	uपूर्णांक8_t s0_idx[2][LB_BATTERY_LEVELS];	/* AP is running */
	uपूर्णांक8_t s3_idx[2][LB_BATTERY_LEVELS];	/* AP is sleeping */

	/* s5: single color pulse on inhibited घातer-up */
	uपूर्णांक8_t s5_idx;

	/* Color palette */
	काष्ठा rgb_s color[8];			/* 0-3 are Google colors */
पूर्ण __ec_toकरो_packed;

/* Lightbar program. */
#घोषणा EC_LB_PROG_LEN 192
काष्ठा lightbar_program अणु
	uपूर्णांक8_t size;
	uपूर्णांक8_t data[EC_LB_PROG_LEN];
पूर्ण __ec_toकरो_unpacked;

काष्ठा ec_params_lightbar अणु
	uपूर्णांक8_t cmd;		      /* Command (see क्रमागत lightbar_command) */
	जोड़ अणु
		/*
		 * The following commands have no args:
		 *
		 * dump, off, on, init, get_seq, get_params_v0, get_params_v1,
		 * version, get_brightness, get_demo, suspend, resume,
		 * get_params_v2_timing, get_params_v2_tap, get_params_v2_osc,
		 * get_params_v2_bright, get_params_v2_thlds,
		 * get_params_v2_colors
		 *
		 * Don't use an empty काष्ठा, because C++ hates that.
		 */

		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t num;
		पूर्ण set_brightness, seq, demo;

		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t ctrl, reg, value;
		पूर्ण reg;

		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t led, red, green, blue;
		पूर्ण set_rgb;

		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t led;
		पूर्ण get_rgb;

		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t enable;
		पूर्ण manual_suspend_ctrl;

		काष्ठा lightbar_params_v0 set_params_v0;
		काष्ठा lightbar_params_v1 set_params_v1;

		काष्ठा lightbar_params_v2_timing set_v2par_timing;
		काष्ठा lightbar_params_v2_tap set_v2par_tap;
		काष्ठा lightbar_params_v2_oscillation set_v2par_osc;
		काष्ठा lightbar_params_v2_brightness set_v2par_bright;
		काष्ठा lightbar_params_v2_thresholds set_v2par_thlds;
		काष्ठा lightbar_params_v2_colors set_v2par_colors;

		काष्ठा lightbar_program set_program;
	पूर्ण;
पूर्ण __ec_toकरो_packed;

काष्ठा ec_response_lightbar अणु
	जोड़ अणु
		काष्ठा __ec_toकरो_unpacked अणु
			काष्ठा __ec_toकरो_unpacked अणु
				uपूर्णांक8_t reg;
				uपूर्णांक8_t ic0;
				uपूर्णांक8_t ic1;
			पूर्ण vals[23];
		पूर्ण dump;

		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t num;
		पूर्ण get_seq, get_brightness, get_demo;

		काष्ठा lightbar_params_v0 get_params_v0;
		काष्ठा lightbar_params_v1 get_params_v1;


		काष्ठा lightbar_params_v2_timing get_params_v2_timing;
		काष्ठा lightbar_params_v2_tap get_params_v2_tap;
		काष्ठा lightbar_params_v2_oscillation get_params_v2_osc;
		काष्ठा lightbar_params_v2_brightness get_params_v2_bright;
		काष्ठा lightbar_params_v2_thresholds get_params_v2_thlds;
		काष्ठा lightbar_params_v2_colors get_params_v2_colors;

		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक32_t num;
			uपूर्णांक32_t flags;
		पूर्ण version;

		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t red, green, blue;
		पूर्ण get_rgb;

		/*
		 * The following commands have no response:
		 *
		 * off, on, init, set_brightness, seq, reg, set_rgb, demo,
		 * set_params_v0, set_params_v1, set_program,
		 * manual_suspend_ctrl, suspend, resume, set_v2par_timing,
		 * set_v2par_tap, set_v2par_osc, set_v2par_bright,
		 * set_v2par_thlds, set_v2par_colors
		 */
	पूर्ण;
पूर्ण __ec_toकरो_packed;

/* Lightbar commands */
क्रमागत lightbar_command अणु
	LIGHTBAR_CMD_DUMP = 0,
	LIGHTBAR_CMD_OFF = 1,
	LIGHTBAR_CMD_ON = 2,
	LIGHTBAR_CMD_INIT = 3,
	LIGHTBAR_CMD_SET_BRIGHTNESS = 4,
	LIGHTBAR_CMD_SEQ = 5,
	LIGHTBAR_CMD_REG = 6,
	LIGHTBAR_CMD_SET_RGB = 7,
	LIGHTBAR_CMD_GET_SEQ = 8,
	LIGHTBAR_CMD_DEMO = 9,
	LIGHTBAR_CMD_GET_PARAMS_V0 = 10,
	LIGHTBAR_CMD_SET_PARAMS_V0 = 11,
	LIGHTBAR_CMD_VERSION = 12,
	LIGHTBAR_CMD_GET_BRIGHTNESS = 13,
	LIGHTBAR_CMD_GET_RGB = 14,
	LIGHTBAR_CMD_GET_DEMO = 15,
	LIGHTBAR_CMD_GET_PARAMS_V1 = 16,
	LIGHTBAR_CMD_SET_PARAMS_V1 = 17,
	LIGHTBAR_CMD_SET_PROGRAM = 18,
	LIGHTBAR_CMD_MANUAL_SUSPEND_CTRL = 19,
	LIGHTBAR_CMD_SUSPEND = 20,
	LIGHTBAR_CMD_RESUME = 21,
	LIGHTBAR_CMD_GET_PARAMS_V2_TIMING = 22,
	LIGHTBAR_CMD_SET_PARAMS_V2_TIMING = 23,
	LIGHTBAR_CMD_GET_PARAMS_V2_TAP = 24,
	LIGHTBAR_CMD_SET_PARAMS_V2_TAP = 25,
	LIGHTBAR_CMD_GET_PARAMS_V2_OSCILLATION = 26,
	LIGHTBAR_CMD_SET_PARAMS_V2_OSCILLATION = 27,
	LIGHTBAR_CMD_GET_PARAMS_V2_BRIGHTNESS = 28,
	LIGHTBAR_CMD_SET_PARAMS_V2_BRIGHTNESS = 29,
	LIGHTBAR_CMD_GET_PARAMS_V2_THRESHOLDS = 30,
	LIGHTBAR_CMD_SET_PARAMS_V2_THRESHOLDS = 31,
	LIGHTBAR_CMD_GET_PARAMS_V2_COLORS = 32,
	LIGHTBAR_CMD_SET_PARAMS_V2_COLORS = 33,
	LIGHTBAR_NUM_CMDS
पूर्ण;

/*****************************************************************************/
/* LED control commands */

#घोषणा EC_CMD_LED_CONTROL 0x0029

क्रमागत ec_led_id अणु
	/* LED to indicate battery state of अक्षरge */
	EC_LED_ID_BATTERY_LED = 0,
	/*
	 * LED to indicate प्रणाली घातer state (on or in suspend).
	 * May be on घातer button or on C-panel.
	 */
	EC_LED_ID_POWER_LED,
	/* LED on घातer adapter or its plug */
	EC_LED_ID_ADAPTER_LED,
	/* LED to indicate left side */
	EC_LED_ID_LEFT_LED,
	/* LED to indicate right side */
	EC_LED_ID_RIGHT_LED,
	/* LED to indicate recovery mode with HW_REINIT */
	EC_LED_ID_RECOVERY_HW_REINIT_LED,
	/* LED to indicate sysrq debug mode. */
	EC_LED_ID_SYSRQ_DEBUG_LED,

	EC_LED_ID_COUNT
पूर्ण;

/* LED control flags */
#घोषणा EC_LED_FLAGS_QUERY BIT(0) /* Query LED capability only */
#घोषणा EC_LED_FLAGS_AUTO  BIT(1) /* Switch LED back to स्वतःmatic control */

क्रमागत ec_led_colors अणु
	EC_LED_COLOR_RED = 0,
	EC_LED_COLOR_GREEN,
	EC_LED_COLOR_BLUE,
	EC_LED_COLOR_YELLOW,
	EC_LED_COLOR_WHITE,
	EC_LED_COLOR_AMBER,

	EC_LED_COLOR_COUNT
पूर्ण;

काष्ठा ec_params_led_control अणु
	uपूर्णांक8_t led_id;     /* Which LED to control */
	uपूर्णांक8_t flags;      /* Control flags */

	uपूर्णांक8_t brightness[EC_LED_COLOR_COUNT];
पूर्ण __ec_align1;

काष्ठा ec_response_led_control अणु
	/*
	 * Available brightness value range.
	 *
	 * Range 0 means color channel not present.
	 * Range 1 means on/off control.
	 * Other values means the LED is control by PWM.
	 */
	uपूर्णांक8_t brightness_range[EC_LED_COLOR_COUNT];
पूर्ण __ec_align1;

/*****************************************************************************/
/* Verअगरied boot commands */

/*
 * Note: command code 0x29 version 0 was VBOOT_CMD in Link EVT; it may be
 * reused क्रम other purposes with version > 0.
 */

/* Verअगरied boot hash command */
#घोषणा EC_CMD_VBOOT_HASH 0x002A

काष्ठा ec_params_vboot_hash अणु
	uपूर्णांक8_t cmd;             /* क्रमागत ec_vboot_hash_cmd */
	uपूर्णांक8_t hash_type;       /* क्रमागत ec_vboot_hash_type */
	uपूर्णांक8_t nonce_size;      /* Nonce size; may be 0 */
	uपूर्णांक8_t reserved0;       /* Reserved; set 0 */
	uपूर्णांक32_t offset;         /* Offset in flash to hash */
	uपूर्णांक32_t size;           /* Number of bytes to hash */
	uपूर्णांक8_t nonce_data[64];  /* Nonce data; ignored अगर nonce_size=0 */
पूर्ण __ec_align4;

काष्ठा ec_response_vboot_hash अणु
	uपूर्णांक8_t status;          /* क्रमागत ec_vboot_hash_status */
	uपूर्णांक8_t hash_type;       /* क्रमागत ec_vboot_hash_type */
	uपूर्णांक8_t digest_size;     /* Size of hash digest in bytes */
	uपूर्णांक8_t reserved0;       /* Ignore; will be 0 */
	uपूर्णांक32_t offset;         /* Offset in flash which was hashed */
	uपूर्णांक32_t size;           /* Number of bytes hashed */
	uपूर्णांक8_t hash_digest[64]; /* Hash digest data */
पूर्ण __ec_align4;

क्रमागत ec_vboot_hash_cmd अणु
	EC_VBOOT_HASH_GET = 0,       /* Get current hash status */
	EC_VBOOT_HASH_ABORT = 1,     /* Abort calculating current hash */
	EC_VBOOT_HASH_START = 2,     /* Start computing a new hash */
	EC_VBOOT_HASH_RECALC = 3,    /* Synchronously compute a new hash */
पूर्ण;

क्रमागत ec_vboot_hash_type अणु
	EC_VBOOT_HASH_TYPE_SHA256 = 0, /* SHA-256 */
पूर्ण;

क्रमागत ec_vboot_hash_status अणु
	EC_VBOOT_HASH_STATUS_NONE = 0, /* No hash (not started, or पातed) */
	EC_VBOOT_HASH_STATUS_DONE = 1, /* Finished computing a hash */
	EC_VBOOT_HASH_STATUS_BUSY = 2, /* Busy computing a hash */
पूर्ण;

/*
 * Special values क्रम offset क्रम EC_VBOOT_HASH_START and EC_VBOOT_HASH_RECALC.
 * If one of these is specअगरied, the EC will स्वतःmatically update offset and
 * size to the correct values क्रम the specअगरied image (RO or RW).
 */
#घोषणा EC_VBOOT_HASH_OFFSET_RO		0xfffffffe
#घोषणा EC_VBOOT_HASH_OFFSET_ACTIVE	0xfffffffd
#घोषणा EC_VBOOT_HASH_OFFSET_UPDATE	0xfffffffc

/*
 * 'RW' is vague अगर there are multiple RW images; we mean the active one,
 * so the old स्थिरant is deprecated.
 */
#घोषणा EC_VBOOT_HASH_OFFSET_RW EC_VBOOT_HASH_OFFSET_ACTIVE

/*****************************************************************************/
/*
 * Motion sense commands. We'll make separate काष्ठाs क्रम sub-commands with
 * dअगरferent input args, so that we know how much to expect.
 */
#घोषणा EC_CMD_MOTION_SENSE_CMD 0x002B

/* Motion sense commands */
क्रमागत motionsense_command अणु
	/*
	 * Dump command वापसs all motion sensor data including motion sense
	 * module flags and inभागidual sensor flags.
	 */
	MOTIONSENSE_CMD_DUMP = 0,

	/*
	 * Info command वापसs data describing the details of a given sensor,
	 * including क्रमागत motionsensor_type, क्रमागत motionsensor_location, and
	 * क्रमागत motionsensor_chip.
	 */
	MOTIONSENSE_CMD_INFO = 1,

	/*
	 * EC Rate command is a setter/getter command क्रम the EC sampling rate
	 * in milliseconds.
	 * It is per sensor, the EC run sample task  at the minimum of all
	 * sensors EC_RATE.
	 * For sensors without hardware FIFO, EC_RATE should be equals to 1/ODR
	 * to collect all the sensor samples.
	 * For sensor with hardware FIFO, EC_RATE is used as the maximal delay
	 * to process of all motion sensors in milliseconds.
	 */
	MOTIONSENSE_CMD_EC_RATE = 2,

	/*
	 * Sensor ODR command is a setter/getter command क्रम the output data
	 * rate of a specअगरic motion sensor in millihertz.
	 */
	MOTIONSENSE_CMD_SENSOR_ODR = 3,

	/*
	 * Sensor range command is a setter/getter command क्रम the range of
	 * a specअगरied motion sensor in +/-G's or +/- deg/s.
	 */
	MOTIONSENSE_CMD_SENSOR_RANGE = 4,

	/*
	 * Setter/getter command क्रम the keyboard wake angle. When the lid
	 * angle is greater than this value, keyboard wake is disabled in S3,
	 * and when the lid angle goes less than this value, keyboard wake is
	 * enabled. Note, the lid angle measurement is an approximate,
	 * un-calibrated value, hence the wake angle isn't exact.
	 */
	MOTIONSENSE_CMD_KB_WAKE_ANGLE = 5,

	/*
	 * Returns a single sensor data.
	 */
	MOTIONSENSE_CMD_DATA = 6,

	/*
	 * Return sensor fअगरo info.
	 */
	MOTIONSENSE_CMD_FIFO_INFO = 7,

	/*
	 * Insert a flush element in the fअगरo and वापस sensor fअगरo info.
	 * The host can use that element to synchronize its operation.
	 */
	MOTIONSENSE_CMD_FIFO_FLUSH = 8,

	/*
	 * Return a portion of the fअगरo.
	 */
	MOTIONSENSE_CMD_FIFO_READ = 9,

	/*
	 * Perक्रमm low level calibration.
	 * On sensors that support it, ask to करो offset calibration.
	 */
	MOTIONSENSE_CMD_PERFORM_CALIB = 10,

	/*
	 * Sensor Offset command is a setter/getter command क्रम the offset
	 * used क्रम calibration.
	 * The offsets can be calculated by the host, or via
	 * PERFORM_CALIB command.
	 */
	MOTIONSENSE_CMD_SENSOR_OFFSET = 11,

	/*
	 * List available activities क्रम a MOTION sensor.
	 * Indicates अगर they are enabled or disabled.
	 */
	MOTIONSENSE_CMD_LIST_ACTIVITIES = 12,

	/*
	 * Activity management
	 * Enable/Disable activity recognition.
	 */
	MOTIONSENSE_CMD_SET_ACTIVITY = 13,

	/*
	 * Lid Angle
	 */
	MOTIONSENSE_CMD_LID_ANGLE = 14,

	/*
	 * Allow the FIFO to trigger पूर्णांकerrupt via MKBP events.
	 * By शेष the FIFO करोes not send पूर्णांकerrupt to process the FIFO
	 * until the AP is पढ़ोy or it is coming from a wakeup sensor.
	 */
	MOTIONSENSE_CMD_FIFO_INT_ENABLE = 15,

	/*
	 * Spoof the पढ़ोings of the sensors.  The spoofed पढ़ोings can be set
	 * to arbitrary values, or will lock to the last पढ़ो actual values.
	 */
	MOTIONSENSE_CMD_SPOOF = 16,

	/* Set lid angle क्रम tablet mode detection. */
	MOTIONSENSE_CMD_TABLET_MODE_LID_ANGLE = 17,

	/*
	 * Sensor Scale command is a setter/getter command क्रम the calibration
	 * scale.
	 */
	MOTIONSENSE_CMD_SENSOR_SCALE = 18,

	/* Number of motionsense sub-commands. */
	MOTIONSENSE_NUM_CMDS
पूर्ण;

/* List of motion sensor types. */
क्रमागत motionsensor_type अणु
	MOTIONSENSE_TYPE_ACCEL = 0,
	MOTIONSENSE_TYPE_GYRO = 1,
	MOTIONSENSE_TYPE_MAG = 2,
	MOTIONSENSE_TYPE_PROX = 3,
	MOTIONSENSE_TYPE_LIGHT = 4,
	MOTIONSENSE_TYPE_ACTIVITY = 5,
	MOTIONSENSE_TYPE_BARO = 6,
	MOTIONSENSE_TYPE_SYNC = 7,
	MOTIONSENSE_TYPE_MAX,
पूर्ण;

/* List of motion sensor locations. */
क्रमागत motionsensor_location अणु
	MOTIONSENSE_LOC_BASE = 0,
	MOTIONSENSE_LOC_LID = 1,
	MOTIONSENSE_LOC_CAMERA = 2,
	MOTIONSENSE_LOC_MAX,
पूर्ण;

/* List of motion sensor chips. */
क्रमागत motionsensor_chip अणु
	MOTIONSENSE_CHIP_KXCJ9 = 0,
	MOTIONSENSE_CHIP_LSM6DS0 = 1,
	MOTIONSENSE_CHIP_BMI160 = 2,
	MOTIONSENSE_CHIP_SI1141 = 3,
	MOTIONSENSE_CHIP_SI1142 = 4,
	MOTIONSENSE_CHIP_SI1143 = 5,
	MOTIONSENSE_CHIP_KX022 = 6,
	MOTIONSENSE_CHIP_L3GD20H = 7,
	MOTIONSENSE_CHIP_BMA255 = 8,
	MOTIONSENSE_CHIP_BMP280 = 9,
	MOTIONSENSE_CHIP_OPT3001 = 10,
	MOTIONSENSE_CHIP_BH1730 = 11,
	MOTIONSENSE_CHIP_GPIO = 12,
	MOTIONSENSE_CHIP_LIS2DH = 13,
	MOTIONSENSE_CHIP_LSM6DSM = 14,
	MOTIONSENSE_CHIP_LIS2DE = 15,
	MOTIONSENSE_CHIP_LIS2MDL = 16,
	MOTIONSENSE_CHIP_LSM6DS3 = 17,
	MOTIONSENSE_CHIP_LSM6DSO = 18,
	MOTIONSENSE_CHIP_LNG2DM = 19,
	MOTIONSENSE_CHIP_MAX,
पूर्ण;

/* List of orientation positions */
क्रमागत motionsensor_orientation अणु
	MOTIONSENSE_ORIENTATION_LANDSCAPE = 0,
	MOTIONSENSE_ORIENTATION_PORTRAIT = 1,
	MOTIONSENSE_ORIENTATION_UPSIDE_DOWN_PORTRAIT = 2,
	MOTIONSENSE_ORIENTATION_UPSIDE_DOWN_LANDSCAPE = 3,
	MOTIONSENSE_ORIENTATION_UNKNOWN = 4,
पूर्ण;

काष्ठा ec_response_motion_sensor_data अणु
	/* Flags क्रम each sensor. */
	uपूर्णांक8_t flags;
	/* Sensor number the data comes from. */
	uपूर्णांक8_t sensor_num;
	/* Each sensor is up to 3-axis. */
	जोड़ अणु
		पूर्णांक16_t             data[3];
		काष्ठा __ec_toकरो_packed अणु
			uपूर्णांक16_t    reserved;
			uपूर्णांक32_t    बारtamp;
		पूर्ण;
		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t     activity; /* motionsensor_activity */
			uपूर्णांक8_t     state;
			पूर्णांक16_t     add_info[2];
		पूर्ण;
	पूर्ण;
पूर्ण __ec_toकरो_packed;

/* Note: used in ec_response_get_next_data */
काष्ठा ec_response_motion_sense_fअगरo_info अणु
	/* Size of the fअगरo */
	uपूर्णांक16_t size;
	/* Amount of space used in the fअगरo */
	uपूर्णांक16_t count;
	/* Timestamp recorded in us.
	 * aka accurate बारtamp when host event was triggered.
	 */
	uपूर्णांक32_t बारtamp;
	/* Total amount of vector lost */
	uपूर्णांक16_t total_lost;
	/* Lost events since the last fअगरo_info, per sensors */
	uपूर्णांक16_t lost[];
पूर्ण __ec_toकरो_packed;

काष्ठा ec_response_motion_sense_fअगरo_data अणु
	uपूर्णांक32_t number_data;
	काष्ठा ec_response_motion_sensor_data data[];
पूर्ण __ec_toकरो_packed;

/* List supported activity recognition */
क्रमागत motionsensor_activity अणु
	MOTIONSENSE_ACTIVITY_RESERVED = 0,
	MOTIONSENSE_ACTIVITY_SIG_MOTION = 1,
	MOTIONSENSE_ACTIVITY_DOUBLE_TAP = 2,
	MOTIONSENSE_ACTIVITY_ORIENTATION = 3,
पूर्ण;

काष्ठा ec_motion_sense_activity अणु
	uपूर्णांक8_t sensor_num;
	uपूर्णांक8_t activity; /* one of क्रमागत motionsensor_activity */
	uपूर्णांक8_t enable;   /* 1: enable, 0: disable */
	uपूर्णांक8_t reserved;
	uपूर्णांक16_t parameters[3]; /* activity dependent parameters */
पूर्ण __ec_toकरो_unpacked;

/* Module flag masks used क्रम the dump sub-command. */
#घोषणा MOTIONSENSE_MODULE_FLAG_ACTIVE BIT(0)

/* Sensor flag masks used क्रम the dump sub-command. */
#घोषणा MOTIONSENSE_SENSOR_FLAG_PRESENT BIT(0)

/*
 * Flush entry क्रम synchronization.
 * data contains समय stamp
 */
#घोषणा MOTIONSENSE_SENSOR_FLAG_FLUSH BIT(0)
#घोषणा MOTIONSENSE_SENSOR_FLAG_TIMESTAMP BIT(1)
#घोषणा MOTIONSENSE_SENSOR_FLAG_WAKEUP BIT(2)
#घोषणा MOTIONSENSE_SENSOR_FLAG_TABLET_MODE BIT(3)
#घोषणा MOTIONSENSE_SENSOR_FLAG_ODR BIT(4)

/*
 * Send this value क्रम the data element to only perक्रमm a पढ़ो. If you
 * send any other value, the EC will पूर्णांकerpret it as data to set and will
 * वापस the actual value set.
 */
#घोषणा EC_MOTION_SENSE_NO_VALUE -1

#घोषणा EC_MOTION_SENSE_INVALID_CALIB_TEMP 0x8000

/* MOTIONSENSE_CMD_SENSOR_OFFSET subcommand flag */
/* Set Calibration inक्रमmation */
#घोषणा MOTION_SENSE_SET_OFFSET BIT(0)

/* Default Scale value, factor 1. */
#घोषणा MOTION_SENSE_DEFAULT_SCALE BIT(15)

#घोषणा LID_ANGLE_UNRELIABLE 500

क्रमागत motionsense_spoof_mode अणु
	/* Disable spoof mode. */
	MOTIONSENSE_SPOOF_MODE_DISABLE = 0,

	/* Enable spoof mode, but use provided component values. */
	MOTIONSENSE_SPOOF_MODE_CUSTOM,

	/* Enable spoof mode, but use the current sensor values. */
	MOTIONSENSE_SPOOF_MODE_LOCK_CURRENT,

	/* Query the current spoof mode status क्रम the sensor. */
	MOTIONSENSE_SPOOF_MODE_QUERY,
पूर्ण;

काष्ठा ec_params_motion_sense अणु
	uपूर्णांक8_t cmd;
	जोड़ अणु
		/* Used क्रम MOTIONSENSE_CMD_DUMP. */
		काष्ठा __ec_toकरो_unpacked अणु
			/*
			 * Maximal number of sensor the host is expecting.
			 * 0 means the host is only पूर्णांकerested in the number
			 * of sensors controlled by the EC.
			 */
			uपूर्णांक8_t max_sensor_count;
		पूर्ण dump;

		/*
		 * Used क्रम MOTIONSENSE_CMD_KB_WAKE_ANGLE.
		 */
		काष्ठा __ec_toकरो_unpacked अणु
			/* Data to set or EC_MOTION_SENSE_NO_VALUE to पढ़ो.
			 * kb_wake_angle: angle to wakup AP.
			 */
			पूर्णांक16_t data;
		पूर्ण kb_wake_angle;

		/*
		 * Used क्रम MOTIONSENSE_CMD_INFO, MOTIONSENSE_CMD_DATA
		 * and MOTIONSENSE_CMD_PERFORM_CALIB.
		 */
		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t sensor_num;
		पूर्ण info, info_3, data, fअगरo_flush, perक्रमm_calib,
				list_activities;

		/*
		 * Used क्रम MOTIONSENSE_CMD_EC_RATE, MOTIONSENSE_CMD_SENSOR_ODR
		 * and MOTIONSENSE_CMD_SENSOR_RANGE.
		 */
		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t sensor_num;

			/* Rounding flag, true क्रम round-up, false क्रम करोwn. */
			uपूर्णांक8_t roundup;

			uपूर्णांक16_t reserved;

			/* Data to set or EC_MOTION_SENSE_NO_VALUE to पढ़ो. */
			पूर्णांक32_t data;
		पूर्ण ec_rate, sensor_odr, sensor_range;

		/* Used क्रम MOTIONSENSE_CMD_SENSOR_OFFSET */
		काष्ठा __ec_toकरो_packed अणु
			uपूर्णांक8_t sensor_num;

			/*
			 * bit 0: If set (MOTION_SENSE_SET_OFFSET), set
			 * the calibration inक्रमmation in the EC.
			 * If unset, just retrieve calibration inक्रमmation.
			 */
			uपूर्णांक16_t flags;

			/*
			 * Temperature at calibration, in units of 0.01 C
			 * 0x8000: invalid / unknown.
			 * 0x0: 0C
			 * 0x7fff: +327.67C
			 */
			पूर्णांक16_t temp;

			/*
			 * Offset क्रम calibration.
			 * Unit:
			 * Accelerometer: 1/1024 g
			 * Gyro:          1/1024 deg/s
			 * Compass:       1/16 uT
			 */
			पूर्णांक16_t offset[3];
		पूर्ण sensor_offset;

		/* Used क्रम MOTIONSENSE_CMD_SENSOR_SCALE */
		काष्ठा __ec_toकरो_packed अणु
			uपूर्णांक8_t sensor_num;

			/*
			 * bit 0: If set (MOTION_SENSE_SET_OFFSET), set
			 * the calibration inक्रमmation in the EC.
			 * If unset, just retrieve calibration inक्रमmation.
			 */
			uपूर्णांक16_t flags;

			/*
			 * Temperature at calibration, in units of 0.01 C
			 * 0x8000: invalid / unknown.
			 * 0x0: 0C
			 * 0x7fff: +327.67C
			 */
			पूर्णांक16_t temp;

			/*
			 * Scale क्रम calibration:
			 * By शेष scale is 1, it is encoded on 16bits:
			 * 1 = BIT(15)
			 * ~2 = 0xFFFF
			 * ~0 = 0.
			 */
			uपूर्णांक16_t scale[3];
		पूर्ण sensor_scale;


		/* Used क्रम MOTIONSENSE_CMD_FIFO_INFO */
		/* (no params) */

		/* Used क्रम MOTIONSENSE_CMD_FIFO_READ */
		काष्ठा __ec_toकरो_unpacked अणु
			/*
			 * Number of expected vector to वापस.
			 * EC may वापस less or 0 अगर none available.
			 */
			uपूर्णांक32_t max_data_vector;
		पूर्ण fअगरo_पढ़ो;

		काष्ठा ec_motion_sense_activity set_activity;

		/* Used क्रम MOTIONSENSE_CMD_LID_ANGLE */
		/* (no params) */

		/* Used क्रम MOTIONSENSE_CMD_FIFO_INT_ENABLE */
		काष्ठा __ec_toकरो_unpacked अणु
			/*
			 * 1: enable, 0 disable fअगरo,
			 * EC_MOTION_SENSE_NO_VALUE वापस value.
			 */
			पूर्णांक8_t enable;
		पूर्ण fअगरo_पूर्णांक_enable;

		/* Used क्रम MOTIONSENSE_CMD_SPOOF */
		काष्ठा __ec_toकरो_packed अणु
			uपूर्णांक8_t sensor_id;

			/* See क्रमागत motionsense_spoof_mode. */
			uपूर्णांक8_t spoof_enable;

			/* Ignored, used क्रम alignment. */
			uपूर्णांक8_t reserved;

			/* Inभागidual component values to spoof. */
			पूर्णांक16_t components[3];
		पूर्ण spoof;

		/* Used क्रम MOTIONSENSE_CMD_TABLET_MODE_LID_ANGLE. */
		काष्ठा __ec_toकरो_unpacked अणु
			/*
			 * Lid angle threshold क्रम चयनing between tablet and
			 * clamshell mode.
			 */
			पूर्णांक16_t lid_angle;

			/*
			 * Hysteresis degree to prevent fluctuations between
			 * clamshell and tablet mode अगर lid angle keeps
			 * changing around the threshold. Lid motion driver will
			 * use lid_angle + hys_degree to trigger tablet mode and
			 * lid_angle - hys_degree to trigger clamshell mode.
			 */
			पूर्णांक16_t hys_degree;
		पूर्ण tablet_mode_threshold;
	पूर्ण;
पूर्ण __ec_toकरो_packed;

काष्ठा ec_response_motion_sense अणु
	जोड़ अणु
		/* Used क्रम MOTIONSENSE_CMD_DUMP */
		काष्ठा __ec_toकरो_unpacked अणु
			/* Flags representing the motion sensor module. */
			uपूर्णांक8_t module_flags;

			/* Number of sensors managed directly by the EC. */
			uपूर्णांक8_t sensor_count;

			/*
			 * Sensor data is truncated अगर response_max is too small
			 * क्रम holding all the data.
			 */
			काष्ठा ec_response_motion_sensor_data sensor[0];
		पूर्ण dump;

		/* Used क्रम MOTIONSENSE_CMD_INFO. */
		काष्ठा __ec_toकरो_unpacked अणु
			/* Should be element of क्रमागत motionsensor_type. */
			uपूर्णांक8_t type;

			/* Should be element of क्रमागत motionsensor_location. */
			uपूर्णांक8_t location;

			/* Should be element of क्रमागत motionsensor_chip. */
			uपूर्णांक8_t chip;
		पूर्ण info;

		/* Used क्रम MOTIONSENSE_CMD_INFO version 3 */
		काष्ठा __ec_toकरो_unpacked अणु
			/* Should be element of क्रमागत motionsensor_type. */
			uपूर्णांक8_t type;

			/* Should be element of क्रमागत motionsensor_location. */
			uपूर्णांक8_t location;

			/* Should be element of क्रमागत motionsensor_chip. */
			uपूर्णांक8_t chip;

			/* Minimum sensor sampling frequency */
			uपूर्णांक32_t min_frequency;

			/* Maximum sensor sampling frequency */
			uपूर्णांक32_t max_frequency;

			/* Max number of sensor events that could be in fअगरo */
			uपूर्णांक32_t fअगरo_max_event_count;
		पूर्ण info_3;

		/* Used क्रम MOTIONSENSE_CMD_DATA */
		काष्ठा ec_response_motion_sensor_data data;

		/*
		 * Used क्रम MOTIONSENSE_CMD_EC_RATE, MOTIONSENSE_CMD_SENSOR_ODR,
		 * MOTIONSENSE_CMD_SENSOR_RANGE,
		 * MOTIONSENSE_CMD_KB_WAKE_ANGLE,
		 * MOTIONSENSE_CMD_FIFO_INT_ENABLE and
		 * MOTIONSENSE_CMD_SPOOF.
		 */
		काष्ठा __ec_toकरो_unpacked अणु
			/* Current value of the parameter queried. */
			पूर्णांक32_t ret;
		पूर्ण ec_rate, sensor_odr, sensor_range, kb_wake_angle,
		  fअगरo_पूर्णांक_enable, spoof;

		/*
		 * Used क्रम MOTIONSENSE_CMD_SENSOR_OFFSET,
		 * PERFORM_CALIB.
		 */
		काष्ठा __ec_toकरो_unpacked  अणु
			पूर्णांक16_t temp;
			पूर्णांक16_t offset[3];
		पूर्ण sensor_offset, perक्रमm_calib;

		/* Used क्रम MOTIONSENSE_CMD_SENSOR_SCALE */
		काष्ठा __ec_toकरो_unpacked  अणु
			पूर्णांक16_t temp;
			uपूर्णांक16_t scale[3];
		पूर्ण sensor_scale;

		काष्ठा ec_response_motion_sense_fअगरo_info fअगरo_info, fअगरo_flush;

		काष्ठा ec_response_motion_sense_fअगरo_data fअगरo_पढ़ो;

		काष्ठा __ec_toकरो_packed अणु
			uपूर्णांक16_t reserved;
			uपूर्णांक32_t enabled;
			uपूर्णांक32_t disabled;
		पूर्ण list_activities;

		/* No params क्रम set activity */

		/* Used क्रम MOTIONSENSE_CMD_LID_ANGLE */
		काष्ठा __ec_toकरो_unpacked अणु
			/*
			 * Angle between 0 and 360 degree अगर available,
			 * LID_ANGLE_UNRELIABLE otherwise.
			 */
			uपूर्णांक16_t value;
		पूर्ण lid_angle;

		/* Used क्रम MOTIONSENSE_CMD_TABLET_MODE_LID_ANGLE. */
		काष्ठा __ec_toकरो_unpacked अणु
			/*
			 * Lid angle threshold क्रम चयनing between tablet and
			 * clamshell mode.
			 */
			uपूर्णांक16_t lid_angle;

			/* Hysteresis degree. */
			uपूर्णांक16_t hys_degree;
		पूर्ण tablet_mode_threshold;

	पूर्ण;
पूर्ण __ec_toकरो_packed;

/*****************************************************************************/
/* Force lid खोलो command */

/* Make lid event always खोलो */
#घोषणा EC_CMD_FORCE_LID_OPEN 0x002C

काष्ठा ec_params_क्रमce_lid_खोलो अणु
	uपूर्णांक8_t enabled;
पूर्ण __ec_align1;

/*****************************************************************************/
/* Configure the behavior of the घातer button */
#घोषणा EC_CMD_CONFIG_POWER_BUTTON 0x002D

क्रमागत ec_config_घातer_button_flags अणु
	/* Enable/Disable घातer button pulses क्रम x86 devices */
	EC_POWER_BUTTON_ENABLE_PULSE = BIT(0),
पूर्ण;

काष्ठा ec_params_config_घातer_button अणु
	/* See क्रमागत ec_config_घातer_button_flags */
	uपूर्णांक8_t flags;
पूर्ण __ec_align1;

/*****************************************************************************/
/* USB अक्षरging control commands */

/* Set USB port अक्षरging mode */
#घोषणा EC_CMD_USB_CHARGE_SET_MODE 0x0030

काष्ठा ec_params_usb_अक्षरge_set_mode अणु
	uपूर्णांक8_t usb_port_id;
	uपूर्णांक8_t mode:7;
	uपूर्णांक8_t inhibit_अक्षरge:1;
पूर्ण __ec_align1;

/*****************************************************************************/
/* Persistent storage क्रम host */

/* Maximum bytes that can be पढ़ो/written in a single command */
#घोषणा EC_PSTORE_SIZE_MAX 64

/* Get persistent storage info */
#घोषणा EC_CMD_PSTORE_INFO 0x0040

काष्ठा ec_response_pstore_info अणु
	/* Persistent storage size, in bytes */
	uपूर्णांक32_t pstore_size;
	/* Access size; पढ़ो/ग_लिखो offset and size must be a multiple of this */
	uपूर्णांक32_t access_size;
पूर्ण __ec_align4;

/*
 * Read persistent storage
 *
 * Response is params.size bytes of data.
 */
#घोषणा EC_CMD_PSTORE_READ 0x0041

काष्ठा ec_params_pstore_पढ़ो अणु
	uपूर्णांक32_t offset;   /* Byte offset to पढ़ो */
	uपूर्णांक32_t size;     /* Size to पढ़ो in bytes */
पूर्ण __ec_align4;

/* Write persistent storage */
#घोषणा EC_CMD_PSTORE_WRITE 0x0042

काष्ठा ec_params_pstore_ग_लिखो अणु
	uपूर्णांक32_t offset;   /* Byte offset to ग_लिखो */
	uपूर्णांक32_t size;     /* Size to ग_लिखो in bytes */
	uपूर्णांक8_t data[EC_PSTORE_SIZE_MAX];
पूर्ण __ec_align4;

/*****************************************************************************/
/* Real-समय घड़ी */

/* RTC params and response काष्ठाures */
काष्ठा ec_params_rtc अणु
	uपूर्णांक32_t समय;
पूर्ण __ec_align4;

काष्ठा ec_response_rtc अणु
	uपूर्णांक32_t समय;
पूर्ण __ec_align4;

/* These use ec_response_rtc */
#घोषणा EC_CMD_RTC_GET_VALUE 0x0044
#घोषणा EC_CMD_RTC_GET_ALARM 0x0045

/* These all use ec_params_rtc */
#घोषणा EC_CMD_RTC_SET_VALUE 0x0046
#घोषणा EC_CMD_RTC_SET_ALARM 0x0047

/* Pass as समय param to SET_ALARM to clear the current alarm */
#घोषणा EC_RTC_ALARM_CLEAR 0

/*****************************************************************************/
/* Port80 log access */

/* Maximum entries that can be पढ़ो/written in a single command */
#घोषणा EC_PORT80_SIZE_MAX 32

/* Get last port80 code from previous boot */
#घोषणा EC_CMD_PORT80_LAST_BOOT 0x0048
#घोषणा EC_CMD_PORT80_READ 0x0048

क्रमागत ec_port80_subcmd अणु
	EC_PORT80_GET_INFO = 0,
	EC_PORT80_READ_BUFFER,
पूर्ण;

काष्ठा ec_params_port80_पढ़ो अणु
	uपूर्णांक16_t subcmd;
	जोड़ अणु
		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक32_t offset;
			uपूर्णांक32_t num_entries;
		पूर्ण पढ़ो_buffer;
	पूर्ण;
पूर्ण __ec_toकरो_packed;

काष्ठा ec_response_port80_पढ़ो अणु
	जोड़ अणु
		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक32_t ग_लिखोs;
			uपूर्णांक32_t history_size;
			uपूर्णांक32_t last_boot;
		पूर्ण get_info;
		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक16_t codes[EC_PORT80_SIZE_MAX];
		पूर्ण data;
	पूर्ण;
पूर्ण __ec_toकरो_packed;

काष्ठा ec_response_port80_last_boot अणु
	uपूर्णांक16_t code;
पूर्ण __ec_align2;

/*****************************************************************************/
/* Temporary secure storage क्रम host verअगरied boot use */

/* Number of bytes in a vstore slot */
#घोषणा EC_VSTORE_SLOT_SIZE 64

/* Maximum number of vstore slots */
#घोषणा EC_VSTORE_SLOT_MAX 32

/* Get persistent storage info */
#घोषणा EC_CMD_VSTORE_INFO 0x0049
काष्ठा ec_response_vstore_info अणु
	/* Indicates which slots are locked */
	uपूर्णांक32_t slot_locked;
	/* Total number of slots available */
	uपूर्णांक8_t slot_count;
पूर्ण __ec_align_size1;

/*
 * Read temporary secure storage
 *
 * Response is EC_VSTORE_SLOT_SIZE bytes of data.
 */
#घोषणा EC_CMD_VSTORE_READ 0x004A

काष्ठा ec_params_vstore_पढ़ो अणु
	uपूर्णांक8_t slot; /* Slot to पढ़ो from */
पूर्ण __ec_align1;

काष्ठा ec_response_vstore_पढ़ो अणु
	uपूर्णांक8_t data[EC_VSTORE_SLOT_SIZE];
पूर्ण __ec_align1;

/*
 * Write temporary secure storage and lock it.
 */
#घोषणा EC_CMD_VSTORE_WRITE 0x004B

काष्ठा ec_params_vstore_ग_लिखो अणु
	uपूर्णांक8_t slot; /* Slot to ग_लिखो to */
	uपूर्णांक8_t data[EC_VSTORE_SLOT_SIZE];
पूर्ण __ec_align1;

/*****************************************************************************/
/* Thermal engine commands. Note that there are two implementations. We'll
 * reuse the command number, but the data and behavior is incompatible.
 * Version 0 is what originally shipped on Link.
 * Version 1 separates the CPU thermal limits from the fan control.
 */

#घोषणा EC_CMD_THERMAL_SET_THRESHOLD 0x0050
#घोषणा EC_CMD_THERMAL_GET_THRESHOLD 0x0051

/* The version 0 काष्ठाs are opaque. You have to know what they are क्रम
 * the get/set commands to make any sense.
 */

/* Version 0 - set */
काष्ठा ec_params_thermal_set_threshold अणु
	uपूर्णांक8_t sensor_type;
	uपूर्णांक8_t threshold_id;
	uपूर्णांक16_t value;
पूर्ण __ec_align2;

/* Version 0 - get */
काष्ठा ec_params_thermal_get_threshold अणु
	uपूर्णांक8_t sensor_type;
	uपूर्णांक8_t threshold_id;
पूर्ण __ec_align1;

काष्ठा ec_response_thermal_get_threshold अणु
	uपूर्णांक16_t value;
पूर्ण __ec_align2;


/* The version 1 काष्ठाs are visible. */
क्रमागत ec_temp_thresholds अणु
	EC_TEMP_THRESH_WARN = 0,
	EC_TEMP_THRESH_HIGH,
	EC_TEMP_THRESH_HALT,

	EC_TEMP_THRESH_COUNT
पूर्ण;

/*
 * Thermal configuration क्रम one temperature sensor. Temps are in degrees K.
 * Zero values will be silently ignored by the thermal task.
 *
 * Set 'temp_host' value allows thermal task to trigger some event with 1 degree
 * hysteresis.
 * For example,
 *	temp_host[EC_TEMP_THRESH_HIGH] = 300 K
 *	temp_host_release[EC_TEMP_THRESH_HIGH] = 0 K
 * EC will throttle ap when temperature >= 301 K, and release throttling when
 * temperature <= 299 K.
 *
 * Set 'temp_host_release' value allows thermal task has a custom hysteresis.
 * For example,
 *	temp_host[EC_TEMP_THRESH_HIGH] = 300 K
 *	temp_host_release[EC_TEMP_THRESH_HIGH] = 295 K
 * EC will throttle ap when temperature >= 301 K, and release throttling when
 * temperature <= 294 K.
 *
 * Note that this काष्ठाure is a sub-काष्ठाure of
 * ec_params_thermal_set_threshold_v1, but मुख्यtains its alignment there.
 */
काष्ठा ec_thermal_config अणु
	uपूर्णांक32_t temp_host[EC_TEMP_THRESH_COUNT]; /* levels of hotness */
	uपूर्णांक32_t temp_host_release[EC_TEMP_THRESH_COUNT]; /* release levels */
	uपूर्णांक32_t temp_fan_off;		/* no active cooling needed */
	uपूर्णांक32_t temp_fan_max;		/* max active cooling needed */
पूर्ण __ec_align4;

/* Version 1 - get config क्रम one sensor. */
काष्ठा ec_params_thermal_get_threshold_v1 अणु
	uपूर्णांक32_t sensor_num;
पूर्ण __ec_align4;
/* This वापसs a काष्ठा ec_thermal_config */

/*
 * Version 1 - set config क्रम one sensor.
 * Use पढ़ो-modअगरy-ग_लिखो क्रम best results!
 */
काष्ठा ec_params_thermal_set_threshold_v1 अणु
	uपूर्णांक32_t sensor_num;
	काष्ठा ec_thermal_config cfg;
पूर्ण __ec_align4;
/* This वापसs no data */

/****************************************************************************/

/* Toggle स्वतःmatic fan control */
#घोषणा EC_CMD_THERMAL_AUTO_FAN_CTRL 0x0052

/* Version 1 of input params */
काष्ठा ec_params_स्वतः_fan_ctrl_v1 अणु
	uपूर्णांक8_t fan_idx;
पूर्ण __ec_align1;

/* Get/Set TMP006 calibration data */
#घोषणा EC_CMD_TMP006_GET_CALIBRATION 0x0053
#घोषणा EC_CMD_TMP006_SET_CALIBRATION 0x0054

/*
 * The original TMP006 calibration only needed four params, but now we need
 * more. Since the algorithm is nothing but magic numbers anyway, we'll leave
 * the params opaque. The v1 "get" response will include the algorithm number
 * and how many params it requires. That way we can change the EC code without
 * needing to update this file. We can also use a dअगरferent algorithm on each
 * sensor.
 */

/* This is the same काष्ठा क्रम both v0 and v1. */
काष्ठा ec_params_पंचांगp006_get_calibration अणु
	uपूर्णांक8_t index;
पूर्ण __ec_align1;

/* Version 0 */
काष्ठा ec_response_पंचांगp006_get_calibration_v0 अणु
	भग्न s0;
	भग्न b0;
	भग्न b1;
	भग्न b2;
पूर्ण __ec_align4;

काष्ठा ec_params_पंचांगp006_set_calibration_v0 अणु
	uपूर्णांक8_t index;
	uपूर्णांक8_t reserved[3];
	भग्न s0;
	भग्न b0;
	भग्न b1;
	भग्न b2;
पूर्ण __ec_align4;

/* Version 1 */
काष्ठा ec_response_पंचांगp006_get_calibration_v1 अणु
	uपूर्णांक8_t algorithm;
	uपूर्णांक8_t num_params;
	uपूर्णांक8_t reserved[2];
	भग्न val[];
पूर्ण __ec_align4;

काष्ठा ec_params_पंचांगp006_set_calibration_v1 अणु
	uपूर्णांक8_t index;
	uपूर्णांक8_t algorithm;
	uपूर्णांक8_t num_params;
	uपूर्णांक8_t reserved;
	भग्न val[];
पूर्ण __ec_align4;


/* Read raw TMP006 data */
#घोषणा EC_CMD_TMP006_GET_RAW 0x0055

काष्ठा ec_params_पंचांगp006_get_raw अणु
	uपूर्णांक8_t index;
पूर्ण __ec_align1;

काष्ठा ec_response_पंचांगp006_get_raw अणु
	पूर्णांक32_t t;  /* In 1/100 K */
	पूर्णांक32_t v;  /* In nV */
पूर्ण __ec_align4;

/*****************************************************************************/
/* MKBP - Matrix KeyBoard Protocol */

/*
 * Read key state
 *
 * Returns raw data क्रम keyboard cols; see ec_response_mkbp_info.cols क्रम
 * expected response size.
 *
 * NOTE: This has been superseded by EC_CMD_MKBP_GET_NEXT_EVENT.  If you wish
 * to obtain the instantaneous state, use EC_CMD_MKBP_INFO with the type
 * EC_MKBP_INFO_CURRENT and event EC_MKBP_EVENT_KEY_MATRIX.
 */
#घोषणा EC_CMD_MKBP_STATE 0x0060

/*
 * Provide inक्रमmation about various MKBP things.  See क्रमागत ec_mkbp_info_type.
 */
#घोषणा EC_CMD_MKBP_INFO 0x0061

काष्ठा ec_response_mkbp_info अणु
	uपूर्णांक32_t rows;
	uपूर्णांक32_t cols;
	/* Formerly "switches", which was 0. */
	uपूर्णांक8_t reserved;
पूर्ण __ec_align_size1;

काष्ठा ec_params_mkbp_info अणु
	uपूर्णांक8_t info_type;
	uपूर्णांक8_t event_type;
पूर्ण __ec_align1;

क्रमागत ec_mkbp_info_type अणु
	/*
	 * Info about the keyboard matrix: number of rows and columns.
	 *
	 * Returns काष्ठा ec_response_mkbp_info.
	 */
	EC_MKBP_INFO_KBD = 0,

	/*
	 * For buttons and चयनes, info about which specअगरically are
	 * supported.  event_type must be set to one of the values in क्रमागत
	 * ec_mkbp_event.
	 *
	 * For EC_MKBP_EVENT_BUTTON and EC_MKBP_EVENT_SWITCH, वापसs a 4 byte
	 * biपंचांगask indicating which buttons or चयनes are present.  See the
	 * bit inidices below.
	 */
	EC_MKBP_INFO_SUPPORTED = 1,

	/*
	 * Instantaneous state of buttons and चयनes.
	 *
	 * event_type must be set to one of the values in क्रमागत ec_mkbp_event.
	 *
	 * For EC_MKBP_EVENT_KEY_MATRIX, वापसs uपूर्णांक8_t key_matrix[13]
	 * indicating the current state of the keyboard matrix.
	 *
	 * For EC_MKBP_EVENT_HOST_EVENT, वापस uपूर्णांक32_t host_event, the raw
	 * event state.
	 *
	 * For EC_MKBP_EVENT_BUTTON, वापसs uपूर्णांक32_t buttons, indicating the
	 * state of supported buttons.
	 *
	 * For EC_MKBP_EVENT_SWITCH, वापसs uपूर्णांक32_t चयनes, indicating the
	 * state of supported चयनes.
	 */
	EC_MKBP_INFO_CURRENT = 2,
पूर्ण;

/* Simulate key press */
#घोषणा EC_CMD_MKBP_SIMULATE_KEY 0x0062

काष्ठा ec_params_mkbp_simulate_key अणु
	uपूर्णांक8_t col;
	uपूर्णांक8_t row;
	uपूर्णांक8_t pressed;
पूर्ण __ec_align1;

#घोषणा EC_CMD_GET_KEYBOARD_ID 0x0063

काष्ठा ec_response_keyboard_id अणु
	uपूर्णांक32_t keyboard_id;
पूर्ण __ec_align4;

क्रमागत keyboard_id अणु
	KEYBOARD_ID_UNSUPPORTED = 0,
	KEYBOARD_ID_UNREADABLE = 0xffffffff,
पूर्ण;

/* Configure keyboard scanning */
#घोषणा EC_CMD_MKBP_SET_CONFIG 0x0064
#घोषणा EC_CMD_MKBP_GET_CONFIG 0x0065

/* flags */
क्रमागत mkbp_config_flags अणु
	EC_MKBP_FLAGS_ENABLE = 1,	/* Enable keyboard scanning */
पूर्ण;

क्रमागत mkbp_config_valid अणु
	EC_MKBP_VALID_SCAN_PERIOD		= BIT(0),
	EC_MKBP_VALID_POLL_TIMEOUT		= BIT(1),
	EC_MKBP_VALID_MIN_POST_SCAN_DELAY	= BIT(3),
	EC_MKBP_VALID_OUTPUT_SETTLE		= BIT(4),
	EC_MKBP_VALID_DEBOUNCE_DOWN		= BIT(5),
	EC_MKBP_VALID_DEBOUNCE_UP		= BIT(6),
	EC_MKBP_VALID_FIFO_MAX_DEPTH		= BIT(7),
पूर्ण;

/*
 * Configuration क्रम our key scanning algorithm.
 *
 * Note that this is used as a sub-काष्ठाure of
 * ec_अणुparams/responseपूर्ण_mkbp_get_config.
 */
काष्ठा ec_mkbp_config अणु
	uपूर्णांक32_t valid_mask;		/* valid fields */
	uपूर्णांक8_t flags;		/* some flags (क्रमागत mkbp_config_flags) */
	uपूर्णांक8_t valid_flags;		/* which flags are valid */
	uपूर्णांक16_t scan_period_us;	/* period between start of scans */
	/* revert to पूर्णांकerrupt mode after no activity क्रम this दीर्घ */
	uपूर्णांक32_t poll_समयout_us;
	/*
	 * minimum post-scan relax समय. Once we finish a scan we check
	 * the समय until we are due to start the next one. If this समय is
	 * लघुer this field, we use this instead.
	 */
	uपूर्णांक16_t min_post_scan_delay_us;
	/* delay between setting up output and रुकोing क्रम it to settle */
	uपूर्णांक16_t output_settle_us;
	uपूर्णांक16_t debounce_करोwn_us;	/* समय क्रम debounce on key करोwn */
	uपूर्णांक16_t debounce_up_us;	/* समय क्रम debounce on key up */
	/* maximum depth to allow क्रम fअगरo (0 = no keyscan output) */
	uपूर्णांक8_t fअगरo_max_depth;
पूर्ण __ec_align_size1;

काष्ठा ec_params_mkbp_set_config अणु
	काष्ठा ec_mkbp_config config;
पूर्ण __ec_align_size1;

काष्ठा ec_response_mkbp_get_config अणु
	काष्ठा ec_mkbp_config config;
पूर्ण __ec_align_size1;

/* Run the key scan emulation */
#घोषणा EC_CMD_KEYSCAN_SEQ_CTRL 0x0066

क्रमागत ec_keyscan_seq_cmd अणु
	EC_KEYSCAN_SEQ_STATUS = 0,	/* Get status inक्रमmation */
	EC_KEYSCAN_SEQ_CLEAR = 1,	/* Clear sequence */
	EC_KEYSCAN_SEQ_ADD = 2,		/* Add item to sequence */
	EC_KEYSCAN_SEQ_START = 3,	/* Start running sequence */
	EC_KEYSCAN_SEQ_COLLECT = 4,	/* Collect sequence summary data */
पूर्ण;

क्रमागत ec_collect_flags अणु
	/*
	 * Indicates this scan was processed by the EC. Due to timing, some
	 * scans may be skipped.
	 */
	EC_KEYSCAN_SEQ_FLAG_DONE	= BIT(0),
पूर्ण;

काष्ठा ec_collect_item अणु
	uपूर्णांक8_t flags;		/* some flags (क्रमागत ec_collect_flags) */
पूर्ण __ec_align1;

काष्ठा ec_params_keyscan_seq_ctrl अणु
	uपूर्णांक8_t cmd;	/* Command to send (क्रमागत ec_keyscan_seq_cmd) */
	जोड़ अणु
		काष्ठा __ec_align1 अणु
			uपूर्णांक8_t active;		/* still active */
			uपूर्णांक8_t num_items;	/* number of items */
			/* Current item being presented */
			uपूर्णांक8_t cur_item;
		पूर्ण status;
		काष्ठा __ec_toकरो_unpacked अणु
			/*
			 * Absolute समय क्रम this scan, measured from the
			 * start of the sequence.
			 */
			uपूर्णांक32_t समय_us;
			uपूर्णांक8_t scan[0];	/* keyscan data */
		पूर्ण add;
		काष्ठा __ec_align1 अणु
			uपूर्णांक8_t start_item;	/* First item to वापस */
			uपूर्णांक8_t num_items;	/* Number of items to वापस */
		पूर्ण collect;
	पूर्ण;
पूर्ण __ec_toकरो_packed;

काष्ठा ec_result_keyscan_seq_ctrl अणु
	जोड़ अणु
		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t num_items;	/* Number of items */
			/* Data क्रम each item */
			काष्ठा ec_collect_item item[0];
		पूर्ण collect;
	पूर्ण;
पूर्ण __ec_toकरो_packed;

/*
 * Get the next pending MKBP event.
 *
 * Returns EC_RES_UNAVAILABLE अगर there is no event pending.
 */
#घोषणा EC_CMD_GET_NEXT_EVENT 0x0067

#घोषणा EC_MKBP_HAS_MORE_EVENTS_SHIFT 7

/*
 * We use the most signअगरicant bit of the event type to indicate to the host
 * that the EC has more MKBP events available to provide.
 */
#घोषणा EC_MKBP_HAS_MORE_EVENTS BIT(EC_MKBP_HAS_MORE_EVENTS_SHIFT)

/* The mask to apply to get the raw event type */
#घोषणा EC_MKBP_EVENT_TYPE_MASK (BIT(EC_MKBP_HAS_MORE_EVENTS_SHIFT) - 1)

क्रमागत ec_mkbp_event अणु
	/* Keyboard matrix changed. The event data is the new matrix state. */
	EC_MKBP_EVENT_KEY_MATRIX = 0,

	/* New host event. The event data is 4 bytes of host event flags. */
	EC_MKBP_EVENT_HOST_EVENT = 1,

	/* New Sensor FIFO data. The event data is fअगरo_info काष्ठाure. */
	EC_MKBP_EVENT_SENSOR_FIFO = 2,

	/* The state of the non-matrixed buttons have changed. */
	EC_MKBP_EVENT_BUTTON = 3,

	/* The state of the चयनes have changed. */
	EC_MKBP_EVENT_SWITCH = 4,

	/* New Fingerprपूर्णांक sensor event, the event data is fp_events biपंचांगap. */
	EC_MKBP_EVENT_FINGERPRINT = 5,

	/*
	 * Sysrq event: send emulated sysrq. The event data is sysrq,
	 * corresponding to the key to be pressed.
	 */
	EC_MKBP_EVENT_SYSRQ = 6,

	/*
	 * New 64-bit host event.
	 * The event data is 8 bytes of host event flags.
	 */
	EC_MKBP_EVENT_HOST_EVENT64 = 7,

	/* Notअगरy the AP that something happened on CEC */
	EC_MKBP_EVENT_CEC_EVENT = 8,

	/* Send an incoming CEC message to the AP */
	EC_MKBP_EVENT_CEC_MESSAGE = 9,

	/* Number of MKBP events */
	EC_MKBP_EVENT_COUNT,
पूर्ण;
BUILD_ASSERT(EC_MKBP_EVENT_COUNT <= EC_MKBP_EVENT_TYPE_MASK);

जोड़ __ec_align_offset1 ec_response_get_next_data अणु
	uपूर्णांक8_t key_matrix[13];

	/* Unaligned */
	uपूर्णांक32_t host_event;
	uपूर्णांक64_t host_event64;

	काष्ठा __ec_toकरो_unpacked अणु
		/* For aligning the fअगरo_info */
		uपूर्णांक8_t reserved[3];
		काष्ठा ec_response_motion_sense_fअगरo_info info;
	पूर्ण sensor_fअगरo;

	uपूर्णांक32_t buttons;

	uपूर्णांक32_t चयनes;

	uपूर्णांक32_t fp_events;

	uपूर्णांक32_t sysrq;

	/* CEC events from क्रमागत mkbp_cec_event */
	uपूर्णांक32_t cec_events;
पूर्ण;

जोड़ __ec_align_offset1 ec_response_get_next_data_v1 अणु
	uपूर्णांक8_t key_matrix[16];

	/* Unaligned */
	uपूर्णांक32_t host_event;
	uपूर्णांक64_t host_event64;

	काष्ठा __ec_toकरो_unpacked अणु
		/* For aligning the fअगरo_info */
		uपूर्णांक8_t reserved[3];
		काष्ठा ec_response_motion_sense_fअगरo_info info;
	पूर्ण sensor_fअगरo;

	uपूर्णांक32_t buttons;

	uपूर्णांक32_t चयनes;

	uपूर्णांक32_t fp_events;

	uपूर्णांक32_t sysrq;

	/* CEC events from क्रमागत mkbp_cec_event */
	uपूर्णांक32_t cec_events;

	uपूर्णांक8_t cec_message[16];
पूर्ण;
BUILD_ASSERT(माप(जोड़ ec_response_get_next_data_v1) == 16);

काष्ठा ec_response_get_next_event अणु
	uपूर्णांक8_t event_type;
	/* Followed by event data अगर any */
	जोड़ ec_response_get_next_data data;
पूर्ण __ec_align1;

काष्ठा ec_response_get_next_event_v1 अणु
	uपूर्णांक8_t event_type;
	/* Followed by event data अगर any */
	जोड़ ec_response_get_next_data_v1 data;
पूर्ण __ec_align1;

/* Bit indices क्रम buttons and चयनes.*/
/* Buttons */
#घोषणा EC_MKBP_POWER_BUTTON	0
#घोषणा EC_MKBP_VOL_UP		1
#घोषणा EC_MKBP_VOL_DOWN	2
#घोषणा EC_MKBP_RECOVERY	3

/* Switches */
#घोषणा EC_MKBP_LID_OPEN	0
#घोषणा EC_MKBP_TABLET_MODE	1
#घोषणा EC_MKBP_BASE_ATTACHED	2
#घोषणा EC_MKBP_FRONT_PROXIMITY	3

/* Run keyboard factory test scanning */
#घोषणा EC_CMD_KEYBOARD_FACTORY_TEST 0x0068

काष्ठा ec_response_keyboard_factory_test अणु
	uपूर्णांक16_t लघुed;	/* Keyboard pins are लघुed */
पूर्ण __ec_align2;

/* Fingerprपूर्णांक events in 'fp_events' क्रम EC_MKBP_EVENT_FINGERPRINT */
#घोषणा EC_MKBP_FP_RAW_EVENT(fp_events) ((fp_events) & 0x00FFFFFF)
#घोषणा EC_MKBP_FP_ERRCODE(fp_events)   ((fp_events) & 0x0000000F)
#घोषणा EC_MKBP_FP_ENROLL_PROGRESS_OFFSET 4
#घोषणा EC_MKBP_FP_ENROLL_PROGRESS(fpe) (((fpe) & 0x00000FF0) \
					 >> EC_MKBP_FP_ENROLL_PROGRESS_OFFSET)
#घोषणा EC_MKBP_FP_MATCH_IDX_OFFSET 12
#घोषणा EC_MKBP_FP_MATCH_IDX_MASK 0x0000F000
#घोषणा EC_MKBP_FP_MATCH_IDX(fpe) (((fpe) & EC_MKBP_FP_MATCH_IDX_MASK) \
					 >> EC_MKBP_FP_MATCH_IDX_OFFSET)
#घोषणा EC_MKBP_FP_ENROLL               BIT(27)
#घोषणा EC_MKBP_FP_MATCH                BIT(28)
#घोषणा EC_MKBP_FP_FINGER_DOWN          BIT(29)
#घोषणा EC_MKBP_FP_FINGER_UP            BIT(30)
#घोषणा EC_MKBP_FP_IMAGE_READY          BIT(31)
/* code given by EC_MKBP_FP_ERRCODE() when EC_MKBP_FP_ENROLL is set */
#घोषणा EC_MKBP_FP_ERR_ENROLL_OK               0
#घोषणा EC_MKBP_FP_ERR_ENROLL_LOW_QUALITY      1
#घोषणा EC_MKBP_FP_ERR_ENROLL_IMMOBILE         2
#घोषणा EC_MKBP_FP_ERR_ENROLL_LOW_COVERAGE     3
#घोषणा EC_MKBP_FP_ERR_ENROLL_INTERNAL         5
/* Can be used to detect अगर image was usable क्रम enrollment or not. */
#घोषणा EC_MKBP_FP_ERR_ENROLL_PROBLEM_MASK     1
/* code given by EC_MKBP_FP_ERRCODE() when EC_MKBP_FP_MATCH is set */
#घोषणा EC_MKBP_FP_ERR_MATCH_NO                0
#घोषणा EC_MKBP_FP_ERR_MATCH_NO_INTERNAL       6
#घोषणा EC_MKBP_FP_ERR_MATCH_NO_TEMPLATES      7
#घोषणा EC_MKBP_FP_ERR_MATCH_NO_LOW_QUALITY    2
#घोषणा EC_MKBP_FP_ERR_MATCH_NO_LOW_COVERAGE   4
#घोषणा EC_MKBP_FP_ERR_MATCH_YES               1
#घोषणा EC_MKBP_FP_ERR_MATCH_YES_UPDATED       3
#घोषणा EC_MKBP_FP_ERR_MATCH_YES_UPDATE_FAILED 5


/*****************************************************************************/
/* Temperature sensor commands */

/* Read temperature sensor info */
#घोषणा EC_CMD_TEMP_SENSOR_GET_INFO 0x0070

काष्ठा ec_params_temp_sensor_get_info अणु
	uपूर्णांक8_t id;
पूर्ण __ec_align1;

काष्ठा ec_response_temp_sensor_get_info अणु
	अक्षर sensor_name[32];
	uपूर्णांक8_t sensor_type;
पूर्ण __ec_align1;

/*****************************************************************************/

/*
 * Note: host commands 0x80 - 0x87 are reserved to aव्योम conflict with ACPI
 * commands accidentally sent to the wrong पूर्णांकerface.  See the ACPI section
 * below.
 */

/*****************************************************************************/
/* Host event commands */


/* Obsolete. New implementation should use EC_CMD_HOST_EVENT instead */
/*
 * Host event mask params and response काष्ठाures, shared by all of the host
 * event commands below.
 */
काष्ठा ec_params_host_event_mask अणु
	uपूर्णांक32_t mask;
पूर्ण __ec_align4;

काष्ठा ec_response_host_event_mask अणु
	uपूर्णांक32_t mask;
पूर्ण __ec_align4;

/* These all use ec_response_host_event_mask */
#घोषणा EC_CMD_HOST_EVENT_GET_B         0x0087
#घोषणा EC_CMD_HOST_EVENT_GET_SMI_MASK  0x0088
#घोषणा EC_CMD_HOST_EVENT_GET_SCI_MASK  0x0089
#घोषणा EC_CMD_HOST_EVENT_GET_WAKE_MASK 0x008D

/* These all use ec_params_host_event_mask */
#घोषणा EC_CMD_HOST_EVENT_SET_SMI_MASK  0x008A
#घोषणा EC_CMD_HOST_EVENT_SET_SCI_MASK  0x008B
#घोषणा EC_CMD_HOST_EVENT_CLEAR         0x008C
#घोषणा EC_CMD_HOST_EVENT_SET_WAKE_MASK 0x008E
#घोषणा EC_CMD_HOST_EVENT_CLEAR_B       0x008F

/*
 * Unअगरied host event programming पूर्णांकerface - Should be used by newer versions
 * of BIOS/OS to program host events and masks
 */

काष्ठा ec_params_host_event अणु

	/* Action requested by host - one of क्रमागत ec_host_event_action. */
	uपूर्णांक8_t action;

	/*
	 * Mask type that the host requested the action on - one of
	 * क्रमागत ec_host_event_mask_type.
	 */
	uपूर्णांक8_t mask_type;

	/* Set to 0, ignore on पढ़ो */
	uपूर्णांक16_t reserved;

	/* Value to be used in हाल of set operations. */
	uपूर्णांक64_t value;
पूर्ण __ec_align4;

/*
 * Response काष्ठाure वापसed by EC_CMD_HOST_EVENT.
 * Update the value on a GET request. Set to 0 on GET/CLEAR
 */

काष्ठा ec_response_host_event अणु

	/* Mask value in हाल of get operation */
	uपूर्णांक64_t value;
पूर्ण __ec_align4;

क्रमागत ec_host_event_action अणु
	/*
	 * params.value is ignored. Value of mask_type populated
	 * in response.value
	 */
	EC_HOST_EVENT_GET,

	/* Bits in params.value are set */
	EC_HOST_EVENT_SET,

	/* Bits in params.value are cleared */
	EC_HOST_EVENT_CLEAR,
पूर्ण;

क्रमागत ec_host_event_mask_type अणु

	/* Main host event copy */
	EC_HOST_EVENT_MAIN,

	/* Copy B of host events */
	EC_HOST_EVENT_B,

	/* SCI Mask */
	EC_HOST_EVENT_SCI_MASK,

	/* SMI Mask */
	EC_HOST_EVENT_SMI_MASK,

	/* Mask of events that should be always reported in hostevents */
	EC_HOST_EVENT_ALWAYS_REPORT_MASK,

	/* Active wake mask */
	EC_HOST_EVENT_ACTIVE_WAKE_MASK,

	/* Lazy wake mask क्रम S0ix */
	EC_HOST_EVENT_LAZY_WAKE_MASK_S0IX,

	/* Lazy wake mask क्रम S3 */
	EC_HOST_EVENT_LAZY_WAKE_MASK_S3,

	/* Lazy wake mask क्रम S5 */
	EC_HOST_EVENT_LAZY_WAKE_MASK_S5,
पूर्ण;

#घोषणा EC_CMD_HOST_EVENT       0x00A4

/*****************************************************************************/
/* Switch commands */

/* Enable/disable LCD backlight */
#घोषणा EC_CMD_SWITCH_ENABLE_BKLIGHT 0x0090

काष्ठा ec_params_चयन_enable_backlight अणु
	uपूर्णांक8_t enabled;
पूर्ण __ec_align1;

/* Enable/disable WLAN/Bluetooth */
#घोषणा EC_CMD_SWITCH_ENABLE_WIRELESS 0x0091
#घोषणा EC_VER_SWITCH_ENABLE_WIRELESS 1

/* Version 0 params; no response */
काष्ठा ec_params_चयन_enable_wireless_v0 अणु
	uपूर्णांक8_t enabled;
पूर्ण __ec_align1;

/* Version 1 params */
काष्ठा ec_params_चयन_enable_wireless_v1 अणु
	/* Flags to enable now */
	uपूर्णांक8_t now_flags;

	/* Which flags to copy from now_flags */
	uपूर्णांक8_t now_mask;

	/*
	 * Flags to leave enabled in S3, अगर they're on at the S0->S3
	 * transition.  (Other flags will be disabled by the S0->S3
	 * transition.)
	 */
	uपूर्णांक8_t suspend_flags;

	/* Which flags to copy from suspend_flags */
	uपूर्णांक8_t suspend_mask;
पूर्ण __ec_align1;

/* Version 1 response */
काष्ठा ec_response_चयन_enable_wireless_v1 अणु
	/* Flags to enable now */
	uपूर्णांक8_t now_flags;

	/* Flags to leave enabled in S3 */
	uपूर्णांक8_t suspend_flags;
पूर्ण __ec_align1;

/*****************************************************************************/
/* GPIO commands. Only available on EC अगर ग_लिखो protect has been disabled. */

/* Set GPIO output value */
#घोषणा EC_CMD_GPIO_SET 0x0092

काष्ठा ec_params_gpio_set अणु
	अक्षर name[32];
	uपूर्णांक8_t val;
पूर्ण __ec_align1;

/* Get GPIO value */
#घोषणा EC_CMD_GPIO_GET 0x0093

/* Version 0 of input params and response */
काष्ठा ec_params_gpio_get अणु
	अक्षर name[32];
पूर्ण __ec_align1;

काष्ठा ec_response_gpio_get अणु
	uपूर्णांक8_t val;
पूर्ण __ec_align1;

/* Version 1 of input params and response */
काष्ठा ec_params_gpio_get_v1 अणु
	uपूर्णांक8_t subcmd;
	जोड़ अणु
		काष्ठा __ec_align1 अणु
			अक्षर name[32];
		पूर्ण get_value_by_name;
		काष्ठा __ec_align1 अणु
			uपूर्णांक8_t index;
		पूर्ण get_info;
	पूर्ण;
पूर्ण __ec_align1;

काष्ठा ec_response_gpio_get_v1 अणु
	जोड़ अणु
		काष्ठा __ec_align1 अणु
			uपूर्णांक8_t val;
		पूर्ण get_value_by_name, get_count;
		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक8_t val;
			अक्षर name[32];
			uपूर्णांक32_t flags;
		पूर्ण get_info;
	पूर्ण;
पूर्ण __ec_toकरो_packed;

क्रमागत gpio_get_subcmd अणु
	EC_GPIO_GET_BY_NAME = 0,
	EC_GPIO_GET_COUNT = 1,
	EC_GPIO_GET_INFO = 2,
पूर्ण;

/*****************************************************************************/
/* I2C commands. Only available when flash ग_लिखो protect is unlocked. */

/*
 * CAUTION: These commands are deprecated, and are not supported anymore in EC
 * builds >= 8398.0.0 (see crosbug.com/p/23570).
 *
 * Use EC_CMD_I2C_PASSTHRU instead.
 */

/* Read I2C bus */
#घोषणा EC_CMD_I2C_READ 0x0094

काष्ठा ec_params_i2c_पढ़ो अणु
	uपूर्णांक16_t addr; /* 8-bit address (7-bit shअगरted << 1) */
	uपूर्णांक8_t पढ़ो_size; /* Either 8 or 16. */
	uपूर्णांक8_t port;
	uपूर्णांक8_t offset;
पूर्ण __ec_align_size1;

काष्ठा ec_response_i2c_पढ़ो अणु
	uपूर्णांक16_t data;
पूर्ण __ec_align2;

/* Write I2C bus */
#घोषणा EC_CMD_I2C_WRITE 0x0095

काष्ठा ec_params_i2c_ग_लिखो अणु
	uपूर्णांक16_t data;
	uपूर्णांक16_t addr; /* 8-bit address (7-bit shअगरted << 1) */
	uपूर्णांक8_t ग_लिखो_size; /* Either 8 or 16. */
	uपूर्णांक8_t port;
	uपूर्णांक8_t offset;
पूर्ण __ec_align_size1;

/*****************************************************************************/
/* Charge state commands. Only available when flash ग_लिखो protect unlocked. */

/* Force अक्षरge state machine to stop अक्षरging the battery or क्रमce it to
 * disअक्षरge the battery.
 */
#घोषणा EC_CMD_CHARGE_CONTROL 0x0096
#घोषणा EC_VER_CHARGE_CONTROL 1

क्रमागत ec_अक्षरge_control_mode अणु
	CHARGE_CONTROL_NORMAL = 0,
	CHARGE_CONTROL_IDLE,
	CHARGE_CONTROL_DISCHARGE,
पूर्ण;

काष्ठा ec_params_अक्षरge_control अणु
	uपूर्णांक32_t mode;  /* क्रमागत अक्षरge_control_mode */
पूर्ण __ec_align4;

/*****************************************************************************/

/* Snapshot console output buffer क्रम use by EC_CMD_CONSOLE_READ. */
#घोषणा EC_CMD_CONSOLE_SNAPSHOT 0x0097

/*
 * Read data from the saved snapshot. If the subcmd parameter is
 * CONSOLE_READ_NEXT, this will वापस data starting from the beginning of
 * the latest snapshot. If it is CONSOLE_READ_RECENT, it will start from the
 * end of the previous snapshot.
 *
 * The params are only looked at in version >= 1 of this command. Prior
 * versions will just शेष to CONSOLE_READ_NEXT behavior.
 *
 * Response is null-terminated string.  Empty string, अगर there is no more
 * reमुख्यing output.
 */
#घोषणा EC_CMD_CONSOLE_READ 0x0098

क्रमागत ec_console_पढ़ो_subcmd अणु
	CONSOLE_READ_NEXT = 0,
	CONSOLE_READ_RECENT
पूर्ण;

काष्ठा ec_params_console_पढ़ो_v1 अणु
	uपूर्णांक8_t subcmd; /* क्रमागत ec_console_पढ़ो_subcmd */
पूर्ण __ec_align1;

/*****************************************************************************/

/*
 * Cut off battery घातer immediately or after the host has shut करोwn.
 *
 * वापस EC_RES_INVALID_COMMAND अगर unsupported by a board/battery.
 *	  EC_RES_SUCCESS अगर the command was successful.
 *	  EC_RES_ERROR अगर the cut off command failed.
 */
#घोषणा EC_CMD_BATTERY_CUT_OFF 0x0099

#घोषणा EC_BATTERY_CUTOFF_FLAG_AT_SHUTDOWN	BIT(0)

काष्ठा ec_params_battery_cutoff अणु
	uपूर्णांक8_t flags;
पूर्ण __ec_align1;

/*****************************************************************************/
/* USB port mux control. */

/*
 * Switch USB mux or वापस to स्वतःmatic चयनing.
 */
#घोषणा EC_CMD_USB_MUX 0x009A

काष्ठा ec_params_usb_mux अणु
	uपूर्णांक8_t mux;
पूर्ण __ec_align1;

/*****************************************************************************/
/* LDOs / FETs control. */

क्रमागत ec_lकरो_state अणु
	EC_LDO_STATE_OFF = 0,	/* the LDO / FET is shut करोwn */
	EC_LDO_STATE_ON = 1,	/* the LDO / FET is ON / providing घातer */
पूर्ण;

/*
 * Switch on/off a LDO.
 */
#घोषणा EC_CMD_LDO_SET 0x009B

काष्ठा ec_params_lकरो_set अणु
	uपूर्णांक8_t index;
	uपूर्णांक8_t state;
पूर्ण __ec_align1;

/*
 * Get LDO state.
 */
#घोषणा EC_CMD_LDO_GET 0x009C

काष्ठा ec_params_lकरो_get अणु
	uपूर्णांक8_t index;
पूर्ण __ec_align1;

काष्ठा ec_response_lकरो_get अणु
	uपूर्णांक8_t state;
पूर्ण __ec_align1;

/*****************************************************************************/
/* Power info. */

/*
 * Get घातer info.
 */
#घोषणा EC_CMD_POWER_INFO 0x009D

काष्ठा ec_response_घातer_info अणु
	uपूर्णांक32_t usb_dev_type;
	uपूर्णांक16_t voltage_ac;
	uपूर्णांक16_t voltage_प्रणाली;
	uपूर्णांक16_t current_प्रणाली;
	uपूर्णांक16_t usb_current_limit;
पूर्ण __ec_align4;

/*****************************************************************************/
/* I2C passthru command */

#घोषणा EC_CMD_I2C_PASSTHRU 0x009E

/* Read data; अगर not present, message is a ग_लिखो */
#घोषणा EC_I2C_FLAG_READ	BIT(15)

/* Mask क्रम address */
#घोषणा EC_I2C_ADDR_MASK	0x3ff

#घोषणा EC_I2C_STATUS_NAK	BIT(0) /* Transfer was not acknowledged */
#घोषणा EC_I2C_STATUS_TIMEOUT	BIT(1) /* Timeout during transfer */

/* Any error */
#घोषणा EC_I2C_STATUS_ERROR	(EC_I2C_STATUS_NAK | EC_I2C_STATUS_TIMEOUT)

काष्ठा ec_params_i2c_passthru_msg अणु
	uपूर्णांक16_t addr_flags;	/* I2C slave address (7 or 10 bits) and flags */
	uपूर्णांक16_t len;		/* Number of bytes to पढ़ो or ग_लिखो */
पूर्ण __ec_align2;

काष्ठा ec_params_i2c_passthru अणु
	uपूर्णांक8_t port;		/* I2C port number */
	uपूर्णांक8_t num_msgs;	/* Number of messages */
	काष्ठा ec_params_i2c_passthru_msg msg[];
	/* Data to ग_लिखो क्रम all messages is concatenated here */
पूर्ण __ec_align2;

काष्ठा ec_response_i2c_passthru अणु
	uपूर्णांक8_t i2c_status;	/* Status flags (EC_I2C_STATUS_...) */
	uपूर्णांक8_t num_msgs;	/* Number of messages processed */
	uपूर्णांक8_t data[];		/* Data पढ़ो by messages concatenated here */
पूर्ण __ec_align1;

/*****************************************************************************/
/* Power button hang detect */

#घोषणा EC_CMD_HANG_DETECT 0x009F

/* Reasons to start hang detection समयr */
/* Power button pressed */
#घोषणा EC_HANG_START_ON_POWER_PRESS  BIT(0)

/* Lid बंदd */
#घोषणा EC_HANG_START_ON_LID_CLOSE    BIT(1)

 /* Lid खोलोed */
#घोषणा EC_HANG_START_ON_LID_OPEN     BIT(2)

/* Start of AP S3->S0 transition (booting or resuming from suspend) */
#घोषणा EC_HANG_START_ON_RESUME       BIT(3)

/* Reasons to cancel hang detection */

/* Power button released */
#घोषणा EC_HANG_STOP_ON_POWER_RELEASE BIT(8)

/* Any host command from AP received */
#घोषणा EC_HANG_STOP_ON_HOST_COMMAND  BIT(9)

/* Stop on end of AP S0->S3 transition (suspending or shutting करोwn) */
#घोषणा EC_HANG_STOP_ON_SUSPEND       BIT(10)

/*
 * If this flag is set, all the other fields are ignored, and the hang detect
 * समयr is started.  This provides the AP a way to start the hang समयr
 * without reconfiguring any of the other hang detect settings.  Note that
 * you must previously have configured the समयouts.
 */
#घोषणा EC_HANG_START_NOW             BIT(30)

/*
 * If this flag is set, all the other fields are ignored (including
 * EC_HANG_START_NOW).  This provides the AP a way to stop the hang समयr
 * without reconfiguring any of the other hang detect settings.
 */
#घोषणा EC_HANG_STOP_NOW              BIT(31)

काष्ठा ec_params_hang_detect अणु
	/* Flags; see EC_HANG_* */
	uपूर्णांक32_t flags;

	/* Timeout in msec beक्रमe generating host event, अगर enabled */
	uपूर्णांक16_t host_event_समयout_msec;

	/* Timeout in msec beक्रमe generating warm reboot, अगर enabled */
	uपूर्णांक16_t warm_reboot_समयout_msec;
पूर्ण __ec_align4;

/*****************************************************************************/
/* Commands क्रम battery अक्षरging */

/*
 * This is the single catch-all host command to exchange data regarding the
 * अक्षरge state machine (v2 and up).
 */
#घोषणा EC_CMD_CHARGE_STATE 0x00A0

/* Subcommands क्रम this host command */
क्रमागत अक्षरge_state_command अणु
	CHARGE_STATE_CMD_GET_STATE,
	CHARGE_STATE_CMD_GET_PARAM,
	CHARGE_STATE_CMD_SET_PARAM,
	CHARGE_STATE_NUM_CMDS
पूर्ण;

/*
 * Known param numbers are defined here. Ranges are reserved क्रम board-specअगरic
 * params, which are handled by the particular implementations.
 */
क्रमागत अक्षरge_state_params अणु
	CS_PARAM_CHG_VOLTAGE,	      /* अक्षरger voltage limit */
	CS_PARAM_CHG_CURRENT,	      /* अक्षरger current limit */
	CS_PARAM_CHG_INPUT_CURRENT,   /* अक्षरger input current limit */
	CS_PARAM_CHG_STATUS,	      /* अक्षरger-specअगरic status */
	CS_PARAM_CHG_OPTION,	      /* अक्षरger-specअगरic options */
	CS_PARAM_LIMIT_POWER,	      /*
				       * Check अगर घातer is limited due to
				       * low battery and / or a weak बाह्यal
				       * अक्षरger. READ ONLY.
				       */
	/* How many so far? */
	CS_NUM_BASE_PARAMS,

	/* Range क्रम CONFIG_CHARGER_PROखाता_OVERRIDE params */
	CS_PARAM_CUSTOM_PROखाता_MIN = 0x10000,
	CS_PARAM_CUSTOM_PROखाता_MAX = 0x1ffff,

	/* Range क्रम CONFIG_CHARGE_STATE_DEBUG params */
	CS_PARAM_DEBUG_MIN = 0x20000,
	CS_PARAM_DEBUG_CTL_MODE = 0x20000,
	CS_PARAM_DEBUG_MANUAL_MODE,
	CS_PARAM_DEBUG_SEEMS_DEAD,
	CS_PARAM_DEBUG_SEEMS_DISCONNECTED,
	CS_PARAM_DEBUG_BATT_REMOVED,
	CS_PARAM_DEBUG_MANUAL_CURRENT,
	CS_PARAM_DEBUG_MANUAL_VOLTAGE,
	CS_PARAM_DEBUG_MAX = 0x2ffff,

	/* Other custom param ranges go here... */
पूर्ण;

काष्ठा ec_params_अक्षरge_state अणु
	uपूर्णांक8_t cmd;				/* क्रमागत अक्षरge_state_command */
	जोड़ अणु
		/* get_state has no args */

		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक32_t param;		/* क्रमागत अक्षरge_state_param */
		पूर्ण get_param;

		काष्ठा __ec_toकरो_unpacked अणु
			uपूर्णांक32_t param;		/* param to set */
			uपूर्णांक32_t value;		/* value to set */
		पूर्ण set_param;
	पूर्ण;
पूर्ण __ec_toकरो_packed;

काष्ठा ec_response_अक्षरge_state अणु
	जोड़ अणु
		काष्ठा __ec_align4 अणु
			पूर्णांक ac;
			पूर्णांक chg_voltage;
			पूर्णांक chg_current;
			पूर्णांक chg_input_current;
			पूर्णांक batt_state_of_अक्षरge;
		पूर्ण get_state;

		काष्ठा __ec_align4 अणु
			uपूर्णांक32_t value;
		पूर्ण get_param;

		/* set_param वापसs no args */
	पूर्ण;
पूर्ण __ec_align4;


/*
 * Set maximum battery अक्षरging current.
 */
#घोषणा EC_CMD_CHARGE_CURRENT_LIMIT 0x00A1

काष्ठा ec_params_current_limit अणु
	uपूर्णांक32_t limit; /* in mA */
पूर्ण __ec_align4;

/*
 * Set maximum बाह्यal voltage / current.
 */
#घोषणा EC_CMD_EXTERNAL_POWER_LIMIT 0x00A2

/* Command v0 is used only on Spring and is obsolete + unsupported */
काष्ठा ec_params_बाह्यal_घातer_limit_v1 अणु
	uपूर्णांक16_t current_lim; /* in mA, or EC_POWER_LIMIT_NONE to clear limit */
	uपूर्णांक16_t voltage_lim; /* in mV, or EC_POWER_LIMIT_NONE to clear limit */
पूर्ण __ec_align2;

#घोषणा EC_POWER_LIMIT_NONE 0xffff

/*
 * Set maximum voltage & current of a dedicated अक्षरge port
 */
#घोषणा EC_CMD_OVERRIDE_DEDICATED_CHARGER_LIMIT 0x00A3

काष्ठा ec_params_dedicated_अक्षरger_limit अणु
	uपूर्णांक16_t current_lim; /* in mA */
	uपूर्णांक16_t voltage_lim; /* in mV */
पूर्ण __ec_align2;

/*****************************************************************************/
/* Hibernate/Deep Sleep Commands */

/* Set the delay beक्रमe going पूर्णांकo hibernation. */
#घोषणा EC_CMD_HIBERNATION_DELAY 0x00A8

काष्ठा ec_params_hibernation_delay अणु
	/*
	 * Seconds to रुको in G3 beक्रमe hibernate.  Pass in 0 to पढ़ो the
	 * current settings without changing them.
	 */
	uपूर्णांक32_t seconds;
पूर्ण __ec_align4;

काष्ठा ec_response_hibernation_delay अणु
	/*
	 * The current समय in seconds in which the प्रणाली has been in the G3
	 * state.  This value is reset अगर the EC transitions out of G3.
	 */
	uपूर्णांक32_t समय_g3;

	/*
	 * The current समय reमुख्यing in seconds until the EC should hibernate.
	 * This value is also reset अगर the EC transitions out of G3.
	 */
	uपूर्णांक32_t समय_reमुख्यing;

	/*
	 * The current समय in seconds that the EC should रुको in G3 beक्रमe
	 * hibernating.
	 */
	uपूर्णांक32_t hibernate_delay;
पूर्ण __ec_align4;

/* Inक्रमm the EC when entering a sleep state */
#घोषणा EC_CMD_HOST_SLEEP_EVENT 0x00A9

क्रमागत host_sleep_event अणु
	HOST_SLEEP_EVENT_S3_SUSPEND   = 1,
	HOST_SLEEP_EVENT_S3_RESUME    = 2,
	HOST_SLEEP_EVENT_S0IX_SUSPEND = 3,
	HOST_SLEEP_EVENT_S0IX_RESUME  = 4,
	/* S3 suspend with additional enabled wake sources */
	HOST_SLEEP_EVENT_S3_WAKEABLE_SUSPEND = 5,
पूर्ण;

काष्ठा ec_params_host_sleep_event अणु
	uपूर्णांक8_t sleep_event;
पूर्ण __ec_align1;

/*
 * Use a शेष समयout value (CONFIG_SLEEP_TIMEOUT_MS) क्रम detecting sleep
 * transition failures
 */
#घोषणा EC_HOST_SLEEP_TIMEOUT_DEFAULT 0

/* Disable समयout detection क्रम this sleep transition */
#घोषणा EC_HOST_SLEEP_TIMEOUT_INFINITE 0xFFFF

काष्ठा ec_params_host_sleep_event_v1 अणु
	/* The type of sleep being entered or निकासed. */
	uपूर्णांक8_t sleep_event;

	/* Padding */
	uपूर्णांक8_t reserved;
	जोड़ अणु
		/* Parameters that apply क्रम suspend messages. */
		काष्ठा अणु
			/*
			 * The समयout in milliseconds between when this message
			 * is received and when the EC will declare sleep
			 * transition failure अगर the sleep संकेत is not
			 * निश्चितed.
			 */
			uपूर्णांक16_t sleep_समयout_ms;
		पूर्ण suspend_params;

		/* No parameters क्रम non-suspend messages. */
	पूर्ण;
पूर्ण __ec_align2;

/* A समयout occurred when this bit is set */
#घोषणा EC_HOST_RESUME_SLEEP_TIMEOUT 0x80000000

/*
 * The mask defining which bits correspond to the number of sleep transitions,
 * as well as the maximum number of suspend line transitions that will be
 * reported back to the host.
 */
#घोषणा EC_HOST_RESUME_SLEEP_TRANSITIONS_MASK 0x7FFFFFFF

काष्ठा ec_response_host_sleep_event_v1 अणु
	जोड़ अणु
		/* Response fields that apply क्रम resume messages. */
		काष्ठा अणु
			/*
			 * The number of sleep घातer संकेत transitions that
			 * occurred since the suspend message. The high bit
			 * indicates a समयout occurred.
			 */
			uपूर्णांक32_t sleep_transitions;
		पूर्ण resume_response;

		/* No response fields क्रम non-resume messages. */
	पूर्ण;
पूर्ण __ec_align4;

/*****************************************************************************/
/* Device events */
#घोषणा EC_CMD_DEVICE_EVENT 0x00AA

क्रमागत ec_device_event अणु
	EC_DEVICE_EVENT_TRACKPAD,
	EC_DEVICE_EVENT_DSP,
	EC_DEVICE_EVENT_WIFI,
पूर्ण;

क्रमागत ec_device_event_param अणु
	/* Get and clear pending device events */
	EC_DEVICE_EVENT_PARAM_GET_CURRENT_EVENTS,
	/* Get device event mask */
	EC_DEVICE_EVENT_PARAM_GET_ENABLED_EVENTS,
	/* Set device event mask */
	EC_DEVICE_EVENT_PARAM_SET_ENABLED_EVENTS,
पूर्ण;

#घोषणा EC_DEVICE_EVENT_MASK(event_code) BIT(event_code % 32)

काष्ठा ec_params_device_event अणु
	uपूर्णांक32_t event_mask;
	uपूर्णांक8_t param;
पूर्ण __ec_align_size1;

काष्ठा ec_response_device_event अणु
	uपूर्णांक32_t event_mask;
पूर्ण __ec_align4;

/*****************************************************************************/
/* Smart battery pass-through */

/* Get / Set 16-bit smart battery रेजिस्टरs */
#घोषणा EC_CMD_SB_READ_WORD   0x00B0
#घोषणा EC_CMD_SB_WRITE_WORD  0x00B1

/* Get / Set string smart battery parameters
 * क्रमmatted as SMBUS "block".
 */
#घोषणा EC_CMD_SB_READ_BLOCK  0x00B2
#घोषणा EC_CMD_SB_WRITE_BLOCK 0x00B3

काष्ठा ec_params_sb_rd अणु
	uपूर्णांक8_t reg;
पूर्ण __ec_align1;

काष्ठा ec_response_sb_rd_word अणु
	uपूर्णांक16_t value;
पूर्ण __ec_align2;

काष्ठा ec_params_sb_wr_word अणु
	uपूर्णांक8_t reg;
	uपूर्णांक16_t value;
पूर्ण __ec_align1;

काष्ठा ec_response_sb_rd_block अणु
	uपूर्णांक8_t data[32];
पूर्ण __ec_align1;

काष्ठा ec_params_sb_wr_block अणु
	uपूर्णांक8_t reg;
	uपूर्णांक16_t data[32];
पूर्ण __ec_align1;

/*****************************************************************************/
/* Battery venकरोr parameters
 *
 * Get or set venकरोr-specअगरic parameters in the battery. Implementations may
 * dअगरfer between boards or batteries. On a set operation, the response
 * contains the actual value set, which may be rounded or clipped from the
 * requested value.
 */

#घोषणा EC_CMD_BATTERY_VENDOR_PARAM 0x00B4

क्रमागत ec_battery_venकरोr_param_mode अणु
	BATTERY_VENDOR_PARAM_MODE_GET = 0,
	BATTERY_VENDOR_PARAM_MODE_SET,
पूर्ण;

काष्ठा ec_params_battery_venकरोr_param अणु
	uपूर्णांक32_t param;
	uपूर्णांक32_t value;
	uपूर्णांक8_t mode;
पूर्ण __ec_align_size1;

काष्ठा ec_response_battery_venकरोr_param अणु
	uपूर्णांक32_t value;
पूर्ण __ec_align4;

/*****************************************************************************/
/*
 * Smart Battery Firmware Update Commands
 */
#घोषणा EC_CMD_SB_FW_UPDATE 0x00B5

क्रमागत ec_sb_fw_update_subcmd अणु
	EC_SB_FW_UPDATE_PREPARE  = 0x0,
	EC_SB_FW_UPDATE_INFO     = 0x1, /*query sb info */
	EC_SB_FW_UPDATE_BEGIN    = 0x2, /*check अगर रक्षित */
	EC_SB_FW_UPDATE_WRITE    = 0x3, /*check अगर रक्षित */
	EC_SB_FW_UPDATE_END      = 0x4,
	EC_SB_FW_UPDATE_STATUS   = 0x5,
	EC_SB_FW_UPDATE_PROTECT  = 0x6,
	EC_SB_FW_UPDATE_MAX      = 0x7,
पूर्ण;

#घोषणा SB_FW_UPDATE_CMD_WRITE_BLOCK_SIZE 32
#घोषणा SB_FW_UPDATE_CMD_STATUS_SIZE 2
#घोषणा SB_FW_UPDATE_CMD_INFO_SIZE 8

काष्ठा ec_sb_fw_update_header अणु
	uपूर्णांक16_t subcmd;  /* क्रमागत ec_sb_fw_update_subcmd */
	uपूर्णांक16_t fw_id;   /* firmware id */
पूर्ण __ec_align4;

काष्ठा ec_params_sb_fw_update अणु
	काष्ठा ec_sb_fw_update_header hdr;
	जोड़ अणु
		/* EC_SB_FW_UPDATE_PREPARE  = 0x0 */
		/* EC_SB_FW_UPDATE_INFO     = 0x1 */
		/* EC_SB_FW_UPDATE_BEGIN    = 0x2 */
		/* EC_SB_FW_UPDATE_END      = 0x4 */
		/* EC_SB_FW_UPDATE_STATUS   = 0x5 */
		/* EC_SB_FW_UPDATE_PROTECT  = 0x6 */
		/* Those have no args */

		/* EC_SB_FW_UPDATE_WRITE    = 0x3 */
		काष्ठा __ec_align4 अणु
			uपूर्णांक8_t  data[SB_FW_UPDATE_CMD_WRITE_BLOCK_SIZE];
		पूर्ण ग_लिखो;
	पूर्ण;
पूर्ण __ec_align4;

काष्ठा ec_response_sb_fw_update अणु
	जोड़ अणु
		/* EC_SB_FW_UPDATE_INFO     = 0x1 */
		काष्ठा __ec_align1 अणु
			uपूर्णांक8_t data[SB_FW_UPDATE_CMD_INFO_SIZE];
		पूर्ण info;

		/* EC_SB_FW_UPDATE_STATUS   = 0x5 */
		काष्ठा __ec_align1 अणु
			uपूर्णांक8_t data[SB_FW_UPDATE_CMD_STATUS_SIZE];
		पूर्ण status;
	पूर्ण;
पूर्ण __ec_align1;

/*
 * Entering Verअगरied Boot Mode Command
 * Default mode is VBOOT_MODE_NORMAL अगर EC did not receive this command.
 * Valid Modes are: normal, developer, and recovery.
 */
#घोषणा EC_CMD_ENTERING_MODE 0x00B6

काष्ठा ec_params_entering_mode अणु
	पूर्णांक vboot_mode;
पूर्ण __ec_align4;

#घोषणा VBOOT_MODE_NORMAL    0
#घोषणा VBOOT_MODE_DEVELOPER 1
#घोषणा VBOOT_MODE_RECOVERY  2

/*****************************************************************************/
/*
 * I2C passthru protection command: Protects I2C tunnels against access on
 * certain addresses (board-specअगरic).
 */
#घोषणा EC_CMD_I2C_PASSTHRU_PROTECT 0x00B7

क्रमागत ec_i2c_passthru_protect_subcmd अणु
	EC_CMD_I2C_PASSTHRU_PROTECT_STATUS = 0x0,
	EC_CMD_I2C_PASSTHRU_PROTECT_ENABLE = 0x1,
पूर्ण;

काष्ठा ec_params_i2c_passthru_protect अणु
	uपूर्णांक8_t subcmd;
	uपूर्णांक8_t port;		/* I2C port number */
पूर्ण __ec_align1;

काष्ठा ec_response_i2c_passthru_protect अणु
	uपूर्णांक8_t status;		/* Status flags (0: unlocked, 1: locked) */
पूर्ण __ec_align1;


/*****************************************************************************/
/*
 * HDMI CEC commands
 *
 * These commands are क्रम sending and receiving message via HDMI CEC
 */

#घोषणा MAX_CEC_MSG_LEN 16

/* CEC message from the AP to be written on the CEC bus */
#घोषणा EC_CMD_CEC_WRITE_MSG 0x00B8

/**
 * काष्ठा ec_params_cec_ग_लिखो - Message to ग_लिखो to the CEC bus
 * @msg: message content to ग_लिखो to the CEC bus
 */
काष्ठा ec_params_cec_ग_लिखो अणु
	uपूर्णांक8_t msg[MAX_CEC_MSG_LEN];
पूर्ण __ec_align1;

/* Set various CEC parameters */
#घोषणा EC_CMD_CEC_SET 0x00BA

/**
 * काष्ठा ec_params_cec_set - CEC parameters set
 * @cmd: parameter type, can be CEC_CMD_ENABLE or CEC_CMD_LOGICAL_ADDRESS
 * @val: in हाल cmd is CEC_CMD_ENABLE, this field can be 0 to disable CEC
 *	or 1 to enable CEC functionality, in हाल cmd is
 *	CEC_CMD_LOGICAL_ADDRESS, this field encodes the requested logical
 *	address between 0 and 15 or 0xff to unरेजिस्टर
 */
काष्ठा ec_params_cec_set अणु
	uपूर्णांक8_t cmd; /* क्रमागत cec_command */
	uपूर्णांक8_t val;
पूर्ण __ec_align1;

/* Read various CEC parameters */
#घोषणा EC_CMD_CEC_GET 0x00BB

/**
 * काष्ठा ec_params_cec_get - CEC parameters get
 * @cmd: parameter type, can be CEC_CMD_ENABLE or CEC_CMD_LOGICAL_ADDRESS
 */
काष्ठा ec_params_cec_get अणु
	uपूर्णांक8_t cmd; /* क्रमागत cec_command */
पूर्ण __ec_align1;

/**
 * काष्ठा ec_response_cec_get - CEC parameters get response
 * @val: in हाल cmd was CEC_CMD_ENABLE, this field will 0 अगर CEC is
 *	disabled or 1 अगर CEC functionality is enabled,
 *	in हाल cmd was CEC_CMD_LOGICAL_ADDRESS, this will encode the
 *	configured logical address between 0 and 15 or 0xff अगर unरेजिस्टरed
 */
काष्ठा ec_response_cec_get अणु
	uपूर्णांक8_t val;
पूर्ण __ec_align1;

/* CEC parameters command */
क्रमागत cec_command अणु
	/* CEC पढ़ोing, writing and events enable */
	CEC_CMD_ENABLE,
	/* CEC logical address  */
	CEC_CMD_LOGICAL_ADDRESS,
पूर्ण;

/* Events from CEC to AP */
क्रमागत mkbp_cec_event अणु
	/* Outgoing message was acknowledged by a follower */
	EC_MKBP_CEC_SEND_OK			= BIT(0),
	/* Outgoing message was not acknowledged */
	EC_MKBP_CEC_SEND_FAILED			= BIT(1),
पूर्ण;

/*****************************************************************************/

/* Commands क्रम audio codec. */
#घोषणा EC_CMD_EC_CODEC 0x00BC

क्रमागत ec_codec_subcmd अणु
	EC_CODEC_GET_CAPABILITIES = 0x0,
	EC_CODEC_GET_SHM_ADDR = 0x1,
	EC_CODEC_SET_SHM_ADDR = 0x2,
	EC_CODEC_SUBCMD_COUNT,
पूर्ण;

क्रमागत ec_codec_cap अणु
	EC_CODEC_CAP_WOV_AUDIO_SHM = 0,
	EC_CODEC_CAP_WOV_LANG_SHM = 1,
	EC_CODEC_CAP_LAST = 32,
पूर्ण;

क्रमागत ec_codec_shm_id अणु
	EC_CODEC_SHM_ID_WOV_AUDIO = 0x0,
	EC_CODEC_SHM_ID_WOV_LANG = 0x1,
	EC_CODEC_SHM_ID_LAST,
पूर्ण;

क्रमागत ec_codec_shm_type अणु
	EC_CODEC_SHM_TYPE_EC_RAM = 0x0,
	EC_CODEC_SHM_TYPE_SYSTEM_RAM = 0x1,
पूर्ण;

काष्ठा __ec_align1 ec_param_ec_codec_get_shm_addr अणु
	uपूर्णांक8_t shm_id;
	uपूर्णांक8_t reserved[3];
पूर्ण;

काष्ठा __ec_align4 ec_param_ec_codec_set_shm_addr अणु
	uपूर्णांक64_t phys_addr;
	uपूर्णांक32_t len;
	uपूर्णांक8_t shm_id;
	uपूर्णांक8_t reserved[3];
पूर्ण;

काष्ठा __ec_align4 ec_param_ec_codec अणु
	uपूर्णांक8_t cmd; /* क्रमागत ec_codec_subcmd */
	uपूर्णांक8_t reserved[3];

	जोड़ अणु
		काष्ठा ec_param_ec_codec_get_shm_addr
				get_shm_addr_param;
		काष्ठा ec_param_ec_codec_set_shm_addr
				set_shm_addr_param;
	पूर्ण;
पूर्ण;

काष्ठा __ec_align4 ec_response_ec_codec_get_capabilities अणु
	uपूर्णांक32_t capabilities;
पूर्ण;

काष्ठा __ec_align4 ec_response_ec_codec_get_shm_addr अणु
	uपूर्णांक64_t phys_addr;
	uपूर्णांक32_t len;
	uपूर्णांक8_t type;
	uपूर्णांक8_t reserved[3];
पूर्ण;

/*****************************************************************************/

/* Commands क्रम DMIC on audio codec. */
#घोषणा EC_CMD_EC_CODEC_DMIC 0x00BD

क्रमागत ec_codec_dmic_subcmd अणु
	EC_CODEC_DMIC_GET_MAX_GAIN = 0x0,
	EC_CODEC_DMIC_SET_GAIN_IDX = 0x1,
	EC_CODEC_DMIC_GET_GAIN_IDX = 0x2,
	EC_CODEC_DMIC_SUBCMD_COUNT,
पूर्ण;

क्रमागत ec_codec_dmic_channel अणु
	EC_CODEC_DMIC_CHANNEL_0 = 0x0,
	EC_CODEC_DMIC_CHANNEL_1 = 0x1,
	EC_CODEC_DMIC_CHANNEL_2 = 0x2,
	EC_CODEC_DMIC_CHANNEL_3 = 0x3,
	EC_CODEC_DMIC_CHANNEL_4 = 0x4,
	EC_CODEC_DMIC_CHANNEL_5 = 0x5,
	EC_CODEC_DMIC_CHANNEL_6 = 0x6,
	EC_CODEC_DMIC_CHANNEL_7 = 0x7,
	EC_CODEC_DMIC_CHANNEL_COUNT,
पूर्ण;

काष्ठा __ec_align1 ec_param_ec_codec_dmic_set_gain_idx अणु
	uपूर्णांक8_t channel; /* क्रमागत ec_codec_dmic_channel */
	uपूर्णांक8_t gain;
	uपूर्णांक8_t reserved[2];
पूर्ण;

काष्ठा __ec_align1 ec_param_ec_codec_dmic_get_gain_idx अणु
	uपूर्णांक8_t channel; /* क्रमागत ec_codec_dmic_channel */
	uपूर्णांक8_t reserved[3];
पूर्ण;

काष्ठा __ec_align4 ec_param_ec_codec_dmic अणु
	uपूर्णांक8_t cmd; /* क्रमागत ec_codec_dmic_subcmd */
	uपूर्णांक8_t reserved[3];

	जोड़ अणु
		काष्ठा ec_param_ec_codec_dmic_set_gain_idx
				set_gain_idx_param;
		काष्ठा ec_param_ec_codec_dmic_get_gain_idx
				get_gain_idx_param;
	पूर्ण;
पूर्ण;

काष्ठा __ec_align1 ec_response_ec_codec_dmic_get_max_gain अणु
	uपूर्णांक8_t max_gain;
पूर्ण;

काष्ठा __ec_align1 ec_response_ec_codec_dmic_get_gain_idx अणु
	uपूर्णांक8_t gain;
पूर्ण;

/*****************************************************************************/

/* Commands क्रम I2S RX on audio codec. */

#घोषणा EC_CMD_EC_CODEC_I2S_RX 0x00BE

क्रमागत ec_codec_i2s_rx_subcmd अणु
	EC_CODEC_I2S_RX_ENABLE = 0x0,
	EC_CODEC_I2S_RX_DISABLE = 0x1,
	EC_CODEC_I2S_RX_SET_SAMPLE_DEPTH = 0x2,
	EC_CODEC_I2S_RX_SET_DAIFMT = 0x3,
	EC_CODEC_I2S_RX_SET_BCLK = 0x4,
	EC_CODEC_I2S_RX_RESET = 0x5,
	EC_CODEC_I2S_RX_SUBCMD_COUNT,
पूर्ण;

क्रमागत ec_codec_i2s_rx_sample_depth अणु
	EC_CODEC_I2S_RX_SAMPLE_DEPTH_16 = 0x0,
	EC_CODEC_I2S_RX_SAMPLE_DEPTH_24 = 0x1,
	EC_CODEC_I2S_RX_SAMPLE_DEPTH_COUNT,
पूर्ण;

क्रमागत ec_codec_i2s_rx_daअगरmt अणु
	EC_CODEC_I2S_RX_DAIFMT_I2S = 0x0,
	EC_CODEC_I2S_RX_DAIFMT_RIGHT_J = 0x1,
	EC_CODEC_I2S_RX_DAIFMT_LEFT_J = 0x2,
	EC_CODEC_I2S_RX_DAIFMT_COUNT,
पूर्ण;

काष्ठा __ec_align1 ec_param_ec_codec_i2s_rx_set_sample_depth अणु
	uपूर्णांक8_t depth;
	uपूर्णांक8_t reserved[3];
पूर्ण;

काष्ठा __ec_align1 ec_param_ec_codec_i2s_rx_set_gain अणु
	uपूर्णांक8_t left;
	uपूर्णांक8_t right;
	uपूर्णांक8_t reserved[2];
पूर्ण;

काष्ठा __ec_align1 ec_param_ec_codec_i2s_rx_set_daअगरmt अणु
	uपूर्णांक8_t daअगरmt;
	uपूर्णांक8_t reserved[3];
पूर्ण;

काष्ठा __ec_align4 ec_param_ec_codec_i2s_rx_set_bclk अणु
	uपूर्णांक32_t bclk;
पूर्ण;

काष्ठा __ec_align4 ec_param_ec_codec_i2s_rx अणु
	uपूर्णांक8_t cmd; /* क्रमागत ec_codec_i2s_rx_subcmd */
	uपूर्णांक8_t reserved[3];

	जोड़ अणु
		काष्ठा ec_param_ec_codec_i2s_rx_set_sample_depth
				set_sample_depth_param;
		काष्ठा ec_param_ec_codec_i2s_rx_set_daअगरmt
				set_daअगरmt_param;
		काष्ठा ec_param_ec_codec_i2s_rx_set_bclk
				set_bclk_param;
	पूर्ण;
पूर्ण;

/*****************************************************************************/
/* Commands क्रम WoV on audio codec. */

#घोषणा EC_CMD_EC_CODEC_WOV 0x00BF

क्रमागत ec_codec_wov_subcmd अणु
	EC_CODEC_WOV_SET_LANG = 0x0,
	EC_CODEC_WOV_SET_LANG_SHM = 0x1,
	EC_CODEC_WOV_GET_LANG = 0x2,
	EC_CODEC_WOV_ENABLE = 0x3,
	EC_CODEC_WOV_DISABLE = 0x4,
	EC_CODEC_WOV_READ_AUDIO = 0x5,
	EC_CODEC_WOV_READ_AUDIO_SHM = 0x6,
	EC_CODEC_WOV_SUBCMD_COUNT,
पूर्ण;

/*
 * @hash is SHA256 of the whole language model.
 * @total_len indicates the length of whole language model.
 * @offset is the cursor from the beginning of the model.
 * @buf is the packet buffer.
 * @len denotes how many bytes in the buf.
 */
काष्ठा __ec_align4 ec_param_ec_codec_wov_set_lang अणु
	uपूर्णांक8_t hash[32];
	uपूर्णांक32_t total_len;
	uपूर्णांक32_t offset;
	uपूर्णांक8_t buf[128];
	uपूर्णांक32_t len;
पूर्ण;

काष्ठा __ec_align4 ec_param_ec_codec_wov_set_lang_shm अणु
	uपूर्णांक8_t hash[32];
	uपूर्णांक32_t total_len;
पूर्ण;

काष्ठा __ec_align4 ec_param_ec_codec_wov अणु
	uपूर्णांक8_t cmd; /* क्रमागत ec_codec_wov_subcmd */
	uपूर्णांक8_t reserved[3];

	जोड़ अणु
		काष्ठा ec_param_ec_codec_wov_set_lang
				set_lang_param;
		काष्ठा ec_param_ec_codec_wov_set_lang_shm
				set_lang_shm_param;
	पूर्ण;
पूर्ण;

काष्ठा __ec_align4 ec_response_ec_codec_wov_get_lang अणु
	uपूर्णांक8_t hash[32];
पूर्ण;

काष्ठा __ec_align4 ec_response_ec_codec_wov_पढ़ो_audio अणु
	uपूर्णांक8_t buf[128];
	uपूर्णांक32_t len;
पूर्ण;

काष्ठा __ec_align4 ec_response_ec_codec_wov_पढ़ो_audio_shm अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t len;
पूर्ण;

/*****************************************************************************/
/* System commands */

/*
 * TODO(crosbug.com/p/23747): This is a confusing name, since it करोesn't
 * necessarily reboot the EC.  Rename to "image" or something similar?
 */
#घोषणा EC_CMD_REBOOT_EC 0x00D2

/* Command */
क्रमागत ec_reboot_cmd अणु
	EC_REBOOT_CANCEL = 0,        /* Cancel a pending reboot */
	EC_REBOOT_JUMP_RO = 1,       /* Jump to RO without rebooting */
	EC_REBOOT_JUMP_RW = 2,       /* Jump to active RW without rebooting */
	/* (command 3 was jump to RW-B) */
	EC_REBOOT_COLD = 4,          /* Cold-reboot */
	EC_REBOOT_DISABLE_JUMP = 5,  /* Disable jump until next reboot */
	EC_REBOOT_HIBERNATE = 6,     /* Hibernate EC */
	EC_REBOOT_HIBERNATE_CLEAR_AP_OFF = 7, /* and clears AP_OFF flag */
	EC_REBOOT_COLD_AP_OFF = 8,   /* Cold-reboot and करोn't boot AP */
पूर्ण;

/* Flags क्रम ec_params_reboot_ec.reboot_flags */
#घोषणा EC_REBOOT_FLAG_RESERVED0      BIT(0)  /* Was recovery request */
#घोषणा EC_REBOOT_FLAG_ON_AP_SHUTDOWN BIT(1)  /* Reboot after AP shutकरोwn */
#घोषणा EC_REBOOT_FLAG_SWITCH_RW_SLOT BIT(2)  /* Switch RW slot */

काष्ठा ec_params_reboot_ec अणु
	uपूर्णांक8_t cmd;           /* क्रमागत ec_reboot_cmd */
	uपूर्णांक8_t flags;         /* See EC_REBOOT_FLAG_* */
पूर्ण __ec_align1;

/*
 * Get inक्रमmation on last EC panic.
 *
 * Returns variable-length platक्रमm-dependent panic inक्रमmation.  See panic.h
 * क्रम details.
 */
#घोषणा EC_CMD_GET_PANIC_INFO 0x00D3

/*****************************************************************************/
/*
 * Special commands
 *
 * These करो not follow the normal rules क्रम commands.  See each command क्रम
 * details.
 */

/*
 * Reboot NOW
 *
 * This command will work even when the EC LPC पूर्णांकerface is busy, because the
 * reboot command is processed at पूर्णांकerrupt level.  Note that when the EC
 * reboots, the host will reboot too, so there is no response to this command.
 *
 * Use EC_CMD_REBOOT_EC to reboot the EC more politely.
 */
#घोषणा EC_CMD_REBOOT 0x00D1  /* Think "die" */

/*
 * Resend last response (not supported on LPC).
 *
 * Returns EC_RES_UNAVAILABLE अगर there is no response available - क्रम example,
 * there was no previous command, or the previous command's response was too
 * big to save.
 */
#घोषणा EC_CMD_RESEND_RESPONSE 0x00DB

/*
 * This header byte on a command indicate version 0. Any header byte less
 * than this means that we are talking to an old EC which करोesn't support
 * versioning. In that हाल, we assume version 0.
 *
 * Header bytes greater than this indicate a later version. For example,
 * EC_CMD_VERSION0 + 1 means we are using version 1.
 *
 * The old EC पूर्णांकerface must not use commands 0xdc or higher.
 */
#घोषणा EC_CMD_VERSION0 0x00DC

/*****************************************************************************/
/*
 * PD commands
 *
 * These commands are क्रम PD MCU communication.
 */

/* EC to PD MCU exchange status command */
#घोषणा EC_CMD_PD_EXCHANGE_STATUS 0x0100
#घोषणा EC_VER_PD_EXCHANGE_STATUS 2

क्रमागत pd_अक्षरge_state अणु
	PD_CHARGE_NO_CHANGE = 0, /* Don't change अक्षरge state */
	PD_CHARGE_NONE,          /* No अक्षरging allowed */
	PD_CHARGE_5V,            /* 5V अक्षरging only */
	PD_CHARGE_MAX            /* Charge at max voltage */
पूर्ण;

/* Status of EC being sent to PD */
#घोषणा EC_STATUS_HIBERNATING	BIT(0)

काष्ठा ec_params_pd_status अणु
	uपूर्णांक8_t status;       /* EC status */
	पूर्णांक8_t batt_soc;      /* battery state of अक्षरge */
	uपूर्णांक8_t अक्षरge_state; /* अक्षरging state (from क्रमागत pd_अक्षरge_state) */
पूर्ण __ec_align1;

/* Status of PD being sent back to EC */
#घोषणा PD_STATUS_HOST_EVENT      BIT(0) /* Forward host event to AP */
#घोषणा PD_STATUS_IN_RW           BIT(1) /* Running RW image */
#घोषणा PD_STATUS_JUMPED_TO_IMAGE BIT(2) /* Current image was jumped to */
#घोषणा PD_STATUS_TCPC_ALERT_0    BIT(3) /* Alert active in port 0 TCPC */
#घोषणा PD_STATUS_TCPC_ALERT_1    BIT(4) /* Alert active in port 1 TCPC */
#घोषणा PD_STATUS_TCPC_ALERT_2    BIT(5) /* Alert active in port 2 TCPC */
#घोषणा PD_STATUS_TCPC_ALERT_3    BIT(6) /* Alert active in port 3 TCPC */
#घोषणा PD_STATUS_EC_INT_ACTIVE  (PD_STATUS_TCPC_ALERT_0 | \
				      PD_STATUS_TCPC_ALERT_1 | \
				      PD_STATUS_HOST_EVENT)
काष्ठा ec_response_pd_status अणु
	uपूर्णांक32_t curr_lim_ma;       /* input current limit */
	uपूर्णांक16_t status;            /* PD MCU status */
	पूर्णांक8_t active_अक्षरge_port;  /* active अक्षरging port */
पूर्ण __ec_align_size1;

/* AP to PD MCU host event status command, cleared on पढ़ो */
#घोषणा EC_CMD_PD_HOST_EVENT_STATUS 0x0104

/* PD MCU host event status bits */
#घोषणा PD_EVENT_UPDATE_DEVICE     BIT(0)
#घोषणा PD_EVENT_POWER_CHANGE      BIT(1)
#घोषणा PD_EVENT_IDENTITY_RECEIVED BIT(2)
#घोषणा PD_EVENT_DATA_SWAP         BIT(3)
काष्ठा ec_response_host_event_status अणु
	uपूर्णांक32_t status;      /* PD MCU host event status */
पूर्ण __ec_align4;

/* Set USB type-C port role and muxes */
#घोषणा EC_CMD_USB_PD_CONTROL 0x0101

क्रमागत usb_pd_control_role अणु
	USB_PD_CTRL_ROLE_NO_CHANGE = 0,
	USB_PD_CTRL_ROLE_TOGGLE_ON = 1, /* == AUTO */
	USB_PD_CTRL_ROLE_TOGGLE_OFF = 2,
	USB_PD_CTRL_ROLE_FORCE_SINK = 3,
	USB_PD_CTRL_ROLE_FORCE_SOURCE = 4,
	USB_PD_CTRL_ROLE_FREEZE = 5,
	USB_PD_CTRL_ROLE_COUNT
पूर्ण;

क्रमागत usb_pd_control_mux अणु
	USB_PD_CTRL_MUX_NO_CHANGE = 0,
	USB_PD_CTRL_MUX_NONE = 1,
	USB_PD_CTRL_MUX_USB = 2,
	USB_PD_CTRL_MUX_DP = 3,
	USB_PD_CTRL_MUX_DOCK = 4,
	USB_PD_CTRL_MUX_AUTO = 5,
	USB_PD_CTRL_MUX_COUNT
पूर्ण;

क्रमागत usb_pd_control_swap अणु
	USB_PD_CTRL_SWAP_NONE = 0,
	USB_PD_CTRL_SWAP_DATA = 1,
	USB_PD_CTRL_SWAP_POWER = 2,
	USB_PD_CTRL_SWAP_VCONN = 3,
	USB_PD_CTRL_SWAP_COUNT
पूर्ण;

काष्ठा ec_params_usb_pd_control अणु
	uपूर्णांक8_t port;
	uपूर्णांक8_t role;
	uपूर्णांक8_t mux;
	uपूर्णांक8_t swap;
पूर्ण __ec_align1;

#घोषणा PD_CTRL_RESP_ENABLED_COMMS      BIT(0) /* Communication enabled */
#घोषणा PD_CTRL_RESP_ENABLED_CONNECTED  BIT(1) /* Device connected */
#घोषणा PD_CTRL_RESP_ENABLED_PD_CAPABLE BIT(2) /* Partner is PD capable */

#घोषणा PD_CTRL_RESP_ROLE_POWER         BIT(0) /* 0=SNK/1=SRC */
#घोषणा PD_CTRL_RESP_ROLE_DATA          BIT(1) /* 0=UFP/1=DFP */
#घोषणा PD_CTRL_RESP_ROLE_VCONN         BIT(2) /* Vconn status */
#घोषणा PD_CTRL_RESP_ROLE_DR_POWER      BIT(3) /* Partner is dualrole घातer */
#घोषणा PD_CTRL_RESP_ROLE_DR_DATA       BIT(4) /* Partner is dualrole data */
#घोषणा PD_CTRL_RESP_ROLE_USB_COMM      BIT(5) /* Partner USB comm capable */
#घोषणा PD_CTRL_RESP_ROLE_EXT_POWERED   BIT(6) /* Partner बाह्यally घातerd */

काष्ठा ec_response_usb_pd_control अणु
	uपूर्णांक8_t enabled;
	uपूर्णांक8_t role;
	uपूर्णांक8_t polarity;
	uपूर्णांक8_t state;
पूर्ण __ec_align1;

काष्ठा ec_response_usb_pd_control_v1 अणु
	uपूर्णांक8_t enabled;
	uपूर्णांक8_t role;
	uपूर्णांक8_t polarity;
	अक्षर state[32];
पूर्ण __ec_align1;

/* Values representing usbc PD CC state */
#घोषणा USBC_PD_CC_NONE		0 /* No accessory connected */
#घोषणा USBC_PD_CC_NO_UFP	1 /* No UFP accessory connected */
#घोषणा USBC_PD_CC_AUDIO_ACC	2 /* Audio accessory connected */
#घोषणा USBC_PD_CC_DEBUG_ACC	3 /* Debug accessory connected */
#घोषणा USBC_PD_CC_UFP_ATTACHED	4 /* UFP attached to usbc */
#घोषणा USBC_PD_CC_DFP_ATTACHED	5 /* DPF attached to usbc */

/* Active/Passive Cable */
#घोषणा USB_PD_CTRL_ACTIVE_CABLE        BIT(0)
/* Optical/Non-optical cable */
#घोषणा USB_PD_CTRL_OPTICAL_CABLE       BIT(1)
/* 3rd Gen TBT device (or AMA)/2nd gen tbt Adapter */
#घोषणा USB_PD_CTRL_TBT_LEGACY_ADAPTER  BIT(2)
/* Active Link Uni-Direction */
#घोषणा USB_PD_CTRL_ACTIVE_LINK_UNIसूची  BIT(3)

काष्ठा ec_response_usb_pd_control_v2 अणु
	uपूर्णांक8_t enabled;
	uपूर्णांक8_t role;
	uपूर्णांक8_t polarity;
	अक्षर state[32];
	uपूर्णांक8_t cc_state;	/* क्रमागत pd_cc_states representing cc state */
	uपूर्णांक8_t dp_mode;	/* Current DP pin mode (MODE_DP_PIN_[A-E]) */
	uपूर्णांक8_t reserved;	/* Reserved क्रम future use */
	uपूर्णांक8_t control_flags;	/* USB_PD_CTRL_*flags */
	uपूर्णांक8_t cable_speed;	/* TBT_SS_* cable speed */
	uपूर्णांक8_t cable_gen;	/* TBT_GEN3_* cable rounded support */
पूर्ण __ec_align1;

#घोषणा EC_CMD_USB_PD_PORTS 0x0102

/* Maximum number of PD ports on a device, num_ports will be <= this */
#घोषणा EC_USB_PD_MAX_PORTS 8

काष्ठा ec_response_usb_pd_ports अणु
	uपूर्णांक8_t num_ports;
पूर्ण __ec_align1;

#घोषणा EC_CMD_USB_PD_POWER_INFO 0x0103

#घोषणा PD_POWER_CHARGING_PORT 0xff
काष्ठा ec_params_usb_pd_घातer_info अणु
	uपूर्णांक8_t port;
पूर्ण __ec_align1;

क्रमागत usb_chg_type अणु
	USB_CHG_TYPE_NONE,
	USB_CHG_TYPE_PD,
	USB_CHG_TYPE_C,
	USB_CHG_TYPE_PROPRIETARY,
	USB_CHG_TYPE_BC12_DCP,
	USB_CHG_TYPE_BC12_CDP,
	USB_CHG_TYPE_BC12_SDP,
	USB_CHG_TYPE_OTHER,
	USB_CHG_TYPE_VBUS,
	USB_CHG_TYPE_UNKNOWN,
	USB_CHG_TYPE_DEDICATED,
पूर्ण;
क्रमागत usb_घातer_roles अणु
	USB_PD_PORT_POWER_DISCONNECTED,
	USB_PD_PORT_POWER_SOURCE,
	USB_PD_PORT_POWER_SINK,
	USB_PD_PORT_POWER_SINK_NOT_CHARGING,
पूर्ण;

काष्ठा usb_chg_measures अणु
	uपूर्णांक16_t voltage_max;
	uपूर्णांक16_t voltage_now;
	uपूर्णांक16_t current_max;
	uपूर्णांक16_t current_lim;
पूर्ण __ec_align2;

काष्ठा ec_response_usb_pd_घातer_info अणु
	uपूर्णांक8_t role;
	uपूर्णांक8_t type;
	uपूर्णांक8_t dualrole;
	uपूर्णांक8_t reserved1;
	काष्ठा usb_chg_measures meas;
	uपूर्णांक32_t max_घातer;
पूर्ण __ec_align4;


/*
 * This command will वापस the number of USB PD अक्षरge port + the number
 * of dedicated port present.
 * EC_CMD_USB_PD_PORTS करोes NOT include the dedicated ports
 */
#घोषणा EC_CMD_CHARGE_PORT_COUNT 0x0105
काष्ठा ec_response_अक्षरge_port_count अणु
	uपूर्णांक8_t port_count;
पूर्ण __ec_align1;

/* Write USB-PD device FW */
#घोषणा EC_CMD_USB_PD_FW_UPDATE 0x0110

क्रमागत usb_pd_fw_update_cmds अणु
	USB_PD_FW_REBOOT,
	USB_PD_FW_FLASH_ERASE,
	USB_PD_FW_FLASH_WRITE,
	USB_PD_FW_ERASE_SIG,
पूर्ण;

काष्ठा ec_params_usb_pd_fw_update अणु
	uपूर्णांक16_t dev_id;
	uपूर्णांक8_t cmd;
	uपूर्णांक8_t port;
	uपूर्णांक32_t size;     /* Size to ग_लिखो in bytes */
	/* Followed by data to ग_लिखो */
पूर्ण __ec_align4;

/* Write USB-PD Accessory RW_HASH table entry */
#घोषणा EC_CMD_USB_PD_RW_HASH_ENTRY 0x0111
/* RW hash is first 20 bytes of SHA-256 of RW section */
#घोषणा PD_RW_HASH_SIZE 20
काष्ठा ec_params_usb_pd_rw_hash_entry अणु
	uपूर्णांक16_t dev_id;
	uपूर्णांक8_t dev_rw_hash[PD_RW_HASH_SIZE];
	uपूर्णांक8_t reserved;        /*
				  * For alignment of current_image
				  * TODO(rspangler) but it's not aligned!
				  * Should have been reserved[2].
				  */
	uपूर्णांक32_t current_image;  /* One of ec_current_image */
पूर्ण __ec_align1;

/* Read USB-PD Accessory info */
#घोषणा EC_CMD_USB_PD_DEV_INFO 0x0112

काष्ठा ec_params_usb_pd_info_request अणु
	uपूर्णांक8_t port;
पूर्ण __ec_align1;

/* Read USB-PD Device discovery info */
#घोषणा EC_CMD_USB_PD_DISCOVERY 0x0113
काष्ठा ec_params_usb_pd_discovery_entry अणु
	uपूर्णांक16_t vid;  /* USB-IF VID */
	uपूर्णांक16_t pid;  /* USB-IF PID */
	uपूर्णांक8_t ptype; /* product type (hub,periph,cable,ama) */
पूर्ण __ec_align_size1;

/* Override शेष अक्षरge behavior */
#घोषणा EC_CMD_PD_CHARGE_PORT_OVERRIDE 0x0114

/* Negative port parameters have special meaning */
क्रमागत usb_pd_override_ports अणु
	OVERRIDE_DONT_CHARGE = -2,
	OVERRIDE_OFF = -1,
	/* [0, CONFIG_USB_PD_PORT_COUNT): Port# */
पूर्ण;

काष्ठा ec_params_अक्षरge_port_override अणु
	पूर्णांक16_t override_port; /* Override port# */
पूर्ण __ec_align2;

/*
 * Read (and delete) one entry of PD event log.
 * TODO(crbug.com/751742): Make this host command more generic to accommodate
 * future non-PD logs that use the same पूर्णांकernal EC event_log.
 */
#घोषणा EC_CMD_PD_GET_LOG_ENTRY 0x0115

काष्ठा ec_response_pd_log अणु
	uपूर्णांक32_t बारtamp; /* relative बारtamp in milliseconds */
	uपूर्णांक8_t type;       /* event type : see PD_EVENT_xx below */
	uपूर्णांक8_t size_port;  /* [7:5] port number [4:0] payload size in bytes */
	uपूर्णांक16_t data;      /* type-defined data payload */
	uपूर्णांक8_t payload[];  /* optional additional data payload: 0..16 bytes */
पूर्ण __ec_align4;

/* The बारtamp is the microsecond counter shअगरted to get about a ms. */
#घोषणा PD_LOG_TIMESTAMP_SHIFT 10 /* 1 LSB = 1024us */

#घोषणा PD_LOG_SIZE_MASK  0x1f
#घोषणा PD_LOG_PORT_MASK  0xe0
#घोषणा PD_LOG_PORT_SHIFT    5
#घोषणा PD_LOG_PORT_SIZE(port, size) (((port) << PD_LOG_PORT_SHIFT) | \
				      ((size) & PD_LOG_SIZE_MASK))
#घोषणा PD_LOG_PORT(size_port) ((size_port) >> PD_LOG_PORT_SHIFT)
#घोषणा PD_LOG_SIZE(size_port) ((size_port) & PD_LOG_SIZE_MASK)

/* PD event log : entry types */
/* PD MCU events */
#घोषणा PD_EVENT_MCU_BASE       0x00
#घोषणा PD_EVENT_MCU_CHARGE             (PD_EVENT_MCU_BASE+0)
#घोषणा PD_EVENT_MCU_CONNECT            (PD_EVENT_MCU_BASE+1)
/* Reserved क्रम custom board event */
#घोषणा PD_EVENT_MCU_BOARD_CUSTOM       (PD_EVENT_MCU_BASE+2)
/* PD generic accessory events */
#घोषणा PD_EVENT_ACC_BASE       0x20
#घोषणा PD_EVENT_ACC_RW_FAIL   (PD_EVENT_ACC_BASE+0)
#घोषणा PD_EVENT_ACC_RW_ERASE  (PD_EVENT_ACC_BASE+1)
/* PD घातer supply events */
#घोषणा PD_EVENT_PS_BASE        0x40
#घोषणा PD_EVENT_PS_FAULT      (PD_EVENT_PS_BASE+0)
/* PD video करोngles events */
#घोषणा PD_EVENT_VIDEO_BASE     0x60
#घोषणा PD_EVENT_VIDEO_DP_MODE (PD_EVENT_VIDEO_BASE+0)
#घोषणा PD_EVENT_VIDEO_CODEC   (PD_EVENT_VIDEO_BASE+1)
/* Returned in the "type" field, when there is no entry available */
#घोषणा PD_EVENT_NO_ENTRY       0xff

/*
 * PD_EVENT_MCU_CHARGE event definition :
 * the payload is "struct usb_chg_measures"
 * the data field contains the port state flags as defined below :
 */
/* Port partner is a dual role device */
#घोषणा CHARGE_FLAGS_DUAL_ROLE         BIT(15)
/* Port is the pending override port */
#घोषणा CHARGE_FLAGS_DELAYED_OVERRIDE  BIT(14)
/* Port is the override port */
#घोषणा CHARGE_FLAGS_OVERRIDE          BIT(13)
/* Charger type */
#घोषणा CHARGE_FLAGS_TYPE_SHIFT               3
#घोषणा CHARGE_FLAGS_TYPE_MASK       (0xf << CHARGE_FLAGS_TYPE_SHIFT)
/* Power delivery role */
#घोषणा CHARGE_FLAGS_ROLE_MASK         (7 <<  0)

/*
 * PD_EVENT_PS_FAULT data field flags definition :
 */
#घोषणा PS_FAULT_OCP                          1
#घोषणा PS_FAULT_FAST_OCP                     2
#घोषणा PS_FAULT_OVP                          3
#घोषणा PS_FAULT_DISCH                        4

/*
 * PD_EVENT_VIDEO_CODEC payload is "struct mcdp_info".
 */
काष्ठा mcdp_version अणु
	uपूर्णांक8_t major;
	uपूर्णांक8_t minor;
	uपूर्णांक16_t build;
पूर्ण __ec_align4;

काष्ठा mcdp_info अणु
	uपूर्णांक8_t family[2];
	uपूर्णांक8_t chipid[2];
	काष्ठा mcdp_version irom;
	काष्ठा mcdp_version fw;
पूर्ण __ec_align4;

/* काष्ठा mcdp_info field decoding */
#घोषणा MCDP_CHIPID(chipid) ((chipid[0] << 8) | chipid[1])
#घोषणा MCDP_FAMILY(family) ((family[0] << 8) | family[1])

/* Get/Set USB-PD Alternate mode info */
#घोषणा EC_CMD_USB_PD_GET_AMODE 0x0116
काष्ठा ec_params_usb_pd_get_mode_request अणु
	uपूर्णांक16_t svid_idx; /* SVID index to get */
	uपूर्णांक8_t port;      /* port */
पूर्ण __ec_align_size1;

काष्ठा ec_params_usb_pd_get_mode_response अणु
	uपूर्णांक16_t svid;   /* SVID */
	uपूर्णांक16_t opos;    /* Object Position */
	uपूर्णांक32_t vकरो[6]; /* Mode VDOs */
पूर्ण __ec_align4;

#घोषणा EC_CMD_USB_PD_SET_AMODE 0x0117

क्रमागत pd_mode_cmd अणु
	PD_EXIT_MODE = 0,
	PD_ENTER_MODE = 1,
	/* Not a command.  Do NOT हटाओ. */
	PD_MODE_CMD_COUNT,
पूर्ण;

काष्ठा ec_params_usb_pd_set_mode_request अणु
	uपूर्णांक32_t cmd;  /* क्रमागत pd_mode_cmd */
	uपूर्णांक16_t svid; /* SVID to set */
	uपूर्णांक8_t opos;  /* Object Position */
	uपूर्णांक8_t port;  /* port */
पूर्ण __ec_align4;

/* Ask the PD MCU to record a log of a requested type */
#घोषणा EC_CMD_PD_WRITE_LOG_ENTRY 0x0118

काष्ठा ec_params_pd_ग_लिखो_log_entry अणु
	uपूर्णांक8_t type; /* event type : see PD_EVENT_xx above */
	uपूर्णांक8_t port; /* port#, or 0 क्रम events unrelated to a given port */
पूर्ण __ec_align1;


/* Control USB-PD chip */
#घोषणा EC_CMD_PD_CONTROL 0x0119

क्रमागत ec_pd_control_cmd अणु
	PD_SUSPEND = 0,      /* Suspend the PD chip (EC: stop talking to PD) */
	PD_RESUME,           /* Resume the PD chip (EC: start talking to PD) */
	PD_RESET,            /* Force reset the PD chip */
	PD_CONTROL_DISABLE,  /* Disable further calls to this command */
	PD_CHIP_ON,          /* Power on the PD chip */
पूर्ण;

काष्ठा ec_params_pd_control अणु
	uपूर्णांक8_t chip;         /* chip id */
	uपूर्णांक8_t subcmd;
पूर्ण __ec_align1;

/* Get info about USB-C SS muxes */
#घोषणा EC_CMD_USB_PD_MUX_INFO 0x011A

काष्ठा ec_params_usb_pd_mux_info अणु
	uपूर्णांक8_t port; /* USB-C port number */
पूर्ण __ec_align1;

/* Flags representing mux state */
#घोषणा USB_PD_MUX_NONE               0      /* Open चयन */
#घोषणा USB_PD_MUX_USB_ENABLED        BIT(0) /* USB connected */
#घोषणा USB_PD_MUX_DP_ENABLED         BIT(1) /* DP connected */
#घोषणा USB_PD_MUX_POLARITY_INVERTED  BIT(2) /* CC line Polarity inverted */
#घोषणा USB_PD_MUX_HPD_IRQ            BIT(3) /* HPD IRQ is निश्चितed */
#घोषणा USB_PD_MUX_HPD_LVL            BIT(4) /* HPD level is निश्चितed */
#घोषणा USB_PD_MUX_SAFE_MODE          BIT(5) /* DP is in safe mode */
#घोषणा USB_PD_MUX_TBT_COMPAT_ENABLED BIT(6) /* TBT compat enabled */
#घोषणा USB_PD_MUX_USB4_ENABLED       BIT(7) /* USB4 enabled */

काष्ठा ec_response_usb_pd_mux_info अणु
	uपूर्णांक8_t flags; /* USB_PD_MUX_*-encoded USB mux state */
पूर्ण __ec_align1;

#घोषणा EC_CMD_PD_CHIP_INFO		0x011B

काष्ठा ec_params_pd_chip_info अणु
	uपूर्णांक8_t port;	/* USB-C port number */
	uपूर्णांक8_t renew;	/* Force renewal */
पूर्ण __ec_align1;

काष्ठा ec_response_pd_chip_info अणु
	uपूर्णांक16_t venकरोr_id;
	uपूर्णांक16_t product_id;
	uपूर्णांक16_t device_id;
	जोड़ अणु
		uपूर्णांक8_t fw_version_string[8];
		uपूर्णांक64_t fw_version_number;
	पूर्ण;
पूर्ण __ec_align2;

काष्ठा ec_response_pd_chip_info_v1 अणु
	uपूर्णांक16_t venकरोr_id;
	uपूर्णांक16_t product_id;
	uपूर्णांक16_t device_id;
	जोड़ अणु
		uपूर्णांक8_t fw_version_string[8];
		uपूर्णांक64_t fw_version_number;
	पूर्ण;
	जोड़ अणु
		uपूर्णांक8_t min_req_fw_version_string[8];
		uपूर्णांक64_t min_req_fw_version_number;
	पूर्ण;
पूर्ण __ec_align2;

/* Run RW signature verअगरication and get status */
#घोषणा EC_CMD_RWSIG_CHECK_STATUS	0x011C

काष्ठा ec_response_rwsig_check_status अणु
	uपूर्णांक32_t status;
पूर्ण __ec_align4;

/* For controlling RWSIG task */
#घोषणा EC_CMD_RWSIG_ACTION	0x011D

क्रमागत rwsig_action अणु
	RWSIG_ACTION_ABORT = 0,		/* Abort RWSIG and prevent jumping */
	RWSIG_ACTION_CONTINUE = 1,	/* Jump to RW immediately */
पूर्ण;

काष्ठा ec_params_rwsig_action अणु
	uपूर्णांक32_t action;
पूर्ण __ec_align4;

/* Run verअगरication on a slot */
#घोषणा EC_CMD_EFS_VERIFY	0x011E

काष्ठा ec_params_efs_verअगरy अणु
	uपूर्णांक8_t region;		/* क्रमागत ec_flash_region */
पूर्ण __ec_align1;

/*
 * Retrieve info from Cros Board Info store. Response is based on the data
 * type. Integers वापस a uपूर्णांक32. Strings वापस a string, using the response
 * size to determine how big it is.
 */
#घोषणा EC_CMD_GET_CROS_BOARD_INFO	0x011F
/*
 * Write info पूर्णांकo Cros Board Info on EEPROM. Write fails अगर the board has
 * hardware ग_लिखो-protect enabled.
 */
#घोषणा EC_CMD_SET_CROS_BOARD_INFO	0x0120

क्रमागत cbi_data_tag अणु
	CBI_TAG_BOARD_VERSION = 0, /* uपूर्णांक32_t or smaller */
	CBI_TAG_OEM_ID = 1,        /* uपूर्णांक32_t or smaller */
	CBI_TAG_SKU_ID = 2,        /* uपूर्णांक32_t or smaller */
	CBI_TAG_DRAM_PART_NUM = 3, /* variable length ascii, nul terminated. */
	CBI_TAG_OEM_NAME = 4,      /* variable length ascii, nul terminated. */
	CBI_TAG_MODEL_ID = 5,      /* uपूर्णांक32_t or smaller */
	CBI_TAG_COUNT,
पूर्ण;

/*
 * Flags to control पढ़ो operation
 *
 * RELOAD:  Invalidate cache and पढ़ो data from EEPROM. Useful to verअगरy
 *          ग_लिखो was successful without reboot.
 */
#घोषणा CBI_GET_RELOAD		BIT(0)

काष्ठा ec_params_get_cbi अणु
	uपूर्णांक32_t tag;		/* क्रमागत cbi_data_tag */
	uपूर्णांक32_t flag;		/* CBI_GET_* */
पूर्ण __ec_align4;

/*
 * Flags to control ग_लिखो behavior.
 *
 * NO_SYNC: Makes EC update data in RAM but skip writing to EEPROM. It's
 *          useful when writing multiple fields in a row.
 * INIT:    Need to be set when creating a new CBI from scratch. All fields
 *          will be initialized to zero first.
 */
#घोषणा CBI_SET_NO_SYNC		BIT(0)
#घोषणा CBI_SET_INIT		BIT(1)

काष्ठा ec_params_set_cbi अणु
	uपूर्णांक32_t tag;		/* क्रमागत cbi_data_tag */
	uपूर्णांक32_t flag;		/* CBI_SET_* */
	uपूर्णांक32_t size;		/* Data size */
	uपूर्णांक8_t data[];		/* For string and raw data */
पूर्ण __ec_align1;

/*
 * Inक्रमmation about resets of the AP by the EC and the EC's own upसमय.
 */
#घोषणा EC_CMD_GET_UPTIME_INFO 0x0121

काष्ठा ec_response_upसमय_info अणु
	/*
	 * Number of milliseconds since the last EC boot. Sysjump resets
	 * typically करो not restart the EC's समय_since_boot epoch.
	 *
	 * WARNING: The EC's sense of time is much less accurate than the AP's
	 * sense of समय, in both phase and frequency.  This समयbase is similar
	 * to CLOCK_MONOTONIC_RAW, but with 1% or more frequency error.
	 */
	uपूर्णांक32_t समय_since_ec_boot_ms;

	/*
	 * Number of बार the AP was reset by the EC since the last EC boot.
	 * Note that the AP may be held in reset by the EC during the initial
	 * boot sequence, such that the very first AP boot may count as more
	 * than one here.
	 */
	uपूर्णांक32_t ap_resets_since_ec_boot;

	/*
	 * The set of flags which describe the EC's most recent reset.  See
	 * include/प्रणाली.h RESET_FLAG_* क्रम details.
	 */
	uपूर्णांक32_t ec_reset_flags;

	/* Empty log entries have both the cause and बारtamp set to zero. */
	काष्ठा ap_reset_log_entry अणु
		/*
		 * See include/chipset.h: क्रमागत chipset_अणुreset,shutकरोwnपूर्ण_reason
		 * क्रम details.
		 */
		uपूर्णांक16_t reset_cause;

		/* Reserved क्रम protocol growth. */
		uपूर्णांक16_t reserved;

		/*
		 * The समय of the reset's निश्चितion, in milliseconds since the
		 * last EC boot, in the same epoch as समय_since_ec_boot_ms.
		 * Set to zero अगर the log entry is empty.
		 */
		uपूर्णांक32_t reset_समय_ms;
	पूर्ण recent_ap_reset[4];
पूर्ण __ec_align4;

/*
 * Add entropy to the device secret (stored in the rollback region).
 *
 * Depending on the chip, the operation may take a दीर्घ समय (e.g. to erase
 * flash), so the commands are asynchronous.
 */
#घोषणा EC_CMD_ADD_ENTROPY	0x0122

क्रमागत add_entropy_action अणु
	/* Add entropy to the current secret. */
	ADD_ENTROPY_ASYNC = 0,
	/*
	 * Add entropy, and also make sure that the previous secret is erased.
	 * (this can be implemented by adding entropy multiple बार until
	 * all rolback blocks have been overwritten).
	 */
	ADD_ENTROPY_RESET_ASYNC = 1,
	/* Read back result from the previous operation. */
	ADD_ENTROPY_GET_RESULT = 2,
पूर्ण;

काष्ठा ec_params_rollback_add_entropy अणु
	uपूर्णांक8_t action;
पूर्ण __ec_align1;

/*
 * Perक्रमm a single पढ़ो of a given ADC channel.
 */
#घोषणा EC_CMD_ADC_READ		0x0123

काष्ठा ec_params_adc_पढ़ो अणु
	uपूर्णांक8_t adc_channel;
पूर्ण __ec_align1;

काष्ठा ec_response_adc_पढ़ो अणु
	पूर्णांक32_t adc_value;
पूर्ण __ec_align4;

/*
 * Read back rollback info
 */
#घोषणा EC_CMD_ROLLBACK_INFO		0x0124

काष्ठा ec_response_rollback_info अणु
	पूर्णांक32_t id; /* Incrementing number to indicate which region to use. */
	पूर्णांक32_t rollback_min_version;
	पूर्णांक32_t rw_rollback_version;
पूर्ण __ec_align4;


/* Issue AP reset */
#घोषणा EC_CMD_AP_RESET 0x0125

/*****************************************************************************/
/* Voltage regulator controls */

/*
 * Get basic info of voltage regulator क्रम given index.
 *
 * Returns the regulator name and supported voltage list in mV.
 */
#घोषणा EC_CMD_REGULATOR_GET_INFO 0x012C

/* Maximum length of regulator name */
#घोषणा EC_REGULATOR_NAME_MAX_LEN 16

/* Maximum length of the supported voltage list. */
#घोषणा EC_REGULATOR_VOLTAGE_MAX_COUNT 16

काष्ठा ec_params_regulator_get_info अणु
	uपूर्णांक32_t index;
पूर्ण __ec_align4;

काष्ठा ec_response_regulator_get_info अणु
	अक्षर name[EC_REGULATOR_NAME_MAX_LEN];
	uपूर्णांक16_t num_voltages;
	uपूर्णांक16_t voltages_mv[EC_REGULATOR_VOLTAGE_MAX_COUNT];
पूर्ण __ec_align2;

/*
 * Configure the regulator as enabled / disabled.
 */
#घोषणा EC_CMD_REGULATOR_ENABLE 0x012D

काष्ठा ec_params_regulator_enable अणु
	uपूर्णांक32_t index;
	uपूर्णांक8_t enable;
पूर्ण __ec_align4;

/*
 * Query अगर the regulator is enabled.
 *
 * Returns 1 अगर the regulator is enabled, 0 अगर not.
 */
#घोषणा EC_CMD_REGULATOR_IS_ENABLED 0x012E

काष्ठा ec_params_regulator_is_enabled अणु
	uपूर्णांक32_t index;
पूर्ण __ec_align4;

काष्ठा ec_response_regulator_is_enabled अणु
	uपूर्णांक8_t enabled;
पूर्ण __ec_align1;

/*
 * Set voltage क्रम the voltage regulator within the range specअगरied.
 *
 * The driver should select the voltage in range बंदst to min_mv.
 *
 * Also note that this might be called beक्रमe the regulator is enabled, and the
 * setting should be in effect after the regulator is enabled.
 */
#घोषणा EC_CMD_REGULATOR_SET_VOLTAGE 0x012F

काष्ठा ec_params_regulator_set_voltage अणु
	uपूर्णांक32_t index;
	uपूर्णांक32_t min_mv;
	uपूर्णांक32_t max_mv;
पूर्ण __ec_align4;

/*
 * Get the currently configured voltage क्रम the voltage regulator.
 *
 * Note that this might be called beक्रमe the regulator is enabled, and this
 * should वापस the configured output voltage अगर the regulator is enabled.
 */
#घोषणा EC_CMD_REGULATOR_GET_VOLTAGE 0x0130

काष्ठा ec_params_regulator_get_voltage अणु
	uपूर्णांक32_t index;
पूर्ण __ec_align4;

काष्ठा ec_response_regulator_get_voltage अणु
	uपूर्णांक32_t voltage_mv;
पूर्ण __ec_align4;

/*
 * Gather all discovery inक्रमmation क्रम the given port and partner type.
 *
 * Note that अगर discovery has not yet completed, only the currently completed
 * responses will be filled in.   If the discovery data काष्ठाures are changed
 * in the process of the command running, BUSY will be वापसed.
 *
 * VDO field sizes are set to the maximum possible number of VDOs a VDM may
 * contain, जबतक the number of SVIDs here is selected to fit within the PROTO2
 * maximum parameter size.
 */
#घोषणा EC_CMD_TYPEC_DISCOVERY 0x0131

क्रमागत typec_partner_type अणु
	TYPEC_PARTNER_SOP = 0,
	TYPEC_PARTNER_SOP_PRIME = 1,
पूर्ण;

काष्ठा ec_params_typec_discovery अणु
	uपूर्णांक8_t port;
	uपूर्णांक8_t partner_type; /* क्रमागत typec_partner_type */
पूर्ण __ec_align1;

काष्ठा svid_mode_info अणु
	uपूर्णांक16_t svid;
	uपूर्णांक16_t mode_count;  /* Number of modes partner sent */
	uपूर्णांक32_t mode_vकरो[6]; /* Max VDOs allowed after VDM header is 6 */
पूर्ण;

काष्ठा ec_response_typec_discovery अणु
	uपूर्णांक8_t identity_count;    /* Number of identity VDOs partner sent */
	uपूर्णांक8_t svid_count;	   /* Number of SVIDs partner sent */
	uपूर्णांक16_t reserved;
	uपूर्णांक32_t discovery_vकरो[6]; /* Max VDOs allowed after VDM header is 6 */
	काष्ठा svid_mode_info svids[0];
पूर्ण __ec_align1;

/* USB Type-C commands क्रम AP-controlled device policy. */
#घोषणा EC_CMD_TYPEC_CONTROL 0x0132

क्रमागत typec_control_command अणु
	TYPEC_CONTROL_COMMAND_EXIT_MODES,
	TYPEC_CONTROL_COMMAND_CLEAR_EVENTS,
	TYPEC_CONTROL_COMMAND_ENTER_MODE,
पूर्ण;

काष्ठा ec_params_typec_control अणु
	uपूर्णांक8_t port;
	uपूर्णांक8_t command;	/* क्रमागत typec_control_command */
	uपूर्णांक16_t reserved;

	/*
	 * This section will be पूर्णांकerpreted based on |command|. Define a
	 * placeholder काष्ठाure to aव्योम having to increase the size and bump
	 * the command version when adding new sub-commands.
	 */
	जोड़ अणु
		uपूर्णांक32_t clear_events_mask;
		uपूर्णांक8_t mode_to_enter;      /* क्रमागत typec_mode */
		uपूर्णांक8_t placeholder[128];
	पूर्ण;
पूर्ण __ec_align1;

/*
 * Gather all status inक्रमmation क्रम a port.
 *
 * Note: this covers many of the वापस fields from the deprecated
 * EC_CMD_USB_PD_CONTROL command, except those that are redundant with the
 * discovery data.  The "enum pd_cc_states" is defined with the deprecated
 * EC_CMD_USB_PD_CONTROL command.
 *
 * This also combines in the EC_CMD_USB_PD_MUX_INFO flags.
 */
#घोषणा EC_CMD_TYPEC_STATUS 0x0133

/*
 * Power role.
 *
 * Note this is also used क्रम PD header creation, and values align to those in
 * the Power Delivery Specअगरication Revision 3.0 (See
 * 6.2.1.1.4 Port Power Role).
 */
क्रमागत pd_घातer_role अणु
	PD_ROLE_SINK = 0,
	PD_ROLE_SOURCE = 1
पूर्ण;

/*
 * Data role.
 *
 * Note this is also used क्रम PD header creation, and the first two values
 * align to those in the Power Delivery Specअगरication Revision 3.0 (See
 * 6.2.1.1.6 Port Data Role).
 */
क्रमागत pd_data_role अणु
	PD_ROLE_UFP = 0,
	PD_ROLE_DFP = 1,
	PD_ROLE_DISCONNECTED = 2,
पूर्ण;

क्रमागत pd_vconn_role अणु
	PD_ROLE_VCONN_OFF = 0,
	PD_ROLE_VCONN_SRC = 1,
पूर्ण;

/*
 * Note: BIT(0) may be used to determine whether the polarity is CC1 or CC2,
 * regardless of whether a debug accessory is connected.
 */
क्रमागत tcpc_cc_polarity अणु
	/*
	 * _CCx: is used to indicate the polarity जबतक not connected to
	 * a Debug Accessory.  Only one CC line will निश्चित a resistor and
	 * the other will be खोलो.
	 */
	POLARITY_CC1 = 0,
	POLARITY_CC2 = 1,

	/*
	 * _CCx_DTS is used to indicate the polarity जबतक connected to a
	 * SRC Debug Accessory.  Assert resistors on both lines.
	 */
	POLARITY_CC1_DTS = 2,
	POLARITY_CC2_DTS = 3,

	/*
	 * The current TCPC code relies on these specअगरic POLARITY values.
	 * Adding in a check to verअगरy अगर the list grows क्रम any reason
	 * that this will give a hपूर्णांक that other places need to be
	 * adjusted.
	 */
	POLARITY_COUNT
पूर्ण;

#घोषणा PD_STATUS_EVENT_SOP_DISC_DONE		BIT(0)
#घोषणा PD_STATUS_EVENT_SOP_PRIME_DISC_DONE	BIT(1)
#घोषणा PD_STATUS_EVENT_HARD_RESET		BIT(2)

काष्ठा ec_params_typec_status अणु
	uपूर्णांक8_t port;
पूर्ण __ec_align1;

काष्ठा ec_response_typec_status अणु
	uपूर्णांक8_t pd_enabled;		/* PD communication enabled - bool */
	uपूर्णांक8_t dev_connected;		/* Device connected - bool */
	uपूर्णांक8_t sop_connected;		/* Device is SOP PD capable - bool */
	uपूर्णांक8_t source_cap_count;	/* Number of Source Cap PDOs */

	uपूर्णांक8_t घातer_role;		/* क्रमागत pd_घातer_role */
	uपूर्णांक8_t data_role;		/* क्रमागत pd_data_role */
	uपूर्णांक8_t vconn_role;		/* क्रमागत pd_vconn_role */
	uपूर्णांक8_t sink_cap_count;		/* Number of Sink Cap PDOs */

	uपूर्णांक8_t polarity;		/* क्रमागत tcpc_cc_polarity */
	uपूर्णांक8_t cc_state;		/* क्रमागत pd_cc_states */
	uपूर्णांक8_t dp_pin;			/* DP pin mode (MODE_DP_IN_[A-E]) */
	uपूर्णांक8_t mux_state;		/* USB_PD_MUX* - encoded mux state */

	अक्षर tc_state[32];		/* TC state name */

	uपूर्णांक32_t events;		/* PD_STATUS_EVENT biपंचांगask */

	/*
	 * BCD PD revisions क्रम partners
	 *
	 * The क्रमmat has the PD major reversion in the upper nibble, and PD
	 * minor version in the next nibble.  Following two nibbles are
	 * currently 0.
	 * ex. PD 3.2 would map to 0x3200
	 *
	 * PD major/minor will be 0 अगर no PD device is connected.
	 */
	uपूर्णांक16_t sop_revision;
	uपूर्णांक16_t sop_prime_revision;

	uपूर्णांक32_t source_cap_pकरोs[7];	/* Max 7 PDOs can be present */

	uपूर्णांक32_t sink_cap_pकरोs[7];	/* Max 7 PDOs can be present */
पूर्ण __ec_align1;

/*****************************************************************************/
/* The command range 0x200-0x2FF is reserved क्रम Rotor. */

/*****************************************************************************/
/*
 * Reserve a range of host commands क्रम the CR51 firmware.
 */
#घोषणा EC_CMD_CR51_BASE 0x0300
#घोषणा EC_CMD_CR51_LAST 0x03FF

/*****************************************************************************/
/* Fingerprपूर्णांक MCU commands: range 0x0400-0x040x */

/* Fingerprपूर्णांक SPI sensor passthru command: prototyping ONLY */
#घोषणा EC_CMD_FP_PASSTHRU 0x0400

#घोषणा EC_FP_FLAG_NOT_COMPLETE 0x1

काष्ठा ec_params_fp_passthru अणु
	uपूर्णांक16_t len;		/* Number of bytes to ग_लिखो then पढ़ो */
	uपूर्णांक16_t flags;		/* EC_FP_FLAG_xxx */
	uपूर्णांक8_t data[];		/* Data to send */
पूर्ण __ec_align2;

/* Configure the Fingerprपूर्णांक MCU behavior */
#घोषणा EC_CMD_FP_MODE 0x0402

/* Put the sensor in its lowest घातer mode */
#घोषणा FP_MODE_DEEPSLEEP      BIT(0)
/* Wait to see a finger on the sensor */
#घोषणा FP_MODE_FINGER_DOWN    BIT(1)
/* Poll until the finger has left the sensor */
#घोषणा FP_MODE_FINGER_UP      BIT(2)
/* Capture the current finger image */
#घोषणा FP_MODE_CAPTURE        BIT(3)
/* Finger enrollment session on-going */
#घोषणा FP_MODE_ENROLL_SESSION BIT(4)
/* Enroll the current finger image */
#घोषणा FP_MODE_ENROLL_IMAGE   BIT(5)
/* Try to match the current finger image */
#घोषणा FP_MODE_MATCH          BIT(6)
/* Reset and re-initialize the sensor. */
#घोषणा FP_MODE_RESET_SENSOR   BIT(7)
/* special value: करोn't change anything just पढ़ो back current mode */
#घोषणा FP_MODE_DONT_CHANGE    BIT(31)

#घोषणा FP_VALID_MODES (FP_MODE_DEEPSLEEP      | \
			FP_MODE_FINGER_DOWN    | \
			FP_MODE_FINGER_UP      | \
			FP_MODE_CAPTURE        | \
			FP_MODE_ENROLL_SESSION | \
			FP_MODE_ENROLL_IMAGE   | \
			FP_MODE_MATCH          | \
			FP_MODE_RESET_SENSOR   | \
			FP_MODE_DONT_CHANGE)

/* Capture types defined in bits [30..28] */
#घोषणा FP_MODE_CAPTURE_TYPE_SHIFT 28
#घोषणा FP_MODE_CAPTURE_TYPE_MASK  (0x7 << FP_MODE_CAPTURE_TYPE_SHIFT)
/*
 * This क्रमागत must reमुख्य ordered, अगर you add new values you must ensure that
 * FP_CAPTURE_TYPE_MAX is still the last one.
 */
क्रमागत fp_capture_type अणु
	/* Full blown venकरोr-defined capture (produces 'frame_size' bytes) */
	FP_CAPTURE_VENDOR_FORMAT = 0,
	/* Simple raw image capture (produces width x height x bpp bits) */
	FP_CAPTURE_SIMPLE_IMAGE = 1,
	/* Self test pattern (e.g. checkerboard) */
	FP_CAPTURE_PATTERN0 = 2,
	/* Self test pattern (e.g. inverted checkerboard) */
	FP_CAPTURE_PATTERN1 = 3,
	/* Capture क्रम Quality test with fixed contrast */
	FP_CAPTURE_QUALITY_TEST = 4,
	/* Capture क्रम pixel reset value test */
	FP_CAPTURE_RESET_TEST = 5,
	FP_CAPTURE_TYPE_MAX,
पूर्ण;
/* Extracts the capture type from the sensor 'mode' word */
#घोषणा FP_CAPTURE_TYPE(mode) (((mode) & FP_MODE_CAPTURE_TYPE_MASK) \
				       >> FP_MODE_CAPTURE_TYPE_SHIFT)

काष्ठा ec_params_fp_mode अणु
	uपूर्णांक32_t mode; /* as defined by FP_MODE_ स्थिरants */
पूर्ण __ec_align4;

काष्ठा ec_response_fp_mode अणु
	uपूर्णांक32_t mode; /* as defined by FP_MODE_ स्थिरants */
पूर्ण __ec_align4;

/* Retrieve Fingerprपूर्णांक sensor inक्रमmation */
#घोषणा EC_CMD_FP_INFO 0x0403

/* Number of dead pixels detected on the last मुख्यtenance */
#घोषणा FP_ERROR_DEAD_PIXELS(errors) ((errors) & 0x3FF)
/* Unknown number of dead pixels detected on the last मुख्यtenance */
#घोषणा FP_ERROR_DEAD_PIXELS_UNKNOWN (0x3FF)
/* No पूर्णांकerrupt from the sensor */
#घोषणा FP_ERROR_NO_IRQ    BIT(12)
/* SPI communication error */
#घोषणा FP_ERROR_SPI_COMM  BIT(13)
/* Invalid sensor Hardware ID */
#घोषणा FP_ERROR_BAD_HWID  BIT(14)
/* Sensor initialization failed */
#घोषणा FP_ERROR_INIT_FAIL BIT(15)

काष्ठा ec_response_fp_info_v0 अणु
	/* Sensor identअगरication */
	uपूर्णांक32_t venकरोr_id;
	uपूर्णांक32_t product_id;
	uपूर्णांक32_t model_id;
	uपूर्णांक32_t version;
	/* Image frame अक्षरacteristics */
	uपूर्णांक32_t frame_size;
	uपूर्णांक32_t pixel_क्रमmat; /* using V4L2_PIX_FMT_ */
	uपूर्णांक16_t width;
	uपूर्णांक16_t height;
	uपूर्णांक16_t bpp;
	uपूर्णांक16_t errors; /* see FP_ERROR_ flags above */
पूर्ण __ec_align4;

काष्ठा ec_response_fp_info अणु
	/* Sensor identअगरication */
	uपूर्णांक32_t venकरोr_id;
	uपूर्णांक32_t product_id;
	uपूर्णांक32_t model_id;
	uपूर्णांक32_t version;
	/* Image frame अक्षरacteristics */
	uपूर्णांक32_t frame_size;
	uपूर्णांक32_t pixel_क्रमmat; /* using V4L2_PIX_FMT_ */
	uपूर्णांक16_t width;
	uपूर्णांक16_t height;
	uपूर्णांक16_t bpp;
	uपूर्णांक16_t errors; /* see FP_ERROR_ flags above */
	/* Template/finger current inक्रमmation */
	uपूर्णांक32_t ढाँचा_size;  /* max ढाँचा size in bytes */
	uपूर्णांक16_t ढाँचा_max;   /* maximum number of fingers/ढाँचाs */
	uपूर्णांक16_t ढाँचा_valid; /* number of valid fingers/ढाँचाs */
	uपूर्णांक32_t ढाँचा_dirty; /* biपंचांगap of ढाँचाs with MCU side changes */
	uपूर्णांक32_t ढाँचा_version; /* version of the ढाँचा क्रमmat */
पूर्ण __ec_align4;

/* Get the last captured finger frame or a ढाँचा content */
#घोषणा EC_CMD_FP_FRAME 0x0404

/* स्थिरants defining the 'offset' field which also contains the frame index */
#घोषणा FP_FRAME_INDEX_SHIFT       28
/* Frame buffer where the captured image is stored */
#घोषणा FP_FRAME_INDEX_RAW_IMAGE    0
/* First frame buffer holding a ढाँचा */
#घोषणा FP_FRAME_INDEX_TEMPLATE     1
#घोषणा FP_FRAME_GET_BUFFER_INDEX(offset) ((offset) >> FP_FRAME_INDEX_SHIFT)
#घोषणा FP_FRAME_OFFSET_MASK       0x0FFFFFFF

/* Version of the क्रमmat of the encrypted ढाँचाs. */
#घोषणा FP_TEMPLATE_FORMAT_VERSION 3

/* Constants क्रम encryption parameters */
#घोषणा FP_CONTEXT_NONCE_BYTES 12
#घोषणा FP_CONTEXT_USERID_WORDS (32 / माप(uपूर्णांक32_t))
#घोषणा FP_CONTEXT_TAG_BYTES 16
#घोषणा FP_CONTEXT_SALT_BYTES 16
#घोषणा FP_CONTEXT_TPM_BYTES 32

काष्ठा ec_fp_ढाँचा_encryption_metadata अणु
	/*
	 * Version of the काष्ठाure क्रमmat (N=3).
	 */
	uपूर्णांक16_t काष्ठा_version;
	/* Reserved bytes, set to 0. */
	uपूर्णांक16_t reserved;
	/*
	 * The salt is *only* ever used क्रम key derivation. The nonce is unique,
	 * a dअगरferent one is used क्रम every message.
	 */
	uपूर्णांक8_t nonce[FP_CONTEXT_NONCE_BYTES];
	uपूर्णांक8_t salt[FP_CONTEXT_SALT_BYTES];
	uपूर्णांक8_t tag[FP_CONTEXT_TAG_BYTES];
पूर्ण;

काष्ठा ec_params_fp_frame अणु
	/*
	 * The offset contains the ढाँचा index or FP_FRAME_INDEX_RAW_IMAGE
	 * in the high nibble, and the real offset within the frame in
	 * FP_FRAME_OFFSET_MASK.
	 */
	uपूर्णांक32_t offset;
	uपूर्णांक32_t size;
पूर्ण __ec_align4;

/* Load a ढाँचा पूर्णांकo the MCU */
#घोषणा EC_CMD_FP_TEMPLATE 0x0405

/* Flag in the 'size' field indicating that the full ढाँचा has been sent */
#घोषणा FP_TEMPLATE_COMMIT 0x80000000

काष्ठा ec_params_fp_ढाँचा अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t size;
	uपूर्णांक8_t data[];
पूर्ण __ec_align4;

/* Clear the current fingerprपूर्णांक user context and set a new one */
#घोषणा EC_CMD_FP_CONTEXT 0x0406

काष्ठा ec_params_fp_context अणु
	uपूर्णांक32_t userid[FP_CONTEXT_USERID_WORDS];
पूर्ण __ec_align4;

#घोषणा EC_CMD_FP_STATS 0x0407

#घोषणा FPSTATS_CAPTURE_INV  BIT(0)
#घोषणा FPSTATS_MATCHING_INV BIT(1)

काष्ठा ec_response_fp_stats अणु
	uपूर्णांक32_t capture_समय_us;
	uपूर्णांक32_t matching_समय_us;
	uपूर्णांक32_t overall_समय_us;
	काष्ठा अणु
		uपूर्णांक32_t lo;
		uपूर्णांक32_t hi;
	पूर्ण overall_t0;
	uपूर्णांक8_t बारtamps_invalid;
	पूर्णांक8_t ढाँचा_matched;
पूर्ण __ec_align2;

#घोषणा EC_CMD_FP_SEED 0x0408
काष्ठा ec_params_fp_seed अणु
	/*
	 * Version of the काष्ठाure क्रमmat (N=3).
	 */
	uपूर्णांक16_t काष्ठा_version;
	/* Reserved bytes, set to 0. */
	uपूर्णांक16_t reserved;
	/* Seed from the TPM. */
	uपूर्णांक8_t seed[FP_CONTEXT_TPM_BYTES];
पूर्ण __ec_align4;

#घोषणा EC_CMD_FP_ENC_STATUS 0x0409

/* FP TPM seed has been set or not */
#घोषणा FP_ENC_STATUS_SEED_SET BIT(0)

काष्ठा ec_response_fp_encryption_status अणु
	/* Used bits in encryption engine status */
	uपूर्णांक32_t valid_flags;
	/* Encryption engine status */
	uपूर्णांक32_t status;
पूर्ण __ec_align4;

/*****************************************************************************/
/* Touchpad MCU commands: range 0x0500-0x05FF */

/* Perक्रमm touchpad self test */
#घोषणा EC_CMD_TP_SELF_TEST 0x0500

/* Get number of frame types, and the size of each type */
#घोषणा EC_CMD_TP_FRAME_INFO 0x0501

काष्ठा ec_response_tp_frame_info अणु
	uपूर्णांक32_t n_frames;
	uपूर्णांक32_t frame_sizes[];
पूर्ण __ec_align4;

/* Create a snapshot of current frame पढ़ोings */
#घोषणा EC_CMD_TP_FRAME_SNAPSHOT 0x0502

/* Read the frame */
#घोषणा EC_CMD_TP_FRAME_GET 0x0503

काष्ठा ec_params_tp_frame_get अणु
	uपूर्णांक32_t frame_index;
	uपूर्णांक32_t offset;
	uपूर्णांक32_t size;
पूर्ण __ec_align4;

/*****************************************************************************/
/* EC-EC communication commands: range 0x0600-0x06FF */

#घोषणा EC_COMM_TEXT_MAX 8

/*
 * Get battery अटल inक्रमmation, i.e. inक्रमmation that never changes, or
 * very infrequently.
 */
#घोषणा EC_CMD_BATTERY_GET_STATIC 0x0600

/**
 * काष्ठा ec_params_battery_अटल_info - Battery अटल info parameters
 * @index: Battery index.
 */
काष्ठा ec_params_battery_अटल_info अणु
	uपूर्णांक8_t index;
पूर्ण __ec_align_size1;

/**
 * काष्ठा ec_response_battery_अटल_info - Battery अटल info response
 * @design_capacity: Battery Design Capacity (mAh)
 * @design_voltage: Battery Design Voltage (mV)
 * @manufacturer: Battery Manufacturer String
 * @model: Battery Model Number String
 * @serial: Battery Serial Number String
 * @type: Battery Type String
 * @cycle_count: Battery Cycle Count
 */
काष्ठा ec_response_battery_अटल_info अणु
	uपूर्णांक16_t design_capacity;
	uपूर्णांक16_t design_voltage;
	अक्षर manufacturer[EC_COMM_TEXT_MAX];
	अक्षर model[EC_COMM_TEXT_MAX];
	अक्षर serial[EC_COMM_TEXT_MAX];
	अक्षर type[EC_COMM_TEXT_MAX];
	/* TODO(crbug.com/795991): Consider moving to dynamic काष्ठाure. */
	uपूर्णांक32_t cycle_count;
पूर्ण __ec_align4;

/*
 * Get battery dynamic inक्रमmation, i.e. inक्रमmation that is likely to change
 * every समय it is पढ़ो.
 */
#घोषणा EC_CMD_BATTERY_GET_DYNAMIC 0x0601

/**
 * काष्ठा ec_params_battery_dynamic_info - Battery dynamic info parameters
 * @index: Battery index.
 */
काष्ठा ec_params_battery_dynamic_info अणु
	uपूर्णांक8_t index;
पूर्ण __ec_align_size1;

/**
 * काष्ठा ec_response_battery_dynamic_info - Battery dynamic info response
 * @actual_voltage: Battery voltage (mV)
 * @actual_current: Battery current (mA); negative=disअक्षरging
 * @reमुख्यing_capacity: Reमुख्यing capacity (mAh)
 * @full_capacity: Capacity (mAh, might change occasionally)
 * @flags: Flags, see EC_BATT_FLAG_*
 * @desired_voltage: Charging voltage desired by battery (mV)
 * @desired_current: Charging current desired by battery (mA)
 */
काष्ठा ec_response_battery_dynamic_info अणु
	पूर्णांक16_t actual_voltage;
	पूर्णांक16_t actual_current;
	पूर्णांक16_t reमुख्यing_capacity;
	पूर्णांक16_t full_capacity;
	पूर्णांक16_t flags;
	पूर्णांक16_t desired_voltage;
	पूर्णांक16_t desired_current;
पूर्ण __ec_align2;

/*
 * Control अक्षरger chip. Used to control अक्षरger chip on the slave.
 */
#घोषणा EC_CMD_CHARGER_CONTROL 0x0602

/**
 * काष्ठा ec_params_अक्षरger_control - Charger control parameters
 * @max_current: Charger current (mA). Positive to allow base to draw up to
 *     max_current and (possibly) अक्षरge battery, negative to request current
 *     from base (OTG).
 * @otg_voltage: Voltage (mV) to use in OTG mode, ignored अगर max_current is
 *     >= 0.
 * @allow_अक्षरging: Allow base battery अक्षरging (only makes sense अगर
 *     max_current > 0).
 */
काष्ठा ec_params_अक्षरger_control अणु
	पूर्णांक16_t max_current;
	uपूर्णांक16_t otg_voltage;
	uपूर्णांक8_t allow_अक्षरging;
पूर्ण __ec_align_size1;

/* Get ACK from the USB-C SS muxes */
#घोषणा EC_CMD_USB_PD_MUX_ACK 0x0603

काष्ठा ec_params_usb_pd_mux_ack अणु
	uपूर्णांक8_t port; /* USB-C port number */
पूर्ण __ec_align1;

/*****************************************************************************/
/*
 * Reserve a range of host commands क्रम board-specअगरic, experimental, or
 * special purpose features. These can be (re)used without updating this file.
 *
 * CAUTION: Don't go nuts with this. Shipping products should करोcument ALL
 * their EC commands क्रम easier development, testing, debugging, and support.
 *
 * All commands MUST be #घोषणाd to be 4-digit UPPER CASE hex values
 * (e.g., 0x00AB, not 0xab) क्रम CONFIG_HOSTCMD_SECTION_SORTED to work.
 *
 * In your experimental code, you may want to करो something like this:
 *
 *   #घोषणा EC_CMD_MAGIC_FOO 0x0000
 *   #घोषणा EC_CMD_MAGIC_BAR 0x0001
 *   #घोषणा EC_CMD_MAGIC_HEY 0x0002
 *
 *   DECLARE_PRIVATE_HOST_COMMAND(EC_CMD_MAGIC_FOO, magic_foo_handler,
 *      EC_VER_MASK(0);
 *
 *   DECLARE_PRIVATE_HOST_COMMAND(EC_CMD_MAGIC_BAR, magic_bar_handler,
 *      EC_VER_MASK(0);
 *
 *   DECLARE_PRIVATE_HOST_COMMAND(EC_CMD_MAGIC_HEY, magic_hey_handler,
 *      EC_VER_MASK(0);
 */
#घोषणा EC_CMD_BOARD_SPECIFIC_BASE 0x3E00
#घोषणा EC_CMD_BOARD_SPECIFIC_LAST 0x3FFF

/*
 * Given the निजी host command offset, calculate the true निजी host
 * command value.
 */
#घोषणा EC_PRIVATE_HOST_COMMAND_VALUE(command) \
	(EC_CMD_BOARD_SPECIFIC_BASE + (command))

/*****************************************************************************/
/*
 * Passthru commands
 *
 * Some platक्रमms have sub-processors chained to each other.  For example.
 *
 *     AP <--> EC <--> PD MCU
 *
 * The top 2 bits of the command number are used to indicate which device the
 * command is पूर्णांकended क्रम.  Device 0 is always the device receiving the
 * command; other device mapping is board-specअगरic.
 *
 * When a device receives a command to be passed to a sub-processor, it passes
 * it on with the device number set back to 0.  This allows the sub-processor
 * to reमुख्य blissfully unaware of whether the command originated on the next
 * device up the chain, or was passed through from the AP.
 *
 * In the above example, अगर the AP wants to send command 0x0002 to the PD MCU,
 *     AP sends command 0x4002 to the EC
 *     EC sends command 0x0002 to the PD MCU
 *     EC क्रमwards PD MCU response back to the AP
 */

/* Offset and max command number क्रम sub-device n */
#घोषणा EC_CMD_PASSTHRU_OFFSET(n) (0x4000 * (n))
#घोषणा EC_CMD_PASSTHRU_MAX(n) (EC_CMD_PASSTHRU_OFFSET(n) + 0x3fff)

/*****************************************************************************/
/*
 * Deprecated स्थिरants. These स्थिरants have been नामd क्रम clarity. The
 * meaning and size has not changed. Programs that use the old names should
 * चयन to the new names soon, as the old names may not be carried क्रमward
 * क्रमever.
 */
#घोषणा EC_HOST_PARAM_SIZE      EC_PROTO2_MAX_PARAM_SIZE
#घोषणा EC_LPC_ADDR_OLD_PARAM   EC_HOST_CMD_REGION1
#घोषणा EC_OLD_PARAM_SIZE       EC_HOST_CMD_REGION_SIZE



#पूर्ण_अगर  /* __CROS_EC_COMMANDS_H */
