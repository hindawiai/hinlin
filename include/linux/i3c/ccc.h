<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Cadence Design Systems Inc.
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 */

#अगर_अघोषित I3C_CCC_H
#घोषणा I3C_CCC_H

#समावेश <linux/bitops.h>
#समावेश <linux/i3c/device.h>

/* I3C CCC (Common Command Codes) related definitions */
#घोषणा I3C_CCC_सूचीECT			BIT(7)

#घोषणा I3C_CCC_ID(id, broadcast)	\
	((id) | ((broadcast) ? 0 : I3C_CCC_सूचीECT))

/* Commands valid in both broadcast and unicast modes */
#घोषणा I3C_CCC_ENEC(broadcast)		I3C_CCC_ID(0x0, broadcast)
#घोषणा I3C_CCC_DISEC(broadcast)	I3C_CCC_ID(0x1, broadcast)
#घोषणा I3C_CCC_ENTAS(as, broadcast)	I3C_CCC_ID(0x2 + (as), broadcast)
#घोषणा I3C_CCC_RSTDAA(broadcast)	I3C_CCC_ID(0x6, broadcast)
#घोषणा I3C_CCC_SETMWL(broadcast)	I3C_CCC_ID(0x9, broadcast)
#घोषणा I3C_CCC_SETMRL(broadcast)	I3C_CCC_ID(0xa, broadcast)
#घोषणा I3C_CCC_SETXTIME(broadcast)	((broadcast) ? 0x28 : 0x98)
#घोषणा I3C_CCC_VENDOR(id, broadcast)	((id) + ((broadcast) ? 0x61 : 0xe0))

/* Broadcast-only commands */
#घोषणा I3C_CCC_ENTDAA			I3C_CCC_ID(0x7, true)
#घोषणा I3C_CCC_DEFSLVS			I3C_CCC_ID(0x8, true)
#घोषणा I3C_CCC_ENTTM			I3C_CCC_ID(0xb, true)
#घोषणा I3C_CCC_ENTHDR(x)		I3C_CCC_ID(0x20 + (x), true)

/* Unicast-only commands */
#घोषणा I3C_CCC_SETDASA			I3C_CCC_ID(0x7, false)
#घोषणा I3C_CCC_SETNEWDA		I3C_CCC_ID(0x8, false)
#घोषणा I3C_CCC_GETMWL			I3C_CCC_ID(0xb, false)
#घोषणा I3C_CCC_GETMRL			I3C_CCC_ID(0xc, false)
#घोषणा I3C_CCC_GETPID			I3C_CCC_ID(0xd, false)
#घोषणा I3C_CCC_GETBCR			I3C_CCC_ID(0xe, false)
#घोषणा I3C_CCC_GETDCR			I3C_CCC_ID(0xf, false)
#घोषणा I3C_CCC_GETSTATUS		I3C_CCC_ID(0x10, false)
#घोषणा I3C_CCC_GETACCMST		I3C_CCC_ID(0x11, false)
#घोषणा I3C_CCC_SETBRGTGT		I3C_CCC_ID(0x13, false)
#घोषणा I3C_CCC_GETMXDS			I3C_CCC_ID(0x14, false)
#घोषणा I3C_CCC_GETHDRCAP		I3C_CCC_ID(0x15, false)
#घोषणा I3C_CCC_GETXTIME		I3C_CCC_ID(0x19, false)

#घोषणा I3C_CCC_EVENT_SIR		BIT(0)
#घोषणा I3C_CCC_EVENT_MR		BIT(1)
#घोषणा I3C_CCC_EVENT_HJ		BIT(3)

/**
 * काष्ठा i3c_ccc_events - payload passed to ENEC/DISEC CCC
 *
 * @events: biपंचांगask of I3C_CCC_EVENT_xxx events.
 *
 * Depending on the CCC command, the specअगरic events coming from all devices
 * (broadcast version) or a specअगरic device (unicast version) will be
 * enabled (ENEC) or disabled (DISEC).
 */
काष्ठा i3c_ccc_events अणु
	u8 events;
पूर्ण;

