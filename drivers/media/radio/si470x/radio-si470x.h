<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  drivers/media/radio/si470x/radio-si470x.h
 *
 *  Driver क्रम radios with Silicon Lअसल Si470x FM Radio Receivers
 *
 *  Copyright (c) 2009 Tobias Lorenz <tobias.lorenz@gmx.net>
 */


/* driver definitions */
#घोषणा DRIVER_NAME "radio-si470x"


/* kernel includes */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/mutex.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-device.h>
#समावेश <यंत्र/unaligned.h>



/**************************************************************************
 * Register Definitions
 **************************************************************************/
#घोषणा RADIO_REGISTER_SIZE	2	/* 16 रेजिस्टर bit width */
#घोषणा RADIO_REGISTER_NUM	16	/* DEVICEID   ... RDSD */
#घोषणा RDS_REGISTER_NUM	6	/* STATUSRSSI ... RDSD */

#घोषणा DEVICEID		0	/* Device ID */
#घोषणा DEVICEID_PN		0xf000	/* bits 15..12: Part Number */
#घोषणा DEVICEID_MFGID		0x0fff	/* bits 11..00: Manufacturer ID */

#घोषणा SI_CHIPID		1	/* Chip ID */
#घोषणा SI_CHIPID_REV		0xfc00	/* bits 15..10: Chip Version */
#घोषणा SI_CHIPID_DEV		0x0200	/* bits 09..09: Device */
#घोषणा SI_CHIPID_FIRMWARE	0x01ff	/* bits 08..00: Firmware Version */

#घोषणा POWERCFG		2	/* Power Configuration */
#घोषणा POWERCFG_DSMUTE		0x8000	/* bits 15..15: Sofपंचांगute Disable */
#घोषणा POWERCFG_DMUTE		0x4000	/* bits 14..14: Mute Disable */
#घोषणा POWERCFG_MONO		0x2000	/* bits 13..13: Mono Select */
#घोषणा POWERCFG_RDSM		0x0800	/* bits 11..11: RDS Mode (Si4701 only) */
#घोषणा POWERCFG_SKMODE		0x0400	/* bits 10..10: Seek Mode */
#घोषणा POWERCFG_SEEKUP		0x0200	/* bits 09..09: Seek Direction */
#घोषणा POWERCFG_SEEK		0x0100	/* bits 08..08: Seek */
#घोषणा POWERCFG_DISABLE	0x0040	/* bits 06..06: Powerup Disable */
#घोषणा POWERCFG_ENABLE		0x0001	/* bits 00..00: Powerup Enable */

#घोषणा CHANNEL			3	/* Channel */
#घोषणा CHANNEL_TUNE		0x8000	/* bits 15..15: Tune */
#घोषणा CHANNEL_CHAN		0x03ff	/* bits 09..00: Channel Select */

#घोषणा SYSCONFIG1		4	/* System Configuration 1 */
#घोषणा SYSCONFIG1_RDSIEN	0x8000	/* bits 15..15: RDS Interrupt Enable (Si4701 only) */
#घोषणा SYSCONFIG1_STCIEN	0x4000	/* bits 14..14: Seek/Tune Complete Interrupt Enable */
#घोषणा SYSCONFIG1_RDS		0x1000	/* bits 12..12: RDS Enable (Si4701 only) */
#घोषणा SYSCONFIG1_DE		0x0800	/* bits 11..11: De-emphasis (0=75us 1=50us) */
#घोषणा SYSCONFIG1_AGCD		0x0400	/* bits 10..10: AGC Disable */
#घोषणा SYSCONFIG1_BLNDADJ	0x00c0	/* bits 07..06: Stereo/Mono Blend Level Adjusपंचांगent */
#घोषणा SYSCONFIG1_GPIO3	0x0030	/* bits 05..04: General Purpose I/O 3 */
#घोषणा SYSCONFIG1_GPIO2	0x000c	/* bits 03..02: General Purpose I/O 2 */
#घोषणा SYSCONFIG1_GPIO2_DIS	0x0000	/* Disable GPIO 2 पूर्णांकerrupt */
#घोषणा SYSCONFIG1_GPIO2_INT	0x0004	/* Enable STC/RDS पूर्णांकerrupt */
#घोषणा SYSCONFIG1_GPIO1	0x0003	/* bits 01..00: General Purpose I/O 1 */

