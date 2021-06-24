<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2017, Microchip Technology Inc.
 * Author: Tuकरोr Ambarus <tuकरोr.ambarus@microchip.com>
 */

#अगर_अघोषित __ATMEL_I2C_H__
#घोषणा __ATMEL_I2C_H__

#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/types.h>

#घोषणा ATMEL_ECC_PRIORITY		300

#घोषणा COMMAND				0x03 /* packet function */
#घोषणा SLEEP_TOKEN			0x01
#घोषणा WAKE_TOKEN_MAX_SIZE		8

/* Definitions of Data and Command sizes */
#घोषणा WORD_ADDR_SIZE			1
#घोषणा COUNT_SIZE			1
#घोषणा CRC_SIZE			2
#घोषणा CMD_OVERHEAD_SIZE		(COUNT_SIZE + CRC_SIZE)

/* size in bytes of the n prime */
#घोषणा ATMEL_ECC_NIST_P256_N_SIZE	32
#घोषणा ATMEL_ECC_PUBKEY_SIZE		(2 * ATMEL_ECC_NIST_P256_N_SIZE)

#घोषणा STATUS_RSP_SIZE			4
#घोषणा ECDH_RSP_SIZE			(32 + CMD_OVERHEAD_SIZE)
#घोषणा GENKEY_RSP_SIZE			(ATMEL_ECC_PUBKEY_SIZE + \
					 CMD_OVERHEAD_SIZE)
#घोषणा READ_RSP_SIZE			(4 + CMD_OVERHEAD_SIZE)
#घोषणा RANDOM_RSP_SIZE			(32 + CMD_OVERHEAD_SIZE)
#घोषणा MAX_RSP_SIZE			GENKEY_RSP_SIZE

/**
 * aपंचांगel_i2c_cmd - काष्ठाure used क्रम communicating with the device.
 * @word_addr: indicates the function of the packet sent to the device. This
 *             byte should have a value of COMMAND क्रम normal operation.
 * @count    : number of bytes to be transferred to (or from) the device.
 * @opcode   : the command code.
 * @param1   : the first parameter; always present.
 * @param2   : the second parameter; always present.
 * @data     : optional reमुख्यing input data. Includes a 2-byte CRC.
 * @rxsize   : size of the data received from i2c client.
 * @msecs    : command execution समय in milliseconds
 */
काष्ठा aपंचांगel_i2c_cmd अणु
	u8 word_addr;
	u8 count;
	u8 opcode;
	u8 param1;
	__le16 param2;
	u8 data[MAX_RSP_SIZE];
	u8 msecs;
	u16 rxsize;
पूर्ण __packed;

/* Status/Error codes */
#घोषणा STATUS_SIZE			0x04
#घोषणा STATUS_NOERR			0x00
#घोषणा STATUS_WAKE_SUCCESSFUL		0x11

/* Definitions क्रम eeprom organization */
#घोषणा CONFIG_ZONE			0

/* Definitions क्रम Indexes common to all commands */
#घोषणा RSP_DATA_IDX			1 /* buffer index of data in response */
#घोषणा DATA_SLOT_2			2 /* used क्रम ECDH निजी key */

/* Definitions क्रम the device lock state */
#घोषणा DEVICE_LOCK_ADDR		0x15
#घोषणा LOCK_VALUE_IDX			(RSP_DATA_IDX + 2)
#घोषणा LOCK_CONFIG_IDX			(RSP_DATA_IDX + 3)

/*
 * Wake High delay to data communication (microseconds). SDA should be stable
 * high क्रम this entire duration.
 */
#घोषणा TWHI_MIN			1500
#घोषणा TWHI_MAX			1550

/* Wake Low duration */
#घोषणा TWLO_USEC			60

/* Command execution समय (milliseconds) */
#घोषणा MAX_EXEC_TIME_ECDH		58
#घोषणा MAX_EXEC_TIME_GENKEY		115
#घोषणा MAX_EXEC_TIME_READ		1
#घोषणा MAX_EXEC_TIME_RANDOM		50

/* Command opcode */
#घोषणा OPCODE_ECDH			0x43
#घोषणा OPCODE_GENKEY			0x40
#घोषणा OPCODE_READ			0x02
#घोषणा OPCODE_RANDOM			0x1b

/* Definitions क्रम the READ Command */
#घोषणा READ_COUNT			7