/**
 * काष्ठा i3c_ccc_mwl - payload passed to SETMWL/GETMWL CCC
 *
 * @len: maximum ग_लिखो length in bytes
 *
 * The maximum ग_लिखो length is only applicable to SDR निजी messages or
 * extended Write CCCs (like SETXTIME).
 */
काष्ठा i3c_ccc_mwl अणु
	__be16 len;
पूर्ण;

/**
 * काष्ठा i3c_ccc_mrl - payload passed to SETMRL/GETMRL CCC
 *
 * @len: maximum पढ़ो length in bytes
 * @ibi_len: maximum IBI payload length
 *
 * The maximum पढ़ो length is only applicable to SDR निजी messages or
 * extended Read CCCs (like GETXTIME).
 * The IBI length is only valid अगर the I3C slave is IBI capable
 * (%I3C_BCR_IBI_REQ_CAP is set).
 */
काष्ठा i3c_ccc_mrl अणु
	__be16 पढ़ो_len;
	u8 ibi_len;
पूर्ण __packed;

/**
 * काष्ठा i3c_ccc_dev_desc - I3C/I2C device descriptor used क्रम DEFSLVS
 *
 * @dyn_addr: dynamic address asचिन्हित to the I3C slave or 0 अगर the entry is
 *	      describing an I2C slave.
 * @dcr: DCR value (not applicable to entries describing I2C devices)
 * @lvr: LVR value (not applicable to entries describing I3C devices)
 * @bcr: BCR value or 0 अगर this entry is describing an I2C slave
 * @अटल_addr: अटल address or 0 अगर the device करोes not have a अटल
 *		 address
 *
 * The DEFSLVS command should be passed an array of i3c_ccc_dev_desc
 * descriptors (one entry per I3C/I2C dev controlled by the master).
 */
काष्ठा i3c_ccc_dev_desc अणु
	u8 dyn_addr;
	जोड़ अणु
		u8 dcr;
		u8 lvr;
	पूर्ण;
	u8 bcr;
	u8 अटल_addr;
पूर्ण;

/**
 * काष्ठा i3c_ccc_defslvs - payload passed to DEFSLVS CCC
 *
 * @count: number of dev descriptors
 * @master: descriptor describing the current master
 * @slaves: array of descriptors describing slaves controlled by the
 *	    current master
 *
 * Inक्रमmation passed to the broadcast DEFSLVS to propagate device
 * inक्रमmation to all masters currently acting as slaves on the bus.
 * This is only meaningful अगर you have more than one master.
 */
काष्ठा i3c_ccc_defslvs अणु
	u8 count;
	काष्ठा i3c_ccc_dev_desc master;
	काष्ठा i3c_ccc_dev_desc slaves[0];
पूर्ण __packed;

/**
 * क्रमागत i3c_ccc_test_mode - क्रमागत listing all available test modes
 *
 * @I3C_CCC_EXIT_TEST_MODE: निकास test mode
 * @I3C_CCC_VENDOR_TEST_MODE: enter venकरोr test mode
 */
क्रमागत i3c_ccc_test_mode अणु
	I3C_CCC_EXIT_TEST_MODE,
	I3C_CCC_VENDOR_TEST_MODE,
पूर्ण;

/**
 * काष्ठा i3c_ccc_entपंचांग - payload passed to ENTTM CCC
 *
 * @mode: one of the &क्रमागत i3c_ccc_test_mode modes
 *
 * Inक्रमmation passed to the ENTTM CCC to inकाष्ठा an I3C device to enter a
 * specअगरic test mode.
 */
काष्ठा i3c_ccc_entपंचांग अणु
	u8 mode;
पूर्ण;

/**
 * काष्ठा i3c_ccc_setda - payload passed to SETNEWDA and SETDASA CCCs
 *
 * @addr: dynamic address to assign to an I3C device
 *
 * Inक्रमmation passed to the SETNEWDA and SETDASA CCCs to assign/change the
 * dynamic address of an I3C device.
 */
काष्ठा i3c_ccc_setda अणु
	u8 addr;
पूर्ण;

/**
 * काष्ठा i3c_ccc_getpid - payload passed to GETPID CCC
 *
 * @pid: 48 bits PID in big endian
 */
