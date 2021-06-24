<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

/*
	Driver architecture
	*******************

	saa7164_core.c/buffer.c/cards.c/i2c.c/dvb.c
		|	: Standard Linux driver framework क्रम creating
		|	: exposing and managing पूर्णांकerfaces to the rest
		|	: of the kernel or userland. Also uses _fw.c to load
		|	: firmware direct पूर्णांकo the PCIe bus, bypassing layers.
		V
	saa7164_api..()	: Translate kernel specअगरic functions/features
		|	: पूर्णांकo command buffers.
		V
	saa7164_cmd..()	: Manages the flow of command packets on/off,
		|	: the bus. Deal with bus errors, समयouts etc.
		V
	saa7164_bus..() : Manage a पढ़ो/ग_लिखो memory ring buffer in the
		|	: PCIe Address space.
		|
		|		saa7164_fw...()	: Load any firmware
		|			|	: direct पूर्णांकo the device
		V			V
	<- ----------------- PCIe address space -------------------- ->
*/

#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/mutex.h>
#समावेश <linux/crc32.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>

#समावेश <media/tuner.h>
#समावेश <media/tveeprom.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dmxdev.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>

#समावेश "saa7164-reg.h"
#समावेश "saa7164-types.h"

#घोषणा SAA7164_MAXBOARDS 8

#घोषणा UNSET (-1U)
#घोषणा SAA7164_BOARD_NOAUTO			UNSET
#घोषणा SAA7164_BOARD_UNKNOWN			0
#घोषणा SAA7164_BOARD_UNKNOWN_REV2		1
#घोषणा SAA7164_BOARD_UNKNOWN_REV3		2
#घोषणा SAA7164_BOARD_HAUPPAUGE_HVR2250		3
#घोषणा SAA7164_BOARD_HAUPPAUGE_HVR2200		4
#घोषणा SAA7164_BOARD_HAUPPAUGE_HVR2200_2	5
#घोषणा SAA7164_BOARD_HAUPPAUGE_HVR2200_3	6
#घोषणा SAA7164_BOARD_HAUPPAUGE_HVR2250_2	7
#घोषणा SAA7164_BOARD_HAUPPAUGE_HVR2250_3	8
#घोषणा SAA7164_BOARD_HAUPPAUGE_HVR2200_4	9
#घोषणा SAA7164_BOARD_HAUPPAUGE_HVR2200_5	10
#घोषणा SAA7164_BOARD_HAUPPAUGE_HVR2255proto	11
#घोषणा SAA7164_BOARD_HAUPPAUGE_HVR2255		12
#घोषणा SAA7164_BOARD_HAUPPAUGE_HVR2205		13

#घोषणा SAA7164_MAX_UNITS		8
#घोषणा SAA7164_TS_NUMBER_OF_LINES	312
#घोषणा SAA7164_PS_NUMBER_OF_LINES	256
#घोषणा SAA7164_PT_ENTRIES		16 /* (312 * 188) / 4096 */
#घोषणा SAA7164_MAX_ENCODER_BUFFERS	64 /* max 5secs of latency at 6Mbps */
#घोषणा SAA7164_MAX_VBI_BUFFERS		64

/* Port related defines */
#घोषणा SAA7164_PORT_TS1	(0)
#घोषणा SAA7164_PORT_TS2	(SAA7164_PORT_TS1 + 1)
#घोषणा SAA7164_PORT_ENC1	(SAA7164_PORT_TS2 + 1)
#घोषणा SAA7164_PORT_ENC2	(SAA7164_PORT_ENC1 + 1)
#घोषणा SAA7164_PORT_VBI1	(SAA7164_PORT_ENC2 + 1)
#घोषणा SAA7164_PORT_VBI2	(SAA7164_PORT_VBI1 + 1)
#घोषणा SAA7164_MAX_PORTS	(SAA7164_PORT_VBI2 + 1)

