<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright 2017-2021  NXP
 *
 ******************************************************************************
 * Communication stack of audio with rpmsg
 ******************************************************************************
 * Packet काष्ठाure:
 *   A SRTM message consists of a 10 bytes header followed by 0~N bytes of data
 *
 *   +---------------+-------------------------------+
 *   |               |            Content            |
 *   +---------------+-------------------------------+
 *   |  Byte Offset  | 7   6   5   4   3   2   1   0 |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       0       |           Category            |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |     1 ~ 2     |           Version             |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       3       |             Type              |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       4       |           Command             |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       5       |           Reserved0           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       6       |           Reserved1           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       7       |           Reserved2           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       8       |           Reserved3           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       9       |           Reserved4           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       10      |            DATA 0             |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   :   :   :   :   :   :   :   :   :   :   :   :   :
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |   N + 10 - 1  |            DATA N-1           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *
 *   +----------+------------+------------------------------------------------+
 *   |  Field   |    Byte    |                                                |
 *   +----------+------------+------------------------------------------------+
 *   | Category |     0      | The destination category.                      |
 *   +----------+------------+------------------------------------------------+
 *   | Version  |   1 ~ 2    | The category version of the sender of the      |
 *   |          |            | packet.                                        |
 *   |          |            | The first byte represent the major version of  |
 *   |          |            | the packet.The second byte represent the minor |
 *   |          |            | version of the packet.                         |
 *   +----------+------------+------------------------------------------------+
 *   |  Type    |     3      | The message type of current message packet.    |
 *   +----------+------------+------------------------------------------------+
 *   | Command  |     4      | The command byte sent to remote processor/SoC. |
 *   +----------+------------+------------------------------------------------+
 *   | Reserved |   5 ~ 9    | Reserved field क्रम future extension.           |
 *   +----------+------------+------------------------------------------------+
 *   | Data     |     N      | The data payload of the message packet.        |
 *   +----------+------------+------------------------------------------------+
 *
 * Audio control:
 *   SRTM Audio Control Category Request Command Table:
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   | Category | Version | Type | Command | Data                          | Function              |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x00   | Data[0]: Audio Device Index   | Open a TX Instance.   |
 *   |          |         |      |         | Data[1]:     क्रमmat           |                       |
 *   |          |         |      |         | Data[2]:     channels         |                       |
 *   |          |         |      |         | Data[3-6]:   samplerate       |                       |
 *   |          |         |      |         | Data[7-10]:  buffer_addr      |                       |
 *   |          |         |      |         | Data[11-14]: buffer_size      |                       |
 *   |          |         |      |         | Data[15-18]: period_size      |                       |
 *   |          |         |      |         | Data[19-22]: buffer_tail      |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x01   | Data[0]: Audio Device Index   | Start a TX Instance.  |
 *   |          |         |      |         | Same as above command         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x02   | Data[0]: Audio Device Index   | Pause a TX Instance.  |
 *   |          |         |      |         | Same as above command         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x03   | Data[0]: Audio Device Index   | Resume a TX Instance. |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x04   | Data[0]: Audio Device Index   | Stop a TX Instance.   |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x05   | Data[0]: Audio Device Index   | Close a TX Instance.  |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x06   | Data[0]: Audio Device Index   | Set Parameters क्रम    |
 *   |          |         |      |         | Data[1]:     क्रमmat           | a TX Instance.        |
 *   |          |         |      |         | Data[2]:     channels         |                       |
 *   |          |         |      |         | Data[3-6]:   samplerate       |                       |
 *   |          |         |      |         | Data[7-22]:  reserved         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x07   | Data[0]: Audio Device Index   | Set TX Buffer.        |
 *   |          |         |      |         | Data[1-6]:   reserved         |                       |
 *   |          |         |      |         | Data[7-10]:  buffer_addr      |                       |
 *   |          |         |      |         | Data[11-14]: buffer_size      |                       |
 *   |          |         |      |         | Data[15-18]: period_size      |                       |
 *   |          |         |      |         | Data[19-22]: buffer_tail      |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x08   | Data[0]: Audio Device Index   | Suspend a TX Instance |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x09   | Data[0]: Audio Device Index   | Resume a TX Instance. |
 *   |          |         |      |         | Data[1]:     क्रमmat           |                       |
 *   |          |         |      |         | Data[2]:     channels         |                       |
 *   |          |         |      |         | Data[3-6]:   samplerate       |                       |
 *   |          |         |      |         | Data[7-10]:  buffer_addr      |                       |
 *   |          |         |      |         | Data[11-14]: buffer_size      |                       |
 *   |          |         |      |         | Data[15-18]: period_size      |                       |
 *   |          |         |      |         | Data[19-22]: buffer_tail      |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0A   | Data[0]: Audio Device Index   | Open a RX Instance.   |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0B   | Data[0]: Audio Device Index   | Start a RX Instance.  |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0C   | Data[0]: Audio Device Index   | Pause a RX Instance.  |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0D   | Data[0]: Audio Device Index   | Resume a RX Instance. |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0E   | Data[0]: Audio Device Index   | Stop a RX Instance.   |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0F   | Data[0]: Audio Device Index   | Close a RX Instance.  |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x10   | Data[0]: Audio Device Index   | Set Parameters क्रम    |
 *   |          |         |      |         | Data[1]:     क्रमmat           | a RX Instance.        |
 *   |          |         |      |         | Data[2]:     channels         |                       |
 *   |          |         |      |         | Data[3-6]:   samplerate       |                       |
 *   |          |         |      |         | Data[7-22]:  reserved         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x11   | Data[0]: Audio Device Index   | Set RX Buffer.        |
 *   |          |         |      |         | Data[1-6]:   reserved         |                       |
 *   |          |         |      |         | Data[7-10]:  buffer_addr      |                       |
 *   |          |         |      |         | Data[11-14]: buffer_size      |                       |
 *   |          |         |      |         | Data[15-18]: period_size      |                       |
 *   |          |         |      |         | Data[19-22]: buffer_tail      |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x12   | Data[0]: Audio Device Index   | Suspend a RX Instance.|
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x13   | Data[0]: Audio Device Index   | Resume a RX Instance. |
 *   |          |         |      |         | Data[1]:     क्रमmat           |                       |
 *   |          |         |      |         | Data[2]:     channels         |                       |
 *   |          |         |      |         | Data[3-6]:   samplerate       |                       |
 *   |          |         |      |         | Data[7-10]:  buffer_addr      |                       |
 *   |          |         |      |         | Data[11-14]: buffer_size      |                       |
 *   |          |         |      |         | Data[15-18]: period_size      |                       |
 *   |          |         |      |         | Data[19-22]: buffer_tail      |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x14   | Data[0]: Audio Device Index   | Set रेजिस्टर value    |
 *   |          |         |      |         | Data[1-6]:   reserved         | to codec              |
 *   |          |         |      |         | Data[7-10]:  रेजिस्टर         |                       |
 *   |          |         |      |         | Data[11-14]: value            |                       |
 *   |          |         |      |         | Data[15-22]: reserved         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x15   | Data[0]: Audio Device Index   | Get रेजिस्टर value    |
 *   |          |         |      |         | Data[1-6]:   reserved         | from codec            |
 *   |          |         |      |         | Data[7-10]:  रेजिस्टर         |                       |
 *   |          |         |      |         | Data[11-22]: reserved         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   Note 1: See <List of Sample Format> क्रम available value of
 *           Sample Format;
 *   Note 2: See <List of Audio Channels> क्रम available value of Channels;
 *   Note 3: Sample Rate of Set Parameters क्रम an Audio TX Instance
 *           Command and Set Parameters क्रम an Audio RX Instance Command is
 *           in little-endian क्रमmat.
 *
 *   SRTM Audio Control Category Response Command Table:
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   | Category | Version | Type | Command | Data                          | Function              |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x00   | Data[0]: Audio Device Index   | Reply क्रम Open        |
 *   |          |         |      |         | Data[1]: Return code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x01   | Data[0]: Audio Device Index   | Reply क्रम Start       |
 *   |          |         |      |         | Data[1]: Return code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x02   | Data[0]: Audio Device Index   | Reply क्रम Pause       |
 *   |          |         |      |         | Data[1]: Return code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x03   | Data[0]: Audio Device Index   | Reply क्रम Resume      |
 *   |          |         |      |         | Data[1]: Return code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x04   | Data[0]: Audio Device Index   | Reply क्रम Stop        |
 *   |          |         |      |         | Data[1]: Return code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x05   | Data[0]: Audio Device Index   | Reply क्रम Close       |
 *   |          |         |      |         | Data[1]: Return code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x06   | Data[0]: Audio Device Index   | Reply क्रम Set Param   |
 *   |          |         |      |         | Data[1]: Return code          | क्रम a TX Instance.    |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x07   | Data[0]: Audio Device Index   | Reply क्रम Set         |
 *   |          |         |      |         | Data[1]: Return code          | TX Buffer             |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x08   | Data[0]: Audio Device Index   | Reply क्रम Suspend     |
 *   |          |         |      |         | Data[1]: Return code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x09   | Data[0]: Audio Device Index   | Reply क्रम Resume      |
 *   |          |         |      |         | Data[1]: Return code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0A   | Data[0]: Audio Device Index   | Reply क्रम Open        |
 *   |          |         |      |         | Data[1]: Return code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0B   | Data[0]: Audio Device Index   | Reply क्रम Start       |
 *   |          |         |      |         | Data[1]: Return code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0C   | Data[0]: Audio Device Index   | Reply क्रम Pause       |
 *   |          |         |      |         | Data[1]: Return code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0D   | Data[0]: Audio Device Index   | Reply क्रम Resume      |
 *   |          |         |      |         | Data[1]: Return code          | a RX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0E   | Data[0]: Audio Device Index   | Reply क्रम Stop        |
 *   |          |         |      |         | Data[1]: Return code          | a RX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0F   | Data[0]: Audio Device Index   | Reply क्रम Close       |
 *   |          |         |      |         | Data[1]: Return code          | a RX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x10   | Data[0]: Audio Device Index   | Reply क्रम Set Param   |
 *   |          |         |      |         | Data[1]: Return code          | क्रम a RX Instance.    |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x11   | Data[0]: Audio Device Index   | Reply क्रम Set         |
 *   |          |         |      |         | Data[1]: Return code          | RX Buffer             |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x12   | Data[0]: Audio Device Index   | Reply क्रम Suspend     |
 *   |          |         |      |         | Data[1]: Return code          | a RX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x13   | Data[0]: Audio Device Index   | Reply क्रम Resume      |
 *   |          |         |      |         | Data[1]: Return code          | a RX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x14   | Data[0]: Audio Device Index   | Reply क्रम Set codec   |
 *   |          |         |      |         | Data[1]: Return code          | रेजिस्टर value        |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x15   | Data[0]: Audio Device Index   | Reply क्रम Get codec   |
 *   |          |         |      |         | Data[1]: Return code          | रेजिस्टर value        |
 *   |          |         |      |         | Data[2-6]:   reserved         |                       |
 *   |          |         |      |         | Data[7-10]:  रेजिस्टर         |                       |
 *   |          |         |      |         | Data[11-14]: value            |                       |
 *   |          |         |      |         | Data[15-22]: reserved         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *
 *   SRTM Audio Control Category Notअगरication Command Table:
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   | Category | Version | Type | Command | Data                          | Function              |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x02 |  0x00   | Data[0]: Audio Device Index   | Notअगरy one TX period  |
 *   |          |         |      |         |                               | is finished           |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x02 |  0x01   | Data[0]: Audio Device Index   | Notअगरy one RX period  |
 *   |          |         |      |         |                               | is finished           |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *
 *   List of Sample Format:
 *   +------------------+-----------------------+
 *   | Sample Format    |   Description         |
 *   +------------------+-----------------------+
 *   |       0x0        | S16_LE                |
 *   +------------------+-----------------------+
 *   |       0x1        | S24_LE                |
 *   +------------------+-----------------------+
 *
 *   List of Audio Channels
 *   +------------------+-----------------------+
 *   |  Audio Channel   |   Description         |
 *   +------------------+-----------------------+
 *   |       0x0        | Left Channel          |
 *   +------------------+-----------------------+
 *   |       0x1        | Right Channel         |
 *   +------------------+---------------- ------+
 *   |       0x2        | Left & Right Channel  |
 *   +------------------+-----------------------+
 *
 */