काष्ठा i3c_ccc_getpid अणु
	u8 pid[6];
पूर्ण;

/**
 * काष्ठा i3c_ccc_getbcr - payload passed to GETBCR CCC
 *
 * @bcr: BCR (Bus Characteristic Register) value
 */
काष्ठा i3c_ccc_getbcr अणु
	u8 bcr;
पूर्ण;

/**
 * काष्ठा i3c_ccc_getdcr - payload passed to GETDCR CCC
 *
 * @dcr: DCR (Device Characteristic Register) value
 */
काष्ठा i3c_ccc_getdcr अणु
	u8 dcr;
पूर्ण;

#घोषणा I3C_CCC_STATUS_PENDING_INT(status)	((status) & GENMASK(3, 0))
#घोषणा I3C_CCC_STATUS_PROTOCOL_ERROR		BIT(5)
#घोषणा I3C_CCC_STATUS_ACTIVITY_MODE(status)	\
	(((status) & GENMASK(7, 6)) >> 6)

/**
 * काष्ठा i3c_ccc_माला_लोtatus - payload passed to GETSTATUS CCC
 *
 * @status: status of the I3C slave (see I3C_CCC_STATUS_xxx macros क्रम more
 *	    inक्रमmation).
 */
काष्ठा i3c_ccc_माला_लोtatus अणु
	__be16 status;
पूर्ण;

/**
 * काष्ठा i3c_ccc_getaccmst - payload passed to GETACCMST CCC
 *
 * @newmaster: address of the master taking bus ownership
 */
काष्ठा i3c_ccc_getaccmst अणु
	u8 newmaster;
पूर्ण;

/**
 * काष्ठा i3c_ccc_bridged_slave_desc - bridged slave descriptor
 *
 * @addr: dynamic address of the bridged device
 * @id: ID of the slave device behind the bridge
 */
काष्ठा i3c_ccc_bridged_slave_desc अणु
	u8 addr;
	__be16 id;
पूर्ण __packed;

/**
 * काष्ठा i3c_ccc_setbrgtgt - payload passed to SETBRGTGT CCC
 *
 * @count: number of bridged slaves
 * @bslaves: bridged slave descriptors
 */
काष्ठा i3c_ccc_setbrgtgt अणु
	u8 count;
	काष्ठा i3c_ccc_bridged_slave_desc bslaves[0];
पूर्ण __packed;

/**
 * क्रमागत i3c_sdr_max_data_rate - max data rate values क्रम निजी SDR transfers
 */
क्रमागत i3c_sdr_max_data_rate अणु
	I3C_SDR0_FSCL_MAX,
	I3C_SDR1_FSCL_8MHZ,
	I3C_SDR2_FSCL_6MHZ,
	I3C_SDR3_FSCL_4MHZ,
	I3C_SDR4_FSCL_2MHZ,
पूर्ण;

/**
 * क्रमागत i3c_tsco - घड़ी to data turn-around
 */
क्रमागत i3c_tsco अणु
	I3C_TSCO_8NS,
	I3C_TSCO_9NS,
	I3C_TSCO_10NS,
	I3C_TSCO_11NS,
	I3C_TSCO_12NS,
पूर्ण;

#घोषणा I3C_CCC_MAX_SDR_FSCL_MASK	GENMASK(2, 0)
#घोषणा I3C_CCC_MAX_SDR_FSCL(x)		((x) & I3C_CCC_MAX_SDR_FSCL_MASK)

/**
 * काष्ठा i3c_ccc_geपंचांगxds - payload passed to GETMXDS CCC
 *
 * @maxwr: ग_लिखो limitations
 * @maxrd: पढ़ो limitations
 * @maxrdturn: maximum पढ़ो turn-around expressed micro-seconds and
 *	       little-endian क्रमmatted
 */
काष्ठा i3c_ccc_geपंचांगxds अणु
	u8 maxwr;
	u8 maxrd;
	u8 maxrdturn[3];
पूर्ण __packed;

#घोषणा I3C_CCC_HDR_MODE(mode)		BIT(mode)