#घोषणा DBGLVL_FW    4
#घोषणा DBGLVL_DVB   8
#घोषणा DBGLVL_I2C  16
#घोषणा DBGLVL_API  32
#घोषणा DBGLVL_CMD  64
#घोषणा DBGLVL_BUS 128
#घोषणा DBGLVL_IRQ 256
#घोषणा DBGLVL_BUF 512
#घोषणा DBGLVL_ENC 1024
#घोषणा DBGLVL_VBI 2048
#घोषणा DBGLVL_THR 4096
#घोषणा DBGLVL_CPU 8192

#घोषणा SAA7164_NORMS \
	(V4L2_STD_NTSC_M | V4L2_STD_NTSC_M_JP)

/* TV frequency range copied from tuner-core.c */
#घोषणा SAA7164_TV_MIN_FREQ (44U * 16U)
#घोषणा SAA7164_TV_MAX_FREQ (958U * 16U)

क्रमागत port_t अणु
	SAA7164_MPEG_UNDEFINED = 0,
	SAA7164_MPEG_DVB,
	SAA7164_MPEG_ENCODER,
	SAA7164_MPEG_VBI,
पूर्ण;

क्रमागत saa7164_i2c_bus_nr अणु
	SAA7164_I2C_BUS_0 = 0,
	SAA7164_I2C_BUS_1,
	SAA7164_I2C_BUS_2,
पूर्ण;

क्रमागत saa7164_buffer_flags अणु
	SAA7164_BUFFER_UNDEFINED = 0,
	SAA7164_BUFFER_FREE,
	SAA7164_BUFFER_BUSY,
	SAA7164_BUFFER_FULL
पूर्ण;

क्रमागत saa7164_unit_type अणु
	SAA7164_UNIT_UNDEFINED = 0,
	SAA7164_UNIT_DIGITAL_DEMODULATOR,
	SAA7164_UNIT_ANALOG_DEMODULATOR,
	SAA7164_UNIT_TUNER,
	SAA7164_UNIT_EEPROM,
	SAA7164_UNIT_ZILOG_IRBLASTER,
	SAA7164_UNIT_ENCODER,
पूर्ण;

/* The PCIe bridge करोesn't grant direct access to i2c.
 * Instead, you address i2c devices using a uniqely
 * allocated 'unitid' value via a messaging API. This
 * is a problem. The kernel and existing demod/tuner
 * drivers expect to talk 'i2c', so we have to मुख्यtain
 * a translation layer, and a series of functions to
 * convert i2c bus + device address पूर्णांकo a unit id.
 */
काष्ठा saa7164_unit अणु
	क्रमागत saa7164_unit_type type;
	u8	id;
	अक्षर	*name;
	क्रमागत saa7164_i2c_bus_nr i2c_bus_nr;
	u8	i2c_bus_addr;
	u8	i2c_reg_len;
पूर्ण;

काष्ठा saa7164_board अणु
	अक्षर	*name;
	क्रमागत port_t porta, portb, portc,
		portd, porte, portf;
	क्रमागत अणु
		SAA7164_CHIP_UNDEFINED = 0,
		SAA7164_CHIP_REV2,
		SAA7164_CHIP_REV3,
	पूर्ण chiprev;
	काष्ठा	saa7164_unit unit[SAA7164_MAX_UNITS];
पूर्ण;

काष्ठा saa7164_subid अणु
	u16     subvenकरोr;
	u16     subdevice;
	u32     card;
पूर्ण;

काष्ठा saa7164_encoder_fh अणु
	काष्ठा v4l2_fh fh;
	काष्ठा saa7164_port *port;
	atomic_t v4l_पढ़ोing;
पूर्ण;

काष्ठा saa7164_vbi_fh अणु
	काष्ठा v4l2_fh fh;
	काष्ठा saa7164_port *port;
	atomic_t v4l_पढ़ोing;
पूर्ण;

काष्ठा saa7164_histogram_bucket अणु
	u32 val;
	u32 count;
	u64 update_समय;
पूर्ण;

काष्ठा saa7164_histogram अणु
	अक्षर name[32];
	काष्ठा saa7164_histogram_bucket counter1[64];
पूर्ण;

