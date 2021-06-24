<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _AV7110_H_
#घोषणा _AV7110_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/socket.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/समय.स>

#समावेश <linux/dvb/video.h>
#समावेश <linux/dvb/audपन.स>
#समावेश <linux/dvb/dmx.h>
#समावेश <linux/dvb/ca.h>
#समावेश <linux/dvb/osd.h>
#समावेश <linux/dvb/net.h>
#समावेश <linux/mutex.h>

#समावेश <media/dvbdev.h>
#समावेश <media/demux.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dmxdev.h>
#समावेश "dvb_filter.h"
#समावेश <media/dvb_net.h>
#समावेश <media/dvb_ringbuffer.h>
#समावेश <media/dvb_frontend.h>
#समावेश "ves1820.h"
#समावेश "ves1x93.h"
#समावेश "stv0299.h"
#समावेश "tda8083.h"
#समावेश "sp8870.h"
#समावेश "stv0297.h"
#समावेश "l64781.h"

#समावेश <media/drv-पूर्णांकf/saa7146_vv.h>


#घोषणा ANALOG_TUNER_VES1820 1
#घोषणा ANALOG_TUNER_STV0297 2

बाह्य पूर्णांक av7110_debug;

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (level & av7110_debug)					\
		prपूर्णांकk(KERN_DEBUG KBUILD_MODNAME ": %s(): " fmt,	\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

#घोषणा MAXFILT 32

क्रमागत अणुAV_PES_STREAM, PS_STREAM, TS_STREAM, PES_STREAMपूर्ण;

क्रमागत av7110_video_mode अणु
	AV7110_VIDEO_MODE_PAL	= 0,
	AV7110_VIDEO_MODE_NTSC	= 1
पूर्ण;

काष्ठा av7110_p2t अणु
	u8		  pes[TS_SIZE];
	u8		  counter;
	दीर्घ पूर्णांक	  pos;
	पूर्णांक		  frags;
	काष्ठा dvb_demux_feed *feed;
पूर्ण;

/* video MPEG decoder events: */
/* (code copied from dvb_frontend.c, should maybe be factored out...) */
#घोषणा MAX_VIDEO_EVENT 8
काष्ठा dvb_video_events अणु
	काष्ठा video_event	  events[MAX_VIDEO_EVENT];
	पूर्णांक			  eventw;
	पूर्णांक			  eventr;
	पूर्णांक			  overflow;
	रुको_queue_head_t	  रुको_queue;
	spinlock_t		  lock;
पूर्ण;


काष्ठा av7110;

/* infrared remote control */
काष्ठा infrared अणु
	काष्ठा rc_dev		*rcdev;
	अक्षर			input_phys[32];
	u32			ir_config;
पूर्ण;

/* place to store all the necessary device inक्रमmation */
काष्ठा av7110 अणु

	/* devices */

	काष्ठा dvb_device	dvb_dev;
	काष्ठा dvb_net		dvb_net;

	काष्ठा video_device	v4l_dev;
	काष्ठा video_device	vbi_dev;

	काष्ठा saa7146_dev	*dev;

	काष्ठा i2c_adapter	i2c_adap;

	अक्षर			*card_name;

	/* support क्रम analog module of dvb-c */
	पूर्णांक			analog_tuner_flags;
	पूर्णांक			current_input;
	u32			current_freq;

	काष्ठा tasklet_काष्ठा	debi_tasklet;
	काष्ठा tasklet_काष्ठा	gpio_tasklet;

	पूर्णांक adac_type;	       /* audio DAC type */
#घोषणा DVB_ADAC_TI	  0
#घोषणा DVB_ADAC_CRYSTAL  1
#घोषणा DVB_ADAC_MSP34x0  2
#घोषणा DVB_ADAC_MSP34x5  3
#घोषणा DVB_ADAC_NONE	 -1


	/* buffers */

	व्योम		       *iobuf;	 /* memory क्रम all buffers */
	काष्ठा dvb_ringbuffer	avout;   /* buffer क्रम video or A/V mux */
#घोषणा AVOUTLEN (128*1024)
	काष्ठा dvb_ringbuffer	aout;    /* buffer क्रम audio */
#घोषणा AOUTLEN (64*1024)
	व्योम		       *bmpbuf;
#घोषणा BMPLEN (8*32768+1024)

	/* biपंचांगap buffers and states */

	पूर्णांक			bmpp;
	पूर्णांक			bmplen;
	अस्थिर पूर्णांक		bmp_state;
#घोषणा BMP_NONE     0
#घोषणा BMP_LOADING  1
#घोषणा BMP_LOADED   2
	रुको_queue_head_t	bmpq;


	/* DEBI and polled command पूर्णांकerface */

	spinlock_t		debilock;
	काष्ठा mutex		dcomlock;
	अस्थिर पूर्णांक		debitype;
	अस्थिर पूर्णांक		debilen;


	/* Recording and playback flags */

	पूर्णांक			rec_mode;
	पूर्णांक			playing;
#घोषणा RP_NONE  0
#घोषणा RP_VIDEO 1
#घोषणा RP_AUDIO 2
#घोषणा RP_AV	 3


	/* OSD */

	पूर्णांक			osdwin;      /* currently active winकरोw */
	u16			osdbpp[8];
	काष्ठा mutex		osd_mutex;

	/* CA */

	काष्ठा ca_slot_info	ci_slot[2];

	क्रमागत av7110_video_mode	vidmode;
	काष्ठा dmxdev		dmxdev;
	काष्ठा dvb_demux	demux;

	काष्ठा dmx_frontend	hw_frontend;
	काष्ठा dmx_frontend	mem_frontend;

	/* क्रम budget mode demux1 */
	काष्ठा dmxdev		dmxdev1;
	काष्ठा dvb_demux	demux1;
	काष्ठा dvb_net		dvb_net1;
	spinlock_t		feedlock1;
	पूर्णांक			feeding1;
	u32			ttbp;
	अचिन्हित अक्षर           *grabbing;
	काष्ठा saa7146_pgtable  pt;
	काष्ठा tasklet_काष्ठा   vpe_tasklet;
	bool			full_ts;

	पूर्णांक			fe_synced;
	काष्ठा mutex		pid_mutex;

	पूर्णांक			video_blank;
	काष्ठा video_status	videostate;
	u16			display_panscan;
	पूर्णांक			display_ar;
	पूर्णांक			trickmode;
#घोषणा TRICK_NONE   0
#घोषणा TRICK_FAST   1
#घोषणा TRICK_SLOW   2
#घोषणा TRICK_FREEZE 3
	काष्ठा audio_status	audiostate;

	काष्ठा dvb_demux_filter *handle2filter[32];
	काष्ठा av7110_p2t	 p2t_filter[MAXFILT];
	काष्ठा dvb_filter_pes2ts p2t[2];
	काष्ठा ipack		 ipack[2];
	u8			*kbuf[2];

	पूर्णांक sinfo;
	पूर्णांक feeding;

	पूर्णांक arm_errors;
	पूर्णांक रेजिस्टरed;


	/* AV711X */

	u32		    arm_fw;
	u32		    arm_rtsl;
	u32		    arm_vid;
	u32		    arm_app;
	u32		    avtype;
	पूर्णांक		    arm_पढ़ोy;
	काष्ठा task_काष्ठा *arm_thपढ़ो;
	रुको_queue_head_t   arm_रुको;
	u16		    arm_loops;

	व्योम		   *debi_virt;
	dma_addr_t	    debi_bus;

	u16		    pids[DMX_PES_OTHER];

	काष्ठा dvb_ringbuffer	 ci_rbuffer;
	काष्ठा dvb_ringbuffer	 ci_wbuffer;

	काष्ठा audio_mixer	mixer;

	काष्ठा dvb_adapter	 dvb_adapter;
	काष्ठा dvb_device	 *video_dev;
	काष्ठा dvb_device	 *audio_dev;
	काष्ठा dvb_device	 *ca_dev;
	काष्ठा dvb_device	 *osd_dev;

	काष्ठा dvb_video_events  video_events;
	video_माप_प्रकार		 video_size;

	u16			wssMode;
	u16			wssData;

	काष्ठा infrared		ir;

	/* firmware stuff */
	अचिन्हित अक्षर *bin_fw;
	अचिन्हित दीर्घ size_fw;

	अचिन्हित अक्षर *bin_dpram;
	अचिन्हित दीर्घ size_dpram;

	अचिन्हित अक्षर *bin_root;
	अचिन्हित दीर्घ size_root;

	काष्ठा dvb_frontend* fe;
	क्रमागत fe_status fe_status;

	काष्ठा mutex ioctl_mutex;

	/* crash recovery */
	व्योम				(*recover)(काष्ठा av7110* av7110);
	क्रमागत fe_sec_voltage		saved_voltage;
	क्रमागत fe_sec_tone_mode		saved_tone;
	काष्ठा dvb_diseqc_master_cmd	saved_master_cmd;
	क्रमागत fe_sec_mini_cmd		saved_minicmd;

	पूर्णांक (*fe_init)(काष्ठा dvb_frontend* fe);
	पूर्णांक (*fe_पढ़ो_status)(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status);
	पूर्णांक (*fe_diseqc_reset_overload)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*fe_diseqc_send_master_cmd)(काष्ठा dvb_frontend *fe,
					 काष्ठा dvb_diseqc_master_cmd *cmd);
	पूर्णांक (*fe_diseqc_send_burst)(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_sec_mini_cmd minicmd);
	पूर्णांक (*fe_set_tone)(काष्ठा dvb_frontend *fe,
			   क्रमागत fe_sec_tone_mode tone);
	पूर्णांक (*fe_set_voltage)(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage);
	पूर्णांक (*fe_dishnetwork_send_legacy_command)(काष्ठा dvb_frontend *fe,
						  अचिन्हित दीर्घ cmd);
	पूर्णांक (*fe_set_frontend)(काष्ठा dvb_frontend *fe);