#अगर_अघोषित _IMX_PCM_RPMSG_H
#घोषणा _IMX_PCM_RPMSG_H

#समावेश <linux/pm_qos.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <sound/dmaengine_pcm.h>

#घोषणा RPMSG_TIMEOUT 1000

/* RPMSG Command (TYPE A)*/
#घोषणा TX_OPEN		0x0
#घोषणा	TX_START	0x1
#घोषणा	TX_PAUSE	0x2
#घोषणा	TX_RESTART	0x3
#घोषणा	TX_TERMINATE	0x4
#घोषणा	TX_CLOSE	0x5
#घोषणा TX_HW_PARAM	0x6
#घोषणा	TX_BUFFER	0x7
#घोषणा	TX_SUSPEND	0x8
#घोषणा	TX_RESUME	0x9

#घोषणा	RX_OPEN		0xA
#घोषणा	RX_START	0xB
#घोषणा	RX_PAUSE	0xC
#घोषणा	RX_RESTART	0xD
#घोषणा	RX_TERMINATE	0xE
#घोषणा	RX_CLOSE	0xF
#घोषणा	RX_HW_PARAM	0x10
#घोषणा	RX_BUFFER	0x11
#घोषणा	RX_SUSPEND	0x12
#घोषणा	RX_RESUME	0x13
#घोषणा SET_CODEC_VALUE 0x14
#घोषणा GET_CODEC_VALUE 0x15
#घोषणा	TX_POINTER	0x16
#घोषणा	RX_POINTER	0x17
/* Total msg numver क्रम type A */
#घोषणा MSG_TYPE_A_NUM  0x18