/* Definitions क्रम the RANDOM Command */
#घोषणा RANDOM_COUNT			7

/* Definitions क्रम the GenKey Command */
#घोषणा GENKEY_COUNT			7
#घोषणा GENKEY_MODE_PRIVATE		0x04

/* Definitions क्रम the ECDH Command */
#घोषणा ECDH_COUNT			71
#घोषणा ECDH_PREFIX_MODE		0x00

/* Used क्रम binding tfm objects to i2c clients. */
काष्ठा aपंचांगel_ecc_driver_data अणु
	काष्ठा list_head i2c_client_list;
	spinlock_t i2c_list_lock;
पूर्ण ____cacheline_aligned;

/**
 * aपंचांगel_i2c_client_priv - i2c_client निजी data
 * @client              : poपूर्णांकer to i2c client device
 * @i2c_client_list_node: part of i2c_client_list
 * @lock                : lock क्रम sending i2c commands
 * @wake_token          : wake token array of zeros
 * @wake_token_sz       : size in bytes of the wake_token
 * @tfm_count           : number of active crypto transक्रमmations on i2c client
 *
 * Reads and ग_लिखोs from/to the i2c client are sequential. The first byte
 * transmitted to the device is treated as the byte size. Any attempt to send
 * more than this number of bytes will cause the device to not ACK those bytes.
 * After the host ग_लिखोs a single command byte to the input buffer, पढ़ोs are
 * prohibited until after the device completes command execution. Use a mutex
 * when sending i2c commands.
 */
काष्ठा aपंचांगel_i2c_client_priv अणु
	काष्ठा i2c_client *client;
	काष्ठा list_head i2c_client_list_node;
	काष्ठा mutex lock;
	u8 wake_token[WAKE_TOKEN_MAX_SIZE];
	माप_प्रकार wake_token_sz;
	atomic_t tfm_count ____cacheline_aligned;
	काष्ठा hwrng hwrng;
पूर्ण;

/**
 * aपंचांगel_i2c_work_data - data काष्ठाure representing the work
 * @ctx : transक्रमmation context.
 * @cbk : poपूर्णांकer to a callback function to be invoked upon completion of this
 *        request. This has the क्रमm:
 *        callback(काष्ठा aपंचांगel_i2c_work_data *work_data, व्योम *areq, u8 status)
 *        where:
 *        @work_data: data काष्ठाure representing the work
 *        @areq     : optional poपूर्णांकer to an argument passed with the original
 *                    request.
 *        @status   : status वापसed from the i2c client device or i2c error.
 * @areq: optional poपूर्णांकer to a user argument क्रम use at callback समय.
 * @work: describes the task to be executed.
 * @cmd : काष्ठाure used क्रम communicating with the device.
 */
काष्ठा aपंचांगel_i2c_work_data अणु
	व्योम *ctx;
	काष्ठा i2c_client *client;
	व्योम (*cbk)(काष्ठा aपंचांगel_i2c_work_data *work_data, व्योम *areq,
		    पूर्णांक status);
	व्योम *areq;
	काष्ठा work_काष्ठा work;
	काष्ठा aपंचांगel_i2c_cmd cmd;
पूर्ण;

पूर्णांक aपंचांगel_i2c_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id);

व्योम aपंचांगel_i2c_enqueue(काष्ठा aपंचांगel_i2c_work_data *work_data,
		       व्योम (*cbk)(काष्ठा aपंचांगel_i2c_work_data *work_data,
				   व्योम *areq, पूर्णांक status),
		       व्योम *areq);

पूर्णांक aपंचांगel_i2c_send_receive(काष्ठा i2c_client *client, काष्ठा aपंचांगel_i2c_cmd *cmd);

व्योम aपंचांगel_i2c_init_पढ़ो_cmd(काष्ठा aपंचांगel_i2c_cmd *cmd);
व्योम aपंचांगel_i2c_init_अक्रमom_cmd(काष्ठा aपंचांगel_i2c_cmd *cmd);
व्योम aपंचांगel_i2c_init_genkey_cmd(काष्ठा aपंचांगel_i2c_cmd *cmd, u16 keyid);
पूर्णांक aपंचांगel_i2c_init_ecdh_cmd(काष्ठा aपंचांगel_i2c_cmd *cmd,
			    काष्ठा scatterlist *pubkey);

#पूर्ण_अगर /* __ATMEL_I2C_H__ */