काष्ठा saa7164_user_buffer अणु
	काष्ठा list_head list;

	/* Attributes */
	u8  *data;
	u32 pos;
	u32 actual_size;

	u32 crc;
पूर्ण;

काष्ठा saa7164_fw_status अणु

	/* RISC Core details */
	u32	status;
	u32	mode;
	u32	spec;
	u32	inst;
	u32	cpuload;
	u32	reमुख्यheap;

	/* Firmware version */
	u32	version;
	u32	major;
	u32	sub;
	u32	rel;
	u32	buildnr;
पूर्ण;

काष्ठा saa7164_dvb अणु
	काष्ठा mutex lock;
	काष्ठा dvb_adapter adapter;
	काष्ठा dvb_frontend *frontend;
	काष्ठा dvb_demux demux;
	काष्ठा dmxdev dmxdev;
	काष्ठा dmx_frontend fe_hw;
	काष्ठा dmx_frontend fe_mem;
	काष्ठा dvb_net net;
	पूर्णांक feeding;
पूर्ण;

काष्ठा saa7164_i2c अणु
	काष्ठा saa7164_dev		*dev;

	क्रमागत saa7164_i2c_bus_nr		nr;

	/* I2C I/O */
	काष्ठा i2c_adapter		i2c_adap;
	काष्ठा i2c_client		i2c_client;
	u32				i2c_rc;
पूर्ण;

काष्ठा saa7164_tvnorm अणु
	अक्षर		*name;
	v4l2_std_id	id;
पूर्ण;

काष्ठा saa7164_encoder_params अणु
	काष्ठा saa7164_tvnorm encodernorm;
	u32 height;
	u32 width;
	u32 is_50hz;
	u32 bitrate; /* bps */
	u32 bitrate_peak; /* bps */
	u32 bitrate_mode;
	u32 stream_type; /* V4L2_MPEG_STREAM_TYPE_MPEG2_TS */

	u32 audio_sampling_freq;
	u32 ctl_mute;
	u32 ctl_aspect;
	u32 refdist;
	u32 gop_size;
पूर्ण;

काष्ठा saa7164_vbi_params अणु
	काष्ठा saa7164_tvnorm encodernorm;
	u32 height;
	u32 width;
	u32 is_50hz;
	u32 bitrate; /* bps */
	u32 bitrate_peak; /* bps */
	u32 bitrate_mode;
	u32 stream_type; /* V4L2_MPEG_STREAM_TYPE_MPEG2_TS */

	u32 audio_sampling_freq;
	u32 ctl_mute;
	u32 ctl_aspect;
	u32 refdist;
	u32 gop_size;
पूर्ण;

काष्ठा saa7164_port;

काष्ठा saa7164_buffer अणु
	काष्ठा list_head list;

	/* Note of which h/w buffer list index position we occupy */
	पूर्णांक idx;

	काष्ठा saa7164_port *port;

	/* Hardware Specअगरic */
	/* PCI Memory allocations */
	क्रमागत saa7164_buffer_flags flags; /* Free, Busy, Full */

	/* A block of page align PCI memory */
	u32 pci_size;	/* PCI allocation size in bytes */
	u64 *cpu;	/* Virtual address */
	dma_addr_t dma;	/* Physical address */
	u32 crc;	/* Checksum क्रम the entire buffer data */

	/* A page table that splits the block पूर्णांकo a number of entries */
	u32 pt_size;		/* PCI allocation size in bytes */
	u64 *pt_cpu;		/* Virtual address */
	dma_addr_t pt_dma;	/* Physical address */

	/* Encoder fops */
	u32 pos;
	u32 actual_size;
पूर्ण;