#घोषणा SYSCONFIG2		5	/* System Configuration 2 */
#घोषणा SYSCONFIG2_SEEKTH	0xff00	/* bits 15..08: RSSI Seek Threshold */
#घोषणा SYSCONFIG2_BAND		0x00c0	/* bits 07..06: Band Select */
#घोषणा SYSCONFIG2_SPACE	0x0030	/* bits 05..04: Channel Spacing */
#घोषणा SYSCONFIG2_VOLUME	0x000f	/* bits 03..00: Volume */

#घोषणा SYSCONFIG3		6	/* System Configuration 3 */
#घोषणा SYSCONFIG3_SMUTER	0xc000	/* bits 15..14: Sofपंचांगute Attack/Recover Rate */
#घोषणा SYSCONFIG3_SMUTEA	0x3000	/* bits 13..12: Sofपंचांगute Attenuation */
#घोषणा SYSCONFIG3_SKSNR	0x00f0	/* bits 07..04: Seek SNR Threshold */
#घोषणा SYSCONFIG3_SKCNT	0x000f	/* bits 03..00: Seek FM Impulse Detection Threshold */

#घोषणा TEST1			7	/* Test 1 */
#घोषणा TEST1_AHIZEN		0x4000	/* bits 14..14: Audio High-Z Enable */

#घोषणा TEST2			8	/* Test 2 */
/* TEST2 only contains reserved bits */

#घोषणा BOOTCONFIG		9	/* Boot Configuration */
/* BOOTCONFIG only contains reserved bits */

#घोषणा STATUSRSSI		10	/* Status RSSI */
#घोषणा STATUSRSSI_RDSR		0x8000	/* bits 15..15: RDS Ready (Si4701 only) */
#घोषणा STATUSRSSI_STC		0x4000	/* bits 14..14: Seek/Tune Complete */
#घोषणा STATUSRSSI_SF		0x2000	/* bits 13..13: Seek Fail/Band Limit */
#घोषणा STATUSRSSI_AFCRL	0x1000	/* bits 12..12: AFC Rail */
#घोषणा STATUSRSSI_RDSS		0x0800	/* bits 11..11: RDS Synchronized (Si4701 only) */
#घोषणा STATUSRSSI_BLERA	0x0600	/* bits 10..09: RDS Block A Errors (Si4701 only) */
#घोषणा STATUSRSSI_ST		0x0100	/* bits 08..08: Stereo Indicator */
#घोषणा STATUSRSSI_RSSI		0x00ff	/* bits 07..00: RSSI (Received Signal Strength Indicator) */

#घोषणा READCHAN		11	/* Read Channel */
#घोषणा READCHAN_BLERB		0xc000	/* bits 15..14: RDS Block D Errors (Si4701 only) */
#घोषणा READCHAN_BLERC		0x3000	/* bits 13..12: RDS Block C Errors (Si4701 only) */
#घोषणा READCHAN_BLERD		0x0c00	/* bits 11..10: RDS Block B Errors (Si4701 only) */
#घोषणा READCHAN_READCHAN	0x03ff	/* bits 09..00: Read Channel */

#घोषणा RDSA			12	/* RDSA */
#घोषणा RDSA_RDSA		0xffff	/* bits 15..00: RDS Block A Data (Si4701 only) */

#घोषणा RDSB			13	/* RDSB */
#घोषणा RDSB_RDSB		0xffff	/* bits 15..00: RDS Block B Data (Si4701 only) */