/* RPMSG Command (TYPE C)*/
#घोषणा	TX_PERIOD_DONE	0x0
#घोषणा	RX_PERIOD_DONE	0x1
/* Total msg numver क्रम type C */
#घोषणा MSG_TYPE_C_NUM  0x2

#घोषणा MSG_MAX_NUM     (MSG_TYPE_A_NUM + MSG_TYPE_C_NUM)

#घोषणा MSG_TYPE_A	0x0
#घोषणा MSG_TYPE_B	0x1
#घोषणा MSG_TYPE_C	0x2

#घोषणा RESP_NONE		0x0
#घोषणा RESP_NOT_ALLOWED	0x1
#घोषणा	RESP_SUCCESS		0x2
#घोषणा	RESP_FAILED		0x3

#घोषणा	RPMSG_S16_LE		0x0
#घोषणा	RPMSG_S24_LE		0x1
#घोषणा	RPMSG_S32_LE		0x2
#घोषणा	RPMSG_DSD_U16_LE	0x3
#घोषणा	RPMSG_DSD_U24_LE	0x4
#घोषणा	RPMSG_DSD_U32_LE	0x5

#घोषणा	RPMSG_CH_LEFT		0x0
#घोषणा	RPMSG_CH_RIGHT		0x1
#घोषणा	RPMSG_CH_STEREO		0x2