/**
 * काष्ठा i3c_ccc_gethdrcap - payload passed to GETHDRCAP CCC
 *
 * @modes: biपंचांगap of supported HDR modes
 */
काष्ठा i3c_ccc_gethdrcap अणु
	u8 modes;
पूर्ण __packed;

/**
 * क्रमागत i3c_ccc_setxसमय_subcmd - SETXTIME sub-commands
 */
क्रमागत i3c_ccc_setxसमय_subcmd अणु
	I3C_CCC_SETXTIME_ST = 0x7f,
	I3C_CCC_SETXTIME_DT = 0xbf,
	I3C_CCC_SETXTIME_ENTER_ASYNC_MODE0 = 0xdf,
	I3C_CCC_SETXTIME_ENTER_ASYNC_MODE1 = 0xef,
	I3C_CCC_SETXTIME_ENTER_ASYNC_MODE2 = 0xf7,
	I3C_CCC_SETXTIME_ENTER_ASYNC_MODE3 = 0xfb,
	I3C_CCC_SETXTIME_ASYNC_TRIGGER = 0xfd,
	I3C_CCC_SETXTIME_TPH = 0x3f,
	I3C_CCC_SETXTIME_TU = 0x9f,
	I3C_CCC_SETXTIME_ODR = 0x8f,
पूर्ण;

/**
 * काष्ठा i3c_ccc_setxसमय - payload passed to SETXTIME CCC
 *
 * @subcmd: one of the sub-commands ddefined in &क्रमागत i3c_ccc_setxसमय_subcmd
 * @data: sub-command payload. Amount of data is determined by
 *	  &i3c_ccc_setxसमय->subcmd
 */
काष्ठा i3c_ccc_setxसमय अणु
	u8 subcmd;
	u8 data[0];
पूर्ण __packed;

#घोषणा I3C_CCC_GETXTIME_SYNC_MODE	BIT(0)
#घोषणा I3C_CCC_GETXTIME_ASYNC_MODE(x)	BIT((x) + 1)
#घोषणा I3C_CCC_GETXTIME_OVERFLOW	BIT(7)

/**
 * काष्ठा i3c_ccc_getxसमय - payload retrieved from GETXTIME CCC
 *
 * @supported_modes: biपंचांगap describing supported XTIME modes
 * @state: current status (enabled mode and overflow status)
 * @frequency: slave's पूर्णांकernal oscillator frequency in 500KHz steps
 * @inaccuracy: slave's पूर्णांकernal oscillator inaccuracy in 0.1% steps
 */
काष्ठा i3c_ccc_getxसमय अणु
	u8 supported_modes;
	u8 state;
	u8 frequency;
	u8 inaccuracy;
पूर्ण __packed;

/**
 * काष्ठा i3c_ccc_cmd_payload - CCC payload
 *
 * @len: payload length
 * @data: payload data. This buffer must be DMA-able
 */
काष्ठा i3c_ccc_cmd_payload अणु
	u16 len;
	व्योम *data;
पूर्ण;

/**
 * काष्ठा i3c_ccc_cmd_dest - CCC command destination
 *
 * @addr: can be an I3C device address or the broadcast address अगर this is a
 *	  broadcast CCC
 * @payload: payload to be sent to this device or broadcasted
 */
काष्ठा i3c_ccc_cmd_dest अणु
	u8 addr;
	काष्ठा i3c_ccc_cmd_payload payload;
पूर्ण;

/**
 * काष्ठा i3c_ccc_cmd - CCC command
 *
 * @rnw: true अगर the CCC should retrieve data from the device. Only valid क्रम
 *	 unicast commands
 * @id: CCC command id
 * @ndests: number of destinations. Should always be one क्रम broadcast commands
 * @dests: array of destinations and associated payload क्रम this CCC. Most of
 *	   the समय, only one destination is provided
 * @err: I3C error code
 */
काष्ठा i3c_ccc_cmd अणु
	u8 rnw;
	u8 id;
	अचिन्हित पूर्णांक ndests;
	काष्ठा i3c_ccc_cmd_dest *dests;
	क्रमागत i3c_error_code err;
पूर्ण;

#पूर्ण_अगर /* I3C_CCC_H */