पूर्ण;


बाह्य पूर्णांक ChangePIDs(काष्ठा av7110 *av7110, u16 vpid, u16 apid, u16 ttpid,
		       u16 subpid, u16 pcrpid);

व्योम av7110_ir_handler(काष्ठा av7110 *av7110, u32 ircom);
पूर्णांक av7110_set_ir_config(काष्ठा av7110 *av7110);
पूर्णांक av7110_ir_init(काष्ठा av7110 *av7110);
व्योम av7110_ir_निकास(काष्ठा av7110 *av7110);

/* msp3400 i2c subaddresses */
#घोषणा MSP_WR_DEM 0x10
#घोषणा MSP_RD_DEM 0x11
#घोषणा MSP_WR_DSP 0x12
#घोषणा MSP_RD_DSP 0x13

बाह्य पूर्णांक i2c_ग_लिखोreg(काष्ठा av7110 *av7110, u8 id, u8 reg, u8 val);
बाह्य u8 i2c_पढ़ोreg(काष्ठा av7110 *av7110, u8 id, u8 reg);
बाह्य पूर्णांक msp_ग_लिखोreg(काष्ठा av7110 *av7110, u8 dev, u16 reg, u16 val);


बाह्य पूर्णांक av7110_init_analog_module(काष्ठा av7110 *av7110);
बाह्य पूर्णांक av7110_init_v4l(काष्ठा av7110 *av7110);
बाह्य पूर्णांक av7110_निकास_v4l(काष्ठा av7110 *av7110);

#पूर्ण_अगर /* _AV7110_H_ */