#घोषणा RDSC			14	/* RDSC */
#घोषणा RDSC_RDSC		0xffff	/* bits 15..00: RDS Block C Data (Si4701 only) */

#घोषणा RDSD			15	/* RDSD */
#घोषणा RDSD_RDSD		0xffff	/* bits 15..00: RDS Block D Data (Si4701 only) */



/**************************************************************************
 * General Driver Definitions
 **************************************************************************/

/*
 * si470x_device - निजी data
 */
काष्ठा si470x_device अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device videodev;
	काष्ठा v4l2_ctrl_handler hdl;
	पूर्णांक band;

	/* Siद_असल पूर्णांकernal रेजिस्टरs (0..15) */
	अचिन्हित लघु रेजिस्टरs[RADIO_REGISTER_NUM];

	/* RDS receive buffer */
	रुको_queue_head_t पढ़ो_queue;
	काष्ठा mutex lock;		/* buffer locking */
	अचिन्हित अक्षर *buffer;		/* size is always multiple of three */
	अचिन्हित पूर्णांक buf_size;
	अचिन्हित पूर्णांक rd_index;
	अचिन्हित पूर्णांक wr_index;

	काष्ठा completion completion;
	bool status_rssi_स्वतः_update;	/* Does RSSI get updated स्वतःmatic? */

	/* si470x ops */

	पूर्णांक (*get_रेजिस्टर)(काष्ठा si470x_device *radio, पूर्णांक regnr);
	पूर्णांक (*set_रेजिस्टर)(काष्ठा si470x_device *radio, पूर्णांक regnr);
	पूर्णांक (*fops_खोलो)(काष्ठा file *file);
	पूर्णांक (*fops_release)(काष्ठा file *file);
	पूर्णांक (*vidioc_querycap)(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_capability *capability);

#अगर IS_ENABLED(CONFIG_USB_SI470X)
	/* reference to USB and video device */
	काष्ठा usb_device *usbdev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	अक्षर *usb_buf;

	/* Interrupt endpoपूर्णांक handling */
	अक्षर *पूर्णांक_in_buffer;
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांक_in_endpoपूर्णांक;
	काष्ठा urb *पूर्णांक_in_urb;
	पूर्णांक पूर्णांक_in_running;

	/* scratch page */
	अचिन्हित अक्षर software_version;
	अचिन्हित अक्षर hardware_version;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_I2C_SI470X)
	काष्ठा i2c_client *client;
	काष्ठा gpio_desc *gpio_reset;
#पूर्ण_अगर
पूर्ण;



/**************************************************************************
 * Firmware Versions
 **************************************************************************/

#घोषणा RADIO_FW_VERSION	12



/**************************************************************************
 * Frequency Multiplicator
 **************************************************************************/

/*
 * The frequency is set in units of 62.5 Hz when using V4L2_TUNER_CAP_LOW,
 * 62.5 kHz otherwise.
 * The tuner is able to have a channel spacing of 50, 100 or 200 kHz.
 * tuner->capability is thereक्रमe set to V4L2_TUNER_CAP_LOW
 * The FREQ_MUL is then: 1 MHz / 62.5 Hz = 16000
 */
#घोषणा FREQ_MUL (1000000 / 62.5)



/**************************************************************************
 * Common Functions
 **************************************************************************/
बाह्य स्थिर काष्ठा video_device si470x_viddev_ढाँचा;
बाह्य स्थिर काष्ठा v4l2_ctrl_ops si470x_ctrl_ops;
पूर्णांक si470x_disconnect_check(काष्ठा si470x_device *radio);
पूर्णांक si470x_set_freq(काष्ठा si470x_device *radio, अचिन्हित पूर्णांक freq);
पूर्णांक si470x_start(काष्ठा si470x_device *radio);
पूर्णांक si470x_stop(काष्ठा si470x_device *radio);