काष्ठा saa7164_port अणु

	काष्ठा saa7164_dev *dev;
	क्रमागत port_t type;
	पूर्णांक nr;

	/* --- Generic port attributes --- */

	/* HW stream parameters */
	काष्ठा पंचांगHWStreamParameters hw_streamingparams;

	/* DMA configuration values, is seeded during initialization */
	काष्ठा पंचांगComResDMATermDescrHeader hwcfg;

	/* hardware specअगरic रेजिस्टरs */
	u32 bufcounter;
	u32 pitch;
	u32 bufsize;
	u32 bufoffset;
	u32 bufptr32l;
	u32 bufptr32h;
	u64 bufptr64;

	u32 numpte;	/* Number of entries in array, only valid in head */

	काष्ठा mutex dmaqueue_lock;
	काष्ठा saa7164_buffer dmaqueue;

	u64 last_irq_msecs, last_svc_msecs;
	u64 last_irq_msecs_dअगरf, last_svc_msecs_dअगरf;
	u32 last_svc_wp;
	u32 last_svc_rp;
	u64 last_irq_svc_msecs_dअगरf;
	u64 last_पढ़ो_msecs, last_पढ़ो_msecs_dअगरf;
	u64 last_poll_msecs, last_poll_msecs_dअगरf;

	काष्ठा saa7164_histogram irq_पूर्णांकerval;
	काष्ठा saa7164_histogram svc_पूर्णांकerval;
	काष्ठा saa7164_histogram irq_svc_पूर्णांकerval;
	काष्ठा saa7164_histogram पढ़ो_पूर्णांकerval;
	काष्ठा saa7164_histogram poll_पूर्णांकerval;

	/* --- DVB Transport Specअगरic --- */
	काष्ठा saa7164_dvb dvb;
	काष्ठा i2c_client *i2c_client_demod;
	काष्ठा i2c_client *i2c_client_tuner;

	/* --- Encoder/V4L related attributes --- */
	/* Encoder */
	/* Defaults established in saa7164-encoder.c */
	काष्ठा saa7164_tvnorm encodernorm;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	v4l2_std_id std;
	u32 height;
	u32 width;
	u32 freq;
	u8 mux_input;
	u8 encoder_profile;
	u8 video_क्रमmat;
	u8 audio_क्रमmat;
	u8 video_resolution;
	u16 ctl_brightness;
	u16 ctl_contrast;
	u16 ctl_hue;
	u16 ctl_saturation;
	u16 ctl_sharpness;
	s8 ctl_volume;

	काष्ठा पंचांगComResAFeatureDescrHeader audfeat;
	काष्ठा पंचांगComResEncoderDescrHeader encunit;
	काष्ठा पंचांगComResProcDescrHeader vidproc;
	काष्ठा पंचांगComResExtDevDescrHeader अगरunit;
	काष्ठा पंचांगComResTunerDescrHeader tunerunit;

	काष्ठा work_काष्ठा workenc;

	/* V4L Encoder Video */
	काष्ठा saa7164_encoder_params encoder_params;
	काष्ठा video_device *v4l_device;
	atomic_t v4l_पढ़ोer_count;

	काष्ठा saa7164_buffer list_buf_used;
	काष्ठा saa7164_buffer list_buf_मुक्त;
	रुको_queue_head_t रुको_पढ़ो;

	/* V4L VBI */
	काष्ठा पंचांगComResVBIFormatDescrHeader vbi_fmt_ntsc;
	काष्ठा saa7164_vbi_params vbi_params;
	काष्ठा saa7164_port *enc_port;

	/* Debug */
	u32 sync_errors;
	u32 v_cc_errors;
	u32 a_cc_errors;
	u8 last_v_cc;
	u8 last_a_cc;
	u32 करोne_first_पूर्णांकerrupt;
पूर्ण;