#घोषणा WORK_MAX_NUM    0x30

/* Category define */
#घोषणा IMX_RMPSG_LIFECYCLE     1
#घोषणा IMX_RPMSG_PMIC          2
#घोषणा IMX_RPMSG_AUDIO         3
#घोषणा IMX_RPMSG_KEY           4
#घोषणा IMX_RPMSG_GPIO          5
#घोषणा IMX_RPMSG_RTC           6
#घोषणा IMX_RPMSG_SENSOR        7

/* rpmsg version */
#घोषणा IMX_RMPSG_MAJOR         1
#घोषणा IMX_RMPSG_MINOR         0

#घोषणा TX SNDRV_PCM_STREAM_PLAYBACK
#घोषणा RX SNDRV_PCM_STREAM_CAPTURE

/**
 * काष्ठा rpmsg_head: rpmsg header काष्ठाure
 *
 * @cate: category
 * @major: major version
 * @minor: minor version
 * @type: message type (A/B/C)
 * @cmd: message command
 * @reserved: reserved space
 */
काष्ठा rpmsg_head अणु
	u8 cate;
	u8 major;
	u8 minor;
	u8 type;
	u8 cmd;
	u8 reserved[5];
पूर्ण __packed;

/**
 * काष्ठा param_s: sent rpmsg parameter
 *
 * @audioindex: audio instance index
 * @क्रमmat: audio क्रमmat
 * @channels: audio channel number
 * @rate: sample rate
 * @buffer_addr: dma buffer physical address or रेजिस्टर क्रम SET_CODEC_VALUE
 * @buffer_size: dma buffer size or रेजिस्टर value क्रम SET_CODEC_VALUE
 * @period_size: period size
 * @buffer_tail: current period index
 */
काष्ठा param_s अणु
	अचिन्हित अक्षर audioindex;
	अचिन्हित अक्षर क्रमmat;
	अचिन्हित अक्षर channels;
	अचिन्हित पूर्णांक  rate;
	अचिन्हित पूर्णांक  buffer_addr;
	अचिन्हित पूर्णांक  buffer_size;
	अचिन्हित पूर्णांक  period_size;
	अचिन्हित पूर्णांक  buffer_tail;
पूर्ण __packed;

/**
 * काष्ठा param_s: send rpmsg parameter
 *
 * @audioindex: audio instance index
 * @resp: response value
 * @reserved1: reserved space
 * @buffer_offset: the consumed offset of buffer
 * @reg_addr: रेजिस्टर addr of codec
 * @reg_data: रेजिस्टर value of codec
 * @reserved2: reserved space
 * @buffer_tail: current period index
 */