काष्ठा saa7164_dev अणु
	काष्ठा list_head	devlist;
	atomic_t		refcount;

	काष्ठा v4l2_device v4l2_dev;

	/* pci stuff */
	काष्ठा pci_dev	*pci;
	अचिन्हित अक्षर	pci_rev, pci_lat;
	पूर्णांक		pci_bus, pci_slot;
	u32		__iomem *lmmio;
	u8		__iomem *bmmio;
	u32		__iomem *lmmio2;
	u8		__iomem *bmmio2;
	पूर्णांक		pci_irqmask;

	/* board details */
	पूर्णांक	nr;
	पूर्णांक	hwrevision;
	u32	board;
	अक्षर	name[16];

	/* firmware status */
	काष्ठा saa7164_fw_status	fw_status;
	u32				firmwareloaded;

	काष्ठा पंचांगComResHWDescr		hwdesc;
	काष्ठा पंचांगComResInterfaceDescr	पूर्णांकfdesc;
	काष्ठा पंचांगComResBusDescr		busdesc;

	काष्ठा पंचांगComResBusInfo		bus;

	/* Interrupt status and ack रेजिस्टरs */
	u32 पूर्णांक_status;
	u32 पूर्णांक_ack;
	bool msi;

	काष्ठा cmd			cmds[SAA_CMD_MAX_MSG_UNITS];
	काष्ठा mutex			lock;

	/* I2c related */
	काष्ठा saa7164_i2c i2c_bus[3];

	/* Transport related */
	काष्ठा saa7164_port ports[SAA7164_MAX_PORTS];

	/* Deferred command/api पूर्णांकerrupts handling */
	काष्ठा work_काष्ठा workcmd;

	/* A kernel thपढ़ो to monitor the firmware log, used
	 * only in debug mode.
	 */
	काष्ठा task_काष्ठा *kthपढ़ो;

पूर्ण;

बाह्य काष्ठा list_head saa7164_devlist;
बाह्य अचिन्हित पूर्णांक रुकोsecs;
बाह्य अचिन्हित पूर्णांक encoder_buffers;
बाह्य अचिन्हित पूर्णांक vbi_buffers;

/* ----------------------------------------------------------- */
/* saa7164-core.c                                              */
व्योम saa7164_dumpregs(काष्ठा saa7164_dev *dev, u32 addr);
व्योम saa7164_getfirmwarestatus(काष्ठा saa7164_dev *dev);
u32 saa7164_अ_लोurrentfirmwareversion(काष्ठा saa7164_dev *dev);
व्योम saa7164_histogram_update(काष्ठा saa7164_histogram *hg, u32 val);

/* ----------------------------------------------------------- */
/* saa7164-fw.c                                                */
पूर्णांक saa7164_करोwnloadfirmware(काष्ठा saa7164_dev *dev);

/* ----------------------------------------------------------- */
/* saa7164-i2c.c                                               */
बाह्य पूर्णांक saa7164_i2c_रेजिस्टर(काष्ठा saa7164_i2c *bus);
बाह्य पूर्णांक saa7164_i2c_unरेजिस्टर(काष्ठा saa7164_i2c *bus);
बाह्य व्योम saa7164_call_i2c_clients(काष्ठा saa7164_i2c *bus,
	अचिन्हित पूर्णांक cmd, व्योम *arg);

/* ----------------------------------------------------------- */
/* saa7164-bus.c                                               */
पूर्णांक saa7164_bus_setup(काष्ठा saa7164_dev *dev);
व्योम saa7164_bus_dump(काष्ठा saa7164_dev *dev);
पूर्णांक saa7164_bus_set(काष्ठा saa7164_dev *dev, काष्ठा पंचांगComResInfo* msg,
	व्योम *buf);
पूर्णांक saa7164_bus_get(काष्ठा saa7164_dev *dev, काष्ठा पंचांगComResInfo* msg,
	व्योम *buf, पूर्णांक peekonly);

/* ----------------------------------------------------------- */
/* saa7164-cmd.c                                               */
पूर्णांक saa7164_cmd_send(काष्ठा saa7164_dev *dev,
	u8 id, क्रमागत पंचांगComResCmd command, u16 controlselector,
	u16 size, व्योम *buf);
व्योम saa7164_cmd_संकेत(काष्ठा saa7164_dev *dev, u8 seqno);
पूर्णांक saa7164_irq_dequeue(काष्ठा saa7164_dev *dev);

/* ----------------------------------------------------------- */
/* saa7164-api.c                                               */
पूर्णांक saa7164_api_get_fw_version(काष्ठा saa7164_dev *dev, u32 *version);
पूर्णांक saa7164_api_क्रमागत_subdevs(काष्ठा saa7164_dev *dev);
पूर्णांक saa7164_api_i2c_पढ़ो(काष्ठा saa7164_i2c *bus, u8 addr, u32 reglen, u8 *reg,
	u32 datalen, u8 *data);
पूर्णांक saa7164_api_i2c_ग_लिखो(काष्ठा saa7164_i2c *bus, u8 addr,
	u32 datalen, u8 *data);
पूर्णांक saa7164_api_dअगर_ग_लिखो(काष्ठा saa7164_i2c *bus, u8 addr,
	u32 datalen, u8 *data);
पूर्णांक saa7164_api_पढ़ो_eeprom(काष्ठा saa7164_dev *dev, u8 *buf, पूर्णांक buflen);
पूर्णांक saa7164_api_set_gpiobit(काष्ठा saa7164_dev *dev, u8 unitid, u8 pin);
पूर्णांक saa7164_api_clear_gpiobit(काष्ठा saa7164_dev *dev, u8 unitid, u8 pin);
पूर्णांक saa7164_api_transition_port(काष्ठा saa7164_port *port, u8 mode);
पूर्णांक saa7164_api_initialize_dअगर(काष्ठा saa7164_port *port);
पूर्णांक saa7164_api_configure_dअगर(काष्ठा saa7164_port *port, u32 std);
पूर्णांक saa7164_api_set_encoder(काष्ठा saa7164_port *port);
पूर्णांक saa7164_api_get_encoder(काष्ठा saa7164_port *port);
पूर्णांक saa7164_api_set_aspect_ratio(काष्ठा saa7164_port *port);
पूर्णांक saa7164_api_set_usercontrol(काष्ठा saa7164_port *port, u8 ctl);
पूर्णांक saa7164_api_get_usercontrol(काष्ठा saa7164_port *port, u8 ctl);
पूर्णांक saa7164_api_set_videomux(काष्ठा saa7164_port *port);
पूर्णांक saa7164_api_audio_mute(काष्ठा saa7164_port *port, पूर्णांक mute);
पूर्णांक saa7164_api_set_audio_volume(काष्ठा saa7164_port *port, s8 level);
पूर्णांक saa7164_api_set_audio_std(काष्ठा saa7164_port *port);
पूर्णांक saa7164_api_set_audio_detection(काष्ठा saa7164_port *port, पूर्णांक स्वतःdetect);
पूर्णांक saa7164_api_get_videomux(काष्ठा saa7164_port *port);
पूर्णांक saa7164_api_set_vbi_क्रमmat(काष्ठा saa7164_port *port);
पूर्णांक saa7164_api_set_debug(काष्ठा saa7164_dev *dev, u8 level);
पूर्णांक saa7164_api_collect_debug(काष्ठा saa7164_dev *dev);
पूर्णांक saa7164_api_get_load_info(काष्ठा saa7164_dev *dev,
	काष्ठा पंचांगFwInfoStruct *i);

/* ----------------------------------------------------------- */
/* saa7164-cards.c                                             */
बाह्य काष्ठा saa7164_board saa7164_boards[];
बाह्य स्थिर अचिन्हित पूर्णांक saa7164_bcount;

बाह्य काष्ठा saa7164_subid saa7164_subids[];
बाह्य स्थिर अचिन्हित पूर्णांक saa7164_idcount;

बाह्य व्योम saa7164_card_list(काष्ठा saa7164_dev *dev);
बाह्य व्योम saa7164_gpio_setup(काष्ठा saa7164_dev *dev);
बाह्य व्योम saa7164_card_setup(काष्ठा saa7164_dev *dev);

बाह्य पूर्णांक saa7164_i2caddr_to_reglen(काष्ठा saa7164_i2c *bus, पूर्णांक addr);
बाह्य पूर्णांक saa7164_i2caddr_to_unitid(काष्ठा saa7164_i2c *bus, पूर्णांक addr);
बाह्य अक्षर *saa7164_unitid_name(काष्ठा saa7164_dev *dev, u8 unitid);