काष्ठा param_r अणु
	अचिन्हित अक्षर audioindex;
	अचिन्हित अक्षर resp;
	अचिन्हित अक्षर reserved1[1];
	अचिन्हित पूर्णांक  buffer_offset;
	अचिन्हित पूर्णांक  reg_addr;
	अचिन्हित पूर्णांक  reg_data;
	अचिन्हित अक्षर reserved2[4];
	अचिन्हित पूर्णांक  buffer_tail;
पूर्ण __packed;

/* Struct of sent message */
काष्ठा rpmsg_s_msg अणु
	काष्ठा rpmsg_head header;
	काष्ठा param_s    param;
पूर्ण;

/* Struct of received message */
काष्ठा rpmsg_r_msg अणु
	काष्ठा rpmsg_head header;
	काष्ठा param_r    param;
पूर्ण;

/* Struct of rpmsg */
काष्ठा rpmsg_msg अणु
	काष्ठा rpmsg_s_msg  s_msg;
	काष्ठा rpmsg_r_msg  r_msg;
पूर्ण;

/* Struct of rpmsg क्रम workqueue */
काष्ठा work_of_rpmsg अणु
	काष्ठा rpmsg_info   *info;
	/* Sent msg क्रम each work */
	काष्ठा rpmsg_msg    msg;
	काष्ठा work_काष्ठा  work;
पूर्ण;

/* Struct of समयr */
काष्ठा stream_समयr अणु
	काष्ठा समयr_list   समयr;
	काष्ठा rpmsg_info   *info;
	काष्ठा snd_pcm_substream *substream;
पूर्ण;

प्रकार व्योम (*dma_callback)(व्योम *arg);

/**
 * काष्ठा rpmsg_info: rpmsg audio inक्रमmation
 *
 * @rpdev: poपूर्णांकer of rpmsg_device
 * @dev: poपूर्णांकer क्रम imx_pcm_rpmsg device
 * @cmd_complete: command is finished
 * @pm_qos_req: request of pm qos
 * @r_msg: received rpmsg
 * @msg: array of rpmsg
 * @notअगरy: notअगरication msg (type C) क्रम TX & RX
 * @notअगरy_updated: notअगरication flag क्रम TX & RX
 * @rpmsg_wq: rpmsg workqueue
 * @work_list: array of work list क्रम workqueue
 * @work_ग_लिखो_index: ग_लिखो index of work list
 * @work_पढ़ो_index: पढ़ो index of work list
 * @msg_drop_count: counter of dropped msg क्रम TX & RX
 * @num_period: period number क्रम TX & RX
 * @callback_param: parameter क्रम period elapse callback क्रम TX & RX
 * @callback: period elapse callback क्रम TX & RX
 * @send_message: function poपूर्णांकer क्रम send message
 * @lock: spin lock क्रम TX & RX
 * @wq_lock: lock क्रम work queue
 * @msg_lock: lock क्रम send message
 * @stream_समयr: समयr क्रम tigger workqueue
 */
काष्ठा rpmsg_info अणु
	काष्ठा rpmsg_device      *rpdev;
	काष्ठा device            *dev;
	काष्ठा completion        cmd_complete;
	काष्ठा pm_qos_request    pm_qos_req;

	/* Received msg (global) */
	काष्ठा rpmsg_r_msg       r_msg;
	काष्ठा rpmsg_msg         msg[MSG_MAX_NUM];
	/* period करोne */
	काष्ठा rpmsg_msg         notअगरy[2];
	bool                     notअगरy_updated[2];

	काष्ठा workqueue_काष्ठा  *rpmsg_wq;
	काष्ठा work_of_rpmsg	 work_list[WORK_MAX_NUM];
	पूर्णांक                      work_ग_लिखो_index;
	पूर्णांक                      work_पढ़ो_index;
	पूर्णांक                      msg_drop_count[2];
	पूर्णांक                      num_period[2];
	व्योम                     *callback_param[2];
	dma_callback             callback[2];
	पूर्णांक (*send_message)(काष्ठा rpmsg_msg *msg, काष्ठा rpmsg_info *info);
	spinlock_t               lock[2]; /* spin lock क्रम resource protection */
	spinlock_t               wq_lock; /* spin lock क्रम resource protection */
	काष्ठा mutex             msg_lock; /* mutex क्रम resource protection */
	काष्ठा stream_समयr      stream_समयr[2];
पूर्ण;

#घोषणा IMX_PCM_DRV_NAME "imx_pcm_rpmsg"

#पूर्ण_अगर /* IMX_PCM_RPMSG_H */