/* ----------------------------------------------------------- */
/* saa7164-dvb.c                                               */
बाह्य पूर्णांक saa7164_dvb_रेजिस्टर(काष्ठा saa7164_port *port);
बाह्य पूर्णांक saa7164_dvb_unरेजिस्टर(काष्ठा saa7164_port *port);

/* ----------------------------------------------------------- */
/* saa7164-buffer.c                                            */
बाह्य काष्ठा saa7164_buffer *saa7164_buffer_alloc(
	काष्ठा saa7164_port *port, u32 len);
बाह्य पूर्णांक saa7164_buffer_dealloc(काष्ठा saa7164_buffer *buf);
बाह्य व्योम saa7164_buffer_display(काष्ठा saa7164_buffer *buf);
बाह्य पूर्णांक saa7164_buffer_activate(काष्ठा saa7164_buffer *buf, पूर्णांक i);
बाह्य पूर्णांक saa7164_buffer_cfg_port(काष्ठा saa7164_port *port);
बाह्य काष्ठा saa7164_user_buffer *saa7164_buffer_alloc_user(
	काष्ठा saa7164_dev *dev, u32 len);
बाह्य व्योम saa7164_buffer_dealloc_user(काष्ठा saa7164_user_buffer *buf);
बाह्य पूर्णांक saa7164_buffer_zero_offsets(काष्ठा saa7164_port *port, पूर्णांक i);

/* ----------------------------------------------------------- */
/* saa7164-encoder.c                                            */
पूर्णांक saa7164_s_std(काष्ठा saa7164_port *port, v4l2_std_id id);
पूर्णांक saa7164_g_std(काष्ठा saa7164_port *port, v4l2_std_id *id);
पूर्णांक saa7164_क्रमागत_input(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_input *i);
पूर्णांक saa7164_g_input(काष्ठा saa7164_port *port, अचिन्हित पूर्णांक *i);
पूर्णांक saa7164_s_input(काष्ठा saa7164_port *port, अचिन्हित पूर्णांक i);
पूर्णांक saa7164_g_tuner(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_tuner *t);
पूर्णांक saa7164_s_tuner(काष्ठा file *file, व्योम *priv, स्थिर काष्ठा v4l2_tuner *t);
पूर्णांक saa7164_g_frequency(काष्ठा saa7164_port *port, काष्ठा v4l2_frequency *f);
पूर्णांक saa7164_s_frequency(काष्ठा saa7164_port *port,
			स्थिर काष्ठा v4l2_frequency *f);
पूर्णांक saa7164_encoder_रेजिस्टर(काष्ठा saa7164_port *port);
व्योम saa7164_encoder_unरेजिस्टर(काष्ठा saa7164_port *port);

/* ----------------------------------------------------------- */
/* saa7164-vbi.c                                            */
पूर्णांक saa7164_vbi_रेजिस्टर(काष्ठा saa7164_port *port);
व्योम saa7164_vbi_unरेजिस्टर(काष्ठा saa7164_port *port);

/* ----------------------------------------------------------- */

बाह्य अचिन्हित पूर्णांक crc_checking;

बाह्य अचिन्हित पूर्णांक saa_debug;
#घोषणा dprपूर्णांकk(level, fmt, arg...)\
	करो अणु अगर (saa_debug & level)\
		prपूर्णांकk(KERN_DEBUG "%s: " fmt, dev->name, ## arg);\
	पूर्ण जबतक (0)

#घोषणा log_warn(fmt, arg...)\
	करो अणु \
		prपूर्णांकk(KERN_WARNING "%s: " fmt, dev->name, ## arg);\
	पूर्ण जबतक (0)

#घोषणा saa7164_पढ़ोl(reg) पढ़ोl(dev->lmmio + ((reg) >> 2))
#घोषणा saa7164_ग_लिखोl(reg, value) ग_लिखोl((value), dev->lmmio + ((reg) >> 2))

#घोषणा saa7164_पढ़ोb(reg)             पढ़ोl(dev->bmmio + (reg))
#घोषणा saa7164_ग_लिखोb(reg, value)     ग_लिखोl((value), dev->bmmio + (reg))

